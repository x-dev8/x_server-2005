#ifndef __CENTERRELATIONHANDLE_H__
#define __CENTERRELATIONHANDLE_H__


long OnProcessRelationMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnGS2CSAddRelationAttribute( NetClient* pNetClient, GS2CSAddRelationAttribute* pMessage );
virtual void _OnGS2CSUpdateRelationAttribute( NetClient* pNetClient, GS2CSUpdateRelationAttribute* pMessage );
virtual void _OnGS2CSAddRelationReq( NetClient* pNetClient, GS2CSAddRelationReq* pMessage );
virtual void _OnGS2CSAddRelationAck( NetClient* pNetClient, GS2CSAddRelationAck* pMessage );
virtual void _OnGS2CSRemoveRelationReq( NetClient* pNetClient, GS2CSRemoveRelationReq* pMessage );
virtual void _OnGS2CSUpdateAddFriendlyTime( NetClient* pNetClient, GS2CSUpdateAddFriendlyTime* pMessage   );
virtual void _OnGS2CSUpdateReceiveQuestTime( NetClient* pNetClient, GS2CSUpdateReceiveQuestTime* pMessage  );
virtual void _OnGS2CSQueryAttributeReq( NetClient* pNetClient, GS2CSQueryAttributeReq* pMessage );
virtual void _OnGS2CSStudentLevelUp( NetClient* pNetClient, GS2CSStudentLevelUp* pMessage );
virtual void _OnGS2CSResetStudentReward( NetClient* pNetClient, GS2CSResetStudentReward* pMessage );
virtual void _OnGS2CSRelationGroupChangeNameReq( NetClient* pNetClient, GS2CSRelationGroupNameChangeReq* pMessage );
virtual void _OnGS2CSRelationDataChangeReq( NetClient* pNetClient, GS2CSRelationDataChangeReq* pMessage );
virtual void _OnGS2CSUpdatePersonalInfo( NetClient* pNetClient, GS2CSUpdatePersonalInfo* pMessage );
virtual void _OnGS2CSFindPerson( NetClient* pNetClient, GS2CSFindPersonReq* pMessage );
virtual void _OnGS2CSRelationUpdateName( NetClient* pNetClient, GS2CSRelationUpdateName* pMessage );

#endif