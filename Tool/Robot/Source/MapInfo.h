#pragma once
#include "../Resource/resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "atlimage.h"
#include "GdiPlusHeaders.h"

//#include "CxImage/ximage.h"


#include <list>
#include <string>
using namespace std;


enum EnumType
{
	Enum_Me = 0,
	Enum_Npc,
	Enum_Enemy,
	Enum_Player,

	Enum_End,
};

static char* s_pszFile[] = 
{
	".\\Data\\Icon\\DuiYou.tga",
	".\\Data\\Icon\\Npc.tga",
	".\\Data\\Icon\\Enemy.tga",
	".\\Data\\Icon\\MoShengRen.tga",	
};

// MapInfo dialog
class BaseRobot;
struct PlayerInfo;
class MapInfo : public CDialog
{
	DECLARE_DYNAMIC(MapInfo)

public:
	MapInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~MapInfo();

// Dialog Data
	enum { IDD = IDD_DIALOG_MAP };

	void SetBotID(int nBotID){m_nBotID = nBotID;}
	
	bool IsShow(){return m_bShow;}
	void SetShow(bool bShow){m_bShow = bShow;}

	void InitInformation();
	void UpdateInformation(int nBotID);
	void ShowMapBmp();

	string SelectMapFile(int nMapID);

private:
	void ShowPlayerList(int nType);

	//void ShowPlayerInfo(CDC *pDC, list<PlayerInfo>& listPlayer, CxImage& xImage);

	void MoveToPosition(int nPosX, int nPosY);

private:
	int m_nBotID; //»úÆ÷ÈËID

	bool m_bShow;
	int m_nLastShowMapID;

	int m_nWidth;
	int m_nHeight;
	CPoint m_xPoint;

	CImage m_xMapImage;

	//CxImage m_xCxImage[Enum_End];
	bool m_bLoad[Enum_End];

	double m_dScaleX;
	double m_dScaleY;

	typedef list<PlayerInfo>::iterator PlayIter;



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listPlayer;
	CStatic m_staticInfo;
	CStatic m_staticMap;
	BOOL m_RadioType;
	afx_msg void OnBnClickedRadioNPC();
	afx_msg void OnBnClickedRadioEnemy();
	afx_msg void OnBnClickedRadioPlayer();
	afx_msg void OnBnClickedButtonAutoMove();
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnStnClickedStaticBigmap();
	CEdit m_editPosX;
	CEdit m_editPosY;
	afx_msg void OnNMClickListPlayer(NMHDR *pNMHDR, LRESULT *pResult);
};
