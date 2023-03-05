// IconEditorDlg.h : header file
//

#pragma once
#include "afxcmn.h"

#include "CxImage\ximage.h"
#include "afxwin.h"
#include "atlimage.h"
#include "Tinyxml\tinyxml.h"
#include "XListCtrl/XListCtrl.h"

#define Default_Width 64
#define Default_Height 64

struct PositionInfo
{
	PositionInfo():nRow(-1), nColumn(-1){}
	
	void Clear() { nRow = -1; nColumn = -1; }
	
	int nRow;
	int nColumn;

	PositionInfo& operator = (const PositionInfo &xPosition)
	{
		if (this != &xPosition)
		{
			nRow = xPosition.nRow;
			nColumn = xPosition.nColumn;
		}

		return *this;
	}

	friend bool operator == (const PositionInfo &xLeft, const PositionInfo &xRight)
	{
		return (xLeft.nRow == xRight.nRow && xLeft.nColumn == xRight.nColumn);
	}

};

struct IconInfo
{
	IconInfo(): nID(-1), strName(""), strImage(""), nWidth(Default_Width), nHeight(Default_Height), bVis("false") {}

	int nID;
	CString strName;
	CString strImage;
	int nWidth;
	int nHeight;
	PositionInfo xPosition;

	/////技能icon里面的属性
	int nType;
	int nProfession;
	int nIndex;
	CString bVis;
	POINT xPoint;

	friend bool operator == (IconInfo &xIcon, const int &nID)
	{
		return (xIcon.nID == nID);
	}

	IconInfo & operator = (const IconInfo &xIcon)
	{
		if (this != &xIcon)
		{
			nID = xIcon.nID;
			strName = xIcon.strName;
			strImage = xIcon.strImage;
			nWidth = xIcon.nWidth;
			nHeight = xIcon.nHeight;

			xPosition = xIcon.xPosition;
		}

		return *this;
	}

	friend bool operator < (const IconInfo &xLeft, const IconInfo &xRight)
	{
		return (xLeft.nID < xRight.nID);
	}
};

struct ImageIndex
{
	ImageIndex(): nIndex(-1){}

	CString name;
	PositionInfo xPostion;	//icon位置
	int nIndex;			//索引

	friend bool operator == (const ImageIndex &xLeft, const ImageIndex &xRight)
	{
		return (xLeft.name == xRight.name && xLeft.xPostion == xRight.xPostion);
	}
};

struct ImageFile 
{
	CString name;

	int width;		//icon 宽
	int height;		//长
	CxImage *pimage;

	ImageFile() : pimage(NULL) { }
};


typedef vector<ImageFile>::iterator imagefileiter;
typedef vector<IconInfo>::iterator iconiter;

// CIconEditorDlg dialog
class CIconEditorDlg : public CDialog
{
	// Construction
public:
	CIconEditorDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_ICONEDITOR_DIALOG };


public:
	void InitInformation();

	void ReadSetConfigFile();			//读取设定

	bool LoadImageFile(const char* pszFile);
	void LoadAllImageFile(const char* pszFile);	//查找所有的文件

	void ShowImage();
	void ShowSelectArea(PositionInfo &xPosition, int nWidth, int nHeight);

	void ClearCXImagePoint();

	void SaveSetConfigFile(char *pszKey, char *pszValue);

	bool GetIconPosition(CPoint &xPoint, PositionInfo &xPosition);

	void InsertInIconList(int nIndex, IconInfo &xIcon, bool bEdit);
	void InsertInSkillIcon(int nProfession, int nSkillType);
	IconInfo* FindIconInfo(int nID);
	int FindIconListIndex(int nID);

	void ShowIconInList(int nIndex);
	bool EditIconInfo(bool bAdd);

	void SetRowAndColumnCount(CxImage *pImage);

	void ShowIconInfo(IconInfo &xIcon);
	void ShowIconCount();

	CString GetImageFileName(const char* pszFilePath);

	bool LoadItemXmlFile(const char* pszFile);
	bool LoadSkillXmlFile(const char* pszFile);
	bool SaveItemXmlFile(const char* pszFile);
	bool SaveSkillXmlFile(const char* pszFile);

	void ReadSkillIcon(TiXmlElement* pElement, int nProfession, int nType);
	void SaveSkillIncon(TiXmlElement* pElement, int nProfession, int nType, CString strSkillBgd);

	void SaveXmlFileWhenClose();

	/////////////////////////////////////////////////////////////////////////////////////////////
	void InitIconImageList(CxImage *pxImage, CString strFile);
	

	bool KeyMoveIcon(WPARAM wParam);

	void UpdateImageFile(CString name);

	ImageFile* GetImageFileByName(CString name);
	int FindImageListIndex(ImageIndex &xImageIndex);

	bool IsAlreadyLoad(CString name);
public:
	int SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle);
	int GetListItemCurSel(CListCtrl &xList);

	void SetEditText(CEdit& xEdit, char *pszFormat, ...);	
	int GetEditInt(CEdit& xEdit, int nDef);
	void InsertItemText(CListCtrl &xList, int nItem, char *pszFormat, ...);
	void SetListItemText(CListCtrl &xList, int nItem, int nSubItem, char *pszFormat, ...);
	int GetListItemInt(CListCtrl &xList,int nItem, int nSubItem,int nDef);

	void ClearListSelectItem(CListCtrl &xList);
	void SetListSelectItem(CListCtrl &xList, int nIndex);

private:
	int GetProfession(const char *szProfession);
	void EnableRadio(BOOL bEnable);
    void ShowImagePath( CString& strImageFile );


public:
	vector<IconInfo> m_vecIcon;
	vector<ImageFile> m_vecImageFile;
	vector<ImageIndex> m_vecImageIndex;
	CImageList m_xImagelist;		
	CxImage *m_pxImage; //当前CxImage
	CString m_strImageFileName;	//当前Image文件

	CPoint m_xPoint;
	CRect m_xRect;

	char m_szFilePath[_MAX_PATH];		//设定档路径

	int m_nRowCount;
	int m_nColumnCount;
	PositionInfo m_xPositionInfo;

	bool m_bChange;
	bool m_bCanSave;

	int m_nStartIconCount;

	int m_nIconWidth;
	int m_nIconHeight;


	int m_nImageIndex;			//当前已经加载的icon 的索引
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listImageFile;
	afx_msg void OnBnClickedButtonFile();
	CEdit m_editImageFilePath;
	afx_msg void OnNMClickListImageFile(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_staticImage;
	afx_msg void OnBnClickedButtonXmlFile();
	CEdit m_editXmlFile;
	afx_msg void OnDestroy();
	CEdit m_editRelaPath;
	CEdit m_editItemID;
	CEdit m_editItemName;
	CEdit m_editImageName;
	CEdit m_editRow;
	CEdit m_editColumn;
	CEdit m_editFirstID;
	CEdit m_editEndID;
	afx_msg void OnStnClickedStaticImage();
	CStatic m_staticInfo;
	afx_msg void OnBnClickedButtonAdd();
	CXListCtrl m_listIcon;
	afx_msg void OnBnClickedButtonLoadXml();
	afx_msg void OnNMClickListIconInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSaveXml();
	CButton m_buttonSaveXml;
	afx_msg void OnBnClickedButtonEditIcon();
	afx_msg void OnBnClickedOk();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedButtonBatchAdd();
	CStatic m_staticCount;
	afx_msg void OnNMRclickListIcon(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelete();
	afx_msg LRESULT OnEditEnd(WPARAM, LPARAM);
	afx_msg void OnLvnItemchangedListIcon(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_buttonEdit;
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedButtonBatchDelete();
	afx_msg void OnBnClickedButtonOpenXml();
	int m_RadioType;
	int m_RadioProfession;	
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	CEdit m_editSkillBgd;
	int m_RadioSkillType;
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnEnChangeEditIconWidth();
	CEdit m_editWidth;
	CEdit m_editHeight;
	afx_msg void OnEnChangeEditIconHeight();
	int m_RadioLoad;
	afx_msg void OnBnClickedRadio16();
	afx_msg void OnBnClickedRadio17();
    CButton m_radioItem;
    afx_msg void OnBnClickedRadio18();
};

enum SkillType
{
	Enum_Profession = 0,
	Enum_Common,
	Enum_Produce,

	Enum_End,
};

const static char* s_pszType[] = 
{
	"Profession",	//枪
	"Common",	//阴阳
	"Produce",		//舞
};


enum EArms
{ // 兵种
	EA_Spear,  // 枪兵
	EA_Staff,  // 杖兵
	EA_Fan,    // 舞兵
	EA_Sword,  // 剑兵
	EA_Bow,    // 弓兵
	ER_Hammer, // 锤兵
	EA_ArmsMaxSize,
};

const static char* s_pszProfession[] = 
{
	"Spear",	//枪
	"Staff",	//阴阳
	"Fan",		//舞
	"Sword",	//刀
	"Bow",		//弓		
	"Hammer",
};