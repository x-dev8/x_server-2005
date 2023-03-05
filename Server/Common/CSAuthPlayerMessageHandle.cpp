#include "GamePlayer.h"
#include "CSAuthMessage.h"
bool GamePlayer::ProcessCSAuthMsg( Msg* pMsg )
{
    DWORD dwType = pMsg->GetType();

    GAMESERVER_MESSAGE_MAPPING_BEGIN
		GAMESERVER_MESSAGE_HANDLE( MSG_CHECKCSAUTHACK, OnMsgCheckCSAuthAck );
    GAMESERVER_MESSAGE_MAPPING_END
    return false;
}
void GamePlayer::OnMsgCheckCSAuthAck(Msg* pMsg)
{
	MsgCheckCSAuthAck * pAck = (MsgCheckCSAuthAck*)pMsg;
	if(!pAck)
		return;
	#ifdef NPGUARD
		_authManager.ReviceCheckMsgByClient(pAck,this);
	#endif
}