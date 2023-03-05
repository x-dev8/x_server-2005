/********************************************************************
Created by UIEditor.exe
FileName: F:\project\Turbo\Bin\Client\Data\Ui\SkillSpirit.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SkillSpirit.h"
#include "Skill.h"
#include "PlayerRole.h"
#include "Helper/XinFaHelper.h"
#include "ItemDetail.h"
#include "ScreenInfoManager.h"
#include "IconManagerClient.h"

static const char* AttrTypeToDesc(uint8 uTypeID);
const int UI_XINFACOUNT = 6;

CUI_ID_FRAME_Skill_Spirit s_CUI_ID_FRAME_Skill_Spirit;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Skill_Spirit, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Skill_Spirit, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillBookOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillBookOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillBookOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillBookOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillOnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Skill_Spirit, ID_LIST__BookNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Skill_Spirit, ID_LIST_AdditionalOnListSelectChange )

CUI_ID_FRAME_Skill_Spirit::CUI_ID_FRAME_Skill_Spirit()
{
	// Member
	m_pID_FRAME_Skill_Spirit = NULL;
	m_pID_LISTIMG_SkillBook = NULL;
	m_pID_LISTIMG_Skill = NULL;
	m_pID_LIST__BookName = NULL;
	m_pID_LIST__BookLv = NULL;
	m_pID_LIST__Book = NULL;
	m_pID_TEXT_SkillName = NULL;
	m_pID_TEXT_SkillIntroduce = NULL;
	m_pID_TEXT_NowExp = NULL;
	m_pID_LIST_Additional = NULL;
}
// Frame
bool CUI_ID_FRAME_Skill_Spirit::OnFrameRun()
{
	if (_IsVisable() && m_pID_TEXT_NowExp)
	{
		char exp[256]={0};
		sprintf_s(exp,sizeof(exp)/sizeof(char),"%I64d",thePlayerRole.GetExpNotUsed());
		m_pID_TEXT_NowExp->SetText(exp);
	}
	return true;
}
bool CUI_ID_FRAME_Skill_Spirit::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Skill_Spirit::ID_LISTIMG_SkillBookOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																 ControlIconDrag::S_ListImg* pItemDrag,
																 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Skill_Spirit::ID_LISTIMG_SkillBookOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Skill_Spirit::ID_LISTIMG_SkillBookOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(NULL == m_pID_FRAME_Skill_Spirit)
		return false;
	
	int index = m_pID_LISTIMG_SkillBook->GetItemIndex(pItem);
	m_pID_LIST_Additional->SetCurSelIndex(index);
	return m_xinFaUIHelper.ClickXinFaIcon(pItem);
}
bool CUI_ID_FRAME_Skill_Spirit::ID_LISTIMG_SkillBookOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Skill_Spirit::ID_LISTIMG_SkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															 ControlIconDrag::S_ListImg* pItemDrag,
															 ControlIconDrag::S_ListImg* pItemSrc )
{
	ItemDefine::SItemSkill* pSkill = NULL; 
	if (pItemDrag != NULL)
	{
		pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
		if( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive ||pSkill->stGeneralType == ItemDefine::generaltype_passive )
		{//主动技能，给提示信息
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_UseFailed, theXmlString.GetString(eText_SkillCanNotDrag));
		}
	}
	return false;
}
bool CUI_ID_FRAME_Skill_Spirit::ID_LISTIMG_SkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Skill_Spirit::ID_LISTIMG_SkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(NULL == m_pID_FRAME_Skill_Spirit)
		return false;

	return m_xinFaUIHelper.ClickSkillIcon(pItem);
}
bool CUI_ID_FRAME_Skill_Spirit::ID_LISTIMG_SkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
void CUI_ID_FRAME_Skill_Spirit::ID_LIST__BookNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	int index = m_pID_LIST__BookName->GetCurSelIndex();
	ControlIconDrag::S_ListImg* pSelItem = m_pID_LISTIMG_SkillBook->GetItemByIndex(index);
	m_xinFaUIHelper.ClickXinFaIcon(pSelItem);
}

void CUI_ID_FRAME_Skill_Spirit::ID_LIST_AdditionalOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	int index = m_pID_LIST_Additional->GetCurSelIndex();
	ControlIconDrag::S_ListImg* pSelItem = m_pID_LISTIMG_SkillBook->GetItemByIndex(index);
	m_xinFaUIHelper.ClickXinFaIcon(pSelItem);
}

// 装载UI
bool CUI_ID_FRAME_Skill_Spirit::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SkillSpirit.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SkillSpirit.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Skill_Spirit::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Skill_Spirit, s_CUI_ID_FRAME_Skill_SpiritOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Skill_Spirit, s_CUI_ID_FRAME_Skill_SpiritOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillBook, s_CUI_ID_FRAME_Skill_SpiritID_LISTIMG_SkillBookOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillBook, s_CUI_ID_FRAME_Skill_SpiritID_LISTIMG_SkillBookOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillBook, s_CUI_ID_FRAME_Skill_SpiritID_LISTIMG_SkillBookOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillBook, s_CUI_ID_FRAME_Skill_SpiritID_LISTIMG_SkillBookOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Skill_Spirit, ID_LISTIMG_Skill, s_CUI_ID_FRAME_Skill_SpiritID_LISTIMG_SkillOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Skill_Spirit, ID_LISTIMG_Skill, s_CUI_ID_FRAME_Skill_SpiritID_LISTIMG_SkillOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Skill_Spirit, ID_LISTIMG_Skill, s_CUI_ID_FRAME_Skill_SpiritID_LISTIMG_SkillOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Skill_Spirit, ID_LISTIMG_Skill, s_CUI_ID_FRAME_Skill_SpiritID_LISTIMG_SkillOnIconRButtonUp );
	theUiManager.OnListSelectChange( ID_FRAME_Skill_Spirit, ID_LIST__BookName, s_CUI_ID_FRAME_Skill_SpiritID_LIST__BookNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Skill_Spirit, ID_LIST_Additional, s_CUI_ID_FRAME_Skill_SpiritID_LIST_AdditionalOnListSelectChange );

	m_pID_FRAME_Skill_Spirit = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Skill_Spirit );
	m_pID_LISTIMG_SkillBook = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Skill_Spirit, ID_LISTIMG_SkillBook );
	m_pID_LISTIMG_Skill = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Skill_Spirit, ID_LISTIMG_Skill );
	m_pID_TEXT_SkillName = (ControlText*)theUiManager.FindControl( ID_FRAME_Skill_Spirit, ID_TEXT_SkillName );
	m_pID_TEXT_SkillIntroduce = (ControlText*)theUiManager.FindControl( ID_FRAME_Skill_Spirit, ID_TEXT_SkillIntroduce );
	m_pID_LIST__BookName = (ControlList*)theUiManager.FindControl( ID_FRAME_Skill_Spirit, ID_LIST__BookName );
	m_pID_LIST__BookLv = (ControlList*)theUiManager.FindControl( ID_FRAME_Skill_Spirit, ID_LIST__BookLv );
	m_pID_LIST__Book = (ControlList*)theUiManager.FindControl( ID_FRAME_Skill_Spirit, ID_LIST__Book );

	m_pID_TEXT_NowExp = (ControlText*)theUiManager.FindControl( ID_FRAME_Skill_Spirit, ID_TEXT_NowExp );
	m_pID_LIST_Additional = (ControlList*)theUiManager.FindControl( ID_FRAME_Skill_Spirit, ID_LIST_Additional );

	char buf[64];
	for(int i=1; i<=UI_XINFACOUNT; ++i)
	{
		sprintf(buf, "ID_TEXT_SkillCondition%d%d", i, i );
		m_pID_TEXT_SubSkillCondition[i - 1] = (ControlText*)theUiManager.FindControl(ID_FRAME_Skill_Spirit, buf);
		assert(m_pID_TEXT_SubSkillCondition[i - 1] != NULL);

		sprintf(buf, "ID_TEXT_SkiillLevel%d%d", i , i );
		m_pID_TEXT_SubSkillLevel[i - 1] = (ControlText*)theUiManager.FindControl(ID_FRAME_Skill_Spirit, buf);
		assert(m_pID_TEXT_SubSkillLevel[i - 1] != NULL);

		sprintf(buf, "ID_TEXT_SkillName%d%d", i , i );
		m_pID_TEXT_SubSkillName[i - 1] = (ControlText*)theUiManager.FindControl(ID_FRAME_Skill_Spirit, buf);
		assert(m_pID_TEXT_SubSkillName[i - 1] != NULL);
	}
	

	assert( m_pID_FRAME_Skill_Spirit );
	assert( m_pID_LISTIMG_SkillBook );
	assert( m_pID_LISTIMG_Skill );
	assert( m_pID_LIST__BookName );
	assert( m_pID_LIST__BookLv );
	assert( m_pID_LIST__Book );
	assert( m_pID_TEXT_SkillName );
	assert( m_pID_TEXT_SkillIntroduce );
	assert( m_pID_TEXT_NowExp );
	assert( m_pID_LIST_Additional );

	GetFrame()->SetFather(s_CUI_ID_FRAME_SKILL.GetFrame());

	m_xinFaUIHelper.Init(m_pID_LISTIMG_SkillBook, m_pID_LISTIMG_Skill,  
					m_pID_TEXT_SkillName, m_pID_TEXT_SkillIntroduce, 
					m_pID_LIST__BookLv, m_pID_LIST__BookName, 
					m_pID_TEXT_SubSkillName, m_pID_TEXT_SubSkillCondition, m_pID_TEXT_SubSkillLevel, 
					UI_XINFACOUNT,m_pID_LIST_Additional);

	m_pID_LISTIMG_SkillBook ->SetEnableDragIn(false);
	m_pID_LISTIMG_SkillBook ->SetEnableDragOut(false);
	m_pID_LISTIMG_Skill->SetEnableDragIn(false);
	m_pID_LISTIMG_Skill->SetShiftLBClickFun( IconOnShiftLBClick );

	m_pID_LIST__Book->SetMsgHoldup(false);
	m_pID_LIST__BookLv->SetMsgHoldup(false);
	m_pID_LIST_Additional->SetMsgHoldup(true);
	m_pID_LIST__BookName->SetMsgHoldup(false);
	m_pID_LIST__BookName->HaveSelBar(false);
	m_pID_LIST__BookLv->HaveSelBar(false);
	m_pID_LIST_Additional->HaveSelBar(true);
	m_pID_LIST__Book->HaveSelBar(false);
	m_pID_LIST__BookName->SetEnable(false);
	m_pID_LIST_Additional->SetEnable(true);
	m_pID_LIST__BookLv->SetEnable(false);
	SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Skill_Spirit::_UnLoadUI()
{
	m_pID_FRAME_Skill_Spirit = NULL;
	m_xinFaUIHelper.Reset();

	return theUiManager.RemoveFrame( "Data\\UI\\SkillSpirit.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Skill_Spirit::_IsVisable()
{
	return m_pID_FRAME_Skill_Spirit->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Skill_Spirit::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_Skill_Spirit->SetVisable( bVisable );

	if (m_pID_TEXT_NowExp && bVisable)
	{
		char exp[256]={0};
		sprintf_s(exp,sizeof(exp)/sizeof(char),"%I64d",thePlayerRole.GetExpNotUsed());
		m_pID_TEXT_NowExp->SetText(exp);
	}
	if(!bVisable)
	{
		m_xinFaUIHelper.ClearSelectedInfo();
	}
}

void CUI_ID_FRAME_Skill_Spirit::Refresh()
{
	m_xinFaUIHelper.RefreshXinFa();
}

void CUI_ID_FRAME_Skill_Spirit::IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	assert(pItem != NULL);

	SCharSkill *pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pItem->m_pkIconInfo->Id());
	//assert(IsValidXinFaSkill(pCharSkill));
	if(NULL == pCharSkill || !IsValidXinFaSkill(pCharSkill))
	{
		return;
	}

	ItemDefine::SItemSkill* pItemSKill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
	if ( pItemSKill == NULL )
	{
		return;
	}
	
	CommonChatFrame::GetActiveChatFrame()->addHyberTextEx( pItemSKill->GetItemName(), MsgChat::HYBERTYPE_SKILL,  pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
}

bool CUI_ID_FRAME_Skill_Spirit::IsSkillList(const ControlObject* pObject)
{
	return pObject == m_pID_LISTIMG_SkillBook ||
			pObject == m_pID_LISTIMG_Skill;
			
}

CXinFaUIHelper::CXinFaUIHelper():
m_pSelectedXinFa(NULL),
m_pImageBook(NULL),
m_pImageSkill(NULL),
m_pTextName(NULL),
m_pTextIntroduction(NULL),
m_pListXinfaNames(NULL),
m_pListXinfaLevels(NULL),
m_booksCount(0),
m_pTextNextIntroduction(NULL)
{
	ClearSelectedInfo();
}

CXinFaUIHelper::~CXinFaUIHelper()
{

}

void CXinFaUIHelper::Init(ControlListImage *pImageBook_, ControlListImage *pImageSkill_, 
		  ControlText *pTextName_, ControlText *pTextIntroduction_, ControlList *pTextLevels_, 
		  ControlList *pXinfaNames_, ControlText **pSkillName, ControlText **pSkillCondition, 
		  ControlText **pNeedXinFaLevel, uint8 booksCount_,ControlList *pAdditional,ControlText* pTextNextIntroduction_)
{
	m_pSelectedXinFa = NULL;
	m_pImageBook = pImageBook_;
	m_pImageSkill = pImageSkill_;

	m_pTextNeedXinfaLevels = pNeedXinFaLevel;
	m_pTextSkillCondition = pSkillCondition;
	m_pTextSkillNames = pSkillName;
	
	m_pTextName = pTextName_;
	m_pTextIntroduction = pTextIntroduction_;
	m_pListXinfaLevels = pTextLevels_;
	m_pListXinfaNames = pXinfaNames_;
	m_booksCount = booksCount_;
	m_pAdditional = pAdditional;

	m_pTextNextIntroduction = pTextNextIntroduction_;
}

void CXinFaUIHelper::Reset(void)
{
	m_pSelectedXinFa = NULL;
	m_pImageBook = NULL;
	m_pImageSkill = NULL;
	
	m_pTextNeedXinfaLevels = NULL;
	m_pTextSkillCondition = NULL;
	m_pTextSkillNames = NULL;
	m_pTextName = NULL;
	m_pTextIntroduction = NULL;
	m_pListXinfaLevels = NULL;
	m_pListXinfaNames = NULL;
	m_booksCount = 0;

	m_pTextNextIntroduction = NULL;
}

bool CXinFaUIHelper::SetXinFaInfo(/*const*/ XinFaConfig::STalentXinFa *pXinFa_, bool isNext /*= false*/)
{
	assert(pXinFa_ != NULL && IsValidXinFa(pXinFa_));

	/*char buf[32];
	sprintf_s(buf, 32, theXmlString.GetString(eText_XinFaLevel), pXinFa_->nLevel);
	std::string name = pXinFa_->strName + buf;
	SetText_SkillName(name.c_str());
	sprintf_s(buf, 32, theXmlString.GetString(eText_XinFaLearnLevel), pXinFa_->nNeedLevel);
	name = pXinFa_->strDesc + buf;*/

	SCharXinFa *pCharXinFa = thePlayerRole.m_xinFaBag.GetXinFaByID(pXinFa_->nId);
	if (!pCharXinFa && isNext)
		pXinFa_ = XinFaConfig::Instance().GetXinFaByID(pXinFa_->nId, pXinFa_->nLevel-1);

	std::string name;
	char buf[32];
	if (!isNext)
	{
		if (pCharXinFa)
			sprintf_s(buf, 32, theXmlString.GetString(eText_XinFaCurrLevel), pXinFa_->nLevel);
		else
			sprintf_s(buf, 32, theXmlString.GetString(eText_XinFaCurrLevel), 0);
	}
	else
	{
		if (pCharXinFa)
			sprintf_s(buf, 32, theXmlString.GetString(eText_XInFaNextLevel), pXinFa_->nLevel);
		else
			sprintf_s(buf, 32, theXmlString.GetString(eText_XInFaNextLevel), 1);
	}
	name += buf;
	
	
	if (/*pCharXinFa &&*/ IsValidXinFa(pXinFa_))
	{
		if (!pCharXinFa && !isNext)
		{

		}
		else
		{
			//增加心法说明
			//name += theXmlString.GetString(eText_XinFaCurrEffect);	
			for (int i=0;i<XinFaConfig::EXCD_EffectCharAttrMax;i++)
			{
				if (pXinFa_->charAttrValue[i].fValue>0)
				{
					int value = pXinFa_->charAttrValue[i].fValue;
					sprintf_s(buf,32,"\n%s+%d",S_IconInfoHero::GetRandStringByType(pXinFa_->charAttrType[i]).c_str(),value);
					name += buf;
				}
			}

			//增加心法对应的技能效果说明
			for (uint8 j=0;j<XinFaConfig::EXCD_SkillMaxCount;j++)
			{
				XinFaConfig::SXinFaSkill* pXinfa_Skill = pXinFa_->GetXinFaSkill(j);
				if (pXinfa_Skill && pXinfa_Skill->nLevel>0)
				{
					ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(pXinfa_Skill->nId,pXinfa_Skill->nLevel);
					if (pSkill)
					{
						bool bHasAttrValue = false;
						std::string bufTemp = "\n";
						for(uint8 k=0;k<XinFaConfig::EXCD_EffectSkillAttr;k++)
						{
							int nAttrValue = pXinfa_Skill->attrValue[k];
							if (nAttrValue==0)
							{
								continue;
							}
							if (!bHasAttrValue)
							{
								//bufTemp += pSkill->GetSkillName();
							}
							bHasAttrValue = true;
							sprintf_s(buf,32,"%s+%d",AttrTypeToDesc(pXinfa_Skill->attrType[k]),nAttrValue);
							//sprintf_s(buf,32,"%s+%d",S_IconInfoHero::GetRandStringByType(pXinfa_Skill->attrType[k]).c_str(),nAttrValue);
							bufTemp += buf;
						}
						if (bHasAttrValue)
							name += bufTemp;
						//sprintf_s(name,256,"%s %s",pSkill->GetSkillName(),bufTemp.c_str());
					}
				}
			}
		}
		
	}
	if (!isNext)
		SetText_SkillIntroduction(name.c_str());
	else
		SetText_NextSkillIntroduction(name.c_str());

	return true;
}
/*
bool CXinFaUIHelper::SetSkillInfo(const XinFaConfig::SXinFaSkill *pItemSkill_)
{
	assert(pItemSkill_ != NULL && IsValidXinFaSkill(pItemSkill_));

	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pItemSkill_->nId, pItemSkill_->nLevel);
	//assert(pSkill != NULL);
	if(NULL == pSkill)
	{
		//提示信息
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, 
									theXmlString.GetString(eText_Configuration_Skill_NotOk));

		return false;
	}

	SetText_SkillName(pSkill->GetSkillName());
	SetText_SkillIntroduction(pSkill->GetSkillDescription());

	return SetSkillIcon(pItemSkill_, m_pImageSelected, 0, false);
}
*/
void CXinFaUIHelper::SetText_SkillName(const char *info_)
{
	assert(info_ != NULL);

	if(m_pTextName)
		m_pTextName->SetText(info_);
}

void CXinFaUIHelper::SetText_SkillIntroduction(const char *info_)
{
	assert(info_ != NULL);

	if(m_pTextIntroduction)
		m_pTextIntroduction->SetText(info_);
}

void CXinFaUIHelper::SetText_NextSkillIntroduction(const char *info_)
{
	assert(info_ != NULL);

	if(m_pTextNextIntroduction)
		m_pTextNextIntroduction->SetText(info_);
}

bool CXinFaUIHelper::ClickXinFaIcon(const ControlIconDrag::S_ListImg *pItem_)
{
	assert(pItem_ != NULL);

	if(NULL == m_pImageBook)
		return false;

	unsigned int index = m_pImageBook->GetItemIndex(pItem_);
	SCharXinFa *pCharXinFa = thePlayerRole.m_xinFaBag.GetXinFaByID(GetXinFaIDByItemIconID(pItem_->m_pkIconInfo->Id()));
	//assert(IsValidXinFa(pCharXinFa));
	if(NULL == pCharXinFa || !IsValidXinFa(pCharXinFa))
	{
		//如果是没有学习的心法
		XinFaConfig::STalentXinFa *pXinFa = XinFaConfig::Instance().GetXinFaByID(GetXinFaIDByItemIconID(pItem_->m_pkIconInfo->Id()), XinFaConfig::EXCD_XinFaMaxLevel - 1);
		//assert(pXinFa != NULL);
		if(NULL == pXinFa)
		{
			//显示提示信息
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, 
				theXmlString.GetString(eText_Configuration_XinFa_NotOk));

			return false;
		}

		m_pSelectedXinFa = pXinFa;
		m_pSelectedSkill = NULL;

		RefreshSkills(pXinFa, true);
		pXinFa = XinFaConfig::Instance().GetXinFaByID(GetXinFaIDByItemIconID(pItem_->m_pkIconInfo->Id()), 1);

		XinFaConfig::STalentXinFa *pNextXinFa = XinFaConfig::Instance().GetXinFaByID(GetXinFaIDByItemIconID(pItem_->m_pkIconInfo->Id()), 1+1);
		if (pNextXinFa)
			SetXinFaInfo(pNextXinFa, true);

		return SetXinFaInfo(pXinFa);
		
	}
	else
	{
		//先把没有学习的心法写上
		XinFaConfig::STalentXinFa *pXinFa = XinFaConfig::Instance().GetXinFaByID(GetXinFaIDByItemIconID(pItem_->m_pkIconInfo->Id()), XinFaConfig::EXCD_XinFaMaxLevel - 1);
		//assert(pXinFa != NULL);
		if(NULL == pXinFa)
		{
			//显示提示信息
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, 
				theXmlString.GetString(eText_Configuration_XinFa_NotOk));

			return false;
		}

		m_pSelectedXinFa = pXinFa;
		m_pSelectedSkill = NULL;

		RefreshSkills(pXinFa, true);

		pXinFa = XinFaConfig::Instance().GetXinFaByID(pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel);
		//assert(pXinFa != NULL);
		if(NULL == pXinFa)
		{
			//显示提示信息
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, 
				theXmlString.GetString(eText_Configuration_XinFa_NotOk));

			return false;
		}

		m_pSelectedXinFa = pXinFa;
		m_pSelectedSkill = NULL;

		RefreshSkills(pXinFa, false, false);

		XinFaConfig::STalentXinFa *pNextXinFa = XinFaConfig::Instance().GetXinFaByID(pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel+1);
		if (pNextXinFa)
			SetXinFaInfo(pNextXinFa, true);

		return SetXinFaInfo(pXinFa);
	}

	
}

bool CXinFaUIHelper::ClickSkillIcon(const ControlIconDrag::S_ListImg *pItem_)
{
	assert(pItem_ != NULL);

	if(NULL == m_pSelectedXinFa || NULL == m_pImageSkill)
		return false;

	unsigned int index = m_pImageSkill->GetItemIndex(pItem_);
	SCharSkill *pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pItem_->m_pkIconInfo->Id());
	//assert(IsValidXinFaSkill(pCharSkill));
	if(NULL == pCharSkill || !IsValidXinFaSkill(pCharSkill))
	{
		//XinFaConfig::SXinFaSkill *pXinFaSkill = m_pSelectedXinFa->GetXinFaSkill(index);
		XinFaConfig::STalentXinFa *pXinFa = XinFaConfig::Instance().GetXinFaByID(m_pSelectedXinFa->nId, XinFaConfig::EXCD_XinFaMaxLevel - 1);
		//assert(pXinFa != NULL);
		if(NULL == pXinFa)
		{
			return false;
		}
		XinFaConfig::SXinFaSkill *pXinFaSkill = pXinFa->GetXinFaSkillByID(pItem_->m_pkIconInfo->GetItemId());
		if(NULL == pXinFaSkill || !IsValidXinFaSkill(pXinFaSkill))
		{
			return false;
		}

		m_pSelectedSkill = pXinFaSkill;
		return true;
	}
	else
	{
		//XinFaConfig::SXinFaSkill *pXinFaSkill = m_pSelectedXinFa->GetXinFaSkill(index);
		XinFaConfig::SXinFaSkill *pXinFaSkill = m_pSelectedXinFa->GetXinFaSkill(pCharSkill->ustSkillID, pCharSkill->stSkillLevel);
		if(NULL == pXinFaSkill || !IsValidXinFaSkill(pXinFaSkill))
		{
			return false;
		}

		m_pSelectedSkill = pXinFaSkill;

		return true;
	}

	
}

bool CXinFaUIHelper::SetSkillIcon(const XinFaConfig::SXinFaSkill *pItemSkill_, ControlListImage *_pListImage_, int index_/* = 0*/, bool bUseIconIndex/* = true*/, bool fixed /*= false*/)
{
	assert(pItemSkill_ != NULL  && IsValidXinFaSkill(pItemSkill_) && _pListImage_ != NULL);

	//得到技能对应的icon数据
	const SUIIconSet::SIconSet *pIcon = g_UISkillMgr.GetSkillIconSet(pItemSkill_->nId);
// 	if(NULL == pIcon)
// 		return false;

	//设置UI界面的icon
	ControlIconDrag::S_ListImg stItem;
	if(pIcon != NULL)
		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
	//stItem.SetData(pItemSkill_->nId, 1, eIcon_Enable);
	if (fixed)
	{
		stItem.SetData(pItemSkill_->nId, 1, eIcon_Disable, true, eTipFlag_SkillNoNextLevel);
	}
	else
	{
		stItem.SetData(pItemSkill_->nId, pItemSkill_->nLevel, eIcon_Enable, true, eTipFlag_SkillWithNextLevel);
	}
	
	
	stItem.SetFlags(CUISkillMgr::eProfession);

	if(bUseIconIndex)
		index_ = pIcon->index;
	
	_pListImage_->SetItem(&stItem, index_);
	_pListImage_->SetVisable(true);

	return true;
}

bool CXinFaUIHelper::SetXinFaIcon(const XinFaConfig::STalentXinFa *pXinFa_, ControlListImage *_pListImage_, int index_/* = 0*/, bool lock /*= false*/)
{
	assert(pXinFa_ != NULL && IsValidXinFa(pXinFa_) && _pListImage_ != NULL);
	if(!IsXinFaImageIndexValid(index_))
		return false;

	//得到心法对应的icon数据


	//设置UI界面的icon
	ControlIconDrag::S_ListImg stItem;
	if (!lock)
	{
		stItem.SetData(pXinFa_->nIconId, 1, eIcon_Enable, true, eTipFlag_Event);
		//stItem.SetOtherInfo("已领悟");
	}
	else
	{
		stItem.SetData(pXinFa_->nIconId, 1, eIcon_Disable, true, eTipFlag_Event);
		stItem.SetOtherInfo("未领悟");
	}
	
	
	_pListImage_->SetItem(&stItem, index_);
	_pListImage_->SetVisable(true);

	return true;
}

bool CXinFaUIHelper::CheckXinFaLevel()
{
	int xinFaCount = thePlayerRole.m_xinFaBag.GetXinFaNum();
	for(int i = 0; i < xinFaCount; ++i)
	{
		SCharXinFa *pCharXinFa = thePlayerRole.m_xinFaBag.GetXinFaByIndex(i);
		if (!pCharXinFa)
			continue;
		if (!IsValidXinFa(pCharXinFa))
			continue;

		if ( thePlayerRole.GetLevel() - pCharXinFa->nXinFaLevel >= 5 )
			return true;
	}

	return false;
}

void CXinFaUIHelper::RefreshXinFa()
{
	if(NULL == m_pImageBook || NULL == m_pImageSkill )
		return;

	//清空icon列表
	m_pImageBook->Clear();
	m_pImageSkill->Clear();
	
	m_pListXinfaLevels->Clear();
	m_pListXinfaNames->Clear();

	m_pAdditional->Clear();
	
	//ControlList::S_List	stItem;
	//stItem.SetData( "" );
	//m_pAdditional->AddItem( &stItem,NULL, false);

//把所有可以学的心法画上
	DWORD dColor = Color_Config.getColor(CC_ItemTip_Skill_Level);
	if (dColor==0)
	{
		dColor = 0xFFFF0000;
	}
	for (int i =0; i < XinFaConfig::EXCD_XinFaMaxNum; ++i)
	{
		XinFaConfig::STalentXinFa *pXinFa  = theXinFaConfig.GetXinFaByProfession(thePlayerRole.GetProfession(), i);
		if (pXinFa)
		{
			int imageIndex = GetXinFaImageIndexByItemIconID(pXinFa->nIconId);
			if(!IsXinFaImageIndexValid(imageIndex))
				continue;

			SetXinFaIcon(pXinFa, m_pImageBook, imageIndex, true);

			ControlList::S_List	stItem;

			XinFaConfig::STalentXinFa *pNeedXinFa = XinFaConfig::Instance().GetXinFaByID(pXinFa->nId, 1);
			if (!pNeedXinFa)
				return;

			DWORD dColorLevel = Color_Config.getColor(CC_ItemTip_Other);
			if (thePlayerRole.GetLevel() < pNeedXinFa->nNeedLevel)
				dColorLevel = Color_Config.getColor(CC_ItemTip_Skill_LearnNotReach);
			if (!dColorLevel)
			{
				dColorLevel = 0xFFFF0000;
			}

			char buf[128];
			sprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"{#%x=%s:#}{#%x=%d#}",dColor,theXmlString.GetString(eText_XinFaNeedLevel),dColorLevel,pNeedXinFa->nNeedLevel);		//{#%x=等级:#}%d
			stItem.RemoveSyntaxFlag(eKeyColor);
			stItem.SetData(buf,0,NULL,0xffffffff);
			

			m_pListXinfaLevels ->AddItem(&stItem,NULL,false);
			
			ControlList::S_List	stNameItem;

			stNameItem.SetData(pXinFa->strName.c_str());

			m_pListXinfaNames ->AddItem(&stNameItem);	

			//就为了点击效果加个控件，真恶心
			ControlList::S_List	temp_stItem;
			temp_stItem.SetData( "" );
			m_pAdditional->AddItem( &temp_stItem,NULL, false);
		}
		
	}
	
	

	int xinFaCount = thePlayerRole.m_xinFaBag.GetXinFaNum();
	for(int i = 0; i < xinFaCount; ++i)
	{
		SCharXinFa *pCharXinFa = thePlayerRole.m_xinFaBag.GetXinFaByIndex(i);
		assert(pCharXinFa != NULL);
		assert(IsValidXinFa(pCharXinFa));

		XinFaConfig::STalentXinFa *pXinFa = XinFaConfig::Instance().GetXinFaByID(pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel);
		assert(pXinFa != NULL);
		//实际运行过程中，因为配置文件的问题经常导致上述断言不成立，如果程序继续运行，将造成客户端异常。
		if(NULL == pXinFa)
		{
			//显示提示信息
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, 
							theXmlString.GetString(eText_Configuration_XinFa_NotOk));

			continue;
		}

		int imageIndex = GetXinFaImageIndexByItemIconID(pXinFa->nIconId);
		if(!IsXinFaImageIndexValid(imageIndex))
			continue;

		SetXinFaIcon(pXinFa, m_pImageBook, imageIndex);

		
		char buf[128];
		sprintf_s(buf, sizeof(buf)/sizeof(char) - 1,"{#%x=%s:#}%d",dColor,theXmlString.GetString(eText_XinFaCengShu),pXinFa->nLevel);		

		ControlList::S_List* stItem = m_pListXinfaLevels->GetListItem(imageIndex);
		stItem->RemoveSyntaxFlag(eKeyColor);
		stItem->SetData(buf,0, NULL, 0xffffffff);
		m_pListXinfaLevels->ParseText(stItem, NULL);
		//m_pListXinfaLevels->AddItem(stItem,NULL,false);
		//就为了点击效果加个控件，真恶心
// 		ControlList::S_List	temp_stItem;
// 		temp_stItem.SetData( "" );
// 		m_pAdditional->AddItem( &temp_stItem,NULL, false);
		
	}
	bool bFixSelect = false;
	if(m_pSelectedXinFa != NULL)
	{
		//判断当前所指心法是否有效，因为心法包有可能已经更新了
		SCharXinFa *pCharXinFa = thePlayerRole.m_xinFaBag.GetXinFaByID(m_pSelectedXinFa->nId);
		if(NULL == pCharXinFa/* || m_pSelectedXinFa->nLevel != pCharXinFa->nXinFaLevel*/)
		{
			//m_pSelectedXinFa = NULL;	//无效则置空
			XinFaConfig::STalentXinFa *pXinFa = XinFaConfig::Instance().GetXinFaByID(m_pSelectedXinFa->nId, XinFaConfig::EXCD_XinFaMaxLevel - 1);
			//assert(pXinFa != NULL);
			if(NULL == pXinFa)
			{
				ClearSelectedInfo();
			}
			else
			{
				bFixSelect = true;
			}
		}
		else
		{
			//有可能已经升级了
			m_pSelectedXinFa = XinFaConfig::Instance().GetXinFaByID(pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel);
		}

		
	}

	if(NULL == m_pSelectedXinFa)
	{
		m_pSelectedSkill = NULL;

		if(xinFaCount > 0)
		{
			SCharXinFa *pCharXinFa = thePlayerRole.m_xinFaBag.GetXinFaByIndex(0);
			//assert(pCharXinFa != NULL && IsValidXinFa(pCharXinFa));
			if(NULL == pCharXinFa || !IsValidXinFa(pCharXinFa))
			{
				return;
			}			

			XinFaConfig::STalentXinFa *pXinFa = XinFaConfig::Instance().GetXinFaByID(pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel);
			//assert(pXinFa != NULL);
			if(NULL == pXinFa)
			{
				return;
			}

			m_pSelectedXinFa = pXinFa;
		}
		
	}

	if(NULL == m_pSelectedXinFa)
		return;

	XinFaConfig::STalentXinFa *pXinFa = XinFaConfig::Instance().GetXinFaByID(m_pSelectedXinFa->nId, XinFaConfig::EXCD_XinFaMaxLevel - 1);
	//assert(pXinFa != NULL);
	if(NULL == pXinFa)
	{
		return;
	}
	RefreshSkills(pXinFa, true);

	if (bFixSelect)
	{
		RefreshSkills(m_pSelectedXinFa, true, false);
	}
	else
	{
		//更新当前心法所拥有的技能对应的image信息
		RefreshSkills(m_pSelectedXinFa, false, false);
	}


	//更新当前选择的心法或技能说明
	if(m_pSelectedSkill != NULL)
	{
		if(NULL == thePlayerRole.m_SkillBag.GetSkillByID(m_pSelectedSkill->nId) &&
			NULL == m_pSelectedXinFa->GetXinFaSkillByID(m_pSelectedSkill->nId))
		{
			m_pSelectedSkill = NULL;
		}
	}

	//m_pAdditional->SetShowStartHeight(6);
	//m_pAdditional->SetScrollValue(20);

	SetXinFaInfo(m_pSelectedXinFa);

	XinFaConfig::STalentXinFa *pNextXinFa = XinFaConfig::Instance().GetXinFaByID(m_pSelectedXinFa->nId, m_pSelectedXinFa->nLevel+1);
	if (!pNextXinFa)
		return;
	SetXinFaInfo(pNextXinFa, true);
}

void CXinFaUIHelper::RefreshSkills(XinFaConfig::STalentXinFa *pXinFa_, bool bFixed /*= false*/, bool bClearList /*= true*/)
{
	assert(pXinFa_ != NULL);

	if(NULL == m_pImageSkill)
		return;
	//清空icon列表
	if (bClearList)
	{
		for(uint8 skillIndex = 0; skillIndex < XinFaConfig::EXCD_SkillMaxCount; ++skillIndex)
		{
			m_pTextNeedXinfaLevels[skillIndex]->SetText("");
			m_pTextSkillNames[skillIndex]->SetText("");
			m_pTextSkillCondition[skillIndex]->SetText("");
		}
		m_pImageSkill->Clear();
	}

	//这里是从配置文件读取技能是否激活。
	//更好的做法应该是从当前的技能包里判断技能是否激活
	DWORD dColor = Color_Config.getColor(CC_ItemTip_Skill_LearnNotReach);
	if (dColor==0)
	{
		dColor = 0xFFFF0000;
	}
	for(uint8 skillIndex = 0; skillIndex < XinFaConfig::EXCD_SkillMaxCount; ++skillIndex)
	{

		XinFaConfig::SXinFaSkill *pXinFaSkill = pXinFa_->GetXinFaSkill(skillIndex);
		if(NULL == pXinFaSkill || !IsValidXinFaSkill(pXinFaSkill))
			continue;
		ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pXinFaSkill->nId, 1);
		if (pSkill)
		{
			m_pTextSkillNames[skillIndex]->SetText(pSkill->GetSkillName());
		}		
		
		
		if (bFixed)
		{
			SetSkillIcon(pXinFaSkill, m_pImageSkill, skillIndex, false, true);	//根据心法配置文件里的顺序进行排序			
			m_pTextSkillCondition[skillIndex]->SetText(theXmlString.GetString(eText_SkillNotGain),0xFFFF0000);
			
		}
		else
		{
			SetSkillIcon(pXinFaSkill, m_pImageSkill, skillIndex, false);	//根据心法配置文件里的顺序进行排序
			m_pTextSkillCondition[skillIndex]->SetText(theXmlString.GetString(eText_SkillAlreadyGain),0xFF00FF00);
			
		}
		
		
		ControlIconDrag::S_ListImg *pImg = m_pImageSkill->GetItemByIndex(skillIndex);
		assert(pImg != NULL);
		if(NULL == pImg)
		{
			continue;
		}
		if (!bFixed)
		{
			if(pXinFa_->IsActiveSkillByIndex(skillIndex))
			{//已激活的技能
				pImg->SetEnable(eIcon_Enable);
			}
			else
			{
				pImg->SetEnable(eIcon_Disable);
			}
		}
		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID( pXinFaSkill->nId,
			pXinFaSkill->nLevel );
		//属于被动技能就不让拖动icon
		if (NULL!=pItemSkill && (ItemDefine::generaltype_passive == pItemSkill->stGeneralType  ||ItemDefine::generaltype_trigger == pItemSkill->stGeneralType ) )
		{
			pImg->SetEnable(eIcon_Disable);
		}
		else
		{
		}

		if(!bFixed)
		{
			dColor = Color_Config.getColor(CC_ItemTip_Skill_Level);
			if (dColor==0)
			{
				dColor = 0xFFFF0000;
			}
			char buf[32];
			sprintf(buf, theXmlString.GetString(eText_XinFaSkillLevel),dColor, pXinFaSkill->nLevel);
			m_pTextNeedXinfaLevels[skillIndex]->SetText(buf);
		}
		else
		{
			int nNeedXinFaLevel = theXinFaConfig.GetSkillNeedXinFaLevel(pXinFa_->nId, pXinFaSkill->nId);
			char buf[32];
			sprintf(buf, theXmlString.GetString(eText_XinFaNeedCengShu),dColor, nNeedXinFaLevel);
			m_pTextNeedXinfaLevels[skillIndex]->SetText(buf);
		}
		
	}
}

void CXinFaUIHelper::ClearSelectedInfo(void)
{
	m_pSelectedXinFa = NULL;
	m_pSelectedSkill = NULL;
}

const char* AttrTypeToDesc(uint8 uTypeID)
{
	switch (uTypeID)			//42
	{
	case 0:
		return NULL;
	case 1:						//CharAttr_AddStrength
		return theXmlString.GetString(eTip_sAddStrength);			//武力
	case 2:						//CharAttr_AddAgility
		return theXmlString.GetString(eTip_sAddAgility);			//敏捷
	case 3:
		return theXmlString.GetString(eTip_sAddConstitution);		//体质
	case 4:
		return theXmlString.GetString(eTip_sAddIntelligence);		//智力
	case 5:
		return theXmlString.GetString(eTip_sAddHPDamage);			//附加伤害
	case 6:
		return theXmlString.GetString(eTip_sAddHPRestore);			//附加治疗
	case 7:
		return theXmlString.GetString(eTip_sAddAOE);				//AOE攻击人数
	/////////////////////////////////////
	case 8:						
		return theXmlString.GetString(eTip_sAddShortAttack);			//物理攻击
	case 9:					
		return theXmlString.GetString(eTip_sAddMagicAttack);			//法术攻击
	case 10:
		return theXmlString.GetString(eTip_sAddShortDefend);			//物理防御
	case 11:
		return theXmlString.GetString(eTip_sAddMagicDefend);			//法术防御
	case 12:
		return theXmlString.GetString(eTip_sAddExact);				//命中
	case 13:
		return theXmlString.GetString(eTip_sAddDodge);			//闪避
	case 14:
		return theXmlString.GetString(eTip_sAddCritical);			//暴击率
	case 15:
		return theXmlString.GetString(eTip_sAddCriticalIntensity);	//暴击伤害
	case 16:
		return theXmlString.GetString(eTip_sAddTenacity);				//韧性
	case 17:
		return theXmlString.GetString(eTip_sAddStrength);				//力量
	case 18:
		return theXmlString.GetString(eTip_sAddAgility);				//敏捷
	case 19:
		return theXmlString.GetString(eTip_sAddConstitution);				//体质
	case 20:
		return theXmlString.GetString(eTip_sAddIntelligence);				//智力
	case 21:
		return theXmlString.GetString(eTip_sAddHPDamage);				//附加伤害
	case 22:
		return theXmlString.GetString(eTip_sAddHPRestore);				//附加治疗
	case 23:
		return theXmlString.GetString(eTip_sAddShortAttack);			//物理攻击
	case 24:
		return theXmlString.GetString(eTip_sAddMagicAttack);				//法术攻击
	case 25:
		return theXmlString.GetString(eTip_sAddShortDefend);				//物理防御
	case 26:
		return theXmlString.GetString(eTip_sAddMagicDefend);				//法术防御
	case 27:
		return theXmlString.GetString(eTip_sAddExact);				//命中
	case 28:
		return theXmlString.GetString(eTip_sAddDodge);				//闪避
	case 29:
		return theXmlString.GetString(eTip_sAddCritical);				//暴击率
	case 30:
		return theXmlString.GetString(eTip_sAddCriticalIntensity);				//暴击伤害
	case 31:
		return theXmlString.GetString(eTip_sAddTenacity);				//韧性
	case 32:
		return theXmlString.GetString(eTip_sAddSuckDamage);				//吸收伤害
	case 33:
		return theXmlString.GetString(eUI_nHpMax);						//HP上限
	case 34:
		return theXmlString.GetString(eUI_sMpMax);						//MP上限
	default:
		return NULL;
	}
	
}