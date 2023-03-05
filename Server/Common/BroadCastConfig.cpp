#include "BroadCastConfig.h"
#include "tstring.h"
#include "BroadCastManager.h"

BroadCastConfig::BroadCastConfig()
{

}

BroadCastConfig::~BroadCastConfig()
{
	m_vecType0.clear();
	m_vecType1.clear();
	m_vecType2.clear();
	m_vecType3.clear();
	m_vecType4.clear();
}

void BroadCastConfig::LoadTimeYear( TimeYear& timeYear, TimeYear& timeEnd, TimeStartEnd& timeSE, MeXmlElement* pYear )
{
	if ( !pYear )
		return;

	Common::_tstring strTimeStart;
	strTimeStart.fromUTF8(pYear->Attribute("StartTime"));
	if ( !strTimeStart.empty() )
	{
		char *szSpn = ".";
		char *szStr;
		int i = 0;

		szStr = strtok( const_cast<char*>(strTimeStart.c_str()),szSpn );
		while( szStr )
		{
			switch (i)
			{
			case 0:
				timeYear.nYear = atoi(szStr);
				break;
			case 1:
				timeYear.nMonth = atoi(szStr);
				break;
			case 2:
				timeYear.nDay = atoi(szStr);
				break;
			case 3:
				timeYear.nHour = atoi(szStr);
				break;
			case 4:
				timeYear.nMinute = atoi(szStr);
				break;
			case 5:
				timeYear.nSecond = atoi(szStr);
				break;
			default:
				break;
			}

			szStr = strtok( NULL,szSpn );
			++i;
		}
	}

	Common::_tstring strTimeEnd;
	strTimeEnd.fromUTF8(pYear->Attribute("EndTime"));
	if ( !strTimeEnd.empty() )
	{
		char *szSpn = ".";
		char *szStr;
		int i = 0;

		szStr = strtok( const_cast<char*>(strTimeEnd.c_str()),szSpn );
		while( szStr )
		{
			switch (i)
			{
			case 0:
				timeEnd.nYear = atoi(szStr);
				break;
			case 1:
				timeEnd.nMonth = atoi(szStr);
				break;
			case 2:
				timeEnd.nDay = atoi(szStr);
				break;
			case 3:
				timeEnd.nHour = atoi(szStr);
				break;
			case 4:
				timeEnd.nMinute = atoi(szStr);
				break;
			case 5:
				timeEnd.nSecond = atoi(szStr);
				break;
			default:
				break;
			}

			szStr = strtok( NULL,szSpn );
			++i;
		}
	}

	TimeEx startTime( timeYear.nYear, timeYear.nMonth, timeYear.nDay, timeYear.nHour, timeYear.nMinute, timeYear.nSecond );
	TimeEx endTime( timeEnd.nYear, timeEnd.nMonth, timeEnd.nDay, timeEnd.nHour, timeEnd.nMinute, timeEnd.nSecond );

	timeSE.nStart = startTime.GetTime();
	timeSE.nEnd = endTime.GetTime();
}

void BroadCastConfig::LoadTimeDay( TimeDay& timeDay, MeXmlElement* pDay )
{
	if ( !pDay )
		return;

	Common::_tstring strTime;
	strTime.fromUTF8(pDay->Attribute("Time"));
	if ( !strTime.empty() )
	{
		char *szSpn = ".";
		char *szStr;
		int i = 0;

		szStr = strtok( const_cast<char*>(strTime.c_str()),szSpn );
		while( szStr )
		{
			switch (i)
			{
			case 0:
				timeDay.nHour = atoi(szStr);
				break;
			case 1:
				timeDay.nMinute = atoi(szStr);
				break;
			case 2:
				timeDay.nSecond = atoi(szStr);
				break;
			default:
				break;
			}

			szStr = strtok( NULL,szSpn );
			++i;
		}
	}
}

bool BroadCastConfig::LoadBroadCastConfig( const char* pszConfig )
{
	if (!pszConfig || *pszConfig == 0)
		return false;

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszConfig))
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;

	MeXmlElement* pType0 = pRoot->FirstChildElement("TipsType0");
	if ( pType0 )
	{
		MeXmlElement* pTip = pType0->FirstChildElement("Tip");
		while ( pTip )
		{
			DataType0 typeData;

			int nType = -1;
			if ( !pTip->Attribute("Type", &nType) )
				return false;
			typeData.mCommon.nType = nType;

			LoadTimeYear( typeData.mStartTime, typeData.mEndTime, typeData.mSETime, pTip );

			int nSpaceTime = 0;
			if ( !pTip->Attribute("SpaceTime", &nSpaceTime) )
				return false;
			typeData.nSpaceTime = nSpaceTime;

			typeData.mCommon.strTip = pTip->Attribute("String");

			_time64( &typeData.mLastTime );

			m_vecType0.push_back( typeData );

			pTip = pTip->NextSiblingElement();
		}
	}

	MeXmlElement* pType1 = pRoot->FirstChildElement("TipsType1");
	if ( pType1 )
	{
		MeXmlElement* pTip = pType1->FirstChildElement("Tip");
		while ( pTip )
		{
			DataType1 typeData;

			int nType = -1;
			if ( !pTip->Attribute("Type", &nType) )
				return false;
			typeData.mCommon.nType = nType;

			LoadTimeYear( typeData.mStartTime, typeData.mEndTime, typeData.mSETime, pTip );

			LoadTimeDay( typeData.mTime, pTip );

			typeData.mCommon.strTip = pTip->Attribute("String");

			m_vecType1.push_back( typeData );

			pTip = pTip->NextSiblingElement();
		}
	}

	MeXmlElement* pType2 = pRoot->FirstChildElement("TipsType2");
	if ( pType2 )
	{
		MeXmlElement* pTip = pType2->FirstChildElement("Tip");
		while ( pTip )
		{
			DataType2 typeData;

			int nType = -1;
			if ( !pTip->Attribute("Type", &nType) )
				return false;
			typeData.mCommon.nType = nType;

			LoadTimeYear( typeData.mStartTime, typeData.mEndTime, typeData.mSETime, pTip );

			int nWeek = 0;
			if ( !pTip->Attribute("Week", &nWeek) )
				return false;
			typeData.nWeek = nWeek + 1;

			int nSpaceTime = 0;
			if ( !pTip->Attribute("SpaceTime", &nSpaceTime) )
				return false;
			typeData.nSpaceTime = nSpaceTime;

			typeData.mCommon.strTip = pTip->Attribute("String");

			_time64( &typeData.mLastTime );

			m_vecType2.push_back( typeData );

			pTip = pTip->NextSiblingElement();
		}
	}

	MeXmlElement* pType3 = pRoot->FirstChildElement("TipsType3");
	if ( pType3 )
	{
		MeXmlElement* pTip = pType3->FirstChildElement("Tip");
		while ( pTip )
		{
			DataType3 typeData;

			int nType = -1;
			if ( !pTip->Attribute("Type", &nType) )
				return false;
			typeData.mCommon.nType = nType;

			LoadTimeYear( typeData.mStartTime, typeData.mEndTime, typeData.mSETime, pTip );

			int nWeek = 0;
			if ( !pTip->Attribute("Week", &nWeek) )
				return false;
			typeData.nWeek = nWeek + 1;

			LoadTimeDay( typeData.mTime, pTip );

			typeData.mCommon.strTip = pTip->Attribute("String");

			m_vecType3.push_back( typeData );

			pTip = pTip->NextSiblingElement();
		}
	}

	MeXmlElement* pType4 = pRoot->FirstChildElement("TipsType4");
	if ( pType4 )
	{
		MeXmlElement* pTip = pType4->FirstChildElement("Tip");
		while ( pTip )
		{
			DataType4 typeData;

			int nType = -1;
			if ( !pTip->Attribute("Type", &nType) )
				return false;
			typeData.mCommon.nType = nType;

			int nMonsterID = -1;
			if ( !pTip->Attribute("MonsterID", &nMonsterID) )
				return false;
			typeData.nMonsterID = nMonsterID;

			int nMapID = -1;
			if ( !pTip->Attribute("MapID", &nMapID) )
				return false;
			typeData.nMapID = nMapID;

			int nSpaceTime = 0;
			if ( !pTip->Attribute("SpaceTime", &nSpaceTime) )
				return false;
			typeData.nSpaceTime = nSpaceTime;

			typeData.mCommon.strTip = pTip->Attribute("String");

			_time64( &typeData.mLastTime );

			m_vecType4.push_back( typeData );

			pTip = pTip->NextSiblingElement();
		}
	}

	theBroadCastManager.UpdataData();

	return true;
}