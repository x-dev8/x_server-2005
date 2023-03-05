#pragma once

/*
 * 中间窗口, 用于渲染模型
 */
class MeCamera;
class RenderHelper;
class MiddleWindow : public wxWindow
{
public:
	MiddleWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
	virtual ~MiddleWindow();

public:
	RenderHelper *GetRenderHelper() { return mRenderHelper; }
	
public:
	void Render();

protected:
	void OnSize(wxSizeEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnEraseBackground(wxEraseEvent &event);
	void OnIdle(wxIdleEvent &event);

	void OnRButtonDown(wxMouseEvent &event);
	void OnRButtonUp(wxMouseEvent &event);
	void OnMouseMotion(wxMouseEvent &event);

	DECLARE_EVENT_TABLE()

protected:
	RenderHelper *mRenderHelper;

	bool mIsLBtnDown;
	bool mIsRBtnDown;
	wxPoint mOldRPos;
};