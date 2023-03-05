#include "MeUi/ControlIconDragManager.h"
#include "FuncPerformanceLog.h"
#include "MeUi/MouseManager.h"
#include "Me3d/Global.h"
#include "MeUi/UiPicture.h"

#define DRAG_ICON_SCALE 6

ControlIconDragManager theIconDragManager;

ControlIconDragManager::ControlIconDragManager(void)
{
	m_pListImgSrc = NULL;
	m_pListImgDst = NULL;
	memset( &m_ptMouse, 0, sizeof(m_ptMouse) );
	memset( &m_ptCurSelItemPos, 0, sizeof(m_ptCurSelItemPos) );
	m_pCurSelItem = NULL;
	m_pLastSelItem = NULL;
	m_isMoved = false;
	m_isDraging = false;
	m_isRemove = false;
	m_nIconArrowId = -1;
	m_isDragOn = false;
	m_pFunSetDragItem = NULL;
	m_pFunClearDragItem = NULL;
	m_pFunDragBegin = NULL;
	m_pFunDragEnd = NULL;
}

ControlIconDragManager::~ControlIconDragManager(void)
{
}


void ControlIconDragManager::Render()
{
	guardfunc;
	if (m_isMoved && m_pListImgSrc && m_pCurSelItem && m_pCurSelItem->m_pkIconInfo )
	{
		RECT rcDst;
		rcDst.left = m_ptMouse.x;
		rcDst.top = m_ptMouse.y;
		rcDst.right = rcDst.left + m_pListImgSrc->GetIconSize() - DRAG_ICON_SCALE * ControlObjectGetSCALE(NULL);
		rcDst.bottom = rcDst.top + m_pListImgSrc->GetIconSize() - DRAG_ICON_SCALE * ControlObjectGetSCALE(NULL);

		bool bOldShow = m_pCurSelItem->m_pkIconInfo->m_bShowCount;
		m_pCurSelItem->m_pkIconInfo->m_bShowCount = false;
		m_pCurSelItem->m_pkIconInfo->DisplayIcon( &rcDst, 0xffffffff, 0, 6, RGB(0xff,0xff,0xff) );
		m_pCurSelItem->m_pkIconInfo->m_bShowCount = bOldShow;

		static bool load = false;
		static char fullpath[MAX_PATH] = {0};
		if (!load)
		{
			sprintf( fullpath, "%s\\Data\\Ui\\Icon\\IconArrow.dds", GetRootPath() );
			load = true;
		}

		theControlPictureManager.BitBlt( &m_nIconArrowId,
			fullpath,
			&rcDst, NULL, 0xffffffff );
	}

	if ( m_pCurSelItem )
	{
		if ( m_pCurSelItem->IsNull() )
		{
			ClearDrag();
			//m_pLastSelItem = NULL;
		}
	}
	unguard;
}

void ControlIconDragManager::Run()
{
}

void ControlIconDragManager::SetIconStateAfterDrag( eIconDrawState eIconState )
{
	m_eIconState = eIconState;
}

bool ControlIconDragManager::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
	//if ( m_pCurSelItem )
	//{
	//	SetCursor( LoadCursor(NULL, IDC_NO ) );
	//}
	m_ptMouse.x = nX;
	m_ptMouse.y = nY;
	if (m_pCurSelItem && m_pListImgSrc&& !m_isMoved &&
		(abs(m_ptMouse.x - m_ptCurSelItemOldMousePos.x) > m_pListImgSrc->GetIconSize() / 2 ||
		abs(m_ptMouse.y - m_ptCurSelItemOldMousePos.y) > m_pListImgSrc->GetIconSize() / 2 ) )
	{
		m_isMoved = true;

		if (m_pCurSelItem && m_pListImgSrc && m_pListImgSrc->IsEnableDragOut())
		{
			m_eIconState = m_pCurSelItem->m_eEnable;
			m_pCurSelItem->m_eEnable = eIcon_Disable;
		}

		if (m_pFunDragBegin)
			m_pFunDragBegin(m_pListImgSrc, m_pCurSelItem);
	}
	return false;
}

bool ControlIconDragManager::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( m_pListImgSrc && m_isDraging && m_pListImgSrc->IsEnableDragOut())
	{
		theMouseManager.ForceSetCursor();
		if ( m_pCurSelItem && m_pCurSelItem->m_pkIconInfo ) 
		{
			POINT pt;
			if ( m_pListImgDst  && m_pListImgDst->GetTilePt( nX, nY, &pt ) )
			{
				if (m_pListImgDst->IsEnableDragIn())
				{
					m_pLastSelItem = NULL;
					if ( m_pListImgSrc == m_pListImgDst && 
						m_ptCurSelItemPos.x == pt.x && m_ptCurSelItemPos.y == pt.y )
					{
						ClearDrag();
						m_isDragOn = true;
						return false;
					}

					if( m_pListImgDst->OnDragOn( pt.x, pt.y, m_pCurSelItem, m_pListImgSrc ) == true )
					{
						if ( !m_pCurSelItem->m_pkIconInfo->PlaySound() )
						{
							m_pListImgDst->PlaySound();
						}
						ClearDrag();
					}
					m_isDragOn = true;
				}
				else
				{
					m_pListImgDst->OnDragDisableOn( pt.x, pt.y, m_pCurSelItem, m_pListImgSrc );
					m_isRemove = true;

				}
			}
			else
			{
				m_isRemove = true;
			}
			//ClearDrag();
		}
	}
	return false;
}

bool ControlIconDragManager::OnRButtonDown( UINT nFlags, const int nX, const int nY )
{
	ClearDrag();
	m_pLastSelItem = NULL;
	return false;
}

bool ControlIconDragManager::OnLButtonUp( UINT nFlags, const int nX, const int nY,  bool otheruser, int index )
{
	if ( m_pListImgSrc && m_pListImgSrc->IsEnableDragOut() )
	{
		theMouseManager.ForceSetCursor();
		if ( m_pListImgDst && m_pCurSelItem && m_pCurSelItem->m_pkIconInfo && m_isMoved ) 
		{
			if (m_pListImgDst->IsEnableDragIn())
			{
				POINT pt;

				if ( m_pListImgDst->GetTilePt( nX, nY, &pt ) )
				{
					RECT rc;
					m_pListImgDst->GetItemRect(pt.x, pt.y, rc);

					if ( m_pListImgSrc == m_pListImgDst && 
						m_ptCurSelItemPos.x == pt.x && m_ptCurSelItemPos.y == pt.y )
					{
						m_pLastSelItem = NULL;
						ClearDrag();
						return false;
					}

					m_pLastSelItem = NULL;
					if( m_pListImgDst->OnDragOn( pt.x, pt.y, m_pCurSelItem, m_pListImgSrc ) == true )
					{
						if ( !m_pCurSelItem->m_pkIconInfo->PlaySound() )
						{
							m_pListImgDst->PlaySound();
						}
						//m_pListImgSrc->OnDragOff( m_ptCurSelItemPos.x, m_ptCurSelItemPos.y,
						//							m_pCurSelItem, m_pListImgDst );
					}
					ClearDrag();
				}
				else
					m_isDraging = m_isMoved;
			}
			else
			{
				POINT pt;

				if ( m_pListImgDst->GetTilePt( nX, nY, &pt ) )
				{
					m_pListImgDst->OnDragDisableOn( pt.x, pt.y, m_pCurSelItem, m_pListImgSrc );
				}
				m_isDraging = m_pListImgDst == NULL && m_isMoved;
			}
		}
		else
			m_isDraging = m_pListImgDst == NULL && m_isMoved;

		if (!m_isDraging)
			ClearDrag();

		//if( otheruser )
		//{
		//	ClearDrag();
		//}
		//else if( index == 0 )
		//{
		//	ClearDrag();
		//}
	}
	return false;
}

bool ControlIconDragManager::OnRButtonUp( UINT nFlags, const int nX, const int nY )
{
	ClearDrag();
	m_pLastSelItem = NULL;
	m_isRemove = false;
	return false;
}

bool ControlIconDragManager::OnLButtonDBClick( UINT nFlags, const int nX, const int nY )
{
	return false;
}

bool ControlIconDragManager::OnRButtonDBClick( UINT nFlags, const int nX, const int nY )
{
	return false;
}

bool ControlIconDragManager::SetDrag( IN ControlIconDrag* pList,
									 IN ControlIconDrag::S_ListImg* pItem,
									 const POINT ptItemPos, const POINT& realPos, const POINT& mousePos )
{
	m_pListImgSrc = pList;
	m_pCurSelItem = pItem;
	m_ptCurSelItemPos = ptItemPos;
	m_ptCurSelItemOldRealPos = realPos;
	m_ptCurSelItemOldMousePos = mousePos;

	m_pLastSelItem = m_pCurSelItem;
	m_isMoved = false;
	m_isDraging = false;

	if (m_pCurSelItem)
		m_eIconState = m_pCurSelItem->m_eEnable;

	if (m_pFunSetDragItem)
		m_pFunSetDragItem(m_pListImgSrc, m_pCurSelItem);
	return true;
}

void ControlIconDragManager::ClearDrag()
{
	if (m_pFunClearDragItem)
		m_pFunClearDragItem(m_pListImgDst, m_pListImgSrc, m_pCurSelItem);

	if (m_pFunDragEnd)
		m_pFunDragEnd(m_pListImgDst, m_pListImgSrc, m_pCurSelItem);

	if (m_pListImgSrc)
		m_pListImgSrc->SetPressItemIndex(-1);

	if (m_pListImgDst)
		m_pListImgDst->SetPressItemIndex(-1);
	if (m_pCurSelItem && m_pListImgSrc && m_pListImgSrc->IsEnableDragOut() && m_isMoved)
		m_pCurSelItem->m_eEnable = m_eIconState;

	m_pListImgSrc = NULL;
	m_pListImgDst = NULL;
	m_pCurSelItem = NULL;
	m_ptCurSelItemOldRealPos.x = 0;
	m_ptCurSelItemOldRealPos.y = 0;
	m_ptCurSelItemOldMousePos.x = 0;
	m_ptCurSelItemOldMousePos.y = 0;
	m_isMoved = false;
	m_isDraging = false;
}
void ControlIconDragManager::ClearInvalidPointer( const ControlIconDrag* const pIconDrag )
{
	if( m_pListImgSrc == pIconDrag )
	{
		m_pListImgSrc = NULL;
		m_pCurSelItem = NULL;
	}
	if( m_pListImgDst == pIconDrag )
	{
		m_pListImgDst = NULL;
	}
}