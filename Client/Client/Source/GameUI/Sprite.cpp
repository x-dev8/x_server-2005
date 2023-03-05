/********************************************************************
Created by UIEditor.exe
FileName: F:\project\Turbo\Bin\Client\Data\Ui\Sprite.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Sprite.h"
#include "XmlStringLanguage.h"
#include "FriendDlg.h"

CUI_ID_FRAME_Sprite s_CUI_ID_FRAME_Sprite;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Sprite, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Sprite, OnFrameRender )
CUI_ID_FRAME_Sprite::CUI_ID_FRAME_Sprite()
{
	// Member
	m_pID_FRAME_Sprite = NULL;
	m_pID_TEXT_Sprite = NULL;

}
// Frame
bool CUI_ID_FRAME_Sprite::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Sprite::OnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Sprite::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Sprite.MEUI",false,  UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Sprite.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Sprite::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Sprite, s_CUI_ID_FRAME_SpriteOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Sprite, s_CUI_ID_FRAME_SpriteOnFrameRender );

	m_pID_FRAME_Sprite = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Sprite );
	m_pID_TEXT_Sprite = (ControlText*)theUiManager.FindControl( ID_FRAME_Sprite, ID_TEXT_Sprite );
	assert( m_pID_FRAME_Sprite );
	assert( m_pID_TEXT_Sprite );

	if(m_pID_TEXT_Sprite)
	{
		m_pID_TEXT_Sprite->SetText(theXmlString.GetString(eText_friend_sprite_tips));
	}

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Sprite::_UnLoadUI()
{
	m_pID_FRAME_Sprite = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Sprite.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Sprite::_IsVisable()
{
	return m_pID_FRAME_Sprite->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Sprite::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_Sprite->SetVisable( bVisable );
}

void CUI_ID_FRAME_Sprite::Refresh()
{

}

void CUI_ID_FRAME_Sprite::ResetFramePos()
{
	if(!m_pID_FRAME_Sprite)
		return;

	//s_CUI_ID_FRAME_FriendView.SetVisable(true);
	RECT rcFriendDlg;
	s_CUI_ID_FRAME_Friend.GetFrame()->GetRealRect(&rcFriendDlg);

	RECT rcFriendView;
	m_pID_FRAME_Sprite->GetRealRect(&rcFriendView);

	int nWidth = rcFriendView.right - rcFriendView.left;
	int nHeight = rcFriendView.bottom - rcFriendView.top;

	RECT rcFriendViewNew;
	if (rcFriendDlg.left < nWidth)
	{
		rcFriendViewNew.left = rcFriendDlg.right; 
	}
	else
	{
		rcFriendViewNew.left = rcFriendDlg.left - nWidth; 
	}
	rcFriendViewNew.top = theUiManager.m_ptMoust.y;
	if (rcFriendViewNew.top + nHeight > rcFriendDlg.bottom)
	{
		rcFriendViewNew.top = rcFriendDlg.bottom - nHeight;
	}

	m_pID_FRAME_Sprite->SetPos(rcFriendViewNew.left,rcFriendViewNew.top);

	//int nPosX = 0,nPosY = 0;
	//int nWidth = 0,nHeight = 0;
	//nPosX = theUiManager.m_ptMoust.x;
	//nPosY = theUiManager.m_ptMoust.y;

	//nWidth = m_pID_FRAME_Sprite->GetWidth();
	//nHeight = m_pID_FRAME_Sprite->GetHeight();

	//if( nPosX + nWidth > SCREEN_WIDTH )
	//{
	//	nPosX = SCREEN_WIDTH - nWidth - 10;
	//}

	//if(nPosY + nHeight > SCREEN_HEIGHT)
	//{
	//	nPosY = SCREEN_HEIGHT - nHeight - 10;
	//}

	//m_pID_FRAME_Sprite->SetPos(nPosX,nPosY);

	//theUiManager.ToTop(m_pID_FRAME_Sprite);
}