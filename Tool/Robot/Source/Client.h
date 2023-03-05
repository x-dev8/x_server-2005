#pragma once
#include <vector>
#include "NetworkInput.h"

using namespace std;

#define CLIENT_ID 0


class LoginInfo;
class BaseRobot;
class Client : public BaseRobot
{
public:
    Client();
	Client(LoginInfo *pLoginInfo);
	virtual ~Client();

	virtual void Update();	
	virtual void PlayGame();
	virtual void Say(const char *pszChat){};
	virtual void Move();

	virtual void    SwitchMsg( Msg* pMsg );
	virtual void    ReGetCharacterlist();

	//virtual void OnMsg_AckLogin(Msg* pMsg);
	virtual void OnMsg_AckChar(Msg* pMsg);
	virtual void OnMsg_EndAckChar(Msg* pMsg);
	virtual void OnMsgAckEnterWorld(Msg* pMsg);
	virtual void OnMsg_AckCreateCheckName(Msg* pMsg);
	virtual void OnMsg_AckCreateChar(Msg* pMsg);
    virtual void OnMsgPingMsg(Msg* PingMsg);
public:	
	
	void SetToPositon(int nPosX, int nPosY);

private:
	LoginInfo *m_pLoginInfo;
public:
	vector<byte> m_vecDelete;

	D3DXVECTOR3 m_xToPos;


public: // for new client
    DWORD dwPingTime;

};