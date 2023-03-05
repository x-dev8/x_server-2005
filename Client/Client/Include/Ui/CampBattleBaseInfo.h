/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CampBattleBaseInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "ScreenInfoManager.h"

#ifndef ID_FRAME_CampBattleBaseInfo
#define ID_FRAME_CampBattleBaseInfo		"ID_FRAME_CampBattleBaseInfo"
#endif  ID_FRAME_CampBattleBaseInfo
#ifndef ID_CHECKBOX_GuoWang
#define ID_CHECKBOX_GuoWang		"ID_CHECKBOX_GuoWang"
#endif  ID_CHECKBOX_GuoWang
#ifndef ID_CHECKBOX_Guild
#define ID_CHECKBOX_Guild		"ID_CHECKBOX_Guild"
#endif  ID_CHECKBOX_Guild
#ifndef ID_CHECKBOX_Union
#define ID_CHECKBOX_Union		"ID_CHECKBOX_Union"
#endif  ID_CHECKBOX_Union
#ifndef ID_CHECKBOX_World
#define ID_CHECKBOX_World		"ID_CHECKBOX_World"
#endif  ID_CHECKBOX_World


class TimeSetting
{
public:
    int GetDayOfWeek() const { return nDayOfWeek; }
    int GetHour() const { return nHour; }
    int GetMinute() const { return nMinute; }
    int GetKeepTime() const { return nKeepTime; }

    void SetDayOfWeek( int nValue ) { nDayOfWeek = nValue; }
    void SetHour( int nValue ) { nHour = nValue; }
    void SetMinute( int nValue ) { nMinute = nValue; }
    void SetKeepTime( int nValue ) { nKeepTime = nValue; }
private:
    int nDayOfWeek;
    int nHour;
    int nMinute;
    int nKeepTime;      // 多久时间( 单位: 分钟 )
};
struct CampBattleTimeInfo
{
	typedef std::vector< TimeSetting > TimeSettingVector;
	typedef TimeSettingVector::iterator TimeSettingVectorIter;

	TimeSettingVector vecSignUpTimeSetting;     // 报名时间
    TimeSettingVector vecPrepareTimeSetting;    // 准备时间
    TimeSettingVector vecEnterTimeSetting;      // 进入时间
    TimeSettingVector vecFightTimeSetting;      // 战斗时间
    TimeSettingVector vecEndTimeSetting;        // 结束时间
	bool IsEmpty()
	{
		return vecSignUpTimeSetting.empty() && 
				vecPrepareTimeSetting.empty() &&
				vecEnterTimeSetting.empty() &&
				vecFightTimeSetting.empty() &&
				vecEndTimeSetting.empty();
	}
	int GetTimeStates(time_t& now,string& Str)
	{
		//判断当前战场处于哪个阶段
		Str = "";
		TimeSettingVectorIter Iter;
		if(!vecSignUpTimeSetting.empty())
		{
			Iter = vecSignUpTimeSetting.begin();
			for(;Iter != vecSignUpTimeSetting.end();++Iter)
			{
				if(IsInTime(*Iter,now))
				{
					char begin[128];
					sprintf_s( begin, 127,theXmlString.GetString(eText_CampBatrle_Info),Iter->GetDayOfWeek(),Iter->GetHour(),Iter->GetMinute(),Iter->GetKeepTime());
					Str= begin;
					return 0;
				}
			}
		}
		if(!vecPrepareTimeSetting.empty())
		{
			Iter = vecPrepareTimeSetting.begin();
			for(;Iter != vecPrepareTimeSetting.end();++Iter)
			{
				if(IsInTime(*Iter,now))
				{
					char begin[128];
					sprintf_s( begin, 127,theXmlString.GetString(eText_CampBatrle_Info),Iter->GetDayOfWeek(),Iter->GetHour(),Iter->GetMinute(),Iter->GetKeepTime());
					Str= begin;
					return 1;
				}
			}
		}
		if(!vecEnterTimeSetting.empty())
		{
			Iter = vecEnterTimeSetting.begin();
			for(;Iter != vecEnterTimeSetting.end();++Iter)
			{
				if(IsInTime(*Iter,now))
				{
					char begin[128];
					sprintf_s( begin, 127,theXmlString.GetString(eText_CampBatrle_Info),Iter->GetDayOfWeek(),Iter->GetHour(),Iter->GetMinute(),Iter->GetKeepTime());
					Str= begin;
					return 2;
				}
			}
		}
		if(!vecFightTimeSetting.empty())
		{
			Iter = vecFightTimeSetting.begin();
			for(;Iter != vecFightTimeSetting.end();++Iter)
			{
				if(IsInTime(*Iter,now))
				{
					char begin[128];
					sprintf_s( begin, 127,theXmlString.GetString(eText_CampBatrle_Info),Iter->GetDayOfWeek(),Iter->GetHour(),Iter->GetMinute(),Iter->GetKeepTime());
					Str= begin;
					return 3;
				}
			}
		}
		if(!vecEndTimeSetting.empty())
		{
			Iter = vecEndTimeSetting.begin();
			for(;Iter != vecEndTimeSetting.end();++Iter)
			{
				if(IsInTime(*Iter,now))
				{
					char begin[128];
					sprintf_s( begin, 127,theXmlString.GetString(eText_CampBatrle_Info),Iter->GetDayOfWeek(),Iter->GetHour(),Iter->GetMinute(),Iter->GetKeepTime());
					Str= begin;
					return 4;
				}
			}
		}
		return -1;
	}

	int GetTimeInfo(std::string& strBeginTime,std::string& strEndTime,time_t& now)
	{
		//获取当前时间 找到最接近的时间设定 并且返回当前状态 和 倒计时	
		TimeSetting TMin;
		int	MinStep = -1;
		int states = -1;
		TimeSettingVectorIter Iter;
		if(!vecSignUpTimeSetting.empty())
		{
			Iter = vecSignUpTimeSetting.begin();
			for(;Iter != vecSignUpTimeSetting.end();++Iter)
			{
				int Step = GetTimeStep(*Iter,now);
				if(Step == -1) continue;
				if(MinStep > Step || MinStep==-1)
				{
					MinStep = Step;
					TMin = *Iter;
					states = 0;
				}
			}
		}
		if(!vecPrepareTimeSetting.empty())
		{
			Iter = vecPrepareTimeSetting.begin();
			for(;Iter != vecPrepareTimeSetting.end();++Iter)
			{
				int Step = GetTimeStep(*Iter,now);
				if(Step == -1) continue;
				if(MinStep > Step || MinStep==-1)
				{
					MinStep = Step;
					TMin = *Iter;
					states = 1;
				}
			}
		}
		if(!vecEnterTimeSetting.empty())
		{
			Iter = vecEnterTimeSetting.begin();
			for(;Iter != vecEnterTimeSetting.end();++Iter)
			{
				int Step = GetTimeStep(*Iter,now);
				if(Step == -1) continue;
				if(MinStep > Step || MinStep==-1)
				{
					MinStep = Step;
					TMin = *Iter;
					states = 2;
				}
			}
		}
		if(!vecFightTimeSetting.empty())
		{
			Iter = vecFightTimeSetting.begin();
			for(;Iter != vecFightTimeSetting.end();++Iter)
			{
				int Step = GetTimeStep(*Iter,now);
				if(Step == -1) continue;
				if(MinStep > Step || MinStep==-1)
				{
					MinStep = Step;
					TMin = *Iter;
					states = 3;
				}
			}
		}
		if(!vecEndTimeSetting.empty())
		{
			Iter = vecEndTimeSetting.begin();
			for(;Iter != vecEndTimeSetting.end();++Iter)
			{
				int Step = GetTimeStep(*Iter,now);
				if(Step == -1) continue;
				if(MinStep > Step || MinStep==-1)
				{
					MinStep = Step;
					TMin = *Iter;
					states = 4;
				}
			}
		}
		GetTimeSettingStrInfo(TMin,strBeginTime,strEndTime,now);
		return states;
	}
	void GetInfoByCampBattleStates(int States,std::string& str)
	{
		switch(States)
		{
		case 0:
			str = theXmlString.GetString(eText_CampBattle_SignUp);
			break;
		case 1:
			str = theXmlString.GetString(eText_CampBattle_Prepare);
			break;
		case 2:
			str = theXmlString.GetString(eText_CampBattle_Enter);
			break;
		case 3:
			str = theXmlString.GetString(eText_CampBattle_Fight);
			break;
		case 4:
			str = theXmlString.GetString(eText_CampBattle_End);
			break;
		}
	}
private:
	time_t GetTimeSecBegin(TimeSetting& setting)
	{
		//将配置项文件的值 开始的时间 当前星期 当前这个星期的指定星期几的日期
		time_t nowtime;
		time(&nowtime);//当前时间
		struct tm *sysNowTime;
		sysNowTime = localtime(&nowtime);
		//判断当前的时间差
		int diffDay = (setting.GetDayOfWeek() - (sysNowTime->tm_wday==0?7:sysNowTime->tm_wday)) * 24 * 60 * 60;//差距的秒数
		int diffHour = (setting.GetHour() - sysNowTime->tm_hour) * 60 * 60;
		int diffMin = (setting.GetMinute() - sysNowTime->tm_min) * 60;
		int diffSec = (0 - sysNowTime->tm_sec);
		int diffStep = diffDay + diffHour + diffMin + diffSec;//和当前时间差距的秒数
		time_t logTime;
		logTime = nowtime + diffStep;
		return logTime;
	}
	time_t GetTimeSecEnd(TimeSetting& setting)
	{
		time_t BeninTime = GetTimeSecBegin(setting);
		time_t EndTime = BeninTime + setting.GetKeepTime()*60;
		return EndTime;//结束的时间
	}
	time_t GetNextTimeSecBegin(TimeSetting& setting)
	{
		time_t nowtime;
		time(&nowtime);//当前时间
		nowtime = nowtime + 7*24*60*60;
		struct tm *sysNowTime;
		sysNowTime = localtime(&nowtime);
		//判断当前的时间差
		int diffDay = (setting.GetDayOfWeek() - (sysNowTime->tm_wday==0?7:sysNowTime->tm_wday)) * 24 * 60 * 60;//差距的秒数
		int diffHour = (setting.GetHour() - sysNowTime->tm_hour) * 60 * 60;
		int diffMin = (setting.GetMinute() - sysNowTime->tm_min) * 60;
		int diffSec = (0 - sysNowTime->tm_sec);
		int diffStep = diffDay + diffHour + diffMin + diffSec;//和当前时间差距的秒数
		time_t logTime;
		logTime = nowtime + diffStep;
		return logTime;
	}
	time_t GetNextTimeSecEnd(TimeSetting& setting)
	{
		time_t BeninTime = GetNextTimeSecBegin(setting);
		time_t EndTime = BeninTime + setting.GetKeepTime()*60;
		return EndTime;//结束的时间
	}
	bool IsInTime(TimeSetting& setting,time_t& now)
	{
		//判断当前时间是否在时间段内
		//判断时间范围 自动时间是否在时间范围内  星期几 几时几分几秒 持续多长时间
		time_t BeginTime= GetTimeSecBegin(setting);
		time_t EndTime= GetTimeSecEnd(setting);
		if(BeginTime<= now && now<=EndTime)
			return true;
		else
			return false;
	}
	int GetTimeStep(TimeSetting& setting,time_t& now)
	{
		//获取当前时间到这个时间段开始时间的差距 并且返回绝对值
		if(IsInTime(setting,now)) return 0;
		//可能涉及到下个星期
		time_t beginTime = GetTimeSecBegin(setting);
		if(beginTime >= now)
			return beginTime - now;
		else
		{
			//判断下星期的差距
			time_t nextBeginTime = GetNextTimeSecBegin(setting);
			return nextBeginTime - now;
		}
	}
	void GetTimeSettingStrInfo(TimeSetting& setting,std::string& strBeginTime,std::string& strEndTime,time_t& now)
	{
		//获取当前时间的字符串表示方法 将时间显示出来
		time_t beginTime = GetTimeSecBegin(setting);
		if(beginTime >= now || IsInTime(setting,now))
		{
			//执行当前星期的
			time_t endTime = GetTimeSecEnd(setting);
			//结束时间和开始时间获取到后 处理和当前的时间差
			int diffBegin =beginTime - now;
			int deffEnd = endTime - now;
			//将时间转为字符串 多少天多少小时多少分钟 
			char begin[128];
			if(diffBegin <=0)
			{
				sprintf_s( begin, 127,theXmlString.GetString(eText_CampBattle_TimeShow),0,0,0,0);
				strBeginTime = begin;
			}
			else
			{
				sprintf_s( begin, 127,theXmlString.GetString(eText_CampBattle_TimeShow),diffBegin/(24*60*60),(diffBegin%(24*60*60))/3600,((diffBegin%(24*60*60))%3600)/60,
					(((diffBegin%(24*60*60))%3600)%60));
				strBeginTime= begin;
			}

			char end[128];
			sprintf_s( end, 127,theXmlString.GetString(eText_CampBattle_TimeShow),deffEnd/(24*60*60),(deffEnd%(24*60*60))/3600,((deffEnd%(24*60*60))%3600)/60,
				(((deffEnd%(24*60*60))%3600)%60));
			strEndTime = end;
		}
		else
		{
			//下个星期的
			beginTime = GetNextTimeSecBegin(setting);
			time_t endTime=GetNextTimeSecEnd(setting);
			
			int diffBegin =beginTime - now;
			int deffEnd = endTime - now;
			//将时间转为字符串 多少天多少小时多少分钟 
			char begin[128];
			if(diffBegin <=0)
			{
				sprintf_s( begin, 127,theXmlString.GetString(eText_CampBattle_TimeShow),0,0,0,0);
				strBeginTime = begin;
			}
			else
			{
				sprintf_s( begin, 127,theXmlString.GetString(eText_CampBattle_TimeShow),diffBegin/(24*60*60),(diffBegin%(24*60*60))/3600,((diffBegin%(24*60*60))%3600)/60,
					(((diffBegin%(24*60*60))%3600)%60));
				strBeginTime= begin;
			}

			char end[128];
			sprintf_s( end, 127,theXmlString.GetString(eText_CampBattle_TimeShow),deffEnd/(24*60*60),(deffEnd%(24*60*60))/3600,((deffEnd%(24*60*60))%3600)/60,
				(((deffEnd%(24*60*60))%3600)%60));
			strEndTime = end;
		}
	}
};

struct CampBattleInfo
{
	int		States;//0-4 但是有些战场不一起有5个阶段
	int		StrID;//提示的信息
	int		Sec;//间隔的秒数
};//战场客户端的屏幕中间的提示信息

struct CampBattleInfoManger
{
	//一个战场的提示信息
	std::map<int,CampBattleInfo>	BattleInfo;//从配置文件读取的战场信息
	CampBattleTimeInfo*			m_Setting;
	time_t						m_LogTime;//上传发送信息的时间
	int							m_States;//上传发送信息的状态
	CampBattleInfoManger()
	{
		m_LogTime = 0;
		m_States = 0;
		BattleInfo.clear();
	}
	void HandleCampBattleInfo(time_t& now)
	{
		//根据参数时间 和 上传发送的时间 判断是否需要进行发送命令
		//1.判断当前时间是否已经改变
		if(m_Setting == NULL) return;
		string StrInfo;
		int States = m_Setting->GetTimeStates(now,StrInfo);//根据当前时间 获取战场处于哪个状态中
		if(States == -1) return;
		if(BattleInfo.find(States) ==  BattleInfo.end() || BattleInfo.find(m_States) ==  BattleInfo.end())
			return;
		if(States != m_States)
		{
			//马上发送消息 并且记录提示
			//1.发送提示信息
			//指定字符串必须与开始和结束时间对应起来
			//StrInfo
			if(BattleInfo.find(States)->second.StrID != 0)
			{
				char begin[256];
				sprintf_s(begin,255,theXmlString.GetString(BattleInfo.find(States)->second.StrID),StrInfo.c_str());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,begin);
			}
			//2.记录
			m_LogTime = now;
			m_States = States;
		}
		else
		{
			if(now - m_LogTime >= BattleInfo.find(States)->second.Sec && BattleInfo.find(States)->second.Sec != 0 )
			{
				//超过秒数  我们发送命令
				//1.发送提示信息
				if(BattleInfo.find(States)->second.StrID != 0)
				{
					char begin[256];
					sprintf_s(begin,255,theXmlString.GetString(BattleInfo.find(States)->second.StrID),StrInfo.c_str());
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,begin);
				}
				//2.记录
				m_LogTime = now;
			}
		}
	}
};

class CUI_ID_FRAME_CampBattleBaseInfo :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_CampBattleBaseInfo();
	 ControlFrame*	m_pID_FRAME_CampBattleBaseInfo;
	 ControlCheckBox*	m_pID_CHECKBOX_GuoWang;
	 ControlCheckBox*	m_pID_CHECKBOX_Guild;
	 ControlCheckBox*	m_pID_CHECKBOX_Union;
	 ControlCheckBox*	m_pID_CHECKBOX_World;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_GuoWangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_UnionOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_WorldOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return false; }
	virtual void InitializeAtEnterWorld();

	ControlFrame *GetFrame() { return m_pID_FRAME_CampBattleBaseInfo;}
};
extern CUI_ID_FRAME_CampBattleBaseInfo s_CUI_ID_FRAME_CampBattleBaseInfo;
