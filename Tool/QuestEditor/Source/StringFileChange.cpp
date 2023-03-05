// StringFileChange.cpp : implementation file
//

#include "stdafx.h"
#include "QuestEditor.h"
#include "StringFileChange.h"

#include "SlkReader.h"
#include "XmlStringLanguage.h"


// StringFileChange dialog

IMPLEMENT_DYNAMIC(StringFileChange, CDialog)

StringFileChange::StringFileChange(CWnd* pParent /*=NULL*/)
	: CDialog(StringFileChange::IDD, pParent)
{

}

StringFileChange::~StringFileChange()
{
}

void StringFileChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, m_editSlkFile);
	DDX_Control(pDX, IDC_EDIT8, m_editXmlFile);
}


BEGIN_MESSAGE_MAP(StringFileChange, CDialog)
	ON_BN_CLICKED(IDC_BUTTON19, &StringFileChange::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON18, &StringFileChange::OnBnClickedButton18)
	ON_BN_CLICKED(IDOK, &StringFileChange::OnBnClickedOk)
END_MESSAGE_MAP()


// StringFileChange message handlers

void StringFileChange::OnBnClickedButton19()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "String Slk(String.slk)|String.slk|");

	if (FileDlg.DoModal() == IDOK)
	{
		m_editSlkFile.SetWindowText(FileDlg.GetPathName());		
	}

}

void StringFileChange::OnBnClickedButton18()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "String Xml(String.xml)|String.xml|");

	if (FileDlg.DoModal() == IDOK)
	{
		m_editXmlFile.SetWindowText(FileDlg.GetPathName());		
	}
}

void StringFileChange::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CString strSlk = "";
	m_editSlkFile.GetWindowText(strSlk);

	CString strXml = "";
	m_editXmlFile.GetWindowText(strXml);

	if (strSlk.IsEmpty() || strXml.IsEmpty())
	{
		return;
	}

	if (LoadFromSlk(strSlk.GetBuffer()))
	{
		if (theXmlString.SaveStringFile(strXml.GetBuffer()))
		{
			AfxMessageBox("转换成功！");
		}		
	}

	//OnOK();
}


bool StringFileChange::LoadFromSlk( char* szFileName )
{
	CSlkReader reader;
	if( !reader.ReadFromFile( szFileName ) )
	{
		assert(false&&"找不到Slk文件");
		return false;
	}

	theXmlString.ClearString();

	int nLine = 2;
	int	nIndex = 0;
	CSlkReader::SField* pField = NULL;
	std::string	strData;
	while( CSlkReader::ret_readover != reader.GotoNextLine( nLine+1 ) )
	{
		// 第一列
		pField = reader.GetFieldOfLine( 1 );
		if( !pField || pField->iFieldType != CSlkReader::field_int )
		{
			assert( false );
			return false;
		}
		if ( nIndex != pField->data.iValue )
		{
			assert( false&&"索引没有按顺序!" );
			return false;
		}
		// 读相应的语言
		//pField = reader.GetFieldOfLine( m_enCurLanguage );
		pField = reader.GetFieldOfLine( 2 );
		if( !pField || pField->iFieldType != CSlkReader::field_string )
		{
			strData = "";
		}
		else
		{
			strData = pField->data.szValue;
		}

		theXmlString.AddString(strData);

		++nIndex;
		++nLine;
	}

	return true;
}