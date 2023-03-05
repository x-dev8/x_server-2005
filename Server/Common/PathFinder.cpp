#include "PathFinder.h"
#include "GameStage.h"

//这个宏对性能有影响
#define CAN_GO_EDGE

#define RECURETIMES 16  // 这个值与MAX_CHAR_PATH_NODE_NUMBER一致
#define OFFSETY     128

PathFinder::PathFinder( GameStage* owner,const char* filename,uint32& mx,uint32& mz)
{
    strncpy_s( mFileName, sizeof(mFileName), filename, sizeof(mFileName)-1 );
    pStageOwner = owner;

    ReadNavMap(filename,mx,mz);

    InitEightDirections();
}

//读取导航信息，文件由编辑器生成
void PathFinder::ReadNavMap( const char* filename, uint32& mx, uint32& mz )
{
    FILE* fp = fopen(filename, "rb");
    if(NULL == fp) 
    {
        assert(fp);
        return ;
    }

    _NAVMAP_HEAD head;
    fread(&head, sizeof(_NAVMAP_HEAD), 1, fp);

    mGridCX = head.width;
    mGridCY = head.height;
    mGridSize = 0.5;
    mInvGridSize = 1 / mGridSize;

    // 得到地图的实际大小
    mx = (uint32)(mGridCX * mGridSize);
    mz = (uint32)(mGridCY * mGridSize);

    mLeftTopx = 0;
    mLeftTopy = 0;

    mMaxNode = mGridCX * mGridCY;

    mWorld = new _WORLD[mMaxNode];
    mWorkWorld = new _WORLD[mMaxNode];
    mNodes = new _NODES[mMaxNode + 1];

    int32 size = sizeof(struct _NAVMAP_HEAD);
    for(int32 j=0;j<mGridCY;j++)
    {
        for(int32 i=0;i<mGridCX;i++)
        {
            int32 info;
            fread(&info,size,1,fp);

            _WORLD* pWorld = mWorld + j * mGridCX + i;
            pWorld->state = info;            
        }
    }

    mNodes[0].yx=0;
    mNodes[0].f=0;
    mNodes[0].g=0;

    curStep=0;
}

//-----------------------------------------------------------------------------
/*
 *                  
 规律如下:
                    5   2   6

                    1   *   3            
                    
                    4   0   7


                    4 5 6 7   0 1 2 3             
                    6 7 4 5   2 3 0 1
 */
//-----------------------------------------------------------------------------
void PathFinder::InitEightDirections()
{
    for( int32 n=0; n<4; ++n)
    { DYX[n].costmultiplier = 10; }

    for( int32 n=4; n<8; ++n)
    { DYX[n].costmultiplier = 14; }

    DYX[0].yx = -mGridCX;
    DYX[0].route = 2;

    DYX[1].yx = 1;
    DYX[1].route = 3;

    DYX[2].yx = mGridCX;
    DYX[2].route = 0;

    DYX[3].yx = -1;
    DYX[3].route = 1;


    DYX[4].yx = -mGridCX + 1;
    DYX[4].route = 6;

    DYX[5].yx = mGridCX + 1;
    DYX[5].route = 7;

    DYX[6].yx = mGridCX - 1;
    DYX[6].route = 4;

    DYX[7].yx = -mGridCX - 1;
    DYX[7].route = 5;
}

PathFinder::~PathFinder()
{   
    SAFE_DELETE_ARRAY(mWorld);
    SAFE_DELETE_ARRAY(mWorkWorld);
    SAFE_DELETE_ARRAY(mNodes);
}

void PathFinder::Reset(int32 starty,int32 endz)
{   
    assert( starty >= 0 && endz < mGridCY);

    //256*256的mempcy大约花费0.040毫秒
    memcpy((void*)(mWorkWorld + (starty * mGridCX)),(void*)(mWorld + (starty * mGridCX)),(endz - starty) * mGridCX * sizeof(_WORLD));
    //memcpy((void*)mWorkWorld,(void*)(mWorld),mMaxNode * sizeof(_WORLD));

    mBestFNode = 1;
    mNodes[mBestFNode].yx = mStartyx;
    mNodes[mBestFNode].g = 0;
    mNodes[mBestFNode].f = mNodes[mBestFNode].g + Distance(mStartyx);

    mWorkWorld[mStartyx].route = NO_ROUTE;
    
    mFreeNode = 1;
    
    mHeap[0] = EMPTY_NODE;
    mLastHeapLeaf = 1;
    mHeap[mLastHeapLeaf] = mBestFNode;
}

//-----------------------------------------------------------------------------
//二叉堆A*
//-----------------------------------------------------------------------------
void PathFinder::RemoveRootFromHeap()
{
    mHeap[ROOT_HEAP] = mHeap[mLastHeapLeaf--];
    
    int32 k=ROOT_HEAP;
    while(NOTEMPTY_DOWN(k))
    {
        int32 leftk=LEFT(k);
        int32 rightk=RIGHT(k);
        int32 bestk;
        if(NOTEMPTY_DOWN(leftk) && NOTEMPTY_DOWN(rightk) )
        {
            if(mNodes[mHeap[leftk]].f < mNodes[mHeap[rightk]].f)
            { bestk = leftk; }
            else
            { bestk = rightk; }
        }
        else if(NOTEMPTY_DOWN(leftk))
        { bestk=leftk; }
        else
        { break; }
        
        if(mNodes[mHeap[bestk]].f < mNodes[mHeap[k]].f)
        {
            SwapHeap(k,bestk);
            k=bestk;
        }
        else
        { break; }
    }
}

void PathFinder::InsertNodeToHeap(uint16 node)
{
    if(mLastHeapLeaf < MAX_HEAP_LEAFS)
    { mLastHeapLeaf++; }
    
    mHeap[mLastHeapLeaf] = node;
    
    int32 k = mLastHeapLeaf;
    while(NOTEMPTY_UP(k))
    {
        int32 parentk=PARENT(k);
        if(NOTEMPTY_UP(parentk))
        {
            if(mNodes[mHeap[k]].f < mNodes[mHeap[parentk]].f)
            {
                SwapHeap(k,parentk);
                k=parentk;
            }
            else
            { break; }
        }
        else
        { break; }
    }
}

//-----------------------------------------------------------------------------
//导航图格子的大小目前暂定为0.5m
//寻路核心函数
//-----------------------------------------------------------------------------
bool PathFinder::FindPath( SWorldPos* startPt, SWorldPos* endPt, SWorldPos* posNode,int32& numNode,int32 nLevel,bool bLine,int32 maxRoute)
{
    if(startPt->fX >= 0  && startPt->fY <pStageOwner->GetHeight() && endPt->fX >= 0 && endPt->fY < pStageOwner->GetHeight() && 
        startPt->fY >= 0 && startPt->fX <pStageOwner->GetWidth()  && endPt->fY >= 0 && endPt->fX < pStageOwner->GetWidth())
    {}
    else
    { return false; }

    mfStartX = startPt->fX;
    mfStartY = startPt->fY;
    mfEndX   = endPt->fX;
    mfEndY   = endPt->fY;
    
    // 起始点在哪个格子上
    mStartx = (uint16) ( ( mfStartX - mLeftTopx ) * mInvGridSize);
    mStarty = (uint16) ( ( mfStartY - mLeftTopy ) * mInvGridSize);

    //结束点在那个格子上

    mEndx = (uint16)( ( mfEndX - mLeftTopx ) * mInvGridSize);
    mEndy = (uint16)( ( mfEndY - mLeftTopy ) * mInvGridSize);

    // 起始点和结束点
    mStartyx = mStarty * mGridCX + mStartx;
    mEndyx   = mEndy * mGridCX + mEndx;

    numNode = 0;
    
    mDistance = 0;
    // 如果需要直线寻路
    if( bLine )
    {
        if( IsCanGo(mWorld[mStartyx].state, nLevel) )
        {
            if(IsStraightLine(mfStartX,mfStartY,mfEndX,mfEndY,false,nLevel))
            {
                posNode[numNode++] = SWorldPos(mfEndX,mfEndY);
                mDistance = RealDistance(mStartyx,mEndyx);
                return true;
            }
            else
            {
                posNode[numNode++] = mFirstCanGoPos;
                mDistance = RealDistance(mStartyx,(uint16) ( ( mFirstCanGoPos.fY - mLeftTopy ) * mInvGridSize) * mGridCX + (uint16) ( ( mFirstCanGoPos.fX - mLeftTopx ) * mInvGridSize) );
                return true;
            }
        }
        else
        { return false; }
    }

    //做A*寻路
    //如果起始点和目标点皆不可行走
    //if(mWorld[mStartzx].state == IMPASSABLE || mWorld[mEndzx].state == IMPASSABLE)
    if( !IsCanGo(mWorld[mStartyx].state, nLevel) || !IsCanGo(mWorld[mEndyx].state, nLevel) )
    {
        return false;
    }
    else
    {
        int32 deltax = abs(mEndx - mStartx);
        int32 deltay = abs(mEndy - mStarty);

        //太远
        if( (deltax + deltay) > maxRoute)
        {
            mDistance = RealDistance(mStartyx,(uint16) ( ( mFirstCanGoPos.fY - mLeftTopy ) * mInvGridSize) * mGridCX + (uint16) ( ( mFirstCanGoPos.fX - mLeftTopx ) * mInvGridSize) );
            return false;
        }

        if( IsStraightLine(mfStartX,mfStartY,mfEndX,mfEndY,false,nLevel))
        {
            posNode[numNode++] = SWorldPos(mfEndX,mfEndY);
            mDistance = RealDistance(mStartyx,mEndyx);
            return true;
        }
        
        int32 minz = min(mStarty,mEndy);
        int32 maxz = max(mStarty,mEndy);
        minz = max(minz - OFFSETY,0);
        maxz = min(maxz + OFFSETY,mGridCY - 1);

        Reset(minz,maxz);
        int32 count = maxRoute;

        do
        {
            mBestFNode = mHeap[ROOT_HEAP];

            //关闭节点
            _NODES *pparent_node = mNodes + mBestFNode;

            //相等,则完成了寻路
            if(pparent_node->yx == mEndyx) 
            {                
                PackRoute(posNode,numNode,nLevel);
                return true;
            }

            mWorkWorld[pparent_node->yx].state = CLOSED;
            RemoveRootFromHeap(); 
            
            // 打开节点
            for( uint8 d = 0;d < EIGHT_DIRECTIONS ; d++)
            {
            //边界过滤,示意
            //运行版本,因地图的四周皆不可走,故而可以不用
            /*
             *    
             0     1     2     3                                           127
             
            127   128   129   130
            
            256   257   258
             */
            
#ifdef CAN_GO_EDGE //release版本不用
                int32 yx = (int32)( pparent_node->yx);
                if( ( yx % mGridCX == 0) && ( (d == 3) || (d == 6) || (d == 7) ) )
                { continue; }

                if( ( yx % mGridCX == (mGridCX -1) ) && ( ( d == 1) || ( d == 4 ) || (d == 5 ) ) )
                { continue; }

                yx += DYX[d].yx;
                if(yx < 0 || yx>= mGridCX * mGridCY)
                { continue; }

#else
                uint16 yx = pparent_node->yx + DYX[d].yx;
#endif
                
                _WORLD *pworld = mWorkWorld + yx;

                if(pworld->state == UNKNOWN) 
                {
                    pworld->state = OPEN; 
                    pworld->route = d; 

                    mFreeNode++; 

                    _NODES *pfree_node = mNodes + mFreeNode;
                    pfree_node->yx = yx;
                    pfree_node->g = pparent_node->g + DYX[d].costmultiplier;
                    pfree_node->f = pfree_node->g + Distance(yx);

                    InsertNodeToHeap(mFreeNode);
                }
            }

            if(mLastHeapLeaf <= 0)
            {
                posNode[numNode++] = mFirstCanGoPos;
                mDistance = RealDistance(mStartyx,(uint16) ( ( mFirstCanGoPos.fY - mLeftTopy ) * mInvGridSize) * mGridCX + (uint16) ( ( mFirstCanGoPos.fX - mLeftTopx ) * mInvGridSize) );
                return TRUE;
            }
        } 
        while( --count>0 );
#ifdef _DEBUG
        count;
#endif
    }

    return false;

}

inline uint16 PathFinder::Distance(const uint32 zx)
{
    //mWidth不能保证为2^
    return (uint16)( ( abs( (int32) (zx & (mGridCX-1)) - (int32) mEndx ) + abs( (int32)(zx / mGridCX) - (int32) mEndy ) ) * 10);
}

void PathFinder::PackRoute(SWorldPos* posNode,int32& numNode, int32 nLevel)
{   
    AIROUTE airoute;
    memset(airoute.route,0,MAX_ROUTES); 
    
    uint32 zx = mEndyx;
    int32 start = MAX_ROUTES - 1;
    uint8 route = NO_ROUTE;

    mGridNum = 0;
    // 优化后代码    
    SWorldPos firstPos;
    mGrids[mGridNum++] = zx;
    mDistance = 0;
    while(zx != mStartyx)
    {
        //反解
        route = mWorkWorld[zx].route;
        zx += DYX[DYX[route].route].yx;

        int32 x = zx % mGridCX;
        int32 z = zx / mGridCX;

        SWorldPos goPos;
        goPos.fX = mLeftTopx + x * mGridSize + mGridSize/2;
        goPos.fY = mLeftTopy + z * mGridSize + mGridSize/2;

        if(IsStraightLine(mfStartX,mfStartY,goPos.fX,goPos.fY,TRUE,nLevel))
        {
            firstPos.fX = mLeftTopx +  x * mGridSize + mGridSize/2;
            firstPos.fY = mLeftTopy +  z * mGridSize + mGridSize/2;

            posNode[numNode++] = firstPos;
            mDistance += RealDistance(zx,mGrids[mGridNum-1]);
            break;
        }
        else
        {
            mGrids[mGridNum++] = zx;
            mDistance += RealDistance(zx,mGrids[mGridNum-1]);
        }
    }

    if(mGridNum)
    {
        mCallTimes = 0;
        curStep = mGridNum;

        EditAStarPathOpt(firstPos.fX,firstPos.fY,posNode,numNode, nLevel);
    }
}

// 这是3d意义上的直线判断
bool PathFinder::IsStraightLine( float mAStarBeginPtx, float mAStarBeginPty, float mAStarEndPtx, float mAStarEndPty, bool edit, int32 nLevel)
{
    int32 intersecttime  = 0;

    SWorldPos startPt(mAStarBeginPtx,mAStarBeginPty);
    SWorldPos endPt(mAStarEndPtx,mAStarEndPty);
    
    int32 xinc1,yinc1;

    //起始点和结束点肯定在内
    int32 x1,y1,x2,y2;
    x1 = (int32)( ( startPt.fX - mLeftTopx ) * mInvGridSize);
    y1 = (int32)( ( startPt.fY - mLeftTopy ) * mInvGridSize);
    x2 = (int32)( ( endPt.fX - mLeftTopx ) * mInvGridSize);
    y2 = (int32)( ( endPt.fY - mLeftTopy ) * mInvGridSize);    

    float deltax,deltay;
    deltax = (endPt.fX-startPt.fX) * mInvGridSize;        
    deltay = (endPt.fY-startPt.fY) * mInvGridSize;

    mFirstCanGoPos = startPt;
    //斜率小于1
    if (fabs(deltax) >= fabs(deltay))
    {
        float slerp = deltay/deltax;

        if (x2 >= x1)                 
        {
            xinc1 = 1;

            for(int32 x =  x1 + xinc1; x <= x2; x += xinc1)
            {
                int32 y = (int32)( ( ( mLeftTopx + x * mGridSize - startPt.fX) * slerp + startPt.fY - mLeftTopy) * mInvGridSize);

                int32 index = x + y * mGridCX; 
                
                //if(mWorld[index].state == IMPASSABLE && (edit ? intersecttime++ : 1 ) )
                if( !IsCanGo(mWorld[index].state,nLevel) && (edit ? intersecttime++ : 1 ) )
                    return false;
                
                mFirstCanGoPos = SWorldPos(mLeftTopx +  x * mGridSize + mGridSize/2,
                mLeftTopy +  y * mGridSize + mGridSize/2);

                index = x - xinc1 + y * mGridCX;
                //if(mWorld[index].state == IMPASSABLE && (edit ? intersecttime++ : 1 ) )
                if( !IsCanGo(mWorld[index].state, nLevel) && (edit ? intersecttime++ : 1 ) )
                    return false;

                mFirstCanGoPos = SWorldPos(mLeftTopx +  ( x - xinc1) * mGridSize + mGridSize/2,
                    mLeftTopy +  y * mGridSize + mGridSize/2);
            }
        }
        else                          
        {
            xinc1 = -1;
            for(int32 x = x1;x >= x2 - xinc1;x += xinc1)
            {
                int32 y =  (int32) ( ( startPt.fY + slerp * ( (mLeftTopx + x*mGridSize) - startPt.fX) - mLeftTopy  ) * mInvGridSize);

                int32 index = x + y * mGridCX; 
                //if(mWorld[x + y * mWidth].state == IMPASSABLE && (edit ? intersecttime++ : 1 ) )
                if( !IsCanGo(mWorld[x + y * mGridCX].state, nLevel) && (edit ? intersecttime++ : 1 ) )
                    return false;

                mFirstCanGoPos = SWorldPos(mLeftTopx +  x * mGridSize + mGridSize/2,
                    mLeftTopy +  y * mGridSize + mGridSize/2);

                index = x + xinc1 + y * mGridCX; 
                //if(mWorld[index].state == IMPASSABLE && (edit ? intersecttime++ : 1 ) )
                if( !IsCanGo(mWorld[index].state,nLevel) && (edit ? intersecttime++ : 1 ) )
                    return false;

                mFirstCanGoPos = SWorldPos(mLeftTopx +  ( x + xinc1) * mGridSize + mGridSize/2,
                    mLeftTopy +  y * mGridSize + mGridSize/2);

            }
        }    
    }
    else//斜率大于1                          
    {
        float slerpInv = deltax/deltay;

        if (y2 >= y1)                 
        {
            yinc1 = 1;        
            for(int32 y = y1 + yinc1;y <= y2;y +=yinc1)
            {
                int32 x = (int32) ( ( (( mLeftTopy + y * mGridSize) - startPt.fY) * slerpInv + startPt.fX - mLeftTopx) * mInvGridSize);
                int32 index = x + y * mGridCX; 
                //if(mWorld[index].state == IMPASSABLE && (edit ? intersecttime++ : 1 ) )
                if( !IsCanGo(mWorld[index].state, nLevel) && (edit ? intersecttime++ : 1 ) )
                    return false;

                mFirstCanGoPos = SWorldPos(mLeftTopx +  x * mGridSize + mGridSize/2,
                    mLeftTopy +  y * mGridSize + mGridSize/2);

                index = x + (y - yinc1) * mGridCX;
                //if(mWorld[index].state == IMPASSABLE && (edit ? intersecttime++ : 1 ) )
                if( !IsCanGo(mWorld[index].state,nLevel) && (edit ? intersecttime++ : 1 ) )
                    return false;

                mFirstCanGoPos = SWorldPos(mLeftTopx +  x * mGridSize + mGridSize/2,
                    mLeftTopy +  (y - yinc1) * mGridSize + mGridSize/2);
            }
        }
        else                          
        {
            yinc1 = -1;
            for(int32 y = y1;y >= y2 -yinc1;y += yinc1)
            {
                int32 x =  (int32)( ( startPt.fX + slerpInv * ( (mLeftTopy + y*mGridSize) - startPt.fY) - mLeftTopx  ) * mInvGridSize);

                int32 index = x + y * mGridCX; 
                //if(mWorld[index].state == IMPASSABLE && (edit ? intersecttime++ : 1 ) )
                if( !IsCanGo(mWorld[index].state, nLevel) && (edit ? intersecttime++ : 1 ) )
                    return false;

                mFirstCanGoPos = SWorldPos(mLeftTopx +  x * mGridSize + mGridSize/2,
                    mLeftTopy +  y * mGridSize + mGridSize/2);

                index = x + (y + yinc1) * mGridCX;
                //if(mWorld[index].state == IMPASSABLE && (edit ? intersecttime++ : 1 ) )
                if( !IsCanGo(mWorld[index].state, nLevel) && (edit ? intersecttime++ : 1 ) )
                    return false;

                mFirstCanGoPos = SWorldPos(mLeftTopx +  x * mGridSize + mGridSize/2,
                    mLeftTopy +  (y + yinc1) * mGridSize + mGridSize/2);
            }
        }


    }

    return true;
}

void PathFinder::EditAStarPathOpt(float startPtx,float startPty,SWorldPos* posNode,int32& numNode,int32 nLevel)
{
    if(mCallTimes++ >= RECURETIMES)
    { return; }
    
    for(int32 i=0; i<curStep; i++)
    {
        int32 x = mGrids[i] % mGridCX;
        int32 y = mGrids[i] / mGridCX;

        SWorldPos goPos;
        if(i != 0)
        {
            goPos.fX = mLeftTopx + x * mGridSize + mGridSize/2;
            goPos.fY = mLeftTopy +  y * mGridSize + mGridSize/2;
        }
        else
        {
            goPos = SWorldPos(mfEndX,mfEndY);
        }

        if(IsStraightLine(startPtx,startPty,goPos.fX,goPos.fY,TRUE,nLevel))
        {
            posNode[ numNode++ ] = goPos;
            curStep = i;

            break;
        }
    }

    if(curStep)
    {
        int32 x = mGrids[curStep] % mGridCX;
        int32 y = mGrids[curStep] / mGridCX;

        SWorldPos startPos;
        startPos.fX = mLeftTopx +  x * mGridSize + mGridSize/2;
        startPos.fY = mLeftTopy +  y * mGridSize + mGridSize/2;

        EditAStarPathOpt(startPos.fX,startPos.fY,posNode,numNode,nLevel);
    }
    else
    {
        numNode;
        numNode;
    }
}

bool PathFinder::IsCanGo(const SWorldPos& pos, const int32 nLevel)
{
    int32 gridx = (uint16) ( ( pos.fX - mLeftTopx ) * mInvGridSize);
    int32 gridy = (uint16) ( ( pos.fY - mLeftTopy ) * mInvGridSize);

    if ( (gridx >= 0 && gridx < mGridCX) && (gridy >= 0 && gridy < mGridCY) )
    { return IsCanGo(mWorld[ gridy * mGridCX + gridx].state,nLevel); }

    return false;
}

// 项目需求高度差 不仅仅是是否可以行
bool PathFinder::IsCanGo( const int32 state, const int32 nDriverLevel )
{ return nDriverLevel >= state; }


//这个函数并不递归
//void PathFinder::EditAStarPath(float startPtx,float startPty,SWorldPos* posNode,int32& numNode)
//{
//    if(mCallTimes++ >= RECURETIMES)
//        return;
//    
//    int32 curGrid = 0;
//
//    for(int32 i= mGridNum - 1;i >= curStep; i--)
//    {
//        int32 x = mGrids[i] % mWidth;
//        int32 y = mGrids[i] / mWidth;
//
//        SWorldPos goPos;
//        goPos.fX = mLeftTopx + x * mGridSize + mGridSize/2;
//        goPos.fY = mLeftTopz +  y * mGridSize + mGridSize/2;
//
//        if(IsStraightLine(startPtx,startPty,goPos.fX,goPos.fY,TRUE))
//        {
//            curStep = i;
//            posNode[ numNode++ ] = goPos;
//
//            curGrid = mGrids[i];            
//
//            break;
//        }
//    }
//
//    if(curGrid != mGrids[mGridNum-1])
//    {
//        int32 x = curGrid % mWidth;
//        int32 y = curGrid / mWidth;
//
//        SWorldPos startPos;
//        startPos.fX = mLeftTopx +  x * mGridSize + mGridSize/2;
//        startPos.fY = mLeftTopz +  y * mGridSize + mGridSize/2;
//
//        EditAStarPath(startPos.fX,startPos.fY,posNode,numNode);
//    }
//}
