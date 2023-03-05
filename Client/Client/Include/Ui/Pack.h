/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\Pack.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "../PlayerAnimCtrl.h"
#include "GlobalDef.h"
#include "MessageDefine.h"
#include "bag\ItemBag2.h"

#ifndef ID_FRAME_PACK
#define ID_FRAME_PACK		"ID_FRAME_PACK"
#endif  ID_FRAME_PACK
#ifndef ID_PICTURE_Di
#define ID_PICTURE_Di		"ID_PICTURE_Di"
#endif  ID_PICTURE_Di
#ifndef ID_PICTURE_Di2
#define ID_PICTURE_Di2		"ID_PICTURE_Di2"
#endif  ID_PICTURE_Di2
#ifndef ID_PICTURE_Icon_Di
#define ID_PICTURE_Icon_Di		"ID_PICTURE_Icon_Di"
#endif  ID_PICTURE_Icon_Di
#ifndef ID_LISTIMG_PACK
#define ID_LISTIMG_PACK		"ID_LISTIMG_PACK"
#endif  ID_LISTIMG_PACK
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_LISTIMG_Task
#define ID_LISTIMG_Task		"ID_LISTIMG_Task"
#endif  ID_LISTIMG_Task
#ifndef ID_PICTURE_FenGe
#define ID_PICTURE_FenGe		"ID_PICTURE_FenGe"
#endif  ID_PICTURE_FenGe
#ifndef ID_PICTURE_Money_Di
#define ID_PICTURE_Money_Di		"ID_PICTURE_Money_Di"
#endif  ID_PICTURE_Money_Di
#ifndef ID_TEXT_MONEY
#define ID_TEXT_MONEY		"ID_TEXT_MONEY"
#endif  ID_TEXT_MONEY
#ifndef ID_PICTURE_title2
#define ID_PICTURE_title2		"ID_PICTURE_title2"
#endif  ID_PICTURE_title2
#ifndef ID_PICTURE_title
#define ID_PICTURE_title		"ID_PICTURE_title"
#endif  ID_PICTURE_title
#ifndef ID_PICTURE_yuanbao
#define ID_PICTURE_yuanbao		"ID_PICTURE_yuanbao"
#endif  ID_PICTURE_yuanbao
#ifndef ID_PICTURE_money
#define ID_PICTURE_money		"ID_PICTURE_money"
#endif  ID_PICTURE_money
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_MONEY2
#define ID_TEXT_MONEY2		"ID_TEXT_MONEY2"
#endif  ID_TEXT_MONEY2
#ifndef ID_TEXT_MONEY1
#define ID_TEXT_MONEY1		"ID_TEXT_MONEY1"
#endif  ID_TEXT_MONEY1
#ifndef ID_LISTIMG_rubbish
#define ID_LISTIMG_rubbish		"ID_LISTIMG_rubbish"
#endif  ID_LISTIMG_rubbish
#ifndef ID_LISTIMG_Split
#define ID_LISTIMG_Split		"ID_LISTIMG_Split"
#endif  ID_LISTIMG_Split
#ifndef ID_BUTTON_rubbish
#define ID_BUTTON_rubbish		"ID_BUTTON_rubbish"
#endif  ID_BUTTON_rubbish
#ifndef ID_BUTTON_Split
#define ID_BUTTON_Split		"ID_BUTTON_Split"
#endif  ID_BUTTON_Split
#ifndef ID_BUTTON_Baitan
#define ID_BUTTON_Baitan		"ID_BUTTON_Baitan"
#endif  ID_BUTTON_Baitan

#ifndef ID_BUTTON_Clean
#define ID_BUTTON_Clean		"ID_BUTTON_Clean"
#endif  ID_BUTTON_Clean

#ifndef ID_CHECKBOX_Decompose
#define ID_CHECKBOX_Decompose	"ID_CHECKBOX_Decompose"
#endif  ID_CHECKBOX_Decompose

#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_CHECKBOX_Zhuangbei
#define ID_CHECKBOX_Zhuangbei		"ID_CHECKBOX_Zhuangbei"
#endif  ID_CHECKBOX_Zhuangbei
#ifndef ID_CHECKBOX_Material
#define ID_CHECKBOX_Material "ID_CHECKBOX_Material"
#endif  ID_CHECKBOX_Material
#ifndef ID_CHECKBOX_Task
#define ID_CHECKBOX_Task "ID_CHECKBOX_Task"
#endif  ID_CHECKBOX_Task
#ifndef ID_TEXT_JinDing
#define ID_TEXT_JinDing		"ID_TEXT_Jinyuanbao"
#endif  ID_TEXT_JinDing
#ifndef ID_TEXT_JinPiao
#define ID_TEXT_JinPiao		"ID_TEXT_Yingyuanbao"
#endif  ID_TEXT_JinPiao
#ifndef ID_BUTTON_Lock
#define ID_BUTTON_Lock		"ID_BUTTON_Lock"
#endif  ID_BUTTON_Lock
#ifndef ID_BUTTON_Unlock
#define ID_BUTTON_Unlock		"ID_BUTTON_Unlock"
#endif  ID_BUTTON_Unlock
#ifndef ID_PICTURE_Tip
#define ID_PICTURE_Tip		"ID_PICTURE_Tip"
#endif  ID_PICTURE_Tip
// #ifndef ID_TEXT_EspecialMoneyZ
// #define ID_TEXT_EspecialMoneyZ		"ID_TEXT_EspecialMoneyZ"
// #endif  ID_TEXT_EspecialMoneyZ
#ifndef ID_TEXT_EspecialMoney
#define ID_TEXT_EspecialMoney		"ID_TEXT_EspecialMoney"
#endif  ID_TEXT_EspecialMoney
#ifndef ID_PICTURE_Tip2
#define ID_PICTURE_Tip2		"ID_PICTURE_Tip2"
#endif  ID_PICTURE_Tip2
#ifndef ID_PROGRESS_TaskItemEff
#define ID_PROGRESS_TaskItemEff		"ID_PROGRESS_TaskItemEff"
#endif  ID_PROGRESS_TaskItemEff

#ifndef ID_BUTTON_PocketShop
#define ID_BUTTON_PocketShop		"ID_BUTTON_PocketShop"
#endif	ID_BUTTON_PocketShop
#ifndef ID_BUTTON_Star
#define ID_BUTTON_Star				"ID_BUTTON_Star"
#endif	ID_BUTTON_Star
#ifndef ID_BUTTON_GemUp
#define ID_BUTTON_GemUp				"ID_BUTTON_GemUp"
#endif	ID_BUTTON_GemUp
#ifndef ID_BUTTON_Gem
#define ID_BUTTON_Gem				"ID_BUTTON_Gem"
#endif	ID_BUTTON_Gem

#ifndef ID_BUTTON_Changku
#define ID_BUTTON_Changku				"ID_BUTTON_Changku"
#endif	ID_BUTTON_Changku

#ifndef ID_BUTTON_mend
#define ID_BUTTON_mend		"ID_BUTTON_mend"
#endif  ID_BUTTON_mend
#ifndef ID_BUTTON_mend2
#define ID_BUTTON_mend2		"ID_BUTTON_mend2"
#endif  ID_BUTTON_mend2

#ifndef ID_TEXT_JIFEN
#define ID_TEXT_JIFEN		"ID_TEXT_JIFEN"
#endif  ID_TEXT_JIFEN



struct HotKeyPackData
{
    int iHotKeyIndex;
    unsigned short ustItemID;
};

#include "UiBase.h"

class CUI_ID_FRAME_PACK : public CUIBase, CUIIntonationUtility
{
    // Member
public:	
    CUI_ID_FRAME_PACK();
private:
    void ResetMembers();
    ControlFrame*	m_pID_FRAME_PACK;
    // 	ControlPicture*	m_pID_PICTURE_Di;
    // 	ControlPicture*	m_pID_PICTURE_Di2;
    // 	ControlPicture*	m_pID_PICTURE_Icon_Di;
    ControlListImage*	m_pID_LISTIMG_PACK;
    ControlListImage*	m_pID_LISTIMG_Material;
    ControlListImage*	m_pID_LISTIMG_Task;
    // 	ControlPicture*	m_pID_PICTURE_FenGe;
    // 	ControlPicture*	m_pID_PICTURE_Money_Di;
    ControlText*	m_pID_TEXT_MONEY;
	ControlText*	m_pID_TEXT_JIFEN;
    // 	ControlPicture*	m_pID_PICTURE_title2;
    // 	ControlPicture*	m_pID_PICTURE_title;
    // 	ControlPicture*	m_pID_PICTURE_yuanbao;
    ControlPicture*	m_pID_PICTURE_money;
    ControlButton*	m_pID_BUTTON_CLOSE;
    // 	ControlListImage*	m_pID_LISTIMG_rubbish;
    // 	ControlListImage*	m_pID_LISTIMG_Split;
    // 	ControlButton*	m_pID_BUTTON_rubbish;
    ControlButton*	m_pID_BUTTON_Split;
    ControlButton*	m_pID_BUTTON_Baitan;
    ControlButton*	m_pID_BUTTON_Clean;

	ControlCheckBox*  m_pID_CHECKBOX_Decompose;

    //	ControlButton*	m_pID_BUTTON_help;
    ControlCheckBox* m_pID_CHECKBOX_Zhuangbei;
    ControlCheckBox* m_pID_CHECKBOX_Material;
    ControlCheckBox* m_pID_CHECKBOX_Task;

    ControlText* m_pID_TEXT_JinDing;
    ControlText* m_pID_TEXT_JinPiao;
    ControlButton*	m_pID_BUTTON_Lock;
    ControlButton*	m_pID_BUTTON_Unlock;
    // ControlPicture*	m_pID_PICTURE_Tip;
    //      ControlText*	m_pID_TEXT_EspecialMoneyZ;
    ControlText*	m_pID_TEXT_EspecialMoney;
    //ControlPicture*	m_pID_PICTURE_Tip2;
    ControlProgress*   m_pID_PROGRESS_TaskItemEff;

	ControlButton*		m_pID_BUTTON_PocketShop;
	ControlButton*		m_pID_BUTTON_Changku;
	ControlButton*		m_pID_BUTTON_Star;		//装备升星
	ControlButton*		m_pID_BUTTON_GemUp;		//装备打孔
	ControlButton*		m_pID_BUTTON_Gem;		//装备打孔

	ControlButton*	m_pID_BUTTON_mend;
	ControlButton*	m_pID_BUTTON_mend2;

public:
    struct MoveSameItemDifInBoundData
    {
        MoveSameItemDifInBoundData()
        {
            indexScr = -1;
            indexDst = -1;
            pBagListImg = NULL;
            pBag = NULL;
            bagType = -1;
            nCount = 0;
            bIsSplit = false;
        }

        MoveSameItemDifInBoundData& operator = ( const MoveSameItemDifInBoundData& data )
        {
            if( this != &data )
            {
                indexScr        = data.indexScr;
                indexDst        = data.indexDst;
                pBagListImg     = data.pBagListImg;
                pBag            = data.pBag;
                bagType         = data.bagType;
                msg             = data.msg;
                nCount          = data.nCount;
                bIsSplit        = data.bIsSplit;
            }
            return *this;
        }

        int indexScr;
        int indexDst;
        ControlListImage* pBagListImg;
        CItemBag2* pBag;
        int bagType;
        MsgMoveGoodsReq msg;
        int nCount;
        bool bIsSplit;
    };

public:
    int GetPackImageIndex(ControlIconDrag::S_ListImg *pImg);
    int GetMaterialImageIndex(ControlIconDrag::S_ListImg *pImg);

    // Frame
    bool OnFrameRun();
    bool OnFrameRender();
    bool ID_LISTIMG_PACKOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
    bool ID_LISTIMG_PACKOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_PACKOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_PACKOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
    bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_TaskOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
    bool ID_LISTIMG_TaskOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_TaskOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_TaskOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
    // 	bool ID_LISTIMG_rubbishOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
    // 	bool ID_LISTIMG_rubbishOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    // 	bool ID_LISTIMG_rubbishOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    // 	bool ID_LISTIMG_rubbishOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    // 	bool ID_LISTIMG_SplitOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
    // 	bool ID_LISTIMG_SplitOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    // 	bool ID_LISTIMG_SplitOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    // 	bool ID_LISTIMG_SplitOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    //	bool ID_BUTTON_rubbishOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_SplitOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_BaitanOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_CleanOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_DecomposeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked );
    //bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
    void ID_CHECKBOX_ZhuangbeiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_MaterialOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_TaskOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    bool ID_BUTTON_LockOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_UnlockOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PocketShopOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ChangkuOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_StarOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GemUpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GemOnButtonClick( ControlObject* pSender );


	bool ID_BUTTON_mendOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_mend2OnButtonClick( ControlObject* pSender );
private:
    virtual bool _LoadUI();				// 载入UI
    bool DoControlConnect();	// 关连控件
    virtual bool _UnLoadUI();			// 卸载UI
    virtual bool _IsVisable();			// 是否可见
    virtual void _SetVisable( const bool bVisable );			// 设置是否可视
    virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();


	void OpenChangKu();
	void OnUpdateUIShopAndCK();
public:
    // Frame操作
    bool IsSameFrame(ControlFrame* pFrame);
    ControlFrame* GetFrame() {return m_pID_FRAME_PACK;}
    void SetFrameArrayMode( const int nMode );
    void MoveToXY(int x, int y) { m_pID_FRAME_PACK->MoveTo(x, y); }

    // 包裹操作
    int	GetBagType(ControlListImage* pImageSender);

    void RefreshPackByIndex(int index);
    void RefreshPackByIndex(int index, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType);

    bool IsListImageByBagType(int iBagType, ControlObject* pObject);
    ControlListImage* GetListImageByBagType(int iBagType);
    ControlIconDrag::S_ListImg* GetItemByIndex(int iBagType, int index);
    ControlIconDrag::S_ListImg* GetItemById(int iBagType, int id);
    int GetIndexByItem(int iBagType, ControlIconDrag::S_ListImg* pListImg);
    ControlIconDrag::S_ListImg* GetItemByXY(int iBagType, unsigned int nX, unsigned int nY);

    bool IsOpenPackByBagType(int iBagType);

    static bool dropIconFromPack(int indexScr, int indexDst, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType);
    static bool dropIconFromShop(ControlListImage* pObjListSrc, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType);
    static bool dropIconFromStorage(int inexSrc, int indexDst, ControlIconDrag* pDlgSrc, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType);
    static bool dropIconFromEquip(int indexScr, ControlIconDrag::S_ListImg* pItemDrag);

    static bool SparkMouseMoveOn( ControlIconDrag::S_ListImg* pImg, ControlIconDrag* pThis );

    // 相同物品的不同绑定状态合一起需要给出提示，由于背包本身写得很烂，这个需求又打乱了流程
    static bool IsSameItemDifInBound( __int64 nGuid1, int nIndex1, __int64 nGuid2, int nIndex2 );                 // 只适用于可堆叠物品
    static void ShowConfirmBoundMessageBox( const MoveSameItemDifInBoundData& data );
    static bool ConfirmBoundCallback( char bPressYesButton, void *pData );

    // 刷新界面
    void RefreshNormalPackByIndex(int index);
    void RefreshMaterialPackByIndex(int index);
    void RefreshTaskPackByIndex(int index);
    void Refeash();
    void RefreshMoney();
    void RefreshArmour();
    void RefreshJiaoZi(); //刷新交子

    void RefreshNormalPack();
    void RefreshMaterialPack();
    void RefreshTaskPack();
    void RefreshAllPack();

    void SetInUIFrameLock(bool bLock) { bInUIFrameLock = bLock; }
    bool GetInUIFrameLock() { return bInUIFrameLock; }

    void SetInUIFrameUnLock(bool bLock) { bInUIFrameUnLock = bLock; }
    bool GetInUIFrameUnLock() { return bInUIFrameUnLock; }

    void SetSplitCount(int nCount) { m_nSplitCount = nCount; }
    int	 GetSplitCount() { return m_nSplitCount; }

	bool ShowSplitInputBox(ControlListImage* pBagListImg, ControlIconDrag::S_ListImg* pItem, CItemBag2* pBag, int bagType);

    void SetSplitItem(bool v);
    bool GetSplitItem();
    void DisableSplitItem();

	bool IsDecomposeItem();
	void DecomposeItem(bool cancel);

    bool ChangeItemIdbyGuid(int iBagType, __int64 nOldGuid, uint16 ustNewItemID, __int64 nNewGuid);

    bool	UseItem(int nID, int nIndex, bool bUseSing = true);
    float	GetItemCost() { return fGetItemCost; }
    void	SetItemCost(float fCost) { fGetItemCost = fCost; }

    int&	GetGoodsCount() { return m_nGoodsCount; }
    void	SetGoodsCount(int nCount) { m_nGoodsCount = nCount; }
    DWORD	GetMoveCount() { return m_dwMoveCount; }

    void	SetTempNpcId(int nNpcId) { nTempNpcId = nNpcId; }
    int		GetTempNpcId() { return nTempNpcId; }

    bool	GetLockItem();
    void	SetLockItem(bool b);
    bool	GetUnLockItem();
    void	SetUnLockItem(bool b);

    void	SetDestroyItem(bool v);
    void	DisableDestroyItem();
    bool	GetDestroyItem() { return m_bDestroyItem; }

    int		GetItemInBagIndex() { return m_nItemInBagIndex; }
    int		GetEquipToWhereIndex() { return m_nEquipToWhereIndex; }

    int		GetForTargetItemIndex() { return m_nForTargetItemIndex; }

    // 喂养草料
    void UseMountRestoreItem();

    void ChangeMoney(int nCurrMoney);

    bool GetCancelOperator() { return m_bCancelOperator; }
    void SetCancelOperator(bool bCancel) { m_bCancelOperator = bCancel; }

    // 自动使用
    bool ActiveItem( ControlIconDrag* pListImgCtrl, CItemBag2* pBag, unsigned short usItemID, unsigned char ucActive );

    void showInUILayout( bool show );

    ControlIconDrag::S_ListImg* GetIntensifyGem( unsigned short ustLevel );
    ControlIconDrag::S_ListImg* GetIntensifyGemById( unsigned short ustItemId, unsigned short ustLevel );
    ControlIconDrag::S_ListImg* GetIntensifyAddRate();
    ControlIconDrag::S_ListImg* GetIntensifyAddRateByGUID( __int64 guid );
    ControlIconDrag::S_ListImg* GetIntensifyProtect();
    ControlIconDrag::S_ListImg* GetIntensifyProtectByGUID( __int64 guid );
    ItemDefine::SCreateMaterial* CanUseIntensifyGemById( unsigned short ustItemId, unsigned short ustArmourLevel );

    bool RemoveItem( EBagType eType, int nIndex, unsigned short usCount );
    bool RemoveItem( Msg* pMsg );
	bool RemoveItemByGuID(Msg* pMsg);

    void Equip( ControlObject* pSender, ControlObject* pMe,
        ControlIconDrag::S_ListImg* pItemDrag,
        ControlIconDrag::S_ListImg* pItemSrc );
    void Equip( unsigned int nWhere, unsigned int nPackIndex );

    void ClearHotkeyPackBackup() { m_vctHotkeyPackBackup.clear(); }
    void PushHotkeyPackBackup(HotKeyPackData xData) { m_vctHotkeyPackBackup.push_back(xData); }
    void UpdateHotkeyAfterClearupBag();

    /** 设置使用物品开始冷却
    */
    bool coolDownRestoreItem( ItemDefine::SItemRestore *pItemRestore, const SCharItem& stItem );
    void RefreshCooldown();

    void PushGoods( SCharItem* pItem );
    bool BuyOrSellGoods( MsgAckBuyOrSellGoods* pMsg );
    bool BuyBackOrSellBackGoods( MsgAckBuyOrSellGoods* pMsg ,MsgBuyBackItemAck* ack );

    void SwitchToBag(int iBagType);	// 打开特定背包分页
    void EnableSlotSpark( int nId, bool bEnable );
    void ClearSlotSpark();

    void DisplayTaskItemEff( int nBagType, int nItemId );       // 指定背包内物品播特效 (任务)
    void StopTaskEff();

    int GetEquipPos();
    void SetEquipPos( int nPos );

	bool IsList(const ControlObject* pObject);
	
	void ClearMotion();//所有背包中操作单个物品的操作RESET，注意这里只设置FLAG，涉及到鼠标指针变化需要额外写代码

	void SellItem(ControlIconDrag::S_ListImg* pListImg, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType);

	bool UseItem(ControlListImage* pBagListImg, CItemBag2* pBag, int bagType, int nID, int nIndex, bool bUseSing = true);
	ControlListImage* GetBagListImg() { return m_pID_LISTIMG_PACK; }
	ControlListImage* GetMaterialListImg() { return m_pID_LISTIMG_Material; }
	ControlListImage* GetTaskListImg() { return m_pID_LISTIMG_Task; }
private:

    void Refresh(ControlListImage* pBagListImg, CItemBag2* pBag, int bagType);


    static void IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

    void UpdateIconInfo();

    // 自动使用
    bool ActiveAutoUseItem( ControlIconDrag* pListImgCtrl, ItemDefine::SItemRestore *pItemRestore, SCharItem& stItem, CItemBag2* pBag, int nIndex );

    void PopGoods( const unsigned int nIndex, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType );

    void ShowTaskItemInfo( ItemDefine::SItemCommon *pItem );

    void CheckTaskItemEff();
	
private:
    bool bInUIFrameLock;
    bool bInUIFrameUnLock;
    DWORD m_dwMoveCount;
    int m_nItemInBagIndex;
    int m_nEquipToWhereIndex;
    int	m_nForTargetItemIndex;
    int	m_nGoodsCount;
    float fGetItemCost;
    int nTempNpcId;
    bool m_bStartIntensify;
    DWORD m_dwLastTime;

    ControlGroup	m_PackGroup;
    ControlGroup	m_MaterialGroup;
    ControlGroup	m_TaskGroup;
    ControlTabGroup m_BagTabGroup;

    bool m_bDestroyItem;
    void EnableDestroyItem();

    int m_nSplitCount;
    bool m_bSplitItem;
    bool m_bShiftRBSplitItem;
    void EnableSplitItem();

    void EnableLockItem();
    void DisableLockItem();
    void EnableUnLockItem();
    void DisableUnLockItem();

    

    bool m_bLockItem;
    bool m_bUnLockItem;

    struct
    {
        bool	m_bQuestUseItem;
        DWORD	m_dwQuestUseItemStartTime;
        DWORD	m_dwQuestTime;
        int		nId;
        int		nIndex;
    }m_stQuestUseItem;

    bool m_bCancelOperator;

    bool CanEquip(ItemDefine::SItemCanEquip *pCanEquip);

    bool PackOnIconDragOn(ControlListImage* pDlgDrag, ControlListImage* pDlgSrc, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc, CItemBag2* pBag, int bagType);
    bool PackOnIconButtonClick(ControlListImage* pBagListImg, ControlIconDrag::S_ListImg* pItem, CItemBag2* pBag, int bagType);
    bool PackOnIconRButtonUp(ControlListImage* pBagListImg, ControlIconDrag::S_ListImg* pItem, CItemBag2* pBag, int bagType);

    //bool UseItem(ControlListImage* pBagListImg, CItemBag2* pBag, int bagType, int nID, int nIndex, bool bUseSing = true);

    std::vector<HotKeyPackData> m_vctHotkeyPackBackup;  // 整理普通包裹前，保存快捷栏上物品的ItemID
    std::map<int, bool>         m_newEquipMap;          // 记录NormalBag里新获得    added by ZhuoMeng.Hu		[11/12/2010]

    // 检查任务道具指引特效用
    int                         m_nTaskEffBagType;
    int                         m_nTaskEffIndex;
    __int64                     m_nTaskEffGuid;  
    bool                        m_bTaskEffNeedCheck;

    int                         m_nEquipPos;            // 穿装备指定部位   added by ZhuoMeng.Hu		[1/12/2011]

public:
    bool LoadGrassItemID();   //载入草料ID集合
    bool IsGrassID(int nItemID); //是否为草料ID
private:
    std::vector<int> m_GrassIDSet; //草料集合
public:
	bool IsCanFixBag();

	void CallIntonationUtility_Start( void* pData );
private:
	bool m_bRepair;
};
extern CUI_ID_FRAME_PACK s_CUI_ID_FRAME_PACK;
