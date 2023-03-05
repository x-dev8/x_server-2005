#ifndef _decal_h
#define _decal_h

#include "Me3d.h"
#include "emitter.h"
#include "Vector.h"

class Vector;

class Decal:public Emitter
{
public:
	typedef struct
	{
		Vector2 p;	// 交点坐标
		int idx;	// 三角形边编号
		float t;	// 交点相对三角形边的参数t
		float s;	// 顶点落在三角形内部时，一个点要靠三角形的两条边来描述，和t配套使用，
		float u, v;	// 交点相对矩形的uv坐标，贴图使用
	} Its;

	typedef struct 
	{
		Vector p;
		unsigned long color;
		float u, v;
	} Vertex;

private:
	static short m_nFaceIndex[10*1024*3];	// 一个足够大的面索引

	LPDIRECT3DINDEXBUFFER9			m_pIB;
protected:
	Vector m_vRect[4];
	int m_nTriangleCount;
	int m_nVertexCount;
	int m_nTextureId;
	std::vector<Vertex> m_vectorVertex;
	
	static int CompareU( const void *arg1, const void *arg2 );
	static int CompareV( const void *arg1, const void *arg2 );
	void TriClipRect( Vector tri3[3], Vector rect3[4], std::vector<Its>& vectorIts );
public:
	Decal();
	virtual ~Decal();

	bool Create();
	void Destroy();

	void SetRect( Vector vRect[4] );
	Vector* GetRect();

	void SetTextureId( int nTextureId );
	int GetTextureId();

	int GetTriangleCount();
	int GetVertexCount();

	int DecalAABB( Vector tri[3], Vector rect[4], std::vector<Vertex>& vectorVertex );
	int DecalAABBBatch( int nTriangleCount, Vector tri[], Vector rect[4] );
	void Render( float fTransparent, DWORD dwColor );
};

// extern D3DXVECTOR3* (*g_pfnGetDecal)( const D3DXVECTOR3 &vLeftBottom,const D3DXVECTOR3 &vLeftTop,
// 							  const D3DXVECTOR3 &vRightTop,const D3DXVECTOR3 &vRightBottom,
// 							  int &iTriCount );

#endif