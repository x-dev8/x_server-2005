/********************************************************************
    Filename:     GamePlayer.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GATESERVER_CLIENT_H__
#define __GATESERVER_CLIENT_H__

#pragma once

#include "MessageDefine.h"
//#include "MeConnector.h"
//#include "MeNetwork.h"
#include "tstring.h"
#include "BaseCharacter.h"
#include "GameTime.h"
#include "GameDataType.h"
#include "CountryMessage.h"
#include "network.h"

using namespace network;

class GamePlayer : public BaseCharacter
{
public:
    enum EConstDefine
    {
        const_iFreeTimeout           = 0,
        const_iSendSwitchGateTimeOut = 3000,
    };

    enum EStatusType
    {
        EStatusType_None                  , // 无切状态
        EStatusType_WaitSwitchGateCallBack, // 等待客户端切服回馈
        EStatusType_GetSwitchGateCallBack , // 收到客户端切服回馈
        EStatusType_NormalExit            , // 正常退出
    };

public:
    GamePlayer();
    virtual ~GamePlayer();

    void SendMsg( Msg* pMsg );

    void SendToClient( Msg* pMessage );

    // 发送经过优化打包的消息
    void SendPackage();
    
public:
    //对数据量大的包进行优化处理
    void          OnPlayerMoveingPos             ( MsgPlayerMovingPos*             pMsg );
    void          OnPlayerMovingPosAndDir        ( MsgPlayerMovingPosAndDir*       pMsg );
    void          OnPlayerPos                    ( MsgPlayerPos*                   pMsg );
    void          OnPlayerDir                    ( MsgPlayerDir*                   pMsg );
    void          OnPlayerPosAndDir              ( MsgPlayerPosAndDir*             pMsg );
    void          OnPlayerVerifyPos              ( MsgPlayerVerifyPos*             pMsg );
    void          OnUnPlayerMovingToPos          ( MsgUnPlayerMovingToPos*         pMsg );
    void          OnUnPlayerVerifyPos            ( MsgUnPlayerVerifyPos*           pMsg );
    void          OnUnPlayerCloseingToLockTarget ( MsgUnPlayerClosingToLockTarget* pMsg );
         
    void          OnPlayerEnterMySight           ( MsgPlayerEnterMySight*          pMsg );
    void          OnAckEnterWorld                ( MsgAckEnterWorld*               pMsg );
         
    void          OnTellCountryID                ( MsgCountryTellCountryID*        pMsg );
    void          OnChangeLevel                  ( MsgSeeCharacterLevelup*         pMsg );

    void          SetConnector                   ( /*IMeConnector*/Socketer* pMeConnector, bool bReleaseOld = true );
    /*IMeConnector*/Socketer* GetConnector                   (){ return m_pConnector; }
    void          ReleaseConnector               ();

    bool          IncFreeCount()
    {
        m_iFreeCount ++;
        if( m_iFreeCount >= const_iFreeTimeout )
        { return true; }
        return false;
    }

    int          GetIncFreeCount()                                        { return m_iFreeCount;                        }
    GameObjectId GetGateServerPlayerId()                                  { return _iGateServerPlayerId;                }
    void         SetGateServerPlayerId( GameObjectId nGateServerPlayerId ){ _iGateServerPlayerId = nGateServerPlayerId; }
    GameObjectId GetGameServerPlayerId()                                  { return _iGameServerPlayerId;                }
    void         SetGameServerPlayerId( GameObjectId iGWID )              { _iGameServerPlayerId = iGWID;               }
    uint32       GetAccountID()                                           { return m_nAccountID;                        }
    void         SetAccountID( uint32 nAccount)                           { m_nAccountID = nAccount;                    }
    /*char**/__int64        GetSessionKey()                                          { return m_SessionKey;                        }
    bool         SetSessionKey( /*const char**/__int64 SessionKey );
               
    void         SetHasSendClientExit()           { m_bHasSendClientExit = true; }
    bool         HasSendClientExit()              { return m_bHasSendClientExit; }
    void         SetPingTime( uint32 dwTime)      { m_LastPingTime = dwTime; }
    DWORD        GetPingTime()                    { return m_LastPingTime;   }
    TCountryId   GetCountryId()                   { return _country;         }
    void         SetCountryId( uint8 uchCountry ) { _country = uchCountry;   }
    uint16       GetLevel() const                 { return _level;           }
    void         SetLevel( uint16 uchValue )      { _level = uchValue;       }
    void         SetDisconnectTime()              { m_dwDisConnectTime = HQ_TimeGetTime(); }
    uint32       GetDisconnectTime()              { return m_dwDisConnectTime; }

    EStatusType GetClientStatus(){ return _clientStatus; }
    void        SetClientStatus( EStatusType state );

    bool        IsWaitAckSwitchGateTimeOut();
    
public:
    Common::_tstring m_strIP;            // 最后一次连接的IP
    uint32           m_dwDisConnectTime; // 断线时间
    uint32           m_dwAcceptTime;     // 连接时间                     
    int              _iAllocId;          // 在alloc队列中的动态id
    bool             m_bIsSendConnectInfo;
    /*IMeConnector*/Socketer*    m_pConnector;

private:
    int              m_iFreeCount;         // 初始=0 被加入删除等待队列后 主逻辑线程 每回合计数
    GameObjectId     _iGateServerPlayerId; // 在GateServer上队列[GateClient]中的动态Id
    GameObjectId     _iGameServerPlayerId; // 在GameServer上[Character]队列中动态Id
    uint32           m_nAccountID;
    //char             m_SessionKey[40+1];
	__int64          m_SessionKey;
           
    bool             m_bHasSendClientExit; // 如果已经发送过，就不再发送
    uint32           m_dwLastSendPackTime;
    uint32           m_LastPingTime;       // 上一次收到ping的时间
    EStatusType      _clientStatus;
    uint32           _dwSendSwitchGateingTime;
    TCountryId       _country;             // 所属国家
    uint8            _level;               // 等级
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void GamePlayer::SetClientStatus( EStatusType state )
{ 
    _clientStatus = state; 
    switch ( state )
    {
    case EStatusType_None:
        {
            _dwSendSwitchGateingTime = 0;
        }
        break;
    case EStatusType_WaitSwitchGateCallBack:
        {
            _dwSendSwitchGateingTime = HQ_TimeGetTime(); 
        }
        break;
    case EStatusType_GetSwitchGateCallBack:
        {
            _dwSendSwitchGateingTime = 0;
        }
        break;
    }
}

inline bool GamePlayer::IsWaitAckSwitchGateTimeOut()
{
    if( GameTime::IsPassCurrentTime( _dwSendSwitchGateingTime, const_iSendSwitchGateTimeOut ) )
    { return true; }

    return false;
}

inline bool GamePlayer::SetSessionKey( /*const char**/__int64 SessionKey )
{
    if (SessionKey == 0)
    { return false; }
    //strncpy_s(m_SessionKey,sizeof(m_SessionKey),SessionKey,sizeof(m_SessionKey)-1);
	m_SessionKey = SessionKey;
    return true;
}

#endif // __GATESERVER_CLIENT_H__
