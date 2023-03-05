#include "RunningScriptControl.h"
#include "GamePlayer.h"
#include "ScriptVarMgr.h"

int RunningScriptControl::PushScript(SScript* p)
{       
    if ( m_lsScript.size() <= EConstDefine_MaxCacheScriptCount )
    { m_lsScript.push_back( *p ); }
    return m_lsScript.size();
}

bool RunningScriptControl::PopScript()
{       
    if ( m_lsScript.size() == 0 )
    { return false;}

    m_lsScript.pop_front();
    if ( m_lsScript.size() == 0 )
    { return false; }
    return true;
}

SScript* RunningScriptControl::GetScript()
{       
    if( m_lsScript.size() == 0 )
    { return NULL; }
    return &m_lsScript.front();
}
 
bool RunningScriptControl::RegisterVar( short stVarId )
{       
    SScript* pScript = GetScript();
    if ( !pScript )
    { return false; }

    pScript->nVarId = stVarId;
    return true;
}

void RunningScriptControl::CancelCurScript( const char* szFile, const char* szFunc )
{
    SScript* pScript = GetScript();
    if ( pScript == NULL )
    { return; }

    CScriptVM* pVM = pScript->thread.GetVM();
    if ( pVM != NULL)
    { pVM->Return(); }

    switch ( GetOwnerType() )
    {
    case EOwnerType_GamePlayer:
        {
            GamePlayer* pGamePlayer = (GamePlayer*)this;
            MsgScriptEnd msgScriptEnd;
			if ( m_dwScriptSleep != 0 )
				msgScriptEnd.type = ST_ScriptSleep;
			else
				msgScriptEnd.type = ST_UNKNOW;
            GettheServer().SendMsgToSingle( &msgScriptEnd, pGamePlayer );

            m_dwScriptSleep = 0;
            if ( PopScript() == true )
            { GetScriptMgr()->ExecuteVM( ST_UNKNOW, -1, pGamePlayer ); }

            pGamePlayer->Log( "%s;%s call CancelCurScript", szFile, szFunc );
        }
        break;
    case EOwnerType_GlobalSystem:
        break;
    }
}

void RunningScriptControl::CancelAllScript()
{
    SScript* pScript = GetScript();
    if ( pScript == NULL )
    { return; }

    CScriptVM* pVM = pScript->thread.GetVM();
    if ( pVM != NULL)
    { pVM->Return(); }

    switch ( GetOwnerType() )
    {
    case EOwnerType_GamePlayer:
        {
            GamePlayer* pGamePlayer = (GamePlayer*)this;
            MsgScriptEnd msgScriptEnd;
			if ( m_dwScriptSleep != 0 )
				msgScriptEnd.type = ST_ScriptSleep;
			else
				msgScriptEnd.type = ST_UNKNOW;
            GettheServer().SendMsgToSingle( &msgScriptEnd, pGamePlayer );

            m_dwScriptSleep = 0;            
        }
        break;
    case EOwnerType_GlobalSystem:
        {

        }
        break;
    }

    // 请掉所有脚本
    m_lsScript.clear();
}

void RunningScriptControl::SetVar( int nKey, int nVar, int nOp, unsigned char uchSendMessage )
{
    CScriptVarMgr::E_VarType eType = CScriptVarMgr::GetKeyType( nKey );

    int nIndex = CScriptVarMgr::GetKeyIndex( eType, nKey );
    if ( nIndex < 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "严重错误SetVar(%d,%d,%d) Type%d,Index%d", nKey, nVar, nOp, eType, nIndex );
        return;
    }
    short* pShort = NULL;
    int*   pInt   = NULL;

    switch ( GetOwnerType() )
    {
    case EOwnerType_GamePlayer:
        {
            GamePlayer* pGamePlayer = (GamePlayer*)this;
            switch( eType ) 
            {
            case CScriptVarMgr::VT_CHAR:        
                if ( nIndex < More_iMaxVars )
                {
                    pShort = &pGamePlayer->gCharInfoServer.otherdata.vars.szVars[nIndex];
                }
                break;
            case CScriptVarMgr::VT_TEMP:
                if ( nIndex < More_iMaxTempVars )
                {
                    pInt = &m_nTempVars[nIndex];
                }   
                break;
            case CScriptVarMgr::VT_SYS:
                { pInt = GetScriptVarMgr()->GetSysVar( nIndex ); }
                break;
            default:
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetVar Invalid eType = %d", eType );
                return;
            }
        }
        break;
    case EOwnerType_GlobalSystem:
        {
            switch( eType ) 
            {         
            case CScriptVarMgr::VT_SYS:
                pInt = GetScriptVarMgr()->GetSysVar( nIndex );            
                break;            
            default:
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetVar Invalid eType");
                return;
            }
        }
        break;
    }

    switch( nOp ) 
    {
    case SKW_SETADD: // +=
        {
            if(pShort)
            { *pShort += nVar; }
            else if(pInt) 
            { *pInt += nVar; }
        }
        break;
    case SKW_SETSUB: // -=
        {
            if( pShort )
            { *pShort -= nVar; }
            else if( pInt )
            { *pInt -= nVar; }
        }
        break;
    case SKW_SET: // =
        {
            if( pShort) 
            { *pShort = nVar; }
            else if( pInt ) 
            { *pInt = nVar;}
        }
        break;
    case SKW_SETMUL: // *=
        {
            if( pShort )
            { *pShort *= nVar; }
            else if( pInt )
            { *pInt *= nVar; }
        }
        break;        
    case SKW_SETDIV: // /=
        {
            if ( nVar != 0 )
            {
                if( pShort )
                { *pShort /= nVar; }
                else if( pInt )
                { *pInt /= nVar; }
            }
        }
        break;
    case SKW_SETRES: // %=
        {
            if ( nVar != 0 )
            {
                if( pShort )
                { *pShort %= nVar; }
                else  if(pInt)
                { *pInt %= nVar; }
            }
        }
        break;
    default:
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetVar Invalid nOp");
        return;
    }        

    if ( uchSendMessage == BV_NotSendMessage )
    { return; }

    switch ( GetOwnerType() )
    {
    case RunningScriptControl::EOwnerType_GamePlayer:
        {
            GamePlayer* pGamePlayer = (GamePlayer*)this;
            // 通知客户端
            if ( eType == CScriptVarMgr::VT_CHAR && pShort )
            {
                MsgTellCharVar msg;
                msg.AddValue( nIndex, *pShort );
                GettheServer().SendMsgToSingle( &msg, pGamePlayer );
            }
            else if ( eType == CScriptVarMgr::VT_GUILD && pShort != NULL )
            {
                pGamePlayer->TellGuildVar( nIndex, *pShort );
            }
        }
        break;
    case RunningScriptControl::EOwnerType_GlobalSystem:
        break;
    }
}

int RunningScriptControl::GetVar( int nKey )
{
    CScriptVarMgr::E_VarType eType = CScriptVarMgr::GetKeyType( nKey );

    int nIndex = CScriptVarMgr::GetKeyIndex( eType, nKey );
    if ( nIndex < 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Type[%d] Key[%d] Index[%d] 错误：变量超出范围", eType,nKey,nIndex);
        return 0;
    }

    switch ( GetOwnerType() )
    {
    case EOwnerType_GamePlayer:
        {
            GamePlayer* pGamePlayer = (GamePlayer*)this;
            switch( eType ) 
            {
            case CScriptVarMgr::VT_CHAR:
                {
                    if ( nIndex < More_iMaxVars )
                    { return pGamePlayer->gCharInfoServer.otherdata.vars.szVars[nIndex]; }
                    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s 角色变量超出范围 Type[%d] Key[%d] Index[%d]", pGamePlayer->GetCharName(), eType,nKey,nIndex );
                }
                break;
            case CScriptVarMgr::VT_TEMP:
                {
                    if ( nIndex < More_iMaxTempVars )
                    { return m_nTempVars[nIndex]; }
                    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s 临时变量超出范围 Type[%d] Key[%d] Index[%d]", pGamePlayer->GetCharName(), eType,nKey,nIndex);
                }
                break;
            case CScriptVarMgr::VT_SYS:
                {
                    int *pInt = GetScriptVarMgr()->GetSysVar( nIndex );
                    if( pInt )
                    { return *pInt; }
                    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s 系统变量超出范围 Type[%d] Key[%d] Index[%d]", pGamePlayer->GetCharName(), eType,nKey,nIndex );
                }
                break;
            case CScriptVarMgr::VT_GUILD:
                {
                    if ( nIndex < More_iMaxGuildVars )
                    { 
                        return pGamePlayer->GetGuildVar(nIndex); 
                    }
                    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s 公会变量超出范围 Type[%d] Key[%d] Index[%d]", pGamePlayer->GetCharName(), eType,nKey,nIndex);
                }
                break;
            default:
                break;
            }
        }
        break;
    case EOwnerType_GlobalSystem:
        break;
    }
    return 0;
}
