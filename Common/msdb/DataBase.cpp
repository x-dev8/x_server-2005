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

//#include "stdafx.h"
#include "DataBase.h"
#include "Mutex.h"

using DataBase::CConnection;
using DataBase::CRecordset;
using DataBase::CDebugOutPut;


//////////////////////////////////////////////////////////////
CDebugOutPut::OutPut CDebugOutPut::m_ErrOut = NULL;
CDebugOutPut::OutPut CDebugOutPut::m_LogOut = NULL;
bool CDebugOutPut::m_bEnableLog = true;

void CDebugOutPut::SetLogOut(const CDebugOutPut::OutPut proc)
{
    m_LogOut = proc;
}

void CDebugOutPut::SetErrorOut(const CDebugOutPut::OutPut proc)
{
    m_ErrOut = proc;
}

void CDebugOutPut::SetEnableLog(bool bEnableLog)
{
    m_bEnableLog = bEnableLog;
}

void CDebugOutPut::LogOut(const BSTR szText)
{
    if (m_LogOut!=NULL && m_bEnableLog)
    {
        static char szBuff[40000] = {0};
        WideCharToMultiByte(CP_ACP, 0, szText, -1, szBuff, sizeof(szBuff), NULL, NULL);
        m_LogOut(szBuff);
    }
}

void CDebugOutPut::ErrOut(const BSTR szText)
{
    if (m_ErrOut!=NULL /*&& m_bEnableLog*/)
    {
        static char szBuff[40000] = {0};
        WideCharToMultiByte(CP_ACP, 0, szText, -1, szBuff, sizeof(szBuff), NULL, NULL);
        m_ErrOut(szBuff);
    }
}

void CDebugOutPut::LogOut(const char* szText)
{
    if (m_LogOut!=NULL && m_bEnableLog)
    {
        m_LogOut(szText);
    }
}

void CDebugOutPut::ErrOut(const char* szText)
{
    if (m_ErrOut!=NULL /*&& m_bEnableLog*/)
    {
        m_ErrOut(szText);
    }
}

/////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
CConnection::CConnection()
{
    m_pCon.CreateInstance(/*__uuidof(Connection)*/"ADODB.Connection");
}

CConnection::CConnection(const CConnection&)
{
//    ��ֹ��vector����������ʱ����������
    m_pCon.CreateInstance(/*__uuidof(Connection)*/"ADODB.Connection");
}

CConnection& CConnection::operator = (const CConnection&)
{
    return *this;
}

CConnection::~CConnection()
{
    if (m_pCon != NULL)
    {
        if (IsOpen())
        {
            Close();
        }
//        m_pCon->Release();
    }
}

bool CConnection::IsOpen() const
{
    try
    {
        return (m_pCon != NULL && (m_pCon->State & adStateOpen));
    }
    catch (_com_error &e)
    {
        CDebugOutPut::ErrOut(m_strConnect.c_str());
        CDebugOutPut::ErrOut(e.Description().GetBSTR());
        return false;
    }
}

void CConnection::Close()
{
    try
    {
        if (m_pCon != NULL && IsOpen())
        {
            m_pCon->Close();
        }
    }
    catch (_com_error &e)
    {
        CDebugOutPut::ErrOut(m_strConnect.c_str());
        CDebugOutPut::ErrOut(e.Description().GetBSTR());
    }
}

//���û��ṩ��ͨ��Ϣ�������������ִ�
bool CConnection::Open(const char* szIP, 
                       const char* szDBName, 
                       const char* szUserName, 
                       const char* szPassword,
                       bool bAsynchronous)
{
    if (szIP==NULL || strlen(szIP)==0 || 
        szDBName==NULL || strlen(szDBName)==0 || 
        szUserName==NULL || strlen(szUserName)==0 ||
        szPassword==NULL/* || strlen(szPassword)==0*/)      //��������Ϊ��
    {
        return false;
    }

    std::string strConn;

    strConn="Driver=SQL Server;Server=";
    strConn+=szIP;
	strConn+=";Database=";
	strConn+=szDBName;
	strConn+=";UID=";
    strConn+=szUserName;
    strConn+=";PWD=";
	strConn+=szPassword;

    //���������ִ���������
    return Open(strConn.c_str(), bAsynchronous);
}

//���û��Զ��������ִ���������
bool CConnection::Open(const char* szConnectString, bool bAsynchronous)
{
    if (szConnectString==NULL || strlen(szConnectString)==0)
    {
        return false;
    }

    m_strConnect = szConnectString;

    try
    {
        if (m_pCon==NULL)
        {
            m_pCon.CreateInstance(__uuidof(Connection));
        }
        if (m_pCon->GetState() != 0)
        {
            m_pCon->Close();
        }
        CDebugOutPut::LogOut(m_strConnect.c_str());

        HRESULT hRet;
        if ( bAsynchronous )
        {
            hRet = m_pCon->Open(m_strConnect.c_str(), "", "", adAsyncConnect);
        }
        else
        {
            hRet = m_pCon->Open(m_strConnect.c_str(), "", "", adConnectUnspecified);
        }
        
        if (SUCCEEDED(hRet))
        {
            CDebugOutPut::LogOut("connect success!");
            return true;
        }
        else
        {
            CDebugOutPut::LogOut("connect fail!");
            return false;
        }
    }
    catch (_com_error &e)
    {
        CDebugOutPut::ErrOut(m_strConnect.c_str());
        CDebugOutPut::ErrOut(e.Description().GetBSTR());

        return false;
    }
}

bool CConnection::Open(const char* szDSN, const char* szUserName, const char* szPassword)
{
    if (szDSN==NULL || strlen(szDSN)==0 ||
        szUserName==NULL || strlen(szUserName)==0 ||
        szPassword==NULL)
    {
        return false;
    }
    std::string strConn;

    strConn = "DSN=";
    strConn += szDSN;
    strConn += ";UID=";
    strConn += szUserName;
    strConn += ";PWD=";
    strConn += szPassword;

    //���������ִ���������
    return Open(strConn.c_str());
}

/////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////
//ִ��SQL��䷵��һ����¼��
CRecordset CConnection::Execute(const char* szSQL, VARIANT * RecordsAffected, long Options)
{
	//��۵�LOG��������ʱ�ر�
    CDebugOutPut::LogOut(szSQL);

    try
    {
        _RecordsetPtr recordset = m_pCon->Execute(_bstr_t(szSQL), RecordsAffected, Options);
		CDebugOutPut::LogOut("ִ�����");
        return CRecordset(recordset);
    }
    catch (_com_error &e)
    {
        CDebugOutPut::ErrOut(szSQL);
        CDebugOutPut::ErrOut(e.Description().GetBSTR());

        //����
        Open(m_strConnect.c_str());

//        throw e;
        return NULL;
    }
}

CRecordset::CRecordset()
{
//    m_pRecordset.CreateInstance(__uuidof(Recordset));
}

CRecordset::CRecordset(const CRecordset&)
{
//    ��ֹ��vector����������ʱ����������
//    m_pRecordset.CreateInstance(__uuidof(Recordset));
}
        
CRecordset::CRecordset(const _RecordsetPtr &recordset)
{
    m_pRecordset = recordset;
}

CRecordset& CRecordset::operator = (const CRecordset &recordset)
{
    m_pRecordset = recordset.GetRecordsetPtr();
    return *this;
}

CRecordset::~CRecordset()
{
//    m_pRecordset.Release();
}

const char* CRecordset::Get(const char* szField, bool bLog)
{
    static char szBuff[4096];
    try
    {
        _variant_t tmp;
        _bstr_t tmp2;
        tmp = m_pRecordset->GetCollect(szField);
		/*m_pRecordset->Fields->GetItem(szField);*/
        if (tmp.vt==VT_NULL)
        {
            return NULL;
        }
        tmp2 = tmp;
        char* tmp3 = _com_util::ConvertBSTRToString(tmp2);
        m_strRet = tmp3;
        delete [] tmp3;
        tmp3 = NULL;

        if (bLog)
        {
            _snprintf(szBuff, sizeof(szBuff)-1, "��ȡ�ֶΣ�%s", szField);
            CDebugOutPut::LogOut(szBuff);
            CDebugOutPut::LogOut(m_strRet.c_str());
        }
        return m_strRet.c_str();
    }
    catch (_com_error &e)
    {
        _snprintf(szBuff, sizeof(szBuff)-1, "��ȡ�ֶΣ�%s", szField);
        CDebugOutPut::ErrOut(szBuff);
        CDebugOutPut::ErrOut(e.Description().GetBSTR());
        return NULL;
    }
}

bool CRecordset::MoveNext()
{
    try
    {
        return SUCCEEDED(m_pRecordset->MoveNext());
    }
    catch (_com_error &e)
    {
        CDebugOutPut::ErrOut(e.Description().GetBSTR());
        return false;
    }
}

//�α���ǰ�ƶ�
bool CRecordset::MoveFirst()
{
    try
    {
        return SUCCEEDED(m_pRecordset->MoveFirst());
    }
    catch (_com_error &e)
    {
        CDebugOutPut::ErrOut(e.Description().GetBSTR());
        return false;
    }
}

//���ؼ�¼�����Ƿ�Ϊ��
//����������ʱ,����Ϊtrue.
bool CRecordset::IsEmpty() const
{
    try
    {
        if (m_pRecordset->GetFirstOfFile() && m_pRecordset->GetEndOfFile())
        {
            return true;
        }
    }
    catch (_com_error &e)
    {
        CDebugOutPut::ErrOut(e.Description().GetBSTR());
        return true;
    }
    return false;
}

bool CRecordset::IsEOF() const
{
    try
    {
//        //��ʱ������ȼ�����Ϊ2,����boolǿ������ת������
//        #pragma warning (push, 2)
//        return static_cast<bool>(m_pRecordset->GetEndOfFile());
//        #pragma warning (pop)
        if (m_pRecordset->GetEndOfFile())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    catch (_com_error &e)
    {
        CDebugOutPut::ErrOut(e.Description().GetBSTR());
        return true;
    }
}

bool CRecordset::IsOpen() const
{
    return (m_pRecordset!=NULL);
}

const char* CRecordset::GetDateTime(const char* szField, bool bLog)
{
	static char szBuff[4096];
	try
	{
		_variant_t tmp;
		_bstr_t tmp2;
		FieldsPtr fields = m_pRecordset->Fields;
		FieldPtr field = fields->GetItem(szField);
		tmp = field->Value;
		//tmp = m_pRecordset->GetCollect("ga_State");
		
		if (tmp.vt==VT_NULL)
		{
			return NULL;
		}
		tmp2 = tmp;
		char* tmp3 = _com_util::ConvertBSTRToString(tmp2);
		m_strRet = tmp3;
		delete [] tmp3;
		tmp3 = NULL;

		if (bLog)
		{
			_snprintf(szBuff, sizeof(szBuff)-1, "��ȡ�ֶΣ�%s", szField);
			CDebugOutPut::LogOut(szBuff);
			CDebugOutPut::LogOut(m_strRet.c_str());
		}
		return m_strRet.c_str();
	}
	catch (_com_error &e)
	{
		_snprintf(szBuff, sizeof(szBuff)-1, "��ȡ�ֶΣ�%s", szField);
		CDebugOutPut::ErrOut(szBuff);
		CDebugOutPut::ErrOut(e.Description().GetBSTR());
		return NULL;
	}
}
