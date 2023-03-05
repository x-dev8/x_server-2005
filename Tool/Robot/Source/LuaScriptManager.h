//////////////////////////////////////////////////////////////////////////
//      FileName:LuaScriptManager.h
//      Author  :eliteYang
//      Desc    :Lua脚本管理类，用于将机器人初始化等操作使用Lua脚本实现
//////////////////////////////////////////////////////////////////////////
#ifndef __LUASCRIPTMANAGER_H__
#define __LUASCRIPTMANAGER_H__
#define Lua_Bind        // 如果使用luabind, 使用此 宏
//#define Lua_Plus      // 如果使用luaplus, 使用此 宏   // 使用LuaPlus需修改工程中添加的Include文件,暂时不使用，还有问题

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
#define theLuaManager LuaBindManager::Instance() // LuaBindManager 实例接口
#elif defined(Lua_Plus)
#define theLuaManager LuaPlusManager::Instance() // LuaPlusManager 实例接口
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
    LuaStateOwner m_LuaScript;              // 创建Lua解释器

#endif

public:
    struct LuaScriptConfig
    {
        int nID;                // 机器人类型ID
        std::string RobotName; // 脚本名称
        std::string ScriptPath; // 脚本路径
    };
    // 读取/保存Lua脚本配置文件
    bool LoadScriptConfig(const char* szFileName);
    bool SaveScriptConfig(const char* szFileName);
    LuaScriptConfig* GetLuaScriptById(int nID);
protected:
    std::vector<LuaScriptConfig*> m_ScriptVector;      // 脚本文件容器
};

#endif // ~__LUASCRIPTMANAGER_H__