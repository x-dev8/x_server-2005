///********************************************************************
//    Filename:    PathFinder.h
//    MaintenanceMan Mail: Luo_157@hotmail.com
//*********************************************************************/
//
//#ifndef __SERVERCOMMON_PATHFINDER_H__
//#define __SERVERCOMMON_PATHFINDER_H__
//
//#pragma once
//
//#include "MeRTLibsServer.h"
//#include "GameDefineSystem.h"
//#include "GameDefineLogic.h"
//
////AI可以行走格子数目
//#define MAX_ROUTES       1024 * 2
//#define EIGHT_DIRECTIONS 8
//
//class GameStage;
//
//class PathFinder
//{
//private:
//    struct _D2XZLOOKUP
//    {
//        uint16 costmultiplier;
//        short  yx;
//        uint8  route;
//    } DYX[EIGHT_DIRECTIONS];
//
//    struct AIROUTE
//    {
//        uint16 count;//不等于0时,其它数据才有意义
//
//        // 行走起始点
//        uint16 walkpoint;
//        uint32 startzx;
//        uint32 endzx;
//        uint8  route[MAX_ROUTES]; 
//    };
//
//    struct _WORLD
//    {
//        int32 state : 4; 
//        int32 route : 4; 
//    };
//
//    struct _NODES
//    {
//        uint16 f;
//        uint16 g;
//        uint32 yx;
//    };
//
//    struct _NAVMAP_HEAD 
//    {
//        uint16 width;
//        uint16 height;
//    };    
//
//
//    enum
//    {
//        EMPTY_NODE     = 0,
//        MIN_NODE       = 1,
//        NO_ROUTE       = EIGHT_DIRECTIONS,
//        MAX_HEAP_LEAFS = MAX_ROUTES,
//    };
//
//    enum
//    {
//        UNKNOWN    = 0,
//        IMPASSABLE = 1,
//        OPEN       = 20,
//        CLOSED     = 30,
//    };
//
//    enum
//    {
//        FINDING    = 0,
//        NO_PATH    = 1,
//        PATH_FOUND = 2,
//    };
//
//    enum
//    {
//        ROOT_HEAP = 1
//    };
//
//private:
//    char       mFileName[MAX_FILE_PATH];
//    GameStage* pStageOwner;
//    int32      mGridCX,mGridCY;      // 导航图的横向和纵向的尺寸
//    float      mGridSize;            // 一个格子的尺寸
//    float      mInvGridSize;         // 每米多少个格子
//    float      mLeftTopx, mLeftTopy; // 基准点位置
//
//    _WORLD* mWorld;
//    _WORLD* mWorkWorld;
//    _NODES* mNodes;
//
//    uint16 mLastHeapLeaf;
//    uint16 mHeap[MAX_HEAP_LEAFS];
//
//    uint16 mBestFNode;
//    uint16 mFreeNode;
//    int32 mMaxNode;
//
//    uint32 mStartyx,mEndyx;                 // 开始与结束数组下标
//    uint16 mStartx, mStarty, mEndx, mEndy;  // 开始与结束地图格子坐标
//    float  mfStartX,mfStartY,mfEndX,mfEndY; // 开始与结束的空间坐标
//
//    //直线校正
//    int32 mCallTimes;
//    int32    mGridNum;
//    int32 mGrids[MAX_ROUTES];
//
//    SWorldPos mFirstCanGoPos;
//    int32 mDistance;
//    int32 curStep;
//
//public:
//    PathFinder( GameStage* owner,const char* filename, uint32& mx, uint32& mz);
//    virtual ~PathFinder();
//    void Reset(int32 startz,int32 endz);
//
//    //前两个参数为输入,3/4参数为输出,
//    bool FindPath( SWorldPos* startPt, SWorldPos* endPos,SWorldPos* posNode,int32& numNode, int32 nLevel, bool bLine = false,int32 maxRoute = MAX_ROUTES);
//    bool IsCanGo(const SWorldPos& pos, const int32 nLevel);
//
//private:
//    void ReadNavMap( const char* filename, uint32& mx, uint32& mz);
//    void InitEightDirections();
//
//    bool IsCanGo( const int32 state, const int32 nDriverLevel );
//    bool IsStraightLine( float mAStarBeginPtx, float mAStarBeginPty, float mAStarEndPtx, float mAStarEndPty,bool edit, int32 nLevel);
//
//    uint16 Distance     ( const uint32 zx                            );
//    uint16 RealDistance ( const uint32 zxFirst,const uint32 zxSecond );
//    int32  LEFT         ( int32 k );
//    int32  RIGHT        ( int32 k );
//    int32  PARENT       ( int32 k );
//    bool   NOTEMPTY_UP  ( int32 k );
//    bool   NOTEMPTY_DOWN( int32 k );
//    void   SwapHeap     ( const int32 k1, const int32 k2 );
//    void   InsertNodeToHeap(uint16 node);
//    void   RemoveRootFromHeap();
//    
//    //VOID EditAStarPath(FLOAT startPtx,FLOAT startPty,SWorldPos* posNode,int32& numNode);
//    void   EditAStarPathOpt(FLOAT startPtx,FLOAT startPty,SWorldPos* posNode,int32& numNode, int32 nLevel);
//    void   PackRoute( SWorldPos* posNode, int32& numNode, int32 nLevel);
//    int32  GetDistance(){ return mDistance; } //这个函数必须在FindPath后调用
//};
//
////////////////////////////////////////////////////////////////////////////
////inline
//inline int32 PathFinder::LEFT(int32 k)
//{ return k << 1; }
//
//inline int32 PathFinder::RIGHT(int32 k)
//{ return (k << 1) + 1; }
//
//inline int32 PathFinder::PARENT(int32 k)
//{ return (k >> 1); }
//
//inline bool PathFinder::NOTEMPTY_UP(int32 k)
//{ return k != 0; }
//
//inline bool PathFinder::NOTEMPTY_DOWN(int32 k)
//{ return k <= mLastHeapLeaf; }
//
//inline void PathFinder::SwapHeap(const int32 k1, const int32 k2)
//{
//    uint16 tmp = mHeap[k1];
//    mHeap[k1] = mHeap[k2];
//    mHeap[k2] = tmp;
//}
//
//inline uint16 PathFinder::RealDistance(const uint32 zxFirst,const uint32 zxSecond)
//{ //mWidth不能保证为2^
//    return (uint16)( ( abs( (int32) (zxFirst & (mGridCX-1)) - (int32) (zxSecond & (mGridCX-1)) ) + abs( (int32)(zxFirst / mGridCX) - (int32) (zxSecond / mGridCX) ) ));
//}
//
//#endif // __SERVERCOMMON_PATHFINDER_H__
