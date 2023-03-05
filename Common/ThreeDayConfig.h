#pragma once
#include <time.h>
#include <vector>
struct ThreeDayOnce
{
	unsigned short nYear;
	unsigned short nMonth;
	unsigned short nDay;
	unsigned int nItemID;
	unsigned int nItemSum;
	unsigned int nValue;
	bool IsOnceDay(tm* fmt) const
	{
		if(fmt->tm_year + 1900 == nYear && fmt->tm_mon +1 == nMonth && fmt->tm_mday == nDay)
			return true;
		else
			return false;
	}
};
class ThreeDayConfig
{
public:
	ThreeDayConfig();
	~ThreeDayConfig();
	static ThreeDayConfig& Instance()
    {
        static ThreeDayConfig s_xConfig;
        return s_xConfig;
    }
	bool LoadThreeDayConfig(const char* FilePath);
	const ThreeDayOnce* GetNowDayThreeDayOnceInfo();//获取今天的数据
	int	GetVision(){return m_Vision;}
	int GetWriteTime(){return m_WriteTime;}
private:
	std::vector<ThreeDayOnce*>	m_ThreeOnceVec;
	int							m_Vision;
	int							m_WriteTime;//在线多长时间后才可以领取奖励
};