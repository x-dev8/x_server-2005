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

    static long m_exitFlag;     // �˳���־
    static void CrashCall();
    static ConsoleApplication* gGlobalConsole;

    void   SetExitFlag();       // �����˳���־

public:
    void Run( DWORD argc, LPTSTR argv[] ); //ִ�з�����������
    void Stop();                           //ֹͣ
    void SetupConsole();
    //SERVICE_STATUS GetStatus(){ return m_ssStatus; } //��ȡ����״̬

    bool Init( int argc, char* argv[] ); // ��ʼ��
    long MainLoop();                     // ��ѭ��    
    void UnInit();                       // ����
    void Reset();                        // ����    

	bool GetDebugMode(){return m_bDebug;}
protected:    
    void ProcessKey(DWORD keycode); // �������¼�
    void ConsoleInputLoop();        // ������Ϣ����ѭ��

private:
    typedef std::list<unsigned long> KeycodeList;
    KeycodeList   m_lstKeycode; // �����б�
    HANDLE        m_hIn;        // ������
    CSemiAutoIntLock _hInLock;
    CWorkThread _mainLogicThread;
    HANDLE      _hMainInputThread;
    DWORD       _dwStartTime;
	bool m_bDebug;
};

inline void ConsoleApplication::SetExitFlag()
{
	//��ֱ�ӹر�Ӧ�ó���,�ȴ��ֶ��ر�
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
