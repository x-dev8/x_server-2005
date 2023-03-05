/********************************************************************
    Filename:    AstarPathFind.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#pragma once

/*===============================================================
Exampla:
bool Possible(short x,short y) { if (x<0||y<0||x>=mapw||y>=maph) return false; return map[y][x].MoveAble; }
--begin
CAstarPathFind PathFind(mapw,maph,Possible);
PathFind.FindPath(startx,starty,endx,endy);
--end
Point PosXY[500];char PosR[500];
PathFind.GetPosPath(&PosXY,500);
PathFind.GetDirPath(&PosR,500);
//清在moveable函数中判断 坐标范围

===============================================================*/
#define COST_MAX 30000
#define tile_pos(x,y) (((ADWORD)y<<16)|x)
#define tile_x(pos)   (pos&0xffff)
#define tile_y(pos)   (pos>>16)
#define CONST_SHORTFINDLENGTH 100*2
#define CONST_SHORTFINDINTERVAL 1

#include <windows.h>

typedef unsigned long ADWORD;
class CAstarPathFind
{
public:
	CAstarPathFind( int nMapWidth, int nMapHeight, bool (*MoveCheck)(short x, short y) )
    { 
        Init(); 
        Create(nMapWidth,nMapHeight,MoveCheck); 
    }
	CAstarPathFind()
    { 
        Init(); 
    }
	~CAstarPathFind()
    { 
        Release(); 
    }
protected:
	void Init();

	struct TAstarNode
	{
		ADWORD Pos;         // 该点的坐标(16,16)的模式保存(y,x)
		short ActualCost;   // 保存从起点到该节点的实际开销
		short EstimateCost; // 保存此点的估价开销
		short SumCost;      // 上面两者之和
		TAstarNode *Father; // 此点的父节点
		TAstarNode *Prev;   // 在Open或者Next中的上一个节点
		TAstarNode *Next;   // 在Open或者Next链表中的下一个节点
		char Modified;      // 该节点是否被修改过，记录而备清除1空,2 Open,4 Close
		short DirWalked;    // 有字节点的方向(未用)
		short DirFrom;      // 从哪个方向来的(未用)
	};
	TAstarNode **Node;      // 对应地图中每个节点
	TAstarNode *Open;       // 保存没有处理的按估计值排序的节点
	TAstarNode *Close;      // 保存处理过的节点
	TAstarNode **Modify;    // 保存修改过的节点
	int height;             // 地图的高度
	int width;              // 地图的宽度
	ADWORD MaxSize;            // 最大面积即height*width
	ADWORD ModifyPoint;        // Modify数组的指针
	ADWORD OpenCount;          // Open队列中的节点数目
	ADWORD CloseCount;         // Close队列里面的节点数目
	ADWORD OpenLimited;        // Open队列最多节点数目
	ADWORD CloseLimited;       // Close队列最多节点数目
	short DirMask;             // 要搜索方向的标志，0-7位为从上开始顺时针七个方向
	ADWORD MinPos;             // 终点或最接近终点的节点
	short TargetX;             // 终点坐标
	short TargetY;            
	bool (*MoveAble)(short x,short y);             // 检查地图是否可以移动函数指针
	char AddToOpenQueue(TAstarNode *node);         // 将节点排序加入Open队列
	char GetFromOpenQueue();                       // 从Open队列取出最小的并放入Close队列
	char PopCloseStack();                          // 取出Close队列中的节点
	void ClearModified();                          // 清除所有搜索记录
	char TryTile(short x,short y,TAstarNode *Father,char FromDir);
	inline const short JudgeCost(short,short,short,short) const;
public:
	enum
	{
		END	= 0xFFFFFFF
	};
	int Create(int map_w,int map_h,bool (*MoveCheck)(short x,short y));
	int Release();
	virtual int FindPath(short startx,short starty,short endx,short endy);
    virtual int FindPathShort(short startx,short starty,short endx,short endy);
	int GetPosPath(short *pstPosXY,int maxpos);
	int GetDirPath(char *Dirs,int maxpos);
	int GetPathLengh(){ return GetPosPath(NULL,0); }

	void SetMapCheck(bool (*MapCheck)(short,short)){ MoveAble=MapCheck; }
    static DWORD m_dwShortFindStartTime;
};