/********************************************************************
    Filename:    PlatformMessageHandle.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

// Include In Class CenterServer
void HandleAddPoint                  ( uint32 clientId, Msg* pMsg );
//void HandleGMKickPlayerReq           ( uint32 clientId, Msg* pMsg );
void HandleGMBroadcastReq            ( uint32 clientId, Msg* pMsg );
//void HandleCreateCharReq             ( uint32 clientId, Msg* pMsg );
void HandleServerStatusReq           ( uint32 clientId, Msg* pMsg );
void HandleMsgPFAddItemReq           ( uint32 clientId, Msg* pMsg );
void HandleMsgPFGMReloadTradeShop    ( uint32 clientId, Msg* pMsg );
void HandleMsgPFGMShutdownServers    ( uint32 clientId, Msg* pMsg );
void HandleMsgPFGMChangeMapExpRateReq( uint32 clientId, Msg* pMsg );
void HandleMsgPFGMOPChatOnOff        ( uint32 clientId, Msg* pMsg );

//platform serve
void PlatFormMsgGMBroadcastReq		( Msg* pMsg );
void PlatFormMsgSendMailReq			( Msg* pMsg );
void PlatFormMsgGMOPChatOnOf		( Msg* pMsg );
void PlatFormMsgShutDownServers		( Msg* pMsg );
void PlatFormMsgModifyError			( Msg* pMsg );
void PlatFormBanAccount				( Msg* pMsg );
void PlatFormBanMacAdress			( Msg* pMsg );
void PlatFormEpistarPointAck		( Msg* pMsg );