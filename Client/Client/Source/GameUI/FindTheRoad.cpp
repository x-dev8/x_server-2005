/********************************************************************
Created by UIEditor.exe
FileName: E:\Zxc\3Guo_Client_10.19\3Guo_Client_10.19\Data\Ui\FindTheRoad.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FindTheRoad.h"
//#include "SlkReader.h"
//#include "ErrorLog.h"
//#include "ItemDetail.h"
//#include "GameMain.h"
//#include "AllNpcList.h"
//#include "Me3d\Include.h"
#include "MeTerrain/stdafx.h"
#include "MeTerrain/MapDef.h"
#include "NpcCoord.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "PositionInfo.h"
//#include "MiniMap.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "CrossMapPF.h"
#include "MapConfig.h"
#include "ScreenInfoManager.h"

CUI_ID_FRAME_FindRoad s_CUI_ID_FRAME_FindRoad;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FindRoad, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FindRoad, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FindRoad, ID_CHECKBOX_ChuanSongOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FindRoad, ID_BUTTON_CloseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_FindRoad, ID_BUTTON_BeginOnButtonClick)
CUI_ID_FRAME_FindRoad::CUI_ID_FRAME_FindRoad()
{
	// Member
	m_pID_FRAME_FindRoad = NULL;
	m_pID_TEXT_Qidian = NULL;
	m_pID_TEXT_Yidongluji = NULL;
	m_pID_TEXT_FindRoad[0] = NULL;
	m_pID_TEXT_FindRoad[1] = NULL;
	m_pID_TEXT_FindRoad[2] = NULL;
	m_pID_TEXT_Zhongdian = NULL;
	m_pID_CHECKBOX_ChuanSong = NULL;
	m_pID_TEXT_FindRoad[3] = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_BUTTON_Begin = NULL;
	//m_pID_TEXT_FindRoad[4] = NULL;

	for (int n =0; n <MAX_TEXT_COUNT;n++)
	{
		strRoadMapname[n].clear();
	}
	start_id = -1;
	target_id = -1;
	ftarget_X = 0.0f;
	ftarget_Y = 0.0f;

	//_vecThroughid.clear();
}
// Frame
bool CUI_ID_FRAME_FindRoad::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_FindRoad::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_FindRoad::ID_CHECKBOX_ChuanSongOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	theHeroGame.GetPlayerMgr()->GetMe()->StopMoving();

	CWorldTile* pCurrTile = CURRENTTILE;
	start_id = pCurrTile->GetMapId();

	bIsMultMove = false;
	_WalkLine._vecThroughid.clear();
	_TransmitLine.npc_id = -1;
	_TransmitLine._vecTransmit.clear();

	bool b = *pbChecked;
	RefreshRoadInfo(true,b);
	//m_pID_CHECKBOX_ChuanSong->SetCheck(true);
	//if (check_npcid)
	//{
	//	check_npcid = false;
	//	m_pID_BUTTON_Begin->SetVisable(true);
	//}
	//else
	//{
	//	check_npcid = true;
	//	m_pID_BUTTON_Begin->SetVisable(false);
	//}
	//findline(ntargetid,nstartid,nTheNpcID);
}


bool CUI_ID_FRAME_FindRoad::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	this->SetVisable(false);
	Refresh();
	return true;
}

void CUI_ID_FRAME_FindRoad::InitializeAtEnterWorld()
{
	if( !m_pID_FRAME_FindRoad )
		return;

	_SetVisable( false );
}

// 装载UI
bool CUI_ID_FRAME_FindRoad::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FindTheRoad.MEUI",false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FindTheRoad.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_FindRoad::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_FindRoad, s_CUI_ID_FRAME_FindRoadOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_FindRoad, s_CUI_ID_FRAME_FindRoadOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FindRoad, ID_CHECKBOX_ChuanSong, s_CUI_ID_FRAME_FindRoadID_CHECKBOX_ChuanSongOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_FindRoad, ID_BUTTON_Close, s_CUI_ID_FRAME_FindRoadID_BUTTON_CloseOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FindRoad, ID_BUTTON_Begin, s_CUI_ID_FRAME_FindRoadID_BUTTON_BeginOnButtonClick );
	m_pID_FRAME_FindRoad = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FindRoad );
	m_pID_TEXT_Qidian = (ControlText*)theUiManager.FindControl( ID_FRAME_FindRoad, ID_TEXT_Qidian );
	m_pID_TEXT_Yidongluji = (ControlText*)theUiManager.FindControl( ID_FRAME_FindRoad, ID_TEXT_Yidongluji );
	m_pID_TEXT_FindRoad[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_FindRoad, ID_TEXT_FindRoad1 );
	m_pID_TEXT_FindRoad[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_FindRoad, ID_TEXT_FindRoad2 );
	m_pID_TEXT_FindRoad[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_FindRoad, ID_TEXT_FindRoad3 );
	m_pID_TEXT_Zhongdian = (ControlText*)theUiManager.FindControl( ID_FRAME_FindRoad, ID_TEXT_Zhongdian );
	m_pID_CHECKBOX_ChuanSong = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FindRoad, ID_CHECKBOX_ChuanSong );
	m_pID_TEXT_FindRoad[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_FindRoad, ID_TEXT_FindRoad4 );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_FindRoad, ID_BUTTON_Close );
	m_pID_BUTTON_Begin = (ControlButton*)theUiManager.FindControl( ID_FRAME_FindRoad, ID_BUTTON_Begin );
	assert( m_pID_FRAME_FindRoad );
	assert( m_pID_TEXT_Qidian );
	assert( m_pID_TEXT_Yidongluji );
	assert( m_pID_TEXT_FindRoad[0] );
	assert( m_pID_TEXT_FindRoad[1] );
	assert( m_pID_TEXT_FindRoad[2] );
	assert( m_pID_TEXT_Zhongdian );
	assert( m_pID_CHECKBOX_ChuanSong );
	assert( m_pID_TEXT_FindRoad[3] );
	assert( m_pID_BUTTON_Close );
	assert(m_pID_BUTTON_Begin);

	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_FindRoad::_UnLoadUI()
{
	m_pID_FRAME_FindRoad = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\FindTheRoad.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_FindRoad::_IsVisable()
{
	return m_pID_FRAME_FindRoad->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_FindRoad::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_FindRoad->SetVisable( bVisable );
	if ( bVisable )
	{
        m_pID_CHECKBOX_ChuanSong->SetCheck( true );
		//RefreshRoadInfo();
		
	}
}
void CUI_ID_FRAME_FindRoad::ResetRoadInfo()
{
	if (!m_pID_FRAME_FindRoad)
	{
		return;
	}
	for (int n =0; n <MAX_TEXT_COUNT;n++)
	{
		strRoadMapname[n].clear();
		if (m_pID_TEXT_FindRoad[n])
		{
			m_pID_TEXT_FindRoad[n]->Clear();
		}
		if (m_pID_TEXT_Qidian)
		{
			m_pID_TEXT_Qidian->Clear();
		}
		if (m_pID_TEXT_Zhongdian)
		{
			m_pID_TEXT_Zhongdian->Clear();
		}
		if (m_pID_TEXT_Yidongluji)
		{
			m_pID_TEXT_Yidongluji->Clear();
		}
	}
	start_id = -1;
	target_id = -1;
	ftarget_X = 0.0f;
	ftarget_Y = 0.0f;
	target_npc_id = -1;
	bIsMultMove = false;
	_WalkLine._vecThroughid.clear();
	_TransmitLine.npc_id = -1;
	_TransmitLine._vecTransmit.clear();

	//_vecThroughid.clear();
}

//bool CUI_ID_FRAME_FindRoad::findline(int targetid,int startid,int nNpcId)
//{
//	Refresh();
//	//首先有没有起点的夸地图寻路数据
//	mapKwamemaps::iterator itrs = _mapKwamemapStartID.find(startid);
//	if (itrs == _mapKwamemapStartID.end())
//	{
//		return false;
//	}
//
//	SKwameMaps* pSKwameMaps = itrs->second;
//	if (!pSKwameMaps)
//	{
//		return false;
//	}
//
//	//终点是否在能跨地图寻路的范围内
//	mapSKwamemap::iterator itr = pSKwameMaps->_mapSKwamemap.find(targetid);
//	if (itr == pSKwameMaps->_mapSKwamemap.end())
//	{
//		return false;
//	}
//
//	SKwameMap* pSKwameMap = itr->second;
//	if (!pSKwameMap)
//	{
//		return false;
//	}
//
//	//尝试找出完整的路线
//	//vector<SKwameMap*> maps;
//	maps.push_back(pSKwameMap);
//	while (itr != pSKwameMaps->_mapSKwamemap.end())
//	{
//		//pSKwameMap = NULL;
//		itr = pSKwameMaps->_mapSKwamemap.find(pSKwameMap->nTargetMap_id);
//		if (itr == pSKwameMaps->_mapSKwamemap.end())
//		{
//			break;
//		}
//		pSKwameMap = itr->second;
//		if (!pSKwameMap)
//		{
//			break;
//		}
//		maps.push_back(pSKwameMap);
//	}
//
//	if (targetid < startid)
//	{
//		reverse(maps.begin(),maps.end());
//	}
//	else
//	{
//		sort(maps.begin(),maps.end());
//	}
//
//
//	ntargetid = targetid;
//	nstartid = startid;
//	nTheNpcID = nNpcId;
//
//	//s_CUI_ID_FRAME_AllNpcList.MoveToXY(pSKwameMap[i].fConveyX,pSKwameMap[i].fConveyY,pSKwameMap->nThroughMap_id);
//
//	//这里应该是一条条的显示,超过4条的话默认就让他选择传送点
//	if(maps.size() > 4)
//	{
//		m_pID_CHECKBOX_ChuanSong->SetEnable(false);
//		RefreshChuansongdian(targetid,startid,nNpcId);
//		Refresh();
//		return true;
//	}
//	else
//	{
//		if (nNpcId != NULL)
//		{   
//			if (!check_npcid)
//			{
//				m_pID_CHECKBOX_ChuanSong->SetEnable(true);
//				//第一个text
//				CWorldTile* pCurrTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(startid);
//				const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(nNpcId,targetid);
//				//PositionInfo::Position* pInfo = PositionInfo::Instance().GetPositionByName(pCurrTile->GetTileName());
//				char szInfo[256] = {0};
//
//
//				MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_QiDian),pCurrTile->GetTileName(),Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
//				m_pID_TEXT_Qidian->SetText(szInfo);
//				m_pID_TEXT_Qidian->SetVisable(true);
//
//				//第二个text
//				MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_YiDongLuJing));
//				m_pID_TEXT_Yidongluji->SetText(szInfo);
//				m_pID_TEXT_Yidongluji->SetVisable(true);
//
//				//第3,4,5,6个Text
//
//				/*for (int i = 0;i < maps.size();++i)*/
//				for (int i = 0;i < maps.size();++i)
//				{	
//
//					//3,4,5,6
//					CWorldTile* pTile1 = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(maps[i]->_mapThroughid[i]->nMap_id/*pSKwameMap[i].nThroughMap_id*/);
//					CWorldTile* pTile2 = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(maps[i]->nTargetMap_id/*pSKwameMap[i].nTargetMap_id*/);
//					if (pTile1 == NULL || pTile2 ==NULL)
//					{
//						break;
//					}
//
//					MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_LuJing1),pTile1->GetTileName(),pTile2->GetTileName());
//					std::vector<UiCallbackDataBase*> CallBackDataArr;
//					std::string text = szInfo;
//					strRoadMapname[i] = pTile2->GetTileName();
//					//const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pTile2->GetTileName(),pTile2->GetMapId());
//					PositionInfo::Position* pInfo = PositionInfo::Instance().GetPositionByName(pTile2->GetTileName());				
//					if (pInfo == NULL)
//					{
//						return false;
//					}
//					//NpcCoord::getInstance()->addNpcHyberForText( text, NpcCoord::eMapId, -1,pInfo->_nID, &CallBackDataArr );
//					//NpcCoord::getInstance()->addNpcHyberForTextName( text, NpcCoord::eMapId, -1,NULL, &CallBackDataArr,false );
//					m_pID_TEXT_FindRoad[i]->SetText(text);
//					m_pID_TEXT_FindRoad[i]->SetVisable(true);
//
//				}
//
//				//第7个text
//				MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_FindTheNpc),Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
//				std::vector<UiCallbackDataBase*> CallBackDataArr;
//				std::string text = szInfo;
//				NpcCoord::getInstance()->addNpcHyberForText( text, NpcCoord::eMapId, -1,pInfo->_nID, &CallBackDataArr );
//				//NpcCoord::getInstance()->addNpcHyberForTextName( text, NpcCoord::eMapId, -1,NULL, &CallBackDataArr,false );
//				m_pID_TEXT_Zhongdian->SetText(text);
//				m_pID_TEXT_Zhongdian->SetVisable(true);
//
//			}
//			else
//			{
//				RefreshChuansongdian(targetid,startid,nNpcId);
//				//Refresh();
//			}
//			//Refresh();
//			return true;
//		}
//	}
//
//	return false;
//}


void CUI_ID_FRAME_FindRoad::Refresh()
{	
	for (int i = 0;i<MAX_TEXT_COUNT;++i)
	{
		m_pID_TEXT_FindRoad[i]->Clear();
		//m_pID_TEXT_FindRoad[i]->SetVisable(false);
	}
}


//这刷新是玩家点击通过NPC传送时候的做的
bool CUI_ID_FRAME_FindRoad::RefreshChuansongdian(int targetid,int startid,int nNpcId)
{
	return true;
	//第一个text
	//MapConfig::MapData* pCurMap = theMapConfig.GetMapDataById(startid);
	//if (!pCurMap)
	//{
	//	return false;
	//}
	//const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(nNpcId);
	//char szInfo[256] = {0};
	//MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_QiDian),pCurMap->MapName.c_str(),Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
	//m_pID_TEXT_Qidian->SetText(szInfo);
	//m_pID_TEXT_Qidian->SetVisable(true);

	////第二个text
	//MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_YiDongLuJing));
	//m_pID_TEXT_Yidongluji->SetText(szInfo);
	//m_pID_TEXT_Yidongluji->SetVisable(true);

	////第3,4,5,6个Text
	////for (int i = 0;i < _vecThroughid.size();++i)
	////{
	////	//3,4,5,6
	////	MapData* pTile1 = theMapConfig.GetMapDataById(_vecThroughid[i]);
	////	if (pTile1 == NULL)
	////	{
	////		continue;
	////	}
	////	if (maps[i]->_mapThroughid[i]->nChuanSong_NpcID == NULL)
	////	{
	////		m_pID_TEXT_FindRoad[i]->SetVisable(false);
	////		continue;
	////	}

	////	const char* szName = NpcCoord::getInstance()->GetNpcName(maps[i]->_mapThroughid[i]->nChuanSong_NpcID);
	////	MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_LuJing1),pTile1->GetTileName(),szName);

	////	///*std::vector<UiCallbackDataBase*> CallBackDataArr;
	////	//std::string text = szInfo;
	////	//NpcCoord::getInstance()->addNpcHyberForText( text, NpcCoord::eMapId, -1,-1, &CallBackDataArr );*/

	////	std::vector<UiCallbackDataBase*> CallBackDataArr;
	////	std::string text = szInfo;
	////	const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(szName,pTile1->GetMapId());
	////	if (pInfo == NULL)
	////	{
	////		return false;
	////	}
	////	NpcCoord::getInstance()->addNpcHyberForText( text, NpcCoord::eMapId, -1,pInfo->_nID, &CallBackDataArr );

	////	m_pID_TEXT_FindRoad[i]->SetText(text);
	////	m_pID_TEXT_FindRoad[i]->SetVisable(true);

	////}

	////第7个text
	//MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_FindTheNpc),Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
	//std::vector<UiCallbackDataBase*> CallBackDataArr;
	//std::string text = szInfo;
	//NpcCoord::getInstance()->addNpcHyberForText( text, NpcCoord::eMapId, -1,pInfo->_nID, &CallBackDataArr );
	//m_pID_TEXT_Zhongdian->SetText(text);
	//m_pID_TEXT_Zhongdian->SetVisable(true);
}


//每次跳转一张地图就会判断是否要隐藏掉一个text
void CUI_ID_FRAME_FindRoad::CloseText()
{
	/*CWorldTile* pCurrTile = CURRENTTILE;
	if(!pCurrTile)
		return;
	CWorldTile* pTile1 = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pCurrTile->GetMapId());
	std::string strNowMapname = pTile1->GetTileName();
	for (int i = 0;i < MAX_TEXT_COUNT;++i)
	{
		if (strNowMapname == strRoadMapname[i])
		{
			m_pID_TEXT_FindRoad[i]->SetVisable(false);
		}
	}*/
	return;
}


bool CUI_ID_FRAME_FindRoad::ID_BUTTON_BeginOnButtonClick(ControlObject* pSender)
{
	return ProcessMultMoving();
	/*CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (pMe)
	{*/
		/*float x,y;
		for (int i = 0; i<maps.size();++i)
		{
			pMe->GetPos(&x,&y,NULL);*/

			/*vector<SKwameMap*>::iterator itr = maps.begin();
			SKwameMap* p = itr->second;
			MapConfig::MapData* pMap = theMapConfig.GetMapDataById(p->_mapThroughid[i]->nMap_id);
			fConveyX = pMap->mapTransportDestinations[i].PositionX;
			fConveyY = pMap->mapTransportDestinations[i].PositionY;
			CWorldTile* pCurrTile = CURRENTTILE;
			bool bRet = CrossMapPF::Instance()->CrossMapFindPath(pCurrTile->GetMapId(),x,y,pMap->Id,fConveyX,fConveyY);
			maps.erase(itr);
			if(bRet)
			{
			return  true;
			}*/
			//vector<SKwameMap*>::iterator itr = maps.begin();
			/*vector<SKwameMap*>::iterator itr1 = map.begin();
			itr1++;*/
			//SKwameMap* p = itr.second;
			//通过MAPID拿到地图数据，或者到下一个点的传送点位置
			//MapConfig::MapData* pMap = theMapConfig.GetMapDataById(evt.mapId);
			//pMap找到到itr1的传送点位置
			//moveto(starid,x,y,targetid,(下一张地图到再下一张地图的传送点位置),(下一张地图到再下一张地图的传送点位置));
			//maps.erase(itr);
		//}	
	//}
	/*return false;*/
}

void CUI_ID_FRAME_FindRoad::SetTargetInfo(int startid,int tragetid,float targetx,float targety,int target_npcid)
{
	start_id = startid;						//当前地图ID 
	target_id = tragetid;          //最终的MAPID
	ftarget_X = targetx;			//最终的X坐标
	ftarget_Y = targety;			//最终的Y坐标
	target_npcid = target_npcid;
}

bool CUI_ID_FRAME_FindRoad::RefreshRoadInfo( bool bCheck ,bool _value )
{
	Refresh();
	CKwamemap::SKwameMap* pKwameMap = theKwamemap.FindKwameMap(start_id,target_id);
	if (!pKwameMap)
	{
		SetVisable(false);
		//todo:如果找不到寻路信息,给了提示
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_MiniMapFindPath, theXmlString.GetString(eClient_AddInfo_PFError) );		
		return false;
	}

	//_WalkLine._vecThroughid.resize(pKwameMap->_SWalkLine._vecThroughid.size());
	//copy(pKwameMap->_SWalkLine._vecThroughid.begin(), pKwameMap->_SWalkLine._vecThroughid.end(), _WalkLine._vecThroughid.begin());	


	//_TransmitLine._vecTransmit.resize(pKwameMap->_STransmitLine._vecTransmit.size());
	//copy(pKwameMap->_STransmitLine._vecTransmit.begin(), pKwameMap->_STransmitLine._vecTransmit.end(), _TransmitLine._vecTransmit.begin());
	//_TransmitLine.npc_id = pKwameMap->_STransmitLine.npc_id;

	//

	//if (!bCheck)
	//{
	//	if(_WalkLine._vecThroughid.size() > 0)  
	//	{
	//		m_pID_CHECKBOX_ChuanSong->SetCheck( false );

	//	}else if (_TransmitLine._vecTransmit.size() > 0)
	//	{	
	//		m_pID_CHECKBOX_ChuanSong->SetCheck( true ); //优先传送
	//	}else
	//	{
	//		SetVisable(false);
	//		//todo:如果找不到寻路信息,给了提示
	//		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_MiniMapFindPath, theXmlString.GetString(eClient_AddInfo_PFError) );		
	//		return false;
	//	}

	//}else
	//{
 //       m_pID_CHECKBOX_ChuanSong->SetCheck(_value);
	//}





	

	//copy行走和传送路线
	if (!m_pID_CHECKBOX_ChuanSong->IsChecked())
	{
		_WalkLine._vecThroughid.resize(pKwameMap->_SWalkLine._vecThroughid.size());
		copy(pKwameMap->_SWalkLine._vecThroughid.begin(), pKwameMap->_SWalkLine._vecThroughid.end(), _WalkLine._vecThroughid.begin());	
		RefreshWalkLineText();
	}
	else
	{
		_TransmitLine._vecTransmit.resize(pKwameMap->_STransmitLine._vecTransmit.size());
		copy(pKwameMap->_STransmitLine._vecTransmit.begin(), pKwameMap->_STransmitLine._vecTransmit.end(), _TransmitLine._vecTransmit.begin());
		_TransmitLine.npc_id = pKwameMap->_STransmitLine.npc_id;
		RefreshTransmitLineText();
	}
	return true;
	//if(_vecThroughid.size() > 4)
	//{
	//	m_pID_CHECKBOX_ChuanSong->SetEnable(false);
	//	RefreshChuansongdian(target_id,start_id,pKwameMap->nChuanSong_NpcID);		
	//	return true;
	//}
	//else
	//{		
	//	if (pKwameMap->nChuanSong_NpcID > 0)
	//	{
	//		if (!check_npcid)
	//		{
	//			m_pID_CHECKBOX_ChuanSong->SetEnable(true);
	//			//第一个text
	//			MapConfig::MapData* pCurMap = theMapConfig.GetMapDataById(start_id);
	//			if (!pCurMap)
	//			{
	//				return false;
	//			}
	//			const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pKwameMap->nChuanSong_NpcID);				
	//			char szInfo[256] = {0};

	//			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_QiDian),pCurMap->MapName.c_str(),Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
	//			m_pID_TEXT_Qidian->SetText(szInfo);
	//			m_pID_TEXT_Qidian->SetVisable(true);

	//			//第二个text
	//			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_YiDongLuJing));
	//			m_pID_TEXT_Yidongluji->SetText(szInfo);
	//			m_pID_TEXT_Yidongluji->SetVisable(true);

	//			//第3,4,5,6个Text
	//			for (int i = 0;i < _vecThroughid.size();++i)
	//			{
	//				//3,4,5,6	
	//				MapConfig::MapData* pMap1 = theMapConfig.GetMapDataById(_vecThroughid[i]);
	//				MapConfig::MapData* pMap2 = theMapConfig.GetMapDataById(target_id);
	//				if (!pMap2||!pMap1)
	//				{
	//					break;
	//				}

	//				MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_LuJing1),pMap1->MapName.c_str(),pMap2->MapName.c_str());
	//				std::vector<UiCallbackDataBase*> CallBackDataArr;
	//				std::string text = szInfo;
	//				strRoadMapname[i] = pMap2->MapName.c_str();					
	//				//PositionInfo::Position* pInfo = PositionInfo::Instance().GetPositionByName(pMap2->MapName.c_str());				
	//				//if (pInfo == NULL)
	//				//{
	//				//	return;
	//				//}
	//				m_pID_TEXT_FindRoad[i]->SetText(text);
	//				m_pID_TEXT_FindRoad[i]->SetVisable(true);
	//			}

	//			//第7个text
	//			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_FindTheNpc),Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
	//			std::vector<UiCallbackDataBase*> CallBackDataArr;
	//			std::string text = szInfo;
	//			NpcCoord::getInstance()->addNpcHyberForText( text, NpcCoord::eMapId, -1,pInfo->_nID, &CallBackDataArr );				
	//			m_pID_TEXT_Zhongdian->SetText(text);
	//			m_pID_TEXT_Zhongdian->SetVisable(true);
	//		}
	//		else
	//		{
	//			RefreshChuansongdian(target_id,start_id,pKwameMap->nChuanSong_NpcID);
	//		}
	//		return true;
	//	}
	//}
}

bool CUI_ID_FRAME_FindRoad::ProcessMultMoving()
{
	CWorldTile* pCurrTile = CURRENTTILE;
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (pMe&&pCurrTile)
	{
		//1,获得角色当前所在地图的位置
		bool bRet = false;
		float x,y;
		pMe->GetPos(&x,&y,NULL);

		MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(pCurrTile->GetMapId());
		if (!pMapData)
		{
			return false;
		}

		if (m_pID_CHECKBOX_ChuanSong->IsChecked())
		{
			//需要通过传送NPC

			//2,第一个传送点是否需要先到达提示传送
			const NpcCoordInfo* pInfo = NULL;
			CKwamemap::vecTransmit::iterator itr = _TransmitLine._vecTransmit.begin();
			if (_TransmitLine.npc_id > 0)
			{
				pInfo = NpcCoord::getInstance()->getNpcCoord(_TransmitLine.npc_id);
			}
			if (pInfo)
			{
				if (theHeroGame.GetPlayerMgr()->MoveRoleToNPC(pInfo))
				{
					if (itr == _TransmitLine._vecTransmit.end())
					{
						_TransmitLine.npc_id = -1;
					}
					else
					{
						_TransmitLine.npc_id = _TransmitLine._vecTransmit[0]->npc_id;
						_TransmitLine._vecTransmit.erase(itr);
					}
					bIsMultMove = true;
				}
			}
			else
			{
				if (itr == _TransmitLine._vecTransmit.end())
				{
					if (pCurrTile->GetMapId() == target_id)
					{
						bRet = theHeroGame.GetPlayerMgr()->MoveRoleTo(ftarget_X,ftarget_Y,true,false);
					}
					else
						bRet = CrossMapPF::Instance()->CrossMapFindPath(pCurrTile->GetMapId(),x,y,target_id,ftarget_X,ftarget_Y);

					bIsMultMove = false;
				}
				else
				{
					MapConfig::TransportPosition* pTransport = NULL;
					for (int n =0;n < pMapData->TransportPositionCount();n++)
					{
						pTransport = pMapData->GetTransportPositionByIndex(n);
						if (!pTransport)
						{
							continue;
						}
						if (pTransport->TargetMapId == _TransmitLine._vecTransmit[0]->mapid)
						{
							break;
						}
					}

					//3,取传送点中间点坐标,并寻路过去
					float go_x = pTransport->MinX + abs(pTransport->MaxX - pTransport->MinX)/2;
					float go_y = pTransport->MinY + abs(pTransport->MaxY - pTransport->MinY)/2;

					bRet = CrossMapPF::Instance()->CrossMapFindPath(pCurrTile->GetMapId(),x,y,pTransport->TargetMapId,go_x,go_y);
					bIsMultMove = true;
					_TransmitLine.npc_id = _TransmitLine._vecTransmit[0]->npc_id;
					_TransmitLine._vecTransmit.erase(itr);
				}
			}
		}
		else
		{
			//不通过传送NPC.直接行走
			//2,得到当前所在地图到下一张地图的传送点位置,如果没有需要经过的地图了,则直接去目标点地图
			//经过的地图
			CKwamemap::vecThroughid::iterator itr = _WalkLine._vecThroughid.begin();
			if (itr != _WalkLine._vecThroughid.end())
			{
				MapConfig::TransportPosition* pTransport = NULL;
				for (int n =0;n < pMapData->TransportPositionCount();n++)
				{
					pTransport = pMapData->GetTransportPositionByIndex(n);
					if (!pTransport)
					{
						continue;
					}
					if (pTransport->TargetMapId == _WalkLine._vecThroughid[0])
					{
						break;
					}
				}

				//3,取传送点中间点坐标,并寻路过去
				float go_x = pTransport->MinX + abs(pTransport->MaxX - pTransport->MinX)/2;
				float go_y = pTransport->MinY + abs(pTransport->MaxY - pTransport->MinY)/2;

				bRet = CrossMapPF::Instance()->CrossMapFindPath(pCurrTile->GetMapId(),x,y,pTransport->TargetMapId,go_x,go_y);
				_WalkLine._vecThroughid.erase(itr);
				bIsMultMove = true;
			}
			else
			{
				bRet = CrossMapPF::Instance()->CrossMapFindPath(pCurrTile->GetMapId(),x,y,target_id,ftarget_X,ftarget_Y);
				bIsMultMove = false;
			}
			return bRet;
		}	
 	}
	return false;
}

void CUI_ID_FRAME_FindRoad::RefreshWalkLineText()
{
	if (_WalkLine._vecThroughid.size() <= 0)
	{//todo:如果行走路线空了,要做些什么?
	}
	else
	{
		char szInfo[256] = {0};
		MapConfig::MapData* pTargetMap = NULL;
		const NpcCoordInfo* pInfo = NULL;
		MapConfig::MapData* pStartMap = theMapConfig.GetMapDataById(start_id);		
		if (!pStartMap)
		{
			return;
		}
		if (target_npc_id > 0)
		{
			pInfo = NpcCoord::getInstance()->getNpcCoord(target_npc_id);
			if (!pInfo)
			{
				return;
			}
			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,
				theXmlString.GetString(eText_QiDian),
				pStartMap->MapName.c_str(),Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
		}
		else
		{
			pTargetMap = theMapConfig.GetMapDataById(target_id);
			if (!pTargetMap)
			{
				return;
			}
			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,
				theXmlString.GetString(eText_QiDian),
				pStartMap->MapName.c_str(),pTargetMap->MapName.c_str());
		}
		//todo:超链接

		//起点信息
		m_pID_TEXT_Qidian->SetText(szInfo);
		m_pID_TEXT_Qidian->SetVisable(true);

		//终点信息
		std::string text;
		if (pInfo)
		{
			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_FindTheNpc),Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
			std::vector<UiCallbackDataBase*> CallBackDataArr;
			text = szInfo;
			NpcCoord::getInstance()->addNpcHyberForText( text, NpcCoord::eMapId, -1,pInfo->_nID, &CallBackDataArr );	
		}
		else if (pTargetMap)
		{
			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,
				theXmlString.GetString(eText_QiDian),
				pStartMap->MapName.c_str(),pTargetMap->MapName.c_str());
		}					
		m_pID_TEXT_Zhongdian->SetText(text);
		m_pID_TEXT_Zhongdian->SetVisable(true);

		for (int n =0;n < MAX_TEXT_COUNT&&n < _WalkLine._vecThroughid.size();n++)
		{
			if (n == MAX_TEXT_COUNT -1 && _WalkLine._vecThroughid.size() > 4)
			{
				MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_More));
				m_pID_TEXT_FindRoad[n]->SetText(szInfo);
			}
			else
			{
				MapConfig::MapData* pMap1 = theMapConfig.GetMapDataById(_WalkLine._vecThroughid[n]);
				MapConfig::MapData* pMap2 = NULL;
				if (n+1 < _WalkLine._vecThroughid.size())
				{
					pMap2 =theMapConfig.GetMapDataById(_WalkLine._vecThroughid[n+1]);
				}
				else
					pMap2 =theMapConfig.GetMapDataById(target_id);

				if (!pMap2||!pMap1)
				{
					break;
				}

				MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_LuJing1),pMap1->MapName.c_str(),pMap2->MapName.c_str());				
				text = szInfo;
				//todo:记得加上超链接,比如:
				//std::vector<UiCallbackDataBase*> CallBackDataArr;
				//NpcCoord::getInstance()->addNpcHyberForText( text, NpcCoord::eMapId, -1,pInfo->_nID, &CallBackDataArr );				
				/////////////////////////////////////////
				m_pID_TEXT_FindRoad[n]->SetText(text);
			}
		}
	}
}
void CUI_ID_FRAME_FindRoad::RefreshTransmitLineText()
{
	//if (_TransmitLine._vecTransmit.size() <= 0)
	//{//todo:如果行走路线空了,要做些什么?
	//}
	//else
	{
		char szInfo[256] = {0};
		MapConfig::MapData* pTargetMap = NULL;
		const NpcCoordInfo* pInfo = NULL;
		MapConfig::MapData* pStartMap = theMapConfig.GetMapDataById(start_id);		
		if (!pStartMap)
		{
			return;
		}
		if (target_npc_id > 0)
		{
			pInfo = NpcCoord::getInstance()->getNpcCoord(target_npc_id);
			if (!pInfo)
			{
				return;
			}
			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,
				theXmlString.GetString(eText_QiDian),
				pStartMap->MapName.c_str(),Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
		}
		else
		{
			pTargetMap = theMapConfig.GetMapDataById(target_id);
			if (!pTargetMap)
			{
				return;
			}
			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,
				theXmlString.GetString(eText_QiDian),
				pStartMap->MapName.c_str(),pTargetMap->MapName.c_str());
		}
		//todo:超链接

		//起点信息
		m_pID_TEXT_Qidian->SetText(szInfo);
		m_pID_TEXT_Qidian->SetVisable(true);

		//终点信息
		std::string text;
		if (pInfo)
		{
			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_FindTheNpc),Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
			std::vector<UiCallbackDataBase*> CallBackDataArr;
			text = szInfo;
			NpcCoord::getInstance()->addNpcHyberForText( text, NpcCoord::eMapId, -1,pInfo->_nID, &CallBackDataArr );	
		}
		else if (pTargetMap)
		{
			MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,
				theXmlString.GetString(eText_QiDian),
				pStartMap->MapName.c_str(),pTargetMap->MapName.c_str());
		}
		m_pID_TEXT_Zhongdian->SetText(text);
		m_pID_TEXT_Zhongdian->SetVisable(true);

		for (int n =0,i = 0;n < MAX_TEXT_COUNT && i < MAX_TEXT_COUNT && n <= _TransmitLine._vecTransmit.size();n++)
		{
			if (n == MAX_TEXT_COUNT -1 && _TransmitLine._vecTransmit.size() > 4)
			{
				MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_More));
				m_pID_TEXT_FindRoad[n]->SetText(szInfo);
			}
			else
			{
				MapConfig::MapData* pMap1 = NULL/*theMapConfig.GetMapDataById(_TransmitLine._vecTransmit[n]->mapid)*/;
				if (n > 0)
					pMap1 = theMapConfig.GetMapDataById(_TransmitLine._vecTransmit[n-1]->mapid);
				MapConfig::MapData* pMap2 = NULL;
				if (n/*+1*/ < _TransmitLine._vecTransmit.size())
				{
					pMap2 =theMapConfig.GetMapDataById(_TransmitLine._vecTransmit[n/*+1*/]->mapid);
				}
				else
					pMap2 =theMapConfig.GetMapDataById(target_id);
				
				const NpcCoordInfo* pInfo1 = NULL;
				if (n == 0)
				{
					pInfo1 = NpcCoord::getInstance()->getNpcCoord(_TransmitLine.npc_id);
				}
				else
					pInfo1 = NpcCoord::getInstance()->getNpcCoord(_TransmitLine._vecTransmit[n-1]->npc_id);

				NpcCoord::getInstance()->getNpcCoord(_TransmitLine.npc_id);
				if ((!pMap2&&!pInfo1)/*||!pMap1*/)
				{
					break;
				}

				memset(szInfo, 0, sizeof(szInfo));

				if (pInfo1)
				{
					MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_LuJing1),Common::_tstring::toNarrowString(pInfo1->_szName.c_str()).c_str(),pMap2->MapName.c_str());
				}
				else if( !pInfo1 && pMap1 && pMap2)
					MeSprintf_s(szInfo,sizeof(szInfo)/sizeof(char) - 1,theXmlString.GetString(eText_LuJing1),pMap1->MapName.c_str(),pMap2->MapName.c_str());

				text = szInfo;
				if (text.length() > 0)
				{
					m_pID_TEXT_FindRoad[i]->SetText(text);
					i++;
				}
				//todo:记得加上超链接,比如:
				//std::vector<UiCallbackDataBase*> CallBackDataArr;
				//NpcCoord::getInstance()->addNpcHyberForText( text, NpcCoord::eMapId, -1,pInfo->_nID, &CallBackDataArr );				
				/////////////////////////////////////////
				//m_pID_TEXT_FindRoad[n]->SetText(text);
			}
		}
	}
}