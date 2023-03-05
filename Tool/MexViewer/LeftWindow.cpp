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
	mPopupMenu->Append(IDC_LEFT_WND_MENU_COPY_FILENAME, wxT("�����ļ���"));
	mPopupMenu->AppendSeparator();
	mPopupMenu->Append(IDC_LEFT_WND_MENU_FILE_RENAME, wxT("�ļ�������"));
	mPopupMenu->AppendSeparator();
	mPopupMenu->Append(IDC_LEFT_WND_MENU_BROWSER_FILE, wxT("����ļ�"));	
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
		// ������objָ��, ��ʹ���߼��
		//gMainFrame->GetRightWindow()->GetModelConfigWnd()->ClearDate();
		if(path.Contains(wxT(".mex")))
		{
			gMainFrame->SetCurrentModel(gMainFrame->GetLastPath());

			//������ʾ��ģ��·��
			gMainFrame->GetRightWindow()->GetModelConfigWnd()->SetString(MODEL_PATH , path);
		}

		//����ͷ��ͼƬ·��
		if(path.Contains(wxT(".tga")) || path.Contains(wxT(".dds")))
		{
			gMainFrame->GetRightWindow()->GetModelConfigWnd()->SetString(MODEL_HEAD , path);
		}
	

	}
	else
	{
		// �����ǰѡ�е���Ŀ¼, ��չ�����۵�
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
		// ��ѡ������Item
		mDirCtrl->GetTreeCtrl()->SelectItem(hitItem);
		// �ٵ����˵�
		PopupMenu(mPopupMenu, pos.x, pos.y);
	}
}

void LeftWindow::OnTreeMouseWheel(wxMouseEvent &event)
{
	// ֹͣ���´���, �Է�ֹ������
	event.StopPropagation();
}

void LeftWindow::OnMenuItemCopyFilename(wxCommandEvent &WXUNUSED(event))
{
	wxString fullPath = mDirCtrl->GetPath();
	wxFileName fn(fullPath);

	wxString fileName = fn.GetName() + wxT(".") + fn.GetExt();

	// ���ļ������Ƶ�������
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData(new wxTextDataObject(fileName));
		wxTheClipboard->Close();
	}	
}

void LeftWindow::OnMenuItemFileRename(wxCommandEvent &WXUNUSED(event))
{
	wxFileName fn(mDirCtrl->GetPath());
	wxTextEntryDialog dlg(this, wxT("�������µ��ļ���:"), wxT("�ļ�������"), fn.GetName(), wxOK);
	if (dlg.ShowModal() == wxID_OK)
	{
		if (!dlg.GetValue().empty())
		{
			wxString oldPath = fn.GetFullPath();

			// �����ļ���
			fn.SetName(dlg.GetValue());
			wxRenameFile(oldPath, fn.GetFullPath());

			// ˢ�����ؼ�
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
	// ���ļ�λ��
	wxString fullPath = mDirCtrl->GetPath();
	wxExecute(wxString::Format("explorer.exe /select, %s", fullPath.c_str()));
}

void LeftWindow::OnSize(wxSizeEvent &event)
{
	wxSize wndSize = event.GetSize();
	mDirCtrl->SetPosition(wxPoint(0, 0));
	mDirCtrl->SetSize(wndSize);
}