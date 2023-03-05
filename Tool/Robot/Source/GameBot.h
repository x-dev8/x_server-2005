// GameBot.h : GameBot Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "../Resource/Resource.h"       // ������
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
// �йش����ʵ�֣������ GameBot.cpp
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

    // ��д
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

    // ʵ��
    afx_msg void OnAppAbout();
    afx_msg void NetworkMsgLog();

    virtual BOOL OnIdle(LONG lCount); // return TRUE if more idle processing
    virtual int Run();

    void PushMessage( SBaseGuiLogicMessage* pGuiMessage);
    void ProcessLogicMessage();
    void SetBotInfo(BaseRobot *pBot, const char* szTips); // �Ѿ����ù��ο�

protected:
    DECLARE_MESSAGE_MAP()
    
    void HandleLMsgRobotInfoChange( LMsgRobotInfoChange* pMessage );
    void HandleLMsgShowRobotinfo( LMsgShowRobotInfo* pMessage ); // �����߼��ı��MessageInfo��ʾ
    void HandleLMsgShowAllBotInfo( LMsgShowAllRobotInfo* pMessage ); // ������ʾ��������������ͼ�����꣬������Ϣ
    void HandleLMsgInitReady(LMsgInitReady* pMessage); // ������Դ������֮��ʹ�á���ӡ���ť����

public:
    BotApplication                       gBotApplication;         // �߼�Application
    CWorkThread                          mainLogicThread;         // �߼��߳�
    MsgStatistician                      m_xTatolMsgStatistician; // ȫ����ͳ����Ϣ
    bool                                 _firstShow;              // ��һ�γ�ʼ����ʾ    

    GuiLogicMessageContainer            _messages; // Logic2Ui��Ϣ����
    CSemiAutoIntLock                    _messageLock;
    Common::TAllocator<uint8, 1024 * 10, 100> _messageAlloc;

    //////////////////////////////////////////////////////////////////////////
    // δ����
public:    
    void ShowServerInfo();    
    void ShowBotInfo(int nID);
    void PrintStatLog(int nType, char* szFile);   //nType = 0 ����������  1 = ���л�����  szFile �ļ�·��        
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
    EctypeMapContainer FlyEctypeMapTableByPlayerNum; // ����Ҫ��ӵĸ���
    EctypeMapContainer FlyEctypeMapTableByTeam; // ��Ҫ��ӵĸ���

    typedef std::map<std::string,CStageDataLoader *> MosterConfigContainer; // ��ͼ���� , ����
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
    nIntMap BotListMap;//������¼�����˶��еĲ���λ��
    void SetOneBotChangedInfo(CListCtrl& xList, int nItem, int nSubItem, LMsgRobotInfoChange* pMessage);
private:
    int m_startItemNum;
};

extern CGameBotApp theApp;
extern int g_nLoginOnly;
extern int g_nReLogin;
extern int g_nDisableCheckTime;
