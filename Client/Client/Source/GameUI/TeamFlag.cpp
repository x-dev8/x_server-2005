/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (22)\TeamFlag.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TeamFlag.h"

CUI_ID_FRAME_TeamFlag s_CUI_ID_FRAME_TeamFlag;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TeamFlag, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TeamFlag, OnFrameRender )
CUI_ID_FRAME_TeamFlag::CUI_ID_FRAME_TeamFlag()
{
	// Member
	m_pID_FRAME_TeamFlag = NULL;
	m_pID_PICTURE_flag = NULL;

}
// Frame
bool CUI_ID_FRAME_TeamFlag::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_TeamFlag::OnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_TeamFlag::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TeamFlag.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TeamFlag.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TeamFlag::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TeamFlag, s_CUI_ID_FRAME_TeamFlagOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TeamFlag, s_CUI_ID_FRAME_TeamFlagOnFrameRender );

	m_pID_FRAME_TeamFlag = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TeamFlag );
	m_pID_PICTURE_flag = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamFlag, ID_PICTURE_flag );

	assert( m_pID_FRAME_TeamFlag );
	assert( m_pID_PICTURE_flag );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TeamFlag::_UnLoadUI()
{
	m_pID_FRAME_TeamFlag = NULL;
	m_pID_PICTURE_flag = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TeamFlag.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TeamFlag::_IsVisable()
{
	if ( !m_pID_FRAME_TeamFlag )
		return false;
	return m_pID_FRAME_TeamFlag->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TeamFlag::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TeamFlag )
		return;
	m_pID_FRAME_TeamFlag->SetVisable( bVisable );
}
