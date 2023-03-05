#pragma once
#include <windows.h>
#include "RapidXml/MeRapidXml.h"

class CEquipmentDoll
{
public:
	enum PartType
	{
		ePart_Helmet,
		ePart_Shoulder,
		ePart_Armour,
		ePart_Sash,
		ePart_Glove,
		ePart_Shoe,
		ePart_Ring, // 戒指1
		ePart_Bangle, // 手镯1
		ePart_Necklace, // 项链
		//ePart_Trousers, // 裤子
		ePart_WeaponMinor,//现在的手套

		ePart_WarriorMain,
		ePart_AssassinMain,
		ePart_MageMain,
		ePart_HunterMain,
		ePart_TaoistMain,

  //      ePart_WarriorMinor,
  //      ePart_AssassinMinor,
  //      ePart_MageMinor,
  //      ePart_HunterMinor,
  //      ePart_TaoistMinor,

		
		ePart_WeaponMain,
		ePart_Max,
	};
	struct Part
	{
		BOOL	bDisable;
		RECT	rcSrc;					// 在原图中的位置
		int		nOffsetX, nOffsetY;		// 渲染的时候,需要偏移一点
		BOOL	bNeedRepair;
		Part():bDisable(FALSE),nOffsetX(0),nOffsetY(0),bNeedRepair(FALSE){}
	};
	
public:
	CEquipmentDoll();
	BOOL	Create();
	void	Destroy();
	void	Render( PartType mainType, PartType minorType );
	BOOL	m_bRender;	//
	Part	m_parts[ePart_Max];

protected:
	void LoadConfig();
	void SetPartUI(CEquipmentDoll::Part& part, MeXmlElement* pRoot, const char* nodeName);

private:
    int		m_nTexture;
    int     m_nX;
    int     m_nY;

};