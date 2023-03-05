/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\SkillTreeSpear.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SkillTree.h"
#include "Skill.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "ActionUI.h"

CUI_ID_FRAME_SkillTree s_CUI_ID_FRAME_SkillTree;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SkillTree, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SkillTree, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SkillTree, ID_LISTIMG_SkillOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillTree, ID_LISTIMG_SkillOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillTree, ID_LISTIMG_SkillOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillTree, ID_LISTIMG_SkillOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillTree, ID_BUTTON_SkillOnButtonClick )
CUI_ID_FRAME_SkillTree::CUI_ID_FRAME_SkillTree()
{
	// Member
	m_pID_FRAME_SkillTree = NULL;
	//m_pID_PICTURE_DI2 = NULL;
	m_pID_PICTURE_Fenge = NULL;
	//m_pID_TEXT_SkillPoint = NULL;

}
// Frame
bool CUI_ID_FRAME_SkillTree::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SkillTree::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SkillTree::ID_LISTIMG_SkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItemDrag,
															ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SkillTree )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillTree::ID_LISTIMG_SkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillTree )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillTree::ID_LISTIMG_SkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillTree )
		return false;
	if( pItem )
	{
		s_CUI_ID_FRAME_SKILL.UseSkill( pItem );
	}
	return true;
}
bool CUI_ID_FRAME_SkillTree::ID_LISTIMG_SkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillTree )
		return false;
	if( pItem )
	{
		s_CUI_ID_FRAME_SKILL.UseSkill( pItem );
	}
	return false;
}
// Button
bool CUI_ID_FRAME_SkillTree::ID_BUTTON_SkillOnButtonClick( ControlObject* pSender )
{
    return true;

	if( !m_pID_FRAME_SkillTree )
		return false;
	for (int i = 0; i < m_skillUps.size(); ++i)
	{
		if (m_skillUps[i] == pSender)
		{
			short stSkillId = m_skillTrees[i]->GetItemByIndex(0)->m_pkIconInfo->GetItemId();
			SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(stSkillId);
			if (!pSkill)
			{
				MsgLearnSkill msg;
				msg.stSkillId = stSkillId;
				GettheNetworkInput().SendMsg( &msg );
			}
			else
			{
				MsgReqUpSkill msg;
				msg.stSkillId = stSkillId;
				GettheNetworkInput().SendMsg( &msg );
			}
			break;
		}
	}
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SkillTree::_LoadUI()
{
	std::string filename("Data\\UI\\SkillTree");

	switch( thePlayerRole.GetProfession() )
	{
	case EArmType_Mage:
		m_professionName = "Staff";
		break;
	case EArmType_Warrior:
		m_professionName = "Spear";
		break;
	case EArmType_Assassin:
		m_professionName = "Sword";
		break;
	case EArmType_Taoist:
		m_professionName = "Fan";
		break;
	case EArmType_Hunter:
		m_professionName = "Bow";
		break;
	}

	filename += m_professionName;
	filename += ".MEUI";
	DWORD dwResult = theUiManager.AddFrame( filename.c_str() );
	if ( dwResult == 0 )
	{
		std::string err = "读取文件[" + filename + "失败";
		MESSAGE_BOX(err.c_str())
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SkillTree::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SkillTree, s_CUI_ID_FRAME_SkillTreeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SkillTree, s_CUI_ID_FRAME_SkillTreeOnFrameRender );

	m_pID_FRAME_SkillTree = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SkillTree );
	//m_pID_PICTURE_DI2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillTree, ID_PICTURE_DI2 );
	m_pID_PICTURE_Fenge = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillTree, ID_PICTURE_Fenge );
	//m_pID_TEXT_SkillPoint = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillTree, ID_TEXT_SkillPoint );
	assert( m_pID_FRAME_SkillTree );
	//assert( m_pID_PICTURE_DI2 );
	assert( m_pID_PICTURE_Fenge );
	//assert( m_pID_TEXT_SkillPoint );

	m_pID_FRAME_SkillTree->SetMsgHoldup(false);

	m_skillTrees.clear();
	m_skillLevels.clear();
	m_skillNames.clear();
	m_skillUps.clear();
	m_skillArrows.clear();
	m_skillBackgrounds.clear();

	char buf[64] = {0};
	int index = 0;
	sprintf(buf, "ID_LISTIMG_Skill%d", index);
	ControlListImage* pListImg = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillTree, buf );
	while (pListImg)
	{
		pListImg->ShowPressEffect(true);

		theUiManager.OnIconDragOn( ID_FRAME_SkillTree, buf, s_CUI_ID_FRAME_SkillTreeID_LISTIMG_SkillOnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_SkillTree, buf, s_CUI_ID_FRAME_SkillTreeID_LISTIMG_SkillOnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_SkillTree, buf, s_CUI_ID_FRAME_SkillTreeID_LISTIMG_SkillOnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_SkillTree, buf, s_CUI_ID_FRAME_SkillTreeID_LISTIMG_SkillOnIconRButtonUp );

		m_skillTrees.push_back(pListImg);

		sprintf(buf, "ID_TEXT_SkillLvl%d", index);
		ControlText* pText = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillTree, buf );
		if (pText)
			m_skillLevels.push_back(pText);

		sprintf(buf, "ID_TEXT_SkillName%d", index);
		ControlText* pNameText = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillTree, buf );
		if (pNameText)
			m_skillNames.push_back(pNameText);

		sprintf(buf, "ID_BUTTON_Skill%d", index);
		ControlButton* pButton = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillTree, buf );
		if (pButton)
		{
			theUiManager.OnButtonClick( ID_FRAME_SkillTree, buf, s_CUI_ID_FRAME_SkillTreeID_BUTTON_SkillOnButtonClick );
			m_skillUps.push_back(pButton);
		}

// 		sprintf(buf, "ID_PICTURE_%d", index);
// 		ControlPicture* pArrow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillTree, buf );
// 		if (pArrow)
// 			m_skillArrows.push_back(pArrow);

		sprintf(buf, "ID_PICTURE_SkillWall%d", index);
		ControlPicture* pBg = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillTree, buf );
		if (pBg)
			m_skillBackgrounds.push_back(pBg);

		++index;
		sprintf(buf, "ID_LISTIMG_Skill%d", index);
		pListImg = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillTree, buf );
	}
	GetFrame()->SetFather(s_CUI_ID_FRAME_SKILL.GetFrame());

	SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SkillTree::_UnLoadUI()
{
	m_skillTrees.clear();
	m_skillLevels.clear();
	m_skillNames.clear();
	m_skillUps.clear();
	m_skillArrows.clear();
	m_skillBackgrounds.clear();
	std::string filename("Data\\UI\\SkillTree");
	filename += m_professionName;
	filename += ".MEUI";

	m_pID_FRAME_SkillTree = NULL;
	//m_pID_PICTURE_DI2 = NULL;
	m_pID_PICTURE_Fenge = NULL;
	//m_pID_TEXT_SkillPoint = NULL;
	return theUiManager.RemoveFrame( filename.c_str() );
}
// 是否可视
bool CUI_ID_FRAME_SkillTree::_IsVisable()
{
	if( !m_pID_FRAME_SkillTree )
		return false;
	return m_pID_FRAME_SkillTree->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SkillTree::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_SkillTree )
		return;
	m_pID_FRAME_SkillTree->SetVisable( bVisable );
}

bool CanLearnSkill(int nId, int nLevel)
{
	SCharBaseInfo *pCharBaseInfo = &thePlayerRole.m_charinfo.baseinfo;
	SCharOtherDataClient *pCharOtherInfo = &thePlayerRole.m_charinfo.otherdataclient;

	//
	CItemDetail::SItemSkill *pSkill = NULL;
	pSkill = GettheItemDetail().GetSkillByID( nId, nLevel );
	if ( !pSkill )
	{
		return false;
	}
	//
	if ( pSkill->stLearnLevelReq != 0 )
	{
		if( pCharBaseInfo->liveinfo.ustLevel < pSkill->stLearnLevelReq )
		{
			return false;
		}
	}
	if ( pSkill->stMoneyNeed != 0 )
	{
		if ( pCharBaseInfo->liveinfo.dwMoney < pSkill->stMoneyNeed )
		{
			return false;
		}
	}
	if (pSkill->nLearnNeedExp > 0)
	{
		if (pCharBaseInfo->liveinfo.dwSkillExp < pSkill->nLearnNeedExp)
			return false;
	}
	//////////////////////////////////////////////////////////////////////////
	//    学习时的 技能牵制条件
	for(int idx = 0; idx<3; idx++)
	{
		if ( pSkill->stSkillNeed[idx] != -1 && pSkill->stSkillLevelNeed[idx] != -1 )
		{
			CItemDetail::SItemSkill *pPreSkill = 
				GettheItemDetail().GetSkillByID( pSkill->stSkillNeed[idx], pSkill->stSkillLevelNeed[idx] );
			if ( pPreSkill )
			{
				int nSkillLevel = -1;
				for ( int n = 0; n<More_iMaxSkillKnown; n++ )
				{
					if ( pCharOtherInfo->skills.skill[n].ustSkillID == pSkill->stSkillNeed[idx] )
					{
						nSkillLevel = pCharOtherInfo->skills.skill[n].stSkillLevel;
						break;
					}
				}
				if ( nSkillLevel < pSkill->stSkillLevelNeed[idx] )
				{
					return false;
				}
			}
		}
	}
	return true;
}

void CUI_ID_FRAME_SkillTree::RefreshSkillTree()
{
	if( !m_pID_FRAME_SkillTree )
		return;
#define ONLY_SHOW_LEARN_SKILL 0

	for (int i = 0; i < m_skillTrees.size(); ++i)
		m_skillTrees[i]->SetVisable(false);

	for (int i = 0; i < m_skillLevels.size(); ++i)
		m_skillLevels[i]->SetVisable(false);

	for (int i = 0; i < m_skillNames.size(); ++i)
		m_skillNames[i]->SetVisable(false);

	for (int i = 0; i < m_skillUps.size(); ++i)
		m_skillUps[i]->SetVisable(false);

	for (int i = 0; i < m_skillArrows.size(); ++i)
		m_skillArrows[i]->SetVisable(false);

	for (int i = 0; i < m_skillBackgrounds.size(); ++i)
		m_skillBackgrounds[i]->SetVisable(false);

	CUISkillTreeConfig::SkillTreePage* pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
		GetPage(CUISkillMgr::eProfession);
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
#if ONLY_SHOW_LEARN_SKILL == 1 // 是否显示为学习的技能
		else
			continue;
#endif

		CItemDetail::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pIcon->iconid, level + 1);
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

		// get the max level
		//unsigned short ustMaxLevel = pItemSkill->ustSkillMaxLvl;
		//char szMaxLevel[20];
		//sprintf_s( szMaxLevel, 20, "\n%s %d", theXmlString.GetString( eSkillMaxLevel_Text ), ustMaxLevel );

		//bCanLearn = CanLearnSkill(pIcon->iconid, level + 1);

		//char szNeedInfo[512] = {0};
		//BOOL canLearn = GettheItemDetail().GetSkillNeedInfo( &thePlayerRole.m_charinfo.baseinfo,
		//	&thePlayerRole.m_charinfo.otherdataclient, 0/*没用*/,
		//	pItemSkill->ustItemID,
		//	level+1, szNeedInfo, sizeof(szNeedInfo) );

        //-----------------        
        //if ( pItemSkill->nLearnNeedExp != 0 )
        //{
        //    std::string strInfo;
        //    strInfo.clear();

        //    char szWord[256] = {0};
        //    if( thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp < pItemSkill->nLearnNeedExp )
        //        strInfo += "<#ffff0000=";

        //    _snprintf( szWord, sizeof(szWord)-1,theXmlString.GetString(eText_NeedSkillExp), 
        //        thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp,pItemSkill->nLearnNeedExp );

        //    strInfo += szWord;

        //    strcat_s(szNeedInfo, sizeof(szNeedInfo) - strlen(szNeedInfo) - 1,strInfo.c_str());
        //}
        //------------------------------------------
		ControlIconDrag::S_ListImg stItem;
		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
		stItem.SetData(pIcon->iconid, level, bEnable ? eIcon_Enable: eIcon_Disable, 0, eTipFlag_SkillNoNextLevel );
		stItem.SetFlags(CUISkillMgr::eProfession);
		//if( level != ustMaxLevel )
		//	stItem.SetOtherInfo( szMaxLevel );
		//stItem.SetOtherInfo( szNeedInfo );

		if (pIcon->index < s_CUI_ID_FRAME_SkillTree.m_skillTrees.size() && pIcon->iconid != 0)
		{
			m_skillTrees[pIcon->index]->SetItem(&stItem, 0);
			m_skillTrees[pIcon->index]->SetVisable(true);

			if (bEnable && pIcon->index < m_skillLevels.size())
			{
				m_skillLevels[pIcon->index]->SetText(level);
				m_skillLevels[pIcon->index]->SetVisable(true);
			}
			if ( pIcon->index < m_skillNames.size())
			{
				m_skillNames[pIcon->index]->SetText(pItemSkill->GetSkillName());
				m_skillNames[pIcon->index]->SetVisable(true);
			}
			if (bEnable && /*pIcon->index < m_skillArrows.size() &&*/ pIcon->index < m_skillBackgrounds.size() )
			{
				/*m_skillArrows[pIcon->index]->SetVisable(true);*/
				m_skillBackgrounds[pIcon->index]->SetVisable(true);
			}
			if (bEnable && bCanLearn && pIcon->index < m_skillUps.size())
			{
				m_skillUps[i]->SetVisable(true);
			}
		}
	}

	Refresh();
}

void CUI_ID_FRAME_SkillTree::RefreshSkillPoint()
{
// 	if( !m_pID_FRAME_SkillTree )
// 		return;
// 	static std::string str = m_pID_TEXT_SkillPoint->GetText();
// 	std::stringstream sstr;
// 	sstr << str;
// 	sstr << thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp;
// 	m_pID_TEXT_SkillPoint->SetText(sstr.str());
}

bool CUI_ID_FRAME_SkillTree::IsSkillList(const ControlObject* pObject )
{
	if( !m_pID_FRAME_SkillTree || !pObject )
		return false;
	for (int i = 0; i < m_skillTrees.size(); ++i)
	{
		if (m_skillTrees[i] == pObject)
			return true;
	}
	return false;
}

void CUI_ID_FRAME_SkillTree::Refresh()
{
	ControlIconDrag::S_ListImg* pItem = NULL;
	ControlIconDrag::S_ListImg stItem;
	for (int i = 0; i < m_skillTrees.size(); ++i)
	{
		pItem = m_skillTrees[i]->GetItemByIndex(0);
		if (!pItem)
		{
			continue;
		}
		stItem = *pItem;
		short stSkillId = pItem->m_pkIconInfo->GetItemId();
		int nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById(stSkillId);
		if (nSkillIndex != -1)
		{
			SkillBag::SColdTime *pTime = thePlayerRole.m_SkillBag.GetColdTimeByIndex(nSkillIndex);
			if (pTime)
			{
				stItem.SetTime(pTime->dwColdStartTime, pTime->dwColdTime);
				m_skillTrees[i]->SetItem(&stItem, 0);
			}
		}
	}
}