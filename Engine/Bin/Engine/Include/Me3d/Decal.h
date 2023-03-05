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
		Vector2 p;	// ��������
		int idx;	// �����α߱��
		float t;	// ������������αߵĲ���t
		float s;	// ���������������ڲ�ʱ��һ����Ҫ�������ε�����������������t����ʹ�ã�
		float u, v;	// ������Ծ��ε�uv���꣬��ͼʹ��
	} Its;

	typedef struct 
	{
		Vector p;
		unsigned long color;
		float u, v;
	} Vertex;

private:
	static short m_nFaceIndex[10*1024*3];	// һ���㹻���������

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