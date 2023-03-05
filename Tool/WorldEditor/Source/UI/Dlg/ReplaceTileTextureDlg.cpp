#include "stdafx.h"
#include "Resource/Resource.h"
#include "WorldEditor.h"
#include "ReplaceTileTextureDlg.h"

IMPLEMENT_DYNAMIC(CReplaceTileTextureDlg, CDialog)

CReplaceTileTextureDlg::CReplaceTileTextureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplaceTileTextureDlg::IDD, pParent)
{

}

CReplaceTileTextureDlg::~CReplaceTileTextureDlg()
{
}

void CReplaceTileTextureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CReplaceTileTextureDlg)
	DDX_Control(pDX, IDC_EDT_NEW_TEXTURE, m_editTexture);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReplaceTileTextureDlg, CDialog)
END_MESSAGE_MAP()


BOOL CReplaceTileTextureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editTexture.Initialize(this, BES_XT_CHOOSEFILE);
	m_editTexture.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );

	CString defaultTexture;
	defaultTexture.Format( _T("%s\\%s"), CWorld::GetAppDataCharDir(), _T("data\\Terrain\caodi\cao_025f_db.dds") );
	m_editTexture.SetWindowText( defaultTexture );

	UpdateData( FALSE );

	return TRUE;
}

void CReplaceTileTextureDlg::OnOK()
{
	UpdateData();

	CString texturePath;

	m_editTexture.GetWindowText( texturePath );
	if( texturePath.GetLength() < 1 ) {
		::AfxMessageBox( _T("必须设定初始纹理！") );
		return;
	}
	if( texturePath.GetLength() > (MAX_PATH>>1) ) {
		::AfxMessageBox( _T("纹理路径长度不对，请检察层次是否太深！") );
		return;
	}
	texturePath.MakeLower();

	CString workPath( CWorld::GetAppDataDir() );
	sInt32 pos = texturePath.Find( workPath );
	if( texturePath.GetLength() < workPath.GetLength() ) {
		::AfxMessageBox( _T("所选纹理必须在工作目录下!") );
		return;
	}
	if( -1 == pos )	{
		::AfxMessageBox( _T("所选纹理必须在工作目录下!") );
		return;
	}
	else if( 0 != pos )	{
		::AfxMessageBox( _T("出现异常错误!") );
		return;
	}
	sInt32 len = texturePath.GetLength() - workPath.GetLength();
	if( len < 1 ) {
		::AfxMessageBox( _T("没有选择纹理!") );
		return;
	}
	CString subDir = texturePath.Right( len-1 );	// 将 '\'或'/' 去掉

	SwPublicFunc::TChar2MutiChar( m_textureName, MAX_PATH*sizeof(TCHAR), subDir, (subDir.GetLength()+1)*sizeof(TCHAR) );

	CDialog::OnOK();
}

// CReplaceTileTextureDlg message handlers
