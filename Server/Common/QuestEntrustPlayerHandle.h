#pragma once
public:
    bool ProcessQuestEntrustMsg( Msg* pMsg );
	void OnMsgLoadQuestEntrustDataReq( Msg* pMsg );
	void OnMsgAddQuestEntrustReq( Msg* pMsg );
	void OnMsgDelQuestEntrustReq( Msg* pMsg );
	void OnMsgUpdateJoinQuestEntrustReq( Msg* pMsg );
	void OnMsgUpdateCanelQuestEntrustReq( Msg* pMsg );
	void OnMsgQuestEntrustSeccReq( Msg* pMsg );