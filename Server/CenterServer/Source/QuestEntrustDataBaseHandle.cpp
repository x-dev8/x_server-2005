#include "NormalLogicWorkThread.h"
#include "zlib/zlib.h"
#include "tstring.h"
#include "MySqlCommunication.h"
#include "QuestEntrust.h"
void NormalLogicWorkThread::OnRequestQuestEntrustDataReq ( BaseSqlMessage* pSqlMessage )
{
	//�������ݿ����ȫ���� ����ί�е�����
	int32 result = ER_Success;
    static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	//���ػʵ۵����ݿ� ����Ϊ���ݿ�
	DBS2CSRequestQuestEntrustDataAck xAck;//ע�� ��С �ִη���
	xAck.ClearAllInfo();
    TRYBEGIN
    {
        sprintf_s( szSql, sizeof( szSql ), "select id,srcplayerid,srcplayername,destplayerid,destplayername,srcquestid,destquestid,rewardtype,rewardsum,issucce,receiveLogTime,info from questentrust;" );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();      
		if ( res && !res.empty())
        {
			//�ֶη���
			for ( int i = 0; i < res.num_rows(); ++i )
            {
				QuestEntrustStates info;
				info.ID = res[i]["id"];
				info.SrcPlayerID = res[i]["srcplayerid"];

				strcpy_s(info.ScrPlayerName,MaxPlayerNameLength,res[i]["srcplayername"].c_str());
				WCHAR wstr[MaxPlayerNameLength];
				MultiByteToWideChar(CP_UTF8,0,info.ScrPlayerName,MaxPlayerNameLength,wstr,MaxPlayerNameLength);
				strcpy_s(info.ScrPlayerName,MaxPlayerNameLength,_tANSICHAR(wstr));

				info.DestPlayerID = res[i]["destplayerid"];
				
				strcpy_s(info.DestPlayerName,MaxPlayerNameLength,res[i]["destplayername"].c_str());
				MultiByteToWideChar(CP_UTF8,0,info.DestPlayerName,MaxPlayerNameLength,wstr,MaxPlayerNameLength);
				strcpy_s(info.DestPlayerName,MaxPlayerNameLength,_tANSICHAR(wstr));

				info.SrcQuestID = res[i]["srcquestid"];
				info.DestQuestID = res[i]["destquestid"];
				info.EntrustRewardType = res[i]["rewardtype"];
				info.EntrustRewardSum = res[i]["rewardsum"];
				info.IsSecc = res[i]["issucce"];

				mysqlpp::DateTime xLogTime = res[i]["receiveLogTime"];		
				info.ReceiveLogTime = xLogTime.operator time_t();
				//��ȡ�����ƿ�
				static char tempDecodeBufferBaseinfo[1024*100] = {0};
				int nDecodeBufferActualSize = DeCodeFromString((const unsigned char*)(res[i]["info"].c_str()), tempDecodeBufferBaseinfo, sizeof(tempDecodeBufferBaseinfo));
				static uint8 uncompressBufffer[1024*256] = {0};            
				uint32 uncompressBufferSize = 1024*256;
				uncompress( uncompressBufffer, &uncompressBufferSize, (uint8*)tempDecodeBufferBaseinfo,  nDecodeBufferActualSize);
				ReadQuestEntrustByteData(uncompressBufffer,uncompressBufferSize,info.ItemInfo);
				//���ݶ�ȡ��Ϻ� ������֯����
				if(xAck.PushInfo(info,(i == res.num_rows() -1)))
				{
					theMysqlCommunication.PushAckMessage( &xAck, pSqlMessage->nClientId );
					xAck.ClearAllInfo();
				}
			}
        }
		else
		{
			//����Ϊ��
			xAck.Sum = 0;
			xAck.IsEnd = true;
			xAck.SetLength();
			theMysqlCommunication.PushAckMessage( &xAck, pSqlMessage->nClientId );
		}
        mysqlQuery.reset();
    }
    TRYEND
    // ִ��ʧ��
    if ( RESULT_FAILED( result ) )
    { return; }
}
void NormalLogicWorkThread::ReadQuestEntrustByteData(BYTE* bybuff,DWORD dwsize,SCharItem& info)
{
	CDataChunkLoader l(bybuff,dwsize);
	while( !l.IsEndOfMemory() )
	{
		if( l.IsChunk('inf1'))
		{
			l.StartChunk( 'inf1' );            
			CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
			{
				r.ReadToBuffer((BYTE*)&info,sizeof(SCharItem));
			}
			l.EndChunk('inf1');
		}
		else 
		{
			l.SkipChunk(); 
		}
	}
}
bool NormalLogicWorkThread::WriteQuestEntrustByteData(uint8* pOutBuffer,uint32 outBufferSize,SCharItem& info,uint32& nActualSize)
{
	CDataChunkWriter xWriter( pOutBuffer, outBufferSize );
	xWriter.StartChunk(DC_TAG('inf1'));
    xWriter.Write ( &info, sizeof(SCharItem), 1);
    xWriter.EndChunk(DC_TAG('inf1'));
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
void NormalLogicWorkThread::OnAddQuestEntrustDataReq( BaseSqlMessage* pSqlMessage )
{
	//�����ݿ�������µ�����ί��
	CS2DBAddQuestEntrustDataAck * p= static_cast< CS2DBAddQuestEntrustDataAck* >( pSqlMessage->GetMessageAddress() );
	for(int i =0;i<p->Sum;++i)
	{
		QuestEntrustStates* info = &p->List[i];
		static char szSql[ 1024 ] = {0};
		memset( szSql, 0, sizeof(szSql) );
		uint32 result = ER_Success;

		static uint8 bufferItemDataChunk[ 1024 * 256 ] = { 0 };
		static uint8 bufferTempZipItem  [ 1024 * 256 ] = { 0 };
		static int8  bufferItemDataField[ 1024 * 256 ] = { 0 };
		uint32 zipBufferSize = sizeof( bufferTempZipItem );
		uint32 nActualSize = 0;
		//�����ɶ����ƿ�
		if ( !WriteQuestEntrustByteData(bufferItemDataChunk,sizeof( bufferItemDataChunk),info->ItemInfo,nActualSize))
		{ 
			continue; 
		}
		compress( bufferTempZipItem,( uLongf* )&zipBufferSize, bufferItemDataChunk, nActualSize ); // ѹ������
		EnCodeToString( bufferTempZipItem, bufferItemDataField, zipBufferSize, sizeof( bufferItemDataField ));


		TRYBEGIN
		{
			// �����µ�
			mysqlpp::DateTime xLogTime(info->ReceiveLogTime);
			string TimeStr = xLogTime.str();
			sprintf_s( szSql, sizeof( szSql ) - 1, "insert into questentrust(id,srcplayerid,srcplayername,destplayerid,destplayername,srcquestid,destquestid,rewardtype,rewardsum,issucce,receiveLogTime,info,InsertTime) values(%d,%d,'%s',%d,'%s',%d,%d,%d,%d,%d,'%s','%s',now());",
				info->ID,info->SrcPlayerID,_tUTF8CHAR(info->ScrPlayerName),info->DestPlayerID,_tUTF8CHAR(info->DestPlayerName),info->SrcQuestID,info->DestQuestID,info->EntrustRewardType,info->EntrustRewardSum,info->IsSecc,TimeStr.c_str(),bufferItemDataField);
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
			mysqlpp::StoreQueryResult res = mysqlQuery.store();
		}
		TRYEND

		// ִ��ʧ��
		if ( RESULT_FAILED( result ) )
		{ continue; }
	}
}
void NormalLogicWorkThread::OnDelQuestEntrustDataReq(BaseSqlMessage* pSqlMessage )
{
	//ɾ��ָ��������ί��
	CS2DBQuestEntrustDeleteReq * p = static_cast< CS2DBQuestEntrustDeleteReq* >( pSqlMessage->GetMessageAddress() );
	for(int i =0;i<p->Sum;++i)
	{
		unsigned int ID = p->List[i];
		static char szSql[ 1024 ] = {0};
		memset( szSql, 0, sizeof(szSql) );
		uint32 result = ER_Success;
		TRYBEGIN
		{
			// �����µ�
			sprintf_s( szSql, sizeof( szSql ) - 1, "delete from questentrust where id=%d;",ID);
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
			mysqlpp::StoreQueryResult res = mysqlQuery.store();
		}
		TRYEND
		// ִ��ʧ��
		if ( RESULT_FAILED( result ) )
		{ continue; }
	}
}
void NormalLogicWorkThread::OnUpdateQuestEntrustDataReq(BaseSqlMessage* pSqlMessage )
{
	//��ָ��ID�����ݽ���Update����
	CS2DBQuestEntrustDataSaveReq * p = static_cast< CS2DBQuestEntrustDataSaveReq* >( pSqlMessage->GetMessageAddress() );
	for(int i =0;i<p->Sum;++i)
	{
		QuestEntrustStates* info = &p->List[i];
		static char szSql[ 1024 ] = {0};
		memset( szSql, 0, sizeof(szSql) );
		uint32 result = ER_Success;
		TRYBEGIN
		{
			// �����µ�
			mysqlpp::DateTime xLogTime(info->ReceiveLogTime);
			string TimeStr = xLogTime.str();
			sprintf_s( szSql, sizeof( szSql ) - 1, "update questentrust set destplayerid=%d,destplayername='%s',issucce=%d,receiveLogTime='%s' where id=%d;",
				info->DestPlayerID,_tUTF8CHAR(info->DestPlayerName),info->IsSecc,TimeStr.c_str(),info->ID);
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
			mysqlpp::StoreQueryResult res = mysqlQuery.store();
		}
		TRYEND
		// ִ��ʧ��
		if ( RESULT_FAILED( result ) )
		{ continue; }
	}
}
