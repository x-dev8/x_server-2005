#include "globalvars.h"
#include "Me3d\global.h"
#include "official.h"
#include "Me3d/Engine/Engine.h"
#include "FuncPerformanceLog.h"

static int g_nGlobalTextures[GlobalTexture::eMaxTexture];
static int g_nMedalTextures[COfficialMgr::eMaxLevel];
static int g_nCountryTextures[country_max];
namespace GlobalTexture
{
	BOOL m_bLoaded = FALSE;
}
int	GlobalTexture::GetTexture( enumTexture id )
{
	guardfunc;
	return g_nGlobalTextures[id];
	unguard;
}
int GlobalTexture::GetMedalTexture( int nId )
{
	guardfunc;
	return g_nMedalTextures[nId];
	unguard;
}
int	GlobalTexture::GetCountryTexture( int nId )
{
	guardfunc;
	return g_nCountryTextures[nId];
	unguard;
}
BOOL GlobalTexture::UnLoad()
{
	guardfunc;
	ITextureManager* pMgr = GetEngine()->GetTextureManager();

	for( int i=0; i<GlobalTexture::eMaxTexture; i++ )
	{
		if( g_nGlobalTextures[i] != -1 )
			pMgr->UnRegisterTexture( g_nGlobalTextures[i] );
	}
	for( int i=0; i<COfficialMgr::eMaxLevel; i++ )
	{
		if( g_nMedalTextures[i] != -1 )
			pMgr->UnRegisterTexture( g_nMedalTextures[i] );
	}

	for( int i=0; i<country_max; i++ )
	{
		if( g_nCountryTextures[i] != -1 )
			pMgr->UnRegisterTexture( g_nCountryTextures[i] );
	}
	return TRUE;
	unguard;
}

static char* GetFullFileName(const char* filename)
{
	static char strFullName[MAX_PATH] = {0};
	sprintf(strFullName, "%s\\%s", GetRootPath(), filename);
	return strFullName;
}

BOOL GlobalTexture::LoadFromSlk( const char* pszFilename )
{
	guardfunc;
	
	ITextureManager* pMgr = GetEngine()->GetTextureManager();
	g_nGlobalTextures[eFootprint]	= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\Footprint.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eSmoke]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\Smoke.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eShadow]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\Shadow.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eHitFlash]	= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\HitFlash.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eElectric]	= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\LightingRed.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eRock]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\Barrenrock1.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eWaterCircle]	= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\WaterCircle.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eRedCircle]	= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\RedCircle.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eIce]			= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\IceBlock.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eAddExp]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\AddExp.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eAddBangGong]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\AddBangGong.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eAddMingWang]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\AddMingWang.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eAddGongXun]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\AddGongXun.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eAddAreaReputation] = pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\AddAreaReputation.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eAddRongYu]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\AddRongYu.dds"),  TRUE ,FALSE);

	g_nGlobalTextures[eMiss]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\Miss_1.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eDodge]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\Dodge.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eNumberRed]	= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\Number.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eNumber2]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\Number2.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eNumberGreen]	= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\BackAtt.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eDefence]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\Defence.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eResist]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\Resist.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eWard]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\Ward.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eCruelHit]	= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\CruelHit.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eDeathHit]	= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\DeathHit.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eBackAttck]	= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\AttackEffect\\BackAttck.dds"),  TRUE ,FALSE);

	g_nGlobalTextures[eRune]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Effect\\Rune.dds"),  TRUE ,FALSE);
	
	// quest
	g_nGlobalTextures[eYellowGanTanHao]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Quest\\YellowGanTanHao.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eWhiteGanTanHao]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Quest\\WhiteGanTanHao.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eYellowWenHao]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Quest\\YellowWenHao.dds"),  TRUE ,FALSE);
	g_nGlobalTextures[eWhiteWenHao]		= pMgr->RegisterTexture( GetFullFileName("Data\\TEXTURE\\Quest\\WhiteWenHao.dds"),  TRUE ,FALSE);

	g_nGlobalTextures[eBanner]		= pMgr->RegisterTexture( "data\\ui\\Map\\ZG_Banner.dds",  TRUE ,FALSE);

    g_nGlobalTextures[eNumber3]    = pMgr->RegisterTexture(GetFullFileName("Data\\TEXTURE\\AttackEffect\\Number3.dds"),TRUE,FALSE);
    g_nGlobalTextures[eNumber4]    = pMgr->RegisterTexture(GetFullFileName("Data\\TEXTURE\\AttackEffect\\Number4.dds"),TRUE,FALSE);
    g_nGlobalTextures[eAddSkillExp] = pMgr->RegisterTexture(GetFullFileName("Data\\TEXTURE\\Effect\\SkillExp.dds"),TRUE,FALSE);

	pMgr->RegisterTexture(GetFullFileName("Data\\Ui\\Common\\TipFrame.dds"),TRUE,FALSE);

	m_bLoaded = TRUE;
	
	return TRUE;
	unguard;
}