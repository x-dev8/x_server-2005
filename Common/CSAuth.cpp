#ifdef NPGUARD
#include "CSAuth.h"
#include "GamePlayer.h"
#include "ColorScreen.h"
void __stdcall CS3LogCallback( int nLogType, char *szLog )
{
	/*if( nLogType == LOG_UPDATE )
		printf("this is update log : %s\n", szLog);
	else if( nLogType == LOG_NORMAL )
		printf("this is normal log : %s\n", szLog);
	else if( nLogType == LOG_DEBUG )
		printf("this is debug log : %s\n", szLog );*/
}

void __stdcall CS3UpdateInfoCallback( int nUpdateType, int nBefore, int nAfter )
{
	/*if( nUpdateType == UPDATE_PROTOCOL )
		printf("this is protocol update notification : %d -> %d \n", nBefore, nAfter);
	else if( nUpdateType == UPDATE_GGVERSION )
		printf("this is ggversion update notification : %d -> %d \n", nBefore, nAfter);*/
}
CSAuthManager::CSAuthManager()
{
	m_NextUpdateTime = 0;
}
CSAuthManager::~CSAuthManager()
{

}
bool CSAuthManager::InitAllCSAuthManager()
{
	UINT32 uReturn = InitCSAuth3("NP/");
	if( uReturn != ERROR_SUCCESS )
	{
		COLOR_MESSAGE(COLOR_YELLOW,"\nCSAuth ����ʧ��");
		return false;
	}
	else
	{
		//���ø��»ص�����
		SetCallbackFunction( CALLBACK_LOG, (PVOID)CS3LogCallback );
		SetCallbackFunction( CALLBACK_UPDATE, (PVOID)CS3UpdateInfoCallback );
		//���������̨ CSAuth�����ɹ�
		COLOR_MESSAGE(COLOR_YELLOW,"\nCSAuth �����ɹ�");
		return true;
	}
}
void CSAuthManager::CloseAllCSAuthManager()
{
	CloseCSAuth3();
}
bool CSAuthManager::InitPlayerCSAuth(GamePlayer* pPlayer)
{
	//��ʼ�����
	if(g_Cfg.IsOpenCSAuth && CHARACTERSERVERID != g_Cfg.dwServerID)
	{
		UINT32 uReturn  = csa.Init(true);
		if (uReturn == 0)
		{
			return SendCheckMsgToClient(pPlayer);
		}
		else
		{
			COLOR_MESSAGE(COLOR_YELLOW,"\nCSAuth �������ʧ�� ���ID:%d",pPlayer->GetDBCharacterID());
			return false;
		}
	}
}
void CSAuthManager::ClosePlayerCSAuth()
{
	if(g_Cfg.IsOpenCSAuth && CHARACTERSERVERID != g_Cfg.dwServerID)
	{
		csa.Close();
	}
}
bool CSAuthManager::SendCheckMsgToClient(GamePlayer* pPlayer)
{
	if(!g_Cfg.IsOpenCSAuth ||  CHARACTERSERVERID == g_Cfg.dwServerID || !pPlayer || pPlayer->GetDBCharacterID() == 0)
		return false;
	if(HQ_TimeGetTime() - m_NextUpdateTime >= 180000 || m_NextUpdateTime == 0)
		m_NextUpdateTime = HQ_TimeGetTime();
	else
		return true;//ʱ�䲻�� �޷�����
	UINT32 uReturnedPacketSize = 0;
	UINT32 uReturn = csa.Get( &uReturnedPacketSize );
	if (uReturn >= 3000)
	{
		// �Ͽ��������
		csa.Close();
		// �ߵ����
		pPlayer->ExitWorld(__FUNCTION__, __FILE__, __LINE__,ET_SystemBeKick);
		COLOR_MESSAGE(COLOR_YELLOW,"\nCSAuth ��֤ʧ�� Get �ߵ���� ���ID:%d",pPlayer->GetDBCharacterID());
		return false;
	} 
	//���͵��ͻ���
	MsgCheckCSAuthReq msg;
	msg.PlayerID = pPlayer->GetDBCharacterID();
	memcpy(msg.packet,csa.packet,uReturnedPacketSize);
	msg.size = uReturnedPacketSize;
	GettheServer().SendMsgToSingle( &msg,pPlayer);
	return true;
}
bool CSAuthManager::ReviceCheckMsgByClient(MsgCheckCSAuthAck* pMsg,GamePlayer* pPlayer)
{
	if(!g_Cfg.IsOpenCSAuth  ||  CHARACTERSERVERID == g_Cfg.dwServerID)
		return false;
	if(!pMsg || !pPlayer || pPlayer->GetDBCharacterID() != pMsg->PlayerID)
		return false;
	//���տͻ��˷�����������	
	memcpy(csa.packet,pMsg->packet,pMsg->size);
	//����Ӧ���ݱ�ֵ�Ƿ�����
	UINT32 uReturn = csa.Check(pMsg->size);
	if( uReturn >= 3000)
	{
		// �Ͽ��������
		csa.Close();
		// �ߵ����
		pPlayer->ExitWorld(__FUNCTION__, __FILE__, __LINE__,ET_SystemBeKick);
		COLOR_MESSAGE(COLOR_YELLOW,"\nCSAuth ��֤ʧ�� Check �ߵ���� ���ID:%d",pPlayer->GetDBCharacterID());
		return false;
	}
	else
	{
		return true;
	}
}
void CSAuthManager::OnUpdate(GamePlayer* pPlayer)
{
	//ÿ�����ӵ��ô�
	if(!g_Cfg.IsOpenCSAuth  ||  CHARACTERSERVERID == g_Cfg.dwServerID)
		return;
	if(!pPlayer)
		return;
	SendCheckMsgToClient(pPlayer);
}
#endif