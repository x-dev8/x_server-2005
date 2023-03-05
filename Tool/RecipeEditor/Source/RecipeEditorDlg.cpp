// RecipeEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RecipeEditor.h"
#include "RecipeEditorDlg.h"
#include "ItemDetailConfig.h"
#include "application_config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CRecipeEditorDlg dialog
CRecipeEditorDlg::CRecipeEditorDlg(CWnd* pParent /*=NULL*/)
: CDialog(CRecipeEditorDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRecipeEditorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SKILL_BIG_TYPE, m_cmbBigType);
    DDX_Control(pDX, IDC_SKILL_SMALL_TYPE, m_cmbSmallType);
    DDX_Control(pDX, IDC_RECIPE_LIST, m_RecipeList);
    DDX_Control(pDX, IDC_USE_ENEGY, m_UseEnegy);
    DDX_Control(pDX, IDC_CASTTIME, m_CastTime);
    DDX_Control(pDX, IDC_USE_MONEY, m_UseMoney);
    DDX_Control(pDX, IDC_ITEM_LIST, m_ItemList);
    DDX_Control(pDX, IDC_EDIT4, m_ProficiencyLimit);
    DDX_Control(pDX, IDC_EDIT5, m_SkillLevelLimit);
    DDX_Control(pDX, IDC_EDIT6, m_AddPoint);
    DDX_Control(pDX, IDC_PRODUCT_LIST, m_ProductList);
    DDX_Control(pDX, IDC_RECIPE_ID, m_RecipeId);
    DDX_Control(pDX, IDC_RECIPE_NAME, m_RecipeName);
}

BEGIN_MESSAGE_MAP(CRecipeEditorDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_DELETE, &CRecipeEditorDlg::OnDeleteRecipe)
    ON_BN_CLICKED(IDC_ADD, &CRecipeEditorDlg::OnAddRecipe)
    ON_BN_CLICKED(IDC_SAVE, &CRecipeEditorDlg::OnSaveRecipe)
    ON_BN_CLICKED(IDC_SAVE_ALL, &CRecipeEditorDlg::OnSaveAllRecipe)
    ON_COMMAND(ID_ADD, &CRecipeEditorDlg::OnAddItem)
    ON_COMMAND(ID_DELETE, &CRecipeEditorDlg::OnDeleteItem)
    ON_CBN_SELCHANGE(IDC_SKILL_BIG_TYPE, &CRecipeEditorDlg::OnSelChangeSkillBigType)
    ON_CBN_SELCHANGE(IDC_SKILL_SMALL_TYPE, &CRecipeEditorDlg::OnSelChangeSkillSmallType)
    ON_LBN_SELCHANGE(IDC_RECIPE_LIST, &CRecipeEditorDlg::OnSelChangeRecipeList)
END_MESSAGE_MAP()


// CRecipeEditorDlg message handlers

BOOL CRecipeEditorDlg::PreTranslateMessage(MSG* pMsg)
{
    if(::TranslateAccelerator(GetSafeHwnd(), m_hAccel, pMsg))   
        return true;

    if(pMsg->message == WM_KEYDOWN) 
    {
        switch(pMsg->wParam)
        {
        case VK_RETURN: //回车
            return TRUE;
        case VK_ESCAPE: //ESC
            return TRUE;
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}

BOOL CRecipeEditorDlg::OnInitDialog()
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

    m_hAccel=::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_ACCELERATOR));

    ShowVersionInformation();
    // TODO: Add extra initialization here
    LoadResourceFile();
    InitRecipeList();
    InitComboBox();
    InitListCtrl(true);
    InitSetInfo();

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRecipeEditorDlg::ShowVersionInformation()
{
    CString strVersion = "";

    strVersion.Format("配方编辑器Version %s", ApplicationConfig::Instance().GetFullVersion());

    this->SetWindowText(strVersion);
}

void CRecipeEditorDlg::LoadResourceFile()
{
    if ( !theRecipeConfig.LoadData(RecipeConfig_File) )
    {
        MessageBox( _T("Load Recipe.config failed!"), _T("Error"), MB_OK | MB_ICONERROR );
        return;
    }

    if ( !theItemDetailConfig.LoadItemDetailConfig(ItemDetial_FilePath) )
    {
        MessageBox(_T("Load ItemDetail config files failed!"), _T("Error"), MB_OK | MB_ICONERROR );
        return;
    }
}

void CRecipeEditorDlg::InitSetInfo()
{
    for (int i = 0; i < Enum_End; ++i)
    {
        m_xStringArray[i].Add(DefaultSelect);
    }
    // 材料ComboBox数据
    std::vector<CItemDetail::SItemCommon*> materialVec = theItemDetailConfig.GetMaterialItemList();
    std::vector<CItemDetail::SItemCommon*>::iterator iterBegin = materialVec.begin();
    std::vector<CItemDetail::SItemCommon*>::iterator iterEnd   = materialVec.end();
    for (; iterBegin != iterEnd; ++iterBegin)
    {
        SetInfo xSetInfo;
        xSetInfo.nValue = (*iterBegin)->ustItemID;
        xSetInfo.strName = (*iterBegin)->GetItemName();
        m_xSetInfo[PrimaryMaterial].push_back(xSetInfo);
        m_xStringArray[PrimaryMaterial].Add((*iterBegin)->GetItemName());
    }
    // 是否随机星级ComboBox数据
    m_xStringArray[IsRandStar].Add(DefineTrue);
    m_xStringArray[IsRandStar].Add(DefineFalse);
    
    SetInfo xSetInfo;
    xSetInfo.nValue = 0;
    xSetInfo.strName = "否";
    m_xSetInfo[IsRandStar].push_back(xSetInfo);
    xSetInfo.nValue = 1;
    xSetInfo.strName = "是";
    m_xSetInfo[IsRandStar].push_back(xSetInfo);

    // 是否绑定
    m_xStringArray[IsBound].Add(DefineTrue);
    m_xStringArray[IsBound].Add(DefineFalse);

    xSetInfo.nValue = 0;
    xSetInfo.strName = "否";
    m_xSetInfo[IsBound].push_back(xSetInfo);
    xSetInfo.nValue = 1;
    xSetInfo.strName = "是";
    m_xSetInfo[IsBound].push_back(xSetInfo);
}

void CRecipeEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRecipeEditorDlg::OnPaint()
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
HCURSOR CRecipeEditorDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CRecipeEditorDlg::OnDeleteRecipe()
{
    int nRecipeId = GetEditTextInt(m_RecipeId);
    if (nRecipeId <= 0)
    { return;}

    if ( MessageBox(_T("是否确定要删除该ID的配方？"), _T("Tip"), MB_YESNO | MB_ICONQUESTION) == IDNO )
    { return;}
    else
    {
        RecipeConfig::ItrComposeRecipeContainer iter = theRecipeConfig.GetRecipes().find(nRecipeId);
        theRecipeConfig.GetRecipes().erase(iter++);
        int nType = m_cmbBigType.GetCurSel();
        int nSubType = m_cmbSmallType.GetCurSel();
        ShowListItemByType(nType, nSubType);
    }
    ClearRecipeInfo();
}

void CRecipeEditorDlg::ClearRecipeInfo()
{
    m_RecipeId.SetWindowText(_T(""));
    // 清掉所有Edit中的内容
    m_RecipeName.SetWindowText(_T(""));
    m_UseEnegy.SetWindowText(_T(""));
    m_CastTime.SetWindowText(_T(""));
    m_UseMoney.SetWindowText(_T(""));
    m_ProficiencyLimit.SetWindowText(_T(""));
    m_SkillLevelLimit.SetWindowText(_T(""));
    m_AddPoint.SetWindowText(_T(""));
    // 删除ListCtrl中的内容
    m_ItemList.DeleteAllItems();
    m_ProductList.DeleteAllItems();
}

void CRecipeEditorDlg::OnAddRecipe()
{
    //使RecipeId可编辑
    m_RecipeId.EnableWindow(TRUE);
    ClearRecipeInfo();
}

void CRecipeEditorDlg::OnSaveRecipe()
{
    RecipeConfig::SRecipe* pRecipe = GetRecipeInfo();
    RecipeConfig::SRecipe* pOldRecipe = theRecipeConfig.GetItemRuleByRuleId(pRecipe->RecipeId);
    if (pOldRecipe != NULL)
    {
        if ( MessageBox("该ID的配方已经存在，确认保存将使用当前数据覆盖原数据，是否保存？", "Warning", MB_YESNO | MB_ICONWARNING) == IDNO )
        {// 选择否，直接返回
            return;
        }
        else
        {
            theRecipeConfig.GetRecipes().insert( std::make_pair(pRecipe->RecipeId, *pRecipe) );
        }
    }
    else
    {
        theRecipeConfig.GetRecipes().insert( std::make_pair(pRecipe->RecipeId, *pRecipe) );
    }
    // 刷新列表
    int nType = m_cmbBigType.GetCurSel();
    int nSubType = m_cmbSmallType.GetCurSel();
    ShowListItemByType(nType, nSubType);
}


void CRecipeEditorDlg::OnSaveAllRecipe()
{
    bool bResult = false;
#ifdef DEBUG
    bResult = theRecipeConfig.SaveFile("..\\Data\\Config\\RecipeTest.config");
#endif
    bResult = theRecipeConfig.SaveFile(RecipeConfig_File);

    if ( !bResult )
    {
        MessageBox("保存配方文件Recipe.config失败，请检查文件是否可写!", "Tip", MB_OK | MB_ICONERROR);
        return;
    }
    else
    {
        MessageBox("保存配方文件Recipe.config成功!", "Tip", MB_OK);
    }
}

void CRecipeEditorDlg::InitRecipeList()
{
    m_RecipeList.ResetContent();
    RecipeConfig::ComposeRecipeContainer recipesMap = theRecipeConfig.GetRecipes();
    RecipeConfig::ItrComposeRecipeContainer iterBegin = recipesMap.begin();
    RecipeConfig::ItrComposeRecipeContainer iterEnd   = recipesMap.end();
    for (int num = 0; iterBegin != iterEnd; ++iterBegin, ++num)
    {
        m_RecipeList.InsertString( num, iterBegin->second.Name.c_str() );
    }
}

int CRecipeEditorDlg::SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle)
{
    xList.SetExtendedStyle(dwStyle);

    RECT rect;
    xList.GetClientRect(&rect);

    return (rect.right - rect.left);
}

void CRecipeEditorDlg::InitListCtrl(bool bInsert)
{
    DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    int nWidth = 0;
    if (bInsert)
    {
        // 消耗材料
        nWidth = SetListCtrlStyle(m_ItemList, dwStyle);
        m_ItemList.InsertColumn( 0, TEXT("【消耗材料】"), 0, (40 * nWidth)/100 );
        m_ItemList.InsertColumn( 1, TEXT("【消耗材料数量】"), 0, (60 * nWidth)/100 );
        // 产出物品
        nWidth = SetListCtrlStyle(m_ProductList, dwStyle);
        m_ProductList.InsertColumn( 0, TEXT("【物品ID】"), 0, (15 * nWidth)/100 );
        m_ProductList.InsertColumn( 1, TEXT("【概率%】"), 0, (15 * nWidth)/100 );
        m_ProductList.InsertColumn( 2, TEXT("【产出数量】"), 0, (15 * nWidth)/100 );
        m_ProductList.InsertColumn( 3, TEXT("【是否随机星级】"), 0, (20 * nWidth)/100 );
        m_ProductList.InsertColumn( 4, TEXT("【最大随机星级】"), 0, (20 * nWidth)/100 );
        m_ProductList.InsertColumn( 5, TEXT("【是否绑定】"), 0, (15 * nWidth)/100 );
    }
    else
    {
        // 消耗材料
        nWidth = SetListCtrlStyle(m_ItemList, dwStyle);
        m_ItemList.SetColumnWidth(0, (40 * nWidth) / 100);
        m_ItemList.SetColumnWidth(1, (60 * nWidth) / 100);
        // 产出物品
        nWidth = SetListCtrlStyle(m_ProductList, dwStyle);
        m_ProductList.SetColumnWidth(0, (15 * nWidth)/100);
        m_ProductList.SetColumnWidth(1, (15 * nWidth)/100);
        m_ProductList.SetColumnWidth(2, (15 * nWidth)/100);
        m_ProductList.SetColumnWidth(3, (20 * nWidth)/100);
        m_ProductList.SetColumnWidth(4, (20 * nWidth)/100);
        m_ProductList.SetColumnWidth(5, (15 * nWidth)/100);
    }
}

void CRecipeEditorDlg::InitComboBox()
{
    RecipeConfig::TypeContainer m_TypeVec = theRecipeConfig.GetTypeContainer();
    RecipeConfig::ItrTypeContainer iterTypeBegin = m_TypeVec.begin();
    RecipeConfig::ItrTypeContainer iterTypeEnd   = m_TypeVec.end();
    //m_cmbBigType.InsertString(0, "请选择");
    for (int num=0; iterTypeBegin != iterTypeEnd; ++iterTypeBegin, ++num)
    {
        m_cmbBigType.InsertString(num, iterTypeBegin->TypeName.c_str());
    }
    //m_cmbBigType.SetCurSel(0);
}

void CRecipeEditorDlg::OnAddItem()
{// 添加一项Ctrl+N
    HWND hWnd = GetFocus()->m_hWnd;
    if (hWnd == m_ItemList.m_hWnd)
    {
        AddItemList(m_ItemList, m_xStringArray[PrimaryMaterial]);
    }
    else if (hWnd == m_ProductList.m_hWnd)
    {
        AddProductList(m_ProductList, m_xStringArray[IsRandStar]);
    }
}

void CRecipeEditorDlg::AddItemList(CXListCtrl& xList, CStringArray& xStringArray)
{
    int nSubItem = 0;
    int nCount = xList.GetItemCount();

    xList.InsertItem(nCount, "");
    xList.SetComboBox(nCount, nSubItem++, TRUE, &xStringArray, xStringArray.GetSize(), 0);
    xList.SetEdit(nCount, nSubItem);
}

void CRecipeEditorDlg::AddProductList(CXListCtrl& xList, CStringArray& xStringArray)
{
    int nSubItem = 0;
    int nCount = xList.GetItemCount();

    xList.InsertItem(nCount, "");
    xList.SetEdit(nCount, nSubItem++);
    xList.SetEdit(nCount, nSubItem++);
    xList.SetEdit(nCount, nSubItem++);
    xList.SetComboBox(nCount, nSubItem++, TRUE, &xStringArray, xStringArray.GetSize(), 0);
    xList.SetEdit(nCount, nSubItem++);
    xList.SetComboBox(nCount, nSubItem++, TRUE, &xStringArray, xStringArray.GetSize(), 0);
}

void CRecipeEditorDlg::OnDeleteItem()
{// 删除一项Delete
    HWND hWnd = GetFocus()->m_hWnd;
    if (hWnd == m_ItemList.m_hWnd)
    {
        int nIndex = m_ItemList.GetCurSel();
        if (nIndex != -1)
        {
            m_ItemList.DeleteItem(nIndex);
        }
    }
    else if(hWnd == m_ProductList.m_hWnd)
    {
        int nIndex = m_ProductList.GetCurSel();
        if (nIndex != -1)
        {
            m_ProductList.DeleteItem(nIndex);
        }
    }
}

void CRecipeEditorDlg::ShowListItemByType(int nType, int nSubType)
{
    m_RecipeList.ResetContent();
    //RecipeConfig::ComposeRecipeContainer recipesMap = theRecipeConfig.GetRecipes();
    RecipeConfig::ItrComposeRecipeContainer iterBegin = theRecipeConfig.GetRecipes().begin();
    RecipeConfig::ItrComposeRecipeContainer iterEnd   = theRecipeConfig.GetRecipes().end();
    if (nSubType == 0)
    {
        int i = 0;
        for (; iterBegin != iterEnd; ++iterBegin)
        {
            if (iterBegin->second.Type == nType)
            {
                m_RecipeList.InsertString( i++, iterBegin->second.Name.c_str() );
            }
        }
    }
    else
    {
        int i = 0;
        for (; iterBegin != iterEnd; ++iterBegin)
        {
            if (iterBegin->second.Type == nType && iterBegin->second.SubType == nSubType)
            {
                m_RecipeList.InsertString( i++, iterBegin->second.Name.c_str() );
            }
        }
    }
}

void CRecipeEditorDlg::OnSelChangeSkillBigType()
{// 更改技能大类
    int nType = m_cmbBigType.GetCurSel();
    RecipeConfig::SType* pType = theRecipeConfig.GetTypeById(nType);
    if (pType == NULL)
    { return;}
    // 修改小类ComboBox
    RecipeConfig::ItrSubTypeContainer iterBegin = pType->m_SubTypeVec.begin();
    RecipeConfig::ItrSubTypeContainer iterEnd   = pType->m_SubTypeVec.end();
    m_cmbSmallType.ResetContent();
    m_cmbSmallType.InsertString(0, DefaultSelect);
    for (int i=1; iterBegin != iterEnd; ++iterBegin, ++i)
    {
        m_cmbSmallType.InsertString(i, iterBegin->subTypeName.c_str());
    }
    m_cmbSmallType.SetCurSel(0);
    // 修改List显示的内容
    int nSubType = m_cmbSmallType.GetCurSel();
    ShowListItemByType(nType, nSubType);
}

void CRecipeEditorDlg::OnSelChangeSkillSmallType()
{// 更改了小类ComboBox的选择
    int nSubType = m_cmbSmallType.GetCurSel();
    int nType = m_cmbBigType.GetCurSel();
    ShowListItemByType(nType, nSubType);
}

void CRecipeEditorDlg::OnSelChangeRecipeList()
{
    int nIndex = m_RecipeList.GetCurSel();
    CString strRecipeName;
    m_RecipeList.GetText(nIndex, strRecipeName);
    RecipeConfig::SRecipe* pRecipe = theRecipeConfig.GetItemRuleByRecipeName( strRecipeName.GetBuffer() );
    ShowRecipeInfo(pRecipe);
    m_cmbBigType.SetCurSel(pRecipe->Type);
    
    RecipeConfig::SType* pType = theRecipeConfig.GetTypeById(pRecipe->Type);
    if (pType == NULL)
    { return;}

    RecipeConfig::ItrSubTypeContainer iterSubBegin = pType->m_SubTypeVec.begin();
    RecipeConfig::ItrSubTypeContainer iterSubEnd   = pType->m_SubTypeVec.end();
    m_cmbSmallType.InsertString(0, DefaultSelect);
    for (int nIndex = 1; iterSubBegin != iterSubEnd; ++iterSubBegin, ++nIndex)
    {
        m_cmbSmallType.InsertString(nIndex, iterSubBegin->subTypeName.c_str());
    }
    m_cmbSmallType.SetCurSel(pRecipe->SubType);
}

void CRecipeEditorDlg::ShowRecipeInfo(RecipeConfig::SRecipe* pRecipe)
{
    char buffer[20] = {0};
    sprintf_s(buffer, sizeof(buffer) - 1, "%d", pRecipe->RecipeId);
    m_RecipeId.SetWindowText(buffer);   // Id

    m_RecipeName.SetWindowText(pRecipe->Name.c_str());  // Name
    
    memset(buffer, 0, sizeof(buffer));
    sprintf_s(buffer, sizeof(buffer) - 1, "%d", pRecipe->Products.begin()->NeedActivity);
    m_UseEnegy.SetWindowText(buffer);   // 消耗活力值

    memset(buffer, 0, sizeof(buffer));
    sprintf_s(buffer, sizeof(buffer) - 1, "%d", pRecipe->Products.begin()->CastTime);
    m_CastTime.SetWindowText(buffer);   // 吟唱时间

    memset(buffer, 0, sizeof(buffer));
    sprintf_s(buffer, sizeof(buffer) - 1, "%d", pRecipe->Products.begin()->NeedMoney);
    m_UseMoney.SetWindowText(buffer);   // 消耗金钱

    memset(buffer, 0, sizeof(buffer));
    sprintf_s(buffer, sizeof(buffer) - 1, "%d", pRecipe->ProficiencyLimit);
    m_ProficiencyLimit.SetWindowText(buffer);   // 提升到的熟练度上限

    memset(buffer, 0, sizeof(buffer));
    sprintf_s(buffer, sizeof(buffer) - 1, "%d", pRecipe->SkillLevelLimit);
    m_SkillLevelLimit.SetWindowText(buffer);    // 提升到的等级上限

    memset(buffer, 0, sizeof(buffer));
    sprintf_s(buffer, sizeof(buffer) - 1, "%d", pRecipe->AddPointValue);
    m_AddPoint.SetWindowText(buffer);   // 增加熟练度

    ShowMaterialInfo(pRecipe->PrimaryMaterials);
    ShowProductInfo(pRecipe->Products);
}

const char* CRecipeEditorDlg::GetSetInfoName(vector<SetInfo> &vecSetInfo, int nValue, const char *pszDef /* = ""*/)
{
    if (nValue == -1)
    {
        return pszDef;
    }

    setiter iter = vecSetInfo.begin();
    setiter end = vecSetInfo.end();

    for ( ; iter != end; ++iter)
    {

        if ((*iter).nValue == nValue)
        {
            return (*iter).strName.c_str();
        }
    }

    return pszDef;
}

int CRecipeEditorDlg::GetSetInfoValue(vector<SetInfo> &vecSetInfo, string strName)
{
    if (strName.empty())
    {
        return -1;
    }

    setiter iter = vecSetInfo.begin();
    setiter end = vecSetInfo.end();
    for ( ; iter != end; ++iter)
    {

        if ((*iter).strName == strName)
        {
            return (*iter).nValue;
        }
    }

    return -1;
}

void CRecipeEditorDlg::ShowMaterialInfo(RecipeConfig::MaterialContainer& ItemVec)
{
    RecipeConfig::ItrMaterialContainer iterBegin = ItemVec.begin();
    RecipeConfig::ItrMaterialContainer iterEnd   = ItemVec.end();
    int nCount = m_ItemList.GetItemCount();
    int nIndex = 0;
    char szCount[10] = {0};
    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (nIndex >= nCount)   // 如果当前列表为空，则新增一行
        {
            AddItemList(m_ItemList, m_xStringArray[PrimaryMaterial]);
            ++nCount;
        }
        //if (iterBegin->MaterialId != -1)
        //{
        //    //m_ItemList.SetComboBox(nCount, 0, TRUE, &m_xStringArray[PrimaryMaterial], m_xStringArray[PrimaryMaterial].GetCount(), 0);
        // 
        //    m_ItemList.SetItemText( nIndex, 0, GetSetInfoName(m_xSetInfo[PrimaryMaterial], iterBegin->MaterialId) );    // ???获得当前下拉框内容
        //    
        //    memset(szCount, 0, sizeof(szCount));
        //    sprintf_s(szCount, sizeof(szCount) - 1, "%d", iterBegin->Count);
        //    m_ItemList.SetItemText( nIndex, 1, szCount );
        //    
        //    ++nIndex;
        //}
    }
    // 多余的删除
    for (int i = nCount - 1; i>=nIndex; --i)
    {
        m_ItemList.DeleteItem(i);
    }
}

void CRecipeEditorDlg::ShowProductInfo(RecipeConfig::ProductsContainer& ProductVec)
{
    RecipeConfig::ItrProductContainer iterBegin = ProductVec.begin();
    RecipeConfig::ItrProductContainer iterEnd   = ProductVec.end();
    int nCount = m_ProductList.GetItemCount();
    int nIndex = 0;
    char szTemp[10] = {0};
    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (nIndex >= nCount)
        {
            AddProductList(m_ProductList, m_xStringArray[IsRandStar]);
            ++nCount;
        }
        if (iterBegin->ProductItems.begin()->ItemId != -1) // 由于现阶段只有一个产出物品，所以只取Begin
        {
            //m_ProductList.SetComboBox(nIndex, 3, TRUE, &m_xStringArray[IsRandStar], m_xStringArray[IsRandStar].GetCount(), 0);

            memset(szTemp, 0, sizeof(szTemp));
            sprintf_s(szTemp, sizeof(szTemp) - 1, "%d", iterBegin->ProductItems.begin()->ItemId);
            m_ProductList.SetItemText(nIndex, 0, szTemp);   // 产品Id
            
            memset(szTemp, 0, sizeof(szTemp));
            sprintf_s(szTemp, sizeof(szTemp) - 1, "%d", iterBegin->ProductItems.begin()->Probility);
            m_ProductList.SetItemText(nIndex, 1, szTemp);
            
            memset(szTemp, 0, sizeof(szTemp));
            sprintf_s(szTemp, sizeof(szTemp) - 1, "%d", iterBegin->ProductItems.begin()->Count);
            m_ProductList.SetItemText(nIndex, 2, szTemp);

            m_ProductList.SetItemText( nIndex, 3, GetSetInfoName(m_xSetInfo[IsRandStar], iterBegin->ProductItems.begin()->bIsStarRandom) );

            memset(szTemp, 0, sizeof(szTemp));
            sprintf_s(szTemp, sizeof(szTemp) - 1, "%d", iterBegin->ProductItems.begin()->nStarLevel);
            m_ProductList.SetItemText(nIndex, 4, szTemp);

            m_ProductList.SetItemText( nIndex, 5, GetSetInfoName(m_xSetInfo[IsBound], iterBegin->ProductItems.begin()->bIsBound) );
            ++nIndex;
        }
    }
    // 多余的删除
    for (int i=nCount - 1; i>=nIndex; --i)
    {
        m_ProductList.DeleteItem(i);
    }
}

int CRecipeEditorDlg::GetListItemInt(CListCtrl &xList, int nItem, int nSubItem, int nDef)
{
    CString strValue = xList.GetItemText(nItem, nSubItem);

    if (strValue.IsEmpty())
    {
        return nDef;
    }

    return (atoi(strValue.GetBuffer()));
}

int CRecipeEditorDlg::GetEditTextInt(CEdit& xEdit)
{
    CString strEdit;
    xEdit.GetWindowText(strEdit);
    if (strEdit.IsEmpty())
    {
        return -1;
    }
    return atoi(strEdit);
}

RecipeConfig::SRecipe* CRecipeEditorDlg::GetRecipeInfo()
{
    int RecipeId = GetEditTextInt(m_RecipeId);
    if (RecipeId <= -1)
    {
        MessageBox(_T("配方ID出错，请检查!"), "Error", MB_OK | MB_ICONERROR);
        return NULL;
    }
    CString strRecipeName;
    m_RecipeName.GetWindowText(strRecipeName);  // 配方名称

    CString strSubTypeName;
    m_cmbSmallType.GetWindowText(strSubTypeName); // 小类名称

    int ProficiencyLimit = GetEditTextInt(m_ProficiencyLimit);
    int SkillLimit = GetEditTextInt(m_SkillLevelLimit);
    int addPoint = GetEditTextInt(m_AddPoint);

    RecipeConfig::SRecipe* pRecipe = theRecipeConfig.GetItemRuleByRuleId(RecipeId);
    if (pRecipe != NULL)
    {
        pRecipe->Type = m_cmbBigType.GetCurSel();
        pRecipe->SubType = m_cmbSmallType.GetCurSel();
        pRecipe->RecipeId = RecipeId;
        pRecipe->Name = strRecipeName.GetBuffer();
        pRecipe->ProficiencyLimit = ProficiencyLimit;
        pRecipe->SkillLevelLimit = SkillLimit;
        pRecipe->AddPointValue = addPoint;
        pRecipe->SubTypeName = strSubTypeName.GetBuffer();
        GetItemInfo(m_ItemList, *pRecipe);
        GetProductInfo(m_ProductList, *pRecipe);

        return pRecipe;
    }
    else
    {
        m_Recipe.Type = m_cmbBigType.GetCurSel();
        m_Recipe.SubType = m_cmbSmallType.GetCurSel();
        m_Recipe.RecipeId = RecipeId;
        m_Recipe.Name = strRecipeName.GetBuffer();
        m_Recipe.ProficiencyLimit = ProficiencyLimit;
        m_Recipe.SkillLevelLimit = SkillLimit;
        m_Recipe.AddPointValue = addPoint;
        m_Recipe.SubTypeName = strSubTypeName.GetBuffer();
        GetItemInfo(m_ItemList, m_Recipe);
        GetProductInfo(m_ProductList, m_Recipe);

        return &m_Recipe;
    }
}

void CRecipeEditorDlg::GetItemInfo(CXListCtrl& xList, RecipeConfig::SRecipe& recipe)
{
    recipe.PrimaryMaterials.clear();
    int nItemCount = xList.GetItemCount();
    for (int i=0; i<nItemCount; ++i)
    {
        CString strItem = xList.GetItemText(i, 0);
        if (strItem == DefaultSelect)   // 如果没有选择材料
        { continue;}

        RecipeConfig::SMaterial xMaterial;
        CItemDetail::SItemCommon* pItem = theItemDetailConfig.GetItemByName(strItem.GetBuffer());
        if (pItem == NULL)
        { continue;}
        /*else
        { xMaterial.MaterialId = pItem->ustItemID;}*/

        xMaterial.Count = GetListItemInt(xList, i, 1, 0);

        recipe.PrimaryMaterials.push_back(xMaterial);
    }
}

void CRecipeEditorDlg::GetProductInfo(CXListCtrl& xList, RecipeConfig::SRecipe& recipe)
{
    int energy = GetEditTextInt(m_UseEnegy);
    int castTime = GetEditTextInt(m_CastTime);
    int money = GetEditTextInt(m_UseMoney);
    // 由于产出物品现阶段只有一个，故无需循环
    RecipeConfig::SProduct xProduct;
    xProduct.NeedActivity = energy;
    xProduct.CastTime = castTime;
    xProduct.NeedMoney = money;
    RecipeConfig::SItem xItem;
    xItem.ItemId = GetListItemInt(xList, 0, 0, -1);
    xItem.Probility = GetListItemInt(xList, 0, 1, 0);
    xItem.Count = GetListItemInt(xList, 0, 2, 0);
    CString strRnadStar = xList.GetItemText(0, 3);
    xItem.bIsStarRandom = GetSetInfoValue(m_xSetInfo[IsRandStar], strRnadStar.GetBuffer());
    xItem.nStarLevel = GetListItemInt(xList, 0, 4, 0);
    CString strBound = xList.GetItemText(0, 5);
    xItem.bIsBound = GetSetInfoValue(m_xSetInfo[IsBound], strBound.GetBuffer());
    xProduct.ProductItems.push_back(xItem);
    recipe.Products[0] = xProduct;  // 由于暂时只有一个产出产品，所以就是0
}