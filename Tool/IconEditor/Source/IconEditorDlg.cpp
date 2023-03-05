// IconEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IconEditor.h"
#include "IconEditorDlg.h"
#include "folder_dialog.h"

#include "application_config.h"
#include "tstring.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define Set_Config_File "Set.ini"
#define Set_Secion "SetInfo"
#define Image_Key "ImageFile"
#define Xml_Key "XmlFile"
#define RelaPath_Key "RelaPath"
#define SkillBgd_Key "SkillBgd"
#define Profession_Key "Type"
#define IconWidth_Key	"IconWidth"
#define IconHeight_Key	"IconHeight"


#define SkillBgd "Ui\\Common\\UIresource18.tga"

const static char* s_pszRelaPath[] = 
{
	"Ui/Icon/NormalItem/",
	"Ui/Icon/Skillicon/Skill/",
	"/Ui/Icon/Armour/",
	"/Ui/Icon/Weapon/",
    "/Ui/Icon/SkillIcon/XinFa/"
};
// CIconEditorDlg dialog

CIconEditorDlg::CIconEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIconEditorDlg::IDD, pParent)
	, m_RadioType(0)
	, m_RadioProfession(0)
	, m_RadioSkillType(0)
	, m_RadioLoad(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bChange = false;
	m_bCanSave = false;

	m_nStartIconCount = 0;

	m_nRowCount = 0; 
	m_nColumnCount = 0;

	m_nIconWidth = 40;
	m_nIconHeight = 40;

	m_nImageIndex = 0;
}

void CIconEditorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST2, m_listImageFile);
    DDX_Control(pDX, IDC_EDIT1, m_editImageFilePath);
    DDX_Control(pDX, IDC_STATIC_IMAGE, m_staticImage);
    DDX_Control(pDX, IDC_EDIT2, m_editXmlFile);
    DDX_Control(pDX, IDC_EDIT10, m_editRelaPath);
    DDX_Control(pDX, IDC_EDIT3, m_editItemID);
    DDX_Control(pDX, IDC_EDIT4, m_editItemName);
    DDX_Control(pDX, IDC_EDIT5, m_editImageName);
    DDX_Control(pDX, IDC_EDIT6, m_editRow);
    DDX_Control(pDX, IDC_EDIT7, m_editColumn);
    DDX_Control(pDX, IDC_EDIT8, m_editFirstID);
    DDX_Control(pDX, IDC_EDIT9, m_editEndID);
    DDX_Control(pDX, IDC_STATIC_INFO, m_staticInfo);
    DDX_Control(pDX, IDC_LIST1, m_listIcon);
    DDX_Control(pDX, IDC_BUTTON4, m_buttonSaveXml);
    DDX_Control(pDX, IDC_STATIC_COUNT, m_staticCount);
    DDX_Control(pDX, IDC_BUTTON8, m_buttonEdit);
    DDX_Radio(pDX, IDC_RADIO14, m_RadioType);
    DDX_Radio(pDX, IDC_RADIO3, m_RadioProfession);
    DDX_Control(pDX, IDC_EDIT11, m_editSkillBgd);
    DDX_Radio(pDX, IDC_RADIO9, m_RadioSkillType);
    DDX_Control(pDX, IDC_EDIT12, m_editWidth);
    DDX_Control(pDX, IDC_EDIT13, m_editHeight);
    DDX_Radio(pDX, IDC_RADIO12, m_RadioLoad);
    DDX_Control(pDX, IDC_RADIO14, m_radioItem);
}

BEGIN_MESSAGE_MAP(CIconEditorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CIconEditorDlg::OnBnClickedButtonFile)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CIconEditorDlg::OnNMClickListImageFile)
	ON_BN_CLICKED(IDC_BUTTON2, &CIconEditorDlg::OnBnClickedButtonXmlFile)
	ON_WM_DESTROY()
	ON_STN_CLICKED(IDC_STATIC_IMAGE, &CIconEditorDlg::OnStnClickedStaticImage)
	ON_BN_CLICKED(IDC_BUTTON7, &CIconEditorDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON3, &CIconEditorDlg::OnBnClickedButtonLoadXml)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CIconEditorDlg::OnNMClickListIconInfo)
	ON_BN_CLICKED(IDC_BUTTON4, &CIconEditorDlg::OnBnClickedButtonSaveXml)
	ON_BN_CLICKED(IDC_BUTTON8, &CIconEditorDlg::OnBnClickedButtonEditIcon)
	ON_BN_CLICKED(IDOK, &CIconEditorDlg::OnBnClickedOk)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON9, &CIconEditorDlg::OnBnClickedButtonBatchAdd)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CIconEditorDlg::OnNMRclickListIcon)
	ON_COMMAND(ID_DELETE, &CIconEditorDlg::OnDelete)

	ON_REGISTERED_MESSAGE(WM_XLISTCTRL_EDIT_END, OnEditEnd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CIconEditorDlg::OnLvnItemchangedListIcon)
	ON_BN_CLICKED(IDC_BUTTON10, &CIconEditorDlg::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON11, &CIconEditorDlg::OnBnClickedButtonBatchDelete)
	ON_BN_CLICKED(IDC_BUTTON12, &CIconEditorDlg::OnBnClickedButtonOpenXml)
	ON_BN_CLICKED(IDC_RADIO3, &CIconEditorDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO14, &CIconEditorDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO15, &CIconEditorDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &CIconEditorDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CIconEditorDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CIconEditorDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CIconEditorDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CIconEditorDlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CIconEditorDlg::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &CIconEditorDlg::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, &CIconEditorDlg::OnBnClickedRadio11)
	ON_EN_CHANGE(IDC_EDIT12, &CIconEditorDlg::OnEnChangeEditIconWidth)
	ON_EN_CHANGE(IDC_EDIT13, &CIconEditorDlg::OnEnChangeEditIconHeight)
	ON_BN_CLICKED(IDC_RADIO16, &CIconEditorDlg::OnBnClickedRadio16)
	ON_BN_CLICKED(IDC_RADIO17, &CIconEditorDlg::OnBnClickedRadio17)
    ON_BN_CLICKED(IDC_RADIO18, &CIconEditorDlg::OnBnClickedRadio18)
END_MESSAGE_MAP()


// CIconEditorDlg message handlers

BOOL CIconEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	InitInformation();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIconEditorDlg::OnPaint()
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
		ShowImage();
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIconEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CIconEditorDlg::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			OnBnClickedButtonFind();
			return TRUE;
		case VK_ESCAPE:
			return TRUE;
	
		case VK_CONTROL:
			if (GetFocus()->m_hWnd == m_staticImage.m_hWnd)
			{
				m_listIcon.SetFocus();
			}
			else
			{
				m_staticImage.SetFocus();
			}			
			
			break;

		default:
			if (KeyMoveIcon(pMsg->wParam))
			{
				return TRUE;
			}
		
			break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CIconEditorDlg::InitInformation()
{
	char szVersion[100] = "";
	sprintf_s(szVersion, sizeof(szVersion) - 1, "Icon编辑器 %s", ApplicationConfig::Instance().GetFullVersion());
	SetWindowText(szVersion);

	m_buttonSaveXml.EnableWindow(FALSE);	
	//////////////////////////////////////////////////////////////////
	
	//计算图片显示的相对位置
	RECT rect1;
	this->GetClientRect(&rect1);
	this->ClientToScreen(&rect1);

	RECT rect2;
	m_staticImage.GetClientRect(&rect2);
	m_staticImage.ClientToScreen(&rect2);

	m_xPoint.x = rect2.left - rect1.left;
	m_xPoint.y = rect2.top - rect1.top;

	m_staticImage.GetClientRect(&m_xRect);	

	////////////////////////////////////////////////////////////////////////////
	m_pxImage = NULL;
		
	m_vecIcon.clear();
	m_vecImageFile.clear();
	m_vecImageIndex.clear();
	//////////////////////////////////////////////////////////////////////////////
	char szProcPath[_MAX_PATH] = "";
	char szDir[_MAX_DIR] = "";
	char szDirve[_MAX_DRIVE] = "";

	::GetModuleFileName(NULL, szProcPath, sizeof(szProcPath));

	_tsplitpath(szProcPath, szDirve, szDir, NULL, NULL);
	sprintf_s(m_szFilePath, sizeof(m_szFilePath), "%s%s\\%s", szDirve, szDir, Set_Config_File);		

	/////////////////////////////////////////////////////////////////////////////

	int nWidth = 0;
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

	nWidth = SetListCtrlStyle(m_listImageFile, dwStyle);
	m_listImageFile.InsertColumn(0, "Icon文件名称", 0, nWidth);


	int nIndex = 0;
	nWidth = SetListCtrlStyle(m_listIcon, dwStyle);
	m_listIcon.InsertColumn(nIndex++, "Icon", 0, nWidth * 15 /100);
	m_listIcon.InsertColumn(nIndex++, "ID", 0, nWidth * 10 /100);
	m_listIcon.InsertColumn(nIndex++, "名称", 0, nWidth * 18 /100);
	m_listIcon.InsertColumn(nIndex++, "文件", 0, nWidth * 29 /100);
	m_listIcon.InsertColumn(nIndex++, "行", 0, nWidth * 8 /100);
	m_listIcon.InsertColumn(nIndex++, "列", 0, nWidth * 8 /100);
	m_listIcon.InsertColumn(nIndex++, "大小", 0, nWidth * 12 /100);
	
	////////////////////////////////////////////////////////////////.

	//读设定文件
	ReadSetConfigFile();
	///////////////////////////////////////////////////////////////////////////
	m_xImagelist.Create(Default_Width, Default_Height, ILC_COLOR32, 0, 1);
	m_listIcon.SetImageList(&m_xImagelist, LVSIL_SMALL);
}

void CIconEditorDlg::ReadSetConfigFile()
{
	char szValue[_MAX_PATH] = "";

	m_nIconWidth = GetPrivateProfileInt(Set_Secion, IconWidth_Key, Default_Width, m_szFilePath);
	SetEditText(m_editWidth, "%d", m_nIconWidth);
	m_nIconHeight = GetPrivateProfileInt(Set_Secion, IconHeight_Key, Default_Height, m_szFilePath);
	SetEditText(m_editHeight, "%d", m_nIconHeight);

	::GetPrivateProfileString(Set_Secion, Image_Key, "", szValue, sizeof(szValue) - 1, m_szFilePath);
	m_editImageFilePath.SetWindowText(szValue);

	::GetPrivateProfileString(Set_Secion, Xml_Key, "", szValue, sizeof(szValue) - 1, m_szFilePath);
	m_editXmlFile.SetWindowText(szValue);

	m_RadioType = GetPrivateProfileInt(Set_Secion, Profession_Key, 0, m_szFilePath);
	UpdateData(FALSE);
	EnableRadio(m_RadioType);

	::GetPrivateProfileString(Set_Secion, RelaPath_Key, s_pszRelaPath[m_RadioType], szValue, sizeof(szValue) - 1, m_szFilePath);
	m_editRelaPath.SetWindowText(szValue);

	::GetPrivateProfileString(Set_Secion, SkillBgd_Key, SkillBgd, szValue, sizeof(szValue) - 1, m_szFilePath);
	m_editSkillBgd.SetWindowText(szValue);	
}

void CIconEditorDlg::OnBnClickedButtonFile()
{
	// TODO: Add your control notification handler code here	
	UpdateData(TRUE);

	if (m_RadioLoad == 0)
	{
		CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "DDS File(*.dds)|*.dds|");

		if (FileDlg.DoModal() == IDOK)
		{
			if (LoadImageFile(FileDlg.GetPathName()))
			{
				int nCount = m_listImageFile.GetItemCount();

				m_listImageFile.InsertItem(nCount, GetImageFileName(FileDlg.GetPathName()));
			}
		}
	}
	else
	{
		m_nIconWidth = GetEditInt(m_editWidth, Default_Width);
		m_nIconHeight = GetEditInt(m_editHeight, Default_Height);

		CString strFolder = "";
        m_editImageFilePath.GetWindowText(strFolder);
		CFolderDialog xFolderDialog(&strFolder);
		if (xFolderDialog.DoModal() == IDOK)
		{
			m_editImageFilePath.SetWindowText(strFolder);
			SaveSetConfigFile(Image_Key, strFolder.GetBuffer());

			LoadAllImageFile(strFolder.GetBuffer());
		}
	}
}

void CIconEditorDlg::OnNMClickListImageFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nIndex = GetListItemCurSel(m_listImageFile);
	if (nIndex == -1)
	{
		return;
	}
	m_strImageFileName = m_listImageFile.GetItemText(nIndex, 0);
	UpdateImageFile(m_strImageFileName);
	
	m_editImageName.SetWindowText(m_strImageFileName);

    ShowImagePath(m_strImageFileName); // 显示相对路径

	CString strRelaPath = "";
	m_editRelaPath.GetWindowText(strRelaPath);

	IconInfo xIconInfo;
	xIconInfo.strImage.Format("%s%s", strRelaPath, m_strImageFileName);
	ShowIconInfo(xIconInfo);

	ShowImage();

	*pResult = 0;
}

void CIconEditorDlg::ShowImage()
{
	if (m_pxImage == NULL)
	{
		return;
	}

	CDC *pDC = GetDC();			
	m_pxImage->Draw(pDC->GetSafeHdc(), m_xPoint.x, m_xPoint.y, m_xRect.Width(), m_xRect.Height());
	ReleaseDC(pDC);

	ShowSelectArea(m_xPositionInfo, m_nIconWidth, m_nIconHeight);
}

void CIconEditorDlg::ShowSelectArea(PositionInfo &xPosition, int nWidth, int nHeight)
{
	if (xPosition.nRow == -1 || xPosition.nColumn == -1 || m_pxImage == NULL)
	{
		return;
	}

	int nDrawWidth = m_nIconWidth * m_xRect.Width() / m_pxImage->GetWidth();
	int nDrawHeight = m_nIconHeight * m_xRect.Height() / m_pxImage->GetHeight();

	int nDrawSizeX = nWidth * m_xRect.Width() / m_pxImage->GetWidth();
	int nDrawSizeY = nHeight * m_xRect.Height() / m_pxImage->GetHeight();

	CDC *pDC = GetDC();
	CPen xPen;
	xPen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));	     
	CPen *pOldPen = pDC->SelectObject(&xPen);       

	//先算出坐标
	POINT xFormPoint;
	POINT xToPoint;

	//上
	xFormPoint.x = m_xPoint.x + xPosition.nColumn * nDrawWidth;
	xFormPoint.y = m_xPoint.y + xPosition.nRow * nDrawHeight ;
	xToPoint.x = xFormPoint.x + nDrawSizeX;
	xToPoint.y = xFormPoint.y;
	
	pDC->MoveTo(xFormPoint);
	pDC->LineTo(xToPoint);

	//下
	xFormPoint.x = m_xPoint.x + xPosition.nColumn * nDrawWidth;
	xFormPoint.y = m_xPoint.y + xPosition.nRow * nDrawHeight + nDrawSizeY;
	xToPoint.x = xFormPoint.x + nDrawSizeX;
	xToPoint.y = xFormPoint.y;

	pDC->MoveTo(xFormPoint);
	pDC->LineTo(xToPoint);

	//左
	xFormPoint.x = m_xPoint.x + xPosition.nColumn * nDrawWidth;
	xFormPoint.y = m_xPoint.y + xPosition.nRow * nDrawHeight;
	xToPoint.x = xFormPoint.x;
	xToPoint.y = xFormPoint.y + nDrawSizeY;

	pDC->MoveTo(xFormPoint);
	pDC->LineTo(xToPoint);

	//右
	xFormPoint.x = m_xPoint.x + xPosition.nColumn * nDrawWidth + nDrawSizeX;
	xFormPoint.y = m_xPoint.y +  xPosition.nRow * nDrawHeight;
	xToPoint.x = xFormPoint.x;
	xToPoint.y = xFormPoint.y + nDrawSizeY;

	pDC->MoveTo(xFormPoint);
	pDC->LineTo(xToPoint);

	//还原释放
	pDC->SelectObject(pOldPen);
	ReleaseDC(pDC);
}



void CIconEditorDlg::OnBnClickedButtonXmlFile()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "config File(*.config)|*.config|");

	if (FileDlg.DoModal() == IDOK)
	{
		m_editXmlFile.SetWindowText(FileDlg.GetPathName());	

		SaveSetConfigFile(Xml_Key, FileDlg.GetPathName().GetBuffer());
	}	
}


bool CIconEditorDlg::LoadImageFile(const char* pszFile)
{
	if (pszFile == NULL || *pszFile == 0)
	{
		return false;
	}

	CString strName = GetImageFileName(pszFile);

	if (!IsAlreadyLoad(strName))  //加载没有加载的
	{
		CxImage *pxImage = new CxImage();
		if (pxImage->Load(pszFile, CXIMAGE_FORMAT_DDS))
		{
			pxImage->Flip();		//dds图片格式坐标系Y方向是反的, 调用Flip 来颠倒回来

			InitIconImageList(pxImage, strName);
		}
		return true;
	}

	return false;
}

//加载文件夹里的所有DDS图片 (目前只加载dds)
void CIconEditorDlg::LoadAllImageFile(const char *pszFile)
{
	if (pszFile == NULL || *pszFile == 0)
	{
		return;
	}

	char szFile[_MAX_PATH] = "";
	sprintf_s(szFile, sizeof(szFile) - 1, "%s\\*.dds", pszFile);

	int nCount = 0;

	WIN32_FIND_DATA xFindData;                                     
	HANDLE hFile = FindFirstFileA(szFile, &xFindData);   	
	if(hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			CString strFile = "";
			strFile.Format("%s\\%s", pszFile, xFindData.cFileName);

			if (LoadImageFile(strFile.GetBuffer()))
			{
				m_listImageFile.InsertItem(nCount, xFindData.cFileName);
				++nCount;
			}			
		}while(FindNextFileA(hFile, &xFindData));                      
		FindClose(hFile);
	}

	if (nCount != 0)
	{
		m_pxImage = m_vecImageFile[0].pimage;
		m_strImageFileName = m_vecImageFile[0].name;

		SetRowAndColumnCount(m_pxImage);
	}
}

void CIconEditorDlg::OnDestroy()
{
	CString strPath = "";
	m_editRelaPath.GetWindowText(strPath);

	SaveSetConfigFile(RelaPath_Key, strPath.GetBuffer());

	ClearCXImagePoint();

	CDialog::OnDestroy();
	// TODO: Add your message handler code here	
}


void CIconEditorDlg::ClearCXImagePoint()
{
	vector<ImageFile>::iterator iter = m_vecImageFile.begin();
	vector<ImageFile>::iterator end =  m_vecImageFile.end();

	for ( ; iter != end; ++iter)
	{
		if ((*iter).pimage != NULL)
		{
			delete (*iter).pimage;
		}
	}

	m_vecImageFile.clear();
}

void CIconEditorDlg::SaveSetConfigFile(char *pszKey, char *pszValue)
{
	::WritePrivateProfileString(Set_Secion, pszKey, pszValue, m_szFilePath);
}

//用坐标换算图片的行 列 位置
bool CIconEditorDlg::GetIconPosition(CPoint &xPoint, PositionInfo &xPosition)
{
	if (m_pxImage == NULL)
	{
		return false;
	}
	//先算出有多少行和列	

	//所标点中的哪一行
	xPosition.nRow = xPoint.y / m_nIconHeight;
	xPosition.nColumn = xPoint.x / m_nIconWidth;

	return (xPosition.nRow < m_nRowCount && xPosition.nColumn < m_nColumnCount);
}


void CIconEditorDlg::OnStnClickedStaticImage()
{
	// TODO: Add your control notification handler code here
	if (m_pxImage == NULL)
	{
		return;
	}

	//float fScaleX = m_pxImage->GetWidth()  / m_xRect.Width();
	//float fScaleY = m_pxImage->GetHeight()  / m_xRect.Width();

	CPoint xPoint;
	GetCursorPos(&xPoint);

	RECT rect;
	m_staticImage.GetClientRect(&rect);
	m_staticImage.ClientToScreen(&rect);

	xPoint.x = (xPoint.x - rect.left) * m_xRect.Width() / m_pxImage->GetWidth();
	xPoint.y = (xPoint.y - rect.top) * m_xRect.Width() / m_pxImage->GetHeight();
	
	IconInfo xIcon;
	if (GetIconPosition(xPoint, xIcon.xPosition))
	{		
		m_editImageName.SetWindowText(m_strImageFileName);
		SetEditText(m_editRow, "%d", xIcon.xPosition.nRow);
		SetEditText(m_editColumn, "%d", xIcon.xPosition.nColumn);
	}	
	else
	{
		m_editImageName.SetWindowText("");
		m_editRow.SetWindowText("");
		m_editColumn.SetWindowText("");
		
		xIcon.xPosition.Clear();
	}	

	xIcon.strImage = m_strImageFileName;

	CString strRelaPath = "";
	m_editRelaPath.GetWindowText(strRelaPath);
	xIcon.strImage.Insert(0, strRelaPath);
	
	m_xPositionInfo = xIcon.xPosition;
	ShowImage();
	ShowIconInfo(xIcon);

	int nIndex = m_listIcon.GetCurSel();
	if (nIndex != -1)
	{
		//m_listIcon.SetFocus();
		m_listIcon.EnsureVisible(nIndex, true);		
	}	
	m_staticImage.SetFocus();
}

void CIconEditorDlg::ShowIconInfo(IconInfo &xIcon)
{
	CString strRelaPath = "";
	m_editRelaPath.GetWindowText(strRelaPath);
	static char* s_pszFormat = "索引坐标  X: %3d Y: %3d    Icon位置  第 %2d 行 第 %2d 列         %s";
	CString strInfo = "";
	strInfo.Format(s_pszFormat, xIcon.xPosition.nColumn * m_nIconWidth, xIcon.xPosition.nRow * m_nIconWidth, xIcon.xPosition.nRow, xIcon.xPosition.nColumn, xIcon.strImage);
	m_staticInfo.SetWindowText(strInfo);
}

//显示已经编辑的icon数量
void CIconEditorDlg::ShowIconCount()
{
	CString strCount = "";

	strCount.Format("Icon 起始数量 : %d   当前数量 : %d", m_nStartIconCount, m_vecIcon.size());

	m_staticCount.SetWindowText(strCount);
}

IconInfo* CIconEditorDlg::FindIconInfo(int nID)
{
	if (nID == -1)
	{
		return NULL;
	}

	iconiter iter = find(m_vecIcon.begin(), m_vecIcon.end(), nID);
	if (iter != m_vecIcon.end())
	{		
		return &(*iter); 		
	}

	return NULL;
}

int CIconEditorDlg::FindIconListIndex(int nID)
{
	if (nID == -1)
	{
		return -1;
	}

	int nCount = m_listIcon.GetItemCount();
	for (int i = 0; i < nCount; ++i)
	{
		int nItemID = GetListItemInt(m_listIcon, i, 1, -1);

		if (nItemID == nID)
		{
			return i;
		}
	}

	return -1;
}

void CIconEditorDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	if (EditIconInfo(true))
	{
		m_bChange = true;
	}
	

	ShowIconCount();
}


void CIconEditorDlg::OnBnClickedButtonLoadXml()
{
	// TODO: Add your control notification handler code here
	CString strXmlFile = "";
	m_editXmlFile.GetWindowText(strXmlFile);
	if (strXmlFile.IsEmpty())
	{
		return;
	}

	ClearListSelectItem(m_listIcon);
	m_listIcon.DeleteAllItems();

	m_nStartIconCount = 0;
	ShowIconCount();

	if (m_RadioType == 1)
	{
		if (!LoadSkillXmlFile(strXmlFile.GetBuffer()))
		{
			AfxMessageBox("加载Icon config文件失败！");
			return;
		}
	}
	else //if (m_RadioType == 0)
	{
		if (!LoadItemXmlFile(strXmlFile.GetBuffer()))
		{
			AfxMessageBox("加载Icon config文件失败！");
			return;
		}
	}
	
	
	m_nStartIconCount = m_vecIcon.size();

	ShowIconCount();
	

	////////////////////////////////////////
	m_buttonSaveXml.EnableWindow(TRUE);
	m_bCanSave = true;
		
	///////////////////////////////////////////
	if (m_RadioType == 1)
	{
		InsertInSkillIcon(m_RadioProfession, m_RadioSkillType);
	}
	else //if (m_RadioType == 0)
	{
		iconiter iter = m_vecIcon.begin();
		iconiter end = m_vecIcon.end();
		for (int i = 0; iter != end; ++iter, ++i)
		{
			InsertInIconList(i, (*iter), false);
		}
	}
	
	
}

void CIconEditorDlg::OnBnClickedButtonSaveXml()
{
	// TODO: Add your control notification handler code here
	CString strXmlFile = "";
	m_editXmlFile.GetWindowText(strXmlFile);
	if (strXmlFile.IsEmpty() || !m_bCanSave)
	{
		return;
	}

	bool bSave = false;
	if (m_RadioType == 1)
	{
		bSave = SaveSkillXmlFile(strXmlFile.GetBuffer());
	}
	else //	if (m_RadioType == 0)
	{
		bSave = SaveItemXmlFile(strXmlFile.GetBuffer());		
	}
	

	if (bSave)	
	{
		m_bChange = false;
		AfxMessageBox("保存Xml文件成功！");
	}
	else
	{
		AfxMessageBox("保存Xml文件失败！");
	}
	
}

bool CIconEditorDlg::LoadItemXmlFile(const char* pszFile)
{
	m_vecIcon.clear();

	TiXmlDocument xTiXmlDoc;
	if (!xTiXmlDoc.LoadFile(pszFile))
	{	
		return false;
	}

	TiXmlElement* pRoot = xTiXmlDoc.FirstChildElement("Project");
	if ( NULL == pRoot ) return false;

	TiXmlElement* pElement = pRoot->FirstChildElement("Icons");
	if ( NULL == pElement ) return false;
	
	TiXmlElement* pIconElement  = pElement->FirstChildElement("Icon");
	while (pIconElement != NULL)
	{
		IconInfo xIconInfo;

		Common::_tstring strValue;

		pIconElement->Attribute("ItemId", &xIconInfo.nID);	
		
		strValue.fromUTF8(pIconElement->Attribute("Name"));
		xIconInfo.strName = strValue.c_str();

		strValue.fromUTF8(pIconElement->Attribute("Image"));
		xIconInfo.strImage = strValue.c_str();

		pIconElement->Attribute("Size", &xIconInfo.nWidth);
		pIconElement->Attribute("Row", &xIconInfo.xPosition.nRow);
		pIconElement->Attribute("Column", &xIconInfo.xPosition.nColumn);

		m_vecIcon.push_back(xIconInfo);

		pIconElement = pIconElement->NextSiblingElement();
	}

	return true;
}

bool CIconEditorDlg::LoadSkillXmlFile(const char* pszFile)
{
	m_vecIcon.clear();

	TiXmlDocument xTiXmlDoc;
	if (!xTiXmlDoc.LoadFile(pszFile))
	{	
		return false;
	}

	TiXmlElement* pRoot = xTiXmlDoc.FirstChildElement("Project");
	if (pRoot == NULL ) return false;

	TiXmlElement* pSkillTree  = pRoot->FirstChildElement("SkillTreeConfig");
	if (pSkillTree == NULL) { return false; }
	
	TiXmlElement* pElement  = pSkillTree->FirstChildElement("Profession");
	while (pElement != NULL)
	{
		Common::_tstring strProfession;
		
		strProfession.fromUTF8(pElement->Attribute("Name"));		
		if (!strProfession.empty())
		{
			int nProfession = GetProfession(strProfession.c_str());		
			if (nProfession != -1)
			{
				TiXmlElement* pIconElement = NULL;

				pIconElement = pElement->FirstChildElement(s_pszType[Enum_Profession]);
				ReadSkillIcon(pIconElement, nProfession, Enum_Profession);

				pIconElement  = pElement->FirstChildElement(s_pszType[Enum_Common]);
				ReadSkillIcon(pIconElement, nProfession, Enum_Common);

				pIconElement  = pElement->FirstChildElement(s_pszType[Enum_Produce]);
				ReadSkillIcon(pIconElement, nProfession, Enum_Produce);				
			}
		}

		pElement = pElement->NextSiblingElement();
	}

	return true;
}


void CIconEditorDlg::ReadSkillIcon(TiXmlElement* pElement, int nProfession, int nType)
{
	if (pElement != NULL)
	{			
		TiXmlElement* pIcon  = pElement->FirstChildElement("Icon");
		while (pIcon != NULL)
		{
			IconInfo xIconInfo;

			Common::_tstring strValue;

			xIconInfo.nProfession = nProfession;
			xIconInfo.nType = nType;

			pIcon->Attribute("Index", &xIconInfo.nIndex);
			strValue.fromUTF8(pIcon->Attribute("IsVisual"));
			xIconInfo.bVis = strValue.c_str();	

			int nPosX = 0;
			pIcon->Attribute("PostionX", &nPosX);
			int nPosY = 0;
			pIcon->Attribute("PostionY", &nPosY);
			xIconInfo.xPoint.x = nPosX;
			xIconInfo.xPoint.y = nPosY;

			pIcon->Attribute("IconId", &xIconInfo.nID);

			//strValue.fromUTF8(pIconElement->Attribute("Name"));
			//xIconInfo.strName = pIconElement->Attribute("Name");//strValue.c_str();

			strValue.fromUTF8(pIcon->Attribute("Image"));
			xIconInfo.strImage = strValue.c_str();

			pIcon->Attribute("IconSize", &xIconInfo.nWidth);
			pIcon->Attribute("Row", &xIconInfo.xPosition.nRow);
			pIcon->Attribute("Column", &xIconInfo.xPosition.nColumn);

			m_vecIcon.push_back(xIconInfo);

			pIcon = pIcon->NextSiblingElement();
		}					
	}			
}

void CIconEditorDlg::SaveSkillIncon(TiXmlElement* pElement, int nProfession, int nType, CString strSkillBgd)
{
	TiXmlElement* pIconElement = pElement->InsertEndChild(TiXmlElement(s_pszType[nType]))->ToElement();
	//设置背景图片
	Common::_tstring bg = strSkillBgd.GetBuffer();
	pIconElement->SetAttribute("Bg", bg.toUTF8().c_str());

	iconiter iter = m_vecIcon.begin();
	iconiter end = m_vecIcon.end();

	for ( ; iter != end; ++iter)
	{
		if ((*iter).nProfession == nProfession && (*iter).nType == nType)
		{
			TiXmlElement* pIcon = pIconElement->InsertEndChild(TiXmlElement("Icon"))->ToElement();
			pIcon->SetAttribute("Index", (*iter).nIndex);
			pIcon->SetAttribute("IsVisual", (*iter).bVis);
			pIcon->SetAttribute("PostionX", (*iter).xPoint.x);
			pIcon->SetAttribute("PostionY", (*iter).xPoint.y);

			pIcon->SetAttribute("IconId", (*iter).nID);		
			Common::_tstring image = (*iter).strImage.GetBuffer();
			pIcon->SetAttribute("Image", image.toUTF8().c_str());
			pIcon->SetAttribute("IconSize", (*iter).nWidth);
			pIcon->SetAttribute("Row", (*iter).xPosition.nRow);
			pIcon->SetAttribute("Column", (*iter).xPosition.nColumn);

			//pIcon->SetAttribute("Name", (*iter).strName.GetBuffer());	
		}			
	}
}

void CIconEditorDlg::SaveXmlFileWhenClose()
{
	if (m_bChange && m_bCanSave)
	{
		if (MessageBox("Icon信息有修改，需要保存吗？", "提示信息", MB_YESNO) == IDYES)
		{
			CString strXmlFile = "";
			m_editXmlFile.GetWindowText(strXmlFile);
			if (!strXmlFile.IsEmpty())
			{	
				if ( m_RadioType == 1)
				{
					SaveSkillXmlFile(strXmlFile.GetBuffer());
				}
				else //if (m_RadioType == 0)
				{
					SaveItemXmlFile(strXmlFile.GetBuffer());
				}				
			}			
		}	
	}		
}

bool CIconEditorDlg::SaveItemXmlFile(const char *pszFile)
{
	TiXmlDocument xTiXmlDoc;
	
	xTiXmlDoc.InsertEndChild(TiXmlDeclaration("1.0","UTF-8","yes"));

	TiXmlElement* pRoot = xTiXmlDoc.InsertEndChild(TiXmlElement("Project"))->ToElement();	

	//SYSTEMTIME xSystemTime;
	//::GetLocalTime(&xSystemTime);
	//CString strTime = "";
	//strTime.Format("%d-%d-%d %d:%d:%d", xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay, xSystemTime.wHour, xSystemTime.wMinute, xSystemTime.wSecond);
	Common::_tstring name = "HeroOnline";
	pRoot->SetAttribute("Name", name.toUTF8().c_str());

	Common::_tstring version = ApplicationConfig::Instance().GetFullVersion();
	pRoot->SetAttribute("Version", ""/*version.toUTF8().c_str()*/);
	
	TiXmlElement* pIcons = pRoot->InsertEndChild(TiXmlElement("Icons"))->ToElement();
	//pIcons->SetAttribute("Count", static_cast<int>(m_vecIcon.size()));

	sort(m_vecIcon.begin(), m_vecIcon.end());		//先按ID排序

	iconiter iter = m_vecIcon.begin();
	iconiter end = m_vecIcon.end();
	for ( ; iter != end; ++iter)
	{
		TiXmlElement* pIcon = pIcons->InsertEndChild(TiXmlElement("Icon"))->ToElement();

		pIcon->SetAttribute("ItemId", (*iter).nID);	

		Common::_tstring image = (*iter).strImage.GetBuffer();
		pIcon->SetAttribute("Image", image.toUTF8().c_str());

		pIcon->SetAttribute("Size", (*iter).nWidth);
		pIcon->SetAttribute("Row", (*iter).xPosition.nRow);
		pIcon->SetAttribute("Column", (*iter).xPosition.nColumn);

		Common::_tstring name = (*iter).strName.GetBuffer();
		pIcon->SetAttribute("Name", name.toUTF8().c_str());
	}

	return xTiXmlDoc.SaveFile(pszFile);
}

bool CIconEditorDlg::SaveSkillXmlFile(const char* pszFile)
{
	TiXmlDocument xTiXmlDoc;

	xTiXmlDoc.InsertEndChild(TiXmlDeclaration("1.0","UTF-8","yes"));

	TiXmlElement* pRoot = xTiXmlDoc.InsertEndChild(TiXmlElement("Project"))->ToElement();

	Common::_tstring name = "HeroOnline";
	pRoot->SetAttribute("Name", name.toUTF8().c_str());

	Common::_tstring version = ApplicationConfig::Instance().GetFullVersion();
	pRoot->SetAttribute("Version", ""/*version.toUTF8().c_str()*/);

	TiXmlElement* pSkillTree = pRoot->InsertEndChild(TiXmlElement("SkillTreeConfig"))->ToElement();

	//SYSTEMTIME xSystemTime;
	//::GetLocalTime(&xSystemTime);
	//CString strTime = "";
	//strTime.Format("%d-%d-%d %d:%d:%d", xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay, xSystemTime.wHour, xSystemTime.wMinute, xSystemTime.wSecond);
	//pSkillTree->SetAttribute("Time",strTime.GetBuffer());

	CString strSkillBgd = "";
	m_editSkillBgd.GetWindowText(strSkillBgd);
	
	for (int i = 0; i < EA_ArmsMaxSize; ++i)
	{
		TiXmlElement* pElement = pSkillTree->InsertEndChild(TiXmlElement("Profession"))->ToElement();
		Common::_tstring name = s_pszProfession[i];
		pElement->SetAttribute("Name", name.toUTF8().c_str());

		SaveSkillIncon(pElement, i, Enum_Profession, strSkillBgd);
		SaveSkillIncon(pElement, i, Enum_Common, strSkillBgd);
		SaveSkillIncon(pElement, i, Enum_Produce, strSkillBgd);	
	}

	return xTiXmlDoc.SaveFile(pszFile);
}

void CIconEditorDlg::InsertInSkillIcon(int nProfession, int nSkillType)
{
	m_listIcon.DeleteAllItems();
	iconiter iter  = m_vecIcon.begin();
	iconiter end = m_vecIcon.end();

	for (int i = 0 ; iter != end; ++iter)
	{
		if ((*iter).nProfession == nProfession && (*iter).nType == nSkillType)
		{
			InsertInIconList(i++, (*iter), false);			
		}
	}
}

void CIconEditorDlg::InsertInIconList(int nIndex, IconInfo &xIcon, bool bEdit)
{
	if (nIndex < 0)
	{
		return;
	}

	int nSubItem = 1;  //列索引
	
	if (!bEdit)   //添加
	{
		m_listIcon.InsertItem(nIndex, "");		//第一个是图片
	}

	CString strImage = GetImageFileName(xIcon.strImage.GetBuffer());

	ImageIndex xImageIndex;

	xImageIndex.name = strImage;
	xImageIndex.xPostion = xIcon.xPosition;

	int nImageIndex = FindImageListIndex(xImageIndex);
	if (nImageIndex != -1)
	{
		m_listIcon.SetItemImage(nIndex, 0, nImageIndex);
	}		


	SetListItemText(m_listIcon, nIndex, nSubItem++, "%d", xIcon.nID);

	m_listIcon.SetItemText(nIndex, nSubItem, xIcon.strName);
	m_listIcon.SetEdit(nIndex, nSubItem++);

	m_listIcon.SetItemText(nIndex, nSubItem, strImage);
	m_listIcon.SetEdit(nIndex, nSubItem++);
	SetListItemText(m_listIcon, nIndex, nSubItem++, "%d", xIcon.xPosition.nRow);
	SetListItemText(m_listIcon, nIndex, nSubItem++, "%d", xIcon.xPosition.nColumn);
	SetListItemText(m_listIcon, nIndex, nSubItem++, "%d", xIcon.nWidth);
}

void CIconEditorDlg::SetRowAndColumnCount(CxImage *pImage)
{
	if (pImage != NULL)
	{
		m_nRowCount = pImage->GetHeight() / m_nIconHeight;
		m_nColumnCount = pImage->GetWidth() /m_nIconWidth;
	}
}

bool CIconEditorDlg::EditIconInfo(bool bAdd)
{
	IconInfo xIconInfo;

	int nID = GetEditInt(m_editItemID, -1);
	int nRow = GetEditInt(m_editRow, -1);
	int nColumu = GetEditInt(m_editColumn, -1);

	if (nID == -1)
	{
		return false;
	}
	xIconInfo.nID = nID;

	m_editItemName.GetWindowText(xIconInfo.strName);
	m_editImageName.GetWindowText(xIconInfo.strImage);


	CString strRelaPath = "";
	m_editRelaPath.GetWindowText(strRelaPath);
	xIconInfo.strImage.Insert(0, strRelaPath);

	xIconInfo.nProfession = m_RadioProfession;
	xIconInfo.nType = m_RadioSkillType;

	xIconInfo.nWidth = m_nIconWidth;
	xIconInfo.nHeight = m_nIconHeight;
	xIconInfo.xPosition.nRow = nRow;
	xIconInfo.xPosition.nColumn = nColumu;

	int nIndex = -1;

	if (bAdd)  //添加
	{
		IconInfo *pIcon = FindIconInfo(nID);
		if (pIcon != NULL)
		{
			//已经有相同的ID
			if (MessageBox("此ID 已经存在列表中，需要覆盖以前的信息吗！", "提示信息", MB_YESNO) == IDNO)
			{
				return false;								
			}

			int nID = pIcon->nID;		
			*pIcon = xIconInfo;	

			nIndex = FindIconListIndex(nID);
							
			bAdd = false;
		}
		else
		{
			nIndex = m_listIcon.GetItemCount();
			xIconInfo.nIndex = nIndex;
			m_vecIcon.push_back(xIconInfo);			
		}		
	}
	else  //编辑
	{
		nIndex = GetListItemCurSel(m_listIcon);
		int nID = GetListItemInt(m_listIcon, nIndex, 1, -1);

		IconInfo *pIconInfo = FindIconInfo(nID);
		if (pIconInfo == NULL)
		{
			return false;			
		}	

		*pIconInfo = xIconInfo;		
	}

	InsertInIconList(nIndex, xIconInfo, !bAdd);

	//ClearListSelectItem(m_listIcon);
	SetListSelectItem(m_listIcon, nIndex);

	return true;	
}

//文件路径中切割出文件名(包括后缀名)
CString CIconEditorDlg::GetImageFileName(const char* pszFilePath)
{
	CString strFile = "";
	if (pszFilePath == NULL)
	{
		return "";
	}

	char szFile[50] = "";
	char szExe[50] = "";

	_tsplitpath(pszFilePath, NULL, NULL, szFile, szExe);

	strFile.Format("%s%s", szFile, szExe);

	return strFile;
}

void CIconEditorDlg::ShowIconInList(int nIndex)
{
	int nID = GetListItemInt(m_listIcon, nIndex, 1, -1);

	IconInfo *pIconInfo = FindIconInfo(nID);
	if (pIconInfo != NULL)
	{
		//如果图片不同 要换显示
		CString strFile = GetImageFileName(pIconInfo->strImage);						
		if (!strFile.IsEmpty() && strFile != m_strImageFileName)
		{
			if (!IsAlreadyLoad(strFile)) //没有加载
			{	
                SetEditText(m_editItemID, "%d", pIconInfo->nID);
                m_editItemName.SetWindowText(pIconInfo->strName);
                
                ShowImagePath( strFile );

				return;
			}		

			m_strImageFileName = strFile;

			UpdateImageFile(m_strImageFileName);
			
			int nCount = m_listImageFile.GetItemCount();
			for (int i = 0; i < nCount; ++i)
			{
				CString strText = m_listImageFile.GetItemText(i, 0);

				if (strText == m_strImageFileName)
				{
					DWORD dwStyle = LVIS_SELECTED | LVIS_FOCUSED;
					m_listImageFile.SetItemState(i, dwStyle, dwStyle);
					//m_listIcon.SetFocus();
					m_listImageFile.EnsureVisible(i, true);

					break;
				}
			}
		}

		SetEditText(m_editItemID, "%d", pIconInfo->nID);
		m_editItemName.SetWindowText(pIconInfo->strName);

		if (pIconInfo->xPosition.nRow == -1 || pIconInfo->xPosition.nColumn == -1)
		{
			m_editImageName.SetWindowText("");
			m_editRow.SetWindowText("");
			m_editColumn.SetWindowText("");			
		}
		else
		{
			m_editImageName.SetWindowText(m_strImageFileName);
			SetEditText(m_editRow, "%d", pIconInfo->xPosition.nRow);
			SetEditText(m_editColumn, "%d", pIconInfo->xPosition.nColumn);
		}

        // 设置相对路径
        ShowImagePath(m_strImageFileName);

		m_xPositionInfo = pIconInfo->xPosition;
		ShowIconInfo(*pIconInfo);
		ShowImage();			
	}
}

void CIconEditorDlg::OnNMClickListIconInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nIndex = GetListItemCurSel(m_listIcon);

	if (nIndex != -1)
	{
		m_buttonEdit.EnableWindow(TRUE);
		ShowIconInList(nIndex);		
	}
	else
	{
		m_buttonEdit.EnableWindow(FALSE);
	}

	*pResult = 0;
}



void CIconEditorDlg::OnBnClickedButtonEditIcon()
{
	// TODO: Add your control notification handler code here

	if (EditIconInfo(false))
	{
		m_bChange = true;
	}	
}

void CIconEditorDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (m_bChange)
	{
		if (MessageBox("Icon信息有修改，需要保存吗？", "提示信息", MB_YESNO) == IDYES)
		{
			SaveXmlFileWhenClose();			
		}	
	}

	OnOK();
}

void CIconEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default
	if (nID == SC_CLOSE)
	{
		SaveXmlFileWhenClose();
	}	


	CDialog::OnSysCommand(nID, lParam);
}

void CIconEditorDlg::OnBnClickedButtonBatchAdd()
{
	// TODO: Add your control notification handler code here
	int nFirstId = GetEditInt(m_editFirstID, -1);
	int nEndId = GetEditInt(m_editEndID, -1);

	if (nFirstId == -1 || nFirstId > nEndId)
	{
		return;
	}

	int nCount = m_listIcon.GetItemCount();
	for (int i = nCount; nFirstId <= nEndId; ++nFirstId)
	{
		IconInfo xIconInfo;

		/////技能属性
		xIconInfo.nProfession = m_RadioProfession;
		xIconInfo.nType = m_RadioSkillType;

		xIconInfo.nIndex = i;
		xIconInfo.nID = nFirstId;
		xIconInfo.nWidth = m_nIconWidth;
		xIconInfo.nWidth = m_nIconHeight;
		IconInfo *pIconInfo = FindIconInfo(xIconInfo.nID);
		if (pIconInfo == NULL)
		{
			m_vecIcon.push_back(xIconInfo);

			InsertInIconList(i++, xIconInfo, false);

			m_bChange = true;
		}		
	}	

	SetListSelectItem(m_listIcon, nCount);	
	ShowIconCount();
}

void CIconEditorDlg::OnNMRclickListIcon(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here	
	int nIndex = GetListItemCurSel(m_listIcon);
	if (nIndex == -1)
	{
		return;
	}

	CMenu menu;
	CPoint pt;
	GetCursorPos(&pt);
	menu.LoadMenu(IDR_MENUDELETE);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);

	*pResult = 0;
}

void CIconEditorDlg::OnDelete()
{
	// TODO: Add your command handler code here

	POSITION pos = m_listIcon.GetFirstSelectedItemPosition();
	while (pos != NULL)
	{
		int nIndex = m_listIcon.GetNextSelectedItem(pos);
		if (nIndex != -1)
		{
			int nID = GetListItemInt(m_listIcon, nIndex, 1, -1);
			iconiter iter = find(m_vecIcon.begin(), m_vecIcon.end(), nID);
			if (iter != m_vecIcon.end())
			{
				m_vecIcon.erase(iter);
				m_listIcon.DeleteItem(nIndex);
			}
		}
	}
}

LRESULT CIconEditorDlg::OnEditEnd(WPARAM nItem, LPARAM nSubItem)
{
	if (nItem >= 0 && nSubItem >= 0)
	{
		CString strText = m_listIcon.GetItemText(nItem, nSubItem);
		if (!strText.IsEmpty())
		{
			int nID = GetListItemInt(m_listIcon, nItem, 1, -1);

			IconInfo *pIconInfo = FindIconInfo(nID);
			if (pIconInfo != NULL)
			{
				if (nSubItem == 2)
				{
					pIconInfo->strName = strText;
				}
				else if (nSubItem == 3)
				{
					CString strRelaPath = "";
					m_editRelaPath.GetWindowText(strRelaPath);

					pIconInfo->strImage.Format("%s%s", strRelaPath, strText);					
				}
				
			}
		}
	}

	return 0;
}

//初始化显示在lsitctrl里面的Icon图片
void CIconEditorDlg::InitIconImageList(CxImage *pxImage, CString strFile)
{
	if (pxImage == NULL)
	{
		return;
	}

	ImageFile xImageFile;
	xImageFile.width = m_nIconWidth;
	xImageFile.height = m_nIconHeight;
	xImageFile.name = strFile;
	xImageFile.pimage = pxImage;
	m_vecImageFile.push_back(xImageFile);

	int nRow = pxImage->GetHeight() / m_nIconHeight;
	int nColumn = pxImage->GetWidth() / m_nIconWidth;

	for (int i = 0; i < nRow; ++i)
	{
		for (int j = 0; j < nColumn; ++j)
		{
			CxImage xSrc;
			RECT rect;

			rect.left = j * m_nIconWidth;
			rect.top = i * m_nIconHeight;

			rect.right = rect.left + m_nIconWidth;
			rect.bottom = rect.top + m_nIconHeight;

			//每次切割大小40的图片
			pxImage->Crop(rect, &xSrc);
			HBITMAP hBitmap = xSrc.MakeBitmap();

			CBitmap xBitmap;
			xBitmap.Attach(hBitmap);

			m_xImagelist.Add(&xBitmap, RGB(255, 255, 255));
			/////////////////////////////////////////////////////////
			//保存每个Icon的 索引信息 
			ImageIndex xImageInfo;
			xImageInfo.name = strFile;
			xImageInfo.xPostion.nRow = i;	//该图片的行
			xImageInfo.xPostion.nColumn = j;			//该图片的列
			xImageInfo.nIndex = m_nImageIndex++;	//在m_xImageList列表中的索引

			m_vecImageIndex.push_back(xImageInfo);
		}
	}

	
}

int CIconEditorDlg::FindImageListIndex(ImageIndex &xImageIndex)
{
	vector<ImageIndex>::iterator iter = find(m_vecImageIndex.begin(), m_vecImageIndex.end(), xImageIndex);
	if (iter != m_vecImageIndex.end())
	{
		return iter->nIndex;
	}

	return -1;
}

bool CIconEditorDlg::IsAlreadyLoad(CString name)
{
	vector<ImageFile>::iterator iter = m_vecImageFile.begin();
	vector<ImageFile>::iterator end = m_vecImageFile.end();

	for ( ; iter != end; ++iter)
	{
		if (iter->name == name)
		{
			return true;
		}
	}

	return false;
}


void CIconEditorDlg::OnLvnItemchangedListIcon(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	int nIndex = GetListItemCurSel(m_listIcon);

	if (nIndex != -1)
	{
		m_buttonEdit.EnableWindow(TRUE);
		ShowIconInList(nIndex);		
	}
	else
	{
		m_buttonEdit.EnableWindow(FALSE);
	}

	*pResult = 0;
}

void CIconEditorDlg::OnBnClickedButtonFind()
{
	// TODO: Add your control notification handler code here

	int nFindID = GetEditInt(m_editItemID, -1);

	if (nFindID == -1)
	{
		return;
	}

	int nCount = m_listIcon.GetItemCount();
	for (int i = 0; i < nCount; ++i)
	{
		int nId = GetListItemInt(m_listIcon, i, 1, -1);
		if (nId == nFindID)
		{					
			SetListSelectItem(m_listIcon, i);			
			return;
		}
	}

	m_editItemName.SetWindowText("");
	m_editImageName.SetWindowText("");
	m_editRow.SetWindowText("");
	m_editColumn.SetWindowText("");
}

void CIconEditorDlg::ClearListSelectItem(CListCtrl &xList)
{
	POSITION pos = m_listIcon.GetFirstSelectedItemPosition();
	while (pos != NULL)
	{
		int nIndex = m_listIcon.GetNextSelectedItem(pos);
		if (nIndex != -1)
		{
			xList.SetItemState(nIndex, 0, LVIS_SELECTED);
		}
	}
	
}

void CIconEditorDlg::SetListSelectItem(CListCtrl &xList, int nIndex)
{
	//ClearListSelectItem(xList);

	DWORD dwStyle = LVIS_SELECTED | LVIS_FOCUSED;
	m_listIcon.SetItemState(nIndex, dwStyle, dwStyle);
	m_listIcon.SetFocus();
	m_listIcon.EnsureVisible(nIndex, true);
}

//批量删除
void CIconEditorDlg::OnBnClickedButtonBatchDelete()
{
	// TODO: Add your control notification handler code here

	int nFirstId = GetEditInt(m_editFirstID, -1);
	int nEndId = GetEditInt(m_editEndID, -1);

	if (nFirstId == -1 || nFirstId > nEndId)
	{
		return;
	}

	if (MessageBox("确定是否需要批量删除这些Icon吗？", "提示信息", MB_YESNO) == IDNO)
	{
		return;	
	}

	int nCount = m_listIcon.GetItemCount();
	for (int i = nCount; nFirstId <= nEndId; ++nFirstId)
	{		
		iconiter iter = find(m_vecIcon.begin(), m_vecIcon.end(), nFirstId);
		if (iter != m_vecIcon.end())
		{
			m_bChange = true;
			m_vecIcon.erase(iter);
	
			for (int j = 0; j < nCount; ++j)
			{
				int nId = GetListItemInt(m_listIcon, j, 1, -1);
				if (nId == nFirstId)
				{					
					m_listIcon.DeleteItem(j);		
					break;
				}
			}			
		}		
	}	

	ShowIconCount();
}

void CIconEditorDlg::OnBnClickedButtonOpenXml()
{
	// TODO: Add your control notification handler code here
	CString strFileName = "";
	m_editXmlFile.GetWindowText(strFileName);
	if (strFileName.IsEmpty())
	{
		return;
	}

	CString strCommon = "";
	strCommon.Format("explorer.exe /select, %s", strFileName);

	::WinExec(strCommon.GetBuffer(), SW_SHOWNORMAL);
}


int CIconEditorDlg::GetProfession(const char *szProfession)
{
	const static int nCount = sizeof(s_pszProfession) / sizeof(char*);
	if (szProfession == NULL || *szProfession == 0)
	{
		return -1;
	}

	for (int i = 0; i < nCount; ++i)
	{
		if (strcmp(s_pszProfession[i], szProfession) == 0)
		{
			return i;
		}
	}

	return -1;
}


void CIconEditorDlg::EnableRadio(BOOL bEnable)
{
	GetDlgItem(IDC_RADIO3)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO4)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO5)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO6)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO7)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO8)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO9)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO10)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO11)->EnableWindow(bEnable);

	m_editSkillBgd.EnableWindow(bEnable);

	m_editRelaPath.SetWindowText(s_pszRelaPath[m_RadioType]);

	CString strType = "";
	strType.Format("%d", bEnable);
	SaveSetConfigFile(Profession_Key, strType.GetBuffer());
}

void CIconEditorDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	m_RadioType = 0;
	EnableRadio(FALSE);		
}

void CIconEditorDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	m_RadioType = 1;
	EnableRadio(TRUE);
}

void CIconEditorDlg::OnBnClickedRadio16()
{
	// TODO: Add your control notification handler code here
	m_RadioType = 2;
	EnableRadio(FALSE);
}

void CIconEditorDlg::OnBnClickedRadio17()
{
	// TODO: Add your control notification handler code here

	m_RadioType = 3;
	EnableRadio(FALSE);
}

void CIconEditorDlg::OnBnClickedRadio18()
{
    // TODO: Add your control notification handler code here

    m_RadioType = 4;
    EnableRadio(FALSE);
}

void CIconEditorDlg::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here

	m_RadioProfession = EA_Spear;

	InsertInSkillIcon(m_RadioProfession, m_RadioSkillType);
}

void CIconEditorDlg::OnBnClickedRadio4()
{
	// TODO: Add your control notification handler code here
	m_RadioProfession = EA_Staff;

	InsertInSkillIcon(m_RadioProfession, m_RadioSkillType);
}

void CIconEditorDlg::OnBnClickedRadio5()
{
	// TODO: Add your control notification handler code here
	m_RadioProfession = EA_Fan;

	InsertInSkillIcon(m_RadioProfession, m_RadioSkillType);
}

void CIconEditorDlg::OnBnClickedRadio6()
{
	// TODO: Add your control notification handler code here
	m_RadioProfession = EA_Sword;

	InsertInSkillIcon(m_RadioProfession, m_RadioSkillType);
}

void CIconEditorDlg::OnBnClickedRadio7()
{
	// TODO: Add your control notification handler code here
	m_RadioProfession = EA_Bow;

	InsertInSkillIcon(m_RadioProfession, m_RadioSkillType);
}

void CIconEditorDlg::OnBnClickedRadio8()
{
	// TODO: Add your control notification handler code here
	m_RadioProfession = ER_Hammer;

	InsertInSkillIcon(m_RadioProfession, m_RadioSkillType);
}

void CIconEditorDlg::OnBnClickedRadio9()
{
	// TODO: Add your control notification handler code here
	m_RadioSkillType = Enum_Profession;

	InsertInSkillIcon(m_RadioProfession, m_RadioSkillType);
}

void CIconEditorDlg::OnBnClickedRadio10()
{
	// TODO: Add your control notification handler code here
	m_RadioSkillType = Enum_Common;
	InsertInSkillIcon(m_RadioProfession, m_RadioSkillType);
}

void CIconEditorDlg::OnBnClickedRadio11()
{
	// TODO: Add your control notification handler code here
	m_RadioSkillType = Enum_Produce;
	InsertInSkillIcon(m_RadioProfession, m_RadioSkillType);
}



bool CIconEditorDlg::KeyMoveIcon(WPARAM wParam)
{
	bool bMove = false;

	if (GetFocus()->m_hWnd != m_staticImage.m_hWnd)
	{
		return bMove;
	}

	switch (wParam)
	{
	case VK_RIGHT:			
		if (m_xPositionInfo.nColumn < (m_nColumnCount - 1))
		{
			++m_xPositionInfo.nColumn;				
		}				

		bMove = true;

		break;
	case VK_LEFT:		
		if (m_xPositionInfo.nColumn > 0)
		{
			--m_xPositionInfo.nColumn;			
		}				

		bMove = true;

		break;
	case VK_UP:		
		if (m_xPositionInfo.nRow > 0)
		{
			--m_xPositionInfo.nRow;			
		}
		bMove = true;

		break;

	case VK_DOWN:		
		if (m_xPositionInfo.nRow < (m_nColumnCount - 1))
		{
			++m_xPositionInfo.nRow;				
		}
		bMove = true;

		break;

	default:
		return bMove;
	}

	ShowImage();

	IconInfo xIconInfo;

	xIconInfo.xPosition = m_xPositionInfo;
	CString strRelaPath = "";
	m_editRelaPath.GetWindowText(strRelaPath);				
	xIconInfo.strImage.Format("%s%s", strRelaPath, m_strImageFileName);		
	ShowIconInfo(xIconInfo);


	SetEditText(m_editRow, "%d", m_xPositionInfo.nRow);
	SetEditText(m_editColumn, "%d", m_xPositionInfo.nColumn);

	return bMove;
}
void CIconEditorDlg::OnEnChangeEditIconWidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int nWidth = GetEditInt(m_editWidth, 40);
	m_nIconWidth = nWidth;

	CString strIconWidth = "";
	strIconWidth.Format("%d", m_nIconWidth);
	SaveSetConfigFile(IconWidth_Key, strIconWidth.GetBuffer());
}

void CIconEditorDlg::OnEnChangeEditIconHeight()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int nHeight = GetEditInt(m_editHeight, 40);
	m_nIconHeight = nHeight;

	CString strIconHeight = "";
	strIconHeight.Format("%d", m_nIconHeight);
	SaveSetConfigFile(IconHeight_Key, strIconHeight.GetBuffer());
}



void CIconEditorDlg::UpdateImageFile(CString name)
{
	ImageFile *pImageFile = GetImageFileByName(name);

	if (pImageFile != NULL)
	{
		m_pxImage = pImageFile->pimage;

		m_nIconWidth = pImageFile->width;
		m_nIconHeight = pImageFile->height;

		SetRowAndColumnCount(m_pxImage);
	}	
}

void CIconEditorDlg::ShowImagePath( CString& strImageFile )
{
    // 设置相对路径
    CString strTemp = strImageFile;
    string strImageFileName = strTemp.MakeLower().GetBuffer();
    if ( strImageFileName.find("item") != string::npos )
    {
        m_radioItem.SetCheck( TRUE );
        ((CButton*) GetDlgItem(IDC_RADIO14))->SetCheck( TRUE );
        ((CButton*) GetDlgItem(IDC_RADIO15))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO16))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO17))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO18))->SetCheck( FALSE );

        OnBnClickedRadio1();
    }
    else if ( strImageFileName.find("armour") != string::npos )
    {
        ((CButton*) GetDlgItem(IDC_RADIO14))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO15))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO16))->SetCheck( TRUE );
        ((CButton*) GetDlgItem(IDC_RADIO17))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO18))->SetCheck( FALSE );
        OnBnClickedRadio16();
    }
    else if ( strImageFileName.find("weapon") != string::npos )
    {
        ((CButton*) GetDlgItem(IDC_RADIO14))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO15))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO16))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO17))->SetCheck( TRUE );
        ((CButton*) GetDlgItem(IDC_RADIO18))->SetCheck( FALSE );
        OnBnClickedRadio17();
    }
    else if ( strImageFileName.find("xinfa") != string::npos )
    {
        ((CButton*) GetDlgItem(IDC_RADIO14))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO15))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO16))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO17))->SetCheck( FALSE );
        ((CButton*) GetDlgItem(IDC_RADIO18))->SetCheck( TRUE );
        OnBnClickedRadio18();
    }
}

ImageFile* CIconEditorDlg::GetImageFileByName(CString name)
{
	if (name == "")
	{
		return NULL;
	}

	imagefileiter iter = m_vecImageFile.begin();
	imagefileiter end = m_vecImageFile.end();

	for ( ; iter != end; ++iter)
	{
		if (iter->name == name)
		{
			return &(*iter);
		}
	}

	return NULL;
}


void CIconEditorDlg::SetEditText(CEdit& xEdit, char *pszFormat, ...)
{
	if (xEdit.m_hWnd != NULL)
	{
		va_list valist;

		va_start(valist,pszFormat);

		char szValue[100] = "";

		vsprintf(szValue, pszFormat, valist);

		va_end(valist);

		xEdit.SetWindowText(szValue);
	}
}

int CIconEditorDlg::GetEditInt(CEdit& xEdit, int nDef)
{
	CString strValue = "";

	xEdit.GetWindowText(strValue);

	if (strValue.IsEmpty())
	{
		return nDef;
	}

	return atoi(strValue.GetBuffer());
}

void CIconEditorDlg::InsertItemText(CListCtrl &xList, int nItem, char *pszFormat, ...)
{
	if (xList.m_hWnd != NULL)
	{
		va_list valist;

		va_start(valist,pszFormat);

		char szValue[100] = "";

		vsprintf(szValue, pszFormat, valist);

		va_end(valist);

		xList.InsertItem(nItem, szValue);
	}	
}

void CIconEditorDlg::SetListItemText(CListCtrl& xList, int nItem, int nSubItem, char *pszFormat, ...)
{
	if (xList.m_hWnd != NULL)
	{
		va_list valist;

		va_start(valist,pszFormat);

		char szValue[100] = "";

		vsprintf(szValue, pszFormat, valist);

		va_end(valist);

		xList.SetItemText(nItem, nSubItem, szValue);
	}	
}

int CIconEditorDlg::GetListItemInt(CListCtrl &xList, int nItem, int nSubItem, int nDef)
{
	CString strValue = xList.GetItemText(nItem, nSubItem);

	if (strValue.IsEmpty())
	{
		return nDef;
	}

	return (atoi(strValue.GetBuffer()));
}

int CIconEditorDlg::GetListItemCurSel(CListCtrl &xList)
{
	POSITION pos = xList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		return xList.GetNextSelectedItem(pos); 
	}

	return -1;
}

int CIconEditorDlg::SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle)
{
	xList.SetExtendedStyle(dwStyle);

	RECT rect;
	xList.GetClientRect(&rect);

	return (rect.right - rect.left);
}
