/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:17
	filename: 	e:\UIEditor\UIObjectDlg.h
	file path:	e:\UIEditor
	file base:	UIObjectDlg
	file ext:	h
	author:		WitSun
	
	purpose:	UIObjectDlg
*********************************************************************/
#pragma once
#include "afxcmn.h"
#include <vector>
#include "MeUi\ControlData.h"
//#include "Control.h"
#include "BaseControl.h"
#include "FrameControl.h"
#include "ButtonControl.h"
#include "CheckBoxControl.h"
#include "EditControl.h"
#include "TextControl.h"
#include "ListControl.h"
#include "ListImgControl.h"
#include "ScrollBarExControl.h"
#include "ComboBoxControl.h"
#include "PictureControl.h"
#include "ProgressControl.h"
#include "TabControl.h"
#include "ListExControl.h"
#include "TreeControl.h"

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

// CUIObjectDlg 对话框

class CUIObjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CUIObjectDlg)

public:
	enum E_ObjectKinds
	{
		ObjectKind_Dialog = 0
		,ObjectKind_Picture

		,ObjectKind_Max
	};

	struct S_ObjectKinds
	{
		S_ObjectKinds()
		{
			hItem = NULL;
			memset( szName,0 ,sizeof(szName) );
			pControl = NULL;
		}
		HTREEITEM	hItem;
		char		szName[MAX_PATH];
		CBaseControl* pControl;
	};

public:
	bool	AddPictuer( const char* szPicName );
	void	ClearPic();
	bool	RemoveSelPic();
	UINT	GetPictureCount(){ return (UINT)m_vtPictures.size(); }
	char*	GetPicture( int n ){ return m_vtPictures[n].szName; }

	void	SetDiglogData( const S_FrameData* pFrameData );

	bool	AddControl( const E_ControlType enType, int nX=0, int nY=0 );
	bool	AddControl( const S_BaseData* pData );
	bool	RemoveSelControl();
	void	ClearControl();
	void	Clear();

	void	Copy();
	void	Paste();
	void	Cut();
	bool	TestDialog( char* szResultString );

	void	UpdateDialogName();
	bool	UpdateControlName();

	bool	ShowSelItem( void* pData );

private:
	void	DBClickDialog( HTREEITEM hItem );
	void	DBClickControl( HTREEITEM hItem );
	void	DBClickPic( HTREEITEM hItem );

	CBaseControl* NewControl( const int enType );
	void	ReleaseCopyControl();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	BOOL			m_bInit;
	S_ObjectKinds	m_stObjectKinds[ObjectKind_Max];
	vector<S_ObjectKinds>	m_vtPictures;
	CBaseControl* m_pCopyControl;

public:
	CTreeCtrl m_treeObject;
	CFrameControl* m_pstDialog;
	vector<S_ObjectKinds>	m_vtControls;
	CBaseControl* m_pstCurControl;

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMDblclkTreeUiObject(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();

public:
	CUIObjectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUIObjectDlg();
	enum { IDD = IDD_DIALOG_UI_OBJECT };
	afx_msg void OnTvnKeydownTreeUiObject(NMHDR *pNMHDR, LRESULT *pResult);
};

extern CUIObjectDlg	theUIObjectDlg;
