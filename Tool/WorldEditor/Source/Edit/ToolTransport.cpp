/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolTransport.cpp
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "ToolTransport.h"
#include "OptStack.h"
#include "Ndl/NdlWorldEditor.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/ToolsWnd/ToolTransportDlg.h"

////////////////////////////////////////////////////////////////////////////////
CToolTransport::CToolTransport()
{
	m_transportDlg  = NULL;
	m_currTran  = NULL;
	m_eoptMode	= optMode_Transport;
}

CToolTransport::~CToolTransport()
{
	SAFE_DELETE( m_selPmpBox );
}

bool CToolTransport::Create( CToolManager* toolMgr )
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

void CToolTransport::ShowPmpModel(  )
{
	if (m_currTran == NULL)
	{
		return;
	}
	Assert( NULL!=GetEditTran()->GetModel() );
	if( NULL != m_selPmpBox ) {
		flt32 scale = 1.0f;		
		//set scale
		scale = GetEditTran()->GetModel()->model->GetScale();
		m_selPmpBox->model->SetScale(scale);
		//set rotation
		float fX, fY, fZ;
		GetEditTran()->GetModel()->model->GetRotation( fX, fY, fZ );
		m_selPmpBox->model->SetRotationX( fX );
		m_selPmpBox->model->SetRotationY( fY );
		m_selPmpBox->model->SetRotationZ( fZ );
		//set position
		m_selPmpBox->model->SetPosition( GetEditTran()->GetModel()->model->GetPosition() );
		//update
		m_selPmpBox->Update(0.0f);
	}
}


void CToolTransport::Bind( CToolTransportDlg* dlg )
{
	m_transportDlg = dlg;
}



bool CToolTransport::OnLMouseDown( UINT nFlags, CPoint point )
{
	m_isLDrag	= true;
	m_oldPos	= point; 

	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	
	sInt32 pickId = view->PickWorldTerrain( point,emPT_Transport|emPT_Terrain|emPT_FloorObj );

	if( -1 != pickId ) { 
		const TPickResult& pickResult = view->GetPickResult();
		if( optMode_Pick == m_eoptMode ) 
		{
			m_currTran		= NULL;
			sInt32 objId	= -1;


			CString strPmt;
			strPmt.Format( _T("没有选中物体") );

			for( sInt32 i=0; i<pickResult.pickResultCount; i++ ) {
				if( emPT_Transport == pickResult.pickResultInfo[i].resultType ) {
					objId = i;
					break;
				}
			}
			CResEditMgr* resMgr = GetResMgr();	
			if( NULL == resMgr )
				return false;

			if( -1 != objId ) 
			{
				m_currTran		= GetResMgr()->Transport(pickResult.pickResultInfo[objId].resultId);
				if( NULL != m_currTran ) {
					m_transportDlg->RefreshTransport(m_currTran);

					if (m_currTran->IsTransport())
					{
						strPmt.Format( _T("选中传送点%d"),m_currTran->GetId());
					}
					else
					{
						strPmt.Format( _T("选中目标点%d"),m_currTran->GetId());
					}
//					g_render->SetSelModel(  pickResult.pickResultInfo[objId].resultId );

					ShowPmpModel();
				}
			}
			else {
				if( NULL != m_selPmpBox ) {
					m_selPmpBox->model->SetPosition( 0.0f, 0.0f, 0.0f );
					m_selPmpBox->Update(0.0f);
				}
			}
			theApp.SetPromptText( strPmt );
		}
		else
		{
			int close_id=GetCloseIndex(pickResult,emPT_Transport);
			flt32 pos[3];
			for( sInt32 i=0; i<3; i++ ) 
			{
				pos[i] = pickResult.pickResultInfo[close_id].point[i];
			}
			CTransportResBase* pRes = NULL;
			if (optMode_Transport == m_eoptMode)
			{
				pRes = GetResMgr()->PushTransport(pos[1] + 0.5f,pos[0] - 0.5f,pos[0] + 0.5f,pos[1] - 0.5f,0);
			}
			else
			{
				bool bRelive = false;
				if (m_transportDlg->IsDlgButtonChecked(IDC_RADIO_ISRELIVE))
				{
					bRelive = true;
				}
				
				pRes = GetResMgr()->PushTarget(pos[0],pos[1],0.f, bRelive);
			}
			((CTransportResBase*)pRes)->AttachModel();
			CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
		}
	}
	return true;
}

bool CToolTransport::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;


	return true;
}

bool CToolTransport::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return true;
}

bool CToolTransport::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 

	return true;
}

bool CToolTransport::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;



	return true;
}

bool CToolTransport::OnMouseMove( UINT nFlags, CPoint point )
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
				int close_id=GetCloseIndex(pickResult,emPT_Transport);
				flt32 pos[3];
				for( sInt32 i=0; i<3; i++ ) 
				{
					pos[i] = pickResult.pickResultInfo[close_id].point[i];
				}
				if (optMode_Transport == m_eoptMode)
				{
					ApplyTransport(pos[1] + 0.5f,pos[0] - 0.5f,pos[0] + 0.5f,pos[1] - 0.5f,0);
				}
				else
				{
					ApplyTarget(pos[0],pos[1],0.f);
				}
			}
		}
	}
	camera->Update( 0.0f, 0.0f );

	return true;
}

bool CToolTransport::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (NULL == m_currTran)
	{
		return false;
	}
	if( nChar == VK_DELETE ) {
		DeleteModel();
		return true;
	}
	if( optMode_Pick == m_eoptMode ) {
		flt32 delta = 0.1f;
		if(nFlags&MK_CONTROL ) 
		{
			delta	= 0.5f;
		}
		if( nChar == VK_LEFT ) 
		{
			m_currTran->SetPosX(m_currTran->GetPosX()-delta);
		}
		else if( nChar == VK_RIGHT ) {
			m_currTran->SetPosX(m_currTran->GetPosX()+delta);
		}
		else if( nChar == VK_DOWN ) {
			m_currTran->SetPosY(m_currTran->GetPosY()-delta);
		}
		else if( nChar == VK_UP ) {
			m_currTran->SetPosY(m_currTran->GetPosY()+delta);
		}
		GetEditTran()->ApplyTransform();
		ShowPmpModel();
		m_transportDlg->RefreshTransport(m_currTran);
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	}

	return true;
}

bool CToolTransport::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);

	return true;
}


void CToolTransport::Render()
{
	if( optMode_Pick == m_eoptMode ) 
	{
		if (NULL != m_currTran)
		{
			m_selPmpBox->Render( 1.0f );
		}
	}

}


void CToolTransport::ApplyTransport( float top,float left,float right,float bottom ,sInt32 nIndex)
{
	CTransportEditRes* pRes = (CTransportEditRes*)m_currTran;
	if (optMode_Pick == m_eoptMode)
	{
		if (m_currTran == NULL || (!m_currTran->IsTransport()))
		{
			return;
		}
		else
		{
			pRes = (CTransportEditRes*)m_currTran;
		}
	}
	else
	{
		if (m_eoptMode != optMode_Transport)
		{
			return;
		}
		else
		{
			pRes = &m_pmpTransport;
		}
	}

	pRes->SetLeft(left);
	pRes->SetRight(right);
	pRes->SetBottom(bottom);
	pRes->SetTop(top);
	pRes->SetNtargetID(nIndex);
	pRes->ApplyTransform();
}

void CToolTransport::ApplyTarget( float posX,float posY,float dir, BOOL bRed/* = FALSE*/, int nVestType/* = 0*/, int nMapId /* = -1*/)
{
	CTargetEditRes* pRes = (CTargetEditRes*)m_currTran;
	if (optMode_Pick == m_eoptMode)
	{
		if (m_currTran == NULL || (m_currTran->IsTransport()))
		{
			return;
		}
		else
		{
			pRes = (CTargetEditRes*)m_currTran;
		}
	}
	else
	{
		if (m_eoptMode != optMode_Target)
		{
			return;
		}
		else
		{
			pRes = &m_pmpTarget;
		}
	}

	pRes->SetPosX(posX);
	pRes->SetPosY(posY);
	pRes->SetTargetDir(dir);

	if(pRes->IsRelive())
	{
		int nType = pRes->GetReliveType();
		nType &= ~(CTargetEditRes::Relive_Attack | CTargetEditRes::Relive_Guard | CTargetEditRes::Relive_RedName);

		if (bRed == TRUE)
		{
			nType |= CTargetEditRes::Relive_RedName;
		}
				
		if (nVestType == 1)
		{
			nType |= CTargetEditRes::Relive_Attack;
		}
		else if (nVestType == 2)
		{
			nType |= CTargetEditRes::Relive_Guard;
		}

		pRes->SetReliveType(nType);

		pRes->SetReliveMapId(nMapId);
	}

	pRes->ApplyTransform();
}

void CToolTransport::Reset()
{
	m_currTran		= NULL;
	SetOptMode(optMode_Transport);
}

CResEditMgr* CToolTransport::GetResMgr()
{
	return (CResEditMgr*)CURRENTTILE->GetCResMgr();
}

void CToolTransport::SetOptMode( optMode eMode )
{
	m_eoptMode = eMode;
	switch (m_eoptMode)
	{
	case optMode_Transport:
		m_pmpTransport.AttachModel();
		m_pmpTarget.DetachModel();
// 		m_pmpTransport.GetModel()->SetAppCulled(false);
// 		m_pmpTarget.GetModel()->SetAppCulled(true);
		break;
	case optMode_Target:
		m_pmpTransport.DetachModel();
		m_pmpTarget.AttachModel();
// 		m_pmpTransport.GetModel()->SetAppCulled(true);
// 		m_pmpTarget.GetModel()->SetAppCulled(false);
		break;
	case optMode_Pick:
		m_pmpTransport.DetachModel();
		m_pmpTarget.DetachModel();
// 		m_pmpTransport.GetModel()->SetAppCulled(true);
// 		m_pmpTarget.GetModel()->SetAppCulled(true);
		break;

	}
}	

void CToolTransport::DeleteModel()
{
	GetResMgr()->DeleteTransport(m_currTran->GetId());
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	m_currTran = NULL;
}

void CToolTransport::SetActive( bool isActive /*= true */ )
{
	CBaseTool::SetActive(isActive);
	if (isActive)
	{
		SetOptMode(optMode_Transport);
	}
	else
	{
		m_pmpTransport.DetachModel();
		m_pmpTarget.DetachModel();
	}
}