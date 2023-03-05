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
    void InitRecipeList();  // ��ʼ���䷽�б�
    void InitComboBox();    // ��ʼ��������
    void InitListCtrl(bool bInsert);    // ��ʼ���б�
    int  SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle); // ����ListCtrl���
    void LoadResourceFile();
    void InitSetInfo();
    void AddItemList(CXListCtrl& xList, CStringArray& xStringArray);
    void AddProductList(CXListCtrl& xList, CStringArray& xStringArray);
    void ShowListItemByType(int nType, int nSubType);// ����������ʾList�е���
    void ShowRecipeInfo(RecipeConfig::SRecipe* pRecipe); // ��ʾ�䷽����Ϣ
    const char* GetSetInfoName(vector<SetInfo> &vecSetInfo, int nValue, const char *pszDef = "");   // ͨ��nValue�õ������������
    int  GetSetInfoValue(vector<SetInfo> &vecSetInfo, string strName);     // �õ��������ֵ
    void ShowMaterialInfo(RecipeConfig::MaterialContainer& ItemVec);    // ��ʾ������Ϣ
    void ShowProductInfo(RecipeConfig::ProductsContainer& ProductVec);  // ��ʾ������Ϣ
    int  GetListItemInt(CListCtrl &xList, int nItem, int nSubItem, int nDef = 0);
    int  GetEditTextInt(CEdit& xEdit);  // �õ�Edit�ؼ�������
    RecipeConfig::SRecipe* GetRecipeInfo();
    void GetItemInfo(CXListCtrl& xList, RecipeConfig::SRecipe& recipe);
    void GetProductInfo(CXListCtrl& xList, RecipeConfig::SRecipe& recipe);
    void ClearRecipeInfo(); // �����ǰ��ʾ�������䷽��Ϣ
public:
    std::vector<SetInfo> m_xSetInfo[Enum_End];// Combobox�趨����Ϣ
    CComboBox m_cmbBigType;     // ���ܴ���
    CComboBox m_cmbSmallType;   // ����С��
    CListBox m_RecipeList;      // �䷽�б�
    CEdit m_RecipeId;           // �䷽������ʾ
    CEdit m_RecipeName;         // �䷽����
    CEdit m_UseEnegy;           // ���Ļ���ֵ
    CEdit m_CastTime;           // ��������ʱ��
    CEdit m_UseMoney;           // ���Ľ�Ǯ
    CXListCtrl m_ItemList;      // ���ĵ���Ʒ�б�
    CEdit m_ProficiencyLimit;   // ��������Ʒ����������������ֵ
    CEdit m_SkillLevelLimit;    // ������Ʒ���������ĵȼ�����
    CEdit m_AddPoint;           // ����������
    CXListCtrl m_ProductList;   // ������Ʒ�б�
    CStringArray m_xStringArray[Enum_End]; // comboBox�ַ�����Ϣ
    afx_msg void OnDeleteRecipe();  // ɾ���䷽
    afx_msg void OnAddRecipe();     // ����䷽
    afx_msg void OnSaveRecipe();    // �����䷽
    afx_msg void OnSaveAllRecipe(); // ���������䷽
    afx_msg void OnAddItem();       // ���һ�� Ctrl+A
    afx_msg void OnDeleteItem();    // ɾ��һ�� Ctrl+X
    afx_msg void OnSelChangeSkillBigType();
    afx_msg void OnSelChangeSkillSmallType();
    afx_msg void OnSelChangeRecipeList();

    RecipeConfig::SRecipe m_Recipe;
};
