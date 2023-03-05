/********************************************************************
	Filename: 	LoginServerManager.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_LOGINSERVERMANANGER_H__
#define __CENTERSERVER_LOGINSERVERMANANGER_H__

#include "MeRTLibsServer.h"
#include "NetClient.h"
#include "LoginServerPeer.h"

#pragma once

#define theLoginServerManager LoginServerManager::GetInstance()

class LoginServerManager
{
public:
    ~LoginServerManager();

    static LoginServerManager& GetInstance();
    
    long Init();
    void UnInit();

    bool AddLoginServerPeer( LoginServerPeer* p );

    LoginServerPeer* GetLoginServerPeer( unsigned long nId );

    void RemoveLoginServerPeer( unsigned long nId );

protected:
    LoginServerManager();
    LoginServerManager( const LoginServerManager& ){}
    LoginServerManager& operator=( const LoginServerManager& ){}  

    void _Release();
private:
    typedef std::map<long, LoginServerPeer*> LoginServerPeerContainer;
    typedef LoginServerPeerContainer::iterator ItrLoginServerPeerContainer;

    LoginServerPeerContainer _LoginServerPeers;
};

#endif // __CENTERSERVER_LOGINSERVERMANANGER_H__
