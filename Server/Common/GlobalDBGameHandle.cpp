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
	//修改GameServer的数据
	if(!pMessage) return;
	theGameGlobalDBManager.UpdateGlobalDBData(pMessage->uchUpdateType,pMessage->Index,pMessage->n64Value);
}
void CenterServerNetEvent::_OnCS2GSLoadGlobalDBAck( NetClient* pNetClient, CS2GSLoadGlobalDBAck* pMessage )
{
	//加载中央服务器发送来的数据
	if(!pMessage) return;
	theGameGlobalDBManager.LoadGlobalDB(pMessage->info);
	theGameGlobalDBManager.SetLoadSuccess(true);
	//从CenterServer读取数据后
	//1.Battle
	CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry(CampDefine::BattleTypeGuildUnion);
	if ( pManager != NULL && pManager->GetBattleType() == CampDefine::BattleTypeGuildUnion)
	{ 
		CampGuildUnionBattleManager * pGuildUnionBattle = static_cast<CampGuildUnionBattleManager*>(pManager);
		pGuildUnionBattle->SetBattleConfig(&theCampGuildUnionBattleConfig.GetGuildBattleSumConfig(theGameGlobalDBManager.GetBattleSum()));
	}
	//2.MapCountryID 野外地图的ID Manager应该在这里Init
	

	//3.4. 标记时间和状态都已经接收完毕了
	theGameTimeHandleManager.SetInit();
}