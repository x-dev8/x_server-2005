// DlgAreaSelect.cpp : implementation file
//

#include "stdafx.h"
#include "NewDlg.h"
#include "DlgAreaSelect.h"
#include "SkinImgMgr.h"

// CDlgAreaSelect dialog
extern SkinImgMgr  ImgMgr  ;
IMPLEMENT_DYNAMIC(CDlgAreaSelect, CDialog)

CDlgAreaSelect::CDlgAreaSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAreaSelect::IDD, pParent)
{

}

CDlgAreaSelect::~CDlgAreaSelect()
{
}

void CDlgAreaSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	

	DDX_Control(pDX,	IDC_SA_OK,		_btnOK);
	DDX_Control(pDX,	IDC_SA_Cancel,	_btnCancel);
	
	

}


BEGIN_MESSAGE_MAP(CDlgAreaSelect, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_1, IDC_BUTTON_X, OnButtonClicked)

	ON_BN_CLICKED(IDC_SA_OK, &CDlgAreaSelect::OnBnClickedSaOk)
	ON_BN_CLICKED(IDC_SA_Cancel, &CDlgAreaSelect::OnBnClickedSaCancel)
END_MESSAGE_MAP()
void CDlgAreaSelect::OnButtonClicked(UINT nID)
{
	int nIndex = nID-IDC_BUTTON_1;
	if(_nAreaIndex>=0&&_nAreaIndex<=btnptr.GetCount())
	{
		btnstruct * node= (btnstruct *)btnptr.GetAt(_nAreaIndex);
		node->btn->SetButtonEnable();
	}
	
	btnstruct * node= (btnstruct *)btnptr.GetAt(nIndex);
	node->btn->SetButtonDisable();
	_nAreaIndex=nIndex;

	
	
}
void CDlgAreaSelect::AddButton(BtnInfo *info,int ctrlid)
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
// CDlgAreaSelect message handlers

BOOL CDlgAreaSelect::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_brush.CreateSolidBrush(RGB(255,0,255));		//背景设置为粉红色

	//SetWindowsLong将窗体设置为层级窗体
	DWORD dwExStyle=GetWindowLong(m_hWnd,GWL_EXSTYLE);
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwExStyle|0x80000);

	//用SetLayeredWindowAttributes设置透明色为0，它比UpdateLayeredWindow的使用要简单些
	HMODULE hInst=LoadLibrary("User32.DLL");
	typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
	MYFUNC SetLayeredWindowAttributes = NULL;
	SetLayeredWindowAttributes=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes"); 
	SetLayeredWindowAttributes(this->GetSafeHwnd(),0xff00ff,0,1); 
	FreeLibrary(hInst); 
	// TODO:  Add extra initialization here


   image=NULL;
 //   image=ImgMgr.AddImg("LauncherUI\\selectarea.bmp");

    m_dwFlags = 0;


    LoadXML("UpData\\SelectAreaDlg.xml");

	_btnOK.SetButtonImage(_btnOk_info._szImg.c_str(), RGB(0,0,255));
	_btnOK.MoveWindow( _btnOk_info._rc.left, _btnOk_info._rc.top, _btnOk_info._rc.right, _btnOk_info._rc.bottom );
//	_btnOK.MoveWindow( _rcBtn1.left, _rcBtn1.top, _rcBtn1.right, _rcBtn1.bottom );
	_btnOK.SetToolTipText( _btnOk_info._szTip.c_str() );

	_btnCancel.SetButtonImage(_btnCancel_info._szImg.c_str() , RGB(0,0,255));
	_btnCancel.MoveWindow( _btnCancel_info._rc.left, _btnCancel_info._rc.top, _btnCancel_info._rc.right, _btnCancel_info._rc.bottom );
//	_btnCancel.MoveWindow( _rcBtn2.left, _rcBtn2.top, _rcBtn2.right, _rcBtn2.bottom );
	_btnCancel.SetToolTipText( _btnCancel_info._szTip.c_str() );
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDlgAreaSelect::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if(nCtlColor=CTLCOLOR_DLG)
		return m_brush;
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

BOOL CDlgAreaSelect::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rtClient;
	GetClientRect(rtClient);

	Graphics graph(pDC->m_hDC);
	if(image)
		graph.DrawImage (image,0, 0,rtClient.Width(),rtClient.Height());
	return true;
	return CDialog::OnEraseBkgnd(pDC);
}
void CDlgAreaSelect::LoadXML(CString filename)
{
	TiXmlDocument	doc;
	if( !doc.LoadFile(filename) )
	{
		assert(false && "Login.cpp::SelectAreaDlg.xml 读取文件出错");
		return;
	}
	
	const char* szValue = NULL;
	TiXmlElement* root	= doc.FirstChildElement("root");
	if( root )
	{
		TiXmlElement* imgbg = root->FirstChildElement("imagebg");
		if( imgbg )
		{
			TiXmlElement* imagebtn = imgbg->FirstChildElement("image");
			if( imagebtn )
			{
				szValue = imagebtn->Attribute("file");
				if( szValue )
				{
					image=ImgMgr.AddImg(szValue);
				}
			}
			TiXmlElement* imagerect = imgbg->FirstChildElement("rect");
			if( imagerect )
			{
				szValue = imagerect->Attribute("value");
				CRect rc;
				if( szValue )
				{
					sscanf( szValue, "%d, %d, %d, %d", &rc.left, &rc.top, &rc.right, &rc.bottom );
					this->MoveWindow(rc);
				}
			}
			
		}
		TiXmlElement* button1 = root->FirstChildElement("button1");
		if( button1 )
		{
			TiXmlElement* imagebtn = button1->FirstChildElement("image");
			if( imagebtn )
			{
				szValue = imagebtn->Attribute("file");
				if( szValue )
				{
					_btnOk_info._szImg= szValue;
				}
			}
			TiXmlElement* imagerect = button1->FirstChildElement("rect");
			if( imagerect )
			{
				szValue = imagerect->Attribute("value");
				if( szValue )
				{
					sscanf( szValue, "%d, %d, %d, %d", &_btnOk_info._rc.left, &_btnOk_info._rc.top, &_btnOk_info._rc.right, &_btnOk_info._rc.bottom );
				}
			}
			TiXmlElement* imagetip = button1->FirstChildElement("tip");
			if( imagetip )
			{
				szValue = imagetip->Attribute("value");
				if( szValue )
				{
					_btnOk_info._szTip = szValue;
				}
			}
		}
		TiXmlElement* button2 = root->FirstChildElement("button2");
		if( button2 )
		{
			TiXmlElement* imagebtn = button2->FirstChildElement("image");
			if( imagebtn )
			{
				szValue = imagebtn->Attribute("file");
				if( szValue )
				{
					_btnCancel_info._szImg = szValue;
				}
			}
			TiXmlElement* imagerect = button2->FirstChildElement("rect");
			if( imagerect )
			{
				szValue = imagerect->Attribute("value");
				if( szValue )
				{
					sscanf( szValue, "%d, %d, %d, %d", &_btnCancel_info._rc.left, &_btnCancel_info._rc.top, &_btnCancel_info._rc.right, &_btnCancel_info._rc.bottom );
				}
			}
			TiXmlElement* imagetip = button2->FirstChildElement("tip");
			if( imagetip )
			{
				szValue = imagetip->Attribute("value");
				if( szValue )
				{
					_btnCancel_info._szTip = szValue;
				}
			}
		}
		TiXmlElement* lpButton = root->FirstChildElement("button");
		if(lpButton)
		{
			TiXmlElement* lpChild = lpButton->FirstChildElement("style");
			while(lpChild)
			{
				BtnInfo btn;
				szValue = lpChild->Attribute("name");
			//	memcpy((char *)btn._szName,szValue,strlen(szValue));
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
				lpStr = lpChild->FirstChildElement("ip");
				if(lpStr)
				{
					szValue = lpStr->Attribute("value");
					if(szValue)
						btn._szHref = szValue;
				}
				lpStr = lpChild->FirstChildElement("port");
				if(lpStr)
				{
					szValue = lpStr->Attribute("value");
					if(szValue)
						btn._port = szValue;
				}
			//	m_vecBtnInfo.push_back(btn);
                AddButton(&btn);
				lpChild = lpChild->NextSiblingElement();
			}
		}
	}
}
void CDlgAreaSelect::OnLButtonDown(UINT nFlags, CPoint point)
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

void CDlgAreaSelect::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ( m_dwFlags & DRAGGING )
	{
		m_dwFlags &= ~DRAGGING;
		ReleaseCapture();
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgAreaSelect::OnMouseMove(UINT nFlags, CPoint point)
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


void CDlgAreaSelect::OnBnClickedSaOk()
{
	SendMessage(WM_CLOSE);

}

void CDlgAreaSelect::OnBnClickedSaCancel()
{
	_nAreaIndex=-1;
	SendMessage(WM_CLOSE);
	// TODO: Add your control notification handler code here
}

BOOL CDlgAreaSelect::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg-> message==WM_KEYDOWN   &&   pMsg-> wParam==VK_ESCAPE)  {   return   TRUE;} 
	if(pMsg-> message==WM_KEYDOWN   &&   pMsg-> wParam==VK_RETURN)  { return   TRUE;   }
	else   
	return CDialog::PreTranslateMessage(pMsg);
}
