#ifndef __COMMON_AVATARSYSTEMSETTING_H__
#define __COMMON_AVATARSYSTEMSETTING_H__

#pragma once

#include "MeRTLibs.h"
#include "Array.h"

#define theAvatarSystemSetting GetAvatarSystemSetting()

class CAvatarSystemSetting
{
public:
    enum
    {
        MAX_SELTIEM = 32
    };

    struct SDefSettingData
    {
        short    stItem;
        char    strName[128];
        SDefSettingData()
        {
            stItem     = 0;
            strName[0] = 0;
        }
    };

    struct SDefSetting
    {
        int                                 nCount;        
        Array<SDefSettingData, MAX_SELTIEM> SItems;

        SDefSetting(): SItems("[AvatarSystemSetting.h]CAvatarSystemSetting.SDefSetting.SItems")
        { nCount = 0; }

        BOOL AddItem( short stItem, const char* pszName )
        {
            if (nCount < 0 || nCount >= MAX_SELTIEM)
            {
                return FALSE;
            }
            SItems[nCount].stItem = stItem;
            memset( SItems[nCount].strName, 0, sizeof(SItems[nCount].strName) );
            strncpy_s(SItems[nCount].strName, sizeof( SItems[nCount].strName ), pszName, sizeof(SItems[nCount].strName)-1);
            nCount++;
            return TRUE;
        }
    };

public:
    CAvatarSystemSetting();
    ~CAvatarSystemSetting();

    BOOL    LoadXmlFile( const char* pszFilename );

    SDefSetting* GetSettingSex()          { return &m_defSettingSex;           }
    SDefSetting* GetSettingMaleDressId()  { return &m_defSettingMaleDressId;   }
    SDefSetting* GetSettingFemaleDressId(){ return &m_defSettingFemaleDressId; }
    SDefSetting* GetSettingMaleFaceId()   { return &m_defSettingMaleFaceId;    }
    SDefSetting* GetSettingFemaleFaceId() { return &m_defSettingFemaleFaceId;  }
    SDefSetting* GetSettingMaleHairId()   { return &m_defSettingMaleHairId;    }
    SDefSetting* GetSettingFemaleHairId() { return &m_defSettingFemaleHairId;  }
    BYTE*        GetSettingHairColor( int nColorId );

protected:
    SDefSetting m_defSettingSex;
    SDefSetting m_defSettingMaleHairId;
    SDefSetting m_defSettingMaleFaceId;
    SDefSetting m_defSettingMaleDressId;
    SDefSetting m_defSettingFemaleHairId;
    SDefSetting m_defSettingFemaleFaceId;
    SDefSetting m_defSettingFemaleDressId;
};

extern CAvatarSystemSetting* GetAvatarSystemSetting();
extern void DestroyAvatarSystemSetting();

#endif // __COMMON_AVATARSYSTEMSETTING_H__
