#include "SevenDays.h"
#include "TimeEx.h"

SevenDaysConfig::SevenDaysConfig()
{
	startTime = 0;
	endTime = 0;
	vecTaskID.resize(TD_Max);
	vecTaskVarID.resize(TD_Max);
	vecDataCommon.resize(TD_Max);
}

SevenDaysConfig::~SevenDaysConfig()
{
	vecTaskID.clear();
	vecTaskVarID.clear();
	vecDataCommon.clear();
}

void SevenDaysConfig::SetDataCommon(DataCommon data, DataCommon& tdata)
{
	tdata.nTaskID = data.nTaskID;
	tdata.nTaskVarID = data.nTaskVarID;
	tdata.nVarNum = data.nVarNum;
	tdata.strName = data.strName;
	tdata.strName1 = data.strName1;
	tdata.strCondition = data.strCondition;

	tdata.strTips = data.strTips;
	tdata.strGift = data.strGift;
	tdata.nGiftID = data.nGiftID;

	for (int i = 0; i < TD_ItemMax; i++)
	{
		tdata.itemdata[i].nItemID = data.itemdata[i].nItemID;
		tdata.itemdata[i].nItemCount = data.itemdata[i].nItemCount;
	}

	tdata.nMoney = data.nMoney;
	tdata.nMoneyType = data.nMoneyType;
}

void SevenDaysConfig::AddTaskID(int index, int id)
{
	if ( index < TD_FirstDay || index > TD_SeventhDay || id < 0 )
		return;
	vecTaskID[index] = id;
}

void SevenDaysConfig::AddTaskVarID(int index, int id)
{
	if ( index < TD_FirstDay || index > TD_SeventhDay || id < 0 )
		return;
	vecTaskVarID[index] = id;
}

void SevenDaysConfig::AddDataCommon(int index, DataCommon data)
{
	if ( index < TD_FirstDay || index > TD_SeventhDay )
		return;
	vecDataCommon[index] = data;
}

void SevenDaysConfig::SetFirstDay(FirstDay data)
{
	SetDataCommon(data.datacommon, firstDay.datacommon);
	AddTaskID( (int)TD_FirstDay, data.datacommon.nTaskID );
	AddTaskVarID( (int)TD_FirstDay, data.datacommon.nTaskVarID );
	AddDataCommon( (int)TD_FirstDay, data.datacommon );
}

void SevenDaysConfig::SetSecondDay(SecondDay data)
{
	SetDataCommon(data.datacommon, secondDay.datacommon);

	for (int i = 0; i < 3; i++)
	{
		secondDay.targetTask[i].nTargetTaskID = data.targetTask[i].nTargetTaskID;
		secondDay.targetTask[i].nTargetTaskCountry = data.targetTask[i].nTargetTaskCountry;
	}

	secondDay.nNeedLevel = data.nNeedLevel;

	AddTaskID( (int)TD_SecondDay, data.datacommon.nTaskID );
	AddTaskVarID( (int)TD_SecondDay, data.datacommon.nTaskVarID );
	AddDataCommon( (int)TD_SecondDay, data.datacommon );
}

void SevenDaysConfig::SetThirdDay(ThirdDay data)
{
	SetDataCommon(data.datacommon, thirdDay.datacommon);
	AddTaskID( (int)TD_ThirdDay, data.datacommon.nTaskID );
	AddTaskVarID( (int)TD_ThirdDay, data.datacommon.nTaskVarID );
	AddDataCommon( (int)TD_ThirdDay, data.datacommon );
}

void SevenDaysConfig::SetFourthDay(FourthDay data)
{
	SetDataCommon(data.datacommon, fourthDay.datacommon);
	AddTaskID( (int)TD_FourthDay, data.datacommon.nTaskID );
	AddTaskVarID( (int)TD_FourthDay, data.datacommon.nTaskVarID );
	AddDataCommon( (int)TD_FourthDay, data.datacommon );
}

void SevenDaysConfig::SetFifthDay(FifthDay data)
{
	SetDataCommon(data.datacommon, fifthDay.datacommon);
	AddTaskID( (int)TD_FifthDay, data.datacommon.nTaskID );
	AddTaskVarID( (int)TD_FifthDay, data.datacommon.nTaskVarID );
	AddDataCommon( (int)TD_FifthDay, data.datacommon );
}

void SevenDaysConfig::SetSixthDay(SixthDay data)
{
	SetDataCommon(data.datacommon, sixthDay.datacommon);
	AddTaskID( (int)TD_SixthDay, data.datacommon.nTaskID );
	AddTaskVarID( (int)TD_SixthDay, data.datacommon.nTaskVarID );
	AddDataCommon( (int)TD_SixthDay, data.datacommon );
}

void SevenDaysConfig::SetSeventhDay(SeventhDay data)
{
	SetDataCommon(data.datacommon, seventhDay.datacommon);
	seventhDay.nStarLevel = data.nStarLevel;

	AddTaskID( (int)TD_SeventhDay, data.datacommon.nTaskID );
	AddTaskVarID( (int)TD_SeventhDay, data.datacommon.nTaskVarID );
	AddDataCommon( (int)TD_SeventhDay, data.datacommon );
}

bool SevenDaysConfig::LoadCommon(DataCommon& data, MeXmlElement* pDay)
{
	if (!pDay)
		return false;

	if ( !pDay->Attribute("TaskID", &data.nTaskID) )
		return false;
	if ( !pDay->Attribute("TaskVarID", &data.nTaskVarID) )
		return false;
	if ( !pDay->Attribute("VarNum", &data.nVarNum) )
		return false;

	data.strName = pDay->Attribute("Name1");
	data.strName1 = pDay->Attribute("Name2");
	data.strCondition = pDay->Attribute("Condition");
	data.strTips = pDay->Attribute("Tips");
	data.strGift = pDay->Attribute("GiftValue");

	pDay->Attribute("GiftItem", &data.nGiftID);

	pDay->Attribute("ItemID1", &data.itemdata[0].nItemID);
	pDay->Attribute("ItemCount1", &data.itemdata[0].nItemCount);
	pDay->Attribute("ItemID2", &data.itemdata[1].nItemID);
	pDay->Attribute("ItemCount2", &data.itemdata[1].nItemCount);
	pDay->Attribute("ItemID3", &data.itemdata[2].nItemID);
	pDay->Attribute("ItemCount3", &data.itemdata[2].nItemCount);
	pDay->Attribute("ItemID4", &data.itemdata[3].nItemID);
	pDay->Attribute("ItemCount4", &data.itemdata[3].nItemCount);

	pDay->Attribute("Money", &data.nMoney);
	pDay->Attribute("MoneyType", &data.nMoneyType);

	return true;
}

bool SevenDaysConfig::LoadSevenDaysConfig(const char* pszConfig)
{
	if (!pszConfig || *pszConfig == 0)
		return false;

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszConfig))
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;

	MeXmlElement* pFirstDay = pRoot->FirstChildElement("FirstDay");
	if (!pFirstDay)
		return false;

	FirstDay firstdata;
	if ( !LoadCommon(firstdata.datacommon, pFirstDay) )
		return false;
	SetFirstDay(firstdata);

	MeXmlElement* pSecondDay = pRoot->FirstChildElement("SecondDay");
	if (!pSecondDay)
		return false;

	SecondDay seconddata;

	if ( !LoadCommon(seconddata.datacommon, pSecondDay) )
		return false;
	pSecondDay->Attribute("NeedLevel", &seconddata.nNeedLevel);

	if ( !pSecondDay->Attribute("TargetTaskID1", &seconddata.targetTask[0].nTargetTaskID) )
		return false;
	if ( !pSecondDay->Attribute("TargetTaskCountry1", &seconddata.targetTask[0].nTargetTaskCountry) )
		return false;
	if ( !pSecondDay->Attribute("TargetTaskID2", &seconddata.targetTask[1].nTargetTaskID) )
		return false;
	if ( !pSecondDay->Attribute("TargetTaskCountry2", &seconddata.targetTask[1].nTargetTaskCountry) )
		return false;
	if ( !pSecondDay->Attribute("TargetTaskID3", &seconddata.targetTask[2].nTargetTaskID) )
		return false;
	if ( !pSecondDay->Attribute("TargetTaskCountry3", &seconddata.targetTask[2].nTargetTaskCountry) )
		return false;

	SetSecondDay(seconddata);

	MeXmlElement* pThirdDay = pRoot->FirstChildElement("ThirdDay");
	if (!pThirdDay)
		return false;

	ThirdDay thirddata;
	if ( !LoadCommon(thirddata.datacommon, pThirdDay) )
		return false;
	SetThirdDay(thirddata);

	MeXmlElement* pFourthDay = pRoot->FirstChildElement("FourthDay");
	if (!pFourthDay)
		return false;

	FourthDay fourthdata;
	if ( !LoadCommon(fourthdata.datacommon, pFourthDay) )
		return false;
	SetFourthDay(fourthdata);

	MeXmlElement* pFifthDay = pRoot->FirstChildElement("FifthDay");
	if (!pFifthDay)
		return false;

	FifthDay fifthdata;
	if ( !LoadCommon(fifthdata.datacommon, pFifthDay) )
		return false;
	SetFifthDay(fifthdata);

	MeXmlElement* pSixthDay = pRoot->FirstChildElement("SixthDay");
	if (!pSixthDay)
		return false;

	SixthDay sixthdata;
	if ( !LoadCommon(sixthdata.datacommon, pSixthDay) )
		return false;
	SetSixthDay(sixthdata);

	MeXmlElement* pSeventhDay = pRoot->FirstChildElement("SeventhDay");
	if (!pSeventhDay)
		return false;

	SeventhDay seventhdata;
	if ( !LoadCommon(seventhdata.datacommon, pSeventhDay) )
		return false;
	pSeventhDay->Attribute("StarLevel", &seventhdata.nStarLevel);

	SetSeventhDay(seventhdata);

	return true;
}