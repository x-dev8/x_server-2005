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
	e_state_no_confirm		,		//等待帐号验证
	e_state_wait_confirm_result,    //帐号验证中
	e_state_confirm_fail,			//帐号验证失败
	State_Select,
/*	State_EnterCharacterS          , // 进入角色服务器*/
	State_CreateChar               , // 创建角色
/*	State_EnterGameS               , // 进入游戏服务器*/
/*	State_Idle                     , // Idle等待消息*/
	State_Play                     , // 游戏
	State_End                      , // 结束
};
const static char* s_szTips[] = 
{
	"帐号未验证       ",
	"帐号验证中       ",
	"帐号验证失败     ",
	"选择角色",
/*	"进入角色服务器   ",*/
	"创建角色         ",
/*	"进入游戏服务器 ",*/
/*	"Idle等待消息   ",*/
	"游戏           ",
	"结束           ",
};



class INetworkNode
{ //网络处理模块
public:
	enum EConstDefine
	{
		ECD_ReconnectGameServerInterval = 2000, // 1 秒
	};
public:
	INetworkNode();
	~INetworkNode();

	virtual void	Update();
	// 当客户节点连接到服务器节点
/*	virtual void	OnConnectToServer(){};*/
	// 当客户节点连与服务器节点断开
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
	uint8            _lastState;          // 上一次状态
	uint8            _currentState;       // 当前状态    
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