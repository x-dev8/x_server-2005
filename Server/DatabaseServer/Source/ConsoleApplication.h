/********************************************************************
    Filename: ConsoleApplication.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __DS_CONSOLEAPPLICATION_H__
#define __DS_CONSOLEAPPLICATION_H__

#pragma once

#include "MeRTLibsServer.h"
#include "WorkThread.h"
#include "DatabaseServerApp.h"
//#include "NTService.h"
#include "Mutex.h"

class ConsoleApplication/* : public NTService*/
{    
public:
    ConsoleApplication(bool isdebug);
    ~ConsoleApplication();

    static long m_exitFlag;     // 退出标志
    static void CrashCall();
    static ConsoleApplication* gGlobalConsole;

    void   SetExitFlag();       // 设置退出标志

public:
    void Run( DWORD argc, LPTSTR argv[] ); //执行服务的主体代码
    void Stop();                           //停止
    void SetupConsole();
    //SERVICE_STATUS GetStatus(){ return m_ssStatus; } //获取服务状态

    bool Init( int argc, char* argv[] ); // 初始化
    long MainLoop();                     // 主循环    
    void UnInit();                       // 结束
    void Reset();                        // 重置    

	bool GetDebugMode(){return m_bDebug;}
protected:    
    void ProcessKey(DWORD keycode); // 处理按键事件
    void ConsoleInputLoop();        // 按键消息输入循环

private:
    typedef std::list<unsigned long> KeycodeList;
    KeycodeList   m_lstKeycode; // 按键列表
    HANDLE        m_hIn;        // 输入句柄
    CSemiAutoIntLock _hInLock;
    CWorkThread _mainLogicThread;
    HANDLE      _hMainInputThread;
    DWORD       _dwStartTime;
	bool m_bDebug;
};

inline void ConsoleApplication::SetExitFlag()
{
	//不直接关闭应用程序,等待手动关闭
    /*InterlockedExchange(&ConsoleApplication::m_exitFlag, 1);

    CSALocker lock(_hInLock);
    INPUT_RECORD input;
    input.EventType = MENU_EVENT;
    input.Event.MenuEvent.dwCommandId = 1;
    uint32 size = sizeof(input);
    WriteConsoleInput( m_hIn, &input, sizeof(input), &size );*/

    //::PostMessage( m_ghIn, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM( 200, 200 ) );
}

#endif // __DS_CONSOLEAPPLICATION_H__
