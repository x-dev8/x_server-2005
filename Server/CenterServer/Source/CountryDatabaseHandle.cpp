#include "NormalLogicWorkThread.h"
#include "zlib/zlib.h"
#include "tstring.h"
#include "MySqlCommunication.h"
#include "CountrySave.h"

void NormalLogicWorkThread::OnRequestCountryDataReq( BaseSqlMessage *pSqlMessage )
{
    static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

    DB2CSRequestCountryDataAck xAck;

    TRYBEGIN
    {
        sprintf_s( szSql, sizeof( szSql ), "select * from countrys;" );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();      

        if ( res && !res.empty() )
        {
            for ( int i = 0; i < res.num_rows(); ++i )
            {
                uint8 uchID = res[i]["id"];
                if ( uchID == CountryDefine::Country_Init || uchID >= CountryDefine::Country_Max )
                { continue; }

                // 读国家信息buffer
                static uint8 bufferDecodeField[ 1024 * 10 ] = {0};
                static uint8 bufferTempUnZip  [ 1024 * 10 ] = {0};
                uint32 unZipBufferSize = sizeof( bufferTempUnZip );

                uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[i]["data"].c_str(), bufferDecodeField, sizeof( bufferDecodeField ) );
                unZipBufferSize = sizeof( bufferTempUnZip );;
                uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeBufferActualSize );
                CountrySave::ReadGameCountry( bufferTempUnZip, unZipBufferSize, xAck.xData[ uchID ] );
            }
        }
        mysqlQuery.reset();
    }
    TRYEND
	for(size_t i = CountryDefine::Country_Init;i<CountryDefine::Country_Max;++i)
	{
		for(size_t j = CountryDefine::Position_None; j<CountryDefine::Position_Max;++j)
		{
			if(xAck.xData[i].GetID() ==0) continue;

			if( xAck.xData[i].GetOfficial(j)  && xAck.xData[i].GetOfficial(j)->GetID() ==CountryDefine::ErrorID )
				continue;				
			//查询玩家的性别 玩家的头部信息 然后保存起来
			uint8 sexid = xAck.xData[i].GetOfficial(j)->GetSexID();
			uint16 faceid = xAck.xData[i].GetOfficial(j)->GetFaceID();
			uint16 headerid = xAck.xData[i].GetOfficial(j)->GetHeaderID();
			uint16 professionID =xAck.xData[i].GetOfficial(j)->GetProfessionID();
			OnLoadCountryOfficialFace(xAck.xData[i].GetOfficial(j)->GetID(),sexid,faceid,headerid,professionID);
			xAck.xData[i].GetOfficial(j)->SetSexID(sexid);
			xAck.xData[i].GetOfficial(j)->SetFaceID(faceid);
			xAck.xData[i].GetOfficial(j)->SetHeaderID(headerid);
			xAck.xData[i].GetOfficial(j)->SetProfessionID(professionID);	
		}
	}

	OnRequestCountryInfoReq(pSqlMessage);//处理国家信息的数据

	TRYBEGIN
    {
		sprintf_s( szSql, sizeof( szSql ), "select country,count(country) as sum from t_game_character group by country;" );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();  
		if ( res && !res.empty() )
        {
			for ( int i = 0; i < res.num_rows(); ++i )
            {
				if(i >= CountryDefine::Country_Max ) break;
				uint8 CountryID =  res[i]["country"];
				uint32 Sum = res[i]["sum"];
				xAck.PlayerSum[CountryID] = Sum;
			}
		}
		mysqlQuery.reset();
		theMysqlCommunication.PushAckMessage( &xAck, pSqlMessage->nClientId );
	}
	TRYEND

    // 执行失败
    if ( RESULT_FAILED( result ) )
    { return; }
}
void NormalLogicWorkThread::OnRequestCountryInfoReq(BaseSqlMessage* pSqlMessage)
{
	//读取数据库的里国家信息方面的数据 并且存储到内存中去
	static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

	DB2CSRequestCountryInfoAck msg;
	TRYBEGIN
    {
        sprintf_s( szSql, sizeof( szSql ), "(select * from countryinfo where countryid =%d order by logtime limit %d ) union all (select * from countryinfo where countryid =%d order by logtime limit %d ) union all (select * from countryinfo where countryid =%d order by logtime limit %d )"
			,CountryDefine::Country_LouLan,CountryDefine::MaxCountryInfoSum
			,CountryDefine::Country_KunLun,CountryDefine::MaxCountryInfoSum
			,CountryDefine::Country_DunHuang,CountryDefine::MaxCountryInfoSum);//根据时间倒序
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();      

        if ( res && !res.empty() )
        {
            for ( int i = 0; i < res.num_rows(); ++i )
            {
                //处理读取出来的信息
				uint8 countryID = res[i]["countryid"];
				time_t t;
				mysqlpp::DateTime xLogTime =res[i]["logtime"];
				int Value = res[i]["value"];
				t = xLogTime.operator time_t();
				__int64 timeLog = t;

				/*char Info[CountryDefine::MaxCountryInfoLength];
				strcpy_s(Info,CountryDefine::MaxCountryInfoLength-1,res[i]["info"].c_str());
				WCHAR wstr[CountryDefine::MaxCountryInfoLength];
				MultiByteToWideChar(CP_UTF8,0,Info,CountryDefine::MaxCountryInfoLength-1,wstr,CountryDefine::MaxCountryInfoLength-1);
				strcpy_s(Info,CountryDefine::MaxCountryInfoLength-1,_tANSICHAR(wstr));*/

				Common::_tstring strName;
                strName.fromUTF8( res[i]["info"] );

				strcpy_s(msg.Info[i%CountryDefine::MaxMsgCountryInfoSum],CountryDefine::MaxCountryInfoLength-1,strName.c_str());
				msg.CountryID[i%CountryDefine::MaxMsgCountryInfoSum] = countryID;
				msg.values[i%CountryDefine::MaxMsgCountryInfoSum] = Value;
				msg.Time[i%CountryDefine::MaxMsgCountryInfoSum] = timeLog;
				++msg.Sum;
				if(msg.Sum == CountryDefine::MaxMsgCountryInfoSum)
				{
					msg.IsEnd = (i==res.num_rows()-1);
					theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );

					memset( msg.Info, 0, sizeof( msg.Info ) );
					memset( msg.Time, 0, sizeof( msg.Time ) );
					memset( msg.CountryID, 0, sizeof( msg.CountryID ) );
					memset( msg.values, 0, sizeof( msg.values ) );
					msg.Sum = 0;
					msg.IsEnd = false;
				}
            }
			if(msg.Sum != 0)
			{
				msg.IsEnd = true;
				theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
			}
        }
        mysqlQuery.reset();
    }
    TRYEND
}
void NormalLogicWorkThread::OnLoadCountryOfficialFace(uint32 RoleID,uint8& Sex,uint16& FaceID,uint16& HeaderID,uint16& ProfessionID)
{
	static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;
	TRYBEGIN
    {
		sprintf_s( szSql, sizeof( szSql ), "select * from t_game_character where CharacterId = %ld and IsDel = 0;",RoleID);
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();      
		if ( res && !res.empty() )
        {
			static char tempDecodeBufferBaseinfo[1024*100] = {0};
			int nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(res[0]["DataInfo"].c_str()), tempDecodeBufferBaseinfo, sizeof(tempDecodeBufferBaseinfo));

            // baseinfo 解压缩进人物信息当中
            static uint8 uncompressBufffer[1024*256] = {0};            
            uint32 uncompressBufferSize = 1024*256;
            uncompress( uncompressBufffer, &uncompressBufferSize, (uint8*)tempDecodeBufferBaseinfo,  nDecodeBufferActualSize);
			
			//读取玩家性别
			CDataChunkLoader l( uncompressBufffer, uncompressBufferSize);
			while( !l.IsEndOfMemory() )
			{
				if( l.IsChunk(  'apto' ) )
				{
					l.StartChunk('apto');
					//ReadCharData p( l.GetPointer().c );
					CDataChunkLoader sr(l.GetPointer().byte,l.GetChunkSize());
					//读取数据
					while( !sr.IsEndOfMemory() )
					{
						if (sr.IsChunk('ap05'))
						{
							sr.StartChunk( 'ap05' );
							CDataChunkLoader r(sr.GetPointer().byte,sr.GetChunkSize());
							while (!r.IsEndOfMemory())
							{
								if (r.IsChunk('sx01'))
								{
									r.StartChunk('sx01');
									CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
									Sex = p.ReadChar();
									r.EndChunk('sx01');
								}
								else if (r.IsChunk('pf01'))
								{
									r.StartChunk('pf01');
									CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
									ProfessionID = p.ReadShort();
									r.EndChunk('pf01');
								}
								else
									r.SkipChunk();
							}
						}
						else
							sr.SkipChunk();
					}
					l.EndChunk('apto');
					break;
				}
				else
					l.SkipChunk();
			}
		}
		mysqlQuery.reset();
	}
	TRYEND
	
	TRYBEGIN
    {
		memset( szSql, 0, sizeof(szSql) );
		sprintf_s( szSql, sizeof( szSql ), "select * from t_game_visualinfo where CharacterId = %ld;",RoleID);
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();      
		if ( res && !res.empty() )
        {
			//读取玩家的头部信息
			static int8 tempDecodeBufferVisual[1024*40] = {0};
            int nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(res[0]["DataInfo"].c_str()), tempDecodeBufferVisual, sizeof(tempDecodeBufferVisual));
			static uint8 uncompressBuffferVisual[ 1024 * 40 ] = {0};
            uint32 uncompressBufferSize = 1024 * 40;
            uncompress( uncompressBuffferVisual,&uncompressBufferSize,(unsigned char*)tempDecodeBufferVisual, nDecodeBufferActualSize);
			CDataChunkLoader l( uncompressBuffferVisual, uncompressBufferSize );

			while( !l.IsEndOfMemory() )
			{
				if( l.IsChunk(  'visl' ) )
				{
					l.StartChunk('visl');
					CDataChunkLoader sr(l.GetPointer().byte,l.GetChunkSize());
					//读取数据
					while( !sr.IsEndOfMemory() )
					{
						if (sr.IsChunk('hai1'))
						{
							sr.StartChunk( 'hai1' );
							{
								CDataChunkLoader r(sr);
								HeaderID = r.ReadShort();
							}
							sr.EndChunk('hai1');
						}
						else if (sr.IsChunk('fac1'))
						{
							sr.StartChunk('fac1');
							{
								CDataChunkLoader r(sr);
								FaceID = r.ReadShort();
							}
							sr.EndChunk('fac1');
						}
						else
							sr.SkipChunk();
					}
					l.EndChunk('visl');
					break;
				}
				else
					l.SkipChunk();
			}
		}
		mysqlQuery.reset();
	}
	TRYEND
}
void NormalLogicWorkThread::OnGetCountryOfficeFaceInfo ( BaseSqlMessage* pSqlMessage )
{
	CS2DBCountryOfficeReq *pMsg = static_cast< CS2DBCountryOfficeReq* >( pSqlMessage->GetMessageAddress() );
    if ( pMsg == NULL )
    { return; }
	uint8 sexid = -1;
	uint16 faceid = -1;
	uint16 headerid = -1;
	uint16 professionID =-1;
	OnLoadCountryOfficialFace(pMsg->nPlayerID,sexid,faceid,headerid,professionID);

	if(sexid == 0xFF || faceid ==0xFFFF || headerid == 0xFFFF || professionID == 0xFFFF)
		return;

	DB2CSRequestCountryOfficeAck msg;
	HelperFunc::SafeNCpy( msg.szName, pMsg->szName, sizeof( msg.szName ) );
	msg.nPlayerID = pMsg->nPlayerID;
	msg.faceID = faceid;
	msg.headerID = headerid;
	msg.professionID = professionID;
	msg.sexID = sexid;
	msg.countryID = pMsg->countryID;
	msg.uchPosition = pMsg->uchPosition;
	theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
}
void NormalLogicWorkThread::OnSaveCountryInfoReq(BaseSqlMessage* pSqlMessage)
{
	CS2DBRequestCountryInfoReq *pSave = static_cast< CS2DBRequestCountryInfoReq* >( pSqlMessage->GetMessageAddress() );
	if ( pSave == NULL )
    { return; }
	
	static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

    TRYBEGIN
    {
        // 插入新的
		mysqlpp::DateTime xLogTime(pSave->Time);
		string TimeStr = xLogTime.str();
		sprintf_s( szSql, sizeof( szSql ) - 1, "insert into countryinfo(info,countryid,value,logtime) values('%s',%d,%d,'%s');",_tUTF8CHAR(pSave->Info),pSave->CountryID,pSave->Value,TimeStr.c_str());
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
		

        //strncpy_s( szSql, sizeof( szSql ), "insert into countryinfo(info,countryid,value,logtime) values(%0q,%1,%2,%3);", sizeof( szSql ) - 1 );
       /* mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute(_tUTF8CHAR(pSave->Info),pSave->CountryID,pSave->Value,xLogTime);
        mysqlQuery.reset();*/
    }
    TRYEND

	// 执行失败
    if ( RESULT_FAILED( result ) )
    { return; }
}
void NormalLogicWorkThread::OnCountryDataSaveReq( BaseSqlMessage *pSqlMessage )
{
    CS2DBCountryDataSaveReq *pSave = static_cast< CS2DBCountryDataSaveReq* >( pSqlMessage->GetMessageAddress() );
    if ( pSave == NULL )
    { return; }

    static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

    static uint8 bufferItemDataChunk[ 1024 * 10 ] = { 0 };
    static uint8 bufferTempZipItem  [ 1024 * 10 ] = { 0 };
    static int8  bufferItemDataField[ 1024 * 10 ] = { 0 };

    uint32 zipBufferSize = sizeof( bufferTempZipItem );
    uint32 nActualSize = 0;
    if ( !CountrySave::WriteGameCountry( pSave->xData, nActualSize, bufferItemDataChunk, sizeof( bufferItemDataChunk ) ) )
    { return; }
    compress( bufferTempZipItem,( uLongf* )&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
    EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, sizeof( bufferItemDataField ) );

    TRYBEGIN
    {
        sprintf_s( szSql, sizeof( szSql ) - 1, "select id from countrys where id=%d;", pSave->xData.GetID() );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();   
        if ( res && !res.empty() )      
        {
            // 存在就更新
            strncpy_s( szSql, sizeof( szSql ), "update countrys set kingguild=%1,money=%2,strength=%3,data=%4q,Tribute=%5 where id=%0;", sizeof( szSql ) - 1 );

            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( pSave->xData.GetID(), mysqlpp::sql_int_unsigned( pSave->xData.GetKingGuild() ), mysqlpp::sql_int_unsigned( pSave->xData.GetMoney() ),
                mysqlpp::sql_int_unsigned( pSave->xData.GetLastStrength() ), bufferItemDataField,mysqlpp::sql_int_unsigned( pSave->xData.GetTribute()));
            mysqlQuery.reset();
        }
        else
        {
            // 插入新的
            strncpy_s( szSql, sizeof( szSql ), "insert into countrys(id,kingguild,money,strength,data,Tribute) values(%0,%1,%2,%3,%4q,%5);", sizeof( szSql ) - 1 );

            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( pSave->xData.GetID(), mysqlpp::sql_int_unsigned( pSave->xData.GetKingGuild() ), mysqlpp::sql_int_unsigned( pSave->xData.GetMoney() ),
                mysqlpp::sql_int_unsigned( pSave->xData.GetLastStrength() ), bufferItemDataField,mysqlpp::sql_int_unsigned(pSave->xData.GetTribute()) );
            mysqlQuery.reset();
        }
    }
    TRYEND
    
    // 执行失败
    if ( RESULT_FAILED( result ) )
    { return; }
}
