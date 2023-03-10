/********************************************************************
	Created by UIEditor.exe
	FileName: E:\trunk\Bin\Client\Data\Ui\PetMaterialUp.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimalMaterialUp.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "GameMain.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "baseProperty.h"
#include "Rename.h"
#include "Dxsdk/dinput.h"
#include "ui/PrivateShop.h"
#include "Me3d/ShaderManager.h"
#include "color_config.h"
#include "PrivateShop.h"
#include "Me3d/Engine/RendererDX.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/SwGlobal.h"
#include "wsRender.h"
#include "exmain.h"
#include "Main.h"
#include "ActionUI.h"
#include "wsCamera.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "WealthProtect.h"
#include "MessageBox.h"
#include "ItemDetail.h"
#include "SoundConfig.h"
#include "SystemStallage.h"
#include "PetSettingConfig.h"  
#include "ui/SuAnimal.h"
#include "Pack.h"
#include "PackItemEnableManager.h"
CUI_ID_FRAME_SuAnimalMaterialUp s_CUI_ID_FRAME_SuAnimalMaterialUp;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimalMaterialUp, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimalMaterialUp, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_BUTTON_ToLeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_BUTTON_ToRightOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_LISTIMG_PetStudySkillOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_LISTIMG_PetStudySkillOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_LISTIMG_PetStudySkillOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_LISTIMG_PetStudySkillOnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_LIST_PetNameOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_BUTTON_SureOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_BUTTON_ExamineOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMaterialUp, ID_BUTTON_ChoiceOnButtonClick )
CUI_ID_FRAME_SuAnimalMaterialUp::CUI_ID_FRAME_SuAnimalMaterialUp()
{
	// Member
	m_pID_FRAME_PetMaterialUp = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TitleTop = NULL;
	m_pID_PICTURE_PetModel = NULL;
	m_pID_BUTTON_ToLeft = NULL;
	m_pID_BUTTON_ToRight = NULL;
	m_pID_LISTIMG_PetStudySkill = NULL;
	m_pID_PICTURE_Motherboard = NULL;
	m_pID_TEXT_PetNameTitle = NULL;
	m_pID_LIST_PetName = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_BUTTON_Examine = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_TEXT_ApperceptionZ = NULL;
	m_pID_TEXT_NowApperception = NULL;
	m_pID_TEXT_Probability = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Choice = NULL;
	m_pID_TEXT_ConsumeMoney = NULL;
	m_pID_TEXT_LockedMoney = NULL;
	m_pID_TEXT_CurrentMoney = NULL;

}
// Frame
bool CUI_ID_FRAME_SuAnimalMaterialUp::OnFrameRun()
{
	int nSroollBarHeight = 0;
	if (s_CUI_ID_FRAME_SuAnimalMaterialUp.IsVisable())
	{
		m_nLastHeight  = m_pID_LIST_PetName->GetShowStartHeight();
		if (m_pID_LIST_PetName->GetScrollBar())
		{
			nSroollBarHeight = m_pID_LIST_PetName->GetScrollBar()->GetValue();
		}
		if ( m_bNeedRefresh)
		{
			Refresh_Help(m_bNeedRefresh);
			SetNeed_Refresh(false);
		}
		int nSelelctID = m_pID_LIST_PetName->GetCurSelIndex();
		SPetItem &mount = thePlayerRole.GetPetByIndex(nSelelctID); 

		if (m_bRotate && m_pID_BUTTON_ToRight->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			m_fRotateZ += 1.5f*theHeroGame.GetFrameElapsedTime();
		}
		else if (m_bRotate && m_pID_BUTTON_ToLeft->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			m_fRotateZ -= 1.5f*theHeroGame.GetFrameElapsedTime();
		}
		else 
			m_bRotate = false;
	}
	m_pID_LIST_PetName->SetShowStartHeight(m_nLastHeight);
	m_pID_LIST_PetName->SetScrollValue(nSroollBarHeight);
	return true;
}
bool CUI_ID_FRAME_SuAnimalMaterialUp::OnFrameRender()
{
	if (m_pID_LIST_PetName ->GetListItemCnt() >0)
	{
		GetEngine()->GetRenderer()->EndScene();
		RenderViewport();
		GetEngine()->GetRenderer()->BeginScene();
	}
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_BUTTON_ToLeftOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_BUTTON_ToRightOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	m_bRotate = false;
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_LISTIMG_PetStudySkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	return DragItemOn(0,pItemDrag,pSender);
}
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_LISTIMG_PetStudySkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_LISTIMG_PetStudySkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_LISTIMG_PetStudySkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	if( pItem && pItem->m_eEnable == eIcon_Disable )
		return false;
	if( s_CUI_ID_FRAME_PrivateShop.IsVisable() )
	{
		int nNullIndex = s_CUI_ID_FRAME_PrivateShop.PetList_GetNullItem();
		if( nNullIndex == -1 )		return false;
		s_CUI_ID_FRAME_PrivateShop.ID_LISTIMG_PetListOnIconDragOn( pSender, 0, pItem,
		s_CUI_ID_FRAME_PrivateShop.PetList_GetItemByIndex( nNullIndex ) );
		return true;
	}
	else if( s_CUI_ID_FRAME_Bargaining.IsVisable() )
	{
		int nNullIndex = s_CUI_ID_FRAME_Bargaining.PetList_GetNullItem();
		if( nNullIndex == -1 )		return false;

		s_CUI_ID_FRAME_Bargaining.ID_LISTIMG_MyPetOnIconDragOn( pSender, 0, pItem,
		s_CUI_ID_FRAME_Bargaining.GetLISTIMG_MyPetItem( nNullIndex ) );
		return true;
	}
	return false;
}
// List
void CUI_ID_FRAME_SuAnimalMaterialUp::ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return;
	m_fRotateZ = 0.0f;
	PetSelectChange(m_pID_LIST_PetName->GetCurSelIndex());
	RefreshPetList();
}
// Button
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_BUTTON_SureOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	return ReadyOk();
}
// Button
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_BUTTON_ExamineOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	int n_index = m_pID_LIST_PetName->GetCurSelIndex();
	s_CUI_ID_FRAME_SuAnimal.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimal.LookPet(n_index);

	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalMaterialUp::ID_BUTTON_ChoiceOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetMaterialUp )   return false;
	int m_index = m_pID_LIST_PetName->GetCurSelIndex();
	m_fRotateZ = 0.0f;
	PetSelectChange(m_index);
	return true;
}

// ????UI
bool CUI_ID_FRAME_SuAnimalMaterialUp::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimalMaterialUp.MEUI" ,false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("????????[Data\\UI\\SuAnimalMaterialUp.MEUI]????")
		return false;
	}
	return DoControlConnect();
}
// ????????
bool CUI_ID_FRAME_SuAnimalMaterialUp::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PetMaterialUp, s_CUI_ID_FRAME_SuAnimalMaterialUpOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PetMaterialUp,s_CUI_ID_FRAME_SuAnimalMaterialUpOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PetMaterialUp, ID_BUTTON_HELP, s_CUI_ID_FRAME_SuAnimalMaterialUpID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetMaterialUp, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SuAnimalMaterialUpID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetMaterialUp, ID_BUTTON_ToLeft, s_CUI_ID_FRAME_SuAnimalMaterialUpID_BUTTON_ToLeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetMaterialUp, ID_BUTTON_ToRight, s_CUI_ID_FRAME_SuAnimalMaterialUpID_BUTTON_ToRightOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_PetMaterialUp, ID_LISTIMG_PetStudySkill, s_CUI_ID_FRAME_SuAnimalMaterialUpID_LISTIMG_PetStudySkillOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetMaterialUp, ID_LISTIMG_PetStudySkill, s_CUI_ID_FRAME_SuAnimalMaterialUpID_LISTIMG_PetStudySkillOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetMaterialUp, ID_LISTIMG_PetStudySkill, s_CUI_ID_FRAME_SuAnimalMaterialUpID_LISTIMG_PetStudySkillOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetMaterialUp, ID_LISTIMG_PetStudySkill, s_CUI_ID_FRAME_SuAnimalMaterialUpID_LISTIMG_PetStudySkillOnIconRButtonUp );
	theUiManager.OnListSelectChange( ID_FRAME_PetMaterialUp, ID_LIST_PetName, s_CUI_ID_FRAME_SuAnimalMaterialUpID_LIST_PetNameOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_PetMaterialUp, ID_BUTTON_Sure, s_CUI_ID_FRAME_SuAnimalMaterialUpID_BUTTON_SureOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetMaterialUp, ID_BUTTON_Examine, s_CUI_ID_FRAME_SuAnimalMaterialUpID_BUTTON_ExamineOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetMaterialUp, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SuAnimalMaterialUpID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetMaterialUp, ID_BUTTON_Choice, s_CUI_ID_FRAME_SuAnimalMaterialUpID_BUTTON_ChoiceOnButtonClick );

	m_pID_FRAME_PetMaterialUp = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetMaterialUp );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_BUTTON_CLOSE );
	m_pID_TEXT_TitleTop = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_TEXT_TitleTop );
	m_pID_PICTURE_PetModel = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_PICTURE_PetModel );
	m_pID_BUTTON_ToLeft = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_BUTTON_ToLeft );
	m_pID_BUTTON_ToRight = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_BUTTON_ToRight );
	m_pID_LISTIMG_PetStudySkill = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_LISTIMG_PetStudySkill );
	m_pID_PICTURE_Motherboard = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_PICTURE_Motherboard );
	m_pID_TEXT_PetNameTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_TEXT_PetNameTitle );
	m_pID_LIST_PetName = (ControlList*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_LIST_PetName );
	m_pID_BUTTON_Sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_BUTTON_Sure );
	m_pID_BUTTON_Examine = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_BUTTON_Examine );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_TEXT_Explain );
	m_pID_TEXT_ApperceptionZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_TEXT_ApperceptionZ );
	m_pID_TEXT_NowApperception = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_TEXT_NowApperception );
	m_pID_TEXT_Probability = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_TEXT_Probability );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_BUTTON_Cancel );
	m_pID_BUTTON_Choice = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_BUTTON_Choice );
	m_pID_TEXT_ConsumeMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_TEXT_ConsumeMoney );
	m_pID_TEXT_LockedMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_TEXT_LockedMoney );
	m_pID_TEXT_CurrentMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMaterialUp, ID_TEXT_CurrentMoney );

	assert( m_pID_FRAME_PetMaterialUp );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_TitleTop );
	assert( m_pID_PICTURE_PetModel );
	assert( m_pID_BUTTON_ToLeft );
	assert( m_pID_BUTTON_ToRight );
	assert( m_pID_LISTIMG_PetStudySkill );
	assert( m_pID_PICTURE_Motherboard );
	assert( m_pID_TEXT_PetNameTitle );
	assert( m_pID_LIST_PetName );
	assert( m_pID_BUTTON_Sure );
	assert( m_pID_BUTTON_Examine );
	assert( m_pID_TEXT_Explain );
	assert( m_pID_TEXT_ApperceptionZ );
	assert( m_pID_TEXT_NowApperception );
	assert( m_pID_TEXT_Probability );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Choice );
	assert( m_pID_TEXT_ConsumeMoney );
	assert( m_pID_TEXT_LockedMoney );
	assert( m_pID_TEXT_CurrentMoney );

	m_pPlayerAnim = MeNew CPlayerAnim;
	m_pPlayer = MeNew CPlayer;
	m_pPlayer->SetAnim( m_pPlayerAnim );
	m_pPlayerAnim->SetPlayer( m_pPlayer );
	theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayer );
	m_pID_BUTTON_ToRight->SetLButtonDownFun(UIPetMaterialUp_RightLBD);
	m_pID_BUTTON_ToLeft->SetLButtonDownFun(UIPetMaterialUp_LeftLBD);
	_SetVisable(false);
	return true;
}
// ????UI
bool CUI_ID_FRAME_SuAnimalMaterialUp::_UnLoadUI()
{
	m_pID_FRAME_PetMaterialUp = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TitleTop = NULL;
	m_pID_PICTURE_PetModel = NULL;
	m_pID_BUTTON_ToLeft = NULL;
	m_pID_BUTTON_ToRight = NULL;
	m_pID_LISTIMG_PetStudySkill = NULL;
	m_pID_PICTURE_Motherboard = NULL;
	m_pID_TEXT_PetNameTitle = NULL;
	m_pID_LIST_PetName = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_BUTTON_Examine = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_TEXT_ApperceptionZ = NULL;
	m_pID_TEXT_NowApperception = NULL;
	m_pID_TEXT_Probability = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Choice = NULL;
	m_pID_TEXT_ConsumeMoney = NULL;
	m_pID_TEXT_LockedMoney = NULL;
	m_pID_TEXT_CurrentMoney = NULL;

	if (m_pPlayer != NULL)
	{
		theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer(m_pPlayer);
		m_pPlayer->Destroy();
		delete m_pPlayer;
		m_pPlayer = 0;
		m_pPlayerAnim = 0;
	}
	m_pID_FRAME_PetMaterialUp = NULL;
	
	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimalMaterialUp.MEUI" );
}
// ????????
bool CUI_ID_FRAME_SuAnimalMaterialUp::_IsVisable()
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	return m_pID_FRAME_PetMaterialUp->IsVisable();
}
// ????????????
void CUI_ID_FRAME_SuAnimalMaterialUp::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return ;
	m_pID_FRAME_PetMaterialUp->SetVisable( bVisable );
	m_fRotateZ = 0.0f;
	m_nModelId = -1;

	if (bVisable)
	{
		Refresh(false);
		PlaySoundConfig(SoundConfig::EST_OpenPackUI);
	}
}

void CUI_ID_FRAME_SuAnimalMaterialUp::Refresh_Help(bool _is)
{
	if (!IsVisable())
		return;

	int nSelId = m_pID_LIST_PetName->GetCurSelIndex();
	RefreshMoney();
	m_pID_LIST_PetName->Clear();
	//m_pID_LISTIMG_PetIcon->Clear();
	m_pID_PICTURE_PetModel->SetVisable(false);
	m_pID_PICTURE_PetModel->SetPicName("");

	//m_pActivedPet = 0;
	int nActivePetIndex = -1;

	int nMaxCount = thePetSettingConfig.GetPlayerPetLimit(thePlayerRole.GetLevel());

	for (int i = 0; i < nMaxCount; ++i)
	{
		if (thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId != InvalidLogicNumber)
		{
			ControlList::S_List sData;

			// ??????
			ItemDefine::SPetMonster* pCommon = GettheItemDetail().GetPetById( thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId );
			if( !pCommon )
				continue;

			DWORD dwColor = S_IconInfoHero::GetPetShowColor( &thePlayerRole.m_charinfo.ItemBagData.petItems[i]);
			SPetItem &mount = thePlayerRole.GetPetByIndex(nSelId);
			if ((&mount) != NULL && mount.baseInfo.guid == thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.guid)
			{
				dwColor = S_IconInfoHero::GetPetShowColor(NULL);
			}
			sData.SetData( thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.szName, 
				thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId, 
				0, 
				dwColor );
			m_pID_LIST_PetName->AddItem(&sData,NULL, false);

			// ????icon??????
		/*	ControlListImage::S_ListImg stItemImage;
			stItemImage.SetData( thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId, 1 );
			((SCharItem*)stItemImage.m_pkIconInfo->GetData())->itembaseinfo.nOnlyInt = thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.guid;

			m_pID_LISTIMG_PetIcon->SetItem( &stItemImage, i );
		*/
			if (thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.isActive)
			{
				m_pActivedPet = &thePlayerRole.GetCharInfo2().ItemBagData.petItems[i];
				nActivePetIndex = i;				
			}
		}
	}

	/*char buf[64];
	sprintf(buf, "%d/%d", thePlayerRole.GetPetCount(), nMaxCount);
	m_pID_TEXT_TakeNum->SetText(buf);*/

	//RefreshFightState(nActivePetIndex);

 		if (_is)
 			m_pID_LIST_PetName->SetCurSelIndex(m_pID_LIST_PetName->GetListItemCnt() - 1);
 		else if (nSelId == -1)
 			m_pID_LIST_PetName->SetCurSelIndex(0);
 		else
		m_pID_LIST_PetName->SetCurSelIndex(nSelId);
	PetSelectChange(nSelId);
	RefreshItemInfo();
}

void CUI_ID_FRAME_SuAnimalMaterialUp::PetSelectChange(int nindex)
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return ;
	m_pID_TEXT_NowApperception->SetText("");//????????
	RefreshMoney();
	if (nindex <0)  return ;
	
	SPetItem &mount = thePlayerRole.GetPetByIndex(nindex);
	if (mount.baseInfo.petId != InvalidLogicNumber)
	{
		ItemDefine::SPetMonster* m_petMonster = GettheItemDetail().GetPetById(mount.baseInfo.petId);
		if (m_petMonster !=NULL &&(m_petMonster->bIsBaby ||m_petMonster->bIsAberrance || !mount.baseInfo.isActive) )
		{
			m_pID_TEXT_NowApperception->SetText(mount.baseInfo.savvy);//????????????
			ChangeModel(mount,m_pPlayerAnim,m_nModelId);
			RefreshMonsy(mount);
			AutoAddMaterial(mount);
		}
		else 
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSavvyFull) );
			return ;
		}
	}
	
}
void CUI_ID_FRAME_SuAnimalMaterialUp::RefreshMonsy(SPetItem &mount)
{
	RefreshMoney();
	ItemDefine::SPetMonster* m_petMonster = GettheItemDetail().GetPetById(mount.baseInfo.petId);
	int quality = 0;
	int m_level = 0;
	if (m_petMonster != NULL)
	{
		quality = m_petMonster->catchQuality;
		m_level = m_petMonster->catchLevel;
	}
	int Rate = thePetSettingConfig.GetSavvyUpItemRate(quality,m_level,mount.baseInfo.savvy); //??????
	int money = thePetSettingConfig.GetSavvyUpItemMoney(quality,m_level,mount.baseInfo.savvy);//????????
	if (m_pID_TEXT_ConsumeMoney != NULL)
	{
		std::string text;
		text.clear();
		thePlayerRole.GetGSCStringFromMoney(money,text);
		if (thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) < (DWORD)money)
		{
			m_pID_TEXT_ConsumeMoney->SetText(text.c_str(),0xffff0000);
			m_pID_BUTTON_Sure->SetEnable(false);
		}
		else
		{
			*m_pID_TEXT_ConsumeMoney = text;
			m_pID_BUTTON_Sure->SetEnable(true);
		}
	}
	if (m_pID_TEXT_Probability != NULL)
	{
		m_pID_TEXT_Probability->SetText(Rate);
	}
}
void CUI_ID_FRAME_SuAnimalMaterialUp::RefreshByMoneyChange()
{	
	int nSelId = m_pID_LIST_PetName->GetCurSelIndex();
	SPetItem &monut = thePlayerRole.GetPetByIndex(nSelId);
	RefreshMonsy(monut);
}
void CUI_ID_FRAME_SuAnimalMaterialUp::ChangeModel(SPetItem &mount, CPlayerAnim* pAnim, int& iOldModelId )
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return ;
	int nModelId = mount.baseInfo.petId;
	if( iOldModelId == nModelId )
		return;

	iOldModelId = nModelId;

	int	nResMexID = -1;
	ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById(mount.baseInfo.petId);
	if(!pPetMonster)
		return;
	if( pAnim )
	{
		pAnim->MyChangeModel( pPetMonster->iModelID, TRUE, NULL );
		pAnim->SetCurAnimType(-1);
	}
}

bool CUI_ID_FRAME_SuAnimalMaterialUp::DragItemOn(int index, ControlIconDrag::S_ListImg* pItemDrag, ControlObject* pSender)
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_PetStudySkill->GetItemByIndex(0);
	if (pListImg == NULL)  return false;
	
	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)      return false;
	if (pItem->equipdata.gemIds[index] != 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_GemInHole) );
		return false;
	}
	if (!IsTypeMatch(pItemDrag))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_GemTypeError) );
		return false;
	}

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE ) )
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

		// ??????
		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
		{			
			short m_sIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );

			SCharItem item;
			if(m_sIndex != -1 && thePlayerRole.m_bag.GetItem(m_sIndex,&item))
			{
				item_info.nOnlyInt = item.itembaseinfo.nOnlyInt;
				item_info.ustItemID = item.itembaseinfo.ustItemID;
				item_info.n_index   = m_sIndex;
			}
			else
			{
				item_info.nOnlyInt =InvalidLogicNumber;
				item_info.ustItemID = InvalidLogicNumber;
			}
			//m_shMaterialBagType[0] = BT_MaterialBag;
			ControlIconDrag::S_ListImg liGem;
			liGem.SetData( pItemDrag->m_pkIconInfo->GetItemId(),1,eIcon_Enable );
			m_pID_LISTIMG_PetStudySkill->SetItem( &liGem, 0 );
			//FillGemInfoInList(item.GetItemID(),m_GemInfoList[index]);
		}
		else
		{
			return false;
		}
		//m_bMaterialBagEnable[0] = false;
	}
	return true;
}

bool  CUI_ID_FRAME_SuAnimalMaterialUp::ReadyOk()
{
	//int nSavvyUpMoney = thePetSettingConfig.GetSavvyUpMoney( pMonsterConfig->catchQuality, pMonsterConfig->catchLevel, pPetItem->baseInfo.savvy );
	//int nSavvyUpRate  = thePetSettingConfig.GetSavvyUpRate ( pMonsterConfig->catchQuality, pMonsterConfig->catchLevel, pPetItem->baseInfo.savvy);
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	if (item_info.ustItemID ==InvalidLogicNumber ) 
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetNoneItem) );
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_ListInfo_RandomTip,theXmlString.GetString(eText_PetNoneItem));
		return false;
	}
	SPetItem pPet = thePlayerRole.GetPetByIndex(GetCurrentMountIndex());
	if(pPet.baseInfo.guid == InvalidLogicNumber)
		return false;
	if (pPet.baseInfo.savvy == PetSettingConfig::EPetSavvy_LevelMax)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_Pet_MaxSavvy));
		return false;
	}
	ItemDefine::SItemCommon * pItemCommon = GettheItemDetail().GetItemByID(item_info.ustItemID);

	if( pItemCommon != NULL)
	{
		ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore*)pItemCommon;
		if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE && 
			pRestore->specialFunction == ItemDefine::EPetFunc_AddSavvy)
		{
			MsgUseGoodsToPet msg;
			msg.nPetIndex = GetCurrentMountIndex();
			if(msg.nPetIndex != -1)
			{
				msg.nGuid =item_info.nOnlyInt;
				msg.ustItemIndex = item_info.n_index;
				msg.stItemCount = 1;
				msg.stSrcChar = 0;
				msg.stDstChar = 0;
				msg.ucItemBagType = BT_NormalItemBag;
				GettheNetworkInput().SendMsg( &msg );
				//RefreshProperty();
				return true;
			}
		}
	}
	return false;
}
short CUI_ID_FRAME_SuAnimalMaterialUp::GetCurrentMountIndex()
{
	if( !m_pID_FRAME_PetMaterialUp )
		return -1;
	return m_pID_LIST_PetName->GetCurSelIndex();	
}
void CUI_ID_FRAME_SuAnimalMaterialUp::RenderViewport()
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return ;
	RECT rc;
	m_pID_PICTURE_PetModel->GetRealRect(&rc);
	RenderMount(m_nModelId,m_pPlayerAnim,m_fRotateZ,rc);
}

void CUI_ID_FRAME_SuAnimalMaterialUp::RenderMount(int nMountId, CPlayerAnim* pAnim, float fRotateZ, const RECT& rt)
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return ;
	if( nMountId < 0 )
		return;

	MeCamera camera;
	D3DVIEWPORT9 viewPort;
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	IRenderer* r = GetEngine()->GetRenderer();

	viewPort.X = rt.left;
	viewPort.Y = rt.top;
	viewPort.Width = rt.right - rt.left;
	viewPort.Height = rt.bottom - rt.top;
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;

	r->SetViewport( &viewPort );
	r->BeginScene();
	r->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );

	RECT rcDst = 
	{
		viewPort.X, viewPort.Y, viewPort.X+viewPort.Width, viewPort.Y + viewPort.Height
	};

	RECT rcSrc =
	{
		0, 0, viewPort.Width, viewPort.Height
	};

	GetDrawer()->FillRect2D(rcDst, 0);

	FLOAT fAspect = ((FLOAT)viewPort.Width) / (float)viewPort.Height;
	camera.SetProjParams( D3DX_PI/180*45.0f, fAspect, 1.0f, 12000.0f );

	D3DXMATRIX matView;
	D3DXMATRIX matWorld, matOldWorld;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMATRIX matTransform1;

	static float x = 0.f, y = -18.f, z = -1.8f;
	DWORD dwTime = HQ_TimeGetTime();
	if( pAnim )
	{
		pAnim->SetScale(Config::m_fMdlSpaceScale * 2.f);
		pAnim->SetPosition( x, y, z );
		pAnim->CalcTransformMatrix( (MeMatrix*)&matTransform1 );
		pAnim->Update( dwTime, (MeMatrix*)&matTransform1 );
		pAnim->UpdateComponents( dwTime, (MeMatrix*)&matTransform1 );
	}

	static float fDist = 22.79;
	static float fRotate = 0.0f;
	static float fRotateX = 0.98199f;
	static D3DXVECTOR3 vEyePt( 0,-1.2f,1.7f );
	static D3DXVECTOR3 vLookatPt( 0.0f,0.0f,0.0f );

	D3DXVECTOR3 vDist = vEyePt-vLookatPt;
	D3DXVec3Normalize( &vDist, &vDist );

	D3DXVECTOR3 vXAxis( 1, 0, 0 );
	D3DXMATRIX matRotX;
	D3DXMatrixRotationAxis(
		&matRotX,
		&vXAxis,
		fRotateX );

	D3DXVec3TransformCoord( &vDist, &vDist, &matRotX );

	D3DXVECTOR3 vZAxis( 0, 0, -1 );
	D3DXMATRIX matRotZ;
	D3DXMatrixRotationAxis(
		&matRotZ,
		&vZAxis,
		fRotate );

	D3DXVec3TransformCoord( &vDist, &vDist, &matRotZ );

	D3DXVECTOR3 vPos( 0, 0, 0 );
	camera.SetViewParams( vPos+vDist*fDist, vPos, D3DXVECTOR3( 0, 0, 1 ) );
	r->SetTransform( D3DTS_VIEW, (FLOAT*)&camera.GetViewMatrix() );
	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&camera.GetProjMatrix() );
	r->SetEyePt( (float*)&vEyePt );	
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
	r->SetRenderState( D3DRS_LIGHTING, TRUE );	
	r->SetRenderState( D3DRS_FOGENABLE , false );	

	bool bUseShader = graphics::ShaderManager::instance()->isUseShader();

	RendererDx* pRendererDx = (RendererDx*)r;
	D3DXVECTOR3 vOldLightDir = pRendererDx->GetLightDir( LIGHT_INDEX_TERRAIN );
	D3DXVECTOR3 vNewLightDir = vOldLightDir;	
	vNewLightDir = vDist;
	D3DXVec3Normalize( &vNewLightDir, &vNewLightDir );
	D3DLIGHT9 kOldLight = SwGlobal::GetRender()->GetD9Light();
	D3DLIGHT9 kLight;
	kLight.Type = D3DLIGHT_DIRECTIONAL;	
	kLight.Ambient = D3DXCOLOR( 0.6f, 0.6f, 0.6f, 1.0f );
	kLight.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	kLight.Specular = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	kLight.Direction = vNewLightDir;	
	pRendererDx->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kLight );
	Config::SetCamera(&camera);

	pAnim->SetRotationZ( fRotateZ );
	pAnim->SetUpperRot( fRotateZ );

	pAnim->Render( 1.0f );
	GetEngine()->GetRenderer()->Flush( eSortByFarZ );
	MeRenderManager::Instance()->DoRender(false);

	Config::SetCamera(getwsCamera()->GetMeCamera());
	pRendererDx->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kOldLight );

	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&getwsCamera()->GetMeCamera()->GetProjMatrix()  );
	r->SetTransform( D3DTS_VIEW, (FLOAT*)&getwsCamera()->GetMeCamera()->GetViewMatrix()  );
	r->EndScene();

	getwsCamera()->ResetViewport();
}

bool  CUI_ID_FRAME_SuAnimalMaterialUp::IsTypeMatch(ControlIconDrag::S_ListImg* pItemDrag)
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return false;
	if (pItemDrag == NULL )   return false;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon != NULL)
	{
		ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore*)pItemCommon;
		if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE && pRestore != NULL && 
			pRestore->specialFunction == ItemDefine::EPetFunc_AddSavvy)
		return true;
	}
	return false;
}

void CUI_ID_FRAME_SuAnimalMaterialUp::RefreshItemInfo()
{
	if ( !m_pID_FRAME_PetMaterialUp )
		return ;
	PetSelectChange( m_pID_LIST_PetName->GetCurSelIndex() );
	m_pID_FRAME_PetMaterialUp->SetRedraw();
}

void CUI_ID_FRAME_SuAnimalMaterialUp::RefreshMoney()
{
	if (!m_pID_FRAME_PetMaterialUp)   return ;
	std::string text;
	text.clear();
	if (m_pID_TEXT_LockedMoney)
	{
		thePlayerRole.GetGSCStringFromCurrentMoney(text);
		*m_pID_TEXT_LockedMoney = text;
	}
	if (m_pID_TEXT_CurrentMoney)
	{
		thePlayerRole.GetGSCStringFromCurrentJiaoZi(text);
		*m_pID_TEXT_CurrentMoney = text;
	}
}

bool CUI_ID_FRAME_SuAnimalMaterialUp::UIPetMaterialUp_LeftLBD(INT x,INT y)
{
	s_CUI_ID_FRAME_SuAnimalMaterialUp.SetRotate(true);
	return true;
}
bool CUI_ID_FRAME_SuAnimalMaterialUp::UIPetMaterialUp_RightLBD(INT nX,INT nY)
{
	s_CUI_ID_FRAME_SuAnimalMaterialUp.SetRotate(true);
	return true;
}

bool CUI_ID_FRAME_SuAnimalMaterialUp::RefreshProperty()
{
	if (!m_pID_FRAME_PetMaterialUp)   return false;
	//RefreshItemInfo();
	//m_pID_LISTIMG_PetStudySkill->Clear();
	return true;
}

void CUI_ID_FRAME_SuAnimalMaterialUp::RefreshPetList()
{
	int nSelId = m_pID_LIST_PetName->GetCurSelIndex();
	m_pID_LIST_PetName->Clear();

	int nMaxCount = thePetSettingConfig.GetPlayerPetLimit(thePlayerRole.GetLevel());
	for (int i = 0; i < nMaxCount; ++i)
	{
		if (thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId != InvalidLogicNumber)
		{
			ControlList::S_List sData;
			DWORD dwColor = S_IconInfoHero::GetPetShowColor( &thePlayerRole.m_charinfo.ItemBagData.petItems[i]);
			SPetItem &mount = thePlayerRole.GetPetByIndex(nSelId);
			if ((&mount) != NULL && mount.baseInfo.guid == thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.guid)
			{
				dwColor = S_IconInfoHero::GetPetShowColor(NULL);
			}
			sData.SetData( thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.szName, 
				thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId, 
				0, 
				dwColor );
			m_pID_LIST_PetName->AddItem(&sData,NULL, false);
		}
	}
	m_pID_LIST_PetName->SetCurSelIndex(nSelId);
}
bool CUI_ID_FRAME_SuAnimalMaterialUp::AutoAddMaterial(SPetItem &mount)
{
	if (mount.baseInfo.petId != InvalidLogicNumber)
	{
 		ControlListImage *pBag = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
 		if (pBag != NULL)
 		{
		m_MatchMaterialArray.clear();
// 			for (int index = 0; index<pBag->GetItemCnt(); ++index)
// 			{
// 				ControlIconDrag::S_ListImg *pListImg = pBag->GetItemByIndex(index);
// 				if (!pListImg || pListImg->IsNull() || NULL == pListImg->m_pkIconInfo)
// 				{
// 					continue;
// 				}
// 				ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pListImg->m_pkIconInfo->GetItemId() );
// 				ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore*)pItemCommon;
// 				if (pItemCommon != NULL && pRestore != NULL && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE 
// 					&&pRestore->specialFunction == ItemDefine::EPetFunc_AddSavvy )
// 				{
// 					if (mount.baseInfo.savvy < pRestore->petSavvy && (pRestore->petSavvy -mount.baseInfo.savvy)<=3 ) //??????????????????????????
// 					{
// 						m_pID_LISTIMG_PetStudySkill->SetItem(pListImg, 0 );
// 						SCharItem* psItem = (SCharItem*)pListImg->m_pkIconInfo->GetData();
// 						if (psItem != NULL)
// 						{
// 							item_info.nOnlyInt = psItem->itembaseinfo.nOnlyInt;
// 							item_info.ustItemID = psItem->itembaseinfo.ustItemID;
// 							item_info.n_index   = index;
// 						}
// 						 CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, index, true );
// 						return true;
// 					}
// 				}
// 			}
// 		}
 		const std::vector<ItemDefine::SItemCommon*>& m_RestoreIte= GettheItemDetail().GetRestoreItemList();
 		for(int index = 0; index < m_RestoreIte.size(); index ++)
 		{
 			 ItemDefine::SItemRestore* pMaterial = ( ItemDefine::SItemRestore* )m_RestoreIte[index];
 			 if (pMaterial != NULL && pMaterial->specialFunction ==ItemDefine::EPetFunc_AddSavvy &&
 				 m_RestoreIte[index] != NULL && m_RestoreIte[index]->byUserTarget == ItemDefine::eTargetPet  )
 			 {
 				 m_MatchMaterialArray.push_back(pMaterial->ustItemID);
 			 }
 		}
		m_pID_LISTIMG_PetStudySkill->Clear();
		ControlIconDrag::S_ListImg *pListImg = NULL;
		for (int i= 0; i<m_MatchMaterialArray.size(); i++)
		{
			pListImg= pBag->GetItemById(m_MatchMaterialArray[i]);
			if (!pListImg || pListImg->IsNull() || NULL == pListImg->m_pkIconInfo)
			{
				continue;
			}
			else
			{//????????????????????????
				ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(m_MatchMaterialArray[i]);
				ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore*)pItemCommon;
				if (mount.baseInfo.savvy <= pRestore->petSavvy && (pRestore->petSavvy -mount.baseInfo.savvy)<3 ) //??????????????????????????
				{
					ControlIconDrag::S_ListImg pListImgNew;
					pListImgNew.SetData(m_MatchMaterialArray[i],1);
					m_pID_LISTIMG_PetStudySkill->SetItem(&pListImgNew, 0 );
					SCharItem* psItem = (SCharItem*)pListImg->m_pkIconInfo->GetData();
					if (psItem != NULL)
					{
						item_info.nOnlyInt = psItem->itembaseinfo.nOnlyInt;
						item_info.ustItemID = psItem->itembaseinfo.ustItemID; 
						item_info.n_index   = pBag->GetItemIndex(pListImg);
						 return true;
					}
					
				}
			}
		}
		}
		//??????????????????
		for (int i=0; i<m_MatchMaterialArray.size(); i++)
		{
			ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(m_MatchMaterialArray[i]);
			ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore*)pItemCommon;
			if (mount.baseInfo.savvy <= pRestore->petSavvy && (pRestore->petSavvy -mount.baseInfo.savvy)<3 ) //??????????????????????????
			{
				ControlIconDrag::S_ListImg ImgItem;
				ImgItem.SetData(m_MatchMaterialArray[i],1,eIcon_Disable);
				m_pID_LISTIMG_PetStudySkill->SetItem( &ImgItem,0);
				return false;
			}
		}
		
		
	}
	return false;
}