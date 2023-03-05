// QuestEditDlg.h : ͷ�ļ�
//
#pragma once
#include "Define.h"
#include "afxwin.h"

class QuestFind;
class DropItemDialog;

// CQuestEditDlg �Ի���
class CQuestEditDlg : public CDialog
{
// ����
public:
	CQuestEditDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QUESTEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	void InitInformation();		
	void InitSetInfo();
	void InitListCtrl(bool bInsert);
	void InitPropertyList();		//��ʼ���б�
	void ReadSetInfoFile();		//��ȡ����

	void SaveSetInfoFile();		//��������
	void SaveSetInfoFile(const char *pszSecion, char *pszKey, vector<SetInfo> &vecSetInfo);

	void ShowQuestVersion();

	bool AddQuestInList(int nIndex, int &nCount, SQuest *xpQuest);
	void ShowQuestInformation(SQuest &xQuest);			//��ʾ������Ϣ
	void ClearQuestInformation();
	void ShowRequirementList(CXListCtrl &xRequirementList, vector<SQuestRequirement> &vecRequirement);	//��ʾ��������
	void ShowRewardList(vector<SQuestReward> &vecReward);					//��ʾ������

	void AddQuestRequiremenetList(CXListCtrl &xRequirementList, CStringArray &xStringArray);	//���һ������Ҫ��
	void AddQuestRewardList(CXListCtrl &xRewardList, CStringArray &xStringArray);	//���һ��������
	void GetQuestRequirement(CXListCtrl &xRequirementList, SQuest &xQuest, bool bCommit);	//�������Ҫ��
	void GetQuestReward(CXListCtrl &xRewardList, SQuest &xQuest);		//��ý���

	bool SubString(string &strDest,string &strSub,string strSign);
	int SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle);
	int GetListCtrlCurSel(CListCtrl &xList);

	int GetStringArrayIndex(CStringArray &xArray, CString &strValue);

	void SetEditText(CEdit& xEdit, char *pszFormat, ...);	
	int GetEditInt(CEdit& xEdit, int nDef);
	void InsertItemText(CListCtrl &xList, int nItem, char *pszFormat, ...);
	void SetListItemText(CListCtrl &xList, int nItem, int nSubItem, char *pszFormat, ...);
	int GetListItemInt(CListCtrl &xList,int nItem, int nSubItem,int nDef);

	bool IsIDNumber(const char *pszID, int nLength);

	void ClickList(CListCtrl &xList, NMHDR *pNMHDR);

	const char* GetSetInfoName(vector<SetInfo> &vecSetInfo, int nValue, char* pszDef = "");	
	int GetSetInfoValue(vector<SetInfo> &vecSetInfo, string strName);	

	/////////////////////////////////////////////////////////////////////////////////
	int FindQuest(CString strValue, int nType, FindInfo *pFindInfo = NULL);
	void ShowFindQuest(int nId);
	void ShowNextFindQuest();
	///////////////////////////////////////////////////////////////////
	void SetListItemCanEdit();


	void LoadResourceFiles();

	bool IsKeyDown(UINT nKey = VK_CONTROL);

private:	
	
	typedef void (CQuestEditDlg::*_FindFun)(CString strValue, FindInfo *pFindInfo);

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

	
	void ShowFindDialog();

	void AddListItem();
	void DeleteListItem();
	bool DeleteQuestFile(int nId);

	string GetFileFullPath(int nId, const char *pszPath, const char* pExt);

	void SetWindowTop();

	void SetCurrentWorkDir();
	void CheckFilePathExist();

	void ShowDropItemDialog();

	void SetListItemColor(CXListCtrl &xList, int nItem, int nSubItem, COLORREF dwColor);
	void SetListItemBGroundColor(CXListCtrl &xList, int nItem, int nSubItem, COLORREF dwColor);

	void SetStringId(int nQuestId);

public:
	char m_szFilePath[_MAX_PATH];					//�����ļ�·��
	vector<SetInfo> m_xSetInfo[Enum_End];			//�趨��Ϣ
	CStringArray m_xStringArray[Enum_End];			//�ַ�����Ϣ
	
	char m_szItemFile[_MAX_PATH];
	char m_szMapFile[_MAX_PATH];
	char m_szMonsterFile[_MAX_PATH];
	char m_szNpcFile[_MAX_PATH];
	char m_szReputeFile[_MAX_PATH];
	char m_szStringFile[_MAX_PATH];

	CString m_strDropItemFile;


	MonsterAndDrop m_xMonsterDrop;

	DropTaskItem m_xDropTaskItem;

private:
	SQuest m_xQuest;

	QuestInfo m_xQuestManager;	//���������
	DropItemDialog *m_pxDropItemDialog;

	CXListCtrl *m_pxListCtrl;		//���浱ǰ������listctrl
	CString m_strValue;				//���浱ʱ��ѡ��
	int m_nItem;
	int m_nSubItem;

	string m_strQuestFile;			//��ǰ���ص������ļ�

	CMenu m_xMenu;

	CImageList m_xImageList;

	QuestFind *m_pxQuestFind;
	vector<int> m_vecFindQuestId;

	int m_nShowFindId;

	bool m_bWindowsTop;

	static _FindFun FindFun[Enum_QuestMax];//���Һ�������
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
public:
	CXListCtrl m_listProperty;
	CXListCtrl m_listReward;
	CXListCtrl m_listPreRequiement;
	CXListCtrl m_listPostRequiement;
	MyTreeCtrl m_xTreeQuest;
	afx_msg void OnLbnDblclkListQuest();
	afx_msg LRESULT OnComboSelection(WPARAM, LPARAM);
	afx_msg LRESULT OnCheckbox(WPARAM, LPARAM);
	afx_msg LRESULT OnEditEnd(WPARAM, LPARAM);
	afx_msg void OnNMClickListReward(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPreRequiement(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPostRequiement(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListProprety(NMHDR *pNMHDR, LRESULT *pResult);	

	DECLARE_MESSAGE_MAP()
	
	
	afx_msg void OnFileLoadQuestFile();
	afx_msg void OnFileSaveQuestFile();
	afx_msg void OnFileExit();
	afx_msg void OnFileSaveAt();
	afx_msg void OnFileFind();
	afx_msg void OnNMClickTreeItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnTvnSelchangedTreeQuest(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CStatic m_staticPre;
	CStatic m_staticPost;
	CStatic m_staticReward;
	CStatic m_staticSave;
	afx_msg void OnNMDClickListPostRequiement(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListPostRequeiment(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelete();
	CButton m_checkBatch;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStringChange();
	afx_msg void OnNpcChange();
};


