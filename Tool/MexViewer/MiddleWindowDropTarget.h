#pragma once

#include "RenderHelper.h"
#include "MiddleWindow.h"

/*
 * MiddleWindow���Ϸ��ļ�ʵ��
 */
class RenderHelper;
class MiddleWindowDropTarget : public wxFileDropTarget
{
public:
	MiddleWindowDropTarget(MiddleWindow *owner) { mOwner = owner; }

	virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &filenames)
	{
		if (filenames.GetCount() > 0)
		{
			mOwner->GetRenderHelper()->SetCurrentModel(filenames[0]);
		}
		return true;
	}

protected:
	MiddleWindow *mOwner;
};