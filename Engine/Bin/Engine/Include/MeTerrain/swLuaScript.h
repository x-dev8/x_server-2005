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

	// ע�ắ�����ô˺���������LUA�ű��е��ã�������ʽΪint (*pFunction)(Lua_State *L)
	void		RegisterFunc( const char* pScriptName, lua_CFunction pFunc );

	// ��ȡһ��LUA�ű��ļ�
	bool		ExecFile( const char* pFilename );

	// ���ַ����ķ�ʽִ��һ��LUA����
	bool		ExecString( const char* pString );

	// ���һ��ȫ�ֱ���(����)������Ϊdouble��
	bool		GetGlobalNumber(const char * pGlobalName, double *pNumber);
	bool		GetGlobalString(const char * pGlobalName, char * pString, int strLen);
	bool		GetTableNumber(const char* pTableName, const char* pVarName, double *pNumber);
	bool		GetTableString(const char* pTableName, const char* pVarName, const char* pszValue);

	// ִ�нű��еĺ������޲������޴�������
	bool		ExcuteNoParamFun(const char* FunName, int nresults=0);
	bool		ExcuteOneParamFun(const char* FunName, double param, int nresults=0);
	bool		ExcuteTwoParamFun(const char* FunName, double param1, double param2, int nresults=0);
	bool		ExcuteThreeParamFun(const char* FunName, double param1, double param2, double param3, int nresults=0);

	// ����LUA�е�ȫ�ֱ��� 
	void		SetGlobal(const char * pObjectName, double dNumber);	// ��������
	void		SetGlobal(const char * pObjectName, const char * pString);	// �����ַ�������

	// ����ջnIndex�ı�������
	bool		CheckStackType(const int nIndex, const int nType);

	static bool	IsType(lua_State* L, int nIndex, int nType, const char* pszFunc);
	static bool	IsVarCount(lua_State* L, int nCount, const char* pszFunc);

protected:

	// ��ʼ��������LUA����
	bool		Create();
	void		Destory();

	// ������ѹ���ջ
	void		PushNumber(const double d);
	void		PushString(const char * pString);

	// ����LUA�е�ȫ�ֱ���ֵ
	void		SetGlobal(const char * pGlobalName);

	// �����ֵ���ʽ����ջ�ϵ�nIndex��LUAֵ
	bool		GetNumber(double * pDouble, int nIndex = -1);

	// ��ȡһ��ȫ�ֺ���,��ѹ���ջ
	bool		GetGlobalFunc(const char *pFunc);
	bool		GetGlobalVar(const char* pVar);

	// �Ա���ģʽ���ú�������ָ�����������ͷ���ֵ��������������
	int			CallFuncProtect(int nArg, int nResult, int nError = 0);

protected:
	lua_State*	m_globalState;
	int			m_error;
};

//END_NAMESPACE_PTGUI