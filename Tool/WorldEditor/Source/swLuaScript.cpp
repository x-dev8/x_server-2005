#include "stdafx.h"
#include "swLuaScript.h"


swLuaScript::swLuaScript()
{
	m_globalState	= NULL;
	m_error			= 0;
	Create();
}

swLuaScript::~swLuaScript()
{
	Destory();
}

bool swLuaScript::Create()
{
	// Open up the global state
	m_globalState = lua_open();

	if (NULL == m_globalState) 
	{
		Trace("ERROR : 初始化LUA环境失败，内存错误!");
		return false;
	}

	return true;
}

void swLuaScript::Destory()
{
	if (NULL != m_globalState)
	{
		lua_close(m_globalState);
		m_globalState = NULL;
	}
}

// Script hooking from source code
void swLuaScript::RegisterFunc(const char* pScriptName, lua_CFunction pFunc)
{
	lua_register( m_globalState, pScriptName, pFunc );
}

bool swLuaScript::ExecFile( const char* pFilename)
{
	m_error = lua_dofile( m_globalState, pFilename );

	if( m_error) 
	{
		Trace("ERROR [LuaScript::exec(%s) : Error(%s)]\n", pFilename, lua_tostring(m_globalState, -1));
		lua_pop( m_globalState, 1 );	/* pop error message from the stack */
		return false;
	}
	return true;
}

bool swLuaScript::ExecString( const char* pString)
{
	m_error = lua_dostring( m_globalState, pString );
	if( m_error )
	{
		Trace( "ERROR ExecStr(%s) : Error : %s \n", pString, lua_tostring(m_globalState, -1));
		lua_pop(m_globalState, 1);
		return false;
	}
	return true;
}

bool swLuaScript::GetGlobalNumber(const char * pGlobalName, double *pNumber)
{
	int nSize = lua_gettop(m_globalState);
	lua_getglobal(m_globalState, pGlobalName);

	if (nSize + 1 == lua_gettop(m_globalState) && CheckStackType(-1, LUA_TNUMBER))
	{
		*pNumber = lua_tonumber(m_globalState, -1);
		lua_pop(m_globalState, 1);
		return true;
	}
	else
	{
		if (nSize + 1 != lua_gettop(m_globalState))
		{
			Trace("ERROR : GetGlobalNumber(%s) : 未找到全局变量\n", pGlobalName);
		}
		if (!CheckStackType(-1, LUA_TNUMBER))
		{
			lua_pop(m_globalState, 1);
			Trace("ERROR : GetGlobalNumber(%s) : 类型不正确\n", pGlobalName);
		}

		return false;
	}
}

bool swLuaScript::GetGlobalString(const char * pGlobalName, char * pString, int strLen )
{
	int nSize = lua_gettop(m_globalState);
	if( strlen( pGlobalName ) > 0 ) 
	{
		lua_getglobal(m_globalState, pGlobalName);
	}
	else 
	{
		lua_getglobal( m_globalState, "STRINGNULL" );
	}
	if (nSize + 1 == lua_gettop(m_globalState) && CheckStackType(-1, LUA_TSTRING))
	{
		const char* pText = lua_tostring(m_globalState, -1);
#if _MSC_VER >= 1400
		strcpy_s( pString, strLen, pText );
#else
		strcpy( pString, pText );
#endif
		lua_pop(m_globalState, 1);
		return true;
	}
	else
	{
		if (nSize + 1 != lua_gettop(m_globalState))
		{
			Trace("ERROR: GetGlobalString(%s) : 未找到全局变量\n", pGlobalName);
		}
		if (!CheckStackType(-1, LUA_TSTRING))
		{
			lua_pop(m_globalState, 1);
			Trace("ERROR: GetGlobalString(%s) : 类型不正确\n", pGlobalName);
		}

		return false;
	}
}

bool swLuaScript::GetGlobalFunc(const char *pFunc)
{
	int nSize = lua_gettop(m_globalState);
	lua_getglobal(m_globalState, pFunc);

	if (nSize + 1 == lua_gettop(m_globalState) && CheckStackType(-1, LUA_TFUNCTION))
	{
		return true;
	}
	else
	{
		if (nSize + 1 != lua_gettop(m_globalState))
		{
			Trace("ERROR: GetGlobalFunction(%s) : 未找到函数\n", pFunc);
		}

		if (!CheckStackType(-1, LUA_TFUNCTION))
		{
			Trace("ERROR: GetGlobalFunction(%s) : 参数不是函数类型\n", pFunc);
		}

		return false;
	}
}

/******************************************************************************/
void swLuaScript::PushNumber(const double d)
{
	lua_pushnumber(m_globalState, d);
}

/******************************************************************************/
void swLuaScript::PushString(const char * pString)
{
	lua_pushstring(m_globalState, pString);
}

bool swLuaScript::ExcuteNoParamFun(const char* FunName, int nresults)
{
	lua_getglobal(m_globalState, FunName);
	if(lua_pcall(m_globalState, 0, nresults, 0) != 0)
	{
		lua_pop(m_globalState,1);
		return false;
	}
	else
	{
		return true;
	}
}

bool swLuaScript::ExcuteOneParamFun(const char* FunName, double param, int nresults)
{
	lua_getglobal(m_globalState, FunName);
	lua_pushnumber(m_globalState, param);
	if(lua_pcall(m_globalState, 1, nresults, 0) != 0)
	{
		lua_pop(m_globalState,1);
		return false;
	}
	else
	{
		return true;
	}
}

bool swLuaScript::ExcuteTwoParamFun(const char* FunName, double param1, double param2, int nresults)
{
	lua_getglobal(m_globalState, FunName);
	lua_pushnumber(m_globalState, param1);
	lua_pushnumber(m_globalState, param2);
	if(lua_pcall(m_globalState, 2, nresults, 0) != 0)
	{
		lua_pop(m_globalState,1);
		return false;
	}
	else
	{
		return true;
	}
}

bool swLuaScript::ExcuteThreeParamFun(const char* FunName, double param1, double param2, double param3, int nresults)
{
	lua_getglobal(m_globalState, FunName);
	lua_pushnumber(m_globalState, param1);
	lua_pushnumber(m_globalState, param2);
	lua_pushnumber(m_globalState, param3);
	if(lua_pcall(m_globalState, 3, nresults, 0) != 0)
	{
		lua_pop(m_globalState,1);
		return false;
	}
	else
	{
		return true;
	}
}

/******************************************************************************/
int swLuaScript::CallFuncProtect(int nArg, int nResult, int nError /* = 0 */)
{
	if (lua_pcall(m_globalState, nArg, nResult, nError) != 0)
	{
		Trace("ERROR: lua_pcall() Error : %s \n",lua_tostring(m_globalState, -1));
		lua_pop(m_globalState, 1);
		return -1;
	}
	else
	{
		return 0;
	}
}

/******************************************************************************/
void swLuaScript::SetGlobal(const char * pGlobalName)
{
	lua_setglobal(m_globalState, pGlobalName);
}

/******************************************************************************/
bool swLuaScript::CheckStackType(const int nIndex, const int nType)
{
	return nType == lua_type(m_globalState, nIndex);
}

/******************************************************************************/
bool swLuaScript::GetNumber(double *pDouble, int nIndex /* = -1 */)
{
	if (CheckStackType(nIndex, LUA_TNUMBER))
	{
		(*pDouble) = lua_tonumber(m_globalState, nIndex);
		//lua_pop(m_globalState, 1);
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************/
void swLuaScript::SetGlobal(const char *pObjectName, double dNumber)
{
	PushNumber(dNumber);
	SetGlobal(pObjectName);
}

/******************************************************************************/
void swLuaScript::SetGlobal(const char * pObjectName, const char * pString)
{
	PushString(pString);
	SetGlobal(pObjectName);
}

/******************************************************************************/
bool swLuaScript::GetTableNumber(const char *pTableName, const char *pVarName, double *pNumber)
{
	if (GetGlobalVar(pTableName))
	{
		PushString(pVarName);
		lua_gettable(m_globalState, -2);

		int bResult = lua_isnumber(m_globalState, -1);
		if (bResult)
		{
			(*pNumber) = lua_tonumber(m_globalState, -1);
			lua_pop(m_globalState, 1);
		}
		else
		{
			lua_pop(m_globalState, 1);
		}

		return true;
	}
	else
		return false;
}

bool swLuaScript::GetTableString(const char* pTableName, const char* pVarName, const char* pszValue)
{
	if (GetGlobalVar(pTableName))
	{
		PushString(pVarName);
		lua_gettable(m_globalState, -2);

		int bResult = lua_isstring(m_globalState, -1);
		if (bResult)
		{
			pszValue = lua_tostring(m_globalState, -1);
			lua_pop(m_globalState, 1);
		}
		else
		{
			lua_pop(m_globalState, 1);
		}

		return true;
	}
	else
		return false;
}

/******************************************************************************/
bool swLuaScript::GetGlobalVar(const char* pVar)
{
	int nSize = lua_gettop(m_globalState);

	lua_getglobal(m_globalState, pVar);

	bool bTable = lua_istable(m_globalState, -1);

	if (nSize + 1 != lua_gettop(m_globalState))
	{
		Trace("ERROR: GetGlobalVar(%s) : 未找到变量\n", pVar);
		return false;
	}

	return true;
}

bool swLuaScript::IsType(lua_State* L, int nIndex, int nType, const char* pszFunc)
{
	int type = lua_type(L, nIndex);

	if (LUA_TNONE == type)
	{
		Trace("未知的LUA类型\n");
		return false;
	}
	else
	{
		return type == nType;
	}
}

bool swLuaScript::IsVarCount(lua_State* L, int nCount, const char* pszFunc)
{
	if (nCount == lua_gettop(L))
	{
		return true;
	}
	else
	{
		if (NULL == pszFunc)
		{
			Trace("ERROR: [ %s ] 参数列表错误 \n");
		}
		else
		{
			Trace("ERROR: [ %s ] 参数列表错误 \n", pszFunc);
		}

		return false;
	}
}