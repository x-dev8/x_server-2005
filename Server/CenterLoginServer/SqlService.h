///********************************************************************
//    Filename:    SqlService.h
//    MaintenanceMan Mail: debugcommand@hotmail.com
//	�˽ṹ������ƽ̨�ʺ���֤�Ľ���,ƽ̨�����ʺ���֤�Ժ�
//	CENTER SERVER���ڻ����֤����,���뵽BUFF��,����֤�����Ƿ�Ϸ�
//	BY VVX 2012.11.22
//*********************************************************************/
//
//#ifndef __CENTERSERVER_SQLSERVICE_H__
//#define __CENTERSERVER_SQLSERVICE_H__
//
//#pragma once
//
//#include "MeRTLibsServer.h"
//#include "WorkThread.h"
//#include "mysql++.h"
//#include "Mutex.h"
//#include "CenterGameMessage.h"
//
//
//
//typedef std::list<SqlMessage>         SqlMessageContainer;
//typedef SqlMessageContainer::iterator ItrSqlMessageContainer;
//
//typedef std::map<unsigned int, KickMessage> KickMessageContainer;
//typedef KickMessageContainer::iterator      ItrKickMessageContainer;
//
//class SqlService
//{
//public:
//    enum EServiceStatus
//    {
//        SS_TryConnect,
//        SS_Connected,
//        SS_ReConnected,
//    };
//
//    enum AccountState
//    {
//        AS_Already_Login          = 1, // 1 --- ��½������dbcenter���Դ���
//        AS_Center_Process         = 2, // 2 --- dbcenter�õ�����û�
//        AS_CanLogin_Game          = 3, // 3 --- dbcenter������ϣ�client�˿��Ե�¼��Ϸ������
//        AS_Already_InGame         = 4, // 4 --- �û�����game server��
//        AS_LoginAllowTimeOver     = 5, // 5 --- ��¼����ʱ
//        AS_NotGameServerService   = 6, // 6
//		AS_OfflineStall			  = 7, // 7 --- ���߰�̯
//    };
//
//public:
//    SqlService();
//    ~SqlService();
//    
//    long  RunOnce();
//
//    void  EnableService(); // ��ʼ����
//    bool  IsEnableService(){ return _bEnableService; }
//
//    void  EnableOnlineQueryFlag();
//
//    bool  GetOnlineQueryMessage( SqlMessage& rMessage );
//    bool  GetKickQueryMessage( KickMessage& rMessage, bool isOverTime = false );
//    
//    void  PushResult( const SqlMessage& sqlMessage );
//
//protected:
//    SqlService& operator=( SqlService& ){}
//
//    void _TryConnectToSqlDb(); // ��������sql
//    bool _CheckState();        // ���SqlService�������
//    int  _GetServiceState(){ return _ConnectState; }
//
//    void _ProcessReuslt();
//
//    void _ClearInvalidTableData();   // ���������� ����ϴβ�������
//    bool _GetOnlineQueryFromTable(); // ���OnlineQuery���ݴ�mysql���ݱ�Online
//    bool _GetKickQueryFromTable();   // ���KickQuery���ݴ�mysql���ݱ�kick_table
//
//    void  _CheckKickQueryMessage();
//
//private:
//    int _ConnectState;                   // ���ӵ�״̬
//    mysqlpp::Connection* _pMysqlConnect; // ��mysql ������
//    unsigned long        _LastUpdateTime;
//                       
//    volatile long        _getOnlineQueryFlag; // ȡ����flag
//    SqlMessageContainer  _OnlineQuerys;       // online���ѯ����
//    CSemiAutoIntLock     _OnlineQuerysLock;
//                       
//    KickMessageContainer  _KickQuerys;    // kick���ѯ����
//    CSemiAutoIntLock      _KickQuerysLock;
//                       
//    SqlMessageContainer  _Results;        // �����Ϣ����
//    CSemiAutoIntLock     _ResultsLock;
//                       
//    volatile bool        _bEnableService; // �Ƿ�ʼ����
//    unsigned long        _LastPingTime;
//    bool                 _bHaveClearInvalidData; // �Ƿ������������������
//                       
//public:                
//    bool                 g_bOpenShowSelect;
//    unsigned long        g_OnceTime; // �ӵõ�mysql query���� ������� �ظ�mysql��ʱ�� �����ж��̵߳���Ϣ��׼ȷ����������ν��
//    unsigned long        g_MaxTime;
//};
//
////////////////////////////////////////////////////////////////////////////
//// inline 
//inline void SqlService::EnableOnlineQueryFlag()
//{
//    InterlockedExchange(&_getOnlineQueryFlag, 1);
//}
//
//#endif // __CENTERSERVER_SQLSERVICE_H__
