#include "CenterServerNetEvent.h"
#include "CampBattleManager.h"
#include "CampGuildUnionBattleManager.h"
#include "CampGuildUnionBattleConfig.h"
#include "CampBattleControl.h"
#include "GameTimeHandleManager.h"
#include "GlobalDBManager.h"

long CenterServerNetEvent::OnProcessGlobalDBMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    MESSAGE_MAPPING_BEGIN
		MESSAGE_HANDLE( CS2GS_UPDATEGLOBALDBACK, CS2GSUpdateGlobalDBAck, _OnCS2GSUpdateGlobalDBAck);
		MESSAGE_HANDLE( CS2GS_LOADINGLOBALDBACK, CS2GSLoadGlobalDBAck, _OnCS2GSLoadGlobalDBAck);
    MESSAGE_MAPPING_END
    return ER_Success;
}
void CenterServerNetEvent::_OnCS2GSUpdateGlobalDBAck(NetClient* pNetClient,CS2GSUpdateGlobalDBAck* pMessage)
{
	//�޸�GameServer������
	if(!pMessage) return;
	theGameGlobalDBManager.UpdateGlobalDBData(pMessage->uchUpdateType,pMessage->Index,pMessage->n64Value);
}
void CenterServerNetEvent::_OnCS2GSLoadGlobalDBAck( NetClient* pNetClient, CS2GSLoadGlobalDBAck* pMessage )
{
	//�������������������������
	if(!pMessage) return;
	theGameGlobalDBManager.LoadGlobalDB(pMessage->info);
	theGameGlobalDBManager.SetLoadSuccess(true);
	//��CenterServer��ȡ���ݺ�
	//1.Battle
	CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry(CampDefine::BattleTypeGuildUnion);
	if ( pManager != NULL && pManager->GetBattleType() == CampDefine::BattleTypeGuildUnion)
	{ 
		CampGuildUnionBattleManager * pGuildUnionBattle = static_cast<CampGuildUnionBattleManager*>(pManager);
		pGuildUnionBattle->SetBattleConfig(&theCampGuildUnionBattleConfig.GetGuildBattleSumConfig(theGameGlobalDBManager.GetBattleSum()));
	}
	//2.MapCountryID Ұ���ͼ��ID ManagerӦ��������Init
	

	//3.4. ���ʱ���״̬���Ѿ����������
	theGameTimeHandleManager.SetInit();
}