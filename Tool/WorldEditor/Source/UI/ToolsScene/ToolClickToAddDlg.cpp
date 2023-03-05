/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolClick2AddDlg.cpp
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "Resource/Resource.h"
#include "Edit/ToolClicktoAdd.h"
#include "Edit/ToolManager.h"
#include "ToolClicktoAddDlg.h"
#include "Ndl/NdlWorldEditor.h"
#include "MeTerrain/NdlResMgr.h"
#include "EditRes/NdlEditRes.h"
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolClick2AddDlg, CDialog)

CToolClick2AddDlg::CToolClick2AddDlg(CToolClick2AddDlg* pParent)
: CDialog(CToolClick2AddDlg::IDD, pParent)
{
}

CToolClick2AddDlg::~CToolClick2AddDlg()
{
	
}

void CToolClick2AddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolClick2AddDlg)
	DDX_Control(pDX, IDC_EDT_CLICK2ADD_X, m_editClick2AddX);
	DDX_Control(pDX, IDC_EDT_CLICK2ADD_Y, m_editClick2AddY);
	DDX_Control(pDX, IDC_EDT_CLICK2ADD_Z, m_editClick2AddZ);
	DDX_Control(pDX, IDC_SPIN_CLICK2ADD_X, m_spinClick2AddX);
	DDX_Control(pDX, IDC_SPIN_CLICK2ADD_Y, m_spinClick2AddY);
	DDX_Control(pDX, IDC_SPIN_CLICK2ADD_Z, m_spinClick2AddZ);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CHK_PICKCLICK2ADD, m_isPickClick2Add);
	DDX_Control(pDX, IDC_EDT_CLICK2ADD_INDEX, m_editIndex);
	DDX_Control(pDX, IDC_EDT_CLICK2ADD_NAME, m_editName);
	DDX_Control(pDX, IDC_LIST_CLICK2ADD, m_Click2AddList);
	DDX_Control(pDX, IDC_EDT_SOUNDPOINT, m_editMusic);
	DDX_Control(pDX, IDC_EDT_CLICK2ADD_Value0, m_editValue0);
	DDX_Control(pDX, IDC_EDT_CLICK2ADD_Value1, m_editValue1);
	DDX_Control(pDX, IDC_SPIN_CLICK2ADD_Value0, m_spinValue0);
	DDX_Control(pDX, IDC_SPIN_CLICK2ADD_Value1, m_spinValue1);
}
BEGIN_MESSAGE_MAP(CToolClick2AddDlg, CDialog)
	//{{AFX_MSG_MAP(CToolClick2AddDlg)
	ON_EN_KILLFOCUS(IDC_EDT_CLICK2ADD_X, &CToolClick2AddDlg::OnEnKillfocusEdtClick2AddPoint)
	ON_EN_KILLFOCUS(IDC_EDT_CLICK2ADD_Y, &CToolClick2AddDlg::OnEnKillfocusEdtClick2AddPoint)
	ON_EN_KILLFOCUS(IDC_EDT_CLICK2ADD_Z, &CToolClick2AddDlg::OnEnKillfocusEdtClick2AddPoint)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHK_PICKCLICK2ADD, &CToolClick2AddDlg::OnBnClickedChkPick)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_CLICK2ADD, &CToolClick2AddDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_RADIO_SOUNDPOINT, &CToolClick2AddDlg::OnBnClickedRadioSoundPoint)
	ON_BN_CLICKED(IDC_RADIO_ADDNPC, &CToolClick2AddDlg::OnBnClickedRadioNPC)
	ON_LBN_SELCHANGE(IDC_LIST_CLICK2ADD, &CToolClick2AddDlg::OnLbnSelchangeListClick2add)
	ON_EN_KILLFOCUS(IDC_EDT_CLICK2ADD_NAME, &CToolClick2AddDlg::OnEnKillfocusEdtClick2addName)
	ON_EN_KILLFOCUS(IDC_EDT_SOUNDPOINT, &CToolClick2AddDlg::OnEnKillfocusEdtSoundpoint)
	ON_EN_KILLFOCUS(IDC_EDT_CLICK2ADD_Value0, &CToolClick2AddDlg::OnEnKillfocusEdtClick2addValue0)
	ON_EN_KILLFOCUS(IDC_EDT_CLICK2ADD_Value1, &CToolClick2AddDlg::OnEnKillfocusEdtClick2addValue1)
END_MESSAGE_MAP()

BOOL CToolClick2AddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

// 	m_editTargetFile.Initialize(this, BES_XT_CHOOSEFILE);
// 
// 	m_editTargetFile.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );
// 	m_editTargetFile.SetDlgFilter(_T("*.mew"));

	m_spinClick2AddX.SetBuddy( &m_editClick2AddX );
	m_spinClick2AddX.SetRange32( 0, 0xfffffff);  
	m_spinClick2AddX.SetPos( 0 );

	m_spinClick2AddY.SetBuddy( &m_editClick2AddY );
	m_spinClick2AddY.SetRange32( 0, 0xfffffff);  
	m_spinClick2AddY.SetPos( 0 );

	m_spinClick2AddZ.SetBuddy( &m_editClick2AddZ );
	m_spinClick2AddZ.SetRange32( 0, 0xfffffff);  
	m_spinClick2AddZ.SetPos( 0 );

	m_spinValue0.SetBuddy( &m_editValue0 );
	m_spinValue0.SetRange32( 0, 0xfffffff);  
	m_spinValue0.SetPos( 0 );

	m_spinValue1.SetBuddy( &m_editValue1 );
	m_spinValue1.SetRange32( 0, 0xfffffff);  
	m_spinValue1.SetPos( 0 );

	m_editMusic.Initialize(this, BES_XT_CHOOSEFILE);
	m_editMusic.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );


	UpdateData( FALSE );

	return TRUE;
}

void CToolClick2AddDlg::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( (nSBCode==SB_THUMBPOSITION) ) {
		switch( pScrollBar->GetDlgCtrlID() ) {
		case IDC_SPIN_CLICK2ADD_X:
		case IDC_SPIN_CLICK2ADD_Y:
		case IDC_SPIN_CLICK2ADD_Z:
			OnEnKillfocusEdtClick2AddPoint();
			break;
		default:
			break;
		}
	}
	CDialog::OnVScroll( nSBCode, nPos, pScrollBar );
}


void CToolClick2AddDlg::RefreshClick2Add(CSoundPointEditRes* res)
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CToolClick2Add* Click2Addsport		= GetToolClick2Add();
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;

	strValue.Format(_T("%d"),res->GetId());
	m_editIndex.SetWindowText(strValue);

	m_editName.SetWindowText(res->GetName());

	float x	= res->GetPosX();
	strValue.Format(_T("%6.2f"),x);
	m_spinClick2AddX.SetPos( ZnFloat2Int( x ) );
	m_editClick2AddX.SetWindowText(strValue);

	float y	= res->GetPosY();
	strValue.Format(_T("%6.2f"),y);
	m_spinClick2AddY.SetPos( ZnFloat2Int( y ) );
	m_editClick2AddY.SetWindowText(strValue);

	{
		float z = res->GetPosZ();
		strValue.Format(_T("%6.2f"),z);
		m_spinClick2AddZ.SetPos( ZnFloat2Int( z ) );
		m_editClick2AddZ.SetWindowText(strValue);
	}
	if (res->GetMuiscPath())
	{
		strValue.Format("%s\\%s",CWorld::GetAppDataCharDir(),res->GetMuiscPath());
	}
	else
	{
		strValue = '\0';
	}
	m_editMusic.SetWindowText( strValue );

	float fmin = res->GetMinDistance();
	strValue.Format(_T("%6.2f"),fmin);
	m_spinValue0.SetPos( ZnFloat2Int( fmin ) );
	m_editValue0.SetWindowText(strValue);

	float fmax = res->GetMaxDistance();
	strValue.Format(_T("%6.2f"),fmax);
	m_spinValue1.SetPos( ZnFloat2Int( fmax ) );
	m_editValue1.SetWindowText(strValue);
		
}

void CToolClick2AddDlg::SetActive( bool isModify )
{

	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_CLICK2ADD );
	CToolClick2Add* toolClick2Add = GetToolClick2Add();

	Assert( NULL != toolClick2Add );

	toolClick2Add->Bind( this );

	toolClick2Add->Reset();
	OnBnClickedRadioSoundPoint();
	UpdateClick2AddList();
	m_isPickClick2Add.SetCheck(0);
	UpdateData(FALSE);

}





CToolClick2Add* CToolClick2AddDlg::GetToolClick2Add()
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();

	return (CToolClick2Add*)( toolManager->GetActiveTool() );
}

void CToolClick2AddDlg::OnEnKillfocusEdtClick2AddPoint()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CToolClick2Add* toolClick2Add = GetToolClick2Add();
	if (NULL == toolClick2Add->m_currClick2Add )
		return;
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
	float x,y,z;
	m_editClick2AddX.GetWindowText( strValue );
	x	= _tstof( strValue );
	x = ZnClamp<flt32>( x,0, tile->GetRowColumn()[0]*WORLD_CHUNKSIZE);
	strValue.Format(_T("%6.2f"),x);
	m_editClick2AddX.SetWindowText(strValue);

	m_editClick2AddY.GetWindowText( strValue );
	y	= _tstof( strValue );
	y = ZnClamp<flt32>( y, 0, tile->GetRowColumn()[1]*WORLD_CHUNKSIZE );
	strValue.Format(_T("%6.2f"),y);
	m_editClick2AddY.SetWindowText(strValue);

	{
		m_editClick2AddZ.GetWindowText( strValue );
		z	= _tstof( strValue );
		z = ZnClamp<flt32>( z, -36000.f, 36000.0f );
	}
	strValue.Format(_T("%6.2f"),z);
	m_editClick2AddZ.SetWindowText(strValue);


	
	toolClick2Add->ApplyClick2Add(x,y,z);
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	toolClick2Add->ShowPmpModel();
}




void CToolClick2AddDlg::OnBnClickedChkPick()
{
	CToolClick2Add* toolClick2Add = GetToolClick2Add();

	if (BST_CHECKED == m_isPickClick2Add.GetCheck())
	{
		toolClick2Add->SetOptMode(CToolClick2Add::optMode_Pick);
	}
	else
	{
		toolClick2Add->SetOptMode(CToolClick2Add::optMode_AddClick2Add);
	}

}





void CToolClick2AddDlg::OnBnClickedButtonDelete()
{
	GetToolClick2Add()->DeletePointModel();
}


void CToolClick2AddDlg::UpdateClick2AddList()
{
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	m_Click2AddList.ResetContent();

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	CString strName;
	if (	m_eClick2AddToolMode == SOUND_POINT_MODE)
	{
		for( sInt32 i=0; i<resMgr->GetSoundPointCount(); i++ ) 
		{
			CSoundPointEditRes* p	= (CSoundPointEditRes*)(resMgr->SoundPoint(i));
			Assert( NULL != p );
			strName			= p->GetName();
			m_Click2AddList.InsertString(p->GetId(), strName );
			p->ShowSoundPointPoint(true);
		}
	}
	else
	{
	}
}

void CToolClick2AddDlg::OnBnClickedRadioSoundPoint()
{
	CheckDlgButton( IDC_RADIO_SOUNDPOINT, 1 );
	CheckDlgButton( IDC_RADIO_ADDNPC, 0 );
	m_eClick2AddToolMode = SOUND_POINT_MODE;
	UpdateClick2AddList();
	GetToolClick2Add()->SetCurrClick2Add(NULL);
}
void CToolClick2AddDlg::OnBnClickedRadioNPC()
{
	CheckDlgButton( IDC_RADIO_SOUNDPOINT, 1 );
	CheckDlgButton( IDC_RADIO_ADDNPC, 0 );
	return;
	CheckDlgButton( IDC_RADIO_SOUNDPOINT, 0 );
	CheckDlgButton( IDC_RADIO_ADDNPC, 1 );
	m_eClick2AddToolMode = NPC_MODE;
	UpdateClick2AddList();
	GetToolClick2Add()->SetCurrClick2Add(NULL);
}

void CToolClick2AddDlg::OnLbnSelchangeListClick2add()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CWorldTile* tile = CURRENTTILE;
	CResEditMgr* pResMgr = (CResEditMgr*)tile->GetCResMgr();
	int sel = m_Click2AddList.GetCurSel();
	if (SOUND_POINT_MODE == m_eClick2AddToolMode)
	{
		GetToolClick2Add()->SetCurrClick2Add((CSoundPointEditRes*)pResMgr->SoundPoint(sel));
	}
	else
	{
	}
}

void CToolClick2AddDlg::OnEnKillfocusEdtClick2addName()
{
	// TODO: Add your control notification handler code here
	CToolClick2Add* toolRoute = GetToolClick2Add();
	if (NULL == toolRoute->m_currClick2Add)
	{
		return;
	}
	CSoundPointEditRes* pRes = (CSoundPointEditRes*)toolRoute->m_currClick2Add;
	CString strValue;

	m_editName.GetWindowText( strValue );
	pRes->SetName(strValue);
	m_Click2AddList.DeleteString(pRes->GetId());
	m_Click2AddList.InsertString(pRes->GetId(),strValue);


	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
}

void CToolClick2AddDlg::OnEnKillfocusEdtSoundpoint()
{
	if (!SwGlobal::GetWorld()||!SwGlobal::GetWorld()->GetWorldBuffer())
	{
		return;
	}
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CToolClick2Add* toolRoute = GetToolClick2Add();
	if (NULL == toolRoute->m_currClick2Add)
	{
		return;
	}

	CString strValue;
	m_editMusic.GetWindowText(strValue);
	char musicPath[MAX_PATH*2];
	if( (strValue.GetLength()>0) )	{
		toolRoute->GetRelativePath(strValue.GetString(),musicPath);
	}
	else {
		memset(musicPath,0,sizeof(char)*MAX_PATH*2);
	}
	toolRoute->m_currClick2Add->SetMuiscPath(musicPath);
}

void CToolClick2AddDlg::OnEnKillfocusEdtClick2addValue0()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CToolClick2Add* toolClick2Add = GetToolClick2Add();
	if (NULL == toolClick2Add->m_currClick2Add )
		return;
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
	float fvalue;

	{
		m_editValue0.GetWindowText( strValue );
		fvalue	= _tstof( strValue );
		fvalue = ZnClamp<flt32>( fvalue, 0.f, tile->GetRowColumn()[1]*WORLD_CHUNKSIZE*1.4);
	}
	strValue.Format(_T("%6.2f"),fvalue);
	m_editValue0.SetWindowText(strValue);


	toolClick2Add->m_currClick2Add->SetMinDistance(fvalue);
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	toolClick2Add->ShowPmpModel();
}

void CToolClick2AddDlg::OnEnKillfocusEdtClick2addValue1()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CToolClick2Add* toolClick2Add = GetToolClick2Add();
	if (NULL == toolClick2Add->m_currClick2Add )
		return;
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
	float fvalue;

	{
		m_editValue1.GetWindowText( strValue );
		fvalue	= _tstof( strValue );
		fvalue = ZnClamp<flt32>( fvalue, 0, tile->GetRowColumn()[1]*WORLD_CHUNKSIZE*1.4 );
	}
	strValue.Format(_T("%6.2f"),fvalue);
	m_editValue1.SetWindowText(strValue);


	
	toolClick2Add->m_currClick2Add->SetMaxDistance(fvalue);
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	toolClick2Add->ShowPmpModel();
}
