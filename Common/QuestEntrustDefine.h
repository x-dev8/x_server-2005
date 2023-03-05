#pragma once
#include "GlobalDef.h"
enum QuestEntrustDefine
{
	//MaxReceiveTime = 4*60*60*1000,
	QuestEntrustUpdateTime = 60*1000,
	QuestEntrustLoadTime = 60*1000,
	QuestEntrustSaveTime = 600*1000,

	MaxPlayerNameLength = 32,
	MaxQuestEntrustSum = 5,

	QuestEntrust_YinBi = 1,
	QuestEntrust_YuanBao =2,

	QuestEntrustMaxLength = 20,

	//CanelQuestBuff  = 1,
	//CanelQuestLevel = 1,
};
struct QuestEntrustStates //每天12点清空当前委托
{
	QuestEntrustStates()
	{
		ID = 0;
		SrcPlayerID = 0;
		strcpy_s(ScrPlayerName,MaxPlayerNameLength,"");		
		DestPlayerID = 0;
		strcpy_s(DestPlayerName,MaxPlayerNameLength,"");
		SrcQuestID = 0;
		DestQuestID = 0;
		EntrustRewardType = 0;
		EntrustRewardSum = 0;
		ReceiveLogTime = 0;
		IsSecc = false;
	}
	unsigned int ID;
	unsigned int SrcPlayerID;
	char ScrPlayerName[MaxPlayerNameLength];
	unsigned int DestPlayerID;
	char DestPlayerName[MaxPlayerNameLength];
	unsigned int SrcQuestID;
	unsigned int DestQuestID;
	unsigned int EntrustRewardType;
	unsigned int EntrustRewardSum;
	__int64  ReceiveLogTime;//当前玩家截取的时间记录
	bool IsSecc;//是否已经完成了 
	SCharItem ItemInfo; 
};