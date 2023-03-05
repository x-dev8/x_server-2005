#include "StdAfx.h"
#include "CopyableMessageDialog.h"

BEGIN_EVENT_TABLE(CopyableMessageDialog, wxDialog)

END_EVENT_TABLE()

CopyableMessageDialog::CopyableMessageDialog(wxWindow *parent, wxWindowID id, const wxString &title,
	const wxSize &size, const wxArrayString &msgLines) : wxDialog(parent, id, title, wxDefaultPosition, size)
{
	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(topSizer);
	this->Center();

	mTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, size, wxTE_RICH | wxTE_READONLY | wxTE_MULTILINE);
	for (int i = 0; i < msgLines.GetCount(); ++i)
		mTextCtrl->AppendText(msgLines[i]);
	topSizer->Add(mTextCtrl, 0, wxALL, 5);

	topSizer->Fit(this);
}

CopyableMessageDialog::~CopyableMessageDialog()
{

}