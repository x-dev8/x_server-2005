#include "MSSqlWorkThread.h"
#include "DatabaseServerApp.h"
#include "helper.h"
#include "zlib/zlib.h"
#include "DataChunkWriter.h"
#include "FuncPerformanceLog.h"
#include "tstring.h"
#include "FileDatabase.h"
#include "RoleDataCache.h"
#include "GameTime.h"
#include "GameDefineSerialize.h"
#include "AccountBillingWorkThread.h"

#define ACKYUANBAOINFOTIME (1000 * 60 * 1)

#pragma comment(lib, "Rpcrt4.lib")

using Common::_tstring; 
using DataBase::CConnection;
using DataBase::CRecordset;

DatabaseServerWorkThread::DatabaseServerWorkThread() : _bHaveLoadGmInfo ( false ), _connectState( MSS_NotConneted )
{
    _pRoleConn    = NULL;
    _pRoleConnOld = NULL;

    //每个线程内如果需要使用COM都需要安装COM环境
    m_dwThreadId = 0xffffffff;

    // 设置错误日志和普通消息日志回调函数
    //其实不需要每个线程都设置一次 不过这么做也不会有什么影响    
    DataBase::CDebugOutPut::SetLogOut(NULL);
    DataBase::CDebugOutPut::SetErrorOut(NULL);
                         
    memset( _charBaseInfoBuffer, 0, CD_CharBaseInfoBufferSize );
    memset( _itemDataBuffer,     0, CD_ItemInfoBufferSize     );
    memset( _visualDataBuffer,   0, CD_VisualInfoBufferSize   );
    memset( _otherDataBuffer,    0, CD_OtherInfoBufferSize    );
    memset( _extendDataBuffer,   0, CD_ExtendInfoBufferSize   );
    memset( _mountDataBuffer,    0, CD_MountInfoBufferSize    );
    _lastReconnectTime = 0;
    _checkQueryTime    = 0;
}

DatabaseServerWorkThread::~DatabaseServerWorkThread()
{  
    if ( _pRoleConn != NULL )
    { 
        delete _pRoleConn; 
        _pRoleConn = NULL;
    }

    if ( _pRoleConnOld )
    {
        delete _pRoleConnOld;
        _pRoleConnOld = NULL;
    }
}        

bool DatabaseServerWorkThread::TryConnectToDatabase()
{
    switch ( _connectState )
    {
    case MSS_NotConneted:
        {
            // 不要频繁Connect
            if ( _lastReconnectTime != 0 && !GameTime::IsPassCurrentTime( _lastReconnectTime, ECD_ReconnectPlatformTimeInterval ) )
            { return false; }

            if ( _pRoleConn == NULL )
            {
                _pRoleConn = new DataBase::CConnection;
                if ( _pRoleConn == NULL)
                { return false;}
            }

            DatabaseServerApp* pSrv = GetDatabaseServerApp();

            //if (!m_pAccConn.IsOpen())
            //{ accsuss = m_pAccConn.Open(pSrv->m_strAccDBSrvIp.c_str(), pSrv->m_strAccDBName.c_str(), pSrv->m_strAccDBSrvUID.c_str(), pSrv->m_strAccDBSrvPWD.c_str()); }

            bool bResult = _pRoleConn->Open(pSrv->m_strRoleDBSrvIp.c_str(), pSrv->m_strRoleDBName.c_str(), pSrv->m_strRoleDBSrvUID.c_str(), pSrv->m_strRoleDBSrvPWD.c_str());
            if ( bResult )
            {
                uint32 laterTime = 5000;
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "WorkThread[%d] Connect MSSql Success. ", m_dwThreadId );
                _connectState = MSS_Connected;

                if ( _pRoleConnOld )
                {
                    _pRoleConnOld->Close();
                    delete _pRoleConnOld;
                    _pRoleConnOld = NULL;
                }
                
                return true;
            }
            else
            {   
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "WorkThread[%d] Connect MSSql Fail!", m_dwThreadId );
                _lastReconnectTime = HQ_TimeGetTime();
                _connectState      = MSS_Reconnect;
                return false;
            }
        }
        break;
    case MSS_Reconnect:
        {
            if ( _pRoleConn != NULL)
            {
                _pRoleConnOld = _pRoleConn;
                //_pRoleConn->Close();
                //delete _pRoleConn;
                _pRoleConn = NULL;
            }

            _connectState = MSS_NotConneted;
        }
        break;
    case MSS_Connected:
        {
            return true;
        }
        break;
    }
    return true;
}

BOOL DatabaseServerWorkThread::LockQuery()
{
    m_csQuery.Lock();
    return TRUE;
}

BOOL DatabaseServerWorkThread::UnlockQuery()
{
    m_csQuery.Unlock();
    return TRUE;
}

BOOL DatabaseServerWorkThread::PushQuery( BaseSqlMessage* pSqlMessage )
{
    if ( pSqlMessage == NULL )
    { return FALSE; }

    return m_taskqueue.PushQuery( pSqlMessage );
}

void DatabaseServerWorkThread::Update()
{
    if( !TryConnectToDatabase() )
    { return;}
}

//CRecordset DatabaseServerWorkThread::AccQuery(const char* pszSql )
//{
//    // 这里返回的记录集只是一个游标（相当于数据库的指针）
//    // 所以即使不返回引用也不会对性能上造成什么影响
//    return m_pAccConn.Execute(pszSql);
//}

CRecordset DatabaseServerWorkThread::RoleQuery(const char* pszSql )
{
    //这里返回的记录集只是一个游标（相当于数据库的指针）
    //所以即使不返回引用也不会对性能上造成什么影响
    if ( !_pRoleConn->IsOpen())
    { return NULL; }
    return _pRoleConn->Execute(pszSql);
}

uint32 DatabaseServerWorkThread::OnQueryAccountChar( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgQueryAccountChar* pDetailSqlMesage = (SqlMessageDBMsgQueryAccountChar*)pSqlMessage;

    DBMsgQueryAccountChar* pReq = &(pDetailSqlMesage->msg);

    char szSql[512]  = {0};
    memset( szSql, 0, sizeof(szSql) );
    if( pReq->bQueryAllChars )
    { // 所有的角色
        if(GetDatabaseServerApp()->m_bUseCancelDel)
        { sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_Character] where AccountId = %ld and (IsDel = 0 or (IsDel = 1 and getdate() - DelTime <= 7))",  pReq->dwAccountId ); }
        else
        { sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_Character] where AccountId = %ld and IsDel = 0", pReq->dwAccountId ); }
    }
    else
    { // 只要一个角色
        if(GetDatabaseServerApp()->m_bUseCancelDel)
        { sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_Character] where CharacterId = %ld and (IsDel = 0 or (IsDel = 1 and getdate() - DelTime <= 7))", pReq->dwCharacterId ); }
        else
        { sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_Character] where CharacterId = %ld and IsDel = 0",  pReq->dwCharacterId );}
    }

    CRecordset pRec = RoleQuery( szSql );
    if( !pRec.IsOpen() )
    { return ER_SQLConnectionReset; }

    DBMsgAckCharInfo ack;
    ack.shServerId  = pReq->shServerId;
    ack.dwAccountID = pReq->dwAccountId;
    ack.header.stID = pReq->header.stID;
    ack.ustLifeCode = pReq->ustLifeCode;

    while( !pRec.IsEOF() )
    {
        ack.dwCharacterID = atoi( pRec.Get("CharacterId") );
        ack.stWhichSlot   = atoi( pRec.Get("CharSlot")    );
        ack.bIsDel        = atoi( pRec.Get("IsDel")       );

        BaseSqlMessage* pSaveQuery = m_taskqueue.GetSaveQueryByCharDbId( ack.dwCharacterID );
        if ( pSaveQuery == NULL )
        { // 已经入库
            // baseinfo 将数据库中读出来的字符串解码成二进制值
            static char tempDecodeBufferBaseinfo[1024*100] = {0};
            int nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(pRec.Get("DataInfo")), tempDecodeBufferBaseinfo, sizeof(tempDecodeBufferBaseinfo));

            // baseinfo 解压缩进人物信息当中
            static uint8 uncompressBufffer[1024*256] = {0};            
            uint32 uncompressBufferSize = 1024*256;
            uncompress( uncompressBufffer, &uncompressBufferSize, (uint8*)tempDecodeBufferBaseinfo,  nDecodeBufferActualSize);

            // 读取人数基本数据
            bool bflag = LoadCharData( uncompressBufffer, uncompressBufferSize, &ack.baseinfo);
            if ( !bflag )
            { 
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"LoadCharData Error!");
                return ER_Failed; 
            }
			ack.baseinfo.liveinfo.ChangeName = atoi( pRec.Get("changeName"));
			
            // 名字
            strncpy_s(ack.baseinfo.aptotic.szCharacterName, sizeof(ack.baseinfo.aptotic.szCharacterName), pRec.Get("CharName"), sizeof(ack.baseinfo.aptotic.szCharacterName)-1);

            // otherdata 将数据库中读出来的字符串解码成二进制值
            static int8 tempDecodeBufferOtherData[1024*400] = {0};
            nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(pRec.Get("OtherData")), tempDecodeBufferOtherData, sizeof(tempDecodeBufferOtherData));

            // otherdata 解压缩进人物信息当中
            static uint8 uncompressBuffferOtherData[1024*400] = {0};
            uncompressBufferSize = 1024*400;
            uncompress( uncompressBuffferOtherData, &uncompressBufferSize, (uint8*)tempDecodeBufferOtherData,  nDecodeBufferActualSize );            
            SCharOtherData otherdata;
            bool bResult = LoadOtherData( uncompressBuffferOtherData, uncompressBufferSize, &otherdata );
            if (!bResult)
            { 
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"LoadOtherData Error!");
                return ER_Failed;
            }

            // 地图Id
            ack.nMapId = otherdata.pos.dwMapID;

            // visual
            sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_VisualInfo] where CharacterId = %ld", ack.dwCharacterID );
            CRecordset pRec2 = RoleQuery( szSql );
            if ( !pRec2.IsOpen())
            { 
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, szSql );
                return ER_SQLConnectionReset; 
            }

            if ( pRec2.IsEmpty())
            { return ER_Failed; }

            // visual 将数据库中读出来的字符串解码成二进制值
            static int8 tempDecodeBufferVisual[1024*40] = {0};
            nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(pRec2.Get("DataInfo")), tempDecodeBufferVisual, sizeof(tempDecodeBufferVisual));

            // visual 解压缩进人物信息当中
            static uint8 uncompressBuffferVisual[ 1024 * 40 ] = {0};
            uncompressBufferSize = 1024 * 40;
            uncompress( uncompressBuffferVisual,&uncompressBufferSize,(unsigned char*)tempDecodeBufferVisual, nDecodeBufferActualSize);
            bool bVisual = LoadVisuals( uncompressBuffferVisual, uncompressBufferSize, &ack.visual);

            if (!bVisual)
            { 
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"LoadVisuals Error!");
                return ER_Failed;
            }
        }
        else
        {
            SqlMessageDBMsgSaveCharacter* pSave = (SqlMessageDBMsgSaveCharacter*)pSaveQuery;
            memcpy_s( &ack.baseinfo, sizeof(ack.baseinfo), &pSave->msg.dbInfo.baseinfo, sizeof(ack.baseinfo) );
            memcpy_s( &ack.visual,   sizeof(ack.visual),   &pSave->msg.dbInfo.visual,   sizeof(ack.visual) );
            ack.nMapId   = pSave->msg.dbInfo.otherdata.pos.dwMapID;
        }

        GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ack );
        pRec.MoveNext();
    }

    if( pReq->needEnd == 1 )
    {
        DBMsgEndAckChar end;
        end.shServerId  = pReq->shServerId;
        end.header.stID = pReq->header.stID;
        end.dwAccountID = pReq->dwAccountId;
        GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &end );
    }

    return ER_Success;
}

bool DatabaseServerWorkThread::LoadItems( const uint32 dwCharacterId, SCharItem* pItem, const int nBagSize, int nBagPos)
{
    char szSql[512] = {0};
    memset( szSql, 0, sizeof(szSql));

    switch ( nBagPos )
    {
    case e_CharBag:
    case e_StroageBag:
    case e_MaterialBag:
    case e_TaskBag:
        sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_Item] where (CharacterId = %ld) and WhoIs = %d", dwCharacterId, nBagPos );
        break;
    default:
        return false;
    }

    CRecordset pRec = RoleQuery( szSql );
    if( !pRec.IsOpen() )
    { return false; }

    for( int i=0; i<nBagSize; ++i)
    {
        pItem[i].itembaseinfo.ustItemID = InvalidLogicNumber;
        pItem[i].itembaseinfo.nOnlyInt  = 0;
    }

    int nIndex = 0;

    while( !pRec.IsEOF() )
    {
        nIndex = -1;
        if (pRec.Get("BagIndex") == NULL || (strlen(pRec.Get("BagIndex")) == 0))
        { nIndex = -1; }
        else
        { nIndex = atoi(pRec.Get("BagIndex"));}

        if (nIndex > nBagSize)
        {
            pRec.MoveNext();
            continue;
        }

        SCharItem ItemTemp;
        memset( &ItemTemp, 0, sizeof(SCharItem));
        ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;

        // itemdata 将数据库中读出来的字符串解码成二进制值
        static char tempDecodeBufferBaseinfo[ 1024 * 40 ] = {0};        
        int nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(pRec.Get("ItemData")), tempDecodeBufferBaseinfo, sizeof(tempDecodeBufferBaseinfo));

        // itemdata 解压缩进人物信息当中
        static uint8 uncompressBuffferItemData[ 1024 * 40 ] = {0};
        uint32 uncompressBufferSize = 1024 * 40;
        uncompress( uncompressBuffferItemData, &uncompressBufferSize, (unsigned char*)tempDecodeBufferBaseinfo, nDecodeBufferActualSize );
        ItemTemp.Read( uncompressBuffferItemData, uncompressBufferSize );

        ////如果这个物品堆叠的数量大于99个就清掉
        //if (ItemTemp.itembaseinfo.ustItemCount > 99)
        //{
        //    ItemTemp.itembaseinfo.ustItemID = ErrorUnsignedShortID;
        //}

        if (nIndex == -1)
        {
            for (int nloop = 0; nloop < nBagSize; nloop++)
            {
                if (pItem[nloop].itembaseinfo.ustItemID == InvalidLogicNumber)
                {
                    memcpy(&pItem[nloop],&ItemTemp,sizeof(SCharItem));
                    break;
                }
            }
        }
        else
        {
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

        pRec.MoveNext();
    }
    return true;
}

bool DatabaseServerWorkThread::LoadMount( uint32 dwCharacterId, SMountItem* pMountItem, int nCount )
{
    char szSql[1024] = {0};
    memset( szSql, 0, sizeof(szSql));
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_Mount] where (CharacterId = %ld)", dwCharacterId );

    CRecordset pRec = RoleQuery( szSql );
    if( !pRec.IsOpen() )
    { return false; }

    if ( nCount>ITEM_MOUNT_MAXCOUNT)
    { nCount = ITEM_MOUNT_MAXCOUNT; }

    for( int i=0; i<nCount; ++i) 
    {
        pMountItem[i].baseInfo.id       = InvalidLogicNumber;
        pMountItem[i].baseInfo.guid     = 0;
        pMountItem[i].baseInfo.isActive = 0;
    }

    while( !pRec.IsEOF() )
    {
        SMountItem mountTemp;
        memset( &mountTemp, 0, sizeof(SMountItem));
        mountTemp.baseInfo.id = InvalidLogicNumber;

        // datainfo 将数据库中读出来的字符串解码成二进制值
        static char tempDecodeBuffer[ 1024 * 35 ] = {0};
        int32 nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(pRec.Get("DataInfo")), tempDecodeBuffer, sizeof(tempDecodeBuffer));

        // datainfo 解压缩进坐骑信息当中
        static uint8 uncompressBuffferItemData[ 1024 * 35 ] = {0};
        uint32 uncompressBufferSize = 1024 * 35;
        uncompress( uncompressBuffferItemData, &uncompressBufferSize,(unsigned char*)tempDecodeBuffer, nDecodeBufferActualSize );        
        mountTemp.Read( uncompressBuffferItemData, uncompressBufferSize );

        for (int nloop = 0; nloop < nCount; ++nloop)
        {
            if (pMountItem[nloop].baseInfo.id == InvalidLogicNumber)
            {
                memcpy(&pMountItem[nloop], &mountTemp,sizeof(SMountItem));
                break;
            }
        }

        pRec.MoveNext();
    }

    return true;
}

uint32 DatabaseServerWorkThread::OnQueryCharEnterWorld( BaseSqlMessage* pSqlMessage )
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
        GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ack );
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "开始使用Cache数据 AccountId[%d] CharDbId[%d]", pReq->dwAccountID, pReq->dwCharacterID );
        return ER_Success;
    }

    BaseSqlMessage* pSaveQuery = m_taskqueue.GetSaveQueryByCharDbId( pReq->dwCharacterID );
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
        GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ack );
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "开始使用UnSaveToMssql数据 AccountId[%d] CharDbId[%d]", pReq->dwAccountID, pReq->dwCharacterID );
        return ER_Success;
    }

    char szSql[1024] = {0};
    memset( szSql, 0, sizeof(szSql));
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_Character] where (AccountId = %ld) and (CharSlot = %d) and IsDel = 0 and CharacterID = %d", pReq->dwAccountID, pReq->stSlot, pReq->dwCharacterID);

    CRecordset pRec = RoleQuery( szSql );
    if( !pRec.IsOpen() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, szSql );
        return ER_SQLConnectionReset;
    }

    if( !pRec.IsEOF() )
    {  
        // 清理一下钱
        ack.charinfo.baseinfo.liveinfo.jinDing = 0;
        ack.charinfo.baseinfo.liveinfo.jinPiao = 0;
        ack.charinfo.baseinfo.liveinfo.jiaoZi = 0;

        ack.bRet                     = ER_Success;    
        ack.nGMLevel                 = 0;
        ack.dwCharacterID            = atoi(pRec.Get("CharacterId"));
        ack.nPKValue                 = atoi(pRec.Get("KillValue"));
        ack.stPKProtectFlag          = atoi(pRec.Get("KillFlag"));
        ack.nStayInHellTime          = atoi(pRec.Get("KillerStateTime"));
        std::string strName( pRec.Get("CharName") );
        uint16 shLevel               = atoi(pRec.Get("Lev"));
        uint32 dwMoney               = atoi(pRec.Get("Money"));
        ack.stStorage.dwStorageMoney = atoi(pRec.Get("StorageMoney"));
        int32 jinding                = atoi(pRec.Get("jinding"));
        int32 jinpiao                = atoi(pRec.Get("jinpiao"));

		ack.charinfo.baseinfo.liveinfo.ChangeName = atoi( pRec.Get("changeName"));
        // 查找是否为GM
        ItrGmContainer itr = gmlist.find( strName );
        if (itr != gmlist.end())
        { ack.nGMLevel = itr->second.nLevel; }

        // DataInfo 将数据库中读出来的字符串解码成二进制值
        static char tempDecodeBuffer[ 1024 * 400 ] = {0};
        int nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(pRec.Get("DataInfo")), tempDecodeBuffer, sizeof(tempDecodeBuffer));      

        // DataInfo 解压缩进人物信息当中
        static uint8 uncompressBufffer[ 1024 * 400 ] = {0};
        uint32 uncompressBufferSize = 1024 * 400;
        uncompress( uncompressBufffer, &uncompressBufferSize, (unsigned char*)tempDecodeBuffer, nDecodeBufferActualSize); 
        bool bResult = LoadCharData( uncompressBufffer, uncompressBufferSize, &ack.charinfo.baseinfo);
        if (!bResult)
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "LoadCharData Error!" );
            return ER_Failed;
        }

        // otherdata 将数据库中读出来的字符串解码成二进制值
        nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(pRec.Get("OtherData")), tempDecodeBuffer, sizeof(tempDecodeBuffer));

        // otherdata 解压缩进人物信息当中
        uncompressBufferSize = 1024 * 400;
        uncompress( uncompressBufffer, &uncompressBufferSize, (unsigned char*)tempDecodeBuffer, nDecodeBufferActualSize);
        bResult = LoadOtherData( uncompressBufffer, uncompressBufferSize, &ack.charinfo.otherdata );
        if ( !bResult )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "LoadOtherData Error" );
            return ER_Failed;
        }

        // 角色名字
        strncpy_s(ack.charinfo.baseinfo.aptotic.szCharacterName, strName.c_str(), sizeof(ack.charinfo.baseinfo.aptotic.szCharacterName)-1);

        // extenddata 将数据库中读出来的字符串解码成二进制值
        nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(pRec.Get("ExtendData")), tempDecodeBuffer, sizeof(tempDecodeBuffer));

        // extenddata 解压缩进人物信息当中
        uncompressBufferSize = 1024 * 400;
        uncompress( uncompressBufffer, &uncompressBufferSize, (unsigned char*)tempDecodeBuffer, nDecodeBufferActualSize );
        bResult = LoadExtendData( uncompressBufffer, uncompressBufferSize, &ack.charinfo.extendData );
        if ( !bResult )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "ReChangExtendData Error" );
            return ER_Failed;
        }

        // visual 穿在身上的装备
        sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_VisualInfo] where CharacterId = %ld", ack.dwCharacterID );
        pRec = RoleQuery( szSql );
        if ( !pRec.IsOpen() )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, szSql);
            return ER_SQLConnectionReset;
        }

        // visual 将数据库中读出来的字符串解码成二进制值
        nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(pRec.Get("DataInfo")), tempDecodeBuffer, sizeof(tempDecodeBuffer));

        // visual 解压缩进人物信息当中
        uncompressBufferSize = 1024 * 400;
        uncompress( uncompressBufffer, &uncompressBufferSize,(unsigned char*)tempDecodeBuffer, nDecodeBufferActualSize);
        bResult = LoadVisuals( uncompressBufffer, uncompressBufferSize, &ack.charinfo.visual);
        if ( !bResult )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "LoadVisuals Error" );
            return ER_Failed;
        }

        // 这里设置独立字段的等级/金钱/银票，在这之后不要改写这些数据。
        ack.charinfo.baseinfo.liveinfo.ustLevel = shLevel;
        ack.charinfo.baseinfo.liveinfo.dwMoney  = dwMoney;
        if ( ack.charinfo.baseinfo.liveinfo.jinDing > 0)
        { // 如果这个时候有 [把封测试时候送的金锭转到金票]
            ack.charinfo.baseinfo.liveinfo.jinPiao += ack.charinfo.baseinfo.liveinfo.jinDing;
        }

        ack.charinfo.baseinfo.liveinfo.jinDing = jinding;

		//lyh进入游戏的时候 把数据库中角色的 商场积分给运行时数据

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
        LoadMount( ack.dwCharacterID, ack.charinfo.itemData.miItems, ack.charinfo.baseinfo.liveinfo.ucMountCount );
		theAccountMoneyCache.MakeMoneyData(ack,pReq->dwAccountID);

		ack.charinfo.otherdata.nGuildID = atoi(pRec.Get("guild"));

        GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ack );
    }
    else
    {
        MsgAckResult msg;
        msg.result = ER_EnterWorldDbSqlException;
        GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &msg );
    }

    return ER_Success;
}

void DatabaseServerWorkThread::OnQueryStorage( BaseSqlMessage* pSqlMessage )
{ // 查询仓库数据
    SqlMessageDBMsgReqStorage* pDetailSqlMessage = (SqlMessageDBMsgReqStorage*)pSqlMessage;
    DBMsgReqStorage* pReq = &pDetailSqlMessage->msg;

    DBMsgAckStorage ack;
    ack.header.stID   = pReq->header.stID;
    ack.ustLifeCode   = pReq->ustLifeCode;
    ack.shServerId = pReq->shServerId;
    ack.dwCharacterId = pReq->dwCharacterId;

    //为维护方便使用统一保存接口
    //LoadStorage( ack.dwCharacterId, ack.stStorage.stStorageItems, STORAGE_Grigs_MAX );

    // 仓库里的钱
    LoadItems( ack.dwCharacterId, ack.stStorage.stStorageItems, STORAGE_ITEMGRID_MAX,e_StroageBag );
    GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ack );
}

void DatabaseServerWorkThread::OnQueryDelChar( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgDeleteChar2* pDetailSqlMessage = (SqlMessageDBMsgDeleteChar2*)pSqlMessage;
    DBMsgDeleteChar2* pDelete = &pDetailSqlMessage->msg;

    char szSql[1024] = {0};
    memset( szSql, 0, sizeof(szSql));
    sprintf_s( szSql, sizeof( szSql ) - 1, "update [t_game_Character] set IsDel=1, DelTime=getdate() where (AccountId = %ld) and (CharacterID = %d)", pDelete->dwAccountID, pDelete->dwCharId );

    CRecordset pRec = RoleQuery( szSql );
    if( !pRec.IsOpen() )
    { return; }

    DBMsgAckDeleteChar2 ackDelete;
    ackDelete.shServerId = pDelete->shServerId;
    ackDelete.header.stID = pDelete->header.stID;    
    ackDelete.stWhichSlot = pDelete->stWhichSlot;
    ackDelete.ustLifeCode = pDelete->ustLifeCode;
    ackDelete.bSuccessed = true;
    GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ackDelete );
}

void DatabaseServerWorkThread::OnQueryCancelDelChar( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgCancelDelChar* pDetailSqlMessage = (SqlMessageDBMsgCancelDelChar*)pSqlMessage;
    DBMsgCancelDelChar* pCancel = &pDetailSqlMessage->msg;
    char szSql[1024] = {0};
    memset( szSql, 0, sizeof(szSql));
    sprintf_s( szSql, sizeof( szSql ) - 1, "update [t_game_Character] set IsDel = 0 where (AccountId = %ld) and (CharacterID = %d) and (IsDel = 1) and (getdate()-DelTime <= 7)", pCancel->dwAccountID, pCancel->dwCharId );
    CRecordset pRec = RoleQuery( szSql );
    if( !pRec.IsOpen()  )
    { return; }

    DBMsgAckCancelDelChar ackCancel;
    ackCancel.shServerId = pCancel->shServerId;
    ackCancel.header.stID = pCancel->header.stID;    
    ackCancel.stWhichSlot = pCancel->stWhichSlot;
    ackCancel.ustLifeCode = pCancel->ustLifeCode;
    ackCancel.bSuccessed = true;
    GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ackCancel );
}

uint32 DatabaseServerWorkThread::OnQuerySaveChar( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgSaveCharacter* pDetailSqlMessage = (SqlMessageDBMsgSaveCharacter*)pSqlMessage;
    DBMsgSaveCharacter* pSave = &pDetailSqlMessage->msg;

    uint32 Performance_SaveRoleBeginTime = 0;
    if (G_PrinfInfo == PRINTFSAVEROLETIME)
    { Performance_SaveRoleBeginTime = HQ_TimeGetTime();}

    uint32 dwTime = (uint32)((double)pSave->dwSaveTime / 1000.00 / 60.00);

    char szSql[ 1024 * 40 + 1 ] = {0};
    memset( szSql, 0, sizeof(szSql) );

    // 需要存放压缩过后的字符
    static uint8 szSaveData  [1024 * 40] = {0};
    static uint8 szOtherData [1024 * 40] = {0};
    static uint8 szVisualData[1024 * 40] = {0};
    static uint8 szExtendData[1024 * 40] = {0};
    static uint8 compressBuffer[1024 * 40] = {0};
    uint32 compressBufferSize = 0;

    // 处理BaseInfo
    compressBufferSize = sizeof(compressBuffer);
    uint32 nActualSize = 0;
    if ( !WriteCharData(&pSave->dbInfo.baseinfo, nActualSize ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] baseinfo 数据出错", pSave->dwCharacterID );
        return ER_Failed;
    }

    compress( compressBuffer, (uLongf*)&compressBufferSize, _charBaseInfoBuffer, nActualSize ); // 压缩数据
    EnCodeToString( compressBuffer, (char*)szSaveData, compressBufferSize, sizeof(szSaveData)); // 转为可视字符串

    // 处理VisualData
    if ( !WriteVisualData(&pSave->dbInfo.visual, nActualSize ))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] visual 数据出错", pSave->dwCharacterID );
        return ER_Failed;
    }
    compressBufferSize = sizeof(compressBuffer); //  因为调用compress会改变size的值，所以这里需要重新赋值一次
    compress(compressBuffer, (uLongf*)&compressBufferSize, _visualDataBuffer, nActualSize );       // 压缩数据
    EnCodeToString(compressBuffer, (char*)szVisualData, compressBufferSize, sizeof(szVisualData)); // 转为可视字符串

    // 处理OtherData
    compressBufferSize = sizeof(compressBuffer); // 因为调用compress会改变size的值，所以这里需要重新赋值一次
    if (!WriteOtherData( &pSave->dbInfo.otherdata, nActualSize ))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] otherData 数据出错", pSave->dwCharacterID );
        return ER_Failed;
    }
    compress(compressBuffer, (uLongf*)&compressBufferSize, _otherDataBuffer, nActualSize );    // 压缩数据    
    EnCodeToString(compressBuffer, (char*)szOtherData, compressBufferSize, sizeof(szOtherData)); // 转为可视字符串

    // 处理ExtendData
    compressBufferSize = sizeof(compressBuffer); // 因为调用compress会改变size的值，所以这里需要重新赋值一次
    if (!WriteExtendData( &pSave->dbInfo.extendData, nActualSize ))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "写角色[%d] extendData 数据出错", pSave->dwCharacterID );
        return ER_Failed;
    }    
    compress(compressBuffer, (uLongf*)&compressBufferSize, _extendDataBuffer, nActualSize);        // 压缩数据    
    EnCodeToString(compressBuffer, (char*)szExtendData, compressBufferSize, sizeof(szExtendData)); // 转为可视字符串

    // 使用存储过程    
    { // 实际用这个 实际会有17*多ms的处理时间
        //使用存储过程批量存储一个玩家的数据
        std::string strItemGUID;
        std::string strItemID;
        std::string strItemName;
        std::string strItemData;
        std::string strWhoIs;
        std::string strBag;
        std::string strX;
        std::string strY;
        std::string strBagIndex;

        std::string strMountID;
        std::string strMountGUID;
        std::string strMountData;
        std::string strCounter;

        // 普通物品背包
        char szTmp[65] = {0};
        memset( szTmp, 0, sizeof(szTmp));
        sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", e_CharBag);
        strBag = szTmp;
        SCharItem* pItem = pSave->dbInfo.itemData.stPackItems;
        for (int i=0; i<ITEM_BAGMAX; ++i, ++pItem)
        {
            if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
            { continue; }

            static uint8 compressBuffer[1024 * 10] = {0};
            static uint8 encodeBuffer  [1024 * 10] = {0};

            int compressBufferSize = 0;

            // 处理物品数据
            compressBufferSize = sizeof(compressBuffer);
            uint32 nActualSize = 0;
            bool bl = WriteItemData( pItem, nActualSize );
            if (!bl)
            { continue; }

            compress(compressBuffer,(uLongf*)&compressBufferSize, _itemDataBuffer, nActualSize ); // 压缩数据
            EnCodeToString(compressBuffer, (char*)encodeBuffer, compressBufferSize, sizeof(encodeBuffer));

            strItemGUID += BigInt2String(pItem->itembaseinfo.nOnlyInt);
            strItemGUID += "|";

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", pItem->itembaseinfo.ustItemID);            
            strItemID += szTmp;
            strItemID += "|";

            strItemName += "no name";
            strItemName += "|";

            strItemData += (char*)encodeBuffer;
            strItemData += "|";

            strWhoIs += strBag;
            strWhoIs += "|";

            //X，Y字段直接写死-1 暂时没有用处
            strX += "-1|";
            strY += "-1|";

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", i);
            strBagIndex += szTmp;
            strBagIndex += "|";
        }

        // 材料背包
        memset( szTmp, 0, sizeof(szTmp));
        sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", e_MaterialBag);
        strBag = szTmp;
        pItem = pSave->dbInfo.itemData.ciMaterialItems;
        for (int i=0; i<ITEM_BAGMATERIAL_MAX; ++i, ++pItem)
        {
            if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
            { continue; }

            static uint8 compressBuffer[1024 * 10] = {0};
            static uint8 encodeBuffer  [1024 * 10] = {0};
            uint32 nActualSize = 0;     
            bool bl = WriteItemData( pItem, nActualSize );
            if (!bl)
            { continue; }

            int compressBufferSize = sizeof(compressBuffer);
            compress( compressBuffer,(uLongf*)&compressBufferSize, _itemDataBuffer, nActualSize ); // 压缩数据
            EnCodeToString( compressBuffer, (char*)encodeBuffer, compressBufferSize, sizeof(encodeBuffer));

            strItemGUID += BigInt2String(pItem->itembaseinfo.nOnlyInt);
            strItemGUID += "|";

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", pItem->itembaseinfo.ustItemID);            
            strItemID += szTmp;
            strItemID += "|";

            strItemName += "no name";
            strItemName += "|";

            strItemData += (char*)encodeBuffer;
            strItemData += "|";

            strWhoIs += strBag;
            strWhoIs += "|";

            //X，Y字段直接写死-1 暂时没有用处
            strX += "-1|";
            strY += "-1|";

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", i);
            strBagIndex += szTmp;
            strBagIndex += "|";
        }

        // 任务背包
        memset( szTmp, 0, sizeof(szTmp));
        sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", e_TaskBag);
        strBag = szTmp;
        pItem = pSave->dbInfo.itemData.ciTaskItems;
        for (int i=0; i<ITEM_BAGTASK_MAX; ++i, ++pItem)
        {
            if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
            { continue; }

            static uint8 compressBuffer[1024 * 10] = {0};
            static uint8 encodeBuffer  [1024 * 10] = {0};

            uint32 nActualSize = 0;
            bool bl = WriteItemData( pItem, nActualSize );
            if (!bl)
            { continue; }

            // 压缩数据
            int compressBufferSize = sizeof(compressBuffer);
            compress( compressBuffer,(uLongf*)&compressBufferSize, _itemDataBuffer, nActualSize );
            EnCodeToString( compressBuffer, (char*)encodeBuffer, compressBufferSize, sizeof(encodeBuffer));

            strItemGUID += BigInt2String(pItem->itembaseinfo.nOnlyInt);
            strItemGUID += "|";

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", pItem->itembaseinfo.ustItemID);            
            strItemID += szTmp;
            strItemID += "|";

            strItemName += "no name";
            strItemName += "|";

            strItemData += (char*)encodeBuffer;
            strItemData += "|";

            strWhoIs += strBag;
            strWhoIs += "|";

            //X，Y字段直接写死-1 暂时没有用处
            strX += "-1|";
            strY += "-1|";

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", i);
            strBagIndex += szTmp;
            strBagIndex += "|";
        }

        // 仓库
        sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", e_StroageBag);
        strBag = szTmp;
        pItem = pSave->storageInfo.stStorageItems;

        for (int i=0; i<STORAGE_ITEMGRID_MAX; ++i, ++pItem)
        {
            if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
            { continue; }

            static uint8 compressBuffer[1024 * 10] = {0};
            static uint8 encodeBuffer  [1024 * 10] = {0};

            uint32 nActualSize = 0;
            bool bl = WriteItemData(pItem, nActualSize);

            if (!bl)
            { continue; }

            // 压缩数据
            int compressBufferSize = sizeof(compressBuffer);
            compress(compressBuffer,(uLongf*)&compressBufferSize, _itemDataBuffer, nActualSize );
            EnCodeToString(compressBuffer, (char*)encodeBuffer, compressBufferSize, sizeof(encodeBuffer));

            strItemGUID += BigInt2String(pItem->itembaseinfo.nOnlyInt);
            strItemGUID += "|";

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", pItem->itembaseinfo.ustItemID);
            strItemID += szTmp;
            strItemID += "|";

            strItemName += "no name";
            strItemName += "|";

            strItemData += (char*)encodeBuffer;
            strItemData += "|";

            strWhoIs += strBag;
            strWhoIs += "|";

            strX += "-1|";
            strY += "-1|";

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", i);
            strBagIndex += szTmp;
            strBagIndex += "|";
        }

        // 装备背包
        sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", e_VisualBag);
        strBag = szTmp;
        pItem = pSave->dbInfo.visual.GetVisualArray();
        for (int i=0; i<EEquipPartType_MaxEquitPart; i++, pItem++)
        {
            if( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->itembaseinfo.nOnlyInt <= 0)
            { continue; }

            static uint8 compressBuffer[1024 * 10] = {0};
            static uint8 encodeBuffer  [1024 * 10] = {0};

            // 处理物品数据
            uint32 nActualSize = 0;
            bool bl = WriteItemData(pItem , nActualSize);
            if (!bl)
            { continue; }

            // 压缩数据
            int compressBufferSize = sizeof(compressBuffer);
            compress(compressBuffer,(uLongf*)&compressBufferSize, _itemDataBuffer, nActualSize );
            EnCodeToString(compressBuffer, (char*)encodeBuffer, compressBufferSize, sizeof(encodeBuffer));

            strItemGUID += BigInt2String(pItem->itembaseinfo.nOnlyInt);
            strItemGUID += "|";

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", pItem->itembaseinfo.ustItemID);
            strItemID += szTmp;
            strItemID += "|";

            strItemName += "no name";
            strItemName += "|";

            strItemData += (char*)encodeBuffer;
            strItemData += "|";

            strWhoIs += strBag;
            strWhoIs += "|";

            //X，Y字段直接写死-1 暂时没有用处
            strX += "-1|";
            strY += "-1|";

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", i);
            strBagIndex += szTmp;
            strBagIndex += "|";
        }

        // 坐骑
        SMountItem* pMountItem = pSave->dbInfo.itemData.miItems;
        for ( int i=0; i<ITEM_MOUNT_MAXCOUNT; ++i, ++pMountItem )
        {
            if( pMountItem->baseInfo.id == InvalidLogicNumber || pMountItem->baseInfo.guid <= 0)
            { continue; }

            static uint8 compressBuffer[1024 * 10] = {0};
            static uint8 encodeBuffer  [1024 * 10] = {0};

            uint32 nActualSize = 0;
            bool bResult = WriteMountData( pMountItem, nActualSize );
            if ( !bResult )
            { 
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "Save Mount WriteMountData Fail[%I64u]",pMountItem->baseInfo.guid );
                continue;
            }

            int compressBufferSize = sizeof(compressBuffer);
            compress(compressBuffer,(uLongf*)&compressBufferSize, _mountDataBuffer, nActualSize ); // 压缩数据
            EnCodeToString(compressBuffer, (char*)encodeBuffer, compressBufferSize, sizeof(encodeBuffer));

            sprintf_s( szTmp, sizeof( szTmp ) - 1, "%d", pMountItem->baseInfo.id );
            strMountID += szTmp;
            strMountID += "|";

            strMountGUID += BigInt2String(pMountItem->baseInfo.guid);
            strMountGUID += "|";

            strMountData += (char*)encodeBuffer;
            strMountData += "|";
        }

        //////////////////////////////////////////////////////////////////////////////////
        ////清除所有带有分隔符“|”中的尾部符号
        //if (!strWhoIs.IsEmpty())
        //{
        //    strWhoIs.SetAt(strWhoIs.GetLength()-1, '\0');
        //    strItemGUID.SetAt(strItemGUID.GetLength()-1, '\0');
        //    strItemID.SetAt(strItemID.GetLength()-1, '\0');
        //    strX.SetAt(strX.GetLength()-1, '\0');
        //    strY.SetAt(strY.GetLength()-1, '\0');
        //    strItemName.SetAt(strItemName.GetLength()-1, '\0');
        //    strItemData.SetAt(strItemData.GetLength()-1, '\0');
        //}        

        sprintf_s( szSql, sizeof( szSql ) - 1, "UpdateRoleInfo %d, "     // ID
            "%d, "                                  // 仓库是否打开
            "'%s', "                                // WhoIs
            "'%s', "                                // ItemGUID
            "'%s', "                                // ItemID
            "'%s', "                                // X
            "'%s', "                                // Y
            "'%s', "                                // BagIndex
            "'%s', "                                // ItemName
            "'%s', "                                // ItemData
            "'%s', "                                // VisualDataInfo
            "'%s', "                                // CharacterDataInfo
            "%d, "                                  // OnlineTime
            "%d, "                                  // Money
            "%d, "                                  // StorageMoney
            "%d, "                                  // Level
            "'%s', "                                // OtherData
            "%I64u, "                               // Exp
            "%d, "                                  // KillValue
            "%d, "                                  // KillFlag
            "%d,  "                                 // jinding
            "%d,  "                                 // jinpiao
            "'%s', "                                // ExtendData
            "'%s', "                                // MountID
            "'%s', "                                // MountGUID
            "'%s' "                                 // MountData

            ,pSave->dwCharacterID,                        // ID
            1,                                            // 仓库是否打开
            strWhoIs.c_str(),                             // WhoIs
            strItemGUID.c_str(),                          // ItemGUID
            strItemID.c_str(),                            // ItemID
            strX.c_str(),                                 // X
            strY.c_str(),                                 // Y
            strBagIndex.c_str(),                          // BagIndex
            strItemName.c_str(),                          // ItemName
            strItemData.c_str(),                          // ItemData
            szVisualData,                                 // VisualDataInfo
            szSaveData,                                   // CharacterDataInfo
            dwTime,                                       // OnlineTime
            pSave->dbInfo.baseinfo.liveinfo.dwMoney,      // Money
            pSave->storageInfo.dwStorageMoney,            // StorageMoney
            pSave->dbInfo.baseinfo.liveinfo.ustLevel,     // Level
            szOtherData,                                  // OtherData
            pSave->dbInfo.baseinfo.liveinfo.dwExp,        // Exp
            pSave->nPKValue,                              // KillValue
            pSave->stPKProtectFlag,                       // KillFlag
            pSave->dbInfo.baseinfo.liveinfo.jinDing,      // jinDing
            pSave->dbInfo.baseinfo.liveinfo.jinPiao,      // jinDing
            szExtendData,                                 // ExtendData
            strMountID.c_str(),                           // MountID
            strMountGUID.c_str(),                         // MountGUID
            strMountData.c_str()                          // MountData
            );

        uint32 Performance_SaveRoleBeginSQLTime = HQ_TimeGetTime();
        CRecordset pRec = RoleQuery( szSql );
        if (G_PrinfInfo == PRINTFSAVEROLETIME)
        { LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"SQL UpdateRoleInfo Once Time = %d ms",HQ_TimeGetTime() - Performance_SaveRoleBeginSQLTime); }

        if (pRec.IsOpen())
        {
            //const char* pContent = pRec.Get("Code");
            //if ( pContent != NULL && strlen(pContent ) != 0)
            //{ LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_INFO,"UpdateRoleInfo Code(%s)", pContent); }

            if ( pSave->shServerId != DiskServerId )
            { // 需要回馈消息的时候
                DBAckOperSucc acksucc;
                acksucc.dwMsgType     = DBMSG_SAVECHARACTER;
                acksucc.dwMsgID       = pSave->subMarker;
                acksucc.dwCharacterID = pSave->dwCharacterID;
                GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &acksucc);
            }
            //theFileMappingCharSaveManager.RemoveDataFile( pSave->dwCharacterID, pDetailSqlMessage->time );
        }
        else
        { 
            LOG_MESSAGE(SQLOBJECT,LOG_PRIORITY_ERROR,"UpdateRoleInfo(%ld) 失败", pSave->dwCharacterID);
            return ER_SQLConnectionReset;
        }
    }

    SaveGmInfo();

    if (G_PrinfInfo == PRINTFSAVEROLETIME)
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Save Role Once Time = %d ms",HQ_TimeGetTime() - Performance_SaveRoleBeginTime);
        G_PrinfInfo = NOPRINT;
    }

    return ER_Success;
}

//检测创建时 玩家的名字是否重复
void DatabaseServerWorkThread::OnQueryCreateCheckName( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgReqCreateCheckName* pDetailSqlMessage = (SqlMessageDBMsgReqCreateCheckName*)pSqlMessage;
    DBMsgReqCreateCheckName* pCreateCheckName = &pDetailSqlMessage->msg;

    DBMsgAckCreateCheckName ack;
    ack.header.stID = pCreateCheckName->header.stID;

    //检测几个由数据库不方便检测的字符
    if ( !CheckCreateName( pCreateCheckName->szName ) )
    {
        ack.bResult = false;
    }
    else
    {
        char szSql[1024] = {0};
        memset( szSql, 0, sizeof(szSql));
        sprintf_s( szSql, sizeof( szSql ) - 1, "CheckUndueWord '%s'", pCreateCheckName->szName );
        CRecordset pRec = RoleQuery( szSql );
        if( !pRec.IsOpen() )
            return;

        if (pRec.IsEmpty())
        {
            //这里发错误消息
            ack.bResult = false;
        }
        else
        {    
            if (stricmp(pRec.Get("Code"), "1") == 0)
            {
                //这里发成功消息
                ack.bResult = true;
            }
            else
            {
                ack.bResult = false;
            }
        }
    }

    GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ack );
}
void DatabaseServerWorkThread::OnQueryCreateChar( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgCreateHeroChar* pDetailSqlMessage = (SqlMessageDBMsgCreateHeroChar* )pSqlMessage;
    DBMsgCreateHeroChar* pCreate = &pDetailSqlMessage->msg;
    if ( pCreate == NULL )
    { return; }

    DBMsgAckCreateCheckName ackcheck;

    static char szSql[ 1024 * 60 ] = {0};
    memset( szSql, 0, sizeof(szSql));

    CRecordset pRec;
    //检查是否含有单引号或是减号
    if ( !CheckCreateName(pCreate->charinfo.baseinfo.aptotic.szCharacterName) )
    {
        //这里发错误消息
        ackcheck.bResult = false;
    }
    else
    {
        sprintf_s( szSql, sizeof( szSql ) - 1, "CheckUndueWord '%s'", pCreate->charinfo.baseinfo.aptotic.szCharacterName );
        pRec = RoleQuery( szSql );
        if( !pRec.IsOpen())
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, szSql);
            return;
        }
        ackcheck.header.stID = pCreate->header.stID;
        if (pRec.IsEmpty())
        {
            //这里发错误消息
            ackcheck.bResult = false;
        }
        else
        {    
            if (_stricmp(pRec.Get("Code"), "1") == 0)
            {
                //这里发成功消息
                ackcheck.bResult = true;
            }
            else
            {
                ackcheck.bResult = false;
            }
        }
    }

    if (!ackcheck.bResult)
    {
        GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ackcheck);
        return;
    }

    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_Character] where CharName = '%s'",  pCreate->charinfo.baseinfo.aptotic.szCharacterName );

    pRec = RoleQuery( szSql );
    if( !pRec.IsOpen() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,szSql);
        return;
    }

    DBMsgCreateCharAck ack;
    ack.subMarker   = pCreate->subMarker;
    ack.accountId   = pCreate->accoundId;
    ack.shServerId  = pCreate->shServerId;
    ack.header.stID = pCreate->header.stID;
    ack.stWhichSlot = pCreate->stWhichSlot;
    ack.ustLifeCode = pCreate->ustLifeCode;
    strncpy_s( ack.charName, sizeof(ack.charName), pCreate->charinfo.baseinfo.aptotic.szCharacterName, sizeof(ack.charName)-1);

    // 检测该位置是否已经存在人物
    if (!pRec.IsEmpty())
    { ack.result = ER_CharNameHaveExist; }
    else
    {
        sprintf_s( szSql, sizeof( szSql ) - 1, "select * from [t_game_Character] where AccountId = %d and IsDel = 0 and CharSlot = %d", pCreate->accoundId, pCreate->stWhichSlot);
        pRec = RoleQuery( szSql );

        if (!pRec.IsOpen() || !pRec.IsEmpty())
        {
            ackcheck.bResult = false;
            GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ackcheck);
            return;
        }

        const int BUFF_SIZE = 1024*40;

        // 需要存放压缩过后的字符
        static uint8 szSaveData[BUFF_SIZE]   = {0};
        static uint8 szOtherData[BUFF_SIZE]  = {0};
        static uint8 szExtendData[BUFF_SIZE] = {0};
        static uint8 szBuff[BUFF_SIZE]       = {0};
        static uint8 szVisualInfo[BUFF_SIZE] = {0};
        int    compressBufferSize = 0; // 实际压缩大小
        uint32 nActualSize        = 0; // 实际buffer大小

        // 处理BaseInfo
        if  ( !WriteCharData(&pCreate->charinfo.baseinfo, nActualSize) )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"WriteCharData Error!");
            return;
        }
        compressBufferSize = sizeof(unsigned char)*BUFF_SIZE; 
        compress(szBuff, (uLongf*)&compressBufferSize, _charBaseInfoBuffer, nActualSize ); // 压缩数据
        EnCodeToString(szBuff, (char*)szSaveData, compressBufferSize, sizeof(szSaveData)); // 转为可视字符串


        // 处理VisualData
        if( !WriteVisualData(&pCreate->charinfo.visual, nActualSize))
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"ChangeCharVisualData Error!");
            return;
        }
        compressBufferSize = sizeof(szBuff); // 因为调用compress会改变size的值，所以这里需要重新赋值一次        
        compress(szBuff, (uLongf*)&compressBufferSize, _visualDataBuffer, nActualSize);        // 压缩数据
        EnCodeToString(szBuff, (char*)szVisualInfo, compressBufferSize, sizeof(szVisualInfo)); // 转为可视字符串

        // 处理OtherData
        compressBufferSize = sizeof(szBuff);
        if ( !WriteOtherData(&pCreate->charinfo.otherdata, nActualSize))
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"WriteOtherData Error!");
            return;
        }
        compress(szBuff, (uLongf*)&compressBufferSize, _otherDataBuffer, nActualSize);       // 压缩数据
        EnCodeToString(szBuff, (char*)szOtherData, compressBufferSize, sizeof(szOtherData)); // 转为可视字符串

        //处理ExtendData
        compressBufferSize = sizeof(szBuff); // 因为调用compress会改变size的值，所以这里需要重新赋值一次
        if (!WriteExtendData(&pCreate->charinfo.extendData , nActualSize ))
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"WriteExtendData Error!");
            return;
        }
        compress(szBuff, (uLongf*)&compressBufferSize, _extendDataBuffer, nActualSize);        // 压缩数据
        EnCodeToString(szBuff, (char*)szExtendData, compressBufferSize, sizeof(szExtendData)); // 转为可视字符串

        sprintf_s( szSql, sizeof( szSql ) - 1, "insert into t_game_Character (AccountId, CharName, Lev, Money, StorageMoney,"
            "DataInfo, OtherData, CharSlot, IsDel, KillValue, KillFlag, KillerStateTime, jinding, jinpiao, ExtendData,profession,changeName,guild)"
            "values ( %d, N'%s', %d, %d, %d,'%s','%s', %d, %d, %d, %d, %d, %d, %d, '%s',%d,%d,%d)",
            pCreate->accoundId,
            pCreate->charinfo.baseinfo.aptotic.szCharacterName,
            pCreate->charinfo.baseinfo.liveinfo.ustLevel,
            pCreate->charinfo.baseinfo.liveinfo.dwMoney,
            0,
            szSaveData, szOtherData,
            pCreate->stWhichSlot,
            0,
            0,
            PKMode_Normal,
            0,
            0,
            0,
            szExtendData,
			pCreate->charinfo.baseinfo.aptotic.usProfession,
			pCreate->charinfo.baseinfo.liveinfo.ChangeName,
			pCreate->charinfo.otherdata.nGuildID);

        CRecordset pRec = RoleQuery( szSql );
        if( !pRec.IsOpen() )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"Insert DB Error,Maybe Database Nohave FreeDisk or Database Role_log File Is Max");
            return;
        }
        sprintf_s( szSql, sizeof( szSql ) - 1, "select CharacterId from [t_game_Character] where AccountId = %ld and CharName = N'%s'", pCreate->accoundId, pCreate->charinfo.baseinfo.aptotic.szCharacterName);
        CRecordset pRec2 = RoleQuery(szSql);
        if (!pRec2.IsOpen())
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, szSql);
            return;
        }
        ack.dwCharacterId = atoi(pRec2.Get("CharacterId"));

        sprintf_s( szSql, sizeof( szSql ) - 1, "insert into t_game_VisualInfo (CharacterID, DataInfo) values (%d, '%s')",ack.dwCharacterId, szVisualInfo);
        CRecordset pRec3 = RoleQuery( szSql );
        if (!pRec3.IsOpen())
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, szSql);
            return;
        }
        ack.result = ER_Success;
    }

    GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &ack );
}

void DatabaseServerWorkThread::OnQueryLogout( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgOffline2* pDetailSqlMessage = (SqlMessageDBMsgOffline2*)pSqlMessage;
    DBMsgOffline2* pOffline = &pDetailSqlMessage->msg;
    if ( pOffline == NULL )
    { return; }
}

void DatabaseServerWorkThread::OnQueryLogin( BaseSqlMessage* pSqlMessage )
{
    //DBMsgLogin2* pLogin = (DBMsgLogin2*)pQuery->m_pBuffer;

    //char szSql[1024] = {0};
    //memset( szSql, 0, sizeof(szSql));

    ////此段代码存在一个很严重的SQL注入漏洞，因此废弃

    //sprintf_s( szSql, "SELECT AccountId FROM [t_game_Account] Where UserName = '%s' AND Password = '%s'", 
    //    pLogin->szUserName, pLogin->szPassword );

    ////strSql.Format(
    ////    "p_game_AccountLogin '%s', '%s', 0, '%s', 1, 0, 0, 0",
    ////    pLogin->szUserName, CMD5Checksum::GetMD5((unsigned char*)pLogin->szPassword, strlen(pLogin->szPassword)).c_str(), pLogin->szIP );

    //CRecordset pRec = AccQuery( szSql );

    //if( !pRec.IsOpen() )
    //    return;

    //DBMsgAckLogin2 ackLogin;
    //ackLogin.shServerId = pLogin->shServerId;
    //
    //ackLogin.dwGWorldServerID = pLogin->dwGWorldServerID;
    //ackLogin.dwLoginServerID = pLogin->dwLoginServerID;
    //ackLogin.header.stID = pLogin->header.stID;
    //ackLogin.ustLifeCode = pLogin->ustLifeCode;
    //ackLogin.IsForceLogin = pLogin->IsForceLogin;
    //HelperFunc::SafeNCpy( ackLogin.szUserName, pLogin->szUserName, dr_MaxUserName );
    //ackLogin.stRet = MsgAckLogin::ret_succ;

    ////当发现用户数据为空或是密码错误时，统一返回密码错误

    //if (!pRec.IsEmpty()/* && strcmp(pRec.Get("Code"), "-1") == 0*/)
    //{
    //    short sflag = 0;
    //    int nAccountId = atoi(pRec.Get("AccountId"));
    //    //if (pRec.Get("flag"))
    //    //{
    //    //    sflag = atoi(pRec.Get("flag"));
    //    //}    
    //    //int nOnlineFlag = pRecordset->GetCollect("OnlineFlag").lVal;
    //    //if( nOnlineFlag )
    //    //{
    //    //    ackLogin.stRet = MsgAckLogin::ret_alreadyaloginthisaccount;
    //    //}
    //    AccountManager::SAccount stAccount;
    //    stAccount.nAccountId = nAccountId;
    //    stAccount.nServerId = pLogin->shServerId;
    //    if( GetAccountManager()->AddNewAccount( &stAccount ) == false )
    //    {
    //        ackLogin.stRet = MsgAckLogin::ret_alreadyaloginthisaccount;
    //        GetAccountManager()->RemoveAccount(nAccountId);
    //    }
    //    ackLogin.accoundId = nAccountId;
    //    ackLogin.stflag = sflag;
    //    
    //}
    //else
    //{
    //    ackLogin.stRet = MsgAckLogin::error_invaliduserorpass;
    //}

    //GetDatabaseInterface()->PushResult( pQuery->nClientId, &ackLogin );
}

const char* DatabaseServerWorkThread::GUID2String( GUID *pguid )
{
    static char szGuid[60] = { 0 };
    memset( szGuid, 0, sizeof( szGuid ) );
    unsigned char *pszGuid;
    if (RPC_S_OK == UuidToString( pguid, &pszGuid ))
    {
        strncpy_s(szGuid, sizeof( szGuid ), (char *)pszGuid, sizeof( szGuid ) - 1 );
        RpcStringFree( &pszGuid );
        return szGuid;
    }
    // ToLog(false);
    return NULL;
}

const GUID DatabaseServerWorkThread::String2GUID( const char* szGUID)
{
    //如果传过来的szGUID没有被"{}"包含，则自动为它加上
    static GUID guid;
    WCHAR wszGUID[40];
    if (szGUID[0] != '{')
    {
        std::string strGUID;
        strGUID = "{";
        strGUID += szGUID;
        strGUID += "}";
        MultiByteToWideChar( CP_ACP, 0, strGUID.c_str(),
            strGUID.length()+1, wszGUID, sizeof(wszGUID)/sizeof(wszGUID[0]) );
    }
    else
    {
        MultiByteToWideChar( CP_ACP, 0, szGUID,
            strlen(szGUID)+1, wszGUID, sizeof(wszGUID)/sizeof(wszGUID[0]) );
    }
    CLSIDFromString( (LPOLESTR)wszGUID, &guid );
    //    UuidFromString( (unsigned char*)szguid, &guid );
    return guid;
}

bool DatabaseServerWorkThread::WriteCharData( SCharBaseInfo* pInfo, uint32& nActualSize  )
{
    CDataChunkWriter w( _charBaseInfoBuffer, CD_CharBaseInfoBufferSize );

    w.StartChunk(DC_TAG('apto'));
    {
        w.StartChunk(DC_TAG('ap05'));
        {
            w.StartChunk(DC_TAG('cn01'));
            w.WriteString(pInfo->aptotic.szCharacterName);
            w.EndChunk(DC_TAG('cn01'));

            w.StartChunk(DC_TAG('sx01'));
            w.WriteChar(pInfo->aptotic.ucSex);
            w.EndChunk(DC_TAG('sx01'));

            w.StartChunk(DC_TAG('pf01'));
            w.WriteShort(pInfo->aptotic.usProfession);
            w.EndChunk(DC_TAG('pf01'));

            w.StartChunk(DC_TAG('hc01'));
            w.WriteChar(pInfo->aptotic.ucHeadPic);
            w.EndChunk(DC_TAG('hc01'));

            w.StartChunk(DC_TAG('ct01'));
            w.WriteChar(pInfo->aptotic.ucCountry);
            w.EndChunk(DC_TAG('ct01'));

            w.StartChunk(DC_TAG('yn01'));
            w.WriteString(pInfo->aptotic.szYearName);
            w.EndChunk(DC_TAG('yn01'));

            w.StartChunk(DC_TAG('yr01'));
            w.WriteByte(pInfo->aptotic.byYear);
            w.EndChunk(DC_TAG('yr01'));

            w.StartChunk(DC_TAG('mt01'));
            w.WriteByte(pInfo->aptotic.byMonth);
            w.EndChunk(DC_TAG('mt01'));

            w.StartChunk(DC_TAG('dy01'));
            w.WriteByte(pInfo->aptotic.byDay);
            w.EndChunk(DC_TAG('dy01'));
        }
        w.EndChunk(DC_TAG('ap05'));
    }
    w.EndChunk(DC_TAG('apto'));

    w.StartChunk(DC_TAG('live'));
    {
        w.OpenChunk('lv06');
        {
            w.WriteWordChunk ('levl', pInfo->liveinfo.ustLevel         );
            w.WriteDwordChunk('mony', pInfo->liveinfo.dwMoney          );
            w.WriteDwordChunk('repu', pInfo->liveinfo.reputation       );
            w.WriteDwordChunk('expt', pInfo->liveinfo.exploit          );
            w.WriteDwordChunk('honr', pInfo->liveinfo.honour           );
            w.WriteDwordChunk('bls1', pInfo->liveinfo.battleScore      );
            w.WriteDwordChunk('hpfg', pInfo->liveinfo.dwHelpFlag       );
            w.WriteByteChunk ('stmp', pInfo->liveinfo.nStorageItemGrid );
            w.WriteDwordChunk('hsct', pInfo->liveinfo.nHighShoutCount  );
            w.WriteIntChunk  ('hp01', pInfo->liveinfo.nHp              );
            w.WriteIntChunk  ('mp01', pInfo->liveinfo.nMp              );
            w.WriteInt64Chunk('exp0', pInfo->liveinfo.dwExp            );
            w.WriteInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed     );
            w.WriteDwordChunk('slep', pInfo->liveinfo.dwSkillExp       );
            w.WriteDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed);
            w.WriteWordChunk ('seid', pInfo->liveinfo.ustSkillExpForSkillID);
            w.WriteCharChunk ('nbgs', pInfo->liveinfo.ucNormalBagSize  );
            w.WriteCharChunk ('mbgs', pInfo->liveinfo.ucMaterialBagSize);
            w.WriteCharChunk ('moco', pInfo->liveinfo.ucMountCount     );
            w.WriteWordChunk ('ene1', pInfo->liveinfo.activity           );
            w.WriteWordChunk ('enm1', pInfo->liveinfo.activityMax        );
            w.WriteWordChunk ('vig1', pInfo->liveinfo.vigor            );
            w.WriteWordChunk ('vim1', pInfo->liveinfo.vigorMax         );
            w.WriteDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime      );
            w.WriteDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo );
            w.WriteShortChunk('ttle', pInfo->liveinfo.nCurrentTitleID  );  //当前称号

            //称号列表
            w.StartChunk(DC_TAG('tt02'));
            w.Write( pInfo->liveinfo.xTitleData, sizeof(TitleData) * MAX_TITLE_COUNT, 1 );
            w.EndChunk(DC_TAG('tt02'));

            w.StartChunk(DC_TAG('are1'));
            w.Write( pInfo->liveinfo.xArea, sizeof( SAreaRepulation ) * MAX_AREAREPULATION_COUNT, 1 );
            w.EndChunk(DC_TAG('are1'));

            w.StartChunk(DC_TAG('msd2'));
            w.Write( &pInfo->liveinfo.xMasterData, sizeof( MasterData ) , 1 );
            w.EndChunk(DC_TAG('msd2'));

			w.StartChunk(DC_TAG('cold'));
			w.Write( pInfo->liveinfo.xItemColdDown, sizeof( SColdDown ) * MAX_SAVERESTORE_COUNT , 1 );
			w.EndChunk(DC_TAG('cold'));
        }
        w.CloseChunk('lv06');
    }
    w.EndChunk(DC_TAG('live'));

    // 基本属性
    w.StartChunk(DC_TAG('batt'));
    for (int nloop=0; nloop <EBaseAttr_MaxSize; ++nloop)
    {
        w.WriteFloat(pInfo->baseProperty.baseAttr.baseAttrValue[nloop].base);
        w.WriteFloat(pInfo->baseProperty.baseAttr.baseAttrValue[nloop].item);
        w.WriteFloat(pInfo->baseProperty.baseAttr.baseAttrValue[nloop].status);
        w.WriteFloat(pInfo->baseProperty.baseAttr.baseAttrValue[nloop].skill);
        w.WriteFloat(pInfo->baseProperty.baseAttr.baseAttrValue[nloop].final);
    }
    w.EndChunk(DC_TAG('batt'));

    w.StartChunk(DC_TAG('fig1'));
    GameDefineSerialize::Serialize( pInfo->baseProperty.fightAttr, &w);
    w.EndChunk(DC_TAG('fig1'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > CD_CharBaseInfoBufferSize)
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteCharData Chunk(%d)>(%d) ", nActualSize, CD_CharBaseInfoBufferSize );
        return false;
    }

    //memcpy( _charBaseInfoBuffer, w.GetBuffer(), nActualSize );
    w.Destroy();
    return true;
}

void DatabaseServerWorkThread::LoadCharApto( ReadCharData inP, int nSize, SCharBaseInfo* pInfo )
{
    CDataChunkLoader l(inP.byte,nSize);

    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('ap05'))
        {
            l.StartChunk( 'ap05' );
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            while (!r.IsEndOfMemory())
            {
                if (r.IsChunk('cn01'))
                {
                    r.StartChunk('cn01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    int nStrSize = p.ReadInt();

                    memset(&pInfo->aptotic.szCharacterName, 0, sizeof(pInfo->aptotic.szCharacterName));
                    memcpy(&pInfo->aptotic.szCharacterName, p.GetPointer().byte, min(sizeof(CHAR)*nStrSize, sizeof(pInfo->aptotic.szCharacterName)));
                    p.GetPointer().c += nStrSize;

                    r.EndChunk('cn01');
                }
                else if (r.IsChunk('sx01'))
                {
                    r.StartChunk('sx01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
                    pInfo->aptotic.ucSex = p.ReadChar();
                    r.EndChunk('sx01');
                }
                else if (r.IsChunk('pf01'))
                {
                    r.StartChunk('pf01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.usProfession = p.ReadShort();
                    r.EndChunk('pf01');
                }
                else if (r.IsChunk('hc01'))
                {
                    r.StartChunk('hc01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.ucHeadPic = p.ReadChar();
                    r.EndChunk('hc01');
                }
                else if (r.IsChunk('ct01'))
                {
                    r.StartChunk('ct01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.ucCountry = p.ReadChar();
                    r.EndChunk('ct01');
                }
                else if (r.IsChunk('yn01'))
                {
                    r.StartChunk('yn01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    int nStrSize1 = p.ReadInt();

                    memset(&pInfo->aptotic.szYearName, 0, sizeof(pInfo->aptotic.szYearName));
                    memcpy(&pInfo->aptotic.szYearName, p.GetPointer().byte, min(sizeof(CHAR)*nStrSize1, sizeof(pInfo->aptotic.szYearName)));
                    p.GetPointer().c += nStrSize1;

                    r.EndChunk('yn01');
                }
                else if (r.IsChunk('yr01'))
                {
                    r.StartChunk('yr01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.byYear = p.ReadByte();
                    r.EndChunk('yr01');
                }
                else if (r.IsChunk('mt01'))
                {
                    r.StartChunk('mt01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.byMonth = p.ReadByte();
                    r.EndChunk('mt01');
                }
                else if (r.IsChunk('dy01'))
                {
                    r.StartChunk('dy01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.byDay = p.ReadByte();
                    r.EndChunk('dy01');
                }
                //else if (r.IsChunk('nd01'))
                //{
                //    r.StartChunk('nd01');
                //    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                //    pInfo->aptotic.bIsNewOtherData = p.ReadInt();
                //    r.EndChunk('nd01');
                //}
                //else if (r.IsChunk('rp01'))
                //{
                //    r.StartChunk('rp01');
                //    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                //    pInfo->aptotic.bIsNewRepute = p.ReadInt();
                //    r.EndChunk('rp01');
                //}
                else
                    r.SkipChunk();
            }                
            l.EndChunk('ap05');
        }
        else 
            l.SkipChunk();
    }
}
void DatabaseServerWorkThread::LoadCharLive( ReadCharData inP, int nSize, SCharBaseInfo* pInfo )
{
    CDataChunkLoader l(inP.byte,nSize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('lv05'))
        {
            l.OpenChunk();
            short stTemp = -1;
            while (!l.IsEndOfChunk())
            {
                if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
                else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
                else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
                else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
                else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
                else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
                else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
                else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
                else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
                else if (l.TryReadByteChunk('stmp',pInfo->liveinfo.nStorageItemGrid))     {}
                else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
                else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
                else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
                else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
                else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
                else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
                else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
                else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
                else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
                else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
                else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
                else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
                else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
                else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
                else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
                else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
                else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}    
                else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
                else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
                else if (l.IsChunk('tt01'))
                {
                    l.StartChunk('tt01');
                    {   
                        CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                        short nTitleArray[MAX_TITLE_COUNT];
                        memset( nTitleArray, 0, sizeof( nTitleArray ) );
                        r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
                        for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
                        {
                            pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
                        }
                    }   
                    l.EndChunk('tt01');
                }
                else if (l.IsChunk('tt02'))
                {
                    l.StartChunk('tt02');
                    {   
                        CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                        r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
                    }   
                    l.EndChunk('tt02');
                }
                else if ( l.IsChunk('are1') )
                {
                    l.StartChunk('are1');
                    {   
                        CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                        r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
                    }   
                    l.EndChunk('are1');
                }
                else{ l.SkipChunk();}
            }
        }
		else if (l.IsChunk('lv06'))
		{
			l.OpenChunk();
			short stTemp = -1;
			while (!l.IsEndOfChunk())
			{
				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
				else if (l.TryReadByteChunk('stmp',pInfo->liveinfo.nStorageItemGrid))     {}
				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}    
				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
				else if (l.IsChunk('tt01'))
				{
					l.StartChunk('tt01');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						short nTitleArray[MAX_TITLE_COUNT];
						memset( nTitleArray, 0, sizeof( nTitleArray ) );
						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
						{
							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
						}
					}   
					l.EndChunk('tt01');
				}
				else if (l.IsChunk('tt02'))
				{
					l.StartChunk('tt02');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
					}   
					l.EndChunk('tt02');
				}
				else if ( l.IsChunk('are1') )
				{
					l.StartChunk('are1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
					}   
					l.EndChunk('are1');
				}
				else if ( l.IsChunk('cold'))
				{
					l.StartChunk('cold');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xItemColdDown, sizeof(pInfo->liveinfo.xItemColdDown));
					}   
					l.EndChunk('cold');
				}
				else{ l.SkipChunk();}
			}
		}
        else 
            l.SkipChunk();
    }
}

void DatabaseServerWorkThread::LoadCharBaseAttr( ReadCharData inP, int nSize, SCharBaseInfo* pInfo )
{
    CDataChunkLoader l(inP.byte,nSize);

    //for (int nloop = 0; nloop <EBaseAttr_MaxSize;nloop++)
    //{
    //    pInfo->baseProperty.baseAttr.baseAttrValue[nloop].base = l.ReadFloat();
    //    pInfo->baseProperty.baseAttr.baseAttrValue[nloop].item = l.ReadFloat();
    //    pInfo->baseProperty.baseAttr.baseAttrValue[nloop].status = l.ReadFloat();
    //    pInfo->baseProperty.baseAttr.baseAttrValue[nloop].skill = l.ReadFloat();
	//    pInfo->baseProperty.baseAttr.baseAttrValue[nloop].hero = l.ReadFloat();
    //    pInfo->baseProperty.baseAttr.baseAttrValue[nloop].final = l.ReadFloat();
    //}
}

bool DatabaseServerWorkThread::LoadCharData( uint8* buffer, uint32 bufferSize, SCharBaseInfo* pInfo)
{
    CDataChunkLoader l( buffer, bufferSize );

    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk(  'apto' ) )
        {
            l.StartChunk('apto');
            ReadCharData p( l.GetPointer().c );
            LoadCharApto( p, l.GetChunkSize(), pInfo );
            l.EndChunk('apto');
        }
        else if (l.IsChunk('live'))
        {
            l.StartChunk('live');
            ReadCharData p( l.GetPointer().c );
            LoadCharLive( p, l.GetChunkSize(), pInfo );
            l.EndChunk('live');

        }
        else if (l.IsChunk('batt'))
        {
            l.StartChunk('batt');
            ReadCharData p( l.GetPointer().c );
            LoadCharBaseAttr( p, l.GetChunkSize(), pInfo );
            l.EndChunk('batt');
        }
        else if (l.IsChunk('fig1'))
        {
            l.StartChunk('fig1');
            {
                CDataChunkLoader r( l.GetPointer().byte, l.GetChunkSize());
                GameDefineSerialize::UnSerialize( r.GetPointer().byte,l.GetChunkSize(), pInfo->baseProperty.fightAttr );
            }   
            l.EndChunk('fig1');
        }
        else 
        { l.SkipChunk(); }
    }
    return true;
}

bool DatabaseServerWorkThread::WriteItemData( SCharItem* pItem, uint32& nActualSize )
{
    CDataChunkWriter w( _itemDataBuffer, CD_ItemInfoBufferSize );

    pItem->Write(&w);

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > CD_ItemInfoBufferSize)
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteItemData Chunk(%d)>(%d) ", nActualSize, CD_ItemInfoBufferSize );
        return false;
    }
    // memcpy( _itemDataBuffer, w.GetBuffer(), nActualSize );    
    w.Destroy();
    return true;
}

bool DatabaseServerWorkThread::WriteMountData( SMountItem* pMount, uint32& nActualSize )
{
    CDataChunkWriter w( _mountDataBuffer, CD_MountInfoBufferSize);
    pMount->Write(&w);

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        // ToLog( false );
        return false;
    }

    if ( nActualSize > CD_MountInfoBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteMountData Chunk(%d)>(%d) ", nActualSize, CD_MountInfoBufferSize );
        return false;
    }

    // memcpy( _mountDataBuffer, w.GetBuffer(), nActualSize );
    w.Destroy();
    return true;
}

bool DatabaseServerWorkThread::WriteVisualData( SCharVisual* pInfo, uint32& nActualSize )
{
    CDataChunkWriter w( _visualDataBuffer, CD_VisualInfoBufferSize );
    w.StartChunk(DC_TAG('visl'));
    pInfo->WriteVisual(&w);
    w.EndChunk(DC_TAG('visl'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > CD_VisualInfoBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteVisualData Chunk(%d)>(%d) ", nActualSize, CD_VisualInfoBufferSize );
        return false;
    }

    // memcpy( _visualDataBuffer, w.GetBuffer(), nActualSize );
    w.Destroy();
    return true;
}

bool DatabaseServerWorkThread::LoadVisuals( uint8* buffer, uint32 bufferSize, SCharVisual* pInfo )
{
    if ( buffer == NULL || bufferSize == 0 ||  pInfo == NULL )
    { return false; }

    CDataChunkLoader l( buffer, bufferSize );
    if (l.IsChunk('visl'))
    {
        l.StartChunk('visl');
        pInfo->ReadVisual( l.GetPointer().byte, l.GetBufferSize() );
        l.EndChunk('visl');
    }
    else 
    { l.SkipChunk(); }
    return true;
}

bool DatabaseServerWorkThread::WriteOtherData( SCharOtherData* pOtherData, uint32& nActualSize )
{
    CDataChunkWriter w( _otherDataBuffer, CD_OtherInfoBufferSize );

    w.StartChunk(DC_TAG('otda'));
    pOtherData->WriteOtherDataBlob(&w);
    w.EndChunk(DC_TAG('otda'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > CD_OtherInfoBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteOtherData Chunk(%d)>(%d) ", nActualSize, CD_OtherInfoBufferSize );
        return false;
    }

    //memcpy( _otherDataBuffer, w.GetBuffer(), nActualSize );
    w.Destroy();
    return true;
}

bool DatabaseServerWorkThread::LoadOtherData( uint8* buffer, uint32 bufferSize, SCharOtherData* pOtherData )
{
    if ( buffer == NULL || bufferSize == 0|| pOtherData == NULL )
    { return false;}

    CDataChunkLoader l( buffer, bufferSize );
    if (l.IsChunk('otda'))
    {
        l.StartChunk('otda');
        {   
            pOtherData->ReadOtherDataBlob( l.GetPointer().byte,l.GetBufferSize());
        }
        l.EndChunk('otda');
    }
    else 
    { l.SkipChunk(); }

    return true;
}

bool DatabaseServerWorkThread::WriteExtendData( SExtendData* pExtendData, uint32& nActualSize )
{
    CDataChunkWriter w( _extendDataBuffer, CD_ExtendInfoBufferSize );

    w.StartChunk(DC_TAG('exda'));
    pExtendData->Write(&w);
    w.EndChunk(DC_TAG('exda'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > CD_ExtendInfoBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteExtendData Chunk(%d)>(%d) ", nActualSize, CD_ExtendInfoBufferSize );
        return false;
    }

    // memcpy( _extendDataBuffer, w.GetBuffer(), nActualSize );
    w.Destroy();
    return true;
}

bool DatabaseServerWorkThread::LoadExtendData( uint8* buffer, uint32 bufferSize, SExtendData* pExtendData )
{
    if ( buffer == NULL || bufferSize == 0 || pExtendData == NULL )
    { return false; }

    CDataChunkLoader l( buffer, bufferSize );

    if (l.IsChunk('exda'))
    {
        l.StartChunk('exda');
        {   
            pExtendData->Read( l.GetPointer().byte, l.GetChunkSize());
        }
        l.EndChunk('exda');
    }
    else 
        l.SkipChunk();

    return true;
}

//////////////////////////////////////////////////////////////////////
bool DatabaseServerWorkThread::RepairItem(int nBagPos)
{
    char szSql[1024 * 10] = {0};
    memset( szSql, 0, sizeof(szSql));
    if( nBagPos == 0)
    { sprintf_s( szSql, "select * from [t_game_Item] Where WhoIs = 0"); }
    else
    { return false; }

    CRecordset pRec = RoleQuery( szSql );
    if( !pRec.IsOpen() )
    { return false; }

    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "正在清理不合法的物品...");

    while (!pRec.IsEOF())
    {
        DWORD dwCharDBId = atoi(pRec.Get("CharacterId"));
        int nIndex       = atoi(pRec.Get("BagIndex"));

        SCharItem ItemTemp;
        memset(&ItemTemp,0,sizeof(SCharItem));
        ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;

        static char szBuff[ 1024 * 40 ] = {0};        
        int nSize = DeCodeFromString((const unsigned char*)(pRec.Get("ItemData")), szBuff, sizeof(szBuff));

        static uint8 uncompressBuffer[ 1024 * 40 ] = { 0 };
        uint32 nBuffSize = 1024 * 40;
        uncompress( uncompressBuffer, &nBuffSize, (unsigned char*)szBuff, nSize);
        ItemTemp.Read( uncompressBuffer, nBuffSize);

        if (ItemTemp.itembaseinfo.ustItemCount > 99)
        { //如果这个物品堆叠的数量大于99个就清掉
            CRecordset pRec2;
            char szSql1[1024] = {0};
            memset( szSql1, 0, sizeof(szSql1) );
            if(nBagPos == 0)
            { printf_s( szSql1,"DELETE FROM [t_game_Item] Where CharacterId = %ld AND BagIndex = %d AND WhoIs = 0",  dwCharDBId,nIndex ); }
            else
            { continue; }

            pRec2 = RoleQuery( szSql1 );
            if (!pRec2.IsOpen())
            { continue;}
        }
        pRec.MoveNext();
    }

    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "清理完毕");
    return true;
}

void DatabaseServerWorkThread::OnQueryReqLoadPublicMessages(BaseSqlMessage* pSqlMessage)
{
    //DBAckLoadPublicMessages msg;

    //char szSql[1024] = {0};
    //memset(szSql,0,sizeof(szSql));
    //sprintf_s( szSql, "select * from t_game_public_messages");
    //CRecordset pRec = RoleQuery( szSql );
    //while (pRec.IsOpen() && !pRec.IsEOF())
    //{
    //    PublicMessageDd info;
    //    info.type        = atoi(pRec.Get("type"));
    //    info.playerDbId  = atoi(pRec.Get("playerid"));
    //    info.level       = atoi(pRec.Get("playerlevel"));
    //    info.profession  = atoi(pRec.Get("playerprofession"));
    //    info.time        = atoi(pRec.Get("publictime"));
    //    strncpy_s( info.addonInfo, sizeof(info.addonInfo), pRec.Get("addoninfo"), sizeof(info.addonInfo) - 1);
    //    strncpy_s( info.playername, sizeof(info.playername), pRec.Get("playername"), sizeof(info.playername) - 1 );

    //    msg.AddPublicMessage( info );
    //    if ( msg.nCount >= dr_MaxPublicMessagesPerCount)
    //    {
    //        GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &msg );
    //        msg.Reset();
    //    }
    //    
    //    pRec.MoveNext();
    //}

    //if ( msg.nCount > 0)
    //{
    //    GetDatabaseInterface()->PushResult( pSqlMessage->nClientId, &msg );
    //}
}

void DatabaseServerWorkThread::SaveGmInfo()
{
    //更新GM权限
    //map<string,GMINFO>::iterator it = gmlist.find( pSave->dbInfo.baseinfo.aptotic.szCharacterName );
    //if ( it != gmlist.end() )
    //{
    //    sprintf_s( szSql, "UPDATE [t_game_GMInfo] SET GMLevel = %d WHERE RoleName = '%s'", 
    //        pSave->nGMLevel, pSave->dbInfo.baseinfo.aptotic.szCharacterName );
    //    pRec = RoleQuery( szSql );
    //    if( !pRec.IsOpen() )
    //    {
    //        // ToLog( 0 && "GM权限更新失败!" );
    //        return;
    //    }
    //    it->second.nLevel = pSave->nGMLevel;
    //}
    //else if ( pSave->nGMLevel > 0 )
    //{
    //    sprintf_s( szSql,  "INSERT INTO [t_game_GMInfo]( RoleName, GMLevel, IPAddress ) VALUES( '%s', %d, '%s' )", 
    //        pSave->dbInfo.baseinfo.aptotic.szCharacterName, pSave->nGMLevel, "" );
    //    pRec = RoleQuery( szSql );
    //    if( !pRec.IsOpen() )
    //    {
    //        // ToLog( 0 && "GM权限更新失败!" );
    //        return;
    //    }
    //    GMINFO gminfo;
    //    gminfo.nLevel = pSave->nGMLevel;
    //    memset( gminfo.szIP, 0, sizeof( gminfo.szIP ) );
    //    gmlist.insert( std::make_pair( pSave->dbInfo.baseinfo.aptotic.szCharacterName, gminfo ) );
    //}
}

void DatabaseServerWorkThread::_TryLoadGmInfo()
{
    if ( _pRoleConn && _pRoleConn->IsOpen() && !_bHaveLoadGmInfo )
    {
        gmlist.clear();
        DataBase::CRecordset pRec = RoleQuery("Select * from t_game_GMInfo");
        while ( pRec.IsOpen() && !pRec.IsEOF())
        {
            string strGMName;
            GMINFO info = {0};

            strGMName = pRec.Get("RoleName");
            info.nLevel = atoi(pRec.Get("GMLevel"));
            if (pRec.Get("IPAddress") != NULL)
            {
                strncpy_s( info.szIP, sizeof( info.szIP ), pRec.Get("IPAddress"), sizeof( info.szIP ) - 1 );
            }
            gmlist.insert(std::pair<string, GMINFO>(strGMName, info));
            pRec.MoveNext();

        }

        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Loaded %d gm charater", gmlist.size());
        _bHaveLoadGmInfo = true;
    }
}

void DatabaseServerWorkThread::_CheckConnection()
{
    if ( _checkQueryTime == 0 || GameTime::IsPassCurrentTime( _checkQueryTime, ECD_CheckQueryTimeInterval ) )
    { 
        char szSql[128] = {0};

        sprintf_s( szSql, "select 1");
        CRecordset pRec = RoleQuery( szSql );
        if ( !pRec.IsOpen() )
        { }
        _checkQueryTime = HQ_TimeGetTime();
    }

    if ( _pRoleConn/* && _pRoleConn->GetErrorCount() >= ECD_MaxErrorCount*/)
    { _connectState = MSS_Reconnect;}
}
