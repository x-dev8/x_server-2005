#include "CenterTimeHandleManager.h"
#include "RapidXml/MeRapidXml.h"
#include "Unit.h"
#include "GlobalDBManager.h"
#include "logmgr.h"
//�����ִ�к���
//bool CreateMonser(TimeHandle& handle)
//{
//	//���ݲ��� �������� �Ⱦ���Ĳ���
//	//ʹ�ô�������
//	//д��LOG ���в���
//	/*SYSTEMTIME time;
//	GetSystemTime(&time);
//	char ss[24];
//	itoa(time.wSecond,ss,10);
//	LOG_MESSAGE( "TimeHandle.log", 7,ss);*/
//	return false;
//}
bool TimeHandle::IsNeedUpdate()
{
	//��ȡ�����ļ������ݿ⵱ǰ��ֵ
	//States
	int DBStates = theCenterGlobalDBManager.GetTimeHandleState(TimeLogID);
	//��2��ֵ�����ж� ��ǰ״̬�Ƿ���Ҫ����ִ��
	if(IsInfinite && DBStates >=0)
		return true;
	else if(DBStates <0)
		return false;
	else if(States >0)
	{
		//��ǰ�ǰ�����ִ�е�
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
	//�ű�ִ�� ��DBStates ��ֵ���л�ԭ ����ִ��
	if(IsAutoOrScript)
		return;
	int DBStates = theCenterGlobalDBManager.GetTimeHandleState(TimeLogID);
	if(DBStates >=0) return;
	//Ϊ�ű����Ƶ�ʱ��
	if(IsInfinite)
	{
		//�����޴�����ʱ�� 
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
	//�������ɹ�ִ�к� ���Ƕ����ݿ�ļ������в���
	//States
	int DBStates = theCenterGlobalDBManager.GetTimeHandleState(TimeLogID);
	time_t now;
	time(&now);//��ȡ��ǰʱ��
	theCenterGlobalDBManager.SetTimeHandleLog(TimeLogID,now);
	if(IsAutoOrScript)
	{
		//�Զ�++ �Ĵ���
		if(!IsInfinite)//���޵Ĳ���Ҫ�޸����ݿ�ֵ һֱΪ0��Ok
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
	//�ڳ�ʼ����ʱ��ִ��
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
	RegisterAllFunction();//ע�ắ��
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
	//����ִ����Щ ��Ҫ��������ִ�еĺ��� 
	if(!m_IsOpen) return ;
	if(m_HandleList.empty()) return;
	time_t now;
	time(&now);//��ȡ��ǰʱ��
	std::vector<TimeHandle>::iterator Iter = m_HandleList.begin();
	for(;Iter != m_HandleList.end();++Iter)
	{
		Iter->OnInitHandle();
	}
}
bool CenterTimeHandleManager::HandleTimeHandleStr(std::string& str,TimeHandle& handle)
{
	//�����ַ��� "createmonster:u:id,f:x,f:y,f:z,f:r"
	handle.HandleName = str.substr(0,str.find_first_of(':'));
	std::string other = str.substr(str.find_first_of(':')+1);
	//��other�����и� ��','�����и� u:id,f:x,f:y,f:z,f:r
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
			//�Ѿ����˽���
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
	 __int64 TimeDB = theCenterGlobalDBManager.GetTimeHandleLog(TimeLog);//��ȡ�洢�����ݿ��������
	 if(TimeDB == 0)
		 return true;
	time_t TimeLogDB = TimeDB;
	//�ж�ʱ����
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
	//�����е����ݽ��и���
	//1.��ȡ��ǰʱ��
	time_t now;
	time(&now);//��ȡ��ǰʱ��
	std::vector<TimeHandle>::iterator Iter = m_HandleList.begin();
	for(;Iter != m_HandleList.end();++Iter)
	{
		unsigned int ID = Iter->ID;
		unsigned int TimeStep = Iter->TimeStep;
		unsigned int CrcID = theUnitManager.Crc32(Iter->HandleName);
		int States = Iter->States;
		bool IsAutoOrScript = Iter->IsAutoOrScript;
		//���ж�״̬�Ƿ���Ҫִ��
		if(!Iter->IsNeedUpdate()) continue;
		//���ݵ�ǰ���� ���ݿ��ʱ�� �� �����ļ���ʱ���� �ж��Ƿ���Ҫִ�к���
		if(IsNeedUpdate(Iter->TimeLogID,now,TimeStep))
		{
			//�����Ҫִ�еĻ� 
			//1.ˢ�����ݿ��ʱ��Ϊ��ǰʱ��		
			//2.ִ�к���
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