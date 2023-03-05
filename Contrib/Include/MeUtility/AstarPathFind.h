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
//����moveable�������ж� ���귶Χ

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
		ADWORD Pos;         // �õ������(16,16)��ģʽ����(y,x)
		short ActualCost;   // �������㵽�ýڵ��ʵ�ʿ���
		short EstimateCost; // ����˵�Ĺ��ۿ���
		short SumCost;      // ��������֮��
		TAstarNode *Father; // �˵�ĸ��ڵ�
		TAstarNode *Prev;   // ��Open����Next�е���һ���ڵ�
		TAstarNode *Next;   // ��Open����Next�����е���һ���ڵ�
		char Modified;      // �ýڵ��Ƿ��޸Ĺ�����¼�������1��,2 Open,4 Close
		short DirWalked;    // ���ֽڵ�ķ���(δ��)
		short DirFrom;      // ���ĸ���������(δ��)
	};
	TAstarNode **Node;      // ��Ӧ��ͼ��ÿ���ڵ�
	TAstarNode *Open;       // ����û�д���İ�����ֵ����Ľڵ�
	TAstarNode *Close;      // ���洦����Ľڵ�
	TAstarNode **Modify;    // �����޸Ĺ��Ľڵ�
	int height;             // ��ͼ�ĸ߶�
	int width;              // ��ͼ�Ŀ��
	ADWORD MaxSize;            // ��������height*width
	ADWORD ModifyPoint;        // Modify�����ָ��
	ADWORD OpenCount;          // Open�����еĽڵ���Ŀ
	ADWORD CloseCount;         // Close��������Ľڵ���Ŀ
	ADWORD OpenLimited;        // Open�������ڵ���Ŀ
	ADWORD CloseLimited;       // Close�������ڵ���Ŀ
	short DirMask;             // Ҫ��������ı�־��0-7λΪ���Ͽ�ʼ˳ʱ���߸�����
	ADWORD MinPos;             // �յ����ӽ��յ�Ľڵ�
	short TargetX;             // �յ�����
	short TargetY;            
	bool (*MoveAble)(short x,short y);             // ����ͼ�Ƿ�����ƶ�����ָ��
	char AddToOpenQueue(TAstarNode *node);         // ���ڵ��������Open����
	char GetFromOpenQueue();                       // ��Open����ȡ����С�Ĳ�����Close����
	char PopCloseStack();                          // ȡ��Close�����еĽڵ�
	void ClearModified();                          // �������������¼
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