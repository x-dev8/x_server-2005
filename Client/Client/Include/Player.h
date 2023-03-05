#ifndef _player_h
#define _player_h
#include "Dxsdk/d3dx9.h"
#include <list>
#include <queue>
#include <map>
#include <windows.h>
#include "StaticArray.h"
//#include "Mesocket.h"
#include "GlobalDef.h"
#include "MessageDefine.h"
//#include "MsgFromBuf.h"
#include "GlobalDef.h"
#include "Me3d\Include.h"
#include "PlayerEX.h"
#include "PlayerAnimCtrl.h"
#include "ExpStage.h"
#include "BuffStatusManager.h"
#include "LagCounter.h"
#include "GlobalDef.h"
#include <string>
#include "PlayerRole.h"
#include "playerequip.h"
#include "CreatureSound.h"
#include "Me3d/Effect/EffectManager.h"
#include "ActionQueue.h"
#include "MoveQueue.h"
#include "MovePath.h"
#include "Me3d/effect/CharEffectContainer.h"
#include "GuildIcon.h"
#include "MeTerrain/SwType.h"
#include "Me3d/MoreAction.h"
#include "MoreActionClient.h"
#include "EquipEnum.h"
#include "MapArea.h"
#include "RTTFont.h"
#include "SwMap.h"
#include "Me3d/BaseGraphics.h"
#include "HeightMapData.h"
#include "NpcInfo.h"
#include "ChainEffect.h"
#include "shortcutkey_configure.h"

using namespace std;

class CPlayer;
class CRecorder;
class I_PlayerEffect;
class CMexEffect;
class ControlText;

class Font3D;
class CNdlDecalRes;
typedef std::pair<GameObjectId, CPlayer*> PlayerPair;
class CWSModelEffect;
class CHitFlashEffect;
class CFootPrint;
class ProgressBar3D;

#define MAX_TARGET_PLAYER	16
#define MAX_WAIT_TIME	0x7fffffff
#define MAX_STATUS_TIME 0x7fffffff

#define NeedVerifyDistance 16.18f
#define CHAT_DIALOG_BOX_LIFE_LONG	1000*10
#define HEIGHTMAP_SHOW_RECT_CNT     45
#define EFFECTPATCHLEN 256

struct SOperation
{
	enum
	{
		eOpNothing,
		eOpIdle,        //����
		eOpUseSkill,    //ʹ�ü���/
		eOpTalk,        //�Ի�
		eOpGetItem,     //ȡ�õ���
		eOpDropItem,	//��������
		eOpMoveTo,      //�ƶ���Ŀ��ص�
		eOpTrade,       //����
		eOpChangeDir,	//ת��
		eOpMoveSkill,   //�ƶ���ȥʹ�ü���
		eOpMoveTalk,    //�ƶ���ȥ�Ի�
		eOpMoveGetItem,  //�ƶ���ȥȡ�õ���
		eOpMoveGetRangeItem, //ȡ����Χ�ĵ���
		eOpMoveDropItem,//�ƶ���ȥ��������
		eOpMoveTrade,   //�ƶ���ȥ����
		eOpMoveFollow,  //����
		eOpDoAction,    //��Ī����Ϊ��Action
		eOpVerifyPos,			// λ��У��
	};

	enum
	{
		eTimeOut	= 1,		// ��ʱ��
		eNoTryTimes = 1<<1,		// ���Դ�������
		eUpdate		= 1<<2,		// ������һ��

	};

	DWORD dwType;				// (��ǰ���ж�)��������
	//
	struct Target
	{
		int stDst;				//Ŀ��npc
		int x, y;				// ����(�����ƶ���Ŀ������) 
	} target;					// Ŀ��
	//
	struct Skill
	{
		int iSkillID;			//ʹ�õļ��ܱ��
		int	iSkillLevel;		//ʹ�õļ��ܵȼ�
	}skill;
	//
	struct Action
	{
		int iActionID;			//��Ҫ���Ķ����ı��
	}action;

	//����ԭ�ع���
	bool	bHoldAttack;
	//
	bool	bAttackToDeadFlag;	//�����ǹ���,�����ж��ܷ񹥻�����
	DWORD	dwFlag;				// ��־λ
	//
	DWORD	dwOperBeginTime;	//�ò�����ʼ��ʱ��
	SOperation(){ Clear(); }
	void	Clear();
};

struct SkillRuntimeDesc
{
	enum
	{
		eNone,
		eIntonate,
		eHold,
	};

	DWORD	dwStartTime;			// ���ܿ�ʼʱ��
	DWORD	dwIntonateTime;			// ����ʱ��
	DWORD	dwHoldTime;				// ����ʱ��
	DWORD	dwCancelTime;			// ȡ��ʱ��
	BOOL	bCancelHasSent;			// ȡ���Ƿ��ѷ���
	BOOL	bMovePermit;			// �Ƿ������ƶ�
	DWORD	dwSkillStatus;			// ��ǰ����״̬���������߳���
	std::vector<I_PlayerEffect*> vectorEffect;		// ��ǰʹ�õ���Ч

	SkillRuntimeDesc(){ Reset() ; }
	void	Reset();
	void	Start( DWORD dwStatus ){ dwSkillStatus = dwStatus; }
	DWORD	GetStatus(){ return dwSkillStatus; }

	void	CancelHasSent( BOOL b ){ bCancelHasSent = b; }
	BOOL	IsCancelHasSent(){ return bCancelHasSent; }
	BOOL	Cancel( DWORD dwTime );
	void	PermitMove( BOOL b ){ bMovePermit = b; }
	BOOL	IsPermitMove(){ return bMovePermit; }

	void	AddEffect( I_PlayerEffect* p ){ vectorEffect.push_back( p ); }
};

enum eActionState
{
	eAction_None = 0, //���κ�״̬
	eAction_Buoy ,    //����
	eAction_HitBack,  //����
	eMax
};

class CPlayer : public MeCommonAllocObj<CPlayer>
{
public:

	CPlayer();
	~CPlayer();

    //�Ƿ������ǣ�Ŀǰ��Ҫ������ʾ����λ�ã���render
    void				SetRole( BOOL bRole ){ m_bRole = bRole; }	
	DWORD				GetDBID() {return m_dwCharacterID;}
    void				SetID( GameObjectId stID ){ m_stID = stID; }

	
	void                SetEffectID(int i,const char* EffectName) ;
	
	void                ReSetEffectID(){m_EffectID = -1; }
	int                 GetEffectID(){return m_EffectID;}

	int                 GetHeroKillTargetNum(){return   m_HeroKillTargetNum;}
	void                SetHeroKilltargetNum(int Num ) {m_HeroKillTargetNum = Num;}
	void                SetHeroKillChanged(bool bchange) {m_HeroKillHasChanged = bchange;}

	int                 GetEffectCharSkillID();
	void                SetEffectCharSkillID(int skillID);

    GameObjectId	GetID(){ return m_stID; }

    void				SetCharacterID( DWORD dwCharacterID );
    DWORD				GetCharacterID();

    void				SetModelId( short stModelId ){ m_nModelId = stModelId; }
    int					GetModelId(){ return m_nModelId; }

    VOID				SetMonsterID(INT nMonsterID) { m_nMonsterID = nMonsterID;}
    INT					GetMonsterID()			{ return m_nMonsterID; }

    void				GetMapPos( int &x,int &y ){ x = m_ptLoc.x; y = m_ptLoc.y; }
    POINT				GetMapPos(){ return m_ptLoc; }
	
	void                SetNpcID(int nID){m_nNpcId = nID;}
	int                 GetNpcID(){return m_nNpcId;}

    void				SetName( char* pszName );
    char*				GetName(){ return m_szName; }

	const char *		GetDisplayName() const { return m_szDisplayName; }

	unsigned char		GetGender() const { return m_ucSex; }
	unsigned char		GetClass() const { return m_ucProfession; }

    // ���
    void                SetPlayerScale( float scale ) { if( scale > 0 ) m_fPlayerScale = scale; }
	float				GetPlayerScale()	{return m_fPlayerScale;}
    void				SetGuildIconCRC(WORD stID,const char* GuildName,ULONG ulCRC);	//sbw_add
    void				setGuildTitle( short shTitle ) { m_shGuildTitle = shTitle; }
    /*void				setGuildInfluence( short shInfluence ) { m_shInfluence = shInfluence; }*/
    /*short               GetGuildInfluence(){return m_shInfluence; }*/
    void				RegisterGuildIcon(ULONG ulCrcCode, LPBYTE pbyte,DWORD dwSize);

    void				SetTeamId( uint32 stId ){ m_stTeamId = stId;}
    uint32				GetTeamId(){ return m_stTeamId; }
    void				SetTeamPosition( char cPos ){ m_cTeamPosition = cPos; }
    char				GetTeamPosition(){ return m_cTeamPosition; }


	CPlayer_SEquipment*	GetEquip() { return m_equips; }
	void				SetEquip( CPlayer_SEquipment* equips );
	float				GetBodySize(){ return m_fBodySize; }
	void				SetBodySize( float fBodySize ){ m_fBodySize = fBodySize; }
	float				GetBodyLengthSize() const { return m_fBodyLengthSize; }
	void				SetBodyLengthSize(float val) { m_fBodyLengthSize = val; }

    int                 GetWeaponModelID(BOOL bLeft = FALSE);

	float				GetWeaponAttackRange(){ return m_fWeaponAttackRange; }
	void				SetWeaponAttackRange( float fRange ){ m_fWeaponAttackRange = fRange; }

	int					GetShotEffectID( void ){ return m_iShotEffectID; }
	void				SetShotEffectID( int iEffectID ){ m_iShotEffectID = iEffectID; }

	void				SetCountry( int iCountry ){ m_iCountry = iCountry; }
	int					GetCountry( void ){ return m_iCountry; }

	// ���ϵ�SetCountry�Ǽٵ�	����Ϊ�� ���� �� ���ҳƺ�		added by zhuomeng.hu		[9/9/2010]
	void				SetRealCountry( uint8 coutryId ){ m_iRealCountry = coutryId; }
	uint8				GetRealCountry(){ return m_iRealCountry; }
	void				SetCountryTitle( uint16 countryTitle ){ m_iCountryTitle = countryTitle; }
	uint16				GetCountryTitle(){ return m_iCountryTitle; }
    void                SetPortraitId( uint8 portraitId ){ m_iPortraitId = portraitId; }
    uint16              GetPortraitId(){ return m_iPortraitId; }

	void				SetFamilyID( uint32 id ) { m_iFamilyID = id; }
	uint32				GetFamilyID() { return m_iFamilyID; }
	void				SetFamilyPos( int8 pos ){ m_iFamilyPos = pos; }
	int8				GetFamilyPos() { return m_iFamilyPos; }

	void				SetCountryMask( int iCountry );
	void				ApplyCountryMask( void );
	void				ClearCountryMask( void );

	void				SetPos( float x, float y, float z );

	void				SetDir( float dir );
	void				SetUpperDir( float dir );
	void				SetLowerDir( float dir );
	void				SetCurDir( float dir );
    void				SetCurDir( D3DXVECTOR3 vDir ){ m_vCurDir = vDir; }
    void				SetCurUpperDir( float dir );
	void				SetCurLowerDir( float dir );
	float               GetCurLowerDir(){return m_fLowerBodyDir;}
	float               GetCurUpperDir(){return m_fUpperBodyDir;}
    D3DXVECTOR3			GetCurDir(){ return m_vCurDir; }

	void				SetDirInt( int nDir );
	int					GetDirInt( void ){ return m_iDir; }
	void				GetPos( float* x, float* y, float* z );
	D3DXVECTOR3			GetPos(){ return D3DXVECTOR3( m_x, m_y, m_z ); }
	float				GetTerrainZ();
	void				GetDir( float* dir );

    int		            GetHp(){ return m_hpinfo.nHp; }
    int		            GetHpMax(){ return m_hpinfo.nHpMax; }
    void	             ClearHPInfo( void ){ m_hpinfo.bIsValid = false; }

    int					GetMp() { return m_charSimpleInfo.nMp;}
    int					GetMpMax() { return m_charSimpleInfo.nMpMax; }
    void				SetMp(int nMp) { m_charSimpleInfo.nMp = nMp; }
    void				SetMpMax(int nMpMax) { m_charSimpleInfo.nMpMax = nMpMax; }
	void				SetMPInfo_MPChange( int nMp );     
    POINT				GetPlayerPos();			//------- �õ����������Ļ����

	//-----------------------------------------------------------------------------------------------
	//Guild
    void				SetGuildId( DWORD dwGuildId, BOOL bClearName = TRUE){ m_dwGuildId = dwGuildId;     if( bClearName ) SetGuildName("");}
    DWORD				GetGuildId(){ return m_dwGuildId; }
    void				SetGuildName( const char* pszName );
    const char*			GetGuildName(){ return m_szGuildName; }
	BOOL				HasGuild(){ return m_dwGuildId != GuildDefine::InitID; }
    //SGuildFlag&			GetGuildFlag()  { return m_stGuildFlag; }
    //void				SetGuildFlag(SGuildFlag& val) { m_stGuildFlag = val; }
    char				GetGangPosition() const { return m_gangPosition; }
    void				SetGangPosition(char val) { m_gangPosition = val; }
	//-----------------------------------------------------------------------------------------------

    void				SetOfficialLevel( BYTE byLevel ){ m_byOfficialLevel = byLevel; }
    BYTE				GetOfficialLevel(){ return m_byOfficialLevel; }
    const char*			GetOfficialTitle();
    void				SetExploit( DWORD dwExploit ){ m_dwExploit = dwExploit; }
    DWORD				GetExploit(){ return m_dwExploit; }

	void				SetGlory( DWORD dwGlory ){ m_dwGlory = dwGlory; }
	DWORD				GetGlory(){ return m_dwGlory; }

	void				SetCountryScore( DWORD dwScore ){ m_dwCountryScore = dwScore; }
	DWORD				GetCountryScore(){ return m_dwCountryScore; }

    // ����
    void				SetReputation( DWORD dwReputation ){ m_dwReputation = dwReputation; }
    DWORD				GetReputation(){ return m_dwReputation; }

    // �ﹱ
    void				SetGuildOffer( DWORD dwValue ){ m_dwGuildOffer = dwValue; }
    DWORD				GetGuildOffer(){ return m_dwGuildOffer; }

    void				SetModelColor( int nColorId ){ m_stColorId = nColorId; }
    short				GetModelColor(void){ return m_stColorId; }

    void				SetVisual( SCharVisual &visual,bool bNeedLoadModel = false );//{ m_equip = equip; }

public:
    BOOL					IsNeedRender()	{ return m_bNeedRender; }
    VOID					SetNeedRender()	;
	DWORD					GetLastRenderTime(){ return m_dwLastRenderTime; }
    VOID					ResetNeedRender();
    void					UpdateBaseData( DWORD time );
	void                    HideOrShowPlayerEffect(bool bShow = true); //lyh++ ���ػ���ʾ��ҵ���Ч
    // ������������
    void					UpdateIntonateDirection();

    // ������������
    void                    UpdateMeDirInFighting();

    //����ˮ����Ч
    void					UpdateWaterEffect();

    void StopRippleEffect(int nRippleEffectID);
    void					LoadRippleEffect();
	void                    LoadWaterSideEffect(); //����ˮ����Ч
	void                    LoadBoatRippleEffect(); //
	void                    LoadRippleIDEffect();

    //��������ϵ���Ч�����õĸ���
    void					UpdateEffectHelper();
    void					UpdateEffectHelper(CCharEffectContainer* pCharEffectContainer);
    //ƽ��֡�Ĵ���
    void					SmoothFrameProcess();
    //���μ��ܵĴ���
    void					HideSkillProcess();
    //�ƶ��Ĵ��� 
    void					MoveProcess();
    //�������ǵ��ƶ�
    void	                RoleMoveProcess();
    void	                RoleMovePathProcess();
    //��������ǵ��ƶ�
    void	                UnRoleMoveProcess();
    //���������ƶ����������赲
    void	                RoleMovingCollision();
    //����ǰ״̬
    void					ProcessCurStatus();
    //�����ƶ�״̬�ı��ʱ��Ķ�������
    void					MoveStatusChangedProcess();
    //���½�ɫ������Ч�����ȣ�jiayi added
    void					UpdateFightPowerEffect();
    //7,8,9��ʱ����Ч, jiayi added
    void					UpdateFullStarEffect();
    void					_UpdateFullStarEffect(float x, float y, bool setScale = false, float scale = 1.0f);
    void					CalcMinimalStar();

    void				Update( DWORD time);
	//��ʾ��ɫ��������Ϣ
	void				ShowChatPaoPao();
	//��ʾ��ɫ�ĸ����̵���Ϣ
	void				ShowPrivateShopInfo();
	//��ɫ�Ķ�������(���ֶ��������ˣ������²���ȷ��)
	void				AnimCorrectProcess();
	//���ǵ���Ϊ����
	void				RoleOperationProcess();
	//���ת��Ĵ���
	void				TurnAroundProcess();
	//������ҵĵ�ǰZ����
	void				UpdateCurZPos();
	//������ҵ���Ծ
	void				JumpingProcess();
	//������ҵ��ܶ���Ч
	void				SoundProcess();
	//��������վ��б�����»�
	void				RoleSlipProcess();
	//����������
	void				UpdateAnimSetting();
	//����NPCͷ������ʾ
	void				UpdateNpcTips();
	//������Ⱦ��Alpha
	void				UpdateRenderAlpha();
	//����״̬��ɫ
	void				UpdateStatusColor();
	//�������������������ʱ��
	void				SpecialIdleTimeProcess();

	void				Render( LPDIRECT3DDEVICE9 pDevice, DWORD dwColor = 0xffffffff, float fTransparent = 1.0f, float fPlayerTransparent = 1.0f );
	void				RenderShadow( LPDIRECT3DDEVICE9 pDevice, DWORD dwColor = 0xffffffff, float fTransparent = 1.0f, float fPlayerTransparent = 1.0f );
	void				RenderChar( LPDIRECT3DDEVICE9 pDevice, BOOL bRenderShadow = FALSE, int* pRetVertexCount=NULL, int* pRetFaceCount=NULL);
	void				ResetMove( DWORD dwSerialNo );

	// cs-->character system
	int					AutoCS( const char* pszSkin = NULL, BOOL bForceLoad = FALSE );
	void				DestroyCS();

	void				UpdateEquip();

	void				UpdateBones();

	void				JumpToMapPos( float x, float y, float z );
	//zֻ���Լ���Ч
	void				JumpToMapPos( float x, float y, float z,float xDir,float yDir );
	void				Destroy();
	
    BOOL                IsMoveStepOver(void);//  �ж��Ƿ���һ�������״̬
    void                StopMovePath(void); //  ��ֹ�߶�

	//��ģ�͹����е�ID
	int					m_iIDInModelMan;

	void				Reset();

	//����·����ʹ��

	void				SetServerZ( float fz );
	bool				IsDeadOver();
	bool				IsDead();
	void				SetCharDead( bool bDead );
	bool				IsActivePlayer(){ return m_bIsActivePlayer; }
	void				DeActive(){ m_bIsActivePlayer = false; }
	
	
	bool				Relive(short shToHell);
	bool				IsTeamMember(const char* name);
	bool				IsInOneTeam();
	bool				IsTeamHeader();
	void				SetDeadOver( bool bDeadOver ){ m_bDeadOver = bDeadOver; }
	
	void				SetAnim( CPlayerAnim* pAnim ){ m_pAnim = pAnim; }
	void				SetMountAnim( CPlayerAnim* pAnim ){ m_pMountAnim = pAnim; }
	void				SetMorphAnim( CPlayerAnim* pAnim ){ m_pMorphAnim = pAnim; }
	CPlayerAnim*		GetAnim(){ return m_pAnim; }
	CPlayerAnim*		GetCurrentAnim();
	CPlayerAnim*		GetMountAnim(){ return m_pMountAnim; }
	CPlayerAnim*		GetMorphAnim(){ return m_pMorphAnim; }
	SAttackInfo*		GetAttackInfo(){ return m_pAttackInfo; }
	POINT				GetTargetMovePos( POINT ptNowPos, POINT ptTargetPos, int iAttackRange );

	void				SetCharInfo( MsgAckCharInfo* pMsg );
	BOOL				IsServerPermitMove(){ return m_bServerPermitMove; }
	void				ServerPermitMove( BOOL b ){ m_bServerPermitMove = b; }

	void				ClearMoveQueue();//����ƶ�����

    enum enumStatus
    {
        //��ͨ״̬
        Player_Status_Normal			= 0
        //����״̬
        ,Player_Status_Intonate
        //ά�ּ���״̬
        ,Player_Status_HoldSkill
        //����״̬
        ,Player_Status_Death
    };
    //
    //�Գ��Լ������Player�ƶ�����
    int						GetPlayerStatus(){ return m_iPlayerStatus; }

	struct StateOnServer
	{
		DWORD	dwTime;
		short	x, y;		// �ڷ������ϵ�λ��
		DWORD	dwState;	// ��ǰ��״̬
		DWORD	dwParams[4];// ����
	};

	SOperation* GetOperation(){ return &m_operation; }

    BOOL    AddOperationIdle(void);
	BOOL	AddOperationUseSkill( int tag_npc, int x, int y, int skillid, int skilllevel );
	BOOL	AddOperationGotoAttackTarget( int tag_npc, int x, int y, int iSkillID, int iSkillLevel = 0);
	BOOL	AddOperationChangeDir( short x, short y  );
	BOOL    AddOperationGotoDropItem( short x, short y  );
	BOOL	AddOperationDoAction(int ActionID);
	void	SwitchSitLoopAnim( DWORD dwTimeOut );
	void	SwitchSitAnim( DWORD dwTimeOut );
	void	SwitchStandAnim();
	void    SwitchMedicalAnim();  //�л���ҩ����

    //״̬�л�����
    void    SwitchActionStatus(CPlayerStatus::STATUS_KEY CurKey, DWORD Delay, CPlayerStatus::STATUS_KEY NextKey = CPlayerStatus::esk_Idle, BOOL bPlayAnim = TRUE );
    //
	BOOL	IsCanPutItem(int x, int y);//�ж�һ���ط��ɷ�ŵ���
	BOOL	TryDropItem( unsigned int nPackIndex );
	BOOL	TryPickItem();
	void	TryPickItem( CPlayer* pItem );
	BOOL	TryTalkWithNpc();
	void	TryTalkWithNpc( CPlayer* pNpc );
	void	TryTalkWithPlayer();//���ǵ�npc������ض�������˵��������������ı�

	void	Face2FaceWithNpc( CPlayer* pNpc );
	BOOL	TryMoveTo();

	//һЩ���ܵ��ж�����
	BOOL	IsCanUseItem(void);//	�жϿɷ�ʹ�õ���
	BOOL	IsCanDoExpression();//�жϿɷ������鶯��
	BOOL	IsTargetIsRight(int skill, int skill_level, int id);
	BOOL    IsCanTalk(int iDestID);					//	�ж��ܷ�Ի�

	BOOL	IsSkillCanUse( ItemDefine::SItemSkill* pSkill );
	BOOL	IsSkillCanUseExceptActionAndTime( ItemDefine::SItemSkill* pSkill,
											bool bCheckOnly = false );
    BOOL    IsSkillCanUse(int skill_id, int skill_level);    //�ж�Ī�����ܿɷ�ʹ��
	BOOL    IsSkillCanUseExceptActionAndTime(int skill_id, int skill_level); //����ʱ�䣬��״̬���ж����ܿɷ�ʹ��

	BOOL	IsSkillCanUseStatus( int skill_id, int skill_level );

    BOOL    IsTagCanBeAttack(void); //�ж�Ŀ��ɷ񹥻�
    BOOL    IsCanMove(void);        //�жϿɷ��ƶ�
	BOOL	IsCanJump(void);		//�ж��Ƿ���Ծ
	BOOL    IsPlayerCanChangeToStatus(int next_status);//	�ж�player�ܷ�ı䵽Ŀ��״̬
    BOOL    IsPlayerCanChangeStatus(void);//  �ж�һ������Ƿ���Ըı�״̬(����)
	//��npc������С�����Ķ���
    BOOL    OperNothing(void);
    BOOL    OperIdle(void);        //����
    BOOL    OperUseSkill(void);    //ʹ�ü���
    BOOL    OperTalk(void);        //�Ի�
    BOOL    OperGetItem(void);     //ȡ�õ���
	BOOL    OperDropItem(void);	   //��������
    BOOL    OperTrade(void);       //����
	BOOL    OperChangeDir(void);	//ת��
    BOOL    OperMoveSkill(void);   //�ƶ���ȥʹ�ü���
	BOOL    OperMoveDroptem(void); //�ƶ���ȥ��������
	BOOL	OperDoAction(void);		//��Ī������

    //һЩ״̬���ƺ���
    //
    void    ActionStatusIdle(void);         //����
    void    ActionStatusPickItem(void);	    //�����
    void    ActionStatusDropItem(void);		//��������
    void    ActionStatusTalk(void);         //�Ի�
    void    ActionStatusTrade(void);        //����
    void    ActionStatusMove(void);         //�ƶ�
    void    ActionStatusChangeDir(void);	//ת��
    void    ActionStatusPreAttack(void);    // Ԥ������״̬
    void	ActionStatusPreIntonate(void);
    void	ActionStatusHoldSkill(void);
    void    ActionStatusAttack(void);       // ����״̬
    void    ActionStatusIntonate(void);		// �ʳ�
    void    ActionStatusBeAttack(void);     // �ܻ�״̬
    void    ActionStatusMiss(void);         // ����״̬
    void    ActionStatusSleep(void);        // �赹״̬
    void    ActionStatusDie(void);          // ����״̬
    void    ActionStatusBeatBack(void);	    // ����
    void    ActionStatusActionTime(void);	//��һ��ʱ������Ī������

	void     SetSpineBoneID(int id) { m_nSpineBoneID = id;}
	void     SetRightHandBoneID(int id) { m_nRightHandBoneID = id;}
	void     SetLeftHandBoneID(int id) { m_nLeftHandBoneID = id;}
	void     SetBackBoneID(int id) { m_nBackBoneID = id;}


	//ʹ�ü���
	BOOL	TryUseSkill( CPlayer* pTagPlayer, ItemDefine::SItemSkill* pSkill,
						bool bCheckOnly = false, bool bNoTip = false );
    //
	D3DXMATRIX* GetTransform(){ return &m_matTransform; }
	void	SetTransform( D3DXMATRIX* pMatrix ){ m_matTransform = *pMatrix; }
	
	//
	void	SetPrivateInfo( const bool bOpen, const char* szInfo );
	std::string& GetShopName(){ return m_strShopName; }
	void	SetShopName( const char* pszShopName, DWORD dwColor );
	ControlText* GetPrivateShopInfo(){ return m_pPrivateShopInfo; }


    void                SetForceTurnRole( BOOL bTurn ){ m_bForceTurnRole = bTurn; }

	void AutoDisMount(ItemDefine::SItemSkill* pSkill = NULL);
	//
private:
    //���״̬��Ч
    BOOL					FindStatusEffect( int nStatusID, int nLevel );

    //���״̬��Ч
    void					AddStatusEffect( int nStatusID, int nLevel, int nEffectID );

    //����ά�ֵ���Ч
    void					ClearUnkeepStatusEffects();

    //����ά�ֱ�־
    void					ResetStatusEffectsKeepFlag();

	//������״̬��Ч
	bool                    ClearStatusEffect( int nStatusID, int nLevel );

public:
//     BOOL					RandomVisual();
//     BOOL					ChangeAvatar( const char* pszFilename );

    CCharEffectContainer*	GetCharEffectContainer(){ return m_pCharEffectContainer; }

    void					CastModelEffect( CWSModelEffect* pEffect, CPlayer* pTargetPlayer = NULL, int nSlot = 0 );
    void					CastModelEffect( CWSModelEffect* pEffect, CCharEffectContainer* pCharEffectContainer, CPlayer* pTargetPlayer = NULL, int nSlot = 0 );
    void					CastHitFlashEffect( CHitFlashEffect* pEffect );
    void					CastMissileEffect( CMissileEffect* pEffect, CPlayer* pTargetPlayer );
    void					CastChainLightingEffect( CChainLightingEffect* pEffect, CPlayer* pTargetPlayer = NULL );
	void                    CastChainEffect( CChainEffect* pEffect,CPlayer* pTargetPlayer = NULL);
    void					SetCharEffectContainer( CCharEffectContainer* pCharEffectContainer );
    // �Ƿ�ָ����ҵĸ����̵���Ϣ����
    bool					IsPtInPrivateShopInfo( int x, int y );
	void					SetSeekEquipInfo( SCharItem aItem[] ){  memcpy( m_equipitemSeekEquip, aItem, sizeof( SCharItem ) * EEquipPartType_MaxEquitPart ); }
    SCharItem*				GetSeekEquipInfo(){ return m_equipitemSeekEquip; }

    void					PlayNormalAttackSound( ItemDefine::SItemSkill *pSkill );
    void                    SetMapEffectId(int nEffectId){m_MapEffectId = nEffectId;}
    int                     GetMapEffectId(){return m_MapEffectId;}


	//////////////////////////////////////////////////////////////////////////
	// ����
	void	InitFiveElementEffect();
	void	UpdateFiveElementEffect();
	void	_UpdateFiveElementEffect(bool setScale = false, float scale = 1.0f);
	void	UpdateMainElement();
	void	CheckSuitForFiveElement();

	// �Ǽ���������Ⱦ����Ϸ�����в���Ҫ���ã�ֻ�����Խ�����ʹ�á�
	void	_RenderFiveElement();
	void	_RenderFullStarEffect();
	//////////////////////////////////////////////////////////////////////////

	bool	IsPrivateShopOpen() { return m_bPrivateShopOpen; }

	bool	IsHide() { return m_bHide; }
	void	SetHide(bool bHide);

	D3DXVECTOR3			m_vDir; //��ɫ�ĳ���
	D3DXVECTOR3			m_vPos; //��ɫ��λ��
    short               m_shGuildTitle;
    short               m_shInfluence;
	std::string				m_szReputeName;

	bool                m_bHasRelive;//�����������������һ��HITPONIT����ᱻ����ȡ��
protected:
	struct NpcCoordInfo* m_pNpcCoordInfo;

    enum eHeadInfo
    {
        eHeadInfo_Name = 0,
        eHeadInfo_Hp,
        eHeadInfo_Mp,
        eHeadInfo_Title,
        eHeadInfo_Guild,
        eHeadInfo_Tong,
        eHeadInfo_Chat,
        eHeadInfo_Count
    };

    bool				IsShow( eHeadInfo eType );

    char            m_pTempMapName[200];        //��ʱ�ӵ���������ڳ�������

	SOperation			m_operation;		//��������
	MsgAckCharInfo		m_charSimpleInfo;
	bool				m_bDead;
	bool				m_bWillDie;
	bool				m_bDeadOver;
	bool				m_bIsActivePlayer;
	DWORD				m_dwDeadTime;
	// �����Ǹով����˹����������Ҫ�ƶ���
	// �����������������
	// ��Ϊ����ϵͳ�Ĵ��ڣ���ɫ������һ���Ժ�ܿ��������ֻ���һ��
	// ��Ȼ�ͻ��˽���˽�Ӳʱ�䣬���Ƿ����������̲������µ�״̬��
	BOOL				m_bServerPermitMove;
	//
	float				m_x, m_y, m_z, m_dir, m_fUpperBodyDir, m_fLowerBodyDir;
	float				m_tx, m_ty, m_tz, m_tdir, m_fTargetUpperBodyDir, m_fTargetLowerBodyDir;
	// ��һ��ȡZʱ�õ�ֵ
	float				m_fLastGetZ_x, m_fLastGetZ_y, m_fLastGetZ_z;
	// ���ƶ�����Ϊ��ֹ����ģ��floor�£�ÿ��m_usUpdateZFrameCount֡����һ�Σ�m_usUpdateZFrameCountȡֵ����[50-100]
	unsigned short		m_usUpdateZFrameCount;
	// �����һ֡λ���뵱ǰ֡��ͬ������
	unsigned short		m_usSamePosFrameCount;

	//�ڷ������ϵ�Z����
	float				m_fServerZ;

	// Player���ڵĵ���߶�
	float				m_fTerrainZ;

	// �ϰ���ĽǶ�����
	float				m_fUpperBodyDirCorrect;

	D3DXVECTOR3 m_vCurDir; // ��ɫ�ĵ�ǰ����
	int					m_iDir;
    BOOL                m_bForceTurnRole;   // 2.5D�ӽ�ǿ����ת����
	
	D3DXMATRIX			m_matTransform;

	POINT				m_ptLoc;
	//POINT				m_ptLocFromAttMsg;
	
	//�Ƿ�����
	BOOL				m_bRole;
	int                 m_EffectID; //װ��ǿ��id ��������������Ч
	char               m_EffectName[EFFECTPATCHLEN]; //lyh�����Ч��ʾ�ļ�·��
	int                m_HeroKillTargetNum; //lyh++
	bool               m_HeroKillHasChanged;
	int                m_EffectCharSkillID;
	// ������Σ�ֻ��һ����ǰ������

	short				m_stCharType;
	short				m_stFaceIcoId;

	short				m_stMonsterType;
	short				m_subMonsterType;
	BOOL				m_isPet;
	
	// ����˵�Id
	GameObjectId				m_stID;
	//NpcID
	int                 m_nNpcId;              

	//����ID
	bool				m_bHadGotValidGuildInfo;
	// ����id
	DWORD				m_dwGuildId;
	// ��������
    char				m_szGuildName[GuildDefine::MaxNameLength  + 1];
    bool                m_bGuildIsCityMaster;
	//SGuildFlag			m_stGuildFlag;                    // ��������
	char				m_gangPosition;                // ְλEGangPosition
    //	�����ID
    int					m_nMonsterID;

    int					m_nModelId;
    //��ɫ����
    int					m_iCountry;

	uint8				m_iRealCountry;		// ����				added by zhuomeng.hu		[9/9/2010]
	uint16				m_iCountryTitle;	// ���ҳƺ�			added by zhuomeng.hu		[9/9/2010]
    uint16              m_iPortraitId;      // ͷ��ID           added by ZhuoMeng.Hu		[9/19/2010]

	uint32				m_iFamilyID;		// ����id����idΪ0����Чid
	int8				m_iFamilyPos;		// ����ְλ

    DWORD				m_dwCharacterID;	// ��ɫDBID

	GuildIcon		m_strGuildIcon;
	// ���εȼ�
	BYTE				m_byOfficialLevel;
	
	// ��ѫֵ
	DWORD				m_dwExploit;
	// ����
	DWORD				m_dwReputation;
	// �ﹱ
	DWORD				m_dwGuildOffer;

	// ����
	DWORD				m_dwGlory;

	// ս������
	DWORD				m_dwCountryScore;

	bool				m_bOpenPrivateShop;
	float				m_fOldPrivateShopX;
	float				m_fOldPrivateShopY;

	ControlText			*m_pPrivateShopInfo;
	bool				m_bPrivateShopOpen;	
	std::string			m_strShopName;

	char				m_szName[dr_MaxPlayerName];
	char				m_szDisplayName[ dr_MaxPlayerName ];
	std::string			m_szFinalName;

	short				m_stColorId;

	CPlayerAnim*		m_pAnim;					//���ﶯ��
	CPlayerAnim*		m_pMountAnim;				//���ﶯ��
	CPlayerAnim*		m_pMorphAnim;				//���嶯��

	int					m_nSpineBoneID;				//�����������Ĺ���λ��
	int					m_nRightHandBoneID;			//���������λ��
	int					m_nLeftHandBoneID;			//���������λ��
	int					m_nBackBoneID;				//������Чλ��

    FLOAT					m_vSaveXYGetZ;
    int						m_iPlayerStatus;

    //��������
    float					m_fBodySize;
    float					m_fBodyLengthSize;
    float					m_fWeaponAttackRange;
    short					m_ustWeaponAttackRange;
    //��ͨ�����ķ�����ЧID,set in CPlayerAnim::ChangeSkeletonAndEquipAll
    int						m_iShotEffectID;
    int						m_iWeaponType;
    BOOL					m_bNeedRender;
	DWORD					m_dwLastRenderTime;
    bool					m_bHasUpdateAnim;			// ģ�ͼ����꣬��UpdateAnimSettingִ�к�����Ⱦ
    bool					m_bNpcGetBodySize;			// Npc�������ֵ
    uint32					m_stTeamId;
    char					m_cTeamPosition;
	bool					m_bHide;					// �Ƿ���ʾ��Ŀǰ������NPC

    CCharEffectContainer* m_pCharEffectContainer;

	//add by yanli  2010-9-27		
	//all equipment
	CPlayer_SEquipment			m_equips[eKeyAll_Max];

    // seek equipʱ������װ����Ϣ������ʱװ
    SCharItem m_equipitemSeekEquip[EEquipPartType_MaxEquitPart];

	//Ч��NPC
	DWORD				m_dwDisplayAfterTime;
	DWORD				m_dwLastUpdateTime;

	// npc ר��
	int					m_nNpcTipsType;
	int					m_nImageType;

    // ͷ���ϵĶԻ���
    ControlText		*m_pChatPaoPao;
    int				m_nOldChatDialogBoxX;
    int				m_nOldChatDialogBoxY;
    DWORD			m_dwChatDialogBoxBornTime;
    DWORD			m_dwChatDialogLifeTime;

    //�����״̬��Ч�ṹ
    struct SStatusEffect
    {
        int		nStatusID;			//��״̬��ID���	
        int		nLevel;				//��״̬�ĵȼ�
        int		nEffectID;			//��Ч�������ڵ�ID
        BOOL	bEffectKeep;		//��Ч�Ƿ�ά��
		IEffect* pEffect;           //������Чָ�룬��ҪĿ�������ж�ɾ����Чʱ��ͨ��nEffectID��õ�ָ���Ƿ���ͬ

        SStatusEffect()
        {
            nStatusID = -1;
            nLevel = -1;
            nEffectID = -1;
            bEffectKeep = FALSE;
			pEffect = NULL;
        }
    };

    //���������״̬��Ч
    typedef std::list<SStatusEffect>        StatusEffectContainer;
    typedef StatusEffectContainer::iterator ItrStatusEffectContainer;
    StatusEffectContainer m_listStatusEffects;

	//////////////////////////////////////////////////////////////////////////
	// �������
	// added, jiayi, [2010/3/11]
	struct FiveElementEffectHelper
	{
		FiveElementEffectHelper(){
			m_nEffectId = -1;
			m_nEffectContainerId = -1;
		}
		int m_nEffectId;
		int m_nEffectContainerId;
	};
	FiveElementEffectHelper m_FiveElementEffectIds[ItemElements_End];
	bool m_bNeedUpdateFiveElement;
	int m_nMainElement; // ��ҪԪ�أ�-1ʱΪ����ʾ
	int m_nMaxElementCount; // ��ҪԪ��ǿ�ȣ�������
	//////////////////////////////////////////////////////////////////////////
	//
	struct SMove
	{
		BOOL			bHalfStep;					//�Ƿ��ߵ�һ�룬���Ϊfase������Ϊ�µ�һ����ʼ
		DWORD			dwTimeLeft;					//��һ���Ķ���ʱ��
		DWORD			dwStartTime;				//��ʼ�ߵ�ʱ��
		DWORD			dwStepTime;					//һ����ʱ��
		D3DXVECTOR3		vStartPos,vEndPos;			//��ʼλ�ã�����λ��,(��������)
        POINT           tEndPoint;                  //�ƶ���Ŀ��λ��(ͼ�ؼ���)
		float			fVelocity;					//�ٶȣ�ÿ��?��
		SMove()
		{
			bHalfStep = FALSE;
		}
	}m_move;

	struct HitPoint
	{
		short stDamage;
	};

    int		m_MapEffectId;
    //�ƶ��ٶ�
    float	m_fMoveRate;
    float	m_fCurMoveRate;
    float	m_fMovingStep;
    float   m_fRunStep;
    float	m_fSwimStep;
    BOOL    m_bMoveRateChange;

    float	m_fNormalAttackRate;
    unsigned short m_ustExact;
    unsigned short m_ustDodge;
    unsigned short m_ustLuck;
    unsigned short m_ustLevel;
    unsigned short m_ustTargetLevel;
    short m_stShortAtt;
	short m_stFarAtt;
    short m_stPhysicDefMax;
    short m_stPhysicDefMin;
    //���������ϸ��ӵ�ս��״̬
    SCharBuff	stBodyStatus[BodyStatusType_Max];	//�����������е�״̬,��¼����
    SkillRuntimeDesc m_skillRuntimeDesc;

    /*SCharItem m_CharEquipItem[EPT_MaxEquitPart];*/


    //
// 	bool    GetNextStep(void);
	// ��ǰ����ʹ�õ�attack info
	SAttackInfo*				m_pAttackInfo;
	//
	short			GetMovingType( float fCurDir, float fMovingDir );
	//Action����ʱ��
	void			HandleActionQueue( bool bSkipStatus = false );
	void			HandleMoveQueue( BOOL bHang = FALSE );
	////////
	CMoveQueue				m_MoveQueue;		//	�ƶ�����
	CMoveQueue::SMove		m_NowMove;	//	��ǰ���ƶ�
	////////
	CActionQueue	m_actionQueue;      //	npc����Ϊ��ջ...�������������������Ϊ...
    CActionQueue::SAction   m_NowAction;//	npc��ǰ����ִ�е���Ϊ��pop�������¼

	//��ɫ�ս��������Ұ��ʱ�򣬲���֪��Ѫ��
	//ĳЩ�������� �������·� ��ǰѪ��
	//		������ ���ڽ�ɫ֮��
	//		��ҵ�ǰ�Ĺ�������
	//		
	//���������ܿ����� ��ɫ������ ��Ѫ
	//���Բ���ÿ�ض���ѯ

	//ĳЩ����£�����Ѫ���仯
	//		��:��ɫ����
	//			
    //��ʱҪ���´ӷ�������ȡѪ��

	//TODO ext:��Ӷ��ѵ�Ѫ��
	//	   ��ɫ��ҩ��ɵ�Ѫ���仯����Ҫ�·�

	struct SCharHPInfo
	{
		int nHp, nHpMax;

		//short stHP,stHPMax;

		//Ѫ���Ƿ���Ч
		bool bIsValid;

		//��ǰ��ʾ��percent
		float fShowPercent;
		//ǰһ��Ѫ��
		float fPrevPercent;
		//��Ҫ�����
		float fTargetPercent;
		//fPercent * fTargetPercent + (1-fPercent)*fPrevPercent;
		//fPercent�ٶ�:0.002
		float fPercent;
		DWORD dwLastShow;
		//
		SCharHPInfo()
		{
			nHp = 100;
			nHpMax = 100;
		}
	}m_hpinfo;
	
	//
	unsigned char  m_ucSitStatus;	//���ڵ��ϵı�־
	unsigned char  m_ucSitInterrupt;//���±���ϵı�־
	unsigned char  m_ucFightStatus;	//ս��ģʽ
	unsigned char  m_ucSex;			//�Ա�
	unsigned char  m_ucProfession;	//ְҵ
	//
	unsigned char  m_ucToFightStatus;//��Ҫ�л�����ս��״̬
	//
	//�Ƿ���ʾѪ��
	bool m_bShowHP;
    
    unsigned char m_ucLiftFlagStatus;   // ����״̬

public:
	BOOL	HasAttackActionQueue(){ return m_actionQueue.GetAttackActionNum(); }

private:
	BOOL	RoleMoveToShore( D3DXVECTOR3& vNextPos, D3DXVECTOR3& vNextDir, BOOL& bCollision, float fRoleHeight, float fCurMoveDist );				//�����ܷ��ƶ�������

	DWORD m_startfeartime;
	D3DXVECTOR3 m_vTargetPos;

	D3DXVECTOR3 m_vTeamFollowLastPos;	//��Ӹ�����һ�εĸ���ص�

//----------- ��ʾ�����������С����  -----------
public:
    static void SetServerTerrainRectShow( bool bShow );
    static void SetHeightMapRectShow( bool bShow );
    static void SetMyCircleShow( bool bShow, float fR );
    static void SetMouseCircleShow( bool bShow, float fR );
    static bool IsHeightMapDataLoad();
    static bool IsServerTerrainRectShow();
    static bool IsHeightMapRectShow();
    static bool IsMyCircleShow();
    static bool IsMouseCircleShow();

    static DWORD GetColorByAHSL( float fAlpha, float fHue, float fSaturation, float fLighteness );

private:
    static void ReleaseHeightMapData();
    static bool LoadHeightMapData();
    static void DrawServerTerrainRect( CPlayer* pPlayer );
    static void DrawHeightMapRect( CPlayer* pPlayer );
    static void DrawMyCircle( CPlayer* pPlayer );
    static void DrawMouseCircle( CPlayer* pPlayer );
    static void DrawTerrainCircle( float fCenterX, float fCenterY, float fR, DWORD dwColor );

    static float Hue2RGB( float v1, float v2, float vH );

    static bool m_bShowServerRect;
    static bool m_bShowHeightMapRect;
    static bool m_bShowMyCircle;
    static bool m_bShowMouseCircle;
    static float m_fMyCircleR;
    static float m_fMouseCircleR;
    static bool m_bHeightMapLoad;
    static CHeightMapData* m_pHeightMapData;
    static CBaseGraphics::Vertex3D m_vtHeightMapRect[ HEIGHTMAP_SHOW_RECT_CNT * HEIGHTMAP_SHOW_RECT_CNT * 6 ]; // ֻ��ʾ�����45*45����
//-----------------------------------------------

public:

	//
	//	���������͹����Ĺ���ʧ�ܵ���Ϣ����
	bool				ServerAttackFailProc(void);

    bool                m_isOfflineStall ;
	void				AddDeathTask();
	BOOL				IsNpc(){ return m_stCharType == Object_Npc; }
	BOOL				IsItem(){ return m_stCharType == Object_Item; }
	BOOL				IsPlayer(){ return m_stCharType == Object_Player; }
    BOOL				IsMonster(){ return m_stCharType == Object_Monster; }
    BOOL				IsEffect(){ return m_stCharType == Object_Effect; }
	BOOL				IsPet(){ return m_isPet; }

	BOOL				IsItemDropDelayOver(void)
	{
		if( IsItem() )
        {
            if( HQ_TimeGetTime() >= m_dwDisplayAfterTime )
			    return TRUE;
            else
                return FALSE;
        }
        else
            return TRUE;
	}



	void				SetPet(BOOL b) { m_isPet = b; }
	void				SetMonsterType( short stMonsterType ){m_stMonsterType = stMonsterType;}
	short				GetMonsterType(){ return m_stMonsterType; }
	void				SetSubMonsterType(short stSuMonsterType) {m_subMonsterType  =stSuMonsterType; }
	short				GetSubMonsterType() {return m_subMonsterType;}
	bool				IsMonsterType(short stMonsterType);
	bool				IsCollection(bool bEnsure = true);
	bool				IsDisableCollection();
	int					m_nCollectionEffectID; // 
    bool                m_bCanPick; // ���ǿ��Լ�m_stCharType������eItem_CHAR����

	bool				EnsureCollection( bool bRet );
	void				SetCharType( short stCharType ){ m_stCharType = stCharType; }
	short				GetCharType(void){ return m_stCharType; }
	void				SetMoveRate( float fMoveRate )
    {
        if( m_fMoveRate == fMoveRate )
            return;
        m_fMoveRate = fMoveRate;
        m_fCurMoveRate = fMoveRate;
        m_bMoveRateChange = TRUE;
    }
	float				GetMoveRate()	{ return m_fMoveRate; }
	void				SetMovingStep( float fMovingStep ){ m_fMovingStep = fMovingStep; }
	float				GetMovingStep(){ return m_fMovingStep; }
    void                SetRunStep(float fRunStep){m_fRunStep = fRunStep;}
    float               GetRunStep(){return m_fRunStep;}
	void				SetReputeName(char* szRepute,DWORD curID,GameObjectId playerid,SRankManager rkmgr);
	float               GetNormalStep();
	void                DelReputeName(DWORD curID,GameObjectId playerid,DWORD delIndex);

	void				SetSwimStep(float fSwimStep){m_fSwimStep = fSwimStep;}
	float				GetSwimStep(){return m_fSwimStep;}
	void				SetNormalAttackRate( float fNormalAttackRate ){ m_fNormalAttackRate = fNormalAttackRate; }
	void                SetShortAtt(short stShortAtt){m_stShortAtt = stShortAtt;}
	void                SetFarAtt(short stFarAtt){m_stFarAtt = stFarAtt;}
	void				SetPhysicDefMax ( short stPhysicDefMax ){ m_stPhysicDefMax = stPhysicDefMax; }
	void				SetPhysicDefMin ( short stPhysicDefMin ){ m_stPhysicDefMin = stPhysicDefMin; }
	void				SetExact ( unsigned short ustExact ){ m_ustExact = ustExact; }
	void				SetDodge ( unsigned short ustDodge ){ m_ustDodge = ustDodge; }
	void				SetLuck ( short stLuck ){ m_ustLuck = stLuck; }
	float				GetAttackRate() { return m_fNormalAttackRate; }
	unsigned short		GetExact() { return m_ustExact; }
	unsigned short		GetDodge() { return m_ustDodge; }
	unsigned short      GetLuck(){ return m_ustLuck; }  
	short               GetShortAtt(){return m_stShortAtt;}
	short               GetFarAtt(){return m_stFarAtt;}
	short				GetPhysicDefMax() { return m_stPhysicDefMax; }
	short				GetPhysicDefMin() { return m_stPhysicDefMin; }
	unsigned short      GetTargetLevel(){ return m_ustTargetLevel; }
	void                SetTargetLevel( unsigned short ustLevel ){ m_ustTargetLevel = ustLevel; }
	void                SetLevel(unsigned short ustLevel){m_ustLevel = ustLevel;}
	unsigned short      GetLevel(){return m_ustLevel;}

	//void                SetCharEquipItem(short stIndex,SCharItem *pitem)
	//					{
 //                           if( stIndex >= 0 && stIndex < EPT_MaxEquitPart )
	//						    memcpy(&m_CharEquipItem[stIndex],pitem,sizeof(SCharItem));							 
	//					}
	
	/*SCharItem *GetCharEquipItem(short stIndex){ return &m_CharEquipItem[stIndex];}*/

	BOOL				IsRole(){ return m_bRole; }

	void				WillDie(){ m_bWillDie = true; }
	bool				IsWillDie(void){return m_bWillDie;}
	void				ClearDeath();

	void				SetDisplayAfterTime( DWORD dwTime ){ m_dwDisplayAfterTime = dwTime; }
	void				SetDeadOverTime( DWORD dwTime ){ m_dwDeadOverTime = dwTime; }
	DWORD				GetDeadOverTime(){ return m_dwDeadOverTime; }

	void    SwitchAnim(CPlayerStatus::STATUS_KEY PreStatus, DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);    //�л�����Ҫ״̬�Ķ���

	void				Dead();

	bool				IsOpenPrivateShop(){ return m_bOpenPrivateShop; }

	//	bTooClose�����Ƿ�����С������Χ֮��
	bool				IsInAttackRange( float fTargetX, float fTargetY, float fTargetBodySize, ItemDefine::SItemSkill *pSkill, BOOL* bTooClose=NULL );
	bool				IsInAttackRangeOnlyTwoPoint( float fTargetX, float fTargetY, float fTargetBodySize, ItemDefine::SItemSkill *pSkill, bool bCalibrate = false, BOOL* bTooClose=NULL );
	BOOL				IsTargetInFront( float fTargetX, float fTargetY, float fTargetZ, float fAngleMax = D3DX_PI/2 );

	float				GetDistToTarget( float fTargetX, float fTargetY );

public:
	CActionQueue*		GetActionQueue(){ return &m_actionQueue; }
	CMoveQueue*			GetMoveQueue(){ return &m_MoveQueue; }
	//��һЩ�������������Ļ�����Ϊ���е�ִ��
	void				Expression(ExpressionInfo* pInfo);
	bool				Attack( SAttackInfo* pAttackInfo, bool bMustToDo = false );

	void				Intonate(IntonateInfo* pIntonageInfo);
	void				HoldSkillEnd();
	void				HoldSkillCancel();
	void				HoldSkillOneHit();
	void				BeAttacked(void);

	void				EndExpression(ExpressionInfo* pInfo){};
	void				EndIntonate(IntonateEndInfo* pInfo);
	void				EndAttack( SAttackInfo* pAttackInfo );
	void				EndMoveAStep( BYTE byDir );

    void                StopWalk();

public:
	BuffStatusManager	m_cFightStatus;
	SkillRuntimeDesc*	GetSkillRuntimeDesc(){ return &m_skillRuntimeDesc; }
	BOOL				ReqCancelSkill();
	BOOL				CancelSkill();

	void				SetNpcTipsType( int nType ){ m_nNpcTipsType = nType; }
	int					GetNpcTipsType(){ return m_nNpcTipsType; }
	//

	void	SetShowFlag( DWORD dw ){ m_dwShowFlag = dw; }
	DWORD	GetShowFlag(){ return m_dwShowFlag; }
	
public:
	void				ClearEffStatus();		//���״̬��Ч
	bool				IsWillPlayDropAnim(){return m_bItemPlayedDropAnim;	}
	void				SetWillPlayDropAnim(bool value){m_bItemPlayedDropAnim = value;}
private:
	
	void CaluHPPercent(void);

	DWORD m_dwDeadOverTime;

	//���ü���
	int		m_iRef;
	//��Ҫɾ��
	bool	m_bNeedToDelete;
	//
	DWORD	m_dwShowFlag;
	// ս��״̬
	DWORD			m_dwFightFlag;
	BOOL			m_bPendingClearFightFlag;	// ս������δ���꣬��ʱ����ս����QL��2009/04/25
	enum FIGHTCHANGE
	{
		eNoChangeFight,
		eChangeFightAll,
	};
	DWORD			m_dwFightChangeFlag;
	DWORD			m_dwFightChangeTime;
	DWORD			m_dwFightChCurrTime;
	
	struct SSound
	{
		DWORD dwLastUpdate;
		CCreatureSound::HCREATURESOUND hSound;
	}m_sound;

	void	PlayCreatureSound( CCreatureSound::enumCreatureSound sound );
	void	UpdateSound( void );

	const char*	m_pWeaponSound;
	const char*	m_pArmourSound;

public:
	BOOL	AddFightFlag( EActionFlag flag , BOOL bIsPlayAmin = TRUE, BOOL IsReEquip = TRUE );
	void	ChangeToFightPose();
	bool	HasFightFlag( EActionFlag flag ){ return _HAS_FLAG(m_dwFightFlag, flag); }
	BOOL	ClearFightFlag( EActionFlag flag, BOOL  bIsPlayAmin = TRUE, BOOL IsReEquip = TRUE );
	void	SetPendingClearFightFlag(BOOL bPendingClear) { m_bPendingClearFightFlag = bPendingClear; }
	void	TurnCameraToPlayer( DWORD time );	//ʹ����������������ﳯ��һ��

	//lyhά�ּ��ܶ�������
	bool GetSkillAnimLoopCnt(int &Times ,ItemDefine::SItemSkill * _skill); 

	// �ܷ��������
	BOOL	NeedVerifyPos( D3DXVECTOR3 vPos, float fVerifyRange = NeedVerifyDistance );
	void	ReSetPos( float fx, float fy, float fz );

	void	SetWeaponSound( const char* pWeaponSound );
	const char*	GetWeaponSound();
	void	SetArmourSound( const char* pArmourSound );
	const char*	GetArmourSound();

	//׼����������
	void	ReadyToLaunchSpecialSkill( short shStartPermillage );
	//��ͣ׼��
	void	CancelReadyToLaunchSpecialSkill();
	//��ʼ���ܵ��Ƽ�ʱ
	void	StartCountDownSpecialSkill();

	//ֹͣ�ƶ�
	void	StopMoving(bool bAction =false);
	//���Ķ���
//	void	SwitchSitAnim(DWORD dwTimeOut);
	//�л�����Ī������
	void	SwitchActionAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л��������Ķ���
	void    SwitchDieAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л����������������
	void	SwitchDieOverAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л������ߵĶ���
	void	SwitchWalkAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л������˶���
	void	SwitchWalkBackWardsAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout, DWORD dwBlendingTime = 0);
	//�л���ת����
	//void	SwitchShuffleAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л�������ת��Ķ���
	void	SwitchShuffleLeftAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л�������ת��Ķ���
	void	SwitchShuffleRightAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л����ܲ��Ķ���
	void    SwitchRunAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л�����Ӿ�Ķ���
	void	SwitchSwimAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л���ˮ�д����Ķ���
	void	SwitchSwimIdleAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л�����������
	void	SwitchJumpAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л������趯��
	void	SwitchGlide(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л������䶯��
	int	SwitchDropAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);		// ����Drop�����Ĳ���ʱ��
	//�л���׼����ɫ�����ж���
	void	SwitchReadyToSpecialAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л���ɫ���ж���
	void	SwitchSpecialAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
    //�л�����������
    void    SwitchIdleAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout, DWORD dwBlendingTime = MexAnimCtrl::eDefaultBlendingTime);
	//�л���ѣ�ζ���
	void	SwitchStunAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л��������������
	void	SwitchSpecialIdleAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
    //�л���ս������
    void    SwitchAttackAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	BOOL	SwitchAttackAnim( unsigned short ustSkillId, unsigned short ustSkillLevel, DWORD* pGetHitPointTime = NULL, DWORD* pGetEndFrameTime = NULL );
	//�л���ʩ������
	void	SwitchSpellAnim( DWORD dwEmissionFlyTime, GameObjectId ustTargetId, unsigned short ustSkillId, unsigned short ustSkillLevel, DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//�л����ʳ�����
	void	SwitchIntonateAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	void	SwitchIntonateAnim(DWORD dwTimeOut, ItemDefine::SItemSkill* pSkill );
	//����Ŀ����Ч
	void    PlaySpellEffect(DWORD dwEmissionFlyTime,GameObjectId ustTargetId,unsigned short ustSkillId,unsigned short ustSkillLevel,DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);

	//Pick
	void	SwitchPickAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout );
	//�л�����������
	void	SwitchHoldSkillAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout );
	//�л�����ܶ���
	void	SwitchDodgeAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout );
	//�л�����������
	void	SwitchHurtAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout );
	//�л��񵲶���
	void	SwitchDefendAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout );
	//�л����ε�
	void	SwitchScabbardAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout, BOOL bPlayScabbard = TRUE );
    // �л������춯�����ϰ���
    void    SwitchLiftFlagAnim();
    // ����ӵ������
    void    SwitchEmbraceAnim();
	//���Ÿ����
	void    SwitchReliveAnim();
	// ���ŵ��䶯����Ҫ������Ʒ
	void    SwitchDropItemAnim();

	void	PlayAnim( const char* szName, int nTimes, const char* szEndName );

	// ����gamesetting�����õĶ�������������������npc�ɼ��ȣ�
	void PlayAnimWithActionID();
	void SetWithNPCAnimInfo( int nActionID, DWORD dwDuringTime );
	//
	void Render( LPDIRECT3DDEVICE9 pDevice );

	void UpdateFootPrint();
	bool IsNeedShowShadowDecal();
	void RenderInfo(LPDIRECT3DDEVICE9 pDevice, int x, int y);
	void RenderText(LPDIRECT3DDEVICE9 pDevice);
	void RenderText2D( LPDIRECT3DDEVICE9 pDevice );
	void RenderChatInfo();
	void RenderPrivateShopInfo();
	void RenderTeamFlag();
	void RenderTeamBattleFlag();
	void RenderRankTitle();
	void RenderCountryTitle();

	//////////////////////////////////////////////////////////////////////////
	CPlayerEx	m_status;

	void SetPetNameColor(CPlayer* pMaster, DWORD& color);
	void SetNameColorByInfluence(DWORD&);
    // �����ǰ�Ķ�������
    void ClearActionQueue();

	//�趨 ĳ����λ��װ��
	void SetEquip( short stWhere,SCharItem *pItem );
	//�趨 ���е�װ��
    void CPlayer::SetAllEquip( SCharVisual* pVisual, bool isautocs = true );
	/*void SetEquipByItemID(short stItemID[EPT_MaxEquitPart], short equipIntensifyTime[EPT_MaxEquitPart], short equipIntensifyStar[EPT_MaxEquitPart], short equipElements[EPT_MaxEquitPart], CPlayer_SEquipment* pEquip);
	void EquipByItemID(short stItemID[EPT_MaxEquitPart], short equipIntensifyTime[EPT_MaxEquitPart], short equipIntensifyStar[EPT_MaxEquitPart], short equipElements[EPT_MaxEquitPart] );*/
	void SetEquipByItemID(uint16 stItemID[], uint8 equipIntensifyTime[], uint8 equipIntensifyStar[], uint8 equipElements[], CPlayer_SEquipment* pEquip);
	void EquipByItemID(uint16 stItemID[], uint8 equipIntensifyTime[], uint8 equipIntensifyStar[], uint8 equipElements[] );
	void SetEquipPart(int nWhere,short stItemId);  //��������ͷ������

	//�������е���Ʒ
	void ChangeSkeletonAndEquipAllItem(bool bFightFlag);
	//��������������е�״̬
	void ClearAllBodyStatusEff(void);
	//��������״̬����ͼЧ��
	void CheckBodyStatusEff(void);

	void SetHPInfo( int nHp, int nHpMax );

	void ResetHPInfo( void );
	void DecHP( int iHPDec );
	void IncHP( int iHPDec );
	//������������õ�
	void SetHPInfo_HP( int nHp );
	void SetHPInfo_HPMax( int nHpMax );
    void SetHPInfo_HPChange( int nHp );     //��ֵ��ʾ��Ѫ����ֵ��ʾ��Ѫ
	int GetHpInfo_HPMax(){return m_hpinfo.nHpMax;}


	//��¼����ֵ
	void SetExPower( int nExPower );
	int  GetExPower(){ return m_nExPower; }
	bool IsHPInfoValid(void);
	BOOL OnShowFlyText( int nBalanceType, int nNum, int nAddNum = 0, int nWordType = 0,/*bool bExplosive = false, bool bExp = false,*/bool bIsPlayer = false );
	bool OnShowFlyText( CPlayer *pTagPlayer, CPlayer *pSrcPlayer, int iBalanceType, int iTagNum, int iScNum, int nAddNum = 0, bool bExplosive = false );
	bool OnShowFlyPic( int nType );
	//���˹���֡��Ҫ��������
	bool OnHitPoint(BOOL bLastHitPoint, int nHitPointType,SAttackInfo *pAttackInfo = 0 );

	/*
	 * Author:	2012-8-3 wangshuai
	 * Desc: 	��ʾ�˺�����
	 */
	void ShowDamageNumber(CPlayer *destPlayer, const SAttackInfoRecord *record);

    void ShowFightInfo(CPlayer* pSrcPlayer,CPlayer* pDestPlayer,SAttackInfoRecord* pRecord,ItemDefine::SItemSkill *pSkill);  //��ʾս����Ϣ

	//ȡ�ö�Ӧ�����ı��
	int		GetPlayerActionID(int ActionID, int iFightType = -1);
	//�ж��Ƿ�������
	bool	IsHaveWeapon(int iWeaponType = -1); // bCanHoldFlag�ж�����ʱ�Ƿ��������
	bool	IsHaveLHardWeapon( );
	BOOL	IsDoubleHandWeapon();
	//�ж��Ƿ��ж�
	BOOL	IsHaveShield();
	void	SetShowWeapon(BOOL bShow, BOOL bShowAfterBlend = FALSE);
	//
	unsigned char	GetSitStatus(void)		{ return m_ucSitStatus; }
	unsigned char	GetSitInterrupt(void)	{ return m_ucSitInterrupt; }
	unsigned char	GetFightStatus(void);//ս��ģʽ
	unsigned char	GetSex(void);//�Ա�
	unsigned char	GetProfession(void);//ְҵ
	unsigned char	GetToFightStatus(void)	{ return m_ucToFightStatus; }//������Ҫ�л�����ս��ģʽ
	int				GetHairColorIndex()		{ return m_nHairColorIndex; }
    unsigned char   GetLiftFlagStatus(void) { return m_ucLiftFlagStatus; }
    void    UpdateLiftFlagStatus(void);
	//
	void SetSitStatus(unsigned char status);
	void SetSitInterrupt(unsigned char status) { m_ucSitInterrupt = status; if(status) SetShowWeapon(TRUE); }
	void SetFightStatus(unsigned char);//ս��ģʽ
	void SetSex(unsigned char);//�Ա�
	void SetProfession(unsigned char);//ְҵ
	void SetToFightStatus(unsigned char);//..��Ҫ�л�����ս��ģʽ
	void SitInterrupt();	// ��ϵ�ǰ����״̬
    void SetLiftFlagStatus(unsigned char status) { if( m_bMounting && status > 0 ) m_ucLiftFlagStatus = status; else m_ucLiftFlagStatus = 0; }  // ֻ�������ܾ���
	
	void OnBuffsUpdate ( MsgBuffsUpdate*  pMsgBuffsUpdate  ); // buff list
	void OnBuffsChanged( MsgBuffsChanged* pMsgBuffsChanged ); // buff changed
    void OnBuffsUpdateOrChangedRender();

	//  ���npc���ϵ�����ս��״̬
	void	OnClearAllBodyStatus();
	//Player����������ǰִ�����еĶ�������
	void	ExcuteClearActionQueue( void );

	void    OnClearAllBodyStatusByDead();

	//���ü���
	void	AddRef( void );
	void	DecRef();
	int		GetRef() const{ return m_iRef ; }
	//true:����ɾ����false:��������
	bool	Release( void );
	bool	IsNeedToDelete( void ){return m_bNeedToDelete; }
	//
	void	SetChatInfo( std::string& strInfo ,DWORD dwLifeTime = CHAT_DIALOG_BOX_LIFE_LONG);
	bool	IsShowChatPaoPao(){return m_pChatPaoPao != NULL;}
	void	ClearChatPaoPao();
	void	SetCreatureSound( char *szCreature );

	void	SetActionTarget( int nID,const char* pName = NULL);
	void	ClearActionTarget();
	void	SetHairColorIndex( int nIndex )
	{
		m_nHairColorIndex = nIndex;
	}


public:
	BOOL IsMoving();
	void SetMoving( BOOL bMoving );
	BOOL m_bMoving;
	BOOL m_bRunning;
	BOOL m_bCountermarch; //�Ƿ��ں���
	BOOL m_bPlayedCoutermarchAnim;
	BOOL m_bLastFrameMoving;
	BOOL m_bCreateUpDataZ;

	///////////////
	// �������
	int  m_nExPower;		    // ��ǰ����
	bool m_bUpdateExPowerEff;   // ���¶�����Ч
	int  m_nFPTotal;		    // �������ֵ
	int  m_nFPTotalBall;	    // ������,�������4��,ƽ��100
	int	 m_nFPCurrentBallCount;	// ��ǰ��������

	// update star effect
	int m_nBaseStarCount;
	int m_nMinimalStar;
	bool m_bUpdateFullStarEffect;

	// play anim with npc
	int	m_nWithNPCActionID;
	DWORD m_dwWithNPCActionTime;

	float sX;
	float sY;
	void				UpdateDecalShadow();
	void InitShadowDecal();
	CNdlDecalRes* GetShadowDecal() ;
	CNdlDecalRes*		m_pkShadowDecal;

	BOOL IsCountermarch(); //�Ƿ��ں���
	void SetCountermarch( BOOL bCountermarch ); //�����Ƿ����

	bool CalcRoleMovePath(const D3DXVECTOR3& targetPos,bool bSync);

private:
	DWORD m_dwStartStopMovingTime;
	int	  m_nHairColorIndex;

public:
	CMovePath m_movepath;
	float m_fSpeed;

public:
	void HangMoving( DWORD dwCurTime, DWORD dwTimeLenght ); //�����ƶ�
	BOOL IsHangMoving( DWORD dwCurTime );

private:
	BOOL m_bHangMoving; //�����ƶ�
	DWORD m_dwStartHangMovingTime; //��ʼ�����ƶ���ʱ��
	DWORD m_dwHangMovingTimeLength; //�Ҷ���ʱ��

public:
	BOOL IsHitPointPlayOver();
	void SetHitPointPlayerOver(bool bret){m_bHitPointPlayOver = bret;}

private:
	void PushHitPoint( int nStartFrameID, int nEndFrameID, int nHitPointFrameID, DWORD dwOneLoopTime );
	BOOL CanPlayHitPoint();
    DWORD CalHitPointPlayTime( int nStartFrameID, int nEndFrameID, int nHitPointFrameID );
	BOOL m_bHitPointPlayOver;
	DWORD m_dwPushHitPointTime;
	DWORD m_dwHitPointPlayTime;

private:
	int m_nActionTargetID;
	char m_szActionTargetName[dr_MaxPlayerName + 1];
public:
	BOOL SetTwoHalfBody( BOOL bValue );
	BOOL SetFourFoot( BOOL bValue );

private:
	// �ϰ������ת����
	float m_fUpperBodyRotLimit;
	BOOL m_bTwoHalfBody;                     //�Ƿ����°������
	BOOL m_bFourFoot;                        //�Ƿ��������

public:
	void Jump();
	BOOL IsJumping(){ return m_bJumping; }
	void SetStartJumpingSpeed( float fSpeed ){ m_fStartJumpingSpeed = fSpeed; }
	float GetStartJumpingSpeed(){ return m_fStartJumpingSpeed; }
	void SetJumpingSpeed( float fSpeed ){ m_fJumpSpeed = fSpeed; }

private:
	// ��ʼ����
	BOOL m_bJumping;
	// ��Ծ������
	short m_shJumpingType;
	// ��ʼ����ʱ��
	DWORD m_dwStartJumpingTime;
	// ��ɫ����Ծ�߶�
	float m_fJumpingHeight;
	// ��ɫ�������ĵر�߶�
	float m_fStartJumpingTerrainZ;
	// ��ɫ��ǰ�����ٶ�
	float m_fJumpSpeed;
	// ��ɫ�������ĳ��ٶ�
	float m_fStartJumpingSpeed;
	// ��ɫ�������������ٶ�
	float m_fMaxStartJumpingSpeed;
	// ��ɫ�Ƿ���Ҫ���仺��
	BOOL m_bNeedDropBuf;
	// ��ɫ���������䶯��
	BOOL m_bPlayedDropAnim;

public:
	void MorphMonster( int nMonsterId, bool bPrivateShop = false );		//���γɹ���
	void DisMorph();							//ȡ������
	bool IsMorph();								//�Ƿ����
	bool IsMorphInThread() const{ return m_bMorphInThread; }
	void SetMorphInThread( bool bMorphInThread ){ m_bMorphInThread = bMorphInThread; }	//���ڱ���
	void SetMorph(bool b);  //���ñ���

private:
	bool m_bMorphing;							//�Ƿ��ڱ���
	bool m_bMorphInThread;						// �Ƿ����ڴ�������߼�
	int m_nMorphMonsterID;						//���ε�ģ��ID

public:
	void MountMonster( int nModelId, int nMountLevel = 0, BOOL bPlayEffect = TRUE, bool bMultThread = true );
	void MountMonster( char* pMonsterPath, char* pSkin );
	void DisMount( BOOL bPlayIdleAnim = TRUE );
	void PostMountMonster( int nResMexID, bool bPlayEffect, int nModelId );
	void SetAutoDismount(bool bAutoDismount) { m_bAutoDismount = bAutoDismount; }
	bool GetAutoDismount() { return m_bAutoDismount; }
	BOOL IsMounting();
	bool IsMultiMounting();
    int  GetMountModelID() { return m_nMountModelID; }
	int  GetMountLevel() { return m_nMountLevel; }
	int  GetMorphModelID() { return m_nMorphMonsterID; }
	bool IsMountInThread() const{ return m_bMountInThread; }
	void SetMountInThread( BOOL bMountInThread ){ m_bMountInThread = bMountInThread; } // ���������У���δ���ϣ����̴߳�����
	BOOL MyTeamMember;
	INT  ManipleID;

	/*
	 * Author:	2012-7-30 wangshuai
	 * Desc: 	��ȡ������������ֵ
	 */
	float GetMountScaleFix() const { return m_fDromeScaleCorrect; }
private:
	bool			m_bAutoDismount;			//�Զ������ͷż����빥��
	BOOL		m_bMounting;					// �Ƿ��������
	bool		m_bMountInThread;
	int			m_nMountModelID;
	int			m_nMountLevel;
	int			m_nMountBoneID;
	float		m_fDromeScaleCorrect;			// ������������
	float		m_fRiderScaleCorrect;			// ������������

private:
	BOOL m_bRotateLowerBody;
	BOOL m_bRotateLowerBodyStart;
	DWORD m_dwRotateLowerBodyStartTime;

public:
	BOOL IsInFloor();

private:
	BOOL m_bInFloor;

public:
	void UpdateDistanceToRole( DWORD time, float fRoleX, float fRoleY );
    float GetDistanceToRole() { return m_fDistanceToRole; }
    void UpdateDistanceToPickRay( float fCameraX, float fCameraY );
    float GetDistanceToPickRay() { return m_fDistanceToPickRay; }

private:
	float m_fDistanceToRole;        //�����ǵľ���
    float m_fDistanceToPickRay;      //�����pick��From��֮��ľ���

public:
	BOOL IsInWater();
    void SetInWater(BOOL bIn);

private:
	BOOL m_bInWater;//�Ƿ���ˮ��
	D3DXCOLOR m_ShadowColor;

public:
	void SetIntonating( BOOL bIntonating );
	void SetIntonatingStartTime( DWORD dwStartTime ){ m_dwIntonatingStartTime = dwStartTime; }
	BOOL IsIntonating();
	DWORD GetIntonatingStartTime(){ return m_dwIntonatingStartTime; }

private:
	bool	m_bLoggingMovePath;

public:
	void	StartLoggingMovePath();
	void	StopLoggingMovePath();
	void	LoggingMovePath();

public:
	int		GetIntonatingEffectID();
	void	SetIntonatingTarget( CPlayer* pTarget );
	void    SetIntonatingTargetID( GameObjectId stID ){ m_nIntonateTargetID = stID; }
	bool	IsIntonatingTargetExist();
	
	CPlayer* GetIntonatingTarget(){ return m_pIntonateTarget; }
	GameObjectId   GetIntonatingTargetID(){ return m_nIntonateTargetID; }

    bool    IsIntonation(){return m_bIntonating;}
	bool    IsCanOverIntonation(){return (m_bIntonating&&!m_bCanInterruptIntonating);}
	void    SetCanInterruptIntonating(bool bValue){m_bCanInterruptIntonating = bValue;}
	DWORD	GetIntonatingDelayTime(){return m_dwIntonateDelayTime;}
	void	SetIntonatingDelayTime(DWORD time){m_dwIntonateDelayTime = time;}
	void	SetIntonatingName(const char* strName){m_strIntonateName = strName;}
	const char* GetIntonatingName(){return m_strIntonateName.c_str();}
private:
	float	m_fShowNameAphla;					//��ʾ���ֵİ�͸��ֵ

private:
	CPlayer* m_pIntonateTarget;					// ��������
	GameObjectId	m_nIntonateTargetID;				// ��������id
	BOOL	m_bIntonating;						//�Ƿ�������
	int		m_nIntonatingEffectID;				//������ЧID
	DWORD	m_dwIntonatingStartTime;			//������ʼ��ʱ��
	bool    m_bCanInterruptIntonating;          //�Ƿ����ж�����,��Ҫ��������ն
	DWORD	m_dwIntonateDelayTime;				//��������ʱ��
	string	m_strIntonateName;					//��������
private:
	DWORD m_dwLastUpdateAnimTime;						//�����¶�����ʱ��

private:
	D3DXVECTOR3			m_vCurNormal; //��ǰ��Եر�ķ���ƫ��
	D3DXVECTOR3			m_vTargetNormal; //��Ҫƫ�Ƶ���Ŀ�귨��
	float				m_fCurRotationX; //��ɫ��ǰ��ǰ����б�Ƕ�
	float				m_fTargetRotationX; //��ɫĿ����б�Ƕ�

private:
	DWORD m_dwSpecialIdleInterval; //��������Ĳ��ż��

private:
	short m_shCurMovingType; //��ǰ���ƶ�״̬

public:
	void ResetRenderAlpha();//{ m_fCurRenderAlpha = 0.0f; } //������Ⱦ͸����
	void SetCurRenderAlpha( float fAlpha ); //���õ�ǰ��͸����
	void SetFinalRenderAlpha( float fAlpha ); //�������յ�͸����
	void SetDefaultFinalRenderAlpha( float fAlpha );//����Ĭ�ϵ�����͸����
	float GetFinalRenderAlpha(); //������յ�͸����
	float GetCurRenderAlpha(); //��ȡ��ǰ��͸����
	float GetDefaultFinalRenderAlpha();//��ȡĬ�ϵ�����͸����

private:
	float m_fCurRenderAlpha; //��ǰ��Ⱦ͸����
	float m_fFinalRenderAlpha; //������Ⱦ͸����
	float m_fDefaultFinalRenderAlpha; //Ĭ����Ⱦ͸����

private:
	BOOL m_bAssaultMoving; //�Ƿ��ڳ���ƶ�
	GameObjectId m_shAssaultTargetID; //���Ŀ���ID
	void AssaultMoving( GameObjectId shTargetID ); //����ƶ�

//HardCode
private:
	bool			m_bInstantMoving;							//�Ƿ�˲���ƶ�
	ItemDefine::SItemSkill* m_pInstantSkill;					//��ǰ˲�Ƶļ���
	EInstantMovingType m_eInstantMovingType;					//˲������
	D3DXVECTOR3		m_vInstantTargetPos;						//˲�Ƶ�Ŀ���
	float			m_fInstantMovingDir;						//˲�Ƶ�Ŀ�귽��
	DWORD			m_dwInstantMovingStartTime;

	void			InstantMoving( D3DXVECTOR3 vTargetPos, bool bCheckPos = true );	//˲���ƶ�

	void			SetInstantMoving( bool bMoving, ItemDefine::SItemSkill* pSkill );
	bool			TryInstantSkill( ItemDefine::SItemSkill* pSkill );

public:
	void			SetInstantTargetPos( const D3DXVECTOR3& vTargetPos, float fDir, EInstantMovingType type, ItemDefine::SItemSkill* pSkill );		//����˲�Ƶ�Ŀ���

private:
	BOOL	UncontrolMoving( D3DXVECTOR3 vTargetPos, BOOL bTestCollision ); //���ܿ��Ƶ��ƶ�
protected:
	BOOL			m_bUncontrolMoving;		//���ܿ��Ƶ��ƶ�
	BOOL			m_bUncontrolFlying;		//���ܿ��Ƶķ���
	D3DXVECTOR3		m_vUncontrolMoveTargetPos; //���ܿ��Ƶ��ƶ���Ŀ���

public:
	void		SetUncontrolMoving( bool bUncontrolMoving,bool isFly = false );
	void		SetUncontrolMoveTargetPos( D3DXVECTOR3 vTargetPos );
	bool		IsUncontrolMoving();
	bool		IsUncontrolFlying(){return m_bUncontrolFlying;}
	bool		IsCanDisMount();
	bool		IsUnControlState();
	D3DXVECTOR3 GetUncontrolMoveTargetPos();

public:
	BOOL	NeedRemove();
	DWORD	GetStartRemoveTime();
	void	Remove( DWORD dwStartRemoveTime );
	void	CancelRemove();

private:
	BOOL	m_bNeedToRemove;		//�Ƿ�Ҫ�Ƴ�
	DWORD	m_dwStartRemoveTime;	//��ʼ׼���Ƴ���ʱ��

private:
	BOOL			m_bHavePet;
	GameObjectId		m_PetID;
	GameObjectId     m_SubPetID;
	bool			m_bHaveSubPet;
public:
	void			SetPetID( GameObjectId PetID );
	GameObjectId		GetPetID();
	BOOL			HavePet();
	void			ReleasePet();

	void			SetSubPetID(GameObjectId suPetID);
	GameObjectId GetSubPetID();
	bool			HaveSubPet();
	void			ReleaseSubPet();

public:
	void SetProtectPetPosition(const D3DXVECTOR3& vPosition) { m_vProtectPetPosition = vPosition; }
	D3DXVECTOR3& GetProtectPetPosition() { return m_vProtectPetPosition; }

private:
	D3DXVECTOR3 m_vProtectPetPosition;

private:
	BOOL			m_bHaveMaster;
	BOOL			m_bMasterIsMe;
	GameObjectId		m_MasterID;
	int				m_AdscriptionPlayerId;
	int				m_AdscriptionGroupId;
	bool			m_bAdscription_teamHeader;
	bool			m_bHold_GroupId;

	std::string		m_strMasterName;

public:
	void			SetAdscriptionPlayerId( int id)		{ m_AdscriptionPlayerId = id; }
	void			SetAdscriptinGroupId( int id )		{ m_AdscriptionGroupId = id;	}
	void			SetAdscription_teamHeader(bool bHeader = true)	{ m_bAdscription_teamHeader = bHeader; }
	void			SetHold_GroupId(bool bHold = true)	{ m_bHold_GroupId = bHold; }
	int				GetAdscriptionPlayerId() const		{ return m_AdscriptionPlayerId; }
	int				GetAdscriptionGroupId() const		{ return m_AdscriptionGroupId;	}
	bool			GetAdscription_teamHeader() const	{ return m_bAdscription_teamHeader; }
	bool			GetHold_GroupId() const				{ return m_bHold_GroupId; }
	bool			IsCanPick( int pick_playerid, int pick_player_Groupid );
	void			SetMasterID( GameObjectId MasterID, BOOL bMasterIsMe );
	GameObjectId		GetMasterID();
	BOOL			HaveMaster();
	BOOL			MasterIsMe();
	void			ReleaseMaster();

	void			SetMasterName(const std::string& name) { m_strMasterName = name; }
	const std::string& GetMasterName() const { return m_strMasterName; }


private:
	bool			m_bItemPlayedDropAnim;
	int				m_nCanPickEffectID;

private:
	BOOL			m_bMaskPlayer;

public:
	int				m_nRippleEffectID;				//ˮ����������ЧID
	int				m_nRippleEffectContainerID;		//ˮ�����������ID
	int				m_nBoatRippleEffectID;				//ˮ����������ЧID
	int				m_nBoatRippleEffectContainerID;		//ˮ�����������ID
	float			m_fRippleEffectPlaySpeed;		//ˮ�������Ĳ����ٶ�
	DWORD			m_dwRippleEffectOverTime;		//ˮ�������Ľ���ʱ��

	int				m_nWaterSideRippleEffectID;				//ˮ����������ЧID
	int				m_nWaterSideRippleEffectContainerID;	//ˮ�����������ID
	float			m_fWaterSideRippleEffectPlaySpeed;		//ˮ�������Ĳ����ٶ�
	DWORD			m_dwWaterSideRippleEffectOverTime;		//ˮ�������Ľ���ʱ��

	// ������Ч
	int				m_nFightPowerEffectID;			// id
	int				m_nFightPowerEffectContainerID; // 

private:
    //������Ч
	bool			LoadFullStarEffect(const char* name, int& iRetEffectID, int& iRetEffectContainerID );
	void			HideFullStarEffect(int iEffectID);
	void			ShowFullStarEffect(float x, float y, bool setScale, float scale, int iEffectID, int iEffectContainerID, int iInstance);

private:
	// ������Ч
	int				m_nFullStarEffectID;
	int				m_nFullStarEffectContainerID;
	int				m_nFullStarEffectID2;
	int				m_nFullStarEffectContainerID2;

public:
	//����赲
	BOOL	IsBuildPlayer();
	BOOL	IsMaskPlayer()			{ return m_bMaskPlayer; }
	VOID	SetMask( BOOL bMask ) { m_bMaskPlayer = bMask; }
	Box* GetBox();
	FLOAT	GetPlayerHeight();

public:
	void			SetFinStatusColor( D3DXVECTOR3 vColor );

private:
	D3DXVECTOR3		m_vCurStatusColor;	//��ǰ��״̬��ɫ
	D3DXVECTOR3		m_vFinStatusColor;	//���յ�״̬��ɫ

public:
	BOOL	m_bDueler;
	INT		m_nDuelEffectId;
	DWORD	m_dwGetMoveMsgTime;

	bool	m_bInSingleFloor;

private:
    short m_isFirstAttack;
    int m_shPKKillValue;
    short m_shPKRightValue;

public:
    //PK
    void  SetIsFirstAttack(bool shPKState) { m_isFirstAttack = shPKState; }
    bool  IsFirstAttack() { return m_isFirstAttack; }
    void  SetPKKillValue(int shPKKillValue) { m_shPKKillValue = shPKKillValue; }
    int   GetPKKillValue() { return m_shPKKillValue; }
    void  SetPKRightValue(short shPKRightValue) { m_shPKRightValue = shPKRightValue; }
    short GetPKRightValue() { return m_shPKRightValue; }

	DWORD GetPkNameColor();
    void  SetPKType(short shPKType) { m_shPKType = shPKType; }
    short GetPKType() { return m_shPKType; }

    void  SetLastPKType(short shPKType) { m_shLastPkTye = shPKType; }
    short GetLastPKType() { return m_shLastPkTye; }

    void SetBattleFlag(short flag) { m_shBattleFlag = flag; }
    short GetBattleFlag() { return m_shBattleFlag; }

    //-----PKģʽ---------------------------------------------------
private:
	short m_shLastPkTye;
    short m_shPKType;       // ��PersonKiller::ePKFlagö������
    short m_shBattleFlag;
    BOOL  m_bIsDuel;

public:
    void SetDuel(BOOL bDuel) { m_bIsDuel = bDuel; }
    BOOL IsDueling() { return m_bIsDuel; }
    //--------------------------------------------------------------

    /** ������һ��ʱ���ڵ���UpdateAnimSetting�������ͼ�����档
    */
    void updateAnimNotRender();

    /** �Ƿ���Թ���Ŀ��
    */
    bool canAttack( CPlayer* target );
	void	GetPFPos(  float &fX, float &fY );
	bool isNPCCanAttack( CPlayer* target );

private:
    /** �Ƿ���Թ���Ŀ�����
    */
    bool _canAttackPlayer( CPlayer* target );

    //--------------------------------------------------------------

    // ��ǰװ������
    int m_currSuitIndex;

    // ��ʾͷ��
    bool m_isShowHelmet;
	bool m_isShowSignature;	//��ʾǩ��
	//��ʾʱװ
	bool m_isShowAecpratove;
	//�ڼ���Ĭ������,������
	int  m_nDefAvaterIndex;
	//��ʾ��������Ч��
	bool m_isShowHero;

	//��ʾ����
	bool m_isShowRankTitle;
	short m_shRankTitleId;
public:
    // ��ʾͷ��
    void ShowHelmet(bool v);
    void ShowHelmetAndSendMsg(bool v);
    bool IsShowHelmet() const;

	//��ʾ��ɫ����
	void ShowSignature(bool v);
	void ShowSignatureAndSendMsg(bool v);
	bool IsShowSignature(void) const;
	void SetSignature(const char *pSignature_);
	const char *GetSignature(void){return m_signature.c_str();}

	//��ʾ����
	void ShowRankTitle( bool v );
	bool IsShowRankTitle() const;
	void SetRankTitleId( short titleId );
	short GetRankTitleId();

	//��ʾʱװ
	void ShowAecpratove(bool v);
	void ShowAecpratoveAndSendMsg(bool v);
	bool IsShowAecpratove() const;

	//��������Ч��
	void SetShowHero(bool b){m_isShowHero = b;}
	bool IsSHowHero() const
	{return m_isShowHero;}

	//Ĭ������
	int GetDefAvaterIndex(){return m_nDefAvaterIndex;}
	void SetDefAvaterIndex(int nIndex){m_nDefAvaterIndex = nIndex;}

    // �Ƿ���ʱװ
    /*void SetCurrSuitIndex(int v) {
        m_currSuitIndex = v;
    }*/

    /*bool IsFashion() const {
        return m_currSuitIndex >= SCharVisual::ShowSuitBeginIndex;
    }*/

	//����player�ߵĳƺ�list by vvx
	vector<ItemDefine::ReputeStruct>PlayerOwnList;
	vector<ItemDefine::ReputeStruct>&	GetPlayerReputeList(){return PlayerOwnList;}

	void	clear();
	short   GetReputeID(int vecIndex);
	void CallForRepute(DWORD flag);

	struct BinaryList					//�˽ṹ��server�˵�C_Character::SReputeFlag���Ӧ����������27���ƺ�
	{
		DWORD a:6;					//��ǰ�ĳƺŵ�ID��(��Ϊ2��5�η�����32���㹻��ʾ27����������)
		DWORD b:26;				//�򿪵ĳƺŵ����
	};

	// Ѱ·
	const std::vector<swVec2f> & GetFoundPathUnLocked();
	std::vector<swVec2f> & GetFoundPathAndLocked();
	void	UnlockedFoundPath();
	int		GetCurrPathPointIndex() const { return m_currPathPointIndex; }
	void	SetCurrPathPointIndex(int val) { m_currPathPointIndex = val; }

	BOOL	IsDropEnd() {return !m_bNeedDropBuf;}
	BOOL	IsCurrNormalAttackAnim();
	void	SetRefreshPathDirction(bool val) { m_RefreshPathDirction = val; }
private:
	std::vector<swVec2f>	m_FoundPath;
	bool					m_RefreshPathDirction;
	CRITICAL_SECTION				m_FoundPathCS;	
	bool m_bFoundPathCSInitialize;
	int m_currPathPointIndex;
	bool	m_bAutoRuning;//�ж����볬��CPathDirection::MinPathLenghtForDirection��
	//
    // Font
    //

public:
    //----------------�ƺ�----------------------------------
    void SetTitleInfoById( int nId ,const char* pszName = NULL);
	void SetTitleId( int nId ){ m_nTitleId = nId; }
	int GetTitleId(){ return m_nTitleId; }
	void SetTitleColor( DWORD dwColor ){ m_dwTitleColor = dwColor; }
    void SetTitle(const std::string& title) { m_strTitle = title; }
    const std::string& GetTitle() const { return m_strTitle; }
	void SetTitleTargetName(const char* name);
	const char* GetTitleTargetName() {return m_szTitleTargetName.c_str();}
private:
    //�ƺ�
    int              m_nTitleId;
    std::string      m_strTitle;
    DWORD            m_dwTitleColor; // �ƺ���ɫ
    std::string      m_szTitleTargetName;   // ��ϵ�ƺŸ���������
	std::string m_signature; //����
public:
	void SetFontObject( RTTFont* pFontObj );
	RTTFont* GetFontObject() const;
private:
	bool m_bNameMulted;

    RTTFont* fontName_;

    Font3D* fontSpeName_;
    Font3D* fontGuild_;
    Font3D*	fontPrivateShopName_;

    ProgressBar3D* m_pHpPB3D;
    ProgressBar3D* m_pMpPB3D;
    ProgressBar3D* m_pFpPB3D;

// ���������Ҫ����ת���ͷż���
private:
	struct SkillInfo 
	{
		CPlayer* pTagPlayer;
		ItemDefine::SItemSkill* pSkill;
		bool bCheckOnly; 
		bool bNoTip;
		bool bTryUse;

		SkillInfo()
		{
			pTagPlayer = 0;
			pSkill = 0;
			bNoTip = false;
			bTryUse = false;
		}
	};
	SkillInfo m_readySkillInfo;

	//
	//
	//
	DWORD m_dwStopMoveTime; // �ͷ��˲����ƶ��ļ��ܣ��ڸ�ʱ��ǰ�����ƶ�
	DWORD m_dwStopJumpTime;	// �ͷ��˲�����Ծ�ļ��ܣ��ڸ�ʱ��ǰ������Ծ

	DWORD m_dwDropEndTime;		// Drop��������ʱ��

	// ս�����ƣ���ս������ʾս��������������X�л�
public:
	BOOL IsFightPose() {return m_bFightPose;}
	void SetFightPose(BOOL bFightPose) {m_bFightPose = bFightPose;}

	BOOL CanScabbard()
	{
		if( HQ_TimeGetTime() < m_dwLastScabbardBeginTime
			|| ( HQ_TimeGetTime() - m_dwLastScabbardBeginTime > 1000) )
			return TRUE;
		return FALSE;
	}

	BOOL IsPlayStandAnim()
	{
		if( m_pAnim && m_pAnim->GetCurAnimType() == MoreActionClient::stand )
			return TRUE;
		return FALSE;
	}

    BOOL IsPlaySitAnim()
    {
        if( m_pAnim && m_pAnim->GetCurAnimType() == MoreActionClient::Sit )
            return TRUE;
        return FALSE;
    }

    BOOL IsSittingAnim()    // �������£��������ţ���վ����
    {
        if( m_pAnim )
        {
            if( m_pAnim->GetCurAnimType() == MoreActionClient::stand 
                || m_pAnim->GetCurAnimType() == MoreActionClient::Sit
                || m_pAnim->GetCurAnimType() == MoreActionClient::SitLoop )
                return TRUE;
        }
        return FALSE;
    }

    BOOL IsEmbraceAnim()
    {
        if( m_pAnim && m_pAnim->GetCurAnimType() == MoreActionClient::yongbao )
            return TRUE;
        return FALSE;
    }

protected:
	BOOL	m_bFightPose;

	// �ϴ��յ�/�ε���ʼʱ�䣬���1�����ϲ����ٴ��յ���ε�
	DWORD m_dwLastScabbardBeginTime;
public:
    //-----------------��ӡ-----------------------------
	BOOL				IsNeedShowFootPrint();
	CFootPrint*         GetFootPrint();
    void                RenderShadowDecal( BOOL bCombineRenderShadowDecal = FALSE );
protected://��ӡ
	void				UpdateFootPrintDetail();
	float				m_distanceDelta;//Ϊ�˽�ӡ
	float				m_distanceDeltaForDynamicLoad;//Ϊ�˶�̬����
	CFootPrint*			m_footPrint;
    //-------------  ��ӡEnd-------------------------------------

    BOOL                m_LastRenderShadowDecal;
//////////////////////////////////////////////////////////////////////////
// point aoe staff
//////////////////////////////////////////////////////////////////////////
public:
	void				SetIsSelectingPoint( bool bSeleting ){ m_bSelectAoePoint = bSeleting ; }
	bool				IsSelectingPoint(){ return m_bSelectAoePoint; }
	void				SetPointAoePos( const D3DXVECTOR3& vPos ){ m_vPointAoePos = vPos ; }
    const D3DXVECTOR3&  GetPointAoePos() { return m_vPointAoePos; }
protected: //point aoe
	bool				m_bSelectAoePoint;	// �Ƿ�����ѡ��aoe��
	D3DXVECTOR3			m_vPointAoePos;		// aoe �ͷŵ�

    BOOL                m_bIsCurRandRun;    // ���浱ǰRandRun״̬
    BOOL                m_bIsCurStun;       // ���浱ǰStun״̬
    BOOL                m_bIsCurFreeze;     // ���浱ǰFreeze״̬

	BOOL				IsRenderParticleEmitters();

    BOOL                IsCollectionAnim(const char* szAnim);

    // ��ǰ�������ļ���
public:
    BOOL                CheckAdvanceSkill(unsigned short nSkillID, unsigned short nSkillLevel);
    BOOL                RemoveAdvanceSkillByID( int nSkillID );
    void                ClearAdvanceSkillList() { m_vctAdvanceSkill.clear(); }
protected:
    enum AdvanceSkillHurtAnimStatus
    {
        ASH_NoNeedPlay,
        ASH_NeedPlay,
        ASH_Played
    };
    struct SAdvanceSkillData
    {
        ItemDefine::SItemSkill*    pSkill;
        DWORD                       dwBeginFrameTime;
        DWORD                       dwHitPointPlayTime;
        DWORD                       dwEndFrameTime;
        int                         nNeedPlayHurtAnim;  // �˺�����Ŀ��ĵ��弼�ܣ���ҪԤ���ܻ�����
        int                         nTargetPlayerID;    // �ܻ�Ŀ��
    };
    std::vector<SAdvanceSkillData> m_vctAdvanceSkill;    // ��ǰ�������ļ����б�

    void                PlayAdvanceSkillHurtAnim(int nPlayerID, ItemDefine::SItemSkill* pSkill);

public:
	BOOL LoadMtlEffect( const char* pszFileName );
    // ��������
public:
    BOOL                IsCanPlayInteraction(CPlayer* pTargetPlayer, BOOL& bTooFar, BOOL& bZTooFar);
    BOOL                IsLootOrIntonateAnim()
    {
        if( m_pAnim && (m_pAnim->IsLootAnim() || m_pAnim->IsIntonateAnim()) )
            return TRUE;
        return FALSE;
    }
    void                SetInteractionMaster(int nPlayerID) {m_nInteractionMasterPlayerID = nPlayerID;}
protected:
    int     m_nInteractionMasterPlayerID;   // ӵ���������ID������Լ�����������Ϊ-1
    BOOL    m_bNeedResetPosAfterInteraction;// ӵ����������Zֵ

// NPC Idle����
public:
	void    TryPlayNpcAction();
	void    ProcessNpcAction();
    bool    IsHaveAppeaseRequire(Require *pReq);
    void    InitNpcAction(DWORD dwTime);        // NPC������Ұ����ʼ������
    void    ExitNpcAction();        // NPC�뿪��Ұ����������
    void    UpdateNpcAction(DWORD dwTime);
protected:
    DWORD   m_dwNextActionTime;     // NPC����Ұ��m_bNextActionTime��Ϊ0
    short   m_shNextActionId;
    BOOL    m_bNeedInitNpcAction;   // NPC����δ�õ�ǰ��������Ҫ��ʼ�������ı��

	DWORD   m_dwNpcActionTime;  //��ʼʱ��
	Action  m_act;
	bool    m_IsSearch;         //�Ƿ�����NPC
	DWORD   m_dwSearchCD;       //����CD,����ÿ֡��ͣ����

    int     m_iBuffStatusAnimType;  // ״̬��������

    // �ٻ����Ƿ�ɼ�
    BOOL    m_bIsVisibleToOtherPlayer;    // ö�����ͣ������ItemDefine::SMonster
public:
    BOOL    IsVisibleToOtherPlayer() { return m_bIsVisibleToOtherPlayer; }
    void    SetVisibleToOtherPlayer( bool bVisible ) { m_bIsVisibleToOtherPlayer = bVisible; }

    void    StopJump();

protected:
    float   m_fPlayerScale;
    
    BOOL    CanSwitchRunAnim();

public:
	Box*	GetWorldBBox();
#ifdef NEW_PLAYER_LOAD
	// [���ģ�ͼ��ػ���],[QL]
	// ��ҽ�����Ұ��ģ������Ĭ�ϲ����أ�����ĳЩ������ż��ز�������
public:
	BOOL	IsModelLoaded() { return m_bModelLoaded; }
	void	UpdateFakeWorldBBox(float x, float y, float z);
	void	LoadModel();
protected:

	BOOL	m_bModelLoaded;
	BOOL	m_bPrivateShop;		// ��������ID��<=0��ʾû����
	Box		m_fakeWorldBBox;			// ûģ������ʱ�������WorldBBox
#endif

	// Player����
public:
	enum PlayerType
	{
		PT_Me					= 1<<0,		// ����
		PT_MyPet				= 1<<1,		// �ҵ��ٻ��޻�ū��
		PT_TeamPlayer			= 1<<2,		// ����
		PT_TeamPlayerPet		= 1<<3,		// ���ѵ��ٻ��޻�ū��
		PT_EnemyGuildPlayer		= 1<<4,		// �ж԰�����
		PT_EnemyGuildPlayerPet	= 1<<5,		// �ж԰����ҵ��ٻ��޻�ū��
		PT_LeaguePlayer			= 1<<6,		// ͬ�����
		PT_LeaguePlayerPet		= 1<<7,		// ͬ����ҵ��ٻ��޻�ū��
		PT_MyGuildPlayer		= 1<<8,		// �Լ�������
		PT_MyGuildPlayerPet		= 1<<9,		// �Լ������ҵ��ٻ��޻�ū��
		PT_NormalPlayer			= 1<<10,	// ��ͨ���
		PT_NormalPlayerPet		= 1<<11,	// ��ͨ��ҵ��ٻ��޻�ū��
		PT_RedNamePlayer		= 1<<12,	// �������ж����
		PT_RedNamePlayerPet		= 1<<13,	// �������ж���ҵ��ٻ��޻�ū��
		PT_PKPlayer				= 1<<14,	// PK���
		PT_PKPlayerPet			= 1<<15,	// PK��ҵ��ٻ��޻�ū��
		PT_Monster				= 1<<16,	// ����
		PT_Other				= 1<<17		// ����
	};

	DWORD GetPlayerType();

protected:
	void AdjustAttackPos();		// ��������˫���߶ȣ����һ���ǹ�һ������ң�������ָ߶�

	void AdjustPosToMaster();
	float m_fPetAdjustPosCD;	// ������ٻ��ޣ�ÿ�����һ�θ߶ȣ���ֹ��ģ�������ϲ�������λ�룬Ĭ��Ϊ2��
public:
    int  GetInfluence() const {return m_nInfluence;}
    void SetInfluence(int nValue);
	bool IsSameInfluence(const CPlayer*);
    void SetActionFluence(int nValue){m_nActionFluence = nValue;}
    void SetUpdateActionFluence(bool bValue){m_bUpdateFluence = bValue;}
    void SwitchCampAnim();    //�л���Ӫս������
private:
	int m_nCampType;
    int m_nInfluence;           //�����ж��Ƿ�����ͬһ����Ӫ����Ҫ����PK�ж�, //Ĭ��enumBattleInfluence_Max ����Ӫ
    int m_nActionFluence;        //�������ţ��ñ�����������Ҫ��¼����Ӫս���У���˭ռ�죬ֻ��NPC��Ч������MsgNPCEnterMySight�д�����
    bool m_bUpdateFluence;       //�Ƿ���Ҫ������Ӫ�ж�������
public:
	void InitMonsterAction(int nIndex,SArea *pArea);
	void UpdateMonsterAction(DWORD dwTime);
	void EndMonsterAction();
	bool GetMonsterAction(){return m_bMonsterActioning;}
	void PlayMonsterAction();
private:
	DWORD   m_dwElapseMonsterActionTime;  //�����ʱ��
	short   m_shCurrMonsterActionId;
	BOOL    m_bMonsterActioning;   // ����˵��������
	short   m_nZoneIndex;          //�ؼ�����

public:
	void ShowAttrChangeInfo(SValueChanged &valueChange);
	void SetFirstOnline(bool bValue){m_bFirstOnline = bValue;}
	bool IsFirstOnline(){return m_bFirstOnline;}
private:
	bool m_bFirstOnline;  //�������ε�һ���������Ըı���Ϣ
public:
	void SetCarrierState(bool bValue);
	bool IsCarrierint(){return m_bCarrier;}
	void SetCarrierPos(int nIndex){m_nCarrierID = nIndex;}
	void SetCarrierDriver(int nID){m_nCarrierDriver = nID;}
	int  GetCarrierPlayerID(){ return m_nCarrierDriver; }
	void SetOthersPet(bool other){ m_bIsOthersPet = other; }
	bool IsOthersPet(){ return m_bIsOthersPet; }
	void AddPassenger(GameObjectId id);
	void RemovePassenge(GameObjectId id);
private:
	bool m_bCarrier;            // �Ƿ��ڴ�������
	int  m_nCarrierID;          // ���ڴ�����ĵڼ���λ��
	int  m_nCarrierDriver;		// ���������ID
	bool m_bIsOthersPet;		// �Ƿ��������������ҵ�����
public:
	bool IsSameCountry(int nCountry);  //�����Ƿ���ͬ

public:
	uint8		GetTypeStatus() const { return m_nTypeStatus; }
	void		SetTypeStatus(uint8 val);
private:
	uint8		m_nTypeStatus;          // ��ǰ״̬

public:
	void ShowPetEffect();//��ʾ������Ч
	void SetPetEffect(const char* pszEffectName);
private:
	bool m_bShowPetEffect; //������ٻ�����ʱ�����ŵ���Ч
	std::string  m_strPetEffect;
	std::vector<GameObjectId>	m_passengers;	//�˵ĳ�����滹�����������
public:
	void TestPlayAnimByType(const char* pszAnim,bool bUpper);
public:
	void ProcessActionState();
	void ProcessHitBack(); //�������
	void ProcessBuoy();    //������
	void SetActionState(eActionState eValue,D3DXVECTOR3 vDir);
private:
	eActionState  m_eState;
	CRecordTimer  m_eStateTimer;  //״̬��ʱ��
	D3DXVECTOR3   m_HitBackDir;   //���˷���
private:
	float  m_fTargetZValue;    //Ŀ��Z��
	bool   m_bStartZMoving;    //��ʼZ���ƶ�
	bool   m_bHigh;            //�Ƿ�����
	bool   m_bInElevator;      //�Ƿ��ڵ�����

public:
	void EquipTalismanById(unsigned short usItemID); //װ������
	void UnEquipTalisman(); //ж�ط���
	void CreateTaliman(unsigned short ustItemID); //��������
	void DestroyTaliman();  //���ٷ���

	void UpdateTaliman(DWORD dwTime); //���·���
	void RenderTaliMan();  //��Ⱦ����
	bool IsShowTaliman(){return m_bShowTaliman;}
	void SetTalismanById(int nItemID){m_nTalismanId = nItemID;}
private:
	CPlayerAnim *m_pAnimTaliman;  //��������
	bool         m_bShowTaliman;  //�Ƿ���ʾ����
	int          m_nTalismanId;   //����ID
public:
	float   GetZByXY(float fCurrentZ,float x,float y,DWORD dwFlag,BOOL* bInFloor = NULL,DWORD* pdwRet = NULL,
		BOOL bIsRole = false, D3DXVECTOR3 *pNormal = NULL );
	int  GetNpcType();
public:
	void ProcessNpcHideOrShow(int nNpcType);
	void SetNpcShow(bool bValue){m_bBeginNpcShow = bValue;}
	void PlayNpcHideOrShow(bool isHide);
	bool IsNpcShowProcessing(){return m_bBeginNpcShow;}
	void HideSpeicalNpc();
private:
	DWORD m_dwNpcBeginTime;  //Npc��ʾ����
	bool  m_bBeginNpcShow;   //�Ƿ�ʼNPC��ʾ����
//����ģʽ
public:
	int GetMountOperaType(){return m_nMountOperaType;}
	void SetMountOperaType(int nValue){m_nMountOperaType = nValue;}
	bool IsGoudaOperaMode(){return m_nMountOperaType == 1;}  //�Ƿ��ڻ���ģʽ
private:
	int  m_nMountOperaType;  //�������ģʽ��0Ϊ��������ģʽ��1Ϊ����ģʽ
public:
	void ProcessSceneSegment();
	void BeginPlaying(int nSceneID);
	void EndPlaying();

public: /// �������
	void SetHeroID(const uint16 id = INVALID_HERO_ID) { mHeroID = id; }
	uint16 GetHeroID() const { return mHeroID; }

	/*
	 * Author:	2012-7-25 wangshuai
	 * Desc: 	ʹ��Player������������״̬���л�, ����״̬������Player�����͡����͡���ɫ(Skin)
	 */
	void ShapeShift();

private:
	// ���������ID
	uint16 mHeroID;
	//Դ��ͷ��������ID
	int source_faceid;
	int source_hairid;

public: /// ѹ�����
	bool IsYabiaoState() const { return mIsYabiaoState; }
	void SetYabiaoState(bool b) { mIsYabiaoState = b; }

	bool IsCanRide() const { return mIsCanRide; }
	void SetIsCanRide(bool b) { mIsCanRide = b; }

	void SetBiaocheScale(float s) { mBiaoCheScale = s; }

private:
	// ֻ������ı�����, ����Master�ſ��Ա����ڳ�
	bool mIsCanRide;

	// �Ƿ�����ڳ�
	bool mIsYabiaoState;

	// �ڳ�������
	float mBiaoCheScale;

//private://��¼����̫ƽ�þ�ǰ������
//	DWORD m_dwMapID;
//	D3DXVECTOR3  m_PrevPosition;	//����̫ƽ�þ�ǰ������
//	bool m_bIsInTPHJ;				//�Ƿ���̫ƽ�þ���
//public:
//	void SetMapID(const DWORD id=INVALID_MAP_ID){m_dwMapID = id;}
//	DWORD GetMapID(){return m_dwMapID;}
//	void SetPrePosition(D3DXVECTOR3 pos){m_PrevPosition = pos;}
//	D3DXVECTOR3 GetPrePosition(){return m_PrevPosition ;}
//	void SetInTPHJ(bool IsIn){m_bIsInTPHJ = IsIn;}
//	bool IsInTPHJ(){return m_bIsInTPHJ;}

private:
	int   m_nSceneID;            // ���ŵĳ���ID
	int   m_nCurrSegmentIndex;   // ��ǰ����Ƭ��
	DWORD m_dwCurrSegBeginTime;  // ��ǰ����ʱ��
private:
	bool m_bPlayDropAnim;	
public:
	bool IsCanOperateByKey(AN_Configure_ShortcutKey::ShortCutKey_Configure type);  //����������״̬ʱ��һЩ������Ҫ��ֹ

public:
	uint32		GetBeLongID(){return m_BeLongID;}
	void		SetBeLongID(uint32 ID);
private:
	uint32		m_BeLongID;//����ID
};
extern volatile swVec2f g_destPos;
extern bool g_PFOK;
extern BOOL g_FindPathThreadWillExit;
extern BOOL g_FindPathThreadExit;

extern int GetNormalAttackByProfession( int iProfession );

#endif