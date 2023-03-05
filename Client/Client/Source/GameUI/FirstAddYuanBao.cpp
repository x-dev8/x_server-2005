/********************************************************************
	Created by UIEditor.exe
	FileName: D:\SVNClient\sg_pro\3Guo_Main\FullClient\Data\Ui\FirstAddYuanBao.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FirstAddYuanBao.h"
//#include "YuanBaoTotleConfig.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "Cfg.h"
#include "shellapi.h"
CUI_ID_FRAME_FirstAddYuanBao s_CUI_ID_FRAME_FirstAddYuanBao;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FirstAddYuanBao, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FirstAddYuanBao, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FirstAddYuanBao, ID_LISTIMG_ItemTipsOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FirstAddYuanBao, ID_LISTIMG_ItemTipsOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FirstAddYuanBao, ID_LISTIMG_ItemTipsOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FirstAddYuanBao, ID_LISTIMG_ItemTipsOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FirstAddYuanBao, ID_BUTTON_ActionAddressOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FirstAddYuanBao, ID_BUTTON_GetRewordOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FirstAddYuanBao, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_FirstAddYuanBao::CUI_ID_FRAME_FirstAddYuanBao()
{
	// Member
	m_pID_FRAME_FirstAddYuanBao = NULL;
	m_pID_LISTIMG_ItemTips = NULL;
	m_pID_BUTTON_ActionAddress = NULL;
	m_pID_BUTTON_GetReword = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_StrOne = NULL;
	m_pID_TEXT_StrTwo = NULL;
	m_pID_TEXT_Info = NULL;

}
// Frame
bool CUI_ID_FRAME_FirstAddYuanBao::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_FirstAddYuanBao::OnFrameRender()
{
	Update();
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_FirstAddYuanBao::ID_LISTIMG_ItemTipsOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_FirstAddYuanBao::ID_LISTIMG_ItemTipsOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FirstAddYuanBao::ID_LISTIMG_ItemTipsOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FirstAddYuanBao::ID_LISTIMG_ItemTipsOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_FirstAddYuanBao::ID_BUTTON_ActionAddressOnButtonClick( ControlObject* pSender )
{
	ShellExecute(NULL, "open", gCfg.m_FirstWedAdd.c_str(),NULL,NULL, 0);  
	return true;
}
// Button
bool CUI_ID_FRAME_FirstAddYuanBao::ID_BUTTON_GetRewordOnButtonClick( ControlObject* pSender )
{
	//向服务器端领取奖励
	GetReward();
	return true;
}
// Button
bool CUI_ID_FRAME_FirstAddYuanBao::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_FirstAddYuanBao::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FirstAddYuanBao.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FirstAddYuanBao.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_FirstAddYuanBao::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_FirstAddYuanBao, s_CUI_ID_FRAME_FirstAddYuanBaoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_FirstAddYuanBao, s_CUI_ID_FRAME_FirstAddYuanBaoOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_FirstAddYuanBao, ID_LISTIMG_ItemTips, s_CUI_ID_FRAME_FirstAddYuanBaoID_LISTIMG_ItemTipsOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_FirstAddYuanBao, ID_LISTIMG_ItemTips, s_CUI_ID_FRAME_FirstAddYuanBaoID_LISTIMG_ItemTipsOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_FirstAddYuanBao, ID_LISTIMG_ItemTips, s_CUI_ID_FRAME_FirstAddYuanBaoID_LISTIMG_ItemTipsOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_FirstAddYuanBao, ID_LISTIMG_ItemTips, s_CUI_ID_FRAME_FirstAddYuanBaoID_LISTIMG_ItemTipsOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_FirstAddYuanBao, ID_BUTTON_ActionAddress, s_CUI_ID_FRAME_FirstAddYuanBaoID_BUTTON_ActionAddressOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FirstAddYuanBao, ID_BUTTON_GetReword, s_CUI_ID_FRAME_FirstAddYuanBaoID_BUTTON_GetRewordOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FirstAddYuanBao, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_FirstAddYuanBaoID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_FirstAddYuanBao = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FirstAddYuanBao );
	m_pID_LISTIMG_ItemTips = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FirstAddYuanBao, ID_LISTIMG_ItemTips );
	m_pID_BUTTON_ActionAddress = (ControlButton*)theUiManager.FindControl( ID_FRAME_FirstAddYuanBao, ID_BUTTON_ActionAddress );
	m_pID_BUTTON_GetReword = (ControlButton*)theUiManager.FindControl( ID_FRAME_FirstAddYuanBao, ID_BUTTON_GetReword );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_FirstAddYuanBao, ID_BUTTON_CLOSE );
	m_pID_TEXT_StrOne = (ControlText*)theUiManager.FindControl( ID_FRAME_FirstAddYuanBao, ID_TEXT_StrOne );
	m_pID_TEXT_StrTwo = (ControlText*)theUiManager.FindControl( ID_FRAME_FirstAddYuanBao, ID_TEXT_StrTwo );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_FirstAddYuanBao, ID_TEXT_Info );
	assert( m_pID_FRAME_FirstAddYuanBao );
	assert( m_pID_LISTIMG_ItemTips );
	assert( m_pID_BUTTON_ActionAddress );
	assert( m_pID_BUTTON_GetReword );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_StrOne );
	assert( m_pID_TEXT_StrTwo );
	assert( m_pID_TEXT_Info );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_FirstAddYuanBao::_UnLoadUI()
{
	m_pID_FRAME_FirstAddYuanBao = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\FirstAddYuanBao.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_FirstAddYuanBao::_IsVisable()
{
	return m_pID_FRAME_FirstAddYuanBao->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_FirstAddYuanBao::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_FirstAddYuanBao->SetVisable( bVisable );
}
void CUI_ID_FRAME_FirstAddYuanBao::OnShow(unsigned int Value)
{
	//1.判断指定数据是否可以显示出来
//	if(!YuanBaoTotleConfig::Instance().IsCheckCanShowOnlyValue(thePlayerRole.GetYuanBaoStates(),Value))
//		return;
	//2.我们将数据设置到UI上面去
//	OnceYuanBaoReward* pInfo = YuanBaoTotleConfig::Instance().GetInfoByOnlyValue(Value);
/*	if(!pInfo)
		return;
	SetEmpty();
	SetVisable(true);
	if(!m_pID_FRAME_FirstAddYuanBao)
		return;
	//3.获取到数据后 我们展示出来
	//4.展示字符串
	m_pID_TEXT_StrOne->SetText(theXmlString.GetString(pInfo->StrOneID));
	m_pID_TEXT_StrTwo->SetText(theXmlString.GetString(pInfo->StrTwoID));
	char Info[128];
	sprintf_s(Info,sizeof(Info)-1,"%d/%d",thePlayerRole.GetYuanBaoTotle(),pInfo->MinYuanBaoSum);
	m_pID_TEXT_Info->SetText(Info);
	//5.展示物品
	std::vector<OnceYuanBaoReward::ItemInfo>::iterator Iter= pInfo->ItemVec.begin();
	for(int Index = 0;Iter != pInfo->ItemVec.end();++Iter,++Index)
	{
		unsigned int ItemID = Iter->ItemID;
		unsigned int ItemSum = Iter->ItemSum;
		//进行展示
		ControlIconDrag::S_ListImg pItems;
		pItems.SetData(ItemID,ItemSum);
		m_pID_LISTIMG_ItemTips->SetItem(&pItems,Index);
	}
	//6.设置按钮的状态
	if(thePlayerRole.GetYuanBaoTotle() >= pInfo->MinYuanBaoSum)
		m_pID_BUTTON_GetReword->SetEnable(true);
	else
		m_pID_BUTTON_GetReword->SetEnable(false);
	m_OnlyValue = Value;

	*/
	
}
void CUI_ID_FRAME_FirstAddYuanBao::SetEmpty()
{
	m_OnlyValue = 0;
	if(!m_pID_FRAME_FirstAddYuanBao)
		return;
	m_pID_LISTIMG_ItemTips->Clear();
	m_pID_TEXT_StrOne->SetText("");
	m_pID_TEXT_StrTwo->SetText("");
	m_pID_TEXT_Info->SetText("");
}
void CUI_ID_FRAME_FirstAddYuanBao::Update()
{
	//更新按钮的状态
/*	if(!YuanBaoTotleConfig::Instance().IsCheckCanShowOnlyValue(thePlayerRole.GetYuanBaoStates(),m_OnlyValue))
	{
		if(IsVisable())
			SetVisable(false);
		return;
	}
	if(!YuanBaoTotleConfig::Instance().IsCanGetReward(thePlayerRole.GetYuanBaoTotle(),thePlayerRole.GetYuanBaoStates(),m_OnlyValue))
	{
		if(m_pID_BUTTON_GetReword->IsEnable())
			m_pID_BUTTON_GetReword->SetEnable(false);
	}
	else
	{
		if(!m_pID_BUTTON_GetReword->IsEnable())
			m_pID_BUTTON_GetReword->SetEnable(true);
	}
	//更新状态
	OnceYuanBaoReward* pInfo = YuanBaoTotleConfig::Instance().GetInfoByOnlyValue(m_OnlyValue);
	if(!pInfo)
		return;
	char Info[128];
	sprintf_s(Info,sizeof(Info)-1,"%d/%d",thePlayerRole.GetYuanBaoTotle(),pInfo->MinYuanBaoSum);
	m_pID_TEXT_Info->SetText(Info);

	*/
}
void CUI_ID_FRAME_FirstAddYuanBao::GetReward()
{
	//向服务器端发送获取奖励的函数
/*	if(!YuanBaoTotleConfig::Instance().IsCanGetReward(thePlayerRole.GetYuanBaoTotle(),thePlayerRole.GetYuanBaoStates(),m_OnlyValue))
		return;
	MsgUpdateYuanBaoDataReq msg;
	msg.ChangeYuanBaoStatesValue = m_OnlyValue;
	GettheNetworkInput().SendMsg(&msg);
	*/
}