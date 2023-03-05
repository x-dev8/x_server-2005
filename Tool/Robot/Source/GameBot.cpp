// GameBot.cpp : 定义应用程序的类行为

#include "stdafx.h"
//#include "NetworkNode.h"
#include "BaseInfo.h"
#include "MainFrm.h"
//#include "MeNetwork.h"
#include "GameBotDoc.h"
#include "AttackBot.h"
#include "NormalBot.h"
#include "FightBot.h"
#include "GameBotView.h"
#include "GameDefineBot.h"
//#include "GuildBot.h"
#include "IdleBot.h"
#include "TeamBot.h"
#include "EctypeBot.h"
#include "DromeBot.h"
#include "LoginBot.h"
#include "MeRTLibsServer.h"
#include "StageDataLoader.h"
#include "NpcInfo.h"
#include "application_config.h"
#include "GameTimer.h"
#include "license.h"

#pragma warning ( push )
#pragma warning ( disable : 4005 )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int g_nTotalMsgNum = 0;
int g_nTotalPosPack = 0;
int g_nTotalPosMsg = 0;
int g_nTotalSightPack = 0;
int g_nTotalSightMsg = 0;
int g_nLoopTime = 0;
int g_nLoginOnly = 0;
int g_nReLogin = 0;
int g_nDisableCheckTime = 1;

inline std::string GetMonsterDataFilePath( const std::string& stageName )
{
    std::string strFilePath = STAGEROOTDIRECTORY;
    strFilePath += "\\";
    strFilePath += stageName;
    strFilePath += "\\";
    strFilePath += stageName;
    strFilePath += MONSTERCONFIG_FILEPATH;
    return strFilePath;
}
#define MAPPINGBUFFSIZE  (4)

// CGameBotApp
BEGIN_MESSAGE_MAP(CGameBotApp, CWinApp)
    ON_COMMAND(ID_APP_ABOUT, &CGameBotApp::OnAppAbout)
    ON_COMMAND(ID_APP_LOG, &CGameBotApp::NetworkMsgLog)
    // 基于文件的标准文档命令
    ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()

// CGameBotApp 构造

CGameBotApp::CGameBotApp()
{
    // TODO: 在此处添加构造代码，
    // 将所有重要的初始化放置在 InitInstance 中	
    bAttack = false;
    pMappingBuf = NULL;
    _firstShow = true;
}


// 唯一的一个 CGameBotApp 对象

CGameBotApp theApp;

int CGameBotApp::LoadFileMappingNum()
{
    if (hMapFile == NULL || hMapFile == INVALID_HANDLE_VALUE)
    {
        return -1;
    }
    pMappingBuf = (LPTSTR) MapViewOfFile( hMapFile,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0, MAPPINGBUFFSIZE); 
    if (pMappingBuf == NULL) 
    {
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Could not map view of file (%d).\n", GetLastError()); 
        return -1;
    }
    int TotalBotNum;

    memcpy_s((void*)&TotalBotNum,sizeof(TotalBotNum),pMappingBuf,sizeof(TotalBotNum));

    UnmapViewOfFile(pMappingBuf);

    return TotalBotNum;
}

int CGameBotApp::Run()
{ return CWinApp::Run(); }

bool CGameBotApp::WriteFileMappingNum(int Num)
{
    if (hMapFile == NULL || hMapFile == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    pMappingBuf = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        MAPPINGBUFFSIZE);

    if (pMappingBuf == NULL) 
    { 
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Could not map view of file (%d).\n", 
            GetLastError()); 
        return false;
    }
    memcpy_s((void*)pMappingBuf,sizeof(Num),(void*)&Num,sizeof(Num));
    UnmapViewOfFile(pMappingBuf);
    return true;
}

BOOL CGameBotApp::OnIdle(LONG lCount)
{
    if ( _firstShow )
    {
        ShowServerInfo();
        _firstShow = false;
    }
    // 处理logic线程消息
    ProcessLogicMessage();
        
    return TRUE;
}
// CGameBotApp 初始化

void MainLogicThreadFunc( void* lpVoid )
{
    BotApplication* pLogicApp = (BotApplication*)lpVoid;
    switch ( pLogicApp->GetAppState())
    {
    case BotApplication::EAppStateType_Init:
        { 
            if ( pLogicApp->Init("") != ER_Success)
            {
                string strLog("初始化文件失败，请检查文件是否正确！");
                LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "[%s]", strLog.c_str());
                pLogicApp->SetAppState( BotApplication::EAppStateType_Exist );
            }
        }
        break;
    case BotApplication::EAppStateType_Update:
        { pLogicApp->Update(); }
        break;
    case BotApplication::EAppStateType_Exist:
        {
            pLogicApp->UnInit(); 
        }
        break;
    case BotApplication::EAppStateType_Exiting:
        { } 
        break;
    default:
        break;
    }

    Sleep( 1 );
}

BOOL CGameBotApp::InitInstance()
{
	LicenseChecker::Instance();
    // 如果一个运行在 Windows XP 上的应用程序清单指定要
    // 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
    //则需要 InitCommonControlsEx()。否则，将无法创建窗口。
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // 将它设置为包括所有要在应用程序中使用的
    // 公共控件类。
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

    // 初始化 OLE 库
    if (!AfxOleInit())
    {
        AfxMessageBox(IDP_OLE_INIT_FAILED);
        return FALSE;
    }
    AfxEnableControlContainer();
    // 标准初始化
    // 如果未使用这些功能并希望减小
    // 最终可执行文件的大小，则应移除下列
    // 不需要的特定初始化例程
    // 更改用于存储设置的注册表项
    // TODO: 应适当修改该字符串，
    // 例如修改为公司或组织名
    SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
    LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)
    // 注册应用程序的文档模板。文档模板
    // 将用作文档、框架窗口和视图之间的连接
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CGameBotDoc),
        RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
        RUNTIME_CLASS(CGameBotView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);

    // 分析标准外壳命令、DDE、打开文件操作的命令行
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // 调度在命令行中指定的命令。如果
    // 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    // 唯一的一个窗口已初始化，因此显示它并对其进行更新
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    // 仅当具有后缀时才调用 DragAcceptFiles
    //  在 SDI 应用程序中，这应在 ProcessShellCommand  之后发生

    LoadBinAStarOver = false;
    MonsterConfigOver = false;
    //SEctypeMap TempMap;
    //EctypeMaps CanFlyEctypeMapId;
    //TempMap.EctyprMapID = 22;
    //TempMap.EnterMapX = 131;
    //TempMap.EnterMapY = 137;
    //CanFlyEctypeMapId.push_back(TempMap); // 北山猎苑

    //TempMap.Reset();
    //TempMap.EctyprMapID = 53;
    //TempMap.EnterMapX = 160;
    //TempMap.EnterMapY = 261;
    //CanFlyEctypeMapId.push_back(TempMap); // 石门大战

    //FlyEctypeMapTableByPlayerNum.insert(std::make_pair(11,CanFlyEctypeMapId)); // 和地图11在一个服务器的副本 11是扬州

    //CanFlyEctypeMapId.clear();
    //TempMap.Reset();
    //TempMap.EctyprMapID = 20;
    //TempMap.EnterMapX   = 41;
    //TempMap.EnterMapY   = 40;
    //CanFlyEctypeMapId.push_back(TempMap); // 练功房

    ////     TempMap.Reset();
    ////     TempMap.EctyprMapID = 64;
    ////     TempMap.EnterMapX   = 194;
    ////     TempMap.EnterMapY   = 229;
    ////     CanFlyEctypeMapId.push_back(TempMap); // 万兽山庄
    //FlyEctypeMapTableByPlayerNum.insert(std::make_pair(10,CanFlyEctypeMapId)); // 太原

    //CanFlyEctypeMapId.clear();
    //TempMap.Reset();
    //TempMap.EctyprMapID = 51;
    //TempMap.EnterMapX   = 193;
    //TempMap.EnterMapY   = 183;
    //CanFlyEctypeMapId.push_back(TempMap); // 上林苑

    //TempMap.Reset();
    //TempMap.EctyprMapID = 63;
    //TempMap.EnterMapX   = 208;
    //TempMap.EnterMapY   = 97;
    //CanFlyEctypeMapId.push_back(TempMap); // 藏剑山庄
    //FlyEctypeMapTableByPlayerNum.insert(std::make_pair(2,CanFlyEctypeMapId)); // 长安


    //    CanFlyEctypeMapId.clear();
    //    CanFlyEctypeMapId.push_back(52); // 瓦岗寨,已经关闭
    //    FlyEctypeMapTableByPlayerNum.insert(std::make_pair(1,CanFlyEctypeMapId)); // 高句丽
    //    FlyEctypeMapTableByPlayerNum.insert(std::make_pair(7,CanFlyEctypeMapId)); // 洛口
    //    FlyEctypeMapTableByPlayerNum.insert(std::make_pair(9,CanFlyEctypeMapId)); // 漠北 
    //    FlyEctypeMapTableByPlayerNum.insert(std::make_pair(0,CanFlyEctypeMapId)); // 辽东
    //    CanFlyEctypeMapId.clear();
    //    FlyEctypeMapTableByPlayerNum.insert(std::make_pair(4,CanFlyEctypeMapId));  // 蓬莱
    //    FlyEctypeMapTableByPlayerNum.insert(std::make_pair(54,CanFlyEctypeMapId)); // 幽泉地狱

    //////////////////////////////////////////////////////////////////////////
    //CanFlyEctypeMapId.clear();
    //TempMap.Reset();
    //TempMap.EctyprMapID = 68;
    //TempMap.EnterMapX   = 160;
    //TempMap.EnterMapY   = 261;
    //CanFlyEctypeMapId.push_back(TempMap); // 石门大战

    //TempMap.Reset();
    //TempMap.EctyprMapID = 55;
    //TempMap.EnterMapX = 103;
    //TempMap.EnterMapY = 142;
    //CanFlyEctypeMapId.push_back(TempMap); // 十殿阎王

    //TempMap.Reset();
    //TempMap.EctyprMapID = 58;
    //TempMap.EnterMapX = 126;
    //TempMap.EnterMapY = 84;
    //CanFlyEctypeMapId.push_back(TempMap); // 龙口谷

    //TempMap.Reset();
    //TempMap.EctyprMapID = 59;
    //TempMap.EnterMapX = 62;
    //TempMap.EnterMapY = 204;
    //CanFlyEctypeMapId.push_back(TempMap); // 王陵武器库

    //TempMap.Reset();
    //TempMap.EctyprMapID = 61;
    //TempMap.EnterMapX = 62;
    //TempMap.EnterMapY = 204;
    //CanFlyEctypeMapId.push_back(TempMap); // 邪帝秘境

    //TempMap.Reset();
    //TempMap.EctyprMapID = 65;
    //TempMap.EnterMapX = 151;
    //TempMap.EnterMapY = 107;
    //CanFlyEctypeMapId.push_back(TempMap); // 杨公宝藏

    //TempMap.Reset();
    //TempMap.EctyprMapID = 66;
    //TempMap.EnterMapX = 54;
    //TempMap.EnterMapY = 69;
    //CanFlyEctypeMapId.push_back(TempMap); // 后山古庙
    //FlyEctypeMapTableByTeam.insert(std::make_pair(11,CanFlyEctypeMapId)); // 扬州

    //CanFlyEctypeMapId.clear();
    //TempMap.Reset();
    //TempMap.EctyprMapID = 13;
    //TempMap.EnterMapX   = 120;
    //TempMap.EnterMapY   = 108;
    //CanFlyEctypeMapId.push_back(TempMap); // 熔炎洞
    //FlyEctypeMapTableByTeam.insert(std::make_pair(3,CanFlyEctypeMapId));  // 淮南
    //FlyEctypeMapTableByTeam.insert(std::make_pair(8,CanFlyEctypeMapId));  // 敦煌
    //FlyEctypeMapTableByTeam.insert(std::make_pair(12,CanFlyEctypeMapId)); // 巴蜀

    //CanFlyEctypeMapId.clear();
    //TempMap.Reset();
    //TempMap.EctyprMapID = 60;
    //TempMap.EnterMapX   = 146;
    //TempMap.EnterMapY   = 145;
    //CanFlyEctypeMapId.push_back(TempMap); // 漠北大营

    //TempMap.Reset();
    //TempMap.EctyprMapID = 70;
    //TempMap.EnterMapX   = 194;
    //TempMap.EnterMapY   = 229;
    //CanFlyEctypeMapId.push_back(TempMap); // 万兽山庄
    //FlyEctypeMapTableByTeam.insert(std::make_pair(10,CanFlyEctypeMapId)); // 太原

    //CanFlyEctypeMapId.clear();
    //TempMap.Reset();
    //TempMap.EctyprMapID = 50;
    //TempMap.EnterMapX   = 203;
    //TempMap.EnterMapY   = 133;
    //CanFlyEctypeMapId.push_back(TempMap); // 王陵护宝

    //TempMap.Reset();
    //TempMap.EctyprMapID = 69;
    //TempMap.EnterMapX   = 208;
    //TempMap.EnterMapY   = 97;
    //CanFlyEctypeMapId.push_back(TempMap); // 藏剑山庄
    //FlyEctypeMapTableByTeam.insert(std::make_pair(2,CanFlyEctypeMapId)); // 长安

    // 整个机器人管理的Application
    //SetNetworkApp(&gBotApplication);
    mainLogicThread.CreateThread( MainLogicThreadFunc, &gBotApplication );//,THREAD_PRIORITY_ABOVE_NORMAL ) )

    return TRUE;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // 对话框数据
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    // 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CGameBotApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

void CGameBotApp::NetworkMsgLog()
{
    /*IMeConnector* pCon = GetMeNetwork().CreateMeConnector();

    if(pCon != NULL) 
    {
        pCon->PrintMsgTypeNum();
        pCon->Close();
        pCon->Release();
        pCon = NULL;

    }*/
}


void CGameBotApp::PushMessage( SBaseGuiLogicMessage* pGuiMessage )
{
    uint8* pTemp = _messageAlloc.allocate( pGuiMessage->size );
    if ( NULL == pTemp )
    { return; }
    memcpy_s( pTemp, pGuiMessage->size, pGuiMessage, pGuiMessage->size );

    CSALocker lock(_messageLock);
    _messages.push_back( pTemp );
}

void CGameBotApp::ProcessLogicMessage()
{
	Sleep(1);
    GuiLogicMessageContainer tempMessage;
    {
        CSALocker locker( _messageLock );
        if ( _messages.empty())
        { return; }
        tempMessage = _messages;
        _messages.clear();
    }

    while( !tempMessage.empty()  )
    {	
        unsigned char* pBlock = tempMessage.front();
        SBaseGuiLogicMessage* pMessage = (SBaseGuiLogicMessage*)pBlock;
        switch ( pMessage->id )
        {
        case EGuiLogicMessageType_RobotInfoChange:
            {
                LMsgRobotInfoChange* pDetail = (LMsgRobotInfoChange*)pMessage;
                HandleLMsgRobotInfoChange( pDetail );
            }
            break;
        case EGuiLogicMessageType_ShowRobotInfo:
            {
                LMsgShowRobotInfo* pMsgShowRobotInfo = (LMsgShowRobotInfo *)pMessage;
                HandleLMsgShowRobotinfo(pMsgShowRobotInfo);
            }
            break;
        case EGuiLogicMessageType_ShowAllRobotInfo:
            {
                LMsgShowAllRobotInfo* pMsgShowAllBotInfo = (LMsgShowAllRobotInfo *)pMessage;
                HandleLMsgShowAllBotInfo(pMsgShowAllBotInfo);
            }
        case EGuiLogicMessageType_InitReady:
            {
                LMsgInitReady* pMsgInitReady = (LMsgInitReady*)pMessage;
                HandleLMsgInitReady(pMsgInitReady);
            }
            break;
        }

        _messageAlloc.deallocate( pBlock );
        tempMessage.pop_front();
    }
}

void CGameBotApp::HandleLMsgRobotInfoChange( LMsgRobotInfoChange* pMessage )
{
    CMDIFrameWnd* pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
    CMDIChildWnd* pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
    CGameBotView* pView  = (CGameBotView*)pChild->GetActiveView();

    if(GettheMainView() == NULL || GettheMainView()->m_hWnd == NULL || GettheMainView()->m_ctlBotList.GetSafeHwnd() == NULL )
    { return; }

    int nSubItem = 1;
    int nIndex = pMessage->info.id; // 当前的ID
    int nCount = GettheMainView()->m_ctlBotList.GetItemCount();

    //int InsertNum = nIndex - GettheMainView()->m_ctlBotList.GetItemCount(); // 得到插入的数量
    if ( nCount == 1)
    {
        for (int i=0; i < nIndex; ++i)
        {
            GettheMainView()->m_ctlBotList.InsertItem(i, s_szType[pMessage->info.type]);
        }
    }
    else
    {
        if (nCount <= nIndex)
        {
            for (int i=nCount-1; i < nIndex; ++i)
            {
                GettheMainView()->m_ctlBotList.InsertItem(i, s_szType[pMessage->info.type]);
            }
        }
    }

    bool bIsModifyItem = false;
    int ModifyItemID=0;

#ifdef HIDE_BOT_INFO

    nIntMapIter iter = BotListMap.find(pMessage->info.id);
    if ( iter != BotListMap.end() )
    {
        ModifyItemID = iter->second;
        bIsModifyItem = true;
    }
    else
    {
        BotListMap.insert( make_pair(pMessage->info.id, --nIndex) );
    }

#else
    if ( nIndex == 0 )
    {
        int nItem = 0;
        static bool s_bInit = false;
        if (!s_bInit)
        {
            GettheMainView()->m_ctlBotList.SetItemText(0, nItem++, s_szType[pMessage->info.type]);
            SetListItemText(GettheMainView()->m_ctlBotList, 0, nItem++, "%d", pMessage->info.id);
            GettheMainView()->m_ctlBotList.SetItemText(0, nItem++, pMessage->info.account);
            s_bInit = true;
        }
        else
        {
            nItem += 3;
        }

        GettheMainView()->m_ctlBotList.SetItemText(0, nItem++, pMessage->info.tipInfo);
        GettheMainView()->m_ctlBotList.SetItemText(0, nItem++, s_szTips[pMessage->info.state] );	
        GettheMainView()->m_ctlBotList.SetItemText(0, nItem++, pMessage->info.map );
        return;
    }
#endif

    if ( !bIsModifyItem ) // 如果不是修改，是新插入
    {
        //GettheMainView()->m_ctlBotList.InsertItem(nCount, s_szType[pMessage->info.type]); // 机器人类型
        //SetListItemText( GettheMainView()->m_ctlBotList, nCount, nSubItem, const_cast<char *>(s_szType[pMessage->info.type]) );// 类型
        SetListItemText(GettheMainView()->m_ctlBotList, nIndex, nSubItem++, "%d", pMessage->info.id); //  ID
        GettheMainView()->m_ctlBotList.SetItemText(nIndex, nSubItem++, pMessage->info.account);
        SetOneBotChangedInfo(GettheMainView()->m_ctlBotList, nIndex, nSubItem, pMessage);
    }
    else //是修改
    {
        nSubItem+=2;
        SetOneBotChangedInfo(GettheMainView()->m_ctlBotList, ModifyItemID, nSubItem, pMessage);
    }

    // TODO:此处设置当所有插入到ListCtrl中后将 “添加” 按钮状态设为可用
    //CString strNum;
    //GettheMainView()->m_frmAdd.m_cmbBotNum.GetWindowText(strNum);

    //CButton* AddButton = (CButton*)( GettheMainView()->m_frmAdd.GetDlgItem(IDC_BUTTON_ADD) );
    //if ( (nIndex - OldAddNum) >= atoi(strNum) ) // 相对个数 = GettheMainView()->m_ctlBotList.GetItemCount()(现在总的Item数量) - 上一次添加的个数
    //{
    //    AddButton->EnableWindow(TRUE);
    //}
}

void CGameBotApp::SetOneBotChangedInfo(CListCtrl& xList, int nItem, int nSubItem, LMsgRobotInfoChange* pMessage)
{
    xList.SetItemText(nItem, nSubItem++, pMessage->info.tipInfo);
    xList.SetItemText(nItem, nSubItem++, s_szTips[pMessage->info.state]);

    CString strMap = "";
    if (pMessage->info.state == State_Play)
    {
        strMap.Format("%s:%s", pMessage->info.channel, pMessage->info.map);
        xList.SetItemText(nItem, nSubItem++, strMap);
    }
    else
    {
        xList.SetItemText(nItem, nSubItem++, "");
    }
}

void CGameBotApp::HandleLMsgShowRobotinfo( LMsgShowRobotInfo* pMessage )
{
// Edit控件 与 ListCtrl控件数据
   MsgStatistician msgStatistician;
   msgStatistician.SetStartTime(pMessage->dwStartTime);
   msgStatistician.SetLoopCount(pMessage->ExecuteActNum);
   msgStatistician.SetMsgSendCount(pMessage->totalSendMsgNum);
   msgStatistician.SetMsgSendSize(pMessage->SendMsgSize);
   msgStatistician.SetMsgRecvCount(pMessage->totalReceiveMsgNum);
   msgStatistician.SetMsgRecvSize(pMessage->ReceiveMsgSize);
	msgStatistician.SetMonsterNum(pMessage->MonsterMum);					//luo.qin 3.18
   msgStatistician.m_xMinSendInfo.dwCount = pMessage->MinSingleSendMsgNum; // 单次最小发送数量
   msgStatistician.m_xMinSendInfo.dwSize  = pMessage->MinSingleSendMsgSize;// 单次最小发送大小
   msgStatistician.m_xMaxSendInfo.dwCount = pMessage->MaxSingleSendMsgNum; // 单次最大发送数量
   msgStatistician.m_xMaxSendInfo.dwSize  = pMessage->MaxSingleSendMsgSize;// 单次最小发送大小
   msgStatistician.m_xMinRecvInfo.dwCount = pMessage->MinSingleRecvMsgNum; // 单次最小接收数量
   msgStatistician.m_xMinRecvInfo.dwSize  = pMessage->MinSingleRecvMsgSize;// 单次最小接收大小
   msgStatistician.m_xMaxRecvInfo.dwCount = pMessage->MaxSingleRecvMsgNum; // 单次最大接收数量
   msgStatistician.m_xMaxRecvInfo.dwSize  = pMessage->MaxSinglerecvMsgSize;// 单次最大接收大小
// 最大最小收发消息
   msgStatistician.m_xMinSendInfo.vecMsgInfo.assign( pMessage->vecMinSendMsgInfo, pMessage->vecMinSendMsgInfo + 4 );
   msgStatistician.m_xMaxSendInfo.vecMsgInfo.assign( pMessage->vecMaxSendMsgInfo, pMessage->vecMaxSendMsgInfo + 10 );
   msgStatistician.m_xMinRecvInfo.vecMsgInfo.assign( pMessage->vecMinRecvMsgInfo, pMessage->vecMinRecvMsgInfo + 4 );
   msgStatistician.m_xMaxRecvInfo.vecMsgInfo.assign( pMessage->vecMaxRecvMsgInfo, pMessage->vecMaxRecvMsgInfo + 10 );
// ToDo:所有发送与接收的总数
   for (int i=0; i<100; ++i)
   {
       msgStatistician.m_mapMsgSendCount.insert( make_pair(i, pMessage->mapMsgSendCount[i]) );
       msgStatistician.m_mapMsgRecvCount.insert( make_pair(i, pMessage->mapMsgRecvCount[i]) );
   }

   GettheMainView()->m_xMsgInfo.UpdataInformation(msgStatistician); // 更新MsgInfo信息

// 连接状态 Ip port 数据
    char *ip = const_cast<char *>( pMessage->strIp.c_str() );
    WORD port = pMessage->wPort;
    int state = pMessage->nState;
    DWORD dwError = pMessage->dwError;
    bool bIsConnect = pMessage->bConnect;
    GettheMainView()->m_xMsgInfo.UpdateConnectInfo(ip, port, state, dwError, bIsConnect);
// ping chat
    DWORD dwPingTime = pMessage->dwPingTime;
    GettheMainView()->m_xMsgInfo.UpdatePingChart(dwPingTime);
// Bot坐标位置
    GettheMainView()->m_frmAdd.m_MapPoint.SetBotID(pMessage->BotID);
 //   GettheMainView()->m_frmAdd.ShowerrorLog()
}

void CGameBotApp::HandleLMsgShowAllBotInfo( LMsgShowAllRobotInfo* pMessage )
{
    // ToDo:在此处调用ShowBotCountInformation 与 ShowBotMapDistributing
    // 显示机器人数量和机器人地图分布
    ShowBotCountInformation(pMessage->nTotalBotNum, pMessage->nOnlineBotNum, pMessage->nAtkBotNum, pMessage->nMoveBotNum, pMessage->nTotalMonsterNum);

    std::map<string, int> mapDistributing;
    for (int i=0; i<50; ++i)
    {
        if ( strcmp(pMessage->BotMap[i].mapName, "") == 0 )
        {
            break;
        }

        mapDistributing.insert( make_pair(pMessage->BotMap[i].mapName, pMessage->BotMap[i].BotInMapNum) );
    }

    if (mapDistributing.empty())
    { return;}

    ShowBotMapDistributing( mapDistributing );
}

void CGameBotApp::HandleLMsgInitReady(LMsgInitReady* pMessage)
{
    if ( !pMessage->bIsInitReady )
    { return;}
    
    theMainFrame->m_wndStatusBar.SetPaneText( 0, _T("资源加载完成") );
    CButton* addButton = (CButton*)( GettheMainView()->m_frmAdd.GetDlgItem(IDC_BUTTON_ADD) );
    addButton->EnableWindow(TRUE);
}

void CGameBotApp::SetBotInfo(BaseRobot *pBot, const char* szTips)
{
    CMDIFrameWnd* pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
    CMDIChildWnd* pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
    CGameBotView* pView  = (CGameBotView*)pChild->GetActiveView();

    if(GettheMainView() == NULL || GettheMainView()->m_hWnd == NULL || GettheMainView()->m_ctlBotList.GetSafeHwnd() == NULL || pBot == NULL)
    { return; }

    int nSubItem = 1;
    bool bInsert = false;

    int nIndex = pBot->GetBotID(); 
    int nCount = GettheMainView()->m_ctlBotList.GetItemCount();

#ifdef HIDE_BOT_INFO	
    static const int nAddIndex = 1;
    nIndex -= nAddIndex;
    --nCount;

#else
    if (nIndex == 0)
    {
        int nItem = 0;
        static bool s_bInit = false;
        if (!s_bInit)
        {
            GettheMainView()->m_ctlBotList.SetItemText(0, nItem++, s_szType[pBot->GetType()]);
            SetListItemText(GettheMainView()->m_ctlBotList, 0, nItem++, "%d", pBot->GetBotID());
            GettheMainView()->m_ctlBotList.SetItemText(0, nItem++, pBot->GetAccount());

            s_bInit = true;
        }
        else
        {
            nItem += 3;
        }

        GettheMainView()->m_ctlBotList.SetItemText(0, nItem++, pBot->GetBotTips());
        GettheMainView()->m_ctlBotList.SetItemText(0, nItem++, szTips);	
        GettheMainView()->m_ctlBotList.SetItemText(0, nItem++, pBot->GetMapName()); // Modify [10/9/2010 pengbo.yang] 去掉GetMapName.c_str(),因为返回值为char *
        return;
    }
#endif

    if(nIndex >= nCount )
    {
        nIndex = nCount;
        bInsert = true;

        GettheMainView()->m_ctlBotList.InsertItem(nIndex, s_szType[pBot->GetType()]);  

        SetListItemText(GettheMainView()->m_ctlBotList, nIndex, nSubItem++, "%d", pBot->GetBotID());
        GettheMainView()->m_ctlBotList.SetItemText(nIndex, nSubItem++, pBot->GetAccount());

        //设置选中
        GettheMainView()->m_ctlBotList.SetItemState(nIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
        GettheMainView()->m_ctlBotList.SetFocus();
        GettheMainView()->m_ctlBotList.EnsureVisible(nIndex, true);
    }
    //不是新插入
    if (!bInsert) 
    { nSubItem += 2; }

    GettheMainView()->m_ctlBotList.SetItemText(nIndex, nSubItem++, pBot->GetBotTips());
    GettheMainView()->m_ctlBotList.SetItemText(nIndex, nSubItem++, szTips);	
    CString strMap = "";

    if (pBot->GetBotState() == State_Play)
    {
        strMap.Format("%s : %s", pBot->GetChannelName(), pBot->GetMapName());
        GettheMainView()->m_ctlBotList.SetItemText(nIndex, nSubItem++, strMap);
    }
    else
    {
        GettheMainView()->m_ctlBotList.SetItemText(nIndex, nSubItem++, "");
    }	
}

void CGameBotApp::ShowBotInfo(int nID)
{
    if(GettheMainView() == NULL || GettheMainView()->GetSafeHwnd() == NULL)
    { return; }

    BaseRobot* pBot = gBotApplication.GetBot(nID);
    if(pBot == NULL) 
    { return; }

    // Show Bot Point Informatio
    if (GettheMainView()->m_frmAdd.m_hWnd == NULL)
    { return; }

    GettheMainView()->m_frmAdd.m_MapPoint.SetBotID(nID);

    ////////////////////////////////////
    string strInfo = "机器人坐标";
    if (!GettheMainView()->m_frmAdd.m_MapPoint.m_strMapName.empty())
    {
        strInfo = "地图:";
        strInfo += GettheMainView()->m_frmAdd.m_MapPoint.m_strMapName;
        strInfo += "坐标:";
        CString strPoint = "";
        strPoint.Format("(%d,%d)", (int)pBot->GetPosX(), (int)pBot->GetPosY());
        strInfo += strPoint.GetBuffer();
    }

    if (GettheMainView()->m_frmAdd.m_Map.m_hWnd != NULL)
    {
        GettheMainView()->m_frmAdd.m_Map.SetWindowText(strInfo.c_str());
    }
    /////////////////////////////////////////////////////////

    //theMainView->UpdateSystemMessageCount(pBot);
    //////////////////////////////////////////////////////////


#ifdef HIDE_BOT_INFO	

    GettheMainView()->UpdataStatMsgInfo(pBot);

    return;
#endif

    GettheMainView()->UpdateSystemMessageCount(pBot);

    //////////////////////////////////////////////////////////////// 
    if (GettheMainView()->m_nInfoIndex != -1)
    {
        GettheMainView()->m_vecBaseInfo[GettheMainView()->m_nInfoIndex]->UpdateInformation(pBot);
    }		

    GettheMainView()->UpdateChatMessage(pBot);	
    ///////////////////////////////////////////////////////////////	
    if (GettheMainView()->m_pMapInfo != NULL && GettheMainView()->m_pMapInfo->IsShow())
    {
        GettheMainView()->m_pMapInfo->UpdateInformation(pBot->GetBotID());
        GettheMainView()->m_pMapInfo->ShowMapBmp();
    }
    ////////////////////////////////////////////////////////////////////
}

void CGameBotApp::ShowServerInfo()
{
    if(theMainFrame == NULL)
    { return; }

    CString strBuf;
    strBuf.Format("%s:%d 版本:%s", theBotDataCenter.GetServerIP(), theBotDataCenter.GetServerPort(), ApplicationConfig::Instance().GetFullVersion() );
    theMainFrame->SetWindowText(strBuf.GetBuffer());
}

int CGameBotApp::ExitInstance()
{
    // TODO: 在此添加专用代码和/或调用基类
    gBotApplication.Exit = TRUE;    
    theMainFrame = NULL;
    mainLogicThread.StopThreadAndWaitDead();
    return CWinApp::ExitInstance();
}

////////////////////////////////////////////////////////////////
void CGameBotApp::ShowErrorInformation(int nBotID, char *szAccount, int nMsgType, int nMsgFlag, int nMsgLength, char *szErrorInfo, char *szErrorFile)
{
    //设置Log文件保存在Error Log 文件夹下
    static char s_szFilePath[_MAX_PATH] = {0};

    if (s_szFilePath[0] == 0)
    {
        char szProcPath[_MAX_PATH];
        char szDir[_MAX_DIR];
        char szDirve[_MAX_DRIVE];

        ::GetModuleFileName(NULL, szProcPath, sizeof(szProcPath));

        _tsplitpath(szProcPath, szDirve, szDir, NULL, NULL);
        sprintf_s(s_szFilePath, sizeof(s_szFilePath), "%s%s\\%s", szDirve, szDir, ERROR_LOG_PATH);

        if (GetFileAttributes(s_szFilePath) == INVALID_FILE_ATTRIBUTES)
        {
            ::_mkdir(s_szFilePath);	
        }		
    }

    Error_Log_ stErrorLog;

    stErrorLog.nBotID = nBotID;
    stErrorLog.strAccount = szAccount;
    stErrorLog.nMsgType = nMsgType;
    stErrorLog.nMsgFlag = nMsgFlag;
    stErrorLog.nMsgLength = nMsgLength;
    stErrorLog.strInfo = szErrorInfo;
    stErrorLog.strFile = szErrorFile;

    if (GettheMainView() != NULL)
    {
        GettheMainView()->m_frmAdd.AddErrorLog(stErrorLog);
    }	
}

void CGameBotApp::ShowBotCountInformation(int nTotalCount, int nOnlineCount, int nAttackCount, int nMoveCount, int nTotalMonsterNum)
{
    if (GettheMainView() == NULL || GettheMainView()->m_frmAdd.m_hWnd == NULL)
    {
        return;
    }

    SetText(GettheMainView()->m_frmAdd.m_TolalRototNumber, "%d", nTotalCount);
    SetText(GettheMainView()->m_frmAdd.m_totalOnlineNum, "%d", nOnlineCount);
    SetText(GettheMainView()->m_frmAdd.m_NotInGame, "%d", nTotalCount - nOnlineCount);
    SetText(GettheMainView()->m_frmAdd.m_AttackCount, "%d", nAttackCount);
    SetText(GettheMainView()->m_frmAdd.m_MoveCount, "%d", nMoveCount);
	SetText(GettheMainView()->m_xMsgInfo.m_editTotalMonsterNum, "%d", nTotalMonsterNum);
}

void CGameBotApp::ShowBotMapDistributing(std::map<string,int> &mapDistributing)
{
    if (GettheMainView() == NULL || GettheMainView()->m_frmAdd.m_hWnd == NULL)
    {
        return;
    }
    map<string,int>::iterator iter = mapDistributing.begin();
    map<string,int>::iterator end = mapDistributing.end();

    int nIndex = 0;
    int nCount = GettheMainView()->m_frmAdd.m_listMapDistributing.GetItemCount();
    CString strMapAndID;
    for ( ; iter != end; ++iter )
    {
        MapConfig::MapData* pMap = theMapConfig.GetMapDataByName(iter->first.c_str());  // Map每次获得都是第一张图的数据
        if (pMap == NULL)
        {
            continue;
        }
        else
        {
            strMapAndID.Format( "%s(%d)", iter->first.c_str(), pMap->Id );
        }

        if (nIndex >= nCount)
        {
            GettheMainView()->m_frmAdd.m_listMapDistributing.InsertItem( nIndex, strMapAndID.GetBuffer() );
            ++nCount;
        }
        else
        {
            GettheMainView()->m_frmAdd.m_listMapDistributing.SetItemText( nIndex, 0, strMapAndID.GetBuffer() );
        }

        SetListItemText(GettheMainView()->m_frmAdd.m_listMapDistributing, nIndex, 1, "%d", (*iter).second);
        ++nIndex;
    }

    for (int i = nCount - 1; i >= nIndex; --i)
    {
        GettheMainView()->m_frmAdd.m_listMapDistributing.DeleteItem(i);
    }
}

//机器人均匀分散
void CGameBotApp::DisPerseBot(char* pszMap, int nCount)
{
    //gBotApplication.DisPerseBot(pszMap, nCount);
}

void CGameBotApp::EditAttackAreaInfo(SAreaInfo *xpAreaInfo, int nCount)
{
    int nIndex = GetListCtrlCurSel(GettheMainView()->m_ctlBotList);
    if (nIndex == -1)
    {
        return;
    }

    for (int i = 0; i < nCount; ++i)
    {
        int nBotID = GetListItemInt(GettheMainView()->m_ctlBotList, nIndex + i, 1, -1);
        if (nBotID == -1)
        {
            break;
        }

        BaseRobot *pBot = gBotApplication.GetBot(nBotID);
        if (pBot != NULL)
        {
            int nType = pBot->GetType();

            switch (nType)
            {
            case Bot_Attack:
                ((CAttackBot*)pBot)->SetAreaInfo(xpAreaInfo);
                break;
            case Bot_Normal:
                ((CNormalBot*)pBot)->SetAreaInfo(xpAreaInfo);
                break;
            case Bot_Fight:
                ((CFightBot*)pBot)->SetAreaInfo(xpAreaInfo);
                break;
            //case Bot_Guild:
            //    ((CGuildBot*)pBot)->SetAreaInfo(xpAreaInfo);
            //    break;
            case Bot_Online:
                ((OnlineBot*)pBot)->SetAreaInfo(xpAreaInfo);
                break;
            case Bot_Team:
                ((TeamBot*)pBot)->SetAreaInfo(xpAreaInfo);
                break;
            case Bot_Ectype:
                ((EctypeBot*)pBot)->SetAreaInfo(xpAreaInfo);
                break;
            case Bot_Brome:
                ((DromeBot*)pBot)->SetAreaInfo(xpAreaInfo);
                break;
            case Bot_Login:
                ((CLoginBot*)pBot)->SetAreaInfo(xpAreaInfo);
            }					
        }
    }

    //POSITION pos = GettheMainView()->m_ctlBotList.GetFirstSelectedItemPosition();
    //while(pos != NULL)
    //{
    //	int nItem = GettheMainView()->m_ctlBotList.GetNextSelectedItem(pos);

    //	if (nItem != -1)
    //	{
    //		int nBotID = GetListItemInt(GettheMainView()->m_ctlBotList, nItem, 1, -1);
    //		if (nBotID != -1)
    //		{
    //			CBot *pBot = m_BotServer.GetBot(nBotID);
    //			if (pBot != NULL)
    //			{
    //				int nType = pBot->GetType();

    //				switch (nType)
    //				{
    //				case Bot_Attack:
    //					((CAttackBot*)pBot)->SetAreaInfo(xpAreaInfo);
    //					break;
    //				case Bot_Normal:
    //					((CNormalBot*)pBot)->SetAreaInfo(xpAreaInfo);
    //					break;
    //				}
    //			}
    //		}
    //	}
    //}
}

void CGameBotApp::SetText(CWnd& xWnd, char *pszFormat, ...)
{
    if (xWnd.m_hWnd != NULL)
    {
        va_list valist;

        va_start(valist,pszFormat);

        char szValue[100] = "";

        vsprintf(szValue, pszFormat, valist);

        va_end(valist);

        xWnd.SetWindowText(szValue);
    }	
}

int CGameBotApp::GetInt(CWnd& xWnd, int nDef)
{
    if (xWnd.m_hWnd == NULL)
    {
        return nDef;
    }

    CString strValue = "";
    xWnd.GetWindowText(strValue);
    if (strValue.IsEmpty())
    {
        return nDef;
    }

    return atoi(strValue.GetBuffer());
}

void CGameBotApp::SetListItemText(CListCtrl& xList, int nItem, int nSubItem, char *pszFormat, ...)
{
    if (xList.m_hWnd != NULL)
    {
       char szValue[200] = "";
		
		va_list valist;

        va_start(valist,pszFormat);

       

        vsprintf(szValue, pszFormat, valist);

        va_end(valist);

        xList.SetItemText(nItem, nSubItem, szValue);
    }	
}

int CGameBotApp::GetListItemInt(CListCtrl &xList, int nItem, int nSubItem, int nDef)
{
    if (xList.m_hWnd == NULL)
    {
        return nDef;
    }

    CString strValue = xList.GetItemText(nItem, nSubItem);

    if (strValue.IsEmpty())
    {
        return nDef;
    }

    return (atoi(strValue.GetBuffer()));
}

int CGameBotApp::GetListCtrlCurSel(CListCtrl &xList)
{
    if (xList.m_hWnd != NULL)
    {
        POSITION pos = xList.GetFirstSelectedItemPosition();
        if (pos != NULL)
        {
            return xList.GetNextSelectedItem(pos); 
        }
    }

    return -1;
}


void CGameBotApp::ShowBigMap()
{
    GettheMainView()->ShowBigMap();
}

static char s_szLogInfo[]	= "*****************************机器人流量统计信息***************************\r\n\r\n";
static char s_szBotCount[]	= "*******************************机器人数量*********************************\r\n\r\n";
static char s_szMapInfo[]	= "*******************************机器人地图分布*****************************\r\n\r\n";
static char s_szMsgTotal[]	= "*******************************机器人消息总数*****************************\r\n\r\n";
static char s_szSendInfo[]	= "*******************************发送的所有消息*****************************\r\n\r\n";
static char s_szRecvInfo[]	= "*******************************接收的所有消息*****************************\r\n\r\n";
static char s_szSpaceString[] = "===================================================================================\r\n";


void CGameBotApp::PrintStatLog(int nType, char *szFile)
{
    if (szFile == NULL || *szFile == 0)
    {
        return;
    }

    ofstream outfile;
    outfile.open(szFile, ios_base::app);	//以追加的方式打开
    if (!outfile)
    {
        CString strError;
        strError.Format("打开%s失败,请确定文件路径正确!", szFile);
        AfxMessageBox(strError);
        return;
    }

    //先打印系统信息	
    outfile << s_szLogInfo;

    SYSTEMTIME xSystemTime;
    ::GetLocalTime(&xSystemTime);

    char szPrinfTime[100] = "";
    sprintf_s(szPrinfTime, sizeof(szPrinfTime) - 1, "打印时间: \t%u-%u-%u %u:%u:%u \r\n", xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay, xSystemTime.wHour, xSystemTime.wMinute, xSystemTime.wSecond);

    outfile << szPrinfTime;

    //运行时间
    char szRunTime[100] = "";
    DWORD dwNowTime = HQ_TimeGetTime();	
    sprintf_s(szRunTime, sizeof(szRunTime) - 1, "运行时间: \t%s \r\n\r\n", m_xTatolMsgStatistician.GetStatisticianTimeString(dwNowTime));
    outfile << szRunTime;


    //打印机器人数量信息
    outfile << s_szBotCount;

    char szBotCount[100] = "";
    sprintf_s(szBotCount,sizeof(szBotCount) - 1, "机器人总数:\t\t%u\r\n在线机器人:\t\t%u\r\n不在线机器人:\t\t%u\r\n打怪机器人:\t\t%u\r\n飞行机器人:\t\t%u\r\n\r\n",
        gBotApplication.GetTotalBotCount(), gBotApplication.GetOnLineBotCount(),gBotApplication.GetTotalBotCount() - gBotApplication.GetOnLineBotCount(), gBotApplication.GetAttackBotCount(), gBotApplication.GetMoveBotCount());
    outfile << szBotCount;

    //打印地图分布信息
    outfile << s_szMapInfo;
    map<string, int>::iterator iter = gBotApplication.m_mapMapDistributing.begin();
    map<string, int>::iterator end = gBotApplication.m_mapMapDistributing.end();

    for ( ; iter != end; ++iter)
    {
        outfile << (*iter).first << "\t\t" << (*iter).second << "\r\n";
    }
    outfile << "\r\n";

    //打印机器人消息总数
    outfile << s_szMsgTotal;
    char szMsgTotal[100] = "";
    sprintf_s(szMsgTotal, sizeof(szMsgTotal) - 1, "%s%16s%16s%16s%16s\r\n\r\n","消息类型", "数量", "大小", "平均数量" ,"平均大小");
    outfile << szMsgTotal;

	sprintf_s(szMsgTotal, sizeof(szMsgTotal) - 1,"%s%16I64u%16I64u%16I64u%16I64u\r\n", "发送消息",
	   m_xTatolMsgStatistician.GetMsgSendCount(), m_xTatolMsgStatistician.GetMsgSendSize(), m_xTatolMsgStatistician.GetMsgSendCountPerSecond(dwNowTime), m_xTatolMsgStatistician.GetMsgSendSizePerSecond(dwNowTime));
	outfile << szMsgTotal;

    sprintf_s(szMsgTotal, sizeof(szMsgTotal) - 1, "%s%16I64u%16I64u%16I64u%16I64u\r\n\r\n", "接收消息",
        m_xTatolMsgStatistician.GetMsgRecvCount(), m_xTatolMsgStatistician.GetMsgRecvSize(), m_xTatolMsgStatistician.GetMsgRecvCountPerSecond(dwNowTime), m_xTatolMsgStatistician.GetMsgRecvSizePerSecond(dwNowTime));
    outfile << szMsgTotal;

    //打印发送的所有消息
    outfile << s_szSendInfo;
    char szSendInfo[100] = "";
    sprintf_s(szSendInfo, sizeof(szSendInfo) - 1, "%10s%16s%16s%16s%16s\r\n\r\n", "消息ID", "消息名称", "数量", "大小", "百分比");
    outfile << szSendInfo;

    vector<MsgStatistician::Msg_Info_> vecSend;
    vecSend.clear();

    map<DWORD, MsgStatistician::Msg_Info_>::iterator senditer = m_xTatolMsgStatistician.m_mapMsgSendCount.begin();
    map<DWORD, MsgStatistician::Msg_Info_>::iterator sendend = m_xTatolMsgStatistician.m_mapMsgSendCount.end();
    for ( ; senditer != sendend; ++senditer)
    {
        vecSend.push_back((*senditer).second);
    }

    //sort(vecSend.begin(), vecSend.end(), greater<MsgStatistician::Msg_Info_>());

    vector<MsgStatistician::Msg_Info_>::iterator viter = vecSend.begin();
    vector<MsgStatistician::Msg_Info_>::iterator vend = vecSend.end();
    for ( ; viter != vend; ++viter)
    {
        float dPercent = ((float)(*viter).dwSize) / m_xTatolMsgStatistician.GetMsgSendSize() * 100;

        sprintf_s(szSendInfo, sizeof(szSendInfo) - 1, "%10u%16s%16I64u%16I64u%16f\r\n", (*viter).dwType,
            GettheMainView()->m_xMsgInfo.GetMessageType((*viter).dwType), (*viter).dwCount, (*viter).dwSize, dPercent);
        outfile << szSendInfo;
    }
    outfile << "\r\n";


    //打印接收的所有信息
    outfile << s_szRecvInfo;
    char szRecvInfo[100] = "";
    sprintf_s(szRecvInfo, sizeof(szRecvInfo) - 1, "%10s%16s%16s%16s%16s\r\n\r\n", "消息ID","消息名称", "数量", "大小", "百分比");
    outfile << szRecvInfo;

    vector<MsgStatistician::Msg_Info_> vecRecv;
    vecRecv.clear();

    map<DWORD, MsgStatistician::Msg_Info_>::iterator recviter = m_xTatolMsgStatistician.m_mapMsgRecvCount.begin();
    map<DWORD, MsgStatistician::Msg_Info_>::iterator recvend = m_xTatolMsgStatistician.m_mapMsgRecvCount.end();
    for ( ; recviter != recvend; ++recviter)
    {
        vecRecv.push_back((*recviter).second);
    }

    sort(vecRecv.begin(), vecRecv.end(), greater<MsgStatistician::Msg_Info_>());

    viter = vecRecv.begin();
    vend = vecRecv.end();
    for ( ; viter != vend; ++viter)
    {
        float dPercent = ((float)(*viter).dwSize) / m_xTatolMsgStatistician.GetMsgRecvSize() * 100;

        sprintf_s(szRecvInfo, sizeof(szRecvInfo) - 1, "%10u%16s%16I64u%16I64u%16f\r\n", (*viter).dwType,
            GettheMainView()->m_xMsgInfo.GetMessageType((*viter).dwType), (*viter).dwCount, (*viter).dwSize, dPercent);
        outfile << szRecvInfo;
    }
    outfile << "\r\n";

    outfile << s_szSpaceString;
    outfile << s_szSpaceString;
    outfile << "\r\n";

    outfile.clear();
    outfile.close();
}

void CGameBotApp::ReadAllScript(const char* pszPath, CComboBox &xComboBox, vector<string> &vecScript)
{
    vecScript.clear();


    char szFile[_MAX_PATH] = "";
    sprintf_s(szFile, sizeof(szFile) - 1, "%s\\*.ini", pszPath);
    if (GetFileAttributes(pszPath) == INVALID_FILE_ATTRIBUTES)
    {
        ::_mkdir(pszPath);	
    }

    WIN32_FIND_DATA xFindData;                                     
    HANDLE hFile = FindFirstFileA(szFile, &xFindData);   	
    if(hFile != INVALID_HANDLE_VALUE)
    {
        do
        {
            xComboBox.AddString(xFindData.cFileName);
            vecScript.push_back(xFindData.cFileName);			

        }while(FindNextFileA(hFile, &xFindData));                      
        FindClose(hFile);
    }
}

void CGameBotApp::UpdataAddFrmScriptCombox()
{
    GettheMainView()->m_frmAdd.m_comboScript.ResetContent();

    GettheMainView()->m_frmAdd.m_comboScript.AddString("不使用脚本");

    ReadAllScript(Script_Path, GettheMainView()->m_frmAdd.m_comboScript);

    GettheMainView()->m_frmAdd.m_comboScript.SetCurSel(0);
}

/////////////////////////////////////////////////////////////////////////////////////
#define Section_Key		"Script"
#define StartId_Key		"StartId"
#define Type_Key		"Type"
#define Count_Key		"Count"
#define RunSpace_Key	"RunSpace"
#define Fly_Key			"FlySpace"
#define OnLine_Key		"OnLineTime"
#define AddSpace_Key	"AddSpace"
#define AddCount_Key	"PerAddCount"
#define Map_Key			"Map"
#define PosX_Key		"PosX"
#define PosY_Key		"PosY"
#define Radius_Key		"Radius"


void CGameBotApp::LoadScript(const char* pszFile, vector<SAddInfo> &vecAddInfo)
{
    vecAddInfo.clear();

    if (pszFile == NULL || *pszFile == 0)
    {
        return;
    }

    SAddInfo xAddInfo;

    int nIndex = 0;
    while (true)
    {
        CString strIndex = "";
        strIndex.Format("%s_%d", Section_Key, nIndex);
        int nStartId = ::GetPrivateProfileInt(strIndex, StartId_Key, -1, pszFile);
        if (nStartId == -1)
        {
            break;
        }

        xAddInfo.nStartId = nStartId;
        xAddInfo.nType = ::GetPrivateProfileInt(strIndex, Type_Key, -1, pszFile);
        xAddInfo.nCount = ::GetPrivateProfileInt(strIndex, Count_Key, 0, pszFile);

        xAddInfo.nMoveStep = ::GetPrivateProfileInt(strIndex, RunSpace_Key, 500, pszFile);
        xAddInfo.nSpaceTime = ::GetPrivateProfileInt(strIndex, AddSpace_Key, 0, pszFile);
        xAddInfo.nPerCount = ::GetPrivateProfileInt(strIndex, AddCount_Key, 1, pszFile);

        xAddInfo.xAreaInfo.nMap = ::GetPrivateProfileInt(strIndex, Map_Key, -1, pszFile);
        xAddInfo.xAreaInfo.xPoint.x = ::GetPrivateProfileInt(strIndex, PosX_Key, 300, pszFile);
        xAddInfo.xAreaInfo.xPoint.y = ::GetPrivateProfileInt(strIndex, PosY_Key, 300, pszFile);
        xAddInfo.xAreaInfo.nRadius = ::GetPrivateProfileInt(strIndex, Radius_Key, 300, pszFile);

        xAddInfo.nFlySpace = ::GetPrivateProfileInt(strIndex, Fly_Key, 120, pszFile);
        xAddInfo.nOnlineTime = ::GetPrivateProfileInt(strIndex, OnLine_Key, 120, pszFile);

        vecAddInfo.push_back(xAddInfo);

        ++nIndex;
    }
}

void CGameBotApp::SaveScript(const char* pszFile, vector<SAddInfo> &vecAddInfo)
{
    if (pszFile == NULL || *pszFile == 0)
    {
        return;
    }

    sort(vecAddInfo.begin(), vecAddInfo.end());

    ItrAddInfoContainer iter = vecAddInfo.begin();
    ItrAddInfoContainer end = vecAddInfo.end();

    for (int i = 0; iter != end; ++i,++iter)
    {
        CString strIndex = "";
        strIndex.Format("%s_%d", Section_Key, i);

        theBotDataCenter.WritePrivateProfileInt(strIndex, StartId_Key, (*iter).nStartId, pszFile);
        theBotDataCenter.WritePrivateProfileInt(strIndex, Type_Key, (*iter).nType, pszFile);	
        theBotDataCenter.WritePrivateProfileInt(strIndex, Count_Key, (*iter).nCount, pszFile);
        theBotDataCenter.WritePrivateProfileInt(strIndex, RunSpace_Key, (*iter).nMoveStep, pszFile);
        theBotDataCenter.WritePrivateProfileInt(strIndex, Map_Key, (*iter).xAreaInfo.nMap, pszFile);
        theBotDataCenter.WritePrivateProfileInt(strIndex, PosX_Key, (*iter).xAreaInfo.xPoint.x, pszFile);
        theBotDataCenter.WritePrivateProfileInt(strIndex, PosY_Key, (*iter).xAreaInfo.xPoint.y, pszFile);
        theBotDataCenter.WritePrivateProfileInt(strIndex, Radius_Key, (*iter).xAreaInfo.nRadius, pszFile);

        theBotDataCenter.WritePrivateProfileInt(strIndex, AddCount_Key, (*iter).nPerCount, pszFile);
        theBotDataCenter.WritePrivateProfileInt(strIndex, AddSpace_Key, (*iter).nSpaceTime, pszFile);
        theBotDataCenter.WritePrivateProfileInt(strIndex, OnLine_Key, (*iter).nOnlineTime, pszFile);
    }
}

bool CGameBotApp::LoadMonsterFile()
{
    if (MonsterConfigOver)
    {
        return true;
    }
    for (int i = 0 ;i<theMapConfig.MapDataCount();++i)
    {
        MapConfig::MapData* pMap = theMapConfig.GetMapDataByIndex(i);
        if (NULL != pMap)
        {
            std::string Path = GetMonsterDataFilePath(pMap->GetMapFilePath());
            CStageDataLoader *MonsterConfig = new CStageDataLoader;
            if (!MonsterConfig->loadXMLSettings(Path.c_str()))
            {
                delete MonsterConfig;
                MonsterConfig = NULL;
                continue;
            }
            MosterConfigs.insert(MosterConfigContainer::value_type(Path,MonsterConfig));
        }
    }
    MonsterConfigOver = true;
    if (MosterConfigs.empty())
    {
        return false;
    }
    return true;
}

CGameBotApp::~CGameBotApp()
{
    while (!MosterConfigs.empty())
    {
        MosterConfigContainer::iterator itr = MosterConfigs.begin();
        CStageDataLoader *MonsterConfig = itr->second;
        if (NULL != MonsterConfig)
        {
            delete MonsterConfig;
            MonsterConfig = NULL;
        }
        MosterConfigs.erase(itr);
    }
    CloseHandle(hMapFile);
    //     while (!BinAStarPFs.empty())
    //     {
    //         BinAStarPFContainer::iterator itr = BinAStarPFs.begin();
    //         BinaryAStarPF* BinMap = itr->second;
    //         if (NULL != BinMap)
    //         {
    //             free(BinMap);
    //             BinMap = NULL;
    //         }
    //         BinAStarPFs.erase(itr);
    //     }
}

// bool CGameBotApp::LoadBinPathFinder()
// {
//     if (LoadBinAStarOver)
//     {
//         return true;
//     }
//     for (int i = 0 ;i<theMapConfig.MapDataCount();++i)
//     {
//         MapConfig::MapData* pMap = theMapConfig.GetMapDataByIndex(i);
//         if (NULL != pMap)
//         {
//             std::string Path = GetAStarDataFilePath(pMap->GetMapMonsterFilePath());
// 
//             CFile pFile;
//             BOOL IsOpen = pFile.Open(Path.c_str(),CFile::modeRead | CFile::typeBinary);
//             if (!IsOpen)
//             {
//                 // 打开对应的文件失败
//                 continue;
//             }
//             TileDataMapHeader head;
//             pFile.Read(&head,sizeof(TileDataMapHeader));
//             int MapSize = head.width * head.height;
//             BYTE* pMapBuffer = (BYTE*)malloc(MapSize*sizeof(BYTE)/8);
// 
//             BinaryAStarPF* pPathFinder = NULL;
//             if (head.version < 3)
//             {
//                 pMapBuffer = (BYTE*)malloc(MapSize*sizeof(BYTE)/8);
//                 pFile.Read(pMapBuffer, MapSize*sizeof(BYTE)/8);
// 
//                 // 创建AStarPathFinder
//                 pPathFinder = new BinaryAStarPF(pMapBuffer, head.width, head.height,true);
//             }
//             else
//             {
//                 pMapBuffer = (BYTE*)malloc(MapSize*sizeof(BYTE));
//                 pFile.Read(pMapBuffer, MapSize*sizeof(BYTE));
// 
//                 // 创建AStarPathFinder
//                 pPathFinder = new BinaryAStarPF(pMapBuffer, head.width, head.height);
//             }
// 
//             BinAStarPFs.insert(BinAStarPFContainer::value_type(Path,pPathFinder));
//         }
//     }
//     LoadBinAStarOver = true;
//     if (BinAStarPFs.empty())
//     {
//         return false;
//     }
//     return true;
// }

CMonsterConfig* CGameBotApp::GetMonsterConfig(std::string MapName)
{
    std::string FindMapName = GetMonsterDataFilePath(MapName);
    MosterConfigContainer::iterator itr = MosterConfigs.find(FindMapName);
    if (itr != MosterConfigs.end())
    {
        return itr->second->GetMonsterConfig();
    }
    return NULL;
}

SMapMonsterInfo* CGameBotApp::GetMonsterInfo(int MonsterId,int &MapId)
{
    if (MonsterId<=0)
        return NULL;

    for (int i = 0;i<theMapConfig.MapDataCount();++i)
    {
        MapConfig::MapData* pData = theMapConfig.GetMapDataByIndex(i);
        if (NULL != pData)
        {
            CMonsterConfig* pCMonsterConfig = GetMonsterConfig(pData->GetMapFilePath());
            if (NULL != pCMonsterConfig)
            {
                for (int MonsterIndex = 0;MonsterIndex < pCMonsterConfig->GetMonsterCount();++MonsterIndex)
                {
                    SMapMonsterInfo* pSMapMonsterInfo = pCMonsterConfig->GetMapMonsterInfo(MonsterIndex);
                    if (NULL != pSMapMonsterInfo&&pSMapMonsterInfo->m_nId == MonsterId)
                    {
                        MapId = pData->Id;
                        return pSMapMonsterInfo;
                    }
                }
            }
        }
    }
    return NULL;
}


// BinaryAStarPF* CGameBotApp::GetBinAStarFindMap(std::string MapName)
// {
//     std::string FindMapName = GetAStarDataFilePath(MapName);
//     BinAStarPFContainer::iterator itr = BinAStarPFs.find(FindMapName);
//     if (itr != BinAStarPFs.end())
//     {
//         return itr->second;
//     }
//     return NULL;
// }

//std::string CGameBotApp::GetAStarDataFilePath( const std::string& stageName )
//{
//    std::string strFilePath = STAGEROOTDIRECTORY;
//    strFilePath += "\\";
//    strFilePath += stageName;
//    strFilePath += "\\";
//    strFilePath += stageName;
//    strFilePath += ".map";
//    return strFilePath;
//}
#pragma warning ( pop )