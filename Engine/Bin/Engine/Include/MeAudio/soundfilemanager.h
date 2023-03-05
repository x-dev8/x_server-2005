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
		int		nUsedCount;			//ʹ�ô���
		DWORD	dwLastUsedTime;		//���ʹ�õ�ʱ��

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
	void		ClearUselessSoundFileInMemory();		                        // �����ڴ����õĲ���������ļ�
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
	std::list<SoundFile>	m_SoundFileList;            // ����Ķ������·��
	SoundFile				m_MusicFile[2];
	std::list<SUnreadyPlayReq*>		mUnreadyPlayReqList;
private:
	DWORD m_dwLastClearSoundFileInMemoryTime;	        // ��������ڴ��������ļ���ʱ��
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