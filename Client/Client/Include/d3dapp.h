//-----------------------------------------------------------------------------
// File: D3DApp.h
//
// Desc: Application class for the Direct3D samples framework library.
//-----------------------------------------------------------------------------
#ifndef D3DAPP_H
#define D3DAPP_H

// basetsd.h defines INT_PTR (used below).  It is not included by default
// under VC 5.0.  If you are using VC6 or later, it is included via Windows.h.
#include <basetsd.h> 
#include <vector>
//-----------------------------------------------------------------------------
// Error codes
//-----------------------------------------------------------------------------
enum APPMSGTYPE { MSG_NONE, MSGERR_APPMUSTEXIT, MSGWARN_SWITCHEDTOREF };

#define D3DAPPERR_NODIRECT3D          0x82000001
#define D3DAPPERR_NOWINDOW            0x82000002
#define D3DAPPERR_NOCOMPATIBLEDEVICES 0x82000003
#define D3DAPPERR_NOWINDOWABLEDEVICES 0x82000004
#define D3DAPPERR_NOHARDWAREDEVICE    0x82000005
#define D3DAPPERR_HALNOTCOMPATIBLE    0x82000006
#define D3DAPPERR_NOWINDOWEDHAL       0x82000007
#define D3DAPPERR_NODESKTOPHAL        0x82000008
#define D3DAPPERR_NOHALTHISMODE       0x82000009
#define D3DAPPERR_NONZEROREFCOUNT     0x8200000a
#define D3DAPPERR_MEDIANOTFOUND       0x8200000b
#define D3DAPPERR_RESIZEFAILED        0x8200000c
#define D3DAPPERR_NULLREFDEVICE       0x8200000d


#define WM_USER_CLOSE   0x0420  // 用户自定义关闭窗口消息，不处理WM_CLOSE消息

//-----------------------------------------------------------------------------
// Name: struct D3DModeInfo
// Desc: Structure for holding information about a display mode
//-----------------------------------------------------------------------------
struct D3DModeInfo
{
    DWORD      Width;      // Screen width in this mode
    DWORD      Height;     // Screen height in this mode
    D3DFORMAT  Format;     // Pixel format in this mode
    DWORD      dwBehavior; // Hardware / Software / Mixed vertex processing
    D3DFORMAT  DepthStencilFormat; // Which depth/stencil format to use with this mode
};




//-----------------------------------------------------------------------------
// Name: struct D3DDeviceInfo
// Desc: Structure for holding information about a Direct3D device, including
//       a list of modes compatible with this device
//-----------------------------------------------------------------------------
struct D3DDeviceInfo
{
    // Device data
    D3DDEVTYPE   DeviceType;      // Reference, HAL, etc.
    D3DCAPS9     d3dCaps;         // Capabilities of this device
    const TCHAR* strDesc;         // Name of this device
    BOOL         bCanDoWindowed;  // Whether this device can work in windowed mode

    // Modes for this device
    DWORD        dwNumModes;
    D3DModeInfo  modes[150];

    // Current state
    DWORD        dwCurrentMode;
    BOOL         bWindowed;
    D3DMULTISAMPLE_TYPE MultiSampleTypeWindowed;
    D3DMULTISAMPLE_TYPE MultiSampleTypeFullscreen;
};




//-----------------------------------------------------------------------------
// Name: struct D3DAdapterInfo
// Desc: Structure for holding information about an adapter, including a list
//       of devices available on this adapter
//-----------------------------------------------------------------------------
struct D3DAdapterInfo
{
    // Adapter data
    D3DADAPTER_IDENTIFIER9 d3dAdapterIdentifier;
    D3DDISPLAYMODE d3ddmDesktop;      // Desktop display mode for this adapter

    // Devices for this adapter
    DWORD          dwNumDevices;
    D3DDeviceInfo  devices[5];

    // Current state
    DWORD          dwCurrentDevice;
};




//-----------------------------------------------------------------------------
// Name: class CD3DApplication
// Desc: A base class for creating sample D3D8 applications. To create a simple
//       Direct3D application, simply derive this class into a class (such as
//       class CMyD3DApplication) and override the following functions, as 
//       needed:
//          OneTimeSceneInit()    - To initialize app data (alloc mem, etc.)
//          InitDeviceObjects()   - To initialize the 3D scene objects
//          FrameMove()           - To animate the scene
//          Render()              - To render the scene
//          DeleteDeviceObjects() - To cleanup the 3D scene objects
//          FinalCleanup()        - To cleanup app data (for exitting the app)
//          MsgProc()             - To handle Windows messages
//-----------------------------------------------------------------------------
struct IDirectDraw7;
class CD3DApplication
{
public: // public functions

	// added, jiayi, [2009/9/16]
	const char* GetDeviceStates(){ return m_strDeviceStats; }

	HINSTANCE		  GetInstance(){return m_hInstance;}
	FLOAT GetAppFps(){return m_fFPS;}


public:
	std::vector<D3DDISPLAYMODE> m_DisplayModes;
	BOOL		m_bChanged;
	INT			m_ChangedDisplayID;
protected:	
	bool			  m_bTrue3D;
	INT					m_BestAdapter;
    // Internal variables for the state of the app
    D3DAdapterInfo    m_Adapters[10];
    DWORD             m_dwNumAdapters;
    DWORD             m_dwAdapter;
    BOOL              m_bWindowed;
    BOOL              m_bActive;
    BOOL              m_bReady;
    BOOL              m_bHasFocus;

    // Internal variables used for timing
    BOOL              m_bFrameMoving;
    BOOL              m_bSingleStep;

    // Internal error handling function
    HRESULT DisplayErrorMsg( HRESULT hr, DWORD dwType );

    // Internal functions to manage and render the 3D scene
    HRESULT BuildDeviceList();
    BOOL    FindDepthStencilFormat( UINT iAdapter, D3DDEVTYPE DeviceType,
                D3DFORMAT TargetFormat, D3DFORMAT* pDepthStencilFormat );
    HRESULT Initialize3DEnvironment();
    HRESULT Resize3DEnvironment();
    HRESULT ToggleFullscreen();
    HRESULT ForceWindowed();
    HRESULT UserSelectNewDevice();
    HRESULT Render3DEnvironment();
    virtual HRESULT AdjustWindowForChange();
    static INT_PTR CALLBACK SelectDeviceProc( HWND hDlg, UINT msg, 
                WPARAM wParam, LPARAM lParam );

    // add [6/30/2008 whu]
    virtual void UpdateNet() = 0;
	virtual void SlowCPU() = 0;


protected:
    // Main objects used for creating and rendering the 3D scene
    D3DPRESENT_PARAMETERS m_d3dpp;         // Parameters for CreateDevice/Reset
    HWND              m_hWnd;              // The main app window
    HWND              m_hWndFocus;         // The D3D focus window (usually same as m_hWnd)
    LPDIRECT3D9       m_pD3D;              // The main D3D object
    LPDIRECT3DDEVICE9 m_pd3dDevice;        // The D3D rendering device
    D3DCAPS9          m_d3dCaps;           // Caps for the device
    D3DSURFACE_DESC   m_d3dsdBackBuffer;   // Surface desc of the backbuffer
    DWORD             m_dwCreateFlags;     // Indicate sw or hw vertex processing
    DWORD             m_dwWindowStyle;     // Saved window style for mode switches
    RECT              m_rcWindowBounds;    // Saved window bounds for mode switches
    RECT              m_rcWindowClient;    // Saved client area size for mode switches
	RECT			  m_rcDesktop;		   // desktop resolution

	RECT              m_rcOldWindowBoundsBeforeMoving;    // Saved OldWindowBoundsBeforeMoving
	RECT			  m_rcHelpWindow;

	// Variables for timing
    FLOAT             m_fTime;             // Current time in seconds
    FLOAT             m_fElapsedTime;      // Time elapsed since last frame
    FLOAT             m_fFPS;              // Instanteous frame rate
    TCHAR             m_strDeviceStats[90];// String to hold D3D device stats
    TCHAR             m_strFrameStats[90]; // String to hold frame stats
    int               m_iFrameCostIn60Frames[60];// 最近60帧内每帧耗时（毫秒）
    short             m_iFramsCostIndex;  // 当前帧记录在m_iFrameCostIn60Frames里的下标
    FLOAT             m_fFrameCostAverage;// 最近60帧平均耗时（毫秒）
    int               m_iLastFrameCost;    // 上一帧耗时（毫秒）
    int               m_iLastFrameUpdateCost;// 上一帧Update耗时（毫秒）
    WORD			  m_NetCost;
    BOOL              m_bAboveNormalPriority; // 进程是否普通优先级

    // Overridable variables for the app
    TCHAR*            m_strWindowTitle;    // Title for the app's window
    BOOL              m_bUseDepthBuffer;   // Whether to autocreate depthbuffer
    DWORD             m_dwMinDepthBits;    // Minimum number of bits needed in depth buffer
    DWORD             m_dwMinStencilBits;  // Minimum number of bits needed in stencil buffer
    DWORD             m_dwCreationWidth;   // Width used to create window
    DWORD             m_dwCreationHeight;  // Height used to create window
    BOOL              m_bShowCursorWhenFullscreen; // Whether to show cursor when fullscreen
    BOOL              m_bClipCursorWhenFullscreen; // Whether to limit cursor pos when fullscreen

    BOOL              m_bPauseRendering;
	BOOL              m_bPauseSIZEMOVE;

    BOOL              m_isDeviceLost;
	BOOL			  m_isScreenSaverRunning;

	HINSTANCE		  m_hInstance;

	IDirectDraw7*	  m_pDDobject;
	HINSTANCE		  m_ddrawLib;

    // Overridable functions for the 3D scene created by the app
    virtual HRESULT ConfirmDevice(D3DCAPS9*,DWORD,D3DFORMAT)   { return S_OK; }
    virtual HRESULT OneTimeSceneInit()                         { return S_OK; } //系统只需要初始化的模块
    virtual HRESULT InitDeviceObjects()                        { return S_OK; }	//初始化D3d设备
    virtual HRESULT RestoreDeviceObjects()                     { return S_OK; } //从新设置设备
    virtual HRESULT FrameMove()                                { return S_OK; }	//帧控制
    virtual HRESULT Render()                                   { return S_OK; }	//上图
    virtual HRESULT InvalidateDeviceObjects()                  { return S_OK; }	//
    virtual HRESULT DeleteDeviceObjects()                      { return S_OK; }
    virtual HRESULT FinalCleanup()                             { return S_OK; }
    VOID    Cleanup3DEnvironment();										//清除
	
	void CleanupDevice();

    BOOL    SetProcessPriority(BOOL bAboveNormal);

public:
    // Functions to create, run, pause, and clean up the application
    virtual HRESULT Create( HINSTANCE hInstance );
    virtual INT     Run();
    virtual LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    virtual VOID    Pause( BOOL bPause );
	virtual BOOL	LoadFxShader() {return TRUE;}
	void	SetSizable( bool bSizable );
	bool	GetSizable() const { return m_bSizable; }


	HWND			CreateHelpWindow();
	// added, jiayi, [2009.5.20]
	RECT&   GetDesktopRect(){ return m_rcDesktop; }
	RECT&	GetHelpWindowRect(){return m_rcHelpWindow;}
    // Internal constructor
    CD3DApplication();
	BOOL	m_bFullScreen;
	BOOL	HasFocus(){ return m_bHasFocus; }
	BOOL    IsFullScreen(){ return m_bFullScreen; }

	HRESULT ChangeDevice( bool bFullScreen = false );
	HRESULT ResizeWindow( bool bFullScreen = false, bool mustResetWnd = false);

	virtual void OnSizeWindow( WPARAM wParam, LPARAM lParam ) = 0;

	D3DPRESENT_PARAMETERS* GetD3DPP() { return &m_d3dpp; }

	float GetFrameElapsedTime() const { return m_fElapsedTime; }

	bool IsInitialized(){ return m_bInitEnd; }
	void Initialized(){ m_bInitEnd = true ;}
	void SetWindowText(const char* text);
    std::string GetWindowText();
	void SetTrue3D( bool bTrue3D ){ m_bTrue3D = bTrue3D; }

	// 返回硬件支持的MultiSample最佳级别
	D3DMULTISAMPLE_TYPE GetBestAvailableMultiSampleType(LPDIRECT3D9 d3d9);

protected:
	bool m_bSizable;
	bool m_bInitEnd;//是否完成初始化

};

extern HWND g_hWnd;

#endif



