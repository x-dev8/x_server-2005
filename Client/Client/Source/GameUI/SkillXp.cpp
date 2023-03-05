/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\SkillXp.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SkillXp.h"
#include "Skill.h"
#include "PlayerRole.h"
#include "ActionUI.h"

CUI_ID_FRAME_XpSkill s_CUI_ID_FRAME_XpSkill;
MAP_FRAME_RUN( s_CUI_ID_FRAME_XpSkill, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_XpSkill, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill5OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill5OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill5OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill5OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill6OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill6OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill6OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill6OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill7OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill7OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill7OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_XpSkill, ID_LISTIMG_Skill7OnIconRButtonUp )
CUI_ID_FRAME_XpSkill::CUI_ID_FRAME_XpSkill()
{
	// Member
	m_pID_FRAME_XpSkill = NULL;
	m_pID_PICTURE_SkillBack = NULL;
	m_pID_LISTIMG_Skill[1 - 1] = NULL;
	m_pID_LISTIMG_Skill[2 - 1] = NULL;
	m_pID_LISTIMG_Skill[3 - 1] = NULL;
	m_pID_LISTIMG_Skill[4 - 1] = NULL;
	m_pID_LISTIMG_Skill[5 - 1] = NULL;
	m_pID_LISTIMG_Skill[6 - 1] = NULL;
	m_pID_LISTIMG_Skill[7 - 1] = NULL;
	m_pID_TEXT_SkillText[1 - 1] = NULL;
	m_pID_TEXT_SkillText[2 - 1] = NULL;
	m_pID_TEXT_SkillText[3 - 1] = NULL;
	m_pID_TEXT_SkillText[4 - 1] = NULL;
	m_pID_TEXT_SkillText[5 - 1] = NULL;
	m_pID_TEXT_SkillText[6 - 1] = NULL;
	m_pID_TEXT_SkillText[7 - 1] = NULL;

}
// Frame
bool CUI_ID_FRAME_XpSkill::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_XpSkill::OnFrameRender()
{
	return true;
}

void UsingSkill(ControlIconDrag::S_ListImg* pItem)
{
	if (pItem)
	{
		s_CUI_ID_FRAME_ActionUI.SetCurFunction( pItem->m_pkIconInfo->Id() );
		s_CUI_ID_FRAME_ActionUI.UseFunction();
	}
}

// ListImg / ListEx
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill5OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill6OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill6OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill7OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill7OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill7OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}
bool CUI_ID_FRAME_XpSkill::ID_LISTIMG_Skill7OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	UsingSkill(pItem);
	return false;
}

// 装载UI
bool CUI_ID_FRAME_XpSkill::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SkillXp.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SkillXp.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_XpSkill::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_XpSkill, s_CUI_ID_FRAME_XpSkillOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_XpSkill, s_CUI_ID_FRAME_XpSkillOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_XpSkill, ID_LISTIMG_Skill1, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill1, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill1, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_XpSkill, ID_LISTIMG_Skill1, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_XpSkill, ID_LISTIMG_Skill2, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill2, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill2, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_XpSkill, ID_LISTIMG_Skill2, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_XpSkill, ID_LISTIMG_Skill3, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill3, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill3, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_XpSkill, ID_LISTIMG_Skill3, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill3OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_XpSkill, ID_LISTIMG_Skill4, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill4, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill4, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_XpSkill, ID_LISTIMG_Skill4, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill4OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_XpSkill, ID_LISTIMG_Skill5, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill5OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill5, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill5OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill5, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill5OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_XpSkill, ID_LISTIMG_Skill5, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill5OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_XpSkill, ID_LISTIMG_Skill6, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill6OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill6, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill6OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill6, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill6OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_XpSkill, ID_LISTIMG_Skill6, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill6OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_XpSkill, ID_LISTIMG_Skill7, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill7OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill7, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill7OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_XpSkill, ID_LISTIMG_Skill7, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill7OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_XpSkill, ID_LISTIMG_Skill7, s_CUI_ID_FRAME_XpSkillID_LISTIMG_Skill7OnIconRButtonUp );

	m_pID_FRAME_XpSkill = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_XpSkill );
	m_pID_PICTURE_SkillBack = (ControlPicture*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_PICTURE_SkillBack );
	m_pID_LISTIMG_Skill[1 - 1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_LISTIMG_Skill1 );
	m_pID_LISTIMG_Skill[2 - 1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_LISTIMG_Skill2 );
	m_pID_LISTIMG_Skill[3 - 1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_LISTIMG_Skill3 );
	m_pID_LISTIMG_Skill[4 - 1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_LISTIMG_Skill4 );
	m_pID_LISTIMG_Skill[5 - 1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_LISTIMG_Skill5 );
	m_pID_LISTIMG_Skill[6 - 1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_LISTIMG_Skill6 );
	m_pID_LISTIMG_Skill[7 - 1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_LISTIMG_Skill7 );
	m_pID_TEXT_SkillText[1 - 1] = (ControlText*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_TEXT_SkillText1 );
	m_pID_TEXT_SkillText[2 - 1] = (ControlText*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_TEXT_SkillText2 );
	m_pID_TEXT_SkillText[3 - 1] = (ControlText*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_TEXT_SkillText3 );
	m_pID_TEXT_SkillText[4 - 1] = (ControlText*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_TEXT_SkillText4 );
	m_pID_TEXT_SkillText[5 - 1] = (ControlText*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_TEXT_SkillText5 );
	m_pID_TEXT_SkillText[6 - 1] = (ControlText*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_TEXT_SkillText6 );
	m_pID_TEXT_SkillText[7 - 1] = (ControlText*)theUiManager.FindControl( ID_FRAME_XpSkill, ID_TEXT_SkillText7 );

	m_pID_FRAME_XpSkill->SetFather( s_CUI_ID_FRAME_SKILL.GetFrame() );
	m_pID_FRAME_XpSkill->SetMsgHoldup( false );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_XpSkill::_UnLoadUI()
{
	m_pID_FRAME_XpSkill = NULL;
	m_pID_PICTURE_SkillBack = NULL;
	m_pID_LISTIMG_Skill[1 - 1] = NULL;
	m_pID_LISTIMG_Skill[2 - 1] = NULL;
	m_pID_LISTIMG_Skill[3 - 1] = NULL;
	m_pID_LISTIMG_Skill[4 - 1] = NULL;
	m_pID_LISTIMG_Skill[5 - 1] = NULL;
	m_pID_LISTIMG_Skill[6 - 1] = NULL;
	m_pID_LISTIMG_Skill[7 - 1] = NULL;
	m_pID_TEXT_SkillText[1 - 1] = NULL;
	m_pID_TEXT_SkillText[2 - 1] = NULL;
	m_pID_TEXT_SkillText[3 - 1] = NULL;
	m_pID_TEXT_SkillText[4 - 1] = NULL;
	m_pID_TEXT_SkillText[5 - 1] = NULL;
	m_pID_TEXT_SkillText[6 - 1] = NULL;
	m_pID_TEXT_SkillText[7 - 1] = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SkillXp.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_XpSkill::_IsVisable()
{
	if ( !m_pID_FRAME_XpSkill )
		return false;
	return m_pID_FRAME_XpSkill->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_XpSkill::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_XpSkill )
		return ;
	m_pID_FRAME_XpSkill->SetVisable( bVisable );
}

void CUI_ID_FRAME_XpSkill::Update()
{
	for (int i = 0; i < SKILL_XP_NUM; ++i)
		m_pID_LISTIMG_Skill[i]->SetVisable(false);

	for (int i = 0; i < SKILL_XP_NUM; ++i)
		m_pID_TEXT_SkillText[i]->SetVisable(false);


	CUISkillTreeConfig::SkillTreePage* pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
		GetPage(CUISkillMgr::eXpSkill);
	if (!pSkillTree)
		return;

	SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

	for (size_t i = 0; i< pSkillIcon->GetLength(); ++i)
	{
		const SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];

		int level = 0;
		SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(pIcon->iconid);
		if (pSkill)
			level = pSkill->stSkillLevel;

		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pIcon->iconid, level + 1);
		if (!pItemSkill)
		{
			pItemSkill = GettheItemDetail().GetSkillByID(pIcon->iconid, level);
			if (!pItemSkill)
				continue;
		}

		bool bEnable = false;
		bool bCanLearn = false;
		if (level > 0)
		{
			bEnable = true;
		}
		else if (pItemSkill->nLearnNeedExp == 0)
		{
			bEnable = false;
		}

		//------------------------------------------
		ControlIconDrag::S_ListImg stItem;
		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
		stItem.SetData(pIcon->iconid, level, bEnable ? eIcon_Enable: eIcon_Disable, 0, eTipFlag_SkillNoNextLevel );
		stItem.SetFlags(CUISkillMgr::eXpSkill);

		if (pIcon->index < SKILL_XP_NUM && pIcon->iconid != 0)
		{
			m_pID_LISTIMG_Skill[pIcon->index]->SetItem(&stItem, 0);
			m_pID_LISTIMG_Skill[pIcon->index]->SetVisable(true);

			if ( pIcon->index < SKILL_XP_NUM)
			{
				m_pID_TEXT_SkillText[pIcon->index]->SetText(pItemSkill->GetSkillName());
				m_pID_TEXT_SkillText[pIcon->index]->SetVisable(true);
			}
		}
	}
}

bool CUI_ID_FRAME_XpSkill::IsSkillList( const ControlObject* pObject )
{
	for (int i = 0; i < SKILL_XP_NUM; ++i)
	{
		if (m_pID_LISTIMG_Skill[i] ==  pObject)
		{
			return true;
		}		
	}
	return false;

}
