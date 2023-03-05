#ifndef __G_DEFINE_H__
#define __G_DEFINE_H__

#pragma warning ( push )
#pragma warning ( disable : 4996)

#include "MeRTLibs.h"
#include "ErrorLog.h"

//宏错开启与否
#define G_ERROR_MESSAGE

#define G_ERROR		-1
#define G_OK		1

#define G_NULL		NULL

#define G_OUT_MESSAGE( m ) {\
	char ErrorMsg[1024];\
	_snprintf(ErrorMsg, sizeof(ErrorMsg)-1, "%s,%d : %s", __FILE__, __LINE__, m );\
	GetErrorLog()->logString(ErrorMsg);\
}
//MessageBox( NULL, ErrorMsg, "catch error", MB_OK );
#define G_ASSERT_RET( e, v ) {\
	if ( !(e) )\
	{\
		G_OUT_MESSAGE( #e );\
		return v;\
	}\
}

#define G_ASSERT_NORET( e ) {\
	if ( !(e) )\
	{\
		G_OUT_MESSAGE( #e );\
	}\
}

#define G_NMSG_ASSERT_RET( e, v ) {\
	if ( !(e) )\
	{\
		return v;\
	}\
}

#define G_NMSG_ASSERT_NORET( e ) {\
	if ( !(e) )\
	{\
	}\
}

#ifdef G_ERROR_MESSAGE
	#define G_ASSERTN( e ) G_ASSERT_RET(e,G_ERROR)			//报错，返回错误码
	#define G_ASSERTP( e ) G_ASSERT_RET(e,G_NULL)			//报错，返回空指针
	#define G_ASSERTE( e ) G_ASSERT_NORET( e )				//报错，不返回
#else
	#define G_ASSERTN( e ) G_NMSG_ASSERT_RET(e,G_ERROR)		//无报错，返回错误码
	#define G_ASSERTP( e ) G_NMSG_ASSERT_RET(e,G_NULL)		//无报错，返回空指针
	#define G_ASSERTE( e ) G_NMSG_ASSERT_NORET( e )			//无报错，不返回
#endif // G_ERROR_MESSAGE

#define Assert(e) G_ASSERT_NORET( e )

namespace ShareData {
    //extern gDebugLog *theLog;
};

inline void _warning (
                      void *expr,
                      void *filename,
                      unsigned lineno
                      )
{
    const char *Texp = (char*)expr;
    const char *Tfilename = (char*)filename;
    char buffer[1024];
    _snprintf( buffer, sizeof(buffer)-1, "%s, AT [%s][%d]\n", Texp, Tfilename, lineno );
#ifdef WARNING_FOR_CLIENT
    OutputDebugString( buffer );
#else

    //ShareData::theLog->Output( buffer );
#endif 
}

#ifdef _DEBUG
    #define Warning(exp) ()( (exp) || (_warning(#exp, __FILE__, __LINE__), 0) )
#else
    #define Warning(exp)     (()0)
#endif 

#pragma warning ( pop )

#endif //__G_DEFINE_H__