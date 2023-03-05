// EditorView.h : interface of the CEditorView class
//


#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "xlistctrl/xlistctrl.h"
#include "xlistctrl/xlistctrl.h"
#include "application_config.h"
#include "MyTreeCtrl.h"
#include "EventTimeTable.h"

class CEditorView : public CFormView
{
protected: // create from serialization only
	CEditorView();
	DECLARE_DYNCREATE(CEditorView)

public:
	enum{ IDD = IDD_EDITOR };

// Attributes
public:
	CEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    void ControlBaseCalendarElement(BOOL IsOpen);
    void ControlBroadcastsElement(BOOL IsOpen);
    void ControlDayElement(BOOL IsOpen);
    void ControlRewardsElement(BOOL IsOpen);


    void ControlClearBaseEventElement();
    void ControlClearNpc();
    void ControlCleaTypeValue();
    void ControlCleaRewardType();
    void ControlClearBroadcastsElement();
    void ControlClearDayElement();
    void ControlClearPeriodType();
    void ControlClearMap();


    void ShowBaseEventElement(const Event* pEven);
    void ShowDayElement(const Event* pEven);
    void ShowRewardsElement(const Event* pEven);
    void ShowBroadcastsElement(const Event* pEven);
    
    void ShowMap(const Event* pEven);
    void ShowNpc(const Event* pEven);
    void ShowPeriodType(const Event* pEven);
    void ShowPeriodValue(const Event* pEven);

    void ShowEventInfo(const HTREEITEM &hItem);

    int GetMapView2Data();
    int GetNpcView2Data();
    
    void OnAddBroadcasts();
    void OnAddReward();
    void AddBroadcastsElement(Event::Broadcast &broadcast);
    void AddRewardElement(Event::Reward &reward);

    void InitEventName();
    void InitBroadcastListCtrl();
    void InitRewardListCtrl();
    void InitMonthDay();
    void InitWday();
    void InitMap();
    void InitNpc();
    void InitPeriodType();
    void InitRewardType();
    void InitItemStringArray();
    void InitNeedLevel();
    void InitQuality();

    void OnEditControlBroadcastsEnd(int Item,int SubItem);
    void OnEndControlRewardsEnd(int Item,int SubItem);

    bool IsNum(const char* string);

    void OnDeleteBroadcast();
    void OnDeleteReward();
    void OnDeleteEvent();
    bool ApplyEvent();
    int GetItemStringIndexByName(const std::string &name);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

    int SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle);
// Implementation
public:
	virtual ~CEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    MyTreeCtrl EventViewTree;

    CString ValueDescription;
    CString ValueName;
    CComboBox ValueQualty;
    INT ValueConunt;
    INT ValueDuration;
    CComboBox ValueNeedLevel;
    INT ValueCompleteId;
    float ValueMapPosY;
    float ValueMapPosX;
    CString ValueDurationDes;

    INT ValueYear;
    INT ValueMonth;
    INT ValueDay;
    INT ValueHour;
    INT ValueMinute;
    BOOL ValueHot;
    BOOL ValuePivot;
    INT ValueScriptId;
    int ValueItemId;

    CComboBox ComboControlMapId;
    CComboBox ComboControlNpcId;

    CComboBox ComboControlPeriodType;
    CComboBox ComboControlTypeValue;

    CXListCtrl* CurListCtrl;
    CXListCtrl ControlBroadcasts;
    CXListCtrl ControlRewards;

    CStringArray RewardStringArray;
    CStringArray ItemStringArray;
    int CurItem;
    int CurSubItem;

    afx_msg void OnTvnSelchangedEventTree(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCbnSelchangeComboPeriodtype();
    afx_msg void OnCbnEditchangeComboPeriodtype();
    afx_msg void OnNMDBLclkListBroadcasts(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMDBLclkListReward(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickListReward(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickListBroadcasts(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg LRESULT OnEditEnd(WPARAM, LPARAM);
    afx_msg void OnAddEvent();
    afx_msg void OnMsgDeletEvent();
    afx_msg void OnSaveEvent();
    afx_msg void OnNMDblclkEventTree(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnApplyEvent();
    afx_msg void OnAddBroadcastOrReward();
    afx_msg LRESULT OnSelectList(WPARAM m_nComboItem, LPARAM m_nSubComboItem);
};

#ifndef _DEBUG  // debug version in EditorView.cpp
inline CEditorDoc* CEditorView::GetDocument() const
   { return reinterpret_cast<CEditorDoc*>(m_pDocument); }
#endif

