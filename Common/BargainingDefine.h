#ifndef __BARGAININGDEFINE_H__
#define __BARGAININGDEFINE_H__

/************************************************************************
            交易属性定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <vector>

namespace BargainingDefine
{
    enum EConstDefine
    {
        //////////////////////////////////////////////////////////
        NoneID = 0,
        MaxItemCount = 16,          // 最多交易物品数量 20
		MaxPetCount = 4,			// 宠物交易上限
        DataLength = 1500,          // 交易道具数据BUFF的长度
        MaxBargainingID = 10000000, // 最大的交易ID
        InviteKeepTime = 60000,     // 交易邀请1分钟有效
        BargainingTime = 720000,    // 交易12分钟时间内有效
        BargainingMoneyLevel = 10,  // 10级以上才能交易金钱
        BargainingMountLevel = 5,   // 交易坐骑不能超过玩家等级5级
        /////////////////////////////////////////////////////////////
        BargainingMoney = 1,        // 交易金钱
        BargainingRMB,              // 交易金锭
        BargainingItem,             // 交易道具
        BargainingMount,            // 交易坐骑
        BargainingPet,              // 交易宠物

        /////////////////////////////////////////////////////////////
        // 交易的状态
        StatusInit = 0,             // 初始状态
        StatusStart,                // 交易开始, 放入物品状态
        StatusLock,                 // 放完物品, 锁定状态
        StatusFix,                  // 锁定后, 确定交易状态
        /////////////////////////////////////////////////////////////
        // 交易结束
        FinishSuccess = 1,          // 交易成功
        FinishTimeOut,              // 交易超时
        FinishCancel,               // 交易取消
        FinishOutLine,              // 玩家下线, 交易取消
        //////////////////////////////////////////////////////////////
        // 交易申请回馈消息
        FailedSuccess = 0,          // 客户端不用处理这个枚举
        FailedBargaining,           // 自己正在交易中
        FailedTargetBargaining,     // 对方正在交易中
        FailedStall,                // 自己正在摆摊中
        FailedTargetStall,          // 对方正在摆摊中
        FailedNotInArea,            // 对方没有在范围内( 16米有效 )
        FailedRefuse,               // 对方拒绝交易
        FailedRequest,              // 已发送交易申请
        FailedFighting,             // 自己正在战斗状态
        FailedTargetFighting,       // 对方正在战斗状态
        //////////////////////////////////////////////////////////////////
        // 请求放入交易道具时的错误回馈
        LessMoney = 1,              // 没有足够的金钱
        MoneyLevelLimit,            // 10级以下不能交易金钱
        LessRMB,                    // 没有足够的金锭
        MaxMoney,                   // 金钱数量超过能携带的上限
        DataError,                  // 交易的道具信息不正确
        DataLocked,                 // 交易的道具已锁定或者已绑定
        DataOverdue,                // 交易的道具已过期
        DataAlready,                // 交易的道具已经在交易栏中了
        IndexAlready,               // 放入的交易栏已经有道具了
        CanNotTrade,                // 交易的道具不能被交易
        IndexError,                 // 交易栏位置错误
        NormalFull,                 // 普通背包满了
        MaterialFull,               // 材料背包满了
        MountFull,                  // 坐骑背包满了
        PetFull,                    // 宠物背包满了
        DataChange,                 // 交易道具已经变更
        MountActive,                // 坐骑已出战, 不能交易
        MountLevelLimit,            // 坐骑等级超过对方等级5级以上
        PetActive,                  // 宠物已出战, 不能交易
        PetLevelLimit,              // 宠物等级超过对方等级5级以上
		PlayerPetLimit,				// 超过对方领养上限,不能交易
        //////////////////////////////////////////////////////////////////
    };
}
//////////////////////////////////////////////////////////////////////////////////////

// 交易的物品数据
class BargainingData
{
public:
    BargainingData() : m_ustItemCount( 0 ), m_n64ItemGuid( 0 ), m_nItemValue1( 0 ), m_nItemValue2( 0 )
    {

    }

    unsigned char GetItemBag() const { return m_uchItemBag; }
    unsigned char GetItemIndex() const { return m_uchItemIndex; }
    unsigned short GetItemCount() const { return m_ustItemCount; }
    __int64 GetItemGuid() const { return m_n64ItemGuid; }
    unsigned int GetItemValue1() const { return m_nItemValue1; }
    unsigned int GetItemValue2() const { return m_nItemValue2; }

    void SetItemBag( unsigned char uchValue ) { m_uchItemBag = uchValue; }
    void SetItemIndex( unsigned char uchValue ) { m_uchItemIndex = uchValue; }
    void SetItemCount( unsigned short ustValue ) { m_ustItemCount = ustValue; }
    void SetItemGuid( __int64 n64Value ) { m_n64ItemGuid = n64Value; }
    void SetItemValue1( unsigned short nValue ) { m_nItemValue1 = nValue; }
    void SetItemValue2( unsigned short nValue ) { m_nItemValue2 = nValue; }

    void ClearData()
    {
        m_n64ItemGuid = 0;
        m_ustItemCount = 0;
    }

protected:
    unsigned char m_uchItemBag;     // 物品背包
    unsigned char m_uchItemIndex;   // 物品索引
    unsigned short m_ustItemCount;  // 物品数量
    __int64 m_n64ItemGuid;          // 物品guid

    // 扩展的数据, 比对用
    unsigned int m_nItemValue1;
    unsigned int m_nItemValue2;
};

// 玩家交易的数据
class PlayerBargaining
{
public:
    PlayerBargaining() : m_uchStatus( BargainingDefine::StatusInit ), m_nPlayerID( 0 ), m_nGameMoney( 0 ), m_nRMBMoney( 0 )
    {
    }

    unsigned int GetID() const { return m_nPlayerID; }
    unsigned char GetStatus() const { return m_uchStatus; }
    unsigned int GetGameMoney() const { return m_nGameMoney; }
    unsigned int GetRMBMoney() const { return m_nRMBMoney; }


    void SetID( unsigned int nValue ) { m_nPlayerID = nValue; }
    void SetStatus( unsigned char uchValue ) { m_uchStatus = uchValue; }
    void SetGameMoney( unsigned int nValue ) { m_nGameMoney = nValue; }
    void SetRMBMoney( unsigned int nValue ) { m_nRMBMoney = nValue; }

    const BargainingData* GetBargainingData( unsigned int nIndex ) const;
    bool AddBargainingData( unsigned int nIndex, BargainingData& xData );
    void ClearBargainingData( unsigned int nIndex );

    // 校验交易的物品是否已经存在的了
    bool CheckBargainingData( unsigned char uchBargainingIndex, unsigned char uchBagType, __int64 n64Guid );

protected:
    typedef std::vector< BargainingData > BargainingDataVector;
    typedef BargainingDataVector::iterator BargainingDataVectorIter;

    unsigned int m_nPlayerID;        // 玩家DBID
    unsigned char m_uchStatus;       // 当前的交易状态
    unsigned int m_nGameMoney;       // 交易的游戏币
    unsigned int m_nRMBMoney;        // 交易的金锭
    BargainingData xData[ BargainingDefine::MaxItemCount ];  // 交易的物品
};

inline const BargainingData* PlayerBargaining::GetBargainingData( unsigned int nIndex ) const
{
    if ( nIndex >= BargainingDefine::MaxItemCount )
    { return NULL; }

    return &( xData[ nIndex ] );
}

inline bool PlayerBargaining::AddBargainingData( unsigned int nIndex, BargainingData& xBargainingData )
{
    if ( nIndex >= BargainingDefine::MaxItemCount )
    { return false; }

    xData[ nIndex ] = xBargainingData;
    return true;
}

inline bool PlayerBargaining::CheckBargainingData( unsigned char uchBargainingIndex, unsigned char uchBagType, __int64 n64Guid )
{
    for ( int i = 0; i < BargainingDefine::MaxItemCount; ++i )
    {
        if ( xData[i].GetItemGuid() != n64Guid )
        { continue; }

        if ( xData[i].GetItemBag() != uchBagType )
        { continue; }

        if ( uchBargainingIndex != i )
        { return false; }
    }

    return true;
}

inline void PlayerBargaining::ClearBargainingData( unsigned int nIndex )
{
    if ( nIndex >= BargainingDefine::MaxItemCount )
    { return; }

    xData[ nIndex ].ClearData();
}

#endif