#pragma once
#include "tinyxml/tinyxml.h"
#include "browser/browser.h"
#include "tstring.h"
#include <string>
#include <afxtempl.h>
#include "KbcButton.h"
#include "updateDlg.h"


using namespace std;

struct btnstruct
{
	CKbcButton *btn;
	BtnInfo *info;

};
#define  IDC_BUTTON_1  3000
#define  IDC_BUTTON_X     4000
// CNewBackDlg dialog

class CNewBackDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewBackDlg)

	vector<string> vec_ServerlistAddr;
 	string	_PathMainApp;
	bool bNeedDownList;
	
	bool bNeedUpdate;
	bool bSelectArea;
	
	CupdateDlg cUpdate;
	
	struct progress
	{
		struct progress()
		{
			image=NULL;
			rect.SetRect(0,0,0,0);
			percent=0;
		};
		Image *image;
		int percent;
		CRect rect;
	};

	struct Fontinfo
	{
		COLORREF crColor;
		int size;
		CRect rect;
		CFont font; 
		CString text;
	};

	Fontinfo _NewVer;
	Fontinfo _LocVer;
	Fontinfo  textfile;
	Fontinfo  needupdate;
	progress progressnow;
	progress progresstotal;


	void RunMain();
	void LoadXML(CString filename); //界面配置文件
	void CNewBackDlg::Load_update_TipXML(CString filename); //下载过程中输出的提示字符串
public:
	CNewBackDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewBackDlg();

// Dialog Data
	enum { IDD = IDD_NEW_BACK_DLG };
	TiXmlDocument	m_TiXmlDoc;	//保存xml用于写入文件
	TiXmlElement*	m_TiElemRoot;	//保存root节点 这个不用更改 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	void OnButtonClicked(UINT nID);
	afx_msg LRESULT Message_DrawProgress(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Message_DrawText(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Message_UpdateFinish(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Message_GetVer(WPARAM wParam,LPARAM lParam);

	
	void AddFont(TiXmlElement* lpColor,Fontinfo &info);
	void AddButton(BtnInfo *info,int ctrlid=0);
	CBrush m_brush;		//背景画刷 
	
	 CPtrArray btnptr;
	int btnsruct_ID;//每次插入一个按钮的ID，插入后将其自增
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	bool FindClientProcess(LPCTSTR name);
};
