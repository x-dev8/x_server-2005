//与其他客户端直接的连接通讯 by vvx 2012.4.9
#pragma once

#include "network.h"

using namespace network;

class CClientSession
{
public:
	enum
	{
		enum_in_list_unknow,			//未知。
		enum_in_list_state_nor_normal,	//此client处于正常连接的链表中
		enum_in_list_state_waite_close,	//此client处于等待关闭的链表中
	};
public:
	CClientSession(void);
	~CClientSession(void);	

	void SetConnecter(Socketer* pS){m_socketer = pS;}
	Socketer* GetConnecter(){return m_socketer;}

	void SendMsg(Msg* pMsg);

	//设置此客户端账号
	void SetAccount( const char *account = NULL ,unsigned long accountid = 0xffffffff);

	//获取此客户端的ip
	const char *GetIP();

	//获取此客户端的账户
	const char *GetAccount(){ return m_account; }
	unsigned long GetAccountId(){return account_id;}

	//是否在正常连接的链表中
	bool IsInNormalList(){ return enum_in_list_state_nor_normal == m_in_list_state; }

	//是否在等待关闭的链表中
	bool IsInWaiteCloseList(){ return enum_in_list_state_waite_close == m_in_list_state; }

	//此client处于未知状态
	bool IsInUnknowList(){ return enum_in_list_unknow == m_in_list_state; }

	//设置其处于正常连接链表
	void SetInNormalList();

	//设置其处于等待关闭的链表中
	void SetInWaiteList();
	//记录何时连接上的
	void SetConnect (unsigned long current);

	void SetCloseTime (unsigned long current);

	bool CanClose (unsigned long current);

	//current为当前时间。overtime为超时时间--超时时间为硬性时间。过overtime毫秒。则关闭
	bool IsOverTime( unsigned long current, unsigned long overtime );
private:
	Socketer* m_socketer;
	char m_ip[20];				//记录连接上来的客户端的ip
	char m_account[64];	//标记此客户端是哪个账号的连接
	short m_in_list_state;		//此client在哪里，状态
	unsigned long account_id;//标记此客户端是哪个账号的连接

	unsigned long m_connecttime;		//记录何时连接上的。
	unsigned long m_closetime;		//关闭时的时间
};