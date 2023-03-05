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
	OpenLimited = 100*50;			// Open�������ڵ���Ŀ
	CloseLimited = 100*100L;		// Close�������ڵ���Ŀ
	DirMask = 0xff;					// Ҫ��������ı�־��0-7λΪ���Ͽ�ʼ˳ʱ���߸�����
	MinPos = 0;
	TargetX = TargetY = 0;
	MoveAble = NULL;
}

// ������ڵ������, ������Ŀ�ĵع��۾����������
char CAstarPathFind::AddToOpenQueue(TAstarNode *node)
{
	ADWORD i;
	short f=node->SumCost;
	register TAstarNode *p,*b;
	node->Modified|=2;    // ��¼Open��־
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

// ����Ŀ�ĵع�������ķ���������
char CAstarPathFind::GetFromOpenQueue()
{
	TAstarNode *BestChoice=Open;
	if (!Open) return -1;
	Open=Open->Next;
	if (Open) Open->Prev=NULL;
	if (BestChoice->Modified&4) return -2; // �Ѿ���Close����
	BestChoice->Next=Close;
	BestChoice->Prev=NULL;
	BestChoice->Modified&=5;    // ���Open��־
	BestChoice->Modified|=4;    // ����Close��־
	if (Close) Close->Prev=BestChoice;
	Close=BestChoice;
	OpenCount--;
	CloseCount++;
	return 0;
}
// �ͷ�ջ���ڵ�
char CAstarPathFind::PopCloseStack()
{
	if (Close) { 
		Close->Modified&=3;        // ���Close��־
		Close=Close->Next;
		if (Close) Close->Prev=NULL;
		CloseCount--; 
		return 0; 
	}
	return -1;
}
// ��ԭ�޸Ĺ������нڵ�
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

// ������һ���ƶ��� x,y ���з�
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
        return 1;            // �����ͼ�޷�ͨ�����˳�

	node=&Node[y][x];
	ActualCost=Father->ActualCost+1;        // ʵ��ֵ����
	if (ActualCost>=node->ActualCost) 
        return 1;

	if (node->Modified&2)                    // ��Open���о����
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
    {        // ��Close���о����
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
		if (!(node->Modified&1)) Modify[ModifyPoint++]=node; // ��¼����޸Ĺ��ĵ��Ի�ԭ
		node->Modified=1;
		node->Father=Father;
		node->DirFrom=FromDir;
		node->ActualCost=ActualCost;
		node->EstimateCost=JudgeCost(x,y,TargetX,TargetY);
		node->SumCost=ActualCost+node->EstimateCost;
		AddToOpenQueue(node);            // ���ڵ����Open����
	}
	return 0;
}

// ·��Ѱ��������
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
		ok=GetFromOpenQueue();        // ȡ��Open���й���ֵ��С�Ľڵ����Close��
		root=Close;                    // �õ��ղ�ȡ���Ľڵ�
		if (ok||root==NULL) 
        { 
            ok=-1; 
            break; 
        }
		x=(short)tile_x(root->Pos);
		y=(short)tile_y(root->Pos);
		if (root->EstimateCost<MinJudge)    // �ҵ�һ���������յ�����ĵ�
        {
			MinJudge=root->EstimateCost, MinPos=root->Pos;
        }
		if (CloseCount>max) 
        {
            max=CloseCount;
        }
		if (x==endx&&y==endy) 
        {
            MinPos=root->Pos,ok=1;    // ����ߵ��յ���
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
                }    // �������ͨ·���Close��ȡ��
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

// ·��Ѱ��������
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
        ok=GetFromOpenQueue();        // ȡ��Open���й���ֵ��С�Ľڵ����Close��
        root=Close;                    // �õ��ղ�ȡ���Ľڵ�
        if (ok||root==NULL) 
        { 
            ok=-1; 
            break; 
        }
        x=(short)tile_x(root->Pos);
        y=(short)tile_y(root->Pos);
        if (root->EstimateCost<MinJudge)    // �ҵ�һ���������յ�����ĵ�
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
            MinPos=root->Pos,ok=1;    // ����ߵ��յ���
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
                }    // �������ͨ·���Close��ȡ��
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
