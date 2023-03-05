#include "ScriptFunctionSupport.h"
#include "ScriptVM.h"
#include "ScriptCompiler.h"

StringMap * CScriptFunctionSingleton::s_pMapFuncName = NULL;
SFuncVector * CScriptFunctionSingleton::s_pVecFunction = NULL;

CScriptFunctionSingleton::CScriptFunctionSingleton()
{
	if( s_pMapFuncName == NULL )
	{ s_pMapFuncName = new StringMap; }

	if( s_pVecFunction == NULL )
	{ s_pVecFunction = new SFuncVector; }
}

CScriptFunctionSingleton::~CScriptFunctionSingleton()
{
	if( s_pMapFuncName )
	{
		delete s_pMapFuncName;
		s_pMapFuncName = NULL;
	}

	if( s_pVecFunction )
	{
		delete s_pVecFunction;
		s_pVecFunction = NULL;
	}
}

CScriptFunctionSingleton* CScriptFunctionSingleton::Lookup( const char* szKeyWord )
{
	if ( !szKeyWord || szKeyWord[0] == 0  )
    { return NULL; }
    
    if ( 0 )
    { // 大小写不敏感
        int nLeng = strlen(szKeyWord);
        char szTempBuffer[512] = {0};
        if ( nLeng>= 512 )
        { return NULL; }
        strncpy_s( szTempBuffer, 512, szKeyWord, nLeng );
        strlwr( szTempBuffer );
        std::string str = szTempBuffer;
    }

	StringMap::iterator it = s_pMapFuncName->find( szKeyWord );
	if( it == s_pMapFuncName->end() )
	{ return NULL; }

	return (*s_pVecFunction)[ it->second ];
}

bool CScriptFunctionSingleton::Register( const char* szKeyWord, CScriptFunctionSingleton* pFunc )
{
	if ( !szKeyWord || szKeyWord[0] == 0  )
    { return NULL; }

    if ( 0 )
    { // 大小写不敏感
        int nLeng = strlen(szKeyWord);
        char szTempBuffer[512] = {0};
        if ( nLeng>= 512 )
        { return NULL; }
        strncpy_s( szTempBuffer, 512, szKeyWord, nLeng );
        strlwr( szTempBuffer );
        std::string str = szTempBuffer;
    }
	
	if( CScriptFunctionSingleton::Lookup( szKeyWord ) )
	{ return false; }

	int id = (int)s_pVecFunction->size();
	s_pVecFunction->push_back( pFunc );
	s_pMapFuncName->insert( StringMap::value_type( szKeyWord, id ) );
	if( !CScriptFunctionSingleton::Lookup( szKeyWord ) )
	{ return false; }

	return true;
}
