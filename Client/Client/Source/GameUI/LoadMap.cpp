/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\LoadMap.cpp
*********************************************************************/
#include <assert.h>
#include "MeTerrain/stdafx.h"
#include "MeUi/UiManager.h"
#include "LoadMap.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "../Player.h"
#include "ErrorLog.h"
#include "MeUi/MouseManager.h"
#include "RapidXml/MeRapidXml.h"
#include "StringLanguageTranslator.h"
#include "../CrossMapPF.h"
#include "MeAudio/MeAudio.h"
#include "../Cfg.h"
#include "Pack.h"
#include "ActionManager.h"
#include "ui/UIMgr.h"
#include "XmlStringLanguage.h"
#include "QuestData.h"
#include "RandPropertyEvaluate.h"
#include "MessageBox.h"
#include "wsRender.h"
#include "wsCamera.h"
#include "Common.h"
#include "Ui/UIMgr.h"
#include "WeatherEventManager.h"
#include "MiniMap.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "KingBattleEnter.h"
#include "ChannelInfo.h"

extern FLOAT g_LoadedProcess;
extern CCfg gCfg;
extern BOOL g_bNeedUpdate45DegreeCamera;
extern CActionManager g_ActionManager;
extern bool isShowDisconnetMsg;
extern BOOL g_bIsShowSceneAndPlayer;
extern HWND g_hWnd;

int CUI_ID_FRAME_LoadMap::lastProgress = 0;
bool CUI_ID_FRAME_LoadMap::m_canHideLoadMapUI = false;
float CUI_ID_FRAME_LoadMap::m_fAddSpeed = 2.0f;


#include "WSModelEffect.h"
//extern bool g_DirectReadInPackage;
extern BOOL g_bGlobalDataLoaded;    // 只加载一次的全局数据是否加载标记，挪到LoadMap里实现，包含任务，特效
DWORD WINAPI LoadMapThreadProc( LPVOID lpParam )
{
	guardfunc;
	WeatherEventManager::Instance()->StopWeather();
	SwGlobal::GetRender()->UnlockModelRes();
	PauseThread();

	GetEngine()->UseTextureMultiThreadLoading( FALSE );
	s_CUI_ID_FRAME_LoadMap.SetMapLoaded(false);
	theMouseManager.SetCursor( MouseManager::Type_Wait );
	//
	if( (s_CUI_ID_FRAME_LoadMap.GetProcessValue() == 0) && !gCfg.m_bLocalVersion )
		s_CUI_ID_FRAME_LoadMap.SetUIProcessValue(0);

	s_CUI_ID_FRAME_LoadMap.SetVisable( true );

	CUI_ID_FRAME_LoadMap::SMapInfo* pMapInfo = (CUI_ID_FRAME_LoadMap::SMapInfo*)lpParam;

	SwGlobal::SetLoadProgress( 0 );
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      清除按键列表", GetCurrentThreadId() );
	// 清除按键列表
	g_ActionManager.Clear();

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载 Land 开始", GetCurrentThreadId() );
	BOOL bSucess = theHeroGame.LoadLand( pMapInfo->dwMapId, pMapInfo->fX, pMapInfo->fY );
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载 Land 结束", GetCurrentThreadId() );
	if( bSucess )
	{
		CPlayer* pMe = NULL;
		if( theHeroGame.GetPlayerMgr() )
		{
			pMe = theHeroGame.GetPlayerMgr()->GetMe();
			if( pMe )
			{
				LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      重置主角位置", GetCurrentThreadId() );
				pMe->JumpToMapPos( pMapInfo->fX, pMapInfo->fY, pMapInfo->fZ,
					pMapInfo->fDirX,pMapInfo->fDirY );
				//GetAdvancedMiniMap()->ProcessMinimapMouseDownL(LOWORD((pMe->GetPos().x + 1)), HIWORD((pMe->GetPos().y + 1)));
				if( pMe->IsJumping() )
					pMe->StopJump();
				pMe->SetForceTurnRole(TRUE);

				
			}
		}
		g_LoadedProcess = 1.0f;
		s_CUI_ID_FRAME_LoadMap.SetMapLoaded(true);

		// 锁2.5D视角
		if( getwsCamera()->GetLock45DegreeCameraMode() )
			getwsCamera()->SetNeedUpdate45DegreeCamera( TRUE );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      进游戏加载结束\n", GetCurrentThreadId() );
	CUI_ID_FRAME_LoadMap::lastProgress = 1000;
	s_CUI_ID_FRAME_LoadMap.SetProcessValue(1000);
	SwGlobal::SetLoadProgress(100);
	s_CUI_ID_FRAME_LoadMap.SetUIProcessValue(1000);
	s_CUI_ID_FRAME_LoadMap.SetMapLoading(false);

	s_CUI_ID_FRAME_ChannelInfo.InitializeAtEnterWorld();

	GetEngine()->UseTextureMultiThreadLoading( TRUE );

	MsgUpdateVisualEquip EquipMsg;
    for (int i=0; i<EEquipPartType_MaxEquitPart; ++i)
    { EquipMsg.AddItem( i,&thePlayerRole.m_pVisual->equipitem[i] ); }
	theHeroGame.GetPlayerMgr()->OnMsgUpdateVisualEquip(&EquipMsg);

	UnpauseThread();
	return 0;
	unguard;
}


CUI_ID_FRAME_LoadMap s_CUI_ID_FRAME_LoadMap;
MAP_FRAME_RUN( s_CUI_ID_FRAME_LoadMap, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_LoadMap, OnFrameRender )
CUI_ID_FRAME_LoadMap::CUI_ID_FRAME_LoadMap()
{
    // SGuildMember
    m_pID_FRAME_LoadMap = NULL;
    m_pID_PROGRESS_LOAD = NULL;
    m_pID_Pic_BgMap = NULL;
	m_pID_Load_Pic = NULL;
    m_pID_text = NULL;
    m_fProgress = 0.0f;

    m_fTempX = 0.0f;
    m_fTempY = 0.0f;
    m_fTempZ = 0.0f;

    StringVector.clear();
	m_LoadPicVector.clear();

    m_bMapLoaded = true;
    m_bMapLoading = false;
}

void	CUI_ID_FRAME_LoadMap::SetProgress( int n )
{
    guardfunc;
    m_pID_PROGRESS_LOAD->SetValue( n );
    unguard;
}
// Frame
bool CUI_ID_FRAME_LoadMap::OnFrameRun()
{
    guardfunc;
    if( !IsVisable() )
        return false;

    float currProgress = SwGlobal::GetLoadProgress() * 10;
    m_fProgress += m_fAddSpeed;
    if (lastProgress < currProgress)
    {
        m_fProgress = lastProgress;
        lastProgress = currProgress;
    }

    if (m_fProgress > lastProgress)
        m_fProgress = lastProgress;


    static bool bFillFSStarted = false;
    if( m_fProgress < 1000 )
    {
        bFillFSStarted = false;
        // 等收到MapInfoReady消息再置为true
        g_bIsShowSceneAndPlayer = FALSE;
    }
    if( m_pID_PROGRESS_LOAD )
    {
        m_pID_PROGRESS_LOAD->SetValue( (int)m_fProgress  );
        if( m_fProgress >= 1000 && !gCfg.m_bLocalVersion )
        {
            if( !bFillFSStarted && !g_bIsShowSceneAndPlayer )
            {
                if( !isShowDisconnetMsg )   // 判断是否断开链接
                {
                    {
                        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_NowLoadingGameData ), theXmlString.GetString( eText_NowLoadingGameData ),CUI_ID_FRAME_MessageBox::eTypeConfirm, true );
                        s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(false);
                    }
                }
                UiDrawer::StartFillFullScreen( 10, true, 0, 255 );
            }

            bFillFSStarted = true;
        }
    }

    Sleep(20);

    return true;
    unguard;
}
bool CUI_ID_FRAME_LoadMap::OnFrameRender()
{
    guardfunc;
    if (m_canHideLoadMapUI)
        _SetVisable(false);
    if (m_fProgress >= 1000 && m_bMapLoaded)
    {
        m_canHideLoadMapUI = true;
    }
	if( m_bMapLoading )
	{
		if( m_fProgress == 0.f )
		{
			m_fProgress = 0.1f;
			return true;
		}
		// 隐藏UI
		//GetUIScriptMgr()->ShowUIInTimeOfLoadMap(false);
		//CWorldTile* activeTile = CURRENTTILE;
		//if( activeTile && activeTile->IsLoad() )
		//{//先将当前tile设置成未加载状态，防止地形数据在多线程卸载过程中被使用
		//	activeTile->SetLoad(false);
		//}
		//LoadMapThreadProc(&m_stMapInfo);

	}
    return true;
    unguard;
}

// 装载UI
bool CUI_ID_FRAME_LoadMap::_LoadUI()
{
    guardfunc;
    DWORD dwResult = 0;

    dwResult = theUiManager.AddFrame( "data\\ui\\LoadMap.meui", true, UI_Render_LayerThree);
    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[UI\\LoadMap.UI]失败")
            return false;
    }
    return DoControlConnect();
    unguard;
}
// 关连控件
bool CUI_ID_FRAME_LoadMap::DoControlConnect()
{
    guardfunc;
    theUiManager.OnFrameRun( ID_FRAME_LoadMap, s_CUI_ID_FRAME_LoadMapOnFrameRun );
    theUiManager.OnFrameRender( ID_FRAME_LoadMap, s_CUI_ID_FRAME_LoadMapOnFrameRender );

    m_pID_FRAME_LoadMap = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_LoadMap );
    m_pID_PROGRESS_LOAD = (ControlProgress*)theUiManager.FindControl( ID_FRAME_LoadMap, ID_PROGRESS_LOAD );
    m_pID_Pic_BgMap = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LoadMap, ID_PICTURE_BgMap);
	m_pID_Load_Pic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LoadMap, ID_Load_Picture );
    m_pID_text = (ControlText*)theUiManager.FindControl(ID_FRAME_LoadMap,ID_TEXT_TEXT);

    assert( m_pID_FRAME_LoadMap );
    assert( m_pID_PROGRESS_LOAD );
    assert( m_pID_Pic_BgMap );
	assert( m_pID_Load_Pic );
    assert( m_pID_text );
    //

    m_pID_FRAME_LoadMap->setRenderFlag( eLinearFilter );

    USE_SCRIPT( eUI_OBJECT_LoadMap, this );

    char fullname[MAX_PATH] = {0};
    MeSprintf_s(fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\config\\LoadingTip.config", GetRootPath());
    MeXmlDocument doc;
    if( doc.LoadFile( fullname ) )
    {
        if( doc.FirstChildElement("Project") )
        {
            MeXmlElement* lpRoot = doc.FirstChildElement("Project")->FirstChildElement("LoadingTip");
            if(lpRoot)
            {
                MeXmlElement* lpWord = lpRoot->FirstChildElement("String");

                const char* szValue = NULL;
                while( lpWord )
                {
                    szValue = lpWord->Attribute("Value");
                    if( szValue )
                    {
                        std::string strContent =_tstring::toNarrowString(_tstring::UTF8towcs(szValue).c_str());;
                        StringVector.push_back(strContent);					
                    }
                    lpWord = lpWord->NextSiblingElement("String");
                }
            }
        }
    }

	char filename[MAX_PATH] = {0};
	MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s\\data\\config\\LoadingPicture.config", GetRootPath());
	MeXmlDocument fdata;
	m_LoadPicVector.clear();

	if (fdata.LoadFile(filename))
	{
		MeXmlElement* pRoot = fdata.FirstChildElement("Project");
		if (pRoot)
		{
			MeXmlElement* lpRoot = pRoot->FirstChildElement("Pictures");
			if (lpRoot)
			{
				MeXmlElement* lpWord = lpRoot->FirstChildElement("LoadPic");
				while (lpWord)
				{
					SLoadPicture pic;
					int mapid;
					Common::_tstring sname;

					lpWord->Attribute("MapId", &mapid);
					pic.mapid = mapid;

					sname.fromUTF8(lpWord->Attribute("PicName"));
					pic.picname = sname;

					if (pic.mapid > 0)
						m_LoadPicVector.push_back(pic);

					lpWord = lpWord->NextSiblingElement("LoadPic");
				}
			}
		}
	}

    return true;
    unguard;
}

void CUI_ID_FRAME_LoadMap::randomLoginMap()
{
    guardfunc;
    if( !IsUILoad() )
        SetVisable( true );

	int iLoadingNum = gCfg.m_shLoadMapNum > 0 ? gCfg.m_shLoadMapNum : 20;
	int nRand = 0;
	if( gCfg.m_fLoadMapProbability > 0 && gCfg.m_vecProbabilityLoadMaps.size() > 0 )
	{
		int prob = rand() % 100;
		if( prob < gCfg.m_fLoadMapProbability * 100 )
		{
			// 从gCfg.m_vecProbabilityLoadMaps里随机
			int iMaps = gCfg.m_vecProbabilityLoadMaps.size();
			int nRandInProb = rand() % iMaps;
			nRand = gCfg.m_vecProbabilityLoadMaps[nRandInProb];
		}
		else
		{
			int iMaps = iLoadingNum - gCfg.m_vecProbabilityLoadMaps.size();
			int nRandInRemain = rand() % iMaps;
			std::vector<short> vecRemainLoadMaps;
			vecRemainLoadMaps.clear();
			for(int i=0; i<iLoadingNum; ++i)
			{
				bool bFind = false;
				for(int j=0; j<gCfg.m_vecProbabilityLoadMaps.size(); ++j)
				{
					if( i == gCfg.m_vecProbabilityLoadMaps[j] )
					{
						bFind = true;
						break;
					}
				}
				if( !bFind )
				{
					vecRemainLoadMaps.push_back(i);
				}
			}
			if( vecRemainLoadMaps.size() > nRandInRemain )
				nRand = vecRemainLoadMaps[nRandInRemain];
			else
				nRand = 0;
		}
	}
	else
	{
		nRand = rand() % iLoadingNum;
	}
    std::stringstream sstr;
    if ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT > 1.5f)
    {
        sstr << "data/ui/LOADing/loading_16x9_";
        sstr << nRand;
        sstr << ".dds";

        m_pID_FRAME_LoadMap->m_pstPic->m_rcClient.right = 1024;
        m_pID_FRAME_LoadMap->m_pstPic->m_rcClient.bottom = 640;
        m_pID_FRAME_LoadMap->m_pstPic->m_rcFrame.right = 1024;
        m_pID_FRAME_LoadMap->m_pstPic->m_rcFrame.bottom = 640;
        m_pID_FRAME_LoadMap->m_nMiddleW = 1024;
        m_pID_FRAME_LoadMap->m_nMiddleH = 640;
    }
    else
    {
		sstr << "data/ui/LOADing/";
		sstr << "loading_";
		sstr << nRand;
		sstr << ".dds";
		sstr << '\0';

		m_pID_FRAME_LoadMap->m_pstPic->m_rcClient.right = 1024;
		m_pID_FRAME_LoadMap->m_pstPic->m_rcClient.bottom = 768;
		m_pID_FRAME_LoadMap->m_pstPic->m_rcFrame.right = 1024;
		m_pID_FRAME_LoadMap->m_pstPic->m_rcFrame.bottom = 768;
		m_pID_FRAME_LoadMap->m_nMiddleW = 1024;
		m_pID_FRAME_LoadMap->m_nMiddleH = 768;
    }
    m_filename = sstr.str();

    m_pID_FRAME_LoadMap->SetPicName(m_filename.c_str());

    m_pID_FRAME_LoadMap->SetWidth( SCREEN_WIDTH );
    m_pID_FRAME_LoadMap->SetHeight( SCREEN_HEIGHT );
    m_pID_FRAME_LoadMap->enableEscKey(false);
    _SetVisable( true );

    if( !StringVector.empty() )
        m_pID_text->SetText(StringVector.at((rand()%StringVector.size())));
    unguard;
}
// 卸载UI
bool CUI_ID_FRAME_LoadMap::_UnLoadUI()
{
    guardfunc;
    theControlPictureManager.UnregisterTexture(m_filename.c_str());
    CLOSE_SCRIPT( eUI_OBJECT_LoadMap );
    m_pID_FRAME_LoadMap = NULL;
	m_pID_PROGRESS_LOAD = NULL;
	m_pID_Pic_BgMap = NULL;
	m_pID_text = NULL;
    return theUiManager.RemoveFrame( "data\\ui\\LoadMap.meui" );	
    unguard;
}
// 是否可视
bool CUI_ID_FRAME_LoadMap::_IsVisable()
{
    guardfunc;
    if( m_pID_FRAME_LoadMap )
        return m_pID_FRAME_LoadMap->IsVisable();

    return false;
    unguard;
}
// 设置是否可视
extern int g_nWindowMode;
extern GAME_STATE		g_GameState;
void CUI_ID_FRAME_LoadMap::_SetVisable( const bool bVisable )
{
	theUiManager.HideAllDlgNoAllVisable(); //lyh++切换地图的时候 关闭所有不是一直显示的ui
	if( bVisable )
	{
		::SetCursor( theMouseManager.GetCursor( MouseManager::Type_Arrow ) );
	}

    guardfunc;
    if( m_pID_FRAME_LoadMap )
    {
        m_pID_FRAME_LoadMap->SetWidth( SCREEN_WIDTH );
        m_pID_FRAME_LoadMap->SetHeight( SCREEN_HEIGHT );
        m_pID_FRAME_LoadMap->SetVisable( bVisable);
        if( bVisable == true )
        {
            //theUiManager.ToTop( m_pID_FRAME_LoadMap );
        }
        theUiManager.Compositor();
        lastProgress = 2;
		m_fProgress = 0;
		if (bVisable)
		{
			m_pID_PROGRESS_LOAD->SetValue( (int)m_fProgress  );
		}
        m_fAddSpeed = 2.0f;
    }
    m_canHideLoadMapUI = false;

	/*if(theHeroGame.GetPlayerMgr())
	{
		if(theHeroGame.GetPlayerMgr()->GetMe())
		{			
			theHeroGame.GetPlayerMgr()->GetMe()->SetHide(bVisable);
		}
	}*/

    unguard;
}

bool CUI_ID_FRAME_LoadMap::IsMapLoaded()
{
    guardfunc;
    return m_bMapLoaded;
    unguard;
}

void CUI_ID_FRAME_LoadMap::SetUIProcessValue(float fValue)
{
    if(!m_pID_FRAME_LoadMap)
        return;

    m_pID_PROGRESS_LOAD->SetValue(fValue);
}


void CUI_ID_FRAME_LoadMap::LoadMap( DWORD dwMapId, int x, int y,  float fDirX,float fDirY,DWORD nGameMapId)
{
    guardfunc;

    if (m_bMapLoading)
        return;

    m_stMapInfo.dwMapId = dwMapId;
    m_stMapInfo.x = x;
    m_stMapInfo.y = y;
    m_stMapInfo.nGameMapId = nGameMapId;
    m_stMapInfo.fX = m_fTempX;
    m_stMapInfo.fY = m_fTempY;
    m_stMapInfo.fZ = m_fTempZ;
    m_stMapInfo.fDirX = fDirX;
    m_stMapInfo.fDirY = fDirY;

    // 保存玩家所在动态地图ID
    thePlayerRole.SetGameMapId(nGameMapId);

	if (s_CUI_ID_FRAME_KingBattleEnter.IsVisable())
	{
		s_CUI_ID_FRAME_KingBattleEnter.Refresh();
	}

    m_bMapLoaded = false;
    m_bMapLoading = true;

	SetLoadPicture();
    // 隐藏UI
    GetUIScriptMgr()->ShowUIInTimeOfLoadMap(false);
    CWorldTile* activeTile = CURRENTTILE;
    if( activeTile && activeTile->IsLoad() )
    {//先将当前tile设置成未加载状态，防止地形数据在多线程卸载过程中被使用
        activeTile->SetLoad(false);
    }
	//LoadMapThreadProc(&m_stMapInfo);
     DWORD dwThreadId = 0;
     HANDLE handle =	CreateThread( NULL, 0,
         LoadMapThreadProc, &m_stMapInfo,
         0, &dwThreadId );

	 // 显示UI
	 GetUIScriptMgr()->ShowUIInTimeOfLoadMap(true);

    unguard;
}
void CUI_ID_FRAME_LoadMap::SetFloatX(float x)
{
    m_fTempX = x;
}
void CUI_ID_FRAME_LoadMap::SetFloatY(float y)
{
    m_fTempY = y;
}

void CUI_ID_FRAME_LoadMap::SetFloatZ(float z)
{
    m_fTempZ = z;
}

void CUI_ID_FRAME_LoadMap::SetLoadPicture()
{
	guardfunc;
	std::string str("data/ui/LOADing/");
	
	for (std::vector<SLoadPicture>::const_iterator it(m_LoadPicVector.begin()), end(m_LoadPicVector.end()); it != end; it++)
	{
		if (it->mapid == m_stMapInfo.dwMapId)
		{
			str += it->picname;
			if (strlen(it->picname.c_str()) == 0)
				str += "splash.dds";
			break;
		}
	}

	m_pID_Load_Pic->SetPicName(str.c_str());
	m_pID_Load_Pic->SetWidth( SCREEN_WIDTH/2 );
	m_pID_Load_Pic->SetHeight( SCREEN_HEIGHT*2/3 );
	m_pID_Load_Pic->SetVisable(true);
	
	unguard;
}