/********************************************************************
Created by UIEditor.exe
FileName: D:\res\client\UI\Storage.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "bag/ItemBag2.h"

#ifndef ID_FRAME_Storage
#define ID_FRAME_Storage		"ID_FRAME_Storage"
#endif  ID_FRAME_Storage
// #ifndef ID_BUTTON_Close
// #define ID_BUTTON_Close		"ID_BUTTON_Close"
// #endif  ID_BUTTON_Close
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_LIST_city
#define ID_LIST_city		"ID_LIST_city"
#endif  ID_LIST_city
#ifndef ID_LIST_price
#define ID_LIST_price		"ID_LIST_price"
#endif  ID_LIST_price
#ifndef ID_LISTIMG_Main
#define ID_LISTIMG_Main		"ID_LISTIMG_Main"
#endif  ID_LISTIMG_Main
#ifndef ID_BUTTON_LOCK
#define ID_BUTTON_LOCK		"ID_BUTTON_LOCK"
#endif  ID_BUTTON_LOCK
#ifndef ID_BUTTON_UNLOCK
#define ID_BUTTON_UNLOCK		"ID_BUTTON_UNLOCK"
#endif  ID_BUTTON_UNLOCK
#ifndef ID_BUTTON_ClearPwd
#define ID_BUTTON_ClearPwd		"ID_BUTTON_ClearPwd"
#endif  ID_BUTTON_ClearPwd
#ifndef ID_BUTTON_CHANGE_PWD
#define ID_BUTTON_CHANGE_PWD		"ID_BUTTON_CHANGE_PWD"
#endif  ID_BUTTON_CHANGE_PWD
#ifndef ID_BUTTON_Up
#define ID_BUTTON_Up		"ID_BUTTON_Up"
#endif  ID_BUTTON_Up
#ifndef ID_BUTTON_Down
#define ID_BUTTON_Down		"ID_BUTTON_Down"
#endif  ID_BUTTON_Down
#ifndef ID_PICTURE_PageShow
#define ID_PICTURE_PageShow		"ID_PICTURE_PageShow"
#endif  ID_PICTURE_PageShow
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_BUTTON_Clean
#define ID_BUTTON_Clean		"ID_BUTTON_Clean"
#endif  ID_BUTTON_Clean
#ifndef ID_BUTTON_Split
#define ID_BUTTON_Split		"ID_BUTTON_Split"
#endif  ID_BUTTON_Split
#ifndef ID_BUTTON_Save
#define ID_BUTTON_Save		"ID_BUTTON_Save"
#endif  ID_BUTTON_Save
#ifndef ID_BUTTON_Get
#define ID_BUTTON_Get		"ID_BUTTON_Get"
#endif  ID_BUTTON_Get
#ifndef ID_TEXT_MONEY
#define ID_TEXT_MONEY		"ID_TEXT_MONEY"
#endif  ID_TEXT_MONEY
#ifndef ID_TEXT_AllNum
#define ID_TEXT_AllNum		"ID_TEXT_AllNum"
#endif  ID_TEXT_AllNum
#ifndef ID_BUTTON_Password
#define ID_BUTTON_Password		"ID_BUTTON_Password"
#endif  ID_BUTTON_Password
#ifndef ID_PICTURE_Limit
#define ID_PICTURE_Limit		"ID_PICTURE_Limit"
#endif  ID_PICTURE_Limit
#ifndef ID_CHECKBOX_Storage1
#define ID_CHECKBOX_Storage1		"ID_CHECKBOX_Storage1"
#endif  ID_CHECKBOX_Storage1
#ifndef ID_CHECKBOX_Storage2
#define ID_CHECKBOX_Storage2		"ID_CHECKBOX_Storage2"
#endif  ID_CHECKBOX_Storage2
#ifndef ID_CHECKBOX_Storage3
#define ID_CHECKBOX_Storage3		"ID_CHECKBOX_Storage3"
#endif  ID_CHECKBOX_Storage3
#ifndef ID_CHECKBOX_Storage4
#define ID_CHECKBOX_Storage4		"ID_CHECKBOX_Storage4"
#endif  ID_CHECKBOX_Storage4

#include "UiBase.h"
class CUI_ID_FRAME_Storage :public CUIBase
{
	// SGuildMember
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_Storage;
//	ControlButton*	m_pID_BUTTON_Close;
	//ControlButton*	m_pID_BUTTON_help;
	ControlList*	m_pID_LIST_city;
	ControlList*	m_pID_LIST_price;
	ControlListImage*	m_pID_LISTIMG_Main;
	ControlButton*	m_pID_BUTTON_LOCK;
	ControlButton*	m_pID_BUTTON_UNLOCK;
	//ControlButton*	m_pID_BUTTON_ClearPwd;
	ControlButton*	m_pID_BUTTON_CHANGE_PWD;
	ControlButton*	m_pID_BUTTON_Up;
	ControlButton*	m_pID_BUTTON_Down;
	ControlPicture*	m_pID_PICTURE_PageShow;
	ControlText*	m_pID_TEXT_Page;
	ControlButton*	m_pID_BUTTON_Clean;
	ControlButton*	m_pID_BUTTON_Split;
	ControlButton*	m_pID_BUTTON_Save;
	ControlButton*	m_pID_BUTTON_Get;
	ControlText*	m_pID_TEXT_MONEY;
	ControlText*	m_pID_TEXT_AllNum;
	ControlButton*	m_pID_BUTTON_Password;
	ControlPicture*	m_pID_PICTURE_Limit;
	ControlCheckBox*	m_pID_CHECKBOX_Storage1;
	ControlCheckBox*	m_pID_CHECKBOX_Storage2;
	ControlCheckBox*	m_pID_CHECKBOX_Storage3;
	ControlCheckBox*	m_pID_CHECKBOX_Storage4;

public:
	CUI_ID_FRAME_Storage();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	void ID_LIST_cityOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_priceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_MainOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MainOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MainOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MainOnIconRDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MainOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_LOCKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UNLOCKOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_ClearPwdOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CHANGE_PWDOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DownOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MainOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CleanOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SplitOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SaveOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GetOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PasswordOnButtonClick( ControlObject* pSender );

	void ID_CHECKBOX_Storage1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Storage2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Storage3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Storage4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
    static	bool StorageFrame_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
public:


	const char* GetItem_LastPWD() { return szItem_LastPWD; }
	void SetItem_LastPWD(const char* buf)
	{
		if( !buf )
			return;
		memcpy(szItem_LastPWD, buf, sizeof(szItem_LastPWD));
	}
	const char* GetItem_PrePWD() { return szItem_PrePWD; }
	void SetItem_PrePWD(const char* buf)
	{
		if( !buf )
			return;
		memcpy(szItem_PrePWD, buf, sizeof(szItem_PrePWD));
	}

	void SetItem_PWD(const char* buf)
	{
		if( !buf )
			return;
		memcpy(szItem_PWD, buf, sizeof(szItem_PWD));
	}
	const char* GetItem_PWD() { return szItem_PWD; }

	void SetInUIFrameLock(bool bLock) { bInUIFrameLock = bLock; }
	bool GetInUIFrameLock() { return bInUIFrameLock; }
	void SetInUIFrameUnLock(bool bLock) { bInUIFrameUnLock = bLock; }
	bool GetInUIFrameUnLock() { return bInUIFrameUnLock; }

	void Refeash(); //刷新仓库信息

	bool IsEqualTo_LISTIMG_Main(ControlObject* pObject);
	int LISTIMG_Main_GetIndexByItem( ControlIconDrag::S_ListImg* pItem );

	int GetPageCurr() { return nPageCurr; }
	int GetDstIndex() { return m_ustDstIndex; }
	void SetDstIndex(int index) { m_ustDstIndex = index; }
	DWORD GetChangeCount() { return m_dwChangeCount; }

	void UpdateMoney();
	void GetNpcSysID( unsigned int nId );

    static bool ConfirmBoundCallback( char bPressYesButton, void *pData );

	void   ChangeItemByIndex(int nIndex);
	void   RefeshStorageState();
	void   InitStorageState();

	int    GetNpcID(){return m_nNpcSysId;}
private:
	void GetPageCout();
	bool AddPackItem( int nPackItemIndex, ControlIconDrag::S_ListImg* pItemPack,
		ControlIconDrag::S_ListImg* pItemStorage,
		ControlListImage* pBagListImg,
		CItemBag2* pBag,
		int bagType );
	void UpdateIconInfo();

	DWORD m_dwChangeCount;
	unsigned short m_ustDstIndex;
	int nNpcID;
	bool bInUIFrameLock;
	bool bInUIFrameUnLock;
	char szItem_PrePWD[PWD_OF_ITEM];
	char szItem_LastPWD[PWD_OF_ITEM];
	char szItem_PWD[PWD_OF_ITEM];
	int m_nNpcSysId;
	bool m_bQuestNpc;
	int nPageCount; //页数
	int nPageCurr; //当前页数
	BYTE  btStorageMaxPage;// 仓库最大页数
	bool  IsNpcStorage;
public:
	void SetIsNpcStorage(bool s){IsNpcStorage = s;}
	bool GetIsNpeStorage(){return IsNpcStorage;}
};
extern CUI_ID_FRAME_Storage s_CUI_ID_FRAME_Storage;

