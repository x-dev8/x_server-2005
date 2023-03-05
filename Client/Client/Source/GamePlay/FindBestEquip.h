#ifndef FINDBESTEQUIP_H
#define FINDBESTEQUIP_H

#include <map>
#include <string>
#include "RapidXml/MeRapidXml.h"
#include "GlobalDef.h"
#include "GameDefineChar.h"
#include "Singleton.h"



enum LevelAreaType
{
	AREA_INVALID = -1,

	AREA_0,
	AREA_1,
	AREA_2,
	AREA_3,
	AREA_4,

	AREA_MAX = 50
};

enum
{
	MAX_INFOCOUNT	= 3,		// ���װ��˵����Ϣ��
	MAX_LEVELAREA	= 5,		// ���ȼ�������
	MAX_CAREERCOUNT = 5			// ���ְҵ��
};

struct EquipInfo
{
	std::string mAllInfo[MAX_INFOCOUNT];
};


class FindBestEquip : public Singleton<FindBestEquip>
{
public:

	~FindBestEquip(){}

	bool			LoadXml();

	int				FindEquipInfo( EArmType CareerId, EEquipPartType PartId, int level, EquipInfo& Data ) const;

private:

	friend class Singleton<FindBestEquip>;
	FindBestEquip();

	int				FindLevelAreaType( int level ) const;

private:

	struct LevelArea
	{
		int mMinLevel;
		int mMaxLevel;
	};

	struct BestEquip
	{
		int mCareer;
		int mPart;
	};

	typedef std::multimap<int, BestEquip> BestEquipSet_t;			// �п����Ƕ�װ������ְͬҵ��ͬһ����
	typedef BestEquipSet_t::const_iterator BestEquipIt_t;

	typedef std::map<int, EquipInfo> EquipInfoSet_t;
	typedef EquipInfoSet_t::const_iterator EquipInfoIt_t;

	typedef std::vector<LevelArea> LevelAreaSet_t;
	typedef std::vector<BestEquipSet_t> AllBestEquipSet_t;

	LevelAreaSet_t			mLevelArea;				// �ȼ������
	AllBestEquipSet_t		mBestEquipSet;			// �ȼ������Ӧ��װ����
	EquipInfoSet_t			mEquipInfoSet;			// װ��ID��Ӧ��װ��˵����

};

#endif