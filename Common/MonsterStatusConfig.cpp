#include "MonsterStatusConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "GlobalDef.h"
#include "ItemDetail.h"

const MonsterStatusConfig::StatusData* MonsterStatusConfig::GetStatusData( int nMonsterID ) const
{
    ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonsterById( nMonsterID );
    if ( pMonsterConfig == NULL )
    { return NULL; }

    StatusDataMapIter iter = m_mapStatusConfig.find( nMonsterID );
    if ( iter == m_mapStatusConfig.end() )
    { 
        // 获得副本怪物前4位ID
        unsigned short nLevel = 0;
        nMonsterID = GetEctypeMonsterID( nMonsterID, nLevel );
        iter = m_mapStatusConfig.find( nMonsterID );
        if ( iter == m_mapStatusConfig.end() )
        { return GetStatusDataByType( pMonsterConfig->stMonsterType ); }
    }

    return &( iter->second );
}

const MonsterStatusConfig::StatusData* MonsterStatusConfig::GetStatusDataByType( int nMonsterType ) const
{
    StatusDataMapIter iter = m_mapStatusTypeConfig.find( nMonsterType );
    if ( iter == m_mapStatusTypeConfig.end() )
    { return NULL; }

    return &( iter->second );
}

bool MonsterStatusConfig::LoadConfig( const char* szFile )
{
    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pStatusTypes = pRoot->FirstChildElement( "MonsterStatusTypes" );
    if ( pStatusTypes == NULL )
    { return false; }

    int nValue;
	float fValue;
    MeXmlElement* pMonster = pStatusTypes->FirstChildElement( "Monster" );
    while ( pMonster != NULL )
    { 
        StatusData xData;

        if ( pMonster->Attribute( "ID", &nValue ) == NULL )
        { return false; }
        xData.SetMonsterID( nValue );

        if ( pMonster->Attribute( "InitStatus", &nValue ) == NULL )
        { return false; }
        xData.SetInitStatus( nValue );

        MeXmlElement* pStatus = pMonster->FirstChildElement( "StatusTypes" );
        while ( pStatus != NULL )
        {
            StatusSetting xSetting;

            if ( pStatus->Attribute( "Status", &nValue ) == NULL )
            { return false; }
            xSetting.SetStatus( nValue );

            if ( pStatus->Attribute( "NextStatus", &nValue ) == NULL )
            { return false; }
            xSetting.SetNextStatus( nValue );

            if ( pStatus->Attribute( "SpaceTime", &nValue ) != NULL )
            { xSetting.SetSpaceTime( nValue ); }

            if ( pStatus->Attribute( "ScriptEnter", &nValue ) == NULL )
            { return false; }
            xSetting.SetScriptEnter( nValue );

            if ( pStatus->Attribute( "ModelID", &nValue ) == NULL )
            { return false; }
            xSetting.SetModelID( nValue );

			if ( pStatus->Attribute( "StartAlpha", &fValue ) == NULL )
			{ return false; }
			xSetting.SetStartAlpha( fValue );

			if ( pStatus->Attribute( "EndAlpha", &fValue ) == NULL )
			{ return false; }
			xSetting.SetEndAlpha( fValue );

			if ( pStatus->Attribute( "StartScale", &fValue ) == NULL )
			{ return false; }
			xSetting.SetStartScale( fValue );

			if ( pStatus->Attribute( "EndScale", &fValue ) == NULL )
			{ return false; }
			xSetting.SetEndScale( fValue );

			if ( pStatus->Attribute( "StartOffsetX", &fValue ) == NULL )
			{ return false; }
			xSetting.SetStartOffsetX( fValue );

			if ( pStatus->Attribute( "EndOffsetX", &fValue ) == NULL )
			{ return false; }
			xSetting.SetEndOffsetX( fValue );

			if ( pStatus->Attribute( "StartOffsetY", &fValue ) == NULL )
			{ return false; }
			xSetting.SetStartOffsetY( fValue );

			if ( pStatus->Attribute( "EndOffsetY", &fValue ) == NULL )
			{ return false; }
			xSetting.SetEndOffsetY( fValue );

			if ( pStatus->Attribute( "StartOffsetZ", &fValue ) == NULL )
			{ return false; }
			xSetting.SetStartOffsetZ( fValue );

			if ( pStatus->Attribute( "EndOffsetZ", &fValue ) == NULL )
			{ return false; }
			xSetting.SetEndOffsetZ( fValue );

            Common::_tstring strEffect;
            strEffect.fromUTF8( pStatus->Attribute("Effect") );
            xSetting.SetEffect( strEffect.c_str() );

			MeXmlElement* pSect = pStatus->FirstChildElement("Sect");
			while(pSect)
			{
				StatusSect sect;
				Common::_tstring strTemp;
				strTemp.fromUTF8( pSect->Attribute("Action") );
				sect.m_strAction = strTemp;
				strTemp.fromUTF8( pSect->Attribute("Effect") );
				sect.m_strEffect = strTemp;
				
				if ( pSect->Attribute( "TalkString", &nValue )  )
				{
					sect.m_StringId = nValue;
				}
				if ( pSect->Attribute( "KeepTime", &nValue )  )
				{
					sect.m_nKeepTime = nValue;
				}
				xSetting.GetArrStatusSect().push_back(sect);
				pSect = pSect->NextSiblingElement( "Sect" );
			}
            xData.AddStatusSetting( xSetting );

            pStatus = pStatus->NextSiblingElement( "StatusTypes" );
        }

        AddStatusData( xData );

        pMonster = pMonster->NextSiblingElement( "Monster" );
    }

    MeXmlElement* pMonsterType = pStatusTypes->FirstChildElement( "MonsterType" );
    while ( pMonsterType != NULL )
    { 
        StatusData xData;

        Common::_tstring strTemp;
        strTemp.fromUTF8( pMonsterType->Attribute("Type") );
        nValue = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(), ItemDefine::g_szMonsterType, sizeof(ItemDefine::g_szMonsterType)/sizeof( char* ) );
        xData.SetMonsterType( nValue );

        if ( pMonsterType->Attribute( "InitStatus", &nValue ) == NULL )
        { return false; }
        xData.SetInitStatus( nValue );

        MeXmlElement* pStatus = pMonsterType->FirstChildElement( "StatusTypes" );
        while ( pStatus != NULL )
        {
            StatusSetting xSetting;

            if ( pStatus->Attribute( "Status", &nValue ) == NULL )
            { return false; }
            xSetting.SetStatus( nValue );

            if ( pStatus->Attribute( "NextStatus", &nValue ) == NULL )
            { return false; }
            xSetting.SetNextStatus( nValue );

            if ( pStatus->Attribute( "SpaceTime", &nValue ) != NULL )
            { xSetting.SetSpaceTime( nValue ); }

            if ( pStatus->Attribute( "ScriptEnter", &nValue ) == NULL )
            { return false; }
            xSetting.SetScriptEnter( nValue );

            if ( pStatus->Attribute( "ModelID", &nValue ) == NULL )
            { return false; }
            xSetting.SetModelID( nValue );

			if ( pStatus->Attribute( "StartAlpha", &fValue ) == NULL )
			{ return false; }
			xSetting.SetStartAlpha( fValue );

			if ( pStatus->Attribute( "EndAlpha", &fValue ) == NULL )
			{ return false; }
			xSetting.SetEndAlpha( fValue );

			if ( pStatus->Attribute( "StartScale", &fValue ) == NULL )
			{ return false; }
			xSetting.SetStartScale( fValue );

			if ( pStatus->Attribute( "EndScale", &fValue ) == NULL )
			{ return false; }
			xSetting.SetEndScale( fValue );

			if ( pStatus->Attribute( "StartOffsetX", &fValue ) == NULL )
			{ return false; }
			xSetting.SetStartOffsetX( fValue );

			if ( pStatus->Attribute( "EndOffsetX", &fValue ) == NULL )
			{ return false; }
			xSetting.SetEndOffsetX( fValue );

			if ( pStatus->Attribute( "StartOffsetY", &fValue ) == NULL )
			{ return false; }
			xSetting.SetStartOffsetY( fValue );

			if ( pStatus->Attribute( "EndOffsetY", &fValue ) == NULL )
			{ return false; }
			xSetting.SetEndOffsetY( fValue );

			if ( pStatus->Attribute( "StartOffsetZ", &fValue ) == NULL )
			{ return false; }
			xSetting.SetStartOffsetZ( fValue );

			if ( pStatus->Attribute( "EndOffsetZ", &fValue ) == NULL )
			{ return false; }
			xSetting.SetEndOffsetZ( fValue );

            Common::_tstring strEffect;
            strEffect.fromUTF8( pStatus->Attribute("Effect") );
            xSetting.SetEffect( strEffect.c_str() );

            MeXmlElement* pSect = pStatus->FirstChildElement("Sect");
            while(pSect)
            {
                StatusSect sect;
                Common::_tstring strTemp;
                strTemp.fromUTF8( pSect->Attribute("Action") );
                sect.m_strAction = strTemp;
                strTemp.fromUTF8( pSect->Attribute("Effect") );
                sect.m_strEffect = strTemp;

                if ( pSect->Attribute( "TalkString", &nValue )  )
                {
                    sect.m_StringId = nValue;
                }
                if ( pSect->Attribute( "KeepTime", &nValue )  )
                {
                    sect.m_nKeepTime = nValue;
                }
                xSetting.GetArrStatusSect().push_back(sect);
                pSect = pSect->NextSiblingElement( "Sect" );
            }
            xData.AddStatusSetting( xSetting );

            pStatus = pStatus->NextSiblingElement( "StatusTypes" );
        }

        AddStatusDataByType( xData );

        pMonsterType = pMonsterType->NextSiblingElement( "MonsterType" );
    }

    return true;
}