// GameBot.h : GameBot 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "../Resource/Resource.h"       // 主符号
#include "BotApplication.h"
#include "MapConfig.h"
#include "MsgStatistician.h"
#include "StageDataLoader.h"
#include "MonsterConfig.h"
#include "NetworkInput.h"
#include <map>
#include "NpcInfo.h"
#pragma warning(disable:4239) // close  nonstandard extension used

#define ERROR_LOG_PATH "Error Log"
#define MESSAGE_FILE_PATH "MsgLog"

// CGameBotApp:
// 有关此类的实现，请参阅 GameBot.cpp
class CGameBotApp : public CWinApp
{
public:
    struct SEctypeMap 
    {
        int     EctyprMapID;
        float   EnterMapX;
        float   EnterMapY;

        SEctypeMap()
        {
            Reset();
        }

        void Reset()
        {
            EctyprMapID = -1;
            EnterMapX = 0.0;
            EnterMapY = 0.0;
        }
    };
    typedef std::vector<CGameBotApp::SEctypeMap> EctypeMaps;
    typedef std::map<int,EctypeMaps>             EctypeMapContainer;
    typedef EctypeMapContainer::iterator         ItrEctypeMapContainer;

public:
    CGameBotApp();
    ~CGameBotApp();

    // 重写
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

    // 实现
    afx_msg void OnAppAbout();
    afx_msg void NetworkMsgLog();

    virtual BOOL OnIdle(LONG lCount); // return TRUE if more idle processing
    virtual int Run();

    void PushMessage( SBaseGuiLogicMessage* pGuiMessage);
    void ProcessLogicMessage();
    void SetBotInfo(BaseRobot *pBot, const char* szTips); // 已经不用供参考

protected:
    DECLARE_MESSAGE_MAP()
    
    void HandleLMsgRobotInfoChange( LMsgRobotInfoChange* pMessage );
    void HandleLMsgShowRobotinfo( LMsgShowRobotInfo* pMessage ); // 处理逻辑改变后MessageInfo显示
    void HandleLMsgShowAllBotInfo( LMsgShowAllRobotInfo* pMessage ); // 处理显示机器人数量，地图，坐标，错误信息
    void HandleLMsgInitReady(LMsgInitReady* pMessage); // 处理资源加载完之后使得“添加”按钮可用

public:
    BotApplication                       gBotApplication;         // 逻辑Application
    CWorkThread                          mainLogicThread;         // 逻辑线程
    MsgStatistician                      m_xTatolMsgStatistician; // 全部的统计信息
    bool                                 _firstShow;              // 第一次初始化显示    

    GuiLogicMessageContainer            _messages; // Logic2Ui消息队列
    CSemiAutoIntLock                    _messageLock;
    Common::TAllocator<uint8, 1024 * 10, 100> _messageAlloc;

    //////////////////////////////////////////////////////////////////////////
    // 未整理
public:    
    void ShowServerInfo();    
    void ShowBotInfo(int nID);
    void PrintStatLog(int nType, char* szFile);   //nType = 0 单个机器人  1 = 所有机器人  szFile 文件路径        
    void ShowErrorInformation(int nBotID, char *szAccount, int nMsgType, int nMsgFlag, int nMsgLength, char *szErrorInfo, char *szErrorFile);
    void ShowBotCountInformation(int nTotalCount, int nOnlineCount, int nAttackCount, int nMoveCount, int nTotalMonsterNum);
    void ShowBotMapDistributing(map<string, int> &mapDistributing);
    void ShowBigMap();
    void SetText(CWnd& xWnd, char *pszFormat, ...);	
    int  GetInt(CWnd& xWnd, int nDef);
    void SetListItemText(CListCtrl& xList, int nItem, int nSubItem, char *pszFormat, ...);
    int  GetListItemInt(CListCtrl &xList,int nItem, int nSubItem,int nDef);
    int  GetListCtrlCurSel(CListCtrl &xList);
    void EditAttackAreaInfo(SAreaInfo *xpAreaInfo, int nCount);
    void DisPerseBot(char* pszMap, int nCount);
    void ReadAllScript(const char* pszPath, CComboBox &xComboBox, vector<string> &vecScript = vector<string>());
    void LoadScript(const char* pszFile, vector<SAddInfo> &vecAddInfo);
    void SaveScript(const char* pszFile, vector<SAddInfo> &vecAddInfo);
    void UpdataAddFrmScriptCombox();
    bool LoadMonsterFile();
    bool LoadBinPathFinder();    
    CMonsterConfig* GetMonsterConfig(std::string MapName);
    SMapMonsterInfo* GetMonsterInfo(int MonsterId,int &MapId);

    /*BinaryAStarPF* GetBinAStarFindMap(std::string MapName);*/
    //std::string GetAStarDataFilePath( const std::string& stageName );

    int  LoadFileMappingNum();
    bool  WriteFileMappingNum(int Num);

public:
    EctypeMapContainer FlyEctypeMapTableByPlayerNum; // 不需要组队的副本
    EctypeMapContainer FlyEctypeMapTableByTeam; // 需要组队的副本

    typedef std::map<std::string,CStageDataLoader *> MosterConfigContainer; // 地图名字 , 配置
    MosterConfigContainer MosterConfigs;

    //typedef std::map<std::string ,BinaryAStarPF*> BinAStarPFContainer;
    //BinAStarPFContainer BinAStarPFs;

    bool     LoadBinAStarOver;
    bool     MonsterConfigOver;

    bool     bAttack;

    LPCTSTR  pMappingBuf;
    HANDLE hMapFile;

    typedef map<int, int> nIntMap;
    typedef nIntMap::iterator nIntMapIter;
    nIntMap BotListMap;//用来记录机器人队列的插入位置
    void SetOneBotChangedInfo(CListCtrl& xList, int nItem, int nSubItem, LMsgRobotInfoChange* pMessage);
private:
    int m_startItemNum;
};

extern CGameBotApp theApp;
extern int g_nLoginOnly;
extern int g_nReLogin;
extern int g_nDisableCheckTime;
