#include "Me3d/Me3d.h"
#include "Me3d/BaseGraphics.h"
#include "Me3d/Include.h"
#include "Me3d/Engine/Engine.h"
#include "FuncPerformanceLog.h"

//#include "..\global.h"
//#include "..\math.h"
//#include "..\shader.h"
static CBaseGraphics g_drawer;
static CBaseGraphics::Vertex2D gs_Vertices2D[1024];
CBaseGraphics* GetDrawer()
{ 
	guardfunc;
	return &g_drawer; 
	unguard;
}

// BOOL CBaseGraphics::m_bUseGroup = FALSE;
// INT  CBaseGraphics::s_nGroupIdx = 0;

// CBaseGraphics::CRenderGroup CBaseGraphics::RenderGroup[50];


CBaseGraphics::CRenderGroup::~CRenderGroup()
{
	guardfunc;
	unguard;
}

CBaseGraphics::CBaseGraphics()
:m_bSupportUIZoom(false)
{
	guardfunc;
	
	unguard;
}

CBaseGraphics::~CBaseGraphics()
{
	guardfunc;
	unguard;
}


void CBaseGraphics::DrawLine3D( D3DXVECTOR3 v0, D3DXVECTOR3 v1, DWORD dwColor )
{
	guardfunc;
	Vertex3D v[2];
	v[0].p = v0;
	v[0].color = dwColor;
	v[1].p = v1;
	v[1].color = dwColor;

	
	//IRenderer* r = GetEngine()->GetRenderer();

	IRenderer* r = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE );
	r->SetRenderState( D3DRS_LIGHTING,  FALSE );
	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	r->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	r->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	r->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
	r->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );
	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );
	r->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	r->Commit();
	

	r->DrawPrimitiveUP( D3DPT_LINELIST, 1, v, sizeof( Vertex3D ) );
	unguard;
}
void CBaseGraphics::FillTri( D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, DWORD dwColor )
{
	guardfunc;
	Vertex3D v[3];

	v[0].p = v0;
	v[0].color = dwColor;

	v[1].p = v1;
	v[1].color = dwColor;

	v[2].p = v2;
	v[2].color = dwColor;


	DWORD dwColorOp = D3DTOP_MODULATE;
	DWORD dwColor1Arg1 = D3DTA_DIFFUSE;
	DWORD dwColor1Arg2 = D3DTA_CURRENT;

	DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
	DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
	DWORD dwAlphaBlendEnable = TRUE;
	DWORD dwAlphaOp = D3DTOP_MODULATE;
	DWORD dwAlphaArg1 = D3DTA_DIFFUSE;
	DWORD dwAlphaArg2 = D3DTA_CURRENT;

	DWORD dwZWriteEnable = FALSE;

	IRenderer* r = GetEngine()->GetRenderer();
	r->SetRenderState( D3DRS_LIGHTING, FALSE );
	
	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	r->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	r->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
	r->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
	r->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
	r->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );

	r->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	r->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	
	r->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColor1Arg1 );
	r->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColor1Arg2 );
	r->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );
	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );

	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE );
	

	r->DrawPrimitiveUP( D3DPT_TRIANGLELIST, 1, v, sizeof( Vertex3D ) );

	unguard;
}
void CBaseGraphics::FillTri( int x0, int y0, int x1, int y1, int x2, int y2, DWORD dwColor )
{
	guardfunc;
	Vertex2D v[3];

	v[0].p = D3DXVECTOR4( x0, y0, 0, 1 );
	v[0].color = dwColor;

	v[1].p = D3DXVECTOR4( x1, y1, 0, 1 );
	v[1].color = dwColor;

	v[2].p = D3DXVECTOR4( x2, y2, 0, 1 );
	v[2].color = dwColor;


	DWORD dwColorOp = D3DTOP_MODULATE;
	DWORD dwColor1Arg1 = D3DTA_DIFFUSE;
	DWORD dwColor1Arg2 = D3DTA_CURRENT;

	DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
	DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
	DWORD dwAlphaBlendEnable = TRUE;
	DWORD dwAlphaOp = D3DTOP_MODULATE;
	DWORD dwAlphaArg1 = D3DTA_DIFFUSE;
	DWORD dwAlphaArg2 = D3DTA_CURRENT;

	DWORD dwZWriteEnable = FALSE;

	IRenderer* r = GetEngine()->GetRenderer();
	r->SetRenderState( D3DRS_LIGHTING, FALSE );
	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	r->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	r->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
	r->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
	r->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );

	r->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColor1Arg1 );
	r->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColor1Arg2 );
	r->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );
	
	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );
	
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
	
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );


	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );
	

	r->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 1, v, sizeof( Vertex2D ) );
	unguard;
}

void CBaseGraphics::DrawProgressRect( int x, int y, int size, int nDegree )
{
	guardfunc;
	int s = size/2;
	POINT pt[] = 
	{
			x,y,
			x,y-s,
			x+s,y-s,
			x+s,y,
			x+s,y+s,
			x,y+s,
			x-s,y+s,
			x-s,y,
			x-s,y-s,
			x,y-s
	};

	int nTriCount = 8;
	int nArea = nDegree/45;
	switch( nArea )
	{
		// [0,45]
	case 0:
		nTriCount = 8;
		pt[1].x = x+tanf( DegreeToRad( nDegree-0 ) )*(s);
		pt[1].y = y-s;
		break;
		// [45,90]
	case 1:
		nTriCount = 7;
		pt[1].x = x;
		pt[1].y = y;
		pt[2].x = x+s;
		pt[2].y = y-tanf( DegreeToRad( 90-nDegree ) )*(s);
		break;
		// [90,135]
	case 2:
		nTriCount = 6;
		pt[2].x = x;
		pt[2].y = y;
		pt[3].x = x+s;
		pt[3].y = y+tanf( DegreeToRad( nDegree-90 ) )*(s);
		break;
		// [135,180]
	case 3:
		nTriCount = 5;
		pt[3].x = x;
		pt[3].y = y;
		pt[4].x = x+tanf( DegreeToRad( 180-nDegree ) )*(s);
		pt[4].y = y+s;
		break;
		// [180,225]
	case 4:
		nTriCount = 4;
		pt[4].x = x;
		pt[4].y = y;
		pt[5].x = x-tanf( DegreeToRad( nDegree-180 ) )*(s);
		pt[5].y = y+s;
		break;
		// [225,270]
	case 5:
		nTriCount = 3;
		pt[5].x = x;
		pt[5].y = y;
		pt[6].x = x-s;
		pt[6].y = y+tanf( DegreeToRad( 270-nDegree) )*(s);
		break;
		// [270,315]
	case 6:
		nTriCount = 2;
		pt[6].x = x;
		pt[6].y = y;
		pt[7].x = x-s;
		pt[7].y = y-tanf( DegreeToRad( nDegree-270 ) )*(s);
		break;
	case 7:
		nTriCount = 1;
		pt[7].x = x;
		pt[7].y = y;
		pt[8].x = x-tanf( DegreeToRad( 360-nDegree) )*(s);
		pt[8].y = y-s;
		break;
	default:
		assert( false && "base graphics draw progress error, degree must in[0,360]" );
	};

	Vertex2D v[10];
	for( int i = 0; i < 10; i++ )
	{
		v[i].p = D3DXVECTOR4( pt[i].x, pt[i].y, 0, 1 );
		v[i].color = 0xcf000000;
	}

	DWORD dwColorOp = D3DTOP_MODULATE;
	DWORD dwColor1Arg1 = D3DTA_DIFFUSE;
	DWORD dwColor1Arg2 = D3DTA_CURRENT;

	DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
	DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
	DWORD dwAlphaBlendEnable = TRUE;
	DWORD dwAlphaOp = D3DTOP_MODULATE;
	DWORD dwAlphaArg1 = D3DTA_DIFFUSE;
	DWORD dwAlphaArg2 = D3DTA_CURRENT;

	DWORD dwZWriteEnable = FALSE;

	IRenderer* r = GetEngine()->GetRenderer();
	r->SetRenderState( D3DRS_LIGHTING, FALSE );
	r->SetRenderState( D3DRS_ZENABLE, FALSE );
	r->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
	r->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
	r->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );
	r->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColor1Arg1 );
	r->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColor1Arg2 );
	r->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );
	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );

	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );

	r->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, nTriCount, &v[8-nTriCount], sizeof( Vertex2D ) );
	unguard;
}


void CBaseGraphics::DrawLine2D( int x0, int y0, int x1, int y1, DWORD dwColor )
{
	guardfunc;
	Vertex2D v[5];

	v[0].p = D3DXVECTOR4( x0, y0, 0, 1 );
	v[0].color = dwColor;
	v[1].p = D3DXVECTOR4( x1, y1, 0, 1 );
	v[1].color = dwColor;	
	IRenderer* r = GetEngine()->GetRenderer();
	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );
	

	r->DrawPrimitiveUP( D3DPT_LINESTRIP, 1, v, sizeof( Vertex2D ) );
	unguard;
}

void CBaseGraphics::DrawRect2D( POINT pt0, POINT pt1, DWORD dwColor )
{
	guardfunc;
	RECT rc = MakeRect( pt0, pt1 );	
	DrawRect2D( rc, dwColor );
	unguard;
}
void CBaseGraphics::DrawRect2D( RECT& rc, DWORD dwColor )
{
	guardfunc;
	Vertex2D v[5];

	v[0].p = D3DXVECTOR4( rc.left, rc.bottom, 0, 1 );
	v[0].color = dwColor;
	v[1].p = D3DXVECTOR4( rc.left, rc.top, 0, 1 );
	v[1].color = dwColor;
	v[2].p = D3DXVECTOR4( rc.right, rc.top, 0, 1 );
	v[2].color = dwColor;
	v[3].p = D3DXVECTOR4( rc.right, rc.bottom, 0, 1 );
	v[3].color = dwColor;
	v[4].p = D3DXVECTOR4( rc.left, rc.bottom, 0, 1 );
	v[4].color = dwColor;


	IRenderer* r = GetEngine()->GetRenderer();
	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );
	

	r->DrawPrimitiveUP( D3DPT_LINESTRIP, 4, v, sizeof( Vertex2D ) );
	unguard;
}

void CBaseGraphics::FillRect2D( POINT pt0, POINT pt1, DWORD dwColor )
{
	guardfunc;
	RECT rc = MakeRect( pt0, pt1 );	
	FillRect2D( rc, dwColor );
	unguard;
}

void CBaseGraphics::FillRect2D( RECT& rc, DWORD col1, DWORD col2, DWORD col3, DWORD col4 )
{
	guardfunc;
	Vertex2D v[4];
	v[0].p = D3DXVECTOR4( rc.left, rc.bottom, 0, 1 );
	v[0].color = col3;
	v[1].p = D3DXVECTOR4( rc.left, rc.top, 0, 1 );
	v[1].color = col1;
	v[2].p = D3DXVECTOR4( rc.right, rc.bottom, 0, 1 );
	v[2].color = col4;
	v[3].p = D3DXVECTOR4( rc.right, rc.top, 0, 1 );
	v[3].color = col2;

	DWORD dwColorOp = D3DTOP_MODULATE;
	DWORD dwColor1Arg1 = D3DTA_DIFFUSE;
	DWORD dwColor1Arg2 = D3DTA_CURRENT;

	DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
	DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
	DWORD dwAlphaBlendEnable = TRUE;
	DWORD dwAlphaOp = D3DTOP_MODULATE;
	DWORD dwAlphaArg1 = D3DTA_DIFFUSE;
	DWORD dwAlphaArg2 = D3DTA_CURRENT;

	DWORD dwZWriteEnable = FALSE;

	IRenderer* r = GetEngine()->GetRenderer();

	r->SetRenderState( D3DRS_LIGHTING, FALSE );
	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	r->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	r->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
	r->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
	r->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );
	r->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColor1Arg1 );
	r->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColor1Arg2 );
	r->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );
	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );
	r->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );


	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );

	r->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, v, sizeof( Vertex2D ) );
	unguard;
}

void CBaseGraphics::FillRect2D( RECT& rc, DWORD dwColor )
{
	guardfunc;
	if ( dwColor == 0 )
	{
		// 如果颜色是完全透明的则就不需要画了
		return;
	}
	FillRect2D( rc, dwColor, dwColor, dwColor, dwColor );
	unguard;
}

void CBaseGraphics::DrawCircle3D( float x, float y, float z, float r, int nSegment, DWORD dwColor )
{
	static Vertex3D v[1024];

	float d = D3DX_PI*2/nSegment;
	for( int i = 0; i <= nSegment; i++ )
	{
		v[i].p = D3DXVECTOR3( x+r*cosf( i*d ), y+r*sinf( i*d ), z );
		v[i].color = dwColor;
	}

	IRenderer* renderer = GetEngine()->GetRenderer();
	renderer->SetTexture( 0, NULL );
	renderer->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE );
	renderer->DrawPrimitiveUP( D3DPT_LINESTRIP, nSegment, v, sizeof( Vertex3D ) );	
}

void CBaseGraphics::DrawCircleFlat3D( float x, float y, float z, float r, int nSegment, DWORD dwColor )
{
	guardfunc;
	//static Vertex3D v[1024];

	//float d = D3DX_PI*2/nSegment;
	//for( int i = 0; i <= nSegment; i++ )
	//{
	//	v[i].p = D3DXVECTOR3( x+r*cosf( i*d ), y+r*sinf( i*d ), z );
	//	v[i].color = dwColor;
	//}

	//IRenderer* renderer = GetEngine()->GetRenderer();
	//renderer->SetTexture( 0, NULL );
	//renderer->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE );
	//renderer->DrawPrimitiveUP( D3DPT_LINESTRIP, nSegment, v, sizeof( Vertex3D ) );
	//static Vertex2D v[1024];
	Vertex2D* v = gs_Vertices2D;

	float d = D3DX_PI*2/nSegment;

	DWORD dwColorOp = D3DTOP_MODULATE;
	DWORD dwColor1Arg1 = D3DTA_DIFFUSE;
	DWORD dwColor1Arg2 = D3DTA_CURRENT;

	DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
	DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
	DWORD dwAlphaBlendEnable = TRUE;
	DWORD dwAlphaOp = D3DTOP_MODULATE;
	DWORD dwAlphaArg1 = D3DTA_DIFFUSE;
	DWORD dwAlphaArg2 = D3DTA_CURRENT;

	DWORD dwZWriteEnable = FALSE;

	IRenderer* renderer = GetEngine()->GetRenderer();

	renderer->SetRenderState( D3DRS_LIGHTING, FALSE );

	renderer->SetRenderState( D3DRS_ZENABLE, TRUE );
	renderer->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	renderer->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
	renderer->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
	renderer->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );
	renderer->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );

	renderer->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

	renderer->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColor1Arg1 );
	renderer->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColor1Arg2 );
	renderer->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );
	renderer->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );
	renderer->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
	renderer->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );

	renderer->SetTexture( 0, NULL );
	renderer->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );
	const int Dx[4]={ 1,-1,-1, 1};
	const int Dy[4]={ 1, 1,-1,-1};
	for (int horn=0;horn<4;horn++)
	{

		v[0].p = D3DXVECTOR4( x+r*Dx[horn], y+r*Dy[horn], z, 1 );
		v[0].color = dwColor;
		int nOffset = horn*nSegment/4;
		for( int i = 0; i <= nSegment/4; i++ )
		{
			v[nSegment/4 + 1 - i].p = D3DXVECTOR4( x+r*cosf( (nOffset+i)*d ), y+r*sinf( (nOffset+i)*d ), z, 1 );
			v[nSegment/4 + 1 - i].color = dwColor;
		}
		renderer->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, nSegment/4, v, sizeof( Vertex2D ) );
	}
	unguard;
}
void CBaseGraphics::DrawCircle2D( int x, int y, float r, int nSegment, DWORD dwColor )
{
	guardfunc;
	//static Vertex2D v[1024];
	Vertex2D* v = gs_Vertices2D;

	float d = D3DX_PI*2/nSegment;
	for( int i = 0; i <= nSegment; i++ )
	{
		v[i].p = D3DXVECTOR4( x+r*cosf( i*d ), y+r*sinf( i*d ), 0, 1 );
		v[i].color = dwColor;
	}

	IRenderer* renderer = GetEngine()->GetRenderer();
	renderer->SetTexture( 0, NULL );
	renderer->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );
	renderer->DrawPrimitiveUP( D3DPT_LINESTRIP, nSegment, v, sizeof( Vertex2D ) );
	unguard;
}
void CBaseGraphics::FillCircle3D( float x, float y, float z, float r, int nSegment, DWORD dwColor )
{
	guardfunc;
	//static Vertex3D v[1024];

	//float d = D3DX_PI*2/nSegment;

	//v[0].p = D3DXVECTOR3( x, y, z );
	//v[0].color = dwColor;
	//for( int i = 0; i <= nSegment; i++ )
	//{
	//	v[i+1].p = D3DXVECTOR3( x+r*cosf( i*d ), y+r*sinf( i*d ), z );
	//	v[i+1].color = dwColor;
	//}

	//IRenderer* renderer = GetEngine()->GetRenderer();

	//renderer->SetTexture( 0, NULL );
	//renderer->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE );	
	//renderer->SetRenderState( D3DRS_ZENABLE,  TRUE );

	//renderer->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, nSegment, v, sizeof( Vertex3D ) );

	//static Vertex2D v[1024];
	Vertex2D* v = gs_Vertices2D;

	float d = D3DX_PI*2/nSegment;

	v[0].p = D3DXVECTOR4( x, y, z, 1 );
	v[0].color = dwColor;
	for( int i = 0; i <= nSegment; i++ )
	{
		v[i+1].p = D3DXVECTOR4( x+r*cosf( i*d ), y+r*sinf( i*d ), z, 1 );
		v[i+1].color = dwColor;
	}

	DWORD dwColorOp = D3DTOP_MODULATE;
	DWORD dwColor1Arg1 = D3DTA_DIFFUSE;
	DWORD dwColor1Arg2 = D3DTA_CURRENT;

	DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
	DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
	DWORD dwAlphaBlendEnable = TRUE;
	DWORD dwAlphaOp = D3DTOP_MODULATE;
	DWORD dwAlphaArg1 = D3DTA_DIFFUSE;
	DWORD dwAlphaArg2 = D3DTA_CURRENT;

	DWORD dwZWriteEnable = FALSE;

	IRenderer* renderer = GetEngine()->GetRenderer();

	renderer->SetRenderState( D3DRS_LIGHTING, FALSE );

	renderer->SetRenderState( D3DRS_ZENABLE, TRUE );
	renderer->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	renderer->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	renderer->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
	renderer->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
	renderer->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );

	renderer->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColor1Arg1 );
	renderer->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColor1Arg2 );
	renderer->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );
	renderer->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );
	renderer->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
	renderer->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );

	renderer->SetTexture( 0, NULL );
	renderer->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );

	renderer->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, nSegment, v, sizeof( Vertex2D ) );
	unguard;
}
void CBaseGraphics::FillRing2D( float x, float y, float r0, float r1, int nSegment, DWORD dwColor, float t )
{
	guardfunc;

	//static Vertex2D v[1024];
	Vertex2D* v = gs_Vertices2D;

	float d = D3DX_PI*2/nSegment;

	int nNumSeg = t/(1.0f/nSegment);

	for( int i = 0; i <= nNumSeg; i++ )
	{
		v[i*2+0].p = D3DXVECTOR4( x+r0*cosf( i*d ), y+r0*sinf( i*d ), 0, 1 );
		v[i*2+0].color = dwColor;
		v[i*2+1].p = D3DXVECTOR4( x+r1*cosf( i*d ), y+r1*sinf( i*d ), 0, 1 );
		v[i*2+1].color = dwColor;
	}

	DWORD dwColorOp = D3DTOP_MODULATE;
	DWORD dwColor1Arg1 = D3DTA_DIFFUSE;
	DWORD dwColor1Arg2 = D3DTA_CURRENT;

	DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
	DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
	DWORD dwAlphaBlendEnable = TRUE;
	DWORD dwAlphaOp = D3DTOP_MODULATE;
	DWORD dwAlphaArg1 = D3DTA_DIFFUSE;
	DWORD dwAlphaArg2 = D3DTA_CURRENT;

	DWORD dwZWriteEnable = FALSE;

	IRenderer* r = GetEngine()->GetRenderer();

	r->SetRenderState( D3DRS_LIGHTING, FALSE );

	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	r->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	r->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
	r->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
	r->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );

	r->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColor1Arg1 );
	r->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColor1Arg2 );
	r->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );
	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );

	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );

	r->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2*nNumSeg, v, sizeof( Vertex2D ) );
	unguard;
}
//------- 填圆    (   at 2004-4-22)
void CBaseGraphics::FillCircle2D( int x, int y, float radius, int nSegment, DWORD dwColor )
{
	guardfunc;

	//static Vertex2D v[1024];
	Vertex2D* v = gs_Vertices2D;

	float d = D3DX_PI*2/nSegment;

	v[0].p = D3DXVECTOR4( x, y, 0, 1 );
	v[0].color = dwColor;
	for( int i = 0; i <= nSegment; i++ )
	{
		v[i+1].p = D3DXVECTOR4( x+radius*cosf( i*d ), y+radius*sinf( i*d ), 0, 1 );
		v[i+1].color = dwColor;
	}

	DWORD dwColorOp = D3DTOP_MODULATE;
	DWORD dwColor1Arg1 = D3DTA_DIFFUSE;
	DWORD dwColor1Arg2 = D3DTA_CURRENT;

	DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
	DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
	DWORD dwAlphaBlendEnable = TRUE;
	DWORD dwAlphaOp = D3DTOP_MODULATE;
	DWORD dwAlphaArg1 = D3DTA_DIFFUSE;
	DWORD dwAlphaArg2 = D3DTA_CURRENT;

	DWORD dwZWriteEnable = FALSE;

	IRenderer* r = GetEngine()->GetRenderer();

	r->SetRenderState( D3DRS_LIGHTING, FALSE );

	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	r->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	r->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
	r->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
	r->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );

	r->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColor1Arg1 );
	r->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColor1Arg2 );
	r->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );
	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );

	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );

	r->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, nSegment, v, sizeof( Vertex2D ) );
	unguard;
}

#define DU 3.14159/180

VOID rotate(float cx, float cy, FLOAT alpha, float &x, float &y ) 
{ 
	D3DXVECTOR2 v( x-cx, y-cy );
	D3DXMATRIX m;
	D3DXMatrixRotationZ( &m, -alpha );
	D3DXVec2TransformCoord( &v, &v, &m );

	x = v.x+cx;
	y = v.y+cy;
} 

BOOL CBaseGraphics::BltEx( int nTextureId,
						LPRECT lpDestRect, 
						LPRECT lpSrcRect, 
						LPRECT lpClipRect,
						int nSrcWidth,
						int nSrcHeight,
						float z, 
						DWORD dwColor,
						DWORD dwFlag,
						FLOAT fDir )
{
//	guardfunc;
	UVVertex2D vertex[4];
	float cx = (lpDestRect->left+lpDestRect->right)/2.0f;
	float cy = (lpDestRect->top+lpDestRect->bottom)/2.0f;
	D3DXVECTOR2 vPos;
	vPos.x = (lpDestRect->left+0.5);
	vPos.y = (lpDestRect->bottom-0.5);
	rotate( cx, cy, fDir, vPos.x, vPos.y );
	vertex[0].p = D3DXVECTOR4( vPos.x, vPos.y, z, 1 );
	vertex[0].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;
	vertex[0].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
	vertex[0].color = dwColor;

	vPos.x = (lpDestRect->left+0.5);
	vPos.y = (lpDestRect->top+0.5);
	rotate( cx, cy, fDir, vPos.x, vPos.y );
	vertex[1].p = D3DXVECTOR4( vPos.x, vPos.y, z, 1 );
	vertex[1].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;;
	vertex[1].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
	vertex[1].color = dwColor;

	vPos.x = (lpDestRect->right-0.5);
	vPos.y = (lpDestRect->bottom-0.5);
	rotate( cx, cy, fDir, vPos.x, vPos.y );
	vertex[2].p = D3DXVECTOR4( vPos.x, vPos.y, z, 1 );
	vertex[2].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
	vertex[2].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
	vertex[2].color = dwColor;

	vPos.x = (lpDestRect->right-0.5);
	vPos.y = (lpDestRect->top+0.5);
	rotate( cx, cy, fDir, vPos.x, vPos.y );
	vertex[3].p = D3DXVECTOR4( vPos.x, vPos.y, z, 1 );
	vertex[3].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
	vertex[3].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
	vertex[3].color = dwColor;
	short index[6] = { 0, 1, 2, 2, 1, 3 };

	GetEngine()->GetRenderer()->DirectPushSurface(
		nTextureId, 
		-1, 
		OBJECT2D_SHADER,
		D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1,
		sizeof( UVVertex2D ), 
		(BYTE*)vertex,
		4,
		(BYTE*)index,
		2,
		eAlphaBlend|dwFlag|eTwoSided );
	return TRUE;

//	unguard;		


}

void    CBaseGraphics::Blt2Tex( int nTextureId,
							int nAlphaTexId,
							LPRECT lpDestRect, 
							LPRECT lpSrcRect, 
							int nSrcWidth,
							int nSrcHeight,
							float z, 
							DWORD dwColor,
							DWORD dwFlag )
{

	UV2Vertex2D vertex[4];

	vertex[0].p = D3DXVECTOR4( (lpDestRect->left-0.5), (lpDestRect->bottom+0.5), z, 1 );
	vertex[0].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;
	vertex[0].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
	vertex[0].u1 = vertex[0].u;
	vertex[0].v1 = vertex[0].v;
	vertex[0].color = dwColor;

	vertex[1].p = D3DXVECTOR4( (lpDestRect->left-0.5), (lpDestRect->top-0.5), z, 1 );
	vertex[1].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;;
	vertex[1].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
	vertex[1].u1 = vertex[1].u;
	vertex[1].v1 = vertex[1].v;
	vertex[1].color = dwColor;

	vertex[2].p = D3DXVECTOR4( (lpDestRect->right+0.5), (lpDestRect->bottom+0.5), z, 1 );
	vertex[2].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
	vertex[2].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
	vertex[2].u1 = vertex[2].u;
	vertex[2].v1 = vertex[2].v;
	vertex[2].color = dwColor;

	vertex[3].p = D3DXVECTOR4( (lpDestRect->right+0.5), (lpDestRect->top-0.5), z, 1 );
	vertex[3].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
	vertex[3].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
	vertex[3].u1 = vertex[3].u;
	vertex[3].v1 = vertex[3].v;
	vertex[3].color = dwColor;
	short index[6] = { 0, 1, 2, 2, 1, 3 };


	GetEngine()->GetRenderer()->SetGlobalTransparent( 1.0f );

	{
		GetEngine()->GetRenderer()->DirectPushSurface(
			nTextureId, 
			nAlphaTexId, 
			TERRAIN_SPLATTING,
			D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1,
			sizeof( UVVertex2D ), 
			(BYTE*)vertex,
			4,
			(BYTE*)index,
			2,
			/*eAlphaBlend|dwFlag*/ 0 );
	}
}

// void CBaseGraphics::Lock()
// {
// 	guardfunc;
// 	
// 	for ( int i=0; i<s_nGroupIdx; i++ )
// 	{
// 		RenderGroup[i].nTex = -1;
// 		RenderGroup[i].dwRenderFlag = 0;
// 		RenderGroup[i].nUseVertex = 0;
// 		RenderGroup[i].nUseIndex = 0;		
// 	}
// 
// 	s_nGroupIdx = 0;
// 	unguard;
// }
// 
// void CBaseGraphics::UnLock()
// {
// 	guardfunc;
// 
// 	for ( int i=0; i<s_nGroupIdx; i++ )
// 	{
// 
// 		INT		nTex	= RenderGroup[i].nTex;
// 		DWORD	dwFlag	= RenderGroup[i].dwRenderFlag;
// 		INT		nUseVex = RenderGroup[i].nUseVertex;
// 		INT		nUseIdx = RenderGroup[i].nUseIndex;
// 		BYTE*	vertex  = (BYTE*)&RenderGroup[i].Vertexs;
// 		BYTE*	index   = (BYTE*)&RenderGroup[i].Indexs;
// 
// 		GetEngine()->GetRenderer()->DirectPushSurface(
// 			nTex, 
// 			-1, 
// 			OBJECT2D_SHADER,
// 			D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1,
// 			sizeof( UVVertex2D ), 
// 			(BYTE*)vertex,
// 			nUseVex,
// 			(BYTE*)index,
// 			nUseIdx/3,
// 			eAlphaBlend|dwFlag );
// 	}
// 	unguard;
// }
// 

void CBaseGraphics::Blt( int nTextureId,
						LPRECT lpDestRect, 
						LPRECT lpSrcRect, 
						int nSrcWidth,
						int nSrcHeight,
						float z, 
						DWORD dwColor,
						DWORD dwFlag )
{
	guardfunc;
	IRenderer* r = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
	ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nTextureId );
	if( pTexture != NULL )
	{
		LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pTexture->GetData();
		//pd3dDevice->SetTexture(0, pd3dTexture);
		BltTexture(pd3dTexture,lpDestRect,lpSrcRect,nSrcWidth,nSrcHeight,z,dwColor,dwFlag);
	}

}

void CBaseGraphics::BltTexture( LPDIRECT3DTEXTURE9 pd3dTexture, LPRECT lpDestRect, LPRECT lpSrcRect, int nSrcWidth, int nSrcHeight, float z, DWORD dwColor, DWORD dwFlag/*, FLOAT fRot = 0.0f */ )
{
	guardfunc;
	IRenderer* r = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
	r->SetTexture(0, pd3dTexture);
	UVVertex2D vertex[4];

// 	vertex[0].p = D3DXVECTOR4( ( lpDestRect->left - 0.5 ), (lpDestRect->bottom+0.5), z, 1 );
// 	vertex[0].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;
// 	vertex[0].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
// 	vertex[0].color = dwColor;
// 
// 	vertex[1].p = D3DXVECTOR4( (lpDestRect->left-0.5), (lpDestRect->top-0.5), z, 1 );
// 	vertex[1].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;;
// 	vertex[1].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
// 	vertex[1].color = dwColor;
// 
// 	vertex[2].p = D3DXVECTOR4( (lpDestRect->right+0.5), (lpDestRect->bottom+0.5), z, 1 );
// 	vertex[2].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
// 	vertex[2].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
// 	vertex[2].color = dwColor;
// 
// 	vertex[3].p = D3DXVECTOR4( (lpDestRect->right+0.5), (lpDestRect->top-0.5), z, 1 );
// 	vertex[3].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
// 	vertex[3].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
// 	vertex[3].color = dwColor;

	vertex[0].p = D3DXVECTOR4( ( lpDestRect->left - 0.5 ), (lpDestRect->bottom-0.5), z, 1 );
	vertex[0].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;
	vertex[0].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
	vertex[0].color = dwColor;

	vertex[1].p = D3DXVECTOR4( (lpDestRect->left-0.5), (lpDestRect->top-0.5), z, 1 );
	vertex[1].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;;
	vertex[1].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
	vertex[1].color = dwColor;

	vertex[2].p = D3DXVECTOR4( (lpDestRect->right-0.5), (lpDestRect->bottom-0.5), z, 1 );
	vertex[2].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
	vertex[2].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
	vertex[2].color = dwColor;

	vertex[3].p = D3DXVECTOR4( (lpDestRect->right-0.5), (lpDestRect->top-0.5), z, 1 );
	vertex[3].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
	vertex[3].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
	vertex[3].color = dwColor;




	r->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	r->SetRenderState(D3DRS_LIGHTING, FALSE);
	r->SetRenderState(D3DRS_FOGENABLE, FALSE);
	r->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	r->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	r->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	r->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	r->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE );

	r->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	r->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	r->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	r->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
	r->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	r->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	if(GetDrawer()->GetSupportUIZoom() || (dwFlag & eLinearFilter ))
	{
		r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	else
	{
		r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT); 
		r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT); 
	}

	r->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0);

	r->Commit();

	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vertex, sizeof(UVVertex2D) );


	unguard;		

}
BOOL CBaseGraphics::Blt( int nTextureId,
						LPRECT lpDestRect, 
						LPRECT lpSrcRect, 
						LPRECT lpClipRect,
						int nSrcWidth,
						int nSrcHeight,
						float z, 
						DWORD dwColor,
						DWORD dwFlag,
						int nAlphaTexId )
{
	//guardfunc;
	if( lpClipRect )
	{
		if( lpDestRect->right < lpClipRect->left )
			return FALSE;
		if( lpDestRect->left > lpClipRect->right )
			return FALSE;
		if( lpDestRect->bottom < lpClipRect->top )
			return FALSE;
		if( lpDestRect->top > lpClipRect->bottom )
			return FALSE;

		int nDestRectWidth = lpDestRect->right-lpDestRect->left;
		int nDestRectHeight = lpDestRect->bottom-lpDestRect->top;

		int nSrcRectWidth = lpSrcRect->right-lpSrcRect->left;
		int nSrcRectHeight = lpSrcRect->bottom-lpSrcRect->top;

		int nLength = 0;
		float t = 0.0f;
		if( lpDestRect->left < lpClipRect->left )
		{
			nLength = lpClipRect->left-lpDestRect->left;
			t = ((float)nLength)/nDestRectWidth;
			//lpDestRect->left += nLength;
			lpDestRect->left = lpClipRect->left;;
			lpSrcRect->left += (int)(t*nSrcRectWidth);
		}
		if( lpDestRect->right > lpClipRect->right )
		{
			nLength = lpDestRect->right-lpClipRect->right;
			t = ((float)nLength)/nDestRectWidth;
			//lpDestRect->right -= nLength;
			lpDestRect->right = lpClipRect->right;
			lpSrcRect->right -= (int)(t*nSrcRectWidth);
		}
		if( lpDestRect->top < lpClipRect->top )
		{
			nLength = lpClipRect->top-lpDestRect->top;
			t = ((float)nLength)/nDestRectHeight;
			//lpDestRect->top += nLength;
			lpDestRect->top = lpClipRect->top;;
			lpSrcRect->top += (int)((t)*nSrcRectHeight);
		}
		if( lpDestRect->bottom > lpClipRect->bottom )
		{
			nLength = lpDestRect->bottom-lpClipRect->bottom;
			t = ((float)nLength)/nDestRectHeight;
			//lpDestRect->bottom -= nLength;
			lpDestRect->bottom = lpClipRect->bottom;;
			lpSrcRect->bottom -= (int)((t)*nSrcRectHeight);
		}
	}

	if( nAlphaTexId == -1 )
	{
		Blt( nTextureId, lpDestRect, lpSrcRect, nSrcWidth, nSrcHeight, z, dwColor, dwFlag );
	}
	else
	{
		Blt2Tex(nTextureId, nAlphaTexId, lpDestRect, lpSrcRect, nSrcWidth, nSrcHeight, z, dwColor, dwFlag );
	}

	return TRUE;
	//unguard;
}

BOOL CBaseGraphics::BltNotTransparency(int nTextureId, LPRECT lpDestRect, LPRECT lpSrcRect, LPRECT lpClipRect, int nSrcWidth, int nSrcHeight, float z, DWORD dwColor, DWORD dwFlag)
{
	guardfunc;
	if( lpClipRect )
	{
		if( lpDestRect->right < lpClipRect->left )
			return FALSE;
		if( lpDestRect->left > lpClipRect->right )
			return FALSE;
		if( lpDestRect->bottom < lpClipRect->top )
			return FALSE;
		if( lpDestRect->top > lpClipRect->bottom )
			return FALSE;

		int nDestRectWidth = lpDestRect->right-lpDestRect->left;
		int nDestRectHeight = lpDestRect->bottom-lpDestRect->top;

		int nSrcRectWidth = lpSrcRect->right-lpSrcRect->left;
		int nSrcRectHeight = lpSrcRect->bottom-lpSrcRect->top;

		int nLength = 0;
		float t = 0.0f;
		if( lpDestRect->left < lpClipRect->left )
		{
			nLength = lpClipRect->left-lpDestRect->left;
			t = ((float)nLength)/nDestRectWidth;
			//lpDestRect->left += nLength;
			lpDestRect->left = lpClipRect->left;;
			lpSrcRect->left += (int)(t*nSrcRectWidth);
		}
		if( lpDestRect->right > lpClipRect->right )
		{
			nLength = lpDestRect->right-lpClipRect->right;
			t = ((float)nLength)/nDestRectWidth;
			//lpDestRect->right -= nLength;
			lpDestRect->right = lpClipRect->right;
			lpSrcRect->right -= (int)(t*nSrcRectWidth);
		}
		if( lpDestRect->top < lpClipRect->top )
		{
			nLength = lpClipRect->top-lpDestRect->top;
			t = ((float)nLength)/nDestRectHeight;
			//lpDestRect->top += nLength;
			lpDestRect->top = lpClipRect->top;;
			lpSrcRect->top += (int)((t)*nSrcRectHeight);
		}
		if( lpDestRect->bottom > lpClipRect->bottom )
		{
			nLength = lpDestRect->bottom-lpClipRect->bottom;
			t = ((float)nLength)/nDestRectHeight;
			//lpDestRect->bottom -= nLength;
			lpDestRect->bottom = lpClipRect->bottom;;
			lpSrcRect->bottom -= (int)((t)*nSrcRectHeight);
		}
	}


	UVVertex2D vertex[4];

	vertex[0].p = D3DXVECTOR4( ( lpDestRect->left - 0.5 ), (lpDestRect->bottom+0.5), z, 1 );
	vertex[0].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;
	vertex[0].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
	vertex[0].color = dwColor;

	vertex[1].p = D3DXVECTOR4( (lpDestRect->left-0.5), (lpDestRect->top-0.5), z, 1 );
	vertex[1].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;;
	vertex[1].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
	vertex[1].color = dwColor;

	vertex[2].p = D3DXVECTOR4( (lpDestRect->right+0.5), (lpDestRect->bottom+0.5), z, 1 );
	vertex[2].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
	vertex[2].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
	vertex[2].color = dwColor;

	vertex[3].p = D3DXVECTOR4( (lpDestRect->right+0.5), (lpDestRect->top-0.5), z, 1 );
	vertex[3].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
	vertex[3].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
	vertex[3].color = dwColor;

	IRenderer* r = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
	ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nTextureId );
	if( pTexture != NULL )
	{
		LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pTexture->GetData();
		//pd3dDevice->SetTexture(0, pd3dTexture);
		r->SetTexture(0, pd3dTexture);
	}

	r->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	r->SetRenderState(D3DRS_LIGHTING, FALSE);
	r->SetRenderState(D3DRS_FOGENABLE, FALSE);
	r->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	r->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	r->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE );

	r->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	r->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	r->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	r->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);
	r->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	r->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	if(GetDrawer()->GetSupportUIZoom() || (dwFlag & eLinearFilter ))
	{
		r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	else
	{
		r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT); 
		r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); 
	}

	r->Commit();

	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vertex, sizeof(UVVertex2D) );

	unguard;
	return TRUE;
}

void CBaseGraphics::DrawBox3D( D3DXVECTOR3 vMin, D3DXVECTOR3 vMax, DWORD dwColor )
{
	guardfunc;
	//Vertex3D v[12];
	D3DXVECTOR3 p[8];
	p[0] = D3DXVECTOR3( vMax.x, vMin.y, vMax.z );
	p[1] = D3DXVECTOR3( vMax.x, vMax.y, vMax.z );
	p[2] = D3DXVECTOR3( vMin.x, vMax.y, vMax.z );
	p[3] = D3DXVECTOR3( vMin.x, vMin.y, vMax.z );

	p[4] = D3DXVECTOR3( vMax.x, vMin.y, vMin.z );
	p[5] = D3DXVECTOR3( vMax.x, vMax.y, vMin.z );
	p[6] = D3DXVECTOR3( vMin.x, vMax.y, vMin.z );
	p[7] = D3DXVECTOR3( vMin.x, vMin.y, vMin.z );

	Vertex3D v[12][2];

	for( int i = 0; i < 12; i++ )
	{
		v[i][0].color = dwColor;
		v[i][1].color = dwColor;
	}

	v[0][0].p = p[0];
	v[0][1].p = p[1];

	v[1][0].p = p[1];
	v[1][1].p = p[2];

	v[2][0].p = p[2];
	v[2][1].p = p[3];

	v[3][0].p = p[3];
	v[3][1].p = p[0];

	v[4][0].p = p[4];
	v[4][1].p = p[5];

	v[5][0].p = p[5];
	v[5][1].p = p[6];

	v[6][0].p = p[6];
	v[6][1].p = p[7];

	v[7][0].p = p[7];
	v[7][1].p = p[4];

	v[8][0].p = p[0];
	v[8][1].p = p[4];

	v[9][0].p = p[1];
	v[9][1].p = p[5];

	v[10][0].p = p[2];
	v[10][1].p = p[6];

	v[11][0].p = p[3];
	v[11][1].p = p[7];

	IRenderer* r = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE );
	r->SetRenderState( D3DRS_LIGHTING,  FALSE );
	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	r->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	r->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	r->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
	r->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );
	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );
	r->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	

	r->DrawPrimitiveUP( D3DPT_LINELIST, 12, v, sizeof( Vertex3D ) );
	unguard;
}
void CBaseGraphics::DrawBox3D( Box* pBox, DWORD dwColor )
{
	guardfunc;

	D3DXVECTOR3* vv = (D3DXVECTOR3*)pBox->v;
	
	D3DXVECTOR3 p[8];
	p[0] = vv[5];
	p[1] = vv[7];
	p[2] = vv[6];
	p[3] = vv[4];
	p[4] = vv[1];
	p[5] = vv[3];
	p[6] = vv[2];
	p[7] = vv[0];

	Vertex3D v[12][2];

	for( int i = 0; i < 12; i++ )
	{
		v[i][0].color = dwColor;
		v[i][1].color = dwColor;
	}

	v[0][0].p = p[0];
	v[0][1].p = p[1];

	v[1][0].p = p[1];
	v[1][1].p = p[2];

	v[2][0].p = p[2];
	v[2][1].p = p[3];

	v[3][0].p = p[3];
	v[3][1].p = p[0];

	v[4][0].p = p[4];
	v[4][1].p = p[5];

	v[5][0].p = p[5];
	v[5][1].p = p[6];

	v[6][0].p = p[6];
	v[6][1].p = p[7];

	v[7][0].p = p[7];
	v[7][1].p = p[4];

	v[8][0].p = p[0];
	v[8][1].p = p[4];

	v[9][0].p = p[1];
	v[9][1].p = p[5];

	v[10][0].p = p[2];
	v[10][1].p = p[6];

	v[11][0].p = p[3];
	v[11][1].p = p[7];

	IRenderer* r = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
	r->SetTexture( 0, NULL );
    r->SetTexture( 1, NULL );
    r->SetRenderState( D3DRS_LIGHTING,  FALSE );
    r->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);
    r->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    r->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	r->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	r->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	r->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE );
	r->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	
	r->DrawPrimitiveUP( D3DPT_LINELIST, 12, v, sizeof( Vertex3D ) );

	unguard;
}
void CBaseGraphics::RenderTexture( void* pTex, LPRECT lpDestRect, LPRECT lpSrcRect, int nSrcWidth, int nSrcHeight, float z, DWORD dwColor )
{
	UVVertex2D vertex[4];

	vertex[0].p = D3DXVECTOR4( ( lpDestRect->left - 0.5 ), (lpDestRect->bottom+0.5), z, 1 );
	vertex[0].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;
	vertex[0].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
	vertex[0].color = dwColor;

	vertex[1].p = D3DXVECTOR4( (lpDestRect->left-0.5), (lpDestRect->top-0.5), z, 1 );
	vertex[1].u = (float)(lpSrcRect->left+0.5f)/nSrcWidth;;
	vertex[1].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
	vertex[1].color = dwColor;

	vertex[2].p = D3DXVECTOR4( (lpDestRect->right+0.5), (lpDestRect->bottom+0.5), z, 1 );
	vertex[2].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
	vertex[2].v = (float)(lpSrcRect->bottom-0.5f)/nSrcHeight;
	vertex[2].color = dwColor;

	vertex[3].p = D3DXVECTOR4( (lpDestRect->right+0.5), (lpDestRect->top-0.5), z, 1 );
	vertex[3].u = (float)(lpSrcRect->right-0.5f)/nSrcWidth;
	vertex[3].v = (float)(lpSrcRect->top+0.5f)/nSrcHeight;
	vertex[3].color = dwColor;

	IRenderer* r = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
	if( pTex )
	{
		r->SetTexture(0, pTex);
	}

	r->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	r->SetRenderState(D3DRS_LIGHTING, FALSE);
	r->SetRenderState(D3DRS_FOGENABLE, FALSE);
	r->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	r->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	r->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	r->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	r->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE );

	r->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	r->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	r->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	r->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
	r->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	r->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	r->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0);

	r->Commit();

	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vertex, sizeof(UVVertex2D) );
}

