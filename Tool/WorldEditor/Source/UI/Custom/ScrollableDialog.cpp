#include "stdafx.h"
#include "ScrollableDialog.h"

IMPLEMENT_DYNAMIC(ScrollableDialog, CDialog)

ScrollableDialog::ScrollableDialog(UINT nIDTemplate, CWnd *pParentWnd, int bar)
	: CDialog(nIDTemplate, pParentWnd)
{
	mBar = bar;
	mCurPos = 0;
}

ScrollableDialog::~ScrollableDialog()
{

}

void ScrollableDialog::HorizontalScrollHandler(UINT nSBCode, UINT nPos)
{

}

void ScrollableDialog::VerticalScrollHandler(UINT nSBCode, UINT nPos)
{
	switch (nSBCode)
	{
	case SB_LINEUP:
		Scroll_LineUpDown(-10);
		break;

	case SB_LINEDOWN:
		Scroll_LineUpDown(10);
		break;

	case SB_THUMBTRACK:
		Scroll_To(nPos);
		break;
	}
}

void ScrollableDialog::Scroll_Setup(int max, int pageSize)
{
	ZeroMemory(&mScrollInfo, sizeof(SCROLLINFO));
	mScrollInfo.cbSize = sizeof(SCROLLINFO);
	mScrollInfo.fMask = SIF_ALL;
	mScrollInfo.nMin = 0;
	mScrollInfo.nMax = max;
	mScrollInfo.nPage = pageSize;
	mScrollInfo.nPos = 0;
	SetScrollInfo(mBar, &mScrollInfo);
}

void ScrollableDialog::Scroll_To(int pos)
{
	int delta = pos - mCurPos;
	if (mBar == SB_HORZ)
		ScrollWindow(-delta, 0);
	else
		ScrollWindow(0, -delta);

	SetScrollPos(mBar, pos);
	mCurPos = pos;
}

void ScrollableDialog::Scroll_LineUpDown(int delta)
{
	if (mBar == SB_HORZ)
		ScrollWindow(-delta, 0);
	else
		ScrollWindow(0, -delta);

	mCurPos += delta;
	SetScrollPos(mBar, mCurPos);
}
