/************************************************************************
            Include in CenterServerNetEvent.h only
************************************************************************/

long OnProcessGameLevelLimitMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void OnMsgUpdateLimitPlayerCount( NetClient* pNetClient, MsgUpdatePlayerCount* pMessage );
virtual void OnMsgAckActiveLimit( NetClient* pNetClient, MsgActiveLimitAck* pMessage );
virtual void OnMsgHoleLimitInfo( NetClient* pNetClient, Msg2AllGameInfo* pMessage );
virtual void OnMsgUpdateLimitState( NetClient* pNetClient, MsgUpdateLevelLimitSate* pMessage );