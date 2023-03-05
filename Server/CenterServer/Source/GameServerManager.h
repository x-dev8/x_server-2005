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
    GameServerPeer* GetGameServerPeer( unsigned long Id );       // �õ�ָ�����ֵ���Ϸ��������ָ��
    void            RemoveGameServerPeer( unsigned long Id );
    void            GetGameServerNames( StringsType& strNames ); // �õ�������Ϸ������������    
    GameServerPeer* GetLowestBurthenGameServerPeer();            // �õ��������ٵ���Ϸ������ 
    GameServerPeer* GetCharacterServerPeer();                    // �õ���ɫѡ�������    
    //GameServerPeer* GetCenterLoginServerPeer();					 // �õ���¼������ID
	long            GetGameServerPeerList( unsigned long nMap, bool bIsRun, GameServerPeers& output ); // �õ��д˵�ͼ����Ϸ������
    long            GetAllMapInfo( MapInfoContainer& mapInfos );
    bool            IsAllGameServerReady();                      // �Ƿ����еķ�����׼������
    int             GetGameServerSize(){ return (int)_GameServerPeers.size();}
    void            Statistics( char* szStr = NULL);                                // ͳ������

    void            SendMsgToSingleRemote     ( uint32 sourceDbId, Msg* pMessage, uint32 nDbId, const char* szCharacterName = "", bool bDirect = true ); // �����ô˺���
    long            SendMsgToSingle           ( Msg* pMsg, uint32 dwDatabaseID, const char* szName = "" );
	long			SendMsgToSingle			  (ClientPeer* pClientPeer, Msg *pMsg);
    long            SendMsgToSingleByAccountId( Msg* pMsg, uint32 accountId );

         
    long            SendMsgToWorld              ( Msg* pMsg );
	//������Ϣ�����е����
	long			SendMsgToWorldUser			( Msg *pMsg );
    long            SendMessageToGameServers    ( Msg* pMessage, long ExceptServerId = -1 );   //������Ϣ�����з�����, nServerId ����
	long			SendMsgToSingleGameServers  ( Msg* pMessage, long GameServerId = -1 ); 
    long            SendMessageToCharacterServer( Msg* pMessage );
         

    bool            GetExtendBornMapOpen();                 
    void            SetExtendBornMapOpen( bool bValue );
       
    void            SendLoadResourceSuccessMessage( uint8 uchLoadType );
	//����Ƿ����Ŷ�.֪ͨcharacter server
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
	bool m_QueueOpen;//�Ŷӷ���
};

#endif // __CENTERSERVER_GAMESERVERMANAGER_H__
