/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\PetCompose.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PetCompose.h"
#include "PlayerRole.h"
#include "PackItemEnableManager.h"
#include "common.h"
#include "NetworkInput.h"
#include "ScreenInfoManager.h"
#include "packet_interface.h"
#include "Me3d/global.h"
#include "Me3d/model/mexres.h"
#include "SeeSuAnimal.h"
CUI_ID_FRAME_PetCompose s_CUI_ID_FRAME_PetCompose;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PetCompose, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PetCompose, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_BUTTON_CanelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_BUTTON_CLOSEOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_LIST_PetListOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_LIST_PicOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_BUTTON_PetMainOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_BUTTON_PetSecondOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_BUTTON_PetMainCanelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_BUTTON_PetSecondCanelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_BUTTON_PetMainOpenOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetCompose, ID_BUTTON_PetSecondOpenOnButtonClick )
CUI_ID_FRAME_PetCompose::CUI_ID_FRAME_PetCompose()
{
	// Member
	m_pID_FRAME_PetCompose = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Canel = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Material = NULL;
	m_pID_LIST_PetList = NULL;
	m_pID_BUTTON_PetMain = NULL;
	m_pID_BUTTON_PetSecond = NULL;
	m_pID_TEXT_PetMain = NULL;
	m_pID_TEXT_PetSecond = NULL;
	m_pID_LIST_Pic = NULL;
	//m_pID_TEXT_Money = NULL;
	m_pID_PICTURE_PetMain = NULL;
	m_pID_PICTURE_PetSecond = NULL;
	m_pID_BUTTON_PetMainCanel = NULL;
	m_pID_BUTTON_PetSecondCanel = NULL;

	m_pID_BUTTON_PetMainOpen = NULL;
	m_pID_BUTTON_PetSecondOpen = NULL;


	m_ItemID = 0;
	m_ItemSum = 0;
	m_MainGuID = 0;
	m_SecGuID= 0;
	m_BagItemSum= 0;
	m_StepLogTime= 0;

	m_IsEnterItem= false;
}
// Frame
bool CUI_ID_FRAME_PetCompose::OnFrameRun()
{
	UpdateMaterial();
	return true;
}
bool CUI_ID_FRAME_PetCompose::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_PetCompose::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_PetCompose::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_PetCompose::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_PetCompose::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_PetCompose::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	OnPetCompose();
	return true;
}
// Button
bool CUI_ID_FRAME_PetCompose::ID_BUTTON_CanelOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_PetCompose::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// List
void CUI_ID_FRAME_PetCompose::ID_LIST_PetListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
void CUI_ID_FRAME_PetCompose::ID_LIST_PicOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{

}
// Button
bool CUI_ID_FRAME_PetCompose::ID_BUTTON_PetMainOnButtonClick( ControlObject* pSender )
{
	SetPetToMain();
	return true;
}
// Button
bool CUI_ID_FRAME_PetCompose::ID_BUTTON_PetSecondOnButtonClick( ControlObject* pSender )
{
	SetPetToSecond();
	return true;
}
// Button
bool CUI_ID_FRAME_PetCompose::ID_BUTTON_PetMainCanelOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_PetCompose)
		return false;
	if(m_MainGuID == 0)
		return true;
	m_MainGuID = 0;
	m_pID_TEXT_PetMain->SetText("");
	m_pID_PICTURE_PetMain->SetPicName("");
	m_pID_PICTURE_PetMain->SetVisable(false);
	UpdatePetPic();

	//设置无法合成 和 设置材料为空
	m_pID_BUTTON_OK->SetEnable(false);
	int BagSize = thePlayerRole.m_bagMaterial.GetNowBagSize();
	for(int i =0;i<BagSize;++i)
	{
		SCharItem * pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(i);
		if(!pItem || pItem->itembaseinfo.ustItemID !=m_ItemID || m_ItemID == 0) continue;
		m_IsEnterItem = false;
		CPackItemEnableManager::Instance()->RefreshBagItemEnable(&thePlayerRole.m_bagMaterial,i,true);
	}
	//清空UI上的材料图标和 一些数据
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(0,0);
	m_pID_LISTIMG_Material->SetItem(&pItems,0);
	m_ItemID = 0;
	return true;
}
// Button
bool CUI_ID_FRAME_PetCompose::ID_BUTTON_PetSecondCanelOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_PetCompose)
		return false;
	if(m_SecGuID == 0)
		return true;
	m_SecGuID = 0;
	m_pID_TEXT_PetSecond->SetText("");
	m_pID_PICTURE_PetSecond->SetPicName("");
	m_pID_PICTURE_PetSecond->SetVisable(false);
	UpdatePetPic();
	//设置无法合成 和 设置材料为空
	m_pID_BUTTON_OK->SetEnable(false);
	int BagSize = thePlayerRole.m_bagMaterial.GetNowBagSize();
	for(int i =0;i<BagSize;++i)
	{
		SCharItem * pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(i);
		if(!pItem || pItem->itembaseinfo.ustItemID !=m_ItemID || m_ItemID == 0) continue;
		m_IsEnterItem = false;
		CPackItemEnableManager::Instance()->RefreshBagItemEnable(&thePlayerRole.m_bagMaterial,i,true);
	}
	//清空UI上的材料图标和 一些数据
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(0,0);
	m_pID_LISTIMG_Material->SetItem(&pItems,0);
	m_ItemID = 0;
	return true;
}
bool CUI_ID_FRAME_PetCompose::ID_BUTTON_PetMainOpenOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_PetCompose)
		return false;
	if(m_MainGuID == 0)
		return true;
	if(!thePlayerRole.GetPetByGUID(m_MainGuID))
		return true;
	s_CUI_ID_FRAME_SeeSuAnimal.SetVisable(true);
	s_CUI_ID_FRAME_SeeSuAnimal.SetPetItem(*thePlayerRole.GetPetByGUID(m_MainGuID));
	return true;
}
bool CUI_ID_FRAME_PetCompose::ID_BUTTON_PetSecondOpenOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_PetCompose)
		return false;
	if(m_SecGuID == 0)
		return true;
	if(!thePlayerRole.GetPetByGUID(m_SecGuID))
		return true;
	s_CUI_ID_FRAME_SeeSuAnimal.SetVisable(true);
	s_CUI_ID_FRAME_SeeSuAnimal.SetPetItem(*thePlayerRole.GetPetByGUID(m_SecGuID));
	return true;
}
// 装载UI
bool CUI_ID_FRAME_PetCompose::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PetCompose.MEUI", false, UI_Render_LayerThree  );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PetCompose.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PetCompose::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PetCompose, s_CUI_ID_FRAME_PetComposeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PetCompose, s_CUI_ID_FRAME_PetComposeOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_PetCompose, ID_LISTIMG_Material, s_CUI_ID_FRAME_PetComposeID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetCompose, ID_LISTIMG_Material, s_CUI_ID_FRAME_PetComposeID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetCompose, ID_LISTIMG_Material, s_CUI_ID_FRAME_PetComposeID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetCompose, ID_LISTIMG_Material, s_CUI_ID_FRAME_PetComposeID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_PetCompose, ID_BUTTON_OK, s_CUI_ID_FRAME_PetComposeID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCompose, ID_BUTTON_Canel, s_CUI_ID_FRAME_PetComposeID_BUTTON_CanelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCompose, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_PetComposeID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_PetCompose, ID_LIST_PetList, s_CUI_ID_FRAME_PetComposeID_LIST_PetListOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_PetCompose, ID_BUTTON_PetMain, s_CUI_ID_FRAME_PetComposeID_BUTTON_PetMainOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCompose, ID_BUTTON_PetSecond, s_CUI_ID_FRAME_PetComposeID_BUTTON_PetSecondOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_PetCompose, ID_LIST_Pic, s_CUI_ID_FRAME_PetComposeID_LIST_PicOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_PetCompose, ID_BUTTON_PetMainCanel, s_CUI_ID_FRAME_PetComposeID_BUTTON_PetMainCanelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCompose, ID_BUTTON_PetSecondCanel, s_CUI_ID_FRAME_PetComposeID_BUTTON_PetSecondCanelOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_PetCompose, ID_BUTTON_PetMainOpen, s_CUI_ID_FRAME_PetComposeID_BUTTON_PetMainOpenOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCompose, ID_BUTTON_PetSecondOpen, s_CUI_ID_FRAME_PetComposeID_BUTTON_PetSecondOpenOnButtonClick );

	m_pID_FRAME_PetCompose = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetCompose );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_LISTIMG_Material );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_BUTTON_OK );
	m_pID_BUTTON_Canel = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_BUTTON_Canel );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_BUTTON_CLOSE );
	m_pID_TEXT_Material = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_TEXT_Material );
	m_pID_LIST_PetList = (ControlList*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_LIST_PetList );
	m_pID_BUTTON_PetMain = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_BUTTON_PetMain );
	m_pID_BUTTON_PetSecond = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_BUTTON_PetSecond );
	m_pID_TEXT_PetMain = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_TEXT_PetMain );
	m_pID_TEXT_PetSecond = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_TEXT_PetSecond );
	m_pID_LIST_Pic = (ControlList*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_LIST_Pic );
	//m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_TEXT_Money );
	m_pID_PICTURE_PetMain = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_PICTURE_PetMain );
	m_pID_PICTURE_PetSecond = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_PICTURE_PetSecond );
	m_pID_BUTTON_PetMainCanel = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_BUTTON_PetMainCanel );
	m_pID_BUTTON_PetSecondCanel = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_BUTTON_PetSecondCanel );
	m_pID_BUTTON_PetMainOpen  = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_BUTTON_PetMainOpen );
	m_pID_BUTTON_PetSecondOpen = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCompose, ID_BUTTON_PetSecondOpen );
	assert( m_pID_FRAME_PetCompose );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Canel );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Material );
	assert( m_pID_LIST_PetList );
	assert( m_pID_BUTTON_PetMain );
	assert( m_pID_BUTTON_PetSecond );
	assert( m_pID_TEXT_PetMain );
	assert( m_pID_TEXT_PetSecond );
	assert( m_pID_LIST_Pic );
	//assert( m_pID_TEXT_Money );
	assert( m_pID_PICTURE_PetMain );
	assert( m_pID_PICTURE_PetSecond );
	assert( m_pID_BUTTON_PetMainCanel );
	assert( m_pID_BUTTON_PetSecondCanel );
	assert( m_pID_BUTTON_PetMainOpen );
	assert( m_pID_BUTTON_PetSecondOpen );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PetCompose::_UnLoadUI()
{
	m_pID_FRAME_PetCompose = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\PetCompose.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PetCompose::_IsVisable()
{
	return m_pID_FRAME_PetCompose->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PetCompose::_SetVisable( const bool bVisable )
{
	if(bVisable)
		OnInit();
	else
		SetEmpty();
	m_pID_FRAME_PetCompose->SetVisable( bVisable );
}
bool CUI_ID_FRAME_PetCompose::IsPackItemBeUsing( __int64 nGuid )
{
	if(!IsVisable())
        return false;
	if(m_SecGuID ==0 || m_MainGuID ==0)
		return false;
	SCharItem  pItems;
	thePlayerRole.m_bagMaterial.GetItemByOnlyeID(nGuid,&pItems);
	if(pItems.itembaseinfo.ustItemID == m_ItemID)
		return m_IsEnterItem;
	else
		return false;
}
void CUI_ID_FRAME_PetCompose::OnInit()
{
	//1.将所有的副将设置到List里面去 根据Index
	m_pID_LIST_PetList->Clear();
	m_pID_LIST_Pic->Clear();
	ControlList::S_List	stItem;
	char szText[128] = {0};
	for(size_t i =0;i<thePlayerRole.GetPetCount();++i)
	{
		SPetItem& pPet = thePlayerRole.GetPetByIndex(i);
		if(pPet.baseInfo.petId == InvalidLogicNumber)
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s","");
		else
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s",pPet.baseInfo.szName);
		stItem.SetData(szText, 0, NULL, 0);
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_PetList->AddItem(&stItem, NULL, false);
		stItem.clear();
		memset(szText, 0, sizeof(szText));
	}
	if(thePlayerRole.GetPetCount() >0)
		m_pID_LISTIMG_Material->SetSelect(0);
	else
	{
		m_pID_BUTTON_PetMain->SetEnable(false);
		m_pID_BUTTON_PetSecond->SetEnable(false);
	}
	//2.将指定按钮设置为灰色
	m_pID_BUTTON_OK->SetEnable(false);
	//3.清空其他的Ui
	m_pID_TEXT_Material->SetText("");
	m_pID_TEXT_PetMain->SetText("");
	m_pID_TEXT_PetSecond->SetText("");
	//m_pID_TEXT_Money->SetText("");
	m_pID_LISTIMG_Material->Clear();
	m_pID_PICTURE_PetMain->SetPicName("");
	m_pID_PICTURE_PetSecond->SetPicName("");
	m_pID_PICTURE_PetMain->SetVisable(false);
	m_pID_PICTURE_PetSecond->SetVisable(false);
	//4 清空已经保存的数据
	m_ItemID = 0;
	m_ItemSum = 0;
	m_MainGuID = 0;
	m_SecGuID= 0;
	m_BagItemSum= 0;
	m_StepLogTime= 0;
}
void CUI_ID_FRAME_PetCompose::SetEmpty()
{
	//当UI关闭的时候
	m_pID_BUTTON_OK->SetEnable(false);
	m_pID_TEXT_Material->SetText("");
	m_pID_TEXT_PetMain->SetText("");
	m_pID_TEXT_PetSecond->SetText("");
	//m_pID_TEXT_Money->SetText("");
	m_pID_LIST_PetList->Clear();
	m_pID_LIST_Pic->Clear();
	m_pID_PICTURE_PetMain->SetPicName("");
	m_pID_PICTURE_PetSecond->SetPicName("");
	m_pID_PICTURE_PetMain->SetVisable(false);
	m_pID_PICTURE_PetSecond->SetVisable(false);
	//设置背包的材料亮起来
	int BagSize = thePlayerRole.m_bagMaterial.GetNowBagSize();
	for(int i =0;i<BagSize;++i)
	{
		SCharItem * pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(i);
		if(!pItem || pItem->itembaseinfo.ustItemID !=m_ItemID || m_ItemID == 0) continue;
		m_IsEnterItem = false;
		CPackItemEnableManager::Instance()->RefreshBagItemEnable(&thePlayerRole.m_bagMaterial,i,true);
	}
	//清空UI上的材料图标和 一些数据
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(0,0);
	m_pID_LISTIMG_Material->SetItem(&pItems,0);
	//清空属性
	m_ItemID = 0;
	m_ItemSum = 0; 
	m_MainGuID = 0;
	m_SecGuID= 0;
	m_BagItemSum= 0;
	m_StepLogTime= 0;
}
void CUI_ID_FRAME_PetCompose::SetPetToMain()
{
	//设置主要的副将
	int Index = m_pID_LIST_PetList->GetCurSelIndex();
	if(Index <0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_None));
		return;
	}
	SPetItem& pPet = thePlayerRole.GetPetByIndex(Index);
	if(pPet.baseInfo.petId == InvalidLogicNumber)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_None));
		return;
	}
	if(m_SecGuID !=0 && m_SecGuID ==pPet.baseInfo.guid)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_NorOne));
		return;//不可以是同一个副将
	}
	if(m_MainGuID == pPet.baseInfo.guid)
	{
		/*m_MainGuID = 0;
		m_pID_TEXT_PetMain->SetText("");
		UpdatePetPic();*/
		return;
	}
	m_MainGuID = pPet.baseInfo.guid;
	m_pID_TEXT_PetMain->SetText(pPet.baseInfo.szName);//设置好名称
	UpdatePetPic();
	if(m_SecGuID !=0 && m_MainGuID !=0)
		SetMaterial();
}
void CUI_ID_FRAME_PetCompose::SetPetToSecond()
{
	int Index = m_pID_LIST_PetList->GetCurSelIndex();
	if(Index <0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_None));
		return;
	}
	SPetItem& pPet = thePlayerRole.GetPetByIndex(Index);
	if(pPet.baseInfo.petId == InvalidLogicNumber)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_None));
		return;
	}
	if(m_MainGuID !=0 && m_MainGuID ==pPet.baseInfo.guid)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_NorOne));
		return;//不可以是同一个副将
	}
	if(m_SecGuID == pPet.baseInfo.guid)
	{
		/*m_SecGuID = 0;
		m_pID_TEXT_PetSecond->SetText("");
		UpdatePetPic();*/
		return;
	}
	m_SecGuID = pPet.baseInfo.guid;
	m_pID_TEXT_PetSecond->SetText(pPet.baseInfo.szName);//设置好名称
	UpdatePetPic();
	if(m_SecGuID !=0 && m_MainGuID !=0)
		SetMaterial();
}
void CUI_ID_FRAME_PetCompose::SetMaterial()
{
	//设置UI上副将合成需要的材料
	m_ItemID = SID_PetComPose;//合成需要的材料
	m_ItemSum = 1;//合成需要的数量
	int sum =thePlayerRole.m_bagMaterial.GetItemCount(m_ItemID);
	m_BagItemSum = sum;
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(m_ItemID,sum);
	if(sum == 0)
		pItems.SetEnable(eIcon_Disable);
	else
		pItems.SetEnable(eIcon_Enable);
	m_pID_LISTIMG_Material->SetItem(&pItems,0);
	//设置好物品的名称
	ItemDefine::SItemCommon* pItemCommon_s = GettheItemDetail().GetItemByID( m_ItemID);
	if(pItemCommon_s)
	{
		char szText[24] = {0};
		sprintf_s(szText, sizeof(szText)-1,"%s X%u",pItemCommon_s->GetItemName(),m_ItemSum);
		m_pID_TEXT_Material->SetText(szText);//物品的名称
	}
	if(sum >= m_ItemSum)
		m_pID_BUTTON_OK->SetEnable(true);
	//让背包的物品灰起来
	int BagSize = thePlayerRole.m_bagMaterial.GetNowBagSize();
	for(int i =0;i<BagSize;++i)
	{
		SCharItem * pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(i);
		if(!pItem || pItem->itembaseinfo.ustItemID !=m_ItemID || m_ItemID == 0) continue;
		m_IsEnterItem = true;
		CPackItemEnableManager::Instance()->RefreshBagItemEnable(&thePlayerRole.m_bagMaterial,i,true);		
	}
}	
void CUI_ID_FRAME_PetCompose::UpdateMaterial()
{	
	//更新材料的数量
	if(m_IsEnterItem && !IsVisable())
	{
		m_IsEnterItem = false;
		SetEmpty();
	}
	if(!IsVisable() || m_ItemID == 0) return;
	if(HQ_TimeGetTime() - m_StepLogTime < 1000) return;//1秒更新一次
	int sum =thePlayerRole.m_bagMaterial.GetItemCount(m_ItemID);
	if(sum != m_BagItemSum)
	{
		m_BagItemSum = sum;
		ControlIconDrag::S_ListImg pItems;
		pItems.SetData(m_ItemID,sum);
		if(sum == 0)
			pItems.SetEnable(eIcon_Disable);
		else
			pItems.SetEnable(eIcon_Enable);
		m_pID_LISTIMG_Material->SetItem(&pItems,0);
		if(sum >= m_ItemSum)
			m_pID_BUTTON_OK->SetEnable(true);
		else
			m_pID_BUTTON_OK->SetEnable(false);
		//让背包的物品灰起来
		int BagSize = thePlayerRole.m_bagMaterial.GetNowBagSize();
		for(int i =0;i<BagSize;++i)
		{
			SCharItem * pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(i);
			if(!pItem || pItem->itembaseinfo.ustItemID !=m_ItemID || m_ItemID == 0) continue;
			m_IsEnterItem = true;
			CPackItemEnableManager::Instance()->RefreshBagItemEnable(&thePlayerRole.m_bagMaterial,i,true);
		}
	}
	m_StepLogTime = HQ_TimeGetTime();
}
bool SendPetComposeMsg(char bSend, void *pData )
{
	if( !bSend )
		return false;
	Msg* pMsg = static_cast<Msg*>(pData);
	GettheNetworkInput().SendMsg( pMsg );	
	s_CUI_ID_FRAME_PetCompose.SetVisable(false);
	return true;
}
void CUI_ID_FRAME_PetCompose::OnPetCompose()
{
	//将2个副将进行合成
	if(m_MainGuID == 0 || m_SecGuID == 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_Erro1));
		return;
	}
	//GetActivedPet
	SPetItem* pMainPet = thePlayerRole.GetPetByGUID(m_MainGuID);
	SPetItem* pSecPet = thePlayerRole.GetPetByGUID(m_SecGuID);
	if(!pMainPet || !pSecPet)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_Erro2));
		return;
	}
	if(pMainPet->baseInfo.petId == InvalidLogicNumber || pSecPet->baseInfo.petId == InvalidLogicNumber)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_Erro2));
		return;
	}
	SPetItem* pAcPet = thePlayerRole.GetActivedPet();
	if(pAcPet && (pAcPet->baseInfo.guid == m_MainGuID || pAcPet->baseInfo.guid == m_SecGuID))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_Erro3));
		return;//2个待合成的副将都不可以出战
	}
	//判断副将身上是否有装备 有的话不可以合成
	for(int i =0;i<SPetItem::PetEquip_MaxSum;++i)
	{
		if(pSecPet->baseInfo.PetEquip[i].GetItemGuid() != 0)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_Equip));
			return;
		}
	}
	//判断材料的数量是否满足
	int sum =thePlayerRole.m_bagMaterial.GetItemCount(m_ItemID);
	if(sum < m_ItemSum)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PetComPose_Erro4));
		return;//2个待合成的副将都不可以出战
	}
	MsgPetCompose msg;
	msg.MainPetGuid = m_MainGuID;
	msg.SecPetGuid = m_SecGuID;
	if(pSecPet->baseInfo.level < pMainPet->baseInfo.level
		|| (pSecPet->baseInfo.level == pMainPet->baseInfo.level && pSecPet->baseInfo.exp < pMainPet->baseInfo.exp)
		)
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_PetCompose_LevelMessage), "", CUI_ID_FRAME_MessageBox::eTypeYesNo, true, SendPetComposeMsg,&msg,msg.header.stLength);
	}
	else
	{
		GettheNetworkInput().SendMsg(&msg);
		//设置ui关闭
		SetVisable(false);
	}
}
void CUI_ID_FRAME_PetCompose::UpdatePetPic()
{
	m_pID_LIST_Pic->Clear();
	m_pID_LIST_Pic->SetShowStartHeight(m_pID_LIST_PetList->GetShowStartHeight());
	
	ControlList::S_List stEmptyItem;
	stEmptyItem.SetData("");

	ControlList::S_List stMainItem;
	stMainItem.SetData("{#4000}");

	ControlList::S_List stSecItem;
	stSecItem.SetData("{#4001}");

	for(size_t i=0;i<thePlayerRole.GetPetCount();++i)
	{
		if(thePlayerRole.GetPetByIndex(i).GetPetGuid() == m_MainGuID)
		{
			SetPetPic(&thePlayerRole.GetPetByIndex(i),true);
			m_pID_LIST_Pic->AddItem(&stMainItem);
		}
		else if(thePlayerRole.GetPetByIndex(i).GetPetGuid() == m_SecGuID)
		{
			SetPetPic(&thePlayerRole.GetPetByIndex(i),false);
			m_pID_LIST_Pic->AddItem(&stSecItem);
		}
		else
		{
			m_pID_LIST_Pic->AddItem(&stEmptyItem);
		}
	}
}
void CUI_ID_FRAME_PetCompose::SetPetPic(SPetItem* pPet,bool IsMain)
{
	ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById(pPet->GetPetID());
	if (pPetMonster == NULL)
		return;
	int m_nModelId = pPetMonster->iModelID;
	if(pPet->baseInfo.PetModeID !=0)
		m_nModelId = pPet->baseInfo.PetModeID;
	MexResMgr::Record* record = GetMexResMgr()->GetRecord(m_nModelId);
	if(IsMain)
	{
		m_pID_PICTURE_PetMain->SetVisable(true);
		m_pID_PICTURE_PetMain->SetPicName(record->headPicture.c_str());
	}
	else
	{
		m_pID_PICTURE_PetSecond->SetVisable(true);
		m_pID_PICTURE_PetSecond->SetPicName(record->headPicture.c_str());
	}
}