#pragma once
private:

public:
    bool ProcessGameBattleMsg( Msg* pMsg ); 

	void OnMsgCampBattleNewDataReq( Msg* pMsg );
	void OnMsgLoadCampBattleDataReq( Msg* pMsg );
	void OnMsgAddCampBattleDataReq( Msg* pMsg );
	void OnMsgDelCampBattleDataReq( Msg* pMsg );
	void OnMsgEnterGameBattleReq( Msg* pMsg );