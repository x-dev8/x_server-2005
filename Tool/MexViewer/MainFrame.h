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

#define RIBBON_BAR_PAGE_NAME_MODEL_INFO			wxT("模型信息")
#define RIBBON_BAR_PAGE_NAME_ANIMATION			wxT("Animation")
#define RIBBON_BAR_PAGE_NAME_PARTICLE_EDIT		wxT("粒子编辑")
#define RIBBON_BAR_PAGE_NAME_AVATAR				wxT("Avatar")
#define RIBBON_BAR_PAGE_NAME_MODEL_CONFIG		wxT("模型配置")

#define MEXVIEWER_MAIN_FRM_STYLE				wxCAPTION | wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxCLIP_CHILDREN
#define MEXVIEWER_RIBBONBAR_MIN_HEIGHT			24
#define MEXVIEWER_RIBBONBAR_MAX_HEIGHT			120

#define MEXVIEWER_LEFT_WND_RATIO				0.22
#define MEXVIEWER_MIDDLE_WND_RATIO				0.56
#define MEXVIEWER_RIGHT_WND_RATIO				0.22

#define MEXVIEWER_FRAME_WND_HEIGHT				26

#define	MEXVIEWER_HELP_MSG						wxT("1. 使用右键拖动来移动摄像机\n2. 按住Alt键并拖动右键来旋转摄像机\n3. 按住Ctrl键并拖动右键旋转模型\n4. 按住Shitf键移动模型")

/*
* MewViewer应用程序主窗口
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
	 * 获取当前显示的模型
	 */
	ModelObj * GetCurrentModel();

	/*
	 * 设置当前显示的模型
	 */
	void SetCurrentModel(const wxString &path);

	/*
	 * 重新加载当前模型
	 */
	void ReloadCurrentModel();

	/*
	 * 获取当前显示的Helper类型
	 */
	int GetCurrentRenderHelper()  const { return mShowHelper; }

	/*
	 * 当前选中的动作索引
	 */
	const int GetCurAnimation() const { return mCurAnimation; }

	/*
	 * 是否显示Skeleton
	 */
	bool IsShowSkeleton() { return mShowSkeleton; }

	/*
	 * 是否显示包围盒
	 */
	bool IsShowAABB() { return mShowAABB; }

	/*
	 * 是否显示辅助网格
	 */
	bool IsShowGrid() const { return mShowGrid; }

	/*
	 * 是否显示Wireframe
	 */
	bool IsShowWireframe() const { return mShowWireframe; }

protected:
	/*
	 * 创建主菜单
	 */
	void CreateFrmMenu();
	
	/*
	 * 创建RibbonBar
	 */
	void CreateFrmRibbonBar();

	/*
	 * 创建子窗口 
	 */
	void CreateChildWindows();

	/*
	 * 从注册表中加载配置信息
	 */
	void LoadConfig();

	/*
	 * 保存配置信息到注册表中
	 */
	void SaveConfig();

	/*
	 * 获取Ribbon Bar的实际高度
	 */
	int GetRibbonBarHeight();

	/*
	 * 保存模型Mex文件
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