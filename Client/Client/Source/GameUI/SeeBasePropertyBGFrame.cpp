/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\SeeBasePropertyBGFrame.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SeeBasePropertyBGFrame.h"
#include "SeekEquip.h"
#include "SeeSelfInfo.h"

CUI_ID_FRAME_SeeBasePropertyBGFrame s_CUI_ID_FRAME_SeeBasePropertyBGFrame;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SeeBasePropertyBGFrame, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SeeBasePropertyBGFrame, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeBasePropertyBGFrame, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeBasePropertyBGFrame, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SeeBasePropertyBGFrame, ID_CHECKBOX_ShuXingOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SeeBasePropertyBGFrame, ID_CHECKBOX_ZiLiaoOnCheckBoxCheck )
CUI_ID_FRAME_SeeBasePropertyBGFrame::CUI_ID_FRAME_SeeBasePropertyBGFrame()
{
	// Member
	m_pID_FRAME_SeeBasePropertyBGFrame = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_CHECKBOX_ShuXing = NULL;
	m_pID_CHECKBOX_ZiLiao = NULL;
	m_pID_PICTURE_ShuXing = NULL;
	m_pID_PICTURE_ZiLiao = NULL;

}
// Frame
bool CUI_ID_FRAME_SeeBasePropertyBGFrame::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_SeeBasePropertyBGFrame::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeBasePropertyBGFrame::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SeeBasePropertyBGFrame )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SeeBasePropertyBGFrame::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SeeBasePropertyBGFrame )
		return false;
	return true;
}
// CheckBox
void CUI_ID_FRAME_SeeBasePropertyBGFrame::ID_CHECKBOX_ShuXingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_SeeBasePropertyBGFrame )
		return;
	m_pID_CHECKBOX_ShuXing->SetCheck(true);
	m_pID_CHECKBOX_ZiLiao->SetCheck(false);
	s_CUI_ID_FRAME_SeekEqup.SetVisable(true);
	s_CUI_ID_FRAME_SeeSelfInfo.SetVisable(false);
	m_pID_PICTURE_ShuXing->SetVisable(true);
	m_pID_PICTURE_ZiLiao->SetVisable(false);
}
// CheckBox
void CUI_ID_FRAME_SeeBasePropertyBGFrame::ID_CHECKBOX_ZiLiaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_SeeBasePropertyBGFrame )
		return;
	m_pID_CHECKBOX_ShuXing->SetCheck(false);
	m_pID_CHECKBOX_ZiLiao->SetCheck(true);
	s_CUI_ID_FRAME_SeekEqup.SetVisable(false);
	s_CUI_ID_FRAME_SeeSelfInfo.SetVisable(true);
	m_pID_PICTURE_ShuXing->SetVisable(false);
	m_pID_PICTURE_ZiLiao->SetVisable(true);
}

// 装载UI
bool CUI_ID_FRAME_SeeBasePropertyBGFrame::_LoadUI()
{
	s_CUI_ID_FRAME_SeeSelfInfo._LoadUI();
	s_CUI_ID_FRAME_SeekEqup._LoadUI();
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SeeBasePropertyBGFrame.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SeeBasePropertyBGFrame.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SeeBasePropertyBGFrame::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SeeBasePropertyBGFrame, s_CUI_ID_FRAME_SeeBasePropertyBGFrameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SeeBasePropertyBGFrame, s_CUI_ID_FRAME_SeeBasePropertyBGFrameOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SeeBasePropertyBGFrame, ID_BUTTON_HELP, s_CUI_ID_FRAME_SeeBasePropertyBGFrameID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeBasePropertyBGFrame, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SeeBasePropertyBGFrameID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SeeBasePropertyBGFrame, ID_CHECKBOX_ShuXing, s_CUI_ID_FRAME_SeeBasePropertyBGFrameID_CHECKBOX_ShuXingOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SeeBasePropertyBGFrame, ID_CHECKBOX_ZiLiao, s_CUI_ID_FRAME_SeeBasePropertyBGFrameID_CHECKBOX_ZiLiaoOnCheckBoxCheck );

	m_pID_FRAME_SeeBasePropertyBGFrame = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SeeBasePropertyBGFrame );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeBasePropertyBGFrame, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeBasePropertyBGFrame, ID_BUTTON_CLOSE );
	m_pID_CHECKBOX_ShuXing = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SeeBasePropertyBGFrame, ID_CHECKBOX_ShuXing );
	m_pID_CHECKBOX_ZiLiao = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SeeBasePropertyBGFrame, ID_CHECKBOX_ZiLiao );
	m_pID_PICTURE_ShuXing = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeBasePropertyBGFrame, ID_PICTURE_ShuXing );
	m_pID_PICTURE_ZiLiao = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeBasePropertyBGFrame, ID_PICTURE_ZiLiao );

	assert( m_pID_FRAME_SeeBasePropertyBGFrame );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_CHECKBOX_ShuXing );
	assert( m_pID_CHECKBOX_ZiLiao );
	assert( m_pID_PICTURE_ShuXing );
	assert( m_pID_PICTURE_ZiLiao );

	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SeeBasePropertyBGFrame::_UnLoadUI()
{
	s_CUI_ID_FRAME_SeeSelfInfo._UnLoadUI();
	s_CUI_ID_FRAME_SeekEqup._UnLoadUI();
	m_pID_FRAME_SeeBasePropertyBGFrame = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_CHECKBOX_ShuXing = NULL;
	m_pID_CHECKBOX_ZiLiao = NULL;
	m_pID_PICTURE_ShuXing = NULL;
	m_pID_PICTURE_ZiLiao = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SeeBasePropertyBGFrame.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SeeBasePropertyBGFrame::_IsVisable()
{
	if ( !m_pID_FRAME_SeeBasePropertyBGFrame )
		return false;
	return m_pID_FRAME_SeeBasePropertyBGFrame->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SeeBasePropertyBGFrame::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_SeeBasePropertyBGFrame )
		return ;
	m_pID_FRAME_SeeBasePropertyBGFrame->SetVisable( bVisable );
	if (bVisable)
	{
		m_pID_CHECKBOX_ShuXing->SetCheck(true);
		m_pID_PICTURE_ShuXing->SetVisable(true);
		m_pID_PICTURE_ZiLiao->SetVisable(false);
		m_pID_CHECKBOX_ZiLiao->SetCheck(false);
		s_CUI_ID_FRAME_SeekEqup.SetVisable(true);
		s_CUI_ID_FRAME_SeeSelfInfo.SetVisable(false);
	}
	
}
