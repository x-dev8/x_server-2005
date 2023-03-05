#pragma once
#include "GlobalDef.h"
#include "Singleton.h"

enum eKeyAllPart
{
	eKeyAll_Hair, //0
	eKeyAll_Face,//1
	eKeyAll_Helmet,//2
	eKeyAll_Armour, //3
	eKeyAll_Glove, //4
	eKeyAll_Shoe, //5
	eKeyAll_RHandItem,//6
	eKeyAll_LHandItem,//7
	eKeyAll_WeaponMinor,//8
	eKeyAll_Badge, //9
	eKeyAll_Ring1, 
	eKeyAll_Ring2, 
	eKeyAll_Bangle1, 
	eKeyAll_Bangle2, 
	eKeyAll_Shoulder, 
	eKeyAll_Necklace, 
	eKeyAll_Sash,
	eKeyAll_LeaderCard, 
	eKeyAll_Amulet, 
	eKeyAll_AecorativeGoods, 
	eKeyAll_AecorativeClothing,
	eKeyAll_Trousers,

	eKeyAll_Max
};

class CEquipPartMap: public Singleton<CEquipPartMap>
{
public:
	CEquipPartMap();
	void Init();

	int GetLogicPart(int nPart);
private:
	int m_sLogicMap[EEquipPartType_MaxEquitPart];
};

