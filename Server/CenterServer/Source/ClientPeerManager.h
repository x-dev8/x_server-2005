/********************************************************************
	Filename: 	ClientPeerManager.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_CLIENTPEERMANAGER_H__
#define __CENTERSERVER_CLIENTPEERMANAGER_H__

#pragma once

#include "ClientPeer.h"

#define theClientPeerManager ClientPeerManager::GetInstance()

class ClientPeerManager
{
public:
    static ClientPeerManager& GetInstance();
    
    // �����Ҫ��¼���û�����
    long        AddLoginClientPeer( int nAccountId, const std::string& strAccount,__int64 sessionkey, const char* strMac,/*char* szSessionKey, *//*char* szPassword,*/ /*char* Seed, */int8 isWallow ); 
    void        ProcessLoginClieetPeers();

    // Login�������
    ClientPeer* GetClientPeerFromLoginQueue( unsigned long nAccountId );
    bool        AddClientPeerToLoginQueue         ( ClientPeer* pClientPeer  );
    void        RemoveClientPeerFromLoginQueue    ( unsigned long nAccountId, bool bRelease = true );

    ClientPeer* GetClientPeer( uint32 nAccountId );
    bool        UpdateClientPeer( ClientPeer* pClientPeer );
    void        RemoveClientPeer( unsigned long nAccountId );

    uint32      ClientPeerSize() { return (uint32)_clientPeers.size(); }
	uint32      ClientLoginPeerSize() { return (uint32)_loginPeers.size(); }

	ClientPeer* GetClientPeerByDBId   ( uint32 dwDataBaseId);
	bool        UpdateClientPeerByDBId( ClientPeer* pClientPeer );     // ������������
	void        RemoveClientPeerByDBId( uint32 dwDataBaseId);

    ClientPeer* GetClientPeerByName   ( const std::string& strName );
    bool        UpdateClientPeerByName( ClientPeer* pClientPeer );     // ������������
    void        RemoveClientPeerByName( const std::string& strName );

	std::vector<ClientPeer*>* GetClientPeerByMac( const std::string& strMac );
	bool        UpdateClientPeerByMac( ClientPeer* pClientPeer );     // ������������
	void        RemoveClientPeerByMac( ClientPeer* pClientPeer /*const std::string& strMac*/ );

    uint32      KickClientPeer( ClientPeer* pClientPeer, uint8 kickType, uint32 time = 0 ); 
    //uint32      KickClientPeersOnGameServerException( unsigned long serverId ); GameServerManager::RemoveGameServerPeer ��ͻ
         
    void        SendLoginHintInfoToLoginServer( unsigned long nLoginServerId, short nClientIdInServer, long nResult );
         
    long        OnPlayerSynInServerInfo( Msg* pMessage             ); // ͬ������ڷ������ϵ���Ϣ
    long        OnPlayerExit           ( GS2CSPlayerExit* pMessage ); // ����˳���Ϸ����
  
    void        Update();

protected:
    ClientPeerManager();
    ClientPeerManager( const ClientPeerManager& );
    ClientPeerManager& operator=( const ClientPeerManager& ){}

    void _Release();

private:
    ClientPeerMapContainer         _loginPeers;      // ���ڵ�¼�����е���� byAccountId

    ClientPeerMapContainer         _clientPeers;     // ������� byAccountId
	ClientPeerMapContainer         _dbClientPeers;   // ������� byDbId
    ClientPeerMapContainerByString _nameClientPeers; // ������� byName
	ClientPeerMapContainerByMac	   _macClientPeers;	 // ������� byMac

    uint32 _lastProcessLoginClieetPeersTime;         // ���һ�δ����¼ʱ��
};

#endif // __CENTERSERVER_CLIENTPEERMANAGER_H__
