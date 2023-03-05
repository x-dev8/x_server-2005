/********************************************************************
	Created by UIEditor.exe
	FileName: D:\FullBag(13.10.181)\Data\Ui\NewGuildGeneralBattleInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "NewGuildGeneralBattleInfo.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "Common.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "ScreenInfoManager.h"
#include "GameBattleMessage.h"
#include "GameBattleDefine.h"
#include "GuildBaseInfo.h"
CUI_ID_FRAME_NewGuildGeneralBattleInfo s_CUI_ID_FRAME_NewGuildGeneralBattleInfo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_NewGuildGeneralBattleInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_NewGuildGeneralBattleInfo, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_NewGuildGeneralBattleInfo, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_NewGuildGeneralBattleInfo, ID_BUTTON_CanelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_NewGuildGeneralBattleInfo, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_NewGuildGeneralBattleInfo::CUI_ID_FRAME_NewGuildGeneralBattleInfo()
{
	// Member
	m_pID_FRAME_NewGuildGeneralBattleInfo = NULL;
	m_pID_TEXT_GuildName = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_TEXT_GuildMoney = NULL;
	m_pID_TEXT_GuildMission = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_BeginTime = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Canel = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_LogShowTime = 0;
}
// Frame
bool CUI_ID_FRAME_NewGuildGeneralBattleInfo::OnFrameRun()
{
	if(m_LogShowTime !=0)
	{
		if(!IsVisable())
		{
			MsgAddCampBattleDataReq msg;
			msg.Result = false;
			msg.add = Info;
			GettheNetworkInput().SendMsg(&msg);
			ClearAllUIInfo();
		}
	}
	return true;
}
bool CUI_ID_FRAME_NewGuildGeneralBattleInfo::OnFrameRender()
{
	if(m_LogShowTime !=0)
	{
		time_t nowtime;
		time(&nowtime);
		if(nowtime - m_LogShowTime >= GameBattleDefine::WaiteAddMsgBattleTime)
		{
			//直接拒绝
			MsgAddCampBattleDataReq msg;
			msg.Result = false;
			msg.add = Info;
			GettheNetworkInput().SendMsg(&msg);
			ClearAllUIInfo();
			SetVisable(false);
		}
	}
	return true;
}
// Button
bool CUI_ID_FRAME_NewGuildGeneralBattleInfo::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	//同意公会约战
	MsgAddCampBattleDataReq msg;
	msg.Result = true;
	msg.add = Info;
	//我们队数据进行过滤
	if(!thePlayerRole.GetGangMgr())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_NonGuild));
		return true;
	}
	else if(Info.DestGuildID != thePlayerRole.GetGangMgr()->GetGuildID())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_TargetGuildNon));
		return true;
	}
	else if(Info.GuildMissionSum * 20 > thePlayerRole.GetGangMgr()->GetGuildMission())
	{
		//公会使命点超过
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_MissionError));
		return true;
	}
	else if(Info.GuildMoneySum * 20 > thePlayerRole.GetGangMgr()->GetGuildMoney())
	{
		//公会资金超过
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_GuildMoneyError));
		return true;
	}
	else if(!thePlayerRole.PackHasEnoughMoney(Info.MoneySum))
	{
		//金钱不足
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_MoneyError));
		return true;
	}
	else if(thePlayerRole.GetGangMgr()->GetGuildMasterID() != thePlayerRole.GetDBID())
	{
		//不是会长
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_NotMaster));
		return true;
	}
	else if(Info.GuildMoneySum == 0 && Info.GuildMissionSum ==0 && Info.MoneySum == 0)
	{
		//不可以全部为0
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_RewardError));
		return true;
	}
	else
	{
		GettheNetworkInput().SendMsg(&msg);
		ClearAllUIInfo();
		SetVisable(false);
		return true;
	}
	return true;
}
// Button
bool CUI_ID_FRAME_NewGuildGeneralBattleInfo::ID_BUTTON_CanelOnButtonClick( ControlObject* pSender )
{
	MsgAddCampBattleDataReq msg;
	msg.Result = false;
	msg.add = Info;
	GettheNetworkInput().SendMsg(&msg);
	ClearAllUIInfo();
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_NewGuildGeneralBattleInfo::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_NewGuildGeneralBattleInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\NewGuildGeneralBattleInfo.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\NewGuildGeneralBattleInfo.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_NewGuildGeneralBattleInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_NewGuildGeneralBattleInfo, s_CUI_ID_FRAME_NewGuildGeneralBattleInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_NewGuildGeneralBattleInfo, s_CUI_ID_FRAME_NewGuildGeneralBattleInfoOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_NewGuildGeneralBattleInfo, ID_BUTTON_OK, s_CUI_ID_FRAME_NewGuildGeneralBattleInfoID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_NewGuildGeneralBattleInfo, ID_BUTTON_Canel, s_CUI_ID_FRAME_NewGuildGeneralBattleInfoID_BUTTON_CanelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_NewGuildGeneralBattleInfo, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_NewGuildGeneralBattleInfoID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_NewGuildGeneralBattleInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_NewGuildGeneralBattleInfo );
	m_pID_TEXT_GuildName = (ControlText*)theUiManager.FindControl( ID_FRAME_NewGuildGeneralBattleInfo, ID_TEXT_GuildName );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_NewGuildGeneralBattleInfo, ID_TEXT_Info );
	m_pID_TEXT_GuildMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_NewGuildGeneralBattleInfo, ID_TEXT_GuildMoney );
	m_pID_TEXT_GuildMission = (ControlText*)theUiManager.FindControl( ID_FRAME_NewGuildGeneralBattleInfo, ID_TEXT_GuildMission );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_NewGuildGeneralBattleInfo, ID_TEXT_Money );
	m_pID_TEXT_BeginTime = (ControlText*)theUiManager.FindControl( ID_FRAME_NewGuildGeneralBattleInfo, ID_TEXT_BeginTime );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_NewGuildGeneralBattleInfo, ID_BUTTON_OK );
	m_pID_BUTTON_Canel = (ControlButton*)theUiManager.FindControl( ID_FRAME_NewGuildGeneralBattleInfo, ID_BUTTON_Canel );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_NewGuildGeneralBattleInfo, ID_BUTTON_CLOSE );
	assert( m_pID_FRAME_NewGuildGeneralBattleInfo );
	assert( m_pID_TEXT_GuildName );
	assert( m_pID_TEXT_Info );
	assert( m_pID_TEXT_GuildMoney );
	assert( m_pID_TEXT_GuildMission );
	assert( m_pID_TEXT_Money );
	assert( m_pID_TEXT_BeginTime );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Canel );
	assert( m_pID_BUTTON_CLOSE );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_NewGuildGeneralBattleInfo::_UnLoadUI()
{
	m_pID_FRAME_NewGuildGeneralBattleInfo = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\NewGuildGeneralBattleInfo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_NewGuildGeneralBattleInfo::_IsVisable()
{
	return m_pID_FRAME_NewGuildGeneralBattleInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_NewGuildGeneralBattleInfo::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_NewGuildGeneralBattleInfo)
		return;
	if(bVisable)
	{
		SetDataToUI(&Info,infoStr,srcGuildName);
		m_LogShowTime = m_LogShowTimeStep;
		m_LogShowTimeStep = 0;
	}
	else
	{
		if(m_LogShowTime != 0)
		{
			MsgAddCampBattleDataReq msg;
			msg.Result = false;
			msg.add = Info;
			GettheNetworkInput().SendMsg(&msg);
			ClearAllUIInfo();
		}
	}
	m_pID_FRAME_NewGuildGeneralBattleInfo->SetVisable( bVisable );
}
void CUI_ID_FRAME_NewGuildGeneralBattleInfo::SetDataToUI(GameBattleDefine::GuildCampBattle* pData,const char * pInfo,const char* nsrcGuildName)
{
	//将数据设置到UI上面去
	/*const CGuildInfo* pSrcGuild = thePlayerRole.GetGuildById(pData->SrcGuildID);
	const CGuildInfo* pDestGuild = thePlayerRole.GetGuildById(pData->DestGuildID);
	if(!pSrcGuild || !pDestGuild || pDestGuild->GetID() != thePlayerRole.GetGangMgr()->GetGuildID())
		return;*/
	if(m_pID_FRAME_NewGuildGeneralBattleInfo)
	{
		m_pID_TEXT_GuildName->SetText(nsrcGuildName);
		m_pID_TEXT_Info->SetText(pInfo);
		std::string strMoney="";
		if(pData->GuildMoneySum != 0)
			thePlayerRole.GetGSCStringFromMoney(pData->GuildMoneySum,strMoney);
		m_pID_TEXT_GuildMoney->SetText(strMoney.c_str());

		if(pData->MoneySum != 0)
			thePlayerRole.GetGSCStringFromMoney(pData->MoneySum,strMoney);
		m_pID_TEXT_Money->SetText(strMoney.c_str());

		time_t tt = pData->BeginTime;
		struct tm sysNowTime(*localtime(&tt));
		char TimeLog[64];
		sprintf_s(TimeLog,63,"%d-%d-%d %d:%d:%d",sysNowTime.tm_year+1900,sysNowTime.tm_mon+1,sysNowTime.tm_mday,sysNowTime.tm_hour,sysNowTime.tm_min,sysNowTime.tm_sec);
		m_pID_TEXT_BeginTime->SetText(TimeLog);
		char In[8];
		sprintf_s(In,7,"%d",pData->GuildMissionSum);
		m_pID_TEXT_GuildMission->SetText(In);
	}

	Info = *pData;
	strcpy_s(infoStr,sizeof(infoStr)-1,pInfo);
	strcpy_s(srcGuildName,sizeof(srcGuildName)-1,nsrcGuildName);
	time_t nowtime;
	time(&nowtime);
	m_LogShowTimeStep = nowtime;
}
void CUI_ID_FRAME_NewGuildGeneralBattleInfo::ClearAllUIInfo()
{
	m_pID_TEXT_GuildName->SetText("");
	m_pID_TEXT_Info->SetText("");
	m_pID_TEXT_GuildMoney->SetText("");
	m_pID_TEXT_Money->SetText("");
	m_pID_TEXT_BeginTime->SetText("");
	m_pID_TEXT_GuildMission->SetText("");
	m_LogShowTime = 0;
	strcpy_s(infoStr,sizeof(infoStr)-1,"");
	memset(&Info,0,sizeof(Info));
} 