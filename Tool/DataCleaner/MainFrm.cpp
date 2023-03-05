#include "StdAfx.h"
#include "MainFrm.h"
#include "DataCleanThread.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(IDC_CHOOSE_DIR_BTN, MainFrame::OnChooseDirButtonClick)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString &title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(640, 480), DATACLEANER_MAIN_FRM_STYLE)
{
	mDirTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(5, 5),
		wxSize(500, 20), wxTE_READONLY);
	mChooseDirBtn = new wxButton(this, IDC_CHOOSE_DIR_BTN, wxT("ѡ��ͻ���Ŀ¼"), wxPoint(510, 5), wxSize(120, 20));

	mTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(5, 30),
		wxSize(500, 450), wxTE_RICH | wxTE_READONLY | wxTE_MULTILINE);

	mProgressCtrl = new wxGauge(this, wxID_ANY, 100, wxPoint(510, 30), wxSize(120, 450), wxGA_VERTICAL | wxGA_SMOOTH);

	Center();
}

MainFrame::~MainFrame()
{

}

void MainFrame::OnChooseDirButtonClick(wxCommandEvent &WXUNUSED(event))
{
	wxDirDialog dlg(this, wxT("��ѡ���������Դ�� �����ͻ��� Ŀ¼"),
		wxT("D:\\"), wxDD_DIR_MUST_EXIST | wxDD_DEFAULT_STYLE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString clientDir = dlg.GetPath();
		if (clientDir.IsEmpty())
		{
			wxMessageBox(wxT("·������Ϊ��!"));
			return;
		}

		if (wxMessageBox(wxT("�Ƿ�ȷ��Ҫ����ÿͻ��˵���Դ? ������޷��ָ�, ���������!"), wxT("��ȷ��"), wxYES_NO) != wxYES)
		{
			return;
		}

		mDirTextCtrl->SetValue(dlg.GetPath());
		mChooseDirBtn->Disable();

		// ִ��������Դ
		DataCleanThread *thread = new DataCleanThread(dlg.GetPath(), mChooseDirBtn, mTextCtrl, mProgressCtrl);
		thread->Create();
		thread->Run();
	}
}