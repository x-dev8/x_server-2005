#include "NormalLogicWorkThread.h"
#include "DatabaseServerApp.h"
#include "zlib/zlib.h"
#include "RoleDataCache.h"
#include "FileDatabase.h"
#include "AccountBillingDefine.h"

NormalLogicWorkThread::NormalLogicWorkThread( MySqlCommunication* pOwn ) : MySqlWorkThread(pOwn),_bHaveLoadGmInfo(false)
{
}

uint32 NormalLogicWorkThread::Update()
{
    // 保存基本的 Sql连接 和 Update
    if ( MySqlWorkThread::Update() == ER_SqlNotConnected )
    { return ER_Success; }

    _TryLoadGmInfo();

    BaseSqlMessage* pSqlMessage = _dbMsgQueue.PopQuery();
    while ( pSqlMessage != NULL)
    {
        switch( pSqlMessage->type )
        {
        case DBMSG_CREATECHAR://GS TO DB 创建角色
            {
                BEGINFUNCPERLOG("OnQueryCreateChar")
                OnQueryCreateChar( pSqlMessage );
                ENDFUNCPERLOG("OnQueryCreateChar")
            }
            break;
        case DBMSG_REQ_CREATE_CHECKNAME://GS TO DB 检测名字
            {
                OnQueryCreateCheckName( pSqlMessage );
            }
            break;
		case DBMSG_CHANGENAMEREQ://GS TO DB 修改角色名
			{
				OnQueryChangeName( pSqlMessage );
			}
			break;
        case DBMSG_QUERYACCOUNTCHAR://GS TO DB 请求账号下的角色
            {
                BEGINFUNCPERLOG("OnQueryCharEnterWorld")
                OnQueryAccountChar( pSqlMessage );
                ENDFUNCPERLOG("OnQueryCharEnterWorld")
            }
            break;
        case DBMSG_ENTERWORD://GS TO DB 进入游戏
            {
                BEGINFUNCPERLOG("OnQueryCharEnterWorld")
                OnQueryCharEnterWorld( pSqlMessage );
                ENDFUNCPERLOG("OnQueryCharEnterWorld")
            }
            break;
        case DBMSG_SAVECHARACTER://GS TO DB 保存角色
            {
                BEGINFUNCPERLOG("OnQuerySaveChar")
                OnQuerySaveChar( pSqlMessage );
                ENDFUNCPERLOG("OnQuerySaveChar")
            }
            break;
        case DBMSG_DELETECHAR://GS TO DB 删除角色
            {
                OnQueryDelChar( pSqlMessage );
            }
            break;
        case DBMSG_CANCELDELCHAR://GS TO DB 恢复删除的角色
            {
                OnQueryCancelDelChar( pSqlMessage );
            }
            break;
        case DBMSG_PETBREEDQUERYREQ://GS TO DB 请求宝宝繁殖
            {
                OnQueryPetBreed( pSqlMessage );
            }
            break;
		case GS2DB_UPDATEYUANBAODATA://GS TO DB 什么元宝状态 不清楚
			{
				OnUpdateAccountYuanBao( pSqlMessage );
			}
			break;
		case GS2DB_UPDATEPLAYERPOINT:
			{
				//处理玩家点数
				OnUpdatePlayerPoint( pSqlMessage );
			}
			break;
        default:
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "NormalLogicWorkThread::Update() MessageId[%d:%d] 没有处理函数", pSqlMessage->type, pSqlMessage->GetMessageSize() );
            break;
        }

        theSqlMessageManager.FreeSqlMessage( pSqlMessage );
        pSqlMessage = _dbMsgQueue.PopQuery();
    }

    _CheckState();
    return ER_Success;
}

bool NormalLogicWorkThread::LoadItems( const uint32 dwCharacterId, SCharItem* pItem, const int nBagSize ,int nBagPos )
{
    char szSql[512] = {0};
    memset( szSql, 0, sizeof(szSql));
    uint32 result = ER_Success;

    switch ( nBagPos )
    {
    case e_CharBag:
    case e_StroageBag:
    case e_MaterialBag:
    case e_TaskBag:
        sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_item where (CharacterId=%ld) and WhoIs=%d;", dwCharacterId, nBagPos );
        break;
    default:
        return false;
    }

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query(szSql);        
        mysqlpp::StoreQueryResult res = mysqlQuery.store();

        int nIndex = 0;
        for( int i=0; i<nBagSize; ++i)
        {
            pItem[i].itembaseinfo.ustItemID = InvalidLogicNumber;
            pItem[i].itembaseinfo.nOnlyInt  = 0;
        }

        if ( res && !res.empty())
        {
            for (int i = 0; i < res.num_rows();++i )
            {
                nIndex = res[i]["BagIndex"];
                if (nIndex > nBagSize)
                { continue; }

                SCharItem ItemTemp;
                memset( &ItemTemp, 0, sizeof(SCharItem));
                ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;

                static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
                static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

                memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
                memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

                // itemdata
                uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
                uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[i]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
                uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
                ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );

                if (pItem[nIndex].itembaseinfo.ustItemID != InvalidLogicNumber)
                {
                    for (int n = 0; n<nBagSize ; n++)
                    {
                        if (pItem[n].itembaseinfo.ustItemID == InvalidLogicNumber)
                        {
                            memcpy(&pItem[n],&ItemTemp,sizeof(SCharItem));
                            break;
                        }
                    }
                }
                else
                {
                    memcpy(&pItem[nIndex],&ItemTemp,sizeof(SCharItem));
                }
            }
        }
        mysqlQuery.reset();
    TRYEND

    if ( RESULT_FAILED(result))
    { return false; }

    return true;
}

bool NormalLogicWorkThread::LoadMount( uint32 dwCharacterId, SMountItem* pMountItem, int nCount ,int nBagPos )
{
    char szSql[1024] = {0};
    memset( szSql, 0, sizeof(szSql));
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_mount where (CharacterId=%ld) and WhereIs=%d;", dwCharacterId, nBagPos );

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
        mysqlpp::StoreQueryResult res = mysqlQuery.store();

        if ( res && !res.empty())
        {
            if (nBagPos == e_CharBag)
            {
                if ( nCount>ITEM_MOUNT_MAXCOUNT)
                { nCount = ITEM_MOUNT_MAXCOUNT; }
            }

            for( int i=0; i<nCount; ++i) 
            {
                pMountItem[i].baseInfo.id       = InvalidLogicNumber;
                pMountItem[i].baseInfo.guid     = 0;
                pMountItem[i].baseInfo.isActive = 0;
            }

            for (int i = 0; i < res.num_rows(); ++i )
            {
                SMountItem mountTemp;
                memset( &mountTemp, 0, sizeof(SMountItem));
                mountTemp.baseInfo.id = InvalidLogicNumber;

                // datainfo
                static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
                static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item ]   = {0};

                int32 nDecodeBufferActualSize = DeCodeToBuffer( res[i]["DataInfo"], bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Item );
                uint32 unZipBufferSize        = CharChunkWR::CD_UnZipTempBufferSize_Item;
                uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeBufferActualSize );        
                mountTemp.Read( bufferTempUnZip, unZipBufferSize );

                if (mountTemp.baseInfo.id == InvalidLogicNumber)
                {
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CharacterId[%ld] 读坐骑  Row[%d] BagPos[%d]  数据出错", dwCharacterId, i, nBagPos );
                    continue;
                }

                for (int nloop = 0; nloop < nCount; ++nloop)
                {
                    if (pMountItem[nloop].baseInfo.id == InvalidLogicNumber)
                    {
                        memcpy(&pMountItem[nloop], &mountTemp,sizeof(SMountItem));
                        break;
                    }
                }
            }
        }
        mysqlQuery.reset();
    TRYEND

    // 执行失败
    if ( RESULT_FAILED(result))
    { return false; }

    return true;
}

bool NormalLogicWorkThread::LoadPets( uint32 dwCharacterId, SPetItem* pPetItem, int nCount ,int nBagPos )
{
    char szSql[1024] = {0};
    memset( szSql, 0, sizeof(szSql));
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_pet where (CharacterId=%ld) and WhereIs=%d;", dwCharacterId, nBagPos );

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
        mysqlpp::StoreQueryResult res = mysqlQuery.store();

        if ( res && !res.empty())
        {
            if (nBagPos == e_CharBag)
            {
                if ( nCount > ITEM_PET_MAXCOUNT )
                { nCount = ITEM_PET_MAXCOUNT; }
            }

            for( int i=0; i<nCount; ++i) 
            {
                pPetItem[i].baseInfo.petId    = InvalidLogicNumber;
                pPetItem[i].baseInfo.guid     = 0;
                pPetItem[i].baseInfo.isActive = 0;
            }

            for (int i = 0; i < res.num_rows(); ++i )
            {
                SPetItem petTemp;
                memset( &petTemp, 0, sizeof(SPetItem));
                petTemp.baseInfo.petId = InvalidLogicNumber;

                // datainfo
                static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
                static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item ]   = {0};

                int32 nDecodeBufferActualSize = DeCodeToBuffer( res[i]["DataInfo"], bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Item );
                uint32 unZipBufferSize        = CharChunkWR::CD_UnZipTempBufferSize_Item;
                uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeBufferActualSize );        
                petTemp.Read( bufferTempUnZip, unZipBufferSize );

                if (petTemp.baseInfo.petId == InvalidLogicNumber)
                {
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CharacterId[%ld] 读取宠物  Row[%d] BagPos[%d]  数据出错", dwCharacterId, i, nBagPos );
                    continue;
                }

                for (int nloop = 0; nloop < nCount; ++nloop)
                {
                    if (pPetItem[nloop].baseInfo.petId == InvalidLogicNumber)
                    {
                        memcpy(&pPetItem[nloop], &petTemp,sizeof(SPetItem));
                        break;
                    }
                }
            }
        }
        mysqlQuery.reset();
    TRYEND

    // 执行失败
    if ( RESULT_FAILED(result))
    { return false; }

    return true;
}

void NormalLogicWorkThread::_TryLoadGmInfo()
{
    if ( !_bHaveLoadGmInfo )
    {
        gmlist.clear();

        char szSql[1024] = {0};
        uint32 result = ER_Success;
        memset( szSql, 0, sizeof(szSql));
        sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_gminfo");

        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
            mysqlpp::StoreQueryResult res = mysqlQuery.store();

            if ( res && !res.empty())
            {
                for (int i = 0; i < res.num_rows();++i )
                {
                    GMINFO info = {0};
                    Common::_tstring strName;
                    strName.fromUTF8( res[i]["RoleName"] );
                    info.nLevel = res[i]["GMLevel"];
                    strncpy_s( info.szIP, sizeof( info.szIP ), res[i]["IPAddress"], sizeof( info.szIP ) - 1 );
                    gmlist.insert( GmContainer::value_type(strName, info));
                }
            }
        TRYEND

        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Loaded %d gm charater", gmlist.size());
        _bHaveLoadGmInfo = true;
    }
}

void NormalLogicWorkThread::OnQueryCreateChar( BaseSqlMessage* pSqlMessage )
{
	int MAX_PLAYER_COUNT = 3;
    SqlMessageDBMsgCreateHeroChar* pDetailSqlMessage = (SqlMessageDBMsgCreateHeroChar*)pSqlMessage;
    DBMsgCreateHeroChar* pCreate = &pDetailSqlMessage->msg;

    static char szSql[ 1024 * 60 ] = {0};
    memset( szSql, 0, sizeof(szSql));
    uint32 result = ER_Success;
    
    // 检查是否含有单引号或是减号
    if ( !CheckCreateName(pCreate->charinfo.baseinfo.aptotic.szCharacterName) )
    {
        DBMsgAckCreateCheckName ackcheck;
        ackcheck.bResult = false;
        theMysqlCommunication.PushAckMessage( &ackcheck, pSqlMessage->nClientId );
        return;
    }
    
    sprintf_s( szSql, sizeof( szSql ) - 1, "select AccountId from t_game_character where CharName='%s';", _tUTF8CHAR(pCreate->charinfo.baseinfo.aptotic.szCharacterName) );

    bool bExistChar = false;
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
        mysqlpp::StoreQueryResult res = mysqlQuery.store();

        if ( res && !res.empty())
        { bExistChar = true; }
    TRYEND

    DBMsgCreateCharAck ack;
    ack.subMarker   = pCreate->subMarker;
    ack.accountId   = pCreate->accoundId;
    ack.shServerId  = pCreate->shServerId;
    ack.header.stID = pCreate->header.stID;    
    ack.ustLifeCode = pCreate->ustLifeCode;
    strncpy_s( ack.charName, sizeof(ack.charName), pCreate->charinfo.baseinfo.aptotic.szCharacterName, sizeof(ack.charName)-1);

    // 执行失败
    if ( RESULT_FAILED(result))
    {
        ack.result = ER_Failed;
        goto FinalProcess;
    }
    
    // 检测该位置是否已经存在人物
    if ( bExistChar )
    { ack.result = ER_CharNameHaveExist; }
    else
    {
        if (true)
        { // 做whickSlot逻辑
            //uint8 slotIn[More_iCharPerAccount] = {0};
            int16 slotIndex = -1;
            //memset( slotIn, 0, sizeof(slotIn));
			int16 Maxslot = -1;
            if(GetDatabaseServerApp()->m_bUseCancelDel)
            { sprintf_s( szSql, sizeof( szSql ) - 1, "select CharSlot from t_game_character where AccountId=%ld and (IsDel=0 or (IsDel=1 and datediff(now(),DelTime)<= 7));", pCreate->accoundId  ); }
            else
            { sprintf_s( szSql, sizeof( szSql ) - 1, "select CharSlot from t_game_character where AccountId=%ld and IsDel=0;", pCreate->accoundId ); }

            TRYBEGIN
                mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
                mysqlpp::StoreQueryResult res = mysqlQuery.store();
				if(res && res.num_rows() >= MAX_PLAYER_COUNT)
				{
					ack.result = ER_Failed;
					goto FinalProcess;
				}
                if ( res && !res.empty())
                {
                    for ( size_t i=0; i<res.num_rows(); ++i )
                    {
                        int16 slot = res[i][0];
                        /*if ( slot>= More_iCharPerAccount )
                        { continue; }*/

                       // slotIn[slot] = 1;
						if(Maxslot <= slot)
							Maxslot = slot; 
                    }
                }
            TRYEND
            
            if ( RESULT_FAILED(result) )
            { // 执行失败=
                ack.result = ER_Failed;
                goto FinalProcess;
            }

            /*for ( size_t i=0; i<More_iCharPerAccount; ++i)
            {
                if ( 0 == slotIn[i] )
                {
                    slotIndex = i;
                    break;
                }
            }*/
			slotIndex = Maxslot +1;
            // 是否有合适的位置
            if ( slotIndex >= 0  )
            { pCreate->stWhichSlot = slotIndex; }
            else
            {
                ack.result = ER_CharSlotFull;
                goto FinalProcess;
            }
        }

        ack.stWhichSlot = pCreate->stWhichSlot;

        sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_character where AccountId=%ld and IsDel=0 and CharSlot=%d;", pCreate->accoundId, pCreate->stWhichSlot);

        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
            mysqlpp::StoreQueryResult res = mysqlQuery.store();

            if ( res && !res.empty())
            { bExistChar = true; }
            mysqlQuery.reset();
        TRYEND
        
        // 执行失败
        if ( RESULT_FAILED(result) || bExistChar )
        {
            DBMsgAckCreateCheckName ackcheck;
            ackcheck.bResult = false;
            theMysqlCommunication.PushAckMessage( &ackcheck, pSqlMessage->nClientId );
            return; 
        }

        // 需要存放压缩过后的字符
        static uint8 bufferTempZip[ CharChunkWR::CD_ZipTempBufferSize ] = {0};

        static uint8 bufferBaseInfoChunk    [ CharChunkWR::CD_CharBaseInfoBufferSize ] = {0};
        static uint8 bufferVisualInfoChunk  [ CharChunkWR::CD_VisualInfoBufferSize   ] = {0};
        static uint8 bufferOtherDataChunk   [ CharChunkWR::CD_OtherInfoBufferSize    ] = {0};
        static uint8 bufferExtendDataChunk  [ CharChunkWR::CD_ExtendInfoBufferSize   ] = {0};
        static uint8 bufferAchieveDataChunk [ CharChunkWR::CD_AchieveDataBufferSize  ] = {0};
        static uint8 bufferIdentifyDataChunk[ CharChunkWR::CD_IdentifyDataBufferSize ] = {0};

        static int8 bufferBaseInfoField     [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};
        static int8 bufferVisualInfoField   [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};
        static int8 bufferOtherDataField    [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};
        static int8 bufferExtendDataField   [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};
        static int8 bufferAchieveDataField  [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};
        static int8 bufferIdentifyDataField [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};

        memset( bufferBaseInfoChunk,    0, CharChunkWR::CD_CharBaseInfoBufferSize);
        memset( bufferVisualInfoChunk,  0, CharChunkWR::CD_VisualInfoBufferSize);
        memset( bufferOtherDataChunk,   0, CharChunkWR::CD_OtherInfoBufferSize);
        memset( bufferExtendDataChunk,  0, CharChunkWR::CD_ExtendInfoBufferSize);
        memset( bufferAchieveDataChunk, 0, CharChunkWR::CD_AchieveDataBufferSize);
        memset( bufferIdentifyDataChunk,0, CharChunkWR::CD_IdentifyDataBufferSize);

        memset( bufferBaseInfoField,    0, CharChunkWR::CD_EncodeFieldBufferSize);
        memset( bufferVisualInfoField,  0, CharChunkWR::CD_EncodeFieldBufferSize);
        memset( bufferOtherDataField,   0, CharChunkWR::CD_EncodeFieldBufferSize);
        memset( bufferExtendDataField,  0, CharChunkWR::CD_EncodeFieldBufferSize);
        memset( bufferAchieveDataField, 0, CharChunkWR::CD_EncodeFieldBufferSize);
        memset( bufferIdentifyDataField,0, CharChunkWR::CD_EncodeFieldBufferSize);

        uint32 zipBufferSize = 0; // 实际压缩大小
        uint32 nActualSize   = 0; // 实际buffer大小

        // 处理BaseInfo
        if  ( !_charDataWR.WriteCharData( &pCreate->charinfo.baseinfo, nActualSize, bufferBaseInfoChunk, CharChunkWR::CD_CharBaseInfoBufferSize) )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"WriteCharData Error!");
            ack.result = ER_Failed;
            goto FinalProcess;
        }

        zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
        compress( bufferTempZip, (uLongf*)&zipBufferSize, bufferBaseInfoChunk, nActualSize ); // 压缩数据
        EnCodeToString( bufferTempZip, bufferBaseInfoField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串

        // 处理VisualData
        if( !_charDataWR.WriteVisualData( &pCreate->charinfo.visual, nActualSize, bufferVisualInfoChunk, CharChunkWR::CD_VisualInfoBufferSize ))
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"ChangeCharVisualData Error!");
            ack.result = ER_Failed;
            goto FinalProcess;
        }

        zipBufferSize = CharChunkWR::CD_ZipTempBufferSize; // 因为调用compress会改变size的值，所以这里需要重新赋值一次        
        compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferVisualInfoChunk, nActualSize); // 压缩数据
        EnCodeToString(bufferTempZip, bufferVisualInfoField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串

        // 处理OtherData
        if ( !_charDataWR.WriteOtherData( &pCreate->charinfo.otherdata, nActualSize, bufferOtherDataChunk, CharChunkWR::CD_OtherInfoBufferSize ))
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"WriteOtherData Error!");
            ack.result = ER_Failed;
            goto FinalProcess;
        }
        zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
        compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferOtherDataChunk, nActualSize);// 压缩数据
        EnCodeToString(bufferTempZip, bufferOtherDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串

        //处理ExtendData
        if ( !_charDataWR.WriteExtendData( &pCreate->charinfo.extendData , nActualSize, bufferExtendDataChunk, CharChunkWR::CD_ExtendInfoBufferSize ))
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"WriteExtendData Error!");
            ack.result = ER_Failed;
            goto FinalProcess;
        }

        zipBufferSize = CharChunkWR::CD_ZipTempBufferSize; // 因为调用compress会改变size的值，所以这里需要重新赋值一次
        compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferExtendDataChunk, nActualSize); // 压缩数据
        EnCodeToString(bufferTempZip, bufferExtendDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串

        //处理AchieveData
        if ( !_charDataWR.WriteAchieveData( &pCreate->charinfo.achieveData , nActualSize, bufferAchieveDataChunk, CharChunkWR::CD_AchieveDataBufferSize ))
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"WriteAchieveData Error!");
            ack.result = ER_Failed;
            goto FinalProcess;
        }

        zipBufferSize = CharChunkWR::CD_ZipTempBufferSize; // 因为调用compress会改变size的值，所以这里需要重新赋值一次
        compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferAchieveDataChunk, nActualSize); // 压缩数据
        EnCodeToString(bufferTempZip, bufferAchieveDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串

        //处理IdentifyData
        if ( !_charDataWR.WriteIdentifyData( &pCreate->charinfo.identifyData , nActualSize, bufferIdentifyDataChunk, CharChunkWR::CD_IdentifyDataBufferSize ))
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"WriteIdentifyData Error!");
            ack.result = ER_Failed;
            goto FinalProcess;
        }

        zipBufferSize = CharChunkWR::CD_ZipTempBufferSize; // 因为调用compress会改变size的值，所以这里需要重新赋值一次
        compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferIdentifyDataChunk, nActualSize); // 压缩数据
        EnCodeToString(bufferTempZip, bufferIdentifyDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串
            
        TRYBEGIN
            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_character(AccountId,CharName,Lev,Money,StorageMoney,DataInfo,OtherData,CharSlot,IsDel,KillValue,KillFlag,KillerStateTime,jinding,jinpiao,ExtendData,UpdateTime,create_time, challenge_score,country,profession,changeName,guild) values(%0,%1q,%2,%3,%4,%5q,%6q,%7,%8,%9,%10,%11,%12,%13,%14q,now(),now(),%15,%16,%17,%18,%19);", sizeof ( szSql ) - 1 );
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pCreate->accoundId),
                _tUTF8CHAR(pCreate->charinfo.baseinfo.aptotic.szCharacterName),
                pCreate->charinfo.baseinfo.liveinfo.ustLevel,
                mysqlpp::sql_int_unsigned(pCreate->charinfo.baseinfo.liveinfo.dwMoney),
                0,
                bufferBaseInfoField, 
                bufferOtherDataField,
                pCreate->stWhichSlot,
                0,
                0,
                PKMode_Normal,
                0,
                0,
                0,
                bufferExtendDataField, 
                0,
                pCreate->charinfo.baseinfo.aptotic.ucCountry,
				pCreate->charinfo.baseinfo.aptotic.usProfession,
				pCreate->charinfo.baseinfo.liveinfo.ChangeName,
				pCreate->charinfo.otherdata.nGuildID
                );

            mysqlQuery.reset();
        TRYEND

        // 执行失败
        if ( RESULT_FAILED(result))
        {
            ack.result = ER_Failed;
            goto FinalProcess;
        }

        sprintf_s( szSql, sizeof( szSql ) - 1, "select CharacterId from t_game_character where AccountId=%ld and CharName='%s';", pCreate->accoundId, _tUTF8CHAR(pCreate->charinfo.baseinfo.aptotic.szCharacterName));
        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query(szSql);        
            mysqlpp::StoreQueryResult res = mysqlQuery.store();

            if ( res && !res.empty())
            { 
                bExistChar = true; 
                ack.dwCharacterId = res[0]["CharacterId"];
            }
            mysqlQuery.reset();
        TRYEND
        
        // 执行失败
        if ( RESULT_FAILED(result) || !bExistChar)
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s(%d)",szSql, bExistChar );
            ack.result = ER_Failed;
            goto FinalProcess;
        }

        TRYBEGIN
            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_visualinfo(CharacterID, DataInfo) values(%0,%1q);", sizeof( szSql ) - 1 );
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(ack.dwCharacterId), bufferVisualInfoField );
            mysqlQuery.reset();

            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_achieve(CharacterId, AchieveData, CreateTime) values(%0,%1q,now());", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(ack.dwCharacterId), bufferAchieveDataField );
            mysqlQuery.reset();

            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_identify(CharacterId, IdentifyData, CreateTime) values(%0,%1q,now());", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(ack.dwCharacterId), bufferIdentifyDataField );
            mysqlQuery.reset();

            // 需要存一次数据
            if ( pCreate->withFlag & DBMsgCreateHeroChar::EF_WithNormalBag )
            {
                static uint8 bufferItemDataChunk[ CharChunkWR::CD_ItemInfoBufferSize   ] = {0};
                static uint8 bufferTempZipItem  [ CharChunkWR::CD_ZipTempBufferSize    ] = {0};
                static int8  bufferItemDataField[ CharChunkWR::CD_EncodeFieldBufferSize] = {0};
				
				static char additionalInfo[100] = {0};

                // 普通物品背包
                SCharItem* pItem = pCreate->charinfo.itemData.stPackItems;
                for (int i=0; i<ITEM_BAGMAX; ++i, ++pItem)
                {
                    if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
                    { continue; }

                    // 处理物品数据
                    uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
                    uint32 nActualSize = 0;
                    if (!_charDataWR.WriteItemData( pItem, nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
                    { continue; }
                    compress( bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
                    EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

                    sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_item where ItemGUID=%I64u and CharacterId=%ld;", pItem->itembaseinfo.nOnlyInt, ack.dwCharacterId );
                    mysqlQuery.execute( szSql );
                    mysqlQuery.reset();

					sprintf_s(additionalInfo,sizeof(additionalInfo) - 1,"%d;%d;%d;%d;%d;%d;",
							  pItem->equipdata.ucLevel,pItem->equipdata.gemHoleCount,pItem->equipdata.gemIds[0],
							  pItem->equipdata.gemIds[1],pItem->equipdata.gemIds[2],pItem->equipdata.gemIds[3]);

                    strncpy_s( szSql, sizeof( szSql ), "insert into t_game_item(CharacterId,ItemGUID,ItemId,x,y,ItemName,ItemData,WhoIs,BagIndex,count,score,equiptype,additional_info) values(%0,%1,%2,-1,-1,'N/A',%3q,%4,%5,%6,%7,%8,%9q);", sizeof( szSql ) - 1 );
                    mysqlQuery << szSql;
                    mysqlQuery.parse();
                    mysqlQuery.execute( mysqlpp::sql_int_unsigned( ack.dwCharacterId), mysqlpp::sql_bigint(pItem->itembaseinfo.nOnlyInt),pItem->itembaseinfo.ustItemID,bufferItemDataField,e_CharBag,i,pItem->itembaseinfo.ustItemCount,pItem->equipdata.fScore,mysqlpp::sql_int_unsigned(pItem->equipdata.ustEquipType),additionalInfo);
                    mysqlQuery.reset();
                }
            }
        TRYEND

        // 执行失败
        if ( RESULT_FAILED(result))
        { 
            ack.result = ER_Failed;
            goto FinalProcess;
        }
        
        ack.result = ER_Success;
    }

FinalProcess:
    theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId );
}

void NormalLogicWorkThread::OnQueryCreateCheckName( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgReqCreateCheckName* pDetailSqlMessage = (SqlMessageDBMsgReqCreateCheckName*)pSqlMessage;
    DBMsgReqCreateCheckName* pCreateCheckName = &pDetailSqlMessage->msg;

    DBMsgAckCreateCheckName ack;
    ack.header.stID = pCreateCheckName->header.stID;
    ack.bResult     = true;
    ack.checkType   = pCreateCheckName->checkType;
    strncpy_s( ack.szName, sizeof(ack.szName), pCreateCheckName->szName, sizeof(ack.szName) - 1);
    uint32 result   = ER_Success;

    //检查是否含有单引号或是减号
    if ( !CheckCreateName( pCreateCheckName->szName ) )
    {
        DBMsgAckCreateCheckName ackcheck;
        ackcheck.bResult = false;
        theMysqlCommunication.PushAckMessage( &ackcheck, pSqlMessage->nClientId );
        return;
    }

    char szSql[1024] = {0};
    sprintf_s( szSql, sizeof( szSql ) - 1, "select AccountId from t_game_character where CharName='%s';",_tUTF8CHAR(pCreateCheckName->szName));

    bool bExistChar = false;
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
        mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql );
        if ( res && !res.empty())
        { bExistChar = true; }
    TRYEND

    // 执行失败
    if ( RESULT_FAILED(result) || bExistChar)
    { ack.bResult = false; }
    theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId );
}
void NormalLogicWorkThread::OnQueryChangeName( BaseSqlMessage* pSqlMessage )
{
	//检查玩家名称是否重复 并且返回命令
	SqlMessageDBMsgChangeNameReq* pMsg = (SqlMessageDBMsgChangeNameReq*)pSqlMessage;
	DBMsgChangeNameReq* pReq = &(pMsg->msg);
	DBMsgChangeNameAck msg;
	msg.header.stID = pReq->header.stID;
	msg.Result = true;
	msg.PlayerID = pReq->PlayerID;
	msg.GuildID = 0;
	strcpy_s(msg.szName,sizeof(msg.szName)-1,pReq->szName);
	if ( !CheckCreateName( pReq->szName ) )
    {
		msg.Result = false;
		theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
		return;
	}
	uint32 result   = ER_Success;
	//1.先判断名称有无重复的
	{
		char szSql[1024] = {0};
		sprintf_s( szSql, sizeof( szSql ) - 1, "select AccountId from t_game_character where CharName='%s';",_tUTF8CHAR(pReq->szName));

		bool bExistChar = false;
		TRYBEGIN
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
			mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql );
			if ( res && !res.empty())
			{ bExistChar = true; }
		TRYEND

		// 执行失败
		if ( RESULT_FAILED(result) || bExistChar)
		{ msg.Result = false; }
	}
	if(!msg.Result)
	{
		theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
		return;
	}
	//基本检测完毕后 我们开始处理数据库的数据
	{
		char szSql[1024] = {0};
		memset( szSql, 0, sizeof(szSql));
		uint32 result = ER_Success;
		sprintf_s( szSql, sizeof( szSql ) - 1, "update t_game_character set t_game_character.CharName = '%s',changeName=0 where t_game_character.characterid = %d and changeName=%d;",_tUTF8CHAR(pReq->szName),pReq->PlayerID,pReq->PlayerID);
		TRYBEGIN
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
			mysqlQuery.execute( szSql );
			mysqlQuery.reset();
		TRYEND
		CHECK_SQL_RESULT( result ) // 执行检测
		if ( RESULT_FAILED(result))
		{ 
			msg.Result = false; 
			theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
			return;
		}
	}
	{
		char szSql[1024] = {0};
		memset( szSql, 0, sizeof(szSql));
		uint32 result = ER_Success;
		sprintf_s( szSql, sizeof( szSql ) - 1, "update guildmember set guildmember.name = '%s' where guildmember.id = %d;",_tUTF8CHAR(pReq->szName),pReq->PlayerID);
		TRYBEGIN
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
			mysqlQuery.execute( szSql );
			mysqlQuery.reset();
		TRYEND
		CHECK_SQL_RESULT( result ) // 执行检测
		if ( RESULT_FAILED(result))
		{ 
			msg.Result = false; 
			theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
			return;
		}
	}
	{
		char szSql[1024] = {0};
		memset( szSql, 0, sizeof(szSql));
		uint32 result = ER_Success;
		sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set relationattribute.name = '%s' where relationattribute.id = %d;",_tUTF8CHAR(pReq->szName),pReq->PlayerID);
		TRYBEGIN
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
			mysqlQuery.execute( szSql );
			mysqlQuery.reset();
		TRYEND
		CHECK_SQL_RESULT( result ) // 执行检测
		if ( RESULT_FAILED(result))
		{ 
			msg.Result = false; 
			theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
			return;
		}
	}
	{
		for(int i =0;i<8;++i)
		{
			char szSql[1024] = {0};
			memset( szSql, 0, sizeof(szSql));
			uint32 result = ER_Success;
			sprintf_s( szSql, sizeof( szSql ) - 1, "update mails set mails.owner_name_%d = '%s' where mails.owner_id_%d = %d;",i,_tUTF8CHAR(pReq->szName),i,pReq->PlayerID);
			TRYBEGIN
				mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
				mysqlQuery.execute( szSql );
				mysqlQuery.reset();
			TRYEND
			CHECK_SQL_RESULT( result ) // 执行检测
			if ( RESULT_FAILED(result))
			{ 
				msg.Result = false; 
				theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
				return;
			}
		}
	}
	{
		char szSql[1024] = {0};
		memset( szSql, 0, sizeof(szSql));
		uint32 result = ER_Success;
		sprintf_s( szSql, sizeof( szSql ) - 1, "select guild from guildmember where id=  %d;",pReq->PlayerID);
		TRYBEGIN
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
			mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql );
			if ( res && !res.empty())
			{
				msg.GuildID = res[0]["guild"];
			}
		TRYEND
	}
	theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
}
void NormalLogicWorkThread::OnQueryAccountChar( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgQueryAccountChar* pDetailSqlMesage = (SqlMessageDBMsgQueryAccountChar*)pSqlMessage;

    DBMsgQueryAccountChar* pReq = &(pDetailSqlMesage->msg);

    static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;
    
    if( pReq->bQueryAllChars )
    { // 所有的角色
        if(GetDatabaseServerApp()->m_bUseCancelDel)
        { sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_character where AccountId=%ld and (IsDel=0 or (IsDel=1 and datediff(now(),DelTime)<= 7));", pReq->dwAccountId ); }
        else
        { sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_character where AccountId=%ld and IsDel=0;", pReq->dwAccountId ); }
    }
    else
    { // 只要一个角色
        if(GetDatabaseServerApp()->m_bUseCancelDel)
        { sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_character where AccountId=%ld and CharacterId=%ld and (IsDel=0 or (IsDel=1 and datediff(now(),DelTime)<= 7));", pReq->dwAccountId, pReq->dwCharacterId ); }
        else
        { sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_character where AccountId=%ld and CharacterId=%ld and IsDel=0;", pReq->dwAccountId, pReq->dwCharacterId );}
    }

    DBMsgAckCharInfo ack;
    ack.shServerId  = pReq->shServerId;
    ack.dwAccountID = pReq->dwAccountId;
    ack.header.stID = pReq->header.stID;
    ack.ustLifeCode = pReq->ustLifeCode;

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty())
        { 
            for (int i = 0; i < res.num_rows();++i )
            {
                ack.dwCharacterID = res[i]["CharacterId"];
                ack.stWhichSlot   = res[i]["CharSlot"];
                ack.bIsDel        = res[i]["IsDel"];
                if ( ack.bIsDel )
                {
                    mysqlpp::DateTime xDelTime = res[i]["DelTime"];
                    TimeEx xRemainTime( xDelTime.year(), xDelTime.month(), xDelTime.day(), xDelTime.hour(), xDelTime.minute(), xDelTime.second() );
                    ack.dwDelTimes  = static_cast< uint32 > ( xRemainTime.GetTime() + OneDaySecond * 7 - TimeEx::GetNowTime() ) ;
                }

                BaseSqlMessage* pSaveQuery = _dbMsgQueue.GetSaveQueryByCharDbId( ack.dwCharacterID );
                if ( pSaveQuery == NULL )
                { // 已经入库
                    // baseinfo 将数据库中读出来的字符串解码成二进制值
                    static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Char ] = {0};
                    static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Char   ] = {0};
                    
                    // baseinfo
                    uint32 unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
                    uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[i]["DataInfo"].c_str(), bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char ); // 转为压缩buffer
                    uncompress( bufferTempUnZip, &unzipBufferSize, (uint8*)bufferDecodeField, nDecodeBufferActualSize); // 解压
                    bool bflag = _charDataWR.LoadCharData( bufferTempUnZip, unzipBufferSize, &ack.baseinfo); // 读取人数基本数据
                    if ( !bflag )
                    { 
                        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"LoadCharData Error!");
                        return; 
                    }

                    // 名字
                    Common::_tstring strName;
                    strName.fromUTF8( res[i]["CharName"] );
                    strncpy_s(ack.baseinfo.aptotic.szCharacterName, sizeof(ack.baseinfo.aptotic.szCharacterName), strName.c_str(), sizeof(ack.baseinfo.aptotic.szCharacterName)-1);

                    // otherdata
                    unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
                    //const mysqlpp::String
                    nDecodeBufferActualSize = DeCodeToBuffer( res[i]["OtherData"].c_str(), bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char );
                    uncompress( bufferTempUnZip, &unzipBufferSize, (uint8*)bufferDecodeField,  nDecodeBufferActualSize );            
                    SCharOtherData otherdata;
                    bool bResult = _charDataWR.LoadOtherData( bufferTempUnZip, unzipBufferSize, &otherdata );
                    if (!bResult)
                    { 
                        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"LoadOtherData Error!");
                        return;
                    }

                    // 地图Id
                    ack.nMapId = otherdata.pos.dwMapID;

					ack.baseinfo.liveinfo.ChangeName = res[i]["changeName"];
					otherdata.nGuildID = res[i]["guild"];

                    // visual
                    bool bVisualExist = false;
                    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_visualinfo where CharacterId = %ld;", ack.dwCharacterID );

                    TRYBEGIN
                        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
                        mysqlpp::StoreQueryResult res = mysqlQuery.store();
                        if ( res && !res.empty())
                        { 
                            // visual
                            nDecodeBufferActualSize = DeCodeToBuffer( res[0]["DataInfo"].c_str(), bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char );
                            unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
                            uncompress( bufferTempUnZip,&unzipBufferSize,(uint8*)bufferDecodeField, nDecodeBufferActualSize);
                            bool bVisual = _charDataWR.LoadVisuals( bufferTempUnZip, unzipBufferSize, &ack.visual);
                            if (!bVisual)
                            { 
                                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"LoadVisuals Error!");
                                return;
                            }
                            bVisualExist = true;
                        }
                    TRYEND

                    // 执行失败
                    if ( RESULT_FAILED(result) || !bVisualExist )
                    { 
                        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, szSql );
                        return;
                    }
                }
                else
                {
                    SqlMessageDBMsgSaveCharacter* pSave = (SqlMessageDBMsgSaveCharacter*)pSaveQuery;
                    memcpy_s( &ack.baseinfo, sizeof(ack.baseinfo), &pSave->msg.dbInfo.baseinfo, sizeof(ack.baseinfo) );
                    memcpy_s( &ack.visual,   sizeof(ack.visual),   &pSave->msg.dbInfo.visual,   sizeof(ack.visual) );
                    ack.nMapId = pSave->msg.dbInfo.otherdata.pos.dwMapID;
                }

                theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId );
            }
        }

        mysqlQuery.reset();
    TRYEND

    // 执行失败
    if ( RESULT_FAILED(result))
    { return; }

    if( pReq->needEnd == 1 )
    {
        DBMsgEndAckChar end;
        end.shServerId  = pReq->shServerId;
        end.header.stID = pReq->header.stID;
        end.dwAccountID = pReq->dwAccountId;
        theMysqlCommunication.PushAckMessage( &end, pSqlMessage->nClientId );
    }
}

void NormalLogicWorkThread::OnQueryCharEnterWorld ( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgEnterWorld* pDetailSqlMessage = (SqlMessageDBMsgEnterWorld*)pSqlMessage;
    DBMsgEnterWorld* pReq = &pDetailSqlMessage->msg;

    DBMsgAckEnterWorld ack;
    ack.header.stID              = pReq->header.stID;
    ack.ustLifeCode              = pReq->ustLifeCode;
    ack.dwCharacterID            = pReq->dwCharacterID;
    ack.nMapId                   = pReq->nMapId;
    ack.nTileX                   = pReq->nTileX;
    ack.nTileY                   = pReq->nTileY;
    ack.fDir                     = pReq->fDir;
    ack.ucNeedTellClientCharInfo = pReq->ucNeedTellClientCharInfo;
    ack.ucNeedUseMessageMapInfo  = pReq->ucNeedUseMessageMapInfo;
    ack.shServerId               = pReq->shServerId;
    ack.dwTeamSessionID          = pReq->dwTeamSessionID;

    RoleDataCache* pRoleData = GetRoleDataCacheManager().GetRoleDataCache( pReq->dwAccountID, pReq->dwCharacterID );
    if ( pRoleData )
    { // 有Cache 切服
        pRoleData->MakeData( ack );
		theAccountMoneyCache.MakeMoneyData(ack,pReq->dwAccountID);
        theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId );
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "开始使用Cache数据 AccountId[%d] CharDbId[%d]", pReq->dwAccountID, pReq->dwCharacterID );
        return;
    }

    BaseSqlMessage* pSaveQuery = _dbMsgQueue.GetSaveQueryByCharDbId( pReq->dwCharacterID );
    if ( pSaveQuery )
    { // 有最新的未存得
        SqlMessageDBMsgSaveCharacter* pSave = (SqlMessageDBMsgSaveCharacter*)pSaveQuery;
        ack.bRet            = ER_Success;
        ack.nPKValue        = pSave->msg.nPKValue;
        ack.stPKProtectFlag = pSave->msg.stPKProtectFlag;
        ack.nGMLevel        = pSave->msg.nGMLevel;
        memcpy_s( &ack.charinfo,    sizeof( ack.charinfo ),   &pSave->msg.dbInfo,      sizeof( ack.charinfo  ));
        memcpy_s( &ack.stStorage,   sizeof( ack.stStorage),   &pSave->msg.storageInfo, sizeof( ack.stStorage ));
        memcpy_s( &ack.runtimeInfo, sizeof( ack.runtimeInfo), &pSave->msg.runtimeInfo, sizeof( ack.runtimeInfo ));
		theAccountMoneyCache.MakeMoneyData(ack,pReq->dwAccountID);
        theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId );
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "开始使用UnSaveToMssql数据 AccountId[%d] CharDbId[%d]", pReq->dwAccountID, pReq->dwCharacterID );
        return;
    }

    char szSql[1024] = {0};
    memset( szSql, 0, sizeof(szSql));
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_character where (AccountId=%ld) and (CharSlot=%d) and IsDel=0 and CharacterID=%ld;", pReq->dwAccountID, pReq->stSlot, pReq->dwCharacterID);
    uint32 result = ER_Success;
    bool bCharExist = false;

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty())
        {
            // 清理一下钱
            ack.charinfo.baseinfo.liveinfo.jinDing = 0;
            ack.charinfo.baseinfo.liveinfo.jinPiao = 0;
            ack.charinfo.baseinfo.liveinfo.jiaoZi = 0;

            ack.bRet                     = ER_Success;    
            ack.nGMLevel                 = 0;
            ack.dwCharacterID            = res[0]["CharacterId"    ];
            ack.nPKValue                 = res[0]["KillValue"      ];
            ack.stPKProtectFlag          = res[0]["KillFlag"       ];
            ack.nStayInHellTime          = res[0]["KillerStateTime"];

            Common::_tstring strName;
            strName.fromUTF8( res[0]["CharName"] );
            uint16 shLevel               = res[0]["Lev"            ];
            uint32 dwMoney               = res[0]["Money"          ];
            ack.stStorage.dwStorageMoney = res[0]["StorageMoney"   ];
            int32 jinding                = res[0]["jinding"        ];
            int32 jinpiao                = res[0]["jinpiao"        ];
            int32 jiaozi                 = res[0]["jiaozi"];

            // 查找是否为GM
            ItrGmContainer itr = gmlist.find( strName );
            if (itr != gmlist.end()&&strcmp(itr->second.szIP,pReq->szIP) == 0)
            { ack.nGMLevel = itr->second.nLevel; }

            static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Char ] = {0};
            static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Char   ] = {0};

            // DataInfo
            uint32 unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
            uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[0]["DataInfo"].c_str(), bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char );
            uncompress( bufferTempUnZip, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize );
            bool bResult = _charDataWR.LoadCharData( bufferTempUnZip, unzipBufferSize, &ack.charinfo.baseinfo);
            CHECK_LOAD( bResult );

            // Otherdata
            unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
            nDecodeBufferActualSize = DeCodeToBuffer( res[0]["OtherData"].c_str(), bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char );            
            uncompress( bufferTempUnZip, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize);
            bResult = _charDataWR.LoadOtherData( bufferTempUnZip, unzipBufferSize, &ack.charinfo.otherdata );
            CHECK_LOAD( bResult );

            // 角色名字
            strncpy_s( ack.charinfo.baseinfo.aptotic.szCharacterName, strName.c_str(), sizeof(ack.charinfo.baseinfo.aptotic.szCharacterName)-1);

            // ExtendData
            unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
            nDecodeBufferActualSize = DeCodeToBuffer( res[0]["ExtendData"].c_str(), bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char );
            uncompress( bufferTempUnZip, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize        );
            bResult = _charDataWR.LoadExtendData( bufferTempUnZip, unzipBufferSize, &ack.charinfo.extendData );
            CHECK_LOAD( bResult );

            // VisualInfo
            sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_visualinfo where CharacterId=%ld;", ack.dwCharacterID );
            TRYBEGIN
                mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
                mysqlpp::StoreQueryResult res = mysqlQuery.store();
                if ( res && !res.empty())
                { // visual
                    unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
                    nDecodeBufferActualSize = DeCodeToBuffer(res[0]["DataInfo"], bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char );
                    uncompress( bufferTempUnZip, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize);
                    bResult = _charDataWR.LoadVisuals( bufferTempUnZip, unzipBufferSize, &ack.charinfo.visual);
                    CHECK_LOAD( bResult );
                }
                mysqlQuery.reset();
            TRYEND

            // AchieveData
            sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_achieve where CharacterId=%ld;", ack.dwCharacterID );
            TRYBEGIN
                mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
                mysqlpp::StoreQueryResult res = mysqlQuery.store();
                if ( res && !res.empty())
                {
                    unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
                    nDecodeBufferActualSize = DeCodeToBuffer(res[0]["AchieveData"], bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char );
                    uncompress( bufferTempUnZip, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize);
                    bResult = _charDataWR.LoadAchieveData( bufferTempUnZip, unzipBufferSize, &ack.charinfo.achieveData);
                    CHECK_LOAD( bResult );
                }
                mysqlQuery.reset();
            TRYEND

            // IdentifyData
            sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_identify where CharacterId=%ld;", ack.dwCharacterID );
            TRYBEGIN
                mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
                mysqlpp::StoreQueryResult res = mysqlQuery.store();
                if ( res && !res.empty())
                {
                    unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
                    nDecodeBufferActualSize = DeCodeToBuffer(res[0]["IdentifyData"], bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char );
                    uncompress( bufferTempUnZip, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize);
                    bResult = _charDataWR.LoadIdentifyData( bufferTempUnZip, unzipBufferSize, &ack.charinfo.identifyData);
                    CHECK_LOAD( bResult );
                }
                mysqlQuery.reset();
            TRYEND

			sprintf_s( szSql, sizeof( szSql ) - 1, "select * from t_game_killplayer where characterid = %ld;", ack.dwCharacterID );
			TRYBEGIN
				mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
				mysqlpp::StoreQueryResult res = mysqlQuery.store();
				if ( res && !res.empty())
				{
					mysqlpp::DateTime xLogTime = res[0]["LogTime"];
					time_t now;		
					time(&now);	
					struct tm *fmt;	
					fmt = localtime(&now);	
					if(fmt->tm_year + 1900 == xLogTime.year() && fmt->tm_mon +1 == xLogTime.month() && fmt->tm_mday == xLogTime.day())
					{
						nDecodeBufferActualSize = DeCodeToBuffer( res[0]["Info"].c_str(), bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char );
						unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
						uncompress( bufferTempUnZip,&unzipBufferSize,(uint8*)bufferDecodeField, nDecodeBufferActualSize);
						//解压完毕 我们将数据读入到结构去
						bResult = _charDataWR.LoadKillInfo( bufferTempUnZip, unzipBufferSize, &ack.charinfo.otherdata);
						CHECK_LOAD( bResult );
					}
				}
			TRYEND

			sprintf_s( szSql, sizeof( szSql ) - 1, "select totleyuanbao,states from accountyuanbaostates where accountid = %ld;",pReq->dwAccountID);
            TRYBEGIN
                mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
                mysqlpp::StoreQueryResult res = mysqlQuery.store();
                if ( res && !res.empty())
                {
				   ack.dwAccountYuanBaoTotle = res[0][0];
                   ack.dwAccountYuanBaoStates = res[0][1];
                }
				else
				{
					ack.dwAccountYuanBaoStates = 0;
					ack.dwAccountYuanBaoTotle = 0;
				}
                mysqlQuery.reset();
            TRYEND



            CHECK_SQL_RESULT( result ) // 执行检测

            // 这里设置独立字段的等级/金钱/银票，在这之后不要改写这些数据
            ack.charinfo.baseinfo.liveinfo.ustLevel = shLevel;
            ack.charinfo.baseinfo.liveinfo.dwMoney  = dwMoney;
            ack.charinfo.baseinfo.liveinfo.jiaoZi = jiaozi;
            if ( ack.charinfo.baseinfo.liveinfo.jinDing > 0)
            { // 如果这个时候有 [把封测试时候送的金锭转到金票]
                ack.charinfo.baseinfo.liveinfo.jinPiao += ack.charinfo.baseinfo.liveinfo.jinDing;
            }

            ack.charinfo.baseinfo.liveinfo.jinDing = jinding;


			ack.charinfo.baseinfo.liveinfo.ChangeName = res[0]["changeName"];
			ack.charinfo.otherdata.nGuildID = res[0]["guild"];


            if ( jinpiao > 0 )
            { ack.charinfo.baseinfo.liveinfo.jinPiao += jinpiao; }

            HelperFunc::SafeNCpy( ack.charinfo.baseinfo.aptotic.szCharacterName, strName.c_str(), sizeof( ack.charinfo.baseinfo.aptotic.szCharacterName ) );

            // 普通物品背包
            LoadItems( ack.dwCharacterID, ack.charinfo.itemData.stPackItems, ack.charinfo.baseinfo.liveinfo.ucNormalBagSize,e_CharBag );

            // 仓库物品背包
            LoadItems( ack.dwCharacterID, ack.stStorage.stStorageItems, STORAGE_ITEMGRID_MAX, e_StroageBag );

            // 材料物品背包
            LoadItems( ack.dwCharacterID, ack.charinfo.itemData.ciMaterialItems, ack.charinfo.baseinfo.liveinfo.ucMaterialBagSize, e_MaterialBag);

            // 任务物品背包
            LoadItems( ack.dwCharacterID, ack.charinfo.itemData.ciTaskItems, ITEM_BAGTASK_MAX, e_TaskBag );

            // 坐骑
            LoadMount( ack.dwCharacterID, ack.charinfo.itemData.miItems, ack.charinfo.baseinfo.liveinfo.ucMountCount, e_CharBag );

            // 仓库坐骑
            LoadMount( ack.dwCharacterID, ack.stStorage.xStorageMounts, STORAGE_MOUNTGRID_MAX, e_StroageBag );

            // 宠物
            LoadPets ( ack.dwCharacterID, ack.charinfo.itemData.petItems,ITEM_PET_MAXCOUNT, e_CharBag );

            // 繁殖宠物
            LoadPets ( ack.dwCharacterID, &ack.charinfo.itemData.petBreedItem, ITEM_BREEDPET_MAXCOUNT, e_NpcBag );
			theAccountMoneyCache.MakeMoneyData(ack,pReq->dwAccountID);
            theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId );
            bCharExist = true;
        }
        else
        {
            bCharExist = false;
        }
    TRYEND
    
    CHECK_SQL_RESULT(result) // 执行检测

    if( !bCharExist )
    {  
        MsgAckResult msg;
        msg.result = ER_EnterWorldDbSqlException;
        theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
        return;
    }
}

void NormalLogicWorkThread::OnQuerySaveChar( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgSaveCharacter* pDetailSqlMessage = (SqlMessageDBMsgSaveCharacter*)pSqlMessage;
    DBMsgSaveCharacter* pSave = &pDetailSqlMessage->msg;

    uint32 Performance_SaveRoleBeginTime = 0;
    if (G_PrinfInfo == PRINTFSAVEROLETIME)
    { Performance_SaveRoleBeginTime = HQ_TimeGetTime();}

    uint32 dwTime = (uint32)((double)pSave->dwSaveTime / 1000.00 / 60.00);
    uint32 result = ER_Success;

    char szSql[ 1024 * 60 ] = {0};
    memset( szSql, 0, sizeof(szSql) );

    static uint8 bufferTempZip[ CharChunkWR::CD_ZipTempBufferSize ] = {0};

    static uint8 bufferBaseInfoChunk    [ CharChunkWR::CD_CharBaseInfoBufferSize ] = {0};
    static uint8 bufferVisualInfoChunk  [ CharChunkWR::CD_VisualInfoBufferSize   ] = {0};
    static uint8 bufferOtherDataChunk   [ CharChunkWR::CD_OtherInfoBufferSize    ] = {0};
    static uint8 bufferExtendDataChunk  [ CharChunkWR::CD_ExtendInfoBufferSize   ] = {0};
    static uint8 bufferAchieveDataChunk [ CharChunkWR::CD_AchieveDataBufferSize  ] = {0};
    static uint8 bufferIdentifyDataChunk[ CharChunkWR::CD_IdentifyDataBufferSize ] = {0};

	static uint8 bufferKillPlayerDataChunk[ CharChunkWR::CD_KillPlayerDataBufferSize ] = {0};

    // 需要存放压缩过后的字符
    static int8 bufferBaseInfoField     [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};
    static int8 bufferVisualInfoField   [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};
    static int8 bufferOtherDataField    [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};
    static int8 bufferExtendDataField   [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};
    static int8 bufferAchieveDataField  [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};
    static int8 bufferIdentifyDataField [ CharChunkWR::CD_EncodeFieldBufferSize ] = {0};

	static int8 bufferKillPlayerDataField [ CharChunkWR::CD_KillPlayerDataBufferSize ] = {0};


    // 处理BaseInfo
    uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    uint32 nActualSize = 0;
    memset( bufferBaseInfoChunk, 0, CharChunkWR::CD_CharBaseInfoBufferSize );
    if ( !_charDataWR.WriteCharData( &pSave->dbInfo.baseinfo, nActualSize, bufferBaseInfoChunk, CharChunkWR::CD_CharBaseInfoBufferSize ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] baseinfo 数据出错", pSave->dwCharacterID );
        return;
    }
    compress( bufferTempZip, (uLongf*)&zipBufferSize, bufferBaseInfoChunk, nActualSize ); // 压缩数据
    EnCodeToString( bufferTempZip, bufferBaseInfoField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串

    // 处理VisualData
    zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    if ( !_charDataWR.WriteVisualData( &pSave->dbInfo.visual, nActualSize, bufferVisualInfoChunk, CharChunkWR::CD_VisualInfoBufferSize ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] visual 数据出错", pSave->dwCharacterID );
        return;
    }
    compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferVisualInfoChunk, nActualSize );       // 压缩数据
    EnCodeToString(bufferTempZip, bufferVisualInfoField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize  ); // 转为可视字符串

    // 处理OtherData
    zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    if (!_charDataWR.WriteOtherData( &pSave->dbInfo.otherdata, nActualSize, bufferOtherDataChunk, CharChunkWR::CD_OtherInfoBufferSize ))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] otherData 数据出错", pSave->dwCharacterID );
        return;
    }
    compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferOtherDataChunk, nActualSize ); // 压缩数据    
    EnCodeToString(bufferTempZip, bufferOtherDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串
	// 处理KillPlayer
	zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    if (!_charDataWR.WriteKillInfo( &pSave->dbInfo.otherdata, nActualSize, bufferKillPlayerDataChunk, CharChunkWR::CD_KillPlayerDataBufferSize ))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] otherData KillPlayer 数据出错", pSave->dwCharacterID );
        return;
    }
    compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferKillPlayerDataChunk, nActualSize ); // 压缩数据    
    EnCodeToString(bufferTempZip, bufferKillPlayerDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串	

    // 处理ExtendData
    zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    if ( !_charDataWR.WriteExtendData( &pSave->dbInfo.extendData, nActualSize, bufferExtendDataChunk, CharChunkWR::CD_ExtendInfoBufferSize  ))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] extendData 数据出错", pSave->dwCharacterID );
        return;
    }    
    compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferExtendDataChunk, nActualSize); // 压缩数据    
    EnCodeToString(bufferTempZip, bufferExtendDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串

    //处理AchieveData
    memset( bufferAchieveDataChunk,0, CharChunkWR::CD_AchieveDataBufferSize);
    memset( bufferAchieveDataField,0, CharChunkWR::CD_EncodeFieldBufferSize);
    zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    if ( !_charDataWR.WriteAchieveData( &pSave->dbInfo.achieveData , nActualSize, bufferAchieveDataChunk, CharChunkWR::CD_AchieveDataBufferSize ))
    {
         LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] AchieveData 数据出错", pSave->dwCharacterID );
         return;
    }
    compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferAchieveDataChunk, nActualSize); // 压缩数据
    EnCodeToString(bufferTempZip, bufferAchieveDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串

    //处理IdentifyData
    memset( bufferIdentifyDataChunk,0, CharChunkWR::CD_IdentifyDataBufferSize);
    memset( bufferIdentifyDataField,0, CharChunkWR::CD_EncodeFieldBufferSize);
    zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    if ( !_charDataWR.WriteIdentifyData( &pSave->dbInfo.identifyData , nActualSize, bufferIdentifyDataChunk, CharChunkWR::CD_IdentifyDataBufferSize ))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] IdentifyData 数据出错", pSave->dwCharacterID );
        return;
    }
    compress(bufferTempZip, (uLongf*)&zipBufferSize, bufferIdentifyDataChunk, nActualSize); // 压缩数据
    EnCodeToString(bufferTempZip, bufferIdentifyDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize ); // 转为可视字符串

    static uint8 bufferItemDataChunk[ CharChunkWR::CD_ItemInfoBufferSize   ] = {0};
    static uint8 bufferTempZipItem  [ CharChunkWR::CD_ZipTempBufferSize    ] = {0};
    static int8  bufferItemDataField[ CharChunkWR::CD_EncodeFieldBufferSize] = {0};

	static char additionalInfo[100] = {0};

    uint32 Performance_SaveRoleBeginSQLTime = HQ_TimeGetTime();
    // 没有使用存储过程因为转义的问题
    // 实际用这个 实际会有17*多ms的处理时间
    // 使用存储过程批量存储一个玩家的数据
    TRYBEGIN
        mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理

        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        strncpy_s( szSql, sizeof( szSql ), "update t_game_visualinfo set DataInfo=%1q where CharacterId=%0;", sizeof( szSql ) - 1 );
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_int_unsigned( pSave->dwCharacterID ), bufferVisualInfoField );        
        mysqlQuery.reset();

        strncpy_s( szSql, sizeof( szSql ), "update t_game_achieve set AchieveData=%1q where CharacterId=%0;", sizeof( szSql ) - 1 );
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_int_unsigned( pSave->dwCharacterID ), bufferAchieveDataField );        
        mysqlQuery.reset();

        strncpy_s( szSql, sizeof( szSql ), "update t_game_identify set IdentifyData=%1q where CharacterId=%0;", sizeof( szSql ) - 1 );
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_int_unsigned( pSave->dwCharacterID ), bufferIdentifyDataField );        
        mysqlQuery.reset();

        //sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_item where CharacterId=%ld and (WhoIs=%d or WhoIs=%d or WhoIs=%d or WhoIs=%d or WhoIs=%d);",pSave->dwCharacterID,e_CharBag,e_VisualBag,e_MaterialBag,e_TaskBag, e_StroageBag );
        //mysqlQuery.execute( szSql );
        //mysqlQuery.reset();

        sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_item where CharacterId=%ld;" ,pSave->dwCharacterID );
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();

        sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_mount where CharacterId=%ld;",pSave->dwCharacterID);
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();

        sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_pet where CharacterId=%ld;"  ,pSave->dwCharacterID);
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();

        strncpy_s( szSql, sizeof( szSql ), "update t_game_character set Lev=%1,Money=%2,StorageMoney=%3,DataInfo=%4q,OtherData=%5q,OnlineTime=OnlineTime+%6,Exp=%7,KillValue=%8,KillFlag=%9,KillerStateTime=%10,jinding=%11,ExtendData=%12q,UpdateTime=now(),jinpiao=%13,jiaozi= %14,challenge_score=%15,country=%16,honour=%17,exploit=%18,KillPlayerSum=%19,guild=%20,equipTotalScore=%21,AllExp=%22 where CharacterId=%0;", sizeof( szSql ) - 1 );
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_int_unsigned( pSave->dwCharacterID ), pSave->dbInfo.baseinfo.liveinfo.ustLevel, mysqlpp::sql_int_unsigned(pSave->dbInfo.baseinfo.liveinfo.dwMoney), mysqlpp::sql_int_unsigned(pSave->storageInfo.dwStorageMoney),
                            bufferBaseInfoField, bufferOtherDataField, mysqlpp::sql_int_unsigned(dwTime), pSave->dbInfo.baseinfo.liveinfo.dwExp, mysqlpp::sql_int(pSave->nPKValue), pSave->stPKProtectFlag, mysqlpp::sql_int_unsigned(0), 
                            mysqlpp::sql_int_unsigned(pSave->dbInfo.baseinfo.liveinfo.jinDing), bufferExtendDataField, mysqlpp::sql_int_unsigned(pSave->dbInfo.baseinfo.liveinfo.jinPiao), mysqlpp::sql_int_unsigned(pSave->dbInfo.baseinfo.liveinfo.jiaoZi),mysqlpp::sql_int_unsigned(pSave->dbInfo.baseinfo.liveinfo.battleScore), 
							pSave->dbInfo.baseinfo.aptotic.ucCountry ,mysqlpp::sql_int_unsigned(pSave->dbInfo.baseinfo.liveinfo.honour),mysqlpp::sql_int_unsigned(pSave->dbInfo.baseinfo.liveinfo.exploit),mysqlpp::sql_int_unsigned(pSave->dbInfo.baseinfo.liveinfo.dwKillPlayerSum),mysqlpp::sql_int_unsigned(pSave->dbInfo.otherdata.nGuildID),
							mysqlpp::sql_int_unsigned(pSave->dbInfo.otherdata.equipTotalScore),pSave->dbInfo.baseinfo.liveinfo.dwExpNotUsed+pSave->dbInfo.baseinfo.liveinfo.dwExp);
        mysqlQuery.reset();

		sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_killplayer where characterid=%ld;" ,pSave->dwCharacterID );
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();
			
		strncpy_s( szSql, sizeof( szSql ), "insert into t_game_killplayer(characterid,LogTime,Info) values(%0,now(),%1q);", sizeof( szSql ) - 1 );
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_int_unsigned( pSave->dwCharacterID ),bufferKillPlayerDataField);
		mysqlQuery.reset();
		
		//int equiptype = -1;
        // 普通物品背包
        SCharItem* pItem = pSave->dbInfo.itemData.stPackItems;
        for (int i=0; i<ITEM_BAGMAX; ++i, ++pItem)
        {
            if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
            { continue; }

            // 处理物品数据
            uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
            uint32 nActualSize = 0;
            if (!_charDataWR.WriteItemData( pItem, nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
            { continue; }
            compress( bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
            EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

            //sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_item where ItemGUID=%I64u and CharacterId=%ld;", pItem->itembaseinfo.nOnlyInt, pSave->dwCharacterID );
            //mysqlQuery.execute( szSql );
            //mysqlQuery.reset();

			sprintf_s(additionalInfo,sizeof(additionalInfo) - 1,"%d;%d;%d;%d;%d;%d;",
						pItem->equipdata.ucLevel,pItem->equipdata.gemHoleCount,pItem->equipdata.gemIds[0],
						pItem->equipdata.gemIds[1],pItem->equipdata.gemIds[2],pItem->equipdata.gemIds[3]);

            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_item(CharacterId,ItemGUID,ItemId,x,y,ItemName,ItemData,WhoIs,BagIndex,count,score,equiptype,additional_info) values(%0,%1,%2,-1,-1,'N/A',%3q,%4,%5,%6,%7,%8,%9q);", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID),mysqlpp::sql_bigint(pItem->itembaseinfo.nOnlyInt),pItem->itembaseinfo.ustItemID,bufferItemDataField,e_CharBag,i,pItem->itembaseinfo.ustItemCount,pItem->equipdata.fScore,mysqlpp::sql_int_unsigned(pItem->equipdata.ustEquipType),additionalInfo);
            mysqlQuery.reset();
        }

        // 材料背包
        pItem = pSave->dbInfo.itemData.ciMaterialItems;
        for (int i=0; i<ITEM_BAGMATERIAL_MAX; ++i, ++pItem)
        {
            if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
            { continue; }

            uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
            uint32 nActualSize = 0;
            if (! _charDataWR.WriteItemData( pItem, nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
            { continue; }
            compress( bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
            EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

            //sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_item where ItemGUID=%I64u and CharacterId=%ld;", pItem->itembaseinfo.nOnlyInt, pSave->dwCharacterID );
            //mysqlQuery.execute( szSql );
            //mysqlQuery.reset();

			sprintf_s(additionalInfo,sizeof(additionalInfo) - 1,"%d;%d;%d;%d;%d;%d;",
				pItem->equipdata.ucLevel,pItem->equipdata.gemHoleCount,pItem->equipdata.gemIds[0],
				pItem->equipdata.gemIds[1],pItem->equipdata.gemIds[2],pItem->equipdata.gemIds[3]);

            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_item(CharacterId,ItemGUID,ItemId,x,y,ItemName,ItemData,WhoIs,BagIndex,count,score,equiptype,additional_info) values(%0,%1,%2,-1,-1,'N/A',%3q,%4,%5,%6,%7,%8,%9q);", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID),mysqlpp::sql_bigint(pItem->itembaseinfo.nOnlyInt),pItem->itembaseinfo.ustItemID,bufferItemDataField,e_MaterialBag,i,pItem->itembaseinfo.ustItemCount,pItem->equipdata.fScore,mysqlpp::sql_int_unsigned(pItem->equipdata.ustEquipType),additionalInfo);
            mysqlQuery.reset();
        }

        // 任务背包
        pItem = pSave->dbInfo.itemData.ciTaskItems;
        for (int i=0; i<ITEM_BAGTASK_MAX; ++i, ++pItem)
        {
            if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
            { continue; }

            uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
            uint32 nActualSize = 0;
            if (!_charDataWR.WriteItemData( pItem, nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
            { continue; }
            compress( bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
            EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

            //sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_item where ItemGUID=%I64u and CharacterId=%ld;", pItem->itembaseinfo.nOnlyInt, pSave->dwCharacterID );
            //mysqlQuery.execute( szSql );
            //mysqlQuery.reset();

			sprintf_s(additionalInfo,sizeof(additionalInfo) - 1,"%d;%d;%d;%d;%d;%d;",
				pItem->equipdata.ucLevel,pItem->equipdata.gemHoleCount,pItem->equipdata.gemIds[0],
				pItem->equipdata.gemIds[1],pItem->equipdata.gemIds[2],pItem->equipdata.gemIds[3]);

            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_item(CharacterId,ItemGUID,ItemId,x,y,ItemName,ItemData,WhoIs,BagIndex,count,score,equiptype,additional_info) values(%0,%1,%2,-1,-1,'N/A',%3q,%4,%5,%6,%7,%8,%9q);", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID),mysqlpp::sql_bigint(pItem->itembaseinfo.nOnlyInt),pItem->itembaseinfo.ustItemID,bufferItemDataField,e_TaskBag,i,pItem->itembaseinfo.ustItemCount,pItem->equipdata.fScore,mysqlpp::sql_int_unsigned(pItem->equipdata.ustEquipType),additionalInfo);
            mysqlQuery.reset();
        }

        // 仓库
        pItem = pSave->storageInfo.stStorageItems;
        for (int i=0; i<STORAGE_ITEMGRID_MAX; ++i, ++pItem)
        {
            if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
            { continue; }

            uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
            uint32 nActualSize = 0;
            if (!_charDataWR.WriteItemData(pItem, nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
            { continue; }
            compress(bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
            EnCodeToString(bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

            //sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_item where ItemGUID=%I64u and CharacterId=%ld;", pItem->itembaseinfo.nOnlyInt, pSave->dwCharacterID );
            //mysqlQuery.execute( szSql );
            //mysqlQuery.reset();

			sprintf_s(additionalInfo,sizeof(additionalInfo) - 1,"%d;%d;%d;%d;%d;%d;",
				pItem->equipdata.ucLevel,pItem->equipdata.gemHoleCount,pItem->equipdata.gemIds[0],
				pItem->equipdata.gemIds[1],pItem->equipdata.gemIds[2],pItem->equipdata.gemIds[3]);

            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_item(CharacterId,ItemGUID,ItemId,x,y,ItemName,ItemData,WhoIs,BagIndex,count,score,equiptype,additional_info) values(%0,%1,%2,-1,-1,'N/A',%3q,%4,%5,%6,%7,%8,%9q);", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID),mysqlpp::sql_bigint(pItem->itembaseinfo.nOnlyInt),pItem->itembaseinfo.ustItemID,bufferItemDataField,e_StroageBag,i,pItem->itembaseinfo.ustItemCount,pItem->equipdata.fScore,mysqlpp::sql_int_unsigned(pItem->equipdata.ustEquipType),additionalInfo);
            mysqlQuery.reset();
        }

        // 装备背包
        pItem = pSave->dbInfo.visual.GetVisualArray();
        for (int i=0; i<EEquipPartType_MaxEquitPart; i++, pItem++)
        {
            if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
            { continue; }

            // 处理物品数据
            uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
            uint32 nActualSize = 0;
            if (!_charDataWR.WriteItemData(pItem , nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
            { continue; }
            compress( bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
            EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

            //sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_item where ItemGUID=%I64u and CharacterId=%ld;", pItem->itembaseinfo.nOnlyInt, pSave->dwCharacterID );
            //mysqlQuery.execute( szSql );
            //mysqlQuery.reset();

			sprintf_s(additionalInfo,sizeof(additionalInfo) - 1,"%d;%d;%d;%d;%d;%d;",
				pItem->equipdata.ucLevel,pItem->equipdata.gemHoleCount,pItem->equipdata.gemIds[0],
				pItem->equipdata.gemIds[1],pItem->equipdata.gemIds[2],pItem->equipdata.gemIds[3]);

            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_item(CharacterId,ItemGUID,ItemId,x,y,ItemName,ItemData,WhoIs,BagIndex,count,score,equiptype,additional_info) values(%0,%1,%2,-1,-1,'N/A',%3q,%4,%5,%6,%7,%8,%9q);", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID),mysqlpp::sql_bigint(pItem->itembaseinfo.nOnlyInt),pItem->itembaseinfo.ustItemID,bufferItemDataField,e_VisualBag,i,pItem->itembaseinfo.ustItemCount,pItem->equipdata.fScore,mysqlpp::sql_int_unsigned(pItem->equipdata.ustEquipType),additionalInfo);
            mysqlQuery.reset();
        }

        // 坐骑
        SMountItem* pMountItem = pSave->dbInfo.itemData.miItems;
        for ( int i=0; i<ITEM_MOUNT_MAXCOUNT; ++i, ++pMountItem )
        {
            if( pMountItem->baseInfo.id == InvalidLogicNumber || pMountItem->baseInfo.guid <= 0)
            { continue; }

            uint32 compressBufferSize = CharChunkWR::CD_ZipTempBufferSize;
            uint32 nActualSize = 0;
            if ( !_charDataWR.WriteMountData( pMountItem, nActualSize,bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ) )
            { 
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CharacterId[%ld] 写人物坐骑[%u] [%I64u] WriteMountData 数据出错",pSave->dwCharacterID, pMountItem->baseInfo.id, pMountItem->baseInfo.guid );
                continue; 
            }

            compress( bufferTempZipItem,(uLongf*)&compressBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
            EnCodeToString( bufferTempZipItem, bufferItemDataField, compressBufferSize, sizeof(bufferItemDataField));

            //sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_mount where GUID=%I64u and CharacterId=%ld and WhereIs=%d;", pMountItem->baseInfo.guid, pSave->dwCharacterID,e_CharBag );
            //mysqlQuery.execute( szSql );
            //mysqlQuery.reset();

            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_mount(CharacterId,GUID,DataInfo,WhereIs,Id,Level) values(%0,%1,%2q,%3,%4,%5);", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID),mysqlpp::sql_bigint(pMountItem->baseInfo.guid),bufferItemDataField,e_CharBag,mysqlpp::sql_int_unsigned(pMountItem->GetMountID()),mysqlpp::sql_int_unsigned(pMountItem->baseInfo.level));
            mysqlQuery.reset();
        }

        // 仓库坐骑
        SMountItem* pStorageMount = pSave->storageInfo.xStorageMounts;
        for ( int i=0; i<STORAGE_MOUNTGRID_MAX; ++i, ++pStorageMount )
        {
            if( pStorageMount->baseInfo.id == InvalidLogicNumber || pStorageMount->baseInfo.guid <= 0)
            { continue; }

            uint32 compressBufferSize = CharChunkWR::CD_ZipTempBufferSize;
            uint32 nActualSize = 0;
            if ( !_charDataWR.WriteMountData( pStorageMount, nActualSize,bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ) )
            { 
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CharacterId[%ld]  写仓库坐骑[%u] [%I64u] WriteMountData 数据出错",pSave->dwCharacterID, pStorageMount->baseInfo.id, pStorageMount->baseInfo.guid );
                continue; 
            }
            compress( bufferTempZipItem,(uLongf*)&compressBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
            EnCodeToString( bufferTempZipItem, bufferItemDataField, compressBufferSize, sizeof(bufferItemDataField));

            //sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_mount where GUID=%I64u and CharacterId=%ld and WhereIs=%d;", pStorageMount->baseInfo.guid, pSave->dwCharacterID,e_StroageBag );
            //mysqlQuery.execute( szSql );
            //mysqlQuery.reset();

            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_mount(CharacterId,GUID,DataInfo,WhereIs,Id,Level) values(%0,%1,%2q,%3,%4,%5);", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID),mysqlpp::sql_bigint(pStorageMount->baseInfo.guid),bufferItemDataField,e_StroageBag,mysqlpp::sql_int_unsigned(pMountItem->GetMountID()),mysqlpp::sql_int_unsigned(pMountItem->baseInfo.level) );
            mysqlQuery.reset();
        }

        // 宠物
        SPetItem* pPetItem = pSave->dbInfo.itemData.petItems;
        for ( int i=0; i<ITEM_PET_MAXCOUNT; ++i, ++pPetItem )
        {
            if( pPetItem->baseInfo.petId == InvalidLogicNumber || pPetItem->baseInfo.guid == 0)
            { continue; }

            uint32 compressBufferSize = CharChunkWR::CD_ZipTempBufferSize;
            uint32 nActualSize = 0;
            if ( !_charDataWR.WritePetData( pPetItem, nActualSize,bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ) )
            { 
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CharacterId[%ld] 写人物宠物[%u] [%I64u] WritePetData 数据出错",pSave->dwCharacterID, pPetItem->baseInfo.petId, pPetItem->baseInfo.guid );
                continue; 
            }

            compress( bufferTempZipItem,(uLongf*)&compressBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
            EnCodeToString( bufferTempZipItem, bufferItemDataField, compressBufferSize, sizeof(bufferItemDataField));

            //sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_Pet where GUID=%I64u and CharacterId=%ld and WhereIs=%d;", pPetItem->baseInfo.guid, pSave->dwCharacterID,e_CharBag );
            //mysqlQuery.execute( szSql );
            //mysqlQuery.reset();

            strncpy_s( szSql, sizeof( szSql ), "insert into t_game_pet(CharacterId,GUID,DataInfo,WhereIs,Id,Level,quality) values(%0,%1,%2q,%3,%4,%5,%6);", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
			mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID),mysqlpp::sql_bigint(pPetItem->baseInfo.guid),bufferItemDataField,e_CharBag,mysqlpp::sql_int_unsigned(pPetItem->GetPetID()),mysqlpp::sql_int_unsigned(pPetItem->baseInfo.level),mysqlpp::sql_int_unsigned(pPetItem->baseInfo.quality));
            mysqlQuery.reset();
        }

        // 繁殖宠物
        SPetItem* pPetBreed = &pSave->dbInfo.itemData.petBreedItem;
        if( pPetBreed->baseInfo.petId != InvalidLogicNumber && pPetBreed->baseInfo.guid != 0)
        {
            uint32 compressBufferSize = CharChunkWR::CD_ZipTempBufferSize;
            uint32 nActualSize = 0;
            if ( _charDataWR.WritePetData( pPetBreed, nActualSize,bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ) )
            { 
                compress( bufferTempZipItem,(uLongf*)&compressBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
                EnCodeToString( bufferTempZipItem, bufferItemDataField, compressBufferSize, sizeof(bufferItemDataField));

                //sprintf_s( szSql, sizeof( szSql ) - 1, "delete from t_game_Pet where GUID=%I64u and CharacterId=%ld and WhereIs=%d;", pPetBreed->baseInfo.guid, pSave->dwCharacterID,e_NpcBag );
                //mysqlQuery.execute( szSql );
                //mysqlQuery.reset();

                strncpy_s( szSql, sizeof( szSql ), "insert into t_game_pet(CharacterId,GUID,DataInfo,WhereIs,Id,Level,quality) values(%0,%1,%2q,%3,%4,%5,%6);", sizeof( szSql ) - 1 );
                mysqlQuery << szSql;
                mysqlQuery.parse();
                mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID),mysqlpp::sql_bigint(pPetBreed->baseInfo.guid),bufferItemDataField,e_NpcBag,mysqlpp::sql_int_unsigned(pPetItem->GetPetID()),mysqlpp::sql_int_unsigned(pPetItem->baseInfo.level),mysqlpp::sql_int_unsigned(pPetItem->baseInfo.quality));
                mysqlQuery.reset();
            }
            else
            {
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CharacterId[%ld] 写繁殖宠物[%u] [%I64u] WritePetData 数据出错",pSave->dwCharacterID, pPetBreed->baseInfo.petId, pPetBreed->baseInfo.guid );
            }
        }


        //if ( strlen( pSave->newName ) > 0)
        //{ // 需要改名字
        //    strncpy_s( szSql, sizeof( szSql ), "update t_game_character set CharName=%1q where CharacterId=%0;", sizeof(szSql)-1 );
        //    mysqlQuery << szSql;
        //    mysqlQuery.parse();
        //    mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID), _tUTF8CHAR(pSave->newName) );
        //    mysqlQuery.reset();

        //    strncpy_s( szSql, sizeof( szSql ), "update relation set Name=%1q where RelationDBID=%0;", sizeof(szSql)-1 );
        //    mysqlQuery << szSql;
        //    mysqlQuery.parse();
        //    mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID), _tUTF8CHAR(pSave->newName) );
        //    mysqlQuery.reset();


        //    strncpy_s( szSql, sizeof( szSql ), "update t_game_guildmember set Name=%1q where MemberID=%0;", sizeof(szSql)-1 );
        //    mysqlQuery << szSql;
        //    mysqlQuery.parse();
        //    mysqlQuery.execute( mysqlpp::sql_int_unsigned(pSave->dwCharacterID), _tUTF8CHAR(pSave->newName) );
        //    mysqlQuery.reset();
        //}
        trans.commit();
    TRYEND

    CHECK_SQL_RESULT( result ) // 执行检测

    if (G_PrinfInfo == PRINTFSAVEROLETIME)
    { LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"MYSQL UpdateRoleInfo Once Time = %d ms",HQ_TimeGetTime() - Performance_SaveRoleBeginSQLTime); }

    if ( RESULT_SUCCESS(result) )
    {
        if ( pSave->shServerId != DiskServerId )
        { // 需要回馈消息的时候
            DBAckOperSucc acksucc;
            acksucc.dwMsgType     = DBMSG_SAVECHARACTER;
            acksucc.dwMsgID       = pSave->subMarker;
            acksucc.dwCharacterID = pSave->dwCharacterID;
            theMysqlCommunication.PushAckMessage( &acksucc, pSqlMessage->nClientId );
        }
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"[%s] [%u] [%u] [%u] [%u]", pSave->dbInfo.baseinfo.aptotic.szCharacterName, pSave->dwCharacterID, pSave->dbInfo.baseinfo.liveinfo.dwMoney, pSave->storageInfo.dwStorageMoney, pSave->dbInfo.baseinfo.liveinfo.jinPiao, pSave->dbInfo.baseinfo.liveinfo.jiaoZi);

        DB2DBNotifyFileDBSaveChar dbNotifyMsg;
        dbNotifyMsg.charId = pSave->dwCharacterID;
        dbNotifyMsg.lifeId = pDetailSqlMessage->time;
        theMysqlCommunication.PushAckMessage( &dbNotifyMsg, pSqlMessage->nClientId );
        //uint32 result = theFileMappingCharSaveManager.RemoveDataFile( pSave->dwCharacterID, pDetailSqlMessage->time );
        //if ( result != ER_Success )
        //{
        //    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"RemoveDataFile [%u] time[%u] Fail", pSave->dwCharacterID );
        //}
    }
    else
    { 
        LOG_MESSAGE(SQLOBJECT,LOG_PRIORITY_ERROR,"UpdateRoleInfo(%ld) 失败", pSave->dwCharacterID);
    }

    SaveGmInfo();

    if (G_PrinfInfo == PRINTFSAVEROLETIME)
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Save Role Once Time = %d ms",HQ_TimeGetTime() - Performance_SaveRoleBeginTime);
        G_PrinfInfo = NOPRINT;
    }
}

void NormalLogicWorkThread::OnQueryDelChar( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgDeleteChar2* pDetailSqlMessage = (SqlMessageDBMsgDeleteChar2*)pSqlMessage;
    DBMsgDeleteChar2* pDelete = &pDetailSqlMessage->msg;

    char szSql[1024] = {0};
    memset( szSql, 0, sizeof(szSql));
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "update t_game_character set IsDel=1, DelTime=now() where (AccountId=%ld) and (CharacterID=%ld);", pDelete->dwAccountID, pDelete->dwCharId );

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();
    TRYEND

    CHECK_SQL_RESULT( result ) // 执行检测

    DBMsgAckDeleteChar2 ackDelete;
    ackDelete.shServerId = pDelete->shServerId;
    ackDelete.header.stID = pDelete->header.stID;    
    ackDelete.stWhichSlot = pDelete->stWhichSlot;
    ackDelete.ustLifeCode = pDelete->ustLifeCode;
    ackDelete.bSuccessed = true;
    theMysqlCommunication.PushAckMessage( &ackDelete, pSqlMessage->nClientId );
}

void NormalLogicWorkThread::OnQueryCancelDelChar( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgCancelDelChar* pDetailSqlMessage = (SqlMessageDBMsgCancelDelChar*)pSqlMessage;
    DBMsgCancelDelChar* pCancel = &pDetailSqlMessage->msg;
    char szSql[1024] = {0};
    uint32 result = ER_Success;
    memset( szSql, 0, sizeof(szSql));
    sprintf_s( szSql, sizeof( szSql ) - 1, "update t_game_character set IsDel = 0 where (AccountId=%ld) and (CharacterID=%d) and (IsDel=1) and (datediff(now(),DelTime)<=7);", pCancel->dwAccountID, pCancel->dwCharId );

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();
    TRYEND

    CHECK_SQL_RESULT( result ) // 执行检测

    DBMsgAckCancelDelChar ackCancel;
    ackCancel.shServerId = pCancel->shServerId;
    ackCancel.header.stID = pCancel->header.stID;    
    ackCancel.stWhichSlot = pCancel->stWhichSlot;
    ackCancel.ustLifeCode = pCancel->ustLifeCode;
    ackCancel.bSuccessed = true;
    theMysqlCommunication.PushAckMessage( &ackCancel, pSqlMessage->nClientId );
}

void NormalLogicWorkThread::OnQueryPetBreed( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgPetBreedQueryReq* pDetailSqlMessage = (SqlMessageDBMsgPetBreedQueryReq*)pSqlMessage;
    DBMsgPetBreedQueryReq* pQuery = &pDetailSqlMessage->msg;
    char szSql[1024] = {0};
    uint32 result = ER_Success;
    memset( szSql, 0, sizeof(szSql));
    sprintf_s( szSql, sizeof( szSql ) - 1, "select CharacterId from t_game_pet where (CharacterId=%ld) and WhereIs=%d;", pQuery->dwDBCharacterID, e_NpcBag );
    
    bool bIsAcquired = false;
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty())
        { bIsAcquired = false; }
        else
        { bIsAcquired = true; }
        mysqlQuery.reset();
    TRYEND

    CHECK_SQL_RESULT( result ) // 执行检测

    DBMsgPetBreedQueryAck ackQuery;
    ackQuery.shServerId      = pQuery->shServerId;
    ackQuery.header.stID     = pQuery->header.stID;    
    ackQuery.ustLifeCode     = pQuery->ustLifeCode;
    ackQuery.dwDBCharacterID = pQuery->dwDBCharacterID;
    ackQuery.nPetGuid        = pQuery->nPetGuid;
    ackQuery.bIsAcquired     = bIsAcquired;
    theMysqlCommunication.PushAckMessage( &ackQuery, pSqlMessage->nClientId );
}
void NormalLogicWorkThread::OnUpdateAccountYuanBao ( BaseSqlMessage* pSqlMessage )
{
	//只做Update操作 
	SqlMessageGS2DBUpdateYuanBaoData* pDetailSqlMessage = (SqlMessageGS2DBUpdateYuanBaoData*)pSqlMessage;
    GS2DBUpdateYuanBaoData* pQuery = &pDetailSqlMessage->msg;
	DB2GSUpdateYuanBaoData msg;
	msg.AccountID = pQuery->AccountID;
	msg.States = pQuery->States;
    char szSql[1024] = {0};
    uint32 result = ER_Success;
    memset( szSql, 0, sizeof(szSql));
    sprintf_s( szSql, sizeof( szSql ) - 1, "update accountyuanbaostates set states =%ld where accountid = %ld;",pQuery->States,pQuery->AccountID);
    TRYBEGIN
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
			mysqlQuery.execute( szSql );
			mysqlQuery.reset();
	TRYEND
	CHECK_SQL_RESULT( result ) // 执行检测
	if ( RESULT_FAILED(result))
		msg.result = false;
	else
		msg.result = true;
	msg.header.stID     = pQuery->header.stID;   
	//回发操作是否成功的消息的GameServer
	theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
	return;
}
void NormalLogicWorkThread::OnUpdatePlayerPoint( BaseSqlMessage* pSqlMessage )
{
	SqlMessageGS2DBUpdatePlayerPoint* pDetailSqlMessage = (SqlMessageGS2DBUpdatePlayerPoint*)pSqlMessage;
    GS2DBUpdatePlayerPoint* pQuery = &pDetailSqlMessage->msg;
	if(!pQuery)
		return;
	//开始更新玩家点数 直接执行存储过程
	DB2GSUpdatePlayerPoint msg;
	msg.PlayerID = pQuery->PlayerID;
	msg.Op = pQuery->Op;
	msg.ChangeValue = pQuery->Value;//修改改变的值
	msg.header.stID     = pQuery->header.stID;   
	uint32 result = ER_Success;
	char szSql[1024] = {0};
	sprintf_s( szSql, sizeof( szSql ) - 1,"call GamePoint( %d, %d, %d, %d);",  
			pQuery->ID,pQuery->Op,pQuery->Value,pQuery->States);
	TRYBEGIN  
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
		mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
		if ( res && !res.empty())
		{
			uint32 count = res[0][0];
			if ( count == 1 )
			{
				msg.ID = res[0][1];
				msg.Value = res[0][2];
				msg.States = res[0][3];
				result = ER_Success;
			}
			else if ( count == 0)
			{
				result = ER_Failed;
			}
		}
		FREESTOREPROCEDURE_TRY;
	TRYEND
	if (result == ER_Success)
	{
		//执行成功 告诉客户端 点数增加成功
		theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
	}
}
void TestProcedure()
{
    //{ // 实际用这个 实际会有17*多ms的处理时间
    //    //使用存储过程批量存储一个玩家的数据
    //    std::string strItemGUID;
    //    std::string strItemID;
    //    std::string strItemName;
    //    std::string strItemData;
    //    std::string strWhoIs;
    //    std::string strBag;
    //    std::string strX;
    //    std::string strY;
    //    std::string strBagIndex;

    //    std::string strMountID;
    //    std::string strMountGUID;
    //    std::string strMountData;
    //    std::string strCounter;

    //    // 普通物品背包
    //    char szTmp[64] = {0};
    //    memset( szTmp, 0, sizeof(szTmp));
    //    sprintf_s( szTmp, "%d", e_CharBag);
    //    strBag = szTmp;
    //    SCharItem* pItem = pSave->dbInfo.itemData.stPackItems;

    //    static uint8 bufferItemDataChunk[ CharChunkWR::CD_ItemInfoBufferSize   ] = {0};
    //    static uint8 bufferTempZipItem  [ CharChunkWR::CD_ZipTempBufferSize    ] = {0};
    //    static int8  bufferItemDataField[ CharChunkWR::CD_EncodeFieldBufferSize] = {0};

    //    for (int i=0; i<ITEM_BAGMAX; ++i, ++pItem)
    //    {
    //        if( pItem->itembaseinfo.ustItemID == ErrorUnsignedShortID || pItem->itembaseinfo.nOnlyInt <= 0)
    //        { continue; }

    //        // 处理物品数据
    //        uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    //        uint32 nActualSize = 0;
    //        if (!_charDataWR.WriteItemData( pItem, nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
    //        { continue; }
    //        compress( bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
    //        EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

    //        strItemGUID += BigInt2String(pItem->itembaseinfo.nOnlyInt);
    //        strItemGUID += "|";

    //        sprintf_s( szTmp, "%d", pItem->itembaseinfo.ustItemID);            
    //        strItemID += szTmp;
    //        strItemID += "|";

    //        strItemName += "N/A";
    //        strItemName += "|";

    //        strItemData += bufferItemDataField;
    //        strItemData += "|";

    //        strWhoIs += strBag;
    //        strWhoIs += "|";

    //        //X，Y字段直接写死-1 暂时没有用处
    //        strX += "-1|";
    //        strY += "-1|";

    //        sprintf_s( szTmp, "%d", i);
    //        strBagIndex += szTmp;
    //        strBagIndex += "|";
    //    }

    //    // 材料背包
    //    memset( szTmp, 0, sizeof(szTmp));
    //    sprintf_s( szTmp, "%d", e_MaterialBag);
    //    strBag = szTmp;
    //    pItem = pSave->dbInfo.itemData.ciMaterialItems;
    //    for (int i=0; i<ITEM_BAGMATERIAL_MAX; ++i, ++pItem)
    //    {
    //        if( pItem->itembaseinfo.ustItemID == ErrorUnsignedShortID || pItem->itembaseinfo.nOnlyInt <= 0)
    //        { continue; }

    //        uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    //        uint32 nActualSize = 0;
    //        if (! _charDataWR.WriteItemData( pItem, nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
    //        { continue; }
    //        compress( bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
    //        EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

    //        strItemGUID += BigInt2String(pItem->itembaseinfo.nOnlyInt);
    //        strItemGUID += "|";

    //        sprintf_s( szTmp, "%d", pItem->itembaseinfo.ustItemID);            
    //        strItemID += szTmp;
    //        strItemID += "|";

    //        strItemName += "N/A";
    //        strItemName += "|";

    //        strItemData += bufferItemDataField;
    //        strItemData += "|";

    //        strWhoIs += strBag;
    //        strWhoIs += "|";

    //        //X，Y字段直接写死-1 暂时没有用处
    //        strX += "-1|";
    //        strY += "-1|";

    //        sprintf_s( szTmp, "%d", i);
    //        strBagIndex += szTmp;
    //        strBagIndex += "|";
    //    }

    //    // 任务背包
    //    memset( szTmp, 0, sizeof(szTmp));
    //    sprintf_s( szTmp, "%d", e_TaskBag);
    //    strBag = szTmp;
    //    pItem = pSave->dbInfo.itemData.ciTaskItems;
    //    for (int i=0; i<ITEM_BAGTASK_MAX; ++i, ++pItem)
    //    {
    //        if( pItem->itembaseinfo.ustItemID == ErrorUnsignedShortID || pItem->itembaseinfo.nOnlyInt <= 0)
    //        { continue; }

    //        uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    //        uint32 nActualSize = 0;
    //        if (!_charDataWR.WriteItemData( pItem, nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
    //        { continue; }
    //        compress( bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
    //        EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

    //        strItemGUID += BigInt2String(pItem->itembaseinfo.nOnlyInt);
    //        strItemGUID += "|";

    //        sprintf_s( szTmp, "%d", pItem->itembaseinfo.ustItemID);            
    //        strItemID += szTmp;
    //        strItemID += "|";

    //        strItemName += "N/A";
    //        strItemName += "|";

    //        strItemData += bufferItemDataField;
    //        strItemData += "|";

    //        strWhoIs += strBag;
    //        strWhoIs += "|";

    //        //X，Y字段直接写死-1 暂时没有用处
    //        strX += "-1|";
    //        strY += "-1|";

    //        sprintf_s( szTmp, "%d", i);
    //        strBagIndex += szTmp;
    //        strBagIndex += "|";
    //    }

    //    // 仓库
    //    sprintf_s( szTmp, "%d", e_StroageBag);
    //    strBag = szTmp;
    //    pItem = pSave->storageInfo.stStorageItems;

    //    for (int i=0; i<STORAGE_Grigs_MAX; ++i, ++pItem)
    //    {
    //        if( pItem->itembaseinfo.ustItemID == ErrorUnsignedShortID || pItem->itembaseinfo.nOnlyInt <= 0)
    //        { continue; }

    //        uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    //        uint32 nActualSize = 0;
    //        if (!_charDataWR.WriteItemData(pItem, nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
    //        { continue; }
    //        compress(bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
    //        EnCodeToString(bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

    //        strItemGUID += BigInt2String(pItem->itembaseinfo.nOnlyInt);
    //        strItemGUID += "|";

    //        sprintf_s( szTmp, "%d", pItem->itembaseinfo.ustItemID);
    //        strItemID += szTmp;
    //        strItemID += "|";

    //        strItemName += "N/A";
    //        strItemName += "|";

    //        strItemData += bufferItemDataField;
    //        strItemData += "|";

    //        strWhoIs += strBag;
    //        strWhoIs += "|";

    //        strX += "-1|";
    //        strY += "-1|";

    //        sprintf_s( szTmp, "%d", i);
    //        strBagIndex += szTmp;
    //        strBagIndex += "|";
    //    }

    //    // 装备背包
    //    sprintf_s( szTmp, "%d", e_VisualBag);
    //    strBag = szTmp;
    //    pItem = pSave->dbInfo.visual.GetVisualArray();
    //    for (int i=0; i<EEquipPartType_MaxEquitPart; i++, pItem++)
    //    {
    //        if( pItem->itembaseinfo.ustItemID == ErrorUnsignedShortID || pItem->itembaseinfo.nOnlyInt <= 0)
    //        { continue; }

    //        // 处理物品数据
    //        uint32 zipBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    //        uint32 nActualSize = 0;
    //        if (!_charDataWR.WriteItemData(pItem , nActualSize, bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ))
    //        { continue; }
    //        compress( bufferTempZipItem,(uLongf*)&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
    //        EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, CharChunkWR::CD_EncodeFieldBufferSize );

    //        strItemGUID += BigInt2String(pItem->itembaseinfo.nOnlyInt);
    //        strItemGUID += "|";

    //        sprintf_s( szTmp, "%d", pItem->itembaseinfo.ustItemID);
    //        strItemID += szTmp;
    //        strItemID += "|";

    //        strItemName += "N/A";
    //        strItemName += "|";

    //        strItemData += bufferItemDataField;
    //        strItemData += "|";

    //        strWhoIs += strBag;
    //        strWhoIs += "|";

    //        //X，Y字段直接写死-1 暂时没有用处
    //        strX += "-1|";
    //        strY += "-1|";

    //        sprintf_s( szTmp, "%d", i);
    //        strBagIndex += szTmp;
    //        strBagIndex += "|";
    //    }

    //    // 坐骑
    //    SMountItem* pMountItem = pSave->dbInfo.itemData.miItems;
    //    for ( int i=0; i<ITEM_MOUNT_MAXCOUNT; ++i, ++pMountItem )
    //    {
    //        if( pMountItem->baseInfo.id == ErrorUnsignedShortID || pMountItem->baseInfo.guid <= 0)
    //        { continue; }

    //        uint32 compressBufferSize = CharChunkWR::CD_ZipTempBufferSize;
    //        uint32 nActualSize = 0;
    //        if ( !_charDataWR.WriteMountData( pMountItem, nActualSize,bufferItemDataChunk, CharChunkWR::CD_ItemInfoBufferSize ) )
    //        { continue; }
    //        compress( bufferTempZipItem,(uLongf*)&compressBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
    //        EnCodeToString( bufferTempZipItem, bufferItemDataField, compressBufferSize, sizeof(bufferItemDataField));

    //        sprintf_s( szTmp, "%d", pMountItem->baseInfo.id );
    //        strMountID += szTmp;
    //        strMountID += "|";

    //        strMountGUID += BigInt2String(pMountItem->baseInfo.guid);
    //        strMountGUID += "|";

    //        strMountData += bufferItemDataField;
    //        strMountData += "|";
    //    }

    //    ////////////////////////////////////////////////////////////////////////////////
    //    //清除所有带有分隔符“|”中的尾部符号
    //    if (!strWhoIs.IsEmpty())
    //    {
    //        strWhoIs.SetAt(strWhoIs.GetLength()-1, '\0');
    //        strItemGUID.SetAt(strItemGUID.GetLength()-1, '\0');
    //        strItemID.SetAt(strItemID.GetLength()-1, '\0');
    //        strX.SetAt(strX.GetLength()-1, '\0');
    //        strY.SetAt(strY.GetLength()-1, '\0');
    //        strItemName.SetAt(strItemName.GetLength()-1, '\0');
    //        strItemData.SetAt(strItemData.GetLength()-1, '\0');
    //    }        

    //    sprintf_s( szSql, "UpdateRoleInfo %d, "     // ID
    //        "%d, "                                  // 仓库是否打开
    //        "'%s', "                                // WhoIs
    //        "'%s', "                                // ItemGUID
    //        "'%s', "                                // ItemID
    //        "'%s', "                                // X
    //        "'%s', "                                // Y
    //        "'%s', "                                // BagIndex
    //        "'%s', "                                // ItemName
    //        "'%s', "                                // ItemData
    //        "'%s', "                                // VisualDataInfo
    //        "'%s', "                                // CharacterDataInfo
    //        "%d, "                                  // OnlineTime
    //        "%d, "                                  // Money
    //        "%d, "                                  // StorageMoney
    //        "%d, "                                  // Level
    //        "'%s', "                                // OtherData
    //        "%I64u, "                               // Exp
    //        "%d, "                                  // KillValue
    //        "%d, "                                  // KillFlag
    //        "%d, "                                  // KillStateTime
    //        "%d,  "                                 // jinding
    //        "%d,  "                                 // jinpiao
    //        "'%s', "                                // ExtendData
    //        "'%s', "                                // MountID
    //        "'%s', "                                // MountGUID
    //        "'%s' "                                 // MountData

    //        ,pSave->dwCharacterID,                        // ID
    //        1,                                            // 仓库是否打开
    //        strWhoIs.c_str(),                             // WhoIs
    //        strItemGUID.c_str(),                          // ItemGUID
    //        strItemID.c_str(),                            // ItemID
    //        strX.c_str(),                                 // X
    //        strY.c_str(),                                 // Y
    //        strBagIndex.c_str(),                          // BagIndex
    //        strItemName.c_str(),                          // ItemName
    //        strItemData.c_str(),                          // ItemData
    //        bufferVisualInfoField,                        // VisualDataInfo
    //        bufferBaseInfoField,                          // CharacterDataInfo
    //        dwTime,                                       // OnlineTime
    //        pSave->dbInfo.baseinfo.liveinfo.dwMoney,      // Money
    //        pSave->storageInfo.dwStorageMoney,            // StorageMoney
    //        pSave->dbInfo.baseinfo.liveinfo.ustLevel,     // Level
    //        bufferOtherDataField,                         // OtherData
    //        pSave->dbInfo.baseinfo.liveinfo.dwExp,        // Exp
    //        pSave->nPKValue,                              // KillValue
    //        pSave->stPKProtectFlag,                       // KillFlag
    //        pSave->nStayInHellTime,                       // StayInHellTime
    //        pSave->dbInfo.baseinfo.liveinfo.jinDing,      // jinDing
    //        pSave->dbInfo.baseinfo.liveinfo.jinPiao,      // jinDing
    //        bufferExtendDataField,                        // ExtendData
    //        strMountID.c_str(),                           // MountID
    //        strMountGUID.c_str(),                         // MountGUID
    //        strMountData.c_str()                          // MountData
    //        );

    //    uint32 Performance_SaveRoleBeginSQLTime = HQ_TimeGetTime();

    //    std::string strCode;
    //    TRYBEGIN
    //        mysqlpp::Query mysqlQuery     = _pMysqlConnect->query();        
    //    mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql) );
    //    if ( res && res.empty() )
    //    {
    //        strCode = res[0][0];
    //    }
    //    FREESTOREPROCEDURE_TRY;
    //    TRYEND

    //        CHECK_SQL_RESULT( result ) // 执行检测

    //        if (G_PrinfInfo == PRINTFSAVEROLETIME)
    //        { LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"SQL UpdateRoleInfo Once Time = %d ms",HQ_TimeGetTime() - Performance_SaveRoleBeginSQLTime); }

    //        if ( RESULT_SUCCESS(result) )
    //        {
    //            if ( !strCode.empty() )
    //            {
    //                LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_INFO,"UpdateRoleInfo Code(%s)", strCode.c_str());
    //            }

    //            if ( pSave->shServerId != DiskServerId )
    //            { // 需要回馈消息的时候
    //                DBAckOperSucc acksucc;
    //                acksucc.dwMsgType     = DBMSG_SAVECHARACTER;
    //                acksucc.dwMsgID       = pSave->subMarker;
    //                acksucc.dwCharacterID = pSave->dwCharacterID;
    //                GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &acksucc);
    //            }
    //            GetFileDatabase().RemoveDataFile( pSave->dwCharacterID, pDetailSqlMessage->time );
    //        }
    //        else
    //        { 
    //            LOG_MESSAGE(SQLOBJECT,LOG_PRIORITY_ERROR,"UpdateRoleInfo(%ld) 失败", pSave->dwCharacterID);
    //        }
    //}

    //SaveGmInfo();

    //if (G_PrinfInfo == PRINTFSAVEROLETIME)
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Save Role Once Time = %d ms",HQ_TimeGetTime() - Performance_SaveRoleBeginTime);
    //    G_PrinfInfo = NOPRINT;
    //}
}