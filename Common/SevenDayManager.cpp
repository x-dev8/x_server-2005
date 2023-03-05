#include "SevenDayManager.h"
#include "SevenDays.h"
#include "GamePlayer.h"
#include "TimeEx.h"
#include "GameServer.h"
#include "GuildDefine.h"
#include "GlobalDef.h"
#include "CountryDefine.h"

#define ONE_DAY (1 * 60 * 60 * 24)
#define TWO_DAYS (2 * 60 * 60 * 24)
#define THREE_DAYS (3 * 60 * 60 * 24)
#define FOUR_DAYS (4 * 60 * 60 * 24)
#define FIVE_DAYS (5 * 60 * 60 * 24)
#define SIX_DAYS (6 * 60 * 60 * 24)
#define SEVEN_DAYS (7 * 60 * 60 * 24)

SevenDayManager::SevenDayManager()
{
	pOwner = 0;
}

SevenDayManager::~SevenDayManager()
{
	
}

bool SevenDayManager::IsInTask(int taskID)
{
	if ( !pOwner || taskID < 0 )
		return false;

	return pOwner->gCharInfoServer.otherdata.vars.szVars[taskID] == (short)TS_UnderWay;
}

bool SevenDayManager::IsCanGainTask(int index)
{
	if ( index < SevenDaysConfig::TD_FirstDay || index > SevenDaysConfig::TD_SeventhDay )
		return false;
	if ( !pOwner)
		return false;

	__time64_t nowTime = 0;
	_time64(&nowTime);
	//__time64_t startTime = theSevenDaysConfig.GetStartTime();
	__time64_t startTime = pOwner->gCharInfoServer.otherdata.sevenDayStartTime;

	/*if ( nowTime < startTime || ( nowTime - startTime > SEVEN_DAYS ) )
		return false;*/
	int nday = GetDayTime( startTime, nowTime );
	if ( nday == -1 /*|| nday > 7*/ )
		return false;

	SevenDaysConfig::TaskIDVec taskVec = theSevenDaysConfig.GetTaskIDVec();

	if ( index == SevenDaysConfig::TD_FirstDay )
	{
		if ( pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index]] == (short)TS_CanGain )
			return true;
	}
	else
	{
		//if ( nowTime - startTime < index * ONE_DAY ) //时间还没到不能领
		//	return false;
		if ( nday < index )
			return false;
		if ( pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index]] != (short)TS_CanGain )
			return false;
		if ( pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index - 1]] == (short)TS_DoneGet ) //前一个任务要领取了奖励
			return true;
	}

	return false;
}

void SevenDayManager::SetTaskState(int index, short state)
{
	if ( index < SevenDaysConfig::TD_FirstDay || index > SevenDaysConfig::TD_SeventhDay )
		return;
	if ( !pOwner)
		return;

	SevenDaysConfig::TaskIDVec taskVec = theSevenDaysConfig.GetTaskIDVec();

	pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index]] = state;

	MsgFreshSevenDayState msg;
	msg.stateIndex = index;
	msg.state = state;
	GettheServer().SendMsgToSingle( &msg, pOwner );
}

short SevenDayManager::GetTaskState(int index)
{
	if ( index < SevenDaysConfig::TD_FirstDay || index > SevenDaysConfig::TD_SeventhDay )
		return -1;
	if ( !pOwner)
		return -1;

	SevenDaysConfig::TaskIDVec taskVec = theSevenDaysConfig.GetTaskIDVec();

	if ( index == (int)SevenDaysConfig::TD_FirstDay ) //第一个默认可接取
	{
		if (pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index]] == (short)TS_UnStart)
			pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index]] = (short)TS_CanGain;
	}
	else
	{
		__time64_t nowTime = 0;
		_time64(&nowTime);
		__time64_t startTime = pOwner->gCharInfoServer.otherdata.sevenDayStartTime;

		int nday = GetDayTime( startTime, nowTime );

		if ( /*nowTime - startTime >= index * ONE_DAY*/ nday >= index /*&& nday <= 7*/ ) //时间到前个任务已经领奖，如果没开启，设置可接取
		{
			if ( pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index - 1]] == (short)TS_DoneGet )
			{
				if (pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index]] == (short)TS_UnStart)
					//pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index]] = (short)TS_CanGain;
					SetTaskState( index, (short)TS_CanGain );
			}
		}
	}

	return pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index]];
}

bool SevenDayManager::GainTask(int index)
{
	if ( !IsCanGainTask( index ) )
		return false;

	SetTaskState(index, (short)TS_UnderWay);

	if ( index != SevenDaysConfig::TD_SecondDay && index != SevenDaysConfig::TD_ThirdDay )
		TriggerSevenDaysVar(index);

	return true;
}

short SevenDayManager::GetTaskVar(int index)
{
	if ( index < SevenDaysConfig::TD_FirstDay || index > SevenDaysConfig::TD_SeventhDay )
		return -1;
	if ( !pOwner)
		return -1;

	SevenDaysConfig::TaskVarVecID taskVarID = theSevenDaysConfig.GetTaskVarIDVec();

	return pOwner->gCharInfoServer.otherdata.vars.szVars[taskVarID[index]];
}

void SevenDayManager::SetTaskVar(int index, short var)
{
	if ( index < SevenDaysConfig::TD_FirstDay || index > SevenDaysConfig::TD_SeventhDay )
		return;
	if ( !pOwner)
		return;

	SevenDaysConfig::TaskVarVecID taskVarID = theSevenDaysConfig.GetTaskVarIDVec();

	pOwner->gCharInfoServer.otherdata.vars.szVars[taskVarID[index]] = var;

	MsgFreshSevenDayState msg;
	msg.varIndex = index;
	msg.var = var;
	GettheServer().SendMsgToSingle( &msg, pOwner );
}

bool SevenDayManager::GainReward(int index)
{
	if ( index < SevenDaysConfig::TD_FirstDay || index > SevenDaysConfig::TD_SeventhDay )
		return false;
	if ( !pOwner)
		return false;

	__time64_t nowTime = 0;
	_time64(&nowTime);
	__time64_t startTime = pOwner->gCharInfoServer.otherdata.sevenDayStartTime;

	/*if ( nowTime < startTime || ( nowTime - startTime > SEVEN_DAYS ) )
		return false;*/
	int nday = GetDayTime( startTime, nowTime );
	if ( nday == -1 /*|| nday > 7*/ )
		return false;

	SevenDaysConfig::TaskIDVec taskVec = theSevenDaysConfig.GetTaskIDVec();

	if ( pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index]] == (short)TS_DoneUnGet )
	{
		SetTaskState(index, (short)TS_DoneGet);

		if ( index < SevenDaysConfig::TD_SeventhDay ) //时间到可以接下个任务，下个任务设置可接
		{
			if ( /*nowTime - startTime >= (index + 1) * ONE_DAY*/ nday >= ( index + 1 ) )
			{
				if (pOwner->gCharInfoServer.otherdata.vars.szVars[taskVec[index + 1]] == (short)TS_UnStart)
					SetTaskState(index + 1, (short)TS_CanGain);
			}
		}

		return true;
	}

	return false;
}

void SevenDayManager::TriggerSevenDaysVar(int index, int nvalue)
{
	if ( index < SevenDaysConfig::TD_FirstDay || index > SevenDaysConfig::TD_SeventhDay )
		return;
	if ( !pOwner)
		return;

	__time64_t nowTime = 0;
	_time64(&nowTime);
	__time64_t startTime = pOwner->gCharInfoServer.otherdata.sevenDayStartTime;

	/*if ( nowTime < startTime || ( nowTime - startTime > SEVEN_DAYS ) )
		return;*/
	int nday = GetDayTime( startTime, nowTime );
	if ( nday == -1 /*|| nday > 7*/ )
		return;

	SevenDaysConfig::TaskIDVec taskVec = theSevenDaysConfig.GetTaskIDVec();

	if ( !IsInTask( taskVec[index] ) )
		return;

	switch (index)
	{
	case 0:
		TriggerFirstDayVar(index);
		break;
	case 1:
		TriggerSecondDayVar(index, nvalue);
		break;
	case 2:
		TriggerThirdDayVar(index, nvalue);
		break;
	case 3:
		TriggerFourthDayVar(index);
		break;
	case 4:
		TriggerFifthDayVar(index);
		break;
	case 5:
		TriggerSixthDayVar(index);
		break;
	case 6:
		TriggerSeventhDayVar(index);
		break;
	default:
		break;
	}
}

void SevenDayManager::TriggerFirstDayVar(int index)
{
	if ( index != SevenDaysConfig::TD_FirstDay )
		return;
	if ( !pOwner)
		return;

	SevenDaysConfig::FirstDay data = theSevenDaysConfig.GetFirstDay();
	short lastVar = GetTaskVar(index);

	if ( lastVar >= data.datacommon.nVarNum )
		return;

	if ( pOwner->GetCountryId() != CountryDefine::Country_Init )
	{
		SetTaskVar(index, data.datacommon.nVarNum);
		SetTaskState(index, (short)TS_DoneUnGet);
	}
}

void SevenDayManager::TriggerSecondDayVar(int index, int questID)
{
	if ( index != SevenDaysConfig::TD_SecondDay )
		return;
	if ( !pOwner )
		return;

	SevenDaysConfig::SecondDay data = theSevenDaysConfig.GetSecondDay();

	if ( pOwner->GetLevel() < data.nNeedLevel )
		return;

	int countryID = pOwner->GetCountryId();
	int nquest = 0;

	for (int i = 0; i < 3; i++)
	{
		if ( data.targetTask[i].nTargetTaskCountry == countryID)
		{
			nquest = data.targetTask[i].nTargetTaskID;
			break;
		}
	}

	if ( nquest != questID )
		return;

	short lastVar = GetTaskVar(index);

	if ( lastVar >= data.datacommon.nVarNum )
		return;

	SetTaskVar(index, lastVar + 1);
	if ( lastVar + 1 >= data.datacommon.nVarNum )
		SetTaskState(index, (short)TS_DoneUnGet);
}

void SevenDayManager::TriggerThirdDayVar(int index, int nvar)
{
	if ( index != SevenDaysConfig::TD_ThirdDay )
		return;
	if ( !pOwner )
		return;

	SevenDaysConfig::ThirdDay data = theSevenDaysConfig.GetThirdDay();

	short lastVar = GetTaskVar(index);
	if ( lastVar >= data.datacommon.nVarNum )
		return;

	if ( lastVar + nvar >= data.datacommon.nVarNum )
	{
		SetTaskVar(index, data.datacommon.nVarNum);
		SetTaskState(index, (short)TS_DoneUnGet);
	}
	else
		SetTaskVar(index, lastVar + nvar);
}

void SevenDayManager::TriggerFourthDayVar(int index)
{
	if ( index != SevenDaysConfig::TD_FourthDay )
		return;
	if ( !pOwner )
		return;

	SevenDaysConfig::FourthDay data = theSevenDaysConfig.GetFourthDay();
	short lastVar = GetTaskVar(index);

	if ( lastVar >= data.datacommon.nVarNum )
		return;

	int cardNum = 0;

	for (int i = 0; i < More_nCardMax; i++)
	{
		if ( pOwner->GetCharInfo().otherdata.cards.shCardLevel[i] > -1 )
			cardNum++;
	}

	if ( cardNum >= data.datacommon.nVarNum )
	{
		SetTaskVar(index, data.datacommon.nVarNum);
		SetTaskState(index, (short)TS_DoneUnGet);
	}
	else
		SetTaskVar(index, cardNum);
}

void SevenDayManager::TriggerFifthDayVar(int index)
{
	if ( index != SevenDaysConfig::TD_FifthDay )
		return;
	if ( !pOwner )
		return;

	SevenDaysConfig::FifthDay data = theSevenDaysConfig.GetFifthDay();
	short lastVar = GetTaskVar(index);

	if ( lastVar >= data.datacommon.nVarNum )
		return;

	short maxlevel = 0;
	for (int i = 0; i < pOwner->_mountManager.GetMountCount(); i++)
	{
		SMountItem* pMount = pOwner->_mountManager.GetMountByIndex(i);
		if ( !pMount )
			continue;

		if ( pMount->baseInfo.level > maxlevel )
			maxlevel = pMount->baseInfo.level;
	}

	if ( maxlevel >= data.datacommon.nVarNum )
	{
		SetTaskVar(index, data.datacommon.nVarNum);
		SetTaskState(index, (short)TS_DoneUnGet);
	}
	else
		SetTaskVar(index, maxlevel);
}

void SevenDayManager::TriggerSixthDayVar(int index)
{
	if ( index != SevenDaysConfig::TD_SixthDay )
		return;
	if ( !pOwner )
		return;

	SevenDaysConfig::SixthDay data = theSevenDaysConfig.GetSixthDay();
	short lastVar = GetTaskVar(index);

	if ( lastVar >= data.datacommon.nVarNum )
		return;

	short maxGem = 0;
	for( int i = 0; i < EEquipPartType_MaxEquitPart; i++ )
	{
		SCharItem* pSCharItem = pOwner->GetVisualEquipItem(i);
		if ( !pSCharItem )
			continue;

		bool hasGem = false;
		for (int j = 0; j < SCharItem::EConstDefine_GemHoleMaxCount; j++)
		{
			if ( pSCharItem->equipdata.gemIds[j] != InvalidLogicNumber )
			{
				hasGem = true;
				break;
			}
		}

		if ( hasGem )
			maxGem++;
	}

	if ( maxGem >= data.datacommon.nVarNum )
	{
		SetTaskVar(index, data.datacommon.nVarNum);
		SetTaskState(index, (short)TS_DoneUnGet);
	}
	else
		SetTaskVar(index, maxGem);
}

void SevenDayManager::TriggerSeventhDayVar(int index)
{
	if ( index != SevenDaysConfig::TD_SeventhDay )
		return;
	if ( !pOwner )
		return;

	SevenDaysConfig::SeventhDay data = theSevenDaysConfig.GetSeventhDay();
	short lastVar = GetTaskVar(index);

	if ( lastVar >= data.datacommon.nVarNum )
		return;

	short equipCount = 0;
	for( int i = 0; i < EEquipPartType_MaxEquitPart; i++ )
	{
		SCharItem* pSCharItem = pOwner->GetVisualEquipItem(i);
		if ( !pSCharItem )
			continue;

		if ( pSCharItem->equipdata.ucLevel >= data.nStarLevel )
			equipCount++;
	}

	if ( equipCount >= data.datacommon.nVarNum )
	{
		SetTaskVar(index, data.datacommon.nVarNum);
		SetTaskState(index, (short)TS_DoneUnGet);
	}
	else
		SetTaskVar(index, equipCount);
}

int SevenDayManager::GetDayTime( __time64_t startTime, __time64_t nowTime )
{
	if ( nowTime < startTime )
		return -1;

	TimeEx startTimeEx( startTime );
	TimeEx nowTimeEx( nowTime );

	TimeSpan span = TimeSpan( nowTime - startTime );
	__int64 ndays = span.GetDays();

	int startHour = startTimeEx.GetHour();
	int startMinute = startTimeEx.GetMinute();
	int startSecond = startTimeEx.GetSecond();

	int nowHour = nowTimeEx.GetHour();
	int nowMinute = nowTimeEx.GetMinute();
	int nowSecond = nowTimeEx.GetSecond();

	//如果现在的小时，分，秒比开始的小时，分，秒小，说明过了一天
	if ( ( nowHour*3600 + nowMinute*60 + nowSecond ) - ( startHour*3600 + startMinute*60 + startSecond) < 0 )
		ndays++;

	return ndays;
}