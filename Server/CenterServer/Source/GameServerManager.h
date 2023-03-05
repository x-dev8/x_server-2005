#ifndef __CENTERSERVER_GAMESERVERMANAGER_H__
#define __CENTERSERVER_GAMESERVERMANAGER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "FuncPerformanceLog.h"
#include "GameServerPeer.h"
#include "MapConfig.h"

typedef std::vector<std::pair<long,SGameStage>> MapInfoContainer;

#define theGameServerManager GameServerManager::GetInstance()

class GameServerManager
{
public:
    static GameServerManager& GetInstance();

    long            Init();
    void            UnInit();
    bool            AddGameServerPeer( GameServerPeer* pPeer );
    GameServerPeer* GetGameServerPeer( unsigned long Id );       // 得到指定名字的游戏服务器的指针
    void            RemoveGameServerPeer( unsigned long Id );
    void            GetGameServerNames( StringsType& strNames ); // 得到所有游戏服务器的名字    
    GameServerPeer* GetLowestBurthenGameServerPeer();            // 得到负载最少的游戏服务器 
    GameServerPeer* GetCharacterServerPeer();                    // 得到角色选择服务器    
    //GameServerPeer* GetCenterLoginServerPeer();					 // 得到登录服务器ID
	long            GetGameServerPeerList( unsigned long nMap, bool bIsRun, GameServerPeers& output ); // 得到有此地图的游戏服务器
    long            GetAllMapInfo( MapInfoContainer& mapInfos );
    bool            IsAllGameServerReady();                      // 是否所有的服务器准备就绪
    int             GetGameServerSize(){ return (int)_GameServerPeers.size();}
    void            Statistics( char* szStr = NULL);                                // 统计数据

    void            SendMsgToSingleRemote     ( uint32 sourceDbId, Msg* pMessage, uint32 nDbId, const char* szCharacterName = "", bool bDirect = true ); // 尽量用此函数
    long            SendMsgToSingle           ( Msg* pMsg, uint32 dwDatabaseID, const char* szName = "" );
	long			SendMsgToSingle			  (ClientPeer* pClientPeer, Msg *pMsg);
    long            SendMsgToSingleByAccountId( Msg* pMsg, uint32 accountId );

         
    long            SendMsgToWorld              ( Msg* pMsg );
	//发送消息给所有的玩家
	long			SendMsgToWorldUser			( Msg *pMsg );
    long            SendMessageToGameServers    ( Msg* pMessage, long ExceptServerId = -1 );   //发送消息给所有服务器, nServerId 除外
	long			SendMsgToSingleGameServers  ( Msg* pMessage, long GameServerId = -1 ); 
    long            SendMessageToCharacterServer( Msg* pMessage );
         

    bool            GetExtendBornMapOpen();                 
    void            SetExtendBornMapOpen( bool bValue );
       
    void            SendLoadResourceSuccessMessage( uint8 uchLoadType );
	//检测是否开启排队.通知character server
	void			CheckQueue(int nNum,bool sub);
	bool			LogOnlineInfo(int _logic,int _normal,int _kick,int _total);
	int				GetNormalClientNum();
protected:
    GameServerManager();
    GameServerManager( const GameServerManager& );
    GameServerManager& operator=( const GameServerManager& ){}    

    void _Release();

private:
    typedef std::map<unsigned long, GameServerPeer*> GameServerPeerContainer;
    typedef GameServerPeerContainer::iterator        ItrGameServerPeerContainer;

    GameServerPeerContainer _GameServerPeers;

    typedef std::map< unsigned int, bool > BornMap;
    typedef BornMap::iterator BornMapIter;

    bool m_bExtendBornMapOpen;
	bool m_QueueOpen;//排队服务
};

#endif // __CENTERSERVER_GAMESERVERMANAGER_H__
