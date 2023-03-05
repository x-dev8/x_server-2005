
/************************************************************************
            Include in CenterServerNetEvent.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/

long OnProcessGuildMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnCS2GSCreateGuildAck( NetClient* pNetClient, CS2GSCreateGuildAck* pMessage );
virtual void _OnCS2GSLeaveGuildAck( NetClient* pNetClient, CS2GSLeaveGuildAck* pMessage );
virtual void _OnCS2GSJoinGuildAck( NetClient* pNetClient, CS2GSJoinGuildAck* pMessage );
virtual void _OnCS2GSDisbandGuildAck( NetClient* pNetClient, CS2GSDisbandGuildAck* pMessage );
virtual void _OnCS2GSMemberDataUpdate( NetClient* pNetClient, CS2GSMemberDataUpdate* pMessage );
virtual void _OnCS2GSGuildDataUpdate( NetClient* pNetClient, CS2GSGuildDataUpdate* pMessage );
virtual void _OnCS2GSGuildNoticeChangeAck( NetClient* pNetClient, CS2GSGuildNoticeChangeAck* pMessage );
virtual void _OnCS2GSGuildAimChangeAck( NetClient* pNetClient, CS2GSGuildAimChangeAck* pMessage );
virtual void _OnCS2GSGuildFamilyChange( NetClient* pNetClient, CS2GSGuildFamilyChange* pMessage );
virtual void _OnCS2GSGuildDataList( NetClient* pNetClient, CS2GSGuildDataList* pMessage );
virtual void _OnCS2GSGuildDataSendSuccess( NetClient* pNetClient, CS2GSGuildDataSendSuccess* pMessage );
virtual void _OnCS2GSGuildDelateRequestReq( NetClient* pNetClient, CS2GSGuildDelateRequestReq* pMessage );
virtual void _OnCS2GSGuildDelateResult( NetClient* pNetClient, CS2GSGuildDelateResult* pMessage );
virtual void _OnCS2GSGuildDonateRequestReq( NetClient* pNetClient, CS2GSGuildDonateRequestReq* pMessage );
virtual void _OnCS2GSGuildDonateStop( NetClient* pNetClient, CS2GSGuildDonateStop* pMessage );
virtual void _OnCS2GSGuildQuestReleaseStatus( NetClient* pNetClient, CS2GSGuildQuestReleaseStatus* pMessage );
virtual void _OnCS2GSGuildClearMemberActivity( NetClient* pNetClient, CS2GSGuildClearMemberActivity* pMessage );
virtual void _OnCS2GSGuildMessage( NetClient* pNetClient, CS2GSGuildMessage* pMessage );
virtual void _OnCS2GSGuildConveneReq( NetClient* pNetClient, CS2GSGuildConveneReq* pMessage );
virtual void _OnCS2GSGuildConveneStop( NetClient* pNetClient, CS2GSGuildConveneStop* pMessage );
virtual void _OnCS2GSPlayerLvUpToThirtyReq( NetClient* pNetClient, GS2CSPlayerLvUpToThirtyMessage* pMessage );
virtual void _OnCS2GSMissionNotEnuoughReq( NetClient* pNetClient, CS2GSMissionNotEnuoughMessage* pMessage );
virtual void _OnCS2GSChangeGuildNameAck( NetClient* pNetClient, CS2GSChangeGuildNameAck* pMessage );
virtual void _OnCS2GSGuildMemberChangeName( NetClient* pNetClient, CS2GSGuildMemberChangeName* pMessage );
virtual void _OnCS2GSUpdateGuildMemberOnLineTime( NetClient* pNetClient, CS2GSUpdateGuildMemberOnLineTime* pMessage );