/********************************************************************
Created by UIEditor.exe
FileName: E:\Work\HeroRuntime\Client\UI\escdlg.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameMain.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "UIStorage.h"
#include "Pack.h"
#include "escdlg.h"
#include "MeUi/MouseManager.h"

#include "XmlStringLanguage.h"
#include "MessageBox.h"
#include "shop.h"
#include "core/Name.h"
#include "ScreenInfoManager.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeCommon/MapConfig.h"
#include "CountryConfig.h"
#include "IntroductionManager.h"
#include <time.h>
#include "XmlStringLanguage.h"

CUI_ID_FRAME_ESCDLG s_CUI_ID_FRAME_ESCDLG;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ESCDLG, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ESCDLG, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_ReliveOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_MoneyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_EntranceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_BattleOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_CurrPlaceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_PerfectOnButtonClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_BaoZouOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_TrueBZOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_BUTTON_NPReliveOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_LISTIMG_ItemOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ESCDLG, ID_LISTIMG_ItemOnIconButtonClick )

CUI_ID_FRAME_ESCDLG::CUI_ID_FRAME_ESCDLG()
// :CUIBase( eUI_OBJECT_EscDlg )
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_ESCDLG = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	//m_pID_PICTURE_Title = NULL;
	m_pID_TEXT_TimeText = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_TEXT_WaitTime = NULL;
	m_pID_BUTTON_Relive = NULL;
	m_pID_BUTTON_Money = NULL;
	m_pID_BUTTON_Entrance = NULL;
	m_pID_BUTTON_Battle = NULL;

	m_pID_BUTTON_CurrPlace = NULL;
	m_pID_BUTTON_Perfect = NULL;

	m_pID_BUTTON_BaoZou = NULL;
	m_pID_BUTTON_TrueBZ = NULL;

	m_pID_TEXT_CurrMoney = NULL;
	m_pID_TEXT_PerMoney = NULL;
	m_pID_BUTTON_NPRelive = NULL;
	m_pID_TEXT_ReLiveCntConfig = NULL;
	m_pID_TEXT_ReLiveCnt = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_TEXT_ItemCount = NULL;

	_tmWaitStart = 0;
	_tmBeginWait = 0;

	_bPassWaitFor = false;

	m_stReliveOriginNonRmb = 0;
	m_stReliveOriginAllHpMpRmb = 0;
	
	mNoteTime = 0;
	mConfigTime = 300000; // 策划要求五分钟的时间玩家不点击复活，就自动传送复活

	m_HeroReliveCnt = 0;

	//byGetBuff = MsgReqRelive::ENoAddtion;
	unguard;

}// Button
BYTE CUI_ID_FRAME_ESCDLG::byGetBuff = MsgReqRelive::ENoAddtion;
bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_ESCDLG )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_ESCDLG )
		return false;
	return true;
}
// Frame
bool CUI_ID_FRAME_ESCDLG::OnFrameRun()
{
	guardfunc;
	if( !m_pID_FRAME_ESCDLG || !m_pID_TEXT_WaitTime)
		return false;

	if( !IsVisable() )
		return false;

	DWORD time = timeGetTime();
	DWORD lostTime = time - mNoteTime;

	int showTime = mConfigTime - lostTime;

	if ( showTime > 0 )
	{
		int m = 0;
		int s = 0;
		//char str[256] = {0};
		//ToMinuteAndSecond( showTime, m, s );
		//sprintf_s( str, theXmlString.GetString(eUI_DeadReliveInfo), m, s );
		*m_pID_TEXT_WaitTime = showTime/1000;
		if( thePlayerRole.IsFinishedIntroduce(INTRO_RELIVE) == false )
		{
			CIntroductionManager::Instance()->ShowTip( INTRO_RELIVE );
			thePlayerRole.SetFinishedIntroduce(INTRO_RELIVE);
		}
	}
	else
	{
		// 如果时间到了模拟下点击传送的键
		ID_BUTTON_ReliveOnButtonClick( NULL );
		/*if (m_pID_BUTTON_Perfect->IsVisable())
		{
			ID_BUTTON_PerfectOnButtonClick(NULL);
		}
		else if (m_pID_BUTTON_CurrPlace->IsVisable())
		{
			ID_BUTTON_CurrPlaceOnButtonClick(NULL);
		}
		else
		{
			ID_BUTTON_ReliveOnButtonClick( NULL );
		}*/
	}

	return true;
	unguard;
}
bool CUI_ID_FRAME_ESCDLG::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}// Button
bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_BattleOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ESCDLG )
		return false;
	theHeroGame.GetPlayerMgr()->ReqRelive( false );
	*m_pID_TEXT_WaitTime = "";
	//关掉界面
	//SetVisable( false );
	return true;
}
bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_EntranceOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_ESCDLG )
		return false;
	theHeroGame.GetPlayerMgr()->ReqRelive( false );
	*m_pID_TEXT_WaitTime = "";
	//关掉界面
	//SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_ReliveOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	//客户端，发送给，服务器段，说明需要复活
    if(!m_pID_FRAME_ESCDLG)    
        return false;    

	theHeroGame.GetPlayerMgr()->ReqRelive( false );
	*m_pID_TEXT_WaitTime = "";
	//关掉界面
	//SetVisable( false );
	return true;
	unguard;
}

// Button
bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_CurrPlaceOnButtonClick( ControlObject* pSender )
{
	//原地复活
	guardfunc;
	//客户端，发送给，服务器段，说明需要复活
	if(!m_pID_FRAME_ESCDLG)    
		return false;    

	theHeroGame.GetPlayerMgr()->ReqRelive( false, false, eReliveOriginNon );
	//*m_pID_TEXT_WaitTime = "";
	//关掉界面
	//SetVisable( false );
	return true;
	unguard;
}

void CUI_ID_FRAME_ESCDLG::ReliveNeedMoney(DWORD &NeedMoney)
{

	NeedMoney = 0;
	int  ReliveOffset = m_HeroReliveCnt - theCountryConfig.GetReliveSetting().GetFreeReliveLimitByLevel(thePlayerRole.GetLevel());

	if (ReliveOffset >= 0)
	{
	
	if(  ReliveOffset <= 10 )//送的完美复活的次数用完 之后多出来的
	{
		NeedMoney = ReliveOffset*0.1*theCountryConfig.GetReliveSetting().GetPerReliveMoney() + theCountryConfig.GetReliveSetting().GetPerReliveMoney();

	}else
	{

		NeedMoney = theCountryConfig.GetReliveSetting().GetPerReliveMoney()*10; //第10次的5倍
	}
	}
  
}

// Button
bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_PerfectOnButtonClick( ControlObject* pSender )
{
	//完美复活
	guardfunc;
	//客户端，发送给，服务器段，说明需要复活
	if(!m_pID_FRAME_ESCDLG)    
		return false;    

	//lyh++ 完美复活 金币检查。



	   DWORD HeroHaveMoney = thePlayerRole.m_charinfo.baseinfo.liveinfo.jiaoZi + thePlayerRole.m_charinfo.baseinfo.liveinfo.dwMoney;

 
  
    
	DWORD _ReliveNeedMoney = 0;

	int itemCount = thePlayerRole.m_bag.GetItemCount( theCountryConfig.GetReliveSetting().GetReliveItemId());
	int nFreeReliveCount = theCountryConfig.GetReliveSetting().GetReilvelSum(thePlayerRole.GetLevel()) - thePlayerRole.GetCharInfo2().baseinfo.liveinfo.nFreeReliveCount;

	int Revile = thePlayerRole.GetCharInfo2().baseinfo.liveinfo.nFreeReliveCount - theCountryConfig.GetReliveSetting().GetReilvelSum(thePlayerRole.GetLevel());
	int Num = ceil(max(0,Revile-5)*0.6 + 1.0) * theCountryConfig.GetReliveSetting().GetReliveItemCount();//需要复活丹的个数

	//完美复活现在改成只要复活丹，不能用金钱 lrt
	 // ReliveNeedMoney(_ReliveNeedMoney);

   if(/*HeroHaveMoney < _ReliveNeedMoney &&*/ itemCount < Num && nFreeReliveCount <= 0 )
   {
	   CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Relive_Belongs, theXmlString.GetString( eText_ReliveOrigin_NoItem ) );
	   return false;
   }

	theHeroGame.GetPlayerMgr()->ReqRelive( false, false, eReliveOriginAllHpMp,byGetBuff );
	//*m_pID_TEXT_WaitTime = "";
	//关掉界面
	//SetVisable( false );
	return true;
	unguard;
}

bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_BaoZouOnButtonClick( ControlObject* pSender )
{
	//完美复活
	guardfunc;
	//客户端，发送给，服务器段，说明需要复活
	if(!m_pID_FRAME_ESCDLG)    
		return false;    

	theHeroGame.GetPlayerMgr()->ReqRelive( false, false, eReliveOriginAllHpMp,byGetBuff );
	//*m_pID_TEXT_WaitTime = "";
	//关掉界面
	//SetVisable( false );
	return true;
	unguard;
}
bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_NPReliveOnButtonClick( ControlObject* pSender )
{
	//完美复活
	guardfunc;
	//客户端，发送给，服务器段，说明需要复活
	if(!m_pID_FRAME_ESCDLG)    
		return false;    

	theHeroGame.GetPlayerMgr()->ReqRelive( false, false, eReliveOriginAllHpMp,byGetBuff );
	//*m_pID_TEXT_WaitTime = "";
	//关掉界面
	//SetVisable( false );
	return true;
	unguard;
}
bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_TrueBZOnButtonClick( ControlObject* pSender )
{
	//完美复活
	guardfunc;
	//客户端，发送给，服务器段，说明需要复活
	if(!m_pID_FRAME_ESCDLG)    
		return false;    

	theHeroGame.GetPlayerMgr()->ReqRelive( false, false, eReliveOriginAllHpMp,byGetBuff );
	//*m_pID_TEXT_WaitTime = "";
	//关掉界面
	//SetVisable( false );
	return true;
	unguard;
}

bool CUI_ID_FRAME_ESCDLG::ID_BUTTON_MoneyOnButtonClick(ControlObject* pSender )
{
	// 是否可原地复活服务器判断 [1/13/2011 zhangjiayi]
	//if ( thePlayerRole.m_bag.GetItemCount( CItemDetail::ESRI_ReliveItem ) > 0 )
	{
		// 信春哥了,满血满状态复活了
		MsgReqRelive msg;

		msg.byBornPos = eReliveTypeOriginFullHpMP;

		GettheNetworkInput().SendMsg( &msg,msg.GetLength() );
	}
// 	else
// 	{
// 		// 错误提示
// 		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FullBufRelive_Failed, theXmlString.GetString( eClient_Err_Relive ) );
// 	}

	return true;
}
bool TellWanmeiRelive(char bIsTell,void *pData )
{
	//theHeroGame.GetPlayerMgr()->SetReLived(FALSE);
	if (bIsTell)
	{
		theHeroGame.GetPlayerMgr()->ReqRelive( false,false,CUI_ID_FRAME_ESCDLG::eReliveOriginAllHpMp);
		s_CUI_ID_FRAME_ESCDLG.ClearWaitTime();	
		//关掉界面
		//s_CUI_ID_FRAME_ESCDLG.SetVisable( false );
	}
	else
	{
		return false;
	}
	return true;
}

bool TellYuandiRelive(char bIsTell,void *pData )
{
	//theHeroGame.GetPlayerMgr()->SetReLived(FALSE);
	if (bIsTell)
	{
		theHeroGame.GetPlayerMgr()->ReqRelive( false,false,CUI_ID_FRAME_ESCDLG::eReliveOriginNon);
		s_CUI_ID_FRAME_ESCDLG.ClearWaitTime();
		//关掉界面
		s_CUI_ID_FRAME_ESCDLG.SetVisable( false );
	}
	else
	{
		return false;
	}
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ESCDLG::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_ESCDLG::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ESCDLG::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ESCDLG::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}


// 装载UI
bool CUI_ID_FRAME_ESCDLG::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\escdlg.meui"/*, true, UI_Render_LayerThree*/ );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\escdlg.UI]失败")
			return false;
	}
// 	else if ( dwResult != 5859/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[UI\\escdlg.UI]与源代码版本不一样")
// 	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_ESCDLG::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_ESCDLG, s_CUI_ID_FRAME_ESCDLGOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ESCDLG, s_CUI_ID_FRAME_ESCDLGOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_HELP, s_CUI_ID_FRAME_ESCDLGID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ESCDLGID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_Relive, s_CUI_ID_FRAME_ESCDLGID_BUTTON_ReliveOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_Money, s_CUI_ID_FRAME_ESCDLGID_BUTTON_MoneyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_Entrance, s_CUI_ID_FRAME_ESCDLGID_BUTTON_EntranceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_Battle, s_CUI_ID_FRAME_ESCDLGID_BUTTON_BattleOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_CurrPlace, s_CUI_ID_FRAME_ESCDLGID_BUTTON_CurrPlaceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_Perfect, s_CUI_ID_FRAME_ESCDLGID_BUTTON_PerfectOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_TrueBZ, s_CUI_ID_FRAME_ESCDLGID_BUTTON_TrueBZOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_BaoZou, s_CUI_ID_FRAME_ESCDLGID_BUTTON_BaoZouOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_ESCDLG, ID_BUTTON_NPRelive, s_CUI_ID_FRAME_ESCDLGID_BUTTON_NPReliveOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_ESCDLG, ID_LISTIMG_Item, s_CUI_ID_FRAME_ESCDLGID_LISTIMG_ItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_ESCDLG, ID_LISTIMG_Item, s_CUI_ID_FRAME_ESCDLGID_LISTIMG_ItemOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_ESCDLG, ID_LISTIMG_Item, s_CUI_ID_FRAME_ESCDLGID_LISTIMG_ItemOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_ESCDLG, ID_LISTIMG_Item, s_CUI_ID_FRAME_ESCDLGID_LISTIMG_ItemOnIconButtonClick );

	m_pID_FRAME_ESCDLG = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ESCDLG );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_CLOSE );
	//m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_PICTURE_Title );
	m_pID_TEXT_TimeText = (ControlText*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_TEXT_TimeText );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_TEXT_Explain );
	m_pID_TEXT_WaitTime = (ControlText*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_TEXT_WaitTime );
	m_pID_BUTTON_Relive = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_Relive );
	m_pID_BUTTON_Money = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_Money );
	m_pID_BUTTON_Entrance = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_Entrance );
	m_pID_BUTTON_Battle = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_Battle );
	m_pID_BUTTON_CurrPlace = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_CurrPlace );
	m_pID_BUTTON_Perfect = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_Perfect );
	m_pID_BUTTON_NPRelive = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_NPRelive );

	m_pID_BUTTON_BaoZou = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_BaoZou );
	m_pID_BUTTON_TrueBZ = (ControlButton*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_BUTTON_TrueBZ );
	m_pID_TEXT_CurrMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_TEXT_CurrMoney );
	m_pID_TEXT_PerMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_TEXT_PerMoney );
	m_pID_TEXT_ReLiveCnt = (ControlText*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_TEXT_ReLiveCnt );
	m_pID_TEXT_ReLiveCntConfig = (ControlText*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_TEXT_ReLiveCntConfig );
	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_LISTIMG_Item );
	m_pID_TEXT_ItemCount = (ControlText*)theUiManager.FindControl( ID_FRAME_ESCDLG, ID_TEXT_ItemCount );

	assert( m_pID_TEXT_ReLiveCnt );
	assert(m_pID_TEXT_ReLiveCntConfig);
	assert( m_pID_BUTTON_NPRelive );
	assert( m_pID_TEXT_CurrMoney );
	assert( m_pID_TEXT_PerMoney );
	assert( m_pID_BUTTON_BaoZou );
	assert( m_pID_BUTTON_TrueBZ );
	assert( m_pID_BUTTON_CurrPlace );
	assert( m_pID_BUTTON_Perfect );
	assert( m_pID_FRAME_ESCDLG );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	//assert( m_pID_PICTURE_Title );
	assert( m_pID_TEXT_TimeText );
	assert( m_pID_TEXT_Explain );
	assert( m_pID_TEXT_WaitTime );
	assert( m_pID_BUTTON_Relive );
	assert( m_pID_BUTTON_Money );
	assert( m_pID_BUTTON_Entrance );
	assert( m_pID_BUTTON_Battle );
	assert( m_pID_LISTIMG_Item );
	assert( m_pID_TEXT_ItemCount );

	USE_SCRIPT( eUI_OBJECT_EscDlg, this );
	m_pID_FRAME_ESCDLG->SetVisable( false );
	m_pID_FRAME_ESCDLG->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);//

	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_ESCDLG::_UnLoadUI()
{
	guardfunc;
	//CUIBase::UnLoadUI();
	m_pID_FRAME_ESCDLG = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	//m_pID_PICTURE_Title = NULL;
	m_pID_TEXT_TimeText = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_TEXT_WaitTime = NULL;
	m_pID_BUTTON_Relive = NULL;
	m_pID_BUTTON_Money = NULL;
	m_pID_BUTTON_Entrance = NULL;
	m_pID_BUTTON_Battle = NULL;
	m_pID_BUTTON_Perfect = NULL;
	m_pID_BUTTON_CurrPlace = NULL;
	CLOSE_SCRIPT( eUI_OBJECT_EscDlg );
	return theUiManager.RemoveFrame( "data\\ui\\escdlg.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_ESCDLG::_IsVisable()
{
	guardfunc;
	if( m_pID_FRAME_ESCDLG )
		return m_pID_FRAME_ESCDLG->IsVisable();

	return false;
	unguard;
}

bool CUI_ID_FRAME_ESCDLG::CheckIsKingCampMap()
{
	if (thePlayerRole.GetCampType() == CampDefine::BattleTypeKing)
	{
		return true;
	}

	return false;
}

void CUI_ID_FRAME_ESCDLG::SetButtonVisableInKingCamp()
{
	if (m_pID_BUTTON_Money)
	{
		m_pID_BUTTON_Money->SetEnable(false);
	}
}

// 设置是否可视
void CUI_ID_FRAME_ESCDLG::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_ESCDLG )
		return ;
	//byGetBuff = MsgReqRelive::ENoAddtion;
	//CUIBase::SetVisable( bVisable );
	m_pID_FRAME_ESCDLG->SetVisable( bVisable );
	if(bVisable)
	{
		//关闭仓库和背包等一些UI界面
		if(s_CUI_ID_FRAME_PACK.IsVisable())
		{
			s_CUI_ID_FRAME_PACK.SetVisable(false);
			theMouseManager.SetUICursor(MouseManager::Type_Arrow);
		}
		if(s_CUI_ID_FRAME_Storage.IsVisable())
		{
			s_CUI_ID_FRAME_Storage.SetVisable(false);
			theMouseManager.SetUICursor(MouseManager::Type_Arrow);
		}
		//设置说明
		char acInfo[2048] = {0};
		CWorldTile* pTile = CURRENTTILE;
		if( pTile )
		{
			m_pID_BUTTON_Battle->SetVisable( false );
			m_pID_BUTTON_Entrance->SetVisable( false );
			m_pID_BUTTON_Relive->SetVisable( false );
			m_pID_BUTTON_CurrPlace->SetVisable(false);
			m_pID_BUTTON_Perfect->SetVisable(false);
			int nStringID = eReliveUI_Relive;
			switch( pTile->GetMapType() )
			{
			case MapConfig::MT_NormalMap://普通地图
				{//普通地图
					nStringID = eReliveUI_Relive;
					m_pID_BUTTON_Relive->SetVisable( true );
					m_pID_BUTTON_CurrPlace->SetVisable(true);
					m_pID_BUTTON_Perfect->SetVisable(true);
				}
				break;
			case MapConfig::MT_SingleGuild:
			case MapConfig::MT_SingleTeam:
				{//副本
					nStringID = eReliveUI_Entrance;
					m_pID_BUTTON_Entrance->SetVisable( true );
					m_pID_BUTTON_Perfect->SetVisable( true );
				}
				break;
			case MapConfig::MT_MultiPlayer:
				{//帮战
					nStringID = eReliveUI_Battle;
					m_pID_BUTTON_Battle->SetVisable( true );
					if (CheckIsKingCampMap())
					{
						SetButtonVisableInKingCamp();
					}
				}				
				break;
			default:
				{
					nStringID = eReliveUI_Relive;
					m_pID_BUTTON_Relive->SetVisable( true );
					m_pID_BUTTON_CurrPlace->SetVisable(true);
					m_pID_BUTTON_Perfect->SetVisable(true);
				}
				break;
			}
			MeSprintf_s( acInfo, 2048 - 1, theXmlString.GetString( nStringID ), 
				GetAttackerName().c_str(), 
				(int)theCountryConfig.GetReliveSetting().GetLevelLimit(),
				(int)theCountryConfig.GetReliveSetting().GetBeforeLevelLimit(),
				(int)theCountryConfig.GetReliveSetting().GetLevelLimit(),
				(int)theCountryConfig.GetReliveSetting().GetAfterLevelLimit(),
				(int)thePlayerRole.GetValidFreeReliveCount() );
			m_pID_TEXT_Explain->SetText( acInfo );

		}

		mNoteTime = timeGetTime();

		//char str[256] = {0};
		int m = 0;
		int s = 0;
		// 如果打开就格式化时间并且显示
		mConfigTime = theCountryConfig.GetReliveSetting().GetReliveTime();
		//sprintf_s( str, theXmlString.GetString(eUI_DeadReliveInfo), m, s );
		*m_pID_TEXT_WaitTime = mConfigTime/1000;

		//随即获得免费完美复活的机会
		//byGetBuff = s_CUI_ID_FRAME_ESCDLG.GetBuff();
		if (byGetBuff & MsgReqRelive::EAddBuff2)		//真暴走
		{
			m_pID_BUTTON_CurrPlace->SetEnable(false);
			m_pID_BUTTON_Perfect->SetEnable(false);
			m_pID_BUTTON_TrueBZ->SetVisable(true);
			m_pID_BUTTON_BaoZou->SetVisable(false);
			m_pID_BUTTON_NPRelive->SetVisable(false);
		}
		else if (byGetBuff & MsgReqRelive::EAddBuff1)		//暴走
		{
			m_pID_BUTTON_CurrPlace->SetEnable(false);
			m_pID_BUTTON_BaoZou->SetVisable(true);
			m_pID_BUTTON_TrueBZ->SetVisable(false);
			m_pID_BUTTON_Perfect->SetEnable(false);
			m_pID_BUTTON_NPRelive->SetVisable(false);
		}
		else if (byGetBuff & MsgReqRelive::EFullHPMP)			//涅槃
		{
			m_pID_BUTTON_CurrPlace->SetEnable(false);
			m_pID_BUTTON_Perfect->SetEnable(false);
			m_pID_BUTTON_BaoZou->SetVisable(false);
			m_pID_BUTTON_TrueBZ->SetVisable(false);
			m_pID_BUTTON_NPRelive->SetVisable(true);
		}
		else
		{
			m_pID_BUTTON_CurrPlace->SetVisable(true);
			m_pID_BUTTON_CurrPlace->SetEnable(true);
			m_pID_BUTTON_Perfect->SetVisable(true);
			m_pID_BUTTON_Perfect->SetEnable(true);
			m_pID_BUTTON_BaoZou->SetVisable(false);
			m_pID_BUTTON_TrueBZ->SetVisable(false);
			m_pID_BUTTON_NPRelive->SetVisable(false);
		}

		DWORD NeedMoney = 0 ;
 		ReliveNeedMoney(NeedMoney);
		//m_pID_TEXT_ReLiveCntConfig->SetText(theCountryConfig.GetReliveSetting().GetFreeReliveLimitByLevel(thePlayerRole.GetLevel()));

		
		m_pID_TEXT_ReLiveCntConfig->SetText(theCountryConfig.GetReliveSetting().GetReilvelSum(thePlayerRole.GetLevel()));

		int Sum = theCountryConfig.GetReliveSetting().GetReilvelSum(thePlayerRole.GetLevel()) - thePlayerRole.GetCharInfo2().baseinfo.liveinfo.nFreeReliveCount;
		if(Sum <0)
			Sum = 0;
		m_pID_TEXT_ReLiveCnt->SetText(Sum);
		
		m_pID_TEXT_PerMoney->SetText(/*theCountryConfig.GetReliveSetting().GetPerReliveMoney()*//*NeedMoney*/theCountryConfig.GetReliveSetting().GetReviceMoney(thePlayerRole.GetLevel(),thePlayerRole.GetCharInfo2().baseinfo.liveinfo.nFreeReliveCount));
		m_pID_TEXT_CurrMoney->SetText(theCountryConfig.GetReliveSetting().GetReliveMoney());
		

		m_pID_LISTIMG_Item->Clear();
		int itemCount = thePlayerRole.m_bag.GetItemCount( theCountryConfig.GetReliveSetting().GetReliveItemId());
		ControlIconDrag::S_ListImg itemListImg;

		//判断当初复活需要多少个复活丹
		int Revile = thePlayerRole.GetCharInfo2().baseinfo.liveinfo.nFreeReliveCount - theCountryConfig.GetReliveSetting().GetReilvelSum(thePlayerRole.GetLevel());
		int Num = ceil(max(0,Revile-5)*0.6 + 1.0) * theCountryConfig.GetReliveSetting().GetReliveItemCount();//需要复活丹的个数

		m_pID_TEXT_ItemCount->SetText(Num);
		if(itemCount < Num)
			itemListImg.SetData(theCountryConfig.GetReliveSetting().GetReliveItemId(), Num, eIcon_Disable);
		else
			itemListImg.SetData(theCountryConfig.GetReliveSetting().GetReliveItemId(), Num, eIcon_Enable);

		/*if ( itemCount == 0 )
			itemListImg.SetData(theCountryConfig.GetReliveSetting().GetReliveItemId(), 1, eIcon_Disable);
		else
			itemListImg.SetData(theCountryConfig.GetReliveSetting().GetReliveItemId(), itemCount, eIcon_Enable);*/

		m_pID_LISTIMG_Item->SetItem( &itemListImg );
		//if (m_pID_PICTURE_TrueBZ->IsVisable() || m_pID_PICTURE_BaoZou->IsVisable())
		//{
		//	m_pID_BUTTON_CurrPlace->SetVisable(false);
		//	//m_pID_BUTTON_Relive->SetVisable(false);
		//	m_pID_TEXT_Explain->SetText(theXmlString.GetString(eText_Relive_FullHPMP));
		//	m_pID_TEXT_Explain->SetVisable(true);
		//}
		//UI_ID_FRAME_SHOP::cancelMendByDeath();
	}
	unguard;
}
void CUI_ID_FRAME_ESCDLG::UpdateReviceSum()
{
	if(IsVisable())
	{
		DWORD NeedMoney = 0 ;
 		ReliveNeedMoney(NeedMoney);
		//m_pID_TEXT_ReLiveCntConfig->SetText(theCountryConfig.GetReliveSetting().GetFreeReliveLimitByLevel(thePlayerRole.GetLevel()));

		
		m_pID_TEXT_ReLiveCntConfig->SetText(theCountryConfig.GetReliveSetting().GetReilvelSum(thePlayerRole.GetLevel()));

		int Sum = theCountryConfig.GetReliveSetting().GetReilvelSum(thePlayerRole.GetLevel()) - thePlayerRole.GetCharInfo2().baseinfo.liveinfo.nFreeReliveCount;
		if(Sum <0)
			Sum = 0;
		m_pID_TEXT_ReLiveCnt->SetText(Sum);
		
		m_pID_TEXT_PerMoney->SetText(/*theCountryConfig.GetReliveSetting().GetPerReliveMoney()*//*NeedMoney*/theCountryConfig.GetReliveSetting().GetReviceMoney(thePlayerRole.GetLevel(),thePlayerRole.GetCharInfo2().baseinfo.liveinfo.nFreeReliveCount));
		m_pID_TEXT_CurrMoney->SetText(theCountryConfig.GetReliveSetting().GetReliveMoney());
		
		m_pID_LISTIMG_Item->Clear();
		int itemCount = thePlayerRole.m_bag.GetItemCount( theCountryConfig.GetReliveSetting().GetReliveItemId());
		ControlIconDrag::S_ListImg itemListImg;


		int Revile = thePlayerRole.GetCharInfo2().baseinfo.liveinfo.nFreeReliveCount - theCountryConfig.GetReliveSetting().GetReilvelSum(thePlayerRole.GetLevel());
		int Num = ceil(max(0,Revile-5)*0.6 + 1.0) * theCountryConfig.GetReliveSetting().GetReliveItemCount();//需要复活丹的个数
		
		m_pID_TEXT_ItemCount->SetText(Num);
		if(itemCount < Num)
			itemListImg.SetData(theCountryConfig.GetReliveSetting().GetReliveItemId(), Num, eIcon_Disable);
		else
			itemListImg.SetData(theCountryConfig.GetReliveSetting().GetReliveItemId(), Num, eIcon_Enable);

		/*if ( itemCount == 0 )
			itemListImg.SetData(theCountryConfig.GetReliveSetting().GetReliveItemId(), 1, eIcon_Disable);
		else
			itemListImg.SetData(theCountryConfig.GetReliveSetting().GetReliveItemId(), itemCount, eIcon_Enable);*/

		m_pID_LISTIMG_Item->SetItem( &itemListImg );
	}
}
void CUI_ID_FRAME_ESCDLG::Process()
{
	guardfunc;
// 	if( !m_pID_FRAME_ESCDLG )
// 		return;

	if( !IsVisable() )
	{	
		
		SetVisable( true );
		
		return;
	}
	SetVisable( !IsVisable() ); 

	unguard;
}
void CUI_ID_FRAME_ESCDLG::ClearWaitTime()
{
	if( !m_pID_FRAME_ESCDLG )
		return;

	*m_pID_TEXT_WaitTime = "";
}

int CUI_ID_FRAME_ESCDLG::ToSecond( DWORD time)
{
	return time/1000;
}
