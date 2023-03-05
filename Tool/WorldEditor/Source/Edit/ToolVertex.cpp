/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolSelect.cpp
* Date: 	03/02/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "OptPaintHeight.h"
#include "OptStack.h"
#include "ToolVertex.h"
#include "Ndl/NdlWorldEditor.h"
#include <mmsystem.h>
#include "ui/ToolsWnd/ToolTerrain.h"
////////////////////////////////////////////////////////////////////////////////
CToolVertex::CToolVertex()
{
	m_isLock			= false;
	m_isHeightPicked	= false;
	
	SetEditSize( 8.0f );
	SetEditStrength( 50.0f );
	SetEditSpeed( 100.0f );

	m_editType		= znTVT_Unknow;
	m_editVertex[0]	= -1;
	m_editVertex[1]	= -1;

	m_isInvEdit		= false;

	m_layerDlg		= NULL;
}

CToolVertex::~CToolVertex()
{

	delete m_brushShape;
	m_brushShape = 0;
}

bool CToolVertex::Create( CToolManager* toolMgr )
{
	CBaseTool::Create( toolMgr );

	//jiayi [09.02.20]
	BuildBrushShape();


	return true;
}


//jiayi [2009.02.23]
//build the brush mesh
void CToolVertex::BuildBrushShape()
{
	m_brushShape = new swBrushShape();

	float fOuterAngle;
	int i = -1;
	int iIndex = 0;
	float fInnerSize = 2.f;
	float fOutterSize = 4.f;
	for (unsigned int ui = 0; ui < s_usBrushShapeVertexCnt; ++ ui)
	{
		i++;

		if(iIndex < 2 * (s_usInnerSegments + s_usOuterSegments))
		{// creates the needed indexes
			if(i != s_usInnerSegments && i != (s_usBrushShapeVertexCnt - 1))
			{ //the lines from the inner to outer circles and end to beginning 
				// should not be indexed
				m_brushShape->kIndex[iIndex] = (unsigned short)ui;
				iIndex++;
				m_brushShape->kIndex[iIndex] = ui + 1;
				iIndex++;
			}        
		}

		if (i <= s_usInnerSegments)
		{ // inner circle

			//set pos
			m_brushShape->kVertex[ui].p.x = fInnerSize*Cos((float)i/float
				(s_usInnerSegments) * PI2);
			m_brushShape->kVertex[ui].p.y = fInnerSize*Sin((float)i / 
				float(s_usInnerSegments) * PI2);
			m_brushShape->kVertex[ui].p.z = 2.0;
			//set color
			m_brushShape->kVertex[ui].color = 0x00ff0000;

		}
		else
		{ // outer circle
			fOuterAngle = ((float)i - (s_usInnerSegments + 1.5f))/(float)
				s_usOuterSegments*PI2;
			
			//set pos
			m_brushShape->kVertex[ui].p.x = fOutterSize*cos(fOuterAngle);
			m_brushShape->kVertex[ui].p.y = fOutterSize*Sin(fOuterAngle);
			m_brushShape->kVertex[ui].p.z = 0;
			//set color
			m_brushShape->kVertex[ui].color = 0x007f0000;
		}
	}
}

bool CToolVertex::OnLMouseDown( UINT nFlags, CPoint point )
{
	m_isLDrag	= true;
	m_oldPos	= point; 
	
	if( znTVT_Unknow == m_editType )
		return true;
	
	if( 0 != (nFlags&MK_CONTROL) ) {
		m_isInvEdit = true;
	}
	else {
		m_isInvEdit = false;
	}
	COptBase* opt = theApp.GetOptStack()->GetPreOpt();
	//Assert( NULL == opt );
	if( NULL != opt ) {
		opt->End();
		theApp.GetOptStack()->SetPreOpt(NULL);
	}

	Vector2 viewSize;
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	view->GetViewSize( viewSize.x, viewSize.y );
	if( viewSize.x < 1 || viewSize.y < 1 )
		return true;

	SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();
	sInt32 pickId = view->PickWorldTerrain( point );
	if( -1 != pickId ) {
		const TPickResult& pickResult = view->GetPickResult();
		m_editPos[0]		= pickResult.pickResultInfo[pickId].point.x;
		m_editPos[1]		= pickResult.pickResultInfo[pickId].point.y;

		m_pickHeight[0]		= pickResult.pickResultInfo[pickId].point.z;
		m_pickHeight[1]		= pickResult.pickResultInfo[pickId].point.z;

		if( znTVT_Plane == m_editType ) {
			m_editBeginPos[0]	= m_editPos[0];
			m_editBeginPos[1]	= m_editPos[1];
		}
		else {
			BeginTimer( 100 );
		}
	}
	return true;
}

bool CToolVertex::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;

	if( znTVT_Plane == m_editType ) {
		if( m_isHeightPicked )
			BuildTerrainPlane( m_editBeginPos, m_editPos, m_pickHeight );
	}
	else {
		EndTimer();
	}
	
	return true;
}

bool CToolVertex::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return true;
}

bool CToolVertex::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 


	return true;
}

bool CToolVertex::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;



	return true;
}

bool CToolVertex::OnMouseMove( UINT nFlags, CPoint point )
{

	if( 0 != (nFlags&MK_CONTROL) ) {
		m_isInvEdit = true;
	}
	else {
		m_isInvEdit = false;
	}

	m_isHeightPicked	= false;

	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

	//added by zilong. 2011-01-15
	//定位功能会利用该类在定位点上画上圆圈，此处清除定位标志。
	view->ResetLocationFlag();

	SwCamera* camera	= view->GetActiveCamera();
	if( m_isRDrag ){	// move
		CameraAdjust(point, nFlags);
	}
	else if( m_isLDrag ) {
		sInt32 pickId = view->PickWorldTerrain( point );
		if( -1 != pickId ) { 
			const TPickResult& pickResult = view->GetPickResult();

			m_editPos[0]		= pickResult.pickResultInfo[pickId].point.x;
			m_editPos[1]		= pickResult.pickResultInfo[pickId].point.y;
			m_pickHeight[1]		= pickResult.pickResultInfo[pickId].point.z;
			m_isHeightPicked	= true;
		}
	}
	else {
		sInt32 pickId = view->PickWorldTerrain( point );
		if( -1 != pickId ) { 
			const TPickResult& pickResult = view->GetPickResult();
			flt32 pos[2];
			pos[0] = pickResult.pickResultInfo[pickId].point.x;
			pos[1] = pickResult.pickResultInfo[pickId].point.y;
			
			UpdateBrushShape( pos );
		}
		else
		{
		}
	}
	camera->Update( 0.0f, 0.0f );

	return true;
}

bool CToolVertex::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if( nChar == VK_CONTROL ) {
		m_isInvEdit = true;
	}

	return true;
}

bool CToolVertex::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);
	if( nChar == VK_SPACE ) {
		m_isLock = !m_isLock;
	}
	if( nChar == VK_CONTROL ) {
		m_isInvEdit = false;
	}
	if( nChar == VK_OEM_4 ) 
	{
		m_editSize = ZnMax(0.f,m_editSize - 1);
		m_layerDlg->EditSizeChanged(m_editSize);

	}
	if( nChar == VK_OEM_6 ) 
	{
		m_editSize = ZnMin(120.f,m_editSize + 1);
		m_layerDlg->EditSizeChanged(m_editSize);
	}
	
	return true;
}

void CToolVertex::Render()
{
	//jiayi [09.02.20]
	IRenderer* r = GetEngine()->GetRenderer();
	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	r->SetTransform( D3DTS_WORLD, (float*)&world );
	r->DirectPushSurface(
		-1,				
		-1,				
		-1,
		D3DFVF_XYZ|D3DFVF_DIFFUSE,
		sizeof( swBrushShapeVertex ),
		(BYTE*)(&m_brushShape->kVertex),
		s_usBrushShapeVertexCnt,
		(BYTE*)(&m_brushShape->kIndex),
		s_usBrushShapeIdxCnt - 96,eLightingDisable, D3DPT_LINELIST );
}

void CToolVertex::SetEditSize( flt32 editSize )
{
	m_editSize		= editSize * WORLD_VERTSIZE;
}

void CToolVertex::SetEditStrength( flt32 editStrength )
{
	m_editStrength	= (editStrength*0.01f)*(WORLD_VERTSIZE);
}

void CToolVertex::SetEditSpeed( flt32 editSpeed )
{
	m_editSpeed		= editSpeed * 0.01f;
}

void CToolVertex::SetEditMode( znVertexEditType editType )
{
	m_editType		= editType;
}

void CToolVertex::UpdateBrushShape(const flt32* origin_, float innerRadius_, float outterRadius_)
{
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	if( NULL == view )
		return;
	CNdlEditWorldPicker* worldPicker = view->GetWorldPicker();
	if( NULL == worldPicker )
		return;

	float fOuterAngle;
	int i = -1;
	int iIndex = 0;
	float fInnerSize = innerRadius_;
	float fOutterSize = outterRadius_;
	for (unsigned int ui = 0; ui < s_usBrushShapeVertexCnt; ++ ui)
	{
		++i;

		if (i <= s_usInnerSegments)
		{ // inner circle

			//set pos
			m_brushShape->kVertex[ui].p.x = fInnerSize*Cos((float)i/float
				(s_usInnerSegments) * PI2) + origin_[0];
			m_brushShape->kVertex[ui].p.y = fInnerSize*Sin((float)i / 
				float(s_usInnerSegments) * PI2) + origin_[1];


		}
		else
		{ // outer circle
			fOuterAngle = ((float)i - (s_usInnerSegments + 1.5f))/(float)
				s_usOuterSegments*PI2;

			//set pos
			m_brushShape->kVertex[ui].p.x = fOutterSize*cos(fOuterAngle) + origin_[0];
			m_brushShape->kVertex[ui].p.y = fOutterSize*Sin(fOuterAngle) + origin_[1];

		}
		if(worldPicker->GetHeight(m_brushShape->kVertex[ui].p.x, 
			m_brushShape->kVertex[ui].p.y, 
			m_brushShape->kVertex[ui].p.z))
		{
			//add an offset to make the circle clear.
			m_brushShape->kVertex[ui].p.z += 0.1f;
		}		
	}
}

void CToolVertex::UpdateBrushShape( flt32* origin )
{
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	if( NULL == view )
		return;
	CNdlEditWorldPicker* worldPicker = view->GetWorldPicker();
	if( NULL == worldPicker )
		return;
	
	float fOuterAngle;
	int i = -1;
	int iIndex = 0;
	float fInnerSize = 2.f * m_editSize * 0.125f;
	float fOutterSize = 4.f * m_editSize * 0.125f;
	for (unsigned int ui = 0; ui < s_usBrushShapeVertexCnt; ++ ui)
	{
		++i;

		if (i <= s_usInnerSegments)
		{ // inner circle

			//set pos
			m_brushShape->kVertex[ui].p.x = fInnerSize*Cos((float)i/float
				(s_usInnerSegments) * PI2) + origin[0];
			m_brushShape->kVertex[ui].p.y = fInnerSize*Sin((float)i / 
				float(s_usInnerSegments) * PI2) + origin[1];
			

		}
		else
		{ // outer circle
			fOuterAngle = ((float)i - (s_usInnerSegments + 1.5f))/(float)
				s_usOuterSegments*PI2;

			//set pos
			m_brushShape->kVertex[ui].p.x = fOutterSize*cos(fOuterAngle) + origin[0];
			m_brushShape->kVertex[ui].p.y = fOutterSize*Sin(fOuterAngle) + origin[1];
			
		}
		if(worldPicker->GetHeight(m_brushShape->kVertex[ui].p.x, 
			m_brushShape->kVertex[ui].p.y, 
			m_brushShape->kVertex[ui].p.z))
		{
			//add an offset to make the circle clear.
			m_brushShape->kVertex[ui].p.z += 0.1f;
		}		
	}

}

bool CToolVertex::OnTimer( )	
{ 
	flt32 deltaHeight = (WORLD_VERTSIZE) * m_editStrength * m_editSpeed;
	if( m_isInvEdit )
		deltaHeight = - deltaHeight;

	switch( m_editType )
	{
	case znTVT_UpDown:
		

		theApp.GetWorldEditor()->UpDownVert( m_editPos, m_editSize, deltaHeight );
		
		
		break;
	case znTVT_Smooth:
		
		theApp.GetWorldEditor()->SmoothVert( m_editPos, m_editSize, m_editStrength * m_editSpeed );
		
		break;
	//case znTVT_Plane:
	//	break;
	case znTVT_Euqal:
		
		theApp.GetWorldEditor()->EqualVert( m_editPos, m_editSize, m_pickHeight[0] );
		
		break;
	default:
		break;
	}

	UpdateBrushShape( m_editPos );

	return false; 
}

bool CToolVertex::BuildTerrainPlane( const flt32* beginPos, const flt32* endPos, const flt32* height )
{
	flt32 bPos[3], ePos[3];
	bPos[0]		= beginPos[0];
	bPos[1]		= beginPos[1];
	bPos[2]		= height[0];

	ePos[0]		= endPos[0];
	ePos[1]		= endPos[1];
	ePos[2]		= height[1];

	return theApp.GetWorldEditor()->PlaneVert( bPos, ePos, m_editSize );
	
}
