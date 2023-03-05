#include "WorldBattleConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "CountryDefine.h"
bool WorldBattleConfig::LoadFilePath(const char* szFile)
{
	//��ȡ�����ļ�
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(szFile)) return false;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("WorldBattle");
	if(pRoot != NULL)
	{
		//��ȡҰ��ս���Ļ���������Ϣ
		//1. ׼��ʱ�� ��ʼʱ�� ����ʱ�� 3���׶� ���ж�ȡ
		MeXmlElement* pTimeSettings = pRoot->FirstChildElement( "TimeSettings" );
		if ( pTimeSettings == NULL )
			return false;
		MeXmlElement* pTime = pTimeSettings->FirstChildElement( "TimeSetting" );
		while( pTime != NULL )
		{
			TimeSetting xSetting;
			MeXmlElement* pSignUp = pTime->FirstChildElement( "PrepareTime" );
			if ( pSignUp == NULL )
			{ return false; }

			int nValue = 0;	
			if ( pSignUp->Attribute( "DayOfWeek", &nValue ) == NULL )
			{ return false; }
			xSetting.SetDayOfWeek( nValue );

			if ( pSignUp->Attribute( "Hour", &nValue ) == NULL )
			{ return false; }
			xSetting.SetHour( nValue );

			if ( pSignUp->Attribute( "Minute", &nValue ) == NULL )
			{ return false; }
			xSetting.SetMinute( nValue );

			if ( pSignUp->Attribute( "KeepTime", &nValue ) == NULL )
			{ return false; }
			xSetting.SetKeepTime( nValue );
			vecPrepareTimeSetting.push_back( xSetting );

			MeXmlElement* pPrepare = pTime->FirstChildElement( "FightTime" );
			if ( pPrepare == NULL )
			{ return false; }

			if ( pPrepare->Attribute( "DayOfWeek", &nValue ) == NULL )
			{ return false; }
			xSetting.SetDayOfWeek( nValue );

			if ( pPrepare->Attribute( "Hour", &nValue ) == NULL )
			{ return false; }
			xSetting.SetHour( nValue );

			if ( pPrepare->Attribute( "Minute", &nValue ) == NULL )
			{ return false; }
			xSetting.SetMinute( nValue );

			if ( pPrepare->Attribute( "KeepTime", &nValue ) == NULL )
			{ return false; }
			xSetting.SetKeepTime( nValue );
			vecFightTimeSetting.push_back( xSetting );

			MeXmlElement* pEnter = pTime->FirstChildElement( "EndTime" );
			if ( pEnter == NULL )
			{ return false; }

			if ( pEnter->Attribute( "DayOfWeek", &nValue ) == NULL )
			{ return false; }
			xSetting.SetDayOfWeek( nValue );

			if ( pEnter->Attribute( "Hour", &nValue ) == NULL )
			{ return false; }
			xSetting.SetHour( nValue );

			if ( pEnter->Attribute( "Minute", &nValue ) == NULL )
			{ return false; }
			xSetting.SetMinute( nValue );

			if ( pEnter->Attribute( "KeepTime", &nValue ) == NULL )
			{ return false; }
			xSetting.SetKeepTime( nValue );
			vecEndTimeSetting.push_back( xSetting );

			pTime = pTime->NextSiblingElement();
		}
		//��������
		MeXmlElement* pMonsters = pTimeSettings->FirstChildElement( "Monsters" );
		while(pMonsters !=NULL)
		{
			int CountryID = CountryDefine::Country_Init;
			
			if ( pMonsters->Attribute( "ID", &CountryID ) == NULL )
			{
				pMonsters = pMonsters->NextSiblingElement();
				continue;
			}

			MeXmlElement* pMonster = pMonsters->FirstChildElement( "Monster" );
			while(pMonster != NULL)
			{
				//��ȡ���������
				MonsterCreateData xCreateData;
				
				int TypeID = 0;
				if ( pMonster->Attribute( "ID", &TypeID ) == NULL )
				{
					pMonster = pMonster->NextSiblingElement();
					continue;
				}
				float x = 0;
				if ( pMonster->Attribute( "x", &x ) == NULL )
				{
					pMonster = pMonster->NextSiblingElement();
					continue;
				}

				float y = 0;
				if ( pMonster->Attribute( "y", &y ) == NULL )
				{
					pMonster = pMonster->NextSiblingElement();
					continue;
				}

				float radio = 0;
				if ( pMonster->Attribute( "radio", &radio ) == NULL )
				{
					pMonster = pMonster->NextSiblingElement();
					continue;
				}

				float dirx = 0;
				if ( pMonster->Attribute( "dirx", &dirx ) == NULL )
				{
					pMonster = pMonster->NextSiblingElement();
					continue;
				}
				float diry = 0;
				if ( pMonster->Attribute( "diry", &diry ) == NULL )
				{
					pMonster = pMonster->NextSiblingElement();
					continue;
				}
				int routeID = 0;
				if ( pMonster->Attribute( "routeID", &routeID ) == NULL )
				{
					pMonster = pMonster->NextSiblingElement();
					continue;
				}
				int countryID = 0;
				if ( pMonster->Attribute( "countryID", &countryID ) == NULL )
				{
					pMonster = pMonster->NextSiblingElement();
					continue;
				}
				xCreateData.SetMapID( GetMapID() );//��ͼID
				xCreateData.SetCreateType( 0 );//������ʽ
				xCreateData.SetCount( 1 );//����
				xCreateData.SetRadius( radio);//��Χ
				xCreateData.SetFightCamp( 0 );//��Ӫ
				xCreateData.SetCountry(countryID);
				xCreateData.SetMonsterID( TypeID );//����ID
				xCreateData.SetPostionX( x);
				xCreateData.SetPostionY( y );
				xCreateData.SetDirX( dirx );
				xCreateData.SetDirY( diry );
				xCreateData.SetRouteID( routeID );
				
				switch(countryID)
				{
				case CountryDefine::Country_Init:
					m_NonCountry.push_back(xCreateData);
					break;
				case CountryDefine::Country_LouLan:
					m_WeiCountry.push_back(xCreateData);
					break;
				case CountryDefine::Country_KunLun:
					m_ShuCountry.push_back(xCreateData);
					break;
				case CountryDefine::Country_DunHuang:
					m_WuCountry.push_back(xCreateData);
					break;
				}

				pMonster = pMonster->NextSiblingElement();
			}
		}
	}
	return true;
}
std::vector<MonsterCreateData>& WorldBattleConfig::GetMonstData(unsigned int CountryID)
{
	switch(CountryID)
	{
	case CountryDefine::Country_Init:
		return m_NonCountry;
		break;
	case CountryDefine::Country_LouLan:
		return m_WeiCountry;
		break;
	case CountryDefine::Country_KunLun:
		return m_ShuCountry;
		break;
	case CountryDefine::Country_DunHuang:
		return m_WuCountry;
		break;
	default:
		return m_NonCountry;
		break;
	}
}
bool WorldBattleConfig::CheckPrepareTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
	//��鵱ǰʱ���Ƿ���ָ�����õ�ʱ��
	for ( TimeSettingVectorIter iter = vecPrepareTimeSetting.begin(); iter != vecPrepareTimeSetting.end(); ++iter )
    {
        if ( ( iter->GetMinute() == nMinute ) && ( iter->GetHour() == nHour ) && ( iter->GetDayOfWeek() == nDayOfWeek ) )
        { return true; }
    }
    return false;
}
bool WorldBattleConfig::CheckFightTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
	for ( TimeSettingVectorIter iter = vecFightTimeSetting.begin(); iter != vecFightTimeSetting.end(); ++iter )
    {
        if ( ( iter->GetMinute() == nMinute ) && ( iter->GetHour() == nHour ) && ( iter->GetDayOfWeek() == nDayOfWeek ) )
        { return true; }
    }
    return false;
}
bool WorldBattleConfig::CheckEndTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
	for ( TimeSettingVectorIter iter = vecEndTimeSetting.begin(); iter != vecEndTimeSetting.end(); ++iter )
    {
        if ( ( iter->GetMinute() == nMinute ) && ( iter->GetHour() == nHour ) && ( iter->GetDayOfWeek() == nDayOfWeek ) )
        { return true; }
    }
    return false;
}