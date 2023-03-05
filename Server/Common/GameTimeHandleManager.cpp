#include "GameTimeHandleManager.h"
#include "RapidXml/MeRapidXml.h"
#include "Unit.h"
#include "GlobalDBManager.h"
#include "logmgr.h"
#include "Configure.h"
#include "GameStage.h"
#include "GameWorld.h"
#include "AiDefine.h"
#include "MonsterCreater.h"
//�����ִ�к���
bool CreateMonser(TimeHandle& handle)
{
	//���ݲ��� �������� �Ⱦ���Ĳ���
	//ʹ�ô�������
	//д��LOG ���в���
	//MapID  TypeID  x,y,,radio,x,y,r
	if(handle.m_ParamVec.size() != 8) return false;
	unsigned int MapID = handle.m_ParamVec[0].GetUInt();
	if(MapID == 0xFFFFFFFF)
		return false;
	
	unsigned int TypeID = handle.m_ParamVec[1].GetUInt();
	if(TypeID == 0xFFFFFFFF)
		return false;

	float x = handle.m_ParamVec[2].GetFloat();
	float y = handle.m_ParamVec[3].GetFloat();
	float radio = handle.m_ParamVec[4].GetFloat();

	float dirx = handle.m_ParamVec[5].GetFloat();
	float diry = handle.m_ParamVec[6].GetFloat();

	int routeID = handle.m_ParamVec[7].GetInt();

	if(x==-1 || y == -1 || radio == -1 || dirx==-1 || diry==-1 || routeID == -1)
		return false;

    if ( !g_Cfg.IsMapRun( MapID ) )
		return false;

	//���ݲ�����ָ����ͼ ָ��������ˢ��ָ������
	GameStage* pStage = theGameWorld.GetStageById( MapID);
    if ( pStage == NULL )
    { return false; }

	MonsterCreateData xCreateData;
    xCreateData.SetMapID( pStage->GetStageID() );//��ͼID
    xCreateData.SetCreateType( 0 );//������ʽ
    xCreateData.SetCount( 1 );//����
    xCreateData.SetRadius( radio);//��Χ
    xCreateData.SetFightCamp( 0 );//��Ӫ

	xCreateData.SetMonsterID( TypeID );//����ID
    xCreateData.SetPostionX( x);
    xCreateData.SetPostionY( y );
    xCreateData.SetDirX( dirx );
    xCreateData.SetDirY( diry );
    xCreateData.SetRouteID( routeID );
    MonsterCreater::ProcessCreateNormalMonster( xCreateData );
	return true;
}
bool TimeHandle::IsNeedUpdate()
{
	//��ȡ�����ļ������ݿ⵱ǰ��ֵ
	//States
	int DBStates = theGameGlobalDBManager.GetTimeHandleState(TimeLogID);
	//��2��ֵ�����ж� ��ǰ״̬�Ƿ���Ҫ����ִ��
	if(IsInfinite && DBStates >=0)
		return true;
	else if(DBStates <0)
		return false;
	else if(States >0)
	{
		//��ǰ�ǰ�����ִ�е�
		if(DBStates < States)
		{
			if(DBStates >=0)
				return true;
			else
				return false;
		}
		else if(DBStates >= States)
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
	int DBStates = theGameGlobalDBManager.GetTimeHandleState(TimeLogID);
	if(DBStates >=0) return;
	//Ϊ�ű����Ƶ�ʱ��
	if(IsInfinite)
	{
		//�����޴�����ʱ�� 
		if(DBStates != -1)
			return;
		theGameGlobalDBManager.SetTimeHandleState(TimeLogID,1);
	}
	else
	{
		DBStates = DBStates * -1;
		theGameGlobalDBManager.SetTimeHandleState(TimeLogID,DBStates);
	}
}
void TimeHandle::OnUpdateSetValue()
{
	//�������ɹ�ִ�к� ���Ƕ����ݿ�ļ������в���
	//States
	int DBStates = theGameGlobalDBManager.GetTimeHandleState(TimeLogID);
	time_t now;
	time(&now);//��ȡ��ǰʱ��
	theGameGlobalDBManager.SetTimeHandleLog(TimeLogID,now);
	if(IsAutoOrScript)
	{
		//�Զ�++ �Ĵ���
		if(!IsInfinite)//���޵Ĳ���Ҫ�޸����ݿ�ֵ һֱΪ0��Ok
		{
			++DBStates;
			theGameGlobalDBManager.SetTimeHandleState(TimeLogID,DBStates);
		}	
	}
	else
	{
		if(IsInfinite)
		{
			theGameGlobalDBManager.SetTimeHandleState(TimeLogID,-1);
		}
		else
		{
			++DBStates;
			DBStates = DBStates * -1;
			theGameGlobalDBManager.SetTimeHandleState(TimeLogID,DBStates);
		}
	}
}
void TimeHandle::OnInitHandle()
{
	//�ڳ�ʼ����ʱ��ִ��
	if(!IsNeedRESTARTHandel) return;
	unsigned int CrcID = theUnitManager.Crc32(HandleName);
	if(!theGameTimeHandleManager.HandleFunction(CrcID,*this)) return;
	if(theGameGlobalDBManager.GetTimeHandleLog(TimeLogID) == 0)
	{
		OnUpdateSetValue();
	}
}
GameTimeHandleManager::GameTimeHandleManager():m_IsInit(false),m_IsOpen(false)
{
	RegisterAllFunction();//ע�ắ��
	m_xUpdateTimer.StartTimer( 1,1000);
}
bool GameTimeHandleManager::LoadFileConfig(const char* FilePath)
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
void GameTimeHandleManager::SetInit()
{
	m_IsInit = true;
	HandleReStartTimeHandle();
}
TimeHandle* GameTimeHandleManager::GetTimeHandleByTimeLogID(unsigned int LogID)
{
	std::vector<TimeHandle>::iterator Iter = m_HandleList.begin();
	for(;Iter != m_HandleList.end();++Iter)
	{
		if(Iter->TimeLogID == LogID)
			return &(*Iter);
	}
	return NULL;
}
bool GameTimeHandleManager::HandleFunction(unsigned int CrcID,TimeHandle& handle)
{
	if(m_HandleFunList.count(CrcID) != 1) return false;
	if(!(*m_HandleFunList[CrcID])(handle)) return false;
	return true;
}
void GameTimeHandleManager::HandleReStartTimeHandle()
{
	//����ִ����Щ ��Ҫ��������ִ�еĺ��� 
	if(m_HandleList.empty()) return;
	if(!m_IsOpen) return;//δ��������Ҫִ��
	time_t now;
	time(&now);//��ȡ��ǰʱ��
	std::vector<TimeHandle>::iterator Iter = m_HandleList.begin();
	for(;Iter != m_HandleList.end();++Iter)
	{
		Iter->OnInitHandle();
	}
}
bool GameTimeHandleManager::HandleTimeHandleStr(std::string& str,TimeHandle& handle)
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
void GameTimeHandleManager::RegisterAllFunction()
{
	RegisterFunction(&CreateMonser,"createmonster");
}
void GameTimeHandleManager::RegisterFunction(HandleFun fun,std::string strName)
{
	unsigned int ID = theUnitManager.Crc32(strName);
	m_HandleFunList.insert(std::map<unsigned int,HandleFun>::value_type(ID,fun));
}
bool GameTimeHandleManager::IsNeedUpdate(unsigned int TimeLog,time_t& timeNow,unsigned int TimeStep)
{
	 __int64 TimeDB = theGameGlobalDBManager.GetTimeHandleLog(TimeLog);//��ȡ�洢�����ݿ��������
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
void GameTimeHandleManager::Update(unsigned int nCurrentTime)
{
	if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
		return;
	if(!m_IsInit) return;
	if(!m_IsOpen) return;
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