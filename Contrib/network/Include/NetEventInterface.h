#ifndef __NETMIDDLE_NETEVENTINTERFACE_H__
#define __NETMIDDLE_NETEVENTINTERFACE_H__

#pragma once

#pragma warning ( push, 0 )
#include "MeRTLibsServer.h"
#include "NetClient.h"
#include "TcpServer.h"
#pragma warning ( pop )

class TcpServer;

#define ME_SAFE_CONVERSION_MESSAGE( messagepointer, messagetype ) \
        messagetype* pTMessage = (messagetype*)messagepointer; \
        CHECK_RETURN( pMessage->GetLength()!=sizeof(messagetype), ERNC_MessageLengthError ); 

#define ME_MESSAGE_MAPPING_BEGIN \
        CHECK_RETURN( pMessage==NULL, ERNC_NullPointer); \
        switch ( msgType ) \
            {

#define ME_MESSAGE_HANDLE( messageId, messageClassType, messageHandle ) \
        case messageId: \
            { \
                ME_SAFE_CONVERSION_MESSAGE(pMessage, messageClassType ); \
                messageHandle( pNetClient, pTMessage ); \
            } \
            break;

#define ME_MESSAGE_HANDLE_NOTCHECK( messageId, messageClassType, messageHandle ) \
        case messageId: \
            { \
                messageClassType* pTMessage = (messageClassType*)pMessage; \
                messageHandle( pNetClient, pTMessage ); \
            } \
            break;

#define ME_MESSAGE_MAPPING_END \
            }

class INetEvent
{
public:
	/*
	* the virtual function use only by TcpServer.
	* return value:
	* true	-> NetClient is Valid.
	* false -> NetClient will Invalid.
	* */
    virtual bool OnAccept( TcpServer* /*pTcpServer*/, NetClient* /*pNetClient*/){ return true; }
	/*
	* the virtual function use only by TcpServer.
	* Because TcpClient will loop TryConnect.
	* */
    virtual bool OnDisconnect( TcpServer* /*pTcpServer*/, NetClient* /*pNetClient*/, void * /*pAttachInfo*/){ return true; }
	/*
	* the virtual function use is Valid.
	* */
    virtual bool OnOvertime( TcpServer* /*pTcpServer*/, NetClient* /*pNetClient*/, void * /*pAttachInfo*/){ return true; }
	/*
	* the virtual function use is Valid.
	* */
    virtual bool OnConnectBroken( TcpServer* /*pTcpServer*/, NetClient* /*pNetClient*/, void * /*pAttachInfo*/){ return true; }
	/*
	* the virtual function use is Valid.
	* */
    virtual bool OnReceiveRateFast( TcpServer* /*pTcpServer*/, NetClient* /*pNetClient*/ ){ return true; }
	/*
	* the virtual function use by TcpServer or TcpClient.
	* when TcpServer's value:
	* TcpServer == NULL -> client's msg.
	* TcpServer != NULL -> server's msg.
	* */
    virtual long OnMessageIncoming( TcpServer* /*pTcpServer*/,NetClient* /*pNetClient*/, unsigned long /*msgType*/, Msg* /*pMessage*/ ){ return true; }
};

#endif // __NETMIDDLE_NETEVENTINTERFACE_H__
