/********************************************************************
Filename:     NetworkInput.h
MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "MessageDefine.h"
//#include "MsgFromBuf.h"
#include "Network.h"
using namespace network;

#define PING_MSG_SPACE (2000)
enum EBotState
{
	e_state_no_confirm		,		//�ȴ��ʺ���֤
	e_state_wait_confirm_result,    //�ʺ���֤��
	e_state_confirm_fail,			//�ʺ���֤ʧ��
	State_Select,
/*	State_EnterCharacterS          , // �����ɫ������*/
	State_CreateChar               , // ������ɫ
/*	State_EnterGameS               , // ������Ϸ������*/
/*	State_Idle                     , // Idle�ȴ���Ϣ*/
	State_Play                     , // ��Ϸ
	State_End                      , // ����
};
const static char* s_szTips[] = 
{
	"�ʺ�δ��֤       ",
	"�ʺ���֤��       ",
	"�ʺ���֤ʧ��     ",
	"ѡ���ɫ",
/*	"�����ɫ������   ",*/
	"������ɫ         ",
/*	"������Ϸ������ ",*/
/*	"Idle�ȴ���Ϣ   ",*/
	"��Ϸ           ",
	"����           ",
};



class INetworkNode
{ //���紦��ģ��
public:
	enum EConstDefine
	{
		ECD_ReconnectGameServerInterval = 2000, // 1 ��
	};
public:
	INetworkNode();
	~INetworkNode();

	virtual void	Update();
	// ���ͻ��ڵ����ӵ��������ڵ�
/*	virtual void	OnConnectToServer(){};*/
	// ���ͻ��ڵ�����������ڵ�Ͽ�
	virtual void	OnDisconnectFromServer(){};
	virtual void	ProcessMsgs(){

	};
	///////////////////////////////////////////////////////////////////

	void ResetConnectted(void){ m_bConnectted = false; }
	bool IsConnectted(void){ return m_bConnectted; }
	BOOL InitConnect( const char *szDstIP,int iPort = 20000 );
	bool   ConnectToServer(); 
	void Close();

	virtual void try_comfirm_account(){};
//	int SendMsg( Msg*pMsg );	

	void Reset(void);
	bool IsClosed(void);
	Socketer* GetConnector(){ return m_pConnector; }
	uint8            _lastState;          // ��һ��״̬
	uint8            _currentState;       // ��ǰ״̬    
	uint8           GetBotState() { return _currentState; }
	virtual void            SetBotState( uint8 nState){};
	DWORD s_time_record;
private:
	char		  m_szDst[ 200 ];
	int		      m_iPort;
	bool		  m_bConnectted;
	
	
	


	Socketer* m_pConnector;
	Listener* m_sock;
	uint32        _dwThreadId;
};


//extern INetworkNode& GettheNetworkInput();