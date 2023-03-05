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
struct QuestEntrustStates //ÿ��12����յ�ǰί��
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
	__int64  ReceiveLogTime;//��ǰ��ҽ�ȡ��ʱ���¼
	bool IsSecc;//�Ƿ��Ѿ������ 
	SCharItem ItemInfo; 
};