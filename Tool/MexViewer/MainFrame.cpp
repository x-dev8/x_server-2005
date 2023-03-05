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

	// α���¼�, ���ݵ�ǰ��Pageˢ��RightWnd
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
		mMenuBar->Append(fileMenu, wxT("�ļ�"));
		{
			fileMenu->Append(wxID_OPEN, wxT("��"));
			fileMenu->AppendSeparator();

			fileMenu->Append(wxID_SAVE, wxT("&����\tCtrl+S"));
			fileMenu->AppendSeparator();

			fileMenu->Append(wxID_EXIT, wxT("�˳�"));
		}
		
		wxMenu *showMenu = new wxMenu;
		mMenuBar->Append(showMenu, wxT("��ʾ"));
		{
			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_SKELETON, wxT("��ʾ&����\tCtrl+1"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_SKELETON, mShowSkeleton);

			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_AABB, wxT("��ʾ&AABB\tCtrl+2"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_AABB, mShowAABB);
			
			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_GRID, wxT("��ʾ&��������\tCtrl+3"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_GRID, mShowGrid);
			showMenu->AppendSeparator();

			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_WIREFRAME, wxT("��ʾ&�߿�\tF3"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_WIREFRAME, mShowWireframe);
			showMenu->AppendSeparator();

			wxMenu *subMenu = new wxMenu;
			showMenu->Append(IDC_SHOW_MENU_SHOW_HELPER, wxT("��ʾHelper"), subMenu);
			{
				mShowHelperMenu[0] = subMenu->AppendCheckItem(IDC_SHOW_MENU_HIDE_ALL_HELPER, wxT("����&����Helper\tCtrl+Q"));
				mShowHelperMenu[1] = subMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_FLOOR, wxT("��ʾ&Floor\tCtrl+W"));
				mShowHelperMenu[2] = subMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_SUPER_FLOOR, wxT("��ʾ&Super Floor\tCtrl+E"));
				mShowHelperMenu[3] = subMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_COLLISION, wxT("��ʾ&Collision\tCtrl+R"));
				mShowHelperMenu[4] = subMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_ALPHA_BOX, wxT("��ʾ&AlphaBox\tCtrl+T"));

				for (int i = 1; i < 5; ++i)
					mShowHelperMenu[i]->Check(false);
				mShowHelperMenu[mShowHelper]->Check(true);
			}
			showMenu->AppendSeparator();

			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_RIBBON_PANELS, wxT("��ʾ&Ribbon���\tCtrl+4"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_RIBBON_PANELS, mShowRibbonPanel);

			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_LEFTWND, wxT("��ʾ&�����\tCtrl+5"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_LEFTWND, mShowLeftWindow);

			showMenu->AppendCheckItem(IDC_SHOW_MENU_SHOW_RIGHTWND, wxT("��ʾ&�����\tCtrl+6"));
			showMenu->Check(IDC_SHOW_MENU_SHOW_RIGHTWND, mShowRightWindow);
		}

		wxMenu *effectMenu = new wxMenu;
		mMenuBar->Append(effectMenu, wxT("����Ч��"));
		{
			effectMenu->AppendCheckItem(IDC_EFFECT_MENU_BLOOM, wxT("ȫ������"));
			effectMenu->Check(IDC_EFFECT_MENU_BLOOM, mBloom);

			effectMenu->AppendCheckItem(IDC_EFFECT_MENU_LIGHT_SHAFT, wxT("�����"));
			effectMenu->Check(IDC_EFFECT_MENU_LIGHT_SHAFT, mLightShaft);
		}

		wxMenu *sceneMenu = new wxMenu;
		mMenuBar->Append(sceneMenu, wxT("��������"));
		{
			sceneMenu->Append(IDC_SCENE_MENU_LIGHT_COLOR_AMBIENT, wxT("������"));
			sceneMenu->Append(IDC_SCENE_MENU_LIGHT_COLOR_DIFFUSE, wxT("�������"));
			sceneMenu->Append(IDC_SCENE_MENU_LIGHT_COLOR_SPECULAR, wxT("���淴���"));
			sceneMenu->Append(IDC_SCENE_MENU_LIGHT_COLOR_DEFAULT, wxT("Ĭ�ϵƹ���ɫ"));
			sceneMenu->AppendSeparator();

			sceneMenu->Append(IDC_SCENE_MENU_BACKGROUND_COLOR, wxT("������ɫ"));
		}

		wxMenu *helpMenu = new wxMenu;
		mMenuBar->Append(helpMenu, wxT("����"));
		{
			helpMenu->Append(IDC_HELP_MENU_HELP, wxT("ʹ��˵��"));
			helpMenu->Append(IDC_HELP_MENU_ABOUT, wxT("����"));
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
				wxRibbonPanel *panel = new wxRibbonPanel(page, wxID_ANY, wxT("����"));

				wxRibbonButtonBar *btnbar = new wxRibbonButtonBar(panel);
				btnbar->AddButton(IDC_BTN_SMALLER, wxT("��С"), wxArtProvider::GetBitmap(wxART_MINUS));
				btnbar->AddButton(IDC_BTN_LARGER, wxT("�Ŵ�"), wxArtProvider::GetBitmap(wxART_PLUS));
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
			wxRibbonPanel *panel = new wxRibbonPanel(page, wxID_ANY, wxT("���ӷ�����"));

			wxRibbonButtonBar *btnbar = new wxRibbonButtonBar(panel);
			btnbar->AddButton(IDC_BTN_SAVEMEX, wxT("����Mex�ļ�"), wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_OTHER, wxSize(20, 20)));
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
	// ��ȡ������Ϣ
	mConfig = new wxConfig(REGKEY_APP_NAME, REGKEY_VENDOR_NAME);

	if (!mConfig->Read(REGKEY_LAST_FOLDER, &mLastPath))
	{
		// ���ע�����û������, ��Ĭ��ΪD��
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
	// ����������Ϣ
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

	// ֻ����������ӱ༭����ģ��
	if (!obj->HasParticleEmitters())
	{
		wxMessageBox(wxT("���ܱ���û�����ӷ�������ģ��"));
		return false;
	}

	// ֻ�е�ǰѡ�е������ӱ�ǩҳ, �ſ��Ա���Mex�ļ�
	if (mRibbonBar->GetActivePage() != 2)
	{
		wxMessageBox(wxT("û����Ҫ��������ӷ�����\n���л������ӱ༭\n�޸����ӷ������������ٱ���Mex�ļ�"));
		return false;
	}

	// �������ӷ���������
	if (!mRightWnd->SaveCurrentParticleEmitterParams())
		return false;

	wxString desc = wxString::Format(wxT("���ڱ���Mex�ļ�: %s"), obj->GetFileName());
	wxProgressDialog dlg(wxT("�����ļ�"), desc, 10, this, wxPD_APP_MODAL);
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
	else if (pageName == RIBBON_BAR_PAGE_NAME_MODEL_CONFIG) //ģ������
	    mRightWnd->ShowChildByType(RightWindow::ChildWnd_ModelConfig);
	else
		wxMessageBox(wxT("���ش���, Page������"));
}

void MainFrame::OnRibbonBtnBarClicked_Smaller(wxRibbonButtonBarEvent &WXUNUSED(evt))
{
	if (mMiddleWnd->GetRenderHelper()->GetCurrentModel() == NULL)
		return;

	mMiddleWnd->GetRenderHelper()->GetCurrentModel()->ToLargerOrSmaller(false);
	mMiddleWnd->GetRenderHelper()->GetCurrentModel()->ApplyTransform();

	// ֪ͨ�ұߴ���ˢ��
	mRightWnd->UpdateInfoByChildType(RightWindow::ChildWnd_ModelInfo);
}

void MainFrame::OnRibbonBtnBarClicked_Larger(wxRibbonButtonBarEvent &WXUNUSED(evt))
{
	if (mMiddleWnd->GetRenderHelper()->GetCurrentModel() == NULL)
		return;

	mMiddleWnd->GetRenderHelper()->GetCurrentModel()->ToLargerOrSmaller(true);
	mMiddleWnd->GetRenderHelper()->GetCurrentModel()->ApplyTransform();

	// ֪ͨ�ұߴ���ˢ��
	mRightWnd->UpdateInfoByChildType(RightWindow::ChildWnd_ModelInfo);
}

void MainFrame::OnRibbonBtnBarClicked_SaveMex(wxRibbonButtonBarEvent &WXUNUSED(evt))
{
	this->SaveCurrentModelMexFile();
}

void MainFrame::OnMenuItemOpen(wxCommandEvent &WXUNUSED(event))
{
	wxFileDialog dlg(this, wxT("��Mex�ļ�"), wxT("D:\\"), wxEmptyString,
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
				// ��Uncheck
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
				// ��ʾ/����������
				mShowLeftWindow = !mLeftWnd->IsShown();
				mLeftWnd->Show(!mLeftWnd->IsShown());
			}
			else if (event.GetId() == IDC_SHOW_MENU_SHOW_RIGHTWND)
			{
				// ��ʾ/�����ұ����
				mShowRightWindow = !mRightWnd->IsShown();
				mRightWnd->Show(mShowRightWindow);
			}

			// α��OnSize��Ϣ
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
			wxMessageBox(MEXVIEWER_HELP_MSG, wxT("ʹ��˵��"));
		}
		break;

	case IDC_HELP_MENU_ABOUT:
		{
			wxAboutDialogInfo info;
			info.SetName(wxT("Mexģ�Ͳ鿴��"));
			info.SetVersion(wxT("0.0.1"));
			info.SetDescription(wxT("Mexģ�Ͳ鿴��"));
			info.SetCopyright(wxT("(C) 2008-2012 �������� Dev Team"));
			info.SetWebSite(wxT("http://www.tolez.com/"), wxT("��������Ƽ�"));
			info.AddDeveloper(wxT("��˧"));
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

	if (mLeftWnd->IsShown() && mRightWnd->IsShown()) // ������嶼��ʾ
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
	else if (mLeftWnd->IsShown()) // ֻ���������ʾ
	{
		mLeftWnd->SetPosition(wxPoint(0, GetRibbonBarHeight()));
		mLeftWnd->SetSize(clientSize.GetWidth() * MEXVIEWER_LEFT_WND_RATIO, h);

		mMiddleWnd->SetPosition(wxPoint(mLeftWnd->GetSize().GetWidth(), GetRibbonBarHeight()));
		mMiddleWnd->SetSize(clientSize.GetWidth() * (1.0f - MEXVIEWER_LEFT_WND_RATIO), h - MEXVIEWER_FRAME_WND_HEIGHT);
	}
	else if (mRightWnd->IsShown()) // ֻ���������ʾ
	{
		mMiddleWnd->SetPosition(wxPoint(0, GetRibbonBarHeight()));
		mMiddleWnd->SetSize(clientSize.GetWidth() * (1.0f - MEXVIEWER_RIGHT_WND_RATIO), h - MEXVIEWER_FRAME_WND_HEIGHT);

		mRightWnd->SetPosition(wxPoint(
			mMiddleWnd->GetSize().GetWidth(),
			GetRibbonBarHeight()));
		mRightWnd->SetSize(clientSize.GetWidth() * MEXVIEWER_RIGHT_WND_RATIO, h);
	}
	else // ������嶼����
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