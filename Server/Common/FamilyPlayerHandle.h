
/************************************************************************/
/* include in GamePlayer.h                                              */
/************************************************************************/

private:
	GameFamily* m_pFamily;

public:
	bool ProcessFamilyMsg( Msg* pMsg );

	void OnMsgCreateFamilyReq( Msg* pMsg );
	void OnMsgInviteFamilyReq( Msg* pMsg );
	void OnMsgInviteJoinFamilyAck( Msg* pMsg );
	void OnMsgJoinFamilyReq( Msg* pMsg );
	void OnMsgRequestJoinFamilyAck( Msg* pMsg );
	void OnMsgQuitFamilyReq( Msg* pMsg );
	void OnMsgKickOutFamilyReq( Msg* pMsg );
	void OnMsgFamilyNoticeReq( Msg* pMsg );
	void OnMsgFamilyTransferReq( Msg* pMsg );
	void OnMsgFamilyDonateReq( Msg* pMsg );
	void OnMsgFamilyUpgradeReq( Msg* pMsg );
	void OnMsgQueryFamilyInfoReq( Msg* pMsg );
	void OnMsgFamilyAimReq( Msg* pMsg );

	void InitPlayerFamily();
	GameFamily* GetFamily() const { return m_pFamily; }
	void SetFamily( GameFamily* pFamily ) { m_pFamily = pFamily; }
	bool HaveFamily() const { return NULL != m_pFamily; }
	unsigned int GetFamilyID() const;
	void SetFamilyID( unsigned int nFamilyID );

	void ProcessJoinFamily( GameFamily* pFamily );
	void ProcessLeaveFamily( GameFamily* pFamily, uint8 nType );