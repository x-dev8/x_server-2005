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
		eOpIdle,        //待机
		eOpUseSkill,    //使用技能/
		eOpTalk,        //对话
		eOpGetItem,     //取得道具
		eOpDropItem,	//丢弃道具
		eOpMoveTo,      //移动到目标地点
		eOpTrade,       //交易
		eOpChangeDir,	//转身
		eOpMoveSkill,   //移动过去使用技能
		eOpMoveTalk,    //移动过去对话
		eOpMoveGetItem,  //移动过去取得道具
		eOpMoveGetRangeItem, //取得周围的道具
		eOpMoveDropItem,//移动过去丢弃道具
		eOpMoveTrade,   //移动过去交易
		eOpMoveFollow,  //跟随
		eOpDoAction,    //作莫个行为的Action
		eOpVerifyPos,			// 位置校正
	};

	enum
	{
		eTimeOut	= 1,		// 超时了
		eNoTryTimes = 1<<1,		// 尝试次数完了
		eUpdate		= 1<<2,		// 更新了一次

	};

	DWORD dwType;				// (当前的行动)操作类型
	//
	struct Target
	{
		int stDst;				//目标npc
		int x, y;				// 坐标(保留移动的目标坐标) 
	} target;					// 目标
	//
	struct Skill
	{
		int iSkillID;			//使用的技能编号
		int	iSkillLevel;		//使用的技能等级
	}skill;
	//
	struct Action
	{
		int iActionID;			//需要做的动作的编号
	}action;

	//呆在原地攻击
	bool	bHoldAttack;
	//
	bool	bAttackToDeadFlag;	//不过是攻击,技能判断能否攻击到死
	DWORD	dwFlag;				// 标志位
	//
	DWORD	dwOperBeginTime;	//该操作开始的时间
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

	DWORD	dwStartTime;			// 技能开始时间
	DWORD	dwIntonateTime;			// 吟唱时间
	DWORD	dwHoldTime;				// 持续时间
	DWORD	dwCancelTime;			// 取消时间
	BOOL	bCancelHasSent;			// 取消是否已发送
	BOOL	bMovePermit;			// 是否允许移动
	DWORD	dwSkillStatus;			// 当前技能状态，吟唱或者持续
	std::vector<I_PlayerEffect*> vectorEffect;		// 当前使用的特效

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
	eAction_None = 0, //无任何状态
	eAction_Buoy ,    //浮空
	eAction_HitBack,  //击退
	eMax
};

class CPlayer : public MeCommonAllocObj<CPlayer>
{
public:

	CPlayer();
	~CPlayer();

    //是否是主角，目前主要用来显示主角位置，见render
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

    // 身高
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

	// 以上的SetCountry是假的	以下为真 国家 和 国家称号		added by zhuomeng.hu		[9/9/2010]
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
    POINT				GetPlayerPos();			//------- 得到玩家所在屏幕坐标

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

    // 声望
    void				SetReputation( DWORD dwReputation ){ m_dwReputation = dwReputation; }
    DWORD				GetReputation(){ return m_dwReputation; }

    // 帮贡
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
	void                    HideOrShowPlayerEffect(bool bShow = true); //lyh++ 隐藏或显示玩家的特效
    // 更新吟唱朝向
    void					UpdateIntonateDirection();

    // 攻击朝向仿神鬼
    void                    UpdateMeDirInFighting();

    //更新水波特效
    void					UpdateWaterEffect();

    void StopRippleEffect(int nRippleEffectID);
    void					LoadRippleEffect();
	void                    LoadWaterSideEffect(); //载入水波特效
	void                    LoadBoatRippleEffect(); //
	void                    LoadRippleIDEffect();

    //对玩家身上的特效的设置的更新
    void					UpdateEffectHelper();
    void					UpdateEffectHelper(CCharEffectContainer* pCharEffectContainer);
    //平滑帧的处理
    void					SmoothFrameProcess();
    //隐形技能的处理
    void					HideSkillProcess();
    //移动的处理 
    void					MoveProcess();
    //处理主角的移动
    void	                RoleMoveProcess();
    void	                RoleMovePathProcess();
    //处理给主角的移动
    void	                UnRoleMoveProcess();
    //处理主角移动中碰到的阻挡
    void	                RoleMovingCollision();
    //处理当前状态
    void					ProcessCurStatus();
    //处理移动状态改变的时候的动画播放
    void					MoveStatusChangedProcess();
    //更新角色斗气特效，仅杖，jiayi added
    void					UpdateFightPowerEffect();
    //7,8,9星时的特效, jiayi added
    void					UpdateFullStarEffect();
    void					_UpdateFullStarEffect(float x, float y, bool setScale = false, float scale = 1.0f);
    void					CalcMinimalStar();

    void				Update( DWORD time);
	//显示角色的聊天信息
	void				ShowChatPaoPao();
	//显示角色的个人商店信息
	void				ShowPrivateShopInfo();
	//角色的动画修正(发现动画播错了，就重新播正确的)
	void				AnimCorrectProcess();
	//主角的行为处理
	void				RoleOperationProcess();
	//玩家转向的处理
	void				TurnAroundProcess();
	//更新玩家的当前Z坐标
	void				UpdateCurZPos();
	//处理玩家的跳跃
	void				JumpingProcess();
	//处理玩家的跑动音效
	void				SoundProcess();
	//处理主角站的斜坡上下滑
	void				RoleSlipProcess();
	//处理动画数据
	void				UpdateAnimSetting();
	//更新NPC头顶的提示
	void				UpdateNpcTips();
	//更新渲染的Alpha
	void				UpdateRenderAlpha();
	//更新状态颜色
	void				UpdateStatusColor();
	//处理播放特殊待机动作的时间
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
	//z只对自己有效
	void				JumpToMapPos( float x, float y, float z,float xDir,float yDir );
	void				Destroy();
	
    BOOL                IsMoveStepOver(void);//  判断是否处在一步走完的状态
    void                StopMovePath(void); //  定止走动

	//在模型管理中得ID
	int					m_iIDInModelMan;

	void				Reset();

	//设置路径后使用

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

	void				ClearMoveQueue();//清除移动队列

    enum enumStatus
    {
        //普通状态
        Player_Status_Normal			= 0
        //吟唱状态
        ,Player_Status_Intonate
        //维持技能状态
        ,Player_Status_HoldSkill
        //死亡状态
        ,Player_Status_Death
    };
    //
    //对除自己以外的Player移动修正
    int						GetPlayerStatus(){ return m_iPlayerStatus; }

	struct StateOnServer
	{
		DWORD	dwTime;
		short	x, y;		// 在服务器上的位置
		DWORD	dwState;	// 当前的状态
		DWORD	dwParams[4];// 参数
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
	void    SwitchMedicalAnim();  //切换喝药动作

    //状态切换函数
    void    SwitchActionStatus(CPlayerStatus::STATUS_KEY CurKey, DWORD Delay, CPlayerStatus::STATUS_KEY NextKey = CPlayerStatus::esk_Idle, BOOL bPlayAnim = TRUE );
    //
	BOOL	IsCanPutItem(int x, int y);//判定一个地方可否放道具
	BOOL	TryDropItem( unsigned int nPackIndex );
	BOOL	TryPickItem();
	void	TryPickItem( CPlayer* pItem );
	BOOL	TryTalkWithNpc();
	void	TryTalkWithNpc( CPlayer* pNpc );
	void	TryTalkWithPlayer();//就是当npc对玩家特定条件下说话和做动作朝向改变

	void	Face2FaceWithNpc( CPlayer* pNpc );
	BOOL	TryMoveTo();

	//一些功能的判定函数
	BOOL	IsCanUseItem(void);//	判断可否使用道具
	BOOL	IsCanDoExpression();//判断可否作表情动作
	BOOL	IsTargetIsRight(int skill, int skill_level, int id);
	BOOL    IsCanTalk(int iDestID);					//	判断能否对话

	BOOL	IsSkillCanUse( ItemDefine::SItemSkill* pSkill );
	BOOL	IsSkillCanUseExceptActionAndTime( ItemDefine::SItemSkill* pSkill,
											bool bCheckOnly = false );
    BOOL    IsSkillCanUse(int skill_id, int skill_level);    //判定莫个技能可否使用
	BOOL    IsSkillCanUseExceptActionAndTime(int skill_id, int skill_level); //除了时间，和状态外判定技能可否使用

	BOOL	IsSkillCanUseStatus( int skill_id, int skill_level );

    BOOL    IsTagCanBeAttack(void); //判定目标可否攻击
    BOOL    IsCanMove(void);        //判断可否移动
	BOOL	IsCanJump(void);		//判断是否跳跃
	BOOL    IsPlayerCanChangeToStatus(int next_status);//	判断player能否改变到目标状态
    BOOL    IsPlayerCanChangeStatus(void);//  判断一个玩家是否可以改变状态(动作)
	//对npc几个最小操作的定义
    BOOL    OperNothing(void);
    BOOL    OperIdle(void);        //待机
    BOOL    OperUseSkill(void);    //使用技能
    BOOL    OperTalk(void);        //对话
    BOOL    OperGetItem(void);     //取得道具
	BOOL    OperDropItem(void);	   //丢弃道具
    BOOL    OperTrade(void);       //交易
	BOOL    OperChangeDir(void);	//转身
    BOOL    OperMoveSkill(void);   //移动过去使用技能
	BOOL    OperMoveDroptem(void); //移动过去丢弃道具
	BOOL	OperDoAction(void);		//作莫个动作

    //一些状态控制函数
    //
    void    ActionStatusIdle(void);         //待机
    void    ActionStatusPickItem(void);	    //捡道具
    void    ActionStatusDropItem(void);		//丢弃道具
    void    ActionStatusTalk(void);         //对话
    void    ActionStatusTrade(void);        //交易
    void    ActionStatusMove(void);         //移动
    void    ActionStatusChangeDir(void);	//转身
    void    ActionStatusPreAttack(void);    // 预备攻击状态
    void	ActionStatusPreIntonate(void);
    void	ActionStatusHoldSkill(void);
    void    ActionStatusAttack(void);       // 攻击状态
    void    ActionStatusIntonate(void);		// 呤唱
    void    ActionStatusBeAttack(void);     // 受击状态
    void    ActionStatusMiss(void);         // 闪避状态
    void    ActionStatusSleep(void);        // 昏倒状态
    void    ActionStatusDie(void);          // 死亡状态
    void    ActionStatusBeatBack(void);	    // 击退
    void    ActionStatusActionTime(void);	//在一段时间内作莫个动作

	void     SetSpineBoneID(int id) { m_nSpineBoneID = id;}
	void     SetRightHandBoneID(int id) { m_nRightHandBoneID = id;}
	void     SetLeftHandBoneID(int id) { m_nLeftHandBoneID = id;}
	void     SetBackBoneID(int id) { m_nBackBoneID = id;}


	//使用技能
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
    //添加状态特效
    BOOL					FindStatusEffect( int nStatusID, int nLevel );

    //添加状态特效
    void					AddStatusEffect( int nStatusID, int nLevel, int nEffectID );

    //清理不维持的特效
    void					ClearUnkeepStatusEffects();

    //重置维持标志
    void					ResetStatusEffectsKeepFlag();

	//清理播放状态特效
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
    // 是否指在玩家的个人商店信息栏内
    bool					IsPtInPrivateShopInfo( int x, int y );
	void					SetSeekEquipInfo( SCharItem aItem[] ){  memcpy( m_equipitemSeekEquip, aItem, sizeof( SCharItem ) * EEquipPartType_MaxEquitPart ); }
    SCharItem*				GetSeekEquipInfo(){ return m_equipitemSeekEquip; }

    void					PlayNormalAttackSound( ItemDefine::SItemSkill *pSkill );
    void                    SetMapEffectId(int nEffectId){m_MapEffectId = nEffectId;}
    int                     GetMapEffectId(){return m_MapEffectId;}


	//////////////////////////////////////////////////////////////////////////
	// 五行
	void	InitFiveElementEffect();
	void	UpdateFiveElementEffect();
	void	_UpdateFiveElementEffect(bool setScale = false, float scale = 1.0f);
	void	UpdateMainElement();
	void	CheckSuitForFiveElement();

	// 星级，五行渲染，游戏场景中不需要调用，只在属性界面中使用。
	void	_RenderFiveElement();
	void	_RenderFullStarEffect();
	//////////////////////////////////////////////////////////////////////////

	bool	IsPrivateShopOpen() { return m_bPrivateShopOpen; }

	bool	IsHide() { return m_bHide; }
	void	SetHide(bool bHide);

	D3DXVECTOR3			m_vDir; //角色的朝向
	D3DXVECTOR3			m_vPos; //角色的位置
    short               m_shGuildTitle;
    short               m_shInfluence;
	std::string				m_szReputeName;

	bool                m_bHasRelive;//如果复活过了再最近的一次HITPONIT如果会被打死取消
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

    char            m_pTempMapName[200];        //临时加的这个人所在场景名称

	SOperation			m_operation;		//动作队列
	MsgAckCharInfo		m_charSimpleInfo;
	bool				m_bDead;
	bool				m_bWillDie;
	bool				m_bDeadOver;
	bool				m_bIsActivePlayer;
	DWORD				m_dwDeadTime;
	// 在主角刚刚经受了攻击后，如果想要移动，
	// 必须请求服务器允许，
	// 因为连招系统的存在，角色在中了一招以后很可能立刻又会中一招
	// 虽然客户端解除了僵硬时间，但是服务器上立刻产生了新的状态，
	BOOL				m_bServerPermitMove;
	//
	float				m_x, m_y, m_z, m_dir, m_fUpperBodyDir, m_fLowerBodyDir;
	float				m_tx, m_ty, m_tz, m_tdir, m_fTargetUpperBodyDir, m_fTargetLowerBodyDir;
	// 上一次取Z时用的值
	float				m_fLastGetZ_x, m_fLastGetZ_y, m_fLastGetZ_z;
	// 不移动物体为防止掉到模型floor下，每过m_usUpdateZFrameCount帧更新一次，m_usUpdateZFrameCount取值区间[50-100]
	unsigned short		m_usUpdateZFrameCount;
	// 如果上一帧位置与当前帧相同，计数
	unsigned short		m_usSamePosFrameCount;

	//在服务器上的Z坐标
	float				m_fServerZ;

	// Player所在的地面高度
	float				m_fTerrainZ;

	// 上半身的角度修正
	float				m_fUpperBodyDirCorrect;

	D3DXVECTOR3 m_vCurDir; // 角色的当前朝向
	int					m_iDir;
    BOOL                m_bForceTurnRole;   // 2.5D视角强制旋转主角
	
	D3DXMATRIX			m_matTransform;

	POINT				m_ptLoc;
	//POINT				m_ptLocFromAttMsg;
	
	//是否主角
	BOOL				m_bRole;
	int                 m_EffectID; //装备强化id 不包括武器的特效
	char               m_EffectName[EFFECTPATCHLEN]; //lyh添加特效显示文件路径
	int                m_HeroKillTargetNum; //lyh++
	bool               m_HeroKillHasChanged;
	int                m_EffectCharSkillID;
	// 无论如何，只有一个当前攻击者

	short				m_stCharType;
	short				m_stFaceIcoId;

	short				m_stMonsterType;
	short				m_subMonsterType;
	BOOL				m_isPet;
	
	// 服务端的Id
	GameObjectId				m_stID;
	//NpcID
	int                 m_nNpcId;              

	//公会ID
	bool				m_bHadGotValidGuildInfo;
	// 公会id
	DWORD				m_dwGuildId;
	// 公会名称
    char				m_szGuildName[GuildDefine::MaxNameLength  + 1];
    bool                m_bGuildIsCityMaster;
	//SGuildFlag			m_stGuildFlag;                    // 帮派旗帜
	char				m_gangPosition;                // 职位EGangPosition
    //	怪物的ID
    int					m_nMonsterID;

    int					m_nModelId;
    //角色国家
    int					m_iCountry;

	uint8				m_iRealCountry;		// 国家				added by zhuomeng.hu		[9/9/2010]
	uint16				m_iCountryTitle;	// 国家称号			added by zhuomeng.hu		[9/9/2010]
    uint16              m_iPortraitId;      // 头像ID           added by ZhuoMeng.Hu		[9/19/2010]

	uint32				m_iFamilyID;		// 家族id，当id为0是无效id
	int8				m_iFamilyPos;		// 家族职位

    DWORD				m_dwCharacterID;	// 角色DBID

	GuildIcon		m_strGuildIcon;
	// 官衔等级
	BYTE				m_byOfficialLevel;
	
	// 功勋值
	DWORD				m_dwExploit;
	// 声望
	DWORD				m_dwReputation;
	// 帮贡
	DWORD				m_dwGuildOffer;

	// 荣誉
	DWORD				m_dwGlory;

	// 战场积分
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

	CPlayerAnim*		m_pAnim;					//人物动画
	CPlayerAnim*		m_pMountAnim;				//坐骑动画
	CPlayerAnim*		m_pMorphAnim;				//形体动画

	int					m_nSpineBoneID;				//人物的上下身的骨骼位置
	int					m_nRightHandBoneID;			//人物的右手位置
	int					m_nLeftHandBoneID;			//人物的左手位置
	int					m_nBackBoneID;				//飞行特效位置

    FLOAT					m_vSaveXYGetZ;
    int						m_iPlayerStatus;

    //体型修正
    float					m_fBodySize;
    float					m_fBodyLengthSize;
    float					m_fWeaponAttackRange;
    short					m_ustWeaponAttackRange;
    //普通攻击的发射特效ID,set in CPlayerAnim::ChangeSkeletonAndEquipAll
    int						m_iShotEffectID;
    int						m_iWeaponType;
    BOOL					m_bNeedRender;
	DWORD					m_dwLastRenderTime;
    bool					m_bHasUpdateAnim;			// 模型加载完，等UpdateAnimSetting执行后再渲染
    bool					m_bNpcGetBodySize;			// Npc获得缩放值
    uint32					m_stTeamId;
    char					m_cTeamPosition;
	bool					m_bHide;					// 是否显示，目前仅用于NPC

    CCharEffectContainer* m_pCharEffectContainer;

	//add by yanli  2010-9-27		
	//all equipment
	CPlayer_SEquipment			m_equips[eKeyAll_Max];

    // seek equip时传来的装备信息，包括时装
    SCharItem m_equipitemSeekEquip[EEquipPartType_MaxEquitPart];

	//效果NPC
	DWORD				m_dwDisplayAfterTime;
	DWORD				m_dwLastUpdateTime;

	// npc 专用
	int					m_nNpcTipsType;
	int					m_nImageType;

    // 头顶上的对话框
    ControlText		*m_pChatPaoPao;
    int				m_nOldChatDialogBoxX;
    int				m_nOldChatDialogBoxY;
    DWORD			m_dwChatDialogBoxBornTime;
    DWORD			m_dwChatDialogLifeTime;

    //自身的状态特效结构
    struct SStatusEffect
    {
        int		nStatusID;			//该状态的ID编号	
        int		nLevel;				//该状态的等级
        int		nEffectID;			//特效管理器内的ID
        BOOL	bEffectKeep;		//特效是否维持
		IEffect* pEffect;           //保存特效指针，主要目的用于判断删除特效时，通过nEffectID获得的指针是否相同

        SStatusEffect()
        {
            nStatusID = -1;
            nLevel = -1;
            nEffectID = -1;
            bEffectKeep = FALSE;
			pEffect = NULL;
        }
    };

    //自身的所有状态特效
    typedef std::list<SStatusEffect>        StatusEffectContainer;
    typedef StatusEffectContainer::iterator ItrStatusEffectContainer;
    StatusEffectContainer m_listStatusEffects;

	//////////////////////////////////////////////////////////////////////////
	// 五行相关
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
	int m_nMainElement; // 主要元素，-1时为不显示
	int m_nMaxElementCount; // 主要元素强度（数量）
	//////////////////////////////////////////////////////////////////////////
	//
	struct SMove
	{
		BOOL			bHalfStep;					//是否走到一半，如果为fase，则认为新的一步开始
		DWORD			dwTimeLeft;					//上一步的多余时间
		DWORD			dwStartTime;				//开始走的时间
		DWORD			dwStepTime;					//一步的时间
		D3DXVECTOR3		vStartPos,vEndPos;			//起始位置，结束位置,(象素坐标)
        POINT           tEndPoint;                  //移动的目标位置(图素级别)
		float			fVelocity;					//速度，每秒?格
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
    //移动速度
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
    //人物身体上附加的战斗状态
    SCharBuff	stBodyStatus[BodyStatusType_Max];	//人物身上能有的状态,记录数据
    SkillRuntimeDesc m_skillRuntimeDesc;

    /*SCharItem m_CharEquipItem[EPT_MaxEquitPart];*/


    //
// 	bool    GetNextStep(void);
	// 当前正在使用的attack info
	SAttackInfo*				m_pAttackInfo;
	//
	short			GetMovingType( float fCurDir, float fMovingDir );
	//Action结束时间
	void			HandleActionQueue( bool bSkipStatus = false );
	void			HandleMoveQueue( BOOL bHang = FALSE );
	////////
	CMoveQueue				m_MoveQueue;		//	移动队列
	CMoveQueue::SMove		m_NowMove;	//	当前的移动
	////////
	CActionQueue	m_actionQueue;      //	npc的行为堆栈...保存服务器发过来的行为...
    CActionQueue::SAction   m_NowAction;//	npc但前正在执行的行为，pop处理后会纪录

	//角色刚进入玩家视野的时候，并不知道血量
	//某些条件触发 服务器下发 当前血量
	//		玩家鼠标 处于角色之上
	//		玩家当前的攻击对象
	//		
	//由于主角能看到的 角色被攻击 减血
	//所以不用每回都查询

	//某些情况下，会有血量变化
	//		如:角色升级
	//			
    //这时要重新从服务器获取血量

	//TODO ext:组队对友的血量
	//	   角色吃药造成的血量变化，需要下发

	struct SCharHPInfo
	{
		int nHp, nHpMax;

		//short stHP,stHPMax;

		//血条是否有效
		bool bIsValid;

		//当前显示的percent
		float fShowPercent;
		//前一个血条
		float fPrevPercent;
		//将要到达的
		float fTargetPercent;
		//fPercent * fTargetPercent + (1-fPercent)*fPrevPercent;
		//fPercent速度:0.002
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
	unsigned char  m_ucSitStatus;	//坐在地上的标志
	unsigned char  m_ucSitInterrupt;//坐下被打断的标志
	unsigned char  m_ucFightStatus;	//战斗模式
	unsigned char  m_ucSex;			//性别
	unsigned char  m_ucProfession;	//职业
	//
	unsigned char  m_ucToFightStatus;//需要切换到的战斗状态
	//
	//是否显示血条
	bool m_bShowHP;
    
    unsigned char m_ucLiftFlagStatus;   // 举旗状态

public:
	BOOL	HasAttackActionQueue(){ return m_actionQueue.GetAttackActionNum(); }

private:
	BOOL	RoleMoveToShore( D3DXVECTOR3& vNextPos, D3DXVECTOR3& vNextDir, BOOL& bCollision, float fRoleHeight, float fCurMoveDist );				//主角能否移动到岸上

	DWORD m_startfeartime;
	D3DXVECTOR3 m_vTargetPos;

	D3DXVECTOR3 m_vTeamFollowLastPos;	//组队跟随上一次的跟随地点

//----------- 显示服务器需求的小方格  -----------
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
    static CBaseGraphics::Vertex3D m_vtHeightMapRect[ HEIGHTMAP_SHOW_RECT_CNT * HEIGHTMAP_SHOW_RECT_CNT * 6 ]; // 只显示最近的45*45格子
//-----------------------------------------------

public:

	//
	//	服务器发送过来的攻击失败的消息处理
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
    bool                m_bCanPick; // 主角可以捡，m_stCharType必须是eItem_CHAR类型

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

	void    SwitchAnim(CPlayerStatus::STATUS_KEY PreStatus, DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);    //切换到需要状态的动画

	void				Dead();

	bool				IsOpenPrivateShop(){ return m_bOpenPrivateShop; }

	//	bTooClose返回是否技能最小攻击范围之内
	bool				IsInAttackRange( float fTargetX, float fTargetY, float fTargetBodySize, ItemDefine::SItemSkill *pSkill, BOOL* bTooClose=NULL );
	bool				IsInAttackRangeOnlyTwoPoint( float fTargetX, float fTargetY, float fTargetBodySize, ItemDefine::SItemSkill *pSkill, bool bCalibrate = false, BOOL* bTooClose=NULL );
	BOOL				IsTargetInFront( float fTargetX, float fTargetY, float fTargetZ, float fAngleMax = D3DX_PI/2 );

	float				GetDistToTarget( float fTargetX, float fTargetY );

public:
	CActionQueue*		GetActionQueue(){ return &m_actionQueue; }
	CMoveQueue*			GetMoveQueue(){ return &m_MoveQueue; }
	//堆一些服务器发过来的基本行为队列的执行
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
	void				ClearEffStatus();		//清除状态特效
	bool				IsWillPlayDropAnim(){return m_bItemPlayedDropAnim;	}
	void				SetWillPlayDropAnim(bool value){m_bItemPlayedDropAnim = value;}
private:
	
	void CaluHPPercent(void);

	DWORD m_dwDeadOverTime;

	//引用计数
	int		m_iRef;
	//需要删除
	bool	m_bNeedToDelete;
	//
	DWORD	m_dwShowFlag;
	// 战斗状态
	DWORD			m_dwFightFlag;
	BOOL			m_bPendingClearFightFlag;	// 战斗动作未播完，延时结束战斗，QL，2009/04/25
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
	void	TurnCameraToPlayer( DWORD time );	//使得摄像机朝向与人物朝向一致

	//lyh维持技能动作处理
	bool GetSkillAnimLoopCnt(int &Times ,ItemDefine::SItemSkill * _skill); 

	// 能否纠正坐标
	BOOL	NeedVerifyPos( D3DXVECTOR3 vPos, float fVerifyRange = NeedVerifyDistance );
	void	ReSetPos( float fx, float fy, float fz );

	void	SetWeaponSound( const char* pWeaponSound );
	const char*	GetWeaponSound();
	void	SetArmourSound( const char* pArmourSound );
	const char*	GetArmourSound();

	//准备发动技能
	void	ReadyToLaunchSpecialSkill( short shStartPermillage );
	//暂停准备
	void	CancelReadyToLaunchSpecialSkill();
	//开始技能倒计记时
	void	StartCountDownSpecialSkill();

	//停止移动
	void	StopMoving(bool bAction =false);
	//坐的动作
//	void	SwitchSitAnim(DWORD dwTimeOut);
	//切换到，莫个动作
	void	SwitchActionAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到死亡的动画
	void    SwitchDieAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到死亡动画的最后
	void	SwitchDieOverAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到行走的动作
	void	SwitchWalkAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到倒退动作
	void	SwitchWalkBackWardsAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout, DWORD dwBlendingTime = 0);
	//切换到转身动作
	//void	SwitchShuffleAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到向左转身的动作
	void	SwitchShuffleLeftAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到向右转身的动作
	void	SwitchShuffleRightAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到跑步的动作
	void    SwitchRunAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到游泳的动作
	void	SwitchSwimAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到水中待机的动作
	void	SwitchSwimIdleAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到起跳动作
	void	SwitchJumpAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到滑翔动作
	void	SwitchGlide(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到下落动作
	int	SwitchDropAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);		// 返回Drop动画的播放时间
	//切换到准备角色的特有动作
	void	SwitchReadyToSpecialAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换角色特有动作
	void	SwitchSpecialAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
    //切换到待机动作
    void    SwitchIdleAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout, DWORD dwBlendingTime = MexAnimCtrl::eDefaultBlendingTime);
	//切换到眩晕动作
	void	SwitchStunAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到特殊待机动作
	void	SwitchSpecialIdleAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
    //切换到战斗动作
    void    SwitchAttackAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	BOOL	SwitchAttackAnim( unsigned short ustSkillId, unsigned short ustSkillLevel, DWORD* pGetHitPointTime = NULL, DWORD* pGetEndFrameTime = NULL );
	//切换到施法动作
	void	SwitchSpellAnim( DWORD dwEmissionFlyTime, GameObjectId ustTargetId, unsigned short ustSkillId, unsigned short ustSkillLevel, DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	//切换到呤唱动作
	void	SwitchIntonateAnim(DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);
	void	SwitchIntonateAnim(DWORD dwTimeOut, ItemDefine::SItemSkill* pSkill );
	//播放目标特效
	void    PlaySpellEffect(DWORD dwEmissionFlyTime,GameObjectId ustTargetId,unsigned short ustSkillId,unsigned short ustSkillLevel,DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout);

	//Pick
	void	SwitchPickAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout );
	//切换到持续技能
	void	SwitchHoldSkillAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout );
	//切换到躲避动作
	void	SwitchDodgeAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout );
	//切换到被击动作
	void	SwitchHurtAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout );
	//切换格挡动作
	void	SwitchDefendAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout );
	//切换到拔刀
	void	SwitchScabbardAnim( DWORD dwTimeOut = MexAnimCtrl::eMaxTimeout, BOOL bPlayScabbard = TRUE );
    // 切换到举旗动作（上半身）
    void    SwitchLiftFlagAnim();
    // 播放拥抱动作
    void    SwitchEmbraceAnim();
	//播放复活动作
	void    SwitchReliveAnim();
	// 播放掉落动作主要用于物品
	void    SwitchDropItemAnim();

	void	PlayAnim( const char* szName, int nTimes, const char* szEndName );

	// 播放gamesetting中配置的动作，服务器发来。（npc采集等）
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
    // 清除当前的动作序列
    void ClearActionQueue();

	//设定 某个部位的装备
	void SetEquip( short stWhere,SCharItem *pItem );
	//设定 所有的装备
    void CPlayer::SetAllEquip( SCharVisual* pVisual, bool isautocs = true );
	/*void SetEquipByItemID(short stItemID[EPT_MaxEquitPart], short equipIntensifyTime[EPT_MaxEquitPart], short equipIntensifyStar[EPT_MaxEquitPart], short equipElements[EPT_MaxEquitPart], CPlayer_SEquipment* pEquip);
	void EquipByItemID(short stItemID[EPT_MaxEquitPart], short equipIntensifyTime[EPT_MaxEquitPart], short equipIntensifyStar[EPT_MaxEquitPart], short equipElements[EPT_MaxEquitPart] );*/
	void SetEquipByItemID(uint16 stItemID[], uint8 equipIntensifyTime[], uint8 equipIntensifyStar[], uint8 equipElements[], CPlayer_SEquipment* pEquip);
	void EquipByItemID(uint16 stItemID[], uint8 equipIntensifyTime[], uint8 equipIntensifyStar[], uint8 equipElements[] );
	void SetEquipPart(int nWhere,short stItemId);  //单独设置头发和脸

	//穿戴所有的物品
	void ChangeSkeletonAndEquipAllItem(bool bFightFlag);
	//清空人物身上所有的状态
	void ClearAllBodyStatusEff(void);
	//设置人物状态的上图效果
	void CheckBodyStatusEff(void);

	void SetHPInfo( int nHp, int nHpMax );

	void ResetHPInfo( void );
	void DecHP( int iHPDec );
	void IncHP( int iHPDec );
	//主角升级后会用到
	void SetHPInfo_HP( int nHp );
	void SetHPInfo_HPMax( int nHpMax );
    void SetHPInfo_HPChange( int nHp );     //负值表示伤血，正值表示加血
	int GetHpInfo_HPMax(){return m_hpinfo.nHpMax;}


	//记录斗气值
	void SetExPower( int nExPower );
	int  GetExPower(){ return m_nExPower; }
	bool IsHPInfoValid(void);
	BOOL OnShowFlyText( int nBalanceType, int nNum, int nAddNum = 0, int nWordType = 0,/*bool bExplosive = false, bool bExp = false,*/bool bIsPlayer = false );
	bool OnShowFlyText( CPlayer *pTagPlayer, CPlayer *pSrcPlayer, int iBalanceType, int iTagNum, int iScNum, int nAddNum = 0, bool bExplosive = false );
	bool OnShowFlyPic( int nType );
	//到了攻击帧需要做的事情
	bool OnHitPoint(BOOL bLastHitPoint, int nHitPointType,SAttackInfo *pAttackInfo = 0 );

	/*
	 * Author:	2012-8-3 wangshuai
	 * Desc: 	显示伤害数字
	 */
	void ShowDamageNumber(CPlayer *destPlayer, const SAttackInfoRecord *record);

    void ShowFightInfo(CPlayer* pSrcPlayer,CPlayer* pDestPlayer,SAttackInfoRecord* pRecord,ItemDefine::SItemSkill *pSkill);  //显示战斗信息

	//取得对应动作的编号
	int		GetPlayerActionID(int ActionID, int iFightType = -1);
	//判断是否有武器
	bool	IsHaveWeapon(int iWeaponType = -1); // bCanHoldFlag判断武器时是否包括旗子
	bool	IsHaveLHardWeapon( );
	BOOL	IsDoubleHandWeapon();
	//判断是否有盾
	BOOL	IsHaveShield();
	void	SetShowWeapon(BOOL bShow, BOOL bShowAfterBlend = FALSE);
	//
	unsigned char	GetSitStatus(void)		{ return m_ucSitStatus; }
	unsigned char	GetSitInterrupt(void)	{ return m_ucSitInterrupt; }
	unsigned char	GetFightStatus(void);//战斗模式
	unsigned char	GetSex(void);//性别
	unsigned char	GetProfession(void);//职业
	unsigned char	GetToFightStatus(void)	{ return m_ucToFightStatus; }//。。需要切换到的战斗模式
	int				GetHairColorIndex()		{ return m_nHairColorIndex; }
    unsigned char   GetLiftFlagStatus(void) { return m_ucLiftFlagStatus; }
    void    UpdateLiftFlagStatus(void);
	//
	void SetSitStatus(unsigned char status);
	void SetSitInterrupt(unsigned char status) { m_ucSitInterrupt = status; if(status) SetShowWeapon(TRUE); }
	void SetFightStatus(unsigned char);//战斗模式
	void SetSex(unsigned char);//性别
	void SetProfession(unsigned char);//职业
	void SetToFightStatus(unsigned char);//..需要切换到的战斗模式
	void SitInterrupt();	// 打断当前坐下状态
    void SetLiftFlagStatus(unsigned char status) { if( m_bMounting && status > 0 ) m_ucLiftFlagStatus = status; else m_ucLiftFlagStatus = 0; }  // 只在马上能举旗
	
	void OnBuffsUpdate ( MsgBuffsUpdate*  pMsgBuffsUpdate  ); // buff list
	void OnBuffsChanged( MsgBuffsChanged* pMsgBuffsChanged ); // buff changed
    void OnBuffsUpdateOrChangedRender();

	//  清除npc身上的所有战斗状态
	void	OnClearAllBodyStatus();
	//Player对象在销毁前执行所有的动作队列
	void	ExcuteClearActionQueue( void );

	void    OnClearAllBodyStatusByDead();

	//引用计数
	void	AddRef( void );
	void	DecRef();
	int		GetRef() const{ return m_iRef ; }
	//true:可以删除，false:还有引用
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
	BOOL m_bCountermarch; //是否在后退
	BOOL m_bPlayedCoutermarchAnim;
	BOOL m_bLastFrameMoving;
	BOOL m_bCreateUpDataZ;

	///////////////
	// 斗气相关
	int  m_nExPower;		    // 当前斗气
	bool m_bUpdateExPowerEff;   // 更新斗气特效
	int  m_nFPTotal;		    // 斗气最大值
	int  m_nFPTotalBall;	    // 斗气球,现在最多4个,平分100
	int	 m_nFPCurrentBallCount;	// 当前斗气球数

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

	BOOL IsCountermarch(); //是否在后退
	void SetCountermarch( BOOL bCountermarch ); //设置是否后退

	bool CalcRoleMovePath(const D3DXVECTOR3& targetPos,bool bSync);

private:
	DWORD m_dwStartStopMovingTime;
	int	  m_nHairColorIndex;

public:
	CMovePath m_movepath;
	float m_fSpeed;

public:
	void HangMoving( DWORD dwCurTime, DWORD dwTimeLenght ); //挂起移动
	BOOL IsHangMoving( DWORD dwCurTime );

private:
	BOOL m_bHangMoving; //挂起移动
	DWORD m_dwStartHangMovingTime; //开始挂起移动的时间
	DWORD m_dwHangMovingTimeLength; //挂多少时间

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
	// 上半身的旋转极限
	float m_fUpperBodyRotLimit;
	BOOL m_bTwoHalfBody;                     //是否上下半身怪物
	BOOL m_bFourFoot;                        //是否四足怪物

public:
	void Jump();
	BOOL IsJumping(){ return m_bJumping; }
	void SetStartJumpingSpeed( float fSpeed ){ m_fStartJumpingSpeed = fSpeed; }
	float GetStartJumpingSpeed(){ return m_fStartJumpingSpeed; }
	void SetJumpingSpeed( float fSpeed ){ m_fJumpSpeed = fSpeed; }

private:
	// 开始起跳
	BOOL m_bJumping;
	// 跳跃的类型
	short m_shJumpingType;
	// 开始起跳时间
	DWORD m_dwStartJumpingTime;
	// 角色的跳跃高度
	float m_fJumpingHeight;
	// 角色的起跳的地表高度
	float m_fStartJumpingTerrainZ;
	// 角色向前跳的速度
	float m_fJumpSpeed;
	// 角色向上跳的初速度
	float m_fStartJumpingSpeed;
	// 角色向上跳的最大初速度
	float m_fMaxStartJumpingSpeed;
	// 角色是否需要下落缓冲
	BOOL m_bNeedDropBuf;
	// 角色播放了下落动作
	BOOL m_bPlayedDropAnim;

public:
	void MorphMonster( int nMonsterId, bool bPrivateShop = false );		//变形成怪物
	void DisMorph();							//取消变形
	bool IsMorph();								//是否变形
	bool IsMorphInThread() const{ return m_bMorphInThread; }
	void SetMorphInThread( bool bMorphInThread ){ m_bMorphInThread = bMorphInThread; }	//正在变形
	void SetMorph(bool b);  //设置变身

private:
	bool m_bMorphing;							//是否在变形
	bool m_bMorphInThread;						// 是否正在处理变形逻辑
	int m_nMorphMonsterID;						//变形的模型ID

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
	void SetMountInThread( BOOL bMountInThread ){ m_bMountInThread = bMountInThread; } // 正在骑马中，还未骑上，多线程处理中
	BOOL MyTeamMember;
	INT  ManipleID;

	/*
	 * Author:	2012-7-30 wangshuai
	 * Desc: 	获取坐骑缩放修正值
	 */
	float GetMountScaleFix() const { return m_fDromeScaleCorrect; }
private:
	bool			m_bAutoDismount;			//自动下马释放技能与攻击
	BOOL		m_bMounting;					// 是否正在骑乘
	bool		m_bMountInThread;
	int			m_nMountModelID;
	int			m_nMountLevel;
	int			m_nMountBoneID;
	float		m_fDromeScaleCorrect;			// 坐骑体型修正
	float		m_fRiderScaleCorrect;			// 骑手体型修正

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
	float m_fDistanceToRole;        //和主角的距离
    float m_fDistanceToPickRay;      //和鼠标pick的From点之间的距离

public:
	BOOL IsInWater();
    void SetInWater(BOOL bIn);

private:
	BOOL m_bInWater;//是否在水里
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
	float	m_fShowNameAphla;					//显示名字的半透明值

private:
	CPlayer* m_pIntonateTarget;					// 吟唱对象
	GameObjectId	m_nIntonateTargetID;				// 吟唱对象id
	BOOL	m_bIntonating;						//是否在吟唱
	int		m_nIntonatingEffectID;				//吟唱特效ID
	DWORD	m_dwIntonatingStartTime;			//吟唱开始的时间
	bool    m_bCanInterruptIntonating;          //是否能中断吟唱,主要用于旋风斩
	DWORD	m_dwIntonateDelayTime;				//吟唱持续时间
	string	m_strIntonateName;					//吟唱名字
private:
	DWORD m_dwLastUpdateAnimTime;						//最后更新动画的时间

private:
	D3DXVECTOR3			m_vCurNormal; //当前相对地表的法线偏移
	D3DXVECTOR3			m_vTargetNormal; //将要偏移到的目标法线
	float				m_fCurRotationX; //角色当前的前后倾斜角度
	float				m_fTargetRotationX; //角色目标倾斜角度

private:
	DWORD m_dwSpecialIdleInterval; //特殊待机的播放间隔

private:
	short m_shCurMovingType; //当前的移动状态

public:
	void ResetRenderAlpha();//{ m_fCurRenderAlpha = 0.0f; } //重设渲染透明度
	void SetCurRenderAlpha( float fAlpha ); //设置当前的透明度
	void SetFinalRenderAlpha( float fAlpha ); //设置最终的透明度
	void SetDefaultFinalRenderAlpha( float fAlpha );//设置默认的最终透明度
	float GetFinalRenderAlpha(); //获得最终的透明度
	float GetCurRenderAlpha(); //获取当前的透明度
	float GetDefaultFinalRenderAlpha();//获取默认的最终透明度

private:
	float m_fCurRenderAlpha; //当前渲染透明度
	float m_fFinalRenderAlpha; //最终渲染透明度
	float m_fDefaultFinalRenderAlpha; //默认渲染透明度

private:
	BOOL m_bAssaultMoving; //是否在冲锋移动
	GameObjectId m_shAssaultTargetID; //冲锋目标的ID
	void AssaultMoving( GameObjectId shTargetID ); //冲锋移动

//HardCode
private:
	bool			m_bInstantMoving;							//是否瞬间移动
	ItemDefine::SItemSkill* m_pInstantSkill;					//当前瞬移的技能
	EInstantMovingType m_eInstantMovingType;					//瞬移类型
	D3DXVECTOR3		m_vInstantTargetPos;						//瞬移的目标点
	float			m_fInstantMovingDir;						//瞬移的目标方向
	DWORD			m_dwInstantMovingStartTime;

	void			InstantMoving( D3DXVECTOR3 vTargetPos, bool bCheckPos = true );	//瞬间移动

	void			SetInstantMoving( bool bMoving, ItemDefine::SItemSkill* pSkill );
	bool			TryInstantSkill( ItemDefine::SItemSkill* pSkill );

public:
	void			SetInstantTargetPos( const D3DXVECTOR3& vTargetPos, float fDir, EInstantMovingType type, ItemDefine::SItemSkill* pSkill );		//设置瞬移的目标点

private:
	BOOL	UncontrolMoving( D3DXVECTOR3 vTargetPos, BOOL bTestCollision ); //不能控制的移动
protected:
	BOOL			m_bUncontrolMoving;		//不能控制的移动
	BOOL			m_bUncontrolFlying;		//不能控制的飞行
	D3DXVECTOR3		m_vUncontrolMoveTargetPos; //不能控制的移动的目标点

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
	BOOL	m_bNeedToRemove;		//是否要移除
	DWORD	m_dwStartRemoveTime;	//开始准备移除的时间

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
	int				m_nRippleEffectID;				//水中涟漪的特效ID
	int				m_nRippleEffectContainerID;		//水中涟漪绑定体的ID
	int				m_nBoatRippleEffectID;				//水中涟漪的特效ID
	int				m_nBoatRippleEffectContainerID;		//水中涟漪绑定体的ID
	float			m_fRippleEffectPlaySpeed;		//水中涟漪的播放速度
	DWORD			m_dwRippleEffectOverTime;		//水中涟漪的结束时间

	int				m_nWaterSideRippleEffectID;				//水边涟漪的特效ID
	int				m_nWaterSideRippleEffectContainerID;	//水边涟漪绑定体的ID
	float			m_fWaterSideRippleEffectPlaySpeed;		//水边涟漪的播放速度
	DWORD			m_dwWaterSideRippleEffectOverTime;		//水边涟漪的结束时间

	// 斗气特效
	int				m_nFightPowerEffectID;			// id
	int				m_nFightPowerEffectContainerID; // 

private:
    //满星特效
	bool			LoadFullStarEffect(const char* name, int& iRetEffectID, int& iRetEffectContainerID );
	void			HideFullStarEffect(int iEffectID);
	void			ShowFullStarEffect(float x, float y, bool setScale, float scale, int iEffectID, int iEffectContainerID, int iInstance);

private:
	// 满星特效
	int				m_nFullStarEffectID;
	int				m_nFullStarEffectContainerID;
	int				m_nFullStarEffectID2;
	int				m_nFullStarEffectContainerID2;

public:
	//玩家阻挡
	BOOL	IsBuildPlayer();
	BOOL	IsMaskPlayer()			{ return m_bMaskPlayer; }
	VOID	SetMask( BOOL bMask ) { m_bMaskPlayer = bMask; }
	Box* GetBox();
	FLOAT	GetPlayerHeight();

public:
	void			SetFinStatusColor( D3DXVECTOR3 vColor );

private:
	D3DXVECTOR3		m_vCurStatusColor;	//当前的状态颜色
	D3DXVECTOR3		m_vFinStatusColor;	//最终的状态颜色

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

    //-----PK模式---------------------------------------------------
private:
	short m_shLastPkTye;
    short m_shPKType;       // 用PersonKiller::ePKFlag枚举类型
    short m_shBattleFlag;
    BOOL  m_bIsDuel;

public:
    void SetDuel(BOOL bDuel) { m_bIsDuel = bDuel; }
    BOOL IsDueling() { return m_bIsDuel; }
    //--------------------------------------------------------------

    /** 负责在一定时间内调用UpdateAnimSetting，否则会图形破面。
    */
    void updateAnimNotRender();

    /** 是否可以攻击目标
    */
    bool canAttack( CPlayer* target );
	void	GetPFPos(  float &fX, float &fY );
	bool isNPCCanAttack( CPlayer* target );

private:
    /** 是否可以攻击目标玩家
    */
    bool _canAttackPlayer( CPlayer* target );

    //--------------------------------------------------------------

    // 当前装备索引
    int m_currSuitIndex;

    // 显示头盔
    bool m_isShowHelmet;
	bool m_isShowSignature;	//显示签名
	//显示时装
	bool m_isShowAecpratove;
	//第几套默认索引,共两套
	int  m_nDefAvaterIndex;
	//显示主将变身效果
	bool m_isShowHero;

	//显示军阶
	bool m_isShowRankTitle;
	short m_shRankTitleId;
public:
    // 显示头盔
    void ShowHelmet(bool v);
    void ShowHelmetAndSendMsg(bool v);
    bool IsShowHelmet() const;

	//显示角色心情
	void ShowSignature(bool v);
	void ShowSignatureAndSendMsg(bool v);
	bool IsShowSignature(void) const;
	void SetSignature(const char *pSignature_);
	const char *GetSignature(void){return m_signature.c_str();}

	//显示军阶
	void ShowRankTitle( bool v );
	bool IsShowRankTitle() const;
	void SetRankTitleId( short titleId );
	short GetRankTitleId();

	//显示时装
	void ShowAecpratove(bool v);
	void ShowAecpratoveAndSendMsg(bool v);
	bool IsShowAecpratove() const;

	//主将变身效果
	void SetShowHero(bool b){m_isShowHero = b;}
	bool IsSHowHero() const
	{return m_isShowHero;}

	//默认索引
	int GetDefAvaterIndex(){return m_nDefAvaterIndex;}
	void SetDefAvaterIndex(int nIndex){m_nDefAvaterIndex = nIndex;}

    // 是否是时装
    /*void SetCurrSuitIndex(int v) {
        m_currSuitIndex = v;
    }*/

    /*bool IsFashion() const {
        return m_currSuitIndex >= SCharVisual::ShowSuitBeginIndex;
    }*/

	//跟随player走的称号list by vvx
	vector<ItemDefine::ReputeStruct>PlayerOwnList;
	vector<ItemDefine::ReputeStruct>&	GetPlayerReputeList(){return PlayerOwnList;}

	void	clear();
	short   GetReputeID(int vecIndex);
	void CallForRepute(DWORD flag);

	struct BinaryList					//此结构和server端的C_Character::SReputeFlag相对应，最多可以有27个称号
	{
		DWORD a:6;					//当前的称号的ID，(因为2的5次方等于32，足够表示27个旗标的索引)
		DWORD b:26;				//打开的称号的旗标
	};

	// 寻路
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
	bool	m_bAutoRuning;//行动距离超过CPathDirection::MinPathLenghtForDirection米
	//
    // Font
    //

public:
    //----------------称号----------------------------------
    void SetTitleInfoById( int nId ,const char* pszName = NULL);
	void SetTitleId( int nId ){ m_nTitleId = nId; }
	int GetTitleId(){ return m_nTitleId; }
	void SetTitleColor( DWORD dwColor ){ m_dwTitleColor = dwColor; }
    void SetTitle(const std::string& title) { m_strTitle = title; }
    const std::string& GetTitle() const { return m_strTitle; }
	void SetTitleTargetName(const char* name);
	const char* GetTitleTargetName() {return m_szTitleTargetName.c_str();}
private:
    //称号
    int              m_nTitleId;
    std::string      m_strTitle;
    DWORD            m_dwTitleColor; // 称号颜色
    std::string      m_szTitleTargetName;   // 关系称号附带的名字
	std::string m_signature; //心情
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

// 智能鼠标需要先旋转后释放技能
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
	DWORD m_dwStopMoveTime; // 释放了不能移动的技能，在该时间前不能移动
	DWORD m_dwStopJumpTime;	// 释放了不能跳跃的技能，在该时间前不能跳跃

	DWORD m_dwDropEndTime;		// Drop动画结束时间

	// 战斗姿势，非战斗中显示战斗待机动作，按X切换
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

    BOOL IsSittingAnim()    // 包含坐下，持续坐着，和站起动作
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

	// 上次收刀/拔刀开始时间，间隔1秒以上才能再次收到或拔刀
	DWORD m_dwLastScabbardBeginTime;
public:
    //-----------------脚印-----------------------------
	BOOL				IsNeedShowFootPrint();
	CFootPrint*         GetFootPrint();
    void                RenderShadowDecal( BOOL bCombineRenderShadowDecal = FALSE );
protected://脚印
	void				UpdateFootPrintDetail();
	float				m_distanceDelta;//为了脚印
	float				m_distanceDeltaForDynamicLoad;//为了动态加载
	CFootPrint*			m_footPrint;
    //-------------  脚印End-------------------------------------

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
	bool				m_bSelectAoePoint;	// 是否正在选择aoe点
	D3DXVECTOR3			m_vPointAoePos;		// aoe 释放点

    BOOL                m_bIsCurRandRun;    // 保存当前RandRun状态
    BOOL                m_bIsCurStun;       // 保存当前Stun状态
    BOOL                m_bIsCurFreeze;     // 保存当前Freeze状态

	BOOL				IsRenderParticleEmitters();

    BOOL                IsCollectionAnim(const char* szAnim);

    // 提前播动作的技能
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
        int                         nNeedPlayHurtAnim;  // 伤害型有目标的单体技能，需要预拨受击动作
        int                         nTargetPlayerID;    // 受击目标
    };
    std::vector<SAdvanceSkillData> m_vctAdvanceSkill;    // 提前播动作的技能列表

    void                PlayAdvanceSkillHurtAnim(int nPlayerID, ItemDefine::SItemSkill* pSkill);

public:
	BOOL LoadMtlEffect( const char* pszFileName );
    // 互动动作
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
    int     m_nInteractionMasterPlayerID;   // 拥抱发起方玩家ID，如果自己是主动方则为-1
    BOOL    m_bNeedResetPosAfterInteraction;// 拥抱结束后检查Z值

// NPC Idle动作
public:
	void    TryPlayNpcAction();
	void    ProcessNpcAction();
    bool    IsHaveAppeaseRequire(Require *pReq);
    void    InitNpcAction(DWORD dwTime);        // NPC进入视野，初始化动作
    void    ExitNpcAction();        // NPC离开视野，结束动作
    void    UpdateNpcAction(DWORD dwTime);
protected:
    DWORD   m_dwNextActionTime;     // NPC出视野后m_bNextActionTime赋为0
    short   m_shNextActionId;
    BOOL    m_bNeedInitNpcAction;   // NPC名字未拿到前，保存需要初始化动作的标记

	DWORD   m_dwNpcActionTime;  //开始时间
	Action  m_act;
	bool    m_IsSearch;         //是否收缩NPC
	DWORD   m_dwSearchCD;       //查找CD,放置每帧不停查找

    int     m_iBuffStatusAnimType;  // 状态动作类型

    // 召唤兽是否可见
    BOOL    m_bIsVisibleToOtherPlayer;    // 枚举类型，定义见ItemDefine::SMonster
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
	// [玩家模型加载机制],[QL]
	// 玩家进入视野，模型数据默认不加载，满足某些条件后才加载并播动作
public:
	BOOL	IsModelLoaded() { return m_bModelLoaded; }
	void	UpdateFakeWorldBBox(float x, float y, float z);
	void	LoadModel();
protected:

	BOOL	m_bModelLoaded;
	BOOL	m_bPrivateShop;		// 保存坐骑ID，<=0表示没上马
	Box		m_fakeWorldBBox;			// 没模型数据时，替代的WorldBBox
#endif

	// Player类型
public:
	enum PlayerType
	{
		PT_Me					= 1<<0,		// 自身
		PT_MyPet				= 1<<1,		// 我的召唤兽或奴仆
		PT_TeamPlayer			= 1<<2,		// 队友
		PT_TeamPlayerPet		= 1<<3,		// 队友的召唤兽或奴仆
		PT_EnemyGuildPlayer		= 1<<4,		// 敌对帮会玩家
		PT_EnemyGuildPlayerPet	= 1<<5,		// 敌对帮会玩家的召唤兽或奴仆
		PT_LeaguePlayer			= 1<<6,		// 同盟玩家
		PT_LeaguePlayerPet		= 1<<7,		// 同盟玩家的召唤兽或奴仆
		PT_MyGuildPlayer		= 1<<8,		// 自己帮会玩家
		PT_MyGuildPlayerPet		= 1<<9,		// 自己帮会玩家的召唤兽或奴仆
		PT_NormalPlayer			= 1<<10,	// 普通玩家
		PT_NormalPlayerPet		= 1<<11,	// 普通玩家的召唤兽或奴仆
		PT_RedNamePlayer		= 1<<12,	// 红名，敌对玩家
		PT_RedNamePlayerPet		= 1<<13,	// 红名，敌对玩家的召唤兽或奴仆
		PT_PKPlayer				= 1<<14,	// PK玩家
		PT_PKPlayerPet			= 1<<15,	// PK玩家的召唤兽或奴仆
		PT_Monster				= 1<<16,	// 怪物
		PT_Other				= 1<<17		// 其他
	};

	DWORD GetPlayerType();

protected:
	void AdjustAttackPos();		// 纠正攻击双方高度，如果一方是怪一方是玩家，则纠正怪高度

	void AdjustPosToMaster();
	float m_fPetAdjustPosCD;	// 如果是召唤兽，每秒纠正一次高度，防止掉模型下面上不来，单位秒，默认为2秒
public:
    int  GetInfluence() const {return m_nInfluence;}
    void SetInfluence(int nValue);
	bool IsSameInfluence(const CPlayer*);
    void SetActionFluence(int nValue){m_nActionFluence = nValue;}
    void SetUpdateActionFluence(bool bValue){m_bUpdateFluence = bValue;}
    void SwitchCampAnim();    //切换阵营战场动画
private:
	int m_nCampType;
    int m_nInfluence;           //用于判断是否属于同一个阵营，主要用于PK判断, //默认enumBattleInfluence_Max 无阵营
    int m_nActionFluence;        //动作播放，该变量的作用主要记录在阵营战场中，被谁占领，只对NPC有效果，从MsgNPCEnterMySight中传过来
    bool m_bUpdateFluence;       //是否需要跟新阵营中动画动画
public:
	void InitMonsterAction(int nIndex,SArea *pArea);
	void UpdateMonsterAction(DWORD dwTime);
	void EndMonsterAction();
	bool GetMonsterAction(){return m_bMonsterActioning;}
	void PlayMonsterAction();
private:
	DWORD   m_dwElapseMonsterActionTime;  //怪物的时间
	short   m_shCurrMonsterActionId;
	BOOL    m_bMonsterActioning;   // 怪物说话进行中
	short   m_nZoneIndex;          //控件索引

public:
	void ShowAttrChangeInfo(SValueChanged &valueChange);
	void SetFirstOnline(bool bValue){m_bFirstOnline = bValue;}
	bool IsFirstOnline(){return m_bFirstOnline;}
private:
	bool m_bFirstOnline;  //用于屏蔽第一次上线属性改变消息
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
	bool m_bCarrier;            // 是否在大载体上
	int  m_nCarrierID;          // 绑定在大载体的第几个位置
	int  m_nCarrierDriver;		// 大载体玩家ID
	bool m_bIsOthersPet;		// 是否乘坐的是其他玩家的坐骑
public:
	bool IsSameCountry(int nCountry);  //国家是否相同

public:
	uint8		GetTypeStatus() const { return m_nTypeStatus; }
	void		SetTypeStatus(uint8 val);
private:
	uint8		m_nTypeStatus;          // 当前状态

public:
	void ShowPetEffect();//显示宠物特效
	void SetPetEffect(const char* pszEffectName);
private:
	bool m_bShowPetEffect; //宠物刚召唤出来时，播放的特效
	std::string  m_strPetEffect;
	std::vector<GameObjectId>	m_passengers;	//乘的宠物后面还载着其他玩家
public:
	void TestPlayAnimByType(const char* pszAnim,bool bUpper);
public:
	void ProcessActionState();
	void ProcessHitBack(); //处理击退
	void ProcessBuoy();    //处理浮空
	void SetActionState(eActionState eValue,D3DXVECTOR3 vDir);
private:
	eActionState  m_eState;
	CRecordTimer  m_eStateTimer;  //状态计时器
	D3DXVECTOR3   m_HitBackDir;   //击退方向
private:
	float  m_fTargetZValue;    //目标Z轴
	bool   m_bStartZMoving;    //开始Z轴移动
	bool   m_bHigh;            //是否上升
	bool   m_bInElevator;      //是否在电梯上

public:
	void EquipTalismanById(unsigned short usItemID); //装备法宝
	void UnEquipTalisman(); //卸载法宝
	void CreateTaliman(unsigned short ustItemID); //创建法宝
	void DestroyTaliman();  //销毁法宝

	void UpdateTaliman(DWORD dwTime); //更新法宝
	void RenderTaliMan();  //渲染法宝
	bool IsShowTaliman(){return m_bShowTaliman;}
	void SetTalismanById(int nItemID){m_nTalismanId = nItemID;}
private:
	CPlayerAnim *m_pAnimTaliman;  //创建法宝
	bool         m_bShowTaliman;  //是否显示法宝
	int          m_nTalismanId;   //法宝ID
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
	DWORD m_dwNpcBeginTime;  //Npc显示问题
	bool  m_bBeginNpcShow;   //是否开始NPC显示问题
//机甲模式
public:
	int GetMountOperaType(){return m_nMountOperaType;}
	void SetMountOperaType(int nValue){m_nMountOperaType = nValue;}
	bool IsGoudaOperaMode(){return m_nMountOperaType == 1;}  //是否处于机甲模式
private:
	int  m_nMountOperaType;  //坐骑操作模式，0为正常骑马模式，1为机甲模式
public:
	void ProcessSceneSegment();
	void BeginPlaying(int nSceneID);
	void EndPlaying();

public: /// 主将相关
	void SetHeroID(const uint16 id = INVALID_HERO_ID) { mHeroID = id; }
	uint16 GetHeroID() const { return mHeroID; }

	/*
	 * Author:	2012-7-25 wangshuai
	 * Desc: 	使得Player在主将和正常状态下切换, 主将状态将更改Player的脸型、发型、肤色(Skin)
	 */
	void ShapeShift();

private:
	// 变身的主将ID
	uint16 mHeroID;
	//源来头发和脸型ID
	int source_faceid;
	int source_hairid;

public: /// 压镖相关
	bool IsYabiaoState() const { return mIsYabiaoState; }
	void SetYabiaoState(bool b) { mIsYabiaoState = b; }

	bool IsCanRide() const { return mIsCanRide; }
	void SetIsCanRide(bool b) { mIsCanRide = b; }

	void SetBiaocheScale(float s) { mBiaoCheScale = s; }

private:
	// 只有能骑的保护怪, 它的Master才可以变身镖车
	bool mIsCanRide;

	// 是否变身镖车
	bool mIsYabiaoState;

	// 镖车的缩放
	float mBiaoCheScale;

//private://记录进入太平幻境前得坐标
//	DWORD m_dwMapID;
//	D3DXVECTOR3  m_PrevPosition;	//进入太平幻境前得坐标
//	bool m_bIsInTPHJ;				//是否在太平幻境中
//public:
//	void SetMapID(const DWORD id=INVALID_MAP_ID){m_dwMapID = id;}
//	DWORD GetMapID(){return m_dwMapID;}
//	void SetPrePosition(D3DXVECTOR3 pos){m_PrevPosition = pos;}
//	D3DXVECTOR3 GetPrePosition(){return m_PrevPosition ;}
//	void SetInTPHJ(bool IsIn){m_bIsInTPHJ = IsIn;}
//	bool IsInTPHJ(){return m_bIsInTPHJ;}

private:
	int   m_nSceneID;            // 播放的场景ID
	int   m_nCurrSegmentIndex;   // 当前场景片段
	DWORD m_dwCurrSegBeginTime;  // 当前场景时间
private:
	bool m_bPlayDropAnim;	
public:
	bool IsCanOperateByKey(AN_Configure_ShortcutKey::ShortCutKey_Configure type);  //当处于坐骑状态时，一些操作需要禁止

public:
	uint32		GetBeLongID(){return m_BeLongID;}
	void		SetBeLongID(uint32 ID);
private:
	uint32		m_BeLongID;//归属ID
};
extern volatile swVec2f g_destPos;
extern bool g_PFOK;
extern BOOL g_FindPathThreadWillExit;
extern BOOL g_FindPathThreadExit;

extern int GetNormalAttackByProfession( int iProfession );

#endif