#ifndef _bsp_h
#define _bsp_h
#include "Me3d.h"
#include "prim.h"
#include "Me3d/Engine/Frustum.h"
#include <vector>
class IMex;
class Vector;
#ifndef X_AXIS
	#define X_AXIS				1
#endif
#ifndef Y_AXIS
	#define Y_AXIS				2
#endif
#ifndef Z_AXIS
	#define Z_AXIS				3
#endif

#ifndef LEFT_NODE
	#define LEFT_NODE 0
#endif
#ifndef RIGHT_NODE
	#define RIGHT_NODE 1
#endif

class IRenderable;
class HugeModel;
class BspTree : public MeCommonAllocObj<BspTree>
{
public:
	struct Vertex
	{
		Vector p;
		//Vector n;
		//DWORD		dwColor;
		//D3DXVECTOR2 uv;
	} ;
	struct CommonVertex
	{
		D3DXVECTOR3 p;
		DWORD		dwColor;
		D3DXVECTOR3 uv;
	};
	struct Face
	{
		int nVertexId[3];
		int nChunkID;
		int nFaceIDInChunk;
		int nMtlID;
		//bool bAdded;
		Face():
		nChunkID(-1),
			nFaceIDInChunk(-1),
			nMtlID(-1)
		{
			nVertexId[0] = 0;
			nVertexId[1] = 0;
			nVertexId[2] = 0;
		}	
	};

	struct SIntersect
	{
		int nFaceId;
		float u, v, t;
		Vector pos;
		Vector vNormal;
		Vector vFacePos[3];
	};

	struct BspNode : public MeCommonAllocObj<BspNode>
	{
		BspNode* pLeftNode;
		BspNode* pRightNode;
		int nAxis;
		float fSplit;
		Vector vMax;
		Vector vMin;
		Vector vCenter;
		std::vector<int> vectorFaceId;
		int nDepth;
		BOOL bBBoxHasBuilded;
		Box bbox;
		BspNode():
			pLeftNode(NULL),
			pRightNode(NULL),
			nAxis(0),
			fSplit(0.0f),
			nDepth(0),
			bBBoxHasBuilded(FALSE)
		{};
		void TryBuildAABB();
	} ;
public:
	std::vector<Vertex> m_vectorVertex;
	std::vector<Face>	m_vectorFace;
	std::vector<BOOL>	m_vectorFaceFlag;

	BspNode*			m_pRootNode;
	int					m_nMaxDepth;
	int					m_nMinNodeLeafCount;
	float				m_fMinLeftSize;
	IMex*				m_pMex;

	int*				m_pRenderFaceIDs;

	BspNode*			m_pBspNodePool;
	int					m_nBspNodePoolSize;

	int					m_nNumRenderFace;
public:
	BspTree();
	virtual ~BspTree();
	bool Create();
	void Destroy();
	BOOL CreateFromMex2( const char* pszFilename );
	BOOL CreateFromMex2( IMex* pMex );
	//
	int	AllocBspNode();
	void FreeBspNode( int nNodeID );
	//   added 2005.08.23
	BOOL AddMesh( float* pVertices, int nVertexCount, short* pFaces, int nFaceCount );
	BOOL AddRenderable( IRenderable* pRenderable );
	BOOL CreateTree2();
	BOOL IsIntersects( BspNode* node, Vector& pos, Vector& dir );
	void RenderBBox( BspNode* node, DWORD dwColor );
	void SetMinLeafSize( float fSize ){ m_fMinLeftSize = fSize; }

	bool CreateTree( Vertex* pVertexBuffer, int nVertexCount, short* pFaceBuffer, int nFaceCount );
	void DeleteNode( BspNode** ppNode );
	void ClearNode( BspNode* pNode );
	bool CopyFace( Face* pFaceDst, Face* pFaceSrc );

	void GetAABB( std::list<int>& listFaceId, Vector& vMin, Vector& vMax );
	void GetAABB( std::vector<int>& vectorFaceId, Vector& vMin, Vector& vMax );
	void SplitFace( int nFaceId, float fSplit, int nAxis, int* pLeftCount, int* pRightCount, int* pBothCount );
	void SplitSpace( BspNode* pRootNode, int nDepth, int nAxis );

	int GetFace( BspNode* pNode, short* pIndexBuffer );
	void GetMaxDepth( BspNode* pNode, int* pDepth );
	BspNode* GetRootNode(){ return m_pRootNode; }
	int MakeVisibleList( Frustum* pFrustumEx, D3DXVECTOR3 vPos, float fOutOfRangeDistance  );
	void CullFace2( 
		Frustum* frustum, 
		BspNode* pNode, 
		D3DXVECTOR3& vPos,
		float	fOutOfRangeDistance,
		int nFaceIds[], 
		int* pnFaceCount  );

	bool SaveToFile( const char* pszFilename );
	bool LoadFromFile( const char* pszFilename );

	std::vector<Vertex>& GetVectorVertex(){ return m_vectorVertex; }
	std::vector<Face>& GetVectorFace(){ return m_vectorFace; }

	//short GetTextureMapId( int nMapId ){ return m_vectorTextureMapId[nMapId]; }

	void Render();
	int Render( BspNode* node );
	
	int GetIntersects( BspNode* node, Vector& pos, Vector& dir, SIntersect* pIntersects, BOOL bNormal = FALSE, BOOL bPickFirst = FALSE );
	bool GetIntersectsQuick(BspNode* node, Vector& pos, Vector& dir, BOOL bNormal = FALSE );
	SIntersect* GetNearestIntersect( Vector& vPos, Vector& vDir, BOOL bNormal = FALSE, BOOL bPickFirst = FALSE );	// bPickFirst代表是否pick第一个就返回还是pick所有

	int GetCameraIntersects( BspNode* node, Vector& pos, Vector& dir, SIntersect* pIntersects );
	SIntersect* GetCameraNearestIntersect( Vector& vPos, Vector& vDir );

	SIntersect*	GetNearestIntersectCmpZ( Vector& vPos, Vector& vDir, BOOL bNormal, float fCurrZ );

	void CameraCorrect( Vector& vPos, Vector& vDir );
	int CameraCorrect( BspNode* node, Vector& pos, Vector& dir );//, SIntersect* pIntersects );


	// bsp按照自身的数据存，但是会在将来应用到游戏中的时候，带有平移和缩放，没有旋转
	// 在地图编辑器中，放置好hugemodel之后，
	// 下次拿出来的时候，有可能会进行平和和缩放
	BOOL Transform( float x, float y, float z, float fScale, BspNode* pNode );
};


//class C

#endif