/////////////////////////////////////////////////////
//暂时给客户端用来认证的HTTP POST任务类,加了宽展功能,可以用作其他方面
//SHttpTask为了请求任务的结构,详细见此结构 by vvx 2012.11.20---debugcommand@hotmail.com
/////////////////////////////////////////////////////
#pragma once
#include<windows.h>
#include<wininet.h>
#include <string>
#include "ossome.h"

//错误和结果的回调函数,定义了,可以直接用
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
	eLoginResult_succ = 1,//1、成功
	eLoginResult_noAccount,//2、账号不存在
	eLoginResult_errorpasswords,//3、密码错误
	eLoginResult_servererror,//4、登录验证服务器异常，请稍后再试
	eLoginResult_max
};

//这里的请求任务的结构,加了union用来根据类型区分结构,可以用作多个方面
struct SHttpTask
{
	union
	{
		TaskTypeDefine::SAccountInfo accountinfo;
	}task_detail;

	short task_type;
	short task_result;

	//暂时不用他,如果要用的话打开注释,注意写一个初始化函数,给2个回调函数赋值
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

//http任务请求的list管理,支持多线程写入,不用担心哦亲---by vvx 2012.11.20
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


//HTTP的请求和返回操作在这里
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

	//打开一个Internet可用的
	bool OpenInternet(const char* address);
	//关闭Internet
	void  CloseInternet();
	//工作线程
	static void InternetTask_Do(void*);

	bool AddHttTask(SHttpTask* pTask);
private:
	InternetContext     m_Context;
	string username;
	string passwords;
	CHttpTaskList m_HttpTaskList;
};

#define theHttpEncapsulation CHttpEncapsulation::Instance()
