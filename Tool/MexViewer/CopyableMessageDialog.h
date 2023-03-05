#pragma once

/*
 * 可复制的信息提示对话框
 */
class CopyableMessageDialog : public wxDialog
{
public:
	CopyableMessageDialog(wxWindow *parent, wxWindowID id, const wxString &title,
		const wxSize &size, const wxArrayString &msgLines);
	virtual ~CopyableMessageDialog();

public:

protected:
	DECLARE_EVENT_TABLE()

protected:
	wxTextCtrl *mTextCtrl;
};