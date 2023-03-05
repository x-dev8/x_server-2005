//-----------------------------------------------------------------------------------------
//��Ȩ������
//
//-----------------------------------------------------------------------------------------

#pragma once


#pragma comment ( lib, "imm32.lib" )
#include <windows.h>
#include <imm.h>

//ʹ��˵����
//
//�������������IME�����Ϣ��������������Щ��Ϣ���͸�DefWindowProc
//��ֹϵͳ�Լ���IME��ش�����ʾ
//
//��static bool staticMsgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)������Ϣ��������
//�ú�������true��ֱ�ӷ��أ�����false����Ϣ���͸�DefWindowProc����
//
//GetImeInput���Եõ����IME����
//����״̬��������һЩIME״̬
//���ƺ���



class CFS_IME_Aplha
{
private:
	static bool g_bIme;//ime�����־
	static TCHAR g_szCompStr[ MAX_PATH ];//�洢ת����Ĵ�
	static TCHAR g_szCompReadStr[ MAX_PATH ];//�洢����Ĵ�
	static TCHAR g_szCandList[ MAX_PATH ];//�洢������ַ���ѡ�ֱ�
	static int g_nImeCursor;//�洢ת����Ĵ��еĹ��λ��
	static CANDIDATELIST *g_lpCandList;//�洢��׼��ѡ�ֱ�
	static TCHAR g_szImeName[ 64 ];//�洢���뷨������
	static bool g_bImeSharp;//ȫ�Ǳ�־
	static bool g_bImeSymbol;//���ı���־
	static void ConvertCandList( CANDIDATELIST *pCandList, TCHAR *pszCandList );//��ѡ�ֱ�����ɴ�

public:
	CFS_IME_Aplha(){ DisableIme();}//ͨ��DisableIme��ʼ��һЩ����
	~CFS_IME_Aplha()
	{
		DisableIme();
		if( g_lpCandList ){
			GlobalFree( (HANDLE)g_lpCandList );
			g_lpCandList = NULL;
		}
	}

	//���ƺ���
	static void DisableIme();//�رղ���ֹ���뷨����ime�Ѿ�����رգ��˺���Ҳ������ȼ�����ime
	static void EnableIme();//�������뷨���˺���ҿ������ȼ�����ime
	static void NextIme();//�л�����һ�����뷨������EnableIme�����Ч
	static void SharpIme( HWND hWnd );//�л�ȫ��/���
	static void SymbolIme( HWND hWnd );//�л���/Ӣ�ı��

	//״̬����
	static TCHAR* GetImeName();//�õ����뷨���֣������ǰ��Ӣ���򷵻�NULL
	static bool IfImeSharp();//�Ƿ�ȫ��
	static bool IfImeSymbol();//�Ƿ����ı��
	static void GetImeInput( TCHAR **pszCompStr, TCHAR **pszCompReadStr, int *pnImeCursor, TCHAR **pszCandList );
	//�õ����뷨״̬���ĸ�ָ�������ΪNULL���״̬���ط���
	//��pszCompStr�з���ת����Ĵ�
	//��pszCompReadStr�з��ؼ���ֱ������Ĵ�
	//��pnImeCursor�з���szCompStr�Ĺ��λ��
	//��pszCandList�з���ѡ�ֱ�ÿ��֮����\t�ָ�


	//��������Ϣ�е��õĺ��������������true���򴰿ں���Ӧֱ�ӷ���0������Ӧ���ݸ�DefWindowProc
	static bool staticMsgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
