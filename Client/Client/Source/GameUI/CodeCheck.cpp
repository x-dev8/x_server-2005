/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\CodeCheck.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CodeCheck.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
//#include "Launcher/DataLauncher.h"
#include "UIMgr.h"
//#include "validate.h"
#include "MeUi/UiRender.h"
#include "Common.h"

extern HWND g_hWnd;

#define GRAPHICCODE_CHARTABLEFILE "%s/data/texture/graphiccode/chartable.raw"
#define GRAPHICCODE_WIDTH 160
#define GRAPHICCODE_HEIGHT 48

CUI_ID_FRAME_CodeCheck s_CUI_ID_FRAME_CodeCheck;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CodeCheck, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CodeCheck, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CodeCheck, ID_BUTTON_CheckOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CodeCheck, ID_CHECKBOX_Check1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CodeCheck, ID_CHECKBOX_Check2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CodeCheck, ID_CHECKBOX_Check3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CodeCheck, ID_CHECKBOX_Check4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CodeCheck, ID_CHECKBOX_Check5OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CodeCheck, ID_CHECKBOX_Check6OnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CodeCheck, ID_BUTTON_SmallOnButtonClick )
CUI_ID_FRAME_CodeCheck::CUI_ID_FRAME_CodeCheck()
{
	// Member
	m_pID_FRAME_CodeCheck = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_PICTURE_Code = NULL;
	m_pID_BUTTON_Check = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_CHECKBOX_Check1 = NULL;
	m_pID_CHECKBOX_Check2 = NULL;
	m_pID_CHECKBOX_Check3 = NULL;
	m_pID_CHECKBOX_Check4 = NULL;
	m_pID_TEXT_Answer1 = NULL;
	m_pID_TEXT_Answer2 = NULL;
	m_pID_TEXT_Answer3 = NULL;
	m_pID_TEXT_Answer4 = NULL;
	//m_pID_BUTTON_Small = NULL;
	m_pID_CHECKBOX_Check5 = NULL;
	m_pID_TEXT_Answer5 = NULL;
	m_pID_CHECKBOX_Check6 = NULL;
	m_pID_TEXT_Answer6 = NULL;
	m_pCodeTexture = 0;
	m_dwLastTime = 0;
}
// Frame
bool CUI_ID_FRAME_CodeCheck::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_CodeCheck::OnFrameRender()
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
bool CUI_ID_FRAME_CodeCheck::ID_BUTTON_CheckOnButtonClick( ControlObject* pSender )
{
	MsgAckGraphicCode msg;
	if( m_pID_CHECKBOX_Check1->IsChecked() )
		msg.index = 0;
	else if( m_pID_CHECKBOX_Check2->IsChecked() )
		msg.index = 1;
	else if( m_pID_CHECKBOX_Check3->IsChecked() )
		msg.index = 2;
	else if( m_pID_CHECKBOX_Check4->IsChecked() )
		msg.index = 3;
	else if( m_pID_CHECKBOX_Check5->IsChecked() )
		msg.index = 4;
	else if( m_pID_CHECKBOX_Check6->IsChecked() )
		msg.index = 5;
	GettheNetworkInput().SendMsg( &msg );
	SetVisable( false );
	return true;
}
// CheckBox
void CUI_ID_FRAME_CodeCheck::ID_CHECKBOX_Check1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CodeCheck)
	{
		assert(false&&"ui error");
		return ;
	}

	m_AnswerGroup.ToggleRadio( m_pID_CHECKBOX_Check1 );
}
// CheckBox
void CUI_ID_FRAME_CodeCheck::ID_CHECKBOX_Check2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CodeCheck)
	{
		assert(false&&"ui error");
		return ;
	}

	m_AnswerGroup.ToggleRadio( m_pID_CHECKBOX_Check2 );
}
// CheckBox
void CUI_ID_FRAME_CodeCheck::ID_CHECKBOX_Check3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CodeCheck)
	{
		assert(false&&"ui error");
		return ;
	}

	m_AnswerGroup.ToggleRadio( m_pID_CHECKBOX_Check3 );
}
// CheckBox
void CUI_ID_FRAME_CodeCheck::ID_CHECKBOX_Check4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CodeCheck)
	{
		assert(false&&"ui error");
		return ;
	}

	m_AnswerGroup.ToggleRadio( m_pID_CHECKBOX_Check4 );
}
// CheckBox
void CUI_ID_FRAME_CodeCheck::ID_CHECKBOX_Check5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CodeCheck)
	{
		assert(false&&"ui error");
		return ;
	}

	m_AnswerGroup.ToggleRadio( m_pID_CHECKBOX_Check5 );
}
// CheckBox
void CUI_ID_FRAME_CodeCheck::ID_CHECKBOX_Check6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CodeCheck)
	{
		assert(false&&"ui error");
		return ;
	}

	m_AnswerGroup.ToggleRadio( m_pID_CHECKBOX_Check6 );
}
// Button
bool CUI_ID_FRAME_CodeCheck::ID_BUTTON_SmallOnButtonClick( ControlObject* pSender )
{

	return true;
}

// 装载UI
bool CUI_ID_FRAME_CodeCheck::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CodeCheck.MEUI", false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CodeCheck.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CodeCheck::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CodeCheck, s_CUI_ID_FRAME_CodeCheckOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CodeCheck, s_CUI_ID_FRAME_CodeCheckOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_CodeCheck, ID_BUTTON_Check, s_CUI_ID_FRAME_CodeCheckID_BUTTON_CheckOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CodeCheck, ID_CHECKBOX_Check1, s_CUI_ID_FRAME_CodeCheckID_CHECKBOX_Check1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CodeCheck, ID_CHECKBOX_Check2, s_CUI_ID_FRAME_CodeCheckID_CHECKBOX_Check2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CodeCheck, ID_CHECKBOX_Check3, s_CUI_ID_FRAME_CodeCheckID_CHECKBOX_Check3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CodeCheck, ID_CHECKBOX_Check4, s_CUI_ID_FRAME_CodeCheckID_CHECKBOX_Check4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CodeCheck, ID_CHECKBOX_Check5, s_CUI_ID_FRAME_CodeCheckID_CHECKBOX_Check5OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CodeCheck, ID_CHECKBOX_Check6, s_CUI_ID_FRAME_CodeCheckID_CHECKBOX_Check6OnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_CodeCheck, ID_BUTTON_Small, s_CUI_ID_FRAME_CodeCheckID_BUTTON_SmallOnButtonClick );

	m_pID_FRAME_CodeCheck = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CodeCheck );
	m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_PICTURE_Title );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_PICTURE_Wall );
	m_pID_PICTURE_Code = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_PICTURE_Code );
	m_pID_BUTTON_Check = (ControlButton*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_BUTTON_Check );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_TEXT_Title );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_TEXT_Time );
	m_pID_CHECKBOX_Check1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_CHECKBOX_Check1 );
	m_pID_CHECKBOX_Check2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_CHECKBOX_Check2 );
	m_pID_CHECKBOX_Check3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_CHECKBOX_Check3 );
	m_pID_CHECKBOX_Check4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_CHECKBOX_Check4 );
	m_pID_TEXT_Answer1 = (ControlText*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_TEXT_Answer1 );
	m_pID_TEXT_Answer2 = (ControlText*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_TEXT_Answer2 );
	m_pID_TEXT_Answer3 = (ControlText*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_TEXT_Answer3 );
	m_pID_TEXT_Answer4 = (ControlText*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_TEXT_Answer4 );
	//m_pID_BUTTON_Small = (ControlButton*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_BUTTON_Small );
	m_pID_CHECKBOX_Check5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_CHECKBOX_Check5 );
	m_pID_TEXT_Answer5 = (ControlText*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_TEXT_Answer5 );
	m_pID_CHECKBOX_Check6 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_CHECKBOX_Check6 );
	m_pID_TEXT_Answer6 = (ControlText*)theUiManager.FindControl( ID_FRAME_CodeCheck, ID_TEXT_Answer6 );
	assert( m_pID_FRAME_CodeCheck );
	assert( m_pID_PICTURE_Title );
	assert( m_pID_PICTURE_Wall );
	assert( m_pID_PICTURE_Code );
	assert( m_pID_BUTTON_Check );
	assert( m_pID_TEXT_Title );
	assert( m_pID_TEXT_Time );
	assert( m_pID_CHECKBOX_Check1 );
	assert( m_pID_CHECKBOX_Check2 );
	assert( m_pID_CHECKBOX_Check3 );
	assert( m_pID_CHECKBOX_Check4 );
	assert( m_pID_TEXT_Answer1 );
	assert( m_pID_TEXT_Answer2 );
	assert( m_pID_TEXT_Answer3 );
	assert( m_pID_TEXT_Answer4 );
	//assert( m_pID_BUTTON_Small );
	assert( m_pID_CHECKBOX_Check5 );
	assert( m_pID_TEXT_Answer5 );
	assert( m_pID_CHECKBOX_Check6 );
	assert( m_pID_TEXT_Answer6 );

	/// do some init	
	memset( m_aucUncompressedBitsstream, 0, MsgReqGraphicCode::ECD_BisstreamMaxSize * sizeof( unsigned char ) * 8 );	
	memset( m_acGlyphBuf, 0, MsgReqGraphicCode::ECD_GlyphBufMaxSize * sizeof( char ) );
	memset( m_awcGlyph, 0, MsgReqGraphicCode::ECD_GlyphBufMaxSize / 2 * sizeof( wchar_t ) );
	m_dwTime = 0;
	m_pCodeTexture = 0;

	SetVisable( false );
	LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	if (FAILED( pDevice->CreateTexture(
		GRAPHICCODE_WIDTH,
		GRAPHICCODE_HEIGHT,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		&m_pCodeTexture,
		NULL)))
	{
		CheckTerminateable( m_pCodeTexture );
		return false;
	}

	m_AnswerGroup.Clear();
	m_AnswerGroup.AddRadio( m_pID_CHECKBOX_Check1 );
	m_AnswerGroup.AddRadio( m_pID_CHECKBOX_Check2 );
	m_AnswerGroup.AddRadio( m_pID_CHECKBOX_Check3 );
	m_AnswerGroup.AddRadio( m_pID_CHECKBOX_Check4 );
	m_AnswerGroup.AddRadio( m_pID_CHECKBOX_Check5 );
	m_AnswerGroup.AddRadio( m_pID_CHECKBOX_Check6 );
	m_pID_FRAME_CodeCheck->enableEscKey( false );
	m_dwLastTime = 0;

	USE_SCRIPT( eUI_OBJECT_CodeCheck, this );
	m_pID_FRAME_CodeCheck->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CodeCheck::_UnLoadUI()
{
	m_pID_FRAME_CodeCheck = NULL;

    m_pID_PICTURE_Title = NULL;
    m_pID_PICTURE_Wall = NULL;
    m_pID_PICTURE_Code = NULL;
    m_pID_BUTTON_Check = NULL;
    m_pID_TEXT_Title = NULL;
    m_pID_TEXT_Time = NULL;
    m_pID_CHECKBOX_Check1 = NULL;
    m_pID_CHECKBOX_Check2 = NULL;
    m_pID_CHECKBOX_Check3 = NULL;
    m_pID_CHECKBOX_Check4 = NULL;
    m_pID_TEXT_Answer1 = NULL;
    m_pID_TEXT_Answer2 = NULL;
    m_pID_TEXT_Answer3 = NULL;
    m_pID_TEXT_Answer4 = NULL;
    //m_pID_BUTTON_Small = NULL;
    m_pID_CHECKBOX_Check5 = NULL;
    m_pID_TEXT_Answer5 = NULL;
    m_pID_CHECKBOX_Check6 = NULL;
    m_pID_TEXT_Answer6 = NULL;

	if( m_pCodeTexture )
	{
		m_pCodeTexture->Release();
		m_pCodeTexture = 0;
	}
	return theUiManager.RemoveFrame( "Data\\UI\\CodeCheck.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CodeCheck::_IsVisable()
{
    if(!m_pID_FRAME_CodeCheck)
        return false;

	return m_pID_FRAME_CodeCheck->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CodeCheck::_SetVisable( const bool bVisable )
{
    if(!m_pID_FRAME_CodeCheck)
        return;

	m_pID_CHECKBOX_Check1->SetCheck( false );
	m_pID_CHECKBOX_Check2->SetCheck( false );
	m_pID_CHECKBOX_Check3->SetCheck( false );
	m_pID_CHECKBOX_Check4->SetCheck( false );
	m_pID_CHECKBOX_Check5->SetCheck( false );
	m_pID_CHECKBOX_Check6->SetCheck( false );
	m_pID_FRAME_CodeCheck->SetVisable( bVisable );
	m_pID_FRAME_CodeCheck->SetRedraw();
}

void CUI_ID_FRAME_CodeCheck::SetStreamInfo( DWORD dwTime, unsigned char* pucBitStream, char* pcGlyphBuf )
{
	m_dwTime = dwTime;
	Uncompress( pucBitStream, m_aucUncompressedBitsstream );	
	CheckTerminateable( m_pCodeTexture );
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
		
	memcpy_s( m_acGlyphBuf, sizeof( m_acGlyphBuf ), pcGlyphBuf, MsgReqGraphicCode::ECD_GlyphBufMaxSize * sizeof( unsigned char ) );
	for( int i = 0 ; i < MsgReqGraphicCode::ECD_GlyphBufMaxSize / 2; ++ i )
	{
		m_awcGlyph[i] = ( m_acGlyphBuf[i * 2] << 8 ) | ( m_acGlyphBuf[i * 2 + 1] );
	}
	wchar_t awcAnswer[5] = {0};	
	memcpy_s( awcAnswer, sizeof( awcAnswer ), m_awcGlyph, sizeof( wchar_t ) * 4 );
	awcAnswer[4] = L'\0';
	m_pID_TEXT_Answer1->SetTextW( awcAnswer );
	memcpy_s( awcAnswer, sizeof( awcAnswer ), m_awcGlyph + 4, sizeof( wchar_t ) * 4 );
	awcAnswer[4] = L'\0';
	m_pID_TEXT_Answer2->SetTextW( awcAnswer );
	memcpy_s( awcAnswer, sizeof( awcAnswer ), m_awcGlyph + 8, sizeof( wchar_t ) * 4 );
	awcAnswer[4] = L'\0';
	m_pID_TEXT_Answer3->SetTextW( awcAnswer );
	memcpy_s( awcAnswer, sizeof( awcAnswer ), m_awcGlyph + 12, sizeof( wchar_t ) * 4 );
	awcAnswer[4] = L'\0';
	m_pID_TEXT_Answer4->SetTextW( awcAnswer );
	if( MsgReqGraphicCode::ECD_GlyphBufMaxSize / 8 > 4 )
	{
		memcpy_s( awcAnswer, sizeof( awcAnswer ), m_awcGlyph + 16, sizeof( wchar_t ) * 4 );
		awcAnswer[4] = L'\0';
		m_pID_TEXT_Answer5->SetTextW( awcAnswer );
		memcpy_s( awcAnswer, sizeof( awcAnswer ), m_awcGlyph + 20, sizeof( wchar_t ) * 4 );
		awcAnswer[4] = L'\0';
		m_pID_TEXT_Answer6->SetTextW( awcAnswer );
	}
	

	// set last time
	m_dwLastTime = HQ_TimeGetTime();
}

void CUI_ID_FRAME_CodeCheck::Uncompress(const unsigned char* bitstream, unsigned char* background)
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
void CUI_ID_FRAME_CodeCheck::CheckTerminateable( LPDIRECT3DTEXTURE9 pTex )
{
	char acErrorInfo[256] = {0};		
	if( !pTex )
	{
		_stprintf_s( acErrorInfo, 256, "%s", theXmlString.GetString( eInitError_92 ) );
		::MessageBoxA( g_hWnd, acErrorInfo, acErrorInfo,MB_ICONERROR | MB_OK );
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}
}

S_BaseData* CUI_ID_FRAME_CodeCheck::GetData()
{
	if(m_pID_FRAME_CodeCheck)
		return m_pID_FRAME_CodeCheck->GetData();
	else
		assert(false&&"ui error");

	return NULL;
}