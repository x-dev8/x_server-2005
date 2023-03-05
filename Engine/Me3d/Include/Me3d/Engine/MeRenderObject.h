#pragma once

#include <MeFoundation/MeSmartPointer.h>
#include <MeFoundation/MeDynamicAllocBuffer.h>
#include "Me3d/Engine/Renderable.h"

/** ��Ⱦ��Ԫ
@desc:
	����Ⱦǰ�������ṹ��Ȼ�����������������һ����Ⱦ��
	��������ṩ��ͨ����Ⱦ�����еı�����
*/
MeSmartPointer( MeRenderObject );
class MeRenderObject : public MeRefObject
{
public:
	/// ��Ⱦ��Ԫ������
	enum ERenderObjectType
	{
		EROT_MODEL,			// ��ͨģ��
		EROT_PARTICLERIBBON,// ���ӣ�����
		EROT_SKELETON,		// ���������� 
		EROT_BILLBOARD,			// ��Ƭģ��
		EROT_COUNT
	};

protected:
	ERenderObjectType m_eType;

	/** ����key
	@desc�� ����ͼid��shaderid��flag����Ϣѹ����һ��64λ��
			�����У�Ȼ����ݴ����ݴ�С��������Ŀǰ��������
			���ţ�
			��16λ����ͼid
			��32λ��flag
			��1λ����͸flag
			��15λ������
			������С�������к󣬰�͸������ͻ��ŵ������ơ�
		*/
	unsigned __int64 m_ui64Key;

	std::string m_szInfo;

	// �Ѿ�����ӹ�
	bool m_bAdded;

protected:
	float m_fAlpha;					//alphaֵ
	short m_stUseTexId;				// ��ͼid
	int m_nAddMapId;				// ��ͼid
	int	m_nLightmapTexId;			// lightmap texture id
	int m_nShaderId;				// shader id
	DWORD m_dwFvf;					// fvf
	int m_nVertexCount;				// ��������
	BYTE* m_pkVB;					// vertex buff
	BYTE*	m_pkIB;					// index buff
	int m_nFaceCount;				// ����
	DWORD m_dwFlag;					// ��Ⱦ��flag�������ܶ���Ⱦ״̬
	short m_stUseLuminanceTexId;	// �߹�
	Vector2 m_vLightmapUVScale;		// lightmap uv scale
	Vector2 m_vLightmapUVOffset;	// lightmap uv offset

protected:
	//add by yanli  2010-8-20
	
	static MeDynamicAllocBuffer< DWORD, 1024 * 20 > ms_kDyBuffer;
	/*static DWORD* m_pAlphaValue;*/
	//const static UINT nBuffSize = 1024 * 20;
	//static DWORD stBuffer[nBuffSize];

public:
	void SetAlpha( float fAlpha ){ m_fAlpha = fAlpha; }
	float GetAlpha() const { return m_fAlpha; }

	bool GetAdded() const { return m_bAdded; }
	void SetAdded( bool bAdded) { m_bAdded = bAdded; }

	void SetUseTexId( short stId ){ m_stUseTexId = stId; }
	short GetUseTexId() const { return m_stUseTexId; }

	void SetAddMapId( int nId ){ m_nAddMapId = nId; }
	int GetAddMapId() const { return m_nAddMapId; }

	void SetLightmapTexId( int nTexId ){ m_nLightmapTexId = nTexId; }
	int GetLightmapTexId() const { return m_nLightmapTexId; }

	void SetShaderId( int nId ){ m_nShaderId = nId; }
	int GetShaderId() const { return m_nShaderId; }

	void SetFVF( DWORD dwFvf ){ m_dwFvf = dwFvf; }
	DWORD GetFVF() const { return m_dwFvf; }

	void SetVertexCount( int nCount ){ m_nVertexCount = nCount;}
	int GetVertexCount() const { return m_nVertexCount; }

	void SetVB( LPDIRECT3DVERTEXBUFFER9 pkVB ){ m_pkVB = (BYTE*)pkVB; }
	void SetVB( BYTE* pkVB ){ m_pkVB = pkVB; }
	BYTE* GetVB() const { return m_pkVB; }

	void SetIB( LPDIRECT3DINDEXBUFFER9 pkIB ){ m_pkIB = (BYTE*)pkIB; }
	void SetIB( BYTE* pkIB ){ m_pkIB = pkIB; }
	BYTE* GetIB() const { return m_pkIB; }

	void SetFaceCount( int nCount ){ m_nFaceCount = nCount; }
	int GetFaceCount() const { return m_nFaceCount; }

	void SetFlag( DWORD dwFlag ){ m_dwFlag = dwFlag; }
	DWORD GetFlag() const { return m_dwFlag; }

	void SetUseLuminanceTexId( short stId ){ m_stUseLuminanceTexId = stId; }
	short GetUseLuminanceTexId() const { return m_stUseLuminanceTexId; }	

	void SetLightmapUVScale( const Vector2& vUVScale ){ m_vLightmapUVScale = vUVScale; }
	const Vector2& GetLightmapUVScale() const { return m_vLightmapUVScale; }

	void SetLightmapUVOffset( const Vector2& vUVOffset ){ m_vLightmapUVOffset = vUVOffset; }
	const Vector2& GetLightmapUVOffset() const { return m_vLightmapUVOffset; }

public:
	/// ctor
	MeRenderObject() : m_fAlpha( 0 ), m_stUseTexId( -1 ), m_nAddMapId( -1 ), m_bAdded( false ),
		m_nShaderId( -1 ), m_dwFvf( 0 ), m_nVertexCount( 0 ),
		m_pkVB( 0 ), m_pkIB( 0 ), m_nFaceCount( 0 ), m_dwFlag( 0 ), 
		m_stUseLuminanceTexId( -1 ), m_ui64Key( 0 ),m_eType( EROT_COUNT ), m_nLightmapTexId(-1)
	{}

	/// get type
	unsigned int GetType() const { return m_eType; }

	/// generate key
	void GenerateKey();
	unsigned __int64 GetKey() const{ return m_ui64Key; }

	void SetInfo(const char *mex, const char *name) { m_szInfo = std::string(mex) + std::string("___") + std::string(name); }

	/// render
	virtual bool BeginRender(){ return true; }
	virtual void DoRender() = 0;
	virtual void EndRender(){};
};

/** ģ�������Ⱦ����
@desc:
	��������������ֻ��û�й������������������һ��
*/
MeSmartPointer( MeModelRenderObject );
class MeModelRenderObject : public MeRenderObject
{
protected:	
	BYTE* m_pkNB;			// normal buff
	BYTE* m_pkDB;			// diffuse buff
	BYTE* m_pkUVB;			// uv buff	
	BYTE* m_pkUVB2;			// uv2 buff	
public:
	void SetNB( BYTE* pkNB ){ m_pkNB = pkNB; }
	void SetNB( LPDIRECT3DVERTEXBUFFER9 pkNB ){ m_pkNB = (BYTE*)pkNB; }
	BYTE* GetNB() const { return m_pkNB; }

	void SetDB( BYTE* pkDB ){ m_pkDB = pkDB; }
	void SetDB( LPDIRECT3DVERTEXBUFFER9 pkDB ){ m_pkDB = (BYTE*)pkDB; }
	BYTE* GetDB() const { return m_pkDB; }

	void SetUVB( BYTE* pkUVB ){ m_pkUVB = pkUVB; }
	void SetUVB( LPDIRECT3DVERTEXBUFFER9 pkUVB ){ m_pkUVB = (BYTE*)pkUVB; }
	BYTE* GetUVB() const { return m_pkUVB; }	

	void SetUVB2( BYTE* pkUVB2 ){ m_pkUVB2 = pkUVB2; }
	void SetUVB2( LPDIRECT3DVERTEXBUFFER9 pkUVB2 ){ m_pkUVB2 = (BYTE*)pkUVB2; }
	BYTE* GetUVB2() const { return m_pkUVB2; }

	//add by yanli 
	void InsertAlphaToVertex(float fAlpha);
	void RestoreAlphaToVertex(float fAlpha); 
	void StoreAlphaToMemory(float fAlpha);
public:
	/// ctor
	MeModelRenderObject() : MeRenderObject(), 
		m_pkNB( 0 ), m_pkDB( 0 ), m_pkUVB( 0 )
	{ 
	m_eType = EROT_MODEL; 
	}


public:	
	virtual bool BeginRender();
	/*virtual */void DoRender();
	virtual void EndRender();;
};

class MeBillboardRenderObject : public MeModelRenderObject
{
public:
	MeBillboardRenderObject():MeModelRenderObject()
	{
		m_eType = EROT_BILLBOARD;
	}
};


/** ���Ӻ����������Ⱦ����
@desc:
	���Ӻ���������Ⱦ���󣬶���һ��stride
*/
MeSmartPointer( MeParticleRibbonRenderObject );
class MeParticleRibbonRenderObject : public MeRenderObject
{
protected:
	unsigned int m_uiStride;
	float m_fAlpha;
	bool m_bOverUI;

public:
	void SetStride( unsigned int uiStride ){ m_uiStride = uiStride; }
	unsigned int GetStride() const { return m_uiStride; }

	void SetAlpha( float fAlpha ){ m_fAlpha = fAlpha; }
	float GetAlpha() const { return m_fAlpha; }

	void SetOverUI( bool bOver ){ m_bOverUI = bOver; }
	bool GetOverUI() const { return m_bOverUI; }

public:
	/// ctor
	MeParticleRibbonRenderObject() : MeRenderObject(),
		m_uiStride( 0 )
	{ m_eType = EROT_PARTICLERIBBON; }

public:
	virtual bool BeginRender();
	/*virtual */void DoRender();
	virtual void EndRender();;

};

/** ��������������Ⱦ����
@desc:
	���npc���ֵȡ�����
*/
MeSmartPointer( MeSkeletonRenderObject );
class MeSkeletonRenderObject : public MeModelRenderObject
{
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pkBoneWeightIdxBuff;
	bool	m_bChangeColor;
	DWORD	m_dwOldColor;
	D3DXMATRIXA16* m_pBoneWorldMatrix;
	unsigned int m_uiBoneMatrixCount; 	

public:	
	void SetBoneWeightIdxBuff( LPDIRECT3DVERTEXBUFFER9 pkBuff ){ m_pkBoneWeightIdxBuff = pkBuff; }
	LPDIRECT3DVERTEXBUFFER9 GetBoneWeightIdxBuff() const { return m_pkBoneWeightIdxBuff; }

	void SetChangeColor( bool bChangeColor ){ m_bChangeColor = bChangeColor; }
	bool GetChangeColor() const { return m_bChangeColor; }

	void SetOldColor( DWORD dwColor ){ m_dwOldColor = dwColor; }
	DWORD GetOldColor() const { return m_dwOldColor; }

	void SetBoneWorldMatrix( D3DXMATRIXA16* pkMat ){ m_pBoneWorldMatrix = pkMat; }
	D3DXMATRIXA16* GetBoneWorldMatrix() const { return m_pBoneWorldMatrix; }

	void SetBoneMatrixCount( unsigned int uiCount ){ m_uiBoneMatrixCount = uiCount; }
	unsigned int GetBoneMatrixCount() const { return m_uiBoneMatrixCount; }

public:
	MeSkeletonRenderObject() : MeModelRenderObject(),
		m_pkBoneWeightIdxBuff( 0 ), m_bChangeColor( false ), 
		m_dwOldColor( 0 ), m_pBoneWorldMatrix( 0 ),
		m_uiBoneMatrixCount( 0 )
	{ m_eType = EROT_SKELETON; }

public:
	virtual bool BeginRender();
	/*virtual */void DoRender();
	virtual void EndRender();;

};

//////////////////////////////////////////////////////////////////////////
class SortRenderable
{
public:
	enum ECollectibleType
	{
		eCT_Shimmer,
		eCT_AlphaBlend,
		eCT_Count
	};
public:
	SortRenderable() : m_dwCollectibleType(eCT_Count),m_nCurrPostIndex(0){}
	virtual ~SortRenderable(){ m_spRenderObject = NULL; }
	// added, jiayi, [2010/5/13]
	/// ������������Ⱦ����������󣬵����������������Ⱦ��
	virtual void DoRender( bool bPost = false ){ 
		if( m_spRenderObject )
			m_spRenderObject->DoRender(); 
		ClearOtherInfo();
	}

	virtual DWORD GetCollectibleType() const{ 
		return m_dwCollectibleType;
	}

	virtual void SetCollectibleType( DWORD dwType ){
		if( m_dwCollectibleType != eCT_Shimmer )
			m_dwCollectibleType = dwType;
	}

	// added, jiayi, [2010/6/9]
	// ��������key
	virtual unsigned __int64 GetSortKey() const
	{ if( !m_spRenderObject ) return 0; return m_spRenderObject->GetKey(); }

	MeRenderObjectPtr GetRenderObject() const { return m_spRenderObject; }

	bool			IsEffect() { if(!m_spRenderObject) return false; return m_spRenderObject->GetType() == MeRenderObject::EROT_PARTICLERIBBON;}
	bool			IsBillborad() {if(!m_spRenderObject) return false; return m_spRenderObject->GetType() == MeRenderObject::EROT_BILLBOARD;}

	virtual int		GetTotalVerticesCount(bool bPost) = 0;
	virtual int		GetTotalFacesCount(bool bPost) = 0;
	virtual float			GetDisToCameraEye(float* pMatrices) = 0;
protected:
	// ����һЩ������Ⱦ���� jiayi, [2010/6/9]
	MeRenderObjectPtr m_spRenderObject;
	DWORD m_dwCollectibleType;
	RenderParams::OtherInfos	m_kOtherInfos;
	RenderParams::OtherInfos	m_kPostInfos; // �������ڴ���(alpha,shimmer,etc.)
	int							m_nCurrPostIndex;
public:
	void PushOtherInfo(  RenderParams* cInfo, bool bPost = false );
	const RenderParams::OtherInfos& GetOtherInfos( bool bPost = false ) const { 
		if( bPost )
			return m_kPostInfos;
		return m_kOtherInfos; 
	}
	bool ClearOtherInfo( bool bPost = false, bool bForce = false ){ 
		if (bPost)
		{
			if ( m_nCurrPostIndex == GetOtherInfos( true ).size()
				|| bForce )
			{//���еĶ��Ѿ���������
				m_kPostInfos.clear();
				m_nCurrPostIndex = 0;
				return true;
			}
		}
		else
		{
			m_kOtherInfos.clear(); 
			return true;
		}
		return false;
	}
};