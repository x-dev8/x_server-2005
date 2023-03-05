#include "MeUi/ControlText.h"
//#include "MeUi/MouseManager.h"
//#include "MeUi/UiManager.h"
//#include "..\HR3D\Tools\BaseGraphics.h"
//#include "../../client/client/NpcCoord.h"
#include "FuncPerformanceLog.h"
#include "MeUi/UiPicture.h"
//#include "..\client\client\Include\Cfg.h"
#include "MeUi/MouseManager.h"
#include "MeUi/ExpressionManager.h"
#include "CxImage/ximage.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/RendererDx8.h"
#include "Me3d/Engine/EngineInstance.h"
#include "MeFont/MeFont.h"
#include <atlimage.h>
#include "Meui/ControlFrame.h" 
#include "Me3d/BaseGraphics.h"
#include "MeFont/MeFontSystem.h"  //##
#include "MeUi/UiDataParsing.h"

// 之所以为4是为兼任以前的错误
#define TEXT_CONTROL_FIX_Y 3


DWORD	ControlText::s_LISTSELECTON_COLOR = 0xFFFFFFFF;
DWORD	ControlText::s_CHAT_HYBER_DOWNLINE_COLOR = 0xFFFFFFFF;
DWORD	ControlText::s_PathFindLinker_COLOR = 0xFFFFFFFF;
DWORD	ControlText::s_CHAT_PLAYERNAME_COLOR = 0xFFFFFFFF;

ControlText::STextData* ControlText::SText::CheckPtInText( int x, int y )
{
	for ( size_t n=0; n<vtTextData.size(); n++ )
	{
		STextData *pTextData = &vtTextData[n];
		if ( x >= pTextData->rc.left &&
			x <= pTextData->rc.right &&
			y >= pTextData->rc.top &&
			y <= pTextData->rc.bottom )
		{
			return pTextData;
		}
	}
	return NULL;
}

bool ControlText::SText::GetTextW( std::wstring *pString )
{
	if ( !pString )
	{
		return false;
	}
	pString->clear();
	for ( size_t n=0; n<vtTextData.size(); n++ )
	{
		*pString += vtTextData[n].str;
	}
	return true;
}

bool ControlText::SText::GetTextA( std::string *pString  )
{
	if ( !pString )
	{
		return false;
	}
	std::wstring str;
	if( !GetTextW( &str ) )
	{
		return false;
	}
	const int nLen = 10240;
	char szChar[nLen];
	WideCharToMultiByte( CP_ACP, 0, str.c_str(), -1,
		szChar, nLen-1, NULL, NULL );
	szChar[nLen-1] = 0;
	*pString = szChar;
	return true;
}
//////////////////////////////////////////////////////////////////////////

// static ControlText* pControlTextMouse = NULL;

ControlText::ControlText(void)
{
	// modified, jiayi, [2010/2/21]
	m_nOffsetHeight = 6*ControlObjectGetSCALE(this);
	m_colUrl = 0xFFFFFF00;
	m_colUrlMouseOn = 0xFFFF0000;
	m_nSyntaxFlag = 0xFFFFFFFF;
	m_nSyntaxUnderLine = 0xFFFFFFFF;
	m_nMaxLines = 0;
	m_nCurShowStartLine = 0;
	m_Analysis = NULL;
	m_bDraging = false;
	m_nCurLineYPos = 0;
	m_pFunOnButtonClick = NULL;
	m_pHyberClick = NULL;
	_bIsDesIconTip = false;
	_bShowUnderLine = true;
	_bIsShowTip = false;
	_singleMaxTextCnt = -1;
	m_dwDrawFlags = 0;
	m_nRenderOffsetY = TEXT_CONTROL_FIX_Y*ControlObjectGetSCALE(this);

	m_nTextHeight = 0;
	m_nTextWidth	= 0;
	m_dwDefaultColor = 0;

	_luaTableName.clear();
	_funHyberClick.clear();

	m_PtInText = NULL;
	m_PtInTextData = NULL;
	m_bOldScrollBarEnabled = true;
	m_bSingleLine = true;
	m_bEnableSelected = false;
	m_nCurShowMaxLine = 0;
	m_CurrCallbackDataArr = NULL;
	m_nCallbackDataArrIndex = 0;
	m_nMaxTextHeight = 3000;
	m_pFunHyberRBtnDown = NULL;

    m_nMaxFontWidth = 3000;
}

ControlText::~ControlText(void)
{
	if ( m_Analysis )
	{
		ScriptStringFree( &m_Analysis );
	}
// 	pControlTextMouse = NULL;
}

void ControlText::SetOffsetY( int oy )
{
	m_nRenderOffsetY = oy;
}

void ControlText::SetCurShowBeginLine( unsigned int nLine )
{
	m_nCurShowStartLine = nLine;
	if ( m_nCurShowStartLine > m_nMaxLines )
	{
		m_nCurShowStartLine = m_nMaxLines;
	}
	m_nCurLineYPos = 0;
	if ( m_nCurShowStartLine == 0 )
	{
		return;
	}
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		for ( size_t i=0; i<pText->vtTextData.size(); i++ )
		{
			STextData* pTextData = &pText->vtTextData[i];
			if ( pTextData->nLine == m_nCurShowStartLine-1 )
			{
				m_nCurLineYPos = max( m_nCurLineYPos, pTextData->rc.bottom );
			}
			else if ( pTextData->nLine > m_nCurShowStartLine-1 )
			{
				break;
			}
		}
	}
	m_UIScroll.SetValue(m_nCurLineYPos);
}

bool ControlText::IsScrollBarShow()
{
	if (m_bSingleLine)
	{
		return false;
	}
	return m_nTextHeight > m_UIScroll.GetPageSize();
}

int ControlText::RefeashByScrollBar()
{
	if (IsScrollBarShow())
	{
		if(m_UIScroll.GetEnable())	
		{
			if (GetFrameFather()->GetFrameRender()->isQueueingEnabled())
			{
				m_nCurLineYPos = m_UIScroll.GetValue();
				m_nCurShowStartLine = -1;
				for ( size_t n=0; n<m_vtText.size(); n++ )
				{
					SText *pText = &m_vtText[n];
					for ( size_t i=0; i<pText->vtTextData.size(); i++ )
					{
						STextData* pTextData = &pText->vtTextData[i];
						if (m_nCurLineYPos < pTextData->rc.bottom )
						{
							m_nCurShowStartLine = pTextData->nLine;
							break;
						}
					}
					if (m_nCurShowStartLine != -1)
					{
						break;
					}
				}
				if (m_nCurShowStartLine == -1)
				{
					m_nCurShowStartLine = 0;
				}
			}
			else
			{
				int nDelta = m_nCurLineYPos - m_UIScroll.GetValue();
				if (nDelta == 0 
					|| (m_UIScroll.IsDrag() && (abs(nDelta) < m_UIScroll.GetStepValue())))
				{
					return m_nCurShowStartLine;
				}
				int nOldCurLine = m_nCurShowStartLine;
				m_nCurLineYPos = m_UIScroll.GetValue();
				m_nCurShowStartLine = 0;
				if (nDelta > 0)
				{//向上
					if (nOldCurLine > 0 &&m_vtText.size() > 0)
					{
						for ( int n=m_vtText.size() -1; n >= 0 ; --n )
						{
							SText *pText = &m_vtText[n];
							if (pText->vtTextData.size() > 1)
							{
								for ( int i=pText->vtTextData.size() - 1; i >= 0; --i )
								{
									STextData* pTextData = &pText->vtTextData[i];
									if ((!m_UIScroll.IsDrag()) &&(pTextData->nLine >= nOldCurLine))
									{
										continue;
									}
									if (m_nCurLineYPos > (pTextData->rc.top - 2))
									{
										{
											m_nCurShowStartLine = pTextData->nLine;
										}
										if (!m_UIScroll.IsDrag())
										{
											m_nCurLineYPos = GetLineTop(m_nCurShowStartLine);
											m_UIScroll.SetValue(m_nCurLineYPos);
										}
										break;
									}
								}
							}
							if (m_nCurShowStartLine != 0)
							{
								break;
							}
						}
					}
				}
				else if (nOldCurLine < m_nMaxLines)
				{//向下
					for ( size_t n=0; n<m_vtText.size(); n++ )
					{
						SText *pText = &m_vtText[n];
						for ( size_t i=0; i<pText->vtTextData.size(); i++ )
						{
							STextData* pTextData = &pText->vtTextData[i];
							if ((!m_UIScroll.IsDrag()) && (pTextData->nLine <= nOldCurLine))
							{
								continue;
							}
							if (m_nCurLineYPos < (pTextData->rc.bottom ))
							{
								m_nCurShowStartLine = pTextData->nLine ;
								if (!m_UIScroll.IsDrag())
								{
									m_nCurLineYPos = GetLineTop(m_nCurShowStartLine);
									if (m_UIScroll.GetMaxValue() - m_nCurLineYPos < m_UIScroll.GetStepValue())
									{
										m_nCurLineYPos = m_UIScroll.GetMaxValue();
									}
									m_UIScroll.SetValue(m_nCurLineYPos);
								}
								break;
							}
						}
						if (m_nCurShowStartLine != 0)
						{
							break;
						}
					}
				}

				if ( m_nCurShowStartLine < 0 )
				{
					m_nCurShowStartLine = 0;
				}
				return m_nCurShowStartLine;

			}
		}
	}
	return 0;
}

int ControlText::GetLineTop( int nLine )
{
	int nlineTop = 1000000;
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		for ( size_t i=0; i<pText->vtTextData.size(); i++ )
		{
			STextData* pTextData = &pText->vtTextData[i];
			if ( (pTextData->nLine < nLine))
			{
				continue;
			}
			if (pTextData->nLine > nLine)
			{
				break;
			}
			if (nlineTop > pTextData->rc.top)
			{
				nlineTop = pTextData->rc.top;
			}
		}
	}
	return nlineTop;
}

//--------------------------------------------------------------------------------
void ControlText::ParseText(std::wstring &_strString)
{
	if (UiDataParsing::Instance()->IsStartNewParse())
	{
		ParseTextNew(_strString);
	}
}

//--------------------------------------------------------------------------------
void ControlText::ParseTextNew(std::wstring &strText)
{
	bool bUseData = false;
	UiCallbackDataBase* pData = NULL;
	if (m_CurrCallbackDataArr && (m_CurrCallbackDataArr->size() > m_nCallbackDataArrIndex) )
	{
		pData = (*m_CurrCallbackDataArr)[m_nCallbackDataArrIndex];
	}

	UiDataParsing::Instance()->BeginParse(strText.size(), m_nSyntaxFlag);
	UiParseData& xParsingData = UiDataParsing::Instance()->GetParsingData();
	xParsingData.InitAndSetColor(m_dwDefaultColor);
	while (UiDataParsing::Instance()->Parsing(strText, pData, bUseData))
	{
		UiParseData& xParsingData = UiDataParsing::Instance()->GetParsingData();
		/*if (xParsingData.m_str.length() <= 0)
		{
			temp_.Reset(m_dwDefaultColor);
			continue;
		}*/

		STextData sTextData;
		sTextData.str = xParsingData.m_str;
		sTextData.pInfo = xParsingData.m_pInfo;
		sTextData.rc = xParsingData.m_rc;
		sTextData.nTextureID = xParsingData.m_nTextureID;

		SText sText;
		sText.type = xParsingData.m_type;
		sText.col = xParsingData.m_col;

		if (bUseData)
		{
			sText.m_callBackData = pData;
			++m_nCallbackDataArrIndex;
			bUseData = false;
			pData = NULL;
			if (m_CurrCallbackDataArr && (m_CurrCallbackDataArr->size() > m_nCallbackDataArrIndex) )
			{
				pData = (*m_CurrCallbackDataArr)[m_nCallbackDataArrIndex];
			}
		}

		sText.vtTextData.push_back(sTextData);
		m_vtText.push_back(sText);

		xParsingData.InitAndSetColor(m_dwDefaultColor);	
	}

	UiDataParsing::Instance()->EndParse();
	
	if( !CalculatePoint() )
	{
		Clear();
		return;
	}
}

bool ControlText::RetriveAnalysis(const std::wstring &str )
{
	if( FontSystem::IsUseNewFont() )
		return true;

	if( m_Analysis )
	{
		ScriptStringFree( &m_Analysis );
		m_Analysis = NULL;
	}
	if (str.length() == 0)
	{
		return false;
	}
	SCRIPT_CONTROL ScriptControl; // For uniscribe
	SCRIPT_STATE   ScriptState;   // For uniscribe
	ZeroMemory( &ScriptControl, sizeof(ScriptControl) );
	ZeroMemory( &ScriptState, sizeof(ScriptState) );
	ScriptApplyDigitSubstitution ( NULL, &ScriptControl, &ScriptState );
	ScriptStringAnalyse( m_hDC,
		str.c_str(),
		(int)str.length() + 1,  // NULL is also analyzed.
		(int)str.length() * 3 / 2 + 16,
		-1,
		SSA_BREAK | SSA_GLYPHS | SSA_FALLBACK | SSA_LINK,
		0,
		&ScriptControl,
		&ScriptState,
		NULL,
		NULL,
		NULL,
		&m_Analysis );
	return m_Analysis != NULL;
}

ControlText::SText& ControlText::GetLastText()
{
	if (m_vtText.empty())
	{
		SText firstText;
		firstText.type = eKeyNormal;
		m_vtText.push_back(firstText);
	}
	return m_vtText.back();
}

void ControlText::SetCurIndex( int nIndex,STextData* pCurLineData )
{

}

ControlText::STextData* ControlText::GetLastTextData()
{
	if (!m_vtText.empty() && !m_vtText.back().vtTextData.empty())
	{
		return &m_vtText.back().vtTextData.back();
	}
	return NULL;
}

const WCHAR * ControlText::GetTextW()
{
	return GetTextWString().c_str();
}

ControlText::STextData* ControlText::GetLastDataByY( int nY )
{
	for ( int n=m_vtText.size() -1; n >= 0 ; --n )
	{
		SText *pText = &m_vtText[n];
		if (pText->vtTextData.size() > 1)
		{
			for ( int i=pText->vtTextData.size() - 1; i >= 0; --i )
			{
				STextData* pData = &pText->vtTextData[i];
				if (pData->rc.top - m_nCurLineYPos< nY)
				{
					return pData;
				}
			}
		}
	}
	return NULL;
}

bool ControlText::OnMouseWheel( bool bUp, const int nX, const int nY )
{
	if ( IsVisable() && IsEnable()  )
	{
		if ( PtInObject(nX, nY,false) == true )
		{
			if ( IsScrollBarShow() )
			{
				if( bUp )
				{
					if( m_UIScroll.GetEnable() )
					{
						if (m_UIScroll.GetValue() - m_UIScroll.GetStepValue() * 3 > 0)
						{
							m_UIScroll.SetValue( m_UIScroll.GetValue() - m_UIScroll.GetStepValue() * 3  );
						}
						else
						{
							m_UIScroll.SetValue(0);
						}
					}
				}
				else
				{
					if( m_UIScroll.GetEnable() )
					{
						if (m_UIScroll.GetValue() + m_UIScroll.GetStepValue() * 3 < m_UIScroll.GetMaxValue())
						{
							m_UIScroll.SetValue( m_UIScroll.GetValue() + m_UIScroll.GetStepValue() * 3 );
						}
						else
						{
							m_UIScroll.SetValue( m_UIScroll.GetMaxValue() );
						}
					}
				}
				RefeashByScrollBar();
				return true;
			}
		}
	}
	return false;

}


EKeyType ControlText::PtInHyber( const int nX, const int nY )
{
	if (m_PtInText)
	{
		return m_PtInText->type;
// 		switch(m_PtInText->type)
// 		{
// 		case eKeyItem:
// 			return HYBER_ITEM;
// 		case eKeyAddress:
// 		case eKeyNpc:
// 			return HYBER_OTHER;
// 		case eKeyPlayer:
// 			return eKeyPlayer;
// 		}
	}
	return eKeyNormal;
}

bool ControlText::PtInObject( const int nX, const int nY ,bool bCheckMsgHold)
{
	if ( ControlObject::PtInObject(nX,nY,bCheckMsgHold) == true )
	{
		return true;
	}
	if ( IsVisable() )
	{
		if( m_UIScroll.GetEnable() )
		{
			if ((!IsSingleLine() )&& IsScrollBarShow() && m_UIScroll.PtInObject( nX, nY ,bCheckMsgHold) == true )
			{
				return true;
			}
		}
	}
	return false;
}

bool ControlText::IsMouseInUI( const int nX, const int nY )
{
	if (ControlObject::IsMouseInUI(nX,nY))
	{
		return true;
	}
	if ( IsVisable() )
	{
		if( m_UIScroll.GetEnable() )
		{
			if ((!IsSingleLine() )&& IsScrollBarShow() && m_UIScroll.IsMouseInUI( nX, nY ) == true )
			{
				return true;
			}
		}

		if( m_PtInText != NULL )
		{
			return true;
		}
	}
	return false;
}

void ControlText::SetRealRect( IN const RECT* prc )
{
	ControlObject::SetRealRect(prc);

	RECT rc = m_UIScroll.GetData()->m_rcRealSize;
	rc.top = 0;//m_pstData->m_rcRealSize.top;
	rc.bottom = m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top;
	m_UIScroll.SetRealRect(&rc);


	RECT rcScreen;
	GetRealRect( &rcScreen );
	m_UIScroll.SetPageSize(rcScreen.bottom - rcScreen.top);
	m_UIScroll.SetMaxValue(m_nTextHeight -  m_UIScroll.GetPageSize() + 2);//添加2的目的是为了显示下划线,因为下划线需要两个像素
}

bool ControlText::OnRButtonUp( UINT nFlags, const int nX, const int nY )
{
	if( IsVisable() && IsEnable()  )
	{
		EKeyType eType = PtInHyber(nX, nY);
		switch( eType )
		{
		case eKeyNormal:
			break;
		case eKeyPlayer:
		case eKeyAddress:
		case eKeyNpc:
			{
				if( m_pFunHyberRBtnDown )
				{
					std::string str;
					m_PtInText->GetTextA( &str );
					m_pFunHyberRBtnDown( this, str.c_str()  ,eType);
					return true;
				}
			}
			break;
		case eKeyItem:
			{
				return true;
			}
			break;
		}
	}
	return false;
}

void ControlText::DrawSelectTextForeGround()
{
	if (!m_stSelect.IsEmpty() && GetFrameFather() && GetFrameFather()->GetFrameRender()->isQueueingEnabled())
	{
		RECT rcScreen;
		GetRealRect( &rcScreen );
		bool bSelectStart = false;
		bool bSelectEnd = false;
		for ( size_t n=0; n<m_vtText.size(); n++ )
		{
			SText *pText = &m_vtText[n];
			if ( !pText->IsImgType() )
			{
				bool bEnd = false;
				for ( size_t i=0; i<pText->vtTextData.size(); i++ )
				{
					STextData* pTextData = &pText->vtTextData[i];
					if ( pTextData->nLine < m_nCurShowStartLine  )
					{
						continue;
					}
					if (pTextData->nLine > m_nCurShowMaxLine)
					{
						bEnd = true;
						break;
					}
					RECT rcDst = pTextData->rc;
					if (!bSelectStart)
					{
						if (m_stSelect.IsStartLine(pTextData))
						{
							bSelectStart = true;
						}
					}
					if (bSelectStart && !bSelectEnd)
					{
						int nHeight = min( FontSystem::GetFontHeight(m_nFontIndex) , rcDst.bottom-rcDst.top ) ; //m_pstData->m_nFontSize
						int nTop = rcScreen.top + rcDst.top + (rcDst.bottom-rcDst.top-nHeight)/2 + 2;
						RECT rcSelect;
						rcSelect.bottom = nTop + nHeight;
						rcSelect.top = nTop;
						if (m_stSelect.IsStartLine(pTextData))
						{
							rcSelect.left = rcScreen.left + m_stSelect.GetStartPos();
						}
						else
						{
							rcSelect.left = rcScreen.left;
						}
						if (m_stSelect.IsEndLine(pTextData))
						{
							bSelectEnd = true;
							rcSelect.right = rcScreen.left + m_stSelect.GetEndPos();
						}
						else
						{
							rcSelect.right = rcScreen.right;
						}
						GetDrawer()->FillRect2D( rcSelect, GetDefaultColor()&0xBF316AC5 );
					}
				}
				if ( bEnd )
				{
					break;
				}
			}
		}
	}
}

void ControlText::Run()
{
	if (m_PtInText && PtInObject(theUiManager.m_ptMoust.x,theUiManager.m_ptMoust.y,false))
	{
		theMouseManager.SetCanSetCursor(true);
		switch(m_PtInText->type)
		{
		case eKeyPlayer:
			{
				theMouseManager.SetUICursor(MouseManager::Type_ChatPlayer);
				theMouseManager.SetCursor(MouseManager::Type_ChatPlayer);
			}
			break;
		case eKeyItem:
			{
				theMouseManager.SetUICursor(MouseManager::Type_ChatHyper);
				theMouseManager.SetCursor(MouseManager::Type_ChatHyper);
			}
			break;
		case eKeyAddress:
		case eKeyNpc:
			{
				theMouseManager.SetUICursor(MouseManager::Type_PathFinding);
				theMouseManager.SetCursor(MouseManager::Type_PathFinding);
			}
			break;
		}
	}

}

// 初始化UI

void ControlText::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	guardfunc
	ControlObject::InitUIData( pFather, pData );
	S_TextData* pTextData = (S_TextData*)pData;
	switch( pTextData->m_nTextAlign ) 
	{
	case AlignMode_LeftTop:
		m_dwDrawFlags = DT_LEFT|DT_TOP;
		break;
	case AlignMode_RightTop:
		m_dwDrawFlags = DT_RIGHT|DT_TOP;
		break;
	case AlignMode_LeftBottom:
		m_dwDrawFlags = DT_LEFT|DT_BOTTOM;
		break;
	case AlignMode_RightBottom:
		m_dwDrawFlags = DT_RIGHT|DT_BOTTOM;
		break;
	case AlignMode_Left:
		m_dwDrawFlags = DT_LEFT|DT_VCENTER;
		break;
	case AlignMode_Top:
		m_dwDrawFlags = DT_TOP|DT_CENTER;
		break;
	case AlignMode_Right:
		m_dwDrawFlags = DT_RIGHT|DT_VCENTER;
		break;
	case AlignMode_Bottom:
		m_dwDrawFlags = DT_BOTTOM|DT_CENTER;
		break;
	case AlignMode_Middle:
		m_dwDrawFlags = DT_CENTER|DT_VCENTER;
		break;
	case AlignMode_LeftMiddle:
		m_dwDrawFlags = DT_LEFT|DT_VCENTER;
		break;
	case AlignMode_TopMiddle:
		m_dwDrawFlags = DT_TOP|DT_VCENTER;
		break;
	case AlignMode_RightMiddle:
		m_dwDrawFlags = DT_RIGHT|DT_VCENTER;
		break;
	case AlignMode_BottomMiddle:
		m_dwDrawFlags = DT_BOTTOM|DT_VCENTER;
		break;
	default:
		break;
	}
	//m_dwDrawFlags = 0;
	SetText( pTextData->m_szCaption );
	m_bSingleLine = pTextData->m_bSingleLine;
	if (!m_bSingleLine)
	{
		m_UIScroll.InitUIData( this, &pTextData->m_stScrollBar );
	}
	else
	{
		m_nOffsetHeight = 0;
		m_nRenderOffsetY = 0;
	}
// 	m_UIScroll.SetPageSize(m_nShowMaxCount);
	SetShowTips();
	unguard;
}

void ControlText::Create( IN const RECT* pRect, const D3DCOLOR colText )
{
	assert( pRect );
	ReleaseUI();
	S_TextData *pText = MeNew S_TextData;
	m_bNeedRelease = true;
	pText->m_nType = Type_Text;
	pText->m_nTextAlign = AlignMode_Middle;
	sprintf( pText->m_szID, "ID_TEXT_AUTO_%d", rand() ); 
	pText->m_rcRealSize = *pRect;
	InitUIData( NULL, pText );
	m_pstData->m_colFont = colText;
}
extern HWND g_hWnd;

// static int m_nOffsetY = 2;
static int IMAGE_OFFSETX = 4;
void ControlText::Render()
{
	ControlObject::Render();
	if ( !IsNeedRender() )
	{
		return;
	}
	RECT rcScreen;
	GetRealRect( &rcScreen );
	if (GetFrameFather() && GetFrameFather()->GetFrameRender()->isQueueingEnabled())
	{
		GetFrameFather()->GetFrameRender()->PushWorkingArea(rcScreen);
		m_nCurShowMaxLine = 0xFFFFFFFF;
		for ( size_t n=0; n<m_vtText.size(); n++ )
		{
			SText *pText = &m_vtText[n];
			if ( pText->IsImgType() )
			{//不能换行
				STextData* pTextData = &pText->vtTextData[0];
				if ( pTextData->nLine < m_nCurShowStartLine )
				{
					continue;
				}
				if (pTextData->nLine > m_nCurShowMaxLine)
				{
					break;
				}
				if ( pTextData->nTextureID != -1 )
				{
					RECT rcDst = rcScreen;
					rcDst.bottom = rcDst.top + pTextData->rc.bottom + m_nRenderOffsetY - m_nCurLineYPos;
					rcDst.top	+= pTextData->rc.top + m_nRenderOffsetY - m_nCurLineYPos;
					if (!m_bSingleLine && ( rcDst.bottom > rcScreen.bottom ))
					{
						m_nCurShowMaxLine = pTextData->nLine;
					}
					rcDst.right = rcDst.left + pTextData->rc.right + IMAGE_OFFSETX;
					rcDst.left	+= pTextData->rc.left + IMAGE_OFFSETX;

					ExpressionManager::GetInstance().DrawExpression((ExpressionManager::ExpressionData*)pTextData->pInfo,rcDst, FontSystem::GetGlobalZ(m_nFontIndex) );
					if (GetFrameFather())
					{
						GetFrameFather()->GetExpressionUpdaterNotNULL()->AddExpress((ExpressionManager::ExpressionData*)pTextData->pInfo);
					}
				}
			}
			else
			{
				bool bEnd = false;
				for ( size_t i=0; i<pText->vtTextData.size(); i++ )
				{
					STextData* pTextData = &pText->vtTextData[i];
					if ( pTextData->nLine < m_nCurShowStartLine  )
					{
						continue;
					}
					if (pTextData->nLine > m_nCurShowMaxLine)
					{
						bEnd = true;
						break;
					}
					RECT rcDst = pTextData->rc;
					int nx = rcScreen.left;
					int ny = rcScreen.top-m_nCurLineYPos;
					rcDst.left += nx;
					rcDst.right += nx;
					rcDst.top += (ny + m_nRenderOffsetY );
					rcDst.bottom += (ny + m_nRenderOffsetY );
					if (!m_bSingleLine && (rcDst.bottom > rcScreen.bottom))
					{
						m_nCurShowMaxLine = pTextData->nLine;
					}
// 					rcDst.bottom = min( rcDst.bottom, rcScreen.bottom+m_nOffsetY * ControlObjectGetREAL_SCALE(this) );
					DWORD col = pText->col;
					bool  bShowLine = false;
					if ( pText == m_PtInText )
					{
						switch(pText->type)
						{
						case eKeyItem:
							{
								col = s_CHAT_HYBER_DOWNLINE_COLOR;
								bShowLine = true;
							}
							break;
						case eKeyAddress:
						case eKeyNpc:
							{
								col = m_colUrlMouseOn;
								bShowLine = true;
							}
							break;
						case eKeyPlayer:
							{
								col = s_CHAT_PLAYERNAME_COLOR;
								bShowLine = true;
							}
							break;
						}
					}
					if ( m_bInFade == true )
					{
						col = ((m_nFadeCurColorA&0xff)<<24)|(col&0x00ffffff);
					}
					if ( _singleMaxTextCnt == -1 ||
						pTextData->str.length() <= _singleMaxTextCnt )
					{

						FontSystem::DrawTextW( pTextData->str.c_str(), &rcDst, /*m_dwDrawFlags & DT_RIGHT ? m_dwDrawFlags : */DT_LEFT | DT_VCENTER | DT_NOCLIP, col, m_nFontIndex, m_bRenderTextWithZ );

					}
					else
					{
						std::wstring showText = pTextData->str;
						showText.erase( _singleMaxTextCnt-2, showText.length()-_singleMaxTextCnt+2 );
						showText += L"..";
						FontSystem::DrawTextW( showText.c_str(), &rcDst, /*m_dwDrawFlags & DT_RIGHT ? m_dwDrawFlags :*/ DT_LEFT | DT_VCENTER | DT_NOCLIP, col, m_nFontIndex, m_bRenderTextWithZ );
					}
					// 画URL下划线
					//if ( pText->type == eKeyNpc && _bShowUnderLine )
					//if(bShowLine)
					if(pText->type == eKeyNpc || pText->type == eKeyItem || pText->type == eKeyPlayer || pText->type == eKeyAddress)
					{
						if(m_nSyntaxUnderLine&pText->type)
						{
							RECT rcUrl = pTextData->rc;
							rcUrl.left += nx;
							rcUrl.right += nx - 1;
							rcUrl.top += (ny+m_nRenderOffsetY);
							rcUrl.bottom += (ny+m_nRenderOffsetY);

							rcUrl.bottom = (rcDst.bottom + rcDst.top + FontSystem::GetFontHeight(m_nFontIndex))/2 + 2;

							if ( rcUrl.bottom <= rcScreen.bottom+m_nRenderOffsetY )
							{
								rcUrl.top = rcUrl.bottom - 1;
								//UiDrawer::FillRect2D( rcUrl, col );
								int nPic = -1;
								theControlPictureManager.BitBlt( &nPic,
									"./data/ui/common/UnderLine.dds",
									&rcUrl, NULL, col );
							}
						}
					}
				}
				if ( bEnd )
				{
					break;
				}
			}

		}
		GetFrameFather()->GetFrameRender()->PopWorkingArea();
		goto Render_End;
	}
	bool bSelectStart = false;
	bool bSelectEnd = false;
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		if ( pText->IsImgType() )
		{//不能换行
			STextData* pTextData = &pText->vtTextData[0];
			if ( pTextData->nLine < m_nCurShowStartLine )
			{
				continue;
			}
			if ( pTextData->nTextureID != -1 )
			{
				RECT rcDst = rcScreen;
				rcDst.bottom = rcDst.top + pTextData->rc.bottom + m_nRenderOffsetY - m_nCurLineYPos;
				rcDst.top	+= pTextData->rc.top + m_nRenderOffsetY - m_nCurLineYPos;
				if (!m_bSingleLine && (rcDst.top < rcScreen.top - 5 || rcDst.bottom > rcScreen.bottom + 2))
				{
					continue;
				}
				rcDst.right = rcDst.left + pTextData->rc.right + IMAGE_OFFSETX;
				rcDst.left	+= pTextData->rc.left + IMAGE_OFFSETX;

				ExpressionManager::GetInstance().DrawExpression((ExpressionManager::ExpressionData*)pTextData->pInfo,rcDst, FontSystem::GetGlobalZ(m_nFontIndex) );
				if (GetFrameFather())
				{
					GetFrameFather()->GetExpressionUpdaterNotNULL()->AddExpress((ExpressionManager::ExpressionData*)pTextData->pInfo);
				}
			}
		}
		else
		{
// 			if (pTextMouseOn == pText)
// 			{
// 				pTextMouseOn = NULL;
// 				pControlTextMouse = NULL;
// 			}
			bool bEnd = false;
			for ( size_t i=0; i<pText->vtTextData.size(); i++ )
			{
				STextData* pTextData = &pText->vtTextData[i];
				if ( pTextData->nLine < m_nCurShowStartLine )
				{
					continue;
				}
				RECT rcDst = pTextData->rc;
				int nx = rcScreen.left;
				int ny = rcScreen.top-m_nCurLineYPos;
				rcDst.left += nx;
				rcDst.right += nx;
				rcDst.top += (ny + m_nRenderOffsetY );
				rcDst.bottom += (ny + m_nRenderOffsetY );
				if (!m_bSingleLine && (rcDst.top + 2 < rcScreen.top || rcDst.bottom > rcScreen.bottom))
				{
					continue;
				}
				if ( rcDst.top >= rcScreen.bottom ||
					rcDst.bottom <= rcScreen.top )
				{
					bEnd = true;
					break;
				}
				rcDst.bottom = min( rcDst.bottom, rcScreen.bottom+m_nRenderOffsetY * ControlObjectGetREAL_SCALE(this) );
				DWORD col = pText->col;
				if ( pText == m_PtInText )
				{
					switch(pText->type)
					{
					case eKeyItem:
						{
							col = s_CHAT_HYBER_DOWNLINE_COLOR;
						}
						break;
					case eKeyAddress:
					case eKeyNpc:
						{
							col = m_colUrlMouseOn;
						}
						break;
					case eKeyPlayer:
						{
							col = s_CHAT_PLAYERNAME_COLOR;
						}
						break;
					}
				}
				if ( m_bInFade == true )
				{
					col = ((m_nFadeCurColorA&0xff)<<24)|(col&0x00ffffff);
				}
				if ( _singleMaxTextCnt == -1 ||
					pTextData->str.length() <= _singleMaxTextCnt )
				{
					
					FontSystem::DrawTextW( pTextData->str.c_str(), &rcDst, /*m_dwDrawFlags & DT_RIGHT ? m_dwDrawFlags : */DT_LEFT | DT_VCENTER | DT_NOCLIP, col, m_nFontIndex, m_bRenderTextWithZ );
					
				}
				else
				{
					std::wstring showText = pTextData->str;
					showText.erase( _singleMaxTextCnt-2, showText.length()-_singleMaxTextCnt+2 );
					showText += L"..";
					FontSystem::DrawTextW( showText.c_str(), &rcDst, /*m_dwDrawFlags & DT_RIGHT ? m_dwDrawFlags :*/ DT_LEFT | DT_VCENTER | DT_NOCLIP, col, m_nFontIndex, m_bRenderTextWithZ );
				}
				// 画URL下划线
 				/*if ( pText->type == eKeyNpc && _bShowUnderLine )
 				{
 					RECT rcUrl = pTextData->rc;
 					rcUrl.left += nx;
 					rcUrl.right += nx;
 					rcUrl.top += (ny+m_nOffsetY );
 					rcUrl.bottom += (ny+m_nOffsetY );
 					if ( rcUrl.bottom <= rcScreen.bottom+m_nOffsetY * ControlObjectGetSCALE(this) )
 					{
 						rcUrl.top = rcUrl.bottom - 1;
 						UiDrawer::FillRect2D( rcUrl, col );
 					}
 				}*/
				if ( !m_stSelect.IsEmpty())
				{
					if (!bSelectStart)
					{
						if (m_stSelect.IsStartLine(pTextData))
						{
							bSelectStart = true;
						}
					}
					if (bSelectStart && !bSelectEnd)
					{
						int nHeight = min( FontSystem::GetFontHeight(m_nFontIndex) , rcDst.bottom-rcDst.top ) ; //m_pstData->m_nFontSize
						int nTop = rcDst.top + (rcDst.bottom-rcDst.top-nHeight)/2 + 2;
						RECT rcSelect;
						rcSelect.bottom = nTop + nHeight;
						rcSelect.top = nTop;
						if (m_stSelect.IsStartLine(pTextData))
						{
							rcSelect.left = rcDst.left + m_stSelect.GetStartPos();
						}
						else
						{
							rcSelect.left = rcDst.left;
						}
						if (m_stSelect.IsEndLine(pTextData))
						{
							bSelectEnd = true;
							rcSelect.right = rcDst.left + m_stSelect.GetEndPos();
						}
						else
						{
							rcSelect.right = rcDst.right;
						}
						GetDrawer()->FillRect2D( rcSelect, GetDefaultColor()&0xBF316AC5 );
					}

				}
			}
			if ( bEnd )
			{
				break;
			}
		}

	}
Render_End:
	if ( IsScrollBarShow() )
	{
		m_UIScroll.SetEnable(m_bOldScrollBarEnabled);
		m_UIScroll.Render();
	}


}

// 解析"\n"
bool ControlText::WordBreak( std::wstring* pOutText, const WCHAR* wInText )
{
	if ( !pOutText || !wInText )
	{
		return false;
	}
	pOutText->clear();
	const WCHAR *p = wInText;
	while ( *p )
	{
		if (!IsSingleLine() && *p == '\\' && *(p+1) == 'n' )
		{
			*pOutText += '\n';
			p+=2;
		}
		else
		{
			*pOutText += *p;
			p+=1;
		}
	}
	return true;
}

void ControlText::SetText( const std::string& szData, DWORD col ,UiCallbackDataArr* pBase)
{
	SetText( szData.c_str(), col ,pBase);
}

void ControlText::SetText( const int nNum, DWORD col ,UiCallbackDataArr* pBase)
{
	char szText[128];
	itoa( nNum, szText, 10 );
	SetText( szText, col ,pBase);
}

void ControlText::SetText( const CHAR* szText, DWORD col ,UiCallbackDataArr* pBase)
{
	if ( !szText )
	{
		return;
	}
	const int nWLen = 10240;
	WCHAR wChar[nWLen];
	MultiByteToWideChar( CP_ACP, 0, szText, -1, wChar, nWLen-1 );
	wChar[nWLen-1] = 0;
	SetTextW( wChar, col ,pBase);
}

void ControlText::SetTextW( const WCHAR* wText, DWORD col ,UiCallbackDataArr* pBase)
{
	if ( !wText || (GetTextWString() == wText && (col != 0) && (col == m_dwDefaultColor)) )
	{
		return;
	}
	if ( !FontSystem::IsUseNewFont() && !m_hDC )   //## 之前是 !m_hDC
	{
		return;
	}

	Clear();
// 	m_strSrcText = wText;
	if ( col == 0 )
	{
		m_dwDefaultColor = m_pstData->m_colFont;
	}
	else
	{
		m_dwDefaultColor = col;
	}
	std::wstring wsTemp(wText);
	_setTextW(wsTemp,pBase);
}

void ControlText::_setTextW( std::wstring& strSrcText ,UiCallbackDataArr* pBase)
{
	if( FontSystem::IsUseNewFont() &&
		GetFrameFather() )
	{
		GetFrameFather()->SetRedraw();
	}
	m_CurrCallbackDataArr = pBase;
	m_nCallbackDataArrIndex = 0;
	std::wstring strText;
	WordBreak( &strText, strSrcText.c_str() );
	ParseText(strText);
	m_stSelect.Empty();

	//
}

bool ControlText::MoveTextDataPos( int nLine, int nEndIndex, int nOffsetX, int nOffsetY )
{
	for ( int n=0; n<(int)m_vtText.size(); n++ )
	{
		if ( nEndIndex != -1 && n>=nEndIndex )
		{
			break;
		}
		SText *pText = &m_vtText[n];
		for ( size_t i=0; i<pText->vtTextData.size(); i++ )
		{
			STextData* pTextData = &pText->vtTextData[i];
			if ( pTextData->nLine == nLine )
			{
				pTextData->rc.left += nOffsetX;
				pTextData->rc.right += nOffsetX;
				pTextData->rc.top += nOffsetY;
				pTextData->rc.bottom += nOffsetY;
			}
		}
	}
	return true;
}
bool ControlText::ReCalculatePoint()
{
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		// modified jiayi, [2010/6/3]
		if( pText && !pText->vtTextData.empty() )
		{
			STextData *pTextData = &pText->vtTextData[0];
			pTextData->nLine = -1;
			// modified, jiayi, [2010/6/3]
			if ( !pText->vtTextData.empty() )
			{
				for (int j = 1; j < pText->vtTextData.size();++j)
				{
					pTextData->str += pText->vtTextData[j].str;
				}
			}
		}		
	}
	m_nTextHeight = 0;
	m_nTextWidth = 0;
	CalculatePoint();
	m_stSelect.Empty();
	return true;
}

bool ControlText::CalculatePointEx()
{
	if (m_vtText.empty())
	{
		return false;
	}

	int nX = 0;
	int nY = m_nTextHeight;
	const int nW = GetWidth() > m_nMaxFontWidth ? m_nMaxFontWidth : GetWidth();
	int nLine = 0;
	if ( nW <= 0 )
	{
		return false;
	}
	int nRowH = FontSystem::GetFontHeight(m_nFontIndex) + m_nOffsetHeight;
	int nOffsetY = 0;
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		// added, jiayi, [2010/6/3]
		if( !( pText && !pText->vtTextData.empty() ) )
			continue;
		//assert( pText->vtTextData.size() == 1 );
		STextData *pTextData = &pText->vtTextData[0];
		if (pTextData->nLine != -1)
		{//本次增量解析
			nLine =  pText->vtTextData.back().nLine + 1;
			continue;
		}
		// 图片
		if ( pText->IsImgType() )
		{
			if ( pTextData->pInfo != NULL )
			{
				int nNeedWidth = (pTextData->rc.right - pTextData->rc.left) + nX;
				if ( nNeedWidth >= nW )
				{
					nX = 0;
					nY += nRowH;
					nRowH = FontSystem::GetFontHeight(m_nFontIndex) + m_nOffsetHeight;
					nOffsetY = 0;
					nLine++;
				}
				pTextData->nLine = nLine;

				ExpressionManager::ExpressionData* pInfo = (ExpressionManager::ExpressionData*)pTextData->pInfo;
				pTextData->rc.right = pInfo->m_nWidth * ControlObjectGetSCALE(this);
				pTextData->rc.left = 0;
				pTextData->rc.bottom = pInfo->m_nHeight * ControlObjectGetSCALE(this);
				pTextData->rc.top = 0;
				pTextData->rc.left += nX;
				pTextData->rc.right += nX;
				pTextData->rc.top += (nY);
				pTextData->rc.bottom += (nY);
				nX += (pTextData->rc.right - pTextData->rc.left);
				//
				int nImgH = (pTextData->rc.bottom - pTextData->rc.top);
				if ( nImgH > nRowH )
				{
					int oy = (nImgH-nRowH)/2;
					MoveTextDataPos( nLine, (int)n, 0, oy );
					nRowH = nImgH;
					nOffsetY += oy;
				}
				else
				{
					int h = (nRowH - nImgH)/2;
					pTextData->rc.top += h;
					pTextData->rc.bottom += h;
				}
			}
		}
		else
		{
			std::wstring str = pTextData->str;
			pText->vtTextData.clear();
			if( str.length() <= 0 )
			{
				continue;
			}
			if ( !FontSystem::IsUseNewFont() && !RetriveAnalysis(str))
			{				
				continue;			
			}			
			size_t nStrIndex = 0;
			int nLastX = 0;
			while ( nStrIndex < str.length() )
			{
				int nCP;
				BOOL bTrail;
				BOOL bEnd;
				XtoCP(  str, nLastX+(nW - nX), &nCP, &bTrail, &bEnd );
				
				int nLen = nCP - (int)nStrIndex;
				if ( nLen <= 0 )
				{
					if ( nX > 0 )
					{
						nX = 0;
						nY += nRowH;
						nRowH = FontSystem::GetFontHeight(m_nFontIndex) + m_nOffsetHeight;
						nOffsetY = 0;
						nLine++;
					}
					else
					{
						/*
						 * Author:	2012-8-29 wangshuai
						 * Desc: 	每天弹几百次，太烦了，先注释掉
						 */
						//assert( false );  
						return false;
					}
				}
				else
				{
					// 检查之间是否有'\n'
					int nWordBreak = -1;
					for ( size_t i=nStrIndex; i<nStrIndex+nLen; i++ )
					{
						if ( str[i] == '\n' )
						{
							nWordBreak = (int)i;
							break;
						}
					}
					int nEndIndex;
					if ( nWordBreak != -1 )
					{
						nEndIndex = nWordBreak + 1;
					}
					else
					{
						nEndIndex = (int)nStrIndex + nLen;
					}
					size_t nCurLen = nEndIndex - nStrIndex;
					
				
					int nEndX;
					CPtoX(str, nEndIndex, FALSE, &nEndX );
					//nEndX=FontSystem::GetTextWidth(m_nFontIndex, str, nStartIndex, nEndIndex) * ControlObject::ControlObjectGetREAL_SCALE(this);

					STextData stTextData;
					stTextData.nLine = nLine;
					stTextData.rc.left = nX + 2;
					stTextData.rc.top = nY + nOffsetY;
					stTextData.rc.right = stTextData.rc.left + (nEndX-nLastX);
					stTextData.rc.bottom = stTextData.rc.top + ( FontSystem::GetFontHeight(m_nFontIndex) + m_nOffsetHeight );
					stTextData.str = str.substr( nStrIndex, nCurLen );
					pText->vtTextData.push_back( stTextData );

					nX += (nEndX-nLastX);
					nLastX = nEndX;
					nStrIndex += nCurLen;
					if ( nWordBreak != -1 )
					{
						nX = 0;
						nY += nRowH;
						nRowH = FontSystem::GetFontHeight(m_nFontIndex) + m_nOffsetHeight;
						nOffsetY = 0;
						nLine++;
						//添加空行
						STextData stTextData;
						stTextData.nLine = nLine;
						stTextData.rc.left = 2;
						stTextData.rc.top = nY + nOffsetY;
						stTextData.rc.right = stTextData.rc.left + 2;
						stTextData.rc.bottom = stTextData.rc.top + ( FontSystem::GetFontHeight(m_nFontIndex)+ m_nOffsetHeight );

						stTextData.str.clear();                        
						pText->vtTextData.push_back(stTextData);
					}
					
				}
				if ( nX >= nW )
				{
					nX = 0;
					nY += nRowH;
					nRowH = FontSystem::GetFontHeight(m_nFontIndex) + m_nOffsetHeight;
					nOffsetY = 0;
					nLine++;
				}
			}
		}
	}

	if (m_vtText.size() != 0)
	{
		int nMinTop = 1000000;
		int nMaxBottom = 0;
		int nMinLeft = 1000000;
		int nMaxRight = 0;
		for ( size_t n=0; n<m_vtText.size(); n++ )
		{
			SText *pText = &m_vtText[n];
			for ( size_t m=0; m<pText->vtTextData.size(); ++m)
			{
				if (nMinTop > pText->vtTextData[m].rc.top)
					nMinTop = pText->vtTextData[m].rc.top;
				if (nMaxBottom < pText->vtTextData[m].rc.bottom)
					nMaxBottom = pText->vtTextData[m].rc.bottom;
				if (nMinLeft > pText->vtTextData[m].rc.left)
					nMinLeft = pText->vtTextData[m].rc.left;
				if (nMaxRight < pText->vtTextData[m].rc.right)
					nMaxRight = pText->vtTextData[m].rc.right;
			}
		}

		m_nTextHeight = nMaxBottom - nMinTop;
		m_nTextWidth = nMaxRight - nMinLeft;
	}

	if (!m_bSingleLine)
	{
		RECT rcScreen;
		GetRealRect( &rcScreen );
		m_UIScroll.SetPageSize(rcScreen.bottom - rcScreen.top);
		m_UIScroll.SetMaxValue(m_nTextHeight  -  m_UIScroll.GetPageSize() + 2);//添加2的目的是为了显示下划线,因为下划线需要两个像素
		m_UIScroll.SetStepValue(( FontSystem::GetFontHeight(m_nFontIndex)+ m_nOffsetHeight ));
		m_UIScroll.OnUpdatePos();
	}
	m_nMaxLines = nLine;
	//
	CheckDrawMode();	
	return true;
}

// 计算坐标
bool ControlText::CalculatePoint()
{
	//assert(false&&"Please use CalculatePointEx()");  //##
	if(FontSystem::IsUseNewFont())
		return CalculatePointEx();

	int nX = 0;
	int nY = m_nTextHeight;
    const int nW = GetWidth() > m_nMaxFontWidth ? m_nMaxFontWidth : GetWidth();
	int nLine = 0;
	if ( nW <= 0 )
	{
		return false;
	}

	int nRowH = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) + m_nOffsetHeight;
	int nOffsetY = 0;
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		// added, jiayi, [2010/6/3]
		if( !( pText && !pText->vtTextData.empty() ) )
			continue;
		//assert( pText->vtTextData.size() == 1 );
		STextData *pTextData = &pText->vtTextData[0];
		if (pTextData->nLine != -1)
		{//本次增量解析
			nLine =  pText->vtTextData.back().nLine + 1;
			continue;
		}
		// 图片
		if ( pText->IsImgType() )
		{
			if ( pTextData->pInfo != NULL )
			{
				int nNeedWidth = (pTextData->rc.right - pTextData->rc.left) + nX;
				if ( nNeedWidth >= nW )
				{
					nX = 0;
					nY += nRowH;
					nRowH = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this)  + m_nOffsetHeight;
					nOffsetY = 0;
					nLine++;
				}
				pTextData->nLine = nLine;

				ExpressionManager::ExpressionData* pInfo = (ExpressionManager::ExpressionData*)pTextData->pInfo;
				pTextData->rc.right = pInfo->m_nWidth * ControlObjectGetSCALE(this);
				pTextData->rc.left = 0;
				pTextData->rc.bottom = pInfo->m_nHeight * ControlObjectGetSCALE(this);
				pTextData->rc.top = 0;
				pTextData->rc.left += nX;
				pTextData->rc.right += nX;
				pTextData->rc.top += (nY);
				pTextData->rc.bottom += (nY);
				nX += (pTextData->rc.right - pTextData->rc.left);
				//
				int nImgH = (pTextData->rc.bottom - pTextData->rc.top)  + m_nOffsetHeight;
				if ( nImgH > nRowH )
				{
					int oy = (nImgH-nRowH)/2;
					MoveTextDataPos( nLine, (int)n, 0, oy );
					nRowH = nImgH;
					nOffsetY += oy;
				}
				else
				{
					int h = (nRowH - nImgH)/2;
					pTextData->rc.top += h;
					pTextData->rc.bottom += h;
				}
			}
		}
		else
		{
			std::wstring str = pTextData->str;
			pText->vtTextData.clear();
			if( str.length() <= 0 )
			{
				continue;
			}
			if (!RetriveAnalysis(str))
			{				
				continue;			
			}			
			size_t nStrIndex = 0;
			int nLastX = 0;
			while ( nStrIndex < str.length() )
			{
				int nCP;
				BOOL bTrail;
				BOOL bEnd;
				XtoCP(  str, nLastX+(nW - nX), &nCP, &bTrail, &bEnd );
				//int nLen = (nCP - (!bEnd&&bTrail?1:0)) - (int)nStrIndex;
				int nLen = nCP - (int)nStrIndex;
				if ( nLen <= 0 )
				{
					if ( nX > 0 )
					{
						nX = 0;
						nY += nRowH;
						nRowH = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) + m_nOffsetHeight;
						nOffsetY = 0;
						nLine++;
					}
					else
					{
						assert( false );
						return false;
					}
				}
				else
				{
					// 检查之间是否有'\n'
					int nWordBreak = -1;
					for ( size_t i=nStrIndex; i<nStrIndex+nLen; i++ )
					{
						if ( str[i] == '\n' )
						{
							nWordBreak = (int)i;
							break;
						}
					}
					int nEndIndex;
					if ( nWordBreak != -1 )
					{
						nEndIndex = nWordBreak + 1;
					}
					else
					{
						nEndIndex = (int)nStrIndex + nLen;
					}
					size_t nCurLen = nEndIndex - nStrIndex;
// 					if ( nCurLen == 0 )
// 					{
// 						nX = 0;
// 						nY += nRowH;
// 						nRowH = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) + m_nOffsetHeight;
// 						nOffsetY = 0;
// 						nStrIndex++;
// 						nLine++;
//                         //为了兼容空行
// 						STextData stTextData;
//                         stTextData.nLine = nLine;
//                         stTextData.rc.left = 0;
//                         stTextData.rc.top = nY + nOffsetY;
//                         stTextData.rc.right = stTextData.rc.left + 2;
//                         stTextData.rc.bottom = stTextData.rc.top + ( m_pstData->m_nFontSize + TEXT_CONTROL_FIX_Y )* ControlObjectGetREAL_SCALE(this);
// 
//                         stTextData.str.clear();                        
//                         pText->vtTextData.push_back(stTextData);
// 					}
// 					else
					{
						int nEndX;
						CPtoX(str, nEndIndex, FALSE, &nEndX );
						STextData stTextData;
						stTextData.nLine = nLine;
						stTextData.rc.left = nX + 2;
						stTextData.rc.top = nY + nOffsetY;
						stTextData.rc.right = stTextData.rc.left + (nEndX-nLastX);
						stTextData.rc.bottom = stTextData.rc.top + ( m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) + m_nOffsetHeight );
						stTextData.str = str.substr( nStrIndex, nCurLen );
						pText->vtTextData.push_back( stTextData );

						nX += (nEndX-nLastX);
						nLastX = nEndX;
						nStrIndex += nCurLen;
						if ( nWordBreak != -1 )
						{
							nX = 0;
							nY += nRowH;
							nRowH = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) + m_nOffsetHeight;
							nOffsetY = 0;
							nLine++;
							//换行并添加空行首
							STextData stTextData;
							stTextData.nLine = nLine;
							stTextData.rc.left = 2;
							stTextData.rc.top = nY + nOffsetY;
							stTextData.rc.right = stTextData.rc.left + 2;
							stTextData.rc.bottom = stTextData.rc.top + ( m_pstData->m_nFontSize* ControlObjectGetREAL_SCALE(this) + m_nOffsetHeight );

							stTextData.str.clear();                        
							pText->vtTextData.push_back(stTextData);
						}
					}
				}
				if ( nX >= nW )
				{
					nX = 0;
					nY += nRowH;
					nRowH = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) + m_nOffsetHeight;
					nOffsetY = 0;
					nLine++;
				}
			}
		}
	}

	if (!m_vtText.empty())
	{
		int nMinTop = 1000000;
		int nMaxBottom = 0;
		for ( size_t n=0; n<m_vtText.size(); n++ )
		{
			SText *pText = &m_vtText[n];
			for ( size_t m=0; m<pText->vtTextData.size(); ++m)
			{
				if (nMinTop > pText->vtTextData[m].rc.top)
					nMinTop = pText->vtTextData[m].rc.top;
				if (nMaxBottom < pText->vtTextData[m].rc.bottom)
					nMaxBottom = pText->vtTextData[m].rc.bottom;
			}
		}

		m_nTextHeight = nMaxBottom - nMinTop;
	}

	if (!m_bSingleLine)
	{
		RECT rcScreen;
		GetRealRect( &rcScreen );
		m_UIScroll.SetPageSize(rcScreen.bottom - rcScreen.top);
		m_UIScroll.SetMaxValue(m_nTextHeight -  m_UIScroll.GetPageSize() );
		m_UIScroll.SetStepValue(( m_pstData->m_nFontSize* ControlObjectGetREAL_SCALE(this) + m_nOffsetHeight ));
		m_UIScroll.OnUpdatePos();
	}
	m_nMaxLines = nLine;
	//
	CheckDrawMode();	
	return true;
}

/*
	检查绘制模式(如中对齐),并进行坐标调整
	目前先不考虑右对齐模式,好像实际运用中用不到
							----   (2007.08.09)
*/
bool ControlText::CheckDrawMode()
{
	// w
	if ( m_dwDrawFlags&DT_CENTER )
	{
		int nLine = 0;
		int nWidth = 0;
		for ( size_t n=0; n<m_vtText.size(); n++ )
		{
			SText* pText = &m_vtText[n];
			for ( size_t i=0; i<pText->vtTextData.size(); i++ )
			{
				STextData *pTextData = &pText->vtTextData[i];
				if ( pTextData->nLine == nLine )
				{
					nWidth += (pTextData->rc.right - pTextData->rc.left);
				}
				else
				{
					if( nWidth != 0 )
					{
						int nx = (GetWidth()-nWidth)/2;
						MoveTextDataPos( nLine, -1, nx, 0 );
					}
					nLine = pTextData->nLine;
					nWidth = (pTextData->rc.right - pTextData->rc.left);
				}
			}
		}
		if( nWidth != 0 )
		{
			int nx = (GetWidth()-nWidth)/2;
			MoveTextDataPos( nLine, -1, nx, 0 );
		}
	}
	// h
	if ( m_dwDrawFlags&DT_VCENTER )
	{
		int nLine = -1;
		int nHeight = 0;
		int nLineHeight = 0;
		for ( size_t n=0; n<m_vtText.size(); n++ )
		{
			SText* pText = &m_vtText[n];
			for ( size_t i=0; i<pText->vtTextData.size(); i++ )
			{
				STextData *pTextData = &pText->vtTextData[i];
				if ( pTextData->nLine != nLine )
				{
					nLine = pTextData->nLine;
					nHeight += nLineHeight;
					nLineHeight = (pTextData->rc.bottom - pTextData->rc.top);
				}
				else
				{
					nLineHeight = max((pTextData->rc.bottom - pTextData->rc.top),nLineHeight);
				}
			}
		}
		nHeight += nLineHeight;
		if( nHeight != 0 )
		{
			int ny = (GetHeight()-nHeight)/2;
			for ( int l=0; l<=m_nMaxLines; l++ )
			{
				MoveTextDataPos( l, -1, 0, ny );
			}
		}
	}
	if ( m_dwDrawFlags&DT_RIGHT )
	{
			int nLine = 0;
			int nWidth = 0;
			for ( size_t n=0; n<m_vtText.size(); n++ )
			{
				SText* pText = &m_vtText[n];
				for ( size_t i=0; i<pText->vtTextData.size(); i++ )
				{
					STextData *pTextData = &pText->vtTextData[i];
					if ( pTextData->nLine == nLine )
					{
						nWidth += (pTextData->rc.right - pTextData->rc.left);
					}
					else
					{
						if( nWidth != 0 )
						{
							int nx = (GetWidth()-nWidth)/2;
							MoveTextDataPos( nLine, -1, nx, 0 );
						}
						nLine = pTextData->nLine;
						nWidth = (pTextData->rc.right - pTextData->rc.left);
					}
				}
			}
			if( nWidth != 0 )
			{
				int nx = (GetWidth()-nWidth - 3);
				MoveTextDataPos( nLine, -1, nx, 0 );
			}
	}
	return true;
}

bool ControlText::CPtoX(const std::wstring &str, int nCP, BOOL bTrail, int *pX ,SCRIPT_STRING_ANALYSIS* pAnalysis)
{
	if ( !pX )
	{
		return false;
	}
	*pX = 0;
	//************************************************************************
	//## add by pyj [20100830]
	if (FontSystem::IsUseNewFont())
	{
		int nStartIndex=0;
		bool bIsTrail = (bTrail==TRUE);
		*pX=FontSystem::GetTextWidth(m_nFontIndex, str, nStartIndex, nCP,bIsTrail);
		return true;
	}
	//************************************************************************
	
	SCRIPT_STRING_ANALYSIS* pLocalAnalysis = pAnalysis;
	if (pLocalAnalysis == NULL && m_Analysis)
	{
		pLocalAnalysis = &m_Analysis;
	}
	HRESULT hr = S_FALSE;
	if ( pLocalAnalysis )
	{
		hr = ScriptStringCPtoX( *pLocalAnalysis, nCP, bTrail, pX );
	}
	//fScale = max( 0.8f, fScale );
	*pX = *pX*ControlObjectGetREAL_SCALE(this);
	return SUCCEEDED( hr );
}

bool ControlText::XtoCP(const std::wstring &str,
					int nX, int *pCP, int *pnTrail, BOOL *pbEnd )
{
	if ( !pCP || !pnTrail || !pbEnd )
	{
		return false;
	}
	*pCP = 0;
	*pnTrail = FALSE;
	*pbEnd = FALSE;
	HRESULT hr = S_FALSE;

	//*************************************************************************************
	//##
	if (FontSystem::IsUseNewFont())
	{
		//nX *= FontSystem::GetFontRealScale(m_nFontIndex);//*1.2f;
		int nStartIndex=0;
		bool bIsEnd;
		FontSystem::GetEndIndexByWidth( m_nFontIndex, str, nStartIndex, nX, *pCP, bIsEnd);
		*pbEnd = (bIsEnd==true);
		return true;
	}
	//*************************************************************************************

	nX = nX* ReciprocalGetREAL_SCALE(this);
	if ( m_Analysis )
	{
		hr = ScriptStringXtoCP( m_Analysis, nX, pCP, pnTrail );
		if( *pCP == -1 && *pnTrail == TRUE )
		{
			*pCP = 0;
			*pnTrail = FALSE;
		}
		else if( *pCP > (int)str.length() && *pnTrail == FALSE )
		{
			*pCP = (int)str.length();
			*pnTrail = TRUE;
			*pbEnd = TRUE;
		}
	}
	return SUCCEEDED( hr );
}

bool ControlText::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
	bool bLastPt = false;
	if (m_PtInText != NULL)
	{
		bLastPt = true;
	}
	m_PtInText = NULL;
	m_PtInTextData = NULL;
	if ( !IsVisable() )
	{
		return false;
	}
	bool bUsed = false;
	if( IsScrollBarShow() && m_UIScroll.GetEnable() )
	{
		if ( m_UIScroll.OnMouseMove( nFlags, nX, nY ) == true )
		{
			if (m_UIScroll.IsDrag())
			{
				RefeashByScrollBar();
			}
			bUsed = true;
		}
	}
	RECT rcScreen;
	GetRealRect( &rcScreen );
	if ( ControlObject::PtInObject( nX, nY ,false) )
	{
		bool isTipShown = false;
		for ( size_t n=0; n<m_vtText.size(); n++ )
		{
			SText *pText = &m_vtText[n];
			if (pText->vtTextData.size() > 0)
			{
				if(pText->vtTextData.back().nLine < m_nCurShowStartLine)
				{
					continue;
				}
				if (pText->vtTextData.front().nLine > m_nCurShowMaxLine)
				{
					break;
				}
			}
			if(m_PtInTextData = pText->CheckPtInText( nX-rcScreen.left,
				nY-rcScreen.top+m_nCurLineYPos-m_nRenderOffsetY))
			{
				m_PtInText = pText;
				if (_bIsShowTip && m_PtInText && m_PtInText->m_callBackData)
				{
					if (m_PtInText->m_callBackData->m_pTipInfo && ( m_PtInText->m_callBackData->m_pTipInfo->m_ucIconInfoLine != 0 ) )
					{
						isTipShown = true;
						theIconInfoMouseTip.SetDisplayInfo( m_PtInText->m_callBackData->m_pTipInfo,
							nX, nY, false,
							m_nFontIndex, FontSystem::GetFontHeight(m_nFontIndex) ,  //m_pstData->m_nFontSize
							m_pstData->m_colFont,
							false );
						bUsed = true;
					}
				}
				//break;
			}
			if((!isTipShown )&&  _bIsShowTip && ( TipInfo.m_ucIconInfoLine != 0 ) )
			{
				theIconInfoMouseTip.SetDisplayInfo( &TipInfo,
					nX, nY, false,
					m_nFontIndex, FontSystem::GetFontHeight(m_nFontIndex) ,  //m_pstData->m_nFontSize
					m_pstData->m_colFont,
					false );
				bUsed = true;
			}

		}
	}
	if( m_bDraging )
	{
		if ( m_PtInTextData != NULL )
		{
			if (!RetriveAnalysis(m_PtInTextData->str))
			{
				return false;
			}
			RECT rcScreen;
			GetRealRect( &rcScreen );
			int x = (nX - rcScreen.left - m_PtInTextData->rc.left );
			int nCP = 0;
			BOOL bTrail = FALSE;
			BOOL bEnd;
			XtoCP(m_PtInTextData->str, x, &nCP, &bTrail,&bEnd );
			int nCurrIndex = nCP + (bTrail?1:0);
			SetCurIndex( nCurrIndex,m_PtInTextData);
			m_stSelect.pEndLine  = m_PtInTextData;
			m_stSelect.nEndIndex = nCurrIndex;
			int nEndX = 0;
			CPtoX( m_PtInTextData->str,nCurrIndex, FALSE, &nEndX );
			m_stSelect.nEndPos = nEndX;
			m_stSelect.eOrder = SSelect::eNone;
		}
		else
		{
			if (ControlObject::PtInObject(nX,nY,false))
			{
				STextData* pData = GetLastDataByY(nY - rcScreen.top);
				if (pData)
				{
					SetCurIndex(pData->str.length(),pData);
					m_stSelect.pEndLine  = pData;
					m_stSelect.nEndIndex = pData->str.length();
					m_stSelect.nEndPos = pData->rc.right;
					m_stSelect.eOrder = SSelect::eNone;
				}
			}

		}
	}
	if (bLastPt || m_PtInText)
	{//鼠标处于可点选目标上是，重绘可点选的颜色
		if (GetFrameFather())
		{
			GetFrameFather()->SetRedraw();
		}
	}
	return bUsed;
}

bool ControlText::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() && IsEnable() )
	{
		RECT rcScreen;
		GetRealRect( &rcScreen );
		if ( m_PtInTextData != NULL )
		{
			if (!RetriveAnalysis(m_PtInTextData->str))
			{
				return false;
			}
            if (m_bEnableSelected)
            {
                int x = (nX - rcScreen.left - m_PtInTextData->rc.left );
                int nCP = 0;
                BOOL bTrail = FALSE;
                BOOL bEnd;
                XtoCP(m_PtInTextData->str, x, &nCP, &bTrail,&bEnd );
                int nCurrIndex = nCP + (bTrail?1:0);
                SetCurIndex( nCurrIndex,m_PtInTextData);
				m_stSelect.pEndLine = m_stSelect.pStartLine = m_PtInTextData;
				m_stSelect.nStartIndex = m_stSelect.nEndIndex = nCurrIndex;
				int nStartX = 0;
				CPtoX(m_PtInTextData->str, nCurrIndex, FALSE, &nStartX );
				m_stSelect.nStartPos = m_stSelect.nEndPos = nStartX;
				m_bDraging = true;
			}

			if ( m_pFunOnButtonClick )
			{
				return m_pFunOnButtonClick(this);
			}
			return true;
		}
		else
		{
			if (PtInObject(nX,nY,true))
			{
				if (IsScrollBarShow() && m_UIScroll.GetEnable() )
				{
					if ( m_UIScroll.OnLButtonDown( nFlags, nX, nY ) == true )
					{
						RefeashByScrollBar();
						return true;
					}
				}
				if (IsMsgHoldup())
				{
					STextData* pData = GetLastDataByY(nY - rcScreen.top);
					if (pData)
					{
						SetCurIndex(pData->str.length(),pData);
						if (m_bEnableSelected)
						{
							m_stSelect.pEndLine = m_stSelect.pStartLine = pData;
							m_stSelect.nStartIndex = m_stSelect.nEndIndex = pData->str.length();
							m_stSelect.nStartPos = m_stSelect.nEndPos = pData->rc.right;
							m_bDraging = true;
						}
					}
				}
			}
			else
			{
				m_bDraging = false;
			}
		}
	}
	return false;
}



bool ControlText::OnLButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() && IsEnable() )
	{
		if ( m_bDraging )
		{
			m_bDraging = false;
		}
		if ( IsScrollBarShow() && m_UIScroll.GetEnable() )
		{
			if ( m_UIScroll.OnLButtonUp( nFlags, nX, nY ) == true )
			{
				return true;
			}
		}
		int bUsed = false;
		if (m_PtInText)
		{
			if (UiDataParsing::Instance()->IsCallbackFunEnable())
			{
				FunClick callBack = UiDataParsing::Instance()->GetCallback(m_PtInText->type);
				if (callBack)
				{
					std::string str;
					m_PtInText->GetTextA( &str );
					callBack(this,str.c_str(),m_PtInText->m_callBackData);					
					bUsed = true;
				}
			}
			else
			{
				switch (m_PtInText->type)
				{
				case eKeyNpc:
				case eKeyAddress:
					{
						if ( m_pHyberClick )
						{
							std::string str;
							m_PtInText->GetTextA( &str );
							m_pHyberClick( this, str.c_str() );
							bUsed = true;
						}
					}
				}

			}
		}
		return bUsed;
	}
	return false;
}

int ControlText::GetCharacterCount()
{
	int nCount = 0;
	for (int  i = 0; i < m_vtText.size(); ++i)
	{
		SText* pText = &m_vtText[i];
		for (int j = 0; j < pText->vtTextData.size(); ++j)
		{
			STextData* pTextData = &pText->vtTextData[j];
			nCount += pTextData->str.size();
		}
	}
	return nCount;

}

const std::wstring& ControlText::GetTextWString()
{
	static std::wstring strText;
	strText.clear();
	for (int  i = 0; i < m_vtText.size(); ++i)
	{
		SText* pText = &m_vtText[i];
		for (int j = 0; j < pText->vtTextData.size(); ++j)
		{
			STextData* pTextData = &pText->vtTextData[j];
			strText += pTextData->str;
		}
	}
	return strText;
}


const char* ControlText::GetText(char* pBuffer ,int nBufferLength)
{
	const std::wstring& strText = GetTextWString();
	const int nLocalLen = 10240;
	static char szLocalChar[nLocalLen];
	char* szChar = szLocalChar;
	int nLen = nLocalLen;
	if (pBuffer)
	{
		szChar = pBuffer;
		nLen = nBufferLength;
	}
// 	std::string			m_strTextA;		// 无控制符文本(多字节)
	WideCharToMultiByte( CP_ACP, 0, strText.c_str(), -1,
		szChar, nLen-1, NULL, NULL );
	szChar[nLen-1] = 0;
// 	m_strTextA = szChar;
	return szChar;
}

const std::string& ControlText::operator=( const std::string& szData )
{
	guardfunc;
	SetText( szData );
	return szData;
	unguard;
}

const int& ControlText::operator=( const int& nNum )
{
	guardfunc;
	SetText( nNum );
	return nNum;
	unguard;
}

void ControlText::setDesIconTip( int nID )
{
	//m_DescriptionTip.SetData( nID, 1, false, false );
}

void ControlText::Clear()
{
	guardfunc;
// 	m_strSrcText.clear();
	for (int  i = 0; i < m_vtText.size(); ++i)
	{
		SText* pText = &m_vtText[i];
		if (pText->m_callBackData)
		{
			pText->m_callBackData->Destory();
			pText->m_callBackData = NULL;
		}
	}
	m_vtText.clear();
	m_nTextHeight = 0;
	m_nTextWidth = 0;
	m_nMaxLines = 0;
	m_nCurShowStartLine = 0;
	m_nCurShowMaxLine = 0;
	m_nCurLineYPos = 0;
	m_nTextWidth = 0;
	m_stSelect.Empty();
	m_UIScroll.Clear();
	m_PtInText = NULL;
	m_PtInTextData = NULL;
	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
	unguard;
}

void ControlText::setTip(const char* data)
{
	guardfunc;
	if( NULL == data )
		return;
	TipInfo.SetInfo( data, DT_LEFT | DT_VCENTER );
	unguard;
}
void ControlText::SetText_HyberClickFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funHyberClick = funName;
	unguard;
}
void ControlText::ResetDevice()
{
	ControlObject::ResetDevice();
	if (!m_bSingleLine)
	{
		m_nOffsetHeight = 6*ControlObjectGetSCALE(this);
		m_nRenderOffsetY = TEXT_CONTROL_FIX_Y*ControlObjectGetSCALE(this);
	}
	ReCalculatePoint();
	if (GetLastTextData())
	{
		SetCurIndex(GetLastTextData()->str.length(),GetLastTextData());
	}
// 	if (!m_strSrcText.empty())
// 	{
// 		_setTextW(); // 更新位置
// 	}
}

int ControlText::GetShowLine()
{
    if(m_vtText.size() <= 0)
        return 0;

    if(m_vtText[0].vtTextData.size() <= 0)
        return 0;

    RECT rcScreen;
    GetRealRect( &rcScreen );
    int height = rcScreen.bottom - rcScreen.top;
    int perRc = m_vtText[0].vtTextData[0].rc.bottom - m_vtText[0].vtTextData[0].rc.top;
    if(perRc == 0)
        perRc = 1;
    return height/perRc;
}

DWORD ControlText::GetDefaultColor()
{
	DWORD dwColoer;
	if( m_dwDefaultColor != 0 )
	{
		dwColoer = m_dwDefaultColor;
	}
	else
	{
		dwColoer = m_pstData->m_colFont;
	}
	return dwColoer;
}

void ControlText::ScrollToTheBegin()
{
	m_UIScroll.SetValue(0);
	RefeashByScrollBar();
}

void ControlText::ScrollToTheLast()
{
	m_UIScroll.SetValue( m_UIScroll.GetMaxValue() );
	RefeashByScrollBar();
}

int ControlText::GetScrollValue()
{
    return m_UIScroll.GetValue();
}

void ControlText::SetScrollValue( int nValue )
{
    nValue = max( 0, nValue );
    nValue = min( nValue, m_UIScroll.GetMaxValue() );
    m_UIScroll.SetValue( nValue );
    RefeashByScrollBar();
}

bool ControlText::IsScrollBarVisable()
{
	return IsScrollBarShow();
}

ControlScrollBar* ControlText::GetScrollBar()
{
	return &m_UIScroll;
}

void ControlText::AddNewLine( const WCHAR* wText , DWORD col ,UiCallbackDataArr* pBase)
{
	if (IsSingleLine())
	{
		return;
	}
	if ( !wText  )
	{
		return;
	}
	if( FontSystem::IsUseNewFont() &&
		GetFrameFather() )
	{
		GetFrameFather()->SetRedraw();
	}
	if (col != 0)
	{
		m_dwDefaultColor = col;
	}
	bool bMoveDown = true;
	if (IsScrollBarShow())
	{
		bMoveDown = GetScrollBar()->GetValue() == GetScrollBar()->GetMaxValue();
	}
	m_CurrCallbackDataArr = pBase;
	m_nCallbackDataArrIndex = 0;
	std::wstring strAddText = wText;
	std::wstring strText;
	WordBreak( &strText, strAddText.c_str() );
	ParseText(strText);
	if (m_stSelect.IsEmpty() && m_nTextHeight > m_nMaxTextHeight + 100)
	{//当总高超过m_nMaxTextHeight，进行一次行删除
		int nDelHeight = min(m_nCurLineYPos - 20, 100);
		if (nDelHeight <= 0 )
		{
			return;
		}
		int nDelLine = 0;
		for ( size_t n=0; n<m_vtText.size(); n++ )
		{
			SText *pText = &m_vtText[n];
			bool bDel = true;
			for ( size_t m=0; m<pText->vtTextData.size(); ++m)
			{
				if (pText->vtTextData[m].rc.bottom > nDelHeight)
				{
					bDel = false;
					nDelLine = pText->vtTextData[m].nLine;
					break;
				}

			}
			if (!bDel)
			{
				break;
			}
		}
		int nDelTextIndex = -1;
		int nDelTextDataIndex = 0;	
		int nDelActualHeight = 0;
		if (nDelLine > 0)
		{
			bool bBreak = false;
			for ( size_t n=0; n<m_vtText.size(); n++ )
			{
				SText *pText = &m_vtText[n];
				for ( size_t m=0; m<pText->vtTextData.size(); ++m)
				{
					if (pText->vtTextData[m].nLine == nDelLine )
					{
						nDelTextIndex = n ;
						nDelTextDataIndex = m ;
					}
					if (pText->vtTextData[m].nLine == nDelLine + 1)
					{
						if(nDelActualHeight == 0 || nDelActualHeight > pText->vtTextData[m].rc.top)
						{
							nDelActualHeight =  pText->vtTextData[m].rc.top;
						}
					}
					if (pText->vtTextData[m].nLine == nDelLine + 2)
					{
						bBreak = true;
						break;
					}
				}
				if (bBreak)
				{
					break;
				}
			}
		}
 		assert(nDelActualHeight >= nDelHeight);
		if (nDelTextIndex != -1)
		{
			for ( size_t n=0; n<nDelTextIndex + 1; n++ )
			{
				SText *pText = &m_vtText[n];
				if (pText->m_callBackData)
				{
					pText->m_callBackData->Destory();
					pText->m_callBackData = NULL;
				}
			}
			m_vtText.erase(m_vtText.begin(),m_vtText.begin() + nDelTextIndex);

			std::vector<STextData>& TextDataArr = m_vtText.front().vtTextData;
			assert(TextDataArr.size() > nDelTextDataIndex);
			if (TextDataArr.size() == nDelTextDataIndex + 1)
			{
				m_vtText.erase(m_vtText.begin(),m_vtText.begin() + 1);
			}
			else
			{
				TextDataArr.erase(TextDataArr.begin(),TextDataArr.begin() + nDelTextDataIndex + 1);
			}
		}

		if (nDelLine > 0)
		{//重现设置现有的内部数据
			m_nMaxLines -= (nDelLine + 1);
			m_nTextHeight -= nDelActualHeight;
			m_nCurLineYPos -= nDelActualHeight;
			m_nCurShowStartLine -= (nDelLine + 1);
			m_nCurShowMaxLine -= (nDelLine + 1);
			m_PtInText = NULL;
			m_PtInTextData = NULL;
			m_UIScroll.SetMaxValue(m_nTextHeight -  m_UIScroll.GetPageSize() + 2);//添加2的目的是为了显示下划线,因为下划线需要两个像素
			m_UIScroll.SetStepValue(( FontSystem::GetFontHeight(m_nFontIndex)+ m_nOffsetHeight ));
			for ( size_t n=0; n<m_vtText.size(); n++ )
			{
				SText *pText = &m_vtText[n];
				for ( size_t m=0; m<pText->vtTextData.size(); ++m)
				{
					pText->vtTextData[m].nLine -= (nDelLine + 1);
					pText->vtTextData[m].rc.top -= nDelActualHeight;
					pText->vtTextData[m].rc.bottom -= nDelActualHeight;
				}
			}
		}
	}
	ClearInvalidPtInText();
	if (bMoveDown)
	{
		ScrollToTheLast();
	}
}

void ControlText::SetMaxFontWidth( int nWidth )
{
    if( nWidth < 0 )
        return;
    m_nMaxFontWidth = nWidth;
}

void ControlText::SetShowTips()
{
	if (strlen(m_pstData->m_szTips) != 0)
	{
		_bIsShowTip = true;
		setTip(m_pstData->m_szTips);
	}
}
void ControlText::ClearInvalidPtInText()
{
	if (m_PtInText!= NULL)
	{
		for( size_t n = 0 ; n < m_vtText.size() ; ++ n )
		{
			SText* pText = &m_vtText[n];
			if( pText == m_PtInText )//found valid
				return;
		}
		m_PtInText = NULL;
		m_PtInTextData = NULL;
	}
}