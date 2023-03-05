/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\SkillEquip.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SkillEquip.h"
#include "Skill.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "Common.h"

CUI_ID_FRAME_SkillEquip s_CUI_ID_FRAME_SkillEquip;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SkillEquip, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SkillEquip, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SkillEquip, ID_LISTIMG_TongyongOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquip, ID_LISTIMG_TongyongOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquip, ID_LISTIMG_TongyongOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillEquip, ID_LISTIMG_TongyongOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquip, ID_BUTTON_BackOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillEquip, ID_BUTTON_NextOnButtonClick )
CUI_ID_FRAME_SkillEquip::CUI_ID_FRAME_SkillEquip()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_SkillEquip::ResetMembers()
{
	m_pID_FRAME_SkillEquip = NULL;
	m_pID_LISTIMG_Tongyong = NULL;
	m_pID_PICTURE_skillback0 = NULL;
	m_pID_TEXT_SkillName1 = NULL;
	m_pID_TEXT_SkillName2 = NULL;
	m_pID_TEXT_SkillName3 = NULL;
	m_pID_TEXT_SkillName4 = NULL;
	m_pID_TEXT_SkillName5 = NULL;
	m_pID_TEXT_SkillName6 = NULL;
	m_pID_TEXT_SkillName7 = NULL;
	m_pID_TEXT_SkillName8 = NULL;
	m_pID_TEXT_SkillName9 = NULL;
	m_pID_TEXT_SkillName10 = NULL;
	m_pID_TEXT_SkillName11 = NULL;
	m_pID_TEXT_SkillName12 = NULL;
// 	m_pID_TEXT_SkillLvl1 = NULL;
// 	m_pID_TEXT_SkillLvl2 = NULL;
// 	m_pID_TEXT_SkillLvl3 = NULL;
// 	m_pID_TEXT_SkillLvl4 = NULL;
// 	m_pID_TEXT_SkillLvl5 = NULL;
// 	m_pID_TEXT_SkillLvl6 = NULL;
// 	m_pID_TEXT_SkillLvl7 = NULL;
// 	m_pID_TEXT_SkillLvl8 = NULL;
// 	m_pID_TEXT_SkillLvl9 = NULL;
// 	m_pID_TEXT_SkillLvl10 = NULL;
// 	m_pID_TEXT_SkillLvl11 = NULL;
// 	m_pID_TEXT_SkillLvl12 = NULL;
	m_pID_TEXT_SkillDesc1 = NULL;
	m_pID_TEXT_SkillDesc2 = NULL;
	m_pID_TEXT_SkillDesc3 = NULL;
	m_pID_TEXT_SkillDesc4 = NULL;
	m_pID_TEXT_SkillDesc5 = NULL;
	m_pID_TEXT_SkillDesc6 = NULL;
	m_pID_TEXT_SkillDesc7 = NULL;
	m_pID_TEXT_SkillDesc8 = NULL;
	m_pID_TEXT_SkillDesc9 = NULL;
	m_pID_TEXT_SkillDesc10 = NULL;
	m_pID_TEXT_SkillDesc11 = NULL;
	m_pID_TEXT_SkillDesc12 = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_BUTTON_Next = NULL;

}
// Frame
bool CUI_ID_FRAME_SkillEquip::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SkillEquip::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SkillEquip::ID_LISTIMG_TongyongOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															  ControlIconDrag::S_ListImg* pItemDrag,
															  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SkillEquip )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquip::ID_LISTIMG_TongyongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquip )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquip::ID_LISTIMG_TongyongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquip )
		return false;
	return false;
}
bool CUI_ID_FRAME_SkillEquip::ID_LISTIMG_TongyongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillEquip )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_SkillEquip::ID_BUTTON_BackOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SkillEquip )
		return false;
	--m_nCurrPageIndex;
	if (m_nCurrPageIndex < 0)
		m_nCurrPageIndex = 0;
	Refresh();
	return true;
}
// Button
bool CUI_ID_FRAME_SkillEquip::ID_BUTTON_NextOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SkillEquip )
		return false;
	++m_nCurrPageIndex;
	if (m_nCurrPageIndex > m_nPageCount - 1)
		m_nCurrPageIndex = m_nPageCount - 1;
	Refresh();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SkillEquip::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SkillEquip.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SkillEquip.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SkillEquip::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SkillEquip, s_CUI_ID_FRAME_SkillEquipOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SkillEquip, s_CUI_ID_FRAME_SkillEquipOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_SkillEquip, ID_LISTIMG_Tongyong, s_CUI_ID_FRAME_SkillEquipID_LISTIMG_TongyongOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SkillEquip, ID_LISTIMG_Tongyong, s_CUI_ID_FRAME_SkillEquipID_LISTIMG_TongyongOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SkillEquip, ID_LISTIMG_Tongyong, s_CUI_ID_FRAME_SkillEquipID_LISTIMG_TongyongOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SkillEquip, ID_LISTIMG_Tongyong, s_CUI_ID_FRAME_SkillEquipID_LISTIMG_TongyongOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SkillEquip, ID_BUTTON_Back, s_CUI_ID_FRAME_SkillEquipID_BUTTON_BackOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SkillEquip, ID_BUTTON_Next, s_CUI_ID_FRAME_SkillEquipID_BUTTON_NextOnButtonClick );

	m_pID_FRAME_SkillEquip = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SkillEquip );
	m_pID_LISTIMG_Tongyong = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_LISTIMG_Tongyong );
	m_pID_PICTURE_skillback0 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_PICTURE_skillback0 );
	m_pID_TEXT_SkillName1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName1 );
	m_pID_TEXT_SkillName2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName2 );
	m_pID_TEXT_SkillName3 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName3 );
	m_pID_TEXT_SkillName4 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName4 );
	m_pID_TEXT_SkillName5 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName5 );
	m_pID_TEXT_SkillName6 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName6 );
	m_pID_TEXT_SkillName7 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName7 );
	m_pID_TEXT_SkillName8 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName8 );
	m_pID_TEXT_SkillName9 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName9 );
	m_pID_TEXT_SkillName10 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName10 );
	m_pID_TEXT_SkillName11 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName11 );
	m_pID_TEXT_SkillName12 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillName12 );
// 	m_pID_TEXT_SkillLvl1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl1 );
// 	m_pID_TEXT_SkillLvl2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl2 );
// 	m_pID_TEXT_SkillLvl3 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl3 );
// 	m_pID_TEXT_SkillLvl4 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl4 );
// 	m_pID_TEXT_SkillLvl5 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl5 );
// 	m_pID_TEXT_SkillLvl6 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl6 );
// 	m_pID_TEXT_SkillLvl7 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl7 );
// 	m_pID_TEXT_SkillLvl8 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl8 );
// 	m_pID_TEXT_SkillLvl9 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl9 );
// 	m_pID_TEXT_SkillLvl10 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl10 );
// 	m_pID_TEXT_SkillLvl11 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl11 );
// 	m_pID_TEXT_SkillLvl12 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillLvl12 );
	m_pID_TEXT_SkillDesc1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc1 );
	m_pID_TEXT_SkillDesc2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc2 );
	m_pID_TEXT_SkillDesc3 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc3 );
	m_pID_TEXT_SkillDesc4 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc4 );
	m_pID_TEXT_SkillDesc5 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc5 );
	m_pID_TEXT_SkillDesc6 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc6 );
	m_pID_TEXT_SkillDesc7 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc7 );
	m_pID_TEXT_SkillDesc8 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc8 );
	m_pID_TEXT_SkillDesc9 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc9 );
	m_pID_TEXT_SkillDesc10 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc10 );
	m_pID_TEXT_SkillDesc11 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc11 );
	m_pID_TEXT_SkillDesc12 = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_TEXT_SkillDesc12 );
	m_pID_BUTTON_Back = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_BUTTON_Back );
	m_pID_BUTTON_Next = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillEquip, ID_BUTTON_Next );
	assert( m_pID_FRAME_SkillEquip );
	assert( m_pID_LISTIMG_Tongyong );
	assert( m_pID_PICTURE_skillback0 );
	assert( m_pID_TEXT_SkillName1 );
	assert( m_pID_TEXT_SkillName2 );
	assert( m_pID_TEXT_SkillName3 );
	assert( m_pID_TEXT_SkillName4 );
	assert( m_pID_TEXT_SkillName5 );
	assert( m_pID_TEXT_SkillName6 );
	assert( m_pID_TEXT_SkillName7 );
	assert( m_pID_TEXT_SkillName8 );
	assert( m_pID_TEXT_SkillName9 );
	assert( m_pID_TEXT_SkillName10 );
	assert( m_pID_TEXT_SkillName11 );
	assert( m_pID_TEXT_SkillName12 );
// 	assert( m_pID_TEXT_SkillLvl1 );
// 	assert( m_pID_TEXT_SkillLvl2 );
// 	assert( m_pID_TEXT_SkillLvl3 );
// 	assert( m_pID_TEXT_SkillLvl4 );
// 	assert( m_pID_TEXT_SkillLvl5 );
// 	assert( m_pID_TEXT_SkillLvl6 );
// 	assert( m_pID_TEXT_SkillLvl7 );
// 	assert( m_pID_TEXT_SkillLvl8 );
// 	assert( m_pID_TEXT_SkillLvl9 );
// 	assert( m_pID_TEXT_SkillLvl10 );
// 	assert( m_pID_TEXT_SkillLvl11 );
// 	assert( m_pID_TEXT_SkillLvl12 );
	assert( m_pID_TEXT_SkillDesc1 );
	assert( m_pID_TEXT_SkillDesc2 );
	assert( m_pID_TEXT_SkillDesc3 );
	assert( m_pID_TEXT_SkillDesc4 );
	assert( m_pID_TEXT_SkillDesc5 );
	assert( m_pID_TEXT_SkillDesc6 );
	assert( m_pID_TEXT_SkillDesc7 );
	assert( m_pID_TEXT_SkillDesc8 );
	assert( m_pID_TEXT_SkillDesc9 );
	assert( m_pID_TEXT_SkillDesc10 );
	assert( m_pID_TEXT_SkillDesc11 );
	assert( m_pID_TEXT_SkillDesc12 );

	m_pID_FRAME_SkillEquip->SetMsgHoldup(false);

	char buf[64];
	int index = 1;
	sprintf(buf, "ID_TEXT_SkillName%d", index);
	ControlText* pName = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, buf );
	while (pName)
	{
		m_names.push_back(pName);

		sprintf(buf, "ID_TEXT_SkillLvl%d", index);
		ControlText* pLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, buf );
		//m_levels.push_back(pLvl);

		sprintf(buf, "ID_TEXT_SkillDesc%d", index);
		ControlText* pDesc = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, buf );
		m_descs.push_back(pDesc);

		++index;
		sprintf(buf, "ID_TEXT_SkillName%d", index);
		pName = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillEquip, buf );
	}
	GetFrame()->SetFather(s_CUI_ID_FRAME_SKILL.GetFrame());

	m_nCurrPageIndex = 0;

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SkillEquip::_UnLoadUI()
{
	m_names.clear();
	//m_levels.clear();
	m_descs.clear();
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\SkillEquip.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SkillEquip::_IsVisable()
{
	if( !m_pID_FRAME_SkillEquip )
		return false;
	return m_pID_FRAME_SkillEquip->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SkillEquip::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_SkillEquip )
		return;
	m_pID_FRAME_SkillEquip->SetVisable( bVisable );
	m_nCurrPageIndex = 0;
}

void CUI_ID_FRAME_SkillEquip::Refresh()
{
	if( !m_pID_FRAME_SkillEquip )
		return;
	m_pID_LISTIMG_Tongyong->Clear();

	for (int i = 0; i < m_names.size(); ++i)
	{
		m_names[i]->SetText("？？？");
	}

// 	for (int i = 0; i < m_levels.size(); ++i)
// 		m_levels[i]->SetVisable(false);

	CUISkillTreeConfig::SkillTreePage* pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
		GetPage(CUISkillMgr::eEquipSkill);
	if (!pSkillTree)
		return;

	SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

	int nEquipSkillCount = pSkillIcon->GetLength();
	int nShowCount = m_names.size();
	m_nPageCount = nEquipSkillCount / nShowCount + 1;
	int nIndex = nShowCount * m_nCurrPageIndex; // 当前页第一个道具技能索引

	m_pID_BUTTON_Back->SetEnable(m_nCurrPageIndex > 0);
	m_pID_BUTTON_Next->SetEnable(m_nCurrPageIndex < m_nPageCount - 1);

	int nNameIndex = 0;
	if (m_nCurrPageIndex > 0)
		nNameIndex = 12;
	for (int i = 0; i < m_descs.size(); ++i, ++nNameIndex)
		m_descs[i]->SetText(theXmlString.GetString( 10301 + nNameIndex ));

	int count = 0;
	for (size_t i = nIndex; i< pSkillIcon->GetLength(); ++i)
	{
		const SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];

		int level = 0;
		bool bEnable = false;

		for (int l = ItemDefine::MaxLevel_Skill - 1; l > 0; --l)
		{
			bEnable = thePlayerRole.suitManager.IsSuitHaveSkill(pIcon->iconid, l);
			if (bEnable)
			{
				level = l;
				break;
			}
		}

		SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(pIcon->iconid);
		if (pSkill)
		{
			if (bEnable)
				pSkill->stSkillLevel = level;
			else
				level = pSkill->stSkillLevel;
		}
		else
			continue;

		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pIcon->iconid, level + 1);
		if (!pItemSkill)
		{
			pItemSkill = GettheItemDetail().GetSkillByID(pIcon->iconid, level);
			if (!pItemSkill)
				continue;
		}

		// get the max level
		unsigned short ustMaxLevel = pItemSkill->ustSkillMaxLvl;
		char szMaxLevel[20];
		MeSprintf_s( szMaxLevel, sizeof(szMaxLevel)/sizeof(char) - 1, "\n%s %d", theXmlString.GetString( eSkillMaxLevel_Text ), ustMaxLevel );

		char szNeedInfo[512] = {0};
		GettheItemDetail().GetSkillNeedInfo( &thePlayerRole.m_charinfo.baseinfo,
			&thePlayerRole.m_charinfo.otherdataclient, 0/*没用*/,
			pItemSkill->ustItemID,
			level+1, szNeedInfo, sizeof(szNeedInfo) );

        //-----------------        
        if ( pItemSkill->nLearnNeedExp != 0 )
        {
            std::string strInfo;
            strInfo.clear();

            char szWord[256] = {0};
            if( thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp < pItemSkill->nLearnNeedExp )
                strInfo += "<#ffff0000=";

            MeSprintf_s( szWord, sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_NeedSkillExp), 
                thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp,pItemSkill->nLearnNeedExp );

            strInfo += szWord;

            strcat_s(szNeedInfo, sizeof(szNeedInfo) - strlen(szNeedInfo) - 1,strInfo.c_str());
        }
        //------------------------------------------
		ControlIconDrag::S_ListImg stItem;
		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
		stItem.SetData(pIcon->iconid, level, bEnable ? eIcon_Enable: eIcon_Disable, 0, eTipFlag_SkillWithNextLevel );
		stItem.SetFlags(CUISkillMgr::eProfession);
		if( level != ustMaxLevel )
			stItem.SetOtherInfo( szMaxLevel );
		stItem.SetOtherInfo( szNeedInfo );

		m_pID_LISTIMG_Tongyong->SetItem(&stItem);

		if (count < m_names.size())
		{
			m_names[count]->SetVisable(true);
			m_names[count]->SetText(pItemSkill->GetSkillName());
		}

// 		if (count < m_levels.size() && level > 0)
// 		{
// 			m_levels[count]->SetVisable(true);
// 			m_levels[count]->SetText(level);
// 		}

		if (count < m_descs.size())
		{
			m_descs[count]->SetVisable(true);
		}

		++count;
	}
}

bool CUI_ID_FRAME_SkillEquip::IsLISTIMG_Tongyong( const ControlObject* pObject )
{
	if( !m_pID_FRAME_SkillEquip || !pObject )
		return false;
	return (m_pID_LISTIMG_Tongyong == pObject);
}