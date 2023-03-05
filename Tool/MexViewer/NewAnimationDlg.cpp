#include "StdAfx.h"
#include "NewAnimationDlg.h"

#include "MainFrame.h"
#include "MiddleWindow.h"
#include "RenderHelper.h"
#include "ModelObj.h"

#define GET_NEW_ANIMATION_DIALOG_CHILD_WINDOWS()\
wxTextCtrl *nameEdit = dynamic_cast<wxTextCtrl *> (FindWindow(IDC_NEW_ANIM_DLG_NAME_EDIT));\
wxSpinCtrl *startSpin = dynamic_cast<wxSpinCtrl *> (FindWindow(IDC_NEW_ANIM_DLG_START_SPIN));\
wxSpinCtrl *endSpin = dynamic_cast<wxSpinCtrl *> (FindWindow(IDC_NEW_ANIM_DLG_END_SPIN));\
wxSpinCtrl *hitpointSpin = dynamic_cast<wxSpinCtrl *> (FindWindow(IDC_NEW_ANIM_DLG_HIT_POINT_SPIN))

BEGIN_EVENT_TABLE(NewAnimationDlg, wxDialog)
	EVT_BUTTON(wxID_OK, NewAnimationDlg::OnButtonOK)
	EVT_BUTTON(wxID_CANCEL, NewAnimationDlg::OnButtonCancel)
END_EVENT_TABLE()

NewAnimationDlg::NewAnimationDlg(wxWindow *parent, wxWindowID id, const wxString &title, int start, int end)
	: wxDialog(parent, id, title)
{
	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(topSizer);
	this->Center();

	mStartFrame = start;
	mEndFrame = end;
	mHitPoint = start;

	wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxStaticText *desc = new wxStaticText(this, wxID_STATIC, NEW_ANIMATION_DLG_DESC);
	boxSizer->Add(desc, 0, wxALIGN_LEFT | wxALL, 5);

	wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(hSizer, 0, wxGROW | wxALL, 5);
	{
		wxStaticText *nameLabel = new wxStaticText(this, wxID_STATIC, wxT("动 画 名:"));
		hSizer->Add(nameLabel, 0, wxGROW | wxALL, 5);

		wxTextCtrl *nameEdit = new wxTextCtrl(this, IDC_NEW_ANIM_DLG_NAME_EDIT);
		hSizer->Add(nameEdit, 0, wxGROW | wxALL, 5);
	}

	hSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(hSizer, 0, wxGROW | wxALL, 5);
	{
		wxStaticText *startLabel = new wxStaticText(this, wxID_STATIC, wxT("开 始 帧:"));
		hSizer->Add(startLabel, 0, wxGROW | wxALL, 5);

		wxSpinCtrl *startSpin = new wxSpinCtrl(this, IDC_NEW_ANIM_DLG_START_SPIN);
		startSpin->SetRange(start, end);
		startSpin->SetValue(start);
		hSizer->Add(startSpin, 0, wxGROW | wxALL, 5);

		wxStaticText *endLabel = new wxStaticText(this, wxID_STATIC, wxT("结 束 帧:"));
		hSizer->Add(endLabel, 0, wxGROW | wxALL, 5);

		wxSpinCtrl *endSpin = new wxSpinCtrl(this, IDC_NEW_ANIM_DLG_END_SPIN);
		endSpin->SetRange(start, end);
		endSpin->SetValue(end);
		hSizer->Add(endSpin, 0, wxGROW | wxALL, 5);
	}

	hSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(hSizer, 0, wxGROW | wxALL, 5);
	{
		wxStaticText *hitpointLabel = new wxStaticText(this, wxID_STATIC, wxT("HitPoint:"));
		hSizer->Add(hitpointLabel, 0, wxGROW | wxALL, 5);

		wxSpinCtrl *hitpointSpin = new wxSpinCtrl(this, IDC_NEW_ANIM_DLG_HIT_POINT_SPIN);
		hitpointSpin->SetRange(start, end);
		hSizer->Add(hitpointSpin, 0, wxGROW | wxALL, 5);
	}

	wxStaticLine *line = new wxStaticLine(this);
	topSizer->Add(line, 0, wxGROW | wxALL, 5);

	wxBoxSizer *okCancelSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(okCancelSizer, 0, wxALIGN_RIGHT | wxALL, 5);
	{
		wxButton *ok = new wxButton(this, wxID_OK, wxT("确定"));
		okCancelSizer->Add(ok, 0, wxGROW | wxALL, 5);

		wxButton *cancel = new wxButton(this, wxID_CANCEL, wxT("取消"));
		okCancelSizer->Add(cancel, 0, wxGROW | wxALL, 5);
	}
}

NewAnimationDlg::~NewAnimationDlg()
{

}

bool NewAnimationDlg::Validate()
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return false;

	MexCfg *mexCfg = obj->model->GetMexCfg();
	if (mexCfg == NULL)
		return false;

	// 检查名字是否已存在
	for (int i = 0; i < mexCfg->m_sequences.m_vectorSequence.size(); ++i)
	{
		if (mexCfg->m_sequences.m_vectorSequence[i] != NULL)
		{
			wxString itemText = mexCfg->m_sequences.m_vectorSequence[i]->m_spAnimName.GetString();
			if (mName == itemText)
			{
				wxMessageBox(wxT("Animation的名字已存在, 请重新输入"));
				return false;
			}
		}
	}

	if (mName.empty())
	{
		wxMessageBox(wxT("Animation名不能为空"));
		return false;
	}
	else if (mStartFrame >= mEndFrame)
	{
		wxMessageBox(wxT("开始帧只能小于结束帧, 请重新输入"));
		return false;
	}
	return true;
}

bool NewAnimationDlg::TransferDataFromWindow()
{
	GET_NEW_ANIMATION_DIALOG_CHILD_WINDOWS();

	mName = nameEdit->GetValue();
	mStartFrame = startSpin->GetValue();
	mEndFrame = endSpin->GetValue();
	mHitPoint = hitpointSpin->GetValue();
	return true;
}

bool NewAnimationDlg::TransferDataToWindow()
{
	GET_NEW_ANIMATION_DIALOG_CHILD_WINDOWS();

	nameEdit->SetValue(mName);
	startSpin->SetValue(mStartFrame);
	endSpin->SetValue(mEndFrame);
	hitpointSpin->SetValue(mHitPoint);
	return true;
}

void NewAnimationDlg::OnButtonOK(wxCommandEvent &event)
{
	if (TransferDataFromWindow() && Validate())
		this->EndModal(wxID_OK);
}

void NewAnimationDlg::OnButtonCancel(wxCommandEvent &event)
{
	this->EndModal(wxID_CANCEL);
}