/********************************************************************
    Filename:     ConsoleApplication.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GS_CONSOLEAPPLICATION_H__
#define __GS_CONSOLEAPPLICATION_H__

#pragma once

#include "MeRTLibsServer.h"
#include "WorkThread.h"
//#include "NTService.h"
#include "Mutex.h"

class ConsoleApplication/* : public NTService*/
{    
public:
    ConsoleApplication(bool isdebug);
    ~ConsoleApplication();    

    void SetExitFlag();

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
    HANDLE           m_hIn;        // ������
    CSemiAutoIntLock _hInLock;
    CWorkThread      _mainLogicThread;
    HANDLE           _hMainInputThread;

	bool             _debugmode;//�Ƿ�debugģʽ
};

inline void ConsoleApplication::SetExitFlag()
{
    /*CSALocker lock(_hInLock);

    INPUT_RECORD input;
    input.EventType = MENU_EVENT;
    input.Event.MenuEvent.dwCommandId = 1;
    uint32 size = sizeof(input);
    WriteConsoleInput( m_hIn, &input, sizeof(input), &size );*/
}

#endif // __GS_CONSOLEAPPLICATION_H__
