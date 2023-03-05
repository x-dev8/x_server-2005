/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Bargaining.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MessageDefine.h"
#include "BargainingMessage.h"
#include "UiBase.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_Bargaining
#define ID_FRAME_Bargaining		"ID_FRAME_Bargaining"
#endif  ID_FRAME_Bargaining
#ifndef ID_BUTTON_Lock
#define ID_BUTTON_Lock			"ID_BUTTON_Lock"
#endif  ID_BUTTON_Lock
#ifndef ID_BUTTON_Complete
#define ID_BUTTON_Complete		"ID_BUTTON_Complete"
#endif  ID_BUTTON_Complete
#ifndef ID_LISTIMG_Me
#define ID_LISTIMG_Me			"ID_LISTIMG_Me"
#endif  ID_LISTIMG_Me
#ifndef ID_LISTIMG_Player
#define ID_LISTIMG_Player		"ID_LISTIMG_Player"
#endif  ID_LISTIMG_Player
#ifndef ID_TEXT_Player
#define ID_TEXT_Player			"ID_TEXT_Player"
#endif  ID_TEXT_Player
#ifndef ID_TEXT_PlayerGold
#define ID_TEXT_PlayerGold		"ID_TEXT_PlayerGold"
#endif  ID_TEXT_PlayerGold
#ifndef ID_TEXT_MeGold
#define ID_TEXT_MeGold		    "ID_TEXT_MeGold"
#endif  ID_TEXT_MeGold
#ifndef ID_PICTURE_SelfLock
#define ID_PICTURE_SelfLock		"ID_PICTURE_SelfLock"
#endif  ID_PICTURE_SelfLock
#ifndef ID_PICTURE_PlayerLock
#define ID_PICTURE_PlayerLock	"ID_PICTURE_PlayerLock"
#endif  ID_PICTURE_PlayerLock
#ifndef ID_TEXT_SelfName
#define ID_TEXT_SelfName		"ID_TEXT_SelfName"
#endif  ID_TEXT_SelfName
#ifndef ID_TEXT_PlayerName
#define ID_TEXT_PlayerName		"ID_TEXT_PlayerName"
#endif  ID_TEXT_PlayerName
#ifndef ID_BUTTON_Quit
#define ID_BUTTON_Quit		    "ID_BUTTON_Quit"
#endif  ID_BUTTON_Quit
#ifndef ID_LISTIMG_PlayerPet
#define ID_LISTIMG_PlayerPet	"ID_LISTIMG_PlayerPet"
#endif  ID_LISTIMG_PlayerPet
#ifndef ID_LISTIMG_MyPet
#define ID_LISTIMG_MyPet		"ID_LISTIMG_MyPet"
#endif  ID_LISTIMG_MyPet
#ifndef ID_BUTTON_SeekPlayerPet
#define ID_BUTTON_SeekPlayerPet	"ID_BUTTON_SeekPlayerPet"
#endif  ID_BUTTON_SeekPlayerPet
#ifndef ID_BUTTON_SeekMyPet
#define ID_BUTTON_SeekMyPet		"ID_BUTTON_SeekMyPet"
#endif  ID_BUTTON_SeekMyPet
#ifndef ID_BUTTON_MoneyInput
#define ID_BUTTON_MoneyInput	"ID_BUTTON_MoneyInput"
#endif  ID_BUTTON_MoneyInput

#ifndef ID_LIST_PlayerPet
#define ID_LIST_PlayerPet		"ID_LIST_PlayerPet"
#endif  ID_LIST_PlayerPet
#ifndef ID_LIST_SelfPet
#define ID_LIST_SelfPet		"ID_LIST_SelfPet"
#endif  ID_LIST_SelfPet


class CUI_ID_FRAME_Bargaining : public CUIBase, CItemEnableChangeSysBase
{
private:
	ControlFrame*	    m_pID_FRAME_Bargaining;
	ControlButton*	    m_pID_BUTTON_Lock;
	ControlButton*	    m_pID_BUTTON_Complete;
	ControlListImage*	m_pID_LISTIMG_Me;
	ControlListImage*	m_pID_LISTIMG_Player;
	ControlText*		m_pID_TEXT_Player;
	ControlText*		m_pID_TEXT_PlayerGold;
    ControlText*        m_pID_TEXT_MeGold;
	ControlPicture*	    m_pID_PICTURE_SelfLock;
	ControlPicture*	    m_pID_PICTURE_PlayerLock;
	ControlText*		m_pID_TEXT_SelfName;
	ControlText*		m_pID_TEXT_PlayerName;
	ControlButton*	    m_pID_BUTTON_Quit;
	ControlListImage*	m_pID_LISTIMG_PlayerPet;
	ControlListImage*	m_pID_LISTIMG_MyPet;
	ControlButton*	    m_pID_BUTTON_SeekPlayerPet;
	ControlButton*	    m_pID_BUTTON_SeekMyPet;
    ControlButton*      m_pID_BUTTON_MoneyInput;

	ControlList*		m_pID_LIST_PlayerPet;
	ControlList*		m_pID_LIST_SelfPet;

public:
	 CUI_ID_FRAME_Bargaining();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	// Button
	bool ID_BUTTON_LockOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_CompleteOnButtonClick( ControlObject* pSender );
	// ListImg / ListEx
	bool ID_LISTIMG_MeOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MeOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	// Edit
	bool ID_BUTTON_QuitOnButtonClick( ControlObject* pSender );

	bool ID_LISTIMG_MyPetOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MyPetOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_MyPetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_PlayerPetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_SeekPlayerPetOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SeekMyPetOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_MoneyInputOnButtonClick( ControlObject* pSender );

	void ID_LIST_PlayerPetOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_SelfPetOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	        // 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable);			// 设置是否可视

public:
	ControlFrame*	GetFrame() { return m_pID_FRAME_Bargaining; }
	ControlIconDrag::S_ListImg* GetLISTIMG_MyPetItem(const unsigned int nIndex);
    int  PetList_GetNullItem();
	bool OnIconDragOnFromPack(ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag);
	bool IsEqualToLISTIMG_Me(const ControlListImage* pItemDrag);
	void SetPlayer( const char* szPlayerName, int nId );
	// --- changed by huwen. -----
	void SetQueryBargaining( bool enabled );
	//----------------------------
	
    virtual bool IsPackItemBeUsing( __int64 nGuid );

    // 新的交易     added by ZhuoMeng.Hu		[12/15/2010]
    static bool QueryBargaining( const char bPressYesButton, void* pData = NULL );
    static void OnVisibleChanged( ControlObject* pSender );
    void TellRequestBargainResult( int nResult );
    void TellPlayerRequestBargain( int nPayerId );
    void TellBargainStart( int nPlayerId );
    void TellBargainFinish( int nType );
    void TellBargainStatus( int nPlayerId, int nStatusType );
    void TellBargainErrors( int nPlayerId, int nErrorType );
    void TellBargainSelfAddData( MsgBargainingDataAck* pMsg );
    void TellBargainPlayerAddData( MsgShowBargainingData* pMsg );
    void TellBargainRemoveData( MsgRemoveBargainingDataAck* pMsg );
    void SelfCancelBargain();
    static bool TellAddMoney( DWORD dwMoney, void* m_pData );
    bool IsSelfItemInBargaining( __int64 nGuid );
	
	void AddPetToBargain( int petIdx );
	void AddPetToBargainAck( int petIdx );
	void CallBackPetFromBargain( int petIdx );
	bool IsPetInBargain( int petIdx );
	void RefreshPetListUI();
protected:
    // added by ZhuoMeng.Hu		    [12/15/2010]
    void BargainReset();                                        // 交易开始前结束后重置面板
    void BargainSelfError();                                    // 交易过程中收到的服务器消息与本地不符时取消交易     
    void RenewItems();                                          // 交易失败或取消时将背包内或兽栏内失效的物品恢复
    void SetSelectMount( ControlIconDrag::S_ListImg* pItem );   // 选中坐骑
    void AddSelfItem( __int64 nGuid );                          // 增加本地保存自己的交易物品
    void RemoveSelfItem( __int64 nGuid );                       // 移除本地保存自己的交易物品

	std::string GetPetName( const SPetItem &pet );

private:
    int             m_nSelfStatus;
    int             m_nPlayerStatus;

    ControlIconDrag::S_ListImg*     m_pSelectMount;             // 选中的坐骑

    std::vector<__int64>            m_selfItems;                // 交易中自己的物品 <Guid>
	std::vector<SMountItem>         m_MountItems;

	std::vector<int>				m_petIDList;				// 交易宠物的列表
	std::vector<SPetItem>			m_PetItems;					// 对方宠物列表

	int				                m_nPlayerId;
	bool			                m_bQueryBargaining;

};
extern CUI_ID_FRAME_Bargaining s_CUI_ID_FRAME_Bargaining;
