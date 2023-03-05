/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	World.h
* Create: 	10/06/2006
* Desc:		��ͼ��
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MAP_WORLD_H__
#define _MAP_WORLD_H__

////////////////////////////////////////////////////////////////////////////////
class CWorldTile;
class CWorldBuffer;
class CNdlEnvRes;
class CNdlLightRes;
class CNdlFogRes;
struct FogProperty;
////////////////////////////////////////////////////////////////////////////////
class CWorld 
{
	friend class	CToolWorld;
	friend class	CEditRender;
	friend class	CNdlDecalRes;
	friend class	CWorldEditDoc;
	friend class	CNdlEditWorldPicker;
	friend class	CNdlWorldEditor;
	friend class	CWorldWriteStream;
	friend class	CTextureNavigationWnd;
public:
					CWorld();
					~CWorld();

					// ��ʼ������(ֻ����һ��)
	bool			Create(CWorldBuffer* worldBuffer);	
	void			Destroy();
	
	void			Update( flt32 totalTime, flt32 deltaTime );

					// װ�ء�World �ļ�
					// NOTE: ��ʱ��ֻ�Ƕ���������Ϣ��û���κ���Դ����
					// pathName �͡�worldName ��ϳ�Ҫװ�ص��ļ���
	bool			Load( const char* pathName );
	void			Reset();

	void			OnDeviceLost();
	void			OnDeviceReset( bool bBeforeReset);

	bool			HasName()	{ return m_hasName; };
	void			SetWorldPath( const char* pathName);

					// ��ʽ���뵽����,װ�ر������Դ(�ȽϺ�ʱ)
					// World �������Ӧ Grid ����Ϊ:
					// TileID(0,0)		<=> Pos(-WORLD_TILESIZE*32,-WORLD_TILESIZE*32)	
					// TileID(31,31)	<=> Pos(0.0f,0.0f)										
					// TileID(63,63)	<=> Pos(WORLD_TILESIZE*32,WORLD_TILESIZE*32)	
	bool			SetActivePos( flt32 posX, flt32 posY );
	void			GetActivePos( flt32& posX, flt32& posY );
	bool			IsTileChange();
	void			SetTileChange( bool isChange );

	const char*		GetWorldPath() 	{ return m_worldPath; };
	// ����/ȡ����Ϸ����Ŀ¼
#if _MSC_VER >= 1400
	static void		SetAppCharDir(const char* appPath)	{ strncpy_s( m_appPath, MAX_PATH*2, appPath, (strlen(appPath)+1) ); };
#else
	static void		SetAppCharDir(const char* appPath)	{ strncpy( m_appPath, appPath, (strlen(appPath)+1) ); };
#endif
	static const char* GetAppCharDir()					{ return m_appPath; };
	// ����/ȡ����Ϸ����Ŀ¼
#if _MSC_VER >= 1400
	static void		SetAppDataCharDir(const char* appDataPath)	{ strncpy_s( m_appDataCharPath, MAX_PATH*2, appDataPath, (strlen(appDataPath)+1) ); };
#else
	static void		SetAppDataCharDir(const char* appDataPath)	{ strncpy( m_appDataCharPath, appDataPath, (strlen(appDataPath)+1) ); };
#endif
	static const char* GetAppDataCharDir()					{ return m_appDataCharPath; };
#if _MSC_VER >= 1400
	static void		SetAppDataDir(const wchar_t* appDataPath)	{ wcsncpy_s( m_appDataPath, MAX_PATH*2, appDataPath, (wcslen(appDataPath)+1) ); };
#else
	static void		SetAppDataDir(const TCHAR* appDataPath)	{ wcsncpy( m_appDataPath, appDataPath, (wcslen(appDataPath)+1) ); };
#endif
	static const wchar_t* GetAppDataDir()					{ return m_appDataPath; };

	bool			IsActive() const		{ return m_isActive; };

	void			SetLightAmbientColor( const NiColor& ambient );
	void			SetLightDiffuseColor( const NiColor& diffuse );
	void			SetLightSpecularColor( const NiColor& specular );
	void			SetSunLessColor( const NiColor& specular );
	void			SetLightDir( const Vector& dir );
	
// 	void			SetFogColor( const NiColor& fogColor );
// 	void			SetFogDepth( flt32 fogNear, flt32 fogFar);
	bool			InitZone();

	bool			IsZoneChange();
	bool			IsLightChange();
	bool			IsFogChange();
	
	void			SetZoneChange( bool isChange );
	void			SetLightChange( bool isChange );
	void			SetFogChange( bool isChange );


	CNdlEnvRes*	GetZoneRes();
	CNdlLightRes*	GetLightRes();
	CNdlFogRes*		GetFogRes();
	CWorldBuffer*	GetWorldBuffer() { return m_worldBuffer; };

	bool			IsLoading();


private:
	Vector2			m_activePos;

	bool			m_isActive;
	bool			m_hasName;
	char			m_worldPath[MAX_PATH*2];		//����·��
	static char		m_appPath[MAX_PATH*2];
	static char		m_appDataCharPath[MAX_PATH*2];
	static wchar_t	m_appDataPath[MAX_PATH*2];
	CWorldBuffer*	m_worldBuffer;				// �������г��������ݣ���
};


#endif	// _MAP_WORLD_H__

