#include "ScriptMgr.h"
#include "ScriptCompiler.h"
#include "ScriptAbstract.h" 
#include "FuncPerformanceLog.h"
#include "SlkReader.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "ResourcePath.h"
#include "RunningScriptControl.h"
#include "ScriptVarMgr.h"
#include "RapidXml/MeRapidXml.h"
#include "GamePlayer.h"

extern IScriptInterface* GetScriptInterface();

CScriptMgr* GetScriptMgr()
{
    static CScriptMgr mgr;
    return &mgr;
}

CScriptMgr::CScriptMgr()
{
    m_dwLastId = 0;
    gbNeedReloadScript = false;
}

CScriptMgr::~CScriptMgr()
{
}

bool CScriptMgr::SScriptData::IsTime( const DWORD dwTime )
{
    //年 月 日 时 分
    //F  F  FF FF FF

    BYTE byCurYear   = (dwTime>>28)&0xF;
    BYTE byCurMonth  = (dwTime>>24)&0xF;
    BYTE byCurDay    = (dwTime>>16)&0xFF;
    BYTE byCurHour   = (dwTime>>8)&0xFF;
    BYTE byCurMinute = (dwTime>>0)&0xFF;

    BYTE byYear   = (dwDstId>>28)&0xF;
    BYTE byMonth  = (dwDstId>>24)&0xF;
    BYTE byDay    = (dwDstId>>16)&0xFF;
    BYTE byHour   = (dwDstId>>8)&0xFF;
    BYTE byMinute = (dwDstId>>0)&0xFF;

    if ( byMinute != 0xFF && byMinute != byCurMinute )
    { return false;}

    if ( byHour != 0xFF && byHour != byCurHour )
    { return false; }

    if ( byDay != 0xFF && byDay != byCurDay )
    { return false; }

    if ( byMonth != 0xF && byMonth != byCurMonth )
    { return false; }

    if ( byYear != 0xF && byYear != byCurYear )
    { return false; }

    return true;
}

//////////////////////////////////////////////////////////////////////////
int CScriptMgr::SScriptControl::GetScriptSize( EScriptType type )
{
    if ( type < 0 || type >= ST_MAX )
    { return 0; }
    return vtScriptData[type].size();
}

CScriptMgr::SScriptData* CScriptMgr::SScriptControl::GetScriptData( EScriptType type, unsigned int nIndex )
{
    if ( nIndex >= vtScriptData[type].size() )
    { return NULL; }
    return &vtScriptData[type][nIndex];
}

void CScriptMgr::SScriptControl::AddScriptData( EScriptType type, SScriptData* pData )
{
    if ( type < 0 || type >= ST_MAX )
    { return; }
    vtScriptData[type].push_back( *pData );
}

bool CScriptMgr::SScriptControl::RemoveScriptDataByDstId( EScriptType type, DWORD dwDstId )
{
    if ( type < 0 || type >= ST_MAX )
    { return false; }

    SScriptData* pScriptData = NULL;
    for ( int n=0; n<vtScriptData[type].size(); n++ )
    {
        pScriptData = GetScriptData( type, n );
        if ( !pScriptData )
        {
            return false;
        }
        if( pScriptData->dwDstId == dwDstId )
        {
            vtScriptData[type].erase( vtScriptData[type].begin()+n );
            n = 0;
        }
    }
    return true;
}

CScriptVM* CScriptMgr::SScriptControl::GetVM( const int nId )
{
    return mapScriptVM.Find(nId);
}

bool CScriptMgr::RunTimeScript( EScriptType type, int nYear, int nMonth, int nDay, int nHour, int nMinute )
{
    CSALocker locker(this);
    DWORD dwTime = (nYear<<28)|(nMonth<<24)|(nDay<<16)|(nHour<<8)|(nMinute);
    int nSize = min(dr_worldMaxPlayers, theRunTimeData.theCharacters.GetSize());
    for( int i=0; i<nSize; i++ )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( i );
        if( !pChar || !pChar->IsPlayer() )
            continue;

        GamePlayer* pPlayer = (GamePlayer*)pChar;
        if( !StartupVM( type, dwTime, pPlayer, true ) )
            break;

        break;
    }
    return true;
}

bool CScriptMgr::RunTimeScript( EScriptType type, DWORD dwTime )
{
    int nSize = min(dr_worldMaxPlayers, theRunTimeData.theCharacters.GetSize());
    for( int i=0; i<nSize; i++ )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( i );
        if( !pChar || !pChar->IsPlayer() )
            continue;

        GamePlayer* pPlayer = (GamePlayer*)pChar;
        if( !StartupVM( type, dwTime, pPlayer, true ) )
            break;

        break;
    }
    return true;
}

void CScriptMgr::Run()
{
    CSALocker locker(this);

    // 定时脚本
    _realTimeScriptTimeRecord.StartTimer( HQ_TimeGetTime(), 60000 );
    if ( _realTimeScriptTimeRecord.DoneTimer( HQ_TimeGetTime() ) )
    {
        std::time_t t = std::time( NULL );
        std::tm* tme  = std::localtime( &t );
        uint8 year    = tme->tm_year - 100;
        uint8 month   = tme->tm_mon + 1;
        uint8 day     = tme->tm_mday;
        uint8 hour    = tme->tm_hour;
        uint8 minute  = tme->tm_min;

        RunTimeScript( ST_REAL_TIME, year, month, day, hour, minute );
    }
}

bool CScriptMgr::SetVMDstId( EScriptType type, const char* szFileName, const int nDstId )
{
    CSALocker locker(this);
    if ( !szFileName || szFileName[0] == 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CScriptMgr::SetVMDstId( %d, %s, %d ) error",type, szFileName, nDstId );
        return false;
    }

    SScriptData *pScriptData = NULL;
    int nSize = m_stScript.GetScriptSize( type );
    for( int n=0; n<nSize; n++ )
    {
        pScriptData = m_stScript.GetScriptData( type, n );
        if ( pScriptData->strFile == szFileName )
        {
            pScriptData->dwDstId = nDstId;
            return true;
        }
    }
    return false;
}

bool CScriptMgr::ReleaseVMByDstId( EScriptType type, DWORD dwDstId )
{
    CSALocker locker(this);
    return m_stScript.RemoveScriptDataByDstId( type, dwDstId );
}

int CScriptMgr::CreateVM( EScriptType type, const char* szFileName, const int nDstId )
{
    CSALocker locker(this);

    if ( !szFileName || szFileName[0] == 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CScriptMgr::CreateVM( %d, %s, %d ) error",type, szFileName, nDstId );
        return -1;
    }

    bool bNotPointerDstIdButGetDst = false; // 应用层传了-1，在队列中找到了可以用的
    int nActiveDstId = -1;
    if ( nDstId == -1 ) // 因为 pScriptData->dwDstId 的算法是 应用层为-1时，会主动把vmId赋给它
    { // 应用层不理会具体值
        nActiveDstId = GetVMByName( type, szFileName ); // 拿到VMId 有可能有值 有可能为-1 查找是否已经有了
        if ( nActiveDstId != -1)
        { bNotPointerDstIdButGetDst = true; }
    }
    else
    {
        nActiveDstId = nDstId;
    }

    int vmId = -1;
    if ( nActiveDstId != -1 )
    {
        // 查找是否有可用的VmId 根据 type, szFileName, nActiveDstId
        SScriptData* pScriptData = GetVMByDstIdAndName( type, szFileName, nActiveDstId );
        if ( pScriptData)
        { return pScriptData->vmId; }

        if ( bNotPointerDstIdButGetDst )
        { // 找到了居然这里没有找到
            assert( false );
        }

        // 查找是否有可用的VmId 根据 type, szFileName
        vmId = GetVMByName( type, szFileName );
    }

    // 查找是否有可复用的VM
    if ( vmId == -1 )
    {
        CScriptCompiler compiler;
        CScriptVM* pVM = compiler.CreateVM( szFileName );
        if ( !pVM )
        { return -1;}

        vmId = m_dwLastId++;
        m_stScript.mapScriptVM.Add( vmId, pVM );
    }

    SScriptData stScriptData;
    stScriptData.strFile = szFileName;
    stScriptData.vmId = vmId;
    switch( type )
    {
    case ST_REAL_TIME:
    case ST_GAME_TIME:
        { stScriptData.dwDstId = nDstId; }
        break;
    default:
        if ( nDstId != -1 )
        { 
            stScriptData.dwDstId = nDstId; 
        }
        else
        { 
            stScriptData.dwDstId = vmId;
        }
        break;
    }
    m_stScript.AddScriptData( type, &stScriptData );
    return vmId;
}

bool CScriptMgr::ReCreateVMByScriptData( const SScriptData& scriptData )
{
    CScriptCompiler compiler;
    CScriptVM* pVM = compiler.CreateVM( scriptData.strFile.c_str() );
    if ( NULL == pVM )
    { 
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ReCreateVMByScriptData(%s) Fail", scriptData.strFile.c_str() );
        return false;
    }

    BOOL bResult = m_stScript.mapScriptVM.Add( scriptData.vmId, pVM );
    if ( !bResult )
    { 
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ReCreateVMByScriptData(%s) Add Fail", scriptData.strFile.c_str() ); 
        return false;
    }

    return true;
}

bool CScriptMgr::ReloadAllScripts()
{
    CSALocker locker(this);
    GetScriptVarMgr()->Reset();

    m_stScript.mapScriptVM.Destroy();
    // 优先加载全局脚本
    const DWORD globalVariableDstId = 10000;
    SScriptData* pScriptData = GetVMByDstId( ST_USE_ITEM, globalVariableDstId );
    if ( pScriptData == NULL )
    { return false; }

    if ( !ReCreateVMByScriptData( *pScriptData ) )
    { return false; }

    // 加载所有的
    for( int type=0; type<ST_MAX; ++type )
    {
        int nSize = m_stScript.GetScriptSize( (EScriptType)type );
        for( int n=0; n<nSize; ++n )
        {
            pScriptData = m_stScript.GetScriptData( (EScriptType)type, n );
            if ( NULL == pScriptData)
            { continue; }
            
            CScriptVM* pScriptVM = m_stScript.mapScriptVM.Find( pScriptData->vmId );
            if ( pScriptVM != NULL )
            { continue; }
            
            if ( !ReCreateVMByScriptData( *pScriptData ) )
            {
                 LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ReloadAllScripts(%s) Add Fail", pScriptData->strFile.c_str() );
                 continue;
            }
        }
    }

    return true;
}

bool CScriptMgr::InitScripts()
{
    CSALocker locker(this);

    MeXmlDocument MeXmlDoc;
    if ( !MeXmlDoc.LoadFile(SCRIPTCONFIG_FILEPATH) )
    {
        LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s read failed!", SCRIPTCONFIG_FILEPATH);
        return false;
    }

    MeXmlElement* pRoot = MeXmlDoc.FirstChildElement("Project");
    if (pRoot == NULL)
    { return false;}

    MeXmlElement* pSUseItems = pRoot->FirstChildElement("ScriptUseItems");
    if (pSUseItems == NULL)
    { return false;}

    MeXmlElement* pSUseItem = pSUseItems->FirstChildElement("ScriptUseItem");
    if (pSUseItem == NULL)
    { return NULL;}

    while (pSUseItem != NULL)
    {
        int nItemId;
        pSUseItem->Attribute("ItemId", &nItemId);

        Common::_tstring strFileName;
        strFileName.fromUTF8( pSUseItem->Attribute("FileName") );

        CreateVM( ST_USE_ITEM, strFileName.c_str(), nItemId );
        pSUseItem = pSUseItem->NextSiblingElement();
    }

    MeXmlElement* pSLevelUps = pRoot->FirstChildElement("ScriptLevelUps");
    if (pSLevelUps == NULL)
    { return false;}

    MeXmlElement* pSLevelUp = pSLevelUps->FirstChildElement("ScriptLevelUp");
    if (pSLevelUp == NULL)
    { return false;}

    while (pSLevelUp != NULL)
    {
        int nLevel;
        pSLevelUp->Attribute("Level", &nLevel);

        Common::_tstring strFileName;
        strFileName.fromUTF8(pSLevelUp->Attribute("FileName"));

        CreateVM(ST_LEVELUP, strFileName.c_str(), nLevel);
        pSLevelUp = pSLevelUp->NextSiblingElement();
    }

    MeXmlElement* pSTimes = pRoot->FirstChildElement("ScriptTimes");
    if (pSTimes == NULL)
    { return false;}

    MeXmlElement* pSTime = pSTimes->FirstChildElement("ScriptTime");
    if (pSTime == NULL)
    { return false;}

    while (pSTime != NULL)
    {
        int nGameType;
        int nYear = -1, nMonth = -1, nDay = -1, nHour = -1, nMinute = -1;
        DWORD dwTime;

        pSTime->Attribute("TimeType", &nGameType);
        pSTime->Attribute("Year", &nYear);
        pSTime->Attribute("Month", &nMonth);
        pSTime->Attribute("Day", &nDay);
        pSTime->Attribute("Hour", &nHour);
        pSTime->Attribute("Minute", &nMinute);

        Common::_tstring strFileName;
        strFileName.fromUTF8(pSTime->Attribute("FileName"));

        if ( nYear == -1 ) 
        { nYear = 0xF;}

        if ( nMonth == -1 ) 
        { nMonth = 0xF; }

        if ( nDay == -1 )
        { nDay = 0xFF; }

        if ( nHour == -1 ) 
        { nHour = 0xFF; }

        if ( nMinute == -1 )
        { nMinute = 0xFF; }

        dwTime = (nYear<<28) | (nMonth<<24) | (nDay<<16) | (nHour<<8) | (nMinute);

        if ( nGameType == 0 )
        { CreateVM( ST_REAL_TIME, strFileName.c_str(), dwTime ); }
        else
        { CreateVM( ST_GAME_TIME, strFileName.c_str(), dwTime ); }

        pSTime = pSTime->NextSiblingElement();
    }

    CreateVM( ST_ONLINE, SCRIPT_PLAYERONLINE_FILEPATH, 0 );
    CreateVM( ST_OFFLINE, SCRIPT_PLAYEROFFLINE_FILEPATH, 0 );    
    CreateVM( ST_CREATE_CHAR, SCRIPT_CREATEPLAYER_FILEPATH, 0 );    
    CreateVM( ST_CHAR_DEAD, SCRIPT_PLAYERDEAD_FILEPATH, 0 );
    //CreateVM( ST_GRAPHICCODE_CHECKRIGHT, SCRIPT_GRAPHICCODECHECKRIGHT_FILEPATH, 0);    
    CreateVM( ST_CHALLENGE, SCRIPT_CHALLENGE_FILEPATH, 0);    
    CreateVM( ST_MARRIAGE, SCRIPT_MARRIAGE_FILEPATH, 0);
    //CreateVM( ST_PKBATTLE, SCRIPT_PKBATTLE_FILEPATH, 1);
    //CreateVM( ST_PKBATTLE, SCRIPT_PKBATTLE_FILEPATH, 2);
    CreateVM( ST_TEAMBATTLER, SCRIPT_TEAMBATTLE_FILEPATH, 0 );
    //CreateVM( ST_LEAVEGUILD, SCRIPT_LEAVEGUILD_FILEPATH, 0 );
    CreateVM( ST_TEACHERSTUDENT, SCRIPT_TEACHERSTUDENT_FILEPATH, 0);
	CreateVM( ST_CHAR_KILLCHAR, SCRIPT_KILLCHAR_FILEPATH, 0);
	
   

    MeXmlElement* pSDelayTimes = pRoot->FirstChildElement("ScriptDelayTimes");
    if (pSDelayTimes == NULL)
    { return false;}

    MeXmlElement* pSDelayTime = pSDelayTimes->FirstChildElement("ScriptDelayTime");
    if (pSDelayTime == NULL)
    { return false;} 

    while (pSDelayTime != NULL)
    {
        int nScriptId;
        pSDelayTime->Attribute("ScriptId", &nScriptId);

        Common::_tstring strFileName;
        strFileName.fromUTF8(pSDelayTime->Attribute("ScriptFile"));

		/*
		 * Author: 2012-9-17 16:43:22 wangshuai
		 * Desc:   此处不拼路径了
		 */
        //std::string strScriptPath = SCRIPT_ROOTDIRECTORY;
        //strScriptPath += strFileName;
        CreateVM(ST_DelayTime, strFileName.c_str(), nScriptId);

        pSDelayTime = pSDelayTime->NextSiblingElement();
    }
    // 将读取SLK换成读取Config
    // 暂时先加一个保存方法，将SLK转为Config
    //SaveScriptFile(SCRIPTCONFIG_FILEPATH);

    return true;
}

CScriptMgr::SScriptData* CScriptMgr::GetVMByDstId( EScriptType type, DWORD dwDstId )
{
    int nSize = m_stScript.GetScriptSize( type );
    SScriptData* pReturn = NULL;
    int nCount = -1;
    bool bFound = false;
    for ( int n=0; n<nSize; n++ )
    {
        SScriptData *pScriptData = NULL;
        pScriptData = m_stScript.GetScriptData( type, n );
        switch( type )
        {
        case ST_REAL_TIME:
        case ST_GAME_TIME:
            bFound = pScriptData->IsTime( dwDstId );
            break;
        default:
            bFound = pScriptData->IsDstId( dwDstId );
            break;
        }
        if( bFound )
        {
            pReturn = pScriptData;
            break;
        }
    }
    return pReturn;
}

CScriptMgr::SScriptData* CScriptMgr::GetVMByDstIdAndName( EScriptType type, const char* szFileName, DWORD dwDstId )
{
    int nSize = m_stScript.GetScriptSize( type );
    SScriptData* pReturn = NULL;
    int nCount = -1;
    bool bFound = false;
    for ( int n=0; n<nSize; n++ )
    {
        SScriptData* pScriptData = m_stScript.GetScriptData( type, n );
        switch( type )
        {
        case ST_REAL_TIME:
        case ST_GAME_TIME:
            if ( pScriptData->IsTime( dwDstId ) && _stricmp(pScriptData->strFile.c_str(), szFileName ) == 0 )
            { 
                bFound = true;
            }
            break;
        default:
            if ( pScriptData->IsDstId( dwDstId ) && _stricmp(pScriptData->strFile.c_str(), szFileName ) == 0)
            {
                bFound = true;
            }
            break;
        }

        if( bFound )
        { 
            pReturn = pScriptData;
            break;
        }
    }
    return pReturn;

}

int CScriptMgr::GetVMByName( EScriptType type, const char* szFileName )
{   
    int size = m_stScript.GetScriptSize( type );
    for( int i=0; i<size; ++i )
    {
        SScriptData* pScriptData = m_stScript.GetScriptData( type, i );
        if ( _stricmp( pScriptData->strFile.c_str(), szFileName) == 0 )
        { return pScriptData->vmId; }
    }
    return -1;
}

int CScriptMgr::GetVMByName( const char* szFileName )
{   
    for( int type=0; type<ST_MAX; ++type )
    {
        int vmId = GetVMByName( (EScriptType)type, szFileName );
        if ( vmId != -1 )
        { return vmId; }
    }
    return -1;
}

bool CScriptMgr::StartupVM( EScriptType type, DWORD dwDstId, GamePlayer* pControl, bool bAll, int nEnter, int nDstId )
{
    CSALocker locker(this);

    if ( NULL == pControl )
    { return false; }

    // 此玩家是否有脚本在运行中
    bool bScriptRunning = (pControl->GetScript() != NULL);

    int nSize = m_stScript.GetScriptSize( type );
    SScriptData* pScriptData = NULL;
    int nCount = -1;
    bool bFound = false;
    for ( int n=0; n<nSize; ++n )
    {
        pScriptData = m_stScript.GetScriptData( type, n );
        switch( type )
        {
        case ST_REAL_TIME:
        case ST_GAME_TIME:
            bFound = pScriptData->IsTime( dwDstId );
            break;
        default:
            bFound = pScriptData->IsDstId( dwDstId );
            break;
        }

        if( bFound )
        {
            SScript stScript;
            stScript.thread.CreateId();
            stScript.thread.SetVM( m_stScript.GetVM( pScriptData->vmId ) );
            //stScript.thread.SetIdType( pControl->GetOwnerType() );
            stScript.thread.SetCharId( pControl->GetID() );
            stScript.thread.SetDstId( nDstId );     // 
            stScript.thread.SetScriptType( type );
            if( stScript.thread.SetEntrance( nEnter ) )
            { nCount = pControl->PushScript( &stScript ); }
            else
            { LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script can`t find proc_start %d npcid = %d", nEnter, nDstId );}

            if ( !bAll )
            { break; }
        }
    }

    if ( bScriptRunning == false && nCount >= 1 )
    { ExecuteVM( type, dwDstId, pControl ); }

    return (nCount != -1);
}

bool CScriptMgr::ExecuteVM( EScriptType type, DWORD dwDstId, GamePlayer* pControl )
{
    CSALocker locker(this);

    if ( !pControl )
    { return false;}

    SScript* pScript = pControl->GetScript();

    if ( !pScript || !pScript->thread.GetVM() )
    {
        if( pControl->PopScript() == true )
        {
            ExecuteVM( type, dwDstId, pControl );
        }
        return false;
    }

    if ( pScript->thread.IsHangup() )
    {
        if ( pScript->nVarId != -1 )
        {
            CScriptCmd__SetVar::Param m_params[1];
            m_params[0].SetNumber( pScript->nVar );
            GetScriptInterface()->SetCurCharId( pControl->GetID() );
            GetScriptInterface()->SetVar( pScript->nVarId, SKW_SET, m_params, 1 );
        }
        pScript->nVarId = -1;
    }

    if( !pScript->thread.Restore() )
    {
        SScriptData* pErr = GetVMByDstId( type, dwDstId );
        if ( pErr != NULL )  // 执行失败, 打一条注释
        { LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script %s:%d:%u GetScriptData Fail", pErr->strFile.c_str(),type, dwDstId ); }

        pScript->thread.Reset();
        if( pControl->PopScript() == true )
        {
            ExecuteVM( type, dwDstId, pControl );
        }
        return false;
    }
    else
    {
        if( pScript->thread.GetState() == CScriptVM::ERunState_RETURN )
        {
            pScript->thread.Reset();
            if( pControl->PopScript() == true )
            {  ExecuteVM( type, dwDstId, pControl ); }
            else
            {
                switch ( type )
                {
                case ST_NPC:
                case ST_QUEST:
                case ST_CANCELQUEST:
                case ST_GUIDEQUEST:
                case ST_UNKNOW:
                    {
                        GamePlayer* pGamePlayer = (GamePlayer* )pControl;
                        MsgScriptEnd msgScriptEnd;
                        msgScriptEnd.type = type;
                        GettheServer().SendMsgToSingle( &msgScriptEnd, pGamePlayer );
                    }
                	break;
                }
                //if ( pControl->GetOwnerType() == RunningScriptControl::EOwnerType_GamePlayer)
                //{ 
                //}
            }
        }
        return true;
    }
}

bool CScriptMgr::DelayRunScript(EScriptType type, DWORD dwdelaytime,int index,DWORD playerdbid)
{
    CSALocker locker(this);
    DWORD dwTime = dwdelaytime;
    int nSize = min(dr_worldMaxPlayers, theRunTimeData.theCharacters.GetSize());
    /*for( int i=0; i<nSize; i++ )*/
    {
        BaseCharacter* pChar = NULL;

        if (playerdbid == 0)
        {
            for( int i=0; i<nSize; i++ )
            {
                pChar = theRunTimeData.GetCharacterByID( i );
                if (pChar&&pChar->IsPlayer())
                    break;
            }
        }
        else
        {
            pChar = theRunTimeData.GetGamePlayerByDBID(playerdbid);
            if( !pChar || !pChar->IsPlayer() )
                return false;
        }

        if ( pChar == NULL )
        { return false; }

        GamePlayer* pPlayer = (GamePlayer*)pChar;
        StartupVM( type, index, pPlayer, true );
    }
    return true;
}

void CScriptMgr::RunDelayTime()
{
    CSALocker locker(this);
    if ( g_delaytimescript.empty())
    { return; }

    DWORD dwnowtime = HQ_TimeGetTime();
    ItrDelayTimeScriptContainer itr = g_delaytimescript.begin();
    for(;itr != g_delaytimescript.end();)
    {
        if (dwnowtime - itr->starttime >= itr->delaytime)
        {
            DelayRunScript(ST_DelayTime, itr->delaytime,itr->script_index,itr->playerdbid);
            itr = g_delaytimescript.erase(itr);
            continue;
        }
        ++itr;
    }
}

void CScriptMgr::InsertDelayTime(SDelayTimeScript &p)
{
    CSALocker locker(this);
    g_delaytimescript.push_back(p);
}

bool CScriptMgr::RemoveDelayScript(int scriptindex,DWORD playerdbid)
{
    CSALocker locker(this);
    ItrDelayTimeScriptContainer itr = g_delaytimescript.begin();
    for(;itr != g_delaytimescript.end();)
    {
        if (itr->playerdbid == playerdbid && itr->script_index == scriptindex)
        {
            g_delaytimescript.erase(itr);
            return true;
        }
    }
    return false;
}

void CScriptMgr::CallQuestScript( QuestScript* pInfo, GamePlayer* pPlayer, int nNpcID )
{
    if ( pInfo == NULL )
    { return; }

    char pszFilename[MAX_PATH] = {0};
    sprintf_s( pszFilename, sizeof(pszFilename)-1, QUESTS_SCRIPT_FILEPATH_FORMAT, pInfo->stQuestId );
    if ( pInfo->m_nVMId == -1 )
    { pInfo->m_nVMId = GetScriptMgr()->CreateVM( ST_QUEST, pszFilename, -1 ); }

    if ( pInfo->m_nVMId == -1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "调用[%s]任务脚本失败", pszFilename );
        return;
    }

    GetScriptMgr()->StartupVM( ST_QUEST, pInfo->m_nVMId, pPlayer, false, pInfo->stEnter, nNpcID );
}
void CScriptMgr::JoinQuestScript(GamePlayer* pPlayer,unsigned int QuestID)
{
	char pszFilename[MAX_PATH] = {0};
    sprintf_s( pszFilename, sizeof(pszFilename)-1, QUESTS_SCRIPT_FILEPATH_FORMAT,QuestID);
	int VMID = GetScriptMgr()->CreateVM( ST_QUEST, pszFilename, -1 );
	if ( VMID == -1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "调用[%s]任务脚本失败", pszFilename );
        return;
    }

	GetScriptMgr()->StartupVM( ST_QUEST, VMID, pPlayer, false,1, -1 );
}
void CScriptMgr::DoneQuestScript(GamePlayer* pPlayer,unsigned int QuestID)
{
	char pszFilename[MAX_PATH] = {0};
    sprintf_s( pszFilename, sizeof(pszFilename)-1, QUESTS_SCRIPT_FILEPATH_FORMAT,QuestID);
	int VMID = GetScriptMgr()->CreateVM( ST_QUEST, pszFilename, -1 );
	if ( VMID == -1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "调用[%s]任务脚本失败", pszFilename );
        return;
    }
	GetScriptMgr()->StartupVM( ST_QUEST, VMID, pPlayer, false,2, -1 );
}