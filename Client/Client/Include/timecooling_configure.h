
#ifndef AN_TIMECOOLING_CONFIGURE_H_
#define AN_TIMECOOLING_CONFIGURE_H_

#include <Windows.h>
#include <map>

enum TimeCoolingConfigure
{
	TCC_MINIMAP_EVENTBTN_RAY = 0,	//有新的时间 闪烁btn的间隔时间
	TCC_MINIMAP_SHOW_EVENT_TIP,		//小地图显示事件提示的时间间隔

	TCC_MAX
};

class CTimeCooling_Configure
{
public:
	CTimeCooling_Configure();
	virtual ~CTimeCooling_Configure();

public:
	void	load();

	int	getTimeCooling(TimeCoolingConfigure type);

private:
	std::map<int, int>	time_cooling_configure;
};

extern CTimeCooling_Configure g_TimeCooling_Config;

#endif