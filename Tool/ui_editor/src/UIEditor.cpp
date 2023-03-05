// UIEditor.cpp : ����Ӧ�ó��������Ϊ��
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// ��׼��ӡ��������
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


// CUIEditorApp ����

CUIEditorApp::CUIEditorApp()
{
	m_enOperateType	= Type_Normal;
	m_bUpdateView = false;

	srand( timeGetTime() );

//	::GetCurrentDirectory( MAX_PATH, g_stRootPath );
}


// Ψһ��һ�� CUIEditorApp ����

CUIEditorApp theApp;

// CUIEditorApp ��ʼ��

BOOL CUIEditorApp::InitInstance()
{
	////===SkinMagic===
	//VERIFY( 1 == InitSkinMagicLib( AfxGetInstanceHandle(), "Demo" , NULL, NULL ) );
	//VERIFY( 1 == LoadSkinFromResource( AfxGetInstanceHandle(), "DEFAULT", "SKINMAGIC" ) );
	////===SkinMagic===
	
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	CMenuXP::InitializeHook();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ����� MRU��
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CUIEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CUIEditorView));
	AddDocTemplate(pDocTemplate);
	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������ں�׺ʱ�ŵ��� DragAcceptFiles��
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand  ֮����
	// ������/��
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

// �������жԻ����Ӧ�ó�������
void CUIEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CUIEditorApp ��Ϣ�������
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
	// TODO: �ڴ����ר�ô����/����û���
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
		MessageBox( AfxGetMainWnd()->m_hWnd, szResultString, "�ɹ�", MB_ICONINFORMATION );
	}
	else
	{
		MessageBox( AfxGetMainWnd()->m_hWnd, szResultString, "�д���", MB_ICONSTOP );
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
