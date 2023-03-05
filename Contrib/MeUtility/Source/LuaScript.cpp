#include "MeRTLibs.h"
#include "LuaScript.h"
#include "Luaplus/LuaPlus.h"
#include "FuncPerformanceLog.h"

LuaScript::LuaScript(void)
{
	guardfunc;
	RegisterStandardFunctions();
	unguard;
}

LuaScript::~LuaScript(void)
{
	guardfunc;
	unguard;
}


BOOL LuaScript::Init()
{
	guardfunc;
	return TRUE;
	unguard;
}

void LuaScript::Exit()
{
	guardfunc;
	//
	unguard;
}

BOOL LuaScript::Load(char* FileName)
{
	guardfunc;
	BOOL bRet = m_LuaOwner->LoadFile( FileName );
	Execute();
	return bRet;
	unguard;
}

BOOL LuaScript::Compile(char* FileName)
{
	guardfunc;
	return m_LuaOwner->DoFile( FileName );
	unguard;
}

BOOL LuaScript::Execute()
{
	guardfunc;
	m_LuaOwner->Call( 0, 0 );
	return TRUE;
	unguard;
}

int nTTT()
{
	return 0;
}

//---------------------------------------------------------------------------
// 函数:	CLuaScript::RegisterStandardFunctions
// 功能:	注册Lua系统标准的函数库
// 返回:	void 
//---------------------------------------------------------------------------
void LuaScript::RegisterStandardFunctions()
{
	guardfunc;
	if (! m_LuaOwner )	
		return ;
	luaopen_base( m_LuaOwner->GetCState() );//Lua基本库
	luaopen_io( m_LuaOwner->GetCState() );//输入输出库
	luaopen_string( m_LuaOwner->GetCState() );//字符串处理库
	luaopen_math( m_LuaOwner->GetCState() );//数值运算库
	//Lua_OpenDBLib(m_LuaState);//调试库
	return;	
	unguard;
}


BOOL LuaScript::RegisterFunction(LPSTR FuncName, void* func )
{
	guardfunc;
	m_LuaOwner->GetGlobals().Register( FuncName,  (lua_CFunction)func );
	return true;
	unguard;
}

BOOL LuaScript::RegisterFunctions( TNativeFun Funcs[], int n )
{
	guardfunc;
	//if (! m_LuaState)	return FALSE;
	if (n == 0)	
		n = sizeof(Funcs) / sizeof(Funcs[0]);
	for (int i = 0; i < n; i ++)	
	{
		m_LuaOwner->GetGlobals().Register(Funcs[i].name, (lua_CFunction)Funcs[i].func);
	}
	return TRUE;
	unguard;
}