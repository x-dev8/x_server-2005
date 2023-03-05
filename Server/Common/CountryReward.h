#ifndef __COUNTRYREWARD_H__
#define __COUNTRYREWARD_H__
/*
 *	Author 2012-12-12 zhuxincong
 *	DESC: ���ҽ���
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
		unsigned int nLevel;            // �ȼ�
		unsigned int nMountID;		 // ����ID	
		unsigned int nItemID; //��ƷID
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
		unsigned int nSubLevel;            // �ȼ�
		unsigned int nSubMountID;		 // ����ID	
		unsigned int nSubItemID; //��ƷID
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
	bool SendCountryReward(const char* charPlayerName,int nPlayID,int nLevel,int nPosition);//�����ʼ�,�����Ͷ�����ȥ������
    CReward* GetMountByLevel( unsigned int nLevel ,int nPosition) ;
	CSubReward* GetItemByLevel(unsigned int nLevel,int nPosition);
	int GetItemID(int nLevel,int nPosition);
	int GetSubItemID(int nLevel,int nPosition);
	int GetSubMountID(int nLevel,int nPosition);
	//ɾ����Ʒ�ĺ�����û��д
	bool BSubItemAndMount(int nPosition,int nPlayID);

private:
	int nSubCount; //��Ϊ�ʼ�һ��ֻ�ܷ���һ��
	int nAddCount; //��ȷ���м�����ƷҪ��������þ���Ҫ���Ͷ��ٴ�
	mapAddReward _mapAddReward;
	mapSubReward _mapSubReward;
};
#define theCountryReward CountryReward::Instance()
#endif