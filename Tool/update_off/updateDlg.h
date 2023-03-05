// updateDlg.h : header file
//

#pragma once
#include <vector>
#include "KbcButton.h"
#include <string>
#include <afxtempl.h>

#include "crc32.h"


using std::string;

/*
#include "httpdownload/TE_Socket.h"
#include "httpdownload/httpdownload.h"
#include "httpdownload/INetDownload.h"
*/
#include "ZipWrapper.h"
#include "vfs.h"
/*
#include "Pack/FolderFileList.h"
*/

using std::vector;
using Crypto::CCRC32;

#define DRAGGING	0x01	// dragging flag
// CupdateDlg dialog

#define WM_DRAW_PROGRESS  2008
#define WM_DRAW_TEXT  3000


//��������ķ�����IP��ַ
typedef struct tagAreaServerIpInfo
{
	_tstring strServerList;
	_tstring strServerOnlineInfo;
	std::vector<_tstring> DownLoadIPList;
}AREASERVERIPINFO;

struct VersionInfo
{
	std::string szCurVersion;
	std::string szNextVersion;
	std::string szPath;
	BOOL		bNeedPack;
};

struct progress_message
{
  int totallen;
  int downlen;
  int type;

};

struct tiptext
{
	CRect rect;
	CString text;
};


class CupdateDlg : public CDialog
{
// Construction
public:
	CupdateDlg(CWnd* pParent = NULL);	// standard constructor

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
	struct	BtnInfo
	{
		string	_szName;
		string	_szImg;
		RECT	_rc;
		string	_szTip;
		string	_szHref;	
	};
	CFont font;  CFont fontT;    
	Image *image;

	DWORD	m_dwFlags;		// flags
    POINT	m_pntMouse;		// Mouse position for dragging

	progress progressnow;
	progress progresstotal;  
	tiptext  textfile;
	
	CBrush m_brush;		//������ˢ
	
	TiXmlDocument	m_TiXmlDoc;	//����xml����д���ļ�
	TiXmlElement*	m_TiElemRoot;	//����root�ڵ� ������ø��� 


	CKbcButton btncancel;
CKbcButton btnclose;BtnInfo btninfo_close;
	typedef struct tagDownLoadFileInfo
	{
		tagDownLoadFileInfo()
		{
			bUseCompress = false;
			bVFSUnit = false;
			strSaveLocalFilePath="";
		};
		_tstring strHostFilePath;
		_tstring strLocalFilePath;
		_tstring strChangeTime;
		_tstring strFileName;
		_tstring strCRC;
		_tstring strPacketName;
		_tstring strSaveLocalFilePath;
		bool bUseCompress;
		bool bVFSUnit;
	}DOWNLOADFILEINFO;

	typedef std::vector<DOWNLOADFILEINFO> UpdateList;

	HANDLE hHandle;


// Dialog Data
	enum { IDD = IDD_UPDATE_DIALOG };
    void LoadXML(CString filename);
	
	bool static SetLocalVersion(const TCHAR* szVersion);   //���ñ��ذ汾
	static void UpdataFileToPacket(UpdateList& updatalist);   
    static UpdateList& GetUpdateFile(_tstring strVersionXML, _tstring strLocalPath,bool is_autopatch = true);       //������Ҫ���ص��ļ�
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT Message_DrawProgress(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT Message_DrawText(WPARAM wParam,LPARAM lParam);

	static bool ManualUpdateFile(const TCHAR* cFilePath,const TCHAR* cCurVersion);
	static DWORD WINAPI UpdateThreadProc(LPVOID lpParam);//���߳�

	afx_msg void OnClose();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton2();

	//��Ȿ�ذ汾���Ƿ���Ҫ����,�汾���Ƿ��ڲ������İ汾�ŷ�Χ��
	static bool CheckVersion(TCHAR* localversion,TCHAR* packversion);
	bool FindClientProcess(LPCTSTR name);
};
