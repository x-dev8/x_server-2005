/********************************************************************
	Filename: 	ConsoleApplication.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CS_CONSOLEAPPLICATION_H__
#define __CS_CONSOLEAPPLICATION_H__

#pragma once

#include "MeRTLibsServer.h"
#include "WorkThread.h"
//#include "NTService.h"
#include "Mutex.h"

#define APPLICATION_NAME "CenterServer"

class ConsoleApplication/* : public NTService*/
{    
public:
    ConsoleApplication(bool bdebug = false);
    ~ConsoleApplication();

    static long m_exitFlag;    // 退出标志
    void SetExitFlag(); // 设置退出标志

public:
    void Run( DWORD argc, LPTSTR argv[] ); //执行服务的主体代码
    void Stop();                           //停止
    void SetupConsole();
    //SERVICE_STATUS GetStatus(){ return m_ssStatus; } //获取服务状态

    bool Init( int argc, char* argv[] ); // 初始化
    long MainLoop();                     // 主循环
    void UnInit();                       // 结束

	bool GetDebugMode(){return _debugmode;}
	void SetDebugMode(bool b){_debugmode = b;}
protected:
    void ProcessKey(DWORD keycode); // 处理按键事件
    void ConsoleInputLoop();        // 按键消息输入循环

private:
    typedef std::list<unsigned long> KeycodeList;
    KeycodeList      m_lstKeycode; // 按键列表
    HANDLE           m_hIn;	       // 输入句柄
    CSemiAutoIntLock _hInLock;
    HANDLE           _hMainInputThread;
    DWORD	         _dwStartTime;
	bool             _debugmode;//是否debug模式
	//SERVICE_STATUS   m_ssStatus;
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

#endif // __CS_CONSOLEAPPLICATION_H__
