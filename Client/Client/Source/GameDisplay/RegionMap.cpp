#include "MeTerrain/stdafx.h"
#include <assert.h>

#include "tga.h"
#include "include/RegionMap.h"
#include "MeUi/UIPicture.h"
#include "gamemain.h"
#include "Player.h"
#include "playermgr.h"
#include "MeUi/UiManager.h"
#include "CfgFileLoader.h"
#include "ui/NpcChatDialogBox.h"
#include "ui/LoadMap.h"
#include "ui/Guild_Pic.h"
#include <math.h>
#include "chatcheck.h"
#include "color_config.h"
#include "MeFont/MeFont.h"
#include "XmlStringLanguage.h"
#include "MotionBillBoard.h"
#include "ui/FriendDlg.h"
#include "PathDirection.h"
#include "CrossMapPF.h"
#include "ui/AllNpcList.h"
#include "core/Name.h"
#include "GameSetting.h"
#include "Cfg.h"
#include "MeFont/MeFontSystem.h"

extern CHeroGame* theApp;
static CPlayerMgr::SNpcQuestInfo* gs_pSelNpcInfo = NULL;
CRegionMap gs_RegionMap;
int const ICON_RENDER_SIZE = 16;
#define MINIMAPRADIUS  88
const DWORD g_refreshInterval = 500;
extern int  g_nsrcPixelEdgeLength;

CRegionMap* GetRegionMap()
{
	return &gs_RegionMap;
}
//
CRegionMap::CRegionMap():
	nTargetFrameIndex(0)
	{
		guardfunc;


		m_pNpcCursorOn		= NULL;
		m_ShowTeamTip		= false;
		m_bUpdateStableImage = true;
		m_RegionStableImageIndex = -1;
		m_nRegionMapId	= -1;
		m_hMonsterDC		= NULL;
		m_nMonsterFont		= -1;
		unguard;
	}

	CRegionMap::~CRegionMap()
	{
		guardfunc;
		unguard;
	}


	BOOL CRegionMap::AddMark( Mark* pMark )
	{
		guardfunc;
		for( int nMark = 0; nMark < eMaxMark; nMark++ )
		{
			if( m_marks[nMark].dwLife == 0 )
			{
				m_marks[nMark] = *pMark;
				return TRUE;
			}
		}
		return FALSE;
		unguard;
	}




	void CRegionMap::RenderRegionMap( RECT rcWindow,RECT rcSrc,int nMapId, float nSelectedPosX, float nSelectedY,float fPixelPerRealDis,int xPixelOffset,int yPixelOffset )
	{
		guardfunc;
		CWorldTile* worldTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapId);
		int texture = worldTile->GetRegionMapId();
		if (texture == -1)
		{
			if(!worldTile->LoadRegionMap())
			{
				return;
			}
			texture = worldTile->GetRegionMapId();
		}

		LPDIRECT3DTEXTURE9 pTexture = (LPDIRECT3DTEXTURE9)GetEngine()->GetTextureManager()->GetTexture(texture)->GetData();
		theControlPictureManager.BitBlt2(pTexture,&rcWindow,&rcSrc,0xffffffff,0,eZWriteDisable);
// 		GetDrawer()->Blt( 
// 			texture,
// 			&rcWindow, 
// 			&rcSrc,
// 			&rcWindow, 
// 			g_nsrcPixelEdgeLength, 
// 			g_nsrcPixelEdgeLength,
// 			0, 0xffffffff,
// 			eZWriteDisable);
		DrawImageOnRegionMap(rcWindow,rcSrc,nMapId,nSelectedPosX,nSelectedY,fPixelPerRealDis,xPixelOffset,yPixelOffset);
		return;
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////




		unguard;	
	}




	BOOL CRegionMap::MarkNpcPosByID( int nNpcID )
	{
		guardfunc;
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(nNpcID);
		if (!pInfo)
		{
			return FALSE;
		}
		Mark mark;
		mark.x = pInfo->_mapX;
		mark.y = pInfo->_mapY;
		mark.dwBornTime = HQ_TimeGetTime();
		mark.dwLife = 4000;
		strcpy( mark.szText, Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
		AddMark( &mark  );
		return TRUE;
		unguard;
	}




#include "ShowScreenText.h"




	void CRegionMap::AddRegionMapImage( int nImage,NpcCoordInfo* pInfo ,GameObjectId nPlayerId)
	{
		RegionMapImage mapImg;
		mapImg.nImageType = nImage;
		mapImg.pInfo = pInfo;
		mapImg.nPlayerId = nPlayerId;
		if (nImage == eImage_YellowGanTanHao || nImage == eImage_WhiteGanTanHao || nImage == eImage_YellowWenHao || nImage == eImage_WhiteWenHao)
		{
			m_currRegionMapImageList.push_front(mapImg);
		}
		else
		{
			m_currRegionMapImageList.push_back(mapImg);
		}

	}

	void CRegionMap::DrawImageOnRegionMap( RECT rcWindow,RECT rcSrc,int nMapId, float nRoleX, float nRoleY ,float fPixelPerRealDis,int xPixelOffset,int yPixelOffset)
	{
		char tip[256];
		tip[0] = '\0';
		Image* pImage = NULL;
		if (m_bUpdateStableImage || m_nRegionMapId != nMapId)
		{
			m_bUpdateStableImage = false;
			m_nRegionMapId = nMapId;
			m_currRegionMapImageList.clear();
			std::vector<NpcCoordInfo>& npcMap = NpcCoord::getInstance()->getNpcVec();
			for( int i=0; i<npcMap.size(); ++i )
			{
				NpcCoordInfo* pInfo = &npcMap[i];
				if(!pInfo->_miniShow)
				{
					continue;
				}
				if(pInfo->_bPFPossible )
				{
					int nImageType = GetImageMap(pInfo->_nType);
					if(pInfo->_bNpc)
					{
						if (nMapId !=  pInfo->_mapId)
						{
							continue;
						}
						int nShowType = s_CUI_ID_FRAME_AllNpcList.GetShowType();
						if (nShowType & CUI_ID_FRAME_AllNpcList::Npc_TaskNpc)
						{
							int nNpcTipsType = theApp->GetPlayerMgr()->UpdateNpcTipsType( pInfo );
							switch( nNpcTipsType )
							{
							case CPlayerMgr::eNpcTips_HaveQuest:
								nImageType = eImage_YellowGanTanHao;
								break;
							case CPlayerMgr::eNpcTips_HaveQuestNotNow:
								nImageType = eImage_WhiteGanTanHao;
								break;
							case CPlayerMgr::eNpcTips_QuestDone:
								nImageType = eImage_YellowWenHao;
								break;
							case CPlayerMgr::eNpcTips_QuestNotDone:
								nImageType = eImage_WhiteWenHao;
								break;
							case CPlayerMgr::eNpcTips_CampBattleS://旗帜随军占领
								nImageType = eImage_CampBattleS;
								break;
							case CPlayerMgr::eNpcTips_CampBattleT://旗帜唐军占领
								nImageType = eImage_CampBattleT;
								break;
							case CPlayerMgr::eNpcTips_CampBattleZL://旗帜无人能占领
								nImageType = eImage_CampBattleZL;
								break;
							default:
								;
							}
						}
					}
					else
					{
						if ((gCfg.GetPrimaryMapId(nMapId) != pInfo->_mapId) || !pInfo->_bMask)//不会出现在区域地图的采集物，物品等等。
						{
							continue;
						}
						nImageType = eImage_Monster;
					}
					if (!IsMatchShowOption(nImageType))
					{
						continue;
					}
					AddRegionMapImage(nImageType,pInfo);
				}
			}
			m_RegionStableImageIndex = m_currRegionMapImageList.size() - 1;
		}

		CWorldTile* currTile = CURRENTTILE;
		CWorldTile* pShowTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapId);
		m_pNpcCursorOn		= NULL;
		m_ShowTeamTip		= false;
		Image* pImageCursorOn = NULL;
		for(std::list<RegionMapImage>::iterator iter = m_currRegionMapImageList.begin();  iter != m_currRegionMapImageList.end(); ++iter)
		{
			RegionMapImage* pMapImg = &(*iter);
			pImage = &m_images[pMapImg->nImageType];
			RECT rcDst;
			RECT rcImageSrc = {0, 0, pImage->nWidth, pImage->nHeight};
			Vector2 ptrlt((xPixelOffset + pMapImg->GetX())*fPixelPerRealDis - rcSrc.left,(yPixelOffset + pMapImg->GetY())*fPixelPerRealDis - (g_nsrcPixelEdgeLength - rcSrc.bottom));
			rcDst.left = rcWindow.left + ptrlt.x-pImage->nWidth/2;
			rcDst.right = rcDst.left + pImage->nWidth;
			rcDst.top = rcWindow.bottom - ptrlt.y-pImage->nHeight/2;
			rcDst.bottom = rcDst.top+pImage->nHeight;
			if (IsOutSide(rcWindow,rcDst))
			{
				continue;
			}
			if (m_strTargetNpc== pMapImg->GetName())
			{
				Image* pTargetImage = &m_images[eImage_Target];

				RECT targetSrc = {0, 0, pTargetImage->nWidth, pTargetImage->nHeight};;
				theControlPictureManager.BitBlt(&pTargetImage->nTextureID,NULL,&rcDst,&targetSrc,0xffffffff,0,0);
// 				GetDrawer()->Blt( pTargetImage->nTextureID, &rcDst, &targetSrc, &rcDst, pTargetImage->nWidth, pTargetImage->nHeight, 0,0xffffffff, 0 );
			}
			theControlPictureManager.BitBlt(&pImage->nTextureID,NULL,&rcDst,&rcImageSrc,0xeeffffff,0,0);
// 			GetDrawer()->Blt( pImage->nTextureID, &rcDst, &rcImageSrc, &rcDst, pImage->nWidth, pImage->nHeight, 0,0xeeffffff, 0 );
			if (pMapImg->nImageType == eImage_Monster && s_CUI_ID_FRAME_AllNpcList.IsShowAllMap() == false )
			{//怪物需要显示名字, 但是 allmap（小地图）显示的时候不显示怪物名称
				DWORD color = Color_Config.getColor(CC_MonsterTip_Strong);
				if (thePlayerRole.GetInfluence() != CampDefine::NoneCamp)
				{
					if (thePlayerRole.GetInfluence() == pMapImg->pInfo->_campType)
					{
						//我方
						color = Color_Config.getColor(CC_PlayerNormal);
					}
					else
					{
						//敌方，红名
						color = Color_Config.getColor(CC_PlayerEnemy);
					}
				}

				ItemDefine::SMonster* pMonster = GettheItemDetail().GetMonsterByName(pMapImg->GetName());
				if (pMonster)
				{
					char cMonsterName[256] = {0};
					int nStringId = eClient_MonsterTip_Normal;
// 					int col = Color_Config.getColor(CC_MonsterTip_Strong);
					if (pMonster->stMonsterType == eMT_LeaderMonster)
					{
						nStringId = eClient_MonsterTip_Enhance;
// 						col = Color_Config.getColor(CC_MonsterTip_Strong);
					}
					else if (pMonster->stMonsterType == eMT_BossMonster)
					{
						nStringId = eClient_MonsterTip_Leader;
// 						col = Color_Config.getColor(CC_MonsterTip_Strong);
					}

					if (pShowTile->GetMapType() == 0)
					{
						sprintf_s(cMonsterName,theXmlString.GetString(eClient_MonsterNameOnRegionMap),theXmlString.GetString(nStringId),pMapImg->GetName(),pMapImg->GetLevel());
					}
					else
					{//副本怪物等级会根据人物或者组队等级变化，客户端并不知道这个变化规则，所以等级不再显示
						sprintf_s(cMonsterName,theXmlString.GetString(eClient_MonsterNameOnRegionMap1),theXmlString.GetString(nStringId),pMapImg->GetName());
					}
					std::wstring wideStr = Common::_tstring::toWideString(cMonsterName);
					if (m_nMonsterFont == -1)
					{
						m_nMonsterFont = FontSystem::CreateFont( m_nFontNameOnRegionMap,
							m_nFontSizeOnRegionMap, 0, FW_NORMAL,
							1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, &m_hMonsterDC);
					}
					int nStrWidth = FontSystem::GetTextWidth(m_nMonsterFont,wideStr, 0, wideStr.length(),false );

					FontSystem::DrawText(  cMonsterName,
						rcWindow.left + ptrlt.x - nStrWidth/2
						, rcDst.top - m_nFontSizeOnRegionMap
						, DT_NOCLIP,
						color, m_nMonsterFont );
				}
			}
			
			POINT ptMouse = theUiManager.m_ptMoust;
			if(PtInRect(&rcDst, ptMouse) )
			{
				m_pNpcCursorOn = pMapImg;
				pImageCursorOn = pImage; 
			}
		}

		std::vector<TeamInfo>::iterator iter = thePlayerRole.GetTeamInfo().begin();
		for (;iter != thePlayerRole.GetTeamInfo().end(); ++iter)
		{
			TeamInfo& info = *iter;
			CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
			if (!pMe || info.szName == pMe->GetName())
			{
				continue;
			}
			int nTeamMapId = EctypeId2MapId(info.nMapID);
			if (nTeamMapId ==  nMapId)
			{
				pImage = &m_images[eImage_Teammate];
				RECT rcDst;
				RECT rcImageSrc =	{					0, 0, pImage->nWidth, pImage->nHeight				};
				Vector2 ptrlt((xPixelOffset + info.fx)*fPixelPerRealDis - rcSrc.left,(yPixelOffset + info.fy)*fPixelPerRealDis- (g_nsrcPixelEdgeLength - rcSrc.bottom));
				rcDst.left = rcWindow.left + ptrlt.x-pImage->nWidth/2;
				rcDst.right = rcDst.left + pImage->nWidth;
				rcDst.top = rcWindow.bottom - ptrlt.y-pImage->nHeight/2;
				rcDst.bottom = rcDst.top+pImage->nHeight;
				if (IsOutSide(rcWindow,rcDst))
				{
					continue;
				}

				theControlPictureManager.BitBlt(&pImage->nTextureID,NULL,&rcDst,&rcImageSrc,0xeeffffff,0,0);
// 				GetDrawer()->Blt( pImage->nTextureID, &rcDst, &rcImageSrc, &rcDst, pImage->nWidth, pImage->nHeight, 0,0xeeffffff, 0 );
				POINT ptMouse = theUiManager.m_ptMoust;
				if(PtInRect(&rcDst, ptMouse) )
				{
					m_pNpcCursorOn = NULL;
					pImageCursorOn = pImage; 
					if (s_CUI_ID_FRAME_AllNpcList.IsTipActive())
					{
						m_ShowTeamTip = true;
						MeSprintf_s( tip,sizeof(tip)/sizeof(char) - 1 ,"%s(%ld,%ld)",info.szName.c_str(), ZnFloor2Int(info.fx), ZnFloor2Int(info.fy));
					}
				}
			}
		}

		//draw target
		if (m_pNpcCursorOn  )
		{
			if (s_CUI_ID_FRAME_AllNpcList.IsTipActive())
			{			
                if((pShowTile->GetMapType() == 0) && m_pNpcCursorOn->IsMonster() && m_pNpcCursorOn->GetLevel() > 0 )
                {
                    MeSprintf_s( tip,sizeof(tip)/sizeof(char) - 1, "%sLv%d(%ld,%ld)",m_pNpcCursorOn->GetName(), m_pNpcCursorOn->GetLevel(),
                        ZnFloor2Int(m_pNpcCursorOn->GetX()), ZnFloor2Int(m_pNpcCursorOn->GetY()));	
                }
                else
                {
                    MeSprintf_s( tip,sizeof(tip)/sizeof(char) - 1, "%s(%ld,%ld)",m_pNpcCursorOn->GetName(),
                        ZnFloor2Int(m_pNpcCursorOn->GetX()), ZnFloor2Int(m_pNpcCursorOn->GetY()));	
                }
			}
			Image* pTargetImage = &m_images[eImage_Target];
			RECT targetSrc = {					0, 0, pTargetImage->nWidth, pTargetImage->nHeight				};
			RECT rcDst;
			Vector2 ptrlt((xPixelOffset + m_pNpcCursorOn->GetX())*fPixelPerRealDis - rcSrc.left,(yPixelOffset + m_pNpcCursorOn->GetY())*fPixelPerRealDis- (g_nsrcPixelEdgeLength - rcSrc.bottom));
			rcDst.left = rcWindow.left + ptrlt.x-pImageCursorOn->nWidth/2;
			rcDst.right = rcDst.left + pImageCursorOn->nWidth;
			rcDst.top = rcWindow.bottom - ptrlt.y-pImageCursorOn->nHeight/2;
			rcDst.bottom = rcDst.top+pImageCursorOn->nHeight;
			if (!IsOutSide(rcWindow,rcDst))
			{
				theControlPictureManager.BitBlt(&pTargetImage->nTextureID,NULL,&rcDst,&targetSrc,0xffffffff,0,0);
// 				GetDrawer()->Blt( pTargetImage->nTextureID, &rcDst, &targetSrc, &rcWindow, pTargetImage->nWidth, pTargetImage->nHeight, 0,0xffffffff, 0 );
				RECT rcImageSrc =	{					0, 0, pImageCursorOn->nWidth, pImageCursorOn->nHeight				};
				theControlPictureManager.BitBlt(&pImageCursorOn->nTextureID,NULL,&rcDst,&rcImageSrc,0xeeffffff,0,0);
// 				GetDrawer()->Blt( pImageCursorOn->nTextureID, &rcDst, &rcImageSrc, &rcDst, pImageCursorOn->nWidth, pImageCursorOn->nHeight, 0,0xeeffffff, 0 );
			}
		}


		if (currTile && (currTile->GetMapId() == nMapId))
		{
			{
				pImage = &m_images[eImage_Me];
				RECT rcImageSrc =		{			0, 0, pImage->nWidth, pImage->nHeight		};
				GetRcSrcForMe(rcImageSrc);
				CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
				if( pMe )
				{
					RECT rcDst;
					Vector2 ptrlt((xPixelOffset + pMe->GetPos().x)*fPixelPerRealDis - rcSrc.left,(yPixelOffset + pMe->GetPos().y)*fPixelPerRealDis- (g_nsrcPixelEdgeLength - rcSrc.bottom));
					rcDst.left = rcWindow.left + ptrlt.x-(rcImageSrc.right- rcImageSrc.left)/2;
					rcDst.right = rcDst.left + (rcImageSrc.right- rcImageSrc.left);
					rcDst.top = rcWindow.bottom - ptrlt.y-(rcImageSrc.bottom- rcImageSrc.top)/2;
					rcDst.bottom = rcDst.top+(rcImageSrc.bottom- rcImageSrc.top);
					if (!IsOutSide(rcWindow,rcDst))
					{
						theControlPictureManager.BitBlt(&pImage->nTextureID,NULL,&rcDst,&rcImageSrc,0xeeffffff,0,0);
// 						GetDrawer()->Blt( pImage->nTextureID, &rcDst, &rcImageSrc, &rcDst, pImage->nWidth, pImage->nHeight, 0,0xeeffffff, 0 );
					}
				}
			}

			//宠物
			{
				pImage = &m_images[eImage_PetAnimal];
				RECT rcImageSrc = {0, 0, pImage->nWidth, pImage->nHeight};
				CPlayer *pPet = NULL;
				if (theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->HavePet())
				{	
					pPet = theHeroGame.GetPlayerMgr()->FindByID(theHeroGame.GetPlayerMgr()->GetMe()->GetPetID());
				}
				if (pPet)
				{
					RECT rcDst;
					Vector2 ptrlt((xPixelOffset + pPet->GetPos().x)*fPixelPerRealDis - rcSrc.left,(yPixelOffset + pPet->GetPos().y)*fPixelPerRealDis- (g_nsrcPixelEdgeLength - rcSrc.bottom));
					rcDst.left = rcWindow.left + ptrlt.x-(rcImageSrc.right- rcImageSrc.left)/2;
					rcDst.right = rcDst.left + (rcImageSrc.right- rcImageSrc.left);
					rcDst.top = rcWindow.bottom - ptrlt.y-(rcImageSrc.bottom- rcImageSrc.top)/2;
					rcDst.bottom = rcDst.top+(rcImageSrc.bottom- rcImageSrc.top);
					if (!IsOutSide(rcWindow,rcDst))
					{
						theControlPictureManager.BitBlt(&pImage->nTextureID,NULL,&rcDst,&rcImageSrc,0xeeffffff,0,0);
					}
				}
			}

			//镖车、受保护怪
			{
				pImage = &m_images[eImage_ProtectMonster];
				RECT rcImageSrc =		{0, 0, pImage->nWidth, pImage->nHeight};
				D3DXVECTOR3* pPosition = NULL;
				if (theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe())
				{
					pPosition = &(theHeroGame.GetPlayerMgr()->GetMe()->GetProtectPetPosition());
				}

				if (pPosition)
				{
					RECT rcDst;
					Vector2 ptrlt((xPixelOffset + pPosition->x)*fPixelPerRealDis - rcSrc.left,(yPixelOffset + pPosition->y)*fPixelPerRealDis- (g_nsrcPixelEdgeLength - rcSrc.bottom));
					rcDst.left = rcWindow.left + ptrlt.x-(rcImageSrc.right- rcImageSrc.left)/2;
					rcDst.right = rcDst.left + (rcImageSrc.right- rcImageSrc.left);
					rcDst.top = rcWindow.bottom - ptrlt.y-(rcImageSrc.bottom- rcImageSrc.top)/2;
					rcDst.bottom = rcDst.top+(rcImageSrc.bottom- rcImageSrc.top);
					if (!IsOutSide(rcWindow,rcDst))
					{
						theControlPictureManager.BitBlt(&pImage->nTextureID,NULL,&rcDst,&rcImageSrc,0xeeffffff,0,0);
					}
				}
			}

			if (CPathDirection::Instance()->IsActive())
			{
				pImage = &m_images[eImage_MiniMapPath];
				RECT rcImageSrc =		{			0, 0, pImage->nWidth, pImage->nHeight		};
				for (int i = CPathDirection::Instance()->GetPathDirBegin(); i < CPathDirection::Instance()->GetPathDirEnd(); ++i)
				{
					if (i%2 != 0)
					{
						continue;
					}
					RECT rcDst;
					float posx,posy;
					CPathDirection::Instance()->GetDirectionPos(i,posx,posy);
					Vector2 ptrlt((xPixelOffset + posx)*fPixelPerRealDis - rcSrc.left,(yPixelOffset + posy)*fPixelPerRealDis- (g_nsrcPixelEdgeLength - rcSrc.bottom));
					rcDst.left = rcWindow.left + ptrlt.x-(rcImageSrc.right- rcImageSrc.left)/2;
					rcDst.right = rcDst.left + (rcImageSrc.right- rcImageSrc.left);
					rcDst.top = rcWindow.bottom - ptrlt.y-(rcImageSrc.bottom- rcImageSrc.top)/2;
					rcDst.bottom = rcDst.top+(rcImageSrc.bottom- rcImageSrc.top);
					if (!IsOutSide(rcWindow,rcDst))
					{
						theControlPictureManager.BitBlt(&pImage->nTextureID,NULL,&rcDst,&rcImageSrc,0xeeffffff,0,0);
// 						GetDrawer()->Blt( pImage->nTextureID, &rcDst, &rcImageSrc, &rcDst, pImage->nWidth, pImage->nHeight, 0,0xeeffffff, 0 );
					}
				}
			}

		}

		//////////////////////////////////////////////////////////////////////////闪烁
		if (m_strTargetNpc.length() == 0)
		{
			int iLightCircle = m_images[eImage_TargetInRegionMap].nTextureID;
			if (nRoleX > 0 && nRoleY > 0 && iLightCircle != -1)
			{
				static DWORD NowTime = 0;
				static RECT rcDst;
				static RECT rcImageSrc = {0,0,m_images[eImage_TargetInRegionMap].nWidth,m_images[eImage_TargetInRegionMap].nHeight};
				const int TargetInRegionMapWidth = m_images[eImage_TargetInRegionMap].nWidth/4;
				const int TargetInRegionMapHeight = m_images[eImage_TargetInRegionMap].nHeight/4;
				if(::GetTickCount() - NowTime > 75)
				{
					NowTime = ::GetTickCount();

					int nXIndex = nTargetFrameIndex%4;
					int nYIndex = nTargetFrameIndex/4;
					rcImageSrc.left = nXIndex*TargetInRegionMapWidth;
					rcImageSrc.right = (nXIndex + 1)*TargetInRegionMapWidth;
					rcImageSrc.top = nYIndex*TargetInRegionMapHeight;
					rcImageSrc.bottom = (nYIndex+1)*TargetInRegionMapHeight;
					nTargetFrameIndex++;
					if (nTargetFrameIndex >= 16)
					{
						nTargetFrameIndex = 0;
					}
				}

 				Vector2 ptrlt((xPixelOffset + nRoleX)*fPixelPerRealDis - rcSrc.left,(yPixelOffset + nRoleY)*fPixelPerRealDis- (g_nsrcPixelEdgeLength - rcSrc.bottom));
				rcDst.left = rcWindow.left + ptrlt.x-16;
				rcDst.right = rcWindow.left + ptrlt.x+16;
				rcDst.top = rcWindow.bottom - ptrlt.y-16;
				rcDst.bottom = rcWindow.bottom - ptrlt.y+16;
				if (!IsOutSide(rcWindow,rcDst))
				{
					theControlPictureManager.BitBlt(&iLightCircle,NULL,&rcDst,&rcImageSrc,0xcfffffff,0,0);
// 					GetDrawer()->Blt(
// 						iLightCircle,
// 						&rcDst,
// 						&rcImageSrc,
// 						&rcDst,
// 						m_images[eImage_TargetInRegionMap].nWidth,
// 						m_images[eImage_TargetInRegionMap].nHeight,
// 						0.0f,
// 						0xcfffffff, 0 );
				}
			}
		}

		if (tip[0] != '\0' && (m_pNpcCursorOn || m_ShowTeamTip))
		{
			RenderTip( rcWindow,tip);
		}
	}



	bool CRegionMap::IsMatchShowOption( int nImageType )
	{
		int nShowType = s_CUI_ID_FRAME_AllNpcList.GetShowType();
		if (nShowType & CUI_ID_FRAME_AllNpcList::Npc_TaskNpc)
		{
			if (nImageType >= eImage_YellowGanTanHao && nImageType <= eImage_WhiteWenHao)
			{
				return true;
			}
		}
		Image* pImage = &m_images[nImageType];

		if (pImage->m_NpcType == 0//不检查过滤标识
			|| (1 << (pImage->m_NpcType - 1)) & nShowType)
		{
			return true;
		}
		return false;
	}

	bool CRegionMap::IsOutSide( RECT& rcWindow,RECT& rcDst )
	{
		Vector2 center((rcDst.top+rcDst.bottom)/2, (rcDst.left+rcDst.right )/2);
		return ( center.x >  rcWindow.bottom || center.x < rcWindow.top || center.y > rcWindow.right || center.y < rcWindow.left	);
	}
	float CRegionMap::RegionMapImage::GetX()
	{
		if (pInfo)
		{
			return pInfo->_mapX;
		}
		else
		{
			assert(-1 != nPlayerId);
// 			std::map< short, CPlayer* >& playArr = theApp->GetPlayerMgr()->m_mapPlayers;
			CPlayer* pPlayer = theApp->GetPlayerMgr()->FindByID(nPlayerId);
			if (!pPlayer)
			{
				return 0;
			}
			float x =0;
			pPlayer->GetPos(&x,NULL,NULL);
			return x;
		}
		return 0;
	}

	float CRegionMap::RegionMapImage::GetY()
	{
		if (pInfo)
		{
			return pInfo->_mapY;
		}
		else
		{
			assert(-1 != nPlayerId);
			CPlayer* pPlayer = theApp->GetPlayerMgr()->FindByID(nPlayerId);
			if (!pPlayer)
			{
				return 0;
			}
			float y =0;
			pPlayer->GetPos(NULL,&y,NULL);
			return y;
		}
		return 0;

	}

	const char* CRegionMap::RegionMapImage::GetName()
	{
		if (pInfo)
		{
			static std::string narrowString;
			narrowString = Common::_tstring::toNarrowString(pInfo->_szName.c_str());
			return narrowString.c_str();
		}
		else
		{
			assert(-1 != nPlayerId);
			CPlayer* pPlayer = theApp->GetPlayerMgr()->FindByID(nPlayerId);
			if (!pPlayer)
			{
				return NULL;
			}
			return pPlayer->GetName();
		}
		return NULL;

	}

    int CRegionMap::RegionMapImage::GetLevel()
    {
        if( pInfo )
        {
            return pInfo->_level;
        }
        else
        {
            if( -1 == nPlayerId )
                return -1;

			CPlayer* pPlayer = theApp->GetPlayerMgr()->FindByID(nPlayerId);
            if( !pPlayer )
                return -1;
            return pPlayer->GetLevel();
        }
    }

    bool CRegionMap::RegionMapImage::IsMonster()
    {
        if( pInfo )
        {
            return !pInfo->_bNpc;
        }
        else
        {
            if( -1 == nPlayerId )
                return false;

			CPlayer* pPlayer = theApp->GetPlayerMgr()->FindByID(nPlayerId);
            if( !pPlayer )
                return false;
            return pPlayer->IsMonster();
        }
    }
