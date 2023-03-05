#pragma once

#include "MapStrToID.h"
#include <Windows.h>
#include <list>
#include "MeFoundation/MeAllocatedObject.h"
#include "Dxsdk/d3dx9math.h"
#include "Singleton.h"
struct SUnreadyPlayReq : public MeAllocatedObject<SUnreadyPlayReq>
{
	BOOL bLoop;
	std::string				m_FileName;
	virtual	int GetType() = 0;
};

class CSoundFileManager : public Singleton<CSoundFileManager>
{
public:
	struct SoundMemoryCache 
	{
		void*	pBuffer;
		int		nSize;
		int		nUsedCount;			//使用次数
		DWORD	dwLastUsedTime;		//最后使用的时间

		SoundMemoryCache()
		{
			pBuffer = NULL;
			nSize = 0;
			nUsedCount = 0;
			dwLastUsedTime = 0;
		}
	};

	struct SoundFile
	{
		DWORD		dwFileID;
		char		szFileName[MAX_PATH];
		//const char*	pFileName;

		SoundFile()
		{
			dwFileID = 0;
			szFileName[0] = '\0';
			//pFileName = NULL;
		}
	};

public:
	CSoundFileManager();
	~CSoundFileManager();

public:
	void		Destroy();
	void		Release(const char* pszFilename);
	void		ClearUselessSoundFileInMemory();		                        // 清理内存中用的不多的声音文件
	void		LoadSoundFileToMemory( const char* pszFilename );
	BOOL		GetSoundFileFromMemory( const char* pszFilename, void** pBuffer, int* nSize );
	void		PlayReadySound(const char* pszFilename,SoundMemoryCache* pCache);
	enum		EUnreadyPlayReqType
	{
		eSoundUnready = 0,
		eMusicUnready
	};
public:
	int			GetSoundFileFinderSize();
	int			GetSoundFileListSize();

	void		AddUnreadyPlayReq(SUnreadyPlayReq* pReq);
private:
	CMapStrToIDMgr			m_SoundFileFinder;
	std::list<SoundFile>	m_SoundFileList;            // 保存的都是相对路径
	SoundFile				m_MusicFile[2];
	std::list<SUnreadyPlayReq*>		mUnreadyPlayReqList;
private:
	DWORD m_dwLastClearSoundFileInMemoryTime;	        // 最后清理内存中声音文件的时间
};

struct SMusicUnreadyPlayReq : public SUnreadyPlayReq
{
	virtual	int GetType() {return CSoundFileManager::eMusicUnready;}
	BOOL bFade;
};
struct SSoundUnreadyPlayReq : public SUnreadyPlayReq
{
	virtual	int GetType() {return CSoundFileManager::eSoundUnready;}
	D3DXVECTOR3 vPos;
	float fMinDistance;
	float fMaxDistance;
};
extern CSoundFileManager* GetSoundMgr();