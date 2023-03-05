/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CountryInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CountryInfo.h"
#include "CountryBaseInfo.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "CountryFunction.h"
CUI_ID_FRAME_Info s_CUI_ID_FRAME_Info;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Info, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Info, OnFrameRender )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Info, ID_BUTTON_CountryCommonOnButtonClick )
CUI_ID_FRAME_Info::CUI_ID_FRAME_Info()
{
	// Member
	m_pID_FRAME_Info = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_CountryTribute = NULL;
	m_pID_TEXT_CountryMoney = NULL;
	m_pID_TEXT_CountryState = NULL;
	m_pID_TEXT_CountryStrong = NULL;
	m_pID_TEXT_KingName = NULL;
	//m_pID_BUTTON_CountryCommon = NULL;
	m_pID_TEXT_CommonInfo = NULL;

}
// Frame
bool CUI_ID_FRAME_Info::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Info::OnFrameRender()
{
	return true;
}
// Button
//bool CUI_ID_FRAME_Info::ID_BUTTON_CountryCommonOnButtonClick( ControlObject* pSender )
//{
//	return true;
//}
// 装载UI
bool CUI_ID_FRAME_Info::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CountryInfo.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CountryInfo.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Info::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Info, s_CUI_ID_FRAME_InfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Info, s_CUI_ID_FRAME_InfoOnFrameRender );
	//theUiManager.OnButtonClick( ID_FRAME_Info, ID_BUTTON_CountryCommon, s_CUI_ID_FRAME_InfoID_BUTTON_CountryCommonOnButtonClick );

	m_pID_FRAME_Info = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Info );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Info, ID_TEXT_Name );
	m_pID_TEXT_CountryTribute = (ControlText*)theUiManager.FindControl( ID_FRAME_Info, ID_TEXT_CountryTribute );
	m_pID_TEXT_CountryMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_Info, ID_TEXT_CountryMoney );
	m_pID_TEXT_CountryState = (ControlText*)theUiManager.FindControl( ID_FRAME_Info, ID_TEXT_CountryState );
	m_pID_TEXT_CountryStrong = (ControlText*)theUiManager.FindControl( ID_FRAME_Info, ID_TEXT_CountryStrong );
	m_pID_TEXT_KingName = (ControlText*)theUiManager.FindControl( ID_FRAME_Info, ID_TEXT_KingName );
	//m_pID_BUTTON_CountryCommon = (ControlButton*)theUiManager.FindControl( ID_FRAME_Info, ID_BUTTON_CountryCommon );
	m_pID_TEXT_CommonInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_Info, ID_TEXT_CommonInfo );
	assert( m_pID_FRAME_Info );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_CountryTribute );
	assert( m_pID_TEXT_CountryMoney );
	assert( m_pID_TEXT_CountryState );
	assert( m_pID_TEXT_CountryStrong );
	assert( m_pID_TEXT_KingName );
	//assert( m_pID_BUTTON_CountryCommon );
	assert( m_pID_TEXT_CommonInfo );
	m_pID_FRAME_Info->SetFather(s_CUI_ID_FRAME_BaseInfo.GetFrame());
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_Info::_UnLoadUI()
{
	m_pID_FRAME_Info = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CountryInfo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Info::_IsVisable()
{
	return m_pID_FRAME_Info->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Info::_SetVisable( const bool bVisable )
{
	if(bVisable)
		OnInitUIInfo();
	m_pID_FRAME_Info->SetVisable( bVisable );
}
void CUI_ID_FRAME_Info::OnInitUIInfo()
{
	//根据获取到的值 初始化UI上的数据
	//1.国家名称
	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return;
	CPlayer* pPlayer = pPlayerMgr->GetMe();
	if( !pPlayer )
		return;
	m_pID_TEXT_Name->SetText(CountryFunction::GetDefaultCountryNameById(pPlayer->GetRealCountry()));
	//2.国王名称
	m_pID_TEXT_KingName->SetText(s_CUI_ID_FRAME_BaseInfo.m_strOfficalName[Position_King]);
	//3.国家实力
	char szText[12] = {0};
	sprintf_s(szText, sizeof(szText)-1,"%d",s_CUI_ID_FRAME_BaseInfo.m_nStrongth);
	m_pID_TEXT_CountryStrong->SetText(szText);
	//4.国家状态
	if(thePlayerRole.IsInWeakCountry())
		m_pID_TEXT_CountryState->SetText(theXmlString.GetString( eText_Country_Weak ));
	else if(thePlayerRole.IsInStrongCountry())
		m_pID_TEXT_CountryState->SetText(theXmlString.GetString( eText_Country_Strongth));
	else
		m_pID_TEXT_CountryState->SetText(theXmlString.GetString( eText_Country_Normal));
	//5.兵书数量
	char szText2[12] = {0};
	sprintf_s(szText2, sizeof(szText2)-1,"%d",s_CUI_ID_FRAME_BaseInfo.m_nTribute);
	m_pID_TEXT_CountryTribute->SetText(szText2);
	//6.国家资金
	m_pID_TEXT_CountryMoney->SetText(s_CUI_ID_FRAME_BaseInfo.m_strMoney);
	//7.国家公告
	m_pID_TEXT_CommonInfo->SetText(s_CUI_ID_FRAME_BaseInfo.m_strBroadcastText);
}