#ifndef __SCRIPTMANAGER_H__
#define __SCRIPTMANAGER_H__
#include "stdafx.h"
#include "MeRTLibsServer.h"

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}
#include "luabind/luabind.hpp"

// 每个线程一个
class ScriptManager
{
public:
    ~ScriptManager();

    static ScriptManager& GetInstance();
    uint32 Init();
    uint32 Bind();
    uint32 LoadScript(const char *szScriptFileName);
    void LogMsg(int Level,const char *szMsg);
    uint32 UnInit();

    template <class T>
    T ScriptFunction( const std::string& funName );

    template <class T, class Param1 >
    T ScriptFunction( const std::string& funName, Param1 p1 );

    template <class T, class Param1, class Param2 >
    T ScriptFunction( const std::string& funName, Param1 p1, Param2 p2 );

    template <class T, class Param1, class Param2, class Param3 >
    T ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3 );

    template <class T, class Param1, class Param2, class Param3, class Param4 >
    T ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4 );

    template <class T, class Param1, class Param2, class Param3, class Param4, class Param5>
    T ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 );

    template <class T, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
    T ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 );

    template <class T, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7 >
    T ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 );

    template <class T, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8 >
    T ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 );

    // void
    
    bool ScriptFunctionVoid( const std::string& funName );

    template <class Param1 >
    bool ScriptFunctionVoid( const std::string& funName, Param1 p1 );

    template <class Param1, class Param2 >
    bool ScriptFunctionVoid( const std::string& funName, Param1 p1, Param2 p2 );

    template < class Param1, class Param2, class Param3 >
    bool ScriptFunctionVoid( const std::string& funName, Param1 p1, Param2 p2, Param3 p3 );

    template < class Param1, class Param2, class Param3, class Param4 >
    bool ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4 );

    template <class Param1, class Param2, class Param3, class Param4, class Param5>
    bool ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 );

    template < class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
    bool ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 );

    template < class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7 >
    bool ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 );

    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8 >
    bool ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 );

private:
    lua_State* _pLuaState;
    ScriptManager();
};
// Error CallBack Function
int GetExecuteErrorFileAndLine(lua_State* pLuaState);
// 模板函数
#include "ScriptManager.inl"

#define theScriptManager ScriptManager::GetInstance()
#endif // __SCRIPTMANAGER_H__
