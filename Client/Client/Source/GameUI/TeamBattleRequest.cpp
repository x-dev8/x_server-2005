/********************************************************************
Created by UIEditor.exe
FileName: E:\trunk2\Bin\Client\Data\Ui\TeamBattleRequest.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TeamBattleRequest.h"
#include "NetworkInput.h"
#include "MessageDefine.h"
#include "XmlStringLanguage.h"
#include "ShowScreenText.h"
#include "../color_config.h"
#include "ScreenInfoManager.h"
#include "MessageBox.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "TeamBattleShowTeamInfo.h"
#include "Common.h"

CUI_ID_FRAME_TeamBattleRequest s_CUI_ID_FRAME_TeamBattleRequest;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TeamBattleRequest, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TeamBattleRequest, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleRequest, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleRequest, ID_BUTTON_TeamOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleRequest, ID_LIST_NameAOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleRequest, ID_LIST_NameBOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TeamBattleRequest, ID_LIST_AllOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TeamBattleRequest, ID_BUTTON_ShowTeamOnButtonClick )
CUI_ID_FRAME_TeamBattleRequest::CUI_ID_FRAME_TeamBattleRequest()
{
	// Member
	m_pID_FRAME_TeamBattleRequest = NULL;
	m_pID_PICTURE_BackWall = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Team = NULL;
	m_pID_TEXT_NameA = NULL;
	m_pID_TEXT_NameB = NULL;
	m_pID_LIST_NameA = NULL;
	m_pID_LIST_NameB = NULL;
	m_pID_LIST_All = NULL;
	m_pID_TEXT_LastTime = NULL;
	m_pID_BUTTON_ShowTeam = NULL;

}
// Frame
bool CUI_ID_FRAME_TeamBattleRequest::OnFrameRun()
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
	

	char timeshow[256] = {0};

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
		//*m_pID_TEXT_LastTime = timeshow;
	}
	else
	{
		MeSprintf_s(timeshow, sizeof(timeshow)/sizeof(char) - 1, theXmlString.GetString(eText_CampBattleRequestLeftTime),szTime);
		//*m_pID_TEXT_LastTime = timeshow;
	}
	

	if( IsVisable() )
	{
		// modified, [9/15/2010 zhangjiayi]
		*m_pID_TEXT_LastTime = timeshow;
		int sel = m_pID_LIST_All->GetShowStartHeight();
		m_pID_LIST_NameA->SetShowStartHeight(sel);
		m_pID_LIST_NameB->SetShowStartHeight(sel);

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
bool CUI_ID_FRAME_TeamBattleRequest::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleRequest::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleRequest)
		return false;
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_TeamBattleRequest::ID_BUTTON_TeamOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleRequest)
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
void CUI_ID_FRAME_TeamBattleRequest::ID_LIST_NameAOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_TeamBattleRequest)
		return;
	m_pID_LIST_NameB->SetCurSelIndex(-1);
}
// List
void CUI_ID_FRAME_TeamBattleRequest::ID_LIST_NameBOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_TeamBattleRequest)
		return;
	m_pID_LIST_NameA->SetCurSelIndex(-1);
}
// List
void CUI_ID_FRAME_TeamBattleRequest::ID_LIST_AllOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_TeamBattleRequest)
		return;
}
// Button
bool CUI_ID_FRAME_TeamBattleRequest::ID_BUTTON_ShowTeamOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_TeamBattleRequest)
		return false;
	if(m_pID_LIST_NameA->GetCurSelIndex()!=-1)
	{
		SetVisable(false);
		s_CUI_ID_FRAME_TeamBattleShowTeamInfo.SetVisable(true);

		int sel = m_pID_LIST_NameA->GetCurSelIndex();

		sel = sel*2;

		MsgQueryBattleTeamInfoReq msg;

		msg.ustMapID = m_SignInfo.ustMapID;
		msg.dwTeamID = m_vecTeamID[sel];

		GettheNetworkInput().SendMsg( &msg );
	}
	else if(m_pID_LIST_NameB->GetCurSelIndex()!=-1)
	{
		SetVisable(false);
		s_CUI_ID_FRAME_TeamBattleShowTeamInfo.SetVisable(true);

		int sel = m_pID_LIST_NameB->GetCurSelIndex();

		sel = sel*2+1;

		MsgQueryBattleTeamInfoReq msg;

		msg.ustMapID = m_SignInfo.ustMapID;
		msg.dwTeamID = m_vecTeamID[sel];

		GettheNetworkInput().SendMsg( &msg );
	}

	return true;
}
// 装载UI
bool CUI_ID_FRAME_TeamBattleRequest::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TeamBattleRequest.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TeamBattleRequest.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TeamBattleRequest::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TeamBattleRequest, s_CUI_ID_FRAME_TeamBattleRequestOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TeamBattleRequest, s_CUI_ID_FRAME_TeamBattleRequestOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleRequest, ID_BUTTON_Cancel, s_CUI_ID_FRAME_TeamBattleRequestID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleRequest, ID_BUTTON_Team, s_CUI_ID_FRAME_TeamBattleRequestID_BUTTON_TeamOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleRequest, ID_LIST_NameA, s_CUI_ID_FRAME_TeamBattleRequestID_LIST_NameAOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleRequest, ID_LIST_NameB, s_CUI_ID_FRAME_TeamBattleRequestID_LIST_NameBOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TeamBattleRequest, ID_LIST_All, s_CUI_ID_FRAME_TeamBattleRequestID_LIST_AllOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_TeamBattleRequest, ID_BUTTON_ShowTeam, s_CUI_ID_FRAME_TeamBattleRequestID_BUTTON_ShowTeamOnButtonClick );
	m_pID_FRAME_TeamBattleRequest = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TeamBattleRequest );
	m_pID_PICTURE_BackWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamBattleRequest, ID_PICTURE_BackWall );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleRequest, ID_BUTTON_Cancel );
	m_pID_BUTTON_Team = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleRequest, ID_BUTTON_Team );
	m_pID_TEXT_NameA = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleRequest, ID_TEXT_NameA );
	m_pID_TEXT_NameB = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleRequest, ID_TEXT_NameB );
	m_pID_LIST_NameA = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleRequest, ID_LIST_NameA );
	m_pID_LIST_NameB = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleRequest, ID_LIST_NameB );
	m_pID_LIST_All = (ControlList*)theUiManager.FindControl( ID_FRAME_TeamBattleRequest, ID_LIST_All );
	m_pID_TEXT_LastTime = (ControlText*)theUiManager.FindControl( ID_FRAME_TeamBattleRequest, ID_TEXT_LastTime );
	m_pID_BUTTON_ShowTeam = (ControlButton*)theUiManager.FindControl( ID_FRAME_TeamBattleRequest, ID_BUTTON_ShowTeam );
	assert( m_pID_FRAME_TeamBattleRequest );
	assert( m_pID_PICTURE_BackWall );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Team );
	assert( m_pID_TEXT_NameA );
	assert( m_pID_TEXT_NameB );
	assert( m_pID_LIST_NameA );
	assert( m_pID_LIST_NameB );
	assert( m_pID_LIST_All );
	assert( m_pID_TEXT_LastTime );
	assert( m_pID_BUTTON_ShowTeam );
	
	SetVisable(false);

	m_pID_LIST_All->HaveSelBar(false);

	m_leftTime=0;
	m_Timestate = 1;
	m_MsgSendTimeCount = 0;

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TeamBattleRequest::_UnLoadUI()
{
	m_pID_FRAME_TeamBattleRequest = NULL;
	m_pID_PICTURE_BackWall = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Team = NULL;
	m_pID_TEXT_NameA = NULL;
	m_pID_TEXT_NameB = NULL;
	m_pID_LIST_NameA = NULL;
	m_pID_LIST_NameB = NULL;
	m_pID_LIST_All = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TeamBattleRequest.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TeamBattleRequest::_IsVisable()
{
	if(!m_pID_FRAME_TeamBattleRequest)
		return false;

	return m_pID_FRAME_TeamBattleRequest->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TeamBattleRequest::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_TeamBattleRequest)
		return ;

	m_pID_FRAME_TeamBattleRequest->SetVisable( bVisable );
}

void CUI_ID_FRAME_TeamBattleRequest::Show(MsgShowBattleSignUpDlg* ack)
{
	m_SignInfo = ack->xSignUpInfo[0];

	if(ack->xSignUpInfo[0].nSignUpLeftTime!=0)
	{
		m_leftTime = ack->xSignUpInfo[0].nSignUpLeftTime*1000;

		m_MsgSendTimeCount = 0;

		m_Timestate = 1;
	}
}

void  CUI_ID_FRAME_TeamBattleRequest::ShowTime(MsgQueryBattleSignUpTimeAck* ack)
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

void CUI_ID_FRAME_TeamBattleRequest::OnAck( MsgBattleSignUpAck* pMsg )
{
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_SignUpSuccess, theXmlString.GetString( 20000 + pMsg->uchResult ) );
}

void CUI_ID_FRAME_TeamBattleRequest::OnTeamInfo( MsgTellBattleSignUpInfo* pMsg )
{
	m_vecName.clear();
	m_vecTeamID.clear();
	for(int i=0;i<pMsg->nCount;++i)
	{
		string str = pMsg->xTeamInfo[i].szName;
		m_vecName.push_back(str);
		m_vecTeamID.push_back(pMsg->xTeamInfo[i].dwTeamID);
	}

	Refresh();
}

void CUI_ID_FRAME_TeamBattleRequest::Refresh()
{
	m_pID_LIST_All->Clear();
	m_pID_LIST_NameA->Clear();
	m_pID_LIST_NameB->Clear();
	ControlList::S_List	stItem;
	for(int i=0;i<m_vecName.size();++i)
	{
		char str[260];

		MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, theXmlString.GetString(eText_TeamBattleName),m_vecName[i].c_str());

		stItem.SetData(str);

		if(i%2==0)
		{
			m_pID_LIST_NameA->AddItem(&stItem,NULL, false);
			stItem.SetData("");
			m_pID_LIST_All->AddItem(&stItem,NULL,false);
		}
		else
		{
			m_pID_LIST_NameB->AddItem(&stItem,NULL, false);
		}
	}
}

bool EnterBattleFiled( const char bPressYesButton, void *pData )
{
	if(pData)
	{
		MsgEnterTeamBattleAck msg;
		::CopyMemory(&msg,pData,sizeof(MsgEnterTeamBattleAck));

		msg.bEnterStage = bPressYesButton;

		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}

void CUI_ID_FRAME_TeamBattleRequest::NotifyEnter()
{
	MsgEnterTeamBattleAck msg;
	s_CUI_ID_FRAME_MessageBox.Show( "是否进入战场","" ,
			CUI_ID_FRAME_MessageBox::eTypeYesNo,false,EnterBattleFiled,&msg,sizeof(MsgEnterTeamBattleAck));
}