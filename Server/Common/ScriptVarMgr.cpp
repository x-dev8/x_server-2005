#include "ScriptVarMgr.h"
#include "ScriptKeyWord.h"
#include "WordParser.h"
#include "DataChunkMgr.h"
#include "FuncPerformanceLog.h"

#define DCSID_SERVERGUI		0xe3574da, 0x86847fa
#define DCID_SCRIPT			0x75bb7af0, 0x26a46884

#pragma warning ( push )
#pragma warning ( disable : 4311 )

CScriptVarMgr* GetScriptVarMgr()
{
    static CScriptVarMgr mgr;
    return &mgr;
}

CScriptVarMgr::CScriptVarMgr()
{
    LoadVar();
}

CScriptVarMgr::~CScriptVarMgr()
{
    //SaveVar();
}

bool CScriptVarMgr::LoadVar()
{
    CDataChunkMgr* pDataMgr   = NULL;
    CAppDataChunk* pDataChunk = NULL;
    pDataMgr   = GetDataChunkMgr();
    pDataChunk = pDataMgr->GetAppDataChunk( CAppDataChunkClassID(DCID_SCRIPT), CAppDataChunkClassID(DCSID_SERVERGUI), 0 );
    if ( !pDataChunk )
        return false;
    if( pDataChunk->m_dwLength == sizeof(m_stSysVar) )
    { memcpy( &m_stSysVar, pDataChunk->m_pbyData, sizeof(m_stSysVar) ); }
    else
    { MessageBox( NULL, "Script global variable data structure changed.", "Warning", MB_OK | MB_ICONWARNING );}

    return true;
}

void CScriptVarMgr::SaveVar()
{
    CDataChunkMgr *pDataMgr = NULL;
    pDataMgr = GetDataChunkMgr();
    pDataMgr->RemoveAppDataChunk( CAppDataChunkClassID(DCID_SCRIPT), 
        CAppDataChunkClassID(DCSID_SERVERGUI), 
        0 );
    pDataMgr->AddAppDataChunk( CAppDataChunkClassID(DCID_SCRIPT), 
        CAppDataChunkClassID(DCSID_SERVERGUI), 
        0,
        sizeof(m_stSysVar),
        &m_stSysVar );
}

CScriptVarMgr::E_VarType CScriptVarMgr::GetKeyType( const char* szVar )
{
    if ( szVar[0] != '$' )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script lawless variable [%s]", szVar );
        return VT_ERROR;
    }
    // $g_var
    if ( strlen(szVar) >= 4 &&
        szVar[1] == 'g' &&
        szVar[2] == '_' )
    {
        return VT_SYS;
    }
    return VT_TEMP;
}

void CScriptVarMgr::Reset()
{
    m_str2IdTemp.Destroy();
    m_str2IdSys.Destroy();
    m_stSysVar.Reset();
}

int CScriptVarMgr::Register( const char* pszName, int nDefault )
{
    E_VarType type;
    type = GetKeyType( pszName );
    int nId = -1;
    switch( type ) 
    {
    case VT_TEMP:
        {
            nId = (int)m_str2IdTemp.GetDstByName(pszName);
            if ( nId != 0 )
            { return nId; }

            static int nLastTempId = VAR_CHAR_MAX;
            if ( nLastTempId >= VAR_TEMP_MAX )
            { return -1; }

            nId = nLastTempId;
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_INFO, "Create temporary variable %s(%d) ", pszName, nId );

            m_str2IdTemp.Register( pszName, nLastTempId++ );
        }
        break;
    case VT_SYS:
        {
            nId = (int)m_str2IdSys.GetDstByName(pszName);
            if ( nId != 0 )
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script the global variable is already be. %s", pszName );
                return -1;
            }
            nId = m_stSysVar.GetKeyByName( pszName );
            if ( nId == -1 )
            {
                if ( m_stSysVar.nLastID >= VAR_SYS_MAX )
                {
                    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script the global variable is too many. " );
                    return -1;
                }
                if ( strlen(pszName) >= SystemVarDefine::NAME_LENGTH )
                {
                    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script variable name is too long, %s", pszName );
                    return -1;
                }

                nId = m_stSysVar.nLastID++;
                SStrVar *pVar = m_stSysVar.GetByKey( nId );
                if ( pVar )
                {
                    strncpy_s( pVar->szName, sizeof(pVar->szName), pszName, sizeof(pVar->szName)-1 );
                    pVar->nVar = nDefault;
                }
                else
                {
                    return -1;
                }
            }
            m_str2IdSys.Register( pszName, nId );

            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_INFO, "Create global variable,%s(%d)=%d", pszName, nId, m_stSysVar.stStrVars[nId-VAR_TEMP_MAX].nVar );
        }
        break;
    default:
        break;
    }
    return nId;
}

int CScriptVarMgr::GetVarId( const char* pszName )
{
    int nKey = 0;
    if ( WordParser::IsNumber( pszName ) )
    {
        nKey = atoi( pszName );
    }
    else
    {
        nKey = g_skwMgr.GetKeyWord( pszName );
        if ( nKey != -1 )
            return nKey;
        E_VarType type;
        type = GetKeyType( pszName );
        switch( type ) 
        {
        case VT_TEMP:
            nKey = (int)m_str2IdTemp.GetDstByName(pszName);
            break;
        case VT_SYS:
            nKey = (int)m_str2IdSys.GetDstByName(pszName);
            break;
        }
        if ( nKey <= 0 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script can`t find variable[%s] ", pszName );
            return -1;
        }
    }
    if ( nKey > 0x7fff || nKey < 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script variable is slop over,%s", pszName );
    }
    return nKey;
}

CScriptVarMgr::E_VarType CScriptVarMgr::GetKeyType( int nVar )
{
    if ( nVar < 0 )
        return VT_ERROR;
    else if ( nVar < VAR_CHAR_MAX )
        return VT_CHAR;
    else if ( nVar < VAR_TEMP_MAX )
        return VT_TEMP;
    else if ( nVar < VAR_SYS_MAX )
        return VT_SYS;
    else if ( nVar < VAR_GUILD_MAX )
        return VT_GUILD;
    return VT_ERROR;
}

int CScriptVarMgr::GetKeyIndex( E_VarType type, int nKey )
{
    int n = -1;
    switch( type ) 
    {
    case VT_CHAR:
        n = nKey;
        break;
    case VT_TEMP:
        n = nKey - VAR_CHAR_MAX;
        break;
    case VT_SYS:
        n = nKey - VAR_TEMP_MAX;
        break;
    case VT_GUILD:
        n = nKey - VAR_SYS_MAX;
        break;
    default:
        break;
    }
    return n;
}

#pragma warning( pop )
