#include "SqlMessages.h"

bool CheckString( const std::string& strName )
{
    if ( strName.empty() )
    { return false; }

    if (strName.find("'") != string::npos || strName.find("-") != string::npos ||
        strName.find("_") != string::npos || strName.find("%") != string::npos ||
        strName.find(" ") != string::npos || strName.find(":") != string::npos || strName.find("\\") != string::npos )
        //strName.find("：") != string::npos )
        //strName.find( theXmlString.GetString(eClient_Chat_Begin) ) != string::npos )
    { return false;}
    return true;
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

BaseSqlMessage* SqlMessageManager::Get3PartySqlMessageByDbMsg( Msg* pMsg )
{
    switch ( pMsg->GetType() )
    {
    case PFMSG_ADDITEM_REQ:
        return NEW_POOL( SQLMSGCLASS( MsgPFAddItemReq) );
    	break;
    case PFMSG_ADDITEM_ACK:
        return NEW_POOL( SQLMSGCLASS(MsgPFAddItemAck) );
        break;
    }
    return NULL;
}

BaseSqlMessage* SqlMessageManager::GetSqlMessageByDbMsg( Msg* pMsg )
{
	switch ( pMsg->GetType())
	{
    case CS2DB_SAVEITEMDROPCONTROL:
        return NEW_POOL( SQLMSGCLASS( CS2DBSaveItemDropControl ) );
        break;
    case CS2DB_ITEMDROPCONTROLREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBItemDropControlReq ) );
        break;
	case GS2CS_MAILLISTREQ:
		return NEW_POOL( SQLMSGCLASS( GS2CSMailListReq) );
        break;
    case CS2GS_MAILLISTACK:
        return NEW_POOL( SQLMSGCLASS( CS2GSMailListAck) );
        break;
    case GS2CS_QUERYMAILCANSENDREQ:
        return NEW_POOL( SQLMSGCLASS( GS2CSQueryMailCanSendReq) );
        break;
    case CS2GS_QUERYMAILCANSENDACK:
        return NEW_POOL( SQLMSGCLASS( CS2GSQueryMailCanSendAck) );
        break;
    case GS2CS_SENDMAILREQ:
        return NEW_POOL( SQLMSGCLASS( GS2CSSendMailReq) );
        break;
    case CS2GS_SENDMAILACK:
        return NEW_POOL( SQLMSGCLASS( CS2GSSendMailAck) );
        break;
    case GS2CS_OPMAILREQ:
        return NEW_POOL( SQLMSGCLASS( GS2CSOpMailReq) );
        break;
    case CS2GS_OPMAILACK:
        return NEW_POOL( SQLMSGCLASS( CS2GSOpMailAck) );
        break;
    case CS2DB_REQUESTCOUNTRYDATAREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBRequestCountryDataReq ) );
        break;
	case CS2DB_REQUESTCOUNTRYINFOREQ:
		return NEW_POOL( SQLMSGCLASS( CS2DBRequestCountryInfoReq ) );
		break;
	//xuda 
	/*case CS2DB_REQUESTEMPERORDATAREQ:
		return NEW_POOL( SQLMSGCLASS(CS2DBRequestEmperorDataReq));
		break;
	case CS2DB_REQUESTWANTEDDATAREQ:
		return NEW_POOL( SQLMSGCLASS(CS2DBRequestWantedDataReq));
		break;
	case CS2DB_WANTEDINSERTREQ:
		return NEW_POOL( SQLMSGCLASS(CS2DBWantedInsertReq));
		break;
	case CS2DB_WANTEDDELETEREQ:
		return NEW_POOL( SQLMSGCLASS(CS2DBWantedDeleteReq));
		break;
	case CS2DB_WANTEDDATASAVEREQ:
		return NEW_POOL( SQLMSGCLASS(CS2DBWantedDataSaveReq));
		break;*/
    case DB2CS_REQUESTCOUNTRYDATAACK:
        return NEW_POOL( SQLMSGCLASS( DB2CSRequestCountryDataAck ) );
        break;
	case DB2CS_REQUESTCOUNTRYINFOACK:
		return NEW_POOL( SQLMSGCLASS( DB2CSRequestCountryInfoAck ) );
		break;
	//xuda 
	/*case DB2CS_REQUESTWANTEDDATAACK:
		return NEW_POOL( SQLMSGCLASS( DBS2CSRequestWantedDataAck ) );
		break;*/
	case DB2CS_REQUESTCOUNTRYOFFICECK:
		return NEW_POOL( SQLMSGCLASS( DB2CSRequestCountryOfficeAck));
		break;
    case CS2DB_COUNTRYDATESAVEREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBCountryDataSaveReq ) );
        break;
	case CS2DB_COUNTRYOFFICEREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBCountryOfficeReq ) );
        break;
    case CS2DB_RELATIONLISTREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBRelationListReq ) );
        break;
    case CS2DB_ADDRELATIONREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBAddRelationReq ) );
        break;
    case CS2DB_UPDATERELATIONDATAREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBUpdateRelationDataReq ) );
        break;
    case CS2DB_ADDATTRIBUTEREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBAddAttributeReq ) );
        break;
    case CS2DB_UPDATEATTRIBUTEREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBUpdateAttributeReq ) );
        break;
    case DB2CS_RELATIONATTRIBUTELIST:
        return NEW_POOL( SQLMSGCLASS( DB2CSRelationAttributeList ) );
        break;
    case DB2CS_RELATIONDATALIST:
        return NEW_POOL( SQLMSGCLASS( DB2CSRelationDataList ) );
        break;
    case GS2CS_QUERYATTRIBUTEREQ:
        return NEW_POOL( SQLMSGCLASS( GS2CSQueryAttributeReq ) );
        break;
    case DB2CS_QUERYATTRIBUTEACK:
        return NEW_POOL( SQLMSGCLASS( DB2CSQueryAttributeAck ) );
        break;
    case CS2DB_UPDATERELATIONGROUP:
        return NEW_POOL( SQLMSGCLASS( CS2DBUpdateRelationGroup ) );
        break;
    case CS2DB_GUILDDATALOADREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBGuildDataLoadReq ) );
        break;
    case DB2CS_GUILDDATALIST:
        return NEW_POOL( SQLMSGCLASS( DB2CSGuildDataList ) );
        break;
    case DB2CS_GUILDMEMBERLIST:
        return NEW_POOL( SQLMSGCLASS( DB2CSGuildMemberList ) );
        break;
    case CS2DB_GUILDDATAUPDATEREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBGuildDataUpdateReq ) );
        break;
    case CS2DB_GUILDMEMBERUPDATEREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBGuildMemberUpdateReq ) );
        break;
    case CS2DB_GUILDDISBANDREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBGuildDisbandReq ) );
        break;
    case CS2DB_GUILDMEMBERLEAVEREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBGuildMemberLeaveReq ) );
        break;
    case CS2DB_LOADCONSIGNMENTDATAREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBLoadConsignmentDataReq ) );
        break;
    case CS2DB_OPERATEMONEYREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBOperateMoneyReq ) );
        break;
    case DB2CS_OPERATEMONEYACK:
        return NEW_POOL( SQLMSGCLASS( DB2CSOperateMoneyAck ) );
        break;
    case CS2DB_CONSIGNMENTMONEYREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBConsignmentMoneyReq ) );
        break;
    case CS2DB_CONSIGNMENTMONEYOPERATEREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBConsignmentmoneyOperateReq ) );
        break;
    case DB2CS_CONSIGNMENTMONEYOPERATEACK:
        return NEW_POOL( SQLMSGCLASS( DB2CSConsignmentmoneyOperateAck ) );
        break;
    case DB2CS_CONSIGNMENTACCOUNTLIST:
        return NEW_POOL( SQLMSGCLASS( DB2CSLoadConsignmentAccount ) );
        break;
    case DB2CS_CONSIGNMENTMONEYLIST:
        return NEW_POOL( SQLMSGCLASS( DB2CSLoadConsignmentMoneyList ) );
        break;
    case DB2CS_CONSIGNMENTHISTROYLIST:
        return NEW_POOL( SQLMSGCLASS( DB2CSLoadConsignmentHistroy ) );
        break;
    case DB2CS_ITEMDROPCONTROL:
        return NEW_POOL( SQLMSGCLASS( DB2CSItemDropControl ) );
        break;
    case CS2DB_SAVESYSTEMVARREQ:    // 从CS保存系统变量到DB的Sql消息
        return NEW_POOL( SQLMSGCLASS( CS2DBSaveSystemVarReq ) );
        break;
    case CS2DB_LOADSYSTEMVARREQ:    // CS 到 DB加载系统变量
        return NEW_POOL( SQLMSGCLASS( CS2DBLoadSystemVarReq ) );
        break;
    case DB2CS_LOADSYSVARSUCCESS:   // DB 发给 CS加载系统变量成功
        return NEW_POOL( SQLMSGCLASS(DB2CSLoadSysVarSuccess) );
        break;
    case DB2CS_LOADSYSTEMVARACK:
        return NEW_POOL( SQLMSGCLASS(DB2CSLoadSystemVarAck) );
        break;
    //case P2CS_ADDPAYREQ:
    //    return NEW_POOL( SQLMSGCLASS( P2CSAddPayReq ));
    //    break;
    //case CS2P_ADDPAYACK:
    //    return NEW_POOL( SQLMSGCLASS( CS2PAddPayAck ));
    //    break;
    case CS2DB_UPDATEPERSONALINFOREQ:
        return NEW_POOL( SQLMSGCLASS( CS2DBUpdatePersonalInfoReq ) );
        break;
    case GS2CS_FINDBYCONDITION:
        return NEW_POOL( SQLMSGCLASS( GS2CSFindPersonReq ) );
        break;
	case CS2DB_FAMILYDATALOADREQ:
		return NEW_POOL( SQLMSGCLASS( CS2DBFamilyDataLoadReq ) );
		break;
	case CS2DB_FAMILYDATAUPDATEREQ:
		return NEW_POOL( SQLMSGCLASS( CS2DBFamilyDataUpdateReq ) );
		break;
	case CS2DB_FAMILYMEMBERUPDATEREQ:
		return NEW_POOL( SQLMSGCLASS( CS2DBFamilyMemberUpdateReq ) );
		break;
	case CS2DB_FAMILYMEMBERLEAVEREQ:
		return NEW_POOL( SQLMSGCLASS( CS2DBFamilyMemberLeaveReq ) );
		break;
	case CS2DB_FAMILYDISBANDREQ:
		return NEW_POOL( SQLMSGCLASS( CS2DBFamilyDisbandReq ) );
		break;
	case DB2CS_FAMILYDATALIST:
		return NEW_POOL( SQLMSGCLASS( DB2CSFamilyDataList ) );
		break;
	case DB2CS_FAMILYMEMBERLIST:
		return NEW_POOL( SQLMSGCLASS( DB2CSFamilyMemberList ) );
		break;
	case GS2CS_UPDATEANTIADDICTIONINFOREQ:
        return NEW_POOL( SQLMSGCLASS( GS2CSUpdateAntiaddictionInfoReq ) );
        break;
    case CS2GS_UPDATEANTIADDICTIONINFOACK:
        return NEW_POOL( SQLMSGCLASS( CS2GSUpdateAntiaddictionInfoAck ) );
        break;
	case MSG_LOADDATA_REQ:
		return NEW_POOL( SQLMSGCLASS(MsgReqMYSQLData));
		break;
	case MSG_LOADDATA_ACK:
		return NEW_POOL( SQLMSGCLASS(MsgAckMySQLData));
		break;
	case MSG_ADDLEVELLIMIT:
		return NEW_POOL( SQLMSGCLASS(MsgAddLevelLimit));
		break;
	case MSG_UPDATELEVELLIMIT:
		return NEW_POOL( SQLMSGCLASS(MsgUpdateLevelLimit));
		break;
	case CS2GS_LOADGLOBALDBREQ:
		return NEW_POOL(SQLMSGCLASS(GS2CSLoadGlobalDBReq));
		break;
	case CS2GS_SAVEGLOBALDBREQ:
		return NEW_POOL(SQLMSGCLASS(GS2CSSaveGlobalDBReq));
		break;
	case CS2GS_LOADGLOBALDBACK:
		return NEW_POOL(SQLMSGCLASS(GS2CSLoadGlobalDBAck));
		break;
	case CS2DB_REQUESTQUESTENTRUSTDATAREQ:
		return NEW_POOL(SQLMSGCLASS(CS2DBRequestQuestEntrustDataReq));
		break;
	case CS2DB_ADDQUESTENTRUSTDATAACK:
		return NEW_POOL(SQLMSGCLASS(CS2DBAddQuestEntrustDataAck));
		break;
	case CS2DB_QUESTENTRUSTDELETEREQ:
		return NEW_POOL(SQLMSGCLASS(CS2DBQuestEntrustDeleteReq));
		break;
	case CS2DB_QUESTENTRUSTDATASAVEREQ:
		return NEW_POOL(SQLMSGCLASS(CS2DBQuestEntrustDataSaveReq));
		break;
	case DB2CS_REQUESTQUESTENTRUSTDATAACK:
		return NEW_POOL(SQLMSGCLASS(DBS2CSRequestQuestEntrustDataAck));
		break;
	case CS2DB_LOADCAMPBATTLEDATA:
        return NEW_POOL( SQLMSGCLASS(CS2DBLoadCampBattleData));
        break;
    case DB2CS_LOADCAMPBATTLEDATA:
        return NEW_POOL( SQLMSGCLASS(DB2CSLoadCampBattleData));
        break;
    case CS2DB_ADDCAMPBATTLEDATA:
        return NEW_POOL( SQLMSGCLASS(CS2DBAddCampBattleData));
        break;
    case CS2DB_DELCAMPBATTLEDATA:
        return NEW_POOL( SQLMSGCLASS(CS2DBDelCampBattleData));
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
