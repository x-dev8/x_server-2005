#ifndef _playermgr_h
#define _playermgr_h
#include "Dxsdk/d3dx9.h"
#include <list>
#include <queue>
#include <map>
#include <string>
#include <windows.h>
#include <Me3d/Bsp.h>
//#include "Mesocket.h"
//#include "MsgFromBuf.h"
#include "LagCounter.h"
#include "QuestManager.h"
#include "FuncPerformanceLog.h"
#include "MapContainer.h"
#include "NpcCoord.h"
#include "MessageDefine.h"
#include "StageDataLoader.h"
#include "MapArea.h"

class MexAnimCtrl;
struct SAttackInfo;
class CRecorder;
class CPlayer;
#define LOAD_PLAYER_NPC_MAX_TIME	5		//毫秒，每帧加载其他玩家和NPC、怪物等的最大时间限制，超过则push进数组下帧加载
#define PLAYER_RENDER_MAX			300		//同屏渲染人数最大值，即不限人数
#define PLAYER_RENDER_QUEUE_MAX		1000	//排序数组最大容量
#define PLAYER_RENDER_DIST_MAX	TEAM_EXP_DIS          // 人物渲染最远距离
#define PLAYER_RENDER_DIST_MIN	20
#define PLAYER_LOCK_DIST_MAX TEAM_EXP_DIS
#define PLAYER_SPECIAL_IDLE_ID      127     // 特殊待机动作作为表情广播时用的ID

struct PlayerRenderLimitData	// 同屏显示人物数据 
{
	BOOL		bRendered;
	CPlayer*	pPlayer;
};
struct NetStatistics	// 网络统计，放在PlayerMgr里比较奇怪
{
	int	iOutAvgPerSecond;
	int iOutMaxPerSecond;
	int iInAvgPerSecond;
	int iInMaxPerSecond;
};
// 记录主角普通攻击状态
enum ECommonAttackStatus
{
    CAS_NOT_ATTACK,
    CAS_NEED_AUTO_ATTACK,           // 需要对当前目标自动攻击
    CAS_ATTACK_AGAIN_WHEN_FAILED,   // 已发第一次攻击包，如果失败需要再发
    CAS_ATTACKING,                  // 已成功攻击锁定怪
};

struct SeeAttackParam
{
    CPlayer* pAttacker;
    CPlayer* pDst;
    short stAttackerX; 
    short stAttackerY;
    int nTagHp; 
    int iTagNum;
    int iSrcHpNum;
	int nTagMp; 
	int iTagMpNum;
	int iSrcMpNum;
    int iBalanceType;
    short stTagBackAttackNum;
	int  nShieldHp;
};

struct SeeDamageParam
{
    GameObjectId nDst;
    GameObjectId nSrc;
    int iTagNum;
    int iSrcNum;
    int iBalanceType;
    int iTagHp;
    int iSrcHp;
    int iTagMp;
    int iSrcMp;
	int iTagMpNum;
	int iSrcMpNum;
    short stTagBackAttackNum;
	short stStatusID;   // 状态id
	short stLevel;      // 状态等级
};

class CPlayerMgr 
{
public:
	//改成基于ID的player结构
	//基于ID查找具体的结构
	//自己的ID
	//
	struct  ControlData
	{
		BOOL       bLeftDownFlag;          //左键按下的标志
		BOOL        bRightDownFlag;         //右键按下的标志
		//
		BOOL        bAutoProcFlag;          //自动处理的标志..在mouse按住2秒后改标志有效
		DWORD       dwAutoProcTime;         //自动处理的时间
		//
		DWORD       dwAutoPressTime;        //间隔发鼠标消息的时间
		//当前所定的玩家
		GameObjectId			LockNpcID;				//取得锁定的npc的编号
		//CPlayer*    pLockPlayer;
		int			iUseSkill;				//当前使用的技能
		int			iUseSkillLevel;			//技能的等级
		//
		ControlData()
		{
			LockNpcID = -1;
			bLeftDownFlag = FALSE;
			bRightDownFlag = FALSE;
			bAutoProcFlag = FALSE;
			dwAutoProcTime = 0;
			dwAutoPressTime = 0;
			iUseSkill = InvalidLogicNumber;
			iUseSkillLevel = 0;
		}
		void ClearAutoFlag(void) {bAutoProcFlag = FALSE, dwAutoProcTime=HQ_TimeGetTime();};
	}m_controldata;

	struct SQuestInfo
	{
		int nQuestId;	// 任务编号
		char chState;	// 相关任务状态
	};
	struct SNpcQuestInfo
	{
		std::string strName;
		std::vector<void*> vectorRelateQuestInfo;	// 相关任务信息
		void		InitialRelateQuestInfo();
		SNpcQuestInfo()
		{

		}
	};
	struct SShowPlayerHP
	{
		//当前的攻击目标
		GameObjectId nIDAttackTarget;
		//鼠标指向的
		GameObjectId nIDMouseOver;		
		GameObjectId nIDLockNpc;//当前锁定的npc
	}m_showhp;

	enum
	{
		eNpcTips_None,
		eNpcTips_HaveQuest,				// 有任务给你
		eNpcTips_HaveQuestNotNow,		// 有任务给你,但现在你还不能接
		eNpcTips_QuestDone,				// 任务完成
		eNpcTips_QuestNotDone,			// 任务未完成
        eNpcTips_CampBattleS,           //旗帜随军占领
        eNpcTips_CampBattleT,           //旗帜唐军占领
        eNpcTips_CampBattleZL,          //旗帜无人能占领
	};

	enum
	{
		eReliveOriginNon,//只在 原地复活
		eReliveOriginAllHpMp,//原地复活HPMP全满
	};

    // 所有游戏人物渲染开关，可采集物品默认都显示
    enum EPlayerRenderFlag
    {
        EPRF_ME     = 1,                                    // 只渲染自己
        EPRF_TEAM   = 1<<1,                                 // 渲染队友
        EPRF_FRIEND = 1<<2,                                 // 渲染好友
        EPRF_NPC    = 1<<3,                                 // 渲染NPC
        EPRF_MONSTER= 1<<4,                                 // 渲染怪物
        EPRF_OTHERS = 1<<5,                                 // 渲染其他玩家
		EPRF_TARGET = 1<<6,									// 渲染选中目标

		EPRF_AMITY = 1<<7,									// 友好的玩家 （目前只针对本国玩家）
		EPRF_ANTAGONIZE = 1<<8,								// 敌对的玩家 （目前只针对非本国的玩家）
        EPRF_ALL    = EPRF_ME | EPRF_TEAM | EPRF_FRIEND | EPRF_NPC | EPRF_MONSTER | EPRF_TARGET | EPRF_OTHERS | EPRF_AMITY | EPRF_ANTAGONIZE,  // 全部渲染
    };

	enum
	{
		eRemoveAny			= 1<<0,
		eRemoveExceptMe		= 1<<1,
	};

	enum
	{
		eExceptMe		=	1<<1,		// 排除我
		eExceptFriend	=	1<<2,		// 排除朋友
		eExceptItem		=	1<<3,		// 排除道具
	};

	////////////////////////////////////////////////////////////////
	//成员变量
public:
	DWORD		m_dwGamePing;			//游戏中的Ping

	//玩家自己
	CPlayer*			m_pMe;
	__int64             m_SessionKey;
	std::string			m_strSessionKey;
	DWORD               m_dwAccountID;

	DWORD m_dwMapId;
	int m_nY;
	int m_nX;
	int m_PlayerID;
	short m_sttype;
	int m_itemid;
	int m_count;
	int m_activeid;

	bool m_bCombineRenderPlayer;

	// 当前鼠标指向的Player服务器ID
	GameObjectId				m_shMouseTargetPlayerSeverID;
	// 缓冲的技能目标的ID
	GameObjectId			m_SkillBufTargetID;

	// 鼠标右键按下时所获得的PlayerID
	int					m_nMouseRDownTargetPlayerServerID;

	// 当前鼠标指向的player
	GameObjectId				m_nPickId;

	// 当前活动玩家
	std::map< GameObjectId, CPlayer* > m_mapPlayers;
	// 当前正在死亡的玩家
	// 当see attack得知该玩家会被杀死那一霎那，
	// 加入到m_vectorDieingPlayers中
	std::vector< CPlayer* > m_vectorDeathPlayer;
	
	//  [1/7/2011 zhangjiayi]
	// 用于存放飞逻辑性的模型(例如baseproperty中)
	std::vector< CPlayer* > m_vectorNoLogicPlayer;

	// 玩家从近致远队列，包括死亡人物，按规则来判断渲染优先顺序
	// 20米内，优先显示队友，NPC，好友，然后怪物，再其他玩家
	PlayerRenderLimitData m_PlayerDistQueue[PLAYER_RENDER_QUEUE_MAX];
	int					m_nPlayerQueueCount;

	BOOL				m_bLoginSucc;

	CLagCounter			m_lag;

	bool				m_bNeedBeginDilog;	//标志Npc对话框是否显示着

	BOOL				m_bShadowColor;		//角色动态阴影色开关
	
	std::vector<SNpcQuestInfo> m_vectorNpcInfo;
	std::vector<INT>	  m_vtAlphaPlayer;

	BOOL				m_bPlayMapEffect;//Only Player
	std::string			m_szPlayMapEffect;

    short sPlayerSlot; /// 玩家选择进入游戏的第几个角色的索引号

	std::vector< CPlayer* > m_vecDynamicCollison;	// 有动态碰撞效果的NPC列表，在每帧更新所有人物位置后获取
	BspTree				m_DynamicCollisionBsp;
	BspTree             m_DynamicFloorBsp;

protected:
	// 渲染数据统计
	int					nRenderPlayerCount;
	int					nRenderVertexCount;
	int					nRenderFaceCount;

	std::vector<MsgNPCEnterMySight> PendingSawNPC;
	std::vector<MsgPlayerEnterMySight> PendingSawPlayer;
	DWORD				m_nSawPlayerNPCCostTime;	// 加载其他玩家和NPC，怪物的时间损耗，超过LOAD_PLAYER_NPC_MAX_TIME则加入数组下帧继续加载

    unsigned int		m_nPlayerRenderFlag;
	unsigned int		m_nLastPlayerRenderFlag;
    BOOL				m_bTurnRoleToCamera;

    BOOL				m_bUseSkillBuf;
	D3DXVECTOR3			m_vFrom;
	D3DXVECTOR3			m_vDir;

    DWORD				m_dwLastUpdateNpcActionTime;  // 上次更新NPC休闲动作时间，每1秒更新一次

    BOOL m_bCanReceivePlayerMsg;    // 加载地图时，设置不接收玩家进入/离开视野，和移动消息

    DWORD m_dwLastReqScriptTime; // 请求脚本消息增加1秒CD，用于:MsgReqScript(请求脚本)，MsgScriptAckShowQuestDlg(返回任务)，MsgAbandonTask（放弃任务）

	std::map<std::string, GameObjectId> m_mapVipPlayer;

	bool m_bNeedUpdateRoleUI;

	bool                m_bClickTheTerrain;
	bool                m_bRelivedByPlayer;
	FLOAT				m_fFarRole;
	int					m_nPlayerRenderLimit;	// 同屏人数限制
	///////////////////////////////////////////////////////////////////////
	//成员函数
public:
	void				OnSeeIntonate(int iSkill, int iSkillLevel, GameObjectId ScNPcID, GameObjectId TagNpcID, int iPercent, unsigned short usType );
	void				OnSeeHoldSkill( int iSkill,int iSkillLevel,GameObjectId iSrcChar,int iPercent );
	//
	//void				OnSeeExpression(short stNpcID, short stActionID);					// 删除旧表情动作函数
	//
	void				OnSeeDamage(DWORD dwState, const SeeDamageParam& kSeeDamageParam );
	//
	void				OnSeeAttack( SAttackInfo* pAttackInfo, DWORD dwState, const SeeAttackParam& kSeeAttackParam );
	//
	void				AutoCS( int iPlayerID );

	void				SawOneItem( Msg *pMsg );

	void				SetAttackTarget( GameObjectId nIDWho );
	void				SetMouseOver( GameObjectId nIDWho );

	CPlayerMgr();
	BOOL				ProcessCommand( const char* pszCommand );

	bool				GetIsNeedNpcDailogShow()		{ return m_bNeedBeginDilog; }
	void				SetNeedBeginDilog(bool val) { m_bNeedBeginDilog = val; }
	void                SetLockNpc(GameObjectId iIDLockNpc);
	void				DisHitch();		//下交通工具
	void				DisDrome();		//下马	
	void				ChangeDrome( short nId );
	void				LockMe();
	CPlayer*			FindNearItemNpc(void);
	BOOL				CheckViewPlayerBBox( Vector &vDir ,float fMaxDis);

	void                SetReLivedByPlayer(bool bIs){m_bRelivedByPlayer = bIs;}
    bool                IsRelivedByPlayer() { return m_bRelivedByPlayer; }
	FLOAT				GetFarRole()		{ return m_fFarRole; }
	VOID				SetFarRole(FLOAT fRole)		{ if( fRole > 0 ) m_fFarRole = fRole; }	// 取消渲染距离设置
	
	int					GetPlayerRenderLimit() { return m_nPlayerRenderLimit; }
	void				SetPlayerRenderLimit(int num) { m_nPlayerRenderLimit = num; }

	VOID				SetPickItemID( GameObjectId nId ) { m_nPickId = nId; }
	GameObjectId		GetPickItemID( ) { return m_nPickId; }

	BOOL				Init();
	void				Release();
	void				Update( DWORD time, Frustum &frustum );
	void				TabSelectPlayer();
    void                LoadGlobalData();

    void                AutoSelectMonster();
	void                UpdateMonsterType();

	BOOL				RandomAddPlayer();
	void				Render( LPDIRECT3DDEVICE9 pDevice, int nType = 0 );
	void				RenderAlpha( LPDIRECT3DDEVICE9 pDevice );
	void				RenderShadow( LPDIRECT3DDEVICE9 pDevice );

	void				RenderPlayerInfo( LPDIRECT3DDEVICE9 pDevice );
	void				RenderPlayerChatInfo();
	void				RenderMiniMap( void );
	void				RenderPlayerTeamFlag();


	void				CheckHPInfo( GameObjectId stIDWho );

	BOOL				CreateMe( GameObjectId stID );
	CPlayer*			GetMe(){ return m_pMe;}
	GameObjectId				GetMyID();
	CPlayer*			FindItemNpc(void);
	CPlayer*			FindNearItemNpc(int x, int y, int range);
	BOOL				IsHaveItemHere(int x, int y);

	// 查找相同ID
	int					FindSameID( GameObjectId stID );

	// 根据服务器的Id查找Player
	CPlayer*			FindByID( GameObjectId	stID );
	// 根据数据库中的角色ID查找Player
	CPlayer*			FindPlayerByCharacterID( DWORD dwCharacterID );

	// 根据客户端的Id查找Player
	CPlayer*			FindByClientID( int nID );
	// 根据服务端的Id在死亡队列中查找Player
	CPlayer*			FindByServerIDInDeath( GameObjectId shID );
	// 根据客户端的Id在死亡队列中查找Player
	CPlayer*			FindByClientIDInDeath( GameObjectId nID );
	
	// 加入Player
	void					AddNoLogicPlayer( CPlayer* pPlayer );
	void					ClearNoLogicPlayer( CPlayer* pPlayer );
	CPlayer*			AddPlayer( GameObjectId stID,int iCharType, bool bIsMe = false );
	BOOL				PlayerExit( GameObjectId stId );
	BOOL				RemovePlayerFromActiveList( GameObjectId stId, DWORD dwFlag = 0);
	BOOL				RemovePlayerFromActiveList( CPlayer* pPlayer, DWORD dwFlag = 0 );
	BOOL				AddPlayerToKeepList( CPlayer* pPlayer, BOOL bFast = FALSE );    //bFast = TRUE, 需要尽快消失
	BOOL				DeleteDeathPlayer( CPlayer* pPlayer );
	void				DeletePlayersExceptMe();
	void				ReqRelive( bool bBornCity,bool bBySkill = false,short stOriginRelieveType = -1,BYTE byAddtion=0);
	GameObjectId				GetMouseTargetPlayerSeverID(){ return m_shMouseTargetPlayerSeverID; }
	GameObjectId     			GetLockPlayerID(){return m_controldata.LockNpcID;}
	void    			SetLockPlayerID(GameObjectId npc_id);
	void				RequestGetOnOtherPet( CPlayer* pPlayer ); //请求骑上别人的宠物
	void				SetCurUseSkill(int skill, int level = 0){m_controldata.iUseSkill = skill, m_controldata.iUseSkillLevel = level;};
	int 				GetCurUseSkill(void){return m_controldata.iUseSkill;}
	int 				GetCurUseSkillLevel(void){return m_controldata.iUseSkillLevel;}

	// 左键响应 -->发出移动指令
	void				TurnRoleTo( CPlayer* pTargetPlayer );
	bool				MoveRoleToNPC(const NpcCoordInfo* pInfo);
	bool				MoveRoleTo( float x, float y, bool bNeedShowTargetPoint = true ,bool bSync = false, bool bHideTargetPoint = true,bool bUseZ = false);

	bool				ProcessShift(  float x, float y );
	void				HideTargetPointEffect();
	void				MoveRoleToPlayer( CPlayer* pTargetPlayer, BOOL bClose = TRUE, float fCorrect = 0.0f, BOOL bPick = FALSE ,BOOL bInRuning = FALSE, BOOL bCalibrate = FALSE );
	// 空格键响应 -->发出蓄力指令
	void				UseSpecialSkill();
	void				ReadytoUseSpecialSkill();
	// 右键响应 -->发出攻击指令
	void				RoleAttackToDead(int tag_player_id, int x, int y, int skill_id, int skill_level = 1);
	void				RoleAttack(int tag_player_id, int x, int y, int skill_id, int skill_level = 1,
						bool bAttackToDead = false,bool bHoldAttack = false );

	//主角使用技能
	void				RoleUseSkill( int nTag_Player_ID, int x, int y, int nSkill_ID, int nSkill_Level );
	//
	void				UseRecordSkillAttackToDead(void);
	void				UseRecordSkill(void);
	//
	void	            RoleIdle(short x, short y);//待机
	void				RoleChangeDir(short x, short y);//转身
	void				ClearRoleGetRangeItem(void);	//给npc控制的npc下达指令。取得周围的道具
	void				RoleDropItem(short x, short y);	//给npc控制的npc下达指令。丢弃鼠标上的道具
	void				RoleDoAction(int ActionID);		//给npc控制的npc下达指令。作某个表情动作

	CPlayer*			FindByPt( int x, int y );
	CPlayer*			FindByName( const char*szName );

	void				Destroy();

	void				RenderPlayer( LPDIRECT3DDEVICE9 pDevice,int iPlayerID );

	//处理消息
	bool				ProcessMsg( Msg* pMsg );

	const BOOL			GetLoginSuccess() const	{ return m_bLoginSucc; }

	void				SetLoginSuccess( const BOOL b )	{ m_bLoginSucc = b; }
	//是否应该绘制血条
	bool				WillHPShow( GameObjectId nIDWho );
	//取得系统的PING.
	DWORD				GetGamePing(void){return m_dwGamePing;}
	//
	int					GenerateNetStreamFluxLen(int val);

	//
	SNpcQuestInfo*		FindNpcInfo( GameObjectId nNpcId );
	SNpcQuestInfo*		FindNpcInfo( const char* pName );
	BOOL				IsNpcHasQuest( GameObjectId nNpcId );
	bool				IsInNpcList( GameObjectId nNpcId);
	void				RefreshAllNpcQuest();
	void				GetNpcQuests( GameObjectId nNpcId, 
							std::vector<SQuest*>* pvectorQuest,
							std::vector<void*>* pvectorState );

	void				GetNpcQuests(const NpcCoordInfo* pCoordInfo, 
							std::vector<SQuest*>* pvectorQuest,
							std::vector<void*>* pvectorState );

	int					UpdateNpcTipsType( GameObjectId stNpcId );
	int					UpdateNpcTipsType(const NpcCoordInfo* pCoordInfo );

	//--返回人物选择　清空ｎｐｃ列表
	void				CleaNpcInfos()	{ m_vectorNpcInfo.clear(); }

	// 发送宠物命令
	void	SendPetCommand( int nCommand );


	void	DrawNetStreamFlux(LPDIRECT3DDEVICE9 pDevice, int x, int y, BOOL bDraw = TRUE, NetStatistics* pRetStatistics = NULL);

	//
	BOOL	OnSkill( BOOL bMouseSelectTarget = FALSE, BOOL bUseSkillBuf = FALSE );
	//
	int		RenderMouseBag(void);
	//
	void	RenderPlayerTip();
	void	RenderInfo(LPDIRECT3DDEVICE9 pDevice, int x, int y);
	void	OnVerifyPos(MsgVerifyPos* pMsgVerifyPos);
	void	OnSyncPos(MsgSyncPos* pMsgSyncPos);
	void	OnSeeAction( GameObjectId stPlayerId, short stActionId );

	//和控制相关的函数
	BOOL    MouseShortCutClear(void);//清空快捷方式
	BOOL	MouseControlFunction( float x, float y, int type, int xMouse, int yMouse, bool bPicked ); //鼠标控制的入口
	BOOL	KeyboardControlFunction(int type, BOOL bDxInput=FALSE);
	BOOL	KeyboardKeyUpControlFunction(int type, BOOL bDxInput=FALSE);
	BOOL	BreakInputMessage( DWORD dwType );
 	BOOL	ControlLButDownProc( float x, float y, bool bPicked );
	BOOL	ControlLButUpProc( float x, float y, bool bPicked );

	void    UseSilllToSelectPoint();

	void	OnClickNon_object( float x, float y );
	void	BeginDialog(float xDst,float yDst);
	BOOL    ControlRButDownProc(int x, int y);  //右键处理
	BOOL    ControlRButUpProc(int x, int y);  

	BOOL    ControlHotKeyProc(int HotKeyIdnex); //对热键的处理
	BOOL	AutoControlClear(void);				//清除自动控制的一些标志
	BOOL    AutoLockAttacker(int AttackerID);				//	自动锁定攻击自己的npc
	//
	BOOL	AutoSkillProc(void);				//制动使用技能的处理
	//发Ping消息给服务器
	BOOL	PingServer(void);
	// 检查是否看玩家的个人商店
	BOOL	CheckPrivateShop( int x, int y );

	void	SwitchScabbard();

	DWORD	GetQuestRankColor( SQuest* pQuest);

	// 发送角色拔出武器的消息
	void	SendDrawWeapon();

	// 发送角色收起武器的消息
	void	SendDrawInWeapon();

	void	ProcessPendingSawPlayerNPC();					// 每帧在处理Net message前调用，处理上帧未加载完的人物
	void	PreloadMapMonsterAndNpc(const char* szMapName);	// 预加载地图的怪物模型

	void    SetPlayerRenderFlag(unsigned int _flag){m_nPlayerRenderFlag = _flag;}
    void	AddPlayerRenderFlag(unsigned int flag) { m_nPlayerRenderFlag |= flag; }
    void	RemovePlayerRenderFlag(unsigned int flag) { m_nPlayerRenderFlag &= ~flag; }
    BOOL	IsPlayerTypeRender(unsigned int flag) { return m_nPlayerRenderFlag & flag; }
    void	SetPlayerRenderPriority(unsigned short pri);
    void	TogglePlayerRenderPriority();
    unsigned short GetPlayerRenderFlag() { return m_nPlayerRenderFlag; }
    BOOL	IsPlayerCanRender(CPlayer* pPlayer, BOOL bDist = FALSE);   // bDist = TRUE，是否在PLAYER_RENDER_DIST_MIN范围内判断
	BOOL    IsPlayerCanRenderEX(CPlayer* pPlayer, BOOL bDist = FALSE);
	/*
	 * 2012.6.25 wangshuai
	 * 添加2个接口, 用于模拟挂起和恢复的过程, 分别是Suspend/Resume
	 */
	void SuspendCurrentRenderFlag();
	void ResumeLastRenderFlag();

    BOOL	IsTurnRoleToCamera() { return m_bTurnRoleToCamera; }
    void	SetTurnRoleToCamera(BOOL bTurn) { m_bTurnRoleToCamera = bTurn; }

    void	SetUseSkillBuf(BOOL bUse) { m_bUseSkillBuf = bUse; }
    BOOL	IsUseSkillBuf() { return m_bUseSkillBuf; }
    void	SetSkillBufPlayer(CPlayer* pTarget);
    GameObjectId GetSkillBufPlayerID() { return m_SkillBufTargetID; }
    void	ClearSkillBuf();

    BOOL	CanReceivePlayerMsg() { return m_bCanReceivePlayerMsg; }
    void	SetCanReceivePlayerMsg(BOOL bCan) {m_bCanReceivePlayerMsg = bCan;}

    BOOL	CanReqScript();

    BOOL	IsPlayerValid(const CPlayer *pPlayer);

	bool	PushVipPlayer( const char* szName, GameObjectId stID );
	bool	IsVipPlayer( const char* szName );

	void	ResetUpdateRoleUI() { m_bNeedUpdateRoleUI = false; }
	bool	IsNeedUpdateRoleUI() { return m_bNeedUpdateRoleUI; }

	bool	DoJumpAction();
	bool	DoUseSkillOperation( GameObjectId TargetID, int nSkillID, int nSkillLevel );

    /** 取消玩家行为
    */
    bool    cancelBehavior();

	void	ClearPlayerQueue()
	{ 		// 清空渲染队列
		m_nPlayerQueueCount = 0;
		memset(m_PlayerDistQueue, 0, PLAYER_RENDER_QUEUE_MAX*sizeof(PlayerRenderLimitData));
	}

    int		GetRenderPlayerCount(){ return nRenderPlayerCount; };
	int		GetRenderPlayerVertexCount() {return nRenderVertexCount;};
	int		GetRenderPlayerFaceCount() {return nRenderFaceCount;};

	bool CheckCanTabCampMonster(CPlayer* pPlayer);
    bool   CanTab(CPlayer* pPlayer);
	void RetriveRelationQuestToNpc( GameObjectId npcId, int &nQuestCount, int * questStates, void * pstList , int nWordCount = 0);
    std::string ParseText(const std::string& str);

	// 处理NPC对话中表情头像字段
	short ProcessExpHead(const char* szText, std::string& strRet);

protected:
		// 动作更新频率时间(毫秒)
	static DWORD ms_dwUpdateAnimTimeStep;
public:
	void SetUpdateAnimTimeStep( DWORD dwTime ){ ms_dwUpdateAnimTimeStep = dwTime; }
	DWORD GetUpdateAnimTimeStep() { return ms_dwUpdateAnimTimeStep; }

protected:	
	//看见一个人
	CPlayer* SawOneNPC( Msg *pMsg );
	CPlayer* SawOnePlayer( Msg *pMsg );

	void DestroyPlayer( CPlayer *pPlayer );

	bool CreateDynamicCollision(CPlayer* pPlayer);

	// 发送角色的跳跃信息
	void SendJumpMsg();

	// 内存不足情况下，玩家不在视野内，距离主角超过30米，且离最近一次渲染超过5秒，则释放动画数据，缓解内存压力
	void CheckDestroyAnimLowMemory(CPlayer* pPlayer);
	void ResetDestroyAnimNum(){ m_iDestroyCharLimitPerFrame = 3; }	// 每帧在CheckDestroyAnimLowMemory前调用
	short m_iDestroyCharLimitPerFrame;

	void	AttackPlayer( CPlayer* pPlayer );

	//消息处理
	/////////////////////////////////////////////////////////////////
public:
	//用 商城积分购买商城道
	void OnMsgRMBConsumeScoreChange(Msg* pMsg); 
	void OnMsgRMBGoldChange( Msg* pMsg );
	void OnAckGlodCovSilver( Msg* pMsg );
	void OnRetResetTime( Msg* pMsg );
	//接受到更改Idle子状态的消息
	void OnMsgChangeSubAction(Msg* pMsg);
	// 接收到确认移动指令
	void OnMsgAckMove( Msg* pMsg );

	// 接收到有NPC进入我的视野(单步移动状态的)
	void OnMsgNPCEnterMySightMovingAStep( Msg* pMsg );

	// 接收到有Player进入我的视野
	void OnMsgPlayerEnterMySight( Msg* pMsg, BOOL bCheckLoadingCost = TRUE );
	// 接收到有Player进入我的视野(单步移动状态的)
	void OnMsgPlayerEnterMySightMovingAStep( Msg* pMsg );

    //接收到有Player进入视野的包
    void OnMsgPlayerEnterMySightPack(Msg* pMsg);
	// 接收到有NPC进入我的视野
	void OnMsgNPCEnterMySight( Msg* pMsg, BOOL bCheckLoadingCost = TRUE );    

	// 接收到改变坐骑的消息
	void OnMsgChangeDrome( Msg* pMsg );

	// 接收到物品进入我的视野
	void OnMsgItemEnterMySight( Msg* pMsg );
	// 接收到角色离开我的视野(包括物品)
	void OnMsgExitMySight( Msg* pMsg );
	// 接收到某人移动到哪里的消息
	void OnMsgMoveToTarget( Msg* pMsg );
	// 接收到角色的显示名称
	void OnMsgAckDisplayName( Msg* pMsg );
	// 通知帮会成员属性变更
	void OnMsgGuildMemberValueChange( Msg* pMsg );
	// 接收到玩家工会信息
	void OnMsgCharGuildInfo( Msg* pMsg );
	// 接收到角色查询数据
	void OnMsgAckCharInfo( Msg* pMsg );
	// 接收到退出指令( 什么退出，是什么退出？)
	void OnMsgExit( Msg* pMsg );
	// 接收到确认攻击消息
	void OnMsgAckAttack( Msg* pMsg );
	// 接收到所有游戏属性(?!)
	void OnMsgAckAllGameProperty( Msg* pMsg );
	// 接收到切换地图消息
	void OnMsgChangeMap( Msg* pMsg );
	// 接收到聊天消息               
	void OnMsgChat( Msg* pMsg );
	// 拉收到事件范围(构造事件范围，用于客户端表现而矣)
	void OnMsgEventRange( Msg* pMsg );
	// 接收到测试网络延迟的消息
	void OnMsgGetLag( Msg* pMsg );
	// 接收到某人的升级消息     
	void OnMsgCharLevelUp( Msg* pMsg );
	// 接收到某人完成任务
	void OnMsgDoneQuest( Msg* pMsg );
	// 接收到某人的技能升级消息     
	void OnMsgCharSkillLevelUp( Msg* pMsg ); 
	//看到角色身上出现法术效果
	void OnMsgCharShowEff( Msg* pMsg );    

	// 接收到刷新角色信息
	void OnMsgRefreshChar( Msg* pMsg );
	// 接收到获得钱的消息
	//void OnMsgGetMoney( Msg* pMsg );
	// 接收到改变公会消息
	void OnMsgChangeGuild( Msg* pMsg );

	// 接收玩家的跳跃信息
	void OnMsgRecevingJump( Msg* pMsg );

	// 接收到玩家拔出武器的信息
	void OnMsgRecevingDrawWeapon( Msg* pMsg );

	// 接收到玩家收起武器的信息
	void OnMsgRecevingDrawInWeapon( Msg* pMsg );

	// 接受到技能提示消息
	void OnMsgUseSkillHintMessage( Msg* pMsg );

	// 接收到看见某的Player死亡的消息
	void OnMsgSawPlayerDead( Msg* pMsg );

	// 接收到单步移动消息
	void OnMsgMoveAStep( Msg* pMsg );

	// 接受到非玩家角色贴近其目标
	void OnMsgUnPlayerClosingToLockTarget( Msg* pMsg );

	// 接收到非玩家移动的消息
	void OnMsgUnPlayerMovingToPos( Msg* pMsg );

	// 接收到非玩家矫正坐标的消息
	void OnMsgUnPlayerVerifyPos( Msg* pMsg );

	// 接收到玩家矫正坐标的信息
	void OnMsgPlayerVerifyPos( Msg* pMsg );

	//// 接收到持续移动的消息
	//void OnMsgPlayerMoving( Msg* pMsg );

	// 接收到移动中玩家位置改变的消息
	void OnMsgPlayerMovingPos( Msg* pMsg );

	// 接收到移动中玩家位置和朝向改变的消息
	void OnMsgPlayerMovingPosAndDir( Msg* pMsg );

	// 接收到移动中玩家位置和朝向改变的消息，自动寻路
	void OnMsgPlayerMovingPosAndDir_TargetDir( Msg* pMsg );

	// 接收到原地不动玩家的位置消息
	void OnMsgPlayerPos( Msg* pMsg );

	// 接收到原地不动玩家的朝向消息
	void OnMsgPlayerDir( Msg* pMsg );

	// 接收到原地不动玩家的位置和朝向消息
	void OnMsgPlayerPosAndDir( Msg* pMsg );

	// 接收到相关移动的消息包
	void OnMsgPosChange( Msg* pMsg );

	// 接收到搭乘移动要移动的目标点
	void OnMsgHitchMoveTargetPos( Msg* pMsg );

	// 接收到玩家能否控制的移动的消息
	void OnMsgCanControlMoving( Msg* pMsg );

	// 接收到服务器传来的是否可以移动的状态
	void OnMsgPermitMove( Msg* pMsg );
	// 接收到位置确认消息
	void OnMsgVerifyPos( Msg* pMsg );    
	//坐标同步
	void OnMsgSyncPos( Msg* pMsg );
	// 接收到扔掉物品的消息
	void OnMsgRemoveSomething(Msg* pMsg);
	// 接收到使用物品的消息
	void OnMsgRemoveItem(Msg* pMsg);
	// 接收到请求查看物品的消息
	void OnMsgGetShop(Msg* pMsg);
	// 接收到买东东的消息
	void OnAckMsgBuyOrSellGoods(Msg* pMsg);
	//// 接收到属性更改消息
	void OnMsgAttrChanged(Msg* pMsg);
	// 接收到属性升级消息
	void OnMsgAttrLevelUp(Msg* pMsg);
	// 接受到放置符石消息
	void OnMsgPlaceStone( Msg* pMsg );
	// 接受到移除符石消息
	void OnMsgRemoveStone( Msg* pMsg );
	// 接受到放置招式片段消息
	void OnMsgPlaceSubSkill( Msg* pMsg );
	// 接受到移除招式片段消息
	void OnMsgRemoveSubSkill( Msg* pMsg );
	// 接受到制造物品的消息
	void OnMsgProduceItem( Msg* pMsg );
	//
	//看到一个效果进入视野
	void OnMsgEffectEnterMySight( Msg *pMsg );
	void OnMsgBuildingEnterMySight( Msg *pMsg );

	//收到下发的持续性魔法效果的伤害
	void OnMsgDamageOfEffect( Msg *pMsg );
	//	看到有人受到了伤害
	void OnMsgSeeDamage( Msg *pMsg );
	//收到下发的看到攻击的消息
	void OnMsgSeeAttack( Msg *pMsg );
	//收到下发的看到无效的施放技能的消息
	void OnMsgSeeCastInefficacySkill( Msg *pMsg );
	//服务器战斗回答
	void OnMsgAckAttack3( Msg *pMsg );
	//看到有人在呤唱
	void OnMsgSeeIntonate(Msg *pMsg);
	//开始吟唱
	void OnMsgIntonateStart(Msg *pMsg);
	//吟唱结束
    void OnMsgIntonateEnd(Msg *pMsg);
	//吟唱中断
	void OnMsgIntonateInterrupt(Msg* pMsg=NULL);

	void OnMsgHoldSkillEnd(Msg*pMsg);
	void OnMsgSkillCanceled( Msg* pMsg );
	void OnMsgSkillStatus(Msg*pMsg);
	//	看到有人在作表情动作
	void OnMsgSeeExpression(Msg*pMsg);
	//接收到装备更换消息
	void OnMsgEquipChanged2( Msg* pMsg );
	//返回掉落物品
	void OnMsgAckDropItem2( Msg*pMsg );
	//
	void OnMsgEquip( Msg* pMsg );
	//--更新角色背包的数据
	void OnMsgUpdateBag( Msg*pMsg );
	//更新快捷
	void OnMsgUpdateShortCutBag( Msg*pMsg );
	//更新player身上装备的道具
	void OnMsgUpdateVisualEquip(Msg* pMsg);
	//更新player身上装备的数据
	void OnMsgUpdateEquipData( Msg* pMsg );
	//得到物品
	void OnMsgGetItem2( Msg*pMsg );
	// 钱变化了
	void OnMsgMoneyChange( Msg* pMsg );
	//某人地图载入完成
	void OnMsgMapLoaded( Msg*pMsg );
	//返回某人的血条
	void OnMsgAckHPInfo( Msg *pMsg );
	//------- 添加任务    (   at 2004-2-19)
	void OnMsgAddMissionIntro( Msg* pMsg );
	//------- 除非任务    (   at 2004-2-19)
	void OnMsgDelMissionIntro( Msg* pMsg );
	// 看到某人做动作
	void OnMsgSeeAction( Msg* pMsg );
	// show image
	void OnMsgScriptShow( Msg* pMsg );

	//接收到角色信息
	void OnMsgAckGetPlayerInfo(Msg * pMsg);

	//有人下线了
	void OnMsgAckFriendLeave(Msg * pMsg);
	//收到服务器发送回来的Ping消息
	void OnMsgPing(Msg * pMsg);
	//站立 状态切换
	void	OnMsgSitStatusChange(Msg * pMsg);
	//战斗状态切换
	void	OnMsgFightStatusChange(Msg * pMsg);
	//接收到关于队伍建立清况的消息
	void	OnMsgCreateTeam(Msg* pMsg);
	//接收到有人加入队伍的消息
	void	OnMsgJoinTeam(Msg* pMsg);
	//队员下线了
	void	OnMsgTeamOutLine(Msg* pMsg);
	//接收到队伍的，信息
	void	OnMsgTeamInfo(Msg* pMsg);
	//有人加入队伍
	void	OnMsgAddTeamMember(Msg* pMsg);
	//有人退出了队伍
	void	OnMsgDeleteAMember(Msg* pMsg);
	//自己离开了队伍
	void	OnMsgExitTeam(Msg* pMsg);//
	//更改小队
	void	OnChangeManipleFromTeamRet(Msg* pMsg);
	//更改小队队长标识
	void	OnRetFlagHeaderFromTeam(Msg* pMsg);
	//刷新关系
	void	OnRefreshSocialty(Msg* pMsg);

	//服务器消息，设置指定格子的物品不可用
	void	OnMsgCloseItemFormIdx(Msg *pMsg);
	

	//队伍分配模式2级以上物品提示索取或者放弃
	void	OnMsgAssign_Item_Team(Msg* pMsg );
	void	OnMsgTeamMemberAck(Msg* pMsg);
	//询问队长
	void	OnMsgInquireTeamHeader(Msg* pMsg);
	void	OnMsgAddTeamCancel( Msg* pMsg );
	void	OnMsgChange_AssignMode( Msg* pMsg );
	void	OnMsgChange_AssignMode_Result( Msg* pMsg );

	//询问被邀请者
	void	OnMsgInquireInvitee(Msg* pMsg);
	//	设置npc身上的战斗状态
	void	OnMsgUpdateCharacterBodyStatus(Msg* pMsg);
	//	清除npc身上的战斗状态
	void	OnMsgClearBodyStatus(Msg* pMsg);
	//	服务器发过来转身的消息
	void	OnMsgChangeDir(Msg* pMsg);
	//HP和MP的改变
	void	OnMsgHPMPModify(Msg* pMsg);
	void	OnMsgFirstEvent(Msg* pMsg);
	void	OnMsgGetGuildIcon(Msg* pMsg);
	void	OnMsgGetReputeName(Msg* pMsg);
	void	OnMsgInviteAddRelationAck(Msg* pMsg);
	void	OnMsgGuildIconUIOpen(Msg* pMsg);
	//建筑状态
	void	OnMsgBuildStatus( Msg* pMsg );
	void	OnMsgBuildDestroyed( Msg *pMsg );
	void	OnMsgBuildSelfDestroyed( Msg *pMsg );
	void	OnMsgBuildFailed( Msg *pMsg );

	
	void	OnMsgGuildAckDismiss( Msg* pMsg );
	void	OnMsgGuildMemberOnline( Msg* pMsg );
	//-------------------------------------------------------------------------------------------------------------
	//帮会
	void	OnMsgGuildAckCreateNotice(Msg*);// 回应请求创建帮派
	void OnMsgFamilyNameChangeNotice(Msg*); //修改家族名返回的提示
	void OnMsgGuildTanHeNotice( Msg*);// 申请弹劾回馈notice
	void OnMsgGuildOfferbuildNotice(Msg*);// 回应帮贡建设notice
	void OnMsgGuildReleaseNotice(Msg*);//回馈客户端发布任务notice
	void OnMsgGuildDiabandTime(Msg*);// 提示帮主帮会将在某日期解散
	void OnMsgGuildDutyStatus(Msg*);// 通知客户端帮派任务发布状态
	void OnMsgGuildDonate(Msg*);// 发送募捐请求给客户端
    void OnMsgFamilyNameChange( Msg*); //修改家族名
	void OnMsgUpdateMemberData(Msg*);//帮成员信息改变
	void OnMsgUpDateGuildData(Msg*);//帮会信息改变
	void OnMsgAddGuildMember(Msg*);//通知帮会成员，有人加入
	void OnMsgSomeOneJoinGuild(Msg*);// 通知附近玩家某人加入帮派了
	void OnMsgSomeOneLeaveGuild(Msg*);// 通知附近玩家某人离开帮派了
	void OnMsgDelGuildMember(Msg*);//通知帮会成员，有人离开
	void MeLeaveGuild();
	void OnMsgGuildMemberLeave( Msg* pMsg );//我离开帮会
	void OnMsgJoinGuildNotice( Msg* pMsg );// 回应申请加入帮派notice
	void OnMsgReciveGuildList(Msg*);//客户端接收所有帮派列表
	void OnMsgGuildDelateResult(Msg*);//弹劾结果
	void OnMsgAddNewGuild(Msg*);//有新帮派创建
	void OnMsgFamilyChangeNotice(Msg*);// 服务器回应修改家族
	void OnMsgGuildAssignPositionNotice(Msg*);//职位任免notice
	void OnMsgGuildTransferAck(Msg*); //回复转让职位
	void OnMsgRemoveGuildMemberNotice(Msg*);//踢人出帮notice
	void OnMsgGuildCreateNotice(Msg*);//创建家族notice
	void OnMsgGuildLevelUpNotice(Msg*);// 回馈升级帮会消息
	void OnMsgGuildDisband(Msg*);// 通知客户端帮派解散了
	void OnMsgGuildShopLevelUpNotice(Msg*);// 回馈帮派商店激活消息
	void OnMsgGuildBuyItemNotice( Msg*);//帮会商店买东西的回馈
	void OnMsgGuildMemberMoveNotice(Msg* pMsg);//转移帮众notice
	void OnMsgInviteGuildNotice(Msg*);// 回应邀请进入帮派notice
	void OnMsgGuildMasterConvent(Msg*);// 帮主召集帮众 到某个地图
	void OnMsgResetGuildMemberActive(Msg*);// 通知将所有成员本周活跃度设置到上周, 并清除本周的活跃度
	void OnMsgStudentLevelUp(Msg*);//徒弟升级，师傅威望增加
	void	OnMsgGuildReqInvite( Msg* pMsg );
	void OnMsgApplyJoinGuild(Msg*);//回应申请加入帮派
	void ShowGuildInfo(const char*);
	//-------------------------------------------------------------------------------------------------------------
	/*帮会战*/
	void OnMsgFlyToCampBattleReq(Msg*);// 服务器通知客户端是否要进入帮派阵营战场
	void OnMsgGetCampBattleInfo(Msg*);// 阵营战场的杀人信息
	void OnMsgGetMyFightCampType(Msg*);// 通知客户端阵营消息
	void OnMsgShowCampGuildBattleEnter(Msg*);// 显示帮派争夺战进入窗口
	void OnMsgEnterCampBattleNotice(Msg*);//进入战场结果回馈notice
	void OnMsgGetGuildBattleResult(Msg*);//通知帮派争夺战结果
	void OnMsgCampBattleSignNotice(Msg*);//报名结果回馈notice
	void OnMsgGuildBattleStatus(Msg*);// 通知阵营战场状态
	void OnMsgGuildFightInfo(Msg*);// 通知阵营战场杀人
	void OnMsgGetCampBattleResource(Msg*);// 同步战场资源分
	void OnMsgSignGuildCampBattleFailed(Msg*);// 通知帮主, 你的帮派最后一个报名没有匹配上, 不能参加帮派争夺战
	void OnMsgGetGuildCampBattleMatch(Msg*);// 通知阵营战场对阵列表
	void OnMsgKillCampBattleMonster(Msg*);// 战场杀死怪物
	void OnMsgCampBattleSignUpReplace(Msg*);// 通知帮派帮主, 你的报名中被其他帮派顶替了
	void OnMsgCampGuildMonsterRefresh(Msg*);// 通知战场内玩家, 某某怪刷出来了
	void ShowGuildBattleInfo(const char* szText);

	void OnMsgCountryBattleGuild(Msg*);// 全国广播某个帮派获得了战场资格
	void OnMsgCountryBattleResult(Msg*);// 通知国家战场结果
	void OnMsgCountryBattlePlayerCount(Msg*);// 发送战场队员个数, 以及帮主死亡次数 ( 红方就是守擂方, 蓝方就是抢擂方 )
	void OnMsgTellCampBattleDeathCount(Msg*);//当前的死亡次数
	/*void ShowCampBattleInfo(const char* szText);*/
	//-------------------------------------------------------------------------------------------------------------
	//void	OnMsgGuildMemberDismiss( Msg* pMsg );// 请求辞去帮派职务
/*	void	OnMsgGuildAckJoin( Msg* pMsg );
	void OnMsgGuildMemberLevel( Msg* pMsg );
	void OnMsgGuildMemberOffline( Msg* pMsg );
	void OnMsgGuildMemberTitle( Msg* pMsg );
	void	OnMsgGuildMemberOffer( Msg* pMsg );
    void	OnMsgGuildFlagChange( Msg* pMsg );
    void	OnMsgGuildExpChange( Msg* pMsg );
    void	OnMsgGuildRankChange( Msg* pMsg );
    void	OnMsgGuildLevelChange( Msg* pMsg );
    void	OnMsgGuildAckLeave( Msg* pMsg );
	void	OnMsgGuildMemberBan( Msg* pMsg );
    void	OnMsgGuildMemberTellGuildId( Msg* pMsg );
	void	OnMsgGuildQueryJoin( Msg* pMsg );
	void	OnMsgGuildGetAllMemberInfo( Msg* pMsg );
	void	OnMsgGuildIntro( Msg* pMsg );
	void	OnMsgGuildAttrDesc( Msg* pMsg );
	void	OnMsgGuildDeclare( Msg* pMsg );
	void    OnMsgAckGuildCreate( Msg* pMsg );*/

	// 通知客户端添加某种关系的剩余时间
	void OnMsgAddRelationCoolDownTime(Msg*);
	//
	void	OnSkillBeginCoolDown( Msg* pMsg );
	void	OnMsgTeamPlayerInfo( Msg *pMsg );
	//
	void	OnMsgAddSkill( Msg* pMsg );
	void    OnMsgChangeSkillBySelect( Msg* pMsg );
	void SetSkillAutoToListImage(SCharSkill*);
	//
	void	OnMsgTellExploit( Msg* pMsg );
	void	OnMsgExploitChange( Msg* pMsg );
	void	OnMsgTellOfficialLevel( Msg* pMsg );

	// 声望
	void	OnMsgTellReputation( Msg* pMsg );

	void	OnMsgPlayerNameChanged( Msg*pMsg );
	void	OnMsgCityInfo( Msg *pMsg );

	//
	void	OnMsgTeachSkill( Msg *pMsg );
	//
	void	OnMsgChangePKRecord( Msg *pMsg );
	//
	void	OnMsgGetAllNpcOnTheMap( Msg* pMsg );

	//
	void	OnMsgTellMapNpcQuest( Msg* pMsg );
	void	OnMsgTellCharVars( Msg* pMsg );
	void	OnShowText( Msg* pMsg );

	void	OnShowBank(Msg* pMsg);
	void	SetStorage( Msg* pMsg);
	//
    void	OnMsgAckCompound( Msg* pMsg );
	//
	void	OnLobbyMsgRoomInfo( Msg* pMsg );
	void	OnLobbyMsgAckCreateRoom( Msg* pMsg );
	void	OnLobbyMsgAckJoinRoom( Msg* pMsg );
	void	OnLobbyMsgAckLeaveRoom( Msg* pMsg );
	void	OnLobbyMsgRoomDismiss( Msg* pMsg );
	void	OnLobbyMsgAckPlayerProfile( Msg* pMsg );
	void	OnLobbyMsgThirdPartyMsg( Msg* pMsg );
	void	OnLobbyMsgPlayerCheat( Msg* pMsg );
	void	OnLobbyMsgAckUseCard( Msg* pMsg );
	void	OnLobbyMsgReqUseCard( Msg* pMsg );

	//
	void	OnMsgPlayMusic(Msg* pMsg);
	void	OnMsgScriptMakeItem(Msg* pMsg);
    void	OnMsgScriptQuestDlg(Msg* pMsg);

	void	OnMsgAckQuestInfo(Msg* pMsg);

	void	OnMsgPopMapNpcList(Msg*pMag);
	void    OnMsgProfessionChangInfo(Msg* pMsg);
	void	OnMsgChangeFightState(Msg* pMsg);
	void	OnMsgAgreeUseSpecialSkill();
	void	OnMsgAgreeReadytoUseSpecialSkill(Msg* pMsg);
	//
	void	OnMsgNpcPlayAnim(Msg* pMsg);
	void	OnMsgScriptSetHotkey(Msg* pMsg);

	void    OnMsgChangEquipHp(Msg* pMsg);
	void	OnMsgUpdateTime(Msg* pMsg);

	void    OnMsgIntensifyEquip(Msg* pMsg);
	void    OnMsgEquipMaintainAck(Msg* pMsg);
	void    OnMsgItemReclaim(Msg* pMsg);
	void    OnMsgIITEMCOMPOSEGEM(Msg* pMsg);
	void    OnMsgZhuJiangCOMPOSE(Msg* pMsg);

	void	OnMsgFransferStarAck(Msg* pMsg);

	void    OnMsgUseGood(Msg* pMsg);

	void    OnMsgRepairItemByServer(Msg* pMsg);
	void    OnMsgClearPwd(Msg* pMsg);
	void    OnMsgOperateBank(Msg* pMsg);

	void    OnMsgShowLevelUpInfo(Msg* pMsg);
	void    OnMsgSetPwdToPlayer(Msg* pMsg);

	void    OnMsgShowIntensifyUI(Msg* pMsg);
	//Seek Equip
	void	OnMsgSeekEquip( Msg* pMsg );
	void    OnMsgChangeItemPwd( Msg* pMsg );
	void	OnMsgEctypeMapInfo( Msg* pMsg );

    void    OnMsgReqDuel( Msg* pMsg );
    void    OnMsgDuelStart( Msg* pMsg );
    void    OnMsgDuelEnd( Msg* pMsg );
	void	OnMsgAckDuel( Msg* pMsg );
    void    OnMsgGuildMemberPos( Msg* pMsg );

	void	OnMsgSetItemAscription( Msg* pMsg );

	void    OnMsgSkillExpChang(Msg* pMsg);

	void    OnMsgReqSkillID(Msg* pMsg);

	void    OnMsgKillMonster(Msg* pMsg);

    void    OnMsgPKStateChange(Msg* pMsg);
    void    OnMsgAckChangePKFlag(Msg* pMsg);

	void	OnMsgPlayEffect(Msg* pMsg);
	void	OnMsgShowIntonateBar(Msg* pMsg);

	void    OnMsgReqRelive(Msg* pMsg);

	void    OnMsgChangPower(Msg* pMsg);

	void    OnMsgChangPowerPoint(Msg* pMsg);

    void	OnMsgIntonatingOverTime(Msg* pMsg);

	void	OnReqMsgCovCorps( Msg *pMsg );

	void	OnOpenUI( Msg* pMsg );
	//
	void	OnMsgChangeBagSize(Msg* pMsg);

	void    OnMsgReduceItem(Msg* pMsg);
	void    OnMsgGuildGiveExp(Msg* pMsg);


	void    OnMsgAskGetShopCenter(Msg* pMsg);

	void    OnMsgShowReduceUI(Msg* pMsg);
	void    OnMsgShowUnsoulBoundUI(Msg* pMsg);

	void    OnMsgUnsoulBound(Msg* pMsg);

	void	OnMsgRetShopCenterItemCnt( Msg* pMsg );

	void    OnMsgSetReliveSilver(Msg* pMsg);

	void    OnMsgCostSilverReqair(Msg* pMsg);

	void    OnMsgLockNum(Msg* pMsg);
	void    OnMsgReqYuanBaoCnt( Msg *pMsg );

	void    OnMsgShowLockIntensifyUI(Msg* pMsg);
	void    OnMsgLockIntensifyRec(Msg* pMsg);
	void	OnChange_OwnAttribute( Msg* pMsg );

	void    OnMsgNewCompoound(Msg* pMsg);

    void    OnChangeBattleFlag(Msg* pMsg);

	void    OnMsgCompoundRateAdd(Msg* pMsg);
	void    OnMsgIntensifyRateAdd(Msg* pMsg);

	void    OnMsgShopCenterOffSell(Msg* pMsg);

	void	OnMsgDelReputeName(Msg* pMsg);

	// --联盟相关--Luo
	void	OnMsgAckGuildList( Msg* pMsg);

    void    OnMsgUpdateGuildInfo( Msg* pMsg );
    void    OnMsgAckGuildIcon( Msg* pMsg );
    void    OnMsgAckGuildRelationChanged( Msg* pMsg );
    void    OnMsgInviteLeague( Msg* pMsg );

	//师徒
	void    OnMsgEnterWorldS(Msg* pMsg);
	void    OnMsgEnterWorldT(Msg* pMsg);

	void    OnMsgReStudentMsg(Msg* pMsg);
	void    OnMsgReTeacherMsg(Msg* pMsg);

	void    OnMsgReSandTRemoveMsg(Msg* pMsg);

	void    OnMsgReqApplySAndT(Msg* pMsg);

    void    OnMsgReqShowEMSMrg(Msg* pMsg);

    void    OnMsgSwitchGate(Msg* pMsg);
    void    OnMsgEnterWorld(Msg* pMsg);
    void    OnMsgEndGetCharacter(Msg* pMsg);

	//-------任务---------------------
	void	OnMsgAckScript(Msg* pMsg);
	void	OnMsgAckResult( Msg* pMsg );
	void	OnMsgScriptEnd( Msg* pMsg );
	//-------新手指引-----------------
	void    OnMsgUpdateGuideAck( Msg* pMsg );
//-------------------------------
	void    OnMsgGuildNotice(Msg* pMsg);
	void	OnMsgGuildNoticeAck(Msg *pMsg);
	//added by zilong. 2011-04-13. --------------------
	void OnMsgTellGuildAim(Msg* pMsg);
	void OnMsgChangeGuildAimAck(Msg* pMsg);
	//added by zilong. end. ---------------------------
	void    OnMsgMEMBER_TITLE(Msg* pMsg);

	void	OnMsgGetMount(Msg* pMsg);
	void	OnMsgUpdateMount(Msg* pMsg);
	void	OnMsgMountStrengthenAck(Msg* pMsg);
	void	OnMsgKillPlayerNum(Msg* pMsg);
	void    OnMsgConKillPlayer(Msg* pMsg);
	// added, jiayi, [2009/9/21], 称号
	////////////////////////////////////////
	//// 称号
	void	OnMsgTellCurrentTitle( Msg* pMsg );
	void	OnMsgTellTitleList( Msg* pMsg );
	void	OnMsgAddTitleAck( Msg* pMsg );
	void	OnMsgRemoveTitleAck( Msg* pMsg );

	void	OnMsgMapInfoReady( Msg* pMsg );

	////////////////////////////////////////
	//// 配方
	void	OnMsgAddRecipeAck( Msg* pMsg );

    // 拾取包裹，物品分配
    void    OnMsgTellPackageAccess( Msg* pMsg );
    void    OnMsgPackageViewAck( Msg* pMsg );
    void    OnMsgPickPackageItemAck( Msg* pMsg );
    void    OnMsgPackageItemBoultReq( Msg* pMsg );
    void    OnMsgPackageItemBoultNumber( Msg* pMsg );
    void    OnMsgPackageItemNeedToAssign( Msg* pMsg );
    void    OnMsgPackageItemAssignAck( Msg* pMsg );

    // 组队分配模式
    void    OnMsgTellTeamAssignInfo( Msg* pMsg );
    void    OnMsgChangeAssignItemLevelAck( Msg* pMsg );
    void    OnMsgPackageitemAccessAck( Msg* pMsg );
    void    OnMsgTellPickPackageItem( Msg* pMsg );

    // 仓库存钱
    void    OnMsgStorageMoneyAck( Msg* pMsg );

    // 副本倒计时
    void    OnMsgEctypeStageTimeRemain( Msg* pMsg );

    // 清空技能CD
    void    OnMsgClearSkillCollDown( Msg* pMsg );

	// 返回验证码
	void	OnMsgReqGraphicCode( Msg* pMsg );

	// 充值点数
	void	OnMsgAccountPoint( Msg* pMsg );

	//////////////////////////////幸运大闯关///////////////////////////////////
	// 触发客户端，显示界面
	void	OnMsgTellLuckReward( Msg* pMsg );
	void	OnMsgLuckRewardAck( Msg* pMsg );
	void	OnMsgLuckRewardResult( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////宝箱//////////////////////////////////////
	void OnMsgShowTreasureBox( Msg* pMsg );
	void OnMsgTreasureBoxResult( Msg* pMsg );
	void OnMsgTreasureBoxAck( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////酒馆任务//////////////////////////////////
	void OnMsgResetPubQuestAck( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////

	void OnMsgTellGameStage( Msg* pMsg );

	////////////////////////////////移星//////////////////////////////////////
	void OnMsgMoveStarAck( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////特殊修理//////////////////////////////////
	void OnMsgSpecialRepairItemAck( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////装备升阶//////////////////////////////////
	void OnMsgEquipUpdateItemAck( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////
    /** 使用守护天使
    */
    void    OnMsgUseAngell(Msg* pMsg);

    void    OnMsgShowHelmet(Msg* pMsg);

    void    OnMsgSwitchSuit(Msg* pMsg);

	void    OnMsgShowTimeTop(Msg* pMsg);
	void    OnMsgShutDownTimeTop(Msg* pMsg);

	void    OnMsgSuitElementCheckupAck( Msg* pMsg );
	//void    OnMsgMoneyItemExchangeAck( Msg* pMsg );

	void	OnMsgTellTeamInfo( Msg* pMsg );
	void	OnMsgTellTeamMemberList( Msg* pMsg );

    void    OnMsgChangeProtectLockTimeAck(Msg* pMsg);
    void    OnMsgTellAntiAddictionAccountInfo(Msg* pMsg);

    // 拆分物品后服务器反馈
    void    OnMsgMoveGoodsAck(Msg* pMsg);

	// 加锁物品反馈
	void    OnMsgLockItemAck(Msg* pMsg);
	// 解锁物品反馈
    void    OnMsgUnLockItemAck(Msg* pMsg);

	// 物品解锁
	void    OnMsgCheckUnLockItemAck( Msg* pMsg );

	// 反外挂
	void	OnMsgCheckCheatReq( Msg* pMsg );
	void	OnMsgGetProcessListReq( Msg* pMsg );

	// 领取倒计时礼物
	void	OnMsgOnLineRewardAck( Msg* pMsg );
	void    OnMsgTellTurenReward(Msg* pMsg);
	

	// 从仓库移独占但又堆叠的物品到包裹，服务器更新包裹中该物品GUID
	void	OnMsgMoveStorageItemAck( Msg* pMsg );

	// 回购
	void	OnMsgBuyBackItemAck( Msg* pMsg );
	void	OnMsgBuyBackItemListAck( Msg* pMsg );

	// 擂台
	void    OnMsgShowBattleSignUpDlg( Msg* pMsg );
	void    OnMsgBattleSignUpAck( Msg* pMsg );
	void    OnMsgTellBattleSignUpCount( Msg* pMsg );

	// 累计在线时间
	void	OnMsgWallowAbout( Msg* pMsg );

	void	OnMsgCheckSecondPassword( Msg* pMsg );
	void	OnMsgSetSecondPassword( Msg* pMsg );
	void	OnMsgClearSecondPassword( Msg* pMsg );
	void	OnMsgCheckSecondPasswordResult( Msg* pMsg );

	//积分商城
	void	OnMsgJiFengShopItemListAck( Msg* pMsg );
	//更新商城信息
	void    OnMsgUpdateTradeShopConfig( Msg* pMsg );
	void    OnMsgTradeShopChange( Msg* pMsg );
public:
    void   OnMsgMailList(Msg* pMsg);  //新邮件列表
    void   OnMsgMailOnAck(Msg* pMsg);   //邮件反馈
    void   OnMsgMailNotify(Msg* pMsg);  //新邮件通知
    void   OnMsgMailOpAck(Msg* pMsg);   //邮件操作反馈
public:
	//移星石升级
	void	OnMsgMoveStarLevelUpAck( Msg* pMsg );
	//升星保星材料升级
	void	OnMsgItemComposeAck( Msg* pMsg );
	//元宝寄售
	void	OnMsgReturnSystemAuction( Msg* pMsg );
	void	OnMsgAckHandleSystemAuctionAccountMoney( Msg* pMsg );
	void	OnMsgAckExcuteSystemAuction( Msg* pMsg );
	void    OnMsgAuctionHistroyList(Msg* pMsg); 
	void    OnMsgOperateMoneyAck(Msg *pMsg);
	void    OnMsgConsignmentOperateAck(Msg *pMsg);
	void    OnMsgQueryConsignmentListAck(Msg *pMsg);
	void    OnMsgConsignmentMoneyHistroyAck(Msg *pMsg);
	void    OnMsgTellConsignmentMoney(Msg *pMsg);
public:
//------------------杀人--------------------------------
    void   OnMsgKillNumProcess(Msg *pMsg);          //通知杀人数处理
//---------------------------------------------------------

//--------------五行转移系统------------------------------
    void OnMsgFiveXingMoveAck(Msg *pMsg);
//--------------------------------------------------------
	// 师徒消息
	//void	OnMsgMasterReportAck(Msg* pMsg);		// 师傅指点结果
	void	OnMsgMasterReportResult(Msg* pMsg);		// 师傅指点成功后发给徒弟消息
	//void	OnMsgPrenticeReportAck(Msg* pMsg);		// 徒弟汇报结果
	//void	OnMsgPrenticeReportResult(Msg* pMsg);	// 徒弟汇报成功后发给师傅消息

	//小队战场
	void    OnMsgTellBattleRecord(Msg* pMsg);//小队战场成绩
	void    OnMsgTellBattleTeamRecord(Msg* pMsg);//小队战场成绩
	void    OnMsgTellBattleSignUpInfo(Msg* pMsg);//小队信息
	void	OnMsgEnterTeamBattleReq(Msg* pMsg);//通知进入战场
	void	OnMsgBattleTeamInfo(Msg* pMsg);
	void	OnMsgQueryBattleSignUpTimeAck(Msg *pMsg);

	// 好友赠送礼物
	void	OnMsgShowViewUseItemToPlayer(Msg *pMsg);// 通知其他玩家, 某人给某人使用了某种物品( 区域范围内客户端显示特效用 )
	void	OnMsgShowAllUseItemToPlayer(Msg *pMsg);	// 全服公告, 某人给某人使用了某物品多少个

	// 协议离婚
	void	OnMsgDelFriendCheckReq(Msg *pMsg);		// 收到协议离婚请求
	void	OnMsgDelFriendCheckAck(Msg *pMsg);		// 请求方收到协议离婚结果

    //添加交子改变
    void   OnMsgJiaoZiChange(Msg *pMsg);            //交子改变消息

	// NPC隐藏/显示
	void	OnMsgTellHideStatus(Msg *pMsg);

	//保护怪位置
	void OnMsgTellProtectPetPos(Msg*);

    void    OnMsgMountAckBreed( Msg *pMsg );        // 交配成功
    void    OnMsgAckOfflineHook( Msg *pMsg );       // 开始离线挂机

//-------------------------国家---------------------------       added by zhuomeng.hu		[8/25/2010]
	void OnMsgTellCountryBattleSignUp( Msg *pMsg );					    // 国家战场报名开始
	void OnMsgTellCountryBattleEnter( Msg *pMsg );                      // 国家战场开始进入
	void OnMsgTellCountryBattleFight( Msg *pMsg );                      // 国家战场战斗开始
	void OnMsgTellCounterBattleResult( Msg *pMsg );                     // 国家战场结束, 通告结果
	void OnMsgCountryBattleSignUpAck( Msg *pMsg );                      // 国家战场报名回馈
	void OnMsgEnterCounterBattleAck( Msg *pMsg );                       // 进入国家战场
	//void OnMsgQueryCountryBattleSignUpAck( Msg *pMsg );                 // 查询国家战场报名回馈
	void OnMsgTellCountryTitleInfo( Msg *pMsg );                        // 广播国家称号
//	void OnMsgQueryCountryInfoReq( Msg *pMsg );                         // 查看国家信息
	void OnMsgQueryCountryInfoAck( Msg *pMsg );                         // 查看国家信息
	void OnMsgTellCountryQueryStatus( Msg *pMsg );                      // 通知国家任务状态
//	void OnMsgCountryNoticeChangeReq( Msg *pMsg );                      // 请求更改国家公告
	void OnMsgCountryNoticeChangeAck( Msg *pMsg );                      // 更改国家公告回馈
	void OnMsgAddCountryInfoReq(Msg* pMsg);
	void OnMsgLoadCountryInfoAck(Msg* pMsg);
//	void OnMsgCountryQuestStateChangeReq( Msg *pMsg );                  // 请求发布国家任务
	void OnMsgCountryQuestStateChangeAck( Msg *pMsg );                  // 请求发布国家任务回馈
//	void OnMsgCountryOfficialAppointReq( Msg *pMsg );                   // 请求任命国家官员
	void OnMsgCountryOfficialAppointAck( Msg *pMsg );                   // 请求任命国家官员回馈
//	void OnMsgCountryOfficialRecallReq( Msg *pMsg );                    // 请求免除国家官员
	void OnMsgCountryOfficialRecallAck( Msg *pMsg );                    // 免除国家官员职位回馈
	void OnMsgCountryQuestStatusStop( Msg *pMsg );                      // 通知国家发布任务结束了
	void OnMsgTellCountryKillPosition( Msg *pMsg );                     // 全世界广播杀死了某国官员
	void OnMsgCountryRequestRaiseReq( Msg *pMsg );                      // 客户端请求募集国家资金
	void OnMsgCountryRequestRaiseAck( Msg *pMsg );                      // 国家募集回馈给申请者
	void OnMsgCountryRaiseToPlayerReq( Msg *pMsg );                     // 服务器发送募捐给所有玩家, 客户端判断等级
//	void OnMsgCountryRaiseToPlayerAck( Msg *pMsg );                     // 玩家募捐回馈
	void OnMsgCountryRaiseTellPlayer( Msg *pMsg );                      // 通知玩家募集结果
	void OnMsgCountryReceiveMountAck( Msg *pMsg );                      // 领取国家坐骑回馈
	void OnMsgTellCountryBordersFight( Msg *pMsg );                     // 记录国家边塞战斗的坐标( 客户也记录, 记录队列长队在CountryConfig设置 )
	void OnMsgTellCountryKillEnemy( Msg *pMsg );                        // 通知客户端 某某某抵御了外敌
//	void OnMsgCountryFlyToBordersReq( Msg *pMsg );                      // 左右捕请求飞往边塞
//	void OnMsgCountryOperateToPlayerReq( Msg *pMsg );                   // 客户端请求操作
	void OnMsgCountryOperateToPlayerAck( Msg *pMsg );                   // 客户端操作回馈
	void OnMsgCountryTellOperateToPlayer( Msg *pMsg );                  // 通知被操作者 你被干嘛了
    void OnMsgTellOperateToCountry( Msg *pMsg );                        // 玩家被国王OOXX了
	void OnMsgCountryConveneResult( Msg *pMsg );                        // 申请国家召集结果 
	void OnMsgCountryConveneReq( Msg *pMsg );                           // 服务器给客户端召集请求
//	void OnMsgCountryConveneAck( Msg *pMsg );                           // 是否同意召集 ( 不同意不用回消息 )
	void OnMsgCountryCountryAppoint( Msg *pMsg );						// 通知被任命或者被免职
    void OnMsgTellCountryBattleGuild( Msg *pMsg );                      // 全国广播某个帮派获得了战场资格
    void OnMsgCountryChangeAck( Msg *pMsg );                            // 叛国回馈
    void OnMsgCountryTellCountryID( Msg *pMsg );                        // 叛国，通知国家ID
    void OnMsgCountryTellWeak( Msg *pMsg );                             // 变弱国
	void OnMsgCountryTellStrong( Msg *pMsg );                             // 变强国
    void OnMsgCountryBattleReplace( Msg *pMsg );                        // 通知帮派帮主, 你的帮派在国家争夺战报名中被其他帮派顶替了
    void OnMsgTellCountryName( Msg *pMsg );                             // 初始化国号
    void OnMsgChangeCountryNameAck( Msg *pMsg );                        // 更改国号回馈
    void OnMsgTellCountryNameChange( Msg *pMsg );                       // 广播国号改变
    void OnMsgTellMassacreCountry( Msg *pMsg );                         // 屠城战
    void OnMsgUpdateCountryWarFightKill( Msg *pMsg );                   // 屠城战杀人计数
    void OnMsgTellCountryPlayerRaise( Msg *pMsg );                      // 募捐公告
	void OnMsgUpdateCountryDate(Msg *pMsg);								// 贡品更新回馈
	void OnMsgGuildSQACK(Msg *pMsg);		
	void OnMsgGuildAddSQ(Msg *pMsg);
	void OnMsgGuildDElSQ(Msg *pMsg);
	void OnMsgFlyMap(Msg *pMsg);
	void OnMsgTellCountryPlayerRaiseItem(Msg *pMsg);
	void OnMsgTellGuildPlayerRaiseItem(Msg *pMsg);
    //------------------------------------------------------------

	void OnMsgActionInterrupt( Msg* pMsg );								// 动作打断消息

	//----------------------大史记--------------------------------
	void OnMsgOnOffNpcShip(Msg *pMsg);

    //---------------------新的交易-------------------------------      added by ZhuoMeng.Hu		[12/15/2010]
    void OnMsgBargainingAck( Msg* pMsg );                               // 交易申请回馈
    void OnMsgBargainingRequestReq( Msg* pMsg );                        // 通知客户端, 某人申请与你交易
    void OnMsgBargainingStart( Msg* pMsg );                             // 通知客户端  与某人的交易开始
    void OnMsgBargainingFinish( Msg* pMsg );                            // 通知客户端  交易结束
    void OnMsgBargainingStatus( Msg* pMsg );                            // 通知客户端 某玩家的交易状态
    void OnMsgBargainingDataAck( Msg* pMsg );                           // 通知玩家加入了物品到交易栏中
    void OnMsgShowBargainingData( Msg* pMsg );                          // 通知对方玩家交易的数据
    void OnMsgRemoveBargainingDataAck( Msg* pMsg );                     // 回应移除交易物品, 客户端删除该位置的物品
    void OnMsgBargainingDataError( Msg* pMsg );                         // 通知客户端交易物品的各类错误             
    //------------------------------------------------------------

    //---------------------坐骑仓库-------------------------------      added by ZhuoMeng.Hu		[12/17/2010]
    void OnMsgUpdateMountStorage( Msg* pMsg );                          // 坐骑仓库数据更新
    void OnMsgUpdateCharMount( Msg* pMsg );                             // 玩家身上坐骑列表更新
    //------------------------------------------------------------

    //---------------------新的摆摊-------------------------------      added by ZhuoMeng.Hu		[12/20/2010]
    void OnMsgAddSellDataAck( Msg* pMsg );                              // 添加一个出售的物品错误信息
    void OnMsgAddBuyDataAck( Msg* pMsg );                               // 回馈添加收购物品的错误信息
    void OnMsgStartStallAck( Msg* pMsg );                               // 回馈摆摊请求错误
    void OnMsgBuyOrSellStallAck( Msg* pMsg );                           // 回馈购买或者出售的错误
    void OnMsgUpdateStallData( Msg* pMsg );                             // 更新摊位的信息到客户端
    void OnMsgTellStartStall( Msg* pMsg );                              // 通知附近玩家, 某人摆摊了
    void OnMsgTellCloseStall( Msg* pMsg );                              // 通知附近玩家关闭摊位
    void OnMsgShowStallData( Msg* pMsg );                               // 发送摊位数据到客户端
    void OnMsgTellBuyOrSellStallData( Msg* pMsg );                      // 通知摊主 玩家 购买 或者 出售给自己东西
    void OnMsgTellStallDataCount( Msg* pMsg );                          // 通知打开摆摊界面买卖操作的玩家
    void OnMsgTellStallTitleToView( Msg* pMsg );                        // 通知周围玩家某玩家的摊位标题改变了
    void OnMsgTellStallPrice( Msg* pMsg );                              // 通知摊位上某个物品价钱
    void OnMsgTellTotalStallData( Msg* pMsg );                          // 通知摊主, 自己摊位上的所有信息
    //------------------------------------------------------------

    void OnMsgTellServerExpModulus( Msg* pMsg );                        // 经验倍率调整
    void OnMsgUpdateQuestVar( Msg* pMsg );                              // 任务计数变量从ShowText里分离

    void OnMsgOfflineFightOpAck( Msg* pMsg );                           // 战斗助手开关回馈

	//人物属性点反馈
	void OnMsgCharAssignPotentialAck(Msg* pMsg); 

	//added by zilong. 2011-02-18. -----------------------------------
	//---------------------------心法相关-----------------------------
	void On_MSG_CHANGEXINFA(Msg *pMsg);
	//added by zilong. end. ------------------------------------------

	//added by zilong. 2011-02-28. -----------------------------------
	//---------------------------摊位查询系统相关-----------------------------
	void On_MSG_ACKSTALLQUERY(Msg *pMsg);
	//added by zilong. end. ------------------------------------------
	void OnMsgGotOnOffDrome(Msg *pMsg);
	void OnMsgReqGotOnDrome(Msg *pMsg);
	void OnMsgReqGotOnDromeAck(Msg *pMsg);

	//added by zilong. 2011-03-18. -----------------------------------
	//---------------------------角色心情-----------------------------
	void On_MSG_SHOWSIGNATURE(Msg *pMsg);
	void On_MSG_CHANGESIGNATUREREQ(Msg *pMsg);
	//added by zilong. end. ------------------------------------------
	
	//--------宠物---------------------
	void OnMsgAddUpdatePet(Msg *pMsg);           //添加更新宠物
	void OnMsgChangePet(Msg *pMsg);              //改变宠物状态
	void OnMsgPetBreedReqAck(Msg *pMsg);         //宠物繁殖反馈
	void OnMsgPetBreedChoiceAck(Msg *pMsg);      //宠物选择反馈
	void OnMsgPetBreedStatus(Msg *pMsg);         //宠物锁定反馈
	void OnMsgPetBreedFinish(Msg *pMsg);         //宠物交易反馈
	void OnMsgPetBreedAcquireAck(Msg *pMsg);     //宠物繁殖交配反馈
	void OnMsgPetCardList(Msg *pMsg);						//更新单个宠物图鉴
	void OnMsgPetCardListAll(Msg *pMsg);				//所有宠物图鉴
	void OnMsgPetSavvyUpack(Msg *pMsg);				//宠物提升悟性结果
	void OnMsgPetUpdateChar(Msg *pMsg);				//更新宠物角色信息
	void OnMsgPetDead(Msg *pMsg);							//出战宠物死亡信息
	void OnMsgPetLearnSkill(Msg *pMsg);					//宠物学习得到技能
	void OnMsgLookOtherPet(Msg *pMsg);				//查看其他人的宠物
	void OnMsgPetBreedCancelLock(Msg *pMsg);	//取消锁定宠物	
	void OnMsgRepeatedlyPet(Msg *pMsg);       //重复注册副将
	//--------家族----------------------
	void OnMsgCreateFamilyAck(Msg *pMsg);		//回复创建家族
	void OnMsgTellFamilyInfo(Msg *pMsg);
	void OnMsgTellCreateFmily(Msg *pMsg);		//全服广播创建了家族
	void OnMsgRequestJoinFamilyReq(Msg *pMsg);	//族长收到加入家族的请求
	void OnMsgInviteJoinFamilyReq(Msg *pMsg);
	void OnMsgInviteFamilyAck(Msg *pMsg);
	void OnMsgFamilyAimAck(Msg *pMsg);

	//------法宝--------------------------
	void OnMsgEquipTalismanAck(Msg* pMsg);   //装备法宝
	void OnMsgUnEquipTalismanAck(Msg* pMsg); //卸载法宝
	void OnMsgChangeTalisman(Msg* pMsg);     //法宝改变

	//-----视频播放---------------------
	void OnMsgPlayMovieReq( Msg* pMsg );                                // 脚本请求播放视频
	void OnMsgPlayScene(Msg *pMsg);

	void OnMsgMoviceScreen(Msg *pMsg);

	//-----------san guo add--------------------
	void OnMsgG2CReqBianShen(Msg* pMsg);
	void OnMsgTellHeroAddAttr(Msg* pMsg);

	//------------太平幻境----------------------
	void OnMsgTellTPHJRank(Msg* msg);

	//------------通知任务时间------------------
	void OnMsgTellQuestTime(Msg* msg);

	//----------------镖车相关----------------//
	void OnMsgChangeToBiaocheAck(Msg* pMsg);
	void OnMsgRestoreFromBiaocheAck(Msg* pMsg);

	//player播放动作
	void	OnMsgPlayerPlayAnim(Msg* pMsg);
	//----------------通知复活buff------------//
	void OnMsgTellReliveBuff(Msg* pMsg);

	void OnMsgReqChangeHero(Msg* pMsg);
	void OnMsgInitLevelLimit(Msg* pMsg);
	void OnMsgDoneLimit(Msg* pMsg);

	//接触指定装备的绑定
	void OnMsgUnBindEquip(Msg* pMsg);

	void OnMsgTimeStep(Msg* pMsg);

	//服务器删除装备 客户端同步
	void OnMsgRemoveItemByType(Msg* pMsg);

	//平台相应操作错误返回提示
	void OnMsgPlatformModifyError(Msg* pMsg);

	void OnMsgWorldBattle(Msg* pMsg);

	void OnMsgBattleSum(Msg* pMsg);

	void OnMonsterBeLong(Msg* pMsg);

	void OnMonsterNurtureInfo(Msg* pMsg);

	void OnMsgSendMessageEnd(Msg* pMsg);

	void OnMsgChangeMapTimeStepReq(Msg* pMsg);

	void OnMsgRandAttributeAck(Msg* pMsg);

	void OnMsgTellClientLeaveTeam(Msg* pMsg);

	void OnMsgGuildClientUpdate(Msg* pMsg);

	void OnMsgChangePetDuration(Msg* pMsg);

	void OnChangePlayerMode(Msg* pMsg);

	void OnMsgTellLeaveEctype(Msg* pMsg);

	void OnMsgTellUseItem(Msg* pMsg);

	void OnMsgUpdateCard(Msg* pMsg);
	void OnMsgCardAchieve(Msg* pMsg);
	void OnMsgCampGuildBattleRewardInfo(Msg* pMsg);

	void OnMsgCampBattleSignUpSecc(Msg* pMsg);
	void OnMsgCampBattleCheckCampBattleValueSum(Msg* pMsg);

	void OnMsgSevenDaysDataAck(Msg* pMsg);
	void OnMsgFreshStateVar(Msg* pMsg);
	void OnMsgTriggerSevenDays(Msg* pMsg);
	void OnMsgAskSevenDaysTaskAck(Msg* pMsg);
	void OnMsgChangeGuldNameAck(Msg* pMsg);
	void OnMsgSelectChannel(Msg* pMsg);
	void OnMsgChangeChannelAck(Msg* pMsg);
	void OnMsgClearTeamMapAck(Msg* pMsg);

	void OnMsgAskGetSalaryAck(Msg* pMsg);
	void OnMsgAskAdvancementAck(Msg* pMsg);
	void OnMsgShowRankTitle(Msg* pMsg);
	
	void OnMsgLoadQuestEntrustDataAck(Msg* pMsg);
	void OnMsgQuestEntrustNeedUpdate(Msg* pMsg);

	void OnMsgReconnectAck(Msg* pMsg);
	void OnMsgReconnectResetState(Msg* pMsg);
	void OnMsgGuildChangeNameAck(Msg* pMsg);
	void OnMsgRelationUpdateNameAck(Msg* pMsg);

	void OnMsgHuntingQuestList(Msg* pMsg);
	//GameBattle
	void OnMsgTellGameBattleStatus(Msg* pMsg);
	void OnMsgShowGameGuildBattleEnter(Msg* pMsg);
	void OnMsgEnterGameBattleNotice(Msg* pMsg);
	void OnMsgGetGameBattleResource(Msg* pMsg);
	void OnMsgTellGameBattleKillPlayer(Msg* pMsg);
	void OnMsgGetGameBattleInfo(Msg* pMsg);
	void OnMsgTellGameBattleMatch(Msg* pMsg);
	void OnMsgKillGameBattleMonster(Msg* pMsg);
	void OnMsgGetGameGuildBattleResult(Msg* pMsg);
	void OnMsgTellGameBattleFightCamp(Msg* pMsg);
	void OnMsgCampBattleNewDataAck(Msg* pMsg);
	void OnMsgGameBattleErrorAck(Msg* pMsg);
	void OnMsgAddCampBattleDataAck(Msg* pMsg);
	void OnMsgLoadCampBattleDataAck(Msg* pMsg);
	void OnMsgDelCampBattleDataAck(Msg* pMsg);
	void OnMsgFlyToGameBattleReq(Msg* pMsg);
	void OnMsgFlyToPosition(Msg* pMsg);

	void OnMsgQuestEntrustInfoAck(Msg* pMsg);
	void OnMsgShowCenterInfo(Msg* pMsg);
	void OnMsgQuestEntrustShowInfo(Msg* pMsg);
	void OnMsgGetThreeDayItemAck(Msg* pMsg);

	void OnMsgUpdateYuanBaoData(Msg* pMsg);

	void OnMsgRemoveItemByGuID(Msg* pMsg);
	void OnMsgUpdateAddCampBattleCD(Msg* pMsg);
	void OnMsgUpdateGuildMemberOnLineTime(Msg* pMsg);

	void OnMsgUpdatePlayerPoint(Msg* pMsg);

	void OnMsgCheckCSAuthReq(Msg* pMsg);
	void OnMsgCountryBuffChange(Msg* pMsg);

	void OnMsgLeaveExpAck(Msg* pMsg);
public:
	void ShowMosterTip(int nCount);
	void LoadMonsterConfig(CWorldTile* pszFilePath);
	SArea* GetAreaByIndex(int nIndex);
//private:
	CStageDataLoader  m_StageDataLoader;
	bool CheckChannel(SChannelInfo* pChannelInfo);
	void ChangeChannel( int32 serverId );
public:
	void InitMustData();     //初始化数字纹理和字体
	void InitBaseData();     //初始化数据
	void ShowMonsterArea();  //显示刷怪区域
	void ResetRevice();      //资源重置
	void ClearMustData();    //释放资源
	void SetShowMonsterArea(bool bValue){m_bShowMonsterArea = bValue;}
private:
	std::vector<IDirect3DTexture9*> m_NumTexSet;  //数字纹理集合
	ID3DXFont *m_pFont;     //字体
	bool       m_bShowMonsterArea;
public:
	void SetPlayerLod(float fValue){m_fPlayerLod = fValue;}
private:
	float   m_fPlayerLod;  //人物绘制时的Mipmap参数值
public:
	bool GetZByXY(float fCurrentZ,float x,float y,float &fTargetZ); 
public:
	bool InitCamera(int nModelID);
	void PlayTaskAnim(const char* pszAnim,float x,float y,float z,float fDir);
	void ProcessCamera();
	void DestroyCamera();
	void BeginTrack(){m_bPlayTrack = true;}
	void EndTrack(){m_bPlayTrack = false;}
	bool IsTracking(){return m_bPlayTrack;}
private:
	MexAnimCtrl *m_pCameraAnim;
	bool         m_bPlayTrack;
	int          m_nCameraModelID;
public:
	void GetTimeBySecond(int m_second,std::string &str);
};

CONST INT MaxMainpleCnt = 4;
#endif
