/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\宠物\PetUp.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimalUp.h"
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
CUI_ID_FRAME_SuAnimalUp s_CUI_ID_FRAME_SuAnimalUp;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimalUp, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimalUp, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalUp, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalUp, ID_BUTTON_CLOSEOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalUp, ID_LIST_PetNameOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalUp, ID_BUTTON_SureOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalUp, ID_BUTTON_ExamineOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalUp, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalUp, ID_BUTTON_Choice0OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalUp, ID_BUTTON_Choice1OnButtonClick )
CUI_ID_FRAME_SuAnimalUp::CUI_ID_FRAME_SuAnimalUp()
{
	// Member
	m_pID_FRAME_PetUp = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TitleTop = NULL;
	m_pID_PICTURE_Motherboard = NULL;
	m_pID_TEXT_PetNameTitle = NULL;
	m_pID_LIST_PetName = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_BUTTON_Examine = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_TEXT_NowApperception = NULL;
	m_pID_TEXT_Probability = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Explain0 = NULL;
	m_pID_TEXT_TextZ0 = NULL;
	m_pID_TEXT_PetName0 = NULL;
	m_pID_BUTTON_Choice0 = NULL;
	m_pID_TEXT_TextZ1 = NULL;
	m_pID_TEXT_PetName1 = NULL;
	m_pID_BUTTON_Choice1 = NULL;
	m_pID_TEXT_ConsumeMoney = NULL;
	m_pID_TEXT_LockedMoney = NULL;
	m_pID_TEXT_CurrentMoney = NULL;
	m_pID_TEXT_NowGenGu = NULL;
	m_CurrentSelectPet = -1;
}
// Frame
bool CUI_ID_FRAME_SuAnimalUp::OnFrameRun()
{
	int nSroollBarHeight = 0;
	if (s_CUI_ID_FRAME_SuAnimalUp.IsVisable())
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
	}
	m_pID_LIST_PetName->SetShowStartHeight(m_nLastHeight);
	m_pID_LIST_PetName->SetScrollValue(nSroollBarHeight);
	return true;
}
bool CUI_ID_FRAME_SuAnimalUp::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalUp::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetUp )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalUp::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetUp )
		return false;
	return ID_BUTTON_CancelOnButtonClick(pSender);
}
// List
void CUI_ID_FRAME_SuAnimalUp::ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_PetUp )    return;
	RefreshPetList();
	RefreshMoney();
}
// Button
bool CUI_ID_FRAME_SuAnimalUp::ID_BUTTON_SureOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetUp )
		return false;
	if (m_UpData.m_srcGenGu <= m_UpData.m_GenGu)  //材料宠物的根骨必须要大于被提升宠物的悟性
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetBoneNotEnough));
		return false;
	}
	if (m_UpData.nDstPetGuid != m_UpData.nSrcPetGuid) //非自身
	{
		MsgPetSavvyUp msg;
		msg.nDstPetGuid = m_UpData.nDstPetGuid;
		msg.nDstPetIndex = m_UpData.nDstPetIndex;
		msg.nSrcPetGuid  = m_UpData.nSrcPetGuid;
		msg.nSrcPetIndex = m_UpData.nSrcPetIndex;
		GettheNetworkInput().SendMsg(&msg);
		return true;
	}
	else
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSelectFirst) );
		return true;
	}
	
	return false;
}
// Button
bool CUI_ID_FRAME_SuAnimalUp::ID_BUTTON_ExamineOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetUp )
		return false;
	int n_index = m_pID_LIST_PetName->GetCurSelIndex();
	s_CUI_ID_FRAME_SuAnimal.LookPet(n_index);
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalUp::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetUp )
		return false;
	m_pID_TEXT_PetName0->SetText("");
	m_pID_TEXT_PetName1->SetText("");
// 	m_pID_BUTTON_Choice0->SetCaption("选择珍兽");
// 	m_pID_BUTTON_Choice1->SetCaption("选择珍兽");
	memset(&m_UpData,0,sizeof(PetUp_Struct));
	RefreshMoney();
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalUp::ID_BUTTON_Choice0OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetUp || m_pID_LIST_PetName == NULL)
		return false;
	int n_index =m_pID_LIST_PetName->GetCurSelIndex(); 
	if (n_index >= 0)
	{
		SPetItem &mount = thePlayerRole.GetPetByIndex(n_index);
		if (mount.baseInfo.petId != InvalidLogicNumber)
		{
			m_CurrentSelectPet = mount.baseInfo.guid;
			ItemDefine::SPetMonster* m_petMonster = GettheItemDetail().GetPetById(mount.baseInfo.petId);
			if (m_petMonster == NULL)  return false;

			if (!m_petMonster->bIsBaby || mount.baseInfo.savvy >= MaxSavvy )
			{
				//悟性满十级或者是成年宠物的话，不能够被提升悟性，只能用作材料宠物
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSavvyFull) );
				return false;
			}
			if (mount.baseInfo.isActive)
			{
				//当前宠物处于出战状态，不能够被提升悟性
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetIsActivedCannotSelect) );
				return false;
			}
			m_pID_TEXT_PetName0->SetText(mount.baseInfo.szName);
			m_pID_TEXT_NowApperception->SetText(mount.baseInfo.savvy);//设置当前悟性
			m_UpData.nDstPetGuid = mount.baseInfo.guid;
			m_UpData.nDstPetIndex = n_index;
			m_UpData.petType         = m_petMonster->petType;
			m_UpData.m_GenGu       = mount.baseInfo.savvy;
			RefreshMonsy(mount);
		}
	}
	else
	{//选择宠物失败
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetFailSelect) );
	}
	RefreshPetList();
	return false;
}
// Button
bool CUI_ID_FRAME_SuAnimalUp::ID_BUTTON_Choice1OnButtonClick( ControlObject* pSender )
{
	if ( m_pID_FRAME_PetUp == NULL || m_pID_LIST_PetName == NULL)  return false;
	int n_index = m_pID_LIST_PetName->GetCurSelIndex();
	if (n_index >= 0)
	{
		SPetItem &mount = thePlayerRole.GetPetByIndex(n_index);
		if (mount.baseInfo.petId != InvalidLogicNumber)
		{
			ItemDefine::SPetMonster* m_petMonster = GettheItemDetail().GetPetById(mount.baseInfo.petId);
			if (m_petMonster == NULL)  return false;
			m_UpData.m_srcGenGu = mount.baseInfo.bone;
			if (m_petMonster->petType != m_UpData.petType || m_petMonster->bIsBaby || mount.baseInfo.isActive)
			{
				//类型不匹配或者未成年的不能作为材料
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetCannotMaterial) );
				return false;
			}
			if (m_UpData.nDstPetGuid == InvalidLogicNumber && m_UpData.nDstPetIndex <=0)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSelectFirst) );
				return false;
			}

			if (m_UpData.nSrcPetGuid == m_UpData.nDstPetGuid && m_UpData.nDstPetGuid !=0)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_SelectSamePet) );
				return false;
			}
			m_pID_TEXT_PetName1->SetText(mount.baseInfo.szName);
			if (m_UpData.m_srcGenGu <= m_UpData.m_GenGu)  //材料宠物的根骨必须要大于被提升宠物的悟性
			{
				DWORD m_color = Color_Config.getColor(CC_PetColor_Red);
				m_pID_TEXT_NowGenGu->SetText(mount.baseInfo.bone,m_color);
			}
			else
			{
				m_pID_TEXT_NowGenGu->SetText(mount.baseInfo.bone);
			}
			m_UpData.nSrcPetGuid = mount.baseInfo.guid;
			m_UpData.nSrcPetIndex = n_index;
		}
	}
	else
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetFailSelect));
	}
	RefreshPetList();
	return false;
}

// 装载UI
bool CUI_ID_FRAME_SuAnimalUp::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimalUp.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuAnimalUp.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuAnimalUp::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PetUp, s_CUI_ID_FRAME_SuAnimalUpOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PetUp, s_CUI_ID_FRAME_SuAnimalUpOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PetUp, ID_BUTTON_HELP,s_CUI_ID_FRAME_SuAnimalUpID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetUp, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SuAnimalUpID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_PetUp, ID_LIST_PetName, s_CUI_ID_FRAME_SuAnimalUpID_LIST_PetNameOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_PetUp, ID_BUTTON_Sure, s_CUI_ID_FRAME_SuAnimalUpID_BUTTON_SureOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetUp, ID_BUTTON_Examine, s_CUI_ID_FRAME_SuAnimalUpID_BUTTON_ExamineOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetUp, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SuAnimalUpID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetUp, ID_BUTTON_Choice0, s_CUI_ID_FRAME_SuAnimalUpID_BUTTON_Choice0OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetUp, ID_BUTTON_Choice1, s_CUI_ID_FRAME_SuAnimalUpID_BUTTON_Choice1OnButtonClick );

	m_pID_FRAME_PetUp = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetUp );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetUp, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetUp, ID_BUTTON_CLOSE );
	m_pID_TEXT_TitleTop = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_TitleTop );
	m_pID_PICTURE_Motherboard = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetUp, ID_PICTURE_Motherboard );
	m_pID_TEXT_PetNameTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_PetNameTitle );
	m_pID_LIST_PetName = (ControlList*)theUiManager.FindControl( ID_FRAME_PetUp, ID_LIST_PetName );
	m_pID_BUTTON_Sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetUp, ID_BUTTON_Sure );
	m_pID_BUTTON_Examine = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetUp, ID_BUTTON_Examine );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_Explain );
	m_pID_TEXT_NowApperception = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_NowApperception );
	m_pID_TEXT_Probability = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_Probability );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetUp, ID_BUTTON_Cancel );
	m_pID_TEXT_Explain0 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_Explain0 );
	m_pID_TEXT_TextZ0 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_TextZ0 );
	m_pID_TEXT_PetName0 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_PetName0 );
	m_pID_BUTTON_Choice0 = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetUp, ID_BUTTON_Choice0 );
	m_pID_TEXT_TextZ1 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_TextZ1 );
	m_pID_TEXT_PetName1 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_PetName1 );
	m_pID_BUTTON_Choice1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetUp, ID_BUTTON_Choice1 );
	m_pID_TEXT_ConsumeMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_ConsumeMoney );
	m_pID_TEXT_LockedMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_LockedMoney );
	m_pID_TEXT_CurrentMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_CurrentMoney );
	m_pID_TEXT_NowGenGu = (ControlText*)theUiManager.FindControl( ID_FRAME_PetUp, ID_TEXT_NowGenGu );
	assert( m_pID_FRAME_PetUp );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_TitleTop );
	assert( m_pID_PICTURE_Motherboard );
	assert( m_pID_TEXT_PetNameTitle );
	assert( m_pID_LIST_PetName );
	assert( m_pID_BUTTON_Sure );
	assert( m_pID_BUTTON_Examine );
	assert( m_pID_TEXT_Explain );
	assert( m_pID_TEXT_NowApperception );
	assert( m_pID_TEXT_Probability );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_Explain0 );
	assert( m_pID_TEXT_TextZ0 );
	assert( m_pID_TEXT_PetName0 );
	assert( m_pID_BUTTON_Choice0 );
	assert( m_pID_TEXT_TextZ1 );
	assert( m_pID_TEXT_PetName1 );
	assert( m_pID_BUTTON_Choice1 );
	assert( m_pID_TEXT_ConsumeMoney );
	assert( m_pID_TEXT_LockedMoney );
	assert( m_pID_TEXT_CurrentMoney );
	assert(m_pID_TEXT_NowGenGu);
	SetVisable(false);
	m_pID_TEXT_PetName0->SetText("");
	m_pID_TEXT_PetName1->SetText("");
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SuAnimalUp::_UnLoadUI()
{
	m_pID_FRAME_PetUp = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TitleTop = NULL;
	m_pID_PICTURE_Motherboard = NULL;
	m_pID_TEXT_PetNameTitle = NULL;
	m_pID_LIST_PetName = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_BUTTON_Examine = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_TEXT_NowApperception = NULL;
	m_pID_TEXT_Probability = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Explain0 = NULL;
	m_pID_TEXT_TextZ0 = NULL;
	m_pID_TEXT_PetName0 = NULL;
	m_pID_BUTTON_Choice0 = NULL;
	m_pID_TEXT_TextZ1 = NULL;
	m_pID_TEXT_PetName1 = NULL;
	m_pID_BUTTON_Choice1 = NULL;
	m_pID_TEXT_ConsumeMoney = NULL;
	m_pID_TEXT_LockedMoney = NULL;
	m_pID_TEXT_CurrentMoney = NULL;
	m_pID_TEXT_NowGenGu = NULL;
	m_UpData.nDstPetGuid = InvalidLogicNumber;
	m_UpData.nDstPetIndex = -1;
	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimalUp.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SuAnimalUp::_IsVisable()
{
	if ( !m_pID_FRAME_PetUp )
		return false;
	return m_pID_FRAME_PetUp->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SuAnimalUp::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_PetUp )
		return ;
	m_pID_FRAME_PetUp->SetVisable( bVisable );
	if (bVisable)
	{
		Refresh(false);
		RefreshPetList();
		//PlaySoundConfig(SoundConfig::EST_OpenPackUI);
	}
	else
	{
		m_CurrentSelectPet = -1;
	}
}

void CUI_ID_FRAME_SuAnimalUp::Refresh_Help(bool _is)
{
	if (!IsVisable())
		return;
	int nSelId = m_pID_LIST_PetName->GetCurSelIndex();
	RefreshPetList();
	if (_is)
		m_pID_LIST_PetName->SetCurSelIndex(m_pID_LIST_PetName->GetListItemCnt() - 1);
	else if (nSelId == -1)
		m_pID_LIST_PetName->SetCurSelIndex(0);
	else
		m_pID_LIST_PetName->SetCurSelIndex(nSelId);
	RefreshMoney();
}

void CUI_ID_FRAME_SuAnimalUp::RefreshMoney()
{
	if (!m_pID_FRAME_PetUp)   return ;
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

void CUI_ID_FRAME_SuAnimalUp::RefreshByMoneyChange()
{
	SPetItem *mount = NULL;
	if (m_CurrentSelectPet != -1)
	{
		mount = thePlayerRole.GetPetByGUID(m_CurrentSelectPet);
		RefreshMonsy(*mount);
	}
}
void CUI_ID_FRAME_SuAnimalUp::RefreshMonsy(SPetItem &mount)
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
	int m_rorate = thePetSettingConfig.GetSavvyUpEatRate(quality,m_level,mount.baseInfo.savvy); //提升成功率
	int money = thePetSettingConfig.GetSavvyUpEatMoney(quality,m_level,mount.baseInfo.savvy);//所需金钱
	if (m_pID_TEXT_ConsumeMoney != NULL)
	{
		std::string text;
		text.clear();
		thePlayerRole.GetGSCStringFromMoney(money,text);
		DWORD m_AllMoney = 0;
		m_AllMoney=  thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
		if (m_AllMoney < money)
		{
			DWORD m_color = Color_Config.getColor(CC_PetColor_Red);
			m_pID_TEXT_ConsumeMoney->SetText(text,m_color);
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
		m_pID_TEXT_Probability->SetText(m_rorate);
	}
}
void CUI_ID_FRAME_SuAnimalUp::RefreshProperty()
{
	m_pID_TEXT_PetName1->SetText("");
	m_pID_TEXT_NowGenGu->SetText("");
	m_pID_TEXT_Probability->SetText("");
	m_UpData.nSrcPetGuid = 0;
	m_UpData.nSrcPetIndex = -1;
	m_UpData.m_GenGu = 0;
	m_UpData.m_srcGenGu = 0;
	if (m_pID_FRAME_PetUp->IsVisable())
	{
		//int n_index =m_pID_LIST_PetName->GetCurSelIndex(); 
		SPetItem *mount = NULL;
		if (m_CurrentSelectPet != -1)
		{
			mount = thePlayerRole.GetPetByGUID(m_CurrentSelectPet);
		}
		else
		{
			m_pID_LIST_PetName->SetCurSelIndex(0);
			*mount = thePlayerRole.GetPetByIndex(0);
		}
		if (mount != NULL && mount->baseInfo.petId != InvalidLogicNumber)
		{
			if (mount->baseInfo.savvy >= MaxSavvy )
			{
				m_pID_TEXT_PetName0->SetText("");
				m_pID_TEXT_NowApperception->SetText("");
				m_pID_TEXT_ConsumeMoney->SetText("");
				memset(&m_UpData,0,sizeof(PetUp_Struct));
				m_pID_LIST_PetName->SetCurSelIndex(0);
				m_CurrentSelectPet = -1;
			}
			else
			{
				ItemDefine::SPetMonster* m_petMonster = GettheItemDetail().GetPetById(mount->baseInfo.petId);
				if(m_petMonster == NULL) return;
				int n_index = thePlayerRole.GetPetIndex(m_CurrentSelectPet);
				m_pID_LIST_PetName->SetCurSelIndex(n_index);
				m_pID_TEXT_PetName0->SetText(mount->baseInfo.szName);
				m_pID_TEXT_NowApperception->SetText(mount->baseInfo.savvy);//设置当前悟性
				m_UpData.nDstPetGuid = mount->baseInfo.guid;
				m_UpData.nDstPetIndex = n_index;
				m_UpData.petType         = m_petMonster->petType;
				m_UpData.m_GenGu		= mount->baseInfo.savvy;
				RefreshMonsy(*mount);
			}
		}
	}
	
	Refresh_Help(true);
}

void CUI_ID_FRAME_SuAnimalUp::RefreshPetList()
{
	int nSelId = m_pID_LIST_PetName->GetCurSelIndex();
	m_pID_LIST_PetName->Clear();

	int nMaxCount = thePetSettingConfig.GetPlayerPetLimit(thePlayerRole.GetLevel());
	for (int i = 0; i < nMaxCount; ++i)
	{
		DWORD dwColor = Color_Config.getColor(CC_PetColor_White);
		if (thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId != InvalidLogicNumber)
		{
			SPetItem pet = thePlayerRole.GetCharInfo2().ItemBagData.petItems[i];
			ControlList::S_List sData;
			// 取颜色
			ItemDefine::SPetMonster* m_petMonster = GettheItemDetail().GetPetById(pet.baseInfo.petId );
			SPetItem &mount = thePlayerRole.GetPetByIndex(nSelId);
			if (!pet.baseInfo.isActive && (m_petMonster != NULL &&( !m_petMonster->bIsBaby || pet.baseInfo.savvy >= MaxSavvy)))
			{
				dwColor = Color_Config.getColor(CC_PetColor_Taupe);
			}
			if (pet.baseInfo.isActive)
			{
				dwColor = Color_Config.getColor(CC_PetColor_Red);
			}
			if ( pet.baseInfo.guid == m_UpData.nDstPetGuid)
			{
				dwColor = Color_Config.getColor(CC_PetColor_Green);
			}
			if (pet.baseInfo.guid == m_UpData.nSrcPetGuid)
			{
				dwColor = Color_Config.getColor(CC_PetColor_Blue);
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