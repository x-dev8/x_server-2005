/********************************************************************
    Filename:     ScriptMgr.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_SCRIPTMGR_H__
#define __GAMESERVER_SCRIPTMGR_H__

#pragma once

#include "GlobalDef.h"
#include "ScriptVM.h"
#include "MapContainer.h"
#include "Mutex.h"
#include "GameTimer.h"

class GamePlayer;

struct SScript
{
    SScript() : nVarId(-1),nVar(-1)
    {}

    void SetVar( const int n ){ nVar = n; }
    
    CScriptVMThread thread;
    int             nVarId; // 变量的Key
    int             nVar  ; // SelItem 或者 QuestId
};

typedef std::list<SScript>         VMScriptContainer;
typedef VMScriptContainer::iterator ItrVMScriptContainer;

class CScriptMgr : public ::CSemiAutoIntLock
{
public:
    struct SScriptData
    {
        SScriptData(): vmId(-1), dwDstId(0)
        { }

        bool IsTime( const DWORD dwTime );
        bool IsDstId( const DWORD id ) { return dwDstId == id; }

        int         vmId;    // VMId
        std::string strFile; // 角本文件名
        DWORD       dwDstId; // 绑定的Id 可能是各种类型的子Id ItemId NpcId TimeId
    };

    typedef std::vector< SScriptData >    ScriptDataContainer;
    typedef ScriptDataContainer::iterator ScriptDataContainerItr;

    struct SScriptControl
    {
        ScriptDataContainer           vtScriptData[ST_MAX];
        CMapContainer<int,CScriptVM*> mapScriptVM; // Key 是 SScriptData->vmId

        int           GetScriptSize( EScriptType type );
        SScriptData*  GetScriptData( EScriptType type, unsigned int nIndex );
        void          AddScriptData( EScriptType type, SScriptData* pData );
        bool          RemoveScriptDataByDstId( EScriptType type, DWORD dwDstId );
        CScriptVM*    GetVM( const int nId );
    };

    struct SDelayTimeScript
    {
        DWORD          starttime;
        DWORD          delaytime;
        unsigned short script_index;
        DWORD          playerdbid;
    };

public:
    CScriptMgr();
    virtual ~CScriptMgr();

    bool      InitScripts();      // 初始化脚本
    bool      ReloadAllScripts(); // 重读脚本

    void      Run();           // Run
    int       CreateVM              ( EScriptType type, const char* szFileName, const int nDstId );
    bool      ReCreateVMByScriptData( const SScriptData& scriptData );

    bool      ReleaseVMByDstId( EScriptType type, DWORD dwDstId );
    bool      SetVMDstId      ( EScriptType type, const char* szFileName, const int nDstId );

    // 是否所有dwDstId的脚本都运行 脚本入口ID
    bool      StartupVM( EScriptType type, DWORD dwDstId, GamePlayer* pScriptControl, bool bAll = false, int nEnter = 1,int nNpcId = -1 );
    bool      ExecuteVM( EScriptType type, DWORD dwDstId, GamePlayer* pScriptControl) ;

    bool      RunTimeScript( EScriptType type,int nYear, int nMonth, int nDay, int nHour, int nMinute );
    bool      RunTimeScript( EScriptType type, DWORD dwTime );

    void      InsertDelayTime( SDelayTimeScript &p);
    void      RunDelayTime();
    bool      DelayRunScript( EScriptType type, DWORD dwdelaytime,int index,DWORD playerdbid = 0);
    bool      RemoveDelayScript(int scriptindex,DWORD playerdbid);

    SScriptControl* GetScriptControl(){ return &m_stScript; }
	SScriptData* GetVMByDstId( EScriptType type, DWORD dwDstId );

    static void CallQuestScript( QuestScript* pInfo, GamePlayer* pPlayer, int nNpcID );
	static void JoinQuestScript(GamePlayer* pPlayer,unsigned int QuestID);
	static void DoneQuestScript(GamePlayer* pPlayer,unsigned int QuestID);
public:
    bool         gbNeedReloadScript;

private:
    int          GetVMByName( EScriptType type, const char* szFileName );
    int          GetVMByName( const char* szFileName );
    //SScriptData* GetVMByDstId( EScriptType type, DWORD dwDstId ); to public by cloud
    SScriptData* GetVMByDstIdAndName( EScriptType type, const char* szFileName, DWORD dwDstId );

private:
    typedef std::vector<SDelayTimeScript>      DelayTimeScriptContainer;
    typedef DelayTimeScriptContainer::iterator ItrDelayTimeScriptContainer;

    DelayTimeScriptContainer g_delaytimescript;
    SScriptControl           m_stScript;
    DWORD                    m_dwLastId;
    GameTimerEx              _realTimeScriptTimeRecord; // 实时脚本时间记录
};

extern CScriptMgr* GetScriptMgr();

#endif // __GAMESERVER_SCRIPTMGR_H__
