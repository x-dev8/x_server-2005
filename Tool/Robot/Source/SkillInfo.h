#pragma once

#include "../Resource/resource.h"
#include "BaseInfo.h"
#include "afxcmn.h"
#include "afxwin.h"

// SkillInfo dialog

class SkillInfo : public CDialog, public BaseInfo
{
	DECLARE_DYNAMIC(SkillInfo)

public:
	SkillInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~SkillInfo();

// Dialog Data
	enum { IDD = IDD_DIALOG_SKILL };

public:
	virtual void InitInformation();
	virtual void UpdateInformation(BaseRobot *pBot);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listProfession;
	CListCtrl m_listNormal;
	CListCtrl m_listProduce;
	CEdit m_editSkillExp;
};
