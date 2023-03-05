//#include "MeTerrain/stdafx.h"	
#include "SortLuaScript.h"
#include "LuaFuns.h"

#include "ErrorLog.h"
#include <io.h>
#include <direct.h>
#include "FuncPerformanceLog.h"
//#include "Shlwapi.h"
LuaScript		g_ScriptSet[MAX_SCRIPT_IN_SET];
CScriptMap		g_ScriptMap;
unsigned int	nCurrentScriptNum;
char			g_szCurScriptDir[MAX_PATH] = {0};

DWORD g_FileName2Id(LPSTR lpFileName)
{
	guardfunc;
	DWORD Id = 0;
	char c = 0;
	for (int i = 0; lpFileName[i]; i++)
	{
		c = lpFileName[i];
#ifndef WIN32
		//for linux path looking up
		if ('/' == c)
			c = '\\';
#endif
		Id = (Id + (i + 1) * c) % 0x8000000b * 0xffffffef;
	}
	return (Id ^ 0x12345678);
	unguard;
}

void	LoadScriptInDirectory(LPSTR lpszRootDir, LPSTR lpszSubDir);

int	operator<(CSortScriptNode ScriptLeft, CSortScriptNode ScriptRight)
{
	return ScriptLeft.GetScriptID() < ScriptRight.GetScriptID();
};

int operator==(CSortScriptNode ScriptLeft, CSortScriptNode ScriptRight)
{
	return ScriptLeft.GetScriptID() == ScriptRight.GetScriptID();
};

//将szFilePath目录下的所有脚本文件加载进ScriptBinTree二叉树中
static unsigned long LoadAllScript(char * szFilePath)
{
	guardfunc;
	char szRootPath[100];
	char szOldRootPath[MAX_PATH] = {0};

	getcwd(szOldRootPath, MAX_PATH);
	strcpy( szRootPath,  szFilePath );
	LoadScriptInDirectory(szRootPath, "");
	chdir(szOldRootPath);

	return nCurrentScriptNum;
	unguard;
}

unsigned long g_IniScriptEngine( std::string szPath )
{
	guardfunc;
	g_szCurScriptDir[0] = 0;
	nCurrentScriptNum = 0;
	g_ScriptMap.clear();
	return LoadAllScript( (char*)szPath.c_str() );
	unguard;
}



const IScript * g_GetScript(DWORD dwScriptId)
{
	guardfunc;
	CScriptMap::iterator it;
	CSortScriptNode ScriptNode;
	ScriptNode.SetScriptID(dwScriptId);
	const DWORD dw = ScriptNode.GetScriptID();
	for( it=g_ScriptMap.begin(); it!=g_ScriptMap.end(); it++ )
	{
		if( it->first == dw )
		{
			ScriptNode = it->second;
			return ScriptNode.GetScript();		
		}
	}
	//for(int i=0;i<g_ScriptMap.size(); i++
	//it = g_ScriptMap.find( dw );
	//if ( it == g_ScriptMap.end() )
	//{
	//	return 0;
	//}
	return NULL;
	unguard;
}

const IScript * g_GetScript(const char * szRelativeScriptFile)
{
	guardfunc;
	DWORD dwScriptId = g_FileName2Id((LPSTR)szRelativeScriptFile);
	return g_GetScript(dwScriptId);
	unguard;
}

extern int LuaIncludeFile(lua_State * L);

//加载脚本，该文件名参数为相对目录
static BOOL LoadScriptToSortListA(char * szRelativeFile)
{
	guardfunc;
	if (!szRelativeFile || !szRelativeFile[0]) 
		return FALSE;
	CSortScriptNode ScriptNode ;
	ScriptNode.SetScriptID(g_FileName2Id(szRelativeFile));
	int t  =strlen(szRelativeFile);
	if (t >= 90)
		t ++;

#ifdef _DEBUG
	//strcpy(ScriptNode.m_szScriptName, szRelativeFile);
#endif
	if (nCurrentScriptNum < MAX_SCRIPT_IN_SET)
	{
		g_ScriptSet[nCurrentScriptNum].Init();
		g_ScriptSet[nCurrentScriptNum].RegisterFunctions(GNativeFun, g_GetNativeFunNum());
		memset( g_ScriptSet[nCurrentScriptNum].m_szScriptName, 0,
				sizeof(g_ScriptSet[nCurrentScriptNum].m_szScriptName) );
		strncpy(g_ScriptSet[nCurrentScriptNum].m_szScriptName,
				szRelativeFile,
				sizeof(g_ScriptSet[nCurrentScriptNum].m_szScriptName)-1 );
		if (!g_ScriptSet[nCurrentScriptNum].Load(szRelativeFile))
		{

		}
		else
		{
			GetErrorLog()->logString("[脚本]加载脚本%s，出错，该脚本无法加载！！请检查！！", szRelativeFile);
			return FALSE;
		}
	}
	else
	{
		GetErrorLog()->logString("[脚本]严重错误!脚本数量超限制%d！请立即解决！！", MAX_SCRIPT_IN_SET);
		return FALSE;
	}

	ScriptNode.SetScriptIndex(nCurrentScriptNum++);
	g_ScriptMap.insert(CScriptMap::value_type(ScriptNode.GetScriptID(), ScriptNode));
	return TRUE;
	unguard;
}

//加载脚本，该文件名参数为实际目录
static BOOL LoadScriptToSortList(char * szFileName)
{
	guardfunc;
	if (!szFileName || !szFileName[0]) return FALSE;
	if (nCurrentScriptNum>= MAX_SCRIPT_IN_SET)
	{
		GetErrorLog()->logString("[Script]脚本总容量超过%d,严重错误请检查!",MAX_SCRIPT_IN_SET);
		return FALSE;
	}
	int nFileNameLen = strlen(szFileName);
	char szRelativeFile[MAX_PATH] = {0};
	sprintf(szRelativeFile, "%s", szFileName);
	return LoadScriptToSortListA(szRelativeFile);
	unguard;
	//	return FALSE;
}


void	LoadScriptInDirectory(LPSTR lpszRootDir, LPSTR lpszSubDir)
{
	guardfunc;
	int				nFlag;
	char			szRealDir[MAX_PATH] = {0};
#ifdef WIN32
	sprintf(szRealDir, "%s\\%s", lpszRootDir, lpszSubDir);
#else
	sprintf(szRealDir, "%s/%s", lpszRootDir, lpszSubDir);
	char *ptr = szRealDir;
	while(*ptr) { if(*ptr == '\\') *ptr = '/';  ptr++;  }
#endif

#ifdef WIN32
	if(chdir(szRealDir)) return;
	_finddata_t FindData;
	long dir = _findfirst("*.*", &FindData);
	while(dir != -1) {
		if(strcmp(FindData.name, ".") == 0 || strcmp(FindData.name, "..") == 0)	{
			if(_findnext(dir, &FindData)) break;
			continue;
		}
		if(FindData.attrib == _A_SUBDIR)
		{
			LoadScriptInDirectory(szRealDir, FindData.name);
		}
		else
		{	
			nFlag = 0;
			for (int i = 0; i < (int)strlen(FindData.name);  i++)
			{
				if (FindData.name[i] == '.')
					break;
				if (FindData.name[i] == '\\')
				{
					nFlag = 1;
					break;
				}
			}
			if (nFlag == 1)
			{
				LoadScriptInDirectory(szRealDir, FindData.name);
			}
			else
			{
				char szExt[50];
				if (strlen(FindData.name) >= 4) 
				{
					strcpy(szExt, FindData.name + strlen(FindData.name) - 4);
					_strupr(szExt);
					if ( (!strcmp(szExt, ".LUA")) /*|| (!strcmp(szExt, ".TXT"))*/)
						if (!LoadScriptToSortList(FindData.name))
						{
							GetErrorLog()->logString("加载%s文件出错", FindData.name);
						}
							
				}
			}
		}
		if(_findnext(dir, &FindData)) break;
	} 
	_findclose(dir);
	chdir(lpszRootDir);
#else
	DIR *dp;
	int i;
	struct dirent *ep;
	if(chdir(szRealDir)) return;
	dp = opendir(".");
	if(dp) {
		while(ep = readdir(dp)) {
			if(strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0) continue;

			if(ep->d_type ==4) {
				LoadScriptInDirectory(szRealDir, ep->d_name);
			}
			else {
				nFlag = 0;
				for (i = 0; i < (int)strlen(ep->d_name);  i++)
				{
					if (ep->d_name[i] == '.')
						break;
					if (ep->d_name[i] == '\\')
					{
						nFlag = 1;
						break;
					}
				}
				if (nFlag == 1)
				{
					LoadScriptInDirectory(szRealDir,ep->d_name);
				}
				else
				{
					char szExt[50];
					if (strlen(ep->d_name) >= 4)
					{
						strcpy(szExt, ep->d_name + strlen(ep->d_name) - 4);
						g_StrUpper(szExt);
						///					_strupr(szExt);
						if ( (!strcmp(szExt, ".LUA")) || (!strcmp(szExt, ".TXT")))
							if (!LoadScriptToSortList(ep->d_name))
								GetErrorLog()->logString("加载%s文件出错", ep->d_name);
					}
				}
			}
		}
		closedir(dp);
	}
	chdir(lpszRootDir);
#endif
	unguard;
}

void UnLoadScript(DWORD dwScriptID)
{
	guardfunc;
	CSortScriptNode ScriptNode;
	ScriptNode.SetScriptID(dwScriptID);
	g_ScriptMap.erase(ScriptNode.GetScriptID());
	unguard;
}

BOOL ReLoadScript(const char * szRelativePathScript)
{
	guardfunc;
	if (!szRelativePathScript || !szRelativePathScript[0])
		return FALSE;
	char script[MAX_PATH] = {0};
	strcpy(script, szRelativePathScript);
	_strlwr(script);
	//g_StrLower(script);
	UnLoadScript(g_FileName2Id(script));
	return LoadScriptToSortListA(script);
	unguard;
}
//
//unsigned long  ReLoadAllScript()
//{
//	g_ScriptMap.clear();
//	return g_IniScriptEngine();
//}