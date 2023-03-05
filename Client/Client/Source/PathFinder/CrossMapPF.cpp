/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	CrossMapPF.cpp
* Create: 	10/14/06
* Desc:		地图类
* Author:	yuanding
*
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "GameMain.h"
#include "CrossMapPF.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "ItemDetail.h"
#include "ScreenInfoManager.h"
#include "PlayerRole.h"
#include "Dxsdk/dinput.h"
#include "CommonChatFrame.h"
#include "core/Name.h"
#include "color_config.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "cfg.h"
//#include "MiniMap.h"
//#include "Player.h"
//#include "GameMain.h"
//#include "PlayerMgr.h"
//#include "Source/FindTheRoad.h"
extern short GetKeyboardInput( int iKey );
extern CHeroGame* theApp;
extern CPlayerRole thePlayerRole;
CrossMapPF::CrossMapPF()
{
	Reset();
}

CrossMapPF::~CrossMapPF()
{}

void CrossMapPF::Reset()
{
	m_bActive		= false;
	mfMinWeight		= INT_MAX;
	m_nMinMapCross	= INT_MAX;
	m_nEndMapId		= -1;
	m_endx			= 0.f;
	m_endy			= 0.f;
	mTransportArr.clear();
}

bool CrossMapPF::CrossMapFindPath( int startMapId,float startx,float starty,int endMapId,float endx,float endy/* ,int nType*/)
{
	if( GetKeyboardInput(DIK_LALT) || GetKeyboardInput(DIK_RALT) )
	{
		CommonChatFrame::GetActiveChatFrame()->addAddressText( endMapId,endx,endy );	
		return true;
	}

	CPlayer* pMe = theApp->GetPlayerMgr()->GetMe();

	int nEndMapIdInMyCountry = endMapId;
	if (pMe)
	{
		nEndMapIdInMyCountry = gCfg.GetMyCountryMapId(endMapId,pMe->GetRealCountry());
	}
	m_nPlayerLevel = thePlayerRole.GetLevel();
	if (m_nPlayerLevel < GetMapLevel(nEndMapIdInMyCountry))
	{
		char temp[1024];
		MeSprintf_s(temp,sizeof(temp)/sizeof(char) - 1,theXmlString.GetString(eTellClient_LessMapMinLevel),GetMapLevel(nEndMapIdInMyCountry));
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, temp );
		return true;
	}
	Reset();
	m_nEndMapId = nEndMapIdInMyCountry;
	m_endx		= endx;
	m_endy		= endy;
	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(startMapId);
	CResMgr* pResMgr = pTile->GetCResMgr();
	for (int i = 0; i < pResMgr->GetTransportCount();++i)
	{
		CTransportResBase* pRes = pResMgr->Transport(i);
		if (pRes->IsTransport())
		{
			float weight = sqrt((startx - pRes->GetPosX())*(startx - pRes->GetPosX())
				+(starty - pRes->GetPosY())*(starty - pRes->GetPosY()));
			std::vector<CTransportResBase*>			localTransportArr;
			localTransportArr.push_back(pRes);
			std::vector<int>			localMapIdArr;
			localMapIdArr.push_back(startMapId);
			GetValidPathWeight(weight,localTransportArr,localMapIdArr);
		}
	}
	if (mTransportArr.size() != 0)
	{
		m_bActive = true;
		m_nMapCross = 0;
		CTransportResBase* pRes = mTransportArr[0];
		if( theApp->GetPlayerMgr()->GetMe())
		{
			return theApp->GetPlayerMgr()->MoveRoleTo(pRes->GetPosX(),pRes->GetPosY(),true,false);
			//if(nType == 4)
			//{
			//	//GetAdvancedMiniMap()->ProcessMinimapMouseDownL(LOWORD(pRes->GetPosX()), HIWORD((int)pRes->GetPosY));
			//	return theApp->GetPlayerMgr()->MoveRoleTo(pRes->GetPosX(),pRes->GetPosY(),false,false,false);
			//}
			//else
			//{
			//	return theApp->GetPlayerMgr()->MoveRoleTo(pRes->GetPosX(),pRes->GetPosY(),true,false);
			//}
		}
	}
	//m_bActive = true;
	return false;
}

bool CrossMapPF::GetValidPathWeight(float  weight,std::vector<CTransportResBase*>&	TransportArr,std::vector<int>&	CrossMapIdArr)
{
	if (CrossMapIdArr.size() > m_nMinMapCross)
	{
		return false;
	}
	CTransportRes* transport = (CTransportRes*)TransportArr[TransportArr.size() - 1];
	if (m_nPlayerLevel < GetMapLevel(transport->GetDesMapID()))
	{
		return false;
	}
	CWorldTile* worldTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(transport->GetDesMapID());
	if (NULL == worldTile)
		return false;
	CResMgr* pResMgr = worldTile->GetCResMgr();
	CTargetRes* target = pResMgr->GetTarget(transport->GetNtargetID());
	if (NULL == target)
	{
		return false;
	}
	TransportArr.push_back(target);
	bool ret = false;
	if (transport->GetDesMapID() == m_nEndMapId)
	{//找到了
		weight += sqrt((m_endx - target->GetPosX())*(m_endx - target->GetPosX())
			+(m_endy - target->GetPosY())*(m_endy - target->GetPosY()));
		if (CrossMapIdArr.size() < m_nMinMapCross || weight < mfMinWeight)
		{
			mTransportArr.clear();
			mfMinWeight = weight;
			m_nMinMapCross = CrossMapIdArr.size();
			for (int i = 0; i < TransportArr.size(); ++i)
			{
				mTransportArr.push_back(TransportArr[i]);
			}
			ret = true;
		}
	}
	else
	{
		CrossMapIdArr.push_back(transport->GetDesMapID());
		int tranportCount = 0;
		for (int i = 0; i < pResMgr->GetTransportCount();++i)
		{
			CTransportResBase* pRes = pResMgr->Transport(i);
			if (pRes->IsTransport())
			{
				if (tranportCount >= target->GetPFWeightArr().size())
				{
					continue;
				}
				if (-1 == target->GetPFWeightArr()[tranportCount])
				{
					continue;
				}
 				CTransportRes* newTransport = (CTransportRes*)pRes;
				float localWeight = weight;
				localWeight += target->GetPFWeightArr()[tranportCount];
				bool bContinue = false;
				for (int x = 0; x < CrossMapIdArr.size();++x)
				{
					if (CrossMapIdArr[x] == newTransport->GetDesMapID())
					{
						bContinue = true;
						break;
					}
				}
				if (bContinue)
				{
					continue;
				}
				TransportArr.push_back(pRes);
				if (GetValidPathWeight(localWeight,TransportArr,CrossMapIdArr))
				{
					ret = true;
				}
				TransportArr.pop_back();
				++tranportCount;
			}
		}
		CrossMapIdArr.pop_back();
	}
	TransportArr.pop_back();
	return ret;
}

bool CrossMapPF::UpdateAfterTileLoad()
{
	if (!m_bActive)
	{
		return false;
	}
	++m_nMapCross;
	float endx,endy;
	if (m_nMapCross*2 >= mTransportArr.size())
	{
		endx = m_endx;
		endy = m_endy;
		m_bActive = false;
	}
	else
	{
		CTransportResBase* pRes = mTransportArr[m_nMapCross*2];
		endx = pRes->GetPosX();
		endy = pRes->GetPosY();
	}
	if( theApp->GetPlayerMgr()->GetMe())
		theApp->GetPlayerMgr()->MoveRoleTo(endx,endy,true,true);
	return true;
}

int CrossMapPF::GetMapLevel( int MapId )
{
	CWorldTile* pWorldTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(MapId);
	if (pWorldTile)
	{
		return pWorldTile->GetMinLevel();
	}
	return -1;
}

bool CrossMapPF::CrossMapPathEvaluation( int startMapId,int endMapId,int& nPathLength )
{

	m_nPlayerLevel = thePlayerRole.GetLevel();
	if (m_nPlayerLevel < GetMapLevel(endMapId))
	{
		return false;
	}
	Reset();
	m_nEndMapId = endMapId;
	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(startMapId);
	CResMgr* pResMgr = pTile->GetCResMgr();
	for (int i = 0; i < pResMgr->GetTransportCount();++i)
	{
		CTransportResBase* pRes = pResMgr->Transport(i);
		if (pRes->IsTransport())
		{
			float weight = 0.f;
			std::vector<CTransportResBase*>			localTransportArr;
			localTransportArr.push_back(pRes);
			std::vector<int>			localMapIdArr;
			localMapIdArr.push_back(startMapId);
			GetValidPathWeight(weight,localTransportArr,localMapIdArr);
		}
	}
	if (mTransportArr.size() != 0)
	{
		nPathLength = mTransportArr.size();
		return true;
	}
	return false;

}