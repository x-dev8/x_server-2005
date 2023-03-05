#ifndef __CONSIGNMENETDEFINE_H__
#define __CONSIGNMENETDEFINE_H__

/************************************************************************
            FileName : ConsignmentDefine.h

            寄售系统的定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <algorithm>
#include <functional>
#include "math.h"

namespace ConsignmentDefine
{
    enum EConstDefine
    {
        // 寄售类型
        Consignment_Init = 0,   // 无效类型
        Consignment_SellRMB,    // 寄售金锭
        Consignment_SellItem,   // 寄售物品
        Consignment_SellMount,  // 寄售坐骑
        Consignment_SellPet,    // 寄售宠物

        Consignment_BuyRMB,     // 收购金锭
        Consignment_BuyItem,    // 收购物品
        Consignment_BuyMount,   // 收购坐骑
        Consignment_BuyPet,     // 收购宠物
        Consignment_Max,        // 最大类型

        // 操作类型
        Operate_Init = 0,       // 无效操作
        Operate_Save,           // 存钱
        Operate_TakeOut,        // 取钱
        Operate_Sell,           // 出售
        Operate_Buy,            // 购买
        Operate_Cancel,         // 撤销
        Operate_TimeOut,        // 超时( 服务器调用 )
        Operate_Max,

        // 查看寄售单的排序方式
        Sort_Normal = 0,        // 默认按日期排序
        Sort_LessPrice,         // 按价钱低到高
        Sort_GreaterPrice,      // 按价钱高到低
        Sort_MySelf,            // 查看自己寄售的
        Sort_ForMe,             // 指定给我的
        Sort_Count,             // 查看指定数量
        Sort_LessCount,         // 数量从小到大排序
        Sort_GreaterCount,      // 数量从大到小排序
        Sort_Date,              // 按日期排序

        Status_Init = 0,        // 初始状态
        Status_Running,         // 挂单中
        Status_BuySuccess,      // 购买成功
        Status_SellSuccess,     // 出售成功
        Status_Buyed,           // 已购买
        Status_Selled,          // 已售出
        Status_Cancel,          // 玩家取消订单
        Status_TimeOut,         // 订单到期
        Status_Max,

        // 寄售物品等的数据长度
        ErrorID = 0xFFFFFFFF,
        NoneID = 0,
        MaxDataLength = 500,                // 寄售物品数据的最大长度
        MaxConsignmentCount = 10,           // 客户端显示的最大的寄售列表数量
        MaxConsignmentTime = 7 * 24 * 3600, // 单子保留的最长时间
        UpdateSpaceTime = 60000,            // 60秒更新一次
        OperateSpaceTime = 2000,            // 2秒间隔才能执行一次
        LoadSpaceTime = 60000 * 10,         // 10分钟间隔才能执行一次

        MaxAccountRMB = 99999,			    // 账号人民币最大数值9
        MaxAccountGameMoney = 999999999,	    // 最大游戏币

        MinSellRMBCount = 15,               // 最少交易金锭数量
    };

    // 出售金锭传入出售金锭的数量, 收购金锭传入花费游戏币的数量
    static unsigned int GetConsignmentCost( int nValue ) 
    {
        const static float s_fCostRate = 0.02f;

        float fValue = static_cast< float >( nValue );
        float fCost = fValue * s_fCostRate;
        return static_cast< unsigned int >( ceil( fCost ) );
    }
}

// 帐号信息
class ConsignmentAccount
{
public:
    ConsignmentAccount( unsigned long nValue ) : nPlayerID( nValue ), nRMBMoney( 0 ), nGameMoney( 0 ){}

    ConsignmentAccount() : nPlayerID( 0 ), nRMBMoney( 0 ), nGameMoney( 0 ){}

    unsigned long GetPlayerID() const		  { return nPlayerID;	}
    unsigned long GetRMBMoney() const		  { return nRMBMoney;	}
    unsigned long GetGameMoney() const		  { return nGameMoney;	}

    void SetPlayerID( unsigned long nValue )  { nPlayerID = nValue; }
    void SetRMBMoney( unsigned long nValue )  { nRMBMoney = nValue; }
    void SetGameMoney( unsigned long nValue ) { nGameMoney = nValue;}

    bool IsErrorAccount() const				  { return nPlayerID == 0; }

    void Initialize( const ConsignmentAccount* pAccount )
    {
        SetPlayerID( pAccount->GetPlayerID() );
        SetRMBMoney( pAccount->GetRMBMoney() );
        SetGameMoney( pAccount->GetGameMoney() );
    }

protected:
    unsigned long nPlayerID;    // 玩家ID
    unsigned long nRMBMoney;    // 金锭
    unsigned long nGameMoney;   // 游戏币
};

// 寄售单结构
class ConsignmentBase
{
public:
    ConsignmentBase() : nBuyPlayerID( 0 ), nItemID( 0 ), n64ID( 0 ){}

    __int64		  GetID() const				{ return n64ID;			}
    unsigned char GetType() const			{ return uchType;		}
    __int64		  GetStartTime() const		{ return n64StartTime;	}
    unsigned long GetSellPlayerID() const	{ return nSellPlayerID; }
    unsigned long GetBuyPlayerID() const	{ return nBuyPlayerID;	}
    unsigned long GetPrice() const			{ return nPrice;		}
    unsigned long GetCount() const			{ return nCount;		}
    unsigned short GetItemID() const		{ return nItemID;		}

    void SetID( __int64 n64Value )			{ n64ID = n64Value;		}
    void SetType( unsigned char uchValue )	{ uchType = uchValue;	}
    void SetStartTime( __int64 n64Value )	{ n64StartTime = n64Value; }
    void SetSellPlayerID( unsigned long nValue ) { nSellPlayerID = nValue; }
    void SetBuyPlayerID( unsigned long nValue )  { nBuyPlayerID = nValue;  }
    void SetPrice( unsigned long nValue )	{ nPrice = nValue;		}
    void SetCount( unsigned long nValue )	{ nCount = nValue;		}
    void SetItemID( unsigned short nValue ) { nItemID = nValue;		}

    void Initialize( const ConsignmentBase* pBase )
    {
        if ( pBase == NULL )
        { return; }

        SetID( pBase->GetID() );
        SetType( pBase->GetType() );
        SetStartTime( pBase->GetStartTime() );
        SetSellPlayerID( pBase->GetSellPlayerID() );
        SetBuyPlayerID( pBase->GetBuyPlayerID() );
        SetPrice( pBase->GetPrice() );
        SetCount( pBase->GetCount() );
        SetItemID( pBase->GetItemID() );
    }

protected:
    __int64 n64ID;                  // 世界唯一的交易流水号
    unsigned char uchType;          // 单子出售类型
    __int64 n64StartTime;           // 开始挂单的时间
    unsigned long nSellPlayerID;    // 卖主
    unsigned long nBuyPlayerID;     // 指定玩家, 没有设置为 0
    unsigned long nPrice;           // 单价
    unsigned long nCount;           // 数量

    // 下面两个变量只有当收购物品, 坐骑, 宠物时才有效
    unsigned short nItemID;         // 收购的ID( 物品, 坐骑, 宠物等 )
};

// 寄售物品, 坐骑, 宠物等
class ConsignmentData : public ConsignmentBase
{
public:
    ConsignmentData() : ConsignmentBase()
    {
        memset( szData, 0, sizeof( szData ) );
    }

    const char* GetData() const { return szData; }
    
    bool SetData( const char* szValue, int nSize )
    {
        if ( szValue == NULL || nSize > sizeof( szData ) )
        { return false; }
        memcpy_s( szData, sizeof( szData ), szValue, nSize );
        return true;
    }

    void Initialize( const ConsignmentData* pData )
    {
        if ( pData == NULL )
        { return; }
        ConsignmentBase::Initialize( pData );
        SetData( pData->GetData(), ConsignmentDefine::MaxDataLength );
    }

protected:
    char szData[ ConsignmentDefine::MaxDataLength ];     // 寄售的东西
};

// 历史记录
class ConsignmentHistroy : public ConsignmentBase
{
public:
    ConsignmentHistroy() : ConsignmentBase(), n64EndTime( 0 ), nOperateID( 0 ) {}

    unsigned long GetOperateID() const	{ return nOperateID; }
    unsigned char GetStatus() const		{ return uchStatus;  }
    __int64		  GetEndTime() const	{ return n64EndTime; }


    void SetOperateID( unsigned long nValue )	{ nOperateID = nValue;	}
    void SetStatus( unsigned char uchValue )	{ uchStatus = uchValue; }
    void SetEndTime( __int64 n64Value )			{ n64EndTime = n64Value;}

    void Initialize( const ConsignmentHistroy* pHistroy )
    {
        ConsignmentBase::Initialize( pHistroy );
        SetStatus( pHistroy->GetStatus() );
        SetEndTime( pHistroy->GetEndTime() );
        SetOperateID( pHistroy->GetOperateID() );
    }

    void Initialize( const ConsignmentBase* pBase )
    {
        ConsignmentBase::Initialize( pBase );
    }

private:
    unsigned long nOperateID;   // 操作人ID
    unsigned char uchStatus;	// 状态
    __int64 n64EndTime;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T, class U >        // 所有寄售单
struct CopyConsignmentMoneyList : public std::binary_function< T, U, void >
{
    void operator() ( const T& xData )
    {
        if ( xData.second->GetBuyPlayerID() != ConsignmentDefine::NoneID )
        { return; }

        m_xVector.push_back( xData.second );
    }

    CopyConsignmentMoneyList( U& xVector ) : m_xVector( xVector ) {}
    U& m_xVector;
};

template< class T, class U >        // 指定数量
struct CopyConsignmentMoneyListCount: public std::binary_function< T, U, void >
{
    void operator() ( const T& xData )
    {
        if ( xData.second->GetBuyPlayerID() != ConsignmentDefine::NoneID )
        { return; }

        if ( xData.second->GetCount() != m_nCount )
        { return; }

        m_xVector.push_back( xData.second );
    }

    CopyConsignmentMoneyListCount( U& xVector, int nCount ) : m_xVector( xVector ), m_nCount( nCount ) {}
    U& m_xVector;
    int m_nCount;
};

template< class T, class U >        // 指定给我
struct CopyConsignmentMoneyListForMe: public std::binary_function< T, U, void >
{
    void operator() ( const T& xData )
    {
        if ( xData.second->GetBuyPlayerID() == m_nPlayerID )
        {
            m_xVector.push_back( xData.second );
        }
    }

    CopyConsignmentMoneyListForMe( U& xVector, int nPlayerID ) : m_xVector( xVector ), m_nPlayerID( nPlayerID ) {}
    U& m_xVector;
    int m_nPlayerID;
};

template< class T, class U >        // 我自己发布的
struct CopyConsignmentMoneyListSelf: public std::binary_function< T, U, void >
{
    void operator() ( const T& xData )
    {
        if ( xData.second->GetSellPlayerID() == m_nPlayerID )
        {
            m_xVector.push_back( xData.second );
        }
    }

    CopyConsignmentMoneyListSelf( U& xVector, int nPlayerID ) : m_xVector( xVector ), m_nPlayerID( nPlayerID ) {}
    U& m_xVector;
    int m_nPlayerID;
};

template< class T >
struct SortByDate : public std::unary_function< T, bool >
{
    bool operator() ( T* xLeft, T* xRight )
    {
        return xLeft->GetStartTime() > xRight->GetStartTime();
    }
};

template< class T >
struct SortByLessPrice : public std::unary_function< T, bool >
{
    bool operator() ( T* xLeft, T* xRight )
    {
        return xLeft->GetPrice() < xRight->GetPrice();
    }
};

template< class T >
struct SortByGreaterPrice : public std::unary_function< T, bool >
{
    bool operator() ( T* xLeft, T* xRight )
    {
        return xLeft->GetPrice() > xRight->GetPrice();
    }
};

template< class T >
struct SortByLessCount : public std::unary_function< T, bool >
{
    bool operator() ( T* xLeft, T* xRight )
    {
        return xLeft->GetCount() < xRight->GetCount();
    }
};

template< class T >
struct SortByGreaterCount : public std::unary_function< T, bool >
{
    bool operator() ( T* xLeft, T* xRight )
    {
        return xLeft->GetCount() > xRight->GetCount();
    }
};

template< class T >
struct EqualHistroy : public std::unary_function< T, bool >
{
    bool operator() ( T* pData )
    {
        return pData->GetID() == m_n64ID;
    }

    EqualHistroy( __int64 nValue ) : m_n64ID( nValue ){}
    __int64 m_n64ID;
};

#endif