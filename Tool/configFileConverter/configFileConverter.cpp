// configFileConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SlkReader.h"
#include "ConverterManager.h"
#include "DataDef.h"
#include <map>
#include <list>


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Ws2_32.lib") 
#pragma comment(lib, "shlwapi.lib")


int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _DEBUG	
	system("pause");
#endif
	/*theItemHero.LoadHeroConfig("SanGuoLord.config");
	return 0;*/
workthread:
	printf("please choose slk to convert!\n");	
	printf("0,exit\n");
	printf("1,xinfa.slk\n");
	printf("2,Daoxing.slk\n");
	printf("3,CharacterBaseSecondAttribute.slk\n");
	printf("4,SanGuoLord.slk\n");
	string change = "";
	std::cin>>change;
	//printf("%s\n",change);
	
	//..//data//config//xinfo.slk
    //C:\Documents and Settings\t036\×ÀÃæ
	std::list<TString> fileNames;
	TString converterName = _T("xinfaConverter");

	//parse the input parameters	
	
	if(1 == argc)
	{
		
		if (change == "1")
		{
			TString address = _T("XinFa.slk");
			fileNames.push_back(address);
		}
		else if(change == "2")
		{	
			TString address = _T("Daoxing.slk");
			fileNames.push_back(address);
		}
		else if (change == "4")
		{
			TString address = _T("SanGuoLord.slk");
			fileNames.push_back(address);
		}
		else if (change == "0")
		{

			return 0;
		}
		else
		{
			TString address = _T("CharacterBaseSecondAttribute.slk");
			fileNames.push_back(address);
		}
	}
	else if(argc > 1)
	{
		for(int i = 1; i < argc; ++i)
		if(argv[i] != NULL && _tcslen(argv[i]) > 0)
		{
			fileNames.push_back(TString(argv[i]));
		}
	}

	CConverterManager converterMgr;
	for(std::list<TString>::iterator it = fileNames.begin(); it != fileNames.end(); ++it)
	{
		converterMgr.AddFile(it->c_str(), converterName.c_str());
	}
	
	converterMgr.Convert();

	system("pause");

	goto workthread;


	return 0;
}

