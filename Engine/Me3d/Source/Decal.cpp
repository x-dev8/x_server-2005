#include "Me3d/Decal.h"
#include "Me3d/Include.h"

#include "Me3d/MathLib.h"
#include "math.h"

//#include "shader.h"
#include "Me3d/Global.h"
//#include "surface.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Config.h"
#include "FuncPerformanceLog.h"
#include "Dxsdk/d3dx9.h"
// D3DXVECTOR3* (*g_pfnGetDecal)( const D3DXVECTOR3 &vLeftBottom,const D3DXVECTOR3 &vLeftTop,
// 									 const D3DXVECTOR3 &vRightTop,const D3DXVECTOR3 &vRightBottom,
// 									 int &iTriCount ) = NULL;

short Decal::m_nFaceIndex[];	// 一个足够大的面索引
Decal::Decal()
{
	guardfunc;
	m_nTextureId = -1;
	m_nTriangleCount = 0;
	m_nVertexCount = 0;
	m_pIB = NULL;
	unguard;
}

Decal::~Decal()
{
	guardfunc;
	if( m_pIB )
	{
		m_pIB->Release();
		m_pIB = NULL;
	}
	unguard;
}

bool Decal::Create()
{
	guardfunc;
	//HRESULT hr;
	//while(1)
	//{
	//	hr = m_pDevice->CreateIndexBuffer( 1024*8*6*sizeof(unsigned short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL );
	//	if( SUCCEEDED(hr) ) break;
	//}
	return true;
	unguard;
}

void Decal::Destroy()
{
	guardfunc;
	m_nTextureId = -1;
	m_nTriangleCount = 0;
	m_nVertexCount = 0;
	unguard;
}

void Decal::SetRect( Vector vRect[4] )
{
	guardfunc;
	m_vRect[0] = vRect[0];
	m_vRect[1] = vRect[1];
	m_vRect[2] = vRect[2];
	m_vRect[3] = vRect[3];
	unguard;
}

Vector* Decal::GetRect()
{
	guardfunc;
	return m_vRect;
	unguard;
}

void Decal::SetTextureId( int nTextureId )
{
	guardfunc;
	m_nTextureId = nTextureId;
	unguard;
}

int Decal::GetTextureId()
{
	guardfunc;
	return m_nTextureId;
	unguard;
}

int Decal::GetTriangleCount()
{
	guardfunc;
	return m_nTriangleCount;
	unguard;
}

int Decal::GetVertexCount()
{
	guardfunc;
	return m_nVertexCount;
	unguard;
}

int Decal::CompareU( const void *arg1, const void *arg2 )
{
	guardfunc;
	Its* v0 = (Its*)arg1;
	Its* v1 = (Its*)arg2;
	if( v0->u > v1->u )return 1;
	if( v0->u < v1->u )return -1;
	return 0;
	unguard;
}

int Decal::CompareV( const void *arg1, const void *arg2 )
{
	guardfunc;
	Its* v0 = (Its*)arg1;
	Its* v1 = (Its*)arg2;
	if( v0->v > v1->v )return 1;
	if( v0->v < v1->v )return -1;
	return 0;
	unguard;
}
BOOL FindIts( std::vector<Decal::Its>& vectorIts, Decal::Its& it )
{
	guardfunc;
	for( int k = 0; k < vectorIts.size(); k++ )
	{
		if( FloatCmp( it.p.x, vectorIts[k].p.x ) == 0 &&
			FloatCmp( it.p.y, vectorIts[k].p.y ) == 0 )
		{
			return TRUE;
		}
	}
	unguard;
	return FALSE;
}
void AddIts( std::vector<Decal::Its>& vectorIts, Decal::Its& it )
{
	guardfunc;
	if( !FindIts( vectorIts, it ) )
		vectorIts.push_back( it );
	unguard;
}

void Decal::TriClipRect( Vector tri3[3], Vector rect3[4], std::vector<Its>& vectorIts )
{
	guardfunc;
	
	Vector2 rect[4] = 
	{
		Vector2( rect3[0].x, rect3[0].z ), 
		Vector2( rect3[1].x, rect3[1].z ), 
		Vector2( rect3[2].x, rect3[2].z ), 
		Vector2( rect3[3].x, rect3[3].z ), 
	};
	Vector2 tri[3] = 
	{
		Vector2( tri3[0].x, tri3[0].z ),
		Vector2( tri3[1].x, tri3[1].z ),
		Vector2( tri3[2].x, tri3[2].z ),
	};	

	/*int flag[3] = { 0, 0, 0 };
	for( int k = 0; k < 3; k++ )
	{
		if( tri[k].x < rect[left].x )
			flag[k] |= 1;
		
		if( tri[k].x > rect[right].x )
			flag[k] |= 1<<1;
		
		if( tri[k].y < rect[top].y )
			flag[k] |= 1<<2;
		
		if( tri[k].y > rect[bottom].y )
			flag[k] |= 1<<3;
	}
	
	if( flag[0]&1 == 1 &&
		flag[1]&1 == 1 &&
		flag[2]&1 == 1 )
		return;
	if( flag[0]&2 == 1 &&
		flag[1]&2 == 1 &&
		flag[2]&2 == 1 )
		return;
	if( flag[0]&4 == 1 &&
		flag[1]&4 == 1 &&
		flag[2]&4 == 1 )
		return;
	if( flag[0]&8 == 1 &&
		flag[1]&8 == 1 &&
		flag[2]&8 == 1 )
		return;*/

	// 剔除
	if( tri[0].x < rect[Math::left].x &&
		tri[1].x < rect[Math::left].x &&
		tri[2].x < rect[Math::left].x )
		return;
	if( tri[0].x > rect[Math::right].x &&
		tri[1].x > rect[Math::right].x &&
		tri[2].x > rect[Math::right].x )
		return;
	if( tri[0].y < rect[Math::top].y &&
		tri[1].y < rect[Math::top].y &&
		tri[2].y < rect[Math::top].y )
		return;
	if( tri[0].y > rect[Math::bottom].y &&
		tri[1].y > rect[Math::bottom].y &&
		tri[2].y > rect[Math::bottom].y )
		return;

	//double k0 = ( tri3[1].x-tri3[0].x )/( tri3[1].z-tri3[0].z );
	//double k1 = ( tri3[2].x-tri3[0].x )/( tri3[2].z-tri3[0].z );
	//if( FloatCmp( k0, k1, 0.11f ) == 0 )
	//	return ;
	/*Vector e0 = tri3[1]-tri3[0];
	Vector e1 = tri3[2]-tri3[0];
	Vector normal = e0.cross( e1 );
	if( FloatCmp( normal.y, 0.01, 0.01f ) == 0 )
		return;*/
	
	
	Vector2 vTriEdge[3][2] = 
	{
		tri[0], tri[1],
		tri[1], tri[2],
		tri[2], tri[0],
	};
	Vector2 vRectEdge[4][2] = 
	{
		rect[0], rect[1],
		rect[1], rect[2],
		rect[2], rect[3],
		rect[3], rect[0],
	};
	
	Vector2 out;
	float t, u, v;
	float tu, tv;
	std::vector<Its> s;
	
	for( int nRectVertexId = 0; nRectVertexId < 4; nRectVertexId++ )
	{
		// 直接加入顶点列表
		if( InsideTri( tri, rect[nRectVertexId], &tu, &tv ) )
		{
			Its its;
			its.idx = 3;
			its.t = tv;
			its.s = tu;

			switch( nRectVertexId )
			{
			case Math::left:
				u = 0.0f;
				v = 0.0f;
				break;
			case Math::bottom:
				u = 0.0f;
				v = 1.0f;
				break;
			case Math::right:
				u = 1.0f;
				v = 1.0f;
				break;
			case Math::top:
				u = 1.0f;
				v = 0.0f;
				break;
			}
			its.p = rect[nRectVertexId];
			its.u = u;
			its.v = v;
			//vectorIts.push_back( its );
			AddIts( vectorIts, its );
		}
	
		s.clear();
		for( int nTriEdgeId = 0; nTriEdgeId < 3; nTriEdgeId++ )
		{
			if( nRectVertexId == Math::left || 
				nRectVertexId == Math::right ) 
			{
				if( ClipVertical( vTriEdge[nTriEdgeId], vRectEdge[nRectVertexId], &out, &t, &v ) )
				{
					Its its;
					its.p = out;
					its.idx = nTriEdgeId;
					if( nRectVertexId == Math::left )
						its.u = 0.0f;
					else
					{
						its.u = 1.0f;
					}
					its.v = v;
					its.t = t;

					s.push_back( its );

				}
			}
			else
			{
				if( ClipHorizon( vTriEdge[nTriEdgeId], vRectEdge[nRectVertexId], &out, &t, &u ) )
				{
					Its its;
					its.p = out;
					its.idx = nTriEdgeId;
					if( nRectVertexId == Math::top )
						its.v = 0.0f;
					else 
						its.v = 1.0f;
					its.u = u;
					its.t = t;

					s.push_back( its );
				}

			}
		}
		if( s.size() > 0 )
		{
			if( nRectVertexId == Math::left || nRectVertexId == Math::right )
			{	
				qsort( (void *)&s[0], s.size(), sizeof( Its ) , CompareV );
				if( nRectVertexId == Math::right )
				{
					for( int i = 0; i < s.size(); i++ )
						s[i].v = 1-s[i].v;
				}
			}
			else
			{
				qsort( (void *)&s[0], s.size(), sizeof( Its ) , CompareU );
				if( nRectVertexId == Math::top )
				{
					for( int i = 0; i < s.size(); i++ )
						s[i].u = 1-s[i].u;
				}
			}
			
			for( int n = 0; n < s.size(); n++ )
			{
				AddIts( vectorIts, s[n] );
				//bool found = false;
				//for( int k = 0; k < vectorIts.size(); k++ )
				//{
				//	if( s[n].p.x == vectorIts[k].p.x &&
				//		s[n].p.y == vectorIts[k].p.y )
				//	{
				//		found = true;
				//		break;
				//	}
				//}
				//if( !found )
				//	vectorIts.push_back( s[n] );
			}

		}
	}
	
	for( int nTriEdgeId = 0; nTriEdgeId < 3; nTriEdgeId++ )
	{
		if( InsideRect( tri[nTriEdgeId], rect ) )
		{
			Its its;
			its.idx = nTriEdgeId;
			its.u = ( tri[nTriEdgeId].x-rect[Math::left].x )/( rect[Math::right].x-rect[Math::left].x );
			its.v = ( tri[nTriEdgeId].y-rect[Math::top].y )/( rect[Math::bottom].y-rect[Math::top].y );
			its.t = 0;


			if( vectorIts.size() < 3 )
			{
				its.p = tri[nTriEdgeId];
				//vectorIts.push_back( its );
				AddIts( vectorIts, its );
			}
			else
			{
				bool added = false;
				for( int i = 0; i < vectorIts.size()-1; i++ )
				{
					if( OutLine( vectorIts[i].p, vectorIts[i+1].p, tri[nTriEdgeId] ) )
					{
						its.p = tri[nTriEdgeId];
						if( !FindIts( vectorIts, its ) )
						{
							vectorIts.insert( vectorIts.begin()+i+1, its );
							added = true;
							break;
						}
					}
				}
				if( !added )
				{
					its.p = tri[nTriEdgeId];
					//vectorIts.push_back( its );
					AddIts( vectorIts, its );
				}
			}
		}
	}
	unguard;
}

int Decal::DecalAABB( Vector tri[3], Vector rect[4], std::vector<Decal::Vertex>& vectorVertex )
{
	guardfunc;
	vectorVertex.clear();
	std::vector<Its> vectorIts;
	TriClipRect( tri, rect, vectorIts );

	Decal::Vertex vertex;
	Vector v;
	int nSize = vectorIts.size();
	for( int i = 0; i < vectorIts.size(); i++ )
	{
		Its* pits = &vectorIts[i];

		vertex.p.x = vectorIts[i].p.x;
		vertex.p.y = 0;
		vertex.p.z = vectorIts[i].p.y;

		vertex.u = vectorIts[i].u;
		vertex.v = vectorIts[i].v;
	
		float t = vectorIts[i].t;
		float s = vectorIts[i].s;
		float delta = 2.0f*GetMe3dConfig()->m_fMdlSpaceScale+0.05f;
		switch( vectorIts[i].idx )
		{
		case 0:
			vertex.p.y = tri[0].y+t*(tri[1].y-tri[0].y )+delta;
			break;
		case 1:
			vertex.p.y = tri[1].y+t*(tri[2].y-tri[1].y )+delta;
			break;
		case 2:
			vertex.p.y = tri[2].y+t*(tri[0].y-tri[2].y )+delta;
			break;
		case 3:
			{
				Vector l0 = t*(tri[1]-tri[0]);
				Vector l1 = s*(tri[2]-tri[0]);
				vertex.p = tri[0]+l0+l1+Vector( 0, delta, 0  );
			}
			break;
		default:
			assert( false );
			break;
		}
		vectorVertex.push_back( vertex );
	}
	return vectorVertex.size();
	unguard;
}

int Decal::DecalAABBBatch( int nTriangleCount, Vector tri[], Vector rect[4] )
{
	guardfunc;
	m_vectorVertex.clear();
	std::vector<Decal::Vertex> vectorTmp;
	int nTotalTriangleCount = 0;
	int nTotalVertexCount = 0;
	for( int i = 0; i < nTriangleCount; i++ )
	{
		vectorTmp.clear();

		DecalAABB( &tri[i*3], rect, vectorTmp );
		
		int nVertexCount = vectorTmp.size();
		if( nVertexCount < 3 )
			continue;
		

		for( int nVertexId = 0; nVertexId < nVertexCount; nVertexId++ )
		{
			SwapYZ( vectorTmp[nVertexId].p );
			vectorTmp[nVertexId].color = 0xffffffff;
			m_vectorVertex.push_back( vectorTmp[nVertexId] );
		}
		
		for( int nTriangleId = 1; nTriangleId < nVertexCount-1; nTriangleId++ )
		{
			m_nFaceIndex[nTotalTriangleCount*3] = nTotalVertexCount;
			m_nFaceIndex[nTotalTriangleCount*3+1] = nTotalVertexCount+nTriangleId;
			m_nFaceIndex[nTotalTriangleCount*3+2] = nTotalVertexCount+nTriangleId+1;
			
			int v0 = m_nFaceIndex[nTotalTriangleCount*3];
			int v1 = m_nFaceIndex[nTotalTriangleCount*3+1];
			int v2 = m_nFaceIndex[nTotalTriangleCount*3+2];

			if( ( m_vectorVertex[v0].p.x == m_vectorVertex[v1].p.x &&
				m_vectorVertex[v0].p.y == m_vectorVertex[v1].p.y &&
				m_vectorVertex[v0].p.z == m_vectorVertex[v1].p.z )
				||
				( m_vectorVertex[v0].p.x == m_vectorVertex[v2].p.x &&
				m_vectorVertex[v0].p.y == m_vectorVertex[v2].p.y &&
				m_vectorVertex[v0].p.z == m_vectorVertex[v2].p.z )
				||
				( m_vectorVertex[v2].p.x == m_vectorVertex[v1].p.x &&
				m_vectorVertex[v2].p.y == m_vectorVertex[v1].p.y &&
				m_vectorVertex[v2].p.z == m_vectorVertex[v1].p.z ) )
			{
				//assert( false );
				m_vectorVertex[v0].p = m_vectorVertex[v1].p;
				m_vectorVertex[v2].p = m_vectorVertex[v1].p;
			}
			
			nTotalTriangleCount++;
		}
		nTotalVertexCount += nVertexCount;
	}
	
	m_nTriangleCount = nTotalTriangleCount;
	m_nVertexCount = nTotalVertexCount;
	
	return nTotalTriangleCount;
	unguard;
}

void Decal::Render( float fTransparent, DWORD dwColor )
{
	guardfunc;
	//SetWordMatrix( NULL );
	if( m_nTriangleCount >= 1 )
	{
		int nVertexCount = m_vectorVertex.size();

		for( int i = 0; i < nVertexCount; i++ )
		{
			//DWORD color = m_vectorVertex[i].color;
			DWORD dwAlpha = (dwColor&0xff000000)>>24;

			dwAlpha = (DWORD)(dwAlpha*fTransparent);
			if( dwAlpha > 255 )
				dwAlpha = 255;
			m_vectorVertex[i].color = dwAlpha<<24|(dwColor&0x00ffffff);
		}

		GetEngine()->GetRenderer()->DirectPushSurface(
			m_nTextureId, 
			-1, 
			MEX2_SHADER,
			//DECAL_SHADER,
			D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,
			sizeof( Vertex ),
			(unsigned char*)&m_vectorVertex[0],
			m_nVertexCount,
			(unsigned char*)m_nFaceIndex, 
			m_nTriangleCount,
			eAlphaBlend|/*eZDisable|*/eZWriteDisable|eLightingDisable );
	}
	unguard;
}