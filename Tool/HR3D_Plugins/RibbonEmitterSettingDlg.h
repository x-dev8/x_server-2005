#pragma once

#include <Windows.h>
#include "max.h"
#include "defines.h"

class RibbonEmitterSettingDlg
{
public:
	RibbonEmitterSettingDlg(void);
	~RibbonEmitterSettingDlg(void);
	LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void DefaultSetting();
	void SaveToNode( INode* pNode );
	void LoadFromNode( INode* pNode );
	void RefreshUI();
	void GetSetting(HR3D_Mdx2RibbonEmitterSetting *pSetting, void *pObject = NULL );

public:
	HWND	m_hWnd;

	char	m_szTextureName[MAX_PATH];

	DWORD	m_dwEdgePerSec;
	DWORD	m_dwEdgeLife;
	DWORD	m_dwVertexAlpha;
	DWORD	m_dwBlendMode;
	char	m_szBindPartName[MEX2_MAX_NAME];
};