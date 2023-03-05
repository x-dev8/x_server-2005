#include "StageMonitor.h"
#include "BaseCharacter.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "WorkThread.h"
#include "ItemDetail.h"
#include "MonsterBaseEx.h"
#include "Configure.h"
#include "FuncPerformanceLog.h"
#include "NewWithDebug.h"
//#include "MeConnector.h"
#include "DatabaseConnectors.h"
//#include "MeNetwork.h"
#include "FileDB.h"
#include "MeRTLibsServer.h"
#include "network.h"

int g_start_stage = 0;
int g_stage_show = 1;
int g_stage_max = 0;

extern HWND g_hMainWnd;
extern HFONT g_hFont;
extern HWND hwndMsg;
extern HWND hWndSmallMap;
extern CWorkThread gMainThread;
extern HWND   hwndDialogMain;

int g_MonitorMapX = 0;
int g_MonitorMapY = 0;

void UpdateMonitorMonseMapPos( int x, int y )
{
    int X, Y;

    X = x - 24;
    Y = y - 177;
    if( X < 0 || Y < 0 )
        return ;

    g_MonitorMapX = X;
    g_MonitorMapY = Y;
}

void PrintMemoryInfo()
{
    LogMessage::LogCapabilityInfo( "[NetServer�����ܲ�����ʼ]" );
    for (int i = 1; i<(sizeof(usetime)/sizeof(usetime[0])); i++)
    {
        if (usetime[i].szFunctionName != NULL && (usetime[0].nTime/1000) != 0)
        {
            LogMessage::LogCapabilityInfo( "����:%-30s  ռ��ǧ�ֱ�:%d", usetime[i].szFunctionName, usetime[i].nTime/(usetime[0].nTime/1000) );
        }
    }
    //ȫ�����
    memset(&usetime, 0, sizeof(usetime));
    LogMessage::LogCapabilityInfo( "[NetServer�����ܲ�����ֹ]");


    LogMessage::LogCapabilityInfo( "[GameWorld�����ܲ�����ʼ]");
    for (int i = 1; i<(sizeof(gwusetime)/sizeof(gwusetime[0])); i++)
    {
        if (gwusetime[i].szFunctionName != NULL && (gwusetime[0].nTime/1000) != 0)
        {
            LogMessage::LogCapabilityInfo( "����:%-30s  ռ��ǧ�ֱ�:%d", gwusetime[i].szFunctionName, gwusetime[i].nTime/(gwusetime[0].nTime/1000));
        }
    }
    //ȫ�����
    memset(&gwusetime, 0, sizeof(gwusetime));
    LogMessage::LogCapabilityInfo( "[GameWorld�����ܲ�����ֹ]");

    LogMessage::LogCapabilityInfo( "[AICharacterCore�����ܲ�����ʼ]");
    //for (int i = 1; i<(sizeof(aiusetime)/sizeof(aiusetime[0])); i++)
    //{
    //    if (aiusetime[i].szFunctionName != NULL && (aiusetime[0].nTime/1000) != 0)
    //    {
    //        LOG_MESSAGE( CAPABILITYOBJECT, LOG_PRIORITY_INFO, "����:%-30s  ռ��ǧ�ֱ�:%d", aiusetime[i].szFunctionName, aiusetime[i].nTime/(aiusetime[0].nTime/1000));
    //    }
    //}
    ////ȫ�����
    //memset(&aiusetime, 0, sizeof(aiusetime));

    LogMessage::LogCapabilityInfo( "[AICharacterCore�����ܲ�����ֹ]");


    {
        CSALocker locker(GetAutoIntLock());
        LogMessage::LogCapabilityInfo( "[�ѷ����ڴ�ռ�������ʼ]");
        unsigned int nAllMemory = 0;
        for (map<const char*, ALLOCMEMORYINFO>::iterator itr = GetAllocInfo().begin(); itr != GetAllocInfo().end(); itr++)
        {
            nAllMemory += itr->second.nAllUseMemory;
            LogMessage::LogCapabilityInfo( "%-60s ռ���ڴ� [%-15d] �ֽ�, Ŀǰδ�ͷŹ����� [%-10d] ��, ��ʷ����[%-10d]��", itr->first!=NULL?itr->first:"δ������;", itr->second.nAllUseMemory, itr->second.nExistCount, itr->second.nAllocCount );
        }


        LogMessage::LogCapabilityInfo( "ȫ�������ڴ�[%d]Byte [%d]MByte", nAllMemory, nAllMemory/(1024*1024) );
    }    

    //OutHeapMemoryInfoToFile("memory.log");
    //NetworkMemoryDebugInfo().OutMemoryInfoToFile("networkmemory.log");

    LogMessage::LogCapabilityInfo( "[�ѷ����ڴ�ռ�������ֹ]\n" );

	LogMessage::LogCapabilityInfo( "��������ݿ�ʼ:");
	LogMessage::LogCapabilityInfo( "%s",network::net_memory_info());
	LogMessage::LogCapabilityInfo( "��������ݽ���!");
    /*IMeConnector* pCtrl = GetMeNetwork().CreateMeConnector();*/
    /*if (pCtrl != NULL)
    {
        pCtrl->PrintMsgTypeNum();
        pCtrl->Release();
    }*/
}

//void RefreshGameServerMonitor()
//{
//    if( !gMainThread.IsStop() )
//    {   
//        HWND hWnd = g_hMainWnd;
//        RECT rc;
//        //GetClientRect(hWndSmallMap,&rc);
//        std::string strMsg;
//        //HDC hDCDevice = GetDC( hWnd );
//        //HDC hDCDialogMainMap = GetDC(hwndDialogMain);
//        //HDC hDCSmallMap = GetDC(hWndSmallMap);
//
//        //HDC hDCBuffer = CreateCompatibleDC( hDCDevice );
//        //HBITMAP hBitmap = CreateCompatibleBitmap( hDCDevice,rc.right,rc.bottom );
//        //HGDIOBJ hOldBitmap = SelectObject( hDCBuffer,hBitmap );
//
//        //HDC hdc = hDCBuffer;
//
//		if (g_Cfg.bOnlySaveToDBOnExit)
//		{
//			::CheckMenuItem(GetMenu(g_pdialogmain->m_hWnd), ID_ONLYEXITSAVETODB, MF_CHECKED);
//		}
//		else
//		{
//			::CheckMenuItem(GetMenu(g_pdialogmain->m_hWnd), ID_ONLYEXITSAVETODB, MF_UNCHECKED);
//		}
//
//		if (g_Cfg.bDisableChatofWorld)
//		{
//			::CheckMenuItem(GetMenu(g_pdialogmain->m_hWnd), ID_OPTION_DISABLECHATOFWORLD, MF_CHECKED);
//		}
//		else
//		{
//			::CheckMenuItem(GetMenu(g_pdialogmain->m_hWnd), ID_OPTION_DISABLECHATOFWORLD, MF_UNCHECKED);
//		}
//
//		if (g_Cfg.bKickPlayerByCredit)
//		{
//			::CheckMenuItem(GetMenu(g_pdialogmain->m_hWnd), ID_KICKCHAR, MF_CHECKED);
//		}
//		else
//		{
//			::CheckMenuItem(GetMenu(g_pdialogmain->m_hWnd), ID_KICKCHAR, MF_UNCHECKED);
//		}
//
//        char sBuf[ 2048 ] = {0};
//        int RunTime = (HQ_TimeGetTime() - GettheServer().GetStartTime())/1000;
//        int RunMin  = 60;
//        int RunHour = 60 * RunMin;
//        int RunDay = 24 * RunHour;
//        int DayNum = RunTime / RunDay;
//        RunTime -= DayNum * RunDay;
//        int HourNum = RunTime / RunHour;
//        RunTime -= HourNum * RunHour;
//        int MinNum = RunTime / RunMin;
//        RunTime -= MinNum * RunMin;
//
//		_snprintf( sBuf, sizeof(sBuf)-1,
//			"Startup time:%d day %d hour %d minute %d second.\n"
//			"Disposal time:%d. Average time:%d\n"
//			"Open monster AI:%s.\n"
//			"Open PK:%s.\n"
//			"Save data to DB just player offline:%s \n"
//			"Multithreading refresh monsters:%s \n"
//			"Multithreading refresh stages:%s \n"
//			"Kice out player when it speedup:%s \n"
//			"Connection:%d, MaxConnection:%d, SumConnection:%d \n"
//            "AccountServer:%d, DatabaseServer:%d, CenterServer:%d, GateServer:%d \n"
//            "LoginServer:%d, LogServer:%d \n"
//            "Exp:%d%% SkillExp:%d%% \n",
//            DayNum,HourNum,MinNum,RunTime,
//            GettheServer().GetServerElapseTime(),
//            GettheServer().GetServerAvgElapseTime(),
//            (g_Cfg.iAllAIOpen==0)?"No":"Yes",
//			(g_Cfg.bPKOpen==0)?"No":"Yes",
//            (!g_Cfg.bOnlySaveToDBOnExit)?"No":"Yes",
//            (!g_Cfg.bMTRefMonster)?"No":"Yes",
//            (!g_Cfg.bMTStageProc)?"No":"Yes",
//            (!g_Cfg.bKickPlayerByCredit)?"No":"Yes",
//			ShareData::GetDataLog()->dwAllConnecter,
//            ShareData::GetDataLog()->dwMaxOnline,
//			ShareData::GetDataLog()->dwAllOnlineCount,
//			g_bAccountConnectted,
//            g_bDBConnectted,
//            GettheServer().IsCenterServerValidate(),
//            g_iGateNum,
//            g_bLoginConnectted,
//            g_bLogConnectted,
//            ShareData::g_nExpPer,
//            ShareData::g_nSkillExpPer);
//
//        //TextOut( hdc,0,0,sBuf,(int)strlen( sBuf ) );
//        strMsg = sBuf;
//        strMsg += '\n';
//        if(g_iGateNum > 0)
//        {
//            strMsg += "GateServer IP";
//            in_addr addr;
//            for(int i=0;i<g_iGateNum;i++)
//            {
//                if(GettheServer().GetGate(i))
//                {
//                    if(GettheServer().GetGate(i)->GetSocket())
//                    {
//                        if(GettheServer().GetGate(i)->GetSocket()->GetPeerName(addr))
//                        {
//                            _snprintf( sBuf, sizeof(sBuf)-1, " %s ",inet_ntoa(addr));
//                            strMsg += sBuf;
//							_snprintf(sBuf, sizeof(sBuf)-1, "In queue size:%d. Out queue size:%d",
//										GettheServer().GetGate(i)->GetInQueueSize(),
//										GettheServer().GetGate(i)->GetOutQueueSize());
//                            strMsg += sBuf;
//                            strMsg += "\n";
//                        }
//                    }
//                }
//            }
//        }
//
//        //��ȡDatabaseServer������Ϣ
//        if (GettheDBCon().m_conCharDB != NULL && !GettheDBCon().m_conCharDB->IsClosed())
//        {
//            char szBuf[100] = {0};
//            in_addr addr;
//            GettheDBCon().m_conCharDB->GetSocket()->GetPeerName(addr);
//            _snprintf(szBuf, sizeof(szBuf)-1, "DatabaseServer:%s In queue size:%d. Out queue size:%d",
//                inet_ntoa(addr),
//                GettheDBCon().m_conCharDB->GetInQueueSize(),
//                GettheDBCon().m_conCharDB->GetOutQueueSize() );
//            strMsg += szBuf;
//            strMsg += "\n";
//        }
//
//        //��ȡAccountServer������Ϣ
//        if (GettheDBCon().m_AccountServerConnector != NULL && !GettheDBCon().m_AccountServerConnector->IsClosed())
//        {
//            char szBuf[100] = {0};
//            in_addr addr;
//            GettheDBCon().m_AccountServerConnector->GetSocket()->GetPeerName(addr);
//            _snprintf(szBuf, sizeof(szBuf)-1, "AccountServer:%s In queue size:%d. Out queue size:%d",
//                inet_ntoa(addr),
//                GettheDBCon().m_AccountServerConnector->GetInQueueSize(),
//                GettheDBCon().m_AccountServerConnector->GetOutQueueSize() );
//            strMsg += szBuf;
//            strMsg += "\n";
//        }
//
//        //��ȡCenterServer������Ϣ
//        if (GettheServer().IsCenterServerValidate())
//        {
//            char szBuf[100] = {0};
//            _snprintf(szBuf, sizeof(szBuf)-1, "CenterServer:%s In queue size:%d. Out queue size:%d",
//                GettheServer().GetCenterServerConnector().GetClientName().c_str(),
//                GettheServer().GetCenterServerConnector().GetInQueueSize(),
//                GettheServer().GetCenterServerConnector().GetOutQueueSize() );
//            strMsg += szBuf;
//            strMsg += "\n";
//        }
//
//        //��ȡLogServer������Ϣ
//        if (GettheDBCon().m_conLog != NULL && g_bLogConnectted && !GettheDBCon().m_conLog->IsClosed() )
//        {
//            char szBuf[100] = {0};
//            in_addr addr;
//            GettheDBCon().m_conLog->GetSocket()->GetPeerName(addr);
//            _snprintf(szBuf, sizeof(szBuf)-1, "LogServerIP:%s In queue size:%d. Out queue size:%d",
//                inet_ntoa(addr),
//                GettheDBCon().m_conLog->GetInQueueSize(),
//                GettheDBCon().m_conLog->GetOutQueueSize() );
//            strMsg += szBuf;
//            strMsg += "\n";
//        }
//
//        //��ȡLoginserver������Ϣ
//        if (GettheServer().m_pLoginSock != NULL && !GettheServer().m_pLoginSock->IsClosed())
//        {
//            char szBuf[100] = {0};
//            in_addr addr;
//            GettheServer().m_pLoginSock->GetSocket()->GetPeerName(addr);
//			_snprintf(szBuf, sizeof(szBuf)-1, "LoginServer:%s In queue size:%d. Out queue size:%d",
//						inet_ntoa(addr),
//						GettheServer().m_pLoginSock->GetInQueueSize(),
//						GettheServer().m_pLoginSock->GetOutQueueSize() );
//            strMsg += szBuf;
//            strMsg += "\n";
//        }
//
//        char szBuff[100] = {0};
//		_snprintf(szBuff, sizeof(szBuff)-1, "FileDB: Character data been saved failed:%d. SumCharacterNum:%d",
//						GettheFileDB().GetMustSavedCount(),
//						GettheFileDB().GetNoSavedCount() );
//        strMsg += szBuff;
//        strMsg += "\n";
//
//		_snprintf(szBuff, sizeof(szBuff)-1, "YuanBao: unsaved:%d",
//            ::GettheYuanBaoHandle().GetUnSavedMsgCount());
//        strMsg += szBuff;
//        strMsg += "\n";
//
//		_snprintf(szBuff, sizeof(szBuff)-1, "theCharacter Used ID:[%d] Sum ID:[%d]",
//					theRunTimeData.theCharacters.GetUsed(),
//					theRunTimeData.theCharacters.GetSize());
//        strMsg += szBuff;
//        strMsg += "\n";
//
//        int LinePos = 20;
//#define LookTime( TC ) \
//    _snprintf( sBuf, sizeof(sBuf)-1, "%-30s = %08ld", #TC, g_TCMgr.TC.GetTime() ); \
//    LinePos += 20;
//
//        SetWindowText(hwndMsg,strMsg.c_str());
//    }
//}
