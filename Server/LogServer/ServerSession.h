#pragma once

#include "network.h"

using namespace network;

class CServerSession
{
public:
	enum
	{
		enum_in_list_unknow,			//δ֪��
		enum_in_list_state_nor_normal,	//�����������ӵ�������
		enum_in_list_state_waite_close,	//���ڵȴ��رյ�������
	};
public:
	CServerSession(void);
	~CServerSession(void);

	void SetIConnecter (Socketer *ico) { m_IConnecter = ico; }
	Socketer* GetIConnecter(){ return m_IConnecter;}
	bool SendMsg( Msg *pMsg );
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
	void Reset();

	//��¼��ʱ�����ϵ�
	void SetConnect (unsigned long current);
	void SetCloseTime (unsigned long current);
	bool CanClose (unsigned long current);
	//currentΪ��ǰʱ�䡣overtimeΪ��ʱʱ��--��ʱʱ��ΪӲ��ʱ�䡣��overtime���롣��ر�
	bool IsOverTime( unsigned long current, unsigned long overtime );

	void SetId(int id){_iAllocId = id;}
	int  GetId(){return _iAllocId;}

	void SetServerId(int id){server_id = id;}
	int  GetServerId(){return server_id;}
private:
	int              _iAllocId;          // ��alloc�����еĶ�̬id
	Socketer*		 m_IConnecter;
	short			 m_in_list_state;			//�������
	unsigned long	 m_connecttime;		//��¼��ʱ�����ϵġ�
	unsigned long	 m_closetime;		//�ر�ʱ��ʱ��
	int              server_id;         //��������ʶ
};