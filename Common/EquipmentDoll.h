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
		ePart_Ring, // ��ָ1
		ePart_Bangle, // ����1
		ePart_Necklace, // ����
		//ePart_Trousers, // ����
		ePart_WeaponMinor,//���ڵ�����

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
		RECT	rcSrc;					// ��ԭͼ�е�λ��
		int		nOffsetX, nOffsetY;		// ��Ⱦ��ʱ��,��Ҫƫ��һ��
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