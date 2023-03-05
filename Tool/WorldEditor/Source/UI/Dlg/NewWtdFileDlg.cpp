/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NewWtdFileDlg.cpp
* Date: 	01/24/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include <atlimage.h>
#include "NewWtdFileDlg.h"
#include "WorldEditor.h"

////////////////////////////////////////////////////////////////////////////////
// CNewWorldDlg dialog
IMPLEMENT_DYNAMIC(CNewWtdFileDlg, CDialog)
BEGIN_MESSAGE_MAP(CNewWtdFileDlg, CDialog)
	ON_BN_CLICKED(IDC_CK_NEWWTD_HEIGHTMAP, &CNewWtdFileDlg::OnBnClickedCkHeightmap)
END_MESSAGE_MAP()

CNewWtdFileDlg::CNewWtdFileDlg(CWnd* pParent /*=NULL*/)
: CDialog(CNewWtdFileDlg::IDD, pParent)
{
	m_height			= 0.0f;
	m_heightMapUnit		= 0.0f;
	m_tileColumn		= 16;
	m_tileRow			= 16;
	m_hasHeightmap		= false;
}

CNewWtdFileDlg::~CNewWtdFileDlg()
{
	m_height			= 0.0f;
	m_hasHeightmap		= false;
}

void CNewWtdFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CNewWorldDlg)
	DDX_Control(pDX, IDC_EDT_NEWWTD_NAME, m_editTileName);
	DDX_Control(pDX, IDC_EDT_NEWWTD_ROW, m_editTileRow);
	DDX_Control(pDX, IDC_EDT_NEWWTD_COLUMN, m_editTileColumn);
	DDX_Control(pDX, IDC_CK_NEWWTD_HEIGHTMAP, m_btnHeightmap);
	DDX_Control(pDX, IDC_EDT_NEWWTD_TEXTURE, m_editTexture);
	DDX_Control(pDX, IDC_EDT_NEWWTD_HEIGHTMAP, m_editHeightmap);
	DDX_Control(pDX, IDC_EDIT_NEWWTD_HEIGHT, m_editHeight);
	DDX_Control(pDX, IDC_EDT_NEWWTD_HEIGHTMAP_UNIT, m_editHeightUnit);
	//}}AFX_DATA_MAP
}

BOOL CNewWtdFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_editTexture.Initialize(this, BES_XT_CHOOSEFILE);
	m_editHeightmap.Initialize(this, BES_XT_CHOOSEFILE);
	
	m_editTexture.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );
	m_editHeightmap.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );

	CString defaultTexture;
	defaultTexture.Format( _T("%s\\%s"), CWorld::GetAppDataCharDir(), _T("data\\Terrain\\caodi\\cao_025f_db.dds") );
	
	m_btnHeightmap.SetCheck(0);
	SetHasHeightmap( false );

	m_editTexture.SetWindowText( defaultTexture );
	m_editTileName.SetWindowText( _T("new tile") );
	m_editTileRow.SetWindowText( _T("16") );
	m_editTileColumn.SetWindowText( _T("16") );
	m_editHeight.SetWindowText( _T("0.0") );
	CString heightMapUnit;
	heightMapUnit.Format( _T("%4.3f"), 0.6f );
	m_editHeightUnit.SetWindowText( heightMapUnit );

	UpdateData( FALSE );

	m_editHeight.SetFocus();

	return TRUE;
}

void CNewWtdFileDlg::SetHasHeightmap( bool hasHeightmap )
{
	m_hasHeightmap = hasHeightmap;

	if( hasHeightmap ){
		m_editHeightmap.EnableWindow( TRUE );
	}
	else{
		m_editHeightmap.EnableWindow( FALSE );
	}
}

void CNewWtdFileDlg::OnOK()
{
	UpdateData();
	
	CString strValue, texturePath;
	m_editTileName.GetWindowText( m_tileName );
	if ((-1 != m_tileName.FindOneOf(_T("~`!@#$%^&*()+-=\\|\"':;?/>.<,{[}]"))))
	{
		::AfxMessageBox( _T("名字错误，存在非法字符，合法的名字应该由字母，数字，空格或者下划线组成！") );
		return;
	}
	if (-1 == m_tileName.Find(_T(".mew")))
	{
		m_tileName += _T(".mew");
	}
	m_editTileRow.GetWindowText( strValue );
	m_tileRow = _tstoi(strValue);
	if (m_tileRow < 1)
	{
		m_tileRow = 1;
	}
	m_editTileColumn.GetWindowText( strValue );
	m_tileColumn = _tstoi(strValue);
	if (m_tileColumn < 1)
	{
		m_tileColumn = 1;
	}
	CFileFind ff;
	CString strPath( m_currPath );
	strPath += _T("\\");
	strPath += m_tileName;
	BOOL bFound = ff.FindFile(strPath);

	if( bFound )
	{
		::AfxMessageBox( _T("名字已经存在，错误！") );
		return;
	}
	
	// height
	m_editHeight.GetWindowText( strValue );
	m_height = _tstof( strValue );
	m_editHeightUnit.GetWindowText( strValue );
	m_heightMapUnit = _tstof( strValue );

	// heghtmap
	if( m_hasHeightmap )
	{
		CString hgtPath;
		m_editHeightmap.GetWindowText( hgtPath );
		if( hgtPath.GetLength() > (MAX_PATH>>1) )
		{
			::AfxMessageBox( _T("高度图目录太深不能处理！") );
			return;
		}
		if( hgtPath.GetLength() < 3 )
		{
			::AfxMessageBox( _T("请选择高度图！") );
			return;
		}
		if( S_OK != m_heightMap.Load( hgtPath ) )
		{
			::AfxMessageBox( _T("不能读取高度图,请确认格式是否正确(BMP)！") );
			return;
		}
		if( /*( ((m_heightMap.GetHeight()-1)%8) != 0 ) || ( 0!=((m_heightMap.GetWidth()-1)%8) ) ||*/
			(m_tileRow*8> m_heightMap.GetHeight()-1) || (m_tileColumn*8 > m_heightMap.GetWidth()-1))
		{
			::AfxMessageBox( _T("高度图大小错误！") );
			return;
		}
		if( (m_tileRow*8 < m_heightMap.GetHeight()-1) || (m_tileColumn*8 < m_heightMap.GetWidth()-1) )
		{
			char prompt[256] = {0};
			sprintf_s(prompt, "高度图太大，只有%d * %d区域有效，是否继续？", m_tileColumn*8+1, m_tileRow*8+1);
			int ret = ::MessageBox( NULL, prompt, "提醒" , MB_OKCANCEL );
			if (ret == IDCANCEL)
			{
				return;
			}
		}
	}
	
	// base texture.
	m_editTexture.GetWindowText( texturePath );
	if( texturePath.GetLength() < 1 )
	{
		::AfxMessageBox( _T("必须设定初始纹理！") );
		return;
	}
	if( texturePath.GetLength() > (MAX_PATH>>1) )
	{
		::AfxMessageBox( _T("纹理路径长度不对，请检察层次是否太深！") );
		return;
	}
	texturePath.MakeLower();
	
	CString workPath( CWorld::GetAppDataDir() );
	workPath.MakeLower();
	sInt32 pos = texturePath.Find( workPath );
	if( texturePath.GetLength() < workPath.GetLength() )
	{
		::AfxMessageBox( _T("所选纹理必须在工作目录下!") );
		return;
	}
	if( -1 == pos )
	{
		::AfxMessageBox( _T("所选纹理必须在工作目录下!") );
		return;
	}
	else if( 0 != pos )
	{
		::AfxMessageBox( _T("出现异常错误!") );
		return;
	}
	sInt32 len = texturePath.GetLength() - workPath.GetLength();
	if( len < 1 )
	{
		::AfxMessageBox( _T("没有选择纹理!") );
		return;
	}

	CString subDir = texturePath.Right( len-1 );	// 将 '\'或'/' 去掉
	
	SwPublicFunc::TChar2MutiChar( m_textureName, MAX_PATH*sizeof(TCHAR), subDir, (subDir.GetLength()+1)*sizeof(TCHAR) );
	
	((CMainFrame *) AfxGetMainWnd())->SetPromptText("Tile创建完毕...", 3000, "请设置灯光和雾，并保存为环境, 才可以看到正确的地图");
	CDialog::OnOK();
}

CString& CNewWtdFileDlg::GetTileName(  ) 
{
	return m_tileName;
}

flt32 CNewWtdFileDlg::GetHeight() const
{
	return m_height;
}

flt32 CNewWtdFileDlg::GetHeightMapUnit() const
{
	return m_heightMapUnit;
}

const CImage* CNewWtdFileDlg::GetHeightmap() const
{
	return &m_heightMap;
}

const char* CNewWtdFileDlg::GetBaseTexture() const
{
	return m_textureName;
}

void CNewWtdFileDlg::OnBnClickedCkHeightmap()
{
	m_hasHeightmap = (1==m_btnHeightmap.GetCheck())?true:false;
	SetHasHeightmap( m_hasHeightmap );
}

void CNewWtdFileDlg::SetCurrPath( const TCHAR* pPath )
{
	m_currPath = pPath;
}