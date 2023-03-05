#include "CenterServerNetEvent.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "RunStatus.h"

long CenterServerNetEvent::OnProcessRelationMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    MESSAGE_MAPPING_BEGIN
        MESSAGE_HANDLE_NOTCHECK( CS2GS_RELATIONLIST, CS2GSRelationList, _OnCS2GSRelationList );
        MESSAGE_HANDLE( CS2GS_RELATIONDATASENDSUCCESS, CS2GSRelationDataSendSuccess, _OnCS2GSRelationDataSendSuccess );      
        MESSAGE_HANDLE( CS2GS_RELATIONONLINE, CS2GSRelationOnLine, _OnCS2GSRelationOnLine );
        MESSAGE_HANDLE( CS2GS_RELATIONOUTLINE, CS2GSRelationOutLine, _OnCS2GSRelationOutLine );
        MESSAGE_HANDLE( CS2GS_ADDRELATIONATTRIBUTE, CS2GSAddRelationAttribute, _OnCS2GSAddRelationAttribute );
        MESSAGE_HANDLE( CS2GS_UPDATERELATIONATTRIBUTE, CS2GSUpdateRelationAttribute, _OnCS2GSUpdateRelationAttribute );
        MESSAGE_HANDLE( CS2GS_DELETERELATIONACK, CS2GSRemoveRelationAck, _OnCS2GSRemoveRelationAck );
        MESSAGE_HANDLE( CS2GS_ADDRELATIONRESULT, CS2GSAddRelationResult, _OnCS2GSAddRelationResult );
        MESSAGE_HANDLE( CS2GS_ADDFRIENDLYTIMELIST, CS2GSMsgAddFriendlyTimeList, _OnCS2GSMsgAddFriendlyTimeList );
        MESSAGE_HANDLE( GS2CS_UPDATEADDFRIENDLYTIME, GS2CSUpdateAddFriendlyTime, _OnUpdateAddFriendlyTime );
        MESSAGE_HANDLE( CS2GS_RECEIVEQUESTTIMELIST, CS2GSMsgReceiveQuestTimeList, _OnCS2GSMsgReceiveQuestTimeList );
        MESSAGE_HANDLE( GS2CS_UPDATERECEIVEQUESTTIME, GS2CSUpdateReceiveQuestTime, _OnUpdateReceiveQuestTime );        
        MESSAGE_HANDLE( CS2GS_STUDENTLEVELUP, CS2GSStudentLevelUp, _OnCS2GSStudentLevelUp );    
        MESSAGE_HANDLE( CS2GS_RELATIONGROUPNAMECHANGE, CS2GSRelationGroupNameChange, _OnCS2GSRelationGroupNameChange );
        MESSAGE_HANDLE( CS2GS_UPDATERELATIONDATA, CS2GSUpdateRelationData, _OnCS2GSUpdateRelationData );
		MESSAGE_HANDLE( CS2GS_UPDATEPERSONALINFOREQ, CS2GSUpdatePersonalInfo, _OnCS2GSUpdatePersonalInfo );      
		MESSAGE_HANDLE( CS2GS_RELATIONUPDATENAME, CS2GSRelationUpdateName, _OnCS2GSRelationUpdateName );      
        
    MESSAGE_MAPPING_END

    return ER_Success;
}

void CenterServerNetEvent::_OnCS2GSRelationList( NetClient* pNetClient, CS2GSRelationList* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->xAttribute.GetID(), true );
    if ( pRelation == NULL )
    { return; }

    pRelation->SetRelationAttributeToServer( pMessage->xAttribute );
    for ( int i = 0; i < pMessage->ustCount; ++i )
    {
        pRelation->AddRelation( pMessage->xData[i], RelationDefine::NotSendToClient );
    }

    theGameRelationManager.AddPlayerNameID( pRelation );
    // 这里处理一下所有加我为好友或者仇人的列表
    theGameRelationManager.ProcessRelationToMe( pRelation );
}

void CenterServerNetEvent::_OnCS2GSRelationDataSendSuccess( NetClient* pNetClient, CS2GSRelationDataSendSuccess* pMessage )
{
	theGameRelationManager.SetLoadSuccess(true);
}

void CenterServerNetEvent::_OnCS2GSRelationOnLine( NetClient* pNetClient, CS2GSRelationOnLine* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->nPlayerID );
    if ( pRelation == NULL )
    { return; }

    pRelation->SendOnLineMessage();
}

void CenterServerNetEvent::_OnCS2GSRelationOutLine( NetClient* pNetClient, CS2GSRelationOutLine* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->nPlayerID );
    if ( pRelation == NULL )
    { return; }

    pRelation->ProcessExitWorld();

    // 删除注册列表
    theGameRelationManager.RemoveRegisterID( RelationDefine::InitRelation, pMessage->nPlayerID );
}

void CenterServerNetEvent::_OnCS2GSAddRelationAttribute( NetClient* pNetClient, CS2GSAddRelationAttribute* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->xAttribute.GetID(), true );
    if ( pRelation == NULL )
    { return; }

    pRelation->SetRelationAttributeToServer( pMessage->xAttribute );

    // 更新名字关联
    theGameRelationManager.AddPlayerNameID( pRelation );
}

void CenterServerNetEvent::_OnCS2GSUpdateRelationAttribute( NetClient* pNetClient, CS2GSUpdateRelationAttribute* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->nPlayerID );
    if ( pRelation == NULL )
    { return; }

    switch ( pMessage->uchType )
    {
    case RelationDefine::UpdateName:
    case RelationDefine::UpdateSignature:
        pRelation->UpdateRelationAttribute( pMessage->uchType, pMessage->xAttribute.szValue );
        break;
    default:
        pRelation->UpdateRelationAttribute( pMessage->uchType, pMessage->xAttribute.n64Value );
        break;
    }
}

void CenterServerNetEvent::_OnCS2GSUpdatePersonalInfo( NetClient* pNetClient, CS2GSUpdatePersonalInfo* pMessage )
{
	GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->nPlayerID );
	if ( pRelation == NULL )
	{ return; }

	pRelation->UpdatePersonalInfo( pMessage->xPersonalInfo );
}

void CenterServerNetEvent::_OnCS2GSRemoveRelationAck( NetClient* pNetClient, CS2GSRemoveRelationAck* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->nReqID );
    if ( pRelation == NULL )
    { return; }

    pRelation->RemoveRelation( pMessage->nAckID, pMessage->stRelation );
}

void CenterServerNetEvent::_OnCS2GSAddRelationResult( NetClient* pNetClient, CS2GSAddRelationResult* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->nReqID );
    if ( pRelation == NULL )
    { return; }

    pRelation->AddRelation( pMessage->xData, RelationDefine::SendToClient );
}


void CenterServerNetEvent::_OnCS2GSMsgAddFriendlyTimeList( NetClient* pNetClient, CS2GSMsgAddFriendlyTimeList* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->dwSelfID );
    if ( pRelation == NULL )
    { return; }

    pRelation->ClearAddFriendlyTime();
    for ( int i = 0; i < pMessage->nCount; ++i )
    {
        pRelation->UpdateAddFriendlyTime( pMessage->dwPlayerID[i], false );    
    }
}

void CenterServerNetEvent::_OnUpdateAddFriendlyTime( NetClient* pNetClient, GS2CSUpdateAddFriendlyTime* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->dwSelfID );
    if ( pRelation == NULL )
    { return; }

    pRelation->UpdateAddFriendlyTime( pMessage->dwPlayerID, pMessage->bClear );
}

void CenterServerNetEvent::_OnCS2GSMsgReceiveQuestTimeList( NetClient* pNetClient, CS2GSMsgReceiveQuestTimeList* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->dwSelfID );
    if ( pRelation == NULL )
    { return; }

    pRelation->ClearReceiveQuestTime();
    for ( int i = 0; i < pMessage->nCount; ++i )
    {
        pRelation->UpdateReceiveQuestTime( pMessage->dwPlayerID[i], false );    
    }
}

void CenterServerNetEvent::_OnUpdateReceiveQuestTime( NetClient* pNetClient, GS2CSUpdateReceiveQuestTime* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->dwSelfID );
    if ( pRelation == NULL )
    { return; }

    pRelation->UpdateReceiveQuestTime( pMessage->dwPlayerID, pMessage->bClear );
}

void CenterServerNetEvent::_OnCS2GSStudentLevelUp( NetClient* pNetClient, CS2GSStudentLevelUp* pMessage )
{
    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->nPlayerID );
    if ( pPlayer == NULL )
    { return; }

    pPlayer->ProcessStudentLevelUp( pMessage->nStudentID, pMessage->bIsStudent, pMessage->nRewardExp, pMessage->nRewardMasterValue );
}

void CenterServerNetEvent::_OnCS2GSRelationGroupNameChange( NetClient* pNetClient, CS2GSRelationGroupNameChange* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->nPlayerID );
    if ( pRelation == NULL )
    { return; }

    pRelation->ProcessRelationGroupNameChange( pMessage->uchGroupID, pMessage->szName );
}

void CenterServerNetEvent::_OnCS2GSUpdateRelationData( NetClient* pNetClient, CS2GSUpdateRelationData* pMessage )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->nPlayerID );
    if ( pRelation == NULL )
    { return; }

    switch ( pMessage->uchType )
    {
    case RelationDefine::UpdateRemark:
        pRelation->UpdateRelationData( pMessage->nTargetID, pMessage->uchType, pMessage->xData.szValue );
        break;
    default:
        pRelation->UpdateRelationData( pMessage->nTargetID, pMessage->uchType, pMessage->xData.nValue );
        break;
    }
}
void CenterServerNetEvent::_OnCS2GSRelationUpdateName( NetClient* pNetClient, CS2GSRelationUpdateName* pMessage )
{
	GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pMessage->PlayerID );
	if(!pRelation)
		return;
	pRelation->UpdateRelationAttribute( RelationDefine::UpdateName,pMessage->szName);
	theGameRelationManager.AddPlayerNameID(pRelation);
	//发送到需要发送的客户端去
	MsgRelationUpdateNameAck msg;
	msg.PlayerID = pMessage->PlayerID;
	strcpy_s(msg.szName,sizeof(msg.szName)-1,pMessage->szName);
	pRelation->SendRelationMessage(&msg);
}