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
    int nKeepTime;      // ���ʱ��( ��λ: ���� )
};
struct CampBattleTimeInfo
{
	typedef std::vector< TimeSetting > TimeSettingVector;
	typedef TimeSettingVector::iterator TimeSettingVectorIter;

	TimeSettingVector vecSignUpTimeSetting;     // ����ʱ��
    TimeSettingVector vecPrepareTimeSetting;    // ׼��ʱ��
    TimeSettingVector vecEnterTimeSetting;      // ����ʱ��
    TimeSettingVector vecFightTimeSetting;      // ս��ʱ��
    TimeSettingVector vecEndTimeSetting;        // ����ʱ��
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
		//�жϵ�ǰս�������ĸ��׶�
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
		//��ȡ��ǰʱ�� �ҵ���ӽ���ʱ���趨 ���ҷ��ص�ǰ״̬ �� ����ʱ	
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
		//���������ļ���ֵ ��ʼ��ʱ�� ��ǰ���� ��ǰ������ڵ�ָ�����ڼ�������
		time_t nowtime;
		time(&nowtime);//��ǰʱ��
		struct tm *sysNowTime;
		sysNowTime = localtime(&nowtime);
		//�жϵ�ǰ��ʱ���
		int diffDay = (setting.GetDayOfWeek() - (sysNowTime->tm_wday==0?7:sysNowTime->tm_wday)) * 24 * 60 * 60;//��������
		int diffHour = (setting.GetHour() - sysNowTime->tm_hour) * 60 * 60;
		int diffMin = (setting.GetMinute() - sysNowTime->tm_min) * 60;
		int diffSec = (0 - sysNowTime->tm_sec);
		int diffStep = diffDay + diffHour + diffMin + diffSec;//�͵�ǰʱ���������
		time_t logTime;
		logTime = nowtime + diffStep;
		return logTime;
	}
	time_t GetTimeSecEnd(TimeSetting& setting)
	{
		time_t BeninTime = GetTimeSecBegin(setting);
		time_t EndTime = BeninTime + setting.GetKeepTime()*60;
		return EndTime;//������ʱ��
	}
	time_t GetNextTimeSecBegin(TimeSetting& setting)
	{
		time_t nowtime;
		time(&nowtime);//��ǰʱ��
		nowtime = nowtime + 7*24*60*60;
		struct tm *sysNowTime;
		sysNowTime = localtime(&nowtime);
		//�жϵ�ǰ��ʱ���
		int diffDay = (setting.GetDayOfWeek() - (sysNowTime->tm_wday==0?7:sysNowTime->tm_wday)) * 24 * 60 * 60;//��������
		int diffHour = (setting.GetHour() - sysNowTime->tm_hour) * 60 * 60;
		int diffMin = (setting.GetMinute() - sysNowTime->tm_min) * 60;
		int diffSec = (0 - sysNowTime->tm_sec);
		int diffStep = diffDay + diffHour + diffMin + diffSec;//�͵�ǰʱ���������
		time_t logTime;
		logTime = nowtime + diffStep;
		return logTime;
	}
	time_t GetNextTimeSecEnd(TimeSetting& setting)
	{
		time_t BeninTime = GetNextTimeSecBegin(setting);
		time_t EndTime = BeninTime + setting.GetKeepTime()*60;
		return EndTime;//������ʱ��
	}
	bool IsInTime(TimeSetting& setting,time_t& now)
	{
		//�жϵ�ǰʱ���Ƿ���ʱ�����
		//�ж�ʱ�䷶Χ �Զ�ʱ���Ƿ���ʱ�䷶Χ��  ���ڼ� ��ʱ���ּ��� �����೤ʱ��
		time_t BeginTime= GetTimeSecBegin(setting);
		time_t EndTime= GetTimeSecEnd(setting);
		if(BeginTime<= now && now<=EndTime)
			return true;
		else
			return false;
	}
	int GetTimeStep(TimeSetting& setting,time_t& now)
	{
		//��ȡ��ǰʱ�䵽���ʱ��ο�ʼʱ��Ĳ�� ���ҷ��ؾ���ֵ
		if(IsInTime(setting,now)) return 0;
		//�����漰���¸�����
		time_t beginTime = GetTimeSecBegin(setting);
		if(beginTime >= now)
			return beginTime - now;
		else
		{
			//�ж������ڵĲ��
			time_t nextBeginTime = GetNextTimeSecBegin(setting);
			return nextBeginTime - now;
		}
	}
	void GetTimeSettingStrInfo(TimeSetting& setting,std::string& strBeginTime,std::string& strEndTime,time_t& now)
	{
		//��ȡ��ǰʱ����ַ�����ʾ���� ��ʱ����ʾ����
		time_t beginTime = GetTimeSecBegin(setting);
		if(beginTime >= now || IsInTime(setting,now))
		{
			//ִ�е�ǰ���ڵ�
			time_t endTime = GetTimeSecEnd(setting);
			//����ʱ��Ϳ�ʼʱ���ȡ���� ����͵�ǰ��ʱ���
			int diffBegin =beginTime - now;
			int deffEnd = endTime - now;
			//��ʱ��תΪ�ַ��� ���������Сʱ���ٷ��� 
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
			//�¸����ڵ�
			beginTime = GetNextTimeSecBegin(setting);
			time_t endTime=GetNextTimeSecEnd(setting);
			
			int diffBegin =beginTime - now;
			int deffEnd = endTime - now;
			//��ʱ��תΪ�ַ��� ���������Сʱ���ٷ��� 
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
	int		States;//0-4 ������Щս����һ����5���׶�
	int		StrID;//��ʾ����Ϣ
	int		Sec;//���������
};//ս���ͻ��˵���Ļ�м����ʾ��Ϣ

struct CampBattleInfoManger
{
	//һ��ս������ʾ��Ϣ
	std::map<int,CampBattleInfo>	BattleInfo;//�������ļ���ȡ��ս����Ϣ
	CampBattleTimeInfo*			m_Setting;
	time_t						m_LogTime;//�ϴ�������Ϣ��ʱ��
	int							m_States;//�ϴ�������Ϣ��״̬
	CampBattleInfoManger()
	{
		m_LogTime = 0;
		m_States = 0;
		BattleInfo.clear();
	}
	void HandleCampBattleInfo(time_t& now)
	{
		//���ݲ���ʱ�� �� �ϴ����͵�ʱ�� �ж��Ƿ���Ҫ���з�������
		//1.�жϵ�ǰʱ���Ƿ��Ѿ��ı�
		if(m_Setting == NULL) return;
		string StrInfo;
		int States = m_Setting->GetTimeStates(now,StrInfo);//���ݵ�ǰʱ�� ��ȡս�������ĸ�״̬��
		if(States == -1) return;
		if(BattleInfo.find(States) ==  BattleInfo.end() || BattleInfo.find(m_States) ==  BattleInfo.end())
			return;
		if(States != m_States)
		{
			//���Ϸ�����Ϣ ���Ҽ�¼��ʾ
			//1.������ʾ��Ϣ
			//ָ���ַ��������뿪ʼ�ͽ���ʱ���Ӧ����
			//StrInfo
			if(BattleInfo.find(States)->second.StrID != 0)
			{
				char begin[256];
				sprintf_s(begin,255,theXmlString.GetString(BattleInfo.find(States)->second.StrID),StrInfo.c_str());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,begin);
			}
			//2.��¼
			m_LogTime = now;
			m_States = States;
		}
		else
		{
			if(now - m_LogTime >= BattleInfo.find(States)->second.Sec && BattleInfo.find(States)->second.Sec != 0 )
			{
				//��������  ���Ƿ�������
				//1.������ʾ��Ϣ
				if(BattleInfo.find(States)->second.StrID != 0)
				{
					char begin[256];
					sprintf_s(begin,255,theXmlString.GetString(BattleInfo.find(States)->second.StrID),StrInfo.c_str());
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,begin);
				}
				//2.��¼
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

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
	virtual bool IsHoldInMemory() const { return false; }
	virtual void InitializeAtEnterWorld();

	ControlFrame *GetFrame() { return m_pID_FRAME_CampBattleBaseInfo;}
};
extern CUI_ID_FRAME_CampBattleBaseInfo s_CUI_ID_FRAME_CampBattleBaseInfo;
