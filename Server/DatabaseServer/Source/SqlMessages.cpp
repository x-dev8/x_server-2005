#include "SqlMessages.h"

void DebugLogMsg(const char* szText)
{
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "%s", szText);
    //char szDate[256] = {0};
    //char szTime[256] = {0};
    //char szFile[256] = {0};
    //char szLog[1024] = {0};

    //SYSTEMTIME systime;
    //GetLocalTime( &systime );

    //_snprintf(szDate, sizeof(szDate)-1, "%04d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
    //_snprintf(szTime, sizeof(szTime)-1, "%02d:%02d:%02d", systime.wHour, systime.wMinute, systime.wSecond);

    //   char szPath[256] = {0};
    //   _snprintf(szPath, sizeof(szPath)-1, "Log\\%s", szDate);
    //   _mkdir("Log");
    //   _mkdir(szPath);

    //   _snprintf(szFile, sizeof(szTime)-1, "%s\\%02d_DB.log", szPath, systime.wHour);
    //std::ofstream fLog(szFile, std::ios::app);

    //if(!fLog.is_open())
    //{
    //    return;
    //}

    //fLog << szDate << " " << szTime << "    " << szText << std::endl;
    //fLog.close();
    //CGameLog::theDBLog.OutputWithTime(szText);
}

const char* BigInt2String(__int64 nInt)
{
    static char szGuid[40];
    _i64toa(nInt, szGuid, 10);
    return szGuid;
}

const __int64 String2BigInt(const char* szBigInt)
{
    return _strtoi64(szBigInt, 0, 10);
}

static unsigned char Decode6BitMask[5] = { 0xfc, 0xf8, 0xf0, 0xe0, 0xc0 };

//编码函数（用于二进制人物数据编码成可视字符串方便数据库存储）
// pDec : 存放编码过后的字串地址
// pSrc : 需要进行编码的二进制数值地址
// 返回值: 编码过后的pDec字串长度
int EnCodeToString(const unsigned char *pszSrc, char *pszDest, size_t nSrcLen, size_t nDestLen)
{
    int           nDestPos   = 0;
    int           nRestCount = 0;
    unsigned char chMade = 0, chRest = 0;

    for (int i = 0; i < nSrcLen; ++i)
    {
        if (nDestPos >= nDestLen) break;

        chMade = ((chRest | (pszSrc[i] >> (2 + nRestCount))) & 0x3f);
        chRest = (((pszSrc[i] << (8 - (2 + nRestCount))) >> 2) & 0x3f);

        nRestCount += 2;

        if (nRestCount < 6)
        { pszDest[nDestPos++] = chMade + 0x3c; }
        else
        {
            if (nDestPos < nDestLen - 1)
            {
                pszDest[nDestPos++]    = chMade + 0x3c;
                pszDest[nDestPos++]    = chRest + 0x3c;
            }
            else
            { pszDest[nDestPos++] = chMade + 0x3c; }

            nRestCount    = 0;
            chRest        = 0;
        }
    }

    if (nRestCount > 0)
    { pszDest[nDestPos++] = chRest + 0x3c; }

    pszDest[nDestPos] = '\0';

    return nDestPos;
}

//解码函数（用于从数据库中载入可视字符串还原成二进制人物数据）
// pDec : 存放解码过后的二进制数值地址
// pSrc : 需要进行解码的字符串地址
// 返回值: 解码过后的pDec二进制数值长度
int DeCodeFromString(const uint8* pszSrc, char* pszDest, size_t nDestLen)
{
    if ( pszSrc == NULL || pszDest == NULL )
    { return 0; }

    int nLen = strlen((const char*)pszSrc);
    int nDestPos = 0, nBitPos = 2;
    int nMadeBit = 0;
    unsigned char ch, chCode, tmp = 0;

    for (int i=0; i<nLen; ++i)
    {
        if ((pszSrc[i] - 0x3c) >= 0)
        { ch = pszSrc[i] - 0x3c; }
        else
        {
            nDestPos = 0;
            break;
        }

        if (nDestPos >= nDestLen) 
        { break; }

        if ((nMadeBit + 6) >= 8)
        {
            chCode = (tmp | ((ch & 0x3f) >> (6 - nBitPos)));
            pszDest[nDestPos++] = chCode;

            nMadeBit = 0;

            if (nBitPos < 6) 
            { nBitPos += 2; }
            else
            {
                nBitPos = 2;
                continue;
            }
        }

        tmp = ((ch << nBitPos) & Decode6BitMask[nBitPos - 2]);
        nMadeBit += (8 - nBitPos);
    }
    return nDestPos;
}

uint32 DeCodeToBuffer(const int8* pszSrc, uint8* pszDest, size_t nDestLen)
{
    if ( pszSrc == NULL || pszDest == NULL )
    { return 0; }

    int nLen = strlen( pszSrc );
    int nDestPos = 0, nBitPos = 2;
    int nMadeBit = 0;
    unsigned char ch, chCode, tmp = 0;

    for (int i=0; i<nLen; ++i)
    {
        if (( (uint8)pszSrc[i] - 0x3c) >= 0)
        { ch = (uint8)pszSrc[i] - 0x3c; }
        else
        {
            nDestPos = 0;
            break;
        }

        if (nDestPos >= nDestLen) 
        { break; }

        if ((nMadeBit + 6) >= 8)
        {
            chCode = (tmp | ((ch & 0x3f) >> (6 - nBitPos)));
            pszDest[nDestPos++] = chCode;

            nMadeBit = 0;

            if (nBitPos < 6) 
            { nBitPos += 2; }
            else
            {
                nBitPos = 2;
                continue;
            }
        }

        tmp = ((ch << nBitPos) & Decode6BitMask[nBitPos - 2]);
        nMadeBit += (8 - nBitPos);
    }
    return nDestPos;
}

int G_PrinfInfo = NOPRINT;

SqlMessageManager& SqlMessageManager::GetInstance()
{
    static SqlMessageManager instance; 
    return instance;
}

BaseSqlMessage* SqlMessageManager::GetSqlMessageByDbMsg( Msg* pMsg )
{
    switch ( pMsg->GetType() )
    {
    // 接受消息池
    case DBMSG_SAVECHARACTER:
        return NEW_POOL( SQLMSGCLASS(DBMsgSaveCharacter) );
    	break;
    case DBMSG_ENTERWORD:
        return NEW_POOL( SQLMSGCLASS(DBMsgEnterWorld) );
        break;
    case DBMSG_QUERYACCOUNTCHAR:
        return NEW_POOL( SQLMSGCLASS(DBMsgQueryAccountChar));
        break;
    case DBMSG_OFFLINE:
        return NEW_POOL( SQLMSGCLASS(DBMsgOffline2));
        break;
    case DBMSG_CREATECHAR:
        return NEW_POOL( SQLMSGCLASS(DBMsgCreateHeroChar));
        break;
    case DBMSG_REQ_CREATE_CHECKNAME:
        return NEW_POOL( SQLMSGCLASS(DBMsgReqCreateCheckName));
        break;
	case DBMSG_CHANGENAMEREQ:
		return NEW_POOL( SQLMSGCLASS(DBMsgChangeNameReq));
        break;
    case DBMSG_DELETECHAR:
        return NEW_POOL( SQLMSGCLASS(DBMsgDeleteChar2));
        break;
    case DBMSG_CANCELDELCHAR:
        return NEW_POOL( SQLMSGCLASS(DBMsgCancelDelChar));
        break;
    case DBMSG_REQ_STORAGE:
        return NEW_POOL( SQLMSGCLASS(DBMsgReqStorage));
        break;
    case DBMSG_REQ_ACCOUNT_BILLING:
        return NEW_POOL( SQLMSGCLASS(DBMsgReqAccountBilling));
        break;
    case DBMSG_REQ_ACCOUNT_BILLING_OP:
        return NEW_POOL( SQLMSGCLASS(DBMsgReqAccountBillingOp));
        break;
    case CS2DB_ACCOUNTPOINTER_REQ:
        return NEW_POOL( SQLMSGCLASS(CS2DBAccountPoints));
        break;
    case DBMSG_ACK_ACCOUNT_BILLING:
        return NEW_POOL( SQLMSGCLASS(DBMsgAckAccountBilling));
        break;
    case DB2CS_ACCOUNTPOINTER_ACK:
        return NEW_POOL( SQLMSGCLASS(DB2CSAccountPoints));
        break;
    case DBMSG_PETBREEDQUERYREQ:
        return NEW_POOL( SQLMSGCLASS(DBMsgPetBreedQueryReq));
        break;
	case GS2DB_UPDATEYUANBAODATA:
		return NEW_POOL( SQLMSGCLASS(GS2DBUpdateYuanBaoData));
        break;
	case GS2DB_UPDATEPLAYERPOINT:
		return NEW_POOL( SQLMSGCLASS(GS2DBUpdatePlayerPoint));
		break;
    // 回馈消息池
    case DBMSG_ACK_CREATE_CHECKNAME:
        return NEW_POOL( SQLMSGCLASS(DBMsgAckCreateCheckName));
        break;
	case DBMSG_CHANGENAMEACK:
		return NEW_POOL( SQLMSGCLASS(DBMsgChangeNameAck));
        break;
    case DBMSG_ACKCREATECHAR:
        return NEW_POOL( SQLMSGCLASS(DBMsgCreateCharAck));
        break;
    case DBMSG_ACKCHAR:
        return NEW_POOL( SQLMSGCLASS(DBMsgAckCharInfo));
        break;
    case DBMSG_ENDACKCHAR:
        return NEW_POOL( SQLMSGCLASS(DBMsgEndAckChar));
        break;
    case DBMSG_ACKENTERWORD:
        return NEW_POOL( SQLMSGCLASS(DBMsgAckEnterWorld));
        break;
    case MSG_ACK_RESULT:
        return NEW_POOL( SQLMSGCLASS(MsgAckResult));
        break;
    case DBMSG_ACKOPERSUCC:
        return NEW_POOL( SQLMSGCLASS(DBAckOperSucc));
        break;
    case DBMSG_ACKDELETECHAR:
        return NEW_POOL( SQLMSGCLASS(DBMsgAckDeleteChar2));
        break;
    case DBMSG_ACKCANCELDELCHAR:
        return NEW_POOL( SQLMSGCLASS(DBMsgAckCancelDelChar));
        break;
    case DBMSG_ACCOUNTWALLOWINFO_REQ:
        return NEW_POOL( SQLMSGCLASS(DBAccountWallowInfoReq));
        break;
    case DBMSG_ACCOUNTWALLOWINFO_ACK:
        return NEW_POOL( SQLMSGCLASS(DBAccountWallowInfoAck));
        break;
    case DBMSG_ACCOUNTWALLOWINFO_SAVE:
        return NEW_POOL( SQLMSGCLASS(DBAccountWallowInfoSave));
        break;
    case MSG_REGISTERSERVERACK:
        return NEW_POOL( SQLMSGCLASS(MsgRegisterServerAck));
        break;
    case MSG_SERVERSTATUSACK:
        return NEW_POOL( SQLMSGCLASS(MsgServerStatusAck));
        break;
    case DBMSG_JIFENGSHOPITEMSLISTREQ:
        return NEW_POOL( SQLMSGCLASS(DBMsgJiFengShopItemsListReq));
        break;
    case DBMSG_JIFENGSHOPITEMSLISTACK:
        return NEW_POOL( SQLMSGCLASS(DBMsgJiFengShopItemsListAck));
        break;
    case DBMSG_JIFENGSHOPITEMSGAINREQ:
        return NEW_POOL( SQLMSGCLASS(DBMsgJiFengShopItemsGainReq));
        break;
    case DBMSG_JIFENGSHOPITEMSGAINACK:
        return NEW_POOL( SQLMSGCLASS(DBMsgJiFengShopItemsGainAck));
        break;
    case DB2DB_NOTIFYFILEDBSAVECHAR:
        return NEW_POOL( SQLMSGCLASS(DB2DBNotifyFileDBSaveChar));
        break;
    case DBMSG_PETBREEDQUERYACK:
        return NEW_POOL( SQLMSGCLASS(DBMsgPetBreedQueryAck));
        break;
	case DBMSG_SHOPPING:
		return NEW_POOL( SQLMSGCLASS(DBMsgShopping));
		break;
	case DBMSG_OPERATEACCOUNTMONEY:
		return NEW_POOL( SQLMSGCLASS(DBMsgOperateAccountMoney));
		break;
	case DBMSG_SETBILLINGMONEY:
		return NEW_POOL(SQLMSGCLASS(DBMsgSetBillingMoney));
		break;
	case DB2DB_Cash:
		return NEW_POOL(SQLMSGCLASS(DB2DBCash));
		break;
	case DB2DB_CashResult:
		return NEW_POOL(SQLMSGCLASS(DB2DBCashResult));
		break;
	case DBMSG_OPCONSUMESCORE:
		return NEW_POOL(SQLMSGCLASS(DBMsgOperateAccountConsumeScore));
	case DBMSG_SETCONSUMESCORE:
		return NEW_POOL(SQLMSGCLASS(DBMsgSetConsumeScore));
		break;
	case DB2DB_ConsumeScore:
		return NEW_POOL(SQLMSGCLASS(DB2DBConsumeScore));
		break;
	case DB2DB_ConsumeScoreResult:
		return NEW_POOL(SQLMSGCLASS(DB2DBConsumeScoreResult));
		break;
	case DB2GS_UPDATEYUANBAODATA:
		return NEW_POOL(SQLMSGCLASS(DB2GSUpdateYuanBaoData));
		break;
	case DB2GS_UPDATEPLAYERPOINT:
		return NEW_POOL(SQLMSGCLASS(DB2GSUpdatePlayerPoint));
		break;
    }
    return NULL;
}

bool SqlMessageManager::FreeSqlMessage( BaseSqlMessage* pSqlMessage )
{
    if ( pSqlMessage == NULL )
    { return false; }
    
    pSqlMessage->Release();
    return true;
}
