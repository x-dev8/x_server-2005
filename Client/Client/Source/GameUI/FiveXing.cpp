/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\FiveXing.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FiveXing.h"
#include "PlayerRole.h"
#include "ui/Pack.h"
#include "NetworkInput.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "XmlStringLanguage.h"
#include "MeUi/ExpressionManager.h"
#include "StarLevelUpConfig.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "color_config.h"
#include "PackItemEnableManager.h"

CUI_ID_FRAME_FiveXing s_CUI_ID_FRAME_FiveXing;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FiveXing, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FiveXing, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_BUTTON_SureOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_BUTTON_ReturnOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXing, ID_BUTTON_ResetOnButtonClick )
CUI_ID_FRAME_FiveXing::CUI_ID_FRAME_FiveXing()
{
	// Member
	m_pID_FRAME_FiveXing = NULL;
// 	m_pID_PICTURE_RightTitle = NULL;
// 	m_pID_PICTURE_MiddleTitle = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
	m_pID_PICTURE_LeftTitle = NULL;
// 	m_pID_PICTURE_TitleWord = NULL;
// 	m_pID_TEXT_Explain = NULL;
// 	m_pID_PICTURE_ItemWall2 = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_PICTURE_ExplainWall = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Mu = NULL;
	m_pID_PICTURE_Shui = NULL;
	m_pID_PICTURE_Huo = NULL;
	m_pID_PICTURE_Tu = NULL;
	m_pID_PICTURE_WordWall  = NULL;
	m_pID_TEXT_String = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_BUTTON_Return = NULL;
// 	m_pID_PICTURE_TitleWordReturn = NULL;
// 	m_pID_TEXT_ExplainReturn = NULL;
    m_pID_TEXT_Word  = NULL;
    m_pID_BUTTON_Reset = NULL;
    m_pID_PICTURE_Flash = NULL;
    m_bAck = false;
    m_elemType = 0;
    m_pID_PICTURE_FiveXing1 = NULL;
    m_pID_PICTURE_FiveXing2 = NULL;
    m_pID_PICTURE_ReturnFiveXing1 = NULL;
    m_pID_PICTURE_ReturnFiveXing2 = NULL;
    m_pID_PICTURE_FiveXing3 = NULL;
    m_pID_PICTURE_ReturnFiveXing3 = NULL;

}
// Frame
bool CUI_ID_FRAME_FiveXing::OnFrameRun()
{
	if( !IsDirty() )
		return true;

	SetDirty( false );

	RefreshAllBagEnable();	

	if( m_pID_LISTIMG_Armour->GetNullItem() != -1 && 
		m_stNormalBagIndex != -1) // 有空位，清空包裹id		
	{
		m_stNormalBagIndex = -1;			
		SetDirty( true );
	}
	else
	{
		RefreshNeedMoney( thePlayerRole.m_bag.GetCharItemFromIdx( m_stNormalBagIndex ) );
	}

	if( m_pID_LISTIMG_Material->GetNullItem() != -1 && 
		m_stMaterialIndex != -1 )
	{
		if( m_eMaterialBagType == BT_NormalItemBag )
		{
		}
		else if( m_eMaterialBagType == BT_MaterialBag )
		{
		}		
		m_stMaterialIndex = -1;
		SetDirty( true );
	}

// 	// 更新按钮状态
// 	m_pID_BUTTON_Ok->SetEnable( true );
// 	m_pID_BUTTON_Return->SetEnable( true );
// 	if( m_pID_LISTIMG_Armour->GetNullItem() != -1 ||
// 		m_pID_LISTIMG_Material->GetNullItem() != -1 )
// 	{
// 		m_pID_BUTTON_Ok->SetEnable( false );
//		m_pID_BUTTON_Return->SetEnable( false );
//  }	
    RefreshOkButton();
	return true;
}
bool CUI_ID_FRAME_FiveXing::OnFrameRender()
{
	if( IsVisable() )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
		{
			float fMeX,fMeY,fMeZ;			
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
			if( dist > 12.0f )
			{
				SetVisable( false );
			}
		}

        RECT rc;
        m_pID_PICTURE_Flash->GetRealRect(&rc);
        m_slideAnim.Update(HQ_TimeGetTime(), &rc);
        if(!m_slideAnim.IsInAnimation()&&m_bAck)
        {
            ShowSuccessUI((EItemElements)m_elemType);
            m_bAck = false;
        }
	}
	return true;
}
// Button
// bool CUI_ID_FRAME_FiveXing::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// // Button
// bool CUI_ID_FRAME_FiveXing::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_FiveXing::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItemDrag,
															ControlIconDrag::S_ListImg* pItemSrc )
{
    if(!m_pID_FRAME_FiveXing)
    {
        assert(false&&"ui error");
        return false;
    }

	if( !pItemDrag )
		return false;

	ID_LISTIMG_MaterialOnIconRButtonUp( 0, 0 );
	OnFrameRun();

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon )
	{
		bool bElements = false;
		if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_CHECKUP)
		{
			ItemDefine::SItemCheckUp* pItemCheckUp = (ItemDefine::SItemCheckUp*)pItemCommon;
			if( pItemCheckUp->stCheckUpType == ItemDefine::SItemCheckUp::ECD_Elements )
				//bElements = true;
                //如果为清除鉴定材料
                if (m_chOperate == MsgSuitElementCheckupReq::ECD_Clear)
                {
                    if(pItemCheckUp->stEffectType == ItemDefine::SItemCheckUp::ECD_ElementsClear)
                        bElements = true;
                }
                else if(m_chOperate == MsgSuitElementCheckupReq::ECD_Checkup)
                {
                    if(pItemCheckUp->stEffectType == ItemDefine::SItemCheckUp::ECD_ElementsCheckUp)
                        bElements = true;
                }
		}

		if( bElements )
		{
			ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )pItemCommon;

	// 		if( ( pMaterial->stMaterialType == ItemDefine::ematerial_identify && GetPlatingType() != ePlatingType_Identify ) 
	// 			|| ( pMaterial->stMaterialType == CItemDetail::ematerial_OpenLight && GetPlatingType() != ePlatingType_KaiGuang ) )
	// 			return false;

			m_pID_LISTIMG_Material->Clear();			
			m_pID_LISTIMG_Material->SetItem( pItemDrag, 0 );
			m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
			m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;		
			// type		
			int nMaterialIndex = 0;
			thePlayerRole.GetBagTypeByItemGUID( pItemDrag->m_pkIconInfo->GetOnlyId(), m_eMaterialBagType, &nMaterialIndex );
			m_nMaterialGuid = pItemDrag->m_pkIconInfo->GetOnlyId();
			//物品在包裹里的id
			m_stMaterialIndex = static_cast<short>(nMaterialIndex);
			m_bMaterialBagEnable = false;
			SetDirty( true );
		}
        else
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eClient_FiveXingTipMaterialError) );
	}
	return false;
}
bool CUI_ID_FRAME_FiveXing::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FiveXing::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FiveXing::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_FiveXing)
    {
        assert(false&&"ui error");
        return false;
    }

	m_bMaterialBagEnable = true;		
	m_pID_LISTIMG_Material->Clear();
	SetDirty( true );

	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_FiveXing::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
    if(!m_pID_FRAME_FiveXing)
    {
        assert(false&&"ui error");
        return false;
    }

	if( !pItemDrag )
		return false;


    unsigned char ucType = ((SCharItem*)pItemDrag->m_pkIconInfo->GetData())->GetElements();
    if (m_chOperate == MsgSuitElementCheckupReq::ECD_Clear&&ucType == 0)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eText_Error_HaveNotElement) );
        return false;
    }
    else if(m_chOperate == MsgSuitElementCheckupReq::ECD_Checkup&&ucType != 0)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eText_Error_ItemAlreadyDid) );
        return false;        
    }



	ID_LISTIMG_ArmourOnIconRButtonUp( 0, 0 );
	OnFrameRun();	

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

		ItemDefine::SItemArmour* pCanEquip = ( ItemDefine::SItemArmour* )pItemCommon;
		if( pCanEquip && !pCanEquip->bIsElements )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eText_Error_ItemNotElement) );
			return false;
		}
		// 包裹里
		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
		{			
			m_stNormalBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
		}
		else
		{
			return false;
		}		

		m_bNormalBagEnable = false;			
		//UpdateAccessory();
		RefreshArmour();

		SetDirty( true );
        SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_FiveXing::SetMaterial0);
	}	
	return false;
}
bool CUI_ID_FRAME_FiveXing::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FiveXing::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FiveXing::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_FiveXing)
    {
        assert(false&&"ui error");
        return false;
    }
	//m_bMaterialBagEnable = true;
	m_bNormalBagEnable = true;			
// 	m_pID_LIST_BaseProperty->Clear();
// 	m_pID_LIST_Property->Clear();
// 	m_pID_LIST_Quality->Clear();
	m_pID_LISTIMG_Armour->Clear();
    m_pID_TEXT_UseMoney->Clear();
	//SetMoneyUi( 0 );
	//m_pID_LISTIMG_Material->Clear();		
	//ClearMoney();
	SetDirty( true );
	return false;
}
// Button
bool CUI_ID_FRAME_FiveXing::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{	
    if(!m_pID_FRAME_FiveXing)
    {
        assert(false&&"ui error");
        return false;
    }
	SendSuitCheckMsg();
	return true;
}
// Button
bool CUI_ID_FRAME_FiveXing::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable( false );
	return true;
}
bool CUI_ID_FRAME_FiveXing::ID_BUTTON_ResetOnButtonClick( ControlObject* pSender )
{
    return true;
}
// Button
bool CUI_ID_FRAME_FiveXing::ID_BUTTON_SureOnButtonClick( ControlObject* pSender )
{
    if(!m_pID_FRAME_FiveXing)
    {
        assert(false&&"ui error");
        return false;
    }

	for( int i = ItemElements_Metal; i < ItemElements_End; ++ i )
	{
		m_FiveEleHelper[i].m_pSuccessPic->SetVisable( false );
	}
	m_FiveGroupHelper.SetVisible( false );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_FiveXing::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FiveXing.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FiveXing.MEUI]失败")
			return false;
	}
	m_stNormalBagIndex = -1;        // 目标物品Index
	m_bNormalBagEnable = true;	
	m_stMaterialIndex = -1;		 // 道具Index
	m_bMaterialBagEnable = true;
	m_nMaterialGuid = 0;
	m_chOperate = 0;
	return DoControlConnect();
}

// Button
bool CUI_ID_FRAME_FiveXing::ID_BUTTON_ReturnOnButtonClick( ControlObject* pSender )
{
	SendSuitCheckMsg();
	return true;
}
// 关连控件
bool CUI_ID_FRAME_FiveXing::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_FiveXing, s_CUI_ID_FRAME_FiveXingOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_FiveXing, s_CUI_ID_FRAME_FiveXingOnFrameRender );
// 	theUiManager.OnButtonClick( ID_FRAME_FiveXing, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_FiveXingID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_FiveXing, ID_BUTTON_help, s_CUI_ID_FRAME_FiveXingID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_FiveXing, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_FiveXing, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_FiveXing, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_FiveXing, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_FiveXing, ID_BUTTON_Ok, s_CUI_ID_FRAME_FiveXingID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FiveXing, ID_BUTTON_Cancel, s_CUI_ID_FRAME_FiveXingID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_FiveXing, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_FiveXing, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_FiveXing, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_FiveXing, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_FiveXing, ID_BUTTON_Sure, s_CUI_ID_FRAME_FiveXingID_BUTTON_SureOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FiveXing, ID_BUTTON_Return, s_CUI_ID_FRAME_FiveXingID_BUTTON_ReturnOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_FiveXing, ID_BUTTON_Reset, s_CUI_ID_FRAME_FiveXingID_BUTTON_ResetOnButtonClick );

	m_pID_FRAME_FiveXing = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FiveXing );
// 	m_pID_PICTURE_RightTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_RightTitle );
// 	m_pID_PICTURE_MiddleTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_MiddleTitle );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_BUTTON_help );
	m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_ItemWall );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_LISTIMG_Armour );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_TEXT_UseMoneyZ );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_TEXT_UseMoney );
	m_pID_PICTURE_LeftTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_LeftTitle );
// 	m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_TitleWord );
// 	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_TEXT_Explain );
// 	m_pID_PICTURE_ItemWall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_ItemWall2 );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_LISTIMG_Material );
	m_pID_PICTURE_ExplainWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_ExplainWall );
	m_pID_PICTURE_Jin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_Jin );
	m_pID_PICTURE_Mu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_Mu );
	m_pID_PICTURE_Shui = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_Shui );
	m_pID_PICTURE_Huo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_Huo );
	m_pID_PICTURE_Tu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_Tu );
	m_pID_PICTURE_WordWall  = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_WordWall  );
	m_pID_TEXT_String = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_TEXT_String );
	m_pID_BUTTON_Sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_BUTTON_Sure );
	m_pID_BUTTON_Return = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_BUTTON_Return );
// 	m_pID_PICTURE_TitleWordReturn = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_TitleWordReturn );
// 	m_pID_TEXT_ExplainReturn = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_TEXT_ExplainReturn );
    m_pID_TEXT_Word = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_TEXT_Word );
    m_pID_BUTTON_Reset = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_BUTTON_Reset );
    m_pID_PICTURE_Flash = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_Flash );
    m_pID_PICTURE_FiveXing1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_FiveXing1 );
    m_pID_PICTURE_FiveXing2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_FiveXing2 );
    m_pID_PICTURE_ReturnFiveXing1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_ReturnFiveXing1 );
    m_pID_PICTURE_ReturnFiveXing2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_ReturnFiveXing2 );
    m_pID_PICTURE_FiveXing3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_FiveXing3 );
    m_pID_PICTURE_ReturnFiveXing3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXing, ID_PICTURE_ReturnFiveXing3 );
	assert( m_pID_FRAME_FiveXing );
// 	assert( m_pID_PICTURE_RightTitle );
// 	assert( m_pID_PICTURE_MiddleTitle );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
	assert( m_pID_PICTURE_ItemWall );
	assert( m_pID_LISTIMG_Armour );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_UseMoneyZ );
	assert( m_pID_TEXT_UseMoney );
	assert( m_pID_PICTURE_LeftTitle );
// 	assert( m_pID_PICTURE_TitleWord );
// 	assert( m_pID_TEXT_Explain );
// 	assert( m_pID_PICTURE_ItemWall2 );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_PICTURE_ExplainWall );
	assert( m_pID_PICTURE_Jin );
	assert( m_pID_PICTURE_Mu );
	assert( m_pID_PICTURE_Shui );
	assert( m_pID_PICTURE_Huo );
	assert( m_pID_PICTURE_Tu );
	assert( m_pID_PICTURE_WordWall  );
	assert( m_pID_TEXT_String );
	assert( m_pID_BUTTON_Sure );
	assert( m_pID_BUTTON_Return );
// 	assert( m_pID_PICTURE_TitleWordReturn );
// 	assert( m_pID_TEXT_ExplainReturn );
    assert( m_pID_TEXT_Word );
    assert( m_pID_BUTTON_Reset );
    assert( m_pID_PICTURE_Flash );
    assert( m_pID_PICTURE_FiveXing1 );
    assert( m_pID_PICTURE_FiveXing2 );
    assert( m_pID_PICTURE_ReturnFiveXing1 );
    assert( m_pID_PICTURE_ReturnFiveXing2 );
    assert( m_pID_PICTURE_FiveXing3 );
    assert( m_pID_PICTURE_ReturnFiveXing3 );
	m_pID_FRAME_FiveXing->SetOnVisibleChangedFun( OnVisibleChange );

	// init helper ui
	InitHelperUi();
	m_FiveGroupHelper.AddControl( m_pID_TEXT_String );
	m_FiveGroupHelper.AddControl( m_pID_PICTURE_ExplainWall );
	m_FiveGroupHelper.AddControl( m_pID_BUTTON_Sure );
	m_FiveGroupHelper.AddControl( m_pID_PICTURE_WordWall );
	m_FiveGroupHelper.SetVisible( false );

    RECT rc;
    m_pID_PICTURE_Flash->GetRealRect(&rc);
    m_slideAnim.Initialize("Ui\\Common\\FiveXingSuitEffect\\HudFiveXingLight", 21, rc, 1000);
	SetVisable( false );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_FiveXing::_UnLoadUI()
{
// 	m_pID_FRAME_FiveXing = NULL;
// 	m_pID_PICTURE_RightTitle = NULL;
// 	m_pID_PICTURE_MiddleTitle = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
	m_pID_PICTURE_LeftTitle = NULL;
// 	m_pID_PICTURE_TitleWord = NULL;
// 	m_pID_TEXT_Explain = NULL;
// 	m_pID_PICTURE_ItemWall2 = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_PICTURE_ExplainWall = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Mu = NULL;
	m_pID_PICTURE_Shui = NULL;
	m_pID_PICTURE_Huo = NULL;
	m_pID_PICTURE_Tu = NULL;
	m_pID_PICTURE_WordWall  = NULL;
	m_pID_TEXT_String = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_BUTTON_Return = NULL;
// 	m_pID_PICTURE_TitleWordReturn = NULL;
// 	m_pID_TEXT_ExplainReturn = NULL;
	m_pID_TEXT_Word  = NULL;
	m_pID_BUTTON_Reset = NULL;
	m_pID_PICTURE_Flash = NULL;
	m_pID_PICTURE_FiveXing1 = NULL;
	m_pID_PICTURE_FiveXing2 = NULL;
	m_pID_PICTURE_ReturnFiveXing1 = NULL;
	m_pID_PICTURE_ReturnFiveXing2 = NULL;
	m_pID_PICTURE_FiveXing3 = NULL;
	m_pID_PICTURE_ReturnFiveXing3 = NULL;

	m_FiveGroupHelper.Clear();
	return theUiManager.RemoveFrame( "Data\\UI\\FiveXing.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_FiveXing::_IsVisable()
{
	if (!m_pID_FRAME_FiveXing)
		return false;
	return m_pID_FRAME_FiveXing->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_FiveXing::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_FiveXing)
		return;

	if( bVisable )
	{
		ClearAllList();
		//ClearMoney();
		SetDirty( true );
	}
	m_pID_FRAME_FiveXing->SetVisable( bVisable );
}
void CUI_ID_FRAME_FiveXing::SendSuitCheckMsg()
{
	SCharItem kItem;
	if( thePlayerRole.m_bag.GetItem( m_stNormalBagIndex, &kItem ) )
	{
		__int64 nArmourGuid = kItem.itembaseinfo.nOnlyInt;
		//if( thePlayerRole.m_bagMaterial.GetItem( m_stMaterialIndex, &kItem ) )
		{
			MsgSuitElementCheckupReq msg;
			msg.chArmourBagType = BT_NormalItemBag;
			msg.stArmourIndex = m_stNormalBagIndex;
			msg.nArmourGuid = nArmourGuid;

			msg.chItemBagType = m_eMaterialBagType;
			msg.stItemIndex = m_stMaterialIndex;
			msg.nItemGuid = m_nMaterialGuid;

			msg.chOperate = m_chOperate;

			GettheNetworkInput().SendMsg( &msg );

            m_slideAnim.StartAnimation(HQ_TimeGetTime());
			return;
		}		
	}	
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eText_Error_ItemNotReady) );
}
void CUI_ID_FRAME_FiveXing::ShowSuccessUI( EItemElements eType )
{
	if( !m_pID_FRAME_FiveXing )
		return;
	if( eType == ItemElements_Init )
		return;

	for( int i = ItemElements_Metal; i < ItemElements_End; ++ i )
	{
		m_FiveEleHelper[i].m_pSuccessPic->SetVisable( false );
	}

	m_FiveGroupHelper.SetVisible( true );
	m_FiveEleHelper[eType].m_pSuccessPic->SetVisable( true );
	*m_pID_TEXT_String = theXmlString.GetString( m_FiveEleHelper[eType].m_nSuccessStringIndex );
	
}
void CUI_ID_FRAME_FiveXing::InitHelperUi()
{
	m_FiveEleHelper[ ItemElements_Metal ].m_pSuccessPic = m_pID_PICTURE_Jin;
	m_FiveEleHelper[ ItemElements_Metal ].m_nSuccessStringIndex = eText_GetJinAttribute;
	m_FiveEleHelper[ ItemElements_Wood ].m_pSuccessPic = m_pID_PICTURE_Mu;
	m_FiveEleHelper[ ItemElements_Wood ].m_nSuccessStringIndex = eText_GetMuAttribute;
	m_FiveEleHelper[ ItemElements_Water ].m_pSuccessPic = m_pID_PICTURE_Shui;
	m_FiveEleHelper[ ItemElements_Water ].m_nSuccessStringIndex = eText_GetShuiAttribute;
	m_FiveEleHelper[ ItemElements_Fire ].m_pSuccessPic = m_pID_PICTURE_Huo;
	m_FiveEleHelper[ ItemElements_Fire ].m_nSuccessStringIndex = eText_GetHuoAttribute;
	m_FiveEleHelper[ ItemElements_Earth ].m_pSuccessPic = m_pID_PICTURE_Tu;
	m_FiveEleHelper[ ItemElements_Earth ].m_nSuccessStringIndex = eText_GetTuAttribute;
	for( int i = ItemElements_Metal; i < ItemElements_End; ++ i )
	{
		m_FiveEleHelper[i].m_pSuccessPic->SetVisable( false );
	}
}

void CUI_ID_FRAME_FiveXing::RefreshMaterial()
{
	if( !m_pID_FRAME_FiveXing )
		return;
	SCharItem kItem;
	if( !thePlayerRole.GetBagItemByGUID( m_nMaterialGuid, &kItem ) )	
	{
		m_bMaterialBagEnable = true;
		m_pID_LISTIMG_Material->Clear();
		SetDirty( true );
	}

}

void CUI_ID_FRAME_FiveXing::RefreshArmour()
{
	if( !m_pID_FRAME_FiveXing )
		return;
	ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_stNormalBagIndex );
	if( !pItemImg )
		return;

	SetArmourInfo( pItemImg );
	//UpdateArmourInfo( (SCharItem*)pItemImg->m_pkIconInfo->GetData(), m_pID_LIST_Property  );
}
void CUI_ID_FRAME_FiveXing::ClearAllList()
{
	s_CUI_ID_FRAME_FiveXing.SetDirty( true );
	s_CUI_ID_FRAME_FiveXing.m_bMaterialBagEnable = true;
	s_CUI_ID_FRAME_FiveXing.m_bNormalBagEnable = true;
	s_CUI_ID_FRAME_FiveXing.RefreshAllBagEnable();	
	s_CUI_ID_FRAME_FiveXing.m_pID_LISTIMG_Armour->Clear();
	s_CUI_ID_FRAME_FiveXing.m_pID_LISTIMG_Material->Clear();
// 	s_CUI_ID_FRAME_GoldPlating.m_pID_LIST_BaseProperty->Clear();
// 	s_CUI_ID_FRAME_GoldPlating.m_pID_LIST_Property->Clear();
// 	s_CUI_ID_FRAME_GoldPlating.m_pID_LIST_Quality->Clear();
}
void CUI_ID_FRAME_FiveXing::SetArmourInfo( ControlIconDrag::S_ListImg* pListImg )
{
	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Armour->SetItem( pListImg, 0 );
	m_pID_LISTIMG_Armour->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
	m_pID_LISTIMG_Armour->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;	
}
void CUI_ID_FRAME_FiveXing::RefreshAllBagEnable()
{
	if( m_stNormalBagIndex != -1 )
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_stNormalBagIndex, true );
	}

	if( m_stMaterialIndex != -1 )
	{
        if( m_bMaterialBagEnable )
        {
            m_nMaterialGuid = 0;
        }
		if( m_eMaterialBagType == BT_NormalItemBag )
		{
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_stMaterialIndex, true );
		}
		else if( m_eMaterialBagType == BT_MaterialBag )
		{
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex, true );
		}		
	}
}
void CUI_ID_FRAME_FiveXing::OnVisibleChange( ControlObject* pUIObject )
{
	if( !s_CUI_ID_FRAME_FiveXing.IsVisable() )
	{
		for( int i = ItemElements_Metal; i < ItemElements_End; ++ i )
		{
			s_CUI_ID_FRAME_FiveXing.m_FiveEleHelper[i].m_pSuccessPic->SetVisable( false );
		}
		s_CUI_ID_FRAME_FiveXing.m_FiveGroupHelper.SetVisible( false );
	}
	else
	{
		s_CUI_ID_FRAME_PACK.SetVisable( true );
	}
	s_CUI_ID_FRAME_FiveXing.ClearAllList();
	s_CUI_ID_FRAME_FiveXing.SetDirty( true );
    s_CUI_ID_FRAME_FiveXing.m_pID_BUTTON_Reset->SetVisable(false);
    s_CUI_ID_FRAME_FiveXing.m_pID_PICTURE_ItemWall->SetVisable(false);
    s_CUI_ID_FRAME_FiveXing.m_pID_TEXT_UseMoney->Clear();
}

void CUI_ID_FRAME_FiveXing::SetMoneyUi( DWORD dwMoney )
{
	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(dwMoney, text);

    DWORD dwColor = 0xffffffff;
    //DWORD dwCurMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
    //if(dwCurMoney < dwMoney)
    if(!thePlayerRole.HaveEnoughMoney(dwMoney))
    {
        dwColor = 0xffff0000;
    }
	//*m_pID_TEXT_UseMoney = text;
    m_pID_TEXT_UseMoney->SetText(text,dwColor);
}
void CUI_ID_FRAME_FiveXing::RefreshNeedMoney( SCharItem* pItem )
{
	if( !pItem )
		return;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if( !pItemCommon )
		return ;

	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return ;

	StarLevelUpData* pData = theStarLevelUpConfig.GetStarLevelUpData( pCanEquip->stEquipLevelReq, pItem->equipdata.ucLevel );
	if( !pData )
		return;

	DWORD dwMoney = pData->GetCostMoney() * 5;
	SetMoneyUi( dwMoney );
	
}

void CUI_ID_FRAME_FiveXing::SetAtomVisible( uint8 chOperate )
{
	if( !m_pID_FRAME_FiveXing )
		return;
    m_pID_PICTURE_FiveXing1->SetVisable(false);
    m_pID_PICTURE_FiveXing2->SetVisable(false);
    m_pID_PICTURE_ReturnFiveXing1->SetVisable(false);
    m_pID_PICTURE_ReturnFiveXing2->SetVisable(false);
    m_pID_PICTURE_FiveXing3->SetVisable(false);
    m_pID_PICTURE_ReturnFiveXing3->SetVisable(false);

	if( chOperate == MsgSuitElementCheckupReq::ECD_Checkup )
	{
// 		m_pID_PICTURE_TitleWord->SetVisable( true );
// 		m_pID_PICTURE_TitleWordReturn->SetVisable( false );

		m_pID_BUTTON_Ok->SetVisable( true );
		m_pID_BUTTON_Return->SetVisable( false );

// 		m_pID_TEXT_ExplainReturn->SetVisable( false );
// 		m_pID_TEXT_Explain->SetVisable( true );

        m_pID_PICTURE_FiveXing1->SetVisable(true);
        m_pID_PICTURE_FiveXing2->SetVisable(true);
        m_pID_PICTURE_FiveXing3->SetVisable(true);

	}
	else if( chOperate == MsgSuitElementCheckupReq::ECD_Clear )
	{
// 		m_pID_PICTURE_TitleWord->SetVisable( false );
// 		m_pID_PICTURE_TitleWordReturn->SetVisable( true );

		m_pID_BUTTON_Ok->SetVisable( false );
		m_pID_BUTTON_Return->SetVisable( true );

// 		m_pID_TEXT_ExplainReturn->SetVisable( true );
// 		m_pID_TEXT_Explain->SetVisable( false );

        m_pID_PICTURE_ReturnFiveXing1->SetVisable(true);
        m_pID_PICTURE_ReturnFiveXing2->SetVisable(true);
        m_pID_PICTURE_ReturnFiveXing3->SetVisable(true);
	}
}

void CUI_ID_FRAME_FiveXing::RefreshOkButton()
{
    if(!IsVisable())
        return;

    m_pID_BUTTON_Return->SetEnable( true );
    m_pID_BUTTON_Ok->SetEnable( true );
    if( m_pID_LISTIMG_Armour->GetNullItem() != -1 ||
        m_pID_LISTIMG_Material->GetNullItem() != -1 )
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        m_pID_BUTTON_Return->SetEnable( false );
        return;
    }

    ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Armour->GetItemByIndex(0);
    if(!pImg)
        return;

    if(pImg->IsNull())
        return;

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId() );
    if( !pItemCommon )
        return ;

    ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
    if( !pCanEquip )
        return ;	

    StarLevelUpData* pData = theStarLevelUpConfig.GetStarLevelUpData( pCanEquip->stEquipLevelReq, ((SCharItem*)pImg->m_pkIconInfo->GetData())->equipdata.ucLevel );
    if( !pData )
        return;

    //DWORD dwCurMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
    //if(dwCurMoney < pData->GetCostMoney() * 5)
    if(!thePlayerRole.HaveEnoughMoney(pData->GetCostMoney() * 5))
    {
        m_pID_BUTTON_Ok->SetEnable(false);
        m_pID_BUTTON_Return->SetEnable(false);
        return;
    }

    RefreshNeedMoney((SCharItem*)pImg->m_pkIconInfo->GetData());

    return;
}

bool CUI_ID_FRAME_FiveXing::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;
    
    if( m_nMaterialGuid == nGuid )
    {
        return true;
    }
    return false;
}
