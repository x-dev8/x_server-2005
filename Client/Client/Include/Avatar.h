#pragma once
#include "Me3d/Material.h"
#include "Me3d/Engine/TextureManagerInstance.h"
#include "Me3d/Engine/MeRenderObject.h"
#include "Me3d/Effect/BladeRibbon.h"

/*
	纸娃娃配置的含义，
	一个模型，引用另一个模型的部分网格，
	并且用指定的纹理替换另一个模型的纹理用来渲染，

	比如一头黑熊，
	具有3个subset，
	2张贴图，

	当我想把黑熊变成白熊的时候，
	引用自身的3个subset，
	将2张贴图的配置替换成白熊的配置，
*/
/*
	Component的设计
	Component是一个部件，也许不是渲染得最小单位，
	也不一定是逻辑的最小单位

	Effect
	包含Component上的特效，
	独立管理，精确管理

	我们可以在刀上捆绑粒子发射器，
	刀光等，

	由于不是刚体邦定，
	现在一件武器需要放在左手，右手，左背，右背，
	相当于4个相同的东西放在不同的地方，
	这样就给美工捆绑特效带来了负担，
	但是也是一个比较实在的解决方案，

	区分不同的地方用比较老的方法，
	就是名字判定，
	比如说billboard，在max中输出的时候有一个名字前缀bbrd,
	配合上lh,rh,lback,rback等，
	来区分部位，
	bbrd.lh.plane01 这是一个放在左手的billboard
	ribb.lh.box01 这是一个左手武器的条带发射器
	part.lh.box01 这是一个左手武器的粒子发射器

	当玩家装备一个武器或者收发武器的时候，
	会检测武器模型的特效，
	试图发现bbrd,ribb,part打头的特殊物体，
	如果发现了，则判断当前的部位，
	目前部位有lh,rh,lback,rback几个，
	如果当前部位是lh(左手)
	则把所有具有lh.命名的特效加入到容器中，
*/

class IMex;
class MexAnimCtrl;
class MtlAnim;
class BladeRibbonEffect;

// 纸娃娃的发型系统
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
		BOOL	bVisible;	// 是否可见
		int		nChunk;		// 在mex中的块编号
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
		DWORD		dwFlag;			// 装备在什么位置,lh,rh,lback,rback
									// 当flah与当前component相同的时候，才进行渲染
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
		// 只做判断是否重复使用，因为现在id不能唯一标示一个模型
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
		// 2006.12.02 加入带有动画的模型
		MexAnimCtrl* pMexAnims[eMaxPartAnim];
		BOOL bCanSee;	// 是否可见
		BOOL bCanSeeAfterBlend;// 动画blend结束再设为bCanSee;
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
	// 所有部件
	std::vector<Component> m_Components;
	// 辅助体
	IMexAttachment* m_pAttachments[MAX_AVATAR_ATTACHMENT];
	// 显示标志
	DWORD	m_dwEnableItemFlag;
	// 发型
	BOOL	m_bHasHairStyle;
	CAvatarHairStyle	m_HairStyle;
};

