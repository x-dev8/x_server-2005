#include <assert.h>
#include "slkreader.h"
#include "modelproj.h"
#include "SystemConfig.h"
#include "ItemDetail.h"
#include "Stdcharskeleton.h"
#include "FuncPerformanceLog.h"
#include "Common.h"

CModelProj* GetModelProjMgr()
{
	static CModelProj s_modelProj;
	return &s_modelProj;
}

std::string CModelProj::GetFileAddress( DWORD nEquipId, int nType, int nSex, int nProfession, int nColor )
{
	guardfunc;
	if( nProfession < 0 || nProfession > EArmType_MaxSize )
	{
		assert("Find Model:Profession Info is NULL");
		return "";
	}
	
	char szPath[MAX_PATH] = {0};
	char szFile[MAX_PATH] = {0};
	char szSex[MAX_PATH] = {0};
	char szFarthPath[MAX_PATH] = {0};
	switch( nSex )
	{
	case 0:
		strcpy( szSex, "male\0" );
		break;
	case 1:
		strcpy( szSex, "female\0");
		break;
	default:
		strcpy( szSex, "male\0" );
		break;
	}

	string szProfession = "";
	if( nProfession >= 0 && nProfession < EArmType_MaxSize )
		szProfession = files[nProfession];

	string szEquipType =  GetPartNames(nType);
	// added, jiayi, [2009/8/13]
	// 由于目录变更，而骨骼名没有变，所以这里加特殊处理
	// 虽然恶心，但很实用...
	
	/*
	 * 2012.6.2 wangshuai
	 * 修改Avatar的模型颜色分隔由0换为_, 如
	 * 原来是: FemaleHair280001.mex
	 * 现在是: FemaleHair2800_1.mex
	 */

	if( szEquipType == "RightHandItem" )
		szEquipType = "HandItem";
	if( nColor != -1 )
	{
		if( szEquipType == "HandItem")
		{
			MeSprintf_s( szFile,sizeof(szFile)/sizeof(char) - 1, "%s%s%d_%d\0", szSex, szEquipType.c_str(), nEquipId, nColor );
			MeSprintf_s( szFarthPath,sizeof(szFarthPath)/sizeof(char) - 1, "%s%s%d\0", szSex, szEquipType.c_str(), nEquipId);
		
		}
		else
		{
			MeSprintf_s( szFile,sizeof(szFile)/sizeof(char) - 1, "%s%s%d_%d\0", szSex, szEquipType.c_str(), nEquipId, nColor );
			MeSprintf_s( szFarthPath,sizeof(szFarthPath)/sizeof(char) - 1, "%s%s%d\0", szSex, szEquipType.c_str(), nEquipId);
		}
		MeSprintf_s( szPath,sizeof(szPath)/sizeof(char) - 1, "Data/Avatar/%s/%s/%s.mex", szEquipType.c_str(), szFarthPath, szFile );
	}
	else
	{
		if( nProfession == EArmType_MaxSize )
		{
			if( szEquipType == "HandItem")
			{
				MeSprintf_s( szFile,sizeof(szFile)/sizeof(char) - 1, "%s%s%d\0", szProfession.c_str(),szEquipType.c_str(), nEquipId );			
			}
			else
			{
				MeSprintf_s( szFile,sizeof(szFile)/sizeof(char) - 1, "%s%s%d\0", szProfession.c_str(),szEquipType.c_str(), nEquipId );
			}
			MeSprintf_s( szPath, sizeof(szPath)/sizeof(char) - 1,"Data/Avatar/%s/%s/%s.mex", szEquipType.c_str(), szFile, szFile );
			//OutputDebugString(szPath);
		}
		else
		{
			if( szEquipType == "HandItem")
			{
				MeSprintf_s( szFile,sizeof(szFile)/sizeof(char) - 1, "%s%s%d\0", szSex, szEquipType.c_str(), nEquipId );			
			}
			else
			{
				MeSprintf_s( szFile,sizeof(szFile)/sizeof(char) - 1, "%s%s%d\0", szSex, szEquipType.c_str(), nEquipId );
			}
			
			MeSprintf_s( szPath,sizeof(szPath)/sizeof(char) - 1,"Data/Avatar/%s/%s/%s.mex", szEquipType.c_str(), szFile, szFile );
		}
	}
	
	return szPath;
	unguard;
}

bool CModelProj::loadXMLSettings(XMLElement *element)
{

	return true;
}

bool CModelProj::exportXMLSettings(std::ofstream &xmlFile  )
{

	return true;
}


const char*	CModelProj::GetProfessionName( int nIdx )
{
	guardfunc;
	if( nIdx > EArmType_MaxSize )
		return NULL;
	return files[nIdx].c_str();
	unguard;
}

CModelProj::CModelProj(void)
:IOXMLObjectInstance("ModelProj"),
files("[ModelProj.h]CModelProj.files")
{
	int iRow = 2;

	std::string strTemp;
	std::string strProfessInfo;
	
	files[EArmType_Warrior]		= "Ji";
	files[EArmType_Mage]		= "Dao";
	files[EArmType_Taoist]		= "Qiang";
	files[EArmType_Assassin]    = "Jian";
    files[EArmType_Hunter]		= "Wu";
    //files[EArmType_Sniper]   = "Hammer";
}

CModelProj::~CModelProj(void)
{
}

CModelProj::Record* CModelProj::GetRecord( int nModelId )
{
	return NULL;
}
