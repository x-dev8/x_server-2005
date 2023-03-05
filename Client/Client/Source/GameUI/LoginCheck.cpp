/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\LoginCheck.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "LoginCheck.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
//#include "Launcher/DataLauncher.h"
#include "UIMgr.h"
#include "GameMain.h"
#include "MessageBox.h"
#include "ui/Select.h"
#include "MeUi/UiRender.h"
#include "Common.h"

#define GRAPHICCODE_CHARTABLEFILE "%s/data/texture/graphiccode/chartable.raw"
#define GRAPHICCODE_WIDTH 160
#define GRAPHICCODE_HEIGHT 48

extern GAME_STATE		g_GameState;

CUI_ID_FRAME_LoginCheck s_CUI_ID_FRAME_LoginCheck;
MAP_FRAME_RUN( s_CUI_ID_FRAME_LoginCheck, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_LoginCheck, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LoginCheck, ID_BUTTON_CheckOnButtonClick )
CUI_ID_FRAME_LoginCheck::CUI_ID_FRAME_LoginCheck()
{
	// Member
	m_pID_FRAME_LoginCheck = NULL;
	m_pID_PICTURE_Code = NULL;
	m_pID_BUTTON_Check = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_PICTURE_CodeCheckWall = NULL;
	m_pID_EDIT_CodeCheck = NULL;

}
// Frame
bool CUI_ID_FRAME_LoginCheck::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_LoginCheck::OnFrameRender()
{
	// set time
	char szBuffer[256] = {0};		
	char szResult[256] = {0};
	DWORD dwElapse = HQ_TimeGetTime() - m_dwLastTime;
	int nSecond = ( m_dwTime - dwElapse ) / 1000;	
	if( m_dwTime < dwElapse )
	{
		SetVisable( false );
		return true;
	}
	int nDay = nSecond / ( 24 * 60 * 60 ) ;	
	int nLeft = nSecond % ( 24 * 60 * 60 );
	int nHour = nLeft / ( 60 * 60 );
	nLeft = nLeft % ( 60 * 60 );
	int nMinute = nLeft / 60;
	nLeft = nLeft % 60;	

	if ( nMinute != 0 )		
		MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1, "%s%d分钟", szBuffer, nMinute );				
	MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1, "%s%d%s", szBuffer, nLeft,theXmlString.GetString(eTimeUnit_Second));	

	MeSprintf_s( szResult, sizeof(szResult)/sizeof(char) - 1, "%s%s", theXmlString.GetString( eText_Title_LeftTime ), szBuffer );			
	*m_pID_TEXT_Time = szResult;

	RECT rcDesRc, rcSrcRc;
	m_pID_PICTURE_Code->GetRealRect( &rcDesRc );
	rcSrcRc.left = 0;
	rcSrcRc.right = GRAPHICCODE_WIDTH;
	rcSrcRc.top = 0;
	rcSrcRc.bottom = GRAPHICCODE_HEIGHT;
	{
		CBaseGraphics::RenderTexture( (void*)m_pCodeTexture, &rcDesRc, &rcSrcRc, GRAPHICCODE_WIDTH, GRAPHICCODE_HEIGHT, 0, 0xffffffff );
	}
	return true;
	
}
// Button
bool CUI_ID_FRAME_LoginCheck::ID_BUTTON_CheckOnButtonClick( ControlObject* pSender )
{	
	if( !m_pID_FRAME_LoginCheck )
		return false;
	MsgAckNumberCode msg;
	msg.index = atoi( m_pID_EDIT_CodeCheck->GetText() );
	GettheNetworkInput().SendMsg( &msg );
	SetVisable( false );

    if( g_GameState == G_SELECT )
    {
        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_WaitEnterWorld), "", CUI_ID_FRAME_MessageBox::eTypeCancel, true, /*UI_ID_FRAME_SELECT::*/EnterWorldFailed);
        s_CUI_ID_FRAME_MessageBox.SetAutoClose(20, false);
    }

	return true;
}
// Edit
void CUI_ID_FRAME_LoginCheck::ID_EDIT_CodeCheckOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_LoginCheck )
		return;
	ID_BUTTON_CheckOnButtonClick( 0 );
}

// 装载UI
bool CUI_ID_FRAME_LoginCheck::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\LoginCheck.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\LoginCheck.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_LoginCheck::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_LoginCheck, s_CUI_ID_FRAME_LoginCheckOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_LoginCheck, s_CUI_ID_FRAME_LoginCheckOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_LoginCheck, ID_BUTTON_Check, s_CUI_ID_FRAME_LoginCheckID_BUTTON_CheckOnButtonClick );

	m_pID_FRAME_LoginCheck = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_LoginCheck );
	m_pID_PICTURE_Code = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LoginCheck, ID_PICTURE_Code );
	m_pID_BUTTON_Check = (ControlButton*)theUiManager.FindControl( ID_FRAME_LoginCheck, ID_BUTTON_Check );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_LoginCheck, ID_TEXT_Time );
	m_pID_PICTURE_CodeCheckWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LoginCheck, ID_PICTURE_CodeCheckWall );
	m_pID_EDIT_CodeCheck = (ControlEdit*)theUiManager.FindControl( ID_FRAME_LoginCheck, ID_EDIT_CodeCheck );
	assert( m_pID_FRAME_LoginCheck );
	assert( m_pID_PICTURE_Code );
	assert( m_pID_BUTTON_Check );
	assert( m_pID_TEXT_Time );
	assert( m_pID_PICTURE_CodeCheckWall );
	assert( m_pID_EDIT_CodeCheck );

	m_pID_EDIT_CodeCheck->SetIsNumber( true );
    m_pID_FRAME_LoginCheck->SetMsgProcFun( frame_msg );

	/// do some init	
	memset( m_aucUncompressedBitsstream, 0, MsgReqGraphicCode::ECD_BisstreamMaxSize * sizeof( unsigned char ) * 8 );	
	memset( m_acGlyphBuf, 0, MsgReqGraphicCode::ECD_GlyphBufMaxSize * sizeof( char ) );
	memset( m_awcGlyph, 0, MsgReqGraphicCode::ECD_GlyphBufMaxSize / 2 * sizeof( wchar_t ) );
	m_dwTime = 0;
	m_pCodeTexture = 0;

	SetVisable( false );
	LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	HRESULT hr = pDevice->CreateTexture(
		GRAPHICCODE_WIDTH,
		GRAPHICCODE_HEIGHT,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		&m_pCodeTexture,
		NULL);

	if( hr == D3DERR_OUTOFVIDEOMEMORY )//显存不足，强制关闭客户端并做提示
	{
		char acError[256] = {0};
		strcpy_s( acError, 256, theXmlString.GetString( eInitError_92 ));
		MessageBoxA( NULL, acError, acError, MB_ICONERROR|MB_OK );
		::TerminateProcess( ::GetCurrentProcess(), 0 );	
	}
	if( hr == E_OUTOFMEMORY )//内存不足，强制关闭客户端并做提示
	{
		char acError[256] = {0};
		strcpy_s( acError, 256, theXmlString.GetString( eInitError_91 ));
		MessageBoxA( NULL, acError, acError, MB_ICONERROR|MB_OK );
		::TerminateProcess( ::GetCurrentProcess(), 0 );	
	}
	

	m_pID_FRAME_LoginCheck->enableEscKey( false );
	m_dwLastTime = 0;

	USE_SCRIPT( eUI_OBJECT_LoginCheck, this );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_LoginCheck::_UnLoadUI()
{
	m_pID_FRAME_LoginCheck = NULL;
	m_pID_PICTURE_Code = NULL;
	m_pID_BUTTON_Check = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_PICTURE_CodeCheckWall = NULL;
	m_pID_EDIT_CodeCheck = NULL;
	if( m_pCodeTexture )
	{
		m_pCodeTexture->Release();
		m_pCodeTexture = 0;
	}
	return theUiManager.RemoveFrame( "Data\\UI\\LoginCheck.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_LoginCheck::_IsVisable()
{
	if( !m_pID_FRAME_LoginCheck )
		return false;
	return m_pID_FRAME_LoginCheck->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_LoginCheck::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_LoginCheck )
		return;
	
	m_pID_FRAME_LoginCheck->SetVisable( bVisable );
	m_pID_FRAME_LoginCheck->SetRedraw();

	m_pID_EDIT_CodeCheck->SetText("");
	if( bVisable )
		m_pID_EDIT_CodeCheck->SetActivate( true );
}
void CUI_ID_FRAME_LoginCheck::SetStreamInfo( DWORD dwTime, unsigned char* pucBitStream )
{
	if( !m_pCodeTexture )
	{
		char acError[256] = {0};
		strcpy_s( acError, 256, theXmlString.GetString( eInitError_92 ));
		MessageBoxA( NULL, acError, acError, MB_ICONERROR|MB_OK );
		::TerminateProcess( ::GetCurrentProcess(), 0 );	
	}
	m_dwTime = dwTime;
	Uncompress( pucBitStream, m_aucUncompressedBitsstream );	
	D3DLOCKED_RECT dRect;
	if( D3D_OK == m_pCodeTexture->LockRect( 0, &dRect, 0, 0 ) )
	{
		for( DWORD y=0; y<GRAPHICCODE_HEIGHT; y++ )
		{
			for( DWORD x=0; x<GRAPHICCODE_WIDTH; x++ )
			{
				DWORD dwFactor = m_aucUncompressedBitsstream[ y * GRAPHICCODE_WIDTH + x ];
				((DWORD*)dRect.pBits)[GRAPHICCODE_WIDTH*y+x] = 
					D3DCOLOR_ARGB( 255, dwFactor, dwFactor, dwFactor );
			}
		}
		m_pCodeTexture->UnlockRect( 0 );
	}
	// set last time
	m_dwLastTime = HQ_TimeGetTime();
}

void CUI_ID_FRAME_LoginCheck::Uncompress(const unsigned char* bitstream, unsigned char* background)
{
	unsigned char charTable[256][8];

	FILE *tableFile;
	long int tableLen;
	int i, dist = 0;

	memset(charTable, 0, 8*256);

	char strName[MAX_PATH] = {0};
	MeSprintf_s(strName,sizeof(strName)/sizeof(char) - 1, GRAPHICCODE_CHARTABLEFILE, SwGlobal::GetWorld()->GetAppDataCharDir());
	tableFile = fopen(strName, "rb");
	if (!tableFile)
	{
		printf("Can't find the charTable file!\n");
		return ;
	}

	fseek(tableFile, 0, SEEK_END);
	tableLen = ftell(tableFile);
	fseek(tableFile, 0, SEEK_SET);

	fread(charTable, sizeof(char), tableLen, tableFile);

	fclose(tableFile);
	tableFile = NULL;

	for (i = 0; i < 960; ++i)
	{ 
		memcpy(background + dist, charTable[bitstream[i]], 8*sizeof(char)); 
		dist += 8;
	}  		
}

bool CUI_ID_FRAME_LoginCheck::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
    guardfunc;
    if ( bMsgUsed == true )
        return false;

    if( !s_CUI_ID_FRAME_LoginCheck.IsVisable() )
        return false;

    switch( msg ) 
    {
    case WM_KEYUP:
        {
            if( wParam == VK_RETURN )
            {
                s_CUI_ID_FRAME_LoginCheck.ID_BUTTON_CheckOnButtonClick(0);
                return true;
            }
        }
        break;
    }

    return false;

    unguard;
}
