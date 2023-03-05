/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\HeroRuntime\CLIENT\UI\SeekEquip.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "..\PlayerAnimCtrl.h"
#include "GlobalDef.h"
#include "MessageDefine.h"

#ifndef ID_FRAME_SeekEqup
#define ID_FRAME_SeekEqup		"ID_FRAME_SeekEqup"
#endif  ID_FRAME_SeekEqup
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_LISTIMG_Head
#define ID_LISTIMG_Head		"ID_LISTIMG_Head"
#endif  ID_LISTIMG_Head
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_LISTIMG_rWeapon
#define ID_LISTIMG_rWeapon		"ID_LISTIMG_rWeapon"
#endif  ID_LISTIMG_rWeapon

#ifndef ID_LISTIMG_Weapon2
#define ID_LISTIMG_Weapon2	"ID_LISTIMG_Weapon2"
#endif  ID_LISTIMG_Weapon2

#ifndef ID_LISTIMG_Temp1
#define ID_LISTIMG_Temp1		"ID_LISTIMG_Temp1"
#endif  ID_LISTIMG_Temp1
#ifndef ID_LISTIMG_Shoe
#define ID_LISTIMG_Shoe		"ID_LISTIMG_Shoe"
#endif  ID_LISTIMG_Shoe
#ifndef ID_LISTIMG_Ring1
#define ID_LISTIMG_Ring1		"ID_LISTIMG_Ring1"
#endif  ID_LISTIMG_Ring1

#ifndef ID_LISTIMG_Ring2
#define ID_LISTIMG_Ring2		"ID_LISTIMG_Ring2"
#endif  ID_LISTIMG_Ring2

#ifndef ID_LISTIMG_Bangle1
#define ID_LISTIMG_Bangle1 "ID_LISTIMG_Bangle1"
#endif  ID_LISTIMG_Bangle1

#ifndef ID_LISTIMG_Bangle2
#define ID_LISTIMG_Bangle2 "ID_LISTIMG_Bangle2"
#endif  ID_LISTIMG_Bangle2

#ifndef ID_LISTIMG_Amulet
#define ID_LISTIMG_Amulet	"ID_LISTIMG_Amulet"
#endif  ID_LISTIMG_Amulet

#ifndef ID_LISTIMG_Symbol
#define ID_LISTIMG_Symbol		"ID_LISTIMG_Symbol"
#endif  ID_LISTIMG_Symbol
#ifndef ID_LISTIMG_Glove
#define ID_LISTIMG_Glove		"ID_LISTIMG_Glove"
#endif  ID_LISTIMG_Glove
#ifndef ID_LISTIMG_Shield
#define ID_LISTIMG_Shield		"ID_LISTIMG_Shield"
#endif  ID_LISTIMG_Shield
#ifndef ID_LISTIMG_Temp
#define ID_LISTIMG_Temp		"ID_LISTIMG_Temp"
#endif  ID_LISTIMG_Temp
#ifndef ID_LISTIMG_Accouterment1
#define ID_LISTIMG_Accouterment1		"ID_LISTIMG_Accouterment1"
#endif  ID_LISTIMG_Accouterment1
#ifndef ID_LISTIMG_Ring1
#define ID_LISTIMG_Ring1		"ID_LISTIMG_Ring1"
#endif  ID_LISTIMG_Ring1
#ifndef ID_LISTIMG_Accouterment
#define ID_LISTIMG_Accouterment		"ID_LISTIMG_Accouterment"
#endif  ID_LISTIMG_Accouterment
#ifndef ID_LISTIMG_lWeapon
#define ID_LISTIMG_lWeapon		"ID_LISTIMG_lWeapon"
#endif  ID_LISTIMG_lWeapon
#ifndef ID_BUTTON_LOCK
#define ID_BUTTON_LOCK		"ID_BUTTON_LOCK"
#endif  ID_BUTTON_LOCK
#ifndef ID_BUTTON_UNLOCK
#define ID_BUTTON_UNLOCK		"ID_BUTTON_UNLOCK"
#endif  ID_BUTTON_UNLOCK
#ifndef ID_LISTIMG_Necklace
#define ID_LISTIMG_Necklace		"ID_LISTIMG_Necklace"
#endif  ID_LISTIMG_Necklace
#ifndef ID_BUTTON_help
#define ID_BUTTON_help	"ID_BUTTON_help"
#endif ID_BUTTON_help
#ifndef ID_BUTTON_Right
#define ID_BUTTON_Right		"ID_BUTTON_Right"
#endif  ID_BUTTON_Right
#ifndef ID_BUTTON_Left
#define ID_BUTTON_Left		"ID_BUTTON_Left"
#endif  ID_BUTTON_Left
#ifndef ID_LISTIMG_Fashionhead
#define ID_LISTIMG_Fashionhead		"ID_LISTIMG_Fashionhead"
#endif  ID_LISTIMG_Fashionhead
#ifndef ID_LISTIMG_Fashionarmour
#define ID_LISTIMG_Fashionarmour		"ID_LISTIMG_Fashionarmour"
#endif  ID_LISTIMG_Fashionarmour
#ifndef ID_LISTIMG_Fashionglove
#define ID_LISTIMG_Fashionglove		"ID_LISTIMG_Fashionglove"
#endif  ID_LISTIMG_Fashionglove
#ifndef ID_LISTIMG_Fashionshoe
#define ID_LISTIMG_Fashionshoe		"ID_LISTIMG_Fashionshoe"
#endif  ID_LISTIMG_Fashionshoe

#ifndef ID_BUTTON_Pet
#define ID_BUTTON_Pet		"ID_BUTTON_Pet"
#endif  ID_BUTTON_Pet

#ifndef ID_BUTTON_Fash
#define ID_BUTTON_Fash		"ID_BUTTON_FASH"
#endif  ID_BUTTON_Fash
#ifndef ID_BUTTON_Fash2
#define ID_BUTTON_Fash2		"ID_BUTTON_FASH2"
#endif  ID_BUTTON_Fash2
#ifndef ID_TEXT_MingZi
#define ID_TEXT_MingZi		"ID_TEXT_MingZi"
#endif  ID_TEXT_MingZi
#ifndef ID_TEXT_ZDengJi
#define ID_TEXT_ZDengJi		"ID_TEXT_ZDengJi"
#endif  ID_TEXT_ZDengJi
#ifndef ID_TEXT_DengJi
#define ID_TEXT_DengJi		"ID_TEXT_DengJi"
#endif  ID_TEXT_DengJi
#ifndef ID_TEXT_ZZhiYe
#define ID_TEXT_ZZhiYe		"ID_TEXT_ZZhiYe"
#endif  ID_TEXT_ZZhiYe
#ifndef ID_TEXT_ZhiYe
#define ID_TEXT_ZhiYe		"ID_TEXT_ZhiYe"
#endif  ID_TEXT_ZhiYe
#ifndef ID_LISTIMG_GangRing
#define ID_LISTIMG_GangRing		"ID_LISTIMG_GangRing"
#endif  ID_LISTIMG_GangRing
#ifndef ID_LISTIMG_GangSkillBox
#define ID_LISTIMG_GangSkillBox		"ID_LISTIMG_GangSkillBox"
#endif  ID_LISTIMG_GangSkillBox
#ifndef ID_TEXT_DBID
#define ID_TEXT_DBID		"ID_TEXT_DBID"
#endif  ID_TEXT_DBID
#ifndef ID_CHECKBOX_Zhuangbei
#define ID_CHECKBOX_Zhuangbei "ID_CHECKBOX_Zhuangbei"
#endif	ID_CHECKBOX_Zhuangbei
#ifndef ID_CHECKBOX_SelfInfo
#define ID_CHECKBOX_SelfInfo "ID_CHECKBOX_SelfInfo"
#endif ID_CHECKBOX_SelfInfo
#ifndef ID_BUTTON_siliao
#define ID_BUTTON_siliao "ID_BUTTON_siliao"
#endif	ID_BUTTON_siliao
#ifndef ID_BUTTON_addfriend
#define ID_BUTTON_addfriend "ID_BUTTON_addfriend"
#endif	ID_BUTTON_addfriend
#ifndef ID_PICTURE_Fashion11
#define ID_PICTURE_Fashion11		"ID_PICTURE_Fashion11"
#endif  ID_PICTURE_Fashion11
#ifndef ID_PICTURE_rWeapon1
#define ID_PICTURE_rWeapon1		"ID_PICTURE_rWeapon1"
#endif  ID_PICTURE_rWeapon1
#ifndef ID_PICTURE_fWeapon1
#define ID_PICTURE_fWeapon1		"ID_PICTURE_fWeapon1"
#endif  ID_PICTURE_fWeapon1
#ifndef ID_TEXT_EquipScore
#define ID_TEXT_EquipScore		"ID_TEXT_EquipScore"
#endif  ID_TEXT_EquipScore

#include "UiBase.h"
class CUI_ID_FRAME_SeekEqup : public CUIBase, public CUIRenderAnim
{
	// SGuildMember
protected:
	void			ResetObjects();
	ControlFrame*	m_pID_FRAME_SeekEqup;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlListImage*	m_pID_LISTIMG_Head;
	 ControlListImage*	m_pID_LISTIMG_Armour;
	 ControlListImage*	m_pID_LISTIMG_rWeapon;
	 ControlListImage*	m_pID_LISTIMG_2Weapon2;
	 ControlListImage*	m_pID_LISTIMG_Amulet;
	 ControlListImage*	m_pID_LISTIMG_Temp1;
	 ControlListImage*	m_pID_LISTIMG_Shoe;
	 /*ControlListImage*	m_pID_LISTIMG_Ring;*/
	 //ControlListImage*	m_pID_LISTIMG_Symbol;
	 ControlListImage*	m_pID_LISTIMG_Glove;
	 ControlListImage*	m_pID_LISTIMG_Shield;
	 ControlListImage*	m_pID_LISTIMG_Temp;
	 ControlListImage*	m_pID_LISTIMG_Accouterment1;
	 ControlListImage*	m_pID_LISTIMG_Ring1;
	 ControlListImage*	m_pID_LISTIMG_Ring2;
	 ControlListImage*	m_pID_LISTIMG_Bangle1;
	 ControlListImage*	m_pID_LISTIMG_Bangle2;
	 ControlListImage*	m_pID_LISTIMG_Accouterment;
	 ControlListImage*	m_pID_LISTIMG_lWeapon;
	 ControlListImage*	m_pID_LISTIMG_Weapon2;
	 ControlListImage*	m_pID_LISTIMG_Necklace;
	 //ControlListImage*	m_pID_LISTIMG_Fashionhead;
	 ControlListImage*	m_pID_LISTIMG_Fashionarmour;
	 /*ControlListImage*	m_pID_LISTIMG_Fashionglove;
	 ControlListImage*	m_pID_LISTIMG_Fashionshoe;*/
	 ControlButton*	m_pID_BUTTON_Right;
	 ControlButton*	m_pID_BUTTON_Left;
	 ControlButton* m_pID_BUTTON_Pet;
	 ControlText*	m_pID_TEXT_MingZi;
	 ControlText*	m_pID_TEXT_ZDengJi;
	 ControlText*	m_pID_TEXT_DengJi;
	 ControlText*	m_pID_TEXT_ZZhiYe;
	 ControlText*	m_pID_TEXT_ZhiYe;
	 ControlListImage*	m_pID_LISTIMG_GangRing;
	 ControlListImage*	m_pID_LISTIMG_GangSkillBox;
	 /*ControlButton*		m_pID_BUTTON_help;
	 ControlText*	m_pID_TEXT_DBID;*/
	 ControlCheckBox* m_pID_CHECKBOX_Zhuangbei;
	 ControlCheckBox* m_pID_CHECKBOX_SelfInfo;
	 ControlButton*   m_pID_BUTTON_siliao;
	 ControlButton*   m_pID_BUTTON_addfriend;
	 ControlButton*	m_pID_BUTTON_Fash;
	 ControlButton*	m_pID_BUTTON_Fash2;
	 ControlPicture*	m_pID_PICTURE_Fashion11;
	 ControlPicture*	m_pID_PICTURE_rWeapon1;
	 ControlPicture*	m_pID_PICTURE_fWeapon1;
	 ControlText*	m_pID_TEXT_EquipScore;
public:
	 static bool helpOnClick( ControlObject* pSender );

	 BOOL InitCamera();
	// Frame
	 CUI_ID_FRAME_SeekEqup();
	 ~CUI_ID_FRAME_SeekEqup();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_HeadOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_HeadOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HeadOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_rWeaponOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_rWeaponOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_rWeaponOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_Weapon2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Weapon2OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Weapon2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_Temp1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Temp1OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Temp1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_ShoeOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ShoeOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ShoeOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_Ring1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Ring1OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Ring1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_Ring2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Ring2OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Ring2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_Bangle1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Bangle1OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Bangle1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_Bangle2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Bangle2OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Bangle2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_BUTTON_17909OnButtonClick( ControlObject* pSender );
	/*bool ID_LISTIMG_SymbolOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SymbolOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SymbolOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );*/

	bool ID_LISTIMG_GloveOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_GloveOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GloveOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_ShieldOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ShieldOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ShieldOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
	/*bool ID_LISTIMG_TempOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_TempOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TempOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );*/
	
	bool ID_LISTIMG_Accouterment1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Accouterment1OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Accouterment1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
	bool ID_LISTIMG_AmuletOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_AmuletOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AmuletOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_AccoutermentOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_AccoutermentOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AccoutermentOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
	bool ID_LISTIMG_lWeaponOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_lWeaponOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_lWeaponOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
	bool ID_LISTIMG_PACKOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PACKOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PACKOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
	bool ID_LISTIMG_rubbishOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_rubbishOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_rubbishOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
	bool ID_BUTTON_LOCKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UNLOCKOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_NecklaceOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_NecklaceOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_NecklaceOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	/*bool ID_LISTIMG_FashionheadOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_FashionheadOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_FashionheadOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_FashionheadOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );*/

	bool ID_BUTTON_RightOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeftOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PetOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FashOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Fash2OnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_siliaoOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_addfriendOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_ZhuangbeiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SelfInfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _LoadUI();				// 载入UI
private:
	bool DoControlConnect();	// 关连控件
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void SetChangeSkeletonAndEquipAll(SCharItem equips[]);
	void SetDestPlayerId(int nDestPlayerId) {m_DestPlayerId = nDestPlayerId;}
	void SortGroup();
private:
	static bool UISeekEquip_RightLBD(INT nX, INT nY);
	static bool UISeekEquip_LeftLBD(INT nX, INT nY);
	bool ClearListImg();
	void UpdataEquipView();
	//void InitChangeSkeletonAndEquipAll(int iSex, SCharItem pItem[]);

	D3DVIEWPORT9 m_ViewPort;
	MeCamera m_Camera;
	FLOAT			m_fRotateZ;
	INT			m_DestPlayerId;
	bool			m_bRotate;

	CPlayer_SEquipment m_equips[eKeyAll_Max];
	bool m_isShowFashion;
	void SetAllIconItem(MsgPeekEquip *);
	void SetAllEquip(SCharItem EquipItem[EEquipPartType_MaxEquitPart]);
	ControlGroup m_BaseGroup;
	/*ControlGroup m_EquipItemGroup;*/
	CPlayer*     m_DestPlayer;
public:
	void OnSeekEquip(Msg*);
};
extern CUI_ID_FRAME_SeekEqup s_CUI_ID_FRAME_SeekEqup;