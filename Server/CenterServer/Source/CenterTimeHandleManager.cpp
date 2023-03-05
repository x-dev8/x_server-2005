#include "CenterTimeHandleManager.h"
#include "RapidXml/MeRapidXml.h"
#include "Unit.h"
#include "GlobalDBManager.h"
#include "logmgr.h"
//具体的执行函数
//bool CreateMonser(TimeHandle& handle)
//{
//	//根据参数 创建怪物 等具体的操作
//	//使用创建函数
//	//写个LOG 进行测试
//	/*SYSTEMTIME time;
//	GetSystemTime(&time);
//	char ss[24];
//	itoa(time.wSecond,ss,10);
//	LOG_MESSAGE( "TimeHandle.log", 7,ss);*/
//	return false;
//}
bool TimeHandle::IsNeedUpdate()
{
	//读取配置文件和数据库当前的值
	//States
	int DBStates = theCenterGlobalDBManager.GetTimeHandleState(TimeLogID);
	//对2个值进行判断 当前状态是否需要继续执行
	if(IsInfinite && DBStates >=0)
		return true;
	else if(DBStates <0)
		return false;
	else if(States >0)
	{
		//当前是按次数执行的
		if(DBStates <= States)
		{
			if(DBStates >=0)
				return true;
			else
				return false;
		}
		else if(DBStates > States)
		{
			return false;
		}
	}
	else if(States <= 0)
		return false;
	return false;
}
void TimeHandle::OnScriptReset()
{
	//脚本执行 将DBStates 的值进行还原 继续执行
	if(IsAutoOrScript)
		return;
	int DBStates = theCenterGlobalDBManager.GetTimeHandleState(TimeLogID);
	if(DBStates >=0) return;
	//为脚本控制的时候
	if(IsInfinite)
	{
		//当不限次数的时候 
		if(DBStates != -1)
			return;
		theCenterGlobalDBManager.SetTimeHandleState(TimeLogID,1);
	}
	else
	{
		DBStates = DBStates * -1;
		theCenterGlobalDBManager.SetTimeHandleState(TimeLogID,DBStates);
	}
}
void TimeHandle::OnUpdateSetValue()
{
	//当函数成功执行后 我们对数据库的计数进行操作
	//States
	int DBStates = theCenterGlobalDBManager.GetTimeHandleState(TimeLogID);
	time_t now;
	time(&now);//获取当前时间
	theCenterGlobalDBManager.SetTimeHandleLog(TimeLogID,now);
	if(IsAutoOrScript)
	{
		//自动++ 的处理
		if(!IsInfinite)//无限的不需要修改数据库值 一直为0就Ok
		{
			++DBStates;
			theCenterGlobalDBManager.SetTimeHandleState(TimeLogID,DBStates);
		}	
	}
	else
	{
		if(IsInfinite)
		{
			theCenterGlobalDBManager.SetTimeHandleState(TimeLogID,-1);
		}
		else
		{
			++DBStates;
			DBStates = DBStates * -1;
			theCenterGlobalDBManager.SetTimeHandleState(TimeLogID,DBStates);
		}
	}
}
void TimeHandle::OnInitHandle()
{
	//在初始化的时候执行
	if(!IsNeedRESTARTHandel) return;
	unsigned int CrcID = theUnitManager.Crc32(HandleName);
	if(!theCenterTimeHandleManager.HandleFunction(CrcID,*this))
		return;
	if(theCenterGlobalDBManager.GetTimeHandleLog(TimeLogID) == 0)
	{
		OnUpdateSetValue();
	}
}
bool CenterTimeHandleManager::HandleFunction(unsigned int CrcID,TimeHandle& handle)
{
	if(m_HandleFunList.count(CrcID) != 1) return false;
	if(!(*m_HandleFunList[CrcID])(handle)) return false;
	return true;
}
CenterTimeHandleManager::CenterTimeHandleManager():m_IsInit(false)
{
	RegisterAllFunction();//注册函数
	m_xUpdateTimer.StartTimer( 1,1000);
}
bool CenterTimeHandleManager::LoadFileConfig(const char* FilePath)
{
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(FilePath)) return false;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("TimeHandle");
	if(pRoot != NULL)
	{
		int IsOpen = 0;
		if (pRoot->Attribute("IsOpen",&IsOpen) == NULL)
			return false;
		m_IsOpen = IsOpen==1?true:false;
		if(!m_IsOpen) return true;
		MeXmlElement* pInfo = pRoot->FirstChildElement("Info");
		while (pInfo != NULL)
		{
			TimeHandle th;
		
			int ID = 0;
			if (pInfo->Attribute("ID",&ID) == NULL)
				return false;
			th.ID = ID;
			
			int TimeStep =0;
			if (pInfo->Attribute("TimeStep",&TimeStep) == NULL)
				return false;
			th.TimeStep = TimeStep;

			int TimeLog = 0;
			if (pInfo->Attribute("TimeLog",&TimeLog) == NULL)
				return false;
			th.TimeLogID = TimeLog;

			if (pInfo->Attribute("States",&th.States) == NULL)
				return false;

			int IsAutoOrScript = 0;
			if (pInfo->Attribute("IsAutoOrScript",&IsAutoOrScript) == NULL)
				return false;
			th.IsAutoOrScript = IsAutoOrScript==1?true:false;

			int IsNeedReStart = 0;
			if (pInfo->Attribute("IsNeedReStart",&IsNeedReStart) == NULL)
				return false;
			th.IsNeedRESTARTHandel = IsNeedReStart==1?true:false;

			int IsInfinite = 0;
			if (pInfo->Attribute("IsInfinite",&IsInfinite) == NULL)
				return false;
			th.IsInfinite = IsInfinite==1?true:false;
	
			std::string info;
			info = pInfo->Attribute("Handle");
			if(HandleTimeHandleStr(info,th))
				m_HandleList.push_back(th);

			pInfo = pInfo->NextSiblingElement("info");
		}
		return true;
	}
	else
		return false;
}
void CenterTimeHandleManager::SetInit()
{
	m_IsInit = true;
	HandleReStartTimeHandle();
}
void CenterTimeHandleManager::HandleReStartTimeHandle()
{
	//马上执行那些 需要重启重新执行的函数 
	if(!m_IsOpen) return ;
	if(m_HandleList.empty()) return;
	time_t now;
	time(&now);//获取当前时间
	std::vector<TimeHandle>::iterator Iter = m_HandleList.begin();
	for(;Iter != m_HandleList.end();++Iter)
	{
		Iter->OnInitHandle();
	}
}
bool CenterTimeHandleManager::HandleTimeHandleStr(std::string& str,TimeHandle& handle)
{
	//解析字符串 "createmonster:u:id,f:x,f:y,f:z,f:r"
	handle.HandleName = str.substr(0,str.find_first_of(':'));
	std::string other = str.substr(str.find_first_of(':')+1);
	//将other进行切割 按','进行切割 u:id,f:x,f:y,f:z,f:r
	size_t begin=0;
	size_t end = 0;
	while(end<other.size())
	{
		if(other[end] == ',')
		{
			TimeHandleParm param;
			param.SetParam(other.substr(begin,end-begin));
			handle.m_ParamVec.push_back(param);
			begin = end +1;
		}
		else if(end == other.size() -1)
		{
			//已经到了结束
			TimeHandleParm param;
			param.SetParam(other.substr(begin,end-begin));
			handle.m_ParamVec.push_back(param);
			begin = end +1;
		}
		++end;
	}
	return true;
}
void CenterTimeHandleManager::RegisterAllFunction()
{
	//RegisterFunction(&CreateMonser,"createmonster");
}
void CenterTimeHandleManager::RegisterFunction(HandleFun fun,std::string strName)
{
	unsigned int ID = theUnitManager.Crc32(strName);
	m_HandleFunList.insert(std::map<unsigned int,HandleFun>::value_type(ID,fun));
}
bool CenterTimeHandleManager::IsNeedUpdate(unsigned int TimeLog,time_t& timeNow,unsigned int TimeStep)
{
	 __int64 TimeDB = theCenterGlobalDBManager.GetTimeHandleLog(TimeLog);//获取存储在数据库里的数据
	 if(TimeDB == 0)
		 return true;
	time_t TimeLogDB = TimeDB;
	//判断时间间隔
	double SpanTime = difftime(timeNow,TimeLogDB);
	if(SpanTime >= TimeStep)
		return true;
	else
		return false;
}
void CenterTimeHandleManager::Update(unsigned int nCurrentTime)
{
	if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
		return;
	if(!m_IsOpen) return ;
	if(!m_IsInit) return;
	//对现有的数据进行更新
	//1.获取当前时间
	time_t now;
	time(&now);//获取当前时间
	std::vector<TimeHandle>::iterator Iter = m_HandleList.begin();
	for(;Iter != m_HandleList.end();++Iter)
	{
		unsigned int ID = Iter->ID;
		unsigned int TimeStep = Iter->TimeStep;
		unsigned int CrcID = theUnitManager.Crc32(Iter->HandleName);
		int States = Iter->States;
		bool IsAutoOrScript = Iter->IsAutoOrScript;
		//先判断状态是否需要执行
		if(!Iter->IsNeedUpdate()) continue;
		//根据当前数据 数据库的时间 和 配置文件的时间间隔 判断是否需要执行函数
		if(IsNeedUpdate(Iter->TimeLogID,now,TimeStep))
		{
			//如果需要执行的话 
			//1.刷新数据库的时间为当前时间		
			//2.执行函数
			if(m_HandleFunList.count(CrcID) == 1)
			{
				if((*m_HandleFunList[CrcID])(*Iter))
				{
					Iter->OnUpdateSetValue();
				}
			}
		}
	}
}