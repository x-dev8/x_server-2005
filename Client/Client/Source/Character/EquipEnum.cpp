#include "EquipEnum.h"
CEquipPartMap::CEquipPartMap()
{
	memset(m_sLogicMap, 0, sizeof(m_sLogicMap));
	Init();
}

int CEquipPartMap::GetLogicPart(int nPart)
{
	if (nPart < 0 || nPart >= EEquipPartType_MaxEquitPart)
	{
		return 0;
	}
	return m_sLogicMap[nPart];
}

void CEquipPartMap::Init()
{
	m_sLogicMap[EEquipPartType_Helmet] = eKeyAll_Helmet;
	m_sLogicMap[EEquipPartType_Armour] = eKeyAll_Armour;
	m_sLogicMap[EEquipPartType_Glove] = eKeyAll_Glove;
	m_sLogicMap[EEquipPartType_Shoe] = eKeyAll_Shoe;
	m_sLogicMap[EEquipPartType_Weapon] = eKeyAll_RHandItem;
	m_sLogicMap[EEquipPartType_WeaponMinor] = eKeyAll_WeaponMinor;
	m_sLogicMap[EEquipPartType_Badge] = eKeyAll_Badge;
	m_sLogicMap[EEquipPartType_Ring1] = eKeyAll_Ring1;
	m_sLogicMap[EEquipPartType_Ring2] = eKeyAll_Ring2;
	m_sLogicMap[EEquipPartType_Bangle1] = eKeyAll_Bangle1;
	m_sLogicMap[EEquipPartType_Bangle2] = eKeyAll_Bangle2;
	m_sLogicMap[EEquipPartType_Shoulder] = eKeyAll_Shoulder;
	m_sLogicMap[EEquipPartType_Necklace] = eKeyAll_Necklace;
	m_sLogicMap[EEquipPartType_Sash] = eKeyAll_Sash;
	m_sLogicMap[EEquipPartType_LeaderCard] = eKeyAll_LeaderCard;
	m_sLogicMap[EEquipPartType_Amulet] = eKeyAll_Amulet;
	m_sLogicMap[EEquipPartType_AecorativeGoods] = eKeyAll_AecorativeGoods;
	m_sLogicMap[EEquipPartType_AecorativeClothing] = eKeyAll_AecorativeClothing;
	m_sLogicMap[EEquipPartType_Trousers] = eKeyAll_Trousers;
}