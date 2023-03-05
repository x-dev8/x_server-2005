/********************************************************************
    Filename:     ScriptVarMgr.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SCRIPTVARMGR_H__
#define __COMMON_SCRIPTVARMGR_H__

#pragma once

#include "MapStrToID.h"
#include "GlobalDef.h"
#include "SystemVarDefine.h"

/*
0        char        6000  temp     8000   sys       13000   guild   13500              14500
|________6000_________|____2000_____|______5000_______|______500_______|______1000_______|
*/
#define VAR_CHAR_MAX    (More_iMaxVars)
#define VAR_TEMP_MAX    (VAR_CHAR_MAX+More_iMaxTempVars)
#define VAR_SYS_MAX     (VAR_TEMP_MAX+More_iMaxSysVars)
#define VAR_GUILD_MAX   (VAR_SYS_MAX+More_iMaxGuildVars)

class CScriptVarMgr
{
public:
    enum E_VarType
    {
        VT_ERROR = 0,
        VT_CHAR,
        VT_TEMP,
        VT_SYS,
        VT_GUILD,   // 公会的记数变量,( 人物身上保存的只是公会记数变量的副本 )
    };

private:
    struct SSysVar
    {
        SSysVar()
        {
            Reset();
        }

        void Reset()
        {
            nLastID = VAR_TEMP_MAX;
            memset( stStrVars, 0, sizeof(stStrVars) );
        }

        int GetKeyByName( const char* sz )
        {
            for( int n=0; n<nLastID-VAR_TEMP_MAX; n++ )
            {
                if( stricmp(stStrVars[n].szName, sz) == 0)
                {
                    return VAR_TEMP_MAX+n;
                }
            }
            return -1;
        }

        SStrVar* GetByKey( int key )
        {
            if ( key < VAR_TEMP_MAX || key >= VAR_SYS_MAX )
            { return NULL; }

            int index = key - VAR_TEMP_MAX;
            if (index < 0 || index >= More_iMaxSysVars )
            { return NULL; }

            return &stStrVars[index];
        }

        SStrVar stStrVars[More_iMaxSysVars];
        int     nLastID;
    };

public:
    CScriptVarMgr();
    ~CScriptVarMgr();
    
    void Reset();
    int  Register( const char* pszName, int nDefault = 0 );
    int  GetVarId( const char* pszName );
    int* GetSysVar( unsigned int nIndex );
    bool LoadVar();
    void SaveVar();
    char* GetVarNameByIndex(unsigned int nIndex)
    {
        if ( nIndex < More_iMaxSysVars )
        {
            return m_stSysVar.stStrVars[nIndex].szName;
        }
        return NULL;
    }
    
    void SetScriptVar(SStrVar& strVar, int nIndex) // 设置系统变量数组中下标为nIndex的值
    {
        if (nIndex < 0)
        { return;}

        strcpy( m_stSysVar.stStrVars[nIndex].szName, strVar.szName );
        m_stSysVar.stStrVars[nIndex].nVar = strVar.nVar;
    }

public:
    static E_VarType GetKeyType( int nVar );
    static int GetKeyIndex( E_VarType type, int nKey );

private:
    E_VarType GetKeyType( const char* szVar );

private:
    CMapStrToIDMgr m_str2IdTemp;
    CMapStrToIDMgr m_str2IdSys;    
    SSysVar        m_stSysVar;
};

//////////////////////////////////////////////////////////////////////////
// inline
inline int* CScriptVarMgr::GetSysVar( unsigned int nIndex )
{
    if ( nIndex < More_iMaxSysVars )
    {
        return &m_stSysVar.stStrVars[nIndex].nVar;
    }
    return NULL;
}

extern CScriptVarMgr* GetScriptVarMgr();

#endif // __COMMON_SCRIPTVARMGR_H__
