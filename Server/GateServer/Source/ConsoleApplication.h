/********************************************************************
	Filename: 	ConsoleApplication.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GTS_CONSOLEAPPLICATION_H__
#define __GTS_CONSOLEAPPLICATION_H__

#pragma once

#include "MeRTLibsServer.h"
#include "WorkThread.h"
//#include "NTService.h"
#include "Mutex.h"

#define APPLICATION_NAME "GateServer"

class ConsoleApplication /*: public NTService*/
{    
public:
    ConsoleApplication(bool isdebug);
    ~ConsoleApplication();

    static long m_exitFlag;    // 退出标志
    void SetExitFlag(); // 设置退出标志

public:
    virtual void Run( DWORD argc, LPTSTR argv[] ); //执行服务的主体代码
    virtual void Stop();                           //停止
    virtual void SetupConsole();
    //SERVICE_STATUS pGamePlayer(){ return m_ssStatus; } //获取服务状态

    bool Init( int argc, char* argv[] );     // 初始化
    long MainLoop(); // 主循环    
    void UnInit();   // 结束
    void Reset();    // 重置
    bool InitLogConfigure();    // 初始化Log4cxx
    void SetReloadLog4cxx( bool bReload ){ bReloadLog4cxx = bReload; }
    bool GetReloadLog4cxx(){ return bReloadLog4cxx; }

	bool GetDebugMode(){return IsDebug;}
protected:
    void ProcessKey(DWORD keycode); // 处理按键事件
    void ConsoleInputLoop();        // 按键消息输入循环

private:
    typedef std::list<unsigned long> KeycodeList;
    KeycodeList m_lstKeycode;   // 按键列表

    CWorkThread      _mainLogicThread;
    HANDLE           _hMainInputThread;
    DWORD	         _dwStartTime;
    CSemiAutoIntLock _hInLock;
    HANDLE           m_hIn;	        // 输入句柄
    bool             bReloadLog4cxx;    // 是否需要热加载Log4cxx
	bool IsDebug;
};

inline void ConsoleApplication::SetExitFlag()
{
	//不直接关闭应用程序,等待手动关闭
    //InterlockedExchange(&ConsoleApplication::m_exitFlag, 1);

    //INPUT_RECORD input;
    //input.EventType = MENU_EVENT;
    //input.Event.MenuEvent.dwCommandId = 1;
    //uint32 size = sizeof(input);

    //CSALocker lock(_hInLock);
    //WriteConsoleInput( m_hIn, &input, sizeof(input), &size );
}

#endif // __GTS_CONSOLEAPPLICATION_H__
