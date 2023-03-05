/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolTransportDlg.cpp
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "Resource/Resource.h"
#include "Edit/ToolTransport.h"
#include "Edit/ToolManager.h"
#include "ToolTransportDlg.h"
#include "Ndl/NdlWorldEditor.h"
#include "MeTerrain/NdlResMgr.h"
#include "EditRes/NdlEditRes.h"
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolTransportDlg, CDialog)

CToolTransportDlg::CToolTransportDlg(CToolTransportDlg* pParent)
: CDialog(CToolTransportDlg::IDD, pParent)
{
}

CToolTransportDlg::~CToolTransportDlg()
{
	
}

void CToolTransportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolTransportDlg)
	DDX_Control(pDX, IDC_EDT_TRANSPORT_X, m_editTransportX);
	DDX_Control(pDX, IDC_EDT_TRANSPORT_Y, m_editTransportY);
	DDX_Control(pDX, IDC_EDT_TRANSPORT_X_SCALE, m_editTransportScaleX);
	DDX_Control(pDX, IDC_EDT_TRANSPORT_Y_SCALE, m_editTransportScaleY);
	DDX_Control(pDX, IDC_SPIN_TRANSPORT_X, m_spinTransportX);
	DDX_Control(pDX, IDC_SPIN_TRANSPORT_Y, m_spinTransportY);
	DDX_Control(pDX, IDC_SPIN_TRANSPORT_X_SCALE, m_spinTransportScaleX);
	DDX_Control(pDX, IDC_SPIN_TRANSPORT_Y_SCALE, m_spinTransportScaleY);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDT_TARGET_TILE, m_editTargetFile);
	DDX_Control(pDX, IDC_EDT_TARGET_X, m_editTargetX);
	DDX_Control(pDX, IDC_EDT_TARGET_Y, m_editTargetY);
	DDX_Control(pDX, IDC_CHK_PICKTRANSPORT, m_isPickTransport);
	DDX_Control(pDX, IDC_EDT_TARGET_ID, m_editTargetID);
	DDX_Control(pDX, IDC_EDT_TARGET_DIR, m_editTargetDir);
	DDX_Control(pDX, IDC_EDT_TARGET_INDEX, m_readonlyTargetIndex);
	DDX_Control(pDX, IDC_SPIN_TARGET_X, m_spinTargetX);
	DDX_Control(pDX, IDC_SPIN_TARGET_Y, m_spinTargetY);
	DDX_Control(pDX, IDC_SPIN_TARGET_DIR, m_spinTargetDir);
	DDX_Control(pDX, IDC_CHECK_REDNAME, m_checkRed);
	DDX_Control(pDX, IDC_COMBO_VESTTYPE, m_comboVestType);
	DDX_Control(pDX, IDC_EDT_TARGET_MAPID, m_editMapId);
}
BEGIN_MESSAGE_MAP(CToolTransportDlg, CDialog)
	//{{AFX_MSG_MAP(CToolTransportDlg)
	ON_EN_KILLFOCUS(IDC_EDT_TRANSPORT_X, &CToolTransportDlg::OnEnKillfocusEdtTransport)
	ON_EN_KILLFOCUS(IDC_EDT_TRANSPORT_Y, &CToolTransportDlg::OnEnKillfocusEdtTransport)
	ON_EN_KILLFOCUS(IDC_EDT_TRANSPORT_X_SCALE, &CToolTransportDlg::OnEnKillfocusEdtTransport)
	ON_EN_KILLFOCUS(IDC_EDT_TRANSPORT_Y_SCALE, &CToolTransportDlg::OnEnKillfocusEdtTransport)
	ON_EN_KILLFOCUS(IDC_EDT_TARGET_ID, &CToolTransportDlg::OnEnKillfocusEdtTransport)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
	ON_EN_KILLFOCUS(IDC_EDT_TARGET_X, &CToolTransportDlg::OnEnKillfocusEdtTarget)
	ON_EN_KILLFOCUS(IDC_EDT_TARGET_Y, &CToolTransportDlg::OnEnKillfocusEdtTarget)
	ON_EN_KILLFOCUS(IDC_EDT_TARGET_TILE, &CToolTransportDlg::OnEnKillfocusEdtTargetTile)
	ON_BN_CLICKED(IDC_CHK_PICKTRANSPORT, &CToolTransportDlg::OnBnClickedChkPicktransport)
	ON_BN_CLICKED(IDC_RADIO_TRANSPORT, &CToolTransportDlg::OnBnClickedRadioTransport)
	ON_BN_CLICKED(IDC_RADIO_TARGET, &CToolTransportDlg::OnBnClickedRadioTarget)
	ON_EN_KILLFOCUS(IDC_EDT_TARGET_DIR, &CToolTransportDlg::OnEnKillfocusEdtTarget)

	ON_BN_CLICKED(IDC_RADIO_ISTARGET, &CToolTransportDlg::OnBnClickedRadioIstarget)
	ON_BN_CLICKED(IDC_RADIO_ISRELIVE, &CToolTransportDlg::OnBnClickedRadioIsrelive)
	ON_BN_CLICKED(IDC_CHECK_REDNAME, &CToolTransportDlg::OnEnKillfocusEdtTarget)
	ON_CBN_SELCHANGE(IDC_COMBO_VESTTYPE, &CToolTransportDlg::OnEnKillfocusEdtTarget)
	ON_EN_KILLFOCUS(IDC_EDT_TARGET_MAPID, &CToolTransportDlg::OnEnKillfocusEdtTarget)
END_MESSAGE_MAP()

BOOL CToolTransportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

// 	m_editTargetFile.Initialize(this, BES_XT_CHOOSEFILE);
// 
// 	m_editTargetFile.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );
// 	m_editTargetFile.SetDlgFilter(_T("*.mew"));

	m_spinTransportX.SetBuddy( &m_editTransportX );
	m_spinTransportX.SetRange32( 0, 0xfffffff);  
	m_spinTransportX.SetPos( 0 );

	m_spinTransportY.SetBuddy( &m_editTransportY );
	m_spinTransportY.SetRange32( 0, 0xfffffff);  
	m_spinTransportY.SetPos( 0 );

	m_spinTransportScaleX.SetBuddy( &m_editTransportScaleX );
	m_spinTransportScaleX.SetRange32( 0, 0xfffffff);  
	m_spinTransportScaleX.SetPos( 100 );
	m_editTransportScaleX.SetWindowText(_T("1"));

	m_spinTransportScaleY.SetBuddy( &m_editTransportScaleY );
	m_spinTransportScaleY.SetRange32( 0, 0xfffffff);  
	m_spinTransportScaleY.SetPos( 100 );
	m_editTransportScaleY.SetWindowText(_T("1"));

	m_spinTargetX.SetBuddy( &m_editTargetX );
	m_spinTargetX.SetRange32( 0, 0xfffffff);  
	m_spinTargetX.SetPos( 0 );

	m_spinTargetY.SetBuddy( &m_editTargetY );
	m_spinTargetY.SetRange32(0, 0xfffffff);  
	m_spinTargetY.SetPos( 0 );

	m_spinTargetDir.SetBuddy( &m_editTargetDir );
	m_spinTargetDir.SetRange32( -360, 360);  
	m_spinTargetDir.SetPos( 0 );

	CheckDlgButton( IDC_RADIO_TARGET, 0 );
	CheckDlgButton( IDC_RADIO_TRANSPORT, 1 );
	SetDlgItemText(IDC_RADIO_TARGET,_T("增加目标点"));


	CheckDlgButton( IDC_RADIO_ISTARGET, 1 );
	CheckDlgButton( IDC_RADIO_ISRELIVE, 0 );

	m_checkRed.EnableWindow(FALSE);
	m_comboVestType.EnableWindow(FALSE);

	m_comboVestType.ResetContent();
	m_comboVestType.AddString("都不是");
	m_comboVestType.AddString("攻城重生点");
	m_comboVestType.AddString("守城重生点");
	m_comboVestType.SetCurSel(0);

	UpdateData( FALSE );

	return TRUE;
}

void CToolTransportDlg::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( (nSBCode==SB_THUMBPOSITION) ) {
		switch( pScrollBar->GetDlgCtrlID() ) {
		case IDC_SPIN_TRANSPORT_X:
		case IDC_SPIN_TRANSPORT_Y:
			OnEnKillfocusEdtTransport();
			break;
		case IDC_SPIN_TRANSPORT_X_SCALE:
			{
				CString strValue;
				flt32 scaleX = ((flt32)m_spinTransportScaleX.GetPos())/100;
				strValue.Format(_T("%6.2f"),scaleX);
				m_editTransportScaleX.SetWindowText(strValue);
				OnEnKillfocusEdtTransport();
			}
			break;
		case IDC_SPIN_TRANSPORT_Y_SCALE:
			{
				CString strValue;
				flt32 scaleY = ((flt32)m_spinTransportScaleY.GetPos())/100;
				strValue.Format(_T("%6.2f"),scaleY);
				m_editTransportScaleY.SetWindowText(strValue);
				OnEnKillfocusEdtTransport();
			}
			break;
		case IDC_SPIN_TARGET_X:
		case IDC_SPIN_TARGET_Y:
		case IDC_SPIN_TARGET_DIR:
			OnEnKillfocusEdtTarget();
			break;
		default:
			break;
		}
	}
	CDialog::OnVScroll( nSBCode, nPos, pScrollBar );
}


void CToolTransportDlg::RefreshTransport(CTransportResBase* res)
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CToolTransport* transport		= GetToolTransport();

	if (res->IsTransport())
	{
		CheckDlgButton( IDC_RADIO_TARGET, 0 );
		CheckDlgButton( IDC_RADIO_TRANSPORT, 1 );
		CTransportEditRes* tranRes = (CTransportEditRes*)res;
		CWorldTile*		tile = CURRENTTILE;
		CString strValue;
		float x,y,scaleX,scaleY;
		x	= tranRes->GetPosX();
		strValue.Format(_T("%6.2f"),x);
		m_spinTransportX.SetPos( ZnFloat2Int( x ) );
		m_editTransportX.SetWindowText(strValue);

		y	= tranRes->GetPosY();
		strValue.Format(_T("%6.2f"),y);
		m_spinTransportY.SetPos( ZnFloat2Int( y ) );
		m_editTransportY.SetWindowText(strValue);

		scaleX = tranRes->GetRight() - tranRes->GetLeft();
		strValue.Format(_T("%6.2f"),scaleX);
		m_spinTransportScaleX.SetPos( ZnFloat2Int( scaleX *100) );
		m_editTransportScaleX.SetWindowText(strValue);

		scaleY = tranRes->GetTop() - tranRes->GetBottom();
		strValue.Format(_T("%6.2f"),scaleY);
		m_spinTransportScaleY.SetPos( ZnFloat2Int( scaleY *100) );
		m_editTransportScaleY.SetWindowText(strValue);

		m_editTargetFile.SetWindowText(_T(""));
		strValue.Format(_T("%d"),tranRes->GetDesMapID());
		m_editTargetFile.SetWindowText(strValue);
		// 			if (*tranRes->GetName() != '\0')
		// 			{
		// 				strValue.Format(_T("%hs\\%hs"),SwGlobal::GetWorld()->GetWorldPath(),tranRes->GetName());
		// 				m_editTargetFile.SetWindowText(strValue);
		// 			}

		strValue.Format(_T("%d"),tranRes->GetNtargetID());
		m_editTargetID.SetWindowText(strValue);
	}
	else
	{
		CheckDlgButton( IDC_RADIO_TARGET, 1 );
		CheckDlgButton( IDC_RADIO_TRANSPORT, 0 );
		CTargetEditRes* targetRes = (CTargetEditRes*)res;
		CWorldTile*		tile = CURRENTTILE;
		float targetX,targetY,targetDir;
		CString strValue;

			//int nType = targetRes->GetType();
		//m_checkTarget.SetCheck(nType & CTargetEditRes::Type_Target);
		//m_checkRelive.SetCheck(nType & CTargetEditRes::Type_Relive);


		targetX	= targetRes->GetPosX();
		strValue.Format(_T("%6.2f"),targetX);
		m_spinTargetX.SetPos( ZnFloat2Int( targetX ) );
		m_editTargetX.SetWindowText(strValue);

		targetY	= targetRes->GetPosY();
		strValue.Format(_T("%6.2f"),targetY);
		m_spinTargetY.SetPos( ZnFloat2Int( targetY ) );
		m_editTargetY.SetWindowText(strValue);

		targetDir = targetRes->GetTargetDir()*180.f/PI;
		strValue.Format(_T("%6.2f"),targetDir);
		m_spinTargetDir.SetPos( ZnFloat2Int( targetDir ) );
		m_editTargetDir.SetWindowText(strValue);

		if(targetRes->IsRelive())
		{
			OnBnClickedRadioIsrelive();

			strValue.Format(_T("%d"),targetRes->GetReliveId());	

			int nType = targetRes->GetReliveType();

			m_checkRed.SetCheck(nType & CTargetEditRes::Relive_RedName);

			if ((nType & CTargetEditRes::Relive_Attack) != 0)
			{
				m_comboVestType.SetCurSel(1);
			}
			else if ((nType & CTargetEditRes::Relive_Guard) != 0)
			{
				m_comboVestType.SetCurSel(2);
			}
			else
			{
				m_comboVestType.SetCurSel(0);
			}

			CString strMapId = "";
			strMapId.Format(_T("%d"), targetRes->GetReliveMapId());
			m_editMapId.SetWindowText(strMapId);
		}
		else
		{
			OnBnClickedRadioIstarget();
			
			m_checkRed.SetCheck(0);
			m_comboVestType.SetCurSel(0);

			strValue.Format(_T("%d"),targetRes->GetNtargetID());
			m_editMapId.SetWindowText("");
		}
		


		m_readonlyTargetIndex.SetWindowText(strValue);
	}

}

void CToolTransportDlg::SetActive( bool isModify )
{

	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_TRANSPORT );
	CToolTransport* toolTransport = GetToolTransport();

	Assert( NULL != toolTransport );

	toolTransport->Bind( this );

	toolTransport->Reset();

	UpdateData(FALSE);

}


CToolTransport* CToolTransportDlg::GetToolTransport()
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();

	return (CToolTransport*)( toolManager->GetActiveTool() );
}

void CToolTransportDlg::OnEnKillfocusEdtTransport()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CToolTransport* toolTranspot = GetToolTransport();
	if (NULL == toolTranspot->m_currTran || CToolTransport::optMode_Pick != toolTranspot->m_eoptMode)
		return;
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
	float x,y,scaleX,scaleY;
	m_editTransportX.GetWindowText( strValue );
	x	= _tstof( strValue );
	x = ZnClamp<flt32>( x,0, tile->GetRowColumn()[0]*WORLD_CHUNKSIZE);
	strValue.Format(_T("%6.2f"),x);
	m_editTransportX.SetWindowText(strValue);

	m_editTransportY.GetWindowText( strValue );
	y	= _tstof( strValue );
	y = ZnClamp<flt32>( y, 0, tile->GetRowColumn()[1]*WORLD_CHUNKSIZE );
	strValue.Format(_T("%6.2f"),y);
	m_editTransportY.SetWindowText(strValue);

	m_editTransportScaleX.GetWindowText( strValue );
	scaleX	= _tstof( strValue );
	scaleX = ZnClamp<flt32>( scaleX, 0, 360.0f );
	strValue.Format(_T("%6.2f"),scaleX);
	m_editTransportScaleX.SetWindowText(strValue);

	m_editTransportScaleY.GetWindowText( strValue );
	scaleY	= _tstof( strValue );
	scaleY = ZnClamp<flt32>( scaleY, 0, 360.0f );
	strValue.Format(_T("%6.2f"),scaleY);
	m_editTransportScaleY.SetWindowText(strValue);

	m_editTargetID.GetWindowText( strValue );
	sInt32 id = _tstoi(strValue);
	id = ZnClamp<sInt32>( id, 0, 0xfffffff );
	strValue.Format(_T("%d"),id);
	m_editTargetID.SetWindowText(strValue);

	toolTranspot->ApplyTransport(y + scaleY/2,x - scaleX/2,x + scaleX/2,y - scaleY/2,id);
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	toolTranspot->ShowPmpModel();
}

void CToolTransportDlg::OnEnKillfocusEdtTarget()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CToolTransport* toolTranspot = GetToolTransport();
	if (NULL == toolTranspot->m_currTran || CToolTransport::optMode_Pick != toolTranspot->m_eoptMode)
	{
		return;
	}
	CWorldTile*		tile = CURRENTTILE;
	float targetX,targetY,targetDir;
	CString strValue;

	int nMapId = -1;
	CString strMapId = "";
	m_editMapId.GetWindowText(strMapId);
	if(!strMapId.IsEmpty()) { nMapId = atoi(strMapId.GetBuffer()); }

	m_editTargetX.GetWindowText( strValue );
	targetX	= _tstof( strValue );
	if (nMapId == -1 || nMapId == tile->GetMapId()) //有的重生点不在本地图,所以要去掉判断
	{
		targetX = ZnClamp<flt32>( targetX, 0, tile->GetRowColumn()[0]*WORLD_CHUNKSIZE );  
	}
	
	strValue.Format(_T("%6.2f"),targetX);
	m_editTargetX.SetWindowText(strValue);

	m_editTargetY.GetWindowText( strValue );
	targetY	= _tstof( strValue );
	if (nMapId == -1 || nMapId == tile->GetMapId())  
	{
		targetY = ZnClamp<flt32>( targetY, 0, tile->GetRowColumn()[1]*WORLD_CHUNKSIZE );  
	}
	
	strValue.Format(_T("%6.2f"),targetY);
	m_editTargetY.SetWindowText(strValue);

	m_editTargetDir.GetWindowText( strValue );
	targetDir	= _tstof( strValue );
	targetDir = ZnClamp<flt32>( targetDir, -360.f, 360.0f );
	strValue.Format(_T("%6.2f"),targetDir);
	m_editTargetDir.SetWindowText(strValue);

	int nRedCheck = m_checkRed.GetCheck();
	int nVestType = m_comboVestType.GetCurSel();
	
	toolTranspot->ApplyTarget(targetX,targetY,targetDir*PI/180.f, nRedCheck, nVestType, nMapId);
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	toolTranspot->ShowPmpModel();

}


void CToolTransportDlg::OnEnKillfocusEdtTargetTile()
{
	// TODO: Add your control notification handler code here
	CToolTransport* toolTranspot = GetToolTransport();
	if (NULL == toolTranspot->m_currTran|| CToolTransport::optMode_Pick != toolTranspot->m_eoptMode)
	{
		return;
	}

	CString strValue;
	m_editTargetFile.GetWindowText( strValue );
	sInt32 mapId = _tstoi( strValue );
	CTransportEditRes* pRes = (CTransportEditRes*)toolTranspot->m_currTran;
	pRes->SetDesMapID(mapId);
// 	char relPath[MAX_PATH];
// 	GetRelativePathToWorldPath(strValue,relPath);
// 	toolTranspot->m_currTran->SetName(relPath);
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
}

void CToolTransportDlg::OnBnClickedChkPicktransport()
{
	CToolTransport* toolTranspot = GetToolTransport();

	if (BST_CHECKED == m_isPickTransport.GetCheck())
	{
		toolTranspot->SetOptMode(CToolTransport::optMode_Pick);
	}
	else
	{
		if (IsDlgButtonChecked(IDC_RADIO_TRANSPORT))
		{
			toolTranspot->SetOptMode(CToolTransport::optMode_Transport);
		}
		else
		{
			toolTranspot->SetOptMode(CToolTransport::optMode_Target);
		}
	}
}

void CToolTransportDlg::OnBnClickedRadioTransport()
{
	CToolTransport* toolTranspot = GetToolTransport();
	if (toolTranspot->m_eoptMode == CToolTransport::optMode_Pick)
	{
		return;
	}
	CheckDlgButton( IDC_RADIO_TARGET, 0 );
	CheckDlgButton( IDC_RADIO_TRANSPORT, 1 );
	toolTranspot->SetOptMode(CToolTransport::optMode_Transport);
}

void CToolTransportDlg::OnBnClickedRadioTarget()
{
	CToolTransport* toolTranspot = GetToolTransport();
	if (toolTranspot->m_eoptMode == CToolTransport::optMode_Pick)
	{
		return;
	}
	CheckDlgButton( IDC_RADIO_TARGET, 1 );
	CheckDlgButton( IDC_RADIO_TRANSPORT, 0 );
	toolTranspot->SetOptMode(CToolTransport::optMode_Target);
}


void CToolTransportDlg::OnBnClickedRadioIstarget()
{
	// TODO: Add your control notification handler code here
	CheckDlgButton( IDC_RADIO_ISTARGET, 1 );
	CheckDlgButton( IDC_RADIO_ISRELIVE, 0 );

	m_checkRed.EnableWindow(FALSE);
	m_comboVestType.EnableWindow(FALSE);
}

void CToolTransportDlg::OnBnClickedRadioIsrelive()
{
	// TODO: Add your control notification handler code here
	CheckDlgButton( IDC_RADIO_ISTARGET, 0 );
	CheckDlgButton( IDC_RADIO_ISRELIVE, 1 );

	m_checkRed.EnableWindow(TRUE);
	m_comboVestType.EnableWindow(TRUE);
}

