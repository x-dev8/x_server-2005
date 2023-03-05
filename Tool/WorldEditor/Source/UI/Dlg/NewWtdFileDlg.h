/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NewWtdFileDlg.h
* Date: 	01/24/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_DLG_NEWWTDFILEDLG_H__
#define _UI_DLG_NEWWTDFILEDLG_H__

//class CImage;
////////////////////////////////////////////////////////////////////////////////
// CNewWtdFileDlg dialog
class CNewWtdFileDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewWtdFileDlg)

public:
						CNewWtdFileDlg(CWnd* pParent = NULL);   // standard constructor
	virtual				~CNewWtdFileDlg();

	bool				HasHeightmap()	{ return m_hasHeightmap; };
	CString&			GetTileName( ) ;
	flt32				GetHeight() const;
	flt32				GetHeightMapUnit() const;
	const CImage*		GetHeightmap() const;
	const char*			GetBaseTexture() const;
	uInt32				GetTileRow() const { return m_tileRow; }
	uInt32				GetTileHeight() const { return m_tileColumn; }

	void				SetCurrPath(const TCHAR* pPath);
	
	// Dialog Data
	enum { IDD = IDD_DLG_NEW_WTD };

protected:
	virtual void		DoDataExchange( CDataExchange* pDX );    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK();

	afx_msg void		OnBnClickedCkHeightmap();
	DECLARE_MESSAGE_MAP()
protected:
	void				SetHasHeightmap( bool hasHeightmap = true );

protected:
	CEdit				m_editTileName;
	CEdit				m_editTileRow;
	CEdit				m_editTileColumn;
	CButton				m_btnHeightmap;
	CEdit				m_editHeight;
	CEdit				m_editHeightUnit;	// 高度图单位落差
	CXTBrowseEdit		m_editHeightmap;
	CXTBrowseEdit		m_editTexture;
	
	CString				m_tileName;
	uInt32				m_tileRow;
	uInt32				m_tileColumn;
	CString				m_currPath;

	flt32				m_height;
	flt32				m_heightMapUnit;
	
	bool				m_hasHeightmap;
	char				m_textureName[MAX_PATH];
	CImage				m_heightMap;
};

#endif	// _UI_DLG_NEWWTDFILEDLG_H__
