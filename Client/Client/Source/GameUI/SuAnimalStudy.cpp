/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\宠物\PetStudy.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimalStudy.h"
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
CUI_ID_FRAME_SuAnimalStudy s_CUI_ID_FRAME_SuAnimalStudy;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimalStudy, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimalStudy, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_BUTTON_YESONButtonClick );
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_BUTTON_CANCELOnButtonClick );
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_BUTTON_ToLeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_BUTTON_ToRightOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_LISTIMG_PetSkillOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_LISTIMG_PetSkillOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_LISTIMG_PetSkillOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_LISTIMG_PetSkillOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_LISTIMG_PetStudySkillOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_LISTIMG_PetStudySkillOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_LISTIMG_PetStudySkillOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_LISTIMG_PetStudySkillOnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_LIST_PetNameOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_BUTTON_ChoiceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalStudy, ID_BUTTON_ExamineOnButtonClick )
CUI_ID_FRAME_SuAnimalStudy::CUI_ID_FRAME_SuAnimalStudy()
{
	// Member
	m_pID_FRAME_PetStudy = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TitleTop = NULL;
	m_pID_PICTURE_PetModel = NULL;
	m_pID_BUTTON_ToLeft = NULL;
	m_pID_BUTTON_ToRight = NULL;
	m_pID_LISTIMG_PetSkill = NULL;
	m_pID_TEXT_PetLv = NULL;
	m_pID_LISTIMG_PetStudySkill = NULL;
	m_pID_PICTURE_Motherboard = NULL;
	m_pID_TEXT_PetNameTitle = NULL;
	m_pID_LIST_PetName = NULL;
	//m_pID_BUTTON_Choice = NULL;
	m_pID_BUTTON_Examine = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_TEXT_ConsumeMoney = NULL;
	m_pID_TEXT_LockedMoney = NULL;
	m_pID_TEXT_CurrentMoney = NULL;
	m_pID_BUTTON_YES= NULL;
	m_pID_BUTTON_CANCEL = NULL;
		m_pPlayer = 0;
}
// Frame
bool CUI_ID_FRAME_SuAnimalStudy::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	int nSroollBarHeight = 0;
	if (s_CUI_ID_FRAME_SuAnimalStudy.IsVisable())
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
bool CUI_ID_FRAME_SuAnimalStudy::OnFrameRender()
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
bool CUI_ID_FRAME_SuAnimalStudy::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalStudy::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalStudy::ID_BUTTON_ToLeftOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
		m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalStudy::ID_BUTTON_ToRightOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
		m_bRotate = false;
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalStudy::ID_LISTIMG_PetSkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalStudy::ID_LISTIMG_PetSkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalStudy::ID_LISTIMG_PetSkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalStudy::ID_LISTIMG_PetSkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalStudy::ID_LISTIMG_PetStudySkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return DragItemOn(0,pItemDrag,pSender);
}
bool CUI_ID_FRAME_SuAnimalStudy::ID_LISTIMG_PetStudySkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalStudy::ID_LISTIMG_PetStudySkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalStudy::ID_LISTIMG_PetStudySkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return false;
}
// List
void CUI_ID_FRAME_SuAnimalStudy::ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_PetStudy )
	m_fRotateZ = 0.0f;
	PetSelectChange(m_pID_LIST_PetName->GetCurSelIndex());
	RefreshPetList();
	return;
}
// Button
bool CUI_ID_FRAME_SuAnimalStudy::ID_BUTTON_ChoiceOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;

	return true;//ReadyOk();
}
// Button
bool CUI_ID_FRAME_SuAnimalStudy::ID_BUTTON_ExamineOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	int n_index = m_pID_LIST_PetName->GetCurSelIndex();
	s_CUI_ID_FRAME_SuAnimal.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimal.LookPet(n_index);

	return true;
}

// 装载UI
bool CUI_ID_FRAME_SuAnimalStudy::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimalStudy.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuAnimalStudy.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuAnimalStudy::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PetStudy, s_CUI_ID_FRAME_SuAnimalStudyOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PetStudy, s_CUI_ID_FRAME_SuAnimalStudyOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PetStudy, ID_BUTTON_HELP, s_CUI_ID_FRAME_SuAnimalStudyID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetStudy, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SuAnimalStudyID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetStudy, ID_BUTTON_ToLeft, s_CUI_ID_FRAME_SuAnimalStudyID_BUTTON_ToLeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetStudy, ID_BUTTON_ToRight, s_CUI_ID_FRAME_SuAnimalStudyID_BUTTON_ToRightOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_PetStudy, ID_LISTIMG_PetSkill, s_CUI_ID_FRAME_SuAnimalStudyID_LISTIMG_PetSkillOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetStudy, ID_LISTIMG_PetSkill, s_CUI_ID_FRAME_SuAnimalStudyID_LISTIMG_PetSkillOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetStudy, ID_LISTIMG_PetSkill, s_CUI_ID_FRAME_SuAnimalStudyID_LISTIMG_PetSkillOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetStudy, ID_LISTIMG_PetSkill, s_CUI_ID_FRAME_SuAnimalStudyID_LISTIMG_PetSkillOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_PetStudy, ID_LISTIMG_PetStudySkill, s_CUI_ID_FRAME_SuAnimalStudyID_LISTIMG_PetStudySkillOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetStudy, ID_LISTIMG_PetStudySkill, s_CUI_ID_FRAME_SuAnimalStudyID_LISTIMG_PetStudySkillOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetStudy, ID_LISTIMG_PetStudySkill, s_CUI_ID_FRAME_SuAnimalStudyID_LISTIMG_PetStudySkillOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetStudy, ID_LISTIMG_PetStudySkill, s_CUI_ID_FRAME_SuAnimalStudyID_LISTIMG_PetStudySkillOnIconRButtonUp );
	theUiManager.OnListSelectChange( ID_FRAME_PetStudy, ID_LIST_PetName, s_CUI_ID_FRAME_SuAnimalStudyID_LIST_PetNameOnListSelectChange );
	//theUiManager.OnButtonClick( ID_FRAME_PetStudy, ID_BUTTON_Choice, s_CUI_ID_FRAME_SuAnimalStudyID_BUTTON_ChoiceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetStudy, ID_BUTTON_Examine, s_CUI_ID_FRAME_SuAnimalStudyID_BUTTON_ExamineOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetStudy,ID_BUTTON_Yes,s_CUI_ID_FRAME_SuAnimalStudyID_BUTTON_YESONButtonClick);
	theUiManager.OnButtonClick( ID_FRAME_PetStudy,ID_BUTTON_CANCEL,s_CUI_ID_FRAME_SuAnimalStudyID_BUTTON_CANCELOnButtonClick);

	m_pID_FRAME_PetStudy = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetStudy );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_BUTTON_CLOSE );
	m_pID_TEXT_TitleTop = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_TEXT_TitleTop );
	m_pID_PICTURE_PetModel = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_PICTURE_PetModel );
	m_pID_BUTTON_ToLeft = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_BUTTON_ToLeft );
	m_pID_BUTTON_ToRight = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_BUTTON_ToRight );
	m_pID_LISTIMG_PetSkill = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_LISTIMG_PetSkill );
	m_pID_TEXT_PetLv = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_TEXT_PetLv );
	m_pID_LISTIMG_PetStudySkill = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_LISTIMG_PetStudySkill );
	m_pID_PICTURE_Motherboard = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_PICTURE_Motherboard );
	m_pID_TEXT_PetNameTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_TEXT_PetNameTitle );
	m_pID_LIST_PetName = (ControlList*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_LIST_PetName );
	//m_pID_BUTTON_Choice = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_BUTTON_Choice );
	m_pID_BUTTON_Examine = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_BUTTON_Examine );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_TEXT_Explain );
	m_pID_TEXT_ConsumeMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_TEXT_ConsumeMoney );
	m_pID_TEXT_LockedMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_TEXT_LockedMoney );
	m_pID_TEXT_CurrentMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_TEXT_CurrentMoney );
	m_pID_BUTTON_YES = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_BUTTON_Yes );
	m_pID_BUTTON_CANCEL = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetStudy, ID_BUTTON_CANCEL);
	assert( m_pID_FRAME_PetStudy );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_TitleTop );
	assert( m_pID_PICTURE_PetModel );
	assert( m_pID_BUTTON_ToLeft );
	assert( m_pID_BUTTON_ToRight );
	assert( m_pID_LISTIMG_PetSkill );
	assert( m_pID_TEXT_PetLv );
	assert( m_pID_LISTIMG_PetStudySkill );
	assert( m_pID_PICTURE_Motherboard );
	assert( m_pID_TEXT_PetNameTitle );
	assert( m_pID_LIST_PetName );
	//assert( m_pID_BUTTON_Choice );
	assert( m_pID_BUTTON_Examine );
	assert( m_pID_TEXT_Explain );
	assert( m_pID_TEXT_ConsumeMoney );
	assert( m_pID_TEXT_LockedMoney );
	assert( m_pID_TEXT_CurrentMoney );

	m_pID_LISTIMG_PetSkill->SetDisableCanbePick(true);
	m_pID_LISTIMG_PetSkill->ShowPressEffect(true);

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
// 卸载UI
bool CUI_ID_FRAME_SuAnimalStudy::_UnLoadUI()
{
	m_pID_FRAME_PetStudy = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TitleTop = NULL;
	m_pID_PICTURE_PetModel = NULL;
	m_pID_BUTTON_ToLeft = NULL;
	m_pID_BUTTON_ToRight = NULL;
	m_pID_LISTIMG_PetSkill = NULL;
	m_pID_TEXT_PetLv = NULL;
	m_pID_LISTIMG_PetStudySkill = NULL;
	m_pID_PICTURE_Motherboard = NULL;
	m_pID_TEXT_PetNameTitle = NULL;
	m_pID_LIST_PetName = NULL;
	//m_pID_BUTTON_Choice = NULL;
	m_pID_BUTTON_Examine = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_TEXT_ConsumeMoney = NULL;
	m_pID_TEXT_LockedMoney = NULL;
	m_pID_TEXT_CurrentMoney = NULL;

	if (m_pPlayer)
	{
		theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer( m_pPlayer );
		m_pPlayer->Destroy();	
		delete m_pPlayer;
		m_pPlayer = 0;
		m_pPlayerAnim = 0;
	}
	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimalStudy.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SuAnimalStudy::_IsVisable()
{
	if ( !m_pID_FRAME_PetStudy )
		return false;
	return m_pID_FRAME_PetStudy->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SuAnimalStudy::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_PetStudy )
		return ;
	m_pID_FRAME_PetStudy->SetVisable( bVisable );
	m_fRotateZ = 0.0f;
	m_nModelId = -1;
	if (bVisable)
	{
		Refresh(false);
		PlaySoundConfig(SoundConfig::EST_OpenPackUI);
	}
}

void CUI_ID_FRAME_SuAnimalStudy::RefreshMoney()
{
	if (!m_pID_FRAME_PetStudy)   return ;
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
	ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_PetStudySkill->GetItemByIndex(0);
	if (pListImg == NULL)  return ;

	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)      return ;
	ItemDefine::SItemReel* pReel = (ItemDefine::SItemReel*)GettheItemDetail().GetItemByID( pItem->GetItemID() );
	if (pReel != NULL)
	{
		int money = pReel->costMoney;
		std::string text;
		text.clear();
		thePlayerRole.GetGSCStringFromMoney(money,text);
		//*m_pID_TEXT_ConsumeMoney = text;
		m_pID_TEXT_PetLv->SetText(pReel->petLevel);
		if (thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) < (DWORD)money)
		{
			m_pID_TEXT_ConsumeMoney->SetText(text.c_str(),0xffff0000);
			m_pID_BUTTON_YES->SetEnable(false);
		}
		else
		{
			*m_pID_TEXT_ConsumeMoney = text;
			m_pID_BUTTON_YES->SetEnable(true);
		}
	}			
}

void CUI_ID_FRAME_SuAnimalStudy::RefreshByMoneyChange()
{
	RefreshMoney();
}
void CUI_ID_FRAME_SuAnimalStudy::Refresh_Help(bool _is)
{
	if (!IsVisable())
		return;

	int nSelId = m_pID_LIST_PetName->GetCurSelIndex();
	RefreshMoney();
	m_pID_LIST_PetName->Clear();

	int nMaxCount = thePetSettingConfig.GetPlayerPetLimit(thePlayerRole.GetLevel());

	for (int i = 0; i < nMaxCount; ++i)
	{
		if (thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId != InvalidLogicNumber)
		{
			ControlList::S_List sData;

			// 取颜色
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
		}
	}
	if (_is)
		m_pID_LIST_PetName->SetCurSelIndex(m_pID_LIST_PetName->GetListItemCnt() - 1);
	else if (nSelId == -1)
		m_pID_LIST_PetName->SetCurSelIndex(0);
	else
		m_pID_LIST_PetName->SetCurSelIndex(nSelId);
		RefreshItemInfo();
}

bool CUI_ID_FRAME_SuAnimalStudy::UIPetMaterialUp_LeftLBD(INT x,INT y)
{
	s_CUI_ID_FRAME_SuAnimalStudy.SetRotate(true);
	return true;
}
bool CUI_ID_FRAME_SuAnimalStudy::UIPetMaterialUp_RightLBD(INT nX,INT nY)
{
	s_CUI_ID_FRAME_SuAnimalStudy.SetRotate(true);
	return true;
}

void CUI_ID_FRAME_SuAnimalStudy::RenderViewport()
{
	RECT rc;
	m_pID_PICTURE_PetModel->GetRealRect(&rc);
	RenderMount(m_nModelId,m_pPlayerAnim,m_fRotateZ,rc);
}

void CUI_ID_FRAME_SuAnimalStudy::RenderMount(int nMountId, CPlayerAnim *pAnim, float fRotateZ, const RECT &rt)
{
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

void CUI_ID_FRAME_SuAnimalStudy::ChangeModel(SPetItem &mount, CPlayerAnim *pAnim, int &iOldModelId)
{
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

bool  CUI_ID_FRAME_SuAnimalStudy::DragItemOn(int index, ControlIconDrag::S_ListImg *pItemDrag, ControlObject *pSender)
{
	ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_PetStudySkill->GetItemByIndex(0);
	if (pListImg == NULL)  return false;

	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)      return false;
	

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_REEL  ) )
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;
		ItemDefine::SItemReel* pReel = (ItemDefine::SItemReel*)pItemCommon;
		if (pReel != NULL && pReel->byUserTarget == ItemDefine::eTargetMount)
		{
			const SCharSkill* pSkill = thePlayerRole.GetPetByIndex(GetCurrentMountIndex()).skillInfo.GetSkill(pReel->skillId);
			if (pSkill != NULL && pSkill->stSkillLevel >= pReel->skillLevel)
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_MountAlreadyLearnSkill ) );
				return false;
			}
			m_pID_TEXT_PetLv->SetText(pReel->petLevel);
		}
		// 包裹里
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

			ControlIconDrag::S_ListImg liGem;
			liGem.SetData( pItemDrag->m_pkIconInfo->GetItemId(),1,eIcon_Enable );
			m_pID_LISTIMG_PetStudySkill->SetItem( &liGem, 0 );
			if (pReel != NULL)
			{
				int money = pReel->costMoney;
				std::string text;
				text.clear();
				thePlayerRole.GetGSCStringFromMoney(money,text);
				if (thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) < (DWORD)money)
				{
					m_pID_TEXT_ConsumeMoney->SetText(text.c_str(),0xffff0000);
					m_pID_BUTTON_YES->SetEnable(false);
				}
				else
				{
					*m_pID_TEXT_ConsumeMoney = text;
					m_pID_BUTTON_YES->SetEnable(true);
				}
	 			//*m_pID_TEXT_ConsumeMoney = text;
				m_pID_TEXT_PetLv->SetText(pReel->petLevel);
			}			
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool  CUI_ID_FRAME_SuAnimalStudy::IsTypeMatch(ControlIconDrag::S_ListImg *pItemDrag)
{
	if (pItemDrag == NULL )   return false;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon != NULL)
	{
		if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_REEL )
			return true;
	}
	return false;
}

bool CUI_ID_FRAME_SuAnimalStudy::RefreshMountSkill(SPetItem &mount)
{
	CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
		GetPage(CUISkillMgr::ePetSkill);
	if (!pSkillTree)
		return false;
	m_pID_LISTIMG_PetSkill->Clear();
	SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

	for ( int i = 0; i < SPetItem::PetDefine_MaxSkillCount; ++i)
	{
		unsigned short usSkillId = mount.skillInfo.skills[i].ustSkillID;
		if ( usSkillId == 0)
			continue;
		unsigned short usLevel = mount.skillInfo.skills[i].stSkillLevel;
		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(usSkillId,usLevel);
		if (!pItemSkill)
			continue;
		//const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue(usSkillId);
		//if (!pIcon)
		//	continue;

		ControlIconDrag::S_ListImg stItem;
		//stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
		stItem.SetData( usSkillId, usLevel, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
		stItem.SetFlags(CUISkillMgr::ePetSkill);

		SkillBag::SColdTime *pTime = NULL;
		pTime = thePlayerRole.m_PetSkillBag.GetColdTimeById( usSkillId );
		if ( pTime )
		{
			stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
		}

		m_pID_LISTIMG_PetSkill->SetItem(&stItem);
	}
	return true;
}

void CUI_ID_FRAME_SuAnimalStudy::PetSelectChange(int nindex)
{
	m_pID_LISTIMG_PetSkill->Clear();
	m_pID_LISTIMG_PetStudySkill->Clear();
	RefreshMoney();
	if (nindex <0 )  return ;
	SPetItem &mount = thePlayerRole.GetPetByIndex(nindex);
	if (mount.baseInfo.petId != InvalidLogicNumber)
	{
		RefreshMountSkill(mount);
		ChangeModel(mount,m_pPlayerAnim,m_nModelId);
	}
}

bool CUI_ID_FRAME_SuAnimalStudy::IsSkillList(const ControlObject *pObject)
{
	if (m_pID_FRAME_PetStudy != NULL)
	{
		return m_pID_LISTIMG_PetSkill == pObject ;
	}
	return false;	
}

bool CUI_ID_FRAME_SuAnimalStudy::ReadyOk()
{
	if (item_info.ustItemID ==InvalidLogicNumber ) 
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetNoneItem) );
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_ListInfo_RandomTip,theXmlString.GetString(eText_PetNoneItem));
		return false;
	}
		
	ItemDefine::SItemCommon * pItemCommon = GettheItemDetail().GetItemByID(item_info.ustItemID);

	if( pItemCommon != NULL)
	{
		if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_REEL  )
		{
			
			ItemDefine::SItemReel* pReel = (ItemDefine::SItemReel*)pItemCommon;
			if (pReel != NULL && pReel->petLevel > GetSelectPet().baseInfo.level)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetLevelSkill) );
				CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_ListInfo_RandomTip,theXmlString.GetString(eText_PetLevelSkill));
				return false;
			}
			//lyh 添加 是否重复学习技能的拦截
			else
			{

				if (pReel != NULL)
				{
					for(int i = 0 ; i < SPetItem::PetDefine_MaxSkillCount ; i++)
					{
						if (GetSelectPet().skillInfo.skills[i].ustSkillID == pReel->skillId)
						{
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_HasPetSkill) );
							item_info.n_index = item_info.nOnlyInt = item_info.ustItemID = InvalidLogicNumber;
							return false;
						}
					}
				}

				//lyh++ 出战的宠物不能进行技能学习
if (GetSelectPet().baseInfo.isActive)
{
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_ActivePetContStudySill) );
	return false;
}

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
					item_info.n_index = item_info.nOnlyInt = item_info.ustItemID = InvalidLogicNumber;
					return true;
				}
			}
		}
	}
	return false;
}

short CUI_ID_FRAME_SuAnimalStudy::GetCurrentMountIndex()
{
	if (m_pID_FRAME_PetStudy == NULL)  return -1;  
	return m_pID_LIST_PetName->GetCurSelIndex();	
}

void CUI_ID_FRAME_SuAnimalStudy::RefreshItemInfo()
{
	PetSelectChange( m_pID_LIST_PetName->GetCurSelIndex() );
	m_pID_FRAME_PetStudy->SetRedraw();
}

bool CUI_ID_FRAME_SuAnimalStudy::ID_BUTTON_YESONButtonClick(ControlObject *pSender)
{
	if (m_pID_FRAME_PetStudy == NULL)  return false;
	m_pID_LISTIMG_PetStudySkill->Clear();
	return ReadyOk();
}
bool CUI_ID_FRAME_SuAnimalStudy::ID_BUTTON_CANCELOnButtonClick(ControlObject *pSender)
{
	if (m_pID_FRAME_PetStudy == NULL) return false;
	m_pID_FRAME_PetStudy->SetVisable(false);
	return true;
}

SPetItem& CUI_ID_FRAME_SuAnimalStudy::GetSelectPet()
{
	int nIndex( ITEM_MOUNT_MAXCOUNT );
	if( IsUILoad() )
		nIndex = m_pID_LIST_PetName->GetCurSelIndex();

	return thePlayerRole.GetPetByIndex(nIndex);
	
}

void CUI_ID_FRAME_SuAnimalStudy::RefreshPetList()
{
	int nSelId = m_pID_LIST_PetName->GetCurSelIndex();
	m_pID_LIST_PetName->Clear();

	int nMaxCount = thePetSettingConfig.GetPlayerPetLimit(thePlayerRole.GetLevel());
	for (int i = 0; i < nMaxCount; ++i)
	{
		if (thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId != InvalidLogicNumber)
		{
			ControlList::S_List sData;
			SPetItem m_PetItem = thePlayerRole.GetCharInfo2().ItemBagData.petItems[i];
			DWORD dwColor = 0;
			if (!m_PetItem.baseInfo.isActive)
			{
				dwColor = Color_Config.getColor(CC_PetColor_White);//白色
			}
			else if (m_PetItem.baseInfo.isActive)
			{
				dwColor =Color_Config.getColor(CC_PetColor_Red); //红色
			}
			SPetItem &mount = thePlayerRole.GetPetByIndex(nSelId);
			if ((&mount) != NULL && mount.baseInfo.guid == m_PetItem.baseInfo.guid)
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