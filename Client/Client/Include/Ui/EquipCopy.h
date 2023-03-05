/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\EquipCopy.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_EquipCopy
#define ID_FRAME_EquipCopy		"ID_FRAME_EquipCopy"
#endif  ID_FRAME_EquipCopy
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Tip2
#define ID_TEXT_Tip2		"ID_TEXT_Tip2"
#endif  ID_TEXT_Tip2
#ifndef ID_LISTIMG_Equip1
#define ID_LISTIMG_Equip1		"ID_LISTIMG_Equip1"
#endif  ID_LISTIMG_Equip1
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_TEXT_Tip1
#define ID_TEXT_Tip1		"ID_TEXT_Tip1"
#endif  ID_TEXT_Tip1
#ifndef ID_LISTIMG_Equip2
#define ID_LISTIMG_Equip2		"ID_LISTIMG_Equip2"
#endif  ID_LISTIMG_Equip2
#ifndef ID_TEXT_TipAllDone
#define ID_TEXT_TipAllDone		"ID_TEXT_TipAllDone"
#endif  ID_TEXT_TipAllDone
#ifndef ID_PICTURE_Begin
#define ID_PICTURE_Begin		"ID_PICTURE_Begin"
#endif  ID_PICTURE_Begin
#ifndef ID_PICTURE_Begin2
#define ID_PICTURE_Begin2		"ID_PICTURE_Begin2"
#endif  ID_PICTURE_Begin2

#include "EquipEvolve.h"
class CUI_ID_FRAME_EquipCopy : public EquipEvolveUI
{
	// Member
public:	
	 CUI_ID_FRAME_EquipCopy();
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Tip2;
	 ControlText*	m_pID_TEXT_Tip1;
	 ControlListImage*	m_pID_LISTIMG_Equip2;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Equip1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Equip1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Equip1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Equip1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Equip2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Equip2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Equip2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Equip2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );



	void SetEquipCopyVisable( const bool bVisable,bool isCross );			
	void ArmourOnIconDragOn(ControlObject* pSender,  ControlIconDrag::S_ListImg* pItemDrag);
    virtual bool IsPackItemBeUsing( __int64 nGuid );

protected:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI

protected:
	virtual int			GetEvolveType(){return m_EvolveType;}
	virtual int			GetEvolveMaterialType() {return  m_MaterialType;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg){return false;}
	virtual void		ResetUIObjects();
	virtual void		RefreshOkButton();

	virtual void		_RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );

	virtual void		RefreshAllBagEnable();
	virtual void		SendEvolveMsg();

	static void			OnVisibleChange( ControlObject* pUIObject ); 

	virtual void		TipVisible(bool IsMaterialExist) ;

	bool				IsSamePart(ControlIconDrag::S_ListImg * pImg,ControlIconDrag::S_ListImg * pTargetImg);
	bool				IsInCrossLevel(ControlIconDrag::S_ListImg * pImg,ControlIconDrag::S_ListImg * pTargetImg);
	bool				IsSameLevel(ControlIconDrag::S_ListImg * pImg,ControlIconDrag::S_ListImg * pTargetImg);
	void				ClearTargetEquip();
protected:
	bool		m_CrossCopy;
	int			m_EvolveType;
	int			m_MaterialType;
	ControlPicture*	m_pID_PICTURE_Begin1;
	ControlPicture*	m_pID_PICTURE_BeginCross;

	short			m_stTargetItemIndex;			// 目标物品Index
	__int64			m_stTargetItemGuid;			//目标物品Guid
	bool			m_bTargetItemEnable;

};
extern CUI_ID_FRAME_EquipCopy s_CUI_ID_FRAME_EquipCopy;
