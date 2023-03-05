#pragma once

/*
 * 2012.7.5 滚动对话框封装
 * 使用步骤:
 * 1. class YourDialog : public ScrollableDialog
 *
 * 2. 构造函数中YourDialog::YourDialog() : ScrollableDialog(YourDialog::IDD, pParent, SB_VERT) {}
 *
 * 3. OnVScroll中添加以下代码
 *    VerticalScrollHandler(nSBCode, nPos);
 *    CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
 *
 * 4. OnSize中添加以下代码
 *    Scroll_Setup(width, rcClient.Height());
 */
class ScrollableDialog : public CDialog
{
public:
	DECLARE_DYNAMIC(ScrollableDialog)

public:
	ScrollableDialog(UINT nIDTemplate, CWnd *pParentWnd, int bar);
	virtual ~ScrollableDialog();

protected:
	void HorizontalScrollHandler(UINT nSBCode, UINT nPos);
	void VerticalScrollHandler(UINT nSBCode, UINT nPos);	

	void Scroll_Setup(int max, int pageSize);
	void Scroll_To(int pos);
	void Scroll_LineUpDown(int delta);

protected:
	int mBar;
	int mCurPos;

	SCROLLINFO mScrollInfo;
};