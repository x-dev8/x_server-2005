#include "LoginServerManager.h"
#include "FuncPerformanceLog.h"
#include "GameServerManager.h"

LoginServerManager::~LoginServerManager()
{
}

LoginServerManager::LoginServerManager()
{
}

LoginServerManager& LoginServerManager::GetInstance()
{
    static LoginServerManager instance;
    return instance;
}


long LoginServerManager::Init()
{
    _Release();
    long nResult = ER_Success;
    return nResult;
}

void LoginServerManager::UnInit()
{
    _Release();
}

LoginServerPeer* LoginServerManager::GetLoginServerPeer( unsigned long nId )
{
    ItrLoginServerPeerContainer it = _LoginServerPeers.find( nId );
    if ( it != _LoginServerPeers.end())
        return it->second;
    return NULL;
}

void LoginServerManager::RemoveLoginServerPeer( unsigned long nId )
{   
    ItrLoginServerPeerContainer it = _LoginServerPeers.find( nId );
    if ( it != _LoginServerPeers.end())
    {
        LoginServerPeer* pLoginServerPeer = it->second;

        if ( pLoginServerPeer )
        {
            AccountIdContainer    Clients = pLoginServerPeer->GetAllClientId();
            ItrAccountIdContainer it    = Clients.begin();
            ItrAccountIdContainer itEnd = Clients.end();
            for (; it!=itEnd; ++it )
            {
                theClientPeerManager.RemoveClientPeer( *it );
            }
            pLoginServerPeer->Release();
			theGameServerManager.CheckQueue(theClientPeerManager.ClientPeerSize(),true);
        }

        _LoginServerPeers.erase( it );
    }
}

bool LoginServerManager::AddLoginServerPeer( LoginServerPeer* pPeer )
{
    CHECK_RETURN( pPeer==NULL, ER_NullPointer );
    return _LoginServerPeers.insert( LoginServerPeerContainer::value_type(pPeer->GetId(), pPeer) ).second;
}

void LoginServerManager::_Release()
{
    ItrLoginServerPeerContainer it = _LoginServerPeers.begin();
    for ( ; it!=_LoginServerPeers.end();++it)
    {
        LoginServerPeer* pLoginServer = it->second;
        if ( !pLoginServer)
            continue;

        pLoginServer->Release();
    }
    _LoginServerPeers.clear();
}
