/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\jiebang.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "me3d/Vector.h"
#include "MessageDefine.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "ItemEnableChangeSysBase.h"
#include "core\Name.h"
#ifndef ID_FRAME_JieBang
#define ID_FRAME_JieBang		"ID_FRAME_JieBang"
#endif  ID_FRAME_JieBang
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
#ifndef ID_LISTIMG_ZJ1
#define ID_LISTIMG_ZJ1		"ID_LISTIMG_ZJ1"
#endif  ID_LISTIMG_ZJ1
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_TEXT_EquipName
#define ID_TEXT_EquipName		"ID_TEXT_EquipName"
#endif  ID_TEXT_EquipName
#ifndef ID_TEXT_ItemName
#define ID_TEXT_ItemName		"ID_TEXT_ItemName"
#endif  ID_TEXT_ItemName
class CUI_ID_FRAME_JieBang :public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	 CUI_ID_FRAME_JieBang();
	 ControlFrame*	m_pID_FRAME_JieBang;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Money;
	 ControlListImage*	m_pID_LISTIMG_Material;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_Ok;
	 ControlListImage*	m_pID_LISTIMG_ZJ1;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlText*	m_pID_TEXT_EquipName;
	 ControlText*	m_pID_TEXT_ItemName;

	 ControlFrame* GetFrame() const { return m_pID_FRAME_JieBang; }

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
	bool ID_LISTIMG_ZJ1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ZJ2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ5OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );// 设置是否可视
	virtual bool IsPackItemBeUsing( __int64 nGuid );
	void UnBindEquipSuc(__int64 equipGuiID);
	bool SetEmpty();
private:
	bool SetItem(ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag);
	
	void UpdateUIButtonByBagItem();
	void HandleUnBindEquip(__int64 EquipOnceID);
	void SetBagItemIsUnUse(bool isUnUse,int16 indexPos);
	void ShowErrorMsgInScreen(eName eErrorID);
private:
	int				m_unBindBagSum;
	int				m_unBindNeedSum;
	SCharItem*		m_unBindEquip;
	int				m_unBindIndex;
	DWORD			m_StepLogTime;
};
extern CUI_ID_FRAME_JieBang s_CUI_ID_FRAME_JieBang;
