#pragma once

/*
 * 2012.7.5 �����Ի����װ
 * ʹ�ò���:
 * 1. class YourDialog : public ScrollableDialog
 *
 * 2. ���캯����YourDialog::YourDialog() : ScrollableDialog(YourDialog::IDD, pParent, SB_VERT) {}
 *
 * 3. OnVScroll��������´���
 *    VerticalScrollHandler(nSBCode, nPos);
 *    CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
 *
 * 4. OnSize��������´���
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