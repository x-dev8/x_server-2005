#pragma once

/*
 * MewViewerӦ�ó���Application��
 */
class MexViewerApp : public wxApp
{
public:
	wxString GetExeFolder();

public:
	virtual bool OnInit();
	virtual int OnExit();

public:
	void OnActiveApp(wxActivateEvent &event);

	DECLARE_EVENT_TABLE()

protected:

};