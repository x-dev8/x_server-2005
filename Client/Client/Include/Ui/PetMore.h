/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\zhuomeng.hu\桌面\PetMore.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GlobalDef.h"
#include "PlayerAnimCtrl.h"

#ifndef ID_FRAME_PetMore
#define ID_FRAME_PetMore		"ID_FRAME_PetMore"
#endif  ID_FRAME_PetMore
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_PICTURE_Pet1
#define ID_PICTURE_Pet1		"ID_PICTURE_Pet1"
#endif  ID_PICTURE_Pet1
#ifndef ID_PICTURE_Pet2
#define ID_PICTURE_Pet2		"ID_PICTURE_Pet2"
#endif  ID_PICTURE_Pet2
#ifndef ID_COMBOBOX_SelectPet1
#define ID_COMBOBOX_SelectPet1		"ID_COMBOBOX_SelectPet1"
#endif  ID_COMBOBOX_SelectPet1
#ifndef ID_COMBOBOX_SelectPet2
#define ID_COMBOBOX_SelectPet2		"ID_COMBOBOX_SelectPet2"
#endif  ID_COMBOBOX_SelectPet2
#ifndef ID_TEXT_Result1
#define ID_TEXT_Result1		"ID_TEXT_Result1"
#endif  ID_TEXT_Result1
#ifndef ID_TEXT_Result2
#define ID_TEXT_Result2		"ID_TEXT_Result2"
#endif  ID_TEXT_Result2
#ifndef ID_TEXT_Level1
#define ID_TEXT_Level1		"ID_TEXT_Level1"
#endif  ID_TEXT_Level1
#ifndef ID_TEXT_Level2
#define ID_TEXT_Level2		"ID_TEXT_Level2"
#endif  ID_TEXT_Level2
#ifndef ID_TEXT_Generation1
#define ID_TEXT_Generation1		"ID_TEXT_Generation1"
#endif  ID_TEXT_Generation1
#ifndef ID_TEXT_Generation2
#define ID_TEXT_Generation2		"ID_TEXT_Generation2"
#endif  ID_TEXT_Generation2
#ifndef ID_TEXT_StrengthZ
#define ID_TEXT_StrengthZ		"ID_TEXT_StrengthZ"
#endif  ID_TEXT_StrengthZ
#ifndef ID_TEXT_AgilityZ
#define ID_TEXT_AgilityZ		"ID_TEXT_AgilityZ"
#endif  ID_TEXT_AgilityZ
#ifndef ID_TEXT_StaminaZ
#define ID_TEXT_StaminaZ		"ID_TEXT_StaminaZ"
#endif  ID_TEXT_StaminaZ
#ifndef ID_TEXT_IntellectZ
#define ID_TEXT_IntellectZ		"ID_TEXT_IntellectZ"
#endif  ID_TEXT_IntellectZ
#ifndef ID_TEXT_Strength
#define ID_TEXT_Strength		"ID_TEXT_Strength"
#endif  ID_TEXT_Strength
#ifndef ID_TEXT_Agility
#define ID_TEXT_Agility		"ID_TEXT_Agility"
#endif  ID_TEXT_Agility
#ifndef ID_TEXT_Stamina
#define ID_TEXT_Stamina		"ID_TEXT_Stamina"
#endif  ID_TEXT_Stamina
#ifndef ID_TEXT_Intellect
#define ID_TEXT_Intellect		"ID_TEXT_Intellect"
#endif  ID_TEXT_Intellect
#ifndef ID_TEXT_NeedMoney
#define ID_TEXT_NeedMoney		"ID_TEXT_NeedMoney"
#endif  ID_TEXT_NeedMoney
#ifndef ID_TEXT_CurrentMoney
#define ID_TEXT_CurrentMoney		"ID_TEXT_CurrentMoney"
#endif  ID_TEXT_CurrentMoney
#ifndef ID_LISTIMG_Skill1
#define ID_LISTIMG_Skill1		"ID_LISTIMG_Skill1"
#endif  ID_LISTIMG_Skill1
#ifndef ID_LISTIMG_Skill2
#define ID_LISTIMG_Skill2		"ID_LISTIMG_Skill2"
#endif  ID_LISTIMG_Skill2

class CUI_ID_FRAME_PetMore : public CUIBase
{
public:	
    CUI_ID_FRAME_PetMore();

    bool OnFrameRun();
    bool OnFrameRender();
    bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
    void ID_COMBOBOX_SelectPet1OnComboBoxChange( ControlObject* pSender, const char* szData );
    void ID_COMBOBOX_SelectPet2OnComboBoxChange( ControlObject* pSender, const char* szData );

    virtual bool _LoadUI();				                    // 载入UI
    bool DoControlConnect();	                    // 关连控件
    virtual bool _UnLoadUI();			                    // 卸载UI
    virtual bool _IsVisable();			                    // 是否可见
    virtual void _SetVisable( const bool bVisable );		// 设置是否可视

    void ResetControls();
    void RefreshMoney();

private:
    ControlFrame*	    m_pID_FRAME_PetMore;
    ControlButton*	    m_pID_BUTTON_OK;
    ControlButton*	    m_pID_BUTTON_CLOSE;
    ControlPicture*	    m_pID_PICTURE_Pet1;
    ControlPicture*	    m_pID_PICTURE_Pet2;
    ControlComboBox*	m_pID_COMBOBOX_SelectPet1;
    ControlComboBox*	m_pID_COMBOBOX_SelectPet2;
    ControlText*	    m_pID_TEXT_Result1;
    ControlText*	    m_pID_TEXT_Result2;
    ControlText*	    m_pID_TEXT_Level1;
    ControlText*	    m_pID_TEXT_Level2;
    ControlText*	    m_pID_TEXT_Generation1;
    ControlText*	    m_pID_TEXT_Generation2;
    ControlText*	    m_pID_TEXT_StrengthZ;
    ControlText*	    m_pID_TEXT_AgilityZ;
    ControlText*	    m_pID_TEXT_StaminaZ;
    ControlText*	    m_pID_TEXT_IntellectZ;
    ControlText*	    m_pID_TEXT_Strength;
    ControlText*	    m_pID_TEXT_Agility;
    ControlText*	    m_pID_TEXT_Stamina;
    ControlText*	    m_pID_TEXT_Intellect;
    ControlText*	    m_pID_TEXT_NeedMoney;
    ControlText*	    m_pID_TEXT_CurrentMoney;
    ControlListImage*	m_pID_LISTIMG_Skill1;
    ControlListImage*	m_pID_LISTIMG_Skill2;

protected:
    static void OnVisibleChange( ControlObject* pUIObject ); 
    void        ResetMembers();
    void        Refresh();
    void        RenderViewport();

private:
    CPlayerAnim*    m_pAnim1;
    CPlayerAnim*    m_pAnim2;
    int             m_nMountId1;
    int             m_nMountId2;
};

extern CUI_ID_FRAME_PetMore s_CUI_ID_FRAME_PetMore;
