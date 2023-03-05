#ifndef __SERVERSTATUSMANAGER_H__
#define __SERVERSTATUSMANAGER_H__

#include "GlobalDef.h"
#include <string>
#include <vector>

using namespace ServerDataDefine;

/************************************************************************
    ���շ������ܹ�, ����ƽṹ
    GateServer��GameServer, ������ΪGateServerΪGameServer���ӽڵ� 
    ����, ���ǿ��Թ����һ�����νṹ

    CharacterServer Ҳ��һ��GameServer

    Hero Server Root
        CenterServer
            DataBaseServer
            CharacterServer
                GateServerCharacter
            GameServerA
                GateServer1
                GateServer2
            GameServerB
                GateServer1
                GateServer2
        .
        .
        .
************************************************************************/
template< class T >
class Data
{
public:
    Data() : nNodeType( Node_Root ), nID( ErrorID )
    {
        vecChildData.clear();
    }
    void AddChildData( const T& xData ) { vecChildData.push_back( xData ); }
    unsigned short GetChildDataCount() { return static_cast< unsigned short >( vecChildData.size() ); }
    T* GetChildData( unsigned int nIndex )
    {
         if ( nIndex >= GetChildDataCount() )
         { return NULL; }

         return &( vecChildData.at( nIndex ) );
    }

    void SetNodeType( NodeType nValue ) { nNodeType       = nValue; }
    void SetID( unsigned int nValue )   { nID             = nValue; }

    NodeType GetNodeType() const        { return nNodeType;         }
    unsigned int GetID() const          { return nID;               }

protected:
    NodeType nNodeType;             // ����
    unsigned int nID;               // ID

    std::vector< T > vecChildData;  // ����ķ�������Ϣ
};

// ��������Ϣ
class ServerData : public Data< ServerData >
{
public:
    ServerData() : nParentNodeType( Node_Root ), nParentID( ErrorID ), strServerName( "" ), nStatus( Status_Fine ), ustVersion( 0 )
    {
    }

    void SetParentNodeType( NodeType nValue )  { nParentNodeType = nValue;    }
    void SetParentID( unsigned int nValue )    { nParentID       = nValue;    }
    void SetName( const char* szName )         { strServerName   = szName;    }
    void SetStatus( Status nValue )            { nStatus         = nValue;    }
    void SetVersion( unsigned short ustValue ) { ustVersion      = ustValue;  }

    NodeType GetParentNodeType() const         { return nParentNodeType;       }
    unsigned int GetParentID() const           { return nParentID;             }
    const char* GetName() const                { return strServerName.c_str(); }
    Status GetStatus() const                   { return nStatus;               }
    unsigned short GetVersion() const          { return ustVersion;            }

protected:
    std::string strServerName;      // ����������
    Status nStatus;                 // ������״̬
    unsigned short ustVersion;         // �������汾��

    NodeType nParentNodeType;       // ����ڵ�����
    unsigned int nParentID;         // ����ڵ������ID
};

struct MsgPFServerStatusAck;
// ֻ���Ŀǰ�������ṹд���㷨, û����дͨ�õ���
class ServerStatusManager
{
public:
    static ServerStatusManager& Instance()
    {
        static ServerStatusManager s_xManager;
        return s_xManager;
    }
    
    void RegisterServer( const ServerData& xData );         // ע��һ��������
    ServerData* GetServerData( NodeType nParentType, unsigned int nParentID, NodeType nType, unsigned int nID );    // ��÷�������Ϣ

    void SetStatus( Status nValue ) { m_nStatus = nValue; }
    Status GetStatus() const { return m_nStatus; }

    void SetClientID( unsigned int nValue ) { m_nClientID = nValue; }

    void RunUpdate( unsigned int nCurrentTime );

    unsigned int GetSendReqTime() const { return m_nSendReqTime; }

    void CheckVersion( ServerData& xServerData );            // ���������汾

protected:
    ServerStatusManager() : m_nSendReqTime( 0 ), m_nClientID( 0 )
    {
        m_xServerData.SetID( 0 );
        m_xServerData.SetParentID( 0 );
        m_xServerData.SetName( "Hero Server Root" );
    };

    ServerData* GetServerData( ServerData* pParentData, NodeType nType, unsigned int nID );

    void SendMessageToServers( unsigned int nCurrentTime );
    void SendMessageToPlat();
    void WaitForServerAck( unsigned int nCurrentTime );

    bool IsNeedSendToMessage( ServerData* pServerData );

    void SetAllServerStatus( ServerData* pParentData, Status nStatus );
    void GetAllServerStatus( ServerData* pParentData, MsgPFServerStatusAck* pMessage );


    void CheckGameVersion( ServerData& xServerData, unsigned short ustDatabaseVersion );
    void CheckDatabaseVersion( ServerData* pParentData, unsigned short ustDatabaseVersion );

private:
    ServerStatusManager( const ServerStatusManager& );
    ServerStatusManager& operator = ( const ServerStatusManager& );
    
    ServerData m_xServerData;           // �������ṹ
    Status m_nStatus;                   // ��ǰ״̬
    unsigned int m_nSendReqTime;        // ���������������״̬��ʱ��
    unsigned int m_nClientID;           // ƽ̨ID
};

#define theServerStatusManager ServerStatusManager::Instance()

#endif