#ifndef __CENTERSYSTEMVAR_H__
#define __CENTERSYSTEMVAR_H__
/************************************************************************/
/*          FileName:CenterSystemVar.h                                  */
/*          Author  :eliteYang                                          */
/*          Desc    :����ϵͳ������DBServer                             */
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
   
    void AddServerSysVar(SystemVar* pSysVar){ m_sysVarMap.insert(std::make_pair(pSysVar->GetServerId(), pSysVar));} // ���һ��������ϵͳ������Map
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
    sysVarMap m_sysVarMap;      // ����������ϵͳ����map
    sysVarSet m_sysVarSet;      // �洢ÿ��������ID
    GameTimerEx m_xLoadTimer;
    GameTimerEx m_xUpdateTimer; // ���µ�DBServer��ʱ��
    bool bLoadSuccess;          // �Ƿ���سɹ�
    bool bHaveSendLoadMessage;  // �Ƿ��ͼ�����Ϣ
};

#endif