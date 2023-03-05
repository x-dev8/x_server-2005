/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\KingScoreTipMin.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "KingScoreTipMin.h"
#include "KingScoreTip.h"
#include "MapConfig.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "ScoreTip.h"

CUI_ID_FRAME_KingScoreMin s_CUI_ID_FRAME_KingScoreMin;
MAP_FRAME_RUN( s_CUI_ID_FRAME_KingScoreMin, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_KingScoreMin, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_KingScoreMin, ID_BUTTON_MaxOnButtonClick )
CUI_ID_FRAME_KingScoreMin::CUI_ID_FRAME_KingScoreMin()
{
	// Member
	m_pID_FRAME_KingScoreMin = NULL;
	m_pID_BUTTON_Max = NULL;

	m_bKingFight = true;
}
	// Frame
	bool CUI_ID_FRAME_KingScoreMin::OnFrameRun()
	{
		return true;
	}
	bool CUI_ID_FRAME_KingScoreMin::OnFrameRender()
	{
		CWorldTile* pTile =CURRENTTILE;
		if (pTile && pTile->GetCanPk() != MapConfig::MapData::EPKM_Guild_PK)
		{
			_SetVisable(false);
		}
		return true;
	}
	// Button
	bool CUI_ID_FRAME_KingScoreMin::ID_BUTTON_MaxOnButtonClick( ControlObject* pSender )
	{
		if(!m_pID_FRAME_KingScoreMin)
			return false;
		m_pID_FRAME_KingScoreMin->SetVisable(false);

		if ( m_bKingFight )
			s_CUI_ID_FRAME_KingScoreTip.SetVisable(true);
		else
			s_CUI_ID_FRAME_ScoreTip.SetVisable( true );
		return true;
	}

	// 装载UI
bool CUI_ID_FRAME_KingScoreMin::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\KingScoreTipMin.MEUI", true );
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\KingScoreTipMin.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_KingScoreMin::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_KingScoreMin, s_CUI_ID_FRAME_KingScoreMinOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_KingScoreMin, s_CUI_ID_FRAME_KingScoreMinOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_KingScoreMin, ID_BUTTON_Max, s_CUI_ID_FRAME_KingScoreMinID_BUTTON_MaxOnButtonClick );

		m_pID_FRAME_KingScoreMin = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_KingScoreMin );
		m_pID_BUTTON_Max = (ControlButton*)theUiManager.FindControl( ID_FRAME_KingScoreMin, ID_BUTTON_Max );
		assert( m_pID_FRAME_KingScoreMin );
		assert( m_pID_BUTTON_Max );

		SetVisable(false);
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_KingScoreMin::_UnLoadUI()
	{
		m_pID_FRAME_KingScoreMin = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\KingScoreTipMin.MEUI" );
	}
	// 是否可视
	bool CUI_ID_FRAME_KingScoreMin::_IsVisable()
	{
		return m_pID_FRAME_KingScoreMin->IsVisable();
	}
	// 设置是否可视
	void CUI_ID_FRAME_KingScoreMin::_SetVisable( const bool bVisable )
	{
		m_pID_FRAME_KingScoreMin->SetVisable( bVisable );
		/*if(s_CUI_ID_FRAME_KingScoreTip.IsVisable() == bVisable)
			s_CUI_ID_FRAME_KingScoreTip.SetVisable(!bVisable);*/
	}
