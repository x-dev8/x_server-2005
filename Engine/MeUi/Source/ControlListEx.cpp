#include "MeUi/ControlListEx.h"
#include "MeUi/UiPicture.h"
#include "FuncPerformanceLog.h"

ControlListEx::ControlListEx(void)
{
	m_bHaveSelFrame = true;
	m_bOnlyIconActive = true;
	m_pFunDrawInfo = NULL;

	_luaTableName.clear();
	_funDrawInfo.clear();
}

ControlListEx::~ControlListEx(void)
{
}


void ControlListEx::Render()
{
	if ( IsNeedRender() )
	{
		ControlObject::Render();

		RECT rcReal;
		GetRealRect( &rcReal );
		S_ListExData *pListExData = (S_ListExData*)m_pstData;
		RECT rcFrame;
		DWORD dwCurTime = HQ_TimeGetTime();
		int nX, nY;
		//
// 		RECT rcView;
// 		rcView.left = 0;
// 		rcView.top = m_nStartIndex;
// 		rcView.right = m_nWidthShowMaxCount;
// 		rcView.bottom = rcView.top + m_nHeightShowMaxCount;
		//
		int nIconWidth,nIconHeight;
		nIconWidth = GetItemWidth();
		nIconHeight = GetItemHeight();
		S_ListImg* pListItem = NULL;
		//
		const int nStartIndex = (m_nShowStartHeight/ nIconHeight)*m_nWidthShowMaxCount;//rcView.top*m_nWidthShowMaxCount;
		const int nEndIndex = (nStartIndex + m_nHeightShowMaxCount + 1)*m_nWidthShowMaxCount;
// 		const int nStartIndex = rcView.top*m_nWidthShowMaxCount;
// 		const int nEndIndex = rcView.bottom*m_nWidthShowMaxCount;
		for ( int n=nStartIndex; n<nEndIndex; n++ )
		{
			pListItem = GetItemByIndex( n );
			if( !pListItem )
				continue;
			if ( pListItem->IsNull() )
				continue;

			nX = n%m_nWidthShowMaxCount;
			nY = n/m_nWidthShowMaxCount;

			rcFrame.left = rcReal.left + nX*nIconWidth;
			rcFrame.top = rcReal.top + (nY*nIconHeight-m_nShowStartHeight);
			rcFrame.right = rcFrame.left + pListExData->m_nItemHeight-1;
			rcFrame.bottom = rcFrame.top + pListExData->m_nItemHeight-1;
#ifdef _DEBUG
			UiDrawer::DrawRect2D( rcFrame, 0x7f7f7f7f );
#endif
			if( pListItem->m_pkIconInfo )
			{
				pListItem->m_pkIconInfo->DisplayIcon( &rcFrame, 0xffffffff,
					GetFontIndex(), GetFontSize(),
					RGB(0xff,0xff,0xff),
					pListItem->m_eEnable ,GetFrameFather());
			}

			//if ( pListItem->m_bEnable )
			//{
			//	pListItem->m_stIcon.DisplayIcon( &rcFrame, 0xffffffff,
			//									m_nFontIndex, GetFontSize(),
			//									RGB(0xff,0xff,0xff) );
			//}
			//else
			//{
			//	pListItem->m_stIcon.DisplayIcon( &rcFrame, 0xc8505050,
			//									m_nFontIndex, GetFontSize(),
			//									RGB(0xff,0xff,0xff) );
			//}
			if ( pListItem->m_dwPeriod != 0 )
			{
				int nDegree = 0;
				nDegree = (dwCurTime - pListItem->m_dwStartTime)*360/pListItem->m_dwPeriod;
				if ( nDegree < 360 )
				{
					UiDrawer::DrawProgressRect( rcFrame.left+pListExData->m_nItemHeight/2,
						rcFrame.top+pListExData->m_nItemHeight/2,
						pListExData->m_nItemHeight, nDegree );
				}
				else
				{
					pListItem->m_dwPeriod = 0;
				}
			}
			rcFrame.left += pListExData->m_nItemHeight;
			rcFrame.top = rcFrame.top;
			//			rcFrame.top = rcReal.top + (h-m_nStartIndex)*nIconHeight;
			rcFrame.right = rcFrame.left + pListExData->m_nItemWidth - pListExData->m_nItemHeight;
			rcFrame.bottom = rcFrame.top + pListExData->m_nItemHeight;
			COLORREF color;
			if( pListItem->m_bUseCol )
			{
				color = pListItem->m_col;
			}
			else
			{
				color = pListExData->m_colFont;
			}

			if( (NULL != state.Get() && _luaTableName.length() > 0 && _funDrawInfo.length() > 0) || m_pFunDrawInfo )
			{
				if( NULL != state.Get() && _luaTableName.length() > 0 && _funDrawInfo.length() > 0 )
				{
					try
					{
						LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
						if( table1Obj.IsTable() )
						{
							LuaFunction<void> function_( table1Obj[_funDrawInfo.c_str()] );
							function_( &rcFrame, pListItem );
						}
					}
					catch (LuaPlus::LuaException &e)
					{
						char szErr[256] = {0};
						_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funDrawInfo.c_str(), e.GetErrorMessage());
						print_error( szErr );
					}
				}
				else
				{
					if ( m_pFunDrawInfo )
					{
						m_pFunDrawInfo( &rcFrame, pListItem );
					}
				}
			}
			else
			{
				if( pListItem->m_pkIconInfo )
				{
					pListItem->m_pkIconInfo->DisplayInfo( &rcFrame, m_bIsShop, GetFontIndex(),
						pListExData->m_nFontSize, color, false, false );
				}				
			}
		}

		if ( m_bHaveSelFrame )
		{
			// 选择框
			POINT ptSel = m_ptCurSel;
			RECT rcSel;
// 			ptSel.y -= m_nStartIndex;
			if ( ptSel.y*nIconHeight >= m_nShowStartHeight && ptSel.y < m_nHeightShowMaxCount )
			{
				rcSel.left = rcReal.left + ptSel.x*nIconWidth;
				rcSel.top = rcReal.top + ptSel.y*nIconHeight - m_nShowStartHeight;
				rcSel.right = rcSel.left + pListExData->m_nItemWidth;
				rcSel.bottom = rcSel.top + pListExData->m_nItemHeight;
				if ( m_bOnlyIconActive == true )
				{
					rcSel.right = rcSel.left + pListExData->m_nItemHeight;
				}
				UiDrawer::DrawRect2D( rcSel, m_colSel );
				rcSel.left--;
				rcSel.right++;
				rcSel.top--;
				rcSel.bottom++;
				UiDrawer::DrawRect2D( rcSel, m_colSel );
			}
			// 选择框
			ptSel = m_ptMouseOnSel;
// 			ptSel.y -= m_nStartIndex;
			if ( ptSel.y*nIconHeight >= 0 && ptSel.y < m_nHeightShowMaxCount )
			{
				rcSel.left = rcReal.left + ptSel.x*nIconWidth;
				rcSel.top = rcReal.top + ptSel.y*nIconHeight - m_nShowStartHeight;
				rcSel.right = rcSel.left + pListExData->m_nItemWidth;
				rcSel.bottom = rcSel.top + pListExData->m_nItemHeight;
				if ( m_bOnlyIconActive == true )
				{
					rcSel.right = rcSel.left + pListExData->m_nItemHeight;
				}
				UiDrawer::DrawRect2D( rcSel, m_colMouseOn );
			}
		}

		m_UIScroll.Render();
	}
}

void ControlListEx::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	ControlObject::InitUIData( pFather, pData );

	S_ListExData *pListExData = (S_ListExData*)pData;
	m_nItemWidth = pListExData->m_nItemWidth;
	m_nItemHeight = pListExData->m_nItemHeight;
	m_nOffsetWidth = pListExData->m_nOffsetWidth;
	m_nOffsetHeight = pListExData->m_nOffsetHeight;

	pListExData->m_nItemWidth = pListExData->m_nItemWidth*ControlObjectGetSCALE(this);
	pListExData->m_nItemHeight = pListExData->m_nItemHeight*ControlObjectGetSCALE(this);
	pListExData->m_nOffsetWidth = pListExData->m_nOffsetWidth*ControlObjectGetSCALE(this);
	pListExData->m_nOffsetHeight = pListExData->m_nOffsetHeight*ControlObjectGetSCALE(this);

	m_nWidthShowMaxCount = (m_nWidth+pListExData->m_nOffsetWidth)/
		(pListExData->m_nItemWidth+pListExData->m_nOffsetWidth);
	m_nHeightShowMaxCount = (m_nHeight+pListExData->m_nOffsetHeight)/
		(pListExData->m_nItemHeight+pListExData->m_nOffsetHeight);
	m_nMaxHeightCount = pListExData->m_nMaxHeightCount;
	//m_nEnbaleRowCnt = m_nMaxHeightCount;

	//assert( m_nWidthShowMaxCount < LISTIMG_ITEM_WIDTH_MAX );
	//assert( m_nHeightShowMaxCount < LISTIMG_ITEM_HEIGHT_MAX );
	//assert( m_nMaxHeightCount < LISTIMG_ITEM_HEIGHT_MAX );
	InitItemDate();

	COLORREF Color = pListExData->m_colSelBar;
	m_colSel = D3DCOLOR_ARGB(255,GetRValue(Color),GetGValue(Color),GetBValue(Color));
	m_colMouseOn = D3DCOLOR_ARGB(128,GetRValue(Color),GetGValue(Color),GetBValue(Color));

	m_UIScroll.InitUIData( this, &pListExData->m_stScrollBar );

#ifdef _DEBUG
	m_UIScroll.m_debug_bHasWarning = false;
#endif
}

POINT ControlListEx::getCurItemPos()
{
	RECT rc;
	GetRealRect( &rc );

	S_ListExData *pListExData = (S_ListExData*)m_pstData;

	POINT pt;
	int nWidth = pListExData->m_nItemWidth+pListExData->m_nOffsetWidth;
	int nHeight = pListExData->m_nItemHeight+pListExData->m_nOffsetHeight;

	pt.x = rc.left + nWidth * m_ptCurSel.x;
	pt.y = rc.top + nHeight * m_ptCurSel.y;

	int maxCnt = -1;
	S_ListImg *pListImg = NULL;
	for( int n = 0; n<m_vtItem.size(); ++n)
	{
		pListImg = &(m_vtItem[n]);
		if(pListImg->IsNull())
		{
			maxCnt = n - 1;
			break;
		}
	}

	if( maxCnt == -1 )
	{
		maxCnt = m_nWidthShowMaxCount * m_nMaxHeightCount;
	}

	if( m_ptCurSel.y * m_nWidthShowMaxCount + m_ptCurSel.x > maxCnt)
	{
		pt.x = rc.left + nWidth * (maxCnt % m_nWidthShowMaxCount);
		pt.y = rc.top + nHeight * (maxCnt / m_nWidthShowMaxCount);
	}
	//int maxCnt = GetNullItem(false);
	//if( maxCnt == -1 )
	//	maxCnt = m_nWidthShowMaxCount*m_nMaxHeightCount;

	//int maxY = maxCnt / m_nWidthShowMaxCount;
	//if( maxCnt % m_nWidthShowMaxCount == 1)
	//{
	//	if( m_ptCurSel.y == maxY )
	//	{
	//		if( m_ptCurSel.x > 0 )
	//		{
	//			pt.x = rc.left;
	//		}
	//	}
	//}

	//if( maxY > 0 )
	//{
	//	int nMaxHeight = rc.top + nHeight * (maxY-1);
	//	pt.y = pt.y > nMaxHeight ? nMaxHeight : pt.y;
	//}

	return pt;
}
// 取得指定坐标的格子坐标
bool ControlListEx::GetTilePt( const int nX, const int nY, OUT POINT *ptTile )
{
	assert( ptTile );
	if ( PtInObject(nX,nY,false) == true )
	{
		RECT rc;
		GetRealRect( &rc );
		S_ListExData *pListExData = (S_ListExData*)m_pstData;
		int nOfW = pListExData->m_nOffsetWidth;
		int nOfH = pListExData->m_nOffsetHeight;
		int nH = pListExData->m_nItemHeight;
		int nW = pListExData->m_nItemWidth;
		if ( m_bOnlyIconActive == true )
		{
			if( (nX-rc.left)%(nW+nOfW) <= nH+nOfW &&
				(nY-rc.top)%(nH+nOfH) <= nH+nOfH )
			{
				ptTile->x = (nX-rc.left)/(nW+nOfW);
				ptTile->y = (nY-rc.top+m_nShowStartHeight)/(nH+nOfH);

				ptTile->y = ptTile->y > m_nHeightShowMaxCount ? m_nHeightShowMaxCount : ptTile->y;

				return true;
			}
		}
		else
		{
			if( (nX-rc.left)%(nW+nOfW) <= nW+nOfW &&
				(nY-rc.top)%(nH+nOfH) <= nH+nOfH )
			{
				ptTile->x = (nX-rc.left)/(nW+nOfW);
				ptTile->y = (nY-rc.top+m_nShowStartHeight)/(nH+nOfH);

				ptTile->y = ptTile->y > m_nHeightShowMaxCount ? m_nHeightShowMaxCount : ptTile->y;

				return true;
			}
		}

	}
	return false;
}

void ControlListEx::SetDrawInfoFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funDrawInfo = funName;
	unguard;
}

void ControlListEx::ResetDevice()
{
	ControlIconDrag::ResetDevice();

	S_ListExData *pListExData = (S_ListExData*)m_pstData;
	pListExData->m_nItemWidth = m_nItemWidth * ControlObjectGetSCALE(this);
	pListExData->m_nItemHeight = m_nItemHeight * ControlObjectGetSCALE(this);
	pListExData->m_nOffsetWidth = m_nOffsetWidth * ControlObjectGetSCALE(this);
	pListExData->m_nOffsetHeight = m_nOffsetHeight * ControlObjectGetSCALE(this);

	m_nWidthShowMaxCount = (m_nWidth+pListExData->m_nOffsetWidth)/
		(pListExData->m_nItemWidth+pListExData->m_nOffsetWidth);
	m_nHeightShowMaxCount = (m_nHeight+pListExData->m_nOffsetHeight)/
		(pListExData->m_nItemHeight+pListExData->m_nOffsetHeight);
	m_nMaxHeightCount = pListExData->m_nMaxHeightCount;
}