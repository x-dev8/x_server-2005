/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\JoinFight.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "JoinFight.h"
#include "NetworkInput.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "PlayerRole.h"
#include "../color_config.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "NpcInfo.h"
#include "ui/NpcChatDialogBox.h"
#include "Common.h"
#include "Ui/NpcTaskDialogBox.h"

extern GAME_STATE	g_GameState;
int g_iShowJoinFightCountDown = 0;	// 如果报名成功g_iShowJoinFightCountDown设为2，切一次地图减1，只要变量大于0显示剩余时间倒计时
CUI_ID_FRAME_JoinFight s_CUI_ID_FRAME_JoinFight;
MAP_FRAME_RUN( s_CUI_ID_FRAME_JoinFight, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_JoinFight, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_JoinFight, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_JoinFight, ID_BUTTON_CancleOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_JoinFight, ID_LIST_ListOnListSelectChange )
CUI_ID_FRAME_JoinFight::CUI_ID_FRAME_JoinFight()
{
	// Member
	m_pID_FRAME_JoinFight = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_LIST_List = NULL;
	m_pID_TEXT_Time = NULL;

}
// Frame
bool CUI_ID_FRAME_JoinFight::OnFrameRun()
{
	if( g_iShowJoinFightCountDown > 0 )
	{
		if( g_GameState != G_MAIN )
		{
			g_iShowJoinFightCountDown = 0;
			return true;
		}
		char buf[256] = {0};
		char szTime[256] = {0};
		int second = m_leftTime - (HQ_TimeGetTime() - m_time) / 1000;
		if (second > 0)
		{
			int minute = second / 60;
			second %= 60;
			if( minute != m_usLastMinute || second != m_usLastSecond )
			{
				if( minute > 0 && second > 0 )
					MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s%d%s", minute, theXmlString.GetString(eTimeUnit_Minute), second, theXmlString.GetString(eTimeUnit_Second) );
				else if( minute > 0 )
					MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s", minute, theXmlString.GetString(eTimeUnit_Minute) );
				else if( second > 0 )
					MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s", second, theXmlString.GetString(eTimeUnit_Second) );
				MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eText_JoinFightCountDown), szTime);

				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_SignUpSuccess, buf );

				m_usLastMinute = minute;
				m_usLastSecond = second;
			}
		}
		return true;
	}
	if( !IsVisable() )
		return true;
	if (m_SignUpInfo.size() > 0)
	{
		char buf[256] = {0};
		char szTime[256] = {0};
		int second = m_leftTime - (HQ_TimeGetTime() - m_time) / 1000;
		if (second > 0)
		{
			int minute = second / 60;
			second %= 60;
			if( minute > 0 && second > 0 )
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s%d%s", minute, theXmlString.GetString(eTimeUnit_Minute), second, theXmlString.GetString(eTimeUnit_Second) );
			else if( minute > 0 )
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s", minute, theXmlString.GetString(eTimeUnit_Minute) );
			else if( second > 0 )
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s", second, theXmlString.GetString(eTimeUnit_Second) );
			MeSprintf_s(buf, sizeof(szTime)/sizeof(char) - 1, theXmlString.GetString(eText_JoinFightRemainTime), szTime);
		}
		else
		{
			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eText_JoinFightRemainTime), "0");
		}
		m_pID_TEXT_Time->SetText(buf);
	}
	else
		m_pID_TEXT_Time->SetText("");

	if( IsVisable() )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
		{
			float fMeX,fMeY,fMeZ;			
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
			if( dist > 12.0f )
			{
				SetVisable(false);
			}
		}
	}

	return true;
}
bool CUI_ID_FRAME_JoinFight::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_JoinFight::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_JoinFight )
		return true;

	if( !m_pID_BUTTON_OK->IsEnable() )
		return true;

	OnOK();
	return true;
}
// Button
bool CUI_ID_FRAME_JoinFight::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_JoinFight )
		return false;
	//s_CUI_ID_FRAME_NpcChatDialogBox.CancelScript();
	s_CUI_NpcTaskDialogBox.CloseDialog();
	SetVisable(false);
	return true;
}
// List
void CUI_ID_FRAME_JoinFight::ID_LIST_ListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_JoinFight )
		return;
	if( !m_pID_FRAME_JoinFight )
		return;
	if (pItem == NULL)
		return;
	if (m_SignUpInfo.empty())
		return;

	uint16 level = (uint16)pItem->m_pData;
	bool bCanEnter = true;
	int id = m_pID_LIST_List->GetCurSelIndex();
	if (m_SignUpInfo[id].ustCount >= m_SignUpInfo[id].ustMaxCount)
	{
		bCanEnter = false;
	}

	/*
	 * Author:	2012-8-10 wangshuai
	 * Desc: 	测试战场，先注释掉等级限制
	 */
	/*
	else if (thePlayerRole.GetLevel() < 40)
	{
		bCanEnter = false;
	}
	else if (40 <= thePlayerRole.GetLevel() && thePlayerRole.GetLevel() <= 44 )
	{
		if( level > 44 || level < 40 )
		{
			bCanEnter = false;
		}
	}
	else if (45 <= thePlayerRole.GetLevel() && thePlayerRole.GetLevel() <= 49 )
	{
		if( level > 49 || level < 45 )
		{
			bCanEnter = false;
		}
	}
	else if (50 <= thePlayerRole.GetLevel() && thePlayerRole.GetLevel() <= 54 )
	{
		if( level > 54 || level < 50 )
		{
			bCanEnter = false;
		}
	}
	else	// 玩家大于54级
	{
		if( level <= 54 )
		{
			bCanEnter = false;
		}
	}
	*/

	if( !bCanEnter )
		m_pID_BUTTON_OK->SetEnable(false);
	else
		m_pID_BUTTON_OK->SetEnable(true);
}

// 装载UI
bool CUI_ID_FRAME_JoinFight::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\JoinFight.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\JoinFight.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_JoinFight::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_JoinFight, s_CUI_ID_FRAME_JoinFightOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_JoinFight, s_CUI_ID_FRAME_JoinFightOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_JoinFight, ID_BUTTON_OK, s_CUI_ID_FRAME_JoinFightID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_JoinFight, ID_BUTTON_Cancle, s_CUI_ID_FRAME_JoinFightID_BUTTON_CancleOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_JoinFight, ID_LIST_List, s_CUI_ID_FRAME_JoinFightID_LIST_ListOnListSelectChange );

	m_pID_FRAME_JoinFight = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_JoinFight );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_JoinFight, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_JoinFight, ID_BUTTON_Cancle );
	m_pID_LIST_List = (ControlList*)theUiManager.FindControl( ID_FRAME_JoinFight, ID_LIST_List );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_JoinFight, ID_TEXT_Time );
	assert( m_pID_FRAME_JoinFight );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_LIST_List );

	m_usLastMinute = 0;
	m_usLastSecond = 0;

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_JoinFight::_UnLoadUI()
{
	m_pID_FRAME_JoinFight = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_LIST_List = NULL;
	m_pID_TEXT_Time = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\JoinFight.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_JoinFight::_IsVisable()
{
	if( !m_pID_FRAME_JoinFight )
		return false;
	return m_pID_FRAME_JoinFight->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_JoinFight::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_JoinFight )
		return;
	m_pID_FRAME_JoinFight->SetVisable( bVisable );
}

void CUI_ID_FRAME_JoinFight::OnOK()
{
	if( !m_pID_FRAME_JoinFight )
		return;

	if (m_SignUpInfo.empty())
		return;

	ControlList::S_List* pItem = m_pID_LIST_List->GetCurSelItem();
	if (pItem == NULL)
		return;

	uint16 level = (uint16)pItem->m_pData;
	bool bCanEnter = true;
	int id = m_pID_LIST_List->GetCurSelIndex();
	if (m_SignUpInfo[id].ustCount >= m_SignUpInfo[id].ustMaxCount)
	{
		bCanEnter = false;
	}

	/*
	* Author:	2012-8-10 wangshuai
	* Desc: 	测试战场，先注释掉等级限制
	*/
	/*
	else if (thePlayerRole.GetLevel() < 40)
	{
		bCanEnter = false;
	}
	else if (40 <= thePlayerRole.GetLevel() && thePlayerRole.GetLevel() <= 44 )
	{
		if( level > 44 || level < 40 )
		{
			bCanEnter = false;
		}
	}
	else if (45 <= thePlayerRole.GetLevel() && thePlayerRole.GetLevel() <= 49 )
	{
		if( level > 49 || level < 45 )
		{
			bCanEnter = false;
		}
	}
	else if (50 <= thePlayerRole.GetLevel() && thePlayerRole.GetLevel() <= 54 )
	{
		if( level > 54 || level < 50 )
		{
			bCanEnter = false;
		}
	}
	else	// 玩家大于54级
	{
		if( level <= 54 )
		{
			bCanEnter = false;
		}
	}

	if( !bCanEnter )
		return;
	*/

	MsgBattleSignUpReq req;
	req.ustMapID = pItem->m_nID;
	req.ustLevel = (uint16)pItem->m_pData;
	req.ustType = m_type;
	GettheNetworkInput().SendMsg( &req );

	//s_CUI_ID_FRAME_NpcChatDialogBox.CancelScript();
	s_CUI_NpcTaskDialogBox.CloseDialog();

	SetVisable(false);
}

struct SignUpInfoSort
{
	bool operator()(const MsgShowBattleSignUpDlg::SignUpInfo& v1, const MsgShowBattleSignUpDlg::SignUpInfo& v2)
	{
		return v1.ustLevel < v2.ustLevel;
	}
};

void CUI_ID_FRAME_JoinFight::Show( MsgShowBattleSignUpDlg* pMsg )
{
	SetVisable(true);
    if(!m_pID_FRAME_JoinFight)
        return;


	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(pMsg->stNpcId);
	if (!pPlayer)
		return;
	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByName(pPlayer->GetName());
	if( !pNpc )
		return;

	m_npcId = pNpc->id;
	m_type = pMsg->uchShowType;

	m_SignUpInfo.clear();
	for (int i = 0; i < MsgShowBattleSignUpDlg::MaxCount; ++i)
	{
		if (pMsg->xSignUpInfo[i].ustMapID != ErrorUnsignedShortID)
			m_SignUpInfo.push_back(pMsg->xSignUpInfo[i]);
	}

	std::sort(m_SignUpInfo.begin(), m_SignUpInfo.end(), SignUpInfoSort());

	Update();

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if ( pMe )
	{
		float fMeX,fMeY,fMeZ;			
		pMe->GetPos( &fMeX, &fMeY, &fMeZ );
		m_vVisiblePos.x = fMeX;
		m_vVisiblePos.y = fMeY;		
	}
}

void CUI_ID_FRAME_JoinFight::OnAck( MsgBattleSignUpAck* pMsg )
{
	switch (pMsg->uchResult)
	{
	case MsgBattleSignUpAck::Success:
		g_iShowJoinFightCountDown = 2;
		break;
	default:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_SignUpSuccess, theXmlString.GetString( 20000 + pMsg->uchResult ) );
		break;
	}
}

void CUI_ID_FRAME_JoinFight::OnUpdateCount( MsgTellBattleSignUpCount* pMsg )
{
	int i=0;
	for ( i = 0; i < m_SignUpInfo.size(); ++i)
	{
		if (m_SignUpInfo[i].ustMapID == pMsg->ustMapID)
		{
			m_SignUpInfo[i].ustCount = pMsg->ustCount;
			m_SignUpInfo[i].nSignUpLeftTime = pMsg->nStartLeftTime;
			break;
		}
	}
	Update(i);
}

void CUI_ID_FRAME_JoinFight::Update(int id/*=-1*/)
{
	if( !m_pID_FRAME_JoinFight )
		return;

	m_pID_LIST_List->Clear();
	m_pID_BUTTON_OK->SetEnable(true);

	if (m_SignUpInfo.empty())
	{
		m_pID_BUTTON_OK->SetEnable(false);
		return;
	}

	m_pID_BUTTON_OK->SetEnable(true);

	if( id < 0 || id >= m_SignUpInfo.size())
		m_leftTime = m_SignUpInfo[0].nSignUpLeftTime;
	else 
		m_leftTime = m_SignUpInfo[id].nSignUpLeftTime;
	m_time = HQ_TimeGetTime();

	int iCurSelIndex = m_pID_LIST_List->GetCurSelIndex();

	char buf[256];
	for (int i = 0; i < m_SignUpInfo.size(); ++i)
	{
		ControlList::S_List stItem;
		int stringid = m_npcId*100 + i;
		D3DCOLOR color = 0;
		bool bCanSel = true;

		MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%s%d/%d", theXmlString.GetString(stringid), m_SignUpInfo[i].ustCount, m_SignUpInfo[i].ustMaxCount);
		if (m_SignUpInfo[i].ustCount >= m_SignUpInfo[i].ustMaxCount)
		{
			color = D3DCOLOR_XRGB(255, 0, 0);
			bCanSel = false;
		}
		// 玩家不能选和自己等级不付的房间
		else
		{
			if (thePlayerRole.GetLevel() < 40)
			{
				MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%s", theXmlString.GetString(stringid));
				color = D3DCOLOR_XRGB(139, 139, 139);
				bCanSel = false;
			}
			else if (40 <= thePlayerRole.GetLevel() && thePlayerRole.GetLevel() <= 44 )
			{
				if( m_SignUpInfo[i].ustLevel > 44 || m_SignUpInfo[i].ustLevel < 40 )
				{
					MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%s", theXmlString.GetString(stringid));
					color = D3DCOLOR_XRGB(139, 139, 139);
					bCanSel = false;
				}
			}
			else if (45 <= thePlayerRole.GetLevel() && thePlayerRole.GetLevel() <= 49 )
			{
				if( m_SignUpInfo[i].ustLevel > 49 || m_SignUpInfo[i].ustLevel < 45 )
				{
					MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%s", theXmlString.GetString(stringid));
					color = D3DCOLOR_XRGB(139, 139, 139);
					bCanSel = false;
				}
			}
			else if (50 <= thePlayerRole.GetLevel() && thePlayerRole.GetLevel() <= 54 )
			{
				if( m_SignUpInfo[i].ustLevel > 54 || m_SignUpInfo[i].ustLevel < 50 )
				{
					MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%s", theXmlString.GetString(stringid));
					color = D3DCOLOR_XRGB(139, 139, 139);
					bCanSel = false;
				}
			}
			else	// 玩家大于54级
			{
				if( m_SignUpInfo[i].ustLevel <= 54 )
				{
					MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%s", theXmlString.GetString(stringid));
					color = D3DCOLOR_XRGB(139, 139, 139);
					bCanSel = false;
				}
			}
		}
		if( iCurSelIndex == i )
		{
			if( bCanSel )
				m_pID_BUTTON_OK->SetEnable(true);
			else
				m_pID_BUTTON_OK->SetEnable(false);
		}
		stItem.SetData(buf, m_SignUpInfo[i].ustMapID, (void*)m_SignUpInfo[i].ustLevel, color);
		m_pID_LIST_List->AddItem(&stItem);
	}
}