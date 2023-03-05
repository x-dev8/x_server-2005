#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ���^�ų�����ʹ�õĳɆT
#endif

// ������б�횃����xȡ��ƽ̨��Ո�޸����ж��x��
// ���� MSDN ȡ�ò�ͬƽ̨����ֵ�������YӍ��
#ifndef WINVER				// ���Sʹ�� Windows XP (��) ����汾���ض����ܡ�
#define WINVER 0x0501		// ����׃����ᘌ� Windows �����汾���m��ֵ��
#endif

#ifndef _WIN32_WINNT		// ���Sʹ�� Windows XP (��) ����汾���ض����ܡ�
#define _WIN32_WINNT 0x0501	// ����׃����ᘌ� Windows �����汾���m��ֵ��
#endif						

#ifndef _WIN32_WINDOWS		// ���Sʹ�� Windows 98 (��) ����汾���ض����ܡ�
#define _WIN32_WINDOWS 0x0410 // ����׃����ᘌ� Windows Me (��) ����汾���m��ֵ��
#endif

#ifndef _WIN32_IE			// ���Sʹ�� IE 6.0 (��) ����汾���ض����ܡ�
#define _WIN32_IE 0x0600	// ����׃����ᘌ� IE �����汾���m��ֵ��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ���_���x���ֵ� CString ������ʽ

// �P�] MFC �[��һЩ��Ҋ��ɺ��Ծ���ӍϢ�Ĺ���
#define _AFX_ALL_WARNINGS

#include <afxwin.h> 
#include <afxext.h> 


#include <afxdisp.h>
#include <direct.h>
#include <assert.h>
#include <map>
#include <string>
#include <vector>

#include <exception>                        // for std::exception
#include <new>                              // for std::bad_alloc
#include <string>                           // for std::string
#include <stdlib.h>                         // for exit codes


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC ֧Ԯ�� Internet Explorer 4 ͨ�ÿ����
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC ֧Ԯ�� Windows ͨ�ÿ����
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win64' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win64' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


