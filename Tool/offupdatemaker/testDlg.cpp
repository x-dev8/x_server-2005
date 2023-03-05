// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include <direct.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void SetError(CString str)
{
	CtestDlg * dlg=   ( CtestDlg * ) AfxGetApp()-> GetMainWnd();
	int nLength = ((CEdit *)dlg->GetDlgItem(IDC_EDIT1))->SendMessage(WM_GETTEXTLENGTH);
	((CEdit *)dlg->GetDlgItem(IDC_EDIT1))->SetSel(nLength, nLength);
	((CEdit *)dlg->GetDlgItem(IDC_EDIT1))->ReplaceSel( str);
}

void SetTip(CString str)
{
	CtestDlg * dlg=   ( CtestDlg * ) AfxGetApp()-> GetMainWnd();
	dlg->GetDlgItem(IDC_STATIC1)->SetWindowText(str);
}

void SetProgress(int pos)
{
	CtestDlg * dlg=   ( CtestDlg * ) AfxGetApp()-> GetMainWnd();
	((CProgressCtrl *)dlg->GetDlgItem(IDC_PROGRESS1))->SetPos(pos);
}




void DeleteDir(const char* strDir)
{
	string  path = strDir;

	//如果路径最后面没有跟上"\\"则加上
	if (path.size() > 0 && '\\' != path[path.size() - 1])
	{
		path.append("\\");
	}

	////string file = fext;
	string  file = _T("*.*");
	string  s = path + file;
	WIN32_FIND_DATA fileinfo ={0};
	HANDLE handle = FindFirstFile(s.c_str(),&fileinfo);

	if(NULL !=handle && INVALID_HANDLE_VALUE != handle)
	{
		do 
		{
			if (_T('.') != fileinfo.cFileName[0])
				if ((FILE_ATTRIBUTE_DIRECTORY & fileinfo.dwFileAttributes)
					== FILE_ATTRIBUTE_DIRECTORY)	//--目录
				{
					string filedir;
					filedir = path+fileinfo.cFileName;
					DeleteDir(filedir.c_str());

				}else
				{
					string filename;
					filename=path+fileinfo.cFileName;
					remove(filename.c_str());
				}
		} while (FindNextFile(handle, &fileinfo));

		FindClose(handle);
		RemoveDirectory(strDir);
	}
}
BOOL FreeSource_3(LPCTSTR szFileName,LPCTSTR pszResName,LPCTSTR pszResType)   
{   
	BOOL bRet = TRUE;   
	HINSTANCE hInst = GetModuleHandle(NULL);   

	//判断指定的资源是否存在   
	HRSRC hResInfo = FindResource(hInst,pszResName,pszResType);   
	if(hResInfo == NULL)   
		return FALSE;   

	HANDLE hFile = NULL;   
	DWORD dwWritten = 0;   
	//调入指定的资源到内存   
	HGLOBAL hResData = LoadResource(hInst,hResInfo);   
	LPVOID pvResData = LockResource(hResData);   
	DWORD dwResSize = SizeofResource(hInst,hResInfo);   

	//创建目标文件并保存数据至文件   
	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);   
	if(pszResType == RT_BITMAP)   
	{   
		//获得位图信息头   
		BITMAPINFOHEADER bmpInfoHdr;   
		CopyMemory(&bmpInfoHdr, pvResData, sizeof(BITMAPINFOHEADER));   
		//获得位图颜色表中RGBQUAD结构的个数   
		long nColorEntries;   
		switch(bmpInfoHdr.biBitCount)   
		{   
		case 1:   
			nColorEntries = 2;   
			break;   
		case 4:   
			nColorEntries = 16;   
			break;   
		case 8:   
			nColorEntries = 256;   
			break;   
		default:   
			nColorEntries = 0;   
		}   
		//根据位图信息头创建位图文件头   
		BITMAPFILEHEADER bmpFileHdr;   
		bmpFileHdr.bfType = 0x4d42;  // 'BM'   
		bmpFileHdr.bfSize = sizeof(BITMAPINFOHEADER) + dwResSize;   
		bmpFileHdr.bfReserved1 = bmpFileHdr.bfReserved2 = 0;   
		bmpFileHdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * nColorEntries;   
		//写入位图文件头   
		WriteFile(hFile, &bmpFileHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);   
	}   
	WriteFile(hFile, pvResData, dwResSize, &dwWritten, NULL);   
	//释放有关内存资源   
	CloseHandle(hFile);   
	FreeResource(hResData);   
	return TRUE;   
}; 

BOOL Replace(LPCTSTR lpszApp, LPCTSTR lpszICO,int id)   
{   
	HANDLE    hICO;   


	CFile mFile;
	if(!mFile.Open(lpszICO,CFile::modeRead))
	{
		CString pic=lpszICO;
		pic+=_T("加载失败：路径不存在"); 
		return false;
	}
	int dwSize=mFile.GetLength();
	char * lpRsrc=new char[mFile.GetLength()];
	mFile.Read(lpRsrc,mFile.GetLength()); 
	HANDLE    hApp;   
	if (NULL == (hApp = ::BeginUpdateResource(lpszApp, NULL)))   
	{   
		return FALSE;   
	}   
	//标记更新资源   
	bool i=::UpdateResource(hApp, "TEX"  , MAKEINTRESOURCE(id),MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (LPVOID)lpRsrc, dwSize);  
	//写入新资源   
	int error=0;   
	if (!::EndUpdateResource(hApp, FALSE))   
	{ 
		error=GetLastError();   
		SetError("添加日志失败");SetTip("添加日志失败");
		return FALSE;   
	}   
	mFile.Close(); delete lpRsrc;SetError("添加日志成功");SetTip("添加日志成功");
	return TRUE;   
}  

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CtestDlg dialog




CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CtestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CtestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CtestDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CtestDlg message handlers

BOOL CtestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	FreeSource_3(".\\ReadMe1.txt",MAKEINTRESOURCE(IDR_TEXT1),"Text"); 
	CStdioFile F;
	CString str1,str2;
	if(F.Open(_T(".\\ReadMe1.txt"),CFile::modeRead|CFile::typeText))
	{
		while(F.ReadString(str1))
		{
			str2+=str1;
			str2+="\r\n";
		}
		SetDlgItemText(IDC_EDIT1,str2);
		F.Close();
		DeleteFile(".\\ReadMe1.txt");
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
CString exepath;
CString sFileName;
CString sLogName;


void CtestDlg::OnBnClickedButton1()
{
	CFileDialog dlg(TRUE); 
	if ( dlg.DoModal()!=IDOK ) return;
	sFileName=dlg.GetPathName();
	
	GetDlgItem(IDC_EDIT3)->SetWindowText(sFileName);
}

void CtestDlg::OnBnClickedButton2()
{
	CFileDialog dlg(TRUE); 
    if ( dlg.DoModal()!=IDOK ) return;
    exepath=dlg.GetPathName();
	
	GetDlgItem(IDC_EDIT2)->SetWindowText(exepath);
}

void CtestDlg::OnBnClickedButton3()
{	
	CFileDialog dlg(TRUE); 
	if ( dlg.DoModal()!=IDOK ) return;
	sLogName=dlg.GetPathName();
	
	GetDlgItem(IDC_EDIT4)->SetWindowText(sLogName);
}
/*
#define SHOW_STR_IN_TEXT(str,IDC_EDIT2)\
	do{\
	CWnd * dlg=   ( CWnd * ) AfxGetApp()-> GetMainWnd();;\
	int nLength = ((CEdit *)GetDlgItem(IDC_EDIT2))->SendMessage(WM_GETTEXTLENGTH);\
	((CEdit *)GetDlgItem(IDC_EDIT2))->SetSel(nLength, nLength);\
	((CEdit *)GetDlgItem(IDC_EDIT2))->ReplaceSel( str); \
	}while(0);*/



ULONG  WINAPI Thread(LPVOID Param)
{
	if(exepath.IsEmpty()&&sFileName.IsEmpty())
	{

		::MessageBox(NULL,"请设置路径","提示",MB_OK);
	}
	
	if(!sLogName.IsEmpty())
	{
		Replace(exepath, sLogName,11) ;
	}

	
	
	CFile mFile,mFiled;
	if(!mFile.Open(sFileName,CFile::modeRead))
	{
		SetError("打开更新包源文件失败");SetTip("打开更新包源文件失败");
		return 0;
	}
	if(!mFiled.Open(exepath,CFile::modeWrite))
	{
		SetError("打开EXE目的文件失败");SetTip("打开EXE目的文件失败");
		return 0;
	}

	char * lpRsrc=new char[1024];
	mFiled.SeekToEnd();
	mFile.SeekToBegin();
	int len=mFile.GetLength();
	int iWrite=0;
	while(1) 
	{ 
		int   i   =mFile.Read(lpRsrc,1024 ); 
		mFiled.Write(lpRsrc,i);
		iWrite=iWrite+1024;

		int pos=(iWrite/10)/(len/1000);
		SetProgress(pos);
		CString s;
		s.Format("%d,%d,%d",iWrite,len,pos);
SetTip(s);
		if(i < 1024) 
			break; 
	}
	mFile.Close(); 
	mFiled.Close();
	delete lpRsrc;
	SetError("写入成功");SetTip("写入成功");

/*
	TCHAR szFilePath2[MAX_PATH + 1];	
	TCHAR szFilePath[MAX_PATH + 1]; 
	GetModuleFileName(NULL, szFilePath, MAX_PATH); 
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	strncpy(szFilePath2,szFilePath,MAX_PATH);
	//    strcat(szFilePath2,"update.exe");
	CString s;
	s.Format("%s",szFilePath2);
	//s=szFilePath2+exepath;AfxMessageBox(s);
//	Replace(exepath, sFileName,11) ;
	FolderFileList pack;
	pack.PackIn("D:\\RTP","c:\\update.exe");

	/*	TCHAR szFilePath2[MAX_PATH + 1];	
	TCHAR szFilePath[MAX_PATH + 1]; 
	GetModuleFileName(NULL, szFilePath, MAX_PATH); 
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	strcat(szFilePath,"update.exe"); */

	//AfxMessageBox(szFilePath);


	/*	CFileDialog dlg(TRUE); 
	if ( dlg.DoModal()!=IDOK ) return;
	CString sFileName=dlg.GetPathName();
	TCHAR szFilePath2[MAX_PATH + 1];	
	TCHAR szFilePath[MAX_PATH + 1]; 
	GetModuleFileName(NULL, szFilePath, MAX_PATH); 
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	strncpy(szFilePath2,szFilePath,MAX_PATH);

	CString str_url =  szFilePath;

	strcat(szFilePath,"tt");

	if (_mkdir(szFilePath) == ENOENT)
	{


	}
	else
	{


	}
	TCHAR szFilePath1[MAX_PATH + 1]; 	
	strncpy(szFilePath1,szFilePath,MAX_PATH);
	strcat(szFilePath,"\\");
	strcat(szFilePath,dlg.GetFileName());
	CopyFile(sFileName,szFilePath,false);

	FolderFileList d;strcat(szFilePath2,"update.exe");
	d.PackIn(szFilePath1,szFilePath2);
	DeleteDir(szFilePath1);
	*/
	/*FolderFileList d;
	d.PackIn(_T("C:\\tt"),_T("C:\\update-off\\release\\update.exe"));// TODO: Add your control notification handler code here
	*/


	return 0;
}
void CtestDlg::OnBnClickedButton4()
{
	DWORD ThreadID=0;
	HANDLE hThread = 
	::CreateThread(
		NULL,0,  
		Thread,
		(LPVOID)(0),0,
		&ThreadID
		);
}
