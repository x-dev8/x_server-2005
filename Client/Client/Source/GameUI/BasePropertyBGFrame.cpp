/********************************************************************
	Created by UIEditor.exe
	FileName: E:\trunk\Bin\Client\Data\Ui\BasePropertyBGFrame.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "BasePropertyBGFrame.h"
#include "BasePropertyBGFrame.h"
#include "SelfInfo.h"
#include "OtherInfo.h"
#include "baseProperty.h"
#include "HeroInfo.h"
#include "packet_interface.h"
#include "RankTitle.h"

CUI_ID_FRAME_BasePropertyBGFrame s_CUI_ID_FRAME_BasePropertyBGFrame;
MAP_FRAME_RUN( s_CUI_ID_FRAME_BasePropertyBGFrame, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_BasePropertyBGFrame, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BasePropertyBGFrame, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BasePropertyBGFrame, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_ShuXingOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_ZiLiaoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_OtherOnCheckBoxCheck )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_HeroOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_RankOnCheckBoxCheck )
CUI_ID_FRAME_BasePropertyBGFrame::CUI_ID_FRAME_BasePropertyBGFrame()
{
	// Member
	m_pID_FRAME_BasePropertyBGFrame = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_CHECKBOX_ShuXing = NULL;
	m_pID_CHECKBOX_ZiLiao = NULL;
	m_pID_CHECKBOX_Other = NULL;
	m_pID_PICTURE_ShuXing = NULL;
	m_pID_PICTURE_ZiLiao = NULL;
	m_pID_PICTURE_Other = NULL;
	m_pID_PICTURE_HeadPic = NULL;
	m_pID_CHECKBOX_Rank = NULL;

}
// Frame
bool CUI_ID_FRAME_BasePropertyBGFrame::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_BasePropertyBGFrame::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_BasePropertyBGFrame::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_BasePropertyBGFrame )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_BasePropertyBGFrame::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_BasePropertyBGFrame )
		return false;
	return true;
}
// CheckBox
void CUI_ID_FRAME_BasePropertyBGFrame::ID_CHECKBOX_ShuXingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_BasePropertyBGFrame )
		return;
	m_pID_CHECKBOX_ZiLiao->SetCheck(false);
	m_pID_CHECKBOX_Other->SetCheck(false);
	m_pID_CHECKBOX_ShuXing->SetCheck(true);
	s_CUI_ID_FRAME_BaseProperty.SetVisable(true);
	s_CUI_ID_FRAME_OtherInfo.SetVisable(false);
	s_CUI_ID_FRAME_SelfInfo.SetVisable(false);
	//s_CUI_ID_FRAME_HeroInfo._SetVisable(false);
	m_pID_PICTURE_ShuXing->SetVisable(true);
	m_pID_PICTURE_ZiLiao->SetVisable(false);
	m_pID_PICTURE_Other->SetVisable(false);
	m_pID_CHECKBOX_Rank->SetCheck(false);
	s_CUI_ID_FRAME_RankTitle.SetVisable(false);

}
// CheckBox
void CUI_ID_FRAME_BasePropertyBGFrame::ID_CHECKBOX_ZiLiaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_BasePropertyBGFrame )
		return;
	m_pID_CHECKBOX_ZiLiao->SetCheck(true);
	m_pID_CHECKBOX_Other->SetCheck(false);
	m_pID_CHECKBOX_ShuXing->SetCheck(false);
	s_CUI_ID_FRAME_BaseProperty.SetVisable(false);
	s_CUI_ID_FRAME_OtherInfo.SetVisable(false);
	s_CUI_ID_FRAME_SelfInfo.SetVisable(true);
	//s_CUI_ID_FRAME_HeroInfo._SetVisable(false);
	m_pID_PICTURE_ShuXing->SetVisable(false);
	m_pID_PICTURE_ZiLiao->SetVisable(true);
	m_pID_PICTURE_Other->SetVisable(false);
	m_pID_CHECKBOX_Rank->SetCheck(false);
	s_CUI_ID_FRAME_RankTitle.SetVisable(false);
}
// CheckBox
void CUI_ID_FRAME_BasePropertyBGFrame::ID_CHECKBOX_OtherOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_BasePropertyBGFrame )
		return;
	m_pID_CHECKBOX_ZiLiao->SetCheck(false);
	m_pID_CHECKBOX_Other->SetCheck(true);
	m_pID_CHECKBOX_ShuXing->SetCheck(false);
	s_CUI_ID_FRAME_BaseProperty.SetVisable(false);
	s_CUI_ID_FRAME_OtherInfo.SetVisable(true);
	s_CUI_ID_FRAME_SelfInfo.SetVisable(false);
	//s_CUI_ID_FRAME_HeroInfo._SetVisable(false);
	m_pID_PICTURE_ShuXing->SetVisable(false);
	m_pID_PICTURE_ZiLiao->SetVisable(false);
	m_pID_PICTURE_Other->SetVisable(true);
	m_pID_CHECKBOX_Rank->SetCheck(false);
	s_CUI_ID_FRAME_RankTitle.SetVisable(false);
}
// CheckBox
//void CUI_ID_FRAME_BasePropertyBGFrame::ID_CHECKBOX_HeroOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
//{
//	if ( !m_pID_FRAME_BasePropertyBGFrame )
//		return;
//	m_pID_CHECKBOX_ZiLiao->SetCheck(false);
//	m_pID_CHECKBOX_Other->SetCheck(false);
//	m_pID_CHECKBOX_ShuXing->SetCheck(false);
//	m_pID_CHECKBOX_Hero->SetCheck(true);
//	s_CUI_ID_FRAME_BaseProperty.SetVisable(false);
//	s_CUI_ID_FRAME_OtherInfo.SetVisable(false);
//	s_CUI_ID_FRAME_SelfInfo.SetVisable(false);
//	//s_CUI_ID_FRAME_HeroInfo._SetVisable(true);
//	m_pID_PICTURE_ShuXing->SetVisable(false);
//	m_pID_PICTURE_ZiLiao->SetVisable(false);
//	m_pID_PICTURE_Other->SetVisable(false);
//	m_pID_PICTURE_Hero->SetVisable(true);
//}
// CheckBox
void CUI_ID_FRAME_BasePropertyBGFrame::ID_CHECKBOX_RankOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_BasePropertyBGFrame )
		return;
	m_pID_CHECKBOX_ZiLiao->SetCheck(false);
	m_pID_CHECKBOX_Other->SetCheck(false);
	m_pID_CHECKBOX_ShuXing->SetCheck(false);
	s_CUI_ID_FRAME_BaseProperty.SetVisable(false);
	s_CUI_ID_FRAME_OtherInfo.SetVisable(false);
	s_CUI_ID_FRAME_SelfInfo.SetVisable(false);
	//s_CUI_ID_FRAME_HeroInfo._SetVisable(false);
	m_pID_PICTURE_ShuXing->SetVisable(false);
	m_pID_PICTURE_ZiLiao->SetVisable(false);
	m_pID_PICTURE_Other->SetVisable(false);
	m_pID_CHECKBOX_Rank->SetCheck(true);
	s_CUI_ID_FRAME_RankTitle.SetVisable(true);
}

// 装载UI
bool CUI_ID_FRAME_BasePropertyBGFrame::_LoadUI()
{
	s_CUI_ID_FRAME_OtherInfo._LoadUI();
	s_CUI_ID_FRAME_SelfInfo._LoadUI();
	//s_CUI_ID_FRAME_HeroInfo._LoadUI();
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\BasePropertyBGFrame.MEUI",false,UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\BasePropertyBGFrame.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_BasePropertyBGFrame::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_BasePropertyBGFrame, s_CUI_ID_FRAME_BasePropertyBGFrameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_BasePropertyBGFrame, s_CUI_ID_FRAME_BasePropertyBGFrameOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_BasePropertyBGFrame, ID_BUTTON_HELP, s_CUI_ID_FRAME_BasePropertyBGFrameID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BasePropertyBGFrame, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_BasePropertyBGFrameID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_ShuXing, s_CUI_ID_FRAME_BasePropertyBGFrameID_CHECKBOX_ShuXingOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_ZiLiao, s_CUI_ID_FRAME_BasePropertyBGFrameID_CHECKBOX_ZiLiaoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_Other, s_CUI_ID_FRAME_BasePropertyBGFrameID_CHECKBOX_OtherOnCheckBoxCheck );
	//theUiManager.OnCheckBoxCheck( ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_Hero, s_CUI_ID_FRAME_BasePropertyBGFrameID_CHECKBOX_HeroOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_Rank, s_CUI_ID_FRAME_BasePropertyBGFrameID_CHECKBOX_RankOnCheckBoxCheck );

	m_pID_FRAME_BasePropertyBGFrame = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_BasePropertyBGFrame );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_BasePropertyBGFrame, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_BasePropertyBGFrame, ID_BUTTON_CLOSE );
	m_pID_CHECKBOX_ShuXing = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_ShuXing );
	m_pID_CHECKBOX_ZiLiao = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_ZiLiao );
	m_pID_CHECKBOX_Other = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_Other );
	m_pID_PICTURE_ShuXing = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BasePropertyBGFrame, ID_PICTURE_ShuXing );
	m_pID_PICTURE_ZiLiao = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BasePropertyBGFrame, ID_PICTURE_ZiLiao );
	m_pID_PICTURE_Other = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BasePropertyBGFrame, ID_PICTURE_Other );
	m_pID_PICTURE_HeadPic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BasePropertyBGFrame, ID_PICTURE_HeadPic );
	m_pID_CHECKBOX_Rank = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BasePropertyBGFrame, ID_CHECKBOX_Rank );

	assert( m_pID_FRAME_BasePropertyBGFrame );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_CHECKBOX_ShuXing );
	assert( m_pID_CHECKBOX_ZiLiao );
	assert( m_pID_CHECKBOX_Other );
	assert( m_pID_PICTURE_ShuXing );
	assert( m_pID_PICTURE_ZiLiao );
	assert( m_pID_PICTURE_Other );
	assert( ID_PICTURE_HeadPic );
	assert( m_pID_CHECKBOX_Rank );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_BasePropertyBGFrame::_UnLoadUI()
{
	m_pID_FRAME_BasePropertyBGFrame = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_CHECKBOX_ShuXing = NULL;
	m_pID_CHECKBOX_ZiLiao = NULL;
	m_pID_CHECKBOX_Other = NULL;
	m_pID_PICTURE_HeadPic = NULL;
	s_CUI_ID_FRAME_OtherInfo._UnLoadUI();
	s_CUI_ID_FRAME_SelfInfo._UnLoadUI();
	//s_CUI_ID_FRAME_HeroInfo._UnLoadUI();
	return theUiManager.RemoveFrame( "Data\\UI\\BasePropertyBGFrame.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_BasePropertyBGFrame::_IsVisable()
{
	if ( !m_pID_FRAME_BasePropertyBGFrame )
		return false;
	return m_pID_FRAME_BasePropertyBGFrame->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_BasePropertyBGFrame::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_BasePropertyBGFrame )
		return ;
	m_pID_FRAME_BasePropertyBGFrame->SetVisable( bVisable );

	if (bVisable)
	{
		s_CUI_ID_FRAME_BaseProperty._SetVisable(true);
		m_pID_PICTURE_ShuXing->SetVisable(true);
		m_pID_PICTURE_ZiLiao->SetVisable(false);
		m_pID_PICTURE_Other->SetVisable(false);
		m_pID_CHECKBOX_ShuXing->SetCheck(true);
		m_pID_CHECKBOX_ZiLiao->SetCheck(false);
		m_pID_CHECKBOX_Other->SetCheck(false);
		m_pID_CHECKBOX_Rank->SetCheck(false);

		if ( !s_CUI_ID_FRAME_RankTitle.IsUILoad() )
		{
			s_CUI_ID_FRAME_RankTitle._LoadUI();
		}
		//m_pID_PICTURE_HeadPic->SetPicName(thePlayerRole);
		//m_pID_PICTURE_HeadPic->SetVisable(true);
		CPlayer *DestPlayer = theHeroGame.GetPlayerMgr()->GetMe();
		if (!DestPlayer)
		{
			return;
		}
		int hairId = DestPlayer->GetEquip()[eKeyAll_Hair].iModelID;
		int faceId = DestPlayer->GetEquip()[eKeyAll_Face].iModelID;
		char filename[MAX_PATH] = {0};
		char sex[2][32] = { "Male", "Female" };
		MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sHairHead_%d_%d.dds",
			GetRootPath(), sex[DestPlayer->GetSex()], hairId,faceId);
		f_Handle* fp = packet_namespace::w_fopen(filename, "r");
		if (fp)
		{
			m_pID_PICTURE_HeadPic->SetPicName(filename);
			packet_namespace::w_fclose(fp);
		}
		else
		{
			if (DestPlayer->GetSex() == Sex_Male)
				m_pID_PICTURE_HeadPic->SetPicName("Data/Ui/HeadPicture/Player/DefaultMale.dds");
			else
				m_pID_PICTURE_HeadPic->SetPicName("Data/Ui/HeadPicture/Player/DefaultFemale.dds");
		}
		m_pID_PICTURE_HeadPic->SetVisable(true);
	}
	
}
void CUI_ID_FRAME_BasePropertyBGFrame::InitializeAtEnterWorld()
{
	SetVisable(false);
}