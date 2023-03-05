/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\tian.peng\桌面\摆摊UI\摆摊UI\ChooseShopType.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ChooseShopType.h"
#include "SystemStallage.h"
#include "XmlStringLanguage.h"

CUI_ID_FRAME_ChooseShopType s_CUI_ID_FRAME_ChooseShopType;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ChooseShopType, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ChooseShopType, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChooseShopType, ID_BUTTON_OnlineOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChooseShopType, ID_BUTTON_LeaveOnButtonClick )
CUI_ID_FRAME_ChooseShopType::CUI_ID_FRAME_ChooseShopType():
m_pCallFun(NULL)
{
	// Member
	m_pID_FRAME_ChooseShopType = NULL;
	m_pID_BUTTON_Online = NULL;
	m_pID_BUTTON_Leave = NULL;
	m_pID_TEXT_Tip = NULL;

}
// Frame
bool CUI_ID_FRAME_ChooseShopType::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ChooseShopType::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ChooseShopType::ID_BUTTON_OnlineOnButtonClick( ControlObject* pSender )
{
	//CSystemStallage::Instance()->OpenStallageWindow(true);
	if(m_pCallFun)
	{
		(*m_pCallFun)(true);
	}

	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_ChooseShopType::ID_BUTTON_LeaveOnButtonClick( ControlObject* pSender )
{
	//CSystemStallage::Instance()->OpenStallageWindow(false);
	if(m_pCallFun)
	{
		(*m_pCallFun)(false);
	}
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_ChooseShopType::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ChooseShopType.MEUI", false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ChooseShopType.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ChooseShopType::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ChooseShopType, s_CUI_ID_FRAME_ChooseShopTypeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ChooseShopType, s_CUI_ID_FRAME_ChooseShopTypeOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ChooseShopType, ID_BUTTON_Online, s_CUI_ID_FRAME_ChooseShopTypeID_BUTTON_OnlineOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ChooseShopType, ID_BUTTON_Leave, s_CUI_ID_FRAME_ChooseShopTypeID_BUTTON_LeaveOnButtonClick );

	m_pID_FRAME_ChooseShopType = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ChooseShopType );
	m_pID_BUTTON_Online = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChooseShopType, ID_BUTTON_Online );
	m_pID_BUTTON_Leave = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChooseShopType, ID_BUTTON_Leave );
	m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_ChooseShopType, ID_TEXT_Tip );
	assert( m_pID_FRAME_ChooseShopType );
	assert( m_pID_BUTTON_Online );
	assert( m_pID_BUTTON_Leave );
	assert( m_pID_TEXT_Tip );

	if(m_pID_TEXT_Tip)
	{
		m_pID_TEXT_Tip->SetText(theXmlString.GetString(eText_Stall_Choose_Tip));
	}

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ChooseShopType::_UnLoadUI()
{
	m_pID_FRAME_ChooseShopType = NULL;
	m_pCallFun = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ChooseShopType.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ChooseShopType::_IsVisable()
{
	return m_pID_FRAME_ChooseShopType->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ChooseShopType::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_ChooseShopType->SetVisable( bVisable );
// 	if(bVisable)
// 	{
// 		theUiManager.ToTop(m_pID_FRAME_ChooseShopType);
// 	}

	if(!bVisable)
	{
		m_pCallFun = NULL;
	}

}

void CUI_ID_FRAME_ChooseShopType::Show(callfun pf)
{
	SetVisable(true);
	if(!m_pID_FRAME_ChooseShopType)
		return;

	m_pCallFun = pf;
	m_pID_FRAME_ChooseShopType->SetArrayMode(ArrayMode_Top);
}
