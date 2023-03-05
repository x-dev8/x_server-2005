#include "HttpEncapsulation.h"
#include <WinSock2.h>
#include "curl/curl.h"
#include "curl/curl.h"
#include <assert.h>
#include "json/reader.h"
#include "json/writer.h"
#include <process.h>
#include "MessageDefine.h"
#include "MessageProcess.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Cfg.h"

#define CURL_ERROR_SIZE 256

////////////////////post////////////////////////////////////////
static char errorBuffer[CURL_ERROR_SIZE]; 
static const int _defaulttimeout = 300;
static string curlbuffer;

int curlwriter(char *data, size_t size, size_t nmemb, string *writerData)
{
	if (writerData == NULL)
		return 0;
	int len = size*nmemb;
	writerData->append(data, len); 

	return len;
}

void _setCurlopt(CURL *curl,const string& url) 
{
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, _defaulttimeout);
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlwriter);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlbuffer); 
}

string curl_post(const string& url, const string& content)
{
	curlbuffer="";
	CURL *curl = curl_easy_init();
	if(curl == NULL)
	{
		assert(false&&"curl_easy_init failed");
	}   

	_setCurlopt(curl,url);
	curl_easy_setopt(curl, CURLOPT_POST, 1 );
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content.c_str());    

	CURLcode code = curl_easy_perform(curl);
	if(code != CURLE_OK)
	{
		assert(false&&"curl_easy_perform failed:code != CURLE_OK");
	}
	curl_easy_cleanup(curl);

	return curlbuffer;
}
////////////////////////////////////////////////////////////////////////

CHttpEncapsulation::CHttpEncapsulation(void)
{
	OpenInternet("testing");
}

CHttpEncapsulation::~CHttpEncapsulation(void)
{
}

bool CHttpEncapsulation::OpenInternet(const char* address)
{
	if (!address)
	{
		return false;
	}

	m_Context.hInstanceOpen = InternetOpen(address, 
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);
	if (m_Context.hInstanceOpen == NULL)
	{
		return false;
	}
	m_Context.hExitEvent = CreateEvent(NULL,0,0,0);//这个是控制线程用的句柄

	_beginthread(InternetTask_Do,0,this);//创建线程
	return true;
}

void CHttpEncapsulation::CloseInternet()
{
	SetEvent(m_Context.hExitEvent);
	CloseHandle(m_Context.hExitEvent);
	InternetCloseHandle(m_Context.hInstanceOpen);
}

bool CHttpEncapsulation::AddHttTask(SHttpTask* pTask)
{
	if (!pTask)
	{
		return false;
	}
	return m_HttpTaskList.PushTask(pTask);
}

void  CHttpEncapsulation::InternetTask_Do(void* pThis)
{
	//这里不只是帐号认证请求使用,之后其他的也可以进入这边来请求
	if(!pThis)
		return ;
	CHttpEncapsulation* pWorkThis = (CHttpEncapsulation*)pThis;
	while(WAIT_TIMEOUT ==  WaitForSingleObject(pWorkThis->m_Context.hExitEvent,2000))
	{
		//判断是否需要进入这里
		SHttpTask* pTask = pWorkThis->m_HttpTaskList.PopTask();
		if (pTask)
		{
			//监测当前地址是否可用
			bool bCheck = InternetCheckConnection(gCfg.m_strHttp.c_str(),
													FLAG_ICC_FORCE_CONNECTION,0);
			if (!bCheck)
			{
				//todo:地址不可用,做下什么通知什么的,比如SHttpTask里面加一个回调函数用来返回错误
				/*if(pTask->errFun)
				{
					(*pTask->errFun)(pTask);
				}*/
				continue;
			}

			//"地址"&"根据任务拼接的字符串""username=sanguo00222&password=12345"
			string url_string = "username=";
			url_string += pTask->task_detail.accountinfo.user_name;
			url_string += "&password=";
			url_string += pTask->task_detail.accountinfo.passwords;

			std::string str=curl_post(gCfg.m_strHttp.c_str(),url_string.c_str());
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(str, root);
			if (ret)
			{//收到JSON返回值信息,并解析成功
			//返回格式说明:返回参数按顺序为 【帐号名，帐号ID，认证结果，session，防沉迷标记】
				const Json::Value& result = root[2];
				int login_res = atoi(result.asString().c_str());
				switch(login_res)
				{
				case eLoginResult_succ:
					{
						//const Json::Value& account_name  =root[0];
						const Json::Value& account_id    =root[1];
						const Json::Value& session       =root[3];
						const Json::Value& indulge       =root[4];

						theHeroGame.GetPlayerMgr()->m_dwAccountID = atoi(account_id.asString().c_str());
						theHeroGame.GetPlayerMgr()->m_strSessionKey = session.asString();

						MsgSwitchGate msg;
						msg.nResult = ER_Success;
						msg.uGatePort = gCfg.m_iServerPort;
						memcpy(msg.szGateIP,gCfg.m_szDstIP,60*sizeof(char));
						memcpy(msg.szChannelName,"Char Server",MAX_NAME_STRING*sizeof(char));
						msg.nServerType = ST_CharacterServer;
						theHeroGame.ProcessSwitchGateMsg(&msg);
					}
					break;
				case eLoginResult_noAccount:
				case eLoginResult_errorpasswords:
				case eLoginResult_servererror:
				default:
					{
						MsgAckLogin msg;
						msg.stErrorCode = login_res;
						g_MessageProcess.GameLoginMsg(&msg);
					}
					break;
				}
			}
			else
			{//如果解析失败
			}
			//注意DELETE掉任务指针,POP出来的
			delete pTask;
		}
		Sleep(100);
	}
}