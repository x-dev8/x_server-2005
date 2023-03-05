#include "LogMessager.h"

int G_PrinfInfo = NOPRINT;

LogMessageManager& LogMessageManager::GetInstance()
{
	static LogMessageManager instance; 
	return instance;
}

BaseLogMessage* LogMessageManager::GetLogMessageByLogMsg( Msg* pMsg )
{
	switch ( pMsg->GetType())
	{
	case LOGMSG_BEGIN_TEST:
		return NEW_POOL( LOGMSGCLASS( TestLogMessage ) );
		break;
	case LOGMSG_OnlineInfo:
		return NEW_POOL( LOGMSGCLASS( CS2LOnlineInfo ) );
		break;
	case LOGMSG_INOUNTINFO:
		return NEW_POOL( LOGMSGCLASS( GS2LPlayerInOutLog ) );
		break;
	case LOGMSG_ITEMGAIN:
		return NEW_POOL( LOGMSGCLASS( GS2LItemGain ) );
		break;
	case LOGMSG_ITEMTRADE:
		return NEW_POOL( LOGMSGCLASS( GS2LItemTrade ) );
		break;
	case LOGMSG_ITEMCONSUME:
		return NEW_POOL( LOGMSGCLASS( GS2LItemConsume ) );
		break;
	case LOGMSG_ITEMUPGRADE:
		return NEW_POOL( LOGMSGCLASS( GS2LItemUpgrade ) );
		break;
	case LOGMSG_QUESTLOG:
		return NEW_POOL( LOGMSGCLASS( GS2LQuestLog ) );
		break;
	case LOGMSG_CURRENCY:
		return NEW_POOL( LOGMSGCLASS( GS2LCurrencyLog ) );
		break;
	case LOGMSG_EXPLOG:
		return NEW_POOL( LOGMSGCLASS( GS2LExpLog ) );
		break;
	case LOGMSG_LEVCHANGE:
		return NEW_POOL( LOGMSGCLASS( GS2LLevelChange ) );
		break;
	case LOGMSG_MAILLOG:
		return NEW_POOL( LOGMSGCLASS( S2LMailLog ) );
		break;
	case LOGMSG_GUILDDETAIL:
		return NEW_POOL( LOGMSGCLASS( S2LGuildDetailLog ) );
		break;
	case LOGMSG_GUILDLOG:
		return NEW_POOL( LOGMSGCLASS( S2LGuildLog ) );
		break;
	case LOGMSG_GMCOMMAND:
		return NEW_POOL( LOGMSGCLASS( GS2LGMCommand ) );
		break;
	case LOGMSG_CHATINFO:
		return NEW_POOL( LOGMSGCLASS( GS2LChatInfo ) );
		break;
	//case CS2DB_SAVEITEMDROPCONTROL:
	//	return NEW_POOL( SQLMSGCLASS( CS2DBSaveItemDropControl ) );
	//	break;
	}
	return NULL;
}

bool LogMessageManager::FreeLogMessage( BaseLogMessage* pSqlMessage )
{
	if ( pSqlMessage == NULL )
	{ return false; }

	pSqlMessage->Release();
	return true;
}
