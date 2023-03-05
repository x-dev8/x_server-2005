#ifndef _MexRes_h
#define _MexRes_h
// #include "IdManager.h"
#include "MapContainer.h"
#include "MapStrToID.h"
#include "Mutex.h"

class IMex;
class IRenderable;
class MexCfg;
/*
	Record����֮���ǲ��ᱻ�ͷŵģ�
	����record�����õ���Դ���ǻᱻ�ͷŵģ�
*/
class MexResMgr :public CSemiAutoIntLock
{
public:
	struct Res
	{
		IMex*	pMex;			// ԭʼmex
		MexCfg* pMexCfg;
		BOOL	bDestroying;	// ɾ����־
		BOOL	bStartDestroying;		// ��ʼ����ɾ��
		DWORD	dwStartDestroyTime;

		Res()
		{
			pMex = NULL;
			pMexCfg = NULL;
			bDestroying = FALSE;
			bStartDestroying = FALSE;
			dwStartDestroyTime = 0;
		}
	};
	struct Record : public MeRefAlloc<MexResMgr::Record>, public CSemiAutoIntLock
	{
		int		nId;
		char	szFilename[MAX_PATH];
		Res		res;
        std::string headPicture;
        bool    bRemoveWhenChangeMap;
		uint32	m_uiRefCount;
		void	IncRefCount( bool bKeepOldData = false );
		void	DecRefCount();
		uint32  GetRefCount(){return m_uiRefCount;}
		void	LoadRes( bool bKeepOldData = false );
		void	Release();
		int		GetCfgFrameCount();
		Record();
		~Record();
	};
public:
	MexResMgr();
	~MexResMgr();
	bool TryLock();
	void UnLock();
	BOOL LoadFromDirectory( const char* pszDir );
	BOOL LoadFromSlk( const char* pszFilename );
	BOOL AddFile( const char* pszFilename, int nId, const char* pszHeadPicture = "", bool bRemoveWhenChangeMap = true );

	int	AddExternalFile( const char* pszFilename );

	BOOL Load( const char* pszFilename );
// 	BOOL CreateTree( HWND hTree );
	
	Record* GetRecord( DWORD dwId );
// 	BOOL CreateActionTree( HWND hTree );


// 	IRenderable* GetCharEquipChunk( int nPartId, DWORD dwModelId );
	IMex* GetModel( DWORD dwModelId );
	const char* GetModelFilename( DWORD dwModelId );
	void Destroy();
	Record* CreateModel( int nModelId, bool bKeepCloneMemory = true, bool bKeepOldData = false );	// bKeepCloneMemory���ͷű���һ���ڴ�����Cloneģ�ͣ���ɫ������������Ҫ
	Record* CreateModel( const char* pszFilename, bool bKeepCloneMemory = true, bool bKeepOldData = false );	// bKeepCloneMemory���ͷű���һ���ڴ�����Cloneģ�ͣ���ɫ������������Ҫ
	BOOL	PreloadModel( int nModelId );	// Ԥ����ģ�ͣ������������ü���
	Record*	AddZeroRefModel( int nModelId, IMex* pMex, MexCfg* pMexCfg );
	void DestroyModel( int nModelId );
	int	GetIdByName( const char* pszFilename );

// 	Record* FindEffectInCache( const char* pszFilename );

// 	void	Clear();
	void	ClearDestroyingRes(BOOL bDelay=TRUE, BOOL bIsTool = FALSE);   // bDelay�ȴ�1������ɾ��ģ������
	void	LogError(const char* szFormat, ...);

	// ����������ع��ܣ��ϲ������ļ���
	BOOL	ReallocMexAnimData( int nModelId, int nFrameCount);
	BOOL	CombineMexAnimData( int nModelId, int nCombineModelId, BOOL bReleaseCombineMex = TRUE );	//bReleaseCombineMex���ϲ����Ƿ��ͷ�nCombineModelId��IMex����
	void	BuildKeyFrameTimeList( int nModelId );
	void						OnDeviceLost();
	void						OnDeviceReset();

	void	RemoveUnusedModelWhenChangeMap();			// ����ͼʱ
    void    DumpRecordCount();                          // added by ZhuoMeng.Hu		[10/15/2010]

public:

	std::map<int,Record*> m_RecordMgr;
    //m_Records�ĳ�Map
	//std::vector<Record*> m_Records;
    std::map<std::string, Record*> m_mapRecords;
	std::vector<Record*> m_EffectCache;

	//std::vector<INT> m_LiftCache;

//	CMapStrToIDMgr		m_Finder;

	int					m_dwExternalBase;
	void				(*m_pfnLoadingCallBack)( const char* pszFilename );
};

extern MexResMgr* GetMexResMgr();

#endif