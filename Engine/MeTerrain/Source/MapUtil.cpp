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
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/MapUtil.h"
#include "Shlwapi.h"


bool GetRelativePathToWorldPath( LPCTSTR fullPath, char* texPath )
{
// 	CString fileName( fullPath );
// 	fileName.MakeLower();
// 	CPathA workPath;
// 	path.Format(_T("%hs"),SwGlobal::GetWorld()->GetWorldPath());
	PathRelativePathTo(texPath,SwGlobal::GetWorld()->GetWorldPath(),FILE_ATTRIBUTE_DIRECTORY,fullPath,FILE_ATTRIBUTE_NORMAL);
// 	workPath.RelativePathTo(path,FILE_ATTRIBUTE_DIRECTORY,fileName,FILE_ATTRIBUTE_NORMAL);

	//CString path(texPath);
	//path = path.Mid( 2);	// 将 '.\'或'./' 去掉
	char path[MAX_PATH];
	strcpy(path, texPath+2);
	
	if( SwPublicFunc::TChar2MutiChar( texPath, MAX_PATH*2*sizeof(char), path, (/*path.GetLength()*/strlen(path)+1)*sizeof(char/*TCHAR*/) ) )
		return false;

	return true;

}


bool SpliteFullPathToDataPath( LPCTSTR fullPath, char* worldPath, char* worldName )
{
// 	CString fileName( fullPath );
// 	fileName.MakeLower();
// 	CPathA workPath;
// 	CString appDataDir(CWorld::GetAppDataCharDir());
// 	workPath.RelativePathTo(appDataDir,FILE_ATTRIBUTE_DIRECTORY,fileName,FILE_ATTRIBUTE_NORMAL);
	PathRelativePathTo(worldPath,CWorld::GetAppDataCharDir(),FILE_ATTRIBUTE_DIRECTORY,fullPath,FILE_ATTRIBUTE_NORMAL);

	//CString path(worldPath);
	//CString subDir	= path.Mid( 2);	// 将 '.\'或'./' 去掉
	//CString strName;	
	//sInt32 len				= subDir.GetLength();
	//sInt32 pos				= subDir.ReverseFind( _T('\\') );
	//CString workPathName		= subDir.Left( pos );
	//strName			= subDir.Right( len-pos-1 );

	//if( SwPublicFunc::TChar2MutiChar( worldPath, MAX_PATH*2*sizeof(char), workPathName, (workPathName.GetLength()+1)*sizeof(TCHAR) ) )
	//	return false;
	//if( SwPublicFunc::TChar2MutiChar( worldName, MAX_PATH*2*sizeof(char), strName, (strName.GetLength()+1)*sizeof(TCHAR) ) )
	//	return false;

	char path[MAX_PATH];
	char subDir[MAX_PATH];
	char workPathName[MAX_PATH];
	char strName[MAX_PATH];
	strcpy(path, worldPath);
	strcpy(subDir, path+2);
	int len = strlen(subDir);
	strcpy(workPathName, subDir);
	char *p = strrchr(workPathName, '\\');
	if( p )
	{
		strcpy(strName, p+1);
		*p = 0;
	}
	else
		strcpy(strName, workPathName);
	if( SwPublicFunc::TChar2MutiChar( worldPath, MAX_PATH*2*sizeof(char), workPathName, (strlen(workPathName)+1)*sizeof(char) ) )
		return false;
	if( SwPublicFunc::TChar2MutiChar( worldName, MAX_PATH*2*sizeof(char), strName, (strlen(strName)+1)*sizeof(char) ) )
		return false;


	return true;
}

void RomovePostfix(char* name)
{
	//CStringA withoutPostfix(name);
	//sInt32 pos				= withoutPostfix.Find(".");
	//if( -1 != pos )
	//	withoutPostfix		= withoutPostfix.Left( pos );
	char withoutPostfix[MAX_PATH];
	strcpy(withoutPostfix, name);
	char *p = strchr(withoutPostfix, '.');
	if( p )
		*p = 0;
#if _MSC_VER >= 1400
	sprintf_s(name,MAX_PATH,"%s",withoutPostfix/*.GetString()*/);
#else
	sprintf(name,"%s",withoutPostfix/*.GetString()*/);
#endif
}

bool SpliteFullPathToDataPathWithoutPostfix( LPCTSTR fullPath, char* worldPath, char* worldName)
{
	if (!SpliteFullPathToDataPath(fullPath,worldPath,worldName))
	{
		return false;
	}
	RomovePostfix(worldName);
	return true;

}


bool GetRelativePathToWorldPathWithoutPostfix( LPCTSTR fullPath, char* texPath )
{
	if (GetRelativePathToWorldPath(fullPath,texPath))
	{
		RomovePostfix(texPath);
		return true;
	}
	return false;

}


void GetChunkIdFromPos(  sInt32* chunk, flt32* pos )
{
	for( sInt32 i=0;i<2;i++ ) {
		chunk[i]	= ChunkFromPos( pos[i] );
		if (chunk[i] < 0)
		{
			chunk[i] = 0;
		}
		if (chunk[i] >= CURRENTTILE->GetRowColumn()[i])
		{
			chunk[i] = CURRENTTILE->GetRowColumn()[i] - 1;
		}
	}
}

bool EnumFile( LPCTSTR fullPath,swFileOperation opt,void* point,bool isRecursive )
{
	//CString strPath( fullPath );
	//strPath += _T("\\*.*");
	char strPath[MAX_PATH];
	sprintf(strPath, "%s\\*.*", fullPath);
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(strPath,&data);
	bool bFind = (hFind != INVALID_HANDLE_VALUE);

	while (bFind)
	{
		sprintf(strPath, "%s\\%s", fullPath, data.cFileName);
		//strPath.Format(_T("%s\\%s"),fullPath,data.cFileName);
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			//if (strPath.ReverseFind(_T('.')) !=  strPath.GetLength() - 1)
			char *p = strrchr(strPath,'.');
			int len = strlen(strPath);
			if( !p || (p && *p != strPath[len-1] ))
			{
				if (isRecursive)
				{
					EnumFile(strPath,opt,point,isRecursive);
				}
			}
		}
		else 
		{
			opt(strPath,point);
		}
		bFind = FindNextFile(hFind,&data);
	}
	FindClose(hFind);
	return true;
}

COLORREF g_defaultLiquidColor = 0xFF001964;// NiColor(0.0, 0.1, 0.4);

flt32 GetAtan( Vector2 &tex )
{
	flt32 Atan = 0.f;
	if (abs(tex.x) < 0.00001)
	{
		if (tex.y > 0)
		{
			Atan = PI/2.f;
		}
		else
		{
			Atan = -PI/2.f;
		}
	}
	else
	{
		if (tex.x > 0.f)
		{
			Atan = atan(tex.y/tex.x);
		}
		else
		{
			Atan = atan(tex.y/tex.x) + PI;
		}
	}
	return Atan;
}


