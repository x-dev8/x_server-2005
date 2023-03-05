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
        gw_tryconnect, // ��ͼ������Ϸ���������
        gw_ReConnect ,
        gw_normal    , // ��������״̬
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
        const_iDisConnectTimeOut       = 1000*15                          , // ���ߺ���������ʱ��
        const_iSendAllocTimeOut        = 1000*60                          ,
        const_iPingOverTime            = 1000*60*5                        , // ��ʱ���Ϊ5����
        const_iGameServerPingOverTiem  = 20000                            ,
        const_iSingleClientMaxMsgCount = 50                               , // ����������ӵ���Ϣ���������
        const_iPingGameServerTime      = 5000                             , // ping GameServer��ʱ�� 5m
    };

    struct SLoginInfo
    {
        SLoginInfo()
        {
            memset(this,0,sizeof(SLoginInfo));
            isConnected = false;
        }

        //char  szPassword[60]    ; // ����
        //char  szSeed[60]        ; // ����
        DWORD recordTime        ; // ��¼�����¼��ʱ��,�����жϵ�¼��ʱ������
        bool  isConnected       ; // �Ƿ�������
		__int64 SessionKey      ;
        //char  szSessionKey[40+1]; //
    };

    struct SDisconnectClient
    {
        //std::string szKey            ;
		__int64     SessionKey       ;
        uint32      nAccountId       ;
        int         nInGateClientsPos; // ��GateClient�����е�λ��
        uint32      nDisconnectTime  ; // ����ʱ��
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
    void           CheckForServerExit(); // ����Ƿ��ڹرշ�����

protected:
    bool           SendAllocClient( GameObjectId iID, const char* szClientName, const char* ip, DWORD dwAccountID );
    bool           AcceptNewClient();    
    void           CloseAllClient();
    void           ProcessGameServerMessage( uint32& count ); // ����GameServer��������Ϣ    
    void           ProcessAllClientMsg();      // ����ͻ�����Ϣ    
    void           SendAllClientMsg();         // �������пͻ�����Ϣ
	void           RecvAllClientMsg();         // �������пͻ�����Ϣ
    void           SendAllClientPackMsg();     // �������пͻ��˵�λ�ø�����Ϣ
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
    
    void           ReleaseReconnectClient( GamePlayer* pClient, bool bConnectHaveToOther = false ); // ֱ�������ͻ���

    void           AddToClientWaitClose( GamePlayer* pClient, char* szFun, int nLine );             // �ر��������ӵĿͻ���
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

    // ��ɫ�˳�
    void           OnMessageCharacterExit( Msg* pMsg );

    // �ͻ���������
    bool           OnClientReConnect     ( Msg* pMessage, int nAllocClientIndex, GamePlayer* pClient );

    // ��GateClient�����д���Close
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

    CStaticArray<BaseCharacter*>* m_pAllocClients;    // �ȴ�GameServer����Id����Ҷ���
    CStaticArray<BaseCharacter*>* m_pNormalClients;   // ��Ϸ�������н�ɫ�Ķ���
    CStaticArray<BaseCharacter*>* m_pClientWaitClose; // �ȴ��ӳ�ɾ���Ľ�ɫ����
    CStaticArray<BaseCharacter*>* m_pGateClients;     // �Ѿ��õ�GameServer���䵽Id����Ҷ���

    DisconnectClientContainer     m_DisConnectClient; // �洢���߿ͻ��˶���

    //�˻�id,��¼��Ϣ
    LoginInfoContainer _loginInfos; //��½�������IP

    /*IMeSocket*/Listener*    m_psockClientListen       ;
    /*IMeConnector*/Socketer* _pGameServerConnector     ;
    CGateWorld    m_world                   ;
    int           m_iOnlineNum              ; // �������� = ��������Ϸ���� + ���ӳٹرն������
    int           m_iOnlinePlayGameNum      ; // ��������Ϸ����
    int           m_iGameServerConnectStatus;
    int           m_nGameServerOnlineCount  ;
    uint32        _revShutdownCommandTime   ; // �յ���ʱ��
    uint32        _revShutdownDelayTime     ; // �յ��ӳ�ʱ����
    bool          _bStopServer              ; // �Ƿ��Ѿ�ͣ��
    bool          _bShowAllPlayerPos        ; // ��ʾ����Char��λ��
    ConsoleApplication* _pOwner             ; // ������
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
