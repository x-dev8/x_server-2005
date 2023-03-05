#include "StdAfx.h"
#include "MainFrame.h"

#include "LeftWindow.h"
#include "RightWindow.h"
#include "FrameWindow.h"
#include "ModelObj.h"
#include "RenderHelper.h"
#include "Utility.h"
#include "icon.xpm"

MainFrame *gMainFrame = NULL;

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_RIBBONBAR_PAGE_CHANGED(IDC_RIBBON_BAR, MainFrame::OnRibbonPageChanged)
	EVT_RIBBONBUTTONBAR_CLICKED(IDC_BTN_SMALLER, MainFrame::OnRibbonBtnBarClicked_Smaller)
	EVT_RIBBONBUTTONBAR_CLICKED(IDC_BTN_LARGER, MainFrame::OnRibbonBtnBarClicked_Larger)
	EVT_RIBBONBUTTONBAR_CLICKED(IDC_BTN_SAVEMEX, MainFrame::OnRibbonBtnBarClicked_SaveMex)

	EVT_MENU(wxID_OPEN, MainFrame::OnMenuItemOpen)
	EVT_MENU(wxID_SAVE, MainFrame::OnMenuItemSave)
	EVT_MENU(wxID_EXIT, MainFrame::OnMenuItemQuit)
	EVT_MENU_RANGE(IDC_SHOW_MENU_SHOW_SKELETON, IDC_HELP_MENU_ABOUT, MainFrame::OnMenuItemRange)

	EVT_MOUSEWHEEL(MainFrame::OnMouseWheel)

	EVT_SIZE(MainFrame::OnSize)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString &title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1260, 748), MEXVIEWER_MAIN_FRM_STYLE),
	mRibbonBar(NULL), mLeftWnd(NULL), mMiddleWnd(NULL), mRightWnd(NULL), mCurAnimation(-1)
{
	SetIcon(wxIcon(icon_xpm));

	this->LoadConfig();

	this->CreateFrmMenu();
	this->CreateFrmRibbonBar();
	this->CreateChildWindows();

	Center();

	gMainFrame = this;
}

MainFrame::~MainFrame()
{
	SaveConfig();
}

ModelObj * MainFrame::GetCurrentModel()
{
	return mMiddleWnd->GetRenderHelper()->GetCurrentModel();
}

void MainFrame::SetCurrentModel(const wxString &path)
{
	ModelObj *obj = mMiddleWnd->GetRenderHelper()->SetCurrentModel(path);
	if (obj == NULL)
		return;

	IMex *mex = obj->model->GetMex();
	if (mex == NULL)
		return;

	mFrameWnd->StartTimer(obj->model->GetStartFrameID(), obj->model->GetEndFrameId());

	// 伪造事件, 根据当前的Page刷新RightWnd
	int curPage = mRibbonBar->GetActivePage();
	if (curPage == -1)
		return;

	wxRibbonPage *page = mRibbonBar->GetPage(curPage);
	wxRibbonBarEvent evt;
	evt.SetPage(page);
	OnRibbonPageChanged(evt);
}

void MainFrame::ReloadCurrentModel()
{
	mMiddleWnd->GetRenderHelper()->ReloadCurrentModel();
}

void MainFrame::CreateFrmMenu()
{
	mMenuBar = new wxMenuBar;
	{
		wxMenu *fileMenu = new wxMenu;
		mMenuBar->Append(fileMenu, wxT("文件"));
		{
			fileMenu->Append(wxID_OPEN, wxT("打开"));
			fileMenu->AppendSeparator();

			fileMenu->Append(wxID_SAVE, wxT("&保存\tCtrl+S"));
			fileMenu->AppendSeparator();

			fileMenu->Append(wxID_EXIT, wxT("退出"));
		}
		
		wxMenu *showMenu = new wxMenu;
		mMenuBar->Append(showMenu, wxT("显示"));
		{
			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_SKELETON, wxT("显示&骨骼\tCtrl+1"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_SKELETON, mShowSkeleton);

			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_AABB, wxT("显示&AABB\tCtrl+2"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_AABB, mShowAABB);
			
			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_GRID, wxT("显示&辅助网格\tCtrl+3"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_GRID, mShowGrid);
			showMenu->AppendSeparator();

			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_WIREFRAME, wxT("显示&线框\tF3"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_WIREFRAME, mShowWireframe);
			showMenu->AppendSeparator();

			wxMenu *subMenu = new wxMenu;
			showMenu->Append(IDC_SHOW_MENU_SHOW_HELPER, wxT("显示Helper"), subMenu);
			{
				mShowHelperMenu[0] = subMenu->AppendCheckItem(IDC_SHOW_MENU_HIDE_ALL_HELPER, wxT("隐藏&所有Helper\tCtrl+Q"));
				mShowHelperMenu[1] = subMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_FLOOR, wxT("显示&Floor\tCtrl+W"));
				mShowHelperMenu[2] = subMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_SUPER_FLOOR, wxT("显示&Super Floor\tCtrl+E"));
				mShowHelperMenu[3] = subMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_COLLISION, wxT("显示&Collision\tCtrl+R"));
				mShowHelperMenu[4] = subMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_ALPHA_BOX, wxT("显示&AlphaBox\tCtrl+T"));

				for (int i = 1; i < 5; ++i)
					mShowHelperMenu[i]->Check(false);
				mShowHelperMenu[mShowHelper]->Check(true);
			}
			showMenu->AppendSeparator();

			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_RIBBON_PANELS, wxT("显示&Ribbon面板\tCtrl+4"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_RIBBON_PANELS, mShowRibbonPanel);

			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_LEFTWND, wxT("显示&左面板\tCtrl+5"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_LEFTWND, mShowLeftWindow);

			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_RIGHTWND, wxT("显示&右面板\tCtrl+6"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_RIGHTWND, mShowRightWindow);
		}

		wxMenu *effectMenu = new wxMenu;
		mMenuBar->Append(effectMenu, wxT("特殊效果"));
		{
			effectMenu->AppendCheckItem(IDC_EFFECT_MENU_BLOOM, wxT("全屏泛光"));
			effectMenu->Check(IDC_EFFECT_MENU_BLOOM, mBloom);

			effectMenu->AppendCheckItem(IDC_EFFECT_MENU_LIGHT_SHAFT, wxT("体积光"));
			effectMenu->Check(IDC_EFFECT_MENU_LIGHT_SHAFT, mLightShaft);
		}

		wxMenu *sceneMenu = new wxMenu;
		mMenuBar->Append(sceneMenu, wxT("场景设置"));
		{
			sceneMenu->Append(IDC_SCENE_MENU_LIGHT_COLOR_AMBIENT, wxT("环境光"));
			sceneMenu->Append(IDC_SCENE_MENU_LIGHT_COLOR_DIFFUSE, wxT("漫反射光"));
			sceneMenu->Append(IDC_SCENE_MENU_LIGHT_COLOR_SPECULAR, wxT("镜面反射光"));
			sceneMenu->Append(IDC_SCENE_MENU_LIGHT_COLOR_DEFAULT, wxT("默认灯光颜色"));
			sceneMenu->AppendSeparator();

			sceneMenu->Append(IDC_SCENE_MENU_BACKGROUND_COLOR, wxT("背景颜色"));
		}

		wxMenu *helpMenu = new wxMenu;
		mMenuBar->Append(helpMenu, wxT("帮助"));
		{
			helpMenu->Append(IDC_HELP_MENU_HELP, wxT("使用说明"));
			helpMenu->Append(IDC_HELP_MENU_ABOUT, wxT("关于"));
		}
	}
	SetMenuBar(mMenuBar);
}

void MainFrame::CreateFrmRibbonBar()
{
	wxSize clientSize = GetClientSize();
	mRibbonBar = new wxRibbonBar(this, IDC_RIBBON_BAR);

	wxColour secondary, tertiary;
	mRibbonBar->GetArtProvider()->GetColourScheme(NULL, &secondary, &tertiary);
	mRibbonBar->GetArtProvider()->SetColourScheme(0xffffffff, secondary, tertiary);
	{
		{
			wxRibbonPage *page = new wxRibbonPage(mRibbonBar, wxID_ANY, RIBBON_BAR_PAGE_NAME_MODEL_INFO);
			{
				wxRibbonPanel *panel = new wxRibbonPanel(page, wxID_ANY, wxT("缩放"));

				wxRibbonButtonBar *btnbar = new wxRibbonButtonBar(panel);
				btnbar->AddButton(IDC_BTN_SMALLER, wxT("缩小"), wxArtProvider::GetBitmap(wxART_MINUS));
				btnbar->AddButton(IDC_BTN_LARGER, wxT("放大"), wxArtProvider::GetBitmap(wxART_PLUS));
			}
		}

		{
			wxRibbonPage *page = new wxRibbonPage(mRibbonBar, wxID_ANY, RIBBON_BAR_PAGE_NAME_ANIMATION);
			{
				wxRibbonPanel *panel = new wxRibbonPanel(page, wxID_ANY, wxT("Animation"));
			}
		}

		{
			wxRibbonPage *page = new wxRibbonPage(mRibbonBar, wxID_ANY, RIBBON_BAR_PAGE_NAME_PARTICLE_EDIT);
			wxRibbonPanel *panel = new wxRibbonPanel(page, wxID_ANY, wxT("粒子发射器"));

			wxRibbonButtonBar *btnbar = new wxRibbonButtonBar(panel);
			btnbar->AddButton(IDC_BTN_SAVEMEX, wxT("保存Mex文件"), wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_OTHER, wxSize(20, 20)));
		}

		{
			wxRibbonPage *page = new wxRibbonPage(mRibbonBar, wxID_ANY, RIBBON_BAR_PAGE_NAME_AVATAR);
			wxRibbonPanel *panel = new wxRibbonPanel(page, wxID_ANY, wxT("AvatarPanel"));
		}
		{
			wxRibbonPage *page = new wxRibbonPage(mRibbonBar, wxID_ANY, RIBBON_BAR_PAGE_NAME_MODEL_CONFIG);
			wxRibbonPanel *panel = new wxRibbonPanel(page, wxID_ANY, wxT("model_Config"));
		
		}
	}
	mRibbonBar->Realize();
}

void MainFrame::CreateChildWindows()
{
	mLeftWnd = new LeftWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, mLastPath);
	mLeftWnd->Show(mShowLeftWindow);

	mMiddleWnd = new MiddleWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	mRightWnd = new RightWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	mRightWnd->Show(mShowRightWindow);

	mFrameWnd = new FrameWindow(this, wxID_ANY);
}

void MainFrame::LoadConfig()
{
	// 读取配置信息
	mConfig = new wxConfig(REGKEY_APP_NAME, REGKEY_VENDOR_NAME);

	if (!mConfig->Read(REGKEY_LAST_FOLDER, &mLastPath))
	{
		// 如果注册表中没有数据, 则默认为D盘
		mLastPath = wxT("D:\\");
	}

	if (!mConfig->Read(REGKEY_SHOW_SKELETON, &mShowSkeleton))
		mShowSkeleton = false;

	if (!mConfig->Read(REGKEY_SHOW_AABB, &mShowAABB))
		mShowAABB = false;

	if (!mConfig->Read(REGKEY_SHOW_GRID, &mShowGrid))
		mShowGrid = true;

	if (!mConfig->Read(REGKEY_SHOW_WIREFRAME, &mShowWireframe))
		mShowWireframe = false;

	if (!mConfig->Read(REGKEY_SHOW_HELPER, &mShowHelper))
		mShowHelper = 0;

	if (!mConfig->Read(REGKEY_SHOW_RIBBON_PANEL, &mShowRibbonPanel))
		mShowRibbonPanel = false;

	if (!mConfig->Read(REGKEY_SHOW_LEFT_WINDOW, &mShowLeftWindow))
		mShowLeftWindow = true;

	if (!mConfig->Read(REGKEY_SHOW_RIGHT_WINDOW, &mShowRightWindow))
		mShowRightWindow = true;

	if (!mConfig->Read(REGKEY_BLOOM, &mBloom))
		mBloom = false;

	if (!mConfig->Read(REGKEY_LIGHT_SHAFT, &mLightShaft))
		mLightShaft = false;
}

void MainFrame::SaveConfig()
{
	// 保存配置信息
	if (mLastPath.Contains(wxT(".mex")))
	{
		wxFileName fileName(mLastPath);
		mConfig->Write(REGKEY_LAST_FOLDER, fileName.GetPath());
	}
	else
	{
		mConfig->Write(REGKEY_LAST_FOLDER, mLastPath);
	}

	mConfig->Write(REGKEY_SHOW_SKELETON, mShowSkeleton);
	mConfig->Write(REGKEY_SHOW_AABB, mShowAABB);
	mConfig->Write(REGKEY_SHOW_GRID, mShowGrid);
	mConfig->Write(REGKEY_SHOW_WIREFRAME, mShowWireframe);
	mConfig->Write(REGKEY_SHOW_HELPER, mShowHelper);
	mConfig->Write(REGKEY_SHOW_RIBBON_PANEL, mShowRibbonPanel);
	mConfig->Write(REGKEY_SHOW_LEFT_WINDOW, mShowLeftWindow);
	mConfig->Write(REGKEY_SHOW_RIGHT_WINDOW, mShowRightWindow);

	mConfig->Write(REGKEY_BLOOM, mBloom);
	mConfig->Write(REGKEY_LIGHT_SHAFT, mLightShaft);

	delete mConfig;
}

int MainFrame::GetRibbonBarHeight()
{
	int ribbonBarHeight = 0;
	if (mShowRibbonPanel)
		ribbonBarHeight = MEXVIEWER_RIBBONBAR_MAX_HEIGHT;
	else
		ribbonBarHeight = MEXVIEWER_RIBBONBAR_MIN_HEIGHT;
	return ribbonBarHeight;
}

bool MainFrame::SaveCurrentModelMexFile()
{
	ModelObj *obj = this->GetCurrentModel();
	if (obj == NULL)
		return false;

	// 只保存带有粒子编辑器的模型
	if (!obj->HasParticleEmitters())
	{
		wxMessageBox(wxT("不能保存没有粒子发射器的模型"));
		return false;
	}

	// 只有当前选中的是粒子标签页, 才可以保存Mex文件
	if (mRibbonBar->GetActivePage() != 2)
	{
		wxMessageBox(wxT("没有需要保存的粒子发射器\n请切换到粒子编辑\n修改粒子发射器参数后再保存Mex文件"));
		return false;
	}

	// 保存粒子发射器参数
	if (!mRightWnd->SaveCurrentParticleEmitterParams())
		return false;

	wxString desc = wxString::Format(wxT("正在保存Mex文件: %s"), obj->GetFileName());
	wxProgressDialog dlg(wxT("保存文件"), desc, 10, this, wxPD_APP_MODAL);
	for (int i = 0; i < 10; ++i)
	{
		if (!dlg.Update(i))
			dlg.Resume();

		wxMilliSleep(60);
	}

	obj->SaveToFile();
	this->ReloadCurrentModel();
	return true;
}

void MainFrame::OnRibbonPageChanged(wxRibbonBarEvent &event)
{
	wxString pageName = event.GetPage()->GetName();
	if (pageName == RIBBON_BAR_PAGE_NAME_MODEL_INFO)
		mRightWnd->ShowChildByType(RightWindow::ChildWnd_ModelInfo);
	else if (pageName == RIBBON_BAR_PAGE_NAME_ANIMATION)
		mRightWnd->ShowChildByType(RightWindow::ChildWnd_Animation);
	else if (pageName == RIBBON_BAR_PAGE_NAME_PARTICLE_EDIT)
		mRightWnd->ShowChildByType(RightWindow::ChildWnd_PartEdit);
	else if (pageName == RIBBON_BAR_PAGE_NAME_AVATAR)
		mRightWnd->ShowChildByType(RightWindow::ChildWnd_Avatar);
	else if (pageName == RIBBON_BAR_PAGE_NAME_MODEL_CONFIG) //模型配置
	    mRightWnd->ShowChildByType(RightWindow::ChildWnd_ModelConfig);
	else
		wxMessageBox(wxT("严重错误, Page不存在"));
}

void MainFrame::OnRibbonBtnBarClicked_Smaller(wxRibbonButtonBarEvent &WXUNUSED(evt))
{
	if (mMiddleWnd->GetRenderHelper()->GetCurrentModel() == NULL)
		return;

	mMiddleWnd->GetRenderHelper()->GetCurrentModel()->ToLargerOrSmaller(false);
	mMiddleWnd->GetRenderHelper()->GetCurrentModel()->ApplyTransform();

	// 通知右边窗口刷新
	mRightWnd->UpdateInfoByChildType(RightWindow::ChildWnd_ModelInfo);
}

void MainFrame::OnRibbonBtnBarClicked_Larger(wxRibbonButtonBarEvent &WXUNUSED(evt))
{
	if (mMiddleWnd->GetRenderHelper()->GetCurrentModel() == NULL)
		return;

	mMiddleWnd->GetRenderHelper()->GetCurrentModel()->ToLargerOrSmaller(true);
	mMiddleWnd->GetRenderHelper()->GetCurrentModel()->ApplyTransform();

	// 通知右边窗口刷新
	mRightWnd->UpdateInfoByChildType(RightWindow::ChildWnd_ModelInfo);
}

void MainFrame::OnRibbonBtnBarClicked_SaveMex(wxRibbonButtonBarEvent &WXUNUSED(evt))
{
	this->SaveCurrentModelMexFile();
}

void MainFrame::OnMenuItemOpen(wxCommandEvent &WXUNUSED(event))
{
	wxFileDialog dlg(this, wxT("打开Mex文件"), wxT("D:\\"), wxEmptyString,
		wxT("Mex Files (*.mex)|*.mex"), wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString path = dlg.GetPath();
		this->SetCurrentModel(path);
	}
}

void MainFrame::OnMenuItemSave(wxCommandEvent &WXUNUSED(event))
{
	this->SaveCurrentModelMexFile();
}

void MainFrame::OnMenuItemQuit(wxCommandEvent &WXUNUSED(event))
{
	Close(false);
}

void MainFrame::OnMenuItemRange(wxCommandEvent &event)
{
	switch (event.GetId())
	{
	case IDC_SHOW_MENU_SHOW_SKELETON:
		mShowSkeleton = !mShowSkeleton;
		break;

	case IDC_SHOW_MENU_SHOW_AABB:
		mShowAABB = !mShowAABB;
		break;

	case IDC_SHOW_MENU_SHOW_GRID:
		mShowGrid = !mShowGrid;	
		break;

	case IDC_SHOW_MENU_SHOW_WIREFRAME:
		mShowWireframe = !mShowWireframe;
		break;

	case IDC_SHOW_MENU_HIDE_ALL_HELPER:
	case IDC_SHOW_MENU_SHOW_FLOOR:
	case IDC_SHOW_MENU_SHOW_SUPER_FLOOR:
	case IDC_SHOW_MENU_SHOW_COLLISION:
	case IDC_SHOW_MENU_SHOW_ALPHA_BOX:
		{
			mShowHelper = event.GetId() - IDC_SHOW_MENU_HIDE_ALL_HELPER;
			if (mShowHelper >= 0 && mShowHelper <= 4)
			{
				// 先Uncheck
				for (int i = 0; i < 5; ++i)
					mShowHelperMenu[i]->Check(false);

				mShowHelperMenu[mShowHelper]->Check(true);
				GetMe3dConfig()->SetRenderHelper((Config::ERenderHelper) mShowHelper);
			}
		}
		break;

	case IDC_SHOW_MENU_SHOW_RIBBON_PANELS:
	case IDC_SHOW_MENU_SHOW_LEFTWND:
	case IDC_SHOW_MENU_SHOW_RIGHTWND:
		{
			if (event.GetId() == IDC_SHOW_MENU_SHOW_RIBBON_PANELS)
			{
				mShowRibbonPanel = !mShowRibbonPanel;
			}
			else if (event.GetId() == IDC_SHOW_MENU_SHOW_LEFTWND)
			{
				// 显示/隐藏左边面板
				mShowLeftWindow = !mLeftWnd->IsShown();
				mLeftWnd->Show(!mLeftWnd->IsShown());
			}
			else if (event.GetId() == IDC_SHOW_MENU_SHOW_RIGHTWND)
			{
				// 显示/隐藏右边面板
				mShowRightWindow = !mRightWnd->IsShown();
				mRightWnd->Show(mShowRightWindow);
			}

			// 伪造OnSize消息
			wxSizeEvent evt;
			OnSize(evt);
		}
		break;

	case IDC_EFFECT_MENU_BLOOM:
	case IDC_EFFECT_MENU_LIGHT_SHAFT:
		{
			if (event.GetId() == IDC_EFFECT_MENU_BLOOM)
				mBloom = !mBloom;
			else if (event.GetId() == IDC_EFFECT_MENU_LIGHT_SHAFT)
				mLightShaft = !mLightShaft;

			PostProcessManager::instance().enableProcess("Bloom", mBloom);
			PostProcessManager::instance().enableProcess("LightShaft", mLightShaft);
		}
		break;

	case IDC_SCENE_MENU_LIGHT_COLOR_AMBIENT:
	case IDC_SCENE_MENU_LIGHT_COLOR_DIFFUSE:
	case IDC_SCENE_MENU_LIGHT_COLOR_SPECULAR:
	case IDC_SCENE_MENU_LIGHT_COLOR_DEFAULT:
		{
			if (GetRenderHelper() == NULL)
				break;

			if (event.GetId() == IDC_SCENE_MENU_LIGHT_COLOR_DEFAULT)
			{
				GetRenderHelper()->SetLighting(true);
				break;
			}

			wxColourData data;
			data.SetChooseFull(true);
			
			D3DLIGHT9 &light = GetRenderHelper()->GetLightParam();
			D3DCOLORVALUE d3dClr;
			if (event.GetId() == IDC_SCENE_MENU_LIGHT_COLOR_AMBIENT)
				d3dClr = light.Ambient;
			else if (event.GetId() == IDC_SCENE_MENU_LIGHT_COLOR_DIFFUSE)
				d3dClr = light.Diffuse;
			else if (event.GetId() == IDC_SCENE_MENU_LIGHT_COLOR_SPECULAR)
				d3dClr = light.Specular;
			
			wxColour clr;
			clr.Set(d3dClr.r * 255, d3dClr.g * 255, d3dClr.b * 255, d3dClr.a * 255);
			data.SetColour(clr);
			wxColourDialog dlg(this, &data);
			if (dlg.ShowModal() == wxID_OK)
			{
				wxColour curSelClr = dlg.GetColourData().GetColour();
				d3dClr.a = (unsigned char) curSelClr.Alpha() / 255.0f;
				d3dClr.r = (unsigned char) curSelClr.Red() / 255.0f;
				d3dClr.g = (unsigned char) curSelClr.Green() / 255.0f;
				d3dClr.b = (unsigned char) curSelClr.Blue() / 255.0f;
				
				if (event.GetId() == IDC_SCENE_MENU_LIGHT_COLOR_AMBIENT)
					GetRenderHelper()->GetLightParam().Ambient = d3dClr;
				else if (event.GetId() == IDC_SCENE_MENU_LIGHT_COLOR_DIFFUSE)
					GetRenderHelper()->GetLightParam().Diffuse = d3dClr;
				else if (event.GetId() == IDC_SCENE_MENU_LIGHT_COLOR_SPECULAR)
					GetRenderHelper()->GetLightParam().Specular = d3dClr;

				GetRenderHelper()->SetLighting(false);
			}
		}
		break;

	case IDC_SCENE_MENU_BACKGROUND_COLOR:
		{
			wxColourData data;
			data.SetChooseFull(true);

			D3DCOLOR bg = GetRenderHelper()->GetBackgroundColor();
			wxColour clr;
			clr.Set((bg >> 16) & 0xff, (bg >> 8) & 0xff, bg & 0xff, (bg >> 24) & 0xff);
			data.SetColour(clr);

			wxColourDialog dlg(this, &data);
			if (dlg.ShowModal() == wxID_OK)
			{
				wxColour curSelClr = dlg.GetColourData().GetColour();
				unsigned char a = (unsigned char) curSelClr.Alpha();
				unsigned char r = (unsigned char) curSelClr.Red();
				unsigned char g = (unsigned char) curSelClr.Green();
				unsigned char b = (unsigned char) curSelClr.Blue();
				DWORD color = (a << 24) | (r << 16) | (g << 8) | b;

				this->GetRenderHelper()->SetBackgroundColor(color);
			}
		}
		break;

	case IDC_HELP_MENU_HELP:
		{
			wxMessageBox(MEXVIEWER_HELP_MSG, wxT("使用说明"));
		}
		break;

	case IDC_HELP_MENU_ABOUT:
		{
			wxAboutDialogInfo info;
			info.SetName(wxT("Mex模型查看器"));
			info.SetVersion(wxT("0.0.1"));
			info.SetDescription(wxT("Mex模型查看器"));
			info.SetCopyright(wxT("(C) 2008-2012 拓乐网络 Dev Team"));
			info.SetWebSite(wxT("http://www.tolez.com/"), wxT("拓乐网络科技"));
			info.AddDeveloper(wxT("王帅"));
			wxAboutBox(info, this);
		}
		break;
	}
}

void MainFrame::OnMouseWheel(wxMouseEvent &event)
{
	mMiddleWnd->GetRenderHelper()->AdjustCameraFarAwayOrComeClose(event);
}

void MainFrame::OnSize(wxSizeEvent &event)
{
	if (mRibbonBar == NULL || mLeftWnd == NULL || mMiddleWnd == NULL || mRightWnd == NULL)
		return;

	wxSize clientSize = this->GetClientSize();
	int h = clientSize.GetHeight() - GetRibbonBarHeight();

	mRibbonBar->SetSize(clientSize.GetWidth(), GetRibbonBarHeight());

	if (mLeftWnd->IsShown() && mRightWnd->IsShown()) // 左右面板都显示
	{
		mLeftWnd->SetPosition(wxPoint(0, GetRibbonBarHeight()));
		mLeftWnd->SetSize(clientSize.GetWidth() * MEXVIEWER_LEFT_WND_RATIO, h);

		mMiddleWnd->SetPosition(wxPoint(mLeftWnd->GetSize().GetWidth(), GetRibbonBarHeight()));
		mMiddleWnd->SetSize(clientSize.GetWidth() * MEXVIEWER_MIDDLE_WND_RATIO, h - MEXVIEWER_FRAME_WND_HEIGHT);

		mRightWnd->SetPosition(wxPoint(
			mLeftWnd->GetSize().GetWidth() + mMiddleWnd->GetSize().GetWidth(),
			GetRibbonBarHeight()));
		mRightWnd->SetSize(clientSize.GetWidth() * MEXVIEWER_RIGHT_WND_RATIO, h);
	}
	else if (mLeftWnd->IsShown()) // 只有左面板显示
	{
		mLeftWnd->SetPosition(wxPoint(0, GetRibbonBarHeight()));
		mLeftWnd->SetSize(clientSize.GetWidth() * MEXVIEWER_LEFT_WND_RATIO, h);

		mMiddleWnd->SetPosition(wxPoint(mLeftWnd->GetSize().GetWidth(), GetRibbonBarHeight()));
		mMiddleWnd->SetSize(clientSize.GetWidth() * (1.0f - MEXVIEWER_LEFT_WND_RATIO), h - MEXVIEWER_FRAME_WND_HEIGHT);
	}
	else if (mRightWnd->IsShown()) // 只有右面板显示
	{
		mMiddleWnd->SetPosition(wxPoint(0, GetRibbonBarHeight()));
		mMiddleWnd->SetSize(clientSize.GetWidth() * (1.0f - MEXVIEWER_RIGHT_WND_RATIO), h - MEXVIEWER_FRAME_WND_HEIGHT);

		mRightWnd->SetPosition(wxPoint(
			mMiddleWnd->GetSize().GetWidth(),
			GetRibbonBarHeight()));
		mRightWnd->SetSize(clientSize.GetWidth() * MEXVIEWER_RIGHT_WND_RATIO, h);
	}
	else // 左右面板都隐藏
	{
		mMiddleWnd->SetPosition(wxPoint(0, GetRibbonBarHeight()));
		mMiddleWnd->SetSize(clientSize.GetWidth(), h - MEXVIEWER_FRAME_WND_HEIGHT);
	}

	int yy = mMiddleWnd->GetPosition().y + mMiddleWnd->GetClientSize().GetHeight();
	int xx =  mMiddleWnd->GetPosition().x;
	mFrameWnd->SetPosition(wxPoint(
		mMiddleWnd->GetPosition().x,
		mMiddleWnd->GetPosition().y + mMiddleWnd->GetClientSize().GetHeight()));
	mFrameWnd->SetSize(
		mMiddleWnd->GetSize().GetWidth(),
		MEXVIEWER_FRAME_WND_HEIGHT);
}