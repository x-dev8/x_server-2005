#include "CountryConfig.h"
#include <algorithm>
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"
#include "Dxsdk\d3dx9math.h"

unsigned int CountryConfig::GetMaxRaiseMoney( unsigned int nLevel ) const
{
    if ( vecRaiseSetting.empty() )
    { return 0; }

    const RaiseSetting& xRaiseSetting = vecRaiseSetting.back();
    unsigned int nMaxRaiseMoney = xRaiseSetting.GetMoney();

    for ( RaiseSettingVectorIter iter = vecRaiseSetting.begin(); iter != vecRaiseSetting.end(); ++iter )
    {
        if ( nLevel < iter->GetLevel() )
        {
            nMaxRaiseMoney = iter->GetMoney();
            break;
        }
    }

    return nMaxRaiseMoney;
}

unsigned int CountryConfig::GetMaxRaiseIndex( unsigned int nLevel ) const
{
    int nIndex = 0;
    for ( RaiseSettingVectorIter iter = vecRaiseSetting.begin(); iter != vecRaiseSetting.end(); ++iter, ++nIndex )
    {
        if ( nLevel < iter->GetLevel() )
        {
            return nIndex;
        }
    }

    return 0;
}

const CountryConfig::BornMapSetting* CountryConfig::GetBornMapSetting( unsigned int nCountry, unsigned char uchIndex ) const
{
    BornMapSettingMapConstIter iter = mapBornMapSetting.find( nCountry );
    if ( iter == mapBornMapSetting.end() )
    { return NULL; }

    if ( uchIndex >= iter->second.size() )
    { return NULL; }

    return &( iter->second.at( uchIndex ) );
}


unsigned int CountryConfig::GetBornMapSettingCount( unsigned int nCountry ) const
{
    BornMapSettingMapConstIter iter = mapBornMapSetting.find( nCountry );
    if ( iter == mapBornMapSetting.end() )
    { return 0; }

    return static_cast< unsigned int >( iter->second.size() );
}

const CountryConfig::SpecialMapSetting* CountryConfig::GetPrisonMapSetting( unsigned int nCountry ) const
{
    if ( nCountry >= vecPrisonMapSetting.size() )
    { return NULL; }

    return &( vecPrisonMapSetting.at( nCountry  ) );
}

const CountryConfig::SpecialMapSetting* CountryConfig::GetReliveMapSetting( unsigned int nCountry ) const
{
    if ( nCountry >= vecReliveMapSetting.size() )
    { return NULL; }

    return &( vecReliveMapSetting.at( nCountry  ) );
}

const CountryConfig::RaiseSetting* CountryConfig::GetRaiseMoneyByIndex( unsigned int nIndex ) const
{
    if ( nIndex >= GetRaiseSettingCount() )
    { return NULL; }

    return &( vecRaiseSetting.at( nIndex ) );
}

const CountryConfig::QuestSetting* CountryConfig::GetQuestSetting( unsigned int nType ) const
{
    if ( nType >= vecQuestSetting.size() )
    { return NULL; }

    return &( vecQuestSetting.at( nType ) );
}

const CountryConfig::MountSetting* CountryConfig::GetMountSettingByLevel( unsigned int nLevel ) const
{
    MountSettingVectorIter iter = std::find( vecMountSetting.begin(), vecMountSetting.end(), nLevel );
    if ( iter == vecMountSetting.end() )
    { return NULL; }

    return &( *iter );
}

const CountryConfig::MountSetting* CountryConfig::GetMountSettingByIndex( unsigned int nIndex ) const
{
    if ( nIndex >= vecMountSetting.size() )
    { return NULL; }

    return &( vecMountSetting.at( nIndex ) );
}

void CountryConfig::AddBornMapSetting( const BornMapSetting& xSetting )
{
    BornMapSettingMapIter iter = mapBornMapSetting.find( xSetting.GetCountry() );
    if ( iter == mapBornMapSetting.end() )
    {
        BornMapSettingVector vecSetting;
        vecSetting.push_back( xSetting );

        mapBornMapSetting.insert( std::make_pair( xSetting.GetCountry(), vecSetting ) );
    }
    else
    {
        iter->second.push_back( xSetting );
    }
}

bool CountryConfig::LoadCountryConfig( const char* szFile )
{
    if ( szFile == NULL || szFile[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pCountry = pRoot->FirstChildElement( "Country" );
    if ( pCountry == NULL )
    { return false; }

    int nValue = 0;

    // 最大金钱
    if ( pCountry->Attribute( "MaxMoney", &nValue ) == NULL )
    { return false; }
    nMaxMoney = nValue;

	//zhuxincong 9.18 新增国家贡品
	if ( pCountry->Attribute("MaxTribute",&nValue) == NULL)
	{
		return false;
	}
	nMaxTribute = nValue;

	if (pCountry->Attribute("MinTribute",&nValue) == NULL)
	{
		return false;
	}
	nMinTribute = nValue;

	if(pCountry->Attribute("FirstTribute",&nValue) == NULL)//初始化的贡品
	{
		return false;
	}
	nFirstTribute = nValue;


    // 国家出生点
    MeXmlElement* pBornMaps = pCountry->FirstChildElement( "BornMaps" );
    if ( pBornMaps == NULL )
    { return false; }   
    mapBornMapSetting.clear();
    MeXmlElement* pBornMap = pBornMaps->FirstChildElement( "BornMap" );
    while ( pBornMap != NULL )
    {
        BornMapSetting xSetting;

        if ( pBornMap->Attribute( "Country", &nValue ) == NULL )
        { return false; }
        xSetting.SetCountry( nValue );

        if ( pBornMap->Attribute( "MapID", &nValue ) == NULL )
        { return false; }
        xSetting.SetMapID( nValue );

        double dValue;
        if ( pBornMap->Attribute( "PosX", &dValue ) == NULL )
        { return false; }
        xSetting.SetPosX( static_cast< float >( dValue ) );

        if ( pBornMap->Attribute( "PosY", &dValue ) == NULL )
        { return false; }
        xSetting.SetPosY( static_cast< float >( dValue ) );

        if ( pBornMap->Attribute( "Dir", &dValue ) == NULL )
        { return false; }

        float fDir  = dValue;
        float fDirX = 0.0f, fDirY = 0.0f;
        if( fDir < 0 || fDir > 360 )
        { fDir = 0; }

        fDir = fDir/180*D3DX_PI;
        float fxtoy = tan(fDir);
        float fPosXOff = 0;
        float fPosYOff = 0;

        if( fxtoy == 0 )
        {
            fPosXOff = 1;
        }
        else
        {
            fPosXOff = sqrtf(1/(1+fxtoy*fxtoy));
            fPosYOff = fabs(fxtoy*fPosXOff);
        }
        if( ( fDir >= 0 && fDir <= D3DX_PI/2 ) || ( fDir >= -D3DX_PI*2 && fDir <= -D3DX_PI*3/2 ) )
        { // 第一象限
            fDirX = fPosXOff;
            fDirY = fPosYOff;
        }
        else if( ( fDir >= D3DX_PI/2 && fDir <= D3DX_PI ) || ( fDir >= -D3DX_PI*3/2 && fDir <= -D3DX_PI ) )
        { // 第二象限
            fDirX = -fPosXOff;
            fDirY = fPosYOff;
        }
        else if( ( fDir >= D3DX_PI && fDir <= D3DX_PI*3/2 ) || ( fDir >= -D3DX_PI && fDir <= -D3DX_PI/2 ) )
        { // 第三象限
            fDirX = -fPosXOff;
            fDirY = -fPosYOff;
        }
        else if( ( fDir >= D3DX_PI*3/2 && fDir <= D3DX_PI*2 ) || ( fDir >= -D3DX_PI/2 && fDir <= 0 ) )
        { // 第四象限
            fDirX = fPosXOff;
            fDirY = -fPosYOff;
        }

        xSetting.SetDirX( fDirX );
        xSetting.SetDirY( fDirY );
        
        AddBornMapSetting( xSetting );

        pBornMap = pBornMap->NextSiblingElement();
    }

    // 国家监狱
    MeXmlElement* pPrisonMaps = pCountry->FirstChildElement( "PrisonMaps" );
    if ( pPrisonMaps == NULL )
    { return false; }   
    vecPrisonMapSetting.clear();
    MeXmlElement* pPrisonMap = pPrisonMaps->FirstChildElement( "PrisonMap" );
    while ( pPrisonMap != NULL )
    {
        SpecialMapSetting xSetting;

        if ( pPrisonMap->Attribute( "Country", &nValue ) == NULL )
        { return false; }
        xSetting.SetCountry( nValue );

        if ( pPrisonMap->Attribute( "MapID", &nValue ) == NULL )
        { return false; }
        xSetting.SetMapID( nValue );

        double dValue;
        if ( pPrisonMap->Attribute( "PosX", &dValue ) == NULL )
        { return false; }
        xSetting.SetPosX( static_cast< float >( dValue ) );

        if ( pPrisonMap->Attribute( "PosY", &dValue ) == NULL )
        { return false; }
        xSetting.SetPosY( static_cast< float >( dValue ) );

        if ( pPrisonMap->Attribute( "Dir", &dValue ) == NULL )
        { return false; }
        xSetting.SetDir( dValue );

        vecPrisonMapSetting.push_back( xSetting );

        pPrisonMap = pPrisonMap->NextSiblingElement();
    }

    // 国家回魂殿
    MeXmlElement* pReliveMaps = pCountry->FirstChildElement( "Relives" );
    if ( pReliveMaps == NULL )
    { return false; }   
    vecReliveMapSetting.clear();
    MeXmlElement* ReliveMap = pReliveMaps->FirstChildElement( "ReliveMap" );
    while ( ReliveMap != NULL )
    {
        SpecialMapSetting xSetting;

        if ( ReliveMap->Attribute( "Country", &nValue ) == NULL )
        { return false; }
        xSetting.SetCountry( nValue );

        if ( ReliveMap->Attribute( "MapID", &nValue ) == NULL )
        { return false; }
        xSetting.SetMapID( nValue );

        double dValue;
        if ( ReliveMap->Attribute( "PosX", &dValue ) == NULL )
        { return false; }
        xSetting.SetPosX( static_cast< float >( dValue ) );

        if ( ReliveMap->Attribute( "PosY", &dValue ) == NULL )
        { return false; }
        xSetting.SetPosY( static_cast< float >( dValue ) );

        if ( ReliveMap->Attribute( "Dir", &dValue ) == NULL )
        { return false; }
        xSetting.SetDir( dValue );

        vecReliveMapSetting.push_back( xSetting );

        ReliveMap = ReliveMap->NextSiblingElement();
    }

    // 修改公告
    MeXmlElement* pPlacard = pCountry->FirstChildElement( "Placard" );
    if ( pPlacard == NULL )
    { return false; }
    if ( pPlacard->Attribute( "Count", &nValue ) == NULL )
    { return false; }
    nPlacardCount = nValue;
    if ( pPlacard->Attribute( "CostMoney", &nValue ) == NULL )
    { return false; }
    nPlacardCost = nValue;

    // 禁言功能
    MeXmlElement* pBanSpeak = pCountry->FirstChildElement( "BanSpeak" );
    if ( pBanSpeak == NULL )
    { return false; }
    if ( pBanSpeak->Attribute( "Count", &nValue ) == NULL )
    { return false; }
    nBanSpeakCount = nValue;
    if ( pBanSpeak->Attribute( "CostMoney", &nValue ) == NULL )
    { return false; }
    nBanSpeakCost = nValue;
    if ( pBanSpeak->Attribute( "KeepTime", &nValue ) == NULL )
    { return false; }
    nBanSpeakTime = nValue;
    
    // 赦免功能
    MeXmlElement* pRemit = pCountry->FirstChildElement( "Remit" );
    if ( pRemit == NULL )
    { return false; }
    if ( pRemit->Attribute( "Count", &nValue ) == NULL )
    { return false; }
    nRemitCount = nValue;
    if ( pRemit->Attribute( "CostMoney", &nValue ) == NULL )
    { return false; }
    nRemitCost = nValue;

    // 囚禁功能
    MeXmlElement* pChain = pCountry->FirstChildElement( "Chain" );
    if ( pChain == NULL )
    { return false; }
    if ( pChain->Attribute( "Count", &nValue ) == NULL )
    { return false; }
    nChainCount = nValue;
    if ( pChain->Attribute( "CostMoney", &nValue ) == NULL )
    { return false; }
    nChainCost = nValue;
    if ( pChain->Attribute( "StatusId", &nValue ) == NULL )
    { return false; }
    nChainStatus = nValue;

    // 召集功能
    MeXmlElement* pConvene = pCountry->FirstChildElement( "Convene" );
    if ( pConvene == NULL )
    { return false; }
    if ( pConvene->Attribute( "Count", &nValue ) == NULL )
    { return false; }
    nConveneCount = nValue;
    if ( pConvene->Attribute( "CostMoney", &nValue ) == NULL )
    { return false; }
    nConveneCost = nValue;
    if ( pConvene->Attribute( "KeepTime", &nValue ) == NULL )
    { return false; }
    nConveneTime = nValue;

    if ( pConvene->Attribute( "MinLevel", &nValue ) == NULL )
    { return false; }
    nConveneMinLevel = nValue;

    // 任命
    MeXmlElement* pAppoint = pCountry->FirstChildElement( "Appoint" );
    if ( pAppoint == NULL )
    { return false; }
    if ( pAppoint->Attribute( "MinLevel", &nValue ) == NULL )
    { return false; }
    nAppointMinLevel = nValue;

    // 募集
    MeXmlElement* pRaises = pCountry->FirstChildElement( "Raises" );
    if ( pRaises == NULL )
    { return false; }
    if ( pRaises->Attribute( "Count", &nValue ) == NULL )
    { return false; }
    nRaiseCount = nValue;
    if ( pRaises->Attribute( "KeepTime", &nValue ) == NULL )
    { return false; }
    nRaiseKeepTime = nValue;
    if ( pRaises->Attribute( "MinLevel", &nValue ) == NULL )
    { return false; }
    nRaiseMinLevel = nValue;
    if ( pRaises->Attribute( "RewardExp", &nValue ) == NULL )
    { return false; }
    nRaiseRewardExp = nValue;
    if ( pRaises->Attribute( "BroadMoney", &nValue ) == NULL )
    { return false; }
    nRaiseBroadMoney = nValue;

    vecRaiseSetting.clear();
    MeXmlElement* pRaise = pRaises->FirstChildElement( "Raise" );
    while ( pRaise != NULL )
    {
        RaiseSetting xSetting;
        if ( pRaise->Attribute( "Level", &nValue ) == NULL )
        { return false; }
        xSetting.SetLevel( nValue );

        if ( pRaise->Attribute( "MaxMoney", &nValue ) == NULL )
        { return false; }
        xSetting.SetMoney( nValue );

        vecRaiseSetting.push_back( xSetting );

        pRaise = pRaise->NextSiblingElement();
    }

    // 国家发布任务
    MeXmlElement* pQuests = pCountry->FirstChildElement( "Quests" );
    if ( pQuests == NULL )
    { return false; }

    vecQuestSetting.clear();
	QuestSetting xSettingZero;
	xSettingZero.SetType(0);
	vecQuestSetting.push_back(xSettingZero);
    MeXmlElement* pQuest = pQuests->FirstChildElement( "Quest" );
    while ( pQuest != NULL )
    {
        QuestSetting xSetting;

        if ( pQuest->Attribute( "Type", &nValue ) == NULL )
        { return false; }
        xSetting.SetType( nValue );

        if ( pQuest->Attribute( "Count", &nValue ) == NULL )
        { return false; }
        xSetting.SetCount( nValue );

        if ( pQuest->Attribute( "CostMoney", &nValue ) == NULL )
        { return false; }
        xSetting.SetCostMoney( nValue );

        if ( pQuest->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        xSetting.SetKeepTime( nValue * 60 );

        Common::_tstring strName = "";			
        strName.fromUTF8( pQuest->Attribute( "Name" ) );
        xSetting.SetName( strName.c_str() );

        Common::_tstring strPosition = "";			
        strPosition.fromUTF8( pQuest->Attribute( "AwardPosition" ) );
        xSetting.SetPosition( strPosition.c_str() );

        Common::_tstring strDescription = "";			
        strDescription.fromUTF8( pQuest->Attribute( "Description" ) );
        xSetting.SetDescription( strDescription.c_str() );

		//lyh++ 添加公告配置
		Common::_tstring broadcast = "";			
		broadcast.fromUTF8( pQuest->Attribute( "broadcast" ) );
		xSetting.SetBroadcast( broadcast.c_str() );

        vecQuestSetting.push_back( xSetting );

        pQuest = pQuest->NextSiblingElement();
    }

    // 国家实力
    MeXmlElement* pStrength = pCountry->FirstChildElement( "Strength" );
    if ( pStrength == NULL )
    { return false; }

    if ( pStrength->Attribute( "Release", &nValue ) == NULL )
    { return false; }
    xStrengthSetting.SetReleaseModulus( nValue );

    if ( pStrength->Attribute( "Quest", &nValue ) == NULL )
    { return false; }
    xStrengthSetting.SetQuestModulus( nValue );

    // 国王坐骑
    MeXmlElement* pMounts = pCountry->FirstChildElement( "Mounts" );
    if ( pMounts == NULL )
    { return false; }

    vecMountSetting.clear();
    MeXmlElement* pMount = pMounts->FirstChildElement( "Mount" );
    while ( pMount != NULL )
    {
        MountSetting xSetting;

        if ( pMount->Attribute( "Level", &nValue ) == NULL )
        { return false; }
        xSetting.SetLevel( nValue );

        if ( pMount->Attribute( "KingID", &nValue ) == NULL )
        { return false; }
        xSetting.SetKingID( nValue );

        if ( pMount->Attribute( "QueenID", &nValue ) == NULL )
        { return false; }
        xSetting.SetQueenID( nValue );

        if ( pMount->Attribute( "DragonID", &nValue ) == NULL )
        { return false; }
        xSetting.SetDragionID( nValue );

        if ( pMount->Attribute( "RosefinchID", &nValue ) == NULL )
        { return false; }
        xSetting.SetRosefinchID( nValue );

        vecMountSetting.push_back( xSetting );

        pMount = pMount->NextSiblingElement();
    }

    // 弹劾
    MeXmlElement* pImpeach = pCountry->FirstChildElement( "Impeach" );
    if ( pImpeach == NULL )
    { return false; }

    if ( pImpeach->Attribute( "Rank", &nValue ) == NULL )
    { return false; }
    xImpeakSetting.SetRank( nValue );

    if ( pImpeach->Attribute( "AgreeGuild", &nValue ) == NULL )
    { return false; }
    xImpeakSetting.SetAgreeGuild( nValue );

    if ( pImpeach->Attribute( "AgreePercent", &nValue ) == NULL )
    { return false; }
    xImpeakSetting.SetAgreePercent( nValue );

    if ( pImpeach->Attribute( "CostGuildMoney", &nValue ) == NULL )
    { return false; }
    xImpeakSetting.SetCostGuildMoney( nValue );

    if ( pImpeach->Attribute( "MinLevel", &nValue ) == NULL )
    { return false; }
    xImpeakSetting.SetMinLevel( nValue );

    // 边境队列长度
    MeXmlElement* pBordersFight = pCountry->FirstChildElement( "BordersFight" );
    if ( pBordersFight == NULL )
    { return false; }

    if ( pBordersFight->Attribute( "Count", &nValue ) == NULL )
    { return false; }
    nBordersFightCount = nValue;
	if ( pBordersFight->Attribute( "ReplaceTime", &nValue ) )
	{
		m_SkipSameOverdueInfoTime = nValue;
	}

    // 国家聊天限制
    MeXmlElement* pCountrySpeak = pCountry->FirstChildElement( "CountrySpeak" );
    if ( pCountrySpeak == NULL )
    { return false; }

    if ( pCountrySpeak->Attribute( "SpaceTime", &nValue ) == NULL )
    { return false; }
    nCountrySpeakSpace = nValue * 1000;

    // 屠城战设置
    MeXmlElement* pWarFight = pCountry->FirstChildElement( "WarFight" );
    if ( pWarFight == NULL )
    { return false; }
    
    if ( pWarFight->Attribute( "DayOfWeek", &nValue ) == NULL )
    { return false; }
    xWarFightSetting.SetDayOfWeek( nValue );

    if ( pWarFight->Attribute( "PrepareHour", &nValue ) == NULL )
    { return false; }
    xWarFightSetting.SetPrepareHour( nValue );

    if ( pWarFight->Attribute( "PrepareMinute", &nValue ) == NULL )
    { return false; }
    xWarFightSetting.SetPrepareMinute( nValue );

    if ( pWarFight->Attribute( "StartHour", &nValue ) == NULL )
    { return false; }
    xWarFightSetting.SetStartHour( nValue );

    if ( pWarFight->Attribute( "StartMinute", &nValue ) == NULL )
    { return false; }
    xWarFightSetting.SetStartMinute( nValue );

    if ( pWarFight->Attribute( "EndHour", &nValue ) == NULL )
    { return false; }
    xWarFightSetting.SetEndHour( nValue );

    if ( pWarFight->Attribute( "EndMinute", &nValue ) == NULL )
    { return false; }
    xWarFightSetting.SetEndMinute( nValue );

    if ( pWarFight->Attribute( "CountryScore", &nValue ) == NULL )
    { return false; }
    xWarFightSetting.SetCountryScore( nValue );

    if ( pWarFight->Attribute( "MaxScore", &nValue ) == NULL )
    { return false; }
    xWarFightSetting.SetMaxCountryScore( nValue );

    if ( pWarFight->Attribute( "LevelLimit", &nValue ) == NULL )
    { return false; }
    xWarFightSetting.SetLevelLimit( nValue );

    //复活设置
    MeXmlElement* pReliveSetting = pCountry->FirstChildElement( "ReliveSystem" );
    if ( pReliveSetting == NULL )
    { return false; }

    if ( pReliveSetting->Attribute( "ReliveTime", &nValue ) == NULL )
    { return false; }
    xReliveSetting.SetReliveTime(nValue);

    if ( pReliveSetting->Attribute( "LevelLimit", &nValue ) == NULL )
    { return false; }
    xReliveSetting.SetLevelLimit(nValue);

    if ( pReliveSetting->Attribute( "BeforeLevelLimit", &nValue ) == NULL )
    { return false; }
    xReliveSetting.SetBeforeLevelLimit(nValue);

    if ( pReliveSetting->Attribute( "AfterLevelLimit", &nValue ) == NULL )
    { return false; }
    xReliveSetting.SetAfterLevelLimit(nValue);
	if ( pReliveSetting->Attribute( "ReliveMoney", &nValue ) == NULL )
	{ nValue=20; }
	xReliveSetting.SetReliveMoney(nValue);
	if ( pReliveSetting->Attribute( "PerReliveMoney", &nValue ) == NULL )
	{ nValue=20; }
	xReliveSetting.SetPerReliveMoney(nValue);

	if ( pReliveSetting->Attribute( "FullHpMpRand", &nValue ) == NULL )
	{
		nValue = 0;
	}
	if (nValue>100 || nValue<0)
	{
		nValue = 0;
	}
	xReliveSetting.SetFullHpMpRand(nValue);

	if ( pReliveSetting->Attribute( "BaoZouRand", &nValue ) == NULL )
	{
		nValue = 0;
	}
	if (nValue>100 || nValue<0)
	{
		nValue = 0;
	}
	xReliveSetting.SetBaoZouRand(nValue);
	if ( pReliveSetting->Attribute( "TrueBZRand", &nValue ) == NULL )
	{
		nValue = 0;
	}
	if (nValue>100 || nValue<0)
	{
		nValue = 0;
	}
	xReliveSetting.SetTrueBZRand(nValue);
	
	if (pReliveSetting->Attribute( "BuffStatusID1", &nValue ) == NULL)
	{
		nValue = 0;
	}
	xReliveSetting.SetBuffStatusID1(nValue);
	if (pReliveSetting->Attribute( "BuffStatusLV1", &nValue ) == NULL)
	{
		nValue = 0;
	}
	xReliveSetting.SetBuffStatusLV1(nValue);
	if (pReliveSetting->Attribute( "BuffStatusID2", &nValue ) == NULL)
	{
		nValue = 0;
	}
	xReliveSetting.SetBuffStatusID2(nValue);
	if (pReliveSetting->Attribute( "BuffStatusLV2", &nValue ) == NULL)
	{
		nValue = 0;
	}
	xReliveSetting.SetBuffStatusLV2(nValue);

	if (pReliveSetting->Attribute( "LevelReviceMoney", &nValue ) == NULL)
	{
		nValue = 0;
	}
	xReliveSetting.SetLevelReviceMoney(nValue);

	if (pReliveSetting->Attribute( "ReviceSumMoney", &nValue ) == NULL)
	{
		nValue = 0;
	}
	xReliveSetting.SetReviceSumMoney(nValue);

	if (pReliveSetting->Attribute( "ReviceMaxMoneySum", &nValue ) == NULL)
	{
		nValue = 0;
	}
	xReliveSetting.SetReviceMaxMoneySum(nValue);

	if (pReliveSetting->Attribute( "ItemId", &nValue ) == NULL)
	{
		nValue = -1;
	}
	xReliveSetting.SetReliveItemId(nValue);

	if (pReliveSetting->Attribute( "ItemCount", &nValue ) == NULL)
	{
		nValue = 0;
	}
	xReliveSetting.SetReliveItemCount(nValue);
	
	MeXmlElement* pReivelLevel = pReliveSetting->FirstChildElement( "ReliveLevel" );
    while ( pReivelLevel != NULL )
    {
        int Level = 0;
		if (pReivelLevel->Attribute( "Level", &Level ) == NULL)
		{
			Level = 0;
		}

		int Sum  = 0;
		if (pReivelLevel->Attribute( "Sum", &Sum ) == NULL)
		{
			Sum = 0;
		}
		xReliveSetting.AddRevileLevel(Level,Sum);
        pReivelLevel = pReivelLevel->NextSiblingElement();
    }


	//随机奖励
	MeXmlElement* pRandReward = pCountry->FirstChildElement( "RandJoinReword" );
	if ( pRandReward == NULL )
	{ return false; }

	if ( pRandReward->Attribute( "RewardID", &nValue ) == NULL )
	{ nValue=0; }
	xRandJoinReward.SetRewardID(nValue);

    return true;
}
int CountryConfig::ReliveSetting::GetReilvelSum(int Level) const
{
	//根据等级获取复活次数
	if(ReliveLevelLimit.empty()) return 0;
	std::map<int,int>::const_iterator Iter = ReliveLevelLimit.begin();
	for(;Iter != ReliveLevelLimit.end();++Iter)
	{
		if(Level <= Iter->first)
			return Iter->second;
	}
	return 0;
}
int CountryConfig::ReliveSetting::GetReviceMoney(int Level,int ReviceSum) const
{
	int sum = GetReilvelSum(Level);
	if(ReviceSum< sum)
		return 0;//免费的
	int a = Level * GetLevelReviceMoney();
	int b = GetReviceSumMoney();
	int c = min((ReviceSum - sum),GetReviceMaxMoneySum());
	int Money = a * (1 + b*c);
	return Money;
}