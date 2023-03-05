/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\宠物\PetCard.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimalCard.h"
#include "SuAnimalCardList.h"
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
#include "GameDefineChar.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/World.h"
#include "packet_interface.h"
//#include "Launcher/DataLauncher.h"
CUI_ID_FRAME_SuAnimalCard s_CUI_ID_FRAME_SuAnimalCard;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimalCard, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimalCard, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_BUTTON_ToLeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_BUTTON_ToRightOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LIST_IconNameOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_CatchLvOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_CatchLvOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_CatchLvOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_CatchLvOnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LIST_PetNameOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_GenreOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_GenreOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_GenreOnIconButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_FullOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_RenOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_ShenOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_XianOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_JiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_MoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_GuiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_YaoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_ShouOnCheckBoxCheck )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_GenreOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_IconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_IconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_IconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_LISTIMG_IconOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_BUTTON_PageUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_BUTTON_PageDownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_BUTTON_ReturnOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_ZiZhiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCard, ID_CHECKBOX_BianShenOnCheckBoxCheck )
CUI_ID_FRAME_SuAnimalCard::CUI_ID_FRAME_SuAnimalCard()
{
	// Member
	m_pID_FRAME_PetCard = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TitleTop = NULL;
	m_pID_PICTURE_PetModel = NULL;
	m_pID_BUTTON_ToLeft = NULL;
	m_pID_BUTTON_ToRight = NULL;
	m_pID_TEXT_Phyle = NULL;
	m_pID_LISTIMG_CatchLv = NULL;
	m_pID_TEXT_PetNameTitle = NULL;
	m_pID_LIST_PetName = NULL;
	m_pID_TEXT_Attribute = NULL;
	m_pID_TEXT_Lv = NULL;
	m_pID_LISTIMG_Genre = NULL;
	m_pID_TEXT_Dower = NULL;
	m_pID_TEXT_DowerLvZ = NULL;
	m_pID_TEXT_TEXTZ = NULL;
	m_pID_LIST_IconName = NULL;
	m_pID_LISTIMG_Icon = NULL;
	m_pID_TEXT_TEXTZ0 = NULL;
	m_pID_TEXT_Introduce = NULL;
	m_pID_TEXT_TEXTZ1 = NULL;
	m_pID_TEXT_Address = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_Return = NULL;
	m_pID_TEXT_ForceZ = NULL;
	m_pID_TEXT_NimbusZ = NULL;
	m_pID_TEXT_StaminaZ = NULL;
	m_pID_TEXT_CelerityZ = NULL;
	m_pID_PICTURE_LeiBieWu = NULL;
	m_pID_PICTURE_LeiBieFa = NULL;
	m_pID_PICTURE_WXTu = NULL;
	m_pID_PICTURE_WXJin = NULL;
	m_pID_PICTURE_WXMu = NULL;
	m_pID_PICTURE_WXShui = NULL;
	m_pID_PICTURE_WXHuo = NULL;
	m_pID_PICTURE_ZhongZuRen = NULL;
	m_pID_PICTURE_ZhongZuJi = NULL;
	m_pID_PICTURE_ZhongZuShou = NULL;
	m_pID_PICTURE_ZhongZuXian = NULL;
	m_pID_PICTURE_ZhongZuGui = NULL;
	m_pID_PICTURE_ZhongZuYao = NULL;
	m_pID_PICTURE_ZhongZuShen = NULL;
	m_pID_PICTURE_ZhongZuMo = NULL;
	m_pID_PICTURE_ZiZhi = NULL;
	m_pID_PICTURE_Force = NULL;
	m_pID_PICTURE_Nimbus = NULL;
	m_pID_PICTURE_Stamina = NULL;
	m_pID_PICTURE_Celerity = NULL;
	m_pID_TEXT_DowerLv = NULL;
	m_nModelId = 0;
	m_pID_PICTURE_BianShen = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_NLZZ= NULL;
	m_pID_CHECKBOX_ZiZhi = NULL;
	m_pID_CHECKBOX_BianShen = NULL;
	m_pID_CHECKBOX_BianShen = NULL;
	m_pID_TEXT_CardAmount = NULL;
	mCurrPage = 1;
}
// Frame
bool CUI_ID_FRAME_SuAnimalCard::OnFrameRun()
{
	if (!s_CUI_ID_FRAME_SuAnimalCard.IsVisable())  return false;

// 	if (m_bRotate && m_pID_BUTTON_ToRight->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
// 	{
// 		m_fRotateZ += 1.5f*theHeroGame.GetFrameElapsedTime();
// 	}
// 	else if (m_bRotate && m_pID_BUTTON_ToLeft->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
// 	{
// 		m_fRotateZ -= 1.5f*theHeroGame.GetFrameElapsedTime();
// 	}
// 	else 
// 		m_bRotate = false;
	return true;
}
bool CUI_ID_FRAME_SuAnimalCard::OnFrameRender()
{
// 	GetEngine()->GetRenderer()->EndScene();
// 	RenderViewport();
// 	GetEngine()->GetRenderer()->BeginScene();
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalCard::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalCard::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalCard::ID_BUTTON_ToLeftOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	//m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalCard::ID_BUTTON_ToRightOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	//m_bRotate = false;
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_CatchLvOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_CatchLvOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_CatchLvOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_CatchLvOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
// List
void CUI_ID_FRAME_SuAnimalCard::ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_GenreOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_GenreOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_GenreOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_GenreOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_FullOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	RefreshCheckBoxStatus(EPhyle_MaxCount);
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(EPhyle_MaxCount);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(EPhyle_MaxCount);
	s_CUI_ID_FRAME_SuAnimalCardList.SetPhylePic(EPhyle_MaxCount);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshCheckBoxStatus(EPhyle_MaxCount);
	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(!s_CUI_ID_FRAME_SuAnimalCard.IsVisable());
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_RenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	RefreshCheckBoxStatus(EPhyle_Human);
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(EPhyle_Human);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(EPhyle_Human);
	s_CUI_ID_FRAME_SuAnimalCardList.SetPhylePic(EPhyle_Human);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshCheckBoxStatus(EPhyle_Human);
	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(!s_CUI_ID_FRAME_SuAnimalCard.IsVisable());
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_ShenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	RefreshCheckBoxStatus(EPhyle_Deity);
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(EPhyle_Deity);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(EPhyle_Deity);
	s_CUI_ID_FRAME_SuAnimalCardList.SetPhylePic(EPhyle_Deity);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshCheckBoxStatus(EPhyle_Deity);
	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(!s_CUI_ID_FRAME_SuAnimalCard.IsVisable());
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_XianOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	RefreshCheckBoxStatus(EPhyle_Immortal);
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(EPhyle_Immortal);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(EPhyle_Immortal);
	s_CUI_ID_FRAME_SuAnimalCardList.SetPhylePic(EPhyle_Immortal);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshCheckBoxStatus(EPhyle_Immortal);
	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(!s_CUI_ID_FRAME_SuAnimalCard.IsVisable());
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_JiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	RefreshCheckBoxStatus(EPhyle_Machine);
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(EPhyle_Machine);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(EPhyle_Machine);
	s_CUI_ID_FRAME_SuAnimalCardList.SetPhylePic(EPhyle_Machine);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshCheckBoxStatus(EPhyle_Machine);
	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(!s_CUI_ID_FRAME_SuAnimalCard.IsVisable());
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_MoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	RefreshCheckBoxStatus(EPhyle_Demon);
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(EPhyle_Demon);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(EPhyle_Demon);
	s_CUI_ID_FRAME_SuAnimalCardList.SetPhylePic(EPhyle_Demon);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshCheckBoxStatus(EPhyle_Demon);
	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(!s_CUI_ID_FRAME_SuAnimalCard.IsVisable());
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_GuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	RefreshCheckBoxStatus(EPhyle_Ghost);
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(EPhyle_Ghost);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(EPhyle_Ghost);
	s_CUI_ID_FRAME_SuAnimalCardList.SetPhylePic(EPhyle_Ghost);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshCheckBoxStatus(EPhyle_Ghost);
	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(!s_CUI_ID_FRAME_SuAnimalCard.IsVisable());
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_YaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	RefreshCheckBoxStatus(EPhyle_Bogey);
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(EPhyle_Bogey);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(EPhyle_Bogey);
	s_CUI_ID_FRAME_SuAnimalCardList.SetPhylePic(EPhyle_Bogey);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshCheckBoxStatus(EPhyle_Bogey);
	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(!s_CUI_ID_FRAME_SuAnimalCard.IsVisable());
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_ShouOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	RefreshCheckBoxStatus(EPhyle_Beast);
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(EPhyle_Beast);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(EPhyle_Beast);
	s_CUI_ID_FRAME_SuAnimalCardList.SetPhylePic(EPhyle_Beast);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshCheckBoxStatus(EPhyle_Beast);
	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(!s_CUI_ID_FRAME_SuAnimalCard.IsVisable());
}
// List
void CUI_ID_FRAME_SuAnimalCard::ID_LIST_IconNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_IconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_IconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_IconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalCard::ID_LISTIMG_IconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_SuAnimalCard::ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	for (int i = 0; i< m_vecPetMonster.size(); i++)
	{
		if (m_vecPetMonster[i]->stMonsterId == m_currentPetId)
		{
			if (i >0)
			{
				SetCurrPage(mCurrPage);
				RefreshPage(m_vecPetMonster[i-1],m_currentphyle);
			}
			else
			{
				mCurrPage = 1;
				SetCurrPage(mCurrPage);
				RefreshPage(m_vecPetMonster[0],m_currentphyle);
			}
		}
	}
	return true;
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_ZiZhiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	m_GroupBianShen.SetVisible(false);
	m_GroupZiZhi.SetVisible(true);
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCard::ID_CHECKBOX_BianShenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCard )
		return;
	m_GroupBianShen.SetVisible(true);
	m_GroupZiZhi.SetVisible(false);
}

// Button
bool CUI_ID_FRAME_SuAnimalCard::ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	for (int i = 0; i< m_vecPetMonster.size(); i++)
	{
		if (m_vecPetMonster[i]->stMonsterId == m_currentPetId)
		{
			if (i<(m_vecPetMonster.size()-1))
			{
				mCurrPage = i+1;
				RefreshPage(m_vecPetMonster[i+1],m_currentphyle);
				SetCurrPage(mCurrPage);
				return true;
			}
			else
			{
				mCurrPage = m_vecPetMonster.size();
				RefreshPage(m_vecPetMonster[m_vecPetMonster.size()-1],m_currentphyle);
				SetCurrPage(mCurrPage);
				return true;
			}
		}
	}
	
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalCard::ID_BUTTON_ReturnOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(true);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(m_currentphyle);
	s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(m_currentphyle);
	s_CUI_ID_FRAME_SuAnimalCard.SetVisable(!s_CUI_ID_FRAME_SuAnimalCard.IsVisable());
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SuAnimalCard::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimalCard.MEUI" , false, UI_Render_LayerThree  );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuAnimalCard.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuAnimalCard::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PetCard, s_CUI_ID_FRAME_SuAnimalCardOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PetCard,s_CUI_ID_FRAME_SuAnimalCardOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PetCard, ID_BUTTON_HELP, s_CUI_ID_FRAME_SuAnimalCardID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCard, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SuAnimalCardID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCard, ID_BUTTON_ToLeft, s_CUI_ID_FRAME_SuAnimalCardID_BUTTON_ToLeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCard, ID_BUTTON_ToRight, s_CUI_ID_FRAME_SuAnimalCardID_BUTTON_ToRightOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_PetCard, ID_LISTIMG_CatchLv, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_CatchLvOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetCard, ID_LISTIMG_CatchLv, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_CatchLvOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetCard, ID_LISTIMG_CatchLv, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_CatchLvOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetCard, ID_LISTIMG_CatchLv, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_CatchLvOnIconRButtonUp );
	theUiManager.OnListSelectChange( ID_FRAME_PetCard, ID_LIST_PetName,s_CUI_ID_FRAME_SuAnimalCardID_LIST_PetNameOnListSelectChange );
	theUiManager.OnIconDragOn( ID_FRAME_PetCard, ID_LISTIMG_Genre, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_GenreOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetCard, ID_LISTIMG_Genre, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_GenreOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetCard, ID_LISTIMG_Genre, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_GenreOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetCard, ID_LISTIMG_Genre, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_GenreOnIconRButtonUp );
	theUiManager.OnListSelectChange( ID_FRAME_PetCard, ID_LIST_IconName, s_CUI_ID_FRAME_SuAnimalCardID_LIST_IconNameOnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_Full, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_FullOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_Ren, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_RenOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_Shen, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_ShenOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_Xian, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_XianOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_Ji, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_JiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_Mo, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_MoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_Gui, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_GuiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_Yao, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_YaoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_Shou, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_ShouOnCheckBoxCheck );
	theUiManager.OnIconDragOn( ID_FRAME_PetCard, ID_LISTIMG_Icon, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_IconOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetCard, ID_LISTIMG_Icon, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_IconOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetCard, ID_LISTIMG_Icon, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_IconOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetCard, ID_LISTIMG_Icon, s_CUI_ID_FRAME_SuAnimalCardID_LISTIMG_IconOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_PetCard, ID_BUTTON_PageUp, s_CUI_ID_FRAME_SuAnimalCardID_BUTTON_PageUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCard, ID_BUTTON_PageDown, s_CUI_ID_FRAME_SuAnimalCardID_BUTTON_PageDownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCard, ID_BUTTON_Return, s_CUI_ID_FRAME_SuAnimalCardID_BUTTON_ReturnOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_ZiZhi, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_ZiZhiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCard, ID_CHECKBOX_BianShen, s_CUI_ID_FRAME_SuAnimalCardID_CHECKBOX_BianShenOnCheckBoxCheck );

	m_pID_FRAME_PetCard = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetCard );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCard, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCard, ID_BUTTON_CLOSE );
	m_pID_TEXT_TitleTop = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_TitleTop );
	m_pID_PICTURE_PetModel = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_PetModel );
	m_pID_BUTTON_ToLeft = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCard, ID_BUTTON_ToLeft );
	m_pID_BUTTON_ToRight = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCard, ID_BUTTON_ToRight );
	m_pID_TEXT_Phyle = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_Phyle );
	m_pID_LISTIMG_CatchLv = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetCard, ID_LISTIMG_CatchLv );
	m_pID_TEXT_PetNameTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_PetNameTitle );
	m_pID_LIST_PetName = (ControlList*)theUiManager.FindControl( ID_FRAME_PetCard, ID_LIST_PetName );
	m_pID_TEXT_Attribute = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_Attribute );
	m_pID_TEXT_Lv = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_Lv );
	m_pID_LISTIMG_Genre = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetCard, ID_LISTIMG_Genre );
	m_pID_TEXT_DowerLvZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_DowerLvZ );
	m_pID_TEXT_TEXTZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_TEXTZ );
	m_pID_LIST_IconName = (ControlList*)theUiManager.FindControl( ID_FRAME_PetCard, ID_LIST_IconName );
	m_pID_LISTIMG_Icon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetCard, ID_LISTIMG_Icon );
	m_pID_TEXT_TEXTZ0 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_TEXTZ0 );
	m_pID_TEXT_Introduce = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_Introduce );
	m_pID_TEXT_TEXTZ1 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_TEXTZ1 );
	m_pID_TEXT_Address = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_Address );
	m_pID_BUTTON_PageUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCard, ID_BUTTON_PageUp );
	m_pID_BUTTON_PageDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCard, ID_BUTTON_PageDown );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_Page );
	m_pID_BUTTON_Return = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCard, ID_BUTTON_Return );
	m_pID_PICTURE_LeiBieWu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_LeiBieWu );
	m_pID_PICTURE_LeiBieFa = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_LeiBieFa );
	m_pID_PICTURE_WXTu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_WXTu );
	m_pID_PICTURE_WXJin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_WXJin );
	m_pID_PICTURE_WXMu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_WXMu );
	m_pID_PICTURE_WXShui = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_WXShui );
	m_pID_PICTURE_WXHuo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_WXHuo );
	m_pID_PICTURE_ZhongZuRen = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_ZhongZuRen );
	m_pID_PICTURE_ZhongZuJi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_ZhongZuJi );
	m_pID_PICTURE_ZhongZuShou = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_ZhongZuShou );
	m_pID_PICTURE_ZhongZuXian = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_ZhongZuXian );
	m_pID_PICTURE_ZhongZuGui = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_ZhongZuGui );
	m_pID_PICTURE_ZhongZuYao = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_ZhongZuYao );
	m_pID_PICTURE_ZhongZuShen = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_ZhongZuShen );
	m_pID_PICTURE_ZhongZuMo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_ZhongZuMo );
	m_phyleIcon[EPhyle_MaxCount] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_Full );
	m_phyleIcon[EPhyle_Human] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_Ren );
	m_phyleIcon[EPhyle_Deity] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_Shen );
	m_phyleIcon[EPhyle_Immortal] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_Xian );
	m_phyleIcon[EPhyle_Machine] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_Ji );
	m_phyleIcon[EPhyle_Demon] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_Mo );
	m_phyleIcon[EPhyle_Ghost] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_Gui );
	m_phyleIcon[EPhyle_Bogey] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_Yao );
	m_phyleIcon[EPhyle_Beast] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_Shou );
	m_pID_PICTURE_ZiZhi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_ZiZhi );
	m_pID_LISTIMG_Genre = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetCard, ID_LISTIMG_Genre );
	m_pID_LISTIMG_CatchLv = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetCard, ID_LISTIMG_CatchLv );
	m_pID_TEXT_LiLZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_LiLZZ );
	m_pID_TEXT_LLZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_LLZZ );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_Name );
	m_pID_TEXT_MJZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCard, ID_TEXT_MJZZ );
	m_pID_LISTIMG_Icon_1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetCard, ID_LISTIMG_Icon_1 );
	m_pID_PICTURE_BianShen = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCard, ID_PICTURE_BianShen );
	m_pID_TEXT_NLZZ = (ControlText*)theUiManager.FindControl(ID_FRAME_PetCard,ID_TEXT_NLZZ);
	m_pID_CHECKBOX_ZiZhi = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_ZiZhi );
	m_pID_CHECKBOX_BianShen = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCard, ID_CHECKBOX_BianShen );
	m_pID_TEXT_CardAmount = (ControlText*)theUiManager.FindControl(ID_FRAME_PetCard,ID_TEXT_CardAmount);

	assert( m_pID_FRAME_PetCard );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_TitleTop );
	assert( m_pID_PICTURE_PetModel );
	assert( m_pID_BUTTON_ToLeft );
	assert( m_pID_BUTTON_ToRight );
	assert( m_pID_TEXT_Phyle );
	assert( m_pID_LISTIMG_CatchLv );
	assert( m_pID_TEXT_PetNameTitle );
	assert( m_pID_LIST_PetName );
	assert( m_pID_TEXT_Attribute );
	assert( m_pID_TEXT_Lv );
	assert( m_pID_LISTIMG_Genre );
	assert( m_pID_TEXT_DowerLvZ );
	assert( m_pID_TEXT_TEXTZ );
	assert( m_pID_LIST_IconName );
	assert( m_pID_LISTIMG_Icon );
	assert( m_pID_TEXT_TEXTZ0 );
	assert( m_pID_TEXT_Introduce );
	assert( m_pID_TEXT_TEXTZ1 );
	assert( m_pID_TEXT_Address );
	assert( m_pID_BUTTON_PageUp );
	assert( m_pID_BUTTON_PageDown );
	assert( m_pID_TEXT_Page );
	assert( m_pID_BUTTON_Return );
	assert( m_pID_PICTURE_LeiBieWu );
	assert( m_pID_PICTURE_LeiBieFa );
	assert( m_pID_PICTURE_WXTu );
	assert( m_pID_PICTURE_WXJin );
	assert( m_pID_PICTURE_WXMu );
	assert( m_pID_PICTURE_WXShui );
	assert( m_pID_PICTURE_WXHuo );
	assert( m_pID_PICTURE_ZhongZuRen );
	assert( m_pID_PICTURE_ZhongZuJi );
	assert( m_pID_PICTURE_ZhongZuShou );
	assert( m_pID_PICTURE_ZhongZuXian );
	assert( m_pID_PICTURE_ZhongZuGui );
	assert( m_pID_PICTURE_ZhongZuYao );
	assert( m_pID_PICTURE_ZhongZuShen );
	assert( m_pID_PICTURE_ZhongZuMo );
	assert( m_phyleIcon[EPhyle_MaxCount]);
	assert( m_phyleIcon[EPhyle_Human] );
	assert( m_phyleIcon[EPhyle_Deity] );
	assert( m_phyleIcon[EPhyle_Immortal] );
	assert( m_phyleIcon[EPhyle_Machine]);
	assert(m_phyleIcon[EPhyle_Demon] );
	assert( m_phyleIcon[EPhyle_Ghost]);
	assert( m_phyleIcon[EPhyle_Bogey]);
	assert( m_phyleIcon[EPhyle_Beast] );
	assert( m_pID_PICTURE_ZiZhi );
	assert( m_pID_TEXT_LiLZZ );
	assert( m_pID_TEXT_LLZZ );
	assert( m_pID_PICTURE_BianShen );
	assert( m_pID_TEXT_MJZZ );
	assert( m_pID_LISTIMG_Icon_1 );
	assert( m_pID_PICTURE_BianShen );
	assert( m_pID_TEXT_Name );
	assert(m_pID_TEXT_NLZZ);
	assert( m_pID_CHECKBOX_ZiZhi );
	assert( m_pID_CHECKBOX_BianShen );
	assert(m_pID_TEXT_CardAmount);
	SortControlGroup();
	m_pPlayerAnim = MeNew CPlayerAnim;
	m_pPlayer = MeNew CPlayer;
	m_pPlayer->SetAnim( m_pPlayerAnim );
	m_pPlayerAnim->SetPlayer( m_pPlayer );
	theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayer );
	m_pID_BUTTON_ToRight->SetLButtonDownFun(UIPetCard_RightLBD);
	m_pID_BUTTON_ToLeft->SetLButtonDownFun(UIPetCard_LeftLBD);
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SuAnimalCard::_UnLoadUI()
{
	m_pID_FRAME_PetCard = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TitleTop = NULL;
	m_pID_PICTURE_PetModel = NULL;
	m_pID_BUTTON_ToLeft = NULL;
	m_pID_BUTTON_ToRight = NULL;
	m_pID_TEXT_Phyle = NULL;
	m_pID_LISTIMG_CatchLv = NULL;
	m_pID_TEXT_PetNameTitle = NULL;
	m_pID_LIST_PetName = NULL;
	m_pID_TEXT_Attribute = NULL;
	m_pID_TEXT_Lv = NULL;
	m_pID_LISTIMG_Genre = NULL;
	m_pID_TEXT_Dower = NULL;
	m_pID_TEXT_DowerLvZ = NULL;
	m_pID_TEXT_TEXTZ = NULL;
	m_pID_LIST_IconName = NULL;
	m_pID_LISTIMG_Icon = NULL;
	m_pID_TEXT_TEXTZ0 = NULL;
	m_pID_TEXT_Introduce = NULL;
	m_pID_TEXT_TEXTZ1 = NULL;
	m_pID_TEXT_Address = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_Return = NULL;
	m_pID_TEXT_ForceZ = NULL;
	m_pID_TEXT_NimbusZ = NULL;
	m_pID_TEXT_StaminaZ = NULL;
	m_pID_TEXT_CelerityZ = NULL;
	m_pID_PICTURE_LeiBieWu = NULL;
	m_pID_PICTURE_LeiBieFa = NULL;
	m_pID_PICTURE_WXTu = NULL;
	m_pID_PICTURE_WXJin = NULL;
	m_pID_PICTURE_WXMu = NULL;
	m_pID_PICTURE_WXShui = NULL;
	m_pID_PICTURE_WXHuo = NULL;
	m_pID_PICTURE_ZhongZuRen = NULL;
	m_pID_PICTURE_ZhongZuJi = NULL;
	m_pID_PICTURE_ZhongZuShou = NULL;
	m_pID_PICTURE_ZhongZuXian = NULL;
	m_pID_PICTURE_ZhongZuGui = NULL;
	m_pID_PICTURE_ZhongZuYao = NULL;
	m_pID_PICTURE_ZhongZuShen = NULL;
	m_pID_PICTURE_ZhongZuMo = NULL;
	m_phyleIcon[EPhyle_MaxCount] = NULL;
	m_phyleIcon[EPhyle_Human] = NULL;
	m_phyleIcon[EPhyle_Deity]  = NULL;
	m_phyleIcon[EPhyle_Immortal] = NULL;
	m_phyleIcon[EPhyle_Machine] = NULL;
	m_phyleIcon[EPhyle_Demon] = NULL;
	m_phyleIcon[EPhyle_Ghost] = NULL;
	m_phyleIcon[EPhyle_Bogey] = NULL;
	m_phyleIcon[EPhyle_Beast] = NULL;
	m_pID_PICTURE_ZiZhi = NULL;
	m_pID_PICTURE_Force = NULL;
	m_pID_PICTURE_Nimbus = NULL;
	m_pID_PICTURE_Stamina = NULL;
	m_pID_PICTURE_Celerity = NULL;
	m_pID_TEXT_DowerLv = NULL;
	m_pID_TEXT_LiLZZ = NULL;
	m_pID_TEXT_LLZZ = NULL;
	m_pID_TEXT_MJZZ = NULL;
	m_pID_LISTIMG_Icon_1 = NULL;
	m_pID_PICTURE_BianShen = NULL;
	m_pID_TEXT_NLZZ = NULL;
		m_pID_CHECKBOX_ZiZhi = NULL;
	m_pID_CHECKBOX_BianShen = NULL;
	if (m_pPlayer != NULL)
	{
	m_pID_PICTURE_BianShen = NULL;
	m_pID_TEXT_Name = NULL;
		delete m_pPlayer;
		m_pPlayer = 0;
		m_pPlayerAnim = 0;
	}

	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimalCard.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SuAnimalCard::_IsVisable()
{
	if ( !m_pID_FRAME_PetCard )
		return false;
	return m_pID_FRAME_PetCard->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SuAnimalCard::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_PetCard )
		return ;
	m_pID_FRAME_PetCard->SetVisable( bVisable );
	if (bVisable)
	{
		theUiManager.ToTop(m_pID_FRAME_PetCard);
	}
	
}

void CUI_ID_FRAME_SuAnimalCard::RefreshPage(ItemDefine::SPetMonster *m_pet,int phyle)
{
	if ( !m_pID_FRAME_PetCard )
		return ;
	if (m_pet != NULL)
	{
		m_pID_TEXT_Name->SetText(m_pet->GetName());
		m_pID_TEXT_Introduce->SetText(m_pet->GetPetDesc());
		std::vector<UiCallbackDataBase*> CallBackDataArr;
		std::string strName(m_pet->GetPetBornDesc());
		//去除名字前面的空格
		if (strName.length() >0)
		{
			strName.erase(0,strName.find_first_not_of(" "));
		}
		NpcCoord::getInstance()->addNpcHyberForText( strName, NpcCoord::eMapId, -1,-1,&CallBackDataArr );
		m_pID_TEXT_Address->SetText(strName,0,&CallBackDataArr);
		SetPhyle(m_pet->phyle);
		m_pID_TEXT_Phyle->SetText(s_CUI_ID_FRAME_SuAnimalCardList.GetPhyleInfo(m_pet->phyle));
		SetElement(m_pet->element);
		SetBaseProperty(m_pet);
		m_pID_TEXT_Lv->SetText(m_pet->takeLevel);
		char temp[32] = {0};
		int m_allNum = m_pet->identifyTotal;
		int m_currentNum = 0;
		if(s_CUI_ID_FRAME_SuAnimalCardList.GetSIdentifyData(m_pet->petType) != NULL)
		{
			m_currentNum = s_CUI_ID_FRAME_SuAnimalCardList.GetSIdentifyData(m_pet->petType)->identifyTotal;
			MeSprintf_s(temp,sizeof(temp),"%d/%d",m_currentNum,m_allNum);
			m_pID_TEXT_CardAmount->SetText(temp);
		}
		else
		{
			MeSprintf_s(temp,sizeof(temp),"%d/%d",m_currentNum,m_allNum);
			m_pID_TEXT_CardAmount->SetText(temp);
		}
		//ChangeModel(m_pet->iModelID,m_pPlayerAnim,m_nModelId);
		SetCurrPetTypePic(m_pet->petType);
		m_pID_LISTIMG_Icon->Clear();
		for (int i =0; i<ItemDefine::SPetMonster::EPet_DropItemIDCount; i++)
		{
 			if (m_pet->dropItemIds[i] != 0)
 			{
 				ControlIconDrag::S_ListImg stListItem;
 				stListItem.SetData(m_pet->dropItemIds[i],1);
 				m_pID_LISTIMG_Icon->SetItem(&stListItem);
 			}
		}
		
		m_currentphyle = phyle;
		m_currentPetId = m_pet->stMonsterId;
		for (int i =0; i< m_vecPetMonster.size(); i++)
		{
			if (m_vecPetMonster[i]->petType == m_pet->petType )
			{
				SetCurrPage(i+1);
				break;
			}
			
		}		
		
		RefreshCheckBoxStatus(m_currentphyle);
	}
}

bool CUI_ID_FRAME_SuAnimalCard::UIPetCard_LeftLBD(INT nX, INT nY)
{
	
		s_CUI_ID_FRAME_SuAnimalCard.SetRotate(true);
		return true;
}

bool CUI_ID_FRAME_SuAnimalCard::UIPetCard_RightLBD(INT nX, INT nY)
{

		s_CUI_ID_FRAME_SuAnimalCard.SetRotate(true);
		return true;
}

void CUI_ID_FRAME_SuAnimalCard::RenderViewport()
{
// 	if (!m_pID_FRAME_PetCard) return ;
// 	RECT rc;
// 	m_pID_PICTURE_PetModel->GetRealRect(&rc);
// 	RenderMount(m_nModelId,m_pPlayerAnim,m_fRotateZ,rc);
}

void CUI_ID_FRAME_SuAnimalCard::RenderMount(int nMountId, CPlayerAnim *pAnim, float fRotateZ, const RECT &rt)
{
// 	if (!m_pID_FRAME_PetCard) return;
// 	if( nMountId < 0 )
// 		return;
// 
// 	MeCamera camera;
// 	D3DVIEWPORT9 viewPort;
// 	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
// 	IRenderer* r = GetEngine()->GetRenderer();
// 
// 	viewPort.X = rt.left;
// 	viewPort.Y = rt.top;
// 	viewPort.Width = rt.right - rt.left;
// 	viewPort.Height = rt.bottom - rt.top;
// 	viewPort.MinZ = 0.0f;
// 	viewPort.MaxZ = 1.0f;
// 
// 	r->SetViewport( &viewPort );
// 	r->BeginScene();
// 	r->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );
// 
// 	RECT rcDst = 
// 	{
// 		viewPort.X, viewPort.Y, viewPort.X+viewPort.Width, viewPort.Y + viewPort.Height
// 	};
// 
// 	RECT rcSrc =
// 	{
// 		0, 0, viewPort.Width, viewPort.Height
// 	};
// 
// 	GetDrawer()->FillRect2D(rcDst, 0);
// 
// 	FLOAT fAspect = ((FLOAT)viewPort.Width) / (float)viewPort.Height;
// 	camera.SetProjParams( D3DX_PI/180*45.0f, fAspect, 1.0f, 12000.0f );
// 
// 	D3DXMATRIX matView;
// 	D3DXMATRIX matWorld, matOldWorld;
// 	D3DXMATRIX matRotation;
// 	D3DXMATRIX matTranslation;
// 	D3DXMATRIX matTransform1;
// 
// 	static float x = 0.f, y = -18.f, z = -1.8f;
// 	DWORD dwTime = HQ_TimeGetTime();
// 	if( pAnim )
// 	{
// 		pAnim->SetPosition( x, y, z );
// 		pAnim->CalcTransformMatrix( (MeMatrix*)&matTransform1 );
// 		pAnim->Update( dwTime, (MeMatrix*)&matTransform1 );
// 		pAnim->UpdateComponents( dwTime, (MeMatrix*)&matTransform1 );
// 	}
// 
// 	static float fDist = 22.79;
// 	static float fRotate = 0.0f;
// 	static float fRotateX = 0.98199f;
// 	static D3DXVECTOR3 vEyePt( 0,-1.2f,1.7f );
// 	static D3DXVECTOR3 vLookatPt( 0.0f,0.0f,0.0f );
// 
// 	D3DXVECTOR3 vDist = vEyePt-vLookatPt;
// 	D3DXVec3Normalize( &vDist, &vDist );
// 
// 	D3DXVECTOR3 vXAxis( 1, 0, 0 );
// 	D3DXMATRIX matRotX;
// 	D3DXMatrixRotationAxis(
// 		&matRotX,
// 		&vXAxis,
// 		fRotateX );
// 
// 	D3DXVec3TransformCoord( &vDist, &vDist, &matRotX );
// 
// 	D3DXVECTOR3 vZAxis( 0, 0, -1 );
// 	D3DXMATRIX matRotZ;
// 	D3DXMatrixRotationAxis(
// 		&matRotZ,
// 		&vZAxis,
// 		fRotate );
// 
// 	D3DXVec3TransformCoord( &vDist, &vDist, &matRotZ );
// 
// 	D3DXVECTOR3 vPos( 0, 0, 0 );
// 	camera.SetViewParams( vPos+vDist*fDist, vPos, D3DXVECTOR3( 0, 0, 1 ) );
// 	r->SetTransform( D3DTS_VIEW, (FLOAT*)&camera.GetViewMatrix() );
// 	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&camera.GetProjMatrix() );
// 	r->SetEyePt( (float*)&vEyePt );	
// 	r->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
// 	r->SetRenderState( D3DRS_LIGHTING, TRUE );	
// 	r->SetRenderState( D3DRS_FOGENABLE , false );	
// 
// 	bool bUseShader = graphics::ShaderManager::instance()->isUseShader();
// 
// 	RendererDx* pRendererDx = (RendererDx*)r;
// 	D3DXVECTOR3 vOldLightDir = pRendererDx->GetLightDir( LIGHT_INDEX_TERRAIN );
// 	D3DXVECTOR3 vNewLightDir = vOldLightDir;	
// 	vNewLightDir = vDist;
// 	D3DXVec3Normalize( &vNewLightDir, &vNewLightDir );
// 	D3DLIGHT9 kOldLight = SwGlobal::GetRender()->GetD9Light();
// 	D3DLIGHT9 kLight;
// 	kLight.Type = D3DLIGHT_DIRECTIONAL;	
// 	kLight.Ambient = D3DXCOLOR( 0.6f, 0.6f, 0.6f, 1.0f );
// 	kLight.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
// 	kLight.Specular = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
// 	kLight.Direction = vNewLightDir;	
// 	pRendererDx->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kLight );
// 	Config::SetCamera(&camera);
// 
// 	pAnim->SetRotationZ( fRotateZ );
// 	pAnim->SetUpperRot( fRotateZ );
// 
// 	pAnim->Render( 1.0f );
// 	GetEngine()->GetRenderer()->Flush( eSortByFarZ );
// 	MeRenderManager::Instance()->DoRender(false);
// 
// 	Config::SetCamera(getwsCamera()->GetMeCamera());
// 	pRendererDx->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kOldLight );
// 
// 	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&getwsCamera()->GetMeCamera()->GetProjMatrix()  );
// 	r->SetTransform( D3DTS_VIEW, (FLOAT*)&getwsCamera()->GetMeCamera()->GetViewMatrix()  );
// 	r->EndScene();
// 
// 	getwsCamera()->ResetViewport();
}

void CUI_ID_FRAME_SuAnimalCard::ChangeModel(int mountId, CPlayerAnim* pAnim, int& iOldModelId )
{
// 	if (!m_pID_FRAME_PetCard) return ;
// 	int nModelId = mountId;
// 	if( iOldModelId == nModelId )
// 		return;
// 	iOldModelId = nModelId;
// 	if( pAnim != NULL)
// 	{
// 		pAnim->MyChangeModel(mountId, TRUE, NULL );
// 		pAnim->SetCurAnimType(-1);
// 	}
}

void CUI_ID_FRAME_SuAnimalCard::SetElement(int n_element)
{
	m_pID_PICTURE_WXJin->SetVisable(false);
	m_pID_PICTURE_WXTu->SetVisable(false);
	m_pID_PICTURE_WXMu->SetVisable(false);
	m_pID_PICTURE_WXShui->SetVisable(false);
	m_pID_PICTURE_WXHuo->SetVisable(false);
	switch(n_element)
	{
	case FiveElements_Metal:  //金
		m_pID_PICTURE_WXJin->SetVisable(true);
		break;
	case FiveElements_Wood:  //木
	 	m_pID_PICTURE_WXMu->SetVisable(true);
		break;
	case FiveElements_Water:  //水
	 	m_pID_PICTURE_WXShui->SetVisable(true);
		break;
	case FiveElements_Fire:		//火
		 m_pID_PICTURE_WXHuo->SetVisable(true);
		break;
	case FiveElements_Earth:	//土
		 m_pID_PICTURE_WXTu->SetVisable(true);
		break;
	}
}

void CUI_ID_FRAME_SuAnimalCard::SetAttackType(int n_index)
{

}

void CUI_ID_FRAME_SuAnimalCard::SetPhyle(int n_id)
{
	m_pID_PICTURE_ZhongZuRen->SetVisable(false);
	m_pID_PICTURE_ZhongZuJi->SetVisable(false);
	m_pID_PICTURE_ZhongZuShou->SetVisable(false);
	m_pID_PICTURE_ZhongZuShen->SetVisable(false);
	m_pID_PICTURE_ZhongZuGui->SetVisable(false);
	m_pID_PICTURE_ZhongZuMo->SetVisable(false);
	m_pID_PICTURE_ZhongZuYao->SetVisable(false);
	m_pID_PICTURE_ZhongZuXian->SetVisable(false);
	switch(n_id)
	{
	case EPhyle_Human:
		m_pID_PICTURE_ZhongZuRen->SetVisable(true);
		break;
	case EPhyle_Machine:
		m_pID_PICTURE_ZhongZuJi->SetVisable(true);
		break;
	case EPhyle_Beast:
		m_pID_PICTURE_ZhongZuShou->SetVisable(true);
		break;
	case EPhyle_Immortal:
		m_pID_PICTURE_ZhongZuXian->SetVisable(true);
		break;
	case EPhyle_Ghost:
		m_pID_PICTURE_ZhongZuGui->SetVisable(true);
		break;
	case EPhyle_Bogey:
		m_pID_PICTURE_ZhongZuYao->SetVisable(true);
		break;
	case EPhyle_Deity:
		m_pID_PICTURE_ZhongZuShen->SetVisable(true);
		break;
	case EPhyle_Demon:
		m_pID_PICTURE_ZhongZuMo->SetVisable(true);
		break;
	}
}

void CUI_ID_FRAME_SuAnimalCard::SetCatchLvl(int n_id)
{

}

void CUI_ID_FRAME_SuAnimalCard::SetTakeLevel(int n_id)
{

}

void CUI_ID_FRAME_SuAnimalCard::SetBaseProperty(ItemDefine::SPetMonster *m_pet)
{
	if (m_pet != NULL)
	{
		m_GroupZiZhi.SetVisible(true);
		m_GroupBianShen.SetVisible(false);
		m_pID_LISTIMG_Icon_1->Clear();
		m_pID_TEXT_LiLZZ->SetText(m_pet->aptitudeAttr[EBaseAttr_Strength]);
		m_pID_TEXT_LLZZ->SetText(m_pet->aptitudeAttr[EBaseAttr_Intelligence]);
		m_pID_TEXT_MJZZ->SetText(m_pet->aptitudeAttr[EBaseAttr_Agility]);
		m_pID_TEXT_NLZZ->SetText(m_pet->aptitudeAttr[EBaseAttr_Stamina]);
		ControlIconDrag::S_ListImg stListItem;
		stListItem.SetData(m_pet->talentSkillId,1);
		m_pID_LISTIMG_Icon_1->SetItem(&stListItem);
	}
}

void CUI_ID_FRAME_SuAnimalCard::SortControlGroup()
{
	m_GroupBianShen.Clear();
	m_GroupBianShen.AddControl(m_pID_PICTURE_BianShen);
// 	m_GroupBianShen.AddControl();
// 	m_GroupBianShen.AddControl();
// 	m_GroupBianShen.AddControl();

	m_GroupZiZhi.Clear();
	m_GroupZiZhi.AddControl(m_pID_PICTURE_ZiZhi);
	m_GroupZiZhi.AddControl(m_pID_TEXT_LiLZZ);
	m_GroupZiZhi.AddControl(m_pID_TEXT_LLZZ);
	m_GroupZiZhi.AddControl(m_pID_TEXT_MJZZ);
	m_GroupZiZhi.AddControl(m_pID_LISTIMG_Icon_1);
	m_GroupZiZhi.AddControl(m_pID_TEXT_NLZZ);
}

void CUI_ID_FRAME_SuAnimalCard::RefreshCheckBoxStatus(int m_currentPhyle)
{
	for (int i =0; i<(EPhyle_MaxCount+1); i++ )
	{
		m_phyleIcon[i]->SetCheck(false);
	}
	switch(m_currentPhyle)
	{
	case EPhyle_Human:
		m_phyleIcon[EPhyle_Human]->SetCheck(true);
		break;
	case EPhyle_Machine:
		m_phyleIcon[EPhyle_Machine]->SetCheck(true);
		break;
	case EPhyle_Beast:
		m_phyleIcon[EPhyle_Beast]->SetCheck(true);
		break;
	case EPhyle_Immortal:
		m_phyleIcon[EPhyle_Immortal]->SetCheck(true);
		break;
	case EPhyle_Ghost:
		m_phyleIcon[EPhyle_Ghost]->SetCheck(true);
		break;
	case EPhyle_Bogey:
		m_phyleIcon[EPhyle_Bogey]->SetCheck(true);
		break;
	case EPhyle_Deity:
		m_phyleIcon[EPhyle_Deity]->SetCheck(true);
		break;
	case EPhyle_Demon:
		m_phyleIcon[EPhyle_Demon]->SetCheck(true);
		break;
	default:
		m_phyleIcon[EPhyle_MaxCount]->SetCheck(true);
		//SetCurrPetTypePic(0); //zhuxincong  8.31 注释
		break;
	}
}

void CUI_ID_FRAME_SuAnimalCard::SetCurrentPhyle(std::vector<ItemDefine::SPetMonster*> &m_vecPet)
{
	m_vecPetMonster = m_vecPet;	
}

void CUI_ID_FRAME_SuAnimalCard::SetCurrPage(int nindex)
{
	if (m_pID_TEXT_Page != NULL)
	{
		char temp[64] = {0};
		int m_size = m_vecPetMonster.size();
		MeSprintf_s(temp,sizeof(temp),"%d/%d",nindex,m_size);
		m_pID_TEXT_Page->SetText(temp);
	}
}

void CUI_ID_FRAME_SuAnimalCard::SetCurrPetTypePic(int pettype)
{
	char temp[256] = {0};
	if (pettype != 0)
	{
		MeSprintf_s(temp,sizeof(temp),"%s/Data/ui/PetPicture/PetType%d.dds",GetRootPath(),pettype);
	}
	f_Handle *fp = packet_namespace::w_fopen(temp,"r");
	if (fp == NULL)
	{
		MeSprintf_s(temp,sizeof(temp),"ui\\PetPicture\\PetTypeDefault.dds");
	}
	m_pID_PICTURE_PetModel->SetPicName(temp);
}