#pragma once
#include "BaseInfo.h"
#include "afxcmn.h"
#include "afxwin.h"


// PackInfo dialog

class PackInfo : public CDialog, public BaseInfo
{
	DECLARE_DYNAMIC(PackInfo)

public:
	PackInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~PackInfo();

// Dialog Data
	enum { IDD = IDD_DIALOG_PACKINFO };

public:
	virtual void InitInformation();
	virtual void UpdateInformation(BaseRobot *pBot);

private:
	void ShowEquipInformation(BaseRobot *pBot);
	void ShowPackInformation(BaseRobot *pBot);

	int FindEmptyPackItemIndex(SCharItem *pItemBag);

	int GetListSelectItemIndex(CListCtrl& xList);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	BaseRobot *m_pBot;

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listEquip;
	CListCtrl m_listPack;
	CEdit m_editGold;
	CEdit m_editSilver;
	CEdit m_editCopper;
	CEdit m_editMoney;
	afx_msg void OnNMRclickListEquip(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListPack(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDebusEquip();
	afx_msg void OnUseItem();
	afx_msg void OnMoveItem();
	afx_msg void OnDeleteItem();
	afx_msg void OnDebusDress();
	CEdit m_editWeightMax;
	CEdit m_editWeightNow;
};
