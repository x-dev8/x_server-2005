// GameBotView.h : CGameBotView 类的接口
//


#pragma once
#include "afxcmn.h"
#include "AddFrm.h"
#include "MessageInfo.h"
#include "MapStatic.h"
#include "afxwin.h"
#include "GameBotDoc.h"
#include "MapInfo.h"

#include <vector>
using namespace std;

class BaseInfo;
class ManInfo;
class PackInfo;
class SkillInfo;


class CGameBotView : public CFormView
{
protected: // 仅从序列化创建
	CGameBotView();
	DECLARE_DYNCREATE(CGameBotView)

public:
	enum{ IDD = IDD_ROBOT_FORM };

// 属性
public:
	CGameBotDoc* GetDocument() const;


private:
	ManInfo *m_pManInfo;
	PackInfo *m_pPackInfo;
	SkillInfo *m_pSkillInfo;
	vector<CDialog*> m_vecDialog;


public:
	MapInfo *m_pMapInfo;

public:	
	vector<BaseInfo*> m_vecBaseInfo;

	int m_nInfoIndex;

	int m_nBotID;

private:
	DWORD _TempSendPackNum;
	DWORD _TempRecvPackNum;
	DWORD _TempSendPackSize;
	DWORD _TempRecvPackSize;

private:
	void InitTabChildDialog();

public:
	void UpdateChatMessage(BaseRobot* pBot);
	void UpdateSystemMessageCount(BaseRobot* pBot);	
	void UpdataStatMsgInfo(BaseRobot* pBot);
	void ShowBigMap();

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CGameBotView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_ctlBotList;
public:
   // CTreeCtrl m_treeBotInfo;
    CAddFrm m_frmAdd;
	MessageInfo m_xMsgInfo;
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    int GetBotTypeByTxt(CString BotTypeTxt);
public:
    afx_msg void OnNMClickListBot(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDBCheckListBotCommond(NMHDR *pNMHDR, LRESULT *pResult);
public:
    virtual BOOL DestroyWindow();
public:
    afx_msg void OnNMRclickListBot(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReLogin();
	CTabCtrl m_Tab;
	CEdit m_SystemList;
	CEdit m_ChatList;
	CStatic m_staticSystem;
	CStatic m_staticChat;
	afx_msg void OnPaint();
	afx_msg void OnTcnSelchangeTabInfo(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_editContent;
	CButton m_buttonSend;
	afx_msg void OnBnClickedButtonSendChat();
	CStatic m_staticChat2;
	CButton m_Radio1;
	CButton m_Radio2;
	CButton m_Radio3;
	CButton m_Radio4;
	CButton m_Radio5;
	CButton m_Radio6;
	int m_RadioType;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();


	CEdit m_editTotalMsgCount;
	CEdit m_editTotalPosPackCount;
	CEdit m_editTotalPosMsgCount;
	CEdit m_editTotalEnemyPackCount;
	CEdit m_editBotTotalMsgCount;
	CEdit m_editBotPosPackCount;
	CEdit m_editBotPosMsgCount;
	CEdit m_editBotEnemyPackCount;
	CEdit m_editBotEnemyMsgCount;
	CEdit m_editTotalEnemyMsgCount;
	CEdit m_editPerSendCount;
	CEdit m_editPerSendSize;
	CEdit m_editPerRecvCount;
	CEdit m_editPerRecvSize;
	afx_msg void OnLvnItemchangedListBot(NMHDR *pNMHDR, LRESULT *pResult);// 左键点选消息
	afx_msg void OnAlllogin();
    afx_msg void OnFlyBackInHell(); // 
    afx_msg void OnAllBotOutline();
    afx_msg void OnSelectedOutline();
};
extern CGameBotView* GettheMainView();

#ifndef _DEBUG  // GameBotView.cpp 中的调试版本
inline CGameBotDoc* CGameBotView::GetDocument() const
   { return reinterpret_cast<CGameBotDoc*>(m_pDocument); }
#endif

