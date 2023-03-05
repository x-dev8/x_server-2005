//-----------------------------------------------------------------------------
// File: D3DUtil.cpp
//
// Desc: Shortcut macros and functions for using DX objects
//-----------------------------------------------------------------------------
#define STRICT
//#include "stdafx.h"
#include "Me3d/Me3d.h"
#include <tchar.h>
#include <stdio.h>
#include "Me3d/D3dUtil.h"
#include "Me3d/DxUtil.h"
#include "Dxsdk/d3dx9.h"
#include "Me3d/Model/MexGeoChunk.h"

//-----------------------------------------------------------------------------
// Name: D3DUtil_InitMaterial()
// Desc: Initializes a D3DMATERIAL9 structure, setting the diffuse and ambient
//       colors. It does not set emissive or specular colors.
//-----------------------------------------------------------------------------
VOID D3DUtil_InitMaterial( D3DMATERIAL9& mtrl, FLOAT r, FLOAT g, FLOAT b,
                           FLOAT a )
{
    ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
    mtrl.Diffuse.r = mtrl.Ambient.r = r;
    mtrl.Diffuse.g = mtrl.Ambient.g = g;
    mtrl.Diffuse.b = mtrl.Ambient.b = b;
    mtrl.Diffuse.a = mtrl.Ambient.a = a;
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_InitLight()
// Desc: Initializes a D3DLIGHT structure, setting the light position. The
//       diffuse color is set to white; specular and ambient are left as black.
//-----------------------------------------------------------------------------
VOID D3DUtil_InitLight( D3DLIGHT9& light, D3DLIGHTTYPE ltType,
                        FLOAT x, FLOAT y, FLOAT z )
{
    ZeroMemory( &light, sizeof(D3DLIGHT9) );
    light.Type        = ltType;
    light.Diffuse.r   = 1.0f;
    light.Diffuse.g   = 1.0f;
    light.Diffuse.b   = 1.0f;
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &D3DXVECTOR3(x, y, z) );
    light.Position.x   = x;
    light.Position.y   = y;
    light.Position.z   = z;
    light.Range        = 1000.0f;
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_CreateTexture()
// Desc: Helper function to create a texture. It checks the root path first,
//       then tries the DXSDK media path (as specified in the system registry).
//-----------------------------------------------------------------------------
HRESULT D3DUtil_CreateTexture( LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* strTexture,
                               LPDIRECT3DTEXTURE9* ppTexture, D3DFORMAT d3dFormat )
{
    // Get the path to the texture
    TCHAR strPath[MAX_PATH];
    DXUtil_FindMediaFile( strPath, strTexture );

    // Create the texture using D3DX
    return D3DXCreateTextureFromFileEx( pd3dDevice, strPath, 
                D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, d3dFormat, 
                D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
                D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 0, NULL, NULL, ppTexture );
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_SetColorKey()
// Desc: Changes all texels matching the colorkey to transparent, black.
//-----------------------------------------------------------------------------
HRESULT D3DUtil_SetColorKey( LPDIRECT3DTEXTURE9 pTexture, DWORD dwColorKey )
{
    // Get colorkey's red, green, and blue components
    DWORD r = ((dwColorKey&0x00ff0000)>>16);
    DWORD g = ((dwColorKey&0x0000ff00)>>8);
    DWORD b = ((dwColorKey&0x000000ff)>>0);

    // Put the colorkey in the texture's native format
    D3DSURFACE_DESC d3dsd;
    pTexture->GetLevelDesc( 0, &d3dsd );
    if( d3dsd.Format == D3DFMT_A4R4G4B4 )
        dwColorKey = 0xf000 + ((r>>4)<<8) + ((g>>4)<<4) + (b>>4);
    else if( d3dsd.Format == D3DFMT_A1R5G5B5 )
        dwColorKey = 0x8000 + ((r>>3)<<10) + ((g>>3)<<5) + (b>>3);
    else if( d3dsd.Format != D3DFMT_A8R8G8B8 )
        return E_FAIL;

    // Lock the texture
    D3DLOCKED_RECT  d3dlr;
    if( FAILED( pTexture->LockRect( 0, &d3dlr, 0, 0 ) ) )
        return E_FAIL;

    // Scan through each pixel, looking for the colorkey to replace
    for( DWORD y=0; y<d3dsd.Height; y++ )
    {
        for( DWORD x=0; x<d3dsd.Width; x++ )
        {
            if( d3dsd.Format==D3DFMT_A8R8G8B8 )
            {
                // Handle 32-bit formats
                if( ((DWORD*)d3dlr.pBits)[d3dsd.Width*y+x] == dwColorKey )
                    ((DWORD*)d3dlr.pBits)[d3dsd.Width*y+x] = 0x00000000;
            }
            else
            {
                // Handle 16-bit formats
                if( ((WORD*)d3dlr.pBits)[d3dsd.Width*y+x] == dwColorKey )
                    ((WORD*)d3dlr.pBits)[d3dsd.Width*y+x] = 0x0000;
            }
        }
    }

    // Unlock the texture and return OK.
    pTexture->UnlockRect(0);
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_CreateVertexShader()
// Desc: Assembles and creates a file-based vertex shader
//-----------------------------------------------------------------------------
HRESULT D3DUtil_CreateVertexShader( LPDIRECT3DDEVICE9 pd3dDevice, 
                                    TCHAR* strFilename, DWORD* pdwVertexDecl,
                                    DWORD* pdwVertexShader )
{
	return S_FALSE;
//    LPD3DXBUFFER pCode;
//    TCHAR        strPath[MAX_PATH];
//    HRESULT      hr;
//
//    // Get the path to the vertex shader file
//    DXUtil_FindMediaFile( strPath, strFilename );
//
//    // Assemble the vertex shader file
//    if( FAILED( hr = D3DXAssembleShaderFromFile( strPath, NULL, 0, NULL, &pCode, NULL ) ) )
//        return hr;
//
// STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD* pDeclaration,CONST DWORD* pFunction,DWORD* pHandle,DWORD Usage) PURE;
//virtual HRESULT STDMETHODCALLTYPE CreateVertexShader (THIS_ CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader) PURE
//    // Create the vertex shader
//    hr = pd3dDevice->CreateVertexShader( pdwVertexDecl, 
//                                         (DWORD*)pCode->GetBufferPointer(),
//                                         pdwVertexShader, 0 );
//    pCode->Release();
   // return hr;
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_GetCubeMapViewMatrix()
// Desc: Returns a view matrix for rendering to a face of a cubemap.
//-----------------------------------------------------------------------------
D3DXMATRIX D3DUtil_GetCubeMapViewMatrix( DWORD dwFace )
{
    D3DXVECTOR3 vEyePt   = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vLookDir;
    D3DXVECTOR3 vUpDir;

    switch( dwFace )
    {
        case D3DCUBEMAP_FACE_POSITIVE_X:
            vLookDir = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
            vUpDir   = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
            break;
        case D3DCUBEMAP_FACE_NEGATIVE_X:
            vLookDir = D3DXVECTOR3(-1.0f, 0.0f, 0.0f );
            vUpDir   = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
            break;
        case D3DCUBEMAP_FACE_POSITIVE_Y:
            vLookDir = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
            vUpDir   = D3DXVECTOR3( 0.0f, 0.0f,-1.0f );
            break;
        case D3DCUBEMAP_FACE_NEGATIVE_Y:
            vLookDir = D3DXVECTOR3( 0.0f,-1.0f, 0.0f );
            vUpDir   = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
            break;
        case D3DCUBEMAP_FACE_POSITIVE_Z:
            vLookDir = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
            vUpDir   = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
            break;
        case D3DCUBEMAP_FACE_NEGATIVE_Z:
            vLookDir = D3DXVECTOR3( 0.0f, 0.0f,-1.0f );
            vUpDir   = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
            break;
    }

    // Set the view transform for this cubemap surface
    D3DXMATRIX matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookDir, &vUpDir );
    return matView;
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_GetRotationFromCursor()
// Desc: Returns a quaternion for the rotation implied by the window's cursor
//       position.
//-----------------------------------------------------------------------------
D3DXQUATERNION D3DUtil_GetRotationFromCursor( HWND hWnd,
                                              FLOAT fTrackBallRadius )
{
    POINT pt;
    RECT  rc;
    GetCursorPos( &pt );
    GetClientRect( hWnd, &rc );
    ScreenToClient( hWnd, &pt );
    FLOAT sx = ( ( ( 2.0f * pt.x ) / (rc.right-rc.left) ) - 1 );
    FLOAT sy = ( ( ( 2.0f * pt.y ) / (rc.bottom-rc.top) ) - 1 );
    FLOAT sz;

    if( sx == 0.0f && sy == 0.0f )
        return D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 1.0f );

    FLOAT d1 = 0.0f;
    FLOAT d2 = sqrtf( sx*sx + sy*sy );

    if( d2 < fTrackBallRadius * 0.70710678118654752440 ) // Inside sphere
        sz = sqrtf( fTrackBallRadius*fTrackBallRadius - d2*d2 );
    else                                                 // On hyperbola
        sz = (fTrackBallRadius*fTrackBallRadius) / (2.0f*d2);

    // Get two points on trackball's sphere
    D3DXVECTOR3 p1( sx, sy, sz );
    D3DXVECTOR3 p2( 0.0f, 0.0f, fTrackBallRadius );

    // Get axis of rotation, which is cross product of p1 and p2
    D3DXVECTOR3 vAxis;
    D3DXVec3Cross( &vAxis, &p1, &p2);

    // Calculate angle for the rotation about that axis
    FLOAT t = D3DXVec3Length( &(p2-p1) ) / ( 2.0f*fTrackBallRadius );
    if( t > +1.0f) t = +1.0f;
    if( t < -1.0f) t = -1.0f;
    FLOAT fAngle = 2.0f * asinf( t );

    // Convert axis to quaternion
    D3DXQUATERNION quat;
    D3DXQuaternionRotationAxis( &quat, &vAxis, fAngle );
    return quat;
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_SetDeviceCursor
// Desc: Gives the D3D device a cursor with image and hotspot from hCursor.
//-----------------------------------------------------------------------------
HRESULT D3DUtil_SetDeviceCursor( LPDIRECT3DDEVICE9 pd3dDevice, HCURSOR hCursor,
                                 BOOL bAddWatermark )
{
    HRESULT hr = E_FAIL;
//    ICONINFO iconinfo;
//    BOOL bBWCursor;
//    LPDIRECT3DSURFACE9 pCursorBitmap = NULL;
//    HDC hdcColor = NULL;
//    HDC hdcMask = NULL;
//    HDC hdcScreen = NULL;
//    BITMAP bm;
//    DWORD dwWidth;
//    DWORD dwHeightSrc;
//    DWORD dwHeightDest;
//    COLORREF crColor;
//    COLORREF crMask;
//    UINT x;
//    UINT y;
//    BITMAPINFO bmi;
//    COLORREF* pcrArrayColor = NULL;
//    COLORREF* pcrArrayMask = NULL;
//    DWORD* pBitmap;
//    HGDIOBJ hgdiobjOld;
//
//    ZeroMemory( &iconinfo, sizeof(iconinfo) );
//    if( !GetIconInfo( hCursor, &iconinfo ) )
//        goto End;
//
//    if (0 == GetObject((HGDIOBJ)iconinfo.hbmMask, sizeof(BITMAP), (LPVOID)&bm))
//        goto End;
//    dwWidth = bm.bmWidth;
//    dwHeightSrc = bm.bmHeight;
//
//    if( iconinfo.hbmColor == NULL )
//    {
//        bBWCursor = TRUE;
//        dwHeightDest = dwHeightSrc / 2;
//    }
//    else 
//    {
//        bBWCursor = FALSE;
//        dwHeightDest = dwHeightSrc;
//    }
//
//    // Create a surface for the fullscreen cursor
//    if( FAILED( hr = pd3dDevice->CreateImageSurface( dwWidth, dwHeightDest, 
//        D3DFMT_A8R8G8B8, &pCursorBitmap ) ) )
//    {
//        goto End;
//    }
//
//    pcrArrayMask = MeNew DWORD[dwWidth * dwHeightSrc];
//
//    ZeroMemory(&bmi, sizeof(bmi));
//    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
//    bmi.bmiHeader.biWidth = dwWidth;
//    bmi.bmiHeader.biHeight = dwHeightSrc;
//    bmi.bmiHeader.biPlanes = 1;
//    bmi.bmiHeader.biBitCount = 32;
//    bmi.bmiHeader.biCompression = BI_RGB;
//
//    hdcScreen = GetDC( NULL );
//    hdcMask = CreateCompatibleDC( hdcScreen );
//    if( hdcMask == NULL )
//    {
//        hr = E_FAIL;
//        goto End;
//    }
//    hgdiobjOld = SelectObject(hdcMask, iconinfo.hbmMask);
//    GetDIBits(hdcMask, iconinfo.hbmMask, 0, dwHeightSrc, 
//        pcrArrayMask, &bmi, DIB_RGB_COLORS);
//    SelectObject(hdcMask, hgdiobjOld);
//
//    if (!bBWCursor)
//    {
//        pcrArrayColor = MeNew DWORD[dwWidth * dwHeightDest];
//        hdcColor = CreateCompatibleDC( GetDC( NULL ) );
//        if( hdcColor == NULL )
//        {
//            hr = E_FAIL;
//            goto End;
//        }
//        SelectObject(hdcColor, iconinfo.hbmColor);
//        GetDIBits(hdcColor, iconinfo.hbmColor, 0, dwHeightDest, 
//            pcrArrayColor, &bmi, DIB_RGB_COLORS);
//    }
//
//    // Transfer cursor image into the surface
//    D3DLOCKED_RECT lr;
//    pCursorBitmap->LockRect( &lr, NULL, 0 );
//    pBitmap = (DWORD*)lr.pBits;
//    for( y = 0; y < dwHeightDest; y++ )
//    {
//        for( x = 0; x < dwWidth; x++ )
//        {
//            if (bBWCursor)
//            {
//                crColor = pcrArrayMask[dwWidth*(dwHeightDest-1-y) + x];
//                crMask = pcrArrayMask[dwWidth*(dwHeightSrc-1-y) + x];
//            }
//            else
//            {
//                crColor = pcrArrayColor[dwWidth*(dwHeightDest-1-y) + x];
//                crMask = pcrArrayMask[dwWidth*(dwHeightDest-1-y) + x];
//            }
//            if (crMask == 0)
//                pBitmap[dwWidth*y + x] = 0xff000000 | crColor;
//            else
//                pBitmap[dwWidth*y + x] = 0x00000000;
//
//            // It may be helpful to make the D3D cursor look slightly 
//            // different from the Windows cursor so you can distinguish 
//            // between the two when developing/testing code.  When
//            // bAddWatermark is TRUE, the following code adds some
//            // small grey "D3D" characters to the upper-left corner of
//            // the D3D cursor image.
//            if( bAddWatermark && x < 12 && y < 5 )
//            {
//                // 11.. 11.. 11.. .... CCC0
//                // 1.1. ..1. 1.1. .... A2A0
//                // 1.1. .1.. 1.1. .... A4A0
//                // 1.1. ..1. 1.1. .... A2A0
//                // 11.. 11.. 11.. .... CCC0
//
//                const WORD wMask[5] = { 0xccc0, 0xa2a0, 0xa4a0, 0xa2a0, 0xccc0 };
//                if( wMask[y] & (1 << (15 - x)) )
//                {
//                    pBitmap[dwWidth*y + x] |= 0xff808080;
//                }
//            }
//        }
//    }
//    pCursorBitmap->UnlockRect();
//
//    // Set the device cursor
//    if( FAILED( hr = pd3dDevice->SetCursorProperties( iconinfo.xHotspot, 
//        iconinfo.yHotspot, pCursorBitmap ) ) )
//    {
//        goto End;
//    }
//
//    hr = S_OK;
//
//End:
//    if( iconinfo.hbmMask != NULL )
//        DeleteObject( iconinfo.hbmMask );
//    if( iconinfo.hbmColor != NULL )
//        DeleteObject( iconinfo.hbmColor );
//    if( hdcScreen != NULL )
//        ReleaseDC( NULL, hdcScreen );
//    if( hdcColor != NULL )
//        DeleteDC( hdcColor );
//    if( hdcMask != NULL )
//        DeleteDC( hdcMask );
//    SAFE_DELETE_ARRAY( pcrArrayColor );
//    SAFE_DELETE_ARRAY( pcrArrayMask );
//    SAFE_RELEASE( pCursorBitmap );
    return hr;
}




//-----------------------------------------------------------------------------
// Name: D3DXQuaternionUnitAxisToUnitAxis2
// Desc: Axis to axis quaternion double angle (no normalization)
//       Takes two points on unit sphere an angle THETA apart, returns
//       quaternion that represents a rotation around cross product by 2*THETA.
//-----------------------------------------------------------------------------
inline D3DXQUATERNION* WINAPI D3DXQuaternionUnitAxisToUnitAxis2
( D3DXQUATERNION *pOut, const D3DXVECTOR3 *pvFrom, const D3DXVECTOR3 *pvTo)
{
    D3DXVECTOR3 vAxis;
    D3DXVec3Cross(&vAxis, pvFrom, pvTo);    // proportional to sin(theta)
    pOut->x = vAxis.x;
    pOut->y = vAxis.y;
    pOut->z = vAxis.z;
    pOut->w = D3DXVec3Dot( pvFrom, pvTo );
    return pOut;
}




//-----------------------------------------------------------------------------
// Name: D3DXQuaternionAxisToAxis
// Desc: Axis to axis quaternion 
//       Takes two points on unit sphere an angle THETA apart, returns
//       quaternion that represents a rotation around cross product by theta.
//-----------------------------------------------------------------------------
inline D3DXQUATERNION* WINAPI D3DXQuaternionAxisToAxis
( D3DXQUATERNION *pOut, const D3DXVECTOR3 *pvFrom, const D3DXVECTOR3 *pvTo)
{
    D3DXVECTOR3 vA, vB;
    D3DXVec3Normalize(&vA, pvFrom);
    D3DXVec3Normalize(&vB, pvTo);
    D3DXVECTOR3 vHalf(vA + vB);
    D3DXVec3Normalize(&vHalf, &vHalf);
    return D3DXQuaternionUnitAxisToUnitAxis2(pOut, &vA, &vHalf);
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_ConvertMeshToD3DXMesh
// Desc: Creates a D3DXMESH from a CMexChunkBase
//		 @param SourceMesh Mesh to extract from
//		 @param D3DMesh Mesh to create
//		 @return Boolean representing success or failure
//-----------------------------------------------------------------------------
struct SUtilVertex
{
	Vector	Position;
	Vector	Normal;
	Vector2	UVs[4];	// 只支持Max导出3层UV，最后一层保存LightMap UV
	DWORD	Color;
};

BOOL D3DUtil_ConvertMeshToD3DXMesh( CMexChunkBase& SourceMesh, LPD3DXMESH& D3DMesh )
{
	D3DVERTEXELEMENT9 VertexElements[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_POSITION, 0},
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_NORMAL,   0},
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_TEXCOORD, 0},
		{ 0, 32, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_TEXCOORD, 1},
		{ 0, 40, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_TEXCOORD, 2},
		{ 0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_TEXCOORD, 3},
		{ 0, 56, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};

	int NumFaces = SourceMesh.GetFaceCount();
	int NumVertices = SourceMesh.GetVertexCount();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	// Create mesh for source data
	if (FAILED(D3DXCreateMesh(NumFaces,NumVertices,D3DXMESH_SYSTEMMEM,VertexElements,pd3dDevice,&D3DMesh) ) )
	{
		OutputDebugString("D3DXCreateMesh() Failed!\n");
		return FALSE;
	}

	SUtilVertex* D3DVertices;
	WORD*		 D3DIndices;
	D3DMesh->LockVertexBuffer(0,(LPVOID*)&D3DVertices);
	D3DMesh->LockIndexBuffer(0,(LPVOID*)&D3DIndices);

	int NumVerts = 0;
	int NumUVs = SourceMesh.GetUVLayerCount();
	if( NumUVs > 3 )
		NumUVs = 3;
	const Mex2Face* pFaces = SourceMesh.GetFaces();
	const Vector* pVertices = SourceMesh.GetVertices();
	const Vector* pNormals = SourceMesh.GetNormals();
	const DWORD* pDiffuse = SourceMesh.GetDiffuses();
	if( !pFaces || !pVertices || !pNormals )
		return FALSE;
	Vector2* pUVs[3];
	pUVs[0] = SourceMesh.GetUVs(0);
	pUVs[1] = SourceMesh.GetUVs(1);
	pUVs[2] = SourceMesh.GetUVs(2);

	for(INT I=0;I<SourceMesh.GetFaceCount();++I)
	{
		const Mex2Face& Face = pFaces[I];
		D3DIndices[I*3 + 0] = Face.nId[0];
		D3DIndices[I*3 + 1] = Face.nId[1];
		D3DIndices[I*3 + 2] = Face.nId[2];
	}
	for(INT I=0;I<SourceMesh.GetVertexCount();++I)
	{
		D3DVertices[I].Position = pVertices[I];
		D3DVertices[I].Normal = pNormals[I];
		if( SourceMesh.IsExistDiffuse() )
			D3DVertices[I].Color = pDiffuse[I];
		for(INT UVIndex = 0; UVIndex < NumUVs; UVIndex++)
		{
			D3DVertices[I].UVs[UVIndex] = pUVs[UVIndex][I];
		}
	}

	D3DMesh->UnlockIndexBuffer();
	D3DMesh->UnlockVertexBuffer();
	D3DMesh->UnlockAttributeBuffer();

	return TRUE;
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_ConvertD3DXMeshToUMesh
// Desc: Creates a CMexChunkBase from a D3DXMesh
// @param DestMesh Destination mesh to extract to
// @param NumUVs Number of UVs
// @return Boolean representing success or failure
//-----------------------------------------------------------------------------
BOOL D3DUtil_ConvertD3DXMeshToMesh( LPD3DXMESH& D3DMesh, CMexChunkBase& DestMesh, INT NumUVs )
{
	// Extract simplified data to CMexChunkBase
	SUtilVertex* D3DVertices;
	WORD*		 D3DIndices;
	D3DMesh->LockVertexBuffer(D3DLOCK_READONLY,(LPVOID*)&D3DVertices);
	D3DMesh->LockIndexBuffer(D3DLOCK_READONLY,(LPVOID*)&D3DIndices);

	int numVert = D3DMesh->GetNumVertices();
	// UV展开后可能增加顶点
	if( numVert > DestMesh.GetVertexCount() )	
	{
		// 重新分配
		if( DestMesh.GetVertices() )
			delete[] DestMesh.GetVertices();
		if( DestMesh.GetNormals() )
			delete[] DestMesh.GetNormals();
		if( DestMesh.IsExistDiffuse() )
			delete[] DestMesh.GetDiffuses();
		for (int i=0; i <DestMesh.GetUVLayerCount(); ++i)
		{
			if( DestMesh.GetUVs(i) )
				delete[] DestMesh.GetUVs(i);
		}

		DestMesh.SetVertexCount(numVert);

		Vector* pData = MeNew Vector[numVert];
		DestMesh.SetVertices((float*)pData);

		pData = MeNew Vector[numVert];
		DestMesh.SetNormals((float*)pData);

		if( DestMesh.IsExistDiffuse() )
		{
			DWORD* pDiffuse = new DWORD[numVert];
			DestMesh.SetDiffuse(pDiffuse);
		}

		for( int i=0; i<DestMesh.GetUVLayerCount(); ++i )
		{
			Vector2* pNewUVs = MeNew Vector2[numVert];
			DestMesh.SetUVs(i, (float*)pNewUVs);
		}
	}

	if( NumUVs > DestMesh.GetUVLayerCount() )
	{
		Vector2* pUVs = MeNew Vector2[DestMesh.GetVertexCount()];
		DestMesh.SetUVLayerCount(NumUVs);
		DestMesh.SetUVs(NumUVs-1, (float*)pUVs);
	}
	Mex2Face* pFaces = DestMesh.GetFaces();
	Vector* pVertices = DestMesh.GetVertices();
	Vector* pNormals = DestMesh.GetNormals();
	DWORD* pDiffuse = DestMesh.GetDiffuses();
	Vector2* pUVs[4];
	pUVs[0] = DestMesh.GetUVs(0);
	pUVs[1] = DestMesh.GetUVs(1);
	pUVs[2] = DestMesh.GetUVs(2);
	pUVs[3] = DestMesh.GetUVs(3);

	int numFace = D3DMesh->GetNumFaces();
	for(int I=0; I<numFace; ++I)
	{
		Mex2Face& Face = pFaces[I];
		Face.nId[0] = D3DIndices[I*3 + 0];
		Face.nId[1] = D3DIndices[I*3 + 1];
		Face.nId[2] = D3DIndices[I*3 + 2];
	}

	for(int I=0;I<numVert;++I)
	{
		for(int UVIndex=0; UVIndex<NumUVs; ++UVIndex)
		{
			pUVs[UVIndex][I] = D3DVertices[I].UVs[UVIndex];
		}

		pVertices[I]  = D3DVertices[I].Position;
		pNormals[I]   = D3DVertices[I].Normal;
		pNormals[I].normalize();
		if( DestMesh.IsExistDiffuse() && pDiffuse && D3DVertices[I].Color )
			pDiffuse[I]   = D3DVertices[I].Color;
	}

	DestMesh.SetVertexCount(numVert);
	DestMesh.SetFaceCount(numFace);

	D3DMesh->UnlockIndexBuffer();
	D3DMesh->UnlockVertexBuffer();

	SAFE_RELEASE(D3DMesh)

	return TRUE;
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_GenerateUVs
// Desc: Generates a unique UV layout for a static mesh
//		 @param StaticMesh - The input/output mesh
//		 @param TexCoordIndex - Index of the uv channel to overwrite or create
//		 @param MaxDesiredStretch - The amount of stretching allowed. 0 means no stretching is allowed, 1 means any amount of stretching can be used. 
//		 @param ChartsGenerated - Number of charts generated by the uv unwrap algorithm.
//		 @return TRUE if successful
//-----------------------------------------------------------------------------
BOOL D3DUtil_GenerateUVs( CMexChunkBase& Mesh, UINT TexCoordIndex, FLOAT &MaxDesiredStretch, UINT &ChartsGenerated )
{
	LPD3DXMESH SourceMesh;
	//convert from StaticMesh to ID3DXMesh
	if (!D3DUtil_ConvertMeshToD3DXMesh(Mesh,SourceMesh))
	{
		OutputDebugString("D3DUtil_GenerateUVs failed, couldn't convert to a D3DXMesh.\n");
		return FALSE;
	}

	DWORD * Adjacency = new DWORD[SourceMesh->GetNumFaces() * 3];
	//generate adjacency info for the mesh, which is needed later
	if (FAILED(SourceMesh->GenerateAdjacency(1e-6f,Adjacency)))
	{
		OutputDebugString("D3DUtil_GenerateUVs failed, couldn't generate adjacency info.\n");
		SAFE_DELETE_ARRAY(Adjacency);
		return FALSE;
	}

	LPD3DXBUFFER pErrorsAndWarnings = NULL;
	HRESULT hr = S_OK;
	hr = D3DXValidMesh( SourceMesh, Adjacency, &pErrorsAndWarnings );
	if( NULL != pErrorsAndWarnings )
	{
		char* s = ( char* )pErrorsAndWarnings->GetBufferPointer();
	}


	LPD3DXMESH TempMesh;
	//clean the mesh
	DWORD* CleanedAdjacency = new DWORD[SourceMesh->GetNumFaces() * 3];
	if( FAILED(D3DXCleanMesh( D3DXCLEAN_SIMPLIFICATION, SourceMesh, Adjacency, &TempMesh, 
		CleanedAdjacency, &pErrorsAndWarnings ) ) )
	{
		OutputDebugString("D3DUtil_GenerateUVs failed, couldn't clean mesh.\n");
		SAFE_DELETE_ARRAY(Adjacency);
		SAFE_DELETE_ARRAY(CleanedAdjacency);
		SAFE_RELEASE(SourceMesh);
		SAFE_RELEASE( pErrorsAndWarnings );
		return FALSE;
	}
	SAFE_RELEASE( pErrorsAndWarnings );

	SAFE_RELEASE(SourceMesh);
	SourceMesh = TempMesh;

	// Input parameters
	//float	Maxcharts = 0.f;
	float	Gutter = 4.0f;
	LPD3DXBUFFER pFacePartitioning = NULL, pVertexRemapArray = NULL;

	// 测试用
	//{
	//	hr = D3DXSaveMeshToX( "c:\\mesha.x",
	//		SourceMesh,
	//		CleanedAdjacency,
	//		NULL,
	//		NULL,
	//		0,
	//		D3DXF_FILEFORMAT_TEXT );
	//}

	if( TexCoordIndex > 4 )
		TexCoordIndex = 4;
	//generate unique uv's
	//size params are only used to determine units of Gutter parameter
	hr = D3DXUVAtlasCreate(SourceMesh, ChartsGenerated, MaxDesiredStretch, 256.f, 256.f, Gutter, 
		TexCoordIndex, CleanedAdjacency, NULL, NULL, NULL, 0.0f, NULL, D3DXUVATLAS_GEODESIC_QUALITY/*D3DXUVATLAS_DEFAULT*/, &TempMesh, &pFacePartitioning,
		&pVertexRemapArray, &MaxDesiredStretch, &ChartsGenerated);

	if (FAILED(hr))
	{
		// 根据返回的ChartsGenerated再尝试一次
		hr = D3DXUVAtlasCreate(SourceMesh, ChartsGenerated, MaxDesiredStretch, 512.f, 512.f, Gutter, 
			TexCoordIndex, CleanedAdjacency, NULL, NULL, NULL, 0.0f, NULL, D3DXUVATLAS_GEODESIC_QUALITY/*D3DXUVATLAS_DEFAULT*/, &TempMesh, &pFacePartitioning,
			&pVertexRemapArray, &MaxDesiredStretch, &ChartsGenerated);

		if (FAILED(hr))
		{
			char msg[256] = {0};
			sprintf_s(msg, sizeof(msg)-1, "D3DXUVAtlasCreate() returned %u with MaxDesiredStretch=%.2f, TexCoordIndex=%u.\n", hr, MaxDesiredStretch, TexCoordIndex);
			OutputDebugString(msg);
			OutputDebugString("D3DUtil_GenerateUVs failed, D3DXUVAtlasCreate failed.\n");
			SAFE_DELETE_ARRAY(Adjacency);
			SAFE_RELEASE(SourceMesh);
			SAFE_DELETE_ARRAY(CleanedAdjacency);
			return FALSE;
		}
	}

	// 测试用
	//{
	//	hr = D3DXSaveMeshToX( "c:\\meshb.x",
	//		SourceMesh,
	//		CleanedAdjacency,
	//		NULL,
	//		NULL,
	//		0,
	//		D3DXF_FILEFORMAT_TEXT );
	//}

	SAFE_RELEASE(SourceMesh);
	SourceMesh = TempMesh;

	SAFE_DELETE_ARRAY(Adjacency);

	SAFE_DELETE_ARRAY(CleanedAdjacency);

	INT NewNumTexCoords = Mesh.GetUVLayerCount();
	//if the selected index doesn't exist yet, create it
	if (TexCoordIndex == Mesh.GetUVLayerCount())
	{
		NewNumTexCoords++;
	}

	//convert back to Mesh
	if (!D3DUtil_ConvertD3DXMeshToMesh(SourceMesh, Mesh, NewNumTexCoords))
	{
		OutputDebugString("D3DUtil_GenerateUVs failed, couldn't convert the simplified D3DXMesh back to a Mesh.\n");
		SAFE_RELEASE(SourceMesh);
		return FALSE;
	}

	SAFE_RELEASE(SourceMesh);

	// Re-build the mesh
	Mesh.RebuildBuffer();

	return TRUE; 
}



//-----------------------------------------------------------------------------
// Generates a simplified LOD from a static mesh
// @param StaticMesh - The input/output mesh
// @param DesiredLOD - The LOD level to generate the simplified mesh for
// @param DesiredTriangles - The desired triangle count for the LOD. Resulting triangle count may not be desired triangle count.
// @return TRUE if successful
//-----------------------------------------------------------------------------
BOOL D3DUtil_GenerateLOD( CMexChunkBase& Mesh, INT DesiredLOD, INT DesiredTriangles )
{
	LPD3DXMESH SourceMesh;
	//convert from StaticMesh to ID3DXMesh
	if (!D3DUtil_ConvertMeshToD3DXMesh(Mesh,SourceMesh))
	{
		OutputDebugString("D3DUtil_GenerateLOD failed, couldn't convert to a D3DXMesh.\n");
		return FALSE;
	}

	DWORD * Adjacency = new DWORD[SourceMesh->GetNumFaces() * 3];
	//generate adjacency info for the mesh, which is needed later
	if (FAILED(SourceMesh->GenerateAdjacency(1e-6f,Adjacency)))
	{
		OutputDebugString("D3DUtil_GenerateLOD failed, couldn't generate adjacency info.\n");
		SAFE_DELETE_ARRAY(Adjacency);
		return FALSE;
	}

	//Clean the mesh, which allows it to be simplified more effectively.  
	LPD3DXMESH TempMesh;

	LPD3DXBUFFER pErrorsAndWarnings = NULL;
	HRESULT hr = S_OK;
	hr = D3DXValidMesh( SourceMesh, Adjacency, &pErrorsAndWarnings );
	if( NULL != pErrorsAndWarnings )
	{
		char* s = ( char* )pErrorsAndWarnings->GetBufferPointer();
	}

	//clean the mesh
	DWORD* NewAdjacency = new DWORD[SourceMesh->GetNumFaces() * 3];
	if( FAILED(D3DXCleanMesh( D3DXCLEAN_SIMPLIFICATION, SourceMesh, Adjacency, &TempMesh, 
		NewAdjacency, &pErrorsAndWarnings ) ) )
	{
		OutputDebugString("D3DUtil_GenerateLOD failed, couldn't clean mesh.\n");
		SAFE_DELETE_ARRAY(Adjacency);
		SAFE_DELETE_ARRAY(NewAdjacency);
		SAFE_RELEASE(SourceMesh);
		SAFE_RELEASE( pErrorsAndWarnings );
		return FALSE;
	}
	SAFE_RELEASE( pErrorsAndWarnings );

	SAFE_RELEASE(SourceMesh);
	SourceMesh = TempMesh;

	// 测试用
	{
		hr = D3DXSaveMeshToX( "c:\\mesha.x",
			SourceMesh,
			NewAdjacency,
			NULL,
			NULL,
			0,
			D3DXF_FILEFORMAT_TEXT );
	}

	// Perform a weld to try and remove excess vertices.
	// Weld the mesh using all epsilons of 1e-6
	if( FAILED(D3DXWeldVertices( SourceMesh, 0, NULL,
		NewAdjacency,NewAdjacency, NULL, NULL ) ) )
	{
		OutputDebugString(TEXT("D3DUtil_GenerateLOD failed, couldn't weld vertices."));
		SAFE_DELETE_ARRAY(Adjacency);
		SAFE_RELEASE(SourceMesh);
		SAFE_DELETE_ARRAY(NewAdjacency);
		return FALSE;
	}

	D3DXATTRIBUTEWEIGHTS d3daw;
	memset( &d3daw, 0, sizeof(D3DXATTRIBUTEWEIGHTS) );
	d3daw.Position = 1.0f;
	d3daw.Boundary = 1.f;//10000.0f;
	d3daw.Normal   = 1.0f;

	//Use the D3DX simplify functionality
	LPD3DXMESH NewMesh;

	if( FAILED(D3DXSimplifyMesh( SourceMesh, NewAdjacency, &d3daw, NULL, DesiredTriangles , D3DXMESHSIMP_FACE, &NewMesh )))
	{
		OutputDebugString(TEXT("D3DUtil_GenerateLOD failed, couldn't simplify mesh."));
		SAFE_DELETE_ARRAY(Adjacency);
		SAFE_RELEASE(SourceMesh);
		SAFE_DELETE_ARRAY(NewAdjacency);
		return FALSE;
	}

	UINT NewTriCount = NewMesh->GetNumFaces();

	SAFE_RELEASE(TempMesh);

	SourceMesh = NewMesh;

	SAFE_DELETE_ARRAY(NewAdjacency);
	SAFE_DELETE_ARRAY(Adjacency);

	// 测试用
	{
		hr = D3DXSaveMeshToX( "c:\\meshb.x",
			SourceMesh,
			NewAdjacency,
			NULL,
			NULL,
			0,
			D3DXF_FILEFORMAT_TEXT );
	}

	//convert back to Mesh
	if (!D3DUtil_ConvertD3DXMeshToMesh(SourceMesh, Mesh, Mesh.GetUVLayerCount()))
	{
		OutputDebugString("D3DUtil_GenerateUVs failed, couldn't convert the simplified D3DXMesh back to a Mesh.\n");
		SAFE_RELEASE(SourceMesh);
		return FALSE;
	}

	SAFE_RELEASE(SourceMesh);

	// Re-build the mesh
	Mesh.RebuildBuffer();

	//// Add dummy LODs if the LOD being inserted is not the next one in the array
	//while(StaticMesh->LODModels.Num() <= DesiredLOD)
	//{
	//	// This LOD will be a new structure
	//	if(StaticMesh->LODModels.Num() <= DesiredLOD)
	//	{
	//		new(StaticMesh->LODModels) FStaticMeshRenderData();
	//	}
	//	// Any others will be dummies
	//	else
	//	{
	//		StaticMesh->LODModels.AddRawItem(0); 
	//	}
	//}

	//// Add dummy LODs if the LOD being inserted is not the next one in the array
	//while(StaticMesh->LODInfo.Num() <= DesiredLOD)
	//{
	//	StaticMesh->LODInfo.AddItem(FStaticMeshLODInfo());
	//}

	//FStaticMeshRenderData& NewLOD = StaticMesh->LODModels(DesiredLOD);
	//if (!ConvertD3DXMeshToUMesh(SourceMesh,NewLOD,BaseLOD.VertexBuffer.GetNumTexCoords(),BaseLOD.Elements, TRUE))
	//{
	//	appDebugMessagef(TEXT("GenerateLOD failed, couldn't convert the simplified D3DXMesh back to a UStaticMesh."));
	//	return FALSE;
	//}
	//// Re-build the static mesh
	//// todo - only rebuild the new LOD

	//StaticMesh->Build();

	return TRUE; 
}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CD3DArcBall::CD3DArcBall()
{
    D3DXQuaternionIdentity( &m_qDown );
    D3DXQuaternionIdentity( &m_qNow );
    D3DXMatrixIdentity( &m_matRotation );
    D3DXMatrixIdentity( &m_matRotationDelta );
    D3DXMatrixIdentity( &m_matTranslation );
    D3DXMatrixIdentity( &m_matTranslationDelta );
    m_bDrag = FALSE;
    m_fRadiusTranslation = 1.0f;
    m_bRightHanded = FALSE;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
VOID CD3DArcBall::SetWindow( int iWidth, int iHeight, float fRadius )
{
    // Set ArcBall info
    m_iWidth  = iWidth;
    m_iHeight = iHeight;
    m_fRadius = fRadius;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
D3DXVECTOR3 CD3DArcBall::ScreenToVector( int sx, int sy )
{
    // Scale to screen
    FLOAT x   = -(sx - m_iWidth/2)  / (m_fRadius*m_iWidth/2);
    FLOAT y   =  (sy - m_iHeight/2) / (m_fRadius*m_iHeight/2);

    if( m_bRightHanded )
    {
        x = -x;
        y = -y;
    }

    FLOAT z   = 0.0f;
    FLOAT mag = x*x + y*y;

    if( mag > 1.0f )
    {
        FLOAT scale = 1.0f/sqrtf(mag);
        x *= scale;
        y *= scale;
    }
    else
        z = sqrtf( 1.0f - mag );

    // Return vector
    return D3DXVECTOR3( x, y, z );
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
VOID CD3DArcBall::SetRadius( FLOAT fRadius )
{
    m_fRadiusTranslation = fRadius;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
LRESULT CD3DArcBall::HandleMouseMessages( HWND hWnd, UINT uMsg, WPARAM wParam,
                                          LPARAM lParam )
{
    static int         iCurMouseX;      // Saved mouse position
    static int         iCurMouseY;
    static D3DXVECTOR3 s_vDown;         // Button down vector

    // Current mouse position
    int iMouseX = LOWORD(lParam);
    int iMouseY = HIWORD(lParam);

    switch( uMsg )
    {
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
            // Store off the position of the cursor when the button is pressed
            iCurMouseX = iMouseX;
            iCurMouseY = iMouseY;
            return TRUE;

        case WM_LBUTTONDOWN:
            // Start drag mode
            m_bDrag = TRUE;
            s_vDown = ScreenToVector( iMouseX, iMouseY );
            m_qDown = m_qNow;
            return TRUE;

        case WM_LBUTTONUP:
            // End drag mode
            m_bDrag = FALSE;
            return TRUE;

        case WM_MOUSEMOVE:
            // Drag object
            if( MK_LBUTTON&wParam )
            {
                if( m_bDrag )
                {
                    // recompute m_qNow
                    D3DXVECTOR3 vCur = ScreenToVector( iMouseX, iMouseY );
                    D3DXQUATERNION qAxisToAxis;
                    D3DXQuaternionAxisToAxis(&qAxisToAxis, &s_vDown, &vCur);
                    m_qNow = m_qDown;
                    m_qNow *= qAxisToAxis;
                    D3DXMatrixRotationQuaternion(&m_matRotationDelta, &qAxisToAxis);
                }
                else
                    D3DXMatrixIdentity(&m_matRotationDelta);
                D3DXMatrixRotationQuaternion(&m_matRotation, &m_qNow);
                m_bDrag = TRUE;
            }
            else if( (MK_RBUTTON&wParam) || (MK_MBUTTON&wParam) )
            {
                // Normalize based on size of window and bounding sphere radius
                FLOAT fDeltaX = ( iCurMouseX-iMouseX ) * m_fRadiusTranslation / m_iWidth;
                FLOAT fDeltaY = ( iCurMouseY-iMouseY ) * m_fRadiusTranslation / m_iHeight;

                if( wParam & MK_RBUTTON )
                {
                    D3DXMatrixTranslation( &m_matTranslationDelta, -2*fDeltaX, 2*fDeltaY, 0.0f );
                    D3DXMatrixMultiply( &m_matTranslation, &m_matTranslation, &m_matTranslationDelta );
                }
                else  // wParam & MK_MBUTTON
                {
                    D3DXMatrixTranslation( &m_matTranslationDelta, 0.0f, 0.0f, 5*fDeltaY );
                    D3DXMatrixMultiply( &m_matTranslation, &m_matTranslation, &m_matTranslationDelta );
                }

                // Store mouse coordinate
                iCurMouseX = iMouseX;
                iCurMouseY = iMouseY;
            }
            return TRUE;
    }

    return FALSE;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CD3DCamera::CD3DCamera()
{
	m_bLeftHand = false;
    // Set attributes for the view matrix
    SetViewParams( D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,1.0f),
                   D3DXVECTOR3(0.0f,1.0f,0.0f) );

    // Set attributes for the projection matrix
    SetProjParams( D3DX_PI/4, 1.0f, 1.0f, 1000.0f );
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
VOID CD3DCamera::SetViewParams( const D3DXVECTOR3 &vEyePt, const D3DXVECTOR3& vLookatPt,
                                const D3DXVECTOR3& vUpVec )
{
    // Set attributes for the view matrix
    m_vEyePt    = vEyePt;
    m_vLookatPt = vLookatPt;
    m_vUpVec    = vUpVec;
    D3DXVec3Normalize( &m_vView, &(m_vLookatPt - m_vEyePt) );
    D3DXVec3Cross( &m_vCross, &m_vView, &m_vUpVec );

    if( m_bLeftHand )
		D3DXMatrixLookAtLH( &m_matView, &m_vEyePt, &m_vLookatPt, &m_vUpVec );
	else
		D3DXMatrixLookAtRH( &m_matView, &m_vEyePt, &m_vLookatPt, &m_vUpVec );

    D3DXMatrixInverse( &m_matBillboard, NULL, &m_matView );

	//D3DXVECTOR3 vYAxis( 0, 1, 0 );
	//D3DXMatrixRotationAxis( &m_matView, &vYAxis, (D3DX_PI/3) );

    m_matBillboard._41 = 0.0f;
    m_matBillboard._42 = 0.0f;
    m_matBillboard._43 = 0.0f;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
VOID CD3DCamera::SetProjParams( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane,
                                FLOAT fFarPlane )
{
    // Set attributes for the projection matrix
    m_fFOV        = fFOV;
    m_fAspect     = fAspect;
    m_fNearPlane  = fNearPlane;
    m_fFarPlane   = fFarPlane;

	if( m_bLeftHand )
		D3DXMatrixPerspectiveFovLH( &m_matProj, fFOV, fAspect, fNearPlane, fFarPlane );
	else
		D3DXMatrixPerspectiveFovRH( &m_matProj, fFOV, fAspect, fNearPlane, fFarPlane );
}

//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
void CD3DCamera::SetOrthoLH( D3DXVECTOR3 vMin, D3DXVECTOR3 vMax )
{
	if( m_bLeftHand )
		D3DXMatrixOrthoOffCenterLH(&m_matProj,vMin.x,vMax.x,vMin.y,vMax.y,vMin.z,vMax.z);
	else
		D3DXMatrixOrthoOffCenterRH(&m_matProj,vMin.x,vMax.x,vMin.y,vMax.y,vMin.z,vMax.z);

	m_fNearPlane  = vMin.z;
	m_fFarPlane   = vMax.z;


}

