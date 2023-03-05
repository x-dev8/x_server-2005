#pragma once
#include "KbcButton.h"
#include <string>
#include <afxtempl.h>
using std::string;
// CDlgAreaSelect dialog
#define DRAGGING	0x01	// dragging flag


/*

动态页面处理方式:
//1.加载.LoadXML(...)加载xml配置文件

//2.创建.tinyxml解析标鉴,以button为例:
<button>
<style name="ok">
<image file="LauncherUI\btn_ok.bmp" />
<rect value="621, 448, 81, 81" />
<tip value="进入游戏" />
</style>
<style name="regedit">
<image file="LauncherUI\btn_regedit.bmp" />
<rect value="220, 533, 95, 32" />
<tip value="进入账号注册页面" />
<href value="http://passport.cnhone.com/register" />
</style>
</button>
每读到一个style就创建一个按钮,id为btnsruct_ID=IDC_BUTTON_1+btnptr.GetCount(),其值范围为IDC_BUTTON_1-IDC_BUTTON_X中间,btnptr用于管理所有按钮指针
对于除button以外的控件没有采用动态创建，所以btnptr不保存它们的信息

//3.事件响应.ON_CONTROL_RANGE负责处理id为IDC_BUTTON_1-IDC_BUTTON_X中间所有BN_CLICKED类型消息.如果按钮是响应网页事件类型的
通过ShellExecute(NULL, "open", "IEXPLORE", (LPCSTR)node->info->_szHref.c_str(), NULL,SW_SHOWMAXIMIZED); 打开网页.
否则,根据BtnInfo._szName0字段内容区别处理.

//4.注意:创建其它控件的ID建议不要占用IDC_BUTTON_1-IDC_BUTTON_X
*/

#define  IDC_BUTTON_1  3000
#define  IDC_BUTTON_X     4000


class CDlgAreaSelect : public CDialog
{
	DECLARE_DYNAMIC(CDlgAreaSelect)
	
	struct	BtnInfo
	{
		string	_szName;
		string	_szImg;
		RECT	_rc;
		string	_szTip;
		string	_szHref;
		string  _port;
	};
	struct btnstruct
	{
		CKbcButton *btn;
		BtnInfo *info;

	};

	
public:
	CDlgAreaSelect(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAreaSelect();
	void LoadXML(CString filename);
	
	
	
	
// Dialog Data
	enum { IDD = IDD_DLG_AREA };
	

	int _nAreaIndex;

	CPtrArray btnptr;
	
	void AddButton(BtnInfo *info,int ctrlid=0);

private:
	int btnsruct_ID;//每次插入一个按钮的ID，插入后将其自增
	Image *image;
	CBrush m_brush;		//背景画刷
	CKbcButton	_btnOK;
	CKbcButton	_btnCancel;
	BtnInfo _btnOk_info;
	BtnInfo _btnCancel_info;
	DWORD	m_dwFlags;		// flags
	POINT	m_pntMouse;		// Mouse position for dragging

	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


	afx_msg void OnBnClickedSaOk();
	afx_msg void OnBnClickedSaCancel(); 
	
	
	afx_msg void OnButtonClicked(UINT nID);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
