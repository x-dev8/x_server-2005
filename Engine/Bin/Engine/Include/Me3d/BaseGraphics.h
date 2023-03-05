#ifndef _basegraphics_h
#define _basegraphics_h

#include "Me3d/Me3d.h"
#include "MeRTLibs.h"
#include "Dxsdk/d3dx9.h"
#include "MeFoundation/MeAllocatedObject.h"

class Box;


class CBaseGraphics
{
public:
	CBaseGraphics();
	~CBaseGraphics();
	typedef struct
	{
		D3DXVECTOR4 p;
		DWORD color;
	} Vertex2D;
	typedef struct 
	{
		D3DXVECTOR3 p;
		DWORD color;
	} Vertex3D;
	typedef struct 
	{
		D3DXVECTOR4 p;
		DWORD color;
		float u, v;
	} UVVertex2D;
	typedef struct 
	{
		D3DXVECTOR4 p;
		DWORD color;
		float u, v;
		float u1, v1;
	} UV2Vertex2D;

	class CRenderGroup
	{
	public:
		CRenderGroup()
			:nTex(-1),
			dwRenderFlag(0),
			nUseVertex(0),
			nUseIndex(0)
		{

		}
		~CRenderGroup();

		INT		nTex;
		DWORD	dwRenderFlag;
		/*
		DWORD	dwShader;
		DWORD	dwFvf;
		*/
		INT		nUseVertex;
		INT		nUseIndex;
		
		UVVertex2D	Vertexs[1024];
		short		Indexs[1536];
	};
	
// 	static CRenderGroup	RenderGroup[50];
// 	static INT			s_nGroupIdx;
// 	void UnLock();
// 	void Lock();
public:
// 	static BOOL	m_bUseGroup;
//	CBaseGraphics():	m_pDevice(NULL){}
//	void	SetDevice( LPDIRECT3DDEVICE9 pDevice ){ m_pDevice = pDevice; }
	void	DrawLine3D( D3DXVECTOR3 v0, D3DXVECTOR3 v1, DWORD dwColor );
	void	DrawLine2D( int x0, int y0, int x1, int y1, DWORD dwColor );
	void	DrawRect2D( POINT pt0, POINT pt1, DWORD dwColor );
	static void	DrawRect2D( RECT& rect, DWORD dwColor );
	void	FillRect2D( POINT pt0, POINT pt1, DWORD dwColor );
	static void	FillRect2D( RECT& rect, DWORD dwColor );
	static void	FillRect2D( RECT& rect, DWORD col1, DWORD col2, DWORD col3, DWORD col4 );
	//void	FillCircle2D( int x, int y, float r, int nSegment, DWORD dwColor );
	void	DrawCircle2D( int x, int y, float r, int nSegment, DWORD dwColor );
	void	FillCircle2D( int x, int y, float r, int nSegment, DWORD dwColor );	//------- ÃÓ‘≤    (   at 2004-4-22)
	void	FillCircle3D( float x, float y, float z, float r, int nSegment, DWORD dwColor );
	void	DrawCircleFlat3D( float x, float y, float z, float r, int nSegment, DWORD dwColor );
	void	DrawCircle3D( float x, float y, float z, float r, int nSegment, DWORD dwColor );
	void	FillRing2D( float x, float y, float r0, float r1, int nSegment, DWORD dwColor, float t );
	void	DrawFlatModel(	BYTE* v, int nVertexCount, int nStride,
							short face[], int nFaceCount, 
							DWORD dwColor );
	void	FillTri( int x0, int y0, int x1, int y1, int x2, int y2, DWORD dwColor );
	void	FillTri( D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, DWORD dwColor );
	static void	DrawProgressRect( int x, int y, int size, int nDegree );
	void	DrawBox3D( D3DXVECTOR3 vMin, D3DXVECTOR3 vMax, DWORD dwColor );
	void	DrawBox3D( Box* pBox, DWORD dwColor );
	static void RenderTexture( void* pTex,
								LPRECT lpDestRect, 
								LPRECT lpSrcRect, 
								int nSrcWidth,
								int nSrcHeight,
								float z, 
								DWORD dwColor );
	static void	Blt( int nTextureId,
						LPRECT lpDestRect, 
						LPRECT lpSrcRect, 
						int nSrcWidth,
						int nSrcHeight,
						float z, 
						DWORD dwColor,
						DWORD dwFlag/*,
						FLOAT fRot = 0.0f */);
	static void	BltTexture( LPDIRECT3DTEXTURE9 pTexture,
		LPRECT lpDestRect, 
		LPRECT lpSrcRect, 
		int nSrcWidth,
		int nSrcHeight,
		float z, 
		DWORD dwColor,
		DWORD dwFlag/*,
					FLOAT fRot = 0.0f */);
	BOOL	Blt(	int nTextureId,
					LPRECT lpDestRect, 
					LPRECT lpSrcRect,
					LPRECT lpClipRect,
					int nSrcWidth,
					int nSrcHeight,
					float z, 
					DWORD dwColor,
					DWORD dwFlag,
					int nAlphaTexId = -1 );

	void    Blt2Tex( int nTextureId,
					 int nAlphaTexId,
					LPRECT lpDestRect, 
					LPRECT lpSrcRect, 
					int nSrcWidth,
					int nSrcHeight,
					float z, 
					DWORD dwColor,
					DWORD dwFlag );

	BOOL    BltEx( int nTextureId,
					LPRECT lpDestRect, 
					LPRECT lpSrcRect, 
					LPRECT lpClipRect,
					int nSrcWidth,
					int nSrcHeight,
					float z, 
					DWORD dwColor,
					DWORD dwFlag,
					FLOAT fDir );
	BOOL	BltNotTransparency(	int nTextureId,
		LPRECT lpDestRect, 
		LPRECT lpSrcRect,
		LPRECT lpClipRect,
		int nSrcWidth,
		int nSrcHeight,
		float z, 
		DWORD dwColor,
		DWORD dwFlag);
	bool GetSupportUIZoom() const { return m_bSupportUIZoom; }
	void SetSupportUIZoom(bool val) { m_bSupportUIZoom = val; }
	protected:
		bool m_bSupportUIZoom;
		//protected:
//	LPDIRECT3DDEVICE9 m_pDevice;

};
//extern CBaseGraphics g_drawer;
extern CBaseGraphics* GetDrawer(); 
#endif