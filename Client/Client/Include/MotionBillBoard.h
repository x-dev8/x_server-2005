#pragma once
#include <MeRTLibs.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>

enum FirstEvent
{
	FRIST_FIGHT_OPERATE = 0
	,FRIST_FIGHT_SKILLLINK
	,FRIST_FIGHT_BACKATTACK
	,FRIST_DUTY
	,FRIST_DUTY_HELP
	,FRIST_COLLECT
	,FRIST_COMPOUND
	,FRIST_SKILL
	,FRIST_ECONOMY_SYSTEM			//第一次点npc
	,BIRTHDAY
	,FRIST_COUNT
};

enum
{
	COM_1	= 1 << 0,
	COM_2	= 1 << 1,
	COM_3	= 1 << 2,
	COM_4	= 1 << 3,
	COM_5	= 1 << 4,
	COM_6	= 1 << 5,
	COM_7	= 1 << 6,
	COM_8	= 1 << 7,
	COM_9	= 1 << 8
};
template<class T,class N>
double addition(T a1,N a2)
{
	return ((double)a1+(double)a2);
}

template<class T,class N>
double multiplication(T a1,N a2)
{
	return ((double)a1*(double)a2);
}

class SpriteIcon : public MeCommonAllocObj<SpriteIcon>
{
public:
	SpriteIcon(const char* cImgPath,int iWidth,int iFrameCounts,int iSpeed);
	~SpriteIcon();
	static RECT GetRectFromImg(int PicWidth,int idx,int lineCounts = 4);
	void DrawSprite(POINT pt);
protected:
	DWORD	dwNowTime;
	int index;
	int _width;
	int _FrameCounts;
	int _iSpeed;
	int iPicImg;
};

class CMotionBillBoard
{
public:
	CMotionBillBoard(void);
	~CMotionBillBoard(void);
	BOOL MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	void BillBoardProcess();
	std::string	GetXML_string(const char* path,const char* value,const char* theData);
	int	 GetXML_int(const char* path,const char* value,const char* theData);
	double GetXML_double(const char* path,const char* value,const char* theData);
	void SetTipCounts(FirstEvent eFtet);
	void SetSpritePlay(bool bshow);
	std::string GetTipString(FirstEvent eFtet);
	void SaveResult();
	void	getFirstInfoFromServer(unsigned long firsInf);
	BOOL MouseInFirstTip();
	BOOL MouseInFirstTip2();

	void ShowBirthdayTip();

	SpriteIcon* pSprite;
protected:
	POINT	ptSrc,ptSrcBkup;
	POINT	ptDst;
	POINT	ptTipPos;
	POINT	ptVPos;
	RECT		DstRct;
	bool bShow;
	bool bMouseDown;
	bool bNeedtoSave;
	int iflySpeed;
	int iSpeedStep;
	FirstEvent	eNowEvent;
	DWORD dwNowTime;
	DWORD dwStringColor;
	int FirstEventArray[FRIST_COUNT];
	std::string str;
	std::string TipString[FRIST_COUNT];

	// whu [6/20/2008]
	DWORD dwHelpFlag;

	bool _bShowBirTip;
	SpriteIcon* pBirthdaySprite;
};

extern CMotionBillBoard* GetBillBoard();