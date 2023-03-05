/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\新十X关\LuckAward.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "LuckAwardUI.h"
#include "LuckGameUI.h"

CUI_ID_FRAME_LuckAward s_CUI_ID_FRAME_LuckAward;
MAP_FRAME_RUN( s_CUI_ID_FRAME_LuckAward, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_LuckAward, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LuckAward, ID_BUTTON_GetAwardsOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LuckAward, ID_BUTTON_LeftAwardOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LuckAward, ID_BUTTON_RightAwardOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LuckAward, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_LuckAward::CUI_ID_FRAME_LuckAward()
{
	// Member
	m_pID_FRAME_LuckAward = NULL;
	m_pID_PICTURE_Background = NULL;
	m_pID_BUTTON_GetAwards = NULL;
	m_pID_BUTTON_LeftAward = NULL;
	m_pID_BUTTON_RightAward = NULL;
	m_pID_LISTIMG_Award = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_CLOSE = NULL;

}
// Frame
bool CUI_ID_FRAME_LuckAward::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_LuckAward::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_LuckAward::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_LuckAward)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_LuckAward::ID_BUTTON_GetAwardsOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_LuckAward)
		return false;
	if(!( ( thePlayerRole.GetMeTeamInfo() == 0 ) || thePlayerRole.IsTeamHeader() ) )
	 		return true;
	SendGetMsgToServer();
	return true;
}
// Button
bool CUI_ID_FRAME_LuckAward::ID_BUTTON_LeftAwardOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_LuckAward)
		return false;
	if( m_nRewardListBeginIndex >= m_pID_LISTIMG_Award->GetItemCnt() )
	{
		m_nRewardListBeginIndex -= m_pID_LISTIMG_Award->GetItemCnt();
		RefreshRewardList();
	}
	
	return true;
}
// Button
bool CUI_ID_FRAME_LuckAward::ID_BUTTON_RightAwardOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_LuckAward)
		return false;
	if( m_nRewardListBeginIndex < ( (int)m_aRewardIds.size() - m_pID_LISTIMG_Award->GetRowItemCnt() ) )
	{
		m_nRewardListBeginIndex += m_pID_LISTIMG_Award->GetItemCnt();
		RefreshRewardList();
	}
	return true;
}

// 装载UI
bool CUI_ID_FRAME_LuckAward::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\LuckAward.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\LuckAward.MEUI]失败")
			return false;
	}
	m_aRewardIds.clear();
	uchRewardType = 0;
	m_nRewardListBeginIndex = 0;
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_LuckAward::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_LuckAward, s_CUI_ID_FRAME_LuckAwardOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_LuckAward, s_CUI_ID_FRAME_LuckAwardOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_LuckAward, ID_BUTTON_GetAwards, s_CUI_ID_FRAME_LuckAwardID_BUTTON_GetAwardsOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LuckAward, ID_BUTTON_LeftAward, s_CUI_ID_FRAME_LuckAwardID_BUTTON_LeftAwardOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LuckAward, ID_BUTTON_RightAward, s_CUI_ID_FRAME_LuckAwardID_BUTTON_RightAwardOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LuckAward, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_LuckAwardID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_LuckAward = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_LuckAward );
	m_pID_PICTURE_Background = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LuckAward, ID_PICTURE_Background );
	m_pID_BUTTON_GetAwards = (ControlButton*)theUiManager.FindControl( ID_FRAME_LuckAward, ID_BUTTON_GetAwards );
	m_pID_BUTTON_LeftAward = (ControlButton*)theUiManager.FindControl( ID_FRAME_LuckAward, ID_BUTTON_LeftAward );
	m_pID_BUTTON_RightAward = (ControlButton*)theUiManager.FindControl( ID_FRAME_LuckAward, ID_BUTTON_RightAward );
	m_pID_LISTIMG_Award = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LuckAward, ID_LISTIMG_Award );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_LuckAward, ID_TEXT_Page );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_LuckAward, ID_BUTTON_CLOSE );
	assert( m_pID_FRAME_LuckAward );
	assert( m_pID_PICTURE_Background );
	assert( m_pID_BUTTON_GetAwards );
	assert( m_pID_BUTTON_LeftAward );
	assert( m_pID_BUTTON_RightAward );
	assert( m_pID_LISTIMG_Award );
	assert( m_pID_TEXT_Page );
	assert( m_pID_BUTTON_CLOSE );
	SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_LuckAward::_UnLoadUI()
{
	m_pID_FRAME_LuckAward = NULL;
	m_pID_PICTURE_Background = NULL;
	m_pID_BUTTON_GetAwards = NULL;
	m_pID_BUTTON_LeftAward = NULL;
	m_pID_BUTTON_RightAward = NULL;
	m_pID_LISTIMG_Award = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\LuckAward.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_LuckAward::_IsVisable()
{
    if(!m_pID_FRAME_LuckAward)
        return false;

	return m_pID_FRAME_LuckAward->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_LuckAward::_SetVisable( const bool bVisable )
{
    if(m_pID_FRAME_LuckAward)
	    m_pID_FRAME_LuckAward->SetVisable( bVisable );
}
void CUI_ID_FRAME_LuckAward::RefreshRewardList()
{
	if(!m_pID_FRAME_LuckAward)
		return;

	m_pID_LISTIMG_Award->Clear();	
	float fMultOrHalf = 1.f;
	if( uchRewardType == ECD_RandType_Half )
		fMultOrHalf = 0.5f;
	else if( uchRewardType == ECD_RandType_Double )
		fMultOrHalf = 2.f;
	for( int i = m_nRewardListBeginIndex ; i < m_aRewardIds.size() ; ++ i )
	{
		if( m_nRewardListBeginIndex < 0 )
			continue;
		if( m_pID_LISTIMG_Award->GetNullItem() == -1 )
			return;
		ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( m_aRewardIds[i].GetItemID() );
		if( !pCommon )
			continue;
		ControlIconDrag::S_ListImg listImg;
		int nCount = m_aRewardIds[i].GetValue();
		if( nCount != 1 )
			nCount *= fMultOrHalf;
		listImg.SetData( m_aRewardIds[i].GetItemID(), nCount, eIcon_Enable, true );
		m_pID_LISTIMG_Award->SetItem( &listImg );
	}
}
void CUI_ID_FRAME_LuckAward::AddReward( const RewardData& data )
{
	m_aRewardIds.push_back( data );
}
void CUI_ID_FRAME_LuckAward::SendGetMsgToServer()
{
	MsgLuckRewardReq msg;
	msg.uchType = MsgLuckRewardReq::ECD_Get;
	GettheNetworkInput().SendMsg( &msg );	
}