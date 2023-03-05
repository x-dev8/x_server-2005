#pragma once
#include "Me3d/Me3d.h"


#define ONE_FRAME_TIME 33
enum
{
	eEffectBindPart_Body,					//身体
	eEffectBindPart_Head,					//头顶
	eEffectBindPart_LeftHand,				//左手
	eEffectBindPart_RightHand,				//右手
	eEffectBindPart_Foot,					//脚底
	eEffectBindPart_Back,					//背
	eEffectBindPart_Spray,					//脚下的站地点
	eEffectBindPartMax,
};

enum
{
	eTerminateMode_Life,
	eTerminateMode_WaitAllInstanceDead,
	eTerminateMode_WaitParentDelete,
	eTerminateMode_Loop,
	eTerminateModeMax
};

enum
{
	eNoCameraStunt = 0,				//无摄象机特效
	eNormalShake,					//普通振动
	eHorizontalShake,				//水平振动
	eVerticalShake,					//垂直振动
	eViewDirShake                   //视线方向震动
};

class IEffectHelper;
class IEffectEmitter;
class IEffectQuoter;
class IEffect
{
public:
	//IEffect(){};
	virtual ~IEffect(){};
	virtual void SetID( int nID ) = 0;
	virtual int	 GetID() = 0;
	virtual void Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance  ) = 0;
	//virtual void Cull( D3DXVECTOR3 vPos, float fDistance ) = 0;
	virtual void Render() = 0;
	virtual BOOL IsDead( DWORD dwTime ) = 0;
	virtual void SetDead() = 0;
	virtual void Release() = 0;
	virtual IEffectQuoter* GetEffectQuoter() = NULL;
	virtual void SetEffectQuoter( IEffectQuoter* pEffectQuoter ) = 0;
};
class IEffectQuoter
{
public:
	virtual BOOL UnRef( int nEffectID ) = 0;
};
class IEffectHelper
{
public:
	//IEffectHelper(){};
	virtual ~IEffectHelper(){}
	virtual void	SetPos( float x, float y, float z ) = 0;
	virtual void	GetPos( float pos[3] ) = 0;
	virtual void	SetFinalRenderAlpha( float fAlpha ){}
	virtual float	GetFinalRenderAlpha(){ return 1; }
	virtual void	SetRot( float fRot ) = 0;
	virtual float	GetRot() = 0;
	virtual void	SetScale( float fScale ) = 0;
	virtual float	GetScale() = 0;
	virtual void	SetTerrainZ( float fTerrainZ ) = 0;
	virtual float	GetTerrainZ() = 0;
	virtual BOOL	IsDestroy() = 0;
};
class IEffectEmitter
{
public:
	virtual ~IEffectEmitter(){}
	virtual void SetStartTime( DWORD dwTime ) = 0;
	virtual DWORD GetStartTime() = 0;
	virtual void SetLife( DWORD dwLife ) = 0;
	virtual DWORD GetLife() = 0;
	virtual void SetMaster( IEffectHelper* pHelper ) = 0;
	virtual IEffectHelper* GetMaster() = 0;
	virtual void SetTarget( int nTarget, IEffectHelper* pHelper ) = 0;
	virtual IEffectHelper* GetTarget( int nTarget ) = 0;
};


class CEffectHelper:public IEffectHelper
{
public:
	CEffectHelper();
	~CEffectHelper();
	void	SetPos( float x, float y, float z );
	void	GetPos( float pos[3] );
	void	SetFinalRenderAlpha( float fAlpha );
	float	GetFinalRenderAlpha();
	void	SetRot( float fRot );
	float	GetRot();
	void	SetScale( float fScale );
	float	GetScale();
	void	SetTerrainZ( float fTerrainZ );
	float	GetTerrainZ();
	void	SetDestroyFlag();
	BOOL	IsDestroy();
protected:
	float m_x, m_y, m_z;
	float m_fTerrainZ;
	float m_fRotZ;
	float m_fScale;
	float m_fFinalRenderAlpha;
	BOOL m_bDestroyFlag;
};


class CBaseEffect:public IEffect, public MeCommonAllocObj<CBaseEffect>
{
public:
	CBaseEffect();
	void SetID( int nID );
	int	 GetID();
	virtual ~CBaseEffect();
	virtual void Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance );
	//virtual void Cull( D3DXVECTOR3 vPos, float fDistance );
	virtual void Render();
	virtual BOOL IsDead( DWORD dwTime );
	virtual void Release();
	virtual void SetDead();
	virtual BOOL LoadSetting( const char* pszFilename, BOOL bMilti  = false ){ return FALSE; }
	void SetEffectQuoter( IEffectQuoter* pEffectQuoter ){ m_pEffectQuoter = pEffectQuoter; }
	IEffectQuoter* GetEffectQuoter(){ return m_pEffectQuoter; }
    void    SetPlayerID( int nID ) { m_nPlayerID = nID; }
    int     GetPlayerID() { return m_nPlayerID; }
protected:
	int		m_nID;
	IEffectQuoter* m_pEffectQuoter;

    // 增加PlayerID，用于隐藏玩家特效时判断玩家与主角的关系
    int     m_nPlayerID;
};

