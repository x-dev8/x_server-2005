/********************************************************************
	Filename: 	YuanBaoHandle.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef _H_YUANBAO_HANDLE_
#define _H_YUANBAO_HANDLE_

#include "MeRTLibsServer.h"
#include "DatabaseConnectors.h"
#include "DBMessageDefine.h"

class CYuanBaoHandle
{
public:
    typedef struct tagYuanBaoInfo
    {
        __int64 ItemGUID;
        int ItemID;
        bool bUsed;
    }YUANBAOINFO;

    typedef struct tagUnSaveMsgInfo
    {
        DWORD dwTime;
        DBMsgReqAccountBillingOp msg;
    }UNSAVEMSGINFO;

public:
    CYuanBaoHandle();
    virtual ~CYuanBaoHandle();

    bool SendToDBInfo();
    void OnDBMsg(DBAckOperSucc* pMsg);
    void OnDBMsg(DBMsgAckAccountBilling* pMsg);

	INT	 GetYuanBaoCnt( DWORD dwAccID );
    bool GetYuanBao(DWORD dwAccID, YUANBAOINFO& info);   // 获取元宝信息
    bool DelYuanBao(DWORD dwAccID, YUANBAOINFO info);    // 从账号中删除元宝信息
    bool UpdateYuanBao(DWORD dwAccID, YUANBAOINFO info); // 元宝提交到网站上
    uint32 GetUnSavedMsgCount(){ return (uint32 )m_msglist.size(); }
    void   Log(const char *pszLog, ...);

protected:
    std::map<DWORD, map<__int64, YUANBAOINFO> > m_unusedlist; // 未领取的元宝（需要领取的元宝会存在于此列表中）
    std::map<__int64, YUANBAOINFO> m_usedlist;                // 已经使用过的元宝
    std::map<unsigned int, UNSAVEMSGINFO> m_msglist;

private:
    DWORD m_dwLastSendReqTime;
};

extern CYuanBaoHandle& GettheYuanBaoHandle();

#endif //_H_YUANBAO_HANDLE_
