#ifndef _playeranimctrl_h
#define _playeranimctrl_h
#include <vector>
#include <list>
#include <windows.h>
//#include "Me3d\MEX2.h"
#include "Me3d/Model/mexconfig.h"
#include "Me3d/AnimTimeline.h"
#include "Stdcharskeleton.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "Avatar.h"
#include "GlobalDef.h"
#include "globalvars.h"
#include "ActionQueue.h"
#include "GlobalDef.h"
#include "PlayerEquip.h"

class AnimTimeLine;
class MexAnimCtrl;
class PlayerAnimCtrlMgr;
class CPlayer;
struct CPlayer_SEquipment;

class CPlayerAnimParam
{
public:
	CPlayerAnimParam()
	{
		szSkin = DEFAULT_AVATARSETTING_NAME;
		nSpecularTextureID = -1;
		nColor = -1;
        nIntensifyTime = -1;
        pEquips = NULL;
		nPart = -1;
		nModelId = -1;
		LowestIntensity = 0;
	}

    // ͨ����λ�õ�CPlayer_SEquipment��
//     CPlayer_SEquipment* getEquipByPart(CStdCharSkeleton::enumPartId part)
//     {
//         return &pEquips[part];
//     }

    // �õ���ǰҪװ����CPlayer_SEquipment��
    CPlayer_SEquipment* getCurrentEquip()
    {
        return &pEquips[nPart];
    }

	INT nModelId;
	INT nProfession;
	INT nSex;
	INT nPart;              // װ����λ��
	const char *szSkin;
	INT nColor;
	INT nSpecularTextureID;
    // װ��ǿ���ȼ�����ͬǿ���ȼ�������ʾ��ͬ��Ч [6/5/2008 whu]
    int nIntensifyTime;
	// ������ϵ����װ���Ǽ�
	int LowestIntensity;
    CPlayer_SEquipment* pEquips;
};

// װ��ǿ����Ч��Ϣ
struct EquipIntensifyEffectInfo
{
	EquipIntensifyEffectInfo() : nIntensifyModelID(-1)
	{
		ZeroMemory(szBindBoneName, 80);
	}

	int nIntensifyModelID;
	char szBindBoneName[80];
};

class CPlayerAnim:public MexAnimCtrl
{
public:
	/*static void InitializePartMask();*/

	//////////////////////////////////////////////////////////////////////////
public:// avatar staff
	void	SetAvatar( CAvatar* pAvatar ){ m_pAvatar = pAvatar; }
	CAvatar* GetAvatar(){ return m_pAvatar; }
	void	UpdateAvatar( DWORD dwTime, float* pfModel, CAvatar* pAvatar );
	BOOL	RenderAvatar( CAvatar* pAvatar, IRenderer* pRenderer, float fAlpha, int* pRetVertexCount=NULL, int* pRetFaceCount=NULL,
		BOOL bIsHairHelmetAlphaTest = FALSE, BOOL bRenderShadow=FALSE,
		BOOL bRenderAll = TRUE);	// bRenderAll, ������Ҫ���������꣬����Ⱦ

	void			ClearBladeRibbon();
	virtual void	ApplyBladeRibbon();
	virtual void	UpdateLocalBBox();
	virtual	bool	UpdateComponents( DWORD dwTime, MeMatrix* pMatrix );
	virtual void	ReleaseLastModel();
	// ����ģ�ͣ�����ͷ�����������ף�������ȫ�����Ը����Ĳ�λ
	BOOL	ChangePartModelById( int nPartId, int nModelId, int nLocalModelId, const char* szSkin = DEFAULT_AVATARSETTING_NAME, int nSpecular = -1, short stStar = 0 );
	// ���ò�λ�Ĳ�����Ч
	BOOL	ApplyPartMtlEffect( int nPartID, int nEffectID );
	void	ReleaseAllLastPartModel();
	void	ReleaseLastPartModel( int nPartId );	
	int		GetPartModelID( int nPart );

	void	AttachEffectToComponent( int nComId, int nBoneId, IMex* pMex );
	void	AttachEffectToComponent( const char* pcComName, int nBoneId, IMex* pMex );

protected:
	void	RenderAvatarShadow( CAvatar* pAvatar, IRenderer* pRenderer );
	void	RenderAvatorComponent( CAvatar* pAvatar, CAvatar::Component* pComponent, IRenderer* pRenderer, float fAlpha, bool bMustUseAlphaBlend,
				int* pRetVertexCount=NULL, int* pRetFaceCount=NULL, BOOL bIsHairHelmet = FALSE,
				BOOL bRenderShadow=FALSE );
	void	RenderAvatorComponentShadow( CAvatar* pAvatar, CAvatar::Component* pComponent, IRenderer* pRenderer, float fAlpha, bool bMustUseAlphaBlend );
	void	AttachEffectToComponent( CAvatar::Component* pComponent, int nBoneId, IMex* pMex );	
	// ��Ϊ�й��������Ĳ�������
	//void	UpdateAsAnimComponent( DWORD dwTime, MexAnimCtrl* pBindAnim, int nBindBoneID, float* pfHelperMatrixInit,int nBoneIndex = 0 );

	virtual BOOL _ChangeModel( IMex* pMex, MexCfg* pMexCfg,const char* pszSkin = NULL);
	virtual void CheckWeaponDisplay();

protected:
	void			_ApplyBladeRibbon(eKeyAllPart eValue);
	void			_ClearBladeRibbon(eKeyAllPart eValue);
	CAvatar*		m_pAvatar;//editor 
	//////////////////////////////////////////////////////////////////////////

public:
    // ����ģ�Ͳ�����ɫ����ֹPost process����ģ��ʱ���� [6/26/2008 whu]
    static D3DMATERIAL9 GlobalMaterial;


	CPlayerAnim();
	virtual ~CPlayerAnim();

	void	SetPlayer( CPlayer* pPlayer ){ m_pPlayer = pPlayer; }
    const CPlayer* GetPlayer() { return m_pPlayer; }
	BOOL	LoadFromFile( const char* pszFilename );
	virtual void	Destroy();
	BOOL	ChangeArmourModel( int nModelId, int nProfession, int nSex, int nType );
	BOOL	ChangeEquip( 
						CPlayerAnimParam &param
						/*int nModelId, 
						int nProfession,
						int nSex, 
						int nType,
						const char* szSkin = DEFAULT_AVATARSETTING_NAME,
						int nColor = -1*/ );

	BOOL	ChangeEquip(const std::string& filename, int nPart);

// 	int		GetMexResId( int nModelId, 
// 						int nProfession,
// 						int nSex, 
// 						int nType,
// 						int nColor = -1 );

	BOOL	ChangePartModel( CPlayerAnimParam& Param,
							//int nPartId, int nModelId, const char* szSkin = DEFAULT_AVATARSETTING_NAME,
							BOOL bNoModel = FALSE ,BOOL bOnePart = FALSE);
	BOOL	TryChangePartModel( CPlayerAnimParam& Param, const char* pcFilename );
	BOOL	MyChangeModel( int nModelId, BOOL bChangeByMultiThread, const char* pszSkin);
	BOOL	TryChangeModel( int nModelId, const char* pszSkin = NULL );

	BOOL	IsAvatarLoaded();

	BOOL	Update( DWORD dwTime, MeMatrix* pMatrix, BOOL* bUpperbodyPlayOver = NULL );	// ���ض����Ƿ��л���bUpperbodyPlayOver��¼�ϰ������Ƿ���
	virtual BOOL	Render( float fTransparent = 1.0f, LayerDataContainer* pMeshContainer = NULL, int* pRetVertexCount=NULL, int* pRetFaceCount=NULL, 
        BOOL bRenderShadow=FALSE , BOOL bRenderParticleEmitters=TRUE, 
		bool bOverUI = false, BOOL bRenderDecal = TRUE );
// 	void	FastRender( float fTransparent = 1.0f );
	void	RenderShadow();
	void	OnHitPoint( AnimTimeLine::SKey* pKey, DWORD dwFlag = 0 );
	DWORD	ConvertAnimType( DWORD dwOldType );

	// ��ָ����ʱ���ڣ������궯��
	void	PlayAnim2(	DWORD dwAnimType, DWORD dwAnimPlayMode,
		DWORD dwOneLoopTime,
		DWORD dwLoopTimes, DWORD dwTimeOut,
		DWORD dwTargetAnimType, DWORD dwTargetAnimPlayMode );

	void	PlayAnim3(	DWORD dwAnimType, DWORD dwAnimPlayMode,
		DWORD dwOneLoopTime,
		DWORD dwLoopTimes, DWORD dwTimeOut,
		DWORD dwTargetAnimType, DWORD dwTargetAnimPlayMode );

	// ����szAnimName��������ʱ��
	int	PlayAnimByActionName( const char* szAnimName, DWORD dwAnimPlayMode,
		DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, DWORD dwBlendingTime,
		const char* szTargetAnimName, DWORD dwTargetAnimPlayMode, 
		DWORD dwTargetOneLoopTime = 0, DWORD dwTargetLoopTimes = eMaxLoopTimes, DWORD dwTargetTimeOut = eMaxTimeout, DWORD dwTargetBlendingTime = eDefaultBlendingTime );

	//// �����ϰ���Ķ���
	//void	PlayUpperAnim( const char* szAnimName, DWORD dwAnimPlayMode,
	//	DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, DWORD dwBlendingTime,
	//	char* szTargetAnimName, DWORD dwTargetAnimPlayMode,
	//	DWORD dwTargetOneLoopTime = 0, DWORD dwTargetLoopTimes = eMaxLoopTimes, DWORD dwTargetTimeOut = eMaxTimeout, DWORD dwTargetBlendingTime = eDefaultBlendingTime );

	//void	PlayUpperAnim( DWORD dwAnimType, DWORD dwAnimPlayMode,
	//	DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, DWORD dwBlendingTime,
	//	DWORD dwTargetAnimType, DWORD dwTargetAnimPlayMode,
	//	DWORD dwTargetOneLoopTime = 0, DWORD dwTargetLoopTimes = eMaxLoopTimes, DWORD dwTargetTimeOut = eMaxTimeout, DWORD dwTargetBlendingTime = eDefaultBlendingTime );

	// �����ϰ���Ķ���
	void	PlayUpperAnim( const char* szAnimName, DWORD dwAnimPlayMode,
		DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, DWORD dwBlendingTime, BOOL bWholeBodyAnim = FALSE, BOOL bNormalAttackAnim = FALSE,
		BOOL bIsPlayerRole = FALSE);

	void	PlayUpperAnim( DWORD dwAnimType, DWORD dwAnimPlayMode,
		DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, DWORD dwBlendingTime, BOOL bWholeBodyAnim = FALSE, BOOL bNormalAttackAnim = FALSE );

	// �����°���Ķ���
	void	PlayLowerAnim( const char* szAnimName, DWORD dwAnimPlayMode,
		DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, DWORD dwBlendingTime,
		const char* szTargetAnimName, DWORD dwTargetAnimPlayMode,
		DWORD dwTargetOneLoopTime = 0, DWORD dwTargetLoopTimes = eMaxLoopTimes, DWORD dwTargetTimeOut = eMaxTimeout, DWORD dwTargetBlendingTime = eDefaultBlendingTime );

	void	PlayLowerAnim( DWORD dwAnimType, DWORD dwAnimPlayMode,
		DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, DWORD dwBlendingTime,
		DWORD dwTargetAnimType, DWORD dwTargetAnimPlayMode,
		DWORD dwTargetOneLoopTime = 0, DWORD dwTargetLoopTimes = eMaxLoopTimes, DWORD dwTargetTimeOut = eMaxTimeout, DWORD dwTargetBlendingTime = eDefaultBlendingTime );

	//����һ������������,����ʱ������ǰ�Ķ���
	void	PlayInsertAnim( const char* AnimName, DWORD AnimPlayMode = MexAnimCtrl::eNormalPlay,
		DWORD OneLoopTime = 0, DWORD LoopTimes = 1, DWORD TimeOut = MexAnimCtrl::eMaxTimeout );

	// �޸ĵ�ǰ������loop���������<0����Ϊ��ǰ�Ѳ�����+1
	void	ForceCurrAnimLoopTime(int nTimes, BOOL bUpperAnim = FALSE);

	int		GetActionModelId( int nProfession, int nSex, int nWeaponType = -1 );
	int		GetModelIDByClassAndGender(int nClass, int nGender);

	int		GetWeaponActionModelId( int nProfession, int nSex, BOOL bHoldFlag = FALSE );
	BOOL	ChangeWeaponAnim( int nWeaponModelId );
	// add, jiayi, [2009.4.17]
	BOOL	ChangeWeaponAnim( int nProfession, int nWeaponModelId );
	DWORD	GetCurAnimType(){ return m_dwAnimType; }
	void	SetCurAnimType( DWORD dwAnimType ){ m_dwAnimType = dwAnimType; }
	DWORD	GetCurTargetAnimType(){ return m_dwTargetAnimType; }
	BOOL	CanReEnter( DWORD dwOldAction, DWORD dwNewAction );

	//   added 2003.01.12
	//��������Ч�����ж���ʯ���������ͻ�˯
	void	CreateSelfEffect( int nEffectId );
	void	EndSelfEffect();

	/*
	 * Author:	2012-8-22 wangshuai
	 * Desc: 	�����Ǽܺͻ�װ
	 */
	void ChangeSkeletonAndEquipAll(void* pEquips, INT iSex, INT nCountry = country_none,
		INT nColor = -1, bool showHelmet = true, bool showFashion = false, int nDefModelIndex = 0,
		unsigned short hero_id = INVALID_HERO_ID,bool showHero = true,bool bSeeCheck = false); //lyh++ ���һ������ ָ�Ƿ�Ϊ�鿴װ�����棬�ǵĻ� ������lua������Ч���ƣ���Ϊû�еط����١�

	void	UpdateHardItem( bool fight_state,	void* pEquips0 );
	void	UpdateRightHardItem( bool fight_state );

	void	SetFightState( BOOL fight_flag );
	//void	FightStateEnd();

	void	SetAttackInfo( SAttackInfo * pAttackInfo )
	{
		m_pAttackInfo = pAttackInfo;
	}
	void	ClearAttackInfo( void );
	bool	HasAttackInfo( void );
	int		GetWeaponType(){ return m_nWeaponType; }
	//BOOL	HaveTryChangePartModel();
	void	SetChangeAllEquipComplete( BOOL bComplete ){ m_bChangeAllEquipComplete = bComplete; }
	BOOL	ChangeAllEquipComplete(){ return m_bChangeAllEquipComplete; }

    //
    // add [6/17/2008 whu]
    //

    /** ����װ����Ч��
    @param part װ����λ��
    @param texFilename ��Ч��ͼ�ļ�����
    */
    void setEquipEffect( int part, const char* texFilename );

    /** ����װ����Ч��
    @param part װ����λ��
    @param MEXFilename ��Чģ���ļ�����
    */
//     void setEquipModelEffect( const char* MEXFilename );

	//const char* GetNextLowerAnimName();
	//void ReplaceNextLowerAnim(SPlayTask* task);

	void SetWholeBodyAnim( BOOL bFlag ) { m_bIsUpperAnimWholeBody = bFlag; }

public:
	unsigned short DefPart[2][eKeyAll_Max];
	void		SetPlayTargetAnim();
	CPlayer_SEquipment* GetBackEquip(){ return BackEquip; }
protected:
	BOOL		m_bChangeAllEquipComplete;
	DWORD		m_dwAnimType;
	DWORD		m_dwTargetAnimType;
	DWORD		m_dwAnimPlayMode;
	CPlayer_SEquipment BackEquip [eKeyAll_Max];

	INT			BackColor;

	//std::vector<int>	m_veTryChangePartModel;			//Ҫ����̼߳��صĲ���
	//std::set<int>		m_seTryChangePartModel;			//Ҫ����̼߳��صĲ���
	//int					m_nSelfEffectId;

	CPlayer*	m_pPlayer;
	int			m_nWeaponType;

	//BOOL		m_bPlayerDeath;

	//������Ϣ
	SAttackInfo *m_pAttackInfo;

	// װ��ǿ����Ч
	MexAnimCtrl *m_pEffectAnim;
	EquipIntensifyEffectInfo mEquipEffectInfo;

	//����ĳ����λ������װ��Ч��
	void SetSpecialEquipEffect( int iPart, CPlayer_SEquipment* pEquip );    

    typedef std::map< std::string, MexAnimCtrl* > EquipEffectMexs;
    EquipEffectMexs _equipEffectMexs;

	BOOL		m_bIsUpperAnimWholeBody;				// �������Ƿ�ȫ����
    BOOL		m_bIsLootAnim;	    // �Ƿ�ɼ�����
    BOOL        m_bIsIntonateAnim;  // �Ƿ�س���������
public:

    BOOL        CanSwitchIdleAnim();
    BOOL        IsCurrAnimHideWeapon();
    BOOL        IsUpperAnimHideWeapon();
    BOOL        IsLowerAnimHideWeapon();
    BOOL        IsAnimNeedHideWeapon( const char* szAnimName );

    BOOL        IsLootAnim();
    BOOL        IsIntonateAnim();
    BOOL        IsInteractionAnim();

    // ���Ӷ���
    BOOL        IsHoldingFlagOnRightHand(CPlayer_SEquipment *pEquip=NULL);
    void        TryPlayFlagAnim(const char* szAnimName);
    void        TryPlayFlagAnim(DWORD dwAnimType);
    
    // NPCģ�ͼ����꣬����ǰ����
    void        PlayDefaultAnimAfterChangeModel();
protected:
    BOOL        m_bIsHoldingFlagOnRightHand;    // ���m_pPlayerΪ�գ����¼����״̬
    BOOL        m_bNpcNeedReplayAnim;           // ���NPC������ʧ�ܣ�����Ҫ�������־
};

// add, for lua [6/17/2008 whu]
extern CPlayerAnimParam* _pCurrPlayerAnimParam;
extern CPlayerAnim*      _pCurrPlayerAnim;
extern INT GetSpecularTexID( INT nType, CPlayer_SEquipment* pEquip );

namespace Equip
{
    CPlayerAnimParam* getCurrentEquipParam();
    CPlayerAnim* getCurrentEquipPlayerAnim();
}


#endif