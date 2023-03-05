/********************************************************************
    Filename:     Server.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_SERVER_H__
#define __GAMESERVER_SERVER_H__

#pragma once

#include "TcpClient.h"
#include "network.h"
#include "MeRTLibsServer.h"
#include "StaticArray.h"
#include "MessageDefine.h"
#include "CenterGameMessage.h"
#include "Mutex.h"
#include "WorkThread.h"
#include "CenterServerNetEvent.h"
#include "GameDataType.h"


using namespace network;

struct SGateServerInfo
{
    char           szIP[60];   // Gate的IP
    unsigned short nPort;      // Gate开放的端口
    unsigned int   nOnlineNum; // Gate当前承载的在线玩家数
};

// 查看性能，特定函数的调用时间
extern SProcessTime usetime[200];

class BaseCharacter;
//class IMeConnector;
//class IMeSocket;
class GamePlayer;

enum EGmToolStatus
{
    GMTOOL_WAIT,
    GMTOOL_LOGIN,
    GMTOOL_PROCESS,
};

struct GMINFO
{
    GMINFO()
    {
        pSock = NULL;
        strGMName = "";
        stState = GMTOOL_WAIT;
    }
    /*IMeConnector*/Socketer* pSock;    // GMTool的Sock
    std::string strGMName;  // GMTool对应的GM名称
    unsigned short stState; // 当前状态
};

enum EGameServerError
{
    ERROR_OK,
    ERROR_FAILED_SHUTDOWN,
    ERROR_FAILED_STARTUP,
    ERROR_FAILED_LISTEN,
    ERROR_FAILED_INIT_SERVER_SOCKET,
    ERROR_FAILED_INIT_CLIENT,
    ERROR_NOPLACE_FOR_CLIENT,
    ERROR_FAILED_ACCEPT,
    ERROR_FAILED_ACK_ACCEPT,
    ERROR_CLOSE_INVALID_CLIENT,
    ERROR_FAILED_CLOSE_CLIENT_SOCKET,
    ERROR_SEND_PACKET_TO_INVALID_CLIENT,
    ERROR_FAILED_SEND_PACKET,

    ERROR_FAILED_SEND,
    ERROR_FAILED_SELECT,
};

class ConsoleApplication;

class GameServer
{
public:
    enum EConstDefine
    {
        const_iMaxGate = 10,
        ECD_LoginInfoUpdateFrequency = 60000,  // 60  秒 更新登录信息的时间频率
        ECD_LoginInfoKeepTime        = 600000, // 600 秒 登录信息的保存时间
    };

public:
    GameServer( DWORD dwAddress, WORD wPort );
    virtual ~GameServer();

    // 发包线程
    static void     SendMsgThread(void* p);
                   
    DWORD           Init( ConsoleApplication* pOwner );      // 初始化服务器
    DWORD           ShutDown();  // 关闭服务器
    DWORD           Startup();   // 启动服务
    void            RunOneStep(); // 运行一轮
                   
    DWORD           GetServerElapseTime()   { return m_dwElapseTime;    } // 取得服务器一次心跳处理需要的时间
    DWORD           GetServerAvgElapseTime(){ return m_dwAvgElapseTime; }
    DWORD           GetStartTime()          { return m_dwStartTime;     }

    void            SetShutdownTime( uint32 revCommandTime, uint32 delayTime );
    uint32          GetShutdownTime() { return _revShutdownCommandTime; }
    uint32          GetShutdownTimeDelay() { return _revShutdownDelayTime; }

    char*           GetFormatErrorString( DWORD dwError );
    bool            SwitchGateServer( MsgSwitchGate* msg, int& nGateServerIndex );

    bool            AddLoginGateCacheInfo( /*char* szSessionKey*/__int64 SessionKey, S2SSwitchGate& info );
    S2SSwitchGate*  GetLoginGateCacheInfo( /*char* szSessionKey*/__int64 SessionKey );
    void            RemoveLoginGateCacheInfo( /*char* szSessionKey*/__int64 SessionKey );

    bool            AddLoginInfo( SLoginInfoBase& info );
    SLoginInfoBase* GetLoginInfo( /*char* szSessionKey*/__int64 SessionKey );
    void            UpdateLoginInfo(); // Update已经连接的玩家
    void            RemoveLoginInfo( /*char* szSessionKey*/__int64 SessionKey );

    void            SendMsgToSingle     ( Msg* pMessage, BaseCharacter* pSendTarget          ); // 发消息给指定的玩家
    void            SendMsgToView       ( Msg* pMessage, GameObjectId playerId, bool bExceptMe = false ); // 发消息给视野内的玩家
    void            SendMsgToArea       ( Msg* pMessage, DWORD dwMapId, int nX, int nY       ); // 发消息给区域内的玩家
    void            SendMsgToRegion     ( Msg* pMessage, GameObjectId playerId              ); // 发消息给地域内的玩家
    void            SendMsgToStage      ( Msg* pMessage, TStageId dwMapId                    ); // 发消息给本场景内的玩家
    void            SendMsgToWorld      ( Msg* pMessage, bool bToCenterServer = false        ); // 发消息给游戏世界里的玩家 默认本服
    void            SendMsgToCountry    ( Msg* pMessage, TCountryId uchCountryId, bool bToCenter, uint16 usthLevel = 0, uint16 stExceptID = -1 ); // 发消息给国家
        
    //void            SendMsgToLoginServer ( Msg* pMessage                     ); // 发消息给LoginServer
    long            SendMsgToCenterServer( Msg* pMessage, void* pData = NULL ); // 发消息给CenterServer
        
    bool            SendMsgToSingleRemote  ( unsigned long sourceDbId, Msg* pMessage, unsigned long nDbId, const char* szCharacterName = "", bool bDirect = true );
    bool            SendMsgToTeamRemote    ( Msg* pMessage, S2STransmit::STeam& xTeam, bool bDirect = true );
    bool            SendMsgToOrganizeRemote( Msg* pMessage, unsigned int Guild,        bool bDirect = true );
    bool            SendMsgToAllServer     ( Msg* pMessage, unsigned int ServerId,     bool bExceptMe );
        
    void            SendMsgToGate ( Msg* pMessage, int iGate, GateMsgAdditionalData* pData = NULL ); // 发消息给GateServer 一般发给自己
    void            SendMsgToGates( Msg* pMessage, GateMsgAdditionalData* pData = NULL            );
        
    //void            SendGMMsg  ( Msg* pMsg                       ); // 发消息给GM
    //void            SendGMMsg  ( const char* szData, size_t size );
    void            TellClients( const char* string, ... );
        
    long            SendUserMsgToCenterServer( GamePlayer *user, Msg *pMessage);
    long            SendCenterServerMsg( Msg* pMessage ); // 发消息给CenterServer
    void            CheckForServerExit();                 // 检查是否在关闭服务器
    //////////////////////////////////////////////////////////////////////////
    // GateServer
    /*IMeConnector*/Socketer* GetGate( short stGateID );
    void CloseAllGates();
    void RecvAllGateMsg();
    void SendAllGateMsg();
    bool OnAcceptGateServer();    
    void ProcessGateMsg(); //处理GateServer的消息
    void AllocNewGateClient( uint16 stGateID, /*IMeConnector*/Socketer* pGate,GameObjectId stID, const std::string& strAccountName, const std::string& ip, DWORD dwAccountID );
    void DeleteGateClient( GameObjectId stID );
    void DeleteAllGateClient( uint16 stGateID );

    //////////////////////////////////////////////////////////////////////////
    // Gm Tools
	//void RecvGMMsg();
	//void SendGMMsg();
	//void ProcessGMMsg();
	//bool AcceptGmTools();
    
    //////////////////////////////////////////////////////////////////////////
    // LoginServer
    /*void RecvLoginServerMsg();
    void SendLoginServerMsg();
    void ProcessLoginServerMsg();
    bool AcceptLoginServer();*/
    
    //////////////////////////////////////////////////////////////////////////
    // CenterServer
    void RunCenterServerCommunication();
    bool IsCenterServerConnecting() { return _ConnectCenterServerTcpClient.GetConnectState() == TcpClient::CS_Connected; }

    bool IsCenterServerValidate() { return _bPassCenterServerValidate;}
    void SetCenterServerValidate( bool bPassCenterServerValidate ) { _bPassCenterServerValidate = bPassCenterServerValidate; }
    TcpClient& GetCenterServerConnector() { return _ConnectCenterServerTcpClient; }
    
    void NotifyMainConsoleThread();

protected:
	bool _StartGraphicCodeCheckThread();
	void _StopGraphicCodeCheckThread();

	bool _StartParthFinderThread();
	void _StopParthFinderThread();

	bool _StartConfigReloaderThread();
	void _StopConfigReloaderThread();

	bool _StartPlayerMoveAnalysisThread();
	void _StopPlayerMoveAnalysisThread();

    bool _StartSendMsgThread();
    void _StopSendMsgThread();

    void _AcceptAllConnect();
    void _LoadDatabaseData();

public:

    DWORD        m_dwAddress;
    DWORD        m_dwAvgElapseTime; // 平均一次游戏心跳处理的时间
    DWORD        m_dwElapseTime;    // 一次游戏心跳处理的时间
    DWORD        m_dwStartTime;     // 启动时间
    unsigned int m_dwLastUpdateLoginInfoTime;

    typedef std::map</*std::string*/__int64, SLoginInfoBase> LoginInfoContainer;
    typedef LoginInfoContainer::iterator          ItrLoginInfoContainer;

    typedef std::map</*std::string*/__int64, S2SSwitchGate>  LoginGateCacheInfoContainer;
    typedef LoginGateCacheInfoContainer::iterator ItrLoginGateCacheInfoContainer;

    LoginInfoContainer          _loginInfos;
    LoginGateCacheInfoContainer _loginGateCacheInfos;

public:
    //////////////////////////////////////////////////////////////////////////
    // 与GateServer通讯
    /*IMeSocket*/Listener*                    _pSocketGateServerListen;
    CStaticArray< /*IMeConnector*/Socketer* > _GateServers;
    CSemiAutoIntLock              _lockGateServer;

    //GateServer的信息，Key为在GateServer在staticarray中的索引
    typedef std::map<int, SGateServerInfo> GateInfoContainer;
    typedef GateInfoContainer::iterator ItrGateInfoContainer;
    GateInfoContainer _GateServerInfos;  

    //////////////////////////////////////////////////////////////////////////
    // GM平台 专用端口监听 20008 不用了
    ///*IMeSocket*/Listener* _pSocketGmToolListen;
    //typedef std::list</*IMeConnector*/Socketer*> GMConnectorContainer;
    //GMConnectorContainer _GmConnectors;

    //////////////////////////////////////////////////////////////////////////
    // LoginServer 专用端口监听 20010(不用了)
    ///*IMeSocket*/Listener* m_pLoginListen;
    ///*IMeConnector*/Socketer* _pLoginServerConnector;

private:
    //////////////////////////////////////////////////////////////////////////
    // CenterServer
    CenterServerNetEvent _CenterServerNetEvent;
    TcpClient            _ConnectCenterServerTcpClient;
    bool                 _bPassCenterServerValidate;
    CWorkThread          _sendthread;
    uint32               _revShutdownCommandTime; // 收到的时刻
    uint32               _revShutdownDelayTime;   // 收到延迟时间秒
    ConsoleApplication*  _pOwner;    

	CWorkThread			_GraphicCodeCheckThread;	//图形验证码生产线程
	CWorkThread			_ParthFinderThread;			// 寻路线程

	CWorkThread			_configReloaderThread;		// 配置热重载线程

	CWorkThread			_playerMoveAnalysisThread;	// 玩家移动合法性分析线程
};

GameServer& GettheServer();

//////////////////////////////////////////////////////////////////////////
inline void GameServer::SetShutdownTime( uint32 revCommandTime, uint32 delayTime )
{
    _revShutdownCommandTime = revCommandTime;
    _revShutdownDelayTime   = delayTime;
}

#endif // __GAMESERVER_SERVER_H__
