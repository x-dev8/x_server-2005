/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\TeamBattleShowTeamInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TeamBattleShowTeamInfo.h"
#include "TeamBattleRequest.h"
#include "NetworkInput.h"
#include "MessageDefine.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "../color_config.h"
#include "ShowScreenText.h"
#include "MessageBox.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "Common.h"

CUI_ID_FRAME_TeamBattleShowTeamInfo s_CUI_ID_FRAME_TeamBattleShowTeamInfo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TeamBattleShowTeamInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TeamBattleShowTeamInfo, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleShowTeamInfo, ID_BUTTON_BackOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleShowTeamInfo, ID_BUTTON_TeamOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_NameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_LvlOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_AllOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_JobOnListSelectChange )
//MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_GangOnListSelectChange )
CUI_ID_FRAME_TeamBattleShowTeamInfo::CUI_ID_FRAME_TeamBattleShowTeamInfo()
{
	// Member
	m_pID_FRAME_TeamBattleShowTeamInfo = NULL;
	m_pID_PICTURE_BackWall = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_BUTTON_Team = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_LIST_Lvl = NULL;
	m_pID_LIST_All = NULL;
	m_pID_TEXT_LastTime = NULL;
	m_pID_TEXT_NameZ = NULL;
	m_pID_TEXT_LvlZ = NULL;
	m_pID_TEXT_JobZ = NULL;
	//m_pID_TEXT_GangZ = NULL;
	m_pID_LIST_Job = NULL;
	//m_pID_LIST_Gang = NULL;

}
// Frame
bool CUI_ID_FRAME_TeamBattleShowTeamInfo::OnFrameRun()
{
	if(m_leftTime > 0 && m_leftTime < 4000000000)
	{
		m_leftTime -= theHeroGame.GetFrameElapsedTime()*1000;

		if(m_leftTime > 4000000000)
		{
			m_leftTime = 0;
		}
	}
	else
	{
		m_leftTime = 0;

		if(m_MsgSendTimeCount<5000)
		{
			m_MsgSendTimeCount += theHeroGame.GetFrameElapsedTime()*1000;
		}
		else
		{
			if(IsVisable())
			{
				MsgQueryBattleSignUpTimeReq msg;
				msg.uchType = 2;
				msg.ustMapID = m_SignInfo.ustMapID;

				if(m_Timestate)
				{
					msg.bIsPassSignTime = true;
				}
				else
				{
					msg.bIsPassSignTime = false;
				}

				GettheNetworkInput().SendMsg( &msg );
			}
			m_MsgSendTimeCount = 0;
		}
	}	

	if( IsVisable() )
	{
		char timeshow[256];

		char szTime[128] = {0};
		int nHour = m_leftTime/3600000;
		int nMin = (m_leftTime - nHour * 3600000)/60000;
		int nSecond = (m_leftTime - nHour * 3600000 - nMin * 60000)/1000;
		if(nHour > 0)
			MeSprintf_s(szTime,sizeof(szTime)/sizeof(char) - 1,"%d%s%d%s%d%s",
			nHour,theXmlString.GetString(eTimeUnit_Hour),nMin,theXmlString.GetString(eTimeUnit_Minute)
			,nSecond,theXmlString.GetString(eTimeUnit_Second));
		else if(nMin > 0)
			MeSprintf_s(szTime,sizeof(szTime)/sizeof(char) - 1,"%d%s%d%s",nMin,theXmlString.GetString(eTimeUnit_Minute)
			,nSecond,theXmlString.GetString(eTimeUnit_Second));
		else if(nSecond >= 0)
			MeSprintf_s(szTime,sizeof(szTime)/sizeof(char) - 1,"%d%s",nSecond,theXmlString.GetString(eTimeUnit_Second));

		if(m_Timestate)
		{
			MeSprintf_s(timeshow, sizeof(timeshow)/sizeof(char) - 1, theXmlString.GetString(eText_JoinFightRemainTime),szTime);
			*m_pID_TEXT_LastTime = timeshow;
		}
		else
		{
			MeSprintf_s(timeshow, sizeof(timeshow)/sizeof(char) - 1, theXmlString.GetString(eText_CampBattleRequestLeftTime),szTime);
			*m_pID_TEXT_LastTime = timeshow;
		}

		if(thePlayerRole.IsTeamBattleInMap())
		{
			SetVisable(false);
		}

		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
		{
			float fMeX,fMeY,fMeZ;			
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
			if( dist > 7.0f )
			{
				SetVisable( false );
			}
		}
	}
	return true;
}
bool CUI_ID_FRAME_TeamBattleShowTeamInfo::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleShowTeamInfo::ID_BUTTON_BackOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_TeamBattleShowTeamInfo )
		return false;
	SetVisable(false);
	s_CUI_ID_FRAME_TeamBattleRequest.SetVisable(true);

	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleShowTeamInfo::ID_BUTTON_TeamOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_TeamBattleShowTeamInfo )
		return false;
	if(thePlayerRole.IsTeamHeader())
	{
		MsgBattleSignUpReq msg;
		msg.ustType = 2;//队伍
		msg.ustMapID = m_SignInfo.ustMapID;//暂时无用
		msg.ustLevel = 0;//无用

		GettheNetworkInput().SendMsg( &msg );

		SetVisable(false);
	}
	else
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_SignUpSuccess, theXmlString.GetString( eText_TeamBattleSignup ) );
	}
	return true;
}
// List
void CUI_ID_FRAME_TeamBattleShowTeamInfo::ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_TeamBattleShowTeamInfo )
		return;
}
// List
void CUI_ID_FRAME_TeamBattleShowTeamInfo::ID_LIST_LvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_TeamBattleShowTeamInfo )
		return;
}
// List
void CUI_ID_FRAME_TeamBattleShowTeamInfo::ID_LIST_AllOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_TeamBattleShowTeamInfo )
		return;
}
// List
void CUI_ID_FRAME_TeamBattleShowTeamInfo::ID_LIST_JobOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_TeamBattleShowTeamInfo )
		return;
}
// List
// void CUI_ID_FRAME_TeamBattleShowTeamInfo::ID_LIST_GangOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// 	if( !m_pID_FRAME_TeamBattleShowTeamInfo )
// 		return;
// }

// 装载UI
bool CUI_ID_FRAME_TeamBattleShowTeamInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TeamBattleShowTeamInfo.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TeamBattleShowTeamInfo.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TeamBattleShowTeamInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TeamBattleShowTeamInfo, s_CUI_ID_FRAME_TeamBattleShowTeamInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TeamBattleShowTeamInfo, s_CUI_ID_FRAME_TeamBattleShowTeamInfoOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleShowTeamInfo, ID_BUTTON_Back, s_CUI_ID_FRAME_TeamBattleShowTeamInfoID_BUTTON_BackOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleShowTeamInfo, ID_BUTTON_Team, s_CUI_ID_FRAME_TeamBattleShowTeamInfoID_BUTTON_TeamOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_Name, s_CUI_ID_FRAME_TeamBattleShowTeamInfoID_LIST_NameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_Lvl, s_CUI_ID_FRAME_TeamBattleShowTeamInfoID_LIST_LvlOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_All, s_CUI_ID_FRAME_TeamBattleShowTeamInfoID_LIST_AllOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_Job, s_CUI_ID_FRAME_TeamBattleShowTeamInfoID_LIST_JobOnListSelectChange );
	//theUiManager.OnListSelectChange( ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_Gang, s_CUI_ID_FRAME_TeamBattleShowTeamInfoID_LIST_GangOnListSelectChange );

	m_pID_FRAME_TeamBattleShowTeamInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TeamBattleShowTeamInfo );
	m_pID_PICTURE_BackWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_PICTURE_BackWall );
	m_pID_BUTTON_Back = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_BUTTON_Back );
	m_pID_BUTTON_Team = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_BUTTON_Team );
	m_pID_LIST_Name = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_Name );
	m_pID_LIST_Lvl = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_Lvl );
	m_pID_LIST_All = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_All );
	m_pID_TEXT_LastTime = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_TEXT_LastTime );
	m_pID_TEXT_NameZ = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_TEXT_NameZ );
	m_pID_TEXT_LvlZ = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_TEXT_LvlZ );
	m_pID_TEXT_JobZ = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_TEXT_JobZ );
	//m_pID_TEXT_GangZ = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_TEXT_GangZ );
	m_pID_LIST_Job = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_Job );
	//m_pID_LIST_Gang = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleShowTeamInfo, ID_LIST_Gang );
	assert( m_pID_FRAME_TeamBattleShowTeamInfo );
	assert( m_pID_PICTURE_BackWall );
	assert( m_pID_BUTTON_Back );
	assert( m_pID_BUTTON_Team );
	assert( m_pID_LIST_Name );
	assert( m_pID_LIST_Lvl );
	assert( m_pID_LIST_All );
	assert( m_pID_TEXT_LastTime );
	assert( m_pID_TEXT_NameZ );
	assert( m_pID_TEXT_LvlZ );
	assert( m_pID_TEXT_JobZ );
	//assert( m_pID_TEXT_GangZ );
	assert( m_pID_LIST_Job );
	//assert( m_pID_LIST_Gang );

	SetVisable(false);
	m_Timestate = 1;
	m_MsgSendTimeCount = 0;

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TeamBattleShowTeamInfo::_UnLoadUI()
{
	m_pID_FRAME_TeamBattleShowTeamInfo = NULL;
	m_pID_PICTURE_BackWall = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_BUTTON_Team = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_LIST_Lvl = NULL;
	m_pID_LIST_All = NULL;
	m_pID_TEXT_LastTime = NULL;
	m_pID_TEXT_NameZ = NULL;
	m_pID_TEXT_LvlZ = NULL;
	m_pID_TEXT_JobZ = NULL;
	//m_pID_TEXT_GangZ = NULL;
	m_pID_LIST_Job = NULL;
	//m_pID_LIST_Gang = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TeamBattleShowTeamInfo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TeamBattleShowTeamInfo::_IsVisable()
{
	if( !m_pID_FRAME_TeamBattleShowTeamInfo )
		return false;
	return m_pID_FRAME_TeamBattleShowTeamInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TeamBattleShowTeamInfo::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_TeamBattleShowTeamInfo )
		return;
	m_pID_FRAME_TeamBattleShowTeamInfo->SetVisable( bVisable );

	m_pID_LIST_All->Clear();
	m_pID_LIST_Name->Clear();
	m_pID_LIST_Lvl->Clear();
	m_pID_LIST_Job->Clear();
	//m_pID_LIST_Gang->Clear();
}

void CUI_ID_FRAME_TeamBattleShowTeamInfo::Show(MsgShowBattleSignUpDlg* ack)
{
	m_SignInfo = ack->xSignUpInfo[0];

	if(ack->xSignUpInfo[0].nSignUpLeftTime!=0)
	{
		m_leftTime = ack->xSignUpInfo[0].nSignUpLeftTime*1000;

		m_MsgSendTimeCount = 0;

		m_Timestate = 1;
	}
}

void  CUI_ID_FRAME_TeamBattleShowTeamInfo::ShowTime(MsgQueryBattleSignUpTimeAck* ack)
{
	if(ack->dwLeftTime == ErrorUnsignedLongID)
	{	
		m_leftTime = 0;
		SetVisable(false);
	}

	m_MsgSendTimeCount = 0;

	m_Timestate = ack->bIsAlreadlySignUp;

	m_leftTime = ack->dwLeftTime;
}

void CUI_ID_FRAME_TeamBattleShowTeamInfo::ShowInfo(MsgQueryBattleTeamInfoAck* pMsg)
{
	char buf[128];
	ControlList::S_List	stItem;

	m_pID_LIST_All->Clear();
	m_pID_LIST_Name->Clear();
	m_pID_LIST_Lvl->Clear();
	m_pID_LIST_Job->Clear();
	//m_pID_LIST_Gang->Clear();

	for(int i=0;i<pMsg->nCount;++i)
	{
		stItem.SetData("");
		m_pID_LIST_All->AddItem(&stItem,NULL,false);

		stItem.SetData(pMsg->xMemberInfo[i].szName);
		m_pID_LIST_Name->AddItem(&stItem,NULL,false);

		MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1,"%d",pMsg->xMemberInfo[i].ustLevel);
		stItem.SetData(buf);
		m_pID_LIST_Lvl->AddItem(&stItem,NULL,false);

		if(pMsg->xMemberInfo[i].uchProfession == EArmType_Mage)
		{
			stItem.SetData(theXmlString.GetString( eProfession_Mage ));
		}
		else if(pMsg->xMemberInfo[i].uchProfession == EArmType_Warrior)
		{
			stItem.SetData(theXmlString.GetString( eProfession_Warrior ));
		}
		else if(pMsg->xMemberInfo[i].uchProfession == EArmType_Assassin)
		{
			stItem.SetData(theXmlString.GetString( eProfession_Assassin ));
		}
		else if(pMsg->xMemberInfo[i].uchProfession == EArmType_Taoist)
		{
			stItem.SetData(theXmlString.GetString( eProfession_Taoist ));
		}
		else if(pMsg->xMemberInfo[i].uchProfession == EArmType_Hunter)
		{
			stItem.SetData(theXmlString.GetString( eProfession_Hunter ));
		}

		m_pID_LIST_Job->AddItem(&stItem,NULL,false);
	}
}