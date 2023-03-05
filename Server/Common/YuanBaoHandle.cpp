#include "YuanBaoHandle.h"
#include "CRC32.h"
#include "helper.h"
#include "XmlStringLanguage.h"

#define REFRESH_YUANBAOINFO_TIME 1000 * 60 * 1  //1分钟请求刷新一次元宝

CYuanBaoHandle& GettheYuanBaoHandle()
{
    static CYuanBaoHandle s_thehandle;
    return s_thehandle;
}
using std::map;

CYuanBaoHandle::CYuanBaoHandle():m_dwLastSendReqTime(0)
{
}

CYuanBaoHandle::~CYuanBaoHandle()
{
}


bool CYuanBaoHandle::SendToDBInfo()
{ // 判断元宝是否发送消息到数据库
    if (HQ_TimeGetTime() - m_dwLastSendReqTime >= REFRESH_YUANBAOINFO_TIME)
    {
        DBMsgReqAccountBilling msg;
        GettheDBCon().SendMsgToDatabaseServer(&msg);
        m_dwLastSendReqTime = HQ_TimeGetTime();

        for (map<unsigned int, UNSAVEMSGINFO>::iterator itr = m_msglist.begin();
            itr != m_msglist.end();
            itr ++)
        {
            if (HQ_TimeGetTime() - itr->second.dwTime >= REFRESH_YUANBAOINFO_TIME)
            {
                DBMsgReqAccountBillingOp msg = itr->second.msg;
                ::GettheDBCon().SendMsgToDatabaseServer(&msg);
                itr->second.dwTime = HQ_TimeGetTime();
            }
        }
    }
    return true;
}

void CYuanBaoHandle::OnDBMsg(DBAckOperSucc* pMsg)
{
    if (pMsg->dwMsgType == DBMSG_REQ_ACCOUNT_BILLING_OP)
    {
        unsigned int nMsgID = pMsg->dwMsgID;
        map<unsigned int, UNSAVEMSGINFO>::iterator itr = m_msglist.find(nMsgID);
        if (itr != m_msglist.end())
        {
            m_msglist.erase(itr);
        }
    }
}

void CYuanBaoHandle::OnDBMsg( DBMsgAckAccountBilling* pMsg)
{
    //if (pMsg == NULL)
    //{ return; }

    //for (int i=0; i<pMsg->nNum; i++)
    //{
    //    if (pMsg->info[i].bIsUsed)
    //    {
    //        YUANBAOINFO info;
    //        info.ItemGUID = pMsg->info[i].GUID;
    //        info.ItemID = pMsg->info[i].ItemID;
    //        info.bUsed = pMsg->info[i].bIsUsed;
    //        m_usedlist[pMsg->info[i].AccID] = info;
    //    }
    //    else
    //    {
    //        //如果数据库里标为未使用但游戏中却标记为使用了，则以游戏为准，不予理会数据库
    //        map<__int64, YUANBAOINFO>::iterator itr = m_usedlist.find(pMsg->info[i].GUID);
    //        if (itr != m_usedlist.end())
    //        {
    //            continue;
    //        }
    //        else
    //        {
    //            map<DWORD, map<__int64, YUANBAOINFO> >::iterator it = m_unusedlist.find(pMsg->info[i].AccID);
    //            if (it == m_unusedlist.end())
    //            {
    //                m_unusedlist.insert(std::pair<DWORD, map<__int64, YUANBAOINFO> >(pMsg->info[i].AccID, map<__int64, YUANBAOINFO>()));
    //            }

    //            map<__int64, YUANBAOINFO>& secondindex = m_unusedlist.find(pMsg->info[i].AccID)->second;
    //            
    //            YUANBAOINFO info;
    //            info.ItemGUID = pMsg->info[i].GUID;
    //            info.ItemID = pMsg->info[i].ItemID;
    //            info.bUsed = pMsg->info[i].bIsUsed;
    //            secondindex[pMsg->info[i].GUID] = info;
    //        }
    //    }
    //}
}

INT	 CYuanBaoHandle::GetYuanBaoCnt( DWORD dwAccID )
{
    map<DWORD, map<__int64, YUANBAOINFO> >::iterator itr = m_unusedlist.find(dwAccID);
    if (itr == m_unusedlist.end())
    {
        return 0;
    }

    map<__int64, YUANBAOINFO>& secondindex = itr->second;

    return secondindex.size();
}

bool CYuanBaoHandle::GetYuanBao(DWORD dwAccID, YUANBAOINFO& info)
{
    map<DWORD, map<__int64, YUANBAOINFO> >::iterator itr = m_unusedlist.find(dwAccID);
    if (itr == m_unusedlist.end())
    {
        return false;
    }

    map<__int64, YUANBAOINFO>& secondindex = itr->second;
    if (secondindex.empty())
    {
        return false;
    }

    map<__int64, YUANBAOINFO>::iterator seconditr = secondindex.begin();
    info = seconditr->second;
    return true;
}

bool CYuanBaoHandle::DelYuanBao(DWORD dwAccID, YUANBAOINFO info)
{
    //map<DWORD, map<__int64, YUANBAOINFO> >::iterator itr = m_unusedlist.find(dwAccID);
    //if (itr == m_unusedlist.end())
    //{
    //    return false;
    //}

    //map<__int64, YUANBAOINFO>& secondindex = itr->second;
    //map<__int64, YUANBAOINFO>::iterator seconditr = secondindex.find(info.ItemGUID);
    //if (seconditr != secondindex.end())
    //{
    //    secondindex.erase(seconditr);

    //    info.bUsed = true;
    //    m_usedlist[info.ItemGUID] = info;

    //    char szGUID[40];
    //    Log(theXmlString.GetString(eLog_info_2slk_27), dwAccID, ::BigInt2String(info.ItemGUID, szGUID), info.ItemID);

    //    DBMsgReqAccountBillingOp msg;
    //    msg.GUID = info.ItemGUID;
    //    msg.ItemID = info.ItemID;
    //    msg.AccountID = dwAccID;
    //    msg.nState = DBMsgReqAccountBillingOp::USED;

    //    //将这条消息的CRC32值作为DBMSGID，减少ID重复机率
    //    Crypto::CCRC32 crc32;
    //    msg.dwDBMSGID = crc32.GetMemCRC32(reinterpret_cast<const unsigned char*>(&msg), sizeof(msg));

    //    ::GettheDBCon().SendMsgToDatabaseServer(&msg);

    //    UNSAVEMSGINFO unsavemsginfo;
    //    unsavemsginfo.dwTime = timeGetTime();
    //    unsavemsginfo.msg = msg;
    //    m_msglist[msg.dwDBMSGID] = unsavemsginfo;
    //    return true;
    //}
    return false;
}

bool CYuanBaoHandle::UpdateYuanBao(DWORD dwAccID, YUANBAOINFO info)
{
    //DBMsgReqAccountBillingOp msg;
    //msg.GUID = info.ItemGUID;
    //msg.ItemID = info.ItemID;
    //msg.AccountID = dwAccID;
    //msg.nState = DBMsgReqAccountBillingOp::TOWEB;

    //char szGUID[40];
    //Log(theXmlString.GetString(eLog_info_2slk_28), dwAccID, ::BigInt2String(info.ItemGUID, szGUID), info.ItemID);

    ////将这条消息的CRC32值作为DBMSGID，减少ID重复机率
    //Crypto::CCRC32 crc32;
    //msg.dwDBMSGID = crc32.GetMemCRC32(reinterpret_cast<const unsigned char*>(&msg), sizeof(msg));

    //::GettheDBCon().SendMsgToDatabaseServer(&msg);

    ////添加到未保存列表
    //UNSAVEMSGINFO unsavemsginfo;
    //unsavemsginfo.dwTime = timeGetTime();
    //unsavemsginfo.msg = msg;
    //m_msglist[msg.dwDBMSGID] = unsavemsginfo;

    return true;
}

void CYuanBaoHandle::Log(const char *pszLog, ...)
{
    if(pszLog == NULL)
    {
        return;
    }
    char szDate[256] = {0};
    char szTime[256] = {0};
    char szBuf[1024] = {0};
    char szLog[1024] = {0};

    SYSTEMTIME systime;
    GetLocalTime( &systime );

    _snprintf(szDate, sizeof(szDate)-1, "%04d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
    _snprintf(szTime, sizeof(szTime)-1, "%02d:%02d:%02d", systime.wHour, systime.wMinute, systime.wSecond);

    //转换参数
    va_list vl;
    va_start(vl, pszLog);
    int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, pszLog, vl);
    va_end(vl);

    _snprintf(szLog, sizeof(szLog)-1, "%s %s: %s\n", szDate, szTime, szBuf);


    char szFile[MAX_PATH] = {0};
    _mkdir("YuanBaoLog");
    _snprintf(szFile, sizeof(szFile)-1, "YuanBaoLog\\YuanBao[%s].log", szDate);
    FILE* fLog = NULL;
    fLog = fopen(szFile, "at");
    if(fLog != NULL)
    {
        fwrite(szLog, strlen(szLog), 1, fLog);
        fclose(fLog);
    }
}