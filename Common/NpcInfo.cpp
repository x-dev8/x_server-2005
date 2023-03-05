#include "NpcInfo.h"
#include "ErrorCode.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include "tstring.h"

int NpcInfo::LoadConfig(const char *path)
{
#ifdef GAME_CLIENT
	dynamicCollNpcs_.clear();
#endif

	if (path == NULL || *path == 0)
	{
		return Param_Error;
	}

	npcs_.clear();


	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(path, 1))
	{	
		return File_Error;
	}


	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if ( NULL == pRoot ) return Attribute_Error;

	{
		// 半身像
		int iValue = 0;
		pRoot->QueryIntAttribute("DialogPic", &iValue);
		SetDialogPic((bool)iValue);
	}

	MeXmlElement* pNpcs = pRoot->FirstChildElement("Npcs");
	if ( NULL == pNpcs ) return Attribute_Error;

	MeXmlElement* pNpc = pNpcs->FirstChildElement("Npc");
	while (pNpc != NULL)
	{			
		Npc xNpc;

		int id;
		if (pNpc->Attribute("Id", &id) == NULL)
		{
			return File_Error;
		}
		xNpc.id = id;

		Common::_tstring name;			
		name.fromUTF8(pNpc->Attribute("Name"));
		xNpc.name = name;
		//xNpc.pinyin = pNpc->Attribute("PinYin");

		Common::_tstring SoundPath;			
		SoundPath.fromUTF8(pNpc->Attribute("SoundPath"));
		xNpc.strSoundPath = SoundPath;

        Common::_tstring pinyin;
        pinyin.fromUTF8(pNpc->Attribute("PinYin"));
        xNpc.pinyin = pinyin;

		int mapId;
		if (pNpc->Attribute("MapId", &mapId) == NULL)
		{
			mapId = -1;
		}
		xNpc.mapId = mapId;

		int level;
		pNpc->Attribute("Level", &level);
		xNpc.level = level;

		int type;
		if (pNpc->Attribute("Type", &type) == NULL)
		{
			type = -1;
		}
		xNpc.type = type;

		int modelId;
		if (pNpc->Attribute("ModelId", &modelId) == NULL)
		{
			modelId = -1;
		}
		xNpc.modelId = modelId;

		double x;
		pNpc->Attribute("PositionX", &x);
		xNpc.x = x;

		double y;
		pNpc->Attribute("PositionY", &y);
		xNpc.y = y;

        double z;
        if ( pNpc->Attribute("PositionZ", &z) != NULL )
        {
            xNpc.z = z;
        }

		int movePath = -1;
		if (pNpc->Attribute("MovePath", &movePath) == NULL)
		{
			movePath = -1;
		}
		xNpc.movePath = movePath;

		int direction;
		pNpc->Attribute("Direction", &direction);
		xNpc.direction = direction;

		int canChangeDirection;
		pNpc->Attribute("CanChangeDirection", &canChangeDirection);
		xNpc.canChangeDirection = canChangeDirection;

		Common::_tstring scriptFile;
		scriptFile.fromUTF8(pNpc->Attribute("ScriptFile"));
		xNpc.triggerScript = scriptFile;

        Common::_tstring actScriptFile;
        actScriptFile.fromUTF8(pNpc->Attribute("ActionScriptFile"));
        if (actScriptFile.empty())
        {
            xNpc.actionScript = "";
        }
        else
        {
            xNpc.actionScript = actScriptFile;
        }
        

		int isShow;
		if (pNpc->Attribute("IsMiniShow", &isShow) == NULL)
		{
			isShow = true;
		}
		xNpc.isMiniShow = isShow;

        if (pNpc->Attribute("IsWorldShow", &isShow) == NULL)
        {
            isShow = true;
        }
        xNpc.isWorldShow = isShow;

		int isCollision;
		if (pNpc->Attribute("IsCollision", &isCollision) == NULL)
		{
			isCollision = true;
		}
		xNpc.isCollision = isCollision;

		Common::_tstring title;
		title.fromUTF8(pNpc->Attribute("Title"));
		xNpc.title = title;

		Common::_tstring tip;
		tip.fromUTF8(pNpc->Attribute("NpcTips"));
		xNpc.tip = tip;

		Common::_tstring headPicture;
		headPicture.fromUTF8(pNpc->Attribute("HeadPicture"));
		xNpc.strHeadPicture = headPicture;

		double bodyScale;
		pNpc->Attribute("BodyScale", &bodyScale);
		xNpc.bodyScale = bodyScale;

		int isDynamicCollision = false;
		pNpc->Attribute("IsDynamicCollision", &isDynamicCollision);
		xNpc.isDynamicCollision = isDynamicCollision;

        int nCountryID;
        if ( pNpc->Attribute( "Country", &nCountryID ) != NULL )
        { xNpc.uchCountryID = nCountryID; }

        int nPhyle;
        if ( pNpc->Attribute( "Phyle", &nPhyle ) != NULL )
        { xNpc.phyle = nPhyle; }
		
		double gutUIScale;
		if (pNpc->Attribute("GutUIScale",&gutUIScale) != NULL)
		{
			xNpc.gutUIScale = gutUIScale;
		}

		int gutUIOffsetX;
		if (pNpc->Attribute("GutUIOffsetX",&gutUIOffsetX) != NULL)
		{
			xNpc.gutUIOffsetX = gutUIOffsetX;
		}

		int gutUIOffsetY;
		if (pNpc->Attribute("GutUIOffsetY",&gutUIOffsetY) != NULL)
		{
			xNpc.gutUIOffsetY = gutUIOffsetY;
		}

		int nMenu = 0;
		if(pNpc->Attribute("MenuId",&nMenu) != NULL)
		{xNpc.nTaskMenu = nMenu;}

        // NPC动作+说话
        xNpc.vctActionData.clear();
        MeXmlElement* pNpcActionData = pNpc->FirstChildElement("ElapseTime");
        while (pNpcActionData != NULL)
        {
			Common::_tstring nodeValue;			
			nodeValue.fromUTF8(pNpcActionData->name());
			if ( nodeValue != "ElapseTime" )
			{
				pNpcActionData = pNpcActionData->NextSiblingElement();
				continue;
			}
			
            NpcActionData kActionData;
            int data;
            pNpcActionData->Attribute("Id", &data);
            kActionData.shId = short(data);
            pNpcActionData->Attribute("Time", &data);
            kActionData.shElapseTime = short(data);
            pNpcActionData->Attribute("NextTimeId", &data);
            kActionData.shNextId = short(data);

            // 动作列表
            kActionData.vctActions.clear();
            MeXmlElement* pActions = pNpcActionData->FirstChildElement("Actions");
            if( pActions )
            {
                MeXmlElement* pOneAction = pActions->FirstChildElement("Action");
                while( pOneAction )
                {
                    ActionData kAction;
                    Common::_tstring name;			
                    name.fromUTF8(pOneAction->Attribute("Name"));
                    kAction.strAnimName = name;

                    pOneAction->Attribute("Probability", &data);
                    kAction.shProbability = (short)data;
                    kActionData.vctActions.push_back(kAction);
 		            //next node
		            pOneAction = pOneAction->NextSiblingElement();
                }
            }

            // 说话列表
            kActionData.vctTalks.clear();
            MeXmlElement* pTalks = pNpcActionData->FirstChildElement("Talks");
            if( pTalks )
            {
                MeXmlElement* pOneTalk = pTalks->FirstChildElement("Talk");
                while( pOneTalk )
                {
                    TalkData kTalk;
                    pOneTalk->Attribute("StringId", &kTalk.shStringId);
                    pOneTalk->Attribute("Probability", &data);
                    kTalk.shProbability = (short)data;
                    kActionData.vctTalks.push_back(kTalk);

                    //next node
                    pOneTalk = pOneTalk->NextSiblingElement();
                }
            }
            xNpc.vctActionData.push_back(kActionData);

 		    //next node
		    pNpcActionData = pNpcActionData->NextSiblingElement();
        }
#ifdef _CLIENT_
		MeXmlElement *pActions = pNpc->FirstChildElement("Actions");
		xNpc.npcAct.ParseAction(pActions);
#endif
        MeXmlElement* pFightInfo = pNpc->FirstChildElement("FightInfo");
        if (pFightInfo != NULL) // 如果存在Npc FightInfo节点，FightInfo节点每个Npc只存在一个
        {
            FightInfo xFightInfo;
            for (int i=0; i<3; ++i)
            {
                char szSkillId[20] = {0};
                sprintf_s(szSkillId, sizeof(szSkillId) - 1, "Skill%dId", i+1);
                int nSkillId;
                pFightInfo->Attribute(szSkillId, &nSkillId);
                xFightInfo.skills[i].skillId = nSkillId;

                char szSkillLevel[20] = {0};
                sprintf_s(szSkillLevel, sizeof(szSkillLevel) - 1, "Skill%dLevel", i+1);
                int nSkillLevel;
                pFightInfo->Attribute(szSkillLevel, &nSkillLevel);
                xFightInfo.skills[i].skillLevel = nSkillLevel;

                char szSkillRate[20] = {0};
                sprintf_s(szSkillRate, sizeof(szSkillRate) - 1, "Skill%dRate", i+1);
                int nSkillRate;
                pFightInfo->Attribute(szSkillRate, &nSkillRate);
                xFightInfo.skills[i].skillRate = nSkillRate;
            }

			int nNpcID;
			pFightInfo->Attribute("Id", &nNpcID);
			xFightInfo.npcId = nNpcID;

            float fBodyLength;
            pFightInfo->Attribute("BodyLength", &fBodyLength);
            xFightInfo.bodyLength = fBodyLength;

            int nLevel;
            pFightInfo->Attribute("Level", &nLevel);
            xFightInfo.level = nLevel;

            int nMaxHp;
            pFightInfo->Attribute("HpMax", &nMaxHp);
            xFightInfo.hpMax = nMaxHp;

            int nMaxMp;
            pFightInfo->Attribute("MpMax", &nMaxMp);
            xFightInfo.mpMax = nMaxMp;

			float nHpRestore;
			pFightInfo->Attribute("HpRestore", &nHpRestore);
			xFightInfo.hpRestore = nHpRestore;

			float nMpRestore;
			pFightInfo->Attribute("MpRestore", &nMpRestore);
			xFightInfo.mpRestore = nMpRestore;

            int nExact;
            pFightInfo->Attribute("Exact", &nExact);
            xFightInfo.exact = nExact;

            int nDodge;
            pFightInfo->Attribute("Dodge", &nDodge);
            xFightInfo.dodge = nDodge;

            int nAttackSpeed;
            pFightInfo->Attribute("AttackSpeed", &nAttackSpeed);
            xFightInfo.attackSpeed = nAttackSpeed;

            float nPhyAttack;
            pFightInfo->Attribute("PhyAttack", &nPhyAttack);
            xFightInfo.attackPhysics = nPhyAttack;

            float nMagAttack;
            pFightInfo->Attribute("MagAttack", &nMagAttack);
            xFightInfo.attackMagic = nMagAttack;

            int fCritical;
            pFightInfo->Attribute("Critical", &fCritical);
            xFightInfo.critical = fCritical;

            int nCriticalIntensity;
            pFightInfo->Attribute("CriticalIntensity", &nCriticalIntensity);
            xFightInfo.criticalIntensity = nCriticalIntensity;

			int nBackStrike;
			pFightInfo->Attribute("BackStrike", &nBackStrike);
			xFightInfo.backStrike = nBackStrike;

			int nBackStrikeResist;
			pFightInfo->Attribute("BackStrikeResist", &nBackStrikeResist);
			xFightInfo.backStrikeResist = nBackStrikeResist;

			int nBreakStrike;
			pFightInfo->Attribute("BreakStrike", &nBreakStrike);
			xFightInfo.breakStrike = nBreakStrike;

			int nStabStrike;
			pFightInfo->Attribute("StabStrike", &nStabStrike);
			xFightInfo.stabStrike = nStabStrike;

			int nElementStrike;
			pFightInfo->Attribute("ElementStrike", &nElementStrike);
			xFightInfo.elementStrike = nElementStrike;

			int nToxinStrike;
			pFightInfo->Attribute("ToxinStrike", &nToxinStrike);
			xFightInfo.toxinStrike = nToxinStrike;

			int nSpiritStrike;
			pFightInfo->Attribute("SpiritStrike", &nSpiritStrike);
			xFightInfo.spiritStrike = nSpiritStrike;

			int nBreakResist;
			pFightInfo->Attribute("BreakResist", &nBreakResist);
			xFightInfo.breakResist = nBreakResist;

			int nStabResist;
			pFightInfo->Attribute("StabResist", &nStabResist);
			xFightInfo.stabResist = nStabResist;

			int nElementResist;
			pFightInfo->Attribute("ElementResist", &nElementResist);
			xFightInfo.elementResist = nElementResist;

			int nToxinResist;
			pFightInfo->Attribute("ToxinResist", &nToxinResist);
			xFightInfo.toxinResist = nToxinResist;

			int nSpiritResist;
			pFightInfo->Attribute("SpiritResist", &nSpiritResist);
			xFightInfo.spiritResist = nSpiritResist;

            int nTenacity;
            pFightInfo->Attribute("Tenacity", &nTenacity);
            xFightInfo.tenacity = nTenacity;

            float fDefendShort;
            pFightInfo->Attribute("DefnedPhysics", &fDefendShort);
            xFightInfo.defendPhysics = fDefendShort;

          /*  float fDefendLong;
            pFightInfo->Attribute("DefendLong", &fDefendLong);
            xFightInfo.defendPhysics = fDefendLong;*/

            float fDefendMagic;
            pFightInfo->Attribute("DefnedMagic", &fDefendMagic);
            xFightInfo.defendMagic = fDefendMagic;

            //int nDerateShort;
            //pFightInfo->Attribute("DerateShort", &nDerateShort);
            //xFightInfo.derateShort = nDerateShort;

            //int nDerateLong;
            //pFightInfo->Attribute("DerateLong", &nDerateLong);
            //xFightInfo.derateLong = nDerateLong;

            //int nDerateMagic;
            //pFightInfo->Attribute("DerateMagic", &nDerateMagic);
            //xFightInfo.derateMagic = nDerateMagic;

            //int nResistDread;
            //pFightInfo->Attribute("ResistDread", &nResistDread);
            //xFightInfo.resistDread = nResistDread;

            //int nResistComa;
            //pFightInfo->Attribute("ResistComa", &nResistComa);
            //xFightInfo.resistComa = nResistComa;

            //int nResistSlience;
            //pFightInfo->Attribute("ResistSilence", &nResistSlience);
            //xFightInfo.resistSilence = nResistSlience;

            //int nResistSlow;
            //pFightInfo->Attribute("ResistSlow", &nResistSlow);
            //xFightInfo.resistSlow = nResistSlow;

            int nNormalAttackMin;
            pFightInfo->Attribute("NormalAttackMin", &nNormalAttackMin);
            xFightInfo.normalAttackMin = nNormalAttackMin;

            int nNormalAttackMax;
            pFightInfo->Attribute("NormalAttackMax", &nNormalAttackMax);
            xFightInfo.normalAttackMax = nNormalAttackMax;

            int nView;
            pFightInfo->Attribute("View", &nView);
            xFightInfo.view = nView;

            int nFightView;
            pFightInfo->Attribute("FightView", &nFightView);
            xFightInfo.fightView = nFightView;

            int nCatchTime;
            pFightInfo->Attribute("CatchTime", &nCatchTime);
            xFightInfo.catchTime = nCatchTime;

            float fMoveSpeed;
            pFightInfo->Attribute("MoveSpeed", &fMoveSpeed);
            xFightInfo.moveSpeed = fMoveSpeed;

            float fMoveStep;
            pFightInfo->Attribute("MoveStep", &fMoveStep);
            xFightInfo.moveStep = fMoveStep;

            float fIdleMoveSpeed;
            pFightInfo->Attribute("IdleMoveSpeed", &fIdleMoveSpeed);
            xFightInfo.idleMoveSpeed = fIdleMoveSpeed;

            float fIdleMoveStep;
            pFightInfo->Attribute("IdleMoveStep", &fIdleMoveStep);
            xFightInfo.idleMoveStep = fIdleMoveStep;

            int nReliveTime;
            pFightInfo->Attribute("ReliveTime", &nReliveTime);
            xFightInfo.reliveTime = nReliveTime;

            Common::_tstring strDeadScript;
            strDeadScript.fromUTF8( pFightInfo->Attribute("DeadScript") );
            xFightInfo.deadScript = strDeadScript.c_str();

            int nIsInitative;
            pFightInfo->Attribute("IsInitiative", &nIsInitative);
            xFightInfo.isInitiative = nIsInitative;

            int nDisappearTime;
            pFightInfo->Attribute("DisappearTime", &nDisappearTime);
            xFightInfo.disappearTime = nDisappearTime;

            int nEnmityDecRate;
            pFightInfo->Attribute("EnmityDecRate", &nEnmityDecRate);
            xFightInfo.enmityDecRate = nEnmityDecRate;

            int nEnmityView;
            pFightInfo->Attribute("EnmityView", &nEnmityView);
            xFightInfo.enmityView = nEnmityView;

            int nMaxRange;
            pFightInfo->Attribute("MaxRange", &nMaxRange);
            xFightInfo.maxRange = nMaxRange;

            int nChangePassive;
            pFightInfo->Attribute("ChangePassive", &nChangePassive);
            xFightInfo.changePassive = nChangePassive;

            int nPassiveTime;
            pFightInfo->Attribute("PassiveTime", &nPassiveTime);
            xFightInfo.passiveTime = nPassiveTime;

            int nBaseEnmityRange;
            pFightInfo->Attribute("BaseEnmityRange", &nBaseEnmityRange);
            xFightInfo.baseEnmityRange = nBaseEnmityRange;

            int nIntegral;
            pFightInfo->Attribute("Intergal", &nIntegral);
            xFightInfo.integral = nIntegral;

            int nRouteId;
            pFightInfo->Attribute("RouteId", &nRouteId);
            xFightInfo.routeId = nRouteId;

			int nFightType;
			pFightInfo->Attribute("FightType", &nFightType);
			xFightInfo.fightType = nFightType;

			int nFightCamp;
			pFightInfo->Attribute("FightCamp", &nFightCamp);
			xFightInfo.fightCamp = nFightCamp;

            xNpc.fightData.push_back(xFightInfo);
        }

		npcs_.insert(make_pair(xNpc.id, xNpc));

#ifdef GAME_CLIENT
		if( xNpc.isDynamicCollision )
		{
			dynamicCollNpcs_.insert(make_pair(xNpc.name, xNpc));
		}
#endif

		//next node
		pNpc = pNpc->NextSiblingElement();
	}

	return File_Success;
}

int NpcInfo::SaveNpcConfig( const char* path )
{
 	if (path == NULL || *path == NULL)
	{
		return Param_Error;
	}

	MeXmlDocument xMeXmlDoc;
	xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
	
	MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild(("Project"))->ToElement();

	pRoot->SetAttribute("Type", "Npc");

	SYSTEMTIME xSystemTime;
	::GetLocalTime(&xSystemTime);
	char szTime[50] = "";
	sprintf_s(szTime, sizeof(szTime) -1 , "%d-%d-%d %d:%d:%d", 
		xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay, xSystemTime.wHour, xSystemTime.wMinute, xSystemTime.wSecond);
	pRoot->SetAttribute("Value", szTime);

	pRoot->SetAttribute("Count", static_cast<int>(npcs_.size()));

	MeXmlElement* pNpcs = pRoot->InsertEndChild(("Npcs"))->ToElement();
	if(pNpcs == NULL)  return Attribute_Error;

	NpcsIter iter = npcs_.begin();
	NpcsIter end = npcs_.end();

	for (; iter != end; ++iter)
	{
	
		MeXmlElement* pNpc = pNpcs->InsertEndChild(("Npc"))->ToElement();

		pNpc->SetAttribute("Id", iter->second.id);

		Common::_tstring name = iter->second.name;		
		pNpc->SetAttribute("Name", name.toUTF8().c_str());

		Common::_tstring namepinyin = iter->second.pinyin;		
		pNpc->SetAttribute("PinYin", namepinyin.toUTF8().c_str());

		pNpc->SetAttribute("MapId", iter->second.mapId);
		pNpc->SetAttribute("Level", iter->second.level);
		pNpc->SetAttribute("Type", iter->second.type);
		pNpc->SetAttribute("ModelId", iter->second.modelId);
		pNpc->SetDoubleAttribute("PositionX", iter->second.x);
		pNpc->SetDoubleAttribute("PositionY", iter->second.y);
		pNpc->SetDoubleAttribute("PositionZ", iter->second.z);

		pNpc->SetAttribute("MovePath", iter->second.movePath);

		pNpc->SetAttribute("Direction", iter->second.direction);
		pNpc->SetAttribute("CanChangeDirection", static_cast<int>(iter->second.canChangeDirection));

		Common::_tstring scriptFile = iter->second.triggerScript;		
		pNpc->SetAttribute("ScriptFile", scriptFile.toUTF8().c_str());

		Common::_tstring actionScript = iter->second.actionScript;		
		pNpc->SetAttribute("actionScript", actionScript.toUTF8().c_str());

		pNpc->SetAttribute("IsMiniShow", static_cast<int>(iter->second.isMiniShow));
		pNpc->SetAttribute("IsWorldShow", static_cast<int>(iter->second.isWorldShow));
		pNpc->SetAttribute("IsCollision", static_cast<int>(iter->second.isCollision));
		pNpc->SetAttribute("IsDynamicCollision", static_cast<int>(iter->second.isDynamicCollision));

		Common::_tstring title = iter->second.title;		
		pNpc->SetAttribute("Title", title.toUTF8().c_str());

		Common::_tstring tip = iter->second.tip;
		pNpc->SetAttribute("NpcTips", tip.toUTF8().c_str());

		Common::_tstring headPicture = iter->second.strHeadPicture;
		pNpc->SetAttribute("HeadPicture", headPicture.toUTF8().c_str());		

		pNpc->SetDoubleAttribute("BodyScale", iter->second.bodyScale);

		pNpc->SetAttribute("Country", static_cast<int>(iter->second.uchCountryID));
		pNpc->SetAttribute("phyle", static_cast<int>(iter->second.phyle));
		pNpc->SetAttribute("MenuId", static_cast<int>(iter->second.nTaskMenu));

		Common::_tstring strSoundPath = iter->second.strSoundPath;
		pNpc->SetAttribute("SoundPath", strSoundPath.toUTF8().c_str());	
		pNpc->SetDoubleAttribute("GutUIScale",iter->second.gutUIScale);
		pNpc->SetAttribute("GutUIOffsetX",iter->second.gutUIOffsetX);
		pNpc->SetAttribute("GutUIOffsetY",iter->second.gutUIOffsetY);
		



		for (int i = 0 ;i < iter->second.vctSaluteData.size();++i)
		{
			if (iter->second.id != iter->second.vctSaluteData[i].shId)
			{
				continue;
			}

			MeXmlElement* pActions = pNpc->InsertEndChild(("Actions"))->ToElement();
			MeXmlElement* pAction = pActions->InsertEndChild(("Action"))->ToElement();
			MeXmlElement* pRequires = pAction->InsertEndChild(("Requires"))->ToElement();
			MeXmlElement* pRequire = pRequires->InsertEndChild(("Require"))->ToElement();
			pRequire->SetAttribute("Type",iter->second.vctSaluteData[i].shType1);
			pRequire->SetAttribute("Min",iter->second.vctSaluteData[i].shMin);
			pRequire->SetAttribute("Max",iter->second.vctSaluteData[i].shMax);
			pRequire->SetAttribute("Need",iter->second.vctSaluteData[i].shNeed);
			
			MeXmlElement* pEvents = pAction->InsertEndChild(("Events"))->ToElement();
			MeXmlElement* pEvent = pEvents->InsertEndChild(("Event"))->ToElement();
			pEvent->SetAttribute("Type",iter->second.vctSaluteData[i].shType2);
			Common::_tstring SaluteName = iter->second.vctSaluteData[i].strSaluteName;
			pEvent->SetAttribute("Name",SaluteName.toUTF8().c_str());
			pEvent->SetAttribute("Probability",iter->second.vctSaluteData[i].shProbability);
			pEvent->SetAttribute("DelayTime",iter->second.vctSaluteData[i].shDelayTime);
			

		   /* MeXmlElement* pFightInfo = pNpc->InsertEndChild(("FightInfo"))->ToElement();
			pFightInfo->SetAttribute("View",iter->second.vctSaluteData[i].shView);*/
		
		}


		for (int i = 0;i < iter->second.vctActionData.size(); ++i)
		{
			if (iter->second.id != iter->second.vctActionData[i].shId)
			{
				continue;
			}

			MeXmlElement* pElapseTime = pNpc->InsertEndChild(("ElapseTime"))->ToElement();
			pElapseTime->SetAttribute("Id", iter->second.vctActionData[i].CycleId);
			pElapseTime->SetAttribute("Time",iter->second.vctActionData[i].shElapseTime);
			pElapseTime->SetAttribute("NextTimeId",iter->second.vctActionData[i].shNextId);
			
			for (int j = 0;j < iter->second.vctActionData[i].vctActions.size();++j)
			{
				MeXmlElement* pActions = pElapseTime->InsertEndChild(("Actions"))->ToElement();
				MeXmlElement* pAction = pActions->InsertEndChild(("Action"))->ToElement();
				Common::_tstring ActionName = iter->second.vctActionData[i].vctActions[j].strAnimName;
				pAction->SetAttribute("Name",ActionName.toUTF8().c_str());
				pAction->SetAttribute("Probability",iter->second.vctActionData[i].vctActions[j].shProbability);
			}
			for (int z = 0; z < iter->second.vctActionData[i].vctTalks.size();++z )
			{
				MeXmlElement* pTalks = pElapseTime->InsertEndChild(("Talks"))->ToElement();
				MeXmlElement* pTalk = pTalks->InsertEndChild(("Talk"))->ToElement();
				pTalk->SetAttribute("StringId",iter->second.vctActionData[i].vctTalks[z].shStringId);
				pTalk->SetAttribute("Probability",iter->second.vctActionData[i].vctTalks[z].shProbability);
			}		
			
		}

		for (int i = 0; i < iter->second.fightData.size(); i++)
		{
			if (iter->second.id != iter->second.fightData[i].npcId)
			{
				continue;
			}

			MeXmlElement* pFightInfo = pNpc->InsertEndChild(("FightInfo"))->ToElement();
			pFightInfo->SetAttribute("Id", iter->second.fightData[i].npcId);
			pFightInfo->SetDoubleAttribute("BodyLength", iter->second.fightData[i].bodyLength);
			pFightInfo->SetAttribute("Level", iter->second.fightData[i].level);
			pFightInfo->SetAttribute("HpMax", iter->second.fightData[i].hpMax);
			pFightInfo->SetAttribute("MpMax", iter->second.fightData[i].mpMax);

			pFightInfo->SetDoubleAttribute("PhyAttack", iter->second.fightData[i].attackPhysics);
			pFightInfo->SetDoubleAttribute("MagAttack", iter->second.fightData[i].attackMagic);
			pFightInfo->SetDoubleAttribute("DefnedPhysics", iter->second.fightData[i].defendPhysics);
			pFightInfo->SetDoubleAttribute("DefnedMagic", iter->second.fightData[i].defendMagic);
			pFightInfo->SetDoubleAttribute("AttackSpeed", iter->second.fightData[i].attackSpeed);

			pFightInfo->SetDoubleAttribute("MoveSpeed", iter->second.fightData[i].moveSpeed);
			pFightInfo->SetDoubleAttribute("HpRestore", iter->second.fightData[i].hpRestore);
			pFightInfo->SetDoubleAttribute("MpRestore", iter->second.fightData[i].mpRestore);
			pFightInfo->SetAttribute("Exact", iter->second.fightData[i].exact);
			pFightInfo->SetAttribute("Dodge", iter->second.fightData[i].dodge);

			pFightInfo->SetAttribute("Critical", iter->second.fightData[i].critical);
			pFightInfo->SetAttribute("Tenacity", iter->second.fightData[i].tenacity);
			pFightInfo->SetAttribute("CriticalIntensity", iter->second.fightData[i].criticalIntensity);
			pFightInfo->SetAttribute("BackStrike", iter->second.fightData[i].backStrike);
			pFightInfo->SetAttribute("BackStrikeResist", iter->second.fightData[i].backStrikeResist);

			pFightInfo->SetAttribute("BreakStrike", iter->second.fightData[i].breakStrike);
			pFightInfo->SetAttribute("StabStrike", iter->second.fightData[i].stabStrike);
			pFightInfo->SetAttribute("ElementStrike", iter->second.fightData[i].elementStrike);
			pFightInfo->SetAttribute("ToxinStrike", iter->second.fightData[i].toxinStrike);
			pFightInfo->SetAttribute("SpiritStrike", iter->second.fightData[i].spiritStrike);

			pFightInfo->SetAttribute("BreakResist", iter->second.fightData[i].breakResist);
			pFightInfo->SetAttribute("StabResist", iter->second.fightData[i].stabResist);
			pFightInfo->SetAttribute("ElementResist", iter->second.fightData[i].elementResist);
			pFightInfo->SetAttribute("ToxinResist", iter->second.fightData[i].toxinResist);
			pFightInfo->SetAttribute("SpiritResist", iter->second.fightData[i].spiritResist);

			pFightInfo->SetAttribute("NormalAttackMin", iter->second.fightData[i].normalAttackMin);
			pFightInfo->SetAttribute("NormalAttackMax", iter->second.fightData[i].normalAttackMax);
			pFightInfo->SetAttribute("View", iter->second.fightData[i].view);
			pFightInfo->SetAttribute("FightView", iter->second.fightData[i].fightView);
			pFightInfo->SetAttribute("CatchTime", iter->second.fightData[i].catchTime);

			pFightInfo->SetDoubleAttribute("MoveStep", iter->second.fightData[i].moveStep);
			pFightInfo->SetDoubleAttribute("IdleMoveSpeed", iter->second.fightData[i].idleMoveSpeed);
			pFightInfo->SetDoubleAttribute("IdleMoveStep", iter->second.fightData[i].idleMoveStep);
			pFightInfo->SetAttribute("ReliveTime", iter->second.fightData[i].reliveTime);
			Common::_tstring deadScript = iter->second.fightData[i].deadScript;
			pFightInfo->SetAttribute("DeadScript", deadScript.toUTF8().c_str());

			pFightInfo->SetAttribute("IsInitiative", iter->second.fightData[i].isInitiative);
			pFightInfo->SetAttribute("DisappearTime", iter->second.fightData[i].disappearTime);
			pFightInfo->SetAttribute("EnmityDecRate", iter->second.fightData[i].enmityDecRate);
			pFightInfo->SetAttribute("EnmityView", iter->second.fightData[i].enmityView);
			pFightInfo->SetAttribute("MaxRange", iter->second.fightData[i].maxRange);

			pFightInfo->SetAttribute("ChangePassive", iter->second.fightData[i].changePassive);
			pFightInfo->SetAttribute("PassiveTime", iter->second.fightData[i].passiveTime);
			pFightInfo->SetAttribute("BaseEnmityRange", iter->second.fightData[i].baseEnmityRange);
			pFightInfo->SetAttribute("Intergal", iter->second.fightData[i].integral);
			pFightInfo->SetAttribute("RouteId", iter->second.fightData[i].routeId);

			pFightInfo->SetAttribute("Skill1Id", iter->second.fightData[i].skills[0].skillId);
			pFightInfo->SetAttribute("Skill1Level", iter->second.fightData[i].skills[0].skillLevel);
			pFightInfo->SetAttribute("Skill1Rate", iter->second.fightData[i].skills[0].skillRate);

			pFightInfo->SetAttribute("Skill2Id", iter->second.fightData[i].skills[1].skillId);
			pFightInfo->SetAttribute("Skill2Level", iter->second.fightData[i].skills[1].skillLevel);
			pFightInfo->SetAttribute("Skill2Rate", iter->second.fightData[i].skills[1].skillRate);

			pFightInfo->SetAttribute("Skill3Id", iter->second.fightData[i].skills[2].skillId);
			pFightInfo->SetAttribute("Skill3Level", iter->second.fightData[i].skills[2].skillLevel);
			pFightInfo->SetAttribute("Skill3Rate", iter->second.fightData[i].skills[2].skillRate);

			pFightInfo->SetAttribute("FightType", iter->second.fightData[i].fightType);
			pFightInfo->SetAttribute("FightCamp", iter->second.fightData[i].fightCamp);
		}
		
		

		//MeXmlElement* pElapseTime = pNpc->InsertEndChild(("ElapseTime"))->ToElement();//zhuxincong 2012.7.18
		//pElapseTime->SetAttribute("Id", iter->second.ActionDataid);
		//pElapseTime->SetAttribute("Time",iter->second.npctime);
		//pElapseTime->SetAttribute("NextId",iter->second.NextId);

		//MeXmlElement* pActions = pElapseTime->InsertEndChild(("Actions"))->ToElement();
		//MeXmlElement* pAction = pActions->InsertEndChild(("Action"))->ToElement();
		//Common::_tstring strActionName = iter->second.ActionName;
		//pAction->SetAttribute("Name",strActionName.toUTF8().c_str());
		//pAction->SetAttribute("Probability",iter->second.ActionProbability);

		//MeXmlElement* pTalks = pElapseTime->InsertEndChild(("Talks"))->ToElement();
		//MeXmlElement* pTalk = pTalks->InsertEndChild(("Talk"))->ToElement();
		//pTalk->SetAttribute("StringId",iter->second.TalkStringid);
		//pTalk->SetAttribute("Probability",iter->second.TalkshProbability);
		
	}

	return (!xMeXmlDoc.SaveFile(path));
}


void NpcInfo::AddNpc(Npc &xNpc)
{
	npcs_.insert(make_pair(xNpc.id, xNpc));

#ifdef GAME_CLIENT
	if( xNpc.isDynamicCollision )
	{
		dynamicCollNpcs_.insert(make_pair(xNpc.name, xNpc));
	}
#endif
}


NpcInfo::Npc* NpcInfo::GetNpcByStaticId(int id)
{
	if (id < 0)
	{
		return NULL;
	}

	NpcsIter iter = npcs_.find(id);
	if (iter != npcs_.end())
	{
		return &(iter->second);
	}

	return NULL;
}

NpcInfo::Npc* NpcInfo::FindNpcByDynamicId(int id)
{
	if (id < 0)
	{
		return NULL;
	}

	NpcsIter iter = npcs_.begin();
	NpcsIter end = npcs_.end();

	for ( ; iter != end; ++iter)
	{
		if (iter->second.dynamicId == id)
		{
			return &(iter->second);
		}
	}

	return NULL;
}

NpcInfo::Npc* NpcInfo::GetNpcByName(std::string name,uint32 mapId)
{
	if (name.empty())
	{
		return NULL;
	}

	NpcsIter iter = npcs_.begin();
	NpcsIter end = npcs_.end();

	for ( ; iter != end; ++iter)
	{
		if (iter->second.name == name)
		{
			if (mapId == -1 || (iter->second.mapId == mapId))
			{
				return &(iter->second);
			}
		}
	}

	return NULL;
}

uint32 NpcInfo::GetNpcs(uint32 id, std::vector<NpcInfo::Npc*>& outResult )
{
    outResult.clear();
    NpcsIter iter = npcs_.begin();
    NpcsIter end  = npcs_.end();

    for (;iter != end;++iter)
        if(iter->second.id == id)
            outResult.push_back(&iter->second);

    if(outResult.size() > 0)
        return ER_Success;
    return ER_Failed;
}

NpcInfo::Npc* NpcInfo::GetNpc(uint32 id, uint32 mapId )
{
    NpcsIter iter = npcs_.begin();
    NpcsIter end  = npcs_.end();
    for (;iter != end;++iter)
        if(iter->second.id == id &&iter->second.mapId == mapId)
            return &iter->second;

    return NULL;
}
#ifdef GAME_CLIENT
NpcInfo::Npc* NpcInfo::GetDynamicCollNpcByName( std::string name, uint32 mapId )
{
	if (name.empty())
	{
		return NULL;
	}

	DynCollNpcsIter iter = dynamicCollNpcs_.find(name);
	if (iter != dynamicCollNpcs_.end())
	{
		if ( iter->second.mapId == mapId )
		{
			return &(iter->second);
		}
	}

	return NULL;
}
#endif