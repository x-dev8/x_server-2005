#ifndef __COUNTRYREWARD_H__
#define __COUNTRYREWARD_H__
/*
 *	Author 2012-12-12 zhuxincong
 *	DESC: 国家奖励
 */
#include <vector>
#include <map>
using namespace std;

class CountryReward
{	
public:
	CountryReward(void);
	~CountryReward(void);

	class CReward
	{
	public:
		unsigned int GetLevel() const { return nLevel; }
		unsigned int GetMountID() const { return nMountID; }
		unsigned int GetItemID() const { return nItemID; }
		
		void SetLevel( unsigned int nValue ) { nLevel = nValue; }
		void SetMountID( unsigned int nValue ) { nMountID = nValue; }
		void SetItemID( unsigned int nValue ) { nItemID = nValue; }
	private:
		unsigned int nLevel;            // 等级
		unsigned int nMountID;		 // 坐骑ID	
		unsigned int nItemID; //物品ID
	};
	typedef vector< CReward > CRewardSettingVector;

	struct CAddReward
	{
		CAddReward()
		{
			nPositionID = 0;
		}
		int nPositionID;
		CRewardSettingVector vecCRewardSetting;
	};
	typedef map<int,CAddReward*> mapAddReward;


	class CSubReward
	{
	public:
		unsigned int GetLevel() const { return nSubLevel; }
		unsigned int GetMountID() const { return nSubMountID; }
		unsigned int GetItemID() const { return nSubItemID; }

		void SetLevel( unsigned int nValue ) { nSubLevel = nValue; }
		void SetMountID( unsigned int nValue ) { nSubMountID = nValue; }
		void SetItemID( unsigned int nValue ) { nSubItemID = nValue; }
	private:
		unsigned int nSubLevel;            // 等级
		unsigned int nSubMountID;		 // 坐骑ID	
		unsigned int nSubItemID; //物品ID
	};
	typedef vector< CSubReward > vecCSubReward;
	struct CSub
	{
		CSub()
		{
			nPosition = 0;
		}
		int nPosition;
		vecCSubReward _vecCSubReward;
	};
	typedef map<int,CSub*> mapSubReward;

public:

	static CountryReward& Instance()
	{
		static CountryReward s_xConfig;
		return s_xConfig;
	}


	bool LoadCountryConfig( const char* szFile );
	bool SendCountryReward(const char* charPlayerName,int nPlayID,int nLevel,int nPosition);//发送邮件,就是送东西过去给国王
    CReward* GetMountByLevel( unsigned int nLevel ,int nPosition) ;
	CSubReward* GetItemByLevel(unsigned int nLevel,int nPosition);
	int GetItemID(int nLevel,int nPosition);
	int GetSubItemID(int nLevel,int nPosition);
	int GetSubMountID(int nLevel,int nPosition);
	//删除物品的函数还没有写
	bool BSubItemAndMount(int nPosition,int nPlayID);

private:
	int nSubCount; //因为邮件一次只能发送一次
	int nAddCount; //是确认有几个物品要发生，最好就是要发送多少次
	mapAddReward _mapAddReward;
	mapSubReward _mapSubReward;
};
#define theCountryReward CountryReward::Instance()
#endif