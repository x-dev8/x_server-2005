#ifndef _prim_h
#define _prim_h

#include "Me3d.h"
#include "vector.h"

class Vector;

class Plane
{
public:
	Plane()
	{
		a = b = c = d = 0;
	}
public:
	float a, b, c, d;
};

class Coord
{
public:
	void SetXAxis( Vector* axis ){ m_vXAxis = *axis; }
	void SetYAxis( Vector* axis ){ m_vYAxis = *axis; }
	void SetZAxis( Vector* axis ){ m_vZAxis = *axis; }
	void SetOrigin( Vector* origin ){ m_vOrigin = *origin; }
	void GetXAxis( Vector* axis ){ *axis = m_vXAxis; }
	void GetYAxis( Vector* axis ){ *axis = m_vYAxis; }
	void GetZAxis( Vector* axis ){ *axis = m_vZAxis; }
	void GetOrigin( Vector* o ){ *o = m_vOrigin; }

	void BuildTransformMatrix();
	MeMatrix* GetTransformMatrix(){ return &m_matTransform; }
protected:
	Vector m_vOrigin;	// o
	Vector m_vXAxis;	// right
	Vector m_vYAxis;	// up
	Vector m_vZAxis;	// 
	MeMatrix m_matTransform;
};

class BoundPlane:public Coord
{
public:
	void SetWidth( float w ){ m_fWidth = w; }
	void SetHeight( float h ){ m_fHeight = h; }
	float GetWidth(){ return m_fWidth; }
	float GetHeight(){ return m_fHeight; }
	void GetNormal( Vector* normal ){ GetZAxis( normal ); }
protected:
	float m_fWidth;
	float m_fHeight;
};

class Box
{
public:
	void BuildAABB( const Vector& max, const Vector& min );
	void BuildPlane();
	void Build( const MeMatrix& matTransform, const Vector& max, const Vector& min );
	void Transform( const MeMatrix& matTransform, Box& worldBox );
	bool Intersect( const Vector& pos, const Vector& dir ,float* pfDis = NULL,bool bNearest = false);
	bool IntersectCircle( const Vector& pos, const Vector& dir, float fDisToRole );
	bool Cull( const Box& box );
public:
	Vector	v[8];
	Plane	plane[6];
};

class Frustum:public Box
{
public:
	void Build( const MeMatrix& matView, const MeMatrix& matProj );	
};

class PrimMesh
{
public:
	typedef Vector Vertex;
	typedef struct
	{
		short nVertexId[3];
	} Face;
public:
	int GetVertexCount(){ return static_cast<int>( m_vectorVertex.size() ); }
	int GetFaceCount(){ return static_cast<int>( m_vectorFace.size() ); }
	Vertex* GetVertexPointer( int nVertexId )
	{
		return &m_vectorVertex[nVertexId];
	}
	Face* GetFacePointer( int nFaceId )
	{
		return &m_vectorFace[nFaceId];
	}
	
	bool Create( int nVertexCount, int nFaceCount )
	{
		Destroy();
		m_vectorVertex.reserve( nVertexCount );
		m_vectorVertex.resize( nVertexCount );
		m_vectorFace.reserve( nFaceCount );
		m_vectorFace.resize( nFaceCount );
		return true;
	}
	void Destroy()
	{ 
		m_vectorVertex.clear();
		m_vectorFace.clear();
	}
protected:
	std::vector<Vertex> m_vectorVertex;
	std::vector<Face> m_vectorFace;
};






extern const int g_nBoxEdge[12][2];
#endif