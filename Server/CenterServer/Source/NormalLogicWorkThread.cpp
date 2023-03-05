#include "NormalLogicWorkThread.h"
#include "zlib/zlib.h"
#include "tstring.h"
#include "MySqlCommunication.h"
#include "GlobalDBManager.h"
#pragma warning( push )
#pragma warning( disable : 4244 )

NormalLogicWorkThread::NormalLogicWorkThread( MySqlCommunication* pOwn ) : MySqlWorkThread(pOwn)
{
}


uint32 NormalLogicWorkThread::Update()
{
    // 保存基本的 Sql连接 和 Update
    if ( MySqlWorkThread::Update() == ER_SqlNotConnected )
    { return ER_Success; }

	theCenterGlobalDBManager.InitGlobalDB();

    BaseSqlMessage* pSqlMessage = _dbMsgQueue.PopQuery();
    while ( pSqlMessage != NULL)
    {
        switch( pSqlMessage->type )
        {
        case CS2DB_SAVEITEMDROPCONTROL:
            OnQuerySaveItemDropControl( pSqlMessage );
            break;
        case CS2DB_ITEMDROPCONTROLREQ:
            OnQueryItemDropControlReq( pSqlMessage );
            break;
        case PFMSG_ADDITEM_REQ:
            OnMsgPFAddItemReq( pSqlMessage );
            break;
        case GS2CS_MAILLISTREQ:
            OnGS2CSMailListReq( pSqlMessage );
            break;
        case GS2CS_QUERYMAILCANSENDREQ:
            OnGS2CSQueryMailCanSendReq( pSqlMessage );
            break;
        case GS2CS_SENDMAILREQ:
            OnGS2CSSendMailReq( pSqlMessage );
            break;
        case GS2CS_OPMAILREQ:
            OnGS2CSOpMailReq( pSqlMessage );
            break;
        case CS2DB_REQUESTCOUNTRYDATAREQ:
            OnRequestCountryDataReq( pSqlMessage );
            break;
		case CS2DB_REQUESTCOUNTRYINFOREQ:
			OnSaveCountryInfoReq( pSqlMessage );
			break;
        case CS2DB_COUNTRYDATESAVEREQ:
            OnCountryDataSaveReq( pSqlMessage );
            break;
		case CS2DB_COUNTRYOFFICEREQ:
			OnGetCountryOfficeFaceInfo(pSqlMessage);
			break;
        case CS2DB_RELATIONLISTREQ:
            OnQueryLoadRelationReq( pSqlMessage );
            break;
        case CS2DB_UPDATERELATIONGROUP:
            OnUpdateRelationGroup( pSqlMessage );
            break;
        case CS2DB_ADDRELATIONREQ:
            OnAddRelationReq( pSqlMessage );
            break;
        case CS2DB_UPDATERELATIONDATAREQ:
            OnUpdateRelationDataReq( pSqlMessage );
            break;
        case CS2DB_ADDATTRIBUTEREQ:
            OnAddAttributeReq( pSqlMessage );
            break;
        case CS2DB_UPDATEATTRIBUTEREQ:
            OnUpdateAttributeReq( pSqlMessage );
            break;
        case GS2CS_QUERYATTRIBUTEREQ:
            OnQueryAttributeReq( pSqlMessage );
            break;
        case CS2DB_GUILDDATALOADREQ:
            OnGuildDataLoadReq( pSqlMessage );
            break;
        case CS2DB_GUILDDATAUPDATEREQ:
            OnGuildDataUpdateReq( pSqlMessage );
            break;
        case CS2DB_GUILDMEMBERUPDATEREQ:
            OnGuildMemberUpdateReq( pSqlMessage );
            break;
        case CS2DB_GUILDDISBANDREQ:
            OnGuildDisbandReq( pSqlMessage );
            break;
        case CS2DB_GUILDMEMBERLEAVEREQ:
            OnGuildMemberLeaveReq( pSqlMessage );
            break;
        case CS2DB_LOADCONSIGNMENTDATAREQ:
            OnLoadConsignmentData( pSqlMessage );
            break;
        case CS2DB_OPERATEMONEYREQ:
            OnConsignmnetAccountReq( pSqlMessage );
            break;
        case CS2DB_CONSIGNMENTMONEYREQ:
            OnConsignmnetMoneyReq( pSqlMessage );
            break;
        case CS2DB_CONSIGNMENTMONEYOPERATEREQ:
            OnConsignmnetMoneyOperateReq( pSqlMessage );
            break;
        case CS2DB_SAVESYSTEMVARREQ:
            OnSaveSysVarReq( pSqlMessage );
            break;
        case CS2DB_LOADSYSTEMVARREQ:
            OnLoadSysVarReq( pSqlMessage );
            break;
        //case P2CS_ADDPAYREQ:
        //    OnP2CSAddPayReq( pSqlMessage );
        case CS2DB_UPDATEPERSONALINFOREQ:
            OnUpdatePersonalInfo( pSqlMessage );
            break;
        case GS2CS_FINDBYCONDITION:
            OnFindPerson( pSqlMessage );
            break;
		case CS2DB_FAMILYDATALOADREQ:
			OnFamilyDataLoadReq( pSqlMessage );
            break;
		case CS2DB_FAMILYDATAUPDATEREQ:
			OnFamilyDataUpdateReq( pSqlMessage );
			break;
		case CS2DB_FAMILYMEMBERUPDATEREQ:
			OnFamilyMemberUpdateReq( pSqlMessage );
			break;
		case CS2DB_FAMILYMEMBERLEAVEREQ:
			OnFamilyMemberLeaveReq( pSqlMessage );
			break;
		case CS2DB_FAMILYDISBANDREQ:
			OnFamilyDisbandReq( pSqlMessage );
			break;
		case MSG_LOADDATA_REQ:
			LoadLevelLimit(pSqlMessage);
			break;
		case MSG_ADDLEVELLIMIT:
			AddLevelLimit(pSqlMessage);
			break;
		case MSG_UPDATELEVELLIMIT:
			UpdateLevelLimit(pSqlMessage);
			break;
		case CS2GS_LOADGLOBALDBREQ:
			OnLoadGlobalDBReq(pSqlMessage);
			break;
		case CS2GS_SAVEGLOBALDBREQ:
			OnSaveGlobalDBReq(pSqlMessage);
			break;
		case CS2DB_REQUESTQUESTENTRUSTDATAREQ:
			OnRequestQuestEntrustDataReq(pSqlMessage);
			break;
		case CS2DB_ADDQUESTENTRUSTDATAACK:
			OnAddQuestEntrustDataReq(pSqlMessage);
			break;
		case CS2DB_QUESTENTRUSTDELETEREQ:
			OnDelQuestEntrustDataReq(pSqlMessage);
			break;
		case CS2DB_QUESTENTRUSTDATASAVEREQ:
			OnUpdateQuestEntrustDataReq(pSqlMessage);
			break;
		case CS2DB_LOADCAMPBATTLEDATA:
			OnLoadGameBattleDataReq(pSqlMessage);
			break;
		case CS2DB_ADDCAMPBATTLEDATA:
			OnAddGameBattleData(pSqlMessage);
			break;
		case CS2DB_DELCAMPBATTLEDATA:
			OnDelGameBattleData(pSqlMessage);
			break;

        default:
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "NormalLogicWorkThread::Update() MessageId[%d] 没有处理函数", pSqlMessage->type );
            break;
        }

        theSqlMessageManager.FreeSqlMessage( pSqlMessage );
        pSqlMessage = _dbMsgQueue.PopQuery();
    }

    _CheckState();
    return ER_Success;
}

bool NormalLogicWorkThread::WriteMountData ( SMountItem* pMount, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize);
    pMount->Write(&w);

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteMountData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }

    w.Destroy();
    return true;
}

bool NormalLogicWorkThread::WritePetData ( SPetItem* pPet, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize);
    pPet->Write(&w);

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WritePetData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }

    w.Destroy();
    return true;
}

bool NormalLogicWorkThread::WriteItemData( SCharItem* pItem, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize );

    pItem->Write(&w);

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize)
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteItemData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }
    w.Destroy();
    return true;
}

void NormalLogicWorkThread::OnQuerySaveItemDropControl( BaseSqlMessage* pSqlMessage )
{
    CS2DBSaveItemDropControl* pControl = static_cast< CS2DBSaveItemDropControl* >( pSqlMessage->GetMessageAddress() );

    for ( int i = 0; i < pControl->nCount; ++i )
    {
        char szSql[256] = { 0 };
        uint32 result = ER_Success;
        sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_itemdropcontrol where ItemID=%d", pControl->xDropInfo[i].nItemID );

        bool bExist = false;
        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
            mysqlpp::StoreQueryResult res = mysqlQuery.store();
            if ( res && !res.empty())
            { bExist = true; }
            mysqlQuery.reset();
        TRYEND

        CHECK_SQL_RESULT( result ) // 执行检测

        memset( szSql, 0, sizeof( szSql ) );
        if ( !bExist )
        {
            sprintf_s( szSql, sizeof( szSql ) - 1, "insert into t_game_itemdropcontrol(ItemID,ControlCount,DropCount) values(%d,%d,%d);", 
                pControl->xDropInfo[i].nItemID, pControl->xDropInfo[i].xControl.dwControlCount, pControl->xDropInfo[i].xControl.dwDropCount );

            TRYBEGIN
                mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
                mysqlQuery.execute( szSql );
                mysqlQuery.reset();
            TRYEND

            CHECK_SQL_RESULT( result ) // 执行检测
        }
        else
        {
            sprintf_s( szSql, sizeof( szSql ) - 1, "update t_game_itemdropcontrol set ControlCount=%d,DropCount=%d where ItemID=%d;", 
                pControl->xDropInfo[i].xControl.dwControlCount, pControl->xDropInfo[i].xControl.dwDropCount, pControl->xDropInfo[i].nItemID );

            TRYBEGIN
                mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
                mysqlQuery.execute( szSql );
                mysqlQuery.reset();
            TRYEND

            CHECK_SQL_RESULT( result ) // 执行检测
        }
    }
}

void NormalLogicWorkThread::OnQueryItemDropControlReq( BaseSqlMessage* pSqlMessage )
{
    char szSql[256] = { 0 };
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_itemdropcontrol;");

    DB2CSItemDropControl xControl;

    TRYBEGIN
    {
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty() )
        { 

            for (int i = 0; i < res.num_rows();++i )
            {
                uint16 nItemID       = res[i]["ItemID"      ];
                uint32 nControlCount = res[i]["ControlCount"];
                uint32 nDropCount    = res[i]["DropCount"   ];

                xControl.AddItemDropControl( nItemID, nControlCount, nDropCount );
                if ( xControl.IsFull() )
                {
                    theMysqlCommunication.PushAckMessage( &xControl, pSqlMessage->nClientId );

                    xControl.Reset();
                }
            }
        }
        mysqlQuery.reset();
    }
    TRYEND

    theMysqlCommunication.PushAckMessage( &xControl, pSqlMessage->nClientId );
}

void NormalLogicWorkThread::OnMsgPFAddItemReq( BaseSqlMessage* pSqlMessage )
{
    SqlMessageMsgPFAddItemReq* pDetailSqlMesage = (SqlMessageMsgPFAddItemReq*)pSqlMessage;

    MsgPFAddItemReq* pReq = &(pDetailSqlMesage->msg);

    static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

    MsgPFAddItemAck ack;
    ack.accountId = pReq->accountId;
    strncpy_s( ack.sn, sizeof(ack.sn), pReq->item.sn, sizeof(ack.sn) - 1);
    ack.itemType  = pReq->item.itemType;
    ack.itemid    = pReq->item.itemId;
    ack.itemCount = pReq->item.itemCount;

    TRYBEGIN
    {
        bool bExist = false;
        sprintf_s( szSql, sizeof( szSql ), "select account_id from platform_objects where sn='%s' and account_id=%u;", pReq->item.sn, pReq->accountId );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();        
        if ( res && !res.empty())
        { bExist = true; }
        mysqlQuery.reset();

        if ( bExist )
        {
            ack.result = MsgPFAddItemAck::ER_SnHaveExist;
            theMysqlCommunication.Push3PartyAckMessage( &ack, pSqlMessage->nClientId );
            return;
        }

        strncpy_s( szSql, sizeof( szSql ), "insert into platform_objects(sn,account_id,object_type,object_id,object_count,status,value_1,value_2,value_3,value_4,value_5,value_6,value_7,value_8,value_9,value_10) values(%1q,%0,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15);", sizeof(szSql)-1);
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_int_unsigned(pReq->accountId), pReq->item.sn, pReq->item.itemType, pReq->item.itemId, pReq->item.itemCount, 1, pReq->item.value[0], pReq->item.value[1], pReq->item.value[2], pReq->item.value[3], pReq->item.value[4], pReq->item.value[5], pReq->item.value[6], pReq->item.value[7], pReq->item.value[8], pReq->item.value[9] );
        mysqlQuery.reset();
    }
    TRYEND

    // 执行失败
    if ( RESULT_FAILED(result))
    { return; }

    ack.result = MsgPFAddItemAck::ER_Success;
    theMysqlCommunication.Push3PartyAckMessage( &ack, pSqlMessage->nClientId );
}


void NormalLogicWorkThread::OnGS2CSMailListReq( BaseSqlMessage* pSqlMessage )
{
    SqlMessageGS2CSMailListReq* pDetailSqlMesage = (SqlMessageGS2CSMailListReq*)pSqlMessage;

    GS2CSMailListReq* pReq = &(pDetailSqlMesage->msg);

    static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

    CS2GSMailListAck msg;
    msg.accountId = pReq->accountId;
    msg.charDbId  = pReq->charDbId;
    
    TRYBEGIN
    {
        sprintf_s( szSql, sizeof( szSql ), "select * from mails where char_id=%u and (datediff(now(),send_time)<=7) order by send_time desc limit %d;", pReq->charDbId, EM_MailMaxCount );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();        
        if ( res && !res.empty())
        {
            for (int i=0; i < res.num_rows();++i )
            {
                msg.mails[msg.count].id    = res[i]["id"];
                msg.mails[msg.count].type  = mysqlpp::sql_smallint(res[i]["type"]);
                msg.mails[msg.count].state = mysqlpp::sql_smallint(res[i]["state"]);

                Common::_tstring strTitle;
                strTitle.fromUTF8( res[i]["title"] );
                strncpy_s( msg.mails[msg.count].title, sizeof(msg.mails[msg.count].title), strTitle.c_str(), sizeof(msg.mails[msg.count].title)-1 );

                char szTempOwnerId[64] = {0};
                char szTempOwnerName[64] = {0};
                for ( int y=0; y<EM_OwnerMaxCount; ++y )
                {
                    sprintf_s( szTempOwnerId, "owner_id_%d", y );
                    sprintf_s( szTempOwnerName, "owner_name_%d", y );

                    msg.mails[msg.count].owners[y].charDbId    = res[i][szTempOwnerId];
					
					if(strlen(res[i][szTempOwnerName]) > 0)
					{
						Common::_tstring strTempOwnerName;
						strTempOwnerName.fromUTF8( res[i][szTempOwnerName] );
						strncpy_s( msg.mails[msg.count].owners[y].addressName, EM_AddressNameSize, strTempOwnerName.c_str(), strlen(strTempOwnerName.c_str()) );                    
					}
                }

                Common::_tstring strContent;
                strContent.fromUTF8( res[i]["content"] );
                strncpy_s( msg.mails[msg.count].content, sizeof(msg.mails[msg.count].content), strContent.c_str(), sizeof(msg.mails[msg.count].content)-1 );    
                msg.mails[msg.count].money = res[i]["money"];
                msg.mails[msg.count].sendTime = mysqlpp::DateTime( res[i]["send_time"] );
                msg.mails[msg.count].accessory.type = res[i]["accessory_type"];

                static uint8 bufferDecodeField[ 1024 * 40 ] = {0};
                static uint8 bufferTempUnZip  [ 1024 * 40 ] = {0};
                uint32 unZipBufferSize = sizeof( bufferTempUnZip );

                switch ( msg.mails[msg.count].accessory.type )
                {
                case SMail::EAT_Item:
                    {
                        SCharItem ItemTemp;
                        uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[i]["accessory_content"].c_str(), bufferDecodeField, sizeof(bufferDecodeField));
                        unZipBufferSize = sizeof( bufferTempUnZip );;
                        uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeBufferActualSize );
                        ItemTemp.Read( bufferTempUnZip, unZipBufferSize );
                        memcpy_s( msg.mails[msg.count].accessory.content, EM_MailAccessorySize, &ItemTemp, EM_MailAccessorySize );
                    }
                	break;
                case SMail::EAT_Mount:
                    {
                        SMountItem mountTemp;
                        memset( &mountTemp, 0, sizeof(SMountItem));
                        mountTemp.baseInfo.id = InvalidLogicNumber;
                        int32 nDecodeBufferActualSize = DeCodeToBuffer( res[i]["accessory_content"], bufferDecodeField, sizeof(bufferDecodeField) );
                        unZipBufferSize = sizeof( bufferTempUnZip );;
                        uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeBufferActualSize );        
                        mountTemp.Read( bufferTempUnZip, unZipBufferSize );

                        memcpy_s( msg.mails[msg.count].accessory.content, EM_MailAccessorySize, &mountTemp, EM_MailAccessorySize );
                    }
                    break;
                case SMail::EAT_Pet:
                    {
                        SPetItem petTemp;
                        memset( &petTemp, 0, sizeof(SPetItem));
                        petTemp.baseInfo.petId = InvalidLogicNumber;
                        int32 nDecodeBufferActualSize = DeCodeToBuffer( res[i]["accessory_content"], bufferDecodeField, sizeof(bufferDecodeField) );
                        unZipBufferSize = sizeof( bufferTempUnZip );;
                        uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeBufferActualSize );        
                        petTemp.Read( bufferTempUnZip, unZipBufferSize );

                        memcpy_s( msg.mails[msg.count].accessory.content, EM_MailAccessorySize, &petTemp, EM_MailAccessorySize );
                    }
                    break;
                default:
                    {
                        memset( msg.mails[msg.count].accessory.content, 0, EM_MailAccessorySize );
                    }
                    break;
                }

                ++msg.count;
               /* if ( msg.count == EM_MailMaxCount)
                {   
                    msg.RecalLength();
                    theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
                    msg.Reset();
                    msg.isnew = 0;
                }*/
            }
        }
        mysqlQuery.reset();

        msg.RecalLength();
		theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
    }
    TRYEND

    // 执行失败
    if ( RESULT_FAILED(result))
    { return; }
}

void NormalLogicWorkThread::OnGS2CSQueryMailCanSendReq( BaseSqlMessage* pSqlMessage )
{
    SqlMessageGS2CSQueryMailCanSendReq* pDetailSqlMesage = (SqlMessageGS2CSQueryMailCanSendReq*)pSqlMessage;

    GS2CSQueryMailCanSendReq* pReq = &(pDetailSqlMesage->msg);

    static char szSql[ 1024 ] = {0}; 
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

    CS2GSQueryMailCanSendAck msg;
    msg.result    = ER_Success;
    msg.charDbId  = pReq->charDbId;

    TRYBEGIN
        for ( int i=0; i<EM_TargetMaxCount; ++i )
        {
            if ( pReq->targets[i].charDbId == 0)
            { break; }
            
            bool bExitChar = false;
            sprintf_s( szSql, sizeof( szSql ), "select characterid from t_game_character where characterid=%u;", pReq->targets[i].charDbId );
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql );
            if ( res && !res.empty())
            { bExitChar = true; }
            mysqlQuery.reset();

            if ( !bExitChar )
            {
                msg.result = ER_MailTargetQueryFail;
                msg.targets[i].result = SMail::ETAR_TargetNotExit;
                memcpy_s( &msg.targets[i].address, sizeof(msg.targets[i].address), &pReq->targets[i], sizeof(msg.targets[i].address) );
                break;
            }
            
            sprintf_s( szSql, sizeof( szSql ), "select count(1) from mails where char_id=%u and (datediff(now(),send_time)<=7);", pReq->targets[i].charDbId );
            res = mysqlQuery.store( szSql  );
            if ( res && !res.empty())
            {
                uint16 count = res[0][0];
                mysqlQuery.reset();

                if ( count >= EM_MailMaxCount )
                {
                    msg.result = ER_MailTargetQueryFail;
                    msg.targets[i].result = SMail::ETAR_TargetMailFull;
                    memcpy_s( &msg.targets[i].address, sizeof(msg.targets[i].address), &pReq->targets[i], sizeof(msg.targets[i].address) );
                    break;
                }
            }
        }
    TRYEND

    // 执行失败
    if ( RESULT_FAILED(result))
    { msg.result = result; }

    theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
}

void NormalLogicWorkThread::OnGS2CSSendMailReq( BaseSqlMessage* pSqlMessage )
{
    SqlMessageGS2CSSendMailReq* pDetailSqlMesage = (SqlMessageGS2CSSendMailReq*)pSqlMessage;

    GS2CSSendMailReq* pReq = &(pDetailSqlMesage->msg);

    static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

    CS2GSSendMailAck msg;
    msg.result    = ER_Success;
    msg.accountId  = pReq->accountId;
    msg.charDbId   = pReq->charDbId;
    memcpy_s( &msg.mail, sizeof(msg.mail), &pReq->mail, sizeof(msg.mail));

    TRYBEGIN
        for ( int i=EM_ToIndex; i<EM_OwnerMaxCount; ++i )
        {   
            if ( pReq->mail.owners[i].charDbId == 0)
            { break; }

			uint8 accessoryType(0);
			DWORD sendMoney(0);
			DWORD AccessoryId(0);
			int64 AccessoryGUID(0);
			DWORD AccessoryCount(0);
            bool bExitChar = false;
            strncpy_s( szSql, sizeof( szSql ), "insert into mails(char_id,type,state,title,owner_id_0,owner_name_0,"
                "owner_id_1,owner_name_1,owner_id_2,owner_name_2,owner_id_3,owner_name_3,owner_id_4,owner_name_4,"
                "owner_id_5,owner_name_5,owner_id_6,owner_name_6,owner_id_7,owner_name_7,content,money,accessory_type,accessory_content,accessory_id,send_time)"
                "values(%0,%1,%2,%3q,%4,%5q,%6,%7q,%8,%9q,%10,%11q,%12,%13q,%14,%15q,%16,%17q,%18,%19q,%20q,%21,%22,%23q,%24,now());",sizeof(szSql)-1);

            static uint8 bufferItemDataChunk[ 1024 * 40 ] = {0};
            static uint8 bufferTempZipItem  [ 1024 * 40 ] = {0};
            static int8  bufferItemDataField[ 1024 * 10 ] = {0};
			
			//收信人才得到附件
			if(i == EM_ToIndex)
			{
				accessoryType  = pReq->mail.accessory.type;
				switch( pReq->mail.accessory.type )
				{
				case SMail::EAT_Item:
					{
						SCharItem* pItem = (SCharItem*)pReq->mail.accessory.content;
						AccessoryId = pItem->itembaseinfo.ustItemID;
						AccessoryGUID = pItem->itembaseinfo.nOnlyInt;
						AccessoryCount = pItem->itembaseinfo.ustItemCount;
						uint32 zipBufferSize = sizeof(bufferTempZipItem);
						uint32 nActualSize = 0;
						if (!WriteItemData( pItem, nActualSize, bufferItemDataChunk, sizeof(bufferItemDataChunk) ))
						{ 
							msg.result    = ER_Failed;
							theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
							return;
						}
						compress( bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
						EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, sizeof(bufferItemDataField) );
					}
					break;
				case SMail::EAT_Mount:
					{
						SMountItem* pMountItem = (SMountItem*)pReq->mail.accessory.content;
						AccessoryId = pMountItem->baseInfo.id;
						AccessoryGUID = pMountItem->baseInfo.guid;
						AccessoryCount = 1;
						uint32 compressBufferSize = sizeof(bufferTempZipItem);
						uint32 nActualSize = 0;
						if ( !WriteMountData( pMountItem, nActualSize,bufferItemDataChunk, sizeof(bufferItemDataChunk) ) )
						{
							msg.result    = ER_Failed;
							theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
							return;
						}
						compress( bufferTempZipItem,(uLongf*)&compressBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
						EnCodeToString( bufferTempZipItem, bufferItemDataField, compressBufferSize, sizeof(bufferItemDataField));
					}
					break;
                case SMail::EAT_Pet:
                    {
                        SPetItem* pPetItem = (SPetItem*)pReq->mail.accessory.content;
						AccessoryId = pPetItem->baseInfo.petId;
						AccessoryGUID = pPetItem->baseInfo.guid;
						AccessoryCount = 1;
                        uint32 compressBufferSize = sizeof(bufferTempZipItem);
                        uint32 nActualSize = 0;
                        if ( !WritePetData( pPetItem, nActualSize,bufferItemDataChunk, sizeof(bufferItemDataChunk) ) )
                        {
                            msg.result    = ER_Failed;
                            theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
                            return;
                        }
                        compress( bufferTempZipItem,(uLongf*)&compressBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
                        EnCodeToString( bufferTempZipItem, bufferItemDataField, compressBufferSize, sizeof(bufferItemDataField));
                    }
                    break;
				default:
					memset( bufferItemDataField, 0, sizeof(bufferItemDataField));
					break;
				}
				sendMoney = pReq->mail.money;
			}
			else
			{
				//抄送者都不获得附件
				sendMoney = 0;
				accessoryType = SMail::EAT_None;
				memset( bufferItemDataField, 0, sizeof(bufferItemDataField));
			}
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pReq->mail.owners[i].charDbId),pReq->mail.type,pReq->mail.state, _tUTF8CHAR(pReq->mail.title),
                mysqlpp::sql_int_unsigned(pReq->mail.owners[0].charDbId),_tUTF8CHAR(pReq->mail.owners[0].addressName),
                mysqlpp::sql_int_unsigned(pReq->mail.owners[1].charDbId),_tUTF8CHAR(pReq->mail.owners[1].addressName),
                mysqlpp::sql_int_unsigned(pReq->mail.owners[2].charDbId),_tUTF8CHAR(pReq->mail.owners[2].addressName),
                mysqlpp::sql_int_unsigned(pReq->mail.owners[3].charDbId),_tUTF8CHAR(pReq->mail.owners[3].addressName),
                mysqlpp::sql_int_unsigned(pReq->mail.owners[4].charDbId),_tUTF8CHAR(pReq->mail.owners[4].addressName),
                mysqlpp::sql_int_unsigned(pReq->mail.owners[5].charDbId),_tUTF8CHAR(pReq->mail.owners[5].addressName),
                mysqlpp::sql_int_unsigned(pReq->mail.owners[6].charDbId),_tUTF8CHAR(pReq->mail.owners[6].addressName),
                mysqlpp::sql_int_unsigned(pReq->mail.owners[7].charDbId),_tUTF8CHAR(pReq->mail.owners[7].addressName), _tUTF8CHAR(pReq->mail.content),
				mysqlpp::sql_int_unsigned(sendMoney), accessoryType, bufferItemDataField,mysqlpp::sql_int_unsigned(AccessoryId));
            mysqlQuery.reset();
        }
    TRYEND

    // 执行失败
    if ( RESULT_FAILED(result))
    { msg.result = result; }

    theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
}

void NormalLogicWorkThread::OnGS2CSOpMailReq( BaseSqlMessage* pSqlMessage )
{
    SqlMessageGS2CSOpMailReq* pDetailSqlMesage = (SqlMessageGS2CSOpMailReq*)pSqlMessage;

    GS2CSOpMailReq* pReq = &(pDetailSqlMesage->msg);

    static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

    CS2GSOpMailAck msg;
    msg.result    = ER_Success;
    msg.op        = pReq->op;
    msg.accountId = pReq->accountId;
    msg.charDbId  = pReq->charDbId;
    msg.mailId    = pReq->mailId;
    
    TRYBEGIN
        bool bExitMail = false;
        sprintf_s( szSql, sizeof( szSql ), "select 1 from mails where char_id=%u and id=%u;", msg.charDbId, msg.mailId,sizeof( szSql ) - 1 );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql );
        if ( res && !res.empty())
        { bExitMail = true; }
        mysqlQuery.reset();

        if ( !bExitMail )
        {
            msg.result = ER_MailNotExit;
            theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
            return;
        }

        switch ( msg.op )
        {
        case EMO_Delete:
            { // 删除邮件
                strncpy_s( szSql, sizeof( szSql ), "delete from mails where char_id=%0 and id=%1;",sizeof( szSql ) - 1 );
                mysqlQuery << szSql;
                mysqlQuery.parse();
                mysqlQuery.execute( mysqlpp::sql_int_unsigned(msg.charDbId),mysqlpp::sql_int_unsigned(msg.mailId));
                mysqlQuery.reset();
            }
            break;
        case EMO_Open:
            {
                strncpy_s( szSql, sizeof( szSql ), "update mails set state=%3 where char_id=%0 and id=%1 and state=%2;",sizeof( szSql ) - 1 );
                mysqlQuery << szSql;
                mysqlQuery.parse();
                mysqlQuery.execute( mysqlpp::sql_int_unsigned(msg.charDbId),mysqlpp::sql_int_unsigned(msg.mailId), SMail::EMS_NotOpen, SMail::EMS_Open );
                mysqlQuery.reset();
            }
            break;
        case EMO_GetMoney:
            {
                bool bExitMail = false;
                sprintf_s( szSql, sizeof( szSql ), "select money from mails where char_id=%u and id=%u and owner_id_1=%u", msg.charDbId, msg.mailId, msg.charDbId );
                mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql );
                if ( res && !res.empty())
                {
                    msg.money = res[0][0];
                    bExitMail = true; 
                }
                mysqlQuery.reset();

                if ( !bExitMail)
                {
                    msg.result    = ER_MailNotExit;
                    theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
                    return;
                }
                strncpy_s( szSql, sizeof( szSql ), "update mails set money=0 where char_id=%0 and id=%1;",sizeof( szSql ) - 1 );
                mysqlQuery << szSql;
                mysqlQuery.parse();
                mysqlQuery.execute( mysqlpp::sql_int_unsigned(msg.charDbId),mysqlpp::sql_int_unsigned(msg.mailId) );
                mysqlQuery.reset();
            }
            break;
        case EMO_GetAccessory:
            {
                bool bExitMail = false;
                sprintf_s( szSql, sizeof( szSql ), "select state,accessory_type,accessory_content from mails where char_id=%u and id=%u and owner_id_1=%u", msg.charDbId, msg.mailId, msg.charDbId );
                mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql );
                if ( res && !res.empty())
                {   
                    uint8 state = res[0]["state"];
                    
                    switch ( state )
                    {
                    case SMail::EMS_HaveGetItem:
                        {
                            msg.result    = ER_MailItemHaveGet;
                            theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
                        }
                    	break;
                    }
                    msg.accessory.type = res[0]["accessory_type"];

                    static uint8 bufferDecodeField[ 1024 * 40 ] = {0};
                    static uint8 bufferTempUnZip  [ 1024 * 40 ] = {0};
                    uint32 unZipBufferSize = sizeof( bufferTempUnZip );

                    switch ( msg.accessory.type )
                    {
                    case SMail::EAT_Item:
                        {
                            SCharItem ItemTemp;
                            uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[0]["accessory_content"].c_str(), bufferDecodeField, sizeof(bufferDecodeField));
                            unZipBufferSize = sizeof( bufferTempUnZip );;
                            uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeBufferActualSize );
                            ItemTemp.Read( bufferTempUnZip, unZipBufferSize );
                            memcpy_s( msg.accessory.content, EM_MailAccessorySize, &ItemTemp, EM_MailAccessorySize );
                        }
                        break;
                    case SMail::EAT_Mount:
                        {
                            SMountItem mountTemp;
                            memset( &mountTemp, 0, sizeof(SMountItem));
                            mountTemp.baseInfo.id = InvalidLogicNumber;
                            int32 nDecodeBufferActualSize = DeCodeToBuffer( res[0]["accessory_content"], bufferDecodeField, sizeof(bufferDecodeField) );
                            unZipBufferSize = sizeof( bufferTempUnZip );;
                            uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeBufferActualSize );        
                            mountTemp.Read( bufferTempUnZip, unZipBufferSize );

                            memcpy_s( msg.accessory.content, EM_MailAccessorySize, &mountTemp, EM_MailAccessorySize );
                        }
                        break;
                    case SMail::EAT_Pet:
                        {
                            SPetItem petTemp;
                            memset( &petTemp, 0, sizeof(SPetItem));
                            petTemp.baseInfo.petId = InvalidLogicNumber;
                            int32 nDecodeBufferActualSize = DeCodeToBuffer( res[0]["accessory_content"], bufferDecodeField, sizeof(bufferDecodeField) );
                            unZipBufferSize = sizeof( bufferTempUnZip );;
                            uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeBufferActualSize );        
                            petTemp.Read( bufferTempUnZip, unZipBufferSize );

                            memcpy_s( msg.accessory.content, EM_MailAccessorySize, &petTemp, EM_MailAccessorySize );
                        }
                        break;
                    default:
                        {
                            memset( msg.accessory.content, 0, EM_MailAccessorySize );
                        }
                        break;
                    }
                    msg.RecalLength();
                    bExitMail = true; 
                }
                mysqlQuery.reset();

                if ( !bExitMail)
                {
                    msg.result    = ER_MailNotExit;
                    theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
                    return;
                }


                strncpy_s( szSql, sizeof( szSql ), "update mails set state=%2 where char_id=%0 and id=%1;",sizeof( szSql ) - 1 );
                mysqlQuery << szSql;
                mysqlQuery.parse();
                mysqlQuery.execute( mysqlpp::sql_int_unsigned(msg.charDbId),mysqlpp::sql_int_unsigned(msg.mailId),SMail::EMS_HaveGetItem );
                mysqlQuery.reset();
            }
            break;
        }
    TRYEND

    // 执行失败
    if ( RESULT_FAILED(result))
    { msg.result = result; }

    theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
}

#pragma warning( pop )