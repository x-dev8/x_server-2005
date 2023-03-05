#include "stdAfx.h"
#include "ToolFreeBlock.h"
#include "Ndl/NdlWorldEditor.h"

#define FREEBLOCK_PRE_PATH "data/sceneobject/common/blocks/"

ToolFreeBlock::ToolFreeBlock()
{
	SetCurrentOperationStatus( ToolFreeBlock::EOS_NONE );
	m_kLastPt = Vector( -1, -1, -1 );
	m_kCurrentPt = m_kLastPt;
	m_bEnable = false;
	m_fMaxBlockLength = 0;
}

ToolFreeBlock::~ToolFreeBlock()
{

}

bool ToolFreeBlock::Create( CToolManager* toolMgr )
{
	// Load blocks info and initialize them.
	LoadBlocksFromDisk();	
	for (BlocksIter iter = mBlocks.begin(); iter != mBlocks.end(); ++iter)
	{
		iter->second.m_fLength = GetBlockLengthByName(iter->second.m_strFilename );
		m_fMaxBlockLength = max(m_fMaxBlockLength, iter->second.m_fLength);
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////
bool ToolFreeBlock::OnLMouseUp( UINT nFlags, CPoint point )
{
	if( !EnableFreeBlock() )
		return false;

	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

	// Get the point in terrain world space.
	sInt32 pickId = view->PickWorldTerrain( point );
	if( -1 == pickId )
		return false;
	
	const TPickResult& pickResult = view->GetPickResult();		
	Vector kPt = pickResult.pickResultInfo[pickId].point;

	// Store point.
	m_kLastPt = m_kCurrentPt;
	m_kCurrentPt = kPt;

	// According to the current status to do specified operation.
	// Did nothing before.
	if( GetCurrentOperationStatus() == ToolFreeBlock::EOS_NONE )
	{
		SetCurrentOperationStatus( ToolFreeBlock::EOS_READYBLOCK );		
	}
	// Already assigned a point.
	else if( GetCurrentOperationStatus() == ToolFreeBlock::EOS_READYBLOCK )
	{
		// Calculate distance.
		Vector kDelta = m_kCurrentPt - m_kLastPt;
		float fLength = kDelta.length();

		// Put a block on terrain with the distance.
		PutBlock( fLength );
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////
bool ToolFreeBlock::OnLMouseDown( UINT nFlags, CPoint point )
{
	return false;
}
//////////////////////////////////////////////////////////////////////////
bool ToolFreeBlock::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return false;
}
//////////////////////////////////////////////////////////////////////////
bool ToolFreeBlock::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point;
	return false;
}
//////////////////////////////////////////////////////////////////////////
bool ToolFreeBlock::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;
	return false;
}
//////////////////////////////////////////////////////////////////////////
bool ToolFreeBlock::OnMouseMove( UINT nFlags, CPoint point )
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
	camera->Update( 0.0f, 0.0f );

	return true;
}
//////////////////////////////////////////////////////////////////////////
bool ToolFreeBlock::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if( !EnableFreeBlock() )
		return false;

	// Clear last point when press Ctrl.
	if( !( nChar == VK_CONTROL ) )
		return false;

	SetCurrentOperationStatus( ToolFreeBlock::EOS_NONE );

	return true;
}
//////////////////////////////////////////////////////////////////////////
bool ToolFreeBlock::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	return false;
}
//////////////////////////////////////////////////////////////////////////
void ToolFreeBlock::Render()
{
	if( !EnableFreeBlock() )
		return;

	// desc: implementation of render block list
	// name-time: wangshuai [2012.3.26]
	IRenderer *render = GetEngine()->GetRenderer();

	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	render->SetTransform(D3DTS_WORLD, (float *) &world);
	
	// 取得当前地图上的物件表, 与阻挡表里对比并渲染成红色
	// todo: 由于牵扯到引擎的渲染, 经商量决定先不实现, 让美术把阻挡贴上一张红色单色纹理, 发布时再替换掉就可以了
}
//////////////////////////////////////////////////////////////////////////
void ToolFreeBlock::LoadBlocksFromDisk()
{
	// Find files with a name which has a postfix of .mex .
	char acPath[MAX_PATH] = {0};
	sprintf_s( acPath, MAX_PATH, "%s/%s/*.mex", GetRootPath(), FREEBLOCK_PRE_PATH );
	
	_finddata32_t kdata;
	intptr_t hfile = _findfirst32( acPath, &kdata );
	if( hfile == -1 )
		return;

	do
	{
		FreeBlock kBlock;
		kBlock.m_strFilename = strlwr( kdata.name );
		kBlock.m_strFilename = std::string( FREEBLOCK_PRE_PATH ) + kBlock.m_strFilename;
		mBlocks.insert(std::make_pair(kBlock.m_strFilename, kBlock));
	}while( _findnext32( hfile, &kdata ) == 0 );	
	// Close it.
	_findclose( hfile );
}
//////////////////////////////////////////////////////////////////////////
void ToolFreeBlock::PutBlock( float fLength )
{
	Vector kActualLast = m_kLastPt;
	do
	{
		float fActualLength = fLength;
		if( fLength > GetMaxBlockLength() )		
			fActualLength = GetMaxBlockLength();

		fLength = fLength - fActualLength;

		BlocksIter iter = FindBlockIndexByLength( fActualLength );
		if (iter == mBlocks.end())
			return;

		// Find the best block.
		FreeBlock kBlock = iter->second;

		// Now, we calculate the position, rotation, scale.
		// Assume that the two vector are in the same plane.
		Vector kDir = Vector( m_kCurrentPt.x, m_kCurrentPt.y, 0 ) - 
			Vector( m_kLastPt.x, m_kLastPt.y, 0 );
		kDir.normalize();

		// 1. Position.
		flt32 fPos3[3] = { 0.f };
		{
			Vector kCenter = ( kActualLast + ( kActualLast + fActualLength * kDir ) ) / 2.f;
			kActualLast = kActualLast + fActualLength * kDir;
			// We use the lowest height.
			kCenter.z = min( m_kCurrentPt.z, m_kLastPt.z );
			fPos3[0] = kCenter.x;
			fPos3[1] = kCenter.y;
			fPos3[2] = kCenter.z;
		}

		// 2.Rotation.
		flt32 fRotation3[3] = { 0.f };
		{
			// Only rotate with Z axis.
			Vector kAxisX( 1, 0, 0 );

			// Dot product.
			float fDot = kDir.dot( kAxisX );

			// Get radian value.
			float fRadian = acos( fDot );

			// Calculate sign.
			float fSignedRadian = kDir.y / fabs( kDir.y ) * fRadian;

			// Radian to Degree.
			fRotation3[2] = fSignedRadian * 180.f / PI;
		}

		// 3.Scale.
		flt32 fScale3[3] = { 1.f, 1.f, 1.f };

		// Finally, put it on terrain.
		flt32 fOffset3[3] = { 0.f };
		theApp.GetWorldEditor()->PutStaticModel( fPos3, fOffset3, fRotation3, fScale3, kBlock.m_strFilename.c_str() );

	}while( fLength > 0 );
}
//////////////////////////////////////////////////////////////////////////
int ToolFreeBlock::GetBlockLengthByName( const std::string& strFilename ) const
{
	if( strFilename.empty() )
		return -1;

	// Get the file name index.( d:/directory/block_3.mex )
	std::string::size_type idx = strFilename.find_last_of( '/' );
	if( idx == std::string::npos )
	{
		idx = strFilename.find_last_of( '\\' );
		if( idx == std::string::npos )
			return -1;
	}

	// ( block_3.mex )
	std::string strName = strFilename.substr( idx + 1 );
	idx = strName.find_last_of( '.' );
	if( idx == std::string::npos )
		return -1;

	// ( block_3 )
	strName = strName.substr( 0, idx );
	idx = strName.find_last_of( '_' );
	if( idx == std::string::npos )
		return -1;

	// ( 3 )
	strName = strName.substr( idx + 1 );
	
	// Get the length.
	int nLen = -1;
	try
	{
		nLen = atoi( strName.c_str() );
	}
	catch( ... )
	{
		OutputDebugStringA( "Error Block Filename! " );
	}

	return nLen;
}

BlocksIter ToolFreeBlock::FindBlockIndexByLength( float fLength )
{
	int nMinimalDelta = MAX_INT;
	BlocksIter iter = mBlocks.begin();
	while (iter != mBlocks.end())
	{
		float fLen = iter->second.m_fLength - fLength;
		if( nMinimalDelta > fLen  && fLen >= 0 )
		{
			nMinimalDelta = fLen;
		}

		++iter;
	}
	return iter;
}