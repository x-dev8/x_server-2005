#pragma once

/*
 * �ɸ��Ƶ���Ϣ��ʾ�Ի���
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