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
    bool GetYuanBao(DWORD dwAccID, YUANBAOINFO& info);   // ��ȡԪ����Ϣ
    bool DelYuanBao(DWORD dwAccID, YUANBAOINFO info);    // ���˺���ɾ��Ԫ����Ϣ
    bool UpdateYuanBao(DWORD dwAccID, YUANBAOINFO info); // Ԫ���ύ����վ��
    uint32 GetUnSavedMsgCount(){ return (uint32 )m_msglist.size(); }
    void   Log(const char *pszLog, ...);

protected:
    std::map<DWORD, map<__int64, YUANBAOINFO> > m_unusedlist; // δ��ȡ��Ԫ������Ҫ��ȡ��Ԫ��������ڴ��б��У�
    std::map<__int64, YUANBAOINFO> m_usedlist;                // �Ѿ�ʹ�ù���Ԫ��
    std::map<unsigned int, UNSAVEMSGINFO> m_msglist;

private:
    DWORD m_dwLastSendReqTime;
};

extern CYuanBaoHandle& GettheYuanBaoHandle();

#endif //_H_YUANBAO_HANDLE_
