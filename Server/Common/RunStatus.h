/********************************************************************
    Filename:    RunStatus.h
    MaintenanceMan Mail: Luo_157@hotmail.com


    ��ʼ��ΪServerStatus_PrepareData
    ����׼��������ʱ����Ϊ ServerStatus_Running
    ���������˳�ʱ ��ΪServerStatus_PrepareStop

    �������߼��߳� ����ΪServerStatus_PrepareStop,�Ͽ�������� ��ΪServerStatus_GameThreadStopped
    ���ݿ��̷߳���ServerStatus_GameThreadStopped������Ϣ����Ϊ�� ��ΪServerStatus_DBThreadStopped 
    Console�̷߳���ServerStatus_DBThreadStopped���˳�����

*********************************************************************/
#ifndef __COMMON_SERVERSTATUS_H__
#define __COMMON_SERVERSTATUS_H__

#include "MeRTLibsServer.h"
#include "RunStatusDefine.h"
#include "GlobalFunction.h"
#include "Singleton.h"

#define theRunStatus RunStatus::Instance()

class RunStatus : public ISingletion< RunStatus >
{
public:
	RunStatus();

    // ���ü��سɹ�
    void SetLoadSuccess( unsigned char uchLoadType );

    // ���÷���������״̬
    void SetStatus( long status ) { InterlockedExchange(&_runstatus, status ); }

    // ��÷���������״̬
    long GetStatus() { return _runstatus; }
protected:
    // ������������״̬
    void CheckRunStatus();
private:
    // ������Դ��Ϣ��ʶ
    BitValue< unsigned long > m_xLoadResource;      
    
    // ����������״̬
    volatile long _runstatus;
};

#endif // __COMMON_SERVERSTATUS_H__
