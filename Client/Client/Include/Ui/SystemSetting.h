/********************************************************************
	Filename : UI\SystemSetting.h
*********************************************************************/
#pragma once

#include "MeRTLibs.h"

#include "MeRapidXml.h"

#define FACTOR_SETTING_VALUE 250

class SystemSetting 
{
public://enums

	/*
	@desc: level
	*/
	enum eSystemSettingLevel
	{
		eSSL_LOW,
		eSSL_LOW_MEDIUM,
		eSSL_MEDIUM,
		eSSL_MEDIUM_HIGH,
		eSSL_HIGH,		
		eSSL_TOTAL
	};

	/*
	@desc: category
	*/
	enum eSystemSettingCategory
	{
		eSSC_GLOBAL_LEVEL,	 //全局设置,0-4共五级,5时为自定义
		eSSC_ADVANCE,		 //高级效果
		eSSC_TEXTURE_MIPMAP, //贴图精度
		eSSC_BRIGHT,		 //亮度
		eSSC_LOWFPS,		 //节能模式
		eSSC_RENDER_DISTANCE,//绘制距离
		eSSC_SHADOW,		 //阴影效果
		eSSC_TERRAIN_DETAIL, //地形混合细节
		eSSC_FONT_SHADOW,	 //字体质量
		eSSC_WATER,			 //水面效果
		eSSC_SKY,			 //天气效果
		eSSC_GRASS,			 //草地
		eSSC_DOF,			 //景深
		eSSC_BLOOM,			 //全屏泛光
		eSSC_LIGHTSHAFT,	 //体积光
		eSSC_VERTICLESYNC,	 //垂直同步
		eSSC_MSAA,			 //抗锯齿
 		eSSC_WINDOWMODE,	 //窗口模式
		eSSC_RESOLUTION,	 //分辨率
		eSSC_SKELETON,		 //骨骼动画
		eSSC_Light,          //光照精度
		eSSC_Effect,         //特效精度
		eSSC_AnimTimeSetp,	 //动画精度
		eSSC_CameraShake,	 //镜头抖动

		//lyh添加2中效果
		eSSC_HDR,  //hdr
		eSSC_TERRAINAOTUTEXTURE,  //地形凹凸纹理映射

		eSSC_TOTAL			 //总数
	};


public://public static functions	
	static SystemSetting* Instance();	
	static bool			   Destroy();

public://public functions

	///~ctor
	~SystemSetting();

	///set level
	void SetLevel( eSystemSettingCategory eCategory, 
		unsigned int uiValue, bool bDirty = true );

	///get level
	unsigned int GetLevel( eSystemSettingCategory eCategory );

	///save last setting
	bool SaveLastSetting();

	///load last system setting
	bool LoadLastSetting( const char* pszFileName );

	///load setting
	bool LoadSetting( const char* pszFileName = NULL );

	///save setting
	bool SaveSetting( const char* pszFileName );

	///load default setting by level
	bool LoadSetting( eSystemSettingLevel eLevel );

	/// get custom setting string
	const char* GetCustomSettingFile();

	///load low level video card list
	bool LoadLowLevelVideoCardList();

	///is low level video card
	bool IsLowLevelCard( std::string strCardName );
	bool IsLowLevelCard(){ return m_bLowLevelCard; }
	void SetLowLevelCard( bool bLow ){ m_bLowLevelCard = bLow; }

	// UserData文件夹是否存在
	bool IsUserDataExisted() const { return m_bIsUserDataExisted; }
	void SetUserDataExisted(bool b) { m_bIsUserDataExisted = b; }

	///Commit changes
	void CommitChanges();

	///set resolution
	void SetResolution( int nWidth,int nHeight );

	///add display mode
	void AddDisplayMode( D3DDISPLAYMODE& mode );

	///add msaa type
	void AddFSAAType( int nType );

	///get display mode list
	std::vector<D3DDISPLAYMODE>& GetDisplayModeList(){ return m_DisplayModes; }

	///get msaa type list
	std::vector<int>& GetFSAATypeList(){ return m_FSAAType; }

	///get advance
	bool IsAdvance(){ return m_bAdvance; }

	///need advance render
	bool IsNeedAdvanceVideoCard( eSystemSettingCategory eCategory );

	void ChangeSetting( eSystemSettingCategory eCategory		);

	/// set resolution value only
	void SetResolutionValueOnly( int nWidth, int nHeight );

	int* GetSetings(){return m_Settings; }

	bool bCanSet;

protected://protected functions

	///ctor
	SystemSetting();

	///remove read-only flag
	void RemoveReadOnlyAttribute( const char* pszFilename );
	///is later change
	bool IsLaterChange( eSystemSettingCategory eCategory );
	///实际变换
	void ChangeSetting( eSystemSettingCategory eCategory, 
			unsigned int uiValue );

	///,0-4共五级,5时为自定义
	void SetGlobalLevel( unsigned int uiValue );
	///贴图精度
	void SetTextureMipMap( unsigned int uiValue );
	///亮度
	void SetBright( unsigned int uiValue );
	///节能模式
	void SetLowFPS( unsigned int uiValue );
	///绘制距离
	void SetRenderDistance( unsigned int uiValue );
	///阴影效果
	void SetShadow( unsigned int uiValue );
	///地形混合细节
	void SetTerrainDetail( unsigned int uiValue );
	///字体质量
	void SetFontShadow( unsigned int uiValue );
	///水面效果
	void SetWater( unsigned int uiValue );
	///天气效果
	void SetSky( unsigned int uiValue );
	///草地
	void SetGrass( unsigned int uiValue );
	///景深
	void SetDof( unsigned int uiValue );
	///全屏泛光
	void SetBloom( unsigned int uiValue );
	///体积光
	void SetLightShaft( unsigned int uiValue );
	///垂直同步
	void SetVerticleSync( unsigned int uiValue );
	///抗锯齿
	void SetMSAA( unsigned int uiValue );
	///窗口模式
	void SetWindowMode( unsigned int uiValue );
	///ViewSet
	void SetViewSet( unsigned int uiValue );
	///高级效果
	void SetAdvance( unsigned int uiValue );
	///骨骼动画
	void SetSkeleton( unsigned int uiValue );
	///光照精度
	void SetLight(unsigned int uiValue);
	///特效精度
	void SetEffect(unsigned int uiValue);
	///动画精度
	void SetAnimTimeStep(unsigned int uiValue);

protected://protected static members
	static SystemSetting* ms_pThis;

protected://protected members
	int m_Settings[eSSC_TOTAL];
	std::string m_SettingNames[eSSC_TOTAL];
	bool m_bDirty[eSSC_TOTAL];

	std::vector<std::string> m_vLowLevelCards;
	std::vector<D3DDISPLAYMODE> m_DisplayModes;
	std::vector<int>			m_FSAAType;
	
	bool m_bLowLevelCard;
	bool m_bAdvance;
	bool m_bIsUserDataExisted;
	unsigned int m_uiResolutionWidth;
	unsigned int m_uiResolutionHeight;
	
	MeXmlDocument SystemSettingXMLDocument;
};
