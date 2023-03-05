/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\法宝资源\法宝\法宝\Talisman.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Talisman.h"
#include "Common.h"
#include "XmlStringLanguage.h"
#include "PlayerRole.h"
#include "IconManagerClient.h"
#include "TalismanConfig.h"
#include "GameDefineTalisman.h"

CUI_ID_FRAME_Talisman s_CUI_ID_FRAME_Talisman;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Talisman, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Talisman, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_BUTTON_HELPOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_LISTIMG_ItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_LISTIMG_ItemOnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_LIST_TalismanListOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_LISTIMG_GenreOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_LISTIMG_GenreOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_LISTIMG_GenreOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Talisman, ID_LISTIMG_GenreOnIconRButtonUp )
CUI_ID_FRAME_Talisman::CUI_ID_FRAME_Talisman()
{
	// Member
	m_pID_FRAME_Talisman = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_PICTURE_Yingxiang = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_TEXT_Generation = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_TEXT_Item = NULL;
	m_pID_TEXT_Item2 = NULL;
	m_pID_PROGRESS_32378 = NULL;
	m_pID_TEXT_ItemIntroduce = NULL;
	m_pID_LIST_TalismanList = NULL;
	m_pID_LISTIMG_Genre = NULL;
	m_pID_TEXT_Moment = NULL;
	m_pID_TEXT_Attribute = NULL;

}
// Frame
bool CUI_ID_FRAME_Talisman::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_Talisman::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_Talisman::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Talisman::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Talisman::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Talisman::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Talisman::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return false;
}
bool CUI_ID_FRAME_Talisman::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return false;
}
bool CUI_ID_FRAME_Talisman::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return false;
}
bool CUI_ID_FRAME_Talisman::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Talisman )
		return false;


	return false;
}
// List
void CUI_ID_FRAME_Talisman::ID_LIST_TalismanListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Talisman )
		return;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Talisman::ID_LISTIMG_GenreOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return false;
}
bool CUI_ID_FRAME_Talisman::ID_LISTIMG_GenreOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return false;
}
bool CUI_ID_FRAME_Talisman::ID_LISTIMG_GenreOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return false;
}
bool CUI_ID_FRAME_Talisman::ID_LISTIMG_GenreOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return false;
}

// 装载UI
bool CUI_ID_FRAME_Talisman::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Talisman.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Talisman.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Talisman::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Talisman, s_CUI_ID_FRAME_TalismanOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Talisman, s_CUI_ID_FRAME_TalismanOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Talisman, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TalismanID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Talisman, ID_BUTTON_Right, s_CUI_ID_FRAME_TalismanID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Talisman, ID_BUTTON_Left, s_CUI_ID_FRAME_TalismanID_BUTTON_LeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Talisman, ID_BUTTON_HELP, s_CUI_ID_FRAME_TalismanID_BUTTON_HELPOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Talisman, ID_LISTIMG_Item, s_CUI_ID_FRAME_TalismanID_LISTIMG_ItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Talisman, ID_LISTIMG_Item, s_CUI_ID_FRAME_TalismanID_LISTIMG_ItemOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Talisman, ID_LISTIMG_Item, s_CUI_ID_FRAME_TalismanID_LISTIMG_ItemOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Talisman, ID_LISTIMG_Item, s_CUI_ID_FRAME_TalismanID_LISTIMG_ItemOnIconRButtonUp );
	theUiManager.OnListSelectChange( ID_FRAME_Talisman, ID_LIST_TalismanList, s_CUI_ID_FRAME_TalismanID_LIST_TalismanListOnListSelectChange );
	theUiManager.OnIconDragOn( ID_FRAME_Talisman, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TalismanID_LISTIMG_GenreOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Talisman, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TalismanID_LISTIMG_GenreOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Talisman, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TalismanID_LISTIMG_GenreOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Talisman, ID_LISTIMG_Genre, s_CUI_ID_FRAME_TalismanID_LISTIMG_GenreOnIconRButtonUp );

	m_pID_FRAME_Talisman = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Talisman );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Talisman, ID_BUTTON_CLOSE );
	m_pID_PICTURE_Yingxiang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Talisman, ID_PICTURE_Yingxiang );
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_Talisman, ID_BUTTON_Right );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_Talisman, ID_BUTTON_Left );
	m_pID_TEXT_Generation = (ControlText*)theUiManager.FindControl( ID_FRAME_Talisman, ID_TEXT_Generation );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_Talisman, ID_BUTTON_HELP );
	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Talisman, ID_LISTIMG_Item );
	m_pID_TEXT_Item = (ControlText*)theUiManager.FindControl( ID_FRAME_Talisman, ID_TEXT_Item );
	m_pID_TEXT_Item2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Talisman, ID_TEXT_Item2 );
	m_pID_PROGRESS_32378 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Talisman, ID_PROGRESS_32378 );
	m_pID_TEXT_ItemIntroduce = (ControlText*)theUiManager.FindControl( ID_FRAME_Talisman, ID_TEXT_ItemIntroduce );
	m_pID_LIST_TalismanList = (ControlList*)theUiManager.FindControl( ID_FRAME_Talisman, ID_LIST_TalismanList );
	m_pID_LISTIMG_Genre = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Talisman, ID_LISTIMG_Genre );
	m_pID_TEXT_Moment = (ControlText*)theUiManager.FindControl( ID_FRAME_Talisman, ID_TEXT_Moment );
	m_pID_TEXT_Attribute = (ControlText*)theUiManager.FindControl( ID_FRAME_Talisman, ID_TEXT_Attribute );

	assert( m_pID_FRAME_Talisman );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_PICTURE_Yingxiang );
	assert( m_pID_BUTTON_Right );
	assert( m_pID_BUTTON_Left );
	assert( m_pID_TEXT_Generation );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_LISTIMG_Item );
	assert( m_pID_TEXT_Item );
	assert( m_pID_TEXT_Item2 );
	assert( m_pID_PROGRESS_32378 );
	assert( m_pID_TEXT_ItemIntroduce );
	assert( m_pID_LIST_TalismanList );
	assert( m_pID_LISTIMG_Genre );
	assert( m_pID_TEXT_Moment );
	assert( m_pID_TEXT_Attribute );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Talisman::_UnLoadUI()
{
	m_pID_FRAME_Talisman = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_PICTURE_Yingxiang = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_TEXT_Generation = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_TEXT_Item = NULL;
	m_pID_TEXT_Item2 = NULL;
	m_pID_PROGRESS_32378 = NULL;
	m_pID_TEXT_ItemIntroduce = NULL;
	m_pID_LIST_TalismanList = NULL;
	m_pID_LISTIMG_Genre = NULL;
	m_pID_TEXT_Moment = NULL;
	m_pID_TEXT_Attribute = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Talisman.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Talisman::_IsVisable()
{
	if ( !m_pID_FRAME_Talisman )
		return false;
	return m_pID_FRAME_Talisman->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Talisman::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Talisman )
		return;

	m_pID_FRAME_Talisman->SetVisable( bVisable );
}

void CUI_ID_FRAME_Talisman::UpdateTalisman(SCharItem *pItem)
{
	if(!pItem)
		return;

	UpdateBaseInfo(pItem);
	UpdateExp(pItem);
	UpdateRebuldInfo(pItem);
}

void CUI_ID_FRAME_Talisman::UpdateBaseInfo(SCharItem *pItem)
{
	if(!pItem)
		return;

	ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
	if(!pItemCommon)
		return;

	//法宝图标
	ControlListImage::S_ListImg img;
	img.SetData(pItem->itembaseinfo.ustItemID,1);
	m_pID_LISTIMG_Item->SetItem(&img);

	//设置名字
	m_pID_TEXT_Item->SetText(pItemCommon->GetItemName());

	//道行显示
	char szInfo[256] = {0};
	MeSprintf_s(szInfo,sizeof(szInfo),theXmlString.GetString(eText_TalismanDaoHangLimilt),pItem->talismandata.daoxing);
	m_pID_TEXT_Item2->SetText(szInfo);

	//设置属性图片

	std::string strInfo;
	strInfo.clear();
	//设置法宝基本属性
	//品质
	switch( pItem->talismandata.quality )
	{
	case ETalismanQuality_Normal:        
		MeSprintf_s( szInfo, sizeof(szInfo), theXmlString.GetString(eText_TalismanQuility), theXmlString.GetString(eText_TalismanNormal) );
		break;
	case ETalismanQuality_Fine:          
		MeSprintf_s( szInfo, sizeof(szInfo), theXmlString.GetString(eText_TalismanQuility), theXmlString.GetString(eText_TalismanRight)/*"良品"*/ );
		break;
	case ETalismanQuality_Refine:         
		MeSprintf_s( szInfo, sizeof(szInfo), theXmlString.GetString(eText_TalismanQuility), theXmlString.GetString(eText_TalismanNicity)/*"精品"*/ );
		break;
	case ETalismanQuality_Fairy:          
		MeSprintf_s( szInfo, sizeof(szInfo), theXmlString.GetString(eText_TalismanQuility), theXmlString.GetString(eText_TalismanImmortal)/*"仙物"*/ );
		break;
	case ETalismanQuality_Deity:         
		MeSprintf_s( szInfo, sizeof(szInfo), theXmlString.GetString(eText_TalismanQuility), theXmlString.GetString(eText_TalismanGold)/*"神器"*/ );
		break;
	}

	strInfo = szInfo;
	strInfo += "  ";
	//是否绑定
	if(pItem->IsBounded())
		MeSprintf_s(szInfo,sizeof(szInfo),"%s",theXmlString.GetString(eTip_BelongerDone));
	else
		MeSprintf_s(szInfo,sizeof(szInfo),"%s",theXmlString.GetString(eText_TalismanBound));
	strInfo += szInfo;
	strInfo += "\n";
	//法宝类型
	//等级
	MeSprintf_s(szInfo,sizeof(szInfo),"%s:%d/%d"/*等级:%d//%d*/,theXmlString.GetString(eText_Level),pItem->talismandata.level,thePlayerRole.GetData(CPlayerRole::TYPE_LEVEL));
	strInfo += szInfo;
	strInfo += "\n"; 

	//灵气
	MeSprintf_s(szInfo,sizeof(szInfo),theXmlString.GetString(eText_TalismanNimBus),pItem->talismandata.nimbus,pItem->talismandata.nimbusMax);
	strInfo += szInfo;
	strInfo += "\n";

	//灵气回复率
	MeSprintf_s(szInfo,sizeof(szInfo),theXmlString.GetString(eText_TalismanNimBusRate),pItem->talismandata.nimbusRestore);
	strInfo += szInfo;
	strInfo += "\n";

	//属性显示
	if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_TALISMAN)
		return;

	ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)pItemCommon;
	// 近
	if(pArmour->attackPhysics != 0)
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->attackPhysics, pItem->equipdata.ucLevel );
		MeSprintf_s( szInfo, sizeof( szInfo ), "%s+%d", theXmlString.GetString( eText_PlayAtt_Short ), nAttStarVal );
		strInfo += szInfo;
		strInfo += "\n";
	}

	// 魔
	if(pArmour->attackMagic != 0)
	{
		int nAttStarVal = (int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->attackMagic, pItem->equipdata.ucLevel );
		MeSprintf_s( szInfo, sizeof( szInfo ), "%s+%d", theXmlString.GetString( eText_PlayAtt_Magic ), nAttStarVal );
		strInfo += szInfo;
		strInfo += "\n";
	}

	// 防御
	if( pArmour->defendPhysics != 0 )  
	{
		// 近
		MeSprintf_s( szInfo, sizeof( szInfo ), "%s+%d", theXmlString.GetString( eText_PlayDef_Short ),
			(int)(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->defendPhysics, pItem->equipdata.ucLevel ) );  
		strInfo += szInfo;
		strInfo += "\n";
	}

	if( pArmour->defendMagic != 0 )  
	{
		// 魔
		MeSprintf_s( szInfo, sizeof( szInfo ), "%s+%d", theXmlString.GetString( eText_PlayDef_Magic ),
			(int)(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->defendMagic, pItem->equipdata.ucLevel ) );  
		strInfo += szInfo;
		strInfo += "\n";
	}
	/*
	 * Author: 2012-10-11 21:43:20 liaojie
	 * Desc:   
	 */
	if( pArmour->Hp != 0 )  
	{
		// Hp
		MeSprintf_s( szInfo, sizeof( szInfo ), "%s+%d", theXmlString.GetString( eTip_sAddHPMax ),
			(int)(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Hp, pItem->equipdata.ucLevel ) );  
		strInfo += szInfo;
		strInfo += "\n";
	}
	if( pArmour->Mp != 0 )  
	{
		// Mp
		MeSprintf_s( szInfo, sizeof( szInfo ), "%s+%d", theXmlString.GetString( eTip_sAddMPMax ),
			(int)(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Mp, pItem->equipdata.ucLevel ) );  
		strInfo += szInfo;
		strInfo += "\n";
	}

	//命中率
	if(pArmour->exact != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddExact),(int)pArmour->exact);
		strInfo += szInfo;
		strInfo += "\n";
	}

	//闪避率
	if(pArmour->dodge != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddDodge),(int)pArmour->dodge);
		strInfo += szInfo;
		strInfo += "\n";
	}

	//暴击率
	if(pArmour->critical != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddCritical),(int)pArmour->critical);
		strInfo += szInfo;
		strInfo += "\n";
	}

	//韧性
	if(pArmour->tenacity != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddTenacity),(int)pArmour->tenacity);
		strInfo += szInfo;
		strInfo += "\n";
	}
#pragma message("法宝这儿也要加下元素属性")
	//破甲伤害
	if(pArmour->breakStrike != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddBreakStrike),(int)pArmour->breakStrike);
		strInfo += szInfo;
		strInfo += "\n";
	}
	//破甲抗性
	if(pArmour->breakResist != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddBreakResist),(int)pArmour->breakResist);
		strInfo += szInfo;
		strInfo += "\n";
	}
	//贯穿伤害
	if(pArmour->stabStrike != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddStabStrike),(int)pArmour->stabStrike);
		strInfo += szInfo;
		strInfo += "\n";
	}
	//贯穿抗性
	if(pArmour->stabResist != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddStabResist),(int)pArmour->stabResist);
		strInfo += szInfo;
		strInfo += "\n";
	}
	//元素伤害
	if(pArmour->elementStrike != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddElementStrike),(int)pArmour->elementStrike);
		strInfo += szInfo;
		strInfo += "\n";
	}
	//元素抗性
	if(pArmour->elementResist != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddElementResist),(int)pArmour->elementResist);
		strInfo += szInfo;
		strInfo += "\n";
	}
	//毒素伤害
	if(pArmour->toxinStrike != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddToxinStrike),(int)pArmour->toxinStrike);
		strInfo += szInfo;
		strInfo += "\n";
	}
	//毒素抗性
	if(pArmour->toxinResist != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddToxinResist),(int)pArmour->toxinResist);
		strInfo += szInfo;
		strInfo += "\n";
	}
	//精神伤害
	if(pArmour->spiritStrike != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddSpiritStrike),(int)pArmour->spiritStrike);
		strInfo += szInfo;
		strInfo += "\n";
	}
	//精神抗性
	if(pArmour->spiritResist != 0)
	{
		MeSprintf_s(szInfo,sizeof(szInfo),"%s+%d",theXmlString.GetString(eTip_sAddSpiritResist),(int)pArmour->spiritResist);
		strInfo += szInfo;
		strInfo += "\n";
	}

	//法宝描述
	strInfo += pItemCommon->GetItemDesc();

	m_pID_TEXT_Attribute->SetText(strInfo.c_str());

	ItemDefine::SItemTalisman* pEquip = (ItemDefine::SItemTalisman*)pItemCommon;
	if(!pEquip)
		return;

	ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(pEquip->skillId,pEquip->skillLevel);
	if(!pSkill)
		return;

	UpdateSkillDesc(pSkill);
}

void CUI_ID_FRAME_Talisman::UpdateExp(SCharItem *pItem)
{
	if(!pItem)
		return;


}

void CUI_ID_FRAME_Talisman::UpdateSkillDesc(ItemDefine::SItemSkill* pSkill)
{
	if(!pSkill)
		return;

	m_pID_TEXT_ItemIntroduce->SetText(pSkill->GetItemDesc());
}

void CUI_ID_FRAME_Talisman::UpdateRebuldInfo(SCharItem *pItem)
{
	if(!pItem)
		return;

	for (int i = 0;i < (int)SCharItem::EConstDefine_TalismanRandMaxCount;++i)
	{
		int nValue = pItem->talismandata.talismanRands[i];
		if(nValue == 0)
			continue;

		TalismanConfig::STalismanRandAttr *pAttr = theTalismanConfig.GetTalismanRandAttr(nValue);
		if(!pAttr)
			continue;

		ControlList::S_List stItem;
		stItem.SetData(pAttr->strDesc.c_str());
		m_pID_LIST_TalismanList->AddItem(&stItem);
	}
}

bool CUI_ID_FRAME_Talisman::IsTalismanList(ControlListImage *pSender)
{
	if(!pSender)
		return false;

	return pSender == m_pID_LISTIMG_Item;
}