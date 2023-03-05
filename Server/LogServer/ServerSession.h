#pragma once

#include "network.h"

using namespace network;

class CServerSession
{
public:
	enum
	{
		enum_in_list_unknow,			//未知。
		enum_in_list_state_nor_normal,	//处于正常连接的链表中
		enum_in_list_state_waite_close,	//处于等待关闭的链表中
	};
public:
	CServerSession(void);
	~CServerSession(void);

	void SetIConnecter (Socketer *ico) { m_IConnecter = ico; }
	Socketer* GetIConnecter(){ return m_IConnecter;}
	bool SendMsg( Msg *pMsg );
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
	void Reset();

	//记录何时连接上的
	void SetConnect (unsigned long current);
	void SetCloseTime (unsigned long current);
	bool CanClose (unsigned long current);
	//current为当前时间。overtime为超时时间--超时时间为硬性时间。过overtime毫秒。则关闭
	bool IsOverTime( unsigned long current, unsigned long overtime );

	void SetId(int id){_iAllocId = id;}
	int  GetId(){return _iAllocId;}

	void SetServerId(int id){server_id = id;}
	int  GetServerId(){return server_id;}
private:
	int              _iAllocId;          // 在alloc队列中的动态id
	Socketer*		 m_IConnecter;
	short			 m_in_list_state;			//此在哪里？
	unsigned long	 m_connecttime;		//记录何时连接上的。
	unsigned long	 m_closetime;		//关闭时的时间
	int              server_id;         //服务器标识
};