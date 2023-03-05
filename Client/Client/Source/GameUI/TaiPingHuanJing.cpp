/********************************************************************
Created by UIEditor.exe
FileName: E:\武将三国\Data\Ui\TaiPingHuanJing.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TaiPingHuanJing.h"
#include "ItemDetail.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "PlayerInfoMgr.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "TPHJManger.h"
#include "ScreenInfoManager.h"
#include "OnBiaoChe.h"


#include "MeTerrain/stdafx.h"
#include "MeTerrain/MapDef.h"

CUI_ID_FRAME_TaiPingHuanJing s_CUI_ID_FRAME_TaiPingHuanJing;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TaiPingHuanJing, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TaiPingHuanJing, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaiPingHuanJing, ID_BUTTON_EnterOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaiPingHuanJing, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaiPingHuanJing, ID_BUTTON_LeaveOnButtonClick )
CUI_ID_FRAME_TaiPingHuanJing::CUI_ID_FRAME_TaiPingHuanJing()
{
	// Member
	m_pID_FRAME_TaiPingHuanJing = NULL;
	m_pID_BUTTON_Enter = NULL;
	m_pID_PICTURE_rank1 = NULL;
	m_pID_PICTURE_rank2 = NULL;
	m_pID_PICTURE_rank3 = NULL;
	m_pID_PICTURE_rank4 = NULL;
	m_pID_PICTURE_rank5 = NULL;
	m_pID_PICTURE_rank6 = NULL;
	m_pID_BUTTON_Leave = NULL;
}
// Frame
bool CUI_ID_FRAME_TaiPingHuanJing::OnFrameRun()
{
	if (!_IsVisable())
	{
		return false;
	}
	CWorldTile* pCurrTile = CURRENTTILE;
	if(!pCurrTile)
		return false;

	if (pCurrTile->GetMapId() == theTPHJManager.GetMapIdByRank(thePlayerRole.GetTPHJRank()))		//已经在太平幻境中
	{
		m_pID_BUTTON_Enter->SetVisable(false);
		m_pID_BUTTON_Leave->SetVisable(true);
	}
	else
	{

		if (!theTPHJManager.MapCanEnterTphj( pCurrTile->GetMapId()))
		{
			m_pID_BUTTON_Enter->SetEnable(false);
		}
		else
		{
			m_pID_BUTTON_Enter->SetEnable(true);
		}
		m_pID_BUTTON_Enter->SetVisable(true);
		m_pID_BUTTON_Leave->SetVisable(false);
	}
	return true;
}
bool CUI_ID_FRAME_TaiPingHuanJing::OnFrameRender()
{
	return true;
}
bool CUI_ID_FRAME_TaiPingHuanJing::ID_BUTTON_EnterOnButtonClick( ControlObject* pSender )
{
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (!pMe)
	{
		return false;
	}
	if (thePlayerRole.GetTPHJRank()<=0)
	{
		return false;
	}

	/////////////////////////////////////////////
	CWorldTile* pCurrTile = CURRENTTILE;
	if(!pCurrTile)
		return false;
	if (!theTPHJManager.MapCanEnterTphj( pCurrTile->GetMapId()))
		return false;
	////////////////////////////////////////////lyh 在运镖的时候不可进入太平幻境

	if(s_CUI_ID_FRAME_OnBiaoChe.IsVisable() || s_CUI_ID_FRAME_OnBiaoChe.HaveBiaoche())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ListInfo_RandomTip, theXmlString.GetString( eText_ContEnterTPHJ_Onbiaoche ) );
		return false;
	}

	//lyh消息截取 ，解决太平环境不可骑乘的bug

		if(pMe->IsMounting())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ListInfo_RandomTip, theXmlString.GetString( eText_TargetMapCont_OnRiding ) );
			return false;
		}

	
	MsgC2GReqFLYTOTPHJ msg;
	msg.in_or_out = true;
	GettheNetworkInput().SendMsg(&msg);
	_SetVisable(false);
	return true;
}
bool CUI_ID_FRAME_TaiPingHuanJing::ID_BUTTON_LeaveOnButtonClick( ControlObject* pSender )
{
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (!pMe)
	{
		return false;
	}

	MsgC2GReqFLYTOTPHJ msg;
	msg.in_or_out = false;	
	GettheNetworkInput().SendMsg(&msg);
	_SetVisable(false);
	return true;
}


bool CUI_ID_FRAME_TaiPingHuanJing::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// 装载UI
bool CUI_ID_FRAME_TaiPingHuanJing::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TaiPingHuanJing.MEUI",false,UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TaiPingHuanJing.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TaiPingHuanJing::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TaiPingHuanJing, s_CUI_ID_FRAME_TaiPingHuanJingOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TaiPingHuanJing, s_CUI_ID_FRAME_TaiPingHuanJingOnFrameRender );	
	theUiManager.OnButtonClick( ID_FRAME_TaiPingHuanJing, ID_BUTTON_Enter, s_CUI_ID_FRAME_TaiPingHuanJingID_BUTTON_EnterOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TaiPingHuanJing, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TaiPingHuanJingID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TaiPingHuanJing, ID_BUTTON_Leave, s_CUI_ID_FRAME_TaiPingHuanJingID_BUTTON_LeaveOnButtonClick );

	m_pID_FRAME_TaiPingHuanJing = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TaiPingHuanJing );
	m_pID_BUTTON_Enter = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaiPingHuanJing, ID_BUTTON_Enter );
	m_pID_BUTTON_Leave = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaiPingHuanJing, ID_BUTTON_Leave );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaiPingHuanJing, ID_BUTTON_CLOSE );
	m_pID_PICTURE_rank1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaiPingHuanJing, ID_PICTURE_rank1 );
	m_pID_PICTURE_rank2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaiPingHuanJing, ID_PICTURE_rank2 );
	m_pID_PICTURE_rank3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaiPingHuanJing, ID_PICTURE_rank3 );
	m_pID_PICTURE_rank4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaiPingHuanJing, ID_PICTURE_rank4 );
	m_pID_PICTURE_rank5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaiPingHuanJing, ID_PICTURE_rank5 );
	m_pID_PICTURE_rank6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaiPingHuanJing, ID_PICTURE_rank6 );
	assert( m_pID_FRAME_TaiPingHuanJing );
	assert( m_pID_BUTTON_Enter );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_PICTURE_rank1 );
	assert( m_pID_PICTURE_rank2 );
	assert( m_pID_PICTURE_rank3 );
	assert( m_pID_PICTURE_rank4 );
	assert( m_pID_PICTURE_rank5 );
	assert( m_pID_PICTURE_rank6 );
	assert( m_pID_BUTTON_Leave );
	_SetVisable(false);	
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TaiPingHuanJing::_UnLoadUI()
{
	m_pID_FRAME_TaiPingHuanJing = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TaiPingHuanJing.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TaiPingHuanJing::_IsVisable()
{
	return m_pID_FRAME_TaiPingHuanJing->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TaiPingHuanJing::_SetVisable( const bool bVisable )
{
	if (_IsVisable() && bVisable)
	{
		return;
	}
	
	m_pID_FRAME_TaiPingHuanJing->SetVisable( bVisable );
	Refresh();
}

void CUI_ID_FRAME_TaiPingHuanJing::InitializeAtEnterWorld()
{
	if( !m_pID_FRAME_TaiPingHuanJing )
		return;

	//ClearSlotSpark();
	_SetVisable( false );
}

void CUI_ID_FRAME_TaiPingHuanJing::Clear()
{
	for (short i=0;i<=theTPHJManager.GetMaxRank();i++)
	{
		switch(i)
		{
		case 1:
			m_pID_PICTURE_rank1->SetPicName(theTPHJManager.FindTPHJRankByRankID(i)->gray_pic.c_str());
			break;
		case 2:
			m_pID_PICTURE_rank2->SetPicName(theTPHJManager.FindTPHJRankByRankID(i)->gray_pic.c_str());
			break;
		case 3:
			m_pID_PICTURE_rank3->SetPicName(theTPHJManager.FindTPHJRankByRankID(i)->gray_pic.c_str());
			break;
		case 4:
			m_pID_PICTURE_rank4->SetPicName(theTPHJManager.FindTPHJRankByRankID(i)->gray_pic.c_str());
			break;
		case 5:
			m_pID_PICTURE_rank5->SetPicName(theTPHJManager.FindTPHJRankByRankID(i)->gray_pic.c_str());
			break;
		case 6:
			m_pID_PICTURE_rank6->SetPicName(theTPHJManager.FindTPHJRankByRankID(i)->gray_pic.c_str());
			break;
		default:
			break;
		}
	}
}

void CUI_ID_FRAME_TaiPingHuanJing::Refresh()
{
	if (!_IsVisable())
	{
		return;
	}
	CWorldTile* pCurrTile = CURRENTTILE;
	if(!pCurrTile)
		return;

	if (pCurrTile->GetMapId() == theTPHJManager.GetMapIdByRank(thePlayerRole.GetTPHJRank()))		//已经在太平幻境中
	{
		m_pID_BUTTON_Enter->SetVisable(false);
		m_pID_BUTTON_Leave->SetVisable(true);
	}
	else
	{
		
		if (!theTPHJManager.MapCanEnterTphj( pCurrTile->GetMapId()))
		{
			m_pID_BUTTON_Enter->SetEnable(false);
		}
		else
		{
			m_pID_BUTTON_Enter->SetEnable(true);
		}
		m_pID_BUTTON_Enter->SetVisable(true);
		m_pID_BUTTON_Leave->SetVisable(false);
	}
	Clear();
	CTPHJManger::STPHJ* sRank = theTPHJManager.FindTPHJRankByRankID(thePlayerRole.GetTPHJRank());
	if (!sRank)
	{
		return;
	}
	switch (thePlayerRole.GetTPHJRank())
	{
	case 6:
		m_pID_PICTURE_rank6->SetPicName(theTPHJManager.FindTPHJRankByRankID(6)->rank_pic.c_str());
	case 5:
		m_pID_PICTURE_rank5->SetPicName(theTPHJManager.FindTPHJRankByRankID(5)->rank_pic.c_str());
	case 4:
		m_pID_PICTURE_rank4->SetPicName(theTPHJManager.FindTPHJRankByRankID(4)->rank_pic.c_str());
	case 3:
		m_pID_PICTURE_rank3->SetPicName(theTPHJManager.FindTPHJRankByRankID(3)->rank_pic.c_str());
	case 2:
		m_pID_PICTURE_rank2->SetPicName(theTPHJManager.FindTPHJRankByRankID(2)->rank_pic.c_str());
	case 1:
		m_pID_PICTURE_rank1->SetPicName(theTPHJManager.FindTPHJRankByRankID(1)->rank_pic.c_str());
	default:
		break;
	}
	
}	