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

    static long m_exitFlag;    // �˳���־
    void SetExitFlag(); // �����˳���־

public:
    void Run( DWORD argc, LPTSTR argv[] ); //ִ�з�����������
    void Stop();                           //ֹͣ
    void SetupConsole();
    //SERVICE_STATUS GetStatus(){ return m_ssStatus; } //��ȡ����״̬

    bool Init( int argc, char* argv[] ); // ��ʼ��
    long MainLoop();                     // ��ѭ��
    void UnInit();                       // ����

	bool GetDebugMode(){return _debugmode;}
	void SetDebugMode(bool b){_debugmode = b;}
protected:
    void ProcessKey(DWORD keycode); // �������¼�
    void ConsoleInputLoop();        // ������Ϣ����ѭ��

private:
    typedef std::list<unsigned long> KeycodeList;
    KeycodeList      m_lstKeycode; // �����б�
    HANDLE           m_hIn;	       // ������
    CSemiAutoIntLock _hInLock;
    HANDLE           _hMainInputThread;
    DWORD	         _dwStartTime;
	bool             _debugmode;//�Ƿ�debugģʽ
	//SERVICE_STATUS   m_ssStatus;
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

#endif // __CS_CONSOLEAPPLICATION_H__
