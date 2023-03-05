#ifndef _SEVENDAYSCONFIG_
#define _SEVENDAYSCONFIG_

#include "MeRTLibs.h"
#include "RapidXml/MeRapidXml.h"

class SevenDaysConfig
{
public:
	enum TaskDay
	{
		TD_FirstDay,
		TD_SecondDay,
		TD_ThirdDay,
		TD_FourthDay,
		TD_FifthDay,
		TD_SixthDay,
		TD_SeventhDay,

		TD_Max,

		TD_ItemMax = 4,
	};

	typedef std::vector< int > TaskIDVec;
	typedef std::vector< int > TaskVarVecID;

	struct ItemData
	{
		ItemData()
		{
			nItemID = 0;
			nItemCount = 0;
		}
		int nItemID;
		int nItemCount;
	};

	struct DataCommon
	{
		DataCommon()
		{
			nTaskID = -1;
			nTaskVarID = -1;
			nVarNum = 0;
			nGiftID = 0;
			nMoney = 0;
			nMoneyType = 20;
		}

		int nTaskID;
		int nTaskVarID;
		int nVarNum;
		std::string strName;
		std::string strName1;
		std::string strCondition;
		std::string strTips;
		std::string strGift;
		int nGiftID;
		ItemData itemdata[TD_ItemMax];
		int nMoney;
		int nMoneyType;
	};

	typedef std::vector< DataCommon > DataCommonVec;

	struct TaskCountry
	{
		TaskCountry()
		{
			nTargetTaskID = -1;
			nTargetTaskCountry = 0;
		}

		int nTargetTaskID;
		int nTargetTaskCountry;
	};

	struct FirstDay
	{
		DataCommon datacommon;
	};

	struct SecondDay
	{
		SecondDay()
		{
			nNeedLevel = 0;
		}

		DataCommon datacommon;
		TaskCountry targetTask[3];
		int nNeedLevel;
	};

	struct ThirdDay
	{
		DataCommon datacommon;
	};

	struct FourthDay
	{
		DataCommon datacommon;
	};

	struct FifthDay
	{
		DataCommon datacommon;
	};

	struct SixthDay
	{
		DataCommon datacommon;
	};

	struct SeventhDay
	{
		SeventhDay()
		{
			nStarLevel = 0;
		}

		DataCommon datacommon;
		int nStarLevel;
	};

	SevenDaysConfig();
	virtual ~SevenDaysConfig();

	__time64_t GetStartTime() { return startTime; }
	__time64_t GetEndTime() { return endTime; }
	FirstDay GetFirstDay() { return firstDay; }
	SecondDay GetSecondDay() { return secondDay; }
	ThirdDay GetThirdDay() { return thirdDay; }
	FourthDay GetFourthDay() { return fourthDay; }
	FifthDay GetFifthDay() { return fifthDay; }
	SixthDay GetSixthDay() { return sixthDay; }
	SeventhDay GetSeventhDay() { return seventhDay; }

	bool LoadSevenDaysConfig(const char* pszConfig);
	bool LoadCommon(DataCommon& data, MeXmlElement* pDay);

	static SevenDaysConfig& Instance()
	{
		static SevenDaysConfig s_xSevenDays;
		return s_xSevenDays;
	}

	TaskIDVec GetTaskIDVec() { return vecTaskID; }
	TaskVarVecID GetTaskVarIDVec() { return vecTaskVarID; }
	DataCommonVec GetDataCommonVec() { return vecDataCommon; }

private:
	void SetDataCommon(DataCommon data, DataCommon& tdata);

	void SetStartTime(__time64_t time) { startTime = time; }
	void SetEndTime(__time64_t time) { endTime = time; }
	void SetFirstDay(FirstDay data);
	void SetSecondDay(SecondDay data);
	void SetThirdDay(ThirdDay data);
	void SetFourthDay(FourthDay data);
	void SetFifthDay(FifthDay data);
	void SetSixthDay(SixthDay data);
	void SetSeventhDay(SeventhDay data);

	void AddTaskID(int index, int id);
	void AddTaskVarID(int index, int id);
	void AddDataCommon(int index, DataCommon data);

private:
	__time64_t startTime;
	__time64_t endTime;
	FirstDay firstDay;
	SecondDay secondDay;
	ThirdDay thirdDay;
	FourthDay fourthDay;
	FifthDay fifthDay;
	SixthDay sixthDay;
	SeventhDay seventhDay;

	TaskIDVec vecTaskID;
	TaskVarVecID vecTaskVarID;
	DataCommonVec vecDataCommon;
};

#define theSevenDaysConfig SevenDaysConfig::Instance()
#endif //_SEVENDAYSCONFIG_