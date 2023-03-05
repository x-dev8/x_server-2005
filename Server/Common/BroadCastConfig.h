#ifndef _BROADCASTCONFIG_
#define _BROADCASTCONFIG_

#include "MeRTLibs.h"
#include "RapidXml/MeRapidXml.h"

class BroadCastConfig
{
public:
	enum BroadCastType
	{
		BCT_Type0, //在某段时间内间隔多久发一次
		BCT_Type1, //在某段时间内每天特定时间点发
		BCT_Type2, //某段时间内星期几间隔多久发一次
		BCT_Type3, //某段时间内星期几特定时间发
		BCT_Type4, //怪物存在时间隔多久发一次

		BCT_TypeMax,
	};

	struct TimeYear
	{
		TimeYear()
		{
			nYear = 0;
			nMonth = 0;
			nDay = 0;
			nHour = 0;
			nMinute = 0;
			nSecond = 0;
		}

		int nYear;
		int nMonth;
		int nDay;
		int nHour;
		int nMinute;
		int nSecond;
	};

	struct TimeDay
	{
		TimeDay()
		{
			nHour = 0;
			nMinute = 0;
			nSecond = 0;
		}

		int nHour;
		int nMinute;
		int nSecond;
	};

	struct DataCommon
	{
		DataCommon()
		{
			nType = -1;
		}

		int nType;
		std::string strTip;
	};

	struct TimeStartEnd
	{
		TimeStartEnd()
		{
			nStart = 0;
			nEnd = 0;
		}

		__time64_t nStart;
		__time64_t nEnd;
	};

	struct DataType0
	{
		DataType0()
		{
			nSpaceTime = 0;
			mLastTime = 0;
		}

		DataCommon mCommon;
		TimeYear mStartTime;
		TimeYear mEndTime;
		int nSpaceTime;
		__time64_t mLastTime;
		TimeStartEnd mSETime;
	};

	struct DataType1
	{
		DataCommon mCommon;
		TimeYear mStartTime;
		TimeYear mEndTime;
		TimeDay mTime;
		TimeStartEnd mSETime;
	};

	struct DataType2
	{
		DataType2()
		{
			nWeek = 0;
			nSpaceTime = 0;
			mLastTime = 0;
		}

		DataCommon mCommon;
		TimeYear mStartTime;
		TimeYear mEndTime;
		int nWeek;
		int nSpaceTime;
		__time64_t mLastTime;
		TimeStartEnd mSETime;
	};

	struct DataType3
	{
		DataType3()
		{
			nWeek = 0;
		}

		DataCommon mCommon;
		TimeYear mStartTime;
		TimeYear mEndTime;
		int nWeek;
		TimeDay mTime;
		TimeStartEnd mSETime;
	};

	struct DataType4
	{
		DataType4()
		{
			nMonsterID = -1;
			nSpaceTime = 0;
			mLastTime = 0;
			nMapID = -1;
		}

		DataCommon mCommon;
		int nMonsterID;
		int nMapID;
		int nSpaceTime;
		__time64_t mLastTime;
	};

	typedef std::vector< DataType0 > VecType0;
	typedef VecType0::iterator type0iter;
	typedef std::vector< DataType1 > VecType1;
	typedef VecType1::iterator type1iter;
	typedef std::vector< DataType2 > VecType2;
	typedef VecType2::iterator type2iter;
	typedef std::vector< DataType3 > VecType3;
	typedef VecType3::iterator type3iter;
	typedef std::vector< DataType4 > VecType4;
	typedef VecType4::iterator type4iter;

	BroadCastConfig();
	virtual ~BroadCastConfig();

	VecType0& GetType0() { return m_vecType0; }
	VecType1& GetType1() { return m_vecType1; }
	VecType2& GetType2() { return m_vecType2; }
	VecType3& GetType3() { return m_vecType3; }
	VecType4& GetType4() { return m_vecType4; }

	bool LoadBroadCastConfig( const char* pszConfig );
	void LoadTimeYear( TimeYear& timeStart, TimeYear& timeEnd, TimeStartEnd& timeSE, MeXmlElement* pYear );
	void LoadTimeDay( TimeDay& timeDay, MeXmlElement* pDay );

	static BroadCastConfig& Instance()
	{
		static BroadCastConfig s_xBroadCast;
		return s_xBroadCast;
	}

private:
	VecType0 m_vecType0;
	VecType1 m_vecType1;
	VecType2 m_vecType2;
	VecType3 m_vecType3;
	VecType4 m_vecType4;
};

#define theBroadCastConfig BroadCastConfig::Instance()

#endif //_BROADCASTCONFIG_