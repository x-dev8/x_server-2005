// RecipeEditorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "./XListCtrl/XListCtrl.h"
#include "Define.h"
#include "RecipeConfig.h"

// CRecipeEditorDlg dialog
class CRecipeEditorDlg : public CDialog
{
    // Construction
public:
    CRecipeEditorDlg(CWnd* pParent = NULL);	// standard constructor

    // Dialog Data
    enum { IDD = IDD_RECIPEEDITOR_DIALOG };
    BOOL PreTranslateMessage(MSG* pMsg);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


    // Implementation
protected:
    HICON m_hIcon;
    HACCEL m_hAccel;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    void ShowVersionInformation();
    void InitRecipeList();  // 初始化配方列表
    void InitComboBox();    // 初始化下拉框
    void InitListCtrl(bool bInsert);    // 初始化列表
    int  SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle); // 设置ListCtrl风格
    void LoadResourceFile();
    void InitSetInfo();
    void AddItemList(CXListCtrl& xList, CStringArray& xStringArray);
    void AddProductList(CXListCtrl& xList, CStringArray& xStringArray);
    void ShowListItemByType(int nType, int nSubType);// 根据类型显示List中的项
    void ShowRecipeInfo(RecipeConfig::SRecipe* pRecipe); // 显示配方的信息
    const char* GetSetInfoName(vector<SetInfo> &vecSetInfo, int nValue, const char *pszDef = "");   // 通过nValue得到下拉框的内容
    int  GetSetInfoValue(vector<SetInfo> &vecSetInfo, string strName);     // 得到下拉框的值
    void ShowMaterialInfo(RecipeConfig::MaterialContainer& ItemVec);    // 显示材料信息
    void ShowProductInfo(RecipeConfig::ProductsContainer& ProductVec);  // 显示产出信息
    int  GetListItemInt(CListCtrl &xList, int nItem, int nSubItem, int nDef = 0);
    int  GetEditTextInt(CEdit& xEdit);  // 得到Edit控件的内容
    RecipeConfig::SRecipe* GetRecipeInfo();
    void GetItemInfo(CXListCtrl& xList, RecipeConfig::SRecipe& recipe);
    void GetProductInfo(CXListCtrl& xList, RecipeConfig::SRecipe& recipe);
    void ClearRecipeInfo(); // 清掉当前显示的所有配方信息
public:
    std::vector<SetInfo> m_xSetInfo[Enum_End];// Combobox设定的信息
    CComboBox m_cmbBigType;     // 技能大类
    CComboBox m_cmbSmallType;   // 技能小类
    CListBox m_RecipeList;      // 配方列表
    CEdit m_RecipeId;           // 配方名称显示
    CEdit m_RecipeName;         // 配方名称
    CEdit m_UseEnegy;           // 消耗活力值
    CEdit m_CastTime;           // 制造吟唱时间
    CEdit m_UseMoney;           // 消耗金钱
    CXListCtrl m_ItemList;      // 消耗的物品列表
    CEdit m_ProficiencyLimit;   // 生产该物品提升的熟练度上限值
    CEdit m_SkillLevelLimit;    // 生产物品能提升到的等级上限
    CEdit m_AddPoint;           // 增加熟练度
    CXListCtrl m_ProductList;   // 产出物品列表
    CStringArray m_xStringArray[Enum_End]; // comboBox字符串信息
    afx_msg void OnDeleteRecipe();  // 删除配方
    afx_msg void OnAddRecipe();     // 添加配方
    afx_msg void OnSaveRecipe();    // 保存配方
    afx_msg void OnSaveAllRecipe(); // 保存所有配方
    afx_msg void OnAddItem();       // 添加一项 Ctrl+A
    afx_msg void OnDeleteItem();    // 删除一项 Ctrl+X
    afx_msg void OnSelChangeSkillBigType();
    afx_msg void OnSelChangeSkillSmallType();
    afx_msg void OnSelChangeRecipeList();

    RecipeConfig::SRecipe m_Recipe;
};
