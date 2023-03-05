#pragma once

#include "Avatar.h"

/*
 * RightWindow中的子窗口, 用于编辑Avatar信息
 */
class CPlayerAnim;
class ModelObj;
class AvatarWindow : public wxWindow
{
public:
	AvatarWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
	virtual ~AvatarWindow();

protected:
	void SetAvatarComponent(Avatar::ComponentType ct);

protected:
	void OnButtonHat(wxCommandEvent &WXUNUSED(event));
	void OnButtonHair(wxCommandEvent &WXUNUSED(event));
	void OnButtonFace(wxCommandEvent &WXUNUSED(event));
	void OnButtonShoulder(wxCommandEvent &WXUNUSED(event));
	void OnButtonClothes(wxCommandEvent &WXUNUSED(event));
	void OnButtonWaistBand(wxCommandEvent &WXUNUSED(event));
	void OnButtonRightHand(wxCommandEvent &WXUNUSED(event));
	void OnButtonGlove(wxCommandEvent &WXUNUSED(event));
	void OnButtonLeftHand(wxCommandEvent &WXUNUSED(event));
	void OnButtonShield(wxCommandEvent &WXUNUSED(event));
	void OnButtonTrousers(wxCommandEvent &WXUNUSED(event));
	void OnButtonShoes(wxCommandEvent &WXUNUSED(event));

	DECLARE_EVENT_TABLE()
};