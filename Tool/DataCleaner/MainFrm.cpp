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
	mChooseDirBtn = new wxButton(this, IDC_CHOOSE_DIR_BTN, wxT("选择客户端目录"), wxPoint(510, 5), wxSize(120, 20));

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
	wxDirDialog dlg(this, wxT("请选择待清理资源的 三国客户端 目录"),
		wxT("D:\\"), wxDD_DIR_MUST_EXIST | wxDD_DEFAULT_STYLE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString clientDir = dlg.GetPath();
		if (clientDir.IsEmpty())
		{
			wxMessageBox(wxT("路径不能为空!"));
			return;
		}

		if (wxMessageBox(wxT("是否确定要清理该客户端的资源? 清理后无法恢复, 请谨慎操作!"), wxT("请确认"), wxYES_NO) != wxYES)
		{
			return;
		}

		mDirTextCtrl->SetValue(dlg.GetPath());
		mChooseDirBtn->Disable();

		// 执行清理资源
		DataCleanThread *thread = new DataCleanThread(dlg.GetPath(), mChooseDirBtn, mTextCtrl, mProgressCtrl);
		thread->Create();
		thread->Run();
	}
}