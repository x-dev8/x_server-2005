/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\NewSkillMain.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "NewSkillMain.h"
#include "Skill.h"
#include "ItemDetail.h"

CUI_ID_FRAME_NewSkillMain s_CUI_ID_FRAME_NewSkillMain;
MAP_FRAME_RUN( s_CUI_ID_FRAME_NewSkillMain, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_NewSkillMain, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_NewSkillMain, ID_LISTIMG_HotkeyOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_NewSkillMain, ID_LISTIMG_HotkeyOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_NewSkillMain, ID_LISTIMG_HotkeyOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_NewSkillMain, ID_LISTIMG_HotkeyOnIconRButtonUp )
CUI_ID_FRAME_NewSkillMain::CUI_ID_FRAME_NewSkillMain()
{
	// Member
	m_pID_FRAME_NewSkillMain = NULL;
	m_pID_LISTIMG_Hotkey = NULL;
    m_bAddSkill = false;
    m_skillIds.clear();
	m_skillLevels.clear();
}
// Frame
bool CUI_ID_FRAME_NewSkillMain::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_NewSkillMain::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_NewSkillMain::ID_LISTIMG_HotkeyOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															  ControlIconDrag::S_ListImg* pItemDrag,
															  ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_NewSkillMain)
		return false;
	return false;
}
bool CUI_ID_FRAME_NewSkillMain::ID_LISTIMG_HotkeyOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_NewSkillMain)
		return false;
	return false;
}
bool CUI_ID_FRAME_NewSkillMain::ID_LISTIMG_HotkeyOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_NewSkillMain)
		return false;
	return false;
}
bool CUI_ID_FRAME_NewSkillMain::ID_LISTIMG_HotkeyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_NewSkillMain)
		return false;
	return false;
}

void CUI_ID_FRAME_NewSkillMain::OnVisibleChanged(ControlObject* pSender)
{
	if (s_CUI_ID_FRAME_NewSkillMain.IsVisable() == false)
	{
		s_CUI_ID_FRAME_NewSkillMain.m_skillIds.clear();
		s_CUI_ID_FRAME_NewSkillMain.m_skillLevels.clear();
		s_CUI_ID_FRAME_NewSkillMain._Refresh();
	}
}

// 装载UI
bool CUI_ID_FRAME_NewSkillMain::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\NewSkillMain.MEUI", true, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\NewSkillMain.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_NewSkillMain::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_NewSkillMain, s_CUI_ID_FRAME_NewSkillMainOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_NewSkillMain, s_CUI_ID_FRAME_NewSkillMainOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_NewSkillMain, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_NewSkillMainID_LISTIMG_HotkeyOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_NewSkillMain, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_NewSkillMainID_LISTIMG_HotkeyOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_NewSkillMain, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_NewSkillMainID_LISTIMG_HotkeyOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_NewSkillMain, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_NewSkillMainID_LISTIMG_HotkeyOnIconRButtonUp );

	m_pID_FRAME_NewSkillMain = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_NewSkillMain );
	m_pID_LISTIMG_Hotkey = (ControlListImage*)theUiManager.FindControl( ID_FRAME_NewSkillMain, ID_LISTIMG_Hotkey );
	assert( m_pID_FRAME_NewSkillMain );
	assert( m_pID_LISTIMG_Hotkey );

	m_pID_LISTIMG_Hotkey->ShowPressEffect(true);
	m_pID_LISTIMG_Hotkey->SetShowAllInfo( true );
	m_pID_LISTIMG_Hotkey->SetDisableCanbePick( true );
	m_pID_LISTIMG_Hotkey->SetOnlyShowItemIcon(true);
	m_pID_LISTIMG_Hotkey->SetDelayTime( g_ControlListImageShortDelayTime );
	m_pID_FRAME_NewSkillMain->SetVisable(false);
	m_pID_FRAME_NewSkillMain->SetMsgHoldup(false);

	m_pID_FRAME_NewSkillMain->SetOnVisibleChangedFun(OnVisibleChanged);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_NewSkillMain::_UnLoadUI()
{
	m_skillIds.clear();
	m_skillLevels.clear();
	m_pID_FRAME_NewSkillMain = NULL;
	m_pID_LISTIMG_Hotkey = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\NewSkillMain.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_NewSkillMain::_IsVisable()
{
    if(!m_pID_FRAME_NewSkillMain)
        return false;

	return m_pID_FRAME_NewSkillMain->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_NewSkillMain::_SetVisable( const bool bVisable )
{
    if(m_pID_FRAME_NewSkillMain)
	   m_pID_FRAME_NewSkillMain->SetVisable( bVisable );
}

void CUI_ID_FRAME_NewSkillMain::AddSkill(int id, int level /*= 1*/)
{
    if (!m_bAddSkill)
		return;

	ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(id, level);
	if (!pItemSkill || pItemSkill->sSkillCategory == ItemDefine::SCT_Passive || pItemSkill->sSkillCategory == ItemDefine::SCT_HeroPassive)
		return;

	m_skillIds.push_back(id);
	m_skillLevels.push_back(level);

	_Refresh();
}
void CUI_ID_FRAME_NewSkillMain::AddSkillByCheck(int id,int level)
{
	if (!m_bAddSkill)
		return;
	ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(id, level);
	if (!pItemSkill || pItemSkill->sSkillCategory == ItemDefine::SCT_Passive || pItemSkill->sSkillCategory == ItemDefine::SCT_HeroPassive)
		return;
	std::vector<int>::iterator it = find(m_skillIds.begin(),m_skillIds.end(),id);
	if(it != m_skillIds.end())
		return;
	m_skillIds.push_back(id);
	m_skillLevels.push_back(level);

	_Refresh();
}
void CUI_ID_FRAME_NewSkillMain::RemoveSkill(unsigned int index)
{
	if (m_pID_LISTIMG_Hotkey->GetItemCnt() <= index)
		return;

	std::vector<int>::iterator it = std::find(m_skillIds.begin(), m_skillIds.end(), m_pID_LISTIMG_Hotkey->GetItemByIndex(index)->m_pkIconInfo->Id());
	if (it != m_skillIds.end())
	{
		for ( std::vector<int>::iterator it2 = m_skillLevels.begin(), it1 = m_skillIds.begin(); it2 != m_skillLevels.end(); it1++, it2++ )
		{
			if ( it1 == it )
			{
				m_skillLevels.erase( it2 );
				break;
			}
		}
		m_skillIds.erase(it);
		_Refresh();
	}
}

void CUI_ID_FRAME_NewSkillMain::_Refresh()
{
    SetVisable( !m_skillIds.empty() );

    if( !m_pID_FRAME_NewSkillMain )
        return;
	if ( !m_pID_LISTIMG_Hotkey )
		return;
	
	m_pID_LISTIMG_Hotkey->Clear();

	int end = m_skillIds.size() - m_pID_LISTIMG_Hotkey->GetRowItemCnt();
	if (end < 0)
		end = 0;
	for (int i = end; i < m_skillIds.size(); ++i)
	{
		int id = m_skillIds[i];
		int level = m_skillLevels[i];

		ControlIconDrag::S_ListImg stItem;

		SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(id);
		if (iconSet)
			stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);
		stItem.SetData( id, level, eIcon_Enable, true, eTipFlag_SkillNoNextLevel );
		stItem.SetFlags(CUISkillMgr::eProfession);

		m_pID_LISTIMG_Hotkey->SetItem(&stItem);
	}
}

int  CUI_ID_FRAME_NewSkillMain::GetListImageIndex(ControlIconDrag::S_ListImg* pImg)
{
    if(!pImg ||!m_pID_FRAME_NewSkillMain)
        return -1;

    return m_pID_LISTIMG_Hotkey->GetItemIndex( pImg );
}
