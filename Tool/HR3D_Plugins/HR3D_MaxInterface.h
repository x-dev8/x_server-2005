#ifndef _hr3d_maxinterface_h
#define _hr3d_maxinterface_h

#include <windows.h>

#include "max.h"
#include "stdmat.h"

#include <vector>

#include "defines.h"

class HR3D_Vector;
class HR3D_Quaternion;

class HR3D_MaxInterface
{
public:
	struct ColorTrack
	{
		int bTiling;		// 是否有tile;
		int nUTile, nVTile;	// u,v块数
		int nStartFrame;	// 开始帧编号
		float fPlaybackRate;	// 每多少帧次更新一次
		DWORD nLastTime;	// 最近一次刷新时间
		int nLastFrameId;	// 上次刷新帧数id

		std::vector<HR3D_Mdx2ColorKey> vectorColorKey;
		ColorTrack()
		{
			bTiling = FALSE;
			nUTile = 1;
			nVTile = 1;
			nStartFrame = 0;
			fPlaybackRate = 50;
		}
	};

	typedef struct 
	{
		std::vector<HR3D_Matrix> vectorMatrix;
		std::vector<float> vectorVisibleFloat;
		std::vector<BOOL> vectorVisibleBool;
		std::vector<HR3D_Vector> vectorTrans;
		std::vector<HR3D_Quaternion> vectorRot;
		BOOL bMirror;
	} Track;
	struct Keyframe
	{
		float fTime;
		float fValue[4];
	};
	struct Anim
	{
		std::vector<Keyframe> KeyFrames;;
	};
	struct TexInfo
	{
		float fUTile, fVTile;
	};
	// realrender added 2003.08.24
	struct Influence
	{
		int nBoneId;
		char szBoneName[64];
		float fWeight;
		Influence()
		{
			nBoneId = -1;
			szBoneName[0] = 0;
			fWeight = 0.0f;
		}
	};
	struct BoneGroup
	{
		std::vector<Influence> vectorInfl;
		void AddInfluence( Influence& infl )
		{
			for( int i = 0; i < vectorInfl.size(); i++ )
			{
				if( strcmp( vectorInfl[i].szBoneName, infl.szBoneName ) == 0 )
				{
					vectorInfl[i].fWeight += infl.fWeight;
					return;
				}
			}
			vectorInfl.push_back( infl );
		}
	};
	// realrender added 2003.08.29
	typedef struct 
	{
		int nVertexId;
		Point3 pos;
		Point3 normal;
		float u, v;
	} SplitVertex;
	// misc
protected:
	static DWORD WINAPI ProgressFunction(LPVOID arg);
	
	// member variables
protected:
	ExpInterface *m_pExpInterface;
	Interface *m_pInterface;
	
	// constructors/destructor
public:
	HR3D_MaxInterface();
	virtual ~HR3D_MaxInterface();
	// member functions
public:
	bool Create(ExpInterface *pExpInterface, Interface *pInterface);
	int GetCurrentFrame();
	float GetCurrentTime();
	int GetEndFrame();
	int GetFps();
	//CWnd *GetMainWnd();
	//CBaseMaterial *GetMaterial(int materialId);
	int GetMaterialCount();
	Mesh *GetMesh(INode *pNode);
	INode *GetNode(const std::string& strName);
	INode *GetRootNode();
	Modifier* FindPhysiqueModifier(INode *pINode);
	Modifier* FindVertexModifier(INode *pINode);
	// realrender added 2002.11.26 for lod
	Modifier* FindModifier( INode* pINode, Class_ID id );
	int GetSelectedNodeCount();
	int GetStartFrame();
	int GetStartTick();
	int GetEndTick();
	int GetTickPerFrame();
	int GetFrameCount();
	//void GetTranslationAndRotation(INode *pNode, INode *pParentNode, float time, CalVector& translation, CalQuaternion& rotation);
	//void GetTranslationAndRotationBoneSpace(INode *pNode, float time, CalVector& translation, CalQuaternion& rotation);
	bool IsBone(INode *pNode);
	bool IsBipedBone(INode *pNode);
	BOOL IsRenderable(INode *pNode);
	
	bool IsDummy(INode *pNode);
	bool IsMesh(INode *pNode);
	bool IsShape( INode* pNode );
	
	// realrender added 2004.08.06
	bool IsLightObject(INode* pNode );
	
	bool IsTarget(INode *pNode);
	bool IsSelected(INode *pNode);
	void SetProgressInfo(int percentage);
	void StartProgressInfo(const std::string& strText);
	void StopProgressInfo();
	// realrender added 2002.10.27 for light track export
	Matrix3 GetRelativeTransform( INode* src, INode* dst );
	// realrender added 2002.11.18 for select node
	INode* GetSelectedNode();
	// realrender added 2002.12.06 for select node by id
	INode* GetSelectedNode( int nNodeId );
	void GetTranslationAndRotation(INode *pNode, INode *pParentNode, float time, HR3D_Vector& translation, HR3D_Quaternion& rotation );
	void GetTranslationAndRotationBoneSpace(INode *pNode, float time, HR3D_Vector& translation, HR3D_Quaternion& rotation );
	
	char* GetMapname( StdMat* pStdMtl );
	Point3 GetVertexNormal( Mesh* pMesh, int faceId, int vertexId );

	// realrender added 2003.05.26
	void ClearNodeTree(){ m_vectorNode.clear(); }
	void GetNodeTree( INode* pNode );
	int GetNodeCount(){ return m_vectorNode.size(); }
	INode* GetNode( int i ){ return m_vectorNode[i]; }
	// realrender added 2003.08.26
	void GetTrack( INode* pNode, Track& track, BOOL bOnlyFirstFrame = FALSE );
	// realrender added 2004.05.19
	void GetTracks( int nNodeCount, INode** pNodes, Track** tracks, BOOL bOnlyFirstFrame = FALSE );

	// realrender added 2003.05.31
	bool GetSubtexmap( INode* pNode, DWORD dwChannel, char szMapname[], TexInfo* pTexInfo );
	// realrender added 2003.06.01
	ViewExp* GetActiveViewPort(){ return m_pInterface->GetActiveViewport(); }
	HR3D_Matrix ConverteMatrix3( Matrix3& mat );
	// realrender added 2003.06.03
	//bool GetTrack( INode* pNode, HR3D_Mdx::Track& track );
	// realrender added 2003.08.24
	void GetBoneGroup( Modifier *pModifier,
						int nModifierType, 
						INode* pNode, 
						Mesh* pMesh,
						int nVertexId, 
						HR3D_MaxInterface::BoneGroup& boneGroup );
	// realrender added 2003.08.29
	BOOL SplitMeshVertices( INode* pMesh, 
							std::vector<SplitVertex>& vectorSplitVertex, 
							Matrix3* pMatrix = NULL );
	// realrender added 2003.09.04
	int GetTime(){ return m_pInterface->GetTime(); }
	// realrender added 2003.10.07
	Interface* GetRealMaxInterface(){ return m_pInterface; }
	// realrender added 2003.12.09
	bool GetMtlAnim( StdMat* pStdMtl, ColorTrack& track );
	// realrender added 2004.08.06
	bool GetLightColorTrack( INode* pNode, ColorTrack& track );

	BOOL GetStdMtlChannelBitmapFileName( StdMat* pStdMat, int nChannel, char szFileName[] );
	BOOL ConvertBoneName();
	void	GetAnim( INode* pNode, Anim* pAnim );
protected:
	Matrix3 GetNodeTM(INode *pNode, float time);

	// realrender added 2003.05.26
	std::vector<INode*> m_vectorNode;

	

};
HR3D_MaxInterface* GetMaxIP();
#endif