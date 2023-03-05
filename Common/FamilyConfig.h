#ifndef __FAMILY_CONFIG_H__
#define __FAMILY_CONFIG_H__

#include <vector>

#define theFamilyConfig FamilyConfig::Instance()

class FamilyConfig
{
public:
	// 创建家族设定
	class CreateSetting
	{
	public:
		CreateSetting()	{ nLevel = 0; nCostMoney = 0;}

		unsigned int	GetLevel() const	{ return nLevel; }
		void	SetLevel( unsigned int nValue )	{ nLevel = nValue;}

		unsigned int	GetCostMoney() const	{ return nCostMoney; }
		void	SetCostMoney( unsigned int nValue )	{ nCostMoney = nValue; }

	private:
		unsigned int nLevel;
		unsigned int nCostMoney;
	};

	// 加入家族设定
	class JoinSetting
	{
	public:
		unsigned int GetLevelLimit() const { return nLevelLimit; }
		void SetLevelLimit( unsigned int nValue ) { nLevelLimit = nValue; }

	private:
		unsigned int nLevelLimit;
	};

	class ProsperitySetting
	{
	public:
		unsigned int GetProsPerDay() const { return nProsperityPerDay; }
		void SetProsPerDay( unsigned int nProsPerDay ) { nProsperityPerDay = nProsPerDay; }

		unsigned int GetProsPerWeek() const { return nProsperityPerWeek; }
		void SetProsPerWeek( unsigned int nProsPerWeek ) { nProsperityPerWeek = nProsPerWeek; }

	private:
		unsigned int nProsperityPerDay;		// 每天第一次上线增加的繁荣度
		unsigned int nProsperityPerWeek;	// 每周扣除的繁荣度
	};

	// 家族属性设定
	class AttrSetting
	{
	public:
		unsigned char GetFamilyLevel() const { return nFamilyLevel; }
		void SetFamilyLevel( unsigned char nValue ) { nFamilyLevel = nValue; }

		unsigned int GetProsperityNeed() const { return nProsperity; }
		void SetProsperityNeed( unsigned int nValue ) { nProsperity = nValue; }

		unsigned int GetCostMoney() const { return nCostMoney; }
		void SetCostMoney( unsigned int nValue ) { nCostMoney = nValue; }

		unsigned char GetMemberCountLimit() const { return nMemberCountLimit; }
		void SetMemberCountLimit( unsigned char nValue ) { nMemberCountLimit = nValue; }

	private:
		unsigned char nFamilyLevel;
		unsigned int nProsperity;
		unsigned int nCostMoney;
		unsigned char nMemberCountLimit;
	};

	// 解散设定
	class DisbandSetting
	{
	public:
		unsigned int GetFamilyKeepTime() const { return nKeepTime; }
		void SetFamilyKeepTime( unsigned int nValue ) { nKeepTime = nValue; }

	private:
		unsigned int nKeepTime;
	};

	class MemberLeaveSetting
	{
	public:
		unsigned int GetLeaveSettingTime() const { return nLeaveSettingTime; }
		void SetLeaveSettingTime( unsigned int nValue ) { nLeaveSettingTime = nValue; }

	private:
		unsigned int nLeaveSettingTime;

	};

	class ChangeAimSetting
	{
	public:
		__int64 GetChangeAimCD() const	{ return nChangeAimCD; }
		unsigned int GetChangeAimCost() const	{ return nChangeAimCost; }

		void SetChangeAimCD( __int64 nCD )	{ nChangeAimCD = nCD; }
		void SetChangeAimCost( unsigned int nCost )	{ nChangeAimCost = nCost; }

	private:
		__int64 nChangeAimCD;
		unsigned int nChangeAimCost;

	};

	//家族字符输入长度限制
	class FamilyWordsLenLimits
	{
	public:
		//FamilyWordsLenLimits()
		//{
		//	nNameLenMax = 16;
		//	nNameLenMin = 6;
		//	nAimLenMax = 400;
		//	nAimLenMin = 0;
		//	nRequestMsgLenMax = 160;
		//	nRequestMsgLenMin = 0;
		//	nNoteLenMax = 160;
		//	nNoteLenMin = 0;
		//}
	public:
		unsigned int GetNameLenMax()const{return nNameLenMax;}
		unsigned int GetNameLenMin()const{return nNameLenMin;}
		unsigned int GetAimLenMax()const{return nAimLenMax;}
		unsigned int GetAimLenMin()const{return nAimLenMin;}
		unsigned int GetRequestMsgLenMax()const{return nRequestMsgLenMax;}
		unsigned int GetRequestMsgLenMin()const{return nRequestMsgLenMin;}
		unsigned int GetNoteLenMax()const{return nNoteLenMax;}
		unsigned int GetNoteLenMin()const{return nNoteLenMin;}

		void SetNameLenMax(unsigned nVal){nNameLenMax = nVal;}
		void SetNameLenMin(unsigned nVal){nNameLenMin = nVal;}
		void SetAimLenMax(unsigned nVal){nAimLenMax = nVal;}
		void SetAimLenMin(unsigned nVal){nAimLenMin = nVal;}
		void SetRequestMsgLenMax(unsigned nVal){nRequestMsgLenMax = nVal;}
		void SetRequestMsgLenMin(unsigned nVal){nRequestMsgLenMin = nVal;}
		void SetNoteLenMax(unsigned nVal){nNoteLenMax = nVal;}
		void SetNoteLenMin(unsigned nVal){nNoteLenMin = nVal;}
	private:
		unsigned int nNameLenMax;
		unsigned int nNameLenMin;
		unsigned int nAimLenMax;
		unsigned int nAimLenMin;
		unsigned int nRequestMsgLenMax;
		unsigned int nRequestMsgLenMin;
		unsigned int nNoteLenMax;
		unsigned int nNoteLenMin;
	};

public:
	static FamilyConfig& Instance()
	{
		static FamilyConfig instance;
		return instance;
	}

	const CreateSetting& GetCreateSetting() const { return _createSetting; }
	const JoinSetting& GetJoinSetting() const { return _joinSetting; }
	const AttrSetting* GetAttrSettingByLevel( unsigned char nLevel );
	const DisbandSetting& GetDisbandSetting() const { return _disbandSetting; }
	const FamilyWordsLenLimits& GetFamilyWordsLenLimits() const { return _familyWordsLen; }
	const ProsperitySetting& GetProsperitySetting() const { return _prosperitySetting; }
	const MemberLeaveSetting& GetMemberLeaveSetting() const { return _memberLeaveSetting; }
	const ChangeAimSetting& GetChangeAimSetting() const { return _changeAimSetting; }

	bool LoadConfig( const char* szFile );

protected:
	FamilyConfig() {}

	typedef std::vector< AttrSetting >		AttrSettingContainer;
	typedef AttrSettingContainer::iterator	AttrSettingContainerItr;

private:
	CreateSetting	_createSetting;
	JoinSetting		_joinSetting;
	AttrSettingContainer	_attrSettings;
	DisbandSetting	_disbandSetting;
	FamilyWordsLenLimits	_familyWordsLen;
	ProsperitySetting		_prosperitySetting;
	MemberLeaveSetting	_memberLeaveSetting;
	ChangeAimSetting	_changeAimSetting;
};

#endif