/********************************************************************
	Created by UIEditor.exe
	FileName: AutoAttackSet.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "AutoAttackSet.h"
#include "Pack.h"
#include "PlayerRole.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "Skill.h"
#include "Pack.h"
#include "ActionUI.h"
#include "baseProperty.h"
#include "PickUp.h"
#include "MathLib.h"
#include "color_config.h"
#include "exmain.h"
#include "UserData.h"
#include <vector>
#ifdef _DEBUG
#include "MeUi/FontManager.h"
#include "MeFont\MeFont.h"
#include "MeFont/MeFontSystem.h"
#endif
#include "RapidXml/MeRapidXml.h"
#include "Common.h"
#include "ScreenInfoManager.h"
#include "packet_interface.h"
#include "Group_DeBuffUI.h"
#include "ui/Target.h"
#include "ui/Team.h"
#include "MonsterDefine.h"

extern BOOL	g_bTheRoleAttackLockTarget;
extern int g_nRoleCommonAttackStatus;
extern BOOL g_bTheRoleMoveToTargetPos;
DWORD AutoFight::s_dwElapseTime = 2000;
#define WAITTIME  2000  //�೤ʱ�䷢��Ϣ

CUI_ID_FRAME_AutoAttackSet s_CUI_ID_FRAME_AutoAttackSet;
MAP_FRAME_RUN( s_CUI_ID_FRAME_AutoAttackSet, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AutoAttackSet, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_PickItemOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_SUODINGOnCheckBoxCheck)
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_AdvanceOnCheckBoxCheck )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_EDIT_HpOnEditEnter )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillAttackOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillAttackOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillAttackOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillAttackOnIconRButtonUp )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_EDIT_MpOnEditEnter )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_AutoAttackOnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillBuffOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillBuffOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillBuffOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillBuffOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_HpOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_HpOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_HpOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_HpOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_MpOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_MpOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_MpOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_MpOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_BeginOnButtonClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_ProtectionBeginOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_ProtectionStopOnButtonClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_PickOnOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_PickOffOnButtonClick )


MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_StopOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_EDIT_SkillHpOnEditEnter )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpOnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_HpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_MpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_TpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_BackOnCheckBoxCheck )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_EDIT_BackHpOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_RenovateOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_AllOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_ReverseOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LIST_MonsterOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_NormalOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_BigOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_SmallOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_Team1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_Team2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_Setting1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_Setting2OnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_DefaultOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_BUTTON_SaveOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_EnergyOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_TeamNeedOnCheckBoxCheck )


MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_CHECKBOX_IsCheckHpTeamOnCheckBoxCheck )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_EDIT_TeamSkillHpOnEditEnter )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpTeamOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpTeamOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpTeamOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpTeamOnIconRButtonUp )
CUI_ID_FRAME_AutoAttackSet::CUI_ID_FRAME_AutoAttackSet()
{
	// Member
	ResetMembers();
	m_bSave = false;
	m_bUILoad = false;
}

void CUI_ID_FRAME_AutoAttackSet::ResetMembers()
{
	m_pID_FRAME_AutoAttackSet = NULL;
// 	m_pID_TEXT_UseItemZ = NULL;
	m_pID_CHECKBOX_PickItem = NULL;
	m_pID_CHECKBOX_SUODING = NULL;
// 	m_pID_TEXT_PickItemZ = NULL;
	m_pID_CHECKBOX_Advance = NULL;
// 	m_pID_TEXT_HpZ = NULL;
	m_pID_EDIT_Hp = NULL;
// 	m_pID_TEXT_HpZ2 = NULL;
	m_pID_LISTIMG_SkillAttack = NULL;
// 	m_pID_TEXT_MpZ = NULL;
	m_pID_EDIT_Mp = NULL;
// 	m_pID_TEXT_MpZ2 = NULL;
// 	m_pID_TEXT_AutoAttackZ = NULL;
	m_pID_CHECKBOX_AutoAttack = NULL;
// 	m_pID_TEXT_SkillAttackZ = NULL;
// 	m_pID_TEXT_SkillBuffZ = NULL;
	m_pID_LISTIMG_SkillBuff = NULL;
	m_pID_LISTIMG_Hp = NULL;
	m_pID_LISTIMG_Mp = NULL;
	m_pID_BUTTON_Begin = NULL;
	m_pID_BUTTON_ProtectionBegin = NULL;
	m_pID_BUTTON_ProtectionStop = NULL;
	m_pID_BUTTON_PickOn = NULL;
	m_pID_BUTTON_PickOff = NULL;
	m_pID_BUTTON_Cancel = NULL;
// 	m_pID_PICTURE_Title = NULL;
	m_pID_BUTTON_Stop = NULL;
	//m_pID_PICTURE_TitleWord = NULL;
	m_pID_EDIT_SkillHp = NULL;
	m_pID_LISTIMG_SkillHp = NULL;
	m_pID_CHECKBOX_Hp = NULL;
	m_pID_CHECKBOX_Mp = NULL;
	m_pID_CHECKBOX_Tp = NULL;
	m_pID_EDIT_Hp = NULL;
	m_pID_EDIT_Mp = NULL;
	m_pID_BUTTON_Renovate = NULL;
	m_pID_BUTTON_All = NULL;
	m_pID_BUTTON_Reverse = NULL;
	m_pID_LIST_Monster = NULL;
	m_pID_CHECKBOX_Normal = NULL;
	m_pID_CHECKBOX_Big = NULL;
	m_pID_CHECKBOX_Small = NULL;

	m_pID_CHECKBOX_Team1 = NULL;
	m_pID_CHECKBOX_Team2 = NULL;

	m_pID_CHECKBOX_Setting1 = NULL;
	m_pID_CHECKBOX_Setting2 = NULL;

	m_pID_BUTTON_Default = NULL;
	m_pID_BUTTON_Save = NULL;

	m_pID_TEXT_TimeText = NULL;
	m_pID_TEXT_Time = NULL;

	m_pID_CHECKBOX_Energy = NULL;
	m_pID_CHECKBOX_TeamNeed = NULL;

	m_pID_CHECKBOX_IsCheckHpTeam= NULL;
	m_pID_EDIT_TeamSkillHp= NULL;
	m_pID_LISTIMG_SkillHpTeam= NULL;

	BeginAutoAttackTime = 0;

}
// Frame
bool CUI_ID_FRAME_AutoAttackSet::OnFrameRun()
{
	if(IsVisable())
	{
		UpdateUIData();
		ControlIconDrag::S_ListImg *pImg = NULL;
		SCharSkill                 *pCharSkill = NULL;
		for (int index = 0;index < USEMAXSKILL;++index)
		{
			//��������
			pImg = m_pID_LISTIMG_SkillAttack->GetItemByIndex(index);
			if(pImg)
			{
				pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pImg->m_pkIconInfo->Id());
				if(pCharSkill && pCharSkill->ustSkillID != InvalidLogicNumber)
				{
					pImg->SetEnable(pCharSkill->bAvailable?eIcon_Enable:eIcon_Disable);
					UpdateCD(pCharSkill->ustSkillID,m_pID_LISTIMG_SkillAttack,index);
				}
			}

			pImg = m_pID_LISTIMG_SkillBuff->GetItemByIndex(index);
			if(pImg)
			{
				pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pImg->m_pkIconInfo->Id());
				if(pCharSkill&&pCharSkill->ustSkillID != InvalidLogicNumber)
				{
					pImg->SetEnable(pCharSkill->bAvailable?eIcon_Enable:eIcon_Disable);
					UpdateCD(pCharSkill->ustSkillID,m_pID_LISTIMG_SkillBuff,index);
				}
			}

			pImg = m_pID_LISTIMG_SkillHp->GetItemByIndex(index);
			if(pImg)
			{
				pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pImg->m_pkIconInfo->Id());
				if(pCharSkill&&pCharSkill->ustSkillID != InvalidLogicNumber)
				{
					pImg->SetEnable(pCharSkill->bAvailable?eIcon_Enable:eIcon_Disable);
					UpdateCD(pCharSkill->ustSkillID,m_pID_LISTIMG_SkillHp,index);
				}
			}

			pImg = m_pID_LISTIMG_SkillHpTeam->GetItemByIndex(index);
			if(pImg)
			{
				pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pImg->m_pkIconInfo->Id());
				if(pCharSkill&&pCharSkill->ustSkillID != InvalidLogicNumber)
				{
					pImg->SetEnable(pCharSkill->bAvailable?eIcon_Enable:eIcon_Disable);
					UpdateCD(pCharSkill->ustSkillID,m_pID_LISTIMG_SkillHpTeam,index);
				}
			}
		}
	}
	return true;
}
bool CUI_ID_FRAME_AutoAttackSet::OnFrameRender()
{        
#ifdef _DEBUG
	m_autoFight.DebugInfo();
#endif
	return true;
}
// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_PickItemOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(*pbChecked)
		m_autoFight.AddPickFlag(Pick_All);
	else
		m_autoFight.RemovePickFlag(Pick_All);

	m_bSave = true;
}

//CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_SUODINGOnCheckBoxCheck(ControlObject *pSender, bool *pbChecked)
{
	if (*pbChecked)
	{
		m_autoFight.AddSuoDingFlag(SuoDing_All);
		m_pID_BUTTON_Renovate->SetEnable(FALSE);
		m_pID_BUTTON_All->SetEnable(FALSE);
		m_pID_BUTTON_Reverse->SetEnable(FALSE);
		//this->ID_BUTTON_RenovateOnButtonClick(NULL);//zhuxincong 9.3 ��д�Ŀ��ܲ������߼�
		theHeroGame.GetPlayerMgr()->UpdateMonsterType();
		SetUpdateUI(true);
	}
	else
	{
		m_autoFight.RemoveSuoDingFlag(SuoDing_All);
		m_pID_BUTTON_Renovate->SetEnable(TRUE);
		m_pID_BUTTON_All->SetEnable(TRUE);
		m_pID_BUTTON_Reverse->SetEnable(TRUE);
	}

	m_bSave = true;

}
// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_IsCheckHpTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked)
{
	OnCheckTeamHpSkill(*pbChecked);//������������Ѫ���õ�ʱ�� ������һЩ����
}
// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_AdvanceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
}
// Edit
void CUI_ID_FRAME_AutoAttackSet::ID_EDIT_HpOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_AutoAttackSet::ID_EDIT_TeamSkillHpOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// ListImg / ListEx  --��������
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillAttackOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{  
    int nIndexDrag = m_pID_LISTIMG_SkillAttack->GetItemIndex(pItemDrag);
    int nIndexSrc  = m_pID_LISTIMG_SkillAttack->GetItemIndex(pItemSrc);

    if(pSender == pMe)
    {
        ControlIconDrag::S_ListImg pDrag;
        ControlIconDrag::S_ListImg pSrc ;

        pDrag = *m_pID_LISTIMG_SkillAttack->GetItemByIndex(nIndexDrag);
        pSrc = *m_pID_LISTIMG_SkillAttack->GetItemByIndex(nIndexSrc);
        
        m_pID_LISTIMG_SkillAttack->SetItem(&pSrc,nIndexDrag);
        m_pID_LISTIMG_SkillAttack->SetItem(&pDrag,nIndexSrc);
        m_bSave = true;

		//���������
		m_autoFight.SetAttackSkill(NULL,nIndexDrag);
		m_autoFight.SetAttackSkill(NULL,nIndexSrc);

		//�����¼���
		SetAttackSkill(nIndexDrag,pItemDrag->m_pkIconInfo->Id());
		SetAttackSkill(nIndexSrc,pItemSrc->m_pkIconInfo->Id());

    }
    else if(s_CUI_ID_FRAME_SKILL.IsSkillList( pSender )
        ||pSender == s_CUI_ID_FRAME_MAIN.GetHotKeyListImage()/*m_pID_LISTIMG_Hotkey*/
        ||pSender == s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain1()
        ||pSender == s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain2())
    {
        SCharSkill *pCharSkill = NULL;
        pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pItemDrag->m_pkIconInfo->Id());
        if ( !pCharSkill ||pCharSkill->ustSkillID == InvalidLogicNumber)
            return false;

        // �����ж�
        ItemDefine::SItemSkill* pSkill = NULL; 
        pSkill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID, pCharSkill->stSkillLevel);
        if( !pSkill || pSkill->sSkillCategory != ItemDefine::SCT_Attack )
            return false;

		//zhuxincong 9.3 ��߻�����Ⱥ������Ҳ�ǿ��Է���ȥ��
        //Ⱥ������Ҳ���ܷ��� ���Ҫ������
	/*	if(!pSkill || (pSkill->shCastType != ItemDefine::casttype_singletarget && pSkill->shCastType != ItemDefine::casttype_AOEcircleself && pSkill->shCastType != ItemDefine::casttype_AOETargetcirclearea))
           return false;*/

        ControlIconDrag::S_ListImg img = *pItemDrag;
        img.m_pkIconInfo->m_strHotKey = "";
        m_pID_LISTIMG_SkillAttack->SetItem(&img,nIndexSrc);

        m_bSave = true;
       
		SetAttackSkill(nIndexSrc,pItemSrc->m_pkIconInfo->Id());
    }

	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillAttackOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillAttackOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillAttackOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Edit
void CUI_ID_FRAME_AutoAttackSet::ID_EDIT_MpOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_AutoAttackOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{

}
// ListImg / ListEx--��������
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillBuffOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
    int nIndexDrag = m_pID_LISTIMG_SkillBuff->GetItemIndex(pItemDrag);
    int nIndexSrc  = m_pID_LISTIMG_SkillBuff->GetItemIndex(pItemSrc);
    if(pSender == pMe)
    {
        ControlIconDrag::S_ListImg pDrag;
        ControlIconDrag::S_ListImg pSrc ;

        pDrag = *m_pID_LISTIMG_SkillBuff->GetItemByIndex(nIndexDrag);
        pSrc = *m_pID_LISTIMG_SkillBuff->GetItemByIndex(nIndexSrc);

        m_pID_LISTIMG_SkillBuff->SetItem(&pSrc,nIndexDrag);
        m_pID_LISTIMG_SkillBuff->SetItem(&pDrag,nIndexSrc);

		//���������
		m_autoFight.SetBufSkill(NULL,nIndexDrag);
		m_autoFight.SetBufSkill(NULL,nIndexSrc);

		//�����¼���
		SetBufSkill(nIndexDrag,pItemDrag->m_pkIconInfo->Id());
		SetBufSkill(nIndexSrc,pItemSrc->m_pkIconInfo->Id());

        m_bSave = true;

    }
    else if(s_CUI_ID_FRAME_SKILL.IsSkillList(pSender)
        ||pSender == s_CUI_ID_FRAME_MAIN.GetHotKeyListImage()/*m_pID_LISTIMG_Hotkey*/
        ||pSender == s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain1()
        ||pSender == s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain2())
    {
        SCharSkill *pCharSkill = NULL;
        pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pItemDrag->m_pkIconInfo->Id());
        if ( !pCharSkill ||pCharSkill->ustSkillID == InvalidLogicNumber)
            return false;

        // �����ж�
        ItemDefine::SItemSkill* pSkill = NULL; 
        pSkill = GettheItemDetail().GetSkillByID(pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
        if( !pSkill || pSkill->sSkillCategory != ItemDefine::SCT_Assistant )
            return false;

        //Ⱥ������Ҳ���ܷ���
        if(!pSkill || pSkill->shCastType != ItemDefine::casttype_singletarget)
            return false;

        ControlIconDrag::S_ListImg img = *pItemDrag;
        img.m_pkIconInfo->m_strHotKey = "";

        m_pID_LISTIMG_SkillBuff->SetItem(&img,nIndexSrc);

		SetBufSkill(nIndexSrc,pItemSrc->m_pkIconInfo->Id());
        m_bSave = true;
    }

	return false;
}

bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillBuffOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillBuffOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillBuffOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillHpOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
	ControlIconDrag::S_ListImg* pItemDrag,
	ControlIconDrag::S_ListImg* pItemSrc )
{
	int nIndexDrag = m_pID_LISTIMG_SkillHp->GetItemIndex(pItemDrag);
	int nIndexSrc  = m_pID_LISTIMG_SkillHp->GetItemIndex(pItemSrc);
	if(pSender == pMe)
	{
		ControlIconDrag::S_ListImg pDrag;
		ControlIconDrag::S_ListImg pSrc ;

		pDrag = *m_pID_LISTIMG_SkillHp->GetItemByIndex(nIndexDrag);
		pSrc = *m_pID_LISTIMG_SkillHp->GetItemByIndex(nIndexSrc);

		m_pID_LISTIMG_SkillHp->SetItem(&pSrc,nIndexDrag);
		m_pID_LISTIMG_SkillHp->SetItem(&pDrag,nIndexSrc);

		m_bSave = true;

		//���������
		m_autoFight.SetRecSkill(NULL,nIndexDrag,0);
		m_autoFight.SetRecSkill(NULL,nIndexSrc,0);

		//�����¼���
		SetHpSkill(nIndexDrag,pItemDrag->m_pkIconInfo->Id());
		SetHpSkill(nIndexSrc,pItemSrc->m_pkIconInfo->Id());

	}
	else if(s_CUI_ID_FRAME_SKILL.IsSkillList(pSender)
		||pSender == s_CUI_ID_FRAME_MAIN.GetHotKeyListImage()/*m_pID_LISTIMG_Hotkey*/
		||pSender == s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain1()
		||pSender == s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain2())
	{
		SCharSkill *pCharSkill = NULL;
		pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pItemDrag->m_pkIconInfo->Id());
		if ( !pCharSkill ||pCharSkill->ustSkillID == InvalidLogicNumber)
			return false;

		ItemDefine::SItemSkill* pSkill = NULL; 
		pSkill = GettheItemDetail().GetSkillByID(pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
		if( !pSkill || pSkill->ustDamageBalanceType != ItemDefine::balancetype_restorehpmp )
			return false;

		ControlIconDrag::S_ListImg img = *pItemDrag;
		img.m_pkIconInfo->m_strHotKey = "";

		m_pID_LISTIMG_SkillHp->SetItem(&img,nIndexSrc);

		m_bSave = true;

		SetHpSkill(nIndexSrc,pItemSrc->m_pkIconInfo->Id());
	}

	return false;
}

bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillHpOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillHpOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillHpOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_HpOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
    if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
    {
        int nPackIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
        if ( nPackIndex == -1 || nPackIndex >= thePlayerRole.m_bag.GetNowBagSize())
            return false;

        //��Ʒ�������ֹ����
        SCharItem stItems;
        thePlayerRole.m_bag.GetItem( nPackIndex, &stItems );
        if(stItems.storageinfo.bIsLocked)
        {
            s_CUI_ID_FRAME_MessageBox.Show(  theXmlString.GetString(eText_ItemHaveBeenLocked) );
            return false;
        }

        ItemDefine::SItemCommon *pItemCommon = NULL;
        pItemCommon = GettheItemDetail().GetItemByID( stItems.itembaseinfo.ustItemID);
        if( !pItemCommon )
            return false;

        if(pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE)
        {

			if(pItemCommon->byUserTarget != ItemDefine::eTargetMe)
				return false; 

            ItemDefine::SItemRestore *pItemRestore;
            pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;

            if(pItemRestore->dwAddHP <= 0)
                return false;

			if(thePlayerRole.GetLevel() <  pItemRestore->stUseLevel)
			{
			
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString(eText_AutoFightUseRestorLev) );
				return false;
			}


			ControlIconDrag::S_ListImg _temp;		
			_temp.SetData( pItemDrag->m_pkIconInfo->Id(),1,eIcon_Enable );
			m_pID_LISTIMG_Hp->SetItem(&_temp,0);  
        }
        m_bSave = true;
		m_autoFight.m_HpItemId = pItemCommon->ustItemID;

    }

	return false;
}

bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_HpOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_HpOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_HpOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillHpTeamOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	//�����Ѫ��������
	int nIndexDrag = m_pID_LISTIMG_SkillHpTeam->GetItemIndex(pItemDrag);
	int nIndexSrc  = m_pID_LISTIMG_SkillHpTeam->GetItemIndex(pItemSrc);
	if(pSender == pMe)
	{
		ControlIconDrag::S_ListImg pDrag;
		ControlIconDrag::S_ListImg pSrc ;

		pDrag = *m_pID_LISTIMG_SkillHpTeam->GetItemByIndex(nIndexDrag);
		pSrc = *m_pID_LISTIMG_SkillHpTeam->GetItemByIndex(nIndexSrc);

		m_pID_LISTIMG_SkillHpTeam->SetItem(&pSrc,nIndexDrag);
		m_pID_LISTIMG_SkillHpTeam->SetItem(&pDrag,nIndexSrc);

		m_bSave = true;

		//���������
		m_autoFight.SetRecTeamSkill(NULL,nIndexDrag,m_autoFight.GetRecHpTeamPer());
		m_autoFight.SetRecTeamSkill(NULL,nIndexSrc,m_autoFight.GetRecHpTeamPer());

		//�����¼���
		SetHpTeamSkill(nIndexDrag,pItemDrag->m_pkIconInfo->Id());
		SetHpTeamSkill(nIndexSrc,pItemSrc->m_pkIconInfo->Id());

	}
	else if(s_CUI_ID_FRAME_SKILL.IsSkillList(pSender)
		||pSender == s_CUI_ID_FRAME_MAIN.GetHotKeyListImage()/*m_pID_LISTIMG_Hotkey*/
		||pSender == s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain1()
		||pSender == s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain2())
	{
		SCharSkill *pCharSkill = NULL;
		pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pItemDrag->m_pkIconInfo->Id());
		if ( !pCharSkill ||pCharSkill->ustSkillID == InvalidLogicNumber)
			return false;

		ItemDefine::SItemSkill* pSkill = NULL; 
		pSkill = GettheItemDetail().GetSkillByID(pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
		if( !pSkill || pSkill->ustDamageBalanceType != ItemDefine::balancetype_restorehpmp )
			return false;

		ControlIconDrag::S_ListImg img = *pItemDrag;
		img.m_pkIconInfo->m_strHotKey = "";

		m_pID_LISTIMG_SkillHpTeam->SetItem(&img,nIndexSrc);

		m_bSave = true;

		SetHpTeamSkill(nIndexSrc,pItemSrc->m_pkIconInfo->Id());
	}
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillHpTeamOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillHpTeamOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_SkillHpTeamOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_MpOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
    if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
    {
        int nPackIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
        if ( nPackIndex == -1 || nPackIndex >= thePlayerRole.m_bag.GetNowBagSize())
               return false;
    
         //��Ʒ�������ֹ����
         SCharItem stItems;
         thePlayerRole.m_bag.GetItem( nPackIndex, &stItems );
         if(stItems.storageinfo.bIsLocked)
         {
             s_CUI_ID_FRAME_MessageBox.Show(  theXmlString.GetString(eText_ItemHaveBeenLocked) );
              return false;
         }

         ItemDefine::SItemCommon *pItemCommon = NULL;
         pItemCommon = GettheItemDetail().GetItemByID( stItems.itembaseinfo.ustItemID);
         if( !pItemCommon )
             return false;

         if(pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE)
         {
             ItemDefine::SItemRestore *pItemRestore;
             pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;

             if(pItemRestore->dwAddMP <= 0)
                 return false;

			if(thePlayerRole.GetLevel() <  pItemRestore->stUseLevel)
			{

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString(eText_AutoFightUseRestorLev) );
				return false;
			}

			 ControlIconDrag::S_ListImg _temp;		
			 _temp.SetData( pItemDrag->m_pkIconInfo->Id(),1,eIcon_Enable );
			 m_pID_LISTIMG_Mp->SetItem(&_temp,0);

         }

         m_bSave = true;
		 m_autoFight.m_MpItemId = pItemCommon->ustItemID;
    }

	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_MpOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_MpOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_LISTIMG_MpOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_BeginOnButtonClick( ControlObject* pSender )
{
	if( !IsUILoad() )
		return false;

	MsgOfflineFightOpReq msg;
	msg.op = EOfflineFightOP_Begin;
	GettheNetworkInput().SendMsg( &msg );
	
	return true;
}

bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_ProtectionBeginOnButtonClick( ControlObject* pSender )
{
	/*
	*	Author 2012-9-15 zhuxincong
	*	DESC: ID_BUTTON_ProtectionStop ID_BUTTON_ProtectionBegin ��������Ϸ���ж��ǲ����ڱ���״̬������HP��MP ���˶��پ��Լ�������Ѫ
	*/
	std::string strMP = m_pID_EDIT_Mp->GetText();
	int nValueMP = atoi(strMP.c_str());
	
	m_autoFight.SetMp(true,nValueMP);

	std::string strHP = m_pID_EDIT_Hp->GetText();
	int nValueHP = atoi(strHP.c_str());

	m_autoFight.SetHp(true,nValueHP);

	m_pID_BUTTON_ProtectionStop->SetVisable(true);
	m_pID_BUTTON_ProtectionBegin->SetVisable(false);

	//m_autoFight.BeginFight();
	m_autoFight.BeginProtection();
	
	m_bSave = true;
	return true;
}

bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_ProtectionStopOnButtonClick( ControlObject* pSender )
{
	std::string strMP = m_pID_EDIT_Mp->GetText();
	int nValueMP = atoi(strMP.c_str());

	m_autoFight.SetMp(false,nValueMP);

	std::string strHP = m_pID_EDIT_Hp->GetText();
	int nValueHP = atoi(strHP.c_str());

	m_autoFight.SetHp(false,nValueHP);

//	m_pID_BUTTON_ProtectionBegin->SetVisable(true);

	
	//m_autoFight.EndFight(); 
	//m_autoFight.Process();
	
	m_pID_BUTTON_ProtectionBegin->SetVisable(true);
	m_pID_BUTTON_ProtectionStop->SetVisable(false);
	m_autoFight.EndinProtection();

	return true;
}


bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_PickOnOnButtonClick(ControlObject* pSender)
{
	m_autoFight.AddPickFlag(Pick_All);
	m_pID_BUTTON_PickOn->SetVisable(false);
	m_pID_BUTTON_PickOff->SetVisable(true);
	m_autoFight.BeginPick();
	m_bSave = true;
	return true;
}

bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_PickOffOnButtonClick(ControlObject* pSender)
{
	m_autoFight.RemovePickFlag(Pick_None);
	m_pID_BUTTON_PickOn->SetVisable(true);
	m_pID_BUTTON_PickOff->SetVisable(false);
	m_autoFight.EndinPick();
	return true;
}


bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
    SetVisable(false);
	return true;
}

bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_StopOnButtonClick( ControlObject* pSender )
{
	if( !IsUILoad() )
		return false;

	MsgOfflineFightOpReq msg;
	msg.op = EOfflineFightOP_End;
	GettheNetworkInput().SendMsg( &msg );

	return true;
}

void CUI_ID_FRAME_AutoAttackSet::ID_EDIT_SkillHpOnEditEnter( ControlObject* pSender, const char* szData )
{

}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_HpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	std::string str = m_pID_EDIT_Hp->GetText();
	int nValue = atoi(str.c_str());

	m_autoFight.SetHp((*pbChecked),nValue);

	m_bSave = true;
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_MpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	std::string str = m_pID_EDIT_Mp->GetText();
	int nValue = atoi(str.c_str());

	m_autoFight.SetMp((*pbChecked),nValue);

	m_bSave = true;
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_TpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_autoFight.SetBackCityNoQuest((*pbChecked));

	m_bSave = true;
}

void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_BackOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{

}

void CUI_ID_FRAME_AutoAttackSet::ID_EDIT_BackHpOnEditEnter( ControlObject* pSender, const char* szData )
{
}

bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_RenovateOnButtonClick( ControlObject* pSender )
{
	theHeroGame.GetPlayerMgr()->UpdateMonsterType();
	SetUpdateUI(true);
	return true;
}
// Button
bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_AllOnButtonClick( ControlObject* pSender )
{
	int nSize = m_autoFight.GetMonsterSize();
	for(int i = 0;i < nSize;++i)
	{
		AutoFight::MonsterSetting *pSetting = m_autoFight.GetMonsterByIndex(i);
		if(!pSetting)
			continue;

		pSetting->bKill = true;
	}

	SetUpdateUI(true);
	return true;
}
// Button
bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_ReverseOnButtonClick( ControlObject* pSender )
{
	int nSize = m_autoFight.GetMonsterSize();
	for(int i = 0;i < nSize;++i)
	{
		AutoFight::MonsterSetting *pSetting = m_autoFight.GetMonsterByIndex(i);
		if(!pSetting)
			continue;

		pSetting->bKill = !pSetting->bKill;
	}
	SetUpdateUI(true);
	return true;
}
// List
void CUI_ID_FRAME_AutoAttackSet::ID_LIST_MonsterOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	AutoFight::MonsterSetting *pSetting = m_autoFight.GetMonsterByIndex(pItem->m_nID);
	if(!pSetting)
		return;

	pSetting->bKill = !pSetting->bKill;

	SetUpdateUI(true);
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_NormalOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_Normal->SetCheck(true);
	m_pID_CHECKBOX_Big->SetCheck(false);
	m_pID_CHECKBOX_Small->SetCheck(false);
	m_autoFight.SetAreaType(Area_Nomal);

	m_bSave = true;
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_BigOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_Normal->SetCheck(false);
	m_pID_CHECKBOX_Big->SetCheck(true);
	m_pID_CHECKBOX_Small->SetCheck(false);

	m_autoFight.SetAreaType(Area_Big);

	m_bSave = true;
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_SmallOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_Normal->SetCheck(false);
	m_pID_CHECKBOX_Big->SetCheck(false);
	m_pID_CHECKBOX_Small->SetCheck(true);

	m_autoFight.SetAreaType(Area_Small);

	m_bSave = true;
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_Team1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(*pbChecked)
		m_autoFight.AddTeamFlag(Team_AcceptInvite);
	else
		m_autoFight.RemoveTeamFlag(Team_AcceptInvite);

	m_bSave = true;
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_Team2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(*pbChecked)
		m_autoFight.AddTeamFlag(Team_AcceptComein);
	else
		m_autoFight.RemoveTeamFlag(Team_AcceptComein);

	m_bSave = true;
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_Setting1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	ClearControlData();
	m_pID_CHECKBOX_Setting1->SetCheck(true);
	m_pID_CHECKBOX_Setting2->SetCheck(false);
	if(!m_autoFight.ReadData(0))
		SetDefaultData();
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_Setting2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	ClearControlData();
	m_pID_CHECKBOX_Setting1->SetCheck(false);
	m_pID_CHECKBOX_Setting2->SetCheck(true);
	if(!m_autoFight.ReadData(1))
		SetDefaultData();
}

// Button
bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender )
{
	//LoadConfig();
	////UpdateUIData();//zhuxincong 8.20 ������
	//return true;
	//ClearControlData();
	SetDefaultData();
	return  true;
}

bool CUI_ID_FRAME_AutoAttackSet::ID_BUTTON_SaveOnButtonClick( ControlObject* pSender )
{
	//if(m_pID_CHECKBOX_Setting1->IsChecked())
		m_autoFight.WriteData(0);
	
	//if(m_pID_CHECKBOX_Setting2->IsChecked())
		//m_autoFight.WriteData(1);

	return true;
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_EnergyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_autoFight.SetUseEnergy(*pbChecked);

	m_bSave = true;
}

// CheckBox
void CUI_ID_FRAME_AutoAttackSet::ID_CHECKBOX_TeamNeedOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(*pbChecked)
		m_autoFight.AddTeamFlag(Team_NeedItem);
	else
		m_autoFight.RemoveTeamFlag(Team_NeedItem);

	m_bSave = true;
}

bool CUI_ID_FRAME_AutoAttackSet::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\AutoAttackSet.MEUI", false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\AutoAttackSet.MEUI]ʧ��")
		return false;
	}
	return DoControlConnect();
}

bool CUI_ID_FRAME_AutoAttackSet::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_AutoAttackSet, s_CUI_ID_FRAME_AutoAttackSetOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_AutoAttackSet, s_CUI_ID_FRAME_AutoAttackSetOnFrameRender );
    theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_PickItem, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_PickItemOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_SUODING, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_SUODINGOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Advance, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_AdvanceOnCheckBoxCheck );
    theUiManager.OnEditEnter( ID_FRAME_AutoAttackSet, ID_EDIT_Hp, s_CUI_ID_FRAME_AutoAttackSetID_EDIT_HpOnEditEnter );
    theUiManager.OnIconDragOn( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillAttack, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillAttackOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillAttack, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillAttackOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillAttack, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillAttackOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillAttack, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillAttackOnIconRButtonUp );
    theUiManager.OnEditEnter( ID_FRAME_AutoAttackSet, ID_EDIT_Mp, s_CUI_ID_FRAME_AutoAttackSetID_EDIT_MpOnEditEnter );
    theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_AutoAttack, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_AutoAttackOnCheckBoxCheck );
    theUiManager.OnIconDragOn( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillBuff, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillBuffOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillBuff, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillBuffOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillBuff, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillBuffOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillBuff, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillBuffOnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_AutoAttackSet, ID_LISTIMG_Hp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_HpOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_Hp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_HpOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_Hp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_HpOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_AutoAttackSet, ID_LISTIMG_Hp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_HpOnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_AutoAttackSet, ID_LISTIMG_Mp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_MpOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_Mp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_MpOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_Mp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_MpOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_AutoAttackSet, ID_LISTIMG_Mp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_MpOnIconRButtonUp );
    theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_Begin, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_BeginOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_ProtectionBegin, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_ProtectionBeginOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_ProtectionStop, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_ProtectionStopOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_PickOn, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_PickOnOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_PickOff, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_PickOffOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_Cancel, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_CancelOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_Stop, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_StopOnButtonClick );
    theUiManager.OnEditEnter( ID_FRAME_AutoAttackSet, ID_EDIT_SkillHp, s_CUI_ID_FRAME_AutoAttackSetID_EDIT_SkillHpOnEditEnter );
	theUiManager.OnIconDragOn( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillHpOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillHpOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillHpOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHp, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillHpOnIconRButtonUp );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Hp, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_HpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Mp, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_MpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Tp, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_TpOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Back, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_BackOnCheckBoxCheck );
	theUiManager.OnEditEnter( ID_FRAME_AutoAttackSet, ID_EDIT_Hp, s_CUI_ID_FRAME_AutoAttackSetID_EDIT_HpOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_AutoAttackSet, ID_EDIT_Mp, s_CUI_ID_FRAME_AutoAttackSetID_EDIT_MpOnEditEnter );
    theUiManager.OnEditEnter( ID_FRAME_AutoAttackSet, ID_EDIT_BackHp, s_CUI_ID_FRAME_AutoAttackSetID_EDIT_BackHpOnEditEnter );
    theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_Renovate, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_RenovateOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_All, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_AllOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_Reverse, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_ReverseOnButtonClick );
    theUiManager.OnListSelectChange( ID_FRAME_AutoAttackSet, ID_LIST_Monster, s_CUI_ID_FRAME_AutoAttackSetID_LIST_MonsterOnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Normal, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_NormalOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Big, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_BigOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Small, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_SmallOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Team1, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_Team1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Team2, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_Team2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Setting1, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_Setting1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Setting2, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_Setting2OnCheckBoxCheck );
    theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_Default, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_DefaultOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_AutoAttackSet, ID_BUTTON_Save, s_CUI_ID_FRAME_AutoAttackSetID_BUTTON_SaveOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Energy, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_EnergyOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_TeamNeed, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_TeamNeedOnCheckBoxCheck );

	theUiManager.OnCheckBoxCheck( ID_FRAME_AutoAttackSet, ID_CHECKBOX_IsCheckHpTeam, s_CUI_ID_FRAME_AutoAttackSetID_CHECKBOX_IsCheckHpTeamOnCheckBoxCheck );
	theUiManager.OnIconDragOn( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpTeam, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillHpTeamOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpTeam, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillHpTeamOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpTeam, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillHpTeamOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpTeam, s_CUI_ID_FRAME_AutoAttackSetID_LISTIMG_SkillHpTeamOnIconRButtonUp );
	theUiManager.OnEditEnter( ID_FRAME_AutoAttackSet, ID_EDIT_TeamSkillHp, s_CUI_ID_FRAME_AutoAttackSetID_EDIT_TeamSkillHpOnEditEnter );

	m_pID_TEXT_TimeText = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_TimeText );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_Time );
	m_pID_CHECKBOX_Setting1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Setting1 );
	m_pID_CHECKBOX_Setting2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Setting2 );

	m_pID_FRAME_AutoAttackSet = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_AutoAttackSet );
// 		m_pID_TEXT_UseItemZ = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_UseItemZ );
	m_pID_CHECKBOX_PickItem = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_PickItem );
	m_pID_CHECKBOX_SUODING = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_SUODING);
// 		m_pID_TEXT_PickItemZ = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_PickItemZ );
	m_pID_CHECKBOX_Advance = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Advance );
// 		m_pID_TEXT_HpZ = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_HpZ );
	m_pID_EDIT_Hp = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_EDIT_Hp );
// 		m_pID_TEXT_HpZ2 = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_HpZ2 );
	m_pID_LISTIMG_SkillAttack = (ControlListImage*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillAttack );
// 		m_pID_TEXT_MpZ = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_MpZ );
	m_pID_EDIT_Mp = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_EDIT_Mp );
// 		m_pID_TEXT_MpZ2 = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_MpZ2 );
// 		m_pID_TEXT_AutoAttackZ = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_AutoAttackZ );
	m_pID_CHECKBOX_AutoAttack = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_AutoAttack );
// 		m_pID_TEXT_SkillAttackZ = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_SkillAttackZ );
// 		m_pID_TEXT_SkillBuffZ = (ControlText*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_TEXT_SkillBuffZ );
	m_pID_LISTIMG_SkillBuff = (ControlListImage*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillBuff );
	m_pID_LISTIMG_Hp = (ControlListImage*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_LISTIMG_Hp );
	m_pID_LISTIMG_Mp = (ControlListImage*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_LISTIMG_Mp );
	m_pID_BUTTON_Begin = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_Begin );		

	m_pID_BUTTON_ProtectionBegin = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_ProtectionBegin );
	m_pID_BUTTON_ProtectionStop = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_ProtectionStop );

	m_pID_BUTTON_PickOn = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_PickOn );
	m_pID_BUTTON_PickOff = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_PickOff );


	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_Cancel );
// 		m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_PICTURE_Title );
	m_pID_BUTTON_Stop = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_Stop );
	//m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_PICTURE_TitleWord );
	m_pID_EDIT_SkillHp = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_EDIT_SkillHp );
	m_pID_LISTIMG_SkillHp = (ControlListImage*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHp );
	m_pID_CHECKBOX_Hp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Hp );
	m_pID_CHECKBOX_Mp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Mp );
	m_pID_CHECKBOX_Tp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Tp );
	m_pID_EDIT_Hp = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_EDIT_Hp );
	m_pID_EDIT_Mp = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_EDIT_Mp );
	m_pID_BUTTON_Renovate = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_Renovate );
	m_pID_BUTTON_All = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_All );
	m_pID_BUTTON_Reverse = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_Reverse );
	m_pID_LIST_Monster = (ControlList*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_LIST_Monster );
	m_pID_CHECKBOX_Normal = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Normal );
	m_pID_CHECKBOX_Big = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Big );
	m_pID_CHECKBOX_Small = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Small );
	m_pID_CHECKBOX_Team1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Team1 );
	m_pID_CHECKBOX_Team2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Team2 );
	m_pID_BUTTON_Default = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_Default );
	m_pID_BUTTON_Save = (ControlButton*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_BUTTON_Save );
	m_pID_CHECKBOX_Energy = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_Energy );
	m_pID_CHECKBOX_TeamNeed = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_TeamNeed );

	m_pID_CHECKBOX_IsCheckHpTeam = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_CHECKBOX_IsCheckHpTeam );
	m_pID_EDIT_TeamSkillHp = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_EDIT_TeamSkillHp );
	m_pID_LISTIMG_SkillHpTeam = (ControlListImage*)theUiManager.FindControl( ID_FRAME_AutoAttackSet, ID_LISTIMG_SkillHpTeam );

	assert( m_pID_FRAME_AutoAttackSet );
// 		assert( m_pID_TEXT_UseItemZ );
	assert( m_pID_CHECKBOX_PickItem );
	assert( m_pID_CHECKBOX_SUODING );
//		assert( m_pID_TEXT_PickItemZ );
	assert( m_pID_CHECKBOX_Advance );
//		assert( m_pID_TEXT_HpZ );
	assert( m_pID_EDIT_Hp );
// 		assert( m_pID_TEXT_HpZ2 );
	assert( m_pID_LISTIMG_SkillAttack );
// 		assert( m_pID_TEXT_MpZ );
	assert( m_pID_EDIT_Mp );
// 		assert( m_pID_TEXT_MpZ2 );
// 		assert( m_pID_TEXT_AutoAttackZ );
	assert( m_pID_CHECKBOX_AutoAttack );
// 		assert( m_pID_TEXT_SkillAttackZ );
// 		assert( m_pID_TEXT_SkillBuffZ );
	assert( m_pID_LISTIMG_SkillBuff );
	assert( m_pID_LISTIMG_Hp );
	assert( m_pID_LISTIMG_Mp );
	assert( m_pID_BUTTON_Begin );

	assert( m_pID_BUTTON_ProtectionBegin);
	assert( m_pID_BUTTON_ProtectionStop);

	assert( m_pID_BUTTON_Cancel );
// 		assert( m_pID_PICTURE_Title );
	assert( m_pID_BUTTON_Stop );
	assert( m_pID_EDIT_SkillHp );
	//assert( m_pID_PICTURE_TitleWord );
	assert( m_pID_LISTIMG_SkillHp );
	assert( m_pID_CHECKBOX_Hp );
	assert( m_pID_CHECKBOX_Mp );
	assert( m_pID_CHECKBOX_Tp );
	assert( m_pID_EDIT_Hp );
	assert( m_pID_EDIT_Mp );
	assert( m_pID_BUTTON_Renovate );
	assert( m_pID_BUTTON_All );
	assert( m_pID_BUTTON_Reverse );
	assert( m_pID_LIST_Monster );
	assert( m_pID_CHECKBOX_Normal );
	assert( m_pID_CHECKBOX_Big );
	assert( m_pID_CHECKBOX_Small );
	assert( m_pID_CHECKBOX_Team1 );
	assert( m_pID_CHECKBOX_Team2 );
	assert( m_pID_CHECKBOX_Setting1 );
	assert( m_pID_CHECKBOX_Setting2 );
	assert( m_pID_BUTTON_Default );
	assert( m_pID_BUTTON_Save );
	assert( m_pID_TEXT_TimeText );
	assert( m_pID_TEXT_Time );
	assert( m_pID_CHECKBOX_Energy );
	assert( m_pID_CHECKBOX_TeamNeed );

	assert( m_pID_CHECKBOX_IsCheckHpTeam );
	assert( m_pID_EDIT_TeamSkillHp );
	assert( m_pID_LISTIMG_SkillHpTeam );

	m_pID_EDIT_SkillHp->SetTextChangedFun(EditDataChangeInHpSkill);
	m_pID_EDIT_Hp->SetTextChangedFun(EditDataChangeInHp);
	m_pID_EDIT_Mp->SetTextChangedFun(EditDataChangeInMp);
	m_pID_EDIT_TeamSkillHp->SetTextChangedFun(EditDataChangeInHpSkillTeam);

	m_pID_LIST_Monster->HaveSelBar(false);

    InitControl();

    SetVisable(false);

	return true;
}

// ж��UI
bool CUI_ID_FRAME_AutoAttackSet::_UnLoadUI()
{
    m_bUILoad = false;
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\AutoAttackSet.MEUI" );
}

// �Ƿ����
bool CUI_ID_FRAME_AutoAttackSet::_IsVisable()
{
	if( !m_pID_FRAME_AutoAttackSet )
		return false;
	return m_pID_FRAME_AutoAttackSet->IsVisable();
}

// �����Ƿ����
void CUI_ID_FRAME_AutoAttackSet::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_AutoAttackSet )
		return;
	m_pID_FRAME_AutoAttackSet->SetVisable( bVisable );
    if(bVisable/*&&!m_bUILoad*/) 
    {
		SetDefaultData();
		if(!m_autoFight.ReadData(0))
             SetDefaultData();
        m_bUILoad = true;
    }
}

void CUI_ID_FRAME_AutoAttackSet::ClearControlData()
{
	//�ͷż���
	m_pID_LISTIMG_SkillAttack->Clear(true);
	m_pID_LISTIMG_SkillBuff->Clear(true);
	m_pID_LISTIMG_SkillHp->Clear(true);
	m_pID_LISTIMG_SkillHpTeam->Clear(true);

	m_pID_LISTIMG_SkillAttack->SetDisableCanbePick(true);
	m_pID_LISTIMG_SkillAttack->ShowPressEffect(true);

	m_pID_LISTIMG_SkillBuff->SetDisableCanbePick(true);
	m_pID_LISTIMG_SkillBuff->ShowPressEffect(true);

	m_pID_LISTIMG_SkillHp->SetDisableCanbePick(true);
	m_pID_LISTIMG_SkillHp->ShowPressEffect(true);

	m_pID_LISTIMG_SkillHpTeam->SetDisableCanbePick(true);
	m_pID_LISTIMG_SkillHpTeam->ShowPressEffect(true);

	m_pID_EDIT_SkillHp->SetIsNumber(true);
	m_pID_EDIT_SkillHp->SetNumberLimit(true,0,100);
	m_pID_EDIT_SkillHp->SetText("0");

	//�Զ���ҩ����
	m_pID_CHECKBOX_Hp->SetCheck(false);
	m_pID_CHECKBOX_Mp->SetCheck(false);
	m_pID_CHECKBOX_Tp->SetCheck(false);
	m_pID_CHECKBOX_Energy->SetCheck(false);

	//Ѫ��������Ϊ0--100
	m_pID_EDIT_Hp->SetIsNumber(true);
	m_pID_EDIT_Hp->SetNumberLimit(true,0,100);
	m_pID_EDIT_Hp->SetText("0");

	m_pID_EDIT_Mp->SetIsNumber(true);
	m_pID_EDIT_Mp->SetNumberLimit(true,0,100);
	m_pID_EDIT_Mp->SetText("0");

	//�Զ��������
	m_pID_LIST_Monster->Clear(true);
	m_pID_CHECKBOX_Normal->SetCheck(false);
	m_pID_CHECKBOX_Big->SetCheck(false);
	m_pID_CHECKBOX_Small->SetCheck(false);

	//�Զ�ʰȡ����
	m_pID_CHECKBOX_PickItem->SetCheck(false);
	
	//��������
	m_pID_CHECKBOX_SUODING->SetCheck(false);

	//�������
	m_pID_CHECKBOX_Team1->SetCheck(false);
	m_pID_CHECKBOX_Team2->SetCheck(false);

	//ʱ������
	m_pID_TEXT_Time->SetText("0");

	m_pID_CHECKBOX_Advance->SetCheck(true);
	m_pID_CHECKBOX_AutoAttack->SetCheck(true);
	m_pID_LISTIMG_Hp->Clear(true);
	m_pID_LISTIMG_Mp->Clear(true);


	m_pID_LISTIMG_Hp->SetDisableCanbePick(true);
	m_pID_LISTIMG_Hp->ShowPressEffect(true);

	m_pID_LISTIMG_Mp->SetDisableCanbePick(true);
	m_pID_LISTIMG_Mp->ShowPressEffect(true);

	m_pID_CHECKBOX_Energy->SetCheck(false);
	m_pID_CHECKBOX_TeamNeed->SetCheck(false);

	m_pID_CHECKBOX_IsCheckHpTeam->SetCheck(false);
	m_pID_EDIT_TeamSkillHp->SetIsNumber(true);
	m_pID_EDIT_TeamSkillHp->SetNumberLimit(true,0,100);
	m_pID_EDIT_TeamSkillHp->SetText("0");
	//OnCheckTeamHpSkill(false);
}

void CUI_ID_FRAME_AutoAttackSet::InitControl()
{
	ClearControlData();

	m_pID_BUTTON_Begin->SetVisable(true);
    m_pID_BUTTON_Stop->SetVisable(false);

	m_pID_BUTTON_ProtectionBegin->SetVisable(true);
	m_pID_BUTTON_ProtectionStop->SetVisable(false);

	m_pID_BUTTON_PickOn->SetVisable(true);
	m_pID_BUTTON_PickOff->SetVisable(false);

	m_pID_CHECKBOX_Setting1->SetCheck(true);
	m_pID_CHECKBOX_Setting2->SetCheck(false);

    m_bSave = false;
}

    
void CUI_ID_FRAME_AutoAttackSet::SetAttackSkill(int nIndex,unsigned short skillId)
{
    SCharSkill *pCharSkill = NULL;
    pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(skillId);
    if ( !pCharSkill ||pCharSkill->ustSkillID == InvalidLogicNumber)
	{
		m_autoFight.SetAttackSkill(NULL,nIndex);
        return;
	}

    ItemDefine::SItemSkill* pSkill = NULL; 
    pSkill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID, pCharSkill->stSkillLevel);
    m_autoFight.SetAttackSkill(pSkill,nIndex);
}

void CUI_ID_FRAME_AutoAttackSet::SetBufSkill(int nIndex,unsigned short skillId)
{
    SCharSkill *pCharSkill = NULL;
    pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(skillId);
    if ( !pCharSkill ||pCharSkill->ustSkillID == InvalidLogicNumber)
	{
		m_autoFight.SetBufSkill(NULL,nIndex);
        return;
	}

    ItemDefine::SItemSkill* pSkill = NULL;
    pSkill = GettheItemDetail().GetSkillByID(pCharSkill->ustSkillID,pCharSkill->stSkillLevel);
    m_autoFight.SetBufSkill(pSkill,nIndex);
}

void CUI_ID_FRAME_AutoAttackSet::SetHpSkill(int nIndex,unsigned short skillId)
{
	SCharSkill *pCharSkill = NULL;
	pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(skillId);
	if ( !pCharSkill ||pCharSkill->ustSkillID == InvalidLogicNumber)
	{
		m_autoFight.SetRecSkill(NULL,nIndex,0);
		return;
	}

	ItemDefine::SItemSkill* pSkill = NULL;
	pSkill = GettheItemDetail().GetSkillByID(pCharSkill->ustSkillID,pCharSkill->stSkillLevel);

	std::string str = m_pID_EDIT_SkillHp->GetText();
	int nNum = atoi(str.c_str());
	m_autoFight.SetRecSkill(pSkill,nIndex,nNum);
}
void CUI_ID_FRAME_AutoAttackSet::SetHpTeamSkill(int nIndex,unsigned short skillId)
{
	SCharSkill *pCharSkill = NULL;
	pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(skillId);
	if ( !pCharSkill ||pCharSkill->ustSkillID == InvalidLogicNumber)
	{
		m_autoFight.SetRecTeamSkill(NULL,nIndex,0);
		return;
	}

	ItemDefine::SItemSkill* pSkill = NULL;
	pSkill = GettheItemDetail().GetSkillByID(pCharSkill->ustSkillID,pCharSkill->stSkillLevel);

	std::string str = m_pID_EDIT_TeamSkillHp->GetText();
	int nNum = atoi(str.c_str());
	m_autoFight.SetRecTeamSkill(pSkill,nIndex,nNum);
}
void CUI_ID_FRAME_AutoAttackSet::UpdateCD(const int id,ControlListImage* pImg,int nIndex /*= 0*/)
{
    if(!pImg || pImg->GetItemCnt() <= nIndex)
        return;

	SkillBag::SColdTime *pTime = thePlayerRole.m_SkillBag.GetColdTimeById(id);
	if (pTime)
	{
		ControlIconDrag::S_ListImg* pImgItem = NULL;
		ControlIconDrag::S_ListImg stImgItem;

		pImgItem = pImg->GetItemByIndex(nIndex);
		if (!pImgItem)
			return;
		
		stImgItem = *pImgItem;
		stImgItem.SetTime(pTime->dwColdStartTime, pTime->dwColdTime);
		pImg->SetItem(&stImgItem,nIndex);

// 			stItem.SetTime(pTime->dwColdStartTime, pTime->dwColdTime);
// 			m_skillTrees[i]->SetItem(&stItem, 0);
	}

//         RestoreColdDown* pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
//         DWORD dwStartTime,dwPeriod;
//         if ( pRestoreCoolDown->GetTime( id, &dwStartTime, &dwPeriod ) )
//             pImg->GetItemByIndex(nIndex)->SetTime(dwStartTime,dwPeriod);
}


void CUI_ID_FRAME_AutoAttackSet::SetFightState()
{
    m_autoFight.BeginFight();  //��ʼ�һ�

    //���ð뾶��λ��
	if( theHeroGame.GetPlayerMgr()->GetMe() )
	{
// 			AreaState eType = Area_Nomal;
// 			float fDis = 20.0f;
// 
// 			if(m_pID_CHECKBOX_Normal->IsChecked())
// 			{
// 				eType = Area_Nomal;
// 				fDis = 20.0f;
// 			}
// 
// 			if(m_pID_CHECKBOX_Big->IsChecked())
// 			{
// 				eType = Area_Big;
// 				fDis = 25.0f;
// 			}
// 
// 			if(m_pID_CHECKBOX_Small->IsChecked())
// 			{
// 				eType = Area_Small;
// 				fDis = 15.0f;
// 			}
		
		m_autoFight.SetPos(theHeroGame.GetPlayerMgr()->GetMe()->GetPos());
	}
    
	m_autoFight.Init();
	m_autoFight.UseAttackSkill();
}

void CUI_ID_FRAME_AutoAttackSet::RefreshQuestUI()
{
	if(!m_pID_FRAME_AutoAttackSet)
		return;

	if(!s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag))
		return;

    ControlIconDrag::S_ListImg *pImg = NULL;
	m_pID_EDIT_Hp->SetText(m_autoFight.m_actHp.nLimitPer);
	m_pID_EDIT_Mp->SetText(m_autoFight.m_actMp.nLimitPer);

	m_pID_CHECKBOX_Hp->SetCheck(m_autoFight.m_actHp.bDo);
	m_pID_CHECKBOX_Mp->SetCheck(m_autoFight.m_actMp.bDo);
	m_pID_CHECKBOX_Tp->SetCheck(m_autoFight.m_actBackCityNoQuest.bDo);
	m_pID_CHECKBOX_Energy->SetCheck(m_autoFight.m_actUseEnergy.bDo);

	//lyh++ ˢ��ҩƷlistimg

	
	ControlIconDrag::S_ListImg _temp;
	if (m_autoFight.m_HpItemId!=0)
	{
		eIconDrawState itemIconState = thePlayerRole.m_bag.GetItemIndexById(m_autoFight.m_HpItemId) == -1? eIcon_Disable : eIcon_Enable;
	_temp.SetData( m_autoFight.m_HpItemId,1,itemIconState );
	m_pID_LISTIMG_Hp->SetItem(&_temp,0);
	}

	if (m_autoFight.m_MpItemId!=0)
	{
		eIconDrawState itemIconState = thePlayerRole.m_bag.GetItemIndexById(m_autoFight.m_MpItemId) == -1? eIcon_Disable : eIcon_Enable;
		_temp.SetData( m_autoFight.m_MpItemId,1,itemIconState );
		m_pID_LISTIMG_Mp->SetItem(&_temp,0);
	}

}

void CUI_ID_FRAME_AutoAttackSet::RefreshSkillUI(bool bUpdate)
{
	if( !m_pID_FRAME_AutoAttackSet )
		return;

    CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
        GetPage(CUISkillMgr::eProfession);
    if (!pSkillTree)
        return;

    SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

    //���ü���
    for (int i = 0;i < USEMAXSKILL;++i)
    {
        ItemDefine::SItemSkill* pItem = m_autoFight.GetAttackSkill(i);
        if(pItem)   
            RefreshSkillImageUI(pItem,m_pID_LISTIMG_SkillAttack,i,bUpdate);

        pItem = m_autoFight.GetBufSkill(i);
        if(pItem)
            RefreshSkillImageUI(pItem,m_pID_LISTIMG_SkillBuff,i,bUpdate);

		pItem = m_autoFight.GetRecSkill(i);
		if(pItem)
			RefreshSkillImageUI(pItem,m_pID_LISTIMG_SkillHp,i,bUpdate);

		pItem = m_autoFight.GetRecTeamSkill(i);
		if(pItem)
			RefreshSkillImageUI(pItem,m_pID_LISTIMG_SkillHpTeam,i,bUpdate);
    }

	m_pID_EDIT_SkillHp->SetText(m_autoFight.GetRecHpPer());
	m_pID_EDIT_TeamSkillHp->SetText(m_autoFight.GetRecHpTeamPer());
}

void CUI_ID_FRAME_AutoAttackSet::RefreshSkillImageUI(ItemDefine::SItemSkill* pItemSkill,ControlListImage* pImage,int nIndex,bool bUpdate)
{
    if(!pItemSkill || !pImage)
        return;

    CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
        GetPage(CUISkillMgr::eProfession);
    if (!pSkillTree)
        return;

    SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

    unsigned short usID = pItemSkill->ustItemID;

    //���ü���
    SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(usID);
    if(!pSkill)
        return;

    ControlIconDrag::S_ListImg stItem;
    const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue(pSkill->ustSkillID);
    if(pIcon)
         stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image,pIcon->iconSize,pIcon->row,pIcon->column);

    stItem.SetData(pSkill->ustSkillID,pSkill->stSkillLevel,pSkill->bAvailable? eIcon_Enable: eIcon_Disable, 0, eTipFlag_SkillNoNextLevel);

    SkillBag::SColdTime *pColdTime = NULL;
    pColdTime = thePlayerRole.m_SkillBag.GetColdTimeById(usID);
    if(pColdTime)
        stItem.SetTime(pColdTime->dwColdStartTime,pColdTime->dwColdTime);

    pImage->SetItem(&stItem,nIndex);

    //ͬ������   
    if(bUpdate)
        pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
    
} 
void CUI_ID_FRAME_AutoAttackSet::RefreshMonsterUI()
{
	if(!m_pID_FRAME_AutoAttackSet)
		return;

	m_pID_LIST_Monster->Clear();
	int nSize = m_autoFight.GetMonsterSize();
	for(int i = 0;i < nSize;++i)
	{
		AutoFight::MonsterSetting *pSetting = m_autoFight.GetMonsterByIndex(i);
		if(!pSetting)
			continue;

		ItemDefine::SMonster *pMonster = GettheItemDetail().GetMonsterById(pSetting->nMonsterId);
		if(!pMonster)
			continue;

		char szWord[256] = {0};
		if(pSetting->bKill)
			MeSprintf_s(szWord,sizeof(szWord),"%s %s(%d)","[��ѡ]",pMonster->GetName(),pMonster->stLevel);
		else
			MeSprintf_s(szWord,sizeof(szWord),"%s %s(%d)","[δѡ]",pMonster->GetName(),pMonster->stLevel);

		ControlList::S_List stItem;
		stItem.SetData(szWord,i);

		m_pID_LIST_Monster->AddItem(&stItem);
	}
}
void CUI_ID_FRAME_AutoAttackSet::RefreshAreaUI()
{
	if(!m_pID_FRAME_AutoAttackSet)
		return;

	m_pID_CHECKBOX_Normal->SetCheck(false);
	m_pID_CHECKBOX_Big->SetCheck(false);
	m_pID_CHECKBOX_Small->SetCheck(false);
	switch(m_autoFight.GetZoneType())
	{
	case Area_Nomal:
		m_pID_CHECKBOX_Normal->SetCheck(true);			
		break;
	case Area_Big:
		m_pID_CHECKBOX_Big->SetCheck(true);
		break;
	case Area_Small:
		m_pID_CHECKBOX_Small->SetCheck(true);
		break;
	}
}
	
void CUI_ID_FRAME_AutoAttackSet::RefreshPickUI()
{
	if(!m_pID_FRAME_AutoAttackSet)
		return;

	m_pID_CHECKBOX_PickItem->SetCheck(m_autoFight.IsPickFlag(Pick_All));
}

void CUI_ID_FRAME_AutoAttackSet::RefershSuoDingUI()
{
	if (!m_pID_FRAME_AutoAttackSet)
		return;

	m_pID_CHECKBOX_SUODING->SetCheck(m_autoFight.IsSuoDingFlag(SuoDing_All));
}

void CUI_ID_FRAME_AutoAttackSet::RefershTeamUI()
{
	if(!m_pID_FRAME_AutoAttackSet)
		return;

	m_pID_CHECKBOX_Team1->SetCheck(m_autoFight.IsTeamFlag(Team_AcceptInvite));
	m_pID_CHECKBOX_Team2->SetCheck(m_autoFight.IsTeamFlag(Team_AcceptComein));
	m_pID_CHECKBOX_TeamNeed->SetCheck(m_autoFight.IsTeamFlag(Team_NeedItem));
}
	
unsigned int CUI_ID_FRAME_AutoAttackSet::SearchQuse(bool IsAddHp/* = true*/)
{
    unsigned int nQuseID = ErrorUnsignedShortID;
    int nSize = thePlayerRole.m_bag.GetNowBagSize();
    for(int nCount = 0;nCount < nSize;++nCount)
    {
        SCharItem sCItem;
        if(!thePlayerRole.m_bag.GetItem(nCount,&sCItem))
            continue;

        if(sCItem.storageinfo.bIsLocked)
            continue;

        ItemDefine::SItemCommon *pItemCommon = NULL;
        pItemCommon = GettheItemDetail().GetItemByID( sCItem.itembaseinfo.ustItemID);
        if( !pItemCommon )
            continue;

        if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_RESTORE)
            continue;
        
        ItemDefine::SItemRestore *pItemRestore;
        pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;

        if(IsAddHp)
        {
          if(pItemRestore->dwAddHP <= 0)
             continue;
        }
        else
        {
            if(pItemRestore->dwAddMP <= 0)
                continue;
        }

        if(nQuseID == ErrorUnsignedShortID || sCItem.itembaseinfo.ustItemID > nQuseID)
            nQuseID = sCItem.itembaseinfo.ustItemID;
    }

    return nQuseID;
}

void CUI_ID_FRAME_AutoAttackSet::SetDefaultData()
{
	ClearControlData();
    LoadConfig();
}

void CUI_ID_FRAME_AutoAttackSet::LoadConfig()
{
	m_autoFight.LoadDefaultData();
}

void CUI_ID_FRAME_AutoAttackSet::EditDataChangeInHpSkill( OUT ControlObject* pSender, OUT const char *szData )
{
	if(strlen(szData) > 0)
	{
		int nValue = atoi(szData);
		s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().SetRecSkillLimit(nValue);
		s_CUI_ID_FRAME_AutoAttackSet.m_bSave = true;
	}
}
void CUI_ID_FRAME_AutoAttackSet::EditDataChangeInHpSkillTeam( OUT ControlObject* pSender, OUT const char *szData )
{
	if(strlen(szData) > 0)
	{
		int nValue = atoi(szData);
		s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().SetRecTeamSkillLimit(nValue);
		s_CUI_ID_FRAME_AutoAttackSet.m_bSave = true;
	}
}
void CUI_ID_FRAME_AutoAttackSet::EditDataChangeInHp( OUT ControlObject* pSender, OUT const char *szData )
{
	if(strlen(szData) > 0)
	{
		int nValue = atoi(szData);
		s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().SetHpLimit(nValue);
		s_CUI_ID_FRAME_AutoAttackSet.m_bSave = true;
	}
}

void CUI_ID_FRAME_AutoAttackSet::EditDataChangeInMp( OUT ControlObject* pSender, OUT const char *szData )
{
	if(strlen(szData) > 0)
	{
		int nValue = atoi(szData);
		s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().SetMpLimit(nValue);
		s_CUI_ID_FRAME_AutoAttackSet.m_bSave = true;
	}
}

void CUI_ID_FRAME_AutoAttackSet::UpdateUIData()
{
	if(!m_bUpdateUI)
		return;

	m_bUpdateUI = false;
	RefreshSkillUI(true);  
	RefreshQuestUI();
	RefreshMonsterUI();
	RefreshAreaUI();
	RefreshPickUI();
	RefershTeamUI();
	RefershSuoDingUI();

	OnCheckTeamHpSkill(m_autoFight.GetIsNeedHpSkillTeam());
}


bool CUI_ID_FRAME_AutoAttackSet::FindBeRecordItem(GameObjectId id)
{
	if (m_PickedItemServerId.size() == 0)
	{
		return false;
	}

   for (int i = 0 ; i < m_PickedItemServerId.size() ; i++)
   {
	   if (id == m_PickedItemServerId[i])
	   {
		   return true;
	   }
   }

	return false;
}
//lyh����ҹһ�
void CUI_ID_FRAME_AutoAttackSet::ReMoveRecordItem(GameObjectId id)
{
	if (m_PickedItemServerId.size() == 0)
		return;

	std::vector<GameObjectId>::iterator it = m_PickedItemServerId.begin();

	for (; it != m_PickedItemServerId.end() ; it++)
	{
		if (id == *it)
		{
			m_PickedItemServerId.erase(it);
			break;
		}
	}


}
void CUI_ID_FRAME_AutoAttackSet::OnCheckTeamHpSkill(bool IsCheck)
{
	//�����ѡ�����ȡ��������Ѫ���ܵ�ʱ��
	if(!m_pID_FRAME_AutoAttackSet)
		return;
	//�жϵ�ǰ��ҵ�ְҵ �Ƿ�Ϊ��ְҵ �ǵĻ� ���Կ��� ���ǵĻ� �ر�
	if(IsCheck)
	{
		if(thePlayerRole.GetProfession() != EArmType_Hunter)
		{
			//��ʾ��� ����ְҵ�������л�Ϊ����ģʽ
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_AutoAttack_OpenTeam_Profession));
			IsCheck = false;
		}
	}
	m_pID_LISTIMG_SkillAttack->SetEnable(!IsCheck);
	m_pID_LISTIMG_SkillHp->SetEnable(!IsCheck);
	m_pID_EDIT_SkillHp->SetEnable(!IsCheck);

	m_pID_EDIT_TeamSkillHp->SetEnable(IsCheck);
	m_pID_LISTIMG_SkillHpTeam->SetEnable(IsCheck);
	m_pID_EDIT_TeamSkillHp->SetText( m_autoFight.GetRecHpTeamPer());
	m_autoFight.SetIsNeedHpSkillTeam(IsCheck);
	if(m_pID_CHECKBOX_IsCheckHpTeam->IsChecked() != IsCheck)
		m_pID_CHECKBOX_IsCheckHpTeam->SetCheck(IsCheck);
}
AutoFight::AutoFight()
{
   m_enum = Enum_Pick;

   m_WaitBeginTime = 0;
//        m_bAutoRecover = false;   //�Զ��ָ�
//        m_bAutoPick = false;      //�Զ�ʰȡ
//        m_bAutoFight = false;     //�Զ����

   m_dwElapseTime = 1000;  //Ĭ����Ϣʱ��Ϊ1��

   m_dwSendMsgTime = 0;

   m_MonsSetting.clear();

   m_HpItemId = 0;
   m_MpItemId = 0;
  m_OutPutFindHP = false;
  m_OutPutFindMP = false;

	m_dwPickState = 0;     //ʰȡ״̬ 
	m_dwTeamState  = 0;   //���״̬
	m_dwSuoDingState = 0;
	m_dwProtection = 0;
	m_vecArea.clear();

	m_IsNeedHpSkillTeam = false;

}

AutoFight::~AutoFight()
{

}

void AutoFight::ProcessRecover()
{
	//��ҩ
	if(IsUseHpQuest())
	{
		//ʧ���˿���û����Ʒ,������CD����
		int nIndex = SearchQuestIndex();
		if(nIndex != -1)
		{
			SCharItem sCharItem;
			if(thePlayerRole.m_bag.GetItem(nIndex,&sCharItem))
				s_CUI_ID_FRAME_PACK.UseItem(sCharItem.itembaseinfo.ustItemID,nIndex);
		}
	}

	//��ҩ
	if (IsUseMpQuset())
	{
		int nIndex = SearchQuestIndex(false);
		if(nIndex != -1)
		{
			SCharItem sCharItem;
			if(thePlayerRole.m_bag.GetItem(nIndex,&sCharItem))
		          s_CUI_ID_FRAME_PACK.UseItem(sCharItem.itembaseinfo.ustItemID,nIndex);  //ʹ����ҩ
		}
	}

	//ûҩƷ�س�
	if(IsBackCityNoQuest())
	{
		CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->GetMe();
		if(pPlayer&&!pPlayer->HasFightFlag(eFighting))
		{
			if(!thePlayerRole.m_SkillBag.IsSkillCoolDownById(CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID))
			{
				s_CUI_ID_FRAME_ActionUI.SetCurFunction( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK );
				s_CUI_ID_FRAME_ActionUI.UseFunction();
				s_CUI_ID_FRAME_AutoAttackSet.ID_BUTTON_StopOnButtonClick(NULL);
			}

			if(!thePlayerRole.m_SkillBag.IsSkillCoolDownById(CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID2))
			{
				s_CUI_ID_FRAME_ActionUI.SetCurFunction( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK2 );
				s_CUI_ID_FRAME_ActionUI.UseFunction();
				s_CUI_ID_FRAME_AutoAttackSet.ID_BUTTON_StopOnButtonClick(NULL);
			}
		}
	}

	//�Ƿ�ʹ�þ�����
	if(IsUseEnergy())
	{
		int nValue = thePlayerRole.GetData(CPlayerRole::TYPE_VIGOR);
		if(nValue <= 0)
		{
			//thePlayerRole.m_bag.GetItemIndexById();
			
		}
	}
}


//ʰȡ�͹����ǲ��ܹ���ģ������Ҫ����,�����������ܳ��֣������ܵ����
//���ݲ߻���������Ҫ��ʰȡ���ȼ�����빥���ֵ�


//ʰȡ��Ʒ�Ĺ��̣�����ѡ��Ŀ�꣬Ȼ���ܣ�֮��ʰȡ.�رս���
void AutoFight::ProcessPick()
{
    if(!m_dwPickState)
        SetState(Enum_Attack);
     
	//if(thePlayerRole.m_TeamData.size() > 0 && (thePlayerRole.GetAssignMode() != AssignMode_FreeMode || !IsTeamFlag(Team_NeedItem)))
	//	SetState(Enum_Attack);

    if(m_enum != Enum_Pick)
        return;

     //����������ˣ���ʾ��Ϣ
    //if(thePlayerRole.m_bagMaterial.GetNullItemCount() <= 0)
	int index = -1;
	if( s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag) )
		index = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag)->GetNullItem();
	if (index == -1 || index >= thePlayerRole.m_bag.GetNowBagSize())
    {
          CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString( eText_NormalPackFull ) );
          SetState(Enum_Attack);
          if(s_CUI_ID_FRAME_PickUp.IsVisable())
              s_CUI_ID_FRAME_PickUp.SetVisable(false);
          return;
    }

    if(s_CUI_ID_FRAME_PickUp.IsVisable())
    {
        s_CUI_ID_FRAME_PickUp.ID_BUTTON_PickAllOnButtonClick(NULL); //��һ����ȫ��ʰȡ
        EnterWait(2000);  //����ȴ�״̬,��Ϊ��Ҫ����������,��Ȼ���ܲ�ͣ����Ϣ
		s_CUI_ID_FRAME_PickUp.SetVisable(false);
        return;
    }

    //������ڴ��,�������
    int lockId = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
    CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(lockId);
    if(pPlayer != NULL)
    {
        if(pPlayer->IsMonster()&&!pPlayer->IsDead())
        {
            SetState(Enum_Attack);
            return;
        }
    }

    if(IsHaveItem())  //�а���,��ʰȡ����
    {
        if(!g_bTheRoleMoveToTargetPos)
        {
            s_CUI_ID_FRAME_ActionUI.SetCurFunction(CUI_ID_FRAME_BaseProperty::TYPE_PICK_ACTION);
            s_CUI_ID_FRAME_ActionUI.UsePick();    //��һ����ȥ�鿴����                                   
        }
    }
    else
        SetState(Enum_Attack);
    
   return;
}

	/*
	 *	Author 2012-9-24 zhuxincong
	 *	DESC: ProcessAutoPick() ����ӿ����ṩ���ǹһ�״̬�µ��Զ�ʰȡ��
	 */
void AutoFight::ProcessAutoPick()
{
	if (m_bPick)
	{
		if(IsHaveItem())  //�а���,��ʰȡ����
		{
			if(!g_bTheRoleMoveToTargetPos)
			{
				s_CUI_ID_FRAME_ActionUI.SetCurFunction(CUI_ID_FRAME_BaseProperty::TYPE_PICK_ACTION);
				s_CUI_ID_FRAME_ActionUI.UsePick();                                      
			}
		}
	}
	return ;
}

void AutoFight::ProcessAttack()
{
    //����һ֡����ֻ����һ������
    //����ʹ�ø�������
//         if(!m_bAutoFight)
//              return;

    if(m_enum != Enum_Attack)
        return;
	if(m_IsNeedHpSkillTeam)
	{
		UseHpSkillInTeam();
	}
	else
	{
		UseAttackSkill();
		UseHpSkill();
	}
	UseBufSkill();
    return;
}

void AutoFight::Process()
{
    //�Ƿ��Զ��һ���
    if(!m_bAuto)
        return;

    if(!theHeroGame.GetPlayerMgr()->GetMe())
        return;

    if(theHeroGame.GetPlayerMgr()->GetMe()->IsDead())
    {
        m_bAuto = false;
        return;
    }


	//5�����Զ��ؿ�һ�ιһ�
	long CurTime = timeGetTime();

	if (s_CUI_ID_FRAME_AutoAttackSet.BeginAutoAttackTime != 0)
	{
		if (CurTime - s_CUI_ID_FRAME_AutoAttackSet.BeginAutoAttackTime >= 1000 * 60 * 5)
		{
			Init();
			UseAttackSkill();
			s_CUI_ID_FRAME_AutoAttackSet.BeginAutoAttackTime = CurTime;
			return;
		}
	}




    //RandMove();
    ProcessRecover();
#ifdef _DEBUG
    DebugInfo();
#endif

    if(ProcessWait())
        return;
    
    if(theHeroGame.GetPlayerMgr()->GetMe()->IsIntonation())
        return;
    ProcessPick();
    ProcessAttack();
}

bool AutoFight::ProcessWait()
{
    if(m_enum != Enum_Wait)
        return false;
    
    if(GetTickCount() - m_WaitBeginTime > m_dwElapseTime)
    {
        m_WaitBeginTime = 0;
        SetState(Enum_Pick);
        return false;
    }
    return true;
}

void AutoFight::ProcessTeam(Msg *pMsg)
{
	bool bAgree = false;
	if(IsTeamFlag(Team_AcceptInvite)
		||(thePlayerRole.IsManipleHeader()&&IsTeamFlag(Team_AcceptComein)))
		bAgree = true;

	MsgInquireInvitee * pMsgInquireInvitee = (MsgInquireInvitee *)pMsg;
	MsgAckInquireInvitee msg;
	if(bAgree)
	   msg.bAgree = MsgAckInquireInvitee::result_agree;
	else
	   msg.bAgree = MsgAckInquireInvitee::result_nonAgree;

	msg.dwReqID = pMsgInquireInvitee->dwReqID;
	msg.AssignMode = pMsgInquireInvitee->AssignMode;
	msg.AssignItemLevel = pMsgInquireInvitee->AssignItemLevel;
	GettheNetworkInput().SendMsg(&msg);
}

void AutoFight::ProcessTeamAssign(Msg *pMsg)
{

}

void  AutoFight::SetPos(D3DXVECTOR3& pos)
{
    m_AttackZone.m_pos = pos;
}

void  AutoFight::SetAreaType(AreaState eValue)
{
	m_AttackZone.m_eAreaState = eValue;
	m_AttackZone.m_Radius = GetAreaSetting(eValue);
// 		switch(eValue)
// 		{
// 		case Area_Nomal:
// 			m_AttackZone.m_Radius = 20;
// 			break;
// 		case Area_Big:
// 			m_AttackZone.m_Radius = 30;
// 			break;
// 		case Area_Small:
// 			m_AttackZone.m_Radius = 15;
// 			break;
// 		}
}

bool  AutoFight::IsInZone(float x,float y)
{
	float xOff = x - m_AttackZone.m_pos.x;
	float yOff = y - m_AttackZone.m_pos.y;
	float fDist = sqrtf(xOff * xOff + yOff * yOff);

	if(fDist < m_AttackZone.m_Radius)
		return true;

	return false;
}

#ifdef _DEBUG
void AutoFight::DebugInfo()
{
// 		if(!m_bAuto)
// 			return;

	//��������
	GetDrawer()->DrawCircle3D(m_AttackZone.m_pos.x,m_AttackZone.m_pos.y,m_AttackZone.m_pos.z,m_AttackZone.m_Radius,20,0xffff0000);


	FontRender::EFontRenders eOldIdx = FontRender::EFR_FIRST;
	if( FontSystem::IsUseNewFont() )
	{
		eOldIdx = FontRender::getFontRender()->GetDefaultRendererIdx();
		FontRender::getFontRender()->SetDefaultRendererIdx( FontRender::EFR_THIRD );
		FontSystem::ClearRender( FontRender::EFR_THIRD );
	}

	DWORD dwFtColor = 0xffff0000;

	RECT fontRect;
	fontRect.left = 300;
	fontRect.top  = 150;
	fontRect.right = fontRect.left + 100;
	fontRect.bottom = fontRect.right + 60;

	char szWord[512];
	ZeroMemory(szWord,sizeof(szWord));
	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"��ҩ����Ϊ: %s %%d ",m_actHp.bDo?"��":"��",m_actHp.nLimitPer);
	FontSystem::DrawTextDirect(szWord,&fontRect,DT_NOCLIP,dwFtColor,0,true);

	fontRect.left = 300;
	fontRect.top  = 150 + 18;
	fontRect.right = fontRect.left + 100;
	fontRect.bottom = fontRect.right + 60;

	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"��ҩ����Ϊ: %s %%d ",m_actMp.bDo?"��":"��",m_actMp.nLimitPer);
	FontSystem::DrawTextDirect(szWord,&fontRect,DT_NOCLIP,dwFtColor,0,true);

	fontRect.left = 300;
	fontRect.top  = 150 + 18 * 2;
	fontRect.right = fontRect.left + 100;
	fontRect.bottom = fontRect.right + 60;

	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"��ҩ�س�: %s ",m_actBackCityNoQuest.bDo?"��":"��");
	FontSystem::DrawTextDirect(szWord,&fontRect,DT_NOCLIP,dwFtColor,0,true);

	fontRect.left = 300;
	fontRect.top  = 150 + 18 * 3;
	fontRect.right = fontRect.left + 100;
	fontRect.bottom = fontRect.right + 60;

	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"ʹ�þ�����: %s",m_actUseEnergy.bDo?"��":"��");
	FontSystem::DrawTextDirect(szWord,&fontRect,DT_NOCLIP,dwFtColor,0,true);

	fontRect.left = 300;
	fontRect.top  = 150 + 18 * 4;
	fontRect.right = fontRect.left + 100;
	fontRect.bottom = fontRect.right + 60;

	std::string str;
	str.clear();

	if (IsPickFlag(Pick_All))
	{
		str += "ʰȡװ��";
	}
	else
	{
		str += "��ʰȡ";
	}

	FontSystem::DrawTextDirect(str.c_str(),&fontRect,DT_NOCLIP,dwFtColor,0,true);


	fontRect.left = 300;
	fontRect.top  = 150 + 18 * 5;
	fontRect.right = fontRect.left + 100;
	fontRect.bottom = fontRect.right + 60;

	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"��������:%s %s %s %s",
		(m_AttackSkill.m_Skill[0] != NULL)?m_AttackSkill.m_Skill[0]->GetSkillName():"��",
		(m_AttackSkill.m_Skill[1] != NULL)?m_AttackSkill.m_Skill[1]->GetSkillName():"��",
		(m_AttackSkill.m_Skill[2] != NULL)?m_AttackSkill.m_Skill[2]->GetSkillName():"��",
		(m_AttackSkill.m_Skill[3] != NULL)?m_AttackSkill.m_Skill[3]->GetSkillName():"��");

	FontSystem::DrawTextDirect(szWord,&fontRect,DT_NOCLIP,dwFtColor,0,true);

	fontRect.left = 300;
	fontRect.top  = 150 + 18 * 6;
	fontRect.right = fontRect.left + 100;
	fontRect.bottom = fontRect.right + 60;

	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"��������:%s %s %s %s",
		(m_BufSkill.m_Skill[0] != NULL)?m_BufSkill.m_Skill[0]->GetSkillName():"��",
		(m_BufSkill.m_Skill[1] != NULL)?m_BufSkill.m_Skill[1]->GetSkillName():"��",
		(m_BufSkill.m_Skill[2] != NULL)?m_BufSkill.m_Skill[2]->GetSkillName():"��",
		(m_BufSkill.m_Skill[3] != NULL)?m_BufSkill.m_Skill[3]->GetSkillName():"��");
	FontSystem::DrawTextDirect(szWord,&fontRect,DT_NOCLIP,dwFtColor,0,true);

	fontRect.left = 300;
	fontRect.top  = 150 + 18 * 7;
	fontRect.right = fontRect.left + 100;
	fontRect.bottom = fontRect.right + 60;

	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"��Ѫ����:%s %s ����:%d",
		(m_RecSkill.m_Skill[0] != NULL)?m_RecSkill.m_Skill[0]->GetSkillName():"��",
		(m_RecSkill.m_Skill[1] != NULL)?m_RecSkill.m_Skill[1]->GetSkillName():"��",m_RecSkill.nLimit);
	FontSystem::DrawTextDirect(szWord,&fontRect,DT_NOCLIP,dwFtColor,0,true);

	fontRect.left = 300;
	fontRect.top  = 150 + 18 * 8;
	fontRect.right = fontRect.left + 100;
	fontRect.bottom = fontRect.right + 60;

	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"�����Ѫ����:%s %s %s %s ����:%d ״̬:%s",
		(m_RecTeamSkill.m_Skill[0] != NULL)?m_RecTeamSkill.m_Skill[0]->GetSkillName():"��",
		(m_RecTeamSkill.m_Skill[1] != NULL)?m_RecTeamSkill.m_Skill[1]->GetSkillName():"��",
		(m_RecTeamSkill.m_Skill[2] != NULL)?m_RecTeamSkill.m_Skill[2]->GetSkillName():"��",
		(m_RecTeamSkill.m_Skill[3] != NULL)?m_RecTeamSkill.m_Skill[3]->GetSkillName():"��",m_RecTeamSkill.nLimit,m_IsNeedHpSkillTeam?"����":"�ر�");
	FontSystem::DrawTextDirect(szWord,&fontRect,DT_NOCLIP,dwFtColor,0,true);


	str.clear();
	if (IsTeamFlag(Team_AcceptInvite))
		str += "�������";

	if (IsTeamFlag(Team_AcceptComein))
		str += "�������";

	if (IsTeamFlag(Team_NeedItem))
		str +="ȫ������";

	fontRect.left = 300;
	fontRect.top  = 150 + 18 * 9;
	fontRect.right = fontRect.left + 100;
	fontRect.bottom = fontRect.right + 60;
	FontSystem::DrawTextDirect(str.c_str(),&fontRect,DT_NOCLIP,dwFtColor,0,true);

	if ( FontSystem::IsUseNewFont() )
	{
		FontRender::getFontRender()->SetDefaultRendererIdx( eOldIdx );
		FontSystem::DoRender( FontRender::EFR_THIRD );
	}	
  }
#endif

bool  AutoFight::IsAutoFight()
{
    return m_bAuto;
}

bool AutoFight::IsProtection()
{
	return m_bProtection;
}

bool AutoFight::IsPick()
{
	return m_bPick;
}

void  AutoFight::SetState(AutoState state)
{
    m_enum = state;
}

void AutoFight::Init()
{
    SetState(Enum_Pick);
    theHeroGame.GetPlayerMgr()->SetLockPlayerID(-1);  //���״̬
}
CPlayer* AutoFight::GetTeamPlayerInNeedHPSkill()
{
	if(!theHeroGame.GetPlayerMgr()->GetMe())
		return NULL;
	if(!thePlayerRole.m_TeamData.empty())
	{
		int MinHpPlayerID = 0;
		int MinHp = 100;
		std::vector<TeamInfo>::iterator Iter = thePlayerRole.GetTeamInfo().begin();
		for(;Iter != thePlayerRole.GetTeamInfo().end();++Iter)
		{
			CPlayer * pTeamMember = NULL;
			if(Iter->nID == theHeroGame.GetPlayerMgr()->GetMe()->GetCharacterID())
				pTeamMember = theHeroGame.GetPlayerMgr()->GetMe();
			else
				pTeamMember = theHeroGame.GetPlayerMgr()->FindPlayerByCharacterID(Iter->nID);
			if(!pTeamMember)
				continue;
			if(pTeamMember->IsDead())
				continue;
			D3DXVECTOR3 vDistance( theHeroGame.GetPlayerMgr()->GetMe()->GetMapPos().x - pTeamMember->GetMapPos().x, 
				theHeroGame.GetPlayerMgr()->GetMe()->GetMapPos().y - pTeamMember->GetMapPos().y, 0);
			float fDistance = D3DXVec3Length( &vDistance);
			if(fDistance <= 100)
			{
				//�ڷ�Χ��
				DWORD dwCurrHP = pTeamMember->GetHp();
				DWORD dwMaxHP  = pTeamMember->GetHpMax();
				int nRatio = int(float(dwCurrHP)/float(dwMaxHP)*100);

				if(Iter->nID == theHeroGame.GetPlayerMgr()->GetLockPlayerID())
				{
					//�����ǰ���Ϊ��������� ������Ȩ
					if(nRatio <= GetRecHpTeamPer())
					{
						return pTeamMember;
					}
				}
				if(MinHp > nRatio && nRatio <= GetRecHpTeamPer())
				{
					MinHp = nRatio;
					MinHpPlayerID = pTeamMember->GetID();
				}
			}
		}	
		if(MinHpPlayerID == 0)
			return NULL;
		CPlayer * pTeamMember = theHeroGame.GetPlayerMgr()->FindByID(MinHpPlayerID);
		//ȷ����Һ� ��������Ŀ��
		return pTeamMember;
	}
	else
	{
		//���ڶ������� ֻ��ֱ�Ӽ�Ѫ
		DWORD dwCurrHP = theHeroGame.GetPlayerMgr()->GetMe()->GetHp();
		DWORD dwMaxHP  = theHeroGame.GetPlayerMgr()->GetMe()->GetHpMax();
		int nRatio = int(float(dwCurrHP)/float(dwMaxHP)*100);
		if(nRatio <= GetRecHpTeamPer())
			return theHeroGame.GetPlayerMgr()->GetMe();
		else
			return NULL;
	}
}
bool  AutoFight::UseHpSkillInTeam()
{
	//�Զ���������ʹ�����Ƽ���  �Զ�����Ŀ�� �����ƶ���ȥ
	//1.ȷ����Ҫ���Ƶ���ҵ�ID
	if(theHeroGame.GetPlayerMgr()->GetMe())//����������˼�Ѫ �����Լ�
	{
		CPlayer * pPlayer = GetTeamPlayerInNeedHPSkill();
		if(pPlayer)
		{
			theHeroGame.GetPlayerMgr()->SetLockPlayerID(pPlayer->GetID());
			s_CUI_ID_FRAME_Target.SetPlayer(pPlayer->GetID());
		}
		else
		{
			theHeroGame.GetPlayerMgr()->SetLockPlayerID(-1);
			s_CUI_ID_FRAME_Target.SetPlayer(-1);
			return false;
		}
		if(!g_bTheRoleMoveToTargetPos)
        {
			CPlayer * pTeamMember = theHeroGame.GetPlayerMgr()->FindByID(theHeroGame.GetPlayerMgr()->GetLockPlayerID());
			if(!pTeamMember)
			{
				theHeroGame.GetPlayerMgr()->SetLockPlayerID(-1);
				s_CUI_ID_FRAME_Target.SetPlayer(-1);
				return false;
			}
			for (int i = 0;i < USEMAXSKILL;++i)
			{
				if(m_RecTeamSkill.m_Skill[m_RecTeamSkill.m_CurrIndex] != NULL)
					break;

				++m_RecTeamSkill.m_CurrIndex;
				m_RecTeamSkill.m_CurrIndex %= USEMAXSKILL;
			}
			int nIndex = m_RecTeamSkill.m_CurrIndex;
			if(m_RecTeamSkill.m_Skill[m_RecSkill.m_CurrIndex] != NULL)
			{
				++m_RecTeamSkill.m_CurrIndex;
				m_RecTeamSkill.m_CurrIndex %= USEMAXSKILL;
			}
			if(m_RecTeamSkill.m_Skill[nIndex] != NULL)
			{
				theHeroGame.GetPlayerMgr()->SetCurUseSkill( m_RecTeamSkill.m_Skill[nIndex]->ustItemID,m_RecTeamSkill.m_Skill[nIndex]->ustLevel );
				thePlayerRole.UpdateUI();
				s_CUI_ID_FRAME_AutoAttackSet.UpdateCD(m_RecTeamSkill.m_Skill[nIndex]->ustItemID,s_CUI_ID_FRAME_AutoAttackSet.m_pID_LISTIMG_SkillHpTeam,nIndex);
				theHeroGame.GetPlayerMgr()->OnSkill( false );
			}
		}
	}
	return false;
}
bool  AutoFight::UseAttackSkill()
{
    //��������ʹ��
    //û����,Ѱ�ҹ���
    int lockId = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
    if(lockId == -1&&!IsBackCityNoQuest())
    {
		 if(m_IsNeedHpSkillTeam)
		 {
			//��������ģʽ ����ֻѡ���Ա
			CPlayer * pPlayer = GetTeamPlayerInNeedHPSkill();
			if(!pPlayer)
				return false;
			theHeroGame.GetPlayerMgr()->SetLockPlayerID(pPlayer->GetID());
			g_nRoleCommonAttackStatus = CAS_NEED_AUTO_ATTACK;
		 }
		 else
		 {
			theHeroGame.GetPlayerMgr()->AutoSelectMonster();
			g_nRoleCommonAttackStatus = CAS_NEED_AUTO_ATTACK;
		}
    }

    lockId = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
    if(lockId == -1)//��ʾ�����޹���
	{
		if(!IsBackCityNoQuest())
			SetState(Enum_Pick);

        return false;
	}
    
    CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(lockId);
	g_nRoleCommonAttackStatus = CAS_NEED_AUTO_ATTACK;
    if(pPlayer != NULL)
    {
        if(!pPlayer->IsMonster()) //
		{
			//����ڹһ��У����ֶ�ѡ����Ŀ������� ������Ŀ��գ����Զ��һ��Զ���ȥѡ��Ŀ��
			//������ͣ������ʲô������
			theHeroGame.GetPlayerMgr()->SetLockPlayerID( -1 ); 
            return false;
		}

      
		//lyh++ �Զ��һ���ʱ�򣬲��ܽ��й����Ĺ��� ��ȥѡ����
		if(pPlayer->GetRealCountry() != CountryDefine::Country_Init&&
			thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry != CountryDefine::Country_Init&&
			thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry ==pPlayer->GetRealCountry())
		{
			//����ڹһ������У����ֶ�ѡ����Ŀ������ǲ����Թ����ģ�������� �����Զ��һ��Զ���ȥѡ�����Ŀ��			
			theHeroGame.GetPlayerMgr()->SetLockPlayerID( -1 ); 
			return false;
		}


        if(!g_bTheRoleMoveToTargetPos)
        {
            //ʹ�ù�������
            for (int i = 0;i < USEMAXSKILL;++i)
            {
                if(m_AttackSkill.m_Skill[m_AttackSkill.m_CurrIndex] != NULL)
                    break;
                
                ++m_AttackSkill.m_CurrIndex;
                m_AttackSkill.m_CurrIndex %= USEMAXSKILL;
            }

            int nIndex = m_AttackSkill.m_CurrIndex;
			ItemDefine::SItemSkill *pItemSkill = m_AttackSkill.m_Skill[nIndex];
            if (pItemSkill != NULL)
            {
                ++m_AttackSkill.m_CurrIndex;
                m_AttackSkill.m_CurrIndex %= USEMAXSKILL;
            }

			BOOL ret = FALSE;
			if (pItemSkill != NULL)
				ret = theHeroGame.GetPlayerMgr()->GetMe()->TryUseSkill(pPlayer, pItemSkill);

			if (pItemSkill != NULL && theHeroGame.GetPlayerMgr()->GetMe() != NULL && ret)
			{
				s_CUI_ID_FRAME_AutoAttackSet.UpdateCD(pItemSkill->ustItemID, s_CUI_ID_FRAME_AutoAttackSet.m_pID_LISTIMG_SkillAttack, nIndex);
				return false;
			}
			else
			{
				if (HQ_TimeGetTime() - m_dwSendMsgTime > WAITTIME)
				{
					g_nRoleCommonAttackStatus = CAS_NEED_AUTO_ATTACK;
					m_dwSendMsgTime = HQ_TimeGetTime();
				}
				theHeroGame.GetPlayerMgr()->MoveRoleToPlayer( pPlayer, FALSE, 0.0f, TRUE );
			}
        }
#ifdef _DEBUG
        if (!pPlayer->IsMonster())
        {
             //assert(0&&"ѡ�����");
            D3DXVECTOR3 pos = pPlayer->GetPos();
            theHeroGame.GetPlayerMgr()->MoveRoleTo(pos.x,pos.y,true);
            m_bAuto = false;
        }
#endif
    }

    return true;
}

bool  AutoFight::UseBufSkill()
{
    bool bUseSkill = false;

    for (int i = 0;i < USEMAXSKILL;++i)
    {
        if(m_BufSkill.m_Skill[m_BufSkill.m_CurrIndex] != NULL)
        {
            short sStatusID = -1;
            if(m_BufSkill.m_Skill[m_BufSkill.m_CurrIndex]->ustMeAddStatusID[0] != -1)
                sStatusID = m_BufSkill.m_Skill[m_BufSkill.m_CurrIndex]->ustMeAddStatusID[0];
            else if(m_BufSkill.m_Skill[m_BufSkill.m_CurrIndex]->ustDstAddStatusID[0] != -1)
                sStatusID = m_BufSkill.m_Skill[m_BufSkill.m_CurrIndex]->ustDstAddStatusID[0];
            else
                assert(0);

            //�ҵ���һ��BUF�Ƿ����
            if(theHeroGame.GetPlayerMgr()->GetMe() && !theHeroGame.GetPlayerMgr()->GetMe()->m_cFightStatus.IsHaveStatus(sStatusID))
            {
                bUseSkill = true;
                break;
            }
        }

        ++m_BufSkill.m_CurrIndex;
        m_BufSkill.m_CurrIndex %= USEMAXSKILL;
    }

    if(bUseSkill)
    {
        int nIndex = m_BufSkill.m_CurrIndex;

        ++m_BufSkill.m_CurrIndex;
        m_BufSkill.m_CurrIndex %= USEMAXSKILL;

        if(theHeroGame.GetPlayerMgr()->GetMe() && 
			theHeroGame.GetPlayerMgr()->GetMe()->TryUseSkill(theHeroGame.GetPlayerMgr()->GetMe(),m_BufSkill.m_Skill[nIndex]))
        {
            s_CUI_ID_FRAME_AutoAttackSet.UpdateCD(m_BufSkill.m_Skill[nIndex]->ustItemID,
                s_CUI_ID_FRAME_AutoAttackSet.m_pID_LISTIMG_SkillBuff,nIndex);

            return true;
        }
    }

    return false;
}
bool  AutoFight::UseHpSkill()
{
	if(!IsUseHpSkill())
		return false;
		
	//ʹ�û�Ѫ����
	for (int i = 0;i < USEMAXSKILL;++i)
	{
		if(m_RecSkill.m_Skill[m_RecSkill.m_CurrIndex] != NULL)
			break;

		++m_RecSkill.m_CurrIndex;
		m_RecSkill.m_CurrIndex %= USEMAXSKILL;
	}

	int nIndex = m_RecSkill.m_CurrIndex;
	if(m_RecSkill.m_Skill[m_RecSkill.m_CurrIndex] != NULL)
	{
		++m_RecSkill.m_CurrIndex;
		m_RecSkill.m_CurrIndex %= USEMAXSKILL;
	}
	if(m_RecSkill.m_Skill[nIndex] != NULL
		&& theHeroGame.GetPlayerMgr()->GetMe()
		&&theHeroGame.GetPlayerMgr()->GetMe()->TryUseSkill(theHeroGame.GetPlayerMgr()->GetMe(),m_RecSkill.m_Skill[nIndex]))
	{
		s_CUI_ID_FRAME_AutoAttackSet.UpdateCD(m_RecSkill.m_Skill[nIndex]->ustItemID,\
			s_CUI_ID_FRAME_AutoAttackSet.m_pID_LISTIMG_SkillHp,nIndex);

		return false;
	}

	return false;
}

void AutoFight::SetAttackSkill(ItemDefine::SItemSkill *pSkill,int nIndex)
{
    if(nIndex < 0 || nIndex >= USEMAXSKILL)
        return;

    m_AttackSkill.m_Skill[nIndex] = pSkill;
}

void AutoFight::SetBufSkill(ItemDefine::SItemSkill *pSkill,int nIndex)
{
    if(nIndex < 0 || nIndex >= USEMAXSKILL)
        return;

    m_BufSkill.m_Skill[nIndex] = pSkill;
}

void AutoFight::SetRecSkill(ItemDefine::SItemSkill *pSkill,int nIndex,int nLimit)
{
	if(nIndex < 0 || nIndex >= USEMAXSKILL)
		return;

	m_RecSkill.m_Skill[nIndex] = pSkill;
	m_RecSkill.nLimit = nLimit;
}
void AutoFight::SetRecTeamSkill(ItemDefine::SItemSkill *pSkill,int nIndex,int nLimit)
{
	if(nIndex < 0 || nIndex >= USEMAXSKILL)
		return;

	m_RecTeamSkill.m_Skill[nIndex] = pSkill;
	m_RecTeamSkill.nLimit = nLimit;
}
ItemDefine::SItemSkill* AutoFight::GetAttackSkill(int nIndex)
{
	if(nIndex < 0 || nIndex >= USEMAXSKILL)
		return NULL;

	return m_AttackSkill.m_Skill[nIndex];
}

ItemDefine::SItemSkill* AutoFight::GetBufSkill(int nIndex)
{
	if(nIndex < 0 || nIndex >= USEMAXSKILL)
		return NULL;

	return m_BufSkill.m_Skill[nIndex];
}

ItemDefine::SItemSkill* AutoFight::GetRecTeamSkill(int nIndex)
{
	if(nIndex < 0 || nIndex >= USEMAXSKILL)
		return NULL;

	return m_RecTeamSkill.m_Skill[nIndex];
}
ItemDefine::SItemSkill* AutoFight::GetRecSkill(int nIndex)
{
	if(nIndex < 0 || nIndex >= USEMAXSKILL)
		return NULL;

	return m_RecSkill.m_Skill[nIndex];
}

void AutoFight::EnterWait(DWORD elpaseTime)
{
    m_dwElapseTime = elpaseTime;
    m_WaitBeginTime = GetTickCount();
    m_enum = Enum_Wait;
}


bool AutoFight::IsHaveItem()
{
    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();

    CPlayer *pItem = pPlayerMgr->FindNearItemNpc();  //�����Ƿ��а�����û�о��л�״̬
    if(pItem != NULL )
	{
		//������item�Ѿ���ʰȡ�� ���򷵻�false
		
		if(s_CUI_ID_FRAME_AutoAttackSet.FindBeRecordItem(pItem->GetID()))
			return false;
       
		return true;
	}

    return false;
}

void AutoFight::ResetSkillSeq()
{
    m_AttackSkill.m_CurrIndex = 0;
    g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
    m_dwSendMsgTime = 0;
}

bool AutoFight::LoadDefaultData()
{
	char strFilename[MAX_PATH] = {0};
	sprintf(strFilename, "%s/Data/ClientConfig/GameSetting.config", GetRootPath());
	MeXmlDocument	doc;
	if( !doc.LoadFile(strFilename) )
	{
		assert(false && "CUI_ID_FRAME_AutoAttackSet::LoadCfgFile �ļ���ȡʧ��");
		return false;
	}

	const char* szValue = NULL;
	int nId = -1;

	MeXmlElement* pElem = doc.FirstChildElement("Project")->FirstChildElement("SystemConfig")->\
		FirstChildElement("Game")->FirstChildElement("AutoAttack");

	if(pElem)
	{
		ClearAreaSetting();
		int nValue = 0;
		pElem->QueryIntAttribute("NormalArea",&nValue);
		AddAreaSetting(nValue);

		pElem->QueryIntAttribute("BigArea",&nValue);
		AddAreaSetting(nValue);

		pElem->QueryIntAttribute("SmallArea",&nValue);
		AddAreaSetting(nValue);
	}

	MeXmlElement* pProfessElem = pElem->FirstChildElement("Profession");
	if (pProfessElem)
	{
		for( ; pProfessElem; pProfessElem = pProfessElem->NextSiblingElement() )
		{
			int nType = -1;
			pProfessElem->QueryIntAttribute("Type", &nType);
			if(nType == thePlayerRole.GetProfession())
			{
				MeXmlElement *pAttack = pProfessElem->FirstChildElement("AttackSkill");
				if(pAttack)
				{
					int nSkillID = 0;
					pAttack->QueryIntAttribute("SkillAttack1",&nSkillID);
					m_AttackSkill.m_CurrIndex = 0;

					SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nSkillID);
					if(pSkill)
					{
						ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_AttackSkill.m_Skill[0] = pItemSkill;
					}
					else
						m_AttackSkill.m_Skill[0] = NULL;

					pAttack->QueryIntAttribute("SkillAttack2",&nSkillID);
					pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nSkillID);
					if(pSkill)
					{
						ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_AttackSkill.m_Skill[1] = pItemSkill;
					}
					else
						m_AttackSkill.m_Skill[1] = NULL;

					pAttack->QueryIntAttribute("SkillAttack3",&nSkillID);
					pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nSkillID);
					if(pSkill)
					{
						ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_AttackSkill.m_Skill[2] = pItemSkill;
					}
					else
						m_AttackSkill.m_Skill[2] = NULL;


					pAttack->QueryIntAttribute("SkillAttack4",&nSkillID);
					pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nSkillID);
					if(pSkill)
					{
						ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_AttackSkill.m_Skill[3] = pItemSkill;
					}
					else
						m_AttackSkill.m_Skill[3] = NULL;
				}

				MeXmlElement *pBuf = pProfessElem->FirstChildElement("BufSkill");
				if(pBuf)
				{
					int nSkillID = 0;
					pBuf->QueryIntAttribute("SkillBuff1",&nSkillID);
					SCharSkill *pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nSkillID);
					if(pSkill)
					{
						ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_BufSkill.m_Skill[0] = pItemSkill;
					}
					else
						m_BufSkill.m_Skill[0] = NULL;

					pBuf->QueryIntAttribute("SkillBuff2",&nSkillID);
					pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nSkillID);
					if(pSkill)
					{
						ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_BufSkill.m_Skill[1] = pItemSkill;
					}
					else
						m_BufSkill.m_Skill[1] = NULL;


					pBuf->QueryIntAttribute("SkillBuff3",&nSkillID);
					pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nSkillID);
					if(pSkill)
					{
						ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_BufSkill.m_Skill[2] = pItemSkill;
					}
					else
						m_BufSkill.m_Skill[2] = NULL;

					pBuf->QueryIntAttribute("SkillBuff4",&nSkillID);
					pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nSkillID);
					if(pSkill)
					{
						ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_BufSkill.m_Skill[3] = pItemSkill;
					}
					else
						m_BufSkill.m_Skill[3] = NULL;
				}

				MeXmlElement *pRecover = pProfessElem->FirstChildElement("RecoverSkill");
				if(pRecover)
				{
					int nValue = 0;
					pRecover->QueryIntAttribute("SkillRec1",&nValue);
					SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nValue);
					if(pSkill)
					{
						ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_RecSkill.m_Skill[0] = pItemSkill;
					}
					else
						m_RecSkill.m_Skill[0] = NULL;

					pRecover->QueryIntAttribute("SkillRec2",&nValue);
					pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nValue);
					if(pSkill)
					{
						ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_RecSkill.m_Skill[1] = pItemSkill;
					}
					else
						m_RecSkill.m_Skill[1] = NULL;

					pRecover->QueryIntAttribute("HpPer",&nValue);
					SetRecSkillLimit(nValue);
				}

				MeXmlElement *pMedical = pProfessElem->FirstChildElement("Medical");
				if(pMedical)
				{
					int nValue = 0,nPer = 0;
					pMedical->QueryIntAttribute("UseHp",&nValue);
					pMedical->QueryIntAttribute("HpPer",&nPer);
					SetHp(nValue,nPer);

					pMedical->QueryIntAttribute("UseMp",&nValue);
					pMedical->QueryIntAttribute("MpPer",&nPer);
					SetMp(nValue,nPer);

					pMedical->QueryIntAttribute("UseEnergy",&nValue);
					SetUseEnergy(nValue);

					pMedical->QueryIntAttribute("UseTpNoMedical",&nValue);
					SetBackCityNoQuest(nValue);
				}

				MeXmlElement *pArea = pProfessElem->FirstChildElement("AttackArea");
				if(pArea)
				{
					int nValue = 0;
					pArea->QueryIntAttribute("AreaType",&nValue);

					SetAreaType((AreaState)nValue);
				}

				MeXmlElement *pPick = pProfessElem->FirstChildElement("Pick");
				if(pPick)
				{
					int nValue = 0;
					pPick->QueryIntAttribute("All",&nValue);
					if(nValue)
						AddPickFlag(Pick_All);
					else
						RemovePickFlag(Pick_All);
				}

				MeXmlElement *pTeam = pProfessElem->FirstChildElement("Team");
				if(pTeam)
				{
					int nValue = 0;
					pTeam->QueryIntAttribute("AcceptInvite",&nValue);
					if(nValue)
						AddTeamFlag(Team_AcceptInvite);
					else
						RemoveTeamFlag(Team_AcceptInvite);

					pTeam->QueryIntAttribute("ComeInTeam",&nValue);
					if(nValue)
						AddTeamFlag(Team_AcceptComein);
					else
						RemoveTeamFlag(Team_AcceptComein);

					pTeam->QueryIntAttribute("NeedAll",&nValue);
					if(nValue)
						AddTeamFlag(Team_NeedItem);
					else
						RemoveTeamFlag(Team_NeedItem);
				}

				MeXmlElement *pRecoverTeam = pProfessElem->FirstChildElement("RecoverTeamSkill");
				if(pRecoverTeam)
				{
					int nValue = 0;
					pRecoverTeam->QueryIntAttribute("TeamSkillRec1",&nValue);
					SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nValue);
					if(pSkill)
					{
						ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_RecTeamSkill.m_Skill[0] = pItemSkill;
					}
					else
						m_RecTeamSkill.m_Skill[0] = NULL;

					pRecoverTeam->QueryIntAttribute("TeamSkillRec2",&nValue);
					pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nValue);
					if(pSkill)
					{
						ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_RecTeamSkill.m_Skill[1] = pItemSkill;
					}
					else
						m_RecTeamSkill.m_Skill[1] = NULL;

					pRecoverTeam->QueryIntAttribute("TeamSkillRec3",&nValue);
					pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nValue);
					if(pSkill)
					{
						ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_RecTeamSkill.m_Skill[2] = pItemSkill;
					}
					else
						m_RecTeamSkill.m_Skill[2] = NULL;

					pRecoverTeam->QueryIntAttribute("TeamSkillRec4",&nValue);
					pSkill = thePlayerRole.m_SkillBag.GetSkillByID(nValue);
					if(pSkill)
					{
						ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
						m_RecTeamSkill.m_Skill[3] = pItemSkill;
					}
					else
						m_RecTeamSkill.m_Skill[3] = NULL;

					pRecoverTeam->QueryIntAttribute("TeamHpPer",&nValue);
					SetRecTeamSkillLimit(nValue);

					pRecoverTeam->QueryIntAttribute("IsOpenTeamHpSkill",&nValue);//�Ƿ��������Ѫģʽ Ĭ�ϲ�����
					m_IsNeedHpSkillTeam = (nValue==1)?true:false;
				}
				break;
			}
		}
	}

	m_HpItemId = 0;
	m_MpItemId = 0;
	s_CUI_ID_FRAME_AutoAttackSet.SetUpdateUI(true);
	return true;
}

bool AutoFight::ReadData(int nValue)
{
    char szPath[MAX_PATH] = {0};
    MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1,"%s/Client/UserData/%s/%s/%s/%s/AutoFight%d.ws", GetRootPath(),
        CUserData::Instance()->GetAccount(),CUserData::Instance()->GetArea(),
        CUserData::Instance()->GetServer(), /*CUserData::Instance()->GetRole()*/thePlayerRole.GetName(),nValue);

    f_Handle* fp = packet_namespace::w_fopen(szPath,"rb");
    if(!fp)
        return false;

    unsigned short usSkillID = 0;
    for (int i = 0;i < USEMAXSKILL;++i)
    {
       packet_namespace::w_fread(&usSkillID,sizeof(unsigned short),1,fp);
       
       SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(usSkillID);
       if(pSkill)
       {
           ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
           m_AttackSkill.m_Skill[i] = pItemSkill;
       }
       else
           m_AttackSkill.m_Skill[i] = NULL;
    }

    m_AttackSkill.m_CurrIndex = 0;

    for (int i = 0;i < USEMAXSKILL;++i)
    {
        packet_namespace::w_fread(&usSkillID,sizeof(unsigned short),1,fp);

        SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(usSkillID);
        if(pSkill)
        {
            ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
            m_BufSkill.m_Skill[i] = pItemSkill;
        }
        else
            m_BufSkill.m_Skill[i] = NULL;
    }
    m_BufSkill.m_CurrIndex = 0;

	for (int i = 0;i < 2;++i)
	{
		packet_namespace::w_fread(&usSkillID,sizeof(unsigned short),1,fp);

		SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(usSkillID);
		if(pSkill)
		{
			ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
			m_RecSkill.m_Skill[i] = pItemSkill;
		}
		else
			m_RecSkill.m_Skill[i] = NULL;
	}
	m_RecSkill.m_CurrIndex = 0;
	packet_namespace::w_fread(&m_RecSkill.nLimit,sizeof(int),1,fp);

	for (int i = 0;i < 4;++i)
	{
		packet_namespace::w_fread(&usSkillID,sizeof(unsigned short),1,fp);

		SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID(usSkillID);
		if(pSkill)
		{
			ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
			m_RecTeamSkill.m_Skill[i] = pItemSkill;
		}
		else
			m_RecTeamSkill.m_Skill[i] = NULL;
	}
	m_RecTeamSkill.m_CurrIndex = 0;
	packet_namespace::w_fread(&m_RecTeamSkill.nLimit,sizeof(int),1,fp);

	packet_namespace::w_fread(&m_actHp,sizeof(Action),1,fp);
	packet_namespace::w_fread(&m_actMp,sizeof(Action),1,fp);
	packet_namespace::w_fread(&m_actUseEnergy,sizeof(Action),1,fp);
	packet_namespace::w_fread(&m_actBackCityNoQuest,sizeof(Action),1,fp);
	packet_namespace::w_fread(&m_AttackZone.m_eAreaState,sizeof(int),1,fp);
	packet_namespace::w_fread(&m_dwPickState,sizeof(DWORD),1,fp);
	packet_namespace::w_fread(&m_dwTeamState,sizeof(DWORD),1,fp);
	packet_namespace::w_fread(&m_dwSuoDingState,sizeof(DWORD),1,fp);
	packet_namespace::w_fread(&m_dwProtection,sizeof(DWORD),1,fp);

	packet_namespace::w_fread(&m_HpItemId,sizeof(DWORD),1,fp);
    packet_namespace::w_fread(&m_MpItemId,sizeof(DWORD),1,fp);
		
	int Value = 0;
	packet_namespace::w_fread(&Value,sizeof(int),1,fp);
	m_IsNeedHpSkillTeam = (Value == 1)?true:false;

	
    packet_namespace::w_fclose(fp);

    s_CUI_ID_FRAME_AutoAttackSet.SetUpdateUI(true);
	s_CUI_ID_FRAME_AutoAttackSet.UpdateUIData(); //lyh++ �������õ�ʱ�� ��������һ��ui
    return true;
}

bool AutoFight::WriteData(int nValue)
{
    if(!s_CUI_ID_FRAME_AutoAttackSet.m_bSave)
        return false;

    char szPath[MAX_PATH] = {0};
    MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1,"%s/Client/UserData/%s/%s/%s/%s/AutoFight%d.ws",GetRootPath(),
            CUserData::Instance()->GetAccount(),CUserData::Instance()->GetArea(),
            CUserData::Instance()->GetServer(), /*CUserData::Instance()->GetRole()*/thePlayerRole.GetName(),nValue);
    FILE* fp = fopen(szPath, "wb" );
    if( !fp )
        return false;  


    for (int i = 0;i < USEMAXSKILL;++i)
    {
        if(m_AttackSkill.m_Skill[i])
           fwrite(&m_AttackSkill.m_Skill[i]->ustItemID,sizeof(unsigned short),1,fp);
        else
        {
           unsigned short usNum = 0;
           fwrite(&usNum,sizeof(unsigned short),1,fp);
        }
    }

    for (int i = 0;i < USEMAXSKILL;++i)
    {
        if(m_BufSkill.m_Skill[i])
            fwrite(&m_BufSkill.m_Skill[i]->ustItemID,sizeof(unsigned short),1,fp);   //Buf
        else
        {
            unsigned short usNum = 0;
           fwrite(&usNum,sizeof(unsigned short),1,fp);
        }
    }

	for (int i = 0;i < 2;++i)
	{
		if(m_RecSkill.m_Skill[i])
			fwrite(&m_RecSkill.m_Skill[i]->ustItemID,sizeof(unsigned short),1,fp);
		else
		{
			unsigned short usNum = 0;
			fwrite(&usNum,sizeof(unsigned short),1,fp);
		}
	}
	fwrite(&m_RecSkill.nLimit,sizeof(int),1,fp);

	for (int i = 0;i < 4;++i)
	{
		if(m_RecTeamSkill.m_Skill[i])
			fwrite(&m_RecTeamSkill.m_Skill[i]->ustItemID,sizeof(unsigned short),1,fp);
		else
		{
			unsigned short usNum = 0;
			fwrite(&usNum,sizeof(unsigned short),1,fp);
		}
	}
	fwrite(&m_RecTeamSkill.nLimit,sizeof(int),1,fp);
	
	fwrite(&m_actHp,sizeof(Action),1,fp);
	fwrite(&m_actMp,sizeof(Action),1,fp);
	fwrite(&m_actUseEnergy,sizeof(Action),1,fp);
	fwrite(&m_actBackCityNoQuest,sizeof(Action),1,fp);
	fwrite(&m_AttackZone.m_eAreaState,sizeof(int),1,fp);
	fwrite(&m_dwPickState,sizeof(DWORD),1,fp);
	fwrite(&m_dwTeamState,sizeof(DWORD),1,fp);
	//zhuxincong 9.27 ���������
	fwrite(&m_dwSuoDingState,sizeof(DWORD),1,fp);
	fwrite(&m_dwProtection,sizeof(DWORD),1,fp);

	//lyh++  д��2��ֵ ��ҩid �� ��ҩid
	fwrite(&m_HpItemId,sizeof(DWORD),1,fp);
	fwrite(&m_MpItemId,sizeof(DWORD),1,fp);

	int Value = (m_IsNeedHpSkillTeam?1:0);
	fwrite(&Value,sizeof(int),1,fp);

    fclose( fp );
    return true;
}

ControlListImage* CUI_ID_FRAME_AutoAttackSet::GetListImage_Hp()
{
	if( !m_pID_FRAME_AutoAttackSet )
		return NULL;

	return m_pID_LISTIMG_Hp;
}

ControlListImage* CUI_ID_FRAME_AutoAttackSet::GetListImage_Mp()
{
	if( !m_pID_FRAME_AutoAttackSet )
		return NULL;

	return m_pID_LISTIMG_Mp;
}

ControlListImage* CUI_ID_FRAME_AutoAttackSet::GetListImage_SkillAttack()
{
	if( !m_pID_FRAME_AutoAttackSet )
		return NULL;

	return m_pID_LISTIMG_SkillAttack;
}

ControlListImage* CUI_ID_FRAME_AutoAttackSet::GetListImage_SkillBuff()
{
	if( !m_pID_FRAME_AutoAttackSet )
		return NULL;

	return m_pID_LISTIMG_SkillBuff;
}

ControlListImage* CUI_ID_FRAME_AutoAttackSet::GetListImage_SkillHp()
{
	if(!m_pID_FRAME_AutoAttackSet)
		return NULL;

	return m_pID_LISTIMG_SkillHp;
}
ControlListImage* CUI_ID_FRAME_AutoAttackSet::GetListImage_SkillHpTeam()
{
	if(!m_pID_FRAME_AutoAttackSet)
		return NULL;

	return m_pID_LISTIMG_SkillHpTeam;
}
void CUI_ID_FRAME_AutoAttackSet::BeginAutoAttack()
{
	if( !IsUILoad() )
		return;

	if(theHeroGame.GetPlayerMgr()&&theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsGoudaOperaMode()
		||theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString(eText_AutoFightNotStartCurState) );
		return; //lyh++ ����ģʽ�����Զ��һ�
	}

	if( s_CUI_ID_FRAME_Target.GetFollowPlayerId() > -1 || s_CUI_ID_FRAME_Team.GetTeamFollowID() > -1)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString(eText_AutoFightNotStartCurState) );
		return; //lyh++ ����Ŀ��״̬�²���ʹ�ùһ�
	}

	//lyh++duorenzuoji //���������� �Ǽ�ʻԱ�����ͷż���
	if(theHeroGame.GetPlayerMgr()&&theHeroGame.GetPlayerMgr()->GetMe())
	{
		if(theHeroGame.GetPlayerMgr()->GetMe()->IsMultiMounting() && 
			theHeroGame.GetPlayerMgr()->GetMe()->GetCarrierPlayerID() != theHeroGame.GetPlayerMgr()->GetMe()->GetID())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotDoIt ) );
			return ;
		}

	}
	m_pID_BUTTON_Begin->SetVisable(false);
	m_pID_BUTTON_Stop->SetVisable(true);

	g_bTheRoleMoveToTargetPos = FALSE; //lyh++ 
	SetFightState();  //����ս��״̬
	//ID_BUTTON_SaveOnButtonClick(NULL); ��ֹ��һ�ν���Ϸ��ʱ�򣬳�ʼ������Ĭ��ֵ��Ȼ��ֱ�ӿ�ݼ��һ�������д��ȥ�Ķ��ǳ�ʼ����ֵ��ui�����
	
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString(eText_AutoFightStart) );

	//lyh�ҹһ�
	BeginAutoAttackTime = timeGetTime();

   //�����һ���ʱ�������ǰĿ�����������յ�ǰĿ��
	CPlayer* targetPlayer = theHeroGame.GetPlayerMgr()->FindByID(s_CUI_ID_FRAME_Target.GetPlayerID()) ;
	if (targetPlayer )
	{
		if(targetPlayer->IsPlayer())
		s_CUI_ID_FRAME_Target.SetPlayer(-1);

		if (targetPlayer->IsMonster())
		{
			if ((targetPlayer->GetTypeStatus() == MonsterDefine::StatusUnMoveNpc 
				|| targetPlayer->GetTypeStatus() == MonsterDefine::StatusMoveNpc ))
			{
				s_CUI_ID_FRAME_Target.SetPlayer(-1);
			}
		}
	}
}


void CUI_ID_FRAME_AutoAttackSet::EndAutoAttack()
{
	if(!m_autoFight.IsAutoFight())
	{
		if ( !IsUILoad())
		{
			return;
		}
		m_pID_BUTTON_Begin->SetVisable(true);
		m_pID_BUTTON_Stop->SetVisable(false);
		return;
	}
	else
	{
		/*m_pID_BUTTON_Begin->SetVisable(true);
		m_pID_BUTTON_Stop->SetVisable(false);*/
		s_CUI_ID_FRAME_AutoAttackSet.SetVisable(true);
		m_pID_BUTTON_Begin->SetVisable(true);
		m_pID_BUTTON_Stop->SetVisable(false);
		if( !IsUILoad() )
			return;
		s_CUI_ID_FRAME_AutoAttackSet.SetVisable(false);
		m_pID_FRAME_AutoAttackSet->SetVisable(false);
		m_pID_BUTTON_Begin->SetVisable(true);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString(eText_AutoFightEnd) );
		if(theHeroGame.GetPlayerMgr() != NULL 
			&&theHeroGame.GetPlayerMgr()->GetMe() != NULL)
			theHeroGame.GetPlayerMgr()->GetMe()->StopMoving(false);

		m_autoFight.EndFight();  //ֹͣ�һ�
		s_CUI_ID_FRAME_AutoAttackSet.BeginAutoAttackTime = 0;
	}
	//s_CUI_ID_FRAME_AutoAttackSet.SetVisable(true);
	//if( !IsUILoad() )
	//	return;
	//s_CUI_ID_FRAME_AutoAttackSet.SetVisable(false);
	//m_pID_FRAME_AutoAttackSet->SetVisable(false);
	//m_pID_BUTTON_Begin->SetVisable(true);
	//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString(eText_AutoFightEnd) );
	//if(theHeroGame.GetPlayerMgr() != NULL 
	//	&&theHeroGame.GetPlayerMgr()->GetMe() != NULL)
	//	theHeroGame.GetPlayerMgr()->GetMe()->StopMoving(false);

	//m_autoFight.EndFight();  //ֹͣ�һ�
}


bool AutoFight::IsNoExistMonster(unsigned int usMonsterId)
{
	for(MonsIter it = m_MonsSetting.begin();it != m_MonsSetting.end();++it)
	{
		if(usMonsterId == it->nMonsterId)
			return it->bKill;
	}
	return true;
}

void AutoFight::AddMonsterSet(unsigned int usMonsterId)
{
	//�ҵ���ֱ�������ܴ�
	for(MonsIter it = m_MonsSetting.begin();it != m_MonsSetting.end();++it)
	{
		if(usMonsterId == it->nMonsterId)
		{
			it->bKill = true;
			return;
		}			
	}

	//δ�ҵ������
	MonsterSetting mons;
	mons.nMonsterId = usMonsterId;
	mons.bKill      = true;

	m_MonsSetting.push_back(mons);
}

void AutoFight::DelMonsterSet(unsigned int usMonsterId)
{
	for(MonsIter it = m_MonsSetting.begin();it != m_MonsSetting.end();++it)
	{
		if(usMonsterId == it->nMonsterId)
		{
			it->bKill = false;
			return;
		}			
	}
}


bool AutoFight::IsUseHpQuest()
{
	if(!m_actHp.bDo)
		return false;

	DWORD dwCurrHP = thePlayerRole.GetData(CPlayerRole::TYPE_HP);
	DWORD dwMaxHP  = thePlayerRole.GetData(CPlayerRole::TYPE_HPMAX);

	int nRatio = int(float(dwCurrHP)/float(dwMaxHP)*100);

	return (nRatio <= m_actHp.nLimitPer);
}

bool AutoFight::IsUseMpQuset()
{
	if(!m_actMp.bDo)
		return false;

	DWORD dwCurMp = thePlayerRole.GetData(CPlayerRole::TYPE_MP);
	DWORD dwMaxMp = thePlayerRole.GetData(CPlayerRole::TYPE_MPMAX);

	int nRatio = int(float(dwCurMp)/float(dwMaxMp) * 100);
	return (nRatio <= m_actMp.nLimitPer);
}

bool AutoFight::IsBackCityNoQuest()
{
	return false;
	if(!m_actBackCityNoQuest.bDo)
		return false;

	if(SearchQuestIndex() == -1)
		return true; 

	return false;
}

bool AutoFight::IsUseHpSkill()
{
	DWORD dwCurrHP = thePlayerRole.GetData(CPlayerRole::TYPE_HP);
	DWORD dwMaxHP  = thePlayerRole.GetData(CPlayerRole::TYPE_HPMAX);

	int nRatio = int(float(dwCurrHP)/float(dwMaxHP)*100);

	return (nRatio <= GetRecHpPer());
}

void AutoFight::SetHp(bool bValue,int nValue)
{
	m_actHp.bDo = bValue;
	m_actHp.nLimitPer = nValue;
}

void AutoFight::SetMp(bool bValue,int nValue)
{
	m_actMp.bDo = bValue;
	m_actMp.nLimitPer = nValue;
}

void AutoFight::SetBackCityNoQuest(bool bValue)
{
	m_actBackCityNoQuest.bDo = bValue;
	m_actBackCityNoQuest.nLimitPer = 0;
}

void AutoFight::SetUseEnergy(bool bValue)
{
	m_actUseEnergy.bDo = bValue;
	m_actUseEnergy.nLimitPer = 0;
}

int AutoFight::SearchQuestIndex(bool bAddHp /*= true*/)
{
	int nQuseID = -1;
	int   nIndex = -1;
	int nSize = thePlayerRole.m_bag.GetNowBagSize();
	int nCount = 0;
	for(;nCount < nSize;nCount++)
	{
		SCharItem sCItem;
		if(!thePlayerRole.m_bag.GetItem(nCount,&sCItem))
			continue;

		if(sCItem.storageinfo.bIsLocked)
			continue;

		ItemDefine::SItemCommon *pItemCommon = NULL;
		pItemCommon = GettheItemDetail().GetItemByID( sCItem.itembaseinfo.ustItemID);
		if( !pItemCommon )
			continue;

		if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_RESTORE)
			continue;

		ItemDefine::SItemRestore *pItemRestore;
		pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;

		if ( pItemRestore->stUseLevel > thePlayerRole.GetLevel() )
			continue;
		
		if (!pItemRestore->arrayProfessionReq[thePlayerRole.GetProfession()])
			continue;

		//zhuxincong 11.28 �߻�����Ҫ��Restore.config�е�RestoteHP�ֶ�Ϊ0��Ҳ���Գ�ҩ
		if(bAddHp)
		{
			if(pItemRestore->dwAddHP <= 0 || s_CUI_ID_FRAME_DeBuffUI.IfHPBuffID())
				continue;
		}
		else
		{
			if(pItemRestore->dwAddMP <= 0 || s_CUI_ID_FRAME_DeBuffUI.IfMPBuffID())
				continue;
		}

		//��߼����� ��ָ����ҩ �򷵻ر�������ֱ����
		if(bAddHp)
		{
			if(!s_CUI_ID_FRAME_AutoAttackSet.m_pID_LISTIMG_Hp->GetItemByIndex(0))
				break;

			if(pItemCommon->ustItemID == m_HpItemId)			
			{
				nQuseID = sCItem.itembaseinfo.ustItemID;
				nIndex = nCount;
				m_OutPutFindHP = true;
                break;
			}
		}
		else
		{
			if(!s_CUI_ID_FRAME_AutoAttackSet.m_pID_LISTIMG_Mp->GetItemByIndex(0))
				break;

			if(pItemCommon->ustItemID == m_MpItemId )
			{
				nQuseID = sCItem.itembaseinfo.ustItemID;
				nIndex = nCount;
				m_OutPutFindMP = true;
				break;
			}
		}



         

		//if(nQuseID == -1 || sCItem.itembaseinfo.ustItemID < nQuseID)
		//{
		//	nQuseID = sCItem.itembaseinfo.ustItemID;
		//	nIndex = nCount;
		//}
	}

	if (bAddHp )
	{
		if (m_OutPutFindHP && nIndex == -1 && !s_CUI_ID_FRAME_DeBuffUI.IfHPBuffID())
		{
			m_OutPutFindHP = false;
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_GuildInfo, theXmlString.GetString(eText_AutoFightNoFindHP) );

		}


	}else
	{
		if (m_OutPutFindMP && nIndex == -1 && !s_CUI_ID_FRAME_DeBuffUI.IfMPBuffID())
		{
           m_OutPutFindMP = false;
		 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_GuildInfo, theXmlString.GetString(eText_AutoFightNoFindMP) );
		}

	}

	return nIndex;
}

void AutoFight::AddAreaSetting(int nValue)
{
	m_vecArea.push_back(nValue);
}

int  AutoFight::GetAreaSetting(AreaState eType)
{
	if((int)eType < 0 || (int)eType >= m_vecArea.size())
		return 0;

	return m_vecArea[eType];
}
