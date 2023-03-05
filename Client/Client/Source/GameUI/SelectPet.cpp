/********************************************************************
Created by UIEditor.exe
FileName: F:\project\Turbo\Bin\Client\Data\Ui\SelectPet.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SelectPet.h"
#include "ui/SeekPet.h"
#include "PlayerRole.h"
#include "GlobalDef.h"
#include "Helper/PetHelper.h"
#include "ui\PrivateShop.h"
#include "SystemStallage.h"
#include "Bargaining.h"
#include "ui/SeeSuAnimal.h"
#include "Common.h"
#include "ScreenInfoManager.h"

CUI_ID_FRAME_SelectPet s_CUI_ID_FRAME_SelectPet;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SelectPet, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SelectPet, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectPet, ID_BUTTON_SelectOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelectPet, ID_LIST_PetNameOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectPet, ID_BUTTON_SeekOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectPet, ID_BUTTON_CallBackOnButtonClick )
CUI_ID_FRAME_SelectPet::CUI_ID_FRAME_SelectPet()
{
	// Member
	m_pID_FRAME_SelectPet = NULL;
	m_pID_BUTTON_Select = NULL;
	m_pID_LIST_PetName = NULL;
	m_pID_BUTTON_Seek = NULL;
	m_pID_BUTTON_CallBack = NULL;
	m_bEnableSelect = true;

}
// Frame
bool CUI_ID_FRAME_SelectPet::OnFrameRun()
{
	if(!IsVisable() || ( !s_CUI_ID_FRAME_PrivateShop._IsVisable() && !s_CUI_ID_FRAME_Bargaining.IsVisable() ) )
		return true;

	RECT rcMain;
	if ( s_CUI_ID_FRAME_PrivateShop._IsVisable() )
	{
		s_CUI_ID_FRAME_PrivateShop.GetFrame()->GetRealRect(&rcMain);
	}
	else
	{
		s_CUI_ID_FRAME_Bargaining.GetFrame()->GetRealRect(&rcMain);
	}
	

	RECT rcMe;
	m_pID_FRAME_SelectPet->GetRealRect(&rcMe);
	int nWidth = rcMe.right - rcMe.left;
	int nHeight = rcMe.bottom - rcMe.top;

	RECT rcNew;
	if (rcMain.left < nWidth)
	{
		rcNew.left = rcMain.right; 
	}
	else
	{
		rcNew.left = rcMain.left - nWidth; 
	}
	rcNew.top = rcMain.top;

	m_pID_FRAME_SelectPet->SetPos(rcNew.left, rcNew.top);

	return true;
}
bool CUI_ID_FRAME_SelectPet::OnFrameRender()
{
	return true;
}
// Button  选择
bool CUI_ID_FRAME_SelectPet::ID_BUTTON_SelectOnButtonClick( ControlObject* pSender )
{
	ControlList::S_List *pItem = NULL;
	if(m_pID_LIST_PetName)
		pItem = m_pID_LIST_PetName->GetCurSelItem();

	if(pItem != NULL)
	{
		SPetItem *pet = (SPetItem *)pItem->m_pData;
		if(pet != NULL)
		{
			if(s_CUI_ID_FRAME_PrivateShop.IsVisable())
			{
				if(pet->baseInfo.IsExitesEquip())//摆摊
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetEquipError));
					return true;
				}
				s_CUI_ID_FRAME_PrivateShop.AddPetToSell(thePlayerRole.GetPetIndex(pet->GetPetGuid()));
			}
			else if ( s_CUI_ID_FRAME_Bargaining.IsVisable() )
			{
				//判断副将是否已经有装备了
				if(pet->baseInfo.IsExitesEquip())//交易
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetEquipError));
					return true;
				}
				s_CUI_ID_FRAME_Bargaining.AddPetToBargain( thePlayerRole.GetPetIndex(pet->GetPetGuid()) );
			}
			
		}
	}
	RefreshButtonStatus();
	return true;
}
// List
void CUI_ID_FRAME_SelectPet::ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( m_bEnableSelect == false )
	{
		((ControlList*)pSender)->SetCurSelIndex(-1);
		return;
	}
	
	RefreshButtonStatus();

}
// Button	查看
bool CUI_ID_FRAME_SelectPet::ID_BUTTON_SeekOnButtonClick( ControlObject* pSender )
{
	ControlList::S_List *pItem = NULL;
	if(m_pID_LIST_PetName)
		pItem = m_pID_LIST_PetName->GetCurSelItem();

	if(pItem != NULL)
	{
		SPetItem *pet = (SPetItem *)pItem->m_pData;
		if(pet != NULL)
		{
			s_CUI_ID_FRAME_SeeSuAnimal.SetVisable(true);
			s_CUI_ID_FRAME_SeeSuAnimal.SetPetItem(*pet);
		}
	}

	return true;
}
// Button  召回
bool CUI_ID_FRAME_SelectPet::ID_BUTTON_CallBackOnButtonClick( ControlObject* pSender )
{
	ControlList::S_List *pItem = NULL;
	if(m_pID_LIST_PetName)
		pItem = m_pID_LIST_PetName->GetCurSelItem();

	if(pItem != NULL)
	{
		SPetItem *pet = (SPetItem *)pItem->m_pData;
		if(pet != NULL)
		{
			if(s_CUI_ID_FRAME_PrivateShop.IsVisable())
			{
				CSystemStallage::Instance()->RemovePetSell(*pet);
			}
			else if ( s_CUI_ID_FRAME_Bargaining.IsVisable() )
			{
				s_CUI_ID_FRAME_Bargaining.CallBackPetFromBargain( thePlayerRole.GetPetIndex(pet->GetPetGuid()) );
				//RefreshButtonStatus();
				Refresh(true);
			}
		}
	}

	return true;
}

// 装载UI
bool CUI_ID_FRAME_SelectPet::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SelectPet.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SelectPet.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SelectPet::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SelectPet, s_CUI_ID_FRAME_SelectPetOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SelectPet, s_CUI_ID_FRAME_SelectPetOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SelectPet, ID_BUTTON_Select, s_CUI_ID_FRAME_SelectPetID_BUTTON_SelectOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_SelectPet, ID_LIST_PetName, s_CUI_ID_FRAME_SelectPetID_LIST_PetNameOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_SelectPet, ID_BUTTON_Seek, s_CUI_ID_FRAME_SelectPetID_BUTTON_SeekOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SelectPet, ID_BUTTON_CallBack, s_CUI_ID_FRAME_SelectPetID_BUTTON_CallBackOnButtonClick );

	m_pID_FRAME_SelectPet = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SelectPet );
	m_pID_BUTTON_Select = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelectPet, ID_BUTTON_Select );
	m_pID_LIST_PetName = (ControlList*)theUiManager.FindControl( ID_FRAME_SelectPet, ID_LIST_PetName );
	m_pID_BUTTON_Seek = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelectPet, ID_BUTTON_Seek );
	m_pID_BUTTON_CallBack = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelectPet, ID_BUTTON_CallBack );
	assert( m_pID_FRAME_SelectPet );
	assert( m_pID_BUTTON_Select );
	assert( m_pID_LIST_PetName );
	assert( m_pID_BUTTON_Seek );
	assert( m_pID_BUTTON_CallBack );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SelectPet::_UnLoadUI()
{
	m_pID_FRAME_SelectPet = NULL;
	m_pID_LIST_PetName = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SelectPet.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SelectPet::_IsVisable()
{
	return m_pID_FRAME_SelectPet->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SelectPet::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_SelectPet->SetVisable( bVisable );

	if(IsVisable())
	{
		Refresh();
	}
	if (!bVisable)
	{
		m_bEnableSelect = true;
		m_pID_LIST_PetName->SetCurSelIndex(-1);
	}
}

void CUI_ID_FRAME_SelectPet::Refresh(  bool bKeepSelect /*= false */ )
{
	if(!IsVisable() || NULL == m_pID_LIST_PetName)
		return;


	int oldIdx = m_pID_LIST_PetName->GetCurSelIndex();

	m_pID_LIST_PetName->Clear();

	ControlList::S_List	stItem;
	for(int i=0; i<ITEM_PET_MAXCOUNT; ++i)
	{
		SPetItem &pet = thePlayerRole.GetPetByIndex(i);

		if(!IsValidPet(pet))
			continue;

		stItem.clear();
		
		DWORD stateClr = 0xFFFFFFFF;
		if( pet.baseInfo.isActive )
		{
			stateClr = 0xFF00FF00;		//出战显示绿色
		}
		if ( s_CUI_ID_FRAME_Bargaining.IsPetInBargain( i ) )
		{
			stateClr = 0xFFFF0000;		//选中显示红色，优先显示选中状态
		}
		ItemDefine::SPetMonster *pPetMonster = GettheItemDetail().GetPetById(pet.baseInfo.petId);
		char temp[64]={0};
		if(pPetMonster != NULL)
		{
			if (strcmp(pPetMonster->GetName(),pet.GetPetName())!= 0)
			{
				MeSprintf_s(temp,sizeof(temp),"%s(%s)",pet.GetPetName(),pPetMonster->GetName());
			}
			else
			{
				MeSprintf_s(temp,sizeof(temp),"%s",pet.GetPetName());
			}
		}
		else
		{
			MeSprintf_s(temp,sizeof(temp),"%s",pet.GetPetName());
		}

		stItem.SetData(temp, 0, &pet, stateClr );

		m_pID_LIST_PetName->AddItem(&stItem, NULL, false);
	}
	
	if ( bKeepSelect == true )
	{
		m_pID_LIST_PetName->SetCurSelIndex( oldIdx );
	}
	

	RefreshButtonStatus();
	
	
}

void CUI_ID_FRAME_SelectPet::RefreshButtonStatus(void)
{
	bool canSelected = false;
	bool canSeek = false;
	bool canCallback = false;

	ControlList::S_List *pItem = NULL;
	if(m_pID_LIST_PetName)
		pItem = m_pID_LIST_PetName->GetCurSelItem();

	if(pItem != NULL)
	{
		SPetItem *pet = (SPetItem *)pItem->m_pData;
		if(pet != NULL)
		{
			canSeek = true;

			if ( s_CUI_ID_FRAME_PrivateShop._IsVisable() )
			{
				if(!CSystemStallage::Instance()->IsPetInStallage(pet->GetPetGuid()))
					canSelected = true;
				else
					canCallback = true;
			}
			else if( s_CUI_ID_FRAME_Bargaining.IsVisable() )
			{
				if(!s_CUI_ID_FRAME_Bargaining.IsPetInBargain(thePlayerRole.GetPetIndex(pet->GetPetGuid())))
				{
					if ( pet->baseInfo.isActive )
					{
						canSelected = false;	//出战状态下也是不能选择的
					}
					else
					{
						canSelected = true;
					}
					
					
				}
				else
					canCallback = true;
			}
		}
	}

	if(m_pID_BUTTON_Seek)
		m_pID_BUTTON_Seek->SetEnable(canSeek);

	if(!canCallback && !canSelected)
	{
		if(m_pID_BUTTON_Select)
		{
			m_pID_BUTTON_Select->SetVisable(true);
			m_pID_BUTTON_Select->SetEnable(false);
		}

		if(m_pID_BUTTON_CallBack)
			m_pID_BUTTON_CallBack->SetVisable(false);
	}
	else
	{
		if(m_pID_BUTTON_CallBack)
		{
			m_pID_BUTTON_CallBack->SetEnable(true);
			m_pID_BUTTON_CallBack->SetVisable(canCallback);
		}

		if(m_pID_BUTTON_Select)
		{
			m_pID_BUTTON_Select->SetEnable(true);
			m_pID_BUTTON_Select->SetVisable(canSelected);
		}
	}


}

void CUI_ID_FRAME_SelectPet::RefreshButtonStatusForBargaining()
{
	
}

void CUI_ID_FRAME_SelectPet::EnableSelect( bool bEnable )
{
	Refresh();
	m_bEnableSelect = bEnable;
}
