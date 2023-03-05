//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include "MeTerrain/stdafx.h"
#include "SystemSetting.h"
#include "wsRender.h"
#include "Me3d/Config.h"
#include "Me3d/ShaderMgr.h"
#include "Me3d/PostProcess/PostProcessManager.h"
#include "MeFont/MeFont.h"
#include "MeAudio/MeAudio.h"
#include "GameMain.h"
#include "wsCamera.h"
#include "Me3d/ShaderManager.h"
#include "MeFont/MeFontSystem.h"
#include "RapidXml/MeRapidXml.h"
#include "PlayerMgr.h"
#include "mac.h"
#include <winsock2.h>
#include <iphlpapi.h>



//---------------------------------------------------------------------------------
#define FILENAME_XML_DEFAULTSYSTEMSETTING "..\\Data\\ClientConfig\\UserSetting.config"
#define FILENAME_XML_CUSTOMSYSTEMSETTING  "SystemSetting.config"
#define FILENAME_XML_LASTSYSTEMSETTING	  ".\\Config\\LastSystemSetting.xml"
#define XML_ROOT_NAME "Project"
#define XML_DISPLAY_ROOT_NAME "DisplaySetting"
#define XML_LOWLEVEL_CARD_ROOT_NAME "LowLevelCards"
#define XML_LOWLEVEL_CARD_NAME "CardName"
//---------------------------------------------------------------------------------
extern INT NEAR_CHUNK ;
extern INT MAX_FAR_CHUNK ;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern HWND g_hWnd;
extern CHeroGame* theApp;
//---------------------------------------------------------------------------------
SystemSetting* SystemSetting::ms_pThis = 0;
static std::string s_SystemSettingLevelName[SystemSetting::eSSL_TOTAL];
//---------------------------------------------------------------------------------
SystemSetting::SystemSetting()
{
	memset( m_Settings, -1, sizeof( eSystemSettingCategory ) * eSSC_TOTAL );
	memset( m_bDirty, 1, sizeof( bool ) * eSSC_TOTAL );

	m_SettingNames[eSSC_GLOBAL_LEVEL]	 = "GlobalLevel";	 //全局设置,0-4共五级,5时为自定义
	m_SettingNames[eSSC_ADVANCE]		 = "Advance";		 //高级效果
	m_SettingNames[eSSC_TEXTURE_MIPMAP]  = "TextureMipMap";  //贴图精度
	m_SettingNames[eSSC_BRIGHT]			 = "Bright";         //亮度
	m_SettingNames[eSSC_LOWFPS]			 = "LowFPS";		 //节能模式
	m_SettingNames[eSSC_RENDER_DISTANCE] = "RenderDistance"; //绘制距离
	m_SettingNames[eSSC_SHADOW]			 = "Shadow";		 //阴影效果
	m_SettingNames[eSSC_TERRAIN_DETAIL]	 = "TerrainDetail";  //地形混合细节
	m_SettingNames[eSSC_FONT_SHADOW]	 = "FontShadow";	 //字体质量
	m_SettingNames[eSSC_WATER]			 = "Water";			 //水面效果
	m_SettingNames[eSSC_SKY]			 = "Sky";			 //天气效果
	m_SettingNames[eSSC_GRASS]			 = "Grass";			 //草地
	m_SettingNames[eSSC_DOF]			 = "Dof";			 //景深
	m_SettingNames[eSSC_BLOOM]			 = "Bloom";			 //全屏泛光
	m_SettingNames[eSSC_LIGHTSHAFT]		 = "LightShaft";	 //体积光
	m_SettingNames[eSSC_VERTICLESYNC]	 = "VerticleSync";	 //垂直同步
	m_SettingNames[eSSC_MSAA]			 = "MSAA";			 //抗锯齿
 	m_SettingNames[eSSC_WINDOWMODE]		 = "WindowMode";	 //窗口模式
	m_SettingNames[eSSC_RESOLUTION]		 = "Resolution";	 //分辨率
	m_SettingNames[eSSC_SKELETON]		 = "SkeletonShader"; //骨骼动画 
	m_SettingNames[eSSC_Light]           = "Light";          //灯光精度
	m_SettingNames[eSSC_Effect]          = "Effect";         //特效精度
	m_SettingNames[eSSC_AnimTimeSetp]	 = "AnimTimeStep";	 //动画精度
	m_SettingNames[eSSC_CameraShake]	 = "CameraShake";	 //镜头抖动

	m_SettingNames[eSSC_HDR]	             = "Hdr";	 //镜头抖动
	m_SettingNames[eSSC_TERRAINAOTUTEXTURE]	 = "TerrainBump";	 //镜头抖动

	RemoveReadOnlyAttribute( FILENAME_XML_LASTSYSTEMSETTING );

	s_SystemSettingLevelName[eSSL_LOW]		   = "Lowest";
	s_SystemSettingLevelName[eSSL_LOW_MEDIUM]  = "LowLevel";
	s_SystemSettingLevelName[eSSL_MEDIUM]	   = "Medium";
	s_SystemSettingLevelName[eSSL_MEDIUM_HIGH] = "High";
	s_SystemSettingLevelName[eSSL_HIGH]		   = "Highest";

	m_bLowLevelCard = false;
	m_bAdvance = false;
	m_bIsUserDataExisted = false;

	m_uiResolutionHeight = 0;
	m_uiResolutionWidth = 0;

	bCanSet = true;
}


bool GetMacByGetAdaptersAddresses(std::string& macOUT,bool IsRand)
{
	bool ret = false;

	ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
	PIP_ADAPTER_ADDRESSES pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
	if (pAddresses == NULL) 
		return false;
	
	if(GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		free(pAddresses);
		pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
		if (pAddresses == NULL) 
			return false;
	}

	//lyh++ 只获得第一个mac地址
	if(GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == NO_ERROR)
	{
		if(IsRand)
		{
			int MacSum = 0;
			for(PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses != NULL; pCurrAddresses = pCurrAddresses->Next)
			{
				// 确保MAC地址的长度为 00-00-00-00-00-00
				if(pCurrAddresses->PhysicalAddressLength != 6)
					continue;
				++MacSum;
				/*char acMAC[32];
				sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
					int (pCurrAddresses->PhysicalAddress[0]),
					int (pCurrAddresses->PhysicalAddress[1]),
					int (pCurrAddresses->PhysicalAddress[2]),
					int (pCurrAddresses->PhysicalAddress[3]),
					int (pCurrAddresses->PhysicalAddress[4]),
					int (pCurrAddresses->PhysicalAddress[5]));
				macOUT = acMAC;
				ret = true;
				break;*/
			}
			int Rand = rand()%MacSum;
			int i = 0;
			for(PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses != NULL; pCurrAddresses = pCurrAddresses->Next)
			{
				if(pCurrAddresses->PhysicalAddressLength != 6)
					continue;
				if(i == Rand)
				{
					char acMAC[32];
					sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
						int (pCurrAddresses->PhysicalAddress[0]),
						int (pCurrAddresses->PhysicalAddress[1]),
						int (pCurrAddresses->PhysicalAddress[2]),
						int (pCurrAddresses->PhysicalAddress[3]),
						int (pCurrAddresses->PhysicalAddress[4]),
						int (pCurrAddresses->PhysicalAddress[5]));
					macOUT = acMAC;
					ret = true;
					break;
				}
				else
					++i;
			}
		}
		else
		{
			for(PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses != NULL; pCurrAddresses = pCurrAddresses->Next)
			{
				// 确保MAC地址的长度为 00-00-00-00-00-00
				if(pCurrAddresses->PhysicalAddressLength != 6)
					continue;
				char acMAC[32];
				sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
					int (pCurrAddresses->PhysicalAddress[0]),
					int (pCurrAddresses->PhysicalAddress[1]),
					int (pCurrAddresses->PhysicalAddress[2]),
					int (pCurrAddresses->PhysicalAddress[3]),
					int (pCurrAddresses->PhysicalAddress[4]),
					int (pCurrAddresses->PhysicalAddress[5]));
				macOUT = acMAC;
				ret = true;
				break;
			}
		}
	} 

	free(pAddresses);
	return ret;
}

//---------------------------------------------------------------------------------
SystemSetting::~SystemSetting(){}
//---------------------------------------------------------------------------------
SystemSetting* SystemSetting::Instance()
{
	if( !ms_pThis )
		ms_pThis = new SystemSetting;
	
	return ms_pThis;
}
//---------------------------------------------------------------------------------
bool SystemSetting::Destroy()
{
	SAFE_DELETE( ms_pThis );

	return true;
}
//---------------------------------------------------------------------------------
void SystemSetting::SetLevel( eSystemSettingCategory eCategory, 
							  unsigned int uiValue, bool bDirty /*= true*/ )
{
	if( m_Settings[eCategory] == uiValue && eCategory != eSSC_WINDOWMODE)
		return;
	if( IsNeedAdvanceVideoCard( eCategory) && IsLowLevelCard() )
		return;
	m_Settings[eCategory] = uiValue;
	m_bDirty[eCategory] = bDirty;	
}
//---------------------------------------------------------------------------------
void SystemSetting::CommitChanges()
{
	for( int i = 0 ; i < eSSC_TOTAL ; ++ i )
	{
		eSystemSettingCategory eCategory = (eSystemSettingCategory)i;
		ChangeSetting( eCategory, m_Settings[eCategory] );
	}
}
//---------------------------------------------------------------------------------
unsigned int SystemSetting::GetLevel( eSystemSettingCategory eCategory )
{
	return m_Settings[eCategory];
}
//---------------------------------------------------------------------------------
const char* SystemSetting::GetCustomSettingFile()
{
	return FILENAME_XML_CUSTOMSYSTEMSETTING;
}
//---------------------------------------------------------------------------------
bool SystemSetting::LoadLastSetting( const char* pszFileName )
{
	MeXmlDocument SystemSettingXMLDocument;
	bool bRet;
	bool bRetUser = false;
	if ( !pszFileName )
		bRet = SystemSettingXMLDocument.LoadFile( FILENAME_XML_DEFAULTSYSTEMSETTING );
	else
	{
		bRet = SystemSettingXMLDocument.LoadFile( pszFileName );
		bRetUser = bRet;
	}

	//if there is no custom setting, load the default one.
	if( pszFileName && !bRet ) //有用户配置路径 ，但是没有读取成功 ，则读取默认的配置路径
	{		
		bRet = SystemSettingXMLDocument.LoadFile( 
			FILENAME_XML_DEFAULTSYSTEMSETTING );

		if( !bRet )
			return false;
	}
	//load root
	MeXmlElement* pRoot = SystemSettingXMLDocument.FirstChildElement( 
		XML_ROOT_NAME );

	if( !pRoot )
		return false;

	pRoot = pRoot->FirstChildElement( XML_DISPLAY_ROOT_NAME );	

	if( !pRoot )
		return false;
	int nLevel;

   //检查mac地址不一样的话就不读了 用默认的。
	if (bRetUser)
	{
		std::string szMac = "None";
		GetMacByGetAdaptersAddresses(szMac,false);  //不管成功或失败 只要mac地址不一样 就读默认的
			const char* _Mac =	pRoot->Attribute("MAC");
			if ((_Mac && strcmp(_Mac,szMac.c_str())!=0) || !_Mac ) //mac 不一样 读默认的配置
			{
			
				bRet = SystemSettingXMLDocument.LoadFile( 
					FILENAME_XML_DEFAULTSYSTEMSETTING );
				if( !bRet )
					return false;
				pRoot = SystemSettingXMLDocument.FirstChildElement( 
					XML_ROOT_NAME );
				if( !pRoot )
					return false;
				pRoot = pRoot->FirstChildElement( XML_DISPLAY_ROOT_NAME );	
				if( !pRoot )
					return false;
				pRoot->QueryIntAttribute( m_SettingNames[eSSC_WINDOWMODE].c_str(), &nLevel );	
				SetLevel( eSSC_WINDOWMODE, nLevel, false );
				// fsaa
				pRoot->QueryIntAttribute( m_SettingNames[eSSC_MSAA].c_str(), &nLevel );	
				SetLevel( eSSC_MSAA, nLevel, false );

				// resolution
				pRoot->QueryIntAttribute( m_SettingNames[eSSC_RESOLUTION].c_str(), &nLevel );	
				SetLevel( eSSC_RESOLUTION, nLevel, false );

				// skeleton shader
				pRoot->QueryIntAttribute( m_SettingNames[eSSC_SKELETON].c_str(), &nLevel );	
				SetLevel( eSSC_SKELETON, nLevel, false );
				return true;



			

		}
	}
	

  
	//load settings
	

	// window mode
	pRoot->QueryIntAttribute( m_SettingNames[eSSC_WINDOWMODE].c_str(), &nLevel );	
	SetLevel( eSSC_WINDOWMODE, nLevel, false );
	// fsaa
	pRoot->QueryIntAttribute( m_SettingNames[eSSC_MSAA].c_str(), &nLevel );	
	SetLevel( eSSC_MSAA, nLevel, false );

	// resolution
	pRoot->QueryIntAttribute( m_SettingNames[eSSC_RESOLUTION].c_str(), &nLevel );	
	SetLevel( eSSC_RESOLUTION, nLevel, false );

	// skeleton shader
	pRoot->QueryIntAttribute( m_SettingNames[eSSC_SKELETON].c_str(), &nLevel );	
	SetLevel( eSSC_SKELETON, nLevel, false );

	return true;
}
//---------------------------------------------------------------------------------
bool SystemSetting::LoadSetting( const char* pszFileName /* = NULL */ )
{
	char szUserData[MAX_PATH] = {0};
	sprintf_s(szUserData, MAX_PATH - 1, "%s\\Client\\UserData", GetRootPath());
	WIN32_FIND_DATA data;
	HANDLE hFind = ::FindFirstFile(szUserData, &data);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		m_bIsUserDataExisted = false;	
	}
	else
	{
		m_bIsUserDataExisted = true;
		::FindClose(hFind);
	}

	MeXmlDocument SystemSettingXMLDocument;
	bool bRet;
	bool bUseRet = false;
	if( !pszFileName )
		bRet = SystemSettingXMLDocument.LoadFile( FILENAME_XML_DEFAULTSYSTEMSETTING );
	else
	{
		bRet = SystemSettingXMLDocument.LoadFile( pszFileName );
		bUseRet = bRet;
	}

	//if there is no custom setting, load the default one.
	if( pszFileName && !bRet )
	{		
		bRet = SystemSettingXMLDocument.LoadFile( 
			FILENAME_XML_DEFAULTSYSTEMSETTING );

		if( !bRet )
			return false;
	}
	//load root
	MeXmlElement* pRoot = SystemSettingXMLDocument.FirstChildElement( 
		XML_ROOT_NAME );

	if( !pRoot )
		return false;
	
	pRoot = pRoot->FirstChildElement( XML_DISPLAY_ROOT_NAME );	

	if( !pRoot )
		return false;

	if (bUseRet) //读用户文件，判断mac地址
	{
		std::string szMac = "None";
		const char* _Mac =	pRoot->Attribute("MAC");
		GetMacByGetAdaptersAddresses(szMac,false);  //不管成功或失败 只要mac地址不一样 就读默认的
		if ((_Mac && strcmp(_Mac,szMac.c_str())!=0) || !_Mac ) //mac 不一样 读默认的配置
		{
			bRet = SystemSettingXMLDocument.LoadFile( 
				FILENAME_XML_DEFAULTSYSTEMSETTING );

			if( !bRet )
				return false;
			pRoot = SystemSettingXMLDocument.FirstChildElement( 
				XML_ROOT_NAME );

			if( !pRoot )
				return false;

			pRoot = pRoot->FirstChildElement( XML_DISPLAY_ROOT_NAME );	
			if( !pRoot )
				return false;
			int nLevel;
			for( int i = 0 ; i < eSSC_TOTAL ; ++ i )
			{
				pRoot->QueryIntAttribute( m_SettingNames[i].c_str(), &nLevel );
				assert( nLevel >= 0 || nLevel < eSSL_TOTAL );
				if( IsLaterChange( (eSystemSettingCategory)i ) )
					continue;
				SetLevel( ( eSystemSettingCategory )i, nLevel );
			}

			return true;
		
		}
	}

	//load settings
	int nLevel;
	for( int i = 0 ; i < eSSC_TOTAL ; ++ i )
	{
		pRoot->QueryIntAttribute( m_SettingNames[i].c_str(), &nLevel );
		assert( nLevel >= 0 || nLevel < eSSL_TOTAL );
		if( IsLaterChange( (eSystemSettingCategory)i ) )
			continue;
		SetLevel( ( eSystemSettingCategory )i, nLevel );
	}

	return true;
}
//---------------------------------------------------------------------------------
bool SystemSetting::LoadSetting( eSystemSettingLevel eLevel )
{
	MeXmlDocument SystemSettingXMLDocument;
	bool bRet = SystemSettingXMLDocument.LoadFile( 
		FILENAME_XML_DEFAULTSYSTEMSETTING );	
	if( !bRet )
		return false;

	//load root
	MeXmlElement* pRoot = SystemSettingXMLDocument.FirstChildElement( 
		XML_ROOT_NAME );
	if( !pRoot )
		return false;

	pRoot = pRoot->FirstChildElement( XML_DISPLAY_ROOT_NAME );
	if( !pRoot )
		return false;

	pRoot = pRoot->FirstChildElement( s_SystemSettingLevelName[eLevel].c_str() );
	if( !pRoot )
		return false;

	//load settings
	int nLevel;
	for( int i = 0 ; i < eSSC_TOTAL ; ++ i )
	{
		if ( pRoot->QueryIntAttribute( m_SettingNames[i].c_str(), &nLevel ) == MEXML_NO_ATTRIBUTE )
			continue;
		assert( nLevel >= 0 || nLevel < eSSL_TOTAL );
		if( IsLaterChange( (eSystemSettingCategory)i ) )
			continue;
		SetLevel( ( eSystemSettingCategory )i, ( eSystemSettingLevel )nLevel );
	}
	return true;
}
//---------------------------------------------------------------------------------
bool SystemSetting::SaveLastSetting()
{
	MeXmlDocument SystemSettingXMLDocument;
	//header
	SystemSettingXMLDocument.InsertEndChild(
		MeXmlDeclaration( "1.0","utf-8","yes" ) );

	//root
	MeXmlElement* pRootNode = SystemSettingXMLDocument.InsertEndChild( 
		( XML_ROOT_NAME ) );
	if( !pRootNode )
		return false;

	pRootNode = pRootNode->InsertEndChild( ( XML_DISPLAY_ROOT_NAME ) );
	if( !pRootNode )
		return false;

	MeXmlElement* pRoot = pRootNode->ToElement();

	//lyh++ mac
	std::string szMac = "None";
	BOOL bResult = GetMacByGetAdaptersAddresses(szMac,false);
	if (bResult)
	{
		pRoot->SetAttribute("MAC",szMac.c_str());
	}else
	{
      pRoot->SetAttribute("MAC","None");
	}
	

	//save settings
	pRoot->SetAttribute( m_SettingNames[eSSC_WINDOWMODE].c_str(), 
		GetLevel( eSSC_WINDOWMODE ) );

	pRoot->SetAttribute( m_SettingNames[eSSC_RESOLUTION].c_str(), 
		GetLevel( eSSC_RESOLUTION ) );

	//save file
	bool bRet = SystemSettingXMLDocument.SaveFile( 
		FILENAME_XML_LASTSYSTEMSETTING );

	return bRet;
}
//---------------------------------------------------------------------------------
bool SystemSetting::SaveSetting( const char* pszFileName )
{
	MeXmlDocument SystemSettingXMLDocument;
	//header
	SystemSettingXMLDocument.InsertEndChild(
		MeXmlDeclaration( "1.0","utf-8","yes" ) );

	//root
	MeXmlElement* pRootNode = SystemSettingXMLDocument.InsertEndChild( 
		( XML_ROOT_NAME ) );
	if( !pRootNode )
		return false;



	pRootNode = pRootNode->InsertEndChild( ( XML_DISPLAY_ROOT_NAME ) );
	if( !pRootNode )
		return false;

	MeXmlElement* pRoot = pRootNode->ToElement();

	//lyh++ mac
	std::string szMac = "None";
	BOOL bResult = GetMacByGetAdaptersAddresses(szMac,false);
	if (bResult)
	{
		pRoot->SetAttribute("MAC",szMac.c_str());
	}else
	{
		pRoot->SetAttribute("MAC","None");
	}

	//save settings
	for( int i = 0 ; i < eSSC_TOTAL ; ++ i )
	{
		pRoot->SetAttribute( m_SettingNames[i].c_str(), 
			GetLevel( ( eSystemSettingCategory )i ) );
	}
	//save file
	bool bRet = SystemSettingXMLDocument.SaveFile( 
		pszFileName );

	return bRet;
}
//---------------------------------------------------------------------------------
bool SystemSetting::LoadLowLevelVideoCardList()
{
// 	MeXmlDocument LowLevelVideoCardXMLDocument;
// 	bool bRet = LowLevelVideoCardXMLDocument.LoadFile( 
// 		FILENAME_XML_DEFAULTSYSTEMSETTING );	
// 	if( !bRet )
// 		return false;
// 
// 	//load root
// 	MeXmlElement* pRoot = LowLevelVideoCardXMLDocument.FirstChildElement( 
// 		XML_LOWLEVEL_CARD_ROOT_NAME );
// 	if( !pRoot )
// 		return false;
// 	pRoot = pRoot->ToElement();
// 
// 	//load card name
// 	MeXmlElement* pCardName = pRoot->FirstChildElement( XML_LOWLEVEL_CARD_NAME );
// 	while( pCardName )
// 	{
// 		const char* pszText = pCardName->GetText();
// 		std::string strText( pszText );		
// 		m_vLowLevelCards.push_back( pszText );
// 		pCardName = pCardName->NextSiblingElement( XML_LOWLEVEL_CARD_NAME );
// 	}
	return true;
}
//---------------------------------------------------------------------------------
bool SystemSetting::IsLowLevelCard( std::string strCardName )
{
	for( int i = 0 ; i < ( int )m_vLowLevelCards.size(); ++ i )
	{
		std::string strName = m_vLowLevelCards[i];
		int nSize = strName.length();
		if( _strnicmp( strCardName.c_str(), strName.c_str(), 
			 nSize ) == 0 )//found
		{
			m_bLowLevelCard = true;
			return true;
		}
	}	
	return false;
}
//---------------------------------------------------------------------------------
bool SystemSetting::IsLaterChange( eSystemSettingCategory eCategory )
{
	if( eCategory == eSSC_WINDOWMODE ||
		eCategory == eSSC_RESOLUTION ||
		eCategory == eSSC_MSAA 
		)
		return true;
	return false;
}
//---------------------------------------------------------------------------------
void SystemSetting::SetResolution( int nWidth,int nHeight )
{
	if( m_Settings[eSSC_WINDOWMODE] != 1 )
	{
		SetResolutionValueOnly( nWidth, nHeight );
		return;
	}

	m_uiResolutionWidth = nWidth;
	m_uiResolutionHeight = nHeight;

	SCREEN_WIDTH = m_uiResolutionWidth;
	SCREEN_HEIGHT = m_uiResolutionHeight;

	float fScale = (float)SCREEN_HEIGHT/768.0f;
	if ( fScale > 1.0f )
		fScale = 1.0f;
	ControlObject::SetUIScale(1/*(float)SCREEN_HEIGHT/960.0f*/);
	ControlObject::SetFontScale( /*1*/ fScale );
	ControlObject::SetAdjustSCALE( fScale );

	GetMe3dConfig()->m_nScreenWidth = SCREEN_WIDTH;
	GetMe3dConfig()->m_nScreenHeight = SCREEN_HEIGHT;
	getwsCamera()->GetViewPortMain()->Width = SCREEN_WIDTH;
	getwsCamera()->GetViewPortMain()->Height = SCREEN_HEIGHT;

	theApp->ChangeDevice();
	getwsCamera()->ResetViewport();
	
}
//---------------------------------------------------------------------------------
void SystemSetting::AddDisplayMode( D3DDISPLAYMODE& mode )
{
	for( int i = 0 ; i < m_DisplayModes.size() ; ++ i)
	{
		if( m_DisplayModes[i].Width == mode.Width 
			&& m_DisplayModes[i].Height == mode.Height )
			return;
	}
	m_DisplayModes.push_back( mode );
	
}
//---------------------------------------------------------------------------------
void SystemSetting::AddFSAAType( int nType )
{
	//现在只提供2x的抗锯齿，还没有解决显存不够的问题，
	//所以这里加这个临时的判断
	/*
	if( nType != 2 && nType != 0 )
		return;
	*/

	for (int i = 0 ; i < m_FSAAType.size(); ++i)
	{
		if (m_FSAAType[i] == nType)
			return;
	}
	m_FSAAType.push_back( nType );
}
//---------------------------------------------------------------------------------
void SystemSetting::RemoveReadOnlyAttribute( const char* pszFilename )
{
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA( pszFilename,&data );
	bool bFind = ( hFind != INVALID_HANDLE_VALUE );
	if ( bFind )
	{
		DWORD dwAttrs = GetFileAttributes( pszFilename );		
		dwAttrs &= ~FILE_ATTRIBUTE_READONLY;
		SetFileAttributes( pszFilename, dwAttrs ); 			
	}
}

void SystemSetting::ChangeSetting( eSystemSettingCategory eCategory )
{
	ChangeSetting(eCategory,m_Settings[eCategory]);
}


//---------------------------------------------------------------------------------
void SystemSetting::ChangeSetting( eSystemSettingCategory eCategory, 
								  unsigned int uiValue )
{
	SetLight(1);
	if( !m_bDirty[eCategory] )
		return;

	m_bDirty[eCategory] = false;

	switch( eCategory )
	{
	case eSSC_GLOBAL_LEVEL:
		SetGlobalLevel( uiValue );
		break;
	case eSSC_TEXTURE_MIPMAP:
		SetTextureMipMap( 1000/*uiValue*/ );
		break;
	case eSSC_BRIGHT:
		SetBright( uiValue );
		break;
	case eSSC_RENDER_DISTANCE:
		SetRenderDistance( uiValue );
		break;
	case eSSC_SHADOW:
		SetShadow( uiValue );
		break;
	case eSSC_TERRAIN_DETAIL:
		SetTerrainDetail( uiValue );
		break;
	case eSSC_FONT_SHADOW:
		SetFontShadow( uiValue );
		break;
	case eSSC_WATER:
		SetWater( uiValue );
		break;
	case eSSC_SKY:
		SetSky( uiValue );
		break;
	case eSSC_GRASS:
		SetGrass( uiValue );
		break;
	case eSSC_DOF:
		SetDof( uiValue );
		break;
	case eSSC_LIGHTSHAFT:
		SetLightShaft( uiValue );
		break;
	case eSSC_BLOOM:
		SetBloom( uiValue );
		break;
	case eSSC_VERTICLESYNC:
		SetVerticleSync( uiValue );
		break;
	case eSSC_MSAA:
		SetMSAA( uiValue );
	//	if(uiValue > 0)
		//PostProcessManager::instance().enableProcess("Hdr",0);
		break;
	case eSSC_WINDOWMODE:
		SetWindowMode( uiValue );
		break;
	case eSSC_RESOLUTION:
		{
			int nWidth = 1024;
			int nHeight = 768;

			int _tempW , _tempH = 0;
			if (uiValue > 1000)
			{
				_tempW = ((uiValue) >> 16) & 0x0000FFFF;
				 _tempH = uiValue & 0x0000FFFF;
			}

			if (_tempW < nWidth )
			{
				_tempW = nWidth;
			}

			if (_tempH < nHeight )
			{
				_tempH = nHeight;
			}
		
			SetResolution( _tempW,_tempH );

		}
		break;
	case eSSC_LOWFPS:
		SetLowFPS( uiValue );
		break;
	case eSSC_ADVANCE:
		SetAdvance( uiValue );
		break;
	case eSSC_SKELETON:
		SetSkeleton( uiValue );
		break;
	case eSSC_Light:   //光照精度
		if(bCanSet)
		SetLight(uiValue);
		break;
	case eSSC_Effect:  //特效精度
		SetEffect(uiValue);
		break;
	case eSSC_AnimTimeSetp:
		SetAnimTimeStep( uiValue );
		break;
	case eSSC_HDR:
		//if(uiValue>0) //如果开hdr 就关闭抗锯齿。
		//	SetMSAA(0);
		PostProcessManager::instance().enableProcess("Hdr",uiValue);
		break;
	case eSSC_TERRAINAOTUTEXTURE:
		{
			//这里需要 shader mode 3.0 如果显卡不支持的话 则设置为0

			LPDIRECT3DDEVICE9 RI = (LPDIRECT3DDEVICE9) (GetEngine()->GetRenderer()->GetRealDevice());
			D3DCAPS9 _caps;
			RI->GetDeviceCaps(&_caps);

			if( _caps.VertexShaderVersion < D3DVS_VERSION( 3, 0 ) || 
				_caps.PixelShaderVersion < D3DPS_VERSION( 3, 0 ) ) //lyh 地形凹凸纹理映射需要 3.0版本 如果显卡太老，不让这两个选项显示，玩家也就不会操作这个值
			{
				SwGlobal::GetRender()->m_BRenderDepth = false;
				return ;
			}

		SwGlobal::GetRender()->m_BRenderDepth = (bool)uiValue;
		}
		break;
	default:
		break;
	}
}

//---------------------------------------------------------------------------------
void SystemSetting::SetGlobalLevel( unsigned int uiValue )
{
	SystemSetting::Instance()->LoadSetting( (SystemSetting::eSystemSettingLevel)uiValue );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetTextureMipMap( unsigned int uiValue )
{
	int nValue = (int)uiValue;
	float fBias = 2.f - (float)nValue/500.0f;
	GetMe3dConfig()->SetMipLodBais( fBias );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetBright( unsigned int uiValue )
{
	
}
//---------------------------------------------------------------------------------
void SystemSetting::SetLowFPS( unsigned int uiValue )
{
	GetMe3dConfig()->SetLockFPS( (bool)uiValue );
}
extern BOOL g_DynamicMapLoadThreadPause;
extern BOOL g_DynamicMapLoadThreadWillPause;
//---------------------------------------------------------------------------------
void SystemSetting::SetRenderDistance( unsigned int uiValue )
{
	int nValue = (int)uiValue;
	float nFar = ((float)nValue/500.0f) * 
		(MAX_FAR_CHUNK - NEAR_CHUNK)+NEAR_CHUNK;
	SwGlobal::GetRender()->SetFarChunk( nFar );
    if( SwGlobal::GetWorld() && SwGlobal::GetWorld()->GetWorldBuffer() )
        SwGlobal::GetWorld()->GetWorldBuffer()->BackupFarChunk( nFar );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetShadow( unsigned int uiValue )
{
	GetShaderMgr()->SetShadowType( (ShadowType)uiValue );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetTerrainDetail( unsigned int uiValue )
{
	//elevel should be 0,1
	//so add 2
	//to get a value among 2,4
	int nValue = 2;
	if (uiValue == 1)
	{
		nValue = 4;
	}
	GetMe3dConfig()->SetTerrainRenderLayer( nValue );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetFontShadow( unsigned int uiValue )
{	
	FontSystem::UseFontShadow( (bool)uiValue );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetWater( unsigned int uiValue )
{
	int nValue = (int)uiValue;
	nValue += 1;
	//1 or 2
	GetShaderMgr()->SetWaterType( nValue );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetSky( unsigned int uiValue )
{
	GetMe3dConfig()->SetPlayMapEffect( (bool)uiValue );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetGrass( unsigned int uiValue )
{
	SwGlobal::GetRender()->SetRenderDoodad( (bool)uiValue );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetDof( unsigned int uiValue )
{	
	PostProcessManager::instance().enableProcess( 
		"DOF", false );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetBloom( unsigned int uiValue )
{
	PostProcessManager::instance().enableProcess(
		"Bloom", (bool)uiValue );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetLightShaft( unsigned int uiValue )
{
	// modified, [9/17/2010 zhangjiayi]
	// 2.5D永远关闭体积光
	PostProcessManager::instance().enableProcess( 
		"LightShaft", (bool)uiValue );
}
//---------------------------------------------------------------------------------
void SystemSetting::SetVerticleSync( unsigned int uiValue )
{
}
//---------------------------------------------------------------------------------
void SystemSetting::SetMSAA( unsigned int uiValue )
{
	theApp->GetD3DPP()->MultiSampleType = (D3DMULTISAMPLE_TYPE)( uiValue );
	theApp->ChangeDevice(false);
}
//---------------------------------------------------------------------------------
void SystemSetting::SetWindowMode( unsigned int uiValue )
{
	if( !SwGlobal::GetWorld() )
		return;

	bool bWindow = (bool)uiValue;
	if( bWindow )
	{	

		if( m_uiResolutionWidth != 0 && m_uiResolutionHeight != 0 )
		{
			SCREEN_WIDTH = m_uiResolutionWidth;
			SCREEN_HEIGHT = m_uiResolutionHeight;
		} 

		float fScale = (float)SCREEN_HEIGHT/768.0f;
		if ( fScale > 1.0f )
			fScale = 1.0f;
		ControlObject::SetUIScale(1/*(float)SCREEN_HEIGHT/960.0f*/);
	    ControlObject::SetFontScale( /*1*/fScale );
		ControlObject::SetAdjustSCALE( fScale );

		GetMe3dConfig()->m_nScreenWidth = SCREEN_WIDTH;
		GetMe3dConfig()->m_nScreenHeight = SCREEN_HEIGHT;
		getwsCamera()->GetViewPortMain()->Width = SCREEN_WIDTH;
		getwsCamera()->GetViewPortMain()->Height = SCREEN_HEIGHT;
		theApp->ResizeWindow( false );
		getwsCamera()->ResetViewport();
	}
	else //full screen
	{
		RECT& rcDesktop = theApp->GetDesktopRect();
		SCREEN_WIDTH = rcDesktop.right;
		SCREEN_HEIGHT = rcDesktop.bottom;

		float fScale = (float)SCREEN_HEIGHT/768.0f;
		if ( fScale > 1.0f )
			fScale = 1.0f;
		ControlObject::SetUIScale(1/*(float)SCREEN_HEIGHT/960.0f*/);
	    ControlObject::SetFontScale( /*1*/fScale );
		ControlObject::SetAdjustSCALE( fScale );

		GetMe3dConfig()->m_nScreenWidth = SCREEN_WIDTH;
		GetMe3dConfig()->m_nScreenHeight = SCREEN_HEIGHT;
		getwsCamera()->GetViewPortMain()->Width = SCREEN_WIDTH;
		getwsCamera()->GetViewPortMain()->Height = SCREEN_HEIGHT;
		
		theApp->ResizeWindow( true );
		getwsCamera()->ResetViewport();
	}

}
//---------------------------------------------------------------------------------
void SystemSetting::SetViewSet( unsigned int uiValue )
{

}
//---------------------------------------------------------------------------------
void SystemSetting::SetAdvance( unsigned int uiValue )
{
	if( IsLowLevelCard() )
		return;

	theApp->ChangeGraphicsLevel( (int)uiValue );
	m_bAdvance = (bool)uiValue;
	m_bDirty[eSSC_BLOOM] = true;
	m_bDirty[eSSC_SHADOW] = true;
	m_bDirty[eSSC_DOF] = true;
	m_bDirty[eSSC_LIGHTSHAFT] = true;
	m_bDirty[eSSC_SKELETON] = true;
}
//---------------------------------------------------------------------------------
void SystemSetting::SetSkeleton( unsigned int uiValue )
{
	graphics::ShaderManager::instance()->enableSkeletonShader( (bool)uiValue );
}
//---------------------------------------------------------------------------------
bool SystemSetting::IsNeedAdvanceVideoCard( eSystemSettingCategory eCategory )
{
	if( eCategory == eSSC_BLOOM ||
		eCategory == eSSC_SHADOW ||
		eCategory == eSSC_DOF ||
		eCategory == eSSC_LIGHTSHAFT ||
		eCategory == eSSC_SKELETON )
		return true;
	return false;
}
//---------------------------------------------------------------------------------
void SystemSetting::SetResolutionValueOnly( int nWidth, int nHeight )
{
	m_uiResolutionHeight = nHeight;
	m_uiResolutionWidth = nWidth;
}
//---------------------------------------------------------------------------------
//光照精度
void SystemSetting::SetLight(unsigned int uiValue)
{
	theHeroGame.ChangeGraphicsLevel(uiValue);
}
//---------------------------------------------------------------------------------
//特效精度
void SystemSetting::SetEffect(unsigned int uiValue)
{
	if(uiValue == 0)
	    GetEngine()->SetMaxPartNum(1);
	else if(uiValue == 1)
	    GetEngine()->SetMaxPartNum(5);
	else
	    GetEngine()->SetMaxPartNum(10);
}
//---------------------------------------------------------------------------------
void SystemSetting::SetAnimTimeStep(unsigned int uiValue)
{
	if( uiValue == 0 )//低
		theHeroGame.GetPlayerMgr()->SetUpdateAnimTimeStep( 100 );
	else
		theHeroGame.GetPlayerMgr()->SetUpdateAnimTimeStep( 0 );
}