#pragma once

#define DATACLEANER_MAIN_FRM_STYLE		wxCAPTION | wxBORDER | wxCLOSE_BOX | wxCLIP_CHILDREN

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString &title);
	virtual ~MainFrame();

protected:
	void OnChooseDirButtonClick(wxCommandEvent &WXUNUSED(event));
	DECLARE_EVENT_TABLE()

protected:
	wxTextCtrl *mDirTextCtrl;
	wxButton *mChooseDirBtn;
	wxTextCtrl *mTextCtrl;
	wxGauge *mProgressCtrl;
};