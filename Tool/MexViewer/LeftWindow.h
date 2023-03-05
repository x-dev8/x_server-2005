#pragma once

#include <wx/textdlg.h>

#define DIR_TREE_FILTER		wxT("Mex (*.mex)|*.mex|Tga (*.tga)|*.tga|DDS (*.dds)|*.dds")

/*
 * ��ߴ���, ��ʾ�ļ���
 */
class LeftWindow : public wxWindow
{
public:
	LeftWindow(wxWindow *parent, wxWindowID id,
		const wxPoint &pos, const wxSize &size, const wxString &defaultFolder);
	virtual ~LeftWindow();

public:
	/*
	 * ��ȡ��ǰѡ�е��ļ�·��
	 */
	wxString GetCurSelFilePath();

protected:
	void OnTreeItemActivated(wxTreeEvent &event);
	void OnTreeItemRightClick(wxTreeEvent &event);
	void OnTreeMouseWheel(wxMouseEvent &event);

	void OnMenuItemCopyFilename(wxCommandEvent &WXUNUSED(event));
	void OnMenuItemFileRename(wxCommandEvent &WXUNUSED(event));
	void OnMenuItemBrowserFile(wxCommandEvent &WXUNUSED(event));

	void OnSize(wxSizeEvent &event);

	DECLARE_EVENT_TABLE()

protected:
	wxGenericDirCtrl *mDirCtrl;
	wxMenu *mPopupMenu;
};