#include "MeUi/ControlIconDrag.h"
#include "MeUi/ControlIconDragManager.h"
#include "MeUi/UiManager.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Include.h"
#include "MeUi/Animation/SmartAnimation.h"
#include "MeUi/Animation/XmlAnimation.h"

extern short GetKeyboardInput( int iKey );

S_IconInfoBase::funcCreateIconInfo S_IconInfoBase::ms_pFuncCreateIconInfo = 0;
ControlIconDrag::funcGlobalOnMouseMove ControlIconDrag::ms_pFuncBlobalOnMouseMove = 0;

ControlIconDrag::ControlIconDrag(void)
{
	m_nWidthShowMaxCount = 0;
	m_nHeightShowMaxCount = 0;
	m_nShowStartHeight = 0;
	m_nMaxHeightCount = 0;
	memset( &m_ptCurSel, 0, sizeof(m_ptCurSel) );
	memset( &m_ptMouseOnSel, -1, sizeof(m_ptMouseOnSel) );
	m_colSel = 0;
	m_colMouseOn = 0;
	m_bIsShop = false;
	m_bShowAllInfo = true;
	m_bDisableCanbePick = false;

	m_pFunDragOn = NULL;
	m_pFunDragDisableOn = NULL;
	m_pFunDragDisableOut = NULL;
	//	m_pFunDragOff = NULL;
	m_pFunLDBClick = NULL;
	m_pFunRButtonUp = NULL;
	m_pFunButtonClick = NULL;
	m_pFunShiftLBClick = NULL;	
	m_pFunOnMouseMove = NULL;
    m_pFunSparkOnMouseMove = NULL;

	m_nEnbaleRowCnt = -1;
	m_nEnbaleCnt = -1;
	m_bEnableCompare = true;
	//
	m_strSound = UiManager::m_strIconDragSound;

	m_bNotMsgClick = false;
	m_bShiftDown = false;
	m_bKeyDown = false;
	m_bLClick = false;
	m_bEnableDragIn = true;
	m_bEnableDragOut = true;

	m_nDelayTime = 0 ;
	m_nPressItemIndex = -1;
	m_nSelectItemIndex = -1;
	m_bShowPressEffect = true;
	m_bShowCursorOnFrameOnNULLItem = true;
}

ControlIconDrag::~ControlIconDrag(void)
{
	theIconDragManager.ClearInvalidPointer( this );
}

void ControlIconDrag::Run()
{
}

bool ControlIconDrag::RemoveItemById( const int nItemID, const int nCount )
{
	for( int n=0; n<m_vtItem.size(); n++ )
	{
		if( !m_vtItem[n].m_pkIconInfo )
			continue;

		if ( m_vtItem[n].m_pkIconInfo->Id() == nItemID )
		{
			if ( nCount <= 0 )
			{
				m_vtItem[n].Clear();
			}
			else
			{
				m_vtItem[n].ChangeCount( false, nCount );
			}
			if (GetFrameFather())
			{
				GetFrameFather()->SetRedraw();
			}
			return true;
		}
	}
	return false;
}
bool ControlIconDrag::RemoveItemByIndex( int nIndex )
{
	if ( nIndex < 0 || nIndex >= m_vtItem.size() )
		return false;

	m_vtItem[nIndex].Clear();
    if( GetFrameFather() )
    {
        GetFrameFather()->SetRedraw();
    }
	return true;
}


bool ControlIconDrag::SetItem( IN S_ListImg *pItem, const int nIndex, bool reverse )
{
	int n = nIndex;
	if ( nIndex == -1 )
	{
		if( reverse )
		{
			n = GetNullItem(true);
		}
		else
		{
			n = GetNullItem();
		}
	}

	if ( n >= m_vtItem.size() || n < 0 )
		return false;

	m_vtItem[n] = *pItem;

	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}

	return true;
}
void ControlIconDrag::SetSpareTime( int nIndex, DWORD dwTime, int nStartTime, bool bShowBottomTime )
{
	if( nIndex >= m_vtItem.size() )
		return;

	if( m_vtItem[nIndex].m_pkIconInfo )
    {
        m_vtItem[nIndex].m_pkIconInfo->EnableStatusBottomTime( bShowBottomTime );
		m_vtItem[nIndex].m_pkIconInfo->SetSpareTime( dwTime, nStartTime );
    }
}

// 取得项
ControlIconDrag::S_ListImg* ControlIconDrag::GetItem( const unsigned int nX, const unsigned int nY )
{
	int nIndex = nY*m_nWidthShowMaxCount + nX;
	return GetItemByIndex( nIndex );
}

ControlIconDrag::S_ListImg* ControlIconDrag::GetCompareItem()
{
	return &m_TempCompareItem;
}

ControlIconDrag::S_ListImg* ControlIconDrag::GetSecondCompareItem()
{
	return &m_SecondTempCompareItem;
}

ControlIconDrag::S_ListImg* ControlIconDrag::GetCurSelItem()
{
	return GetItem( m_ptCurSel.x, m_ptCurSel.y );
}

//int ControlIconDrag::GetMaxCount()
//{
//	return m_nMaxHeightCount*m_nWidthShowMaxCount;
//}
ControlIconDrag::S_ListImg* ControlIconDrag::GetLastIndex( int index )
{
	if ( index >= m_vtItem.size() )
		return NULL;

	int maxCnt = 0;
	S_ListImg *pCurItem = NULL;
	for( int n=0; n<m_vtItem.size(); ++n)
	{
		pCurItem = &(m_vtItem[n]);
		if(pCurItem->IsNull())
		{
			maxCnt = n - 1;
			break;
		}
	}

	if( index >= maxCnt )
		return &m_vtItem[maxCnt];

	return &m_vtItem[index];
}
ControlIconDrag::S_ListImg* ControlIconDrag::GetItemByIndex( const unsigned int nIndex )
{
	if ( nIndex >= m_vtItem.size() )
		return NULL;

	//int maxCnt = 0;
	//S_ListImg *pCurItem = NULL;
	//for( int n=0; n<m_vtItem.size(); ++n)
	//{
	//	pCurItem = &(m_vtItem[n]);
	//	if(pCurItem->IsNull())
	//	{
	//		maxCnt = n - 1;
	//		break;
	//	}
	//}

	//if( nIndex >= maxCnt )
	//	return &m_vtItem[maxCnt];

	if (m_vtItem[nIndex].m_eEnable == eIcon_Lock)
		return NULL;

	return &m_vtItem[nIndex];
}

ControlIconDrag::S_ListImg* ControlIconDrag::GetItemById( const int nId )
{
	for ( int n=0; n<m_vtItem.size(); n++ )
	{
		if( !m_vtItem[n].m_pkIconInfo )
			continue;

		if ( m_vtItem[n].m_pkIconInfo->Id() == nId )
		{
			return &(m_vtItem[n]);
		}
	}
	return NULL;
}

bool ControlIconDrag::OnLDBClick( const int nX, const int nY, OUT IN S_ListImg* pItem,
								 IN ControlObject* pSender )
{
	if ( !pItem || pItem->IsNull() )
	{
		return false;
	}
	if ( m_pFunLDBClick )
	{
		return m_pFunLDBClick( this, pItem );
	}
#ifdef _DEBUG
	else if ( m_debug_bHasWarning )
	{
		char szDebug[128];
		char szFatherID[128] = "";
		if ( m_pFather )
		{
			strcpy( szFatherID, m_pFather->GetControlID() );
		}
		sprintf(szDebug,"[%s]::[%s] ControlIconDrag::OnLDBClick(char* szData) not defend!!\r\n", szFatherID, GetControlID() );
		//OutputDebugString(szDebug);
	}
#endif
	return false;
}

bool ControlIconDrag::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
	bool ret = false;
	if ( IsVisable() )
	{
// 		RECT rc;
// 		GetRealRect( &rc );
		POINT ptNewMouseOnSel ;
		ptNewMouseOnSel.x = -1;
		ptNewMouseOnSel.y = -1;

		if ( m_nMaxHeightCount > m_nHeightShowMaxCount && m_UIScroll.IsDrag() )
		{
			Refeash();
		}
		//else if ( PtInObject(nX,nY) == true )
		else// if ( nX >= rc.left && nX <= rc.right && nY >= rc.top && nY <= rc.bottom )
		{
			if ( GetTilePt( nX, nY, &ptNewMouseOnSel ) == true )
			{
				// added, jiayi, [2009/10/20]
				// 这里tip的位置取当前item的左边界
				// 这样就可以固定tip位置
				RECT rcItem;
				GetItemRect( nX, nY, rcItem );	
				// 偏移到中间
				rcItem.left += GetItemWidth() / 2;
				rcItem.top += GetItemHeight() / 2;
				S_ListImg *pItem = GetItem( ptNewMouseOnSel.x, ptNewMouseOnSel.y );
				if( ms_pFuncBlobalOnMouseMove )
					ret = ms_pFuncBlobalOnMouseMove( pItem, m_bEnableCompare, rcItem, this );
				if( m_pFunOnMouseMove )
					m_pFunOnMouseMove( nFlags, nX, nY );
				if (ptNewMouseOnSel.x != m_ptMouseOnSel.x || ptNewMouseOnSel.y != m_ptMouseOnSel.y )
				{
					m_ptMouseOnSel.x = ptNewMouseOnSel.x;
					m_ptMouseOnSel.y = ptNewMouseOnSel.y;
					if (GetFrameFather())
					{
						GetFrameFather()->SetRedraw();
					}
				}
				else
				{
					return false;
				}

// 				bool bHaveCompare = false;

                // 闪光效果在鼠标悬浮后消失     added by zhuomeng.hu		[11/11/2010]
                if( pItem && pItem->m_bSpark )
                {
                    if( m_pFunSparkOnMouseMove )
                    {
                        m_pFunSparkOnMouseMove( pItem, this );
                    }
                }

// 				S_ListImg* pCompareItem = 0;
				// added, jiayi, [2009/7/1]

				if( pItem && m_bLClick && !IsEnableDragOut() )
				{
					OnDragDisableOut( this,pItem );
				}

				m_bLClick = false;
// 				if( pItem )
// 				{
// 					if( m_bEnableCompare && pItem->m_pkIconInfo )
// 					{
// 						CItemDetail :: SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->m_stItem.itembaseinfo.ustItemID );
// 						pCompareItem = GetCompareItem();
// 						if( pItemDetail 
// 							&& 
// 							( pItemDetail->ucItemType == CItemDetail::ITEMTYPE_WEAPON 
// 							|| pItemDetail->ucItemType == CItemDetail::ITEMTYPE_ARMOUR
// 							)
// 							)
// 						{
// 							CItemDetail::SItemCanEquip *pEquip = (CItemDetail::SItemCanEquip *)pItemDetail;
// 							{	
// 								pEquip->eAccounterment
// 								BOOL bContinue = FALSE;
// 								int nCanEquipPart = 0;
// 								for( int i=0; i< EPT_MaxEquitPart; i++ )
// 								{
// 									if( bContinue )
// 									{
// 										continue;
// 									}
// 									if ( pEquip->arrayCanEquip[i] == 1 )
// 									{
// 										nCanEquipPart = i;
// 										bContinue = TRUE;
// 									}
// 								}
// 								 added, jiayi, [2009/8/26], 判断时装
// 								bool bFashion = pEquip->bFashion;
// 								 added, jiayi, [2009/7/1]							
// 								const SCharItem* pCompareEquipItem = &thePlayerRole.m_pVisual->GetSuitArray( (int)bFashion )[nCanEquipPart];
// 								if( pCompareEquipItem )
// 								{
// 									pCompareItem->SetData( (void*)pCompareEquipItem, eIcon_Enable, eTipFlag_Normal, true, theHeroGame.GetPlayerMgr()->GetMyID() );
// 									bHaveCompare = true;
// 								}
// 								else
// 									bHaveCompare = false;
// 
// 								bContinue = FALSE;
// 							}
// 						}
// 					}
// 
// 					if( bHaveCompare )
// 					{
// 						theIconInfoMouseTip.SetDisplayInfo( &pItem->m_stIcon,
// 							rcItem.left, rcItem.top, m_bIsShop,
// 							m_pstData->m_szFont, m_pstData->m_nFontSize * GetREAL_SCALE(this),
// 							m_pstData->m_colFont,
// 							m_bShowAllInfo, &pCompareItem->m_stIcon, HQ_TimeGetTime(), m_nDelayTime );
// 						ret = true;
// 					}
// 					else
// 					{
// 						if (pItem->m_stIcon.Id() != ErrorUnsignedShortID)
// 						{
// 							theIconInfoMouseTip.SetDisplayInfo( &pItem->m_stIcon,
// 								rcItem.left, rcItem.top, m_bIsShop,
// 								m_pstData->m_szFont, m_pstData->m_nFontSize * GetREAL_SCALE(this),
// 								m_pstData->m_colFont,
// 								m_bShowAllInfo, 0, HQ_TimeGetTime(), m_nDelayTime );
// 							ret = true;
// 						}
// 						else
// 						{
// 							if (strlen(m_pstData->m_szCaption) > 0)
// 							{
// 								theIconInfoMouseTip.SetDisplayInfo( &TipInfo,
// 									rcItem.left, rcItem.top, false,
// 									m_pstData->m_szFont, m_pstData->m_nFontSize,
// 									m_pstData->m_colFont,
// 									true );
// 								ret = true;
// 							}
// 						}
// 					}
// 				}

			}
		}

		if (ptNewMouseOnSel.x == -1 || ptNewMouseOnSel.y == -1)
		{
			m_ptMouseOnSel.x = -1;
			m_ptMouseOnSel.y = -1;
			if (GetFrameFather())
			{
				GetFrameFather()->SetRedraw();
			}
		}
		if ( m_nMaxHeightCount > m_nHeightShowMaxCount && m_UIScroll.GetEnable())
		{
			m_UIScroll.OnMouseMove(nFlags, nX, nY);
		}
	}
	return ret;
}

int ControlIconDrag::Refeash()
{
// 	float fRate = (float)m_UIScroll.GetValue()/m_UIScroll.GetMaxValue();
	m_nShowStartHeight = m_UIScroll.GetValue();//(int)((m_nMaxHeightCount-m_nHeightShowMaxCount)*fRate+0.5f);

	if ( m_nShowStartHeight < 0 )
	{
		m_nShowStartHeight = 0;
	}
	return m_nShowStartHeight;
}

bool ControlIconDrag::OnMouseWheel( bool bUp, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if ( PtInObject(nX, nY,false) == true )
		{
			if ( m_nMaxHeightCount > m_nHeightShowMaxCount )
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
					if( m_UIScroll.GetEnable())
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

bool ControlIconDrag::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if( m_bNotMsgClick )
			return false;

		if (GetFrameFather())
		{
			GetFrameFather()->SetRedraw();
		}

		m_nPressItemIndex = -1;

		if ( m_nMaxHeightCount > m_nHeightShowMaxCount && m_UIScroll.OnLButtonDown( nFlags, nX, nY) == true)
		{
			Refeash();
		}
		else if ( PtInObject(nX, nY,true) == true )
		{
			SetActivate();

			m_bLClick = true;

			if (theIconDragManager.IsIconDraging())
				theIconDragManager.SetDstListImg( this );

			if ( GetTilePt( nX, nY, &m_ptCurSel ) == true && CanbePick() )
			{
				S_ListImg* pListImg = GetItem(m_ptCurSel.x, m_ptCurSel.y);
				if ( pListImg && !pListImg->IsNull() &&
					!theIconDragManager.IsIconDraging() && IsEnableDragOut())
				{

					if ( pListImg->m_eEnable == eIcon_Enable ||
						IsDisableCanbePick() )
					{
						POINT mousePos;
						mousePos.x = nX;
						mousePos.y = nY;
						RECT realRC;
						GetItemRect(m_ptCurSel.x, m_ptCurSel.y, realRC);
						POINT realPos;
						realPos.x = realRC.left;
						realPos.y = realRC.top;
						theIconDragManager.SetDrag( this, pListImg, m_ptCurSel, realPos, mousePos );
						PlaySound();
					}
				}

				m_nPressItemIndex = m_ptCurSel.y*m_nWidthShowMaxCount + m_ptCurSel.x;

				if (pListImg && !pListImg->IsNull())
					return m_bMsgHoldup;
				else
					return false;
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

bool ControlIconDrag::OnLButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if( m_bNotMsgClick )
			return false;

		if (GetFrameFather())
		{
			GetFrameFather()->SetRedraw();
		}
		m_nPressItemIndex = -1;

		if ( m_nMaxHeightCount > m_nHeightShowMaxCount && m_UIScroll.OnLButtonUp(nFlags, nX, nY) )
		{

		}
		else if ( PtInObject( nX, nY ,true) )
		{
			m_bLClick = false;

			theIconDragManager.SetDstListImg( this );

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

			pListImg = GetItem(m_ptMouseOnSel.x, m_ptMouseOnSel.y);

			if( NULL == pListImg || theIconDragManager.GetIconDragOn() || theIconDragManager.IsIconMoved() )
			{
				theIconDragManager.SetIconDragOn(false);
				return false;
			}

			if( GetKeyboardInput(0x2A/*DIK_LSHIFT*/) || GetKeyboardInput(0x36/*DIK_RSHIFT*/) ) 
			{
				if( m_pFunShiftLBClick )
				{
					m_pFunShiftLBClick( this, pListImg );
				}
			}
			else
			{
				if( !pListImg->IsNull() )
				{
					if( m_pFunButtonClick )
					{
						m_pFunButtonClick(this, pListImg);
					}
				}
			}

			if (pListImg && !pListImg->IsNull())
				return m_bMsgHoldup;
			else
				return false;
		}
		else
		{
			return false;
		}
		return m_bMsgHoldup;
	}
	return false;
}

bool ControlIconDrag::OnRButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if( m_bNotMsgClick )
			return false;

		if ( PtInObject( nX, nY ,true) )
		{
			if ( GetTilePt( nX, nY, &m_ptCurSel ) == true && CanbePick() )
			{
				if (GetFrameFather())
				{
					GetFrameFather()->SetRedraw();
				}
				m_nPressItemIndex = m_ptCurSel.y*m_nWidthShowMaxCount + m_ptCurSel.x;
			}
			S_ListImg* pListImg = GetItem(m_ptCurSel.x, m_ptCurSel.y);
			if (pListImg && !pListImg->IsNull())
				return m_bMsgHoldup;
			else
				return false;
		}
	}
	return false;
}

bool ControlIconDrag::OnRButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if( m_bNotMsgClick )
			return false;

		if (GetFrameFather())
		{
			GetFrameFather()->SetRedraw();
		}
		m_nPressItemIndex = -1;

		if ( PtInObject( nX, nY ,true) )
		{
			if ( m_pFunRButtonUp )
			{
				m_pFunRButtonUp( this, GetItem(m_ptMouseOnSel.x, m_ptMouseOnSel.y) );
			}
			S_ListImg* pListImg = GetItem(m_ptCurSel.x, m_ptCurSel.y);
			if (pListImg && !pListImg->IsNull())
				return m_bMsgHoldup;
			else
				return false;
		}
	}
	return false;
}

bool ControlIconDrag::OnLButtonDBClick( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if ( PtInObject(nX, nY,true) == true )
		{
			OnLDBClick( m_ptMouseOnSel.x, m_ptMouseOnSel.y,
				GetItem(m_ptMouseOnSel.x, m_ptMouseOnSel.y),
				this );
			return true;
		}
	}
	return false;
}
bool ControlIconDrag::OnDragDisableOn( const int nX, const int nY, OUT IN S_ListImg* pItem, IN ControlObject* pSender )
{
	if ( pItem->IsNull() )
	{
		return false;
	}
	PlaySound();
	S_ListImg *pDstItem = GetItem(nX,nY);
	if ( m_pFunDragDisableOn && pDstItem)
	{
		return m_pFunDragDisableOn(pSender,this, pItem, pDstItem );
	}
	return false;

}

bool ControlIconDrag::OnDragDisableOut( IN ControlObject* pSender,OUT IN S_ListImg* pItem )
{
	if ( pItem->IsNull() )
	{
		return false;
	}

	PlaySound();

	if( m_pFunDragDisableOut )
	{
		return m_pFunDragDisableOut(pSender,pItem);
	}

	return false;
}

bool ControlIconDrag::OnDragOn( const int nX, const int nY, OUT IN S_ListImg* pItem,
							   IN ControlObject* pSender ) 
{
	if ( pItem->IsNull() )
	{
		return false;
	}
	PlaySound();
	S_ListImg *pDstItem = GetItem(nX,nY);
	if ( m_pFunDragOn && pDstItem)
	{
		return m_pFunDragOn(pSender,this, pItem, pDstItem );
	}

#ifdef _DEBUG
	else if ( m_debug_bHasWarning )
	{
		char szDebug[128];
		char szFatherID[128] = "";
		if ( m_pFather )
		{
			strcpy( szFatherID, m_pFather->GetControlID() );
		}
		sprintf(szDebug,"[%s]::[%s] ControlIconDrag::OnDragOn() not defend!!\r\n", szFatherID, GetControlID() );
		//OutputDebugString(szDebug);
	}
#endif

	//	return AddItem1( nX, nY, pItem );
	return false;
}

//bool ControlIconDrag::OnDragOff( const int nX, const int nY, OUT IN S_ListImg* pItem,
//								IN ControlObject* pSender )
//{
//	if ( pItem->IsNull() )
//	{
//		return false;
//	}
//
//	if ( m_pFunDragOff )
//	{
//		return m_pFunDragOff(pSender,this, pItem );
//	}
//#ifdef _DEBUG
//	else if ( m_debug_bHasWarning )
//	{
//		char szDebug[128];
//		char szFatherID[128] = "";
//		if ( m_pFather )
//		{
//			strcpy( szFatherID, m_pFather->GetControlID() );
//		}
//		sprintf(szDebug,"[%s]::[%s] ControlListImage::OnDragOff(char* szData) not defend!!\r\n", szFatherID, GetControlID() );
//		OutputDebugString(szDebug);
//	}
//#endif
//
//	return RemoveItem( nX, nY, 1 );
//}

void ControlIconDrag::Clear( bool bChangeStartIndex )
{
	for ( int n=0; n<m_vtItem.size(); n++ )
	{
		m_vtItem[n].Clear();
	}
	if( bChangeStartIndex == true )
	{
		m_nShowStartHeight = 0;
	}
	memset( &m_ptCurSel, 0, sizeof(POINT) );
	m_nShowStartHeight = 0;
}

int ControlIconDrag::GetItemIndex( IN const S_ListImg *pItem )
{

	S_ListImg *pCurItem = NULL;
	for ( int n=0; n<m_vtItem.size(); n++ )
	{
		pCurItem = &(m_vtItem[n]);
		if ( pCurItem == pItem )
		{
			return n;
		}
	}
	return -1;
}
//to zizi 这个应该放到 逻辑层处理 时间有限 先放到这里 有时间再改
int ControlIconDrag::GetNullItem( bool reverse)
{
	S_ListImg *pCurItem = NULL;
	if( reverse )
	{
		int count = m_nEnbaleCnt == -1 ? m_vtItem.size() : m_nEnbaleCnt;
		for( int n=count - 1; n>=0; --n )
		{
			if( m_nEnbaleCnt != -1 && n >= m_nEnbaleCnt )
				return -1;//说明没有空的了 (例如：背包已满)

			pCurItem = &(m_vtItem[n]);
			if(pCurItem->IsNull())
				return n;
		}
	}
	else
	{
		for( int n=0; n<m_vtItem.size(); ++n)
		{
			if( m_nEnbaleCnt != -1 && n >= m_nEnbaleCnt )
				return -1;//说明没有空的了 (例如：背包已满)

			pCurItem = &(m_vtItem[n]);
			if(pCurItem->IsNull())
				return n;
		}
	}
	return -1;	//-1 说明没有空的了 (例如：背包已满) 
}
void ControlIconDrag::InitItemDate()
{
	assert( m_nWidthShowMaxCount > 0 && m_nMaxHeightCount > 0 );
	m_vtItem.resize( m_nWidthShowMaxCount*m_nMaxHeightCount );
}

void ControlIconDrag::SetScrollVisable( bool bShow )
{
	m_UIScroll.SetVisable( bShow );
}

bool ControlIconDrag::OnKeyDown( UINT nChar )
{
	if( nChar == VK_LSHIFT || nChar == VK_RSHIFT )
		m_bShiftDown = true;
	return false;
}

bool ControlIconDrag::OnKeyUp( UINT nChar )
{
	if( nChar == VK_LSHIFT || nChar == VK_RSHIFT )
		m_bShiftDown = false;
	return false;
}

void ControlIconDrag::SetEnableRowCnt(int cnt)
{
	m_nEnbaleRowCnt = cnt;
	if (m_nEnbaleRowCnt > m_nMaxHeightCount)
		m_nEnbaleRowCnt = m_nMaxHeightCount;

	if (m_nEnbaleRowCnt != -1)
		SetEnableCnt(m_nEnbaleRowCnt * m_nWidthShowMaxCount);
	else
		SetEnableCnt(-1);
}

void ControlIconDrag::SetEnableCnt(int cnt)
{
	m_nEnbaleCnt = cnt;
	if (m_nEnbaleCnt > m_vtItem.size())
		m_nEnbaleCnt = m_vtItem.size();

	if (m_nEnbaleCnt != -1)
	{
		for (size_t i = m_nEnbaleCnt; i < m_vtItem.size(); ++i)
			m_vtItem[i].m_eEnable = eIcon_Lock;
	}
	else
	{
		for (size_t i = 0; i < m_vtItem.size(); ++i)
		{
			if (m_vtItem[i].m_eEnable == eIcon_Lock)
				m_vtItem[i].m_eEnable = eIcon_Enable;
		}
	}
}

void ControlIconDrag::RefreshTipShow( const int nX, const int nY )
{
	POINT ptNewMouseOnSel ;
	if ( GetTilePt( nX, nY, &ptNewMouseOnSel ) == true )
	{
		// added, jiayi, [2009/10/20]
		// 这里tip的位置取当前item的左边界
		// 这样就可以固定tip位置
		RECT rcItem;
		GetItemRect( nX, nY, rcItem );	
		// 偏移到中间
		rcItem.left += GetItemWidth() / 2;
		rcItem.top += GetItemHeight() / 2;
		S_ListImg *pItem = GetItem( ptNewMouseOnSel.x, ptNewMouseOnSel.y );
		if( ms_pFuncBlobalOnMouseMove )
			ms_pFuncBlobalOnMouseMove( pItem, m_bEnableCompare, rcItem, this );
	}
}

void ControlIconDrag::SetVisable( const bool bVisable )
{
	ControlObject::SetVisable(bVisable);
	for ( int n=0; n<m_vtItem.size(); n++ )
	{
		CSmartAnimation* pCoolDownAni = m_vtItem[n].GetCoolDownAni();
		if( pCoolDownAni && pCoolDownAni->IsInAnimation() )
		{
			GetFrameFather()->GetUiAniManageNotNULL()->StopAnimation( pCoolDownAni );
		}

        CSmartAnimation* pSparkAni = m_vtItem[n].GetSparkAni();
        if( pSparkAni && pSparkAni->IsInAnimation() )
        {
            GetFrameFather()->GetUiAniManageNotNULL()->StopAnimation( pSparkAni );
        }
	}
}

ControlIconDrag::S_ListImg::S_ListImg()
{
    m_pkIconInfo = NULL;
	if( S_IconInfoBase::ms_pFuncCreateIconInfo )
		m_pkIconInfo = S_IconInfoBase::ms_pFuncCreateIconInfo();

	m_dwCooldownFinishStartTime = 0;
	m_bCooldownStart = false;
	m_pCoolDownAni = NULL;
	m_pAniManage = NULL;
    m_pSparkAnimation = NULL;
    m_dwSparkBeginTime = 0;
	Clear();
}

ControlIconDrag::S_ListImg::S_ListImg( const S_ListImg& v )
{
	if( S_IconInfoBase::ms_pFuncCreateIconInfo )
		m_pkIconInfo = S_IconInfoBase::ms_pFuncCreateIconInfo();

	if( v.m_pkIconInfo )
	{
		//*m_pkIconInfo = *v.m_pkIconInfo;
		m_pkIconInfo->Clone( v.m_pkIconInfo );
	}

    m_bSpark = v.m_bSpark;
	m_eEnable = v.m_eEnable;
	m_dwStartTime = v.m_dwStartTime;
	m_dwPeriod = v.m_dwPeriod;
	m_dwFlags = v.m_dwFlags;
	m_col = v.m_col;
	m_bUseCol = v.m_bUseCol;
	m_dwColor = v.m_dwColor;
	m_pCoolDownAni = NULL;
    m_pSparkAnimation = NULL;
    m_dwSparkBeginTime = v.m_dwSparkBeginTime;
}

ControlIconDrag::S_ListImg& ControlIconDrag::S_ListImg::operator=( const ControlIconDrag::S_ListImg& v )
{
	//m_stIcon = v.m_stIcon;
	if( !m_pkIconInfo && S_IconInfoBase::ms_pFuncCreateIconInfo )
		m_pkIconInfo = S_IconInfoBase::ms_pFuncCreateIconInfo();

	if( m_pkIconInfo )
	{
		//*m_pkIconInfo = *v.m_pkIconInfo;
		m_pkIconInfo->Clone( v.m_pkIconInfo );
	}

    m_bSpark = v.m_bSpark;
	m_eEnable = v.m_eEnable;
	m_dwStartTime = v.m_dwStartTime;
	m_dwPeriod = v.m_dwPeriod;
	m_dwFlags = v.m_dwFlags;
	m_col = v.m_col;
	m_bUseCol = v.m_bUseCol;
	m_dwColor = v.m_dwColor;
	//m_pCoolDownAni = NULL;
	return *this;
}

ControlIconDrag::S_ListImg::~S_ListImg()
{
	Clear();
	if (m_pCoolDownAni)
	{
		delete m_pCoolDownAni;
		m_pCoolDownAni = NULL;
	}
    if( m_pSparkAnimation )
    {
        delete m_pSparkAnimation;
        m_pSparkAnimation = NULL;
    }
	delete m_pkIconInfo;
	m_pkIconInfo = 0;
}

CSmartAnimation* ControlIconDrag::S_ListImg::GetCoolDownAniNotNULL(CSmartAniManage* pAniManage) 
{
	if (NULL == m_pCoolDownAni)
	{
		m_pCoolDownAni = new CSmartAnimation( pAniManage->GetFrame()->GetFrameRender() );
		CIntervalFunctor* pSrcXFunctor = (CIntervalFunctor*)CFunctorMaker::GetInstance()->CreateFunctor("Interval");
		m_pCoolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_SrcX,0,pSrcXFunctor);
		m_pAniManage = pAniManage;
	}
	return m_pCoolDownAni;
}

CSmartAnimation* ControlIconDrag::S_ListImg::GetSparkAniNotNULL( CSmartAniManage* pAniManage )
{
    if( NULL == m_pSparkAnimation )
    {
        m_pSparkAnimation = new CSmartAnimation( pAniManage->GetFrame()->GetFrameRender() );

        MeXmlDocument doc;
        std::string strFilePath = std::string( GetRootPath() ) + "\\data\\Ui\\UIAni\\PackNewEquip.2DAni";
        if( !doc.LoadFile( strFilePath.c_str() ) )
        {
            assert( false && "Load Spark Animation Failed!" );
            return m_pSparkAnimation;
        }

        MeXmlElement* pElement = doc.FirstChildElement( "ProgressEffect" );
        if( pElement )
        {
            CXmlAnimation* pSmart = ( CXmlAnimation* )m_pSparkAnimation;
            pSmart->Initialize( pElement );
        }

        m_pAniManage = pAniManage;
    }
    return m_pSparkAnimation;
}

void ControlIconDrag::S_ListImg::Clear()
{
	if( m_pkIconInfo )
	{
		m_pkIconInfo->Clear();
		if( m_pkIconInfo == theIconInfoMouseTip.GetIconInfo() )
			theIconInfoMouseTip.Clear();
	}
	
	if (m_pCoolDownAni)
	{
		if(m_pCoolDownAni->IsInAnimation())
		{
			m_pAniManage->StopAnimation(m_pCoolDownAni);
		}
	}
    
    if( m_pSparkAnimation )
    {
        if( m_pSparkAnimation->IsInAnimation() )
        {
            m_pAniManage->StopAnimation( m_pSparkAnimation );
        }
    }

	m_bSpark = false;
	m_eEnable = eIcon_Enable;
	m_dwStartTime = 0;
	m_dwPeriod = 0;
	m_dwFlags = 0;
	m_bUseCol = false;
	m_dwColor = 0xffffffff;
}