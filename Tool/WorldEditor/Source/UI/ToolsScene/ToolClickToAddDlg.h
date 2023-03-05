/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolClick2AddDlg.h
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __TOOL_CLICK2ADD_DLG_H__
#define __TOOL_CLICK2ADD_DLG_H__
#include "afxwin.h"
#include "afxcmn.h"


class CToolClick2Add;
////////////////////////////////////////////////////////////////////////////////
class CToolClick2AddDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolClick2AddDlg)

public:
					CToolClick2AddDlg(CToolClick2AddDlg* pParent = NULL);   // standard constructor
	virtual			~CToolClick2AddDlg();

	// Dialog Data
	enum { IDD = IDD_DLG_Click2Add };

	typedef enum
	{
		SOUND_POINT_MODE = 0,
		NPC_MODE
	} EClick2AddToolMode;
	void			SetActive( bool isModify = false );
	void				RefreshClick2Add(CSoundPointEditRes* pt );

	void				UpdateLock( bool isLock );
	void				UpdateClick2AddList();
protected:
	CToolClick2Add*		GetToolClick2Add();

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolClick2AddDlg)
	virtual void		OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL	OnInitDialog();
	virtual void	OnOK(){};
	virtual void	OnCancel(){};
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CToolClick2AddDlg)
	afx_msg void OnEnKillfocusEdtClick2AddPoint();
	afx_msg void OnBnClickedChkPick();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedRadioSoundPoint();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CEdit				m_editClick2AddX;
	CEdit				m_editClick2AddY;
	CEdit				m_editClick2AddZ;
	CSpinButtonCtrl		m_spinClick2AddX;
	CSpinButtonCtrl		m_spinClick2AddY;
	CSpinButtonCtrl		m_spinClick2AddZ;
	CEdit				m_editIndex;
	CEdit				m_editName;

	CEdit				m_readonlyTargetIndex;
	CXTBrowseEdit		m_editMusic;

	CButton				m_isPickClick2Add;
	CListBox			m_Click2AddList;
	EClick2AddToolMode		m_eClick2AddToolMode;
public:
	afx_msg void OnBnClickedRadioNPC();
	afx_msg void OnLbnSelchangeListClick2add();
	afx_msg void OnEnKillfocusEdtClick2addName();
	afx_msg void OnEnKillfocusEdtSoundpoint();
	CEdit m_editValue0;
	afx_msg void OnEnKillfocusEdtClick2addValue0();
	CEdit m_editValue1;
	afx_msg void OnEnKillfocusEdtClick2addValue1();
	CSpinButtonCtrl m_spinValue0;
	CSpinButtonCtrl m_spinValue1;
};







#endif //__TOOL_CLICK2ADD_DLG_H__