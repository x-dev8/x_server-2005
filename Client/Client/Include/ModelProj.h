#pragma once
#include <windows.h>
#include "IOXMLObject.h"
#include "GlobalDef.h"
#include "GlobalDef.h"
#include <string>
#include <vector>

#include "Array.h"

class CModelProj:public IOXMLObjectInstance
{
public:
	
public:
	//
	virtual bool loadXMLSettings(XMLElement *element);
	virtual bool exportXMLSettings(std::ofstream &xmlFile  );
	std::string	 GetFileAddress( DWORD nEquipId, int nType, int nSex, int nProfession, int nColor = -1 );
public:
	struct Record
	{
		Record() : files("[ModeProj.h]CModelProj.Record.files")
		{
		}
		DWORD dwId;
		//std::string files[EArmType_MaxSize][2];
		Array< Array<std::string, 2>, EArmType_MaxSize>	files;// zizi add
		std::string strDropGroundFilename;
	};
public:
	CModelProj(void);
	~CModelProj(void);
	Record* GetRecord( int nModelId );
	const char*	GetProfessionName( int nIdx );
protected:
	//std::vector<Record> m_records;
	//std::string files[EArmType_MaxSize];
	Array<std::string, EArmType_MaxSize>	files;//zizi add
};
extern CModelProj* GetModelProjMgr();