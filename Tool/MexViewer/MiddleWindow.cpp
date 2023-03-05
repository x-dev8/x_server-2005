#include "StdAfx.h"
#include "MiddleWindow.h"

#include "RenderHelper.h"
#include "ModelObj.h"
#include "MiddleWindowDropTarget.h"
#include "MainFrame.h"
#include "RightWindow.h"

BEGIN_EVENT_TABLE(MiddleWindow, wxWindow)
	EVT_SIZE(MiddleWindow::OnSize)
	EVT_PAINT(MiddleWindow::OnPaint)
	EVT_ERASE_BACKGROUND(MiddleWindow::OnEraseBackground)
	EVT_IDLE(MiddleWindow::OnIdle)

	EVT_RIGHT_DOWN(MiddleWindow::OnRButtonDown)
	EVT_RIGHT_UP(MiddleWindow::OnRButtonUp)
	EVT_MOTION(MiddleWindow::OnMouseMotion)
END_EVENT_TABLE()

MiddleWindow::MiddleWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
	: wxWindow(parent, id, pos, size), mIsRBtnDown(false)
{
	mRenderHelper = NULL;
	this->SetDropTarget(new MiddleWindowDropTarget(this));
}

MiddleWindow::~MiddleWindow()
{
	SAFE_DELETE(mRenderHelper);
}

void MiddleWindow::Render()
{
	if (mRenderHelper != NULL)
		mRenderHelper->Render();
}

void MiddleWindow::OnPaint(wxPaintEvent &event)
{

}

void MiddleWindow::OnSize(wxSizeEvent &event)
{
	HWND hWnd = (HWND) this->GetHWND();
	wxSize wndSize = event.GetSize();

	std::string oldModelPath;
	if (mRenderHelper != NULL)
	{
		// 如果当前模型存在, 则保存模型文件路径
		ModelObj *obj = mRenderHelper->GetCurrentModel();
		if (obj != NULL)
			oldModelPath = obj->GetFilePath();
	}

	// 重新创建RenderHelper	
	SAFE_DELETE(mRenderHelper);
	if (wndSize.GetWidth() > 0 && wndSize.GetHeight() > 0)
		mRenderHelper = new RenderHelper(hWnd, wndSize.GetWidth(), wndSize.GetHeight());

	// 重新加载当前模型
	if (!oldModelPath.empty())
	{
		mRenderHelper->SetCurrentModel(oldModelPath);
	}
}

void MiddleWindow::OnEraseBackground(wxEraseEvent &event)
{

}

void MiddleWindow::OnIdle(wxIdleEvent &event)
{
	if (wxTheApp->IsActive())
	{
		event.RequestMore(true);
		Render();
	}
}

void MiddleWindow::OnRButtonDown(wxMouseEvent &event)
{
	mIsRBtnDown = true;
	mOldRPos = event.GetPosition();
}

void MiddleWindow::OnRButtonUp(wxMouseEvent &event)
{
	mIsRBtnDown = false;
}

void MiddleWindow::OnMouseMotion(wxMouseEvent &event)
{
	if (event.Dragging())
	{
		if (mIsRBtnDown)
		{
			wxPoint pos = event.GetPosition();
			wxPoint delta = pos - mOldRPos;
			{
				if (event.AltDown())
				{
					// 旋转摄像机
					mRenderHelper->AdjustCamera(delta, true);
				}
				else if (event.ControlDown())
				{
					// 旋转模型及辅助网格
					mRenderHelper->RotateCurrentModelAndGrid(delta);
				}
				else if (event.ShiftDown())
				{
					// 移动模型
					mRenderHelper->MoveCurrentModel(delta);
				}
				else
				{
					// 移动摄像机
					mRenderHelper->AdjustCamera(delta, false);
				}
			}
			mOldRPos = pos;
		}
	}
}