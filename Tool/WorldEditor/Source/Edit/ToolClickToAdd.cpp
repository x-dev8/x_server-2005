/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolClick2Add.cpp
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "ToolClicktoAdd.h"
#include "OptStack.h"
#include "Ndl/NdlWorldEditor.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/ToolsScene/ToolClicktoAddDlg.h"
#include "NDL\NdlHelper.h"
////////////////////////////////////////////////////////////////////////////////
CToolClick2Add::CToolClick2Add()
{
	m_click2AddDlg  = NULL;
	m_currClick2Add  = NULL;
	m_SelectedClick2AddPoint = -1;
	m_eoptMode	= optMode_AddClick2Add;
	m_pmpClick2AddPoint = NULL;
}

CToolClick2Add::~CToolClick2Add()
{
	SAFE_DELETE( m_selPmpBox );
	if(!m_pmpClick2AddPoint)
	{
		SAFE_DELETE(m_pmpClick2AddPoint);
	}
}

bool CToolClick2Add::Create( CToolManager* toolMgr )
{
	CBaseTool::Create( toolMgr );
	char path[MAX_PATH*2];
	sprintf_s( path, "%s\\Required\\Model\\Box.mex", CWorld::GetAppCharDir() );

	//create the pmpbox
	m_selPmpBox = MeNew TObjectEditInfo();
	if(!m_selPmpBox->LoadFromFile( path ))
		return false;
	return true;

}

void CToolClick2Add::ShowPmpModel(  )
{
	if (m_currClick2Add == NULL)
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
// 		m_currClick2Add->GetModel()->model->GetRotation( fX, fY, fZ );
// 		m_selPmpBox->model->SetRotationX( fX );
// 		m_selPmpBox->model->SetRotationY( fY );
// 		m_selPmpBox->model->SetRotationZ( fZ );
		//set position
		m_selPmpBox->model->SetPosition( m_currClick2Add->GetPosX(), 
			m_currClick2Add->GetPosY(),
			m_currClick2Add->GetPosZ());
		//update
		m_selPmpBox->Update(0.0f);
	}
}


void CToolClick2Add::Bind( CToolClick2AddDlg* dlg )
{
	m_click2AddDlg = dlg;
}



bool CToolClick2Add::OnLMouseDown( UINT nFlags, CPoint point )
{
	m_isLDrag	= true;
	m_oldPos	= point; 

	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	
	sInt32 pickId = view->PickWorldTerrain( point,emPT_Click2Add|emPT_Terrain|emPT_FloorObj );

	if( -1 != pickId ) 
	{ 
		CResEditMgr* resMgr = GetResMgr();	
		if( NULL == resMgr )
			return false;
		const TPickResult& pickResult = view->GetPickResult();
		if( optMode_Pick == m_eoptMode ) 
		{
			sInt32 objId	= -1;


			CString strPmt;
			strPmt.Format( _T("没有选中物体") );

			for( sInt32 i=0; i<pickResult.pickResultCount; i++ ) {
				if( emPT_Click2Add == pickResult.pickResultInfo[i].resultType ) {
					objId = i;
					break;
				}
			}

			if( -1 != objId ) 
			{
				{
					CSoundPointEditRes* selClick2Add = (CSoundPointEditRes*)pickResult.pickResultInfo[objId].resultObjInfo;
					SetCurrClick2Add(selClick2Add);
					m_SelectedClick2AddPoint = pickResult.pickResultInfo[objId].resultId;
					m_click2AddDlg->RefreshClick2Add(m_currClick2Add);


//					g_render->SetSelModel(  pickResult.pickResultInfo[objId].resultId );
					{
						strPmt.Format( _T("选中点声源\"%s\""),m_currClick2Add->GetName());
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
			int close_id=GetCloseIndex(pickResult,emPT_Click2Add);
			flt32 pos[3];
			for( sInt32 i=0; i<3; i++ ) 
			{
				pos[i] = pickResult.pickResultInfo[close_id].point[i];
			}
			char tmp[256];
			sprintf_s(tmp,"%d",resMgr->GetSoundPointCount());
			CSoundPointEditRes* pRes = (CSoundPointEditRes*)resMgr->PushSoundPoint(tmp);
			pRes->SetPosX(pos[0]);
			pRes->SetPosY(pos[1]);
			pRes->SetPosZ(pos[2]);
			pRes->ShowSoundPointPoint(true);
			m_click2AddDlg->UpdateClick2AddList();
			CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
		}
	}
	return true;
}

bool CToolClick2Add::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;


	return true;
}

bool CToolClick2Add::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return true;
}

bool CToolClick2Add::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 

	return true;
}

bool CToolClick2Add::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;



	return true;
}

bool CToolClick2Add::OnMouseMove( UINT nFlags, CPoint point )
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
				ApplyClick2Add(pos[0],pos[1],pos[2]);
			}
		}
	}
	camera->Update( 0.0f, 0.0f );

	return true;
}

bool CToolClick2Add::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (NULL == m_currClick2Add)
	{
		return false;
	}
	if (m_SelectedClick2AddPoint == -1)
	{
		return false;
	}
	if( nChar == VK_DELETE ) {
		DeletePointModel();
		return true;
	}
//	if( optMode_Pick == m_eoptMode ) 
	{
		flt32 delta = 0.1f;
		{
			delta	= 0.5f*nRepCnt;
		}
		if( nChar == VK_LEFT ) 
		{
			m_currClick2Add->SetPosX(m_currClick2Add->GetPosX()-delta);
		}
		else if( nChar == VK_RIGHT ) {
			m_currClick2Add->SetPosX(m_currClick2Add->GetPosX()+delta);
		}
		else if( nChar == VK_DOWN ) 
		{
			m_currClick2Add->SetPosY(m_currClick2Add->GetPosY()-delta);
		}
		else if( nChar == VK_UP ) 
		{
			m_currClick2Add->SetPosY(m_currClick2Add->GetPosY()+delta);
		}
		else if (nChar == 'w' || nChar == 'W')
		{
			m_currClick2Add->SetPosZ(m_currClick2Add->GetPosZ()+delta);
		}
		else if (nChar == 's' || nChar == 'S')
		{
			m_currClick2Add->SetPosZ(m_currClick2Add->GetPosZ()-delta);
		}
		m_currClick2Add->ApplyTransform();
		ShowPmpModel();
		m_click2AddDlg->RefreshClick2Add(m_currClick2Add);
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	}

	return true;
}

bool CToolClick2Add::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);

	return true;
}


void CToolClick2Add::Render()
{
// 	if( optMode_Pick == m_eoptMode ) 
	{
		if (NULL != m_currClick2Add)
		{
			m_selPmpBox->Render( 1.0f );
		}
	}

}


void CToolClick2Add::ApplyClick2Add( float x,float y,float z)
{
	if (optMode_Pick == m_eoptMode)
	{
		if (-1 != m_SelectedClick2AddPoint)
		{
			m_currClick2Add->SetPosX(x);
			m_currClick2Add->SetPosY(y);
			m_currClick2Add->SetPosZ(z);
			m_currClick2Add->ApplyTransform();
		}
	}
	else
	{
		GetPmpModel()->model->SetPosition(x,y,z);
	}

}


void CToolClick2Add::Reset()
{
	m_currClick2Add		= NULL;
	m_SelectedClick2AddPoint = -1;
	SetOptMode(optMode_AddClick2Add);
}

CResEditMgr* CToolClick2Add::GetResMgr()
{
	return (CResEditMgr*)CURRENTTILE->GetCResMgr();
}

void CToolClick2Add::SetOptMode( optMode eMode )
{
	m_eoptMode = eMode;
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CNdlHelper* helper = view->GetHelper();
	switch (m_eoptMode)
	{
	case optMode_AddClick2Add:
		helper->AttachHelper(GetPmpModel());
		break;
	case optMode_Pick:
		helper->DetachHelper(GetPmpModel());
		break;

	}
}

void CToolClick2Add::DeletePointModel()
{
	if (-1 == m_SelectedClick2AddPoint)
	{
		return;
	}
	CResEditMgr* resMgr = GetResMgr();	
	if( NULL == resMgr )
		return ;
	resMgr->DeleteSoundPoint(m_SelectedClick2AddPoint);
	m_SelectedClick2AddPoint = -1;
	SetCurrClick2Add(NULL);
	m_click2AddDlg->UpdateClick2AddList();
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
}

void CToolClick2Add::SetActive( bool isActive /*= true */ )
{
	CBaseTool::SetActive(isActive);
	if (isActive)
	{
		SetOptMode(optMode_AddClick2Add);
// 		if (theApp.GetWorld()->GetWorldBuffer())
// 		{
// 			CResMgr* resMgr = theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
// 			if (resMgr && resMgr->GetClick2AddCount() > 0)
// 			{
// 				m_currClick2Add = resMgr->Click2Add(0);
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

TObjectEditInfo* CToolClick2Add::GetPmpModel()
{
	if (m_pmpClick2AddPoint == NULL)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		m_pmpClick2AddPoint = (TObjectEditInfo*)(helper->GetHelper(HT_SoundPoint)->pObject->Clone());
		if(!m_pmpClick2AddPoint)
		{
			SAFE_DELETE(m_pmpClick2AddPoint);
			return 0;
		}
		m_pmpClick2AddPoint->ApplyTransform();
	}
	return m_pmpClick2AddPoint;
}

void CToolClick2Add::SetCurrClick2Add( CSoundPointEditRes* route )
{
	if (route != m_currClick2Add)
	{
		m_currClick2Add = route;
		if (m_currClick2Add)
		{
			m_SelectedClick2AddPoint = m_currClick2Add->GetId();
			m_click2AddDlg->RefreshClick2Add(m_currClick2Add);
			GetPmpModel()->model->SetPosition(m_currClick2Add->GetPosX(),m_currClick2Add->GetPosY(),m_currClick2Add->GetPosZ());
		}
		else
		{
			m_SelectedClick2AddPoint = RES_INVALID_ID;
		}
	}
}