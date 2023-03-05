// NpcEditDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include <NpcInfo.h>
#include "afxwin.h"
#include "PositionInfo.h"
#include "./Source/UI/ToolsWnd/CEditableListBox/EditableListBox.h"

#define ELAPSE "Elapse"
#define ACTION "Action"
#define TALK   "Talk"

#define WM_MY_MESSAGE WM_USER+1000

enum Filter
{
	FILTER_MAPID = 0,  //地图过滤
	FILTER_NAME  = 1,  //名称过滤
	FILTER_NONE  = 2,  //不过滤
};

// CNpcEditDlg dialog
class CNpcEditDlg : public CDialog
{
// Construction
public:
	CNpcEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NPCEDIT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQueryfile();
	afx_msg void OnBnClickedInsert();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);

public:
	void InitTreeControlData(Filter eumValue,const char* pszValue = NULL);
	void InitTreeControlData(HTREEITEM hSubItem,Filter eumValue,int nMapId,const char *pszNpcName /*= NULL*/);                                 //初始化属性控件数据

	void ClearTalkProtery();
	void ClearActionProtery();
	void ClearElpaseProtery();
	void ClearNpcProtery();

	bool GetNpcProtery(NpcInfo::Npc &npc);                      //获得Npc属性
	bool SetNpcProtery(NpcInfo::Npc &npc);

	bool GetNpcFightData(NpcInfo::Npc &npc);
	bool SetNpcFightData(const NpcInfo::Npc &npc);
	
	bool GetElpaseTime(NpcInfo::NpcActionData &Elpase);         //从控件中获得Elpase属性
	bool SetElpaseTime(NpcInfo::NpcActionData &Elpase);

	bool GetActionProtery(NpcInfo::ActionData &actionData);     //获得Action属性
	bool SetActionProtery(NpcInfo::ActionData &actionData);

	bool GetTalkProtery(NpcInfo::TalkData &talk);               //获得谈话属性
	bool SetTalkProtery(NpcInfo::TalkData &talk);

	bool SetMaxNpcInfo();

	const char* ParseString(CString &strData);                  //分析字符串
	bool SaveConfig(const char *pszPath);                       //获得保存的文件
    bool SavePositionConfig(const char *pszPath);               //保存Position

	NpcInfo::NpcActionData* GetNpcActionData(int nNpcID,int nElapseID);
	NpcInfo::ActionData*    GetActionData(int nNpcID,int nElapseID,CString &cAnimStr);
	NpcInfo::TalkData*      GetTalkData(int nNpcID,int nElapseID,int nStringID);

	//有效性检测
	bool IsValidActionData(int nNpcID,int nElapseID,NpcInfo::ActionData &Data,char *pszError,bool bUpdate = false,NpcInfo::ActionData *DataNew = NULL);    //ActionData数据是否正确
	bool IsValidTalkData(int nNpcID,int nElapseID,NpcInfo::TalkData &Data,char *pszError,bool bUpdate = false,NpcInfo::TalkData *DataNew = NULL);        //TalkData数据是否正确

	bool IsValidElpaseData(int nNpcID,char *pszError);      //ElapseData数据是否正确

    inline bool IsNpcNode(CString &cText);     //是否为Npc节点
	inline bool IsElapseNode(CString &cText);  //是否为Elapse节点
	inline bool IsActionNode(CString &cText);  //是否为Action节点
	inline bool IsTalkNode(CString &cText);    //是否为Talk节点
    inline bool IsMapNode(CString &cText);     //是否为Map节点

	inline bool IsActionsNode(CString &cText);	//是否为Action节点
	inline bool IsRequireNode(CString &cText);
	inline bool IsEventNode(CString &cText);
	inline bool IsEventTalkNode(CString &cText);
	inline bool IsEventAnimNode(CString &cText);
	inline bool IsEventFaceToNode(CString &cText);
public:
	void InitGrapicsData();
	bool InitComboxData(CString strData/*const char *pszString*/,const char *pszKeyWord,const char *pszAttribute,CComboBox* comBox);
	bool InitComboxDataType( CComboBox* comBox, int maxID );
	bool InitComboxNpcType( CComboBox* comBox );
	void SetRequiresEnabled( BOOL bValue );
	void ClearRequiresValue();
	void ExpandNode(DWORD_PTR data);
	void UpdateActionsToNpc();
	void SetTipInfo(const char* pszTip);
private:
	CTreeCtrl m_TreeCtrl;  //属性列表

public:
//	afx_msg void OnBnClickedLoadxml();
	afx_msg void OnBnClickedNpcupdate();
//	afx_msg void OnBnClickedNpcsave();
	afx_msg void OnBnClickedTalkupdate();
	afx_msg void OnBnClickedTalkinsert();
	afx_msg void OnBnClickedActionupdate();
	afx_msg void OnBnClickedActioninsert();
	afx_msg void OnBnClickedElapinsert();
	afx_msg void OnBnClickedElapupdate();
	int m_mapID;
	float m_fPosX;
	float m_fPosY;
	afx_msg void OnSavexml();
	afx_msg void OnBnClickedAddpp();
	afx_msg void OnBnClickedDelpp();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnOK();
	afx_msg void OnCancel();
	afx_msg LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	CString m_strNote;

public:
	bool InitArrayData(CString strData,const char *pszKeyWord,const char *pszAttribute,CStringArray& arrayStr);

	void     SetNpcId(int npcId){m_NpcID = npcId;}
	void     InitNpcData(int npcId);

	void	InitNpcActions(int npcId);
	void	RefreshNpcActionUI();
	void	ClearNpcActionUI();		//重置npcaction界面等待输入
	void	DeleteNpcActions();
	bool	ValidateRequire();	//检查数据填写是否正确
	bool	ValidateEvent();
	void	DeleteOneAction(Action* action);

private:
	int  m_NpcID;
    bool bIsSetScroll;
    int m_cursel ;

	std::vector<Action*> m_ActSetPtr;
		 
public:
	afx_msg void OnBnClickedNpcmodify();
    afx_msg void OnNpcMenuUpdate();
    afx_msg void OnChangeNpcMenuStringId();
    CEdit m_NpcMenuStringID;    // NpcMenu字串ID
    CEditableListBox m_NpcMenuList;
    void OnInsertNewItem();
    void OnDelNpcMenu();
    CEdit m_Act;
    afx_msg void OnClickActScript();
	afx_msg void OnCbnSelchangeComrtype();
	afx_msg void OnCbnSelchangeCometype();
	afx_msg void OnBnClickedBnactionAdd();
	afx_msg void OnBnClickedBnactionDelete();
	CTreeCtrl mEventActionTree;
	afx_msg void OnTvnSelchangedTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBnrequireInsert();
	afx_msg void OnBnClickedBneventInsert();
	afx_msg void OnBnClickedBnrequireModify();
	afx_msg void OnBnClickedBneventModify();
	afx_msg void OnBnClickedBtnFightUpdate();
};