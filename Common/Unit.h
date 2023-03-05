#pragma once
#include "Singleton.h"
class UnitManager : public ISingletion<UnitManager>
{ 
public:
	UnitManager();
	virtual ~UnitManager();
public:
	unsigned int Crc32(std::string& str);
private:
	void CreateCrc32Table();
private:
	unsigned int Crc32Table[256];		//1.����Crc32��Table
};
#define theUnitManager UnitManager::Instance()