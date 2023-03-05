#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimalMain.h"
#include "GlobalDef.h"
#include "PlayerRole.h"
#include "Skill.h"
#include "shortcutkey_configure.h"
#include "ScreenInfoManager.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "ActionUI.h"
#include "baseProperty.h"
#include "SelectPet.h"
#include "SuAnimal.h"
CUI_ID_FRAME_SuAnimalMain s_CUI_ID_FRAME_SuAnimalMain;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimalMain, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimalMain, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain0OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain0OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain0OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain0OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain5OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain5OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain5OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain5OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain6OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain6OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain6OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain6OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain7OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain7OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain7OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain7OnIconRButtonUp )
CUI_ID_FRAME_SuAnimalMain::CUI_ID_FRAME_SuAnimalMain()
{
	// Member
	m_pID_FRAME_SuAnimalMain = NULL;
	m_pID_TEXT_PetSkillText = NULL;
	m_pID_PICTURE_PetMain0 = NULL;
	m_pID_PICTURE_PetMain1 = NULL;
	m_pID_PICTURE_PetMain2 = NULL;
	m_pID_PICTURE_PetMain3 = NULL;
	m_pID_PICTURE_PetMain4 = NULL;
	m_pID_PICTURE_PetMain5 = NULL;
	m_pID_LISTIMG_PetMain0 = NULL;
	m_pID_LISTIMG_PetMain1 = NULL;
	m_pID_LISTIMG_PetMain2 = NULL;
	m_pID_LISTIMG_PetMain3 = NULL;
	m_pID_LISTIMG_PetMain4 = NULL;
	m_pID_LISTIMG_PetMain5 = NULL;
	m_pID_PICTURE_PetMain6 = NULL;
	m_pID_PICTURE_PetMain7 = NULL;
	m_pID_LISTIMG_PetMain6 = NULL;
	m_pID_LISTIMG_PetMain7 = NULL;
}

// Frame
bool CUI_ID_FRAME_SuAnimalMain::OnFrameRun()
{
	UpdateUIState();
	return true;
}

bool CUI_ID_FRAME_SuAnimalMain::OnFrameRender()
{
	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain0OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	UseSkill(pItem);
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	UseSkill(pItem);
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	UseSkill(pItem);
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	UseSkill(pItem);
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	UseSkill(pItem);
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain5OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	UseSkill(pItem);
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain6OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain6OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	UseSkill(pItem);
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain7OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain7OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain7OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	UseSkill(pItem);
	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::ID_LISTIMG_PetMain7OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// 装载UI
bool CUI_ID_FRAME_SuAnimalMain::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimalMain.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuAnimalMain.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_SuAnimalMain::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SuAnimalMain, s_CUI_ID_FRAME_SuAnimalMainOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SuAnimalMain, s_CUI_ID_FRAME_SuAnimalMainOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain0, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain0OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain0, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain0OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain0, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain0OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain0, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain0OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain1, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain1, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain1, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain1, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain2, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain2, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain2, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain2, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain3, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain3, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain3, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain3, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain3OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain4, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain4, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain4, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain4, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain4OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain5, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain5OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain5, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain5OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain5, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain5OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain5, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain5OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain6, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain6OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain6, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain6OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain6, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain6OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain6, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain6OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain7, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain7OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain7, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain7OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain7, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain7OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain7, s_CUI_ID_FRAME_SuAnimalMainID_LISTIMG_PetMain7OnIconRButtonUp );

	m_pID_FRAME_SuAnimalMain = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SuAnimalMain );
	m_pID_TEXT_PetSkillText = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_TEXT_PetSkillText );
	m_pID_PICTURE_PetMain0 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_PICTURE_PetMain0 );
	m_pID_PICTURE_PetMain1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_PICTURE_PetMain1 );
	m_pID_PICTURE_PetMain2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_PICTURE_PetMain2 );
	m_pID_PICTURE_PetMain3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_PICTURE_PetMain3 );
	m_pID_PICTURE_PetMain4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_PICTURE_PetMain4 );
	m_pID_PICTURE_PetMain5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_PICTURE_PetMain5 );
	m_pID_LISTIMG_PetMain0 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain0 );
	m_pID_LISTIMG_PetMain1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain1 );
	m_pID_LISTIMG_PetMain2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain2 );
	m_pID_LISTIMG_PetMain3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain3 );
	m_pID_LISTIMG_PetMain4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain4 );
	m_pID_LISTIMG_PetMain5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain5 );
	m_pID_PICTURE_PetMain6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_PICTURE_PetMain6 );
	m_pID_PICTURE_PetMain7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_PICTURE_PetMain7 );
	m_pID_LISTIMG_PetMain6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain6 );
	m_pID_LISTIMG_PetMain7 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalMain, ID_LISTIMG_PetMain7 );
	assert( m_pID_FRAME_SuAnimalMain );
	assert( m_pID_TEXT_PetSkillText );
	assert( m_pID_PICTURE_PetMain0 );
	assert( m_pID_PICTURE_PetMain1 );
	assert( m_pID_PICTURE_PetMain2 );
	assert( m_pID_PICTURE_PetMain3 );
	assert( m_pID_PICTURE_PetMain4 );
	assert( m_pID_PICTURE_PetMain5 );
	assert( m_pID_LISTIMG_PetMain0 );
	assert( m_pID_LISTIMG_PetMain1 );
	assert( m_pID_LISTIMG_PetMain2 );
	assert( m_pID_LISTIMG_PetMain3 );
	assert( m_pID_LISTIMG_PetMain4 );
	assert( m_pID_LISTIMG_PetMain5 );
	assert( m_pID_PICTURE_PetMain6 );
	assert( m_pID_PICTURE_PetMain7 );
	assert( m_pID_LISTIMG_PetMain6 );
	assert( m_pID_LISTIMG_PetMain7 );

	SortControl();
	m_pID_FRAME_SuAnimalMain->enableEscKey( false );
	m_pID_FRAME_SuAnimalMain->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	// 设置LISTIMAGE为可拖动
	m_pID_LISTIMG_PetMain4->SetDisableCanbePick(false);
	m_pID_LISTIMG_PetMain4->ShowPressEffect(true);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_SuAnimalMain::_UnLoadUI()
{
	m_pID_FRAME_SuAnimalMain = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimalMain.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_SuAnimalMain::_IsVisable()
{
	if(!m_pID_FRAME_SuAnimalMain)
		return false;

	return m_pID_FRAME_SuAnimalMain->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_SuAnimalMain::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_SuAnimalMain)
		return;

	m_pID_FRAME_SuAnimalMain->SetVisable( bVisable );
}


void CUI_ID_FRAME_SuAnimalMain::RefreshPetSkill()
{
	if(!IsVisable())
		return;

	SPetItem& pet = thePlayerRole.GetPetByIndex(thePlayerRole.GetActivedPetIndex());
	if(pet.baseInfo.petId == InvalidLogicNumber)
		return;

	CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.GetPage(CUISkillMgr::ePetSkill);
	if (!pSkillTree)
	{
		return;
	}

	SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

	for ( int i = 0; i < PET_SKILLNUM; ++i )
	{
		m_pID_LISTIMG_PetMain[i]->Clear();
		m_pID_PICTURE_PetMain[i]->SetVisable(false);
		m_pID_LISTIMG_PetMain[i]->SetVisable(false);
	}

	AN_Configure_ShortcutKey::ShortCutKey_Configure eKey = (AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_PetSkill1 + 0);
	ControlIconDrag::S_ListImg stItem;
	stItem.SetData( CUI_ID_FRAME_BaseProperty::TYPE_PETATTACK, true);
	stItem.SetFlags(CUISkillMgr::eCommon);
	stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);
	m_pID_LISTIMG_PetMain[0]->SetItem(&stItem);
	m_pID_LISTIMG_PetMain[0]->SetVisable(true);
	m_pID_PICTURE_PetMain[0]->SetVisable(true);

	stItem.Clear();
	eKey = (AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_PetSkill1 + 1);
	stItem.SetData( CUI_ID_FRAME_BaseProperty::TYPE_PETFOLLOW, true);
	stItem.SetFlags(CUISkillMgr::eCommon);
	stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);
	m_pID_LISTIMG_PetMain[1]->SetItem(&stItem);
	m_pID_LISTIMG_PetMain[1]->SetVisable(true);
	m_pID_PICTURE_PetMain[1]->SetVisable(true);

	stItem.Clear();
	eKey = (AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_PetSkill1 + 2);
	stItem.SetData(CUI_ID_FRAME_BaseProperty::TYPE_PETDISMISS, true);
	stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);
	stItem.SetFlags(CUISkillMgr::eCommon);
	m_pID_LISTIMG_PetMain[2]->SetItem(&stItem);
	m_pID_LISTIMG_PetMain[2]->SetVisable(true);
	m_pID_PICTURE_PetMain[2]->SetVisable(true);

	stItem.Clear();
	eKey = (AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_PetSkill1 + 3);
	stItem.SetData( CUI_ID_FRAME_BaseProperty::TYPE_PETAICOMMAND, true);
	stItem.SetFlags(CUISkillMgr::eCommon);
	stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);
	m_pID_LISTIMG_PetMain[3]->SetItem(&stItem);
	m_pID_LISTIMG_PetMain[3]->SetVisable(true);
	m_pID_PICTURE_PetMain[3]->SetVisable(true);

	int skillCount = 4;
	for ( int i = 0; i < PET_SKILLNUM; ++i )
	{
		unsigned short usSkillId = pet.skillInfo.skills[i].ustSkillID;
		if ( usSkillId == 0)
			continue;

		unsigned short usLevel = pet.skillInfo.skills[i].stSkillLevel;
		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(usSkillId,usLevel);
		if (!pItemSkill)
			continue;

		const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue(usSkillId);
		if ( !pIcon )
			continue;

		AN_Configure_ShortcutKey::ShortCutKey_Configure eKey = (AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_PetSkill1 + skillCount);

		ControlIconDrag::S_ListImg stItem;
		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
		stItem.SetData( usSkillId, usLevel, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
		stItem.SetFlags(CUISkillMgr::ePetSkill);
		stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

		SkillBag::SColdTime *pTime = NULL;
		pTime = thePlayerRole.m_PetSkillBag.GetColdTimeById( usSkillId );
		if ( pTime )
			stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );

		if ( pItemSkill->sSkillCategory == ItemDefine::SCT_PetMasterManualControl)
		{
			m_pID_LISTIMG_PetMain[skillCount]->SetItem(&stItem);
			m_pID_LISTIMG_PetMain[skillCount]->SetVisable(true);
			m_pID_PICTURE_PetMain[skillCount]->SetVisable(true);

			++skillCount;
		}
	}

	if ( skillCount == 0 )
	{
		SetVisable( false );
	}
}

bool CUI_ID_FRAME_SuAnimalMain::IsSkillList(const ControlObject* pObject)
{
	if(!m_pID_FRAME_SuAnimalMain)
		return false;

	for (int i = 0;i < PET_SKILLNUM;++i)
	{
		if(pObject == m_pID_LISTIMG_PetMain[i])
			return true;
	}

	return false;
}

bool CUI_ID_FRAME_SuAnimalMain::UseSkill(ControlIconDrag::S_ListImg* pItem)
{
	if( !pItem )
	{
		return false;
	}

	switch (pItem->m_dwFlags)
	{
	case CUISkillMgr::ePetSkill:
		{
			SCharSkill *pSkill = thePlayerRole.m_PetSkillBag.GetSkillByID( pItem->m_pkIconInfo->Id() );
			if (pSkill == NULL)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_FuJiang_NotActived ) );
				return true;
			}

			CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
			if (pMe != NULL)
			{
				MsgPetCommand petcommand;
				petcommand.header.stID = pMe->GetID();
				petcommand.shPetCommandIndex = MsgPetCommand::eUseSkill;
				petcommand.skillId = pSkill->ustSkillID;
				petcommand.skillLevel = pSkill->stSkillLevel;

				if (-1 == GettheNetworkInput().SendMsg(&petcommand))
				{
					return false;
				}

				// 设置技能CD
				SkillBag::SColdTime *cd = thePlayerRole.m_PetSkillBag.GetColdTimeById(pSkill->ustSkillID);
				if (cd != NULL)
				{
					pItem->SetTime(cd->dwColdStartTime, /*cd->dwColdTime*/ 15000);
				}
			}

			//theHeroGame.GetPlayerMgr()->SetCurUseSkill( pSkill->ustSkillID,
			//pSkill->stSkillLevel );
			//thePlayerRole.UpdateUI();
			//theHeroGame.GetPlayerMgr()->OnSkill( FALSE );
		}
		break;
	case CUISkillMgr::eCommon:
		{
			s_CUI_ID_FRAME_ActionUI.SetCurFunction( pItem->m_pkIconInfo->Id() );
			s_CUI_ID_FRAME_ActionUI.UseFunction();
		}
		break;
	}

	return true;
}

void CUI_ID_FRAME_SuAnimalMain::SetHotkeyPressIndex(int nIndex)
{
	if(!m_pID_FRAME_SuAnimalMain)
		return;

	m_nSkillIndex = nIndex;
	if (m_nSkillIndex < 0 || m_nSkillIndex >= PET_SKILLNUM)
	{
		return;
	}

	if (m_pID_LISTIMG_PetMain[m_nSkillIndex]->IsVisable())
	{
		ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_PetMain[m_nSkillIndex]->GetItemByIndex(0);
		if (pItem)
		{
			UseSkill(pItem);
		}
	}
}

void CUI_ID_FRAME_SuAnimalMain::SortControl()
{
	if(!m_pID_FRAME_SuAnimalMain)
		return;

	m_pID_LISTIMG_PetMain[0] = m_pID_LISTIMG_PetMain0;
	m_pID_LISTIMG_PetMain[1] = m_pID_LISTIMG_PetMain1;
	m_pID_LISTIMG_PetMain[2] = m_pID_LISTIMG_PetMain2;
	m_pID_LISTIMG_PetMain[3] = m_pID_LISTIMG_PetMain3;
	m_pID_LISTIMG_PetMain[4] = m_pID_LISTIMG_PetMain4;
	m_pID_LISTIMG_PetMain[5] = m_pID_LISTIMG_PetMain5;
	m_pID_LISTIMG_PetMain[6] = m_pID_LISTIMG_PetMain6;
	m_pID_LISTIMG_PetMain[7] = m_pID_LISTIMG_PetMain7;

	m_pID_PICTURE_PetMain[0] = m_pID_PICTURE_PetMain0;
	m_pID_PICTURE_PetMain[1] = m_pID_PICTURE_PetMain1;
	m_pID_PICTURE_PetMain[2] = m_pID_PICTURE_PetMain2;
	m_pID_PICTURE_PetMain[3] = m_pID_PICTURE_PetMain3;
	m_pID_PICTURE_PetMain[4] = m_pID_PICTURE_PetMain4;
	m_pID_PICTURE_PetMain[5] = m_pID_PICTURE_PetMain5;
	m_pID_PICTURE_PetMain[6] = m_pID_PICTURE_PetMain6;
	m_pID_PICTURE_PetMain[7] = m_pID_PICTURE_PetMain7;
}
void CUI_ID_FRAME_SuAnimalMain::UpdateUIState()
{
	if(IsVisable()) return;
	SPetItem *pPet = thePlayerRole.GetActivedPet();
	if(!pPet)
		return;
	else
	{

		thePlayerRole.ActivePetByGUID(pPet->baseInfo.guid);
		thePlayerRole.AddPetSkill(*pPet);
		s_CUI_ID_FRAME_SuAnimal.Refresh();
		s_CUI_ID_FRAME_SuAnimal.SetPetCallIndex(thePlayerRole.GetPetIndexByName(pPet->baseInfo.szName));		//出战的时候设置召唤的副将索引
		s_CUI_ID_FRAME_SuAnimal.RefreshButtonGroup();
		s_CUI_Group.Refeash();
		s_CUI_ID_FRAME_SuAnimalMain.SetVisable(true);
		s_CUI_ID_FRAME_SuAnimalMain.RefreshPetSkill();
		s_CUI_ID_FRAME_SelectPet.Refresh(true);
	}
} 