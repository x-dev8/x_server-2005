#pragma once
#include "Singleton.h"
#include "GameTimer.h"
#include <map>
struct TimeHandleParm
{
public:
	enum ParamStates
	{
		PS_Error  = 0,
		PS_Float,
		PS_Int,
		PS_UInt,
		PS_Str,
		PS_StrManLength = 128,
	};

	TimeHandleParm():m_IsStates(PS_Error){}

	int GetInt()
	{
		if(m_IsStates != PS_Int)
			return -1;
		return m_Param.paramInt;
	}

	float GetFloat()
	{
		if(m_IsStates != PS_Float)
			return -1;
		return m_Param.paramFloat;
	}

	unsigned int GetUInt()
	{
		if(m_IsStates != PS_UInt)
			return -1;
		return m_Param.paramUInt;
	}

	const char* GetStr()
	{
		if(m_IsStates != PS_Str)
			return NULL;
		return m_Param.paramStr;
	}

	ParamStates GetParamStates(){return m_IsStates;}

	void SetParam(std::string& str)
	{
		//���� �и���ַ��� ��ȡ����
		//"s:xxx"
		switch(str[0])
		{
		case 's':
			{
				m_IsStates = TimeHandleParm::PS_Str;
				strcpy_s(m_Param.paramStr,PS_StrManLength,str.substr(2).c_str());
			}
			break;
		case 'u':
			{
				m_IsStates = TimeHandleParm::PS_UInt;
				__int64 sLong =  _atoi64(str.substr(2).c_str());
				m_Param.paramUInt = static_cast<unsigned int>(sLong);
			}
			break;
		case 'i':
			{
				m_IsStates = TimeHandleParm::PS_Int;
				m_Param.paramInt = atoi(str.substr(2).c_str());
			}
			break;
		case 'f':
			{
				m_IsStates = TimeHandleParm::PS_Float;
				m_Param.paramFloat =  static_cast<float>(atof(str.substr(2).c_str()));
			}
			break;
		default:
			m_IsStates = TimeHandleParm::PS_Error;
			break;
		}
	}
private:
	union Param
	{
			float			paramFloat;
			int				paramInt;
			unsigned int	paramUInt;
			char			paramStr[PS_StrManLength];
		};
	Param				m_Param;
	ParamStates			m_IsStates;
};
struct TimeHandle //�����ļ���һ����Ϣ �����ִ����ҪһGlobalDB�������
{
	unsigned int ID;//��ʾID
	unsigned int TimeStep;//ʱ����
	unsigned int TimeLogID;//��¼�����ݿ����õ�ʱ�������
	int States;//״̬��ֵ  0Ϊ��ִ�� ����0Ϊִ�д���
	bool IsInfinite;//�Ƿ�����ִ��
	bool IsAutoOrScript;
	bool IsNeedRESTARTHandel;//�Ƿ���Ҫ��������������ִ��
	//����ִ�е����� ���� ��"createmonster:u:ID,f:x,f:y,f:z,f:raido"�������ַ��� ������Ҫ���д���
	std::string	 HandleName;//��������
	std::vector<TimeHandleParm>	m_ParamVec;//�������ϴ���

	bool IsNeedUpdate();//�жϵ�ǰ״̬���Ƿ���Ҫ����
	void OnScriptReset();//�ű������� ����ֵ
	void OnUpdateSetValue();//ִ�гɹ�������ֵ
	void OnInitHandle();
};
class GameTimeHandleManager  : public ISingletion<GameTimeHandleManager>//Ӧ��Center��GameServer ��һ�� ֮�䲻�����໥ͨѶ �����и��Ե�Update ��ʱ��
{
public:
	GameTimeHandleManager();
	~GameTimeHandleManager(){}
	bool LoadFileConfig(const char* FilePath);//��ȡ�����ļ�

	void Update(unsigned int nCurrentTime);

	void SetInit();
	TimeHandle* GetTimeHandleByTimeLogID(unsigned int LogID);
	bool HandleFunction(unsigned int CrcID,TimeHandle& handle);
private:
	bool HandleTimeHandleStr(std::string& str,TimeHandle& handle);//����
	
	typedef bool (*HandleFun)(TimeHandle& handle);
	void RegisterAllFunction();
	void RegisterFunction(HandleFun fun,std::string strName);

	bool IsNeedUpdate(unsigned int TimeLog,time_t& timeNow,unsigned int TimeStep);
	void HandleReStartTimeHandle();
private:
	bool								m_IsOpen;
	bool								m_IsInit;
	std::vector<TimeHandle>				m_HandleList;//�����ļ������õ������¼�
	std::map<unsigned int,HandleFun>	m_HandleFunList;//�洢����center��ִ�к���
	GameTimerEx							m_xUpdateTimer;     // ���¶�ʱ��
};
#define theGameTimeHandleManager GameTimeHandleManager::Instance()