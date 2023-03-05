#pragma once

#include "MiddleWindow.h"

#define REGKEY_APP_NAME							wxT("ModelViewer")
#define REGKEY_VENDOR_NAME						wxT("Tolez")
#define REGKEY_LAST_FOLDER						wxT("LastFolder")
#define REGKEY_SHOW_SKELETON					wxT("ShowSkeleton")
#define REGKEY_SHOW_AABB						wxT("ShowAABB")
#define REGKEY_SHOW_GRID						wxT("ShowGrid")
#define REGKEY_SHOW_WIREFRAME					wxT("ShowWireframe")
#define REGKEY_SHOW_HELPER						wxT("ShowHelper")
#define REGKEY_SHOW_RIBBON_PANEL				wxT("ShowRibbonPanel")
#define REGKEY_SHOW_LEFT_WINDOW					wxT("ShowLeftWindow")
#define REGKEY_SHOW_RIGHT_WINDOW				wxT("ShowRightWindow")
#define REGKEY_BLOOM							wxT("Bloom")
#define REGKEY_LIGHT_SHAFT						wxT("LightShaft")

#define RIBBON_BAR_PAGE_NAME_MODEL_INFO			wxT("ģ����Ϣ")
#define RIBBON_BAR_PAGE_NAME_ANIMATION			wxT("Animation")
#define RIBBON_BAR_PAGE_NAME_PARTICLE_EDIT		wxT("���ӱ༭")
#define RIBBON_BAR_PAGE_NAME_AVATAR				wxT("Avatar")
#define RIBBON_BAR_PAGE_NAME_MODEL_CONFIG		wxT("ģ������")

#define MEXVIEWER_MAIN_FRM_STYLE				wxCAPTION | wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxCLIP_CHILDREN
#define MEXVIEWER_RIBBONBAR_MIN_HEIGHT			24
#define MEXVIEWER_RIBBONBAR_MAX_HEIGHT			120

#define MEXVIEWER_LEFT_WND_RATIO				0.22
#define MEXVIEWER_MIDDLE_WND_RATIO				0.56
#define MEXVIEWER_RIGHT_WND_RATIO				0.22

#define MEXVIEWER_FRAME_WND_HEIGHT				26

#define	MEXVIEWER_HELP_MSG						wxT("1. ʹ���Ҽ��϶����ƶ������\n2. ��סAlt�����϶��Ҽ�����ת�����\n3. ��סCtrl�����϶��Ҽ���תģ��\n4. ��סShitf���ƶ�ģ��")

/*
* MewViewerӦ�ó���������
*/
class LeftWindow;
class RightWindow;
class FrameWindow;
class ModelObj;
class RenderHelper;
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString &title);
	virtual ~MainFrame();

public:
	LeftWindow * GetLeftWindow() { return mLeftWnd; }
	RenderHelper * GetRenderHelper() { return mMiddleWnd->GetRenderHelper(); }
	RightWindow * GetRightWindow() { return mRightWnd; }
	FrameWindow * GetFrameWindow() { return mFrameWnd; }

	void SetLastPath(const wxString &folder) { mLastPath = folder; }
	const wxString & GetLastPath() const { return mLastPath; }

	/*
	 * ��ȡ��ǰ��ʾ��ģ��
	 */
	ModelObj * GetCurrentModel();

	/*
	 * ���õ�ǰ��ʾ��ģ��
	 */
	void SetCurrentModel(const wxString &path);

	/*
	 * ���¼��ص�ǰģ��
	 */
	void ReloadCurrentModel();

	/*
	 * ��ȡ��ǰ��ʾ��Helper����
	 */
	int GetCurrentRenderHelper()  const { return mShowHelper; }

	/*
	 * ��ǰѡ�еĶ�������
	 */
	const int GetCurAnimation() const { return mCurAnimation; }

	/*
	 * �Ƿ���ʾSkeleton
	 */
	bool IsShowSkeleton() { return mShowSkeleton; }

	/*
	 * �Ƿ���ʾ��Χ��
	 */
	bool IsShowAABB() { return mShowAABB; }

	/*
	 * �Ƿ���ʾ��������
	 */
	bool IsShowGrid() const { return mShowGrid; }

	/*
	 * �Ƿ���ʾWireframe
	 */
	bool IsShowWireframe() const { return mShowWireframe; }

protected:
	/*
	 * �������˵�
	 */
	void CreateFrmMenu();
	
	/*
	 * ����RibbonBar
	 */
	void CreateFrmRibbonBar();

	/*
	 * �����Ӵ��� 
	 */
	void CreateChildWindows();

	/*
	 * ��ע����м���������Ϣ
	 */
	void LoadConfig();

	/*
	 * ����������Ϣ��ע�����
	 */
	void SaveConfig();

	/*
	 * ��ȡRibbon Bar��ʵ�ʸ߶�
	 */
	int GetRibbonBarHeight();

	/*
	 * ����ģ��Mex�ļ�
	 */
	bool SaveCurrentModelMexFile();

protected:
	void OnRibbonPageChanged(wxRibbonBarEvent &event);
	void OnRibbonBtnBarClicked_Smaller(wxRibbonButtonBarEvent &WXUNUSED(evt));
	void OnRibbonBtnBarClicked_Larger(wxRibbonButtonBarEvent &WXUNUSED(evt));
	void OnRibbonBtnBarClicked_SaveMex(wxRibbonButtonBarEvent &WXUNUSED(evt));

	void OnMenuItemOpen(wxCommandEvent &WXUNUSED(event));
	void OnMenuItemQuit(wxCommandEvent &WXUNUSED(event));
	void OnMenuItemSave(wxCommandEvent &WXUNUSED(event));
	void OnMenuItemRange(wxCommandEvent &event);

	void OnMouseWheel(wxMouseEvent &event);

	void OnSize(wxSizeEvent &event);

	DECLARE_EVENT_TABLE()

protected:
	wxMenuBar *mMenuBar;
	wxMenuItem *mShowHelperMenu[5];

	wxRibbonBar *mRibbonBar;

	LeftWindow *mLeftWnd;
	MiddleWindow *mMiddleWnd;
	RightWindow *mRightWnd;
	FrameWindow *mFrameWnd;

	wxConfig *mConfig;
	wxString mLastPath;
	bool mShowSkeleton;
	bool mShowAABB;
	bool mShowGrid;
	bool mShowWireframe;
	int mShowHelper;
	bool mShowRibbonPanel;
	bool mShowLeftWindow;
	bool mShowRightWindow;

	bool mBloom;
	bool mLightShaft;

	int mCurAnimation;
};

extern MainFrame *gMainFrame;