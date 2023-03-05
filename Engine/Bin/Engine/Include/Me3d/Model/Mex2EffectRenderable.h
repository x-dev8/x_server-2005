#ifndef _mex2_EffectRenderable_h
#define _mex2_EffectRenderable_h

#include "Me3d/Me3d.h"
#include "Me3d/Model/MexSkinMesh.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/Renderable.h"
#include "Mutex.h"
#include "Me3d/Model/MexConfig.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Model/MexGeoChunk.h"

enum ECKFMex2ParticleEmitterFlag
{
	MEX2_PARTICLE_EMITTER_SQUIRT		=	1<<13,
	MEX2_PARTICLE_EMITTER_LINEEMITTER	=	1<<14,
	MEX2_PARTICLE_EMITTER_HEAD			=	1<<15,
	MEX2_PARTICLE_EMITTER_TAIL			=	1<<16,
	MEX2_PARTICLE_EMITTER_BOTH			=	1<<17,
	MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE	=	1<<18,
	MEX2_PARTICLE_EMITTER_XYQUAD		=	1<<19,
	MEX2_PARTICLE_EMITTER_LOCKEMITTER	=	1<<20,
	MEX2_PARTICLE_EMITTER_TANGENT		=	1<<21,

};

// mex2 ���������� added 2003.10.06
#define MEX2_MAX_RIBBON_EDGE 64 //32 //����Բ���޸ĺ���β̫�̣��ĳ�64

/*
 * 2012.7.2 wangshuai
 * ʹ��dwBlendMode
 */
struct Mex2RibbonEmitterSetting
{
	Vector vLines[2];
	char szParentBonename[MEX2_MAX_NAME];
	int nParentBoneId;
	int nTextureId;
	DWORD dwEdgePerSec;
	DWORD dwEdgeLifeSec;
	DWORD dwVertexAlpha;
	DWORD dwBlendMode;
};

struct Mex2RibbonEdge
{
	DWORD dwBornTime;
	BOOL bStart;
	DWORD dwStartTime;
	DWORD dwLife;
	float fU;			// fF��dwLife֮�ڴ�0��Ϊ1
	//float fTU;
	Vector vPoint[2];
	//DWORD dwLastChangeTUTime;
	Mex2RibbonEdge():		dwBornTime(0),
								bStart(FALSE),
								dwStartTime(0x7fffffff),
								dwLife(0),
								fU(0.0f)
								//fTU(0.0f),
								//vPoint( 0, 0, 0 ),
								//dwLastChangeTUTime(0){};
								{}

};

struct SEmitterVertex
{
	SEmitterVertex()
	{
		color = 0;
		u = 0;
		v = 0;
	}
	D3DXVECTOR3 p;
	unsigned long color;
	float u, v;
};

class CEffectRenderable:public SortRenderable
{
public:
	virtual void DoRender( bool bPost );
 	virtual bool DoRender( SEmitterVertex* pBuffer ) = 0;
	virtual float			GetDisToCameraEye(float* pMatrices) ;
protected:
	D3DXVECTOR3		m_vCenter;

};

class	Mex2RibbonEmitter:public IMexRibbonEmitter, public MeCommonAllocObj<Mex2RibbonEmitter>, public CEffectRenderable
{
	friend Mex2;
public:
 	virtual bool DoRender( SEmitterVertex* pBuffer );

public:
	Mex2RibbonEmitter():	
        pSetting(NULL),
		nEdgeCount(0),
        nMaxEdgeCount(0),
        nLastFrameID(-1),
        pParentMex(NULL),
        pParentBone(NULL),
		dwLastGenEdgeTime(0),
		dwLastUpdateTime(0)
	{
		memset( m_szBindPartName, 0x00, MEX2_MAX_NAME );
		m_spRenderObject = MeNew MeParticleRibbonRenderObject;
	}
	virtual int GetTotalVerticesCount(bool bPost) {return (nEdgeCount-1)*4;}
	virtual int GetTotalFacesCount(bool bPost)  {return (nEdgeCount-1)*2;}

	BOOL	Read( Mex2Pointer inP, int nSize );
	BOOL	Bind( Mex2* pMex );

	//////////////////////////////////////////////////////////////////////////
	// �麯��
	const char* GetName(){ return ""; }
	const char* GetBindPartName(){ return m_szBindPartName; }
	void	Update( int nTime, int nFrameID, float* pfMatrices, float* pfmatModel, BOOL bSmooth = FALSE );
	void	Render( float* pfMatrix, short stTextureId, float fAlpha, BOOL bInterp, bool bOverUI );
	void	RenderNormal( float* pfMatrix, short stTextureID, float fAlpha );
	int		GetParentBoneID(){ return pSetting->nParentBoneId; }
	int		GetLocalTextureID(){ return pSetting->nTextureId; }
	void	GetPoint( float* pfPoint );
	IMexRibbonEmitter* Clone();
	void	Release(){ delete this; }
	void	Clear(){
		nEdgeCount = 0;
	}
	void	Reset()
	{
		vLastEdgePos = Vector::ZERO;
		qLastEdgeQuat = Quaternion(0,0,0,0);
	}
// 	static bool createBuffers();
// 	static void destroyBuffers();

private:	
// 	static LPDIRECT3DVERTEXBUFFER9 m_pVB;
// 	static LPDIRECT3DINDEXBUFFER9 m_pIB;
protected:

	Mex2RibbonEmitterSetting *pSetting;
	char	m_szBindPartName[MEX2_MAX_NAME];;
	int		nEdgeCount;
	int		nMaxEdgeCount;
	//Mex2RibbonEdge edgeHead;
	Mex2RibbonEdge edges[MEX2_MAX_RIBBON_EDGE];
	//Vector ControlPoints0[MEX2_MAX_RIBBON_EDGE];
	//Vector ControlPoints1[MEX2_MAX_RIBBON_EDGE];
	
	int				nLastFrameID;
	Mex2*		pParentMex;
	//Mex2Bone*	pParentBone;
	IMexBone*		pParentBone;
	//float	fUOffset, fVOffset;
	DWORD	dwLastGenEdgeTime;
	DWORD	dwLastUpdateTime;
	Quaternion qLastEdgeQuat;	// �����ߵ���ת
	Vector	vLastEdgePos;		// �����ߵ�λ��

	

	
	BOOL	IsEdgeDead( Mex2RibbonEdge* pEdge, int nTime );
	void	GenEdge( Mex2RibbonEdge* pEdge, int nTime, MeMatrix* pParentTransform );
	BOOL	AddNewEdge( Mex2RibbonEdge* pEdge );
	void	UpdateEdge( Mex2RibbonEdge* pEdge, int nTime, MeMatrix* pmatModel = NULL );
	
	void	MakeARenderEdge( Mex2RibbonEdge* pEdge, SEmitterVertex* vertex );


	//   added 2003.12.12
	//void	Render2(  );

};
struct Mex2RibbonEmitters:public IMexRibbonEmitters, public MeCommonAllocObj<Mex2RibbonEmitters>
{
	friend Mex2;
public:
	BOOL	Read( Mex2Pointer inP, int nSize );
	BOOL	Bind( Mex2* pMex );
	//////////////////////////////////////////////////////////////////////////
	// �麯��
	int		GetEmitterCount(){ return vectorRibbonEmitter.size(); }
	IMexRibbonEmitter* GetEmitter( int i ){ return &vectorRibbonEmitter[i]; }
protected:
	std::vector<Mex2RibbonEmitter> vectorRibbonEmitter;
	//void	Update( int nTime, MeMatrix* pmatModel );
	//void	Render();

};

struct Mex2Particle : public MeCommonAllocObj<Mex2Particle>
{
    DWORD   dwBornTime;         // ����ʱ��
    DWORD   dwLife;             // ����
    Vector  vBornPos;           // ����ʱ��λ��
    Vector  vPos;               // λ�ã������ģ������ϵ�ģ�
    Vector  vPosWorld;          // λ�ã�ģ������ϵ�����任�Ժ�Ľ��
    Vector  vDynamicPos;        // ��̬�˶�����
    float   fSpeed;             // ����
    Vector  vDir;               // �˶�����
    Vector  vDirWorld;
    float   fScale;             // ����
    float   fScaleRandomRate;   // ���ű�����ÿ�����Ӳ���ʱ�����һ�����ű�������Ϊ fScale ��ϵ��   added by zhuomeng.hu		[2/14/2011]
    DWORD   dwColor;
    int     nCellId;            // ��ͼcell���
    int     nCellOffset;        // ��ͼCellƫ�ƣ����Բ��������һ֡        added by zhuomeng.hu		[3/10/2011]
    int     nRepeatTimes;       // ��ͼ�����Ѿ�ѭ�����ŵĴ���
    DWORD   dwLastUpdateTime;   // �ϴθ���ʱ��
//  float   fLerpT;             // Slerp(a, b, t)�Ĳ���t������shader;
//  char    cSegmentColorIndex;
    float   fRanAngle;          // �漴����ת�Ƕ�		        added by ZhuoMeng.Hu        [8/5/2010]
    float   fTailLength;        // ����β�ĳ��ȸ�Ϊ�ɱ�ֵ       added by zhuomeng.hu		[2/18/2011]

};

struct Mex2ParticleEmitterSetting
{
	DWORD		dwFlag;
	char		szName[MEX2_MAX_NAME];	// 80 byte
	int			nParentBoneId;	// ��������˶�
	Vector	vPivot;		// ԭʼλ��

	// ������ѡ��
	int			nCount;			// ������Ŀ
	float		fSpeed;			// ���Ӵ���ʱ�ĳ�ʼ�ٶ�
	float		fVariation;		// speed�仯���
	float		fConeAngle;		// ����cone�ļн�
	float		fGravity;		// ����
	// ʱ��ѡ��
	float		fLifeSpan;		// ����
	float		fEmissionRate;	// ÿ���Ӵ���������Ŀ
	float		fWidth;			
	float		fHeight;		// ���������Ĵ�С
	// ��ͼѡ��
	DWORD		dwBlendMode;	// ���ģʽ
	int			nRow;
	int			nCol;			// ��ͼ���ʵ�������

	// ����ѡ��
	// head, tail˵��
	// head��һ�������ε�billboard
	// tile��һ��������billboard���������ӵ��˶����򣬳���=fTailLength
	DWORD		dwPart;
	float		fTailLength;	// ��β����
	float		fMiddleTime;	// ������middle key�����ʱ��

	int			nSegmentColor[3][3];	// start/middle/end, multiply������ɫ
	int			nAlpha[3];				// start/middle/end
	float		fParticleScaling[3];	// start/middle/end
	DWORD		dwUVAnimFps;			// uv�����Ĳ�������
	DWORD		dwLifeSpanHeadUVAnim[3];	// start/middle/end
	DWORD		dwDecayHeadUVAnim[3];		// start/middle/end
	DWORD		dwLifeSpanTailUVAnim[3];		// start/middle/end
	DWORD		dwDecayTailUVAnim[3];	// start/middle/end
	int			nTextureId;				// ��ͼid
	int			nPriorityPlane;			// ���ȼ�ƽ��
};

struct Mex2ParticleEmitterSetting2:public Mex2ParticleEmitterSetting
{
	Vector vPlaneNormal;
	Vector vPlaneXAxis;
	Vector vPlaneYAxis;
	Mex2ParticleEmitterSetting2();
};

// added by zhuomeng.hu		[2/12/2011]
struct Mex2ParticleEmitterSetting3 : public Mex2ParticleEmitterSetting2
{
    Mex2ParticleEmitterSetting3();
    const Mex2ParticleEmitterSetting3& operator =( const Mex2ParticleEmitterSetting2& emtSetting );

    float fLifeSpanMax;     // ����������ֵ��������ֵ���� fLifeSpan ��Ч
    float fScaleRateMin;    // ��С���ű�����С���ֵ��������ֵС�� fScaleRateMin ��Ч
    float fScaleRateMax;    // ��С���ű���������ֵ��������ֵ���� fScaleRateMax ��Ч
    bool  bContraryColor;   // ���Ӷ����Ƿ�ɫ
};

// added by zhuomeng.hu		[2/18/2011]
struct Mex2ParticleEmitterSetting4 : public Mex2ParticleEmitterSetting3
{
    Mex2ParticleEmitterSetting4();
    const Mex2ParticleEmitterSetting4& operator =( const Mex2ParticleEmitterSetting3& emtSetting );

    bool  bAngleChangeByCone;       // �����Ƿ���淢�䷽��Ĳ�ͬ����ת
    bool  bTailLengthChange;        // ����β�ĳ����Ƿ��仯
    float fTailLengthChange[3];     // ����β�ĳ��ȱ仯ֵ
};

class  Mex2ParticleEmitter:public IMexParticleEmitter, public MeCommonAllocObj<Mex2ParticleEmitter>, public CEffectRenderable
{
	friend class Mex2ParticleEmitters;
	friend class Mex2;

public:
    virtual bool DoRender( SEmitterVertex* pBuffer);
	virtual int GetTotalVerticesCount(bool bPost) {return m_nAliveNumPart*4;}
	virtual int GetTotalFacesCount(bool bPost)  {return m_nAliveNumPart*2;}

public:
	Mex2ParticleEmitter();
	~Mex2ParticleEmitter();
	void	Read(Mex2Pointer inP,int inSize);
	void	Read2(Mex2Pointer inP,int inSize, DWORD version);
    void	Read3( Mex2Pointer inP, int inSize, DWORD version );    //added by zhuomeng.hu		[2/12/2011]
    void	Read4( Mex2Pointer inP, int inSize, DWORD version );    //added by zhuomeng.hu		[2/18/2011]
	// �麯��
	const char* GetName(){ return "" ; }
	const char* GetBindPartName(){ return m_szBindPartName; }

	void	Update( int nTime, float fScale, float* pfMatrices, float* pfmatModel  ,int nFrameId );
	void	Render( int nTime, short stTextureId, float fAlpha, bool bOverUI );
	int		GetLocalTextureID(){ return setting.nTextureId; }//setting->nTextureId; }
	virtual void SetLocalTextureID(int texid) { setting.nTextureId = texid; }
	void	SetActive( BOOL bActive ){ m_bIsActive = bActive; }
	void	SetPlaySpeed( float fPlaySpeed ){ m_fPlaySpeed = fPlaySpeed; }
	IMexParticleEmitter* Clone();
	void	Release();
	void	SetParentBoneID( int nBoneId ){ setting.nParentBoneId = nBoneId; }
	int		GetParentBoneID(){ return setting.nParentBoneId; }

	/*
	 * Ϊģ�Ͳ鿴�����ӽӿ�, �����޸����ӷ������Ĳ���
	 * 2012.5.29 wangshuai
	 */
	Mex2ParticleEmitterSetting4 * GetSetting() { return &setting; }
	void SetBindPartName(const char *szBindPart);
	BOOL & UseTimeBasedCell() { return m_bUseTimeBasedCell; }
	int & TimeBasedCellLoopTimes() { return m_nSeqLoopTimes; }
	BOOL & RotateParticle() { return m_bRotateParticle; }
	int & Rotate360DegreeCostTime() { return m_nRotate360DegreeCostTime; }
	BOOL & RandomDir() { return m_bRandomDir; }
	BOOL & RotNotFollowEmitter() { return m_bNoSelfRotate; }
	BOOL & UVRandomFirstCell() { return m_bUVRandomFirstCell; }
	BOOL & XYQuadLaydownInWorld() { return m_bXYInWorldSpace; }

	void SetSrcMex( IMex* pMex )
	{ 
		if( !pMex )
			return;
		Mex2* pMex2 = (Mex2*)( pMex );
		if( !pMex2 )
			return;

		pSrcMex = pMex2; 
	}

	static void SetMaxPartNum( int nNum ){ ms_nMaxPartNum = nNum; }
	static int GetMaxPartNum() { return ms_nMaxPartNum; }
protected:
	static int ms_nMaxPartNum;

protected:

	DWORD	dwVersion;
	BOOL	bReleased;
	
	//Mex2ParticleEmitterSetting*	setting;
	Mex2ParticleEmitterSetting4 setting;
	Mex2* pSrcMex;
	//
	Vector	vPos;

	float	m_fScale;
	int		m_nTime;
	float	m_fPlaySpeed;

	Vector vPlaneNormal;
	Vector	vPlaneXAxis;
	Vector vPlaneYAxis;
	//Vector vCameraSpaceUp;
	//Vector vCameraSpaceRight;
	Vector vPlaneViewUp;
	Vector vPlaneViewRight;
	DWORD	dwLastUpdateTime;
	DWORD	dwLastGenPartsTime;
	int		m_nNumPart;
	int		m_nAliveNumPart;
	Mex2Particle*		particles;//[MEX2_EMITTER_MAX_PARTICLE];
	BOOL	m_bIsActive;
	BOOL	m_bSquirtted;
	char	m_szBindPartName[MEX2_MAX_NAME];;
	BOOL	m_bUseTimeBasedCell;
	int		m_nSeqLoopTimes;
	
	BOOL	m_bRandomDir;		    // ������������ͼ�Ƿ��漴����                added by ZhuoMeng.Hu		[8/5/2010]
    BOOL    m_bNoSelfRotate;        // �����Ƿ���淢�����ı任����ת���ӿ���    added by zhuomeng.hu		[1/30/2011]
    BOOL    m_bUVRandomFirstCell;   // ���ӵ�UV�����Ƿ����������һ֡            added by zhuomeng.hu		[3/10/2011]
    BOOL    m_bXYInWorldSpace;      // ���ӵ�XYQuadģʽ�£�����������ϵ�з�ƽ    added by zhuomeng.hu		[3/17/2011]
	int		m_nRotate360DegreeCostTime;
	BOOL	m_bRotateParticle;
	// added, jiayi, [2010/6/9]
	// render�����alpha�������¼��
	float	m_fRenderAlpha;

	BOOL	IsParticleDead( Mex2Particle* pParticle, int nTime );
	void	GenParticle( Mex2Particle* pParticle, int nTime );
	void	UpdateParticle( Mex2Particle* pParticle, int nTime, float* pfMatrices, MeMatrix* pmatModel = NULL );
	void	GenDirection( Vector* axis, float fAngle, Vector* dir );
	void	MakeARenderParticle( Mex2Particle* pParticle, SEmitterVertex* vertex, float fAlpha );

	void	Reset();
	
	//   added 2004.07.01
	//void	SetActive( BOOL b ){ m_bIsActive = b; }

// private:	
// 	static LPDIRECT3DVERTEXBUFFER9 m_pVB;
// 	static LPDIRECT3DINDEXBUFFER9 m_pIB;
};

class Mex2ParticleEmitters:public IMexParticleEmitters, public MeCommonAllocObj<Mex2ParticleEmitters>
{
	friend Mex2;
public:
	void	Read(Mex2Pointer inP,int inSize, DWORD version);
	void	Bind( Mex2* pMex );

	int		GetEmitterCount(){ return vectorParticleEmitter.size(); }
	IMexParticleEmitter* GetEmitter( int i ){ return vectorParticleEmitter[i]; }

	virtual void   AppendEmitter(IMexParticleEmitter *e) { vectorParticleEmitter.push_back(dynamic_cast<Mex2ParticleEmitter *> (e)); }
	
protected:
	std::vector<Mex2ParticleEmitter*> vectorParticleEmitter;
	
	//void	Update( int nTime );
	//void	Render( int nTime );
	//   added 2004.07.16
	
};

#endif