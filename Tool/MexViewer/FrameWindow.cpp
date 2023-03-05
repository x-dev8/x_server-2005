#include "StdAfx.h"
#include "FrameWindow.h"

#include "ModelObj.h"
#include "MainFrame.h"
#include "Utility.h"

BEGIN_EVENT_TABLE(FrameWindow, wxWindow)
	EVT_TIMER(MEXVIEWER_FRAME_WND_TIMER_ID, FrameWindow::OnTimer)

	EVT_BUTTON(IDC_FRAME_WND_PREV_BTN, FrameWindow::OnPrevButton)
	EVT_BUTTON(IDC_FRAME_WND_PLAY_PAUSE_BTN, FrameWindow::OnPlayPauseButton)
	EVT_BUTTON(IDC_FRAME_WND_NEXT_BTN, FrameWindow::OnNextButton)
	EVT_BUTTON(IDC_FRAME_WND_ENTER_FRM_BTN, FrameWindow::OnEnterButton)

	EVT_SLIDER(IDC_FRAME_WND_SLIDER, FrameWindow::OnSlider)
END_EVENT_TABLE()

FrameWindow::FrameWindow(wxWindow *parent, wxWindowID id)
	: wxWindow(parent, id), mTimer(this, MEXVIEWER_FRAME_WND_TIMER_ID),
	mStartFrameID(0), mEndFrameID(0)
{
	wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(hSizer);
	{
		mStart = new wxStaticText(this, wxID_ANY, wxT("0"));
		hSizer->Add(mStart, 0, wxGROW | wxALL, 6);

		mSlider = new wxSlider(this, IDC_FRAME_WND_SLIDER, 0, 0, 100,
			wxDefaultPosition, wxSize(320, -1));
		hSizer->Add(mSlider, 0, wxGROW | wxALL, 6);

		mEndTotal = new wxStaticText(this, wxID_ANY, wxT("0/100"));
		hSizer->Add(mEndTotal, 0, wxGROW | wxALL, 6);

		mPrevBtn = new wxButton(this, IDC_FRAME_WND_PREV_BTN, wxT("<"));
		hSizer->Add(mPrevBtn, 0, wxGROW | wxALL, 1);

		mPlayPauseBtn = new wxButton(this, IDC_FRAME_WND_PLAY_PAUSE_BTN, wxT("Play"));
		hSizer->Add(mPlayPauseBtn, 0, wxGROW | wxALL, 1);

		mNextBtn = new wxButton(this, IDC_FRAME_WND_NEXT_BTN, wxT(">"));
		hSizer->Add(mNextBtn, 0, wxGROW | wxALL, 1);

		mEnterBtn = new wxButton(this, IDC_FRAME_WND_ENTER_FRM_BTN, wxT("Goto"));
		hSizer->Add(mEnterBtn, 0, wxGROW | wxALL, 1);
	}
	hSizer->Fit(this);
}

FrameWindow::~FrameWindow()
{

}

void FrameWindow::StartTimer()
{
	this->StartTimer(mStartFrameID, mEndFrameID);
}

void FrameWindow::StartTimer(int start, int end)
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	mStartFrameID = start;
	mEndFrameID = end;

	wxString tempString = wxString::Format(wxT("%d"), mStartFrameID);
	mStart->SetLabel(tempString);

	mSlider->SetRange(mStartFrameID, mEndFrameID);
	mSlider->SetValue(mStartFrameID);
	if (mTimer.IsRunning())
	{
		mTimer.Stop();
	}
	wxString endTotal = wxString::Format(wxT("%d/%d"), mStartFrameID, mEndFrameID);
	mEndTotal->SetLabel(endTotal);

	mPlayPauseBtn->SetLabel(wxT("Pause"));

	obj->model->SetFrameID(mStartFrameID);

	int time = obj->model->GetUpperBodyAnimTimeLine()->GetOneLoopTime() / (float) 200.0f;
	mTimer.Start(time);
}

void FrameWindow::UpdateEndTotalLabel()
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	wxString endTotal = wxString::Format(wxT("%d/%d"), obj->model->GetFrameId(), mEndFrameID);
	mEndTotal->SetLabel(endTotal);
}

void FrameWindow::OnPrevNextButtonClicked(bool prev)
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	int curFrame = mSlider->GetValue();
	if (!prev)
		curFrame += 2;
	if (curFrame > obj->model->GetEndFrameId())
		curFrame = obj->model->GetEndFrameId();

	obj->SetPause(true, curFrame);
	mSlider->SetValue(curFrame);

	this->UpdateEndTotalLabel();
}

void FrameWindow::OnTimer(wxTimerEvent &event)
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	mSlider->SetValue(obj->model->GetFrameId());
	this->UpdateEndTotalLabel();
}

void FrameWindow::OnPrevButton(wxCommandEvent &WXUNUSED(event))
{
	this->OnPrevNextButtonClicked(true);
}

void FrameWindow::OnPlayPauseButton(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	wxString curLabel = mPlayPauseBtn->GetLabel();
	if (curLabel == wxT("Pause"))
	{
		mPlayPauseBtn->SetLabel(wxT("Play"));

		// 暂停播放
		obj->SetPause(true, obj->model->GetFrameId());
	}
	else
	{
		mPlayPauseBtn->SetLabel(wxT("Pause"));

		// 恢复播放
		obj->SetPause(false, obj->model->GetFrameId());

		this->StartTimer(
			obj->model->GetStartFrameID(),
			obj->model->GetEndFrameId());
	}
}

void FrameWindow::OnNextButton(wxCommandEvent &WXUNUSED(event))
{
	this->OnPrevNextButtonClicked(false);
}

void FrameWindow::OnEnterButton(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	wxNumberEntryDialog dlg(this, wxT("请输入需要跳转到的帧数:"), wxT("帧数"), wxT("输入对话框"),
		0, obj->model->GetStartFrameID(), obj->model->GetEndFrameId() - 1);
	if (dlg.ShowModal() == wxID_OK)
	{
		obj->SetPause(true, dlg.GetValue() + 1);
		this->UpdateEndTotalLabel();
	}
}

void FrameWindow::OnSlider(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	if (mTimer.IsRunning())
		mTimer.Stop();

	int curFrame = mSlider->GetValue();
	curFrame += mStartFrameID;
	obj->SetPause(true, curFrame);
	
	this->UpdateEndTotalLabel();
}