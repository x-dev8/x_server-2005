#ifndef __SERVERSTATUSMANAGER_H__
#define __SERVERSTATUSMANAGER_H__

#include "GlobalDef.h"
#include <string>
#include <vector>

using namespace ServerDataDefine;

/************************************************************************
    按照服务器架构, 来设计结构
    GateServer连GameServer, 我们认为GateServer为GameServer的子节点 
    类推, 我们可以构造出一个树形结构

    CharacterServer 也是一个GameServer

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
    NodeType nNodeType;             // 类型
    unsigned int nID;               // ID

    std::vector< T > vecChildData;  // 子类的服务器信息
};

// 服务器信息
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
    std::string strServerName;      // 服务器名字
    Status nStatus;                 // 服务器状态
    unsigned short ustVersion;         // 服务器版本号

    NodeType nParentNodeType;       // 父类节点类型
    unsigned int nParentID;         // 父类节点服务器ID
};

struct MsgPFServerStatusAck;
// 只针对目前服务器结构写的算法, 没工夫写通用的了
class ServerStatusManager
{
public:
    static ServerStatusManager& Instance()
    {
        static ServerStatusManager s_xManager;
        return s_xManager;
    }
    
    void RegisterServer( const ServerData& xData );         // 注册一个服务器
    ServerData* GetServerData( NodeType nParentType, unsigned int nParentID, NodeType nType, unsigned int nID );    // 获得服务器信息

    void SetStatus( Status nValue ) { m_nStatus = nValue; }
    Status GetStatus() const { return m_nStatus; }

    void SetClientID( unsigned int nValue ) { m_nClientID = nValue; }

    void RunUpdate( unsigned int nCurrentTime );

    unsigned int GetSendReqTime() const { return m_nSendReqTime; }

    void CheckVersion( ServerData& xServerData );            // 检查服务器版本

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
    
    ServerData m_xServerData;           // 服务器结构
    Status m_nStatus;                   // 当前状态
    unsigned int m_nSendReqTime;        // 发送请求各服务器状态的时间
    unsigned int m_nClientID;           // 平台ID
};

#define theServerStatusManager ServerStatusManager::Instance()

#endif