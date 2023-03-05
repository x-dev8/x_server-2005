/*******************************************************************************
*  Copyright ZWS (C) 2007 - All Rights Reserved
*
* File: 	ReplaceTileTextureDlg.h
* Date: 	11/01/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_DLG_REPLACETILETEXTUREDLG_H__
#define _UI_DLG_REPLACETILETEXTUREDLG_H__

class CReplaceTileTextureDlg : public CDialog
{
	friend class		CToolWorld;
	DECLARE_DYNAMIC(CReplaceTileTextureDlg)

public:
	enum { IDD = IDD_DLG_RELACE_TILE_TEXTURE };
						CReplaceTileTextureDlg(CWnd* pParent = NULL);   // standard constructor
	virtual				~CReplaceTileTextureDlg();

// Dialog Data
	void				SetTile( sInt32 tileX, sInt32 tileY );
	
protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK();

	DECLARE_MESSAGE_MAP()

protected:
	CXTBrowseEdit		m_editTexture;
	char				m_textureName[MAX_PATH];
};

#endif	// _UI_DLG_REPLACETILETEXTUREDLG_H__