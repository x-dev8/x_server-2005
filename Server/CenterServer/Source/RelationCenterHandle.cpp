#include "NetEvent.h"
#include "GameServerManager.h"
#include "RelationManager.h"
#include "MySqlCommunication.h"
#include "XmlStringLanguage.h"
long NetEvent::OnProcessRelationMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    MESSAGE_MAPPING_BEGIN
        MESSAGE_HANDLE( GS2CS_ADDRELATIONATTRIBUTE, GS2CSAddRelationAttribute, _OnGS2CSAddRelationAttribute );
        MESSAGE_HANDLE( GS2CS_UPDATERELATIONATTRIBUTE, GS2CSUpdateRelationAttribute, _OnGS2CSUpdateRelationAttribute );
        MESSAGE_HANDLE( GS2CS_ADDRELAITONREQ, GS2CSAddRelationReq, _OnGS2CSAddRelationReq );
        MESSAGE_HANDLE( GS2CS_DELETERELATIONREQ, GS2CSRemoveRelationReq, _OnGS2CSRemoveRelationReq );
        MESSAGE_HANDLE( GS2CS_UPDATEADDFRIENDLYTIME, GS2CSUpdateAddFriendlyTime, _OnGS2CSUpdateAddFriendlyTime );
        MESSAGE_HANDLE( GS2CS_UPDATERECEIVEQUESTTIME, GS2CSUpdateReceiveQuestTime, _OnGS2CSUpdateReceiveQuestTime );    
        MESSAGE_HANDLE( GS2CS_QUERYATTRIBUTEREQ, GS2CSQueryAttributeReq, _OnGS2CSQueryAttributeReq );   
        MESSAGE_HANDLE( GS2CS_STUDENTLEVELUP, GS2CSStudentLevelUp, _OnGS2CSStudentLevelUp );   
        MESSAGE_HANDLE( GS2CS_RESETSTUDENTREWARD, GS2CSResetStudentReward, _OnGS2CSResetStudentReward );   
        MESSAGE_HANDLE( GS2CS_ADDRELATIONACK, GS2CSAddRelationAck, _OnGS2CSAddRelationAck ); 
        MESSAGE_HANDLE( GS2CS_RELATIONGROUPNAMECHANGEREQ, GS2CSRelationGroupNameChangeReq, _OnGS2CSRelationGroupChangeNameReq ); 
        MESSAGE_HANDLE( GS2CS_RELATIONDATACHANGEREQ, GS2CSRelationDataChangeReq, _OnGS2CSRelationDataChangeReq );
		MESSAGE_HANDLE( GS2CS_UPDATEPERSONALINFOREQ, GS2CSUpdatePersonalInfo, _OnGS2CSUpdatePersonalInfo );    
		MESSAGE_HANDLE( GS2CS_FINDBYCONDITION, GS2CSFindPersonReq, _OnGS2CSFindPerson );

		MESSAGE_HANDLE( GS2CS_RELATIONUPDATENAME, GS2CSRelationUpdateName, _OnGS2CSRelationUpdateName );

    MESSAGE_MAPPING_END

    return ER_Success;
}

void NetEvent::_OnGS2CSAddRelationAttribute( NetClient* pNetClient, GS2CSAddRelationAttribute* pMessage )
{
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pMessage->xAttribute.GetID(), true );
    if ( pRelation == NULL )
    { return; }

    pRelation->SetRelationAttribute( pMessage->xAttribute );
    pRelation->SendAddAttributeToDatabase();

    // 更新名字关联
    theCenterRelationManager.AddPlayerNameID( pRelation );

    // 同步给所有服务器
    CS2GSAddRelationAttribute xReq;
    xReq.xAttribute = *pRelation;
    theGameServerManager.SendMessageToGameServers( &xReq );
}

void NetEvent::_OnGS2CSUpdateRelationAttribute( NetClient* pNetClient, GS2CSUpdateRelationAttribute* pMessage )
{
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nPlayerID );
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

void NetEvent::_OnGS2CSUpdatePersonalInfo( NetClient* pNetClient, GS2CSUpdatePersonalInfo* pMessage )
{
	CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nPlayerID );
	if ( pRelation == NULL )
	{ return; }
	pRelation->UpdatePersonalInfo( pMessage->xPersonalInfo );
}

void NetEvent::_OnGS2CSAddRelationReq( NetClient* pNetClient, GS2CSAddRelationReq* pMessage )
{
    CenterRelation* pReqRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nReqID );
    CenterRelation* pAckRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nAckID );
    if ( pReqRelation == NULL || pAckRelation == NULL)
    { return; }

    if ( !pAckRelation->GetOnLine() )
    { return; }

    if ( pReqRelation->CheckCanAddRelation( pMessage->nAckID, pMessage->stRelation ) != RelationDefine::CanAddRelation )
    { return; }

    // 不是2级关系, 不用对方确认, 直接加上去, 
    if ( !RelationData::IsHigherRelation( pMessage->stRelation ) )
    {
        // 如果是加仇人, 判断数量, 超过最大数的话, 顶掉一个
        if ( pMessage->stRelation == RelationDefine::Vendetta )
        {  
            if ( !pReqRelation->CheckVendettaRelationCount() )
            { return; } // 不能顶掉仇人, 就不添加
        }
    
        if ( pReqRelation->IsEmptyGroup( pMessage->uchGroupID ) )
        { pMessage->uchGroupID = 0; }

        RelationDataToServer xData;
        xData.SetID( pMessage->nAckID );
        xData.SetRelation( pMessage->stRelation );
        xData.SetGroupID( pMessage->uchGroupID );
        pReqRelation->AddRelation( xData, RelationDefine::SendToClient );
        return;
    }

    // 如果是2级关系, 需要判断对方, 
    unsigned short ustRelation = pMessage->stRelation;
    switch ( ustRelation )
    {
    case RelationDefine::Teacher:
        ustRelation = RelationDefine::Student;
        break;
    case RelationDefine::Student:
        ustRelation = RelationDefine::Teacher;
        break;
    }

    // 判断对方能否添加响应关系
    if ( pAckRelation->CheckCanAddRelation( pMessage->nReqID, ustRelation ) != RelationDefine::CanAddRelation )
    { return; }

    // 发送邀请消息
    MsgInviteRelationReq xReq;
    xReq.stRelation = pMessage->stRelation;
    xReq.dwReqID    = pReqRelation->GetID();
    HelperFunc::SafeNCpy( xReq.szReqName, pReqRelation->GetName(), sizeof( xReq.szReqName ) );
    theGameServerManager.SendMsgToSingleRemote( RelationDefine::InitID, &xReq, pAckRelation->GetID() );

    // 添加一个邀请记录
    RelationInvite xInvite;
    xInvite.dwTargetID = pAckRelation->GetID();
    xInvite.stRelation = pMessage->stRelation;
    xInvite.StartTimer( HQ_TimeGetTime() );
    theCenterRelationManager.AddRelationInvite( pReqRelation->GetID(), xInvite );
}

void NetEvent::_OnGS2CSAddRelationAck( NetClient* pNetClient, GS2CSAddRelationAck* pMessage )
{
    RelationInvite* pInvite = theCenterRelationManager.GetRelationInvite( pMessage->nReqID, pMessage->nAckID );
    if ( pInvite == NULL )  // 邀请记录已经过期了
    { return; } 

    RelationInvite xInvite = *pInvite;
    theCenterRelationManager.RemoveRelationInvite( pMessage->nReqID, pMessage->nAckID );    // 删除记录

    CenterRelation* pReqRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nReqID );
    CenterRelation* pAckRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nAckID );
    if ( pReqRelation == NULL || pAckRelation == NULL )
    { return; }

    if ( !pMessage->bAgreeAdd ) // 对方不同意
    {
        MsgAddRelationAck xAck;
        xAck.uchResult = RelationDefine::TargetNotAgree;
        xAck.xRelationData.SetRelation( pMessage->ustRelation );
        xAck.xRelationData.SetName( pAckRelation->GetName() );
        theGameServerManager.SendMsgToSingleRemote( RelationDefine::InitID, &xAck, pReqRelation->GetID() );

        return;
    }

    // 判断能否添加关系
    if ( pReqRelation->CheckCanAddRelation( pAckRelation->GetID(), xInvite.stRelation ) != RelationDefine::CanAddRelation )
    { return; }

    // 如果是2级关系, 需要判断对方, 
    unsigned short ustRelation = xInvite.stRelation;
    switch ( ustRelation )
    {
    case RelationDefine::Teacher:
        ustRelation = RelationDefine::Student;
        break;
    case RelationDefine::Student:
        ustRelation = RelationDefine::Teacher;
        break;
    }

    // 判断对方能否添加关系
    if ( pAckRelation->CheckCanAddRelation( pReqRelation->GetID(), ustRelation ) != RelationDefine::CanAddRelation )
    { return; }

    RelationDataToServer xData;

    // 申请方添加关系
    xData.SetID( pAckRelation->GetID() );
    xData.SetRelation( xInvite.stRelation );
    pReqRelation->AddRelation( xData, RelationDefine::SendToClient );

    // 被邀请方接受关系
    xData.SetID( pReqRelation->GetID() );
    xData.SetRelation( ustRelation );
    pAckRelation->AddRelation( xData, RelationDefine::SendToClient );
	
	if(ustRelation == RelationDefine::Marriage)
	{
		//如果是夫妻关系 发送全服公告
		char szText[512] = {0};
		sprintf_s( szText,sizeof(szText)-1,theXmlString.GetString( eText_AddRelationMarriageInfo),pReqRelation->GetName(),pAckRelation->GetName());
		//字符串组织完毕后 发送出去
		MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
		xChat.SetString( szText );
		theGameServerManager.SendMsgToWorldUser( &xChat );
	}
}

void NetEvent::_OnGS2CSRemoveRelationReq( NetClient* pNetClient, GS2CSRemoveRelationReq* pMessage )
{
    CenterRelation* pReqRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nReqID );
    if ( pReqRelation == NULL )
    { return; }

    pReqRelation->RemoveRelation( pMessage->nAckID, pMessage->stRelation );

    // 如果是2级关系 对方也要删除关系
    if ( RelationData::IsHigherRelation( pMessage->stRelation ) )       
    {
        CenterRelation* pAckRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nAckID );
        if ( pAckRelation == NULL )
        { return; }

        switch( pMessage->stRelation )
        {
        case RelationDefine::Student:
            pMessage->stRelation = RelationDefine::Teacher;
            break;
        case RelationDefine::Teacher:
            pMessage->stRelation = RelationDefine::Student;
            break;
        default:
            break;
        }

        pAckRelation->RemoveRelation( pMessage->nReqID, pMessage->stRelation );
    }
}

void NetEvent::_OnGS2CSUpdateAddFriendlyTime( NetClient* pNetClient, GS2CSUpdateAddFriendlyTime* pMessage )
{
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pMessage->dwSelfID );
    if ( pRelation == NULL )
    { return; }

    pRelation->UpdateAddFriendlyTime( pMessage->dwPlayerID, pMessage->bClear );
    pRelation->SendAddFriendlyTimeMessage( pMessage->dwPlayerID, pMessage->bClear );
}

void NetEvent::_OnGS2CSUpdateReceiveQuestTime( NetClient* pNetClient, GS2CSUpdateReceiveQuestTime* pMessage )
{
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pMessage->dwSelfID );
    if ( pRelation == NULL )
    { return; }

    pRelation->UpdateReceiveQuestTime( pMessage->dwPlayerID, pMessage->bClear );
    pRelation->SendReceiveQuestTimeMessage( pMessage->dwPlayerID, pMessage->bClear );
}

void NetEvent::_OnGS2CSQueryAttributeReq( NetClient* pNetClient, GS2CSQueryAttributeReq* pMessage )
{
    theMysqlCommunication.PushReqMessage( pMessage, 0 );
}

void NetEvent::_OnGS2CSFindPerson( NetClient* pNetClient, GS2CSFindPersonReq* pMessage )
{
	theMysqlCommunication.PushReqMessage( pMessage, 0 );
}

void NetEvent::_OnGS2CSStudentLevelUp( NetClient* pNetClient, GS2CSStudentLevelUp* pMessage )
{
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nPlayerID );
    if ( pRelation == NULL )
    { return; }

    pRelation->ProcessStudentLevelUp( pMessage->nPlayerID, pMessage->nLevel );
}

void NetEvent::_OnGS2CSResetStudentReward( NetClient* pNetClient, GS2CSResetStudentReward* pMessage )
{
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nPlayerID );
    if ( pRelation == NULL )
    { return; }

    int nValue = 0;
    pRelation->UpdateRelationAttribute( RelationDefine::UpdateRewardExp, nValue );
    pRelation->UpdateRelationAttribute( RelationDefine::UpdateRewardPrestige, nValue );
}

void NetEvent::_OnGS2CSRelationGroupChangeNameReq( NetClient* pNetClient, GS2CSRelationGroupNameChangeReq* pMessage )
{
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nPlayerID );
    if ( pRelation == NULL )
    { return; }

    pRelation->ProcessRelationGroupNameChange( pMessage->uchGroupID, pMessage->szName );
}

void NetEvent::_OnGS2CSRelationDataChangeReq( NetClient* pNetClient, GS2CSRelationDataChangeReq* pMessage )
{
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nPlayerID );
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
void NetEvent::_OnGS2CSRelationUpdateName( NetClient* pNetClient, GS2CSRelationUpdateName* pMessage )
{
	//修改关系数据里的玩家的名称 并且通知所有在线的有关系的玩家
	CenterRelation* pRelation =  theCenterRelationManager.GetPlayerRelation(pMessage->PlayerID);
	if(!pRelation)
		return;
	theCenterRelationManager.AddPlayerNameID(pRelation);
	pRelation->UpdateRelationAttribute( RelationDefine::UpdateName,pMessage->szName);

	CS2GSRelationUpdateName msg;
	msg.PlayerID = pMessage->PlayerID;
	strcpy_s(msg.szName,sizeof(msg.szName)-1,pMessage->szName);
    theGameServerManager.SendMessageToGameServers( &msg );
}