// EditorView.h : interface of the CEditorView class
//
#pragma once
#include "QuestEditorDoc.h"
#include "Define.h"
#include "afxwin.h"

class DropMonsterDialog;
class DropItemDialog;
class QuestFind;
class QuestStringEdit;

class CQuestEditorView : public CFormView
{
protected: // create from serialization only
	CQuestEditorView();
	DECLARE_DYNCREATE(CQuestEditorView)

public:
	enum{ IDD = IDD_EDITOR };

// Attributes
public:
	CQuestEditorDoc* GetDocument() const;

public:
	vector<SetInfo> m_xSetInfo[Enum_End];			//设定信息
	CStringArray m_xStringArray[Enum_End];			//字符串信息

	CString m_strDropItemFile;
	MonsterAndDrop m_xMonsterDrop;

	DropTaskItem m_xDropTaskItem;

	CXListCtrl *m_pxListCtrl;		//保存当前操作的listctrl
	int m_nItem;
	int m_nSubItem;

private:
	SQuest m_xQuest;

	DropMonsterDialog *m_pxDropMonsterDialog;
	DropItemDialog *m_pxDropItemDialog;
	QuestFind *m_pxQuestFind;
	QuestStringEdit *m_pxQuestStringEdit;
	
	CString m_strValue;				//保存当时的选择
	

	string m_strQuestFile;			//当前加载的任务文件

	bool m_bRemoveReadOnly;

	vector<int> m_vecFindQuestId;

	int m_nShowFindId;

	typedef void (CQuestEditorView::*_FindFun)(CString strValue, FindInfo *pFindInfo);
	static _FindFun FindFun[Enum_QuestMax];//查找函数数组

	std::map<int, int> m_mapViewQuest;

// Operations
public:

	void InitInformation();		
	void InitSetInfo();
	void InitListCtrl(bool bInsert);
	void InitPropertyList();		//初始化列表

	void SaveSetInfoFile();		//保存设置
	void SaveSetInfoFile(const char *pszSecion, char *pszKey, vector<SetInfo> &vecSetInfo);

	bool AddQuestInList(int nIndex, int &nCount, SQuest *xpQuest);
	void ShowQuestInformation(SQuest &xQuest);			//显示任务信息
	void ShowQuestInformation(HTREEITEM hItem);
	void ClearQuestInformation();
	void ShowRequirementList(CXListCtrl &xRequirementList, vector<SQuestRequirement> &vecRequirement,bool bCommit);	//显示任务需求
	void ShowRewardList(vector<SQuestReward> &vecReward);					//显示任务奖励

	void AddQuestRequiremenetList(CXListCtrl &xRequirementList, CStringArray &xStringArray,bool bCommit);	//添加一个任务要求
	void AddQuestRewardList(CXListCtrl &xRewardList, CStringArray &xStringArray);	//添加一个任务奖励
	void GetQuestRequirement(CXListCtrl &xRequirementList, SQuest &xQuest, bool bCommit);	//获得任务要求
	void GetQuestReward(CXListCtrl &xRewardList, SQuest &xQuest);		//获得奖励

	bool SubString(string &strDest,string &strSub,string strSign);
	int SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle);
	int GetListCtrlCurSel(CListCtrl &xList);

	void SetEditText(CEdit& xEdit, char *pszFormat, ...);	
	int GetEditInt(CEdit& xEdit, int nDef);
	void InsertItemText(CListCtrl &xList, int nItem, char *pszFormat, ...);
	void SetListItemText(CListCtrl &xList, int nItem, int nSubItem, char *pszFormat, ...);
	int GetListItemInt(CListCtrl &xList,int nItem, int nSubItem,int nDef);

	void ClickList(CListCtrl &xList, NMHDR *pNMHDR);

	const char* GetSetInfoName(vector<SetInfo> &vecSetInfo, int nValue, const char* pszDef = "");	
	int GetSetInfoValue(vector<SetInfo> &vecSetInfo, string strName);	

	/////////////////////////////////////////////////////////////////////////////////
	int FindQuest(CString strValue, int nType, FindInfo *pFindInfo = NULL);
	void ShowFindQuest(int nId);
	void ShowNextFindQuest();
	///////////////////////////////////////////////////////////////////
	void SetListItemCanEdit();

	void LoadResourceFiles();

	void AddListItem();
	void DeleteListItem();
	void DeleteQuest();

	void ShowFindDialog();
	void ShowStringEditDialog();

	void SetListItemColor(CXListCtrl &xList, int nItem, int nSubItem, COLORREF dwColor);
	void SetListItemBGroundColor(CXListCtrl &xList, int nItem, int nSubItem, COLORREF dwColor);
private:	

	void GetFormatString(char* szText, int nSize, char* szFormat, va_list &valist);

	void FindByQuestId(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByQuestNameId(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByQuestName(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByQuality(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByContentId(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByContent(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByTargetId(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByTarget(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByMapId(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByMapName(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByNpcId(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByNpcName(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByCanAssist(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByCanShare(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByRepeate(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByCancel(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByPreRequementItemId(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByPreRequementItemName(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByPostRequementItemId(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByPostRequementItemName(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByRewardItemId(CString strValue, FindInfo *pFindInfo = NULL);
	void FindByRewardItemName(CString strValue, FindInfo *pFindInfo = NULL);

	int AddInQuestList();
	bool SaveQuestAndStringInFile(const char* pszFile, SQuest &xQuest);

	void ShowMainMenu();
	void ShowQuestTreeList();
	void AddQuestInTree(HTREEITEM hParent, SQuest &xQuest, HTREEITEM hInsertAfter = TVI_LAST);

	bool DeleteQuestFile(int nId);

	string GetFileFullPath(const char* pszParentPath, int nId, const char *pszPath, const char* pExt);
	
	void SetCurrentWorkDir();
	void CheckFilePathExist(const char *pszPath);

	void ShowDropMonsterDialog();
	void ShowDropItemDialog();
	
	void SetQuestStringId(int nQuestId);
	///////////////////////////////////////////////////////////////
	void OnComboSelectionProperty(WPARAM nItem, LPARAM nSubItem);
	void OnComboSelectionRequiement(WPARAM nItem, LPARAM nSubItem);
	void OnComboSelectionReward(WPARAM nItem, LPARAM nSubItem);

	void OnEditEndProperty(WPARAM nItem, LPARAM nSubItem);
	void OnEditEndRequiement(WPARAM nItem, LPARAM nSubItem);
	void OnEditEndReward(WPARAM nItem, LPARAM nSubItem);

	//读取显示字串函数
	void ReadSetConfig(const char* pszPath);
	void RemoveFileReadOnly(const char* pszPath);

	void GetQuestStringId(int nQuest, std::vector<int>& vecStringId);

	/////显示作用
	void SetQuestViewColor(SQuest *pQuest);
	void AddQuestView(int nQuestId, int Type, COLORREF leftcolor, COLORREF rightcolor);
	void SetQuestColor(int nQuestId, COLORREF leftcolor, COLORREF rightcolor);
	void RemoveQuestView(int nQuestId);



	//////////////////
	void SaveQuestIdList(const char* szPath);

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

	DECLARE_MESSAGE_MAP()
// Implementation
public:
	virtual ~CQuestEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CXListCtrl m_listProperty;
	CXListCtrl m_listReward;
	CXListCtrl m_listPreRequirement;
	CXListCtrl m_listPostRequiement;
	MyTreeCtrl m_xTreeQuest;

	CStatic m_staticPre;
	CStatic m_staticPost;
	CStatic m_staticReward;
	CStatic m_staticSave;
	CButton m_checkBatch;

// Generated message map functions
public:
	afx_msg void OnLbnDblclkListQuest();
	afx_msg LRESULT OnComboSelection(WPARAM, LPARAM);
	afx_msg LRESULT OnCheckbox(WPARAM, LPARAM);
	afx_msg LRESULT OnEditEnd(WPARAM, LPARAM);
	afx_msg void OnNMClickListReward(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPreRequiement(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPostRequiement(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListProprety(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnFileLoadQuestFile();
	afx_msg void OnFileSaveQuestFile();
	afx_msg void OnFileSaveAt();
	afx_msg void OnFileFind();
	afx_msg void OnNMClickTreeItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeQuest(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMDClickListPostRequiement(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListPostRequeiment(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeletedDrop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStringChange();
	afx_msg void OnNpcChange();

	afx_msg void OnRClickEditor(NMHDR *pNMHDR, LRESULT *pResult);

public:
	afx_msg void OnDestroy();
	CButton m_checkReadOnly;
	afx_msg void OnBnClickedCheckReadOnly();
	int curr_show_quest_id;
};

#ifndef _DEBUG  // debug version in EditorView.cpp
inline CQuestEditorDoc* CQuestEditorView::GetDocument() const
   { return reinterpret_cast<CQuestEditorDoc*>(m_pDocument); }
#endif


extern CQuestEditorView* theEditor;