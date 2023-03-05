// MeQuestConvert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "QuestData.h"
#include "XmlStringLanguage.h"

#ifndef String_Ext
#define String_Ext ".string"
#endif
#ifndef Bin_String_Ext
#define Bin_String_Ext ".stringb"
#endif
#ifndef Quest_Ext
#define Quest_Ext ".quest"
#endif
#ifndef Bin_Quest_Ext
#define Bin_Quest_Ext ".questb"
#endif

#define SUBFOLDER	"Client"

// string文件转换成stringb
bool DeleteBinary(const char* szStringPath)
{
	if (szStringPath == NULL || *szStringPath == 0)
	{
		return false;
	}

	char szFile[_MAX_PATH + 1] = "";
	sprintf_s(szFile, sizeof(szFile) - 1, "%s\\%s\\*%s", szStringPath, SUBFOLDER, Bin_String_Ext);

	WIN32_FIND_DATA xFindData;         
	HANDLE hFile = FindFirstFile(szFile, &xFindData);   	
	if(hFile != INVALID_HANDLE_VALUE)
	{
		char szStringFile[_MAX_PATH + 1] = {0};
		do
		{
			sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%s\\%s\\%s", szStringPath, SUBFOLDER, xFindData.cFileName);
			::DeleteFile(szStringFile);

		}while(FindNextFile(hFile, &xFindData));                      
		FindClose(hFile);
	}

	sprintf_s(szFile, sizeof(szFile) - 1, "%s\\%s\\*%s", szStringPath, SUBFOLDER, Bin_Quest_Ext);

	hFile = FindFirstFile(szFile, &xFindData);   	
	if(hFile != INVALID_HANDLE_VALUE)
	{
		char szStringFile[_MAX_PATH + 1] = {0};
		do
		{
			sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%s\\%s\\%s", szStringPath, SUBFOLDER, xFindData.cFileName);
			::DeleteFile(szStringFile);

		}while(FindNextFile(hFile, &xFindData));                      
		FindClose(hFile);
	}

	char szMsg[_MAX_PATH+_MAX_PATH] = {0};
	sprintf_s(szMsg, sizeof(szMsg)-1, "\nFinish DeleteBinary!\n");
	printf(szMsg);

	return true;
}



// string文件转换成stringb
bool ConvertStringToBinary(const char* szStringPath, bool bNeedDelete)
{
	if (szStringPath == NULL || *szStringPath == 0)
	{
		return false;
	}

	char szFile[_MAX_PATH + 1] = "";
	sprintf_s(szFile, sizeof(szFile) - 1, "%s\\%s\\*%s", szStringPath, SUBFOLDER, String_Ext);


	int nCount = 0;
	char szMsg[_MAX_PATH+_MAX_PATH] = {0};
	WIN32_FIND_DATA xFindData;         
	HANDLE hFile = FindFirstFile(szFile, &xFindData);   	
	if(hFile != INVALID_HANDLE_VALUE)
	{
		char szStringFile[_MAX_PATH + 1] = {0};
		char szBinStringFile[_MAX_PATH + 1] = {0};
		do
		{
			sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%s\\%s\\%s", szStringPath, SUBFOLDER, xFindData.cFileName);

			bool bLoad = theXmlString.LoadStringFile(szStringFile, true, true, true); //加载
			if( bLoad )
			{
				char *p = strstr(szStringFile, String_Ext);
				if( p )
				{
					*p = 0;
					sprintf_s(szBinStringFile, sizeof(szBinStringFile)-1, "%s%s", szStringFile, Bin_String_Ext);
					bool bSave = theXmlString.SaveBinStringFile(szBinStringFile);
					if( !bSave )
					{
						sprintf_s(szMsg, sizeof(szMsg)-1, "\n[ERROR] SaveBinStringFile FAILED: %s\n", szBinStringFile);
						printf(szMsg);
					}
					else
					{
						++nCount;
						// 删除源数据文件
						if( bNeedDelete )
						{
							char szSourceFile[_MAX_PATH+1] = {0};
							sprintf_s(szSourceFile, sizeof(szSourceFile)-1, "%s\\%s\\%s", szStringPath, SUBFOLDER, xFindData.cFileName);
							::DeleteFile(szSourceFile);
						}

						sprintf_s(szMsg, sizeof(szMsg)-1, ".");
						printf(szMsg);
					}
				}
			}
			else
			{
				sprintf_s(szMsg, sizeof(szMsg)-1, "\n[ERROR] LoadStringFile FAILED: %s\n", szStringFile);
				printf(szMsg);
			}
		}while(FindNextFile(hFile, &xFindData));                      
		FindClose(hFile);
	}

	sprintf_s(szMsg, sizeof(szMsg)-1, "\nFinish converting %d strings!\n", nCount);
	printf(szMsg);

	return true;
}

// stringb文件转换成string
bool ConvertBinaryToString(const char* szStringPath, bool bNeedDelete)
{
	if (szStringPath == NULL || *szStringPath == 0)
	{
		return false;
	}

	char szFile[_MAX_PATH + 1] = "";
	sprintf_s(szFile, sizeof(szFile) - 1, "%s\\%s\\*%s", szStringPath, SUBFOLDER, Bin_String_Ext);


	int nCount = 0;
	char szMsg[_MAX_PATH+_MAX_PATH] = {0};
	WIN32_FIND_DATA xFindData;         
	HANDLE hFile = FindFirstFile(szFile, &xFindData);   	
	if(hFile != INVALID_HANDLE_VALUE)
	{
		char szStringFile[_MAX_PATH + 1] = {0};
		char szBinStringFile[_MAX_PATH + 1] = {0};
		do
		{
			sprintf_s(szBinStringFile, sizeof(szBinStringFile) - 1, "%s\\%s\\%s", szStringPath, SUBFOLDER, xFindData.cFileName);

			bool bLoad = theXmlString.LoadBinStringFile(szBinStringFile, true, true, true, false); //加载
			if( bLoad )
			{
				char *p = strstr(szBinStringFile, Bin_String_Ext);
				if( p )
				{
					*p = 0;
					sprintf_s(szStringFile, sizeof(szStringFile)-1, "%s%s", szBinStringFile, String_Ext);
					bool bSave = theXmlString.SaveStringFile(szStringFile);
					if( !bSave )
					{
						sprintf_s(szMsg, sizeof(szMsg)-1, "\n[ERROR] SaveStringFile FAILED: %s\n", szStringFile);
						printf(szMsg);
					}
					else
					{
						++nCount;
						// 删除源数据文件
						if( bNeedDelete )
						{
							char szSourceFile[_MAX_PATH+1] = {0};
							sprintf_s(szSourceFile, sizeof(szSourceFile)-1, "%s\\%s\\%s", szStringPath, SUBFOLDER, xFindData.cFileName);
							::DeleteFile(szSourceFile);
						}

						sprintf_s(szMsg, sizeof(szMsg)-1, ".");
						printf(szMsg);
					}
				}
			}
			else
			{
				sprintf_s(szMsg, sizeof(szMsg)-1, "\n[ERROR] LoadBinStringFile FAILED: %s\n", szBinStringFile);
				printf(szMsg);
			}
		}while(FindNextFile(hFile, &xFindData));                      
		FindClose(hFile);
	}

	sprintf_s(szMsg, sizeof(szMsg)-1, "\nFinish converting %d strings!\n", nCount);
	printf(szMsg);

	return true;
}

// quest文件转换成questb
bool ConvertQuestToBinary(const char* szFilePath, bool bNeedDelete)
{
	if (szFilePath == NULL || *szFilePath == 0)
	{
		return false;
	}

	char szMsg[_MAX_PATH+_MAX_PATH] = {0};
	if( !QuestInfo::Instance().LoadCommondData(szFilePath) )
	{
		sprintf_s(szMsg, sizeof(szMsg)-1, "Load common.quest failed!\n");
		printf(szMsg);
	}

	char szFile[_MAX_PATH + 1] = {0};
	sprintf_s(szFile, sizeof(szFile) - 1, "%s\\%s\\*%s", szFilePath, SUBFOLDER, Quest_Ext);

	char szQuestPath[_MAX_PATH + 1] = {0};
	sprintf_s(szQuestPath, sizeof(szQuestPath) - 1, "%s\\%s", szFilePath, SUBFOLDER);

	int nCount = 0;
	WIN32_FIND_DATA xFindData;         
	HANDLE hFile = FindFirstFile(szFile, &xFindData);   	
	if(hFile != INVALID_HANDLE_VALUE)
	{
		char szQuestFileNoExt[_MAX_PATH + 1] = {0};
		char szBinQuestFile[_MAX_PATH + 1] = {0};
		do
		{
			// 文件名去掉后缀
			strncpy(szQuestFileNoExt, xFindData.cFileName, sizeof(szQuestFileNoExt) - 1);
			char *p = strstr(szQuestFileNoExt, Quest_Ext);
			if( p )
				*p = 0;

			bool bLoad = QuestInfo::Instance().LoadOneQuest(szQuestPath, szQuestFileNoExt, true, false); //加载
			if( bLoad )
			{
				sprintf_s(szBinQuestFile, sizeof(szBinQuestFile)-1, "%s\\%s%s", szQuestPath, szQuestFileNoExt, Bin_Quest_Ext);
				bool bSave = QuestInfo::Instance().SaveBinQuest(szBinQuestFile);
				if( !bSave )
				{
					sprintf_s(szMsg, sizeof(szMsg)-1, "\n[ERROR] SaveBinQuest FAILED: %s\n", szBinQuestFile);
					printf(szMsg);
				}
				else
				{
					++nCount;
					// 删除源数据文件
					if( bNeedDelete )
					{
						char szSourceFile[_MAX_PATH+1] = {0};
						sprintf_s(szSourceFile, sizeof(szSourceFile)-1, "%s\\%s", szQuestPath, xFindData.cFileName);
						::DeleteFile(szSourceFile);
					}
					
					sprintf_s(szMsg, sizeof(szMsg)-1, ".");
					printf(szMsg);
				}
			}
			else
			{
				sprintf_s(szMsg, sizeof(szMsg)-1, "\n[ERROR] LoadOneQuest FAILED: %s\\%s%s\n", szQuestPath, szQuestFileNoExt, Quest_Ext);
				printf(szMsg);
			}
		}while(FindNextFile(hFile, &xFindData));                      
		FindClose(hFile);
	}

	sprintf_s(szMsg, sizeof(szMsg)-1, "\nFinish converting %d quests!\n", nCount);
	printf(szMsg);

	return true;
}

// questb文件转换成quest
bool ConvertBinaryToQuest(const char* szQuestPath, bool bNeedDelete)
{
	if (szQuestPath == NULL || *szQuestPath == 0)
	{
		return false;
	}

	char szMsg[_MAX_PATH+_MAX_PATH] = {0};
	if( !QuestInfo::Instance().LoadCommondData(szQuestPath) )
	{
		sprintf_s(szMsg, sizeof(szMsg)-1, "Load common.quest failed!\n");
		printf(szMsg);
	}

	char szFile[_MAX_PATH + 1] = {0};
	sprintf_s(szFile, sizeof(szFile) - 1, "%s\\%s\\*%s", szQuestPath, SUBFOLDER, Bin_Quest_Ext);


	int nCount = 0;
	WIN32_FIND_DATA xFindData;         
	HANDLE hFile = FindFirstFile(szFile, &xFindData);   	
	if(hFile != INVALID_HANDLE_VALUE)
	{
		char szQuestFileNoExt[_MAX_PATH + 1] = {0};
		char szQuestFile[_MAX_PATH+1] = {0};
		char szBinQuestFile[_MAX_PATH + 1] = {0};
		do
		{
			// 文件名去掉后缀
			strncpy(szQuestFileNoExt, xFindData.cFileName, sizeof(szQuestFileNoExt) - 1);
			char *p = strstr(szQuestFileNoExt, Bin_Quest_Ext);
			if( p )
				*p = 0;

			sprintf_s(szBinQuestFile, sizeof(szBinQuestFile)-1, "%s\\%s\\%s", szQuestPath, SUBFOLDER, xFindData.cFileName);

			bool bLoad = QuestInfo::Instance().LoadOneBinQuest(szBinQuestFile); //加载
			if( bLoad )
			{
				sprintf_s(szQuestFile, sizeof(szQuestFile)-1, "%s\\%s\\%s%s", szQuestPath, SUBFOLDER, szQuestFileNoExt, Quest_Ext);
				bool bSave = QuestInfo::Instance().SaveOneQuest(szQuestFile);
				if( !bSave )
				{
					sprintf_s(szMsg, sizeof(szMsg)-1, "\n[ERROR] SaveOneQuest FAILED: %s\n", szQuestFile);
					printf(szMsg);
				}
				else
				{
					++nCount;
					// 删除源数据文件
					if( bNeedDelete )
					{
						::DeleteFile(szBinQuestFile);
					}

					sprintf_s(szMsg, sizeof(szMsg)-1, ".");
					printf(szMsg);
				}
			}
			else
			{
				sprintf_s(szMsg, sizeof(szMsg)-1, "\n[ERROR] LoadOneBinQuest FAILED: %s\\%s\\%s%s\n", szBinQuestFile, SUBFOLDER, szQuestFileNoExt, Quest_Ext);
				printf(szMsg);
			}
		}while(FindNextFile(hFile, &xFindData));                      
		FindClose(hFile);
	}

	sprintf_s(szMsg, sizeof(szMsg)-1, "\nFinish converting %d quests!\n", nCount);
	printf(szMsg);

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 3 || strcmp(argv[1],"-d") != 0)
	{
		printf("MeQuestConverter.exe [-d directory] [-notdelete] [-reverse]\n");
		printf("Press any key to continue...\n");
		getchar();
		return -1;
	}

	bool bNeedDelete = true;	// 默认转换后删除原始数据
	bool bReverse = false;		// 默认从文本转成二进制
	if( argc > 3 )
	{
		if( 0 == stricmp(argv[3], "-notdelete" ))
			bNeedDelete = false;
		else if( 0 == stricmp(argv[3], "-reverse") )
		{
			bReverse = true;
		}

		if( argc > 4 )
		{
			if( 0 == stricmp(argv[4], "-notdelete" ))
				bNeedDelete = false;
			else if( 0 == stricmp(argv[4], "-reverse") )
			{
				bReverse = true;
			}
		}
	}

	// 文本 -> 二进制
	if( !bReverse )
	{
		//清除已有的二进制文件
		printf("MeQuestConverter Clear %s and %s ...\n", Bin_Quest_Ext, Bin_String_Ext);
		DeleteBinary(argv[2]);

		printf("MeQuestConverter Start Converting %s to %s...\n", String_Ext, Bin_String_Ext);

		ConvertStringToBinary(argv[2], bNeedDelete);

		printf("\nMeQuestConverter Start Converting %s to %s...\n", Quest_Ext, Bin_Quest_Ext);

		ConvertQuestToBinary(argv[2], bNeedDelete);
	}
	else	// 二进制 -> 文本，用于校验
	{
		printf("MeQuestConverter Start Converting %s to %s...\n", Bin_String_Ext, String_Ext);

		ConvertBinaryToString(argv[2], bNeedDelete);

		printf("\nMeQuestConverter Start Converting %s to %s...\n", Bin_Quest_Ext, Quest_Ext);

		ConvertBinaryToQuest(argv[2], bNeedDelete);
	}

	printf("MeQuestConverter Convert Finished!\n");
	printf("Press any key to continue...\n");
	getchar();

	return 0;
}

