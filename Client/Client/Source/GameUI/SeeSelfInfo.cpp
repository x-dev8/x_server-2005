/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面SeeSelfInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SeeSelfInfo.h"
#include "SeeBasePropertyBGFrame.h"
CUI_ID_FRAME_SeeSelfInfo s_CUI_ID_FRAME_SeeSelfInfo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SeeSelfInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SeeSelfInfo, OnFrameRender )
CUI_ID_FRAME_SeeSelfInfo::CUI_ID_FRAME_SeeSelfInfo()
{
	// Member
	m_pID_FRAME_SeeSelfInfo = NULL;
	m_pID_TEXT_Age = NULL;
	m_pID_TEXT_City = NULL;
	m_pID_TEXT_Job = NULL;
	m_pID_TEXT_QQ = NULL;
	m_pID_TEXT_Desc = NULL;
	m_pID_TEXT_Like = NULL;
	m_pID_TEXT_Mail = NULL;
	m_pID_TEXT_MSN = NULL;
	m_pID_TEXT_NickName = NULL;
	m_pID_TEXT_Http = NULL;
	m_pID_TEXT_Animal = NULL;
	m_pID_TEXT_Constellation = NULL;
	m_pID_TEXT_BirthMonth = NULL;
	m_pID_TEXT_BirthDay = NULL;
	m_pID_TEXT_Province = NULL;
	m_pID_TEXT_Sex = NULL;

}
// Frame
bool CUI_ID_FRAME_SeeSelfInfo::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_SeeSelfInfo::OnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SeeSelfInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SeeSelfInfo.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SeeSelfInfo.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SeeSelfInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SeeSelfInfo, s_CUI_ID_FRAME_SeeSelfInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SeeSelfInfo, s_CUI_ID_FRAME_SeeSelfInfoOnFrameRender );

	m_pID_FRAME_SeeSelfInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SeeSelfInfo );
	m_pID_TEXT_Age = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_Age );
	m_pID_TEXT_City = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_City );
	m_pID_TEXT_Job = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_Job );
	m_pID_TEXT_QQ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_QQ );
	m_pID_TEXT_Desc = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_Desc );
	m_pID_TEXT_Like = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_Like );
	m_pID_TEXT_Mail = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_Mail );
	m_pID_TEXT_MSN = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_MSN );
	m_pID_TEXT_NickName = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_NickName );
	m_pID_TEXT_Http = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_Http );
	m_pID_TEXT_Animal = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_Animal );
	m_pID_TEXT_Constellation = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_Constellation );
	m_pID_TEXT_BirthMonth = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_BirthMonth );
	m_pID_TEXT_BirthDay = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_BirthDay );
	m_pID_TEXT_Province = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_Province );
	m_pID_TEXT_Sex = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSelfInfo, ID_TEXT_Sex );

	assert( m_pID_FRAME_SeeSelfInfo );
	assert( m_pID_TEXT_Age );
	assert( m_pID_TEXT_City );
	assert( m_pID_TEXT_Job );
	assert( m_pID_TEXT_QQ );
	assert( m_pID_TEXT_Desc );
	assert( m_pID_TEXT_Like );
	assert( m_pID_TEXT_Mail );
	assert( m_pID_TEXT_MSN );
	assert( m_pID_TEXT_NickName );
	assert( m_pID_TEXT_Http );
	assert( m_pID_TEXT_Animal );
	assert( m_pID_TEXT_Constellation );
	assert( m_pID_TEXT_BirthMonth );
	assert( m_pID_TEXT_BirthDay );
	assert( m_pID_TEXT_Province );
	assert( m_pID_TEXT_Sex );
	m_pID_FRAME_SeeSelfInfo->SetFather(s_CUI_ID_FRAME_SeeBasePropertyBGFrame.GetFrame());
	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SeeSelfInfo::_UnLoadUI()
{
	m_pID_FRAME_SeeSelfInfo = NULL;
	m_pID_TEXT_Age = NULL;
	m_pID_TEXT_City = NULL;
	m_pID_TEXT_Job = NULL;
	m_pID_TEXT_QQ = NULL;
	m_pID_TEXT_Desc = NULL;
	m_pID_TEXT_Like = NULL;
	m_pID_TEXT_Mail = NULL;
	m_pID_TEXT_MSN = NULL;
	m_pID_TEXT_NickName = NULL;
	m_pID_TEXT_Http = NULL;
	m_pID_TEXT_Animal = NULL;
	m_pID_TEXT_Constellation = NULL;
	m_pID_TEXT_BirthMonth = NULL;
	m_pID_TEXT_BirthDay = NULL;
	m_pID_TEXT_Province = NULL;
	m_pID_TEXT_Sex = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SeeSelfInfo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SeeSelfInfo::_IsVisable()
{
	if ( !m_pID_FRAME_SeeSelfInfo )
		return false;
	return m_pID_FRAME_SeeSelfInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SeeSelfInfo::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_SeeSelfInfo )
		return ;
	m_pID_FRAME_SeeSelfInfo->SetVisable( bVisable );
}
