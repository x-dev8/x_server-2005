/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolFlyRoute.cpp
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "ToolFlyRoute.h"
#include "OptStack.h"
#include "Ndl/NdlWorldEditor.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/ToolsWnd/ToolFlyRouteDlg.h"
#include "NDL\NdlHelper.h"
#include "rollback\IRouteOperation.h"
#include <sstream>
////////////////////////////////////////////////////////////////////////////////
CToolRoute::CToolRoute()
{
	m_transportDlg  = NULL;
	m_currRoute  = NULL;
	m_SelectedRoutePoint = -1;
	m_eoptMode	= optMode_AddRoute;
	m_pmpRoutePoint = NULL;
}

CToolRoute::~CToolRoute()
{
	SAFE_DELETE( m_selPmpBox );
	if(!m_pmpRoutePoint)
	{
		SAFE_DELETE(m_pmpRoutePoint);
	}
}

bool CToolRoute::Create( CToolManager* toolMgr )
{
	CBaseTool::Create( toolMgr );
	char path[MAX_PATH*2];
	sprintf_s( path, "%s\\Required\\Model\\Box.mex", CWorld::GetAppCharDir() );

	//create the pmpbox
	m_selPmpBox = MeNew TObjectEditInfo();
	if(!m_selPmpBox->LoadFromFile( path ))
		return false;
	return true;



	return true;
}

void CToolRoute::ShowPmpModel(  )
{
	if (m_currRoute == NULL)
	{
		return;
	}
	if( NULL != m_selPmpBox ) 
	{
		flt32 scale = 1.0f;		
		//set scale
		m_selPmpBox->model->SetScale(scale);
// 		//set rotation
// 		float fX, fY, fZ;
// 		m_currRoute->GetModel()->model->GetRotation( fX, fY, fZ );
// 		m_selPmpBox->model->SetRotationX( fX );
// 		m_selPmpBox->model->SetRotationY( fY );
// 		m_selPmpBox->model->SetRotationZ( fZ );
		//set position
		m_selPmpBox->model->SetPosition( m_currRoute->GetPosX(m_SelectedRoutePoint), 
			m_currRoute->GetPosY(m_SelectedRoutePoint),
			m_currRoute->GetPosZ(m_SelectedRoutePoint));
		//update
		m_selPmpBox->Update(0.0f);
	}
}


void CToolRoute::Bind( CToolRouteDlg* dlg )
{
	m_transportDlg = dlg;
}



bool CToolRoute::OnLMouseDown( UINT nFlags, CPoint point )
{
	m_isLDrag	= true;
	m_oldPos	= point; 

	if (NULL == m_currRoute)
	{
		return false;
	}
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	
	sInt32 pickId = view->PickWorldTerrain( point,emPT_FlyRoute|emPT_NpcRoute|emPT_Terrain|emPT_FloorObj );

	if( -1 != pickId ) { 
		const TPickResult& pickResult = view->GetPickResult();
		if( optMode_Pick == m_eoptMode ) 
		{
			sInt32 objId	= -1;


			CString strPmt;
			strPmt.Format( _T("没有选中物体") );

			for( sInt32 i=0; i<pickResult.pickResultCount; i++ ) {
				if( emPT_FlyRoute == pickResult.pickResultInfo[i].resultType || emPT_NpcRoute == pickResult.pickResultInfo[i].resultType ) {
					objId = i;
					break;
				}
			}
			CResEditMgr* resMgr = GetResMgr();	
			if( NULL == resMgr )
				return false;

			if( -1 != objId ) 
			{
				{
					CRouteRes* selRoute = (CRouteRes*)pickResult.pickResultInfo[objId].resultObjInfo;
					SetCurrRoute(selRoute);
					m_SelectedRoutePoint = pickResult.pickResultInfo[objId].resultId;
					m_transportDlg->RefreshRoutePoint(m_currRoute,m_SelectedRoutePoint);


//					g_render->SetSelModel(  pickResult.pickResultInfo[objId].resultId );
					if (m_currRoute->IsFlyRoute())
					{
						strPmt.Format( _T("选中飞行路线\"%s\"第%d个路点"),m_currRoute->GetName(),m_SelectedRoutePoint);
					}
					else
					{
						strPmt.Format( _T("选中npc路线\"%s\"第%d个路点"),m_currRoute->GetName(),m_SelectedRoutePoint);
					}
					ShowPmpModel();
				}
			}
			else 
			{
				if( NULL != m_selPmpBox ) {
					m_selPmpBox->model->SetPosition( 0.0f, 0.0f, 0.0f );
					m_selPmpBox->Update(0.0f);
				}
			}
			theApp.SetPromptText( strPmt );
		}
		else
		{
			int close_id=GetCloseIndex(pickResult,emPT_FlyRoute|emPT_NpcRoute);
			flt32 pos[3];
			for( sInt32 i=0; i<3; i++ ) 
			{
				pos[i] = pickResult.pickResultInfo[close_id].point[i];
			}

			//m_currRoute->AddRoutePoint(pos[0],pos[1],pos[2],true);
			DoAddRoutePoint((CNPCRouteRes *)m_currRoute, pos[0],pos[1],pos[2],true);

			CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
		}
	}
	return true;
}

bool CToolRoute::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;


	return true;
}

bool CToolRoute::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return true;
}

bool CToolRoute::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 

	return true;
}

bool CToolRoute::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;



	return true;
}

bool CToolRoute::OnMouseMove( UINT nFlags, CPoint point )
{
	Vector2 viewSize;
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	view->GetViewSize( viewSize.x, viewSize.y );
	if( viewSize.x < 1 || viewSize.y < 1 )
		return false;

	SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();

	CPoint delta = point - m_oldPos;
	if( m_isRDrag ){	// move
		CameraAdjust(point, nFlags);
	}
	else if( m_isLDrag ) {
		m_oldPos = point;
	}
	else {
		sInt32 pickId = view->PickWorldTerrain( point,emPT_Terrain|emPT_FloorObj );
		if( -1 != pickId ) 
		{ 
			const TPickResult& pickResult = view->GetPickResult();
			if( 		 optMode_Pick != m_eoptMode  ) 
			{
				int close_id=GetCloseIndex(pickResult,0);
				flt32 pos[3];
				for( sInt32 i=0; i<3; i++ ) 
				{
					pos[i] = pickResult.pickResultInfo[close_id].point[i];
				}
				ApplyFlyRoute(pos[0],pos[1],pos[2]);
			}
		}
	}
	camera->Update( 0.0f, 0.0f );

	return true;
}

bool CToolRoute::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (NULL == m_currRoute)
	{
		return false;
	}
	if (m_SelectedRoutePoint == -1)
	{
		return false;
	}
	if( nChar == VK_DELETE ) {
		DeletePointModel();
		return true;
	}
	if( optMode_Pick == m_eoptMode ) {
		flt32 x = m_currRoute->GetPosX(m_SelectedRoutePoint);
		flt32 y = m_currRoute->GetPosY(m_SelectedRoutePoint);
		flt32 z = m_currRoute->GetPosZ(m_SelectedRoutePoint);

		flt32 delta = 0.1f;
		{
			delta	= 0.5f*nRepCnt;
		}
		if( nChar == VK_LEFT ) 
		{
			//m_currRoute->SetPosX(m_SelectedRoutePoint,m_currRoute->GetPosX(m_SelectedRoutePoint)-delta);
			x -= delta;
		}
		else if( nChar == VK_RIGHT ) {
			//m_currRoute->SetPosX(m_SelectedRoutePoint,m_currRoute->GetPosX(m_SelectedRoutePoint)+delta);
			x += delta;
		}
		else if( nChar == VK_DOWN ) 
		{
			//m_currRoute->SetPosY(m_SelectedRoutePoint,m_currRoute->GetPosY(m_SelectedRoutePoint)-delta);
			y -= delta;
		}
		else if( nChar == VK_UP ) 
		{
			//m_currRoute->SetPosY(m_SelectedRoutePoint,m_currRoute->GetPosY(m_SelectedRoutePoint)+delta);
			y += delta;
		}
		else if (nChar == 'w' || nChar == 'W')
		{
			//m_currRoute->SetPosZ(m_SelectedRoutePoint,m_currRoute->GetPosZ(m_SelectedRoutePoint)+delta);
			z += delta;
		}
		else if (nChar == 's' || nChar == 'S')
		{
			//m_currRoute->SetPosZ(m_SelectedRoutePoint,m_currRoute->GetPosZ(m_SelectedRoutePoint)-delta);
			z -= delta;
		}

		DoChangeRoutePointPosition((CNPCRouteRes*)m_currRoute, m_SelectedRoutePoint, x, y, z);

		ShowPmpModel();
		m_transportDlg->RefreshRoutePoint(m_currRoute,m_SelectedRoutePoint);
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	}

	return true;
}

bool CToolRoute::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);

	return true;
}


void CToolRoute::Render()
{
	if( optMode_Pick == m_eoptMode ) 
	{
		if (NULL != m_currRoute)
		{
			m_selPmpBox->Render( 1.0f );
		}
	}

	RenderIndex();
}


void CToolRoute::ApplyFlyRoute( float x,float y,float z)
{
	if (optMode_Pick == m_eoptMode)
	{
		if (-1 != m_SelectedRoutePoint)
		{
			m_currRoute->SetRoutePoint(m_SelectedRoutePoint,x,y,z);
		}
	}
	else
	{
		GetPmpModel()->model->SetPosition(x,y,z);
	}

}


void CToolRoute::Reset()
{
	m_currRoute		= NULL;
	m_SelectedRoutePoint = -1;
	SetOptMode(optMode_AddRoute);
}

CResEditMgr* CToolRoute::GetResMgr()
{
	return (CResEditMgr*)CURRENTTILE->GetCResMgr();
}

void CToolRoute::SetOptMode( optMode eMode )
{
	m_eoptMode = eMode;
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CNdlHelper* helper = view->GetHelper();
	switch (m_eoptMode)
	{
	case optMode_AddRoute:
		helper->AttachHelper(GetPmpModel());
		break;
	case optMode_Pick:
		helper->DetachHelper(GetPmpModel());
		break;

	}
}

void CToolRoute::DeletePointModel()
{
	if (-1 == m_SelectedRoutePoint || NULL == m_currRoute)
	{
		return;
	}

	//m_currRoute->DeleteRoutePoint(m_SelectedRoutePoint);
	DoDeleteRoutePoint((CNPCRouteRes *)m_currRoute, m_SelectedRoutePoint);

	m_SelectedRoutePoint = -1;
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
}

void CToolRoute::SetActive( bool isActive /*= true */ )
{
	CBaseTool::SetActive(isActive);
	if (isActive)
	{
		SetOptMode(optMode_AddRoute);
// 		if (theApp.GetWorld()->GetWorldBuffer())
// 		{
// 			CResMgr* resMgr = theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
// 			if (resMgr && resMgr->GetFlyRouteCount() > 0)
// 			{
// 				m_currRoute = resMgr->FlyRoute(0);
// 				m
// 			}
// 		}
	}
	else
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		helper->DetachHelper(GetPmpModel());
	}
}

TObjectEditInfo* CToolRoute::GetPmpModel()
{
	if (m_pmpRoutePoint == NULL)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		m_pmpRoutePoint = (TObjectEditInfo*)(helper->GetHelper(HT_FlyRoute)->pObject->Clone());
		if(!m_pmpRoutePoint)
		{
			SAFE_DELETE(m_pmpRoutePoint);
			return 0;
		}
		m_pmpRoutePoint->ApplyTransform();
	}
	return m_pmpRoutePoint;
}

void CToolRoute::SetCurrRoute( CRouteRes* route )
{
	if (route != m_currRoute)
	{
		if (m_currRoute)
		{
			m_currRoute->ClearModel();
		}
		m_currRoute = route;
		m_SelectedRoutePoint = -1;
		if (m_currRoute)
		{
			m_currRoute->ShowRoutePoint(true);
			m_transportDlg->RefreshFlyRoute(m_currRoute);
		}
	}
}

void CToolRoute::RenderIndex(void)
{
	if(NULL == m_currRoute)
		return;

	int count = m_currRoute->GetRoutePointList().size();
	for(int i=0; i<count; ++i)
	{
		Vector position;
		position.x = m_currRoute->GetPosX(i);
		position.y = m_currRoute->GetPosY(i);
		position.z = m_currRoute->GetPosZ(i);

		RenderIndex(i, position);
	}
}

void CToolRoute::RenderIndex(int index_, const Vector &point_)
{
	//world coordinate --> screen coordinate
	Vector2 viewSize;
	CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	if(NULL == pView)
		return;
	//pView->GetViewSize( viewSize.x, viewSize.y );
	RECT rect;
	pView->GetClientRect( &rect );
	viewSize.x = rect.right;
	viewSize.y = rect.bottom;

	SwCamera* pCamera	= pView->GetActiveCamera();
	if(NULL == pCamera)
		return;

	flt32 x, y;
	if(!pCamera->WorldToScreen(point_, &x, &y, viewSize.x, viewSize.y))
		return;

	//render the text
	if(pView->m_pFont != NULL)
	{
		std::ostringstream ss;
		ss << index_ << endl;

		RECT RT;
		SetRect(&RT, x, y, 0, 0);
		pView->m_pFont->DrawText( NULL, ss.str().c_str(), -1, &RT, DT_NOCLIP, D3DCOLOR_ARGB( 255,255,0,0)  );
	}
}

void CToolRoute::Redo(void)
{
	m_opManager.Roll();
}

void CToolRoute::Undo(void)
{
	m_opManager.Rollback();
}

bool CToolRoute::CanRedo(void)
{
	return m_opManager.CanRoll();
}
bool CToolRoute::CanUndo(void)
{
	return m_opManager.CanRollback();
}

bool CToolRoute::DoDeleteRoute(CNPCRouteRes *_pRes_)
{
	if(NULL == _pRes_)
		return false;

	NRouteTool::CDeleteRoute *mydo = new NRouteTool::CDeleteRoute(this);
	mydo->SetData(_pRes_);
	NRouteTool::CAddRoute *undo = new NRouteTool::CAddRoute(this);
	undo->SetData(_pRes_);

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolRoute::DeleteRoute(CNPCRouteRes *_pRes_)
{
	if(NULL == _pRes_)
		return false;

	_pRes_->ClearModel();
	return GetResMgr()->PopRoute(_pRes_);
}

bool CToolRoute::DoAddRoute(const char *pName_, bool bFlyRoute_)
{
	if(NULL == pName_ || 0 == strlen(pName_))
		return false;

	CNPCRouteRes *pRes = GetResMgr()->CreateRoute(pName_, bFlyRoute_);
	if(NULL == pRes)
		return false;

	NRouteTool::CAddRoute *mydo = new NRouteTool::CAddRoute(this);
	mydo->SetData(pRes);
	NRouteTool::CDeleteRoute *undo = new NRouteTool::CDeleteRoute(this);
	undo->SetData(pRes);

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolRoute::AddRoute(CNPCRouteRes *_pRes_)
{
	if(NULL == _pRes_)
		return false;

	return GetResMgr()->PushRoute(_pRes_);
}

bool CToolRoute::DoGenerateCloseRoute(CNPCRouteRes *_pRes_, bool bShow_)
{
	if(NULL == _pRes_)
		return false;

	NRouteTool::CGenerateCloseRoute *mydo = new NRouteTool::CGenerateCloseRoute(this);
	mydo->SetData(_pRes_, bShow_, true);
	NRouteTool::CGenerateCloseRoute *undo = new NRouteTool::CGenerateCloseRoute(this);
	undo->SetData(_pRes_, bShow_, false);

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolRoute::GenerateCloseRoute(CNPCRouteRes *_pRes_, bool bShow_, bool bGenerate_)
{
	if(NULL == _pRes_)
		return false;

	if(bGenerate_)
	{
		return _pRes_->GenerateCloseRoute(bShow_);
	}
	else
	{
		return _pRes_->CancelCloseRoute();
	}
}

bool CToolRoute::DoChangeRouteProperty(CNPCRouteRes *_pRes_, const char *name_, sInt32 nextMapId_, sInt32 nextRouteId_)
{
	if(NULL == _pRes_ || NULL == name_)
		return false;

	NRouteTool::CChangeRouteProperty *mydo = new NRouteTool::CChangeRouteProperty(this);
	mydo->SetData(_pRes_, name_, nextMapId_, nextRouteId_);
	NRouteTool::CChangeRouteProperty *undo = new NRouteTool::CChangeRouteProperty(this);
	undo->SetData(_pRes_, _pRes_->GetName(), _pRes_->GetNextMapID(), _pRes_->GetNextRouteID());

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolRoute::ChangeRouteProperty(CNPCRouteRes *_pRes_, const char *name_, sInt32 nextMapId_, sInt32 nextRouteId_)
{
	if(NULL == _pRes_ || NULL == name_)
		return false;

	_pRes_->SetName(name_);
	_pRes_->SetNextMapID(nextMapId_);
	_pRes_->SetNextRouteID(nextRouteId_);

	return true;
}

bool CToolRoute::DoAddRoutePoint(CNPCRouteRes *_pRes_, float x_, float y_,float z_,bool bShow_)
{
	if(NULL == _pRes_)
		return false;

	CNPCRouteRes::SNpcRoutePoint *npcPoint = NULL;
	Vector *point = NULL;
	if(!_pRes_->CreatePoint(x_, y_, z_, npcPoint, point))
		return false;

	int index = _pRes_->GetPointCount();
	NRouteTool::CAddRoutePoint *mydo = new NRouteTool::CAddRoutePoint(this);
	mydo->SetData(_pRes_, index, npcPoint, point, bShow_);
	NRouteTool::CDeleteRoutePoint *undo = new NRouteTool::CDeleteRoutePoint(this);
	undo->SetData(_pRes_, index);

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolRoute::AddRoutePoint(CNPCRouteRes *_pRes_,  int index_, CNPCRouteRes::SNpcRoutePoint *pNpcPoint_, Vector *pPoint_, bool bShow_)
{
	if(NULL == _pRes_)
		return false;

	if(index_ < 0)
		return false;

	return _pRes_->PushPoint(index_, pNpcPoint_, pPoint_, bShow_);
}

bool CToolRoute::DoDeleteRoutePoint(CNPCRouteRes *_pRes_, int index_)
{
	if(NULL == _pRes_)
		return false;

	if(index_ < 0 || index_ >= _pRes_->GetPointCount())
		return false;

	CNPCRouteRes::SNpcRoutePoint *npcPoint = NULL;
	Vector *point = NULL;
	if(_pRes_->GetPoint(index_, npcPoint, point))
		return false;

	NRouteTool::CDeleteRoutePoint *mydo = new NRouteTool::CDeleteRoutePoint(this);
	mydo->SetData(_pRes_, index_);
	NRouteTool::CAddRoutePoint *undo = new NRouteTool::CAddRoutePoint(this);
	undo->SetData(_pRes_, index_, npcPoint, point, true);	//这里只好先设置成true了

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolRoute::DeleteRoutePoint(CNPCRouteRes *_pRes_, int index_)
{
	if(NULL == _pRes_)
		return false;

	if(index_ < 0 || index_ >= _pRes_->GetPointCount())
		return false;

	return _pRes_->PopPoint(index_);
}

bool CToolRoute::DoChangeRoutePointPosition(CNPCRouteRes *_pRes_, int index_, float x_, float y_,float z_)
{
	if(NULL == _pRes_)
		return false;

	if(index_ < 0 || index_ >= _pRes_->GetPointCount())
		return false;

	NRouteTool::CChangeRoutePointPosition *mydo = new NRouteTool::CChangeRoutePointPosition(this);
	mydo->SetData(_pRes_, index_, x_, y_, z_);
	NRouteTool::CChangeRoutePointPosition *undo = new NRouteTool::CChangeRoutePointPosition(this);
	undo->SetData(_pRes_, index_, _pRes_->GetPosX(index_), _pRes_->GetPosY(index_), _pRes_->GetPosZ(index_));

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolRoute::ChangeRoutePointPosition(CNPCRouteRes *_pRes_, int index_, float x_, float y_,float z_)
{
	if(NULL == _pRes_)
		return false;

	if(index_ < 0 || index_ >= _pRes_->GetPointCount())
		return false;

	_pRes_->SetRoutePoint(index_, x_, y_, z_);
	return true;
}

bool CToolRoute::DoChangeRoutePointProperty(CNPCRouteRes *_pRes_, int index_, const CNPCRouteRes::SNpcRoutePoint &npcPoint_)
{
	if(NULL == _pRes_)
		return false;

	if(index_ < 0 || index_ >= _pRes_->GetPointCount())
		return false;

	CNPCRouteRes::SNpcRoutePoint *pOldNpcPoint = _pRes_->GetRoutePoint(index_);
	if(NULL == pOldNpcPoint)
		return false;

	NRouteTool::CChangeRoutePointProperty *mydo = new NRouteTool::CChangeRoutePointProperty(this);
	mydo->SetData(_pRes_, index_, npcPoint_);
	NRouteTool::CChangeRoutePointProperty *undo = new NRouteTool::CChangeRoutePointProperty(this);
	undo->SetData(_pRes_, index_, *pOldNpcPoint);

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolRoute::ChangeRoutePointProperty(CNPCRouteRes *_pRes_, int index_, const CNPCRouteRes::SNpcRoutePoint &npcPoint_)
{
	if(NULL == _pRes_)
		return false;

	if(index_ < 0 || index_ >= _pRes_->GetPointCount())
		return false;

	_pRes_->SetNpcRoutePoint(index_, npcPoint_);

	return true;
}