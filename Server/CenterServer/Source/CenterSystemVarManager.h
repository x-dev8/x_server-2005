#ifndef __CENTERSYSTEMVAR_H__
#define __CENTERSYSTEMVAR_H__
/************************************************************************/
/*          FileName:CenterSystemVar.h                                  */
/*          Author  :eliteYang                                          */
/*          Desc    :保存系统变量到DBServer                             */
/************************************************************************/
#include "GlobalDef.h"
#include "GameTimer.h"
#include "Singleton.h"
#include "SystemVarMessage.h"
#include "SystemVarDefine.h"

#define theCenterSysVarManager CenterSystemVarManager::Instance()

///////////////////////////////////////////////////////////////////////////////////
class CenterSystemVarManager : public ISingletion< CenterSystemVarManager >
{
public:
    CenterSystemVarManager();
    ~CenterSystemVarManager();
    void RunUpdate( uint32 nCurrentTime );
    void AutoSaveToDatabase();
   
    void AddServerSysVar(SystemVar* pSysVar){ m_sysVarMap.insert(std::make_pair(pSysVar->GetServerId(), pSysVar));} // 添加一个服务器系统变量到Map
    SystemVar* GetServerSysVar(uint32 serverId);
    void OnGS2CSSendChangeVarReq( GS2CSSendChangeVarReq* pMsg, uint32 serverId );
    void SendSysVarToGameServer(uint32 serverId);
    bool GetLoadSuccess() { return bLoadSuccess;}
    void SetLoadSuccess(bool bValue);
    void StartLoadTimer();
    void StopLoadTimer();
    void AutoAddToServerSet(uint32 nServerId) { m_sysVarSet.insert(nServerId);}
    void ClearAutoSaveToServerSet() { m_sysVarSet.clear();}
    bool NeedToAutoSave() { return !m_sysVarSet.empty(); }
protected:
    enum EConstDefine
    {
        ECD_UpdateLoadTime = 10000     ,
        ECD_UpdateSaveTime = 10 * 60 * 1000,
    };
    typedef std::map<uint32, SystemVar*> sysVarMap;
    typedef sysVarMap::iterator sysVarMapIter;
    typedef std::set<uint32> sysVarSet;
    typedef sysVarSet::iterator sysVarSetIter;

    void ProcessLoadSysVarData( unsigned int nCurrentTime );

private:
    sysVarMap m_sysVarMap;      // 各个服务器系统变量map
    sysVarSet m_sysVarSet;      // 存储每个服务器ID
    GameTimerEx m_xLoadTimer;
    GameTimerEx m_xUpdateTimer; // 更新到DBServer定时器
    bool bLoadSuccess;          // 是否加载成功
    bool bHaveSendLoadMessage;  // 是否发送加载消息
};

#endif