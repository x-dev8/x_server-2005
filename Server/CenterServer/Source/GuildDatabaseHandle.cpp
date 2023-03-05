#include "NormalLogicWorkThread.h"
#include "tstring.h"
#include "MySqlCommunication.h"
#include "zlib/zlib.h"


void NormalLogicWorkThread::OnGuildDataLoadReq( BaseSqlMessage* pSqlMessage )
{
    LoadGuildData( pSqlMessage );
    LoadGuildMember( pSqlMessage );
}

void NormalLogicWorkThread::LoadGuildData( BaseSqlMessage* pSqlMessage )
{
    char szSql[ 512 ] = { 0 };
    memset( szSql, 0,sizeof( szSql ) );
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from guild;" );

    DB2CSGuildDataList xList;  

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty() )
        {
            GuildDataToServer xData;

            for (int i = 0; i < res.num_rows(); ++i )
            {
                xData.SetID( res[i]["id"] );

                Common::_tstring strName;
                strName.fromUTF8( res[i]["name"] );
                xData.SetName( strName.c_str() );

                Common::_tstring strNotice;
                strNotice.fromUTF8( res[i]["notice"] );
                xData.SetNotice( strNotice.c_str() );

				Common::_tstring strAim;
				strAim.fromUTF8( res[i]["aim"] );
				xData.SetAim( strAim.c_str() );

                xData.SetCountry( res[i]["country"] );
                xData.SetLevel( res[i]["level"] );
                xData.SetMasterID( res[i]["master"] );
                xData.SetMoney( res[i]["money"] );
                xData.SetShopLevel( res[i]["shoplevel"] );
                xData.SetExp( res[i]["exp"] );
                xData.SetMission( res[i]["mission"] );
				xData.SetMissionCount(res[i]["missioncount"]);
                xData.SetSalary( res[i]["salary"] );
                xData.SetCreateTime( res[i]["createtime"] );
                xData.SetDisbandTime( res[i]["disbandtime"] );
                xData.SetReleaseTime( res[i]["releasetime"] );
				int X = res[i]["changename"];
				xData.SetChangeName( X ==0?false:true);
				xData.SetGuildCampBattlePoint( res[i]["GuildCampBattlePoint"]);
                // 需要存放压缩过后的字符
                static uint8 bufferDecodeField[ GuildDefine::DecodeFieldBufferSize ] = { 0 };
                static uint8 bufferTempUnZip  [ GuildDefine::UnZipTempBufferSize   ] = { 0 };

                memset( bufferDecodeField, 0, GuildDefine::DecodeFieldBufferSize );
                memset( bufferTempUnZip, 0, GuildDefine::UnZipTempBufferSize );
                uint32 unZipBufferSize = GuildDefine::UnZipTempBufferSize;
                uint32 nDecodeSize = 0;
                uint32 nCopySize = 0;

                // 家族信息
                nDecodeSize = DeCodeToBuffer((const int8*)(res[i]["family"]), bufferDecodeField, GuildDefine::DecodeFieldBufferSize );
                unZipBufferSize = GuildDefine::UnZipTempBufferSize;
                uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeSize );
                nCopySize = sizeof( FamilyData ) * GuildDefine::MaxFamilyCount;
                memcpy_s( xData.GetFamily(1), nCopySize, bufferTempUnZip, nCopySize );

                // 帮派记数变量
                nDecodeSize = DeCodeToBuffer((const int8*)(res[i]["vars"]), bufferDecodeField, GuildDefine::DecodeFieldBufferSize );
                unZipBufferSize = GuildDefine::UnZipTempBufferSize;
                uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeSize );
                nCopySize = sizeof( short ) * GuildDefine::MaxGuildVarCount;
                memcpy_s( xData.GetVarAddress(), nCopySize, bufferTempUnZip, nCopySize );

                xList.AddGuildData( xData );
                if ( xList.IsFull() )
                {
                    theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId );
                    xList.Reset();
                }
				xData.SetBattleSum(res[i]["battlesum"]);	
            }
        }
    TRYEND

    CHECK_SQL_RESULT( result ) // 执行检测
    theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId ); 
}

void NormalLogicWorkThread::LoadGuildMember( BaseSqlMessage* pSqlMessage )
{
    char szSql[ 512 ] = { 0 };
    memset( szSql, 0,sizeof( szSql ) );
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from guildmember;" );

    DB2CSGuildMemberList xList;  

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty() )
        {
            GuildMember xMember;

            for (int i = 0; i < res.num_rows(); ++i )
            {
                xMember.SetID( res[i]["id"] );

                Common::_tstring strName;
                strName.fromUTF8( res[i]["name"] );
                xMember.SetName( strName.c_str() );

                xMember.SetLevel( res[i]["level"] );
                xMember.SetProfession( res[i]["profession"] );
                xMember.SetGuildID( res[i]["guild"] );
                xMember.SetPosition( res[i]["position"] );
                xMember.SetFamilyID( res[i]["family"] );
                xMember.SetOffer( res[i]["offer"] );
                xMember.SetActivity( res[i]["activity"] );
                xMember.SetLastActivity( res[i]["lastactivity"] );
				xMember.SetCampBattleValue( res[i]["campbattlevalue"] );
				xMember.SetOnLineTime( res[i]["OnLineTime"] );
                xList.AddGuildMember( xMember );
                if ( xList.IsFull() )
                {
                    theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId );
                    xList.Reset();
                }
            }
        }
    TRYEND

    CHECK_SQL_RESULT( result ) // 执行检测
    theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId ); 
}

void NormalLogicWorkThread::OnGuildDataUpdateReq( BaseSqlMessage* pSqlMessage )
{
    CS2DBGuildDataUpdateReq *pReq = static_cast< CS2DBGuildDataUpdateReq* >( pSqlMessage->GetMessageAddress() );

    static uint8 bufferTempZip[ GuildDefine::ZipTempBufferSize ]        = {0};
    static int8 bufferFamilyField[ GuildDefine::EncodeFieldBufferSize ] = {0};
    static int8 bufferVarsField[ GuildDefine::EncodeFieldBufferSize ]   = {0};

    memset( bufferFamilyField, 0, GuildDefine::EncodeFieldBufferSize );
    memset( bufferVarsField, 0, GuildDefine::EncodeFieldBufferSize );

    uint32 zipBufferSize = GuildDefine::ZipTempBufferSize;

    compress( bufferTempZip, (uLongf*)&zipBufferSize, (uint8*)pReq->xData.GetFamily( 1 ), sizeof( FamilyData ) * GuildDefine::MaxFamilyCount ); // 压缩数据
    EnCodeToString( bufferTempZip,bufferFamilyField, zipBufferSize, GuildDefine::EncodeFieldBufferSize ); // 转为字符串

    zipBufferSize = GuildDefine::ZipTempBufferSize;
    compress( bufferTempZip, (uLongf*)&zipBufferSize, (uint8*)pReq->xData.GetVarAddress(), sizeof( short ) * GuildDefine::MaxGuildVarCount ); // 压缩数据
    EnCodeToString( bufferTempZip,bufferVarsField, zipBufferSize, GuildDefine::EncodeFieldBufferSize ); // 转为字符串

    char szSql[ 512 ] = { 0 };
    sprintf_s( szSql, sizeof( szSql ) - 1, "select country from guild where id=%ld;", pReq->xData.GetID() );

    uint32 result = ER_Success;
    bool bIsExist = false;

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty() )
        { bIsExist = true; }
        mysqlQuery.reset();
    TRYEND

    if ( !bIsExist )        // 存在
    {
        memset( szSql, 0, sizeof( szSql ) );
        strncpy_s( szSql, sizeof( szSql ), "insert into guild(id,name,country,notice,level,master,money,shoplevel,exp,mission,missioncount,salary,createtime,disbandtime,releasetime,family,vars,aim,strength,battlesum,changename,GuildCampBattlePoint) values(%0,%1q,%2,%3q,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15q,%16q,%17q,%18,%19,%20,%21);", sizeof( szSql ) - 1 );

        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned( pReq->xData.GetID() ), _tUTF8CHAR( pReq->xData.GetName() ), pReq->xData.GetCountry(), _tUTF8CHAR( pReq->xData.GetNotice() ), pReq->xData.GetLevel(),
                mysqlpp::sql_int_unsigned( pReq->xData.GetMasterID() ), mysqlpp::sql_int_unsigned( pReq->xData.GetMoney() ), mysqlpp::sql_int_unsigned( pReq->xData.GetShopLevel() ), mysqlpp::sql_int_unsigned( pReq->xData.GetExp() ), 
                mysqlpp::sql_int_unsigned( pReq->xData.GetMission() ),mysqlpp::sql_int_unsigned( pReq->xData.GetMissionCount() ), mysqlpp::sql_int_unsigned( pReq->xData.GetSalary() ), mysqlpp::sql_bigint_unsigned( pReq->xData.GetCreateTime() ),
				mysqlpp::sql_bigint_unsigned( pReq->xData.GetDisbandTime() ), mysqlpp::sql_bigint_unsigned( pReq->xData.GetReleaseTime() ), bufferFamilyField, bufferVarsField, _tUTF8CHAR( pReq->xData.GetAim() ),pReq->xData.GetStrength(),pReq->xData.GetBattleSum(),pReq->xData.GetIsCanChangeName()?1:0,pReq->xData.GetGuildCampBattlePoint());
            mysqlQuery.reset();
        TRYEND
    }
    else        // 已经存在就更新
    {
        memset( szSql, 0, sizeof( szSql ) );
        strncpy_s( szSql, sizeof( szSql ), "update guild set notice=%1q,level=%2,master=%3,money=%4,shoplevel=%5,exp=%6,mission=%7,missioncount=%8,salary=%9,disbandtime=%10,releasetime=%11,family=%12q,vars=%13q,aim=%14q,strength=%15,battlesum =%16,name= %17q,changename=%18,GuildCampBattlePoint=%19 where id=%0;", sizeof( szSql ) - 1 );

        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned( pReq->xData.GetID() ), _tUTF8CHAR( pReq->xData.GetNotice() ), pReq->xData.GetLevel(), mysqlpp::sql_int_unsigned( pReq->xData.GetMasterID() ),
                mysqlpp::sql_int_unsigned( pReq->xData.GetMoney() ), mysqlpp::sql_int_unsigned( pReq->xData.GetShopLevel() ), mysqlpp::sql_int_unsigned( pReq->xData.GetExp() ), mysqlpp::sql_int_unsigned( pReq->xData.GetMission() ),
				mysqlpp::sql_int_unsigned( pReq->xData.GetMissionCount() ),mysqlpp::sql_int_unsigned( pReq->xData.GetSalary() ), mysqlpp::sql_bigint_unsigned( pReq->xData.GetDisbandTime() ), 
				mysqlpp::sql_bigint_unsigned( pReq->xData.GetReleaseTime() ), bufferFamilyField, bufferVarsField, _tUTF8CHAR( pReq->xData.GetAim() ),pReq->xData.GetStrength(),pReq->xData.GetBattleSum(), _tUTF8CHAR( pReq->xData.GetName()),pReq->xData.GetIsCanChangeName()?1:0,pReq->xData.GetGuildCampBattlePoint());
            mysqlQuery.reset();
        TRYEND
    }
}

void NormalLogicWorkThread::OnGuildMemberUpdateReq( BaseSqlMessage* pSqlMessage )
{
    CS2DBGuildMemberUpdateReq *pReq = static_cast< CS2DBGuildMemberUpdateReq* >( pSqlMessage->GetMessageAddress() );

    for ( int i = 0; i < pReq->ustCount; ++i )
    {
        UpdateGuileMember( pReq->xList[i] );
    }
}

void NormalLogicWorkThread::UpdateGuileMember( GuildMember& xMember )
{
    char szSql[ 512 ] = { 0 };
    sprintf_s( szSql, sizeof( szSql ) - 1, "select level from guildmember where id=%ld;", xMember.GetID() );

    uint32 result = ER_Success;
    bool bIsExist = false;

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty() )
        { bIsExist = true; }
        mysqlQuery.reset();
    TRYEND

    if ( !bIsExist )        // 存在
    {
    memset( szSql, 0, sizeof( szSql ) );
    strncpy_s( szSql, sizeof( szSql ), "insert into guildmember(id,name,level,profession,guild,position,family,offer,activity,lastactivity,campbattlevalue,OnLineTime) values(%0,%1q,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11);", sizeof( szSql ) - 1 );

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_int_unsigned( xMember.GetID() ), _tUTF8CHAR( xMember.GetName() ), xMember.GetLevel(), xMember.GetProfession(),
            mysqlpp::sql_int_unsigned( xMember.GetGuildID() ), xMember.GetPosition(), xMember.GetFamilyID(), mysqlpp::sql_int_unsigned( xMember.GetOffer() ), 
			xMember.GetActivity(), xMember.GetLastActivity(),xMember.GetCampBattleValue(),xMember.GetOnLineTime());
        mysqlQuery.reset();
    TRYEND
    }
    else        // 已经存在就更新
    {
        memset( szSql, 0, sizeof( szSql ) );
        strncpy_s( szSql, sizeof( szSql ), "update guildmember set name=%1q,level=%2,profession=%3,guild=%4,position=%5,family=%6,offer=%7,activity=%8,lastactivity=%9,campbattlevalue=%10,OnLineTime=%11 where id=%0;", sizeof( szSql ) - 1 );

        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned( xMember.GetID() ), _tUTF8CHAR( xMember.GetName() ), xMember.GetLevel(), xMember.GetProfession(),
                mysqlpp::sql_int_unsigned( xMember.GetGuildID() ), xMember.GetPosition(), xMember.GetFamilyID(), mysqlpp::sql_int_unsigned( xMember.GetOffer() ), 
                xMember.GetActivity(), xMember.GetLastActivity(),xMember.GetCampBattleValue(),xMember.GetOnLineTime());
            mysqlQuery.reset();
        TRYEND
    }
}

void NormalLogicWorkThread::OnGuildDisbandReq( BaseSqlMessage* pSqlMessage )
{
    CS2DBGuildDisbandReq *pReq = static_cast< CS2DBGuildDisbandReq* >( pSqlMessage->GetMessageAddress() );

    char szSql[512] = { 0 };
    uint32 result = ER_Success;    

    TRYBEGIN
        sprintf_s( szSql, sizeof( szSql ) - 1, "delete from guild where id=%ld;", pReq->nGuildID );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();

        sprintf_s( szSql, sizeof( szSql ) - 1, "delete from guildmember where guild=%u;", pReq->nGuildID );
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();
    TRYEND
}

void NormalLogicWorkThread::OnGuildMemberLeaveReq( BaseSqlMessage* pSqlMessage )
{
    CS2DBGuildMemberLeaveReq *pReq = static_cast< CS2DBGuildMemberLeaveReq* >( pSqlMessage->GetMessageAddress() );

    char szSql[512] = { 0 };
    uint32 result = ER_Success;

    sprintf_s( szSql, sizeof( szSql ) - 1, "delete from guildmember where id=%u;", pReq->nPlayerID );

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();
    TRYEND
}