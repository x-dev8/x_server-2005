/********************************************************************
	Created by UIEditor.exe
	FileName: E:\OnlineAward2.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "OnlineAward2.h"
#include "UIMgr.h"
#include "XmlStringLanguage.h"
#include "MessageDefine.h"
#include "Common.h"
#include "NetworkInput.h"
#include "ItemDetail.h"
#include "IconManagerClient.h"
#include "OnlineReward.h"
#include "PlayerRole.h"

// 领取奖励按钮来回闪间隔
#define SPARK_CHANGE_TIME       300

CUI_ID_FRAME_OnlineAward2 s_CUI_ID_FRAME_OnlineAward2;
MAP_FRAME_RUN( s_CUI_ID_FRAME_OnlineAward2, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_OnlineAward2, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_OnlineAward2, ID_LISTIMG_HotkeyOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_OnlineAward2, ID_LISTIMG_HotkeyOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_OnlineAward2, ID_LISTIMG_HotkeyOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_OnlineAward2, ID_LISTIMG_HotkeyOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_OnlineAward2, ID_BUTTON_GetAwardOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_OnlineAward2, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_OnlineAward2, ID_BUTTON_CLOSEOnButtonClick )

CUI_ID_FRAME_OnlineAward2::CUI_ID_FRAME_OnlineAward2()
{
	// Member
	m_pID_FRAME_OnlineAward2 = NULL;
	m_pID_PICTURE_PageWall = NULL;
	m_pID_LISTIMG_Hotkey = NULL;
	m_pID_TEXT_Word = NULL;
	m_pID_BUTTON_GetAward = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Tips = NULL;
	m_pID_PROGRESS_Effect = NULL;
	m_pID_PROGRESS_Effect2 = NULL;
	//m_pID_PICTURE_ItemWall = NULL;
    Reset();
}

void CUI_ID_FRAME_OnlineAward2::InitializeAtEnterWorld()
{
    Reset();
}

void CUI_ID_FRAME_OnlineAward2::Reset()
{
    m_shRewardIndex = -1;
    m_usItemID = 0;
    m_usItemCount = 0;
    m_bChange = false;
    m_dwElapse = 0;
}

// Frame
bool CUI_ID_FRAME_OnlineAward2::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_OnlineAward2::OnFrameRender()
{

	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_OnlineAward2::ID_LISTIMG_HotkeyOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_OnlineAward2 )
		return false;
	return false;
}
bool CUI_ID_FRAME_OnlineAward2::ID_LISTIMG_HotkeyOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_OnlineAward2 )
		return false;
	return false;
}
bool CUI_ID_FRAME_OnlineAward2::ID_LISTIMG_HotkeyOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_OnlineAward2 )
		return false;
	return false;
}
bool CUI_ID_FRAME_OnlineAward2::ID_LISTIMG_HotkeyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_OnlineAward2 )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_OnlineAward2::ID_BUTTON_GetAwardOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_OnlineAward2 )
		return false;
 	MsgOnLineRewardReq msg;
 	msg.nIndex = m_shRewardIndex;
 	//msg.uchType = MsgOnLineRewardReq::Type_NewChar;
 	GettheNetworkInput().SendMsg(&msg);
 	m_pID_BUTTON_GetAward->SetEnable(false);
	m_pID_PROGRESS_Effect->SetVisable(false);
	m_pID_PROGRESS_Effect2->SetVisable(false);
	// 作为保护，否则界面有可能永远不能关闭 [12/20/2010 zhangjiayi]
	if (!thePlayerRole.IsDie())
		m_pID_BUTTON_CLOSE->SetEnable( true );
	return true;
}
// Button
bool CUI_ID_FRAME_OnlineAward2::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	COnlineReward::Instance().SetCurrentStatus( COnlineReward::ORS_CLICKOK );
	COnlineReward::Instance().SetUpdateOnlineReward();
	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_OnlineAward2::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

	// 装载UI
bool CUI_ID_FRAME_OnlineAward2::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\OnlineAward2.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\OnlineAward2.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_OnlineAward2::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_OnlineAward2, s_CUI_ID_FRAME_OnlineAward2OnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_OnlineAward2, s_CUI_ID_FRAME_OnlineAward2OnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_OnlineAward2, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_OnlineAward2ID_LISTIMG_HotkeyOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_OnlineAward2, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_OnlineAward2ID_LISTIMG_HotkeyOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_OnlineAward2, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_OnlineAward2ID_LISTIMG_HotkeyOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_OnlineAward2, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_OnlineAward2ID_LISTIMG_HotkeyOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_OnlineAward2, ID_BUTTON_GetAward, s_CUI_ID_FRAME_OnlineAward2ID_BUTTON_GetAwardOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_OnlineAward2, ID_BUTTON_OK, s_CUI_ID_FRAME_OnlineAward2ID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_OnlineAward2, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_OnlineAward2ID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_OnlineAward2 = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_OnlineAward2 );
	m_pID_PICTURE_PageWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_OnlineAward2, ID_PICTURE_PageWall );
	m_pID_LISTIMG_Hotkey = (ControlListImage*)theUiManager.FindControl( ID_FRAME_OnlineAward2, ID_LISTIMG_Hotkey );
	m_pID_TEXT_Word = (ControlText*)theUiManager.FindControl( ID_FRAME_OnlineAward2, ID_TEXT_Word );
	m_pID_BUTTON_GetAward = (ControlButton*)theUiManager.FindControl( ID_FRAME_OnlineAward2, ID_BUTTON_GetAward );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_OnlineAward2, ID_BUTTON_OK );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_OnlineAward2, ID_BUTTON_CLOSE );
	m_pID_TEXT_Tips = (ControlText*)theUiManager.FindControl( ID_FRAME_OnlineAward2, ID_TEXT_Tips );
	m_pID_PROGRESS_Effect = (ControlProgress*)theUiManager.FindControl( ID_FRAME_OnlineAward2, ID_PROGRESS_Effect );
	m_pID_PROGRESS_Effect2 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_OnlineAward2, ID_PROGRESS_Effect2 );
	//m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_OnlineAward2, ID_PICTURE_ItemWall );
	assert( m_pID_FRAME_OnlineAward2 );
	assert( m_pID_PICTURE_PageWall );
	assert( m_pID_LISTIMG_Hotkey );
	assert( m_pID_TEXT_Word );
	assert( m_pID_BUTTON_GetAward );
	//assert( m_pID_PICTURE_ItemWall );
	assert( m_pID_PROGRESS_Effect );
	assert( m_pID_PROGRESS_Effect2 );

	m_pID_FRAME_OnlineAward2->enableEscKey( false );
	m_pID_FRAME_OnlineAward2->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);

	m_pID_FRAME_OnlineAward2->SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_OnlineAward2::_UnLoadUI()
{

	m_pID_FRAME_OnlineAward2 = NULL;
	m_pID_PICTURE_PageWall = NULL;
	m_pID_LISTIMG_Hotkey = NULL;
	m_pID_TEXT_Word = NULL;
	m_pID_BUTTON_GetAward = NULL;
// 	m_pID_PICTURE_ItemWall = NULL;
	m_pID_PROGRESS_Effect = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\OnlineAward2.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_OnlineAward2::_IsVisable()
{
	if( !m_pID_FRAME_OnlineAward2 )
		return false;
	return m_pID_FRAME_OnlineAward2->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_OnlineAward2::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_OnlineAward2 )
		return;
	m_pID_FRAME_OnlineAward2->SetVisable( bVisable );
}

// 显示展示界面(多个text，button为确定）
void CUI_ID_FRAME_OnlineAward2::ShowConfirmAward( int nIndex, const OnLineRewardConfig::OnLineReward* pReward )
{
	if( !pReward )
		return;

	SetVisable( true );
	m_pID_BUTTON_OK->SetVisable( true );
	m_pID_TEXT_Tips->SetVisable( true );
	m_pID_BUTTON_CLOSE->SetEnable( false );
	m_pID_BUTTON_GetAward->SetVisable( false );
	m_pID_PROGRESS_Effect->SetVisable(false);
	m_pID_PROGRESS_Effect2->SetVisable(false);
	// 填充奖励 
	ShowOnlineReward( nIndex, pReward );
	// text提示
	DWORD dwRemainTime = pReward->dwCountDown * 60000;
// 	int second = dwRemainTime * 1.f / 1000;
// 	int minute = second * 1.f / 60;
// 	int hour = minute * 1.f / 24;
// 	minute -= hour * 24;
// 	if( second * 1000 < dwRemainTime )
// 		++second;
	int second =  min( 60, pReward->dwCountDown * 60 );
	int minute = min( 60 , ( pReward->dwCountDown * 60 - second ) / 60 );
	int hour = ( pReward->dwCountDown - minute ) / 60;

	char szTime[MAX_PATH] = {0};
	if( hour > 0 )
		MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s%d%s%d%s", hour, theXmlString.GetString(eTimeUnit_Hour), minute, theXmlString.GetString(eTimeUnit_Minute),
		second, theXmlString.GetString(eTimeUnit_Second));
	else if( minute > 0 )
		MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s%d%s", minute, theXmlString.GetString(eTimeUnit_Minute), second, theXmlString.GetString(eTimeUnit_Second));
	else
		MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d%s", second, theXmlString.GetString(eTimeUnit_Second));

	char szStr[MAX_PATH] = {0};
	MeSprintf_s(szStr, sizeof(szStr)/sizeof(char) - 1, theXmlString.GetString(eText_OnlineAwardPretime), szTime );
	m_pID_TEXT_Tips->SetText( szStr );
}
// 显示领取界面（没有text，button为领取）
void CUI_ID_FRAME_OnlineAward2::ShowGetAward()
{
	SetVisable( true );
	m_pID_BUTTON_GetAward->SetVisable( true );
	m_pID_PROGRESS_Effect->SetVisable(true);
	m_pID_PROGRESS_Effect2->SetVisable(true);
	m_pID_BUTTON_OK->SetVisable( false );
	m_pID_TEXT_Tips->SetVisable( false );
}

bool CUI_ID_FRAME_OnlineAward2::ShowOnlineReward( short index, const OnLineRewardConfig::OnLineReward* pReward )
{
	if( !pReward )
		return false;

	ClearList();
	bool bRet = false;
	for( int i = 0 ; i < OnLineRewardConfig::EConstDefine_RewardItemMaxSize; ++ i )
	{
		if( pReward->nItemID[i] == InvalidLogicNumber )
			continue;
		 bRet = SetOnlineReward(index, pReward->nItemID[i], pReward->nCount[i]) | bRet;
	}	
	return bRet;
}

bool CUI_ID_FRAME_OnlineAward2::SetOnlineReward( short index, unsigned short usItemID, unsigned short usItemCount )
{
	if( index < 0 )
		return false;
	m_shRewardIndex = index;
	m_usItemID = usItemID;
	m_usItemCount = usItemCount;

	ItemDefine::SItemCommon *pItemCommon = NULL;
	pItemCommon = GettheItemDetail().GetItemByID( usItemID );

	if( !pItemCommon )
		return false;

    SetVisable( true );
    if( !m_pID_FRAME_OnlineAward2 )
        return false;

	ControlIconDrag::S_ListImg stItem;
	stItem.SetData( usItemID, usItemCount );
	//m_pID_LISTIMG_Hotkey->Clear();
	m_pID_LISTIMG_Hotkey->SetItem( &stItem );

	DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
	char strItemColor[MAX_PATH] = {0};
	sprintf(strItemColor, "{#%x=%s#}", dwColor, pItemCommon->GetItemName());

	char szStr[MAX_PATH] = {0};
	sprintf_s(szStr, MAX_PATH-1, theXmlString.GetString(eText_OnlineAward2), m_shRewardIndex+1, strItemColor);
	m_pID_TEXT_Word->SetText(szStr);

	//m_pID_BUTTON_GetAward->SetEnable(true);
	
	return true;
}
void CUI_ID_FRAME_OnlineAward2::ClearList()
{
	if( !m_pID_FRAME_OnlineAward2 )
		return;
	m_pID_LISTIMG_Hotkey->Clear();
}
void CUI_ID_FRAME_OnlineAward2::SetButGetAwardEnable(bool bEnable)
{
    if(!m_pID_FRAME_OnlineAward2)
        return;

    m_pID_BUTTON_GetAward->SetEnable(bEnable);
	m_pID_PROGRESS_Effect->SetVisable(bEnable);
	m_pID_PROGRESS_Effect2->SetVisable(bEnable);
	m_pID_BUTTON_CLOSE->SetEnable( !bEnable );
}

// void CUI_ID_FRAME_OnlineAward2::DisplaySparkEffect()
// {
//     if( !IsUILoad() )
//         return;
// 
//     if( !m_pID_BUTTON_GetAward->IsVisable() || !m_pID_BUTTON_GetAward->IsEnable() )
//         return;
// 
//     if( m_pID_BUTTON_GetAward->PtInObject( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y, false ) )
//         return;
// 
//     S_ButtonData *pstData = ( S_ButtonData* )m_pID_BUTTON_GetAward->GetData();
//     
//     DWORD dwCurrentTime = HQ_TimeGetTime();
//     if( dwCurrentTime - m_dwElapse > SPARK_CHANGE_TIME )
//     {
//         m_dwElapse = dwCurrentTime;
//         m_bChange = !m_bChange;
//         if( m_bChange )
//             m_pID_BUTTON_GetAward->SetPic( &pstData->m_stMoveOnPic );
//         else
//             m_pID_BUTTON_GetAward->SetPic( &pstData->m_stBackPic );
//     }
// }
