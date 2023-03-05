/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\宠物\PetStudy.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include "PlayerAnimCtrl.h"
#include "UIBase.h"

#ifndef ID_FRAME_PetStudy
#define ID_FRAME_PetStudy		"ID_FRAME_SuAnimalStudy"
#endif  ID_FRAME_PetStudy
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Yes
#define ID_BUTTON_Yes	 "ID_BUTTON_Yes"
#endif ID_BUTTON_Yes
#ifndef ID_BUTTON_CANCEL
#define ID_BUTTON_CANCEL "ID_BUTTON_Cancel"
#endif ID_BUTTON_CANCEL
#ifndef ID_TEXT_TitleTop
#define ID_TEXT_TitleTop		"ID_TEXT_TitleTop"
#endif  ID_TEXT_TitleTop
#ifndef ID_PICTURE_PetModel
#define ID_PICTURE_PetModel		"ID_PICTURE_PetModel"
#endif  ID_PICTURE_PetModel
#ifndef ID_BUTTON_ToLeft
#define ID_BUTTON_ToLeft		"ID_BUTTON_ToLeft"
#endif  ID_BUTTON_ToLeft
#ifndef ID_BUTTON_ToRight
#define ID_BUTTON_ToRight		"ID_BUTTON_ToRight"
#endif  ID_BUTTON_ToRight
#ifndef ID_LISTIMG_PetSkill
#define ID_LISTIMG_PetSkill		"ID_LISTIMG_PetSkill"
#endif  ID_LISTIMG_PetSkill
#ifndef ID_TEXT_PetLv
#define ID_TEXT_PetLv		"ID_TEXT_PetLv"
#endif  ID_TEXT_PetLv
#ifndef ID_LISTIMG_PetStudySkill
#define ID_LISTIMG_PetStudySkill		"ID_LISTIMG_PetStudySkill"
#endif  ID_LISTIMG_PetStudySkill
#ifndef ID_PICTURE_Motherboard
#define ID_PICTURE_Motherboard		"ID_PICTURE_Motherboard"
#endif  ID_PICTURE_Motherboard
#ifndef ID_TEXT_PetNameTitle
#define ID_TEXT_PetNameTitle		"ID_TEXT_PetNameTitle"
#endif  ID_TEXT_PetNameTitle
#ifndef ID_LIST_PetName
#define ID_LIST_PetName		"ID_LIST_PetName"
#endif  ID_LIST_PetName
#ifndef ID_BUTTON_Choice
#define ID_BUTTON_Choice		"ID_BUTTON_Choice"
#endif  ID_BUTTON_Choice
#ifndef ID_BUTTON_Examine
#define ID_BUTTON_Examine		"ID_BUTTON_Examine"
#endif  ID_BUTTON_Examine
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain
#ifndef ID_TEXT_ConsumeMoney
#define ID_TEXT_ConsumeMoney		"ID_TEXT_ConsumeMoney"
#endif  ID_TEXT_ConsumeMoney
#ifndef ID_TEXT_LockedMoney
#define ID_TEXT_LockedMoney		"ID_TEXT_LockedMoney"
#endif  ID_TEXT_LockedMoney
#ifndef ID_TEXT_CurrentMoney
#define ID_TEXT_CurrentMoney		"ID_TEXT_CurrentMoney"
#endif  ID_TEXT_CurrentMoney

class CUI_ID_FRAME_SuAnimalStudy:public CUIBase
{
	// Member
private:	

	 ControlFrame*	m_pID_FRAME_PetStudy;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_TitleTop;
	 ControlPicture*	m_pID_PICTURE_PetModel;
	 ControlButton*	m_pID_BUTTON_ToLeft;
	 ControlButton*	m_pID_BUTTON_ToRight;
	 ControlListImage*	m_pID_LISTIMG_PetSkill;
	 ControlText*	m_pID_TEXT_PetLv;
	 ControlListImage*	m_pID_LISTIMG_PetStudySkill;
	 ControlPicture*	m_pID_PICTURE_Motherboard;
	 ControlText*	m_pID_TEXT_PetNameTitle;
	 ControlList*	m_pID_LIST_PetName;
	 ControlButton*	m_pID_BUTTON_Choice;
	 ControlButton*	m_pID_BUTTON_Examine;
	 ControlText*	m_pID_TEXT_Explain;
	 ControlText*	m_pID_TEXT_ConsumeMoney;
	 ControlText*	m_pID_TEXT_LockedMoney;
	 ControlText*	m_pID_TEXT_CurrentMoney;
	 ControlButton *m_pID_BUTTON_YES;
	 ControlButton *m_pID_BUTTON_CANCEL;

public:	
	// Frame
	CUI_ID_FRAME_SuAnimalStudy();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ToLeftOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ToRightOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_PetSkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetSkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetSkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetSkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetStudySkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetStudySkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetStudySkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetStudySkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_ChoiceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ExamineOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_YESONButtonClick(ControlObject *pSender);
	bool ID_BUTTON_CANCELOnButtonClick(ControlObject *pSender);
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetRotate(bool bRotate) {m_bRotate = bRotate;}
private:	
	int m_nLastHeight;
	bool m_bNeedRefresh;
	bool m_bRotate;
	float m_fRotateZ;

	CPlayer*			m_pPlayer;
	CPlayerAnim*        m_pPlayerAnim;
	int                 m_nModelId; //模型ID
public:
	void RefreshMoney();  //刷钱
	void Refresh_Help(bool _is);

	void SetNeed_Refresh(bool _need) {m_bNeedRefresh = _need;}
	void Refresh(bool bNeed) {SetNeed_Refresh(true); }
	static bool UIPetMaterialUp_LeftLBD(INT x,INT y);
	static bool UIPetMaterialUp_RightLBD(INT nX,INT nY);
	void 		RenderViewport();
	SPetItem &GetSelectPet();
	void PetSelectChange(int nindex);
	void RenderMount( int nMountId, CPlayerAnim* pAnim, float fRotateZ, const RECT& rt );
	void ChangeModel(SPetItem& mount, CPlayerAnim* pAnim, int& iOldModelId);
	bool DragItemOn(int index, ControlIconDrag::S_ListImg* pItemDrag, ControlObject* pSender);
private:
	struct  Item_PetStudy 
	{
		Item_PetStudy() {  memset(this,0,sizeof(Item_PetStudy)); }
		uint16  ustItemID; // 物品ID
		__int64 nOnlyInt ; // 物品世界唯一ID
		int         n_index; //背包中的索引位置
	};
	Item_PetStudy  item_info;//升级道具信息
public:
	bool  IsTypeMatch(ControlIconDrag::S_ListImg* pItemDrag);//道具类型匹配
	bool  RefreshMountSkill(SPetItem &mount);
	bool  IsSkillList(const ControlObject *pobject);
	bool  ReadyOk();
	short GetCurrentMountIndex();
	void RefreshItemInfo();
	void RefreshPetList();
	void RefreshByMoneyChange();//从uibase中继承过来的虚函数，用来当金钱改变时刷新当前金钱数目
};
extern CUI_ID_FRAME_SuAnimalStudy s_CUI_ID_FRAME_SuAnimalStudy;

