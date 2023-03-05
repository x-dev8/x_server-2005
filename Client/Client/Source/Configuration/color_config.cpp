
#include "color_config.h"
#include "FuncPerformanceLog.h"
#include "RapidXml/MeRapidXml.h"
#include "timecooling_configure.h"
#include "Meui/ControlList.h"
#include "Cfg.h"
CColor_Configure Color_Config;

CColor_Configure::CColor_Configure()
{
	guardfunc;
	memset( mAllColor, 0, sizeof( mAllColor ) );
	unguard;
}
CColor_Configure::~CColor_Configure()
{
	guardfunc;
	unguard;
}
DWORD CColor_Configure::ARGBtoDWORD(int a, int r, int g, int b)
{
	guardfunc;
	DWORD color = ( ((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
	return color;
	unguard;
}
DWORD CColor_Configure::getColor(ColorConfigure type)
{
	guardfunc;
	
	if ( type <= CC_CONFIG_INVALID || type >= CC_CONFIG_MAX )
	{
		return 0;
	}

	return mAllColor[type];
	unguard;
}


//extern DWORD GColorItemDesc;
//extern DWORD GColorItemType;
//extern DWORD GColorProNeed;
//extern DWORD GColorLvlNeed;
//extern DWORD GColorEquipHP;
//extern DWORD GColorEquipType;


void CColor_Configure::load()
{
	guardfunc;

	g_TimeCooling_Config.load();

	MeXmlDocument	doc;
	if( !doc.LoadFile(XML_GLOBALCONFIG_FILENAME) )
	{
		assert(false && "Login.cpp::LoadConfigXml 读取文件不错");
		return;
	}

	const char* szValue = NULL;
	int nValue = 0;
	int a = 0, r = 0, g = 0, b = 0;
	
	MeXmlElement* pElem = doc.FirstChildElement(XML_GLOBALCONFIG_ROOT_NAME)->FirstChildElement("ColorSetting")->FirstChildElement("configure");
	for( ; pElem; pElem = pElem->NextSiblingElement() )
	{
		pElem->QueryIntAttribute("id", &nValue);
		if ( nValue <= CC_CONFIG_INVALID || nValue >= CC_CONFIG_MAX )
		{
			continue;
		}

		szValue = pElem->Attribute("color");
		sscanf( szValue, "%d, %d, %d, %d", &a, &r, &g, &b);
		mAllColor[nValue] = ARGBtoDWORD( a, r, g, b );
	}

	//////////////////////////////////////////////////////////////////////////
	//Init Color 
	// 
	//GColorItemDesc	= mAllColor[CC_ITME_SHOW];
	//GColorItemType	= mAllColor[CC_ITME_TYPE];
	//GColorProNeed	= mAllColor[CC_ITME_PRONEED];
	//GColorLvlNeed	= mAllColor[CC_ITEM_LVLNEED];
	//GColorEquipHP	= mAllColor[CC_ITEM_WEAR];
	//GColorEquipType	= mAllColor[CC_ITEM_EQUIPTYPE];
	//////////////////////////////////////////////////////////////////////////
	
	ControlList::s_LISTSELECTON_COLOR			= mAllColor[CC_LISTSELECTON];
	ControlList::s_CHAT_HYBER_DOWNLINE_COLOR	= mAllColor[CC_CHAT_HYBER_DOWNLINE];
	ControlList::s_PathFindLinker_COLOR			= mAllColor[CC_PathFindLinker];
	ControlList::s_CHAT_PLAYERNAME_COLOR		= mAllColor[CC_CHAT_PLAYERNAME];

	unguard;
}

// 白名是0级别
static const int s_nPKValueLevel[] = { 0, 5, 15, 30, 60, 100, 155, 225, 305, 395, 490  };
static const int s_nPKValueLevelCount = sizeof(s_nPKValueLevel) / sizeof(int);

DWORD CColor_Configure::GetPkNameColor( int nPkType )
{
	DWORD col = 0;
    switch( nPkType )
    {
    case PKMode_Normal:
        col = Color_Config.getColor(CC_PetColor_Green /*CC_WhiteName*/ );
        break;
    case PKMode_Fight:
		col = Color_Config.getColor( CC_PetColor_Green );
        //col = Color_Config.getColor( CC_TwoRedName );
        break;
    case PKMode_Critical:
        col = Color_Config.getColor( CC_SixRedName );
        break;
	case PKMode_AttackFight:
	case PKMode_AttackGuild:
		col = Color_Config.getColor( CC_TwoRedName );
		break;
	case PKMode_Guild:
		col = Color_Config.getColor( CC_PetColor_Green );
		//col = Color_Config.getColor( CC_ThreeRedName);
		break;
    default:
        col = Color_Config.getColor( CC_PetColor_Green );
        break;
    }
    return col;
}
