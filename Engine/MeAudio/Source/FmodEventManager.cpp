#include "FmodEventManager.h"

FmodEventManager			GEventManager;

FMOD_RESULT F_CALLBACK FmodEventManager::eventCallBack(FMOD_EVENT *event, FMOD_EVENT_CALLBACKTYPE type, void *param1, void *param2, void *userdata)
{
	switch (type)
	{
	case FMOD_EVENT_CALLBACKTYPE_SYNCPOINT:
		//param1 = (char *) name of sync point
		//param2 = (unsigned int) PCM offset of sync point.
		break;
	case FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_START:
		//param1 = (char *) name of sound definition being started
		//param2 = (int) index of wave being started inside sound definition (ie for multi wave sound definitions)
		break;
	case FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_END:
		//param1 = (char *) name of sound definition being stopped
		//param2 = (int) index of wave being stopped inside sound definition (ie for multi wave sound definitions)
		break;
	case FMOD_EVENT_CALLBACKTYPE_STOLEN:
		//param1 = 0
		//param2 = 0
		break;
	case FMOD_EVENT_CALLBACKTYPE_EVENTFINISHED:
		//param1 = 0
		//param2 = 0
		break;
	case FMOD_EVENT_CALLBACKTYPE_NET_MODIFIED:
		//param1 = (FMOD_EVENT_PROPERTY) which property was modified
		//param2 = (float) the new property value
		break;
	case FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_CREATE:
		//param1 = (char *) name of sound definition
		//param2 [in] = (int *) pointer to index of sound definition entry
		//param2 [out] = (FMOD::Sound **) pointer to a valid lower level API FMOD Sound handle
		break;
	case FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_RELEASE:
		//param1 = (char *) name of sound definition
		//param2 = (FMOD::Sound *) the FMOD sound handle that was previously created in FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_CREATE
		break;
	case FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_INFO:
		//param1 = (char *) name of sound definition
		//param2 = (FMOD::Sound *) the FMOD sound handle that FMOD will use for this sound definition
		break;
	case FMOD_EVENT_CALLBACKTYPE_EVENTSTARTED:
		//param1 = 0
		//param2 = 0
		break;;
	case FMOD_EVENT_CALLBACKTYPE_SOUNDDEF_SELECTINDEX:
		//param1 = (char *) name of sound definition if FMOD_EVENT_INIT_DETAILED_SOUNDDEF_INFO was not specified
		//param1 = (FMOD_EVENT_SOUNDDEFINFO *) sound definition info struct if FMOD_EVENT_INIT_DETAILED_SOUNDDEF_INFO was specified
		//param2 [in] = (int *) pointer to number of entries in this sound definition
		//*param2 [out] = (int) index of sound definition entry to select
		break;
	case FMOD_EVENT_CALLBACKTYPE_OCCLUSION:
		//param1 = (float *) pointer to a floating point direct value that can be read and modified after the geometry engine has calculated it for this event's channel.
		//param2 = (float *) pointer to a floating point reverb value that can be read and modified after the geometry engine has calculated it for this event's channel.
		break;
	}
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK FmodEventManager::musicCallBack(FMOD_MUSIC_CALLBACKTYPE  type, void *  param1, void *  param2, void *  userdata)
{
	switch(type)
	{
	case FMOD_MUSIC_CALLBACKTYPE_SEGMENT_START:       /* Called when a segment is started. */
		//param1: (unsigned int) ID of segment being started.
		//param2: Unused.
		break;
	case FMOD_MUSIC_CALLBACKTYPE_SEGMENT_END:         /* Called when a segment ends. */
		//param1: (unsigned int) ID of segment being stopped.
		//param2: Unused.
		break;
	case FMOD_MUSIC_CALLBACKTYPE_SAMPLE_CREATE:       /* Called when a segment needs a sound created. */
		//param1: (FMOD_MUSIC_SAMPLE_INFO*) Info about sample being created.
		//param2 [out]: (FMOD::Sound**) pointer to a valid low level FMOD Sound handle. The sound must be created with FMOD_SOFTWARE set. It is also recommended to set FMOD_2D | FMOD_NONBLOCKING | FMOD_CREATESTREAM.
		break;
	case FMOD_MUSIC_CALLBACKTYPE_SAMPLE_RELEASE:      /* Called when a segment is finished with a sound. */
		//param1: (FMOD_MUSIC_SAMPLE_INFO*) Info about sample being released.
		//param2: (FMOD::Sound*) the low level FMOD Sound handle that was previously returned by FMOD_MUSIC_CALLBACKTYPE_SAMPLE_CREATE.
		break;
	case FMOD_MUSIC_CALLBACKTYPE_CHANNEL_CREATED:     /* Called when a channel is created to play a segment. */
		//param1: (FMOD_MUSIC_SEGMENT_INFO*) info about the segment that is being played.
		//param2: (FMOD::Channel*) the channel that was created.
		break;
	case FMOD_MUSIC_CALLBACKTYPE_CHANNEL_DESTROYED:   /* Called when a segment channel is destroyed. */
		//param1: (FMOD_MUSIC_SEGMENT_INFO*) info about the segment that was being played.
		//param2: (FMOD::Channel*) the channel that was destroyed.
		break;
	case FMOD_MUSIC_CALLBACKTYPE_RESET:               /* Called when the system is reset */
		//param1: Unused.
		//param2: Unused.
		break;
	case FMOD_MUSIC_CALLBACKTYPE_BEAT:                 /* Called each time a beat is passed (based on segment tempo and time signature) */
		//param1: (int) bar number (starting at 1).
		//param2: (int) beat number (starting at 1).
		break;
	}
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK FmodEventManager::eventqueueCallBack(FMOD_EVENTQUEUE_CALLBACKTYPE  type, FMOD_EVENTQUEUE *  queue, FMOD_EVENTQUEUEENTRY *  entry, void *  callbackuserdata)
{
	switch(type)
	{
	case FMOD_EVENTQUEUE_CALLBACKTYPE_PREPARE:       /* Called when an entry is being prepared for playback */
	case FMOD_EVENTQUEUE_CALLBACKTYPE_ABOUTTOPLAY:   /* Called when an entry is about to play */
	case FMOD_EVENTQUEUE_CALLBACKTYPE_FINISHED:      /* Called when an entry has finished playing */
	case FMOD_EVENTQUEUE_CALLBACKTYPE_EXPIRED:        /* Called when an entry has expired before being played. See EventQueueEntry::setExpiryTime */
		break;
	}
	return FMOD_OK;
}

void SpiltEvent(const char* pEvent, char* eventName)
{
	std::string str = pEvent;
	std::size_t pos = str.find_last_of('/', str.length());
	if (pos != -1)
		strcpy(eventName, str.substr(pos+1, str.length()).c_str());
	else
		strcpy(eventName, pEvent);
}

FmodEventManager::FmodEventManager(void)
{
	m_bInitilize = false;
	m_eventsystem = NULL;
	m_musicsystem = NULL;
	m_EventProject = NULL;
	m_lasterrorresult = FMOD_OK;
	m_EventQueue = NULL;
	m_bFreeWhenStop = false;
	m_EventMusic = NULL;
}

FmodEventManager::~FmodEventManager(void)
{
	m_bInitilize = false;
	m_eventsystem = NULL;
	m_musicsystem = NULL;
	m_EventProject = NULL;
	m_lasterrorresult = FMOD_OK;
	m_EventQueue = NULL;
	m_bFreeWhenStop = false;
	m_EventMusic = NULL;
}

bool FmodEventManager::Initilize()
{
	unsigned int version;
	m_bInitilize = true;

	if (CheckResult(FMOD::EventSystem_Create(&m_eventsystem)) == FMOD_OK)
	{
		CheckResult(m_eventsystem->getVersion(&version));
		if (version < FMOD_VERSION)
		{
			//printf("Error! You are using an old version of FMOD %08x. This program requires %08x\n", version, FMOD_VERSION);
			return false;
		}

#ifdef MEDEBUG
		if ( CheckResult(m_eventsystem->init(1024, FMOD_INIT_3D_RIGHTHANDED | FMOD_INIT_ENABLE_PROFILE, 0, FMOD_EVENT_INIT_NORMAL)) != FMOD_OK )
			return false;
#else
		if ( CheckResult(m_eventsystem->init(1024, FMOD_INIT_3D_RIGHTHANDED, 0, FMOD_EVENT_INIT_NORMAL)) != FMOD_OK )
			return false;
#endif

		if ( CheckResult(m_eventsystem->createEventQueue(&m_EventQueue)) != FMOD_OK )
			return false;

		CheckResult( m_EventQueue->setCallback(&FmodEventManager::eventqueueCallBack, NULL) );

	}else
		return false;
	return true;
}

void FmodEventManager::Destory()
{
	m_bInitilize = false;

	if (m_EventQueue)
	{
		CheckResult(m_EventQueue->release());
		m_EventQueue = NULL;
	}

	if (m_musicsystem)
	{
		CheckResult(m_musicsystem->freeSoundData(false));
		CheckResult(m_musicsystem->reset());
		m_musicsystem = NULL;
	}

	if (m_EventProject)
	{
		CheckResult(m_EventProject->release());
		m_EventProject = NULL;
	}

	if (m_eventsystem)
	{
		CheckResult(m_eventsystem->unload());
		CheckResult(m_eventsystem->release());
	}
	m_EventMusic = NULL;
	m_eventsystem = NULL;
	m_bFreeWhenStop = false;
}

void FmodEventManager::Update( DWORD dwTime )
{
	if (!m_eventsystem)
		return;

	if (CheckResult(m_eventsystem->update()) != FMOD_OK)
		return;

	RemoveInvalidEventHandle();
	if (m_bFreeWhenStop){
		freeStopEvent();
	}
}

FMOD_RESULT FmodEventManager::GetFmodSystem(FMOD::System **Fmodsystem)
{
	if (!m_eventsystem)
		return m_lasterrorresult;

	return CheckResult(m_eventsystem->getSystemObject(Fmodsystem));
}

void FmodEventManager::SetMediaPath(const char* path)
{
	if (!m_eventsystem || path == NULL)
		return;

	if (CheckResult(m_eventsystem->setMediaPath(path)) != FMOD_OK)
		return;
}

void FmodEventManager::Load(const char* fevfile, char* pEncrytKey)
{
	if (!m_eventsystem || fevfile == NULL)
		return;

	FMOD_EVENT_LOADINFO info;
	info.size = sizeof(FMOD_EVENT_LOADINFO);
	//如果我们需要一个密码
	info.encryptionkey = pEncrytKey;
	if (CheckResult(m_eventsystem->load(fevfile, &info, &m_EventProject)) == FMOD_OK)
	{
		CheckResult(m_eventsystem->getMusicSystem(&m_musicsystem));
		CheckResult(m_musicsystem->setCallback(&FmodEventManager::musicCallBack, NULL));
	}
}

void FmodEventManager::RemoveInvalidEventHandle()
{
	FMOD_EVENT_STATE state;
	EventRegistry::iterator it = m_vEvent.begin();
	while (it != m_vEvent.end())
	{
		if (it->second)
		{
			FMOD_RESULT result = it->second->getState( &state );
			if (result != FMOD_ERR_INVALID_HANDLE)
			{
				++it;
				continue;
			}
		}
		it = m_vEvent.erase(it);
	}
	if (m_EventMusic)
	{
		FMOD_RESULT result = m_EventMusic->getState( &state );
		if (result == FMOD_ERR_INVALID_HANDLE)
		{
			m_EventMusic = NULL;
		}
	}
}

void FmodEventManager::freeStopEvent()
{
	FMOD::EventGroup*		group;
	FMOD_EVENT_STATE		state;
	EventRegistry::iterator it = m_vEvent.begin();
	while (it != m_vEvent.end())
	{
		FMOD_RESULT result = it->second->getState( &state );
		if ( result == FMOD_ERR_INVALID_HANDLE )
		{
			it = m_vEvent.erase(it);
			continue;
		}else if (!(state & FMOD_EVENT_STATE_PLAYING))
		{
			if ( CheckResult(it->second->getParentGroup(&group)) == FMOD_OK )
			{
				CheckResult(group->freeEventData(it->second));
				it = m_vEvent.erase(it);
				continue;
			}
		}
		++it;
	}
}


void FmodEventManager::CallSound(
								 const char* pEvent, 
								 D3DXVECTOR3* vPos,
								 const char* pParam, 
								 FLOAT Param_value, 
								 FLOAT Volume,
								 FMOD_EVENT_CALLBACK callback, 
								 FMOD_EVENT_MODE mode
								 )
{
	if (!m_EventProject || pEvent == NULL)
		return;

	if ( pEvent[0] == 0)
		return;

	int						index;
	char*					name;
	FMOD_EVENT_INFO			info;
	FMOD::Event				*eve = NULL;

	FMOD_VECTOR				pos = {0,0,0};
	if (vPos)				
	{
		pos.x = vPos->x;
		pos.y = vPos->y;
		pos.z = vPos->z;
	}

	if(CheckResult(m_EventProject->getEvent(pEvent, mode, &eve)) == FMOD_OK)
	{
		if(CheckResult(eve->set3DAttributes(&pos, 0, 0)) == FMOD_OK)
		{
			CheckResult(eve->setCallback(&FmodEventManager::eventCallBack, NULL));
			if (pParam)
			{
				float param_min, param_max, param_cur;
				FMOD::EventParameter *param;
				CheckResult( eve->getParameter(pParam, &param) );
				if (param)
				{
					CheckResult( param->getRange(&param_min, &param_max) );
					param_cur = CLAMP<float>(Param_value, param_min, param_max);
					CheckResult( param->setValue(param_cur) );
				}
			}
			CheckResult( eve->setVolume(Volume));
			CheckResult( eve->start() );

			if (CheckResult( eve->getInfo(&index, &name, &info) ) == FMOD_OK)
			{
				m_vEvent.insert(EventRegistry::value_type(name, eve));
			}
		}
	}
}

void FmodEventManager::CallSound2Music(
					 const char* pEvent,
					 const char* pParam,
					 FLOAT Param_value,
					 FLOAT Volume
					 )
{
	if (!m_EventProject || pEvent == NULL)
	{
		StopMusic();
		return;
	}

	if ( pEvent[0] == 0 )
	{
		StopMusic();
		return;
	}

	int						index;
	char*					name;
	FMOD_EVENT_INFO			info;
	FMOD_VECTOR				pos = {0,0,0};

	if (m_EventMusic)
	{
		char _cEvent[MAX_PATH];
		SpiltEvent(pEvent, _cEvent);
		if (CheckResult( m_EventMusic->getInfo(&index, &name, &info) ) == FMOD_OK)
		{
			if ( strcmp( name, _cEvent ) == 0 )
			{
				if (pParam)
				{
					float param_min, param_max, param_cur;
					FMOD::EventParameter *param;
					CheckResult( m_EventMusic->getParameter(pParam, &param) );
					if (param)
					{
						CheckResult( param->getRange(&param_min, &param_max) );
						param_cur = CLAMP<float>(Param_value, param_min, param_max);
						CheckResult( param->setValue(param_cur) );
					}
				}
				CheckResult( m_EventMusic->setVolume(Volume));
				return;
			}
		}
	}
	StopMusic();

	if(CheckResult(m_EventProject->getEvent(pEvent, FMOD_EVENT_NONBLOCKING, &m_EventMusic)) == FMOD_OK)
	{
		if(CheckResult(m_EventMusic->set3DAttributes(&pos, 0, 0)) == FMOD_OK)
		{
			//CheckResult(eve->setCallback(&FmodEventManager::eventCallBack, NULL));
			if (pParam)
			{
				float param_min, param_max, param_cur;
				FMOD::EventParameter *param;
				CheckResult( m_EventMusic->getParameter(pParam, &param) );
				if (param)
				{
					CheckResult( param->getRange(&param_min, &param_max) );
					param_cur = CLAMP<float>(Param_value, param_min, param_max);
					CheckResult( param->setValue(param_cur) );
				}
			}
			CheckResult( m_EventMusic->setVolume(Volume));
			CheckResult( m_EventMusic->start() );
		}
	}
}


void FmodEventManager::CallSoundInQueue(
										const char* pEvent, 
										D3DXVECTOR3* vPos
										)
{
	if (!m_EventQueue || pEvent == NULL)
		return;

	if ( pEvent[0] == 0)
		return;

	FMOD::Event          *eve = NULL;
	FMOD_VECTOR				pos = {0,0,0};
	if (vPos)				
	{
		pos.x = vPos->x;
		pos.y = vPos->y;
		pos.z = vPos->z;
	}

	if( CheckResult(m_EventProject->getEvent(pEvent, FMOD_EVENT_INFOONLY, &eve)) == FMOD_OK )
	{
		if( CheckResult(eve->set3DAttributes(&pos, 0, 0)) == FMOD_OK )
		{
			CheckResult(eve->setCallback(&FmodEventManager::eventCallBack, NULL));
			FMOD::EventQueueEntry* pEntry;
			if( CheckResult(m_eventsystem->createEventQueueEntry(eve, &pEntry)) == FMOD_OK )
			{
				CheckResult(m_EventQueue->add(pEntry));
			}
		}
	}

}

void FmodEventManager::CallMusic(int musicId, bool bprompt)
{
	if (!m_musicsystem)
		return;

	if (bprompt){
		CheckResult(m_musicsystem->promptCue( musicId ));
		return;
	}

	FMOD::MusicPrompt    *musicprompt;
	MusicRegistry::iterator it = m_vMusicPrompt.find(musicId);
	if (it != m_vMusicPrompt.end()){
		musicprompt = it->second;
	}else{
		CheckResult(m_musicsystem->prepareCue(musicId, &musicprompt));
		m_vMusicPrompt[musicId] = musicprompt;
	}

	bool bactive = false;
	CheckResult(musicprompt->isActive(&bactive));
	if (!bactive){
		CheckResult(musicprompt->begin());
	}else{
		CheckResult(musicprompt->end());
	}
}

void FmodEventManager::StopMusic()
{
	if (m_EventMusic)
	{
		CheckResult(m_EventMusic->stop());
		m_EventMusic = NULL;
	}

	if (!m_musicsystem)
		return;

	CheckResult(m_musicsystem->reset());
	MusicRegistry::iterator it = m_vMusicPrompt.begin();
	while (it != m_vMusicPrompt.end())
	{
		CheckResult(it->second->release());
		++it;
	}
	CheckResult(m_musicsystem->freeSoundData());
	m_vMusicPrompt.clear();
}

void FmodEventManager::StopSound()
{
	if (!m_EventProject)
		return;

	//因为muisc现在使用Event来播放处理的 故不用这种方式停止音效
	//CheckResult(m_EventProject->stopAllEvents());

	EventRegistry::iterator it = m_vEvent.begin();
	while(it != m_vEvent.end())
	{
		FMOD_RESULT result = it->second->stop(true);//立即关闭
		++it;
	}
	m_vEvent.clear();
}


bool FmodEventManager::IsSoundInPlay(const char* pEvent)
{
	if (!m_EventProject || pEvent == NULL)
		return false;

	if ( pEvent[0] == 0)
		return false;

	char _cEvent[MAX_PATH];
	SpiltEvent(pEvent, _cEvent);

	FMOD_EVENT_STATE		state;
	EventRegistry::iterator it = m_vEvent.begin();
	while (it != m_vEvent.end())
	{
		if ( strcmp(it->first.c_str(), _cEvent) == 0 )
		{
			FMOD_RESULT result = it->second->getState(&state);
			if ( result == FMOD_ERR_INVALID_HANDLE )
			{
				it = m_vEvent.erase(it);
				continue;
			}else 
			{
				if(result == FMOD_OK)
					return (state & FMOD_EVENT_STATE_PLAYING)>0;
			}
		}
		++it;
	}
	return false;
}

unsigned int FmodEventManager::GetCurrMusicLength()
{
	int index;
	char* name;	
	FMOD_EVENT_INFO info;
	if (m_EventMusic)
	{
		FMOD_RESULT result = m_EventMusic->getInfo(&index, &name, &info);
		if ( result == FMOD_ERR_INVALID_HANDLE )
		{
			m_EventMusic = NULL;
			return 0;
		}else
		{
			return (info.lengthms);
		}
	}
	return 0;
}

bool FmodEventManager::IsCurrMusicOver(DWORD offset)
{
	int index;
	char* name;	
	FMOD_EVENT_INFO info;
	if (m_EventMusic)
	{
		FMOD_RESULT result = m_EventMusic->getInfo(&index, &name, &info);
		if ( result == FMOD_ERR_INVALID_HANDLE )
		{
			m_EventMusic = NULL;
			return false;
		}else
		{
			if (info.lengthms == -1)
			{
				return false;
			}
			return (info.positionms + offset > info.lengthms);
		}
	}
	return true;
}

void FmodEventManager::ReleaseSound(const char* pEvent)
{
	if (!m_EventProject || pEvent == NULL)
		return;

	if ( pEvent[0] == 0)
		return;

	char _cEvent[MAX_PATH];
	SpiltEvent(pEvent, _cEvent);

	FMOD::EventGroup*		group;
	EventRegistry::iterator it = m_vEvent.begin();
	while (it != m_vEvent.end())
	{
		if ( strcmp(it->first.c_str(), _cEvent) == 0 )
		{
			FMOD_RESULT result = it->second->getParentGroup(&group);
			if (result == FMOD_ERR_INVALID_HANDLE)
			{
				it = m_vEvent.erase(it);
				continue;
			}else
			{
				if ( result == FMOD_OK )
				{
					CheckResult(group->freeEventData(it->second));
					it = m_vEvent.erase(it);
					continue;
				}
			}
		}
		++it;
	}

}

void FmodEventManager::ReleaseAllSound()
{
	FMOD::EventGroup* group;
	EventRegistry::iterator it = m_vEvent.begin();
	while (it != m_vEvent.end())
	{
		FMOD_RESULT result = CheckResult(it->second->getParentGroup(&group));
		if (result == FMOD_ERR_INVALID_HANDLE)
		{
			it = m_vEvent.erase(it);
			continue;
		}else
		{
			CheckResult(group->freeEventData(it->second));
		}
		++it;
	}
	m_vEvent.clear();
}

void FmodEventManager::Paused( bool bPaused, int type )
{
	if ( type & eMEAUDIO_SOUND )
	{
		EventRegistry::iterator it = m_vEvent.begin();
		while (it != m_vEvent.end())
		{
			FMOD_RESULT result = CheckResult(it->second->setPaused(bPaused));
			if (result == FMOD_ERR_INVALID_HANDLE)
			{
				it = m_vEvent.erase(it);
				continue;
			}
			++it;
		}
	}
	if ( type & eMEAUDIO_MUSIC )
	{
		if (m_musicsystem)
			CheckResult(m_musicsystem->setPaused(bPaused));

		if (m_EventMusic)
		{
			CheckResult(m_EventMusic->setPaused(bPaused));
		}
	}
}

void FmodEventManager::SetVolume( FLOAT fVal, int type )
{
	if ( type & eMEAUDIO_SOUND )
	{
		EventRegistry::iterator it = m_vEvent.begin();
		while (it != m_vEvent.end())
		{
			FMOD_RESULT result = CheckResult(it->second->setVolume(fVal));
			if (result == FMOD_ERR_INVALID_HANDLE)
			{
				it = m_vEvent.erase(it);
				continue;
			}
			++it;
		}
	}
	if ( type & eMEAUDIO_MUSIC)
	{
		if (m_musicsystem)
			CheckResult(m_musicsystem->setVolume(fVal));
		if(m_EventMusic)
			CheckResult(m_EventMusic->setVolume(fVal));
	}
}

void FmodEventManager::SetMute( bool bmute, int type )
{
	if ( type & eMEAUDIO_SOUND )
	{
		EventRegistry::iterator it = m_vEvent.begin();
		while (it != m_vEvent.end())
		{
			FMOD_RESULT result = CheckResult(it->second->setMute(bmute));
			if (result == FMOD_ERR_INVALID_HANDLE)
			{
				it = m_vEvent.erase(it);
				continue;
			}
			++it;
		}
	}
	if ( type & eMEAUDIO_MUSIC )
	{
		if (m_musicsystem)
			CheckResult(m_musicsystem->setMute(bmute));
		if (m_EventMusic)
			CheckResult(m_EventMusic->setMute(bmute));
	}
}

void FmodEventManager::Stop( int type )
{
	if (type & eMEAUDIO_SOUND)
	{
		StopSound();
	}
	if (type & eMEAUDIO_MUSIC)
	{
		StopMusic();
	}
}

void FmodEventManager::SetGlobalReverb( const char* pReverbName )
{
	if (!m_EventProject || pReverbName == NULL)
		return;

	if ( pReverbName[0] == 0)
		return;

	int index;
	FMOD_REVERB_PROPERTIES musicreverb = FMOD_PRESET_GENERIC;
	if( CheckResult( m_eventsystem->getReverbPreset( pReverbName, &musicreverb, &index ) ) == FMOD_OK )
	{
		CheckResult( m_eventsystem->setReverbProperties( &musicreverb ) );
	}
}

void FmodEventManager::CloseGlobalReverb()
{
	FMOD_REVERB_PROPERTIES reverb = FMOD_PRESET_OFF;

	CheckResult( m_eventsystem->setReverbProperties( &reverb ) );
}

void FmodEventManager::SetReverbState( bool bClose, int type )
{
	int room = bClose?-10000:0;
	FMOD_REVERB_CHANNELPROPERTIES    reverbchannelproperties;    
	if ( type & eMEAUDIO_SOUND )
	{
		EventRegistry::iterator it = m_vEvent.begin();
		while (it != m_vEvent.end())
		{
			memset(&reverbchannelproperties, 0, sizeof(FMOD_REVERB_CHANNELPROPERTIES));
			reverbchannelproperties.Flags = FMOD_REVERB_CHANNELFLAGS_INSTANCE0;
			FMOD_RESULT result = it->second->getReverbProperties(&reverbchannelproperties);
			if (result == FMOD_ERR_INVALID_HANDLE)
			{
				it = m_vEvent.erase(it);
				continue;
			}else
			{
				reverbchannelproperties.Room = room;
				CheckResult(it->second->setReverbProperties(&reverbchannelproperties));
			}
			++it;
		}
	}
	if ( type & eMEAUDIO_MUSIC )
	{
		if (m_musicsystem)
		{
			memset(&reverbchannelproperties, 0, sizeof(FMOD_REVERB_CHANNELPROPERTIES));
			reverbchannelproperties.Flags = FMOD_REVERB_CHANNELFLAGS_INSTANCE0;
			FMOD_RESULT result = m_musicsystem->getReverbProperties(&reverbchannelproperties);
			reverbchannelproperties.Room = room;
			CheckResult(m_musicsystem->setReverbProperties(&reverbchannelproperties));
		}

		if (m_EventMusic)
		{
			memset(&reverbchannelproperties, 0, sizeof(FMOD_REVERB_CHANNELPROPERTIES));
			reverbchannelproperties.Flags = FMOD_REVERB_CHANNELFLAGS_INSTANCE0;
			FMOD_RESULT result = m_EventMusic->getReverbProperties(&reverbchannelproperties);
			if (result == FMOD_ERR_INVALID_HANDLE)
			{
				m_EventMusic = NULL;
			}else
			{
				reverbchannelproperties.Room = room;
				CheckResult(m_EventMusic->setReverbProperties(&reverbchannelproperties));
			}
			
		}
	}
}

void FmodEventManager::Create3DReverb( const char* pReverbName, D3DXVECTOR3 pos, float minDistance, float maxDistance )
{
	if (!m_EventProject || pReverbName == NULL)
		return;

	if ( pReverbName[0] == 0)
		return;

	FMOD::EventReverb               *Reverb;

	if(CheckResult(m_eventsystem->createReverb(&Reverb)) == FMOD_OK)
	{
		int index;
		FMOD_REVERB_PROPERTIES musicreverb = FMOD_PRESET_GENERIC;
		if( CheckResult( m_eventsystem->getReverbPreset( pReverbName, &musicreverb, &index ) ) == FMOD_OK )
		{
			FMOD_VECTOR                      reverbposition;
			reverbposition.x = pos.x;
			reverbposition.y = pos.y;
			reverbposition.z = pos.z;
			CheckResult( Reverb->setProperties( &musicreverb ) );
			CheckResult( Reverb->set3DAttributes(&reverbposition, minDistance, maxDistance));
			CheckResult( Reverb->setActive(true));
			m_v3DReverb.push_back(Reverb);
		}
	}
}

void FmodEventManager::CloseAll3DReverb()
{
	ReverbRegistry::iterator it = m_v3DReverb.begin();
	while( it != m_v3DReverb.end() )
	{
		FMOD::EventReverb *Temp = (*it);
		if (Temp)
		{
			Temp->setActive(false);
			Temp->release();
		}
		++it;
	}
	m_v3DReverb.clear();
}

FMOD_RESULT FmodEventManager::CheckResult(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		m_lasterrorresult = result;
	}
	return result;
}

const char* FmodEventManager::GetLastErrorString()
{
	return FMOD_ErrorString(m_lasterrorresult);
}

void FmodEventManager::UpdateEarPos( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir, int updatetime )
{
	if( !m_eventsystem )
		return ;
	m_vEarPos = vPos;
	m_vEarDir = vDir;

	FMOD_VECTOR listenerpos;
	listenerpos.x = m_vEarPos.x;
	listenerpos.y = m_vEarPos.y;
	listenerpos.z = m_vEarPos.z;

	FMOD_VECTOR listenerdir;
	listenerdir.x = m_vEarDir.x;
	listenerdir.y = m_vEarDir.y;
	listenerdir.z = m_vEarDir.z;


	static FMOD_VECTOR lastpos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR forward        = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR up             = { 0.0f, 1.0f, 0.0f };
	FMOD_VECTOR vel;

	forward = listenerdir;

	vel.x = (listenerpos.x - lastpos.x) * (1000 / updatetime);
	vel.y = (listenerpos.y - lastpos.y) * (1000 / updatetime);
	vel.z = (listenerpos.z - lastpos.z) * (1000 / updatetime);

	lastpos = listenerpos;

	CheckResult( m_eventsystem->set3DListenerAttributes( 0, &listenerpos, &vel, &forward, &up ) );
}

void FmodEventManager::PushEventNameVector( FMOD::EventGroup *group, std::string path, std::vector<std::string> *vEventName )
{
	if ( !group )
		return;

	char *name;
	if( CheckResult( group->getInfo(NULL, &name) ) != FMOD_OK )
		return;

	path += name;
	path += '/';

	int numGroups = 0;
	CheckResult( group->getNumGroups( &numGroups ) );
	for ( int i = 0 ; i < numGroups ; ++i )
	{
		FMOD::EventGroup *nextgroup;
		if( CheckResult( group->getGroupByIndex( i, false, &nextgroup ) ) == FMOD_OK )
		{
			PushEventNameVector(nextgroup, path, vEventName);
		}
	}

	int numEvents = 0;
	CheckResult( group->getNumEvents( &numEvents ) );
	for ( int num = 0; num < numEvents ; ++num )
	{
		FMOD::Event *eve;
		if( CheckResult( group->getEventByIndex( num,  FMOD_EVENT_INFOONLY, &eve) ) == FMOD_OK )
		{
			if( CheckResult( eve->getInfo( NULL, &name, NULL ) ) == FMOD_OK )
			{
				vEventName->push_back( path + name );
			}
		}
	}

}

void FmodEventManager::GetEventNameVector( std::vector<std::string> *vEventName )
{
	if ( !m_EventProject )
		return;

	int numEvents = 0;
	CheckResult( m_eventsystem->getNumEvents( &numEvents ) );
	vEventName->reserve( numEvents );

	int numGroups = 0;
	CheckResult( m_EventProject->getNumGroups( &numGroups ) );
	std::string fullName;
	for ( int i = 0 ; i < numGroups ; ++i )
	{
		fullName.clear();
		FMOD::EventGroup *group;
		if( CheckResult( m_EventProject->getGroupByIndex( i, false, &group ) ) == FMOD_OK )
		{
			PushEventNameVector(group, fullName, vEventName);
		}
	}
}

void FmodEventManager::GetEventWaveBankName( const char* pEvent, std::vector<std::string>& wavebank )
{
	if (!m_EventProject || pEvent == NULL)
		return;

	if ( pEvent[0] == 0)
		return;

	wavebank.clear();

	FMOD::Event *eve;
	if( CheckResult( m_EventProject->getEvent( pEvent, FMOD_EVENT_INFOONLY, &eve) ) == FMOD_OK )
	{
		FMOD_EVENT_INFO info;
#define maxwaveBanks 16
		info.maxwavebanks = maxwaveBanks;
		static FMOD_EVENT_WAVEBANKINFO wavebankinfo[maxwaveBanks];
#undef  maxwaveBanks
		info.wavebankinfo = wavebankinfo;
		if( CheckResult( eve->getInfo( NULL, NULL, &info ) ) == FMOD_OK )
		{
			for (int i = 0 ; i < info.maxwavebanks ; ++i)
			{
				wavebank.push_back(info.wavebankinfo[i].name);
			}
		}
	}
}