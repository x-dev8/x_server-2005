/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\package\PickUp.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"

#ifndef ID_FRAME_PickUp
#define ID_FRAME_PickUp		"ID_FRAME_PickUp"
#endif  ID_FRAME_PickUp
#ifndef ID_PICTURE_Wall
#define ID_PICTURE_Wall		"ID_PICTURE_Wall"
#endif  ID_PICTURE_Wall
#ifndef ID_BUTTON_Item1
#define ID_BUTTON_Item1		"ID_BUTTON_Item1"
#endif  ID_BUTTON_Item1
#ifndef ID_BUTTON_Item2
#define ID_BUTTON_Item2		"ID_BUTTON_Item2"
#endif  ID_BUTTON_Item2
#ifndef ID_BUTTON_Item3
#define ID_BUTTON_Item3		"ID_BUTTON_Item3"
#endif  ID_BUTTON_Item3
#ifndef ID_BUTTON_Item4
#define ID_BUTTON_Item4		"ID_BUTTON_Item4"
#endif  ID_BUTTON_Item4
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_BUTTON_PickAll
#define ID_BUTTON_PickAll		"ID_BUTTON_PickAll"
#endif  ID_BUTTON_PickAll
#ifndef ID_TEXT_Name1
#define ID_TEXT_Name1		"ID_TEXT_Name1"
#endif  ID_TEXT_Name1
#ifndef ID_TEXT_Name2
#define ID_TEXT_Name2		"ID_TEXT_Name2"
#endif  ID_TEXT_Name2
#ifndef ID_TEXT_Name3
#define ID_TEXT_Name3		"ID_TEXT_Name3"
#endif  ID_TEXT_Name3
#ifndef ID_TEXT_Name4
#define ID_TEXT_Name4		"ID_TEXT_Name4"
#endif  ID_TEXT_Name4
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_BUTTON_Pageup
#define ID_BUTTON_Pageup		"ID_BUTTON_Pageup"
#endif  ID_BUTTON_Pageup
#ifndef ID_BUTTON_Pagedown
#define ID_BUTTON_Pagedown		"ID_BUTTON_Pagedown"
#endif  ID_BUTTON_Pagedown
#ifndef ID_LISTIMG_Item
#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
#endif  ID_LISTIMG_Item
#ifndef ID_PICTURE_MemberList
#define ID_PICTURE_MemberList		"ID_PICTURE_MemberList"
#endif  ID_PICTURE_MemberList
#ifndef ID_LIST_MemberList
#define ID_LIST_MemberList		"ID_LIST_MemberList"
#endif  ID_LIST_MemberList
#ifndef ID_LISTIMG_Item2
#define ID_LISTIMG_Item2		"ID_LISTIMG_Item2"
#endif  ID_LISTIMG_Item2
#ifndef ID_LISTIMG_Item3
#define ID_LISTIMG_Item3		"ID_LISTIMG_Item3"
#endif  ID_LISTIMG_Item3
#ifndef ID_LISTIMG_Item4
#define ID_LISTIMG_Item4		"ID_LISTIMG_Item4"
#endif  ID_LISTIMG_Item4

#include "UiBase.h"
class CUI_ID_FRAME_PickUp :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_PickUp();
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_PickUp;
	 //ControlPicture*	m_pID_PICTURE_Wall;
	 ControlButton*	m_pID_BUTTON_Item1;
	 ControlButton*	m_pID_BUTTON_Item2;
	 ControlButton*	m_pID_BUTTON_Item3;
	 ControlButton*	m_pID_BUTTON_Item4;
	 ControlButton*	m_pID_BUTTON_Close;
	 ControlButton*	m_pID_BUTTON_PickAll;
	 ControlText*	m_pID_TEXT_Name1;
	 ControlText*	m_pID_TEXT_Name2;
	 ControlText*	m_pID_TEXT_Name3;
	 ControlText*	m_pID_TEXT_Name4;
	 ControlText*	m_pID_TEXT_Page;
	 ControlButton*	m_pID_BUTTON_Pageup;
	 ControlButton*	m_pID_BUTTON_Pagedown;
	 ControlListImage*	m_pID_LISTIMG_Item;
	 ControlPicture*	m_pID_PICTURE_MemberList;
	 ControlList*	m_pID_LIST_MemberList;
	 ControlListImage*	m_pID_LISTIMG_Item2;
	 ControlListImage*	m_pID_LISTIMG_Item3;
	 ControlListImage*	m_pID_LISTIMG_Item4;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_Item1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Item2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Item3OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Item4OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PickAllOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageupOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PagedownOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_LIST_MemberListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_Item2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Item2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Item3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Item4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

    static void ID_LISTIMG_ItemOnMouseOn( UINT nFLag, int nX, int nY );
    static void ID_LISTIMG_Item2OnMouseOn( UINT nFLag, int nX, int nY );
    static void ID_LISTIMG_Item3OnMouseOn( UINT nFLag, int nX, int nY );
    static void ID_LISTIMG_Item4OnMouseOn( UINT nFLag, int nX, int nY );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	ControlButton* GetButtonPickAll();
	bool IsSamePackage( int nPackageID ) { return nPackageID == nItemPackageID; }
	void Reset();
	void InitData();
	bool AddItem(const SCharItem& kItem, bool bCanPick);
	void SetPackageInfo( int ID, bool bNeedSend ) { nItemPackageID = ID; bNeedSendCloseMsg = bNeedSend; }
	void PickAll();
    void DeleteItem( __int64 nItemID ); // 物品唯一ID
	void UpdateItemCanLoot(__int64 nItemID, bool bCanLoot);
	void SetAssignItemListMemberList(int nItemCount, __int64* pItemList, int nPlayerCount, uint32* pPlayerIDList);

	void AllItemAssignMySelf(); //指定所有物品给自己
	bool SinglePlayerTeamPickUpItem(int iItem);

private:
    void SetItem(SCharItem& kItem, int index);
    void PickOneItem(const SCharItem& kItem);
    short CalculateTotalPage(int nCurPage, int nDisplayNumPerPage);
    void ClearItemList();
    void ShowAssignMemberList();
    void RemovePlayerFromAssignList(uint32 iPlayerDBID);


    struct LootItemData
    {
        bool        bHasItem;
        SCharItem   kItem;
        bool        bCanLoot;
        bool        bNeedLeadAssign;        // 需要队长分配
    };
    struct TeamMemberAssignData
    {
        uint32      nPlayerDBID;
        char        szPlayerName[64];
    };

    LootItemData    kLootItemList[MaxPackageItemCount];
    short           sCurrentPage;
    short           sTotalPage;
    short           sItemCount;
    short           sItemNumPerPage;
    int             nItemPackageID;
    bool            bNeedSendCloseMsg;
    int             nCurrentSelectItem;

    std::vector<TeamMemberAssignData> vctTeamMemberAssignList;        // 需要队长分配物品的队员列表
};
extern CUI_ID_FRAME_PickUp s_CUI_ID_FRAME_PickUp;
