#include "NormalLogicWorkThread.h"
#include "MySqlCommunication.h"
#include "zlib/zlib.h"
void NormalLogicWorkThread::OnLoadGlobalDBReq(BaseSqlMessage* pSqlMessage)
{
	//读取一个服务器的数据 
	//1.查询数据库 这个表里就一条数据并且主键ID为1
	static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;
	TRYBEGIN
    {
        sprintf_s( szSql, sizeof( szSql ), "select * from globaldb where id = 1;" );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();      
        if ( res && !res.empty() && res.num_rows() == 1)
        {
			GS2CSLoadGlobalDBAck msg;
            static char tempDecodeBufferBaseinfo[1024*100] = {0};
			int nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(res[0]["info"].c_str()), tempDecodeBufferBaseinfo, sizeof(tempDecodeBufferBaseinfo));
            static uint8 uncompressBufffer[1024*256] = {0};            
            uint32 uncompressBufferSize = 1024*256;
            uncompress( uncompressBufffer, &uncompressBufferSize, (uint8*)tempDecodeBufferBaseinfo,  nDecodeBufferActualSize);
			ReadGlobalDBByte(uncompressBufffer,uncompressBufferSize,msg.info);
			//发送命令
			theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
        }
		else // 否则没有数据 就发送空的
		{
			GS2CSLoadGlobalDBAck msg;
			theMysqlCommunication.PushAckMessage( &msg, pSqlMessage->nClientId );
		}
        mysqlQuery.reset();
    }
    TRYEND
    if ( RESULT_FAILED( result ) )
    { return; }
}
void NormalLogicWorkThread::OnSaveGlobalDBReq(BaseSqlMessage* pSqlMessage)
{
	//将数据保存起来
	GS2CSSaveGlobalDBReq *pMsg = static_cast< GS2CSSaveGlobalDBReq* >( pSqlMessage->GetMessageAddress() );
	if(!pMsg) return;
	static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;
    static uint8 bufferItemDataChunk[ 1024 * 256 ] = { 0 };
    static uint8 bufferTempZipItem  [ 1024 * 256 ] = { 0 };
    static int8  bufferItemDataField[ 1024 * 256 ] = { 0 };
    uint32 zipBufferSize = sizeof( bufferTempZipItem );
    uint32 nActualSize = 0;
    if ( !WriteGlobalDBByte(bufferItemDataChunk,sizeof( bufferItemDataChunk),pMsg->info,nActualSize))
    { 
		return; 
	}
    compress( bufferTempZipItem,( uLongf* )&zipBufferSize, bufferItemDataChunk, nActualSize ); // 压缩数据
    EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, sizeof( bufferItemDataField ));
	//数据压缩完毕后 我们判断当前数据是插入还是Update
	TRYBEGIN
    {
        sprintf_s( szSql, sizeof( szSql ) - 1, "select id from globaldb where id = 1;");
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();   
        if ( res && !res.empty() && res.num_rows() == 1 )      
        {
            // 存在就更新
            strncpy_s( szSql, sizeof( szSql ), "update globaldb set info=%0q where id=1;", sizeof( szSql ) - 1 );
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute(bufferItemDataField);
            mysqlQuery.reset();
        }
        else
        {
            // 插入新的
            strncpy_s( szSql, sizeof( szSql ), "insert into globaldb(id,info) values(%0,%1q);", sizeof( szSql ) - 1 );
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute(1,bufferItemDataField);
            mysqlQuery.reset();
        }
    }
    TRYEND
	// 执行失败
    if ( RESULT_FAILED( result ) )
    { return; }
}
void NormalLogicWorkThread::ReadGlobalDBByte(BYTE* bybuff,DWORD dwsize,GlobalDB& info)
{
	//读取指定数据库 并且设置到集合里面去
	CDataChunkLoader l(bybuff,dwsize);
	while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk('gdb1'))
        {
			l.StartChunk( 'gdb1' );            
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
				info.SetBattleSum(r.ReadDword());
				info.SetMapCountryID(0);
            }
            l.EndChunk('gdb1');
        }
		else if( l.IsChunk('gdb2'))
        {
			l.StartChunk( 'gdb2' );            
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
				info.SetBattleSum(r.ReadDword());
				info.SetMapCountryID(r.ReadDword());
            }
            l.EndChunk('gdb2');
        }
		else if( l.IsChunk('gdb3'))
        {
			l.StartChunk( 'gdb3' );            
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
				info.SetBattleSum(r.ReadDword());
				info.SetMapCountryID(r.ReadDword());
				for(size_t i =0;i<GlobalDB::MAX_TimeHHandleSum;++i)
				{
					info.SetTimeHandleLog(i,r.ReadInt64());
				}
            }
            l.EndChunk('gdb3');
        }
		else if( l.IsChunk('gdb4'))
        {
			l.StartChunk( 'gdb4' );            
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            {
				info.SetBattleSum(r.ReadDword());
				info.SetMapCountryID(r.ReadDword());
				for(size_t i =0;i<GlobalDB::MAX_TimeHHandleSum;++i)
				{
					info.SetTimeHandleLog(i,r.ReadInt64());
				}
				for(size_t i =0;i<GlobalDB::MAX_TimeHHandleSum;++i)
				{
					info.SetTimeHandleState(i,r.ReadInt());
				}
            }
            l.EndChunk('gdb4');
        }
		else 
        {
			l.SkipChunk(); 
		}
	}
}
bool NormalLogicWorkThread::WriteGlobalDBByte(uint8* pOutBuffer,uint32 outBufferSize,GlobalDB& info,uint32& nActualSize)
{
	//将结构里的数据写入到字段内
	CDataChunkWriter xWriter( pOutBuffer, outBufferSize );
	xWriter.StartChunk(DC_TAG('gdb4'));
    xWriter.WriteDword(info.GetBattleSum());
	xWriter.WriteDword(info.GetMapCountryID());
	for(size_t i =0;i<GlobalDB::MAX_TimeHHandleSum;++i)
	{
		xWriter.WriteInt64(info.GetTimeHandleLog(i));
	}
	for(size_t i =0;i<GlobalDB::MAX_TimeHHandleSum;++i)
	{
		xWriter.WriteInt(info.GetTimeHandleState(i));
	}
    xWriter.EndChunk(DC_TAG('gdb4'));
	nActualSize = xWriter.GetUsedSize();
    if( nActualSize == 0 )
    {
        xWriter.Destroy();
        return false;
    }
    if ( nActualSize > outBufferSize)
    { 
		return false; 
	}
    xWriter.Destroy();
    return true;
}