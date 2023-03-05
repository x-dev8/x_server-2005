/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CountryBaseInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CountryBaseInfo.h"
#include "UIMgr.h"
#include "CountryBroadcast.h"
#include "CountryQuestPost.h"
#include "CountryInput.h"
#include "CountryFunction.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "Gang.h"
#include "MiniMapUI.h"
#include "AllNpcList.h"
#include "CountryBattleKillNum.h"
#include "CampBattleMessage.h"
#include "ChangeCountryTip.h"
#include "CountryQuest.h"
#include "CountryOfficial.h"
#include "CountryInfo.h"
#include "Select.h"
#include "CountryChangeInfo.h"

#ifndef STR_MAXLEN
#define STR_MAXLEN	255
#endif

CUI_ID_FRAME_BaseInfo s_CUI_ID_FRAME_BaseInfo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_BaseInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_BaseInfo, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseInfo, ID_CHECKBOX_InfoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseInfo, ID_CHECKBOX_QuestOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseInfo, ID_CHECKBOX_PositionOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseInfo, ID_CHECKBOX_CountryInfoOnCheckBoxCheck )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseInfo, ID_BUTTON_JinYanOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseInfo, ID_BUTTON_CommonOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseInfo, ID_BUTTON_QuestOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseInfo, ID_BUTTON_RewardMoneyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseInfo, ID_BUTTON_SheMianOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseInfo, ID_BUTTON_QiuJinOnButtonClick )
CUI_ID_FRAME_BaseInfo::CUI_ID_FRAME_BaseInfo()
{
	// Member
	m_pID_FRAME_BaseInfo = NULL;
	m_pID_CHECKBOX_Info = NULL;
	m_pID_CHECKBOX_Quest = NULL;
	m_pID_CHECKBOX_Position = NULL;
	//m_pID_TEXT_CountryName = NULL;
	m_pID_BUTTON_JinYan = NULL;
	m_pID_BUTTON_Common = NULL;
	m_pID_BUTTON_Quest = NULL;
	m_pID_BUTTON_RewardMoney = NULL;
	m_pID_BUTTON_SheMian = NULL;
	m_pID_BUTTON_QiuJin = NULL;
	m_pID_CHECKBOX_CountryInfo = NULL;

	m_nStrongth = 0;
	m_nTribute = 0;
	m_nCountryRight = 0;
	m_nMoney = 0;
	ResetProperties();
	
	IsLoad = false;
}
// Frame
bool CUI_ID_FRAME_BaseInfo::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_BaseInfo::OnFrameRender()
{
	if(!IsLoad && m_pID_CHECKBOX_CountryInfo->IsEnable())
	{
		m_pID_CHECKBOX_CountryInfo->SetEnable(false);//数据为加载完成的时候不可以使用
		s_CUI_ID_FRAME_CountryInfo.SetVisable(false);
	}
	else if(IsLoad && !m_pID_CHECKBOX_CountryInfo->IsEnable())
	{
		m_pID_CHECKBOX_CountryInfo->SetEnable(true);
	}
	return true;
}
// CheckBox
void CUI_ID_FRAME_BaseInfo::ID_CHECKBOX_InfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	//选择国家信息 
	if(!m_pID_CHECKBOX_Info->IsChecked())
	{
		m_pID_CHECKBOX_Info->SetCheck(true);
		return;
	}
	OnShowUI(CountryUIStates::CUS_Info);
	m_pID_CHECKBOX_Quest->SetCheck(false);
	m_pID_CHECKBOX_Position->SetCheck(false);
	m_pID_CHECKBOX_CountryInfo->SetCheck(false);
}
// CheckBox
void CUI_ID_FRAME_BaseInfo::ID_CHECKBOX_QuestOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_CHECKBOX_Quest->IsChecked())
	{
		m_pID_CHECKBOX_Quest->SetCheck(true);
		return;
	}
	OnShowUI(CountryUIStates::CUS_Quest);
	m_pID_CHECKBOX_Info->SetCheck(false);
	m_pID_CHECKBOX_Position->SetCheck(false);
	m_pID_CHECKBOX_CountryInfo->SetCheck(false);
}
// CheckBox
void CUI_ID_FRAME_BaseInfo::ID_CHECKBOX_PositionOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_CHECKBOX_Position->IsChecked())
	{
		m_pID_CHECKBOX_Position->SetCheck(true);
		return;
	}
	OnShowUI(CountryUIStates::CUS_Official);
	m_pID_CHECKBOX_Info->SetCheck(false);
	m_pID_CHECKBOX_Quest->SetCheck(false);
	m_pID_CHECKBOX_CountryInfo->SetCheck(false);
}
void CUI_ID_FRAME_BaseInfo::ID_CHECKBOX_CountryInfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_CHECKBOX_CountryInfo->IsChecked())
	{
		m_pID_CHECKBOX_CountryInfo->SetCheck(true);
		return;
	}
	OnShowUI(CountryUIStates::CUS_CountryInfo);
	m_pID_CHECKBOX_Info->SetCheck(false);
	m_pID_CHECKBOX_Quest->SetCheck(false);
	m_pID_CHECKBOX_Position->SetCheck(false);
}
// Button
bool CUI_ID_FRAME_BaseInfo::ID_BUTTON_JinYanOnButtonClick( ControlObject* pSender )
{
	//禁言
	if ( !m_pID_FRAME_BaseInfo )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_JinYan );
	return true;
}
// Button
bool CUI_ID_FRAME_BaseInfo::ID_BUTTON_CommonOnButtonClick( ControlObject* pSender )
{
	//通告
	if ( !m_pID_FRAME_BaseInfo )
	{
		assert( false && "ui error" );
		return false;
	}
	s_CUI_ID_FRAME_CountryBroadcast.SetVisable( true );
	return true;
}
// Button
bool CUI_ID_FRAME_BaseInfo::ID_BUTTON_QuestOnButtonClick( ControlObject* pSender )
{
	//发布任务 ..
	return true;
}
// Button
bool CUI_ID_FRAME_BaseInfo::ID_BUTTON_RewardMoneyOnButtonClick( ControlObject* pSender )
{
	//募捐
	if ( !m_pID_FRAME_BaseInfo )
	{
		assert( false && "ui error" );
		return false;
	}
	// 给服务器发消息
	MsgCountryRequestRaiseReq msg;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
// Button
bool CUI_ID_FRAME_BaseInfo::ID_BUTTON_SheMianOnButtonClick( ControlObject* pSender )
{
	//赦免
	if ( !m_pID_FRAME_BaseInfo )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_SheMian );
	return true;
}
// Button
bool CUI_ID_FRAME_BaseInfo::ID_BUTTON_QiuJinOnButtonClick( ControlObject* pSender )
{
	//囚禁
	if ( !m_pID_FRAME_BaseInfo )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( eShowType_QiuJin );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_BaseInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CountryBaseInfo.MEUI" ,false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CountryBaseInfo.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_BaseInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_BaseInfo, s_CUI_ID_FRAME_BaseInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_BaseInfo, s_CUI_ID_FRAME_BaseInfoOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseInfo, ID_CHECKBOX_Info, s_CUI_ID_FRAME_BaseInfoID_CHECKBOX_InfoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseInfo, ID_CHECKBOX_Quest, s_CUI_ID_FRAME_BaseInfoID_CHECKBOX_QuestOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseInfo, ID_CHECKBOX_Position, s_CUI_ID_FRAME_BaseInfoID_CHECKBOX_PositionOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseInfo, ID_CHECKBOX_CountryInfo, s_CUI_ID_FRAME_BaseInfoID_CHECKBOX_CountryInfoOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_BaseInfo, ID_BUTTON_JinYan, s_CUI_ID_FRAME_BaseInfoID_BUTTON_JinYanOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseInfo, ID_BUTTON_Common, s_CUI_ID_FRAME_BaseInfoID_BUTTON_CommonOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseInfo, ID_BUTTON_Quest, s_CUI_ID_FRAME_BaseInfoID_BUTTON_QuestOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseInfo, ID_BUTTON_RewardMoney, s_CUI_ID_FRAME_BaseInfoID_BUTTON_RewardMoneyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseInfo, ID_BUTTON_SheMian, s_CUI_ID_FRAME_BaseInfoID_BUTTON_SheMianOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseInfo, ID_BUTTON_QiuJin, s_CUI_ID_FRAME_BaseInfoID_BUTTON_QiuJinOnButtonClick );

	m_pID_FRAME_BaseInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_BaseInfo );
	m_pID_CHECKBOX_Info = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_CHECKBOX_Info );
	m_pID_CHECKBOX_Quest = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_CHECKBOX_Quest );
	m_pID_CHECKBOX_Position = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_CHECKBOX_Position );
	m_pID_CHECKBOX_CountryInfo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_CHECKBOX_CountryInfo );
	//m_pID_TEXT_CountryName = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_TEXT_CountryName );
	m_pID_BUTTON_JinYan = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_BUTTON_JinYan );
	m_pID_BUTTON_Common = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_BUTTON_Common );
	m_pID_BUTTON_Quest = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_BUTTON_Quest );
	m_pID_BUTTON_RewardMoney = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_BUTTON_RewardMoney );
	m_pID_BUTTON_SheMian = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_BUTTON_SheMian );
	m_pID_BUTTON_QiuJin = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseInfo, ID_BUTTON_QiuJin );
	assert( m_pID_FRAME_BaseInfo );
	assert( m_pID_CHECKBOX_Info );
	assert( m_pID_CHECKBOX_Quest );
	assert( m_pID_CHECKBOX_Position );
	//assert( m_pID_TEXT_CountryName );
	assert( m_pID_BUTTON_JinYan );
	assert( m_pID_BUTTON_Common );
	assert( m_pID_BUTTON_Quest );
	assert( m_pID_BUTTON_RewardMoney );
	assert( m_pID_BUTTON_SheMian );
	assert( m_pID_BUTTON_QiuJin );
	assert( m_pID_CHECKBOX_CountryInfo );
	ResetProperties();
	m_pID_FRAME_BaseInfo->SetOnVisibleChangedFun( OnVisibleChange );
	TryToUpdate();
	CheckNeedGetCountryInfo();
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_BaseInfo::_UnLoadUI()
{
	m_pID_FRAME_BaseInfo = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CountryBaseInfo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_BaseInfo::_IsVisable()
{
	return m_pID_FRAME_BaseInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_BaseInfo::_SetVisable( const bool bVisable )
{
	if(thePlayerRole.GetCountry() == CountryDefine::Country_Init)
	{
		//没有国家 无法弹出Ui 弹出MessageBox提示
		m_pID_FRAME_BaseInfo->SetVisable( false );
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NonCountryByCountry));
		return;
	}
	OnShowUI();
	m_pID_FRAME_BaseInfo->SetVisable( bVisable );
}
void CUI_ID_FRAME_BaseInfo::OnUpdateUI()
{
	//1.根据权力 显示按钮的状态
	// 禁言权
	if( m_nCountryRight & Right_BanSpeak )
		m_pID_BUTTON_JinYan->SetEnable( true );
	else
		m_pID_BUTTON_JinYan->SetEnable( false );

	// 囚禁权
	if( m_nCountryRight & Right_Chain )
		m_pID_BUTTON_QiuJin->SetEnable( true );
	else
		m_pID_BUTTON_QiuJin->SetEnable( false );

	// 赦免权
	if( m_nCountryRight & Right_Remit )
		m_pID_BUTTON_SheMian->SetEnable( true );
	else
		m_pID_BUTTON_SheMian->SetEnable( false );

	// 募集权
	if( m_nCountryRight & Right_Raise )
		m_pID_BUTTON_RewardMoney->SetEnable( true );
	else
		m_pID_BUTTON_RewardMoney->SetEnable( false );

	//发布国务
	if( m_nCountryRight & Right_QuestKing 
		|| m_nCountryRight & Right_QuestGeneral 
		|| m_nCountryRight & Right_QuestCouncilorLeft 
		|| m_nCountryRight & Right_QuestCouncilorRight 
		)
		m_pID_BUTTON_Quest->SetEnable( true );
	else
		m_pID_BUTTON_Quest->SetEnable( false );

	//公告
	if( m_nCountryRight & Right_Placard )
		m_pID_BUTTON_Common->SetEnable( true );
	else
		m_pID_BUTTON_Common->SetEnable( false );
}
void CUI_ID_FRAME_BaseInfo::OnShowUI(CountryUIStates Type)
{
	OnUpdateUI();
	//显示UI 时候 对UI上的数据 控件进行设置
	m_pID_CHECKBOX_Info->SetCheck(false);
	m_pID_CHECKBOX_Quest->SetCheck(false);
	m_pID_CHECKBOX_Position->SetCheck(false);
	m_pID_CHECKBOX_CountryInfo->SetCheck(false);

	s_CUI_ID_FRAME_Info.SetVisable(false);
	s_CUI_ID_FRAME_Quest.SetVisable(false);
	s_CUI_ID_FRAME_Official.SetVisable(false);
	s_CUI_ID_FRAME_CountryInfo.SetVisable(false);
	switch(Type)
	{
	case CountryUIStates::CUS_Info:
		m_pID_CHECKBOX_Info->SetCheck(true);
		s_CUI_ID_FRAME_Info.SetVisable(true);
		break;
	case CountryUIStates::CUS_Quest:
		m_pID_CHECKBOX_Quest->SetCheck(true);
		s_CUI_ID_FRAME_Quest.SetVisable(true);
		break;
	case CountryUIStates::CUS_Official:
		m_pID_CHECKBOX_Position->SetCheck(true);
		s_CUI_ID_FRAME_Official.SetVisable(true);
		break;
	case CountryUIStates::CUS_CountryInfo:
		m_pID_CHECKBOX_CountryInfo->SetCheck(true);
		s_CUI_ID_FRAME_CountryInfo.SetVisable(true);
		break;
	}
}
//开始处理结束与国家相关的全部信息处理 命令
void CUI_ID_FRAME_BaseInfo::GetCountryInfo( const MsgQueryCountryInfoAck* pMsg )
{
	if( !pMsg )
		return;
	m_strBroadcastText = pMsg->szNotice; //国家公告
	for( int i = 0; i < Position_Max; i++ )
	{
		m_strOfficalName[ i ] = pMsg->szOfficial[ i ]; //官员名称

		m_OfficialDisPlayer[i].sex  =  pMsg->szsexID[i];
		m_OfficialDisPlayer[i].face  = pMsg->szfaceID[i];
		m_OfficialDisPlayer[i].header  = pMsg->szheaderID[i];
		m_OfficialDisPlayer[i].profession  = pMsg->szprofession[i];
	}
    // 金银铜
	m_nMoney = pMsg->nMoney;
    uint32 nCopper = m_nMoney % 100;
    uint32 nSiller = ( m_nMoney / 100 ) % 100;
    uint32 nGold = m_nMoney / 10000;
    char szMoney[ STR_MAXLEN ] = {0};
    MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#83}", nCopper );
    m_strMoney = szMoney; //国库资金
	m_nStrongth	= pMsg->nStrongth;
    if( nSiller )
    {
        MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#82}%s", nSiller, m_strMoney.c_str() );
        m_strMoney = szMoney;
    }
    if( nGold )
    {
	    MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#81}%s", nGold, m_strMoney.c_str() );
        m_strMoney = szMoney;
    }

	m_nCountryRight = pMsg->nCountryRight; //当前玩家权力
	for( int i = 0; i < QuestType_Max; i++ ) //任务状态
	{
		m_taskStatus[ i ].uchCount = pMsg->xQuestStatus[ i ].uchCount;
		m_taskStatus[ i ].nLeftTime = pMsg->xQuestStatus[ i ].nLeftTime;
	}
	m_nTribute = pMsg->nTribute;
	//更新完国家相关属性 我们需要更新UI上的值
	UpdateUIInfo();
}
void CUI_ID_FRAME_BaseInfo::OnAddCountryInfo(const char * szInfo,__int64 Time,int Value)
{
	//更新UI上的数据
	bool IsNeedChange = true;
	for(int i =0;i<CountryDefine::MaxCountryInfoSum;++i)
	{
		if(szCountryTime[i] == 0)
		{
			szCountryTime[i] = Time;
			szCountryValue[i] = Value;
			HelperFunc::SafeNCpy( szCountryInfo[i], szInfo, sizeof( szCountryInfo[i] ) );
			IsNeedChange = false;
			break;
		}
		else
			continue;
	}
	if(IsNeedChange)
	{
		for(int i =1;i<CountryDefine::MaxCountryInfoSum;++i)
		{
			szCountryTime[i-1]=szCountryTime[i];
			szCountryValue[i-1] = szCountryValue[i];
			HelperFunc::SafeNCpy( szCountryInfo[i-1], szCountryInfo[i], sizeof( szCountryInfo[i-1] ) );
		}
		szCountryTime[CountryDefine::MaxCountryInfoSum -1] = Time;
		szCountryValue[CountryDefine::MaxCountryInfoSum -1] = Value;
		HelperFunc::SafeNCpy( szCountryInfo[CountryDefine::MaxCountryInfoSum -1], szInfo, sizeof( szCountryInfo[CountryDefine::MaxCountryInfoSum -1] ) );
	}
	UpdateUIInfo();
}
void CUI_ID_FRAME_BaseInfo::OnLoadCountryInfo(MsgLoadCountryInfoAck * pMsg)
{
	for(int j = 0;j<pMsg->Sum;++j)
	{
		strcpy_s(szCountryInfo[j],CountryDefine::MaxCountryInfoLength,pMsg->Info[j]);
		szCountryTime[j] = pMsg->Time[j];
		szCountryValue[j] = pMsg->values[j];
	}
	if(pMsg->IsEnd)
	{
		IsLoad = true;
	}
}
void CUI_ID_FRAME_BaseInfo::GetCountryDate(const MsgUpdateCountryDate* pMsg)
{
	if (!pMsg)
	{
		return;
	}
	switch (pMsg->chType)
	{
	case UpdateTribute:
		m_nTribute = pMsg->nValue;
		break;
	case UpdateMoney:
		{
			int ChangeValue = pMsg->nValue - m_nMoney;
			if(/*!IsLoad &&*/ m_nMoney == 0)
				ChangeValue = 0;
			m_nMoney  = pMsg->nValue;
			uint32 nCopper = m_nMoney % 100;
			uint32 nSiller = ( m_nMoney / 100 ) % 100;
			uint32 nGold = m_nMoney / 10000;
			char szMoney[ STR_MAXLEN ] = {0};
			MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#83}", nCopper );
			m_strMoney = szMoney; //国库资金
			if( nSiller )
			{
				MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#82}%s", nSiller, m_strMoney.c_str() );
				m_strMoney = szMoney;
			}
			if( nGold )
			{
				MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#81}%s", nGold, m_strMoney.c_str() );
				m_strMoney = szMoney;
			}
			char szText[256] = {0};
			if(ChangeValue >0)
			{
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Country_IncreaseGuildMoney),ChangeValue);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, szText );
			}
			else if(ChangeValue<0)
			{
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Country_DecreaseGuildMoney), ChangeValue*-1);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, szText );
			}
			else
			{
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Country_NowGuildMoney), m_nMoney);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, szText );
			}
		}
		break;
	case UpdateNowStrength:
		//更新本周实力
		m_nStrongth = pMsg->nValue;
		break;
	}
	UpdateUIInfo();
}
void CUI_ID_FRAME_BaseInfo::TryToUpdate()
{
	MsgQueryCountryInfoReq msg;
	GettheNetworkInput().SendMsg( &msg );
}
void CUI_ID_FRAME_BaseInfo::OnVisibleChange( ControlObject* pUIObject )
{
	if( s_CUI_ID_FRAME_BaseInfo.IsVisable() )
	{
		s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
	}
}
void CUI_ID_FRAME_BaseInfo::ResetProperties()
{
	m_strBroadcastText = "";
	m_strMoney = "";
	m_nMoney = 0;
	m_nCountryRight = 0;
	m_nStrongth = 0;
	m_nTribute =0;
	for( int i = 0; i < Position_Max; i++ )
	{
		m_strOfficalName[ i ] = "";

		m_OfficialDisPlayer[i].sex = Sex_Male;
		m_OfficialDisPlayer[i].face = 0;
		m_OfficialDisPlayer[i].header= 0;
	}
	for( int i = 0; i < QuestType_Max; i++ )
	{
		m_taskStatus[ i ].uchCount = 0;
		m_taskStatus[ i ].nLeftTime = 0;
	}
}
void CUI_ID_FRAME_BaseInfo::UpdateUIInfo()
{
	if(!s_CUI_ID_FRAME_BaseInfo.IsVisable())
		return;
	OnUpdateUI();
	if(s_CUI_ID_FRAME_Info.IsVisable())
	{
		//进行更新UI上的设置
		s_CUI_ID_FRAME_Info.OnInitUIInfo();
	}
	else if(s_CUI_ID_FRAME_Quest.IsVisable())
	{
		//进行更新UI上的设置
		s_CUI_ID_FRAME_Quest.OnInitUIInfo();
	}
	else if(s_CUI_ID_FRAME_Official.IsVisable())
	{
		//进行更新UI上的设置
		s_CUI_ID_FRAME_Official.OnInitUIInfo();
	}
	else if(s_CUI_ID_FRAME_CountryInfo.IsVisable())
	{
		s_CUI_ID_FRAME_CountryInfo.OnInitUIInfo();
	}
}
// 以下为国家召集的功能
void CUI_ID_FRAME_BaseInfo::GetConveneResult( uint8 result )
{
	switch( result )
	{
	case MsgCountryConveneResult::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_CountryConvene_Success ) );
		TryToUpdate();
		break;
	case MsgCountryConveneResult::ECD_NotRight:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_CountryConvene_NotRight ) );
		break;
	case MsgCountryConveneResult::ECD_TimeLimit:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_CountryConvene_TimeLimit ) );
		break;
	case MsgCountryConveneResult::ECD_NotEnoughMoney:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_CountryConvene_NotEnoughMoney ) );
		break;
	default:
		break;
	}
}
void CUI_ID_FRAME_BaseInfo::ShowCountryConvene()
{
	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_CountryConvene_YesOrNo ), "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
		false, ProcessConveneReply );
}

bool CUI_ID_FRAME_BaseInfo::ProcessConveneReply( const char bYesPress, void *pData )
{
	if( bYesPress )
	{
		MsgCountryConveneAck msg;
		GettheNetworkInput().SendMsg( &msg );
		return true;
	}
	return true;
}

void CUI_ID_FRAME_BaseInfo::GetBattleSignUpResult( uint8 result )
{
    switch( result )
    {
    case CampDefine::SignUp_Success:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_Success ) );
        break;
    case CampDefine::SignUp_NotSignUpStatus:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_NotTime ) );
        break;
    case CampDefine::SignUp_MustGuildMaster:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_MustMaster ) );
        break;
    case CampDefine::SignUp_GuildLevelLess:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_LevelLess ) );
        break;
    case CampDefine::SignUp_GuildMemberLess:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_MemberLess ) );
        break;
    case CampDefine::SignUp_GuildStrengthLess:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_StrengthLess ) );
        break;
	case CampDefine::SignUp_GuildUnionBattleSumError:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
				theXmlString.GetString( eText_SignUp_GuildUnionBattleSumError ) );
		}
		break;
	case CampDefine::SignUp_GuildUnionBattleNone:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
				theXmlString.GetString( eText_SignUp_GuildUnionBattleNone ) );
		}
		break;
	case CampDefine::SignUp_GuildBattleFull:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
				theXmlString.GetString( eText_SignUp_GuildBattleFull ) );
		}
		break;
    case CampDefine::SignUp_NotEnoughGuildMoney:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_MoreMoney ) );
        break;
    case CampDefine::SignUp_AlreadySignUp:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_Already ) );
        break;
    case CampDefine::SignUp_CanNotSignUp:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip,
            theXmlString.GetString( eText_CountryBattle_SignUp_CanNot ) );
        break;
    default:
        break;
    }
}

void CUI_ID_FRAME_BaseInfo::TellCountryBattleSignUp( uint8 nType, uint32 nTime )
{
    // 报名持续时间
    char szTemp[MAX_PATH] = {0};
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nType );
    std::string strTime = CountryFunction::GetTimeStringBySeconds( ( DWORD )nTime * 1000 );
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_SignUp ), strBattleName.c_str(), strTime.c_str() );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
}

void CUI_ID_FRAME_BaseInfo::TellGuildCountryBattleQualify( uint8 nBattleType, uint32 nGuildID )
{
    // 公会获得进入战场资格
    const CGuildInfo* pGuildInfo = thePlayerRole.GetGuildById( nGuildID );
    if( !pGuildInfo )
        return;
    
    char szTemp[MAX_PATH] = {0};
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_GuildOwnRight ), pGuildInfo->GetName(), strBattleName.c_str() );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Bull_System, szTemp);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szTemp);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ShiTu_Belongs_Success, szTemp);
}

void CUI_ID_FRAME_BaseInfo::TellCountryBattleEnterBegin( uint8 nBattleType, uint32 nTime )
{
    // 开始进入
    char szTemp[MAX_PATH] = {0};
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
    std::string strTime = CountryFunction::GetTimeStringBySeconds( ( DWORD )nTime * 1000 );
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_Open ), strBattleName.c_str(), strTime.c_str() );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
}

void CUI_ID_FRAME_BaseInfo::TellCountryBattleBegin( uint8 nBattleType, uint32 nTime )
{
    // 战斗开始
    char szTemp[MAX_PATH] = {0};
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
    std::string strTime = CountryFunction::GetTimeStringBySeconds( ( DWORD )nTime * 1000 );
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_BattleBegin ), strBattleName.c_str(), strTime.c_str() );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
}

void CUI_ID_FRAME_BaseInfo::TellCountryBattleResult( uint8 nBattleType, uint8 nWinType, uint32 nGuildID )
{
    // 国家战场结果
    const CGuildInfo* pGuildInfo = thePlayerRole.GetGuildById( nGuildID );
    if( !pGuildInfo )
        return;

    char szTemp[MAX_PATH] = {0};
	char szTemp1[MAX_PATH] = {0};
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
    switch( nWinType )
    {
    case BattleWin_FistTime:
        {
			
            MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryKing_ApplySuccess ),CountryFunction::GetCountryNameById(pGuildInfo->GetCountry()).c_str(),pGuildInfo->GetName() );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szTemp);

			//有新的国王产生
			char szTemp2[MAX_PATH] = {0};
			MeSprintf_s( szTemp2, sizeof( szTemp2 ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryKing_New ),pGuildInfo->GetMasterName(),CountryFunction::GetCountryNameById(pGuildInfo->GetCountry()).c_str());
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp2 );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp2 );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szTemp2);
			
        }
        break;
    case BattleWin_Guard:
        {
            MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_GuardSuccess ),CountryFunction::GetCountryNameById(pGuildInfo->GetCountry()).c_str(),
                strBattleName.c_str(), pGuildInfo->GetName() );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szTemp);

			//MeSprintf_s(szTemp1,sizeof(szTemp1)/ sizeof(char) - 1,theXmlString.GetString(eText_CountryBattle_QuitCountryWar));
			//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, szTemp1);
        }
        break;
    case BattleWin_Challenge:
        {
            MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString(eText_CountryBattle_ChallengeSuccess),
				CountryFunction::GetCountryNameById(pGuildInfo->GetCountry()).c_str(),
                strBattleName.c_str(), 
				pGuildInfo->GetName() );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szTemp);

			//MeSprintf_s(szTemp1,sizeof(szTemp1)/ sizeof(char) - 1,theXmlString.GetString(eText_CountryBattle_QuitCountryWar));
			//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, szTemp1);

			//有新的国王产生
			char szTemp2[MAX_PATH] = {0};
			MeSprintf_s( szTemp2, sizeof( szTemp2 ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryKing_New ),pGuildInfo->GetMasterName(),CountryFunction::GetCountryNameById(pGuildInfo->GetCountry()).c_str());
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, szTemp2 );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp2 );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szTemp2);
        }
        break;
    default:
        break;
    }
}
void CUI_ID_FRAME_BaseInfo::TellBetrayCountry( uint8 nCountry, GameObjectId nPlayerId )
{
    // 叛国通告
    char szTemp[MAX_PATH] = {0};
    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
    if( !pPlayerMgr )
        return;
    CPlayer* pPlayer = pPlayerMgr->FindByID( nPlayerId );
    if( !pPlayer )
        return;
	int old_counrty = thePlayerRole.GetCountry();//老国家的 ID
    pPlayer->SetRealCountry( nCountry );
    if( pPlayerMgr->GetMe() == pPlayer )
    {
        thePlayerRole.SetCountry( nCountry );
        /*if( thePlayerRole.IsInWeakCountry()&&nCountry != CountryDefine::Country_Init)
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_BeWeak ) );
        }
		else if( thePlayerRole.IsInStrongCountry()&&nCountry != CountryDefine::Country_Init)
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_BeStrong ) );
        }*/
        thePlayerRole.UpdateActiveQuestState();
        RefreshCountryNameBelongs();

		//lyh 添加下面几行，加入国家只让主角自己提示 不同步给其他玩家。
		std::string strCountry ="";
		if (old_counrty == CountryDefine::Country_Init)
		{
			theCountryTipInstance.AddTips(nCountry);
			strCountry = CountryFunction::GetDefaultCountryNameById( nCountry );
		}
		else if(old_counrty != thePlayerRole.GetCountry())
		{
			 strCountry = CountryFunction::GetDefaultCountryNameById( old_counrty );//zhuxincong 9.13 修改GetCountryNameById函数为GetDefaultCountryNameById函数
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBetray_Broadcast ), pPlayer->GetName(), strCountry.c_str() );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
		}
		std::string strWindowName = s_CUI_ID_FRAME_Select.m_strWindowText+" " + CountryFunction::GetDefaultCountryNameById( nCountry );
		theHeroGame.SetWindowText( strWindowName.c_str() );		
    }

	//if (old_counrty == CountryDefine::Country_Init)
	//{
	//	//std::string strCountry = CountryFunction::GetDefaultCountryNameById( nCountry );//zhuxincong 9.13 修改GetCountryNameById函数为GetDefaultCountryNameById函数
	//	//MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryChange ), strCountry.c_str() );
	//	//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
	//	theCountryTipInstance.AddTips(nCountry);
	//	//theCountryTipInstance.Render();
	//}
	//else if(old_counrty != thePlayerRole.GetCountry())
	//{
	//	std::string strCountry = CountryFunction::GetDefaultCountryNameById( nCountry );//zhuxincong 9.13 修改GetCountryNameById函数为GetDefaultCountryNameById函数
	//	MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBetray_Broadcast ), pPlayer->GetName(), strCountry.c_str() );
	//	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
	//}
}

void CUI_ID_FRAME_BaseInfo::TellBetrayCountryResult( uint8 nResult )
{
    // 叛国结果
    switch( nResult )
    {
    case MsgCountryChangeAck::ECD_Success:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Success, theXmlString.GetString( eText_CountryBetray_Success ) );
        break;
    case MsgCountryChangeAck::ECD_HaveTeam:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoTeam ) );
        break;
    case MsgCountryChangeAck::ECD_HaveGuild:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoGuild ) );
        break;
    case MsgCountryChangeAck::ECD_SameCountry:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoSameCountry ) );
        break;
    case MsgCountryChangeAck::ECD_ErrorCountry:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_ErrorCountry ) );
        break;
    case MsgCountryChangeAck::ECD_NotEnoughMoney:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoMoney ) );
        break;
    case MsgCountryChangeAck::ECD_HaveMarriage:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoMarry ) );
        break;
    case MsgCountryChangeAck::ECD_HaveStudent:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoStudent ) );
        break;
    case MsgCountryChangeAck::ECD_HaveTeacher:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_NoTeacher ) );
        break;
    case MsgCountryChangeAck::ECD_TimeLimit:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_OncePerWeek ) );
        break;
	/*case MsgCountryChangeAck::ECD_Config:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_config ) );
		break;*/
	case MsgCountryChangeAck::ECD_HaveOff:
		 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_Office ) );
		break;
	case MsgCountryChangeAck::ECD_Item:
		 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_Item ) );
		break;
	case MsgCountryChangeAck::ECD_MaxLevel:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_MaxLevel ) );
		break;
	case MsgCountryChangeAck::ECD_MinLevel:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_MinLeve ) );
		break;
	case MsgCountryChangeAck::ECD_QuestStates:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBetray_Failed, theXmlString.GetString( eText_CountryBetray_QuestState ) );
		break;
    default:
        break;
    }
}

void CUI_ID_FRAME_BaseInfo::TellCountryBattleReplace( uint8 nBattleType )
{
    // 战场报名被顶
    std::string strBattleName = CountryFunction::GetCountryBattleNameByType( nBattleType );
    char szTemp[MAX_PATH] = {0};
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_SignUpBeReplaced ), strBattleName.c_str() );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_Failed, szTemp );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, szTemp );
}

void CUI_ID_FRAME_BaseInfo::TellCountryWeak( uint8 nWeakCountry )
{
    // 弱国任务
    /*if( nWeakCountry == thePlayerRole.GetCountry()&&nWeakCountry != CountryDefine::Country_Init)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_BeWeak ) );
    }*/
    thePlayerRole.SetWeakCountry( nWeakCountry );
    thePlayerRole.UpdateActiveQuestState();
	/*
	 *	Author 2012-9-22 zhuxincong
	 *	DESC: 国家逻辑中因为0为无国籍的判断，而在弱国判断中0为弱国.
			那么在国家逻辑中，玩家加入国家后就不会再次回到0，那么我就全部注释掉了。
	 */
	return;
}
void CUI_ID_FRAME_BaseInfo::TellCountryStrong( uint8 nStrongCountry )
{
	//设置本国为强国
	/*if( nStrongCountry == thePlayerRole.GetCountry()&&nStrongCountry != CountryDefine::Country_Init)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_Country_BeStrong ) );
    }*/
    thePlayerRole.SetStrongCountry( nStrongCountry );
    thePlayerRole.UpdateActiveQuestState();
	return;
}
void CUI_ID_FRAME_BaseInfo::TellCountryNameChange( uint8 nCountryId, char* szName, char* szKingName )
{
    // 更改国号
    CountryFunction::Instance()->UpdateCountryName( nCountryId, szName );
    RefreshCountryNameBelongs();

    if( thePlayerRole.GetCountry() == nCountryId )
    {
        char szTemp[MAX_PATH] = {0};
        MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_Country_KingChangeName ), szKingName, szName );
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_ChangeName, szTemp );
    }
}

void CUI_ID_FRAME_BaseInfo::TellCountryNameInit( char* szName )
{
    // 获取国号
    for( int i = Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        CountryFunction::Instance()->UpdateCountryName( i, szName + i * CountryDefine::MaxCountryLength );
    }
    RefreshCountryNameBelongs();
}

void CUI_ID_FRAME_BaseInfo::TellChangeCountryNameResult( int nResult )
{
    // 改国号回馈
    switch( nResult )
    {
    case MsgChangeCountryNameAck::ECD_Success:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_ChangeNameSuccess ) );
        break;
    case MsgChangeCountryNameAck::ECD_NotHaveRight:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_ChangeNameNoRight ) );
        break;
    case MsgChangeCountryNameAck::ECD_ChangeOnce:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_ChangeNameOnce ) );
        break;
    case MsgChangeCountryNameAck::ECD_ErrorName:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_ChangeNameError ) );
        break;
    default:
        break;
    }
}

void CUI_ID_FRAME_BaseInfo::TellCountryWarStatus( int nStatus )
{
    // 屠城战
    switch( nStatus )
    {
    case CountryDefine::WarStatusPrepare:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast,
                theXmlString.GetString( eText_CountryWar_WillBegin ) );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate,
                theXmlString.GetString( eText_CountryWar_WillBegin ) );
        }
        break;
    case CountryDefine::WarStatusFight:
        {
            s_CUI_ID_FRAME_HolyShit.SetCountryBattleShow( true );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast,
                theXmlString.GetString( eText_CountryWar_Begin ) );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate,
                theXmlString.GetString( eText_CountryWar_Begin ) );
        }
        break;
    case CountryDefine::WarStatusEnd:
        {
            s_CUI_ID_FRAME_HolyShit.SetCountryBattleShow( false );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryBattle_Broadcast, theXmlString.GetString( eText_CountryWar_End ) );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Operate, theXmlString.GetString( eText_CountryWar_End ) );
        }
        break;
    default:
        break;
    }
}

void CUI_ID_FRAME_BaseInfo::TellPlayerRaiseResult( const char* pName, int nMoney )
{
    // 广播募捐
    if( !pName || nMoney <= 0 )
        return;

    int nGold( 0 ), nSilver( 0 ), nCopper( 0 );
    thePlayerRole.GetGSCFromMoney( nMoney, nGold, nSilver, nCopper );

    std::stringstream str;
    if( nGold > 0 )
        str << nGold << theXmlString.GetString( eText_Money_Gold );
    if( nSilver > 0 )
        str << nSilver << theXmlString.GetString( eText_Money_Silver );
    if( nCopper > 0 || ( nGold == 0 && nSilver == 0 ) )
        str << nCopper << theXmlString.GetString( eText_Money_Copper );
    std::string strMoney = str.str();

    char szTemp[MAX_PATH] = {0};
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryRise_Broadcast ), pName, strMoney.c_str() );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_CountryRaise_Broadcast, szTemp );
}
void CUI_ID_FRAME_BaseInfo::RefreshCountryNameBelongs()
{
    DWORD dwColor = Color_Config.getColor( CC_Center_MapInfo );
    s_CUI_ID_FRAME_MiniMap.ShowMapName( dwColor );
    s_CUI_ID_FRAME_AllNpcList.RefreshMapList();
}
void CUI_ID_FRAME_BaseInfo::GetRaiseResult( uint8 result )
{
	switch( result )
	{
	case MsgCountryRequestRaiseAck::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Raise_Success ) );
		TryToUpdate();
		break;
	case MsgCountryRequestRaiseAck::ECD_NotRight:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Raise_NotRight ) );
		break;
	case MsgCountryRequestRaiseAck::ECD_TimeLimit:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Raise_TimeLimit ) );
		break;
	default:
		break;
	}
}
void CUI_ID_FRAME_BaseInfo::GetReceiveMountResult( uint8 result )
{
	// 领取坐骑
	switch( result )
	{
	case MsgCountryReceiveMountAck::ECD_Success:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Mount_Success ) );
		TryToUpdate();
		break;
	case MsgCountryReceiveMountAck::ECD_NotRight:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Mount_NotRight ) );
		break;
	case MsgCountryReceiveMountAck::ECD_Alreadly:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Mount_Alreadly ) );
		break;
	case MsgCountryReceiveMountAck::ECD_NotHaveMount:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Mount_NotHave ) );
		break;
	case MsgCountryReceiveMountAck::ECD_MaxCount:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Mount_MaxCount ) );
		break;
	default:
		break;
	}
}
void CUI_ID_FRAME_BaseInfo::GetKillOfficialInfo( const MsgTellCountryKillPosition* pMsg )
{
	if( !pMsg )
		return;

	// 杀死国家官员
    std::string strCountryName1 = CountryFunction::GetCountryNameById( pMsg->uchKillerCountry );
    std::string strCountryName2 = CountryFunction::GetCountryNameById( pMsg->uchBeKilledCountry );
    std::string strPlayerPostion = CountryFunction::GetCountryOfficialNameById( pMsg->uchBeKilledPosition );

	char szKillInfo[ eMAX_TEMP_BUFF ];
	MeSprintf_s( szKillInfo, eMAX_TEMP_BUFF - 1, theXmlString.GetString( eText_Country_Kill_Offical ), 
		strCountryName1.c_str(), pMsg->szKillerName, strCountryName2.c_str(), strPlayerPostion.c_str(), pMsg->szBeKilledName );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_OfficialBeKilled, szKillInfo );
}
void CUI_ID_FRAME_BaseInfo::GetCountryTitleInfo( uint16 title )
{
	thePlayerRole.m_charinfo.baseinfo.liveinfo.nCountryTitle = title;
	m_nCountryRight = ( uint32 )GetCountryRightByTitle( ( unsigned short )title );
	s_CUI_ID_FRAME_Quest.GetNewCountryRight( m_nCountryRight );
	TryToUpdate();
}
void CUI_ID_FRAME_BaseInfo::TellCountryDonateResult( uint8 result )
{
	switch(result)
    {
    case MsgCountryRaiseTellPlayer::ECD_Success:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_Success ) );
		s_CUI_ID_FRAME_BaseInfo.TryToUpdate();
        //s_CUI_ID_FRAME_Country.TryToUpdate();
        break;
    case MsgCountryRaiseTellPlayer::ECD_LevelLess:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_LevelLess ) );
        break;
    case MsgCountryRaiseTellPlayer::ECD_NotEnoughMoney:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_NotEnoughMoney ) );
        break;
    case MsgCountryRaiseTellPlayer::ECD_ErrorRaiseMoney:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_ErrorRaiseMoney ) );
        break;
    case MsgCountryRaiseTellPlayer::ECD_NotRaiseTime:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_NotRaiseTime ) );
        break;
    case MsgCountryRaiseTellPlayer::ECD_CountryMoneyMax:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Donate_CountryMoneyMax ) );
        break;
    }
}
void CUI_ID_FRAME_BaseInfo::LoadConfig()
{
	//在初始化的时候读取配置文件
	if(COUNTRYEQUIPNAME.empty()) return;
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(COUNTRYEQUIPNAME.c_str())) return;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("Project");
	if(pRoot == NULL) return;
	MeXmlElement* pPosition = pRoot->FirstChildElement("Position");
	if (pPosition == NULL) return;
	while (pPosition != NULL)
	{
		CountryOfficeModeInfo mode;
		int OffcieID = 0;
		if (pPosition->Attribute("ID",&OffcieID) == NULL)
			return;
		mode.OfficeID = OffcieID;

		int MaleModexID = 0;
		if (pPosition->Attribute("ValueMale",&MaleModexID) == NULL)
			return;
		mode.MaleModeID = MaleModexID;

		int FeMaleModeID = 0;
		if (pPosition->Attribute("ValueFeMale",&FeMaleModeID) == NULL)
			return;
		mode.FeMaleModeID = FeMaleModeID;

		if (pPosition->Attribute("PosX",&mode.X) == NULL)
			return;
		if (pPosition->Attribute("PosY",&mode.Y) == NULL)
			return;
		if (pPosition->Attribute("PosZ",&mode.Z) == NULL)
			return;

		if (pPosition->Attribute("ScaleMale",&mode.ScaleMale) == NULL)
			return;
		if (pPosition->Attribute("ScaleMale",&mode.ScaleFeMale) == NULL)
			return;

		if (pPosition->Attribute("RotationZ",&mode.RotationZ) == NULL)
			return;
		m_ModeInfo[mode.OfficeID] = mode;
		
		pPosition = pPosition->NextSiblingElement("Position");
	}
} 
void CUI_ID_FRAME_BaseInfo::InitializeAtEnterWorld()
{
	LoadConfig();
}
bool CUI_ID_FRAME_BaseInfo::CheckNeedGetCountryInfo()
{
	if(!IsLoad)
	{
		//发送命令 需要加载国家的数据
		MsgLoadCountryInfoReq msg;
		GettheNetworkInput().SendMsg( &msg );
		return false;
	}
	return true;
}