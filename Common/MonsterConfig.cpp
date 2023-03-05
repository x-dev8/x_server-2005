#include "MonsterConfig.h"


CMonsterConfig::CMonsterConfig()
{

}

CMonsterConfig::~CMonsterConfig()
{

}

void CMonsterConfig::ProcessLoadZoneInfo( XMLElement* element, int nZoneNumber )
{

}

void CMonsterConfig::ProcessLoadMonsterGroup( XMLElement* element, int nZoneNumber )
{

}

void CMonsterConfig::exportXML( CStageDataLoader* pStageDataLoader, int i )
{
    pStageDataLoader->beginFlag( "MonsterGroupInfo" );
    //pStageDataLoader->writeString( "MonsterGroupIntro", m_vecMonster[i].m_strIntro.c_str(), m_vecMonster[i].m_strIntro.length() );
    pStageDataLoader->writeInt( "ZoneId", m_vecMonster[i].m_iZone );
    pStageDataLoader->writeFloat( "X", m_vecMonster[i].m_nX );
    pStageDataLoader->writeFloat( "Y", m_vecMonster[i].m_nY );
    pStageDataLoader->writeBool( "RandRange", m_vecMonster[i].m_bRandRange );
    pStageDataLoader->writeInt( "Dir", m_vecMonster[i].m_nDir );
    //pStageDataLoader->writeString( "TemplateName", m_vecMonster[i].m_strName.c_str(), m_vecMonster[i].m_strName.length() );
    pStageDataLoader->writeInt( "Index", m_vecMonster[i].m_nId );
    pStageDataLoader->writeInt( "Number", m_vecMonster[i].m_iNumber );
    //pStageDataLoader->writeInt( "Relife", m_vecMonster[i].m_iRelife );
    pStageDataLoader->writeInt( "County", m_vecMonster[i].m_iCountry );
    pStageDataLoader->writeBool( "Enable", m_vecMonster[i].m_bEnable );
    pStageDataLoader->writeBool( "Hide", m_vecMonster[i].m_bHide );
    pStageDataLoader->writeString( "DeadScript", m_vecMonster[i].m_strScriptName.c_str(), m_vecMonster[i].m_strScriptName.length() );
    pStageDataLoader->writeString( "LuaScript", m_vecMonster[i].m_strLuaScript.c_str(), m_vecMonster[i].m_strLuaScript.length() );
    pStageDataLoader->writeInt( "AIValue", m_vecMonster[i].m_iAiValue );
    pStageDataLoader->writeInt( "Camp", m_vecMonster[i].m_nFightCamp );
    pStageDataLoader->writeInt( "Force", m_vecMonster[i].m_nForce );
    pStageDataLoader->writeInt( "Path", m_vecMonster[i].m_nRouteID );
    pStageDataLoader->EndParam();
    pStageDataLoader->EndFlag( "MonsterGroupInfo" );

    //pStageDataLoader->beginFlag( "MonsterAITrigger" );
    //pStageDataLoader->EndParam();
    //{
    //	for( int a = 0;a < m_vecMonster[i].m_monsterAITrigger.GetMaxMonsterAITrigger(); a++ )
    //	{
    //		pStageDataLoader->beginFlag( "AITrigger" );
    //		pStageDataLoader->EndParam();

    //		//介绍
    //		{
    //			pStageDataLoader->beginFlag( "TriggerIntro" );

    //			pStageDataLoader->writeString( "TriggerIntro", m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->szTriggerIntro,
    //				strlen(m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->szTriggerIntro) );

    //			pStageDataLoader->EndParam();
    //			pStageDataLoader->endFlag( "TriggerIntro" );
    //		}

    //		//事件
    //		{
    //			pStageDataLoader->beginFlag( "Event" );

    //			pStageDataLoader->writeString( "EventIntro", m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->event.szEventIntro,
    //				strlen(m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->event.szEventIntro) );

    //			pStageDataLoader->writeInt( "EventID", m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->event.stEventID );

    //			pStageDataLoader->EndParam();
    //			pStageDataLoader->endFlag( "Event" );
    //		}

    //		//条件
    //		{
    //			pStageDataLoader->beginFlag( "Condition" );

    //			pStageDataLoader->writeString( "ConditionIntro", m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->condition.szConditionIntro,
    //				strlen(m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->condition.szConditionIntro ) );

    //			pStageDataLoader->writeInt( "ConditionID", m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->condition.stConditionID );
    //			pStageDataLoader->writeInt( "Operator1", (int)m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->condition.byOperation[0] );
    //			pStageDataLoader->writeInt( "Value1", m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->condition.nValue[0] );

    //			pStageDataLoader->EndParam();
    //			pStageDataLoader->endFlag( "Condition" );
    //		}

    //		//动作
    //		{
    //			pStageDataLoader->beginFlag( "Action" );

    //			pStageDataLoader->writeString( "ActionIntro", m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->action.szActionIntro,
    //				strlen(m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->action.szActionIntro) );

    //			pStageDataLoader->writeInt( "ActionID", m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->action.stActionID );
    //			pStageDataLoader->writeInt( "Value1", m_vecMonster[i].m_monsterAITrigger.GetMonsterAITriggerByID(a)->action.nValue[0] );

    //			pStageDataLoader->EndParam();
    //			pStageDataLoader->endFlag( "Action" );
    //		}
    //		pStageDataLoader->EndFlag( "AITrigger" );
    //	}
    //}
    //pStageDataLoader->EndFlag( "MonsterAITrigger" );


    //pStageDataLoader->beginFlagNoParam( "MonsterDataCorrect");
    ////怪物配置属性
    //{
    //	pStageDataLoader->beginFlag( "OptionInfo");
    //	pStageDataLoader->writeString( "NameCorrect", m_vecMonster[i].m_strMonsterName.c_str(), m_vecMonster[i].m_strMonsterName.length() );
    //	pStageDataLoader->writeInt( "ModelIDCorrect", m_vecMonster[i].m_iModelIDCorrect );
    //	pStageDataLoader->writeInt( "TypeCorrect", m_vecMonster[i].m_iMonsterTypeCorrect );
    //	pStageDataLoader->writeString( "CreatureSoundCorrect", m_vecMonster[i].m_strCreatureSound.c_str(), m_vecMonster[i].m_strCreatureSound.length() );
    //	pStageDataLoader->EndParam();
    //	pStageDataLoader->endFlag( "OptionInfo" );
    //}

    ////怪物的基本属性
    //{
    //	pStageDataLoader->beginFlag( "BaseInfo" );
    //	pStageDataLoader->writeInt( "StrengthCorrect", m_vecMonster[i].m_iStrengthCorrect );
    //	pStageDataLoader->writeInt( "ConstitutionCorrect", m_vecMonster[i].m_iConstitutionCorrect );
    //	pStageDataLoader->writeInt( "AgilityCorrect", m_vecMonster[i].m_iAgilityCorrect );
    //	pStageDataLoader->writeInt( "MagicCorrect", m_vecMonster[i].m_iMagicCorrect );
    //	pStageDataLoader->writeInt( "IntelligenceCorrect", m_vecMonster[i].m_iIntelligenceCorrect );
    //	pStageDataLoader->writeInt( "CharmCorrect", m_vecMonster[i].m_iCharmCorrect );
    //	pStageDataLoader->EndParam();
    //	pStageDataLoader->EndFlag( "BaseInfo" );
    //}

    ////怪物的战斗属性
    //{
    //	pStageDataLoader->beginFlag( "FightInfo" );
    //	pStageDataLoader->writeInt( "LevelCorrect", m_vecMonster[i].m_iLevelCorrect );
    //	pStageDataLoader->writeInt( "RewardExpCorrect", m_vecMonster[i].m_iRewardExpCorrect );
    //	pStageDataLoader->writeInt( "BodySizeCorrect", m_vecMonster[i].m_iBodySizeCorrect );
    //	pStageDataLoader->writeInt( "HpMaxCorrect", m_vecMonster[i].m_iHpMaxCorrect );
    //	pStageDataLoader->writeInt( "MpMaxCorrect", m_vecMonster[i].m_iMpMaxCorrect );
    //	pStageDataLoader->writeInt( "HpRestoreCorrect", m_vecMonster[i].m_iHpRestoreCorrect );
    //	pStageDataLoader->writeInt( "MpRestoreCorrect", m_vecMonster[i].m_iMpRestoreCorrect );
    //	pStageDataLoader->writeInt( "ExactCorrect", m_vecMonster[i].m_iExactCorrect );
    //	pStageDataLoader->writeInt( "DodgeCorrect", m_vecMonster[i].m_iDodgeCorrect );
    //	pStageDataLoader->writeInt( "ViewCorrect", m_vecMonster[i].m_iViewCorrect );
    //	pStageDataLoader->writeInt( "PhysicsMaxCorrect", m_vecMonster[i].m_iPhysicsMaxCorrect );
    //	pStageDataLoader->writeInt( "PhysicsMinCorrect", m_vecMonster[i].m_iPhysicsMinCorrect );
    //	pStageDataLoader->writeInt( "MagicMaxCorrect", m_vecMonster[i].m_iMagicMaxCorrect );
    //	pStageDataLoader->writeInt( "MagicMinCorrect", m_vecMonster[i].m_iMagicMinCorrect );
    //	pStageDataLoader->writeInt( "CriticalRateCorrect", m_vecMonster[i].m_iCriticalRateCorrect );
    //	pStageDataLoader->writeInt( "AttackRateCorrect", m_vecMonster[i].m_iAttackRateCorrect );
    //	pStageDataLoader->writeInt( "PhysicsDefCorrect", m_vecMonster[i].m_iPhysicsDefCorrect );
    //	pStageDataLoader->writeInt( "MagicDefCorrect", m_vecMonster[i].m_iMagicDefCorrect );
    //	pStageDataLoader->writeInt( "CatchTimeCorrect", m_vecMonster[i].m_iCatchTimeCorrect );
    //	pStageDataLoader->writeFloat( "MoveSpeedCorrect", m_vecMonster[i].m_fMoveSpeedCorrect );
    //	pStageDataLoader->EndParam();
    //	pStageDataLoader->EndFlag( "FightInfo" );
    //}

    ////怪物的元素攻击
    //{
    //	pStageDataLoader->beginFlag( "ElementAtt" );
    //	pStageDataLoader->writeInt( "FrostAttCorrect", m_vecMonster[i].m_iFrostAttCorrect );
    //	pStageDataLoader->writeInt( "BlazeAttCorrect", m_vecMonster[i].m_iBlazeAttCorrect );
    //	pStageDataLoader->writeInt( "ThunderAttCorrect", m_vecMonster[i].m_iThunderAttCorrect );
    //	pStageDataLoader->writeInt( "PoisonAttCorrect", m_vecMonster[i].m_iPoisonAttCorrect );
    //	pStageDataLoader->EndParam();
    //	pStageDataLoader->EndFlag( "ElementAtt" );
    //}

    ////怪物的元素抗性
    //{
    //	pStageDataLoader->beginFlag( "ElementDef" );
    //	pStageDataLoader->writeInt( "FrostDefCorrect", m_vecMonster[i].m_iFrostDefCorrect );
    //	pStageDataLoader->writeInt( "BlazeDefCorrect", m_vecMonster[i].m_iBlazeDefCorrect );
    //	pStageDataLoader->writeInt( "ThunderDefCorrect", m_vecMonster[i].m_iThunderDefCorrect );
    //	pStageDataLoader->writeInt( "PoisonDefCorrect", m_vecMonster[i].m_iPoisonDefCorrect );
    //	pStageDataLoader->EndParam();
    //	pStageDataLoader->EndFlag( "ElementDef" );
    //}

    ////怪物的技能文件
    //{
    //	pStageDataLoader->beginFlag( "Skill" );
    //	pStageDataLoader->writeInt( "Skill1Correct", m_vecMonster[i].m_iSkill1Correct );
    //	pStageDataLoader->writeInt( "Skill2Correct", m_vecMonster[i].m_iSkill2Correct );
    //	pStageDataLoader->writeInt( "Skill3Correct", m_vecMonster[i].m_iSkill3Correct );
    //	pStageDataLoader->writeInt( "Skill1LevelCorrect", m_vecMonster[i].m_iSkill1LevelCorrect );
    //	pStageDataLoader->writeInt( "Skill2LevelCorrect", m_vecMonster[i].m_iSkill2LevelCorrect );
    //	pStageDataLoader->writeInt( "Skill3LevelCorrect", m_vecMonster[i].m_iSkill3LevelCorrect );
    //	pStageDataLoader->writeInt( "Skill1RateCorrect", m_vecMonster[i].m_iSkill1RateCorrect );
    //	pStageDataLoader->writeInt( "Skill2RateCorrect", m_vecMonster[i].m_iSkill2RateCorrect );
    //	pStageDataLoader->writeInt( "Skill3RateCorrect", m_vecMonster[i].m_iSkill3RateCorrect );
    //	pStageDataLoader->EndParam();
    //	pStageDataLoader->EndFlag( "Skill" );
    //}

    ////怪物的包裹文件
    //{
    //	pStageDataLoader->beginFlagNoParam( "ItemBag" );

    //	{
    //		pStageDataLoader->beginFlag( "StandardBag" );
    //		pStageDataLoader->writeInt( "Item1Correct", m_vecMonster[i].m_iItem1Correct );
    //		pStageDataLoader->writeInt( "Item2Correct", m_vecMonster[i].m_iItem2Correct );
    //		pStageDataLoader->writeInt( "Item3Correct", m_vecMonster[i].m_iItem3Correct );
    //		pStageDataLoader->writeInt( "Item4Correct", m_vecMonster[i].m_iItem4Correct );
    //		pStageDataLoader->writeInt( "Item5Correct", m_vecMonster[i].m_iItem5Correct );
    //		pStageDataLoader->writeInt( "Item6Correct", m_vecMonster[i].m_iItem6Correct );
    //		pStageDataLoader->writeInt( "Item1RateCorrect", m_vecMonster[i].m_iItem1RateCorrect );
    //		pStageDataLoader->writeInt( "Item2RateCorrect", m_vecMonster[i].m_iItem2RateCorrect );
    //		pStageDataLoader->writeInt( "Item3RateCorrect", m_vecMonster[i].m_iItem3RateCorrect );
    //		pStageDataLoader->writeInt( "Item4RateCorrect", m_vecMonster[i].m_iItem4RateCorrect );
    //		pStageDataLoader->writeInt( "Item5RateCorrect", m_vecMonster[i].m_iItem5RateCorrect );
    //		pStageDataLoader->writeInt( "Item6RateCorrect", m_vecMonster[i].m_iItem6RateCorrect );
    //		pStageDataLoader->writeInt( "DropMoneyMaxCorrect", m_vecMonster[i].m_iDropMoneyMaxCorrect );
    //		pStageDataLoader->writeInt( "DropMoneyMinCorrect", m_vecMonster[i].m_iDropMoneyMinCorrect );
    //		pStageDataLoader->writeFloat( "DropMultipleRateCorrect", m_vecMonster[i].m_fDropMultipleRateCorrect );
    //		pStageDataLoader->EndParam();
    //		pStageDataLoader->EndFlag( "StandardBag" );
    //	}

    //	int nItemTol = (int)m_vecMonster[i].m_Items.size();
    //	if ( nItemTol > 0 )
    //	{
    //		for( int x = 0; x < nItemTol; x++ )
    //		{
    //			pStageDataLoader->beginFlag( "AddItemToBag" );
    //			pStageDataLoader->writeString( "ItemName", m_vecMonster[i].m_Items[x].m_strName.c_str(), m_vecMonster[i].m_Items[x].m_strName.length() );
    //			pStageDataLoader->writeInt( "ItemDropRate", m_vecMonster[i].m_Items[x].m_iRate );
    //			pStageDataLoader->EndParam();
    //			pStageDataLoader->endFlag( "AddItemToBag" );
    //		}
    //	}
    //	pStageDataLoader->endFlag( "ItemBag" );
    //}
    //pStageDataLoader->EndFlag( "MonsterDataCorrect");
}

void CMonsterConfig::Clear()
{
    CSALocker lock(_lock);
	m_vecMonster.clear();
}

int CMonsterConfig::GetMonsterCount()
{
    CSALocker lock(_lock);
	return m_vecMonster.size();
}

SMapMonsterInfo* CMonsterConfig::GetMapMonsterInfo( int nIndex )
{   
    CSALocker lock(_lock);
    if ( nIndex<0 || nIndex>=m_vecMonster.size())
    { return NULL;}
    return &m_vecMonster[nIndex];
}

void CMonsterConfig::loadXML( CStageDataLoader* pStageDataLoader, XMLElement* element, int nZoneNumber )
{
    XMLElement* MonsterGroupChild = NULL;
    XMLElement* MonsterDataCorrectChild = NULL;
    XMLElement* ItemBagChild = NULL;
    XMLElement* AITriggerCount = NULL;
    XMLElement* AITriggerChild = NULL;

    SMapMonsterInfo cm_MonsterStruct;

    for( int i = 0; i < element->getChildrenCount(); i++ )
    {
        if( !( MonsterGroupChild = element->getChild(i) )  )
            continue;

        if( MonsterGroupChild->getName() == "MonsterGroupInfo" )
        {
            //pStageDataLoader->GetValue( cm_MonsterStruct.m_strIntro, MonsterGroupChild->getChildByName( "MonsterGroupIntro" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_iZone, MonsterGroupChild->getChildByName( "ZoneId" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_nX, MonsterGroupChild->getChildByName( "X" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_nY, MonsterGroupChild->getChildByName( "Y" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_bRandRange, MonsterGroupChild->getChildByName( "RandRange" ));
            pStageDataLoader->GetValue( cm_MonsterStruct.m_nDir, MonsterGroupChild->getChildByName( "Dir" ) );
            //pStageDataLoader->GetValue( cm_MonsterStruct.m_strName, MonsterGroupChild->getChildByName( "TemplateName" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_nId, MonsterGroupChild->getChildByName( "Index" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_iNumber, MonsterGroupChild->getChildByName( "Number" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_iRelife, MonsterGroupChild->getChildByName( "Relife" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_iCountry, MonsterGroupChild->getChildByName( "County" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_bEnable, MonsterGroupChild->getChildByName( "Enable" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_bHide, MonsterGroupChild->getChildByName( "Hide" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_strScriptName, MonsterGroupChild->getChildByName( "DeadScript" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_strLuaScript, MonsterGroupChild->getChildByName( "LuaScript" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_iAiValue, MonsterGroupChild->getChildByName( "AIValue" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_nFightCamp, MonsterGroupChild->getChildByName( "Camp" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_nForce, MonsterGroupChild->getChildByName( "Force" ) );
            pStageDataLoader->GetValue( cm_MonsterStruct.m_nRouteID, MonsterGroupChild->getChildByName( "Path" ) );
            //cm_MonsterStruct.m_iZone = nZoneNumber;
        }

        //	if( MonsterGroupChild->getName() == "MonsterAITrigger" )
        //	{
        //		for ( int a = 0; a < MonsterGroupChild->getChildrenCount(); a++ )
        //		{
        //			if( !( AITriggerCount = MonsterGroupChild->getChild(a) ) )
        //				continue;

        //			if( AITriggerCount->getName() == "AITrigger" )
        //			{
        //				SMonsterTrigger monstertrigger;

        //				for ( int b = 0; b < AITriggerCount->getChildrenCount(); b++ )
        //				{
        //					if( !( AITriggerChild = AITriggerCount->getChild(b) ) )
        //						continue;

        //					if( AITriggerChild->getName() == "TriggerIntro" )
        //					{
        //						pStageDataLoader->GetValue( monstertrigger.szTriggerIntro, AITriggerChild->getChildByName( "TriggerIntro" ), sizeof(monstertrigger.szTriggerIntro) );
        //					}


        //					if( AITriggerChild->getName() == "Event" )
        //					{
        //						pStageDataLoader->GetValue( monstertrigger.event.szEventIntro, AITriggerChild->getChildByName( "EventIntro" ), sizeof(monstertrigger.event.szEventIntro) );
        //						pStageDataLoader->GetValue( monstertrigger.event.stEventID, AITriggerChild->getChildByName( "EventID" ) );
        //					}

        //					if( AITriggerChild->getName() == "Condition" )
        //					{
        //						pStageDataLoader->GetValue( monstertrigger.condition.szConditionIntro, AITriggerChild->getChildByName( "ConditionIntro" ), sizeof(monstertrigger.condition.szConditionIntro) );
        //						pStageDataLoader->GetValue( monstertrigger.condition.stConditionID, AITriggerChild->getChildByName( "ConditionID" ) );
        //						pStageDataLoader->GetValue( monstertrigger.condition.byOperation[0], AITriggerChild->getChildByName( "Operator1" ) );
        //						pStageDataLoader->GetValue( monstertrigger.condition.nValue[0], AITriggerChild->getChildByName( "Value1" ) );
        //					}

        //					if( AITriggerChild->getName() == "Action" )
        //					{
        //						pStageDataLoader->GetValue( monstertrigger.action.szActionIntro, AITriggerChild->getChildByName( "ActionIntro" ), sizeof(monstertrigger.action.szActionIntro) );
        //						pStageDataLoader->GetValue( monstertrigger.action.stActionID, AITriggerChild->getChildByName( "ActionID" ) );
        //						pStageDataLoader->GetValue( monstertrigger.action.nValue[0], AITriggerChild->getChildByName( "Value1" ) );
        //					}
        //				}
        //				cm_MonsterStruct.m_monsterAITrigger.AddMonsterAITrigger( monstertrigger );
        //			}
        //		}
        //	}

        //	if( MonsterGroupChild->getName() == "MonsterDataCorrect" )
        //	{
        //		for ( int j = 0; j < MonsterGroupChild->getChildrenCount(); j++ )
        //		{
        //			if( !( MonsterDataCorrectChild = MonsterGroupChild->getChild(j) )  )
        //				continue;

        //			if( MonsterDataCorrectChild->getName() == "OptionInfo" )
        //			{
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_strMonsterName, MonsterDataCorrectChild->getChildByName( "NameCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iModelIDCorrect, MonsterDataCorrectChild->getChildByName( "ModelIDCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iMonsterTypeCorrect, MonsterDataCorrectChild->getChildByName( "TypeCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_strCreatureSound, MonsterDataCorrectChild->getChildByName( "CreatureSoundCorrect" ) );
        //			}

        //			if( MonsterDataCorrectChild->getName() == "BaseInfo" )
        //			{
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iStrengthCorrect, MonsterDataCorrectChild->getChildByName( "StrengthCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iConstitutionCorrect, MonsterDataCorrectChild->getChildByName( "ConstitutionCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iAgilityCorrect, MonsterDataCorrectChild->getChildByName( "AgilityCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iMagicCorrect, MonsterDataCorrectChild->getChildByName( "MagicCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iIntelligenceCorrect, MonsterDataCorrectChild->getChildByName( "IntelligenceCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iCharmCorrect, MonsterDataCorrectChild->getChildByName( "CharmCorrect" ) );
        //			}

        //			if( MonsterDataCorrectChild->getName() == "FightInfo" )
        //			{
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iBodySizeCorrect, MonsterDataCorrectChild->getChildByName( "BodySizeCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iLevelCorrect, MonsterDataCorrectChild->getChildByName( "LevelCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iRewardExpCorrect, MonsterDataCorrectChild->getChildByName( "RewardExpCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iHpMaxCorrect, MonsterDataCorrectChild->getChildByName( "HpMaxCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iMpMaxCorrect, MonsterDataCorrectChild->getChildByName( "MpMaxCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iHpRestoreCorrect, MonsterDataCorrectChild->getChildByName( "HpRestoreCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iMpRestoreCorrect, MonsterDataCorrectChild->getChildByName( "MpRestoreCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iExactCorrect, MonsterDataCorrectChild->getChildByName( "ExactCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iDodgeCorrect, MonsterDataCorrectChild->getChildByName( "DodgeCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iViewCorrect, MonsterDataCorrectChild->getChildByName( "ViewCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iPhysicsMaxCorrect, MonsterDataCorrectChild->getChildByName( "PhysicsMaxCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iPhysicsMinCorrect, MonsterDataCorrectChild->getChildByName( "PhysicsMinCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iMagicMaxCorrect, MonsterDataCorrectChild->getChildByName( "MagicMaxCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iMagicMinCorrect, MonsterDataCorrectChild->getChildByName( "MagicMinCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iCriticalRateCorrect, MonsterDataCorrectChild->getChildByName( "CriticalRateCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iAttackRateCorrect, MonsterDataCorrectChild->getChildByName( "AttackRateCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iPhysicsDefCorrect, MonsterDataCorrectChild->getChildByName( "PhysicsDefCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iMagicDefCorrect, MonsterDataCorrectChild->getChildByName( "MagicDefCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iCatchTimeCorrect, MonsterDataCorrectChild->getChildByName( "CatchTimeCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_fMoveSpeedCorrect, MonsterDataCorrectChild->getChildByName( "MoveSpeedCorrect" ) );
        //			}

        //			if( MonsterDataCorrectChild->getName() == "ElementAtt" )
        //			{
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iFrostAttCorrect, MonsterDataCorrectChild->getChildByName( "FrostAttCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iBlazeAttCorrect, MonsterDataCorrectChild->getChildByName( "FrostAttCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iThunderAttCorrect, MonsterDataCorrectChild->getChildByName( "ThunderAttCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iPoisonAttCorrect, MonsterDataCorrectChild->getChildByName( "PoisonAttCorrect" ) );
        //			}

        //			if( MonsterDataCorrectChild->getName() == "ElementDef" )
        //			{
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iFrostDefCorrect, MonsterDataCorrectChild->getChildByName( "FrostDefCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iBlazeDefCorrect, MonsterDataCorrectChild->getChildByName( "BlazeDefCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iThunderDefCorrect, MonsterDataCorrectChild->getChildByName( "ThunderDefCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iPoisonDefCorrect, MonsterDataCorrectChild->getChildByName( "PoisonDefCorrect" ) );
        //			}

        //			if( MonsterDataCorrectChild->getName() == "Skill" )
        //			{
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iSkill1Correct, MonsterDataCorrectChild->getChildByName( "Skill1Correct" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iSkill2Correct, MonsterDataCorrectChild->getChildByName( "Skill2Correct" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iSkill3Correct, MonsterDataCorrectChild->getChildByName( "Skill3Correct" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iSkill1LevelCorrect, MonsterDataCorrectChild->getChildByName( "Skill1LevelCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iSkill2LevelCorrect, MonsterDataCorrectChild->getChildByName( "Skill2LevelCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iSkill3LevelCorrect, MonsterDataCorrectChild->getChildByName( "Skill3LevelCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iSkill1RateCorrect, MonsterDataCorrectChild->getChildByName( "Skill1RateCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iSkill2RateCorrect, MonsterDataCorrectChild->getChildByName( "Skill2RateCorrect" ) );
        //				pStageDataLoader->GetValue( cm_MonsterStruct.m_iSkill3RateCorrect, MonsterDataCorrectChild->getChildByName( "Skill3RateCorrect" ) );
        //			}

        //			if( MonsterDataCorrectChild->getName() == "ItemBag" )
        //			{
        //				for( int t = 0; t < MonsterDataCorrectChild->getChildrenCount(); t++ )
        //				{
        //					if( !( ItemBagChild = MonsterDataCorrectChild->getChild(t) ) )
        //						continue;

        //					int nAddItemCount = 0;

        //					if ( ItemBagChild->getName() == "StandardBag" )
        //					{
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem1Correct, ItemBagChild->getChildByName( "Item1Correct" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem2Correct, ItemBagChild->getChildByName( "Item2Correct" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem3Correct, ItemBagChild->getChildByName( "Item3Correct" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem4Correct, ItemBagChild->getChildByName( "Item4Correct" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem5Correct, ItemBagChild->getChildByName( "Item5Correct" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem6Correct, ItemBagChild->getChildByName( "Item6Correct" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem1RateCorrect, ItemBagChild->getChildByName( "Item1RateCorrect" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem2RateCorrect, ItemBagChild->getChildByName( "Item2RateCorrect" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem3RateCorrect, ItemBagChild->getChildByName( "Item3RateCorrect" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem4RateCorrect, ItemBagChild->getChildByName( "Item4RateCorrect" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem5RateCorrect, ItemBagChild->getChildByName( "Item5RateCorrect" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iItem6RateCorrect, ItemBagChild->getChildByName( "Item6RateCorrect" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iDropMoneyMaxCorrect, ItemBagChild->getChildByName( "DropMoneyMaxCorrect" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_iDropMoneyMinCorrect, ItemBagChild->getChildByName( "DropMoneyMinCorrect" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_fDropMultipleRateCorrect, ItemBagChild->getChildByName( "DropMultipleRateCorrect" ) );
        //					}

        //					if ( ItemBagChild->getName() == "AddItemToBag" )
        //					{
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_Items[nAddItemCount].m_strName.c_str(), ItemBagChild->getChildByName( "ItemName" ) );
        //						pStageDataLoader->GetValue( cm_MonsterStruct.m_Items[nAddItemCount].m_iRate, ItemBagChild->getChildByName( "ItemDropRate" ) );
        //						nAddItemCount++;
        //					}
        //				}
        //			}
        //		}
        //	}
    }
    m_vecMonster.push_back( cm_MonsterStruct );
    MonsterGroupChild = NULL;
    MonsterDataCorrectChild = NULL;
    AITriggerCount = NULL;
    AITriggerChild = NULL;
    ItemBagChild = NULL;
}