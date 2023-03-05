/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (22)\CrowdCarryMain.cpp
*********************************************************************/
#include <assert.h>
#include "Common.h"
#include "NetworkInput.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "GameMain.h"
#include "MeUi/UiManager.h"
#include "CrowdCarryMain.h"

CUI_ID_FRAME_CrowdCarryMain s_CUI_ID_FRAME_CrowdCarryMain;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CrowdCarryMain, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CrowdCarryMain, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CrowdCarryMain, ID_BUTTON_LiveOnButtonClick )
CUI_ID_FRAME_CrowdCarryMain::CUI_ID_FRAME_CrowdCarryMain()
{
	// Member
	m_pID_FRAME_CrowdCarryMain = NULL;
	m_pID_TEXT_Amount = NULL;
	m_pID_BUTTON_Live = NULL;
	m_pID_TEXT_CZ = NULL;
	m_iTotalSets = 0;

}
void CUI_ID_FRAME_CrowdCarryMain::SetHostViewer()
{
	if ( !m_pID_FRAME_CrowdCarryMain )
		return;
	m_pID_TEXT_Amount->SetVisable(true);
	m_pID_BUTTON_Live->SetVisable(false);
	m_pID_TEXT_CZ->SetVisable(true);
}

void CUI_ID_FRAME_CrowdCarryMain::SetPassagerViewer()
{
	if ( !m_pID_FRAME_CrowdCarryMain )
		return;
	m_pID_TEXT_Amount->SetVisable(false);
	m_pID_BUTTON_Live->SetVisable(true);
	m_pID_TEXT_CZ->SetVisable(false);
}

void CUI_ID_FRAME_CrowdCarryMain::SetTotalSet( int totalNum )
{
	m_iTotalSets = totalNum;
}

void CUI_ID_FRAME_CrowdCarryMain::UpdateLeftSets( int passagerNum )
{
	if ( !m_pID_FRAME_CrowdCarryMain )
		return;

	if ( m_iTotalSets - passagerNum >= 0 )
	{
		char strTmp[128] = {0};
		MeSprintf( strTmp, sizeof(strTmp) - 1, "%d", m_iTotalSets - passagerNum );
		m_pID_TEXT_Amount->SetText( strTmp );
	}
	
}

// Frame
bool CUI_ID_FRAME_CrowdCarryMain::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_CrowdCarryMain::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_CrowdCarryMain::ID_BUTTON_LiveOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CrowdCarryMain )
		return false;

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if ( pMe )
	{
		MsgReqGotOffDrome msg;
		msg.driverId = pMe->GetCarrierPlayerID();
		msg.riderId = pMe->GetID();
		GettheNetworkInput().SendMsg(&msg);
	}

	return true;
}

// 装载UI
bool CUI_ID_FRAME_CrowdCarryMain::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CrowdCarryMain.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CrowdCarryMain.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CrowdCarryMain::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CrowdCarryMain, s_CUI_ID_FRAME_CrowdCarryMainOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CrowdCarryMain, s_CUI_ID_FRAME_CrowdCarryMainOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_CrowdCarryMain, ID_BUTTON_Live, s_CUI_ID_FRAME_CrowdCarryMainID_BUTTON_LiveOnButtonClick );

	m_pID_FRAME_CrowdCarryMain = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CrowdCarryMain );
	m_pID_TEXT_Amount = (ControlText*)theUiManager.FindControl( ID_FRAME_CrowdCarryMain, ID_TEXT_Amount );
	m_pID_BUTTON_Live = (ControlButton*)theUiManager.FindControl( ID_FRAME_CrowdCarryMain, ID_BUTTON_Live );
	m_pID_TEXT_CZ = (ControlText*)theUiManager.FindControl( ID_FRAME_CrowdCarryMain, ID_TEXT_CZ );

	assert( m_pID_FRAME_CrowdCarryMain );
	assert( m_pID_TEXT_Amount );
	assert( m_pID_BUTTON_Live );
	assert( m_pID_TEXT_CZ );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CrowdCarryMain::_UnLoadUI()
{
	m_pID_FRAME_CrowdCarryMain = NULL;
	m_pID_TEXT_Amount = NULL;
	m_pID_BUTTON_Live = NULL;
	m_pID_TEXT_CZ = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CrowdCarryMain.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CrowdCarryMain::_IsVisable()
{
	if ( !m_pID_FRAME_CrowdCarryMain )
		return false;
	return m_pID_FRAME_CrowdCarryMain->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CrowdCarryMain::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_CrowdCarryMain )
		return;
	m_pID_FRAME_CrowdCarryMain->SetVisable( bVisable );

	if (!bVisable)
	{
		if (theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe())
		{
			theHeroGame.GetPlayerMgr()->GetMe()->SetCarrierDriver(-1);
		}
	}
}
