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
		//根据 切割的字符串 获取参数
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
struct TimeHandle //配置文件的一条信息 具体的执行需要一GlobalDB进行配合
{
	unsigned int ID;//标示ID
	unsigned int TimeStep;//时间间隔
	unsigned int TimeLogID;//记录在数据库中用的时间的索引
	int States;//状态数值  0为不执行 大于0为执行次数
	bool IsInfinite;//是否无限执行
	bool IsAutoOrScript;
	bool IsNeedRESTARTHandel;//是否需要在重新启动后再执行
	//具体执行的主体 参数 如"createmonster:u:ID,f:x,f:y,f:z,f:raido"这样的字符串 我们需要进行处理
	std::string	 HandleName;//函数名称
	std::vector<TimeHandleParm>	m_ParamVec;//参数集合处理

	bool IsNeedUpdate();//判断当前状态下是否需要更新
	void OnScriptReset();//脚本触发了 重置值
	void OnUpdateSetValue();//执行成功后设置值
	void OnInitHandle();
};
class GameTimeHandleManager  : public ISingletion<GameTimeHandleManager>//应该Center和GameServer 各一个 之间不进行相互通讯 各自有各自的Update 和时间
{
public:
	GameTimeHandleManager();
	~GameTimeHandleManager(){}
	bool LoadFileConfig(const char* FilePath);//读取配置文件

	void Update(unsigned int nCurrentTime);

	void SetInit();
	TimeHandle* GetTimeHandleByTimeLogID(unsigned int LogID);
	bool HandleFunction(unsigned int CrcID,TimeHandle& handle);
private:
	bool HandleTimeHandleStr(std::string& str,TimeHandle& handle);//加载
	
	typedef bool (*HandleFun)(TimeHandle& handle);
	void RegisterAllFunction();
	void RegisterFunction(HandleFun fun,std::string strName);

	bool IsNeedUpdate(unsigned int TimeLog,time_t& timeNow,unsigned int TimeStep);
	void HandleReStartTimeHandle();
private:
	bool								m_IsOpen;
	bool								m_IsInit;
	std::vector<TimeHandle>				m_HandleList;//配置文件中配置的所有事件
	std::map<unsigned int,HandleFun>	m_HandleFunList;//存储所有center的执行函数
	GameTimerEx							m_xUpdateTimer;     // 更新定时器
};
#define theGameTimeHandleManager GameTimeHandleManager::Instance()