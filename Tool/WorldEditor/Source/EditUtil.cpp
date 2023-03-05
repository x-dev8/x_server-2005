/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	MapUtil.cpp
* Create: 	10/06/2006
* Desc:		定义地图通用数据结构和函数
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "EditUtil.h"
#include "Shlwapi.h"



bool GetGameWtdFileName( const char* pName, char* gameWtdPath )
{
	CStringA gameWtdFileName = SwGlobal::GetWorld()->GetAppDataCharDir();
	gameWtdFileName += "\\data\\";
	gameWtdFileName += "World";
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFile(gameWtdFileName,&data);
	bool bFind = (hFind != INVALID_HANDLE_VALUE);
	if (!bFind)
	{
		CreateDirectoryA(gameWtdFileName,NULL);
	}
	CStringA relName = pName;
	int npos = relName.Find('\\');
	while (npos != -1)
	{
		CStringA temp(gameWtdFileName);
		temp += "\\";
		temp += relName.Left(npos);
		hFind = FindFirstFile(temp,&data);
		bFind = (hFind != INVALID_HANDLE_VALUE);
		if (!bFind)
		{
			CreateDirectoryA(temp,NULL);
		}
		npos = relName.Find('\\',npos + 1);		
	}
	sprintf_s(gameWtdPath,MAX_PATH,"%s\\data\\World\\%s",SwGlobal::GetWorld()->GetAppDataCharDir(),pName);
	_strlwr(gameWtdPath);
	return true;
}
