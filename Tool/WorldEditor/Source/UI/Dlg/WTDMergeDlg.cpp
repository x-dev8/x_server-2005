/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WTDMergeDlg.cpp
* Create: 	11/18/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "Resource/Resource.h"
#include "WTDMergeDlg.h"
#include "Map/WorldReadStreamEdit.h"
#include "Map/WorldWriteStream.h"
IMPLEMENT_DYNAMIC(CWTDMergeDlg, CDialog)

CWTDMergeDlg::CWTDMergeDlg( CWnd* pParent /*= NULL*/ )
: CDialog(CWTDMergeDlg::IDD, pParent)
,m_isUpDown(true)
{

}

BEGIN_MESSAGE_MAP(CWTDMergeDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_LEFTRIGHT, &CWTDMergeDlg::OnBnClickedRadioLeftright)
	ON_BN_CLICKED(IDC_RADIO_UPDOWN, &CWTDMergeDlg::OnBnClickedRadioUpdown)
END_MESSAGE_MAP()


BOOL CWTDMergeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_editSourceFileName.Initialize(this, BES_XT_CHOOSEFILE);
	m_editSourceFileName.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );

	m_editUpLeft.Initialize(this, BES_XT_CHOOSEFILE);
	m_editUpLeft.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );

	OnBnClickedRadioUpdown();
	UpdateData( FALSE );
	return TRUE;
}

void CWTDMergeDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDT_MERGEWTD_UPLEFT, m_editSourceFileName);
	DDX_Control(pDX, IDC_EDT_MERGEWTD_DOWNRIGHT, m_editUpLeft);

}

void CWTDMergeDlg::OnOK()
{
	CResEditMgr::CreateStaticStream();
	CString strValue;

	m_editSourceFileName.GetWindowText( strValue );
	if( strValue.GetLength() < 1 ) {
		::AfxMessageBox( _T("文件1必须设定名称！") );
		return;
	}
	if( strValue.GetLength() > (MAX_PATH>>1) ) {
		::AfxMessageBox( _T("路径长度不对，请检察层次是否太深！") );
		return;
	}
	strValue.MakeLower();

	SwPublicFunc::TChar2MutiChar( m_SourcefileName, MAX_PATH*2*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );


	m_editUpLeft.GetWindowText( strValue );
	if( strValue.GetLength() < 1 ) {
		::AfxMessageBox( _T("文件2必须设定名称！") );
		return;
	}
	if( strValue.GetLength() > (MAX_PATH>>1) ) {
		::AfxMessageBox( _T("路径长度不对，请检察层次是否太深！") );
		return;
	}
	strValue.MakeLower();

	SwPublicFunc::TChar2MutiChar( m_UpLeft, MAX_PATH*2*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );

	CWorldBuffer* pBuffer = SwGlobal::GetWorld()->GetWorldBuffer();
	CWorldReadStreamEdit readStream(NULL);
	CWorldTile firstTile(m_SourcefileName);
	firstTile.Create(pBuffer,new CResEditMgr);

	if (!readStream.LoadWtd(&firstTile,m_SourcefileName))
	{
		::AfxMessageBox( _T("文件1加载失败！") );
		return;
	}
	char fileName[MAX_PATH*2];
	sprintf_s( fileName, "%s",m_SourcefileName);
	char* pFind = strstr(fileName,".mew");
	strcpy(&pFind[1],"road");
	readStream.LoadRoadRes(&firstTile,fileName);
	strcpy(&pFind[1],"grass");
	if (!readStream.LoadDoodadRes(&firstTile,fileName))
	{
		strcpy(&pFind[1],"cao");
		readStream.LoadDoodadRes(&firstTile,fileName);
	}
// 	strcpy(&pFind[1],"alp");
// 	readStream.LoadAlphaRes(&firstTile,fileName);

	CWorldTile secondTile(m_UpLeft);
	secondTile.Create(pBuffer,new CResEditMgr);
	if (!readStream.LoadWtd(&secondTile,m_UpLeft))
	{
		::AfxMessageBox( _T("文件2加载失败！") );
		return;
	}
	sprintf_s( fileName, "%s",m_UpLeft);
	pFind = strstr(fileName,".mew");
	strcpy(&pFind[1],"road");
	readStream.LoadRoadRes(&secondTile,fileName);
	strcpy(&pFind[1],"grass");
	if (!readStream.LoadDoodadRes(&secondTile,fileName))
	{
		strcpy(&pFind[1],"cao");
		readStream.LoadDoodadRes(&secondTile,fileName);
	}
// 	strcpy(&pFind[1],"alp");
// 	readStream.LoadAlphaRes(&secondTile,fileName);
	sInt32 newRow = 0;
	sInt32 newColumn = 0;
	if (m_isUpDown)
	{
		if (secondTile.GetRowColumn()[0] != firstTile.GetRowColumn()[0])
		{
			::AfxMessageBox( _T("用于合并的tiles宽度不匹配！") );
			return;
		}
		newColumn = secondTile.GetRowColumn()[0] ;
		newRow	= secondTile.GetRowColumn()[1] +firstTile.GetRowColumn()[1] ;
	}
	else
	{
		if (secondTile.GetRowColumn()[1] != firstTile.GetRowColumn()[1])
		{
			::AfxMessageBox( _T("用于合并的tiles高度不匹配！") );
			return;
		}
		newColumn = secondTile.GetRowColumn()[0] + firstTile.GetRowColumn()[0] ;
		newRow	= secondTile.GetRowColumn()[1] ;
	}
	CStringA newName(firstTile.GetPathName());
	int nstart = newName.Find(".mew");
	newName.Insert(nstart,".merge");
	CWorldTile newTile(newName);
	newTile.Create(pBuffer,new CResEditMgr);
	newTile.SetRowColumn(newRow,newColumn);
	CWorldChunk* pSourceChunk = NULL;
	for (sInt32 x = 0; x < newColumn; ++x)
	{
		for (sInt32 y = 0; y < newRow; ++y)
		{
			if (x < firstTile.GetRowColumn()[0])
			{
				if (y < firstTile.GetRowColumn()[1])
				{
					pSourceChunk = firstTile.GetChunk(y* firstTile.GetRowColumn()[0] + x);
				}
				else
				{
					pSourceChunk = secondTile.GetChunk((y - firstTile.GetRowColumn()[1])*secondTile.GetRowColumn()[0] + x);
				}
			}
			else
			{
				if (y < firstTile.GetRowColumn()[1])
				{
					pSourceChunk = secondTile.GetChunk(y* secondTile.GetRowColumn()[0] + x - firstTile.GetRowColumn()[0]);
				}
				else
				{
					Assert(0);
				}
			}
			Assert(pSourceChunk);
			CWorldChunk* pDestChunk = newTile.GetChunk(y*newColumn + x);
			pDestChunk->CloneFrom(pSourceChunk);
		}
	}
	{//clone model
		sInt32 chunkOffset[2];
		chunkOffset[0] = 0;
		chunkOffset[1] = 0;
		((CResEditMgr*)newTile.GetCResMgr())->CloneModelInfo(firstTile.GetCResMgr(),chunkOffset);
		chunkOffset[0] = newColumn - secondTile.GetRowColumn()[0];
		chunkOffset[1] = newRow - secondTile.GetRowColumn()[1];
		((CResEditMgr*)newTile.GetCResMgr())->CloneModelInfo(secondTile.GetCResMgr(),chunkOffset);
	}
// 	for( int i = 0; i < newTile.GetChunkTotal(); i++ ) 
// 	{
// 		newTile.GetChunk(i)->SetLoadLevel(CWorldChunk::eDoodadLoaded);
// 	}
	newTile.SetLoad(true);

	CWorldWriteStream	writeStream(SwGlobal::GetWorld());
	if(!writeStream.WriteWtd(newName,&newTile,false))
	{
		::AfxMessageBox( _T("写入合并后的tile失败！") );
		return;
	}
	newName.Replace(".mew",".road");
	writeStream.WriteRoadRes(newName,&newTile);
	if(newName.Replace(".road",".grass"))
	{
		writeStream.WriteDoodadRes(newName, &newTile);
	}
	if(newName.Replace(".grass",".alpha"))
	{
		writeStream.WriteAlphaRes(newName, &newTile);
	}
	CDialog::OnOK();
}

void CWTDMergeDlg::OnBnClickedRadioLeftright()
{
	CheckDlgButton( IDC_RADIO_UPDOWN, 0 );
	CheckDlgButton( IDC_RADIO_LEFTRIGHT, 1 );
	m_isUpDown = false;
}

void CWTDMergeDlg::OnBnClickedRadioUpdown()
{
	CheckDlgButton( IDC_RADIO_UPDOWN, 1 );
	CheckDlgButton( IDC_RADIO_LEFTRIGHT, 0 );
	m_isUpDown = true;
}
