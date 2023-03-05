// BinDataBuilder.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "BinDataBuilder.h"
#include "main_frame.h"

#include "child_frame.h"
#include "doc.h"
#include "view.h"
#include "application_config.h"
#include "compile_dialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//extern CCompileDlg* GetCompileDlg();
static CCompileDlg* gs_pCompileDlg = NULL;
CCompileDlg* GetCompileDlg()
{
	return gs_pCompileDlg;
}
// CBinDataBuilderApp

BEGIN_MESSAGE_MAP(CBinDataBuilderApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CBinDataBuilderApp ����

CBinDataBuilderApp::CBinDataBuilderApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CItemFactoryApp ����

CBinDataBuilderApp theApp;

// CBinDataBuilderApp ��ʼ��

BOOL CBinDataBuilderApp::InitInstance()
{
	//AfxMessageBox( "" );
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
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_ItemFactoryTYPE,
		RUNTIME_CLASS(CItemFactoryDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CItemFactoryView));
	AddDocTemplate(pDocTemplate);	

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow( SW_HIDE );
	pMainFrame->UpdateWindow();

    gs_pCompileDlg = new CCompileDlg;
    gs_pCompileDlg->Create( CCompileDlg::IDD, m_pMainWnd ); 
    gs_pCompileDlg->ShowWindow( SW_SHOWNORMAL );
    gs_pCompileDlg->CenterWindow();

    ShowVersionInformation();
	return TRUE;
}



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

// �������жԻ����Ӧ�ó�������
void CBinDataBuilderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CBinDataBuilderApp ��Ϣ�������


int CBinDataBuilderApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	if( gs_pCompileDlg )
	{
		delete gs_pCompileDlg;
	}

	return CWinApp::ExitInstance();
}


void CBinDataBuilderApp::ShowVersionInformation()
{
    CString strVersion = "";

    strVersion.Format("������� %s", ApplicationConfig::Instance().GetFullVersion());

    if ( gs_pCompileDlg != NULL )
    {
        gs_pCompileDlg->SetWindowText(strVersion);
    }
}