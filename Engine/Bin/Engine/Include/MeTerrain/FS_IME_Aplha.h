//-----------------------------------------------------------------------------------------
//版权声明：
//
//-----------------------------------------------------------------------------------------

#pragma once


#pragma comment ( lib, "imm32.lib" )
#include <windows.h>
#include <imm.h>

//使用说明：
//
//这个类拦截所有IME相关消息，并处理，不将这些消息发送给DefWindowProc
//防止系统自己的IME相关窗口显示
//
//将static bool staticMsgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)置于消息处理函数里
//该函数返回true，直接返回，返回false，消息发送给DefWindowProc处理
//
//GetImeInput可以得到相关IME数据
//其他状态函数返回一些IME状态
//控制函数



class CFS_IME_Aplha
{
private:
	static bool g_bIme;//ime允许标志
	static TCHAR g_szCompStr[ MAX_PATH ];//存储转换后的串
	static TCHAR g_szCompReadStr[ MAX_PATH ];//存储输入的串
	static TCHAR g_szCandList[ MAX_PATH ];//存储整理成字符串选字表
	static int g_nImeCursor;//存储转换后的串中的光标位置
	static CANDIDATELIST *g_lpCandList;//存储标准的选字表
	static TCHAR g_szImeName[ 64 ];//存储输入法的名字
	static bool g_bImeSharp;//全角标志
	static bool g_bImeSymbol;//中文标点标志
	static void ConvertCandList( CANDIDATELIST *pCandList, TCHAR *pszCandList );//将选字表整理成串

public:
	CFS_IME_Aplha(){ DisableIme();}//通过DisableIme初始化一些数据
	~CFS_IME_Aplha()
	{
		DisableIme();
		if( g_lpCandList ){
			GlobalFree( (HANDLE)g_lpCandList );
			g_lpCandList = NULL;
		}
	}

	//控制函数
	static void DisableIme();//关闭并禁止输入法，如ime已经打开则关闭，此后玩家不能用热键呼出ime
	static void EnableIme();//允许输入法，此后玩家可以用热键呼出ime
	static void NextIme();//切换到下一种输入法，必须EnableIme后才有效
	static void SharpIme( HWND hWnd );//切换全角/半角
	static void SymbolIme( HWND hWnd );//切换中/英文标点

	//状态函数
	static TCHAR* GetImeName();//得到输入法名字，如果当前是英文则返回NULL
	static bool IfImeSharp();//是否全角
	static bool IfImeSymbol();//是否中文标点
	static void GetImeInput( TCHAR **pszCompStr, TCHAR **pszCompReadStr, int *pnImeCursor, TCHAR **pszCandList );
	//得到输入法状态，四个指针任意可为NULL则此状态不回返回
	//在pszCompStr中返回转换后的串
	//在pszCompReadStr中返回键盘直接输入的串
	//在pnImeCursor中返回szCompStr的光标位置
	//在pszCandList中返回选字表，每项之间以\t分隔


	//必须在消息中调用的函数，如果返回是true，则窗口函数应直接返回0，否则应传递给DefWindowProc
	static bool staticMsgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
