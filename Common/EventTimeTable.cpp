#include "EventTimeTable.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include "tstring.h"
#include "helper.h"
#include "NpcInfo.h"
#include "MapConfig.h"
#include "logmgr.h"
#include "LogFileObjectNameEx.h"
#include "application_config.h"
#include "ItemDetail.h"

using namespace Common;

bool EventManager::Load(const std::string& filename, const struct tm& nowtime)
{
	m_hotEventContents.clear();
	m_weekEventContents.clear();
	m_everydayEventContents.clear();

    EventPeriodTypes.clear();
    EventRewardTypes.clear();
	m_AllEventContents.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(filename.c_str()))
		return false;

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;

    MeXmlElement* pPeriodType = pRoot->FirstChildElement("PeriodTypes");
    if (NULL != pPeriodType)
    {
        MeXmlElement* pType = pPeriodType->FirstChildElement("Type");
        while(NULL != pType)
        {
            EventPeriodType type;
            if (pType->Attribute("Id",&type.id) == NULL)
                return false;
            const char* pDescription = pType->Attribute("Description");
            if (NULL != pDescription)
                type.description = _tstring::toNarrowString(_tstring::UTF8towcs(pDescription).c_str());

            EventPeriodTypes.push_back(type);
            pType = pType->NextSiblingElement();
        }
    }

    MeXmlElement* pRewardType = pRoot->FirstChildElement("RewardTypes");
    if (NULL != pRewardType)
    {
        MeXmlElement* pType = pRewardType->FirstChildElement("Type");
        while(NULL != pType)
        {
            EventRewardType type;
            if (pType->Attribute("Id",&type.id) == NULL)
                return false;

            const char* pDescription = pType->Attribute("Description");
            if (NULL != pDescription)
                type.description = _tstring::toNarrowString(_tstring::UTF8towcs(pDescription).c_str());

            EventRewardTypes.push_back(type);
            pType = pType->NextSiblingElement();
        }
    }

	////////////////////////////////////////////////////////////
	MeXmlElement* pCategorys = pRoot->FirstChildElement("Categorys");
	if (NULL != pCategorys)
	{
		MeXmlElement* pType = pCategorys->FirstChildElement("Type");
		while(NULL != pType)
		{
			EventCategorys type;
			if (pType->Attribute("Id",&type.id) == NULL)
				return false;

			const char* pDescription = pType->Attribute("Description");
			if (NULL != pDescription)
				type.description = _tstring::toNarrowString(_tstring::UTF8towcs(pDescription).c_str());

			m_AllCategory.push_back(type);
			pType = pType->NextSiblingElement();
		}
	}
	////////////////////////////////////////////////////////////

	MeXmlElement* pActivityType = pRoot->FirstChildElement("ActivityTypes");
	if (NULL != pActivityType)
	{
		MeXmlElement* pType = pActivityType->FirstChildElement("Type");
		while(NULL != pType)
		{
			EventActivityType type;
			if (pType->Attribute("Id",&type.id) == NULL)
				return false;

			const char* pDescription = pType->Attribute("Description");
			if (NULL != pDescription)
				type.description = _tstring::toNarrowString(_tstring::UTF8towcs(pDescription).c_str());

			m_AllActivityType.push_back(type);
			pType = pType->NextSiblingElement();
		}
	}


    MeXmlElement* pEvents = pRoot->FirstChildElement("Events");
    if (NULL == pEvents)
    {
        return true;
    }

    MeXmlElement* pEvent = pEvents->FirstChildElement("Event");
	while (NULL != pEvent)
	{
        const char* name = pEvent->Attribute("Name");
        if (NULL == name)
            return false;

		Event evt;

        // 增加活动 Id、分类、本日总次数、简述       added by ZhuoMeng.Hu		[11/24/2010]
        if( pEvent->Attribute( "Id", &evt.id ) == NULL )
            return false;

        if( pEvent->Attribute( "Category", &evt.category ) == NULL )
            return false;

		/*
		 * Author: 2012-9-18 10:16:33 liaojie
		 * Desc:   增加国家限制和活动类别
		 */
		int eventTemp = 0;
		pEvent->Attribute( "Country", &eventTemp );
		evt.country = eventTemp;

		if ( pEvent->Attribute( "ActivityType", &evt.mActivityType ) == NULL )
		{
			return false;
		}
			

        const char* szTotalCount = pEvent->Attribute( "TotalCount" );
        if( NULL != szTotalCount )
            evt.totalCount = _tstring::toNarrowString( _tstring::UTF8towcs( szTotalCount ).c_str() );

        const char* szFormulation = pEvent->Attribute( "Formulation" );
        if( NULL != szFormulation )
            evt.formulation = _tstring::toNarrowString( _tstring::UTF8towcs( szFormulation ).c_str() );

        const char* szOpenTime = pEvent->Attribute( "OpenTime" );
        if( NULL != szOpenTime )
            evt.openTime = _tstring::toNarrowString( _tstring::UTF8towcs( szOpenTime ).c_str() );


		const char* szPic = pEvent->Attribute( "PicPath");
		if(NULL != szPic)
			evt.picPath = _tstring::toNarrowString( _tstring::UTF8towcs( szPic ).c_str() );
        
        if (pEvent->Attribute("Year", &evt.year) == NULL)
            return false;

        if (pEvent->Attribute("Month", &evt.month) == NULL)
            return false;

        if (evt.month > 11 ||evt.month < -1)
            evt.month = -1;

        if (pEvent->Attribute("Day", &evt.day) == NULL)
            return false;

        if (pEvent->Attribute("Hour", &evt.hour) == NULL )
            return false;

        if (pEvent->Attribute("Minute", &evt.minute) == NULL)
            return false;

        evt.week = HelperFunc::Ymd2Wday(evt.year,evt.month+1,evt.day);//根据读入的时间算出是周几

        int tempPeriodTypeId;
        if ( NULL == pEvent->Attribute("PeriodTypeId", &tempPeriodTypeId) )
            return false;
        evt.periodTypeId = tempPeriodTypeId;
        
        int tempPeriodTypeVar;
        if ( NULL == pEvent->Attribute("PeriodParameter", &tempPeriodTypeVar) )
            return false;
        evt.periodParameter = tempPeriodTypeVar;

#ifndef __EVENT_EDIT__
		evt.isEveryday = 0;
		if (evt.periodTypeId == 1)
		{
			evt.week = nowtime.tm_wday;
			evt.isEveryday = 1;
		}
#endif
        if (evt.periodTypeId == 2)//每周
        {
            if (evt.periodParameter < -1|| evt.periodParameter > 6)
			{ return false; }
			evt.week = evt.periodParameter;
        }
        else if (evt.periodTypeId == 3)//每月
        {
            if (evt.periodParameter < -1|| evt.periodParameter > 31)
            { return false; }
            if (evt.periodParameter == 0)
			{ evt.periodParameter = -1; }

			// 根据读入的时间算出是周几
			evt.week = HelperFunc::Ymd2Wday(nowtime.tm_year + 1900, nowtime.tm_mon + 1, evt.periodParameter); 
			evt.day = evt.periodParameter;

//#ifndef __EVENT_EDIT__
//			if (nowtime.tm_mday > evt.periodParameter)
//			{
//				int offsetday = nowtime.tm_mday - evt.periodParameter;
//				if (nowtime.tm_wday == 0)
//				{
//					if (offsetday > 6)
//					{
//						pEvent = pEvent->NextSiblingElement();
//						continue; // 不在本周内
//					}
//					evt.week = 7 - offsetday;
//				}
//				else
//				{
//					if (offsetday >= nowtime.tm_wday)
//					{
//						pEvent = pEvent->NextSiblingElement();
//						continue; // 不在本周内
//					}
//					evt.week = nowtime.tm_wday - offsetday;
//				}
//			}
//			else if (nowtime.tm_mday < evt.periodParameter)
//			{
//				int offsetday = evt.periodParameter - nowtime.tm_mday;
//				if (offsetday > abs(nowtime.tm_wday - 7))
//				{
//					pEvent = pEvent->NextSiblingElement();
//					continue; // 不在本周内
//				}
//				evt.week = nowtime.tm_wday + offsetday;
//				if (evt.week >= 7)
//					evt.week = evt.week - 7;
//			}
//			else
//				evt.week = nowtime.tm_wday;
//
//            if (nowtime.tm_mday > evt.periodParameter)
//            {
//                pEvent = pEvent->NextSiblingElement();
//                continue;
//            }
//#endif
        }
        ItrPeriodTypeContainer Itr = find(EventPeriodTypes.begin(),EventPeriodTypes.end(),evt.periodTypeId);
        if (Itr == EventPeriodTypes.end())
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Event %s Not Find PeriodType! PeriodTypeId = %d",evt.name.c_str(),evt.periodTypeId);
            return false;
        }
        evt.period = Itr->description; // 显示使用


		evt.name = _tstring::toNarrowString(_tstring::UTF8towcs(name).c_str());
        if ( NULL == pEvent->Attribute("NeedLevel", &evt.needLevel) )
            return false;
        if ( NULL == pEvent->Attribute("Quality", &evt.quality) )
            return false;
        if ( NULL == pEvent->Attribute("Count", &evt.count) )
            return false;

        int IsHot = 0;
        pEvent->Attribute("IsHot", &IsHot);
        evt.isHot = IsHot < 1?FALSE:TRUE;

        int IsPivot = 0;
        pEvent->Attribute("IsPivot", &IsPivot);
        evt.isPivot = IsPivot < 1?FALSE:TRUE;

        int tempScript = 0;
        if ( NULL == pEvent->Attribute("ScriptId", &tempScript) )
            return false;
        if (tempScript < -1)
            tempScript = -1;
        evt.scriptId = tempScript;

        int tempEventItemId = 0;
        if ( NULL == pEvent->Attribute("EventItemId", &tempEventItemId) )
        { tempEventItemId = InvalidLogicNumber; }
        unsigned short shTempEventItemId = (unsigned short)tempEventItemId;
        ItemDefine::SItemCommon * pItem = GettheItemDetail().GetItemByID(shTempEventItemId);
        if (NULL == pItem)
        { shTempEventItemId = InvalidLogicNumber; }
        evt.eventItemId = shTempEventItemId;

        if ( NULL == pEvent->Attribute("NpcId", &evt.npcId) )
            return false;

        NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(evt.npcId);
        if (NULL != pNpc)
            evt.npc = pNpc->name;

        if ( NULL == pEvent->Attribute("MapId", &evt.mapId) )
            return false;
        MapConfig::MapData* pMap = theMapConfig.GetMapDataById(evt.mapId);
        if (NULL != pMap)
            evt.mapName = pMap->MapName;
        else
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Event %s Not Find Map! MapId = %d",evt.name.c_str(),evt.mapId);
            //return false;
			pEvent = pEvent->NextSiblingElement("Event");
			continue;
        }

        double  mapPosX;
        if ( NULL == pEvent->Attribute("MapPosX", &mapPosX) )
            return false;
        if (mapPosX > pMap->Column*16.0f)
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Event %s Map Size Error! MapId = %d MapPosX = %4.0f",evt.name.c_str(),evt.mapId,mapPosX);
            return false;
        }
        evt.mapPosX = mapPosX;

        double  mapPosY;
        if ( NULL == pEvent->Attribute("MapPosY", &mapPosY) )
            return false;
        if (mapPosY > pMap->Row*16.0f)
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Event %s Map Size Error! MapId = %d MapPosY = %4.0f",evt.name.c_str(),evt.mapId,mapPosY);
            return false;
        }
        evt.mapPosY = mapPosY;


        if ( NULL == pEvent->Attribute("CompleteId", &evt.completeTimeVarIndex) )
            return false;

        const char* var = pEvent->Attribute("Description");
        if (NULL != var)
            evt.description = _tstring::toNarrowString(_tstring::UTF8towcs(var).c_str());

        if (pEvent->Attribute("Duration", &evt.duration) == NULL)
            return false;

        const char* durationDesVar = pEvent->Attribute("DurationDescription");
        if (NULL != durationDesVar)
            evt.durationDescription = _tstring::toNarrowString(_tstring::UTF8towcs(durationDesVar).c_str());

        ////////////////////////////////结束时间////////////////////////////////////
		evt.endWeek = evt.week + evt.duration / (24 * 60);
		evt.endHour = evt.hour + (evt.duration - ( evt.endWeek - evt.week ) * 24 * 60) / 60;
		evt.endMinute = evt.minute + (evt.duration - ( evt.endWeek - evt.week ) * 24 * 60 - ( evt.endHour - evt.hour ) * 60);

		if (evt.endMinute >= 60)
		{
			evt.endMinute = evt.endMinute - 60;
			evt.endHour++;
		}

		if (evt.endHour >= 24)
		{
			evt.endHour = evt.endHour - 24;
			evt.endWeek++;
		}

		if (evt.endWeek >= 7)
		{
			evt.endWeek = evt.endWeek - 7;
		}
        ///////////////////////////////结束时间////////////////////////////////////
        

        MeXmlElement* pBroadcasts = pEvent->FirstChildElement("Broadcasts");
        if (NULL != pBroadcasts)
        {
            MeXmlElement* pBroadcast = pBroadcasts->FirstChildElement("Broadcast");
            while (NULL !=  pBroadcast)
            {
                Event::Broadcast tempBroadcast;
                if ( NULL == pBroadcast->Attribute("OffsetTime",&tempBroadcast.offsetTime) )
                    return false;

                
                 const char* var = pBroadcast->Attribute("Content");
                 if (NULL != var)
                     tempBroadcast.content = _tstring::toNarrowString(_tstring::UTF8towcs(var).c_str());

                evt.broadcast.push_back(tempBroadcast);
                pBroadcast = pBroadcast->NextSiblingElement();
            }
        }
        evt.rewards.clear();
        MeXmlElement* pRewards = pEvent->FirstChildElement("Rewards");
        if (NULL != pRewards)
        {
            MeXmlElement* pReward = pRewards->FirstChildElement("Reward");
            while (NULL !=  pReward)
            {
                Event::Reward rewardItem;
                if ( NULL == pReward->Attribute("TypeId",&rewardItem.typeId) )
                    return false;
                ItrEventRewardTypeContainer Itr = find(EventRewardTypes.begin(),EventRewardTypes.end(),rewardItem.typeId);
                if (Itr == EventRewardTypes.end())
                {
                    LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Event %s Not Find EventRewardTypes! EventRewardType = %d",evt.name.c_str(),rewardItem.typeId);
                    return false;
                }

                if ( NULL == pReward->Attribute("Parameter1",&rewardItem.id) )
                    return false;

                if ( NULL == pReward->Attribute("Parameter2",&rewardItem.count) )
                    return false;

                evt.rewards.push_back(rewardItem);
                pReward = pReward->NextSiblingElement();
            }
        }

        // 这里的逻辑是需要把本周的放入m_weekEventContents，如果是热点的同时需要放入到m_hotEventContents
        if (evt.isHot)
            m_hotEventContents.push_back(evt);
        else //else if ( nowtime.tm_wday == evt.week )// 如果今天有
		{
			if (evt.periodTypeId == 1)
			{
				// 填写一周内的活动
				m_everydayEventContents.push_back(evt);
			}
			else
			{
				ItrPeriodTypeContainer Itr = find(EventPeriodTypes.begin(),EventPeriodTypes.end(),evt.week + 10);
				if (Itr != EventPeriodTypes.end())
					evt.period = Itr->description;
				m_weekEventContents[evt.week].push_back(evt);
			}
		}
        
            

#ifndef __EVENT_EDIT__
        m_AllEventContents.push_back(evt);
#else
        evt.name = evt.name + "@";
        char buf[20];
        
        sprintf_s(buf,sizeof(buf),"%d",evt.hour);
        evt.name = evt.name + buf;
        m_AllEventContents.push_back(evt);
#endif // _EDIT

        pEvent = pEvent->NextSiblingElement("Event");
	}
	return true;
}

bool EventManager::Load( const std::string& filename )
{
	m_hotEventContents.clear();
	m_weekEventContents.clear();
	m_everydayEventContents.clear();

    EventPeriodTypes.clear();
    EventRewardTypes.clear();
	m_AllEventContents.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(filename.c_str()))
    { return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
    { return false; }

    MeXmlElement* pPeriodType = pRoot->FirstChildElement("PeriodTypes");
    if (NULL != pPeriodType)
    {
        MeXmlElement* pType = pPeriodType->FirstChildElement("Type");
        while(NULL != pType)
        {
            EventPeriodType type;
            if (pType->Attribute("Id",&type.id) == NULL)
                return false;
            const char* pDescription = pType->Attribute("Description");
            if (NULL != pDescription)
                type.description = _tstring::toNarrowString(_tstring::UTF8towcs(pDescription).c_str());

            EventPeriodTypes.push_back(type);
            pType = pType->NextSiblingElement();
        }
    }

    MeXmlElement* pRewardType = pRoot->FirstChildElement("RewardTypes");
    if (NULL != pRewardType)
    {
        MeXmlElement* pType = pRewardType->FirstChildElement("Type");
        while(NULL != pType)
        {
            EventRewardType type;
            if (pType->Attribute("Id",&type.id) == NULL)
                return false;

            const char* pDescription = pType->Attribute("Description");
            if (NULL != pDescription)
                type.description = _tstring::toNarrowString(_tstring::UTF8towcs(pDescription).c_str());

            EventRewardTypes.push_back(type);
            pType = pType->NextSiblingElement();
        }
    }

	////////////////////////////////////////////////////////////
	MeXmlElement* pCategorys = pRoot->FirstChildElement("Categorys");
	if (NULL != pCategorys)
	{
		MeXmlElement* pType = pCategorys->FirstChildElement("Type");
		while(NULL != pType)
		{
			EventCategorys type;
			if (pType->Attribute("Id",&type.id) == NULL)
				return false;

			const char* pDescription = pType->Attribute("Description");
			if (NULL != pDescription)
				type.description = _tstring::toNarrowString(_tstring::UTF8towcs(pDescription).c_str());

			m_AllCategory.push_back(type);
			pType = pType->NextSiblingElement();
		}
	}
	////////////////////////////////////////////////////////////

	MeXmlElement* pActivityType = pRoot->FirstChildElement("ActivityTypes");
	if (NULL != pActivityType)
	{
		MeXmlElement* pType = pActivityType->FirstChildElement("Type");
		while(NULL != pType)
		{
			EventActivityType type;
			if (pType->Attribute("Id",&type.id) == NULL)
				return false;

			const char* pDescription = pType->Attribute("Description");
			if (NULL != pDescription)
				type.description = _tstring::toNarrowString(_tstring::UTF8towcs(pDescription).c_str());

			m_AllActivityType.push_back(type);
			pType = pType->NextSiblingElement();
		}
	}

    MeXmlElement* pEvents = pRoot->FirstChildElement("Events");
    if (NULL == pEvents)
    { return true;}

    MeXmlElement* pEvent = pEvents->FirstChildElement("Event");
	while (NULL != pEvent)
	{
        const char* name = pEvent->Attribute("Name");
        if (NULL == name)
        { return false; }

		Event evt;

        if (pEvent->Attribute("Id", &evt.id) == NULL)
        { return false; }

        if (pEvent->Attribute("Category", &evt.category) == NULL)
        { return false; }

		int eventTemp = 0;
		pEvent->Attribute( "Country", &eventTemp );
		evt.country = eventTemp;

		if (pEvent->Attribute("ActivityType", &evt.mActivityType) == NULL)
		{
			return false;
		}

        if (pEvent->Attribute("Year", &evt.year) == NULL)
        { return false; }

        if (pEvent->Attribute("Month", &evt.month) == NULL)
        { return false; }

        if (evt.month > 11 ||evt.month < -1)
        { evt.month = -1; }

        if (pEvent->Attribute("Day", &evt.day) == NULL)
        { return false; }

        if (pEvent->Attribute("Hour", &evt.hour) == NULL )
        { return false; }

        if (pEvent->Attribute("Minute", &evt.minute) == NULL)
        { return false; }

        // 根据读入的时间算出是周几
        evt.week = HelperFunc::Ymd2Wday(evt.year,evt.month+1,evt.day); 

        int tempPeriodTypeId;
        if ( NULL == pEvent->Attribute("PeriodTypeId", &tempPeriodTypeId) )
            return false;
        evt.periodTypeId = tempPeriodTypeId;
        
        int tempPeriodTypeVar;
        if ( NULL == pEvent->Attribute("PeriodParameter", &tempPeriodTypeVar) )
            return false;
        evt.periodParameter = tempPeriodTypeVar;

		evt.isEveryday = 0;
		if (evt.periodTypeId == 1)
		{ evt.isEveryday = 1; }
        else if (evt.periodTypeId == 2)//每周
        {
            if (evt.periodParameter < -1|| evt.periodParameter > 6)
			{ return false; }
			evt.week = evt.periodParameter;
        }
        else if (evt.periodTypeId == 3)//每月
        {
            if (evt.periodParameter < -1|| evt.periodParameter > 31)
            { return false; }

            if (evt.periodParameter == 0)
            { evt.periodParameter = -1; }
        }

        ItrPeriodTypeContainer Itr = find(EventPeriodTypes.begin(),EventPeriodTypes.end(),evt.periodTypeId);
        if (Itr == EventPeriodTypes.end())
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Event %s Not Find PeriodType! PeriodTypeId = %d",evt.name.c_str(),evt.periodTypeId);
            return false;
        }

        evt.period = Itr->description; // 显示使用

		evt.name = _tstring::toNarrowString(_tstring::UTF8towcs(name).c_str());
        if ( NULL == pEvent->Attribute("NeedLevel", &evt.needLevel) )
        { return false; }

        if ( NULL == pEvent->Attribute("Quality", &evt.quality) )
        { return false; }

        if ( NULL == pEvent->Attribute("Count", &evt.count) )
        { return false; }

        int IsHot = 0;
        pEvent->Attribute("IsHot", &IsHot);
        evt.isHot = IsHot < 1?FALSE:TRUE;

        int IsPivot = 0;
        pEvent->Attribute("IsPivot", &IsPivot);
        evt.isPivot = IsPivot < 1?FALSE:TRUE;

        int tempScript = 0;
        if ( NULL == pEvent->Attribute("ScriptId", &tempScript) )
        { return false; }
        if (tempScript < -1)
        { tempScript = -1; }
        evt.scriptId = tempScript;

        int tempEventItemId = 0;
        if ( NULL == pEvent->Attribute("EventItemId", &tempEventItemId) )
        { tempEventItemId = InvalidLogicNumber; }
        unsigned short shTempEventItemId = (unsigned short)tempEventItemId;
        ItemDefine::SItemCommon * pItem = GettheItemDetail().GetItemByID(shTempEventItemId);
        if (NULL == pItem)
        { shTempEventItemId = InvalidLogicNumber; }
        evt.eventItemId = shTempEventItemId;
        
        if ( NULL == pEvent->Attribute("NpcId", &evt.npcId) )
        { return false; }

        NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(evt.npcId);
        if (NULL != pNpc)
        { evt.npc = pNpc->name; }

        if ( NULL == pEvent->Attribute("MapId", &evt.mapId) )
        { return false;}

        MapConfig::MapData* pMap = theMapConfig.GetMapDataById(evt.mapId);
        if (NULL != pMap)
        { evt.mapName = pMap->MapName; }
        else
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Event %s Not Find Map! MapId = %d",evt.name.c_str(),evt.mapId);
            return false;
        }

        double  mapPosX;
        if ( NULL == pEvent->Attribute("MapPosX", &mapPosX) )
            return false;
        if (mapPosX > pMap->Column*16.0f)
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Event %s Map Size Error! MapId = %d MapPosX = %4.0f",evt.name.c_str(),evt.mapId,mapPosX);
            return false;
        }
        evt.mapPosX = mapPosX;

        double  mapPosY;
        if ( NULL == pEvent->Attribute("MapPosY", &mapPosY) )
            return false;
        if (mapPosY > pMap->Row*16.0f)
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Event %s Map Size Error! MapId = %d MapPosY = %4.0f",evt.name.c_str(),evt.mapId,mapPosY);
            return false;
        }
        evt.mapPosY = mapPosY;

        if ( NULL == pEvent->Attribute("CompleteId", &evt.completeTimeVarIndex) )
        { return false; }

        const char* var = pEvent->Attribute("Description");
        if (NULL != var)
        { evt.description = _tstring::toNarrowString(_tstring::UTF8towcs(var).c_str()); }

        if (pEvent->Attribute("Duration", &evt.duration) == NULL)
        { return false; }

        const char* durationDesVar = pEvent->Attribute("DurationDescription");
        if (NULL != durationDesVar)
        { evt.durationDescription = _tstring::toNarrowString(_tstring::UTF8towcs(durationDesVar).c_str()); }

        ////////////////////////////////结束时间////////////////////////////////////
		evt.endWeek   = evt.week + evt.duration / (24 * 60);
		evt.endHour   = evt.hour + (evt.duration - ( evt.endWeek - evt.week ) * 24 * 60) / 60;
		evt.endMinute = evt.minute + (evt.duration - ( evt.endWeek - evt.week ) * 24 * 60 - ( evt.endHour - evt.hour ) * 60);

		if (evt.endMinute >= 60)
		{
			evt.endMinute = evt.endMinute - 60;
			evt.endHour++;
		}

		if (evt.endHour >= 24)
		{
			evt.endHour = evt.endHour - 24;
			evt.endWeek++;
		}

		if (evt.endWeek >= 7)
		{
			evt.endWeek = evt.endWeek - 7;
		}
        ///////////////////////////////结束时间////////////////////////////////////
        

        MeXmlElement* pBroadcasts = pEvent->FirstChildElement("Broadcasts");
        if (NULL != pBroadcasts)
        {
            MeXmlElement* pBroadcast = pBroadcasts->FirstChildElement("Broadcast");
            while (NULL !=  pBroadcast)
            {
                Event::Broadcast tempBroadcast;
                if ( NULL == pBroadcast->Attribute("OffsetTime",&tempBroadcast.offsetTime) )
                    return false;

                
                 const char* var = pBroadcast->Attribute("Content");
                 if (NULL != var)
                     tempBroadcast.content = _tstring::toNarrowString(_tstring::UTF8towcs(var).c_str());

                evt.broadcast.push_back(tempBroadcast);
                pBroadcast = pBroadcast->NextSiblingElement();
            }
        }
        evt.rewards.clear();
        MeXmlElement* pRewards = pEvent->FirstChildElement("Rewards");
        if (NULL != pRewards)
        {
            MeXmlElement* pReward = pRewards->FirstChildElement("Reward");
            while (NULL !=  pReward)
            {
                Event::Reward rewardItem;
                if ( NULL == pReward->Attribute("TypeId",&rewardItem.typeId) )
                    return false;
                ItrEventRewardTypeContainer Itr = find(EventRewardTypes.begin(),EventRewardTypes.end(),rewardItem.typeId);
                if (Itr == EventRewardTypes.end())
                {
                    LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Event %s Not Find EventRewardTypes! EventRewardType = %d",evt.name.c_str(),rewardItem.typeId);
                    return false;
                }

                if ( NULL == pReward->Attribute("Parameter1",&rewardItem.id) )
                    return false;

                if ( NULL == pReward->Attribute("Parameter2",&rewardItem.count) )
                    return false;

                evt.rewards.push_back(rewardItem);
                pReward = pReward->NextSiblingElement();
            }
        }

        // 这里的逻辑是需要把本周的放入m_weekEventContents，如果是热点的同时需要放入到m_hotEventContents
        if (evt.isHot)
        { m_hotEventContents.push_back(evt); }

        else //else if ( nowtime.tm_wday == evt.week )// 如果今天有
		{
			if (evt.periodTypeId == 1)
			{
				// 填写一周内的活动
				m_everydayEventContents.push_back(evt);
			}
			else
			{
				ItrPeriodTypeContainer Itr = find(EventPeriodTypes.begin(),EventPeriodTypes.end(),evt.week + 10);
				if (Itr != EventPeriodTypes.end())
					evt.period = Itr->description;
				m_weekEventContents[evt.week].push_back(evt);
			}
		}

        m_AllEventContents.push_back(evt);
        pEvent = pEvent->NextSiblingElement("Event");
	}
	return true;
}
	


Event* EventManager::GetEventByName(const std::string &eventName)
{
    ItrEventContents itr = find(m_AllEventContents.begin(),m_AllEventContents.end(),eventName);
    if (itr != m_AllEventContents.end())
    {
        return &(*itr);
    }
    return NULL;
}

Event* EventManager::GetEventByIndex(const unsigned int &index)
{
    if (index > m_AllEventContents.size())
        return NULL;

    return &m_AllEventContents[index];
}

EventPeriodType* EventManager::GetEventPeriodTypeById(const unsigned int &id)
{
    ItrPeriodTypeContainer itr = find (EventPeriodTypes.begin(),EventPeriodTypes.end(),id);
    if (itr != EventPeriodTypes.end())
        return &(*itr);

    return NULL;
}

EventPeriodType* EventManager::GetEventPeriodTypeByIndex(const unsigned int &id)
{
    if (id >= EventPeriodTypes.size())
        return NULL;
    return &EventPeriodTypes[id];
}

EventRewardType* EventManager::GetEventRewardType(const unsigned int &id)
{
    if (id >= EventRewardTypes.size())
        return NULL;
    return &EventRewardTypes[id];
}

EventPeriodType* EventManager::GetEventPeriodTypeByDes(const std::string &des)
{
    ItrPeriodTypeContainer itr = find(EventPeriodTypes.begin(),EventPeriodTypes.end(),des.c_str());
    if (itr != EventPeriodTypes.end())
    {
        return &(*itr);
    }
    return NULL;
}

bool Event::DeleteEventRewardByIndex(const int &IndexId)
{
    if (IndexId > rewards.size())
        return false;

    int i = 0;
    for (std::vector<Event::Reward>::iterator itrReward = rewards.begin();itrReward != rewards.end();++itrReward)
    {
        if (IndexId == i)
        {
            rewards.erase(itrReward);
            return true;
        }
        ++i;
    }
    
    return false;
}

bool Event::DeleteEventRewardByRewardId(const int &RewardId)
{
    std::vector<Event::Reward>::iterator itrReward = find (rewards.begin(),rewards.end(),RewardId);
    if (itrReward != rewards.end())
    {
        rewards.erase(itrReward);
        return true;
    }
    return false;
}

bool Event::DeleteEventBroadcast(const int &BroadcastOffsetTime)
{
    std::vector<Event::Broadcast>::iterator itrBroadcast = find (broadcast.begin(),broadcast.end(),BroadcastOffsetTime);
    if (itrBroadcast != broadcast.end())
    {
        broadcast.erase(itrBroadcast);
        return true;
    }
    return false;
}

bool Event::AddEventReward(const Event::Reward &reward)
{
    std::vector<Event::Reward>::iterator itrReward = find (rewards.begin(),rewards.end(),reward.id);
    if (itrReward != rewards.end())
    {
        return false;
    }
    rewards.push_back(reward);
    return true;
}

bool Event::AddEventBroadcast(const Event::Broadcast &addBroadcast)
{
    std::vector<Event::Broadcast>::iterator itrBroadcast = find (broadcast.begin(),broadcast.end(),addBroadcast.offsetTime);
    if (itrBroadcast != broadcast.end())
    {
        return false;
    }
    broadcast.push_back(addBroadcast);
    return true;
}

bool Event::ModifyEventReward(int RewardId,const Event::Reward &reward)
{
    std::vector<Event::Reward>::iterator itrReward = find (rewards.begin(),rewards.end(),reward.id);
    if (itrReward != rewards.end())
    {
        *itrReward = reward;
        return true;
    }
    return false;
}
bool Event::ModifyEventBroadcast(int BroadcastOffsetTime,const Event::Broadcast &mobroadcast)
{
    std::vector<Event::Broadcast>::iterator itrBroadcast = find (broadcast.begin(),broadcast.end(),mobroadcast.offsetTime);
    if (itrBroadcast != broadcast.end())
    {
        *itrBroadcast = mobroadcast;
        return true;
    }
    return false;
}

Event::Reward* Event::GetEventRewardByRewardId(const int &RewardId)
{
    std::vector<Event::Reward>::iterator itrReward = find (rewards.begin(),rewards.end(),RewardId);
    if (itrReward != rewards.end())
    {
        return &(*itrReward);
    }
    return NULL;
}

Event::Broadcast* Event::GetEventBroadcastByOffsetTime(const int &BroadcastOffsetTime)
{
    std::vector<Event::Broadcast>::iterator itrBroadcast = find (broadcast.begin(),broadcast.end(),BroadcastOffsetTime);
    if (itrBroadcast != broadcast.end())
    {
        return &(*itrBroadcast);
    }
    return NULL;
}

bool EventManager::AddEvent(const Event &event)
{
    ItrEventContents itr = find(m_AllEventContents.begin(),m_AllEventContents.end(),event.name);
    if (itr == m_AllEventContents.end())
    {
        m_AllEventContents.push_back(event);
        return true;
    }
    return false;
}

bool EventManager::DeleteEvent(const std::string &eventName)
{
    ItrEventContents itr = find(m_AllEventContents.begin(),m_AllEventContents.end(),eventName);
    if (itr != m_AllEventContents.end())
    {
        m_AllEventContents.erase(itr);
        return true;
    }
    return false;
}

bool EventManager::ModifiyEvent(const std::string &EventName ,const Event &event)
{
    ItrEventContents itr = find(m_AllEventContents.begin(),m_AllEventContents.end(),EventName);
    if (itr != m_AllEventContents.end())
    {
        itr->BaseCopy(event);
        return true;
    }
    return false;
}

Event::Reward* Event::GetEventRewardByIndex(const unsigned int &index)
{
    if (index >= rewards.size())
        return NULL;
    return &rewards[index];
}

Event::Broadcast* Event::GetEventBroadcastByIndex(const unsigned int &index)
{
    if (index >= broadcast.size())
        return NULL;
    return &broadcast[index];
}

int EventManager::GetRewardTypeByDes(const std::string &des)
{
    if (des.empty())
        return -1;
    
    ItrEventRewardTypeContainer itr = find(EventRewardTypes.begin(),EventRewardTypes.end(),des.c_str());
    if (itr != EventRewardTypes.end())
    {
        return itr->id;
    }
    return NULL;
}

int EventManager::GetPeriodTypeByDes(const std::string &des)
{
    if (des.empty())
        return -1;
    ItrPeriodTypeContainer itr = find(EventPeriodTypes.begin(),EventPeriodTypes.end(),des.c_str());
    if (itr != EventPeriodTypes.end())
    {
        return itr->id;
    }
    return NULL;
}

const char* EventManager::GetActivityTypeStr( int typeId )
{
	EventActivityTypeIt_t it = m_AllActivityType.begin();
	EventActivityTypeIt_t itEnd = m_AllActivityType.end();

	for ( ; it != itEnd; ++it )
	{
		if ( it->id == typeId )
		{
			return it->description.c_str();
		}
	}

	return NULL;
}


bool EventManager::Save(const std::string& filename)
{
    if (filename.empty())
        return false;

    MeXmlDocument xMeXmlDoc;
    xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","UTF-8","yes"));
    MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild(("Project"))->ToElement();
    if (pRoot == NULL) 
    { return false; }

    Common::_tstring strName = "HeroOnline";
    pRoot->SetAttribute("Name", strName.toUTF8().c_str());
    Common::_tstring strVersion = ApplicationConfig::Instance().GetFullVersion();
    pRoot->SetAttribute("Version",strVersion.toUTF8().c_str());
    
    Common::_tstring strComment = "\nNeedLeve 活动需求等级(1～70)\n\
        Quality  活动推荐度  (1～5 )\r\n\
        MapPosX,MapPosY     (无发布NPC活动 寻路地点坐标)\n\
        Duration 活动持续时间(单位:分)\n\
        Count    活动次数限制(1~99 or -1为无限次数)\n\
        ComleteId  活动次数计数变量(脚本自定义)";
    pRoot->append_node(xMeXmlDoc.RetriveCommentElement(strComment.toUTF8().c_str()));
    // PeriodTypes
    MeXmlElement* pPeriodTypes = pRoot->InsertEndChild(("PeriodTypes"))->ToElement();
    if (NULL == pPeriodTypes)
    { return false; }

    ItrPeriodTypeContainer itrPeriod = EventPeriodTypes.begin();
    ItrPeriodTypeContainer itrEndPeriod = EventPeriodTypes.end();
    for (;itrPeriod!=itrEndPeriod;++itrPeriod)
    {
        MeXmlElement* pPeriodType = pPeriodTypes->InsertEndChild(("Type"))->ToElement();
        if (NULL == pPeriodType )
        { return false; }
        pPeriodType->SetAttribute("Id",itrPeriod->id);
        Common::_tstring strDescription = itrPeriod->description.c_str();
        pPeriodType->SetAttribute("Description",strDescription.toUTF8().c_str());
    }

    // RewardTypes
    MeXmlElement* pRewardTypes = pRoot->InsertEndChild(("RewardTypes"))->ToElement();
    if (NULL == pRewardTypes)
    { return false; }

    ItrEventRewardTypeContainer itrReward = EventRewardTypes.begin();
    ItrEventRewardTypeContainer itrEndReward = EventRewardTypes.end();
    for (;itrReward!=itrEndReward;++itrReward)
    {
        MeXmlElement* pRewardType = pRewardTypes->InsertEndChild(("Type"))->ToElement();
        if (NULL == pRewardType )
        { return false; }
        pRewardType->SetAttribute("Id",itrReward->id);
        Common::_tstring strDescription = itrReward->description.c_str();
        pRewardType->SetAttribute("Description",strDescription.toUTF8().c_str());
    }

	// ActivityTypes
	MeXmlElement* pActivityType = pRoot->InsertEndChild(("ActivityTypes"))->ToElement();
	if (NULL == pRewardTypes)
	{ return false; }

	EventActivityTypeIt_t itAct = m_AllActivityType.begin();
	EventActivityTypeIt_t itActEnd = m_AllActivityType.end();
	for ( ; itAct!=itActEnd; ++itAct )
	{
		MeXmlElement* pType= pActivityType->InsertEndChild(("Type"))->ToElement();
		if (NULL == pActivityType )
		{ return false; }
		pType->SetAttribute("Id",itAct->id);
		Common::_tstring strDescription = itAct->description.c_str();
		pType->SetAttribute("Description",strDescription.toUTF8().c_str());
	}

    MeXmlElement* pEvents = pRoot->InsertEndChild(("Events"))->ToElement();
    if (NULL == pEvents)
    { return false; }

    ItrEventContents itrEvent = m_AllEventContents.begin();
    ItrEventContents itrEndEvent = m_AllEventContents.end();
    for (;itrEvent!=itrEndEvent;++itrEvent)
    {
        MeXmlElement* pEvent = pEvents->InsertEndChild(("Event"))->ToElement();
        if (NULL == pEvent)
            return false;
#ifndef __EVENT_EDIT__
        Common::_tstring strEventName = itrEvent->name.c_str();
#else
        Common::_tstring strEventName = itrEvent->name.substr(0,itrEvent->name.find_first_of("@"));
#endif
        
        pEvent->SetAttribute("Name",strEventName.toUTF8().c_str());
        if (itrEvent->needLevel < -1||itrEvent->needLevel>70)
        {
            LOG_MESSAGE(SYSTEMOBJECT, LOG_PRIORITY_ERROR,"%s Event NeedLevel < -1 || NeedLevel>70 NeedLevel = %d",itrEvent->name.c_str(),itrEvent->needLevel);
            return false;
        }
        pEvent->SetAttribute("NeedLevel",itrEvent->needLevel);
        pEvent->SetAttribute("Quality",itrEvent->quality);
        pEvent->SetAttribute("NpcId",itrEvent->npcId);
        pEvent->SetAttribute("MapId",itrEvent->mapId);
        pEvent->SetAttribute("MapPosX",itrEvent->mapPosX);
        pEvent->SetAttribute("MapPosY",itrEvent->mapPosY);
        Common::_tstring strEventDescription = itrEvent->description.c_str();
        pEvent->SetAttribute("Description",strEventDescription.toUTF8().c_str());
        pEvent->SetAttribute("PeriodTypeId",itrEvent->periodTypeId);
        pEvent->SetAttribute("PeriodParameter",itrEvent->periodParameter);
        pEvent->SetAttribute("Year",itrEvent->year);
        pEvent->SetAttribute("Month",itrEvent->month);
        pEvent->SetAttribute("Day",itrEvent->day);
        pEvent->SetAttribute("Hour",itrEvent->hour);
        pEvent->SetAttribute("Minute",itrEvent->minute);
        pEvent->SetAttribute("Duration",itrEvent->duration);
        Common::_tstring strDurationDescription = itrEvent->durationDescription.c_str();
        pEvent->SetAttribute("DurationDescription",strDurationDescription.toUTF8().c_str());
        pEvent->SetAttribute("Count",itrEvent->count);
        pEvent->SetAttribute("CompleteId",itrEvent->completeTimeVarIndex);
        pEvent->SetAttribute("IsHot",itrEvent->isHot);
        pEvent->SetAttribute("IsPivot", itrEvent->isPivot);

		pEvent->SetAttribute("ActivityType", itrEvent->mActivityType);

        int tempScriptId = itrEvent->scriptId;
        pEvent->SetAttribute("ScriptId",tempScriptId);
        
        ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID(itrEvent->eventItemId);
        if (NULL != pItem)
        {
            int tempEventItemId = itrEvent->eventItemId;
            pEvent->SetAttribute("EventItemId",tempEventItemId);
        }
        else
        {
            int tempEventItemId = InvalidLogicNumber;
            pEvent->SetAttribute("EventItemId",tempEventItemId);
        }
        

        MeXmlElement* pBroadcasts = pEvent->InsertEndChild(("Broadcasts"))->ToElement();
        if (NULL == pBroadcasts)
            return false;

        std::vector<Event::Broadcast>::iterator itrBroadcast = itrEvent->broadcast.begin();
        std::vector<Event::Broadcast>::iterator itrEndBroadcast = itrEvent->broadcast.end();
        for (;itrBroadcast!=itrEndBroadcast;++itrBroadcast)
        {
            MeXmlElement* pBroadcast = pBroadcasts->InsertEndChild(("Broadcast"))->ToElement();
            pBroadcast->SetAttribute("OffsetTime",itrBroadcast->offsetTime);
            Common::_tstring strContent = itrBroadcast->content.c_str();
            pBroadcast->SetAttribute("Content",strContent.toUTF8().c_str());
        }

        MeXmlElement* pRewards = pEvent->InsertEndChild(("Rewards"))->ToElement();
        if (NULL == pRewards)
        { return false; }
        std::vector<Event::Reward>::iterator itrReward = itrEvent->rewards.begin();
        std::vector<Event::Reward>::iterator itrEndReward = itrEvent->rewards.end();
        for (;itrReward!=itrEndReward;++itrReward)
        {
            MeXmlElement* pReward = pRewards->InsertEndChild(("Reward"))->ToElement();
            if (NULL == pReward)
                return false;

            pReward->SetAttribute("TypeId",itrReward->typeId);
            pReward->SetAttribute("Parameter1",itrReward->id);
            pReward->SetAttribute("Parameter2",itrReward->count);
        }
    }

    return xMeXmlDoc.SaveFile(filename.c_str());
}

void Event::BaseCopy (const Event &otherEvent) // 用于编辑器，不拷贝rewards，broadcast
{
    name = otherEvent.name;
    description = otherEvent.description;
    needLevel = otherEvent.needLevel;
    quality = otherEvent.quality;
    count = otherEvent.count;	
    completeTimeVarIndex = otherEvent.completeTimeVarIndex; 
    npcId = otherEvent.npcId;
    duration = otherEvent.duration;
    durationDescription = otherEvent.durationDescription;
    mapId = otherEvent.mapId;
    mapPosX = otherEvent.mapPosX;
    mapPosY = otherEvent.mapPosY;

    isHot = otherEvent.isHot;
    isPivot = otherEvent.isPivot;

    periodTypeId = otherEvent.periodTypeId;
    periodParameter = otherEvent.periodParameter;

    year = otherEvent.year;
    month = otherEvent.month;
    day = otherEvent.day;
    hour = otherEvent.hour;
    minute = otherEvent.minute;
    scriptId = otherEvent.scriptId;
    eventItemId = otherEvent.eventItemId;
}

struct LessByMonthDay 
{
	bool operator()(const Event& v1, const Event& v2)
	{
		if (v1.day < v2.day)
			return true;
		else if (v1.day == v2.day)
			return v1.eventItemId < v2.eventItemId;
		return false;
	}
};

void EventManager::GetMonthEventContents(const struct tm& nowtime, EventContents& out)
{
	int nowYear = nowtime.tm_year + 1900;
	int nowMonth = nowtime.tm_mon;
	for (int i = 0; i < m_AllEventContents.size(); ++i)
	{
		if ( (m_AllEventContents[i].year == nowYear && m_AllEventContents[i].month == nowMonth)
			|| m_AllEventContents[i].periodTypeId == 3)
		{
			out.push_back(m_AllEventContents[i]);
		}
	}

	static int mdays[]={31,28,31,30,31,30,31,31,30,31,30,31};
	int days = mdays[nowtime.tm_mon]; 

	WeekEventContents::iterator it = m_weekEventContents.begin();
	WeekEventContents::iterator end = m_weekEventContents.end();
	for ( ; it != end; ++it)
	{
		for (int e = 0; e < it->second.size(); ++e)
		{
			Event& evt = it->second[e];
			if (evt.periodTypeId != 2)
				continue;

			for (int d = 1; d <= days; ++d)
			{
				int week = HelperFunc::Ymd2Wday(nowYear, nowMonth + 1, d);
				if (week == evt.week)
				{
					Event newEvt = evt;
					newEvt.year = nowYear;
					newEvt.month = nowMonth;
					newEvt.day = d;
					out.push_back(newEvt);
				}
			}
		}
	}

	std::sort(out.begin(), out.end(), LessByMonthDay());
}
