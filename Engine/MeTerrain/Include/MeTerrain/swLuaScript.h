#pragma once 

//#include "MeFoundation/Singleton.h"
#include "Luaplus/luaplus.h"

//BEG_NAMESPACE_PTGUI

class swLuaScript	 : public Singleton<swLuaScript>
{
public:
	swLuaScript();
	virtual ~swLuaScript();

	void		RegisterGameScirpt();

	// 注册函数，让此函数可以在LUA脚本中调用，函数格式为int (*pFunction)(Lua_State *L)
	void		RegisterFunc( const char* pScriptName, lua_CFunction pFunc );

	// 读取一个LUA脚本文件
	bool		ExecFile( const char* pFilename );

	// 以字符串的方式执行一段LUA代码
	bool		ExecString( const char* pString );

	// 获得一个全局变量(数字)，类型为double型
	bool		GetGlobalNumber(const char * pGlobalName, double *pNumber);
	bool		GetGlobalString(const char * pGlobalName, char * pString, int strLen);
	bool		GetTableNumber(const char* pTableName, const char* pVarName, double *pNumber);
	bool		GetTableString(const char* pTableName, const char* pVarName, const char* pszValue);

	// 执行脚本中的函数，无参数，无错误处理函数
	bool		ExcuteNoParamFun(const char* FunName, int nresults=0);
	bool		ExcuteOneParamFun(const char* FunName, double param, int nresults=0);
	bool		ExcuteTwoParamFun(const char* FunName, double param1, double param2, int nresults=0);
	bool		ExcuteThreeParamFun(const char* FunName, double param1, double param2, double param3, int nresults=0);

	// 设置LUA中的全局变量 
	void		SetGlobal(const char * pObjectName, double dNumber);	// 设置数字
	void		SetGlobal(const char * pObjectName, const char * pString);	// 设置字符串类型

	// 检查堆栈nIndex的变量类型
	bool		CheckStackType(const int nIndex, const int nType);

	static bool	IsType(lua_State* L, int nIndex, int nType, const char* pszFunc);
	static bool	IsVarCount(lua_State* L, int nCount, const char* pszFunc);

protected:

	// 初始化、清理LUA环境
	bool		Create();
	void		Destory();

	// 将数据压入堆栈
	void		PushNumber(const double d);
	void		PushString(const char * pString);

	// 设置LUA中的全局变量值
	void		SetGlobal(const char * pGlobalName);

	// 以数字的形式返回栈上第nIndex个LUA值
	bool		GetNumber(double * pDouble, int nIndex = -1);

	// 获取一个全局函数,并压入堆栈
	bool		GetGlobalFunc(const char *pFunc);
	bool		GetGlobalVar(const char* pVar);

	// 以保护模式调用函数，需指定参数个数和返回值个数及错误处理函数
	int			CallFuncProtect(int nArg, int nResult, int nError = 0);

protected:
	lua_State*	m_globalState;
	int			m_error;
};

//END_NAMESPACE_PTGUI