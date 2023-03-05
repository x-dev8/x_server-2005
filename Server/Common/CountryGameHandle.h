
/************************************************************************
            Include in CenterServerNetEvent.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/

long OnProcessCountryMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnCS2GSCountryNoticeChangeAck     ( NetClient* pNetClient, CS2GSCountryNoticeChangeAck* pMessage );
virtual void _OnCS2GSCountryQuestStatusChangeAck( NetClient* pNetClient, CS2GSCountryQuestStatusChangeAck* pMessage );
virtual void _OnCS2GSCountryDateChangeed        ( NetClient* pNetClient, CS2GSCountryDateChangeed* pMessage );
virtual void _OnCS2GSCountryQuestStatusStop     ( NetClient* pNetClient, CS2GSCountryQuestStatusStop* pMessage );
virtual void _OnCS2GSCountryDataList            ( NetClient* pNetClient, CS2GSCountryDataList* pMessage );
virtual void _OnCS2GSCountryBattleResult        ( NetClient* pNetClient, CS2GSCountryBattleResult* pMessage );
virtual void _OnCS2GSCountryRequestRaiseAck     ( NetClient* pNetClient, CS2GSCountryRequestRaiseAck* pMessage );
virtual void _OnCS2GSCountryBordersFight        ( NetClient* pNetClient, CS2GSCountryBordersFight* pMessage );
virtual void _OnCS2GSCountryOperateToPlayerReq  ( NetClient* pNetClient, CS2GSCountryOperateToPlayerReq* pMessage );
virtual void _OnCS2GSCountryOperateToPlayerAck  ( NetClient* pNetClient, CS2GSCountryOperateToPlayerAck* pMessage );
virtual void _OnCS2GSCountryConveneReq          ( NetClient* pNetClient, CS2GSCountryConveneReq* pMessage );
virtual void _OnCS2GSCountrySetOfficial         ( NetClient* pNetClient, CS2GSCountrySetOfficial* pMessage );
virtual void _OnCS2GSCountryDataUpdate          ( NetClient* pNetClient, CS2GSCountryDataUpdate* pMessage );
virtual void _OnCS2GSCountryOfficialChange      ( NetClient* pNetClient, CS2GSCountryOfficialChange* pMessage );
virtual void _OnCS2GSTellWeakCountry            ( NetClient* pNetClient, CS2GSTellWeakCountry* pMessage );
virtual void _OnCS2GSCountryNameChange          ( NetClient* pNetClient, CS2GSCountryNameChange* pMessage );
virtual void _OnCS2GSCountryWarStatus           ( NetClient* pNetClient, CS2GSCountryWarStatus* pMessage );
virtual void _OnCS2GSCountryWarKillPlayer       ( NetClient* pNetClient, CS2GSCountryWarKillPlayer* pMessage );
virtual void _OnCS2GSTellStrongCountry			( NetClient* pNetClient, CS2GSTellStrongCountry* pMessage );
virtual void _OnCS2GSCountryWeakStrong			( NetClient* pNetClient, CS2GSCountryWeakStrongthChange* pMessage );
virtual void _OnCS2GSAddCountryOfficial			( NetClient* pNetClient, CS2GSAddCountryOfficial* pMessage );
virtual void _OnCS2GSCountryOfficialReward		( NetClient* pNetClient, CS2GSCountryOfficialReward* pMessage );
virtual void _OnCS2GSAddCountryInfoAck			( NetClient* pNetClient, CS2GSAddCountryInfoAck* pMessage );
virtual void _OnCS2GSRequestCountryInfoAck		( NetClient* pNetClient, CS2GSRequestCountryInfoAck* pMessage );