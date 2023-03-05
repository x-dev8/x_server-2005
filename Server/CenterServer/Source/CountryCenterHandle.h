
/************************************************************************
            Include in NetEvent.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/

long OnProcessCountryMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnGS2CSCountryNoticeChangeReq     ( NetClient* pNetClient, GS2CSCountryNoticeChangeReq* pMessage );
virtual void _OnGS2CSCountryQuestStatusChangeReq( NetClient* pNetClient, GS2CSCountryQuestStatusChangeReq* pMessage );
virtual void _OnGS2CSCountryOfficialAppointReq  ( NetClient* pNetClient, GS2CSCountryOfficialAppointReq* pMessage );
virtual void _OnGS2CSCountryOfficialRecallReq   ( NetClient* pNetClient, GS2CSCountryOfficialRecallReq* pMessage );
virtual void _OnGS2CSCountryBattleResult        ( NetClient* pNetClient, GS2CSCountryBattleResult* pMessage );
virtual void _OnGS2CSCountryBattleReward        ( NetClient* pNetClient, GS2CSCountryBattleReward* pMessage );
virtual void _OnGS2CSCountryRequestRaiseReq     ( NetClient* pNetClient, GS2CSCountryRequestRaiseReq* pMessage );
virtual void _OnGS2CSCountryMoneyRaiseed        ( NetClient* pNetClient, GS2CSCountryMoneyRaiseed* pMessage );
virtual void _OnGS2CSCountryBordersFight        ( NetClient* pNetClient, GS2CSCountryBordersFight* pMessage );
virtual void _OnGS2CSCountryOperateToPlayerReq  ( NetClient* pNetClient, GS2CSCountryOperateToPlayerReq* pMessage );
virtual void _OnGS2CSCountryOperateToPlayerAck  ( NetClient* pNetClient, GS2CSCountryOperateToPlayerAck* pMessage );
virtual void _OnGS2CSCountryConveneReq          ( NetClient* pNetClient, GS2CSCountryConveneReq* pMessage );
virtual void _OnGS2CSCountrySetOfficial         ( NetClient* pNetClient, GS2CSCountrySetOfficial* pMessage );
virtual void _OnGS2CSCountryChangeResult        ( NetClient* pNetClient, GS2CSCountryChangeResult* pMessage );
virtual void _OnGS2CSCountryDateChangeReq       ( NetClient* pNetClient, GS2CSCountryDateChangeReq* pMessage );
virtual void _OnGS2CSChangeCountryNameReq       ( NetClient* pNetClient, GS2CSChangeCountryNameReq* pMessage );
virtual void _OnGS2CSCountryWarKillPlayer       ( NetClient* pNetClient, GS2CSCountryWarKillPlayer* pMessage );
virtual void _OnGS2CSCountryWarStatusChange     ( NetClient* pNetClient, GS2CSCountryWarStatusChange* pMessage );
virtual void _OnGS2CSCountryPlayerChange		( NetClient* pNetClient, GS2CSCountryPlayerChange* pMessage );
virtual void _OnGS2CSAddCountryOfficial			( NetClient* pNetClient, GS2CSAddCountryOfficial* pMessage );
virtual void _OnGS2CSRaiseCountryPlayerItem		( NetClient* pNetClient, GS2CSRaiseCountryPlayerItem* pMessage );
virtual void _OnGS2CSDelCountryOfficialReq		( NetClient* pNetClient, GS2CSDelCountryOfficialReq* pMessage );
virtual void _OnGS2CSAddCountryInfoReq			( NetClient* pNetClient, GS2CSAddCountryInfoReq* pMessage );