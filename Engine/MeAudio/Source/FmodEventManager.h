/******************************************************
*add by:zxy 2012/5/2
*Fmod event system
*******************************************************/
#pragma once
#include "fmod/fmod_event.hpp"
#include "fmod/fmod_errors.h"
#include "Dxsdk/d3dx9math.h"
#include <vector>
#include <map>
#include <string>

template< class T > inline T CLAMP( const T X, const T Min, const T Max )
{
	return X<Min ? Min : X<Max ? X : Max;
}
//#define CLAMP(var, min, max)   (((var) < (min)) ? (var) = (min) : ((var) > (max)) ? (var) = (max) : (var))
enum 
{
	eMEAUDIO_SOUND = 0x00000001,
	eMEAUDIO_MUSIC = 0x00000002,
	eMEAUDIO_ALL = eMEAUDIO_MUSIC | eMEAUDIO_SOUND
};

class FmodEventManager
{
public:
	FmodEventManager(void);
	~FmodEventManager(void);
public:
	bool Initilize();
	void Destory();
	void Update( DWORD dwTime );
public:
	FMOD_RESULT GetFmodSystem(FMOD::System **Fmodsystem);
public:
	void SetMediaPath(const char* path);
	void Load(const char* fevfile, char* pEncrytKey = NULL);
public:
	//播放event音效
	void CallSound(
		const char* pEvent,												//Event 名称(Group\EventName)
		D3DXVECTOR3* vPos,												//音效世界坐标
		const char* pParam = NULL,										//参数名称 先只用一个参数名
		FLOAT Param_value = 0,											//参数值
		FLOAT Volume = 0.125f,											//音量
		FMOD_EVENT_CALLBACK callback = &FmodEventManager::eventCallBack,//回调函数
		FMOD_EVENT_MODE mode = FMOD_EVENT_NONBLOCKING					//读取模式 NONBLOCKING是线程加载
		);
	
	//为了背景音乐专门写出的接口，因为背景音乐用这种方式播放，要与Sound做出区别
	void CallSound2Music(
		const char* pEvent,
		const char* pParam = NULL,
		FLOAT Param_value = 0,
		FLOAT Volume = 0.125f
		);

	//队列播放event音效 INFOONLY模式
	void CallSoundInQueue(
		const char* pEvent, 
		D3DXVECTOR3* vPos
		);

	//播放音乐
	void CallMusic( 
		int musicId, 
		bool bprompt = true 
		);
public:
	void Paused	  ( bool bPaused, int type = eMEAUDIO_ALL );//1.for Sound 2.for music 3.for all
	void SetVolume( FLOAT fVal, int type = eMEAUDIO_ALL );
	void SetMute  ( bool bmute, int type = eMEAUDIO_ALL );
	void Stop     ( int type = eMEAUDIO_ALL );

	bool IsSoundInPlay(const char* pEvent);
	bool HasMusic(){return m_EventMusic!=NULL;};
	unsigned int GetCurrMusicLength();
	bool IsCurrMusicOver(DWORD offset);

	void ReleaseSound(const char* pEvent);
	void ReleaseAllSound();
public://3D Sound
	void UpdateEarPos( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir, int updatetime = 50 );
	D3DXVECTOR3		m_vEarPos;
	D3DXVECTOR3		m_vEarDir;

public://Reverb : use intance0
	void SetGlobalReverb( const char* pReverbName );//全局环境音效 如在大厅或者水中的效果。pReverbName填入designer中的命名
	void CloseGlobalReverb();//关闭环境音效

	void Create3DReverb( const char* pReverbName, D3DXVECTOR3 pos, float minDistance, float maxDistance );
	void CloseAll3DReverb();

	void SetReverbState( bool bClose, int type = eMEAUDIO_ALL );//打开/关闭 music/sound环境音效
public://tool
	void GetEventNameVector( std::vector<std::string> *vEventName );
	void GetEventWaveBankName( const char* pEvent, std::vector<std::string>& wavebank );
private:
	void PushEventNameVector( FMOD::EventGroup *group, std::string path, std::vector<std::string> *vEventName );
public://for debug
	const char* GetLastErrorString();

protected:
	static FMOD_RESULT F_CALLBACK eventCallBack(FMOD_EVENT *event, FMOD_EVENT_CALLBACKTYPE type, void *param1, void *param2, void *userdata);
	static FMOD_RESULT F_CALLBACK musicCallBack(FMOD_MUSIC_CALLBACKTYPE  type, void *  param1, void *  param2, void *  userdata);
	static FMOD_RESULT F_CALLBACK eventqueueCallBack(FMOD_EVENTQUEUE_CALLBACKTYPE  type, FMOD_EVENTQUEUE *  queue, FMOD_EVENTQUEUEENTRY *  entry, void *  callbackuserdata);

	FMOD_RESULT CheckResult(FMOD_RESULT result);
	void RemoveInvalidEventHandle();
	void freeStopEvent();
	void StopMusic();
	void StopSound();

	bool				 m_bInitilize;
	bool				 m_bFreeWhenStop;

	FMOD::EventSystem    *m_eventsystem;
	FMOD::MusicSystem    *m_musicsystem;
	FMOD::EventProject	 *m_EventProject;
	FMOD::EventQueue	 *m_EventQueue;

	FMOD_RESULT m_lasterrorresult;

	typedef std::multimap<std::string, FMOD::Event*>		EventRegistry;
	typedef std::map<int, FMOD::MusicPrompt*>				MusicRegistry;
	typedef std::vector< FMOD::EventReverb* >				ReverbRegistry;

	EventRegistry		m_vEvent;
	MusicRegistry		m_vMusicPrompt;
	ReverbRegistry		m_v3DReverb;

	//背景音乐占用
	FMOD::Event*		m_EventMusic;
};

extern FmodEventManager			GEventManager;