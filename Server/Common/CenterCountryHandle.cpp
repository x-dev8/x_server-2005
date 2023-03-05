#include "CountryMessage.h"
#include "CountryManager.h"
#include "NetEvent.h"

long NetEvent::OnProcessCountryMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    MESSAGE_MAPPING_BEGIN
        MESSAGE_HANDLE( GS2CS_COUNTRYNOTICECHANGEREQ, GS2CSCountryNoticeChangeReq, _OnGS2CSCountryNoticeChangeReq);

    MESSAGE_MAPPING_END

    return ER_Success;
}


void NetEvent::_OnGS2CSCountryNoticeChangeReq( NetClient* pNetClient, GS2CSCountryNoticeChangeReq* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    if ( !pCountry->IsHaveRight( CountryDefine::Right_Placard, pMessage->nPlayerID ) )
    { return; }

    if ( pCountry->GetPlacardCount() >= CountryDefine::MaxPlacardCount )
    { return; }

    pCountry->SetNotice( pMessage->szNotice );
    pCountry->SetNeedSaveToDatabase( true );

    // 消息同步给所有服务器
    CS2GSCountryNoticeChangeAck xAck;
    xAck.uchCountryID = pMessage->uchCountryID;
    xAck.nPlayerID    = pMessage->nPlayerID;
    strncpy_s( xAck.szNotice, sizeof( xAck.szNotice ), pMessage->szNotice, sizeof( xAck.szNotice ) - 1 ); 

    theGameServerManager.SendMessageToGameServers( &xAck );
}