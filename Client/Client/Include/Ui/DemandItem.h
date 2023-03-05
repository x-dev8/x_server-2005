/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\package\DemandItem.h
    物品掷骰子
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"

#ifndef ID_FRAME_DemandItem
#define ID_FRAME_DemandItem		"ID_FRAME_DemandItem"
#endif  ID_FRAME_DemandItem
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_BUTTON_Demand
#define ID_BUTTON_Demand		"ID_BUTTON_Demand"
#endif  ID_BUTTON_Demand
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_LISTIMG_Item
#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
#endif  ID_LISTIMG_Item
#ifndef ID_PICTURE_9017
#define ID_PICTURE_9017		"ID_PICTURE_9017"
#endif  ID_PICTURE_9017
#ifndef ID_PROGRESS_27816
#define ID_PROGRESS_27816		"ID_PROGRESS_27816"
#endif  ID_PROGRESS_27816
#ifndef ID_BUTTON_GiveUp
#define ID_BUTTON_GiveUp		"ID_BUTTON_GiveUp"
#endif  ID_BUTTON_GiveUp

#include "UiBase.h"
class CUI_ID_FRAME_DemandItem  :public CUINotManagedByUIMgr
{
	// Member
public:	
	 CUI_ID_FRAME_DemandItem(int frameIndex);
private:
	 ControlFrame*	m_pID_FRAME_DemandItem;
	 ControlButton*	m_pID_BUTTON_Close;
	 ControlButton*	m_pID_BUTTON_Demand;
	 ControlText*	m_pID_TEXT_Name;
	 ControlListImage*	m_pID_LISTIMG_Item;
	 ControlPicture*	m_pID_PICTURE_9017;
	 ControlProgress*	m_pID_PROGRESS;
	 ControlButton*	m_pID_BUTTON_GiveUp;
public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DemandOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_GiveUpOnButtonClick( ControlObject* pSender );
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    void AddItem( int nItemPackageID, SCharItem& kCharItem, DWORD dwStart, DWORD dwEnd );

	ControlIconDrag::S_ListImg* GetItemByIndex( int i );
private:
    int             m_FrameIndex;                   // 并列的第几个frame
    ControlFrame*	m_pObject;
    char	        szFrameID[64];                  // Frame唯一标识

    DWORD           m_dwStartCountDownTime;   // 开始倒计时时间
    DWORD           m_dwEndCountDownTime;     // 结束倒计时时间
    int             m_nItemPackageID;


};

class DemandItemFrameMgr 
{
public:
    DemandItemFrameMgr();
    ~DemandItemFrameMgr();
    void					Reset();
    void					SetVisable( const bool bVisable );			// 设置是否可视
    CUI_ID_FRAME_DemandItem*    CreateFrame(int index);
    bool                    AddDemandItem(int nPackageID, const SCharItem& kCharItem, int iCountDown);
    bool                    RemoveDemandItem( CUI_ID_FRAME_DemandItem* pDemandItem );
    bool                    IsVisable();
    SCharItem*              GetItemInResultList(__int64 nItemID);
    void                    RemoveItemInResultList(__int64 nItemID);
    void                    Update();
public:
    bool OnFrameRunIndexedFrame(int index);
    bool OnFrameRenderIndexedFrame(int index);
    bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_DemandOnButtonClick( ControlObject* pSender );
    bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
    bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_BUTTON_GiveUpOnButtonClick( ControlObject* pSender );
    int  GetFrameIndexByChildWidget(ControlObject* pSender);
    CUI_ID_FRAME_DemandItem*				GetDemandItemByIndex(int index);
    CUI_ID_FRAME_DemandItem*				GetDemandItemByChildWidget(ControlObject* pSender);
    CUI_ID_FRAME_DemandItem*				GetActiveTeamFrame();

    struct DemandItemData
    {
        int         nItemPackageID;
        SCharItem   kItem;
        bool        bDisplay;               // 如果CUI_ID_FRAME_DemandItem显示个数已满，则置为false
        DWORD       dwStartCountDownTime;   // 开始倒计时时间
        DWORD       dwEndCountDownTime;     // 结束倒计时时间
    };
private: 
    std::vector<CUI_ID_FRAME_DemandItem*>   mDemandItemArr;
    int	m_ActiveIndex;

    std::vector<DemandItemData>             m_vctDemandItemData;    // 所有需要掷骰子的物品列表

    std::vector<SCharItem>                  m_vctItemWaitResult;    // 掷骰子后把SCharItem挪进来等待结果
};

extern DemandItemFrameMgr DemandItemFrameManage;
