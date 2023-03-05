#ifndef __COMMON_DAOXINGCONFIG_H__
#define __COMMON_DAOXINGCONFIG_H__

#pragma once

#include <string>
#include <vector>
#include <map>

#include "GlobalDef.h"

#define DAOXING_QUOTIENT_LIMIT      1000    // 道行上限

class DaoxingConfig
{
public:
    struct SDaoxingEffect
    {
        uint16  nId;
        uint16  nBeginQuotient; 
        uint16  nEndQuotient  ;
        uint16  resist      [SNT_MaxCount];
        uint16  addTimePer  [SNT_MaxCount];
        
        SDaoxingEffect()  
        { memset(this,0,sizeof(SDaoxingEffect)); }
    };

protected:
    DaoxingConfig()  {};

public:
    ~DaoxingConfig() {};

    inline static DaoxingConfig& Instance()
    {
        static DaoxingConfig s_xConfig;
        return s_xConfig;
    }

    SDaoxingEffect* GetDaoxingEffect( unsigned short nQuotient );
    bool LoadDaoxingConfig(const char* szFile);

private:
    std::vector<SDaoxingEffect> vecDaoxingEffect;
    typedef std::vector<SDaoxingEffect>::iterator DaoxingIter;
};

#define theDaoxingConfig DaoxingConfig::Instance()   //实例接口

#endif