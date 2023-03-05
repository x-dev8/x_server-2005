/********************************************************************
    Filename:     DatabaseClient.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

//#include "MeConnector.h"
#include "GlobalDef.h"
#include "MsgBase.h"
//#include "NetworkNode.h"
#include "network.h"

using namespace network;

class DatabaseClient/* : public INetworkNode*/
{
public:
    DatabaseClient();
    ~DatabaseClient();

    void ProcessMsgs();
    void OnRegister();
    void OnUnRegister();
    
    void OnMsgLogin( Msg* pMsg );

    const char* GetUserName();

	void ReleaseConnector();
	void SetConnector(Socketer* ps,bool breleaseold = true);
	void SendToClient(Msg* pMsg);
	Socketer* GetConnector(){return m_pConnector;}
	void SetId(int id){client_id = id;}
	short GetId(){return client_id;}
protected:
    void PartitionLogFile();
private:
	Socketer* m_pConnector;
	short client_id;
};
