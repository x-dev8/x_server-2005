#include "AstarPathFind.h"

#include "FuncPerformanceLog.h"
#include <vector>

DWORD CAstarPathFind::m_dwShortFindStartTime = 0;

inline const short CAstarPathFind::JudgeCost(short x,short y,short endx,short endy) const
{
	return 9*(abs(x-endx)+abs(y-endy));
}

void CAstarPathFind::Init()
{
	Node = NULL;
	Open = NULL;
	Close = NULL;
	Modify = NULL;
	height = width = 0;
	MaxSize = 0;
	ModifyPoint = 0;
	OpenCount = 0;
	CloseCount = 0;
	OpenLimited = 100*50;			// Open队列最多节点数目
	CloseLimited = 100*100L;		// Close队列最多节点数目
	DirMask = 0xff;					// 要搜索方向的标志，0-7位为从上开始顺时针七个方向
	MinPos = 0;
	TargetX = TargetY = 0;
	MoveAble = NULL;
}

// 待处理节点入队列, 依靠对目的地估价距离插入排序
char CAstarPathFind::AddToOpenQueue(TAstarNode *node)
{
	ADWORD i;
	short f=node->SumCost;
	register TAstarNode *p,*b;
	node->Modified|=2;    // 记录Open标志
	for (b=NULL,p=Open,i=0;p&&i<=OpenCount;b=p,p=p->Next,i++) 
		if (f<=p->SumCost) break;
	if (i>OpenCount) return -2;
	node->Next=p;
	node->Prev=b;
	if (b) b->Next=node;
	else Open=node;
	if (p) p->Prev=node;
	OpenCount++;
	return 0;
}

// 将离目的地估计最近的方案出队列
char CAstarPathFind::GetFromOpenQueue()
{
	TAstarNode *BestChoice=Open;
	if (!Open) return -1;
	Open=Open->Next;
	if (Open) Open->Prev=NULL;
	if (BestChoice->Modified&4) return -2; // 已经在Close中了
	BestChoice->Next=Close;
	BestChoice->Prev=NULL;
	BestChoice->Modified&=5;    // 清除Open标志
	BestChoice->Modified|=4;    // 设置Close标志
	if (Close) Close->Prev=BestChoice;
	Close=BestChoice;
	OpenCount--;
	CloseCount++;
	return 0;
}
// 释放栈顶节点
char CAstarPathFind::PopCloseStack()
{
	if (Close) { 
		Close->Modified&=3;        // 清除Close标志
		Close=Close->Next;
		if (Close) Close->Prev=NULL;
		CloseCount--; 
		return 0; 
	}
	return -1;
}
// 还原修改过的所有节点
void CAstarPathFind::ClearModified()
{
	ADWORD i;
	for (i=0;i<ModifyPoint;i++) {
		Modify[i]->Modified=0;
		Modify[i]->ActualCost=COST_MAX;
	}
	ModifyPoint=0;
	OpenCount=0;
	CloseCount=0;
	Open=NULL;
	Close=NULL;
}

extern std::vector< POINT > g_vecPathPoint;

// 尝试下一步移动到 x,y 可行否
char CAstarPathFind::TryTile(short x,short y,TAstarNode *Father,char FromDir)
{
    //POINT ptRecord = { x, y };
    //g_vecPathPoint.push_back( ptRecord );

    //void main_draw_monitor();
    //extern HWND g_hMainWnd;
    //if( g_hMainWnd )
        //main_draw_monitor();

	register TAstarNode *node;
	short ActualCost;

	if (!MoveAble(x,y)) 
        return 1;            // 如果地图无法通过则退出

	node=&Node[y][x];
	ActualCost=Father->ActualCost+1;        // 实际值计算
	if (ActualCost>=node->ActualCost) 
        return 1;

	if (node->Modified&2)                    // 在Open表中就清除
	{
		if (node->Next) node->Next->Prev=node->Prev;    
		if (node->Prev) node->Prev->Next=node->Next;
		else Open=node->Next;
		OpenCount--;
		node->Modified=1;
		node->Father=Father;
		node->ActualCost=ActualCost;
		node->SumCost=ActualCost+node->EstimateCost;
		AddToOpenQueue(node);
	}    
    else if (node->Modified&4) 
    {        // 在Close表中就清除
		if (node->Next) node->Next->Prev=node->Prev;
		if (node->Prev) node->Prev->Next=node->Next;
		else Close=node->Next;
		CloseCount--;
		node->Modified=1;
		node->Father=Father;
		node->ActualCost=ActualCost;
		node->SumCost=ActualCost+node->EstimateCost;
		AddToOpenQueue(node);
	}    
    else 
    {
		if (!(node->Modified&1)) Modify[ModifyPoint++]=node; // 记录这个修改过的点以还原
		node->Modified=1;
		node->Father=Father;
		node->DirFrom=FromDir;
		node->ActualCost=ActualCost;
		node->EstimateCost=JudgeCost(x,y,TargetX,TargetY);
		node->SumCost=ActualCost+node->EstimateCost;
		AddToOpenQueue(node);            // 将节点加入Open队列
	}
	return 0;
}

// 路径寻找主函数
int CAstarPathFind::FindPath(short startx,short starty,short endx,short endy)
{ 
	TAstarNode *root;
	int j,ok;
	short x,y;
	ADWORD max=0;
	short MinJudge;

	if (!Node||!Modify) return -1;
	ClearModified();
	root=&Node[starty][startx];
	root->ActualCost=0;
	root->EstimateCost=JudgeCost(startx,starty,endx,endy);
	root->SumCost=root->EstimateCost;
	root->Father=NULL; 
	root->Modified=1;
	Modify[ModifyPoint++]=root;
	AddToOpenQueue(root);
	MinPos=tile_pos(startx,starty);
	MinJudge=root->EstimateCost;
	TargetX=endx;
	TargetY=endy;

	for (ok=0;ok==0;)
	{
		ok=GetFromOpenQueue();        // 取出Open队列估价值最小的节点放入Close中
		root=Close;                    // 得到刚才取出的节点
		if (ok||root==NULL) 
        { 
            ok=-1; 
            break; 
        }
		x=(short)tile_x(root->Pos);
		y=(short)tile_y(root->Pos);
		if (root->EstimateCost<MinJudge)    // 找到一个估计离终点最近的点
        {
			MinJudge=root->EstimateCost, MinPos=root->Pos;
        }
		if (CloseCount>max) 
        {
            max=CloseCount;
        }
		if (x==endx&&y==endy) 
        {
            MinPos=root->Pos,ok=1;    // 如果走到终点了
        }
		else 
        {
			j=1;
			if (DirMask&1) 
                j&=TryTile(x,y-1,root,0);
			if (DirMask&2) 
                j&=TryTile(x+1,y-1,root,0);
			if (DirMask&4) 
                j&=TryTile(x+1,y,root,0);
			if (DirMask&8) 
                j&=TryTile(x+1,y+1,root,0);
			if (DirMask&16) 
                j&=TryTile(x,y+1,root,0);
			if (DirMask&32) 
                j&=TryTile(x-1,y+1,root,0);
			if (DirMask&64) 
                j&=TryTile(x-1,y,root,0);
			if (DirMask&128) 
                j&=TryTile(x-1,y-1,root,0);
			if (j) 
            {
                if (PopCloseStack()) 
                { 
                    ok=-2; 
                    break; 
                }    // 如果不是通路则从Close中取出
            }
		}
		if (OpenCount>=OpenLimited||CloseCount>=CloseLimited) 
        {
            ok=2;
        }
	}

	if (ok<0) 
    {
        return -2;
    }

	return 0;
}

int CAstarPathFind::GetPosPath(short *pstPosXY,int maxpos)
{
	TAstarNode* p = &Node[tile_y(MinPos)][tile_x(MinPos)];
	TAstarNode* s = p;
	if ( maxpos == 0 )	return p->ActualCost;
	else if (maxpos>1)	maxpos--;
	else return 0;
	short x,y;
	ADWORD j;
	int i;
	for ( j=0;p&&j<MaxSize;p=p->Father,j++ )
	{
		x=(short)tile_x(p->Pos);
		y=(short)tile_y(p->Pos);
		i=(p->ActualCost<maxpos)?p->ActualCost:maxpos;
		pstPosXY[2*i]  = x;
		pstPosXY[2*i+1]= y;
	}
	i=(s->ActualCost+1<maxpos)?(s->ActualCost+1):maxpos;
	//pstPosXY[i]=END;
	//PosXY[i]=END;
	return j;
}

int CAstarPathFind::GetDirPath(char *PosDir,int maxpos)
{
	TAstarNode* p = &Node[tile_y(MinPos)][tile_x(MinPos)];
	TAstarNode* s = p;
	if (maxpos == 0) return p->ActualCost;
	else if (maxpos>1) maxpos--;
	else return 0;
	static char inc2r[10]={ 7,0,1,6,8,2,5,4,3,0 }; 
	short i=0,x=0,y=0,nx=0,ny=0;
	ADWORD j;
	for (j=0;p&&j<MaxSize;p=p->Father,j++)
	{
		nx=(short)tile_x(p->Pos);
		ny=(short)tile_y(p->Pos);
		i=(p->ActualCost<maxpos)?(p->ActualCost):maxpos;
		PosDir[i]=inc2r[(y-ny+1)*3+x-nx+1];
		x=nx;
		y=ny;
	}
	i=(s->ActualCost+1<maxpos)?(s->ActualCost+1):maxpos;
	PosDir[i]=8;
	return j;
}

int CAstarPathFind::Create(int mapw,int maph,bool (*MoveCheck)(short,short) )
{
	Release();

	int i,j;
	height=maph;    width=mapw;
	MaxSize=maph;    MaxSize*=mapw;
	Modify=new TAstarNode*[MaxSize*2];
	if (!Modify) return -1;
	Node=new TAstarNode*[maph];
	if (!Node) 
	{ 
		delete Modify; 
		Modify=0; 
		return -1; 
	}

	for (i=0;i<maph;i++) 
		Node[i] = new TAstarNode[mapw];

	for (i=0,j=1;i<maph;i++) 
		if (!Node[i]) 
			j=0;

	if (!j)
	{
		for (i=0;i<maph;i++) 
			if (Node[i]) 
			{
				delete Node[i];
				Node[i] = 0;
			}
		delete [] Node;
		delete [] Modify;

		return -2;
	}
	for (j=0;j<maph;j++) 
		for (i=0;i<mapw;i++) 
		{
			Node[j][i].Pos=tile_pos(i,j);
			Node[j][i].Modified=0;
			Node[j][i].ActualCost=COST_MAX;
		}
		ModifyPoint=0;
		SetMapCheck(MoveCheck);
		CloseLimited = MaxSize/20;
		return 0;
}
int CAstarPathFind::Release()
{
	int j;
	if (Node) 
		for (j=0;j<height;j++) 
			if (Node[j]) 
			{
				delete Node[j];
				Node[j] = 0;
			}
	if (Node) 
		delete [] Node;

	if (Modify) 
	{
		delete Modify;
		Modify = 0;
	}

	return 0;
}

// 路径寻找主函数
int CAstarPathFind::FindPathShort(short startx,short starty,short endx,short endy)
{
    TAstarNode *root;
    int j,ok;
    short x,y;
    ADWORD max=0;
    short MinJudge;

    if (!Node||!Modify) return -1;
    ClearModified();
    root=&Node[starty][startx];
    root->ActualCost=0;
    root->EstimateCost=JudgeCost(startx,starty,endx,endy);
    root->SumCost=root->EstimateCost;
    root->Father=NULL; 
    root->Modified=1;
    Modify[ModifyPoint++]=root;
    AddToOpenQueue(root);
    MinPos=tile_pos(startx,starty);
    MinJudge=root->EstimateCost;
    TargetX=endx;
    TargetY=endy;

    DWORD now = HQ_TimeGetTime();

    for (ok=0;ok==0;)
    {
        ok=GetFromOpenQueue();        // 取出Open队列估价值最小的节点放入Close中
        root=Close;                    // 得到刚才取出的节点
        if (ok||root==NULL) 
        { 
            ok=-1; 
            break; 
        }
        x=(short)tile_x(root->Pos);
        y=(short)tile_y(root->Pos);
        if (root->EstimateCost<MinJudge)    // 找到一个估计离终点最近的点
        {
            MinJudge=root->EstimateCost, MinPos=root->Pos;
        }
        if (CloseCount>max) 
        {
            max=CloseCount;
        }
        if( now - m_dwShortFindStartTime >= CONST_SHORTFINDINTERVAL )
        {
            MinPos = root->Pos,ok=1;
        }
        else if( OpenCount > CONST_SHORTFINDLENGTH )
        {
            MinPos = root->Pos,ok=1;
        }
        else if (x==endx&&y==endy) 
        {
            MinPos=root->Pos,ok=1;    // 如果走到终点了
        }
        else 
        {
            j=1;
            if (DirMask&1) 
                j&=TryTile(x,y-1,root,0);
            if (DirMask&2) 
                j&=TryTile(x+1,y-1,root,0);
            if (DirMask&4) 
                j&=TryTile(x+1,y,root,0);
            if (DirMask&8) 
                j&=TryTile(x+1,y+1,root,0);
            if (DirMask&16) 
                j&=TryTile(x,y+1,root,0);
            if (DirMask&32) 
                j&=TryTile(x-1,y+1,root,0);
            if (DirMask&64) 
                j&=TryTile(x-1,y,root,0);
            if (DirMask&128) 
                j&=TryTile(x-1,y-1,root,0);
            if (j) 
            {
                if (PopCloseStack()) 
                { 
                    ok=-2; 
                    break; 
                }    // 如果不是通路则从Close中取出
            }
        }
        if (OpenCount>=OpenLimited||CloseCount>=CloseLimited) 
        {
            ok=2;
        }
    }

    if (ok<0) 
    {
        return -2;
    }
	return 0;
}
