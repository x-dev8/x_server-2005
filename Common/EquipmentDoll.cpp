#include "MeRTLibs.h"
#include "equipmentdoll.h"
#include "Me3d/Include.h"
#include "Me3d/Engine/Engine.h"
#include "MeUi/ControlObject.h"
CEquipmentDoll::CEquipmentDoll():
m_nTexture(-1),
m_bRender(FALSE),
m_nX(0),
m_nY(0)
{
	//m_parts[ePart_Helmet].rcSrc.left	= 0*64;
	//m_parts[ePart_Helmet].rcSrc.top		= 0*64;

	//m_parts[ePart_Armoure].rcSrc.left	= 2*64;
	//m_parts[ePart_Armoure].rcSrc.top	= 0*64;

	//m_parts[ePart_Shoulder].rcSrc.left	= 1*64;
	//m_parts[ePart_Shoulder].rcSrc.top	= 0*64;

	//m_parts[ePart_Trousers].rcSrc.left	= 1*64;
	//m_parts[ePart_Trousers].rcSrc.top	= 1*64;

	//m_parts[ePart_Waist].rcSrc.left		= 3*64;
	//m_parts[ePart_Waist].rcSrc.top		= 0*64;

	//m_parts[ePart_Glover].rcSrc.left	= 0*64;
	//m_parts[ePart_Glover].rcSrc.top		= 1*64;

	//m_parts[ePart_Shoe].rcSrc.left		= 2*64;
	//m_parts[ePart_Shoe].rcSrc.top		= 1*64;

	//m_parts[ePart_RightHandItem].rcSrc.left		= 0*64;
	//m_parts[ePart_RightHandItem].rcSrc.top		= 2*64;
	//m_parts[ePart_RightHandItem].nOffsetX		= 4;
	//m_parts[ePart_RightHandItem].nOffsetY		= 10;

	//m_parts[ePart_LeftHandItem].rcSrc.left		= 0*64;
	//m_parts[ePart_LeftHandItem].rcSrc.top		= 2*64;
	//m_parts[ePart_LeftHandItem].nOffsetX		= 44;
	//m_parts[ePart_LeftHandItem].nOffsetY		= 10;

	//m_parts[ePart_Shield].rcSrc.left	= 1*64;
	//m_parts[ePart_Shield].rcSrc.top		= 2*64;
	//m_parts[ePart_Shield].nOffsetX		= 40;
	//m_parts[ePart_Shield].nOffsetY		= 16;

	////m_parts[ePart_Shield].bNeedRepair	= 1;
	////m_parts[ePart_Helmet].bNeedRepair	= 1;
	////m_parts[ePart_Shoulder].bNeedRepair	= 1;
	////m_parts[ePart_Waist].bNeedRepair	= 1;
	////m_parts[ePart_Shoe].bNeedRepair	= 1;
	//for( int nPart = 0; nPart < ePart_Max; nPart++ )
	//{
	//	Part& part = m_parts[nPart];
	//	part.rcSrc.right = part.rcSrc.left+64;
	//	part.rcSrc.bottom = part.rcSrc.top+64;
	//}

}

void CEquipmentDoll::SetPartUI(CEquipmentDoll::Part& part, MeXmlElement* pRoot, const char* nodeName)
{
	MeXmlElement* pElement = pRoot->FirstChildElement(nodeName);
	if (pElement)
	{
		int nValue = 0;
		pElement->Attribute("u", &nValue);
		part.rcSrc.left = nValue;
		pElement->Attribute("v", &nValue);
		part.rcSrc.top = nValue;
		pElement->Attribute("w", &nValue);
		part.rcSrc.right = part.rcSrc.left + nValue;
		pElement->Attribute("h", &nValue);
		part.rcSrc.bottom = part.rcSrc.top + nValue;
		pElement->Attribute("ox", &nValue);
		part.nOffsetX = nValue;
		pElement->Attribute("oy", &nValue);
		part.nOffsetY = nValue;
	}
}

BOOL CEquipmentDoll::Create()
{
	m_nTexture = GetEngine()->GetTextureManager()->RegisterTexture( "data\\texture\\doll.tga", false ,TRUE);

	LoadConfig();
	return TRUE;
}

void CEquipmentDoll::LoadConfig()
{

	MeXmlDocument doc;
	if( !doc.LoadFile("..\\Data\\ClientConfig\\GameSetting.config") )
		return;

	/*
	<Equip>
	<Helmet u="0" v="0" w="64" h="64" ox="0" oy="0"></Helmet>
	<Shoulder u="64" v="0" w="64" h="64" ox="0" oy="0"></Shoulder>
	<Armoure u="128" v="0" w="64" h="64" ox="0" oy="0"></Armoure>
	<Sash u="192" v="0" w="64" h="64" ox="0" oy="0"></Sash>
	<Glove u="64" v="64" w="64" h="64" ox="0" oy="0"></Glove>
	<Shoe u="128" v="64" w="64" h="64" ox="0" oy="0"></Shoe>
	<Trousers u="192" v="64" w="64" h="64" ox="0" oy="0"></Trousers>
	<Spear u="64" v="0" w="64" h="64" ox="0" oy="0"></Spear>
	<Sword u="64" v="0" w="64" h="64" ox="0" oy="0"></Sword>
	<Staff u="64" v="0" w="64" h="64" ox="0" oy="0"></Staff>
	<Bow u="64" v="0" w="64" h="64" ox="0" oy="0"></Bow>
	<Fan u="64" v="0" w="64" h="64" ox="0" oy="0"></Fan>
	</Equip>
	*/
	MeXmlElement* pRoot = doc.FirstChildElement("Project")->FirstChildElement("EquipmentDollSetting");
	if( pRoot )
	{
        MeXmlElement* pElement = pRoot->FirstChildElement( "CenterPoint" );
        if( pElement )
        {
            int nTemp( 0 );
            if( pElement->Attribute( "ScreenX", &nTemp ) )
                m_nX = nTemp;
            if( pElement->Attribute( "ScreenY", &nTemp ) )
                m_nY = nTemp;
        }

		SetPartUI(m_parts[ePart_Helmet], pRoot, "Helmet");
		SetPartUI(m_parts[ePart_Shoulder], pRoot, "Shoulder");
		SetPartUI(m_parts[ePart_Armour], pRoot, "Armour");
		SetPartUI(m_parts[ePart_Sash], pRoot, "Sash");
		SetPartUI(m_parts[ePart_Glove], pRoot, "Glove");
		SetPartUI(m_parts[ePart_Shoe], pRoot, "Shoe");
		SetPartUI(m_parts[ePart_Ring], pRoot, "Ring");
		SetPartUI(m_parts[ePart_Bangle], pRoot, "Bangle");
		SetPartUI(m_parts[ePart_Necklace], pRoot, "Necklace");
		SetPartUI(m_parts[ePart_WeaponMinor], pRoot,"Trousers" /*"WeaponMinor"*/);
		//SetPartUI(m_parts[ePart_Trousers], pRoot, "Trousers");

		SetPartUI(m_parts[ePart_WarriorMain], pRoot, "ji");
		SetPartUI(m_parts[ePart_AssassinMain], pRoot, "wu");
		SetPartUI(m_parts[ePart_MageMain], pRoot, "jian");
		SetPartUI(m_parts[ePart_HunterMain], pRoot, "dao");
		SetPartUI(m_parts[ePart_TaoistMain], pRoot, "qiang");
		SetPartUI(m_parts[ePart_WeaponMain], pRoot, "MainWwapon"); //lyh++ 主武器

  //      SetPartUI(m_parts[ePart_WarriorMinor], pRoot, "WarriorMinor");
  //      SetPartUI(m_parts[ePart_AssassinMinor], pRoot, "AssassinMinor");
  //      SetPartUI(m_parts[ePart_MageMinor], pRoot, "MageMinor");
  //      SetPartUI(m_parts[ePart_HunterMinor], pRoot, "HunterMinor");
  //      SetPartUI(m_parts[ePart_TaoistMinor], pRoot, "TaoistMinor");
	}
}

void CEquipmentDoll::Destroy()
{
	if( m_nTexture != -1 )
	{
		GetEngine()->GetTextureManager()->UnRegisterTexture( m_nTexture );
		m_nTexture = -1;
	}
}
void CEquipmentDoll::Render( PartType mainType, PartType minorType )
{
#ifdef _DEBUG
	static bool needLoad = false;
	if (needLoad)
		LoadConfig();
#endif

	if( !m_bRender )
		return;
	//DWORD adwPartColor[ePart_Max];
	//for( int nPart = 0; nPart < ePart_Max; nPart++ )
	//{
	//	Part& part = m_parts[nPart];
	//	if( part.bDisable )
	//		continue;
	//	if( part.bNeedRepair  )
	//		adwPartColor[nPart] = 0xffff0000;
	//	//else if( part.nDamage < 50)
	//	else 
	//		adwPartColor[nPart] = 0xffffffff;
	//	RECT rcDst = 
	//	{ 
	//		x+part.nOffsetX, 
	//		y+part.nOffsetY, 
	//		x+part.nOffsetX+64, 
	//		y+part.nOffsetY+64 };

	//	GetDrawer()->Blt( 
	//		m_nTexture,
	//		&rcDst,
	//		&part.rcSrc,
	//		512,
	//		256,
	//		0.001f,
	//		adwPartColor[nPart],
	//		0 );
	//}

	for( int nPart = 0; nPart < ePart_WarriorMain/*ePart_WarriorMain*/; nPart++ )
	{
		DWORD color;
		Part& part = m_parts[nPart];
		if( part.bDisable ) 
			continue;
		if( part.bNeedRepair  )
			color = 0xffff0000;
		else 
			color = 0xffffffff;
		RECT rcDst;
		rcDst.left = SCREEN_WIDTH + ( m_nX + part.nOffsetX ) * ControlObject::GetSCALE(NULL);
		rcDst.right = rcDst.left + ( part.rcSrc.right - part.rcSrc.left ) * ControlObject::GetSCALE(NULL);
		rcDst.top = ( m_nY + part.nOffsetY ) * ControlObject::GetSCALE(NULL);
		rcDst.bottom = rcDst.top + ( part.rcSrc.bottom - part.rcSrc.top ) * ControlObject::GetSCALE(NULL);

		GetDrawer()->Blt( 
			m_nTexture,
			&rcDst,
			&part.rcSrc,
			256,
			256,
			0.001f,
			color,
			0 );
	}

	// 主手
    if( !m_parts[ePart_WeaponMain].bDisable )
    {
        DWORD color;
       // Part& part = m_parts[mainType]; //lyh--
		Part& part = m_parts[ePart_WeaponMain]; //lyh++ 所有的武器都用一张图即可
        if( m_parts[ePart_WeaponMain].bNeedRepair )
        {
            color = 0xffff0000;
        }
        else 
        {
            color = 0xffffffff;
        }

        RECT rcDst;
        rcDst.left = SCREEN_WIDTH + ( m_nX + part.nOffsetX ) * ControlObject::GetSCALE( NULL );
        rcDst.right = rcDst.left + ( part.rcSrc.right - part.rcSrc.left ) * ControlObject::GetSCALE( NULL );
        rcDst.top = ( m_nY + part.nOffsetY ) * ControlObject::GetSCALE( NULL );
        rcDst.bottom = rcDst.top + ( part.rcSrc.bottom - part.rcSrc.top ) * ControlObject::GetSCALE( NULL );

        GetDrawer()->Blt( m_nTexture, &rcDst, &part.rcSrc, 256, 256, 0.001f, color, 0 );
    }

    // 副手
    /*if( !m_parts[ePart_WeaponMinor].bDisable )
    {
        DWORD color;
        Part& part = m_parts[minorType];
        if( m_parts[ePart_WeaponMinor].bNeedRepair )
        {
            color = 0xffff0000;
        }
        else 
        {
            color = 0xffffffff;
        }

        RECT rcDst;
        rcDst.left = SCREEN_WIDTH + ( m_nX + part.nOffsetX ) * ControlObject::GetSCALE( NULL );
        rcDst.right = rcDst.left + ( part.rcSrc.right - part.rcSrc.left ) * ControlObject::GetSCALE( NULL );
        rcDst.top = ( m_nY + part.nOffsetY ) * ControlObject::GetSCALE( NULL );
        rcDst.bottom = rcDst.top + ( part.rcSrc.bottom - part.rcSrc.top ) * ControlObject::GetSCALE( NULL );

        GetDrawer()->Blt( m_nTexture, &rcDst, &part.rcSrc, 512, 256, 0.001f, color, 0 );
    }*/
}