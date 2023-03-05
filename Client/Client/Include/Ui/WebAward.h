///********************************************************************
//	Created by UIEditor.exe
//	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\WebAward.h
//*********************************************************************/
//#pragma once
//#include "MeUi/MeUi.h"
//#include "me3d/Vector.h"
//
//#ifndef ID_FRAME_WebAward
//#define ID_FRAME_WebAward		"ID_FRAME_WebAward"
//#endif  ID_FRAME_WebAward
//#ifndef ID_PICTURE_BackGround
//#define ID_PICTURE_BackGround		"ID_PICTURE_BackGround"
//#endif  ID_PICTURE_BackGround
//#ifndef ID_TEXT_PlayerName
//#define ID_TEXT_PlayerName		"ID_TEXT_PlayerName"
//#endif  ID_TEXT_PlayerName
//#ifndef ID_PICTURE_PlayerName
//#define ID_PICTURE_PlayerName		"ID_PICTURE_PlayerName"
//#endif  ID_PICTURE_PlayerName
//#ifndef ID_EDIT_PlayerName
//#define ID_EDIT_PlayerName		"ID_EDIT_PlayerName"
//#endif  ID_EDIT_PlayerName
//#ifndef ID_TEXT_PhoneZ
//#define ID_TEXT_PhoneZ		"ID_TEXT_PhoneZ"
//#endif  ID_TEXT_PhoneZ
//#ifndef ID_PICTURE_Phone
//#define ID_PICTURE_Phone		"ID_PICTURE_Phone"
//#endif  ID_PICTURE_Phone
//#ifndef ID_EDIT_Phone
//#define ID_EDIT_Phone		"ID_EDIT_Phone"
//#endif  ID_EDIT_Phone
//#ifndef ID_TEXT_Email
//#define ID_TEXT_Email		"ID_TEXT_Email"
//#endif  ID_TEXT_Email
//#ifndef ID_PICTURE_Email
//#define ID_PICTURE_Email		"ID_PICTURE_Email"
//#endif  ID_PICTURE_Email
//#ifndef ID_EDIT_Email
//#define ID_EDIT_Email		"ID_EDIT_Email"
//#endif  ID_EDIT_Email
//#ifndef ID_BUTTON_CLOSE
//#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
//#endif  ID_BUTTON_CLOSE
//#ifndef ID_BUTTON_Reset
//#define ID_BUTTON_Reset		"ID_BUTTON_Reset"
//#endif  ID_BUTTON_Reset
//#ifndef ID_BUTTON_Register
//#define ID_BUTTON_Register		"ID_BUTTON_Register"
//#endif  ID_BUTTON_Register
//#ifndef ID_TEXT_Card
//#define ID_TEXT_Card		"ID_TEXT_Card"
//#endif  ID_TEXT_Card
//#ifndef ID_PICTURE_Card
//#define ID_PICTURE_Card		"ID_PICTURE_Card"
//#endif  ID_PICTURE_Card
//#ifndef ID_EDIT_Card
//#define ID_EDIT_Card		"ID_EDIT_Card"
//#endif  ID_EDIT_Card
//#ifndef ID_PICTURE_PlayerNameExplain
//#define ID_PICTURE_PlayerNameExplain		"ID_PICTURE_PlayerNameExplain"
//#endif  ID_PICTURE_PlayerNameExplain
//#ifndef ID_PICTURE_EmailExplain
//#define ID_PICTURE_EmailExplain		"ID_PICTURE_EmailExplain"
//#endif  ID_PICTURE_EmailExplain
//#ifndef ID_PICTURE_CardExplain
//#define ID_PICTURE_CardExplain		"ID_PICTURE_CardExplain"
//#endif  ID_PICTURE_CardExplain
//#ifndef ID_PICTURE_PhoneExplain
//#define ID_PICTURE_PhoneExplain		"ID_PICTURE_PhoneExplain"
//#endif  ID_PICTURE_PhoneExplain
//#ifndef ID_LISTIMG_Item
//#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
//#endif  ID_LISTIMG_Item
//#ifndef ID_TEXT_TakeTip
//#define ID_TEXT_TakeTip		"ID_TEXT_TakeTip"
//#endif  ID_TEXT_TakeTip
//#ifndef ID_TEXT_23244
//#define ID_TEXT_23244		"ID_TEXT_23244"
//#endif  ID_TEXT_23244
//#ifndef ID_BUTTON_Web
//#define ID_BUTTON_Web		"ID_BUTTON_Web"
//#endif  ID_BUTTON_Web
//#ifndef ID_TEXT_Alarm
//#define ID_TEXT_Alarm		"ID_TEXT_Alarm"
//#endif  ID_TEXT_Alarm
//#ifndef ID_CHECKBOX_Agree
//#define ID_CHECKBOX_Agree		"ID_CHECKBOX_Agree"
//#endif  ID_CHECKBOX_Agree
//#ifndef ID_BUTTON_Agreement2
//#define ID_BUTTON_Agreement2		"ID_BUTTON_Agreement2"
//#endif  ID_BUTTON_Agreement2
//
//#include "UiBase.h"
//class CUI_ID_FRAME_WebAward :public CUIBase
//{
//	// Member
//private:
//	void ResetMembers();
//	 ControlFrame*	m_pID_FRAME_WebAward;
//	 ControlPicture*	m_pID_PICTURE_BackGround;
//	 ControlText*	m_pID_TEXT_PlayerName;
//	 ControlPicture*	m_pID_PICTURE_PlayerName;
//	 ControlEdit*	m_pID_EDIT_PlayerName;
//	 ControlText*	m_pID_TEXT_PhoneZ;
//	 ControlPicture*	m_pID_PICTURE_Phone;
//	 ControlEdit*	m_pID_EDIT_Phone;
//	 ControlText*	m_pID_TEXT_Email;
//	 ControlPicture*	m_pID_PICTURE_Email;
//	 ControlEdit*	m_pID_EDIT_Email;
//	 ControlButton*	m_pID_BUTTON_CLOSE;
//	 ControlButton*	m_pID_BUTTON_Reset;
//	 ControlButton*	m_pID_BUTTON_Register;
//	 ControlText*	m_pID_TEXT_Card;
//	 ControlPicture*	m_pID_PICTURE_Card;
//	 ControlEdit*	m_pID_EDIT_Card;
//	 ControlPicture*	m_pID_PICTURE_PlayerNameExplain;
//	 ControlPicture*	m_pID_PICTURE_EmailExplain;
//	 ControlPicture*	m_pID_PICTURE_CardExplain;
//	 ControlPicture*	m_pID_PICTURE_PhoneExplain;
//	 ControlListImage*	m_pID_LISTIMG_Item;
//	 ControlText*	m_pID_TEXT_TakeTip;
//	 ControlText*	m_pID_TEXT_23244;
//	 ControlButton*	m_pID_BUTTON_Web;
//	 ControlText*	m_pID_TEXT_Alarm;
//// 	 ControlCheckBox*	m_pID_CHECKBOX_Agree;
//// 	 ControlButton*	m_pID_BUTTON_Agreement2;
//
//public:	
//	CUI_ID_FRAME_WebAward();
//	// Frame
//	bool OnFrameRun();
//	bool OnFrameRender();
//	void ID_EDIT_PlayerNameOnEditEnter( ControlObject* pSender, const char* szData );
//	void ID_EDIT_PhoneOnEditEnter( ControlObject* pSender, const char* szData );
//	void ID_EDIT_EmailOnEditEnter( ControlObject* pSender, const char* szData );
//	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
//	bool ID_BUTTON_ResetOnButtonClick( ControlObject* pSender );
//	bool ID_BUTTON_RegisterOnButtonClick( ControlObject* pSender );
//
//	void ID_EDIT_CardOnEditEnter( ControlObject* pSender, const char* szData );
//	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
//	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
//	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
//	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
//	bool ID_BUTTON_WebOnButtonClick( ControlObject* pSender );
//// 	void ID_CHECKBOX_AgreeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
//// 	bool ID_BUTTON_Agreement2OnButtonClick( ControlObject* pSender );
//
//	
//private:
//	virtual bool _LoadUI();				// 载入UI
//	bool DoControlConnect();	// 关连控件
//	virtual bool _UnLoadUI();			// 卸载UI
//	virtual bool _IsVisable();			// 是否可见
//	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
//public:
//
//
//	ControlGroup& GetAddressCtrlGroup() { return m_AddressCtrlGroup; }
//	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
//	void SetOkVisible();
//	bool EditInputIsVisable();
//private:
//
//	const Vector& GetVisiblePosition() const { return m_vVisiblePos; }
//	void RefreshAllBagEnable();
//	void SetRealAwardItemBagIndex(int index, bool enable);
//	void SetRealAwardItem(ControlIconDrag::S_ListImg* pItem);
//	void ClearInfo();
//
//	static void OnVisibleChanged(ControlObject* pSender);
//	static void OnTab( );
//
//	int m_moveStarItemBagIndex;
//	bool m_moveStarItemEnable; 
//	bool m_bNeedUpdate;
//	Vector m_vVisiblePos;			 // 分解界面打开时的人物位置,用来自动关闭时使用
//
//	ControlGroup	m_AwardInfoCtrlGroup;
//	ControlGroup	m_AddressCtrlGroup;
//};
//extern CUI_ID_FRAME_WebAward s_CUI_ID_FRAME_WebAward;
