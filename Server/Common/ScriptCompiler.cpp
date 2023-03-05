#include "ScriptCompiler.h"
#include "ScriptSyntax.h"
#include "ScriptFunctionSupport.h"
#include "ScriptAbstract.h"
#include "ScriptVarMgr.h"
#include "NewWithDebug.h"
#include "XmlStringLanguage.h"

extern IScriptInterface* GetScriptInterface();

CScriptCompilerSourceLine::CScriptCompilerSourceLine() :  m_nSourceLine(0), m_dwState(0)
{}

CScriptCompilerSourceLine::~CScriptCompilerSourceLine()
{
}

void CScriptCompilerSourceLine::ParseSourceCode( const char* pszSourceCode )
{
    m_words.Parse( pszSourceCode );
    m_strSourceCode = pszSourceCode;
}

CScriptCompiler::~CScriptCompiler()
{
    Destroy();
}

void CScriptCompiler::Log( const char* pszFormat, ... )
{    
    char TmpBuf[1024];
    va_list vl;

    //转换参数
    va_start(vl, pszFormat);
    vsnprintf(TmpBuf, sizeof(TmpBuf)-1, pszFormat, vl);
    va_end(vl);
    m_strLog += TmpBuf;
}

void CScriptCompiler::ClearLog()
{
    m_strLog.clear();
}

#include "StringLanguageTranslator.h"

BOOL CScriptCompiler::LoadSourceFile( const char* pszFilename )
{
    if( strlen( pszFilename ) < 1 )
        return FALSE;
    FILE* fp = fopen( pszFilename, "r" );
    if( !fp )
        return FALSE;

    char buf[1024];
    int nSourceLine = 0;
    while( fgets( buf, 1024, fp ) )
    {
        CScriptCompilerSourceLine* pLine = new CScriptCompilerSourceLine;
        //pLine->GetWords()->Parse( buf );
        pLine->ParseSourceCode( ST(buf) );
        // 设置行号
        pLine->SetSourceLine( nSourceLine );
        m_vectorLine.push_back( pLine );
        nSourceLine++;
    }
    fclose( fp );

    return TRUE;
}

void CScriptCompiler::Destroy()
{
    for( int i = 0; i < m_vectorLine.size(); i++ )
    { delete m_vectorLine[i]; }
    m_vectorLine.clear();
    //for(int i=0;i< (int)m_vectorCmd.size();i++)
    //{
    //    m_vectorCmd[i]->Release();
    //}
    //m_vectorCmd.clear();
}

// flytomap 1 23 34
// _return = Command 100
// pos = 1 47 47
CScriptCommand* CScriptCompiler::CreateCmd( int nSourceLine, WordParser* words )
{
    int nKey = -1;
    CScriptFunctionSingleton *pCreater = NULL;
    WordParser scriptWord;
    int nOp = -1;
    const char *szOp = words->GetWord(1);
    if ( strcmp( szOp, "=" ) == 0 )
    { nOp = SKW_SET; }
    else if ( strcmp( szOp, "+=" ) == 0 )
    { nOp = SKW_SETADD; }
    else if ( strcmp( szOp, "-=" ) == 0 )
    { nOp = SKW_SETSUB; }
    else if ( strcmp( szOp, "*=" ) == 0 )
    { nOp = SKW_SETMUL; }
    else if ( strcmp( szOp, "/=" ) == 0 )
    { nOp = SKW_SETDIV; }
    else if ( strcmp( szOp, "%=" ) == 0 )
    { nOp = SKW_SETRES; }

    if( nOp != SKW_UNKNOWN )
    {
        nKey = GetScriptVarMgr()->GetVarId( words->GetWord(0) );
        if ( nKey == -1 )
        { return NULL; }

        pCreater = CScriptFunctionSingleton::Lookup( words->GetWord(2) );
        if ( !pCreater )
        {
            pCreater = CScriptFunctionSingleton::Lookup( "_SetVar" );
            scriptWord.CreateFrom(2, words );
        }
        else
        {
            scriptWord.CreateFrom(3, words );
        }
    }
    else
    {
        pCreater = CScriptFunctionSingleton::Lookup( words->GetWord(0) );
        scriptWord.CreateFrom(1, words );
    }

    if( !pCreater )
    { return NULL; }

    CScriptCommand* cmd = NULL;
    cmd = pCreater->CreateFunc();
    if( cmd == NULL )
        return NULL;
    cmd->SetReturnKey( nKey );
    cmd->SetOp( nOp );
    if( cmd->Create( &scriptWord ) )
        return cmd;

    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script was create failed, row[%d]", nSourceLine+1);

    GetScriptInterface()->MarkSourceLine( nSourceLine );
    cmd->Release();
    return NULL;
}

CScriptCommand* CScriptCompiler::CreateCmd( int nSourceLine, const char* pszCmd )
{
    WordParser words;
    words.Parse( pszCmd );
    CScriptCommand* cmd = CreateCmd( nSourceLine, &words );
    return cmd;
}

int CScriptCompiler::MatchIf( DWORD dwIfAddr )
{
    // 查找检测匹配的else and endif
    bool bElseMatched = false;
    bool bEndIfMatched = false;
    int nCmdCount = (int)m_vectorCmd.size();
    
    for( int nLine = dwIfAddr+1; !bEndIfMatched && nLine < nCmdCount; nLine++ )
    {
        CScriptCommand* pCmd = m_vectorCmd[nLine];
        CScriptCompilerSourceLine* pLine = m_vectorLine[pCmd->GetSourceLine()];
        std::string szIfTestKey = pCmd->GetCmdID();
        if( szIfTestKey == std::string( "if" ) )
        {
            int nEndAddr = MatchIf( nLine );
            if( nEndAddr == -1 )
            {
                Log( theXmlString.GetString(eLog_info_2slk_0), nLine );
                pLine->AddState( eScriptLine_NotMatch );
                return -1;
            }
            // 跳到这个嵌套的if对应的endif那行
            nLine = nEndAddr;
        }
        else if( szIfTestKey == std::string( "else" ) )
        {
            if( bElseMatched )
            {
                Log( theXmlString.GetString(eLog_info_2slk_1), nLine );
                pLine->AddState( eScriptLine_NotMatch );
                return -1;
            }
            else
            {
                ((CScriptCmd_If*)m_vectorCmd[dwIfAddr])->m_nMatchElseAddr = nLine;
                bElseMatched = true;
            }
        }
        else if( szIfTestKey == std::string( "endif" ) )
        {
            if( bEndIfMatched )
            {
                Log( theXmlString.GetString(eLog_info_2slk_2), nLine );
                pLine->AddState( eScriptLine_NotMatch );
                return -1;
            }
            else
            {
                ((CScriptCmd_If*)m_vectorCmd[dwIfAddr])->m_nMatchEndIfAddr = nLine;
                int nElseId = -1;
                if( bElseMatched )
                {
                    nElseId = ((CScriptCmd_If*)m_vectorCmd[dwIfAddr])->m_nMatchElseAddr;
                    ((CScriptCmd_Else*)m_vectorCmd[nElseId])->m_nMatchIfAddr = dwIfAddr;
                    ((CScriptCmd_Else*)m_vectorCmd[nElseId])->m_nMatchEndIfAddr = nLine;
                }
                ((CScriptCmd_EndIf*)m_vectorCmd[nLine])->m_nMatchIfAddr = dwIfAddr;
                ((CScriptCmd_EndIf*)m_vectorCmd[nLine])->m_nMatchElseAddr = nElseId;
                bEndIfMatched = true;
            }
        }
        else if( szIfTestKey == std::string( "proc_start" ) )
        {
            Log( theXmlString.GetString(eLog_info_2slk_3), nLine );
            pLine->AddState( eScriptLine_InvalidEmbeded );
            return -1;
        }
        else if( szIfTestKey == std::string( "proc_end" ) )
        {
            Log( theXmlString.GetString(eLog_info_2slk_4), nLine );
            pLine->AddState( eScriptLine_InvalidEmbeded );
            return -1;
        }
    }
    if( !bElseMatched ||
        !bEndIfMatched )
    {
        CScriptCommand* pCmd = m_vectorCmd[dwIfAddr];
        CScriptCompilerSourceLine* pLine = m_vectorLine[pCmd->GetSourceLine()];

        Log( theXmlString.GetString(eLog_info_2slk_5), dwIfAddr+1 );
        pLine->AddState( eScriptLine_NotMatch );
        return -1;
    }
    
    int nMatchEndIfAddr = ((CScriptCmd_If*)m_vectorCmd[dwIfAddr])->m_nMatchEndIfAddr;
    int nMatchElseAddr = ((CScriptCmd_If*)m_vectorCmd[dwIfAddr])->m_nMatchElseAddr;

    if (nMatchElseAddr < 1 || nMatchElseAddr > m_vectorCmd.size())
    {
        Log(theXmlString.GetString(eLog_info_2slk_6), dwIfAddr+1 );
        return -1;
    }
    if( m_vectorCmd[nMatchElseAddr-1]->GetCmdID() != std::string( "jumptoendif" ) )
    {
    }
    ((CScriptCmd_JumpToEndIf*)m_vectorCmd[nMatchElseAddr-1])->m_nMatchEndIfAddr = nMatchEndIfAddr;
    
    return nMatchEndIfAddr;

}

BOOL CScriptCompiler::FirstPass()
{
    BOOL bPassed = TRUE;

    // 初始化proc地址
    for( int i = 0; i < CScriptVM::MAX_PROC; i++ )
        m_anProcAddr[i] = -1;

    for( int nLine = 0; nLine < m_vectorLine.size(); nLine++ )
    {
        CScriptCompilerSourceLine* pSourceLine = m_vectorLine[nLine];

        const char* pszWord = pSourceLine->GetWords()->GetWord(0);
        if( pszWord[0] == 0 || strncmp( pszWord, "//", 2) == 0 )
        {
            continue;
        }

        CScriptCommand* cmd = CreateCmd( nLine, pSourceLine->GetWords() );

        if( cmd )
        {
            cmd->SetSourceLine( nLine );
            std::string szKeyWord = "else";
            std::string szCmdID = cmd->GetCmdID();
            if( szKeyWord == szCmdID )
            {
                CScriptCmd_JumpToEndIf* jump = (CScriptCmd_JumpToEndIf *)CreateCmd( 0, "jumptoendif" );
                if( jump )
                {
                    m_vectorCmd.push_back( jump );  
                }
                else
                {
                }
            }
            m_vectorCmd.push_back( cmd );
        }
        else
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "[Error] Script was create failed. row:[%d], sentence[%s]",
                nLine+1,
                pSourceLine->GetSourceCode().c_str() );
            pSourceLine->AddState( eScriptLine_UnknownCommand );
            return FALSE;
        }
    }


    int nCmdCount = (int)m_vectorCmd.size();
    int nIPAddr =0;
    for( nIPAddr = 0; nIPAddr < nCmdCount; nIPAddr++ )
    {
        std::string szKeyWord = m_vectorCmd[nIPAddr]->GetCmdID();
        int nLine = m_vectorCmd[nIPAddr]->GetSourceLine() + 1;
        if( szKeyWord == std::string("proc_start") )
        {
            int nProcId = ((CScriptCmd_ProcStart*)m_vectorCmd[nIPAddr])->m_nProcId;
            
            if (nProcId < 0 || nProcId >= CScriptVM::MAX_PROC)
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:Script is slop over, row:[%d]", nLine);
                continue;
            }
            m_anProcAddr[nProcId] = nIPAddr;
            // 查找检测匹配的ProcEnd
            bool bProcEndMatched = false;
            for( int i = nIPAddr+1; !bProcEndMatched && i < nCmdCount; i++ )
            {
                std::string szTestKey = m_vectorCmd[i]->GetCmdID();
                if( szTestKey == std::string( "proc_start" ) )
                {
                    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:Script can`t find proc_end, row[%d]", nLine);
                    bPassed = FALSE;
                }
                else if( szTestKey == std::string( "proc_end" ) )
                {
                    ((CScriptCmd_ProcStart*)m_vectorCmd[nIPAddr])->m_nMatchProcEndAddr = i;
                    ((CScriptCmd_ProcEnd*)m_vectorCmd[i])->m_nMatchProcStartAddr = nIPAddr;
                    bProcEndMatched = true;
                }
            }
        }
        else if( szKeyWord == std::string("if") )
        {
            int nEndIfAddr = MatchIf( nIPAddr );
            if( nEndIfAddr != -1 )
                nIPAddr = nEndIfAddr;
            else
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:Script can`t find if-else-endif, row[%d]", nLine);
                bPassed = FALSE;
            }

        }
  
    }

    for( nIPAddr = 0; nIPAddr < nCmdCount; nIPAddr++ )
    {
        std::string szKeyWord = m_vectorCmd[nIPAddr]->GetCmdID();
        int nLine = m_vectorCmd[nIPAddr]->GetSourceLine() + 1;
        if( szKeyWord == std::string("jump") )
        {
            CScriptCmd_Jump* cmd = (CScriptCmd_Jump*)m_vectorCmd[nIPAddr];
            if( cmd->m_nProcId < 0 || cmd->m_nProcId >= CScriptVM::MAX_PROC )
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:Script jump is failed, row[%d]", nLine);
                bPassed = FALSE;
            }
            if( m_anProcAddr[cmd->m_nProcId] == -1 )
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:Script jump is failed, row[%d]", nLine);
                bPassed = FALSE;
            }
        }
    }

    return bPassed;
}

CScriptVM* CScriptCompiler::CreateVM( const char* pszFilename )
{
    if( !LoadSourceFile( pszFilename ) )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_WARNING, "%s ............ [FILE LOST]", pszFilename );
        return NULL;
    }
    m_strFileName = pszFilename;
    if( !FirstPass() )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s ............ [FAILED]", pszFilename );
        return NULL;
    }
    CScriptVM* vm = CNewWithDebug<CScriptVM>::Alloc(1, "CScriptCompiler::CreateVM中创建vm");
    for( int i = 0; i < CScriptVM::MAX_PROC; i++ )
    {
        vm->m_anProcAddr[i] = m_anProcAddr[i];
    }
    vm->m_vectorCmd = m_vectorCmd;
    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_INFO, "%s ............ [OK]", pszFilename );
    return vm;
}
