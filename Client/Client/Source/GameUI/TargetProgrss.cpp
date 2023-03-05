/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\Turbo\Program\trunk\Bin\Client\Data\Ui\TargetProgrss.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TargetProgrss.h"

CUI_ID_FRAME_TargetProgrss s_CUI_ID_FRAME_TargetProgrss;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TargetProgrss, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TargetProgrss, OnFrameRender )
CUI_ID_FRAME_TargetProgrss::CUI_ID_FRAME_TargetProgrss()
{
	// Member
	m_pID_FRAME_TargetProgrss = NULL;
	m_pID_CASTINGBAR_Intermit = NULL;
	m_pID_PROGRESS = NULL;
	m_pID_TEXT_PROGRESSNAME = NULL;
	m_pID_CASTINGBAR_BORDER = NULL;
	m_pID_CASTINGBAR_Full = NULL;

}
// Frame
bool CUI_ID_FRAME_TargetProgrss::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_TargetProgrss::OnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_TargetProgrss::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TargetProgrss.MEUI" ,false, UI_Render_LayerFirst );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TargetProgrss.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
void CUI_ID_FRAME_TargetProgrss::SetProgressValue(int nValue)
{
	if (m_pID_PROGRESS)
	{
		 m_pID_PROGRESS->SetValue(nValue);
	}	
}
void CUI_ID_FRAME_TargetProgrss::SetProgressText(const char* strText)
{
	if (m_pID_TEXT_PROGRESSNAME)
	{
		m_pID_TEXT_PROGRESSNAME->SetText(strText);
	}	
}
// 关连控件
bool CUI_ID_FRAME_TargetProgrss::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TargetProgrss, s_CUI_ID_FRAME_TargetProgrssOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TargetProgrss, s_CUI_ID_FRAME_TargetProgrssOnFrameRender );

	m_pID_FRAME_TargetProgrss = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TargetProgrss );
	m_pID_CASTINGBAR_Intermit = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TargetProgrss, ID_CASTINGBAR_Intermit );
	m_pID_PROGRESS = (ControlProgress*)theUiManager.FindControl( ID_FRAME_TargetProgrss, ID_PROGRESS );
	m_pID_TEXT_PROGRESSNAME = (ControlText*)theUiManager.FindControl( ID_FRAME_TargetProgrss, ID_TEXT_PROGRESSNAME );
	m_pID_CASTINGBAR_BORDER = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TargetProgrss, ID_CASTINGBAR_BORDER );
	m_pID_CASTINGBAR_Full = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TargetProgrss, ID_CASTINGBAR_Full );

	assert( m_pID_FRAME_TargetProgrss );
	assert( m_pID_CASTINGBAR_Intermit );
	assert( m_pID_CASTINGBAR_Full );
	assert( m_pID_CASTINGBAR_BORDER );

	assert( m_pID_PROGRESS );
	assert( m_pID_TEXT_PROGRESSNAME );
	
	m_pID_FRAME_TargetProgrss->SetFadeInorFadeOut(true);
	m_pID_CASTINGBAR_Full->SetVisable(false);
	m_pID_CASTINGBAR_BORDER->SetVisable(false);
	m_pID_CASTINGBAR_Intermit->SetVisable(false);
	m_pID_PROGRESS->SetVisable(false);
	SetVisable(false);
	return true;
}
void CUI_ID_FRAME_TargetProgrss::InitializeAtEnterWorld()
{
	_SetVisable( false );
}
// 卸载UI
bool CUI_ID_FRAME_TargetProgrss::_UnLoadUI()
{
	m_pID_FRAME_TargetProgrss = NULL;
	m_pID_CASTINGBAR_Intermit = NULL;
	m_pID_PROGRESS = NULL;
	m_pID_TEXT_PROGRESSNAME = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TargetProgrss.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TargetProgrss::_IsVisable()
{
	if ( !m_pID_FRAME_TargetProgrss )
		return false;
	return m_pID_FRAME_TargetProgrss->IsVisable();
}
void CUI_ID_FRAME_TargetProgrss::Finish()
{
	m_pID_CASTINGBAR_BORDER->SetVisable(false);
	m_pID_CASTINGBAR_Full->SetVisable(true);
	SetVisable(false);
}
void CUI_ID_FRAME_TargetProgrss::BreakProgress()
{
	m_pID_CASTINGBAR_BORDER->SetVisable(false);
	m_pID_CASTINGBAR_Intermit->SetVisable(true);
	SetVisable(false);
}
void CUI_ID_FRAME_TargetProgrss::Reset()
{
	m_pID_CASTINGBAR_Intermit->SetVisable(false);
	m_pID_CASTINGBAR_Full->SetVisable(false);
	m_pID_CASTINGBAR_BORDER->SetVisable(false);
	m_pID_PROGRESS->SetVisable(false);
	SetVisable(false);
}
// 设置是否可视
void CUI_ID_FRAME_TargetProgrss::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TargetProgrss )
		return ;
	if (bVisable)
	{
		m_pID_CASTINGBAR_Intermit->SetVisable(false);
		m_pID_CASTINGBAR_Full->SetVisable(false);
		m_pID_CASTINGBAR_BORDER->SetVisable(true);
		m_pID_PROGRESS->SetVisable(true);
	}	
	
	m_pID_FRAME_TargetProgrss->SetVisable( bVisable );
}
