#pragma once
#include <MeFoundation/MeCycleTimer.h>
#include <MeFoundation/MeTimeLine.h>

/**
* @desc 管理天气系统事件。
*/
class WeatherEventManager : public Singleton< WeatherEventManager >
{
// Defines.
public:
	typedef MeTimeline< MeHourTimer/*MeCycleTimer< 100000, MeClockTimer >*/ > WeatherEventTimeline;
	typedef std::map< int , WeatherEventTimeline* > WeatherEventTimelines;
	typedef WeatherEventTimelines::iterator WeatherEventTimelinesIterator;
	typedef WeatherEventTimelines::const_iterator WeatherEventTimelinesConstIterator;

// Construction.
public:
	~WeatherEventManager(){}

// Construction.
private:
	friend class Singleton< WeatherEventManager >;
	WeatherEventManager(){
		m_nMapId = -1;
	}

// Methods.
public:
	/// 销毁。
	void DestoryWeather();

	/// 初始化天气系统。
	void InitializeWeather( const std::string& strFilename);

	/// 更新天气。
	void UpdateWeather();

	/// 渲染天气。
	void RenderWeather();

	/// 停止更新天气。
	void StopWeather();

	/// 更新地图数据，在每次地图加载结束后都要进行更新。
	/// 这包括灯光等随地图改变的信息。
	/// 这个函数要保证在LoadLand之后调用。
	void UpdateWorldData( int nMapId );

	/// 开始计时。
	void StartWeatherTime( int nMapId, const MeTimeValue& kStartTime );

	/// 设备丢失
	void OnDeviceLost();

	/// 设备恢复
	void OnDeviceReset();

// Static Methods.
public:
	static void ResetEventWithWorldData( MeTimelineEventBase* pEvent );

	/// 更新位置信息。
	static void SendCurrentRolePositionInfo( MeTimelineEventBase* pEvent );

// Methods.
protected:
	/// CloudySky Read.
	void LoadCloudySkyConfig();

// Members.
protected:
	WeatherEventTimelines m_mapTimelines;

	/// 当前mapid
	int m_nMapId;
};
//////////////////////////////////////////////////////////////////////////
// 配置文件示例。
/*/========================================================================================================================================================\*\
<WeatherTimeline>
	<!--阴天-->
	<Event Type = "0" Mapid = "2" TimeRatio = "5" StartTime = "0" EndTime = "7000" ToFull = "2000" ToEnd = "5000" DestAmbient = "255,55,55,55" DestDiffuse = "255,55,55,55" />
</WeatherTimeline>
\*\========================================================================================================================================================/*/