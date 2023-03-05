#include "SystemVarMessage.h"
#include "NormalLogicWorkThread.h"
#include "MySqlCommunication.h"
#include "zlib/zlib.h"
#include "tstring.h"

void NormalLogicWorkThread::OnLoadSysVarReq( BaseSqlMessage* pSqlMsg )
{// ����ϵͳ����
    static char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

    DB2CSLoadSystemVarAck xAck;
    TRYBEGIN
    {
        sprintf_s( szSql, sizeof(szSql), "select * from systemvar;");
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query(szSql);
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        // ��ȡ���е�buffer�������Ӧ��5000����
        if ( res && !res.empty() )
        {
            for ( int i=0; i<res.num_rows(); ++i)
            {
                uint32 uchServerId = res[i]["serverid"];
                static uint8 bufferDecodeField[ 1024 * 40 ] = {0};
                static uint8 bufferTempUnZip[ 1024 * 40 ] = {0};
                uint32 unZipBufferSize = sizeof( bufferTempUnZip );

                uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[i]["systemvar"].c_str(), bufferDecodeField, sizeof(bufferDecodeField) );
                unZipBufferSize = sizeof(bufferTempUnZip);
                uncompress( bufferTempUnZip, &unZipBufferSize, bufferDecodeField, nDecodeBufferActualSize );

                xAck.xSystemVar.SetServerId(uchServerId);
                memcpy( xAck.xSystemVar.sysVar, bufferTempUnZip, sizeof(bufferTempUnZip) );
                
                theMysqlCommunication.PushAckMessage( &xAck, pSqlMsg->nClientId ); // ÿ��ȡһ��ϵͳ����buffer���ͽ����CS
            }

            mysqlQuery.reset();
        }
    }
    TRYEND
    // ִ��ʧ��
    if ( RESULT_FAILED( result ) )
    { return;}

    DB2CSLoadSysVarSuccess xLoadSuccess;
    theMysqlCommunication.PushAckMessage( &xLoadSuccess, 0 );
}

void NormalLogicWorkThread::OnSaveSysVarReq( BaseSqlMessage* pSqlMsg )
{// ����ϵͳ����
    CS2DBSaveSystemVarReq* pReq = static_cast< CS2DBSaveSystemVarReq * >(pSqlMsg->GetMessageAddress());
    if (pReq == NULL)
    { return;}

    static uint8 bufferTempZip[ DecodeFieldBufferSize ]    = {0};
    static int8 bufferVarsField[ EncodeFieldBufferSize ]   = {0};

    memset( bufferVarsField, 0, EncodeFieldBufferSize );

    uint32 zipBufferSize = ZipTempBufferSize;

    compress( bufferTempZip, (uLongf*)&zipBufferSize, (uint8*)&pReq->xSystemVar.sysVar, sizeof( pReq->xSystemVar.sysVar ) ); // ѹ������
    EnCodeToString( bufferTempZip,bufferVarsField, zipBufferSize, EncodeFieldBufferSize ); // תΪ�ַ���

    char szSql[ 512 ] = { 0 };
    sprintf_s( szSql, sizeof( szSql ) - 1, "select serverid from systemvar where serverid=%d;", pReq->xSystemVar.GetServerId() );

    uint32 result = ER_Success;
    bool bIsExist = false;

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty() )
        { bIsExist = true; }
        mysqlQuery.reset();
    TRYEND

    if ( !bIsExist ) // ������
    {
        memset( szSql, 0, sizeof( szSql ) );
        strncpy_s( szSql, sizeof( szSql ), "insert into systemvar(serverid,systemvar) values(%0,%1q);", sizeof( szSql ) - 1 );

        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned( pReq->xSystemVar.GetServerId() ), bufferVarsField);
            mysqlQuery.reset();
        TRYEND
    }
    else // �Ѿ����ھ͸���
    {
        memset( szSql, 0, sizeof( szSql ) );
        strncpy_s( szSql, sizeof( szSql ), "update systemvar set systemvar=%1q where serverid=%0;", sizeof( szSql ) - 1 );

        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned( pReq->xSystemVar.GetServerId() ), bufferVarsField );
            mysqlQuery.reset();
        TRYEND
    }
    // ����������Ϣ��CS
}