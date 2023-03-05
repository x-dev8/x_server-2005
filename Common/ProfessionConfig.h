#ifndef __PROFESSION_CONFIG_H__
#define __PROFESSION_CONFIG_H__

#pragma once

#include <string>
#include <vector>
#include <map>

#include "GlobalDef.h"

class ProfessionConfig
{
public:
    enum EProfessionConstDefine
    {
        EProfession_MaxNumLimit =	 255,		//职业数量上限
    };

public:
	struct Profession
	{
		uint8	nID;            // 职业ID
		uint8	nLevel;         // 职业阶段
		std::string	strName;    // 名称
		uint8	nPrevID;        // 前置职业

		Profession()
			: strName("")
		{
			nID = 0;
			nLevel = 0;
			nPrevID = 0;
		}

		Profession(const Profession& xProfession)
		{
			*this = xProfession;
		}

		Profession& operator = (const Profession& xProfession)
		{
			if (this != &xProfession)
			{
				nID = xProfession.nID;
				nLevel = xProfession.nLevel;
				strName = xProfession.strName;
				nPrevID = xProfession.nPrevID;
			}

			return *this;
		}

		bool operator == (const uint8 Id) { return (this->nID == Id); }

		uint8	GetID() const	{ return nID; }
		uint8 GetLevel() const	{ return nLevel; }
		std::string GetName() const	{ return strName; }
		uint8 GetPrevID() const	{ return nPrevID; }
	};

protected:
	ProfessionConfig();

public:
	~ProfessionConfig();

	inline static ProfessionConfig& Instance()
	{
		static ProfessionConfig s_xConfig;
		return s_xConfig;
	}

	bool LoadProfessionConfig(const char* szFile);

	Profession*  GetProfession  ( uint8 nId ) 
	{
		if ( nId >= EProfession_MaxNumLimit)
		{ return NULL; }

		Profession xProfession = m_vecProfession[nId];

		if ( xProfession.GetID() == InvalidLogicNumber )
		{ return NULL; }

		return &m_vecProfession[nId];
	}

	const std::vector<Profession>& GetProfessionList() const{ return m_vecProfession; }

private:
	std::vector<Profession>    m_vecProfession;

public:
	typedef std::vector<Profession>::iterator  ProfessionIter ;
};

#define theProfessionConfig ProfessionConfig::Instance()   //实例接口

#endif

