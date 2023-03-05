#include "stdafx.h"
#include "ApplicationManager.h"
#include "ApplicationManagerDialog.h"
#include "ApplicationInfoPage.h"
#include "Tinyxml/Tinyxml.h"
#include "Message.h"
#include "TrayIcon.h"
#include "DataCenter.h"
#include "license.h"
#include "Helper.h"
#include "Application_Config.h"
#include "ResourcePath.h"
#include "tstring.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CApplicationManagerDialog::CApplicationManagerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CApplicationManagerDialog::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CApplicationManagerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

LRESULT CApplicationManagerDialog::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // 自身消息的派发
    if ( WM_SETTEXT == message )
    {
        ProcessManager::Instance().DispatchMessage( (unsigned long)wParam, (char*)lParam );
        return 0;
    }
    else if ( WM_SHOWTRAY == message )
    {
        if( wParam != IDR_MAINFRAME ) 
            return 0;

        switch( lParam )
        {
        case WM_RBUTTONUP:
            {
                HMENU hMenu,hSubMenu;
                POINT pt;
                hMenu = LoadMenu( GlobalObject::g_hMainInstance,  MAKEINTRESOURCE(IDR_MENU_MAIN ) );
                hSubMenu = GetSubMenu( hMenu, 0 );
                GetCursorPos( &pt );
                TrackPopupMenu( hSubMenu, TPM_RIGHTALIGN|TPM_LEFTBUTTON,  pt.x, pt.y, 0, GlobalObject::g_hMainWin, 0 );
            }
            break;
        case WM_LBUTTONDBLCLK:            
            GlobalObject::makeTrayShow( false );
            ShowWindow( SW_NORMAL );
            break;
        }
        return 0;
    }
    else
    {
        return CDialog::DefWindowProc( message, wParam, lParam);
    }
}

HTREEITEM CApplicationManagerDialog::AddTreeNode(HTREEITEM hParentItem, const std::string& strNodeText, unsigned int uiNodeType, unsigned long ulDataId )
{
    TV_INSERTSTRUCT treeItem;
    treeItem.hParent = hParentItem;
    treeItem.hInsertAfter = TVI_SORT;
    treeItem.item.pszText = const_cast<LPSTR>(strNodeText.c_str());
    treeItem.item.mask = uiNodeType;
    HTREEITEM item = _pProcessTree->InsertItem(&treeItem);
    _pProcessTree->SetItemData( item, ulDataId );
    return item;
}

BEGIN_MESSAGE_MAP(CApplicationManagerDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_TIMER()
    ON_COMMAND(ID_FILE_EXIT, &CApplicationManagerDialog::OnFileExit)
    ON_COMMAND(ID_OPEN_SOLUTION, &CApplicationManagerDialog::OnOpenSolution)
    ON_COMMAND(ID_OPEN_APPENDOPENCONFIG, &CApplicationManagerDialog::OnAppendOpenconfig)
    ON_NOTIFY(NM_DBLCLK, IDC_TREE_PROCESS, &CApplicationManagerDialog::OnNMDblclkTreeProcess)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PROCESS, &CApplicationManagerDialog::OnTcnSelchangeTabProcess)
    ON_COMMAND(ID_DEBUG_TESTCASE, &CApplicationManagerDialog::OnDebugTestcase)
    ON_WM_SIZE()
    ON_COMMAND(ID_HELP_ABOUT, &CApplicationManagerDialog::OnHelpAbout)
    ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


BOOL CApplicationManagerDialog::OnInitDialog()
{
#ifdef NEEDONLY
    std::string strContent = "Application Manager already run!";
    HANDLE hMutexHandle = CreateMutex( NULL, true, strContent.c_str());
    if ( GetLastError() == ERROR_ALREADY_EXISTS )
    {
        MessageBox( strContent.c_str(), "Application Manager", MB_OK | MB_ICONWARNING );
        ReleaseMutex( hMutexHandle );
        CloseHandle( hMutexHandle );
        exit(1);
    }
#endif

	CDialog::OnInitDialog();

    // 禁止掉系统的X按钮
//     CMenu* Menu = GetSystemMenu(FALSE);
//     if (NULL != Menu)
//     {
//         Menu->ModifyMenu(SC_CLOSE,MF_BYCOMMAND|MF_GRAYED);
//     }
    //不显示cancel
    CWnd *phCancelWnd = GetDlgItem(IDCANCEL);
    if (NULL != phCancelWnd)
    {
        phCancelWnd->ShowWindow(SW_HIDE);
    }

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	LicenseChecker::Instance();

    RECT rcWnd;
    ::GetWindowRect( m_hWnd, &rcWnd );
    ::SetWindowPos( m_hWnd, HWND_TOP, 500, 200, rcWnd.right-rcWnd.left, rcWnd.bottom-rcWnd.top, SWP_SHOWWINDOW );

    // 定时器
    SetTimer( 0, 3000, 0);

    // 初始化 TextInfo
    _pTextInfo = (CStatic*)GetDlgItem( IDC_STATIC_INFO );
    _pTextInfo->SetWindowText(ApplicationConfig::Instance().GetFullVersion());    

    // 初始化 TreeCtrl  
    _pProcessTree = (CTreeCtrl*)GetDlgItem( IDC_TREE_PROCESS );

    // 初始化 tab
    _ProcessTab.SubclassDlgItem(IDC_TAB_PROCESS, this);
    _ProcessTab.AdjustItemSize();

    // 初始化 实例句柄
    GlobalObject::g_hMainInstance = AfxGetInstanceHandle();
    GlobalObject::g_hMainWin      = m_hWnd;

    //
    DataCenter::Instance().ClearApplicationInfos();

	// 在这里 整理文件属性 把server里面的操作去掉...否则会大家都卡
	HelperFunc::CreateOutputFolder( OUTPUT_DIRECTORY );

    _bAutoStart = false;
	_bCrashAutoStart = false;
    // 默认打开配置
    char szPath[MAX_PATH];  
    _getcwd(szPath,MAX_PATH);
    std::string strPath = szPath;
    strPath += "\\..\\Setting\\ApplicationManager.config";
    LoadConfig(strPath);
	//设置当进程崩溃的时候进程是否自动重新启动
	ProcessManager::Instance().SetReStrat(_bCrashAutoStart);
    // 
    if ( _bAutoStart )
        _StartAllApplication();

	return TRUE;
}

void CApplicationManagerDialog::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CApplicationManagerDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CApplicationManagerDialog::OnCancel()
{
    if ( IDNO == MessageBox( "此操作会中断所有服务器运行[ 服务器不会正常退出保存数据 ]", "Application Manager", MB_YESNO | MB_ICONQUESTION ) )
    {
        return;
    }
    else
    {
        //ProcessManager::Instance().TerminateAllProcees();
        CDialog::OnCancel();
        GlobalObject::makeTrayShow( false );
    }
}

void CApplicationManagerDialog::OnTimer(UINT_PTR nIDEvent)
{   
    CDialog::OnTimer(nIDEvent);
    ProcessManager::Instance().WatchProcessList();
}

bool CApplicationManagerDialog::LoadConfig(const std::string& strSolutionPath, bool bAppend)
{   
    if ( !bAppend )
    { // reload
        ClearConfig();
    }

    TiXmlDocument doc;
    if ( !doc.LoadFile( strSolutionPath.c_str() ) )
        return false;

    TiXmlElement* element = doc.FirstChildElement("Project");

    if ( NULL==element)
        return false;

    std::string strProjectName = element->Attribute("Name");
    std::string strVersion     = element->Attribute("Version");

    int nValue = 0;
    element->QueryIntAttribute("AutoStart", &nValue);
    _bAutoStart      = nValue==0 ? false : true;
    
    element->QueryIntAttribute("CrashAutoStart", &nValue);
    _bCrashAutoStart = nValue==0 ? false : true;
    
    HTREEITEM hRootItem = _pProcessTree->GetRootItem();
    if ( !hRootItem )
        hRootItem = AddTreeNode( NULL, strProjectName, TVIF_TEXT, 0 );
    
    element = element->FirstChildElement("ApplicationList");
    if ( NULL != element ) 
    {   
        element = element->FirstChildElement("Applicaton");
        while ( element )
        {
            ApplicationInfo applicationInfo;     
			Common::_tstring strName;
			strName.fromUTF8( element->Attribute("Name") );
            applicationInfo.strApplicationName = /*element->Attribute("Name")*/strName;
            applicationInfo.strApplicationPath = element->Attribute("Path");
            applicationInfo.strConfigFilePath  = element->Attribute("Config");

            element->Attribute("DetectInterval", (int*)&applicationInfo.nDetectInterval);
            applicationInfo.nIsLog = (strcmp( element->Attribute("IsOutputLog"), "0")==0) ? 0 : 1;

            bool bResult = DataCenter::Instance().AddApplicationInfo(applicationInfo);
            if ( bResult )
                AddTreeNode( hRootItem, applicationInfo.strApplicationName, TVIF_TEXT, applicationInfo.id  );

            element = element->NextSiblingElement("Applicaton");
        }

        _pProcessTree->Expand( hRootItem,TVE_EXPAND );
    }
    
    return true;
}

void CApplicationManagerDialog::ClearConfig()
{
    DataCenter::Instance().ClearApplicationInfos();
    _pProcessTree->DeleteAllItems();

    _ProcessTab.ClearAllPage();
}

void CApplicationManagerDialog::OnFileExit()
{
    OnCancel();
}

void CApplicationManagerDialog::OnOpenSolution()
{
    CFileDialog fileDlg(TRUE );
    fileDlg.GetOFN().lpstrInitialDir = ".\\";
    fileDlg.GetOFN().lpstrDefExt     = ".config";
    fileDlg.GetOFN().lpstrFilter     = "config (.config)\0*.config\0all file (*.*)\0*.*\0\0";
    INT_PTR nResult= fileDlg.DoModal();
    if ( IDOK == nResult)
    {
        std::string strPath = fileDlg.GetPathName().GetBuffer();
        LoadConfig( strPath );
    }
    else if ( IDCANCEL == nResult)
    { 
    }
}

void CApplicationManagerDialog::OnAppendOpenconfig()
{
    CFileDialog fileDlg(TRUE );
    fileDlg.GetOFN().lpstrInitialDir = ".\\";
    fileDlg.GetOFN().lpstrDefExt     = ".config";
    fileDlg.GetOFN().lpstrFilter     = "config (.config)\0*.config\0all file (*.*)\0*.*\0\0";
    INT_PTR nResult= fileDlg.DoModal();
    if ( IDOK == nResult)
    {
        std::string strPath = fileDlg.GetPathName().GetBuffer();
        LoadConfig( strPath, true);
    }
    else if ( IDCANCEL == nResult)
    { 
    }
}

void CApplicationManagerDialog::OnNMDblclkTreeProcess(NMHDR*, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    HTREEITEM item = _pProcessTree->GetSelectedItem();
    DWORD_PTR ret = _pProcessTree->GetItemData( item );

    ApplicationInfo* pApplicationInfo =  DataCenter::Instance().GetApplicationInfo( (unsigned long)ret );

    if ( pApplicationInfo != NULL )
    {
        int nApplicationType = LNT_NONE;
        if ( pApplicationInfo->nIsLog == 0 )
            nApplicationType = LNT_APPLICATION_NORMAL;
        else
            nApplicationType = LNT_APPLICATION_CAN_RECEIVE_MESSAGE;

        switch ( nApplicationType )
        {
        case LNT_APPLICATION_CAN_RECEIVE_MESSAGE:
            {
                if ( !_ProcessTab.IsExist(pApplicationInfo->strApplicationName.c_str()) )
                {
                    CPage page;
                    page.pDialog = new CApplicationInfoPage();
                    page.pDialog->Create( IDD_PROPPAGE_PROCESS_INFO, &_ProcessTab );
                    page.pDialog->SetApplicationPath( pApplicationInfo->strApplicationPath );
                    page.pDialog->SetConfigPath( pApplicationInfo->strConfigFilePath );
                    page.strTitle = pApplicationInfo->strApplicationName;

                    ProcessManager::Instance().RegisterHandle( SM_LOGINCHECK, page.pDialog );
                    ProcessManager::Instance().RegisterHandle( SM_LOG, page.pDialog );

                    _ProcessTab.AddPage( page );
                }                
                _ProcessTab.Show( pApplicationInfo->strApplicationName.c_str() );
            }
            break;
        case LNT_APPLICATION_NORMAL:
            {
                _ProcessTab.AddPage( pApplicationInfo->strApplicationName.c_str(),  IDD_PROPPAGE_PROCESS_INFO );
                CPage* pPage = _ProcessTab.GetPage( pApplicationInfo->strApplicationName.c_str() );
                if ( pPage )
                {
                    pPage->pDialog->SetApplicationPath( pApplicationInfo->strApplicationPath );
                    pPage->pDialog->SetConfigPath( pApplicationInfo->strConfigFilePath );
                }
                _ProcessTab.Show( pApplicationInfo->strApplicationName.c_str() );
            }
            break;
        default:
            assert( false && "Error application Type" );
            break;
        }
    }
    *pResult = 0;
}

void CApplicationManagerDialog::OnTcnSelchangeTabProcess(NMHDR *, LRESULT *pResult)
{
    *pResult = 0;
    int nItem = _ProcessTab.GetCurSel();
    _ProcessTab.Show( nItem );
    // UpdateData( FALSE );
}

void CApplicationManagerDialog::OnDebugTestcase()
{
    // GlobalObject::makeTrayShow();
}

void CApplicationManagerDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    if ( SIZE_MINIMIZED == nType )
    {
        GlobalObject::makeTrayShow();
        ShowWindow( SW_HIDE );
    }
}

void CApplicationManagerDialog::OnHelpAbout()
{
    CHelpDialog dlg;
    dlg.DoModal();
}

void CApplicationManagerDialog::_StartAllApplication()
{
    ApplicationInfoListType& infos = DataCenter::Instance().GetApplicationInfos();
    
    ApplicationInfoListType::iterator it = infos.begin();

    std::string strFirst;
    for ( ; it!=infos.end(); ++it)
    {
        ApplicationInfo& info = it->second;
        if ( it == infos.begin() )
            strFirst = info.strApplicationName;

        if ( !_ProcessTab.IsExist(info.strApplicationName.c_str()) )
        {
            CPage page;
            page.pDialog = new CApplicationInfoPage();
            page.pDialog->Create( IDD_PROPPAGE_PROCESS_INFO, &_ProcessTab );
            page.pDialog->SetApplicationPath( info.strApplicationPath );
            page.pDialog->SetConfigPath( info.strConfigFilePath );
            page.strTitle = info.strApplicationName;

            ProcessManager::Instance().RegisterHandle( SM_LOGINCHECK, page.pDialog );
            ProcessManager::Instance().RegisterHandle( SM_LOG, page.pDialog );

            _ProcessTab.AddPage( page );
        }                

        
        _ProcessTab.Show( info.strApplicationName.c_str() );
        CPage* pPage = _ProcessTab.GetPage( info.strApplicationName );
        if ( pPage && pPage->pDialog  )
        {
            pPage->pDialog->OnBnClickedButtonStart();
        }
		Sleep(100);
    }

    if ( !strFirst.empty())
        _ProcessTab.Show( strFirst.c_str() );
}

void CApplicationManagerDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
    // TODO: Add your message handler code here and/or call default

    CDialog::OnSysCommand(nID, lParam);
}

void CApplicationManagerDialog::SetTreeItemText( std::string strName, bool IsBad )
{
	ApplicationInfoListType& infos = DataCenter::Instance().GetApplicationInfos();

	ApplicationInfoListType::iterator it = infos.begin();
	std::string strFindName;

	for ( ; it!=infos.end(); ++it)
	{
		ApplicationInfo& info = it->second;
		if ( strcmp( info.strConfigFilePath.c_str(), strName.c_str()) == 0 )
		{
			strFindName = info.strApplicationName;
			break;
		}
	}

	if ( strFindName.length() <= 0 )
		return;

	CString str( strFindName.c_str() );
	CString strErr( "【Error！】 " );
	if ( !IsBad )
		str = strErr + str;

	HTREEITEM hItem = FindTreeItem( _pProcessTree->GetRootItem(), str );
	if ( hItem )
	{
		CString strText;
		if ( IsBad )
			strText = strErr + str;
		else
			strText = CString(_T(strFindName.c_str()));

		_pProcessTree->SetItemText( hItem, strText.GetBuffer());
	}
}

HTREEITEM CApplicationManagerDialog::FindTreeItem( HTREEITEM item, CString strText )
{
	HTREEITEM hFind;      
	if(item == NULL)  
		return NULL;  

	while(item != NULL)  
	{  
		if(_pProcessTree->GetItemText(item) == strText)  
			return item;  

		if(_pProcessTree->ItemHasChildren(item))  
		{  
			item = _pProcessTree->GetChildItem(item);  
			hFind = FindTreeItem(item, strText);        
			if(hFind)  
			{  
				return hFind;         
			}  
			else  
			{  
				item= _pProcessTree->GetNextSiblingItem(_pProcessTree->GetParentItem(item));  
			}  
		}  
		else  
		{  
			item = _pProcessTree->GetNextSiblingItem(item);  
			if(item == NULL)  
				return NULL;  
		}         
	}  

	return item;  
}