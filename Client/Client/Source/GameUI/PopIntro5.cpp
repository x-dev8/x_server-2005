/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\PopIntro5.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PopIntro5.h"
#include "Common.h"
#include "ItemDetailConfig.h"
#include "Ui\IconManagerClient.h"
#include "Pack.h"
#include "Ui/baseProperty.h"

CUI_ID_FRAME_PopIntro5 s_CUI_ID_FRAME_PopIntro5;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PopIntro5, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PopIntro5, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PopIntro5, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PopIntro5, ID_LISTIMG_EquipOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PopIntro5, ID_LISTIMG_EquipOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PopIntro5, ID_LISTIMG_EquipOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PopIntro5, ID_LISTIMG_EquipOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PopIntro5, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_PopIntro5::CUI_ID_FRAME_PopIntro5()
{
	// Member
	m_pID_FRAME_PopIntro5 = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_LISTIMG_Equip = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_EquipName = NULL;

    m_nItemId = -1;
}

// Frame
bool CUI_ID_FRAME_PopIntro5::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_PopIntro5::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_PopIntro5::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
    // 打开的背包指定到物品所在页       modified by zhuomeng.hu		[1/4/2011]
	s_CUI_ID_FRAME_PACK.SetVisable( true );
    SCharItem charItem;
    if( thePlayerRole.m_bag.GetItemByItemID( m_nItemId, &charItem ) )
    {
        s_CUI_ID_FRAME_PACK.SwitchToBag( BT_NormalItemBag );
        s_CUI_ID_FRAME_PACK.DisplayTaskItemEff( BT_NormalItemBag, m_nItemId );
    }
    else if( thePlayerRole.m_bagMaterial.GetItemByItemID( m_nItemId, &charItem ) )
    {
        s_CUI_ID_FRAME_PACK.SwitchToBag( BT_MaterialBag );
        s_CUI_ID_FRAME_PACK.DisplayTaskItemEff( BT_MaterialBag, m_nItemId );
    }
    else if( thePlayerRole.m_bagTask.GetItemByItemID( m_nItemId, &charItem ) )
    {
        s_CUI_ID_FRAME_PACK.SwitchToBag( BT_TaskBag );
        s_CUI_ID_FRAME_PACK.DisplayTaskItemEff( BT_TaskBag, m_nItemId );
    }

	s_CUI_ID_FRAME_BaseProperty.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_BaseProperty.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
	SetVisable(false);
	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_PopIntro5::ID_LISTIMG_EquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_PopIntro5::ID_LISTIMG_EquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_PopIntro5::ID_LISTIMG_EquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_PopIntro5::ID_LISTIMG_EquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// Button
bool CUI_ID_FRAME_PopIntro5::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_PopIntro5::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PopIntro5.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PopIntro5.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_PopIntro5::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PopIntro5, s_CUI_ID_FRAME_PopIntro5OnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PopIntro5, s_CUI_ID_FRAME_PopIntro5OnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PopIntro5, ID_BUTTON_Ok, s_CUI_ID_FRAME_PopIntro5ID_BUTTON_OkOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_PopIntro5, ID_LISTIMG_Equip, s_CUI_ID_FRAME_PopIntro5ID_LISTIMG_EquipOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PopIntro5, ID_LISTIMG_Equip, s_CUI_ID_FRAME_PopIntro5ID_LISTIMG_EquipOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PopIntro5, ID_LISTIMG_Equip, s_CUI_ID_FRAME_PopIntro5ID_LISTIMG_EquipOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PopIntro5, ID_LISTIMG_Equip, s_CUI_ID_FRAME_PopIntro5ID_LISTIMG_EquipOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_PopIntro5, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_PopIntro5ID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_PopIntro5 = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PopIntro5 );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_PopIntro5, ID_BUTTON_Ok );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_PopIntro5, ID_TEXT_Info );
	m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PopIntro5, ID_LISTIMG_Equip );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PopIntro5, ID_BUTTON_CLOSE );
	m_pID_TEXT_EquipName = (ControlText*)theUiManager.FindControl( ID_FRAME_PopIntro5, ID_TEXT_EquipName );
	m_pID_FRAME_PopIntro5->enableEscKey( false );

	m_pID_LISTIMG_Equip->SetCanbePick(false);
	m_pID_LISTIMG_Equip->ShowPressEffect(false);

	assert( m_pID_FRAME_PopIntro5 );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_TEXT_Info );
	assert( m_pID_LISTIMG_Equip );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_EquipName );
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_PopIntro5::_UnLoadUI()
{
	m_pID_FRAME_PopIntro5 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\PopIntro5.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_PopIntro5::_IsVisable()
{
	if(!m_pID_FRAME_PopIntro5)
		return false;

	return m_pID_FRAME_PopIntro5->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_PopIntro5::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_PopIntro5)
		return;

	m_pID_FRAME_PopIntro5->SetVisable( bVisable );
}

void  CUI_ID_FRAME_PopIntro5::ShowItemInfo(std::string &strInfo)
{
	if(!m_pID_FRAME_PopIntro5)
		return;

	if(strInfo.length() <= 0)
		return;

	std::string::size_type nBegin = strInfo.find("[");
	std::string::size_type nEnd   = strInfo.find("]");
	if(nEnd == std::string::npos || nBegin == std::string::npos)
		return;

	std::string strItemId = strInfo.substr(1,nEnd - nBegin - 1);
	std::string strTipInfo   = strInfo.substr(nEnd + 1);

	int nItemId  = 0;
	if(sscanf_s(strItemId.c_str(),"%d",&nItemId) != 1)
		return;

	ItemDefine::SItemCommon * pCommon = GettheItemDetail().GetItemByID(nItemId);
	if(!pCommon)
		return;

	m_pID_TEXT_EquipName->SetText(pCommon->GetItemName(),S_IconInfoHero::GetQualityColor(pCommon->ustLevel));

	char szWord[256] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s",strTipInfo.c_str());

	m_pID_TEXT_Info->SetText(szWord);

	m_pID_LISTIMG_Equip->Clear();
	ControlListImage::S_ListImg img;
	img.SetData(nItemId,1);
	m_pID_LISTIMG_Equip->SetItem(&img);

    m_nItemId = nItemId;
}

