/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\UseItem.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_UseItem
#define ID_FRAME_UseItem		"ID_FRAME_UseItem"
#endif  ID_FRAME_UseItem
#ifndef ID_LISTIMG_Item
#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
#endif  ID_LISTIMG_Item

class CUI_ID_FRAME_UseItem : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_UseItem();
	virtual ~CUI_ID_FRAME_UseItem();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
	virtual bool IsHoldInMemory() const { return true; }

	void SetItem(unsigned short ustItemId);

private:	
	 ControlFrame*	m_pID_FRAME_UseItem;
	 ControlListImage*	m_pID_LISTIMG_Item;

	 unsigned short m_ItemId;
};
extern CUI_ID_FRAME_UseItem s_CUI_ID_FRAME_UseItem;
