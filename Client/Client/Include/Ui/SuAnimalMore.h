#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GlobalDef.h"
#include "PlayerAnimCtrl.h"

#ifndef ID_FRAME_SuAnimalMore
#define ID_FRAME_SuAnimalMore		"ID_FRAME_SuAnimalMore"
#endif  ID_FRAME_SuAnimalMore
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_PICTURE_Pet1
#define ID_PICTURE_Pet1		"ID_PICTURE_Pet1"
#endif  ID_PICTURE_Pet1
#ifndef ID_PICTURE_Pet2
#define ID_PICTURE_Pet2		"ID_PICTURE_Pet2"
#endif  ID_PICTURE_Pet2
#ifndef ID_TEXT_Result1
#define ID_TEXT_Result1		"ID_TEXT_Result1"
#endif  ID_TEXT_Result1
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
#ifndef ID_TEXT_Result2
#define ID_TEXT_Result2		"ID_TEXT_Result2"
#endif  ID_TEXT_Result2
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
#ifndef ID_COMBOBOX_SelectPet1
#define ID_COMBOBOX_SelectPet1		"ID_COMBOBOX_SelectPet1"
#endif  ID_COMBOBOX_SelectPet1
#ifndef ID_COMBOBOX_SelectPet2
#define ID_COMBOBOX_SelectPet2		"ID_COMBOBOX_SelectPet2"
#endif  ID_COMBOBOX_SelectPet2
#ifndef ID_LIST_Pet
#define ID_LIST_Pet		"ID_LIST_Pet"
#endif  ID_LIST_Pet
#ifndef ID_TEXT_PartnerPetName
#define ID_TEXT_PartnerPetName		"ID_TEXT_PartnerPetName"
#endif  ID_TEXT_PartnerPetName
#ifndef ID_TEXT_MyPetName
#define ID_TEXT_MyPetName		"ID_TEXT_MyPetName"
#endif  ID_TEXT_MyPetName
#ifndef ID_TEXT_Info1
#define ID_TEXT_Info1		"ID_TEXT_Info1"
#endif  ID_TEXT_Info1
#ifndef ID_BUTTON_ChangePet
#define ID_BUTTON_ChangePet		"ID_BUTTON_ChangePet"
#endif  ID_BUTTON_ChangePet
#ifndef ID_BUTTON_LookPet
#define ID_BUTTON_LookPet		"ID_BUTTON_LookPet"
#endif  ID_BUTTON_LookPet
#ifndef ID_TEXT_Info2
#define ID_TEXT_Info2		"ID_TEXT_Info2"
#endif  ID_TEXT_Info2
#ifndef ID_BUTTON_LookPartnerPet
#define ID_BUTTON_LookPartnerPet		"ID_BUTTON_LookPartnerPet"
#endif  ID_BUTTON_LookPartnerPet
#ifndef ID_BUTTON_Lock
#define ID_BUTTON_Lock		"ID_BUTTON_Lock"
#endif  ID_BUTTON_Lock
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Right1
#define ID_BUTTON_Right1		"ID_BUTTON_Right1"
#endif  ID_BUTTON_Right1
#ifndef ID_BUTTON_Right2
#define ID_BUTTON_Right2		"ID_BUTTON_Right2"
#endif  ID_BUTTON_Right2
#ifndef ID_BUTTON_Left1
#define ID_BUTTON_Left1		"ID_BUTTON_Left1"
#endif  ID_BUTTON_Left1
#ifndef ID_BUTTON_Left2
#define ID_BUTTON_Left2		"ID_BUTTON_Left2"
#endif  ID_BUTTON_Left2
#ifndef ID_BUTTON_UnchainLock
#define ID_BUTTON_UnchainLock		"ID_BUTTON_UnchainLock"
#endif  ID_BUTTON_UnchainLock
#ifndef ID_PICTURE_SD1
#define ID_PICTURE_SD1 "ID_PICTURE_SD1"
#endif ID_PICTURE_SD1
#ifndef ID_PICTURE_SD2
#define ID_PICTURE_SD2 "ID_PICTURE_SD2"
#endif ID_PICTURE_SD2
class CUI_ID_FRAME_SuAnimalMore : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_SuAnimalMore();
	 ControlFrame*	m_pID_FRAME_SuAnimalMore;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlPicture*	m_pID_PICTURE_Pet1;
	 ControlPicture*	m_pID_PICTURE_Pet2;
	 ControlText*	m_pID_TEXT_Result1;
	 ControlText*	m_pID_TEXT_Level1;
	 ControlText*	m_pID_TEXT_Level2;
	 ControlText*	m_pID_TEXT_Generation1;
	 ControlText*	m_pID_TEXT_Generation2;
	 ControlText*	m_pID_TEXT_Result2;
	 ControlText*	m_pID_TEXT_StrengthZ;
	 ControlText*	m_pID_TEXT_AgilityZ;
	 ControlText*	m_pID_TEXT_StaminaZ;
	 ControlText*	m_pID_TEXT_IntellectZ;
	 ControlText*	m_pID_TEXT_Strength;
	 ControlText*	m_pID_TEXT_Agility;
	 ControlText*	m_pID_TEXT_Stamina;
	 ControlText*	m_pID_TEXT_Intellect;
	 ControlText*	m_pID_TEXT_NeedMoney;
	 ControlText*	m_pID_TEXT_CurrentMoney;
	 ControlListImage*	m_pID_LISTIMG_Skill1;
	 ControlListImage*	m_pID_LISTIMG_Skill2;
	 ControlComboBox*	m_pID_COMBOBOX_SelectPet1;
	 ControlComboBox*	m_pID_COMBOBOX_SelectPet2;
	 ControlList*	m_pID_LIST_Pet;
	 ControlText*	m_pID_TEXT_PartnerPetName;
	 ControlText*	m_pID_TEXT_MyPetName;
	 ControlText*	m_pID_TEXT_Info1;
	 ControlButton*	m_pID_BUTTON_ChangePet;
	 ControlButton*	m_pID_BUTTON_LookPet;
	 ControlText*	m_pID_TEXT_Info2;
	 ControlButton*	m_pID_BUTTON_LookPartnerPet;
	 ControlButton*	m_pID_BUTTON_Lock;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_Right1;
	 ControlButton*	m_pID_BUTTON_Right2;
	 ControlButton*	m_pID_BUTTON_Left1;
	 ControlButton*	m_pID_BUTTON_Left2;
	 ControlButton*	m_pID_BUTTON_UnchainLock;
	 ControlPicture * m_pID_PICTURE_SD1;
	 ControlPicture * m_pID_PICTURE_SD2;
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Skill1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Skill1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Skill2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Skill2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_COMBOBOX_SelectPet1OnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_SelectPet2OnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_LIST_PetOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_ChangePetOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LookPetOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LookPartnerPetOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LockOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Right1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Right2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Left1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Left2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UnchainLockOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
protected:
	static void OnVisibleChange( ControlObject* pUIObject ); 
	void        Refresh();
	void        RenderViewport();
public:
	void        ResetControls();
	void        RefreshMoney();
	void        ShowAllPet();
	void        ReqPetBreed(); 
    bool        IsTeamLeader( const char* playerName );//是否队长
	void        SendSelPetReg(int nIndex);
	void        RegLockPet();
	void        ConfirmPetBreed();
	void        CancelPetBreed();
	void        SetMyPetItem(SPetItem* pItem);
	void        SetTargetPetItem(SPetItem *pItem);
	void        SetMyLockItem(bool bValue) ;
	void        SetTargetLockItem(bool bValue);
	void        ClearTargetStatus();
	void		RefreshByMoneyChange();//从uibase中继承过来的虚函数，用来当金钱改变时刷新当前金钱数目
private:
	CPlayerAnim* m_pPlayerAnim1;
	CPlayer*     m_pPlayer1;
	CPlayerAnim* m_pPlayerAnim2;
	CPlayer*     m_pPlayer2;
	int             m_nMountId1;
	int             m_nMountId2;
	float               m_fRotateZ1;
	float               m_fRotateZ2;
protected:
	SPetItem        m_sPetItem;
	SPetItem        m_sTargetItem;
	bool            m_bMyLock;
	bool            m_bTargetLock;
};
extern CUI_ID_FRAME_SuAnimalMore s_CUI_ID_FRAME_SuAnimalMore;
