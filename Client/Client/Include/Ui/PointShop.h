/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\PointShop.h
*********************************************************************/
#pragma once
#include "MessageDefine.h"
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"

#ifndef ID_FRAME_PointShop
#define ID_FRAME_PointShop		"ID_FRAME_PointShop"
#endif  ID_FRAME_PointShop
#ifndef ID_PICTURE_Wall
#define ID_PICTURE_Wall		"ID_PICTURE_Wall"
#endif  ID_PICTURE_Wall
#ifndef ID_LISTIMG_SelectedAward
#define ID_LISTIMG_SelectedAward		"ID_LISTIMG_SelectedAward"
#endif  ID_LISTIMG_SelectedAward
#ifndef ID_BUTTON_Select
#define ID_BUTTON_Select		"ID_BUTTON_Select"
#endif  ID_BUTTON_Select
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_LISTIMG_AllAward
#define ID_LISTIMG_AllAward		"ID_LISTIMG_AllAward"
#endif  ID_LISTIMG_AllAward
#ifndef ID_TEXT_Null
#define ID_TEXT_Null		"ID_TEXT_Null"
#endif  ID_TEXT_Null
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain

#include "UiBase.h"
class CUI_ID_FRAME_PointShop :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_PointShop();
private:
	ControlFrame*	m_pID_FRAME_PointShop;
	ControlPicture*	m_pID_PICTURE_Wall;
	ControlListImage*	m_pID_LISTIMG_SelectedAward;
	ControlButton*	m_pID_BUTTON_Select;
	ControlButton*	m_pID_BUTTON_OK;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlListImage*	m_pID_LISTIMG_AllAward;
	ControlText*	m_pID_TEXT_Null;
	ControlText*	m_pID_TEXT_Explain;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_SelectedAwardOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SelectedAwardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SelectedAwardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SelectedAwardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_SelectOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_AllAwardOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_AllAwardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AllAwardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AllAwardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	void Refresh();				// 
	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; };
	void UpdateItem( Msg* pMsg );

private:


	Vector m_vVisiblePos;

	vector< SJiFengItemRecordClient > m_vecItemRecord;
	vector< SJiFengItemRecordClient > m_vecItemSelect;

	int m_nItemCount;

	ControlIconDrag::S_ListImg* m_pSelectItem;
	void SetSelectItem(ControlIconDrag::S_ListImg* pItem);
};
extern CUI_ID_FRAME_PointShop s_CUI_ID_FRAME_PointShop;
