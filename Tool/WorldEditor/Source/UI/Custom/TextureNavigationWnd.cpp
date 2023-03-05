/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	TextureNavigationWnd.cpp
* Date: 	07/03/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "TextureNavigationWnd.h"
#include "ui/ToolsScene/ToolWorld.h"
#include "ReachableMapGenerate.h"
#include "ndl/NdlHelper.h"
#include "SwMap.h"
namespace {

	const sInt32 l_width	= 220;
	const sInt32 l_height	= 220;
}

////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CTextureNavigationWnd, CStatic)
	//{{AFX_MSG_MAP(CTextureNavigationWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////
CTextureNavigationWnd::CTextureNavigationWnd()
:m_showArea(0.f,0.f,0.f,0.f),m_tileArea(0.f,0.f,0.f,0.f)
{
	m_pParentWnd	= NULL;
	m_heightScale	= 1.f;
	m_sizeScale		= 1.f;
	m_isShowReachable = false;
	m_isShowGrid	= false;
	m_flagModel		= 0;
	Reset();
}

CTextureNavigationWnd::~CTextureNavigationWnd()
{
	m_pParentWnd = NULL;
	m_flagModel = 0;
}

void CTextureNavigationWnd::Init(UINT nID, CToolWorld* pParentWnd)
{
	m_pParentWnd	= pParentWnd;
	m_hasTexture	= false;
	if( FALSE == SubclassDlgItem(nID, pParentWnd) ) {
		AfxMessageBox( _T("不能创建子控件!") );
	}
	m_image.Create( l_width, l_height, 24 );
	for( sInt32 y = 0; y< l_height; y++ ) {
		for( sInt32 x = 0; x< l_width; x++ ) {
			m_image.SetPixelColor( x, y, 0x80808080 );
		}
	}
	m_hasTexture = false;
	MoveWindow( 6, 400, l_width, l_height );

}

void CTextureNavigationWnd::Reset()
{
	m_cameraDir			= Vector( -1.0f, 0.0f, 0.0f );//( 0.0f, 1.0f, 0.0f );

	m_curTileObjCount	= 0;

	m_curTile			= NULL;
	
	m_hasTexture		= false;
	m_isShowGrid		= false;
	m_isShowReachable	= false;
}

bool CTextureNavigationWnd::SetTextureName( const char* textureName )
{
	if( NULL != textureName ) {
		TCHAR strName[MAX_PATH];
		_stprintf_s( strName, _T("%s\\%hs"), CWorld::GetAppDataCharDir(), textureName );
		if( _tcscmp( m_textureName, strName ) != 0 ) {
			_tcscpy_s( m_textureName, strName );
			if( !m_image.Load( m_textureName, CXIMAGE_FORMAT_PNG  ) ) {
				m_hasTexture = false;
				return false;
			}
			m_hasTexture = true;
		}
	}
	else {
		_tcscpy_s( m_textureName, _T("No texture") );
		m_hasTexture = false;
	}
	Invalidate();
	return true;
}

bool CTextureNavigationWnd::SetTexture( const char* path, const char* textureName )
{
	if( NULL != textureName && NULL != path ) {
		_stprintf_s( m_textureName, _T("%s\\%hs\\%hs"), CWorld::GetAppDataCharDir(), path, textureName );
		if( !m_image.Load( m_textureName, CXIMAGE_SUPPORT_DDS  ) ) {
			m_hasTexture = false;
			return false;
		}
		m_hasTexture = true;
	}
	else {
		m_hasTexture = false;
	}
	Invalidate();
	return true;
}

void CTextureNavigationWnd::UpdateMinimap()
{
	
	if (NULL == CURRENTTILE)
	{
		return;
	}
	UpdateCurrTile(  );
	
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	SwCamera* camera		= view->GetActiveCamera();
	
	Vector rot			= camera->GetRot();
	NiMatrix3 matRot;
	//matRot.FromEulerAnglesXYZ( rot.z, rot.y, 0.0f );
	matRot.FromEulerAnglesXYZ( rot.x, 0.0f, rot.z );
	m_cameraDir				= Vector( -1.0f, 0.0f, 0.0f )/*( 0.0f, 1.0f, 0.0f )*/ * matRot;
	m_cameraDir.z			= m_cameraDir.y;
	m_cameraDir.y			= m_cameraDir.x;
	m_cameraDir.x			= -m_cameraDir.z;//m_cameraDir.z;
	m_cameraDir.z			= 0.0f;
	m_cameraDir.normalize();
	
	CString strPromt;
	sInt32 axis[2];
	Vector pos			= camera->GetPos();
	axis[0]					= ChunkFromPos(pos.x);
	axis[1]					= ChunkFromPos(pos.y);
	

	strPromt.Format( _T("摄像机所在Tile:[%hs(%d*%d)] 坐标:(%02d,%02d) 物体个数:[%d]")
						, m_curTile->GetPathName(),m_curTile->GetRowColumn()[0],m_curTile->GetRowColumn()[1], axis[0], axis[1], m_curTileObjCount );
	
	m_pParentWnd->SetTilePrompt( strPromt );
	

	Invalidate( FALSE );
}

void CTextureNavigationWnd::ShowGrid( bool isShowGrid )
{
	m_isShowGrid = isShowGrid;
}


void CTextureNavigationWnd::UpdateCurrTile(  )
{
	for( sInt32 y=0; y<l_height; y++ ) {
		for( sInt32 x=0; x<l_width; x++ ) {
			COLORREF color = RGB( 0xFF, 0x00, 0xFF );
			m_image.SetPixelColor( x, y, color );
		}
	}
	CWorldBuffer* pBuffer = theApp.GetWorld()->m_worldBuffer;

	m_curTile = pBuffer->GetActiveTile();	


	if( NULL == m_curTile ) {
		return;
	}

	if( (-swInfinity == m_curTile->m_height[0]) || (swInfinity == m_curTile->m_height[1]) )
		return;

	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	SwCamera* camera		= view->GetActiveCamera();
//	theApp.GetWorld()->GetActivePos(m_centerPos.x,m_centerPos.y);

	m_centerPos = camera->GetPos();
	 
	flt32 fpixelRealSize = WORLD_VERTSIZE*m_sizeScale;//当m_showAreaScale==1的时候每一个像素代表一个WORLD_VERTSIZE
	flt32 halfShowSizeWidth = fpixelRealSize*l_width/2;
	flt32 halfShowSizeHeight = fpixelRealSize*l_height/2;

	if (m_centerPos.x - halfShowSizeWidth > 0)
	{
		m_tileArea.left = m_centerPos.x - halfShowSizeWidth;
		m_showArea.left = 0;
	}
	else
	{
		m_tileArea.left = 0;
		m_showArea.left	= ZnFloat2Int((halfShowSizeWidth - m_centerPos.x)/fpixelRealSize );
	}
	if (m_centerPos.y - halfShowSizeHeight > 0)
	{
		m_tileArea.bottom = m_centerPos.y - halfShowSizeHeight;
		m_showArea.bottom = 0;
	}
	else
	{
		m_tileArea.bottom = 0;
		m_showArea.bottom	= ZnFloat2Int((halfShowSizeHeight - m_centerPos.y)/fpixelRealSize );
	}

	if (m_centerPos.x + halfShowSizeWidth > m_curTile->GetRowColumn()[0]*WORLD_CHUNKSIZE)
	{
		m_tileArea.right = m_curTile->GetRowColumn()[0]*WORLD_CHUNKSIZE;
		m_showArea.right = m_showArea.left + ZnFloat2Int((m_tileArea.right - m_tileArea.left)/fpixelRealSize);
	}
	else
	{
		m_tileArea.right = m_centerPos.x + halfShowSizeWidth;
		m_showArea.right = l_width;
	}

	if (m_centerPos.y + halfShowSizeHeight > m_curTile->GetRowColumn()[1]*WORLD_CHUNKSIZE)
	{
		m_tileArea.top = m_curTile->GetRowColumn()[1]*WORLD_CHUNKSIZE;
		m_showArea.top = m_showArea.bottom + ZnFloat2Int((m_tileArea.top - m_tileArea.bottom)/fpixelRealSize);
	}
	else
	{
		m_tileArea.top = m_centerPos.y + halfShowSizeHeight;
		m_showArea.top = l_height;
	}

	CNdlEditWorldPicker* pPicker = view->GetWorldPicker();
	sInt32 col			= 0;

	Vector pos(m_tileArea.left + fpixelRealSize * 0.5f,m_tileArea.bottom + fpixelRealSize * 0.5f,0.f);
	for (sInt32 x = m_showArea.left;(x < m_showArea.right); ++x)
	{		
		for (sInt32 y = m_showArea.bottom;(y < m_showArea.top); ++y)
		{			
			THeightResult pickResult;
			if (!pPicker->GetHeight( pos.x, pos.y, pickResult ))
			{
				Trace( "Can't get height[%4.2f:%4.2f] \n", pos.x,pos.y);
				continue;
			}

			col = 0xFF - ZnFloat2Int( (pickResult.height-m_curTile->m_height[0])/m_heightScale );
			if( col < 0x0 )
				col = 0x0;
			if( col > 0xFF )
				col = 0xFF;
			COLORREF color;
			sInt32 r = col,g =col,b = col;
			if (pickResult.isInLiquid)
			{
				r = 80;
				g = 80;
				b = 200;
			}
			if (m_isShowReachable)
			{
				char ret = CReachableMapGenerate::Instance()->IsRealPosReachable(pos.x,pos.y,m_curTile->GetReachableAngle()*PIOVER180,&pickResult);
				switch (ret)
				{
				case SwMap::MAIN_ROAD:
					{
						r = 80;
						g = 200;
						b = 80;
						break;
					}
				case SwMap::SUB_ROAD:
					{
						r = 200;
						g = 200;
						b = 80;
						break;
					}
				case SwMap::OTHERS:
					{
						r = 80;
						g = 200;
						b = 200;
						break;
					}
				}
			}
			color  = RGB( r, g, b );
			m_image.SetPixelColor( x, y, color );
 			pos.y += fpixelRealSize;
// 			if (pos.y > top)
// 			{
// 				break;
// 			}
		}
		pos.y = m_tileArea.bottom + fpixelRealSize * 0.5f;
 		pos.x += fpixelRealSize;
// 		if (pos.x > right)
// 		{
// 			break;
// 		}
	}
	
	
	sInt32 id			= 0;
	sInt32 pX = 0, pY	= 0;
	
	m_curTileObjCount = 0;

	m_curTileObjCount += m_curTile->GetCResMgr()->GetStaticModelList().size();
	m_hasTexture = true;
}


void CTextureNavigationWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if( !theApp.GetWorld()->IsActive() )
		return;
	
	if( (m_curTile == NULL))
		return;
	
	if( point.x < m_showArea.left || point.x > m_showArea.right)
		return;
	
	if( point.y < l_height - m_showArea.top || point.y > l_height -  m_showArea.bottom)
		return;
	
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	SwCamera* camera		= view->GetActiveCamera();
	flt32 fpixelRealSize = WORLD_VERTSIZE*m_sizeScale;//当m_showAreaScale==1的时候每一个像素代表一个WORLD_VERTSIZE



	Vector oldPos;
	theApp.GetWorld()->GetActivePos(oldPos.x,oldPos.y);
	view->GetWorldPicker()->GetHeight( oldPos.x, oldPos.y, oldPos.z );

	Vector newPos = oldPos;
	newPos.x += (point.x-l_width/2)*fpixelRealSize;
	newPos.y += (l_height/2-point.y)*fpixelRealSize;
// 	theApp.GetWorld()->SetActivePos( newPos.x, newPos.y );
// 
// 	view->GetWorldPicker()->GetHeight( newPos.x, newPos.y, newPos.z );
// 	GetFlagModel()->SetTranslate(newPos);
// 	GetFlagModel()->Update(0.f);


	Vector deltaPos;
	deltaPos.x	= newPos.x - oldPos.x;//(newPos.z - oldPos.z);
	deltaPos.y  =  (newPos.y - oldPos.y);
	deltaPos.z	= newPos.z - oldPos.z;
	Vector cameraPos = camera->GetPos() + deltaPos;//rot* deltaPos;
	float height;
	view->GetWorldPicker()->GetHeight( cameraPos.x, cameraPos.y, height );
	if (cameraPos.z < height)
	{
		cameraPos.z = height + 5.f;
	}
	camera->SetPos( cameraPos );
	theApp.GetWorld()->SetActivePos( cameraPos.x, cameraPos.y );
	
	GetFlagModel()->pObject->model->SetPosition(cameraPos.x, cameraPos.y, height);
	GetFlagModel()->Update(0.f);
//	camera->GetNiCamera()->LookAtWorldPoint(cameraPos, Vector::UNIT_Z);
	camera->Update(0.f,0.f);

	CStatic::OnLButtonUp(nFlags, point);
}

void CTextureNavigationWnd::OnPaint()
{
	CPaintDC dcPaint(this); // device context for painting

	CRect rc;
	GetWindowRect(rc);
	Draw( &dcPaint, CRect(0, 0, rc.right-rc.left, rc.bottom-rc.top) );
}

void CTextureNavigationWnd::Draw( CPaintDC *pDC, CRect& rect )
{
	CRect workRc;
	workRc.left		= workRc.top	= 0;
	workRc.right	=  l_width ;
	workRc.bottom	= l_height;
	if( !DrawBgnd( pDC, workRc ) )
		return;

	DrawGrid( pDC);

	DrawCamera( pDC, workRc );

	//rect.InflateRect(3, 3);
	//pDC->Draw3dRect(rect, RGB(0xFF, 0xFF, 0xFF), 0xFFFF0000);
}

bool CTextureNavigationWnd::DrawGrid( CPaintDC* pDC )
{	
	if( m_isShowGrid ) {
		CRect winRect(m_showArea.left,l_height - m_showArea.top,m_showArea.right,l_width - m_showArea.bottom);
		CPen newPen;  // Construct it, then initialize
		if( newPen.CreatePen( PS_SOLID, 1, RGB(0,128,0) ) )
		{
			CPen* pOldPen = pDC->SelectObject( &newPen );


//			sInt32 step = ZnFloat2Int( (winRect.right - winRect.left) / m_curTile->GetRowColumn()[0] );
			sInt32 step = ZnFloat2Int( WORLD_TILE_CHUNK_VERT_NUM/m_sizeScale);
			flt32 startX = winRect.left;
			flt32 startY =  winRect.top;
			sInt32 chunkX = ChunkFromPos(m_tileArea.left);
			if (startX == 0 )
			{
				startX = ZnFloat2Int(((chunkX+1)*WORLD_CHUNKSIZE - m_tileArea.left)/(WORLD_VERTSIZE*m_sizeScale));
			}
			flt32 localTop = m_curTile->GetRowColumn()[1]*WORLD_CHUNKSIZE - m_tileArea.top;
			sInt32 chunkY = ChunkFromPos(localTop);
			if (startY == 0)
			{
				startY = ZnFloat2Int(((chunkY+1)*WORLD_CHUNKSIZE - localTop)/(WORLD_VERTSIZE*m_sizeScale));
			}
			sInt32 pt;
			for( sInt32 i=chunkX; i < m_curTile->GetRowColumn()[0] ; i++ ) 
			{

				pt = startX + (i - chunkX)* step;
				if (pt > l_width)
				{
					break;
				}
				pDC->MoveTo( pt, winRect.top );
				pDC->LineTo( pt, winRect.bottom );
			}
//			step = ZnFloat2Int( (winRect.bottom - winRect.top) / m_curTile->GetRowColumn()[1] );
			for( sInt32 i=chunkY; i<m_curTile->GetRowColumn()[1]; i++ ) 
			{
				pt = startY + (i- chunkY) * step;
				if (pt > l_height)
				{
					break;
				}
				pDC->MoveTo( winRect.left, pt );
				pDC->LineTo( winRect.right, pt );
			}
			pDC->SelectObject( pOldPen );
		} 
	}

	return true;
}

bool CTextureNavigationWnd::DrawBgnd( CPaintDC* pDC, CRect& rect )
{
	if( !m_hasTexture ) {
		pDC->FillSolidRect( rect, RGB(0xEC, 0xE9, 0xD8));
		return false;
	}
	if( !m_image.IsValid() ) 
		return false;

	m_image.Stretch( *pDC, rect.left, rect.top, (rect.right-rect.left), (rect.bottom-rect.top) );

	return true;
}

bool CTextureNavigationWnd::DrawCamera( CPaintDC* pDC, CRect& rect )
{

	CPen newPen;  // Construct it, then initialize
	if( newPen.CreatePen( PS_SOLID, 1, RGB(255,255,0) ) )
	{
		CPen* pOldPen = pDC->SelectObject( &newPen );

		sInt32 x, y, w, h, dx, dy;
		CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		SwCamera* camera		= view->GetActiveCamera();
		Vector cameraPos = camera->GetPos();
		Vector activePos;
		theApp.GetWorld()->GetActivePos(activePos.x,activePos.y);
		float deltaX = cameraPos.x - activePos.x;
		float deltaY = cameraPos.y - activePos.y;
		flt32 fpixelRealSize = WORLD_VERTSIZE*m_sizeScale;//当m_showAreaScale==1的时候每一个像素代表一个WORLD_VERTSIZE

		w = rect.right - rect.left;
		h = rect.bottom - rect.top;
		x = rect.left + w/2 + ZnFloor2Int(deltaX/fpixelRealSize);
		y = rect.bottom - h/2 - ZnFloor2Int(deltaY/fpixelRealSize);

		dx = x + ZnFloat2Int( m_cameraDir.x * w * 0.1f );
		dy = y - ZnFloat2Int( m_cameraDir.y * h * 0.1f );

		//if( x < rect.left )		x = rect.left;
		//if( x > rect.right )	x = rect.right;
		//if( y < rect.top )		y = rect.top;
		//if( y > rect.bottom )	y = rect.bottom;
		const sInt32 r = 2;
		pDC->MoveTo( x-r, y-r );
		pDC->LineTo( x+r, y-r );
		pDC->LineTo( x+r, y+r );
		pDC->LineTo( x-r, y+r );
		pDC->LineTo( x-r, y-r );

		//if( dx < rect.left )	dx = rect.left;
		//if( dx > rect.right )	dx = rect.right;
		//if( dy < rect.top )		dy = rect.top;
		//if( dy > rect.bottom )	dy = rect.bottom;
		pDC->MoveTo( x, y );
		pDC->LineTo( dx, dy );

		pDC->SelectObject( pOldPen );
	}

	return true;
}

void CTextureNavigationWnd::ShowReachable( bool isShowGrid /*= true */ )
{
	m_isShowReachable = isShowGrid;
}


HelperObject* CTextureNavigationWnd::GetFlagModel()
{
	if (m_flagModel == NULL)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		m_flagModel = helper->GetHelper(HT_Flag);
	}
	return m_flagModel;
}
