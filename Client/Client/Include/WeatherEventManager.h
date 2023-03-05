#pragma once
#include <MeFoundation/MeCycleTimer.h>
#include <MeFoundation/MeTimeLine.h>

/**
* @desc ��������ϵͳ�¼���
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
	/// ���١�
	void DestoryWeather();

	/// ��ʼ������ϵͳ��
	void InitializeWeather( const std::string& strFilename);

	/// ����������
	void UpdateWeather();

	/// ��Ⱦ������
	void RenderWeather();

	/// ֹͣ����������
	void StopWeather();

	/// ���µ�ͼ���ݣ���ÿ�ε�ͼ���ؽ�����Ҫ���и��¡�
	/// ������ƹ�����ͼ�ı����Ϣ��
	/// �������Ҫ��֤��LoadLand֮����á�
	void UpdateWorldData( int nMapId );

	/// ��ʼ��ʱ��
	void StartWeatherTime( int nMapId, const MeTimeValue& kStartTime );

	/// �豸��ʧ
	void OnDeviceLost();

	/// �豸�ָ�
	void OnDeviceReset();

// Static Methods.
public:
	static void ResetEventWithWorldData( MeTimelineEventBase* pEvent );

	/// ����λ����Ϣ��
	static void SendCurrentRolePositionInfo( MeTimelineEventBase* pEvent );

// Methods.
protected:
	/// CloudySky Read.
	void LoadCloudySkyConfig();

// Members.
protected:
	WeatherEventTimelines m_mapTimelines;

	/// ��ǰmapid
	int m_nMapId;
};
//////////////////////////////////////////////////////////////////////////
// �����ļ�ʾ����
/*/========================================================================================================================================================\*\
<WeatherTimeline>
	<!--����-->
	<Event Type = "0" Mapid = "2" TimeRatio = "5" StartTime = "0" EndTime = "7000" ToFull = "2000" ToEnd = "5000" DestAmbient = "255,55,55,55" DestDiffuse = "255,55,55,55" />
</WeatherTimeline>
\*\========================================================================================================================================================/*/