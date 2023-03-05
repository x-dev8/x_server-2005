#include "StdAfx.h"
#include "AvatarWindow.h"

#include "MainFrame.h"
#include "LeftWindow.h"
#include "MiddleWindow.h"
#include "RenderHelper.h"
#include "Utility.h"
#include "ModelObj.h"

BEGIN_EVENT_TABLE(AvatarWindow, wxWindow)
	EVT_BUTTON(IDC_AVATAR_BTN_HAT, AvatarWindow::OnButtonHat)
	EVT_BUTTON(IDC_AVATAR_BTN_HAIR, AvatarWindow::OnButtonHair)
	EVT_BUTTON(IDC_AVATAR_BTN_FACE, AvatarWindow::OnButtonFace)
	EVT_BUTTON(IDC_AVATAR_BTN_SHOULDER, AvatarWindow::OnButtonShoulder)
	EVT_BUTTON(IDC_AVATAR_BTN_CLOTHES, AvatarWindow::OnButtonClothes)
	EVT_BUTTON(IDC_AVATAR_BTN_WAISTBAND, AvatarWindow::OnButtonWaistBand)
	EVT_BUTTON(IDC_AVATAR_BTN_RIGHT_HAND, AvatarWindow::OnButtonRightHand)
	EVT_BUTTON(IDC_AVATAR_BTN_GLOVE, AvatarWindow::OnButtonGlove)
	EVT_BUTTON(IDC_AVATAR_BTN_LEFT_HAND, AvatarWindow::OnButtonLeftHand)
	EVT_BUTTON(IDC_AVATAR_BTN_SHIELD, AvatarWindow::OnButtonShield)
	EVT_BUTTON(IDC_AVATAR_BTN_TROUSERS, AvatarWindow::OnButtonTrousers)
	EVT_BUTTON(IDC_AVATAR_BTN_SHOES, AvatarWindow::OnButtonShoes)
END_EVENT_TABLE()

AvatarWindow::AvatarWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
	: wxWindow(parent, id, pos, size)
{
	wxStaticBox *box = new wxStaticBox(this, wxID_ANY, wxT("Avatar"));
	wxStaticBoxSizer *topSizer = new wxStaticBoxSizer(box, wxVERTICAL);
	this->SetSizer(topSizer);
	{
		wxGridBagSizer *sizer = new wxGridBagSizer(1, 1);
		topSizer->Add(sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL);

		wxButton *btn = NULL;
		btn = new wxButton(this, IDC_AVATAR_BTN_HAT, wxT("ñ��"), wxDefaultPosition, wxSize(36, -1));
		sizer->Add(btn, wxGBPosition(0, 2));

		btn = new wxButton(this, IDC_AVATAR_BTN_HAIR, wxT("ͷ��"), wxDefaultPosition, wxSize(36, -1));
		sizer->Add(btn, wxGBPosition(1, 2));

		btn = new wxButton(this, IDC_AVATAR_BTN_FACE, wxT("��"), wxDefaultPosition, wxSize(36, -1));
		sizer->Add(btn, wxGBPosition(2, 2));

		// �Ҽ�
		btn = new wxButton(this, IDC_AVATAR_BTN_SHOULDER, wxT("���"), wxDefaultPosition, wxSize(36, -1));
		sizer->Add(btn, wxGBPosition(3, 1));

		// ���
		btn = new wxButton(this, wxID_ANY, wxT(" "), wxDefaultPosition, wxSize(36, -1));
		sizer->Add(btn, wxGBPosition(3, 3));

		btn = new wxButton(this, IDC_AVATAR_BTN_CLOTHES, wxT("�·�"), wxDefaultPosition, wxSize(36, 36));
		sizer->Add(btn, wxGBPosition(4, 2), wxGBSpan(3, 1), wxEXPAND);

		btn = new wxButton(this, IDC_AVATAR_BTN_WAISTBAND, wxT("����"), wxDefaultPosition, wxSize(36, -1));
		btn->Enable(false);
		sizer->Add(btn, wxGBPosition(7, 2));

		{
			btn = new wxButton(this, IDC_AVATAR_BTN_RIGHT_HAND, wxT("����"), wxDefaultPosition, wxSize(36, -1));
			sizer->Add(btn, wxGBPosition(7, 0));

			btn = new wxButton(this, IDC_AVATAR_BTN_GLOVE, wxT("����"), wxDefaultPosition, wxSize(36, -1));
			sizer->Add(btn, wxGBPosition(7, 1));

			btn = new wxButton(this, IDC_AVATAR_BTN_LEFT_HAND, wxT("����"), wxDefaultPosition, wxSize(36, -1));
			sizer->Add(btn, wxGBPosition(7, 3));

			btn = new wxButton(this, IDC_AVATAR_BTN_SHIELD, wxT("����"), wxDefaultPosition, wxSize(36, -1));
			btn->Enable(false);
			sizer->Add(btn, wxGBPosition(7, 4));

			btn = new wxButton(this, IDC_AVATAR_BTN_TROUSERS, wxT("����"), wxDefaultPosition, wxSize(36, -1));
			btn->Enable(false);
			sizer->Add(btn, wxGBPosition(8, 2));
		}

		btn = new wxButton(this, IDC_AVATAR_BTN_SHOES, wxT("Ь��"), wxDefaultPosition, wxSize(36, -1));
		sizer->Add(btn, wxGBPosition(10, 2));
	}
	topSizer->Fit(this);
}

AvatarWindow::~AvatarWindow()
{

}

void AvatarWindow::SetAvatarComponent(Avatar::ComponentType ct)
{
	MainFrame *gMainFrame = dynamic_cast<MainFrame *> (GetParent()->GetParent());
	if (gMainFrame == NULL)
		return;

	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	wxString curFilePath = gMainFrame->GetLeftWindow()->GetCurSelFilePath();
	if (curFilePath.IsEmpty())
		return;

	ModelObj *component_obj = gMainFrame->GetRenderHelper()->AppendModelToCacheLink(curFilePath.mb_str());
	if (obj != NULL)
	{
		if (ct != Avatar::LeftHand && ct != Avatar::RightHand)
		{
			if (obj->model->GetMex()->GetSkeleton()->IsSameFormat(component_obj->model->GetMex()->GetSkeleton()))
			{
				// ֻ�й�����ͬ�ſ��Ի�װ, ��������
				obj->GetAvatar()->ChangeAvatarComponent(ct, component_obj);
			}
			else
			{
				wxMessageBox(wxT("��������ͬ, �޷���װ"));
			}
		}
		else
		{
			obj->GetAvatar()->ChangeAvatarComponent(ct, component_obj);
		}
	}
}

void AvatarWindow::OnButtonHat(wxCommandEvent &WXUNUSED(event))
{
	this->SetAvatarComponent(Avatar::Hat);
}

void AvatarWindow::OnButtonHair(wxCommandEvent &WXUNUSED(event))
{
	this->SetAvatarComponent(Avatar::Hair);
}

void AvatarWindow::OnButtonFace(wxCommandEvent &WXUNUSED(event))
{
	this->SetAvatarComponent(Avatar::Face);
}

void AvatarWindow::OnButtonShoulder(wxCommandEvent &WXUNUSED(event))
{
	this->SetAvatarComponent(Avatar::Shoulder);
}

void AvatarWindow::OnButtonClothes(wxCommandEvent &WXUNUSED(event))
{
	this->SetAvatarComponent(Avatar::Armour);
}

void AvatarWindow::OnButtonWaistBand(wxCommandEvent &WXUNUSED(event))
{
	//this->SetAvatarComponent(Avatar::WaistBand);
}

void AvatarWindow::OnButtonRightHand(wxCommandEvent &WXUNUSED(event))
{
	this->SetAvatarComponent(Avatar::RightHand);
}

void AvatarWindow::OnButtonGlove(wxCommandEvent &WXUNUSED(event))
{
	this->SetAvatarComponent(Avatar::Glove);
}

void AvatarWindow::OnButtonLeftHand(wxCommandEvent &WXUNUSED(event))
{
	this->SetAvatarComponent(Avatar::LeftHand);
}

void AvatarWindow::OnButtonShield(wxCommandEvent &WXUNUSED(event))
{
	//this->SetAvatarComponent(Avatar::Shield);
}

void AvatarWindow::OnButtonTrousers(wxCommandEvent &WXUNUSED(event))
{
	//SetAvatarComponent(Avatar::Trousers);
}

void AvatarWindow::OnButtonShoes(wxCommandEvent &WXUNUSED(event))
{
	this->SetAvatarComponent(Avatar::Shoes);
}