#ifndef __CENTERSERVER_GAMESERVERPEER_H__
#define __CENTERSERVER_GAMESERVERPEER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "Memory_Pool.h"
#include "NetClient.h"
#include "CenterGameMessage.h"
#include "ClientPeerManager.h"

typedef std::vector<SGameStage> MapIdContainer;

class GameServerPeer : INHERIT_POOL(GameServerPeer)
{
public:
    GameServerPeer();
    virtual ~GameServerPeer(){}

	static GameServerPeer* CreateInstance() { return MES_NEW(GameServerPeer);}
	virtual void Release();

    std::string   GetName()                            { return _strName;    }
    void          SetName( const std::string& strName ){ _strName = strName; }
    long          GetId()                              { return _Id;         }
    void          SetId( long id )                     { _Id = id;           }
    void          SetNetClient( NetClient* pNetClient ){ _pNetClient = pNetClient; }
    NetClient*    GetNetClient()                       { return _pNetClient; }
    void          UpdateBurthen( const SBurthenBase& info );
    SBurthenBase& GetBurthen()                         { return _burthenInfo ;}

    // ��������ӵ�еĿ��õ�ͼ��Ϣ ����
    void AddStageInfo( const SGameStage& gs )    { _gameStages[gs.ulStageId] = gs;    }
    void RemoveStageInfo( const SGameStage& gs ) { _gameStages.erase( gs.ulStageId ); }
	void SetStageOpen( unsigned long nMapID, bool bValue );
    bool IsHaveStageInfo( unsigned long nMapId, bool bIsRun );
    long GetAllStageId( MapIdContainer& mapIds );

    bool IsCanLogin();

    void OnMessageUpdateMapInfo( MessageUpdateMapInfo* pMessage );

    AccountIdContainer& GetAllClient() { return _clients; }

    bool AddAccountId( unsigned long nAccountId )    { return _clients.insert( nAccountId ).second;}
    void RemoveAccountId( unsigned long nAccountId ) { _clients.erase( nAccountId );               }
    void SetHaveSendAllGuildInfos( bool bHave )      { _bHaveSendAllGuildInfos = bHave; }
    bool GetHaveSendAllGuildInfos()                  { return _bHaveSendAllGuildInfos; }
    void SetHaveReady( bool bReady )                 { _bHaveReady = bReady;}
    bool GetHaveReady()                              { return _bHaveReady; }

    size_t GetClientSize(){ return _clients.size(); }

    long Send( Msg* pMessage );

    
private:
    typedef std::map<unsigned long, SGameStage> GameStageInfoContainer;
    typedef GameStageInfoContainer::iterator ItrGameStageInfoContainer;
    GameStageInfoContainer _gameStages; // ��������ӵ�еĵ�ͼId

    static const int   s_nLeaveCount = 100; // ������Ԥ����100����,��ֹ�ܶ���һ���, �����������˷ɲ�����

    std::string        _strName;
    long               _Id;
    NetClient*         _pNetClient;             //�����װ�㲻��ֱ��DELETE,������������ʱ��delete
    SBurthenBase       _burthenInfo;
    AccountIdContainer _clients;                // ���ڴ˷������м����˺�
    bool               _bHaveSendAllGuildInfos; // �Ƿ��͹����а�����Ϣ
    bool               _bHaveReady;             // �Ƿ��Ѿ�����
};

inline long GameServerPeer::Send( Msg* pMessage )
{
    CHECK_RETURN( _pNetClient== NULL, ER_NullPointer);
    return _pNetClient->Send( pMessage );
}

typedef std::vector<std::string> StringsType;
typedef std::vector<GameServerPeer*> GameServerPeers;

#endif // __CENTERSERVER_GAMESERVERPEER_H__
