//-----------------------------------------------------------------------------
// File: D3DApp.cpp
//
// Desc: Application class for the Direct3D samples framework library.
//-----------------------------------------------------------------------------
#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <basetsd.h>
#include <mmsystem.h>
#include <stdio.h>
#include <tchar.h>
#include "Dxsdk/D3D9.h"
#include "D3DApp.h"
#include "D3DUtil.h"
#include "DXUtil.h"
#include "D3DRes.h"
#include "Me3d\Shader.h"
#include "Me3d\ShaderManager.h"
#include "GlobalDef.h"
#include "FuncPerformanceLog.h"
#include "SystemConfig.h"
#include "cfg.h"
#include "Me3d/Config.h"
#include "XmlStringLanguage.h"
#include "application_config.h"
#include "UI/ExitGame.h"
#include "ui/SystemSetting.h"
#include "ui/SystemSettingUI.h"
#include "core/Name.h"
#include "Common.h"
#include <ui/Login.h>
#include <ui/FirstCreate.h>
#include <ui/Create.h>
#include <ui/Select.h>
#include "ui/LoadMap.h"

#ifdef NPGUARD
//LYH NP
#include <NP/NPGameLib.h>
extern CNPGameLib *npgl;
#endif

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int g_nWindowMode;
extern const char* g_pszVersion;
BOOL g_bWindowed = TRUE;
extern bool g_bCloseApp;
extern BOOL g_bMouseLeave;


//-----------------------------------------------------------------------------
// Global access to the app (needed for the global WndProc())
//-----------------------------------------------------------------------------
static CD3DApplication* g_pD3DApp = NULL;

extern const char* GetRootPath();

HWND g_hWnd = NULL;

//#pragma comment( lib , "png.lib" )
#pragma comment ( lib, "imm32.lib" )

/*
 * Author:	2012-8-16 wangshuai
 * Desc: 	是否是低端显卡
 */
bool IsBadVideoCard(LPDIRECT3D9 d3d9, IDirectDraw7 *ddobj)
{
	if (ddobj == NULL)
		return false;

	DDSCAPS2 ddscaps2;
	ZeroMemory(&ddscaps2, sizeof(DDSCAPS2));
	ddscaps2.dwCaps = DDSCAPS_VIDEOMEMORY;
	DWORD dwTotal = 0;
	DWORD dwFree = 0;
	ddobj->GetAvailableVidMem(&ddscaps2, &dwTotal, &dwFree);
	dwTotal *= 0.0000001;
	/*graphics::ShaderManager::instance()->supportPixelShader( 2, 0 )*/
	return dwTotal < 600;
}

//-----------------------------------------------------------------------------
// Name: CD3DApplication()
// Desc: Constructor
//-----------------------------------------------------------------------------
CD3DApplication::CD3DApplication()
{
	OutputDebugStr("Application");
    g_pD3DApp           = this;
	OutputDebugStr("Application1");

	m_bTrue3D			= false;
    m_dwNumAdapters     = 0;
    m_dwAdapter         = 0L;
    m_pD3D              = NULL;
    m_pd3dDevice        = NULL;
    m_hWnd              = NULL;
    m_hWndFocus         = NULL;
    m_bActive           = FALSE;
    m_bReady            = FALSE;
    m_bHasFocus		= FALSE;
    m_dwCreateFlags     = 0L;
	
    m_bFrameMoving      = TRUE;
    m_bSingleStep       = FALSE;
    m_fFPS              = 0.0f;
    m_strDeviceStats[0] = _T('\0');
    m_strFrameStats[0]  = _T('\0');

	OutputDebugStr("Application2");
    m_strWindowTitle    = _T("D3D8 Application");
	OutputDebugStr("Application3");
    m_dwCreationWidth   = 400;
    m_dwCreationHeight  = 300;
    m_bUseDepthBuffer   = FALSE;
    m_dwMinDepthBits    = 0;
    m_dwMinStencilBits  = 0;
    m_bShowCursorWhenFullscreen = FALSE;

	m_BestAdapter = 0;

	m_bChanged		=	FALSE;
	m_ChangedDisplayID = -1;
	m_bSizable = true;
	m_bInitEnd = false;

    // When m_bClipCursorWhenFullscreen is TRUE, the cursor is limited to
    // the device window when the app goes fullscreen.  This prevents users
    // from accidentally clicking outside the app window on a multimon system.
    // This flag is turned off by default for debug builds, since it makes 
    // multimon debugging difficult.
#if defined(_DEBUG) || defined(DEBUG)
    m_bClipCursorWhenFullscreen = FALSE;
#else
    m_bClipCursorWhenFullscreen = TRUE;
#endif
	m_bWindowed = FALSE;

    m_bPauseRendering = FALSE;
	m_bPauseSIZEMOVE = FALSE;
    m_isDeviceLost = FALSE;
	m_isScreenSaverRunning = FALSE;

    memset(m_iFrameCostIn60Frames, 0, 60*sizeof(int));
    m_iFramsCostIndex = 0;
    m_fFrameCostAverage = 0.f;
    m_iLastFrameCost = 0;
    m_iLastFrameUpdateCost = 0;
    m_NetCost = 0;
    m_bAboveNormalPriority = FALSE;

	OutputDebugStr("Application4");
}




//-----------------------------------------------------------------------------
// Name: WndProc()
// Desc: Static msg handler which passes messages to the application class.
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	BeginGuard
    return g_pD3DApp->MsgProc( hWnd, uMsg, wParam, lParam );
	EndGuard
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Create()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CD3DApplication::Create( HINSTANCE hInstance )
{
    HRESULT hr;

	m_hInstance = hInstance;
    // 窗口类名5shen window不要修改，launcher要判断窗口类名检查双开
    const char pWindowName[32] = "YiQiDangQian window";
	
    // Create the Direct3D object
    m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
    if( m_pD3D == NULL )
        return DisplayErrorMsg( D3DAPPERR_NODIRECT3D, MSGERR_APPMUSTEXIT );
    // Build a list of Direct3D adapters, modes and devices. The
    // ConfirmDevice() callback is used to confirm that only devices that
    // meet the app's requirements are considered.
    if( FAILED( hr = BuildDeviceList() ) )
    {
        SAFE_RELEASE( m_pD3D );
        return DisplayErrorMsg( hr, MSGERR_APPMUSTEXIT );
    }
	HWND hDesktop = GetDesktopWindow();
	RECT rcDesktop;
	GetWindowRect( hDesktop, &m_rcDesktop );
	GetWindowRect( hDesktop, &rcDesktop );

	//AdjustWindowRect( &rcDesktop, GetWindowStyle(hDesktop), FALSE );;
	HWND hTaskBar = FindWindow( "Shell_TrayWnd", "" );
	RECT rcTaskBark;
	GetWindowRect( hTaskBar, &rcTaskBark );
	int nTaskBarHeight = rcTaskBark.bottom-rcTaskBark.top;
	rcDesktop.bottom -= nTaskBarHeight;
	// Unless a substitute hWnd has been specified, create a window to
    // render into
    if( m_hWnd == NULL)
    {
        // Register the windows class
        WNDCLASS wndClass = { CS_DBLCLKS, WndProc, 0, 0, hInstance,
                              LoadIcon( hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON) ),
                              NULL,
                              (HBRUSH)GetStockObject(WHITE_BRUSH),
                              NULL, _T(pWindowName) };
        RegisterClass( &wndClass );

		RECT rc;
		if( g_nWindowMode && !m_bTrue3D )//window
			// Set the window's initial style
		{
			m_dwWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX; //lyh修改窗口风格
			//
			m_dwCreationWidth  = SCREEN_WIDTH;
			m_dwCreationHeight = SCREEN_HEIGHT ;

			SetRect( &rc, 0, 0, m_dwCreationWidth, m_dwCreationHeight );
			AdjustWindowRect( &rc, m_dwWindowStyle, FALSE );



		}
		else//fake full screen
		{
			//
			m_dwWindowStyle = WS_POPUP;
			//
			m_dwCreationWidth = m_rcDesktop.right-m_rcDesktop.left;
			m_dwCreationHeight = m_rcDesktop.bottom-m_rcDesktop.top;
			SetRect( &rc, 0, 0, m_dwCreationWidth, m_dwCreationHeight );
		}

        // Create the render window
        g_hWnd = m_hWnd = CreateWindow( _T(pWindowName), m_strWindowTitle, m_dwWindowStyle,
                               0, 0,
							   //m_dwCreationWidth, m_dwCreationHeight,
                               (rc.right-rc.left), (rc.bottom-rc.top), 
							   0L,
                               NULL/*hMenu*/,
                               hInstance, 0L );
		// 马上显示窗口 [11/29/2010 zhangjiayi]
		ShowWindow( m_hWnd, SW_SHOW );

		#ifdef NPGUARD	//LYH NP
		if(npgl)
		npgl->SetHwnd(m_hWnd);
        #endif

		char name[256];
		MeSprintf_s(name,sizeof(name)/sizeof(char) - 1, "%s", ApplicationConfig::Instance().GetProjectName());

		::SetWindowText(m_hWnd, name);
		//
    }
    //
    //
    if( m_hWndFocus == NULL )
        m_hWndFocus = m_hWnd;

    //
   // m_dwWindowStyle = GetWindowLong( m_hWnd, GWL_STYLE ); //lyh-- 窗口风格和上边创建时不一样
    GetWindowRect( m_hWnd, &m_rcWindowBounds );
    GetClientRect( m_hWnd, &m_rcWindowClient );
	SCREEN_WIDTH = m_rcWindowClient.right-m_rcWindowClient.left;;
	SCREEN_HEIGHT = m_rcWindowClient.bottom-m_rcWindowClient.top;;

    // Initialize the application timer
    DXUtil_Timer( TIMER_START );

    // Initialize the app's custom scene stuff
    if( ( hr = OneTimeSceneInit() ) != S_OK )
    {
        SAFE_RELEASE( m_pD3D );
        return DisplayErrorMsg( hr, MSGERR_APPMUSTEXIT );
    }

    // Initialize the 3D environment for the app
    if( ( hr = Initialize3DEnvironment() ) != S_OK )
    {
        SAFE_RELEASE( m_pD3D );
        return DisplayErrorMsg( hr, MSGERR_APPMUSTEXIT );
    }
    // The app is ready to go
    m_bReady = TRUE;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SortModesCallback()
// Desc: Callback function for sorting display modes (used by BuildDeviceList).
//-----------------------------------------------------------------------------
static int SortModesCallback( const VOID* arg1, const VOID* arg2 )
{
    D3DDISPLAYMODE* p1 = (D3DDISPLAYMODE*)arg1;
    D3DDISPLAYMODE* p2 = (D3DDISPLAYMODE*)arg2;

    if( p1->Format > p2->Format )   return -1;
    if( p1->Format < p2->Format )   return +1;
    if( p1->Width  < p2->Width )    return -1;
    if( p1->Width  > p2->Width )    return +1;
    if( p1->Height < p2->Height )   return -1;
    if( p1->Height > p2->Height )   return +1;

    return 0;
}




//-----------------------------------------------------------------------------
// Name: BuildDeviceList()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CD3DApplication::BuildDeviceList()
{
    const DWORD dwNumDeviceTypes = 2;
    const TCHAR* strDeviceDescs[] = { _T("HAL"), _T("REF") };
    const D3DDEVTYPE DeviceTypes[] = { D3DDEVTYPE_HAL, D3DDEVTYPE_REF };

    BOOL bHALExists = FALSE;
    BOOL bHALIsWindowedCompatible = FALSE;
    BOOL bHALIsDesktopCompatible = FALSE;
    BOOL bHALIsSampleCompatible = FALSE;

    // Loop through all the adapters on the system (usually, there's just one
    // unless more than one graphics card is present).
    for( UINT iAdapter = 0; iAdapter < m_pD3D->GetAdapterCount(); iAdapter++ )
    {
        // Fill in adapter info
        D3DAdapterInfo* pAdapter  = &m_Adapters[m_dwNumAdapters];
        m_pD3D->GetAdapterIdentifier( iAdapter, D3DADAPTER_DEFAULT, &pAdapter->d3dAdapterIdentifier );
        m_pD3D->GetAdapterDisplayMode( iAdapter, &pAdapter->d3ddmDesktop );
        pAdapter->dwNumDevices    = 0;
        pAdapter->dwCurrentDevice = 0;

        // Enumerate all display modes on this adapter
        D3DDISPLAYMODE modes[100];
        D3DFORMAT      formats[20];
        DWORD dwNumFormats      = 0;
        DWORD dwNumModes        = 0;
        DWORD dwNumAdapterModes = m_pD3D->GetAdapterModeCount( iAdapter, D3DFMT_X8R8G8B8 );

        // Add the adapter's current desktop format to the list of formats
        formats[dwNumFormats++] = pAdapter->d3ddmDesktop.Format;

        for( UINT iMode = 0; iMode < dwNumAdapterModes; iMode++ )
        {
            // Get the display mode attributes
            D3DDISPLAYMODE DisplayMode;
            m_pD3D->EnumAdapterModes( iAdapter, D3DFMT_X8R8G8B8, iMode, &DisplayMode );

            // Filter out low-resolution modes
            if( DisplayMode.Width  < 1024 || DisplayMode.Height < 768 )
                continue;
			if( DisplayMode.RefreshRate < 60 )
				continue;

            // Check if the mode already exists (to filter out refresh rates)
			DWORD m = 0;
            for( m=0L; m<dwNumModes; m++ )
            {
                if( ( modes[m].Width  == DisplayMode.Width  ) &&
                    ( modes[m].Height == DisplayMode.Height ) &&
                    ( modes[m].Format == DisplayMode.Format ) )
                    break;
            }

            // If we found a MeNew mode, add it to the list of modes
            if( m == dwNumModes )
            {
                modes[dwNumModes].Width       = DisplayMode.Width;
                modes[dwNumModes].Height      = DisplayMode.Height;
                modes[dwNumModes].Format      = DisplayMode.Format;
                modes[dwNumModes].RefreshRate = 0;
                dwNumModes++;

                // Check if the mode's format already exists
				DWORD f = 0;
                for( f=0; f<dwNumFormats; f++ )
                {
                    if( DisplayMode.Format == formats[f] )
                        break;
                }

                // If the format is new, add it to the list
                if( f== dwNumFormats )
                    formats[dwNumFormats++] = DisplayMode.Format;
            }
			m_DisplayModes.push_back( DisplayMode );
        }

        // Sort the list of display modes (by format, then width, then height)
        qsort( modes, dwNumModes, sizeof(D3DDISPLAYMODE), SortModesCallback );

        // Add devices to adapter
        for( UINT iDevice = 0; iDevice < dwNumDeviceTypes; iDevice++ )
        {
            // Fill in device info
            D3DDeviceInfo* pDevice;
            pDevice                 = &pAdapter->devices[pAdapter->dwNumDevices];
            pDevice->DeviceType     = DeviceTypes[iDevice];
            m_pD3D->GetDeviceCaps( iAdapter, DeviceTypes[iDevice], &pDevice->d3dCaps );
            pDevice->strDesc        = strDeviceDescs[iDevice];
            pDevice->dwNumModes     = 0;
            pDevice->dwCurrentMode  = 0;
            pDevice->bCanDoWindowed = FALSE;
            pDevice->bWindowed      = FALSE;

            D3DMULTISAMPLE_TYPE multiSampleType = (_D3DMULTISAMPLE_TYPE)gCfg.m_dwMultiSample;
            if ( FAILED( m_pD3D->CheckDeviceMultiSampleType( iAdapter, pDevice->DeviceType,
                pAdapter->d3ddmDesktop.Format, pDevice->bWindowed, multiSampleType, NULL ) ) )
            {
                multiSampleType = D3DMULTISAMPLE_NONE;
            }
			
            pDevice->MultiSampleTypeFullscreen = multiSampleType;
            pDevice->MultiSampleTypeWindowed = multiSampleType;

            // Examine each format supported by the adapter to see if it will
            // work with this device and meets the needs of the application.
            BOOL  bFormatConfirmed[20];
            DWORD dwBehavior[20];
            D3DFORMAT fmtDepthStencil[20];

            for( DWORD f=0; f<dwNumFormats; f++ )
            {
                bFormatConfirmed[f] = FALSE;
                fmtDepthStencil[f] = D3DFMT_UNKNOWN;

                // Skip formats that cannot be used as render targets on this device
                if( FAILED( m_pD3D->CheckDeviceType( iAdapter, pDevice->DeviceType,
                                                     formats[f], formats[f], FALSE ) ) )
                    continue;

                if( pDevice->DeviceType == D3DDEVTYPE_HAL )
                {
                    // This system has a HAL device
                    bHALExists = TRUE;
                }

                // Confirm the device/format for HW vertex processing
                if( pDevice->d3dCaps.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT )
                {
                    if( pDevice->d3dCaps.DevCaps&D3DDEVCAPS_PUREDEVICE )
                    {
                        dwBehavior[f] = D3DCREATE_HARDWARE_VERTEXPROCESSING |
                                        D3DCREATE_PUREDEVICE;

                        if( SUCCEEDED( ConfirmDevice( &pDevice->d3dCaps, dwBehavior[f],
                                                      formats[f] ) ) )
                            bFormatConfirmed[f] = TRUE;
                    }

                    if ( FALSE == bFormatConfirmed[f] )
                    {
                        dwBehavior[f] = D3DCREATE_HARDWARE_VERTEXPROCESSING;

                        if( SUCCEEDED( ConfirmDevice( &pDevice->d3dCaps, dwBehavior[f],
                                                      formats[f] ) ) )
                            bFormatConfirmed[f] = TRUE;
                    }

                    if ( FALSE == bFormatConfirmed[f] )
                    {
                        dwBehavior[f] = D3DCREATE_MIXED_VERTEXPROCESSING;

                        if( SUCCEEDED( ConfirmDevice( &pDevice->d3dCaps, dwBehavior[f],
                                                      formats[f] ) ) )
                            bFormatConfirmed[f] = TRUE;
                    }
                }

                // Confirm the device/format for SW vertex processing
                if( FALSE == bFormatConfirmed[f] )
                {
                    dwBehavior[f] = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

                    if( SUCCEEDED( ConfirmDevice( &pDevice->d3dCaps, dwBehavior[f],
                                                  formats[f] ) ) )
                        bFormatConfirmed[f] = TRUE;
                }

                // Find a suitable depth/stencil buffer format for this device/format
                if( bFormatConfirmed[f] && m_bUseDepthBuffer )
                {
                    if( !FindDepthStencilFormat( iAdapter, pDevice->DeviceType,
                        formats[f], &fmtDepthStencil[f] ) )
                    {
                        bFormatConfirmed[f] = FALSE;
                    }
                }
            }

            // Add all enumerated display modes with confirmed formats to the
            // device's list of valid modes
			DWORD m = 0L;
            for( m=0L; m<dwNumModes; m++ )
            {
                for( DWORD f=0; f<dwNumFormats; f++ )
                {
                    if( modes[m].Format == formats[f] )
                    {
                        if( bFormatConfirmed[f] == TRUE )
                        {
                            // Add this mode to the device's list of valid modes
                            pDevice->modes[pDevice->dwNumModes].Width      = modes[m].Width;
                            pDevice->modes[pDevice->dwNumModes].Height     = modes[m].Height;
                            pDevice->modes[pDevice->dwNumModes].Format     = modes[m].Format;
                            pDevice->modes[pDevice->dwNumModes].dwBehavior = dwBehavior[f];
                            pDevice->modes[pDevice->dwNumModes].DepthStencilFormat = fmtDepthStencil[f];
                            pDevice->dwNumModes++;

                            if( pDevice->DeviceType == D3DDEVTYPE_HAL )
                                bHALIsSampleCompatible = TRUE;
                        }
                    }
                }
            }

            // Select any 640x480 mode for default (but prefer a 16-bit mode)
            for( m=0; m<pDevice->dwNumModes; m++ )
            {
                //if( pDevice->modes[m].Width==640 && pDevice->modes[m].Height==480 )
				if( pDevice->modes[m].Width==800 && pDevice->modes[m].Height==600 )
                {
                    pDevice->dwCurrentMode = m;
                    if( pDevice->modes[m].Format == D3DFMT_R5G6B5 ||
                        pDevice->modes[m].Format == D3DFMT_X1R5G5B5 ||
                        pDevice->modes[m].Format == D3DFMT_A1R5G5B5 )
                    {
                        break;
                    }
                }
            }

            {
                pDevice->bCanDoWindowed = TRUE;
                pDevice->bWindowed      = TRUE;
            }

            // If valid modes were found, keep this device
            if( pDevice->dwNumModes > 0 )
                pAdapter->dwNumDevices++;
        }

        // If valid devices were found, keep this adapter
        if( pAdapter->dwNumDevices > 0 )
            m_dwNumAdapters++;
    }

    // Return an error if no compatible devices were found
    if( 0L == m_dwNumAdapters )
        return D3DAPPERR_NOCOMPATIBLEDEVICES;

    // Pick a default device that can render into a window
    // (This code assumes that the HAL device comes before the REF
    // device in the device array).
    for( DWORD a=0; a<m_dwNumAdapters; a++ )
    {
        for( DWORD d=0; d < m_Adapters[a].dwNumDevices; d++ )
        {
            if( m_Adapters[a].devices[d].bWindowed )
            {
                m_Adapters[a].dwCurrentDevice = d;
                m_dwAdapter = a;
				//<*******>
                m_bWindowed = FALSE;

                // Display a warning message
                if( m_Adapters[a].devices[d].DeviceType == D3DDEVTYPE_REF )
                {
                    if( !bHALExists )
                        DisplayErrorMsg( D3DAPPERR_NOHARDWAREDEVICE, MSGWARN_SWITCHEDTOREF );
                    else if( !bHALIsSampleCompatible )
                        DisplayErrorMsg( D3DAPPERR_HALNOTCOMPATIBLE, MSGWARN_SWITCHEDTOREF );
                    else if( !bHALIsWindowedCompatible )
                        DisplayErrorMsg( D3DAPPERR_NOWINDOWEDHAL, MSGWARN_SWITCHEDTOREF );
                    else if( !bHALIsDesktopCompatible )
                        DisplayErrorMsg( D3DAPPERR_NODESKTOPHAL, MSGWARN_SWITCHEDTOREF );
                    else // HAL is desktop compatible, but not sample compatible
                        DisplayErrorMsg( D3DAPPERR_NOHALTHISMODE, MSGWARN_SWITCHEDTOREF );
                }

                return S_OK;
            }
        }
    }

    return D3DAPPERR_NOWINDOWABLEDEVICES;
}




//-----------------------------------------------------------------------------
// Name: FindDepthStencilFormat()
// Desc: Finds a depth/stencil format for the given device that is compatible
//       with the render target format and meets the needs of the app.
//-----------------------------------------------------------------------------
BOOL CD3DApplication::FindDepthStencilFormat( UINT iAdapter, D3DDEVTYPE DeviceType,
    D3DFORMAT TargetFormat, D3DFORMAT* pDepthStencilFormat )
{
    if( m_dwMinDepthBits <= 16 && m_dwMinStencilBits == 0 )
    {
        if( SUCCEEDED( m_pD3D->CheckDeviceFormat( iAdapter, DeviceType,
            TargetFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16 ) ) )
        {
            if( SUCCEEDED( m_pD3D->CheckDepthStencilMatch( iAdapter, DeviceType,
                TargetFormat, TargetFormat, D3DFMT_D16 ) ) )
            {
                *pDepthStencilFormat = D3DFMT_D16;
                return TRUE;
            }
        }
    }

    if( m_dwMinDepthBits <= 15 && m_dwMinStencilBits <= 1 )
    {
        if( SUCCEEDED( m_pD3D->CheckDeviceFormat( iAdapter, DeviceType,
            TargetFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D15S1 ) ) )
        {
            if( SUCCEEDED( m_pD3D->CheckDepthStencilMatch( iAdapter, DeviceType,
                TargetFormat, TargetFormat, D3DFMT_D15S1 ) ) )
            {
                *pDepthStencilFormat = D3DFMT_D15S1;
                return TRUE;
            }
        }
    }

    if( m_dwMinDepthBits <= 24 && m_dwMinStencilBits == 0 )
    {
        if( SUCCEEDED( m_pD3D->CheckDeviceFormat( iAdapter, DeviceType,
            TargetFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X8 ) ) )
        {
            if( SUCCEEDED( m_pD3D->CheckDepthStencilMatch( iAdapter, DeviceType,
                TargetFormat, TargetFormat, D3DFMT_D24X8 ) ) )
            {
                *pDepthStencilFormat = D3DFMT_D24X8;
                return TRUE;
            }
        }
    }

    if( m_dwMinDepthBits <= 24 && m_dwMinStencilBits <= 8 )
    {
        if( SUCCEEDED( m_pD3D->CheckDeviceFormat( iAdapter, DeviceType,
            TargetFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24S8 ) ) )
        {
            if( SUCCEEDED( m_pD3D->CheckDepthStencilMatch( iAdapter, DeviceType,
                TargetFormat, TargetFormat, D3DFMT_D24S8 ) ) )
            {
                *pDepthStencilFormat = D3DFMT_D24S8;
                return TRUE;
            }
        }
    }

    if( m_dwMinDepthBits <= 24 && m_dwMinStencilBits <= 4 )
    {
        if( SUCCEEDED( m_pD3D->CheckDeviceFormat( iAdapter, DeviceType,
            TargetFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X4S4 ) ) )
        {
            if( SUCCEEDED( m_pD3D->CheckDepthStencilMatch( iAdapter, DeviceType,
                TargetFormat, TargetFormat, D3DFMT_D24X4S4 ) ) )
            {
                *pDepthStencilFormat = D3DFMT_D24X4S4;
                return TRUE;
            }
        }
    }

    if( m_dwMinDepthBits <= 32 && m_dwMinStencilBits == 0 )
    {
        if( SUCCEEDED( m_pD3D->CheckDeviceFormat( iAdapter, DeviceType,
            TargetFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D32 ) ) )
        {
            if( SUCCEEDED( m_pD3D->CheckDepthStencilMatch( iAdapter, DeviceType,
                TargetFormat, TargetFormat, D3DFMT_D32 ) ) )
            {
                *pDepthStencilFormat = D3DFMT_D32;
                return TRUE;
            }
        }
    }

    return FALSE;
}


#include <sstream>
extern HWND g_HelpHwnd;
extern HWND g_RegisterHwnd;
//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Message handling function.
//-----------------------------------------------------------------------------
LRESULT CD3DApplication::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                                  LPARAM lParam )
{
    HRESULT hr;
	if( 0 )
	{
		SetSizable( false );
		SetSizable( true );
	}

    switch( uMsg )
    {
	case WM_CREATE:
		{
			/*
			 * 2012.6.25 wangshuai
			 * 为Framework中的d3dapp加上了窗口居中的功能
			 */
			SIZE screenSize = { 0, 0 };
			screenSize.cx = ::GetSystemMetrics(SM_CXSCREEN);
			screenSize.cy = ::GetSystemMetrics(SM_CYSCREEN);

			RECT rcWnd;
			::GetWindowRect(hWnd, &rcWnd);

			rcWnd.left = (screenSize.cx - rcWnd.right) / 2;
			rcWnd.top = (screenSize.cy - rcWnd.bottom) / 2;

			// 窗口居中
			::SetWindowPos(hWnd, NULL, rcWnd.left, rcWnd.top, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED);

			// If an application processes this message
			// it should return zero to continue creation of the window.
			return 0;
		}
		break;

	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

    case WM_PAINT:
        // Handle paint messages when the app is not ready
        if( m_pd3dDevice && !m_bReady )
        {
            if( m_bWindowed )
            {

            }
        }
        break;

    case WM_ACTIVATEAPP:
        m_bHasFocus = (BOOL) wParam;

		if (m_bPauseSIZEMOVE)
		{
			Pause( FALSE );
			m_bPauseSIZEMOVE = FALSE;
			m_bPauseRendering = FALSE;
		}
        if ( !m_bWindowed )
        {
            if ( wParam == TRUE )
            {
                m_bPauseRendering = FALSE;
            }
            else
            {
                m_bPauseRendering = TRUE;
            }
        }

        break;

    case WM_GETMINMAXINFO:
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 100;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 100;
        break;

    case WM_ENTERSIZEMOVE:
        // Halt frame movement while the app is sizing or moving
		if (m_bPauseSIZEMOVE == FALSE)
		{
			Pause( TRUE );
			m_bPauseSIZEMOVE = TRUE;
		}
        m_bPauseRendering = TRUE;
        break;

	case WM_MOVING:
		{
			if (g_HelpHwnd)
			{
				RECT* rect = (RECT*)lParam;
				RECT delta = {rect->left - m_rcOldWindowBoundsBeforeMoving.left,
					rect->top - m_rcOldWindowBoundsBeforeMoving.top,
					rect->right - m_rcOldWindowBoundsBeforeMoving.right,
					rect->bottom - m_rcOldWindowBoundsBeforeMoving.bottom
				};
				m_rcOldWindowBoundsBeforeMoving = *rect;
				GetWindowRect( g_HelpHwnd, &m_rcHelpWindow );
				m_rcHelpWindow.left += delta.left;
				m_rcHelpWindow.top += delta.top;
				m_rcHelpWindow.right += delta.right;
				m_rcHelpWindow.bottom += delta.bottom;
				SetWindowPos( g_HelpHwnd, 0,
					m_rcHelpWindow.left, m_rcHelpWindow.top,
					( m_rcHelpWindow.right - m_rcHelpWindow.left ),
					( m_rcHelpWindow.bottom - m_rcHelpWindow.top ),
					SWP_NOACTIVATE );
				UpdateWindow( g_HelpHwnd );
			}
			else if( g_RegisterHwnd )
			{
				RECT* rect = (RECT*)lParam;
				RECT delta = {rect->left - m_rcOldWindowBoundsBeforeMoving.left,
					rect->top - m_rcOldWindowBoundsBeforeMoving.top,
					rect->right - m_rcOldWindowBoundsBeforeMoving.right,
					rect->bottom - m_rcOldWindowBoundsBeforeMoving.bottom
				};
				m_rcOldWindowBoundsBeforeMoving = *rect;
				RECT rcRegisterWindow;
				GetWindowRect( g_RegisterHwnd, &rcRegisterWindow );
				rcRegisterWindow.left += delta.left;
				rcRegisterWindow.top += delta.top;
				rcRegisterWindow.right += delta.right;
				rcRegisterWindow.bottom += delta.bottom;
				SetWindowPos( g_RegisterHwnd, 0,
					rcRegisterWindow.left, rcRegisterWindow.top,
					( rcRegisterWindow.right - rcRegisterWindow.left ),
					( rcRegisterWindow.bottom - rcRegisterWindow.top ),
					SWP_NOACTIVATE );
				UpdateWindow( g_RegisterHwnd );
			}
			break;
		}
	case WM_KEYUP:
		{
			if (g_HelpHwnd)
			{
				if(IsWindowVisible(g_HelpHwnd))
				{
					switch( wParam )
					{
					case VK_ESCAPE:
						{
							ShowWindow( g_HelpHwnd, SW_HIDE );
						}							
						break;
					}
				}
			}
			else if(g_RegisterHwnd)
			{
				if(IsWindowVisible(g_RegisterHwnd))
				{
					switch( wParam )
					{
					case VK_ESCAPE:
						{
							DestroyWindow(g_RegisterHwnd);
							BringWindowToTop(g_hWnd);
							g_RegisterHwnd = NULL;

						}							
						break;
					}
				}
			}
			return HTCLIENT;
		}	
	case WM_SIZING:
		{
			RECT *pRect = (RECT *) lParam;

			int   width   =   pRect->right - pRect->left;
			int   height   =   pRect->bottom - pRect->top;

			//lrt 1024和768是客户区的大小，offsetwidth,offsetheight是加上窗口和客户区的误差
			int   offsetwidth = (m_rcWindowBounds.right - m_rcWindowBounds.left) - (m_rcWindowClient.right - m_rcWindowClient.left);
			if ( offsetwidth < 0 )
				offsetwidth = 0;
			int   offsetheight = (m_rcWindowBounds.bottom - m_rcWindowBounds.top)  - (m_rcWindowClient.bottom - m_rcWindowClient.top);
			if ( offsetheight < 0 )
				offsetheight = 0;

			static const DWORD MIN_WINDOW_WIDTH = 1024 + offsetwidth;
			static const DWORD MIN_WINDOW_HEIGHT = 768 + offsetheight;
			switch(wParam)  
			{  
			case   WMSZ_BOTTOM:  
				{  
					if   (height   <   MIN_WINDOW_HEIGHT)  
						pRect->bottom   =   pRect->top   +   MIN_WINDOW_HEIGHT;  
					break;  
				}  
			case   WMSZ_LEFT:  
				{  
					if   (width   <   MIN_WINDOW_WIDTH)  
						pRect->left   =   pRect->right   -   MIN_WINDOW_WIDTH;  
					break;  
				}  
			case   WMSZ_RIGHT:  
				{  
					if   (width   <   MIN_WINDOW_WIDTH)  
						pRect->right   =   pRect->left   +   MIN_WINDOW_WIDTH;  
					break;  
				}  
			case   WMSZ_TOP:  
				{  
					if   (height   <   MIN_WINDOW_HEIGHT)  
						pRect->top   =   pRect->bottom   -   MIN_WINDOW_HEIGHT;  
					break;  
				}  
			case   WMSZ_TOPLEFT:  
				{  
					if   (width   <   MIN_WINDOW_WIDTH)  
						pRect->left   =   pRect->right   -   MIN_WINDOW_WIDTH;  
					if   (height   <   MIN_WINDOW_HEIGHT)  
						pRect->top   =   pRect->bottom   -   MIN_WINDOW_HEIGHT;  
					break;  
				}  
			case   WMSZ_TOPRIGHT:  
				{  
					if   (width   <   MIN_WINDOW_WIDTH)  
						pRect->right   =   pRect->left   +   MIN_WINDOW_WIDTH;  
					if   (height   <   MIN_WINDOW_HEIGHT)  
						pRect->top   =   pRect->bottom   -   MIN_WINDOW_HEIGHT;  
					break;  
				}  
			case   WMSZ_BOTTOMLEFT:  
				{  
					if   (width   <   MIN_WINDOW_WIDTH)  
						pRect->left   =   pRect->right   -   MIN_WINDOW_WIDTH;  
					if   (height   <   MIN_WINDOW_HEIGHT)  
						pRect->bottom   =   pRect->top   +   MIN_WINDOW_HEIGHT;  
					break;  
				}  
			case   WMSZ_BOTTOMRIGHT:  
				{  
					if   (width   <   MIN_WINDOW_WIDTH)  
						pRect->right   =   pRect->left   +   MIN_WINDOW_WIDTH;  
					if   (height   <   MIN_WINDOW_HEIGHT)  
						pRect->bottom   =   pRect->top   +   MIN_WINDOW_HEIGHT;  
					break;  
				}  
			}   
			return TRUE;
		}
		break;

    case WM_SIZE:
		{
			if( !m_bInitEnd )
				return false;

			// Check to see if we are losing our window...
			if( SIZE_MAXHIDE==wParam || SIZE_MINIMIZED==wParam )
			{
				if( m_bClipCursorWhenFullscreen && !m_bWindowed )
					ClipCursor( NULL );
				m_bActive = FALSE;
				m_bPauseRendering = TRUE;
                // 最小化
                if( m_bAboveNormalPriority )
                    SetProcessPriority(FALSE);
			}
			else
			{
				m_bActive = TRUE;
				m_bPauseRendering = FALSE;		
				//static bool bFirst = true;
				//if( !bFirst )
				{
					OnSizeWindow( wParam, lParam );						
				}
				//bFirst = false;
			}				
		}
        break;

    case WM_EXITSIZEMOVE:
        Pause( FALSE );
		m_bPauseSIZEMOVE = FALSE;
        m_bPauseRendering = FALSE;

        if( m_bActive && m_bWindowed )
        {
            RECT rcClientOld;
            rcClientOld = m_rcWindowClient;

            // Update window properties
            GetWindowRect( m_hWnd, &m_rcWindowBounds );
            GetClientRect( m_hWnd, &m_rcWindowClient );

            if( rcClientOld.right - rcClientOld.left !=
                m_rcWindowClient.right - m_rcWindowClient.left ||
                rcClientOld.bottom - rcClientOld.top !=
                m_rcWindowClient.bottom - m_rcWindowClient.top)
            {
                // A MeNew window size will require a MeNew backbuffer
                // size, so the 3D structures must be changed accordingly.
                m_bReady = FALSE;

                m_d3dpp.BackBufferWidth  = m_rcWindowClient.right - m_rcWindowClient.left;
                m_d3dpp.BackBufferHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;

                // Resize the 3D environment
                if( FAILED( hr = Resize3DEnvironment() ) )
                {
                    DisplayErrorMsg( D3DAPPERR_RESIZEFAILED, MSGERR_APPMUSTEXIT );
                    return 0;
                }

                m_bReady = TRUE;
            }
        }

        break;
     case WM_MOUSEMOVE:
        if( m_bActive && m_bReady && m_pd3dDevice != NULL && !g_bMouseLeave )
        {
            POINT ptCursor;
            GetCursorPos( &ptCursor );
            if( !m_bWindowed )
                ScreenToClient( m_hWnd, &ptCursor );
            m_pd3dDevice->SetCursorPosition( ptCursor.x, ptCursor.y, 0L );
			char buff[1024];
			sprintf(buff,"移动鼠标：x%d , y:%d\n",ptCursor.x,ptCursor.y);
			OutputDebugString(buff);
        }
        break;

   case WM_ENTERMENULOOP:
        break;

    case WM_EXITMENULOOP:
        break;


    case WM_NCHITTEST:
        // Prevent the user from selecting the menu in fullscreen mode
        if( !m_bWindowed )
            return HTCLIENT;

        break;

    case WM_POWERBROADCAST:
        switch( wParam )
        {
            #ifndef PBT_APMQUERYSUSPEND
                #define PBT_APMQUERYSUSPEND 0x0000
            #endif
            case PBT_APMQUERYSUSPEND:
                // At this point, the app should save any data for open
                // network connections, files, etc., and prepare to go into
                // a suspended mode.
                return TRUE;

            #ifndef PBT_APMRESUMESUSPEND
                #define PBT_APMRESUMESUSPEND 0x0007
            #endif
            case PBT_APMRESUMESUSPEND:
                // At this point, the app should recover any data, network
                // connections, files, etc., and resume running from when
                // the app was suspended.
                return TRUE;
        }
        break;

    case WM_SYSCOMMAND:
		{

			// Prevent moving/sizing and power loss in fullscreen mode
			char buff[1024] ={0};
			sprintf(buff,"%d\n",wParam);
			OutputDebugString(buff);
			//MessageBox(NULL,"",buff,MB_OK);
			switch( wParam )
			{
			case SC_SCREENSAVE:
				m_isScreenSaverRunning = TRUE;
				break;

			case SC_MOVE:
			case SC_SIZE:
			case SC_MAXIMIZE:
			case SC_KEYMENU:
			case SC_MONITORPOWER:
			case 0XF032: //双击标题栏最大化
				if( FALSE == m_bWindowed )
					return 1;
				//lyh++ loadmap的时候进制窗口的最大化操作
				if (m_bWindowed && s_CUI_ID_FRAME_LoadMap.IsVisable())
				{
					return 0;
				}
				break;
			}
		}
      
        break;

    case WM_COMMAND:
        switch( LOWORD(wParam) )
        {
		case IDM_TOGGLEFULLSCREEN:
            // Toggle the fullscreen/window mode
            if( m_bActive && m_bReady )
            {
                Pause( TRUE );
                
                if( FAILED( ToggleFullscreen() ) )
                {
                    DisplayErrorMsg( D3DAPPERR_RESIZEFAILED, MSGERR_APPMUSTEXIT );
                    return 0;
                }

                Pause( FALSE );                        
            }
            return 0;

        case IDM_EXIT:
            // Recieved key/menu command to exit app
            SendMessage( hWnd, WM_USER_CLOSE/*WM_CLOSE*/, 0, 0 );
            return 0;
        }
        break;

	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		{
			if( wParam == VK_MENU )
				return 0;
			if( wParam == VK_F10 )
				return 0;
			if( wParam == VK_F11 )
				return 0;
			if( wParam == VK_F12 )
                return 0;
		}
		break;

    case WM_CLOSE:
        return 0;
    case WM_USER_CLOSE:
        ShowWindow( hWnd, SW_HIDE );
        Cleanup3DEnvironment();
        DestroyMenu( GetMenu(hWnd) );
        DestroyWindow( hWnd );
        PostQuitMessage(0);            
        return 0;
    }

    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: Initialize3DEnvironment()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CD3DApplication::Initialize3DEnvironment()
{
	HRESULT hr;

    D3DAdapterInfo* pAdapterInfo = &m_Adapters[m_dwAdapter];
    D3DDeviceInfo*  pDeviceInfo  = &pAdapterInfo->devices[pAdapterInfo->dwCurrentDevice];
	D3DModeInfo*    pModeInfo    = &pDeviceInfo->modes[pDeviceInfo->dwCurrentMode];
	m_bWindowed = !m_bTrue3D;
	pDeviceInfo->bWindowed = m_bWindowed;
    // Prepare window for possible windowed/fullscreen change
    AdjustWindowForChange();

#if 0
    // Set up the presentation parameters
    ZeroMemory( &m_d3dpp, sizeof(m_d3dpp) );
	//   added 2003.07.26 for toggle full screen
	m_d3dpp.Flags				   = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	m_d3dpp.Windowed               = pDeviceInfo->bWindowed;
	//m_d3dpp.Windowed               = FALSE;
	//m_d3dpp.Windowed               = g_bWindowed;
    m_d3dpp.BackBufferCount        = 1;
    if( pDeviceInfo->bWindowed )
        m_d3dpp.MultiSampleType    = pDeviceInfo->MultiSampleTypeWindowed;
    else
        m_d3dpp.MultiSampleType    = pDeviceInfo->MultiSampleTypeFullscreen;
    m_d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD ;//D3DSWAPEFFECT_DISCARD;D3DSWAPEFFECT_DISCARD;
    m_d3dpp.EnableAutoDepthStencil = m_bUseDepthBuffer;

	//m_d3dpp.AutoDepthStencilFormat = pModeInfo->DepthStencilFormat;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;

    m_d3dpp.hDeviceWindow          = m_hWnd;
    if( m_bWindowed && !m_bChanged )
    {
        m_d3dpp.BackBufferWidth  = m_rcWindowClient.right - m_rcWindowClient.left;
        m_d3dpp.BackBufferHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;
		m_d3dpp.BackBufferFormat = pAdapterInfo->d3ddmDesktop.Format;
    }
    else
    {
        m_d3dpp.BackBufferWidth  = pModeInfo->Width;
        m_d3dpp.BackBufferHeight = pModeInfo->Height;
        m_d3dpp.BackBufferFormat = pModeInfo->Format;
    }

	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if( pDeviceInfo->d3dCaps.PrimitiveMiscCaps & D3DPMISCCAPS_NULLREFERENCE )
    {
        // Warn user about null ref device that can't render anything
        DisplayErrorMsg( D3DAPPERR_NULLREFDEVICE, 0 );
    }
	
	m_pD3D->GetAdapterModeCount( m_BestAdapter, D3DFMT_X8R8G8B8 );
	for( int i=0; i<m_pD3D->GetAdapterModeCount( m_BestAdapter, D3DFMT_X8R8G8B8 ); i++ )
	{
		D3DDISPLAYMODE	DisplayMode;

		m_pD3D->EnumAdapterModes(m_BestAdapter,D3DFMT_X8R8G8B8,i,&DisplayMode);
		if( DisplayMode.Width >= 640 )
		{
			m_DisplayModes.push_back( DisplayMode );
			SystemSetting::Instance()->AddDisplayMode( DisplayMode );
		}
	}

	if( !( pModeInfo->dwBehavior & D3DCREATE_MULTITHREADED ) )
		pModeInfo->dwBehavior |= D3DCREATE_MULTITHREADED;
    // Create the device
    hr = m_pD3D->CreateDevice( m_dwAdapter, pDeviceInfo->DeviceType,
                               m_hWndFocus, pModeInfo->dwBehavior, &m_d3dpp,
                               &m_pd3dDevice );

#else
	// access device via driver
	if (m_pD3D->GetAdapterCount() < 1)
		return D3DERR_INVALIDCALL;

	// Set up the presentation parameters
	D3DDEVTYPE devType = D3DDEVTYPE_HAL;
	UINT adapterNumber = 0;

	// Look for 'NVIDIA NVPerfHUD' adapter (<= v4)
	// or 'NVIDIA PerfHUD' (v5)
	// If it is present, override default settings
	for (UINT adapter=0; adapter < m_pD3D->GetAdapterCount(); ++adapter)
	{
		D3DADAPTER_IDENTIFIER9 identifier;
		HRESULT res;
		res = m_pD3D->GetAdapterIdentifier(adapter,0,&identifier);
		if (strstr(identifier.Description,"PerfHUD") != 0)
		{
			adapterNumber = adapter;
			devType = D3DDEVTYPE_REF;
			break;
		}
	}

	ZeroMemory( &m_d3dpp, sizeof(D3DPRESENT_PARAMETERS) );
	m_d3dpp.Windowed					= m_bWindowed;
	m_d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	// triple buffer if VSync is on
	m_d3dpp.BackBufferCount			= 1;
	m_d3dpp.EnableAutoDepthStencil	= TRUE;
	m_d3dpp.hDeviceWindow			= m_hWnd;
	m_d3dpp.FullScreen_RefreshRateInHz = 0;
	if( m_bWindowed && !m_bChanged )
	{
		m_d3dpp.BackBufferWidth  = m_rcWindowClient.right - m_rcWindowClient.left;
		m_d3dpp.BackBufferHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;
		m_d3dpp.BackBufferFormat = pAdapterInfo->d3ddmDesktop.Format;
	}
	else
	{
		m_d3dpp.BackBufferWidth  = pAdapterInfo->d3ddmDesktop.Width;
		m_d3dpp.BackBufferHeight = pAdapterInfo->d3ddmDesktop.Height;
		m_d3dpp.BackBufferFormat = pAdapterInfo->d3ddmDesktop.Format;
		m_d3dpp.FullScreen_RefreshRateInHz = pAdapterInfo->d3ddmDesktop.RefreshRate;

	}

	/*if( GetMe3dConfig()->IsVSync() )
		m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	else*/
		m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Try to create a 32-bit depth, 8-bit stencil
	if( FAILED( m_pD3D->CheckDeviceFormat(adapterNumber,
		devType,  m_d3dpp.BackBufferFormat,  D3DUSAGE_DEPTHSTENCIL, 
		D3DRTYPE_SURFACE, D3DFMT_D24S8 )))
	{
		// Bugger, no 8-bit hardware stencil, just try 32-bit zbuffer 
		if( FAILED( m_pD3D->CheckDeviceFormat(adapterNumber,
			devType,  m_d3dpp.BackBufferFormat,  D3DUSAGE_DEPTHSTENCIL, 
			D3DRTYPE_SURFACE, D3DFMT_D32 )))
		{
			// Jeez, what a naff card. Fall back on 16-bit depth buffering
			m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		}
		else
			m_d3dpp.AutoDepthStencilFormat = D3DFMT_D32;
	}
	else
	{
		// Woohoo!
		if( SUCCEEDED( m_pD3D->CheckDepthStencilMatch(adapterNumber, devType,
			m_d3dpp.BackBufferFormat, m_d3dpp.BackBufferFormat, D3DFMT_D24S8)))
		{
			m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; 
		} 
		else 
			m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8; 
	}
	for( UINT iMode=0; iMode < m_pD3D->GetAdapterModeCount( adapterNumber, D3DFMT_X8R8G8B8 ); iMode++ )
	{
		D3DDISPLAYMODE displayMode;
		m_pD3D->EnumAdapterModes( adapterNumber, D3DFMT_X8R8G8B8, iMode, &displayMode );

		if( displayMode.Width >= 1024 && displayMode.Width > displayMode.Height )
		{
			m_DisplayModes.push_back( displayMode );
			SystemSetting::Instance()->AddDisplayMode( displayMode );
		}
	}

	D3DMULTISAMPLE_TYPE FSAAType = D3DMULTISAMPLE_NONE;
	DWORD FSAAQuality = 0;
	int nLevel = D3DMULTISAMPLE_2_SAMPLES;//SystemSetting::Instance()->GetLevel( SystemSetting::eSSC_MSAA );
	bool bD3dSupport = false;

	/*
	for( UINT iMode=0; iMode < m_pD3D->GetAdapterModeCount( adapterNumber, D3DFMT_X8R8G8B8 ); iMode++ )
	{
		D3DDISPLAYMODE displayMode;
		m_pD3D->EnumAdapterModes( adapterNumber, D3DFMT_X8R8G8B8, iMode, &displayMode );

		// Filter out low-resolutions
		if( displayMode.Width != m_dwCreationWidth || displayMode.Height != m_dwCreationHeight )// modified, jiayi, [2009.4.17]
			continue;

		// get non maskable FSAA for this VMODE
		DWORD numLevels = 0;
		HRESULT hr;
		SystemSetting::Instance()->AddFSAAType( 0 );		
		for( int iSampleCount = 2 ; iSampleCount <= 16 ; iSampleCount++ )
		{
			hr = m_pD3D->CheckDeviceMultiSampleType( 
				adapterNumber, 
				D3DDEVTYPE_HAL, 
				displayMode.Format, 
				!m_bWindowed, 
				(D3DMULTISAMPLE_TYPE)iSampleCount, 
				&numLevels);

			numLevels -= 1;

			bool bOK = SUCCEEDED(hr);
			if (bOK && numLevels >= 0)
			{
				SystemSetting::Instance()->AddFSAAType( iSampleCount );	
				if( iSampleCount == nLevel )
					bD3dSupport = true;
			}
		}	
	}
	*/

	int msaaLevel = SystemSetting::Instance()->GetLevel(SystemSetting::eSSC_MSAA);
	m_d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE) msaaLevel;
	m_d3dpp.MultiSampleQuality = 0;

	D3DCAPS9 caps;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	GetBestAvailableMultiSampleType(m_pD3D);

	if (!m_pd3dDevice)
	{
		// We haven't created the device yet, this must be the first time
		DWORD extraFlags = 0;
		extraFlags |= D3DCREATE_MULTITHREADED;

		hr = m_pD3D->CreateDevice( adapterNumber, devType, m_hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING | extraFlags , &m_d3dpp, &m_pd3dDevice );
		if (FAILED(hr))
		{
			// Try a second time, may fail the first time due to back buffer count,
			// which will be corrected down to 1 by the runtime
			hr = m_pD3D->CreateDevice( adapterNumber, devType, m_hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | extraFlags, &m_d3dpp, &m_pd3dDevice );
		}
		if( FAILED( hr ) )
		{
			hr = m_pD3D->CreateDevice( adapterNumber, devType, m_hWnd,
				D3DCREATE_MIXED_VERTEXPROCESSING | extraFlags, &m_d3dpp, &m_pd3dDevice );
			if( FAILED( hr ) )
			{
				hr = m_pD3D->CreateDevice( adapterNumber, devType, m_hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | extraFlags, &m_d3dpp, &m_pd3dDevice );
			}
		}
	}
#endif

	m_bChanged = FALSE;
    if( SUCCEEDED(hr) )
    {
        if( m_bWindowed )
        {
			// 马上显示窗口 [11/29/2010 zhangjiayi]
            SetWindowPos( m_hWnd, HWND_NOTOPMOST,
                          m_rcWindowBounds.left, m_rcWindowBounds.top,
                          ( m_rcWindowBounds.right - m_rcWindowBounds.left ),
                          ( m_rcWindowBounds.bottom - m_rcWindowBounds.top ),
                          /*SWP_HIDEWINDOW*/SWP_SHOWWINDOW );
        }

        // Store device Caps
        m_pd3dDevice->GetDeviceCaps( &m_d3dCaps );

		// added, jiayi, [2009/6/19]
		// 由于不能准确的判定显卡性能，比如gpu，带宽等信息
		// 无法取到，所以我们这里判断shader版本，这是是随
		// gpu的提高而增加的，所以可以相对准确的判断显卡性能
		if( m_d3dCaps.VertexShaderVersion < D3DVS_VERSION( 3, 0 ) || 
			m_d3dCaps.PixelShaderVersion < D3DPS_VERSION( 3, 0 ) )
		{
			/*m_bLowLevelVideoCard = true;*/
			MeLog::Instance()->Print("VS | PS版本小于3.0");
			// 现在这里判断不准确, 改用另一个函数来判断
			//SystemSetting::Instance()->SetLowLevelCard( true );
		}

		// added, jiayi, [2009/9/26]
		// 显卡最低要求为vs,ps >= 2.0, 如果不符合，关闭客户端
		if( m_d3dCaps.VertexShaderVersion <= D3DVS_VERSION( 1, 0 ) ||
			m_d3dCaps.PixelShaderVersion  <= D3DVS_VERSION( 1, 0 ) )
		{
			::MessageBoxA( m_hWnd, theXmlString.GetString( eError_VideoCardToSlow ), "", MB_OK | MB_TOPMOST );
			::TerminateProcess( ::GetCurrentProcess(), 0 );			
		}

        m_dwCreateFlags = pModeInfo->dwBehavior;

        if( pDeviceInfo->DeviceType == D3DDEVTYPE_HAL )
        {
            lstrcpy( m_strDeviceStats, pAdapterInfo->d3dAdapterIdentifier.Description );			
			GetMe3dConfig()->SetCardType( eATI_Card );
			
        }

        // Set up the fullscreen cursor
        if( m_bShowCursorWhenFullscreen && !m_bWindowed )
        {
            HCURSOR hCursor;
#ifdef _W64
            hCursor = (HCURSOR)(DWORD_PTR)GetClassLongPtr( m_hWnd, GCLP_HCURSOR );
#else
            hCursor = (HCURSOR)(DWORD_PTR)GetClassLong( m_hWnd, GCL_HCURSOR );
#endif
            D3DUtil_SetDeviceCursor( m_pd3dDevice, hCursor, TRUE );
            m_pd3dDevice->ShowCursor( TRUE );
        }

        // Confine cursor to fullscreen window
        if( m_bClipCursorWhenFullscreen )
        {
            if (!m_bWindowed )
            {
                RECT rcWindow;
                GetWindowRect( m_hWnd, &rcWindow );
                ClipCursor( &rcWindow );
            }
            else
            {
                ClipCursor( NULL );
            }
        }

        // Initialize the app's device-dependent objects
        hr = InitDeviceObjects();
        if( hr == S_OK )
        {
            hr = RestoreDeviceObjects();
            if( hr == S_OK )
            {
                m_bActive = TRUE;
                return S_OK;
            }
        }

		// 是否是低端显卡 
		SystemSetting::Instance()->SetLowLevelCard(IsBadVideoCard(m_pD3D, m_pDDobject));

        // Cleanup before we try again
        InvalidateDeviceObjects();
        DeleteDeviceObjects();
        SAFE_RELEASE( m_pd3dDevice );
    }

    // If that failed, fall back to the reference rasterizer
    if( pDeviceInfo->DeviceType == D3DDEVTYPE_HAL )
    {
        // Select the default adapter
        m_dwAdapter = 0L;
        pAdapterInfo = &m_Adapters[m_dwAdapter];

        // Look for a software device
        for( UINT i=0L; i<pAdapterInfo->dwNumDevices; i++ )
        {
            if( pAdapterInfo->devices[i].DeviceType == D3DDEVTYPE_REF )
            {
                pAdapterInfo->dwCurrentDevice = i;
                pDeviceInfo = &pAdapterInfo->devices[i];
                m_bWindowed = pDeviceInfo->bWindowed;
                break;
            }
        }

        // Try again, this time with the reference rasterizer
        if( pAdapterInfo->devices[pAdapterInfo->dwCurrentDevice].DeviceType ==
            D3DDEVTYPE_REF )
        {
            // Make sure main window isn't topmost, so error message is visible
            SetWindowPos( m_hWnd, HWND_NOTOPMOST,
                          m_rcWindowBounds.left, m_rcWindowBounds.top,
                          ( m_rcWindowBounds.right - m_rcWindowBounds.left ),
                          ( m_rcWindowBounds.bottom - m_rcWindowBounds.top ),
                          SWP_HIDEWINDOW );
            AdjustWindowForChange();

            // Let the user know we are switching from HAL to the reference rasterizer
            DisplayErrorMsg( hr, MSGWARN_SWITCHEDTOREF );

            hr = Initialize3DEnvironment();
        }
    }
	
    return hr;
}

//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CD3DApplication::Resize3DEnvironment()
{
    HRESULT hr;

    // Release all vidmem objects
    if( FAILED( hr = InvalidateDeviceObjects() ) )
        return hr;

    // Reset the device
    if( FAILED( hr = m_pd3dDevice->Reset( &m_d3dpp ) ) )
        return hr;

    // Set up the fullscreen cursor
    if( m_bShowCursorWhenFullscreen && !m_bWindowed )
    {
        HCURSOR hCursor;
#ifdef _W64
        hCursor = (HCURSOR)(DWORD_PTR)GetClassLongPtr( m_hWnd, GCLP_HCURSOR );
#else
        hCursor = (HCURSOR)(DWORD_PTR)GetClassLong( m_hWnd, GCL_HCURSOR );
#endif
        D3DUtil_SetDeviceCursor( m_pd3dDevice, hCursor, TRUE );
        m_pd3dDevice->ShowCursor( TRUE );
    }

    // Confine cursor to fullscreen window
    if( m_bClipCursorWhenFullscreen )
    {
        if (!m_bWindowed )
        {
            RECT rcWindow;
            GetWindowRect( m_hWnd, &rcWindow );
            ClipCursor( &rcWindow );
        }
        else
        {
            ClipCursor( NULL );
        }
    }

    // Initialize the app's device-dependent objects
    hr = RestoreDeviceObjects();
    if( FAILED(hr) )
        return hr;

    // If the app is paused, trigger the rendering of the current frame
    if( FALSE == m_bFrameMoving )
    {
        m_bSingleStep = TRUE;
        DXUtil_Timer( TIMER_START );
        DXUtil_Timer( TIMER_STOP );
    }

    m_isDeviceLost = FALSE;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: ToggleFullScreen()
// Desc: Called when user toggles between fullscreen mode and windowed mode
//-----------------------------------------------------------------------------
HRESULT CD3DApplication::ToggleFullscreen()
{
    // Get access to current adapter, device, and mode
    D3DAdapterInfo* pAdapterInfo = &m_Adapters[m_dwAdapter];
    D3DDeviceInfo*  pDeviceInfo  = &pAdapterInfo->devices[pAdapterInfo->dwCurrentDevice];
    D3DModeInfo*    pModeInfo    = &pDeviceInfo->modes[pDeviceInfo->dwCurrentMode];

    // Need device change if going windowed and the current device
    // can only be fullscreen
    if( !m_bWindowed && !pDeviceInfo->bCanDoWindowed )
        return ForceWindowed();

    m_bReady = FALSE;

    // Toggle the windowed state
    m_bWindowed = !m_bWindowed;
    pDeviceInfo->bWindowed = m_bWindowed;

    // Prepare window for windowed/fullscreen change
    AdjustWindowForChange();

    // Set up the presentation parameters
    m_d3dpp.Windowed               = pDeviceInfo->bWindowed;
    if( m_bWindowed )
        m_d3dpp.MultiSampleType    = pDeviceInfo->MultiSampleTypeWindowed;
    else
        m_d3dpp.MultiSampleType    = pDeviceInfo->MultiSampleTypeFullscreen;

	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;

    m_d3dpp.hDeviceWindow          = m_hWnd;
    if( m_bWindowed )
    {
        m_d3dpp.BackBufferWidth  = m_rcWindowClient.right - m_rcWindowClient.left;
        m_d3dpp.BackBufferHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;
        m_d3dpp.BackBufferFormat = pAdapterInfo->d3ddmDesktop.Format;
    }
    else
    {
        m_d3dpp.BackBufferWidth  = pModeInfo->Width;
        m_d3dpp.BackBufferHeight = pModeInfo->Height;
        m_d3dpp.BackBufferFormat = pModeInfo->Format;
    }

    // Resize the 3D device
    if( FAILED( Resize3DEnvironment() ) )
    {
        if( m_bWindowed )
            return ForceWindowed();
        else
            return E_FAIL;
    }
	//
    if( m_bWindowed )
    {
        SetWindowPos( m_hWnd, HWND_NOTOPMOST,
                      m_rcWindowBounds.left, m_rcWindowBounds.top,
                      ( m_rcWindowBounds.right - m_rcWindowBounds.left ),
                      ( m_rcWindowBounds.bottom - m_rcWindowBounds.top ),
                      SWP_HIDEWINDOW );
    }

    m_bReady = TRUE;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: ForceWindowed()
// Desc: Switch to a windowed mode, even if that means picking a MeNew device
//       and/or adapter
//-----------------------------------------------------------------------------
HRESULT CD3DApplication::ForceWindowed()
{
    HRESULT hr;
    D3DAdapterInfo* pAdapterInfoCur = &m_Adapters[m_dwAdapter];
    D3DDeviceInfo*  pDeviceInfoCur  = &pAdapterInfoCur->devices[pAdapterInfoCur->dwCurrentDevice];
    BOOL bFoundDevice = FALSE;

    if( pDeviceInfoCur->bCanDoWindowed )
    {
        bFoundDevice = TRUE;
    }
    else
    {
        // Look for a windowable device on any adapter
        D3DAdapterInfo* pAdapterInfo;
        DWORD dwAdapter;
        D3DDeviceInfo* pDeviceInfo;
        DWORD dwDevice;
        for( dwAdapter = 0; dwAdapter < m_dwNumAdapters; dwAdapter++ )
        {
            pAdapterInfo = &m_Adapters[dwAdapter];
            for( dwDevice = 0; dwDevice < pAdapterInfo->dwNumDevices; dwDevice++ )
            {
                pDeviceInfo = &pAdapterInfo->devices[dwDevice];
                if( pDeviceInfo->bCanDoWindowed )
                {
                    m_dwAdapter = dwAdapter;
                    pDeviceInfoCur = pDeviceInfo;
                    pAdapterInfo->dwCurrentDevice = dwDevice;
                    bFoundDevice = TRUE;
                    break;
                }
            }
            if( bFoundDevice )
                break;
        }
    }

    if( !bFoundDevice )
        return E_FAIL;

    pDeviceInfoCur->bWindowed = TRUE;
    m_bWindowed = TRUE;

    // Now destroy the current 3D device objects, then reinitialize

    m_bReady = FALSE;

    // Release all scene objects that will be re-created for the MeNew device
    InvalidateDeviceObjects();
    DeleteDeviceObjects();

    // Release display objects, so a MeNew device can be created
    if( m_pd3dDevice->Release() > 0L )
        return DisplayErrorMsg( D3DAPPERR_NONZEROREFCOUNT, MSGERR_APPMUSTEXIT );

    // Create the MeNew device
    if( FAILED( hr = Initialize3DEnvironment() ) )
        return DisplayErrorMsg( hr, MSGERR_APPMUSTEXIT );
    m_bReady = TRUE;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: AdjustWindowForChange()
// Desc: Prepare the window for a possible change between windowed mode and
//       fullscreen mode.  This function is virtual and thus can be overridden
//       to provide different behavior, such as switching to an entirely
//       different window for fullscreen mode (as in the MFC sample apps).
//-----------------------------------------------------------------------------
HRESULT CD3DApplication::AdjustWindowForChange()
{
	if( m_bWindowed )
    {
        // Set windowed-mode style
        SetWindowLong( m_hWnd, GWL_STYLE, m_dwWindowStyle );
    }
    else
    {
        // Set fullscreen-mode style
        SetWindowLong( m_hWnd, GWL_STYLE, WS_POPUP|WS_SYSMENU|WS_VISIBLE );
    }
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: UserSelectNewDevice()
// Desc: Displays a dialog so the user can select a MeNew adapter, device, or
//       display mode, and then recreates the 3D environment if needed
//-----------------------------------------------------------------------------
HRESULT CD3DApplication::UserSelectNewDevice()
{
    HRESULT hr;

    // Can't display dialogs in fullscreen mode
    if( m_bWindowed == FALSE )
    {
        if( FAILED( ToggleFullscreen() ) )
        {
            DisplayErrorMsg( D3DAPPERR_RESIZEFAILED, MSGERR_APPMUSTEXIT );
            return E_FAIL;
        }
    }

    // Prompt the user to change the mode
    if( IDOK != DialogBoxParam( (HINSTANCE)GetModuleHandle(NULL),
                                MAKEINTRESOURCE(IDD_SELECTDEVICE), m_hWnd,
                                SelectDeviceProc, (LPARAM)this ) )
        return S_OK;

    // Get access to the newly selected adapter, device, and mode
    DWORD dwDevice;
    dwDevice  = m_Adapters[m_dwAdapter].dwCurrentDevice;
    m_bWindowed = m_Adapters[m_dwAdapter].devices[dwDevice].bWindowed;

    // Release all scene objects that will be re-created for the MeNew device
    InvalidateDeviceObjects();
    DeleteDeviceObjects();

    // Release display objects, so a MeNew device can be created
    if( m_pd3dDevice->Release() > 0L )
        return DisplayErrorMsg( D3DAPPERR_NONZEROREFCOUNT, MSGERR_APPMUSTEXIT );

    // Inform the display class of the change. It will internally
    // re-create valid surfaces, a d3ddevice, etc.
    if( FAILED( hr = Initialize3DEnvironment() ) )
        return DisplayErrorMsg( hr, MSGERR_APPMUSTEXIT );

    // If the app is paused, trigger the rendering of the current frame
    if( FALSE == m_bFrameMoving )
    {
        m_bSingleStep = TRUE;
        DXUtil_Timer( TIMER_START );
        DXUtil_Timer( TIMER_STOP );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SelectDeviceProc()
// Desc: Windows message handling function for the device select dialog
//-----------------------------------------------------------------------------
INT_PTR CALLBACK CD3DApplication::SelectDeviceProc( HWND hDlg, UINT msg,
                                                    WPARAM wParam, LPARAM lParam )
{
    // Get access to the UI controls
    HWND hwndAdapterList        = GetDlgItem( hDlg, IDC_ADAPTER_COMBO );
    HWND hwndDeviceList         = GetDlgItem( hDlg, IDC_DEVICE_COMBO );
    HWND hwndFullscreenModeList = GetDlgItem( hDlg, IDC_FULLSCREENMODES_COMBO );
    HWND hwndWindowedRadio      = GetDlgItem( hDlg, IDC_WINDOW );
    HWND hwndFullscreenRadio    = GetDlgItem( hDlg, IDC_FULLSCREEN );
    HWND hwndMultiSampleList    = GetDlgItem( hDlg, IDC_MULTISAMPLE_COMBO );
    BOOL bUpdateDlgControls     = FALSE;

    // Static state for adapter/device/mode selection
    static CD3DApplication* pd3dApp;
    static DWORD  dwOldAdapter, dwNewAdapter;
    static DWORD  dwOldDevice,  dwNewDevice;
    static DWORD  dwOldMode,    dwNewMode;
    static BOOL   bOldWindowed, bNewWindowed;
    static D3DMULTISAMPLE_TYPE OldMultiSampleTypeWindowed, NewMultiSampleTypeWindowed;
    static D3DMULTISAMPLE_TYPE OldMultiSampleTypeFullscreen, NewMultiSampleTypeFullscreen;

    // Working variables
    D3DAdapterInfo* pAdapter;
    D3DDeviceInfo*  pDevice;

    // Handle the initialization message
    if( WM_INITDIALOG == msg )
    {
        // Old state
        pd3dApp      = (CD3DApplication*)lParam;
        dwOldAdapter = pd3dApp->m_dwAdapter;
        pAdapter     = &pd3dApp->m_Adapters[dwOldAdapter];

        dwOldDevice  = pAdapter->dwCurrentDevice;
        pDevice      = &pAdapter->devices[dwOldDevice];

        dwOldMode    = pDevice->dwCurrentMode;
        bOldWindowed = pDevice->bWindowed;
        OldMultiSampleTypeWindowed = pDevice->MultiSampleTypeWindowed;
        OldMultiSampleTypeFullscreen = pDevice->MultiSampleTypeFullscreen;

        // New state is initially the same as the old state
        dwNewAdapter = dwOldAdapter;
        dwNewDevice  = dwOldDevice;
        dwNewMode    = dwOldMode;
        bNewWindowed = bOldWindowed;
        NewMultiSampleTypeWindowed = OldMultiSampleTypeWindowed;
        NewMultiSampleTypeFullscreen = OldMultiSampleTypeFullscreen;

        // Set flag to update dialog controls below
        bUpdateDlgControls = TRUE;
    }

    if( WM_COMMAND == msg )
    {
        // Get current UI state
        bNewWindowed  = Button_GetCheck( hwndWindowedRadio );

        if( IDOK == LOWORD(wParam) )
        {
            // Handle the case when the user hits the OK button. Check if any
            // of the options were changed
            if( dwNewAdapter != dwOldAdapter || dwNewDevice  != dwOldDevice  ||
                dwNewMode    != dwOldMode    || bNewWindowed != bOldWindowed ||
                NewMultiSampleTypeWindowed != OldMultiSampleTypeWindowed ||
                NewMultiSampleTypeFullscreen != OldMultiSampleTypeFullscreen )
            {
                pd3dApp->m_dwAdapter = dwNewAdapter;

                pAdapter = &pd3dApp->m_Adapters[dwNewAdapter];
                pAdapter->dwCurrentDevice = dwNewDevice;

                pAdapter->devices[dwNewDevice].dwCurrentMode = dwNewMode;
                pAdapter->devices[dwNewDevice].bWindowed     = bNewWindowed;
                pAdapter->devices[dwNewDevice].MultiSampleTypeWindowed = NewMultiSampleTypeWindowed;
                pAdapter->devices[dwNewDevice].MultiSampleTypeFullscreen = NewMultiSampleTypeFullscreen;

                EndDialog( hDlg, IDOK );
            }
            else
                EndDialog( hDlg, IDCANCEL );

            return TRUE;
        }
        else if( IDCANCEL == LOWORD(wParam) )
        {
            // Handle the case when the user hits the Cancel button
            EndDialog( hDlg, IDCANCEL );
            return TRUE;
        }
        else if( CBN_SELENDOK == HIWORD(wParam) )
        {
            if( LOWORD(wParam) == IDC_ADAPTER_COMBO )
            {
                dwNewAdapter = ComboBox_GetCurSel( hwndAdapterList );
                pAdapter     = &pd3dApp->m_Adapters[dwNewAdapter];

                dwNewDevice  = pAdapter->dwCurrentDevice;
                dwNewMode    = pAdapter->devices[dwNewDevice].dwCurrentMode;
                bNewWindowed = pAdapter->devices[dwNewDevice].bWindowed;
            }
            else if( LOWORD(wParam) == IDC_DEVICE_COMBO )
            {
                pAdapter     = &pd3dApp->m_Adapters[dwNewAdapter];

                dwNewDevice  = ComboBox_GetCurSel( hwndDeviceList );
                dwNewMode    = pAdapter->devices[dwNewDevice].dwCurrentMode;
                bNewWindowed = pAdapter->devices[dwNewDevice].bWindowed;
            }
            else if( LOWORD(wParam) == IDC_FULLSCREENMODES_COMBO )
            {
                dwNewMode = ComboBox_GetCurSel( hwndFullscreenModeList );
            }
            else if( LOWORD(wParam) == IDC_MULTISAMPLE_COMBO )
            {
                DWORD dwItem = ComboBox_GetCurSel( hwndMultiSampleList );
                if( bNewWindowed )
                    NewMultiSampleTypeWindowed = (D3DMULTISAMPLE_TYPE)ComboBox_GetItemData( hwndMultiSampleList, dwItem );
                else
                    NewMultiSampleTypeFullscreen = (D3DMULTISAMPLE_TYPE)ComboBox_GetItemData( hwndMultiSampleList, dwItem );
            }
        }
        // Keep the UI current
        bUpdateDlgControls = TRUE;
    }

    // Update the dialog controls
    if( bUpdateDlgControls )
    {
        // Reset the content in each of the combo boxes
        ComboBox_ResetContent( hwndAdapterList );
        ComboBox_ResetContent( hwndDeviceList );
        ComboBox_ResetContent( hwndFullscreenModeList );
        ComboBox_ResetContent( hwndMultiSampleList );

        pAdapter = &pd3dApp->m_Adapters[dwNewAdapter];
        pDevice  = &pAdapter->devices[dwNewDevice];

        // Add a list of adapters to the adapter combo box
        for( DWORD a=0; a < pd3dApp->m_dwNumAdapters; a++ )
        {
            // Add device name to the combo box
            DWORD dwItem = ComboBox_AddString( hwndAdapterList,
                             pd3dApp->m_Adapters[a].d3dAdapterIdentifier.Description );

            // Set the item data to identify this adapter
            ComboBox_SetItemData( hwndAdapterList, dwItem, a );

            // Set the combobox selection on the current adapater
            if( a == dwNewAdapter )
                ComboBox_SetCurSel( hwndAdapterList, dwItem );
        }

        // Add a list of devices to the device combo box
        for( DWORD d=0; d < pAdapter->dwNumDevices; d++ )
        {
            // Add device name to the combo box
            DWORD dwItem = ComboBox_AddString( hwndDeviceList,
                                               pAdapter->devices[d].strDesc );

            // Set the item data to identify this device
            ComboBox_SetItemData( hwndDeviceList, dwItem, d );

            // Set the combobox selection on the current device
            if( d == dwNewDevice )
                ComboBox_SetCurSel( hwndDeviceList, dwItem );
        }

        // Add a list of modes to the mode combo box
		DWORD m = 0;
        for( m=0; m < pDevice->dwNumModes; m++ )
        {
            DWORD BitDepth = 16;
            if( pDevice->modes[m].Format == D3DFMT_X8R8G8B8 ||
                pDevice->modes[m].Format == D3DFMT_A8R8G8B8 ||
                pDevice->modes[m].Format == D3DFMT_R8G8B8 )
            {
                BitDepth = 32;
            }

            // Add mode desc to the combo box
            TCHAR strMode[80];
            _stprintf( strMode, _T("%ld x %ld x %ld"), pDevice->modes[m].Width,
                                                       pDevice->modes[m].Height,
                                                       BitDepth );
            DWORD dwItem = ComboBox_AddString( hwndFullscreenModeList, strMode );

            // Set the item data to identify this mode
            ComboBox_SetItemData( hwndFullscreenModeList, dwItem, m );

            // Set the combobox selection on the current mode
            if( m == dwNewMode )
                ComboBox_SetCurSel( hwndFullscreenModeList, dwItem );
        }

        // Add a list of multisample modes to the multisample combo box
        for( m=0; m <= 16; m++ )
        {
            TCHAR strDesc[50];

            D3DFORMAT fmt;
            if( bNewWindowed )
                fmt = pd3dApp->m_Adapters[dwNewAdapter].d3ddmDesktop.Format;
            else
                fmt = pDevice->modes[dwNewMode].Format;

            if ( m == 1 ) // 1 is not a valid multisample type
                continue;

            if( SUCCEEDED( pd3dApp->m_pD3D->CheckDeviceMultiSampleType( dwNewAdapter,
                pDevice->DeviceType, fmt, bNewWindowed, (D3DMULTISAMPLE_TYPE)m, NULL ) ) )
            {
                if( m == 0 )
                    lstrcpy( strDesc, _T("none") );
                else
                    wsprintf( strDesc, _T("%d samples"), m );

                // Add device name to the combo box
                DWORD dwItem = ComboBox_AddString( hwndMultiSampleList, strDesc );

                // Set the item data to identify this multisample type
                ComboBox_SetItemData( hwndMultiSampleList, dwItem, m );

                // Set the combobox selection on the current multisample type
                if( bNewWindowed )
                {
                    if( (D3DMULTISAMPLE_TYPE)m == NewMultiSampleTypeWindowed || m == 0 )
                        ComboBox_SetCurSel( hwndMultiSampleList, dwItem );
                }
                else
                {
                    if( (D3DMULTISAMPLE_TYPE)m == NewMultiSampleTypeFullscreen || m == 0 )
                        ComboBox_SetCurSel( hwndMultiSampleList, dwItem );
                }
            }
        }
        DWORD dwItem = ComboBox_GetCurSel( hwndMultiSampleList );
        if( bNewWindowed )
            NewMultiSampleTypeWindowed = (D3DMULTISAMPLE_TYPE)ComboBox_GetItemData( hwndMultiSampleList, dwItem );
        else
            NewMultiSampleTypeFullscreen = (D3DMULTISAMPLE_TYPE)ComboBox_GetItemData( hwndMultiSampleList, dwItem );
        EnableWindow( hwndMultiSampleList, ComboBox_GetCount( hwndMultiSampleList ) > 1);
        EnableWindow( hwndWindowedRadio, pDevice->bCanDoWindowed );

        if( bNewWindowed )
        {
            Button_SetCheck( hwndWindowedRadio,   TRUE );
            Button_SetCheck( hwndFullscreenRadio, FALSE );
            EnableWindow( hwndFullscreenModeList, FALSE );
        }
        else
        {
            Button_SetCheck( hwndWindowedRadio,   FALSE );
            Button_SetCheck( hwndFullscreenRadio, TRUE );
            EnableWindow( hwndFullscreenModeList, TRUE );
        }
        return TRUE;
    }

    return FALSE;
}



#ifdef _DEBUG
#define LOAD_COST_TIME_DEBUG 0
#else
#define LOAD_COST_TIME_DEBUG 0
#endif //_DEBUG

//-----------------------------------------------------------------------------
// Name: Run()
// Desc:
//-----------------------------------------------------------------------------
INT CD3DApplication::Run()
{
    // Load keyboard accelerators
//    HACCEL hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

    // Now we're ready to recieve and process Windows messages.
    BOOL bGotMsg;
    MSG  msg;
    msg.message = WM_NULL;
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
	FLOAT m_timeTotal			= 0.0f;
	FLOAT m_nextFrameWaitTime	= GetMe3dConfig()->GetKeepFPS()>0 ? 1.f/GetMe3dConfig()->GetKeepFPS() : 0.f;
	FLOAT m_nextFrameTime		= m_nextFrameWaitTime;

    while( WM_QUIT != msg.message  )
    {
#if LOAD_COST_TIME_DEBUG
		DWORD time_cost = HQ_TimeGetTime() ;
#endif

        // Use PeekMessage() if the app is active, so we can use idle time to
        // render the scene. Else, use GetMessage() to avoid eating CPU time.
		bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );

        if( bGotMsg )
        {           
			TranslateMessage( &msg );
			DispatchMessage( &msg );  
        }
        else
        {
            //////////////////////////////////////////////////////////////////////////
            //一定要在 Frame的开始UpdateMsg. To Human
            //处理系统消息
			BeginGuard
            UpdateNet();
			EndGuard

            // Render a frame during idle time (no messages are waiting)
            if(m_bReady )
            {
				bool bSkipFrame = false;
				// 更新时间
				m_timeTotal = DXUtil_Timer( TIMER_GETAPPTIME );

				SlowCPU();
                // 锁帧判断
                bool bNeedLockFPS = false;
                float fLockFPS = 0;
                // 如果窗口非激活且非最小化并帧数降低，则锁到10帧
                if( m_bActive )
                {
                    if( GetActiveWindow() != g_hWnd )
                    {
                        bNeedLockFPS = true;
                        fLockFPS = 30.f;
                    }
                }
				// 是否UI设置锁帧
				if( !bNeedLockFPS && GetMe3dConfig()->IsLockFPS() )
				{
                    bNeedLockFPS = true;
                    fLockFPS = (float)GetMe3dConfig()->GetKeepFPS();
                }

                // 计算锁帧每帧延时
                if( bNeedLockFPS && fLockFPS > 0 )
                {
					m_nextFrameWaitTime = 1.f / fLockFPS;
					if( m_timeTotal < m_nextFrameTime )
					{
						// 时间没到
						// 等待时间超过2ms，则睡眠1ms，降低CPU占用时间
						if( m_nextFrameTime - m_timeTotal > 0.002f )
						{
							Sleep(1);
						}
						bSkipFrame = true;
					}
				}

                if( !bSkipFrame )
				{
					// 计算下一帧的理论时间
					while ( m_nextFrameTime <= m_timeTotal )
					{
						m_nextFrameTime += m_nextFrameWaitTime;
					}

					Render3DEnvironment();
					
				}
            }
			
			/*
			 * Author: 2012-9-4 21:26:18 wangshuai
			 * Desc:   修正了屏保退出后帧数下降至10以下的问题
			 */
		/*	if (m_isScreenSaverRunning)
			{
				BOOL isScreenSaverActive = FALSE;
				::SystemParametersInfo(SPI_GETSCREENSAVERRUNNING, 0, &isScreenSaverActive, 0);

				static BOOL runOnceAfterScreenSaverExit = FALSE;
				if (!isScreenSaverActive && !runOnceAfterScreenSaverExit)
				{
					runOnceAfterScreenSaverExit = TRUE;
				}

				if (runOnceAfterScreenSaverExit)
				{
					m_isScreenSaverRunning = FALSE;
					runOnceAfterScreenSaverExit = FALSE;

					if (m_bFullScreen)
					{
						SystemSetting::Instance()->SetLevel(SystemSetting::eSSC_WINDOWMODE, 1);
						SystemSetting::Instance()->CommitChanges();

						SystemSetting::Instance()->SetLevel(SystemSetting::eSSC_WINDOWMODE, 0);
						SystemSetting::Instance()->CommitChanges();
						
					}
					else
					{
						unsigned int resolution = SystemSetting::Instance()->GetLevel(SystemSetting::eSSC_RESOLUTION);
						SIZE size = { resolution >> 16 , resolution & 0xffff };
						size.cx += 1;
						size.cy += 1;

						resolution = (((size.cx << 16) & 0xffff0000) | size.cy);
						SystemSetting::Instance()->SetLevel(SystemSetting::eSSC_RESOLUTION, resolution);
						SystemSetting::Instance()->CommitChanges();
					}	
					
				}
			}*/
			
			if ( !m_bActive )
			{
				Sleep( 1 );
			}
        }
#if LOAD_COST_TIME_DEBUG
// 		static int nFrameCount = 0;
// 		++nFrameCount;
// 		if (nFrameCount == 10)
// 		{
// 			Sleep(100);
// 			nFrameCount = 0;
// 		}
		time_cost = HQ_TimeGetTime() - time_cost;
		if (time_cost > 80)
		{
			char cOutputString[2048];
			MeSprintf_s( cOutputString, 2048, "\nFrameCost:%d\n", time_cost );
			OutputDebugStr(cOutputString);
		}
#endif
    }

    return (INT)msg.wParam;
}


enum ESkipRenderStatus
{
    SRS_NOT_SKIP,          // 没跳过渲染
    SRS_FIRST_SKIP,        // 本帧跳过渲染
    SRS_SECONE_NOT_SKIP    // 下一帧需要渲染
};
//-----------------------------------------------------------------------------
// Name: Render3DEnvironment()
// Desc: Draws the scene.
//-----------------------------------------------------------------------------
HRESULT CD3DApplication::Render3DEnvironment()
{
    static 
    HRESULT hr;
    // Test the cooperative level to see if it's okay to render
    bool bDeviceLostSkipRender = false;
    if( m_isDeviceLost && FAILED( hr = m_pd3dDevice->TestCooperativeLevel() ) )
    {
        if (D3DERR_DEVICELOST == hr)
        {
            bDeviceLostSkipRender = true;
        }
        else
        {
            if( FAILED( hr = Resize3DEnvironment() ) )
            {
                bDeviceLostSkipRender = true;
            }
            else
            {
                m_isDeviceLost = FALSE;
                return S_OK;
            }
        }
    }

    // Get the app's time, in seconds. Skip rendering if no time elapsed
    FLOAT fAppTime        = DXUtil_Timer( TIMER_GETAPPTIME );
    FLOAT fElapsedAppTime = DXUtil_Timer( TIMER_GETELAPSEDTIME );
    if( ( 0.0f == fElapsedAppTime ) && m_bFrameMoving )
        return S_OK;

    BOOL bSkipRender = FALSE;
    static int s_iLastRenderStatus = SRS_NOT_SKIP;

    m_iLastFrameUpdateCost += (int)m_NetCost;
    // 如果窗口非激活且非最小化并帧数降低，则提高进程优先级
    /*if( m_bActive )
    {
        if( GetActiveWindow() != g_hWnd )
        {
            if(m_fFPS < 7 && m_iLastFrameCost > m_fFrameCostAverage+5 && !m_bAboveNormalPriority )
                SetProcessPriority(TRUE);
        }
        else
        {
            if( m_bAboveNormalPriority )
                SetProcessPriority(FALSE);
        }
    }*/
    // 如果上帧Update耗时超过100ms，或者如果窗口非激活且帧数降低，则每3帧跳过一次渲染
    if( 0/*m_iLastFrameUpdateCost >= 50*/ )
    {
        if( s_iLastRenderStatus == SRS_NOT_SKIP )
        {
            bSkipRender = TRUE;
            s_iLastRenderStatus = SRS_FIRST_SKIP;
        }
        else
        {
            s_iLastRenderStatus++;
            if( s_iLastRenderStatus > SRS_SECONE_NOT_SKIP )
                s_iLastRenderStatus = SRS_NOT_SKIP;
        }
    }
    else
        s_iLastRenderStatus = SRS_NOT_SKIP;
    
    WORD time_cost = HQ_TimeGetTime();
	// Render the scene as normal
    if ( !m_bPauseRendering && !bSkipRender && !bDeviceLostSkipRender )
    {
        if( ( hr = Render() ) == S_FALSE )
            return hr;
	}

	if( !m_pd3dDevice )	
	   return S_FALSE;
	if (FAILED(hr = m_pd3dDevice->Present( NULL, NULL, NULL, NULL )))
	{
		m_isDeviceLost = D3DERR_DEVICELOST == hr || D3DERR_DRIVERINTERNALERROR == hr;
	}
    
	// FrameMove (animate) the scene
    WORD frame_cost = HQ_TimeGetTime();
	if( m_bFrameMoving || m_bSingleStep )
	{
		// Store the time for the app
		m_fTime        = fAppTime;
		m_fElapsedTime = fElapsedAppTime;

		// Frame move the scene
		if( ( hr = FrameMove() ) == S_FALSE )
			return hr;

		m_bSingleStep = FALSE;
	}

    time_cost = HQ_TimeGetTime() - time_cost;
    m_iLastFrameCost = (int)(time_cost + m_NetCost);
    frame_cost = HQ_TimeGetTime() - frame_cost;
    m_iLastFrameUpdateCost = (int)frame_cost;
#if LOAD_COST_TIME_DEBUG
	if (time_cost > 40)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nRenderCost:%d FrameMoveCost:%d\n", time_cost - frame_cost,frame_cost);
		OutputDebugStr(cOutputString);
	}
#endif

    // Keep track of the frame count
    static FLOAT fLastTime = 0.0f;
    static DWORD dwFrames  = 0L;
    FLOAT fTime = DXUtil_Timer( TIMER_GETABSOLUTETIME );
    ++dwFrames;

    // 保存本帧耗时
    m_iFrameCostIn60Frames[m_iFramsCostIndex++] = m_iLastFrameCost;
    if( m_iFramsCostIndex >= 60 )
        m_iFramsCostIndex = 0;
    FLOAT fTotalFrameCost = 0;
    for(int i=0; i<60; i++)
    {
        fTotalFrameCost += m_iFrameCostIn60Frames[i];
    }
    m_fFrameCostAverage = fTotalFrameCost / 60.f;

    // Update the scene stats once per second
    if( fTime - fLastTime > 1.0f )
    {
        m_fFPS    = dwFrames / (fTime - fLastTime);
        fLastTime = fTime;
        dwFrames  = 0L;


		_stprintf( m_strFrameStats, _T("%.02f fps"), m_fFPS );
    }

    // Show the frame on the primary surface.
// 	if( !m_pd3dDevice )	
//         return S_FALSE;

// 	IDirect3DQuery9* pOcclusionQuery;
// 	DWORD numberOfPixelsDrawn = 0;
// 
// 	m_pd3dDevice->CreateQuery(D3DQUERYTYPE_OCCLUSION, &pOcclusionQuery);
// 
// 	// Add an end marker to the command buffer queue.
// 	pOcclusionQuery->Issue(D3DISSUE_BEGIN);
// 
//     if (FAILED(hr = m_pd3dDevice->Present( NULL, NULL, NULL, NULL )))
//     {
//         m_isDeviceLost = D3DERR_DEVICELOST == hr || D3DERR_DRIVERINTERNALERROR == hr;
//     }
// 
// 
// 	// Add an end marker to the command buffer queue.
// 	pOcclusionQuery->Issue(D3DISSUE_END);

	// Force the driver to execute the commands from the command buffer.
	// Empty the command buffer and wait until the GPU is idle.
// 	while(S_FALSE == pOcclusionQuery->GetData( &numberOfPixelsDrawn, 
// 		sizeof(DWORD), D3DGETDATA_FLUSH ));

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Pause()
// Desc: Called in to toggle the pause state of the app.
//-----------------------------------------------------------------------------
VOID CD3DApplication::Pause( BOOL bPause )
{
    static DWORD dwAppPausedCount = 0L;

    dwAppPausedCount += ( bPause ? +1 : -1 );
    m_bReady          = ( dwAppPausedCount ? FALSE : TRUE );

    // Handle the first pause request (of many, nestable pause requests)
    if( bPause && ( 1 == dwAppPausedCount ) )
    {
        // Stop the scene from animating
        if( m_bFrameMoving )
            DXUtil_Timer( TIMER_STOP );
    }

    if( 0 == dwAppPausedCount )
    {
        // Restart the timers
        if( m_bFrameMoving )
            DXUtil_Timer( TIMER_START );
    }
	if (bPause)
	{
		m_rcOldWindowBoundsBeforeMoving = m_rcWindowBounds;
	}
}




//-----------------------------------------------------------------------------
// Name: Cleanup3DEnvironment()
// Desc: Cleanup scene objects
//-----------------------------------------------------------------------------
VOID CD3DApplication::Cleanup3DEnvironment()
{
    m_bActive = FALSE;
    m_bReady  = FALSE;
	//应该要先清除其他的东西，最后在clear D3D...
    FinalCleanup();
	//
    if( m_pd3dDevice )
    {
        InvalidateDeviceObjects();
        DeleteDeviceObjects();
		//
        m_pd3dDevice->Release();
        m_pD3D->Release();
		//
        m_pd3dDevice = NULL;
        m_pD3D       = NULL;
    }
}
//-----------------------------------------------------------------------------
// Name: DisplayErrorMsg()
// Desc: Displays error messages in a message box
//-----------------------------------------------------------------------------
HRESULT CD3DApplication::DisplayErrorMsg( HRESULT hr, DWORD dwType )
{
	assert( 0 && "display error msg" );
    TCHAR strMsg[512];

    switch( hr )
    {
	case D3DAPPERR_NODIRECT3D:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_80 ))
			 );
		break;

	case D3DAPPERR_NOCOMPATIBLEDEVICES:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_81 )));
		break;

	case D3DAPPERR_NOWINDOWABLEDEVICES:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_82 ))
			);
		break;

	case D3DAPPERR_NOHARDWAREDEVICE:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_83 ))
			 );
		break;

	case D3DAPPERR_HALNOTCOMPATIBLE:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_84 )) 
			);

		break;

	case D3DAPPERR_NOWINDOWEDHAL:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_85 ))
			);
		break;

	case D3DAPPERR_NODESKTOPHAL:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_86 ))
			);
		break;

	case D3DAPPERR_NOHALTHISMODE:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_87 ))
			);
		break;

	case D3DAPPERR_RESIZEFAILED:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_88 )) );
		break;

	case D3DAPPERR_NONZEROREFCOUNT:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_89 )));
		break;

	case D3DAPPERR_NULLREFDEVICE:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_90 ))
			);
		break;

	case E_OUTOFMEMORY:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_91 )) );
		break;

	case D3DERR_OUTOFVIDEOMEMORY:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_92 )) );
		break;

	default:
		_tcscpy( strMsg, _T(theXmlString.GetString( eInitError_93 ))
			);
    }

    if( MSGERR_APPMUSTEXIT == dwType )
    {
        _tcscat( strMsg, _T(theXmlString.GetString( eInitError_94 )) );
        MessageBox( NULL, strMsg, m_strWindowTitle, MB_ICONERROR|MB_OK );

        // close window
        if( m_hWnd )
            ::TerminateProcess( ::GetCurrentProcess(), 0 );	
    }
    else
    {
        MessageBox( NULL, strMsg, m_strWindowTitle, MB_ICONWARNING|MB_OK );
    }

    return hr;
}

HRESULT CD3DApplication::ResizeWindow( bool bFullScreen /* = false */, bool mustResetWnd)
{	
	RECT rc;

	//lyh++ 如果改变分辨率的时候，则设置 s_CUI_ID_FRAME_LOGIN frame 的大小，不然ui位置将会出错
	if (s_CUI_ID_FRAME_LOGIN.GetFrame())
	{
		s_CUI_ID_FRAME_LOGIN.GetFrame()->SetWidth(SCREEN_WIDTH);
		s_CUI_ID_FRAME_LOGIN.GetFrame()->SetHeight( SCREEN_HEIGHT );
		s_CUI_ID_FRAME_LOGIN.GetFrame()->SetRedraw();
	}
	if (s_CUI_ID_FRAME_Select.GetFrame())
	{
		s_CUI_ID_FRAME_Select.GetFrame()->SetWidth(SCREEN_WIDTH);
		s_CUI_ID_FRAME_Select.GetFrame()->SetHeight( SCREEN_HEIGHT );
		s_CUI_ID_FRAME_Select.GetFrame()->SetRedraw();
	}
	if (s_CUI_ID_FRAME_FirstCreate.GetFrame())
	{
		s_CUI_ID_FRAME_FirstCreate.GetFrame()->SetWidth(SCREEN_WIDTH);
		s_CUI_ID_FRAME_FirstCreate.GetFrame()->SetHeight( SCREEN_HEIGHT );
		s_CUI_ID_FRAME_FirstCreate.GetFrame()->SetRedraw();
		s_CUI_ID_FRAME_FirstCreate.OnGameWindowMove(0,0);
	}

	if (s_CUI_ID_FRAME_CREATE.GetFrame())
	{
		s_CUI_ID_FRAME_CREATE.GetFrame()->SetWidth(SCREEN_WIDTH);
		s_CUI_ID_FRAME_CREATE.GetFrame()->SetHeight( SCREEN_HEIGHT );
		s_CUI_ID_FRAME_CREATE.GetFrame()->SetRedraw();
	}



	m_bFullScreen = bFullScreen;
	if( bFullScreen )
	{
		DWORD windowStyle = WS_POPUP;
		SCREEN_WIDTH = m_rcDesktop.right;
		SCREEN_HEIGHT = m_rcDesktop.bottom;
		::SetRect( &rc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
		if (m_dwWindowStyle != windowStyle)
			::SetWindowLong( m_hWnd, GWL_STYLE, windowStyle );
		m_dwWindowStyle = windowStyle;
		::SetWindowPos( m_hWnd, 0, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW );
	}
	else
	{
		RECT oldRc;

		::GetWindowRect(m_hWnd,&oldRc);
		if ((oldRc.right - oldRc.left) == SCREEN_WIDTH && (oldRc.bottom - oldRc.top) == SCREEN_HEIGHT && !mustResetWnd)
		{
		}
		else
		{
			
			
			DWORD windowStyle =  WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
			::SetRect( &rc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
			::AdjustWindowRect( &rc, windowStyle, FALSE );
			if (m_dwWindowStyle != windowStyle)
				::SetWindowLong( m_hWnd, GWL_STYLE, windowStyle );
			m_dwWindowStyle = windowStyle;
			SetWindowPos( m_hWnd, 0,0,0, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW|SWP_NOMOVE );


			
		}
	}

	::GetWindowRect( m_hWnd, &m_rcWindowBounds );
	::GetClientRect( m_hWnd, &m_rcWindowClient );

	if (g_HelpHwnd)
	{
		int nWidth = gCfg.m_nHelpPageWidth;
		int nHeight = gCfg.m_nHelpPageHeight;
		m_rcHelpWindow.left = (m_rcWindowBounds.left + m_rcWindowBounds.right - nWidth)/2;
		m_rcHelpWindow.top = (m_rcWindowBounds.top + m_rcWindowBounds.bottom - nHeight)/2;
		m_rcHelpWindow.right = m_rcHelpWindow.left + nWidth;
		m_rcHelpWindow.bottom = m_rcHelpWindow.top + nHeight;
		SetWindowPos( g_HelpHwnd, 0,
			m_rcHelpWindow.left, m_rcHelpWindow.top,
			( m_rcHelpWindow.right - m_rcHelpWindow.left ),
			( m_rcHelpWindow.bottom - m_rcHelpWindow.top ),
			SWP_NOACTIVATE );
	}
	else if(g_RegisterHwnd)
	{
		int nWidth = 367;
		int nHeight = 332;
		RECT rect;
		rect.left = (m_rcWindowBounds.left + m_rcWindowBounds.right - nWidth)/2;
		rect.top = (m_rcWindowBounds.top + m_rcWindowBounds.bottom - nHeight)/2;
		rect.right = rect.left + nWidth;
		rect.bottom = rect.top + nHeight;
		SetWindowPos( g_RegisterHwnd, 0,
			rect.left, rect.top,
			( rect.right - rect.left ),
			( rect.bottom - rect.top ),
			SWP_NOACTIVATE );
	}
	m_d3dpp.BackBufferWidth  = 0;
	m_d3dpp.BackBufferHeight = 0;
	HRESULT hr = Resize3DEnvironment();

	InvalidateRect(0, 0, TRUE);

	theUiManager.ReSetWindowPosNoAllVisable();

    return hr;
}

void CD3DApplication::CleanupDevice()
{
	if( m_pd3dDevice )
	{
		InvalidateDeviceObjects();
		DeleteDeviceObjects();

		m_pd3dDevice->Release();
		m_pd3dDevice = NULL;
	}
}

HRESULT CD3DApplication::ChangeDevice( bool bFullScreen /* = false */ )
{
	return ResizeWindow( bFullScreen );
	//return Resize3DEnvironment();
}

BOOL CD3DApplication::SetProcessPriority( BOOL bAboveNormal )
{
    BOOL ret = FALSE;
    if( m_bAboveNormalPriority != bAboveNormal )
    {
        m_bAboveNormalPriority = bAboveNormal;
        if( m_bAboveNormalPriority )
            ret = SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
        else
            ret = SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
    }
    return ret;
}
#include "Browser/Browser.h"
//-----------------------------------------------------------------------------
// Name: HelpWndProc()
// Desc: Static msg handler which passes messages to the Help class.
//-----------------------------------------------------------------------------
// 	INT_PTR CALLBACK HelpWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
RECT WindwosRect = {0,0,0,0};
LRESULT CALLBACK HelpWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
	case WM_CREATE:
		{
			//long lstyle = GetWindowLong(hWnd,GWL_STYLE);
			//lstyle = WS_OVERLAPPED;
			//SetWindowLong(hWnd,GWL_STYLE,lstyle);
			// Embed the browser object into our host window. We need do this only
			// once. Note that the browser object will start calling some of our
			// IOleInPlaceFrame and IOleClientSite functions as soon as we start
			// calling browser object functions in EmbedBrowserObject().
			if ( EmbedBrowserObject( hWnd ) ) return -1;

			return 0; // Success
		}
	case WM_MOUSEACTIVATE:
		{
			POINT ptCursor;
			GetCursorPos( &ptCursor );
			RECT helpRect ;
			GetWindowRect(hWnd,&helpRect);
			if (ptCursor.x < helpRect.right - 23
				&& ptCursor.x > helpRect.right - 55
				&& ptCursor.y > helpRect.top + 3
				&& ptCursor.y < helpRect.top + 35)
			{
				DestroyWindow(hWnd);
				BringWindowToTop(g_hWnd);
			}
			return 0;
		}
		break;
	case WM_DESTROY:
		{
			// Detach the browser object from this window, and free resources.
			UnEmbedBrowserObject( hWnd );
			g_HelpHwnd = NULL;
			return 0;
		}
	case WM_KEYUP:
		{
			switch( wParam )
			{
			case VK_ESCAPE:
				ShowWindow( hWnd, SW_HIDE );
				break;
			}
			return 0;
		}
	}

	return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
}

HWND CD3DApplication::CreateHelpWindow()
{
	int nWidth = gCfg.m_nHelpPageWidth;
	int nHeight = gCfg.m_nHelpPageHeight;
	SetRect( &m_rcHelpWindow, (m_rcWindowBounds.left + m_rcWindowBounds.right - nWidth)/2 , (m_rcWindowBounds.top + m_rcWindowBounds.bottom - nHeight)/2, nWidth, nHeight );
//DWORD dwWindowStyle = WS_OVERLAPPED| WS_POPUP|WS_CHILD /*| WS_VISIBLE |WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX*/;
	DWORD dwExWindowStyle = 0;
	DWORD dwWindowStyle = WS_OVERLAPPED| WS_POPUP|WS_CHILD | WS_VISIBLE |WS_CAPTION|WS_SYSMENU;
	      // DWORD dwWindowStyle = WS_OVERLAPPED | WS_CAPTION   | WS_THICKFRAME | WS_POPUP | WS_CHILD | WS_SYSMENU;
	WNDCLASS wndClass = { CS_PARENTDC, HelpWndProc, 0, 0, NULL,
		NULL,
		LoadCursor( NULL, IDC_ARROW ),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		NULL, _T("Help Window") };
	RegisterClass( &wndClass );
	g_HelpHwnd = CreateWindowEx(dwExWindowStyle, _T("Help Window"), _T("官方活动"), dwWindowStyle,
		m_rcHelpWindow.left, m_rcHelpWindow.top,
		nWidth, nHeight, 
		g_hWnd,
		NULL/*hMenu*/,
		NULL, 0L );
	return g_HelpHwnd;
}
void CD3DApplication::SetSizable( bool bSizable )
{
	m_bSizable = bSizable;
	if( bSizable )	
		::SetWindowLong( g_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW );	
	else
		::SetWindowLong( g_hWnd, GWL_STYLE, WS_OVERLAPPED );
	UpdateWindow( g_hWnd );
}

void CD3DApplication::SetWindowText( const char* text )
{
	if( !text )
		return;
	char name[256];
	MeSprintf_s(name,sizeof(name)/sizeof(char) - 1, "%s %s", ApplicationConfig::Instance().GetProjectName(), text);
	::SetWindowText(m_hWnd, name);
}

// added by ZhuoMeng.Hu		[10/20/2010]
std::string CD3DApplication::GetWindowText()
{
    char name[256] = {0};
    ::GetWindowText( m_hWnd, name, sizeof( name ) / sizeof( char ) - 1 );
    std::string strName = name;
    std::string strPrj = ApplicationConfig::Instance().GetProjectName();
    if( !strPrj.empty() )
    {
        std::string::size_type n = strName.find( strPrj );
        if( n == 0 )
            strName = strName.substr( strPrj.size() );
        while( !strName.empty() && ( strName.find( " " ) == 0 ) )
        {
            strName = strName.substr( 1 );
        }
    }
    return strName;
}

D3DMULTISAMPLE_TYPE CD3DApplication::GetBestAvailableMultiSampleType(LPDIRECT3D9 d3d9)
{
	D3DDISPLAYMODE displayMode;
	m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

	SystemSetting::Instance()->GetFSAATypeList().clear();
	SystemSetting::Instance()->AddFSAAType(0);
	for (int i = 2; i <= 16; ++i)
	{
		D3DMULTISAMPLE_TYPE bestMultiSampleType = (D3DMULTISAMPLE_TYPE) i;
		if (SUCCEEDED(d3d9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			displayMode.Format, TRUE, bestMultiSampleType, NULL)))
		{
			SystemSetting::Instance()->AddFSAAType(i);
		}
	}

	//if (IsBadVideoCard(d3d9))
	//bestMultiSampleType = D3DMULTISAMPLE_NONE;
	return D3DMULTISAMPLE_NONE;
}
//----------------------------------------------------------------------------
//	End.
//----------------------------------------------------------------------------

