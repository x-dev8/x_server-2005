// updateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "update.h"
#include "updateDlg.h"
#include "tstring.h"
#include "packet_interface.h"

#include "datafile.h"
#include <math.h>
#include "DlgSelectPath.h"
#include"tlhelp32.h"
#include <map>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

SkinImgMgr  ImgMgr; //���ڹ������е�ͼƬ��Դ������������Ի��򱳾�ͼƬ

char g_szUpdatePack[MAX_PATH] = "temp"; //qh 2011 3 16
char g_szUpdateFile[MAX_PATH] = ".\\UpData\\update.xml";//��ǰ�汾���ļ�
std::map<int, std::string>	m_mapStringSet;
using FileIO::CVFS;
using FileIO::CZipWrapper;
map<_tstring, CVFS*> vfslist;
/*
CHttpDownload GHttpDownload;
CINetDownLoad GInetDownload;
*/
volatile bool g_bIsEnd = false;//�жϸ��µı�־


char g_szCurPath[MAX_PATH] ;
bool ManuaPath=false;

BYTE langType=0;//0,���ģ�2��Ӣ�ģ�1������
//std::string g_szCurPath;
_tstring s_strVersion;//��ǰ�汾���ļ�

vector<AREASERVERIPINFO> s_iplist;	
vector<AREASERVERIPINFO> s_backupiplist;		//����IP

void SetTip(_tstring strInfo)
{
	//SetDlgItemText(theApp.GetMainWnd()->GetSafeHwnd(), IDC_TIP, strInfo.c_str());
	_tstring strNew;
	if(strInfo.length() > 60)
	{
		//int nLengh = strInfo.length();
		//strInfo.replace(5, 5+strInfo.length() - 50,strInfo.length() - 50, ".");
		//int offset = strInfo.find( " ");
		//_tstring strFirstSect = strInfo.substr(0, offset);
		_tstring strFirstSect = strInfo.substr(0, 50);
		//_tstring strSecondSect = strInfo.substr( offset + nLengh - 56, 56 - offset);
		strNew = strFirstSect + " ...";// + strSecondSect;
	}
	else
		strNew = strInfo;

	CString cstringText(strNew.c_str());
	CWnd * dlg=         AfxGetApp()-> GetMainWnd();
((CupdateDlg*) dlg)->textfile.text=cstringText;
	dlg->InvalidateRect(((CupdateDlg*) dlg)->textfile.rect);
	
//	::SendMessage(dlg->m_hWnd,WM_DRAW_TEXT,(WPARAM)strNew.c_str(),0);
//	if( GetPatchInstance() && !g_bIsEnd)
//		GetPatchInstance()->TextPrintOut(cstringText);
//
};


void DeleteDir(const char* strDir)
{
	_tstring path = strDir;

	//���·�������û�и���"\\"�����
	if (path.size() > 0 && '\\' != path[path.size() - 1])
	{
		path.append("\\");
	}

	////string file = fext;
	_tstring file = _T("*.*");
	_tstring s = path + file;
	WIN32_FIND_DATA fileinfo ={0};
	HANDLE handle = FindFirstFile(s.c_str(),&fileinfo);

	if(NULL !=handle && INVALID_HANDLE_VALUE != handle)
	{
		do 
		{
			if (_T('.') != fileinfo.cFileName[0])
				if ((FILE_ATTRIBUTE_DIRECTORY & fileinfo.dwFileAttributes)
					== FILE_ATTRIBUTE_DIRECTORY)	//--Ŀ¼
				{
					_tstring filedir;
					filedir = path+fileinfo.cFileName;
					DeleteDir(filedir.c_str());

				}else
				{
					_tstring filename;
					filename=path+fileinfo.cFileName;
					remove(filename.c_str());
				}
		} while (FindNextFile(handle, &fileinfo));

		FindClose(handle);
		RemoveDirectory(strDir);
	}
}
bool SetFileChangeTime(_tstring strFilePath, _tstring strFileTime)
{
	FILETIME filetime;

	size_t nPos = strFileTime.find(_T("|"));
	_tstring strHighTime = strFileTime.substr(0, nPos);
	_tstring strLowTime = strFileTime.substr(nPos+1, strFileTime.length()-nPos);
	filetime.dwHighDateTime = atol(_tANSICHAR(strHighTime));
	filetime.dwLowDateTime = atol(_tANSICHAR(strLowTime));

	HANDLE fileHandle = CreateFile(strFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

	if (fileHandle != INVALID_HANDLE_VALUE)
	{
		SetFileTime(fileHandle, (LPFILETIME)NULL, (LPFILETIME)NULL, &filetime);
	}
	else
	{
		return false;
	}
	CloseHandle(fileHandle);
	return true;
}


_tstring GetFileLength(_tstring& strFile)
{
	_tstring length = _T("0");
	fstream file(_tUNICODECHAR(strFile));
	if (!file.is_open())
	{
		return length;
	}

	file.seekg(0, std::ios::end);
	unsigned int nlength = file.tellg();
	if (nlength == 0)
	{
		return length;
	}
	else
	{
		length.Format(_T("%d"), nlength);
		return length;
	}
}

_tstring GetFileDate(_tstring& strFilePath)
{
	_tstring strDate;
	HANDLE fileHandle = CreateFile(strFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

	if( fileHandle == INVALID_HANDLE_VALUE )
	{
		CloseHandle(fileHandle);
		return strDate;
	}
	_BY_HANDLE_FILE_INFORMATION fileInfo;
	if(!GetFileInformationByHandle(fileHandle, &fileInfo))
	{
		CloseHandle(fileHandle);
		return strDate;
	}

	CloseHandle(fileHandle);
	strDate.Format(_T("%d|%d"), fileInfo.ftLastWriteTime.dwHighDateTime, fileInfo.ftLastWriteTime.dwLowDateTime);
	return strDate;
}

_tstring GetFileCrc(_tstring& strFilePath)
{
	_tstring strCrc;
	unsigned long nCrc = Crypto::CCRC32().GetFileCRC32(strFilePath.toNarrowString().c_str());
	strCrc.Format(_T("%d"), nCrc);
	return strCrc;
}

//��ȡ��Ŀ¼�����·���ļ�����
_tstring GetFolder(_tstring strPath, _tstring strFilePath)
{
	if (!strPath.empty() && strPath[strPath.length()-1] != _T('\\'))
	{
		strPath += _T("\\");
	}
	size_t nLength = strFilePath.length();
	size_t nPos = 0;
	for (size_t i = nLength; i>0; i--)
	{
		if (strFilePath[i-1] == _T('\\'))
		{
			nPos = i;
			break;
		}
	}
	if (nPos == strPath.length())
	{
		return _T("");
	}

	_tstring strFolder = strFilePath.substr(strPath.length(), nPos-strPath.length()-1);

	return strFolder;
}

//�����ļ���
_tstring GetFileName(_tstring& strFilePath)
{
	size_t nLength = strFilePath.length();
	size_t nPos = 0;
	for (size_t i = nLength; i>0; i--)
	{
		if (strFilePath[i-1] == _T('\\'))
		{
			nPos = i;
			break;
		}
	}
	_tstring strFileName = strFilePath.substr(nPos, strFilePath.length()-nPos);
	return strFileName;
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


// CupdateDlg dialog

CupdateDlg::CupdateDlg(CWnd* pParent /*=NULL*/)
: CDialog(CupdateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CupdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CupdateDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
    ON_MESSAGE(WM_DRAW_PROGRESS ,Message_DrawProgress)
    ON_MESSAGE(WM_DRAW_TEXT ,Message_DrawText)

	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()

	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CupdateDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CupdateDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


BOOL FreeSource_3(LPCTSTR szFileName,LPCTSTR pszResName,LPCTSTR pszResType)   
{   
	BOOL bRet = TRUE;   
	HINSTANCE hInst = GetModuleHandle(NULL);   

	//�ж�ָ������Դ�Ƿ����   
	HRSRC hResInfo = FindResource(hInst,pszResName,pszResType);   
	if(hResInfo == NULL)   
		return FALSE;   

	HANDLE hFile = NULL;   
	DWORD dwWritten = 0;   
	//����ָ������Դ���ڴ�   
	HGLOBAL hResData = LoadResource(hInst,hResInfo);   
	LPVOID pvResData = LockResource(hResData);   
	DWORD dwResSize = SizeofResource(hInst,hResInfo);   

	//����Ŀ���ļ��������������ļ�   
	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);   
	if(pszResType == RT_BITMAP)   
	{   
		//���λͼ��Ϣͷ   
		BITMAPINFOHEADER bmpInfoHdr;   
		CopyMemory(&bmpInfoHdr, pvResData, sizeof(BITMAPINFOHEADER));   
		//���λͼ��ɫ����RGBQUAD�ṹ�ĸ���   
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
		//����λͼ��Ϣͷ����λͼ�ļ�ͷ   
		BITMAPFILEHEADER bmpFileHdr;   
		bmpFileHdr.bfType = 0x4d42;  // 'BM'   
		bmpFileHdr.bfSize = sizeof(BITMAPINFOHEADER) + dwResSize;   
		bmpFileHdr.bfReserved1 = bmpFileHdr.bfReserved2 = 0;   
		bmpFileHdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * nColorEntries;   
		//д��λͼ�ļ�ͷ   
		WriteFile(hFile, &bmpFileHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);   
	}   
	WriteFile(hFile, pvResData, dwResSize, &dwWritten, NULL);   
	//�ͷ��й��ڴ���Դ   
	CloseHandle(hFile);   
	FreeResource(hResData);   
	return TRUE;   
};  


BOOL CupdateDlg::OnInitDialog()
{
#ifdef _DEBUG
	MessageBox("debug","debug",MB_OK);
#endif
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


	font.CreateFont( 20,                                          //   nHeight      
		0,                                                   //   nWidth      
		0,                                                   //   nEscapement    
		0,                                                   //   nOrientation      
		FW_NORMAL,                                   //   nWeight      
		FALSE,                                           //   bItalic      
		FALSE,                                           //   bUnderline      
		0,                                                   //   cStrikeOut      
		ANSI_CHARSET,                             //   nCharSet      
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision      
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision      
		DEFAULT_QUALITY,                       //   nQuality      
		DEFAULT_PITCH   |   FF_SWISS,     //   nPitchAndFamily        
		_T("΢���ź�"));   

	fontT.CreateFont( 17,                                          //   nHeight      
		0,                                                   //   nWidth      
		0,                                                   //   nEscapement    
		0,                                                   //   nOrientation      
		FW_NORMAL,                                   //   nWeight      
		FALSE,                                           //   bItalic      
		FALSE,                                           //   bUnderline      
		0,                                                   //   cStrikeOut      
		ANSI_CHARSET,                             //   nCharSet      
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision      
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision      
		DEFAULT_QUALITY,                       //   nQuality      
		DEFAULT_PITCH   |   FF_SWISS,     //   nPitchAndFamily        
		_T("΢���ź�"));  

	m_dwFlags = 0;
	m_brush.CreateSolidBrush(RGB(255,0,255));		//��������Ϊ�ۺ�ɫ

	//SetWindowsLong����������Ϊ�㼶����
	DWORD dwExStyle=GetWindowLong(m_hWnd,GWL_EXSTYLE);
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwExStyle|0x80000);
	//��SetLayeredWindowAttributes����͸��ɫΪ0������UpdateLayeredWindow��ʹ��Ҫ��Щ
	HMODULE hInst=LoadLibrary("User32.DLL");
	typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
	MYFUNC SetLayeredWindowAttributes = NULL;
	SetLayeredWindowAttributes=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes"); 
	SetLayeredWindowAttributes(this->GetSafeHwnd(),0xff00ff,0,1); 
	FreeLibrary(hInst); 
	// TODO: Add extra initialization here

	//���ע����Ƿ��м�¼
	CDlgSelectPath dlg;
	dlg.DoModal();
	if(GetFileAttributes(dlg.selPath)   ==   0xFFFFFFFF)   
	{   
		ManuaPath=false;
	} 
	else
	{ 
		ManuaPath=true;
	    strncpy(g_szCurPath,dlg.selPath,dlg.selPath.GetLength()-1);
    }

	//	LoadXML(".\\updatebk.xml");image=NULL;

	char *szValue="13,267,465,272";
	//	progressnow.image=ImgMgr.AddImgR(NULL,IDB_BITMAP3,"Bitmap");
	sscanf(szValue, "%d, %d, %d, %d", &progressnow.rect.left, &progressnow.rect.top, &progressnow.rect.right, &progressnow.rect.bottom);
	textfile.rect.left=progressnow.rect.left;textfile.rect.top=progressnow.rect.top-20;textfile.rect.right=progressnow.rect.right;textfile.rect.bottom=progressnow.rect.bottom-7;
	szValue="13,277,465,282";
	//	progresstotal.image=ImgMgr.AddImgR(NULL,IDB_BITMAP3,"Bitmap");
	sscanf(szValue, "%d, %d, %d, %d", &progresstotal.rect.left, &progresstotal.rect.top, &progresstotal.rect.right, &progresstotal.rect.bottom);

	FreeSource_3(".\\ReadMe1.txt",MAKEINTRESOURCE(11),"TEX"); 
	//	FreeSource_3(".\\ReadMe1.txt",MAKEINTRESOURCE(IDR_TEXT1),"Text"); 
	FreeSource_3(".\\bg1.bmp",MAKEINTRESOURCE(IDB_BITMAP1),RT_BITMAP); 
	FreeSource_3(".\\bg2.bmp",MAKEINTRESOURCE(IDB_BITMAP5),RT_BITMAP); 
	FreeSource_3(".\\bg3.bmp",MAKEINTRESOURCE(IDB_BITMAP6),RT_BITMAP); 
	FreeSource_3(".\\bg4.bmp",MAKEINTRESOURCE(IDB_BITMAP7),RT_BITMAP);   
	FreeSource_3(".\\bg5.bmp",MAKEINTRESOURCE(IDB_BITMAP8),RT_BITMAP); 

	btnclose.SubclassDlgItem(IDC_BUTTON2,this);
	btnclose.SetButtonImage(".\\bg5.bmp", RGB(0,0,255));

	progressnow.image=ImgMgr.AddImg(".\\bg3.bmp");
	progresstotal.image=ImgMgr.AddImg(".\\bg4.bmp");


	image=ImgMgr.AddImg(".\\bg1.bmp");
	btncancel.SubclassDlgItem(IDC_BUTTON1,this);btncancel.SetButtonImage(".\\bg2.bmp", RGB(0,0,255));
	btncancel.ShowWindow(SW_HIDE);
	DeleteFile(".\\bg1.bmp");DeleteFile(".\\bg2.bmp");DeleteFile(".\\bg3.bmp");DeleteFile(".\\bg4.bmp");DeleteFile(".\\bg5.bmp");

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
		((CEdit *)GetDlgItem(IDC_EDIT1))->SetReadOnly(TRUE); 
		F.Close();
		DeleteFile(".\\ReadMe1.txt");
	}
	if(!ManuaPath)
	{
		CFile file;
		if(!file.Open(_T(g_szUpdateFile),CFile::modeRead|CFile::typeText)) 
		{
			if(langType==0)
				AfxMessageBox("�뽫����ŵ���ϷĿ¼��");
			else if(langType==1)
				AfxMessageBox("Ո������ŵ��[��Ŀ��e");
			else if(langType==2)
				AfxMessageBox("Please program into the game directory");

			exit(0);
		}
		else
		{
			if (FindClientProcess(_T("Client.exe"))
				||FindClientProcess(_T("launcher.exe")))
			{
				MessageBox("��رտͻ��˺��Զ����³����ٽ��и���!","warning",MB_OK);
				return TRUE;
			}

			hHandle=CreateThread(NULL,0,UpdateThreadProc,NULL,0,NULL);
		}
	}
	else
	{
		if (FindClientProcess(_T("Client.exe"))
			||FindClientProcess(_T("launcher.exe")))
		{
			MessageBox("��رտͻ��˺��Զ����³����ٽ��и���!","warning",MB_OK);
			return TRUE;
		}
		hHandle=CreateThread(NULL,0,UpdateThreadProc,NULL,0,NULL);
	}
	
	//   SetTimer(1,50,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

bool CupdateDlg::FindClientProcess(LPCTSTR name)
{
	PROCESSENTRY32 pe;
	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	pe.dwSize=sizeof(PROCESSENTRY32);
	if(!Process32First(hSnapshot,&pe))
		return false;
	while(1)
	{
		pe.dwSize=sizeof(PROCESSENTRY32);
		if(Process32Next(hSnapshot,&pe)==FALSE)
			break;
		if(strcmp(pe.szExeFile,name)==0)
		{
			return true;
		}
	}
	CloseHandle(hSnapshot);
	return false;
}

void CupdateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CupdateDlg::OnPaint()
{
	/*if (IsIconic())
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
	*/
	
	//if ( !(m_dwFlags & DRAGGING) )
	{
		
	CPaintDC dc(this); // device context for painting
	Rect dest;
	dest.X=progressnow.rect.left;
	dest.Y=progressnow.rect.top;
	dest.Width=progressnow.rect.Width()*progressnow.percent/100;dest.Height=progressnow.rect.Height();

	CRect rtClient;
	GetClientRect(rtClient);
	Graphics graph(dc.m_hDC);

	if(progressnow.image)
		graph.DrawImage(progressnow.image,dest,0,0,progressnow.image->GetWidth()*progressnow.percent/100,progressnow.image->GetHeight(),UnitPixel);

	dest.X=progresstotal.rect.left;
	dest.Y=progresstotal.rect.top;
	dest.Width=progresstotal.rect.Width()*progresstotal.percent/100;dest.Height=progresstotal.rect.Height();
	if(progresstotal.image)
		graph.DrawImage(progresstotal.image,dest,0,0,progresstotal.image->GetWidth()*progresstotal.percent/100,progresstotal.image->GetHeight(),UnitPixel);


	CPoint textpt;
	textpt.x=progressnow.rect.left;
	textpt.y=progressnow.rect.top-15;

	dc.SelectObject(&fontT);   
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,255));
	dc.TextOut(textfile.rect.left,textfile.rect.top, textfile.text);
	}

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CupdateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CupdateDlg::LoadXML(CString filename)
{
	if( !m_TiXmlDoc.LoadFile(filename) )
	{
		return;
	}
	const char* szValue = NULL;

	m_TiElemRoot	= m_TiXmlDoc.FirstChildElement("root");
	if(m_TiElemRoot)
	{
/*		TiXmlElement* button1 = m_TiElemRoot->FirstChildElement("button1");
		if(button1 )
		{

			TiXmlElement* imagebtn = button1->FirstChildElement("image");
			if( imagebtn )
			{
				szValue = imagebtn->Attribute("file");
				if( szValue )
				{
					btncancel._szImg = szValue;
				}
			}
			TiXmlElement* imagerect = button1->FirstChildElement("rect");
			if( imagerect )
			{
				szValue = imagerect->Attribute("value");
				if( szValue )
				{
					sscanf( szValue, "%d, %d, %d, %d", &btninfo_ok._rc.left, &btninfo_ok._rc.top, &btninfo_ok._rc.right, &btninfo_ok._rc.bottom );
				}btninfo_ok._rc.right+=btninfo_ok._rc.left;btninfo_ok._rc.bottom+=btninfo_ok._rc.top;
			}
			TiXmlElement* imagetip = button1->FirstChildElement("tip");
			if( imagetip )
			{
				szValue = imagetip->Attribute("value");
				if( szValue )
				{
					btninfo_ok._szTip = szValue;
				}
			}
		} */
		TiXmlElement* lpWindow;
		lpWindow = m_TiElemRoot->FirstChildElement("progress1");
		if(lpWindow)
		{
			TiXmlElement* lpChild = lpWindow->FirstChildElement("image");
			if(lpChild)
			{
				szValue = lpChild->Attribute("file");
				if(szValue)  
					progressnow.image=ImgMgr.AddImg(szValue);

			}
			lpChild = lpChild->NextSiblingElement();
			if(lpChild)
			{
				szValue = lpChild->Attribute("value");  
				if(szValue)
				{	sscanf(szValue, "%d, %d, %d, %d", &progressnow.rect.left, &progressnow.rect.top, &progressnow.rect.right, &progressnow.rect.bottom);
				    textfile.rect.left=progressnow.rect.left;textfile.rect.top=progressnow.rect.top-20;textfile.rect.right=progressnow.rect.right;textfile.rect.bottom=progressnow.rect.bottom-7;
				}


			}

		}
		lpWindow = m_TiElemRoot->FirstChildElement("progress2");
		if(lpWindow)
		{
			TiXmlElement* lpChild = lpWindow->FirstChildElement("image");
			if(lpChild)
			{
				szValue = lpChild->Attribute("file");  
				if(szValue)  
					progresstotal.image=ImgMgr.AddImg(szValue);

			}
			lpChild = lpChild->NextSiblingElement();
			if(lpChild)
			{
				szValue = lpChild->Attribute("value");  
				if(szValue)
					sscanf(szValue, "%d, %d, %d, %d", &progresstotal.rect.left, &progresstotal.rect.top, &progresstotal.rect.right, &progresstotal.rect.bottom);

			}

		}	


	}
}


HBRUSH CupdateDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_DLG)
		return m_brush;
	return hbr;
}
using Common::_tstring;


BOOL CupdateDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rtClient;
	GetClientRect(rtClient);

	Graphics graph(pDC->m_hDC);
	if(image)
		graph.DrawImage (image,0, 0,rtClient.Width(),rtClient.Height());
	
	
	CPoint textpt;
	textpt.x=15;
	textpt.y=10;
	pDC->SelectObject(&font);   

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,0,0));
	if(langType==0)
	pDC->TextOut(textpt.x,textpt.y, "�Զ����¹�����");
	else if(langType==1)
		pDC->TextOut(textpt.x,textpt.y, "�ԄӸ��¹�����");
	else if(langType==2)
		pDC->TextOut(textpt.x,textpt.y, "Automatic Update Manager");
	return true;
	return CDialog::OnEraseBkgnd(pDC);
}

void CupdateDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ( !(m_dwFlags & DRAGGING) )
	{
		m_pntMouse = point;
		m_dwFlags |= DRAGGING;
		SetCapture();
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CupdateDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ( m_dwFlags & DRAGGING )
	{
		m_dwFlags &= ~DRAGGING;
		ReleaseCapture();
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CupdateDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ( m_dwFlags & DRAGGING )
	{
		RECT rect;
		GetWindowRect( &rect );

		rect.left += point.x - m_pntMouse.x;
		rect.top += point.y - m_pntMouse.y;

		SetWindowPos( NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE );


	}
	CDialog::OnMouseMove(nFlags, point);
}
LRESULT CupdateDlg::Message_DrawProgress(WPARAM wParam,LPARAM lParam)
{
	progress_message *mess=(progress_message *)wParam;
	if(mess->type==0)
	{
		progressnow.percent=((float)mess->downlen/(float)mess->totallen * 100);
		InvalidateRect(progressnow.rect,true);

	}
	if(mess->type==1)
	{
		progresstotal.percent=((float)mess->downlen/(float)mess->totallen * 100);
		InvalidateRect(progresstotal.rect,true);
    }

		return 0;
}
void FTPDownLoadProc(unsigned int nFileSize, unsigned int nCurrDownLoadSize)
{
	progress_message mess;
	mess.downlen=nCurrDownLoadSize;
	mess.totallen=nFileSize;
	mess.type=0;
	
	CWnd * dlg=         AfxGetApp()-> GetMainWnd();
	::SendMessage(dlg->m_hWnd,WM_DRAW_PROGRESS,(WPARAM)&mess,0);
	

}
LRESULT CupdateDlg::Message_DrawText(WPARAM wParam,LPARAM lParam)
{
	char *ss=(char *) wParam;
    textfile.text=ss;
	InvalidateRect(textfile.rect);

	return 0;

}

using FileIO::CVFS;

BOOL CheckVersionIsNeedPack(_tstring szCmpFile, _tstring strCmpVersion, _tstring& strNextVersion )
{
	TiXmlDocument versiondoc( szCmpFile.c_str() );
	if (!versiondoc.LoadFile())
	{
		//throw Common::CException(0, _T(m_mapStringSet[74].c_str()));
		return FALSE;
	}		
	//GetCur Version
	TiXmlElement* elementversion = versiondoc.FirstChildElement(_tUTF8CHAR(_T("NewVersion")));
	if (elementversion == NULL)
	{
		//throw Common::CException(0, _T(m_mapStringSet[75].c_str()));
	}

	_tstring strVersion;
	strVersion.fromUTF8(elementversion->GetText());

	//versiondoc.Get
	std::vector<VersionInfo> vtVI;
	//--------------
	const char* szValue;
	TiXmlElement* lpOldVer = versiondoc.FirstChildElement("OldVersion");
	if( lpOldVer )
	{
		TiXmlElement* lpVersion = lpOldVer->FirstChildElement("Version");
		while(lpVersion)
		{
			VersionInfo VI;
			szValue = lpVersion->Attribute("Cur");
			if( szValue )
			{
				VI.szCurVersion = szValue;
			}
			szValue = lpVersion->Attribute("Next");
			if(szValue)
			{
				VI.szNextVersion = szValue;
			}
			szValue = lpVersion->Attribute("NextPath");
			if(szValue)
			{
				VI.szPath = szValue;
			}
			szValue = lpVersion->Attribute("NeedPack");
			if(szValue)
			{
				if( stricmp( szValue, "TRUE") == 0 )
				{
					VI.bNeedPack = TRUE;
				}
				else
				{
					VI.bNeedPack = FALSE;
				}
			}
			else
			{
				VI.bNeedPack = FALSE;
			}

			vtVI.push_back( VI );
			lpVersion = lpVersion->NextSiblingElement("Version");
		}
	}

	for( int i=0; i<vtVI.size(); i++ )
	{
		if( vtVI[i].szCurVersion == strCmpVersion )
		{
			strNextVersion = vtVI[i].szNextVersion;
			return vtVI[i].bNeedPack;
		}
	}

	strNextVersion = strVersion;
	return TRUE;

}

const char* g_szDataDir = "Client\\";//��ԴĿ¼��ַ

void CupdateDlg::UpdataFileToPacket(UpdateList& updatalist)
{
	size_t nFileCount = updatalist.size();
	packet* pPacket = NULL;
	_tstring strTip;
	for (size_t i=0; i<nFileCount && !g_bIsEnd; i++)
	{
		DOWNLOADFILEINFO& info = updatalist[i];
		if(info.strPacketName.size()>0)
		{
			_tstring strPacket = g_szDataDir;
			if(!ManuaPath)
			{
				_mkdir(_tANSICHAR(_T(g_szDataDir)));
			}
			else
			{
				string ss=g_szCurPath;
				ss+=g_szDataDir;
				_mkdir(_tANSICHAR(_T(ss)));strPacket=ss;
			}
			strPacket+=info.strPacketName.c_str();

			DWORD dwAttrs = GetFileAttributes(strPacket.c_str());

			if(dwAttrs != INVALID_FILE_ATTRIBUTES)
			{
				if(dwAttrs & FILE_ATTRIBUTE_READONLY)
					SetFileAttributes(strPacket.c_str(),dwAttrs&~FILE_ATTRIBUTE_READONLY);
			}

			pPacket =packet_namespace::getpacket(strPacket.c_str());
			if(!pPacket)
			{
				strTip.Format(_T(m_mapStringSet[139].c_str()), info.strFileName.c_str());
				SetTip(strTip);
				continue;
			}
			char fileName[256];
			strcpy(fileName,info.strSaveLocalFilePath.c_str());
			char filedir[20];
			memcpy(filedir,fileName,4);
			filedir[4]='\0';
			//if(!strcmp(filedir,"bin\\"))
			//{
			//	strcpy(fileName,fileName+4);
			//}
			for (int i=strlen(fileName);i>=0;--i)
			{
				if(fileName[i]=='\\' || fileName[i]=='/')
				{
					fileName[i+1]='0';
					strcpy(fileName+i+1,info.strFileName.c_str());
					break;
				}

			}
			if(!pPacket->UpdateFile(info.strLocalFilePath.c_str(),fileName))
			{
				pPacket->AddFile(info.strLocalFilePath.c_str(),fileName);
			}

			if(langType==0)
				SetTip(_T("�����Դ��")+info.strLocalFilePath);
			else if(langType==1)
				SetTip(_T("����YԴ��")+info.strLocalFilePath);
			else if(langType==2)
				SetTip(_T("Add Resource Kit")+info.strLocalFilePath);
			//SetTip("�����Դ��"+info.strPacketName);
		}	

		progress_message mess;
		mess.downlen=i+1;
		mess.totallen=nFileCount;
		mess.type=1;

		CWnd * dlg=         AfxGetApp()-> GetMainWnd();
		::SendMessage(dlg->m_hWnd,WM_DRAW_PROGRESS,(WPARAM)&mess,0);

//		::SendDlgItemMessage(theApp.m_pMainWnd->GetSafeHwnd(), IDC_UpdateProc, PBM_SETPOS, static_cast<WPARAM>(((double)i/(double)nFileCount)*100), 0);
//		if(GetPatchInstance())
//			GetPatchInstance()->SetProgress(i+1, nFileCount);
		_tstring strProcessTip;
		strProcessTip.Format(_T("%d /   %d"), i+1, nFileCount);
//		SetCurrProcessTip(strProcessTip);
	}
	packet_namespace::SavePacket();
	packet_namespace::AfreshAllPacket();
	packet_namespace::release();
}

CupdateDlg::UpdateList& CupdateDlg::GetUpdateFile(_tstring strVersionXML, _tstring strLocalPath,bool is_autopatch)
{
	//	try
	//{
	if (!strLocalPath.empty() && strLocalPath[strLocalPath.length()-1] != _T('\\'))
	{
		strLocalPath += _T("\\");
	}
	static UpdateList s_downlist;
	s_downlist.clear();
	TiXmlDocument doc(_tANSICHAR(strVersionXML));

	if (!doc.LoadFile())
	{
		//			throw Common::CException(0, _T(m_mapStringSet[49].c_str()));
	}
	TiXmlNode* nodeversioninfo = doc.FirstChild(_tUTF8CHAR(_T("VersionInfo")));
	if (nodeversioninfo == NULL)
	{
		//			throw Common::CException(0, _T(m_mapStringSet[50].c_str()));
	}

	TiXmlNode* nodefilelist = nodeversioninfo->FirstChild(_tUTF8CHAR(_T("FileList")));
	if (nodefilelist == NULL)
	{
		//			throw Common::CException(0, _T(m_mapStringSet[51].c_str()));
	}

	//�ȰѸ�Ŀ¼�µ��ļ�����һ��
	TiXmlElement* elementfile = nodefilelist->FirstChildElement(_tUTF8CHAR(_T("File")));
	while (elementfile != NULL && !g_bIsEnd)
	{
		_tstring strFile;
		strFile.fromUTF8(elementfile->GetText());

		//���ϴ�Ű汾�ŵ��ļ�update.xml���򲻸���
		if (strFile == _T(g_szUpdateFile))
		{
			elementfile = elementfile->NextSiblingElement();
			continue;
		}
		_tstring strTip;
		strTip.Format(_T(m_mapStringSet[52].c_str()), strLocalPath.c_str(), strFile.c_str());
		//			SetTip(strTip);
		//			GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str());
		//			GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);

		_tstring strSize;
		TiXmlElement* elementsize = elementfile->FirstChildElement(_tUTF8CHAR(_T("Size")));
		strSize.fromUTF8(elementsize->GetText());

		if (strSize == _T("0"))
		{
			_tstring strfile = strLocalPath + strFile;
			DeleteFile(strfile.c_str());
			elementfile = elementfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
			fstream file(_tUNICODECHAR(strfile), std::ios::app);
			continue;
		}

		_tstring strDate;
		TiXmlElement* elementdate = elementfile->FirstChildElement(_tUTF8CHAR(_T("Date")));
		strDate.fromUTF8(elementdate->GetText());

		_tstring strCrc;
		TiXmlElement* elementcrc = elementfile->FirstChildElement(_tUTF8CHAR(_T("Crc")));
		strCrc.fromUTF8(elementcrc->GetText());

		DOWNLOADFILEINFO info;
		info.bVFSUnit = false;
		info.strHostFilePath += strFile;//�ļ���
		info.strLocalFilePath = strLocalPath + strFile;
		info.strChangeTime = strDate;
		info.strFileName = strFile;
		info.strCRC = strCrc;

		if (elementfile->Attribute(_tUTF8CHAR("Compress")) != NULL)
		{
			info.bUseCompress = true;
			info.strHostFilePath += _T(".zip");
		}
		else
		{
			info.bUseCompress = false;
		}

		if (strDate != GetFileDate(info.strLocalFilePath))
		{
			if (strCrc != GetFileCrc(info.strLocalFilePath))
			{
				s_downlist.push_back(info);
			}
			else
			{
				SetFileChangeTime(info.strLocalFilePath, info.strChangeTime);
			}
		}
		else
		{
			//��ʹ�ļ��������ҲҪ����CRCУ������
			if (strCrc != GetFileCrc(info.strLocalFilePath))
			{
				s_downlist.push_back(info);
			}
		}
		elementfile = elementfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
	}

	//���ڷ�����Ŀ¼�µ�
	TiXmlElement* elementfolder = nodefilelist->FirstChildElement(_tUTF8CHAR(_T("Folder")));
	while (elementfolder != NULL && !g_bIsEnd)
	{
		_tstring strFolder;
		strFolder.fromUTF8(elementfolder->GetText());
		if (strFolder[strFolder.length()-1] != _T('\\'))
		{
			strFolder += _T("\\");
		}
		_tstring strPacketName;
		TiXmlElement* pElementPacket = elementfolder->FirstChildElement(_tUTF8CHAR(_T("packet")));
		if(pElementPacket)
			strPacketName.fromUTF8(pElementPacket->GetText());//������
	//	    MakeEmbedFolder(strFolder);

		TiXmlElement* elementfile = elementfolder->FirstChildElement(_tUTF8CHAR(_T("File")));
		while (elementfile != NULL && !g_bIsEnd)
		{
			_tstring strFile;
			strFile.fromUTF8(elementfile->GetText());

			//���ϴ�Ű汾�ŵ��ļ�update.xml���򲻸���
			if (strFile == _T(g_szUpdateFile))
			{
				elementfile = elementfile->NextSiblingElement();
				continue;
			}

			_tstring strTip;
			strTip.Format(_T(m_mapStringSet[53].c_str()), strLocalPath.c_str(), strFolder.c_str(), strFile.c_str());
			//				SetTip(strTip);
			//				GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str());
			//				GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);

			_tstring strSize;
			TiXmlElement* elementsize = elementfile->FirstChildElement(_tUTF8CHAR(_T("Size")));
			strSize.fromUTF8(elementsize->GetText());

			if (strSize == _T("0"))
			{
				_tstring strfile = strLocalPath + strFolder + strFile;
				DeleteFile(strfile.c_str());
				elementfile = elementfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
				fstream file(_tUNICODECHAR(strfile), std::ios::app);
				continue;
			}

			_tstring strDate;
			TiXmlElement* elementdate = elementfile->FirstChildElement(_tUTF8CHAR(_T("Date")));
			strDate.fromUTF8(elementdate->GetText());

			_tstring strCrc;
			TiXmlElement* elementcrc = elementfile->FirstChildElement(_tUTF8CHAR(_T("Crc")));
			strCrc.fromUTF8(elementcrc->GetText());

			DOWNLOADFILEINFO info;
			info.bVFSUnit = false;
			info.strHostFilePath = strFolder + strFile;
			info.strLocalFilePath = strLocalPath + strFolder + strFile;
			info.strChangeTime = strDate;
			info.strFileName = strFile;
			info.strCRC = strCrc;
			info.strPacketName = strPacketName;
			

			if (elementfile->Attribute(_tUTF8CHAR("Compress")) != NULL)
			{
				info.bUseCompress = true;
				info.strHostFilePath += _T(".zip");
			}
			else
			{
				info.bUseCompress = false;
			}

			if (is_autopatch)
			{
				if (strDate != GetFileDate(info.strLocalFilePath))
				{
					if  (strCrc != GetFileCrc(info.strLocalFilePath))
					{
						s_downlist.push_back(info);
					}
					else
					{
						SetFileChangeTime(info.strLocalFilePath, info.strChangeTime);
					}
				}
				else
				{
					//��ʹ�ļ��������ҲҪ����CRCУ������
					if (strCrc != GetFileCrc(info.strLocalFilePath))
					{
						s_downlist.push_back(info);
					}
				}
			}
			else
			{//����Ǳ��ظ��£��ֶ����£������ܱ����ļ�����Ҫ���³ɰ��е��ļ�
				s_downlist.push_back(info);
			}

			elementfile = elementfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
		}
		elementfolder = elementfolder->NextSiblingElement(_tUTF8CHAR(_T("Folder")));
	}

	//���ڷ��������ļ�ϵͳ
	TiXmlElement* elementvfolder = nodefilelist->FirstChildElement(_tUTF8CHAR(_T("VFolder")));
	while (elementvfolder != NULL && !g_bIsEnd)
	{
		_tstring strVFSFile;
		strVFSFile.fromUTF8(elementvfolder->GetText());
		CVFS vfs;
		//����VFS�ļ���������������½���
		if (!vfs.LoadVFS(strVFSFile.c_str()))
		{
			if (!vfs.NewVFSFile(strVFSFile.c_str()))
			{
				//					throw Common::CException(0, _T(m_mapStringSet[54].c_str()), strVFSFile.c_str());
			}
		}
		CVFS::UNITLIST list = vfs.GetUnitList();
		//���������ļ�ϵͳ��Ŀ¼���ļ�
		TiXmlElement* elementvfile = elementvfolder->FirstChildElement(_tUTF8CHAR(_T("File")));
		while (elementvfile != NULL && !g_bIsEnd)
		{
			DOWNLOADFILEINFO info;
			info.bVFSUnit = true;
			info.strLocalFilePath = strVFSFile;
			info.strFileName.fromUTF8(elementvfile->GetText());

			_tstring strTip;
			strTip.Format(_T(m_mapStringSet[55].c_str()), info.strFileName.c_str());
			//				SetTip(strTip);
			//				GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str());
			//				GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);

			_tstring strCrc;
			TiXmlElement* elementcrc = elementvfile->FirstChildElement(_tUTF8CHAR(_T("Crc")));
			strCrc.fromUTF8(elementcrc->GetText());
			info.strCRC = strCrc;

			_tstring strFileName = info.strFileName;
			strFileName.Replace(_T("/"), _T("\\"));
			strFileName.MakeLower();

			CVFS::UNITLIST::iterator itr = list.find(strFileName);
			if (itr != list.end())
			{
				if (itr->second.nCrc == static_cast<unsigned long>(atol(_tANSICHAR(strCrc))))
				{
					elementvfile = elementvfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
					continue;
				}
				else        //���vfs�д��ڴ��ļ�����ɾ��
				{
					vfs.DelUnit(info.strFileName.c_str());
				}
			}

			//CRCֵΪ0�����ʾ����ҲΪ0
			if (strCrc == _T("0"))
			{
				vfs.AddUnit(info.strFileName.c_str(), NULL, 0);
				vfs.Save(NULL);
				elementvfile = elementvfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
				continue;
			}

			info.strHostFilePath = info.strLocalFilePath + _T("/") + info.strFileName;
			if (elementvfile->Attribute(_tUTF8CHAR("Compress")) != NULL)
			{
				info.bUseCompress = true;
				info.strHostFilePath += _T(".zip");
			}
			else
			{
				info.bUseCompress = false;
			}
			s_downlist.push_back(info);
			elementvfile = elementvfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
		}


		//���������ļ�ϵͳ��Ŀ¼���ļ�
		TiXmlElement* elementvsubfolder = elementvfolder->FirstChildElement(_tUTF8CHAR(_T("Folder")));
		while (elementvsubfolder != NULL && !g_bIsEnd)
		{
			_tstring strVsubfolder;
			strVsubfolder.fromUTF8(elementvsubfolder->GetText());
			//���������ļ�ϵ��Ŀ¼���ļ�
			TiXmlElement* elementvsubfile = elementvsubfolder->FirstChildElement(_tUTF8CHAR(_T("File")));
			while (elementvsubfile != NULL && !g_bIsEnd)
			{
				DOWNLOADFILEINFO info;
				info.bVFSUnit = true;
				info.strLocalFilePath = strVFSFile;
				_tstring strFile;
				strFile.fromUTF8(elementvsubfile->GetText());
				info.strFileName.Format(_T("%s\\%s"), strVsubfolder.c_str(), strFile.c_str());

				_tstring strTip;
				strTip.Format(_T(m_mapStringSet[55].c_str()), info.strFileName.c_str());
				//					SetTip(strTip);
				//					GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str());
				//					GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);

				_tstring strCrc;
				TiXmlElement* elementcrc = elementvsubfile->FirstChildElement(_tUTF8CHAR(_T("Crc")));
				strCrc.fromUTF8(elementcrc->GetText());
				info.strCRC = strCrc;

				_tstring strFileName = info.strFileName;
				strFileName.Replace(_T("/"), _T("\\"));
				strFileName.MakeLower();

				CVFS::UNITLIST::iterator itr = list.find(strFileName);
				if (itr != list.end())
				{
					if (itr->second.nCrc == static_cast<unsigned long>(atol(_tANSICHAR(strCrc))))
					{
						elementvsubfile = elementvsubfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
						continue;
					}
					else        //���vfs�д��ڴ��ļ�����ɾ��
					{
						vfs.DelUnit(info.strFileName.c_str());
					}
				}
				//CRCֵΪ0�����ʾ����ҲΪ0
				if (strCrc == _T("0"))
				{
					vfs.AddUnit(info.strFileName.c_str(), NULL, 0);
					elementvsubfile = elementvsubfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
					continue;
				}

				info.strHostFilePath = info.strLocalFilePath + _T("/") + info.strFileName;
				if (elementvsubfile->Attribute(_tUTF8CHAR("Compress")) != NULL)
				{
					info.bUseCompress = true;
					info.strHostFilePath += _T(".zip");
				}
				else
				{
					info.bUseCompress = false;
				}
				s_downlist.push_back(info);
				elementvsubfile = elementvsubfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
			}

			elementvsubfolder = elementvsubfolder->NextSiblingElement(_tUTF8CHAR(_T("Folder")));
		}
		//			if (!vfs.Save(ChangeProcCallBack))
		{
			//				throw Common::CException(0, _T(m_mapStringSet[56].c_str()), strVFSFile.c_str());
		}
		elementvfolder = elementvfolder->NextSiblingElement(_tUTF8CHAR(_T("VFolder")));
	}
	//	}
	/*	catch (Common::CException& exp)
	{
	_tstring strErr;
	strErr.Format(_T(m_mapStringSet[57].c_str()), exp.GetCode(), exp.GetMsg().c_str());
	::MessageBox(theApp.GetMainWnd()->GetSafeHwnd(), strErr.c_str(), _T(m_mapStringSet[34].c_str()), MB_ICONERROR);
	}
	*/
	return s_downlist;
}

bool CupdateDlg::SetLocalVersion(const TCHAR* szVersion)
{
//	try
	{
		_tstring strErr;
		TiXmlDocument doc;

		if(ManuaPath)
		{
			string ss;
			ss=g_szCurPath;
			ss+=g_szUpdateFile;
			if (!doc.LoadFile(ss.c_str()))
			{

			}

		}
		else
		{

			if (!doc.LoadFile(_tANSICHAR(_T(g_szUpdateFile))))
			{

			}
		}

	//	if (!doc.LoadFile(_tANSICHAR(_T(g_szUpdateFile))))
		{
//			throw Common::CException(0, _T(m_mapStringSet[40].c_str()), _tstring(doc.ErrorDesc()).c_str());
		}
		TiXmlElement* elementupdate = doc.FirstChildElement(_tUTF8CHAR(_T("Update")));
		if (elementupdate == NULL)
		{
//			throw Common::CException(0, _T(m_mapStringSet[41].c_str()));
		}

		TiXmlElement* elementversion = elementupdate->FirstChildElement(_tUTF8CHAR(_T("Version")));
		if (elementversion != NULL)
		{
			elementupdate->RemoveChild(elementversion);
		}
		TiXmlElement newversion(_tUTF8CHAR(_T("Version")));
		newversion.InsertEndChild(TiXmlText(_tUTF8CHAR(szVersion)));
		elementupdate->InsertEndChild(newversion);
		doc.SaveFile();
		return true;
	}
/*	catch (Common::CException& exp)
	{
		_tstring strErr;
		strErr.Format(_T(m_mapStringSet[42].c_str()), exp.GetCode(), exp.GetMsg().c_str());
		MessageBox(theApp.GetMainWnd()->GetSafeHwnd(), strErr.c_str(), _T(m_mapStringSet[34].c_str()), MB_ICONERROR);
		return false;
	}*/
}


bool CupdateDlg::ManualUpdateFile(const TCHAR *cFilePath, const TCHAR* cCurVersion)
{
	
	//�ҵ�cFilePathĿ¼�£�temp\0.81-0.82���ļ�versioninfo_0.82.xml
	if (!cFilePath || !cCurVersion)
	{
		
		if(langType==0)
			SetTip("·������");
		else if(langType==1)
			SetTip(_T("·�����e"));
		else if(langType==2)
			SetTip(_T("Path error"));
		Sleep(200);
		
		return false;
	}
	_tstring strTip;
	_tstring strLocalVersionFile;
	strLocalVersionFile.Format(_T("%s\\VersionInfo_%s.xml"), cFilePath, cCurVersion);
	UpdateList& downlist = GetUpdateFile(strLocalVersionFile, _T("\\"),false);//��Ϊ����Ҫ�������ļ�ȫ������ʱ�ļ�����

	if (downlist.empty())
	{
		strTip.Format(_T(m_mapStringSet[133].c_str()), cFilePath);
		
		if(langType==0)
			SetTip("��װĿ¼��û���ҵ��κ��ļ�");
		else if(langType==1)
			SetTip(_T("���bĿ��]���ҵ��κ��ļ�"));
		else if(langType==2)
			SetTip(_T("Installation directory does not find any documentation"));
//		GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str(),false);
//		GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);
		return false;
	}

	unsigned int nFileMaxSize = downlist.size();

	float per = 0;
	for (int i = 0; i < nFileMaxSize&&!g_bIsEnd; ++i)
	{//SetTip("����");
		DOWNLOADFILEINFO& info = downlist[i];

		_tstring strTmp = cFilePath + info.strLocalFilePath + _T(".zip");
		strTip.Format(_T(m_mapStringSet[137].c_str()), strTmp.c_str());
		SetTip(strTip);
	//	GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str());
	//	GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);
		CZipWrapper zip(strTmp.c_str());
		if (!zip.IsOpen())
		{
			if(langType==0)
				SetTip("��ʧ��"+strTmp);
			else if(langType==1)
				SetTip(_T("���_ʧ��")+strTmp);
			else if(langType==2)
				SetTip(_T("Open failed")+strTmp);
			
	//		strTip.Format(_T(m_mapStringSet[138].c_str()), strTmp.c_str());
	//		SetTip(strTip);
	//		GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str(),false);
	//		GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);
			return false;
		}

		_tstring strUnZipTmpFile = _T("ManualUpdateTemp\\unziptmp.tmp");
		
		
		SetFileAttributes(strUnZipTmpFile.c_str(), FILE_ATTRIBUTE_NORMAL);
		remove(_tANSICHAR(strUnZipTmpFile));

		_tstring strUnCompressfilepath ;

		if(info.strPacketName.size() <= 0)
		{
			strUnCompressfilepath= info.strFileName;
		}else
		{
			
			if(!ManuaPath)
		{
			strUnCompressfilepath=_T("ManualUpdateTemp\\");
		}
		else
		{
			strUnCompressfilepath=g_szCurPath;
			strUnCompressfilepath+=_T("\\ManualUpdateTemp\\");
		}
		//	strUnCompressfilepath = _T("ManualUpdateTemp\\");
			strUnCompressfilepath+=info.strFileName;
		}
		char nfileflage[]=".zip";
		char nCurrFileFlage[5];
		char nFilepath[MAX_PATH];
		int nFlageOffset = strlen(info.strHostFilePath.c_str())-4;
		strcpy(nCurrFileFlage,info.strHostFilePath.c_str()+nFlageOffset);
		if(strcmp(nfileflage,nCurrFileFlage) == 0)
		{
			strcpy(nFilepath,info.strHostFilePath.c_str());
			nFilepath[nFlageOffset] = '\0';
			info.strSaveLocalFilePath = nFilepath;
			
		}else
		{
			info.strSaveLocalFilePath = info.strHostFilePath.c_str();
		}


//SetTip("��װ"+info.strFileName);
		if(info.strPacketName == "")//���û�а�ʱ����ֱ�ӽ⵽��ӦĿ¼��
		{    
			_tstring strFilename ;
			strFilename+=info.strSaveLocalFilePath;
			
			string ss;
			if(!ManuaPath)
			{
				
			}
			else
			{
				ss=g_szCurPath;
				ss+=_T("\\");
				strUnZipTmpFile=ss+strUnZipTmpFile;
				
				
				strFilename=ss+info.strSaveLocalFilePath;
			}


			if(!zip.SaveUnitToFile(info.strFileName.c_str(),strUnZipTmpFile.c_str()))
			{	
				if(langType==0)
			SetTip("��װ�ļ�ʧ��"+strTmp);
			else if(langType==1)
				SetTip(_T("���b�ļ�ʧ��")+strTmp);
			else if(langType==2)
				SetTip(_T("Installation file failed")+strTmp);
			Sleep(200);
		//		strTip.Format(_T(m_mapStringSet[139].c_str()), info.strFileName.c_str());
				
	//			GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str(),false);
	//			GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);
				return false;
			}
			else
			{
				
				if(langType==0)
					SetTip("��װ�ļ�"+strTmp);
				else if(langType==1)
					SetTip(_T("���b�ļ�")+strTmp);
				else if(langType==2)
					SetTip(_T("Installation file")+strTmp);
                  Sleep(200);
			//	Sleep(20);
				
				DWORD dwAttrs = GetFileAttributes(strFilename.c_str());

				if(dwAttrs != INVALID_FILE_ATTRIBUTES)
				{
					if(dwAttrs & FILE_ATTRIBUTE_READONLY);

					SetFileAttributes(strFilename.c_str(),dwAttrs&~FILE_ATTRIBUTE_READONLY);
				}

				remove(_tANSICHAR(strFilename));
				rename(_tANSICHAR(strUnZipTmpFile), _tANSICHAR(strFilename));
				if(GetLastError() == ERROR_PATH_NOT_FOUND)
				{
					if(!zip.SaveUnitToFile(info.strFileName.c_str(),strFilename.c_str()))
					{
						strTip.Format(_T(m_mapStringSet[139].c_str()), info.strFileName.c_str());
						if(langType==0)
					SetTip("��װ�ļ�ʧ��"+strTip);
					else if(langType==1)
						SetTip(_T("���b�ļ�ʧ��")+strTip);
					else if(langType==2)
						SetTip(_T("Installation file failed")+strTip);
					Sleep(200);
						
		//				SetTip(strTip);
		//				GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str(),false);
		//				GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);
						return false;
					}
				}
			}
		}else{//�а�

			string ss;
			if(!ManuaPath)
			{
				ss=_T("ManualUpdateTemp\\");
			}
			else
			{
				ss=g_szCurPath;
				ss+=_T("\\ManualUpdateTemp\\");
			}

			;ss+=info.strLocalFilePath;info.strLocalFilePath=ss;
			
			if(langType==0)
				SetTip("��װ���ļ�"+info.strLocalFilePath);
			else if(langType==1)
				SetTip(_T("���b���ļ�")+info.strLocalFilePath);
			else if(langType==2)
				SetTip(_T("Installation package file")+info.strLocalFilePath);
			
			if (!zip.SaveUnitToFile(info.strFileName.c_str(), info.strLocalFilePath.c_str()))
			{
				strTip.Format(_T(m_mapStringSet[139].c_str()), info.strFileName.c_str());
				if(langType==0)
					SetTip("��װ�ļ�ʧ��"+strTip);
				else if(langType==1)
					SetTip(_T("���b�ļ�ʧ��")+strTip);
				else if(langType==2)
					SetTip(_T("Installation file failed")+strTip);
				Sleep(200);
		//		SetTip(strTip);
		//		GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str(),false);
		//		GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);
				return false;
			}
		}                  
		zip.CloseZipFile();
		per = (float)(i+1)/nFileMaxSize;
		per *= 100;
		
		progress_message mess;
		mess.downlen=i+1;
		mess.totallen=nFileMaxSize;
		mess.type=1;

		CWnd * dlg=         AfxGetApp()-> GetMainWnd();
		::SendMessage(dlg->m_hWnd,WM_DRAW_PROGRESS,(WPARAM)&mess,0);


//		GetPatchInstance()->SetProgressUpdateDigPercentage(per);
//		GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);
		//DrawManualUpdateProc(nFileMaxSize+nFileMaxSize/4,i+1);
	}
	
	
//	_mkdir(_tANSICHAR(g_szCurPath+_T("\\bin\\res\\")));

	if(!ManuaPath)
	{
		_mkdir(_tANSICHAR(_T(g_szDataDir)));
	}
	else
	{
		string ss=g_szCurPath;
		ss+=g_szDataDir;
		_mkdir(_tANSICHAR(_T(ss)));
	}

	
	UpdataFileToPacket(downlist);
	remove(_tANSICHAR(_T("ManualUpdateTemp")));
	return true;
}

//����PE�ļ���Ϣ����������С��   
ULONG  GetFileLen(LPVOID pBaseaddr,LPVOID pReadBuf)  
{  
	LPBYTE pBase=(LPBYTE)pBaseaddr;  
	PIMAGE_DOS_HEADER pDosHeader=(PIMAGE_DOS_HEADER)pReadBuf;  
	ULONG uSize=PIMAGE_OPTIONAL_HEADER((pBase+pDosHeader->e_lfanew+4+20))->SizeOfHeaders;  
	PIMAGE_SECTION_HEADER    pSec = (PIMAGE_SECTION_HEADER)(pBase+pDosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS));  
	for(int i=0;i<PIMAGE_FILE_HEADER(pBase+pDosHeader->e_lfanew+4)->NumberOfSections;++i)  
	{  
		uSize+=pSec[i].SizeOfRawData;  
	}  
	return uSize;  
}  

extern bool MakeEmbedFolder(string strFolderPath);
DWORD WINAPI  CupdateDlg::UpdateThreadProc(LPVOID p)
{

	_tstring lasttip;
	
	
	
	//��װ���裺һ����Դ���ȡ�������ļ��������߰�װ
	string packTmp,packTmp1;string strTmp;


	string packstr;
	if(!ManuaPath)
	{
		MakeEmbedFolder(".\\zippack");
        packTmp=".\\temp\\";
        MakeEmbedFolder(packTmp);
		strTmp=".\\zippack\\tt\\temp.zip";
		packstr=".\\zippack";
	}
	else
	{
       string ss;
	   ss=g_szCurPath;
	   ss+="\\zippack";
		MakeEmbedFolder(ss); 
		packTmp=g_szCurPath;
		packTmp+="\\temp\\";
		MakeEmbedFolder(packTmp);
		strTmp=g_szCurPath;
		strTmp+="\\zippack\\tt\\temp.zip";packstr=g_szCurPath;
		packstr+="\\zippack";
	}
	

	if(langType==0)
			SetTip(_T("��ʼд���ļ�"));
	else if(langType==1)
		SetTip(_T("�_ʼ�����ļ�"));
	else if(langType==2)
		SetTip(_T("Began to write file"));
	int len=GetFileLen( GetModuleHandle(NULL), GetModuleHandle(NULL));
	TCHAR my_name[MAX_PATH];	
	::GetModuleFileName(0, my_name, sizeof(my_name));

	char   path[256]; 
	::GetTempPath(256,path);
	strcat(path,"temp.zip"); 
	
	FILE* myself; 
	CFile mFile,mFiled;
	if(!mFiled.Open(path,CFile::modeWrite|CFile::modeCreate))
	{
		if(langType==0)
			SetTip(_T("д���ļ�ʧ��"));
		else if(langType==1)
			SetTip(_T("�����ļ�ʧ��"));
		else if(langType==2)
			SetTip(_T("Failed to write file"));
		return 0;
	}
	if(!mFile.Open(my_name,CFile::modeRead))
	{
		if(langType==0)
			SetTip(_T("д���ļ�ʧ��"));
		else if(langType==1)
			SetTip(_T("�����ļ�ʧ��"));
		else if(langType==2)
			SetTip(_T("Failed to write file"));
		return 0;
	}
	char * lpRsrc=new char[1024];
	mFiled.SeekToEnd();
	mFile.Seek(len,CFile::begin);
	while(1) 
	{ 
		int   i   =mFile.Read(lpRsrc,1024 ); 
		mFiled.Write(lpRsrc,i);

		if(i < 1024) 
			break; 
	}
	mFile.Close(); 
	mFiled.Close();
	delete lpRsrc;
	strTmp=path;
/*	FolderFileList d;
	if(!d.PackOut((char *)packstr.c_str()))
	{
		if(langType==0)
			SetTip(_T("����ʧ��"));
		else if(langType==1)
			SetTip(_T("����ʧ��"));
		else if(langType==2)
			SetTip(_T("Failed to update"));
		return 0;
	}
*/
	//��ѹ   
	if(langType==0)
		SetTip(_T("д���ļ��ɹ�"));
	else if(langType==1)
		SetTip(_T("�����ļ��ɹ�"));
	else if(langType==2)
		SetTip(_T("Successfully write files"));
	
	Sleep(500);

	
	if(langType==0)
		SetTip(_T("��ʼ��ѹ�ļ�"));
	else if(langType==1)
		SetTip(_T("�_ʼ�≺�ļ�"));
	else if(langType==2)
		SetTip(_T("Begin extracting files"));

	CZipWrapper zip(strTmp.c_str());
	if (!zip.IsOpen())
	{
		//		GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str(),false);
		//		GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);

		if(langType==0)
		SetTip(_T("��ѹ����ʧ��")+strTmp);
		else if(langType==1)
        SetTip(_T("���_���s��ʧ��")+strTmp);
		else if(langType==2)
			SetTip(_T("Failed to open archive")+strTmp);
		return 0;
	}

	CZipWrapper::UnitInfoList list=zip.GetUnitList(); 

	size_t nFileCount = list.size();

	for (size_t i=0; i<nFileCount && !g_bIsEnd; i++)
	{
		CZipWrapper::UNITINFO& info = list[i];	
		packTmp1=packTmp+info.strFileName;
		if (!zip.SaveUnitToFile(info.strFileName.c_str(), packTmp1.c_str()))
		{			
			if(langType==0)
				SetTip(_T("��ѹʧ��")+packTmp1);
			else if(langType==1)
				SetTip(_T("�≺ʧ��")+strTmp);
			else if(langType==2)
				SetTip(_T("Extract failed")+strTmp);
			Sleep(200);
            return 0;
		}
		else
		{		
			if(langType==0)
				SetTip(_T("���ڽ�ѹ")+info.strFileName);	
			else if(langType==1)
				SetTip(_T("���ڽ≺")+strTmp);
			else if(langType==2)
				SetTip(_T("Is extracted")+strTmp);

			progress_message mess;
			mess.downlen=i+1;
			mess.totallen=nFileCount;
			mess.type=1;

			CWnd * dlg=         AfxGetApp()-> GetMainWnd();
			::SendMessage(dlg->m_hWnd,WM_DRAW_PROGRESS,(WPARAM)&mess,0);
		}
	}
	
	zip.CloseZipFile();

	if(!ManuaPath)
	{
		DeleteDir(_T(".\\zippack"));
	}
	else
	{
		string ss=g_szCurPath;
		ss+=_T("\\zippack");
        DeleteDir(ss.c_str());
	}

    
	if(langType==0)
		SetTip(_T("��ȡ��ǰ�汾����"));
	else if(langType==1)
		SetTip(_T("�xȡ��ǰ�汾����"));
	else if(langType==2)
		SetTip(_T("Read the current version of the configuration"));
	
	Sleep(100);
	//��ȡ��ǰ�汾����
	TiXmlDocument doc;

	if(ManuaPath)
	{
		string ss;
		ss=g_szCurPath;
		ss+=g_szUpdateFile;
		if (!doc.LoadFile(ss.c_str()))
		{
			if(langType==0)
				SetTip(_T("��ȡ�汾�ļ�ʧ��"));
			else if(langType==1)
				SetTip(_T("�xȡ�汾�ļ�ʧ��"));
			else if(langType==2)
				SetTip(_T("Failed to read version of the file"));
			return 0;
		}
	}
	else
	{
		if (!doc.LoadFile(_tANSICHAR(_T(g_szUpdateFile))))
		{

				if(langType==0)
					SetTip(_T("��ȡ�汾�ļ�ʧ��"));
				else if(langType==1)
					SetTip(_T("�xȡ�汾�ļ�ʧ��"));
				else if(langType==2)
					SetTip(_T("Failed to read version of the file"));
				return 0;

		}
	}
	TiXmlElement* elementupdate = doc.FirstChildElement(_tUTF8CHAR(_T("Update")));
	if (elementupdate == NULL)
	{

			if(langType==0)
				SetTip(_T("��ȡ�汾�ļ�ʧ��"));
			else if(langType==1)
				SetTip(_T("�xȡ�汾�ļ�ʧ��"));
			else if(langType==2)
				SetTip(_T("Failed to read version of the file"));
			return 0;
	}

	TiXmlElement* elementversion = elementupdate->FirstChildElement(_tUTF8CHAR(_T("Version")));
	if (elementversion == NULL)
	{

			if(langType==0)
				SetTip(_T("��ȡ�汾�ļ�ʧ��"));
			else if(langType==1)
				SetTip(_T("�xȡ�汾�ļ�ʧ��"));
			else if(langType==2)
				SetTip(_T("Failed to read version of the file"));
			return 0;

	}

	Sleep(500);

	_tstring strVersion;
	strVersion.fromUTF8(elementversion->GetText());
	s_strVersion = strVersion;
	doc.Clear();


	
//��ѹ���п�����temp,temp//temp
	_tstring szFind;

	WIN32_FIND_DATA FindFileData;
	szFind = packTmp; //tempĿ¼��
	szFind+="temp";
	szFind = szFind + _T("\\*");

	HANDLE hFind=::FindFirstFile(szFind.c_str(),&FindFileData);
	if(INVALID_HANDLE_VALUE == hFind)
	{
		//		GetPatchInstance()->m_btn[0].SetButtonEnable();
		//		GetPatchInstance()->m_bManualUpdate = false;
		//		GetPatchInstance()->HideProgressUpdateDig();
		if(langType==0)
			lasttip=_T("�������߰���ʧ��");
		else if(langType==1)
			lasttip=_T("�����x������ʧ��");
		else if(langType==2)
			lasttip=_T("An offline package failed to find");

		FindClose(hFind);
		goto clean;
	}

	bool bIsRestart = false;


	bool changeVer=false;


	while(TRUE)
	{
		if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // ������ļ���
		{
			if(FindFileData.cFileName[0]!='.')
			{
				/*float fCurVerVersion = 0.0f;
				fCurVerVersion = atof(s_strVersion.c_str());*/

				//_tstring tPackVersion = _T(FindFileData.cFileName);
				TCHAR  filename[MAX_PATH] = {0};
				memcpy(filename,FindFileData.cFileName,MAX_PATH);
				TCHAR* cLow = NULL;
				TCHAR* cHigh = NULL;
				cLow = strtok(filename,"-");
				cHigh = strtok(NULL,"-");

				TCHAR  localversion[MAX_PATH] = {0};
				memcpy(localversion,s_strVersion.c_str(),MAX_PATH);
				TCHAR  packetversion[MAX_PATH] = {0};
				memcpy(packetversion,FindFileData.cFileName,MAX_PATH);
				/*float fLowVersion = 0.0f;
				float fHighVersion = 0.0f;

				fLowVersion = atof(cLow);
				fHighVersion = atof(cHigh);*/

				//if (fHighVersion > fCurVerVersion && fCurVerVersion >= fLowVersion) // �����ǰ�汾С����߰汾���Ҵ�����С�汾 �������
				if(CheckVersion(localversion,packetversion))
				{
					//if(	fabs(fHighVersion - fCurVerVersion) > 0.000001 ) //������ж���Ϊ�˱�����Ϊfloat����������Ȱ汾�Ž���
					{
						_tstring temp;
						temp.clear();
						temp=packTmp+"temp";
				//		temp = g_szUpdatePack;
						temp = temp + _T("\\") + FindFileData.cFileName;
						//��ʼ���
						_tstring strTip;
						strTip.Format(_T(m_mapStringSet[143].c_str()),temp.c_str());
						SetTip(strTip);
						//		GetPatchInstance()->SetProgressUpdateDigText(strTip.c_str());
						//		GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);

					    //temp\\0.81-0.82,0.82
						if (ManualUpdateFile(temp.c_str(),cHigh)) //��ѹ�ɹ�����Ӱ汾�Ų�ɾ��û�õİ�
						{
							bIsRestart = true;
                            changeVer=true;
							SetLocalVersion(cHigh);
							s_strVersion = cHigh;

							{							
								_tstring vertip;
								if(langType==0)
								vertip.Format("���߰�װ����[%s]�����°�[%s]",s_strVersion.c_str(),FindFileData.cFileName);							
								else if(langType==1)
								vertip.Format("�x�����b�Y��[%s]�����°�[%s]",s_strVersion.c_str(),FindFileData.cFileName);
								else if(langType==2)
								vertip.Format("update finish[%s]��pack[%s]",s_strVersion.c_str(),FindFileData.cFileName);
								lasttip=vertip;
				
							
							}	
							
							// ɾ��
							//							GetPatchInstance()->SetProgressUpdateDigText(m_mapStringSet[145].c_str());
							//							GetPatchInstance()->SendUpdateDigPercentageMessage(WM_PROGRESSUPDATE);
							//							DeleteManualUpdateFile(temp.c_str());
							//							DrawManualUpdateProc(100,100);
						}
						else
						{
							//							GetPatchInstance()->m_btn[0].SetButtonEnable();
							//							GetPatchInstance()->m_bManualUpdate = false;
							
							if(!ManuaPath)
							{
								goto clean;
						//		DeleteDir(_T(".\\zippack"));DeleteDir(_T("ManualUpdateTemp"));DeleteDir(_T("temp"));DeleteDir(_T("zippack"));DeleteFile("Dir.xml");
							}
							else
							{
								string ss=g_szCurPath;
								ss+=_T("\\zippack");DeleteDir(ss.c_str());
								ss=g_szCurPath;ss+=_T("\\ManualUpdateTemp");DeleteDir(ss.c_str());
								ss=g_szCurPath;ss+=_T("\\temp");DeleteDir(ss.c_str());
								ss=g_szCurPath;ss+=_T("\\Dir.xml");DeleteFile(ss.c_str());
							}
							Sleep(10000);
							{
								if(langType==0)
									lasttip=_T("��װ����");
								else if(langType==1)
									lasttip=_T("���b���e");
								else if(langType==2)
									lasttip=_T("Installation error");
							}
							FindClose(hFind);
							goto clean;
						}
					}	
				}
				else
				{
					_tstring vertip;
					if(langType==0)
						vertip=_T("�汾�Ų�ƥ���޷�����!");
					else if(langType==1)
						vertip=_T("�汾�Ų�ƥ���޷�����!");
					else if(langType==2)
						vertip=_T("�汾�Ų�ƥ���޷�����!");
					_tstring s;
					s.Format("[%s]�����°�[%s]",s_strVersion.c_str(),FindFileData.cFileName);
					vertip+=s;
					lasttip=vertip;FindClose(hFind);
					goto clean;
				}
				/*if(fHighVersion <=fCurVerVersion)
				{
					_tstring vertip;
					if(langType==0)
						vertip=_T("��ǰ�汾�������°汾,�������");
					else if(langType==1)
						vertip=_T("��ǰ�汾�������°汾,�o�����");
					else if(langType==2)
						vertip=_T("An offline package failed to find");
					_tstring s;
					s.Format("[%s]�����°�[%s]",s_strVersion.c_str(),FindFileData.cFileName);
					vertip+=s;
					lasttip=vertip;FindClose(hFind);
					goto clean;
				}
				if(fCurVerVersion < fLowVersion)
				{
					_tstring vertip;
					if(langType==0)
						vertip=_T("��ǰ�ͻ��˰汾����,����ʧ��");
					else if(langType==1)
						vertip=_T("��ǰ�͑��˰汾�^��,����ʧ��");
					else if(langType==2)
						vertip=_T("The current client version is too low, the update fails");
					_tstring s;
					s.Format("[%s]�����°�[%s]",s_strVersion.c_str(),FindFileData.cFileName);
					vertip+=s;
					lasttip=vertip;FindClose(hFind);
					goto clean;
				}*/
			}
		}
		if(!FindNextFile(hFind,&FindFileData))
			break;
	}
	FindClose(hFind);

	
	//	GetPatchInstance()->m_btn[0].SetButtonEnable();
	//	GetPatchInstance()->m_bManualUpdate = false;
	//	GetPatchInstance()->HideProgressUpdateDig();
	//	if (bIsRestart) //������й�����,��ô����launcher
	//		::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MANUALUPDAT, 0, 0);

	if(!ManuaPath)
	{
		goto clean;
//		DeleteDir(_T(".\\zippack"));DeleteDir(_T("ManualUpdateTemp"));DeleteDir(_T("temp"));DeleteDir(_T("zippack"));DeleteFile("Dir.xml");
	}
	else
	{
		string ss=g_szCurPath;
		ss+=_T("\\zippack");DeleteDir(ss.c_str());
		ss=g_szCurPath;ss+=_T("\\ManualUpdateTemp");DeleteDir(ss.c_str());
        ss=g_szCurPath;ss+=_T("\\temp");DeleteDir(ss.c_str());
        ss=g_szCurPath;ss+=_T("\\Dir.xml");DeleteFile(ss.c_str());
	}	
clean:
	{	
		DeleteDir(_T(".\\zippack"));DeleteDir(_T("ManualUpdateTemp"));DeleteDir(_T("temp"));DeleteDir(_T("zippack"));DeleteFile("Dir.xml");
		SetTip(lasttip);		
		if(langType==0)
			::MessageBox(NULL,"���½���","���߸�����ʾ",MB_OK);
		else if(langType==1)
			::MessageBox(NULL,"���½���","�x��������ʾ",MB_OK);
		else if(langType==2)
			::MessageBox(NULL,"update over!","Offline update prompt",MB_OK);
	}

	return 0;
}

//��Ȿ�ذ汾���Ƿ���Ҫ����,�汾���Ƿ��ڲ������İ汾�ŷ�Χ��
bool CupdateDlg::CheckVersion(TCHAR* localversion,TCHAR* packversion)
{
	if (!localversion||!packversion)
	{//����ǿյ��򲻸�������
		return false;
	}
	//ÿ���汾�ָ��е��������� 0.0.0 ���и� ˳��
	TCHAR* cVersionlLow = NULL;
	TCHAR* cVersionMid = NULL;
	TCHAR* cVersionHigh = NULL;	

	//���صİ汾��
	cVersionlLow = strtok(localversion,".");
	cVersionMid = strtok(NULL,".");
	cVersionHigh = strtok(NULL,".");

	int nlocalLowVersion = atoi(cVersionlLow);
	int nlocalMidVersion = atoi(cVersionMid);
	int nlocalHighVersion = atoi(cVersionHigh);

	TCHAR* cpackLow = NULL;
	TCHAR* cpackHigh = NULL;
	//�������İ汾�����ļ���,�ֵ׸�2����Ҫ�ֿ�����
	cpackLow = strtok(packversion,"-");
	cpackHigh = strtok(NULL,"-");

	int nPackLowVersion = 0;
	int nPackMidVersion = 0;
	int nPackHighVersion = 0;

	int nPackLowVersionLow = 0;
	int nPackMidVersionLow = 0;
	int nPackHighVersionLow = 0;

	//1,�Ƚ����߰汾�ŵ��뱾�ذ汾�űȽ�
	cVersionlLow = strtok(cpackHigh,".");
	cVersionMid = strtok(NULL,".");
	cVersionHigh = strtok(NULL,".");
	nPackLowVersion = atoi(cVersionlLow);
	nPackMidVersion = atoi(cVersionMid);
	nPackHighVersion = atoi(cVersionHigh);

	cVersionlLow = strtok(cpackLow,".");
	cVersionMid = strtok(NULL,".");
	cVersionHigh = strtok(NULL,".");
	nPackLowVersionLow = atoi(cVersionlLow);
	nPackMidVersionLow = atoi(cVersionMid);
	nPackHighVersionLow = atoi(cVersionHigh);

	if (nlocalLowVersion > nPackLowVersion)
	{//��һλ�汾�Ŵ����ʾ���ذ汾�űȽϴ�,������
		return false;
	}
	else if (nlocalLowVersion < nPackLowVersion)
	{//��һλС�����鲹�����Ͱ汾��
		goto checklow;
	}
	else if (nlocalLowVersion == nPackLowVersion)
	{//��һλ��ȼ�����������
		if (nlocalMidVersion > nPackMidVersion)
		{//�ڶ�λ����,������
			return false;
		}
		else if(nlocalMidVersion < nPackMidVersion)
		{//�ڶ�λС�����鲹�����Ͱ汾��
			goto checklow;
		}
		else if (nlocalMidVersion == nPackMidVersion)
		{//�ڶ�λ��ȼ�����������
			if (nlocalHighVersion >= nPackHighVersion)
			{//����λ���ڵ���,������
				return false;
			}			
			else if (nlocalHighVersion < nPackHighVersion)
			{//����λС��,���¼��Ͱ汾
				goto checklow;
			}
		}
	}

checklow:
	if (nlocalLowVersion < nPackLowVersionLow)
	{//��һλ�汾��С���ʾ���ذ汾��̫С,������
		return false;
	}
	else if(nlocalLowVersion > nPackLowVersionLow)
	{//��һλ���صĴ�,��ֱ�Ӹ���
		return true;
	}
	else if (nlocalLowVersion == nPackLowVersionLow)
	{//��һλ��ȼ�������ļ��
		if (nlocalMidVersion < nPackMidVersionLow)
		{//�ڶ�λС��,������
			return false;
		}
		else if(nlocalMidVersion > nPackMidVersionLow)
		{//�ڶ�λС�����鲹�����Ͱ汾��
			return true;
		}
		else if (nlocalMidVersion == nPackMidVersionLow)
		{//�ڶ�λ��ȼ�����������
			if (nlocalHighVersion < nPackHighVersionLow)
			{//����λ���ڵ���,������
				return false;
			}			
			else
			{//����λС��,���¼��Ͱ汾
				return true;
			}
		}
	}
	return false;
}

void CupdateDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

    ImgMgr.Release();m_TiXmlDoc.Clear();m_brush.DeleteObject();
	 g_bIsEnd=true;
	if(hHandle)TerminateProcess(hHandle,0);
	DeleteDir(_T(".\\zippack"));DeleteDir(_T("ManualUpdateTemp"));DeleteDir(_T("temp"));DeleteDir(_T("zippack"));DeleteFile("Dir.xml");
	CDialog::OnClose();
}

void CupdateDlg::OnBnClickedButton1()
{

    g_bIsEnd=true;

}

void CupdateDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(progressnow.percent>100)progressnow.percent=0;
	if(progresstotal.percent>100)progresstotal.percent=0;
	InvalidateRect(progressnow.rect,true);InvalidateRect(progresstotal.rect,true);
	progressnow.percent+=8;progresstotal.percent+=4;
	CDialog::OnTimer(nIDEvent);
}

BOOL CupdateDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg-> message==WM_KEYDOWN   &&   pMsg-> wParam==VK_ESCAPE)  {   return   TRUE;} 
	if(pMsg-> message==WM_KEYDOWN   &&   pMsg-> wParam==VK_RETURN)  { return   TRUE;   }
	else   

	return CDialog::PreTranslateMessage(pMsg);
}

void CupdateDlg::OnBnClickedButton2()
{
	g_bIsEnd=true;
    ::SendMessage(this->m_hWnd,WM_CLOSE,NULL,0);
	// TODO: Add your control notification handler code here
}
