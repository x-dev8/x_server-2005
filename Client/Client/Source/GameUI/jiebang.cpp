/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\jiebang.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "jiebang.h"
#include "ItemDetail.h"
#include "GlobalDef.h"
#include "ui/Pack.h"
#include "PackItemEnableManager.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "ScreenInfoManager.h"
CUI_ID_FRAME_JieBang s_CUI_ID_FRAME_JieBang;
MAP_FRAME_RUN( s_CUI_ID_FRAME_JieBang, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_JieBang, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_LISTIMG_ZJ1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_LISTIMG_ZJ1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_LISTIMG_ZJ1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_LISTIMG_ZJ1OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_JieBang, ID_BUTTON_HELPOnButtonClick )
CUI_ID_FRAME_JieBang::CUI_ID_FRAME_JieBang()
{
	// Member
	m_pID_FRAME_JieBang = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_LISTIMG_ZJ1 = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_TEXT_EquipName = NULL;
	m_pID_TEXT_ItemName = NULL;


	m_unBindEquip = NULL;
	m_unBindBagSum = 0;
	m_unBindNeedSum = 0;
	m_StepLogTime=0;
	m_unBindIndex = -1;
}
	// Frame
	bool CUI_ID_FRAME_JieBang::OnFrameRun()
	{
		UpdateUIButtonByBagItem();
		return true;
	}
	bool CUI_ID_FRAME_JieBang::OnFrameRender()
	{
		return true;
	}
	// Button
	bool CUI_ID_FRAME_JieBang::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
	{
		return SetEmpty();//当关闭的时候
	}

	static void UIJiebang_VisableChanged(ControlObject* pObject)
	{
		if (!s_CUI_ID_FRAME_JieBang.IsVisable())
		{
			s_CUI_ID_FRAME_JieBang.SetEmpty();
		}
	}


	// ListImg / ListEx
	bool CUI_ID_FRAME_JieBang::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_JieBang::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_JieBang::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_JieBang::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// Button
	bool CUI_ID_FRAME_JieBang::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
	{
		if(SetEmpty())
			SetVisable(false);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_JieBang::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
	{
		if(m_unBindEquip)
			HandleUnBindEquip(m_unBindEquip->itembaseinfo.nOnlyInt);
		return true;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_JieBang::ID_LISTIMG_ZJ1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return SetItem(pSender, pItemDrag);
		return false;
	}
	bool CUI_ID_FRAME_JieBang::ID_LISTIMG_ZJ1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_JieBang::ID_LISTIMG_ZJ1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_JieBang::ID_LISTIMG_ZJ1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return SetEmpty();
	}
	// Button
	bool CUI_ID_FRAME_JieBang::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
	{
		return true;
	}
	// ListImg / ListEx

	// 装载UI
bool CUI_ID_FRAME_JieBang::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\jiebang.MEUI",false, UI_Render_LayerThree );
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\jiebang.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
bool CUI_ID_FRAME_JieBang::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_JieBang, s_CUI_ID_FRAME_JieBangOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_JieBang, s_CUI_ID_FRAME_JieBangOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_JieBang, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_JieBangID_BUTTON_CLOSEOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_JieBang, ID_LISTIMG_Material, s_CUI_ID_FRAME_JieBangID_LISTIMG_MaterialOnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_JieBang, ID_LISTIMG_Material, s_CUI_ID_FRAME_JieBangID_LISTIMG_MaterialOnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_JieBang, ID_LISTIMG_Material, s_CUI_ID_FRAME_JieBangID_LISTIMG_MaterialOnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_JieBang, ID_LISTIMG_Material, s_CUI_ID_FRAME_JieBangID_LISTIMG_MaterialOnIconRButtonUp );
theUiManager.OnButtonClick( ID_FRAME_JieBang, ID_BUTTON_Cancel, s_CUI_ID_FRAME_JieBangID_BUTTON_CancelOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_JieBang, ID_BUTTON_Ok, s_CUI_ID_FRAME_JieBangID_BUTTON_OkOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_JieBang, ID_LISTIMG_ZJ1, s_CUI_ID_FRAME_JieBangID_LISTIMG_ZJ1OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_JieBang, ID_LISTIMG_ZJ1, s_CUI_ID_FRAME_JieBangID_LISTIMG_ZJ1OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_JieBang, ID_LISTIMG_ZJ1, s_CUI_ID_FRAME_JieBangID_LISTIMG_ZJ1OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_JieBang, ID_LISTIMG_ZJ1, s_CUI_ID_FRAME_JieBangID_LISTIMG_ZJ1OnIconRButtonUp );
theUiManager.OnButtonClick( ID_FRAME_JieBang, ID_BUTTON_HELP, s_CUI_ID_FRAME_JieBangID_BUTTON_HELPOnButtonClick );

		m_pID_FRAME_JieBang = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_JieBang );
		m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_JieBang, ID_BUTTON_CLOSE );
		m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_JieBang, ID_TEXT_Money );
		m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_JieBang, ID_LISTIMG_Material );
		m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_JieBang, ID_BUTTON_Cancel );
		m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_JieBang, ID_BUTTON_Ok );
		m_pID_LISTIMG_ZJ1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_JieBang, ID_LISTIMG_ZJ1 );
		m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_JieBang, ID_BUTTON_HELP );

		m_pID_TEXT_EquipName = (ControlText*)theUiManager.FindControl( ID_FRAME_JieBang, ID_TEXT_EquipName );
		m_pID_TEXT_ItemName = (ControlText*)theUiManager.FindControl( ID_FRAME_JieBang, ID_TEXT_ItemName );

		m_pID_FRAME_JieBang->SetOnVisibleChangedFun(UIJiebang_VisableChanged);
		

		m_pID_BUTTON_Ok->SetEnable(false);
		assert( m_pID_FRAME_JieBang );
		assert( m_pID_BUTTON_CLOSE );
		assert( m_pID_TEXT_Money );
		assert( m_pID_LISTIMG_Material );
		assert( m_pID_BUTTON_Cancel );
		assert( m_pID_BUTTON_Ok );
		assert( m_pID_LISTIMG_ZJ1 );
		assert( m_pID_BUTTON_HELP );
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_JieBang::_UnLoadUI()
	{
		m_pID_FRAME_JieBang = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\jiebang.MEUI" );
	}
	// 是否可视
bool CUI_ID_FRAME_JieBang::_IsVisable()
	{
		return m_pID_FRAME_JieBang->IsVisable();
	}
	// 设置是否可视
void CUI_ID_FRAME_JieBang::_SetVisable( const bool bVisable )
{
	if(!bVisable)
		SetEmpty();
	m_pID_FRAME_JieBang->SetVisable( bVisable );
}
bool CUI_ID_FRAME_JieBang::IsPackItemBeUsing( __int64 nGuid )
{
	if(!IsVisable())
        return false;
	if(m_unBindEquip)
	{
		//UI 在工作中
		if(m_unBindEquip->itembaseinfo.nOnlyInt == nGuid)
			return true;
		SCharItem  pItems;
		thePlayerRole.m_bagMaterial.GetItemByOnlyeID(nGuid,&pItems);
		if(pItems.itembaseinfo.ustItemID == SID_UnBindItem)
			return true;
		return false;
	}
	else
		return false;
}
bool CUI_ID_FRAME_JieBang::SetEmpty()//清空UI上全部的信息 并且还原对背包的影响
{
	//清空UI上的数据
	//1.按钮置灰
	m_pID_BUTTON_Ok->SetEnable(false);
	//2 让背包的图标变亮起来 如果需要的话
	SetBagItemIsUnUse(false,m_unBindIndex);
	//3.材料图标清空
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(0,0);
	m_pID_LISTIMG_Material->SetItem(&pItems,0);
	//4.提示信息清空
	m_pID_TEXT_Money->SetText("");
	m_pID_TEXT_EquipName->SetText("");
	m_pID_TEXT_ItemName->SetText("");
	//5.装备清空
	m_pID_LISTIMG_ZJ1->SetItem(&pItems,0);
	m_unBindBagSum = 0;
	m_unBindNeedSum = 0;
	m_unBindEquip=NULL;
	m_unBindIndex = -1;
	return true;
}
bool CUI_ID_FRAME_JieBang::SetItem(ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag)
{
	//将拖拽到控件上的物品设置好  需要判断物品是否符合标准 必须是已经绑定的  并且可以解绑的  并且计算出解绑装备需要的物品数量和ID
	SetEmpty();//使用前先清空UI上的数据
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId());//回去物品的基本结构
	//1.判断物品能否绑定
	if(!pItemCommon)
	{
		ShowErrorMsgInScreen(eText_UnBind_Error1);
		return false;
	}
	if(!pItemCommon->IsCanEquip())
	{
		ShowErrorMsgInScreen(eText_UnBind_Error3);
		return false;
	}
	ItemDefine::SItemCanEquip* pEquipCommon = (ItemDefine::SItemCanEquip*)pItemCommon;
	if(!pEquipCommon)
	{
		ShowErrorMsgInScreen(eText_UnBind_Error1);
		return false;
	}
	if(!pEquipCommon->bIsCanBound)
	{
		ShowErrorMsgInScreen(eText_UnBind_Error2);
		return false;
	}
	//2.只有装备才继续处理
	if(!pEquipCommon->IsCanEquip())
	{
		ShowErrorMsgInScreen(eText_UnBind_Error3);
		return false;
	}
	SCharItem * pItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	if(!pItem)
	{
		ShowErrorMsgInScreen(eText_UnBind_Error1);
		return false;
	}
	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	if(!pImageSender )
	{
		ShowErrorMsgInScreen(eText_UnBind_Error1);
		return false;
	}
	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender))//非背包物品 无法解绑 
	{
		ShowErrorMsgInScreen(eText_UnBind_Error4);
		return false;
	}
	if(!pItem->IsBounded())
	{
		ShowErrorMsgInScreen(eText_UnBind_Error5);
		return false;//物品未绑定 不可以解绑
	}
	int MaxUnBindSum = pEquipCommon->unBindCount;//配置表读取的
	int NowUnBindSum = pItem->equipdata.unBindCount;//数据库中存储的 
	//if((NowUnBindSum == 0xFFFF && MaxUnBindSum !=0xFFFF) || ( MaxUnBindSum ==0xFFFF && NowUnBindSum != 0xFFFF))
	//{
	//	NowUnBindSum = MaxUnBindSum;
	//	pItem->equipdata.unBindCount = pEquipCommon->unBindCount;
	//}
	//if(MaxUnBindSum == 0)
	//{
	//	ShowErrorMsgInScreen(eText_UnBind_Error6);
	//	return false;//本物品无法解封
	//}
	//if(NowUnBindSum == 0 && MaxUnBindSum != 0xFFFF)
	//{
	//	ShowErrorMsgInScreen(eText_UnBind_Error7);
	//	return false;//当前物品解封次数已经使用完毕
	//}
	if(NowUnBindSum == 0xFFFF && MaxUnBindSum !=0xFFFF)
	{
		NowUnBindSum = MaxUnBindSum;
		pItem->equipdata.unBindCount = pEquipCommon->unBindCount;
	}
	if(NowUnBindSum == 0)
	{
		ShowErrorMsgInScreen(eText_UnBind_Error6);
		return false;//本物品无法解封
	}

	//判断物品是否有宝石镶嵌在上面 有的话 提示用户 解绑失败
	for(size_t i=0;i<pItem->EConstDefine_GemHoleMaxCount;++i)
	{
		if(pItem->equipdata.gemIds[i] != 0)
		{
			ShowErrorMsgInScreen(eText_UnBind_Error8);
			return false;//打过宝石的装备不可以解绑
		}
	}
	//获取物品的一些属性 
	//物品的星级 品质 等级
	float starLevel = pItem->equipdata.ucLevel+1;//物品为0
	float QueryLevel = pItem->equipdata.quality+1;//品质
	float level = pEquipCommon->stEquipLevelReq+1;//需要的级别
	int num = (int)((starLevel*0.7)*(4*0.2)*(level*0.1)*0.4) +1;
	//获得了需要消耗解绑符的数量后 我们将解绑符的图标和数量设置到UI上面去
	//1.获取背包解绑符数量
	//装备解绑符在材料背包
	int sum =thePlayerRole.m_bagMaterial.GetItemCount(SID_UnBindItem);
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(SID_UnBindItem,sum);
	if(sum == 0)
		pItems.SetEnable(eIcon_Disable);
	else
		pItems.SetEnable(eIcon_Enable);
	m_pID_LISTIMG_Material->SetItem(&pItems,0);
	m_pID_BUTTON_Ok->SetEnable((sum >= num));
	//2.设置提示信息 X NUM
	
	if(sum < num)
	{
		char szText[24] = {0};
		sprintf_s(szText, sizeof(szText)-1,"(%s)X %d",theXmlString.GetString(eText_UnBind_Info),num);
		m_pID_TEXT_Money->SetText(szText,Color_Config.getColor( CC_PetColor_Red ));
	}
	else
	{
		char szText[12] = {0};
		sprintf_s(szText, sizeof(szText)-1,"X %d",num);
		m_pID_TEXT_Money->SetText(szText);
	}
	m_pID_TEXT_EquipName->SetText(pEquipCommon->GetItemName());//放上去的装备的名称 
	
	ItemDefine::SItemCommon* pItemCommon_s = GettheItemDetail().GetItemByID( SID_UnBindItem);
	if(pItemCommon_s)
		m_pID_TEXT_ItemName->SetText(pItemCommon_s->GetItemName());//物品的名称

	m_unBindBagSum = sum;
	m_unBindNeedSum = num;
	m_unBindEquip = pItem;
	//到目前 已经确认装备可以解绑料 我们要设置 让UI上显示物品的图标 并且背包设置为灰色
	int index = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
	if (index != -1)
	{
		ControlIconDrag::S_ListImg item = *pItemDrag;
		item.m_eEnable = eIcon_Enable;
		m_pID_LISTIMG_ZJ1->SetItem(&item, 0);
		//让背包指定位置变灰
		SetBagItemIsUnUse(true,index);
		m_unBindIndex = index;
	}
	return true;
}
void CUI_ID_FRAME_JieBang::UpdateUIButtonByBagItem()//Ui的Update事件 用于循环更新 保证UI上数据的正确性
{
	//根据背包物品数量判断指定UI按钮是否需要重新设置
	if(!IsVisable() || !m_unBindEquip) return;
    if(HQ_TimeGetTime() - m_StepLogTime < 1000) return;//1秒更新一次
	//1.获取物品在背包中的数量
	//1秒更新一次
	int sum =thePlayerRole.m_bagMaterial.GetItemCount(SID_UnBindItem);
	if(sum != m_unBindBagSum)
	{
		//当背包的解绑符发生变化的时候
		m_unBindBagSum = sum;
		bool states = m_unBindNeedSum <= m_unBindBagSum;
		if(m_pID_BUTTON_Ok->IsEnable() != states)
			m_pID_BUTTON_Ok->SetEnable(states);
		ControlIconDrag::S_ListImg pItem;
		pItem.SetData(SID_UnBindItem,m_unBindBagSum);
		if(sum == 0)
			pItem.SetEnable(eIcon_Disable);
		else
			pItem.SetEnable(eIcon_Enable);
		m_pID_LISTIMG_Material->SetItem(&pItem,0);//更新UI上物品的数量

		if(sum < m_unBindNeedSum)
		{
			char szText[24] = {0};
			sprintf_s(szText, sizeof(szText)-1,"(%s)X %d",theXmlString.GetString(eText_UnBind_Info),m_unBindNeedSum);
			m_pID_TEXT_Money->SetText(szText,Color_Config.getColor( CC_PetColor_Red ));
		}
		else
		{
			char szText[12] = {0};
			sprintf_s(szText, sizeof(szText)-1,"X %d",m_unBindNeedSum);
			m_pID_TEXT_Money->SetText(szText);
		}

		//让所有解绑符全部变灰
		int BagSize = thePlayerRole.m_bagMaterial.GetNowBagSize();
		for(int i =0;i<BagSize;++i)
		{
			SCharItem * pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(i);
			if(!pItem || pItem->itembaseinfo.ustItemID !=SID_UnBindItem || SID_UnBindItem == 0) continue;
			CPackItemEnableManager::Instance()->RefreshBagItemEnable(&thePlayerRole.m_bagMaterial,i,true);
		}
	}
	m_StepLogTime = HQ_TimeGetTime();
}
void CUI_ID_FRAME_JieBang::HandleUnBindEquip(__int64 EquipOnceID)//向服务器端发送装备解绑的命令
{
	//开始处理装备解绑处理
	//1.判断背包的解绑符的数量是否大于要求的
	int sum =thePlayerRole.m_bagMaterial.GetItemCount(SID_UnBindItem);
	if(m_unBindNeedSum > sum)
	{
		m_pID_BUTTON_Ok->SetEnable(false);
		return;
	}
	//发送命令到服务器端
	MsgUnBindEquipReq req;
	req.nEquipGuid = EquipOnceID;
	GettheNetworkInput().SendMsg(&req);
}
void CUI_ID_FRAME_JieBang::UnBindEquipSuc(__int64 equipGuiID)//接收到服务器端的返回命令 设置装备的属性
{
	if(equipGuiID !=-1 && m_unBindEquip && equipGuiID ==  m_unBindEquip->itembaseinfo.nOnlyInt)
	{
		SCharItem* pItem=thePlayerRole.m_bag.GetCharItemFromIdx(thePlayerRole.m_bag.GetItemIndexByGUID(equipGuiID));
		m_unBindEquip->SetBounded(false);
		if(pItem)
			pItem->SetBounded(false);
		if(m_unBindEquip->equipdata.unBindCount != pItem->equipdata.unBindCount)
			pItem->equipdata.unBindCount = m_unBindEquip->equipdata.unBindCount;//装备第一次解绑的时候背包物品值没传来
		if(m_unBindEquip->equipdata.unBindCount >0 && m_unBindEquip->equipdata.unBindCount !=0xFFFF)
			--m_unBindEquip->equipdata.unBindCount;
		if(pItem->equipdata.unBindCount >0 && pItem->equipdata.unBindCount !=0xFFFF)
			--pItem->equipdata.unBindCount;
		//在右下角提示 装备已经解绑
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_UnBind_Sec ) );
	}
	SetEmpty();
}
void CUI_ID_FRAME_JieBang::SetBagItemIsUnUse(bool isUnUse,int16 indexPos)//设置指定背包的物品被使用 为灰色 或者亮起
{
	//设置指定背包的指定材料和指定装备为灰色 不可以使用
	//指定物品变灰
	if(!isUnUse)
		m_unBindEquip =NULL;
	CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag,indexPos,true);
	//获取普通背包是有物品类型为解绑符的物品的位置 并且设置为不可以使用
	//遍历背包如果有相同的
	int BagSize = thePlayerRole.m_bagMaterial.GetNowBagSize();
	for(int i =0;i<BagSize;++i)
	{
		SCharItem * pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx(i);
		if(!pItem || pItem->itembaseinfo.ustItemID !=SID_UnBindItem || SID_UnBindItem == 0) continue;
		CPackItemEnableManager::Instance()->RefreshBagItemEnable(&thePlayerRole.m_bagMaterial,i,true);
	}
}
void CUI_ID_FRAME_JieBang::ShowErrorMsgInScreen(eName eErrorID) //屏幕中央的提示信息
{
	//根据错误ID 在屏幕中间提示玩家错误信息
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eErrorID));
}