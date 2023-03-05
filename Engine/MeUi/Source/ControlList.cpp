#include "MeUi/MeUi.h"
#include "MeUi/ControlList.h"
#include "MeUi/UiPicture.h"
#include "MeUi/UiManager.h"
#include "FuncPerformanceLog.h"
#include "Me3d/BaseGraphics.h"
#include "tstring.h"
#include "MeUi/MouseManager.h"
#include "MeUi/ExpressionManager.h"
#include "CxImage/ximage.h"
#include "MeFont/MeFontSystem.h"  //##
#include "MeUi/UiDataParsing.h"
using namespace Common;

const std::string HyberLeft = "<";
const std::string HyberRight = ">";
DWORD	ControlList::s_LISTSELECTON_COLOR = 0xFFFFFFFF;
DWORD	ControlList::s_CHAT_HYBER_DOWNLINE_COLOR = 0xFFFFFFFF;
DWORD	ControlList::s_PathFindLinker_COLOR = 0xFFFFFFFF;
DWORD	ControlList::s_CHAT_PLAYERNAME_COLOR = 0xFFFFFFFF;

// ControlList::funcGlobalParseText ControlList::ms_pfGlobalParseText = 0;
// ControlList::funcFindHyber_Player ControlList::ms_pfFindHyperPlayer = 0;
RECT ControlList::ms_rcSelectBar = { 0, 2, 128, 27 };
RECT ControlList::ms_rcMouseHoverBar = { 0, 32, 128, 57 };
std::string ControlList::ms_strSelectBar = "./data/ui/common/ListSelectBar.dds";
std::string ControlList::ms_strMouseHoverBar = "./data/ui/common/ListSelectBar.dds";

ControlList::ControlList(void)
{
	//OutputDebugStr("gDebugLog");
	m_bCanLDB = true;
	m_nShowStartHeight = 0;
	m_nLastStartHeight = 0;
	m_nCurSelIndex = 0;
	m_nLastCurSel = 0;
	m_nOldCurSel = 0;
	m_nMouseOnSel = 0;
	m_nMouseOnTextData = 0;
	m_eHyberType = eKeyNormal;
	m_nSyntaxFlag = 0xFFFFFFFF;
	m_nShowMaxCount = 0;
	m_pFunSelectChange = NULL;
	m_pFunLDBClick = NULL;
	m_pFunRBClick = NULL;
	m_pFunLBtnDown = NULL;
    m_pFunLBtnUp = NULL;
// 	m_pFunShiftRBClick = NULL;
// 	m_pFunShiftLBClick = NULL;
	m_pFunHyberRBtnDown = NULL;
// 	m_pFunHyberItemClick = NULL;
// 	m_pFunHyberOtherClick = NULL;
	m_pFunOnCollapse = NULL;
	m_pFunOnShowTip = NULL;
	m_bHaveSelBar = true;
	m_dwItemMaxCount = 0xffffffff;
	m_bSelShow = LIST_SHOWBAR;
	//
	m_strSound = UiManager::m_strListSound;
	m_szHyberPlayerName.clear();
	CurHyberItem = NULL;

// 	m_bMouseOnHyber = false;
	m_bEnablePathFinding = true;
	_bIsShowTip = false;
// 	memset( &m_rcMouseOnHyber, 0, sizeof(m_rcMouseOnHyber) );


	m_bAutoSetCurIndex = true;


	_luaTableName.clear();

	_funSelectChangeName.clear();
	_funLDBClickName.clear();
	_funLRBClickName.clear();
// 	_funShiftRBClickName.clear();
// 	_funShiftLBClickName.clear();
// 	_funHyberClickName.clear();
	_funHyberRBtnDownName.clear();
// 	_funHyberItemClickName.clear();

	m_bShowScrollBar = false;
	m_bShiftDown = false;
	m_bOldScrollBarEnabled = true;
// 	m_pFunHyberClick	= NULL;

	m_bEnableShortcutKey = true;
	m_dwDrawFlags = DT_LEFT/*|DT_NOCLIP*/;
	m_nSelBarOffset = -1;
	m_bAlwaysProcessRButtonMsg = false;

	m_bRecalRect = false;
	memset( m_vFadeList, 0, sizeof( SelItemFade ) * ITEM_FADE_COUNT );
	m_bChangeColor = true;
	m_bOnlyLeafCanBeSelected = true;
    m_bIgnoreLBtnDown = false;
    m_nLBtnDownPosX = 0;
    m_nLBtnDownPosY = 0;
}


ControlList::~ControlList(void)
{
	Clear();
}

int   ControlList::GetListItemHeight()
{ 
	return m_nDefaultItemHeight; 
}

void ControlList::Render()
{
	if ( IsNeedRender() )
	{
		if (m_bRecalRect)
		{
			for (int n = 0; n<(int)m_vtpItem.size(); ++n)
			{ 
				m_vtpItem[n]->CalculatePoint(GetListItemHeight(),m_hDC, m_nFontIndex);  //## 增加, this->GetFontIndex()
				CheckDrawMode(m_vtpItem[n]);
			}
			m_bRecalRect = false;
		}
		RECT rcScreen;
		GetRealRect( &rcScreen );
		GetFrameFather()->GetFrameRender()->PushWorkingArea(rcScreen);

		ControlObject::Render();

		RECT rc;
		GetRealRect( &rc );
		DWORD dwColoer = 0;
		int nItemHeight = GetListItemHeight();	
			
		if ( m_bHaveSelBar == true && m_vtpItem.size() > 0 )
		{
			int nBarTop = m_nCurSelIndex*nItemHeight - m_nShowStartHeight;
			if ( nBarTop >= -nItemHeight && nBarTop < m_nHeight )
			{
				int nWidth = rc.right - rc.left;
				RECT rcBar;
				rcBar.left = rc.left;
				rcBar.top = rc.top+nBarTop;
				rcBar.right = rc.right;
				rcBar.bottom = rcBar.top+nItemHeight;
				int nID = -1;
				RECT rcSrc = ms_rcSelectBar;
				if( m_nCurSelIndex >=0 && m_nCurSelIndex < m_vtpItem.size() )
				{
					S_List* pList = m_vtpItem[m_nCurSelIndex];
					if( pList )
					{
						D3DCOLOR col = pList->m_colTextCol;
						if(!m_bChangeColor)
							col = 0xffffffff;

						theControlPictureManager.BitBlt( &nID,
							ms_strSelectBar.c_str(),
							&rcBar, &rcSrc, col );
						if( GetFrameFather() )
							GetFrameFather()->SetRedraw();
					}
				}				
			}
		}

		bool needRenderLine = false;

		if ( m_bHaveSelBar == true && m_bSelShow == LIST_SHOWBAR )
		{
			// 计算消失时间
			DWORD dwCurrentTime = HQ_TimeGetTime();
			for( int i = 0 ; i < ITEM_FADE_COUNT ; ++ i )
			{
				SelItemFade* pFade = &m_vFadeList[i];
				if( !pFade )
					continue;
				if( ( dwCurrentTime - pFade->m_dwBeginTime ) > 500 )//500毫秒以内的进行渐变处理
				{
					pFade->m_dwBeginTime = 0;
					pFade->m_nIndex = 0;
					continue;
				}

				DWORD dwDelta = dwCurrentTime - pFade->m_dwBeginTime;
				if( pFade->m_nIndex < 0 || pFade->m_nIndex >= m_vtpItem.size() )
				{					
					continue;
				}

				int nBarTop = pFade->m_nIndex*nItemHeight - m_nShowStartHeight;
				if ( nBarTop >= -nItemHeight && nBarTop < m_nHeight )
				{
					int nWidth = rc.right - rc.left;
					RECT rcBar;
					rcBar.left = rc.left;
					rcBar.top = rc.top+nBarTop;
					rcBar.right = rc.right;
					rcBar.bottom = rcBar.top+nItemHeight;
					int nID = -1;
					RECT rcSrc = ms_rcMouseHoverBar;
					if( pFade->m_nIndex >=0 && pFade->m_nIndex < m_vtpItem.size() )
					{
						S_List* pList = m_vtpItem[pFade->m_nIndex];
						if( pList )
						{
							D3DCOLOR col = pList->m_colTextCol;
							if(!m_bChangeColor)
								col = 0xffffffff;

							// 变化alpha
							int nAlpha = ( 500.f - (float)dwDelta ) / 500.f * 255;
							int nR = (( col & 0x00ff0000 ) >> 16) ;						
							int nG = (( col & 0x0000ff00 ) >> 8);						
							int nB = (( col & 0x000000ff ));							
							DWORD dwCoverColor = ( (nAlpha)<<24) | ((nR)<<16) | ((nG)<<8) | (nB) ;

							theControlPictureManager.BitBlt( &nID,
								ms_strMouseHoverBar.c_str(),
								&rcBar, &rcSrc, dwCoverColor );
							if( GetFrameFather() )
								GetFrameFather()->SetRedraw();
						}
					}					
				}
			}	

			int nMouseSelTop = m_nMouseOnSel*GetListItemHeight()-m_nShowStartHeight;
			if ( nMouseSelTop >= -GetListItemHeight() && nMouseSelTop < m_nHeight )
			{
				RECT rcMouseOnSel;
				rcMouseOnSel.left = rc.left;
				rcMouseOnSel.top = rc.top+nMouseSelTop;
				rcMouseOnSel.right = rc.right;
				rcMouseOnSel.bottom = rcMouseOnSel.top+GetListItemHeight();
				int nID = -1;
				RECT rcSrc = ms_rcMouseHoverBar;
				if( m_nMouseOnSel >=0 && m_nMouseOnSel < m_vtpItem.size() )
				{
					S_List* pList = m_vtpItem[m_nMouseOnSel];
					if( pList )
					{
						D3DCOLOR col = pList->m_colTextCol;
						if(!m_bChangeColor)
							col = 0xffffffff;
						theControlPictureManager.BitBlt( &nID,
							ms_strMouseHoverBar.c_str(),
							&rcMouseOnSel, &rcSrc, col );
						if( GetFrameFather() )
							GetFrameFather()->SetRedraw();
					}
				}				
				
			}
		}
		int nStartIndex = m_nShowStartHeight/GetListItemHeight() - 1;
		if (nStartIndex < 0)
		{
			nStartIndex = 0;
		}
		RECT rcText;
		for( int n=nStartIndex ;
			n<(int)m_vtpItem.size() && n < nStartIndex+m_nShowMaxCount;
			n++ )
		{
			DWORD dwColoer_Normal = 0;
			DWORD dwColoer_Hyber = 0;

			if( n == m_nCurSelIndex && m_vtpItem[n]->UseSelColor )
			{
				dwColoer_Normal = s_LISTSELECTON_COLOR;
			}
			else if ( m_bInFade)
			{
				dwColoer_Normal = ((m_nFadeCurColorA&0xff)<<24)|(m_vtpItem[n]->m_colTextCol&0x00ffffff);
			}
			else
			{
				dwColoer_Normal = m_vtpItem[n]->m_colTextCol;
			}
			if (m_vtpItem[n]->vtTextData.size() != 0)
			{
                // 默认左对齐
				rcText.left = rc.left + m_vtpItem[n]->GetMargin();
				rcText.right = rc.right;
				rcText.top = rc.top + (n*nItemHeight-m_nShowStartHeight);
				rcText.bottom = rcText.top + nItemHeight;

                // 中对齐 和 右对齐 只支持单行
                if( m_vtpItem[n]->vtTextData.size() == 1 )
                {
                    std::wstring strText = m_vtpItem[n]->vtTextData[0].str;
                    if( strText.size() > 0 )
                    {
                        int nTextWidth = FontSystem::GetTextWidth( m_nFontIndex, strText, 0, strText.size(), false );
                        int nOffset = rc.right - rc.left - nTextWidth;
                        // 文字宽度比控件宽度小才支持右对齐和中对齐
                        if( nOffset > 0 )
                        {
                            if( m_vtpItem[n]->GetAlignMode() == S_List::LIST_ALIGNMODE_MIDDLE )
                            {
                                rcText.left = rc.left + nOffset / 2;
                                rcText.right = rcText.left + nTextWidth;
                            }
                            else if( m_vtpItem[n]->GetAlignMode() == S_List::LIST_ALIGNMODE_RIGHT )
                            {
                                rcText.right = rc.right - m_vtpItem[n]->GetMargin();
                                rcText.left = rc.right - nTextWidth;
                            }
                        }
                    }
                }
				m_vtpItem[n]->Render(rcText,m_nFontIndex,this);
			}

		}
		GetFrameFather()->GetFrameRender()->PopWorkingArea();
		if ( GetTotalHeight() > m_nHeight )
		{
			m_UIScroll.SetEnable(m_bOldScrollBarEnabled);
			m_UIScroll.Render();
		}
		else if (m_bShowScrollBar)
		{
			m_UIScroll.SetEnable(false);
			m_UIScroll.Render();
		}

// 		if( IsVisable())
// 		{
// 			// added, jiayi, [2009/8/27], 不画下划线
// 			if (!needRenderLine && 0)
// 				UpdataLine2D();
// 		}
	}
}
// void ControlList::UpdataLine2D()
// {
// 	GetDrawer()->DrawLine2D(m_rcMouseOnHyber.left - 2, m_rcMouseOnHyber.bottom + 5, 
// 		m_rcMouseOnHyber.right + 2, m_rcMouseOnHyber.bottom + 5, s_CHAT_HYBER_DOWNLINE_COLOR );
// }
bool ControlList::OnMouseWheel( bool bUp, const int nX, const int nY )
{
	if ( IsVisable() && IsEnable()  )
	{
		if ( PtInObject(nX, nY,false) == true )
		{
			if ( GetTotalHeight() > m_nHeight )
			{
				if( bUp )
				{
					if( m_UIScroll.GetEnable() )
					{
						if (m_UIScroll.GetValue() - m_UIScroll.GetStepValue() /** 3*/ > 0)
						{
							m_UIScroll.SetValue( m_UIScroll.GetValue() - m_UIScroll.GetStepValue() /** 3*/  );
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
						if (m_UIScroll.GetValue() + m_UIScroll.GetStepValue() /** 3*/ < m_UIScroll.GetMaxValue())
						{
							m_UIScroll.SetValue( m_UIScroll.GetValue() + m_UIScroll.GetStepValue() /** 3*/ );
						}
						else
						{
							m_UIScroll.SetValue( m_UIScroll.GetMaxValue() );
						}
					}
				}
				Refeash();
			}
			return true;
		}
	}
	return false;
}

bool ControlList::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() && IsEnable()  )
	{
		m_nMouseOnSel = -1;
		m_eHyberType = eKeyNormal;
		m_nMouseOnTextData = NULL;

		bool bUse = false;
		if( GetTotalHeight() > m_nHeight &&	m_UIScroll.IsDrag() )
		{
			Refeash();
			bUse = true;
		}
		
		if ( PtInObject(nX, nY,false) == true )
		{
			RECT rc;
			GetRealRect( &rc );
			m_nMouseOnSel = (nY - rc.top + m_nShowStartHeight)/GetListItemHeight() ;
			m_eHyberType = PtInHyber(nX, nY);
			if ( m_bSelShow )
			{				
				if ( m_nMouseOnSel < (int)m_vtpItem.size() && m_nMouseOnSel >= 0 )
				{
					// 更新fade列表
					if( m_nMouseOnSel >= 0 )
					{
						bool bFound = false;
						SelItemFade* pUseFade = 0;
						for( int i = 0 ; i < ITEM_FADE_COUNT ; ++ i )
						{
							SelItemFade* pFade = &m_vFadeList[i];
							if( !pFade )
								continue;
							if( pFade->m_dwBeginTime == 0 )//可用
								pUseFade = pFade;
							if( pFade->m_nIndex == m_nMouseOnSel )//可用
							{
								pFade->m_dwBeginTime = HQ_TimeGetTime();
								pFade->m_nIndex = m_nMouseOnSel;
								bFound = true;
								break;
							}
						}
						if( !bFound && pUseFade )
						{
							pUseFade->m_dwBeginTime = HQ_TimeGetTime();
							pUseFade->m_nIndex = m_nMouseOnSel;
						}
					}
				}
				GetFrameFather()->SetRedraw();
			}
			if( IsShowTip() )
			{
				bool isTipShown = false;
				if (m_nMouseOnTextData && m_nMouseOnTextData->m_callBackData)
				{
					if (m_nMouseOnTextData->m_callBackData->m_pTipInfo)
					{
						isTipShown = true;
						theIconInfoMouseTip.SetDisplayInfo( m_nMouseOnTextData->m_callBackData->m_pTipInfo,
							nX, nY, false,
							m_nFontIndex, FontSystem::GetFontHeight(m_nFontIndex) ,  //m_pstData->m_nFontSize
							m_pstData->m_colFont,
							false );
					}
				}
				if (!isTipShown)
				{
					if ( m_nMouseOnSel < (int)m_vtpItem.size() && m_nMouseOnSel >= 0 )
					{
						if( m_vtpItem[m_nMouseOnSel] )
						{
							if (m_pFunOnShowTip)
							{
								m_pFunOnShowTip(this,m_vtpItem[m_nMouseOnSel]);
							}

							if( m_vtpItem[m_nMouseOnSel]->_bOnline )
							{
								if( m_vtpItem[m_nMouseOnSel]->m_pTipInfo )
								{
									if(InListContextRect(m_nMouseOnSel,nX,nY))
									{
										TipInfo = *m_vtpItem[m_nMouseOnSel]->m_pTipInfo;
										// modified, jiayi, [2009/7/24]								
										theIconInfoMouseTip.SetDisplayInfo( &TipInfo, nX, nY, false, m_UIScroll.GetFontIndex(), FontSystem::GetFontHeight(m_nFontIndex) ,m_UIScroll.GetFontColor(),false );
									}
								}								
							}
						}
					}
				}
			}

			bUse = true;
		}
		else
		{	
			RECT rc;
			m_UIScroll.GetRealRect( &rc );
			if ( nX < rc.left - 50 * ControlObjectGetSCALE(this) || nX > rc.right + 50 * ControlObjectGetSCALE(this) ||
				nY < rc.top - 50 * ControlObjectGetSCALE(this) || nY > rc.bottom + 50 * ControlObjectGetSCALE(this) )
			{
				m_UIScroll.ClearDrag();
			}
		}

		if( m_UIScroll.GetEnable() && m_UIScroll.IsDrag() )
		{
			if ( GetTotalHeight() > m_nHeight &&	m_UIScroll.OnMouseMove( nFlags, nX, nY ) == true )
			{
				bUse = true;
			}
		}
		return bUse;
	}
	return false;
}
bool ControlList::OnRButtonDown( UINT nFlags, const int nX, const int nY)
{
	if( IsVisable() && IsEnable()  )
	{
		bool inner = false;
		if (m_bAlwaysProcessRButtonMsg)
		{
			RECT rc;
			GetRealRect( &rc );
			if ( m_vtpItem.size() > 0 && nX >= rc.left && nX <= rc.right )
			{
				int h = GetTotalHeight();
				if (nY >= rc.top && nY <= rc.top + h)
					inner = true;
			}
		}
		else
			inner = PtInObject(nX, nY,true);

		if( inner )
		{
			CalCurSelByMouse(nX,nY);

			if( m_vtpItem.size() > 0 )
			{
				if( m_nCurSelIndex >= 0 && m_nCurSelIndex < (int)m_vtpItem.size() )
				{
					return true;
				}
			}
			if ( m_bMsgHoldup == true )
			{
				SetActivate();
			}
			return m_bMsgHoldup;
		}
		
	}
	return false;
}

bool ControlList::OnRButtonUp(UINT nFlags, const int nX, const int nY)
{
	if( IsVisable() && IsEnable()  )
	{
// 		EKeyType eType = PtInHyber(nX, nY);
		switch( m_eHyberType )
		{
		case eKeyNormal:
			break;
		case eKeyPlayer:
		case eKeyAddress:
		case eKeyNpc:
			if( m_pFunHyberRBtnDown && m_nMouseOnTextData)
			{
				m_pFunHyberRBtnDown( this, Common::_tstring::toNarrowString(m_nMouseOnTextData->str.c_str()).c_str() ,m_eHyberType);
				return true;
			}
			break;
		case eKeyItem:
			{
				return true;
			}
			break;
		}

		bool inner = false;
		if (m_bAlwaysProcessRButtonMsg)
		{
			RECT rc;
			GetRealRect( &rc );
			if ( m_vtpItem.size() > 0 && nX >= rc.left && nX <= rc.right )
			{
				int h = GetTotalHeight();
				if (nY >= rc.top && nY <= rc.top + h)
					inner = true;
			}
		}
		else
			inner = PtInObject(nX, nY,true);

		if( inner )
		{
			CalCurSelByMouse(nX,nY);

			if( m_vtpItem.size() > 0 )
			{
				if( m_nCurSelIndex >= 0 && m_nCurSelIndex < (int)m_vtpItem.size() )
				{
					if(m_bRbCanSelect)
					{
						OnSelectChange(m_vtpItem[m_nCurSelIndex]);
					}

					if( m_bShiftDown )
					{
// 						OnShiftRBDown( m_vtpItem[m_nCurSelIndex] );
					}
					else
					{
						OnRBDown( m_vtpItem[m_nCurSelIndex] );
					}

					return true;
				}
			}
			if ( m_bMsgHoldup == true )
			{
				SetActivate();
			}
			ControlObject::PlaySound();

			return m_bMsgHoldup;
		}

	}
	return false;
}

void ControlList::SetShowStartHeight( int val )
{
	m_nShowStartHeight = val;
	if(m_UIScroll.GetEnable())
		m_UIScroll.SetValue( m_nShowStartHeight );
}

EKeyType ControlList::PtInHyber( const int nX, const int nY )
{
	guardfunc;
	
// 	m_szHyberPlayerName.clear();
	if( m_vtpItem.size() == 0 )
		return eKeyNormal;
	if ( m_nMouseOnSel >= (int)m_vtpItem.size() || m_nMouseOnSel < 0 )
		return eKeyNormal;

	RECT rc;
	GetRealRect( &rc );
	if ( nX < rc.left || nX > rc.right || nY < rc.top || nY > rc.bottom )
		return eKeyNormal;

// 	int nCurSel = (nY - rc.top + m_nShowStartHeight)/m_nDefaultItemHeight;
// 	if ( nCurSel > (int)m_vtpItem.size() - 1 )
// 	{
// 		nCurSel = (int)m_vtpItem.size() - 1;
// 	}
// 	nCurSel = nCurSel < 0 ? 0 : nCurSel;

	if (m_nMouseOnSel == -1)
	{
		return eKeyNormal;
	}
	if (m_vtpItem[m_nMouseOnSel]->vtTextData.size() != 0)
	{
		std::vector<S_List::STextData>& textData = m_vtpItem[m_nMouseOnSel]->vtTextData;
		for (int i = 0; i < textData.size();++i)
		{
			S_List::STextData& data = textData[i];
			RECT tmp={rc.left + data.rc.left,rc.top + data.rc.top + (m_nMouseOnSel*GetListItemHeight()-m_nShowStartHeight),rc.left + data.rc.right,rc.top + data.rc.bottom + (m_nMouseOnSel*GetListItemHeight()-m_nShowStartHeight)};
			if ( nX < tmp.left || nX > tmp.right || nY < tmp.top || nY > tmp.bottom )
				continue;
// 			switch (data.type)
// 			{
// 			case eKeyPlayer:
// 				m_szHyberPlayerName = Common::_tstring::toNarrowString(data.str.c_str());
// 			break;
// 			case eKeyAddress:
// 			case eKeyNpc:
// 				m_strHyberClickContent = Common::_tstring::toNarrowString(data.str.c_str());
// 				break;
// 			case eKeyItem:
// 				break;
// 			}
			m_nMouseOnTextData = &data;
			return data.type;
		}
	}
	return eKeyNormal;

// 	EKeyType retType = findHyber_player( nCurSel, nX, nY ) ;
// 	if(retType != eKeyNormal )
// 	{
// 		return retType;
// 	}
// 
// 	return findHyber_item( nCurSel, nX, nY );

	unguard;
}
// EKeyType ControlList::findHyber_player( int index, int x, int y )
// {
// 	guardfunc;
// 	RECT rc;
// 	GetRealRect( &rc );
// 	if ( x < rc.left || x > rc.right || y < rc.top || y > rc.bottom )
// 		return eKeyNormal;
// 
// 	if (m_vtpItem[index]->vtTextData.size() != 0)
// 	{
// 		std::vector<S_List::STextData>& textData = m_vtpItem[index]->vtTextData;
// 		for (int i = 0; i < textData.size();++i)
// 		{
// 			S_List::STextData& data = textData[i];
//  			if (data.type != eKeyPlayer)
//  			{
//  				continue;
//  			}
// 			RECT tmp={rc.left + data.rc.left,rc.top + data.rc.top + (index*GetListItemHeight()-m_nShowStartHeight),rc.left + data.rc.right,rc.top + data.rc.bottom + (index*GetListItemHeight()-m_nShowStartHeight)};
// 			if ( x < tmp.left || x > tmp.right || y < tmp.top || y > tmp.bottom )
// 				continue;
// 
// 			m_szHyberPlayerName = Common::_tstring::toNarrowString(data.str.c_str());
// 			return eKeyPlayer;
// 		}
// 		for (int i = 0; i < textData.size();++i)
// 		{
// 			S_List::STextData& data = textData[i];
// 			if (data.type != eKeyAddress && data.type != eKeyNpc)
// 			{
// 				continue;
// 			}
// 			RECT tmp={rc.left + data.rc.left,rc.top + data.rc.top + (index*GetListItemHeight()-m_nShowStartHeight),rc.left + data.rc.right,rc.top + data.rc.bottom + (index*GetListItemHeight()-m_nShowStartHeight)};
// 			if ( x < tmp.left || x > tmp.right || y < tmp.top || y > tmp.bottom )
// 				continue;
// 
// 			m_strHyberClickContent = Common::_tstring::toNarrowString(data.str.c_str());
// 			return data.type;
// 		}
// 	}
// 	return eKeyNormal;
// 	unguard;
// }
// 
// EKeyType ControlList::findHyber_item( int index, int x, int y )
// {
// 	RECT rc;
// 	GetRealRect( &rc );
// 	if (m_vtpItem[index]->vtTextData.size() != 0)
// 	{
// 		if ( x < rc.left || x > rc.right || y < rc.top || y > rc.bottom )
// 			return eKeyNormal;
// 		std::vector<S_List::STextData>& textData = m_vtpItem[index]->vtTextData;
// 		int nItemCount = -1;
// 		for (int i = 0; i < textData.size();++i)
// 		{
// 			S_List::STextData& data = textData[i];
// 			if (data.type != eKeyItem)
// 				continue;
// 			else if (data.str.length() < 3)
// 				continue;
// 
// 			++nItemCount;
// 			RECT tmp={rc.left + data.rc.left,rc.top + data.rc.top + (index*GetListItemHeight()-m_nShowStartHeight),rc.left + data.rc.right,rc.top + data.rc.bottom +(index*GetListItemHeight()-m_nShowStartHeight)};
// 			if ( x < tmp.left || x > tmp.right || y < tmp.top || y > tmp.bottom )
// 				continue;
// 
// 			CurHyberItem = m_vtpItem[index]->_hyberItemInfoRaw /*+ nItemCount * m_vtpItem[index]->m_nItemSiz*/;
// 			if( !CurHyberItem )
// 				continue;
// 
// 			Common::_tstring itemName = _tstring::toNarrowString(data.str.substr(1, data.str.length() - 2).c_str());
// 			S_IconInfoBase::ms_pfGetReplacedName( S_IconInfoBase::ms_pfGetItemLevel( CurHyberItem ), itemName );
// 			Common::_tstring tstrName( S_IconInfoBase::ms_pfGetItemName( CurHyberItem ) );					
// 			S_IconInfoBase::ms_pfGetReplacedName( S_IconInfoBase::ms_pfGetItemLevel( CurHyberItem ), tstrName );
// 			if ( tstrName != itemName)
// 				continue;
// 
// // 			m_rcMouseOnHyber = tmp;
// 			return eKeyItem;
// 		}
// 		return eKeyNormal;
// 	}

//  	return eKeyNormal;
// }
bool ControlList::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
    if ( IsVisable() && IsEnable() )
    {
        m_nLBtnDownPosX = nX;
        m_nLBtnDownPosY = nY;
        if( m_bIgnoreLBtnDown )
        {
            return false;
        }
        else
        {
            return OnListLButtonDown( nFlags, nX, nY );
        }
    }
    else
    {
        return false;
    }
}

bool ControlList::OnListLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() && IsEnable() )
	{
		if ( GetTotalHeight() > m_nHeight && m_UIScroll.GetEnable() )
		{
			if ( m_UIScroll.OnLButtonDown( nFlags, nX, nY ) == true )
			{
				Refeash();
				return true;
			}
		}
		switch( m_eHyberType )
		{
		case eKeyNormal:
			break;
		case eKeyPlayer:
		case eKeyItem:
		case eKeyAddress:
		case eKeyNpc:
			return true;
			break;
		}
		int nCollapse = -1;
		S_List* pCollapseList = PtOnCollapse(nX, nY,&nCollapse);
		if (pCollapseList)
		{
			if (pCollapseList->m_bCollapse)
			{
				int nOffset = 0;
				int nSubStart = 0;
				for(int i = 0; i < pCollapseList->m_vtpChildItem.size(); ++i)
				{
					S_List* pList = pCollapseList->m_vtpChildItem[i];
					InterInsertList(pList,nCollapse + i + nOffset);
					nSubStart = nCollapse + i + nOffset;
					if(!pList->m_bCollapse)
					{
						if(pList->m_vtpChildItem.size() > 0)
						{
							for (int j = 0;j < pList->m_vtpChildItem.size();++j)
							{
								S_List *pSubList = pList->m_vtpChildItem[j];
								InterInsertList(pSubList,nSubStart + j + 1);
							}
							nOffset += pList->m_vtpChildItem.size();
						}
					}
				}
			}
			else
			{
				for(int i = 0; i < pCollapseList->m_vtpChildItem.size(); ++i)
				{
					S_List *pList = pCollapseList->m_vtpChildItem[i];
					if(pList->m_vtpChildItem.size() > 0)
					{
						if(pList->m_bCollapse)
							m_vtpItem.erase(m_vtpItem.begin() + nCollapse + 1);
						else
						{
							//开始和结束区间
							std::vector<S_List*>::iterator itBegin = m_vtpItem.begin() + nCollapse + 1;
							std::vector<S_List*>::iterator itEnd   = m_vtpItem.begin() + nCollapse + 1 + pList->m_vtpChildItem.size() + 1;
							m_vtpItem.erase(itBegin,itEnd);
						}
					}
					else
						m_vtpItem.erase(m_vtpItem.begin()+nCollapse + 1);
				}
			}

			m_UIScroll.SetMaxValue(GetTotalHeight() - GetHeight());
			pCollapseList->m_bCollapse = !pCollapseList->m_bCollapse;
			if (m_nHeight >= GetTotalHeight() - m_nShowStartHeight)
			{
				SetShowStartHeight(0);
			}
			m_bRecalRect = true;
			if (m_pFunOnCollapse)
			{
				m_pFunOnCollapse(this,pCollapseList);
			}
			return true;
		}
		if (PtInObject(nX, nY,true) == true )
		{
			CalCurSelByMouse(nX,nY);
			if ( m_bMsgHoldup == true )
			{
				SetActivate();
			}
			S_List* pSelList = GetCurSelItem();

			//
			//ControlObject::PlaySound();
			if( m_pFunLBtnDown )
			{
				m_pFunLBtnDown( this, pSelList );
			}

		}
		else
		{
			return false;
		}

		return m_bMsgHoldup;
	}

	return false;

}



bool ControlList::OnLButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() && IsEnable() )
	{
        // 鼠标左键按下后移动就不响应Up消息
        if( m_bIgnoreLBtnDown && ( m_nLBtnDownPosX != nX || m_nLBtnDownPosY != nY ) )
        {
            return false;
        }

        // 左键忽略的消息响应在这里弥补回来
        if( m_bIgnoreLBtnDown )
        {
            OnListLButtonDown( nFlags, nX, nY );
        }

		if ( GetTotalHeight() > m_nHeight && m_UIScroll.GetEnable() )
		{
			if ( m_UIScroll.OnLButtonUp( nFlags, nX, nY ) == true )
			{
				return true;
			}
		}

		if (m_nMouseOnTextData)
		{
			if (UiDataParsing::Instance()->IsCallbackFunEnable())
			{
				FunClick callBack = UiDataParsing::Instance()->GetCallback(m_nMouseOnTextData->type);
				if (callBack)
				{
					callBack(this,Common::_tstring::toNarrowString(m_nMouseOnTextData->str.c_str()).c_str(),m_nMouseOnTextData->m_callBackData);					
					return true;
				}
			}
		}
		if (PtInObject(nX, nY,true) == true )
		{
			if (m_bAutoSetCurIndex)
			{
				CalCurSelByMouse(nX,nY);

				if ( m_nCurSelIndex >= 0 && m_nCurSelIndex < (int)m_vtpItem.size()  )
				{
					OnSelectChange( m_vtpItem[m_nCurSelIndex] );

					if( m_bShiftDown )
					{
// 						OnShiftLBDown( m_vtpItem[m_nCurSelIndex] );
// 						return true;
					}
				}
				// commented out, jiayi, [2009/9/30]
				// 点马到聊天框后会这里至回焦点
// 				if ( m_bMsgHoldup == true )
// 				{
// 					SetActivate();
// 				}
				//
				//ControlObject::PlaySound();
			}

            // List左键弹起增加回调     added by zhuomeng.hu		[3/28/2011]
            S_List* pSelList = GetCurSelItem();
            ControlObject::PlaySound();
            if( m_pFunLBtnUp && pSelList )
            {
                m_pFunLBtnUp( this, pSelList );
            }
		}
		else
		{
			return false;
		}
		return m_bMsgHoldup;
	}
	return false;
}

void ControlList::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	ControlObject::InitUIData( pFather, pData );

	S_ListData* pListData = (S_ListData*)pData;
	//pListData->m_nItemHeight += 5.f;
	m_nDefaultItemHeight = pListData->m_nItemHeight*ControlObjectGetSCALE(this);

	COLORREF Color = pListData->m_colSelBar;
	m_colBar =  D3DCOLOR_ARGB(0xff,GetRValue(Color),GetGValue(Color),GetBValue(Color));
	m_colFrame =  D3DCOLOR_ARGB(0xff,GetRValue(Color),GetGValue(Color),GetBValue(Color));
	m_nShowMaxCount = m_nHeight/GetListItemHeight() + 2;
	m_UIScroll.InitUIData( this, &pListData->m_stScrollBar );
	m_UIScroll.SetStepValue(GetListItemHeight());
    m_UIScroll.SetPageSize(m_nHeight);
	memset( m_vFadeList, 0, sizeof( SelItemFade ) * ITEM_FADE_COUNT );

#ifdef _DEBUG
	m_UIScroll.m_debug_bHasWarning = false;
#endif
}
ControlList::S_List* ControlList::GetParentList( IN int nHiberarchy,int nStartIndex )
{
	if (nHiberarchy == 0)
	{//root
		return NULL;
	}
	if (-1 == nStartIndex)
	{
		nStartIndex = m_vtpItem.size() -1;
	}
	for (int i = nStartIndex; i >= 0; --i)
	{
		if (m_vtpItem[i]->m_nHiberarchy == nHiberarchy -1)
		{
			return m_vtpItem[i];
		}
	}
	assert(0);
	return NULL;
}

ControlList::S_List* ControlList::AddItem( IN const S_List* pItem,UiCallbackDataArr* pBase, const bool bMoveDonw )
{
	if ( !pItem )
	{
		assert( pItem );
		return NULL;
	}
	S_List* pList = NULL;
	if ( m_vtpItem.size() < m_dwItemMaxCount )
	{
		pList = MeNew S_List;
		pList->m_pParentList = this;
		*pList = *pItem;
		if (pList->m_nHiberarchy != -1)
		{
			S_List* pParent = GetParentList(pList->m_nHiberarchy);
			if (pParent)
			{
				pParent->m_vtpChildItem.push_back(pList);
			}
			if (!pParent || !pParent->m_bCollapse)
			{
				m_vtpItem.push_back( pList );
			}
		}
		else
		{
			m_vtpItem.push_back( pList );
		}

		m_UIScroll.SetMaxValue(GetTotalHeight() - GetHeight());
	}
	else
	{
		S_List* pFirstItem = m_vtpItem[0];
		if (pFirstItem->m_nHiberarchy == 0)
		{
			assert(0);
			return NULL;
		}
		for ( UINT n=0; n<m_vtpItem.size()-1; n++ )
		{
			m_vtpItem[n] = m_vtpItem[n+1];
		}
		m_vtpItem[m_vtpItem.size()-1] = pFirstItem;
		*m_vtpItem[m_vtpItem.size()-1] = *pItem;
		pList = m_vtpItem[m_vtpItem.size()-1];

// 		if (m_nShowStartHeight > 0 && m_nShowStartHeight < m_UIScroll.GetMaxValue())
// 		{
// 			--m_nShowStartHeight;
// 			m_UIScroll.SetValue(m_nShowStartHeight);
// 		}
	}

	if ( pList && pList->m_colTextCol == 0 )
	{
		COLORREF Color = m_pstData->m_colFont; // change to ARGB
		pList->m_colTextCol = \
			D3DCOLOR_ARGB(0xff,GetRValue(Color),GetGValue(Color),GetBValue(Color));
	}

	if ( bMoveDonw == true && !m_UIScroll.IsDrag() )
	{
		ScrollToTheLast();
	}
	else
	{
		//m_nStartIndex = 0;
		//m_UIScroll.SetValue( 0 );
	}
	ParseText(pList,pBase);
	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
	return pList;
}

bool ControlList::AddArrayItem( IN const S_List* pItem, const int nItemCount, const bool bMoveDonw )
{
	if ( !pItem )
	{
		assert( pItem );
		return false;
	}
	for ( int n=0; n<nItemCount; n++ )
	{
		AddItem( &pItem[n],NULL, bMoveDonw );
	}
	return true;
}

// bool ControlList::ResetItem( IN const S_List* pItem, const int nItemCount )
// {
// 	Clear();
// 	assert( pItem );
// 	for ( int n=0; n<nItemCount; n++ )
// 	{
// 		AddItem( &pItem[n] ,NULL);
// 	}
// 	return true;
// }

void ControlList::Clear(bool bClearCurrSelectedIndex)
{
	for ( UINT n=0; n<m_vtpItem.size(); n++ )
	{
		S_List* p = m_vtpItem[n];
		delete p;
	}
	m_vtpItem.clear();

	m_nCurSelIndex = -1;
	m_nOldCurSel = -1;
	m_nMouseOnSel = -1;
	m_nMouseOnTextData = NULL;
	m_UIScroll.Clear();
	m_UIScroll.SetStepValue(GetListItemHeight());
	if (bClearCurrSelectedIndex)
	{
		SetShowStartHeight(0);
	}
	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
}
// void ControlList::OnShiftLBDown( IN S_List* pItem )
// {
// 	guardfunc;
// 	if( NULL != state.Get() && _luaTableName.length() > 0 && _funShiftLBClickName.length() > 0 )
// 	{
// 		try
// 		{
// 			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
// 			if( table1Obj.IsTable() )
// 			{
// 				LuaFunction<void> function_( table1Obj[_funShiftLBClickName.c_str()] );
// 				function_( pItem );
// 			}
// 		}
// 		catch (LuaPlus::LuaException &e)
// 		{
// 			char szErr[256] = {0};
// 			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funShiftLBClickName.c_str(), e.GetErrorMessage());
// 			print_error( szErr );
// 		}
// 	}
// 	else
// 	{
// 		if( m_pFunShiftLBClick )
// 		{
// 			m_pFunShiftLBClick( this, pItem );
// 		}
// 	}
// 
// 	unguard;
// }
// void ControlList::OnShiftRBDown( IN S_List* pItem )
// {
// 	guardfunc;
// 	if( NULL != state.Get() && _luaTableName.length() > 0 && _funShiftRBClickName.length() > 0 )
// 	{
// 		try
// 		{
// 			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
// 			if( table1Obj.IsTable() )
// 			{
// 				LuaFunction<void> function_( table1Obj[_funShiftRBClickName.c_str()] );
// 				function_( pItem );
// 			}
// 		}
// 		catch (LuaPlus::LuaException &e)
// 		{
// 			char szErr[256] = {0};
// 			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funShiftRBClickName.c_str(), e.GetErrorMessage());
// 			print_error( szErr );
// 		}
// 	}
// 	else
// 	{
// 		if( m_pFunShiftRBClick )
// 		{
// 			m_pFunShiftRBClick( this, pItem );
// 		}
// 	}
// 
// 
// 	unguard;
// }
void ControlList::OnRBDown( IN S_List* pItem )
{
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funLRBClickName.length() > 0 )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funLRBClickName.c_str()] );
				function_( pItem );
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funLRBClickName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
	}
	else
	{
		if( m_pFunRBClick )
		{
			m_pFunRBClick( this, pItem );
		}
	}

}
void ControlList::OnSelectChange( IN S_List* pItem )
{
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funSelectChangeName.length() > 0 )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funSelectChangeName.c_str()] );
				function_( pItem );
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funSelectChangeName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
	}
	else
	{
		if ( m_pFunSelectChange )
		{
			m_pFunSelectChange( this, pItem );
		}
	}


#ifdef _DEBUG
	if ( m_debug_bHasWarning )
	{
		char szDebug[128];
		char szFatherID[128] = "";
		if ( m_pFather )
		{
			strcpy( szFatherID, m_pFather->GetControlID() );
		}
		sprintf(szDebug,"[%s]::[%s] ControlList::OnSelectChange() not defend!!\r\n", szFatherID, GetControlID() );
		//OutputDebugString(szDebug);
	}
#endif
}

ControlList::S_List* ControlList::GetCurSelItem()
{
//	assert( m_nCurSel >= 0 );
	if ( m_nCurSelIndex >= 0 && m_nCurSelIndex < (int)m_vtpItem.size() )
	{
		return m_vtpItem[m_nCurSelIndex];
	}
	return NULL;
}
ControlList::S_List* ControlList::GetOldCurSelItem()
{
	if( m_nOldCurSel >= 0 && m_nOldCurSel < m_vtpItem.size() )
	{
		return m_vtpItem[m_nOldCurSel];
	}
	return NULL;
}
void ControlList::Create( IN const RECT* pRect, const D3DCOLOR colBack,
						 IN funSelectChange pSelectChangeFun, IN funMouseClick pLDBClickFun )
{
	assert( pRect );
	ReleaseUI();
	S_ListData *pList = MeNew S_ListData;
	m_bNeedRelease = true;
	pList->m_nType = Type_List;
	sprintf( pList->m_szID, "ID_LIST_AUTO_%d", rand() );
	pList->m_rcRealSize = *pRect;
	InitUIData( NULL, pList );
	m_colBackColor = colBack;

	m_pFunSelectChange = pSelectChangeFun;
	m_pFunLDBClick = pLDBClickFun;
}

bool ControlList::SetCurSelIndex( const int nIndex )
{
	//assert( nIndex >= 0 );
	bool bFound = false;
	if ( nIndex < (int)m_vtpItem.size() )
	{
		m_nOldCurSel = m_nCurSelIndex;
		m_nCurSelIndex = nIndex;
		bFound = true;
	}
	else
	{
		m_nOldCurSel = m_nCurSelIndex;
		m_nCurSelIndex = (int)m_vtpItem.size() - 1;
		if ( m_nCurSelIndex < 0 )
		{
			m_nCurSelIndex = 0;
		}
	}
	OnlyLeafCanBeSelected();


	if( m_nShowStartHeight + m_nHeight <= m_nCurSelIndex*GetListItemHeight() )
	{
		SetShowStartHeight(m_nCurSelIndex*GetListItemHeight() - m_nHeight + GetListItemHeight());
	}
	
	return bFound;
}

bool ControlList::SetLastCurSelIndex( const int nIndex )
{
    if( nIndex < 0 || nIndex > (int)m_vtpItem.size() )
        return false;

    m_nLastCurSel = nIndex;
    return true;
}

ControlList::S_List* ControlList::FindItemByID( const int nID )
{
	for ( UINT n=0; n<m_vtpItem.size(); n++ )
	{
		//if ( m_vtpItem[n]->m_nID == nID )
		if ( n == nID )
		{
			return m_vtpItem[n];
		}
	}
	return NULL;
}
void ControlList::setItemTip( int index, const char* tip )	//设置某个item的tip
{
	guardfunc;
	for ( UINT n=0; n<m_vtpItem.size(); n++ )
	{
		if ( n == index && NULL != tip )
		{
			if( NULL != m_vtpItem[n] )
				m_vtpItem[n]->setTip( tip );
		}
	}
	unguard;
}
int ControlList::FindItemByItem( const char* item )
{
	for ( UINT n=0; n<m_vtpItem.size(); n++ )
	{
		if ( strcmp( m_vtpItem[n]->m_szText, item) == 0 )
		{
			return n;
		}
	}
	return -1;
}
bool ControlList::OnLButtonDBClick( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() && m_bCanLDB)
	{
		if (ControlObject::PtInObject(nX,nY,true) == true )
		{
			CalCurSelByMouse(nX,nY);

			if ( m_nCurSelIndex >= 0 && m_nCurSelIndex < (int)m_vtpItem.size() )
			{
				OnLDBClick( m_vtpItem[m_nCurSelIndex] );
			}
			// commented out, jiayi, [2009/9/30]
			// 点马到聊天框后会这里至回焦点
// 			if ( m_bMsgHoldup == true )
// 			{
// 				SetActivate();
// 			}
			return true;
		}
	}
	return false;
}

void ControlList::OnLDBClick( IN S_List* pItem )
{
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funLDBClickName.length() > 0 )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funLDBClickName.c_str()] );
				function_( pItem );
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funLDBClickName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
	}
	else
	{
		if ( m_pFunLDBClick )
		{
			m_pFunLDBClick( this, pItem );
		}
	}


#ifdef _DEBUG
	if ( m_debug_bHasWarning )
	{
		char szDebug[128];
		char szFatherID[128] = "";
		if ( m_pFather )
		{
			strcpy( szFatherID, m_pFather->GetControlID() );
		}
		sprintf(szDebug,"[%s]::[%s] ControlList::OnLDBClick() not defend!!\r\n", szFatherID, GetControlID() );
		//OutputDebugString(szDebug);
	}
#endif
}

bool ControlList::OnKeyDown( UINT nChar )
{
	if ( IsVisable() && IsActivated() && m_bEnableShortcutKey )
	{
		bool bUse = true;
		switch( nChar )
		{
		case VK_UP:
			{
				m_nOldCurSel = m_nCurSelIndex;
				if( --m_nCurSelIndex < 0 )
				{
					m_nCurSelIndex = 0;
				}
				int nShowStartHeight = m_nShowStartHeight;
				if( m_nCurSelIndex*GetListItemHeight() < m_nShowStartHeight )
				{
					nShowStartHeight -= GetListItemHeight();
					if ( nShowStartHeight < 0 )
					{
						nShowStartHeight = 0;
					}
				}
				SetShowStartHeight(nShowStartHeight);

				if ( m_nOldCurSel != m_nCurSelIndex && 
					m_nCurSelIndex >= 0 &&
					m_nCurSelIndex < m_vtpItem.size() )
				{
					OnSelectChange( m_vtpItem[m_nCurSelIndex] );
				}
			}
			break;
		case VK_DOWN:
			{
				m_nOldCurSel = m_nCurSelIndex;
				if( ++m_nCurSelIndex > (int)m_vtpItem.size() - 1 )
				{
					m_nCurSelIndex = (int)m_vtpItem.size() - 1;
				}
				int nShowStartHeight = m_nShowStartHeight;
				if ( m_nCurSelIndex*GetListItemHeight() >= m_nShowStartHeight + m_nHeight )
				{
					nShowStartHeight+= GetListItemHeight();
					if ( nShowStartHeight > GetTotalHeight()-m_nHeight)
					{
						nShowStartHeight = GetTotalHeight()-m_nHeight;
					}
				}
				SetShowStartHeight(nShowStartHeight);

				if ( m_nOldCurSel != m_nCurSelIndex &&
					m_nCurSelIndex >= 0 &&
					m_nCurSelIndex < m_vtpItem.size() )
				{
					OnSelectChange( m_vtpItem[m_nCurSelIndex] );
				}
			}
			break;
		case VK_LSHIFT:
		case VK_RSHIFT:
			m_bShiftDown = true;
			break;
		default:
			bUse = false;
			break;
		}
		return bUse;
	}
	return false;
}

int ControlList::Refeash()
{
	if(GetTotalHeight() > m_nHeight)
	{
		if(m_UIScroll.GetEnable())	//应该是不可用 现在 暂时用这个代替 有时间再改
		{
			SetShowStartHeight(m_UIScroll.GetValue());
			//float fRate = (float)m_UIScroll.GetValue()/m_UIScroll.GetMaxValue();

			//m_nStartIndex = (int)((m_vtpItem.size()-m_nShowMaxCount)*fRate+0.5f);
			//if( (m_vtpItem.size())*fRate+0.5f > m_nShowMaxCount)
			//	m_nStartIndex = (int)((m_vtpItem.size())*fRate+0.5f - m_nShowMaxCount);
			//else
			//	m_nStartIndex = (int)((m_vtpItem.size())*fRate+0.5f );

			if ( m_nShowStartHeight < 0 )
			{
				SetShowStartHeight(0);
			}
			return m_nShowStartHeight;
		}
	}
	//else
	return 0;
}

void ControlList::SetScrollPos( const int nX, const int nY )
{
	RECT rc;
	GetRealRect( &rc );
	m_UIScroll.SetPos( rc.left+nX, rc.top+nY );
}

bool ControlList::PtInObject( const int nX, const int nY ,bool bCheckMsgHold)
{
	if (ControlObject::PtInObject(nX,nY,bCheckMsgHold) == true )
	{
		return true;
	}
	if ( IsVisable() )
	{
		if( m_UIScroll.GetEnable() )
		{
			if ( m_UIScroll.PtInObject( nX, nY ,bCheckMsgHold) == true )
			{
				return true;
			}
		}
	}
	return false;
}

bool ControlList::IsMouseInUI( const int nX, const int nY )
{
	if (ControlObject::IsMouseInUI(nX,nY) == true )
	{
		return true;
	}
	if ( IsVisable() )
	{
		if( m_UIScroll.GetEnable() )
		{
			if ( m_UIScroll.IsMouseInUI( nX, nY ) == true )
			{
				return true;
			}
		}
		if(PtOnCollapse(nX, nY))
			return true;

		if( m_eHyberType != eKeyNormal )
		{
			return true;
		}
	}
	return false;
}

void ControlList::SetScrollValue(int nValue)
{
	int nMax = m_UIScroll.GetMaxValue();
	nValue = nValue < 0 ? 0 : nValue > nMax ? nMax : nValue;

	if( m_UIScroll.GetEnable() )
	{
		m_UIScroll.SetValue(nValue);
	}
	Refeash();
}

void ControlList::BeginUpdate()
{
	m_nLastStartHeight = m_nShowStartHeight;
	m_nLastCurSel = m_nCurSelIndex;
	m_nLastMouseOnSel = m_nMouseOnSel;
}

void ControlList::EndUpdate()
{
	if ((m_nLastStartHeight < GetTotalHeight()) 
		&& ((GetTotalHeight() - m_nLastStartHeight) >= GetHeight()))
	{
		SetShowStartHeight(m_nLastStartHeight);
	}
	else
	{
		if (GetTotalHeight() > GetHeight())
		{
			SetShowStartHeight(GetTotalHeight() - GetHeight());
		}
		else
		{
			SetShowStartHeight(0);
		}
	}
	if (m_nLastCurSel < GetListItemCnt())
	{
		m_nCurSelIndex = m_nLastCurSel;
		OnlyLeafCanBeSelected();
	}
	else
	{
		SetCurSelIndex(0);
	}
	if (m_nLastMouseOnSel < GetListItemCnt())
	{
		m_nMouseOnSel = m_nLastMouseOnSel;
	}
}

void ControlList::SetSelectChangeFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funSelectChangeName = funName;
	unguard;
}
void ControlList::SetRBClickFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funLRBClickName = funName;
	unguard;
}
// void ControlList::SetShiftRBClickFun_2lua( const char* luaTable, const char* funName )
// {
// 	guardfunc;
// 	_luaTableName = luaTable;
// 	_funShiftRBClickName = funName;
// 	unguard;
// }
// void ControlList::SetShiftLBClickFun_2lua( const char* luaTable, const char* funName )
// {
// 	guardfunc;
// 	_luaTableName = luaTable;
// 	_funShiftLBClickName = funName;
// 	unguard;
// }
void ControlList::SetLDBClickFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funLDBClickName = funName;
	unguard;
}
// void ControlList::SetHyberClickFun_2lua( const char* luaTable, const char* funName )
// {
// 	guardfunc;
// 	_luaTableName = luaTable;
// 	_funHyberClickName = funName;
// 	unguard;
// }
void ControlList::SetHyberRBtnDown_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funHyberRBtnDownName = funName;
	unguard;
}
// void ControlList::SetHyberItemClick_2lua( const char* luaTable, const char* funName )
// {
// 	guardfunc;
// 	_luaTableName = luaTable;
// 	_funHyberItemClickName = funName;
// 	unguard;
// }
void ControlList::ResetDevice()
{
	ControlObject::ResetDevice();
	m_UIScroll.ResetDevice();

	S_ListData* pListData = (S_ListData*)m_pstData;
	m_nDefaultItemHeight = pListData->m_nItemHeight * ControlObjectGetSCALE(this);
}
void ControlList::SetLeftScrollBar(bool b)
{
	if (b)
	{
		int w = m_UIScroll.GetData()->m_rcRealSize.right - m_UIScroll.GetData()->m_rcRealSize.left;
		m_UIScroll.GetData()->m_rcRealSize.left = -w;
		m_UIScroll.GetData()->m_rcRealSize.right = 0;
		m_pstData->m_rcRealSize.left += w;
		m_pstData->m_rcRealSize.right += w;
	}
}

bool ControlList::OnKeyUp( UINT nChar )
{
	if( nChar == VK_LSHIFT || nChar == VK_RSHIFT )
		m_bShiftDown = false;
	return false;
}

void ControlList::ParseText(  S_List* pItem ,UiCallbackDataArr* pBase)
{
	static const int scnMaxLineHeight = 1000;
	int lineHeight = 0;
	pItem->ParseText(lineHeight,pBase,m_nSyntaxFlag);
	lineHeight = min( lineHeight, scnMaxLineHeight );
	while(lineHeight > GetListItemHeight() + 2)
	{
		if (pItem->IsExistImg())
		{
			S_List list;
			list.m_nHiberarchy = pItem->m_nHiberarchy;
			AddItem(&list,NULL);
		}
		lineHeight -= GetListItemHeight() + 2;
	}
	m_bRecalRect = true;
}

void ControlList::SetRealRect( const RECT* prc )
{
	ControlObject::SetRealRect(prc);

	RECT rc = m_UIScroll.GetData()->m_rcRealSize;
	rc.top = 0;//m_pstData->m_rcRealSize.top;
	rc.bottom = m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top;
	m_UIScroll.SetRealRect(&rc);

	S_ListData* pListData = (S_ListData*)m_pstData;
	m_nShowMaxCount = m_nHeight/GetListItemHeight() + 2;
	m_UIScroll.SetPageSize(m_nHeight);
// 	int n = GetListItemCnt() - m_nShowMaxCount;
// 	if (n < 1)
// 		n = 1;
	m_UIScroll.SetMaxValue(GetTotalHeight() - GetHeight());
}

void ControlList::RemoveListItem( int index )
{
	// added, jiayi, [2009/11/23]
	if( m_vtpItem.size() - 1 < index )
	{
		index = m_vtpItem.size() - 1;
	}
	std::vector<S_List*>::iterator iter = m_vtpItem.begin()+index;
	S_List* pList = *(iter);
	if (pList->m_nHiberarchy != -1)
	{
		if (!pList->m_bCollapse)
		{
			int nChildCount = pList->m_vtpChildItem.size();
			for (int i = 0; i < nChildCount; ++i)
			{
				RemoveListItem(index + 1);
			}
		}
		S_List* pParent = GetParentList(pList->m_nHiberarchy,index);
		if (pParent)
		{
			pParent->RemoveChild(pList);
		}
	}

	m_vtpItem.erase(m_vtpItem.begin()+index);
	delete pList;
	if (index == m_nCurSelIndex)
	{
		m_nCurSelIndex = 0;
	}
}

void ControlList::InterInsertList( S_List* pList,int nInsertIndex )
{
	m_vtpItem.push_back(pList);
 	for(int i = m_vtpItem.size() - 1; i > nInsertIndex + 1; --i)
	{
		m_vtpItem[i] = m_vtpItem[i - 1];
	}
	m_vtpItem[nInsertIndex + 1] = pList;
}

void ControlList::S_List::ParseText( int& lineHeight ,UiCallbackDataArr* pBase,DWORD	nSyntaxFlag)
{
	m_CurrCallbackDataArr = pBase;
	m_nCallbackDataArrIndex = 0;
	if (UiDataParsing::Instance()->IsStartNewParse())
	{
		ParseTextNew(lineHeight,nSyntaxFlag);
	}

	m_CurrCallbackDataArr = NULL;
}

//------------------------------------------------------------------------------------------------
void ControlList::S_List::NoParse(const WCHAR* wChar)
{
	STextData stTextData;
	stTextData.type = eKeyNormal;		
	stTextData.col = 0;
	stTextData.str = wChar;
	stTextData.pInfo = 0;
	vtTextData.push_back( stTextData );
}

//------------------------------------------------------------------------------------------------
void ControlList::S_List::ParseHiberarchy()
{
	STextData stTextData;
	stTextData.type = eKeyImg;		
	stTextData.col = 0;
	stTextData.pInfo = 0;
	ExpressionManager::ExpressionData* pInfo = ExpressionManager::GetInstance().GetExpressionInfo("#202");
	if (pInfo)
	{
		stTextData.pInfo = (void*)pInfo;
		stTextData.nTextureID = pInfo->GetTextureId();
	}
	vtTextData.push_back(stTextData);
}

void ControlList::S_List::ParseTextNew( int& lineHeight ,DWORD	nSyntaxFlag)
{
	vtTextData.clear();
	const int nWLen = 10240;
	WCHAR wChar[nWLen];
	MultiByteToWideChar( CP_ACP, 0, m_szText, -1, wChar, nWLen-1 );
	wChar[nWLen-1] = 0;
	if (!m_bParseText)
	{
		NoParse(wChar);
		return;
	}

	if (m_nHiberarchy != -1)
	{
		ParseHiberarchy();
	}

	bool bUseData = false;
	UiCallbackDataBase* pData = NULL;
	if (m_CurrCallbackDataArr && (m_CurrCallbackDataArr->size() > m_nCallbackDataArrIndex) )
	{
		pData = (*m_CurrCallbackDataArr)[m_nCallbackDataArrIndex];
	}

	std::wstring strText(wChar);
	UiDataParsing::Instance()->BeginParse(strText.size(), nSyntaxFlag);
	UiParseData& xParsingData = UiDataParsing::Instance()->GetParsingData();
	xParsingData.Init();
	while (UiDataParsing::Instance()->Parsing(strText, pData, bUseData))
	{
		/*if (xParsingData.m_str.length() <= 0)
		{
			temp_.Reset();
			continue;
		}*/

		STextData sTextData;
		sTextData.col = xParsingData.m_col;
		sTextData.type = xParsingData.m_type;
		sTextData.str = xParsingData.m_str;
		sTextData.pInfo = xParsingData.m_pInfo;
		sTextData.rc = xParsingData.m_rc;
		sTextData.nTextureID = xParsingData.m_nTextureID;

		if (bUseData)
		{
			sTextData.m_callBackData = pData;
			++m_nCallbackDataArrIndex;
			bUseData = false;
			pData = NULL;
			if (m_CurrCallbackDataArr && (m_CurrCallbackDataArr->size() > m_nCallbackDataArrIndex) )
			{
				pData = (*m_CurrCallbackDataArr)[m_nCallbackDataArrIndex];
			}
		}

		vtTextData.push_back(sTextData);
		xParsingData.Init();

		//对于Img,需要设置lineHeight
		if (sTextData.IsImgType())
		{
			if (lineHeight <= sTextData.rc.bottom )
			{
				lineHeight = sTextData.rc.bottom;
			}
		}
	}

	UiDataParsing::Instance()->EndParse();
}

void ControlList::S_List::Render( RECT &rect ,int fontIndex,ControlList* pList)
{
	//
		bool bEnd = false;
		for ( size_t i=0; i<vtTextData.size(); i++ )
		{
			STextData* pTextData = &vtTextData[i];
			RECT rcDst = pTextData->rc;
			int nx = rect.left;
			int ny = rect.top;
			rcDst.left += nx;
			rcDst.right += nx;
			rcDst.top += (ny );
			rcDst.bottom += (ny );
			if ( pTextData->IsImgType() )
			{
				if ( pTextData->nTextureID != -1 )
				{
// 					RECT rcImgDst = rect;
// 					float scale = (pTextData->rc.bottom - pTextData->rc.top)/(rect.bottom - rect.left);
// 					rcImgDst.bottom = rcImgDst.top + pTextData->rc.bottom;
// 					rcImgDst.top	+= pTextData->rc.top;
// 					rcImgDst.right = rcImgDst.left + pTextData->rc.right;
// 					rcImgDst.left	+= pTextData->rc.left;

					ExpressionManager::GetInstance().DrawExpression((ExpressionManager::ExpressionData*)pTextData->pInfo,rcDst);
					if (pList->GetFrameFather())
					{
						pList->GetFrameFather()->GetExpressionUpdaterNotNULL()->AddExpress((ExpressionManager::ExpressionData*)pTextData->pInfo);
					}
				}
			}
			else
			{
				DWORD col = pTextData->col;
				if (col == 0)
				{
					col = m_colTextCol;
				}
				if (pTextData->type == eKeyPlayer)
				{
					if ( ( PtInRect( &rcDst, theUiManager.m_ptMoust) == TRUE ))
					{
						col = s_CHAT_HYBER_DOWNLINE_COLOR ;
					}
// 					else // added, jiayi, [2010/2/21]
// 					{
// 						col = s_CHAT_PLAYERNAME_COLOR ;
// 					}
				}

				if(pTextData->type == eKeyNpc)
				{
					if(PtInRect(&rcDst,theUiManager.m_ptMoust) == TRUE)
						col = m_colUrlMouseOn;
				}
				//## 原DT_NOCLIP 

				std::wstring itemRealText = GetListItemRealText(pTextData->str);
				FontSystem::DrawTextW( itemRealText.c_str(), &rcDst,  DT_NOCLIP|DT_VCENTER, col, fontIndex ); 
				
				if(m_nSyntaxUnderLine&pTextData->type/*pTextData->type == eKeyNpc || pTextData->type == eKeyItem || pTextData->type == eKeyPlayer || pTextData->type == eKeyAddress*/)
				{
					RECT rcUrl = pTextData->rc;
					rcUrl.left += nx;
					rcUrl.right += nx - 1;
					rcUrl.top += ny;
					rcUrl.bottom += ny;


					rcUrl.bottom = (rcDst.bottom + rcDst.top + FontSystem::GetFontHeight(fontIndex))/2 + 2;
					int lineBottom = (rcDst.bottom + rcDst.top + pList->GetListItemHeight())/2;
					if ( rcUrl.bottom <= lineBottom)
					{
						rcUrl.top = rcUrl.bottom - 1;
						//UiDrawer::FillRect2D( rcUrl, col );
						int nPic = -1;
						theControlPictureManager.BitBlt( &nPic,
							"./data/ui/common/UnderLine.dds",
							&rcUrl, NULL, col );
					}
				}


				// 画URL下划线
// 				if ( pTextData->type == eKeyItem )
// 				{
// 					RECT rcUrl = pTextData->rc;
// 					rcUrl.left += nx;
// 					rcUrl.right += nx;
// 					rcUrl.top += (ny);
// 					rcUrl.bottom += (ny);
// 					if ( rcUrl.bottom <= rect.bottom )
// 					{
// 						rcUrl.top = rcUrl.bottom - 1;
// 						UiDrawer::FillRect2D( rcUrl, m_colTextCol );
// 					}
// 				}
			}
		}

}

bool ControlList::S_List::CalculatePoint(int lineHeight,HDC dc, int nFontIndex)
{
	int nX = 0;
	int nY = 0;
	if (m_nHiberarchy != -1)
	{
		if (vtTextData.size() > 0)
		{
			STextData& stTextData = vtTextData[0];
			assert(stTextData.IsImgType());
			ExpressionManager::ExpressionData* pInfo = NULL;
			if ((m_nHiberarchy != 0) && (m_vtpChildItem.size() == 0))
			{
				stTextData.nTextureID = -1;
				pInfo = NULL;
// 				pInfo = ExpressionManager::GetInstance().GetExpressionInfo("#202");
			}
			else
			{
				if (m_bCollapse)
				{
					pInfo = ExpressionManager::GetInstance().GetExpressionInfo("#201");
				}
				else
				{
					pInfo = ExpressionManager::GetInstance().GetExpressionInfo("#200");
				}
			}
			if (pInfo)
			{
				stTextData.pInfo = (void*)pInfo;
				stTextData.nTextureID = pInfo->GetTextureId();
				stTextData.rc.right = pInfo->m_nWidth *  ControlObjectGetSCALE(m_pParentList);
				stTextData.rc.left = 0;

                // +- 居中      added by ZhuoMeng.Hu		[12/13/2010]
                int nPicHeight = pInfo->m_nHeight * ControlObjectGetSCALE( m_pParentList );
                if( nPicHeight > 0 && nPicHeight < lineHeight )
                {
                    stTextData.rc.top = ( lineHeight - nPicHeight ) / 2;
                    stTextData.rc.bottom = stTextData.rc.top + nPicHeight;
                }
                else
                {
                    stTextData.rc.bottom = pInfo->m_nHeight * ControlObjectGetSCALE( m_pParentList );
                    stTextData.rc.top = 0;
                }
				nX += m_nHiberarchy * pInfo->m_nWidth * ControlObjectGetSCALE( m_pParentList );
			}
			else
			{
				if (m_bCollapse)
				{
					pInfo = ExpressionManager::GetInstance().GetExpressionInfo("#201");
				}
				else
				{
					pInfo = ExpressionManager::GetInstance().GetExpressionInfo("#200");
				}
				if(pInfo)
				{
					int nHiberarchy = m_nHiberarchy - 1;
					if(nHiberarchy < 0)
						nHiberarchy = 0;

					nX += nHiberarchy * pInfo->m_nWidth *  ControlObjectGetSCALE(m_pParentList);
				}
				
			}
		}
	}
	int nRowH = lineHeight;
	for ( size_t n=0; n<vtTextData.size(); n++ )
	{
		STextData *pTextData = &vtTextData[n];
		//assert( pText->vtTextData.size() == 1 );
		// 图片
		if ( pTextData->IsImgType() )
		{
			if ( pTextData->pInfo != NULL )
			{

//				float scale = (pTextData->rc.bottom - pTextData->rc.top)/(float)lineHeight;

// 				int nNeedWidth = (pTextData->rc.right - pTextData->rc.left)/scale;
				ExpressionManager::ExpressionData* pInfo = (ExpressionManager::ExpressionData*)pTextData->pInfo;
                {
                    int nNeedWidth = pInfo->m_nWidth * ControlObjectGetSCALE(m_pParentList);

                    // +- 居中       added by ZhuoMeng.Hu		[12/13/2010]
                    int nPicHeight = pInfo->m_nHeight * ControlObjectGetSCALE( m_pParentList );
                    if( nPicHeight > 0 && nPicHeight < lineHeight )
                    {
                        pTextData->rc.top = ( lineHeight - nPicHeight ) / 2;
                        pTextData->rc.bottom = pTextData->rc.top + nPicHeight;
                    }
                    else
                    {
                        pTextData->rc.top = 0;
                        pTextData->rc.bottom = pInfo->m_nHeight * ControlObjectGetSCALE( m_pParentList );
                    }
                    pTextData->rc.left = nX;
                    pTextData->rc.right = pTextData->rc.left + nNeedWidth;
                    nX += nNeedWidth/* * (m_nHiberarchy + 1)*/;
                }
				//
			}
		}
		else
		{
			std::wstring itemRealText = GetListItemRealText(pTextData->str);
			assert(itemRealText.length() >= 0);

			int nNeedWidth = ControlHelper::Get().GetTextWidth(itemRealText.c_str(), dc, 0, itemRealText.length(), m_pParentList, nFontIndex);
			pTextData->rc.top = 0;
			pTextData->rc.bottom = lineHeight;
			pTextData->rc.left = nX;
			pTextData->rc.right = pTextData->rc.left + nNeedWidth;
			nX += nNeedWidth;
		}
	}
	return true;
}

ControlList::S_List& ControlList::S_List::operator=( const ControlList::S_List& pRight)
{
	SetData(pRight.m_szText,pRight.m_nID,pRight.m_pData,pRight.m_colTextCol,(char*)pRight.m_szNote,(char*)pRight._hyberItemInfoRaw,ITEM_HYBER_MAX_CNT, pRight.m_nItemSize );
	_bOnline = pRight._bOnline;
	if( pRight.m_pTipInfo )
	{
		if( !m_pTipInfo )
		{
			m_pTipInfo = MeNew S_TextTipInfo();
		}
		//memcpy( m_pTipInfo, pRight.m_pTipInfo, sizeof( S_TextTipInfo ) );
		*m_pTipInfo = *pRight.m_pTipInfo;
	}	
	//m_pTipInfo		= pRight.TipInfo;
	UseSelColor = pRight.UseSelColor;
	m_bUseHyberColor = pRight.m_bUseHyberColor;
	m_colHyberOther = pRight.m_colHyberOther;
	m_nHiberarchy  = pRight.m_nHiberarchy;
	m_bCollapse = pRight.m_bCollapse;
	m_bParseText = pRight.m_bParseText;
	m_pParentList = pRight.m_pParentList;
    m_eAlignMode = pRight.m_eAlignMode;
    m_nMargin = pRight.m_nMargin;
	m_nSyntaxUnderLine = pRight.m_nSyntaxUnderLine;
	vtTextData.clear();
	for (int i = 0; i < pRight.vtTextData.size();++i)
	{
		assert(pRight.vtTextData[i].m_callBackData == NULL);
		vtTextData.push_back(pRight.vtTextData[i]);
	}
	return *this;
// 	for ( std::vector<STextData>::iterator iter =  pRight.vtTextData.begin(); iter != pRight.vtTextData.end();++iter)
// 	{
// 		vtTextData.push_back((*iter));
// 	}
}

bool ControlList::S_List::IsExistImg()
{
	for (int i = 0; i < vtTextData.size();++i)
	{
		STextData& data = vtTextData[i];
		if (data.IsImgType())
		{
			return true;
		}
	}
	return false;
}

void ControlList::S_List::clear()
{
	if (m_bCollapse)
	{
		for (int i = 0; i < m_vtpChildItem.size(); ++i)
		{
			delete m_vtpChildItem[i];
		}
		m_bCollapse		= false;
	}
	for (int i = 0; i < vtTextData.size(); ++i)
	{
		if (vtTextData[i].m_callBackData)
		{
			vtTextData[i].m_callBackData->Destory();
			vtTextData[i].m_callBackData = NULL;
		}
	}
	m_vtpChildItem.clear();
	m_nID = -1;
	memset( m_szText, 0, sizeof(m_szText) );
	memset( m_szNote, 0, sizeof(m_szNote) );
	m_pData = NULL;
	m_colTextCol = 0xffffffff;
	if( m_pTipInfo )
		m_pTipInfo->Clear();
	_bOnline = false;
	UseSelColor = FALSE;
	m_bUseHyberColor = false;
	m_nHiberarchy = -1;
	m_bParseText	= true;
	m_nItemSize = 0;
	m_pParentList = NULL;
	m_CurrCallbackDataArr = NULL;
	m_nCallbackDataArrIndex = 0;
	SAFE_DELETE( m_pTipInfo );
}

void ControlList::S_List::RemoveChild( S_List* pList )
{
	for (std::vector<S_List*>::iterator iter = m_vtpChildItem.begin(); iter != m_vtpChildItem.end(); ++iter)
	{
		if ((*iter) == pList)
		{
			if (m_bCollapse)
			{
				delete pList;
			}
			m_vtpChildItem.erase(iter);
			return;
		}
	}
}

bool ControlList::CheckDrawMode(S_List* pList)
{
	if ( m_dwDrawFlags&DT_CENTER )
	{
		int nWidth = 0;
// 		for (int nLine = 0; nLine < m_vtpItem.size(); ++nLine)
		{
// 			S_List* pList = m_vtpItem[nLine];
			for ( size_t i=0; i<pList->vtTextData.size(); i++ )
			{
				S_List::STextData *pTextData = &pList->vtTextData[i];
				nWidth += (pTextData->rc.right - pTextData->rc.left);
			}
		}
		if( nWidth != 0 )
		{
			int nx = (GetWidth()-nWidth)/2;
			MoveTextDataPos( pList, nx, 0 );
		}
	}
	if ( m_dwDrawFlags&DT_RIGHT )
	{
		int nWidth = 0;
// 		for (int nLine = 0; nLine < m_vtpItem.size(); ++nLine)
		{
// 			S_List* pList = m_vtpItem[nLine];
			for ( size_t i=0; i<pList->vtTextData.size(); i++ )
			{
				S_List::STextData *pTextData = &pList->vtTextData[i];
				nWidth += (pTextData->rc.right - pTextData->rc.left);
			}
		}
		if( nWidth != 0 )
		{
			int nx = (GetWidth()-nWidth - 3);
			MoveTextDataPos( pList, nx, 0 );
		}
	}
	return true;

}

bool ControlList::MoveTextDataPos(S_List* pList, int nOffsetX, int nOffsetY )
{
// 	S_List* pList = m_vtpItem[nLine];
	for (int i = 0; i < pList->vtTextData.size();++i)
	{
		S_List::STextData* pTextData = &pList->vtTextData[i];
		{
			pTextData->rc.left += nOffsetX;
			pTextData->rc.right += nOffsetX;
			pTextData->rc.top += nOffsetY;
			pTextData->rc.bottom += nOffsetY;
		}
	}
	return true;
}

void ControlList::CalCurSelByMouse( const int nX , const int nY )
{
	RECT rc;
	GetRealRect( &rc );
	m_nOldCurSel = m_nCurSelIndex;
	m_nCurSelIndex = (nY - rc.top + m_nShowStartHeight)/GetListItemHeight();
	if ( m_nCurSelIndex > (int)m_vtpItem.size() - 1 )
	{
		m_nCurSelIndex = (int)m_vtpItem.size() - 1;
	}
	OnlyLeafCanBeSelected();
}

void ControlList::OnlyLeafCanBeSelected()
{
	if (!m_bOnlyLeafCanBeSelected)
	{
		return;
	}
	S_List* pSelList = GetCurSelItem();
	if(pSelList)
	{
		if (pSelList->m_nHiberarchy != -1)
		{
			if (pSelList->m_vtpChildItem.size() > 0)
			{
				m_nCurSelIndex = -1;
			}
		}
	}
}

ControlList::S_List* ControlList::PtOnCollapse( const int nX, const int nY ,int * pnIndex)
{
	RECT rc;
	GetRealRect( &rc );
	if ( nX >= rc.left && nX <= rc.right &&
		nY >= rc.top && nY <= rc.bottom )
	{
		int nCollapse = (nY - rc.top + m_nShowStartHeight)/GetListItemHeight();
		S_List* pCollapseList = NULL;
		if ( nCollapse >= 0 && nCollapse < (int)m_vtpItem.size() )
		{
			pCollapseList = m_vtpItem[nCollapse];
		}
		if(pCollapseList)
		{
			if (pCollapseList->m_nHiberarchy != -1)
			{
				//对整行添加判断
//				bool bHitted = false;
// 				std::vector<S_List::STextData>& textData = pCollapseList->vtTextData;
// 				for (int i = 0; i < textData.size();++i)
// 				{
// 					S_List::STextData& data = textData[i];
// 					RECT tmp={rc.left + data.rc.left,rc.top + data.rc.top + (nCollapse*GetListItemHeight()-m_nShowStartHeight),rc.left + data.rc.right,rc.top + data.rc.bottom +(nCollapse*GetListItemHeight()-m_nShowStartHeight)};
// 					if ( nX < tmp.left || nX > tmp.right || nY < tmp.top || nY > tmp.bottom )
// 						continue;
// 					else
// 					{
// 						bHitted = true;
// 						break;
// 					}
// 				}
//				if (bHitted && pCollapseList->m_vtpChildItem.size() > 0)
				if ((pCollapseList->m_nHiberarchy == 0 || pCollapseList->m_vtpChildItem.size() > 0))
				{
					if (pnIndex)
					{
						*pnIndex = nCollapse;
					}
					return pCollapseList;
				}
			}
		}
	}
	return NULL;
}

void ControlList::ScrollToTheBegin()
{
	SetShowStartHeight(0);
}

void ControlList::ScrollToTheLast()
{
	if ( GetTotalHeight() > m_nHeight )
	{
		SetShowStartHeight(GetTotalHeight() - m_nHeight);
	}
}

void ControlList::Run()
{
	if(m_eHyberType != eKeyNormal && m_bEnablePathFinding && PtInObject(theUiManager.m_ptMoust.x,theUiManager.m_ptMoust.y,false))
	{
		theMouseManager.SetCanSetCursor(true);
		{
			switch(m_eHyberType)
			{
			case eKeyPlayer:
				{
					theMouseManager.SetUICursor(MouseManager::Type_ChatPlayer);
// 					if( GetFrameFather() )
// 						GetFrameFather()->SetRedraw();
				}
				break;
			case eKeyItem:
				{
					theMouseManager.SetUICursor(MouseManager::Type_ChatHyper);
// 					if( GetFrameFather() )
// 						GetFrameFather()->SetRedraw();
				}
				break;
			case eKeyAddress:
			case eKeyNpc:
				{
					theMouseManager.SetUICursor(MouseManager::Type_PathFinding);
// 					if( GetFrameFather() )
// 						GetFrameFather()->SetRedraw();
				}
				break;
			}
		}
	}

}
void ControlList::SetSelectBar( const RECT& rcBar, const std::string& strFile )
{
	ms_rcSelectBar = rcBar;
	ms_strSelectBar = strFile;
}
void ControlList::SetMouseHoverBar( const RECT& rcBar, const std::string& strFile )
{
	ms_rcMouseHoverBar = rcBar;
	ms_strMouseHoverBar = strFile;
}

bool ControlList::InListContextRect(int nCol,int nX,int nY)
{
	if(nCol < 0 || nCol >= m_vtpItem.size())
		return false;

	S_List* pList = m_vtpItem[nCol];
	if(!pList)
		return false;

	RECT rc;
	GetRealRect(&rc);
	std::vector<S_List::STextData>& vtTextData = pList->vtTextData;
	for (int i = 0;i < vtTextData.size();++i)
	{
		S_List::STextData& data = vtTextData[i];
		RECT itemRect = {rc.left + data.rc.left,rc.top + data.rc.top + (nCol * GetListItemHeight() - m_nShowStartHeight),
			rc.left + data.rc.right,rc.top + data.rc.bottom + (nCol * GetListItemHeight() - m_nShowStartHeight)};

		if(nX < itemRect.left || nX > itemRect.right || nY < itemRect.top || nY > itemRect.bottom)
			continue;
		else
			return true;
	}

	return false;
}

void ControlList::SetIgnoreLBtnDown( bool bIgnore )
{
    m_bIgnoreLBtnDown = bIgnore;
}

bool ControlList::IsIgnoreLBtnDown()
{
    return m_bIgnoreLBtnDown;
}

void ControlList::SetStartIndex(int nStartIndex)
{
	m_nShowStartHeight = nStartIndex*m_nDefaultItemHeight;
	m_UIScroll.SetValue( nStartIndex*m_UIScroll.GetStepValue() );
}