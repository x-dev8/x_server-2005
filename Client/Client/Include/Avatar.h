#pragma once
#include "Me3d/Material.h"
#include "Me3d/Engine/TextureManagerInstance.h"
#include "Me3d/Engine/MeRenderObject.h"
#include "Me3d/Effect/BladeRibbon.h"

/*
	ֽ�������õĺ��壬
	һ��ģ�ͣ�������һ��ģ�͵Ĳ�������
	������ָ���������滻��һ��ģ�͵�����������Ⱦ��

	����һͷ���ܣ�
	����3��subset��
	2����ͼ��

	������Ѻ��ܱ�ɰ��ܵ�ʱ��
	���������3��subset��
	��2����ͼ�������滻�ɰ��ܵ����ã�
*/
/*
	Component�����
	Component��һ��������Ҳ������Ⱦ����С��λ��
	Ҳ��һ�����߼�����С��λ

	Effect
	����Component�ϵ���Ч��
	����������ȷ����

	���ǿ����ڵ����������ӷ�������
	����ȣ�

	���ڲ��Ǹ�����
	����һ��������Ҫ�������֣����֣��󱳣��ұ���
	�൱��4����ͬ�Ķ������ڲ�ͬ�ĵط���
	�����͸�����������Ч�����˸�����
	����Ҳ��һ���Ƚ�ʵ�ڵĽ��������

	���ֲ�ͬ�ĵط��ñȽ��ϵķ�����
	���������ж���
	����˵billboard����max�������ʱ����һ������ǰ׺bbrd,
	�����lh,rh,lback,rback�ȣ�
	�����ֲ�λ��
	bbrd.lh.plane01 ����һ���������ֵ�billboard
	ribb.lh.box01 ����һ����������������������
	part.lh.box01 ����һ���������������ӷ�����

	�����װ��һ�����������շ�������ʱ��
	��������ģ�͵���Ч��
	��ͼ����bbrd,ribb,part��ͷ���������壬
	��������ˣ����жϵ�ǰ�Ĳ�λ��
	Ŀǰ��λ��lh,rh,lback,rback������
	�����ǰ��λ��lh(����)
	������о���lh.��������Ч���뵽�����У�
*/

class IMex;
class MexAnimCtrl;
class MtlAnim;
class BladeRibbonEffect;

// ֽ���޵ķ���ϵͳ
class CAvatarHairStyle
{
public:
	enum
	{
		eBasePart,
		eJiGuanPart,
		eMaWeiPart,
		eLiuHaiPart,
		eLuoSaiPart,
		eHuXuPart,
		eDaoBaPart,
		eMaxPart,
	};
	struct Mesh
	{
		BOOL	bVisible;	// �Ƿ�ɼ�
		int		nChunk;		// ��mex�еĿ���
		Mesh():bVisible(FALSE),nChunk(-1){}
	};
	struct Vertex
	{
		D3DXVECTOR3 vPos;
		D3DXVECTOR3 vNormal;
		float		u, v;
		DWORD		dwColor;
	};
public:
	void	Render();
	Mesh*	GetMesh( int nMesh );
	BOOL	Build( IMex* pMex );
protected:
	DWORD	m_dwColor;
	std::vector<Mesh> m_Meshes;
	int		m_nNumVert;
	int		m_nNumFace;
	Vertex*	m_pVertices;
	WORD*	m_pIndices;
};
class CAvatar : public MeCommonAllocObj<CAvatar>
{
public:

	enum
	{
		eItem_RBack				= 1<<0,
		eItem_LeftHand			= 1<<1,
		eItem_RightHand			= 1<<2,
		eItem_Ground			= 1<<3,
		eItem_Shield			= 1<<4,
		eItem_LBack				= 1<<5,
		eItem_BackShield		= 1<<6,
	};
	enum
	{
		RIGHTHAND_ATTACHMENT,	
		LEFTHAND_ATTACHMENT,		
		RIGHTSHOULDER_ATTACHMENT,	
		LEFTSHOULDER_ATTACHMENT,	
		RIGHTBACK_ATTACHMENT,
		LEFTBACK_ATTACHMENT,		
		//RIGHTWAIST_ATTACHMENT,	
		//LEFTWAIST_ATTACHMENT,	
		SHIELD_ATTACHMENT,
		HEAD_ATTACHMENT,	
		BACKSHIELD_ATTACHMENT,	
		MAX_AVATAR_ATTACHMENT
	};
	enum
	{
		eExtra_RightHandPart,
		eExtra_LeftHandPart,
		eExtra_RightShoulderPart,
		eExtra_LeftShoulderPart,
		eExtra_RightBackPart,
		eExtra_LeftBackPart,
		eExtra_RightWaistPart,
		eExtra_LeftWaistPart,
		eExtra_ShieldPart,
		eExtraMaxPart,
	};
	enum
	{
		eMaxAttachBone = 2,
		eMaxParticleEmitter = 16,
		eMaxRibbonEmitter = 4,
		eMaxPartAnim = 2
		//eMaxAttachment = 10,
	};
	enum
	{
		eEffect_ParticleEmitter,
		eEffect_RibbonEmitter,
		eEffect_Billboard,
	};
	struct Effect
	{

		IMexParticleEmitter*	part;
		IMexRibbonEmitter*	ribb;
		IRenderable*			bbrd;
		BladeRibbonEffect*		pWeaponBladeRibbon;
		int			nType;
		DWORD		dwFlag;			// װ����ʲôλ��,lh,rh,lback,rback
									// ��flah�뵱ǰcomponent��ͬ��ʱ�򣬲Ž�����Ⱦ
		Effect();
	};
	struct EffectContainer
	{
		std::vector<Effect> effects;
		EffectContainer(){};
		void Destroy();
	};
	class Component
	{
	public:
		Component();

		void Clear();
		void SetAttachment( BOOL b ){ bIsAttachment = b; }
		BOOL IsAttachment(){ return bIsAttachment; }
		void SetMexAnim( int nSlot, MexAnimCtrl* pMexAnim );
		void SetCollectibleType(SortRenderable::ECollectibleType type);
        MexAnimCtrl* GetMexAnim( int nSlot );
		void SetCanSee( BOOL bcansee )
		{
			bCanSee = bcansee;
			if( !bCanSee && bCanSeeAfterBlend )
				bCanSeeAfterBlend = FALSE;
		}
		BOOL IsCanSee(){ return bCanSee; }
		void SetCanSeeAfterBlend( BOOL bcansee ){ bCanSeeAfterBlend = bcansee; }
		BOOL IsCanSeeAfterBlend(){ return bCanSeeAfterBlend; }

	public:
		std::string strName;
		IMex* pMex;
		// added, [10/20/2010 zhangjiayi]
		// ֻ���ж��Ƿ��ظ�ʹ�ã���Ϊ����id����Ψһ��ʾһ��ģ��
		short stSex;
		std::vector<IRenderable*> vectorChunk;
		MtlAnim* pMtlEffect;
		std::vector<DWORD> flags;
		//IMexAttachment* pAttachment;
		int nAttachment;
		MexCfgAvatarSetting* m_pAvatarSetting;
		MexReplaceableTextureProj ReplaceableTextureProj;
		MexReplaceableTextureProj ShimmerGrayTextureProj;
		MexReplaceableTextureProj LuminanceTextureProj;
		int HeatShimmerTexId;
		//MexCfgAvatarSetting* pAvatarSetting;
		int nModelID;
		DWORD dwItemFlag;
		graphics::Material material;		
		BOOL m_bLeftHand;
		EffectContainer m_EffectContainer;
		INT	 m_nSpecularTexID;

	private:
		BOOL bIsAttachment;
		// 2006.12.02 ������ж�����ģ��
		MexAnimCtrl* pMexAnims[eMaxPartAnim];
		BOOL bCanSee;	// �Ƿ�ɼ�
		BOOL bCanSeeAfterBlend;// ����blend��������ΪbCanSee;
	};
	struct CreateParam
	{
		int nComponentCount;
		char** ppszComponentNames;
		CreateParam();
	};
public:
	CAvatar();
	virtual ~CAvatar();

	BOOL	Create( CreateParam* pParam );
	int		GetComponentCount(){ return m_Components.size(); }
	Component* GetComponent( int nComponentID );
	Component* GetComponent( const char* pszComponentName );
	int		GetComponent( int nComponentID, Component** pComponents );

	BOOL	IsValidComponentID( int nComponentID ){
		if( nComponentID < 0 || nComponentID >=  m_Components.size() )
		{
			return FALSE;
		}
		return TRUE;
	}
	DWORD	GetEffectPart( const char* pszName );

	BOOL	BindAttachments( MexAnimCtrl* pMexAnimCtrl );
	//BOOL	BindAttachments( MexAnimCtrl* pMexAnimCtrl, int nProfession );
	BOOL	ChangeComponent( MexAnimCtrl* pMexAnimCtrl,
							int nComponentID, 
							int nModelID,
							int nLocalModelId,
							const char* szSkin,
							INT nSpecular,
							short stStar );
	BOOL	ChangeComponent( MexAnimCtrl* pMexAnimCtrl,
							int nComponentID,
							int nSlot, 
							MexResMgr::Record* pRecord, 
							MexAnimCtrl* pChild,
							const char* szSkin = DEFAULT_AVATARSETTING_NAME,
							INT nSpecular = -1,
							short stStar = 0 );
	BOOL	ChangeAttachment( MexAnimCtrl* pChild, 
								Component* pComponent,
								int nSlot );
	BOOL	ReleaseComponent( int nComponentID );
	BOOL	ReleaseAllComponents();

	void	EnableItem( DWORD dwFlag );
	void	DisableItem( DWORD dwFlag );
	void	ClearItem();
	void	SetItemFlag( DWORD dwFlag ){ m_dwEnableItemFlag = dwFlag; }
	DWORD	GetItemFlag(){ return m_dwEnableItemFlag; }
	IMexAttachment* GetAttachment( int nPart );
	BOOL	HasHairStyle(){ return m_bHasHairStyle; }
	void	EnableHairStyle( BOOL bEnable ){ m_bHasHairStyle = bEnable; }
	CAvatarHairStyle* GetHairStyle(){ return &m_HairStyle; }
protected:
	// ���в���
	std::vector<Component> m_Components;
	// ������
	IMexAttachment* m_pAttachments[MAX_AVATAR_ATTACHMENT];
	// ��ʾ��־
	DWORD	m_dwEnableItemFlag;
	// ����
	BOOL	m_bHasHairStyle;
	CAvatarHairStyle	m_HairStyle;
};

