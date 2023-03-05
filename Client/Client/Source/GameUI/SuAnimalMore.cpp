#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimalMore.h"
#include "PlayerRole.h"
#include "IconManagerClient.h"
#include "XmlStringLanguage.h"
#include "GameDefinePlayer.h"
#include "Skill.h"
#include "NetworkInput.h"
#include "ScreenInfoManager.h"
#include "SuAnimal.h"
#include "player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "SeeSuAnimal.h"
#include "PetSettingConfig.h"
#include "color_config.h"
#include "ItemDetail.h"

CUI_ID_FRAME_SuAnimalMore s_CUI_ID_FRAME_SuAnimalMore;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimalMore, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimalMore, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_HELPOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill2OnIconRButtonUp )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_COMBOBOX_SelectPet1OnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_COMBOBOX_SelectPet2OnComboBoxChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_LIST_PetOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_ChangePetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_LookPetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_LookPartnerPetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_LockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_Right1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_Right2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_Left1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_Left2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMore, ID_BUTTON_UnchainLockOnButtonClick )
CUI_ID_FRAME_SuAnimalMore::CUI_ID_FRAME_SuAnimalMore()
{
	// Member
	m_pID_FRAME_SuAnimalMore = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_PICTURE_Pet1 = NULL;
	m_pID_PICTURE_Pet2 = NULL;
	m_pID_TEXT_Result1 = NULL;
	m_pID_TEXT_Level1 = NULL;
	m_pID_TEXT_Level2 = NULL;
	m_pID_TEXT_Generation1 = NULL;
	m_pID_TEXT_Generation2 = NULL;
	m_pID_TEXT_Result2 = NULL;
	m_pID_TEXT_StrengthZ = NULL;
	m_pID_TEXT_AgilityZ = NULL;
	m_pID_TEXT_StaminaZ = NULL;
	m_pID_TEXT_IntellectZ = NULL;
	m_pID_TEXT_Strength = NULL;
	m_pID_TEXT_Agility = NULL;
	m_pID_TEXT_Stamina = NULL;
	m_pID_TEXT_Intellect = NULL;
	m_pID_TEXT_NeedMoney = NULL;
	m_pID_TEXT_CurrentMoney = NULL;
	m_pID_LISTIMG_Skill1 = NULL;
	m_pID_LISTIMG_Skill2 = NULL;
	m_pID_COMBOBOX_SelectPet1 = NULL;
	m_pID_COMBOBOX_SelectPet2 = NULL;
	m_pID_LIST_Pet = NULL;
	m_pID_TEXT_PartnerPetName = NULL;
	m_pID_TEXT_MyPetName = NULL;
	m_pID_TEXT_Info1 = NULL;
	m_pID_BUTTON_ChangePet = NULL;
	m_pID_BUTTON_LookPet = NULL;
	m_pID_TEXT_Info2 = NULL;
	m_pID_BUTTON_LookPartnerPet = NULL;
	m_pID_BUTTON_Lock = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Right1 = NULL;
	m_pID_BUTTON_Right2 = NULL;
	m_pID_BUTTON_Left1 = NULL;
	m_pID_BUTTON_Left2 = NULL;
	m_pID_BUTTON_UnchainLock = NULL;

	m_nMountId1 = -1;
	m_nMountId2 = -1;

    m_pPlayer1 = NULL;
	m_pPlayerAnim1 = NULL;

	m_pPlayer2 = NULL;
	m_pPlayerAnim2 = NULL;
	m_pID_PICTURE_SD1= NULL;
	m_pID_PICTURE_SD2 = NULL;
}

// Frame
bool CUI_ID_FRAME_SuAnimalMore::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_SuAnimalMore::OnFrameRender()
{
	GetEngine()->GetRenderer()->EndScene();
	RenderViewport();
	GetEngine()->GetRenderer()->BeginScene();
	if(m_bTargetLock&&m_bMyLock)
		m_pID_BUTTON_OK->SetEnable(true);
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	CancelPetBreed();
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMore::ID_LISTIMG_Skill1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															  ControlIconDrag::S_ListImg* pItemDrag,
															  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMore::ID_LISTIMG_Skill1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMore::ID_LISTIMG_Skill1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMore::ID_LISTIMG_Skill1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalMore::ID_LISTIMG_Skill2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															  ControlIconDrag::S_ListImg* pItemDrag,
															  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMore::ID_LISTIMG_Skill2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMore::ID_LISTIMG_Skill2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_SuAnimalMore::ID_LISTIMG_Skill2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// ComboBox
void CUI_ID_FRAME_SuAnimalMore::ID_COMBOBOX_SelectPet1OnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_SuAnimalMore )
		return;

// 	int iSelId1 = m_pID_COMBOBOX_SelectPet1->GetListBox().GetCurSelIndex();
// 	int iSelId2 = m_pID_COMBOBOX_SelectPet2->GetListBox().GetCurSelIndex();
// 	if( iSelId2 > -1 && iSelId1 == iSelId2 )
// 	{
// 		m_pID_COMBOBOX_SelectPet1->GetListBox().SetCurSelIndex( -1 );
// 		m_pID_COMBOBOX_SelectPet1->GetEditInput().SetText( "" );
// 		m_nMountId1 = -1;
// 	}
// 	else if( iSelId1 > -1 && iSelId1 < thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount )
// 	{
// 		s_CUI_ID_FRAME_SuAnimal.ChangeModel( thePlayerRole.m_charinfo.ItemBagData.petItems[iSelId1], m_pAnim1, m_nMountId1 );
// 	}
// 
// 	Refresh();
}

// ComboBox
void CUI_ID_FRAME_SuAnimalMore::ID_COMBOBOX_SelectPet2OnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_SuAnimalMore )
		return;

// 	int iSelId1 = m_pID_COMBOBOX_SelectPet1->GetListBox().GetCurSelIndex();
// 	int iSelId2 = m_pID_COMBOBOX_SelectPet2->GetListBox().GetCurSelIndex();
// 	if( iSelId1 > -1 && iSelId1 == iSelId2 )
// 	{
// 		m_pID_COMBOBOX_SelectPet2->GetListBox().SetCurSelIndex( -1 );
// 		m_pID_COMBOBOX_SelectPet2->GetEditInput().SetText( "" );
// 		m_nMountId2 = -1;
// 	}
// 	else if( iSelId2 > -1 && iSelId2 < thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount )
// 	{
// 		s_CUI_ID_FRAME_SuAnimal.ChangeModel( thePlayerRole.m_charinfo.ItemBagData.petItems[iSelId2], m_pAnim2, m_nMountId2 );
// 	}
// 
// 	Refresh();
}

// List
void CUI_ID_FRAME_SuAnimalMore::ID_LIST_PetOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_ChangePetOnButtonClick( ControlObject* pSender )
{
	int nIndex = m_pID_LIST_Pet->GetCurSelIndex();
	if (m_bMyLock)//判读是否锁定了
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,theXmlString.GetString(eText_PetLockMySelf));
		return false;
	}
	
	SPetItem & mount = thePlayerRole.GetPetByIndex(nIndex);//得到选择中的副将的信息
	if (mount.baseInfo.petId != InvalidLogicNumber)//验证副将的ID是否为空
	{
		int breedMaxNum = thePetSettingConfig.GetPetBreedNum(mount.baseInfo.level);//获得副将繁殖的次数
		ItemDefine::SPetMonster* pCommon = GettheItemDetail().GetPetById(mount.baseInfo.petId );
		if (pCommon != NULL)
		{
			if (pCommon->bIsAberrance || !pCommon->bIsBaby)
			{//变异或者成年的不能够被繁殖
				CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,theXmlString.GetString(eText_PetCannotFanZhi));
				return false;
			}
			if (mount.baseInfo.generation >0)
			{//二代以上的不能够被选择
				CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,theXmlString.GetString(eText_PetGenerationNotCatch));
				return false;
			}
		}
		if(mount.baseInfo.breedNum >= breedMaxNum)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetBreedMaxNum) );
			return false;
		}
		//去掉副将快乐度相关的  by liaojie 11.21
		/*if (mount.baseInfo.loyalty < 100 )
		{
			ShowAllPet();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetLoyaltyLower) );
			return false;
		}*/
		if(mount.baseInfo.duration <1000)
		{
			ShowAllPet();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetDruationLower) );
			return false;
		}
		if (mount.baseInfo.isActive)
		{
			ShowAllPet();
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetActiveCannotFanZhi));
			return false;
		}
		
	}
	RefreshMoney();
	SendSelPetReg(nIndex);
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_LookPetOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_SuAnimal.SetVisable(true);
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_LookPartnerPetOnButtonClick( ControlObject* pSender )
{
	if(m_sTargetItem.baseInfo.petId != InvalidLogicNumber)
	{
		s_CUI_ID_FRAME_SeeSuAnimal.SetVisable(true);
		s_CUI_ID_FRAME_SeeSuAnimal.SetPetItem(m_sTargetItem);
	}
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_LockOnButtonClick( ControlObject* pSender )
{
	if (m_bTargetLock)
	{
		SPetItem &m_pet = thePlayerRole.GetPetByIndex(m_pID_LIST_Pet->GetCurSelIndex());
		if (m_sTargetItem.baseInfo.petId !=	InvalidLogicNumber && m_pet.baseInfo.petId !=InvalidLogicNumber)
		{
			char temp[64];
			if (m_sTargetItem.baseInfo.petType != m_pet.baseInfo.petType)
			{//类型不一样
				MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetTypeNotCatch),m_sTargetItem.baseInfo.szName);
				CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,temp);
				return false;
			}
			if (m_sTargetItem.baseInfo.sex == m_pet.baseInfo.sex)
			{//同性不能繁殖
				MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetSexNotCatch),
					(m_sTargetItem.baseInfo.sex== 0? theXmlString.GetString(eText_PetMale): theXmlString.GetString(eText_PetFemale)));
				CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,temp);
				return false;
			}
		}
	}
	RegLockPet();

	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SuAnimalMore )
		return false;
	if(thePlayerRole.GetMeTeamInfo() != NULL)
	{//在队伍中
		ConfirmPetBreed();
	}
	else
	{//不在队伍中
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,theXmlString.GetString(eText_PetNoInTeam));
		CancelPetBreed();
	}
	/*
	// 发送交配消息
	int nMountLimitCnt = thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount;
	int iSelId1 = m_pID_COMBOBOX_SelectPet1->GetListBox().GetCurSelIndex();
	int iSelId2 = m_pID_COMBOBOX_SelectPet2->GetListBox().GetCurSelIndex();
	if( iSelId1 < 0 || iSelId2 < 0 || iSelId1 > nMountLimitCnt || iSelId2 > nMountLimitCnt || iSelId1 == iSelId2 )
		return true;
	SMountItem mount1 = thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId1];
	SMountItem mount2 = thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId2];

	ItemDefine::SDrome* pDrome1 = ( ItemDefine::SDrome* )GettheItemDetail().GetItemByID( mount1.baseInfo.id );
	ItemDefine::SDrome* pDrome2 = ( ItemDefine::SDrome* )GettheItemDetail().GetItemByID( mount2.baseInfo.id );
	if( !pDrome1 || !pDrome2 )
		return true;
	if( pDrome1->stType != pDrome2->stType )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountType_CannotBreed ) );
		return true;
	}
	if( !mount1.IsCanBreed() || !mount2.IsCanBreed() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBreed_Unable ) );
		return true;
	}

	MsgMountBreed msg;
	msg.masterGuid = mount1.baseInfo.guid;
	msg.assistantGuid = mount2.baseInfo.guid;
	GettheNetworkInput().SendMsg( &msg );

	return true;
	*/
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
    CancelPetBreed();
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_Right1OnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_Right2OnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_Left1OnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_Left2OnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimalMore::ID_BUTTON_UnchainLockOnButtonClick( ControlObject* pSender )
{
// 	if (m_bTargetLock)
// 	{
// 		SPetItem &m_pet = thePlayerRole.GetPetByIndex(m_pID_LIST_Pet->GetCurSelIndex());
// 		if (m_sTargetItem.baseInfo.petId !=	InvalidLogicNumber && m_pet.baseInfo.petId !=InvalidLogicNumber)
// 		{
// 			char temp[64];
// 			if (m_sTargetItem.baseInfo.petType != m_pet.baseInfo.petType)
// 			{//类型不一样
// 				MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetTypeNotCatch),m_sTargetItem.baseInfo.szName);
// 				CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,temp);
// 				return false;
// 			}
// 			if (m_sTargetItem.baseInfo.sex == m_pet.baseInfo.sex)
// 			{//同性不能繁殖
// 				MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetSexNotCatch),
// 					(m_sTargetItem.baseInfo.sex== 0? theXmlString.GetString(eText_PetMale): theXmlString.GetString(eText_PetFemale)));
// 				CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,temp);
// 				return false;
// 			}
// 		}
// 	}
	//取消锁定状态
	MsgPetBreedCancelLock msg;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SuAnimalMore::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimalMore.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuAnimalMore.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_SuAnimalMore::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SuAnimalMore, s_CUI_ID_FRAME_SuAnimalMoreOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SuAnimalMore, s_CUI_ID_FRAME_SuAnimalMoreOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_HELP, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_HELPOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill1, s_CUI_ID_FRAME_SuAnimalMoreID_LISTIMG_Skill1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill1, s_CUI_ID_FRAME_SuAnimalMoreID_LISTIMG_Skill1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill1, s_CUI_ID_FRAME_SuAnimalMoreID_LISTIMG_Skill1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill1, s_CUI_ID_FRAME_SuAnimalMoreID_LISTIMG_Skill1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill2, s_CUI_ID_FRAME_SuAnimalMoreID_LISTIMG_Skill2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill2, s_CUI_ID_FRAME_SuAnimalMoreID_LISTIMG_Skill2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill2, s_CUI_ID_FRAME_SuAnimalMoreID_LISTIMG_Skill2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill2, s_CUI_ID_FRAME_SuAnimalMoreID_LISTIMG_Skill2OnIconRButtonUp );
	theUiManager.OnComboBoxChange( ID_FRAME_SuAnimalMore, ID_COMBOBOX_SelectPet1, s_CUI_ID_FRAME_SuAnimalMoreID_COMBOBOX_SelectPet1OnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_SuAnimalMore, ID_COMBOBOX_SelectPet2, s_CUI_ID_FRAME_SuAnimalMoreID_COMBOBOX_SelectPet2OnComboBoxChange );
	theUiManager.OnListSelectChange( ID_FRAME_SuAnimalMore, ID_LIST_Pet, s_CUI_ID_FRAME_SuAnimalMoreID_LIST_PetOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_ChangePet, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_ChangePetOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_LookPet, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_LookPetOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_LookPartnerPet, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_LookPartnerPetOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_Lock, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_LockOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_OK, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_Right1, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_Right1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_Right2, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_Right2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_Left1, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_Left1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_Left2, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_Left2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMore, ID_BUTTON_UnchainLock, s_CUI_ID_FRAME_SuAnimalMoreID_BUTTON_UnchainLockOnButtonClick );

	m_pID_FRAME_SuAnimalMore = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SuAnimalMore );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_CLOSE );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_HELP );
	m_pID_PICTURE_Pet1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_PICTURE_Pet1 );
	m_pID_PICTURE_Pet2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_PICTURE_Pet2 );
	m_pID_TEXT_Result1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Result1 );
	m_pID_TEXT_Level1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Level1 );
	m_pID_TEXT_Level2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Level2 );
	m_pID_TEXT_Generation1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Generation1 );
	m_pID_TEXT_Generation2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Generation2 );
	m_pID_TEXT_Result2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Result2 );
	m_pID_TEXT_StrengthZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_StrengthZ );
	m_pID_TEXT_AgilityZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_AgilityZ );
	m_pID_TEXT_StaminaZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_StaminaZ );
	m_pID_TEXT_IntellectZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_IntellectZ );
	m_pID_TEXT_Strength = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Strength );
	m_pID_TEXT_Agility = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Agility );
	m_pID_TEXT_Stamina = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Stamina );
	m_pID_TEXT_Intellect = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Intellect );
	m_pID_TEXT_NeedMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_NeedMoney );
	m_pID_TEXT_CurrentMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_CurrentMoney );
	m_pID_LISTIMG_Skill1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill1 );
	m_pID_LISTIMG_Skill2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_LISTIMG_Skill2 );
	m_pID_COMBOBOX_SelectPet1 = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_COMBOBOX_SelectPet1 );
	m_pID_COMBOBOX_SelectPet2 = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_COMBOBOX_SelectPet2 );
	m_pID_LIST_Pet = (ControlList*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_LIST_Pet );
	m_pID_TEXT_PartnerPetName = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_PartnerPetName );
	m_pID_TEXT_MyPetName = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_MyPetName );
	m_pID_TEXT_Info1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Info1 );
	m_pID_BUTTON_ChangePet = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_ChangePet );
	m_pID_BUTTON_LookPet = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_LookPet );
	m_pID_TEXT_Info2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_TEXT_Info2 );
	m_pID_BUTTON_LookPartnerPet = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_LookPartnerPet );
	m_pID_BUTTON_Lock = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_Lock );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_OK );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_Cancel );
	m_pID_BUTTON_Right1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_Right1 );
	m_pID_BUTTON_Right2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_Right2 );
	m_pID_BUTTON_Left1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_Left1 );
	m_pID_BUTTON_Left2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_Left2 );
	m_pID_BUTTON_UnchainLock = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMore, ID_BUTTON_UnchainLock );
	m_pID_PICTURE_SD1 =(ControlPicture*)theUiManager.FindControl(ID_FRAME_SuAnimalMore,ID_PICTURE_SD1);
	m_pID_PICTURE_SD2 =(ControlPicture*)theUiManager.FindControl(ID_FRAME_SuAnimalMore,ID_PICTURE_SD2);
	assert( m_pID_FRAME_SuAnimalMore );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_PICTURE_Pet1 );
	assert( m_pID_PICTURE_Pet2 );
	assert( m_pID_TEXT_Result1 );
	assert( m_pID_TEXT_Level1 );
	assert( m_pID_TEXT_Level2 );
	assert( m_pID_TEXT_Generation1 );
	assert( m_pID_TEXT_Generation2 );
	assert( m_pID_TEXT_Result2 );
	assert( m_pID_TEXT_StrengthZ );
	assert( m_pID_TEXT_AgilityZ );
	assert( m_pID_TEXT_StaminaZ );
	assert( m_pID_TEXT_IntellectZ );
	assert( m_pID_TEXT_Strength );
	assert( m_pID_TEXT_Agility );
	assert( m_pID_TEXT_Stamina );
	assert( m_pID_TEXT_Intellect );
	assert( m_pID_TEXT_NeedMoney );
	assert( m_pID_TEXT_CurrentMoney );
	assert( m_pID_LISTIMG_Skill1 );
	assert( m_pID_LISTIMG_Skill2 );
	assert( m_pID_COMBOBOX_SelectPet1 );
	assert( m_pID_COMBOBOX_SelectPet2 );
	assert( m_pID_LIST_Pet );
	assert( m_pID_TEXT_PartnerPetName );
	assert( m_pID_TEXT_MyPetName );
	assert( m_pID_TEXT_Info1 );
	assert( m_pID_BUTTON_ChangePet );
	assert( m_pID_BUTTON_LookPet );
	assert( m_pID_TEXT_Info2 );
	assert( m_pID_BUTTON_LookPartnerPet );
	assert( m_pID_BUTTON_Lock );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Right1 );
	assert( m_pID_BUTTON_Right2 );
	assert( m_pID_BUTTON_Left1 );
	assert( m_pID_BUTTON_Left2 );
	assert( m_pID_BUTTON_UnchainLock );
	assert(m_pID_PICTURE_SD1);
	assert(m_pID_PICTURE_SD2);
	m_pID_PICTURE_SD1->SetVisable(false);
	m_pID_PICTURE_SD2->SetVisable(false);
	m_pID_LISTIMG_Skill1->SetDisableCanbePick( false );
	m_pID_LISTIMG_Skill2->SetDisableCanbePick( false );
	m_pID_LISTIMG_Skill1->ShowPressEffect( false );
	m_pID_LISTIMG_Skill2->ShowPressEffect( false );
	m_pID_FRAME_SuAnimalMore->SetOnVisibleChangedFun( OnVisibleChange );

	m_pPlayerAnim1 = MeNew CPlayerAnim;
	m_pPlayer1 = MeNew CPlayer;
	m_pPlayer1->SetAnim( m_pPlayerAnim1 );
	m_pPlayerAnim1->SetPlayer( m_pPlayer1 );
	theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayer1 );

	m_pPlayerAnim2 = MeNew CPlayerAnim;
	m_pPlayer2 = MeNew CPlayer;
	m_pPlayer2->SetAnim( m_pPlayerAnim2 );
	m_pPlayerAnim2->SetPlayer( m_pPlayer2 );
	theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayer2 );
	m_pID_BUTTON_UnchainLock->SetVisable(false);
	m_pID_BUTTON_UnchainLock->SetEnable(false);
	m_pID_BUTTON_Lock->SetVisable(true);
	m_pID_BUTTON_Lock->SetEnable(true);
	_SetVisable( false );
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_SuAnimalMore::_UnLoadUI()
{
	if (m_pPlayer1)
	{
		theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer( m_pPlayer1 );
		m_pPlayer1->Destroy();	
		delete m_pPlayer1;
		m_pPlayer1 = 0;
		m_pPlayerAnim1 = 0;
	}

	if(m_pPlayer2)
	{
		theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer( m_pPlayer2 );
		m_pPlayer2->Destroy();	
		delete m_pPlayer2;
		m_pPlayer2 = 0;
		m_pPlayerAnim2 = 0;
	}
	m_pID_FRAME_SuAnimalMore = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimalMore.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_SuAnimalMore::_IsVisable()
{
	if(!m_pID_FRAME_SuAnimalMore)
		return false;

	return m_pID_FRAME_SuAnimalMore->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_SuAnimalMore::_SetVisable( const bool bVisable )
{
	if(m_pID_FRAME_SuAnimalMore)
	   m_pID_FRAME_SuAnimalMore->SetVisable( bVisable );

	if(bVisable)
	{
		ShowAllPet();
		ReqPetBreed();
		RefreshMoney();
	}
	else
	{
		ClearTargetStatus();
	}
	m_nMountId1 = -1;
	m_nMountId2 = -1;
	m_fRotateZ1 = 0.0f;
	m_fRotateZ2 = 0.0f;

	m_bMyLock = false;
	m_bTargetLock = false;
}

void CUI_ID_FRAME_SuAnimalMore::OnVisibleChange( ControlObject* pUIObject )
{
	if( s_CUI_ID_FRAME_SuAnimalMore.IsVisable() )
	{
		s_CUI_ID_FRAME_SuAnimalMore.ResetControls();
	}
}

void CUI_ID_FRAME_SuAnimalMore::Refresh()
{
	if( !m_pID_FRAME_SuAnimalMore )
		return;

	int nMountLimitCnt = thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount;
	int iSelId1 = m_pID_COMBOBOX_SelectPet1->GetListBox().GetCurSelIndex();
	int iSelId2 = m_pID_COMBOBOX_SelectPet2->GetListBox().GetCurSelIndex();

	RefreshMoney();
	bool bCanBreed1 = false;
	bool bCanBreed2 = false;
	if( iSelId1 > -1 && iSelId1 < nMountLimitCnt )
	{
		// 主坐骑资质
		SMountItem mount = thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId1];
		SMountItem::SBaseInfo mountInfo1 = mount.baseInfo;
		*m_pID_TEXT_StrengthZ = mountInfo1.aptitudeAttribute[EBaseAttr_Strength];
		*m_pID_TEXT_AgilityZ = mountInfo1.aptitudeAttribute[EBaseAttr_Agility];
		*m_pID_TEXT_StaminaZ = mountInfo1.aptitudeAttribute[EBaseAttr_Stamina];
		*m_pID_TEXT_IntellectZ = mountInfo1.aptitudeAttribute[EBaseAttr_Intelligence];

		// 等级、辈分、能否繁殖
		*m_pID_TEXT_Level1 = mountInfo1.level;
		*m_pID_TEXT_Generation1 = theXmlString.GetString( eText_MountGeneration_First + mountInfo1.generation );
		*m_pID_TEXT_Result1 = theXmlString.GetString( eText_Mount_Mate_Unable + mount.IsCanBreed() );
		bCanBreed1 = mount.IsCanBreed();

		// 技能Icon
		m_pID_LISTIMG_Skill1->Clear();
		m_pID_LISTIMG_Skill2->Clear();
		m_pID_LISTIMG_Skill1->SetEnableCnt( mount.skillInfo.initiativeSkillNumber );
		CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.GetPage( CUISkillMgr::eMountSkill );
		if( pSkillTree )
		{
			SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
			for( int i = 0; i < SMountItem::MICD_MaxSkillCount; ++i )
			{
				unsigned short usSkillId = mount.skillInfo.skills[i].ustSkillID;
				if( usSkillId == 0 )
					continue;
				unsigned short usLevel = mount.skillInfo.skills[i].stSkillLevel;
				ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID( usSkillId, usLevel );
				if( !pItemSkill )
					continue;
				const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue( usSkillId );
				if( !pIcon )
					continue;

				ControlIconDrag::S_ListImg stItem;
				stItem.m_pkIconInfo->SetIconImageInfo( pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column );
				stItem.SetData( usSkillId, usLevel, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
				stItem.SetFlags( CUISkillMgr::eMountSkill );

				switch( pItemSkill->sSkillCategory )
				{
				case ItemDefine::SCT_MountPassive:
				case ItemDefine::SCT_MountMasterInitiativeUnControl:
					m_pID_LISTIMG_Skill2->SetItem( &stItem );
					break;
				case ItemDefine::SCT_MountMasterInitiativeControl:
					m_pID_LISTIMG_Skill1->SetItem( &stItem );
					break;
				}
			}
		}
	}
	else
	{
		// 主坐骑默认值
		*m_pID_TEXT_StrengthZ = "";
		*m_pID_TEXT_AgilityZ = "";
		*m_pID_TEXT_StaminaZ = "";
		*m_pID_TEXT_IntellectZ = "";
		*m_pID_TEXT_Level1 = "";
		*m_pID_TEXT_Generation1 = "";
		*m_pID_TEXT_Result1 = "";
		m_pID_LISTIMG_Skill1->Clear();
		m_pID_LISTIMG_Skill2->Clear();
		m_pID_LISTIMG_Skill1->SetEnableCnt( SMountItem::MICD_PassiveSkillIndex );
	}

	if( iSelId2 > -1 && iSelId2 < nMountLimitCnt )
	{
		// 副坐骑属性
		SMountItem::SBaseInfo mountInfo2 = thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId2].baseInfo;
		*m_pID_TEXT_Strength = mountInfo2.baseAttribute[EBaseAttr_Strength];
		*m_pID_TEXT_Agility = mountInfo2.baseAttribute[EBaseAttr_Agility];
		*m_pID_TEXT_Stamina = mountInfo2.baseAttribute[EBaseAttr_Stamina];
		*m_pID_TEXT_Intellect = mountInfo2.baseAttribute[EBaseAttr_Intelligence];

		// 等级、辈分、能否繁殖
		*m_pID_TEXT_Level2 = mountInfo2.level;
		*m_pID_TEXT_Generation2 = theXmlString.GetString( eText_MountGeneration_First + mountInfo2.generation );
		*m_pID_TEXT_Result2 = theXmlString.GetString( eText_Mount_Mate_Unable + thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId2].IsCanBreed() );
		bCanBreed2 = thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId2].IsCanBreed();
	}
	else
	{
		// 副坐骑默认值
		*m_pID_TEXT_Strength = "";
		*m_pID_TEXT_Agility = "";
		*m_pID_TEXT_Stamina = "";
		*m_pID_TEXT_Intellect = "";
		*m_pID_TEXT_Level2 = "";
		*m_pID_TEXT_Generation2 = "";
		*m_pID_TEXT_Result2 = "";
	}

	if (bCanBreed1 && bCanBreed2)
	{
		m_pID_BUTTON_OK->SetEnable(true);
	}
	else
	{
		//m_pID_BUTTON_OK->SetEnable(false);
	}
}


void  CUI_ID_FRAME_SuAnimalMore::RenderViewport()
{
	if( !IsVisable() )
		return;

	RECT rc1,rc2;
	m_pID_PICTURE_Pet1->GetRealRect( &rc1 );
	m_pID_PICTURE_Pet2->GetRealRect( &rc2 );
	//s_CUI_ID_FRAME_SuAnimal.RenderMount( m_nMountId1, m_pPlayerAnim1, m_fRotateZ1, rc1 );
	//s_CUI_ID_FRAME_SuAnimal.RenderMount( m_nMountId2, m_pPlayerAnim2, m_fRotateZ2, rc2 );
}

void  CUI_ID_FRAME_SuAnimalMore::ResetControls()
{
	m_nMountId1 = -1;
	m_nMountId2 = -1;
	m_fRotateZ1 = 0.0f;
	m_fRotateZ2 = 0.0f;

	m_bMyLock = false;
	m_bTargetLock = false;

	if( !m_pID_FRAME_SuAnimalMore )
		return;

	m_pID_TEXT_MyPetName->SetText("");
	m_pID_TEXT_PartnerPetName->SetText("");

	m_pID_BUTTON_OK->SetEnable(false);
	ClearTargetStatus();
// 	{
// 		int nMountLimitCnt = thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount;
// 		m_pID_COMBOBOX_SelectPet1->GetListBox().Clear();
// 		m_pID_COMBOBOX_SelectPet2->GetListBox().Clear();
// 		for( int i = 0; i < nMountLimitCnt; ++i )
// 		{
// 			SMountItem::SBaseInfo mountInfo = thePlayerRole.m_charinfo.ItemBagData.miItems[i].baseInfo;
// 			if( mountInfo.id != InvalidLogicNumber )
// 			{
// 				ControlList::S_List	stItem;
// 
// 				// 取颜色
// 				ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( mountInfo.id );
// 				if( !pCommon )
// 					continue;
// 				DWORD dwColor = S_IconInfoHero::GetQualityColor( pCommon->ustLevel );
// 				stItem.SetData( mountInfo.szName, mountInfo.id, 0, dwColor );
// 				m_pID_COMBOBOX_SelectPet1->GetListBox().AddItem( &stItem,NULL, false );
// 				m_pID_COMBOBOX_SelectPet2->GetListBox().AddItem( &stItem,NULL, false );
// 			}
// 		}
// 		m_pID_COMBOBOX_SelectPet1->GetListBox().SetCurSelIndex( -1 );
// 		m_pID_COMBOBOX_SelectPet2->GetListBox().SetCurSelIndex( -1 );
// 		m_pID_COMBOBOX_SelectPet1->GetEditInput().SetText( "" );
// 		m_pID_COMBOBOX_SelectPet2->GetEditInput().SetText( "" );
// 	}
// 	Refresh();
}

void CUI_ID_FRAME_SuAnimalMore::RefreshMoney()
{
	if( !m_pID_FRAME_SuAnimalMore )
		return;

	// 所需和现有交子
	m_pID_TEXT_NeedMoney->SetText("");
	m_pID_TEXT_CurrentMoney->SetText("");
	std::string strMoney;
	int money = 0;
	if (m_sPetItem.baseInfo.petId != InvalidLogicNumber)
	{
		ItemDefine::SPetMonster* m_petMonster = GettheItemDetail().GetPetById(m_sPetItem.baseInfo.petId);
		int quality = 0;
		int m_level = 0;

		if (m_petMonster != NULL)
		{
			quality = m_petMonster->catchQuality;
			m_level = m_petMonster->catchLevel;
		}
		money = thePetSettingConfig.GetPetBreedMoney(quality,m_level);//所需金钱
	
	}
	thePlayerRole.GetGSCStringFromMoney(money, strMoney );
	if (thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) < (DWORD)money)
	{
		m_pID_TEXT_NeedMoney->SetText(strMoney.c_str(),0xffff0000);
		m_pID_BUTTON_OK->SetEnable(false);
	}
	else
	{
		*m_pID_TEXT_NeedMoney = strMoney;
		m_pID_BUTTON_OK->SetEnable(true);
	}
	strMoney.clear();
	thePlayerRole.GetGSCStringFromCurrentMoney( strMoney );
	*m_pID_TEXT_CurrentMoney = strMoney;
}
void CUI_ID_FRAME_SuAnimalMore::RefreshByMoneyChange()
{
	RefreshMoney();
}
void CUI_ID_FRAME_SuAnimalMore::ShowAllPet()
{
	if(!m_pID_FRAME_SuAnimalMore)
		return;
	int nIndex = m_pID_LIST_Pet->GetCurSelIndex();
	m_pID_LIST_Pet->Clear();

	for (int i = 0;i < ITEM_MOUNT_MAXCOUNT;++i)
	{
		DWORD dwcolor = Color_Config.getColor(CC_PetColor_White);//白色
		SPetItem pet = thePlayerRole.GetCharInfo2().ItemBagData.petItems[i];
		if(pet.GetPetGuid() == 0 || pet.baseInfo.petId == InvalidLogicNumber)
			continue;
		int breedMaxNum = thePetSettingConfig.GetPetBreedNum(pet.baseInfo.level);
		ControlList::S_List stItem;
		ItemDefine::SPetMonster* m_petMonster = GettheItemDetail().GetPetById(pet.baseInfo.petId);
		if (!pet.baseInfo.isActive &&((m_petMonster != NULL && ! m_petMonster->bIsBaby )|| pet.baseInfo.breedNum>= breedMaxNum 
			|| m_petMonster->bIsAberrance ||pet.baseInfo.generation >0 ||/*pet.baseInfo.loyalty < 100 ||*/ pet.baseInfo.duration <1000) )
		{
			dwcolor= Color_Config.getColor(CC_PetColor_Taupe); //暗灰色
		}
		if (pet.baseInfo.isActive)
		{
			dwcolor = Color_Config.getColor(CC_PetColor_Red); //红色
		}
		SPetItem &m_SelectPet = thePlayerRole.GetPetByIndex(nIndex);
		if (m_SelectPet.baseInfo.petId != InvalidLogicNumber && m_SelectPet.baseInfo.guid == pet.baseInfo.guid)
		{
			dwcolor = Color_Config.getColor(CC_PetColor_Green);
		}
		stItem.SetData(pet.GetPetName(),pet.GetPetID(),0,dwcolor);
		m_pID_LIST_Pet->AddItem(&stItem);
	}
	m_pID_LIST_Pet->SetCurSelIndex(nIndex);
}

void CUI_ID_FRAME_SuAnimalMore::ReqPetBreed()
{
	if(!IsTeamLeader(thePlayerRole.GetName()))
		return;

	MsgPetBreedReq msg;
    GettheNetworkInput().SendMsg(&msg);
}

bool CUI_ID_FRAME_SuAnimalMore::IsTeamLeader( const char* playerName )
{
	if ( playerName )
	{
		std::vector<TeamInfo> vecInfos = thePlayerRole.GetTeamInfo();
		int count = (int)vecInfos.size();
		for ( int i = 0; i < count; i ++ )
		{
			if( vecInfos[i].bHeader )
			{

				if ( vecInfos[i].szName.compare(playerName) == 0 )
				{
					return true;
				}
				break;
			}
		}

	}
	return false;
}

void CUI_ID_FRAME_SuAnimalMore::SendSelPetReg(int nIndex)
{
	MsgPetBreedChoice msg;
	msg.index = nIndex;
    GettheNetworkInput().SendMsg(&msg);
}

void  CUI_ID_FRAME_SuAnimalMore::SetMyPetItem(SPetItem* pItem)
{
	if(!pItem)
		return;

	memcpy(&m_sPetItem,pItem,sizeof(SPetItem));
	//s_CUI_ID_FRAME_SuAnimal.ChangeModel(m_sPetItem, m_pPlayerAnim1, m_nMountId1);	
	if(!m_pID_FRAME_SuAnimalMore)
		return;

	//设置名字
	m_pID_TEXT_MyPetName->SetText(m_sPetItem.GetPetName());
}

void CUI_ID_FRAME_SuAnimalMore::SetTargetPetItem(SPetItem *pItem)
{
	if(!pItem)
		return;

	memcpy(&m_sTargetItem,pItem,sizeof(SPetItem));
	//s_CUI_ID_FRAME_SuAnimal.ChangeModel(m_sTargetItem, m_pPlayerAnim2, m_nMountId2);
	if(!m_pID_FRAME_SuAnimalMore)
		return;

	//设置名字
	m_pID_TEXT_PartnerPetName->SetText(m_sTargetItem.GetPetName());
}


void CUI_ID_FRAME_SuAnimalMore::RegLockPet()
{
	MsgPetBreedLock msg;
    GettheNetworkInput().SendMsg(&msg);
}

void CUI_ID_FRAME_SuAnimalMore::ConfirmPetBreed()
{
	MsgPetBreedConfirm msg;
	GettheNetworkInput().SendMsg(&msg);
}

void CUI_ID_FRAME_SuAnimalMore::CancelPetBreed()
{
	MsgPetBreedCancelReq msg;
	GettheNetworkInput().SendMsg(&msg);
}

void CUI_ID_FRAME_SuAnimalMore::SetMyLockItem(bool bValue)
{
	m_bMyLock = bValue; 
	 m_pID_BUTTON_Lock->SetEnable(!bValue);
	 m_pID_BUTTON_Lock->SetVisable(!bValue);
	 m_pID_BUTTON_UnchainLock->SetEnable(bValue);
	 m_pID_BUTTON_UnchainLock->SetVisable(bValue);
	 if (m_bMyLock)
	 {
		 m_pID_PICTURE_SD2->SetVisable(true);
	 }
	 else
	 {
		 m_pID_PICTURE_SD2->SetVisable(false);
	 }
	 
}

void CUI_ID_FRAME_SuAnimalMore::SetTargetLockItem(bool bValue)
{
	m_bTargetLock = bValue;
	if (m_bTargetLock)
	{
		m_pID_PICTURE_SD1->SetVisable(true);
	}
	else
	{
		m_pID_PICTURE_SD1->SetVisable(false);
	}
	
}
void CUI_ID_FRAME_SuAnimalMore::ClearTargetStatus()
{
	m_sTargetItem.baseInfo.petId = InvalidLogicNumber;
	m_bTargetLock = false;
}