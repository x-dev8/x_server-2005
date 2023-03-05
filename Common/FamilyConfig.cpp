#include "FamilyConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"


const FamilyConfig::AttrSetting* FamilyConfig::GetAttrSettingByLevel( unsigned char nLevel )
{
	AttrSettingContainerItr itr = _attrSettings.begin();
	AttrSettingContainerItr endItr = _attrSettings.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( itr->GetFamilyLevel() == nLevel )
		{
			return &*itr;
		}
	}

	return NULL;
}

bool FamilyConfig::LoadConfig( const char* szFile )
{
	if ( szFile == NULL || szFile[ 0 ] == 0 )
	{ return false; }

	MeXmlDocument xMeXml;
	if ( !xMeXml.LoadFile( szFile, 1 ) )
	{ return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
	if ( pRoot == NULL )
	{ return false; }

	MeXmlElement* pFamilySettings = pRoot->FirstChildElement( "FamilySettings" );
	if ( pFamilySettings == NULL )
	{ return false; }

	int nValue = 0;

	// 创建家族设定
	MeXmlElement* pCreateFamily = pFamilySettings->FirstChildElement( "CreateFamily" );
	if ( pCreateFamily == NULL )
	{ return false; }

	if ( pCreateFamily->Attribute( "Level", &nValue ) == NULL )
	{ return false; }
	_createSetting.SetLevel( nValue );

	if ( pCreateFamily->Attribute( "CostMoney", &nValue ) == NULL )
	{ return false; }
	_createSetting.SetCostMoney( nValue );

	// 加入家族设定
	MeXmlElement* pJoinFamily = pFamilySettings->FirstChildElement( "JoinFamily" );
	if ( NULL == pJoinFamily )
	{ return false; }

	if ( pJoinFamily->Attribute( "LevelLimit", &nValue ) == NULL )
	{ return false; }
	_joinSetting.SetLevelLimit( nValue );

	// 家族繁荣度设定
	MeXmlElement* pProperitySetting = pFamilySettings->FirstChildElement( "ProsperitySetting" );
	if ( NULL == pProperitySetting )
	{ return false; }

	if ( pProperitySetting->Attribute( "DayAdd", &nValue ) == NULL )
	{ return false; }
	_prosperitySetting.SetProsPerDay( nValue );

	if ( pProperitySetting->Attribute( "WeekSub", &nValue ) == NULL )
	{ return false; }
	_prosperitySetting.SetProsPerWeek( nValue );


	// 家族属性设定
	MeXmlElement* pFamilyAttrs = pFamilySettings->FirstChildElement( "FamilyAttrs" );
	if ( pFamilyAttrs == NULL )
	{ return false; }

	_attrSettings.clear();
	_attrSettings.push_back( AttrSetting() );
	MeXmlElement* pAttr = pFamilyAttrs->FirstChildElement( "Attr" );
	while ( pAttr != NULL )
	{
		AttrSetting attr;

		if ( pAttr->Attribute( "FamilyLevel", &nValue ) == NULL )
		{ return false; }
		attr.SetFamilyLevel( nValue );

		if ( pAttr->Attribute( "ProsperityNeed", &nValue ) == NULL )
		{ return false; }
		attr.SetProsperityNeed( nValue );

		if ( pAttr->Attribute( "CostMoeny", &nValue ) == NULL )
		{ return false; }
		attr.SetCostMoney( nValue );

		if ( pAttr->Attribute( "MemberCountLimit", &nValue ) == NULL )
		{ return false; }
		attr.SetMemberCountLimit( nValue );

		_attrSettings.push_back( attr );

		pAttr = pAttr->NextSiblingElement();
	}

	// 解散家族设定
	MeXmlElement* pDisbandFamily = pFamilySettings->FirstChildElement( "DisbandFamily" );
	if ( NULL == pDisbandFamily )
	{ return false; }

	if ( pDisbandFamily->Attribute( "KeepTime", &nValue ) == NULL )
	{ return false; }
	_disbandSetting.SetFamilyKeepTime( nValue );

	// 玩家离开设定
	MeXmlElement* pMmeberLeave = pFamilySettings->FirstChildElement( "MemberLeave" );
	if ( NULL == pMmeberLeave )
	{ return false; }

	if ( pMmeberLeave->Attribute( "LeaveTime", &nValue ) == NULL )
	{ return false; }
	_memberLeaveSetting.SetLeaveSettingTime( nValue );

	// 玩家更改宗旨设定
	MeXmlElement* pChangeAim = pFamilySettings->FirstChildElement( "ChangeAim" );
	if ( NULL == pChangeAim )
	{ return false; }

	if ( pChangeAim->Attribute( "CD", &nValue ) == NULL )
	{ return false; }
	_changeAimSetting.SetChangeAimCD( nValue );

	if ( pChangeAim->Attribute( "Cost", &nValue ) == NULL )
	{ return false; }
	_changeAimSetting.SetChangeAimCost( nValue );

	// 家族消息相关输入的字符长度设定
	int nMaxVal = 0;
	int nMinVal = 0;

	MeXmlElement* pValueElement = pFamilySettings->FirstChildElement( "FamilyNameLen" );
	if ( NULL == pValueElement )
	{return false;}
	if ( pValueElement->Attribute( "max", &nMaxVal ) == NULL )
	{return false;}
	if ( pValueElement->Attribute( "min", &nMinVal ) == NULL )
	{return false;}
	_familyWordsLen.SetNameLenMax(nMaxVal);
	_familyWordsLen.SetNameLenMin(nMinVal);

	pValueElement = pFamilySettings->FirstChildElement( "FamilyAimLen" );
	if ( NULL == pValueElement )
	{return false;}
	if ( pValueElement->Attribute( "max", &nMaxVal ) == NULL )
	{return false;}
	if ( pValueElement->Attribute( "min", &nMinVal ) == NULL )
	{return false;}
	_familyWordsLen.SetAimLenMax(nMaxVal);
	_familyWordsLen.SetAimLenMin(nMinVal);

	pValueElement = pFamilySettings->FirstChildElement( "FamilyRequestMsgLen" );
	if ( NULL == pValueElement )
	{return false;}
	if ( pValueElement->Attribute( "max", &nMaxVal ) == NULL )
	{return false;}
	if ( pValueElement->Attribute( "min", &nMinVal ) == NULL )
	{return false;}
	_familyWordsLen.SetRequestMsgLenMax(nMaxVal);
	_familyWordsLen.SetRequestMsgLenMin(nMinVal);

	pValueElement = pFamilySettings->FirstChildElement( "FamilyNoteLen" );
	if ( NULL == pValueElement )
	{return false;}
	if ( pValueElement->Attribute( "max", &nMaxVal ) == NULL )
	{return false;}
	if ( pValueElement->Attribute( "min", &nMinVal ) == NULL )
	{return false;}
	_familyWordsLen.SetNoteLenMax(nMaxVal);
	_familyWordsLen.SetNoteLenMin(nMinVal);

	return true;
}
