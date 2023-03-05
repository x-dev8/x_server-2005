/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Hole.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Hole.h"
#include "Common.h"
#include "IconManagerClient.h"
#include "GlobalDef.h"
#include "Pack.h"
#include "ShowScreenText.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
GemBaseUI::GemBaseUI()
{
	// Member
	m_pID_PICTURE_Open1 = NULL;
	m_pID_PICTURE_Open2 = NULL;
	m_pID_PICTURE_Open3 = NULL;
	m_pID_PICTURE_Open4 = NULL;
	m_pID_LISTIMG_Hole1 = NULL;
	m_pID_LISTIMG_Hole2 = NULL;
	m_pID_LISTIMG_Hole3 = NULL;
	m_pID_LISTIMG_Hole4 = NULL;
	m_pID_PICTURE_Lock1 = NULL;
	m_pID_PICTURE_Lock2 = NULL;
	m_pID_PICTURE_Lock3 = NULL;
	m_pID_PICTURE_Lock4 = NULL;

	m_GemHoleIndex = -1;
}


void GemBaseUI::ResetUIObjects()
{
	EquipEvolveUI::ResetUIObjects();
	for(int i = 0; i < m_nMaxHoleNum; ++i)
	{
		m_UnHolePic[i] = NULL;
		m_HoledPic[i] = NULL;
		m_pID_LISTIMG_Hole[i] = NULL;
	}
	m_GemHoleIndex = -1;
}

void GemBaseUI::ClearEquip()
{
	EquipEvolveUI::ClearEquip();
	for(int i = 0; i < m_nMaxHoleNum; ++i)
	{
		m_pID_LISTIMG_Hole[i]->Clear();
	}
	m_GemHoleIndex = -1;
}

void GemBaseUI::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	if( !m_pID_FRAME_EquipEvolve )
		return;
	EquipEvolveUI::_RefreshEquipInfo(pListImg);
	for(int i = 0; i < m_nMaxHoleNum; ++i)
	{
		m_pID_LISTIMG_Hole[i]->Clear();
	}
	m_GemHoleIndex = -1;

	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	for(int i = 0; i < m_nMaxHoleNum; ++i)
	{
		m_UnHolePic[i]->SetVisable(nHole <= i);
		m_HoledPic[i]->SetVisable(nHole > i);
		m_pID_LISTIMG_Hole[i]->SetVisable(nHole > i);
		if (nHole > i)
		{
			if (pItem->equipdata.gemIds[i] != 0)
			{
				ControlIconDrag::S_ListImg liGem;
				liGem.SetData( pItem->equipdata.gemIds[i],1,eIcon_Enable );
				m_pID_LISTIMG_Hole[i]->SetItem( &liGem, 0 );

				m_GemHoleIndex = i;
			}
			RefreshDragEnable(pItem, i);
		}
		
	}

}

void GemBaseUI::InitializeGemBase()
{
	EquipEvolveIntialize();
	m_UnHolePic[0] = m_pID_PICTURE_Lock1;
	m_UnHolePic[1] = m_pID_PICTURE_Lock2;
	//m_UnHolePic[2] = m_pID_PICTURE_Lock3;
	//m_UnHolePic[3] = m_pID_PICTURE_Lock4;

	m_HoledPic[0] = m_pID_PICTURE_Open1;
	m_HoledPic[1] = m_pID_PICTURE_Open2;
	//m_HoledPic[2] = m_pID_PICTURE_Open3;
	//m_HoledPic[3] = m_pID_PICTURE_Open4;

	m_pID_LISTIMG_Hole[0] = m_pID_LISTIMG_Hole1;
	m_pID_LISTIMG_Hole[1] = m_pID_LISTIMG_Hole2;
	//m_pID_LISTIMG_Hole[2] = m_pID_LISTIMG_Hole3;
	//m_pID_LISTIMG_Hole[3] = m_pID_LISTIMG_Hole4;
	for(int i = 0; i < m_nMaxHoleNum; ++i)
	{
		m_pID_LISTIMG_Hole[i]->SetEnableDrag(false);
	}
	m_GemHoleIndex = -1;
}

bool GemBaseUI::_IsFullHole( ControlIconDrag::S_ListImg * pImg )
{
	SCharItem* pItem = ((SCharItem*)pImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return true;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	if (nHole >= m_nMaxHoleNum)
	{
		return true;
	}
	return false;

}

void GemBaseUI::RefreshDragEnable( SCharItem* pItem, int index )
{
	;
}


void FillGemInfoInList( uint16 gemId,ControlList* pList )
{
	pList->Clear();
	ItemDefine::SItemGem* pGem = ( ItemDefine::SItemGem* )GettheItemDetail().GetItemByID(gemId);
	for (int i = 0; i < ItemDefine::SItemGem::CD_TypeCount; ++i)
	{
		if (pGem->type[i] != 0)
		{
			ControlList::S_List sList;
			char szTemp[256] = {0};
			sprintf( szTemp, "%s+%d", S_IconInfoHero::GetRandStringByType( pGem->type[i] ).c_str(), (int)pGem->value[i].fValue );
			sList.SetData(szTemp,i,NULL,Color_Config.getColor(CC_Gem_Attribute));
			sList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
			pList->AddItem(&sList);
		}

	}
}