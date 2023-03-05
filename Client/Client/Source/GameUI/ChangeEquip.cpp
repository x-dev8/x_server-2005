/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\liuchuanpeng\桌面\ChangeEquip.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ChangeEquip.h"
#include "UserData.h"
#include "PlayerRole.h"
#include "GameSettingFunction.h"
#include "Pack.h"
#include "baseProperty.h"
#include "Rename.h"
#include "Dxsdk/dinput.h"
#include "color_config.h"
#include "shortcutkey_configure.h"
#include "ScreenInfoManager.h"

extern short GetKeyboardInput( int iKey );
extern GAME_STATE	g_GameState;

DWORD CUI_ID_FRAME_ChangeEquip::s_dwElapseTime = 1000;

CUI_ID_FRAME_ChangeEquip s_CUI_ID_FRAME_ChangeEquip;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ChangeEquip, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ChangeEquip, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChangeEquip, ID_BUTTON_SaveOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChangeEquip, ID_BUTTON_DeleteOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChangeEquip, ID_BUTTON_CloseOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChangeEquip, ID_CHECKBOX_1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChangeEquip, ID_CHECKBOX_2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChangeEquip, ID_CHECKBOX_3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChangeEquip, ID_CHECKBOX_4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChangeEquip, ID_CHECKBOX_5OnCheckBoxCheck )

CUI_ID_FRAME_ChangeEquip::CUI_ID_FRAME_ChangeEquip()
{
	// Member
	m_pID_FRAME_ChangeEquip = NULL;
	m_pID_BUTTON_Save = NULL;
// 	m_pID_BUTTON_Delete = NULL;
// 	m_pID_BUTTON_Close = NULL;
	m_pID_CHECKBOX_1 = NULL;
	m_pID_CHECKBOX_2 = NULL;
	m_pID_CHECKBOX_3 = NULL;
	m_pID_CHECKBOX_4 = NULL;
	m_pID_CHECKBOX_5 = NULL;
	m_pID_PICTURE_1 = NULL;
	m_pID_PICTURE_2 = NULL;
	m_pID_PICTURE_3 = NULL;
	m_pID_PICTURE_4 = NULL;
	m_pID_PICTURE_5 = NULL;

	m_CurrSuit = -1;
	m_dwCoolDown = 0;
}

// Frame
bool CUI_ID_FRAME_ChangeEquip::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_ChangeEquip::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_ChangeEquip::ID_BUTTON_SaveOnButtonClick( ControlObject* pSender )
{
	if(m_CurrSuit == -1)
		return false;

	if(CUserData::Instance()->AddSuit(m_CurrSuit))
		SaveSuit();
	return true;
}

// Button
// bool CUI_ID_FRAME_ChangeEquip::ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender )
// {
// 	if(m_CurrSuit == -1)
// 		return false;
// 
// 	CUserData::Instance()->ClearSuit(m_CurrSuit);
// 	return true;
// }
// 
// // Button
// bool CUI_ID_FRAME_ChangeEquip::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
// {
// 	SetVisable(false);
// 	return true;
// }

// CheckBox
void CUI_ID_FRAME_ChangeEquip::ID_CHECKBOX_1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_1->SetCheck(false);

	if(!IsCoolDowning())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_EquipChange_Failed, theXmlString.GetString(eChangeSuitCD) );
		if(m_CurrSuit == 0)
			m_pID_CHECKBOX_1->SetCheck(true);
		return;
	}

	m_CurrSuit = 0;
	SetSuit(0);
	ChangeSuit(0);
}

// CheckBox
void CUI_ID_FRAME_ChangeEquip::ID_CHECKBOX_2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_2->SetCheck(false);

	if(!IsCoolDowning())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_EquipChange_Failed, theXmlString.GetString(eChangeSuitCD) );
		if(m_CurrSuit == 1)
			m_pID_CHECKBOX_2->SetCheck(true);
		return;
	}

	m_CurrSuit = 1;
	SetSuit(1);
	ChangeSuit(1);
}

// CheckBox
void CUI_ID_FRAME_ChangeEquip::ID_CHECKBOX_3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_3->SetCheck(false);

	if(!IsCoolDowning())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_EquipChange_Failed, theXmlString.GetString(eChangeSuitCD) );
		if(m_CurrSuit == 2)
			m_pID_CHECKBOX_3->SetCheck(true);
		return;
	}

	m_CurrSuit = 2;
	SetSuit(2);
	ChangeSuit(2);
}

// CheckBox
void CUI_ID_FRAME_ChangeEquip::ID_CHECKBOX_4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_4->SetCheck(false);

	if(!IsCoolDowning())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_EquipChange_Failed, theXmlString.GetString(eChangeSuitCD) );
		if(m_CurrSuit == 3)
			m_pID_CHECKBOX_4->SetCheck(true);
		return;
	}

	m_CurrSuit = 3;
	SetSuit(3);
	ChangeSuit(3);
}

// CheckBox
void CUI_ID_FRAME_ChangeEquip::ID_CHECKBOX_5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_5->SetCheck(false);

	if(!IsCoolDowning())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_EquipChange_Failed, theXmlString.GetString(eChangeSuitCD) );
		if(m_CurrSuit == 4)
			m_pID_CHECKBOX_5->SetCheck(true);
		return;
	}

	m_CurrSuit = 4;
	SetSuit(4);
	ChangeSuit(4);
}

// 装载UI
bool CUI_ID_FRAME_ChangeEquip::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ChangeEquip.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ChangeEquip.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ChangeEquip::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ChangeEquip, s_CUI_ID_FRAME_ChangeEquipOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ChangeEquip, s_CUI_ID_FRAME_ChangeEquipOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ChangeEquip, ID_BUTTON_Save, s_CUI_ID_FRAME_ChangeEquipID_BUTTON_SaveOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_ChangeEquip, ID_BUTTON_Delete, s_CUI_ID_FRAME_ChangeEquipID_BUTTON_DeleteOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_ChangeEquip, ID_BUTTON_Close, s_CUI_ID_FRAME_ChangeEquipID_BUTTON_CloseOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChangeEquip, ID_CHECKBOX_1, s_CUI_ID_FRAME_ChangeEquipID_CHECKBOX_1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChangeEquip, ID_CHECKBOX_2, s_CUI_ID_FRAME_ChangeEquipID_CHECKBOX_2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChangeEquip, ID_CHECKBOX_3, s_CUI_ID_FRAME_ChangeEquipID_CHECKBOX_3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChangeEquip, ID_CHECKBOX_4, s_CUI_ID_FRAME_ChangeEquipID_CHECKBOX_4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChangeEquip, ID_CHECKBOX_5, s_CUI_ID_FRAME_ChangeEquipID_CHECKBOX_5OnCheckBoxCheck );

	m_pID_FRAME_ChangeEquip = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ChangeEquip );
	m_pID_BUTTON_Save = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_BUTTON_Save );
// 	m_pID_BUTTON_Delete = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_BUTTON_Delete );
// 	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_BUTTON_Close );
	m_pID_CHECKBOX_1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_CHECKBOX_1 );
	m_pID_CHECKBOX_2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_CHECKBOX_2 );
	m_pID_CHECKBOX_3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_CHECKBOX_3 );
	m_pID_CHECKBOX_4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_CHECKBOX_4 );
	m_pID_CHECKBOX_5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_CHECKBOX_5 );
	m_pID_PICTURE_1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_PICTURE_1 );
	m_pID_PICTURE_2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_PICTURE_2 );
	m_pID_PICTURE_3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_PICTURE_3 );
	m_pID_PICTURE_4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_PICTURE_4 );
	m_pID_PICTURE_5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChangeEquip, ID_PICTURE_5 );
	assert( m_pID_FRAME_ChangeEquip );
	assert( m_pID_BUTTON_Save );
// 	assert( m_pID_BUTTON_Delete );
// 	assert( m_pID_BUTTON_Close );
	assert( m_pID_CHECKBOX_1 );
	assert( m_pID_CHECKBOX_2 );
	assert( m_pID_CHECKBOX_3 );
	assert( m_pID_CHECKBOX_4 );
	assert( m_pID_CHECKBOX_5 );
	assert( m_pID_PICTURE_1 );
	assert( m_pID_PICTURE_2 );
	assert( m_pID_PICTURE_3 );
	assert( m_pID_PICTURE_4 );
	assert( m_pID_PICTURE_5 );

	m_pID_FRAME_ChangeEquip->SetMsgProcFun( frame_msg );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ChangeEquip::_UnLoadUI()
{
	m_pID_FRAME_ChangeEquip = NULL;
	m_pID_BUTTON_Save = NULL;
// 	m_pID_BUTTON_Delete = NULL;
// 	m_pID_BUTTON_Close = NULL;
	m_pID_CHECKBOX_1 = NULL;
	m_pID_CHECKBOX_2 = NULL;
	m_pID_CHECKBOX_3 = NULL;
	m_pID_CHECKBOX_4 = NULL;
	m_pID_CHECKBOX_5 = NULL;
	m_pID_PICTURE_1 = NULL;
	m_pID_PICTURE_2 = NULL;
	m_pID_PICTURE_3 = NULL;
	m_pID_PICTURE_4 = NULL;
	m_pID_PICTURE_5 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ChangeEquip.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ChangeEquip::_IsVisable()
{
	if( !m_pID_FRAME_ChangeEquip )
		return false;
	return m_pID_FRAME_ChangeEquip->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ChangeEquip::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_ChangeEquip )
		return;
	m_pID_FRAME_ChangeEquip->SetVisable( bVisable );
}

void CUI_ID_FRAME_ChangeEquip::SetSuit(int nIndex)
{
	m_pID_CHECKBOX_1->SetCheck(false);
	m_pID_CHECKBOX_2->SetCheck(false);
	m_pID_CHECKBOX_3->SetCheck(false);
	m_pID_CHECKBOX_4->SetCheck(false);
	m_pID_CHECKBOX_5->SetCheck(false);

	if(nIndex == 0)
		m_pID_CHECKBOX_1->SetCheck(true);
	else if(nIndex == 1)
		m_pID_CHECKBOX_2->SetCheck(true);
	else if(nIndex == 2)
		m_pID_CHECKBOX_3->SetCheck(true);
	else if(nIndex == 3)
		m_pID_CHECKBOX_4->SetCheck(true);
	else if(nIndex == 4)
		m_pID_CHECKBOX_5->SetCheck(true);
}

//void CUI_ID_FRAME_ChangeEquip::ChangeSuit(int nIndex)
//{
//	if(!IsCanReplace(nIndex))
//	{
//		GetShowScreenText() ->AddInfo(theXmlString.GetString(eChangeSuitFail),Color_Config.getColor(CC_Center_ImmediateInfo));
//		return;
//	}
//	else
//		GetShowScreenText() ->AddInfo(theXmlString.GetString(eChangeSuitSuccess),Color_Config.getColor(CC_Center_ImmediateInfo));
//
//	//替换物品
//	for (int i = 0;i < EEquipPartType_MaxEquitPart;++i)
//	{
//		__int64 nGuid = CUserData::Instance()->GetGUID(nIndex,i);
//		if(nGuid != 0)
//		{
//			int n = thePlayerRole.m_bag.GetItemIndexByGUID(nGuid);
//			if(n != -1)
//			{
//				ControlIconDrag::S_ListImg* pImg = s_CUI_ID_FRAME_PACK.GetItemByIndex(BT_NormalItemBag,n);
//				if(pImg)
//				{
//					SCharItem item;
//					if(thePlayerRole.m_bag.GetItem(n,&item))
//						s_CUI_ID_FRAME_PACK.UseItem(pImg->m_pkIconInfo->Id(),n);
//				}
//			}
//		}
//		else
//		{
//			ControlIconDrag::S_ListImg* pImg = NULL;
//			if(i < EPT_MaxEquitPart)
//			{
//				if(i == EPT_RHandItem || i == EPT_Armour || i == EPT_Shoe || i == EPT_Glove
//					|| i == EPT_Necklace || i == EPT_Ring || i == EPT_RBangle || i == EPT_Sash
//					|| i == EPT_Trousers || i == EPT_Shoulder || i == EPT_Helmet || i == EPT_Honor
//					|| i == EPT_Badge     || i == EPT_GemBag)
//				{
//					pImg = s_CUI_ID_FRAME_BaseProperty.GetEquipList()[i]->GetItemByIndex(0);
//					if(pImg&&!pImg->IsNull())
//						s_CUI_ID_FRAME_BaseProperty.ID_LISTIMG_OnIconRButtonUp(NULL,pImg);
//				}
//			}
//			else
//			{
//				if( i == EPT_MaxEquitPart + EPT_Helmet)  //头盔
//					pImg = s_CUI_ID_FRAME_BaseProperty.GetFashionEquip()[0]->GetItemByIndex(0);
//				else if(i == EPT_MaxEquitPart + EPT_Armour) //盔甲
//					pImg = s_CUI_ID_FRAME_BaseProperty.GetFashionEquip()[1]->GetItemByIndex(0);
//				else if(i == EPT_MaxEquitPart + EPT_Glove) //手套
//					pImg = s_CUI_ID_FRAME_BaseProperty.GetFashionEquip()[2]->GetItemByIndex(0);
//				else if(i == EPT_MaxEquitPart + EPT_Shoe) //鞋子
//					pImg = s_CUI_ID_FRAME_BaseProperty.GetFashionEquip()[3]->GetItemByIndex(0);
//
//				if(pImg&&!pImg->IsNull())
//				{
//					int index = -1;
//					if( s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag) )
//						index = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag)->GetNullItem();
//					if (index == -1 || index >= thePlayerRole.m_bag.GetNowBagSize())
//					{
//						GetShowScreenText() ->AddInfo(theXmlString.GetString(eText_ChangeSuitFail),Color_Config.getColor(CC_Center_WarningErrorInfo));
//						continue;
//					}
//
//					s_CUI_ID_FRAME_BaseProperty.ID_LISTIMG_OnIconRButtonUp(NULL,pImg);
//				}
//			}
//		}
//	}
//}


//add by yanli  2010-9-28
void CUI_ID_FRAME_ChangeEquip::ChangeSuit(int nIndex)
{
	if(!IsCanReplace(nIndex))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_EquipChange_Failed, theXmlString.GetString(eChangeSuitFail) );
		return;
	}
	else
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_EquipChange_Success, theXmlString.GetString(eChangeSuitSuccess) );

	//替换物品
	for (int i = 0;i < EEquipPartType_MaxEquitPart;++i)
	{
		__int64 nGuid = CUserData::Instance()->GetGUID(nIndex,i);
		if(nGuid != 0)
		{
			int n = thePlayerRole.m_bag.GetItemIndexByGUID(nGuid);
			if(n != -1)
			{
				ControlIconDrag::S_ListImg* pImg = s_CUI_ID_FRAME_PACK.GetItemByIndex(BT_NormalItemBag,n);
				if(pImg)
				{
					SCharItem item;
					if(thePlayerRole.m_bag.GetItem(n,&item))
						s_CUI_ID_FRAME_PACK.UseItem(pImg->m_pkIconInfo->Id(),n);
				}
			}
		}
		else
		{
			ControlIconDrag::S_ListImg* pImg = NULL;
			pImg = s_CUI_ID_FRAME_BaseProperty.GetEquipList()[i]->GetItemByIndex(0);
			if(pImg&&!pImg->IsNull())
				s_CUI_ID_FRAME_BaseProperty.ID_LISTIMG_OnIconRButtonUp(NULL,pImg);
		}
	}
}


//bool CUI_ID_FRAME_ChangeEquip::IsCanReplace(int nIndex)
//{
//	//         if(m_CurrSuit == nIndex)
//	//             return false;
//
//	if(CUserData::Instance()->GetSuitIndex(nIndex) == -1)
//		return false;
//
//	return true;
//
//	//需要考虑装备对话之间的差值
//	//装备的数量 <= 需要替换的数量 + 空白空间 + 公用的部件
//	//需要替换的数量可能不存在了
//	//需要判断需要替换的装备是否存在
//	int nTotleNum = thePlayerRole.m_bag.GetNullItemCount();
//	SCharItem* pVisual = thePlayerRole.m_pVisual->GetAllSuitArray();
//	for (int i = 0;i < EPT_TotalWearCount;++i)
//	{
//		if(i == EPT_RHandItem || i == EPT_Armour || i == EPT_Shoe || i == EPT_Glove
//			|| i == EPT_Necklace || i == EPT_Ring || i == EPT_RBangle || i == EPT_Sash
//			|| i == EPT_Trousers || i == EPT_Shoulder || i == EPT_Helmet || i == EPT_Honor
//			|| i == EPT_Badge     || i == EPT_GemBag ||i == EPT_MaxEquitPart + EPT_Helmet
//			|| i == EPT_MaxEquitPart + EPT_Armour ||i == EPT_MaxEquitPart + EPT_Glove
//			||i == EPT_MaxEquitPart + EPT_Shoe)
//		{
//			__int64 nGuid = CUserData::Instance()->GetGUID(nIndex,i);
//			int n = thePlayerRole.m_bag.GetItemIndexByGUID(nGuid);
//			//装备的数量,需要取下物品
//			if(pVisual[i].itembaseinfo.ustItemID != ErrorUnsignedShortID && pVisual[i].itembaseinfo.nOnlyInt != 0&&n == -1)
//				--nTotleNum;      
//		}
//	}
//
//	//计算公用部件
//	for (int nCommon = 0; nCommon < EPT_TotalWearCount;++nCommon)
//	{
//		__int64 nGuid = CUserData::Instance()->GetGUID(nIndex,nCommon);
//		if(nGuid != 0)
//		{
//			for (int n = 0; n < EPT_TotalWearCount;++n)
//			{
//				if(pVisual[n].itembaseinfo.ustItemID != ErrorUnsignedShortID && pVisual[n].itembaseinfo.nOnlyInt == nGuid)
//					++nTotleNum;
//			}
//		}
//	}
//	if(nTotleNum >= 0)
//		return true;
//
//	return false;
//}
//
//

//add by yanli  2010-9-28
bool CUI_ID_FRAME_ChangeEquip::IsCanReplace(int nIndex)
{
	//         if(m_CurrSuit == nIndex)
	//             return false;

	/*if(CUserData::Instance()->GetSuitIndex(nIndex) == -1)
		return false;*/

	return true;

	//需要考虑装备对话之间的差值
	//装备的数量 <= 需要替换的数量 + 空白空间 + 公用的部件
	//需要替换的数量可能不存在了
	//需要判断需要替换的装备是否存在
	int nTotleNum = thePlayerRole.m_bag.GetNullItemCount();
	SCharItem* pVisual = thePlayerRole.m_pVisual->GetVisualArray();
	for (int i = 0;i < EEquipPartType_MaxEquitPart;++i)
	{
		__int64 nGuid = CUserData::Instance()->GetGUID(nIndex,i);
		int n = thePlayerRole.m_bag.GetItemIndexByGUID(nGuid);
		//装备的数量,需要取下物品
		if(pVisual[i].itembaseinfo.ustItemID != ErrorUnsignedShortID && pVisual[i].itembaseinfo.nOnlyInt != 0&&n == -1)
			--nTotleNum;      
	}

	//计算公用部件
	for (int nCommon = 0; nCommon < EEquipPartType_MaxEquitPart;++nCommon)
	{
		__int64 nGuid = CUserData::Instance()->GetGUID(nIndex,nCommon);
		if(nGuid != 0)
		{
			for (int n = 0; n < EEquipPartType_MaxEquitPart;++n)
			{
				if(pVisual[n].itembaseinfo.ustItemID != ErrorUnsignedShortID && pVisual[n].itembaseinfo.nOnlyInt == nGuid)
					++nTotleNum;
			}
		}
	}
	if(nTotleNum >= 0)
		return true;

	return false;
}

void CUI_ID_FRAME_ChangeEquip::Init()
{
	if( !m_pID_FRAME_ChangeEquip )
		return;
	bool bShow = CUserData::Instance()->IsShowSuitUI();
	int  nIndex = CUserData::Instance()->GetSuitLastIndex();
	SetVisable(bShow);
	SetSuit(nIndex);
}

void CUI_ID_FRAME_ChangeEquip::SaveSuit(bool bShowInfo/* = true*/)
{
	CUserData::Instance()->SetSuitLastIndex(m_CurrSuit);
	CUserData::Instance()->SetShowSuitUI(IsVisable());
	if(CUserData::Instance()->SaveSuit()&&bShowInfo)
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_EquipChange_Success, theXmlString.GetString(eChangeSuitSave) );
}

bool CUI_ID_FRAME_ChangeEquip::IsCoolDowning()
{
	if(m_dwCoolDown == 0)
	{
		m_dwCoolDown = GetTickCount();
		return true;
	}
	else
	{
		if(GetTickCount() - m_dwCoolDown >= s_dwElapseTime)
		{
			m_dwCoolDown = 0;
			return true;
		}
		return false;
	}

	return false;
}

bool CUI_ID_FRAME_ChangeEquip::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if ( bMsgUsed == true || g_GameState != G_MAIN )
		return false;
	if( !s_CUI_ID_FRAME_ChangeEquip.m_pID_FRAME_ChangeEquip )
		return false;

	switch( msg ) 
	{
	case WM_KEYDOWN:
		{

			if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_ChangeSuit1) )
			{
				s_CUI_ID_FRAME_ChangeEquip.ID_CHECKBOX_1OnCheckBoxCheck(NULL,NULL);
				return true;
			}
			else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_ChangeSuit2) )
			{
				s_CUI_ID_FRAME_ChangeEquip.ID_CHECKBOX_2OnCheckBoxCheck(NULL,NULL);
				return true;
			}
			else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_ChangeSuit3) )
			{
				s_CUI_ID_FRAME_ChangeEquip.ID_CHECKBOX_3OnCheckBoxCheck(NULL,NULL);
				return true;
			}
			else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_ChangeSuit4) )
			{
				s_CUI_ID_FRAME_ChangeEquip.ID_CHECKBOX_4OnCheckBoxCheck(NULL,NULL);
				return true;
			}
			else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_ChangeSuit5) )
			{
				s_CUI_ID_FRAME_ChangeEquip.ID_CHECKBOX_5OnCheckBoxCheck(NULL,NULL);
				return true;
			}
		}
	}
	return false;
}
