// UIEditor.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "UIEditor.h"
#include "MainFrm.h"
#include <assert.h>
#include <mmsystem.h>

#pragma comment(lib,"WinMM.lib")
//#pragma comment(lib, "SkinMagicLibMT7Trial.lib")

#include "UIEditorDoc.h"
#include "UIEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

E_AppState g_enState = State_Dialog;
char	g_stPath[MAX_PATH] = "";
char	g_stFileName[MAX_PATH] = "";

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CUIEditorApp

BEGIN_MESSAGE_MAP(CUIEditorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_EDIT_ADD_BUTTON, OnEditAddButton)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_BUTTON, OnUpdateEditAddButton)
	ON_COMMAND(ID_EDIT_ADD_CHECKBOX, OnEditAddCheckbox)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_CHECKBOX, OnUpdateEditAddCheckbox)
	ON_COMMAND(ID_EDIT_ADD_EDIT, OnEditAddEdit)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_EDIT, OnUpdateEditAddEdit)
	ON_COMMAND(ID_EDIT_ADD_TEXT, OnEditAddText)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_TEXT, OnUpdateEditAddText)
	ON_COMMAND(ID_EDIT_ADD_LIST, OnEditAddList)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_LIST, OnUpdateEditAddList)
	ON_COMMAND(ID_EDIT_ADD_LISTIMG, OnEditAddListimg)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_LISTIMG, OnUpdateEditAddListimg)
	ON_COMMAND(ID_EDIT_ADD_POINT, OnEditAddPoint)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_POINT, OnUpdateEditAddPoint)
	ON_COMMAND(ID_EDIT_ADD_SCROLLBAR, OnEditAddScrollbar)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_SCROLLBAR, OnUpdateEditAddScrollbar)
	ON_COMMAND(ID_EDIT_ADD_SCROLLBAREX, OnEditAddScrollbarEx)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_SCROLLBAREX, OnUpdateEditAddScrollbarEx)
	ON_COMMAND(ID_EDIT_ADD_COMBO_BOX, OnEditAddComboBox)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_COMBO_BOX, OnUpdateEditAddComboBox)
	ON_COMMAND(ID_EDIT_ADD_PICTURE, OnEditAddPicture)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_PICTURE, OnUpdateEditAddPicture)
	ON_COMMAND(ID_EDIT_ADD_PROGRESS, OnEditAddProgress)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_PROGRESS, OnUpdateEditAddProgress)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_TESTDLG, OnEditTestdlg)
	ON_COMMAND(ID_EDIT_ADD_TAB, OnEditAddTab)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_TAB, OnUpdateEditAddTab)
	ON_COMMAND(ID_EDIT_ADD_LISTEX, OnEditAddListex)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_LISTEX, OnUpdateEditAddListex)
	ON_COMMAND(ID_EDIT_ADD_TREE, OnEditAddTree)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD_TREE, OnUpdateEditAddTree)
END_MESSAGE_MAP()


// CUIEditorApp 构造

CUIEditorApp::CUIEditorApp()
{
	m_enOperateType	= Type_Normal;
	m_bUpdateView = false;

	srand( timeGetTime() );

//	::GetCurrentDirectory( MAX_PATH, g_stRootPath );
}


// 唯一的一个 CUIEditorApp 对象

CUIEditorApp theApp;

// CUIEditorApp 初始化

BOOL CUIEditorApp::InitInstance()
{
	////===SkinMagic===
	//VERIFY( 1 == InitSkinMagicLib( AfxGetInstanceHandle(), "Demo" , NULL, NULL ) );
	//VERIFY( 1 == LoadSkinFromResource( AfxGetInstanceHandle(), "DEFAULT", "SKINMAGIC" ) );
	////===SkinMagic===
	
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	CMenuXP::InitializeHook();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项（包括 MRU）
	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CUIEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CUIEditorView));
	AddDocTemplate(pDocTemplate);
	// 启用“DDE 执行”
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当存在后缀时才调用 DragAcceptFiles，
	//  在 SDI 应用程序中，这应在 ProcessShellCommand  之后发生
	// 启用拖/放
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

// 用于运行对话框的应用程序命令
void CUIEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CUIEditorApp 消息处理程序
void CUIEditorApp::OnEditAddButton()
{
	m_enOperateType = Type_Button;
	m_bUpdateView = true;
}
void CUIEditorApp::OnEditAddCheckbox()
{
	m_enOperateType = Type_CheckBox;
	m_bUpdateView = true;
}
void CUIEditorApp::OnEditAddEdit()
{
	m_enOperateType = Type_Edit;
	m_bUpdateView = true;
}
void CUIEditorApp::OnEditAddText()
{
	m_enOperateType = Type_Text;
	m_bUpdateView = true;
}
void CUIEditorApp::OnEditAddList()
{
	m_enOperateType = Type_List;
	m_bUpdateView = true;
}
void CUIEditorApp::OnEditAddListimg()
{
	m_enOperateType = Type_ListImg;
	m_bUpdateView = true;
}
void CUIEditorApp::OnEditAddScrollbar()
{
	m_enOperateType = Type_ScrollBar;
	m_bUpdateView = true;
}
void CUIEditorApp::OnEditAddScrollbarEx()
{
	m_enOperateType = Type_ScrollBarEx;
	m_bUpdateView = true;
}
void CUIEditorApp::OnEditAddComboBox()
{
	m_enOperateType = Type_ComboBox;
	m_bUpdateView = true;
}

void CUIEditorApp::OnEditAddPicture()
{
	m_enOperateType = Type_Picture;
	m_bUpdateView = true;
}

void CUIEditorApp::OnEditAddProgress()
{
	m_enOperateType = Type_Progress;
	m_bUpdateView = true;
}

void CUIEditorApp::OnEditAddTree()
{
	return;
	/*m_enOperateType = Type_Tree;*/
	m_bUpdateView = true;
}

void CUIEditorApp::OnUpdateEditAddButton(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_Button, pCmdUI );
}
void CUIEditorApp::OnUpdateEditAddCheckbox(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_CheckBox, pCmdUI );
}
void CUIEditorApp::OnUpdateEditAddEdit(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_Edit, pCmdUI );
}
void CUIEditorApp::OnUpdateEditAddText(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_Text, pCmdUI );
}
void CUIEditorApp::OnUpdateEditAddList(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_List, pCmdUI );
}
void CUIEditorApp::OnUpdateEditAddListimg(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_ListImg, pCmdUI );
}
void CUIEditorApp::OnUpdateEditAddScrollbar(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_ScrollBar, pCmdUI );
}
void CUIEditorApp::OnUpdateEditAddScrollbarEx(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_ScrollBarEx, pCmdUI );
}
void CUIEditorApp::OnUpdateEditAddComboBox(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_ComboBox, pCmdUI );
}

void CUIEditorApp::OnUpdateEditAddPicture(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_Picture, pCmdUI );
}

void CUIEditorApp::OnUpdateEditAddProgress(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_Progress, pCmdUI );
}

void CUIEditorApp::OnUpdateEditAddTree(CCmdUI *pCmdUI)
{
	/*RefeashOperatorType( Type_Tree, pCmdUI );*/
}

void CUIEditorApp::RefeashOperatorType( const E_ControlType enType, CCmdUI* pCmdUI )
{
	if ( m_enOperateType == enType )
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

BOOL CUIEditorApp::OnIdle(LONG lCount)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( thePropertyDlg.IsUpdate() )
	{
		switch( g_enState )
		{
		case State_Dialog:
			{
				theUIObjectDlg.UpdateDialogName();
			}
			break;
		case State_Control:
			{
				theUIObjectDlg.UpdateControlName();
			}
			break;
		case State_Pic:
			break;
		default:
			assert( false );
			break;
		}
		GetDoc()->UpdateAllViews(NULL);
	}
	else if ( m_bUpdateView == true )
	{
		m_bUpdateView = false;
		GetDoc()->UpdateAllViews(NULL);
	}

	return CWinApp::OnIdle(lCount);
}

void CUIEditorApp::OnEditAddPoint()
{
	m_enOperateType = Type_Normal;
	m_bUpdateView = true;
}

void CUIEditorApp::OnUpdateEditAddPoint(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_Normal, pCmdUI );
}


int CUIEditorApp::ExitInstance()
{
//	ExitSkinMagicLib();
	CMenuXP::UninitializeHook();
	return CWinApp::ExitInstance();
}

void CUIEditorApp::OnEditCopy()
{
	theUIObjectDlg.Copy();
	m_bUpdateView = true;
}

void CUIEditorApp::OnEditPaste()
{
	theUIObjectDlg.Paste();
	m_bUpdateView = true;
}

void CUIEditorApp::OnEditCut()
{
	theUIObjectDlg.Cut();
	m_bUpdateView = true;
}

void CUIEditorApp::OnEditTestdlg()
{
	char szResultString[128];
	if( theUIObjectDlg.TestDialog( szResultString ) == true )
	{
		MessageBox( AfxGetMainWnd()->m_hWnd, szResultString, "成功", MB_ICONINFORMATION );
	}
	else
	{
		MessageBox( AfxGetMainWnd()->m_hWnd, szResultString, "有错误", MB_ICONSTOP );
	}
}

void CUIEditorApp::OnEditAddTab()
{
	return;
	m_enOperateType = Type_Tab;
	m_bUpdateView = true;
}

void CUIEditorApp::OnUpdateEditAddTab(CCmdUI *pCmdUI)
{
	//RefeashOperatorType( Type_Tab, pCmdUI );
}

void CUIEditorApp::OnEditAddListex()
{
	m_enOperateType = Type_ListEx;
	m_bUpdateView = true;
}

void CUIEditorApp::OnUpdateEditAddListex(CCmdUI *pCmdUI)
{
	RefeashOperatorType( Type_ListEx, pCmdUI );
}
