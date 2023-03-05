#include "avatarsystemsetting.h"

#include "WordParser.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"
#include "core/Name.h"
#include "tstring.h"
#include "RapidXml\MeRapidXml.h"

static CAvatarSystemSetting* gs_pAvatarSystemSetting = NULL;
extern const char* GetRootPath();
CAvatarSystemSetting* GetAvatarSystemSetting()
{
    if( gs_pAvatarSystemSetting == NULL )
    {
        gs_pAvatarSystemSetting = new CAvatarSystemSetting;
    }
    return gs_pAvatarSystemSetting;
}

void DestroyAvatarSystemSetting()
{
    if( gs_pAvatarSystemSetting )
    {
        delete gs_pAvatarSystemSetting;
        gs_pAvatarSystemSetting = NULL;
    }
}
BYTE* CAvatarSystemSetting::GetSettingHairColor( int nColorId )
{
    static BYTE defSettingHairColorRGB[][3] =
    {
        220,15,20, //            红色:
        10,50,170, //              蓝色:
        40,180,190,//              青色:
        170,40,210,//              紫色:
        250,220,40,//              黄色:
        255,120,0, //              橙色:
        40,150,10, //              绿色:
        255,110,140,//            粉红色:
        130,150,155,//              灰色:
        0,100,255,    //            亮蓝色:
        0,90,60,    //            暗绿色:
        120,45,0,    //              棕色:
    };

    return defSettingHairColorRGB[nColorId];
}

CAvatarSystemSetting::CAvatarSystemSetting()
{
    m_defSettingSex.nCount = 2;
    m_defSettingSex.SItems[0].stItem = 0;
    strncpy_s(m_defSettingSex.SItems[0].strName, sizeof( m_defSettingSex.SItems[0].strName ), theXmlString.GetString(eClient_AddInfo_2slk_132), sizeof(m_defSettingSex.SItems[0].strName)-1);
    m_defSettingSex.SItems[1].stItem = 1;
    strncpy_s(m_defSettingSex.SItems[1].strName, sizeof( m_defSettingSex.SItems[1].strName ), theXmlString.GetString(eClient_AddInfo_2slk_133), sizeof(m_defSettingSex.SItems[1].strName)-1);

#ifdef _CLIENT_
    char strFilename[MAX_PATH] = {0};
    sprintf_s(strFilename, sizeof( strFilename ) - 1, "%s/Data/ClientConfig/GameSetting.config", GetRootPath());
    BOOL bOK = LoadXmlFile( strFilename );
#else
    BOOL bOK = LoadXmlFile( AVATARSYSTEMSETTING_FILEPATH );
#endif
    
    //// ToLog( bOK );
}

CAvatarSystemSetting::~CAvatarSystemSetting()
{
}

BOOL CAvatarSystemSetting::LoadXmlFile( const char* pszFilename )
{
    if ( pszFilename == NULL || *pszFilename == 0 )
    { return FALSE; }
    
    MeXmlDocument    doc;
    if( !doc.LoadFile(pszFilename) )
    {
        // ToLog(false && "CAvatarSystemSetting::LoadCfgFile 文件读取失败");
        return FALSE;
    }

//     MeXmlHandle        hDoc(&doc);
    const char* szValue = NULL;
    int nId = -1;
    std::wstring str;

#ifdef _CLIENT_
	MeXmlElement* pAvatarSetting = doc.FirstChildElement("Project")->FirstChildElement("AvatarSetting");
#else
	MeXmlElement* pAvatarSetting = doc.FirstChildElement("root");
#endif

	if (NULL == pAvatarSetting)
	{
		return FALSE;
	}
    // MaleDress
    MeXmlElement* pElem = pAvatarSetting->FirstChildElement("MaleDress")->FirstChildElement("Key");
    for( ; pElem; pElem = pElem->NextSiblingElement() )
    {
        pElem->QueryIntAttribute("ModelId", &nId);
        szValue = pElem->Attribute("ModelName");
        str = Common::_tstring::UTF8towcs(szValue);
        m_defSettingMaleDressId.AddItem((short)nId, Common::_tstring::toNarrowString(str.c_str()).c_str());
    }

    // MaleFace
    pElem = pAvatarSetting->FirstChildElement("MaleFace")->FirstChildElement("Key");
    for( ; pElem; pElem = pElem->NextSiblingElement() )
    {
        pElem->QueryIntAttribute("ModelId", &nId);
        szValue = pElem->Attribute("ModelName");
        str = Common::_tstring::UTF8towcs(szValue);
        m_defSettingMaleFaceId.AddItem((short)nId, Common::_tstring::toNarrowString(str.c_str()).c_str());
    }

    // MaleHair
    pElem = pAvatarSetting->FirstChildElement("MaleHair")->FirstChildElement("Key");
    for( ; pElem; pElem = pElem->NextSiblingElement() )
    {
        pElem->QueryIntAttribute("ModelId", &nId);
        szValue = pElem->Attribute("ModelName");
        str = Common::_tstring::UTF8towcs(szValue);
        m_defSettingMaleHairId.AddItem((short)nId, Common::_tstring::toNarrowString(str.c_str()).c_str());
    }

    // FemaleDress
    pElem = pAvatarSetting->FirstChildElement("FemaleDress")->FirstChildElement("Key");
    for( ; pElem; pElem = pElem->NextSiblingElement() )
    {
        pElem->QueryIntAttribute("ModelId", &nId);
        szValue = pElem->Attribute("ModelName");
        str = Common::_tstring::UTF8towcs(szValue);
        m_defSettingFemaleDressId.AddItem((short)nId, Common::_tstring::toNarrowString(str.c_str()).c_str());
    }

    // FemaleFace
    pElem = pAvatarSetting->FirstChildElement("FemaleFace")->FirstChildElement("Key");
    for( ; pElem; pElem = pElem->NextSiblingElement() )
    {
        pElem->QueryIntAttribute("ModelId", &nId);
        szValue = pElem->Attribute("ModelName");
        str = Common::_tstring::UTF8towcs(szValue);
        m_defSettingFemaleFaceId.AddItem((short)nId, Common::_tstring::toNarrowString(str.c_str()).c_str());
    }

    // FemaleHair
    pElem = pAvatarSetting->FirstChildElement("FemaleHair")->FirstChildElement("Key");
    for( ; pElem; pElem = pElem->NextSiblingElement() )
    {
        pElem->QueryIntAttribute("ModelId", &nId);
        szValue = pElem->Attribute("ModelName");
        str = Common::_tstring::UTF8towcs(szValue);
        m_defSettingFemaleHairId.AddItem((short)nId, Common::_tstring::toNarrowString(str.c_str()).c_str());
    }

    return TRUE;
}