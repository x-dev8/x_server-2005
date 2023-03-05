#include "stdafx.h"
#include "fs_ime_aplha.h"
//#include ".\CSD3DGBFont.h"
#include <string>

using namespace std;

bool CFS_IME_Aplha::g_bIme = true;//ime允许标志
TCHAR CFS_IME_Aplha::g_szCompStr[ MAX_PATH ];//存储转换后的串
TCHAR CFS_IME_Aplha::g_szCompReadStr[ MAX_PATH ];//存储输入的串
TCHAR CFS_IME_Aplha::g_szCandList[ MAX_PATH ];//存储整理成字符串选字表
int  CFS_IME_Aplha::g_nImeCursor;//存储转换后的串中的光标位置
CANDIDATELIST *CFS_IME_Aplha::g_lpCandList;//存储标准的选字表
TCHAR CFS_IME_Aplha::g_szImeName[ 64 ];//存储输入法的名字
bool CFS_IME_Aplha::g_bImeSharp;//全角标志
bool CFS_IME_Aplha::g_bImeSymbol;//中文标点标志


//必须在消息中调用的函数，如果返回是true，则窗口函数应直接返回0，否则应传递给DefWindowProc
bool CFS_IME_Aplha::staticMsgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_INPUTLANGCHANGEREQUEST:
		{
			return !g_bIme;//如果禁止ime则返回false，此时窗口函数应返回0，否则DefWindowProc会打开输入法
		}

	case WM_IME_STARTCOMPOSITION:
		{
			return true;//
		}
	case WM_IME_ENDCOMPOSITION:
		{
			return true;
		}
	case WM_IME_SETCONTEXT:
		{
			return true;
		}		
	case WM_INPUTLANGCHANGE:
		{
			//ime改变
			HKL hKL = GetKeyboardLayout( 0 );
			if( ImmIsIME( hKL )){
				HIMC hIMC = ImmGetContext( hWnd );
				ImmEscape( hKL, hIMC, IME_ESC_IME_NAME, g_szImeName );//取得新输入法名字
				DWORD dwConversion, dwSentence;
				ImmGetConversionStatus( hIMC, &dwConversion, &dwSentence );
				g_bImeSharp = ( dwConversion & IME_CMODE_FULLSHAPE )? true : false;//取得全角标志
				g_bImeSymbol = ( dwConversion & IME_CMODE_SYMBOL )? true : false;//取得中文标点标志
				ImmReleaseContext( hWnd, hIMC );
			}
			else//英文输入
				g_szImeName[ 0 ] = 0;
			return false;//总是返回false，因为需要窗口函数调用DefWindowProc继续处理
		}
	case WM_IME_COMPOSITION:
		{
			HIMC hIMC;
			DWORD dwSize;
			hIMC = ImmGetContext( hWnd );
			if( lParam & GCS_COMPSTR ){
				::ZeroMemory(g_szCompStr, sizeof(g_szCompStr));
				dwSize = ImmGetCompositionString( hIMC, GCS_COMPSTR, (void*)g_szCompStr, sizeof( g_szCompStr )) / sizeof(TCHAR);
				g_szCompStr[ dwSize ] = 0;
			}//取得szCompStr
			if( lParam & GCS_COMPREADSTR ){
				::ZeroMemory(g_szCompReadStr, sizeof(g_szCompReadStr));
				dwSize = ImmGetCompositionString( hIMC, GCS_COMPREADSTR, (void*)g_szCompReadStr, sizeof( g_szCompReadStr )) / sizeof(TCHAR);
				g_szCompReadStr[ dwSize ] = 0;
			}//取得szCompReadStr
			if( lParam & GCS_CURSORPOS ){
				g_nImeCursor = 0xffff & ImmGetCompositionString( hIMC, GCS_CURSORPOS, NULL, 0 );
			}//取得nImeCursor
			if( lParam & GCS_RESULTSTR ){
				TCHAR str[ MAX_PATH ];
				dwSize = ImmGetCompositionString( hIMC, GCS_RESULTSTR, (void*)str, sizeof( str )) / sizeof(TCHAR);//取得汉字输入串
				str[ dwSize ] = 0;
				TCHAR *p = str;
				while( *p )PostMessage( hWnd, WM_CHAR, (WPARAM)(*p++), 1 );//转成WM_CHAR消息
			}
			ImmReleaseContext( hWnd, hIMC );
			return true;//总是返回true，防止ime窗口打开
		}
	case WM_IME_NOTIFY:
		{
			HIMC hIMC;
			DWORD dwSize;
			DWORD dwConversion, dwSentence;
			switch( wParam ){
			case IMN_SETCONVERSIONMODE://全角/半角，中/英文标点改变
				hIMC = ImmGetContext( hWnd );
				ImmGetConversionStatus( hIMC, &dwConversion, &dwSentence );
				g_bImeSharp = ( dwConversion & IME_CMODE_FULLSHAPE )? true : false;
				g_bImeSymbol = ( dwConversion & IME_CMODE_SYMBOL )? true : false;
				ImmReleaseContext( hWnd, hIMC );
				break;
			case IMN_OPENCANDIDATE://进入选字状态
			case IMN_CHANGECANDIDATE://选字表翻页
				hIMC = ImmGetContext( hWnd );
				if( g_lpCandList ){
					GlobalFree( (HANDLE)g_lpCandList );
					g_lpCandList = NULL;
				}//释放以前的选字表
				if( dwSize = ImmGetCandidateList( hIMC, 0, NULL, 0 )){
					g_lpCandList = (LPCANDIDATELIST)GlobalAlloc( GPTR, dwSize );
					if( g_lpCandList )
						ImmGetCandidateList( hIMC, 0, g_lpCandList, dwSize );
				}//得到新的选字表
				ImmReleaseContext( hWnd, hIMC );
				if( g_lpCandList )ConvertCandList( g_lpCandList, g_szCandList );//选字表整理成串
				break;
			case IMN_CLOSECANDIDATE://关闭选字表
				if( g_lpCandList ){
					GlobalFree( (HANDLE)g_lpCandList );
					g_lpCandList = NULL;
				}//释放
				g_szCandList[ 0 ] = 0;
				break;
					}
			return true;//总是返回true，防止ime窗口打开
		}

	}
	return false;

}


void CFS_IME_Aplha::DisableIme(){
	while( ImmIsIME( GetKeyboardLayout( 0 )))
		ActivateKeyboardLayout(( HKL )HKL_NEXT, 0 );//如果ime打开通过循环切换到下一个关闭
	g_bIme = false;
	g_szImeName[ 0 ] = 0;
	g_szCompStr[ 0 ] = 0;
	g_szCompReadStr[ 0 ] = 0;
	g_szCandList[ 0 ] = 0;
	g_nImeCursor = 0;
}

void CFS_IME_Aplha::EnableIme(){
	g_bIme = true;
}

void CFS_IME_Aplha::NextIme(){
	if( g_bIme )ActivateKeyboardLayout(( HKL )HKL_NEXT, 0 );
}

void CFS_IME_Aplha::SharpIme( HWND hWnd ){
	ImmSimulateHotKey( hWnd, IME_CHOTKEY_SHAPE_TOGGLE );
}

void CFS_IME_Aplha::SymbolIme( HWND hWnd ){
	ImmSimulateHotKey( hWnd, IME_CHOTKEY_SYMBOL_TOGGLE );
}

void CFS_IME_Aplha::ConvertCandList( CANDIDATELIST *pCandList, TCHAR *pszCandList ){//转换CandidateList到一个串，\t分隔每一项
	unsigned int i;
	if( pCandList->dwCount < pCandList->dwSelection ){
		pszCandList[ 0 ] = 0;
		return;
	}
	//待选字序号超出总数，微软拼音第二次到选字表最后一页后再按PageDown会出现这种情况，并且会退出选字状态，开始一个新的输入
	//但微软拼音自己的ime窗口可以解决这个问题，估计微软拼音实现了更多的接口，所以使用了这种不太标准的数据
	//我现在无法解决这个问题，而且实际使用中也很少遇到这种事，而且其它标准输入法不会引起这种bug
	//非标准输入法估计实现的接口比较少，所以应该也不会引起这种bug
	for( i = 0; ( i < pCandList->dwCount - pCandList->dwSelection )&&( i < pCandList->dwPageSize ); i++ ){
		*pszCandList++ = ( i % 10 != 9 )? i % 10 + _T('1') : _T('0');//每项对应的数字键
		*pszCandList++ = _T('.');//用'.'分隔
		_tcscpy( pszCandList, (TCHAR*)((char*)pCandList
			+ pCandList->dwOffset[ pCandList->dwSelection + i ] ));//每项实际的内容
		pszCandList += _tcslen( pszCandList );
		*pszCandList++ = '\t';//项之间以'\t'分隔
	}
	*( pszCandList - 1 )= 0;//串尾，并覆盖最后一个'\t'
}

TCHAR* CFS_IME_Aplha::GetImeName(){
	return g_szImeName[ 0 ]? g_szImeName : NULL;
}

bool CFS_IME_Aplha::IfImeSharp(){//是否全角
	return g_bImeSharp;
}

bool CFS_IME_Aplha::IfImeSymbol(){//是否中文标点
	return g_bImeSymbol;
}

void CFS_IME_Aplha::GetImeInput( TCHAR **pszCompStr, TCHAR **pszCompReadStr, int *pnImeCursor, TCHAR **pszCandList ){
	if( pszCompStr )*pszCompStr = g_szCompStr;
	if( pszCompReadStr )*pszCompReadStr = g_szCompReadStr;
	if( pnImeCursor )*pnImeCursor = g_nImeCursor;
	if( pszCandList )*pszCandList = g_szCandList;
}