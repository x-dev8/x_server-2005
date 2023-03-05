//����һ���
#pragma once
#ifdef NPGUARD
#include "CSAuthMessage.h"
#include "NP/ggsrv30.h"
extern class GamePlayer;
class CSAuthManager
{
public:
	CSAuthManager();
	~CSAuthManager();
	static bool InitAllCSAuthManager();//��ʼ�����⺯�� GameServer��ʼ����ʱ��
	static void CloseAllCSAuthManager();//�رշ�������� GameServer�رյ�ʱ��
	bool InitPlayerCSAuth(GamePlayer* pPlayer);//��GamePlayer������ʱ��
	void ClosePlayerCSAuth();
	void OnUpdate(GamePlayer* pPlayer);//���º��� ������ҵ�Run������ 3���ӵ��ô�
	bool SendCheckMsgToClient(GamePlayer* pPlayer);
	bool ReviceCheckMsgByClient(MsgCheckCSAuthAck* pMsg,GamePlayer* pPlayer);
private:
	CCSAuth3 csa;//����ҵ��� ÿ��GamePlayer���и� 
	unsigned int m_NextUpdateTime;
};
#endif