// CrashRptUploadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CrashRptUpload.h"
#include "CrashRptUploadDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
std::string u_url;
std::string u_user;
std::string u_pwd;
std::string szDumpPath;
std::string szAppPath;
void set_upload_info(std::string user_,std::string pwd_,std::string ip_,std::string dump,std::string app)
{
	u_url=ip_;
	u_user=user_;
	u_pwd=pwd_;
	szDumpPath=dump;
	szAppPath=app;
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


// CCrashRptUploadDlg dialog




CCrashRptUploadDlg::CCrashRptUploadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCrashRptUploadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCrashRptUploadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCrashRptUploadDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CCrashRptUploadDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCrashRptUploadDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCrashRptUploadDlg message handlers

BOOL CCrashRptUploadDlg::OnInitDialog()
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


	GetDlgItem(IDC_STATIC)->SetWindowText("客户端遇到未知错误，给您带来不便深表歉意。我们己经产生了一个关于此错误的报告(报告中不包含任何用户隐私信息)。我们希望您选择发送报告给我们以帮助改善产品的质量。");
	GetDlgItem(IDC_CHECK1)->SetWindowText("发送错误报告");
	GetDlgItem(IDC_CHECK2)->SetWindowText("重启程序");
	GetDlgItem(IDC_BUTTON1)->SetWindowText("确定");
	GetDlgItem(IDC_BUTTON2)->SetWindowText("取消");
	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(true);
	((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(true);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCrashRptUploadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCrashRptUploadDlg::OnPaint()
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
HCURSOR CCrashRptUploadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





std::string GetFileNameByFilePath(const std::string filepath)
{
	std::string filename;
	if(filepath.size() < 0)
		return "";
	std::string::size_type ix = filepath.find_last_of('\\');
	if(ix != std::string::npos)
		return filepath.substr(ix+1,filepath.size()-ix);
	return filepath;
}

#include "minizip/zip.h"

//最终接口：从某个目录创建zip文件
void CreateZipFromDir(const std::string& dirName, const std::string& zipFileName);


//将文件添加到zip文件中，注意如果源文件srcFile为空则添加空目录
//fileNameInZip: 在zip文件中的文件名，包含相对路径

void AddFileToZip(zipFile zf, const char* fileNameInZip, const char* srcFile)
{
	FILE* srcfp = NULL;
	//初始化写入zip的文件信息
	zip_fileinfo zi;
	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
		zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
	zi.dosDate = 0;
	zi.internal_fa = 0;
	zi.external_fa = 0;
	//如果srcFile为空，加入空目录
	char new_file_name[MAX_PATH];
	memset(new_file_name, 0, sizeof(new_file_name));
	strcat(new_file_name, fileNameInZip);
	if (srcFile == NULL)
	{
		strcat(new_file_name, "/");
	}
	//在zip文件中创建新文件
	zipOpenNewFileInZip(zf, new_file_name, &zi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);
	if (srcFile != NULL)
	{
		//打开源文件
		srcfp = fopen(srcFile, "rb");
		if (srcfp == NULL)
		{
			//			MessageBox(_T("无法添加文件") + CString(srcFile) + _T("!"));
			zipCloseFileInZip(zf); //关闭zip文件
			return;
		}
		//读入源文件并写入zip文件
		char buf[100*1024]; //buffer
		int numBytes = 0;
		while( !feof(srcfp) )
		{
			numBytes = fread(buf, 1, sizeof(buf), srcfp);
			zipWriteInFileInZip(zf, buf, numBytes);
			if( ferror(srcfp) )
				break;
		}
		//关闭源文件
		fclose(srcfp);
	}
	//关闭zip文件
	zipCloseFileInZip(zf);
}



void zipEnFile(const std::string& dirName, const char* zipFileName)
{

	zipFile newZipFile = zipOpen(zipFileName, APPEND_STATUS_CREATE); //创建zip文件
	if (newZipFile == NULL)
	{
		return;
	}
	std::string s=GetFileNameByFilePath(dirName);
	AddFileToZip(newZipFile, s.c_str(), dirName.c_str()); 
	zipClose(newZipFile, NULL);
}



#include "libcurl\curl.h"  
#include "libcurl\easy.h"
#include <sys/stat.h>



/* parse headers for Content-Length */
size_t getcontentlengthfunc(void *ptr, size_t size, size_t nmemb, void *stream) {
	int r;
	long len = 0;
	/* _snscanf() is Win32 specific */
	//r = _snscanf(ptr, size * nmemb, "Content-Length: %ld/n", &len);
	r = sscanf((char *)ptr, "Content-Length: %ld/n", &len);
	if (r) /* Microsoft: we don't read the specs */
		*((long *) stream) = len;
	return size * nmemb;
}
/* discard downloaded data */

size_t discardfunc(void *ptr, size_t size, size_t nmemb, void *stream) {
	return size * nmemb;
}

//write data to upload 

size_t writefunc(void *ptr, size_t size, size_t nmemb, void *stream) 
{ 
	return fwrite(ptr, size, nmemb, (FILE*)stream); 
} 

/* read data to upload */
size_t readfunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
	FILE *f = (FILE*)stream;
	size_t n;
	if (ferror(f))
		return CURL_READFUNC_ABORT;
	n = fread(ptr, size, nmemb, f) * size;
	return n;
}

int upload(CURL *curlhandle, const char * remotepath, const char * localpath,
		   long timeout, long tries)
{
	FILE *f;
	long uploaded_len = 0;
	CURLcode r = CURLE_GOT_NOTHING;
	int c;
	f = fopen(localpath, "rb");
	if (f == NULL) {
		perror(NULL);
		return 0;

	}
	curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);
	curl_easy_setopt(curlhandle, CURLOPT_URL, remotepath);
	if (timeout)
		curl_easy_setopt(curlhandle, CURLOPT_FTP_RESPONSE_TIMEOUT, timeout);
	curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION, getcontentlengthfunc);
	curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &uploaded_len);
	curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, discardfunc);
	curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readfunc);
	curl_easy_setopt(curlhandle, CURLOPT_READDATA, f);
	curl_easy_setopt(curlhandle, CURLOPT_FTPPORT, "-"); /* disable passive mode */
	curl_easy_setopt(curlhandle, CURLOPT_FTP_CREATE_MISSING_DIRS, 1L);
	curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1L);
	for (c = 0; (r != CURLE_OK) && (c < tries); c++) {
		/* are we resuming? */
		if (c) { /* yes */
			/* determine the length of the file already written */
			/*
			* With NOBODY and NOHEADER, libcurl will issue a SIZE
			* command, but the only way to retrieve the result is
			* to parse the returned Content-Length header. Thus,
			* getcontentlengthfunc(). We need discardfunc() above
			* because HEADER will dump the headers to stdout
			* without it.
			*/
			curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 1L);
			curl_easy_setopt(curlhandle, CURLOPT_HEADER, 1L);
			r = curl_easy_perform(curlhandle);
			if (r != CURLE_OK)
				continue;
			curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 0L);
			curl_easy_setopt(curlhandle, CURLOPT_HEADER, 0L);
			fseek(f, uploaded_len, SEEK_SET);
			curl_easy_setopt(curlhandle, CURLOPT_APPEND, 1L);
		}
		else { /* no */
			curl_easy_setopt(curlhandle, CURLOPT_APPEND, 0L);
		}
		r = curl_easy_perform(curlhandle);
	}

	fclose(f);
	if (r == CURLE_OK)
		return 1;
	else {
		fprintf(stderr, "%s/n", curl_easy_strerror(r));
		return 0;
	}
}


int upload_dump_file_func(std::string user,std::string pwd,std::string url,std::string path) {

	CURL *curlhandle = NULL;
	CURL *curldwn = NULL;
	curl_global_init(CURL_GLOBAL_ALL);
	curlhandle = curl_easy_init();
	curldwn = curl_easy_init();

	std::string result=path+".zip";
	std::string filename=GetFileNameByFilePath(result);
	zipEnFile(path, result.c_str());
	std::string url_r="ftp://"+user+":"+pwd+"@"+url+"/"+filename;//"ftp://cd:123@127.0.0.1/libcurl.zip"

	upload(curlhandle,url_r.c_str() , result.c_str(), 1, 3);
	DeleteFile(result.c_str());
	curl_easy_cleanup(curlhandle);
	curl_easy_cleanup(curldwn);
	curl_global_cleanup();
	return 0;
}




























void CCrashRptUploadDlg::OnBnClickedButton1()
{
	if(((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck()==BST_CHECKED )
	{
		upload_dump_file_func(u_user,u_pwd,u_url,szDumpPath);
	}
	if(((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck()==BST_CHECKED)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );
		CreateProcess(NULL, (LPSTR)szAppPath.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	}

	DeleteFile(szDumpPath.c_str());
	PostMessage(WM_CLOSE);
}

void CCrashRptUploadDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	DeleteFile(szDumpPath.c_str());
	PostMessage(WM_CLOSE);
}

void CCrashRptUploadDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	DeleteFile(szDumpPath.c_str());
	CDialog::OnClose();
}
