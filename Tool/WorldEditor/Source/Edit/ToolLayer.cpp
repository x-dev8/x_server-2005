/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolLayer.cpp
* Date: 	03/14/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "EditRes/NdlEditRes.h"
#include "ToolLayer.h"
#include "OptStack.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/ToolsWnd/ToolLayer.h"
#include "Ndl/NdlWorldEditor.h"
#include "MeTerrain/World.h"
#include "ToolManager.h"

////////////////////////////////////////////////////////////////////////////////
CToolLayer::CToolLayer()
{
	m_isLock		= false;
	m_layerDlg		= NULL;
	m_selWorldChunk	= NULL;
	m_selResMgr		= NULL;
	m_alpha			= 0xFF;
	m_textureId		= RES_INVALID_ID;
	m_brushId		=  2;
	m_paintMode		=  znLBM_Add;
	m_flow			= 50;
	m_texInfoList.clear();
	m_brushList.clear();

	m_brushDecal	= NULL;
	m_isPaintShadow = true;
	m_multiSel      = false;
}

CToolLayer::~CToolLayer()
{
	m_selWorldChunk	= NULL;
	m_selResMgr		= NULL;
	m_layerDlg		= NULL;

	SAFE_DELETE( m_brushDecal );

	for( size_t i=0; i< m_brushList.size(); i++ ) {
		TLayerBrush* p = m_brushList[i];
		SAFE_DELETE( p );
	}
	m_brushList.clear();
	for( size_t i=0; i<m_texInfoList.size(); i++ ) {
		SAFE_DELETE( m_texInfoList[i] );
	}
	m_texInfoList.clear();

	delete m_brushDecal;
	m_brushDecal = 0;
}

bool CToolLayer::Create( CToolManager* toolMgr )
{
	CBaseTool::Create( toolMgr );

	if( !LoadLayerBrush() )
		return false;

	if( !LoadLayerTexture() )
		return false;

	m_brushDecal = MeNew CNdlDecalRes();
	char path[MAX_PATH];
	sprintf_s( path, "%s\\Required\\Helper\\brushDecal.tga", CWorld::GetAppCharDir() );
	m_brushDecal->Create( path, 30 );
	m_brushDecal->SetScale( GetBrushDecalScale() );

	return true;
}

void CToolLayer::Bind( CToolLayerDlg* dlg )
{
	m_layerDlg = dlg;
}

bool CToolLayer::LoadLayerTexture()
{
	MeXmlDocument Doc;
	char fileName[MAX_PATH*2];
	sprintf_s( fileName, "%s\\Required\\Config\\layer.xml", CWorld::GetAppCharDir() );
	if( !Doc.LoadFile( fileName ) )
		return false;
	MeXmlElement* root = Doc.FirstChildElement( "Config" );
	if( NULL != root ) {
		MeXmlElement* xmlElmt = root->FirstChildElement();
		while( NULL != xmlElmt ) {
			MeXmlElement* subElmt = xmlElmt->FirstChildElement();
			while( NULL != subElmt ) {
				const char* brushName	= subElmt->Attribute( "name" );
				ASSERT( NULL != brushName );
				ASSERT( (strlen(brushName)+1) < RES_NAME_LEN );
				const char* pathName		= subElmt->Attribute( "data" );
				ASSERT( NULL != pathName );
				ASSERT( (strlen(pathName)+1) < MAX_PATH );
				CString dir;
				dir.Format( _T("%s\\%hs"), CWorld::GetAppDataCharDir(), pathName );
				EnumFile( dir );
				subElmt = subElmt->NextSiblingElement();
			}
			xmlElmt	= xmlElmt->NextSiblingElement();
		}
	}
	return true;
}

bool CToolLayer::LoadLayerBrush()
{
	MeXmlDocument Doc;
	char fileName[MAX_PATH*2];
	sprintf_s( fileName, "%s\\Required\\Config\\Brush.xml", CWorld::GetAppCharDir() );
	if( !Doc.LoadFile( fileName ) )
		return false;
	MeXmlElement* root = Doc.FirstChildElement( "Config" );
	if( NULL != root ) {
		MeXmlElement* xmlElmt = root->FirstChildElement();
		while( NULL != xmlElmt ) {
			MeXmlElement* subElmt = xmlElmt->FirstChildElement();
			while( NULL != subElmt ) {
				const char* brushName	= subElmt->Attribute( "name" );
				ASSERT( NULL != brushName );
				ASSERT( (strlen(brushName)+1) < RES_NAME_LEN );
				const char* texName		= subElmt->Attribute( "data" );
				ASSERT( NULL != texName );
				ASSERT( (strlen(texName)+1) < MAX_PATH );

				CString path;
				path.Format( _T("%s\\%hs"), theApp.GetAppDir(), texName );

				if( !LoadBrushFromBitmap( path, brushName ) ) {
					Trace( "<<<ERROR>>> can't load brush[%s] \n", texName );
				}
				subElmt = subElmt->NextSiblingElement();
			}
			xmlElmt	= xmlElmt->NextSiblingElement();
		}
	}
	return true;
}

bool CToolLayer::LoadBrushFromBitmap( LPCTSTR fileName, const char* brushName )
{
	CImage image;
	if( S_OK != image.Load( fileName ) ) {
		return false;
	}	
	TLayerBrush* newBrush	= new TLayerBrush;
	strcpy_s( newBrush->brushName, brushName );
	Assert( image.GetWidth() == image.GetHeight() );
	newBrush->brushSize		= image.GetWidth();
	newBrush->brushData		= new uInt8[newBrush->brushSize*newBrush->brushSize];
	uInt8* dataPtr			= newBrush->brushData;
	for( sInt32 y=0; y<newBrush->brushSize; y++ ) {
		for( sInt32 x=0; x<newBrush->brushSize; x++ ) {
			COLORREF col = image.GetPixel(x,y);
			// 取红色高4位.
			uInt8 alpha = col&0xF0;
			alpha		|= (alpha>>4);
			*dataPtr	= alpha;
			dataPtr++;
		}
	}
	m_brushList.push_back( newBrush );

	return true;
}

void CToolLayer::EnumFile( LPCTSTR strDir )
{
	CFileFind ff;
	CString strPath( strDir );
	strPath += _T("\\*.*");
	BOOL bFound = ff.FindFile(strPath);
	if (!bFound) 
		return;

	char objPath[MAX_PATH*2];
	char objName[MAX_PATH*2];
	while (bFound)	{
		bFound = ff.FindNextFile();

		if (ff.IsDots())
			continue;

		strPath = ff.GetFilePath();
		if ( ff.IsDirectory() ) {
			EnumFile( strPath );
		}
		else{
			if( !SpliteFullPathToDataPath( strPath, objPath, objName ) ) {
				continue;
			}
			_strlwr_s( objName );
			const char* strTga = strstr( objName, ".tga" );
			const char* strPng = strstr( objName, ".png" );
			const char* strDDS = strstr( objName, ".dds" );

			ENUM_CXIMAGE_FORMATS texFormat;
			if( NULL !=strTga && strlen(strTga) == 4) {
				texFormat = CXIMAGE_FORMAT_TGA;
			}
			else if( NULL!=strPng && strlen(strPng) == 4)	{
				texFormat = CXIMAGE_FORMAT_PNG;
			}
			else if( NULL!=strDDS && strlen(strDDS) == 4) {
				texFormat = CXIMAGE_FORMAT_DDS;
			}
			else {
				continue;
			}
			_strlwr_s( objPath );
			if( !FindTexture( objPath, objName ) ) {
				TNameInfo* newInfo	= new TNameInfo;
				strcpy_s( newInfo->path, objPath );
				strcpy_s( newInfo->name, objName );
				newInfo->format	= texFormat;
				m_texInfoList.push_back( newInfo );
			}
		}
	}	
}

bool CToolLayer::FindTexture( const char* path, const char* fileName )
{
	for( size_t i=0; i<m_texInfoList.size(); i++ ) {
		TNameInfo* p = m_texInfoList[i];
		if( (strcmp(p->name,fileName) == 0) && (strcmp( p->path, path )==0) ) {
			return true;
		}
	}
	return false;
}

const TLayerBrush* CToolLayer::GetBrush( size_t brushId ) const
{
	Assert( (brushId >=0) && (brushId<m_brushList.size()) );
	return m_brushList[brushId];
}


bool CToolLayer::OnLMouseDown( UINT nFlags, CPoint point )
{
	if(m_multiSel)
	{
		for(int i=0;i<m_vecWorldChunk.size();++i)
		{
			if(m_vecWorldChunk[i]==m_selWorldChunk)
			{
				//m_selResMgr->RefreshLiquidHeight(m_vecWorldChunk[i],m_height,m_NiColor,m_alphaCoaf);

				m_vecWorldChunk.erase(m_vecWorldChunk.begin()+i);

				return true;
			}
		}

		m_selWorldChunk->RenderWireFrame(true);
		m_vecWorldChunk.push_back(m_selWorldChunk);
	}
	else
	{
		m_isLDrag	= true;

		PaintSth(nFlags,point);
	}

	return true;
}

bool CToolLayer::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;


	return true;
}

bool CToolLayer::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return true;
}

bool CToolLayer::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 


	return true;
}

bool CToolLayer::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;



	return true;
}

TNameInfo* CToolLayer::GetTexNameInfoFromId( sInt32 textureId )
{
	if( textureId<0 || textureId>=m_texInfoList.size() )
		return NULL;

	return m_texInfoList[textureId];
}

bool CToolLayer::PaintPoint( flt32* pt, bool isInv )
{
	if( -1 == m_brushId )
		return false;

	TNameInfo* nameInfo = GetTexNameInfoFromId( m_textureId );
	if( NULL == nameInfo )
		return false;

	const TLayerBrush* brush = GetBrush( m_brushId );
	sInt32 currPaintMode = m_paintMode;
	if (isInv)
	{
		switch (m_paintMode)
		{
		case znLBM_InvAdd:
			currPaintMode = znLBM_Add;
			break;
		case znLBM_Add:
			currPaintMode = znLBM_InvAdd;
			break;
		case znLBM_SetDown:
			currPaintMode = znLBM_SetUp;
			break;

		case znLBM_SetUp:
			currPaintMode = znLBM_SetDown;
			break;
		}
	}

	char path[MAX_PATH];
	sprintf_s( path, "%s\\%s", nameInfo->path, nameInfo->name );
	theApp.GetWorldEditor()->PaintTexture( pt, brush->brushData, brush->brushSize, path, m_alpha, currPaintMode );

	return true;
}

bool CToolLayer::PaintShadow( flt32* pt, bool isAddShadow , uInt8 alpha)
{
	const TLayerBrush* brush = GetBrush( m_brushId );
	theApp.GetWorldEditor()->PaintShadow( pt, brush->brushData, brush->brushSize, isAddShadow,alpha );

	return true;
}

bool CToolLayer::PaintVertexColor( flt32* pt, bool isAdd , uInt8 alpha)
{
	const TLayerBrush* brush = GetBrush( m_brushId );
	theApp.GetWorldEditor()->PaintVertexColor( pt,  brush->brushSize,m_NiColor,m_flow,isAdd,alpha);

	return true;
}

bool CToolLayer::UpdateLayer( flt32* pt )
{
	if( m_isLock )
		return false;

	if( theApp.GetWorldEditor()->GetSelWorld( pt, &m_selWorldChunk, &m_selResMgr ) ) {
		if( NULL != m_layerDlg ) {
			m_layerDlg->RefreshLayer();
		}
	}
	return true;
}

bool CToolLayer::OnMouseMove( UINT nFlags, CPoint point )
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
		PaintSth( nFlags,point );
	}
	else {
		sInt32 pickId = view->PickWorldTerrain( point );
		if( -1 != pickId ) { 
			const TPickResult& pickResult = view->GetPickResult();
			flt32 pt[2];
			pt[0] = pickResult.pickResultInfo[pickId].point.x;
			pt[1] = pickResult.pickResultInfo[pickId].point.y;
			DecalUpdate(pt);
			UpdateLayer( pt );
		}
	}
	camera->Update( 0.0f, 0.0f );

	return true;
}

bool CToolLayer::OnMouseWheel( UINT nFlags, short zDelta, CPoint point)
{
	Vector2 viewSize;
	CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetViewSize( viewSize.x, viewSize.y );
	if( viewSize.x < 1 || viewSize.y < 1 )
		return false;

	Vector deltaPos;
	deltaPos.x	= zDelta / 32.0f;
	deltaPos.y  = 0.0f;
	deltaPos.z	= 0.0f;

	if( 0 != (nFlags&MK_CONTROL) ) {
		deltaPos = deltaPos * CAMERA_HUGE_STEP;
	}

	CameraFarNear(deltaPos);

	return true;
}

bool CToolLayer::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{

	return true;
}

bool CToolLayer::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);
	if( nChar == VK_SPACE ) {
		SetLock( !m_isLock );
		m_layerDlg->UpdateLock( m_isLock );
	}
	if( nChar == VK_OEM_4 ) 
	{
		if (m_brushId > 0)
		{
			--m_brushId;
			m_layerDlg->BrushChanged(m_brushId);
			m_brushDecal->SetScale( GetBrushDecalScale() );
		}		

	}
	if( nChar == VK_OEM_6 ) 
	{
		if (m_brushId + 1 < m_brushList.size())
		{
			++m_brushId;
			m_layerDlg->BrushChanged(m_brushId);
			m_brushDecal->SetScale( GetBrushDecalScale() );
		}		

	}
	if( nChar == '9' ) 
	{
		m_paintMode = ZnMax<sInt32>(znLBM_Add,m_paintMode - 1);
		m_layerDlg->PaintModeChange(m_paintMode);
	}
	if (nChar == '0')
	{
		m_paintMode = ZnMin<sInt32>(znLBM_InvVertexCorlor,m_paintMode + 1);
		m_layerDlg->PaintModeChange(m_paintMode);
	}
	return true;
}

void CToolLayer::Render()
{
	m_brushDecal->Render();
}

bool CToolLayer::ClearVertexColor( flt32* pt )
{
	const TLayerBrush* brush = GetBrush( m_brushId );
	theApp.GetWorldEditor()->ClearVertexColor( pt,  brush->brushSize);

	return true;

}

flt32 CToolLayer::GetBrushDecalScale()
{
	const TLayerBrush* brush = GetBrush( m_brushId );
	flt32 fNewScale = (brush->brushSize)*1.0f;
	if (m_paintMode != znLBM_VertexCorlor
		&& m_paintMode != znLBM_InvVertexCorlor)
	{
		fNewScale /= 4;
	}
	return fNewScale/64;
}

bool CToolLayer::OnWTPacket( PACKET& packet,CPoint& point )
{
	uInt8 alpha	= ZnMin<int>(packet.pkNormalPressure, 511)/2;

#ifdef _DEBUG
	char temp[128] = {0};
	sprintf(temp, "pressure: %d, alpha: %d\n", packet.pkNormalPressure, alpha);
	OutputDebugString(temp);
#endif

	if ((znLBM_VertexCorlor != m_paintMode) && (m_paintMode != znLBM_InvVertexCorlor))
	{
		if (m_layerDlg->IsUseWinTabPressAsAlpha())
		{
			alpha			= alpha & 0xF0;
			alpha			= alpha|(alpha>>4);
			m_layerDlg->ShowAlphaText(alpha);
			m_alpha = alpha;
		}
	}

	m_flow = alpha*100/255;
	m_layerDlg->FlowChanged(m_flow);
	// 	if ((packet.pkButtons) & 2 )
	// 	{
	// 		return CameraAdjust(point, 0);		
	// 	}
	// 	else if((packet.pkButtons) & 4)
	// 	{
	// 		return CameraAdjust(point, MK_SHIFT);		
	// 	}

	if (alpha > 0)
	{
		int nFlags = 0;
		if (packet.pkCursor == 1)
		{
			switch (m_paintMode)
			{
			case znLBM_InvAdd:
				m_paintMode = znLBM_Add;
				break;
			case znLBM_SetDown:
				m_paintMode = znLBM_SetUp;
				break;

			case znLBM_InvVertexCorlor:
				m_paintMode = znLBM_VertexCorlor;
				break;
			}
		}
		else if(packet.pkCursor == 2)
		{
			switch (m_paintMode)
			{
			case znLBM_Add:
				m_paintMode = znLBM_InvAdd;
				break;
			case znLBM_SetUp:
				m_paintMode = znLBM_SetDown;
				break;

			case znLBM_VertexCorlor:
				nFlags |= MK_CONTROL;
				break;
			}

		}
		m_layerDlg->PaintModeChange(m_paintMode);
		//		PaintSth(nFlags,point);
	}
	// 	else
	// 	{
	// 		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	// 		sInt32 pickId = view->PickWorldTerrain( point );
	// 		if( -1 != pickId ) { 
	// 			const TPickResult& pickResult = view->GetPickResult();
	// 			flt32 pt[2];
	// 			pt[0] = pickResult.pickResultInfo[pickId].point.x;
	// 			pt[1] = pickResult.pickResultInfo[pickId].point.y;
	// 			DecalUpdate(pt);
	// 			UpdateLayer( pt );
	// 		}
	// 	}
	return true;
}

void CToolLayer::PaintSth(UINT nFlags , CPoint point)
{
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	sInt32 pickId = view->PickWorldTerrain( point );
	if( -1 != pickId ) { 
		const TPickResult& pickResult = view->GetPickResult();
		flt32 pt[2];
		pt[0] = pickResult.pickResultInfo[pickId].point.x;
		pt[1] = pickResult.pickResultInfo[pickId].point.y;
		DecalUpdate(pt);
		{
			bool isInv = false;
			if( 0 != (nFlags&MK_CONTROL) ) {
				isInv = true;
			}
			if( m_paintMode == znLBM_Shadow ) 
			{
				if (m_isPaintShadow)
				{
					PaintShadow( pt, !isInv,m_alpha );
				}
				else
				{
					PaintRoad( pt, !isInv,m_alpha );
				}
			}
			else if (m_paintMode == znLBM_VertexCorlor)
			{
				if (isInv)
					ClearVertexColor(pt);
				else
					PaintVertexColor(pt,!isInv,m_alpha);
			}
			else if ( m_paintMode == znLBM_InvVertexCorlor)
			{
				PaintVertexColor(pt, false, m_alpha);
			}
			else {
				PaintPoint( pt, isInv );
			}
			UpdateLayer( pt );
		}
		m_oldPos	= point; 
	}
}

void CToolLayer::DecalUpdate( flt32 * pt )
{
	m_brushDecal->SetPos( pt );
	m_brushDecal->SetScale( GetBrushDecalScale() );
}

bool CToolLayer::PaintRoad( flt32* pt, bool isAddShadow, uInt8 alpha )
{
	const TLayerBrush* brush = GetBrush( m_brushId );
	theApp.GetWorldEditor()->PaintRoad( pt, brush->brushData, brush->brushSize, isAddShadow,alpha );

	return true;

}

void CToolLayer::SetPaintShadow( bool val )
{
	m_isPaintShadow = val;
	// 	m_selResMgr->SetRoadShow(!m_isPaintShadow);
}

void CToolLayer::setMultiSel(bool b)
{
	m_multiSel = b;

	if(m_multiSel)
	{
		m_vecWorldChunk.clear();
	}
	else
	{
		m_vecWorldChunk.clear();
	}
}