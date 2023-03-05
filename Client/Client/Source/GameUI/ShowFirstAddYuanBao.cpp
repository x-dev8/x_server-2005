/********************************************************************
	Created by UIEditor.exe
	FileName: D:\SVNClient\sg_pro\3Guo_Main\FullClient\Data\Ui\ShowFirstAddYuanBao.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ShowFirstAddYuanBao.h"
#include "FirstAddYuanBao.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "PlayerRole.h"
//#include "YuanBaoTotleConfig.h"
CUI_ID_FRAME_ShowFirstAddYuanbao s_CUI_ID_FRAME_ShowFirstAddYuanbao;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ShowFirstAddYuanbao, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ShowFirstAddYuanbao, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShowFirstAddYuanbao, ID_BUTTON_OpenFirstAddYuanBaoOnButtonClick )
CUI_ID_FRAME_ShowFirstAddYuanbao::CUI_ID_FRAME_ShowFirstAddYuanbao()
{
	// Member
	m_pID_FRAME_ShowFirstAddYuanbao = NULL;
	m_pID_BUTTON_OpenFirstAddYuanBao = NULL;
	m_NowOnlyValue = 0;
}
// Frame
bool CUI_ID_FRAME_ShowFirstAddYuanbao::OnFrameRun()
{
	Update();
	return true;
}
bool CUI_ID_FRAME_ShowFirstAddYuanbao::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ShowFirstAddYuanbao::ID_BUTTON_OpenFirstAddYuanBaoOnButtonClick( ControlObject* pSender )
{
	if(m_NowOnlyValue == 0)
	{
		SetVisable(false);
		s_CUI_ID_FRAME_FirstAddYuanBao.SetVisable(false);
		return true;
	}
	s_CUI_ID_FRAME_FirstAddYuanBao.OnShow(m_NowOnlyValue);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_ShowFirstAddYuanbao::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ShowFirstAddYuanBao.MEUI",true,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ShowFirstAddYuanBao.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ShowFirstAddYuanbao::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ShowFirstAddYuanbao, s_CUI_ID_FRAME_ShowFirstAddYuanbaoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ShowFirstAddYuanbao, s_CUI_ID_FRAME_ShowFirstAddYuanbaoOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ShowFirstAddYuanbao, ID_BUTTON_OpenFirstAddYuanBao, s_CUI_ID_FRAME_ShowFirstAddYuanbaoID_BUTTON_OpenFirstAddYuanBaoOnButtonClick );

	m_pID_FRAME_ShowFirstAddYuanbao = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ShowFirstAddYuanbao );
	m_pID_BUTTON_OpenFirstAddYuanBao = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShowFirstAddYuanbao, ID_BUTTON_OpenFirstAddYuanBao );
	assert( m_pID_FRAME_ShowFirstAddYuanbao );
	assert( m_pID_BUTTON_OpenFirstAddYuanBao );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ShowFirstAddYuanbao::_UnLoadUI()
{
	m_pID_FRAME_ShowFirstAddYuanbao = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ShowFirstAddYuanBao.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ShowFirstAddYuanbao::_IsVisable()
{
	return m_pID_FRAME_ShowFirstAddYuanbao->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ShowFirstAddYuanbao::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_ShowFirstAddYuanbao->SetVisable( bVisable );
}
void CUI_ID_FRAME_ShowFirstAddYuanbao::Update()
{
	static unsigned int ShowAddYuanBaoLogTime = 0;
	if(ShowAddYuanBaoLogTime != 0 && HQ_TimeGetTime() - ShowAddYuanBaoLogTime < 1000)
		return;//1秒更新一次
	ShowAddYuanBaoLogTime = HQ_TimeGetTime();
	if( !theHeroGame.GetPlayerMgr()->GetMe())
	{
		m_NowOnlyValue = 0;
		SetVisable(false);
		s_CUI_ID_FRAME_FirstAddYuanBao.SetVisable(false);
		return;//隐藏
	}
	//if(!YuanBaoTotleConfig::Instance().IsCheckCanShowOnlyValue(thePlayerRole.GetYuanBaoStates(),m_NowOnlyValue))
	//	m_NowOnlyValue = 0;
//	if(m_NowOnlyValue == 0)
//	{
//		unsigned int OnlyValue = YuanBaoTotleConfig::Instance().GetOnlyValue(thePlayerRole.GetYuanBaoTotle(),thePlayerRole.GetYuanBaoStates());
//		if(OnlyValue == 0)
//		{
//			m_NowOnlyValue = 0;
//			SetVisable(false);
//			s_CUI_ID_FRAME_FirstAddYuanBao.SetVisable(false);
//			return;//隐藏
//		}
//		m_NowOnlyValue = OnlyValue;
//		if(!IsVisable())
//			SetVisable(true);
//	}
//	else
//	{
//		if(!IsVisable())
//			SetVisable(true);
//	}
}