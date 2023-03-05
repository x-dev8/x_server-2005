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
	unsigned int Crc32Table[256];		//1.ÓÃÓÚCrc32µÄTable
};
#define theUnitManager UnitManager::Instance()