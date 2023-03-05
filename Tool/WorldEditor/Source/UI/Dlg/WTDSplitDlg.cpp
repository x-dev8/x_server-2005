/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WTDSplitDlg.cpp
* Create: 	11/18/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "Resource/Resource.h"
#include "WTDSplitDlg.h"
#include "Map/WorldReadStreamEdit.h"
#include "Map/WorldWriteStream.h"
IMPLEMENT_DYNAMIC(CWTDSplitDlg, CDialog)

CWTDSplitDlg::CWTDSplitDlg( CWnd* pParent /*= NULL*/ )
: CDialog(CWTDSplitDlg::IDD, pParent)
,m_isUpDown(true)
{
	m_UpLeft = 0;
}

BEGIN_MESSAGE_MAP(CWTDSplitDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_LEFTRIGHT_SPLIT, &CWTDSplitDlg::OnBnClickedRadioLeftright)
	ON_BN_CLICKED(IDC_RADIO_UPDOWN_SPLIT, &CWTDSplitDlg::OnBnClickedRadioUpdown)
END_MESSAGE_MAP()


BOOL CWTDSplitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_editSourceFileName.Initialize(this, BES_XT_CHOOSEFILE);
	m_editSourceFileName.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );

	m_editUpLeft.SetWindowText(_T("1"));

	OnBnClickedRadioUpdown();
	UpdateData( FALSE );
	return TRUE;
}

void CWTDSplitDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDT_SPLITWTD_UPLEFT, m_editSourceFileName);
	DDX_Control(pDX, IDC_EDT_SPLITWTD_DOWNRIGHT, m_editUpLeft);

}

void CWTDSplitDlg::OnOK()
{
	CResEditMgr::CreateStaticStream();
	CString strValue;

	m_editSourceFileName.GetWindowText( strValue );
	if( strValue.GetLength() < 1 ) {
		::AfxMessageBox( _T("源文件必须设定名称！") );
		return;
	}
	if( strValue.GetLength() > (MAX_PATH>>1) ) {
		::AfxMessageBox( _T("路径长度不对，请检察层次是否太深！") );
		return;
	}
	strValue.MakeLower();

// 	SwPublicFunc::TChar2MutiChar( m_SourcefileName, MAX_PATH*2*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(char) );



	CWorldBuffer* pBuffer = SwGlobal::GetWorld()->GetWorldBuffer();
	CWorldReadStreamEdit readStream(NULL);
	CWorldTile sourceTile(strValue.GetString());
	sourceTile.Create(pBuffer,new CResEditMgr);

	if (!readStream.LoadWtd(&sourceTile,strValue.GetString()))
	{
		::AfxMessageBox( _T("源文件加载失败！") );
		return;
	}
	char fileName[MAX_PATH*2];
	sprintf_s( fileName, "%s",strValue.GetString());
	char* pFind = strstr(fileName,".mew");
	strcpy(&pFind[1],"road");
	readStream.LoadRoadRes(&sourceTile,fileName);
	strcpy(&pFind[1],"grass");
	if (!readStream.LoadDoodadRes(&sourceTile,fileName))
	{
		strcpy(&pFind[1],"cao");
		readStream.LoadDoodadRes(&sourceTile,fileName);
	}
// 	strcpy(&pFind[1],"alp");
// 	readStream.LoadAlphaRes(&sourceTile,fileName);

	m_editUpLeft.GetWindowText( strValue );
	m_UpLeft = _tstoi(strValue);
	if( m_UpLeft < 1) 
	{
		::AfxMessageBox( _T("新tile1的chunk最少大于0！") );
		return;
	}

	{
		sInt32 chunkOffset[2];
		chunkOffset[0] = 0;
		chunkOffset[1] = 0;
		sInt32 UpLeftRow = sourceTile.GetRowColumn()[1];
		sInt32 UpLeftColumn = sourceTile.GetRowColumn()[0];
		CStringA upLeftName(sourceTile.GetPathName());
		int nstart = upLeftName.Find(".mew");
		if (m_isUpDown)
		{
			upLeftName.Insert(nstart,".Up");
			UpLeftRow = m_UpLeft;
		}
		else
		{
			upLeftName.Insert(nstart,".Left");
			UpLeftColumn = m_UpLeft;
		}
		CWorldTile UpLeftTile(upLeftName);
		UpLeftTile.Create(pBuffer,new CResEditMgr);
		UpLeftTile.SetRowColumn(UpLeftRow,UpLeftColumn);
		CWorldChunk* pSourceChunk = NULL;
		for (sInt32 x = 0; x < UpLeftColumn; ++x)
		{
			for (sInt32 y = 0; y < UpLeftRow; ++y)
			{
				pSourceChunk = sourceTile.GetChunk(y* sourceTile.GetRowColumn()[0] + x);
				Assert(pSourceChunk);
				CWorldChunk* pDestChunk = UpLeftTile.GetChunk(y*UpLeftColumn + x);
				pDestChunk->CloneFrom(pSourceChunk);
			}
		}
		{//clone model
			((CResEditMgr*)UpLeftTile.GetCResMgr())->CloneModelInfo(sourceTile.GetCResMgr(),chunkOffset);
		}
		UpLeftTile.SetLoad(true);

		CWorldWriteStream	writeStream(SwGlobal::GetWorld());
		if(!writeStream.WriteWtd(upLeftName,&UpLeftTile,false))
		{
			::AfxMessageBox( _T("写入拆分后的tile1失败！") );
			return;
		}
		upLeftName.Replace(".mew",".road");
		writeStream.WriteRoadRes(upLeftName,&UpLeftTile);
		if(upLeftName.Replace(".road",".grass"))
		{
			writeStream.WriteDoodadRes(upLeftName, &UpLeftTile);
		}
		if(upLeftName.Replace(".grass",".alpha"))
		{
			writeStream.WriteAlphaRes(upLeftName, &UpLeftTile);
		}
	}
	{
		sInt32 chunkOffset[2];
		chunkOffset[0] = 0;
		chunkOffset[1] = 0;
		sInt32 downRightRow = sourceTile.GetRowColumn()[1];
		sInt32 downRightColumn = sourceTile.GetRowColumn()[0];
		CStringA downRightName(sourceTile.GetPathName());
		int nstart = downRightName.Find(".mew");
		if (m_isUpDown)
		{
			downRightName.Insert(nstart,".Down");
			downRightRow -= m_UpLeft;
			chunkOffset[1] = m_UpLeft;
		}
		else
		{
			downRightName.Insert(nstart,".Right");
			downRightColumn -= m_UpLeft;
			chunkOffset[0] = m_UpLeft;
		}
		CWorldTile downRightTile(downRightName);
		downRightTile.Create(pBuffer,new CResEditMgr);
		downRightTile.SetRowColumn(downRightRow,downRightColumn);
		CWorldChunk* pSourceChunk = NULL;
		for (sInt32 x = 0; x < downRightColumn; ++x)
		{
			for (sInt32 y = 0; y < downRightRow; ++y)
			{
				pSourceChunk = sourceTile.GetChunk((y+chunkOffset[1])* sourceTile.GetRowColumn()[0] + x + chunkOffset[0]);
				Assert(pSourceChunk);
				CWorldChunk* pDestChunk = downRightTile.GetChunk(y*downRightColumn + x);
				pDestChunk->CloneFrom(pSourceChunk);
			}
		}
		{//clone model
			chunkOffset[0] = -chunkOffset[0];
			chunkOffset[1] = -chunkOffset[1];
			((CResEditMgr*)downRightTile.GetCResMgr())->CloneModelInfo(sourceTile.GetCResMgr(),chunkOffset);
		}
		downRightTile.SetLoad(true);

		CWorldWriteStream	writeStream(SwGlobal::GetWorld());
		if(!writeStream.WriteWtd(downRightName,&downRightTile,false))
		{
			::AfxMessageBox( _T("写入拆分后的tile2失败！") );
			return;
		}
		downRightName.Replace(".mew",".road");
		writeStream.WriteRoadRes(downRightName,&downRightTile);
		if(downRightName.Replace(".road",".grass"))
		{
			writeStream.WriteDoodadRes(downRightName, &downRightTile);
		}
		if(downRightName.Replace(".grass",".alpha"))
		{
			writeStream.WriteAlphaRes(downRightName, &downRightTile);
		}
	}

	CDialog::OnOK();
}

void CWTDSplitDlg::OnBnClickedRadioLeftright()
{
	CheckDlgButton( IDC_RADIO_UPDOWN, 0 );
	CheckDlgButton( IDC_RADIO_LEFTRIGHT, 1 );
	m_isUpDown = false;
}

void CWTDSplitDlg::OnBnClickedRadioUpdown()
{
	CheckDlgButton( IDC_RADIO_UPDOWN, 1 );
	CheckDlgButton( IDC_RADIO_LEFTRIGHT, 0 );
	m_isUpDown = true;
}
