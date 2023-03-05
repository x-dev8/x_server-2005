/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolLayer.h
* Date: 	05/31/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_TOOLSWND_TOOLLAYER_H__
#define _UI_TOOLSWND_TOOLLAYER_H__
#include "afxcmn.h"
#include "afxwin.h"

class CToolLayer;
class CToolLayerDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolLayerDlg)

public:
	CToolLayerDlg(CToolLayerDlg* pParent = NULL);   // standard constructor
	virtual				~CToolLayerDlg();

	// Dialog Data
	enum { IDD = IDD_DLG_LAYER };

	void				SetActive( bool isModify = false );
	void				RefreshLayer( );

	void				RefreshSpecialInfo( CWorldChunk* worldChunk );
	void				UpdateLock( bool isLock );
	void				ShowAlphaText( uInt8 alpha);
	void				PaintModeChange( sInt32 paintMode );

	void				BrushChanged( int nSelect );
	void				FlowChanged( uInt32 flow );

	BOOL				IsUseWinTabPressAsAlpha();
protected:
	void				UpdateLayer();
	void				UpdatePreview( const char* path, const char* name, sInt32 format );
	bool				UpdateSetting( bool isModify );
	bool				FindComboFolderId( const char* folder, sInt32& comboId );
	bool				FindComboTextureId( const char* folder, const char* name, sInt32& comboFdId, sInt32& comboTxId );

	void				DeleteLayer( sInt32 layerId );
	void				EnableAlphaCtrl( BOOL isEnable = TRUE );
	void				EnableColorSelect( BOOL isEnable = TRUE );
	CToolLayer*			GetToolLayer();

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolLayerDlg)
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();

	virtual void		OnOK(){};
	virtual void		OnCancel(){};
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CToolLayerDlg)
	afx_msg void		OnKillfocusEdtAlpha();

	afx_msg void		OnKillfocusCBFlow();
	afx_msg void		OnBtnDeleteLayer( UINT nID );
	afx_msg void		OnBtnGetLayer( UINT nID );
	afx_msg void		OnBtnSetLayer( UINT nID );
	afx_msg void		OnBtnUpLayer( UINT nID );
	afx_msg void		OnBtnDownLayer( UINT nID );
	afx_msg void		OnBrushChange();
	afx_msg void		OnTextureChange();
	afx_msg void		OnModeChange();
	afx_msg void		OnSelVertexColor();
	afx_msg void		OnBnClickedCheckTileCulling();
	afx_msg void		OnBnClickedAlign();
	afx_msg void		OnEnKillfocusEditTextureX0();
	afx_msg void		OnEnKillfocusEditTextureY0();
	afx_msg void		OnEnKillfocusEditTextureScalex0();
	afx_msg void		OnEnKillfocusEditTextureScaley0();
	afx_msg void		OnEnKillfocusEditTextureRotation();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	bool				m_isFillUI;
	sInt32				m_iLayerMode;
	CSpinButtonCtrl		m_spinAlpha;
	CEdit				m_editAlpha;
	CSpinButtonCtrl		m_spinFlow;
	CEdit				m_editFlow;
	CComboBox			m_brushList;
	CComboBox			m_textureList;
	CComboBox			m_modeList;
	CButton				m_chkLockLayer;

	CTexturePreviewWnd	m_texturePreview;
	CTexturePreviewWnd	m_textureLayer[4];


	CXTColorPicker		m_cpVertexColor;
	COLORREF			m_vertexColor;
	CButton				m_chk_Culled;
	CEdit m_edit_textureX0;
	CEdit m_edit_textureY0;
	CEdit m_edit_textureScaleX0;
	CEdit m_edit_textureScaleY0;
	CSpinButtonCtrl m_spin_TextureX0;
	CSpinButtonCtrl m_spin_TextureY0;
	CSpinButtonCtrl m_spin_TextureScaleX0;
	CSpinButtonCtrl m_spin_TextureScaleY0;
	CButton m_chk_Alignment;
	CEdit m_edit_TextureRotation;
	CSpinButtonCtrl m_spin_TextureRotation;

	sInt32			m_nspecialOptLevel;

	CButton			m_UseWinTabsPressCheckBox;
	int				m_nLastAlpha;
public:
	afx_msg void OnBnClickedRadioLevel3();
	afx_msg void OnBnClickedRadioLevel2();
	afx_msg void OnBnClickedRadioLevel1();
	afx_msg void OnBnClickedRadioLevel0();
	void				RefreshSpecialRadioBtn( );
	afx_msg void OnBnClickedBtnRefreshTexture();
	// protected:
	// 	CButton m_chkButtonPaintShadow;
	// public:
	// 	afx_msg void OnBnClickedCheckPaintShadow();
	afx_msg void OnBnClickedButtonSeltexture();
	afx_msg void OnBnClickedCkUseWintab4Alpha();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

#endif	// _UI_TOOLSWND_TOOLLAYER_H__