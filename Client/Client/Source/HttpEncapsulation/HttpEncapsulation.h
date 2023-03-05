/////////////////////////////////////////////////////
//��ʱ���ͻ���������֤��HTTP POST������,���˿�չ����,����������������
//SHttpTaskΪ����������Ľṹ,��ϸ���˽ṹ by vvx 2012.11.20---debugcommand@hotmail.com
/////////////////////////////////////////////////////
#pragma once
#include<windows.h>
#include<wininet.h>
#include <string>
#include "ossome.h"

//����ͽ���Ļص�����,������,����ֱ����
typedef void (CallResultFun)(struct SHttpTask*);
typedef void (CallFunErr)(struct SHttpTask*);


#define MAX_USERNAME 32
#define MAX_PASSWORDS 128

using namespace std;

typedef struct  InternetContext
{
	HINTERNET  hInstanceOpen;//
	HANDLE     hExitEvent;
}InternetContext;

namespace TaskTypeDefine
{
#pragma pack(push,1)
	struct SAccountInfo
	{
		char user_name[MAX_USERNAME];
		char passwords[MAX_PASSWORDS];
	};
#pragma pack(pop)
};


enum etasktype
{
	etasktype_login = 0,
	etasktype_max,
};

enum etaskresult
{
	etaskresult_fail = 0,
	etaskresult_succ,
	etaskresult_error,
	etaskresult_max
};

enum eLoginResult
{
	eLoginResult_succ = 1,//1���ɹ�
	eLoginResult_noAccount,//2���˺Ų�����
	eLoginResult_errorpasswords,//3���������
	eLoginResult_servererror,//4����¼��֤�������쳣�����Ժ�����
	eLoginResult_max
};

//�������������Ľṹ,����union���������������ֽṹ,���������������
struct SHttpTask
{
	union
	{
		TaskTypeDefine::SAccountInfo accountinfo;
	}task_detail;

	short task_type;
	short task_result;

	//��ʱ������,���Ҫ�õĻ���ע��,ע��дһ����ʼ������,��2���ص�������ֵ
	/*CallResultFun*  resultFun;
	CallFunErr *     errFun;*/

	SHttpTask()
	{
		memset(this,0,sizeof(*this));
		task_type = etasktype_max;
		task_result = etaskresult_max;
		//resultFun = NULL;
		//errFun = NULL;
	}
	~SHttpTask()
	{
	}
};

//http���������list����,֧�ֶ��߳�д��,���õ���Ŷ��---by vvx 2012.11.20
class CHttpTaskList
{
public:
	struct SHttpTaskNode
	{
		SHttpTaskNode()
		{
			pData = NULL;
			pNext = NULL;
			pPer = NULL;
		}
		SHttpTask* pData;
		SHttpTaskNode* pNext;
		SHttpTaskNode* pPer;
	};
public:
	CHttpTaskList()
	{
		m_CurrentNode = NULL;
		LOCK_INIT(&m_lock);
	}
	~CHttpTaskList()
	{
		LOCK_DELETE(&m_lock);
	}

	bool PushTask(SHttpTask* pData)
	{
		if (!pData)
		{
			return false;
		}
		LOCK_LOCK(&m_lock);
		SHttpTaskNode* pNode = new SHttpTaskNode;
		pNode->pData = pData;
		pNode->pNext = &m_End;
		if(m_End.pPer == NULL)
		{
			m_End.pPer = pNode;
			pNode->pPer = &m_Header;
			m_Header.pNext= pNode;
		}
		else
		{
			pNode->pPer = m_End.pPer;
			SHttpTaskNode* pOldNode = m_End.pPer;
			m_End.pPer = pNode;
			pOldNode->pNext = pNode;
		}
		LOCK_UNLOCK(&m_lock);
	}
	SHttpTask* PopTask()
	{
		if(NULL == m_Header.pNext)
			return NULL;

		LOCK_LOCK(&m_lock);
		SHttpTask* pData = NULL;
		if(m_Header.pNext == m_CurrentNode && m_CurrentNode != NULL)
		{
			if(m_CurrentNode->pNext == &m_End)
			{
				LOCK_UNLOCK(&m_lock);
				return NULL;
			}
			pData = m_CurrentNode->pNext->pData;
			m_Header.pNext = m_CurrentNode->pNext;
			SHttpTaskNode* pOldNode = m_CurrentNode;
			m_CurrentNode = m_CurrentNode->pNext;
			delete pOldNode;
			LOCK_UNLOCK(&m_lock);
			return pData;
		}
		m_CurrentNode = m_Header.pNext;
		pData = m_Header.pNext->pData;
		LOCK_UNLOCK(&m_lock);
		return pData;
	}

private:
	LOCK_struct m_lock;

	SHttpTaskNode  m_Header;
	SHttpTaskNode  m_End;
	SHttpTaskNode* m_CurrentNode;
};


//HTTP������ͷ��ز���������
class CHttpEncapsulation
{
public:
	CHttpEncapsulation(void);
	~CHttpEncapsulation(void);

	static CHttpEncapsulation& Instance()
	{
		static CHttpEncapsulation chen;
		return chen;
	}

	//��һ��Internet���õ�
	bool OpenInternet(const char* address);
	//�ر�Internet
	void  CloseInternet();
	//�����߳�
	static void InternetTask_Do(void*);

	bool AddHttTask(SHttpTask* pTask);
private:
	InternetContext     m_Context;
	string username;
	string passwords;
	CHttpTaskList m_HttpTaskList;
};

#define theHttpEncapsulation CHttpEncapsulation::Instance()
