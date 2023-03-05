#include "StdAfx.h"
#include "AnimationWindow.h"

#include "MainFrame.h"
#include "MiddleWindow.h"
#include "RenderHelper.h"
#include "ModelObj.h"
#include "NewAnimationDlg.h"
#include "FrameWindow.h"
#include "Utility.h"

#define GET_ANIMATION_WND_CHILD_WINDOWS()\
wxListBox *listBox = dynamic_cast<wxListBox *> (FindWindow(IDC_ANIM_WND_ANIM_LIST_BOX));\
wxCheckBox *lightTrackCB = dynamic_cast<wxCheckBox *> (FindWindow(IDC_ANIM_WND_LIGHT_TRACK_CHECK_BOX));\
wxTextCtrl *nameEdit = dynamic_cast<wxTextCtrl *> (FindWindow(IDC_ANIM_WND_NAME_EDIT));\
wxSpinCtrl *startSpin = dynamic_cast<wxSpinCtrl *> (FindWindow(IDC_ANIM_WND_START_SPIN));\
wxSpinCtrl *endSpin = dynamic_cast<wxSpinCtrl *> (FindWindow(IDC_ANIM_WND_END_SPIN));\
wxSpinCtrl *hitpointSpin = dynamic_cast<wxSpinCtrl *> (FindWindow(IDC_ANIM_WND_HIT_POINT_SPIN));\
wxSlider *slider = dynamic_cast<wxSlider *> (FindWindow(IDC_ANIM_WND_ONE_LOOP_TIME_SLIDER))

static const float ONE_LOOP_TIME_SCALES[11] =
{
	0.1, 0.2, 0.4, 0.6, 0.8,
	1.0,
	1.2, 1.4, 1.6, 1.8, 2.0
};

static int ONE_LOOP_TIME = 0;

BEGIN_EVENT_TABLE(AnimationWindow, wxWindow)
	EVT_LISTBOX(IDC_ANIM_WND_ANIM_LIST_BOX, AnimationWindow::OnEventListBox)

	EVT_BUTTON(IDC_ANIM_WND_ADD_BTN, AnimationWindow::OnButtonAdd)
	EVT_BUTTON(IDC_ANIM_WND_DEL_BTN, AnimationWindow::OnButtonDel)
	EVT_BUTTON(IDC_ANIM_WND_SAVE_ANI_BTN, AnimationWindow::OnButtonSaveAni)
	EVT_BUTTON(IDC_ANIM_WND_IMPORT_ANI_TEMP_BTN, AnimationWindow::OnButtonImportAniTemplate)
	EVT_BUTTON(IDC_ANIM_WND_EXPORT_ANI_TEMP_BTN, AnimationWindow::OnButtonExportAniTemplate)

	EVT_SLIDER(IDC_ANIM_WND_ONE_LOOP_TIME_SLIDER, AnimationWindow::OnSlider)
END_EVENT_TABLE()

AnimationWindow::AnimationWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
	: wxWindow(parent, id, pos, size)
{
	wxStaticBox *box = new wxStaticBox(this, wxID_ANY, wxT("Animation"));
	wxStaticBoxSizer *topSizer = new wxStaticBoxSizer(box, wxVERTICAL);
	this->SetSizer(topSizer);
	
	wxStaticText *totalLabel = new wxStaticText(this, IDC_ANIM_WND_TOTAL_FRM_STATIC, wxT("TotalFrame: 0"));
	topSizer->Add(totalLabel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxListBox *animListBox = new wxListBox(this, IDC_ANIM_WND_ANIM_LIST_BOX,
		wxDefaultPosition, wxSize(-1, 280));
	topSizer->Add(animListBox, 0, wxALIGN_RIGHT | wxGROW | wxALL, 5);

	wxCheckBox *cb = new wxCheckBox(this, IDC_ANIM_WND_LIGHT_TRACK_CHECK_BOX, wxT("光线追踪"));
	topSizer->Add(cb, 0, wxALIGN_RIGHT | wxALL, 5);

	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		topSizer->Add(hSizer, 0, wxALIGN_RIGHT | wxALL, 5);

		wxStaticText *nameLabel = new wxStaticText(this, wxID_STATIC, wxT("Name:"));
		hSizer->Add(nameLabel, 0, wxGROW | wxALL, 5);

		wxTextCtrl *nameEdit = new wxTextCtrl(this, IDC_ANIM_WND_NAME_EDIT,
			wxEmptyString, wxDefaultPosition, wxSize(180, -1));
		hSizer->Add(nameEdit, 0, wxGROW | wxALL, 5);
	}

	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		topSizer->Add(hSizer, 0, wxALIGN_RIGHT | wxALL, 5);

		wxStaticText *startLabel = new wxStaticText(this, wxID_STATIC, wxT("Start:"));
		hSizer->Add(startLabel, 0, wxGROW | wxALL, 5);

		wxSpinCtrl *startSpin = new wxSpinCtrl(this, IDC_ANIM_WND_START_SPIN,
			wxEmptyString, wxDefaultPosition, wxSize(180, -1));
		hSizer->Add(startSpin, 0, wxGROW | wxALL, 5);
	}

	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		topSizer->Add(hSizer, 0, wxALIGN_RIGHT | wxALL, 5);

		wxStaticText *endLabel = new wxStaticText(this, wxID_STATIC, wxT("End:"));
		hSizer->Add(endLabel, 0, wxGROW | wxALL, 5);

		wxSpinCtrl *endSpin = new wxSpinCtrl(this, IDC_ANIM_WND_END_SPIN,
			wxEmptyString, wxDefaultPosition, wxSize(180, -1));
		hSizer->Add(endSpin, 0, wxGROW | wxALL, 5);
	}

	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		topSizer->Add(hSizer, 0, wxALIGN_RIGHT | wxALL, 5);

		wxStaticText *startLabel = new wxStaticText(this, wxID_STATIC, wxT("HitPoint:"));
		hSizer->Add(startLabel, 0, wxGROW | wxALL, 5);

		wxSpinCtrl *hitpointSpin = new wxSpinCtrl(this, IDC_ANIM_WND_HIT_POINT_SPIN,
			wxEmptyString, wxDefaultPosition, wxSize(180, -1));
		hSizer->Add(hitpointSpin, 0, wxGROW | wxALL, 5);
	}

	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		topSizer->Add(hSizer, 0, wxALIGN_RIGHT | wxALL, 5);

		wxStaticText *speedLabel = new wxStaticText(this, wxID_STATIC, wxT("Speed:"));
		hSizer->Add(speedLabel, 0, wxGROW | wxALL, 5);

		wxSlider *oneLoopTimeSlider = new wxSlider(this, IDC_ANIM_WND_ONE_LOOP_TIME_SLIDER, 6, 0, 11, wxDefaultPosition,
			wxSize(120, -1), wxHORIZONTAL | wxSL_MIN_MAX_LABELS);
		hSizer->Add(oneLoopTimeSlider, 0, wxGROW | wxALL, 5);
	}

	wxStaticLine *line = new wxStaticLine(this);
	topSizer->Add(line, 0, wxGROW | wxALL, 5);

	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		topSizer->Add(hSizer, 0, wxALIGN_RIGHT | wxALL, 5);

		wxButton *addBtn = new wxButton(this, IDC_ANIM_WND_ADD_BTN, wxT("添加"), wxDefaultPosition, wxSize(60, 22));
		hSizer->Add(addBtn, 0, wxGROW | wxALL, 5);

		wxButton *delBtn = new wxButton(this, IDC_ANIM_WND_DEL_BTN, wxT("删除"), wxDefaultPosition, wxSize(60, 22));
		hSizer->Add(delBtn, 0, wxGROW | wxALL, 5);

		wxButton *saveBtn = new wxButton(this, IDC_ANIM_WND_SAVE_ANI_BTN, wxT("保存Ani"), wxDefaultPosition, wxSize(60, 22));
		hSizer->Add(saveBtn, 0, wxGROW | wxALL, 5);
	}

	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		topSizer->Add(hSizer, 0, wxALIGN_RIGHT | wxALL, 5);

		wxButton *importAniTempBtn = new wxButton(this, IDC_ANIM_WND_IMPORT_ANI_TEMP_BTN, wxT("导入Ani模板"), wxDefaultPosition, wxSize(90, 22));
		hSizer->Add(importAniTempBtn, 0, wxGROW | wxALL, 5);

		wxButton *exportAniTempBtn = new wxButton(this, IDC_ANIM_WND_EXPORT_ANI_TEMP_BTN, wxT("导出Ani模板"), wxDefaultPosition, wxSize(90, 22));
		hSizer->Add(exportAniTempBtn, 0, wxGROW | wxALL, 5);
	}

	topSizer->Fit(this);
}

AnimationWindow::~AnimationWindow()
{

}

void AnimationWindow::UpdateAnimationList()
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	MexCfg *mexCfg = obj->model->GetMexCfg();
	if (mexCfg == NULL)
		return;

	GET_ANIMATION_WND_CHILD_WINDOWS();

	if (ONE_LOOP_TIME == 0)
	{
		ONE_LOOP_TIME = obj->model->GetUpperBodyAnimTimeLine()->GetOneLoopTime();
	}

	listBox->Clear();
	for (int i = 0; i < mexCfg->m_sequences.m_vectorSequence.size(); ++i)
	{
		if (mexCfg->m_sequences.m_vectorSequence[i] != NULL)
		{
			listBox->Append(
				mexCfg->m_sequences.m_vectorSequence[i]->m_spAnimName.GetString(),
				new AnimationLBClientData(
					mexCfg->m_sequences.m_vectorSequence[i]->m_npHasLightTrack.GetNumber() == 1 ? true : false,
					mexCfg->m_sequences.m_vectorSequence[i]->m_spAnimName.GetString(),
					mexCfg->m_sequences.m_vectorSequence[i]->m_npStartFrameId.GetNumber(),
					mexCfg->m_sequences.m_vectorSequence[i]->m_npEndFrameId.GetNumber(),
					Utility_GetHitPoint(mexCfg->m_sequences.m_vectorSequence[i])
				));
		}
	}

	listBox->SetSelection(-1);

	// 设置总帧数
	wxStaticText *totalFrmStatic = dynamic_cast<wxStaticText *> (FindWindow(IDC_ANIM_WND_TOTAL_FRM_STATIC));
	wxString label = wxString::Format(wxT("TotalFrame: %d"), obj->GetFrameCount());
	totalFrmStatic->SetLabel(label);

	// 清空其它内容
	lightTrackCB->SetValue(false);
	nameEdit->SetValue(wxT(""));
	startSpin->SetValue(0);
	endSpin->SetValue(1);
	hitpointSpin->SetValue(0);

	slider->SetValue(6);
}

void AnimationWindow::OnEventListBox(wxCommandEvent &event)
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	MexCfg *mexCfg = obj->model->GetMexCfg();
	if (mexCfg == NULL)
		return;

	GET_ANIMATION_WND_CHILD_WINDOWS();

	int index = listBox->GetSelection();
	if (index == -1 || mexCfg->m_sequences.m_vectorSequence[index] == NULL)
		return;

	startSpin->SetRange(0, obj->GetFrameCount() - 1);
	endSpin->SetRange(0, obj->GetFrameCount() - 1);
	hitpointSpin->SetRange(0, obj->GetFrameCount() - 1);

	lightTrackCB->SetValue(mexCfg->m_sequences.m_vectorSequence[index]->m_npHasLightTrack.GetNumber());
	nameEdit->SetValue(mexCfg->m_sequences.m_vectorSequence[index]->m_spAnimName.GetString());
	startSpin->SetValue(mexCfg->m_sequences.m_vectorSequence[index]->m_npStartFrameId.GetNumber());
	endSpin->SetValue(mexCfg->m_sequences.m_vectorSequence[index]->m_npEndFrameId.GetNumber());
	hitpointSpin->SetValue(Utility_GetHitPoint(mexCfg->m_sequences.m_vectorSequence[index]));

	// 播放选中的Animation
	gMainFrame->GetRenderHelper()->PlayCurrentModelByAnimName(
		mexCfg->m_sequences.m_vectorSequence[index]->m_spAnimName.GetString());

	// 通知FrameWindow
	gMainFrame->GetFrameWindow()->StartTimer(
		mexCfg->m_sequences.m_vectorSequence[index]->m_npStartFrameId.GetNumber(),
		mexCfg->m_sequences.m_vectorSequence[index]->m_npEndFrameId.GetNumber());
}

void AnimationWindow::OnButtonAdd(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
	{
		wxMessageBox(wxT("请选选择一个模型"));
		return;
	}

	MexCfg *mexCfg = obj->model->GetMexCfg();
	if (mexCfg == NULL)
		return;

	wxListBox *listBox = dynamic_cast<wxListBox *> (FindWindow(IDC_ANIM_WND_ANIM_LIST_BOX));

	int startFrame = 0;
	int endFrame = 0;
	obj->GetFrameRange(&startFrame, &endFrame);
	NewAnimationDlg dlg(this, wxID_ANY, wxT("新建Animation"), startFrame, endFrame);
	if (dlg.ShowModal() == wxID_OK)
	{
		std::string name = dlg.GetAnimName();
		int start = dlg.GetStartFrame();
		int end = dlg.GetEndFrame();
		int hitpoint = dlg.GetHitPoint();

		MexCfgSequence *anim = MeNew MexCfgSequence;
		anim->m_spAnimName.SetValue(name.c_str());
		anim->m_npStartFrameId.SetNumber(start);
		anim->m_npEndFrameId.SetNumber(end);
		Utility_AddHitPoint(anim, hitpoint);
		mexCfg->m_sequences.m_vectorSequence.push_back(anim);

		// 刷新动作列表
		this->UpdateAnimationList();
	}
}

void AnimationWindow::OnButtonDel(wxCommandEvent &WXUNUSED(event))
{
	wxListBox *listBox = dynamic_cast<wxListBox *> (FindWindow(IDC_ANIM_WND_ANIM_LIST_BOX));

	int selection = listBox->GetSelection();
	if (selection == -1)
	{
		wxMessageBox(wxT("请选择要删除的动作"));
		return;
	}

	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	MexCfg *mexCfg = obj->model->GetMexCfg();
	if (mexCfg == NULL)
		return;

	const char *itemNeedDel = mexCfg->m_sequences.m_vectorSequence[selection]->m_spAnimName.GetString();
	for (std::vector<MexCfgSequence *>::iterator iter = mexCfg->m_sequences.m_vectorSequence.begin();
		iter != mexCfg->m_sequences.m_vectorSequence.end();
		++iter)
	{
		if (stricmp(itemNeedDel, (*iter)->m_spAnimName.GetString()) == 0)
		{
			mexCfg->m_sequences.m_vectorSequence.erase(iter);
			break;	
		}
	}

	// 删除后, 刷新Animation列表
	this->UpdateAnimationList();
}

void AnimationWindow::OnButtonSaveAni(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	MexCfg *mexCfg = obj->model->GetMexCfg();
	if (mexCfg == NULL)
		return;

	GET_ANIMATION_WND_CHILD_WINDOWS();
	
	int index = listBox->GetSelection();
	if (index != -1 && mexCfg->m_sequences.m_vectorSequence[index] != NULL)
	{
		mexCfg->m_sequences.m_vectorSequence[index]->m_npHasLightTrack.SetNumber(lightTrackCB->GetValue());
		mexCfg->m_sequences.m_vectorSequence[index]->m_spAnimName.SetString(nameEdit->GetValue().mb_str());
		mexCfg->m_sequences.m_vectorSequence[index]->m_npStartFrameId.SetNumber(startSpin->GetValue());
		mexCfg->m_sequences.m_vectorSequence[index]->m_npEndFrameId.SetNumber(endSpin->GetValue());
		Utility_SetHitPoint(mexCfg->m_sequences.m_vectorSequence[index], hitpointSpin->GetValue());
	}

	// 保存Ani
	wxString folder = obj->GetFileFolder();
	wxFileName fn(obj->GetFileName());

	wxString mexAniFilePath = folder + wxT("\\") + fn.GetName() + wxT(".ani");
	BOOL ret = mexCfg->SaveToFile(mexAniFilePath.mb_str());
	if (!ret)
	{
		wxMessageBox(wxT("保存ANI文件失败, 目标文件为只读或不存在!"));
	}

	// 刷新ListBox
	this->UpdateAnimationList();
}

void AnimationWindow::OnButtonImportAniTemplate(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	MexCfg *mexCfg = obj->model->GetMexCfg();
	if (mexCfg == NULL)
		return;

	wxListBox *listBox = dynamic_cast<wxListBox *> (FindWindow(IDC_ANIM_WND_ANIM_LIST_BOX));

	wxString curSeqName;
	int curSeq = listBox->GetSelection();
	if (curSeq != -1)
		curSeqName = mexCfg->m_sequences.m_vectorSequence[curSeq]->m_spAnimName.GetString();

	wxFileDialog dlg(this, wxT("导入Ani模板"), wxEmptyString, wxEmptyString,
		SEQ_FILE_WILDCARD, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString &path = dlg.GetPath();

		// 清空并根据导入的内容填充MexCfg中的数据
		for (int i = 0; i < mexCfg->m_sequences.m_vectorSequence.size(); ++i)
		{
			// 此句最好写在MexCfgSequences的析构函数中
			mexCfg->m_seqMapStrToIdMgr.UnRegister(mexCfg->m_sequences.m_vectorSequence[i]->m_spAnimName.GetString());

			MeDelete mexCfg->m_sequences.m_vectorSequence[i];
			mexCfg->m_sequences.m_vectorSequence[i] = NULL;
		}
		mexCfg->m_sequences.m_vectorSequence.clear();

		FILE *fp = NULL;
		if (fopen_s(&fp, path.mb_str(), "rt") != 0)
			return;
		
		char temp[64] = {0};
		char name[32] = {0};
		int start, end, hitPoint;
		MexCfgSequence *seq = NULL;
		while (fgets(temp, 64, fp) != NULL)
		{
			sscanf(temp, SEQ_FILE_LINE_FORMAT, name, &start, &end, &hitPoint);

			seq = MeNew MexCfgSequence;
			seq->m_spAnimName.SetString(name);
			seq->m_npStartFrameId.SetNumber(start);
			seq->m_npEndFrameId.SetNumber(end);
			Utility_AddHitPoint(seq, hitPoint);
			mexCfg->m_sequences.m_vectorSequence.push_back(seq);
			mexCfg->m_seqMapStrToIdMgr.Register(name, seq);
		}
		fclose(fp);

		// 刷新动作列表
		this->UpdateAnimationList();

		// 重新播放动作
		if (!curSeqName.empty())
			obj->model->PlayAnimByName(curSeqName, 0);
	}
}

void AnimationWindow::OnButtonExportAniTemplate(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	MexCfg *mexCfg = obj->model->GetMexCfg();
	if (mexCfg == NULL)
		return;

	wxFileDialog dlg(this, wxT("导出Ani模板"), wxEmptyString, wxEmptyString,
		SEQ_FILE_WILDCARD, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString &path = dlg.GetPath();

		FILE *fp = NULL;
		if (fopen_s(&fp, path.mb_str(), "wt") != 0)
			return;

		char temp[64 + 1] = {0};
		for (int i = 0; i < mexCfg->m_sequences.m_vectorSequence.size(); ++i)
		{
			sprintf_s(temp, 64, SEQ_FILE_LINE_FORMAT,
				mexCfg->m_sequences.m_vectorSequence[i]->m_spAnimName.GetString(),
				mexCfg->m_sequences.m_vectorSequence[i]->m_npStartFrameId.GetNumber(),
				mexCfg->m_sequences.m_vectorSequence[i]->m_npEndFrameId.GetNumber(),
				mexCfg->m_sequences.m_vectorSequence[i]->m_npRealHitPoint.GetNumber());
			fputs(temp, fp);
		}
		fclose(fp);
	}
}

void AnimationWindow::OnSlider(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	GET_ANIMATION_WND_CHILD_WINDOWS();
	if (slider == NULL)
		return;

	int n = slider->GetValue();
	int oneLoopTime = ONE_LOOP_TIME * ONE_LOOP_TIME_SCALES[n];
	obj->model->GetUpperBodyAnimTimeLine()->SetOneLoopTime(oneLoopTime);

	// 通知FrameWindow使之生效
	gMainFrame->GetFrameWindow()->StartTimer();
}