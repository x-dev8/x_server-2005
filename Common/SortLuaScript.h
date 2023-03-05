#pragma once
#include "MeRTLibs.h"
//排序二叉树，保存经过文件名转数字的脚本的id,并实现快速查找对应脚本
#include "LuaScript.h"

#define LUA_UIMAIN "UILua.lua"

#define LUA_UICHAT "Chat.lua"
#define LUA_TEST "Test.lua"
#define LUA_TEST_EFFECT "Effect.lua"
extern char g_szCurScriptDir[MAX_PATH];

#ifdef _SERVER 
#define MAX_SCRIPT_IN_SET 10000
#else
#define MAX_SCRIPT_IN_SET 50
#endif

extern LuaScript g_ScriptSet[MAX_SCRIPT_IN_SET];

class CSortScriptNode
{

	DWORD m_dwScriptIndex;
	DWORD m_dwScriptID;
public:

#ifdef _DEBUG
	char m_szScriptName[100];
#endif

	DWORD GetScriptIndex(){return m_dwScriptIndex;};
	DWORD GetScriptID(){return m_dwScriptID;};

	void SetScriptIndex(DWORD dwScriptIndex){m_dwScriptIndex = dwScriptIndex;};
	void SetScriptID(DWORD dwScriptID){m_dwScriptID = dwScriptID;};

	const IScript * GetScript()
	{
		if (m_dwScriptIndex >= 0 && m_dwScriptIndex <MAX_SCRIPT_IN_SET) 
			return &g_ScriptSet[m_dwScriptIndex];
		else
			return NULL;
	}
};

typedef std::map< DWORD, CSortScriptNode > CScriptMap;
extern CScriptMap		g_ScriptMap;
extern unsigned long g_IniScriptEngine( std::string szPath);
extern const IScript * g_GetScript(DWORD dwScriptId);
extern const IScript * g_GetScript(const char * szRelativeScriptFile);
extern BOOL ReLoadScript(const char * szRelativePathScript);
extern unsigned long  ReLoadAllScript();

