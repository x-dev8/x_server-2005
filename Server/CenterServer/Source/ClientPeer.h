/********************************************************************
	Filename: 	ClientPeer.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_CLIENTPEER_H__
#define __CENTERSERVER_CLIENTPEER_H__

#pragma once

#include "GlobalDef.h"
#include "Memory_Pool.h"
#include "FuncPerformanceLog.h"
#include "NetClient.h"
//#include "MessageDefine.h"
#include "CenterGameMessage.h"

class GameServerPeer;

// Client ��ҪʱЧ�Ե�һ��LifeId
class ClientPeer : INHERIT_POOL(ClientPeer)
{
public:
	DECLARE_POOL_FUNC(ClientPeer)

    ClientPeer();
    virtual ~ClientPeer(){}
    virtual long ProcessMessage( NetClient* pNetClient, Msg* pMessage );

    // �˺ż�����Ϣ
    void             SetLoginInfo( const SLoginInfoBase& loginInfo ) { _loginInfo = loginInfo; }
    SLoginInfoBase&  GetLoginInfo() { return _loginInfo; }
    unsigned long    GetAccountId() { return _loginInfo.nAccountID; }
	std::string		 GetMacAdress() { return _loginInfo.szMac; }

    EClientStateType GetLoginState() { return _loginState; }
    void             SetLoginState( EClientStateType state ) { _loginState = state; }

    EClientStateType GetState() { return _playState; }
    void             SetState( EClientStateType state ) { _playState = state; }

    void             ChangeServerInfo( const SServerInfo& si);
    SServerInfo&     GetServerInfo()    { return _serverInfo;   } // ��ǰ���ڵķ�������Ϣ
    SStageReqInfo&   GetReqServerInfo() { return _stageReqInfo; } // ��Ҫȥ�ķ�������Ϣ

    void             GetToken()  { _IsHaveToken = true;  }
    void             MissToken() { _IsHaveToken = false; }
    bool             HaveToken() { return _IsHaveToken;  }
                  
    void             SetRequeryLoginTime(unsigned long dwTime) { _ReqLoginTime = dwTime; }
    unsigned long    GetRequeryLoginTime()            { return _ReqLoginTime; }

	void				ProcessPreDataLogin();	// �����½ǰ��׼������
    void                ProcessLogin();			// �����¼��Ϊ
	void                ProcessEnterWorld();	// ���������Ϸ
	void                ProcessExitWorld();		// �����˳���Ϸ

	void                UpdateCountryOnlineCount( int nCount );
    // ��ɫ������Ϣ
    void                SetCharDynamicId( GameObjectId sCharId ) { _charDynamicId = sCharId; }
    GameObjectId        GetCharDynamicId() { return _charDynamicId; }
                     
    void                SetCharDbId( unsigned long nCharDbId ) { _currentCharDbId = nCharDbId; } 
    unsigned long       GetCharDbId() { return _currentCharDbId; }
    
    void                SetCountry( uint8 uchValue ) { _uchCountry = uchValue; }
    uint8               GetCountry()                 { return _uchCountry; }

    unsigned long       GetLastMapId() { return _nLastMapId;}
    void                SetLastMapId( unsigned long nLastMapId ) { _nLastMapId = nLastMapId; }

    SStageReqInfo&      GetStageReqInfo() { return _stageReqInfo;}
    void                ResetStageReqInfo(){ memset(&_stageReqInfo, 0xff, sizeof(_stageReqInfo)); _stageReqInfo.bHaveInvalidInfo = false;}

    void                OnSynInServerInfo( GS2CSPlayerSynInServerInfo* pMessage );
    long                OnExitServer( unsigned char ucExitType );

    void                SetCharacterName( const char* szName ) { strncpy_s( _szCharacterName, sizeof(_szCharacterName), szName, sizeof(_szCharacterName)-1); }
    const char*         GetCharacterName() { return _szCharacterName; }

    void                ResetAccountInfo();// �����˺���Ϣ ����
    void                ResetCharInfo();   // ���ý�ɫ��Ϣ ����ѡ��
	
	uint32				GetLoginServerId() { return _loginserverId;}
	void                SetLoginServerId( uint32 nId ) { _loginserverId = nId; }
	uint8				GetChannelStatus(uint32 client_count);

protected:
    void _OnS2SSwitchGate( S2SSwitchGate* pMessage );
    void _OnGS2CSSwitchStageReq( GS2CSSwitchStageReq* pMessage );
    void _OnMsgS2SSelectChannel( MsgS2SSelectChannel* pMessage );

    unsigned short _HandleEnterWorld( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage, bool bCorrect = false);
    unsigned short _HandleEnterMapGameServer( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage );
    unsigned short _HandleEnterCharacterLogin( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage );
    unsigned short _HandleFlyToMap( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage );
	unsigned short _HandleChangeChannel( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage );
	
private:
    // �˺ż���
    SLoginInfoBase   _loginInfo;    // ��½��Ϣ
    EClientStateType _loginState;   // ״̬ ��¼״̬
    SServerInfo      _serverInfo;   // ���ڷ�������Ϣ
    bool             _IsHaveToken;  // �Ƿ���Ʊ
    uint32           _ReqLoginTime; // ���ͻ��������¼��ʱ��

    // ��ɫ����
    uint8            _uchCountry;
    char             _szCharacterName[dr_MaxPlayerName];
    GameObjectId     _charDynamicId;              // �����ڷ������϶�̬Id
    uint32           _currentCharDbId;            // ��ǰ��ѡ��Ľ�ɫ
    short            _stWhichSlot;                // ��ǰ��ѡ��Ľ�ɫ��λ��
    unsigned long    _nStageId;                   // ����Id
    EClientStateType _playState;                  // ״̬ ��Ϸ״̬
    unsigned long    _nLastMapId;                 // ���һ�����ڵ�ͼ
    SStageReqInfo    _stageReqInfo;               // Ҫ���ĵ�ͼ����Ϣ
    bool             _bIsHavePlayingInGameServer; // �Ƿ��Ѿ�ѡ�˽�ɫ����Ϸ�������� ����Ļ��Ϳ��Ը���GameServer��Ҫ�ٷ���ɫ���ݸ�Client    
    uint32           _organizeId;
  
	uint32           _loginserverId;				//��¼��������id
};


typedef std::set<unsigned long>      AccountIdContainer;
typedef AccountIdContainer::iterator ItrAccountIdContainer;

typedef std::map<unsigned long, ClientPeer*> ClientPeerMapContainer;
typedef ClientPeerMapContainer::iterator     ItrClientPeerMapContainer;

typedef std::map<std::string, ClientPeer*>       ClientPeerMapContainerByString;
typedef ClientPeerMapContainerByString::iterator ItrClientPeerMapContainerByString;

typedef std::map<std::string, std::vector<ClientPeer*> >  ClientPeerMapContainerByMac;
typedef ClientPeerMapContainerByMac::iterator		  ItrClientPeerMapContainerByMac;

#endif // __CENTERSERVER_CLIENTPEER_H__
