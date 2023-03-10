

long OnProcessGuildMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnGS2CSCreateGuildReq( NetClient* pNetClient, GS2CSCreateGuildReq* pMessage );
virtual void _OnGS2CSLeaveGuildReq( NetClient* pNetClient, GS2CSLeaveGuildReq* pMessage );
virtual void _OnGS2CSKickGuildReq( NetClient* pNetClient, GS2CSKickGuildReq* pMessage );
virtual void _OnGS2CSInviteGuildReq( NetClient* pNetClient, GS2CSInviteGuildReq* pMessage );
virtual void _OnGS2CSInviteJoinGuildAck( NetClient* pNetClient, GS2CSInviteJoinGuildAck* pMessage );
virtual void _OnGS2CSJoinGuildReq( NetClient* pNetClient, GS2CSJoinGuildReq* pMessage );
virtual void _OnGS2CSRequestJoinGuildAck( NetClient* pNetClient, GS2CSRequestJoinGuildAck* pMessage );
virtual void _OnGS2CSGuildNoticeChangeReq( NetClient* pNetClient, GS2CSGuildNoticeChangeReq* pMessage );
virtual void _OnGS2CSGuildResignPositionReq( NetClient* pNetClient, GS2CSGuildResignPositionReq* pMessage );
virtual void _OnGS2CSGuildTransferPositionReq( NetClient* pNetClient, GS2CSGuildTransferPositionReq* pMessage );
virtual void _OnGS2CSGuildCreateFamilyReq( NetClient* pNetClient, GS2CSGuildCreateFamilyReq* pMessage );
virtual void _OnGS2CSGuildFamilyChangeReq( NetClient* pNetClient, GS2CSGuildFamilyChangeReq* pMessage );
virtual void _OnGS2CSGuildMemberFamilyChangeReq( NetClient* pNetClient, GS2CSGuildMemberFamilyChangeReq* pMessage );
virtual void _OnGS2CSGuildAssignPositionReq( NetClient* pNetClient, GS2CSGuildAssignPositionReq* pMessage );
virtual void _OnGS2CSMemberDataChangeReq( NetClient* pNetClient, GS2CSMemberDataChangeReq* pMessage );
virtual void _OnGS2CSGuildDataChangeReq( NetClient* pNetClient, GS2CSGuildDataChangeReq* pMessage );
virtual void _OnGS2CSGuildLevelUpReq( NetClient* pNetClient, GS2CSGuildLevelUpReq* pMessage );
virtual void _OnGS2CSGuildOfferBuildReq( NetClient* pNetClient, GS2CSGuildOfferBuildReq* pMessage );
virtual void _OnGS2CSGuildCollectReq( NetClient* pNetClient, GS2CSGuildCollectReq* pMessage );
virtual void _OnGS2CSGuildDelateRequestReq( NetClient* pNetClient, GS2CSGuildDelateRequestReq* pMessage );
virtual void _OnGS2CSGuildDelateAgreeAck( NetClient* pNetClient, GS2CSGuildDelateAgreeAck* pMessage );
virtual void _OnGS2CSGuildDonateRequestReq( NetClient* pNetClient, GS2CSGuildDonateRequestReq* pMessage );
virtual void _OnGS2CSGuildDonateAck( NetClient* pNetClient, GS2CSGuildDonateAck* pMessage );
virtual void _OnGS2CSGuildQuestReleaseReq( NetClient* pNetClient, GS2CSGuildQuestReleaseReq* pMessage );
virtual void _OnGS2CSGuildMessage( NetClient* pNetClient, GS2CSGuildMessage* pMessage );
virtual void _OnGS2CSGuildConveneReq( NetClient* pNetClient, GS2CSGuildConveneReq* pMessage );
virtual void _OnGS2CSGuildAimChangeReq( NetClient* pNetClient, GS2CSGuildAimChangeReq* pMessage );
virtual void _OnGS2CSPlayerLvUpToThirtyReq( NetClient* pNetClient, GS2CSPlayerLvUpToThirtyMessage* pMessage );
virtual void _OnGS2CSGuildSQReq( NetClient* pNetClient, GS2CSGuildSQReq* pMessage );
virtual void _OnGS2CSRaiseGuildPlayerItem( NetClient* pNetClient, GS2CSRaiseGuildPlayerItem* pMessage );
virtual void _OnCS2GSGuildBattleSum( NetClient* pNetClient, CS2GSGuildBattleSum* pMessage );
virtual void _OnGS2CSSetGuildCampBattleValue( NetClient* pNetClient, GS2CSSetGuildCampBattleValue* pMessage );
virtual void _OnGS2CSChangeGuildNameReq( NetClient* pNetClient, GS2CSChangeGuildNameReq* pMessage );
virtual void _OnGS2CSGuildMemberChangeName		( NetClient* pNetClient, GS2CSGuildMemberChangeName* pMessage );
virtual void _OnGS2CSUpdateGuildCampBattlePoint( NetClient* pNetClient, GS2CSUpdateGuildCampBattlePoint* pMessage );
virtual void _OnGS2CSUpdateGuildMemberOnLineTime( NetClient* pNetClient, GS2CSUpdateGuildMemberOnLineTime* pMessage );