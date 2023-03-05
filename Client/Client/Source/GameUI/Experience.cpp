/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\experience\Experience.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Experience.h"
#include "GameMain.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "XmlStringLanguage.h"
#include "Player.h"
#include "baseProperty.h"

CUI_ID_FRAME_Experience s_CUI_ID_FRAME_Experience;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Experience, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Experience, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Experience, ID_LIST_ExperienceListOnListSelectChange )
CUI_ID_FRAME_Experience::CUI_ID_FRAME_Experience()
{
	// Member
	m_pID_FRAME_Experience = NULL;
	m_pID_PICTURE_WallPaper = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_LIST_ExperienceList = NULL;

}
// Frame
bool CUI_ID_FRAME_Experience::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Experience::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_Experience::ID_LIST_ExperienceListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// 装载UI
bool CUI_ID_FRAME_Experience::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Experience.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Experience.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Experience::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Experience, s_CUI_ID_FRAME_ExperienceOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Experience, s_CUI_ID_FRAME_ExperienceOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_Experience, ID_LIST_ExperienceList, s_CUI_ID_FRAME_ExperienceID_LIST_ExperienceListOnListSelectChange );

	m_pID_FRAME_Experience = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Experience );
	m_pID_PICTURE_WallPaper = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Experience, ID_PICTURE_WallPaper );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_Experience, ID_TEXT_Explain );
	m_pID_LIST_ExperienceList = (ControlList*)theUiManager.FindControl( ID_FRAME_Experience, ID_LIST_ExperienceList );
	SetVisable( false );
	m_pID_FRAME_Experience->SetMsgHoldup(false);
	m_pID_LIST_ExperienceList->HaveSelBar( 0, 0 );
	assert( m_pID_FRAME_Experience );
	assert( m_pID_PICTURE_WallPaper );
	assert( m_pID_TEXT_Explain );
	assert( m_pID_LIST_ExperienceList );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Experience::_UnLoadUI()
{
	m_pID_FRAME_Experience = NULL;
	m_pID_PICTURE_WallPaper = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_LIST_ExperienceList = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Experience.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Experience::_IsVisable()
{
	if(!m_pID_FRAME_Experience)
		return false;
	return m_pID_FRAME_Experience->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Experience::_SetVisable( const bool bVisable )
{
	if (m_pID_FRAME_Experience == NULL)
	{
		return;
	}
	
	m_pID_FRAME_Experience->SetVisable( bVisable );
}
void CUI_ID_FRAME_Experience::Refresh()
{
	if (m_pID_FRAME_Experience == NULL)
	{
		return;
	}

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe )
		return;

	m_pID_LIST_ExperienceList->Clear();


	ControlList::S_List stItem;
	//char szBuff[256];
	// 功勋
	s_CUI_ID_FRAME_BaseProperty.SetTextGongXun( pMe->GetExploit() );
	// 声望
	s_CUI_ID_FRAME_BaseProperty.SetTextMingWang( pMe->GetReputation() );
}