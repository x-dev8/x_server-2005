/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolFlyRouteDlg.cpp
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "Resource/Resource.h"
#include "Edit/ToolFlyRoute.h"
#include "Edit/ToolManager.h"
#include "ToolFlyRouteDlg.h"
#include "Ndl/NdlWorldEditor.h"
#include "MeTerrain/NdlResMgr.h"
#include "EditRes/NdlEditRes.h"
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolRouteDlg, CDialog)

CToolRouteDlg::CToolRouteDlg(CToolRouteDlg* pParent)
: CDialog(CToolRouteDlg::IDD, pParent)
{
}

CToolRouteDlg::~CToolRouteDlg()
{
	
}

void CToolRouteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolFlyRouteDlg)
	DDX_Control(pDX, IDC_EDT_FLYROUTE_X, m_editRouteX);
	DDX_Control(pDX, IDC_EDT_FLYROUTE_Y, m_editRouteY);
	DDX_Control(pDX, IDC_EDT_FLYROUTE_Z, m_editFlyRouteZ);
	DDX_Control(pDX, IDC_SPIN_FLYROUTE_X, m_spinRouteX);
	DDX_Control(pDX, IDC_SPIN_FLYROUTE_Y, m_spinRouteY);
	DDX_Control(pDX, IDC_SPIN_FLYROUTE_Z, m_spinFlyRouteZ);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CHK_PICKFLYROUTE, m_isPickRoute);
	DDX_Control(pDX, IDC_EDT_ROUTE_INDEX, m_editIndex);
	DDX_Control(pDX, IDC_EDT_ROUTE_NAME, m_editName);
	DDX_Control(pDX, IDC_EDT_NEXT_MAP, m_editNextMapID);
	DDX_Control(pDX, IDC_EDT_NEXT_ROUTE, m_editNextRouteID);
	DDX_Control(pDX, IDC_LIST_FLYROUTE, m_RouteList);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_radio_NPC);
	DDX_Control(pDX, IDC_EDT_WALK_SPEED, m_edit_NPC_Walk_Speed);
	DDX_Control(pDX, IDC_EDT_WALK_LENGTH, m_edit_NPC_Walk_Length);
	DDX_Control(pDX, IDC_EDT_STAY_TIME, m_edit_NPC_Stay_Time);
	DDX_Control(pDX, IDC_EDT_STAY_ACTION, m_edit_StayAction);
}
BEGIN_MESSAGE_MAP(CToolRouteDlg, CDialog)
	//{{AFX_MSG_MAP(CToolFlyRouteDlg)
	ON_EN_KILLFOCUS(IDC_EDT_FLYROUTE_X, &CToolRouteDlg::OnEnKillfocusEdtRoutePoint)
	ON_EN_KILLFOCUS(IDC_EDT_FLYROUTE_Y, &CToolRouteDlg::OnEnKillfocusEdtRoutePoint)
	ON_EN_KILLFOCUS(IDC_EDT_FLYROUTE_Z, &CToolRouteDlg::OnEnKillfocusEdtRoutePoint)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
	ON_EN_KILLFOCUS(IDC_EDT_ROUTE_NAME, &CToolRouteDlg::OnEnKillfocusEdtRoute)
	ON_EN_KILLFOCUS(IDC_EDT_NEXT_MAP, &CToolRouteDlg::OnEnKillfocusEdtRoute)
	ON_EN_KILLFOCUS(IDC_EDT_NEXT_ROUTE, &CToolRouteDlg::OnEnKillfocusEdtRoute)
	ON_BN_CLICKED(IDC_CHK_PICKFLYROUTE, &CToolRouteDlg::OnBnClickedChkPick)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CToolRouteDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CToolRouteDlg::OnBnClickedButtonDelete)
	ON_LBN_SELCHANGE(IDC_LIST_FLYROUTE, &CToolRouteDlg::OnLbnSelchangeListFlyroute)
	ON_BN_CLICKED(IDC_RADIO_NPC, &CToolRouteDlg::OnBnClickedRadioNpc)
	ON_EN_KILLFOCUS(IDC_EDT_WALK_SPEED, &CToolRouteDlg::OnEnKillfocusEdtWalkSpeed)
	ON_EN_KILLFOCUS(IDC_EDT_WALK_LENGTH, &CToolRouteDlg::OnEnKillfocusEdtWalkLength)
	ON_EN_KILLFOCUS(IDC_EDT_STAY_TIME, &CToolRouteDlg::OnEnKillfocusEdtStayTime)
	ON_BN_CLICKED(IDC_RADIO_FLY, &CToolRouteDlg::OnBnClickedRadioFly)
	ON_EN_KILLFOCUS(IDC_EDT_STAY_ACTION, &CToolRouteDlg::OnEnKillfocusEdtStayAction)
	ON_BN_CLICKED(IDC_BUTTON_GenerateClosedRoute, &CToolRouteDlg::OnBnClickedButtonGenerateclosedroute)
END_MESSAGE_MAP()

BOOL CToolRouteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

// 	m_editTargetFile.Initialize(this, BES_XT_CHOOSEFILE);
// 
// 	m_editTargetFile.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );
// 	m_editTargetFile.SetDlgFilter(_T("*.mew"));

	m_spinRouteX.SetBuddy( &m_editRouteX );
	m_spinRouteX.SetRange32( 0, 0xfffffff);  
	m_spinRouteX.SetPos( 0 );

	m_spinRouteY.SetBuddy( &m_editRouteY );
	m_spinRouteY.SetRange32( 0, 0xfffffff);  
	m_spinRouteY.SetPos( 0 );

	m_spinFlyRouteZ.SetBuddy( &m_editFlyRouteZ );
	m_spinFlyRouteZ.SetRange32( 0, 0xfffffff);  
	m_spinFlyRouteZ.SetPos( 0 );



	UpdateData( FALSE );

	return TRUE;
}

void CToolRouteDlg::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( (nSBCode==SB_THUMBPOSITION) ) {
		switch( pScrollBar->GetDlgCtrlID() ) {
		case IDC_SPIN_FLYROUTE_X:
		case IDC_SPIN_FLYROUTE_Y:
		case IDC_SPIN_FLYROUTE_Z:
			OnEnKillfocusEdtRoutePoint();
			break;
		default:
			break;
		}
	}

	//CDialog::OnVScroll( nSBCode, nPos, pScrollBar );
}


void CToolRouteDlg::RefreshFlyRoute(CRouteRes* res)
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CToolRoute* Routesport		= GetToolRoute();
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
// 	RefreshRoutePoint(res,Routesport->GetSelectedRoutePoint());

	strValue.Format(_T("%d"),res->GetId());
	m_editIndex.SetWindowText(strValue);

	m_editName.SetWindowText(res->GetName());

// 	if (res->IsFlyRoute())
	{
		CNPCRouteRes* RouteRes = (CNPCRouteRes*)res;
		strValue.Format(_T("%d"),RouteRes->GetNextRouteID());
		m_editNextRouteID.SetWindowText(strValue);

		strValue.Format(_T("%d"),RouteRes->GetNextMapID());
		m_editNextMapID.SetWindowText(strValue);
	}
// 	else
// 	{
// 
// 	}

		
}

void CToolRouteDlg::SetActive( bool isModify )
{

	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_FLYROUTE );
	CToolRoute* toolFlyRoute = GetToolRoute();

	Assert( NULL != toolFlyRoute );

	toolFlyRoute->Bind( this );

	toolFlyRoute->Reset();
	OnBnClickedRadioNpc();
	UpdateRouteList();
	m_isPickRoute.SetCheck(0);
	UpdateData(FALSE);

}





CToolRoute* CToolRouteDlg::GetToolRoute()
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();

	return (CToolRoute*)( toolManager->GetActiveTool() );
}

void CToolRouteDlg::OnEnKillfocusEdtRoutePoint()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CToolRoute* toolRoute = GetToolRoute();
	if (NULL == toolRoute->m_currRoute || CToolRoute::optMode_Pick != toolRoute->m_eoptMode)
		return;
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
	float x,y,z;
	m_editRouteX.GetWindowText( strValue );
	x	= _tstof( strValue );
	x = ZnClamp<flt32>( x,0, tile->GetRowColumn()[0]*WORLD_CHUNKSIZE);
	strValue.Format(_T("%6.2f"),x);
	m_editRouteX.SetWindowText(strValue);

	m_editRouteY.GetWindowText( strValue );
	y	= _tstof( strValue );
	y = ZnClamp<flt32>( y, 0, tile->GetRowColumn()[1]*WORLD_CHUNKSIZE );
	strValue.Format(_T("%6.2f"),y);
	m_editRouteY.SetWindowText(strValue);

	if (NPC_ROUTE_MODE == m_eRouteToolMode)
	{
		BOOL bInfloor = FALSE;
		z = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,x,y,0,&bInfloor);
	}
	else
	{
		m_editFlyRouteZ.GetWindowText( strValue );
		z	= _tstof( strValue );
		z = ZnClamp<flt32>( z, -36000.f, 36000.0f );
	}
	strValue.Format(_T("%6.2f"),z);
	m_editFlyRouteZ.SetWindowText(strValue);

	//toolRoute->ApplyFlyRoute(x,y,z);
	toolRoute->DoChangeRoutePointPosition((CNPCRouteRes *)toolRoute->m_currRoute, toolRoute->m_SelectedRoutePoint, x, y, z);

	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	toolRoute->ShowPmpModel();
}




void CToolRouteDlg::OnEnKillfocusEdtRoute()
{
	// TODO: Add your control notification handler code here
	CToolRoute* toolRoute = GetToolRoute();
	if (NULL == toolRoute->m_currRoute)
	{
		return;
	}
	CRouteRes* pRes = (CRouteRes*)toolRoute->m_currRoute;
	CString strValue;
	CString strName;

	m_editName.GetWindowText(strName);

	//pRes->SetName(strValue);

	int nCutSel = m_RouteList.GetCurSel();
	m_RouteList.DeleteString(nCutSel);
	m_RouteList.InsertString(nCutSel,strName);
	m_RouteList.SetCurSel(nCutSel);
	m_RouteList.SetItemDataPtr(nCutSel,pRes);

// 	if(m_eRouteToolMode != NPC_ROUTE_MODE)
//	{
// 		assert(pRes->IsFlyRoute());
		CNPCRouteRes* pFlyRes = (CNPCRouteRes*)pRes;
		m_editNextMapID.GetWindowText( strValue );
		sInt32 mapId = _tstoi(strValue);
		mapId = ZnClamp<sInt32>( mapId, -1, 0xfffffff );
		strValue.Format(_T("%d"),mapId);
		m_editNextMapID.SetWindowText(strValue);

		//pFlyRes->SetNextMapID(mapId);

		m_editNextRouteID.GetWindowText( strValue );
		sInt32 routeId = _tstoi( strValue );
		routeId = ZnClamp<sInt32>( routeId, -1, 0xfffffff );
		strValue.Format(_T("%d"),routeId);
		m_editNextRouteID.SetWindowText(strValue);

		//pFlyRes->SetNextRouteID(routeId);
//	}

	toolRoute->DoChangeRouteProperty((CNPCRouteRes*)toolRoute->m_currRoute, strName, mapId, routeId);

	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
}

void CToolRouteDlg::OnBnClickedChkPick()
{
	CToolRoute* toolRoute = GetToolRoute();

	if (BST_CHECKED == m_isPickRoute.GetCheck())
	{
		toolRoute->SetOptMode(CToolRoute::optMode_Pick);
	}
	else
	{
		toolRoute->SetOptMode(CToolRoute::optMode_AddRoute);
	}

}


void CToolRouteDlg::RefreshRoutePoint( CRouteRes* res, int index )
{
	if (index == -1)
	{
		return;
	}
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
	float x	= res->GetPosX(index);
	strValue.Format(_T("%6.2f"),x);
	m_spinRouteX.SetPos( ZnFloat2Int( x ) );
	m_editRouteX.SetWindowText(strValue);

	float y	= res->GetPosY(index);
	strValue.Format(_T("%6.2f"),y);
	m_spinRouteY.SetPos( ZnFloat2Int( y ) );
	m_editRouteY.SetWindowText(strValue);

	CNPCRouteRes* RouteRes = (CNPCRouteRes*)res;
	float fwalkSpeed	= RouteRes->GetWalkSpeed(index);
	strValue.Format(_T("%6.2f"),fwalkSpeed);
	m_edit_NPC_Walk_Speed.SetWindowText(strValue);

	float fwalkLength	= RouteRes->GetWalkLength(index);
	strValue.Format(_T("%6.2f"),fwalkLength);
	m_edit_NPC_Walk_Length.SetWindowText(strValue);

	sInt32 fstayTime	= RouteRes->GetStayTime(index);
	strValue.Format(_T("%d"),fstayTime);
	m_edit_NPC_Stay_Time.SetWindowText(strValue);

	sInt32 fstayAction	= RouteRes->GetStayAction(index);
	strValue.Format(_T("%d"),fstayAction);
	m_edit_StayAction.SetWindowText(strValue);
	if (res->IsFlyRoute())
	{
		float z = RouteRes->GetPosZ(index);
		strValue.Format(_T("%6.2f"),z);
		m_spinFlyRouteZ.SetPos( ZnFloat2Int( z ) );
		m_editFlyRouteZ.SetWindowText(strValue);
	}
}


void CToolRouteDlg::OnBnClickedButtonAdd()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CWorldTile* tile = CURRENTTILE;
	CResEditMgr* pResMgr = (CResEditMgr*)tile->GetCResMgr();
	CRouteRes* pRes = NULL;

	CString strValue;
	m_editName.GetWindowText( strValue );

	/*
	if (NPC_ROUTE_MODE == m_eRouteToolMode)
	{
		pRes = pResMgr->PushNPCRoute(strValue);
	}
	else
	{
		pRes = pResMgr->PushFlyRoute(strValue);
	}


	*/

	CToolRoute *toolRoute = GetToolRoute();
	if(NULL == toolRoute)
		return;

	if(!toolRoute->DoAddRoute(strValue, FLY_ROUTE_MODE == m_eRouteToolMode))
		return;
	pRes = toolRoute->GetResMgr()->NPCRoute(toolRoute->GetResMgr()->GetNPCRouteCount() - 1);

	toolRoute->SetCurrRoute(pRes);
	int index = m_RouteList.AddString(strValue );
	m_RouteList.SetItemDataPtr(index,pRes);
	m_RouteList.SetCurSel(index);

}

void CToolRouteDlg::OnBnClickedButtonDelete()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CWorldTile* tile = CURRENTTILE;
	CResEditMgr* pResMgr = (CResEditMgr*)tile->GetCResMgr();
	int sel = m_RouteList.GetCurSel();
	if ( sel == -1 )
	{
		return;
	}
	CNPCRouteRes* pRes = (CNPCRouteRes*)m_RouteList.GetItemDataPtr(sel);
	//pResMgr->DeleteNPCRoute(pRes->GetId());

	CToolRoute *toolRoute = GetToolRoute();
	if(NULL == toolRoute)
		return;

	toolRoute->DoDeleteRoute(pRes);

	m_RouteList.DeleteString(sel);
	GetToolRoute()->SetCurrRoute(NULL);
	//CWorldEditDoc::GetActiveMapDoc()->SetWorldModify();
}

void CToolRouteDlg::OnLbnSelchangeListFlyroute()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	CWorldTile* tile = CURRENTTILE;
	CResEditMgr* pResMgr = (CResEditMgr*)tile->GetCResMgr();
	int sel = m_RouteList.GetCurSel();
	GetToolRoute()->SetCurrRoute((CRouteRes*)m_RouteList.GetItemDataPtr(sel));
}

void CToolRouteDlg::UpdateRouteList()
{
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	m_RouteList.ResetContent();

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	CString strName;
	for( sInt32 i=0; i<resMgr->GetNPCRouteCount(); i++ ) 
	{
		CNPCRouteRes* p	= (resMgr->NPCRoute(i));
		if (p->IsFlyRoute() == 
			(m_eRouteToolMode == FLY_ROUTE_MODE))
		{
			Assert( NULL != p );
			strName			= p->GetName();
			int nIndex = m_RouteList.AddString(strName);
			m_RouteList.SetItemDataPtr(nIndex,p);
		}
	}
	if (m_RouteList.GetCount() > 0)
	{
		m_RouteList.SetCurSel(0);
		GetToolRoute()->SetCurrRoute((CRouteRes*)m_RouteList.GetItemDataPtr(0));
	}
	else
	{
		GetToolRoute()->SetCurrRoute(NULL);
	}
}

void CToolRouteDlg::OnEnKillfocusEdtWalkSpeed()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	if (m_eRouteToolMode != NPC_ROUTE_MODE)
	{
		return;
	}
	CToolRoute* toolRoute = GetToolRoute();
	if (NULL == toolRoute->m_currRoute || CToolRoute::optMode_Pick != toolRoute->m_eoptMode)
		return;
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
	float fWalkSpeed;
	m_edit_NPC_Walk_Speed.GetWindowText( strValue );
	fWalkSpeed	= _tstof( strValue );

	if (toolRoute->GetSelectedRoutePoint() != -1)
	{
		assert(!toolRoute->m_currRoute->IsFlyRoute());
		CNPCRouteRes* npcRes = (CNPCRouteRes*)toolRoute->m_currRoute;

		//npcRes->SetWalkSpeed(toolRoute->GetSelectedRoutePoint(),fWalkSpeed);
		CNPCRouteRes::SNpcRoutePoint *pNpcPoint = npcRes->GetRoutePoint(toolRoute->GetSelectedRoutePoint());
		if(NULL == pNpcPoint)
			return;
		pNpcPoint->mWalkSpeed = fWalkSpeed;
		toolRoute->DoChangeRoutePointProperty(npcRes, toolRoute->GetSelectedRoutePoint(), *pNpcPoint);

		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	}


	toolRoute->ShowPmpModel();
}

void CToolRouteDlg::OnEnKillfocusEdtWalkLength()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	if (m_eRouteToolMode != NPC_ROUTE_MODE)
	{
		return;
	}
	CToolRoute* toolRoute = GetToolRoute();
	if (NULL == toolRoute->m_currRoute || CToolRoute::optMode_Pick != toolRoute->m_eoptMode)
		return;
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
	float fWalkLength;
	m_edit_NPC_Walk_Length.GetWindowText( strValue );
	fWalkLength	= _tstof( strValue );

	if (toolRoute->GetSelectedRoutePoint() != -1)
	{
		assert(!toolRoute->m_currRoute->IsFlyRoute());
		CNPCRouteRes* npcRes = (CNPCRouteRes*)toolRoute->m_currRoute;

		//npcRes->SetWalkLength(toolRoute->GetSelectedRoutePoint(),fWalkLength);
		CNPCRouteRes::SNpcRoutePoint *pNpcPoint = npcRes->GetRoutePoint(toolRoute->GetSelectedRoutePoint());
		if(NULL == pNpcPoint)
			return;
		pNpcPoint->mWalkLenght = fWalkLength;
		toolRoute->DoChangeRoutePointProperty(npcRes, toolRoute->GetSelectedRoutePoint(), *pNpcPoint);

		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	}
}

void CToolRouteDlg::OnEnKillfocusEdtStayTime()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	if (m_eRouteToolMode != NPC_ROUTE_MODE)
	{
		return;
	}
	CToolRoute* toolRoute = GetToolRoute();
	if (NULL == toolRoute->m_currRoute || CToolRoute::optMode_Pick != toolRoute->m_eoptMode)
		return;
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
	sInt32 nStayTime;
	m_edit_NPC_Stay_Time.GetWindowText( strValue );
	nStayTime	= _tstoi( strValue );

	if (toolRoute->GetSelectedRoutePoint() != -1)
	{
		assert(!toolRoute->m_currRoute->IsFlyRoute());
		CNPCRouteRes* npcRes = (CNPCRouteRes*)toolRoute->m_currRoute;

		//npcRes->SetStayTime(toolRoute->GetSelectedRoutePoint(),nStayTime);
		CNPCRouteRes::SNpcRoutePoint *pNpcPoint = npcRes->GetRoutePoint(toolRoute->GetSelectedRoutePoint());
		if(NULL == pNpcPoint)
			return;
		pNpcPoint->mStayTime = nStayTime;
		toolRoute->DoChangeRoutePointProperty(npcRes, toolRoute->GetSelectedRoutePoint(), *pNpcPoint);

		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	}
}

void CToolRouteDlg::OnBnClickedRadioNpc()
{
	CheckDlgButton( IDC_RADIO_NPC, 1 );
	CheckDlgButton( IDC_RADIO_FLY, 0 );
	m_eRouteToolMode = NPC_ROUTE_MODE;
	UpdateRouteList();
}
void CToolRouteDlg::OnBnClickedRadioFly()
{
	CheckDlgButton( IDC_RADIO_NPC, 0 );
	CheckDlgButton( IDC_RADIO_FLY, 1 );
	m_eRouteToolMode = FLY_ROUTE_MODE;
	UpdateRouteList();
}

void CToolRouteDlg::OnEnKillfocusEdtStayAction()
{
	if (NULL ==CURRENTTILE )
	{
		return;
	}
	if (m_eRouteToolMode != NPC_ROUTE_MODE)
	{
		return;
	}
	CToolRoute* toolRoute = GetToolRoute();
	if (NULL == toolRoute->m_currRoute || CToolRoute::optMode_Pick != toolRoute->m_eoptMode)
		return;
	CWorldTile*		tile = CURRENTTILE;
	CString strValue;
	sInt32 nStayAction;
	m_edit_StayAction.GetWindowText( strValue );
	nStayAction	= _tstoi( strValue );

	if (toolRoute->GetSelectedRoutePoint() != -1)
	{
		assert(!toolRoute->m_currRoute->IsFlyRoute());
		CNPCRouteRes* npcRes = (CNPCRouteRes*)toolRoute->m_currRoute;

		//npcRes->SetStayAction(toolRoute->GetSelectedRoutePoint(),nStayAction);
		CNPCRouteRes::SNpcRoutePoint *pNpcPoint = npcRes->GetRoutePoint(toolRoute->GetSelectedRoutePoint());
		if(NULL == pNpcPoint)
			return;
		pNpcPoint->mStayAction = nStayAction;
		toolRoute->DoChangeRoutePointProperty(npcRes, toolRoute->GetSelectedRoutePoint(), *pNpcPoint);

		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	}
}

void CToolRouteDlg::OnBnClickedButtonGenerateclosedroute()
{
	CToolRoute* tool = GetToolRoute();
	if(NULL == tool || NULL == tool->m_currRoute)
		return;

	if(IDYES == AfxMessageBox(_T("确定要生成闭合路线吗？"), MB_YESNO))
	{
		//((CNPCRouteRes *)tool->m_currRoute)->GenerateCloseRoute(true);

		tool->DoGenerateCloseRoute((CNPCRouteRes *)tool->m_currRoute, true);
	}
}
