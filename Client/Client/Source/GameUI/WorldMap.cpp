/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\WorldMap.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "WorldMap.h"
#include "AllNpcList.h"
#include "MeTerrain/stdafx.h"
#include "AllNpcList.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "ScreenInfoManager.h"
#include "SoundConfig.h"
#include "Cfg.h"
extern char* GetFullFileName(const char* filename);

CUI_ID_FRAME_WorldMap s_CUI_ID_FRAME_WorldMap;
MAP_FRAME_RUN( s_CUI_ID_FRAME_WorldMap, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_WorldMap, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WorldMap, ID_BUTTON_AreaMapOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WorldMap, ID_BUTTON_CloseOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WorldMap, ID_BUTTON_HelpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WorldMap, ID_BUTTON_WorldMapOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_WorldMap, ID_BUTTON_StoryMapOnButtonClick )
CUI_ID_FRAME_WorldMap::CUI_ID_FRAME_WorldMap()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_WorldMap::ResetMembers()
{
	m_pID_FRAME_WorldMap = NULL;
	//m_pID_PICTURE_TitleDi = NULL;
	m_pID_PICTURE_WorldMap = NULL;
	m_pID_BUTTON_AreaMap = NULL;
// 	m_pID_BUTTON_Close = NULL;
	//m_pID_BUTTON_Help = NULL;
	m_pID_PICTURE_FenGe = NULL;
	m_pID_BUTTON_WorldMap = NULL;
	m_pID_BUTTON_StoryMap = NULL;
	m_isWorldMap = true;
	buttonMap.clear();
	buttonStoryMap.clear();

}
// Frame
bool CUI_ID_FRAME_WorldMap::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_WorldMap::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_WorldMap::ID_BUTTON_AreaMapOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_WorldMap )
		return false;
	s_CUI_ID_FRAME_AllNpcList.SetVisable(true);
	/*RECT rcWindow;
	m_pID_FRAME_WorldMap->GetRealRect(&rcWindow);
	s_CUI_ID_FRAME_AllNpcList.SetPos(rcWindow.left,rcWindow.top);*/
	SetVisable(false);

	return true;
}
// Button
// bool CUI_ID_FRAME_WorldMap::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_WorldMap )
// 		return false;
// 	SetVisable(false);
// 	return true;
// }
// Button
// bool CUI_ID_FRAME_WorldMap::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_WorldMap )
// 		return false;
// 	return true;
// }

// 装载UI
bool CUI_ID_FRAME_WorldMap::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\WorldMap.MEUI" ,false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\WorldMap.MEUI]失败")
		return false;
	}
	else if ( dwResult != 1/*文件版本号*/ )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\WorldMap.MEUI]与源代码版本不一样")
	}
	return DoControlConnect();
}
const char strCityPrifix[] = "ID_BUTTON_City";
bool ID_BUTTON_CityOnButtonClick( ControlObject* pSender )
{
	char* pButtonId = pSender->GetControlID();
	char* pNumberBegin = &pButtonId[strlen(strCityPrifix)];
	int mapId = atoi(pNumberBegin);
	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(mapId);
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (!pTile || !pMe || (pMe->GetLevel() < pTile->GetMinLevel()))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_SearchInfo, theXmlString.GetString(eText_LevelNotReachable) );
		return false;

	}
	s_CUI_ID_FRAME_WorldMap.SetVisable(false);
	s_CUI_ID_FRAME_AllNpcList.SetVisable(true);
	RECT rcWindow;
	s_CUI_ID_FRAME_WorldMap.GetFrame()->GetRealRect(&rcWindow);
	s_CUI_ID_FRAME_AllNpcList.SetPos(rcWindow.left,rcWindow.top);
	int nMapIdInMyCountry = gCfg.GetMyCountryMapId(mapId,pMe->GetRealCountry());
	s_CUI_ID_FRAME_AllNpcList.InitByTile(SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapIdInMyCountry));
	return true;
}
// 关连控件
bool CUI_ID_FRAME_WorldMap::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_WorldMap, s_CUI_ID_FRAME_WorldMapOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_WorldMap, s_CUI_ID_FRAME_WorldMapOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_WorldMap, ID_BUTTON_AreaMap, s_CUI_ID_FRAME_WorldMapID_BUTTON_AreaMapOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_WorldMap, ID_BUTTON_Close, s_CUI_ID_FRAME_WorldMapID_BUTTON_CloseOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_WorldMap, ID_BUTTON_Help, s_CUI_ID_FRAME_WorldMapID_BUTTON_HelpOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_WorldMap, ID_BUTTON_WorldMap, s_CUI_ID_FRAME_WorldMapID_BUTTON_WorldMapOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_WorldMap, ID_BUTTON_StoryMap, s_CUI_ID_FRAME_WorldMapID_BUTTON_StoryMapOnButtonClick );

	m_pID_FRAME_WorldMap = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_WorldMap );
	//m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_PICTURE_TitleDi );
	m_pID_PICTURE_WorldMap = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_PICTURE_WorldMap );
		m_pID_PICTURE_StoryMap = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_PICTURE_StoryMap );
		m_pID_PICTURE_BgCountryInfo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_PICTURE_BgCountryInfo );
		m_pID_TEXT_TitleCountryMap = (ControlText*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_TEXT_TitleCountryMap );
	m_pID_BUTTON_AreaMap = (ControlButton*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_BUTTON_AreaMap );
// 	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_BUTTON_Close );
	//m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_BUTTON_Help );
	m_pID_PICTURE_FenGe = (ControlPicture*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_PICTURE_FenGe );


		m_pID_TEXT_CountryName = (ControlText*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_TEXT_CountryName );
		m_pID_TEXT_CountryDesc = (ControlText*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_TEXT_CountryDesc );
		m_pID_TEXT_TitleStoryMap = (ControlText*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_TEXT_TitleStoryMap );
		m_pID_BUTTON_WorldMap = (ControlButton*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_BUTTON_WorldMap );
		m_pID_BUTTON_StoryMap = (ControlButton*)theUiManager.FindControl( ID_FRAME_WorldMap, ID_BUTTON_StoryMap );
	assert( m_pID_FRAME_WorldMap );
	//assert( m_pID_PICTURE_TitleDi );
	assert( m_pID_PICTURE_WorldMap );
	assert( m_pID_BUTTON_AreaMap );
// 	assert( m_pID_BUTTON_Close );
	//assert( m_pID_BUTTON_Help );
	assert( m_pID_PICTURE_FenGe );

	char temp[256];
	CWorldBuffer* pBuffer = SwGlobal::GetWorld()->GetWorldBuffer();
	std::map<sInt32,CWorldTile*>& tileHash = pBuffer->GetTileMapHash();
	for(std::map<sInt32,CWorldTile*>::iterator iter = tileHash.begin(); iter != tileHash.end();++iter)
	{
		CWorldTile* pWorldTile =iter->second;
		if (pWorldTile == NULL) {	continue; }

		sprintf(temp,"%s%d",strCityPrifix,pWorldTile->GetMapId());
		ControlObject* pCityButton = m_pID_FRAME_WorldMap->FindControl(temp);
		if (pCityButton)
		{
			//if (gCfg.IsCountryMapInWorldMap(pWorldTile->GetMapId()))
			//{
				buttonMap.insert(make_pair(pWorldTile->GetMapId(),pCityButton));
			/*}
			else
			{
				buttonStoryMap.insert(make_pair(pWorldTile->GetMapId(),pCityButton));
			}*/
			theUiManager.OnButtonClick( ID_FRAME_WorldMap, temp, ID_BUTTON_CityOnButtonClick );
		}		
	}
	
	RefreshMapMode();

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_WorldMap::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\WorldMap.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_WorldMap::_IsVisable()
{
	if( !m_pID_FRAME_WorldMap )
		return false;
	return m_pID_FRAME_WorldMap->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_WorldMap::_SetVisable( const bool bVisable ,bool isWorldMap)
{
	if( !m_pID_FRAME_WorldMap )
		return;
	m_pID_FRAME_WorldMap->SetVisable( bVisable );
	if (bVisable)
	{
		m_isWorldMap = isWorldMap;
		s_CUI_ID_FRAME_AllNpcList.SetVisable(false);
		RefreshMapMode();
// 			RefreshButtonStatus();
	}
}

void CUI_ID_FRAME_WorldMap::RefreshButtonStatus()
{
	std::map<int,void*>::iterator iLoop;
	std::map<int,void*>* pMap = &buttonMap;
	if (!m_isWorldMap)
	{
		pMap = &buttonStoryMap;
	}
	for( iLoop = pMap->begin() ; iLoop != pMap->end() ; ++iLoop )
	{
		ControlObject* pCityButton = (ControlObject*)iLoop->second;
		if (NULL == pCityButton)
		{
			continue;
		}
		CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(iLoop->first);
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if (!pTile || !pMe || (pMe->GetLevel() < pTile->GetMinLevel()))
		{
			pCityButton->SetEnable(false);
		}
		else
		{
			pCityButton->SetEnable(true);
		}
	}

}

bool CUI_ID_FRAME_WorldMap::ID_BUTTON_WorldMapOnButtonClick( ControlObject* pSender )
{
	m_isWorldMap = true;
	RefreshMapMode();
	return true;
}

bool CUI_ID_FRAME_WorldMap::ID_BUTTON_StoryMapOnButtonClick( ControlObject* pSender )
{
	m_isWorldMap = false;
	RefreshMapMode();
	return true;
}

bool CUI_ID_FRAME_WorldMap::RefreshMapMode()
{
	m_pID_BUTTON_WorldMap->SetVisable(!m_isWorldMap);
	m_pID_PICTURE_StoryMap->SetVisable(!m_isWorldMap);
	m_pID_TEXT_TitleStoryMap->SetVisable(!m_isWorldMap);

	m_pID_BUTTON_StoryMap->SetVisable(m_isWorldMap);
	m_pID_TEXT_CountryDesc->SetVisable(m_isWorldMap);
	m_pID_TEXT_CountryName->SetVisable(m_isWorldMap);
	m_pID_PICTURE_BgCountryInfo->SetVisable(m_isWorldMap);
	m_pID_TEXT_TitleCountryMap->SetVisable(m_isWorldMap);
	m_pID_PICTURE_WorldMap->SetVisable(m_isWorldMap);

	std::map<int,void*>::iterator iLoop;
	for( iLoop = buttonMap.begin() ; iLoop != buttonMap.end() ; ++iLoop )
	{
		ControlObject* pCityButton = (ControlObject*)iLoop->second;
		pCityButton->SetVisable(m_isWorldMap);
	}
	for( iLoop = buttonStoryMap.begin() ; iLoop != buttonStoryMap.end() ; ++iLoop )
	{
		ControlObject* pCityButton = (ControlObject*)iLoop->second;
		pCityButton->SetVisable(!m_isWorldMap);
	}
	return true;
}

void CUI_ID_FRAME_WorldMap::SetVisable( const bool bVisable ,bool isWorldMap /*= true*/ )
{
	CUIBase::SetVisable(bVisable);
	if (m_bUILoad)
	{
		_SetVisable(bVisable,isWorldMap);
	}
	if( bVisable )
	{
		PlaySoundConfig( SoundConfig::EST_OpenWorldMapUI );
	}
}

void CUI_ID_FRAME_WorldMap::SetPos( int x,int y )
{
	if (m_pID_FRAME_WorldMap)
	{
		m_pID_FRAME_WorldMap->SetPos(x,y);
	}

}