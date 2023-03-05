#pragma once

/*
 * ¶¯»­Ö¡¿ØÖÆ´°¿Ú
 */
class FrameWindow : public wxWindow
{
public:
	FrameWindow(wxWindow *parent, wxWindowID id);
	virtual ~FrameWindow();

public:
	void StartTimer();
	void StartTimer(int start, int end);

protected:
	void UpdateEndTotalLabel();
	void OnPrevNextButtonClicked(bool prev);

protected:
	void OnTimer(wxTimerEvent &event);

	void OnPrevButton(wxCommandEvent &WXUNUSED(event));
	void OnPlayPauseButton(wxCommandEvent &WXUNUSED(event));
	void OnNextButton(wxCommandEvent &WXUNUSED(event));
	void OnEnterButton(wxCommandEvent &WXUNUSED(event));

	void OnSlider(wxCommandEvent &WXUNUSED(event));
	DECLARE_EVENT_TABLE()

protected:
	wxStaticText *mStart;
	wxSlider *mSlider;
	wxStaticText *mEndTotal;

	wxButton *mPrevBtn;
	wxButton *mPlayPauseBtn;
	wxButton *mNextBtn;
	wxButton *mEnterBtn;

	wxTimer mTimer;

	int mStartFrameID;
	int mEndFrameID;
};