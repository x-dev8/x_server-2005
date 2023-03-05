#ifndef __BARGAININGMANAGER_H__
#define __BARGAININGMANAGER_H__

/************************************************************************
            交易管理
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <map>
#include "GameTimer.h"
#include "Singleton.h"
#include "Memory_Pool.h"
#include "BargainingDefine.h"

// 玩家交易信息
class BargainingInfo : INHERIT_POOL_PARAM( BargainingInfo, 10 )
{
public:
    static BargainingInfo* Instace() { return CNewWithDebug< BargainingInfo >::Alloc( 1, "创建BargainingInfo实例" ); }
    virtual void Release() { CNewWithDebug< BargainingInfo >::Free( this ); }

    // 获得交易ID号
    unsigned int GetID() const { return m_nBargainingID; }

    // 设置交易ID号
    void SetID( unsigned int nValue ) { m_nBargainingID = nValue; }
    
    PlayerBargaining& GetPlayerBargainingA() { return m_xPlayerBargainingA; }
    PlayerBargaining& GetPlayerBargainingB() { return m_xPlayerBargainingB; }

    // 获得玩家交易信息
    PlayerBargaining* GetPlayerBargaining( unsigned int nPlayerID );

    // 获得对方交易信息
    PlayerBargaining* GetTargetPlayerBargaining( unsigned int nPlayerID );

    // 删除交易信息
    void ClearBargainingData( unsigned char uchType );

    // 检查定时器
    bool CheckTimer() { return m_xBargainingTimer.DoneTimer(); }

    // 开启定时器
    void StartTimer( unsigned int nStartTime, unsigned int nKeepTime );

protected:
    unsigned int m_nBargainingID;
    PlayerBargaining m_xPlayerBargainingA;    // 交易玩家A
    PlayerBargaining m_xPlayerBargainingB;    // 交易玩家B
    GameTimerEx m_xBargainingTimer;           // 交易定时器
};

// 交易申请
class BargainingInvite
{
public:
    // 获得申请交易玩家ID
    unsigned int GetInviteID() const { return m_nInviteID; }

    // 设置申请交易玩家ID
    void SetInviteID( unsigned int nValue ) { m_nInviteID = nValue; }

    // 开启定时器
    void StartTimer( unsigned int nStartTime, unsigned int nKeepTime ) { m_xInviteTimer.StartTimer( nStartTime, nKeepTime ); }
    
    // 检查定时器
    bool CheckTimer() { return m_xInviteTimer.DoneTimer(); }

protected:
    unsigned int m_nInviteID;    // 申请人
    GameTimerEx m_xInviteTimer;  // 超时定时器
};

#define theBargainingManager BargainingManager::Instance()

// 交易管理
class BargainingManager : public ISingletion< BargainingManager >
{
public:
    BargainingManager();
    ~BargainingManager();

    // 创建一个交易
    BargainingInfo* CreateBargaining();

    // 删除一个交易
    void RemoveBargaining( unsigned int nBargainingID, unsigned char uchRemoveType );

    // 获得一个交易
    BargainingInfo* GetBargaining( unsigned int nBargainingID );

    // 添加一个交易申请记录
    void AddBargainingInvite( unsigned int nReqID, unsigned int nAckID );

    // 删除一个交易记录
    void RemoveBargainingInvite( unsigned int nAckID );

    // 获得邀请者ID
    unsigned int GetBargainingInvite( unsigned int nAckID );    

    // 执行更新
    void RunUpdate( unsigned int nCurrentTime );

protected:

    // 获得交易ID号
    unsigned int GetBarganingID();

    // 更新邀请列表
    void UpdateBargainingInvite( unsigned int nCurrentTime );

    // 更新交易列表
    void UpdateBargaining( unsigned int nCurrentTime );

private:

    // 交易列表
    typedef std::map< unsigned int, BargainingInfo* > BargainingMap;
    typedef BargainingMap::iterator BargainingMapIter;

    // 交易申请列表
    typedef std::map< unsigned int, BargainingInvite > BargainingInviteMap;
    typedef BargainingInviteMap::iterator BargainingInviteMapIter;

    unsigned int m_nBargainingID;       // 交易ID
    BargainingMap m_mapBargaining;      // 交易列表
    BargainingInviteMap m_mapInvite;    // 申请记录
    GameTimerEx m_xUpdateTimer;         // 交易更新定时器
};

#endif