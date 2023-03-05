// NewBackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewDlg.h"
#include "NewBackDlg.h"
#include "SkinImgMgr.h"
#include "DlgAreaSelect.h"
#include"tlhelp32.h"
// CNewBackDlg dialog
#include <map>

extern int RetrieveFileFromInternet(CHAR* pHttpAddress,CHAR* pFileFullPath);

SkinImgMgr  ImgMgr;
IMPLEMENT_DYNAMIC(CNewBackDlg, CDialog)
extern _tstring strVersion_LOC;
extern _tstring strVersion_NEW;
CNewBackDlg::CNewBackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewBackDlg::IDD, pParent)
{


}

CNewBackDlg::~CNewBackDlg()
{
}

void CNewBackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewBackDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_1, IDC_BUTTON_X, OnButtonClicked)
	ON_MESSAGE(WM_DRAW_PROGRESS ,Message_DrawProgress)
	ON_MESSAGE(WM_DRAW_TEXT ,Message_DrawText)  
	ON_MESSAGE(WM_UPDATE_FINISH ,Message_UpdateFinish)
	ON_MESSAGE(WM_GET_VER ,Message_GetVer)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CLauncherBackDlg message handlers
void CNewBackDlg::OnButtonClicked(UINT nID)
{
	int nIndex = nID-IDC_BUTTON_1;
	btnstruct * node=(btnstruct *)btnptr.GetAt(nIndex);
	if(!node->info->_szHref.empty())
	{
		ShellExecute(NULL, "open", "IEXPLORE", (LPCSTR)node->info->_szHref.c_str(), NULL,SW_SHOWMAXIMIZED); 
	}
	else if (!node->info->_app.empty())
	{
		if (node->info->_szName == "ok")
		{
			if(bNeedUpdate)
			{
				if (FindClientProcess(_T("Client.exe")))
				{
					MessageBox("请关闭客户端再进行自动更新!","warning",MB_OK);
					return;
				}
				for(int i=0;i<btnptr.GetCount();i++)
				{
					btnstruct * node1=(btnstruct *)btnptr.GetAt(i);
					if(node1->info->_szName=="ok")
					{
						node1->btn->EnableWindow(false);
					}
				}
				cUpdate.start();
			}
			else
				RunMain();
		}
		else
		{
			::ShellExecute(NULL, _T("open"), node->info->_app.c_str(), NULL, NULL, NULL);
		}
		//	::PostQuitMessage(0);
	}
	if(node->info->_szName=="exit")
	{
		//ShowWindow(SW_MINIMIZE);

		CWnd * dlg=         AfxGetApp()-> GetMainWnd();
		::SendMessage(dlg->m_hWnd,WM_CLOSE,NULL,0);
	}
}

unsigned int ren;
void CNewBackDlg::RunMain()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	bool downloaded = false;
	if (bNeedDownList)
	{
		DeleteFile("client\\serverlist.config");

		CHttpDownload GHttpDownload1;
		GHttpDownload1.Init();
		for (int n =0; n < vec_ServerlistAddr.size();n++)
		{
			ren = GHttpDownload1.Download(vec_ServerlistAddr[n].c_str(), "client\\serverlist.config");

			if(ren==DOWNLOAD_RESULT_SUCCESS)
			{
				downloaded = true;
				break;
			}
		}
		//for (int n =0; n < vec_ServerlistAddr.size();n++)
		//{
		//	//-1错误,0成功
		//	ren = RetrieveFileFromInternet((LPSTR)vec_ServerlistAddr[n].c_str(), "client\\serverlist.config");
		//	if (ren == 0)
		//	{
		//		break;
		//	}
		//}
	}
	if (downloaded)
	{
		CreateProcess(NULL, (LPSTR)_PathMainApp.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	}
	else
	{
		MessageBox("下载服务器列表错误,请检查网络后重新启动客户端!","警告",MB_OK);
	}

	CWnd * dlg= AfxGetApp()-> GetMainWnd();
	::SendMessage(dlg->m_hWnd,WM_CLOSE,NULL,0);

//	ShellExecute(NULL, "Open", _PathMainApp.c_str(), "-package", NULL, SW_SHOWNORMAL);
	// 得到Windows目录
/*	BOOL ret = CreateProcess(
		s.c_str(),
		NULL,
		NULL, 
		NULL, 
		FALSE, 
		0, 
		NULL, 
		NULL, 
		&si,
		&pi );
/*	
	BOOL ret = CreateProcess(s.c_str(),NULL,
		NULL, 
		NULL, 
		FALSE, 
		0, 
		NULL, 
		NULL, 
		&si,
		&pi );
*/	
}

void CNewBackDlg::Load_update_TipXML(CString filename)
{
	if( !m_TiXmlDoc.LoadFile(filename) )
	{
		return;
	}
	tiplist_.clear();
	const char* szValue = NULL;
	m_TiElemRoot	= m_TiXmlDoc.FirstChildElement("root");
	if(m_TiElemRoot)
	{
		TiXmlElement* lpButton = m_TiElemRoot;
		if(lpButton)
		{
			TiXmlElement* lpChild = lpButton->FirstChildElement("str");
			while(lpChild)
			{
				BtnInfo btn;
				szValue = lpChild->Attribute("value");
				if(szValue)
					btn._szTip = szValue;
				szValue = lpChild->Attribute("name");
				if(szValue)
					btn._szName = szValue;
				tiplist_.push_back(btn);
				lpChild = lpChild->NextSiblingElement();
			}
		}
	}
}

HBRUSH CNewBackDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if(nCtlColor=CTLCOLOR_DLG)
		return m_brush;
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

BOOL CNewBackDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_brush.CreateSolidBrush(RGB(128,128,128));
	DWORD dwExStyle=GetWindowLong(m_hWnd,GWL_EXSTYLE);
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwExStyle|0x80000);

	HMODULE hInst=LoadLibrary("User32.DLL");
	typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
	MYFUNC SetLayeredWindowAttributes = NULL;
	SetLayeredWindowAttributes=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes"); 
	SetLayeredWindowAttributes(this->GetSafeHwnd(),RGB(128,128,128),0,1); 
	FreeLibrary(hInst);

	bSelectArea=true;
	LoadXML(_T(".\\UpData\\bk.xml"));
	Load_update_TipXML(".\\UpData\\update_config.xml");
	extern CWnd * wndNotify;
	wndNotify = CWnd::FromHandle(this->m_hWnd);
	for(int i=0;i<btnptr.GetCount();i++)
	{
		btnstruct * node1=(btnstruct *)btnptr.GetAt(i);
		if(node1->info->_szName=="ok")
		{
			node1->btn->EnableWindow(false);
		}
	}
	
// 	CString   sFile= CONFIGFILENAME_LAUNCHER; 
// 	char buf[MAX_PATH];
// 	GetPrivateProfileString("Default","image","",buf,MAX_PATH,sFile); 
// 	string name=buf;
// 	if(!name.empty())
// 	{
// 		for(int i=0;i<btnptr.GetCount();i++)
// 		{
// 			btnstruct * node1=(btnstruct *)btnptr.GetAt(i);
// 			if(node1->info->_szName=="selectarea")
// 			{
// 				node1->btn->SetButtonImage(name.c_str(), RGB(0,0,255));
// 			}	
// 		}
// 	}

	bNeedUpdate=true;
	//if (FindClientProcess(_T("Client-Debug.exe")))
	//{
	//	MessageBox("123","123",MB_OK);
	//	return TRUE;
	//}

	cUpdate.start();
	return TRUE;
}

bool CNewBackDlg::FindClientProcess(LPCTSTR name)
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

BOOL CNewBackDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg-> message==WM_KEYDOWN   &&   pMsg-> wParam==VK_ESCAPE)  {   return   TRUE;} 
	if(pMsg-> message==WM_KEYDOWN   &&   pMsg-> wParam==VK_RETURN)  { return   TRUE;   }
	else   
	return CDialog::PreTranslateMessage(pMsg);
}

void CNewBackDlg::LoadXML(CString filename)
{
	if( !m_TiXmlDoc.LoadFile(filename) )
	{
		return;
	}
	const char* szValue = NULL;
	bNeedDownList = true;
	m_TiElemRoot	= m_TiXmlDoc.FirstChildElement("root");
	if(m_TiElemRoot)
	{
		TiXmlElement* lpWindow  = m_TiElemRoot->FirstChildElement("browser1");		
		if(lpWindow)
		{
			TiXmlElement* lpChild = lpWindow->FirstChildElement("rect");
			if(lpChild)
			{
				szValue = lpChild->Attribute("value");  CRect rect;
				if(szValue)
				{	
					sscanf(szValue, "%d, %d, %d, %d", &rect.left, &rect.top, &rect.right, &rect.bottom);
					GetDlgItem(IDC_EXPLORER1)->MoveWindow(rect);	
					CRect rc;
					GetDlgItem(IDC_EXPLORER1)->GetClientRect(rc);
					EmbedBrowserObject((GetDlgItem(IDC_EXPLORER1))->m_hWnd);
					ResizeBrowser((GetDlgItem(IDC_EXPLORER1))->m_hWnd,rc.Width(),rc.Height());
					DisplayHTMLPage( (GetDlgItem(IDC_EXPLORER1))->m_hWnd, (LPTSTR)lpWindow->Attribute("href"));
				}
			}
		}
		TiXmlElement* lpButton = m_TiElemRoot->FirstChildElement("button");
		if(lpButton)
		{
			TiXmlElement* lpChild = lpButton->FirstChildElement("style");
			while(lpChild)
			{
				BtnInfo btn;
				szValue = lpChild->Attribute("name");
				if(szValue)
					btn._szName = szValue;
				TiXmlElement* lpStr = lpChild->FirstChildElement("image");
				if(lpStr)
				{
					szValue = lpStr->Attribute("file");
					if(szValue)
						btn._szImg = szValue;
				}
				lpStr = lpChild->FirstChildElement("rect");
				if(lpStr)
				{
					szValue = lpStr->Attribute("value");
					if(szValue)
						sscanf(szValue, "%d, %d, %d, %d", &btn._rc.left, &btn._rc.top, &btn._rc.right, &btn._rc.bottom);
				}
				lpStr = lpChild->FirstChildElement("tip");
				if(lpStr)
				{
					szValue = lpStr->Attribute("value");
					if(szValue)
						btn._szTip = szValue;
				}
				lpStr = lpChild->FirstChildElement("href");
				if(lpStr)
				{
					szValue = lpStr->Attribute("value");
					if(szValue)
						btn._szHref = szValue;
				}
				lpStr = lpChild->FirstChildElement("app");
				if(lpStr)
				{
					szValue = lpStr->Attribute("value");
					if(szValue)
						btn._app = szValue;
				}
				AddButton(&btn);
				lpChild = lpChild->NextSiblingElement();
			}
		}
		TiXmlElement* lpMainApp  = m_TiElemRoot->FirstChildElement("mainapp");
		if(lpMainApp)
		{
			TiXmlElement* lpChild = lpMainApp->FirstChildElement("path");
			if(lpChild)
			{
				szValue = lpChild->Attribute("file");
				if(szValue)  
					_PathMainApp=szValue;

				char chlist[32];
				memset(chlist,0,sizeof(char)*32);
				int index = 0;
				while(1)
				{
					sprintf(chlist,"serverlist%d",index);
					szValue = lpChild->Attribute(chlist);
					if(szValue) 
					{
						string _ServerlistAddr=szValue;
						vec_ServerlistAddr.push_back(_ServerlistAddr);
						index++;
					}
					else
						break;
				}
				szValue = lpChild->Attribute("need");
				if(szValue)  
					bNeedDownList=atoi(szValue);				
			}			
		}
		
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
				{	
					sscanf(szValue, "%d, %d, %d, %d", &progressnow.rect.left, &progressnow.rect.top, &progressnow.rect.right, &progressnow.rect.bottom);
					textfile.rect.left=progressnow.rect.left;textfile.rect.top=progressnow.rect.top-35;
					textfile.rect.right=progressnow.rect.right;textfile.rect.bottom=progressnow.rect.bottom-22;
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
		lpButton = m_TiElemRoot->FirstChildElement("pack-server");
		if(lpButton)
		{
			TiXmlElement* lpChild = lpButton->FirstChildElement("style");
			while(lpChild)
			{
				string _szTipTemp;				
				TiXmlElement* lpStr = lpChild->FirstChildElement("tip");
				if(lpStr)
				{
					szValue = lpStr->Attribute("value");
					if(szValue)
						_szTipTemp = szValue;
				}
				lpStr = lpChild->FirstChildElement("ip");
				if(lpStr)
				{
					char chvalue[32];
					memset(chvalue,0,sizeof(char)*32);
					int index = 0;
					while(1)
					{
						sprintf(chvalue,"value%d",index);
						szValue = lpStr->Attribute(chvalue);
						if(szValue)
						{
							BtnInfo btn;
							btn._szName = szValue;
							btn._szTip = _szTipTemp;
							cUpdate.iplist_.push_back(btn);
							index++;
						}
						else
							break;
					}
				}
				
				lpChild = lpChild->NextSiblingElement();
			}
		}
		TiXmlElement* lpColor  = m_TiElemRoot->FirstChildElement("ver-new");
		if(lpColor)
		{
			AddFont(lpColor,_NewVer);
		}
		lpColor  = m_TiElemRoot->FirstChildElement("ver-local");
		if(lpColor)
		{
			AddFont(lpColor,_LocVer);
		}
		lpColor = m_TiElemRoot->FirstChildElement("down-tip-text");
		if(lpColor)
		{
			AddFont(lpColor,textfile);
		}	
		lpColor = m_TiElemRoot->FirstChildElement("update-tip");
		if(lpColor)
		{
			AddFont(lpColor,needupdate);
		}
	}
}

void CNewBackDlg::AddFont(TiXmlElement* lpColor,Fontinfo &info)
{
	if(lpColor)
	{
		const char* szValue;
		int crColorR=0;int crColorG=0;int crColorB=0;
		TiXmlElement* lpChild = lpColor;
		szValue = lpChild->Attribute("red");
		if(szValue)  
		{
			crColorR=atoi(szValue);
			if(crColorR<0)crColorR=0;
			if(crColorR>255)crColorR=255;
		}
		szValue = lpChild->Attribute("green");
		if(szValue)  
		{
			crColorG=atoi(szValue);
			if(crColorG<0)crColorG=0;
			if(crColorG>255)crColorG=255;
		}

		szValue = lpChild->Attribute("blue");
		if(szValue)  
		{
			crColorB=atoi(szValue);
			if(crColorB<0)crColorB=0;
			if(crColorB>255)crColorB=255;	
		}

		szValue = lpChild->Attribute("font-size");
		if(szValue)  
		{
			info.size=atoi(szValue);
		}

		szValue = lpChild->Attribute("rect");  
		if(szValue)
			sscanf(szValue, "%d, %d, %d, %d", &info.rect.left, &info.rect.top, &info.rect.right, &info.rect.bottom);

		szValue = lpChild->Attribute("tip");
		if(szValue)
			info.text = szValue;

		info.font.CreateFont( _NewVer.size,                                          //   nHeight      
			0,                                                   //   nWidth      
			0,                                                   //   nEscapement    
			0,                                                   //   nOrientation      
			FW_BOLD,//FW_NORMAL,                                   //   nWeight      
			FALSE,                                           //   bItalic      
			FALSE,                                           //   bUnderline      
			0,                                                   //   cStrikeOut      
			ANSI_CHARSET,                             //   nCharSet      
			OUT_DEFAULT_PRECIS,                 //   nOutPrecision      
			CLIP_DEFAULT_PRECIS,               //   nClipPrecision      
			DEFAULT_QUALITY,                       //   nQuality      
			DEFAULT_PITCH   |   FF_SWISS,     //   nPitchAndFamily        
			_T("幼圆"));   //微软雅黑楷体_GB2312

		info.crColor=RGB(crColorR,crColorG,crColorB);//(255,188,0,255)
	}

}

void CNewBackDlg::AddButton(BtnInfo *info,int ctrlid)
{
	if(ctrlid==0)
		btnsruct_ID=btnptr.GetCount();
	else btnsruct_ID=ctrlid;
	CKbcButton *btn=new CKbcButton;
	btn->Create("区域选择",BS_PUSHBUTTON |WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_OWNERDRAW ,
		CRect(0,0,100,50),this,IDC_BUTTON_1+btnsruct_ID);

	btn->SetButtonImage(info->_szImg.c_str(), RGB(0,0,255));
	btn->MoveWindow(info->_rc.left, info->_rc.top, info->_rc.right, info->_rc.bottom);
	btn->SetToolTipText(info->_szTip.c_str());

	BtnInfo * btninfo=new BtnInfo;
	*btninfo=*info;
	btnstruct * node =new btnstruct;
	node->btn=btn;
	node->info=btninfo;
	btnptr.InsertAt(btnptr.GetCount(),node);

}

LRESULT CNewBackDlg::Message_GetVer(WPARAM wParam,LPARAM lParam)
{
	if(strVersion_LOC==strVersion_NEW)
	{
		bNeedUpdate=false;
	}
	InvalidateRect(_NewVer.rect);
	InvalidateRect(_LocVer.rect);
	InvalidateRect(needupdate.rect);
	for(int i=0;i<btnptr.GetCount();i++)
	{
		btnstruct * node1=(btnstruct *)btnptr.GetAt(i);
		if(node1->info->_szName=="ok")
		{
			node1->btn->EnableWindow(true);
		}
	}
	return 0;
}

LRESULT CNewBackDlg::Message_UpdateFinish(WPARAM wParam,LPARAM lParam)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	RunMain();
	return 0;
}

LRESULT CNewBackDlg::Message_DrawProgress(WPARAM wParam,LPARAM lParam)
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


CString SmallString(CString str)
{
	CString s;
	s=str;
	if(str.GetLength()>50)
	{
		s=str.Left(16);
		s+="......";
		s+=str.Right(16);
	}
	return s;
}

LRESULT CNewBackDlg::Message_DrawText(WPARAM wParam,LPARAM lParam)
{
	char *ss=(char *) wParam;
	textfile.text=ss;
	textfile.text=SmallString(textfile.text);
	InvalidateRect(textfile.rect);
	return 0;
}
void CNewBackDlg::OnPaint()
{
	CPaintDC dc(this); 
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


	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&textfile.font);   
	dc.SetTextColor(textfile.crColor);
	dc.TextOut(textfile.rect.left,textfile.rect.top, textfile.text);

	CString s;
	dc.SelectObject(&_LocVer.font);  
	dc.SetTextColor(_LocVer.crColor);
	s.Format("%s",strVersion_LOC.c_str());
	dc.TextOut(_LocVer.rect.left,_LocVer.rect.top, s);

	dc.SelectObject(&_NewVer.font);  
	dc.SetTextColor(_NewVer.crColor);
	s.Format("%s",strVersion_NEW.c_str());
	dc.TextOut(_NewVer.rect.left,_NewVer.rect.top, s);

	if(bNeedUpdate)
	{
		dc.SelectObject(&needupdate.font);  
		dc.SetTextColor(needupdate.crColor);
		dc.TextOut(needupdate.rect.left,needupdate.rect.top, needupdate.text);
	}
}
