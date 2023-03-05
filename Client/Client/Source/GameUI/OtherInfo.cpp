/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\角色资料和其他信息界面\角色资料和其他信息界面\OtherInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "OtherInfo.h"
#include "PlayerRole.h"
#include "SystemFamily.h"
#include "GlobalDef.h"
#include "GameMain.h"
#include "Player.h"
#include "..\PlayerMgr.h"
#include "baseProperty.h"
#include "BasePropertyBGFrame.h"
#include "CountryDefine.h"
#include "CountryFunction.h"

CUI_ID_FRAME_OtherInfo s_CUI_ID_FRAME_OtherInfo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_OtherInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_OtherInfo, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_OtherInfo, ID_EDIT_MSNOnEditEnter )
CUI_ID_FRAME_OtherInfo::CUI_ID_FRAME_OtherInfo()
{
	ResetMember();
}
CUI_ID_FRAME_OtherInfo::~CUI_ID_FRAME_OtherInfo()
{
	ResetMember();
}
void CUI_ID_FRAME_OtherInfo::ResetMember()
{
	// Member
	m_pID_FRAME_OtherInfo = NULL;
	m_pID_EDIT_MSN = NULL;
	m_pID_TEXT_ID = NULL;
	m_pID_TEXT_Family = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_Gang = NULL;
	m_pID_TEXT_Spouse = NULL;
	m_pID_TEXT_BangGong = NULL;
	m_pID_TEXT_WeiWang = NULL;
	m_pID_TEXT_TianFu = NULL;
	m_pID_TEXT_RongYu = NULL;
	m_pID_TEXT_PK = NULL;
	m_pID_TEXT_BattlefieldLevel = NULL;
	m_pID_TEXT_BattlefieldIntegral = NULL;
	m_pID_TEXT_SurplusMaster = NULL;
	m_pID_TEXT_AllMaster = NULL;
	m_pID_TEXT_SurplusApprentice = NULL;
	m_pID_TEXT_AllApprentice = NULL;
	m_pID_TEXT_SurplusDoubleEXP = NULL;
	m_pID_TEXT_PossessDoubleEXP = NULL;
	m_pID_TEXT_EspecialMoney = NULL;
	m_pID_TEXT_MONEY = NULL;
	m_pID_TEXT_Yingyuanbao = NULL;
	m_pID_TEXT_Jinyuanbao = NULL;
	//m_pID_TEXT_NowSkillExp =NULL;
	m_pID_TEXT_Exploit = NULL;
	m_pID_TEXT_WorldKillPlayer = NULL;
	m_pID_TEXT_WeekKillPlayer =NULL;
	m_pID_TEXT_Country = NULL;
	m_pID_TEXT_Position = NULL;

}
// Frame
bool CUI_ID_FRAME_OtherInfo::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_OtherInfo::OnFrameRender()
{
	return true;
}
// Edit
void CUI_ID_FRAME_OtherInfo::ID_EDIT_MSNOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_OtherInfo )
		return;
}

// 装载UI
bool CUI_ID_FRAME_OtherInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\OtherInfo.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\OtherInfo.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_OtherInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_OtherInfo, s_CUI_ID_FRAME_OtherInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_OtherInfo, s_CUI_ID_FRAME_OtherInfoOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_OtherInfo, ID_EDIT_MSN, s_CUI_ID_FRAME_OtherInfoID_EDIT_MSNOnEditEnter );

	m_pID_FRAME_OtherInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_OtherInfo );
	m_pID_EDIT_MSN = (ControlEdit*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_EDIT_MSN );
	m_pID_TEXT_ID = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_ID );
	m_pID_TEXT_Family = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_Family );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_Name );
	m_pID_TEXT_Gang = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_Gang );
	m_pID_TEXT_Spouse = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_Spouse );
	m_pID_TEXT_BangGong = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_BangGong );
	m_pID_TEXT_WeiWang = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_WeiWang );
	m_pID_TEXT_TianFu = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_TianFu );
	m_pID_TEXT_RongYu = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_RongYu );
	m_pID_TEXT_Exploit = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_Exploit );
	m_pID_TEXT_PK = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_PK );
	m_pID_TEXT_BattlefieldLevel = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_BattlefieldLevel );
	m_pID_TEXT_BattlefieldIntegral = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_BattlefieldIntegral );
	m_pID_TEXT_SurplusMaster = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_SurplusMaster );
	m_pID_TEXT_AllMaster = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_AllMaster );
	m_pID_TEXT_SurplusApprentice = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_SurplusApprentice );
	m_pID_TEXT_AllApprentice = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_AllApprentice );
	m_pID_TEXT_SurplusDoubleEXP = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_SurplusDoubleEXP );
	m_pID_TEXT_PossessDoubleEXP = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_PossessDoubleEXP );
	m_pID_TEXT_EspecialMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_EspecialMoney );
	m_pID_TEXT_MONEY = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_MONEY );
	m_pID_TEXT_Yingyuanbao = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_Yingyuanbao );
	m_pID_TEXT_Jinyuanbao = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_Jinyuanbao );
	//m_pID_TEXT_NowSkillExp = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_NowSkillExp );
	m_pID_TEXT_WorldKillPlayer = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_WorldKillPlayer);
	m_pID_TEXT_WeekKillPlayer =(ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_WeekKillPlayer);
	m_pID_TEXT_Country = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_Country );
	m_pID_TEXT_Position = (ControlText*)theUiManager.FindControl( ID_FRAME_OtherInfo, ID_TEXT_Position );
	
	SetKillPlayerSum(thePlayerRole.GetAllKillSum(),thePlayerRole.GetWeekKillSum());

	assert( m_pID_FRAME_OtherInfo );
	assert( m_pID_EDIT_MSN );
	assert( m_pID_TEXT_ID );
	assert( m_pID_TEXT_Family );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_Gang );
	assert( m_pID_TEXT_Spouse );
	assert( m_pID_TEXT_BangGong );
	assert( m_pID_TEXT_WeiWang );
	assert( m_pID_TEXT_TianFu );
	assert( m_pID_TEXT_RongYu );

	assert( m_pID_TEXT_Exploit );
	assert( m_pID_TEXT_PK );
	assert( m_pID_TEXT_BattlefieldLevel );
	assert( m_pID_TEXT_BattlefieldIntegral );
	assert( m_pID_TEXT_SurplusMaster );
	assert( m_pID_TEXT_AllMaster );
	assert( m_pID_TEXT_SurplusApprentice );
	assert( m_pID_TEXT_AllApprentice );
	assert( m_pID_TEXT_SurplusDoubleEXP );
	assert( m_pID_TEXT_PossessDoubleEXP );
	assert( m_pID_TEXT_EspecialMoney );
	assert( m_pID_TEXT_MONEY );
	assert( m_pID_TEXT_Yingyuanbao );
	assert( m_pID_TEXT_Jinyuanbao );
	assert( m_pID_TEXT_WorldKillPlayer );
	assert( m_pID_TEXT_WeekKillPlayer );
	assert( m_pID_TEXT_Country );
	assert( m_pID_TEXT_Position );
	//assert( m_pID_TEXT_NowSkillExp);
	m_pID_FRAME_OtherInfo->SetFather(s_CUI_ID_FRAME_BasePropertyBGFrame.GetFrame());
	_SetVisable(false);
	return true;
}
void CUI_ID_FRAME_OtherInfo::SetKillPlayerSum(uint32 WorldNum,uint32 WeekNum)
{
	if(m_pID_TEXT_WorldKillPlayer)
	{
		char szText[12] = {0};
		sprintf_s(szText, sizeof(szText)-1,"%d",WorldNum);
		m_pID_TEXT_WorldKillPlayer->SetText(szText);
	}
	if(m_pID_TEXT_WeekKillPlayer)
	{
		char szText[12] = {0};
		sprintf_s(szText, sizeof(szText)-1,"%d",WeekNum);
		m_pID_TEXT_WeekKillPlayer->SetText(szText);
	}
}
// 卸载UI
bool CUI_ID_FRAME_OtherInfo::_UnLoadUI()
{
	m_pID_FRAME_OtherInfo = NULL;
	m_pID_EDIT_MSN = NULL;
	m_pID_TEXT_ID = NULL;
	m_pID_TEXT_Family = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_Gang = NULL;
	m_pID_TEXT_Spouse = NULL;
	m_pID_TEXT_BangGong = NULL;
	m_pID_TEXT_WeiWang = NULL;
	m_pID_TEXT_TianFu = NULL;
	m_pID_TEXT_RongYu = NULL;
	m_pID_TEXT_PK = NULL;
	m_pID_TEXT_BattlefieldLevel = NULL;
	m_pID_TEXT_BattlefieldIntegral = NULL;
	m_pID_TEXT_SurplusMaster = NULL;
	m_pID_TEXT_AllMaster = NULL;
	m_pID_TEXT_SurplusApprentice = NULL;
	m_pID_TEXT_AllApprentice = NULL;
	m_pID_TEXT_SurplusDoubleEXP = NULL;
	m_pID_TEXT_PossessDoubleEXP = NULL;
	m_pID_TEXT_EspecialMoney = NULL;
	m_pID_TEXT_MONEY = NULL;
	m_pID_TEXT_Yingyuanbao = NULL;
	m_pID_TEXT_Jinyuanbao = NULL;
	m_pID_TEXT_Exploit = NULL;
	m_pID_TEXT_WorldKillPlayer = NULL;
	m_pID_TEXT_WeekKillPlayer =NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\OtherInfo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_OtherInfo::_IsVisable()
{
	if ( !m_pID_FRAME_OtherInfo )
		return false;
	return m_pID_FRAME_OtherInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_OtherInfo::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_OtherInfo )
		return ;
	m_pID_FRAME_OtherInfo->SetVisable( bVisable );
	if (bVisable)
	{
		RefreshBaseInfo();
	}
	
}

void CUI_ID_FRAME_OtherInfo::RefreshBaseInfo()
{
	m_pID_EDIT_MSN->SetText("");
	m_pID_TEXT_ID->SetText("");

	m_pID_TEXT_Family->SetText("");
	if (CSystemFamily::Instance()->IsMeHaveFamily() && CSystemFamily::Instance()->GetFamilyInfo() != NULL)
	{
		m_pID_TEXT_Family->SetText(	CSystemFamily::Instance()->GetFamilyInfo()->GetFamilyName());
	}
	
	m_pID_TEXT_Name->SetText("");
	m_pID_TEXT_Name->SetText(thePlayerRole.GetName());

	m_pID_TEXT_Gang->SetText("");
	CGangMgr *pGangMgr = thePlayerRole.GetGangMgr();
	if (NULL != pGangMgr || pGangMgr->GetGuildID() != GuildDefine::InitID)
	{
		m_pID_TEXT_Gang->SetText(pGangMgr->GetGuildName());
	}
	
	m_pID_TEXT_Spouse->SetText("");
	m_pID_TEXT_Spouse->SetText(thePlayerRole.GetMarryerName());

	m_pID_TEXT_BangGong->SetText("");
	m_pID_TEXT_PK->SetText("");
	m_pID_TEXT_BattlefieldLevel->SetText("");
	m_pID_TEXT_BattlefieldIntegral->SetText("");
	//m_pID_TEXT_NowSkillExp->SetText(thePlayerRole.GetSkillExpNotUsed());
	m_pID_TEXT_TianFu->SetText("");
	m_pID_TEXT_WeiWang->SetText("");
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( pMe != NULL )
	{
		m_pID_TEXT_BangGong->SetText(pMe->GetGuildOffer());
		m_pID_TEXT_PK->SetText(pMe->GetPKKillValue());
		m_pID_TEXT_BattlefieldIntegral->SetText(0);
		m_pID_TEXT_BattlefieldLevel->SetText(0);
		m_pID_TEXT_TianFu->SetText(0);
		m_pID_TEXT_WeiWang->SetText(thePlayerRole.GetMasterValue());
	}
	m_pID_TEXT_RongYu->SetText("");
	m_pID_TEXT_RongYu->SetText(thePlayerRole.m_charinfo.baseinfo.liveinfo.honour);

	if (m_pID_TEXT_Exploit)
	{
		m_pID_TEXT_Exploit->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_Exploit));
	}

	m_pID_TEXT_SurplusMaster->SetText("");
	m_pID_TEXT_AllMaster->SetText("");
	m_pID_TEXT_SurplusApprentice->SetText("");
	m_pID_TEXT_AllApprentice->SetText("");

	m_pID_TEXT_SurplusDoubleEXP->SetText("");
	m_pID_TEXT_SurplusDoubleEXP->SetText(thePlayerRole.m_charinfo.baseinfo.liveinfo.nSysDoubleExpTime);
	m_pID_TEXT_PossessDoubleEXP->SetText("");
	m_pID_TEXT_PossessDoubleEXP->SetText(thePlayerRole.m_charinfo.baseinfo.liveinfo.nItemDoubleExpTime);

	RefreshMoney();
	SetCountryAndPosition();

}

void CUI_ID_FRAME_OtherInfo::RefreshMoney()
{
	m_pID_TEXT_EspecialMoney->SetText("");
	m_pID_TEXT_MONEY->SetText("");
	m_pID_TEXT_Yingyuanbao->SetText("");
	m_pID_TEXT_Jinyuanbao->SetText("");
	
	std::string text = "";
	thePlayerRole.GetGSCStringFromCurrentJiaoZi(text);

	m_pID_TEXT_EspecialMoney->SetText(/*thePlayerRole.m_charinfo.baseinfo.liveinfo.jiaoZi*/text.c_str());

	thePlayerRole.GetGSCStringFromCurrentMoney(text);
	m_pID_TEXT_MONEY->SetText(/*thePlayerRole.m_charinfo.baseinfo.liveinfo.dwMoney*/text.c_str());

	m_pID_TEXT_Jinyuanbao->SetText(/*thePlayerRole.m_charinfo.baseinfo.liveinfo.jinDing*/thePlayerRole.GetData(CPlayerRole::TYPE_JinDing));
	m_pID_TEXT_Yingyuanbao->SetText(/*thePlayerRole.m_charinfo.baseinfo.liveinfo.jinPiao*/thePlayerRole.GetData(CPlayerRole::TYPE_JinPiao));

}

void CUI_ID_FRAME_OtherInfo::SetCountryAndPosition()
{
	if (!m_pID_TEXT_Country || !m_pID_TEXT_Position)
		return;
	m_pID_TEXT_Country->SetText("");
	m_pID_TEXT_Position->SetText("");

	uint8 nCountryId = thePlayerRole.GetCountry();
	std::string str = CountryFunction::GetDefaultCountryNameById(nCountryId);

	m_pID_TEXT_Country->SetText(str.c_str());

	uint8 nPosition = thePlayerRole.m_charinfo.baseinfo.liveinfo.uchPosition;
	std::string str1 = CountryFunction::GetCountryOfficialNameById(nPosition);

	if (nPosition == CountryDefine::Position_Queen && thePlayerRole.m_charinfo.baseinfo.aptotic.ucSex == 0)
		str1 = theXmlString.GetString(eText_CountryPos_QueenMale);

	m_pID_TEXT_Position->SetText(str1.c_str());
}