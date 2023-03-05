#include "StdAfx.h"
#include "LeftWindow.h"

#include "wx/filename.h"
#include "wx/clipbrd.h"

#include "MainFrame.h"
#include "MiddleWindow.h"
#include "RightWindow.h"
#include "RenderHelper.h"
#include "Utility.h"
#include "ModelConfigWindow.h"

BEGIN_EVENT_TABLE(LeftWindow, wxWindow)
	EVT_MENU(IDC_LEFT_WND_MENU_COPY_FILENAME, LeftWindow::OnMenuItemCopyFilename)
	EVT_MENU(IDC_LEFT_WND_MENU_FILE_RENAME, LeftWindow::OnMenuItemFileRename)
	EVT_MENU(IDC_LEFT_WND_MENU_BROWSER_FILE, LeftWindow::OnMenuItemBrowserFile)

	EVT_SIZE(LeftWindow::OnSize)
END_EVENT_TABLE()

LeftWindow::LeftWindow(wxWindow *parent, wxWindowID id,
					   const wxPoint &pos, const wxSize &size, const wxString &defaultFolder)
	: wxWindow(parent, id, pos, size)
{
	mDirCtrl = new wxGenericDirCtrl(this, IDC_LEFT_WND_DIR_CTRL, defaultFolder,
		wxPoint(0, 0), size, wxDIRCTRL_SHOW_FILTERS);
	mDirCtrl->GetTreeCtrl()->Connect(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler(LeftWindow::OnTreeItemActivated), NULL, this);
	mDirCtrl->GetTreeCtrl()->Connect(wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler(LeftWindow::OnTreeItemRightClick), NULL, this);

	mPopupMenu = new wxMenu;
	mPopupMenu->Append(IDC_LEFT_WND_MENU_COPY_FILENAME, wxT("复制文件名"));
	mPopupMenu->AppendSeparator();
	mPopupMenu->Append(IDC_LEFT_WND_MENU_FILE_RENAME, wxT("文件重命名"));
	mPopupMenu->AppendSeparator();
	mPopupMenu->Append(IDC_LEFT_WND_MENU_BROWSER_FILE, wxT("浏览文件"));	
}

LeftWindow::~LeftWindow()
{
	
}

wxString LeftWindow::GetCurSelFilePath()
{
	return mDirCtrl->GetPath();
}

void LeftWindow::OnTreeItemActivated(wxTreeEvent &event)
{
	MainFrame *gMainFrame = reinterpret_cast<MainFrame *>(GetParent());
	if (gMainFrame == NULL)
		return;

	wxString path = mDirCtrl->GetPath();
	gMainFrame->SetLastPath(path);

	if (path.Contains(wxT(".mex"))|| path.Contains(wxT(".tga")) || path.Contains(wxT(".dds")))
	{
		// 无须检查obj指针, 由使用者检查
		//gMainFrame->GetRightWindow()->GetModelConfigWnd()->ClearDate();
		if(path.Contains(wxT(".mex")))
		{
			gMainFrame->SetCurrentModel(gMainFrame->GetLastPath());

			//设置显示的模型路径
			gMainFrame->GetRightWindow()->GetModelConfigWnd()->SetString(MODEL_PATH , path);
		}

		//设置头像图片路径
		if(path.Contains(wxT(".tga")) || path.Contains(wxT(".dds")))
		{
			gMainFrame->GetRightWindow()->GetModelConfigWnd()->SetString(MODEL_HEAD , path);
		}
	

	}
	else
	{
		// 如果当前选中的是目录, 则展开或折叠
		wxTreeItemId curItem = mDirCtrl->GetTreeCtrl()->GetSelection();
		if (mDirCtrl->GetTreeCtrl()->IsExpanded(curItem))
			mDirCtrl->GetTreeCtrl()->Collapse(curItem);
		else
			mDirCtrl->GetTreeCtrl()->Expand(curItem);
	}
}

void LeftWindow::OnTreeItemRightClick(wxTreeEvent &event)
{
	wxPoint pos;
	wxTreeItemId hitItem;
	Utility_TreeCtrlHitTest(mDirCtrl->GetTreeCtrl(), pos, hitItem);
	if (hitItem.IsOk())
	{
		// 先选中树的Item
		mDirCtrl->GetTreeCtrl()->SelectItem(hitItem);
		// 再弹出菜单
		PopupMenu(mPopupMenu, pos.x, pos.y);
	}
}

void LeftWindow::OnTreeMouseWheel(wxMouseEvent &event)
{
	// 停止向下传递, 以防止树滚动
	event.StopPropagation();
}

void LeftWindow::OnMenuItemCopyFilename(wxCommandEvent &WXUNUSED(event))
{
	wxString fullPath = mDirCtrl->GetPath();
	wxFileName fn(fullPath);

	wxString fileName = fn.GetName() + wxT(".") + fn.GetExt();

	// 把文件名复制到剪贴板
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData(new wxTextDataObject(fileName));
		wxTheClipboard->Close();
	}	
}

void LeftWindow::OnMenuItemFileRename(wxCommandEvent &WXUNUSED(event))
{
	wxFileName fn(mDirCtrl->GetPath());
	wxTextEntryDialog dlg(this, wxT("请输入新的文件名:"), wxT("文件名更改"), fn.GetName(), wxOK);
	if (dlg.ShowModal() == wxID_OK)
	{
		if (!dlg.GetValue().empty())
		{
			wxString oldPath = fn.GetFullPath();

			// 更改文件名
			fn.SetName(dlg.GetValue());
			wxRenameFile(oldPath, fn.GetFullPath());

			// 刷新树控件
			wxTreeItemId curSel = mDirCtrl->GetTreeCtrl()->GetSelection();
			if (curSel != NULL)
			{
				wxDirItemData *clientData = new wxDirItemData(fn.GetFullPath(), fn.GetName(), false);
				mDirCtrl->GetTreeCtrl()->SetItemData(curSel, clientData);
				mDirCtrl->GetTreeCtrl()->SetItemText(curSel, fn.GetName() + wxT(".") + fn.GetExt());
			}
		}
	}
}

void LeftWindow::OnMenuItemBrowserFile(wxCommandEvent &WXUNUSED(event))
{
	// 打开文件位置
	wxString fullPath = mDirCtrl->GetPath();
	wxExecute(wxString::Format("explorer.exe /select, %s", fullPath.c_str()));
}

void LeftWindow::OnSize(wxSizeEvent &event)
{
	wxSize wndSize = event.GetSize();
	mDirCtrl->SetPosition(wxPoint(0, 0));
	mDirCtrl->SetSize(wndSize);
}