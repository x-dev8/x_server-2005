#pragma once
#include "KbcButton.h"
#include <string>
#include <afxtempl.h>
using std::string;
// CDlgAreaSelect dialog
#define DRAGGING	0x01	// dragging flag


/*

��̬ҳ�洦��ʽ:
//1.����.LoadXML(...)����xml�����ļ�

//2.����.tinyxml�������,��buttonΪ��:
<button>
<style name="ok">
<image file="LauncherUI\btn_ok.bmp" />
<rect value="621, 448, 81, 81" />
<tip value="������Ϸ" />
</style>
<style name="regedit">
<image file="LauncherUI\btn_regedit.bmp" />
<rect value="220, 533, 95, 32" />
<tip value="�����˺�ע��ҳ��" />
<href value="http://passport.cnhone.com/register" />
</style>
</button>
ÿ����һ��style�ʹ���һ����ť,idΪbtnsruct_ID=IDC_BUTTON_1+btnptr.GetCount(),��ֵ��ΧΪIDC_BUTTON_1-IDC_BUTTON_X�м�,btnptr���ڹ������а�ťָ��
���ڳ�button����Ŀؼ�û�в��ö�̬����������btnptr���������ǵ���Ϣ

//3.�¼���Ӧ.ON_CONTROL_RANGE������idΪIDC_BUTTON_1-IDC_BUTTON_X�м�����BN_CLICKED������Ϣ.�����ť����Ӧ��ҳ�¼����͵�
ͨ��ShellExecute(NULL, "open", "IEXPLORE", (LPCSTR)node->info->_szHref.c_str(), NULL,SW_SHOWMAXIMIZED); ����ҳ.
����,����BtnInfo._szName0�ֶ�����������.

//4.ע��:���������ؼ���ID���鲻Ҫռ��IDC_BUTTON_1-IDC_BUTTON_X
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
	int btnsruct_ID;//ÿ�β���һ����ť��ID�������������
	Image *image;
	CBrush m_brush;		//������ˢ
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
