
/************************************************************************
            Include in NetEvent.h
************************************************************************/

long OnProcessFamilyMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnGS2CSCreateFamilyReq( NetClient* pNetClient, GS2CSCreateFamilyReq* pMessage );
virtual void _OnGS2CSInviteFamilyReq( NetClient* pNetClient, GS2CSInviteFamilyReq* pMessage );
virtual void _OnGS2CSInviteJoinFamilyAck( NetClient* pNetClient, GS2CSInviteJoinFamilyAck* pMessage );
virtual void _OnGS2CSJoinFamilyReq( NetClient* pNetClient, GS2CSJoinFamilyReq* pMessage );
virtual void _OnGS2CSRequestJoinFamilyAck( NetClient* pNetClient, GS2CSRequestJoinFamilyAck* pMessage );
virtual void _OnGS2CSQuitFamilyReq( NetClient* pNetClient, GS2CSQuitFamilyReq* pMessage );
virtual void _OnGS2CS_KickOutFamilyReq( NetClient* pNetClient, GS2CSKickOutFamilyReq* pMessage );
virtual void _OnGS2CS_FamilyNoticeReq( NetClient* pNetClient, GS2CSFamilyNoticeReq* pMessage );
virtual void _OnGS2CSFamilyTransferReq( NetClient* pNetClient, GS2CSFamilyTransferReq* pMessage );
virtual void _OnGS2CSFamilyDonateReq( NetClient* pNetClient, GS2CSFamilyDonateReq* pMessage );
virtual void _OnGS2CSFamilyUpgradeReq( NetClient* pNetClient, GS2CSFamilyUpgradeReq* pMessage );
virtual void _OnGS2CSTellMemberOffline( NetClient* pNetClient, GS2CSTellMemberOffline* pMessage );
virtual void _OnGS2CSFamilyPlayerLvToTen( NetClient* pNetClient, GS2CSFamilyPlayerLvUpToTenMessage* pMessage );
virtual void _OnGS2CSFamilyMemberDataChangeReq( NetClient* pNetClient, GS2CSFamilyMemberDataChangeReq* pMessage );
virtual void _OnGS2CSFamilyMessage( NetClient* pNetClient, GS2CSFamilyMessage* pMessage );
virtual void _OnGS2CSFamilyProsperityUpdate( NetClient* pNetClient, GS2CSFamilyProsperityUpdate* pMessage );
virtual void _OnGS2CS_FamilyAimReq( NetClient* pNetClient, GS2CSFamilyAimReq* pMessage );