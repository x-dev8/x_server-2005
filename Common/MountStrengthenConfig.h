#ifndef __MOUNTSTRENGTHENCONFIG_H__
#define __MOUNTSTRENGTHENCONFIG_H__

#include "MeRTLibs.h"
#include "GlobalDef.h"
#include "Singleton.h"

class MountStrengthenData
{
	struct SData
	{
		SData()
		{
			unLossToLevel = 0;
			fProbability = 0.0f;
			unStrength = 0;
			unStamina = 0;
			unAgility = 0;
			unIntelligence = 0;
			nPrice = 0;
		}

		uint16 unLossToLevel; //掉落到几级
		float fProbability;	 //成功概率
		uint16 unStrength;	 //增加的武力
		uint16 unStamina;	 //增加的统御
		uint16 unAgility;	 //增加的身法
		uint16 unIntelligence; //增加的智力
		int nPrice;			 //消耗的钱(铰子)
	};

	typedef std::vector< SData > MountVector;

public:
	MountStrengthenData()
	{
		m_ustMountID = 0;
		m_vecMounts.clear();
		m_vecMounts.resize(SMountItem::MICD_MountMaxLevel);
	}

	unsigned short GetMountID() const { return m_ustMountID; }

	float GetProbability(uint16 unMountLevel) const
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return 0.0f; 

		return m_vecMounts[unMountLevel].fProbability;
	}
	uint16 GetLossToLevel(uint16 unMountLevel) const
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return 0; 

		return m_vecMounts[unMountLevel].unLossToLevel;
	}
	uint16 GetStrength(uint16 unMountLevel) const
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return 0; 

		return m_vecMounts[unMountLevel].unStrength;
	}
	uint16 GetStamina(uint16 unMountLevel) const
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return 0; 

		return m_vecMounts[unMountLevel].unStamina;
	}
	uint16 GetAgility(uint16 unMountLevel) const
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return 0; 

		return m_vecMounts[unMountLevel].unAgility;
	}
	uint16 GetIntelligence(uint16 unMountLevel) const
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return 0; 

		return m_vecMounts[unMountLevel].unIntelligence;
	}
	int GetPrice(uint16 unMountLevel) const
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return 0; 

		return m_vecMounts[unMountLevel].nPrice;
	}

	void SetMountID( unsigned short ustValue ) { m_ustMountID = ustValue; }
	bool AddProbability( uint16 unMountLevel, float fProbability )
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return false; 

		m_vecMounts[unMountLevel].fProbability = fProbability;
		return true;
	}
	bool AddLossToLevel( uint16 unMountLevel, uint16 unLossToLevel )
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return false; 

		m_vecMounts[unMountLevel].unLossToLevel = unLossToLevel;
		return true;
	}
	bool AddStrength( uint16 unMountLevel, uint16 unStrength )
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return false; 

		m_vecMounts[unMountLevel].unStrength = unStrength;
		return true;
	}
	bool AddStamina( uint16 unMountLevel, uint16 unStamina )
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return false; 

		m_vecMounts[unMountLevel].unStamina = unStamina;
		return true;
	}
	bool AddAgility( uint16 unMountLevel, uint16 unAgility )
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return false; 

		m_vecMounts[unMountLevel].unAgility = unAgility;
		return true;
	}
	bool AddIntelligence( uint16 unMountLevel, uint16 unIntelligence )
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return false; 

		m_vecMounts[unMountLevel].unIntelligence = unIntelligence;
		return true;
	}
	bool AddPrice( uint16 unMountLevel, int nPrice )
	{
		if ( unMountLevel >= m_vecMounts.size() )
			return false; 

		m_vecMounts[unMountLevel].nPrice = nPrice;
		return true;
	}

private:
	MountVector m_vecMounts;
	unsigned short m_ustMountID;         // 坐骑ID
};

class MountStrengthenConfig :public ICfgSingletion<MountStrengthenConfig>
{
public:
	typedef std::map< unsigned short, MountStrengthenData > MountStrengthenDataMap;
	typedef MountStrengthenDataMap::iterator MountStrengthenDataMapIter;
	typedef MountStrengthenDataMap::const_iterator MountStrengthenDataMapConstIter;

	MountStrengthenConfig()
	{
		m_mapMountStrengthenData.clear();
	}
	virtual ~MountStrengthenConfig(){}

public:
	virtual bool LoadResourceConfig( const char* pszConfig );

	const MountStrengthenData* GetMountStrengthenData( unsigned short ustItemID ) const;
	bool AddMountStrengthenData( const MountStrengthenData& xData );

	virtual void OnReloadFinished();

private:
	MountStrengthenDataMap m_mapMountStrengthenData;
};

#define theMountStrengthenConfig MountStrengthenConfig::Instance()

#endif //__MOUNTSTRENGTHENCONFIG_H__