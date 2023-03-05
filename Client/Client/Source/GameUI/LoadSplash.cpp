/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\GameLogo\LoadSplash.cpp
*********************************************************************/
#include <assert.h>
#include "MeTerrain/stdafx.h"
#include "MeUi/UiManager.h"
#include "LoadSplash.h"
#include "UIMgr.h"
#include "GameMain.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"
#include "Common.h"
#include "BackgroundLoadingThreadProc.h"

CUI_ID_FRAME_LoadSplash s_CUI_ID_FRAME_LoadSplash;
MAP_FRAME_RUN( s_CUI_ID_FRAME_LoadSplash, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_LoadSplash, OnFrameRender )

MeThread* CUI_ID_FRAME_LoadSplash::m_pkLoadSklThread = 0;
MeThread* CUI_ID_FRAME_LoadSplash::m_pkLoadConfigThread = 0;
MeThread* CUI_ID_FRAME_LoadSplash::m_pkLoadEffectThread = 0;
MeThread* CUI_ID_FRAME_LoadSplash::m_pkLoadTaskDataThread = 0;

CUI_ID_FRAME_LoadSplash::CUI_ID_FRAME_LoadSplash()
{
	// Member
	m_pID_FRAME_LoadSplash = NULL;
	m_pID_PICTURE_BgMap = NULL;
	m_pID_PROGRESS_LOAD = NULL;
	m_pID_TEXT_TEXT = NULL;
    m_fMainThreadRate = 0.0f;
    m_fSklLoadRate = 0.0f;
    m_fConfigLoadRate = 0.0f;
    m_fEffectLoadRate = 0.0f;
    m_fTaskLoadRate = 0.0f;
    m_bUILoaded = false;
    InitializeCriticalSection( &m_LoadingCS );
}

CUI_ID_FRAME_LoadSplash::~CUI_ID_FRAME_LoadSplash()
{
    DeleteCriticalSection( &m_LoadingCS );
}

#ifdef _DEBUG
#define LOAD_COST_TIME_DEBUG 1
#else
#define LOAD_COST_TIME_DEBUG 0
#endif //_DEBUG
// Frame
bool CUI_ID_FRAME_LoadSplash::OnFrameRun()
{
    if( !IsVisable() )
        return false;

    EnterCriticalSection( &m_LoadingCS );

    m_nProgress += 25;
    if (m_lastProgress < m_nDstProgress)
    {
        m_nProgress = m_lastProgress;
        m_lastProgress = m_nDstProgress;
    }

    if (m_nProgress > m_lastProgress)
        m_nProgress = m_lastProgress;

    if( m_pID_PROGRESS_LOAD )
        m_pID_PROGRESS_LOAD->SetValue( m_nProgress );

    LeaveCriticalSection( &m_LoadingCS );

	if( m_nDstProgress < 950 )
		Sleep(10);

    if( m_nProgress >= 1000 )
	{
		// 加载ICON代码没有多线程保护，所以放在主线程加载
#if LOAD_COST_TIME_DEBUG
		DWORD nLastTimeRecord = HQ_TimeGetTime();
		char cOutputString[2048];
#endif
// 		theHeroGame.LoadUIIcons();
// #if LOAD_COST_TIME_DEBUG
// 		DWORD nThisTimeRecord = HQ_TimeGetTime();
// 		MeSprintf_s( cOutputString, 2048, "\nLoadUIIcons:%d\n", nThisTimeRecord - nLastTimeRecord );
// 		nLastTimeRecord = nThisTimeRecord;
// 		OutputDebugStr(cOutputString);
// #endif

        //ChangeGameState(G_LOADSPLASH, G_LOGIN);
#if LOAD_COST_TIME_DEBUG
		DWORD nThisTimeRecord = HQ_TimeGetTime();
		MeSprintf_s( cOutputString, 2048, "\nLogin加载:%d\n", nThisTimeRecord - nLastTimeRecord );
		nLastTimeRecord = nThisTimeRecord;
		OutputDebugStr(cOutputString);
#endif
		theHeroGame.Initialized();
	}

    return true;
}
bool CUI_ID_FRAME_LoadSplash::OnFrameRender()
{
	static int s_nFrames = 0;

	if( s_nFrames == 1 )
	{
		theHeroGame.InitGameInThread();		
		theMouseManager.SetCursor( MouseManager::Type_Wait );
		CHeroGame::LoadTaskDataProc();
		CHeroGame::LoadRoleSklProc();
		CHeroGame::LoadEffectProc();
		CHeroGame::LoadConfigProc();		
	}
	++s_nFrames;
	
	return true;
}

	// 装载UI
bool CUI_ID_FRAME_LoadSplash::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\LoadSplash.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\LoadSplash.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_LoadSplash::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_LoadSplash, s_CUI_ID_FRAME_LoadSplashOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_LoadSplash, s_CUI_ID_FRAME_LoadSplashOnFrameRender );

	m_pID_FRAME_LoadSplash = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_LoadSplash );
	m_pID_PICTURE_BgMap = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LoadSplash, ID_PICTURE_BgMap );
	m_pID_PROGRESS_LOAD = (ControlProgress*)theUiManager.FindControl( ID_FRAME_LoadSplash, ID_PROGRESS_LOAD );
	m_pID_TEXT_TEXT = (ControlText*)theUiManager.FindControl( ID_FRAME_LoadSplash, ID_TEXT_TEXT );
	assert( m_pID_FRAME_LoadSplash );
	assert( m_pID_PICTURE_BgMap );
	assert( m_pID_PROGRESS_LOAD );
	assert( m_pID_TEXT_TEXT );

    m_nProgress = 0;
    m_nDstProgress = 0;
    m_lastProgress = 0;

    USE_SCRIPT( eUI_OBJECT_LoadSplash, this );

    TipsString.clear();
    char fullname[MAX_PATH] = {0};
    MeSprintf_s(fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\config\\LoadingTip.config", GetRootPath());
    MeXmlDocument doc;
    if( doc.LoadFile( fullname ) )
    {
        if( doc.FirstChildElement("Project") )
        {
            MeXmlElement* lpRoot = doc.FirstChildElement("Project")->FirstChildElement("LoadSplashTips");
            if(lpRoot)
            {
                MeXmlElement* lpWord = lpRoot->FirstChildElement("String");

                const char* szValue = NULL;
                while( lpWord )
                {
                    szValue = lpWord->Attribute("Value");
                    if( szValue )
                    {
                        std::string strContent =Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(szValue).c_str());;
                        TipsString.push_back(strContent);					
                    }
                    lpWord = lpWord->NextSiblingElement("String");
                }
            }
        }
    }
    
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_LoadSplash::_UnLoadUI()
{
    TipsString.clear();
    theControlPictureManager.UnregisterTexture(m_strFileName.c_str());
    CLOSE_SCRIPT( eUI_OBJECT_LoadSplash );
    m_pID_FRAME_LoadSplash = NULL;
	m_pID_PICTURE_BgMap = NULL;
	m_pID_PROGRESS_LOAD = NULL;
	m_pID_TEXT_TEXT = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\LoadSplash.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_LoadSplash::_IsVisable()
{
    if(!m_pID_FRAME_LoadSplash)
        return false;

	return m_pID_FRAME_LoadSplash->IsVisable();
}

DWORD WINAPI InitGameThreadProc( LPVOID lpParam )
{
    guardfunc;

    theHeroGame.InitGameInThread();

    theMouseManager.SetCursor( MouseManager::Type_Wait );

    return 0;
    unguard;
}

// 设置是否可视
void CUI_ID_FRAME_LoadSplash::_SetVisable( const bool bVisable )
{
    if( m_pID_FRAME_LoadSplash )
    {
        if( bVisable )
        {
            if ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT > 1.5f)
            {
                m_strFileName = "data/ui/LOADing/splash_16x9.dds";

                m_pID_FRAME_LoadSplash->m_pstPic->m_rcClient.right = 1024;
                m_pID_FRAME_LoadSplash->m_pstPic->m_rcClient.bottom = 640;
                m_pID_FRAME_LoadSplash->m_pstPic->m_rcFrame.right = 1024;
                m_pID_FRAME_LoadSplash->m_pstPic->m_rcFrame.bottom = 640;
                m_pID_FRAME_LoadSplash->m_nMiddleW = 1024;
                m_pID_FRAME_LoadSplash->m_nMiddleH = 640;
            }
            else
            {
                m_strFileName = "data/ui/LOADing/splash.dds";

                m_pID_FRAME_LoadSplash->m_pstPic->m_rcClient.right = 1024;
                m_pID_FRAME_LoadSplash->m_pstPic->m_rcClient.bottom = 768;
                m_pID_FRAME_LoadSplash->m_pstPic->m_rcFrame.right = 1024;
                m_pID_FRAME_LoadSplash->m_pstPic->m_rcFrame.bottom = 768;
                m_pID_FRAME_LoadSplash->m_nMiddleW = 1024;
                m_pID_FRAME_LoadSplash->m_nMiddleH = 768;
            }

            m_pID_FRAME_LoadSplash->SetPicName(m_strFileName.c_str());
            m_pID_FRAME_LoadSplash->enableEscKey(false);

            if( !TipsString.empty() )
                m_pID_TEXT_TEXT->SetText(TipsString.at((rand()%TipsString.size())));
        }

        bool bFade = true;
        m_pID_FRAME_LoadSplash->SetWidth( SCREEN_WIDTH );
        m_pID_FRAME_LoadSplash->SetHeight( SCREEN_HEIGHT );
        m_pID_FRAME_LoadSplash->SetVisable( bVisable);
		m_pID_FRAME_LoadSplash->SetFadeInorFadeOut(bFade);
//         m_pID_PROGRESS_LOAD->SetVisable( bVisable, bFade );
//         m_pID_PICTURE_BgMap->SetVisable( bVisable, bFade );
//         m_pID_TEXT_TEXT->SetVisable( bVisable,bFade );
        if( bVisable == true )
        {
            theUiManager.ToTop( m_pID_FRAME_LoadSplash );
        }
        theUiManager.Compositor();
        m_lastProgress = 2;

        if( bVisable )
        {
            // 创建线程
            //HANDLE handle =	CreateThread( NULL, 0,
            //    InitGameThreadProc, 0, 0, NULL );
#ifdef _DEBUG
            //if(handle)
            //    CloseHandle(handle);
#endif

            // added by ZhuoMeng.Hu		[10/25/2010]
            // 任务线程
            //BackgoundLoadingThreadProc* m_pkLoadTaskThreadProc = MeNew BackgoundLoadingThreadProc;
            //m_pkLoadTaskThreadProc->SetThreadProcCallBack( CHeroGame::LoadTaskDataProc );
            //m_pkLoadTaskDataThread = MeThread::CreateThread( m_pkLoadTaskThreadProc );

            //// 骨骼线程
            //BackgoundLoadingThreadProc* m_pkRoleSklThreadProc = MeNew BackgoundLoadingThreadProc;
            //m_pkRoleSklThreadProc->SetThreadProcCallBack( CHeroGame::LoadRoleSklProc );
            //m_pkLoadSklThread = MeThread::CreateThread( m_pkRoleSklThreadProc );

            //// 特效线程
            //BackgoundLoadingThreadProc* m_pkLoadEffectThreadProc = MeNew BackgoundLoadingThreadProc;
            //m_pkLoadEffectThreadProc->SetThreadProcCallBack( CHeroGame::LoadEffectProc );
            //m_pkLoadEffectThread = MeThread::CreateThread( m_pkLoadEffectThreadProc );

            //// 读表线程
            //BackgoundLoadingThreadProc* m_pkReadConfigThreadProc = MeNew BackgoundLoadingThreadProc;
            //m_pkReadConfigThreadProc->SetThreadProcCallBack( CHeroGame::LoadConfigProc );
            //m_pkLoadConfigThread = MeThread::CreateThread( m_pkReadConfigThreadProc );

            /*theHeroGame.InitGameInThread();
            theMouseManager.SetCursor( MouseManager::Type_Wait );
            CHeroGame::LoadTaskDataProc();
            CHeroGame::LoadRoleSklProc();
            CHeroGame::LoadEffectProc();
            CHeroGame::LoadConfigProc();*/
        }
    }
}

void CUI_ID_FRAME_LoadSplash::DestroyMultiThread()
{
    //MeDelete( m_pkLoadSklThread );
    //MeDelete( m_pkLoadConfigThread );
    //MeDelete( m_pkLoadTaskDataThread );
    //MeDelete( m_pkLoadEffectThread );
    m_pkLoadSklThread = NULL;
    m_pkLoadConfigThread = NULL;
    m_pkLoadEffectThread = NULL;
    m_pkLoadTaskDataThread = NULL;
}

void CUI_ID_FRAME_LoadSplash::SetThreadLoadRate( int iThreadType, float fRate )
{
    switch( iThreadType )
    {
    case Thread_Main:
        m_fMainThreadRate = fRate;
        break;
    case Thread_Skeleton:
        m_fSklLoadRate = fRate;
        break;
    case Thread_Config:
        m_fConfigLoadRate = fRate;
        break;
    case Thread_Task:
        m_fTaskLoadRate = fRate;
        break;
    case Thread_Effect:
        m_fEffectLoadRate = fRate;
    default:
        break;
    }
    float fSumRate = m_fMainThreadRate + m_fSklLoadRate + m_fConfigLoadRate + m_fTaskLoadRate + m_fEffectLoadRate;
    m_nDstProgress = static_cast<int>( 1000.0f * fSumRate / ( Thread_Max - 1 ) );
    if( m_nDstProgress >= 1000 )
    {
        m_nProgress = 970;
        m_lastProgress = 970;
    }
}

bool CUI_ID_FRAME_LoadSplash::ShouldUILoad()
{
    // 当Splash加载到 3/4 处，主线程开始加载UI
    if( !m_bUILoaded && ( m_fMainThreadRate + m_fSklLoadRate + m_fConfigLoadRate + m_fTaskLoadRate + m_fEffectLoadRate > 0.75f * ( Thread_Max - 1 ) ) )
    {
        m_bUILoaded = true;
        return true;
    }
    else
    {
        return false;
    }
}
