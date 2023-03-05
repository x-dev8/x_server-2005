template< class Param1 >
inline bool ScriptManager::ScriptFunctionVoid( const std::string& funName, Param1 p1 )
{
    if (NULL == _pLuaState)
    {
        return false;
    }

    try
    {
        luabind::call_function<void>( _pLuaState, funName.c_str(),p1);
        return true;
    }
    catch (luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState,-1);
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Call %s Function Error : %s.\
                                                 Description: %s.",funName.c_str(),e.what(),
                                                 luaErrorInfo.c_str());
    }
    return false;
}

template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8 >
inline bool ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 )
{
    if (NULL == _pLuaState)
    {
        return false;
    }

    try
    {
        luabind::call_function<void>( _pLuaState, funName.c_str(),p1,p2,p3,p4,p5,p6,p7,p8);
        return true;
    }
    catch (luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState,-1);
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Call %s Function Error : %s.\
                                                 Description: %s.",funName.c_str(),e.what(),
                                                 luaErrorInfo.c_str());
    }
    return false;
}

template < class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7 >
inline bool ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 )
{
    if (NULL == _pLuaState)
    {
        return false;
    }

    try
    {
        luabind::call_function<void>( _pLuaState, funName.c_str(),p1,p2,p3,p4,p5,p6,p7);
        return true;
    }
    catch (luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState,-1);
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Call %s Function Error : %s.\
                                                 Description: %s.",funName.c_str(),e.what(),
                                                 luaErrorInfo.c_str());
    }
    return false;
}

template < class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
inline bool ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 )
{ 
    if (NULL == _pLuaState)
    {
        return false;
    }

    try
    {
        luabind::call_function<void>( _pLuaState, funName.c_str(),p1,p2,p3,p4,p5,p6);
        return true;
    }
    catch (luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState,-1);
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Call %s Function Error : %s.\
                                                 Description: %s.",funName.c_str(),e.what(),
                                                 luaErrorInfo.c_str());
    }
    return false;
}

template <class Param1, class Param2, class Param3, class Param4, class Param5>
inline bool ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 )
{
    if (NULL == _pLuaState)
    {
        return false;
    }

    try
    {
        luabind::call_function<void>( _pLuaState, funName.c_str(),p1,p2,p3,p4,p5);
        return true;
    }
    catch (luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState,-1);
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Call %s Function Error : %s.\
                                                 Description: %s.",funName.c_str(),e.what(),
                                                 luaErrorInfo.c_str());
    }
    return false;
}

template < class Param1, class Param2, class Param3, class Param4 >
inline bool ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4 )
{
    if (NULL == _pLuaState)
    {
        return false;
    }

    try
    {
        luabind::call_function<void>( _pLuaState, funName.c_str(),p1,p2,p3,p4);
        return true;
    }
    catch (luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState,-1);
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Call %s Function Error : %s.\
                                                 Description: %s.",funName.c_str(),e.what(),
                                                 luaErrorInfo.c_str());
    }
    return false;
}

template < class Param1, class Param2, class Param3 >
inline bool ScriptManager::ScriptFunctionVoid( const std::string& funName, Param1 p1, Param2 p2, Param3 p3 )
{
    if (NULL == _pLuaState)
    {
        return false;
    }

    try
    {
        luabind::call_function<void>( _pLuaState, funName.c_str(),p1,p2,p3);
        return true;
    }
    catch (luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState,-1);
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Call %s Function Error : %s.\
                                                 Description: %s.",funName.c_str(),e.what(),
                                                 luaErrorInfo.c_str());
    }
    return false;
}

template <class Param1, class Param2 >
inline bool ScriptManager::ScriptFunctionVoid( const std::string& funName, Param1 p1, Param2 p2 )
{
    if (NULL == _pLuaState)
    {
        return false;
    }

    try
    {
        luabind::call_function<void>( _pLuaState, funName.c_str(),p1);
        return true;
    }
    catch (luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState,-1);
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Call %s Function Error : %s.\
                                                 Description: %s.",funName.c_str(),e.what(),
                                                 luaErrorInfo.c_str());
    }
    return false;
}

template <class T, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8 >
inline T ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 )
{
    if (NULL == _pLuaState)
    {
        return NULL;
    }

    return luabind::call_function<T>( _pLuaState, funName.c_str(), p1, p2, p3, p4, p5, p6, p7, p8 );
}

template <class T, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7 >
inline T ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 )
{
    if (NULL == _pLuaState)
    {
        return NULL;
    }

    return luabind::call_function<T>( _pLuaState, funName.c_str(), p1, p2, p3, p4, p5, p6, p7 );
}

template <class T, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
inline T ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 )
{
    if (NULL == _pLuaState)
    {
        return NULL;
    }

    return luabind::call_function<T>( _pLuaState, funName.c_str(), p1, p2, p3, p4, p5, p6);
}

template <class T, class Param1, class Param2, class Param3, class Param4, class Param5>
inline T ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 )
{
    if (NULL == _pLuaState)
    {
        return NULL;
    }

    return luabind::call_function<T>( _pLuaState, funName.c_str(), p1, p2, p3, p4, p5 );
}

template <class T, class Param1, class Param2, class Param3, class Param4 >
inline T ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3, Param4 p4 )
{
    if (NULL == _pLuaState)
    {
        return NULL;
    }

    return luabind::call_function<T>( _pLuaState, funName.c_str(), p1, p2, p3, p4 );
}

template <class T, class Param1, class Param2, class Param3 >
inline T ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2, Param3 p3 )
{
    if (NULL == _pLuaState)
    {
        return NULL;
    }

    return luabind::call_function<T>( _pLuaState, funName.c_str(), p1, p2, p3 );
}

template <class T, class Param1, class Param2 >
inline T ScriptManager::ScriptFunction( const std::string& funName, Param1 p1, Param2 p2 )
{
    if (NULL == _pLuaState)
    {
        return NULL;
    }

    return luabind::call_function<T>( _pLuaState, funName.c_str(), p1, p2 );
}

template <class T, class Param1 >
inline T ScriptManager::ScriptFunction( const std::string& funName, Param1 p1 )
{
    if (NULL == _pLuaState)
    {
        return NULL;
    }

    return luabind::call_function<T>( _pLuaState, funName.c_str(), p1);
}

template <class T>
inline T ScriptManager::ScriptFunction( const std::string& funName )
{
    if (NULL == _pLuaState)
    {
        return NULL;
    }

    return luabind::call_function<T>( _pLuaState, funName.c_str());
}

template <>
inline void ScriptManager::ScriptFunction<void>( const std::string& funName )
{
    if (NULL == _pLuaState)
    {
        return;
    }

    luabind::call_function<void>( _pLuaState, funName.c_str());
}