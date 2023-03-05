/********************************************************************
	Filename: 	LoginServerPeer.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_LOGINSERVERPEER_H__
#define __CENTERSERVER_LOGINSERVERPEER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "Memory_Pool.h"
#include "FuncPerformanceLog.h"
#include "NetClient.h"
#include "ClientPeer.h"
#include "ClientPeerManager.h"

class LoginServerPeer : INHERIT_POOL(LoginServerPeer)
{
public:
    LoginServerPeer();
    virtual ~LoginServerPeer(){}

	DECLARE_POOL_FUNC(LoginServerPeer)

    long GetId() { return _Id; }
    void SetId( long id ){ _Id = id; }

    void SetNetClient( NetClient* pNetClient ) { _pNetClient = pNetClient; }
    NetClient* GetNetClient() { return _pNetClient; }

    long Send( Msg* pMessage );
    
    AccountIdContainer& GetAllClientId() { return _pClients; }

    bool AddAccountId( unsigned long nAccountId )    { return _pClients.insert( nAccountId ).second;}
    void RemoveAccountId( unsigned long nAccountId ) { _pClients.erase( nAccountId );}

private:
    long _Id;
    NetClient* _pNetClient;
    
    AccountIdContainer _pClients;
};

inline
long LoginServerPeer::Send( Msg* pMessage )
{
    CHECK_RETURN( _pNetClient== NULL, ER_NullPointer);
    return _pNetClient->Send( pMessage );
}

#endif // __CENTERSERVER_LOGINSERVERPEER_H__
