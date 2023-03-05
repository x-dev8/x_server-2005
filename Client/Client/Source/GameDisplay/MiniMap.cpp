#include "MeTerrain/stdafx.h"
#include <assert.h>
#include "tga.h"
#include "ui/MiniMapUI.h"
#include "include/MiniMap.h"
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
#include "MapConfig.h"
#include "wsCamera.h"
#include "MeFont/MeFontSystem.h"
#include "RapidXml/MeRapidXml.h"
#include "ScreenInfoManager.h"
#include "Pet.h"
#include "PositionInfo.h"
#include "..\GameUI\AutoAttackSet.h"
//#include "..\Kwamemap.h"
#include "../GameUI/FindTheRoad.h"

extern CHeroGame* theApp;
static CPlayerMgr::SNpcQuestInfo* gs_pSelNpcInfo = NULL;
CAdvancedMiniMap gs_AdvancedMiniMap;
int const ICON_RENDER_SIZE = 16;
#define MINIMAPRADIUS  88
const DWORD g_refreshInterval = 500;
CAdvancedMiniMap::Image CAdvancedMiniMap::m_images[eImage_Max];
int CAdvancedMiniMap::m_nFontSizeOnRegionMap = 20;
char CAdvancedMiniMap::m_nFontNameOnRegionMap[256] = {0};

CAdvancedMiniMap* GetAdvancedMiniMap()
{
	return &gs_AdvancedMiniMap;
}
const char* miniIcon[CAdvancedMiniMap::eImage_Max] =
{
	"Target",
	"TargetInRegionMap",
	"Monster",
	"DeadMonster",
	"Npc",
	"NpcDirectLoocked",
	"Restore",
	"Weapon",
	"Ring",
	"Dress",
	"Material",
	"Transport",
	"Pet",
	"Storage",
	"Star",
	"MakeItem",
	"Active",
	"RepeatTask",
	"YuanBao",
	"Change",
	"GongXun",
	"MingWang",
	"ShiZhuang",
	"WenDa",
	"JiNeng",
	"PeiJian",
	"ShiWu",
	"YiZhan",
	"ZaHuo",
	"FenJie",
	"QianZhuang",
	"YiXing",			// 移星
	"TeXiu",			// 特修
	"KeepWord0",			// 保留字0
	"KeepWord1",			// 保留字1
	"KeepWord2",			// 保留字2
	"KeepWord3",			// 保留字3
	"KeepWord4",			// 保留字4
	"KeepWord5",			// 保留字5
	"KeepWord6",			// 保留字6
	"KeepWord7",			// 保留字7
	"KeepWord8",			// 保留字8
	"KeepWord9",			// 保留字9
	"NpcDirect",
	"MouseDirect",
	"MiniMapPath",
	"YellowGanTanHao",
	"WhiteGanTanHao",
	"YellowWenHao",
	"WhiteWenHao",
	"RoleArrow",
	"NpcPosMark",
	"Player",
	"Guild",
	"Friend",
	"Teammate",
	"Enemy",
	"Camera",
	"Me",
	"PetAnimal",//宠物
	"ProtectMonster",//受保护怪，镖车等
    "ZhangChangS",
    "ZhangChangT",
    "ZhangChangZL",
};
//
CAdvancedMiniMap::CAdvancedMiniMap()
{
	guardfunc;


	m_maxDimension	= 0;
	oldTexid		= -1;
	oldTile			= NULL;
	m_xPixelOffset	= 0;
	m_yPixelOffset	= 0;
	m_pPlayerCursorOn = NULL;
	m_ShowTeamTip		= false;
	m_lastRefreshTime = 0;
	m_pTargetPlayer = NULL;
	m_bInitialize	= false;
	m_texEdge = 1024;

	unguard;
}

CAdvancedMiniMap::~CAdvancedMiniMap()
{
	guardfunc;
	unguard;
}

void CAdvancedMiniMap::Destroy()
{
	guardfunc;

	for( int i = 0; i < eImage_Max; i++ )
	{
		if( m_images[i].nTextureID != -1 )
		{
			GetEngine()->GetTextureManager()->UnRegisterTexture( m_images[i].nTextureID );
			m_images[i].nTextureID = -1;
		}
	}
	m_ImageTypeList.clear();

	gs_pSelNpcInfo = NULL;
	m_bInitialize = false;
	unguard;
}

BOOL CAdvancedMiniMap::LoadImage( int nImage, const char* pszFilename ,const char* shortcut,const char* effect/*,const char* pTypeString*/,int type)
{
	guardfunc;
	if( nImage < 0 || nImage >= eImage_Max )
	{
		assert( false );
		return FALSE;
	}
	ITextureManager* pTextureMgr = GetEngine()->GetTextureManager();
	Image* pImage = &m_images[nImage];
	if (shortcut)
	{
		strcpy(pImage->shortcut,shortcut);
	}
	pImage->nWidth = MAPTEX_WIDTH;
	pImage->nHeight = MAPTEX_HEIGHT;
	pImage->m_NpcType = type;

	char fullname[MAX_PATH] = {0};
	MeSprintf_s(fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\%s", GetRootPath(), pszFilename);
	ControlPictureManager::S_Pic* pPic = theControlPictureManager.RegisterTexture(&pImage->nTextureID, fullname);
// 	if (pImage->nTextureID == -1)
// 	{
// 		char szDef[MAX_PATH] = {0};
// 		MeSprintf_s(szDef,sizeof(szDef)/sizeof(char) - 1, "%s\\data\\flag.tga", GetRootPath());
// 		pImage->nTextureID = GetEngine()->GetTextureManager()->RegisterTexture( szDef, FALSE ,TRUE);
// 	}
	if( pPic && pPic->m_TextureId != -1)
	{
		LPDIRECT3DTEXTURE9 pTexture = (LPDIRECT3DTEXTURE9)GetEngine()->GetTextureManager()->GetTexture(pPic->m_TextureId)->GetData();
		if(NULL != pTexture )
		{
			D3DSURFACE_DESC desc;
			pTexture->GetLevelDesc( 0, &desc );
			pImage->nWidth = desc.Width;
			pImage->nHeight = desc.Height;
		}
	}
	if (effect)
	{
		pImage->strEffectPath = effect;
	}
	return TRUE;
	unguard;
}

void CAdvancedMiniMap::LoadImages()
{
	guardfunc;
	CCfgFileLoader l;

	char fullname[MAX_PATH] = {0};
	MeSprintf_s(fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\config\\Minimap.config", GetRootPath());


	MeXmlDocument doc;
	if( !doc.LoadFile( fullname,TIXML_ENCODING_UTF8 ) )////////////////////////////?????????????
	{
		//			assert(false && "LoadMap读取文件失误");
	}
	m_ImageTypeList.clear();
	MeXmlElement* pProject = doc.FirstChildElement("Project");
	MeXmlElement* lpTypeRoot = pProject->FirstChildElement("MiniMapType");
	if (lpTypeRoot)
	{
		MeXmlElement* lpWord = lpTypeRoot->FirstChildElement("Track");
		while(lpWord)
		{
			SImageType type;
			lpWord->Attribute("Type",&type.m_NpcType);
			Common::_tstring typeString;
			typeString.fromUTF8(lpWord->Attribute("String"));
			type.strTypeString = typeString;			
			lpWord->Attribute("ShowOrder",&type.m_Order);
			InsertImageTypeByOrder(type);
			lpWord = lpWord->NextSiblingElement("Track");
		}
	}

	MeXmlElement *lpSortRoot = pProject->FirstChildElement("SortNpcType");
	if(lpSortRoot)
	{
		MeXmlElement *lpSort = lpSortRoot->FirstChildElement("SortNpc");
		while(lpSort)
		{
			SortNpcType mapType;
			Common::_tstring typeString;
			typeString.fromUTF8(lpSort->Attribute("SortName"));
			mapType.strType = typeString;

			Common::_tstring npcType;
			npcType.fromUTF8(lpSort->Attribute("NpcType"));
			std::string strSort = npcType;
			if(!strSort.empty())
			{
				std::string::size_type nSize = strSort.find(",");
				std::string::size_type nBegin = 0;
				std::string strValue;
				strValue.clear();
				if(nSize != std::string::npos)
				{
					while (nSize != std::string::npos)
					{
						strValue = strSort.substr(nBegin,nSize - nBegin);
						int nValue = 0;
						if(sscanf_s(strValue.c_str(),"%d",&nValue) == 1)
							mapType.vecSet.push_back(nValue);

						nBegin = nSize + 1;
						nSize = strSort.find(",",nBegin);
					}
				}
			
				strValue = strSort.substr(nBegin);
				int nValue = 0;
				if(sscanf_s(strValue.c_str(),"%d",&nValue) == 1)
					mapType.vecSet.push_back(nValue);
				
			}

			m_NpcSort.push_back(mapType);

			lpSort = lpSort->NextSiblingElement("SortNpc");
		}
	}

	MeXmlElement* lpIconRoot = pProject->FirstChildElement("MiniMapIcon");
	if(lpIconRoot)
	{
		MeXmlElement* lpWord = lpIconRoot->FirstChildElement("Icon");

		const char* szValue = NULL;
		while( lpWord )
		{
			szValue = lpWord->Attribute("Name");
			if( szValue )
			{
				int type = GetImageType(szValue);
				if (type != -1)
				{
					int nNpcType = -1;
					lpWord->Attribute("Type",&nNpcType);
					BOOL bLoadSucc = FALSE;
					bLoadSucc = LoadImage( type, lpWord->Attribute("File"),lpWord->Attribute("Shortcut"),lpWord->Attribute("Effect"),/*lpWord->Attribute("TypeString"),*/nNpcType );
				}
			}
			lpWord = lpWord->NextSiblingElement("Icon");
		}
	}

	MeXmlElement* lpFont = pProject->FirstChildElement("FontOnRegionMap");
	if (lpFont)
	{
		lpFont->QueryIntAttribute("FontSize",&m_nFontSizeOnRegionMap);
		const char* pszValue = lpFont->Attribute("Font");
		if (pszValue)
		{
			strcpy( m_nFontNameOnRegionMap, Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszValue).c_str()).c_str() );
		}
	}

	unguard;

}


BOOL CAdvancedMiniMap::Create( int nMapRealWidth, int nMapRealHeight, char* pszFilename )
{
	guardfunc;
	if (!m_bInitialize)
	{
		Destroy();
		m_bInitialize = true;
		LoadImages();
	}
	return TRUE;
	unguard;
}
/*
	首先解决把一张大图上的区域渲染到屏幕区域的问题，
	这里有几个问题，
	主角的坐标并不是总是位于窗口中心，

	假设，

	得到大图上的区域，
	这个是玩家的视野，
	不考虑缩放，
	只考虑大小，

	现在大图尺寸MapWidth,MapHeight
	主角坐标cx,cy
	主角视野SightWidth,SightHeight，
	渲染窗口尺寸WindowWidth,WindowHeight
	那么，
	主角看可以看见的区域是
	RECT cx-SightWidth/2,cy-SightHeight/2,cx+SightWidth,cy+SightHeight
	如果矩形左上角益处了地图大小
	则对视野大小进行裁减

	//
	npc icon的定位，
	设置一个算法，把一个map坐标的点mx,my换算成mapimage中的坐标imagex,imagey
	imagex = mx/m_nMapRealWidth*m_nMapImageWidth;
	然后再把imagex,imagey换算成渲染窗口中的坐标，windowx,windowy
	计算imagex,imagey相对于rcSight的偏移量，
	offsetx=imagex-rcSight.left
	offsetx乘以rcSight到rcWindow的缩放比例
	可以理解为，rcSight中的每一个像素，在rcWindow中都会进行缩放，
	那么，offset也会按照相同的比例进行缩放
	最终，
	windowx=rcWindow.left+offsetx*scale
*/
void CAdvancedMiniMap::GetImageWindowRect( RECT rcWindow,  int nImageType, int nImageX, int nImageY, RECT& rcDst , int nRoleX, int nRoleY, float fScale)
{
	guardfunc;
	Image* pImage = &m_images[nImageType];
	if(nImageType == eImage_Me)
	{
		rcDst.left	= rcWindow.left +  (rcWindow.right - rcWindow.left)/2 - pImage->nWidth /(4*4);
		rcDst.top	= rcWindow.top + (rcWindow.bottom - rcWindow.top)/2 - pImage->nHeight /(4*4);
		rcDst.right = rcDst.left + pImage->nWidth/(2*4) - 1;
		rcDst.bottom = rcDst.top + pImage->nHeight/(2*4) - 1;
	}
	else
	{
		if( nImageType == eImage_YellowGanTanHao || nImageType == eImage_WhiteGanTanHao || nImageType == eImage_YellowWenHao || nImageType == eImage_WhiteWenHao  )
		{
			rcDst.left	= rcWindow.left + (rcWindow.right - rcWindow.left)/2 + (nImageX - nRoleX * 0.5) * fScale *m_texEdge/m_maxDimension  - pImage->nWidth /2 * fScale;
			rcDst.top	= rcWindow.top + (rcWindow.bottom - rcWindow.top)/2 + (nRoleY* 0.5 - nImageY  ) * fScale *m_texEdge/m_maxDimension  - pImage->nHeight /2 * fScale;
			rcDst.right	= rcDst.left + pImage->nWidth - 1;
			rcDst.bottom = rcDst.top + pImage->nHeight - 1;
		}
		else
		{
			rcDst.left	= rcWindow.left + (rcWindow.right - rcWindow.left)/2 + (nImageX - nRoleX* 0.5) * fScale *m_texEdge/m_maxDimension  - ICON_RENDER_SIZE /2 * fScale;
			rcDst.top	= rcWindow.top + (rcWindow.bottom - rcWindow.top)/2 + (nRoleY* 0.5 - nImageY ) * fScale *m_texEdge/m_maxDimension  - ICON_RENDER_SIZE /2 * fScale;
			rcDst.right	= rcDst.left + ICON_RENDER_SIZE - 1;
			rcDst.bottom = rcDst.top + ICON_RENDER_SIZE - 1;
		}
	}
	unguard;
}
BOOL CAdvancedMiniMap::DrawTextUnderImage( RECT rcImage, const char* pszText, DWORD dwColor )
{
	guardfunc;
	char s[256];
	MeSprintf_s( s,sizeof(s)/sizeof(char) - 1, "%s", pszText );
	int nLength = strlen( s )*6+4;
	int x = (rcImage.right+rcImage.left)/2;
	int y = (rcImage.bottom);
	x -= nLength/2;
	FontSystem::DrawText( s, x, y, DT_NOCLIP, dwColor );
	return TRUE;
	unguard;
}

BOOL CAdvancedMiniMap::DrawImage( RECT rcWindow, int nImageType, 
					RECT& rcDst, bool target)
{
	guardfunc;
	Image* pImage = &m_images[nImageType];
	

	RECT rcSrc =
	{
		0, 0, pImage->nWidth, pImage->nHeight
		//0,0,16,16
	};
	float z = 0.13f;
	if( nImageType == eImage_Me  )
	{
		GetRcSrcForMe(rcSrc);
		z = 0.115f;
		DrawCameraImage(rcWindow);
	}
	if( target && nImageType != eImage_Me)
	{
		z = 0.11f;
		 
		Image* pTargetImage = &m_images[eImage_Target];

		RECT targetSrc = {					0, 0, pTargetImage->nWidth, pTargetImage->nHeight				};;
		theControlPictureManager.BitBlt(&pTargetImage->nTextureID,NULL,&rcDst,&targetSrc,0xffffffff,z,0);
// 		GetDrawer()->Blt( pTargetImage->nTextureID, &rcDst, &targetSrc, &rcWindow, pTargetImage->nWidth, pTargetImage->nHeight, z,0xffffffff, 0 );
		theControlPictureManager.BitBlt(&pImage->nTextureID,NULL,&rcDst,&rcSrc,0xffffffff,z,0);
// 		return GetDrawer()->Blt( pImage->nTextureID, &rcDst, &rcSrc, &rcWindow, pImage->nWidth, pImage->nHeight, z,0xffffffff, 0 );
	}
	else
	{
		theControlPictureManager.BitBlt(&pImage->nTextureID,NULL,&rcDst,&rcSrc,0xffffffff,z,0);
// 		return GetDrawer()->Blt( pImage->nTextureID, &rcDst, &rcSrc, &rcWindow, pImage->nWidth, pImage->nHeight, z,0xffffffff, 0 );
	}
	return true;
	unguard;
}






BOOL CAdvancedMiniMap::GetCurSelectNpc( D3DXVECTOR3& vPos )
{
	guardfunc;
	if( !m_vecNpcInfo.empty() )
	{
		vPos.x = m_vecNpcInfo[0]._mapX;
		vPos.y = m_vecNpcInfo[0]._mapY;
		vPos.z = 0;
		return TRUE;
	}
	return FALSE;
	unguard;
}

void CAdvancedMiniMap::Run(int nRoleX, int nRoleY)
{
	if (!s_CUI_ID_FRAME_MiniMap.GetPICTURE_Map() || !s_CUI_ID_FRAME_MiniMap.GetPICTURE_Map()->IsVisable())
	{
		return;
	}



	DWORD nowTime = ::GetTickCount();
	if (nowTime - m_lastRefreshTime > g_refreshInterval)
	{
		RefreshCurrMapTexture();
		RECT rcWindow;
		if( s_CUI_ID_FRAME_MiniMap.GetPICTURE_Map() )
			s_CUI_ID_FRAME_MiniMap.GetPICTURE_Map()->GetRealRect( &rcWindow );
		rcWindow.left -= 5;
		m_lastRefreshTime = nowTime;
		int nPosX = nRoleX * 2;
		int nPosY = nRoleY * 2;
		float zoomScale = s_CUI_ID_FRAME_MiniMap.GetZoomScale();
		int h = m_minimapScreenHeight / zoomScale;
		float fMaxShowRadius = h*m_maxDimension/(m_texEdge*2);
		m_currMapImageList.clear();

		std::map< GameObjectId, CPlayer* >& playArr = theApp->GetPlayerMgr()->m_mapPlayers;
		std::map<GameObjectId, CPlayer*>::iterator it;
		for( it = playArr.begin(); it != playArr.end(); it++ )
		{
			CPlayer* pPlayer = it->second;
			if (!pPlayer)
			{
				continue;
			}
			pPlayer->UpdateDistanceToRole(0,nRoleX,nRoleY);
			if(pPlayer->GetDistanceToRole() > fMaxShowRadius)
				continue;
			//宠物
			if (pPlayer->IsPet())
			{
				AddMapImage(eImage_PetAnimal, pPlayer->GetID());
				continue;
			}

			//镖车,保护怪
			if (pPlayer->IsMonster() && pPlayer->IsMonsterType(eMT_Protect))
			{
				AddMapImage(eImage_ProtectMonster, pPlayer->GetID());
				continue;
			}

			if (pPlayer->IsNpc() )
			{
				if( GameSetting::Instance()->GetLevel( GameSetting::eGSC_MiniMapNpc ) )
				{
					//--画 npc--

					const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pPlayer->GetNpcID());
					if (pInfo == NULL || !pInfo->_miniShow)
					{
						continue;
					}
					int nImageType = GetImageMap(pInfo->_nType);
					{
						int nNpcTipsType = theApp->GetPlayerMgr()->UpdateNpcTipsType( pPlayer->GetID() );
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
						}
					}
					AddMapImage(nImageType,pPlayer->GetID());
				}			

			}//--end of npc
			else if(pPlayer->IsPlayer() && !pPlayer->m_cFightStatus.IsHide())
			{
				bool bDontShow = false;
				//--画主角-
				if (pPlayer == theApp->GetPlayerMgr()->GetMe())
				{
					AddMapImage(eImage_Me,pPlayer->GetID());
					continue;
				}
				if (pPlayer->m_cFightStatus.IsHide())
				{//隐身状态，不绘制
					continue;
				}
				float posx,posy;
				pPlayer->GetPos(&posx,&posy,NULL);
				if(thePlayerRole.IsTeamMember(pPlayer->GetName()) && ( bDontShow = true ) && GameSetting::Instance()->GetLevel( GameSetting::eGSC_MiniMapTeam ) )
				{
					//--画队友
					AddMapImage(eImage_Teammate,pPlayer->GetID());				
				}
				else if(thePlayerRole.GetDuelTarget() == pPlayer->GetID() 
					|| ((CURRENTTILE->GetCanPk() == MapConfig::MapData::EPKM_Allow_PK)	/*&& ( thePlayerRole.GetGangMgr()->guildRelation(pPlayer) == GR_ADVERSE )*/	)
					)
				{	
					AddMapImage(eImage_Enemy,pPlayer->GetID());					
				}
				else if ( (thePlayerRole.isChouRen(pPlayer->GetName()) && ( bDontShow = true ) && GameSetting::Instance()->GetLevel( GameSetting::eGSC_MiniMapEnemy ))
					||(CURRENTTILE&&CURRENTTILE->GetCanPk() == MapConfig::MapData::EPKM_Group_PK&& thePlayerRole.GetInfluence() != pPlayer->GetInfluence()))
				{
					AddMapImage(eImage_Enemy,pPlayer->GetID());
					// 仇人
				}
				else if(thePlayerRole.IsFriend(pPlayer->GetName()) && ( bDontShow = true ) && GameSetting::Instance()->GetLevel( GameSetting::eGSC_MiniMapFriend ) )
				{//朋友
					AddMapImage(eImage_Friend,pPlayer->GetID());
				}
				else if( ( pPlayer->HasGuild() && pPlayer->GetGuildId() ==  thePlayerRole.GetGangMgr()->GetGuildID() )
					&& ( bDontShow = true ) && GameSetting::Instance()->GetLevel( GameSetting::eGSC_MiniMapGuild ) )
				{				
					AddMapImage(eImage_Guild,pPlayer->GetID());
				}
				else if (thePlayerRole.GetInfluence() != CampDefine::NoneCamp && thePlayerRole.GetInfluence() == pPlayer->GetInfluence())
				{
					AddMapImage(eImage_Guild,pPlayer->GetID());
				}
				else
				{
					if( !bDontShow && GameSetting::Instance()->GetLevel( GameSetting::eGSC_MiniMapOther ) )
						AddMapImage(eImage_Player,pPlayer->GetID());
				}

			}
		}
		POINT ptMouse = theUiManager.m_ptMoust;
		float posx,posy;
		CPlayer* pCursor = NULL;
		std::list<MapImage>::iterator iter = m_currMapImageList.begin();
		while(iter != m_currMapImageList.end())
		{
			MapImage& img = (*iter);
			CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(img.nPlayerId);
			// added, jiayi, [2009.4.19]
			if(!pPlayer)
			{
				++iter;
				continue;
			}
			pPlayer->GetPos(&posx,&posy,NULL);

			RECT rcDst;
			GetImageWindowRect( rcWindow,  img.nImageType, posx, posy, rcDst,nPosX,nPosY,zoomScale );
			if(PtInRect(&rcDst, ptMouse))
			{
				float deltax = ptMouse.x - m_minimapScreenCenterX;
				float deltay = ptMouse.y - m_minimapScreenCenterY;
				if (sqrtf(deltax*deltax+deltay*deltay) < m_minimapScreenHeight/2)
				{
					pCursor = pPlayer;
					break;
				}
			}
			++iter;
		}
		if (m_pPlayerCursorOn != pCursor)
		{
			m_pPlayerCursorOn = pCursor;
			s_CUI_ID_FRAME_MiniMap.GetFrame()->SetRedraw();
		}
	}
}

void CAdvancedMiniMap::Render( int nRoleX, int nRoleY )
{
	RECT rcWindow;
	if( s_CUI_ID_FRAME_MiniMap.GetPICTURE_Map() )
		s_CUI_ID_FRAME_MiniMap.GetPICTURE_Map()->GetRealRect( &rcWindow );
	rcWindow.left -= 5;
	GetDrawer()->DrawCircleFlat3D(rcWindow.left+(rcWindow.right-rcWindow.left)/2/*MINIMAPRADIUS / 2*/,
		rcWindow.top+(rcWindow.bottom-rcWindow.top)/2/*MINIMAPRADIUS / 2*/,
		0,
		(rcWindow.right-rcWindow.left)/2 + (ControlObject::GetSCALE(NULL) >= 1.0f ? 1.5 : 1.5 * ControlObject::GetSCALE(NULL)),//MINIMAPRADIUS / 2+10,
		32,
		0x0);
	//-- 这里渲染
	// 小地图图片的宽高。

	RECT rcWindowCopy = rcWindow;

	m_minimapScreenWidth = rcWindow.right - rcWindow.left;
	m_minimapScreenHeight = rcWindow.bottom - rcWindow.top;

	float zoomScale = s_CUI_ID_FRAME_MiniMap.GetZoomScale();
	// 小地图显示区域的宽高。
	int w = m_minimapScreenWidth / zoomScale;
	int h = m_minimapScreenHeight / zoomScale;

	// 世界坐标
	float x = m_xPixelOffset + nRoleX;
	float y = m_yPixelOffset + nRoleY;

	RECT rcMapImageCopy;//  (2.0 - zoomScale);
	rcMapImageCopy.left = (x / m_maxDimension) * m_texEdge - w / 2;
	rcMapImageCopy.top = m_texEdge - (y / m_maxDimension) * m_texEdge - h / 2;
	rcMapImageCopy.right = rcMapImageCopy.left + w;
	rcMapImageCopy.bottom = rcMapImageCopy.top + h;
	float posx,posy;


	GetDrawer()->BltNotTransparency( 
		oldTexid,
		&rcWindowCopy, 
		&rcMapImageCopy,
		&rcWindowCopy, 
		m_texEdge, 
		m_texEdge,
		0.15f, 0xffffffff,
		0);

	if (s_CUI_ID_FRAME_MiniMap.m_bTipActive && m_pPlayerCursorOn && theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->IsPlayerValid(m_pPlayerCursorOn))
	{
		char tip[256];
		m_pPlayerCursorOn->GetPos(&posx,&posy,NULL);
		{
			MeSprintf_s( tip,sizeof(tip)/sizeof(char) - 1, "%s(%ld,%ld)",m_pPlayerCursorOn->GetName(), ZnFloor2Int(posx), ZnFloor2Int(posy ));
		}
		RenderTip( rcWindow,tip);
	}
}

void CAdvancedMiniMap::RenderNeedRedraw( int nMode, int nRoleX, int nRoleY)
{
	guardfunc;
	RECT rcWindow;
	if( s_CUI_ID_FRAME_MiniMap.GetPICTURE_Map() )
		s_CUI_ID_FRAME_MiniMap.GetPICTURE_Map()->GetRealRect( &rcWindow );
	rcWindow.left -= 5;
	POINT ptMouse = theUiManager.m_ptMoust;
	gs_pSelNpcInfo = NULL;

	int nPosX = nRoleX * 2;
	int nPosY = nRoleY * 2;

	float zoomScale = s_CUI_ID_FRAME_MiniMap.GetZoomScale();

	m_minimapScreenCenterX = rcWindow.left+(rcWindow.right-rcWindow.left)/2;
	m_minimapScreenCenterY = rcWindow.top+(rcWindow.bottom-rcWindow.top)/2;
	m_minimapScreenRadius = (rcWindow.right-rcWindow.left)/2;

	float posx,posy;

// 	std::map< short, CPlayer* >& playArr = theApp->GetPlayerMgr()->m_mapPlayers;
// 	std::map<short, CPlayer*>::iterator it;
// 	string sTypeString;
// 	DWORD nowTime = ::GetTickCount();
// 	if (nowTime - m_lastRefreshTime > g_refreshInterval)
	{
		if (CPathDirection::Instance()->IsActive())
		{
			float zoomScale = s_CUI_ID_FRAME_MiniMap.GetZoomScale();
			int h = m_minimapScreenHeight / zoomScale;
			float fMaxShowRadius = h*m_maxDimension/(m_texEdge*2);
			float posxMe,posyMe;
			theHeroGame.GetPlayerMgr()->GetMe()->GetPos(&posxMe,&posyMe,NULL);
			for (int i = CPathDirection::Instance()->GetPathDirBegin(); i < CPathDirection::Instance()->GetPathDirEnd(); ++i)
			{
				CPathDirection::Instance()->GetDirectionPos(i,posx,posy);
				if (sqrtf((posxMe - posx)*(posxMe - posx) + (posyMe - posy)*(posyMe - posy)) > fMaxShowRadius)
				{
					continue;
				}
				RECT rcDst;
				GetImageWindowRect( rcWindow,  eImage_MiniMapPath, posx, posy, rcDst,nPosX,nPosY,zoomScale );
				DrawImage(  rcWindow,  eImage_MiniMapPath, rcDst );
			}
		}

		std::list<MapImage>::iterator iter = m_currMapImageList.begin();
		while(iter != m_currMapImageList.end())
		{
			MapImage& img = (*iter);
			CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(img.nPlayerId);
			// added, jiayi, [2009.4.19]
			if(!pPlayer)
			{
				++iter;
				continue;
			}
			pPlayer->GetPos(&posx,&posy,NULL);
			bool bTarget =  (pPlayer== m_pTargetPlayer) || (pPlayer == m_pPlayerCursorOn);

			RECT rcDst;
			GetImageWindowRect( rcWindow,  img.nImageType, posx, posy, rcDst,nPosX,nPosY,zoomScale );
// 			if(NULL == m_pPlayerCursorOn && PtInRect(&rcDst, ptMouse))
// 			{
// 				float deltax = ptMouse.x - m_minimapScreenCenterX;
// 				float deltay = ptMouse.y - m_minimapScreenCenterY;
// 				if (sqrtf(deltax*deltax+deltay*deltay) < m_minimapScreenHeight/2)
// 				{
// 					m_pPlayerCursorOn = pPlayer;
// 					bTarget = true;
// 				}
// 			}
			DrawImage( rcWindow, img.nImageType, rcDst,  bTarget);
			++iter;
		}
	}

	unguard;	 
}


void CAdvancedMiniMap::CancelNPCPF()
{
	guardfunc;
	m_vecNpcInfo.clear();
	CPathDirection::Instance()->Reset();
	CrossMapPF::Instance()->Reset();
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();

	if (pMe)
	{
		pMe->SetMoving(FALSE);
	}

	unguard;
}
void CAdvancedMiniMap::SetNpcInfo(const char* szName, double mapX, double mapY, bool bNpc)
{
	guardfunc;
	NpcCoordInfo info;
	if(szName && strlen(szName) > 0)
	{
		info._szName = Common::_tstring::toWideString(szName);
		info._mapX	 = mapX;
		info._mapY	 = mapY;
		info._bNpc	 = bNpc;
	}
	m_vecNpcInfo.push_back(info);

	unguard;
}

void CAdvancedMiniMap::SetNpcInfo(const NpcCoordInfo* pInfo )
{
	m_vecNpcInfo.clear();
	if (pInfo)
	{
		m_vecNpcInfo.push_back(*pInfo);
	}

}
const NpcCoordInfo* CAdvancedMiniMap::getNpcInfo(int index )
{
    if ( index < m_vecNpcInfo.size() )
    {
        return &m_vecNpcInfo[index];
    }
    return NULL;
}

void CAdvancedMiniMap::ProcessMinimapMouseDownL(int x, int y)//zhuxincong点击小地图 上的坐标然后上马寻路过去
{

	int xd = x - m_minimapScreenCenterX;
	int yd = y - m_minimapScreenCenterY;
	int dist = xd * xd + yd * yd;
	if (fabsf(dist) > m_minimapScreenRadius * m_minimapScreenRadius)
		return;

	RECT _temp ={0,0,0,0};
	s_CUI_ID_FRAME_MiniMap.GetPicMapRect(_temp);

	if (x>_temp.left && x < _temp.right && y > _temp.top && y < _temp.bottom)
		if (s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
		{
			s_CUI_ID_FRAME_AutoAttackSet.EndAutoAttack();//zhuxincong 点击后 移除挂机状态
		}

	m_pTargetPlayer = m_pPlayerCursorOn;
	CWorldTile* pCurrTile = CURRENTTILE;
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();

	float fXOff = 0;
	float fYOff = 0;
	float fDist = 0;

	if (m_pPlayerCursorOn)
	{
		fXOff = m_pPlayerCursorOn->GetPos().x - pMe->GetPos().x;
		fYOff = m_pPlayerCursorOn->GetPos().y - pMe->GetPos().y;
		fDist = sqrtf(fXOff*fXOff+fYOff*fYOff);
		
		if (m_pPlayerCursorOn->IsNpc())
		{
			const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(m_pPlayerCursorOn->GetNpcID(),pCurrTile->GetMapId());
			PositionInfo::Position* pos = PositionInfo::Instance().GetPositionById(pInfo->_nID);
		
			if (pInfo->_bPFPossible && pos->needMount && fDist >=50)
			{
				if (thePlayerRole.GetActivedMount())
				{
					if (!(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting()))//zhuxincong 8.2 2012 寻路上马，没有判断距离长度
					{
						// 压镖状态下寻路禁止上马
						if (!theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
							s_CUI_ID_FRAME_Pet.Mount();
					}
				}
				theHeroGame.GetPlayerMgr()->MoveRoleToNPC(pInfo);
				return;
			}

			else if (pos == NULL && fDist >= 50)
			{
				if (thePlayerRole.GetActivedMount())
				{
					if (!(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting()))//zhuxincong 8.2 2012 寻路上马，没有判断距离长度
					{
						// 压镖状态下寻路禁止上马
						if (!theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
							s_CUI_ID_FRAME_Pet.Mount();
					}
				}
				theHeroGame.GetPlayerMgr()->MoveRoleToNPC(pInfo);
				return;
			}
		}
		{
			theHeroGame.GetPlayerMgr()->MoveRoleToPlayer(m_pPlayerCursorOn);
		}
	}
	else
	{
		RECT rcMinModeWindow;
		if( s_CUI_ID_FRAME_MiniMap.GetPICTURE_Map() )
			s_CUI_ID_FRAME_MiniMap.GetPICTURE_Map()->GetRealRect( &rcMinModeWindow );
		rcMinModeWindow.left -= 5;

		float posx,posy;
		if(theApp->GetPlayerMgr()->GetMe() )
			theApp->GetPlayerMgr()->GetMe()->GetPos(&posx,&posy,NULL);

		float zoomScale = s_CUI_ID_FRAME_MiniMap.GetZoomScale();

		float targetPosX = (x - (rcMinModeWindow.right + rcMinModeWindow.left)/2)/(2*zoomScale )+ posx;
		float targetPosY = posy - (y - (rcMinModeWindow.top + rcMinModeWindow.bottom)/2)/(2*zoomScale);
		s_CUI_ID_FRAME_MiniMap.SetLastPFPoint(targetPosX,targetPosY,pCurrTile->GetMapId());
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			theHeroGame.GetPlayerMgr()->GetMe()->SetActionTarget(-1);

		theHeroGame.GetPlayerMgr()->MoveRoleTo(targetPosX, targetPosY);
	}

}
#include "ShowScreenText.h"

bool CAdvancedMiniMap::MoveRoleToNPC()
{
	const NpcCoordInfo* pNpcInfo = getNpcInfo(0);
	if ( pNpcInfo )
	{
		if (pNpcInfo->_bPFPossible)
		{
			if( theApp->GetPlayerMgr()->GetMe())
			{
				bool bRet = theApp->GetPlayerMgr()->MoveRoleToNPC(pNpcInfo);
				if (!bRet)
				{
					CWorldTile* pCurrTile = CURRENTTILE;
					if (pCurrTile->GetMapId() != pNpcInfo->_mapId)
					{
						s_CUI_ID_FRAME_FindRoad.ResetRoadInfo();
						s_CUI_ID_FRAME_FindRoad.SetTargetInfo(pCurrTile->GetMapId(),pNpcInfo->_mapId,pNpcInfo->_mapX,pNpcInfo->_mapY,pNpcInfo->_nID);
						s_CUI_ID_FRAME_FindRoad.SetVisable(true);
						s_CUI_ID_FRAME_FindRoad.RefreshRoadInfo();
					}
					
					//CWorldTile* pCurrTile = CURRENTTILE;
					//if (pCurrTile->GetMapId() != pNpcInfo->_mapId)
					//{
					//	/*CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_MiniMapFindPath, theXmlString.GetString(eText_StringNoArried) );
					//	return false;*/
					//	s_CUI_ID_FRAME_FindRoad.SetTargetInfo();
					//	s_CUI_ID_FRAME_FindRoad._SetVisable(true);
					//	bool bifRoad = s_CUI_ID_FRAME_FindRoad.findline(pNpcInfo->_mapId,pCurrTile->GetMapId(),pNpcInfo->_nID);
					//	if (!bifRoad)
					//	{
					//		/*
					//		 *	Author 2012-11-8 zhuxincong
					//		 *	DESC: 跨地图寻路
					//		 */
					//		s_CUI_ID_FRAME_FindRoad.SetVisable(false);
					//		s_CUI_ID_FRAME_FindRoad.Refresh();
					//		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, theXmlString.GetString(eText_CannotCrossMapPathFind) );
					//	}
					//}
				}
			}
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_MiniMapFindPath, theXmlString.GetString(eText_StringNoArried) );
			return false;
		}
	}	
	return true;
}

void CAdvancedMiniMap::AddMapImage( int nImageType,int nPlayerId)
{
	MapImage img;
	img.nImageType	= nImageType;
	img.nPlayerId		= nPlayerId;
    if(nImageType == eImage_CampBattleS || nImageType == eImage_CampBattleT || nImageType == eImage_CampBattleZL)
    {
        m_currMapImageList.push_front(img);
        return;
    }
	std::list<MapImage>::iterator iter = m_currMapImageList.begin();
	while(iter != m_currMapImageList.end())
	{
		if ((*iter).nImageType > nImageType)
		{
			m_currMapImageList.insert(iter,img);
			return;
		}
		++iter;
	}
	m_currMapImageList.push_back(img);
}

BOOL CAdvancedMiniMap::DrawCameraImage( RECT rcWindow)
{
	guardfunc;
	Image* pImage = &m_images[eImage_Camera];
	const int imagePixel = 64;
	RECT rcDst;
			rcDst.left	= rcWindow.left +  (rcWindow.right - rcWindow.left)/2 - imagePixel /2;
			rcDst.top	= rcWindow.top + (rcWindow.bottom - rcWindow.top)/2 - imagePixel /2;
			rcDst.right = rcDst.left + imagePixel - 1;
			rcDst.bottom = rcDst.top + imagePixel - 1;

	RECT rcSrc =
	{
		0, 0, pImage->nWidth, pImage->nHeight
		//0,0,16,16
	};
	float z = 0.115f;
	{
		FLOAT fDir = 0.0f;
		fDir = getwsCamera()->GetCameraRotateX() + getwsCamera()->GetCameraRotateXCorrect() + D3DX_PI/2;
		while(fDir < 0)
		{
			fDir += 2* D3DX_PI;
		}
		while(fDir > 2* D3DX_PI)
		{
			fDir -= 2* D3DX_PI;
		}
		fDir = fDir/2;
		const float fPer = D3DX_PI/16;
		INT fValues = fDir / fPer;
		INT fY = fValues / 4;
		INT fX = fValues % 4;
		SetRect( &rcSrc, (fX)*imagePixel, (fY)*imagePixel, (fX+1)*imagePixel, (fY+1)*imagePixel );
	}
	theControlPictureManager.BitBlt(&pImage->nTextureID,NULL,&rcDst,&rcSrc,0xffffffff,z,0);
	return true;
// 	return GetDrawer()->Blt( pImage->nTextureID, &rcDst, &rcSrc, &rcWindow, pImage->nWidth, pImage->nHeight, z,0xffffffff, 0 );	

	unguard;

}
extern int  g_nsrcPixelEdgeLength;

void CAdvancedMiniMap::RefreshCurrMapTexture()
{
	int texid = -1;
	CWorldTile* worldTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
	if (worldTile)
	{
        texid = worldTile->GetMinimapId();
        if( texid != -1 && (oldTile != worldTile || texid != oldTexid) )
		{
			oldTexid = texid;
			oldTile = worldTile;
			flt32 worldWidth = worldTile->GetWidth();
			flt32 worldHeight = worldTile->GetDepth();

			if (worldWidth > worldHeight )
			{
				m_maxDimension = (worldWidth * worldTile->GetRegionEdge()) /(g_nsrcPixelEdgeLength);
				m_xPixelOffset = 0 - worldTile->GetRegionOffsetX()*worldWidth/g_nsrcPixelEdgeLength;
				m_yPixelOffset = (worldWidth - worldHeight)/2 - worldTile->GetRegionOffsetY()*worldWidth/g_nsrcPixelEdgeLength;
			}
			else
			{
				m_maxDimension = (worldHeight * worldTile->GetRegionEdge()) /(g_nsrcPixelEdgeLength);
				m_xPixelOffset = (worldHeight - worldWidth)/2 - worldTile->GetRegionOffsetX()*worldHeight/g_nsrcPixelEdgeLength;
				m_yPixelOffset = 0 - worldTile->GetRegionOffsetY()*worldHeight/g_nsrcPixelEdgeLength;
			}

			m_texEdge = 1024;
		}
	}
}


void CAdvancedMiniMap::GetRcSrcForMe( RECT& rcSrc )
{
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe )
		return;
	Image* pImage = &m_images[eImage_Me];
	FLOAT fDir = 0.0f;
	pMe->GetDir( &fDir );
	fDir = fDir/2;
	const float fPer = D3DX_PI/16;
	INT fValues = fDir / fPer;
	INT fY = fValues / 4;
	INT fX = fValues % 4;
	SetRect( &rcSrc, (fX)*pImage->nWidth/4, (fY)*pImage->nWidth/4, (fX+1)*pImage->nHeight/4, (fY+1)*pImage->nHeight/4 );
}

void CAdvancedMiniMap::RenderTip( RECT &rcWindow ,const char * tip )
{
	{
		int nLength = strlen( tip )*6+4;
		int nTipX = theUiManager.m_ptMoust.x;
		int nTipY = theUiManager.m_ptMoust.y-25;
		if( nTipX+nLength >= SCREEN_WIDTH )
			nTipX = SCREEN_WIDTH-nLength;
		if( nTipY+16 >= SCREEN_HEIGHT )
			nTipY = SCREEN_HEIGHT-16;
		RECT rc = {	nTipX,nTipY, nTipX+nLength,	nTipY+19 };

		if( rc.left < rcWindow.left )
			rc.left = rcWindow.left;
		if( rc.top < rcWindow.top )
			rc.top = rcWindow.top;
		if( rc.left > rcWindow.right - nLength )
			rc.left = rcWindow.right - nLength;
		if( rc.bottom > rcWindow.bottom - 14 )
			rc.bottom = rcWindow.bottom - 14;

 		m_TipInfo.SetInfo( tip );

		if( s_CUI_ID_FRAME_MiniMap.GetFrame() )
		{
			theIconInfoMouseTip.SetDisplayInfo( &m_TipInfo,
				nTipX, nTipY, false,
				s_CUI_ID_FRAME_MiniMap.GetFrame()->GetFontIndex(), 
				s_CUI_ID_FRAME_MiniMap.GetFrame()->GetFontSize() * ControlObject::GetREAL_SCALE(s_CUI_ID_FRAME_MiniMap.GetFrame()),
				s_CUI_ID_FRAME_MiniMap.GetFrame()->GetFontColor(),
				false );
		}
	}
}


int CAdvancedMiniMap::GetImageType( const char* pString )
{

	if (!pString)
	{
		return -1;
	}
	for (int i =0; i < eImage_Max; ++i)
	{
		if(strcmp(pString,miniIcon[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

void CAdvancedMiniMap::SetTargetNpc( const char* val )
{
	if (val)
	{
		m_strTargetNpc = val;
	}
	else
	{
		m_strTargetNpc.clear();
	}
}

void CAdvancedMiniMap::InsertImageTypeByOrder( SImageType& type )
{
	std::list<SImageType>::iterator iter = m_ImageTypeList.begin();
	for(iter = m_ImageTypeList.begin(); iter != m_ImageTypeList.end();++iter)
	{
		if ((*iter).m_Order > type.m_Order)
		{
			m_ImageTypeList.insert(iter,type);
			break;
		}
	}
	if (iter == m_ImageTypeList.end())
	{
		m_ImageTypeList.push_back(type);
	}
}

int CAdvancedMiniMap::GetImageMap( BYTE byNpcType )
{
    int nImageType = eImage_NormalNpc;
    switch( byNpcType )
    {
    case eNT_Restore:
        nImageType = eImage_Restore;
        break;
    case eNT_Weapon:
        nImageType = eImage_Weapon;
        break;
    case eNT_Jewelry:
        nImageType = eImage_Jewelry;
        break;
    case eNT_Dress:
        nImageType = eImage_Dress;
        break;
    case eNT_Material:
        nImageType = eImage_Material;
        break;
    case eNT_Transport:
        nImageType = eImage_Transport;
        break;
    case eNT_Cavalry:
        nImageType = eImage_Cavalry;
        break;
    case eNT_Storage:
        nImageType = eImage_Storage;
        break;
    case eNT_Star:
        nImageType = eImage_Star;
        break;
    case eNT_MakeItemNpc:
        nImageType = eImage_MakeItem;
        break;
    case eNT_Activity:
        nImageType = eImage_Activity;
        break;
    case eNT_Feudal:
        nImageType = eImage_Feudal;
        break;
    case eNT_Sale:
        nImageType = eImage_Sale;
        break;
    case eNT_SpecialSale:
        nImageType = eImage_SpecialSale;
        break;
    case eNT_GongXun:
        nImageType = eImage_GongXun;
        break;
    case eNT_MingWang:
        nImageType = eImage_MingWang;
        break;
    case eNT_ShiZhuang:
        nImageType = eImage_ShiZhuang;
        break;
    case eNT_WenDa:
        nImageType = eImage_WenDa;
        break;
    case eNT_JiNeng:
        nImageType = eImage_JiNeng;
        break;
    case eNT_PeiJian:
        nImageType = eImage_PeiJian;
        break;
    case eNT_ShiWu:
        nImageType = eImage_ShiWu;
        break;
    case eNT_YiZhan:
        nImageType = eImage_YiZhan;
        break;
    case eNT_ZaHuo:
        nImageType = eImage_ZaHuo;
        break;
    case eNT_FenJie:
        nImageType = eImage_FenJie;
        break;
    case eNT_QianZhuang:
        nImageType = eImage_QianZhuang;
        break;
    case eNT_MoveStar:
        nImageType = eImage_MoveStar;
        break;
    case eNT_SpecialRepair:
        nImageType = eImage_SpecialRepair;
        break;
//     case eNT_Patrol:
//         nImageType = eImage_Patrol;
//         break;
    case eNT_Ship:
        nImageType = eImage_KeepWord1;
        break;
    case eNT_KeepWord2:
        nImageType = eImage_KeepWord2;
        break;
    case eNT_KeepWord3:
        nImageType = eImage_KeepWord3;
        break;
    case eNT_KeepWord4:
        nImageType = eImage_KeepWord4;
        break;
    case eNT_KeepWord5:
        nImageType = eImage_KeepWord5;
        break;
    case eNT_KeepWord6:
        nImageType = eImage_KeepWord6;
        break;
    case eNT_KeepWord7:
        nImageType = eImage_KeepWord7;
        break;
    case eNT_KeepWord8:
        nImageType = eImage_KeepWord8;
        break;
    case eNT_KeepWord9:
        nImageType = eImage_KeepWord9;
        break;
    default:
        break;
    }
    return nImageType;
}
