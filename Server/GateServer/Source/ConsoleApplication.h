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

    static long m_exitFlag;    // �˳���־
    void SetExitFlag(); // �����˳���־

public:
    virtual void Run( DWORD argc, LPTSTR argv[] ); //ִ�з�����������
    virtual void Stop();                           //ֹͣ
    virtual void SetupConsole();
    //SERVICE_STATUS pGamePlayer(){ return m_ssStatus; } //��ȡ����״̬

    bool Init( int argc, char* argv[] );     // ��ʼ��
    long MainLoop(); // ��ѭ��    
    void UnInit();   // ����
    void Reset();    // ����
    bool InitLogConfigure();    // ��ʼ��Log4cxx
    void SetReloadLog4cxx( bool bReload ){ bReloadLog4cxx = bReload; }
    bool GetReloadLog4cxx(){ return bReloadLog4cxx; }

	bool GetDebugMode(){return IsDebug;}
protected:
    void ProcessKey(DWORD keycode); // �������¼�
    void ConsoleInputLoop();        // ������Ϣ����ѭ��

private:
    typedef std::list<unsigned long> KeycodeList;
    KeycodeList m_lstKeycode;   // �����б�

    CWorkThread      _mainLogicThread;
    HANDLE           _hMainInputThread;
    DWORD	         _dwStartTime;
    CSemiAutoIntLock _hInLock;
    HANDLE           m_hIn;	        // ������
    bool             bReloadLog4cxx;    // �Ƿ���Ҫ�ȼ���Log4cxx
	bool IsDebug;
};

inline void ConsoleApplication::SetExitFlag()
{
	//��ֱ�ӹر�Ӧ�ó���,�ȴ��ֶ��ر�
    //InterlockedExchange(&ConsoleApplication::m_exitFlag, 1);

    //INPUT_RECORD input;
    //input.EventType = MENU_EVENT;
    //input.Event.MenuEvent.dwCommandId = 1;
    //uint32 size = sizeof(input);

    //CSALocker lock(_hInLock);
    //WriteConsoleInput( m_hIn, &input, sizeof(input), &size );
}

#endif // __GTS_CONSOLEAPPLICATION_H__
