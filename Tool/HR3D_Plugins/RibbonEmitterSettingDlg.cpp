#include "resource.h"
#include <windows.h>

#include "hr3d_Plugins.h"
#include "hr3d_maxinterface.h"
#include "ribbonemittersettingdlg.h"
#include "hr3d_mdx2candidate.h"

static const char *RIBBON_EMITTER_BLEND_MODES[] =
{
	"Blend", "Modulate"	
};
static const DWORD RIBBON_EMITTER_BLEND_VALUES[] =
{
	eTwoSided|eAlphaBlend|eZWriteDisable|eDstBlendOne,
	eTwoSided|eAlphaBlend|eZWriteDisable|eOpModulate1X
};

RibbonEmitterSettingDlg g_ribbonEmitterSetting;
INT_PTR CALLBACK RibbonEmitterSettingWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return g_ribbonEmitterSetting.MsgProc( hWnd, uMsg, wParam, lParam );
}

RibbonEmitterSettingDlg::RibbonEmitterSettingDlg(void)
{

}

RibbonEmitterSettingDlg::~RibbonEmitterSettingDlg(void)
{

}

void RibbonEmitterSettingDlg::RefreshUI()
{
	HWND hItem = NULL;
	hItem = GetDlgItem( m_hWnd,  IDC_EDIT_TEXTURENAME );
	SetWindowText( hItem, m_szTextureName );

	char s[256];

	sprintf( s, "%ld", m_dwEdgePerSec );
	hItem = GetDlgItem( m_hWnd,  IDC_EDIT_EDGEPERSEC );
	SetWindowText( hItem, s );

	sprintf( s, "%ld", m_dwEdgeLife );
	hItem = GetDlgItem( m_hWnd,  IDC_EDIT_EDGELIFE );
	SetWindowText( hItem, s );

	sprintf( s, "%ld", m_dwVertexAlpha );
	hItem = GetDlgItem( m_hWnd,  IDC_EDIT_VERTEXALPHA );
	SetWindowText( hItem, s );

	hItem = GetDlgItem( m_hWnd, IDC_COMBO_BINDPARTNAME );
	ComboBox_SelectString( hItem, 0, m_szBindPartName );

	int curSel = 0;
	for (int i = 0; i < 2; ++i)
	{
		if (m_dwBlendMode == RIBBON_EMITTER_BLEND_VALUES[i])
		{
			curSel = i;
			break;
		}
	}
	hItem = GetDlgItem(m_hWnd, IDC_COMBO3);
	ComboBox_SetCurSel(hItem, curSel);

}
void RibbonEmitterSettingDlg::DefaultSetting()
{
	m_szTextureName[0] = 0;
	m_dwEdgePerSec = 1;
	m_dwEdgeLife = 1;
	m_dwVertexAlpha = 255;

	// 旧的默认是0
	m_dwBlendMode = RIBBON_EMITTER_BLEND_VALUES[0];
}

void RibbonEmitterSettingDlg::SaveToNode( INode* pNode )
{
	HWND hItem = NULL;
	hItem = GetDlgItem( m_hWnd,  IDC_EDIT_TEXTURENAME );
	GetWindowText( hItem, m_szTextureName, MAX_PATH );

	char s[256];
	hItem = GetDlgItem( m_hWnd,  IDC_EDIT_EDGEPERSEC );
	GetWindowText( hItem, s, 256 );
	m_dwEdgePerSec = atoi( s );

	hItem = GetDlgItem( m_hWnd,  IDC_EDIT_EDGELIFE );
	GetWindowText( hItem, s, 256 );
	m_dwEdgeLife = atoi( s );

	hItem = GetDlgItem( m_hWnd,  IDC_EDIT_VERTEXALPHA );
	GetWindowText( hItem, s, 256 );
	m_dwVertexAlpha = atoi( s );

	hItem = GetDlgItem( m_hWnd,  IDC_COMBO_BINDPARTNAME );
	int curSel = ComboBox_GetCurSel( hItem );
	if (curSel != -1)
	{
		ComboBox_GetLBText( hItem, curSel, m_szBindPartName );
	}

	hItem = GetDlgItem(m_hWnd, IDC_COMBO3);
	curSel = ComboBox_GetCurSel(hItem);
	m_dwBlendMode = RIBBON_EMITTER_BLEND_VALUES[curSel];

	pNode->SetUserPropString( STR_TEXTURENAME, m_szTextureName );
	pNode->SetUserPropString( STR_BINDPARTNAME,	m_szBindPartName );
	pNode->SetUserPropInt( STR_EDGEPERSEC, m_dwEdgePerSec );
	pNode->SetUserPropInt( STR_EDGELIFE, m_dwEdgeLife );
	pNode->SetUserPropInt( STR_VERTEXALPHA, m_dwVertexAlpha );
	pNode->SetUserPropInt( STR_BLEND_MODE, m_dwBlendMode );
}

void RibbonEmitterSettingDlg::LoadFromNode( INode* pNode )
{
	CStr str;
	if (pNode->UserPropExists( STR_TEXTURENAME ) )
	{
		pNode->GetUserPropString( STR_TEXTURENAME,	str );
		strcpy( m_szTextureName, str.data() );
	}

	int i;
	if (pNode->UserPropExists( STR_EDGEPERSEC ) )
	{
		pNode->GetUserPropInt( STR_EDGEPERSEC, i );
		m_dwEdgePerSec = i;
	}

	if( pNode->UserPropExists( STR_EDGELIFE ) )
	{
		pNode->GetUserPropInt( STR_EDGELIFE, i );
		m_dwEdgeLife = i;
	}

	if( pNode->UserPropExists( STR_VERTEXALPHA ) )
	{
		pNode->GetUserPropInt( STR_VERTEXALPHA, i );
		m_dwVertexAlpha = i;
	}

	if( pNode->UserPropExists( STR_BINDPARTNAME ) )
	{
		pNode->GetUserPropString( STR_BINDPARTNAME,	str );
		strcpy( m_szBindPartName, str.data() );
	}

	if (pNode->UserPropExists(STR_BLEND_MODE))
	{
		pNode->GetUserPropInt(STR_BLEND_MODE, i);
		m_dwBlendMode = i;
	}
}

void RibbonEmitterSettingDlg::GetSetting(HR3D_Mdx2RibbonEmitterSetting *pSetting, void *pObject)
{
	pSetting->dwEdgePerSec = m_dwEdgePerSec;
	pSetting->dwEdgeLifeSec = m_dwEdgeLife;
	pSetting->dwVertexAlpha = m_dwVertexAlpha;
	pSetting->dwBlendMode = m_dwBlendMode;
	if (pObject != NULL)
	{
		HR3D_Mdx2Candidate::RibbonEmitter *re = (HR3D_Mdx2Candidate::RibbonEmitter *) pObject;
		strcpy(re->szBindPartName, m_szBindPartName);
	}
}

LRESULT	RibbonEmitterSettingDlg::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_NOTIFY:
		{
			NMHDR *lpNMHDR = (LPNMHDR) lParam;
			if (lpNMHDR->code == UDN_DELTAPOS)
			{
				NMUPDOWN *lpNMUD = (LPNMUPDOWN) lParam;

				int buddyEditID = 0;
				if (lpNMUD->hdr.idFrom == IDC_SPIN1)
					buddyEditID = IDC_EDIT_EDGEPERSEC;
				else if (lpNMUD->hdr.idFrom == IDC_SPIN32)
					buddyEditID = IDC_EDIT_EDGELIFE;
				else if (lpNMUD->hdr.idFrom == IDC_SPIN33)
					buddyEditID = IDC_EDIT_VERTEXALPHA;

				UINT integerValue = ::GetDlgItemInt(hWnd, buddyEditID, NULL, FALSE);

				// up
				if (lpNMUD->iDelta > 0)
					--integerValue;
				else
					++integerValue;

				if (lpNMUD->hdr.idFrom == IDC_COMBO3)
				{
					if (integerValue < 0)
						integerValue = 0;

					if (integerValue > 255)
						integerValue = 255;
				}
				else
				{
					if (integerValue < 1)
						integerValue = 1;
				}

				::SetDlgItemInt(hWnd, buddyEditID, integerValue, FALSE);
				return 0;
			}
		}
		break;

	case WM_INITDIALOG:
		m_hWnd = hWnd;
		DefaultSetting();
		{
			HWND hItem = GetDlgItem( hWnd, IDC_COMBO_BINDPARTNAME );
			ComboBox_AddString( hItem, STRING_BINDNONE );
			ComboBox_AddString( hItem, STRING_BINDLEFTHAND );
			ComboBox_AddString( hItem, STRING_BINDRIGHTHAND );
			ComboBox_AddString( hItem, STRING_BINDLEFTBACK );
			ComboBox_AddString( hItem, STRING_BINDRIGHTBACK );
			ComboBox_SelectString( hItem, 0, STRING_BINDNONE );

			hItem = GetDlgItem(hWnd, IDC_COMBO3);
			for (int i = 0; i < 2; ++i)
				ComboBox_AddString(hItem, RIBBON_EMITTER_BLEND_MODES[i]);
			ComboBox_SelectString(hItem, 0, "");
		}
		
		// 如果选择了一个节点，
		if (GetMaxIP()->GetSelectedNode( 0 ))
		{
			LoadFromNode( GetMaxIP()->GetSelectedNode( 0 ) );
		}

		RefreshUI();

		{
			SIZE screenSize = { 0, 0 };
			screenSize.cx = ::GetSystemMetrics(SM_CXSCREEN);
			screenSize.cy = ::GetSystemMetrics(SM_CYSCREEN);

			RECT rcWnd;
			::GetWindowRect(hWnd, &rcWnd);

			rcWnd.left = (screenSize.cx - rcWnd.right) / 2;
			rcWnd.top = (screenSize.cy - rcWnd.bottom) / 2;

			// 窗口居中
			::SetWindowPos(hWnd, NULL, rcWnd.left, rcWnd.top, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED);
		}
		break;
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDOK:
		case IDCANCEL:
			EndDialog( hWnd, 0 );
			break;

		case IDC_BUTTON_TEXTURE:
			{
				static TCHAR filter[] =
					TEXT("Tga files (*.tga)\0*.tga\0")
					TEXT("All Files (*.*)\0*.*\0");
				std::string pszFilename = GetOpenOrSaveFileNameEx( filter, filter);
				if( !pszFilename.empty())
				{
					strcpy( m_szTextureName, pszFilename.c_str() );
					HWND hItem = GetDlgItem( m_hWnd,  IDC_EDIT_TEXTURENAME );
					SetWindowText( hItem, m_szTextureName );
				}
			}
			break;

		case IDC_BUTTON_SAVERIBBONEMITTERSETTING:
			{
				INode* pNode = GetMaxIP()->GetSelectedNode( 0 );
				if( pNode )
				{
					SaveToNode( pNode );
				}
			}
			break;
		};
		break;
	};
	return FALSE;
}