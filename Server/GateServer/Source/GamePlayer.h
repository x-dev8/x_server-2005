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
        EStatusType_None                  , // ����״̬
        EStatusType_WaitSwitchGateCallBack, // �ȴ��ͻ����з�����
        EStatusType_GetSwitchGateCallBack , // �յ��ͻ����з�����
        EStatusType_NormalExit            , // �����˳�
    };

public:
    GamePlayer();
    virtual ~GamePlayer();

    void SendMsg( Msg* pMsg );

    void SendToClient( Msg* pMessage );

    // ���;����Ż��������Ϣ
    void SendPackage();
    
public:
    //����������İ������Ż�����
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
    Common::_tstring m_strIP;            // ���һ�����ӵ�IP
    uint32           m_dwDisConnectTime; // ����ʱ��
    uint32           m_dwAcceptTime;     // ����ʱ��                     
    int              _iAllocId;          // ��alloc�����еĶ�̬id
    bool             m_bIsSendConnectInfo;
    /*IMeConnector*/Socketer*    m_pConnector;

private:
    int              m_iFreeCount;         // ��ʼ=0 ������ɾ���ȴ����к� ���߼��߳� ÿ�غϼ���
    GameObjectId     _iGateServerPlayerId; // ��GateServer�϶���[GateClient]�еĶ�̬Id
    GameObjectId     _iGameServerPlayerId; // ��GameServer��[Character]�����ж�̬Id
    uint32           m_nAccountID;
    //char             m_SessionKey[40+1];
	__int64          m_SessionKey;
           
    bool             m_bHasSendClientExit; // ����Ѿ����͹����Ͳ��ٷ���
    uint32           m_dwLastSendPackTime;
    uint32           m_LastPingTime;       // ��һ���յ�ping��ʱ��
    EStatusType      _clientStatus;
    uint32           _dwSendSwitchGateingTime;
    TCountryId       _country;             // ��������
    uint8            _level;               // �ȼ�
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
