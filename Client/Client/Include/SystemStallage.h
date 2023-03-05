/********************************************************************
            新摆摊系统        by ZhuoMeng.Hu		[12/23/2010]
*********************************************************************/

#pragma once

#include "Singleton.h"
#include "StallMessage.h"
#include "StallDefine.h"
#include "GlobalDef.h"
#include "ItemEnableChangeSysBase.h"

class CSystemStallage : public Singleton<CSystemStallage>, CItemEnableChangeSysBase
{
public:
    struct StallageItem 
    {
        StallageItem()
        {
            m_nBagType = -1;
            m_nSrcIndex = -1;
            m_nDestIndex = -1;
            m_nCount = -1;
            m_nMoneyPrice = 0;
            m_nItemId = 0;
            m_nGuid = 0;
        }
        int         m_nBagType;
        int         m_nSrcIndex;
        int         m_nDestIndex;
        int         m_nCount;
        int         m_nMoneyPrice;
        int         m_nItemId;
        __int64     m_nGuid;
    };

public:
    ~CSystemStallage();

    virtual bool IsPackItemBeUsing( __int64 nGuid );

    // 服务端发来的消息处理
    void TellPlayerStartStall( int nPlayerId, int nModelId, const char* pTitle, bool bIsOffline_);   // 通知附近玩家，某人摆摊了
    void TellPlayerCloseStallage( int nPlayerId );                                  // 通知附近玩家关闭摊位
    void TellPlayerTitleChange( int nPlayerId, const char* pTitle );                // 通知附近玩家某摊位改名了

    void ShowSelfStallageData( const MsgTellTotalStallData* pMsg );                 // 自己摊位打开时同步服务端的数据
    void TellSelfStallageUpdate( const MsgUpdateStallData* pMsg );                  // 更新自己的摊位信息 (增加、移除)
    void TellSelfGoodsPriceChange( int nIndex, int nMoneyPrice, int nGoldPrice );   // 更新自己的物品价格
    void AddSelfTradeRecord( MsgTellBuyOrSellStallData* pMsg );                     // 自己摆摊的交易记录

    void TellPlayerStallageData( MsgShowStallData* pMsg );                          // 通知玩家摊位数据
    void TellPlayerStallageCountChange( int nTotalIndex, int nCount );              // 玩家摊位物品数量改变

    void TellAddSellResult( int nResult );                                          // 添加一个出售物品回馈
    void TellAddBuyResult( int nResult );                                           // 添加一个回购物品回馈
    void TellQuestStallResult( int nResult );                                       // 摆摊请求回馈
    void TellErrorsInStall( int nErrorType );                                       // 摆摊过程中各种交易错误

	void SendOpenStallMsg(bool bOnline_);

    // 用户UI界面操作处理
    void OpenStallageWindow();                                                      // 打开摆摊界面，请求同步摊位数据
	void OpenStallageWindow2(void);
    void MoveFromPackToGoodsSell( int nDestIndex, int nSrcIndex, int nBagType );    // 从背包往摊位物品栏移动
    void MoveMountToSell( int nDestIndex, int nSrcIndex );                          // 从兽栏往摊位坐骑栏移动
    void MoveFromPackToGoodsBuy( int nDestIndex, int nSrcIndex, int nBagType );     // 从背包往摊位收购栏移动
    static bool AddItemToStallageSell( DWORD dwPrice, void *pData );                // 出售金钱输入框回调
    static bool AddItemToStallageBuy( DWORD dwPrice, int nCount, void *pData );     // 收购输入框回调
    void MoveGoodsInSellSlots( int nSrcIndex, int nDestIndex );                     // 物品出售栏内移动
    void MoveMountInSellSlots( int nSrcIndex, int nDestIndex );                     // 坐骑栏内物品移动
    void MoveGoodsInBuySlots( int nSrcIndex, int nDestIndex );                      // 收购栏内物品移动
    void RemoveGoodsSell( int nIndex );                                             // 出售栏内移除物品
    void RemoveMountSell( int nIndex );                                             // 坐骑栏内移除物品
    void RemoveGoodsBuy( int nIndex );                                              // 收购栏内移除物品
    void StartStallRequest();                                                       // 点击开始摆摊
    void CloseStallRequest();                                                       // 点击收摊
    void ChangeStallName();                                                         // 点击更改摊位名称
    void TellStallageName( const char* pName );                                     // 更改的摊位名称
    void SetItemPrice( int nIndex, bool bIsSell, bool bIsMount, __int64 nGuid );    // 点击设置价格
    static bool SelfStallageSetPrice( DWORD dwPrice, void *pData );                 // 设置价格输入框回调
    void ClearTradeRecord();                                                        // 清空交易记录

    void QuerryPlayerStallageRequest( int nPlayerId );                              // 点击查看别人的摊位
    void LeaveMessageToVender();                                                    // 给摊主留言
    void GetItemFromVenderSell( int nIndex, bool bIsMount, __int64 nGuid );         // 从摊主处购买东东
    static bool BuyItemFromVender( const char* szInputData, void *pData );          // 从摊主处购买东东数目输入框回调
    static bool SellItemToVender( const char* szInputData, void *pData );           // 卖给摊主东东数目输入框回调
    void MoveItemToVenderBuy( int nBagType, int nSrcIndex, int nDestIndex, __int64 nGuid );                     // 将物品拖至摊主收购栏内

	//增加宠物到柜台
	void AddPetToSell(SPetItem &pet_, int srcIndex_, int destIndex_);
	//从柜台移除宠物
	void RemovePetSell(int index_);
	void RemovePetSell(SPetItem &pet_);
    
    // 接口
    bool IsSelfInStalling();                                                        // 自己是否在摆摊
    bool IsPlayerInStalling( int nPlayerId );                                       // 玩家是否在摆摊
    bool IsMountInStallage( __int64 nGuid );                                        // 坐骑是否在摊位中
	bool IsPetInStallage(__int64 nGuid );
    int  GetMountIndexByGuid( __int64 nGuid );                                      // 坐骑在哪一格
    void SetCharItemEnable( __int64 nGuid, bool bEnable );                          // 设置玩家背包栏和兽栏的 Enablehe 和 Disable
    bool CheckMeExist();                                                            // 判断 GetPlayerMgr()->GetMe()
    bool CheckPlayerExist( int nPlayerId );                                         // 判断 GetPlayerMgr()->FindById()

    int  GetVenderId();                                                             // 获取摊主ID
    void SeekSelfMountByIndex( int nIndex, __int64 nGuid );                         // 查看自己摊位的坐骑，Guid用于校验
    void SeekPlayerMountByIndex( int nIndex, __int64 nGuid );                       // 查看摊主的坐骑，Guid用于校验
    const std::vector<std::string>& GetTradeRecord();                               // 获取交易记录
    std::string GetPriceTipString( DWORD dwPrice );                                 // 获取Tip价格描述
    void RefreshCharItemsInStallage();                                              // 刷新在摊位中的背包内物品， Enablehe 和 Disable

    bool GetSelfItemPrice( IN int nIndex, IN bool bIsSell, IN bool bIsMount,
        OUT int& nMoneyPrice, OUT int& nGoldPrice, OUT int& nCount );               // 获取自己商品价格信息

    bool GetPlayerItemPrice( IN int nIndex, IN bool bIsSell, IN bool bIsMount,
        OUT int& nMoneyPrice, OUT int& nGoldPrice, OUT int& nCount );               // 获取摊主商品价格信息

    // 内部逻辑
    void TellSelfEnterWorld();                                                      // 角色登陆，用于初始化
    int GetBuyStackNumLimit();                                                      // 收购物品堆叠最大数量限制
    SellDataToClient* GetPlayerSellData();                                          // 获取本地摊主出售数据
    BuyDataToClient* GetPlayerBuyData();                                            // 获取本地摊主收购数据

protected:
    int GetSubIndexByTotalIndex( int nIndex, int nUsage, int nBagType = BT_NormalItemBag );                     // 根据服务端的索引获取客户端的
    int GetTotalIndexBySubIndex( int nIndex, int nUsage, int nBagType = BT_NormalItemBag );                     // 根据客户端的索引获取服务端的
    bool ClassifyByTotalIndex( IN int nTotalIndex, OUT int& nSubIndex, OUT int& nUsage, OUT bool& bIsMount );   // 根据服务端的索引获取其他信息

    void ClearSelfStallage();                                                       // 清空自己本地摊位数据
    void ClearPlayerStallage();                                                     // 清空摊主本地摊位数据


private:
    friend class Singleton<CSystemStallage>;
    CSystemStallage();

public:
	enum EGoodsType
	{
		E_Goods_common = 0,
		E_Goods_pet,
		E_Goods_mount,//E_Goods_replace,
		E_Goods_replace,//E_Goods_mount,
		E_Goods_buy,
		E_Goods_end,
	};

	EGoodsType GetGoodInfo(int index_, int &_subIndex);
	bool CheckGoodIndex(int index_, EGoodsType goodType_);	//检验物品的totalIndex是否合法
	void SetItemPrice(int totalIndex_);
	int GetTotalIndexBySubIndex(int subIndex_, EGoodsType goodType_);
	bool GetSelfItemPrice(int subIndex_, EGoodsType goodType_, int &_moneyPrice, int &_goldPrice, int &_count);
	bool GetPlayerItemPrice(int subIndex_, EGoodsType goodType_, int &_moneyPrice, int &_goldPrice, int &_count);
	void GetItemFromVenderSell( int totalIndex_);         // 从摊主处购买东东

private:
    const int m_nItemSellIndexBegin;                // 物品出售索引起始值
    const int m_nMountSellIndexBegin;               // 坐骑出售索引起始值
    const int m_nItemBuyIndexBegin;                 // 物品收购索引起始值

	static const int m_goodsIndex[E_Goods_end + 1];

    const int m_nItemBuyStackCnt;                   // 收购物品堆叠最大数量限制

    bool m_bStallageFirstShow;                      // 角色是否第一次自己摆摊
    int m_nVenderPlayerId;                          // 记录摊主的Id
    std::vector<std::string>    m_tradeRecordVec;   // 交易记录

    // 客户端保存一份摊位数据
    StallData           m_selfStallData[ StallDefine::MaxStallCount ];
    BuyDataToClient     m_playerBuyData[ StallDefine::MaxStallCount ];
    SellDataToClient    m_playerSellData[ StallDefine::MaxStallCount ];

	bool m_bOnlineStall;	//是否为在线摆摊
};
