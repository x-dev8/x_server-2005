#pragma once
#include <vector>
#include "Engine.h"
#include "Me3d\Vector.h"
#include "Me3d\Quaternion.h"

enum
{
	eMex_HitAll,
	eMex_HitFloor,
};
enum
{
	eCloneMirrorXAxis = 1<<0,
	eCloneMirrorYAxis = 1<<1,
	eCloneMirrorZAxis = 1<<2,
};

enum
{
	eMex_SaveFlag_SaveAsXml = 1<<0,
	eMex_SaveFlag_BuildLightMapUV = 1<<1,
	eMex_SaveFlag_OnlyFirstFrame = 1<<2,
	eMex_SaveFlag_ConvertBoneMatrixToTranslationAndRotation = 1<<3,
};
enum
{
	eMex_LoadFlag_FastLoad	= 1<<0,
	eMex_LoadFlag_SnapShot	= 1<<1
};

#define MEX2_MAX_NAME 80

class IMex;
class IMexLayer
{
public:
	virtual void SetBlendMode( int nBlendMode ) = 0;
	virtual int GetBlendMode() = 0;
	virtual void SetFlag( DWORD dwFlag ) = 0;
	virtual DWORD GetFlag() = 0;
	virtual void SetTextureID( int nTextureID ) = 0;
	virtual int GetTextureID() = 0;
	virtual void SetAlpha( float fAlpha ) = 0;
	virtual float GetAlpha() = 0;
	virtual BOOL IsSameLayer( IMexLayer* pLayer ) = 0;
};
class IMexMaterial
{
public:
	virtual int GetLayerCount() = 0;
	virtual IMexLayer* GetLayer( int nLayer ) = 0;
	virtual IMexLayer* AddLayer() = 0;
	virtual BOOL IsSameMtl( IMexMaterial* pMtl , DWORD dwFlag ) = 0;
	virtual BOOL Prepare( IRenderer* pRenderer, IReplaceableTextureProj* pTextureProj, DWORD* pdwFlag, int* pnTextureID ) = 0;
};
class IMexMaterials
{
public:
	virtual int GetMtlCount() = 0;
	virtual IMexMaterial* GetMtl( int nMtl ) = 0;
};
class IMexBone
{
public:
	virtual ~IMexBone(){};

	virtual const char* GetName() = 0;
	virtual int	GetParentId() = 0;
	virtual int GetChildCount() = 0;
	virtual int GetChildId( int i ) = 0;
	virtual int GetFrameId() = 0;
	virtual int GetFrameCount() = 0;
	virtual float* GetMatrices( int nFrameId ) = 0;
	virtual float* GetMatricesFromKeyTime( float fKeyTime, int nFps, float* parentMat = NULL ) = 0;
	virtual float* GetBlendedMatrices( float t, float fKeyTime0, float fKeyTime1, int nFps, BOOL bIsLastBlend = FALSE, Vector* pLastBlendTrans = NULL, Quaternion* pLastBlendQuats = NULL ) = 0;
	virtual float GetRotation( float fKeyTime, int nFps ) = 0;
	virtual BOOL HasKeyFrame() = 0;
	virtual float* GetTransform() = 0;
	virtual float* GetFrame0Inv() = 0;
	virtual float* GetInv() = 0;
	virtual BOOL HasVisibleTrack() = 0;
	virtual BOOL IsVisible( int nFrameId ) = 0;
	virtual float GetVisibleFloat( int nFrameId ) = 0;
	
};
class IMexAttachment
{
public:
	virtual int GetAttachBoneID() = 0;
	virtual const char* GetName() = 0;
	virtual float* GetInitMatrix() = 0;
};
class IMexAttachments
{
public:
	virtual int GetNumAttachment() = 0;
	virtual IMexAttachment* GetAttachment( int nAttachment ) = 0;
	virtual IMexAttachment* FindAttachment( const char* pszName ) = 0;
	// add, jiayi, [2009.4.17]
	virtual IMexAttachment*	FindAttachment( const char* pszName, int nOffset ) = 0;

};
class IMexSkeleton
{
public:
	virtual ~IMexSkeleton(){};
	virtual int			GetBoneCount() = 0;
	virtual IMexBone*	GetBone( int i ) = 0;
	virtual int			GetRootBoneCount() = 0;
	virtual int			GetRootBoneId( int i ) = 0;
	virtual void		SetMex( IMex* pMex ) = 0;
	virtual IMex*		GetMex() = 0; 
	virtual BOOL		Read( void* p, int nSize, DWORD dwVersion ) = 0;
	virtual BOOL		IsSameFormat( IMexSkeleton* pSkeleton ) = 0;
	virtual int			FindBone( const char* pszBoneName ) = 0;
	virtual BOOL		SnapShotFromFile( FILE* fp, int nSize, DWORD dwFlag ) = 0;
};
class IMexGeometry
{
public:
	virtual int	GetChunkCount() = 0;
	virtual IRenderable* GetChunk( int nChunkId ) = 0;
	virtual IRenderable* FindChunkByName( const char* pszName ) = 0;
};
class IMexSequence
{
public:
	virtual const char* GetName() = 0;
	virtual int GetStartFrameID() = 0;
	virtual int GetEndFrameID() = 0;
	virtual BOOL IsLoopping() = 0;
};
class IMexSequences
{
public:
	virtual int GetSequenceCount() = 0;
	virtual IMexSequence* GetSequence( int i ) = 0;
};

class IMexBoneGroup
{
public:
	virtual int GetBoneCount() = 0;
	virtual int GetBoneID( int i ) = 0;
	virtual BOOL SetBoneID( int i, int nBoneID ) = 0;
	virtual int* GetBoneIDs() = 0;
	virtual float	GetBoneWeight( int i ) = 0;
};
class IMexBoneGroups
{
public:
	virtual int GetBoneGroupCount() = 0;
	virtual IMexBoneGroup* GetBoneGroup( int i ) = 0;
};

class IMexTexture
{
public:
	virtual void SetName( const char* pszName ) = 0;
	virtual const char* GetName() = 0;
};
class IMexTextures
{
public:
	virtual int GetTextureCount() = 0;
	virtual IMexTexture* GetTexture( int i ) = 0;
	virtual int GetRenderTextureCount() = 0;
	virtual int GetRenderTextureID( int i ) = 0;
	virtual void AddRenderTextureID( int nID ) = 0;
	virtual void ClearRenderTextureIDs() = 0;
	virtual IMexTexture* AddTexture() = 0;
};

class IMexLight
{
public:
	virtual void SetFlag( DWORD dwFlag ) = 0;
	virtual DWORD GetFlag() = 0;
	virtual void SetName( const char* pszName ) = 0;
	virtual const char* GetName() = 0;
	virtual void SetParentBoneID( int nParentBoneID ) = 0;
	virtual int GetParentBoneID() = 0;
	virtual void SetRange( float fRange ) = 0;
	virtual float GetRange() = 0;
	virtual void SetColor( float* pfColor ) = 0;
	virtual float* GetColor() = 0;
	virtual void SetIntense( float fIntense ) = 0;
	virtual float GetIntense() = 0;
	virtual void SetAttenuration( float* pfAtten ) = 0;
	virtual float* GetAttenuration() = 0;
	virtual void SetFrameCount( int nFrameCount ) = 0;
	virtual int GetFrameCount() = 0;
	virtual void SetColorTrack( float* pfColorTrack ) = 0;
	virtual float* GetColorTrack() = 0;
	virtual void SetLightID( int nLightID ) = 0;
	virtual int GetLightID() = 0;
	virtual void SetPivot( float* pfPivot ) = 0;
	virtual float* GetPivot() = 0;
	virtual void SetPos( float* pfPos ) = 0;
	virtual float* GetPos() = 0;

	virtual void Update( int nTime, float* pfMatrices, float* pfMatModel ) = 0;

	virtual IMexLight* Clone() = 0;
	virtual void Release() = 0;
};
class IMexLights
{
public:
	virtual int GetLightCount() = 0;
	virtual IMexLight* GetLight( int nLight ) = 0;
};

class IMexParticleEmitter
{
public:
	virtual ~IMexParticleEmitter(){}
	
	virtual void	Update( int nTime, float fScale, float* pfMatrices, float* pfmatModel,int nFrameId ) = 0;
	virtual void	Render( int nTime, short stTextureId, float fAlpha, bool bOverUI) = 0;
	virtual int		GetLocalTextureID() = 0;
	virtual void    SetLocalTextureID(int texid) = 0;
	virtual void	SetActive( BOOL bActive ) = 0;
	virtual IMexParticleEmitter* Clone() = 0;
	virtual void	Release() = 0;
	virtual const char* GetName() = 0;
	virtual const char* GetBindPartName() = 0;		// 有些是绑定在装备上面的，需要知道部位
	virtual void SetPlaySpeed( float fPlaySpeed ) = 0;
	// added, jiayi, [2010/7/6]
	virtual void	SetParentBoneID( int nBoneId ) = 0;
	virtual int		GetParentBoneID() = 0;
	virtual void	SetSrcMex( IMex* pMex ) = 0;
};
class IMexParticleEmitters
{
public:
	virtual int		GetEmitterCount() = 0;
	virtual IMexParticleEmitter* GetEmitter( int i ) = 0;
	virtual void   AppendEmitter(IMexParticleEmitter *e) = 0;
};
class IMexRibbonEmitter
{
public:
	
	virtual void	Update( int nTime, int nFrameID, float* pfMatrices, float* pfmatModel, BOOL bSmooth = FALSE ) = 0;
	virtual void	Render( float* pfMatrix, short stTextureId, float fAlpha, BOOL bInterp, bool bOverUI ) = 0;
	virtual int		GetParentBoneID() = 0;
	virtual IMexRibbonEmitter* Clone() = 0;
	virtual int		GetLocalTextureID() = 0;
	virtual void	Release() = 0;
	virtual const char* GetName() = 0;
	virtual const char* GetBindPartName() = 0;		// 有些是绑定在装备上面的，需要知道部位
	virtual void	GetPoint( float* pfPoint ) = 0;
	virtual void	Clear() = 0;
	virtual void	Reset() = 0;
};
class IMexRibbonEmitters
{
public:
	virtual int		GetEmitterCount() = 0;
	virtual IMexRibbonEmitter* GetEmitter( int i ) = 0;
};
class Vector;
class MexReplaceableTextureProj;
class IMex
{
public:
	IMex(){ m_bDestroying = FALSE; }
	virtual ~IMex(){};
	virtual void SetKeepOldData( bool bKeepOldData ) = 0;
	virtual DWORD GetVersion() = 0;

	virtual IMexSequence* GetSequence() = 0;
	virtual IMexSkeleton* GetSkeleton() = 0;
	virtual IMexMaterials* GetMtls() = 0;
	virtual IMexGeometry* GetGeometry() = 0;
	virtual IMexBoneGroups* GetBoneGroups() = 0;
	virtual IMexTextures* GetTextures() = 0;
	//virtual IMexLights* GetLights() = 0;
	virtual IMexRibbonEmitters* GetRibbonEmitters() = 0;
	virtual IMexParticleEmitters* GetParticleEmitters() = 0;
	virtual IMexAttachments* GetAttachments() = 0;
	virtual const char* GetFilename() = 0;

	virtual BOOL LoadFromFile( const char* pszFilename, DWORD dwFlag, bool bKeepCloneMemory = true ) = 0;
	virtual BOOL SaveToFile( const char* pszFilename, DWORD dwFlag ) = 0;

	virtual BOOL CreateParticleEmitters() = 0;
	virtual void DestroyParticleEmitters() = 0;

	virtual BOOL IsBoneVisible( int nFrameId, int nBoneId ) = 0;
	//virtual BOOL RegisterTextures() = 0;
	//virtual void UnRegisterTextures() = 0;
	//virtual BOOL HasTextureLoaded() = 0;
// 	virtual BOOL Intersect( float* pvStart, float* pvDir, float* pvHit, DWORD dwFlag ) = 0;
	virtual bool IntersectQuick( Vector* pvStart, Vector* pvDir, MexReplaceableTextureProj* replaceableTexture, D3DXMATRIX* pModelInverseMatrix ) = 0;
	virtual BOOL HasMtl() = 0;
// 	virtual void SetFrameId( int nFrameId ) = 0;
// 	virtual int	 GetFrameId() = 0;

	

	virtual int	GetVertexCount() = 0;
	virtual int	GetFaceCount() = 0;

	virtual void Release() = 0;
	virtual IMex*	Clone( DWORD dwFlag ) = 0;

	virtual void						OnDeviceLost() = 0;
	virtual void						OnDeviceReset( ) = 0;
	BOOL IsDestroying(){ return m_bDestroying; }		//是否在被删除中
	void FlagDestroying(){ m_bDestroying = FALSE; }		//标志删除中

protected:
	BOOL				m_bDestroying;
};