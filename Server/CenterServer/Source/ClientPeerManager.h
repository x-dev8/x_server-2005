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
    
    // 添加需要登录的用户数据
    long        AddLoginClientPeer( int nAccountId, const std::string& strAccount,__int64 sessionkey, const char* strMac,/*char* szSessionKey, *//*char* szPassword,*/ /*char* Seed, */int8 isWallow ); 
    void        ProcessLoginClieetPeers();

    // Login队列相关
    ClientPeer* GetClientPeerFromLoginQueue( unsigned long nAccountId );
    bool        AddClientPeerToLoginQueue         ( ClientPeer* pClientPeer  );
    void        RemoveClientPeerFromLoginQueue    ( unsigned long nAccountId, bool bRelease = true );

    ClientPeer* GetClientPeer( uint32 nAccountId );
    bool        UpdateClientPeer( ClientPeer* pClientPeer );
    void        RemoveClientPeer( unsigned long nAccountId );

    uint32      ClientPeerSize() { return (uint32)_clientPeers.size(); }
	uint32      ClientLoginPeerSize() { return (uint32)_loginPeers.size(); }

	ClientPeer* GetClientPeerByDBId   ( uint32 dwDataBaseId);
	bool        UpdateClientPeerByDBId( ClientPeer* pClientPeer );     // 更新索引导向
	void        RemoveClientPeerByDBId( uint32 dwDataBaseId);

    ClientPeer* GetClientPeerByName   ( const std::string& strName );
    bool        UpdateClientPeerByName( ClientPeer* pClientPeer );     // 更新索引导向
    void        RemoveClientPeerByName( const std::string& strName );

	std::vector<ClientPeer*>* GetClientPeerByMac( const std::string& strMac );
	bool        UpdateClientPeerByMac( ClientPeer* pClientPeer );     // 更新索引导向
	void        RemoveClientPeerByMac( ClientPeer* pClientPeer /*const std::string& strMac*/ );

    uint32      KickClientPeer( ClientPeer* pClientPeer, uint8 kickType, uint32 time = 0 ); 
    //uint32      KickClientPeersOnGameServerException( unsigned long serverId ); GameServerManager::RemoveGameServerPeer 冲突
         
    void        SendLoginHintInfoToLoginServer( unsigned long nLoginServerId, short nClientIdInServer, long nResult );
         
    long        OnPlayerSynInServerInfo( Msg* pMessage             ); // 同步玩家在服务器上的信息
    long        OnPlayerExit           ( GS2CSPlayerExit* pMessage ); // 玩家退出游戏世界
  
    void        Update();

protected:
    ClientPeerManager();
    ClientPeerManager( const ClientPeerManager& );
    ClientPeerManager& operator=( const ClientPeerManager& ){}

    void _Release();

private:
    ClientPeerMapContainer         _loginPeers;      // 正在登录处理中的玩家 byAccountId

    ClientPeerMapContainer         _clientPeers;     // 在线玩家 byAccountId
	ClientPeerMapContainer         _dbClientPeers;   // 在线玩家 byDbId
    ClientPeerMapContainerByString _nameClientPeers; // 在线玩家 byName
	ClientPeerMapContainerByMac	   _macClientPeers;	 // 在线玩家 byMac

    uint32 _lastProcessLoginClieetPeersTime;         // 最近一次处理登录时间
};

#endif // __CENTERSERVER_CLIENTPEERMANAGER_H__
