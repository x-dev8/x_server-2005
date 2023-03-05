#pragma once

#include "wx/dir.h"
#include "wx/filename.h"
#include "wx/textfile.h"

class DataCleanThread : public wxThread
{
public:
	DataCleanThread(const wxString &dir, wxButton *button, wxTextCtrl *textCtrl, wxGauge *gauge);

public:
	virtual void * Entry();

private:
	wxString mClientDir;
	wxButton *mButton;
	wxTextCtrl *mTextCtrl;
	wxGauge *mProgressCtrl;	
};