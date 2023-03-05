#ifndef __CONSIGNMENT_H__
#define __CONSIGNMENT_H__
/************************************************************************
            FileName : Consignment.h

            寄售系统
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <map>
#include <vector>
#include "ConsignmentDefine.h"
#include "Singleton.h"
#include "GameTimer.h"
#include "MeRTLibsServer.h"
#include "Memory_Pool.h"

#define theConsignmentManager ConsignmentManager::Instance()

struct Msg;

class ConsignmentManager : public ISingletion< ConsignmentManager >
{
protected:
    // 帐号列表
    class Account : public ConsignmentAccount, INHERIT_POOL( Account )
    {
    public:
        DECLARE_POOL_FUNC(Account)

        Account() : ConsignmentAccount(), m_bIsWaitProcess( false ) {}

        bool IsWaitProcess() const { return m_bIsWaitProcess; }
        void SetWaitPorcess( bool bValue ) { m_bIsWaitProcess = bValue; }
    private:
        bool m_bIsWaitProcess;
    };

    class Consignment : public ConsignmentBase
    {
    public:
        Consignment() : ConsignmentBase(), m_bIsWaitProcess( false ) {}

        bool IsWaitProcess() const { return m_bIsWaitProcess; }
        void SetWaitPorcess( bool bValue ) { m_bIsWaitProcess = bValue; }
    private:
        bool m_bIsWaitProcess;
    };

    // 寄售金锭
    class SellRMB : public Consignment, INHERIT_POOL_PARAM( SellRMB, 50 )
    {
    public:
        DECLARE_POOL_FUNC(SellRMB);
    };

    // 收购金锭
    class BuyRMB : public Consignment, INHERIT_POOL_PARAM( BuyRMB, 50 )
    {
    public:
        DECLARE_POOL_FUNC(BuyRMB);
    };

    // 寄售物品
    class SellItem : public Consignment, INHERIT_POOL_PARAM( SellItem, 50 )
    {
    public:
        DECLARE_POOL_FUNC(SellItem);
    };

    // 收购物品
    class BuyItem : public Consignment, INHERIT_POOL_PARAM( BuyItem, 50 )
    {
    public:
        DECLARE_POOL_FUNC(BuyItem);
    };

    // 金锭收购寄售历史记录
    class RMBHistroy : public ConsignmentHistroy, INHERIT_POOL ( RMBHistroy )
    {
    public:
        DECLARE_POOL_FUNC(RMBHistroy);
    };

    // 物品收购寄售历史记录
    class ItemHistroy : public ConsignmentHistroy, INHERIT_POOL ( ItemHistroy )
    {
    public:
        DECLARE_POOL_FUNC(ItemHistroy);
    };

    // 定义帐号信息
    typedef std::map< unsigned long, Account* > MapAccount;   
    typedef MapAccount::iterator MapAccountIter;

    // 定义金锭寄售信息
    typedef std::map< __int64, SellRMB* > SellRMBMap;
    typedef SellRMBMap::iterator SellRMBMapIter;
    typedef std::pair< __int64, SellRMB* > SellRMBPair;

    typedef std::vector< SellRMB* > SellRMBVector;
    typedef SellRMBVector::iterator SellRMBVectorIter;

    // 定义金锭收购信息
    typedef std::map< __int64, BuyRMB* > BuyRMBMap;
    typedef BuyRMBMap::iterator BuyRMBMapIter;
    typedef std::pair< __int64, BuyRMB* > BuyRMBPair;

    typedef std::vector< BuyRMB* > BuyRMBVector;
    typedef BuyRMBVector::iterator BuyRMBVectorIter;

    // 定义物品寄售信息
    typedef std::map< __int64, SellItem* > SellItemMap;
    typedef SellItemMap::iterator SellItemMapIter;

    // 定义物品收购信息
    typedef std::map< __int64, BuyItem* > BuyItemMap;
    typedef BuyItemMap::iterator BuyItemMapIter;

    // 定义金锭历史记录
    typedef std::vector< RMBHistroy* > RMBHistroyVector;
    typedef RMBHistroyVector::iterator RMBHistroyVectorIter;
    typedef RMBHistroyVector::const_iterator RMBHistroyVectorConstIter;
    typedef std::map< unsigned long, RMBHistroyVector > RMBHistroyMap;
    typedef RMBHistroyMap::iterator RMBHistroyMapIter;

    // 定义物品历史记录
    typedef std::vector< ItemHistroy* > VectorItemHistroy;
    typedef VectorItemHistroy::iterator VectorItemHistroyIter;
    typedef std::map< unsigned long, VectorItemHistroy > MapItemHistroy;
    typedef MapItemHistroy::iterator ItemHistroyMapIter;

public:
    ConsignmentManager();
    ~ConsignmentManager();
    
    // 执行更新
    void RunUpdate( unsigned long nCurrentTime );

    // 设置加载成功
    void SetLoadSuccess( bool bValue );

    // 获得是否加载成功
    bool GetLoadSuccess() const { return m_bLoadSuccess; }

    // 设置加载帐号列表完成
    void SetLoadConsignmentAccount( bool bValue ){ m_bLoadAccount = bValue; }
    
    // 设置加载寄售单列表完成
    void SetLoadConsignmentMoneyList( bool bValue ) { m_bLoadBuyRMB = m_bLoadSellRMB = bValue; }

    // 设置加载寄售历史记录完成
    void SetLoadConsignmentMoneyHistroy( bool bValue ) { m_LoadRMBHistory = bValue; }
    
    // 开启加载定时器
    void StartLoadTimer( unsigned int nCurrentTime );

    // 停止加载定时器
    void StopLoadTimer(){ m_xLoadTimer.StopTimer(); }

    // 初始化寄售账户
    void InitConsignmentAccount( const ConsignmentAccount* pAccount, int nCount ); // 初始化帐号列表

    // 获得寄售账户信息
    Account* GetConsignmentAccount( unsigned long dwPlayerID );   // 获得帐号信息

    // 初始化寄售金锭列表
    void InitConsignmentMoneyList( const ConsignmentBase* pConsignment, int nCount );     // 初始化金锭寄售列表

    // 初始化寄售物品列表
    void InitConsignmentItemList( const ConsignmentData* pConsignment, int nCount );      // 初始化金锭寄售列表

    // 初始化寄售历史记录
    void InitConsignmentHistoryList( const ConsignmentHistroy* pHistroy, int nCount );    // 初始化交易记录

    // 添加一个寄售单
    bool AddConsignment( const ConsignmentBase* pConsignment );

    // 删除一个寄售单
    void RemoveConsignment( __int64 n64ID, unsigned char uchType );

    // 获得一个寄售单
    Consignment* GetConsignmentMoney( __int64 n64ID, unsigned char uchType );

    // 添加一个寄售金锭历史记录
    void AddRMBHistroy( const ConsignmentHistroy* pHistroy );

    // 添加一个寄售物品历史记录
    void AddItemHistroy( const ConsignmentHistroy* pHistroy );

    // 获得玩家的寄售金锭所有历史记录
    const RMBHistroyVector* GetRMBHistroy( unsigned int nPlayerID );

    // 获得玩家某个寄售单历史记录
    RMBHistroy* GetRMBHistory( unsigned int nPlayerID, __int64 nConsignmentID );

    // 处理寄售金锭排序逻辑
    void ProcessSortSellRMB( unsigned char uchSortType, int nValue = 0 );

    // 处理收购金锭排序逻辑
    void ProcessSortBuyRMB( unsigned char uchSortType, int nValue = 0 );

    // 处理寄售账户
    void ProcessGameAccountOperate( unsigned int nPlayerID, unsigned char uchOperate, unsigned int nRMBMoney, unsigned int nGameMoney );

    // 处理DB回馈后寄售账户
    void ProcessDBAccountOperate( const ConsignmentAccount& xAccount, unsigned char uchOperate, unsigned int nRMBMoney, unsigned int nGameMoney );

    // 处理寄售单
    void ProcessGameConsignmentMoney( unsigned int nPlayerID, ConsignmentBase& xConsignment, unsigned int nCostValue );

	//处理寄售物品
	void ProcessGameConsignmentItem( unsigned int nPlayerID, ConsignmentData& xConsignment, unsigned int nCostValue );

    // 查询寄售单历史记录
    void ProcessQueryMoneyHistroy( unsigned int nPlayerID );

    // 处理寄售申请
    void ProcessConsignmentOperate( unsigned int nPlayerID, __int64 nConsignmentID, unsigned char uchConsignmentType, unsigned char uchOperate );

    // db回馈后寄售单处理
    void ProcessDBConsignmentmoneyOperate( const ConsignmentAccount& xOperateAccount, const ConsignmentAccount& xSellerAccount, __int64 nConsignmentID, unsigned char uchEndStatus, 
                                                __int64 n64EndTime, const ConsignmentHistroy& xNewHistroy );

    // 发送寄售帐号信息
    void SendAccountMessage( unsigned int nPlayerID );
    void SendAccountMessage( const Account* pAccount );
    
    // 发送寄售账户正在等待处理
    void SendOperateMessage( unsigned int nPlayerID, bool bProcess );

    // 发送寄售单列表消息
    void SendConsignmentMoneyListMessage( unsigned int nPlayerID, unsigned char uchConsignmentType );
    void SendConsignmentMoneyListMessage( unsigned int nPlayerID, unsigned char uchConsignmentType, unsigned char uchSortType, int nValue = 0 );

protected:

    // 处理加载数据
    void ProcessLoadConsignmentData( unsigned int nCurrentTime );

    // 发送消息给寄售玩家
    void SendMessageToPlayer( unsigned int nPlayerID, Msg* pMessage, bool bDirect );

    // 发送某人发布了一个寄售单
    void SendConsignmentMoneyToWorld( const ConsignmentBase& xConsignment );

    // 处理寄售单操作
    void ProcessConsignmentMoneyOperate( unsigned int nPlayerID, __int64 nConsignmentID, unsigned char uchConsignmentType, unsigned char uchOperate );

    // 处理出售寄售单超时
    void ProcessSellRMBTimeOut();

    // 处理收购寄售单超时
    void ProcessBuyRMBTimeOut();

    // 创建寄售单ID
    __int64 CreateConsigmentID( unsigned int nPlayerID, __int64 n64Time );

private:
    MapAccount     m_mapAccount;      // 保存用户的账号信息
    SellRMBMap     m_mapSellRMB;      // 金锭寄售的列表
    BuyRMBMap      m_mapBuyRMB;       // 金锭收购的列表
    SellItemMap    m_mapSellItem;     // 物品寄售的列表
    BuyItemMap     m_mapBuyItem;      // 物品收购的列表
    RMBHistroyMap  m_mapRMBHistroy;   // 金锭历史交易记录
    MapItemHistroy m_mapItemHistroy;  // 物品历史交易记录

    bool m_bIsStartLoad;
    bool m_bLoadSuccess;
    bool m_bLoadAccount;
    bool m_bLoadSellRMB;
    bool m_bLoadBuyRMB;
    bool m_bLoadSellItem;
    bool m_bLoadBuyItem;
    bool m_LoadRMBHistory;
    bool m_LoadItemHistory;

    GameTimerEx m_xUpdateTimer;     // 更新定时器
    GameTimerEx m_xLoadTimer;       // 加载定时器

    SellRMBVector m_vecSellRMB;
    BuyRMBVector m_vecBuyRMB;
};

#endif