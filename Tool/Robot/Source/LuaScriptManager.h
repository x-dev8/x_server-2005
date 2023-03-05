//////////////////////////////////////////////////////////////////////////
//      FileName:LuaScriptManager.h
//      Author  :eliteYang
//      Desc    :Lua�ű������࣬���ڽ������˳�ʼ���Ȳ���ʹ��Lua�ű�ʵ��
//////////////////////////////////////////////////////////////////////////
#ifndef __LUASCRIPTMANAGER_H__
#define __LUASCRIPTMANAGER_H__
#define Lua_Bind        // ���ʹ��luabind, ʹ�ô� ��
//#define Lua_Plus      // ���ʹ��luaplus, ʹ�ô� ��   // ʹ��LuaPlus���޸Ĺ�������ӵ�Include�ļ�,��ʱ��ʹ�ã���������

#if defined(Lua_Bind)
extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}
#include "luabind/luabind.hpp"
#elif defined(Lua_Plus)
#include "LuaPlus/LuaPlus.h"
#endif

#if defined(Lua_Bind)
#define theLuaManager LuaBindManager::Instance() // LuaBindManager ʵ���ӿ�
#elif defined(Lua_Plus)
#define theLuaManager LuaPlusManager::Instance() // LuaPlusManager ʵ���ӿ�
#endif

#if defined(Lua_Bind)
class LuaBindManager
{
public:
    LuaBindManager();
    ~LuaBindManager();

    static LuaBindManager& Instance()
    {
        static LuaBindManager x_LuaBindManager;
        return x_LuaBindManager;
    }

    unsigned long Init();
    unsigned long Bind();
    unsigned long LoadLuaScript(const char* szFileName);
    unsigned long UnInit();
    lua_State* GetLuaState(){ return _pLuaState;}
private:
    lua_State* _pLuaState;

#elif defined(Lua_Plus)

class LuaPlusManager
{
public:
    LuaPlusManager();
    ~LuaPlusManager();
    static LuaPlusManager& Instance()
    {
        static LuaPlusManager x_LusPlusManager;
        return x_LusPlusManager;
    }

    LuaFunction<int> GetGlobalFunc(LPCSTR cFuncName){ return m_LuaScript->GetGlobal(cFuncName);}
    void LoadLuaScript(const char* LuaFileName);
    LuaStateOwner& GetLuaStateOwner(){ return m_LuaScript;}
private:
    LuaStateOwner m_LuaScript;              // ����Lua������

#endif

public:
    struct LuaScriptConfig
    {
        int nID;                // ����������ID
        std::string RobotName; // �ű�����
        std::string ScriptPath; // �ű�·��
    };
    // ��ȡ/����Lua�ű������ļ�
    bool LoadScriptConfig(const char* szFileName);
    bool SaveScriptConfig(const char* szFileName);
    LuaScriptConfig* GetLuaScriptById(int nID);
protected:
    std::vector<LuaScriptConfig*> m_ScriptVector;      // �ű��ļ�����
};

#endif // ~__LUASCRIPTMANAGER_H__