/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\AddQuestEntrust.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "QuestEntrustDefine.h"
#include "ItemEnableChangeSysBase.h"
#ifndef ID_FRAME_AddQuestEntrust
#define ID_FRAME_AddQuestEntrust		"ID_FRAME_AddQuestEntrust"
#endif  ID_FRAME_AddQuestEntrust
#ifndef ID_TEXT_QuestEntruestName
#define ID_TEXT_QuestEntruestName		"ID_TEXT_QuestEntruestName"
#endif  ID_TEXT_QuestEntruestName
#ifndef ID_TEXT_QuestEntrustDepict
#define ID_TEXT_QuestEntrustDepict		"ID_TEXT_QuestEntrustDepict"
#endif  ID_TEXT_QuestEntrustDepict
#ifndef ID_TEXT_QuestEntrustInfo
#define ID_TEXT_QuestEntrustInfo		"ID_TEXT_QuestEntrustInfo"
#endif  ID_TEXT_QuestEntrustInfo
#ifndef ID_CHECKBOX_YinBi
#define ID_CHECKBOX_YinBi		"ID_CHECKBOX_YinBi"
#endif  ID_CHECKBOX_YinBi
#ifndef ID_CHECKBOX_YuanBao
#define ID_CHECKBOX_YuanBao		"ID_CHECKBOX_YuanBao"
#endif  ID_CHECKBOX_YuanBao
#ifndef ID_BUTTON_Add
#define ID_BUTTON_Add		"ID_BUTTON_Add"
#endif  ID_BUTTON_Add
#ifndef ID_BUTTON_Canel
#define ID_BUTTON_Canel		"ID_BUTTON_Canel"
#endif  ID_BUTTON_Canel
#ifndef ID_EDIT_Jin
#define ID_EDIT_Jin		"ID_EDIT_Jin"
#endif  ID_EDIT_Jin
#ifndef ID_EDIT_Yin
#define ID_EDIT_Yin		"ID_EDIT_Yin"
#endif  ID_EDIT_Yin
#ifndef ID_EDIT_Ton
#define ID_EDIT_Ton		"ID_EDIT_Ton"
#endif  ID_EDIT_Ton
#ifndef ID_EDIT_YuanBao
#define ID_EDIT_YuanBao		"ID_EDIT_YuanBao"
#endif  ID_EDIT_YuanBao
#ifndef ID_LISTIMG_Item
#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
#endif  ID_LISTIMG_Item
#ifndef ID_EDIT_ItemNum
#define ID_EDIT_ItemNum		"ID_EDIT_ItemNum"
#endif  ID_EDIT_ItemNum

class CUI_ID_FRAME_AddQuestEntrust: public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	CUI_ID_FRAME_AddQuestEntrust();
	virtual ~CUI_ID_FRAME_AddQuestEntrust();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_YinBiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_YuanBaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_AddOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CanelOnButtonClick( ControlObject* pSender );
	void ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_YinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_TonOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_YuanBaoOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_EDIT_ItemNumOnEditEnter( ControlObject* pSender, const char* szData );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );// 设置是否可视
	virtual bool IsPackItemBeUsing( __int64 nGuid );
	static void OnVisibleChange( ControlObject* pUIObject );
public:
	void LoadInfoToUI(unsigned int QuestID);
	void SendInfo();
	void SetItem(__int64 ItemOnceID);
	void SetEmpty();
private:	
	 ControlFrame*	m_pID_FRAME_AddQuestEntrust;
	 ControlText*	m_pID_TEXT_QuestEntruestName;
	 ControlText*	m_pID_TEXT_QuestEntrustDepict;
	 ControlText*	m_pID_TEXT_QuestEntrustInfo;
	 ControlCheckBox*	m_pID_CHECKBOX_YinBi;
	 ControlCheckBox*	m_pID_CHECKBOX_YuanBao;
	 ControlButton*	m_pID_BUTTON_Add;
	 ControlButton*	m_pID_BUTTON_Canel;
	 ControlEdit*	m_pID_EDIT_Jin;
	 ControlEdit*	m_pID_EDIT_Yin;
	 ControlEdit*	m_pID_EDIT_Ton;
	 ControlEdit*	m_pID_EDIT_YuanBao;
	 ControlListImage*	m_pID_LISTIMG_Item;
	 ControlEdit*	m_pID_EDIT_ItemNum;

	 unsigned int   m_QuestID;
	 __int64 ItemID;
};
extern CUI_ID_FRAME_AddQuestEntrust s_CUI_ID_FRAME_AddQuestEntrust;
