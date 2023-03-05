#pragma once

#define NEW_ANIMATION_DLG_DESC		wxT("请在下面输入新Animation的名字, 开始与结束帧等参数")

/*
 * 新建Animation对话框
 */
class NewAnimationDlg : public wxDialog
{
public:
	NewAnimationDlg(wxWindow *parent, wxWindowID id, const wxString &title,
		int start, int end);
	virtual ~NewAnimationDlg();

public:
	/*
	 * 获取动作名
	 */
	const wxString & GetAnimName() const { return mName; }

	/*
	 * 获取动作开始帧
	 */
	int GetStartFrame() const { return mStartFrame; }

	/*
	 * 获取动作结束帧
	 */
	int GetEndFrame() const { return mEndFrame; }

	/*
	 * 获取Hit Point
	 */
	int GetHitPoint() const { return mHitPoint; }

protected:
	virtual bool Validate();
	virtual bool TransferDataFromWindow();
	virtual bool TransferDataToWindow();

protected:
	void OnButtonOK(wxCommandEvent &event);
	void OnButtonCancel(wxCommandEvent &event);

	DECLARE_EVENT_TABLE()

protected:
	wxString mName;
	int mStartFrame;
	int mEndFrame;
	int mHitPoint;
};