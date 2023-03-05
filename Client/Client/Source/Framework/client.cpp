//-----------------------------------------------------------------------------
// File: DragoonApp.cpp
//
// Desc: DirectX window application created by the DirectX AppWizard
//-----------------------------------------------------------------------------
//#define STRICT
#include <windows.h>
#include <basetsd.h>
#include <math.h>
#include <stdio.h>
#include "Dxsdk/d3dx9.h"
#include "Dxsdk/dxerr9.h"
#include <tchar.h>
 #include "SystemConfig.h"
#include "D3DApp.h"
#include "D3DUtil.h"
#include "DXUtil.h"
#include "../Resource/Resource.h"
#include "client.h"
#include "GameMain.h"
#include "GlobalVars.h"
#include "Me3d\BaseGraphics.h"
#include "Me3d\include.h"
#include "FuncPerformanceLog.h"
#include "filepath.h"
#include "Me3d/Engine/Engine.h"
#include "Common.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

//-----------------------------------------------------------------------------
// Global access to the app (needed for the global WndProc())
//-----------------------------------------------------------------------------
CMyD3DApplication* g_pApp  = NULL;
HINSTANCE          g_hInst = NULL;

//-----------------------------------------------------------------------------
// Name: CMyD3DApplication()
// Desc: Application constructor. Sets attributes for the app.
//-----------------------------------------------------------------------------
CMyD3DApplication::CMyD3DApplication()
{
	OutputDebugStr("MyApplication..");
    m_dwCreationWidth           = SCREEN_WIDTH;
    m_dwCreationHeight          = SCREEN_HEIGHT;
	OutputDebugStr("MyApplication1");
	m_dwMinDepthBits			= 0;
	//
    m_strWindowTitle            = "";
    m_bUseDepthBuffer           = TRUE;

    m_bLoadingApp               = TRUE;

	OutputDebugStr("MyApplication End");
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::OneTimeSceneInit()
{
    // TODO: perform one time initialization

    // Drawing loading status message until app finishes loading
    SendMessage( m_hWnd, WM_PAINT, 0, 0 );

    m_bLoadingApp = FALSE;

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device initialization, this code checks the display device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior,
                                          D3DFORMAT Format )
{
    BOOL bCapsAcceptable;

    // TODO: Perform checks to see if these display caps are acceptable.
    bCapsAcceptable = TRUE;

    if( bCapsAcceptable )         
        return S_OK;
    else
        return E_FAIL;
}

//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    // TODO: create device objects

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Restores scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    // TODO: setup render states
    HRESULT hr;
    // Setup a material
    D3DMATERIAL9 mtrl;
    D3DUtil_InitMaterial( mtrl, 1.0f, 0.0f, 0.0f );
	mtrl.Ambient.r = 0.0f;
	mtrl.Ambient.g = 0.0f;
	mtrl.Ambient.b = 0.0f;

	mtrl.Specular.a = 1.0f;
	mtrl.Specular.r = 1.0f;
	mtrl.Specular.g = 1.0f;
	mtrl.Specular.b = 1.0f;
	mtrl.Power = 10;
    m_pd3dDevice->SetMaterial( &mtrl );

    // Set up the textures
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
 
	//m_pd3dDevice->SetS
	m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

    // Set miscellaneous render states
    m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE,   FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,        TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT,        D3DCOLOR_ARGB(200,60,60,60) );

    // Set the world matrix
    D3DXMATRIX matIdentity;
    D3DXMatrixIdentity( &matIdentity );
    m_pd3dDevice->SetTransform( D3DTS_WORLD,  &matIdentity );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DXMATRIX matView;
    D3DXVECTOR3 vFromPt   = D3DXVECTOR3( 0.0f, 0.0f, -5.0f );
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &matView, &vFromPt, &vLookatPt, &vUpVec );
    m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // Set the projection matrix
    D3DXMATRIX matProj;
    FLOAT fAspect = ((FLOAT)m_d3dsdBackBuffer.Width) / m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, fAspect, 1.0f, 100.0f );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    // TODO: update world

    // Update user input state
    UpdateInput( &m_UserInput );


    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: UpdateInput()
// Desc: Update the user input.  Called once per frame 
//-----------------------------------------------------------------------------
void CMyD3DApplication::UpdateInput( UserInput* pUserInput )
{
    pUserInput->bRotateUp    = ( m_bHasFocus && (GetAsyncKeyState( VK_UP )    & 0x8000) == 0x8000 );
    pUserInput->bRotateDown  = ( m_bHasFocus && (GetAsyncKeyState( VK_DOWN )  & 0x8000) == 0x8000 );
    pUserInput->bRotateLeft  = ( m_bHasFocus && (GetAsyncKeyState( VK_LEFT )  & 0x8000) == 0x8000 );
    pUserInput->bRotateRight = ( m_bHasFocus && (GetAsyncKeyState( VK_RIGHT ) & 0x8000) == 0x8000 );
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         0x000000ff, 1.0f, 0L );

    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        // End the scene.
        m_pd3dDevice->EndScene();
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Overrrides the main WndProc, so the sample can do custom message
//       handling (e.g. processing mouse, keyboard, or menu commands).
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd, UINT msg, WPARAM wParam,
                                    LPARAM lParam )
{
    return CD3DApplication::MsgProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Invalidates device objects.  
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    // TODO: Cleanup any objects created in RestoreDeviceObjects()
//    SAFE_RELEASE( m_pD3DXFont );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc: Called when the app is exiting, or the device is being changed,
//       this function deletes any device dependent objects.  
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::DeleteDeviceObjects()
{
    // TODO: Cleanup any objects created in InitDeviceObjects()

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FinalCleanup()
{

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
#define MAX_BLOODBAR 128
struct SBloodBar
{
	int x, y;
	int h;
	int nFrameWidth;
	DWORD color;
	int nBloodWidth; 
	DWORD dwBloodColor;
};
int g_nBloodBarCount = 0;
SBloodBar g_BloodBars[MAX_BLOODBAR];
void DrawBloodBar( int x, int y, int h, 
				  int nFrameWidth, 
				  int nBloodWidth, 
				  DWORD dwBloodColor )
{
	//TRUETIMEFUNC();
	g_BloodBars[g_nBloodBarCount].x = x;
	g_BloodBars[g_nBloodBarCount].y = y;
	g_BloodBars[g_nBloodBarCount].h = h;
	g_BloodBars[g_nBloodBarCount].nFrameWidth = nFrameWidth;
	g_BloodBars[g_nBloodBarCount].nBloodWidth = nBloodWidth;
	g_BloodBars[g_nBloodBarCount].dwBloodColor = dwBloodColor;
	g_nBloodBarCount++;
	assert( g_nBloodBarCount <= MAX_BLOODBAR && "blood bar count out of range" );
}

void FlushBloodBarToScreen()
{
	SBloodBar* bar = g_BloodBars;
	RECT rcBlood;
	for( int i = 0; i < g_nBloodBarCount; i++ )
	{
		rcBlood.left = bar->x-bar->nFrameWidth/2;
		rcBlood.top = bar->y;
		rcBlood.right = rcBlood.left+bar->nBloodWidth;
		rcBlood.bottom = rcBlood.top+bar->h;
		// draw blood bar
		GetDrawer()->FillRect2D( rcBlood, bar->dwBloodColor );
		
		rcBlood.right =  bar->x+bar->nFrameWidth/2;
		// draw blood bar frame
		GetDrawer()->DrawRect2D( rcBlood, 0xff000000 );
		
		bar++;

	}
	g_nBloodBarCount =  0;
}

void DrawNumberCharBitmap( int x, int y, int w, int h, int start_line, DWORD color, int nNumber, Simple2DVertex vertex[] )
{
	static POINT index[12] =
	{
		0, 0,
		0, 1,	
		0, 2,
		0, 3,

		0, 4,
		0, 5,
		0, 6,
		0, 7,

		1, 0,
		1, 1,
		1, 2,
		1, 3,
	};

	RECT rect;
	rect.left	= x;
	rect.top	= y;
	rect.right	= x+w;
	rect.bottom = y+h;
	//
	float sdv = 1.0f / 4 * start_line;
	float du = 1.0f/8;
	float dv = 1.0f/8;
	int row = index[nNumber].x;
	int col = index[nNumber].y;

	float z = 0.2f;

	vertex[0].p = D3DXVECTOR4( rect.left, rect.bottom, z, 1 );
	vertex[0].color = color;
	vertex[0].u = du*col;
	vertex[0].v = sdv + dv*row+dv;

	vertex[1].p = D3DXVECTOR4( rect.left, rect.top, z, 1 );
	vertex[1].color = color;
	vertex[1].u = du*col;
	vertex[1].v = sdv + dv*row;

	vertex[2].p = D3DXVECTOR4( rect.right, rect.bottom, z, 1 );
	vertex[2].color = color;
	vertex[2].u = du*col+du;
	vertex[2].v = sdv + dv*row+dv;

	vertex[3].p = D3DXVECTOR4( rect.right, rect.top, z, 1 );
	vertex[3].color = color;
	vertex[3].u = du*col+du;
	vertex[3].v = sdv + dv*row;

}
