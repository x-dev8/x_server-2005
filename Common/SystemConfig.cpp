#include "Systemconfig.h"
#include "Logger.h"
#include "MediaPathManager.h"
#include "FuncPerformanceLog.h"
#include "ResourcePath.h"
#include "tstring.h"
CSystemConfig* GetSystemConfig()
{
    //	static BOOL b = FALSE;
    static CSystemConfig gs_Config;
    //	if( !b )
    //	{
    //		InitVFS();
    //		b = TRUE;
    //	}


    //	Logger::initialize("LogXml.config");
    return &gs_Config;
}

CSystemConfig::CSystemConfig(void)
:IOXMLObjectInstance("Project")
{
    m_fSelectUIRoleScale = 1.0f;

    m_vtPackType.push_back("Model");
    m_vtPackType.push_back("Slk");
    m_vtPackType.push_back("Textures");
    m_vtPackType.push_back("UI");
    m_vtPackType.push_back("World");
    m_vtPackType.push_back("Music");
    m_vtPackType.push_back("Sound");
    m_vtPackType.push_back("Effect");
    m_vtPackType.push_back("Cfg");


    m_dwWhite	= 0xFFFFFFFF;
    m_dwGrayed	= 0x7f7f7f7f;
    m_dwBlue	= 0xFF0000FF;
    m_dwGreen	= 0xFF008000;
    m_dwGold	= 0xFFA6A600;
    m_dwYellow	= 0xFF008000;
    m_dwRed		= 0xFFFF0000;
    m_dwPurple = 0xFF800080;


    memset(&m_PackRoleLight, 0, sizeof(m_PackRoleLight));
    m_PackRoleLight.Type        = D3DLIGHT_DIRECTIONAL;
    m_PackRoleLight.Diffuse.r   = 1.0f;
    m_PackRoleLight.Diffuse.g   = 1.0f;
    m_PackRoleLight.Diffuse.b   = 1.0f;
    D3DXVec3Normalize( (D3DXVECTOR3*)&m_PackRoleLight.Direction, &D3DXVECTOR3(-1, 1, 2) );
    m_PackRoleLight.Position.x   = -1;
    m_PackRoleLight.Position.y   = 1;
    m_PackRoleLight.Position.z   = 2;
    m_PackRoleLight.Range        = 1000.0f;


    m_PackRoleLight.Diffuse.a =1.0f;
    m_PackRoleLight.Diffuse.r =0.3f;
    m_PackRoleLight.Diffuse.g =0.3f;
    m_PackRoleLight.Diffuse.b =0.3f;

    m_PackRoleLight.Ambient.r = 0.2f;
    m_PackRoleLight.Ambient.g = 0.2f;
    m_PackRoleLight.Ambient.b = 0.2f;

    m_PackRoleLight.Specular.r = 1.0f;
    m_PackRoleLight.Specular.g = 1.0f;
    m_PackRoleLight.Specular.b = 1.0f;
    m_PackRoleLight.Specular.a = 1.0f;

    //g_GameSun.Direction.z = -g_GameSun.Direction.z;
    D3DXVec3Normalize( (D3DXVECTOR3*)&m_PackRoleLight.Direction, (D3DXVECTOR3*)&m_PackRoleLight.Direction );
    m_PackRoleLight.Direction = (-1)*m_PackRoleLight.Direction;


    //m_bLinkPage = FALSE;

#ifdef _CLIENT_
    IOXMLObjectInstance::loadXMLSettings( "..\\Data\\ClientConfig\\GameSetting.config" );
#else
    // IOXMLObjectInstance::loadXMLSettings( SYSTEMCONFIG_FILEPATH );
#endif
}


CSystemConfig::~CSystemConfig(void)
{
    //	Logger::flush();
}

bool CSystemConfig::loadXMLSettings(const char *path  )
{
    //if( )
    return true;
}

CProfessionInfo* CSystemConfig::GetProessionInfoFromID(int nID )
{
    for( int i = 0; i < m_vtProfession.size(); i++ )
    {
        if( m_vtProfession[i].nID == nID )
            return &m_vtProfession[i];
    }
    return NULL;
}

int CSystemConfig::GetProfessionCount()
{
    return m_vtProfession.size();
}

bool CSystemConfig::loadXMLSettings(XMLElement *element)
{
    //	LOGINFO("CSystemConfig::loadXMLSettings");
    if(!isSuitable(element))
        return false;

    element = element->getChildByName("SystemConfig");
    XMLElement  *child   = NULL;
    XMLElement  *xmlValues   = NULL;
    bool         success = false;

    // 	for(size_t i = 0; i < element->getChildrenCount(); i++)
    // 	{
    // 		child = element->getChild(i);
    // 
    // 		if(child->getName() == "MediaFolder")
    // 		{
    // 			MediaPathManager::registerPath(child);
    // 			continue;
    // 		}
    // 	}

    //for(size_t i = 0; i < element->getChildrenCount(); i++)
    //{
    //	child = element->getChild(i);

    //	if(child->getName() == "PackCfg")
    //	{
    //		CPackConfig cfg;
    //		XMLElement* pElement = child->getChildByName("Type");
    //		if( pElement )
    //		{
    //			for( int i=0; i<eMaxPack; i++ )
    //			{
    //				if( pElement->getValue() == m_vtPackType[i] )
    //					cfg.nPackType = i;
    //			}				
    //		}
    //		pElement = child->getChildByName("Number");
    //		if( pElement )
    //		{
    //			cfg.nPackCnt = pElement->getValuei();
    //		}
    //		m_vtPackConfig.push_back(  cfg );
    //	//	MediaPathManager::registerPath(child);
    //		continue;
    //	}
    //}

    ////////////////////////////////////////////////////////////////////////////
    ////
    //child = element->getChildByName( "Windows" );
    //if( child )
    //{	
    //	XMLElement* pElement = child->getChildByName("title");
    //	if( pElement )
    //	{
    //		m_WindowsConifg.m_strCaption = pElement->getValue();
    //	}
    //	pElement = child->getChildByName("isFull");
    //	if( pElement )
    //	{
    //		m_WindowsConifg.bFullSrceen = ( pElement->getValue() == "true" ) ? true : false;
    //	}
    //	pElement = child->getChildByName("x");
    //	if( pElement ) 
    //	{
    //		m_WindowsConifg.nPosX = pElement->getValuei();
    //	}
    //	pElement = child->getChildByName("y");
    //	if( pElement ) 
    //	{
    //		m_WindowsConifg.nPosY = pElement->getValuei();
    //	}
    //	pElement = child->getChildByName("width");
    //	if( pElement ) 
    //	{
    //		m_WindowsConifg.nPosY = pElement->getValuei();
    //	}
    //	pElement = child->getChildByName("height");
    //	if( pElement ) 
    //	{
    //		m_WindowsConifg.nPosY = pElement->getValuei();
    //	}
    //	pElement = child->getChildByName("openlink");
    //	if( pElement ) 
    //	{
    //		m_bLinkPage = ( pElement->getValue() == "true" ) ? true : false;
    //	}

    //	pElement = child->getChildByName("LinkWeb");
    //	if( pElement ) 
    //	{
    //		m_LinkWeb =  pElement->getValue();
    //	}
    //	else

    //	{
    //		m_LinkWeb = "http://www.5shen.cn";
    //	}
    //	
    //	
    //}
    //
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //
    child = element->getChildByName( "Game" );
    if( child )
    {	
        XMLElement* pElement = child->getChildByName("Professions");
        if( pElement )
        {
            XMLElement* pProElement;
            for( int i=0; i<pElement->getChildrenCount(); i++)
            {
                pProElement = pElement->getChild(i);
                if(pProElement->getName() == "Profession" )
                {
                    XMLElement *pCurr = NULL;
                    CProfessionInfo Pro;// = &m_vtProfession[i];
                    //m_vtProfession.insert( )
                    pCurr = pProElement->getChildByName("Id");
                    if( pCurr )
                    {
                        Pro.nID = pCurr->getValuei();
                    }
                    pCurr = pProElement->getChildByName("CreateShowString");
                    if( pCurr )
                    {
                        std::wstring str = Common::_tstring::UTF8towcs(pCurr->getValue().c_str());
                        Pro.m_strCreateShow = Common::_tstring::toNarrowString(str.c_str()).c_str();
                    }
                    pCurr = pProElement->getChildByName("Text");
                    if( pCurr )
                    {
                        std::wstring str = Common::_tstring::UTF8towcs(pCurr->getValue().c_str());
                        Pro.m_strNote = Common::_tstring::toNarrowString(str.c_str()).c_str();
                    }
                    pCurr = pProElement->getChildByName("CName");
                    if( pCurr )
                    {
                        std::wstring str = Common::_tstring::UTF8towcs(pCurr->getValue().c_str());
                        Pro.m_strProShow = Common::_tstring::toNarrowString(str.c_str()).c_str();
                    }
                    m_vtProfession.push_back(Pro);
                }
            }
        }

        XMLElement* pRanks = child->getChildByName("Ranks");
        if (pRanks)
        {
            m_rankDescriptions.clear();
            for (int i = 0; i < pRanks->getChildrenCount(); i++)
            {
                XMLElement* pRank = pRanks->getChild(i);
                XMLElement* pType = pRank->getChildByName("Type");
                if (!pType)
                    continue;

                XMLElement* pDesc = pRank->getChildByName("Description");
                if (pDesc)
                {
                    std::wstring str = Common::_tstring::UTF8towcs(pType->getValue().c_str());
                    std::string type = Common::_tstring::toNarrowString(str.c_str()).c_str();

                    str = Common::_tstring::UTF8towcs(pDesc->getValue().c_str());
                    std::string desc = Common::_tstring::toNarrowString(str.c_str()).c_str();

                    m_rankDescriptions[type].type = type;
                    m_rankDescriptions[type].description = desc;
                }
            }
        }
    }
    //
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //
    //
    //child = element->getChildByName( "SelectUI" );
    //if( child )
    //{	
    //	XMLElement* pElement = child->getChildByName("fRoleScale");
    //	if( pElement )
    //	{
    //		m_fSelectUIRoleScale = pElement->getValuef();
    //	}
    //}
    m_fSelectUIRoleScale = 2.2f;

    child = element->getChildByName( "UIEx" );
    if( child )
    {	
        DWORD dwColor0 = 0xFFFFFFFF;
        DWORD dwColor1 = 0xFFFFFFFF;
        BYTE a, r,g,b;
        XMLElement* pElement = child->getChildByName("TipsColor0_A");
        if( pElement )
        {
            a= pElement->getValuei();
        }
        pElement = child->getChildByName("TipsColor0_R");
        if( pElement )
        {
            r= pElement->getValuei();
        }
        pElement = child->getChildByName("TipsColor0_G");
        if( pElement )
        {
            g= pElement->getValuei();
        }
        pElement = child->getChildByName("TipsColor0_B");
        if( pElement )
        {
            b= pElement->getValuei();
        }
        dwColor0 = a<<24 | r<<16 | g <<8 | b;

        //////////////////////////////////////////////////////////////////////////
        //
        pElement = child->getChildByName("TipsColor1_A");
        if( pElement )
        {
            a= pElement->getValuei();
        }
        pElement = child->getChildByName("TipsColor1_R");
        if( pElement )
        {
            r= pElement->getValuei();
        }
        pElement = child->getChildByName("TipsColor1_G");
        if( pElement )
        {
            g= pElement->getValuei();
        }
        pElement = child->getChildByName("TipsColor1_B");
        if( pElement )
        {
            b= pElement->getValuei();
        }
        dwColor1 = a<<24 | r<<16 | g <<8 | b;
        m_dwTipColor0 = dwColor0;
        m_dwTipColor1 = dwColor1;
    }
    //
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //
    child = element->getChildByName( "TipsTextColor" );
    if( child )
    {	
        DWORD dwColor0 = 0xFFFFFFFF;
        DWORD dwColor1 = 0xFFFFFFFF;
        BYTE a, r,g,b;
        XMLElement* 
            pElement = child->getChildByName("Blue_A");
        if( pElement )
        {
            a= pElement->getValuei();
        }
        pElement = child->getChildByName("Blue_R");
        if( pElement )
        {
            r= pElement->getValuei();
        }	
        pElement = child->getChildByName("Blue_G");
        if( pElement )
        {
            g= pElement->getValuei();
        }	
        pElement = child->getChildByName("Blue_B");
        if( pElement )
        {
            b= pElement->getValuei();
        }
        if( a != 0 &&
            r != 0 &&
            g != 0 &&
            b != 0 )
        {
            dwColor1 = a<<24 | r<<16 | g <<8 | b;
            m_dwBlue = dwColor1;
        }

        //////////////////////////////////////////////////////////////////////////

        pElement = child->getChildByName("Grayed_A");
        if( pElement )
        {
            a= pElement->getValuei();
        }
        pElement = child->getChildByName("Grayed_R");
        if( pElement )
        {
            r= pElement->getValuei();
        }	
        pElement = child->getChildByName("Grayed_G");
        if( pElement )
        {
            g= pElement->getValuei();
        }	
        pElement = child->getChildByName("Grayed_B");
        if( pElement )
        {
            b= pElement->getValuei();
        }
        if( a != 0 &&
            r != 0 &&
            g != 0 &&
            b != 0 )
        {
            dwColor1 = a<<24 | r<<16 | g <<8 | b;
            m_dwGrayed = dwColor1;
        }
        //////////////////////////////////////////////////////////////////////////
        pElement = child->getChildByName("Green_A");
        if( pElement )
        {
            a= pElement->getValuei();
        }
        pElement = child->getChildByName("Green_R");
        if( pElement )
        {
            r= pElement->getValuei();
        }	
        pElement = child->getChildByName("Green_G");
        if( pElement )
        {
            g= pElement->getValuei();
        }	
        pElement = child->getChildByName("Green_B");
        if( pElement )
        {
            b= pElement->getValuei();
        }
        if( a != 0 &&
            r != 0 &&
            g != 0 &&
            b != 0 )
        {
            dwColor1 = a<<24 | r<<16 | g <<8 | b;
            m_dwGreen = dwColor1;
        }

        //////////////////////////////////////////////////////////////////////////
        pElement = child->getChildByName("Gold_A");
        if( pElement )
        {
            a= pElement->getValuei();
        }
        pElement = child->getChildByName("Gold_R");
        if( pElement )
        {
            r= pElement->getValuei();
        }	
        pElement = child->getChildByName("Gold_G");
        if( pElement )
        {
            g= pElement->getValuei();
        }	
        pElement = child->getChildByName("Gold_B");
        if( pElement )
        {
            b= pElement->getValuei();
        }
        if( a != 0 &&
            r != 0 &&
            g != 0 &&
            b != 0 )
        {
            dwColor1 = a<<24 | r<<16 | g <<8 | b;
            m_dwGold = dwColor1;
        }

        //////////////////////////////////////////////////////////////////////////
        pElement = child->getChildByName("Yellow_A");
        if( pElement )
        {
            a= pElement->getValuei();
        }
        pElement = child->getChildByName("Yellow_R");
        if( pElement )
        {
            r= pElement->getValuei();
        }	
        pElement = child->getChildByName("Yellow_G");
        if( pElement )
        {
            g= pElement->getValuei();
        }	
        pElement = child->getChildByName("Yellow_B");
        if( pElement )
        {
            b= pElement->getValuei();
        }
        if( a != 0 &&
            r != 0 &&
            g != 0 &&
            b != 0 )
        {
            dwColor1 = a<<24 | r<<16 | g <<8 | b;
            m_dwYellow = dwColor1;
        }

        //////////////////////////////////////////////////////////////////////////

        pElement = child->getChildByName("Red_A");
        if( pElement )
        {
            a= pElement->getValuei();
        }
        pElement = child->getChildByName("Red_R");
        if( pElement )
        {
            r= pElement->getValuei();
        }	
        pElement = child->getChildByName("Red_G");
        if( pElement )
        {
            g= pElement->getValuei();
        }	
        pElement = child->getChildByName("Red_B");
        if( pElement )
        {
            b= pElement->getValuei();
        }
        if( a != 0 &&
            r != 0 &&
            g != 0 &&
            b != 0 )
        {
            dwColor1 = a<<24 | r<<16 | g <<8 | b;
            m_dwRed = dwColor1;
        }
        //////////////////////////////////////////////////////////////////////////
        a = 255;
        r = 128;
        g = 0;
        b = 129;
        if( a != 0 &&
            r != 0 &&
            g != 0 &&
            b != 0 )
        {
            dwColor1 = a<<24 | r<<16 | g <<8 | b;
            m_dwPurple = dwColor1;
        }

        //////////////////////////////////////////////////////////////////////////
    }
    //
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //
    //
    child = element->getChildByName( "PackUIViewport" );
    if( child )
    {	
        XMLElement* pElement = child->getChildByName("fX");
        if( pElement )
        {
            m_ViewportCfg.m_fX = pElement->getValuef();
        }
        pElement = child->getChildByName("fY");
        if( pElement )
        {
            m_ViewportCfg.m_fY = pElement->getValuef();
        }
        pElement = child->getChildByName("fWidth");
        if( pElement )
        {
            m_ViewportCfg.m_fWidth = pElement->getValuef();
        }
        pElement = child->getChildByName("fHeight");
        if( pElement )
        {
            m_ViewportCfg.m_fHeight = pElement->getValuef();
        }
        pElement = child->getChildByName("fRoleScaleMale");
        if( pElement )
        {
            m_ViewportCfg.m_fRoleScaleMale = pElement->getValuef();
        }
        pElement = child->getChildByName("fRoleScaleFemale");
        if( pElement )
        {
            m_ViewportCfg.m_fRoleScaleFemale = pElement->getValuef();
        }
    }
    child = element->getChildByName( "TargetPackUIViewport" );
    if( child )
    {	
        XMLElement* pElement = child->getChildByName("fX");
        if( pElement )
        {
            m_targetViewportCfg.m_fX = pElement->getValuef();
        }
        pElement = child->getChildByName("fY");
        if( pElement )
        {
            m_targetViewportCfg.m_fY = pElement->getValuef();
        }
        pElement = child->getChildByName("fWidth");
        if( pElement )
        {
            m_targetViewportCfg.m_fWidth = pElement->getValuef();
        }
        pElement = child->getChildByName("fHeight");
        if( pElement )
        {
            m_targetViewportCfg.m_fHeight = pElement->getValuef();
        }
        pElement = child->getChildByName("fRoleScaleMale");
        if( pElement )
        {
            m_targetViewportCfg.m_fRoleScaleMale = pElement->getValuef();
        }
        pElement = child->getChildByName("fRoleScaleFemale");
        if( pElement )
        {
            m_targetViewportCfg.m_fRoleScaleFemale = pElement->getValuef();
        }
    }
    //
    //////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////////////
    //
    BOOL HasChild = FALSE;
    D3DXVECTOR3		vRoleSunDirect = D3DXVECTOR3( 0, 0, -1);
    D3DCOLORVALUE	colorRoleSun;
    colorRoleSun.a = 1.0f;
    colorRoleSun.r = 75.f / 255;
    colorRoleSun.g = 70.f / 255;
    colorRoleSun.b = 60.f / 255;

    D3DCOLORVALUE	colorRoleAmbient;//  = D3DCOLORVALUE(1.0f,1.0f,1.0f,1.0f) ;
    colorRoleAmbient.a = 1.0f;
    colorRoleAmbient.r = 45.5 / 255;
    colorRoleAmbient.g = 50.f / 255;
    colorRoleAmbient.b = 55.f / 255;

    //child = element->getChildByName("PackRoleLight");
    //if( child )
    //{
    //	XMLElement  *childDir   = NULL;
    //	childDir = child->getChildByName("Direction");
    //	if( childDir )
    //	{
    //		if( childDir->getChildByName("x") )
    //			vRoleSunDirect.x = childDir->getChildByName("x")->getValuef();
    //		if( childDir->getChildByName("y") )
    //			vRoleSunDirect.y = childDir->getChildByName("y")->getValuef();
    //		if( childDir->getChildByName("z") )
    //			vRoleSunDirect.z = childDir->getChildByName("z")->getValuef();

    //		D3DXVec3Normalize( &vRoleSunDirect, &vRoleSunDirect );
    //		HasChild = TRUE;
    //	}
    //	childDir = child->getChildByName("Color");
    //	if( childDir )
    //	{
    //		colorRoleSun.a = 1.0f;
    //		if( childDir->getChildByName("R") )
    //			colorRoleSun.r = childDir->getChildByName("R")->getValuef()/255.0f;
    //		if( childDir->getChildByName("G") )
    //			colorRoleSun.g = childDir->getChildByName("G")->getValuef()/255.0f;
    //		if( childDir->getChildByName("B") )
    //			colorRoleSun.b = childDir->getChildByName("B")->getValuef()/255.0f;
    //		HasChild = TRUE;
    //	}

    //	childDir = child->getChildByName("Ambient");
    //	if( childDir )
    //	{
    //		colorRoleAmbient.a = 1.0f;
    //		if( childDir->getChildByName("R") )
    //			colorRoleAmbient.r = childDir->getChildByName("R")->getValuef()/255.0f;
    //		if( childDir->getChildByName("G") )
    //			colorRoleAmbient.g = childDir->getChildByName("G")->getValuef()/255.0f;
    //		if( childDir->getChildByName("B") )
    //			colorRoleAmbient.b = childDir->getChildByName("B")->getValuef()/255.0f;
    //		HasChild = TRUE;
    //	}


    //}
    //if( HasChild )
    {
        m_PackRoleLight.Diffuse = colorRoleSun;
        m_PackRoleLight.Direction = vRoleSunDirect;
        m_PackRoleLight.Ambient = colorRoleAmbient;
    }
    //
    return true;
}

bool CSystemConfig::exportXMLSettings(std::ofstream &xmlFile  )
{
    return true;
}

bool CSystemConfig::exportXMLSettings(const char* xmlPath)
{
    return true;
}