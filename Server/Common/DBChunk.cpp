#include "DBChunk.h"

#include "Configure.h"
#include "DataChunkMgr.h"
#include "zlib/zlib.h"
#include "ResourcePath.h"

//#pragma comment(lib, "Zlib/lib/zdll.lib")

CDBChunk g_dbchunk;

using DataBase::CConnection;
using DataBase::CRecordset;
using std::string;
using std::vector;

//��־�������
//void DebugLogMsg(const char* szText)
//{
//	char szDate[256] = {0};
//	char szTime[256] = {0};
//	char szLog[1024] = {0};
//
//	SYSTEMTIME systime;
//	GetLocalTime( &systime );
//	_snprintf(szDate, sizeof(szDate)-1, "%04d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);	
//
//    // ��һ��
//    _mkdir(OUTPUT_DIRECTORY);
//
//    // �ڶ��� MsSqllogĿ¼
//    char szPath[MAX_PATH] = {0};
//    _snprintf(szPath, sizeof(szPath)-1, MSSQL_LOGDIRECTORY_FORMAT, OUTPUT_DIRECTORY);
//	_mkdir(szPath);
//
//    // ������ ����Ŀ¼
//    char szLogFolder[MAX_PATH] = {0};
//    memset( szLogFolder, 0, MAX_PATH);
//    _snprintf(szLogFolder, MAX_PATH-1, "%s\\%s", szPath, szDate);
//    _mkdir(szLogFolder);
//
//    // ���ļ� �ļ�
//    char szFile[MAX_PATH] = {0};
//    _snprintf(szFile, MAX_PATH-1, "%s\\%02d.log", szLogFolder, systime.wHour);
//
//	std::ofstream fLog(szFile, std::ios::app);
//
//	if(!fLog.is_open())
//		return;
//
//	fLog << szDate << " " << szTime << "    " << szText << std::endl;
//	fLog.close();
//}

static unsigned char Decode6BitMask[5] = { 0xfc, 0xf8, 0xf0, 0xe0, 0xc0 };

//���뺯�������ڶ������������ݱ���ɿ����ַ����������ݿ�洢��
// pDec : ��ű��������ִ���ַ
// pSrc : ��Ҫ���б���Ķ�������ֵ��ַ
// ����ֵ: ��������pDec�ִ�����
int EnCodeToString(const unsigned char *pszSrc, char *pszDest, size_t nSrcLen, size_t nDestLen)
{
	int				nDestPos	= 0;
	int				nRestCount	= 0;
	unsigned char	chMade = 0, chRest = 0;

	for (int i = 0; i < nSrcLen; i++)
	{
		if (nDestPos >= nDestLen) break;
		
		chMade = ((chRest | (pszSrc[i] >> (2 + nRestCount))) & 0x3f);
		chRest = (((pszSrc[i] << (8 - (2 + nRestCount))) >> 2) & 0x3f);

		nRestCount += 2;

		if (nRestCount < 6)
			pszDest[nDestPos++] = chMade + 0x3c;
		else
		{
			if (nDestPos < nDestLen - 1)
			{
				pszDest[nDestPos++]	= chMade + 0x3c;
				pszDest[nDestPos++]	= chRest + 0x3c;
			}
			else
				pszDest[nDestPos++] = chMade + 0x3c;

			nRestCount	= 0;
			chRest		= 0;
		}
	}

	if (nRestCount > 0)
		pszDest[nDestPos++] = chRest + 0x3c;

	pszDest[nDestPos] = '\0';

	return nDestPos;
}

//���뺯�������ڴ����ݿ�����������ַ�����ԭ�ɶ������������ݣ�
// pDec : ��Ž������Ķ�������ֵ��ַ
// pSrc : ��Ҫ���н�����ַ�����ַ
// ����ֵ: ��������pDec��������ֵ����
int DeCodeFromString(const uint8* pszSrc, char *pszDest, size_t nDestLen)
{
	int				nLen = strlen((const char *)pszSrc);
	int				nDestPos = 0, nBitPos = 2;
	int				nMadeBit = 0;
	unsigned char	ch, chCode, tmp;

	for (int i = 0; i < nLen; i++)
	{
		if ((pszSrc[i] - 0x3c) >= 0)
			ch = pszSrc[i] - 0x3c;
		else
		{
			nDestPos = 0;
			break;
		}

		if (nDestPos >= nDestLen) break;

		if ((nMadeBit + 6) >= 8)
		{
			chCode = (tmp | ((ch & 0x3f) >> (6 - nBitPos)));
			pszDest[nDestPos++] = chCode;

			nMadeBit = 0;

			if (nBitPos < 6) 
				nBitPos += 2;
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



CDBChunk::CDBChunk(void)
{
    DataBase::CDebugOutPut::SetErrorOut(NULL);
    DataBase::CDebugOutPut::SetLogOut(NULL);
}

CDBChunk::~CDBChunk(void)
{
}

bool CDBChunk::ConnectDB()
{
    return m_pConn.Open(g_Cfg.szDBIP, g_Cfg.szDBName, g_Cfg.szDBUser, g_Cfg.szDBPwd);
}

bool CDBChunk::AsynConnectDB()
{
    return m_pConn.Open(g_Cfg.szDBIP, g_Cfg.szDBName, g_Cfg.szDBUser, g_Cfg.szDBPwd, true);
}

void CDBChunk::SaveOnlineInfoToDB(unsigned int nOnlineNum)
{
    if (!m_pConn.IsOpen())
    {   
        AsynConnectDB();
        return;
    }

    char szSQL[1024] = {0};
    _snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO t_Online_Info (Online, DateTime) VALUES ("
            "%d, GETDATE())", nOnlineNum);

    m_pConn.Execute(szSQL);

}

bool CDBChunk::LoadChunkMgrDataFromDB()
{
    if (!m_pConn.IsOpen())
    {
        return false;
    }
    
    char szSQL[1024] = {0};
    _snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM t_server_Info WHERE ServerName = '%s'", g_Cfg.szGameServerName);
    CRecordset pRec = m_pConn.Execute(szSQL);

    if (!pRec.IsOpen())
    {
        return false;
    }

    vector<unsigned char> chunkdata;
    while (!pRec.IsEOF())
    {
        //���ݶ�
        unsigned int nSegmentIndex = atoi(pRec.Get("SegmentIndex"));
        
        //���chunkdata�Ĵ�С�������������ݣ�������chunkdata
        if ((nSegmentIndex+1)*3000 > chunkdata.size())
        {
            //����resize��ԭ�����ݲ��������
            chunkdata.resize((nSegmentIndex+1)*3000);
        }

        //��Ϊ����ȫ��Ϊ�ַ����������ʹ��strncpy������memcpy���и���
        strncpy((char*)&chunkdata[nSegmentIndex*3000], pRec.Get("DataSegment"), 3000-1); 
        pRec.MoveNext();
    }

    //�������1M�ռ�洢Chunk��ѹ���������;
    //ʹ��staticʹ֮�洢��������ɶ�ջ���
    static unsigned char bBuffer[1024*1024];
    static unsigned char bUnCompressBuffer[1024*1024];

    memset(bBuffer, 0, sizeof(bBuffer));
    memset(bUnCompressBuffer, 0, sizeof(bUnCompressBuffer));

    //�����ݿ��ж�����ֵ������������

	if (chunkdata.empty())
	{
		return true;
	}
    unsigned int nDecodeSize = DeCodeFromString((unsigned char*)&chunkdata[0], (char*)bBuffer, sizeof(bBuffer));
    unsigned int uncompresssize = sizeof(bUnCompressBuffer);
    uncompress((unsigned char*)&bUnCompressBuffer, (uLongf*)&uncompresssize, bBuffer, nDecodeSize);
    //
    //nDecodeSize = DeCodeFromString((const unsigned char*)(pRec.Get("OtherData")), szBuff, sizeof(szBuff));
    //structsize = sizeof(ack.charinfo.otherdata);
    //uncompress((unsigned char*)&ack.charinfo.otherdata, (uLongf*)&structsize, (unsigned char*)szBuff, nDecodeSize);

    CDataChunkMgr* pMgr = GetDataChunkMgr();
    pMgr->LoadFromMemory(bUnCompressBuffer, uncompresssize);
    return true;
}

bool CDBChunk::SaveChunkMgrDataToDB()
{
    CDataChunkMgr* pMgr = GetDataChunkMgr();

    //�������1M�ռ�洢Chunk��ѹ���������;
    //ʹ��staticʹ֮�洢��������ɶ�ջ���
    static unsigned char bBuffer[1024*1024];
    static unsigned char bCompressBuffer[1024*1024];
    
    memset(bBuffer, 0, sizeof(bBuffer));

    unsigned int size = sizeof(bBuffer);
    pMgr->SaveToMemory(bBuffer, size);

    memset(bCompressBuffer, 0, sizeof(bCompressBuffer));

//    memcpy(bBuffer, (void*)0x400000, sizeof(bBuffer));
    unsigned int compresssize = sizeof(bCompressBuffer);
    //ѹ������
    compress(bCompressBuffer, (uLongf*)&compresssize, bBuffer, size);
    memset(bBuffer, 0, sizeof(bBuffer));

    //תΪ�����ַ���
    unsigned int nEncodesize = EnCodeToString(bCompressBuffer, (char*)bBuffer, compresssize, sizeof(bBuffer));

    if (nEncodesize == 0)
    {
        return false;
    }

    static char szSegment[3001] = {0};
    static char szSQL[4000] = {0};
    
    memset(szSQL, 0, sizeof(szSQL));

    //���������ݿ��е�����ȫ�����
    _snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM t_server_Info WHERE ServerName = '%s'", g_Cfg.szGameServerName);
    CRecordset pRec = m_pConn.Execute(szSQL);
    if (!pRec.IsOpen())
    {
        return false;
    }
    unsigned int nSegmentIndex = 0;
    while (nEncodesize != 0)
    {
        memset(szSegment, 0, sizeof(szSegment));
        memset(szSQL, 0, sizeof(szSQL));
        strncpy(szSegment, (char*)&bBuffer[nSegmentIndex*3000], 3000-1);
        _snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO t_server_Info (ServerName, SegmentIndex, DataSegment) VALUES ("
            "'%s', %d, '%s')", g_Cfg.szGameServerName, nSegmentIndex, szSegment);

        m_pConn.Execute(szSQL);

        if (nEncodesize < 3000)
        {
            nEncodesize = 0;
        }
        else
        {
            nEncodesize -= 3000;
        }
        nSegmentIndex++;
    }

    return true;
}

bool CDBChunk::SaveUserInfo(const char* szUser, const char* szLog)
{
    if (szUser == NULL || szLog == NULL)
    {
        return false;
    }

    static char szSQL[1024] = {0};
    _snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO t_User_Info (UserName, UserLog) VALUES ('%s', '%s')", szUser, szLog);
    CRecordset pRec = m_pConn.Execute(szSQL);

    if (!pRec.IsOpen())
    {
        return false;
    }

    return true;

}