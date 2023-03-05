/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\分级系统\Decompound.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Decompound.h"
#include "UIMgr.h"
#include "Pack.h"
#include "ItemDetail.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "core/Name.h"
#include "MessageBox.h"
#include "ItemDetail.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "SplitItemConfig.h"
#include "RandPropertyEvaluate.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "IconManagerClient.h"
#include "Progress.h"
#include "Common.h"
#include "PackItemEnableManager.h"

extern ControlIconDragManager theIconDragManager;
extern int g_nTheRoleProfession;
extern GAME_STATE	g_GameState;

extern DWORD dwYellow;// = 0xffffee03;
extern DWORD dwBlue;//   = 0xff06a2ff;
extern DWORD dwRed;//	   = 0xfffd1d11;
bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

#define ITEM_SHOW_INT_PRETEXT(x, str, col)		if(x > 0) \
{									\
    sprintf( szTemp, "%s%s+%d",theXmlString.GetString( eTip_PreText_Normal ), str, x );	\
    sList.clear();	\
    sList.SetData( szTemp, 0, 0, col );\
    m_pID_LIST_BaseProperty2->AddItem( &sList );	\
    sList.clear(); \
    m_pID_LIST_Quality->AddItem( &sList );\
}
#define ITEM_SHOW_FLOAT_PRETEXT(x, str, col)		if(x > 0.0f) \
{	\
    sprintf( szTemp, "%s%s%0.1f",theXmlString.GetString( eTip_PreText_Normal ), str, x );	\
    sList.clear();	\
    sList.SetData( szTemp, 0, 0, col );\
    m_pID_LIST_BaseProperty2->AddItem( &sList );	\
    sList.clear(); \
    m_pID_LIST_Quality->AddItem( &sList );\
}
extern float GetAttributeWithLevel( int nEquipType, float fAttribute, short stLevel );
//{
//    return fAttribute * ( 1 + 0.25f * ( (float)stLevel * 2.f + 10.f ) / 7.f * (int)( stLevel != 0 ) );
//}

extern int GetAttributeWithLevel( int nEquipType, int nAttribute, short stLevel );
//{
//    return nAttribute * ( 1 + 0.25f * ( (float)stLevel * 2.f + 10.f ) / 7.f * (int)( stLevel != 0 ));
//}

void ShowSplitResult(uint32 iResult)
{
	switch( iResult )
	{
	case ER_SplitItemNotExist:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eText_SplitFailed_ItemNotExist ) );
		break;
	case ER_SplitItemIndexGuidError:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eText_SplitFailed_ItemIndexGuidError ) );
		break;
	case ER_SplitItemTypeError:
	case ER_SplitItemLevelError:
	case ER_SplitItemLevelMulError:
	case ER_SplitItemConfigNotExist:
		{
			char str[MAX_PATH] = {0};
			char str_code[MAX_PATH] = {0};
			uint16 level = 0;//theItemSplitConfig.GetLevel();
			sprintf(str, theXmlString.GetString(eText_SplitFailed_ItemTypeLevelError), level);
			sprintf(str_code, "%s(%d)", str, iResult);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, str_code );
		}
		break;
	case ER_SplitItemCantBeSplit:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eText_SplitFailed_CantBeSplit ) );
		break;
	case ER_SplitItemQualityLevelError:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eText_SplitFailed_QualityLevelError ) );
		break;
	case ER_SplitItemProductNotExit:
	case ER_SplitItemCreateFail:
	case ER_SplitItemPopFail:
	case ER_SplitItemPushFail:
	case ER_ItemConfigNotExist:
		{
			char str_code[MAX_PATH] = {0};
			sprintf(str_code, "%s(%d)", theXmlString.GetString( eText_SplitFailed ), iResult);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, str_code );
		}
		break;
	default:
		break;
	}
}

bool Decompound( char bPressYesButton,void *pData )
{
    if (bPressYesButton && pData )
    {
        MsgAckReduceItem* pMsg = (MsgAckReduceItem*)pData;

		if( s_CUI_ID_FRAME_Decompound.CanDecompound( pMsg->index, true ) )
        {
			s_CUI_ID_FRAME_Decompound.StartIntonate();	// 开始吟唱
        }
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////

CUI_ID_FRAME_Decompound s_CUI_ID_FRAME_Decompound;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Decompound, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Decompound, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_BUTTON_helpOnButtonClick )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_Aim1OnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_Aim1OnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_Aim1OnIconButtonClick )
//MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_Aim1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_BUTTON_CancelOnButtonClick )
// MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LIST_BasePropertyOnListSelectChange )
// MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LIST_BaseProperty2OnListSelectChange )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_Aim2OnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_Aim2OnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_Aim2OnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LISTIMG_Aim2OnIconRButtonUp )
// MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Decompound, ID_LIST_QualityOnListSelectChange )
CUI_ID_FRAME_Decompound::CUI_ID_FRAME_Decompound()
{
	// Member
	m_pID_FRAME_Decompound = NULL;
// 	m_pID_PICTURE_RightTitle = NULL;
// 	m_pID_PICTURE_MiddleTitle = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
// 	m_pID_TEXT_Wall = NULL;
// 	m_pID_PICTURE_ItemWall = NULL;
// 	m_pID_LISTIMG_Aim1 = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
// 	m_pID_TEXT_UseMoneyZ = NULL;
// 	m_pID_TEXT_UseMoney = NULL;
// 	m_pID_LIST_BaseProperty = NULL;
// 	m_pID_LIST_BaseProperty2 = NULL;
// 	m_pID_PICTURE_LeftTitle = NULL;
// 	m_pID_PICTURE_TitleWord = NULL;
// 	m_pID_TEXT_GoldPlating = NULL;
// 	m_pID_LISTIMG_Aim2 = NULL;
// 	m_pID_LIST_Quality = NULL;
	m_pID_PICTURE_DecompoundEffect = NULL;
	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;
}

// Frame
bool CUI_ID_FRAME_Decompound::OnFrameRun()
{
	if( IsVisable() )
	{
		// 走路或跳跃打断吟唱
		if( m_bStartIntonate )
		{
			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
			if( pMe && (pMe->IsMoving() || pMe->IsJumping()) )
			{
				m_bStartIntonate = false;
				s_CUI_Progress.SetProgressComplete();
			}
		}
		// 吟唱结束
		if( m_bStartIntonate && m_dwStartIntonateTime + m_nIntonateTime < HQ_TimeGetTime() )
		{
			m_bStartIntonate = false;
			s_CUI_Progress.SetProgressComplete();

			// 播放序列帧动画
			m_slideAnim.StartAnimation(HQ_TimeGetTime());
			m_bStartAnim = true;

			// 请求分解
			SCharItem* pCharItem = thePlayerRole.m_bag.GetCharItemFromIdx( m_iNormalBagIndex );
			if( pCharItem && CanDecompound(m_iNormalBagIndex, true) )
			{
				MsgAckReduceItem kDecompoundMsg;
				kDecompoundMsg.index = m_iNormalBagIndex;
				kDecompoundMsg.guid = pCharItem->itembaseinfo.nOnlyInt;
				GettheNetworkInput().SendMsg( &kDecompoundMsg );
			}
		}
	}

	return true;
}
bool CUI_ID_FRAME_Decompound::OnFrameRender()
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
                ID_BUTTON_CancelOnButtonClick(NULL);
            }
        }
		if( m_bStartAnim )
		{
			RECT rc;
			m_pID_PICTURE_DecompoundEffect->GetRealRect(&rc);
			m_slideAnim.Update(HQ_TimeGetTime(),&rc);
			if (!m_slideAnim.IsInAnimation())
			{
				m_bStartAnim = false;
				m_slideAnim.UnRelativePicResource();
			}
		}
	}
	return true;
}
// Button
//bool CUI_ID_FRAME_Decompound::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
//{
//	if(!m_pID_FRAME_Decompound)
//	{
//		assert(false&&"ui error");
//		return false;
//	}
//
//    SetBagItemLock(false);
//    ResetAll();
//	return true;
//}
//// Button
//bool CUI_ID_FRAME_Decompound::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
//{
//	return true;
//}
//// ListImg / ListEx
//bool CUI_ID_FRAME_Decompound::ID_LISTIMG_Aim1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
//										ControlIconDrag::S_ListImg* pItemDrag,
//										ControlIconDrag::S_ListImg* pItemSrc )
//{
//	return false;
//}
//bool CUI_ID_FRAME_Decompound::ID_LISTIMG_Aim1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
//bool CUI_ID_FRAME_Decompound::ID_LISTIMG_Aim1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
//bool CUI_ID_FRAME_Decompound::ID_LISTIMG_Aim1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
// ListImg / ListEx
bool CUI_ID_FRAME_Decompound::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_Decompound)
	{
		assert(false&&"ui error");
		return false;
	}

    if( !pItemDrag )
        return false;

    ID_LISTIMG_ArmourOnIconRButtonUp( 0, 0 );

	// 判断装备能否分解
	uint32 iCanSplit = GettheItemDetail().IsCanSplitItem( pItemDrag->m_pkIconInfo->GetItemId() );
	if( iCanSplit != ER_Success )
	{
		ShowSplitResult(iCanSplit);
		return false;
	}
	m_pID_BUTTON_Ok->SetEnable(true);

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
    if( pItemCommon && ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
        pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR ) )
    {
        ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
        if( !pImageSender )
            return false;

        // 包裹里
        if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
        {			
            m_iNormalBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
        }
        else
        {
            return false;
        }		

        RefreshArmour();
        SetBagItemLock(true);
        theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
    }	

	return false;
}
bool CUI_ID_FRAME_Decompound::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Decompound::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Decompound::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_Decompound)
	{
		assert(false&&"ui error");
		return false;
	}

    SetBagItemLock(false);
    ResetAll();
	m_pID_BUTTON_Ok->SetEnable(false);
	return false;
}
// Button
bool CUI_ID_FRAME_Decompound::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Decompound)
	{
		assert(false&&"ui error");
		return false;
	}

    if( m_pID_LISTIMG_Armour->GetNullItem() == -1 && m_iNormalBagIndex >= 0 && !m_bStartIntonate )//有装备
    {
        SCharItem* pCharItem = thePlayerRole.m_bag.GetCharItemFromIdx( m_iNormalBagIndex );
        if( pCharItem )
        {
            ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
            if( pItemDetail )
            {
                MsgAckReduceItem kDecompoundMsg;
                kDecompoundMsg.index = m_iNormalBagIndex;
                kDecompoundMsg.guid = pCharItem->itembaseinfo.nOnlyInt;

                char str[MAX_PATH] = {0};
                char str_color[MAX_PATH] = {0};
                Common::_tstring tstrName( pItemDetail->GetItemName() );
                S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
                DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemDetail->ustLevel );
                sprintf(str_color,"{#%8x=%s#}", dwColor, tstrName.c_str());
                sprintf(str, theXmlString.GetString(eText_ConfirmSplit), str_color);
                s_CUI_ID_FRAME_MessageBox.Show( str, "", CUI_ID_FRAME_MessageBox::eTypeYesNo, true, Decompound, &kDecompoundMsg, sizeof(kDecompoundMsg) );
            }
        }
    }
	return true;
}
// Button
bool CUI_ID_FRAME_Decompound::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_Decompound)
	{
		assert(false&&"ui error");
		return false;
	}

   // ID_BUTTON_CLOSEOnButtonClick(NULL);
    SetVisable(false);
	return true;
}
// List
// void CUI_ID_FRAME_Decompound::ID_LIST_BasePropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// }
// // List
// void CUI_ID_FRAME_Decompound::ID_LIST_BaseProperty2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// }
// ListImg / ListEx
//bool CUI_ID_FRAME_Decompound::ID_LISTIMG_Aim2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
//										ControlIconDrag::S_ListImg* pItemDrag,
//										ControlIconDrag::S_ListImg* pItemSrc )
//{
//	return false;
//}
//bool CUI_ID_FRAME_Decompound::ID_LISTIMG_Aim2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
//bool CUI_ID_FRAME_Decompound::ID_LISTIMG_Aim2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
//bool CUI_ID_FRAME_Decompound::ID_LISTIMG_Aim2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
// List
// void CUI_ID_FRAME_Decompound::ID_LIST_QualityOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// }

	// 装载UI
bool CUI_ID_FRAME_Decompound::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Decompound.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Decompound.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Decompound::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Decompound, s_CUI_ID_FRAME_DecompoundOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Decompound, s_CUI_ID_FRAME_DecompoundOnFrameRender );
//     theUiManager.OnButtonClick( ID_FRAME_Decompound, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_DecompoundID_BUTTON_CLOSEOnButtonClick );
//     theUiManager.OnButtonClick( ID_FRAME_Decompound, ID_BUTTON_help, s_CUI_ID_FRAME_DecompoundID_BUTTON_helpOnButtonClick );
//     theUiManager.OnIconDragOn( ID_FRAME_Decompound, ID_LISTIMG_Aim1, s_CUI_ID_FRAME_DecompoundID_LISTIMG_Aim1OnIconDragOn );
//     theUiManager.OnIconLDBClick( ID_FRAME_Decompound, ID_LISTIMG_Aim1, s_CUI_ID_FRAME_DecompoundID_LISTIMG_Aim1OnIconLDBClick );
//     theUiManager.OnIconButtonClick( ID_FRAME_Decompound, ID_LISTIMG_Aim1, s_CUI_ID_FRAME_DecompoundID_LISTIMG_Aim1OnIconButtonClick );
//     theUiManager.OnIconRButtonUp( ID_FRAME_Decompound, ID_LISTIMG_Aim1, s_CUI_ID_FRAME_DecompoundID_LISTIMG_Aim1OnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_Decompound, ID_LISTIMG_Armour, s_CUI_ID_FRAME_DecompoundID_LISTIMG_ArmourOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_Decompound, ID_LISTIMG_Armour, s_CUI_ID_FRAME_DecompoundID_LISTIMG_ArmourOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_Decompound, ID_LISTIMG_Armour, s_CUI_ID_FRAME_DecompoundID_LISTIMG_ArmourOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_Decompound, ID_LISTIMG_Armour, s_CUI_ID_FRAME_DecompoundID_LISTIMG_ArmourOnIconRButtonUp );
    theUiManager.OnButtonClick( ID_FRAME_Decompound, ID_BUTTON_Ok, s_CUI_ID_FRAME_DecompoundID_BUTTON_OkOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Decompound, ID_BUTTON_Cancel, s_CUI_ID_FRAME_DecompoundID_BUTTON_CancelOnButtonClick );
//     theUiManager.OnListSelectChange( ID_FRAME_Decompound, ID_LIST_BaseProperty, s_CUI_ID_FRAME_DecompoundID_LIST_BasePropertyOnListSelectChange );
   // theUiManager.OnListSelectChange( ID_FRAME_Decompound, ID_LIST_BaseProperty2, s_CUI_ID_FRAME_DecompoundID_LIST_BaseProperty2OnListSelectChange );
//     theUiManager.OnIconDragOn( ID_FRAME_Decompound, ID_LISTIMG_Aim2, s_CUI_ID_FRAME_DecompoundID_LISTIMG_Aim2OnIconDragOn );
//     theUiManager.OnIconLDBClick( ID_FRAME_Decompound, ID_LISTIMG_Aim2, s_CUI_ID_FRAME_DecompoundID_LISTIMG_Aim2OnIconLDBClick );
//     theUiManager.OnIconButtonClick( ID_FRAME_Decompound, ID_LISTIMG_Aim2, s_CUI_ID_FRAME_DecompoundID_LISTIMG_Aim2OnIconButtonClick );
//     theUiManager.OnIconRButtonUp( ID_FRAME_Decompound, ID_LISTIMG_Aim2, s_CUI_ID_FRAME_DecompoundID_LISTIMG_Aim2OnIconRButtonUp );
//     theUiManager.OnListSelectChange( ID_FRAME_Decompound, ID_LIST_Quality, s_CUI_ID_FRAME_DecompoundID_LIST_QualityOnListSelectChange );

	m_pID_FRAME_Decompound = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Decompound );
// 	m_pID_PICTURE_RightTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Decompound, ID_PICTURE_RightTitle );
// 	m_pID_PICTURE_MiddleTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Decompound, ID_PICTURE_MiddleTitle );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Decompound, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_Decompound, ID_BUTTON_help );
// 	m_pID_TEXT_Wall = (ControlText*)theUiManager.FindControl( ID_FRAME_Decompound, ID_TEXT_Wall );
// 	m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Decompound, ID_PICTURE_ItemWall );
// 	m_pID_LISTIMG_Aim1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Decompound, ID_LISTIMG_Aim1 );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Decompound, ID_LISTIMG_Armour );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Decompound, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Decompound, ID_BUTTON_Cancel );
// 	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_Decompound, ID_TEXT_UseMoneyZ );
// 	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_Decompound, ID_TEXT_UseMoney );
// 	m_pID_LIST_BaseProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_Decompound, ID_LIST_BaseProperty );
// 	m_pID_LIST_BaseProperty2 = (ControlList*)theUiManager.FindControl( ID_FRAME_Decompound, ID_LIST_BaseProperty2 );
// 	m_pID_PICTURE_LeftTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Decompound, ID_PICTURE_LeftTitle );
// 	m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Decompound, ID_PICTURE_TitleWord );
// 	m_pID_TEXT_GoldPlating = (ControlText*)theUiManager.FindControl( ID_FRAME_Decompound, ID_TEXT_GoldPlating );
// 	m_pID_LISTIMG_Aim2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Decompound, ID_LISTIMG_Aim2 );
// 	m_pID_LIST_Quality = (ControlList*)theUiManager.FindControl( ID_FRAME_Decompound, ID_LIST_Quality );
	m_pID_PICTURE_DecompoundEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Decompound, ID_PICTURE_DecompoundEffect );
// 	assert( m_pID_FRAME_Decompound );
// 	assert( m_pID_PICTURE_RightTitle );
// 	assert( m_pID_PICTURE_MiddleTitle );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
// 	assert( m_pID_TEXT_Wall );
// 	assert( m_pID_PICTURE_ItemWall );
// 	assert( m_pID_LISTIMG_Aim1 );
// 	assert( m_pID_LISTIMG_Armour );
// 	assert( m_pID_BUTTON_Ok );
// 	assert( m_pID_BUTTON_Cancel );
// 	assert( m_pID_TEXT_UseMoneyZ );
// 	assert( m_pID_TEXT_UseMoney );
// 	assert( m_pID_LIST_BaseProperty );
// 	assert( m_pID_LIST_BaseProperty2 );
// 	assert( m_pID_PICTURE_LeftTitle );
// 	assert( m_pID_PICTURE_TitleWord );
// 	assert( m_pID_TEXT_GoldPlating );
// 	assert( m_pID_LISTIMG_Aim2 );
// 	assert( m_pID_LIST_Quality );
// 	assert( m_pID_PICTURE_DecompoundEffect );
    m_pID_FRAME_Decompound->SetMsgProcFun( frame_msg );

//     m_pID_LIST_Quality->SetMsgHoldup(false);
//     m_pID_LIST_Quality->HaveSelBar( false );
//     m_pID_LIST_BaseProperty->SetMsgHoldup(false);
//     m_pID_LIST_BaseProperty->HaveSelBar( false );
//     m_pID_LIST_BaseProperty2->SetMsgHoldup(false);
//     m_pID_LIST_BaseProperty2->HaveSelBar( false );

    ResetAll();

	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;
	RECT rc;
	m_pID_PICTURE_DecompoundEffect->GetRealRect(&rc);
	m_slideAnim.Initialize("Ui\\Common\\DecompoundEffect\\DecompoundEffect", 20, rc, 1400);

    USE_SCRIPT( eUI_OBJECT_Decompound, this );

    SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Decompound::_UnLoadUI()
{
    CLOSE_SCRIPT( eUI_OBJECT_Decompound );
// 	m_pID_FRAME_Decompound = NULL;
// 	m_pID_PICTURE_RightTitle = NULL;
// 	m_pID_PICTURE_MiddleTitle = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
// 	m_pID_TEXT_Wall = NULL;
// 	m_pID_PICTURE_ItemWall = NULL;
// 	m_pID_LISTIMG_Aim1 = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
// 	m_pID_TEXT_UseMoneyZ = NULL;
// 	m_pID_TEXT_UseMoney = NULL;
// 	m_pID_LIST_BaseProperty = NULL;
// 	m_pID_LIST_BaseProperty2 = NULL;
// 	m_pID_PICTURE_LeftTitle = NULL;
// 	m_pID_PICTURE_TitleWord = NULL;
// 	m_pID_TEXT_GoldPlating = NULL;
// 	m_pID_LISTIMG_Aim2 = NULL;
// 	m_pID_LIST_Quality = NULL;
	m_pID_PICTURE_DecompoundEffect = NULL;
	if( m_bStartAnim )
	{
		m_bStartAnim = false;
		m_slideAnim.StopAnimation();
		m_slideAnim.UnRelativePicResource();
	}
	if( m_bStartIntonate )
	{
		m_bStartIntonate = false;
		s_CUI_Progress.SetProgressComplete();
	}

	return theUiManager.RemoveFrame( "Data\\UI\\Decompound.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Decompound::_IsVisable()
{
    if( m_pID_FRAME_Decompound )
	    return m_pID_FRAME_Decompound->IsVisable();
    return false;
}
// 设置是否可视
void CUI_ID_FRAME_Decompound::_SetVisable( const bool bVisable )
{
    if( m_pID_FRAME_Decompound )
    {
        if( bVisable )
        {
            s_CUI_ID_FRAME_PACK.SetVisable(true);
			ResetWindowPosition(m_pID_FRAME_Decompound, s_CUI_ID_FRAME_PACK.GetFrame());
            ResetAll();
            UpdateAtomVisible();
			m_pID_BUTTON_Ok->SetEnable(false);
        }
		if( m_bStartAnim )
		{
			m_bStartAnim = false;
			m_slideAnim.StopAnimation();
			m_slideAnim.UnRelativePicResource();
		}
		if( m_bStartIntonate )
		{
			m_bStartIntonate = false;
			s_CUI_Progress.SetProgressComplete();
		}
        m_pID_FRAME_Decompound->SetVisable( bVisable );
    }
}

void CUI_ID_FRAME_Decompound::ResetAll()
{
    m_iNormalBagIndex = -1;
    m_bNormalBagEnable = true;
//     m_pID_LIST_BaseProperty->Clear();
//     m_pID_LIST_BaseProperty2->Clear();
//     m_pID_LIST_Quality->Clear();
    m_pID_LISTIMG_Armour->Clear();
}

void CUI_ID_FRAME_Decompound::RefreshArmour()
{
    ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_iNormalBagIndex );
    if( !pItemImg )
        return;

    SetArmourInfo( pItemImg );
    UpdateAtomVisible();
   // UpdateArmourInfo( (SCharItem*)pItemImg->m_pkIconInfo->GetData(), m_pID_LIST_BaseProperty2 );
}

void CUI_ID_FRAME_Decompound::UpdateAtomVisible()
{
//     if( m_pID_LISTIMG_Armour->GetNullItem() == -1 )//有装备
//         m_pID_TEXT_GoldPlating->SetVisable(false);
//     else
//         m_pID_TEXT_GoldPlating->SetVisable(true);
}

void CUI_ID_FRAME_Decompound::SetArmourInfo( ControlIconDrag::S_ListImg* pListImg )
{
    if( pListImg )
    {
        m_pID_LISTIMG_Armour->Clear();
        m_pID_LISTIMG_Armour->SetItem( pListImg, 0 );
        m_pID_LISTIMG_Armour->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
        m_pID_LISTIMG_Armour->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;	
    }
}

void CUI_ID_FRAME_Decompound::DecompoundSuccess(int index)
{
	if( !m_pID_FRAME_Decompound )
		return;

    // 物品解锁
    int iItemIndex = index;
    if( iItemIndex >= 0 && iItemIndex < thePlayerRole.m_bag.GetNowBagSize() )
    {
        thePlayerRole.m_bag.m_pPackItem[index].storageinfo.bIsLocked = false;

        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, index, true );
    }
    ResetAll();
    UpdateAtomVisible();
}

void CUI_ID_FRAME_Decompound::RefreshBagEnable()
{
    if( m_iNormalBagIndex >= 0 && m_iNormalBagIndex < thePlayerRole.m_bag.GetNowBagSize() )
    {
        thePlayerRole.m_bag.m_pPackItem[m_iNormalBagIndex].storageinfo.bIsLocked = !m_bNormalBagEnable;

        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_iNormalBagIndex, true );
    }
}

void CUI_ID_FRAME_Decompound::SetBagItemLock( bool bLock )
{
    if( m_pID_LISTIMG_Armour->GetNullItem() == -1 && m_iNormalBagIndex != -1 )//有装备
    {
        m_bNormalBagEnable = !bLock;
        RefreshBagEnable();
    }
}

void CUI_ID_FRAME_Decompound::StartIntonate()
{
	if( !m_pID_FRAME_Decompound )
		return;

	// 开始吟唱
	if( !m_bStartIntonate )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if( pMe && !pMe->IsMoving() && !pMe->IsJumping() )
		{
			m_bStartIntonate = true;
			m_dwStartIntonateTime = HQ_TimeGetTime();
			m_nIntonateTime = 3000;
			s_CUI_Progress.ShowByTime( m_dwStartIntonateTime, m_nIntonateTime, true, 1, true, true, theXmlString.GetString(eText_Decompound_Progress) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString(eClient_AddInfo_2slk_11) );
		}
	}
}

void CUI_ID_FRAME_Decompound::ShowBaseInfo( void* pItemDetail, INT nType, SCharItem* pstItem )
{
    guardfunc;

    ItemDefine::SItemCommon *pItem = NULL;

    if( pItemDetail )
    {
        pItem = (ItemDefine::SItemCommon *)pItemDetail;
    }
    //物品品质
    char szTemp [256] = {0};
    DWORD dwNameColor = 0xFFFF6400;

    if (!pItem)
    {
        return;
    }
    ///	名称
    if( pItemDetail )
    {
        if (pstItem->itembaseinfo.ustItemID != CompoundItemID && pItem != NULL)
        {				
            Common::_tstring tstrName( pItem->GetItemName() );
            S_IconInfoHero::ReplaceSpecifiedName( pItem->ustLevel, tstrName );
            strncpy(szTemp, tstrName.c_str(), 255 );

        }
    }

    if ( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON
        || pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR)
    {
        if( pItemDetail )
        {
            if (pstItem->equipdata.gemHoleCount > SCharItem::EConstDefine_GemHoleMaxCount)
            {
                pstItem->equipdata.gemHoleCount = 0;
            }

            if (pstItem->equipdata.gemHoleCount > 0)
            {
                //sprintf( szTemp, "%s(%s)+%d",szName,theXmlString.GetString(pItem->ustLevel+eUI_ItemLvl_0), m_stItem.equipdata.gemHoleCount );
                dwNameColor = S_IconInfoHero::GetQualityColor(pItem->ustLevel);
            }
            else
            {
                //sprintf( szTemp, "%s(%s)", szName, theXmlString.GetString(pItem->ustLevel+eUI_ItemLvl_0) );
                dwNameColor = S_IconInfoHero::GetQualityColor( pItem->ustLevel );
            }
        }
    }
    else
    {
        //品质
        //sprintf( szTemp, "%s(%s)", szName, theXmlString.GetString( pItem->ustLevel+eUI_ItemLvl_0 ) );
        dwNameColor = S_IconInfoHero::GetQualityColor( pItem->ustLevel );
    }


    if (pstItem->equipdata.gemHoleCount == SCharItem::EConstDefine_GemHoleMaxCount)
    {
        dwNameColor = 0xFFA6A600;
    }

    ControlList::S_List sList;
    ControlList::S_List sTempList;
    sTempList.clear();
    sTempList.UseSelColor = false;

    sList.UseSelColor = false;		
    sList.clear();
    sList.SetData( szTemp, 0, 0, dwNameColor );
  //  m_pID_LIST_BaseProperty->AddItem( &sList );		

    if( pItemDetail )
    {
        if ( pstItem->itembaseinfo.szCreaterName[0] != 0 )
        {
            sprintf( szTemp," (%s)", pstItem->itembaseinfo.szCreaterName );
            sList.clear();
            sList.SetData( szTemp, 0, 0, 0xffffffff );
//             m_pID_LIST_BaseProperty->AddItem( &sList );	
//             m_pID_LIST_Quality->AddItem( &sTempList );
        }
    }
    // 绑定
    if( pItem && pItem->bIsCanBound )
    {
        if ( ( nType == ItemDefine::ITEMTYPE_ARMOUR || nType == ItemDefine::ITEMTYPE_WEAPON ) )
        {
			if ( pstItem->IsBounded())
            {				
                sList.clear();
                sList.SetData( theXmlString.GetString(eTip_BelongerDone), 0, 0, dwYellow );
//                 m_pID_LIST_BaseProperty2->AddItem( &sList );
//                 m_pID_LIST_Quality->AddItem( &sTempList );	
            }
            else
            {
                if( !pItem->bIsCanTrade )
                {
                    if ( pstItem->itembaseinfo.stPacketIdx != -1 ) //背包index不为-1说明在包里
                    {						
                        sList.clear();
                        sList.SetData( theXmlString.GetString(eTip_BelongerDone), 0, 0, dwYellow );
//                         m_pID_LIST_BaseProperty2->AddItem( &sList );	
//                         m_pID_LIST_Quality->AddItem( &sTempList );

                    }
                    else
                    {					
                        sList.clear();
                        sList.SetData( theXmlString.GetString(eTip_PickBound), 0, 0, dwYellow );
//                         m_pID_LIST_BaseProperty2->AddItem( &sList );	
//                         m_pID_LIST_Quality->AddItem( &sTempList );
                    }
                }
                else
                {					
                    sList.clear();
                    sList.SetData( theXmlString.GetString(eText_Title_Bound), 0, 0, dwYellow );
//                     m_pID_LIST_BaseProperty2->AddItem( &sList );	
//                     m_pID_LIST_Quality->AddItem( &sTempList );
                }

            }
        }			
    }

    return;
    unguard;
}
void CUI_ID_FRAME_Decompound::ShowCanWeapon( void* pItemDetail, INT nType, SCharItem* pItem )
{
    if( !pItem )
        return;

    char szTemp [256] = {0};

    if( nType == ItemDefine::ITEMTYPE_WEAPON ||
        nType == ItemDefine::ITEMTYPE_ARMOUR 
        )
    {
        ItemDefine::SItemCanEquip* pDeTail = NULL;
        if( pItemDetail )
        {
            pDeTail = (ItemDefine::SItemCanEquip*)pItemDetail;
        }		
        if (!pDeTail)
        {
            return;
        }
        INT	nHPMax = pDeTail->stHPMax;
        int nCurrHP = pItem->equipdata.usHP;		
        if ( nCurrHP < 0 )
        {
            nCurrHP = nHPMax;
        }

        ItemDefine::SItemCanEquip* pEquip = NULL;
        if (pItemDetail)
        {
            pEquip = (ItemDefine::SItemCanEquip*)pItemDetail;
        }	
        ControlList::S_List sList;
        sList.UseSelColor = false;
        int nAddPhyAtt = 0;
        int nAddPhyDef = 0;
        int nAddMagAtt = 0;
        int nAddMagDef = 0;
        int nNullGemCount = 0;		
        char szBuff[256] = {0};
        //时装没有星级
        if( !pDeTail->bFashion )
        {
            // 星级
			if( pItem->equipdata.ucLevel <= 9 )
				MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) -1, "{#100%d}", (int)pItem->equipdata.ucLevel );
			else
				MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) -1, "{#130%d}", (int)pItem->equipdata.ucLevel-10 );
            sList.clear();
            sList.SetData( szTemp );
          //  m_pID_LIST_BaseProperty2->AddItem( &sList );
            sList.clear();			
           // m_pID_LIST_Quality->AddItem( &sList );
        }

        //需要等级
        const DWORD dwColor1 = 0xffffffff;	
        DWORD dwNeedColor = 0xffffffff;
        if( pItemDetail )
        {

            //级别需求			

            if( thePlayerRole.GetLevel() < pEquip->stEquipLevelReq )//red			
                dwNeedColor = dwRed;				

            MeSprintf_s( szBuff, sizeof(szBuff)/sizeof(char) - 1, "%s %d", theXmlString.GetString(eUI_NeedLevel), (int)pEquip->stEquipLevelReq );
            sList.clear();
            sList.SetData( szBuff, 0, 0, dwNeedColor );
          //  m_pID_LIST_BaseProperty->AddItem( &sList );

            char szSex[128] = {0};
            BOOL bNeedShowSex = true;
            //性别
            switch(pEquip->cEquipSexReq)
            {
            case -1:
                bNeedShowSex = false;
                break;
            case Sex_Male:
                sprintf( szSex, "%s", theXmlString.GetString( eSex_Man ) );
                break;
            case Sex_Female:
                sprintf( szSex, "%s", theXmlString.GetString( eSex_FeMan ) );
                break;
            default:
                bNeedShowSex = false;
                break;
            }
            if( bNeedShowSex)
            {
                //性别需求
                if( pEquip->cEquipSexReq  == thePlayerRole.GetSex() )				
                    dwNeedColor = 0xffffffff;				
                else				
                    dwNeedColor = dwRed;				
                char szTemp[256] = {0};
                sprintf( szTemp, "%s %s", theXmlString.GetString(eUI_NeedSex), szSex );
                sList.clear();
                sList.SetData( szTemp, 0, 0, dwNeedColor );
               // m_pID_LIST_BaseProperty->AddItem( &sList );
            }
            int nProfession[EArmType_MaxSize - 1] = {0};
            BOOL bIsAllProfession = FALSE;
            INT nProCnt = 0;
            BOOL bIsMeIn = false;

            for( int i=0; i<EArmType_MaxSize - 1; i++ )
            {
                if( pEquip->arrayEquipArmsReq[i] )
                {
                    nProCnt++;
                    nProfession[i] = 1;
                }
                else
                    nProfession[i] = 0;
            }
            if( nProCnt == EArmType_MaxSize - 1)
            {
                bIsAllProfession = true;
            }
            if( !bIsAllProfession )
            {
                char szProfession[128] = {0};
                char szProfessionTemp[10] = {0};
                //职业
                BOOL bIsFirst = true;
                for ( int n = 0; n < EArmType_MaxSize - 1 ; n++ )
                {
                    if (nProfession[n] == 1)
                    {
                        int nStringEnum = 0;
                        switch(n)
                        {
                        case EArmType_Mage:
                            nStringEnum = eProfession_Mage;
                            break;
                        case EArmType_Taoist:
                            nStringEnum = eProfession_Taoist;	
                            break;
                        case EArmType_Assassin:
                            nStringEnum = eProfession_Assassin;					
                            break;
                        case EArmType_Warrior:
                            nStringEnum = eProfession_Warrior;
                            break;
                        case EArmType_Hunter:
                            nStringEnum = eProfession_Hunter;													
                            break;
                        default:
                            break;
                        }
                        if (bIsFirst)
                        {
                            strcpy( szProfession, theXmlString.GetString(nStringEnum) );
                            bIsFirst = false;
                        }
                        else
                        {
                            strcpy(szProfessionTemp," ");
                            HelperFunc::AddNCpy(szProfessionTemp, theXmlString.GetString(nStringEnum),sizeof(szProfessionTemp));									
                            HelperFunc::AddNCpy(szProfession,szProfessionTemp, sizeof(szProfession));
                        }	
                    }						
                }
                char szTemp[256] = {0};
                if( nProfession[g_nTheRoleProfession] == 1)				
                    dwNeedColor = 0xffffffff;				
                else				
                    dwNeedColor = dwRed;		
                sprintf( szTemp, "%s %s",theXmlString.GetString(eNeed_Profession), szProfession );
                sList.clear();
                sList.SetData( szTemp, 0, 0, dwNeedColor );
               // m_pID_LIST_BaseProperty->AddItem( &sList );
            }
            else
            {	
                sList.clear();
                sList.SetData( theXmlString.GetString(eText_AllPro), 0, 0, 0xffffffff );
               // m_pID_LIST_BaseProperty->AddItem( &sList );
            }				

        }
        //////////////////////////////////////////////////////////////////////////
        //耐久点数
        if( pItemDetail )
        {
            sprintf( szTemp, "%s %d/%d", theXmlString.GetString(eEquip_Durable), nCurrHP, nHPMax );			
            if( nCurrHP > 0 )
                dwNeedColor = 0xffffffff;
            else
                dwNeedColor = dwRed;
            sList.clear();
            sList.SetData( szTemp, 0, 0, dwNeedColor );
           // m_pID_LIST_BaseProperty2->AddItem( &sList );
            sList.clear();			
          //  m_pID_LIST_Quality->AddItem( &sList );
        }

        // end 显示耐久
    }	

    return;
}

void CUI_ID_FRAME_Decompound::ShowWeapon( void* pItemDetail, INT nType, SCharItem* pItem )
{

    char szTemp [256] = {0};
    if( nType != ItemDefine::ITEMTYPE_WEAPON )
        return;

    //武器类型	
    ItemDefine::SItemWeapon* pWeapon = NULL;
    if (pItemDetail)
    {
        pWeapon = (ItemDefine::SItemWeapon*)pItemDetail;
    }	
    if (pWeapon)
    {		
        ControlList::S_List sList;
        sList.UseSelColor = false;
        // 远程攻击
        if( pWeapon->attackMagic != 0 )  
        {  
            sprintf( szTemp, "%s+%d", theXmlString.GetString( eTip_sAddMagicAttack ),
                (int)GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackMagic, pItem->equipdata.ucLevel ) );
            //theXmlString.GetString( eTip_PreText_Normal ), 
            sList.clear();
            sList.SetData( szTemp, 0, 0, 0xffffffff );
            //m_pID_LIST_BaseProperty2->AddItem( &sList );
            sList.clear();
           // m_pID_LIST_Quality->AddItem( &sList );
        }		

        // 近程攻击
        if( pWeapon->attackPhysics != 0 )  
        {  
            sprintf( szTemp, "%s+%d",theXmlString.GetString( eTip_sAddShortAttack ),
                (int)GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackPhysics, pItem->equipdata.ucLevel ) );
            //theXmlString.GetString( eTip_PreText_Normal ), 
            sList.clear();
            sList.SetData( szTemp, 0, 0, 0xffffffff );
           // m_pID_LIST_BaseProperty2->AddItem( &sList );
            sList.clear();
          //  m_pID_LIST_Quality->AddItem( &sList );
        }

        
    }
}

void CUI_ID_FRAME_Decompound::ShowArmour( void* pItemDetail, INT nType, SCharItem* pItem )
{
    if( nType != ItemDefine::ITEMTYPE_ARMOUR )
        return;

    char szTemp [256] = {0};	
    ItemDefine::SItemArmour* pArmour = NULL;
    DWORD dwDestColor = 0xffffffff;

    if ( pItemDetail )
    {
        if( pItemDetail )
        {
            pArmour = (ItemDefine::SItemArmour*)pItemDetail;
        }
        ControlList::S_List sList;
        sList.UseSelColor = false;		
		//ITEM_SHOW_INT_PRETEXT( GetAttributeWithLevel( pArmour->ustEquipType, pArmour->nHpMax, pItem->equipdata.ucLevel ),	theXmlString.GetString(eTip_sAddHPMax),					dwDestColor );	 // 血气
		//ITEM_SHOW_INT_PRETEXT( GetAttributeWithLevel( pArmour->ustEquipType, pArmour->sMpMax, pItem->equipdata.ucLevel ),	theXmlString.GetString(eTip_sAddMPMax),					dwDestColor );	 // 法力
		//ITEM_SHOW_INT_PRETEXT((int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->attack,pItem->equipdata.ucLevel ),	theXmlString.GetString(eTip_sAddShortAttack),				dwDestColor );	 // 近程攻击
		//ITEM_SHOW_INT_PRETEXT((int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->attack,	pItem->equipdata.ucLevel ),   theXmlString.GetString(eTip_sAddMagicAttack),			dwDestColor );	 // 远程攻击
		//ITEM_SHOW_INT_PRETEXT((int) pArmour->usAddtionDamage,		theXmlString.GetString(eTip_sAddDamage),				dwDestColor );	 // 附加伤害
		//ITEM_SHOW_INT_PRETEXT((int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->fPhysicsDefend, pItem->equipdata.ucLevel ),	theXmlString.GetString(eTip_sAddShortDefend),				dwDestColor );	 // 近防
		//ITEM_SHOW_INT_PRETEXT((int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->fMagicDefend,  pItem->equipdata.ucLevel ),		theXmlString.GetString(eTip_sAddMagicDefend),			dwDestColor );	 // 远防
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType, pArmour->usAddDamageResist, pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddDamageResist),			dwDestColor );   // 附加伤害抗
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->critical,	pItem->equipdata.ucLevel ),				theXmlString.GetString(eTip_sAddCritical),				dwDestColor );	 // 暴击率
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->criticalIntensity,pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddCriticalIntensity),		dwDestColor );	 // 暴击强度
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->criticalResist,pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddCriticalResist),		dwDestColor );	 // 暴击抗性		
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->exact,		pItem->equipdata.ucLevel ),				theXmlString.GetString(eTip_sAddExact),					dwDestColor );	 // 命中
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->dodge,	pItem->equipdata.ucLevel ),					theXmlString.GetString(eTip_sAddDodge),					dwDestColor );	 // 闪避
		////ITEM_SHOW_INT_PRETEXT(pArmour->sHpRestore,					theXmlString.GetString(eTip_sAddHPRestoreRate),			dwDestColor );	 // 气血回复速度
		//ITEM_SHOW_INT_PRETEXT(pArmour->sMpRestore,					theXmlString.GetString(eTip_sAddMPRestoreRate),			dwDestColor );	 // 法力回复速度
		//ITEM_SHOW_FLOAT_PRETEXT(pArmour->fMoveSpeed,				theXmlString.GetString(eTip_sAddMoveSpeed),				dwDestColor );	 // 移动速度 
		//ITEM_SHOW_INT_PRETEXT(pArmour->sAttSpeedAdd,				theXmlString.GetString(eTip_sAddMoveSpeed),				dwDestColor );	 // 攻击速度
		//ITEM_SHOW_INT_PRETEXT(pArmour->sIntonateSpeed,				theXmlString.GetString(eTip_sCastSpeed),				dwDestColor );	 // 吟唱速度
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->resistDread,	pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddGiddyResist),			dwDestColor );	 // 眩晕抗性
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->resistComa,	pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddStandResist),			dwDestColor );	 // 定身抗性
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->resistSlow,pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddSlowdownResist),		dwDestColor );	 // 减速抗性
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->resistSilence,	pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddTorpidResist),			dwDestColor );	 // 麻痹抗性

    }
}

void CUI_ID_FRAME_Decompound::UpdateArmourInfo( SCharItem* pItem, ControlList* pList )
{
//    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
//    if( !pItemCommon )
//        return;
//    ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
//    if( !pCanEquip )
//        return;
//
//   // m_pID_LIST_BaseProperty->Clear();
//    pList->Clear();
//   // m_pID_LIST_Quality->Clear();
//    ControlList::S_List sList;
//    sList.UseSelColor = false;
//    ShowBaseInfo( pItemCommon, pCanEquip->ucItemType, pItem );
//    ShowCanWeapon( pItemCommon, pCanEquip->ucItemType, pItem );
//    ShowWeapon( pItemCommon, pCanEquip->ucItemType, pItem );
//    ShowArmour( pItemCommon, pCanEquip->ucItemType, pItem );
//    // 随机属性
//    if( pCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR  && pCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
//        return;	
//
//    // 显示鉴定等级ui
//    unsigned short usRandEvalValue_Identify = S_IconInfoHero::GetEquipRandomEvaluate( pItemCommon, pCanEquip->ucItemType, CRandPropertyEvaluate::PropertyEvaluate_Identify, *pItem );
//    unsigned short usRandEvalValue_OpenLight = S_IconInfoHero::GetEquipRandomEvaluate( pItemCommon, pCanEquip->ucItemType, CRandPropertyEvaluate::PropertyEvaluate_OpenLight, *pItem );	
//
//    int nRandValue = 0;
//    char szTemp[256] = {0};
//    int nTipPreTextIndex = 0;
//    //bool bHaveRand = false;
//    // 鉴定还需要另外显示‘鉴定:’
//    if( usRandEvalValue_Identify != InvalidLogicNumber )
//    {
//        MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) - 1, "%s:", theXmlString.GetString( eText_Identify ) );
//        sList.clear();
//        sList.SetData( szTemp, 0, 0, 0xffffffff );
//       // m_pID_LIST_BaseProperty2->AddItem( &sList );
//        MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) - 1, "{#30%d}", usRandEvalValue_Identify );
//        sList.clear();
//        sList.SetData( szTemp, 0, 0, 0xffffffff );
//      //  m_pID_LIST_Quality->AddItem( &sList );
//        //去掉多余的行
////         if( m_pID_LIST_Quality->GetListItem( m_pID_LIST_Quality->GetListItemCnt() - 1 )->m_szText[0]
////         == '\0' )
////             m_pID_LIST_Quality->RemoveListItem( m_pID_LIST_Quality->GetListItemCnt() - 1 );
//    }
//
//
//    for (int nloop = 0; nloop < SCharItem::EConstDefine_BaseRandMaxCount; nloop++)
//    {
//        ItemDefine::SRandAttribute* pArmourRand = NULL;
//        unsigned short usRand =pItem->equipdata.baseRands[nloop];
//        if( nloop >= pCanEquip->additiveRandCount )//&& ( nloop != ( SCharItem::e_AddRandIndex ) ) )//随机个数以内
//            continue;
//
//        if( usRand == InvalidLogicNumber )// 显示问号
//        {   /*
//            // 品质介于2-5，现在套装也显示
//            if( pCanEquip->ustLevel >= 2 && pCanEquip->ustLevel <= 5 )
//            {
//                MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) - 1, "%s %s", theXmlString.GetString( eTip_PreText_Addition1 + nTipPreTextIndex ),
//                    theXmlString.GetString( eTip_PreText_NoIdentify ) );
//                nTipPreTextIndex++;
//                DWORD dwColor = dwBlue;
//                if( nloop == ( SCharItem::e_AddRandIndex ) )
//                {
//                    MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) - 1, "%s %s", theXmlString.GetString( eTip_PreText_KaiGuang ),
//                        theXmlString.GetString( eTip_PreText_NoKaiGuang ) );
//                    dwColor = dwYellow;
//                    //m_pID_TEXT_EspecialProperty->SetText( szTemp, dwYellow );					
//                }				
//                sList.clear();
//                sList.SetData( szTemp, 0, 0, dwColor );
//                m_pID_LIST_BaseProperty2->AddItem( &sList );
//                sList.clear();			
//                m_pID_LIST_Quality->AddItem( &sList );
//
//            }*/
//            continue;
//        }
//
//        pArmourRand = GettheItemDetail().GetRandByID(pItem->equipdata.baseRands[nloop]);
//
//        if (!pArmourRand)
//            continue;
//
//        for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
//        {
//            nRandValue = S_IconInfoHero::GetRandValueByType( pArmourRand, i );
//            if( pArmourRand->type[i] == CItemDetail::RT_None )continue;
//
//            //if( nloop == ( SCharItem::e_AddRandIndex ) )//开光
//            {
//                sprintf( szTemp, "%s+%d", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ), nRandValue );  
//                //theXmlString.GetString( eTip_PreText_KaiGuang ), 
//
//                /*m_pID_TEXT_EspecialProperty->SetText( szTemp, dwYellow );*/
//                sList.clear();
//                sList.SetData( szTemp, 0, 0, dwYellow );
//                m_pID_LIST_BaseProperty2->AddItem( &sList );
//                MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) - 1, "{#30%d}", usRandEvalValue_OpenLight );
//                sList.clear();
//                sList.SetData( szTemp, 0, 0, 0xffffffff );
//                m_pID_LIST_Quality->AddItem( &sList );
//                //去掉多余的行
//                if( m_pID_LIST_Quality->GetListItem( m_pID_LIST_Quality->GetListItemCnt() - 1 )->m_szText[0]
//                == '\0' )
//                    m_pID_LIST_Quality->RemoveListItem( m_pID_LIST_Quality->GetListItemCnt() - 1 );
//                continue;
//            }
//
//            if( nRandValue != InvalidLogicNumber )  
//            {  
//                //bHaveRand = true;
//                sprintf( szTemp, "%s+%d", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ), nRandValue );  
//                //theXmlString.GetString( eTip_PreText_Addition1 + nTipPreTextIndex ), 
//                nTipPreTextIndex ++ ;
//
//                sList.clear();
//                sList.SetData( szTemp, 0, 0, dwBlue );
//                m_pID_LIST_BaseProperty2->AddItem( &sList );
//                sList.clear();
//                m_pID_LIST_Quality->AddItem( &sList );
//
//            }			
//        }
//    }		
}

bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
    if ( bMsgUsed == true || g_GameState != G_MAIN || !s_CUI_ID_FRAME_Decompound.IsVisable())
        return false;

    if( msg == WM_KEYUP )
    {
        if( wParam == VK_ESCAPE )
        {
            s_CUI_ID_FRAME_Decompound.ID_BUTTON_CancelOnButtonClick(NULL);
            return true;
        }
    }

    return false;
}

bool CUI_ID_FRAME_Decompound::CanDecompound(int iNormalBagIndex, bool bShowInfo)
{
	if( !m_pID_FRAME_Decompound )
		return false;
	if( iNormalBagIndex >= 0 )//有装备
	{
		SCharItem* pCharItem = thePlayerRole.m_bag.GetCharItemFromIdx( iNormalBagIndex );
		if( pCharItem )
		{
			ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
			if( pItemDetail )
			{
				// 判断物品是否能分解
				uint32 iCanSplit = GettheItemDetail().IsCanSplitItem(pCharItem->itembaseinfo.ustItemID);
				if( iCanSplit == ER_Success )
					return true;
				else if( bShowInfo )
				{
					ShowSplitResult(iCanSplit);
				}
			}
		}
	}
	return false;
}
