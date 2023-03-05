#include "CountryFunction.h"
#include "XmlStringLanguage.h"
#include "TimeEx.h"
#include "Common.h"
#include "GlobalDef.h"

CountryFunction::CountryFunction()
{
    for( int i = 0; i < CountryDefine::Country_Max; ++i )
    {
        m_nCountryName[i].clear();
    }
}

CountryFunction::~CountryFunction()
{
}

// 根据国家 ID 取阵营名
std::string CountryFunction::GetDefaultCountryNameById( int Id )
{
    std::string str;
    switch( Id )
    {
	case CountryDefine::Country_Init:
		str = theXmlString.GetString( eText_CountryName );
		break;
    case CountryDefine::Country_LouLan:
        str = theXmlString.GetString( eText_Country_LouLan );
        break;
    case CountryDefine::Country_KunLun:
        str = theXmlString.GetString( eText_Country_KunLun );
        break;
    case CountryDefine::Country_DunHuang:
        str = theXmlString.GetString( eText_Country_DunHuang );
        break;
        //case CountryDefine::Country_LaiYin:
        //	str = theXmlString.GetString( eText_Country_LaiYin );
        //	break;
    default:
        break;
    }
    return str;
}

// 根据国家 ID 取国号名
std::string CountryFunction::GetCountryNameById( int Id )
{
    std::string str;
    if( Id <= CountryDefine::Country_Init || Id >= CountryDefine::Country_Max )
        return str;

    const std::string* pStrNameArray = CountryFunction::Instance()->GetCountryNameArray();
    if( !pStrNameArray )
        return str;

    str = pStrNameArray[Id - 1];
    if( str.empty() )
        return ( GetDefaultCountryNameById( Id ) );

    return str;
}

// 根据阵营名取Id
short CountryFunction::GetCountryIdByDefaultName( const char * pCountry )
{
    if (!pCountry)
    {
        return -1;
    }
    if (0 == strcmp(pCountry,theXmlString.GetString( eText_Country_LouLan )))
    {
        return CountryDefine::Country_LouLan;
    }
    if (0 == strcmp(pCountry,theXmlString.GetString( eText_Country_KunLun )))
    {
        return CountryDefine::Country_KunLun;
    }
    if (0 == strcmp(pCountry,theXmlString.GetString( eText_Country_DunHuang )))
    {
        return CountryDefine::Country_DunHuang;
    }
    //if (0 == strcmp(pCountry,theXmlString.GetString( eText_Country_LaiYin )))
    //{
    //	return CountryDefine::Country_LaiYin;
    //}
    return -1;
}

// 根据国号名取Id
short CountryFunction::GetCountryIdByName( const char* pCountry )
{
    if( !pCountry )
    {
        return -1;
    }
    const std::string* pStrNameArray = CountryFunction::Instance()->GetCountryNameArray();
    if( 0 == strcmp( pCountry, pStrNameArray[CountryDefine::Country_LouLan - 1].c_str() ) )
    {
        return CountryDefine::Country_LouLan;
    }
    if( 0 == strcmp( pCountry, pStrNameArray[CountryDefine::Country_KunLun - 1].c_str() ) )
    {
        return CountryDefine::Country_KunLun;
    }
    if( 0 == strcmp( pCountry, pStrNameArray[CountryDefine::Country_DunHuang - 1].c_str() ) )
    {
        return CountryDefine::Country_DunHuang;
    }
    return -1;
}

// 根据国家称号 ID 取称号名
std::string CountryFunction::GetCountryTitleNameById( int Id )
{
    std::string str;
    switch( Id )
    {
    case CountryDefine::Title_King:
        str = theXmlString.GetString( eText_CountryTitle_King );
        break;
    case CountryDefine::Title_General:
        str = theXmlString.GetString( eText_CountryTitle_General );
        break;
    case CountryDefine::Title_Queen:
        str = theXmlString.GetString( eText_CountryTitle_Queen );
        break;
    case CountryDefine::Title_CouncilorLeft:
        str = theXmlString.GetString( eText_CountryTitle_CouncilorLeft );
        break;
    case CountryDefine::Title_CouncilorRight:
        str = theXmlString.GetString( eText_CountryTitle_CouncilorRight );
        break;
    case CountryDefine::Title_CaptorLeft:
        str = theXmlString.GetString( eText_CountryTitle_CaptorLeft );
        break;
    case CountryDefine::Title_CaptorRight:
        str = theXmlString.GetString( eText_CountryTitle_CaptorRight );
        break;
    case CountryDefine::Title_KingGuard:
        str = theXmlString.GetString( eText_CountryTitle_KingGuard );
        break;
    case CountryDefine::Title_Dragon:
        str = theXmlString.GetString( eText_CountryTitle_Dragon );
        break;
    case CountryDefine::Title_DragonGuard:
        str = theXmlString.GetString( eText_CountryTitle_DragonGuard );
        break;
    case CountryDefine::Title_Rosefinch:
        str = theXmlString.GetString( eText_CountryTitle_Rosefinch );
        break;
    case CountryDefine::Title_RosefinchGuard:
        str = theXmlString.GetString( eText_CountryTitle_RosefinchGuard );
        break;
    default:
        break;
    }
    return str;
}

// 根据公会称号Id取公会名
std::string CountryFunction::GetGuildTitleNameById( int Id )
{
    std::string str;
    switch( Id )
    {
    case CountryDefine::Title_GuildMaster:
    case CountryDefine::Title_King:
        str = theXmlString.GetString( eTextGang_Master );
        break;
    case CountryDefine::Title_ViceMaster:
        str = theXmlString.GetString( eTextGang_ViceMaster );
        break;
    case CountryDefine::Title_FamilyMaster:
        str = theXmlString.GetString( eTextTong_Master );
        break;
	case CountryDefine::Title_GuildMember:
		str = theXmlString.GetString( eTextGang_Member);
		break;
    default:
        break;
    }
    return str;
}

// 检测是否为国家称号
bool CountryFunction::CheckIsCountryTitle( int nTitle )
{
    return nTitle <= CountryDefine::Title_QueenMale && nTitle >= CountryDefine::Title_King; 
}

// 检测是否为公会称号
bool CountryFunction::CheckIsGuildTitle( int nTitle )
{
    return nTitle <= CountryDefine::Title_FamilyMaster && nTitle >= CountryDefine::Title_GuildMaster;
}

// 根据国家职位 ID 取职位名
std::string CountryFunction::GetCountryOfficialNameById( int id )
{
    std::string str;
    if( id < CountryDefine::Position_Max && id > 0 )
    {
        switch( id )
        {
        case CountryDefine::Position_CaptorLeft:
            str = theXmlString.GetString( eText_CountryPos_LCaptor );
            break;
        case CountryDefine::Position_CaptorRight:
            str = theXmlString.GetString( eText_CountryPos_RCaptor );
            break;
        case CountryDefine::Position_CouncilorLeft:
            str = theXmlString.GetString( eText_CountryPos_LCouncilor );
            break;
        case CountryDefine::Position_CouncilorRight:
            str = theXmlString.GetString( eText_CountryPos_RCouncilor );
            break;
        case CountryDefine::Position_General:
            str = theXmlString.GetString( eText_CountryPos_General );
            break;
        case CountryDefine::Position_Queen:
            str = theXmlString.GetString( eText_CountryPos_Queen );
            break;
        case CountryDefine::Position_King:
            str = theXmlString.GetString( eText_CountryPos_King );
            break;
        default:
            break;
        }
    }
    return str;
}

// 得到有颜色的国家职位字串
std::string CountryFunction::GetOfficialForChat( int id )
{
    std::string str;
    if( id < CountryDefine::Position_Max && id > 0 )
    {
        switch( id )
        {
        case CountryDefine::Position_CaptorLeft:
            str = theXmlString.GetString( eText_CountryTitle_CaptorLeft_Col );
            break;
        case CountryDefine::Position_CaptorRight:
            str = theXmlString.GetString( eText_CountryTitle_CaptorRight_Col );
            break;
        case CountryDefine::Position_CouncilorLeft:
            str = theXmlString.GetString( eText_CountryTitle_CouncilorLeft_Col );
            break;
        case CountryDefine::Position_CouncilorRight:
            str = theXmlString.GetString( eText_CountryTitle_CouncilorRight_Col );
            break;
        case CountryDefine::Position_General:
            str = theXmlString.GetString( eText_CountryTitle_General_Col );
            break;
        case CountryDefine::Position_Queen:
            str = theXmlString.GetString( eText_CountryTitle_Queen_Col );
            break;
        case CountryDefine::Position_King:
            str = theXmlString.GetString( eText_CountryTitle_King_Col );
        default:
            break;
        }
    }
    return str;
}

// 根据国家职位 ID 取称号名
std::string CountryFunction::GetCountryTitleNameByOfficialId( int id )
{
    return GetCountryOfficialNameById( CountryDefine::GetCountryTitleByPosition( id ) );
}

// 根据国家战场类型取名字
std::string CountryFunction::GetCountryBattleNameByType( int nType )
{
    std::string strBattle;
    switch( nType )
    {
    case CountryDefine::Battle_King:
        strBattle = theXmlString.GetString( eText_CountryBattle_King );
        break;
    case CountryDefine::Battle_Dragon:
        strBattle = theXmlString.GetString( eText_CountryBattle_Dragon );
        break;
    case CountryDefine::Battle_Rosefinch:
        strBattle = theXmlString.GetString( eText_CountryBattle_Rosefinch );
        break;
    default:
        break;
    }
    return strBattle;
}

// 根据职业取攻击方式描述
std::string CountryFunction::GetAttackStringByProfession( int nProfession )
{
    std::string strAttType;
    switch( nProfession )
    {
    case EArmType_Warrior:
    case EArmType_Assassin:
        strAttType = theXmlString.GetString( eText_PlayAtt_Short );
        break;
    case EArmType_Hunter:
    case EArmType_Sniper:
        strAttType = theXmlString.GetString( eText_PlayAtt_Long );
        break;
    case EArmType_Mage:
    case EArmType_Taoist:
        strAttType = theXmlString.GetString( eText_PlayAtt_Magic );
        break;
    default:
        break;
    }
    return strAttType;
}

// 根据时间取时间字串
std::string CountryFunction::GetTimeStringBySeconds( DWORD dwTime )
{
    std::string strTime;
    char szTemp[MAX_PATH] = {0};
    TimeEx time( dwTime );
    int nHour = time.GetHour();
    int nMinute = time.GetMinute();
    int nSecond = time.GetSecond();
    if( nHour > 0 )
    {
        MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%d%s", nHour, theXmlString.GetString( eTimeUnit_Hour ) );
        strTime += szTemp;
    }
    if( nMinute > 0 )
    {
        MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%d%s", nMinute, theXmlString.GetString( eTimeUnit_Minute ) );
        strTime += szTemp;
    }
    if( nSecond > 0 )
    {
        MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%d%s", nSecond, theXmlString.GetString( eTimeUnit_Second ) );
        strTime += szTemp;
    }
    return strTime;
}

// 根据职业ID取职业名
std::string CountryFunction::GetProfessionByID( int nProfessionID )
{
    std::string str;
    switch( nProfessionID )
    {
    case EArmType_Warrior:
        str = theXmlString.GetString( eProfession_Warrior );
        break;
    case EArmType_Assassin:
        str = theXmlString.GetString( eProfession_Assassin );
        break;
    case EArmType_Mage:
        str = theXmlString.GetString( eProfession_Mage );
        break;
    case  EArmType_Taoist:
        str = theXmlString.GetString( eProfession_Taoist );
        break;
    case EArmType_Hunter:
        str = theXmlString.GetString( eProfession_Hunter );
        break;
    default:
        break;
    }
    return str;
}

//------------  逻辑部分  -----------------
void CountryFunction::UpdateCountryName( int nCountryId, char* szName )
{
    if( nCountryId <= CountryDefine::Country_Init || nCountryId >= CountryDefine::Country_Max )
        return;

    m_nCountryName[nCountryId - 1] = szName;
}

void CountryFunction::ClearCountryName()
{
    for( int i = 0; i < CountryDefine::Country_Max; ++i )
    {
        m_nCountryName[i].clear();
    }
}

const std::string* CountryFunction::GetCountryNameArray()
{
    return m_nCountryName;
}
