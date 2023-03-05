#include "stdafx.h"
#include "fs_ime_aplha.h"
//#include ".\CSD3DGBFont.h"
#include <string>

using namespace std;

bool CFS_IME_Aplha::g_bIme = true;//ime�����־
TCHAR CFS_IME_Aplha::g_szCompStr[ MAX_PATH ];//�洢ת����Ĵ�
TCHAR CFS_IME_Aplha::g_szCompReadStr[ MAX_PATH ];//�洢����Ĵ�
TCHAR CFS_IME_Aplha::g_szCandList[ MAX_PATH ];//�洢������ַ���ѡ�ֱ�
int  CFS_IME_Aplha::g_nImeCursor;//�洢ת����Ĵ��еĹ��λ��
CANDIDATELIST *CFS_IME_Aplha::g_lpCandList;//�洢��׼��ѡ�ֱ�
TCHAR CFS_IME_Aplha::g_szImeName[ 64 ];//�洢���뷨������
bool CFS_IME_Aplha::g_bImeSharp;//ȫ�Ǳ�־
bool CFS_IME_Aplha::g_bImeSymbol;//���ı���־


//��������Ϣ�е��õĺ��������������true���򴰿ں���Ӧֱ�ӷ���0������Ӧ���ݸ�DefWindowProc
bool CFS_IME_Aplha::staticMsgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_INPUTLANGCHANGEREQUEST:
		{
			return !g_bIme;//�����ֹime�򷵻�false����ʱ���ں���Ӧ����0������DefWindowProc������뷨
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
			//ime�ı�
			HKL hKL = GetKeyboardLayout( 0 );
			if( ImmIsIME( hKL )){
				HIMC hIMC = ImmGetContext( hWnd );
				ImmEscape( hKL, hIMC, IME_ESC_IME_NAME, g_szImeName );//ȡ�������뷨����
				DWORD dwConversion, dwSentence;
				ImmGetConversionStatus( hIMC, &dwConversion, &dwSentence );
				g_bImeSharp = ( dwConversion & IME_CMODE_FULLSHAPE )? true : false;//ȡ��ȫ�Ǳ�־
				g_bImeSymbol = ( dwConversion & IME_CMODE_SYMBOL )? true : false;//ȡ�����ı���־
				ImmReleaseContext( hWnd, hIMC );
			}
			else//Ӣ������
				g_szImeName[ 0 ] = 0;
			return false;//���Ƿ���false����Ϊ��Ҫ���ں�������DefWindowProc��������
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
			}//ȡ��szCompStr
			if( lParam & GCS_COMPREADSTR ){
				::ZeroMemory(g_szCompReadStr, sizeof(g_szCompReadStr));
				dwSize = ImmGetCompositionString( hIMC, GCS_COMPREADSTR, (void*)g_szCompReadStr, sizeof( g_szCompReadStr )) / sizeof(TCHAR);
				g_szCompReadStr[ dwSize ] = 0;
			}//ȡ��szCompReadStr
			if( lParam & GCS_CURSORPOS ){
				g_nImeCursor = 0xffff & ImmGetCompositionString( hIMC, GCS_CURSORPOS, NULL, 0 );
			}//ȡ��nImeCursor
			if( lParam & GCS_RESULTSTR ){
				TCHAR str[ MAX_PATH ];
				dwSize = ImmGetCompositionString( hIMC, GCS_RESULTSTR, (void*)str, sizeof( str )) / sizeof(TCHAR);//ȡ�ú������봮
				str[ dwSize ] = 0;
				TCHAR *p = str;
				while( *p )PostMessage( hWnd, WM_CHAR, (WPARAM)(*p++), 1 );//ת��WM_CHAR��Ϣ
			}
			ImmReleaseContext( hWnd, hIMC );
			return true;//���Ƿ���true����ֹime���ڴ�
		}
	case WM_IME_NOTIFY:
		{
			HIMC hIMC;
			DWORD dwSize;
			DWORD dwConversion, dwSentence;
			switch( wParam ){
			case IMN_SETCONVERSIONMODE://ȫ��/��ǣ���/Ӣ�ı��ı�
				hIMC = ImmGetContext( hWnd );
				ImmGetConversionStatus( hIMC, &dwConversion, &dwSentence );
				g_bImeSharp = ( dwConversion & IME_CMODE_FULLSHAPE )? true : false;
				g_bImeSymbol = ( dwConversion & IME_CMODE_SYMBOL )? true : false;
				ImmReleaseContext( hWnd, hIMC );
				break;
			case IMN_OPENCANDIDATE://����ѡ��״̬
			case IMN_CHANGECANDIDATE://ѡ�ֱ�ҳ
				hIMC = ImmGetContext( hWnd );
				if( g_lpCandList ){
					GlobalFree( (HANDLE)g_lpCandList );
					g_lpCandList = NULL;
				}//�ͷ���ǰ��ѡ�ֱ�
				if( dwSize = ImmGetCandidateList( hIMC, 0, NULL, 0 )){
					g_lpCandList = (LPCANDIDATELIST)GlobalAlloc( GPTR, dwSize );
					if( g_lpCandList )
						ImmGetCandidateList( hIMC, 0, g_lpCandList, dwSize );
				}//�õ��µ�ѡ�ֱ�
				ImmReleaseContext( hWnd, hIMC );
				if( g_lpCandList )ConvertCandList( g_lpCandList, g_szCandList );//ѡ�ֱ�����ɴ�
				break;
			case IMN_CLOSECANDIDATE://�ر�ѡ�ֱ�
				if( g_lpCandList ){
					GlobalFree( (HANDLE)g_lpCandList );
					g_lpCandList = NULL;
				}//�ͷ�
				g_szCandList[ 0 ] = 0;
				break;
					}
			return true;//���Ƿ���true����ֹime���ڴ�
		}

	}
	return false;

}


void CFS_IME_Aplha::DisableIme(){
	while( ImmIsIME( GetKeyboardLayout( 0 )))
		ActivateKeyboardLayout(( HKL )HKL_NEXT, 0 );//���ime��ͨ��ѭ���л�����һ���ر�
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

void CFS_IME_Aplha::ConvertCandList( CANDIDATELIST *pCandList, TCHAR *pszCandList ){//ת��CandidateList��һ������\t�ָ�ÿһ��
	unsigned int i;
	if( pCandList->dwCount < pCandList->dwSelection ){
		pszCandList[ 0 ] = 0;
		return;
	}
	//��ѡ����ų���������΢��ƴ���ڶ��ε�ѡ�ֱ����һҳ���ٰ�PageDown�����������������һ��˳�ѡ��״̬����ʼһ���µ�����
	//��΢��ƴ���Լ���ime���ڿ��Խ��������⣬����΢��ƴ��ʵ���˸���Ľӿڣ�����ʹ�������ֲ�̫��׼������
	//�������޷����������⣬����ʵ��ʹ����Ҳ�������������£�����������׼���뷨������������bug
	//�Ǳ�׼���뷨����ʵ�ֵĽӿڱȽ��٣�����Ӧ��Ҳ������������bug
	for( i = 0; ( i < pCandList->dwCount - pCandList->dwSelection )&&( i < pCandList->dwPageSize ); i++ ){
		*pszCandList++ = ( i % 10 != 9 )? i % 10 + _T('1') : _T('0');//ÿ���Ӧ�����ּ�
		*pszCandList++ = _T('.');//��'.'�ָ�
		_tcscpy( pszCandList, (TCHAR*)((char*)pCandList
			+ pCandList->dwOffset[ pCandList->dwSelection + i ] ));//ÿ��ʵ�ʵ�����
		pszCandList += _tcslen( pszCandList );
		*pszCandList++ = '\t';//��֮����'\t'�ָ�
	}
	*( pszCandList - 1 )= 0;//��β�����������һ��'\t'
}

TCHAR* CFS_IME_Aplha::GetImeName(){
	return g_szImeName[ 0 ]? g_szImeName : NULL;
}

bool CFS_IME_Aplha::IfImeSharp(){//�Ƿ�ȫ��
	return g_bImeSharp;
}

bool CFS_IME_Aplha::IfImeSymbol(){//�Ƿ����ı��
	return g_bImeSymbol;
}

void CFS_IME_Aplha::GetImeInput( TCHAR **pszCompStr, TCHAR **pszCompReadStr, int *pnImeCursor, TCHAR **pszCandList ){
	if( pszCompStr )*pszCompStr = g_szCompStr;
	if( pszCompReadStr )*pszCompReadStr = g_szCompReadStr;
	if( pnImeCursor )*pnImeCursor = g_nImeCursor;
	if( pszCandList )*pszCandList = g_szCandList;
}