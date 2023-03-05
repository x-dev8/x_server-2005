#pragma once

#define NEW_ANIMATION_DLG_DESC		wxT("��������������Animation������, ��ʼ�����֡�Ȳ���")

/*
 * �½�Animation�Ի���
 */
class NewAnimationDlg : public wxDialog
{
public:
	NewAnimationDlg(wxWindow *parent, wxWindowID id, const wxString &title,
		int start, int end);
	virtual ~NewAnimationDlg();

public:
	/*
	 * ��ȡ������
	 */
	const wxString & GetAnimName() const { return mName; }

	/*
	 * ��ȡ������ʼ֡
	 */
	int GetStartFrame() const { return mStartFrame; }

	/*
	 * ��ȡ��������֡
	 */
	int GetEndFrame() const { return mEndFrame; }

	/*
	 * ��ȡHit Point
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