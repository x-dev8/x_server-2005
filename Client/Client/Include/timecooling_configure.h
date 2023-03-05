
#ifndef AN_TIMECOOLING_CONFIGURE_H_
#define AN_TIMECOOLING_CONFIGURE_H_

#include <Windows.h>
#include <map>

enum TimeCoolingConfigure
{
	TCC_MINIMAP_EVENTBTN_RAY = 0,	//���µ�ʱ�� ��˸btn�ļ��ʱ��
	TCC_MINIMAP_SHOW_EVENT_TIP,		//С��ͼ��ʾ�¼���ʾ��ʱ����

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