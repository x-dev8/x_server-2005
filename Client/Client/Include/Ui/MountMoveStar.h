/********************************************************************
	Created by UIEditor.exe
	FileName: D:\SVNClient\sg_pro\3Guo_Main\FullClient\Data\Ui\MountMoveStar.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "ItemEnableChangeSysBase.h"
#include "PlayerRole.h"
#ifndef ID_FRAME_MountMoveStar
#define ID_FRAME_MountMoveStar		"ID_FRAME_MountMoveStar"
#endif  ID_FRAME_MountMoveStar
#ifndef ID_LISTIMG_OldMount
#define ID_LISTIMG_OldMount		"ID_LISTIMG_OldMount"
#endif  ID_LISTIMG_OldMount
#ifndef ID_LISTIMG_NewMount
#define ID_LISTIMG_NewMount		"ID_LISTIMG_NewMount"
#endif  ID_LISTIMG_NewMount
#ifndef ID_LISTIMG_MountItem
#define ID_LISTIMG_MountItem		"ID_LISTIMG_MountItem"
#endif  ID_LISTIMG_MountItem
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Canel
#define ID_BUTTON_Canel		"ID_BUTTON_Canel"
#endif  ID_BUTTON_Canel
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info

#ifndef ID_TEXT_OldLevel
#define ID_TEXT_OldLevel		"ID_TEXT_OldLevel"
#endif  ID_TEXT_OldLevel
#ifndef ID_TEXT_NewLevel
#define ID_TEXT_NewLevel		"ID_TEXT_NewLevel"
#endif  ID_TEXT_NewLevel


class CUI_ID_FRAME_MountMoveStar: public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	 CUI_ID_FRAME_MountMoveStar();
	 ControlFrame*	m_pID_FRAME_MountMoveStar;
	 ControlListImage*	m_pID_LISTIMG_OldMount;
	 ControlListImage*	m_pID_LISTIMG_NewMount;
	 ControlListImage*	m_pID_LISTIMG_MountItem;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Canel;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Money;
	 ControlText*	m_pID_TEXT_Info;

	 ControlText*	m_pID_TEXT_OldLevel;
	 ControlText*	m_pID_TEXT_NewLevel;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_OldMountOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_OldMountOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_OldMountOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_OldMountOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_NewMountOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_NewMountOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_NewMountOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_NewMountOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MountItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MountItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MountItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MountItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CanelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsPackItemBeUsing( __int64 nGuid );

	void Clear();
	void SetMountData(ControlIconDrag::S_ListImg* pItemDrag,bool IsOldMount);
	void SetMount(ControlIconDrag::S_ListImg* pItemDrag);
	void EnableBagItem(CItemBag2* pBag,unsigned int ItemID);
private:
	bool IsCanMoveStar(bool IsShowCenterInfo);
private:
	unsigned int m_LogMountLevel;//当前移星的等级记录
	__int64	m_OldMountID;
	__int64 m_NewMountID;
};
extern CUI_ID_FRAME_MountMoveStar s_CUI_ID_FRAME_MountMoveStar;
