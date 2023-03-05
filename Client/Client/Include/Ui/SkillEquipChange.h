/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\SkillEquipChange.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "EquipUIHelper.h"
#include "MeUi/Animation/SlideAnimation.h"

#ifndef ID_FRAME_SkillEquipChange
#define ID_FRAME_SkillEquipChange		"ID_FRAME_SkillEquipChange"
#endif  ID_FRAME_SkillEquipChange
#ifndef ID_PICTURE_RightTitle
#define ID_PICTURE_RightTitle		"ID_PICTURE_RightTitle"
#endif  ID_PICTURE_RightTitle
#ifndef ID_PICTURE_MiddleTitle
#define ID_PICTURE_MiddleTitle		"ID_PICTURE_MiddleTitle"
#endif  ID_PICTURE_MiddleTitle
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_PICTURE_ItemWall
#define ID_PICTURE_ItemWall		"ID_PICTURE_ItemWall"
#endif  ID_PICTURE_ItemWall
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_UseMoneyZ
#define ID_TEXT_UseMoneyZ		"ID_TEXT_UseMoneyZ"
#endif  ID_TEXT_UseMoneyZ
#ifndef ID_TEXT_UseMoney
#define ID_TEXT_UseMoney		"ID_TEXT_UseMoney"
#endif  ID_TEXT_UseMoney
#ifndef ID_PICTURE_LeftTitle
#define ID_PICTURE_LeftTitle		"ID_PICTURE_LeftTitle"
#endif  ID_PICTURE_LeftTitle
#ifndef ID_PICTURE_TitleWord
#define ID_PICTURE_TitleWord		"ID_PICTURE_TitleWord"
#endif  ID_PICTURE_TitleWord
#ifndef ID_PICTURE_ItemWall1
#define ID_PICTURE_ItemWall1		"ID_PICTURE_ItemWall1"
#endif  ID_PICTURE_ItemWall1
#ifndef ID_PICTURE_ItemWall2
#define ID_PICTURE_ItemWall2		"ID_PICTURE_ItemWall2"
#endif  ID_PICTURE_ItemWall2
#ifndef ID_LISTIMG_Material1
#define ID_LISTIMG_Material1		"ID_LISTIMG_Material1"
#endif  ID_LISTIMG_Material1
#ifndef ID_BUTTON_Sure
#define ID_BUTTON_Sure		"ID_BUTTON_Sure"
#endif  ID_BUTTON_Sure
#ifndef ID_PICTURE_TitleWordReturn
#define ID_PICTURE_TitleWordReturn		"ID_PICTURE_TitleWordReturn"
#endif  ID_PICTURE_TitleWordReturn
#ifndef ID_LISTIMG_Material2
#define ID_LISTIMG_Material2		"ID_LISTIMG_Material2"
#endif  ID_LISTIMG_Material2
#ifndef ID_TEXT_ChangeInfo
#define ID_TEXT_ChangeInfo		"ID_TEXT_ChangeInfo"
#endif  ID_TEXT_ChangeInfo
#ifndef ID_BUTTON_Reset
#define ID_BUTTON_Reset		"ID_BUTTON_Reset"
#endif  ID_BUTTON_Reset


#include "UiBase.h"
class CUI_ID_FRAME_SkillEquipChange : public EquipUIHelper<2> ,public CUIBase
{
	// Member
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_SkillEquipChange;
	//ControlPicture*	m_pID_PICTURE_RightTitle;
	ControlPicture*	m_pID_PICTURE_MiddleTitle;
// 	ControlButton*	m_pID_BUTTON_CLOSE;
// 	ControlButton*	m_pID_BUTTON_help;
	ControlPicture*	m_pID_PICTURE_ItemWall;
	ControlListImage*	m_pID_LISTIMG_Armour;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlText*	m_pID_TEXT_UseMoneyZ;
	ControlText*	m_pID_TEXT_UseMoney;
// 	ControlPicture*	m_pID_PICTURE_LeftTitle;
// 	ControlPicture*	m_pID_PICTURE_TitleWord;
	ControlPicture*	m_pID_PICTURE_ItemWall1;
	ControlPicture*	m_pID_PICTURE_ItemWall2;
	ControlListImage*	m_pID_LISTIMG_Material1;
	ControlButton*	m_pID_BUTTON_Sure;
	//ControlPicture*	m_pID_PICTURE_TitleWordReturn;
	ControlListImage*	m_pID_LISTIMG_Material2;
	ControlText*	m_pID_TEXT_ChangeInfo;
	ControlButton*	m_pID_BUTTON_Reset;

public:	
	CUI_ID_FRAME_SkillEquipChange();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
// 	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_SureOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_ResetOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void OnAck(MsgSuitChangeAck* pAck);
private:
	virtual bool _CanSetEquipCallback(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag, ItemDefine::SItemCanEquip* pDragItemCanEquip);
	virtual bool _CanSetMaterial0Callback(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag, ItemDefine::SItemCommon* pDragItemCommon);
	virtual bool _CanSetMaterial1Callback(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag, ItemDefine::SItemCommon* pDragItemCommon);

	virtual void _SetEquipCallback(ControlIconDrag::S_ListImg& item);
	virtual void _SetMaterial0Callback(ControlIconDrag::S_ListImg& item);
	virtual void _SetMaterial1Callback(ControlIconDrag::S_ListImg& item);

	virtual void _ClearEquipCallback();
	virtual void _ClearMaterial0Callback();
	virtual void _ClearMaterial1Callback();

	// 刷新控件状态
	void RefreshControls();
	void ShowControls(bool bInitializeStatus);
	// 显示升级结果
	void ShowResult();
	// 是否可以放入道具
	bool IsActived();

	void OnOk();

	static void OnVisibleChanged(ControlObject* pSender);	

	CSlideAnimation m_slideAnim;

	bool m_hasAck;
	bool m_isStart;
	unsigned short m_result;
};
extern CUI_ID_FRAME_SkillEquipChange s_CUI_ID_FRAME_SkillEquipChange;
