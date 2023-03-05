#ifndef __GATESERVER_GATASERVER_H__
#define __GATESERVER_GATASERVER_H__

#pragma once

#include "StaticArray.h"
#include "GlobalDef.h"
#include "GamePlayer.h"
#include "World.h"
//#include "MeNetwork.h"
#include "GameTimer.h"
#include "network.h"

using namespace network;

#define WAITCLOSE_ALLOW_RATE 0.3f

#define theGateServer GettheGateServer()

class ConsoleApplication;

class CGateServer
{    
public:
    enum EServerStatus
    {   
        gw_tryconnect, // 试图连接游戏世界服务器
        gw_ReConnect ,
        gw_normal    , // 正常连接状态
    };

    enum EServerResult
    {
        ret_succ               ,
        ret_socketstartuperror ,
        ret_listenerror        ,
        ret_allocerror         ,
        ret_gwsocketcreateerror,
        GSR_LoadWorldMapError  ,
        GSR_InitWorldMapError  ,
        ret_createiocerror     ,
    };

    enum EConstDefine
    {
        const_iGWorldListenPort        = DP_GameServerListenGateServerPort,        
        const_iDisConnectTimeOut       = 1000*15                          , // 断线后允许重连时间
        const_iSendAllocTimeOut        = 1000*60                          ,
        const_iPingOverTime            = 1000*60*5                        , // 超时检测为5分钟
        const_iGameServerPingOverTiem  = 20000                            ,
        const_iSingleClientMaxMsgCount = 50                               , // 如果单个连接的消息队列数最多
        const_iPingGameServerTime      = 5000                             , // ping GameServer的时间 5m
    };

    struct SLoginInfo
    {
        SLoginInfo()
        {
            memset(this,0,sizeof(SLoginInfo));
            isConnected = false;
        }

        //char  szPassword[60]    ; // 密码
        //char  szSeed[60]        ; // 密码
        DWORD recordTime        ; // 记录请求登录的时间,用于判断登录超时的问题
        bool  isConnected       ; // 是否连接着
		__int64 SessionKey      ;
        //char  szSessionKey[40+1]; //
    };

    struct SDisconnectClient
    {
        //std::string szKey            ;
		__int64     SessionKey       ;
        uint32      nAccountId       ;
        int         nInGateClientsPos; // 在GateClient队列中的位置
        uint32      nDisconnectTime  ; // 掉线时间
    };

public:
    CGateServer( );
    virtual ~CGateServer();

    int            Init( ConsoleApplication* pOwner );
    void           Shutdown();
    void           RunOneStep();
    BaseCharacter* GetChar( GameObjectId stID );
    int            GetGameServerConnectStatus() { return m_iGameServerConnectStatus; }        
    int            GetMessageInCount( bool bTemp );
    int            GetMessageOutCount();        
    int            GetOnlinePlayGameNum() { return m_iOnlinePlayGameNum; }
    int            GetOnlineNum() { return m_iOnlineNum; }

    void           SetShutdownTime( uint32 revCommandTime, uint32 delayTime );
    void           CheckForServerExit(); // 检查是否在关闭服务器

protected:
    bool           SendAllocClient( GameObjectId iID, const char* szClientName, const char* ip, DWORD dwAccountID );
    bool           AcceptNewClient();    
    void           CloseAllClient();
    void           ProcessGameServerMessage( uint32& count ); // 处理GameServer服务器消息    
    void           ProcessAllClientMsg();      // 处理客户端消息    
    void           SendAllClientMsg();         // 发送所有客户端消息
	void           RecvAllClientMsg();         // 发送所有客户端消息
    void           SendAllClientPackMsg();     // 发送所有客户端的位置更新消息
    void           TellWorldGateInfo();
    void           UpdateTheLoginInfo();
         
    void           DispatchToPlayer      ( Msg* pMsg );
    void           DispatchToSingle      ( GameObjectId stID, Msg* pMsg );
    void           DispatchToView        ( GameObjectId stID, Msg* pMsg, bool bExceptMe = false );
    void           DispatchToRegion      ( GameObjectId stID, Msg* pMsg );

    void           DispatchToArea        ( uint32 dwMapId, int nX, int nY, Msg *pMsg );
    void           DispatchToStage       ( uint32 dwMapId, Msg *pMsg );
    void           DispatchToWorld       ( Msg* pMsg );
    void           DispatchToCountry     ( Msg* pMsg, TCountryId country, uint16 ustLevel, uint16 stExceptID );
         
    void           OnLoginInfo           ( MsgLoginInfo* pMsg);
    void           OnDelLoginInfo        ( MsgDelLoginInfo* pMsg );
    void           OnAddFirstList        ( Msg* pMsg );
    void           OnRemoveFirstList     ( Msg* pMsg );
         
    void           CheckToken            ( GamePlayer* pGamePlayer );
    bool           CreateGameServerConnectorSocket();
    void           TryConnectGameServer();
    
    void           ReleaseReconnectClient( GamePlayer* pClient, bool bConnectHaveToOther = false ); // 直接析构客户端

    void           AddToClientWaitClose( GamePlayer* pClient, char* szFun, int nLine );             // 关闭正常连接的客户端
    void           CheckClientWaitClose( bool bWait = true );
         
    void           SendClientExit( GameObjectId iID );
    int            IncreaseOnlinePlayGameNum( int nCount = 1);
    int            IncreaseOnlineNum( int nCount = 1);

    SLoginInfo*    GetLoginInfo( unsigned long accountId );
    void           PartitionLogFile();

    void           OnMsgAllocClientAck   ( Msg* pMsg );
    void           OnMsgSyncCharPos      ( Msg* pMsg );
    void           OnMsgSyncCharInfo     ( Msg* pMsg );
    void           OnMsgCreateStage      ( Msg* pMsg );
    void           OnMsgReleaseStage     ( Msg* pMsg );

    // 角色退出
    void           OnMessageCharacterExit( Msg* pMsg );

    // 客户端重新连
    bool           OnClientReConnect     ( Msg* pMessage, int nAllocClientIndex, GamePlayer* pClient );

    // 在GateClient队列中处理Close
    void           ProcessIsCloseInGateClient( GamePlayer* pGamePlayer, int nGateClientIndex );

    // for debug
    void           ShowDebugInfo();

    void           CheckDisConnectClients();

public:
    unsigned int m_dwLastUpdateLoginInfoTime;
    unsigned int m_nLastPingGameServerTime;
    unsigned int m_nGameServerAckPingTime;

private:
    typedef std::map</*std::string*/__int64, SDisconnectClient > DisconnectClientContainer;
    typedef DisconnectClientContainer::iterator       DisconnectClientContainerItr;
    typedef std::map<unsigned int, SLoginInfo>        LoginInfoContainer;
    typedef LoginInfoContainer::iterator              ItrLoginInfoContainer;

    CStaticArray<BaseCharacter*>* m_pAllocClients;    // 等待GameServer分配Id的玩家队列
    CStaticArray<BaseCharacter*>* m_pNormalClients;   // 游戏世界所有角色的队列
    CStaticArray<BaseCharacter*>* m_pClientWaitClose; // 等待延迟删除的角色队列
    CStaticArray<BaseCharacter*>* m_pGateClients;     // 已经得到GameServer分配到Id的玩家队列

    DisconnectClientContainer     m_DisConnectClient; // 存储断线客户端队列

    //账户id,登录信息
    LoginInfoContainer _loginInfos; //登陆过的玩家IP

    /*IMeSocket*/Listener*    m_psockClientListen       ;
    /*IMeConnector*/Socketer* _pGameServerConnector     ;
    CGateWorld    m_world                   ;
    int           m_iOnlineNum              ; // 在线人数 = 在线玩游戏的人 + 在延迟关闭队列里的
    int           m_iOnlinePlayGameNum      ; // 在线玩游戏的人
    int           m_iGameServerConnectStatus;
    int           m_nGameServerOnlineCount  ;
    uint32        _revShutdownCommandTime   ; // 收到的时刻
    uint32        _revShutdownDelayTime     ; // 收到延迟时间秒
    bool          _bStopServer              ; // 是否已经停服
    bool          _bShowAllPlayerPos        ; // 显示所有Char的位置
    ConsoleApplication* _pOwner             ; // 所有者
public:
    //////////////////////////////////////////////////////////////////////////
    // for debug    
    bool    showFrameTime;

    GameTimerEx xCheckDisConnectClientsTimer;
};

CGateServer& GettheGateServer();

//////////////////////////////////////////////////////////////////////////
// inline
inline int CGateServer::GetMessageInCount( bool bTemp )
{
    if ( !_pGameServerConnector )
    { return -1; }

    /*if ( bTemp )
    { return _pGameServerConnector->GetLogicInQueueSize(); }
    else
    { return _pGameServerConnector->GetInQueueSize(); }*/
	return 0;
}

inline int CGateServer::GetMessageOutCount()
{
    if ( !_pGameServerConnector )
        return -1;

    /*return _pGameServerConnector->GetOutQueueSize();*/
	return 0;
}

inline int CGateServer::IncreaseOnlinePlayGameNum( int nCount )
{
    int iCount = m_iOnlinePlayGameNum + nCount;
    if ( iCount < 0)
    { iCount = 0; }
    m_iOnlinePlayGameNum = iCount;
    return m_iOnlinePlayGameNum;
}

inline int CGateServer::IncreaseOnlineNum( int nCount)
{
    int iCount = m_iOnlineNum + nCount;
    if ( iCount < 0)
    { iCount = 0; }
    m_iOnlineNum = iCount;
    return m_iOnlineNum;
}

inline void CGateServer::SetShutdownTime( uint32 revCommandTime, uint32 delayTime )
{
    _revShutdownCommandTime = revCommandTime;
    _revShutdownDelayTime   = delayTime;
}

#endif // __GATESERVER_GATASERVER_H__
