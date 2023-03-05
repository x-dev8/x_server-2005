// MapInfo.cpp : implementation file
//
#pragma warning( push, 0  )

#include "stdafx.h"
#include "MapInfo.h"
#include "Bot.h"
#include "BotApplication.h"
#include "GameBot.h"
#include "Client.h"

// MapInfo dialog

IMPLEMENT_DYNAMIC(MapInfo, CDialog)

MapInfo::MapInfo(CWnd* pParent /*=NULL*/)
	: CDialog(MapInfo::IDD, pParent)
	, m_RadioType(FALSE)
{
	m_nBotID = -1;
	m_bShow = false;

	m_nLastShowMapID = -1;

	m_dScaleX = 0.0;
	m_dScaleY = 0.0;
	m_xPoint.x = 32;
	m_xPoint.y = 24;
}

MapInfo::~MapInfo()
{
}

void MapInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listPlayer);
	DDX_Control(pDX, IDC_STATIC_INFO, m_staticInfo);
	DDX_Control(pDX, IDC_STATIC_BIGMAP, m_staticMap);
	DDX_Radio(pDX, IDC_RADIO1, m_RadioType);
	DDX_Control(pDX, IDC_EDIT1, m_editPosX);
	DDX_Control(pDX, IDC_EDIT2, m_editPosY);
}


BEGIN_MESSAGE_MAP(MapInfo, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &MapInfo::OnBnClickedRadioNPC)
	ON_BN_CLICKED(IDC_RADIO2, &MapInfo::OnBnClickedRadioEnemy)
	ON_BN_CLICKED(IDC_RADIO3, &MapInfo::OnBnClickedRadioPlayer)
	ON_BN_CLICKED(IDC_BUTTON1, &MapInfo::OnBnClickedButtonAutoMove)
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_STN_CLICKED(IDC_STATIC_BIGMAP, &MapInfo::OnStnClickedStaticBigmap)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &MapInfo::OnNMClickListPlayer)
END_MESSAGE_MAP()


// MapInfo message handlers
BOOL MapInfo::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void MapInfo::InitInformation()
{
	RECT rectlist;
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	int nWidth = 0;
	int iIndex = 0;
	/////////////////////////////////////////////////////////////////////
	m_listPlayer.SetExtendedStyle(dwStyle);

	m_listPlayer.GetClientRect(&rectlist);
	nWidth = rectlist.right - rectlist.left;

	m_listPlayer.InsertColumn(iIndex++, _T("   名称"), 0, (35 * nWidth / 100));
	m_listPlayer.InsertColumn(iIndex++, _T("   坐标"), 0, (65 * nWidth / 100));

	m_staticInfo.SetWindowText("NPC列表");

	//显示区域大小
	CRect rect;   
	m_staticMap.GetClientRect(&rect); 
	m_nWidth = rect.Width();
	m_nHeight = rect.Height();

	//加载图标
	//for (int i = 0; i < Enum_End; ++i)
	//{
	//	m_bLoad[i] = m_xCxImage[i].Load(s_pszFile[i], CXIMAGE_FORMAT_TGA);
	//}
}

void MapInfo::UpdateInformation(int nBotID)
{
	SetBotID(nBotID);

	ShowPlayerList(m_RadioType);
	
	////不能放在InitInformation里计算, 调用的时候InitInformation 窗口还没有显示
	//static bool s_bInit = false;
	//if (!s_bInit && m_bShow)
	//{
	//	//计算起始坐标
	//	RECT rect1;
	//	this->ClientToScreen(&rect1);
	//	RECT rect2;
	//	m_staticMap.ClientToScreen(&rect2);
	//	m_xPoint.x = rect2.left - rect1.left;
	//	m_xPoint.y = rect2.top - rect1.top;

	//	s_bInit = true;
	//}
}

void MapInfo::OnBnClickedRadioNPC()
{
	// TODO: Add your control notification handler code here

	m_staticInfo.SetWindowText("NPC列表");
	m_RadioType = 0;
	ShowPlayerList(m_RadioType);
}

void MapInfo::OnBnClickedRadioEnemy()
{
	// TODO: Add your control notification handler code here
	m_staticInfo.SetWindowText("怪物列表");
	m_RadioType = 1;
	ShowPlayerList(m_RadioType);

}

void MapInfo::OnBnClickedRadioPlayer()
{
	// TODO: Add your control notification handler code here
	m_staticInfo.SetWindowText("玩家列表");
	m_RadioType = 2;

	ShowPlayerList(m_RadioType);
}


void MapInfo::ShowPlayerList(int nType)
{
	BaseRobot *pBot = theApp.gBotApplication.GetBot(m_nBotID);
	if (pBot == NULL || pBot->GetBotState() != State_Play)
	{
		m_listPlayer.DeleteAllItems();
		return;
	}

	PlayIter iter;
	PlayIter end;

	switch (nType)
	{
	case 0:
		iter = pBot->m_listNPCList.begin();
		end = pBot->m_listNPCList.end();
		break;

	case 1:
		iter = pBot->m_listMonsterList.begin();
		end = pBot->m_listMonsterList.end();
		break;

	case 2:
		iter = pBot->m_listPlayerList.begin();
		end = pBot->m_listPlayerList.end();
		break;

	default:
		return;
	}

	int nCount = m_listPlayer.GetItemCount();
	int i = 0;
	for ( ; iter != end; ++iter, ++i)
	{		
		if (i < nCount)
		{
			m_listPlayer.SetItemText(i, 0, (*iter).szName);
		}
		else
		{
			m_listPlayer.InsertItem(i, (*iter).szName);
		}
		
		theApp.SetListItemText(m_listPlayer, i, 1, "%d,%d", (int)(*iter).m_vPos.x, (int)(*iter).m_vPos.y);
	}

	for (int j = nCount - 1; j >= i;  --j)
	{
		m_listPlayer.DeleteItem(j);
	}
}

void MapInfo::ShowMapBmp()
{	
	BaseRobot *pBot = theApp.gBotApplication.GetBot(m_nBotID);
	if (pBot == NULL || pBot->GetBotID() != 0 || pBot->GetBotState() != State_Play)
	{		
		m_nLastShowMapID = -1;
		return;
	}

	//判断地图是否相同
	if (pBot->GetMapID() != m_nLastShowMapID)
	{	
		//计算地图缩放比例
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(pBot->GetMapID());			
	
		if (pMapData != NULL && pMapData->Row != 0 && pMapData->Column != 0)
		{			
			m_dScaleX = m_nWidth * 100 / pMapData->Row * CHUNK_SIZE;
			m_dScaleY = m_nHeight * 100 / pMapData->Column * CHUNK_SIZE;	
		}		
		////加载图片
		string strFile = SelectMapFile(pBot->GetMapID());
		HRESULT hResult;
		if ((hResult = m_xMapImage.Load(strFile.c_str())))
		{				
			return;
		}	
		m_nLastShowMapID = pBot->GetMapID();
	}

	CDC *pDC = GetDC();
	////画地图	
	m_xMapImage.TransparentBlt(pDC->GetSafeHdc(), m_xPoint.x, m_xPoint.y, m_nWidth, m_nHeight, 0, 0, m_xMapImage.GetWidth(), m_xMapImage.GetHeight());	
	
	////画自己
	//if (m_bLoad[Enum_Me])
	//{	
	//	m_xCxImage[Enum_Me].Draw(pDC->GetSafeHdc(), m_xPoint.x - m_xCxImage[Enum_Me].GetWidth() / 2 + pBot->GetPosX() * m_dScaleX / 100, m_xPoint.y - m_xCxImage[Enum_Me].GetHeight() / 2 + (m_nHeight - pBot->GetPosY() * m_dScaleY / 100), 
	//		m_xCxImage[Enum_Me].GetWidth(),  m_xCxImage[Enum_Me].GetHeight());
	//}

	////画NPC
	//if (m_bLoad[Enum_Npc])
	//{
	//	ShowPlayerInfo(pDC, pBot->m_listNPCList, m_xCxImage[Enum_Npc]);
	//}

	////怪物
	//if (m_bLoad[Enum_Enemy])
	//{
	//	ShowPlayerInfo(pDC, pBot->m_listMonsterList, m_xCxImage[Enum_Enemy]);
	//}

	////玩家
	//if (m_bLoad[Enum_Player])
	//{
	//	ShowPlayerInfo(pDC, pBot->m_listPlayerList, m_xCxImage[Enum_Player]);
	//}	
	////////////////////////////////////////////////////////
	ReleaseDC(pDC);
}

void MapInfo::OnBnClickedButtonAutoMove()
{
	// TODO: Add your control notification handler code here
	
	CString strPosX = "";
	CString strPosY = "";
	m_editPosX.GetWindowText(strPosX);
	m_editPosY.GetWindowText(strPosY);
	if (strPosX.IsEmpty() || strPosY.IsEmpty())
	{
		return;
	}
	
	MoveToPosition(atoi(strPosX.GetBuffer()), atoi(strPosY.GetBuffer()));	
}

void MapInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages

	ShowMapBmp();
}

void MapInfo::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default
	if (nID == SC_CLOSE || nID == SC_MINIMIZE)
	{	
		m_bShow = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}

string MapInfo::SelectMapFile(int nMapID)
{
	if (nMapID < 0)
	{
		return "";
	}

	static char* s_pszFile = ".\\Data\\MiniMap\\";

	static char szFile[_MAX_PATH] = "";
	memset(szFile, 0, sizeof(szFile));
	sprintf_s(szFile, sizeof(szFile) - 1, "%s%d.bmp", s_pszFile, nMapID);

	return szFile;
}

void MapInfo::OnStnClickedStaticBigmap()
{
	// TODO: Add your control notification handler code here
	CPoint xPoint;
	GetCursorPos(&xPoint);

	RECT rect;
	m_staticMap.GetClientRect(&rect);
	m_staticMap.ClientToScreen(&rect);

	int nPosX = (xPoint.x - rect.left) * 100 / m_dScaleX;
	int nPosY = (m_nHeight - xPoint.y + rect.top) * 100 / m_dScaleY;

	MoveToPosition(nPosX, nPosY);
	
	theApp.SetText(m_editPosX, "%d", nPosX);
	theApp.SetText(m_editPosY, "%d", nPosY);
}

void MapInfo::MoveToPosition(int nPosX, int nPosY)
{
	Client *pClient = (Client*) theApp.gBotApplication.GetBot(m_nBotID);
	if (pClient == NULL || pClient->GetBotState() != State_Play)
	{
		return;
	}

	pClient->SetToPositon(nPosX, nPosY);
}

//void MapInfo::ShowPlayerInfo(CDC *pDC, std::list<PlayerInfo> &listPlayer, CxImage &xImage)
//{
//	PlayIter iter = listPlayer.begin();
//	PlayIter end = listPlayer.end();
//
//	for ( ; iter != end; ++iter)
//	{
//		xImage.Draw(pDC->GetSafeHdc(), m_xPoint.x - xImage.GetWidth() / 2 + (*iter).m_vPos.x * m_dScaleX / 100, m_xPoint.y - xImage.GetHeight() / 2 + m_nHeight - (*iter).m_vPos.y * m_dScaleY / 100, 
//			xImage.GetWidth(),  xImage.GetHeight());
//	}
//}

void MapInfo::OnNMClickListPlayer(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	POSITION pos = m_listPlayer.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_listPlayer.GetNextSelectedItem(pos);
		if (nIndex != -1)
		{
			CString strTemp = m_listPlayer.GetItemText(nIndex, 1);

			string strPoint = strTemp.GetBuffer();
			string::size_type nPos = strPoint.find(",");

			if (nPos != string::npos)
			{
				string strValue = strPoint.substr(0, nPos);
				m_editPosX.SetWindowText(strValue.c_str());
				strValue = strPoint.substr(nPos + 1);
				m_editPosY.SetWindowText(strValue.c_str());
			}
		}
	}

	*pResult = 0;
}

#pragma warning( pop )