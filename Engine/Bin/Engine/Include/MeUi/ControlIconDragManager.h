
#pragma once

#include "MeUi/ControlIconDrag.h"
#include <Windows.h>

class ControlIconDragManager
{
public:
	void Render();
	void Run();
	bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnRButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnLButtonUp( UINT nFlags, const int nX, const int nY, bool otheruser, int index );
	bool OnRButtonUp( UINT nFlags, const int nX, const int nY );
	bool OnLButtonDBClick( UINT nFlags, const int nX, const int nY );
	bool OnRButtonDBClick( UINT nFlags, const int nX, const int nY );

	bool SetDrag( IN ControlIconDrag* pList, IN ControlIconDrag::S_ListImg* pItem,
		const POINT ptItemPos, const POINT& realPos, const POINT& mousePos );
	void SetDstListImg( IN ControlIconDrag* pList ) { m_pListImgDst = pList; }
	void ClearDrag();
	//
	ControlIconDrag::S_ListImg* GetCurItem(){ return m_pCurSelItem; }

	bool IsIconMoved() { return m_isMoved; }
	bool IsIconDraging() { return m_isDraging; }

	void SetRemoveIcon(bool v) { m_isRemove = v; }
	bool GetRemoveIcon() const { return m_isRemove; }

	void SetIconDragOn(bool v) { m_isDragOn = v; }
	bool GetIconDragOn() const { return m_isDragOn; }

	void SetDraging()
	{
		m_isMoved = true;
		m_isDraging = true;
	}
	typedef void (*funDragItemBegin)(ControlIconDrag* pList, ControlIconDrag::S_ListImg* pItem);
	typedef void (*funDragItemEnd)(ControlIconDrag* pDstList, ControlIconDrag* pSrcList, ControlIconDrag::S_ListImg* pSrcListItem);

	void SetOnSetDragItemFun(funDragItemBegin fun) { m_pFunSetDragItem = fun; }
	void SetOnClearDragItemFun(funDragItemEnd fun) { m_pFunClearDragItem = fun; }
	void SetOnDragBeginFun(funDragItemBegin fun) { m_pFunDragBegin = fun; }
	void SetOnDragEndFun(funDragItemEnd fun) { m_pFunDragEnd = fun; }

	ControlIconDrag* GetDragIconDrag() { return m_pListImgSrc; }
	ControlIconDrag* GetDropIconDrag() { return m_pListImgDst; }

	void ClearInvalidPointer( const ControlIconDrag* const pIconDrag );

	void SetIconStateAfterDrag( eIconDrawState eIconState );

public:
	ControlIconDrag::S_ListImg	*m_pLastSelItem;
	POINT			m_ptMouse;

private:
	ControlIconDrag	*m_pListImgSrc;
	ControlIconDrag	*m_pListImgDst;
	ControlIconDrag::S_ListImg	*m_pCurSelItem;
	POINT			m_ptCurSelItemPos;
	POINT			m_ptCurSelItemOldRealPos;
	POINT			m_ptCurSelItemOldMousePos;

	bool			m_isMoved;
	bool			m_isDraging;
	bool			m_isRemove;
	bool			m_isDragOn;
	eIconDrawState	m_eIconState;

	int	m_nIconArrowId;

	funDragItemBegin		m_pFunSetDragItem;
	funDragItemEnd			m_pFunClearDragItem;
	funDragItemBegin		m_pFunDragBegin;
	funDragItemEnd			m_pFunDragEnd;

public:
	ControlIconDragManager(void);
	~ControlIconDragManager(void);
};

extern ControlIconDragManager theIconDragManager;
