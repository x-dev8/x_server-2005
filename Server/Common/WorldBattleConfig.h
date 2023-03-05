#pragma once
#include <vector>
#include "AiDefine.h"
class WorldBattleConfig
{
public:
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

	WorldBattleConfig(){}
	~WorldBattleConfig(){}
	bool LoadFilePath(const char* szFile);//加载配置文件

	unsigned int GetMapID(){return MapID;}

	bool CheckPrepareTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );
	bool CheckFightTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );
	bool CheckEndTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

	std::vector<MonsterCreateData>& GetMonstData(unsigned int CountryID);
private:
	typedef std::vector< TimeSetting > TimeSettingVector;
    typedef TimeSettingVector::const_iterator TimeSettingVectorIter;

    TimeSettingVector vecPrepareTimeSetting;    // 准备时间
    TimeSettingVector vecFightTimeSetting;      // 战斗时间
    TimeSettingVector vecEndTimeSetting;        // 结束时间

	std::vector<MonsterCreateData>	m_NonCountry;
	std::vector<MonsterCreateData>	m_WeiCountry;
	std::vector<MonsterCreateData>	m_ShuCountry;
	std::vector<MonsterCreateData>	m_WuCountry;

	unsigned int			MapID;//战斗地图ID
};