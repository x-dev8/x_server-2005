/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\MoveStar.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "MessageDefine.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_MoveStar
#define ID_FRAME_MoveStar		"ID_FRAME_MoveStar"
#endif  ID_FRAME_MoveStar
#ifndef ID_PICTURE_DI2
#define ID_PICTURE_DI2		"ID_PICTURE_DI2"
#endif  ID_PICTURE_DI2
#ifndef ID_PICTURE_title2
#define ID_PICTURE_title2		"ID_PICTURE_title2"
#endif  ID_PICTURE_title2
#ifndef ID_PICTURE_title
#define ID_PICTURE_title		"ID_PICTURE_title"
#endif  ID_PICTURE_title
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_TEXT_ItemWall
#define ID_TEXT_ItemWall		"ID_TEXT_ItemWall"
#endif  ID_TEXT_ItemWall
#ifndef ID_PICTURE_ItemWall
#define ID_PICTURE_ItemWall		"ID_PICTURE_ItemWall"
#endif  ID_PICTURE_ItemWall
#ifndef ID_PICTURE_TargetWall
#define ID_PICTURE_TargetWall		"ID_PICTURE_TargetWall"
#endif  ID_PICTURE_TargetWall
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_LISTIMG_Especial
#define ID_LISTIMG_Especial		"ID_LISTIMG_Especial"
#endif  ID_LISTIMG_Especial
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_UseMoneyZ
#define ID_TEXT_UseMoneyZ		"ID_TEXT_UseMoneyZ"
#endif  ID_TEXT_UseMoneyZ
#ifndef ID_TEXT_TargetPrompt
#define ID_TEXT_TargetPrompt		"ID_TEXT_TargetPrompt"
#endif  ID_TEXT_TargetPrompt
#ifndef ID_TEXT_UseMoney
#define ID_TEXT_UseMoney		"ID_TEXT_UseMoney"
#endif  ID_TEXT_UseMoney
#ifndef ID_LIST_ArmourProperty
#define ID_LIST_ArmourProperty		"ID_LIST_ArmourProperty"
#endif  ID_LIST_ArmourProperty
#ifndef ID_LIST_TargetProperty
#define ID_LIST_TargetProperty		"ID_LIST_TargetProperty"
#endif  ID_LIST_TargetProperty
#ifndef ID_PICTURE_Gray
#define ID_PICTURE_Gray		"ID_PICTURE_Gray"
#endif  ID_PICTURE_Gray
#ifndef ID_PICTURE_Yellow
#define ID_PICTURE_Yellow		"ID_PICTURE_Yellow"
#endif  ID_PICTURE_Yellow
#ifndef ID_PICTURE_ItemGray
#define ID_PICTURE_ItemGray		"ID_PICTURE_ItemGray"
#endif  ID_PICTURE_ItemGray
#ifndef ID_PICTURE_Star9
#define ID_PICTURE_Star9		"ID_PICTURE_Star9"
#endif  ID_PICTURE_Star9
#ifndef ID_TEXT_Star
#define ID_TEXT_Star		"ID_TEXT_Star"
#endif  ID_TEXT_Star
#ifndef ID_PICTURE_Star18
#define ID_PICTURE_Star18		"ID_PICTURE_Star18"
#endif  ID_PICTURE_Star18
#ifndef ID_PICTURE_Star17
#define ID_PICTURE_Star17		"ID_PICTURE_Star17"
#endif  ID_PICTURE_Star17
#ifndef ID_PICTURE_Star16
#define ID_PICTURE_Star16		"ID_PICTURE_Star16"
#endif  ID_PICTURE_Star16
#ifndef ID_PICTURE_Star15
#define ID_PICTURE_Star15		"ID_PICTURE_Star15"
#endif  ID_PICTURE_Star15
#ifndef ID_PICTURE_Star14
#define ID_PICTURE_Star14		"ID_PICTURE_Star14"
#endif  ID_PICTURE_Star14
#ifndef ID_PICTURE_Star13
#define ID_PICTURE_Star13		"ID_PICTURE_Star13"
#endif  ID_PICTURE_Star13
#ifndef ID_PICTURE_Star12
#define ID_PICTURE_Star12		"ID_PICTURE_Star12"
#endif  ID_PICTURE_Star12
#ifndef ID_PICTURE_Star11
#define ID_PICTURE_Star11		"ID_PICTURE_Star11"
#endif  ID_PICTURE_Star11
#ifndef ID_PICTURE_Star10
#define ID_PICTURE_Star10		"ID_PICTURE_Star10"
#endif  ID_PICTURE_Star10
#ifndef ID_PICTURE_Star8
#define ID_PICTURE_Star8		"ID_PICTURE_Star8"
#endif  ID_PICTURE_Star8
#ifndef ID_PICTURE_Star7
#define ID_PICTURE_Star7		"ID_PICTURE_Star7"
#endif  ID_PICTURE_Star7
#ifndef ID_PICTURE_Star6
#define ID_PICTURE_Star6		"ID_PICTURE_Star6"
#endif  ID_PICTURE_Star6
#ifndef ID_PICTURE_Star5
#define ID_PICTURE_Star5		"ID_PICTURE_Star5"
#endif  ID_PICTURE_Star5
#ifndef ID_PICTURE_Star4
#define ID_PICTURE_Star4		"ID_PICTURE_Star4"
#endif  ID_PICTURE_Star4
#ifndef ID_PICTURE_Star3
#define ID_PICTURE_Star3		"ID_PICTURE_Star3"
#endif  ID_PICTURE_Star3
#ifndef ID_PICTURE_Star2
#define ID_PICTURE_Star2		"ID_PICTURE_Star2"
#endif  ID_PICTURE_Star2
#ifndef ID_PICTURE_Star1
#define ID_PICTURE_Star1		"ID_PICTURE_Star1"
#endif  ID_PICTURE_Star1
#ifndef ID_PICTURE_Star0
#define ID_PICTURE_Star0		"ID_PICTURE_Star0"
#endif  ID_PICTURE_Star0
#ifndef ID_LISTIMG_Especial2
#define ID_LISTIMG_Especial2		"ID_LISTIMG_Especial2"
#endif  ID_LISTIMG_Especial2
#ifndef ID_LISTIMG_Target
#define ID_LISTIMG_Target		"ID_LISTIMG_Target"
#endif  ID_LISTIMG_Target
#ifndef ID_TEXT_NextStar
#define ID_TEXT_NextStar		"ID_TEXT_NextStar"
#endif  ID_TEXT_NextStar
#ifndef ID_PICTURE_NextStar18
#define ID_PICTURE_NextStar18		"ID_PICTURE_NextStar18"
#endif  ID_PICTURE_NextStar18
#ifndef ID_PICTURE_NextStar17
#define ID_PICTURE_NextStar17		"ID_PICTURE_NextStar17"
#endif  ID_PICTURE_NextStar17
#ifndef ID_PICTURE_NextStar16
#define ID_PICTURE_NextStar16		"ID_PICTURE_NextStar16"
#endif  ID_PICTURE_NextStar16
#ifndef ID_PICTURE_NextStar15
#define ID_PICTURE_NextStar15		"ID_PICTURE_NextStar15"
#endif  ID_PICTURE_NextStar15
#ifndef ID_PICTURE_NextStar14
#define ID_PICTURE_NextStar14		"ID_PICTURE_NextStar14"
#endif  ID_PICTURE_NextStar14
#ifndef ID_PICTURE_NextStar13
#define ID_PICTURE_NextStar13		"ID_PICTURE_NextStar13"
#endif  ID_PICTURE_NextStar13
#ifndef ID_PICTURE_NextStar12
#define ID_PICTURE_NextStar12		"ID_PICTURE_NextStar12"
#endif  ID_PICTURE_NextStar12
#ifndef ID_PICTURE_NextStar11
#define ID_PICTURE_NextStar11		"ID_PICTURE_NextStar11"
#endif  ID_PICTURE_NextStar11
#ifndef ID_PICTURE_NextStar10
#define ID_PICTURE_NextStar10		"ID_PICTURE_NextStar10"
#endif  ID_PICTURE_NextStar10
#ifndef ID_PICTURE_NextStar9
#define ID_PICTURE_NextStar9		"ID_PICTURE_NextStar9"
#endif  ID_PICTURE_NextStar9
#ifndef ID_PICTURE_NextStar8
#define ID_PICTURE_NextStar8		"ID_PICTURE_NextStar8"
#endif  ID_PICTURE_NextStar8
#ifndef ID_PICTURE_NextStar7
#define ID_PICTURE_NextStar7		"ID_PICTURE_NextStar7"
#endif  ID_PICTURE_NextStar7
#ifndef ID_PICTURE_NextStar6
#define ID_PICTURE_NextStar6		"ID_PICTURE_NextStar6"
#endif  ID_PICTURE_NextStar6
#ifndef ID_PICTURE_NextStar5
#define ID_PICTURE_NextStar5		"ID_PICTURE_NextStar5"
#endif  ID_PICTURE_NextStar5
#ifndef ID_PICTURE_NextStar4
#define ID_PICTURE_NextStar4		"ID_PICTURE_NextStar4"
#endif  ID_PICTURE_NextStar4
#ifndef ID_PICTURE_NextStar3
#define ID_PICTURE_NextStar3		"ID_PICTURE_NextStar3"
#endif  ID_PICTURE_NextStar3
#ifndef ID_PICTURE_NextStar2
#define ID_PICTURE_NextStar2		"ID_PICTURE_NextStar2"
#endif  ID_PICTURE_NextStar2
#ifndef ID_PICTURE_NextStar1
#define ID_PICTURE_NextStar1		"ID_PICTURE_NextStar1"
#endif  ID_PICTURE_NextStar1
#ifndef ID_PICTURE_NextStar0
#define ID_PICTURE_NextStar0		"ID_PICTURE_NextStar0"
#endif  ID_PICTURE_NextStar0
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_PICTURE_MoveStarEffect
#define ID_PICTURE_MoveStarEffect		"ID_PICTURE_MoveStarEffect"
#endif  ID_PICTURE_MoveStarEffect
#ifndef ID_TEXT_TargetPrompt2
#define ID_TEXT_TargetPrompt2		"ID_TEXT_TargetPrompt2"
#endif  ID_TEXT_TargetPrompt2

#include "UiBase.h"
class CUI_ID_FRAME_MoveStar :public CUIBase, CItemEnableChangeSysBase
{
	// Member
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_MoveStar;
	ControlPicture*	m_pID_PICTURE_DI2;
	ControlPicture*	m_pID_PICTURE_title2;
	//ControlPicture*	m_pID_PICTURE_title;
// 	ControlButton*	m_pID_BUTTON_CLOSE;
// 	ControlButton*	m_pID_BUTTON_help;
// 	ControlText*	m_pID_TEXT_ItemWall;
// 	ControlPicture*	m_pID_PICTURE_ItemWall;
// 	ControlPicture*	m_pID_PICTURE_TargetWall;
	ControlListImage*	m_pID_LISTIMG_Material;
	ControlListImage*	m_pID_LISTIMG_Armour;
	//ControlListImage*	m_pID_LISTIMG_Especial;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlText*	m_pID_TEXT_UseMoneyZ;
	//ControlText*	m_pID_TEXT_TargetPrompt;
	ControlText*	m_pID_TEXT_UseMoney;
	ControlList*	m_pID_LIST_ArmourProperty;
	ControlList*	m_pID_LIST_TargetProperty;
// 	ControlPicture*	m_pID_PICTURE_Gray;
// 	ControlPicture*	m_pID_PICTURE_Yellow;
// 	ControlPicture*	m_pID_PICTURE_ItemGray;
	ControlPicture*	m_pID_PICTURE_Star9;
	//ControlText*	m_pID_TEXT_Star;
	ControlPicture*	m_pID_PICTURE_Star18;
	ControlPicture*	m_pID_PICTURE_Star17;
	ControlPicture*	m_pID_PICTURE_Star16;
	ControlPicture*	m_pID_PICTURE_Star15;
	ControlPicture*	m_pID_PICTURE_Star14;
	ControlPicture*	m_pID_PICTURE_Star13;
	ControlPicture*	m_pID_PICTURE_Star12;
	ControlPicture*	m_pID_PICTURE_Star11;
	ControlPicture*	m_pID_PICTURE_Star10;
	ControlPicture*	m_pID_PICTURE_Star8;
	ControlPicture*	m_pID_PICTURE_Star7;
	ControlPicture*	m_pID_PICTURE_Star6;
	ControlPicture*	m_pID_PICTURE_Star5;
	ControlPicture*	m_pID_PICTURE_Star4;
	ControlPicture*	m_pID_PICTURE_Star3;
	ControlPicture*	m_pID_PICTURE_Star2;
	ControlPicture*	m_pID_PICTURE_Star1;
	ControlPicture*	m_pID_PICTURE_Star0;
	//ControlListImage*	m_pID_LISTIMG_Especial2;
	ControlListImage*	m_pID_LISTIMG_Target;
	//ControlText*	m_pID_TEXT_NextStar;
	ControlPicture*	m_pID_PICTURE_NextStar18;
	ControlPicture*	m_pID_PICTURE_NextStar17;
	ControlPicture*	m_pID_PICTURE_NextStar16;
	ControlPicture*	m_pID_PICTURE_NextStar15;
	ControlPicture*	m_pID_PICTURE_NextStar14;
	ControlPicture*	m_pID_PICTURE_NextStar13;
	ControlPicture*	m_pID_PICTURE_NextStar12;
	ControlPicture*	m_pID_PICTURE_NextStar11;
	ControlPicture*	m_pID_PICTURE_NextStar10;
	ControlPicture*	m_pID_PICTURE_NextStar9;
	ControlPicture*	m_pID_PICTURE_NextStar8;
	ControlPicture*	m_pID_PICTURE_NextStar7;
	ControlPicture*	m_pID_PICTURE_NextStar6;
	ControlPicture*	m_pID_PICTURE_NextStar5;
	ControlPicture*	m_pID_PICTURE_NextStar4;
	ControlPicture*	m_pID_PICTURE_NextStar3;
	ControlPicture*	m_pID_PICTURE_NextStar2;
	ControlPicture*	m_pID_PICTURE_NextStar1;
	ControlPicture*	m_pID_PICTURE_NextStar0;
	//ControlPicture*	m_pID_PICTURE_Title;
	ControlPicture*	m_pID_PICTURE_MoveStarEffect;
//	ControlText*	m_pID_TEXT_TargetPrompt2;

	ControlGroup		m_StarGroup;
	ControlGroup		m_NextStarGroup;

public:	
	CUI_ID_FRAME_MoveStar();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
// 	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EspecialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_EspecialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EspecialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_EspecialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	void ID_LIST_ArmourPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_TargetPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
// 	bool ID_LISTIMG_Especial2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
// 	bool ID_LISTIMG_Especial2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_Especial2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_Especial2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_TargetOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	void SetVisable( const bool bVisable, MsgMoveStarReq::EConstDefine type );			// 设置是否可视

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable, MsgMoveStarReq::EConstDefine type );			// 设置是否可视

public:
	void MoveStar(char result, unsigned char chStarLevel, bool bBound);
    virtual bool IsPackItemBeUsing( __int64 nGuid );

private:
	MsgMoveStarReq::EConstDefine m_type; 

	void UpdateInfo(SCharItem* pItem, ControlList* pList);

	void SetEquipBagIndex(int index, bool enable);
	void SetEquip(ControlIconDrag::S_ListImg* pItem);
	bool SetEquip(ControlObject* pSender, ControlIconDrag::S_ListImg* pItem);

	void SetMoveStarItemBagIndex(int index, bool enable);
	void SetMoveStarItem(ControlIconDrag::S_ListImg* pItem);
	bool SetMoveStarItem_(ControlObject* pSender, ControlIconDrag::S_ListImg* pItem);

	ControlIconDrag::S_ListImg* FindZeroStarItem();
	ControlIconDrag::S_ListImg* FindStarItem();

	void RefreshAllBagEnable();

	void ClearInfo();
	void ClearAnim();

	void ShowStar( int nStar );
	void ShowNextStar( int nStar );

	void SetAtomVisible( bool bVisible );

	static void OnVisibleChanged(ControlObject* pSender);

	Vector m_vVisiblePos;

	int m_equipBagIndex;
	bool m_equipEnable; 

	int m_moveStarItemBagIndex;
	bool m_moveStarItemEnable; 

	int m_bNeedUpdate;

	bool m_bShowError;

	CSlideAnimation m_slideAnim;			//序列帧动画
	bool			m_bStartAnim;

	bool			m_bStartIntonate;
	int				m_nIntonateTime;		// 吟唱时间，毫秒
	DWORD			m_dwStartIntonateTime;	// 开始吟唱时间
};
extern CUI_ID_FRAME_MoveStar s_CUI_ID_FRAME_MoveStar;
