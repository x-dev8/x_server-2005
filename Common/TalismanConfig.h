#ifndef __TALISMAN_CONFIG_H__
#define __TALISMAN_CONFIG_H__

#pragma once

#include <string>
#include <vector>
#include <map>

#include "GlobalDef.h"
#include "GameDefineTalisman.h"

class TalismanConfig
{
public:
    enum ETalismanConstDefine
    {
        EPoolRandAttrMaxSize =    20,
    };

    struct STalismanEquipAttr
    {
        uint16  nTalismanID;
        uint8   nElement;
        uint8   nQuality;
        uint16  nRandAttr[SCharItem::EConstDefine_BaseRandMaxCount];
    };

    struct STalismanRandAttr
    {
        uint16  nRandID;
        uint8   nAttrType;
        uint32  nAttrValue;
        std::string strDesc;
    };

    struct SRandAttrPool
    {
        uint16  nPoolID     ;
        uint16  nRandAttr[EPoolRandAttrMaxSize] ;
    };

protected:
	TalismanConfig();

public:
	~TalismanConfig();

	inline static TalismanConfig& Instance()
	{
		static TalismanConfig s_xConfig;
		return s_xConfig;
	}

    uint8* GetTalismanQuality() { return _TalismanQuality; }
    uint8  GetRandAttrNumber (int quality) { return _TalismanAttrNumber[quality];  }
    void   InitTalismanEquipAttr( int itemId, int quality, int element, uint16* pBaseRand );
    void   InitTalismanRandAttr ( int poolId, uint16* pTalismanRand ); 

    int64  GetLevelExperience( int level ) ;

    STalismanRandAttr* GetTalismanRandAttr( int randId );

	bool   LoadTalismanConfig(const char* szFile);

private:
    uint8   _TalismanQuality    [ETalismanQuality_Count];
    uint8   _TalismanAttrNumber [ETalismanQuality_Count];
    int64   _TalismanExperiences[const_iCharMaxLevel];

    std::vector< STalismanEquipAttr >   vecTalismanEquipAttr;
    std::vector< STalismanRandAttr >    vecTalismanRandAttr ;
    std::vector< SRandAttrPool >        vecTalismanRandAttrPool;
};

#define theTalismanConfig TalismanConfig::Instance()   //ÊµÀý½Ó¿Ú

#endif

