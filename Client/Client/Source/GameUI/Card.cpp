/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\Card.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Card.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "zhujiangtujian.h"
#include "ItemHero.h"
#include "SeekPet.h"
#include "ItemDetail.h"
#include "SuAnimalCard.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "MiniMapUI.h"

const char* chStars[12] = 
{
	"{#77701}",
	"{#77702}",
	"{#77703}",
	"{#77704}",
	"{#77705}",
	"{#77706}",
	"{#77707}",
	"{#77708}",
	"{#77709}",
	"{#77710}",
	"{#77711}",
	"{#77712}",
};

CUI_ID_FRAME_CARD s_CUI_ID_FRAME_CARD;

MAP_FRAME_RUN( s_CUI_ID_FRAME_CARD, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CARD, OnFrameRender )

MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_CHECKBOX_HeroOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_CHECKBOX_PetOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_CHECKBOX_MountOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Card1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Card2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Card3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Card4OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Card5OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Card6OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Card7OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Card8OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Card9OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Card10OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_PageUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_PageDownOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_CHECKBOX_AchieveOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Achieve1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Achieve2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Achieve3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Achieve4OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Achieve5OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Achieve6OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Achieve7OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Achieve8OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Achieve9OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CARD, ID_BUTTON_Achieve10OnButtonClick )

CUI_ID_FRAME_CARD::CUI_ID_FRAME_CARD()
{
	// Member
	m_pID_FRAME_CARD = NULL;
	m_pID_CHECKBOX_Hero = NULL;
	m_pID_CHECKBOX_Pet = NULL;
	m_pID_CHECKBOX_Mount = NULL;
	m_pID_PICTURE_Card1 = NULL;
	m_pID_BUTTON_Card1 = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_State1 = NULL;
	m_pID_PICTURE_Card2 = NULL;
	m_pID_BUTTON_Card2 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_State2 = NULL;
	m_pID_PICTURE_Card3 = NULL;
	m_pID_BUTTON_Card3 = NULL;
	m_pID_TEXT_Name3 = NULL;
	m_pID_TEXT_State3 = NULL;
	m_pID_PICTURE_Card4 = NULL;
	m_pID_BUTTON_Card4 = NULL;
	m_pID_TEXT_Name4 = NULL;
	m_pID_TEXT_State4 = NULL;
	m_pID_PICTURE_Card5 = NULL;
	m_pID_BUTTON_Card5 = NULL;
	m_pID_TEXT_Name5 = NULL;
	m_pID_TEXT_State5 = NULL;
	m_pID_PICTURE_Card6 = NULL;
	m_pID_BUTTON_Card6 = NULL;
	m_pID_TEXT_Name6 = NULL;
	m_pID_TEXT_State6 = NULL;
	m_pID_PICTURE_Card7 = NULL;
	m_pID_BUTTON_Card7 = NULL;
	m_pID_TEXT_Name7 = NULL;
	m_pID_TEXT_State7 = NULL;
	m_pID_PICTURE_Card8 = NULL;
	m_pID_BUTTON_Card8 = NULL;
	m_pID_TEXT_Name8 = NULL;
	m_pID_TEXT_State8 = NULL;
	m_pID_PICTURE_Card9 = NULL;
	m_pID_BUTTON_Card9 = NULL;
	m_pID_TEXT_Name9 = NULL;
	m_pID_TEXT_State9 = NULL;
	m_pID_PICTURE_Card10 = NULL;
	m_pID_BUTTON_Card10 = NULL;
	m_pID_TEXT_Name10 = NULL;
	m_pID_TEXT_State10 = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_CHECKBOX_Achieve = NULL;
	
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Star1 = NULL;
	m_pID_TEXT_Star2 = NULL;
	m_pID_TEXT_Star3 = NULL;
	m_pID_TEXT_Star4 = NULL;
	m_pID_TEXT_Star5 = NULL;
	m_pID_TEXT_Star6 = NULL;
	m_pID_TEXT_Star7 = NULL;
	m_pID_TEXT_Star8 = NULL;
	m_pID_TEXT_Star9 = NULL;
	m_pID_TEXT_Star10 = NULL;

	m_pID_BUTTON_Achieve1 = NULL;
	m_pID_BUTTON_Achieve2 = NULL;
	m_pID_BUTTON_Achieve3 = NULL;
	m_pID_BUTTON_Achieve4 = NULL;
	m_pID_BUTTON_Achieve5 = NULL;
	m_pID_BUTTON_Achieve6 = NULL;
	m_pID_BUTTON_Achieve7 = NULL;
	m_pID_BUTTON_Achieve8 = NULL;
	m_pID_BUTTON_Achieve9 = NULL;
	m_pID_BUTTON_Achieve10 = NULL;

	m_curPage = 1;
	m_totalPage = 1;
	m_curShowType = EST_Hero;

}
CUI_ID_FRAME_CARD::~CUI_ID_FRAME_CARD()
{
	m_vecHero.clear();
	m_vecPet.clear();
	m_vecMount.clear();
	vecShowCard.clear();
	m_vecAchieve.clear();
	vecShowAchieve.clear();

	for (int i = 0; i < PAGE_SIZE; i++)
		m_Group[i].Clear();
}
// Frame
bool CUI_ID_FRAME_CARD::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_CARD::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_CARD::ID_CHECKBOX_HeroOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckType( EST_Hero );
	SetTotalPage();
	ShowPage();
	RefreshPageEnable();
	Refresh();
}
// CheckBox
void CUI_ID_FRAME_CARD::ID_CHECKBOX_PetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckType( EST_Pet );
	SetTotalPage();
	ShowPage();
	RefreshPageEnable();
	Refresh();
}
// CheckBox
void CUI_ID_FRAME_CARD::ID_CHECKBOX_MountOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckType( EST_Mount );
	SetTotalPage();
	ShowPage();
	RefreshPageEnable();
	Refresh();
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Card1OnButtonClick( ControlObject* pSender )
{
	OnDetail( 0 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Card2OnButtonClick( ControlObject* pSender )
{
	OnDetail( 1 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Card3OnButtonClick( ControlObject* pSender )
{
	OnDetail( 2 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Card4OnButtonClick( ControlObject* pSender )
{
	OnDetail( 3 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Card5OnButtonClick( ControlObject* pSender )
{
	OnDetail( 4 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Card6OnButtonClick( ControlObject* pSender )
{
	OnDetail( 5 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Card7OnButtonClick( ControlObject* pSender )
{
	OnDetail( 6 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Card8OnButtonClick( ControlObject* pSender )
{
	OnDetail( 7 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Card9OnButtonClick( ControlObject* pSender )
{
	OnDetail( 8 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Card10OnButtonClick( ControlObject* pSender )
{
	OnDetail( 9 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender )
{
	if ( m_curPage > 1 )
	{
		m_curPage--;
		ShowPage();
		RefreshPageEnable();
		Refresh();
	}
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender )
{
	if ( m_curPage < m_totalPage )
	{
		m_curPage++;
		ShowPage();
		RefreshPageEnable();
		Refresh();
	}
	return true;
}
// CheckBox
void CUI_ID_FRAME_CARD::ID_CHECKBOX_AchieveOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckType( EST_Achieve );
	SetTotalPage();
	ShowPage();
	RefreshPageEnable();
	Refresh();
}

// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Achieve1OnButtonClick( ControlObject* pSender )
{
	OnButtonAchieve( 0 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Achieve2OnButtonClick( ControlObject* pSender )
{
	OnButtonAchieve( 1 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Achieve3OnButtonClick( ControlObject* pSender )
{
	OnButtonAchieve( 2 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Achieve4OnButtonClick( ControlObject* pSender )
{
	OnButtonAchieve( 3 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Achieve5OnButtonClick( ControlObject* pSender )
{
	OnButtonAchieve( 4 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Achieve6OnButtonClick( ControlObject* pSender )
{
	OnButtonAchieve( 5 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Achieve7OnButtonClick( ControlObject* pSender )
{
	OnButtonAchieve( 6 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Achieve8OnButtonClick( ControlObject* pSender )
{
	OnButtonAchieve( 7 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Achieve9OnButtonClick( ControlObject* pSender )
{
	OnButtonAchieve( 8 );
	return true;
}
// Button
bool CUI_ID_FRAME_CARD::ID_BUTTON_Achieve10OnButtonClick( ControlObject* pSender )
{
	OnButtonAchieve( 9 );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_CARD::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Card.meui", false, UI_Render_LayerThree  );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Card.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CARD::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CARD, s_CUI_ID_FRAME_CARDOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CARD, s_CUI_ID_FRAME_CARDOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CARD, ID_CHECKBOX_Hero, s_CUI_ID_FRAME_CARDID_CHECKBOX_HeroOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CARD, ID_CHECKBOX_Pet, s_CUI_ID_FRAME_CARDID_CHECKBOX_PetOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CARD, ID_CHECKBOX_Mount, s_CUI_ID_FRAME_CARDID_CHECKBOX_MountOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Card1, s_CUI_ID_FRAME_CARDID_BUTTON_Card1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Card2, s_CUI_ID_FRAME_CARDID_BUTTON_Card2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Card3, s_CUI_ID_FRAME_CARDID_BUTTON_Card3OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Card4, s_CUI_ID_FRAME_CARDID_BUTTON_Card4OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Card5, s_CUI_ID_FRAME_CARDID_BUTTON_Card5OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Card6, s_CUI_ID_FRAME_CARDID_BUTTON_Card6OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Card7, s_CUI_ID_FRAME_CARDID_BUTTON_Card7OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Card8, s_CUI_ID_FRAME_CARDID_BUTTON_Card8OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Card9, s_CUI_ID_FRAME_CARDID_BUTTON_Card9OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Card10, s_CUI_ID_FRAME_CARDID_BUTTON_Card10OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_PageUp, s_CUI_ID_FRAME_CARDID_BUTTON_PageUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_PageDown, s_CUI_ID_FRAME_CARDID_BUTTON_PageDownOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CARD, ID_CHECKBOX_Achieve, s_CUI_ID_FRAME_CARDID_CHECKBOX_AchieveOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_CARDID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Achieve1, s_CUI_ID_FRAME_CARDID_BUTTON_Achieve1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Achieve2, s_CUI_ID_FRAME_CARDID_BUTTON_Achieve2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Achieve3, s_CUI_ID_FRAME_CARDID_BUTTON_Achieve3OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Achieve4, s_CUI_ID_FRAME_CARDID_BUTTON_Achieve4OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Achieve5, s_CUI_ID_FRAME_CARDID_BUTTON_Achieve5OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Achieve6, s_CUI_ID_FRAME_CARDID_BUTTON_Achieve6OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Achieve7, s_CUI_ID_FRAME_CARDID_BUTTON_Achieve7OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Achieve8, s_CUI_ID_FRAME_CARDID_BUTTON_Achieve8OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Achieve9, s_CUI_ID_FRAME_CARDID_BUTTON_Achieve9OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CARD, ID_BUTTON_Achieve10, s_CUI_ID_FRAME_CARDID_BUTTON_Achieve10OnButtonClick );

	m_pID_FRAME_CARD = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CARD );
	m_pID_CHECKBOX_Hero = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CARD, ID_CHECKBOX_Hero );
	m_pID_CHECKBOX_Pet = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CARD, ID_CHECKBOX_Pet );
	m_pID_CHECKBOX_Mount = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CARD, ID_CHECKBOX_Mount );
	m_pID_PICTURE_Card1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CARD, ID_PICTURE_Card1 );
	m_pID_BUTTON_Card1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Card1 );
	m_pID_TEXT_Name1 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Name1 );
	m_pID_TEXT_State1 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_State1 );
	m_pID_PICTURE_Card2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CARD, ID_PICTURE_Card2 );
	m_pID_BUTTON_Card2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Card2 );
	m_pID_TEXT_Name2 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Name2 );
	m_pID_TEXT_State2 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_State2 );
	m_pID_PICTURE_Card3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CARD, ID_PICTURE_Card3 );
	m_pID_BUTTON_Card3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Card3 );
	m_pID_TEXT_Name3 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Name3 );
	m_pID_TEXT_State3 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_State3 );
	m_pID_PICTURE_Card4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CARD, ID_PICTURE_Card4 );
	m_pID_BUTTON_Card4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Card4 );
	m_pID_TEXT_Name4 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Name4 );
	m_pID_TEXT_State4 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_State4 );
	m_pID_PICTURE_Card5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CARD, ID_PICTURE_Card5 );
	m_pID_BUTTON_Card5 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Card5 );
	m_pID_TEXT_Name5 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Name5 );
	m_pID_TEXT_State5 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_State5 );
	m_pID_PICTURE_Card6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CARD, ID_PICTURE_Card6 );
	m_pID_BUTTON_Card6 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Card6 );
	m_pID_TEXT_Name6 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Name6 );
	m_pID_TEXT_State6 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_State6 );
	m_pID_PICTURE_Card7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CARD, ID_PICTURE_Card7 );
	m_pID_BUTTON_Card7 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Card7 );
	m_pID_TEXT_Name7 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Name7 );
	m_pID_TEXT_State7 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_State7 );
	m_pID_PICTURE_Card8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CARD, ID_PICTURE_Card8 );
	m_pID_BUTTON_Card8 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Card8 );
	m_pID_TEXT_Name8 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Name8 );
	m_pID_TEXT_State8 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_State8 );
	m_pID_PICTURE_Card9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CARD, ID_PICTURE_Card9 );
	m_pID_BUTTON_Card9 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Card9 );
	m_pID_TEXT_Name9 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Name9 );
	m_pID_TEXT_State9 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_State9 );
	m_pID_PICTURE_Card10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CARD, ID_PICTURE_Card10 );
	m_pID_BUTTON_Card10 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Card10 );
	m_pID_TEXT_Name10 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Name10 );
	m_pID_TEXT_State10 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_State10 );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Page );
	m_pID_BUTTON_PageUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_PageUp );
	m_pID_BUTTON_PageDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_PageDown );
	m_pID_CHECKBOX_Achieve = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CARD, ID_CHECKBOX_Achieve );
	
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_CLOSE );
	m_pID_TEXT_Star1 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Star1 );
	m_pID_TEXT_Star2 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Star2 );
	m_pID_TEXT_Star3 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Star3 );
	m_pID_TEXT_Star4 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Star4 );
	m_pID_TEXT_Star5 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Star5 );
	m_pID_TEXT_Star6 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Star6 );
	m_pID_TEXT_Star7 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Star7 );
	m_pID_TEXT_Star8 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Star8 );
	m_pID_TEXT_Star9 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Star9 );
	m_pID_TEXT_Star10 = (ControlText*)theUiManager.FindControl( ID_FRAME_CARD, ID_TEXT_Star10 );
	m_pID_BUTTON_Achieve1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Achieve1 );
	m_pID_BUTTON_Achieve2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Achieve2 );
	m_pID_BUTTON_Achieve3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Achieve3 );
	m_pID_BUTTON_Achieve4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Achieve4 );
	m_pID_BUTTON_Achieve5 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Achieve5 );
	m_pID_BUTTON_Achieve6 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Achieve6 );
	m_pID_BUTTON_Achieve7 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Achieve7 );
	m_pID_BUTTON_Achieve8 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Achieve8 );
	m_pID_BUTTON_Achieve9 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Achieve9 );
	m_pID_BUTTON_Achieve10 = (ControlButton*)theUiManager.FindControl( ID_FRAME_CARD, ID_BUTTON_Achieve10 );

	assert( m_pID_FRAME_CARD );
	assert( m_pID_CHECKBOX_Hero );
	assert( m_pID_CHECKBOX_Pet );
	assert( m_pID_CHECKBOX_Mount );
	assert( m_pID_PICTURE_Card1 );
	assert( m_pID_BUTTON_Card1 );
	assert( m_pID_TEXT_Name1 );
	assert( m_pID_TEXT_State1 );
	assert( m_pID_PICTURE_Card2 );
	assert( m_pID_BUTTON_Card2 );
	assert( m_pID_TEXT_Name2 );
	assert( m_pID_TEXT_State2 );
	assert( m_pID_PICTURE_Card3 );
	assert( m_pID_BUTTON_Card3 );
	assert( m_pID_TEXT_Name3 );
	assert( m_pID_TEXT_State3 );
	assert( m_pID_PICTURE_Card4 );
	assert( m_pID_BUTTON_Card4 );
	assert( m_pID_TEXT_Name4 );
	assert( m_pID_TEXT_State4 );
	assert( m_pID_PICTURE_Card5 );
	assert( m_pID_BUTTON_Card5 );
	assert( m_pID_TEXT_Name5 );
	assert( m_pID_TEXT_State5 );
	assert( m_pID_PICTURE_Card6 );
	assert( m_pID_BUTTON_Card6 );
	assert( m_pID_TEXT_Name6 );
	assert( m_pID_TEXT_State6 );
	assert( m_pID_PICTURE_Card7 );
	assert( m_pID_BUTTON_Card7 );
	assert( m_pID_TEXT_Name7 );
	assert( m_pID_TEXT_State7 );
	assert( m_pID_PICTURE_Card8 );
	assert( m_pID_BUTTON_Card8 );
	assert( m_pID_TEXT_Name8 );
	assert( m_pID_TEXT_State8 );
	assert( m_pID_PICTURE_Card9 );
	assert( m_pID_BUTTON_Card9 );
	assert( m_pID_TEXT_Name9 );
	assert( m_pID_TEXT_State9 );
	assert( m_pID_PICTURE_Card10 );
	assert( m_pID_BUTTON_Card10 );
	assert( m_pID_TEXT_Name10 );
	assert( m_pID_TEXT_State10 );
	assert( m_pID_TEXT_Page );
	assert( m_pID_BUTTON_PageUp );
	assert( m_pID_BUTTON_PageDown );
	assert( m_pID_CHECKBOX_Achieve );
	
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Star1 );
	assert( m_pID_TEXT_Star2 );
	assert( m_pID_TEXT_Star3 );
	assert( m_pID_TEXT_Star4 );
	assert( m_pID_TEXT_Star5 );
	assert( m_pID_TEXT_Star6 );
	assert( m_pID_TEXT_Star7 );
	assert( m_pID_TEXT_Star8 );
	assert( m_pID_TEXT_Star9 );
	assert( m_pID_TEXT_Star10 );
	assert( m_pID_BUTTON_Achieve1 );
	assert( m_pID_BUTTON_Achieve2 );
	assert( m_pID_BUTTON_Achieve3 );
	assert( m_pID_BUTTON_Achieve4 );
	assert( m_pID_BUTTON_Achieve5 );
	assert( m_pID_BUTTON_Achieve6 );
	assert( m_pID_BUTTON_Achieve7 );
	assert( m_pID_BUTTON_Achieve8 );
	assert( m_pID_BUTTON_Achieve9 );
	assert( m_pID_BUTTON_Achieve10 );

	for (int i = 0; i < PAGE_SIZE; i++)
		m_Group[i].Clear();

	//AddControl的顺序不能乱，后面是根据顺序来取控件的，这样能省不少代码
	m_Group[0].AddControl( m_pID_PICTURE_Card1 );
	m_Group[0].AddControl( m_pID_BUTTON_Card1 );
	m_Group[0].AddControl( m_pID_TEXT_Name1 );
	m_Group[0].AddControl( m_pID_TEXT_State1 );
	m_Group[0].AddControl( m_pID_BUTTON_Achieve1 );
	m_Group[0].AddControl( m_pID_TEXT_Star1 );

	m_Group[1].AddControl( m_pID_PICTURE_Card2 );
	m_Group[1].AddControl( m_pID_BUTTON_Card2 );
	m_Group[1].AddControl( m_pID_TEXT_Name2 );
	m_Group[1].AddControl( m_pID_TEXT_State2 );
	m_Group[1].AddControl( m_pID_BUTTON_Achieve2 );
	m_Group[1].AddControl( m_pID_TEXT_Star2 );

	m_Group[2].AddControl( m_pID_PICTURE_Card3 );
	m_Group[2].AddControl( m_pID_BUTTON_Card3 );
	m_Group[2].AddControl( m_pID_TEXT_Name3 );
	m_Group[2].AddControl( m_pID_TEXT_State3 );
	m_Group[2].AddControl( m_pID_BUTTON_Achieve3 );
	m_Group[2].AddControl( m_pID_TEXT_Star3 );

	m_Group[3].AddControl( m_pID_PICTURE_Card4 );
	m_Group[3].AddControl( m_pID_BUTTON_Card4 );
	m_Group[3].AddControl( m_pID_TEXT_Name4 );
	m_Group[3].AddControl( m_pID_TEXT_State4 );
	m_Group[3].AddControl( m_pID_BUTTON_Achieve4 );
	m_Group[3].AddControl( m_pID_TEXT_Star4 );

	m_Group[4].AddControl( m_pID_PICTURE_Card5 );
	m_Group[4].AddControl( m_pID_BUTTON_Card5 );
	m_Group[4].AddControl( m_pID_TEXT_Name5 );
	m_Group[4].AddControl( m_pID_TEXT_State5 );
	m_Group[4].AddControl( m_pID_BUTTON_Achieve5 );
	m_Group[4].AddControl( m_pID_TEXT_Star5 );

	m_Group[5].AddControl( m_pID_PICTURE_Card6 );
	m_Group[5].AddControl( m_pID_BUTTON_Card6 );
	m_Group[5].AddControl( m_pID_TEXT_Name6 );
	m_Group[5].AddControl( m_pID_TEXT_State6 );
	m_Group[5].AddControl( m_pID_BUTTON_Achieve6 );
	m_Group[5].AddControl( m_pID_TEXT_Star6 );

	m_Group[6].AddControl( m_pID_PICTURE_Card7 );
	m_Group[6].AddControl( m_pID_BUTTON_Card7 );
	m_Group[6].AddControl( m_pID_TEXT_Name7 );
	m_Group[6].AddControl( m_pID_TEXT_State7 );
	m_Group[6].AddControl( m_pID_BUTTON_Achieve7 );
	m_Group[6].AddControl( m_pID_TEXT_Star7 );

	m_Group[7].AddControl( m_pID_PICTURE_Card8 );
	m_Group[7].AddControl( m_pID_BUTTON_Card8 );
	m_Group[7].AddControl( m_pID_TEXT_Name8 );
	m_Group[7].AddControl( m_pID_TEXT_State8 );
	m_Group[7].AddControl( m_pID_BUTTON_Achieve8 );
	m_Group[7].AddControl( m_pID_TEXT_Star8 );

	m_Group[8].AddControl( m_pID_PICTURE_Card9 );
	m_Group[8].AddControl( m_pID_BUTTON_Card9 );
	m_Group[8].AddControl( m_pID_TEXT_Name9 );
	m_Group[8].AddControl( m_pID_TEXT_State9 );
	m_Group[8].AddControl( m_pID_BUTTON_Achieve9 );
	m_Group[8].AddControl( m_pID_TEXT_Star9 );

	m_Group[9].AddControl( m_pID_PICTURE_Card10 );
	m_Group[9].AddControl( m_pID_BUTTON_Card10 );
	m_Group[9].AddControl( m_pID_TEXT_Name10 );
	m_Group[9].AddControl( m_pID_TEXT_State10 );
	m_Group[9].AddControl( m_pID_BUTTON_Achieve10 );
	m_Group[9].AddControl( m_pID_TEXT_Star10 );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CARD::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\Card.meui" );
}
// 是否可视
bool CUI_ID_FRAME_CARD::_IsVisable()
{
	if( !m_pID_FRAME_CARD )
		return false;
	return m_pID_FRAME_CARD->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CARD::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_CARD )
		return;
	m_pID_FRAME_CARD->SetVisable( bVisable );

	if ( bVisable )
	{
		InitData();
		SetCheckType( EST_Hero );
		SetTotalPage();
		ShowPage();
		RefreshPageEnable();
		Refresh();

		s_CUI_ID_FRAME_MiniMap.SetCardTextShow(false);
	}
}

void CUI_ID_FRAME_CARD::SetCheckType( EShowType type )
{
	if ( !m_pID_CHECKBOX_Hero || !m_pID_CHECKBOX_Pet ||
		!m_pID_CHECKBOX_Mount || !m_pID_CHECKBOX_Achieve )
		return;

	switch (type)
	{
	case EST_Pet:
		{
			m_pID_CHECKBOX_Pet->SetCheck( true );
			m_pID_CHECKBOX_Hero->SetCheck( false );
			m_pID_CHECKBOX_Mount->SetCheck( false );
			m_pID_CHECKBOX_Achieve->SetCheck( false );
			m_curShowType = EST_Pet;
		}
		break;
	case EST_Hero:
		{
			m_pID_CHECKBOX_Pet->SetCheck( false );
			m_pID_CHECKBOX_Hero->SetCheck( true );
			m_pID_CHECKBOX_Mount->SetCheck( false );
			m_pID_CHECKBOX_Achieve->SetCheck( false );
			m_curShowType = EST_Hero;
		}
		break;
	case EST_Mount:
		{
			m_pID_CHECKBOX_Pet->SetCheck( false );
			m_pID_CHECKBOX_Hero->SetCheck( false );
			m_pID_CHECKBOX_Mount->SetCheck( true );
			m_pID_CHECKBOX_Achieve->SetCheck( false );
			m_curShowType = EST_Mount;
		}
		break;
	case EST_Achieve:
		{
			m_pID_CHECKBOX_Pet->SetCheck( false );
			m_pID_CHECKBOX_Hero->SetCheck( false );
			m_pID_CHECKBOX_Mount->SetCheck( false );
			m_pID_CHECKBOX_Achieve->SetCheck( true );
			m_curShowType = EST_Achieve;
		}
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_CARD::InitControl()
{
	for (int i = 0; i < PAGE_SIZE; i++)
	{
		int nSize = m_Group[i].GetControlSize();
		for (int j = 0; j < nSize; j++)
		{
			switch (j)
			{
			case 0:
				{
					ControlPicture* pPic = (ControlPicture*)m_Group[i].GetControl(j);
					if ( !pPic )
						return;
					pPic->SetPicName("");
				}
				break;
			case 1:
			case 4:
				break;
			case 2:
			case 3:
			case 5:
				{
					ControlText* pText = (ControlText*)m_Group[i].GetControl(j);
					if ( !pText )
						return;
					pText->SetText("");
					pText->setTip("");
					pText->setShowTip(false);
				}
				break;
			default:
				break;
			}
			
		}

		m_Group[i].SetVisible(false);
	}
}

void CUI_ID_FRAME_CARD::InitData()
{
	m_vecHero.clear();
	m_vecPet.clear();
	m_vecMount.clear();
	m_vecAchieve.clear();

	CardIconConfig::CardVector vecCard = theCardIconConfig.GetCardVec();
	int nSize = vecCard.size();

	for (int i = 0; i < nSize; i++)
	{
		switch (vecCard[i].type)
		{
		case CardIconConfig::ECT_Hero:
			m_vecHero.push_back( vecCard[i] );
			break;
		case CardIconConfig::ECT_Mount:
			m_vecMount.push_back( vecCard[i] );
			break;
		case CardIconConfig::ECT_Pet:
			m_vecPet.push_back( vecCard[i] );
			break;
		default:
			break;
		}	
	}

	CardAchieveConfig::CardAchieveVector vecAchieve = theCardAchieveConfig.GetCardVec();
	nSize = vecAchieve.size();

	for (int i = 0; i < nSize; i++)
	{
		if ( vecAchieve[i].shID >= 0 )
			m_vecAchieve.push_back( vecAchieve[i] );
	}
	
}

void CUI_ID_FRAME_CARD::SetTotalPage()
{
	int nsize = 0;
	int nsurplus = 0;
	switch ( m_curShowType )
	{
	case EST_Pet:
		{
			nsize = m_vecPet.size();
		}
		break;
	case EST_Mount:
		{
			nsize = m_vecMount.size();
		}
		break;
	case EST_Hero:
		{
			nsize = m_vecHero.size();
		}
		break;
	case EST_Achieve:
		{
			nsize = m_vecAchieve.size();
		}
		break;
	default:
		break;
	}

	nsurplus = nsize % PAGE_SIZE;
	m_totalPage = nsize / PAGE_SIZE + ( nsurplus > 0 ? 1 : 0 );
	if ( m_totalPage == 0 )
		m_totalPage = 1;

	m_curPage = 1;
}

void CUI_ID_FRAME_CARD::ShowPage()
{
	if ( !m_pID_TEXT_Page )
		return;

	char buf[24] = {0};
	sprintf_s( buf, sizeof(buf) - 1, "%d/%d", m_curPage, m_totalPage );
	m_pID_TEXT_Page->SetText( buf );
}

void CUI_ID_FRAME_CARD::RefreshPageEnable()
{
	if ( !m_pID_BUTTON_PageUp || !m_pID_BUTTON_PageDown )
		return;

	m_pID_BUTTON_PageUp->SetEnable( true );
	m_pID_BUTTON_PageDown->SetEnable( true );

	if (  m_curPage <= 1 )
		m_pID_BUTTON_PageUp->SetEnable( false );

	if ( m_curPage >= m_totalPage )
		m_pID_BUTTON_PageDown->SetEnable( false );
}

void CUI_ID_FRAME_CARD::Refresh()
{
	InitControl();

	vecShowCard.clear();
	vecShowAchieve.clear();

	int nsize = 0;
	switch (m_curShowType)
	{
	case EST_Pet:
		{
			nsize = m_vecPet.size();
		}
		break;
	case EST_Mount:
		{
			nsize = m_vecMount.size();
		}
		break;
	case EST_Hero:
		{
			nsize = m_vecHero.size();
		}
		break;
	case EST_Achieve:
		{
			nsize = m_vecAchieve.size();
		}
		break;
	default:
		break;
	}

	int nStart = ( m_curPage - 1 ) * PAGE_SIZE;
	if ( nStart < 0 )
		nStart = 0;
	for (int i = nStart, j = 0; i < nsize && j < PAGE_SIZE; i++, j++)
	{
		switch (m_curShowType)
		{
		case EST_Pet:
			{
				vecShowCard.push_back( m_vecPet[i] );
			}
			break;
		case EST_Mount:
			{
				vecShowCard.push_back( m_vecMount[i] );
			}
			break;
		case EST_Hero:
			{
				vecShowCard.push_back( m_vecHero[i] );
			}
			break;
		case EST_Achieve:
			{
				vecShowAchieve.push_back( m_vecAchieve[i] );
			}
			break;
		default:
			break;
		}
	}
	
	if ( m_curShowType == EST_Pet || m_curShowType == EST_Mount || m_curShowType == EST_Hero )
		RefreshCard( vecShowCard );
	else
		RefreshAchieve( vecShowAchieve );
}

void CUI_ID_FRAME_CARD::RefreshCard( CardIconConfig::CardVector& cardVec )
{
	int nSize = cardVec.size();
	if ( nSize <= 0 )
		return;

	for (int i = 0; i < nSize; i++)
	{
		m_Group[i].SetVisible( true );

		short level = thePlayerRole.GetCharInfo2().otherdataclient.cards.shCardLevel[cardVec[i].shID];
		bool IsHad = false;
		if ( level >= 0 )
			IsHad = true;

		int nGSize = m_Group[i].GetControlSize();
		for (int j = 0; j < nGSize; j++)
		{
			switch (j)
			{
			case 0: //m_pID_PICTURE_Card
				{
					ControlPicture* pPic = (ControlPicture*)m_Group[i].GetControl(j);
					if ( !pPic )
						return;

					S_BaseData::S_Pic sPic;
					RECT rcClient;
					std::string strImg;

					if( IsHad )
					{
						rcClient.left = cardVec[i].sBrightImg.nWidth * ( cardVec[i].sBrightImg.nColumn - 1 );
						rcClient.top = cardVec[i].sBrightImg.nHeight * ( cardVec[i].sBrightImg.nRow - 1 );
						rcClient.right = rcClient.left + cardVec[i].sBrightImg.nWidth;
						rcClient.bottom = rcClient.top + cardVec[i].sBrightImg.nHeight;

						strImg = cardVec[i].sBrightImg.strImg;
					}
					else
					{
						rcClient.left = cardVec[i].sDarkImg.nWidth * ( cardVec[i].sDarkImg.nColumn - 1 );
						rcClient.top = cardVec[i].sDarkImg.nHeight * ( cardVec[i].sDarkImg.nRow - 1 );
						rcClient.right = rcClient.left + cardVec[i].sDarkImg.nWidth;
						rcClient.bottom = rcClient.top + cardVec[i].sDarkImg.nHeight;

						strImg = cardVec[i].sDarkImg.strImg;
					}
					sPic.SetPicStruct(strImg.c_str(), &rcClient, &rcClient);
					pPic->SetPic(&sPic, true);
					pPic->SetPicName(strImg.c_str());
				}
				break;
			case 1: //m_pID_BUTTON_Card
				break;
			case 2: //m_pID_TEXT_Name
				{
					ControlText* pText = (ControlText*)m_Group[i].GetControl(j);
					if ( !pText )
						return;
					/*char buf[128] = {0};
					if ( IsHad )
					{
						sprintf_s( buf, sizeof(buf) - 1, "%s:%d%s", cardVec[i].strName.c_str(), level, theXmlString.GetString(eText_CardIcon_Level) );
					}
					else
					{
						sprintf_s( buf, sizeof(buf) - 1, "%s:%d%s", cardVec[i].strName.c_str(), cardVec[i].nLevel, theXmlString.GetString(eText_CardIcon_Level) );
					}*/
					pText->SetText( cardVec[i].strName.c_str() );
				}
				break;
			case 3: //m_pID_TEXT_State
				{
					ControlText* pText = (ControlText*)m_Group[i].GetControl(j);
					if ( !pText )
						return;

					if ( IsHad )
					{
						pText->SetText( theXmlString.GetString(eText_CardIcon_Get) );
					}
					else
					{
						pText->SetText( theXmlString.GetString(eText_CardIcon_UnGet) );
					}
					
				}
				break;
			case 4: //m_pID_BUTTON_Achieve
				{
					ControlButton* pButton = (ControlButton*)m_Group[i].GetControl(j);
					if ( !pButton )
						return;
					pButton->setTip("");
					pButton->SetShowTip(false);
					pButton->SetVisable(false);
				}
				break;
			case 5: //m_pID_TEXT_Star
				{
					ControlText* pText = (ControlText*)m_Group[i].GetControl(j);
					if ( !pText )
						return;
					int nstar = level;
					if ( !IsHad )
						nstar = cardVec[i].nLevel;
					if ( cardVec[i].type == CardIconConfig::ECT_Hero || cardVec[i].type == CardIconConfig::ECT_Pet )
						nstar += 1;

					if ( nstar >= 1 && nstar <= 12 )
						pText->SetText( chStars[nstar - 1] );
					
					if ( nstar > 0 )
					{
						char buf[24] = {0};
						sprintf_s( buf, sizeof(buf) - 1, "%s:%d%s", cardVec[i].strName.c_str(), nstar, theXmlString.GetString(eText_CardIcon_Level) );
						pText->setShowTip(true);
						pText->setTip(buf);
					}
					
				}
				break;
			default:
				break;
			}

		}
	}
	
}

void CUI_ID_FRAME_CARD::OnDetail( int index )
{
	if ( index < 0 || index >= PAGE_SIZE )
		return;

	switch (m_curShowType)
	{
	case EST_Pet:
		{
			ShowPetDetail( index );
		}
		break;
	case EST_Mount:
		{
			ShowMountDetail( index );
		}
		break;
	case EST_Hero:
		{
			ShowHeroDetail( index );
		}
		break;
	case EST_Achieve:
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_CARD::ShowHeroDetail( int index )
{
	if ( index < 0 || index >= PAGE_SIZE )
		return;

	int nsize = vecShowCard.size();
	if ( index >= nsize )
		return;

	short stCardID = vecShowCard[index].shID;

	short level = thePlayerRole.GetCharInfo2().otherdataclient.cards.shCardLevel[stCardID];
	if ( level < 0 )
		level = vecShowCard[index].nLevel;

	if ( level >= CardIconConfig::ECT_MaxID )
		return;

	int heroId = vecShowCard[index].unTypeID[level];
	if ( heroId <= 0 )
		return;

	CItemHero::SItemHero* pHero = theItemHero.FindHeroByHeroID(heroId);
	if (!pHero)
		return;

	if (s_CUI_ID_FRAME_zhujiangtujian.IsVisable())
	{
		s_CUI_ID_FRAME_zhujiangtujian._SetVisable(false);
	}
	s_CUI_ID_FRAME_zhujiangtujian.SetItemId(pHero->itemd_id);
	s_CUI_ID_FRAME_zhujiangtujian._SetVisable(true);
}

void CUI_ID_FRAME_CARD::ShowMountDetail( int index )
{
	if ( index < 0 || index >= PAGE_SIZE )
		return;

	int nsize = vecShowCard.size();
	if ( index >= nsize )
		return;

	short level = thePlayerRole.GetCharInfo2().otherdataclient.cards.shCardLevel[vecShowCard[index].shID];
	if ( level < 0 )
		level = vecShowCard[index].nLevel;

	int mountId = vecShowCard[index].unTypeID[0];
	if ( mountId <= 0 )
		return;

	s_CUI_ID_FRAME_SeekPet.SetVisable(true);
	s_CUI_ID_FRAME_SeekPet.SetCardMountByIdLevel( mountId, level );
}

void CUI_ID_FRAME_CARD::ShowPetDetail( int index )
{
	if ( index < 0 || index >= PAGE_SIZE )
		return;

	int nsize = vecShowCard.size();
	if ( index >= nsize )
		return;

	int petId = vecShowCard[index].unTypeID[0];
	if ( petId <= 0 )
		return;

	ItemDefine::SPetMonster*  m_pet = GettheItemDetail().GetPetById(petId);
	if ( !m_pet )
		return;

	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(true);
	std::vector<ItemDefine::SPetMonster*> m_petinfo;
	m_petinfo.push_back( m_pet );

	s_CUI_ID_FRAME_SuAnimalCard.SetCurrentPhyle( m_petinfo );
	s_CUI_ID_FRAME_SuAnimalCard.RefreshPage( m_pet, m_pet->phyle );
}

void CUI_ID_FRAME_CARD::RefreshAchieve( CardAchieveConfig::CardAchieveVector& achieveVec )
{
	int nSize = achieveVec.size();
	if ( nSize <= 0 )
		return;

	for (int i = 0; i < nSize; i++)
	{
		m_Group[i].SetVisible( true );

		bool IsHad = false;
		int nHasCount = 0;
		for (int j = 0; j < achieveVec[i].shCardCount; j++)
		{
			if ( achieveVec[i].shCardIDs[j] < 0 || achieveVec[i].shCardIDs[j] > More_nCardMax )
				continue;
			if ( thePlayerRole.GetCharInfo2().otherdataclient.cards.shCardLevel[achieveVec[i].shCardIDs[j]] >= 0 )
				nHasCount++;
		}

		if ( nHasCount >= achieveVec[i].shCardCount )
			IsHad = true;
		
		bool IsGet = false;
		if ( thePlayerRole.GetCharInfo2().otherdataclient.cards.unCardAchieve[ achieveVec[i].shID ] == 1 )
			IsGet = true;

		int nGSize = m_Group[i].GetControlSize();
		for (int j = 0; j < nGSize; j++)
		{
			switch (j)
			{
			case 0:
				{
					ControlPicture* pPic = (ControlPicture*)m_Group[i].GetControl(j);
					if ( !pPic )
						return;

					S_BaseData::S_Pic sPic;
					RECT rcClient;
					std::string strImg;

					if( IsHad )
					{
						rcClient.left = achieveVec[i].sBrightImg.nWidth * ( achieveVec[i].sBrightImg.nColumn - 1 );
						rcClient.top = achieveVec[i].sBrightImg.nHeight * ( achieveVec[i].sBrightImg.nRow - 1 );
						rcClient.right = rcClient.left + achieveVec[i].sBrightImg.nWidth;
						rcClient.bottom = rcClient.top + achieveVec[i].sBrightImg.nHeight;

						strImg = achieveVec[i].sBrightImg.strImg;
					}
					else
					{
						rcClient.left = achieveVec[i].sDarkImg.nWidth * ( achieveVec[i].sDarkImg.nColumn - 1 );
						rcClient.top = achieveVec[i].sDarkImg.nHeight * ( achieveVec[i].sDarkImg.nRow - 1 );
						rcClient.right = rcClient.left + achieveVec[i].sDarkImg.nWidth;
						rcClient.bottom = rcClient.top + achieveVec[i].sDarkImg.nHeight;

						strImg = achieveVec[i].sDarkImg.strImg;
					}
					sPic.SetPicStruct(strImg.c_str(), &rcClient, &rcClient);
					pPic->SetPic(&sPic, true);
					pPic->SetPicName(strImg.c_str());
				}
				break;
			case 1:
				{
					ControlButton* pText = (ControlButton*)m_Group[i].GetControl(j);
					if ( !pText )
						return;
					pText->SetVisable(false);
				}
				break;
			case 2:
				{
					ControlText* pText = (ControlText*)m_Group[i].GetControl(j);
					if ( !pText )
						return;
					
					pText->SetText( achieveVec[i].strName.c_str() );
				}
				break;
			case 3:
				{
					ControlText* pText = (ControlText*)m_Group[i].GetControl(j);
					if ( !pText )
						return;

					char buf[24] = {0};
					sprintf_s( buf, sizeof(buf) - 1, "%s:%d/%d", theXmlString.GetString(eText_CardIcon_GetNum), nHasCount, achieveVec[i].shCardCount );

					pText->SetText( buf );

					if ( !IsHad )
					{
						CardIconConfig::CardVector vecCard = theCardIconConfig.GetCardVec();
						std::string str;
						str += theXmlString.GetString( eText_CardIcon_Lack );
						for (int k = 0; k < achieveVec[i].shCardCount; k++)
						{
							if ( achieveVec[i].shCardIDs[k] < 0 || achieveVec[i].shCardIDs[k] > More_nCardMax )
								continue;
							if ( thePlayerRole.GetCharInfo2().otherdataclient.cards.shCardLevel[achieveVec[i].shCardIDs[k]] < 0 )
							{
								str += vecCard[achieveVec[i].shCardIDs[k]].strName;
								str += "  ";
							}
						}

						pText->setShowTip(true);
						pText->setTip(str.c_str());
					}
					
				}
				break;
			case 4:
				{
					ControlButton* pButton = (ControlButton*)m_Group[i].GetControl(j);
					if ( !pButton )
						return;
					pButton->SetEnable( false );
					pButton->setTip("");
					pButton->SetShowTip(false);

					if ( IsHad )
					{
						if ( !IsGet )
							pButton->SetEnable( true );
						else
						{
							pButton->setTip( theXmlString.GetString( eText_CardIcon_HadGet ) );
							pButton->SetShowTip(true);
						}
					}		
				}
				break;
			case 5:
				{
					ControlText* pText = (ControlText*)m_Group[i].GetControl(j);
					if ( !pText )
						return;
					pText->SetText("");
					pText->setTip("");
					pText->setShowTip(false);
				}
				break;
			default:
				break;
			}
		}
	}
}

void CUI_ID_FRAME_CARD::OnButtonAchieve( int index )
{
	if ( index < 0 || index >= PAGE_SIZE )
		return;

	MsgCardAchieve msg;
	msg.stAchieveId = vecShowAchieve[index].shID;
	GettheNetworkInput().SendMsg( &msg );
}