/*++

Copyright (c) 2005

Module Name:

    DataBase.h
    DataBase.cpp
    .\_PRIVE\Mutex.h

Abstract:

    �ṩһ���򵥵����ݿ���ʽӿ�

    ע��:��ΪADOΪCOM���,������ʹ��ǰӦ�õ��� CoInitialize(NULL);
         ����ʱӦ�õ��� CoUninitialize();

Author:

    ����(yukun1984@gmail.com) 7-Oct-2005

Revision History:

    ����һ���쳣������ܵ��µ�ϸ΢�ڴ�й©  14-Mar-2006
    �쳣�����Ż���һ�����õĶ������        27-Mar-2006
    Ϊ��־����Ƿ����ÿ���                  5-Dec-2006

--*/

#ifndef _DB_DATA_BASE_H
#define _DB_DATA_BASE_H

#include <string>

#if _WIN32_WINNT < 0x0500
#define _WIN32_WINNT 0x0501
#endif

#pragma comment(lib, "comsupp.lib")
//����ADO��COM DLL (DLL����·�����������,���Ըı�)
#import "C:\Program Files\common files\system\ado\msado15.dll" no_namespace rename("EOF","EndOfFile") rename("BOF","FirstOfFile")

using std::string;

namespace DataBase
{
    class CDebugOutPut
    {
        //�û��Զ�����־���������ʽ
        typedef void (*OutPut)(const char*); 

    public:
        //�����û��Զ�����־�ʹ���������ַ
        void static SetLogOut(const OutPut proc);
        void static SetErrorOut(const OutPut proc);

        void static SetEnableLog(bool bEnableLog);

    protected:
        //�ṩ��CConnection��CRecordset����
        friend class CConnection;
        friend class CRecordset;

        //���ú��������־�������
        void static LogOut(const BSTR szText);
        void static LogOut(const char* szText);

        void static ErrOut(const BSTR szText);
        void static ErrOut(const char* szText);

    private:
        static OutPut m_LogOut;
        static OutPut m_ErrOut;
        static bool m_bEnableLog;
    };


    class CRecordset
    {
    public:
        //��ȡ�ֶ�ֵ
        const char* Get(const char* szField, bool bLog = false);
		const char* GetDateTime(const char* szField, bool bLog = false);

		_RecordsetPtr GetRecordset()const{return m_pRecordset;}
    public:
        //�α�����ƶ�һ��
        bool MoveNext();
        //�α��������
        bool MoveFirst();

    public:
        //�α��¼�Ƿ�Ϊ��
        bool IsEmpty() const;
        //�α��Ƿ��������
        bool IsEOF() const;
        //�α��Ƿ��
        bool IsOpen() const;
    public:
        CRecordset();
        CRecordset(const CRecordset &recordset);
        CRecordset(const _RecordsetPtr &recordset);
        virtual ~CRecordset();

    public:
        CRecordset& operator = (const CRecordset &recordset);

    protected:
        _RecordsetPtr GetRecordsetPtr()const{return m_pRecordset;}

    private:
        _RecordsetPtr m_pRecordset;
        string m_strRet;            //���صļ�¼ֵ��ʱ�洢ָ��
    };

    class CConnection
    {
    public:
        //��һ������
        bool Open(const char* szIP, 
                  const char* szDBName, 
                  const char* szUserName, 
                  const char* szPassword,
                  bool bAsynchronous = false );
        
        //ֱ��ʹ�������ִ�
        bool Open(const char* szConnectString, bool bAsynchronous = false);
        
        //ʹ��DSN����
        bool Open(const char* szDSN, const char* szUserName, const char* szPassword);

    public:
        //ִ��SQL��䷵��һ����¼��
        CRecordset Execute(const char* szSQL, VARIANT * RecordsAffected = NULL, long Options = -1);

    public:
        //��������Ƿ��
        bool IsOpen() const;
        //�ر�����
        void Close();
        

    public:
        CConnection();
        virtual ~CConnection();

    private:
        _ConnectionPtr m_pCon;      //ADO������
        string m_strConnect;        //ADO�����ִ�

    private:
        CConnection(const CConnection &conn);
        CConnection& operator = (const CConnection &conn);
    };
};
#endif