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
		eSSC_GLOBAL_LEVEL,	 //ȫ������,0-4���弶,5ʱΪ�Զ���
		eSSC_ADVANCE,		 //�߼�Ч��
		eSSC_TEXTURE_MIPMAP, //��ͼ����
		eSSC_BRIGHT,		 //����
		eSSC_LOWFPS,		 //����ģʽ
		eSSC_RENDER_DISTANCE,//���ƾ���
		eSSC_SHADOW,		 //��ӰЧ��
		eSSC_TERRAIN_DETAIL, //���λ��ϸ��
		eSSC_FONT_SHADOW,	 //��������
		eSSC_WATER,			 //ˮ��Ч��
		eSSC_SKY,			 //����Ч��
		eSSC_GRASS,			 //�ݵ�
		eSSC_DOF,			 //����
		eSSC_BLOOM,			 //ȫ������
		eSSC_LIGHTSHAFT,	 //�����
		eSSC_VERTICLESYNC,	 //��ֱͬ��
		eSSC_MSAA,			 //�����
 		eSSC_WINDOWMODE,	 //����ģʽ
		eSSC_RESOLUTION,	 //�ֱ���
		eSSC_SKELETON,		 //��������
		eSSC_Light,          //���վ���
		eSSC_Effect,         //��Ч����
		eSSC_AnimTimeSetp,	 //��������
		eSSC_CameraShake,	 //��ͷ����

		//lyh���2��Ч��
		eSSC_HDR,  //hdr
		eSSC_TERRAINAOTUTEXTURE,  //���ΰ�͹����ӳ��

		eSSC_TOTAL			 //����
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

	// UserData�ļ����Ƿ����
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
	///ʵ�ʱ任
	void ChangeSetting( eSystemSettingCategory eCategory, 
			unsigned int uiValue );

	///,0-4���弶,5ʱΪ�Զ���
	void SetGlobalLevel( unsigned int uiValue );
	///��ͼ����
	void SetTextureMipMap( unsigned int uiValue );
	///����
	void SetBright( unsigned int uiValue );
	///����ģʽ
	void SetLowFPS( unsigned int uiValue );
	///���ƾ���
	void SetRenderDistance( unsigned int uiValue );
	///��ӰЧ��
	void SetShadow( unsigned int uiValue );
	///���λ��ϸ��
	void SetTerrainDetail( unsigned int uiValue );
	///��������
	void SetFontShadow( unsigned int uiValue );
	///ˮ��Ч��
	void SetWater( unsigned int uiValue );
	///����Ч��
	void SetSky( unsigned int uiValue );
	///�ݵ�
	void SetGrass( unsigned int uiValue );
	///����
	void SetDof( unsigned int uiValue );
	///ȫ������
	void SetBloom( unsigned int uiValue );
	///�����
	void SetLightShaft( unsigned int uiValue );
	///��ֱͬ��
	void SetVerticleSync( unsigned int uiValue );
	///�����
	void SetMSAA( unsigned int uiValue );
	///����ģʽ
	void SetWindowMode( unsigned int uiValue );
	///ViewSet
	void SetViewSet( unsigned int uiValue );
	///�߼�Ч��
	void SetAdvance( unsigned int uiValue );
	///��������
	void SetSkeleton( unsigned int uiValue );
	///���վ���
	void SetLight(unsigned int uiValue);
	///��Ч����
	void SetEffect(unsigned int uiValue);
	///��������
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
