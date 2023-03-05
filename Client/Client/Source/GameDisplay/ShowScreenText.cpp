#include "ShowScreenText.h"
#include "MeUi/FontManager.h"
#include "Cfg.h"
#include <assert.h>
#include "Me3d/Engine/EngineInstance.h"
#include "FuncPerformanceLog.h"
#include "MeFont/MeFont.h"
#include "MeUi/ControlObject.h"
#include "tstring.h"
#include "XmlStringLanguage.h"
#include "core/Name.h"
#include "Me3d/Engine/RendererDX.h"
#include "MeFont/MeFontSystem.h"
#include "ScreenInfoManager.h"

DWORD HQ_TimeGetTime();

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#define TEXT_FADE_IN_RATE		800
#define TEXT_FADE_OUT_RATE		2000

bool		g_showPFErrorText =  false; //为了避免多线程冲突

CShowScreenText* GetShowScreenText()
{
	static CShowScreenText s;
	return &s;
}
int			CShowScreenText::m_nSkipSameInfoTime = 0;
int			CShowScreenText::m_nScrollTime= 0;
int			CShowScreenText::m_nPauseTime= 0;

int			CShowScreenText::m_nBigTitleYPos = 0;
int			CShowScreenText::m_nSysInfoYPos = 0;
int			CShowScreenText::m_nRiseUpInfoYPos = 0;
int			CShowScreenText::m_nSmallInfoYPos = 0;

int			CShowScreenText::m_nBigTileFontSize = 0;
int			CShowScreenText::m_nSysInfoFontSize = 0;
int			CShowScreenText::m_nRiseUpInfoFontSize = 0;
int			CShowScreenText::m_nSmallInfoFontSize = 0;

char	    CShowScreenText::m_szBigTileFontName[256] = {0};
char		CShowScreenText::m_szSysInfoFontName[256] = {0};
char		CShowScreenText::m_szRiseUpFontName[256] = {0};
char		CShowScreenText::m_szSmallFontName[256] = {0};

CShowScreenText::CShowScreenText(void)
{
	guardfunc;
	HDC hTileDC;
	int nBigFont = FontSystem::CreateFont( m_szBigTileFontName,
		m_nBigTileFontSize, 0, FW_NORMAL,
		1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, &hTileDC);

	int nSysFont = FontSystem::CreateFont( m_szSysInfoFontName,
		m_nSysInfoFontSize, 0, FW_NORMAL,
		1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, &hTileDC);

	HDC hInfoDC;
	int nRiseFont = FontSystem::CreateFont( m_szRiseUpFontName,
		m_nRiseUpInfoFontSize, 0, FW_NORMAL,
		1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, &hInfoDC );

    int nSmallFont = FontSystem::CreateFont( m_szSmallFontName,
        m_nSmallInfoFontSize, 0, FW_NORMAL,
        1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, &hInfoDC );

	for( int n = eInfoBigTileText; n < eInfoMax; n++ )
	{
		m_stText[n] = new SText;
	}
	m_stText[eInfoBigTileText]->nFont = nBigFont;
	m_stText[eInfoBigTileText]->hDC = hTileDC;

    m_stText[eInfoSysText]->nFont = nSysFont;
    m_stText[eInfoSysText]->hDC = hTileDC;

	ReCalYPos();
	for( int n = eRiseTextBegin; n <= eRiseTextEnd; n++ )
	{
		m_stText[n]->nFont = nRiseFont;
		m_stText[n]->hDC = hInfoDC;
		m_stText[n]->nY = m_nTextYPos[n];
	}
    for( int n = eUnRiseTextBegin; n <= eUnRiseTextEnd; n++ )
    {
        m_stText[n]->nFont = nSmallFont;
        m_stText[n]->hDC = hInfoDC;
        m_stText[n]->nY = m_nTextYPos[n];
    }
	dwMoveStartTime = 0;
	dwPauseStartTime = 0;
    m_nUnRiseLines = 0;
	unguard;
}

CShowScreenText::~CShowScreenText(void)
{
	guardfunc;
	for (int i = 0; i < eInfoMax; ++i)
	{
		delete m_stText[i];
		m_stText[i] = NULL;
	}
	unguard;
}

void CShowScreenText::Render(bool isTopLevel)
{
	DWORD dwTimeCost = HQ_TimeGetTime();
	char acCost[256] = {0};

	bool bNeedRender = false;
	for ( int i=0; i<eInfoMax; i++ )
	{
		SText *pText = m_stText[i];
		if (pText->bTopLevel != isTopLevel)
		{
			continue;
		}
		if (eShowHide != pText->enShowState)
		{
			bNeedRender = true;
			break;
		}
	}
	if (!bNeedRender)
	{
		return;
	}
    //修改渲染细致时修改渲染参数的Bug
    RendererDx* RI = (RendererDx*)GetEngine()->GetRenderer();
    if(RI)
    {
        RI->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
        RI->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
        RI->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
        RI->Commit();
    }
	dwTimeCost = HQ_TimeGetTime() - dwTimeCost;
	sprintf_s( acCost, 256, "\n CShowScreenText 111111 Cost: %d", dwTimeCost );
	if( dwTimeCost > 10 )
		OutputDebugStringA( acCost );
	dwTimeCost = HQ_TimeGetTime();

	if (g_showPFErrorText)
	{
        //为了避免多线程冲突
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, theXmlString.GetString( eClient_AddInfo_PFError ) );
		g_showPFErrorText = false;
	}
	DWORD nowTime = HQ_TimeGetTime();
	if (dwPauseStartTime < dwMoveStartTime && nowTime > dwMoveStartTime)
	{
		dwPauseStartTime = dwMoveStartTime + m_nScrollTime;
	}
	if (nowTime > dwMoveStartTime + m_nScrollTime)
	{
		for ( int n=eRiseTextBegin; n < eRiseTextEnd - 1; n++ )
		{
			m_stText[n]->fMoveSpeed = 0;
			m_stText[n]->nY = m_nTextYPos[n];
		}
	}

	dwTimeCost = HQ_TimeGetTime() - dwTimeCost;
	sprintf_s( acCost, 256, "\n CShowScreenText 22222 Cost: %d", dwTimeCost );
	if( dwTimeCost > 10 )
		OutputDebugStringA( acCost );
	dwTimeCost = HQ_TimeGetTime();

	DWORD deltaTime = nowTime - dwLastRenderTime;
	dwLastRenderTime = nowTime;
	//return;
	guardfunc;
	SText *pText = NULL;
	for ( int i=0; i<eInfoMax; i++ )
	{
        pText = m_stText[i];
        if (pText->bTopLevel != isTopLevel)
        {
            continue;
        }
        int nTime = HQ_TimeGetTime() - pText->dwStartTime;
        switch( pText->enShowState ) 
        {
        case eShowNormal:
            if ( nTime >= pText->dwShowTime )
            {
                pText->enShowState = eShowHide;
            }
            break;
        case eShowFadein:
            {
                if ( nTime >= TEXT_FADE_IN_RATE )
                {
                    pText->enShowState = eShowFadeNormal;
                    pText->dwColor |= 0xff000000;
                    break;
                }
                int n = TEXT_FADE_IN_RATE - nTime;
                BYTE alpha = 0xFF - 0xFF*n/TEXT_FADE_IN_RATE;
                pText->dwColor &= 0x00ffffff;
                pText->dwColor |= alpha<<24;
            }
            break;
        case eShowFadeNormal:
            if ( nTime >= TEXT_FADE_OUT_RATE + pText->dwShowTime )
            {
                pText->enShowState = eShowFadeout;
            }
            break;
        case eShowFadeout:
            {
                if ( nTime >= TEXT_FADE_OUT_RATE*2 + pText->dwShowTime )
                {
                    pText->enShowState = eShowHide;
                    break;
                }
                int n = TEXT_FADE_OUT_RATE*2 + pText->dwShowTime - nTime;
                BYTE alpha = 0xFF*n/TEXT_FADE_OUT_RATE;
                pText->dwColor &= 0x00ffffff;
                pText->dwColor |= alpha<<24;
            }
            break;
        case eShowHide:
            continue;
        default:
            assert( false );
            continue;
        }
        if (i < eRiseTextEnd && i >= eRiseTextBegin)
        {
            pText->nY = max(m_nTextYPos[i],pText->nY + pText->fMoveSpeed*deltaTime);
        }
        if( i == eInfoBigTileText )
            FontSystem::DrawTextHighBorder(  pText->strText.c_str(),
            pText->nX, pText->nY, DT_NOCLIP,
            pText->dwColor, pText->nFont );
        else
            FontSystem::DrawText(  pText->strText.c_str(),
            pText->nX, pText->nY, DT_NOCLIP,
            pText->dwColor, pText->nFont );
	}

	dwTimeCost = HQ_TimeGetTime() - dwTimeCost;
	sprintf_s( acCost, 256, "\n CShowScreenText Render Cost: %d\n", dwTimeCost );
	if ( dwTimeCost > 20 )
		OutputDebugStringA( acCost );

	unguard;
}

void CShowScreenText::SetText( SText *pText,
								int x, int y, int nFontSize,
								DWORD time,
								DWORD color, const char* szText,
								EAlign eAlign,
								EShowState eShowState,bool IsTopLevel  )
{
	guardfunc;
	assert( pText );
	assert( szText );
 
	DWORD dwTimeCost = HQ_TimeGetTime();
	char acCost[256] = {0};

	if( !szText )
	{
		return;
	}

	std::wstring wideStr = Common::_tstring::toWideString(szText);

	int nStrLen = strlen( szText );
	int nStrWidth = ControlHelper::Get().GetTextWidth(wideStr, pText->hDC, 0, wideStr.length(),NULL, pText->nFont);//nStrLen*nFontSize/2;
	int nStrHeight = nFontSize;
	pText->enShowState = eShowState;
	pText->dwShowTime = time;
	pText->dwColor = color;
	pText->strText = szText;
	pText->dwStartTime = HQ_TimeGetTime();
	pText->bTopLevel = IsTopLevel;

	//消去名字可以点选的标记~XXX_
	{
		int firstpos = pText->strText.find('~');
		int secondpos = pText->strText.find('_');
		
		if(firstpos!=-1&&secondpos!=-1)
		{
			if(firstpos<secondpos)
			{
				pText->strText.erase(firstpos,1);
				pText->strText.erase(secondpos-1,1);
			}
		}
	}

	switch( eAlign ) 
	{
	case eAlignLeftTop:
		pText->nX = x;
		pText->nY = y;
		break;
	case eAlignTop:
		pText->nX = SCREEN_WIDTH/2 - nStrWidth/2 + x;
		pText->nY = y;
		break;
	case eAlignRightTop:
		pText->nX = SCREEN_WIDTH - nStrWidth + x;
		pText->nY = y;
		break;
	case eAlignLeft:
		pText->nY = SCREEN_HEIGHT/2 - nStrHeight/2 + x;
		pText->nY = y;
		break;
	case eAlignMiddle:
		pText->nX = SCREEN_WIDTH/2 - nStrWidth/2 + x;
		pText->nY = SCREEN_HEIGHT/2 - nStrHeight/2 + y;
		break;
	case eAlignRight:
		pText->nX = SCREEN_WIDTH - nStrWidth + x;
		pText->nY = SCREEN_HEIGHT/2 - nStrHeight/2 + y;
		break;
	case eAlignLeftBottom:
		pText->nX = x;
		pText->nY = SCREEN_HEIGHT - nStrHeight + y;
		break;
	case eAlignBottom:
		pText->nX = SCREEN_WIDTH/2 - nStrWidth/2 + x;
		pText->nY = SCREEN_HEIGHT - nStrHeight + y;
		break;
	case eAlignRightBottom:
		pText->nX = SCREEN_WIDTH - nStrWidth + x;
		pText->nY = SCREEN_HEIGHT - nStrHeight + y;
		break;
	default:
		assert( false );
		pText->nX = x;
		pText->nY = y;
		break;
	} 

	dwTimeCost = HQ_TimeGetTime() - dwTimeCost;
	sprintf_s( acCost, 256, "\n CShowScreenText SetText Cost: %d", dwTimeCost );
	if( dwTimeCost > 10 )
		OutputDebugStringA( acCost );

	unguard;
}

void CShowScreenText::ReCalYPos()
{
    m_nTextYPos[eInfoBigTileText] =  m_nBigTitleYPos * ControlObject::GetSCALE(NULL);
    m_nTextYPos[eInfoSysText] =  m_nSysInfoYPos * ControlObject::GetSCALE(NULL);
    for( int n = eRiseTextBegin; n <= eRiseTextEnd; n++ )
    {
        m_nTextYPos[n] = ( m_nRiseUpInfoYPos - m_nRiseUpInfoFontSize * ( eRiseTextEnd - n ) * 1.5 )* ControlObject::GetSCALE(NULL);
    }
    for( int n = eUnRiseTextBegin; n <= eUnRiseTextEnd; n++ )
    {
        m_nTextYPos[n] = ( m_nSmallInfoYPos + m_nSmallInfoFontSize * ( n - eUnRiseTextBegin ) * 1.5 )* ControlObject::GetSCALE(NULL);
    }
}

void CShowScreenText::MoveTextUp()
{
	SText* pText = m_stText[eRiseTextBegin];
	for( int n = eRiseTextBegin; n < eRiseTextEnd; n++ )
	{
		m_stText[n] = m_stText[n + 1];
	}
	m_stText[eRiseTextEnd] = pText;
	DWORD nowTime = HQ_TimeGetTime();
	if (nowTime > dwPauseStartTime && nowTime - dwPauseStartTime < m_nPauseTime)
	{//在pause期间内
		dwMoveStartTime = dwPauseStartTime + m_nPauseTime;
	}
	else
	{
		dwMoveStartTime = nowTime;
	}
	for ( int n = eRiseTextBegin; n < eRiseTextEnd ; n++ )
	{
		if (m_stText[n]->enShowState != eShowHide)
		{
			m_stText[n]->fMoveSpeed = (float)(m_nTextYPos[n] - m_stText[n]->nY)*ControlObject::GetSCALE(NULL)/m_nScrollTime;
		}
		else
		{
			m_stText[n]->fMoveSpeed = 0;
		}
	}
}

int CShowScreenText::GetFontIndex( int nType )
{
	if( nType < 0 || nType >= eInfoMax )
		return -1;

	return m_stText[nType]->nFont;
}

// 为兼容老接口而存在       added by ZhuoMeng.Hu		[11/17/2010]
void CShowScreenText::SetBigTile( const char* szText, DWORD color, DWORD time )
{
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldScreen_BigTitle, std::string( szText ) );
}

void CShowScreenText::SetTile( const char* szText, DWORD color, DWORD time )
{
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldScreen_NormalTitle, std::string( szText ) );
}

void CShowScreenText::AddInfo( const char* szText, DWORD color, DWORD time, int nInfoIndex, bool IsTopLevel, int eShowState )
{
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldScreen_Info, std::string( szText ) );
}

void CShowScreenText::SetInfo( const char* szText, DWORD color, DWORD time )
{
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldScreen_Info, std::string( szText ) );
}

// 老接口修改
void CShowScreenText::_AddBigInfo( const char* szText,
                                  DWORD color,DWORD time )
{
    guardfunc;
    if ( !szText )
        return;
    SText* pText = m_stText[eInfoBigTileText];
    SetText( pText, -5, m_nBigTitleYPos * ControlObject::GetSCALE(NULL),
        m_nBigTileFontSize, time, color, szText,
        eAlignTop, eShowFadein );
    unguard;
}

void CShowScreenText::_AddSingleLineInfo( const char* szText,
                                         DWORD color,DWORD time )
{
    guardfunc;
    if ( !szText )
        return;
    SText* pText = m_stText[eInfoSysText];
    SetText( pText, 0, m_nSysInfoYPos * ControlObject::GetSCALE(NULL),
        m_nSysInfoFontSize, time, color, szText,
        eAlignTop, eShowFadein );
    unguard;
}

void CShowScreenText::_AddMultiLineRiseInfo( const char* szText, DWORD color, DWORD time, int nInfoIndex, bool IsTopLevel , int eShowState )
{
    guardfunc;
    int nLen = strlen( szText );
    std::string strText;
    for ( int n=0; n<nLen; n++ )
    {
        bool bNewLine = false;
        if ( n+1 < nLen )
        {
            if ( szText[n] == '\\' && szText[n+1] == 'n')
            {
                bNewLine = true;
                n++;
            }
        }
        if ( szText[n] == '\n' )
        {
            bNewLine = true;
        }
        if ( bNewLine == true &&
            strText.size() > 0 )
        {
            _AddRiseInfo( strText.c_str(), color, time, nInfoIndex, IsTopLevel, eShowState );
            strText.clear();
        }
        else
        {
            strText += szText[n];
        }
    }
    if ( strText.size() > 0 )
    {
        _AddRiseInfo( strText.c_str(), color, time, nInfoIndex, IsTopLevel, eShowState );
    }
    unguard;
}

void CShowScreenText::_AddRiseInfo( const char* szText,
                                             DWORD color, DWORD time, int nInfoIndex ,
                                             bool IsTopLevel ,int eShowState)
{
    guardfunc;
    if ( !szText || strlen(szText) == 0 )
        return;
    SText* pText = m_stText[eRiseTextEnd];
    if ((HQ_TimeGetTime() - pText->dwStartTime ) < m_nSkipSameInfoTime && pText->strText == szText )
    {
        return;
    }
    // 	int nShowIndex = -1;
    // 	if ( nInfoIndex != -1 )
    // 	{
    // 		nShowIndex = nInfoIndex + eInfoTextBegin;
    // 	}
    // 	else
    // 	{
    // 		for ( int n=eInfoTextBegin; n<=eInfoTextEnd; n++ )
    // 		{
    // 			SText* pText = m_stText[n];
    // 			if ( pText->enShowState == eShowHide )
    // 			{
    // 				nShowIndex = n;
    // 				break;
    // 			}
    // 		}
    // 	}
    // 	if ( nShowIndex < eInfoTextBegin ||
    // 		nShowIndex > eInfoTextEnd )
    // 	{
    // 		nShowIndex = eInfoTextBegin;
    // 	}
    // 	int y = m_nInfoYPosition * ControlObject::GetSCALE(NULL) + m_nFontSize*(nShowIndex - eInfoTextBegin);

    if (m_stText[eRiseTextEnd]->enShowState != eShowHide)
    {
        MoveTextUp();
    }
    SetText( m_stText[eRiseTextEnd], 0, m_nRiseUpInfoYPos, m_nRiseUpInfoFontSize,
        time, color, szText, eAlignTop, (EShowState)eShowState ,IsTopLevel);
    unguard;
}

void CShowScreenText::_AddMultiLineUnRiseInfo( const char* szText, DWORD color, DWORD time, int nInfoIndex, bool IsTopLevel , int eShowState )
{
    guardfunc;
    int nLen = strlen( szText );
    std::string strText;
    for ( int n = 0; n < nLen; n++ )
    {
        bool bNewLine = false;
        if ( n + 1 < nLen )
        {
            if ( szText[n] == '\\' && szText[n+1] == 'n')
            {
                bNewLine = true;
                n++;
            }
        }
        if ( szText[n] == '\n' )
        {
            bNewLine = true;
        }
        if ( bNewLine == true && strText.size() > 0 )
        {
            _AddUnRiseInfo( strText.c_str(), color, time, nInfoIndex, IsTopLevel, eShowState );
            strText.clear();
        }
        else
        {
            strText += szText[n];
        }
    }
    if ( strText.size() > 0 )
    {
        _AddUnRiseInfo( strText.c_str(), color, time, nInfoIndex, IsTopLevel, eShowState );
    }
    unguard;
}

void CShowScreenText::_AddUnRiseInfo( const char* szText,
                                             DWORD color, DWORD time, int nInfoIndex ,
                                             bool IsTopLevel ,int eShowState)
{
    guardfunc;
    if ( !szText || strlen( szText ) == 0 )
        return;
    m_nUnRiseLines++;
    int nCurrentLine = eUnRiseTextBegin + m_nUnRiseLines - 1;
    if( nCurrentLine > eUnRiseTextEnd )
        return;

    SetText( m_stText[nCurrentLine], 0, m_nTextYPos[nCurrentLine], m_nSmallInfoFontSize,
        time, color, szText, eAlignTop, (EShowState)eShowState ,IsTopLevel );
    unguard;
}

void CShowScreenText::SetUnRiseInfoBegin()
{
    m_nUnRiseLines = 0;
}

void CShowScreenText::SetUnRiseInfoEnd()
{
    if( m_nUnRiseLines == 0 )
        return;

    for( int i = eUnRiseTextBegin + m_nUnRiseLines; i <= eUnRiseTextEnd; ++i )
    {
        SetText( m_stText[i], 0, m_nTextYPos[i], m_nSmallInfoFontSize,
            0, 0xffffffff, "", eAlignTop, eShowFadein );
    }
}
