#pragma once
#include "afxwin.h"

#include <vector>

// PositionFind dialog

class PositionFind : public CDialog
{
	DECLARE_DYNAMIC(PositionFind)

public:
	PositionFind(CWnd* pParent = NULL);   // standard constructor
	virtual ~PositionFind();


private:
	int m_nType;
private:
	void InitInformation();

private:
	struct FindInfo
	{
		int id;
		std::string name;
	};
	std::vector<FindInfo> m_vecFind;

// Dialog Data
	enum { IDD = IDD_DIALOG_POSITION };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listPosition;
	CEdit m_editName;
	afx_msg void OnEnChangeEditName();
	afx_msg void OnLbnDblclkListPosition();
	int m_RadioType;
	afx_msg void OnBnClickedRadioPosition();
	afx_msg void OnBnClickedRadioMonster();
	afx_msg void OnBnClickedRadioItem();
	afx_msg void OnLbnSelchangeListPosition();
	CEdit m_editId;
};
