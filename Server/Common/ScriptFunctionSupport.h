/********************************************************************
    Filename:    ScriptFunctionSupport.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SCRIPTFUNCTIONSUPPORT_H__
#define __COMMON_SCRIPTFUNCTIONSUPPORT_H__

#include "MeRTLibsServer.h"

class WordParser;
class CScriptVM;
class CScriptCommand;

typedef std::map< std::string, int, std::less< std::string > > StringMap;

class CScriptFunctionSingleton;
typedef std::vector< CScriptFunctionSingleton * >              SFuncVector;

class CScriptFunctionSingleton
{
public:
    CScriptFunctionSingleton();
    virtual ~CScriptFunctionSingleton();

    static CScriptFunctionSingleton* Lookup( const char * szKeyWord );
    static bool Register( const char * szKeyWord, CScriptFunctionSingleton * pFunc );
    virtual CScriptCommand* CreateFunc() = 0;

protected:
    static StringMap*   s_pMapFuncName;
    static SFuncVector* s_pVecFunction;
    std::string         m_szKeyWord;
};

template < class T >
class CScriptRegisterFunc : public CScriptFunctionSingleton
{
public:

    CScriptRegisterFunc( const char * szKeyWord )
    {
        if( !Register( szKeyWord, this ) )
        {
            MessageBox( NULL, szKeyWord, "Register Script Function Failed: maybe renamed function name", MB_OK );
        }
        m_szKeyWord = szKeyWord;
    }
    
    virtual CScriptCommand * CreateFunc()
    {
        return (CScriptCommand*) new T;
    }

};

#define SCRIPT_DECLARE( m, c ) class c; CScriptRegisterFunc<c> script_singleton_##m(#m);
#define SCRIPT_REGISTER( m ) class CISCFunc##m; CScriptRegisterFunc<CISCFunc##m> script_singleton_##m(#m);
// 定义命令开始
#define SCRIPT_BEGIN( m ) SCRIPT_REGISTER( m ); \
class CISCFunc##m : public CScriptCommand \
{ \
public: \
    const char * GetCmdID() \
    {\
        return #m; \
    }				\
	void Release(){ delete this; }
// 定义命令参数
#define SCRIPT_PARAM protected:
#define SCRIPT_FUNCTION public:
// 定义命令结束
#define SCRIPT_END };

#endif // __SCRIPT_FUNCTION_SUPPORT_H__
