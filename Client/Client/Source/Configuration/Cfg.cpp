#include <assert.h>
#include "cfg.h"
#include "CfgFileLoader.h"
#include "FuncPerformanceLog.h"
#include "Dxsdk/D3DX9Math.h"
#include "GlobalDef.h"
#include "CameraStuntManager.h"
#include "helper.h"
// #include "Tinyxml/tinyxml.h"
#include "tstring.h"
#include "MeTerrain/stdafx.h"
#include "GameMain.h"
#include "wsCamera.h"
#include "Common.h"
#include "ShowScreenText.h"
#include "MeUtility/tstring.h"
#include "MovieManager.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int g_nDisplayMode;

extern float g_fDisplayZoomInLimit;
extern float g_fPlayerRotateSpeed;
extern float g_fZoomChangeSpeed;
extern float g_fLookatPtHeight;

float g_fMaleLookatPtHeight = 80.0f;//65.0f;
float g_fFemaleLookatPtHeight = 75.0f;//60.0f;

extern float g_fPlayerCollisionHeight;
extern float g_fBeginZoom;
extern float g_fTheRoleSlipJumpingAngle; //主角下滑的角度


extern bool g_bUseD3DFont;
#define XML_VALUE_NAME "Value"

CCfg gCfg;
CCfg::CCfg(void):
m_nLanguage(2)
,m_dwMultiSample( 0 )
,m_bUseSkinMeshShader(FALSE)
,m_nRoleRunLoopTime(600)
{ 
	guardfunc;
	m_fPathDirectionMaxStep = 9;
	m_fPathDirectionMinStep = 2;
	m_bUseSkinMeshShader = FALSE;	
	m_nNameFontSize = 9;
	m_bLocalVersion = 0;
	m_nLocalRoleProfession = 1;
	m_nLocalRoleSex = 0;
	strcpy( m_szNameFontName, "宋体" );
	strcpy( m_szDefaultFont, "宋体" );
	m_nDefaultFontSize = 12;
	m_fNameShowDistance = 35.0f;
	m_fNameFontScale = 6.0f;
	m_fUIFontScale = 2.f;
	m_fNameFontOffset = 0.0f;
	m_dwNameFontFrameColor = D3DCOLOR_XRGB(0,0,0);
	m_isNameFontBold = false;
	m_fModelShowDistance = 300.0f;  // 模型最远渲染距离
	m_fDoodadShowDistance = 35.0f;
	m_fJumpUpValueMale = 0.618f;
	m_fJumpUpValueFemale = 0.618f;
	m_fDropValueMale = 1;
	m_fDropValueFemale = 1;
	m_dwJumpBlendingTimeMale = 0;		
	m_dwJumpBlendingTimeFemale = 0;
	strcpy( m_szSpearCriticalEffectSelf, "" );
	strcpy( m_szStaffCriticalEffectSelf, "" );	
	strcpy( m_szFanCriticalEffectSelf, "" );		
	strcpy( m_szSwordCriticalEffectSelf, "" );
	strcpy( m_szSpearCriticalEffectTarget, "" );
	strcpy( m_szStaffCriticalEffectTarget, "" );		
	strcpy( m_szFanCriticalEffectTarget, "" );		
	strcpy( m_szSwordCriticalEffectTarget, "" );
	strcpy( m_szSpearBackStrikeEffectSelf, "" );	
	strcpy( m_szStaffBackStrikeEffectSelf, "" );	
	strcpy( m_szFanBackStrikeEffectSelf, "" );		
	strcpy( m_szSwordBackStrikeEffectSelf, "" );
	strcpy( m_szSpearBackStrikeEffectTarget, "" );		
	strcpy( m_szStaffBackStrikeEffectTarget, "" );
	strcpy( m_szFanBackStrikeEffectTarget, "" );		
	strcpy( m_szSwordBackStrikeEffectTarget, "" );
	strcpy( m_szSpearDeadlyEffectSelf, "" );		
	strcpy( m_szStaffDeadlyEffectSelf, "" );		
	strcpy( m_szFanDeadlyEffectSelf, "" );		
	strcpy( m_szSwordDeadlyEffectSelf, "" );	
	strcpy( m_szSpearDeadlyEffectTarget, "" );		
	strcpy( m_szStaffDeadlyEffectTarget, "" );		
	strcpy( m_szFanDeadlyEffectTarget, "" );		
	strcpy( m_szSwordDeadlyEffectTarget, "" );	
	strcpy( m_szDoneQuestEffect, "" );
	strcpy( m_szSkillLevelUpEffect, "" );
	m_nCriticalAttackCameraShakeType = CCameraStuntManager::LPOT_NORMAL;
	m_fCriticalAttackMaxShakeRange = 1;
	m_fCriticalAttackMinShakeRange = 0;
	m_dwCriticalAttackShakeKeepTime = 200;
	m_bFastLoadMex = 0;
	m_MaleRoleSetting.clear();
	m_FemaleRoleSetting.clear();
    strcpy( m_pszCreatePlayAnim, "" );
    strcpy( m_pszSelectSceneName, "" );
    m_strSelectSceneModelNotUpdate.clear();
	strcpy( m_szHelpPagePath, "" );
	m_nHelpPageWidth = 800;
	m_nHelpPageHeight = 600;
    m_ucPKLevelLimit = 15;
    m_ucPrivateShopLevelLimit = 15;
    m_shProtectTimeAtLeast = 1;
    m_PingGoodMin = 0;
    m_PingGoodColor = 0xff40ff00;
    m_PingNormalMin = 200;
    m_PingNormalColor = 0xffffd400;
    m_PingBadMin = 500;
    m_PingBadColor = 0xffff2d00;
    m_vectorHideWeaponAnims.clear();
    m_fPlayerScaleMin = 0.9f;
    m_fPlayerScaleMax = 1.1f;
    m_bShopCenterUseQualityColor = false;
    m_bCanCreatePlayer = true;
	m_vectorMirrorType.clear();
	m_mapLotteryBox.clear();
	m_bPlayFriendPointEffect = false;
	m_strFriendPointEffect = "";
	m_bPlayFriendUpgradeEffect = false;
	m_strFriendUpgradeEffect = "";
	for(int i=0; i<EArmType_MaxSize; ++i)
	{
		m_fMountScales[i] = 1.f;
	}
	m_vectorGivePresents.clear();
	m_shLoadMapNum = 20;
	m_fLoadMapProbability = 0.f;
	m_vecProbabilityLoadMaps.clear();

	m_nLoginMapId = -1;
	m_nSelectPlayerMapId = -1;
	m_nCreateMapId = -1;
    m_nFirstMapId = -1;

	RECT rect = {363, 155, 386, 178};
	m_rcFreeTipCloseRect = rect;
	m_strFreeTipCloseBtn = "Data\\Ui\\Common\\HudButton.dds";

	m_nXiaoLaBaItemId = 5703;
	m_nMinSoulItemLevel = 40;
	m_nMinSoulPlayerLevel = 45;
	m_nMinOpenLightPlayerLevel= 60;
	m_nMinOpenLightItemLevel = 60;
	m_nMinHoleLevel = 0;
	m_nMinEquipCopyPlayerLevel= 60;
	m_nMinEquipCopyItemLevel = 60;
	m_dwAutoStarLevelUpInterval = 3000;

	m_nSoulPicWidth = 28;
	m_nSoulPicHeight = 28;

	m_nAchievementFinishHoldTime = 100000;
	m_nAnimationDelayTime = 500;
	m_strAchieveSoundPath = "";
	m_nSimpleMapLoadDistance = 60;
	m_nSimpleMapLoadDistanceFly = 100;
	m_fSelectRoleManScale = 1.2f;
	m_fSelectRoleWomenScale = 1.2f;
	m_fSelectRoleRotateZ = -1.85f;

	m_MaleRoleSetting.clear();
	m_FemaleRoleSetting.clear();

	m_strReliveEffect.clear();  //复活特效
	m_strReliveAnim.clear();    //复活动作
	m_strImmunity.clear();
	m_SuAnimalCardEffect.clear(); //图鉴特效
	m_strNpcShowEffect.clear();
	m_strNpcShowAnim.clear();

	m_strNpcHideEffect.clear();
	m_strNpcHideAnim.clear();

    m_NpcHeadModel.clear();
	m_strRanklistWebPath = "";
	m_nflashWidth = 350;
	m_nflashHeight = 197;
	m_noffsizeX = 29;
	m_noffsizeY = 514;
	m_nFriendLevel = 0;


	bUploadDump=false;
	DumpFtpUser.clear();
	DumpFtpPwd.clear();
	DumpFtpUrl.clear();

	m_strExitPage.clear();
	m_FirstWedAdd.clear();
	m_bOpenExitPage = false;

	m_vecChannelMapId.clear();

	unguard;
}

CCfg::~CCfg(void)
{
	guardfunc;
	m_vecChannelMapId.clear();
	unguard;
}

void CCfg::GetChildElementFloat( MeXmlElement* pElement, 
								const char* pszName, float& fValue )
{
	MeXmlElement* pEle = pElement->FirstChildElement( pszName );
	assert( pEle );
	if( !pEle )
		return ;

	pEle->ToElement()->QueryFloatAttribute( XML_VALUE_NAME, &fValue );

}
void CCfg::GetChildElementInt( MeXmlElement* pElement, 
							  const char* pszName, DWORD& dwValue )
{
	MeXmlElement* pEle = pElement->FirstChildElement( pszName );
	assert( pEle );
	if( !pEle )
		return ;

	pEle->ToElement()->QueryIntAttribute( XML_VALUE_NAME, (int*)&dwValue );

}
void CCfg::GetChildElementInt( MeXmlElement* pElement, 
							 const char* pszName, int& nValue )
{
	MeXmlElement* pEle = pElement->FirstChildElement( pszName );
	assert( pEle );
	if( !pEle )
		return ;

	
	pEle->ToElement()->QueryIntAttribute( XML_VALUE_NAME, &nValue );

}
bool CCfg::GetChildElementString( MeXmlElement* pElement, 
							const char* pszName, std::string& strValue )
{
	strValue.clear();

	MeXmlElement* pEle = pElement->FirstChildElement( pszName );

	assert( pEle );
	if( !pEle )
		return false;

	const char* pszTemp = pEle->ToElement()->Attribute( XML_VALUE_NAME );
	strValue = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszTemp).c_str());
	return true;	
}

void CCfg::InitializeConfig()
{
	guardfunc;
	
	std::string strTemp;
	//load file
	MeXmlDocument GlobalConfigXMLDocument;
	bool bRet = GlobalConfigXMLDocument.LoadFile( XML_GLOBALCONFIG_FILENAME );
	assert( bRet && "无法读取全局配置文件,将读取默认设置" );
	if( !bRet )
		return;
	
	MeXmlElement* pRoot = GlobalConfigXMLDocument.FirstChildElement( XML_GLOBALCONFIG_ROOT_NAME );
	assert( pRoot && "读取全局配置文件根节点失败" );
	if( !pRoot )
		return;

	//lyh++ 鼠标移动目标身上 显示的目标tips位置读取
	m_TargetTipsOffset.left = 100;
	m_TargetTipsOffset.top = 250;
	m_TargetTipsOffset.right = 100;
	m_TargetTipsOffset.bottom = 25;
	MeXmlElement* TargetTipsPos = pRoot->FirstChildElement( "TargetTipsPos" ); 
	if( TargetTipsPos )
	{
		int _value;
		if(TargetTipsPos->QueryIntAttribute( "XOffset",&_value) == MEXML_SUCCESS)
		{
           m_TargetTipsOffset.left = _value;

		}
		if(TargetTipsPos->QueryIntAttribute( "YOffset",&_value) == MEXML_SUCCESS)
		{
           m_TargetTipsOffset.top = _value;
		}

		if(TargetTipsPos->QueryIntAttribute( "offsetX",&_value) == MEXML_SUCCESS)
		{
			m_TargetTipsOffset.right = _value;
			

		}
		if(TargetTipsPos->QueryIntAttribute( "offsetY",&_value) == MEXML_SUCCESS)
		{
			
			m_TargetTipsOffset.bottom = _value;
		}

	}


	/////////////////////////////web setting///////////////////////////////////
	MeXmlElement* pWebPageSetting = pRoot->FirstChildElement( "WebPageSetting" ); 
	if( pWebPageSetting )
	{
		int _value;
		pWebPageSetting->QueryIntAttribute( "OpenExitPage",&_value);
		if (_value <= 0)
		{
			m_bOpenExitPage = false;
		}
		else
			m_bOpenExitPage = true;
		m_strExitPage = pWebPageSetting->Attribute( "ExitPage");
		m_FirstWedAdd = pWebPageSetting->Attribute( "FirstAddYuanBaoPage");
	}
	///////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////load MainSetting////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	MeXmlElement* pMainSetting = pRoot->FirstChildElement( "MainSetting" );
	assert( pMainSetting && "读取MainSetting失败" );
	pMainSetting = pMainSetting->ToElement();

	int nLocalValue;
	GetChildElementInt( pMainSetting, "LocalVersion", nLocalValue );
	m_bLocalVersion = (bool)nLocalValue;
	GetChildElementInt( pMainSetting, "SimpleLoadMode", nLocalValue );
	SwGlobal::s_SimpleMapLoadMode = (bool)nLocalValue;
	GetChildElementInt( pMainSetting, "SimpleLoadMaxDistance", nLocalValue );
	m_nSimpleMapLoadDistance = nLocalValue;
	SwGlobal::s_SimpleMapLoadDistance = nLocalValue;
	GetChildElementInt( pMainSetting, "SimpleLoadFlyMaxDistance", nLocalValue );
	m_nSimpleMapLoadDistanceFly = nLocalValue;
	GetChildElementInt( pMainSetting, "LocalRoleProfession", nLocalValue );
	m_nLocalRoleProfession = (unsigned short)nLocalValue;
	GetChildElementInt( pMainSetting, "LocalRoleSex", nLocalValue );
	m_nLocalRoleSex = (unsigned short)nLocalValue;
	GetChildElementInt( pMainSetting, "Language", m_nLanguage );
	GetChildElementInt( pMainSetting, "NameFontSize", m_nNameFontSize );
	GetChildElementInt( pMainSetting, "DefaultFontSize", m_nDefaultFontSize );
	GetChildElementFloat( pMainSetting, "NameShowDistance", m_fNameShowDistance );
	GetChildElementFloat( pMainSetting, "NameFontScale", m_fNameFontScale );
	GetChildElementFloat( pMainSetting, "NameFontOffset", m_fNameFontOffset );
	GetChildElementFloat( pMainSetting, "UIFontScale", m_fUIFontScale );

	GetChildElementInt( pMainSetting, "LoginMapId", m_nLoginMapId );
	GetChildElementInt( pMainSetting, "SelectMapId", m_nSelectPlayerMapId );
	GetChildElementInt( pMainSetting, "CreateMapId", m_nCreateMapId );
	GetChildElementInt( pMainSetting,"FirstCreateMapId",m_nFirstMapId);

	int value = 0;
	GetChildElementInt( pMainSetting, "NameFontBold", value );
	m_isNameFontBold = value;
	
    
//     MeSprintf_s(m_szLoginPageMusic,sizeof(m_szLoginPageMusic)/sizeof(char) - 1, "%s/Data/Audio/Music/Login.mp3", SwGlobal::GetWorld()->GetAppDataCharDir());
//     MeSprintf_s(m_szSelectPageMusic,sizeof(m_szSelectPageMusic)/sizeof(char) - 1, "%s/Data/Audio/Music/Login.mp3", SwGlobal::GetWorld()->GetAppDataCharDir());
    //锁定被动目标时的特效
	strcpy( m_szLockPassivityTargetEffectPath, "./Data/Effect/Common/TargetPoint1.ini"  );
    //锁定主动目标时的特效
	strcpy( m_szLockInitiativeTargetEffectPath, "./Data/Effect/Common/TargetPoint2.ini" );


	if( GetChildElementString( pMainSetting, "NameFontName", strTemp ) )
		strcpy( m_szNameFontName, strTemp.c_str() );

	if( GetChildElementString( pMainSetting, "DefaultFont", strTemp ) )
		strcpy( m_szDefaultFont, strTemp.c_str() );

	GetChildElementString( pMainSetting, "DumpFtpUser", DumpFtpUser );
	GetChildElementString( pMainSetting, "DumpFtpPwd", DumpFtpPwd );
	GetChildElementString( pMainSetting, "DumpFtpUrl", DumpFtpUrl );
	
	int open_upload_dump=0;
	GetChildElementInt( pMainSetting,"open_upload_dump",open_upload_dump);
	if(open_upload_dump<=0)
		bUploadDump=false;
	else
		bUploadDump=true;


	for ( int n=0; n<MAX_FONTCOUNT; n++ )
	{
		char szFileName[256];
		MeSprintf_s( szFileName, sizeof(szFileName)/sizeof(char) - 1, "FontFile%d", n );
		if( GetChildElementString( pMainSetting, szFileName, strTemp ) )
			strcpy( m_szFontFile[n], strTemp.c_str() );

	}
	if( GetChildElementString( pMainSetting, "HelpPagePath", strTemp ) )
		strcpy( m_szHelpPagePath, strTemp.c_str() );
	GetChildElementInt( pMainSetting, "HelpPageWidth", m_nHelpPageWidth );
	GetChildElementInt( pMainSetting, "HelpPageHeight", m_nHelpPageHeight );

	m_bUseSkinMeshShader = false;

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////load DisplayConfig//////////////////////////////
	//////////////////////////////////////////////////////////////////////////
    MeXmlElement* pDisplayConfig = pRoot->FirstChildElement( "DisplayConfig" );
    //摄象机水平旋转角速率(默认180度/秒)
    if(pDisplayConfig)
	{
		float rotateZSpeed = getwsCamera()->GetCameraRotateZSpeed();
		GetChildElementFloat( pDisplayConfig, "RotateXSpeed", rotateZSpeed );
		getwsCamera()->SetCameraRotateZSpeed( rotateZSpeed );
	}
    else
	{
        getwsCamera()->SetCameraRotateZSpeed( 60 );
	}

	//摄像机垂直旋转角速率(默认180度/秒)
	getwsCamera()->SetCameraRotateXSpeed( 60 );
	//俯仰角度，与地平线的夹角(默认:85度)
    float fDisplayRotateYMin = 85;
	//俯仰角度，与地平线的夹角(默认:-20度)
    float fDisplayRotateYMax = -60;
	//摄像机拉近拉远的速率(默认:6f)
    getwsCamera()->SetZoomChangeSpeed( 6 );

	float rotateXSpeed = getwsCamera()->GetCameraRotateXSpeed();
	float rotateZSpeed = getwsCamera()->GetCameraRotateZSpeed();

	getwsCamera()->SetCameraRotateZSpeed( (float)rotateZSpeed/180*D3DX_PI*0.001f );
	getwsCamera()->SetCameraRotateXSpeed( (float)rotateXSpeed/180*D3DX_PI*0.001f );


	getwsCamera()->SetDisplayRotateYMin( ( (float)fDisplayRotateYMin - 90 )/180*D3DX_PI );
	getwsCamera()->SetDisplayRotateYMax( ( (float)fDisplayRotateYMax - 90 )/180*D3DX_PI );

	m_fFlyRunStep = 6.5f;
    g_fPlayerRotateSpeed = 820;
	g_fPlayerRotateSpeed = (float)g_fPlayerRotateSpeed/180*D3DX_PI;
	
	m_dwMultiSample = 0;

	//////////////////////////////////////////////////////////////////////////
	////////////////////////////load CombatEffect/////////////////////////////
	//////////////////////////////////////////////////////////////////////////
		
	MeXmlElement* pCombatEffect = pRoot->FirstChildElement( "CombatEffect" );
	assert( pCombatEffect && "读取CombatEffect失败" );

    m_dwJumpPlayTimeMale = 700;
    m_dwJumpPlayTimeFemale = 900;

    m_dwFallToTheGroundRunPlayTimeMale = 900;
    m_dwFallToTheGroundRunPlayTimeFemale = 900;

    m_dwDropPlayTimeMale = 300;
    m_dwDropPlayTimeFemale = 300;

    m_fJumpUpValueMale = 0.4f;
    m_fJumpUpValueFemale = 0.4f;

    m_fDropValueMale = 3.f;
    m_fDropValueFemale = 3.f;

    m_dwJumpBlendingTimeMale = 0;
    m_dwJumpBlendingTimeFemale = 0;

	//暴击特效
	if( GetChildElementString( pCombatEffect, "SpearCriticalEffectSelf", strTemp ) )
		strcpy( m_szSpearCriticalEffectSelf, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "StaffCriticalEffectSelf", strTemp ) )
		strcpy( m_szStaffCriticalEffectSelf, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "FanCriticalEffectSelf", strTemp ) )
		strcpy( m_szFanCriticalEffectSelf, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "SwordCriticalEffectSelf", strTemp ) )
		strcpy( m_szSwordCriticalEffectSelf, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "BowCriticalEffectSelf", strTemp ) )
		strcpy( m_szBowCriticalEffectSelf, strTemp.c_str() );

	if( GetChildElementString( pCombatEffect, "SpearCriticalEffectTarget", strTemp ) )
		strcpy( m_szSpearCriticalEffectTarget, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "StaffCriticalEffectTarget", strTemp ) )
		strcpy( m_szStaffCriticalEffectTarget, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "FanCriticalEffectTarget", strTemp ) )
		strcpy( m_szFanCriticalEffectTarget, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "SwordCriticalEffectTarget", strTemp ) )
		strcpy( m_szSwordCriticalEffectTarget, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "BowCriticalEffectTarget", strTemp ) )
		strcpy( m_szBowCriticalEffectTarget, strTemp.c_str() );

	//背击特效
	if( GetChildElementString( pCombatEffect, "SpearBackStrikeEffectSelf", strTemp ) )
		strcpy( m_szSpearBackStrikeEffectSelf, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "StaffBackStrikeEffectSelf" , strTemp) )
		strcpy( m_szStaffBackStrikeEffectSelf, strTemp.c_str());
	if( GetChildElementString( pCombatEffect, "FanBackStrikeEffectSelf", strTemp ) )
		strcpy( m_szFanBackStrikeEffectSelf, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "SwordBackStrikeEffectSelf", strTemp ) )
		strcpy( m_szSwordBackStrikeEffectSelf, strTemp.c_str());
	if( GetChildElementString( pCombatEffect, "BowBackStrikeEffectSelf", strTemp ) )
		strcpy( m_szBowBackStrikeEffectSelf, strTemp.c_str() );

	if( GetChildElementString( pCombatEffect, "SpearBackStrikeEffectTarget" , strTemp) )
		strcpy( m_szSpearBackStrikeEffectTarget,strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "StaffBackStrikeEffectTarget", strTemp ) )
		strcpy( m_szStaffBackStrikeEffectTarget, strTemp.c_str());
	if( GetChildElementString( pCombatEffect, "FanBackStrikeEffectTarget", strTemp ) )
		strcpy( m_szFanBackStrikeEffectTarget, strTemp.c_str());
	if( GetChildElementString( pCombatEffect, "SwordBackStrikeEffectTarget" , strTemp) )
		strcpy( m_szSwordBackStrikeEffectTarget, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "BowBackStrikeEffectTarget" , strTemp) )
		strcpy( m_szBowBackStrikeEffectTarget, strTemp.c_str() );

	//致命攻击特效
	if( GetChildElementString( pCombatEffect, "SpearDeadlyEffectSelf" , strTemp) )
		strcpy( m_szSpearDeadlyEffectSelf, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "StaffDeadlyEffectSelf" , strTemp) )
		strcpy( m_szStaffDeadlyEffectSelf, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "FanDeadlyEffectSelf" , strTemp) )
		strcpy( m_szFanDeadlyEffectSelf,strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "SwordDeadlyEffectSelf" , strTemp) )
		strcpy( m_szSwordDeadlyEffectSelf, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "BowDeadlyEffectSelf" , strTemp) )
		strcpy( m_szBowDeadlyEffectSelf, strTemp.c_str() );

	if( GetChildElementString( pCombatEffect, "SpearDeadlyEffectTarget" , strTemp) )
		strcpy( m_szSpearDeadlyEffectTarget, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "StaffDeadlyEffectTarget", strTemp ) )
		strcpy( m_szStaffDeadlyEffectTarget, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "FanDeadlyEffectTarget" , strTemp) )
		strcpy( m_szFanDeadlyEffectTarget, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "SwordDeadlyEffectTarget" , strTemp) )
		strcpy( m_szSwordDeadlyEffectTarget, strTemp.c_str() );
	if( GetChildElementString( pCombatEffect, "BowDeadlyEffectTarget" , strTemp) )
		strcpy( m_szBowDeadlyEffectTarget, strTemp.c_str() );

    strcpy( m_szDoneQuestEffect, "Common\\DoneQuest.ini" );

    strcpy( m_szSkillLevelUpEffect, "Common\\SkillLevelUp.ini");	

	//暴击摄象机的振动类型
	GetChildElementInt( pCombatEffect, "CriticalAttackCameraShakeType", m_nCriticalAttackCameraShakeType );

	//暴击最大振幅
	GetChildElementFloat( pCombatEffect, "CriticalAttackMaxShakeRange", m_fCriticalAttackMaxShakeRange );

	//暴击最小振幅
	GetChildElementFloat( pCombatEffect, "CriticalAttackMinShakeRange", m_fCriticalAttackMinShakeRange );

	//暴击震动维持时间
	GetChildElementInt( pCombatEffect, "CriticalAttackShakeKeepTime", m_dwCriticalAttackShakeKeepTime );

    m_bFastLoadMex = 0;


	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////load Create Role Setting////////////////////
	//////////////////////////////////////////////////////////////////////////
    MeXmlElement* pCreateRoleSetting = pRoot->FirstChildElement( "CreateRoleSetting" );
    assert( pCreateRoleSetting && "读取CreateRoleSetting失败" );
    if( pCreateRoleSetting )
    {
        MeXmlElement* pElem = NULL;
        // 能否创建人物
        int nValue;
        pElem = pCreateRoleSetting->FirstChildElement("CanCreatePlayer");
        if( pElem )
        {
            if( pElem->QueryIntAttribute("Value", &nValue) == TIXML_SUCCESS )
                m_bCanCreatePlayer = (bool)nValue;
        }
        const char* szValue = NULL;
        // 男
        if( pCreateRoleSetting->FirstChildElement("Male") )
        {
            pElem = pCreateRoleSetting->FirstChildElement("Male")->FirstChildElement("Keys");
            for( ; pElem; pElem = pElem->NextSiblingElement() )
            {
				if(!pElem)
					continue;

				RoleSetting setting;
				szValue = pElem->Attribute("Name");
				std::wstring str;
				str = Common::_tstring::UTF8towcs(szValue);

				setting.m_strName = Common::_tstring::toNarrowString(str.c_str());

				MeXmlElement *pSetting = pElem->FirstChildElement("Key");
				for (;pSetting;pSetting = pSetting->NextSiblingElement())
				{
					CreateRoleSetting kSetting;
					pSetting->QueryIntAttribute("Profession", &kSetting.nProfession);
					pSetting->QueryIntAttribute("FaceModelId", &kSetting.nFaceModelId);
					pSetting->QueryIntAttribute("WeaponModelId", &kSetting.nWeaponModelId);
					pSetting->QueryIntAttribute("WeaponItemId", &kSetting.nWeaponItemId);
					pSetting->QueryIntAttribute("ArmourModelId", &kSetting.nArmourModelId);
					pSetting->QueryIntAttribute("GloveModelId", &kSetting.nGloveModelId);
					pSetting->QueryIntAttribute("HeadModelId", &kSetting.nHeadModelId);
					pSetting->QueryIntAttribute("ShoeModelId", &kSetting.nShoeModelId);
					//pElem->QueryIntAttribute("ShoulderModelId", &kSetting.nShoulderModelId);
					pSetting->QueryIntAttribute("SashModelId", &kSetting.nSashModelId);
					//pElem->QueryIntAttribute("TrousersModelId", &kSetting.nTrousersModelId);

					pSetting->QueryIntAttribute("ArmourItemId", &kSetting.nArmourItemId);
					pSetting->QueryIntAttribute("GloveItemId", &kSetting.nGloveItemId);
					pSetting->QueryIntAttribute("HeadItemId", &kSetting.nHeadItemId);
					pSetting->QueryIntAttribute("ShoeItemId", &kSetting.nShoeItemId);
					//pElem->QueryIntAttribute("ShoulderItemId", &kSetting.nShoulderItemId);
					pSetting->QueryIntAttribute("SashItemId", &kSetting.nSashItemId);
					//pElem->QueryIntAttribute("TrousersItemId", &kSetting.nTrousersItemId);

					szValue = pSetting->Attribute("Effect");
					strcpy( kSetting.szEffectName, szValue );

					setting.m_vCreateSetting.push_back(kSetting);
				}

				m_MaleRoleSetting.push_back(setting);
            }
        }

        // 女
        if( pCreateRoleSetting->FirstChildElement("Female") )
        {
            pElem = pCreateRoleSetting->FirstChildElement("Female")->FirstChildElement("Keys");
            for( ; pElem; pElem = pElem->NextSiblingElement() )
            {
				if(!pElem)
					continue;

			    RoleSetting setting;
				szValue = pElem->Attribute("Name");
				std::wstring str;
				str = Common::_tstring::UTF8towcs(szValue);

				setting.m_strName = Common::_tstring::toNarrowString(str.c_str());

				MeXmlElement *pSetting = pElem->FirstChildElement("Key");
				for (;pSetting;pSetting = pSetting->NextSiblingElement())
				{
					CreateRoleSetting kSetting;
					pSetting->QueryIntAttribute("Profession", &kSetting.nProfession);
					pSetting->QueryIntAttribute("FaceModelId", &kSetting.nFaceModelId);
					pSetting->QueryIntAttribute("WeaponModelId", &kSetting.nWeaponModelId);
					pSetting->QueryIntAttribute("WeaponItemId", &kSetting.nWeaponItemId);
					pSetting->QueryIntAttribute("ArmourModelId", &kSetting.nArmourModelId);
					pSetting->QueryIntAttribute("GloveModelId", &kSetting.nGloveModelId);
					pSetting->QueryIntAttribute("HeadModelId", &kSetting.nHeadModelId);
					pSetting->QueryIntAttribute("ShoeModelId", &kSetting.nShoeModelId);
					//pElem->QueryIntAttribute("ShoulderModelId", &kSetting.nShoulderModelId);
					pSetting->QueryIntAttribute("SashModelId", &kSetting.nSashModelId);
					//pElem->QueryIntAttribute("TrousersModelId", &kSetting.nTrousersModelId);

					pSetting->QueryIntAttribute("ArmourItemId", &kSetting.nArmourItemId);
					pSetting->QueryIntAttribute("GloveItemId", &kSetting.nGloveItemId);
					pSetting->QueryIntAttribute("HeadItemId", &kSetting.nHeadItemId);
					pSetting->QueryIntAttribute("ShoeItemId", &kSetting.nShoeItemId);
					//pElem->QueryIntAttribute("ShoulderItemId", &kSetting.nShoulderItemId);
					pSetting->QueryIntAttribute("SashItemId", &kSetting.nSashItemId);
					//pElem->QueryIntAttribute("TrousersItemId", &kSetting.nTrousersItemId);

					szValue = pSetting->Attribute("Effect");
					strcpy( kSetting.szEffectName, szValue );

                    setting.m_vCreateSetting.push_back(kSetting);
				}

				m_FemaleRoleSetting.push_back(setting);
            }
        }
        // 动画名称
        if( GetChildElementString( pCreateRoleSetting, "PlayAnim" , strTemp) )
        	strncpy( m_pszCreatePlayAnim, strTemp.c_str(), 63 );

        // 身高限制
        pElem = pCreateRoleSetting->FirstChildElement("PlayerScale");
        if( pElem )
        {
            MeXmlElement* pScaleElem = pElem->FirstChildElement("ScaleMin");
            if( pScaleElem )
            {
                pScaleElem->QueryFloatAttribute( "Value", &m_fPlayerScaleMin );
            }

            pScaleElem = pElem->FirstChildElement("ScaleMax");
            if( pScaleElem )
            {
                pScaleElem->QueryFloatAttribute( "Value", &m_fPlayerScaleMax );
            }
        }

		// 选人界面，人物缩放，朝向
		pElem = pCreateRoleSetting->FirstChildElement("SelectRole");
		if( pElem )
		{
			float fValue = 0.f;
			if( pElem->QueryFloatAttribute( "ScaleMan", &fValue ) == TIXML_SUCCESS )
			{
				m_fSelectRoleManScale = fValue;
			}
			if( pElem->QueryFloatAttribute("ScaleWomen",&fValue) == TIXML_SUCCESS)
			{
                m_fSelectRoleWomenScale = fValue;
			}
			if( pElem->QueryFloatAttribute( "CreateScaleMan", &fValue ) == TIXML_SUCCESS )
			{
				m_fCreateRoleManScale = fValue;
			}
			if( pElem->QueryFloatAttribute("CreateScaleWomen",&fValue) == TIXML_SUCCESS)
			{
				m_fCreateRoleWomenScale = fValue;
			}
			if( pElem->QueryFloatAttribute( "RotateZ", &fValue ) == TIXML_SUCCESS )
			{
				m_fSelectRoleRotateZ = fValue;
			}
		}
    }

    MeXmlElement* pPKSetting = pRoot->FirstChildElement( "PKSetting" ); 
    if( pPKSetting )
    {
        int level=0;
        pPKSetting->QueryIntAttribute( "Level", &level );
        m_ucPKLevelLimit = (unsigned char)level;
    }

	MeXmlElement* pVipShout = pRoot->FirstChildElement( "VipShout" ); 
	if( pVipShout )
	{
		int level=0;
		pVipShout->QueryIntAttribute( "ItemID", &level );
		m_nXiaoLaBaItemId = level;
	}

	MeXmlElement* pStam = pRoot->FirstChildElement( "Soul" ); 
	if( pStam )
	{
		int level=0;
		pStam->QueryIntAttribute( "MinItemLevel", &level );
		m_nMinSoulItemLevel = level;
		pStam->QueryIntAttribute( "MinPlayerLevel", &level );
		m_nMinSoulPlayerLevel = level;

		pStam->QueryIntAttribute( "PicWidth", &level );
		m_nSoulPicWidth = level;
		pStam->QueryIntAttribute( "PicHeight", &level );
		m_nSoulPicHeight = level;
	}

	MeXmlElement* pOpenLight = pRoot->FirstChildElement( "OpenLight" ); 
	if( pOpenLight )
	{
		int level=0;
		pOpenLight->QueryIntAttribute( "MinItemLevel", &level );
		m_nMinOpenLightItemLevel = level;
		pOpenLight->QueryIntAttribute( "MinPlayerLevel", &level );
		m_nMinOpenLightPlayerLevel = level;
	}

	MeXmlElement* pHole = pRoot->FirstChildElement( "Hole" ); 
	if( pHole )
	{
		int level=0;
		pHole->QueryIntAttribute( "MinItemLevel", &level );
		m_nMinHoleLevel = level;
	}

	MeXmlElement* pEquipCopy = pRoot->FirstChildElement( "BoZhi" ); 
	if( pEquipCopy )
	{
		int level=0;
		pEquipCopy->QueryIntAttribute( "MinItemLevel", &level );
		m_nMinEquipCopyItemLevel = level;
		pEquipCopy->QueryIntAttribute( "MinPlayerLevel", &level );
		m_nMinEquipCopyPlayerLevel = level;
		pEquipCopy->QueryIntAttribute( "CrossLevel", &level );
		m_nMaxEquipCopyItemCrossLevel = level;
	}

	MeXmlElement* pStar = pRoot->FirstChildElement( "Star" ); 
	if( pStar )
	{
		int level=0;
		pStar->QueryIntAttribute( "AutoLevelUpInterval", &level );
		m_dwAutoStarLevelUpInterval = level;
	}

	MeXmlElement* pAchievement = pRoot->FirstChildElement( "Achievement" ); 
	if( pAchievement )
	{
		int time=0;
		pAchievement->QueryIntAttribute( "FinishTipHoldTime", &time );
		m_nAchievementFinishHoldTime = time;
		pAchievement->QueryIntAttribute( "AnimationDelayTime", &time );
		m_nAnimationDelayTime = time;
		const char* szSoundPath = pAchievement->Attribute("Sound");
		if(szSoundPath != NULL)
		{
			m_strAchieveSoundPath = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(szSoundPath).c_str());
		}
	}

	// 生活技能
    MeXmlElement* pProduceSkillSetting = pRoot->FirstChildElement( "SkillSetting" ); 
    if( pProduceSkillSetting )
    {
        const char* szValue = NULL;
        std::wstring str;
        MeXmlElement* pElem = pProduceSkillSetting->FirstChildElement("Skill");
        for( ; pElem; pElem = pElem->NextSiblingElement() )
        {
            ProduceSkillInfo kSkillInfo;
            pElem->QueryIntAttribute("ID", &kSkillInfo.iSkillId);
            szValue = pElem->Attribute("SkillName");
            str = Common::_tstring::UTF8towcs(szValue);
            strncpy( kSkillInfo.szSkillName, Common::_tstring::toNarrowString(str.c_str()).c_str(), 16 );
            pElem->QueryIntAttribute("LearnSkillNPCID", &kSkillInfo.iLearnSkillNPCId);
            pElem->QueryIntAttribute("SkillPointLv1Limit", &kSkillInfo.SkillPointLimit[0]);
            pElem->QueryIntAttribute("SkillPointLv2Limit", &kSkillInfo.SkillPointLimit[1]);
            pElem->QueryIntAttribute("SkillPointLv3Limit", &kSkillInfo.SkillPointLimit[2]);
            pElem->QueryIntAttribute("SkillPointLv4Limit", &kSkillInfo.SkillPointLimit[3]);
            pElem->QueryIntAttribute("SkillPointLv5Limit", &kSkillInfo.SkillPointLimit[4]);
            pElem->QueryIntAttribute("SkillPointLv6Limit", &kSkillInfo.SkillPointLimit[5]);
            pElem->QueryIntAttribute("SkillPointLv7Limit", &kSkillInfo.SkillPointLimit[6]);
            pElem->QueryIntAttribute("SkillPointLv8Limit", &kSkillInfo.SkillPointLimit[7]);
            pElem->QueryIntAttribute("SkillPointLv9Limit", &kSkillInfo.SkillPointLimit[8]);

            m_vProduceSkillInfo.push_back(kSkillInfo);
        }
    }

    MeXmlElement* pPrivateShopSetting = pRoot->FirstChildElement( "PrivateShopSetting" ); 
    if( pPrivateShopSetting )
    {
        int level=0;
        pPrivateShopSetting->QueryIntAttribute( "Level", &level );
        m_ucPrivateShopLevelLimit = (unsigned char)level;
    }

    // 财产保护
    MeXmlElement* pProtectSetting = pRoot->FirstChildElement( "ProtectSetting" ); 
    if( pProtectSetting )
    {
        const char* szValue = NULL;
        std::wstring str;
        MeXmlElement* pElem = pProtectSetting->FirstChildElement("Protect");
        for( ; pElem; pElem = pElem->NextSiblingElement() )
        {
            std::string strProtect;
            szValue = pElem->Attribute("Str");
            str = Common::_tstring::UTF8towcs(szValue);
            strProtect = Common::_tstring::toNarrowString(str.c_str());

            m_vctStrProtectSetting.push_back(strProtect);
        }
        
        // 最少保护时间
        pElem = pProtectSetting->FirstChildElement("TimeAtLeast");
        if( pElem )
        {
            int time=0;
            pElem->QueryIntAttribute( "Time", &time );
            m_shProtectTimeAtLeast = (short)time;
        }
    }

    // Ping显示设置
    MeXmlElement* pPingSetting = pRoot->FirstChildElement( "PingSetting" ); 
    if( pPingSetting )
    {
        const char* szValue = NULL;
        int r = 0, g = 0, b = 0;
        // 好
        MeXmlElement* pElem = pPingSetting->FirstChildElement("PingGood");
        if( pElem )
        {
            pElem->QueryIntAttribute( "PingMin", &m_PingGoodMin );
            szValue = pElem->Attribute("Color");
            sscanf( szValue, "%d, %d, %d", &r, &g, &b);
            m_PingGoodColor = ( (0xff<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
        }
        // 中
        pElem = pPingSetting->FirstChildElement("PingNormal");
        if( pElem )
        {
            pElem->QueryIntAttribute( "PingMin", &m_PingNormalMin );
            szValue = pElem->Attribute("Color");
            sscanf( szValue, "%d, %d, %d", &r, &g, &b);
            m_PingNormalColor = ( (0xff<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
        }
        // 差
        pElem = pPingSetting->FirstChildElement("PingBad");
        if( pElem )
        {
            pElem->QueryIntAttribute( "PingMin", &m_PingBadMin );
            szValue = pElem->Attribute("Color");
            sscanf( szValue, "%d, %d, %d", &r, &g, &b);
            m_PingBadColor = ( (0xff<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
        }
    }

    // 隐藏武器动作列表
    MeXmlElement* pHideWeaponAnimSetting = pRoot->FirstChildElement( "HideWeaponAnimSetting" ); 
    if( pHideWeaponAnimSetting )
    {
        const char* szValue = NULL;
        MeXmlElement* pElem = pHideWeaponAnimSetting->FirstChildElement("Anim");
        for( ; pElem; pElem = pElem->NextSiblingElement() )
        {
            std::string strAnim;
            szValue = pElem->Attribute("Name");
            strAnim = szValue;
            m_vectorHideWeaponAnims.push_back(strAnim);
        }
    }

    // 商城
    MeXmlElement* pShopCenterSetting = pRoot->FirstChildElement( "ShopCenterSetting" ); 
    if( pShopCenterSetting )
	{
		// 商城物品名称颜色
        MeXmlElement* pElem = pShopCenterSetting->FirstChildElement("UseQualityColor");
        if( pElem )
        {
            int value;
            pElem->QueryIntAttribute( "Value", &value );
            m_bShopCenterUseQualityColor = value;
		}
		// 商城充值网址
		pElem = pShopCenterSetting->FirstChildElement("PayWebAddress");
		if( pElem )
		{
			const char* value = pElem->Attribute( "Value" );
			if (value)
				m_strPayWebAddress = value;
		}
	}
	// 镜像地图列表
	MeXmlElement* pMirrorMapIds = pRoot->FirstChildElement( "MirrorMapIdList" ); 
	if( pMirrorMapIds )
	{
		const char* szValue = NULL;
		MeXmlElement* pElem = pMirrorMapIds->FirstChildElement("MapId");
		for( ; pElem; pElem = pElem->NextSiblingElement() )
		{
			SMirrorType tmp;
			pElem->Attribute("Value",&tmp.m_PrimaryMapId);
			char keyTemp[256];
			int i = 1;
			do 
			{
				MeSprintf_s(keyTemp,sizeof(keyTemp)/sizeof(char) - 1,"Mirror%d",i);
				i++;
				int MirrorMapId;
				if (pElem->Attribute(keyTemp,&MirrorMapId))
				{
					tmp.m_vectorMirrorMapIds.push_back(MirrorMapId);
				}
				else
				{
					break;
				}
			} while (1);

			m_vectorMirrorType.push_back(tmp);
		}
	}

	// 国家地图列表
	{
		MeXmlElement* pCountryList = pRoot->FirstChildElement("CountryMap");
		for( ; pCountryList; pCountryList = pCountryList->NextSiblingElement() )
		{
			int nValue = -1;
			pCountryList->Attribute("Value",&nValue);
			MeXmlElement* pElem = pCountryList->FirstChildElement("MapId");
			for( ; pElem; pElem = pElem->NextSiblingElement() )
			{
				int nMapId = -1;
				pElem->Attribute("Id",&nMapId);
				m_CountryMapInWorldMap.push_back(nMapId);
			}
		}
	}

	//小喇叭
	MeXmlElement* pHornSetting = pRoot->FirstChildElement( "HornEffectSetting" ); 
	if (pHornSetting)
	{
		int value = 0;
		pHornSetting->QueryIntAttribute("EffectShowTime", &value);
		m_HornSetting.m_nEffectShowTime = value;

		pHornSetting->QueryIntAttribute("HornShowTime", &value);
		m_HornSetting.m_nHornShowTime = value;
	}

	MeXmlElement* pGuildCampButtonSparkSetting = pRoot->FirstChildElement( "GuildCampButtonSpartSetting" ); 
	if (pHornSetting)
	{
		const char* szPic = pGuildCampButtonSparkSetting->Attribute("szPicPath");
		if (NULL == szPic)
			m_xGuildCampButton.m_strPicPath = Common::_tstring::toNarrowString( Common::_tstring::UTF8towcs(szPic).c_str() );

		int value = 0;
		pGuildCampButtonSparkSetting->QueryIntAttribute("FramePerTime", &value);
		m_xGuildCampButton.m_nFamePerTime = value;

		pGuildCampButtonSparkSetting->QueryIntAttribute("StartX", &value);
		m_xGuildCampButton.m_nStartX = value;

		pGuildCampButtonSparkSetting->QueryIntAttribute("StartY", &value);
		m_xGuildCampButton.m_nStartY = value;

		pGuildCampButtonSparkSetting->QueryIntAttribute("GapX", &value);
		m_xGuildCampButton.m_nGapX = value;

		pGuildCampButtonSparkSetting->QueryIntAttribute("GapY", &value);
		m_xGuildCampButton.m_nGapY = value;

		pGuildCampButtonSparkSetting->QueryIntAttribute("PicWidth", &value);
		m_xGuildCampButton.m_nPicWidth = value;

		pGuildCampButtonSparkSetting->QueryIntAttribute("PicLength", &value);
		m_xGuildCampButton.m_nPicLength = value;

		pGuildCampButtonSparkSetting->QueryIntAttribute("Row", &value);
		m_xGuildCampButton.m_nRow = value;

		pGuildCampButtonSparkSetting->QueryIntAttribute("Column", &value);
		m_xGuildCampButton.m_nColumn = value;

		pGuildCampButtonSparkSetting->QueryIntAttribute("Count", &value);
		m_xGuildCampButton.m_nCount = value;
	}


	m_fTabFrutomFov = D3DX_PI/3;
	m_fTabFrutomFarDist = 20.0f;
	m_fTabFrutomNearDist = 1.0f;
	m_fTabFrutomToEyeDist = 1.0f;
	m_fTabBackRadius = 10.0f;

	//tab人物裁剪Frustom相关参数
	MeXmlElement* pTabSetting = pRoot->FirstChildElement( "TabSetting" ); 
	if( pTabSetting )
	{
		MeXmlElement* pElem = pTabSetting->FirstChildElement("FrutomFov");
		if( pElem )
		{
			float value;
			pElem->QueryFloatAttribute( "Value", &value );
			m_fTabFrutomFov = value;
		}
		pElem = pTabSetting->FirstChildElement("FrutomFarDist");
		if( pElem )
		{
			float value;
			pElem->QueryFloatAttribute( "Value", &value );
			m_fTabFrutomFarDist = value;
		}
		pElem = pTabSetting->FirstChildElement("TabFrutomNearDist");
		if( pElem )
		{
			float value;
			pElem->QueryFloatAttribute( "Value", &value );
			m_fTabFrutomNearDist = value;
		}
		pElem = pTabSetting->FirstChildElement("TabBackRadius");
		if( pElem )
		{
			float value;
			pElem->QueryFloatAttribute( "Value", &value );
			m_fTabBackRadius = value;
		}
	}

	// 摇奖箱子名称
	MeXmlElement* pLotteryBoxSetting = pRoot->FirstChildElement( "LotteryBoxSetting" ); 
	if( pLotteryBoxSetting )
	{
		const char* szValue = NULL;
		std::wstring str;
		MeXmlElement* pElem = pLotteryBoxSetting->FirstChildElement("Box");
		for( ; pElem; pElem = pElem->NextSiblingElement() )
		{
			int BoxId = 0;
			pElem->QueryIntAttribute("Id", &BoxId);
			std::string strName;
			szValue = pElem->Attribute("Name");
			str = Common::_tstring::UTF8towcs(szValue);
			strName = Common::_tstring::toNarrowString(str.c_str());
			m_mapLotteryBox.insert(std::map<unsigned short,std::string>::value_type(BoxId, strName));
		}
	}

	// 亲密度特效
	MeXmlElement* pFriendPointUp = pRoot->FirstChildElement("FriendPointUp");
	if( pFriendPointUp )
	{
		int iPlay = 0;
		pFriendPointUp->QueryIntAttribute("PlayEffect", &iPlay);
		m_bPlayFriendPointEffect = (bool)(iPlay == 1);
		const char* szValue = pFriendPointUp->Attribute("Path");
		if( szValue )
			m_strFriendPointEffect = szValue;
		// 升级特效
		iPlay = 0;
		pFriendPointUp->QueryIntAttribute("PlayUpgradeEffect", &iPlay);
		m_bPlayFriendUpgradeEffect = (bool)(iPlay == 1);
		szValue = pFriendPointUp->Attribute("UpgradePath");
		if( szValue )
			m_strFriendUpgradeEffect = szValue;
	}

	// 职业对应坐骑大小
	MeXmlElement* pProfessionMountScale = pRoot->FirstChildElement("ProfessionMountScale");
	if( pProfessionMountScale )
	{
		MeXmlElement* pElem = pProfessionMountScale->FirstChildElement("SpearScale");
		if( pElem )
		{
			float scale = 0.f;
			pElem->QueryFloatAttribute("Value", &scale);
			m_fMountScales[EArmType_Warrior] = scale;
		}
		pElem = pProfessionMountScale->FirstChildElement("StaffScale");
		if( pElem )
		{
			float scale = 0.f;
			pElem->QueryFloatAttribute("Value", &scale);
			m_fMountScales[EArmType_Mage] = scale;
		}
		pElem = pProfessionMountScale->FirstChildElement("FanScale");
		if( pElem )
		{
			float scale = 0.f;
			pElem->QueryFloatAttribute("Value", &scale);
			m_fMountScales[EArmType_Taoist] = scale;
		}
		pElem = pProfessionMountScale->FirstChildElement("SwordScale");
		if( pElem )
		{
			float scale = 0.f;
			pElem->QueryFloatAttribute("Value", &scale);
			m_fMountScales[EArmType_Assassin] = scale;
		}
		pElem = pProfessionMountScale->FirstChildElement("BowScale");
		if( pElem )
		{
			float scale = 0.f;
			pElem->QueryFloatAttribute("Value", &scale);
			m_fMountScales[EArmType_Hunter] = scale;
		}
		pElem = pProfessionMountScale->FirstChildElement("HammerScale");
		if( pElem )
		{
			float scale = 0.f;
			pElem->QueryFloatAttribute("Value", &scale);
			m_fMountScales[EArmType_Sniper] = scale;
		}
	}

	// 赠送礼物特效
	MeXmlElement* pGivePresentEffect = pRoot->FirstChildElement("GivePresentEffect");
	if( pGivePresentEffect )
	{
		const char* szValue = NULL;
		MeXmlElement* pElem = pGivePresentEffect->FirstChildElement("Present");
		for( ; pElem; pElem = pElem->NextSiblingElement() )
		{
			SGivePresent present;
			int Id = 0;
			pElem->QueryIntAttribute("ItemId", &Id);
			present.iItemId = Id;
			szValue = pElem->Attribute("Effect");
			if( szValue )
				MeSprintf_s(present.szEffect, sizeof(present.szEffect)/sizeof(char) - 1, "%s", szValue);
			else
				strncpy(present.szEffect, "", sizeof(present.szEffect)-1);
			m_vectorGivePresents.push_back(present);
		}
	}

	// 加载地图UI背景
	MeXmlElement* pLoadMap = pRoot->FirstChildElement("LoadMap");
	if( pLoadMap )
	{
		int iValue = 0;
		if( pLoadMap->QueryIntAttribute("Num", &iValue) == TIXML_SUCCESS )
			m_shLoadMapNum = (short)iValue;
		float fValue = 0.f;
		if( pLoadMap->QueryFloatAttribute("Probability", &fValue) == TIXML_SUCCESS )
		{
			m_fLoadMapProbability = fValue * 0.01f;
			if( m_fLoadMapProbability > 0 )
			{
				MeXmlElement* pElem = pLoadMap->FirstChildElement("Loading");
				for( ; pElem; pElem = pElem->NextSiblingElement() )
				{
					short id = 0;
					if( pElem->QueryIntAttribute("Id", &iValue) == TIXML_SUCCESS )
					{
						id = (short)iValue;
						if( id >= 0 && id < m_shLoadMapNum )
							m_vecProbabilityLoadMaps.push_back(id);
					}
				}
			}
		}
	}

	// FreeTip
	MeXmlElement* pFreeTip = pRoot->FirstChildElement("FreeTip");
	if( pFreeTip )
	{
		const char* pszValue = pFreeTip->Attribute("CloseButton");
		if(pszValue != NULL)
		{
			m_strFreeTipCloseBtn = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str());
		}

		pszValue = pFreeTip->Attribute("CloseRect");
		if(pszValue != NULL)
		{
			std::string str;
			RECT rect;
			str = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str());
			if(sscanf_s(str.c_str(),"%d,%d,%d,%d",&rect.left,&rect.top,	&rect.right,&rect.bottom) == 4)
			{
				m_rcFreeTipCloseRect = rect;
			}
		}
	}

	// ChatPaoPao
	MeXmlElement* pChatPaoPao = pRoot->FirstChildElement("ChatPaoPao");
	if( pChatPaoPao )
	{
		const char* pszValue = pChatPaoPao->Attribute("Texture");
		if(pszValue != NULL)
		{
			m_strChatPaoPaoTexture = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str());
		}
		MeXmlElement* pRect = pChatPaoPao->FirstChildElement("Rect");
		if (pRect)
		{
			int iValue = 0;
			pRect->QueryIntAttribute("Right", &iValue);
			m_ChatPaoPaoRect.right = iValue;
			pRect->QueryIntAttribute("Top", &iValue);
			m_ChatPaoPaoRect.top = iValue;
			pRect->QueryIntAttribute("Left", &iValue);
			m_ChatPaoPaoRect.left = iValue;
			pRect->QueryIntAttribute("Bottom", &iValue);
			m_ChatPaoPaoRect.bottom = iValue;
		}
		MeXmlElement* pInnerRect = pChatPaoPao->FirstChildElement("InnerRect");
		if (pInnerRect)
		{
			int iValue = 0;
			pInnerRect->QueryIntAttribute("Right", &iValue);
			m_ChatPaoPaoInnerRect.right = iValue;
			pInnerRect->QueryIntAttribute("Top", &iValue);
			m_ChatPaoPaoInnerRect.top = iValue;
			pInnerRect->QueryIntAttribute("Left", &iValue);
			m_ChatPaoPaoInnerRect.left = iValue;
			pInnerRect->QueryIntAttribute("Bottom", &iValue);
			m_ChatPaoPaoInnerRect.bottom = iValue;
		}
	}

	//摆摊
	MeXmlElement* pPrivateShop = pRoot->FirstChildElement("PrivateShop");
	if( pPrivateShop )
	{
		const char* pszValue = pPrivateShop->Attribute("Texture");
		if(pszValue != NULL)
		{
			m_strPrivateTexture = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str());
		}
		pszValue = pPrivateShop->Attribute("RealRect");
		if(pszValue)
		{
			if(sscanf_s(pszValue,"%d,%d,%d,%d",&m_RealRect.left,&m_RealRect.top,&m_RealRect.right,&m_RealRect.bottom) != 4)
				assert(0&&"GameSetting.config 摆摊RealReac错误");
		}

		MeXmlElement* pRect = pPrivateShop->FirstChildElement("Rect");
		if (pRect)
		{
			int iValue = 0;
			pRect->QueryIntAttribute("Right", &iValue);
			m_PrivateRect.right = iValue;
			pRect->QueryIntAttribute("Top", &iValue);
			m_PrivateRect.top = iValue;
			pRect->QueryIntAttribute("Left", &iValue);
			m_PrivateRect.left = iValue;
			pRect->QueryIntAttribute("Bottom", &iValue);
			m_PrivateRect.bottom = iValue;
		}
		MeXmlElement* pInnerRect = pPrivateShop->FirstChildElement("InnerRect");
		if (pInnerRect)
		{
			int iValue = 0;
			pInnerRect->QueryIntAttribute("Right", &iValue);
			m_PrivateInnerRect.right = iValue;
			pInnerRect->QueryIntAttribute("Top", &iValue);
			m_PrivateInnerRect.top = iValue;
			pInnerRect->QueryIntAttribute("Left", &iValue);
			m_PrivateInnerRect.left = iValue;
			pInnerRect->QueryIntAttribute("Bottom", &iValue);
			m_PrivateInnerRect.bottom = iValue;
		}
	}
	MeXmlElement* pNoticeSetting = pRoot->FirstChildElement("NoticeSetting");
	if( pNoticeSetting )
	{
		pNoticeSetting->QueryIntAttribute("SkipSameInfoTime",&CShowScreenText::m_nSkipSameInfoTime);
		pNoticeSetting->QueryIntAttribute("ScrollTime",&CShowScreenText::m_nScrollTime);
		pNoticeSetting->QueryIntAttribute("PauseTime",&CShowScreenText::m_nPauseTime);

		pNoticeSetting->QueryIntAttribute("BigTitleYPos",&CShowScreenText::m_nBigTitleYPos);
        pNoticeSetting->QueryIntAttribute("SysInfoYPos",&CShowScreenText::m_nSysInfoYPos);
		pNoticeSetting->QueryIntAttribute("RiseUpInfoYPos",&CShowScreenText::m_nRiseUpInfoYPos);
        pNoticeSetting->QueryIntAttribute("SmallInfoYPos",&CShowScreenText::m_nSmallInfoYPos);

		pNoticeSetting->QueryIntAttribute("FontSizeBigTile",&CShowScreenText::m_nBigTileFontSize);
        pNoticeSetting->QueryIntAttribute("FontSizeSysInfo",&CShowScreenText::m_nSysInfoFontSize);
		pNoticeSetting->QueryIntAttribute("FontSizeRiseUpInfo",&CShowScreenText::m_nRiseUpInfoFontSize);
		pNoticeSetting->QueryIntAttribute("FontSizeSmallInfo",&CShowScreenText::m_nSmallInfoFontSize);

		const char* pszValue = pNoticeSetting->Attribute("FontNameBigTile");
		if (pszValue)
		{
			strcpy( CShowScreenText::m_szBigTileFontName, Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str()).c_str() );
		}
		pszValue = pNoticeSetting->Attribute("FontNameSysInfo");
		if (pszValue)
		{
			strcpy( CShowScreenText::m_szSysInfoFontName, Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str()).c_str() );
		}
		pszValue = pNoticeSetting->Attribute("FontNameRiseUpInfo");
		if (pszValue)
		{
			strcpy( CShowScreenText::m_szRiseUpFontName, Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str()).c_str() );
		}
        pszValue = pNoticeSetting->Attribute("FontNameSmallInfo");
        if (pszValue)
        {
            strcpy( CShowScreenText::m_szSmallFontName, Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str()).c_str() );
        }
	}

	MeXmlElement* pMapElem = pRoot->FirstChildElement("AllNpcList");
	if (pMapElem)
	{
		pMapElem = pMapElem->FirstChildElement("Pic");
		if (pMapElem)
		{
			const char *pszValue = pMapElem->Attribute("Path");
			if(pszValue != NULL)
				m_strMapPath = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str());

			pszValue = pMapElem->Attribute("BgSrc");
			if(pszValue != NULL)
			{
				std::string str;
				str = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str());
				if(sscanf_s(str.c_str(),"%d,%d,%d,%d",&m_BgSrc.left,&m_BgSrc.top,&m_BgSrc.right,&m_BgSrc.bottom) != 4)
				{
					assert(0&&"AllNpcList错误");
				}
			}
		}
	}

	// 上线奖励特效
	MeXmlElement* pOnlineReward = pRoot->FirstChildElement("OnlineReward");
	if( pOnlineReward )
	{
		const char* pcValue = pOnlineReward->Attribute("Path");
		if( pcValue )
		{
			m_strOnlineRewardFile = pcValue;
		}

		int nValue = 0;

		pOnlineReward->QueryIntAttribute("ItemWidth", &nValue);
		m_nOnlineRewardItemWidth = nValue;

		pOnlineReward->QueryIntAttribute("ItemHeight", &nValue );
		m_nOnlineRewardItemHeight = nValue;

		pOnlineReward->QueryIntAttribute("Row", &nValue );
		m_nOnlineRewardRow = nValue;

		pOnlineReward->QueryIntAttribute("Column", &nValue );
		m_nOnlineRewardColumn = nValue;

		pOnlineReward->QueryIntAttribute("Time", &nValue );
		m_nOnlineRewardTime = nValue;

		pOnlineReward->QueryIntAttribute("Count", &nValue );
		m_nOnlineRewardCount = nValue;

	}
	
	// 动画配置           added by zhuomeng.hu		[3/1/2011]
	CMovieManager::Instance()->LoadConfig( pRoot );

	//////////////////////////////////////////////////////////////////////////
	/////////////////////Load Player Actions When Singing/////////////////////
	//////////////////////////////////////////////////////////////////////////
	/*<PlayerNPCActions>
		<!--NPCId : npc id, ActionName : 动作名称, SingTime : 吟唱时间-->
		<PlayerNPCAction NPCId ="" ActionName = "" SingTime = ""/>
		<PlayerNPCAction NPCId ="" ActionName = "" SingTime = ""/>
	</PlayerNPCActions>*/

	MeXmlElement* pPlayerNPCActions = pRoot->FirstChildElement( "PlayerNPCActions" );
	if( pPlayerNPCActions )
	{
		pPlayerNPCActions = pPlayerNPCActions->FirstChildElement( "PlayerNPCAction" );
		while( pPlayerNPCActions )
		{
			PlayerNPCActions kPNA;
			
			const char* pcValue = pPlayerNPCActions->Attribute( "Id" );
			if( pcValue )
				kPNA.m_nId = atoi( pcValue );

			pcValue = pPlayerNPCActions->Attribute( "ActionName" );
			if( pcValue )
				strcpy( kPNA.m_acSingName, Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pcValue).c_str()).c_str() );

			m_PlayerNpcActions.insert( std::make_pair( kPNA.m_nId, kPNA ) );
			pPlayerNPCActions = pPlayerNPCActions->NextSiblingElement( "PlayerNPCAction" );
		}
	}

	MeXmlElement* pPlayerAnimation = pRoot->FirstChildElement( "RoleAnimation" );
	if( pPlayerAnimation )
	{
		int nValue = 0;
		pOnlineReward->QueryIntAttribute("RunLoopTime", &nValue);
		if( nValue > 0 )
			m_nRoleRunLoopTime = nValue;
	}

	MeXmlElement* pRelive = pRoot->FirstChildElement("Relive");
	if(pRelive)
	{
		const char* pcValue = pRelive->Attribute( "Effect" );
		if( pcValue )
			m_strReliveEffect = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pcValue).c_str());
		
		pcValue = pRelive->Attribute("Anim");
		if(pcValue)
			m_strReliveAnim = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pcValue).c_str());
	}
	MeXmlElement* pSuAnimalCard = pRoot->FirstChildElement("SuAnimalCardEffect");
	if (pSuAnimalCard != NULL)
	{
		const char*pValue = pSuAnimalCard->Attribute("Effect");
		if (pValue != NULL)
		{
			m_SuAnimalCardEffect = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pValue).c_str());
		}
	}
	MeXmlElement* pImmunity = pRoot->FirstChildElement("Immunity");
	if(pImmunity)
	{
		const char* pcImmunity = pImmunity->Attribute("Effect");
		if(pcImmunity)
			m_strImmunity = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pcImmunity).c_str());
	}
	
	MeXmlElement* pNpcShowEffect = pRoot->FirstChildElement("NpcShowEffect");
	if(pNpcShowEffect)
	{
		MeXmlElement *pHide = pNpcShowEffect->FirstChildElement("Hide");
		if(pHide)
		{
			const char* pszShowEffect = pHide->Attribute("Effect");
			if(pszShowEffect)
				m_strNpcShowEffect = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszShowEffect).c_str());

			const char* pszShowAnim = pHide->Attribute("Anim");
			if(pszShowAnim)
				m_strNpcShowAnim = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszShowAnim).c_str());
		}

		MeXmlElement *pShow = pNpcShowEffect->FirstChildElement("Show");
		if(pShow)
		{
			const char* pszShowEffect = pShow->Attribute("Effect");
			if(pszShowEffect)
				m_strNpcHideEffect = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszShowEffect).c_str());

			const char* pszShowAnim = pShow->Attribute("Anim");
			if(pszShowAnim)
				m_strNpcHideAnim = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszShowAnim).c_str());
		}
	}

	MeXmlElement* pNpcHead = pRoot->FirstChildElement("NpcHeadModel");
	if(pNpcHead)
	{
		MeXmlElement *pElem = pNpcHead->FirstChildElement("Npc");
		for (;pElem != NULL;pElem = pElem->NextSiblingElement())
		{
			NpcHeadModel model;
			float fStature = 0.0f,fX = 0.0f, fY = 0.0f,fWidth=0.0f,fHeight=0.0f,fViewHigh = 0.0f;
			float fScale = 0.06f;

			pElem->QueryFloatAttribute("fStature",&fStature);
			model.fStature = fStature;

			pElem->QueryFloatAttribute("fX",&fX);
			model.fX = fX;

			pElem->QueryFloatAttribute("fY",&fY);
			model.fY = fY;

			pElem->QueryFloatAttribute("fWidth",&fWidth);
			model.fWidth = fWidth;

			pElem->QueryFloatAttribute("fHeight",&fHeight);
			model.fHeight = fHeight;

			pElem->QueryFloatAttribute("viewHigh",&fViewHigh);
			model.fViewHigh = fViewHigh;

			pElem->QueryFloatAttribute("fScale",&fScale);
			model.fScale = fScale;

			m_NpcHeadModel.insert(std::make_pair(fStature,model));
		}
	}

	MeXmlElement *pFriendLevel = pRoot->FirstChildElement("Friend");
	if(pFriendLevel)
	{
		int nValue = 0;
		pFriendLevel->Attribute("Level",&nValue);
		m_nFriendLevel = nValue;
	}
	
	MeXmlElement *pRankWebPath = pRoot->FirstChildElement("RankWebPath");
	if (pRankWebPath)
	{
		Common::_tstring strWebPath;
		MeXmlElement *pPath = pRankWebPath->FirstChildElement("Path");
		if (pPath)
		{
			strWebPath.fromUTF8(pPath->Attribute("http"));
			m_strRanklistWebPath = strWebPath;
		}
	}
	//
	MeXmlElement *pFlashWindow = pRoot->FirstChildElement("FlashWindow");
	if (pFlashWindow)
	{
		int flashWidth=0,flashHeight=0,offsizeX=0,offsizeY=0;
		if (pFlashWindow->Attribute("flashWidth",&flashWidth))
		{
			m_nflashWidth = flashWidth;
		}
		if (pFlashWindow->Attribute("flashHeight",&flashHeight))
		{
			m_nflashHeight = flashHeight;
		}
		if (pFlashWindow->Attribute("offsizeX",&offsizeX))
		{
			m_noffsizeX = offsizeX;
		}
		if (pFlashWindow->Attribute("offsizeY",&offsizeY))
		{
			m_noffsizeY = offsizeY;
		}
		
	}


	m_IsOpenPetAtter = true;
	MeXmlElement *pPet = pRoot->FirstChildElement("PetAttacter");
	int Value = 0;
	if (pPet->Attribute("IsOpen",&Value))
	{
		m_IsOpenPetAtter = (Value == 1)?true:false;
	}

	MeXmlElement *pSelectChannel = pRoot->FirstChildElement("SelectChannel");
	if ( pSelectChannel )
	{
		Common::_tstring strMapIds;
		strMapIds.fromUTF8(pSelectChannel->Attribute("MapIds"));
		if ( !strMapIds.empty() )
		{
			m_vecChannelMapId.clear();
			char *szSpn = ",";
			char *szStr;

			szStr = strtok( const_cast<char*>(strMapIds.c_str()),szSpn );
			while( szStr )
			{
				m_vecChannelMapId.push_back( atoi(szStr) );

				szStr = strtok( NULL,szSpn );
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////load Others/////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	m_bIsOpenResourceCkeck = false;
	m_dwAntiTime = 0;

	
	//install font
	for ( int n=0; n<MAX_FONTCOUNT; n++ )
	{
		InstallFont( m_szFontFile[n] );
	}
	//m_bUseTexGroupMap = FALSE;

    // 选人、创建人物场景名称
    strncpy(m_pszSelectSceneName, "playerselect", sizeof(m_pszSelectSceneName)-1);// 确保小写
    m_strSelectSceneModelNotUpdate.push_back("select.mex"); // 确保小写
 
 	unguard;
 }

BOOL CCfg::InstallFont( const char* szFile )
{
	//	return TRUE;
	//.TTF  file  name.
	if ( !szFile || strlen( szFile ) <= 4 )
	{
		return FALSE;
	}
    std::string filename = szFile;
    std::string::size_type p = filename.find_last_of('/');
    if (p != std::string::npos)
    {
        filename = filename.substr(p + 1);
    }

	TCHAR sWinDir[MAX_PATH] = {0};  
	GetWindowsDirectory(sWinDir,MAX_PATH);
	std::string sFontDir = sWinDir;
	sFontDir += "\\Fonts\\";
	char szFOTFile[MAX_PATH] = {0};
	strncpy( szFOTFile, sFontDir.c_str(), MAX_PATH-1 );
	strcat_s( szFOTFile, filename.c_str() );
	int n = strlen(szFOTFile) - 4;
	szFOTFile[n] = 0;
	strcat_s( szFOTFile, ".FOT" );
	//Copying file is used to install font file  
	std::string strDest = sFontDir+filename;
	WIN32_FIND_DATAA data;

	// added, jiayi, [2009/9/1]
	// 删除之前创建的.fot文件	
	HANDLE hFind = FindFirstFileA( szFOTFile,&data );
	bool bFind = ( hFind != INVALID_HANDLE_VALUE );

	// added, jiayi, [2009/9/1]
	// 移除只读属性，copyfile会带属性拷贝	
	hFind = FindFirstFileA( szFile,&data );
	bFind = ( hFind != INVALID_HANDLE_VALUE );
	if ( bFind )
	{
		DWORD dwAttrs = GetFileAttributes( szFile );		
		dwAttrs &= ~FILE_ATTRIBUTE_READONLY;
		SetFileAttributes( szFile, dwAttrs ); 			
	}
	// 移除目标文件的只读属性
	hFind = FindFirstFileA( strDest.c_str(),&data );
	bFind = ( hFind != INVALID_HANDLE_VALUE );
	if ( bFind )
	{
		DWORD dwAttrs = GetFileAttributes( strDest.c_str() );		
		dwAttrs &= ~FILE_ATTRIBUTE_READONLY;
		SetFileAttributes( strDest.c_str(), dwAttrs ); 			
	}
	BOOL  Result;
	Result = CopyFile( szFile, strDest.c_str(), true);  
	Result = CreateScalableFontResource( 0, szFOTFile, filename.c_str(), sFontDir.c_str() );

	Result = AddFontResource(szFOTFile);  

	::PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);  
	return TRUE;
}

AreaInfo CCfg::Areas[AREA_COUNT] = {{"","",""},{"","",""},{"","",""},{"","",""},{"","",""},{"","",""},{"","",""},{"","",""},{"","",""},{"","",""}};

ProduceSkillInfo* CCfg::GetProduceSkillInfo( int iSkillId )
{
    for(int i=0; i<m_vProduceSkillInfo.size(); i++)
    {
        if( m_vProduceSkillInfo[i].iSkillId == iSkillId )
            return &m_vProduceSkillInfo[i];
    }
    return NULL;
}

BOOL CCfg::IsMirrorMapIds( int nMapId )
{
	for(int i = 0; i < m_vectorMirrorType.size();++i)
	{
		SMirrorType& mirrorType = m_vectorMirrorType[i];
		for(int j = 0; j < mirrorType.m_vectorMirrorMapIds.size(); ++j)
		{
			if (mirrorType.m_vectorMirrorMapIds[j] == nMapId)
			{
				return true;
			}
		}
	}
	return false;
}

int CCfg::GetPrimaryMapId( int nMapId )
{
	for(int i = 0; i < m_vectorMirrorType.size();++i)
	{
		SMirrorType& mirrorType = m_vectorMirrorType[i];
		for(int j = 0; j < mirrorType.m_vectorMirrorMapIds.size(); ++j)
		{
			if (mirrorType.m_vectorMirrorMapIds[j] == nMapId)
			{
				return mirrorType.m_PrimaryMapId;
			}
		}
	}
	return nMapId;

}

int CCfg::GetMyCountryMapId( int MapId,int nCountry )
 {
	SMirrorType* pMirrorMap = NULL;
	for(int i = 0; i < m_vectorMirrorType.size();++i)
	{
		SMirrorType& mirrorType = m_vectorMirrorType[i];
		if (mirrorType.m_PrimaryMapId == MapId)
		{
			pMirrorMap = &mirrorType;
			break;
		}
		for(int j = 0; j < mirrorType.m_vectorMirrorMapIds.size(); ++j)
		{
			if (mirrorType.m_vectorMirrorMapIds[j] == MapId)
			{
				pMirrorMap = &mirrorType;
				break;
			}
		}
		if (pMirrorMap)
		{
			break;
		}
	}
	int nRet = MapId;
	if (pMirrorMap)
	{
		std::map<int, int>::iterator iter = m_vectorCountryMap.find(pMirrorMap->m_PrimaryMapId);
		
		if (iter != m_vectorCountryMap.end() && iter->second == nCountry)
		{
			nRet = iter->first;
		}
		else
		{
			for(int j = 0; j < pMirrorMap->m_vectorMirrorMapIds.size(); ++j)
			{
				iter = m_vectorCountryMap.find(pMirrorMap->m_vectorMirrorMapIds[j]);
				if (iter != m_vectorCountryMap.end())
				{
					if (iter->second == nCountry)
					{
						nRet = iter->first;
						break;
					}
				}
			}
		}
	}
	return nRet;
}

void CCfg::FillTileIdCountryMap()
{
	CWorldBuffer* pWorldBuffer = SwGlobal::GetWorld()->GetWorldBuffer();
	std::map<sInt32,CWorldTile*>& TileMap = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileMapHash(); 
	for (std::map<sInt32,CWorldTile*>::iterator iter = TileMap.begin(); iter != TileMap.end(); ++iter)
	{
		CWorldTile* pTile = iter->second;
		m_vectorCountryMap.insert(std::map<int, int>::value_type(iter->first,pTile->GetCountry()));
	}
}

bool CCfg::IsCountryMapInWorldMap( int MapId )
{
	for (std::vector<int>::iterator iter = m_CountryMapInWorldMap.begin(); iter != m_CountryMapInWorldMap.end(); ++iter)
	{
		if (*iter == MapId)
		{
			return true;
		}
	}
	return false;
}

NpcHeadModel* CCfg::GetHeadModelByHeight(float fHeight)
{
	NpcHeadModel* pResult = NULL;
	float fMin = 999999.0f;
	std::map<float,NpcHeadModel>::iterator it = m_NpcHeadModel.begin();
	for (;it != m_NpcHeadModel.end();++it)
	{
		float fDiff = it->second.fStature - fHeight;
		fDiff = abs(fDiff);
		if(fDiff < fMin)
		{
			fMin = fDiff;
			pResult = &it->second;
		}
	}

	return pResult;
}
