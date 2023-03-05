#pragma once
#include <string>

/*
*	load/save dumper info to a xml file
*/

class DumpInfo
{
public:
	DumpInfo();
	~DumpInfo();

	bool SaveDumpInfo();
	bool LoadDumpInfo();
	void DeleteTempFile();
	bool CheckDumpTempFile();

public:
	// dump file name
	std::string m_strDumpFileName;

	// dump content, include device info, server
	// name, character name, client version
	std::string m_strContent;

	// custom system setting file name
	std::string m_strCustomSystemSettingFile;

	// custom game setting file name
	std::string m_strCustomGameSettingFile;
};