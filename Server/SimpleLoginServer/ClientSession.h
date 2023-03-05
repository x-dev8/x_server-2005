//�������ͻ���ֱ�ӵ�����ͨѶ by vvx 2012.4.9
#pragma once

#include "network.h"

using namespace network;

class CClientSession
{
public:
	enum
	{
		enum_in_list_unknow,			//δ֪��
		enum_in_list_state_nor_normal,	//��client�����������ӵ�������
		enum_in_list_state_waite_close,	//��client���ڵȴ��رյ�������
	};
public:
	CClientSession(void);
	~CClientSession(void);	

	void SetConnecter(Socketer* pS){m_socketer = pS;}
	Socketer* GetConnecter(){return m_socketer;}

	void SendMsg(Msg* pMsg);

	//���ô˿ͻ����˺�
	void SetAccount( const char *account = NULL ,unsigned long accountid = 0xffffffff);

	//��ȡ�˿ͻ��˵�ip
	const char *GetIP();

	//��ȡ�˿ͻ��˵��˻�
	const char *GetAccount(){ return m_account; }
	unsigned long GetAccountId(){return account_id;}

	//�Ƿ����������ӵ�������
	bool IsInNormalList(){ return enum_in_list_state_nor_normal == m_in_list_state; }

	//�Ƿ��ڵȴ��رյ�������
	bool IsInWaiteCloseList(){ return enum_in_list_state_waite_close == m_in_list_state; }

	//��client����δ֪״̬
	bool IsInUnknowList(){ return enum_in_list_unknow == m_in_list_state; }

	//�����䴦��������������
	void SetInNormalList();

	//�����䴦�ڵȴ��رյ�������
	void SetInWaiteList();
	//��¼��ʱ�����ϵ�
	void SetConnect (unsigned long current);

	void SetCloseTime (unsigned long current);

	bool CanClose (unsigned long current);

	//currentΪ��ǰʱ�䡣overtimeΪ��ʱʱ��--��ʱʱ��ΪӲ��ʱ�䡣��overtime���롣��ر�
	bool IsOverTime( unsigned long current, unsigned long overtime );
private:
	Socketer* m_socketer;
	char m_ip[20];				//��¼���������Ŀͻ��˵�ip
	char m_account[64];	//��Ǵ˿ͻ������ĸ��˺ŵ�����
	short m_in_list_state;		//��client�����״̬
	unsigned long account_id;//��Ǵ˿ͻ������ĸ��˺ŵ�����

	unsigned long m_connecttime;		//��¼��ʱ�����ϵġ�
	unsigned long m_closetime;		//�ر�ʱ��ʱ��
};