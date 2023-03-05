#ifndef __GAMERELATIONHANDLE_H__
#define __GAMERELATIONHANDLE_H__


long OnProcessRelationMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );


virtual void _OnCS2GSRelationList( NetClient* pNetClient, CS2GSRelationList* pMessage );
virtual void _OnCS2GSRelationOnLine( NetClient* pNetClient, CS2GSRelationOnLine* pMessage );
virtual void _OnCS2GSRelationOutLine( NetClient* pNetClient, CS2GSRelationOutLine* pMessage );
virtual void _OnCS2GSAddRelationAttribute( NetClient* pNetClient, CS2GSAddRelationAttribute* pMessage );
virtual void _OnCS2GSUpdateRelationAttribute( NetClient* pNetClient, CS2GSUpdateRelationAttribute* pMessage );
virtual void _OnCS2GSRemoveRelationAck( NetClient* pNetClient, CS2GSRemoveRelationAck* pMessage );
virtual void _OnCS2GSAddRelationResult( NetClient* pNetClient, CS2GSAddRelationResult* pMessage );
virtual void _OnCS2GSMsgAddFriendlyTimeList( NetClient* pNetClient, CS2GSMsgAddFriendlyTimeList* pMessage );
virtual void _OnUpdateAddFriendlyTime( NetClient* pNetClient, GS2CSUpdateAddFriendlyTime* pMessage );
virtual void _OnCS2GSMsgReceiveQuestTimeList( NetClient* pNetClient, CS2GSMsgReceiveQuestTimeList* pMessage );
virtual void _OnUpdateReceiveQuestTime( NetClient* pNetClient, GS2CSUpdateReceiveQuestTime* pMessage );
virtual void _OnCS2GSStudentLevelUp( NetClient* pNetClient, CS2GSStudentLevelUp* pMessage );
virtual void _OnCS2GSRelationDataSendSuccess( NetClient* pNetClient, CS2GSRelationDataSendSuccess* pMessage );
virtual void _OnCS2GSRelationGroupNameChange( NetClient* pNetClient, CS2GSRelationGroupNameChange* pMessage );
virtual void _OnCS2GSUpdateRelationData( NetClient* pNetClient, CS2GSUpdateRelationData* pMessage );
virtual void _OnCS2GSUpdatePersonalInfo( NetClient* pNetClient, CS2GSUpdatePersonalInfo* pMessage );
virtual void _OnCS2GSRelationUpdateName( NetClient* pNetClient, CS2GSRelationUpdateName* pMessage );
#endif