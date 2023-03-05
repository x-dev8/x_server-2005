#include "CampCountryBattleConfig.h"

bool CampCountryBattleConfig::LoadConfig( const char* szFile,unsigned char countryid)
{
    if ( !CampBattleConfig::LoadConfig( szFile ,countryid) )
    { return false; }

    if ( szFile == NULL || szFile[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pGuildBattle = pRoot->FirstChildElement( "BattleSettings" );
	//zhuxincong �޸���Config�Ķ�ȡ��֮ǰ��3�����Ҷ�һ�����ϣ����ǻᵼ��ÿ�ζ�ֻ�ܶ�ȡ���һ�����ҵ����ã�
	//�����޸ĳɰ���ÿ�����ҵ�ID����ȡ����
	while (pGuildBattle)
	{
		int nValueCountry = CountryDefine::Country_Init;
		if ( pGuildBattle->Attribute( "CountryId", &nValueCountry ) == NULL )
		{ return false; }

		if (nValueCountry != CountryDefine::Country_Init&&nValueCountry != countryid)
		{
			pGuildBattle = pGuildBattle->NextSiblingElement("BattleSettings");
			continue;
		}

		int nValue = 0;

		// �����趨
		MeXmlElement* pSignUpSetting = pGuildBattle->FirstChildElement( "SignUpSetting" );
		if ( pSignUpSetting == NULL )
		{ return false; }

		if ( pSignUpSetting->Attribute( "GuildLevel", &nValue ) == NULL )
		{ return false; }
		xSignUpSetting.SetMinGuildLevel( nValue );

		if ( pSignUpSetting->Attribute( "MemberCount", &nValue ) == NULL )
		{ return false; }
		xSignUpSetting.SetMinMemberCount( nValue );

		if ( pSignUpSetting->Attribute( "CostGuildMoney", &nValue ) == NULL )
		{ return false; }
		xSignUpSetting.SetCostGuildMoney( nValue );

		//�����趨
		MeXmlElement* pEnterSetting = pGuildBattle->FirstChildElement("EnterSetting");
		if (pEnterSetting == NULL)
		{ return false; }

		if (pEnterSetting->Attribute("MaxCount", &nValue) == NULL)
		{ return false; }
		xEnterSetting.SetMaxEnterCount(nValue);

		if (pEnterSetting->Attribute("MinLevel", &nValue) == NULL)
		{ return false; }
		xEnterSetting.SetMinEnterLevel(nValue);

		// ���������趨
		MeXmlElement* pDeathSetting = pGuildBattle->FirstChildElement( "Death" );
		if ( pDeathSetting == NULL )
		{ return false; }

		if ( pDeathSetting->Attribute( "MaxCount", &nValue ) == NULL )
		{ return false; }
		nMaxDeathCount = nValue;

		if(pDeathSetting->Attribute("MaxScore",&nValue) == NULL)
		{return false;}
		nMaxScore = nValue;
		nRedScore = 0;
		nBlueScore = 0;

		return true;		
	}
	return false;
}