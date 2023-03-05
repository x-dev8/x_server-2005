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
    char           szIP[60];   // Gate��IP
    unsigned short nPort;      // Gate���ŵĶ˿�
    unsigned int   nOnlineNum; // Gate��ǰ���ص����������
};

// �鿴���ܣ��ض������ĵ���ʱ��
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
    /*IMeConnector*/Socketer* pSock;    // GMTool��Sock
    std::string strGMName;  // GMTool��Ӧ��GM����
    unsigned short stState; // ��ǰ״̬
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
        ECD_LoginInfoUpdateFrequency = 60000,  // 60  �� ���µ�¼��Ϣ��ʱ��Ƶ��
        ECD_LoginInfoKeepTime        = 600000, // 600 �� ��¼��Ϣ�ı���ʱ��
    };

public:
    GameServer( DWORD dwAddress, WORD wPort );
    virtual ~GameServer();

    // �����߳�
    static void     SendMsgThread(void* p);
                   
    DWORD           Init( ConsoleApplication* pOwner );      // ��ʼ��������
    DWORD           ShutDown();  // �رշ�����
    DWORD           Startup();   // ��������
    void            RunOneStep(); // ����һ��
                   
    DWORD           GetServerElapseTime()   { return m_dwElapseTime;    } // ȡ�÷�����һ������������Ҫ��ʱ��
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
    void            UpdateLoginInfo(); // Update�Ѿ����ӵ����
    void            RemoveLoginInfo( /*char* szSessionKey*/__int64 SessionKey );

    void            SendMsgToSingle     ( Msg* pMessage, BaseCharacter* pSendTarget          ); // ����Ϣ��ָ�������
    void            SendMsgToView       ( Msg* pMessage, GameObjectId playerId, bool bExceptMe = false ); // ����Ϣ����Ұ�ڵ����
    void            SendMsgToArea       ( Msg* pMessage, DWORD dwMapId, int nX, int nY       ); // ����Ϣ�������ڵ����
    void            SendMsgToRegion     ( Msg* pMessage, GameObjectId playerId              ); // ����Ϣ�������ڵ����
    void            SendMsgToStage      ( Msg* pMessage, TStageId dwMapId                    ); // ����Ϣ���������ڵ����
    void            SendMsgToWorld      ( Msg* pMessage, bool bToCenterServer = false        ); // ����Ϣ����Ϸ���������� Ĭ�ϱ���
    void            SendMsgToCountry    ( Msg* pMessage, TCountryId uchCountryId, bool bToCenter, uint16 usthLevel = 0, uint16 stExceptID = -1 ); // ����Ϣ������
        
    //void            SendMsgToLoginServer ( Msg* pMessage                     ); // ����Ϣ��LoginServer
    long            SendMsgToCenterServer( Msg* pMessage, void* pData = NULL ); // ����Ϣ��CenterServer
        
    bool            SendMsgToSingleRemote  ( unsigned long sourceDbId, Msg* pMessage, unsigned long nDbId, const char* szCharacterName = "", bool bDirect = true );
    bool            SendMsgToTeamRemote    ( Msg* pMessage, S2STransmit::STeam& xTeam, bool bDirect = true );
    bool            SendMsgToOrganizeRemote( Msg* pMessage, unsigned int Guild,        bool bDirect = true );
    bool            SendMsgToAllServer     ( Msg* pMessage, unsigned int ServerId,     bool bExceptMe );
        
    void            SendMsgToGate ( Msg* pMessage, int iGate, GateMsgAdditionalData* pData = NULL ); // ����Ϣ��GateServer һ�㷢���Լ�
    void            SendMsgToGates( Msg* pMessage, GateMsgAdditionalData* pData = NULL            );
        
    //void            SendGMMsg  ( Msg* pMsg                       ); // ����Ϣ��GM
    //void            SendGMMsg  ( const char* szData, size_t size );
    void            TellClients( const char* string, ... );
        
    long            SendUserMsgToCenterServer( GamePlayer *user, Msg *pMessage);
    long            SendCenterServerMsg( Msg* pMessage ); // ����Ϣ��CenterServer
    void            CheckForServerExit();                 // ����Ƿ��ڹرշ�����
    //////////////////////////////////////////////////////////////////////////
    // GateServer
    /*IMeConnector*/Socketer* GetGate( short stGateID );
    void CloseAllGates();
    void RecvAllGateMsg();
    void SendAllGateMsg();
    bool OnAcceptGateServer();    
    void ProcessGateMsg(); //����GateServer����Ϣ
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
    DWORD        m_dwAvgElapseTime; // ƽ��һ����Ϸ���������ʱ��
    DWORD        m_dwElapseTime;    // һ����Ϸ���������ʱ��
    DWORD        m_dwStartTime;     // ����ʱ��
    unsigned int m_dwLastUpdateLoginInfoTime;

    typedef std::map</*std::string*/__int64, SLoginInfoBase> LoginInfoContainer;
    typedef LoginInfoContainer::iterator          ItrLoginInfoContainer;

    typedef std::map</*std::string*/__int64, S2SSwitchGate>  LoginGateCacheInfoContainer;
    typedef LoginGateCacheInfoContainer::iterator ItrLoginGateCacheInfoContainer;

    LoginInfoContainer          _loginInfos;
    LoginGateCacheInfoContainer _loginGateCacheInfos;

public:
    //////////////////////////////////////////////////////////////////////////
    // ��GateServerͨѶ
    /*IMeSocket*/Listener*                    _pSocketGateServerListen;
    CStaticArray< /*IMeConnector*/Socketer* > _GateServers;
    CSemiAutoIntLock              _lockGateServer;

    //GateServer����Ϣ��KeyΪ��GateServer��staticarray�е�����
    typedef std::map<int, SGateServerInfo> GateInfoContainer;
    typedef GateInfoContainer::iterator ItrGateInfoContainer;
    GateInfoContainer _GateServerInfos;  

    //////////////////////////////////////////////////////////////////////////
    // GMƽ̨ ר�ö˿ڼ��� 20008 ������
    ///*IMeSocket*/Listener* _pSocketGmToolListen;
    //typedef std::list</*IMeConnector*/Socketer*> GMConnectorContainer;
    //GMConnectorContainer _GmConnectors;

    //////////////////////////////////////////////////////////////////////////
    // LoginServer ר�ö˿ڼ��� 20010(������)
    ///*IMeSocket*/Listener* m_pLoginListen;
    ///*IMeConnector*/Socketer* _pLoginServerConnector;

private:
    //////////////////////////////////////////////////////////////////////////
    // CenterServer
    CenterServerNetEvent _CenterServerNetEvent;
    TcpClient            _ConnectCenterServerTcpClient;
    bool                 _bPassCenterServerValidate;
    CWorkThread          _sendthread;
    uint32               _revShutdownCommandTime; // �յ���ʱ��
    uint32               _revShutdownDelayTime;   // �յ��ӳ�ʱ����
    ConsoleApplication*  _pOwner;    

	CWorkThread			_GraphicCodeCheckThread;	//ͼ����֤�������߳�
	CWorkThread			_ParthFinderThread;			// Ѱ·�߳�

	CWorkThread			_configReloaderThread;		// �����������߳�

	CWorkThread			_playerMoveAnalysisThread;	// ����ƶ��Ϸ��Է����߳�
};

GameServer& GettheServer();

//////////////////////////////////////////////////////////////////////////
inline void GameServer::SetShutdownTime( uint32 revCommandTime, uint32 delayTime )
{
    _revShutdownCommandTime = revCommandTime;
    _revShutdownDelayTime   = delayTime;
}

#endif // __GAMESERVER_SERVER_H__
