/*******************************************************************************
* Copyright ShenWang 2011 - All Rights Reserved
* 
* File: 	ToolStaticLight.cpp
* Create: 	02/22/2011
* Desc:		静态光源场景控制
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdAfx.h"
#include "ToolStaticLight.h"
#include "Me3d/Model/MexGeoChunk.h"

#define OffsetZ 1

CToolStaticLight::CToolStaticLight()
: m_bindDlg(NULL)
, m_eOptMode(optMode_Pick)
{
	m_vecLightModels.clear();
	m_vSelected.clear();
}

CToolStaticLight::~CToolStaticLight()
{
	m_bindDlg		= NULL;
	ClearAllLightModel();
}

bool CToolStaticLight::Create( CToolManager* toolMgr )
{
	return LoadLightModel();
}

void CToolStaticLight::Bind( CToolStaticLightDlg* bindDlg )
{
	if( bindDlg )
		m_bindDlg = bindDlg;
}

void CToolStaticLight::Reset()
{
	SetOptMode(optMode_Pick);
	m_vSelected.clear();
	ClearAllLightModel();
}

bool CToolStaticLight::OnLMouseDown( UINT nFlags, CPoint point )
{
	m_isLDrag	= true;
	m_oldPos	= point; 

	if( !m_bindDlg )
		return false;

	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

	if( optMode_Pick == m_eOptMode ) 
	{
		Vector rayPt, rayDir;
		if( !CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetRayFromPoint(point, rayPt, rayDir) )
			return false;

		rayDir.normalize();

		// 遍历所有光源模型
		int closeIndex = -1;
		float closeDist = 1000.f;
		for( int i=0; i<m_vecLightModels.size(); ++i )
		{
			if( !m_vecLightModels[i] )
				continue;

			Vector pos;
			pos.x= m_vecLightModels[i]->pos[0];
			pos.y= m_vecLightModels[i]->pos[1];
			pos.z= m_vecLightModels[i]->pos[2];
			
			float fLightRadius = m_vecLightModels[i]->scale[0];

			Vector vPointtoLight = pos - rayPt;
			float fLengthPtoL = vPointtoLight.normalize();
			// 光线与射线夹角
			float fAngle = acos(vPointtoLight.dot(rayDir));
			// 光源到射线垂直距离
			float fDistRaytoLight = fLengthPtoL * sin(fAngle);
			if( fDistRaytoLight <= fLightRadius )
			{
				if( fDistRaytoLight < closeDist )
				{
					closeIndex = i;
					closeDist = fDistRaytoLight;
				}
			}
		}
		if( closeIndex >= 0 )
		{
			bool bSelected = false;
			for( int i=0; i<m_vSelected.size(); ++i )
			{
				if( m_vSelected[i] == closeIndex )
				{
					bSelected = true;
					break;
				}
			}
			if( bSelected )
			{
				m_bindDlg->UnSelectLight(closeIndex);
			}
			else
			{
				if( (nFlags & MK_CONTROL) != 0 )
					m_bindDlg->SelectLight(closeIndex, TRUE);
				else
					m_bindDlg->SelectLight(closeIndex, FALSE);
			}
		}
	}
	else if (optMode_PutLight == m_eOptMode)
	{
		sInt32 pickId = view->PickWorldTerrain( point, emPT_Terrain|emPT_FloorObj );
		if( -1 != pickId )
		{ 
			const TPickResult& pickResult = view->GetPickResult();

			// 增加点光源
			int close_id = GetCloseIndex(pickResult, emPT_Unknown);
			Vector pos = pickResult.pickResultInfo[close_id].point;
			pos.z += OffsetZ;
			m_bindDlg->AddLight(pos);
			SetOptMode(optMode_Pick);
			CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );
		}
	}
	return true;
}

bool CToolStaticLight::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;

	return true;
}

bool CToolStaticLight::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return true;
}

bool CToolStaticLight::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 

	return true;
}

bool CToolStaticLight::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;

	return true;
}

bool CToolStaticLight::OnMouseMove( UINT nFlags, CPoint point )
{
	Vector2 viewSize;
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	view->GetViewSize( viewSize.x, viewSize.y );
	if( viewSize.x < 1 || viewSize.y < 1 )
		return false;

	SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();

	CPoint delta = point - m_oldPos;
	if( m_isRDrag )
	{	// move
		CameraAdjust(point, nFlags);
	}
	else if( m_isLDrag )
	{
		m_oldPos = point;
	}
	else
	{
		sInt32 pickId = view->PickWorldTerrain( point,emPT_Terrain|emPT_FloorObj );
		if( -1 != pickId ) 
		{ 
			const TPickResult& pickResult = view->GetPickResult();
			if( optMode_PutLight == m_eOptMode ) 
			{
				int close_id = GetCloseIndex(pickResult, emPT_Unknown);
				if( m_lightNode.model )
				{
					Vector pos = pickResult.pickResultInfo[close_id].point;
					m_lightNode.pos[0] = pos.x;
					m_lightNode.pos[1] = pos.y;
					m_lightNode.pos[2] = pos.z+OffsetZ;
					m_lightNode.ApplyTransform();
				}
			}
		}
	}
	camera->Update( 0.0f, 0.0f );

	return true;
}

bool CToolStaticLight::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	return true;
}

bool CToolStaticLight::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);
	if( nChar == VK_ESCAPE )
	{
		m_bindDlg->CancelSelect();
	}
	return true;
}

void CToolStaticLight::Render()
{
	if( m_eOptMode == optMode_PutLight )
		m_lightNode.Render( 1.f );

	for(int i=0; i<m_vecLightModels.size(); ++i)
	{
		float alpha = 0.2f;
		for( int j=0; j<m_vSelected.size(); ++j )
		{
			if( i == m_vSelected[j] )
			{
				alpha = 1.f;
				break;
			}
		}

		if( m_vecLightModels[i] )
		{
			m_vecLightModels[i]->SetAlpha(alpha);
			m_vecLightModels[i]->Render( alpha );
		}
	}
}

bool CToolStaticLight::LoadLightModel()
{
	char file[MAX_PATH*2];
	sprintf_s( file, "%s\\%s", CWorld::GetAppCharDir(), "Required\\Model\\PointLight.mex" );

	bool ret = m_lightNode.LoadFromFile( file );
	if( !ret || !m_lightNode.model )
	{
		::AfxMessageBox( _T("缺少光源辅助工具Required\\Model\\PointLight.mex！") );
	}
	m_lightNode.model->SetRenderFlag(eWireFrame);

	return ret;
}

void CToolStaticLight::SetOptMode( optMode mode )
{
	m_eOptMode = mode;
	if( m_eOptMode == optMode_PutLight )
		UnSelectAll();
}

bool CToolStaticLight::PushLightModel( float fDist, const Vector& pos, const NiColorB& color )
{
	TObjectEditInfo* pModel = (TObjectEditInfo*)m_lightNode.Clone();
	if( pModel )
	{
		pModel->pos[0] = pos.x;
		pModel->pos[1] = pos.y;
		pModel->pos[2] = pos.z;
		pModel->scale[0] = fDist;
		pModel->scale[1] = fDist;
		pModel->scale[2] = fDist;

		pModel->ApplyTransform();
		pModel->model->SetRenderFlag(eWireFrame);

		m_vecLightModels.push_back(pModel);
		return true;
	}

	return false;
}

bool CToolStaticLight::UpdatePosX( int index, float v )
{

	if( index < 0 || index >= m_vecLightModels.size() )
		return false;

	if( !m_vecLightModels[index] || !m_vecLightModels[index]->model )
		return false;

	m_vecLightModels[index]->pos[0] = v;
	m_vecLightModels[index]->ApplyTransform();
	return true;
}

bool CToolStaticLight::UpdatePosY( int index, float v )
{
	if( index < 0 || index >= m_vecLightModels.size() )
		return false;

	if( !m_vecLightModels[index] || !m_vecLightModels[index]->model )
		return false;

	m_vecLightModels[index]->pos[1] = v;
	m_vecLightModels[index]->ApplyTransform();
	return true;
}

bool CToolStaticLight::UpdatePosZ( int index, float v )
{
	if( index < 0 || index >= m_vecLightModels.size() )
		return false;

	if( !m_vecLightModels[index] || !m_vecLightModels[index]->model )
		return false;

	m_vecLightModels[index]->pos[2] = v;
	m_vecLightModels[index]->ApplyTransform();
	return true;
}

bool CToolStaticLight::UpdateDistance( int index, float v )
{
	if( index < 0 || index >= m_vecLightModels.size() )
		return false;

	if( !m_vecLightModels[index] || !m_vecLightModels[index]->model )
		return false;

	m_vecLightModels[index]->scale[0] = v;
	m_vecLightModels[index]->scale[1] = v;
	m_vecLightModels[index]->scale[2] = v;
	m_vecLightModels[index]->ApplyTransform();
	return true;
}

bool CToolStaticLight::UpdateColor( int index, const NiColorB& color )
{
	if( index < 0 || index >= m_vecLightModels.size() )
		return false;

	if( !m_vecLightModels[index] || !m_vecLightModels[index]->model )
		return false;

	return true;
}

bool CToolStaticLight::RemoveLightModel( int index )
{
	if( index < 0 || index >= m_vecLightModels.size() )
		return false;
	
	TObjectEditInfo* pObject = m_vecLightModels[index];
	SAFE_DELETE(pObject);
	m_vecLightModels.erase(m_vecLightModels.begin()+index);
	
	int iErase = -1;
	for( int i=0; i<m_vSelected.size(); ++i )
	{
		if( m_vSelected[i] == index )
		{
			iErase = i;
		}
		else if( m_vSelected[i] > index )
		{
			--m_vSelected[i];
		}
	}
	if( iErase >= 0 )
	{
		m_vSelected.erase(m_vSelected.begin() + iErase);
	}
	return true;
}

void CToolStaticLight::ClearAllLightModel()
{
	for( int i=0; i<m_vecLightModels.size(); ++i )
	{
		SAFE_DELETE( m_vecLightModels[i] );
	}
	m_vecLightModels.clear();
	m_vSelected.clear();
}

void CToolStaticLight::DoSelect( int select )
{
	if( select < 0 || select >= m_vecLightModels.size() )
		return;

	bool bFind = false;
	for( int i=0; i<m_vSelected.size(); ++i )
	{
		if( select == m_vSelected[i] )
		{
			bFind = true;
			break;
		}
	}
	if( !bFind )
	{
		m_vSelected.push_back(select);
	}
}

void CToolStaticLight::UnSelect( int select )
{
	if( select < 0 || select >= m_vecLightModels.size() )
		return;

	int index = -1;
	for( int i=0; i<m_vSelected.size(); ++i )
	{
		if( select == m_vSelected[i] )
		{
			index = i;
			break;
		}
	}
	if( index >= 0 )
	{
		m_vSelected.erase(m_vSelected.begin() + index);
	}
}