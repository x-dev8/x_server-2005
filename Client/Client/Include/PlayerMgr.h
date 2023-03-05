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
#define LOAD_PLAYER_NPC_MAX_TIME	5		//���룬ÿ֡����������Һ�NPC������ȵ����ʱ�����ƣ�������push��������֡����
#define PLAYER_RENDER_MAX			300		//ͬ����Ⱦ�������ֵ������������
#define PLAYER_RENDER_QUEUE_MAX		1000	//���������������
#define PLAYER_RENDER_DIST_MAX	TEAM_EXP_DIS          // ������Ⱦ��Զ����
#define PLAYER_RENDER_DIST_MIN	20
#define PLAYER_LOCK_DIST_MAX TEAM_EXP_DIS
#define PLAYER_SPECIAL_IDLE_ID      127     // �������������Ϊ����㲥ʱ�õ�ID

struct PlayerRenderLimitData	// ͬ����ʾ�������� 
{
	BOOL		bRendered;
	CPlayer*	pPlayer;
};
struct NetStatistics	// ����ͳ�ƣ�����PlayerMgr��Ƚ����
{
	int	iOutAvgPerSecond;
	int iOutMaxPerSecond;
	int iInAvgPerSecond;
	int iInMaxPerSecond;
};
// ��¼������ͨ����״̬
enum ECommonAttackStatus
{
    CAS_NOT_ATTACK,
    CAS_NEED_AUTO_ATTACK,           // ��Ҫ�Ե�ǰĿ���Զ�����
    CAS_ATTACK_AGAIN_WHEN_FAILED,   // �ѷ���һ�ι����������ʧ����Ҫ�ٷ�
    CAS_ATTACKING,                  // �ѳɹ�����������
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
	short stStatusID;   // ״̬id
	short stLevel;      // ״̬�ȼ�
};

class CPlayerMgr 
{
public:
	//�ĳɻ���ID��player�ṹ
	//����ID���Ҿ���Ľṹ
	//�Լ���ID
	//
	struct  ControlData
	{
		BOOL       bLeftDownFlag;          //������µı�־
		BOOL        bRightDownFlag;         //�Ҽ����µı�־
		//
		BOOL        bAutoProcFlag;          //�Զ�����ı�־..��mouse��ס2���ı�־��Ч
		DWORD       dwAutoProcTime;         //�Զ������ʱ��
		//
		DWORD       dwAutoPressTime;        //����������Ϣ��ʱ��
		//��ǰ���������
		GameObjectId			LockNpcID;				//ȡ��������npc�ı��
		//CPlayer*    pLockPlayer;
		int			iUseSkill;				//��ǰʹ�õļ���
		int			iUseSkillLevel;			//���ܵĵȼ�
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
		int nQuestId;	// ������
		char chState;	// �������״̬
	};
	struct SNpcQuestInfo
	{
		std::string strName;
		std::vector<void*> vectorRelateQuestInfo;	// ���������Ϣ
		void		InitialRelateQuestInfo();
		SNpcQuestInfo()
		{

		}
	};
	struct SShowPlayerHP
	{
		//��ǰ�Ĺ���Ŀ��
		GameObjectId nIDAttackTarget;
		//���ָ���
		GameObjectId nIDMouseOver;		
		GameObjectId nIDLockNpc;//��ǰ������npc
	}m_showhp;

	enum
	{
		eNpcTips_None,
		eNpcTips_HaveQuest,				// ���������
		eNpcTips_HaveQuestNotNow,		// ���������,�������㻹���ܽ�
		eNpcTips_QuestDone,				// �������
		eNpcTips_QuestNotDone,			// ����δ���
        eNpcTips_CampBattleS,           //�������ռ��
        eNpcTips_CampBattleT,           //�����ƾ�ռ��
        eNpcTips_CampBattleZL,          //����������ռ��
	};

	enum
	{
		eReliveOriginNon,//ֻ�� ԭ�ظ���
		eReliveOriginAllHpMp,//ԭ�ظ���HPMPȫ��
	};

    // ������Ϸ������Ⱦ���أ��ɲɼ���ƷĬ�϶���ʾ
    enum EPlayerRenderFlag
    {
        EPRF_ME     = 1,                                    // ֻ��Ⱦ�Լ�
        EPRF_TEAM   = 1<<1,                                 // ��Ⱦ����
        EPRF_FRIEND = 1<<2,                                 // ��Ⱦ����
        EPRF_NPC    = 1<<3,                                 // ��ȾNPC
        EPRF_MONSTER= 1<<4,                                 // ��Ⱦ����
        EPRF_OTHERS = 1<<5,                                 // ��Ⱦ�������
		EPRF_TARGET = 1<<6,									// ��Ⱦѡ��Ŀ��

		EPRF_AMITY = 1<<7,									// �Ѻõ���� ��Ŀǰֻ��Ա�����ң�
		EPRF_ANTAGONIZE = 1<<8,								// �жԵ���� ��Ŀǰֻ��ԷǱ�������ң�
        EPRF_ALL    = EPRF_ME | EPRF_TEAM | EPRF_FRIEND | EPRF_NPC | EPRF_MONSTER | EPRF_TARGET | EPRF_OTHERS | EPRF_AMITY | EPRF_ANTAGONIZE,  // ȫ����Ⱦ
    };

	enum
	{
		eRemoveAny			= 1<<0,
		eRemoveExceptMe		= 1<<1,
	};

	enum
	{
		eExceptMe		=	1<<1,		// �ų���
		eExceptFriend	=	1<<2,		// �ų�����
		eExceptItem		=	1<<3,		// �ų�����
	};

	////////////////////////////////////////////////////////////////
	//��Ա����
public:
	DWORD		m_dwGamePing;			//��Ϸ�е�Ping

	//����Լ�
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

	// ��ǰ���ָ���Player������ID
	GameObjectId				m_shMouseTargetPlayerSeverID;
	// ����ļ���Ŀ���ID
	GameObjectId			m_SkillBufTargetID;

	// ����Ҽ�����ʱ����õ�PlayerID
	int					m_nMouseRDownTargetPlayerServerID;

	// ��ǰ���ָ���player
	GameObjectId				m_nPickId;

	// ��ǰ����
	std::map< GameObjectId, CPlayer* > m_mapPlayers;
	// ��ǰ�������������
	// ��see attack��֪����һᱻɱ����һ���ǣ�
	// ���뵽m_vectorDieingPlayers��
	std::vector< CPlayer* > m_vectorDeathPlayer;
	
	//  [1/7/2011 zhangjiayi]
	// ���ڴ�ŷ��߼��Ե�ģ��(����baseproperty��)
	std::vector< CPlayer* > m_vectorNoLogicPlayer;

	// ��Ҵӽ���Զ���У���������������������ж���Ⱦ����˳��
	// 20���ڣ�������ʾ���ѣ�NPC�����ѣ�Ȼ�������������
	PlayerRenderLimitData m_PlayerDistQueue[PLAYER_RENDER_QUEUE_MAX];
	int					m_nPlayerQueueCount;

	BOOL				m_bLoginSucc;

	CLagCounter			m_lag;

	bool				m_bNeedBeginDilog;	//��־Npc�Ի����Ƿ���ʾ��

	BOOL				m_bShadowColor;		//��ɫ��̬��Ӱɫ����
	
	std::vector<SNpcQuestInfo> m_vectorNpcInfo;
	std::vector<INT>	  m_vtAlphaPlayer;

	BOOL				m_bPlayMapEffect;//Only Player
	std::string			m_szPlayMapEffect;

    short sPlayerSlot; /// ���ѡ�������Ϸ�ĵڼ�����ɫ��������

	std::vector< CPlayer* > m_vecDynamicCollison;	// �ж�̬��ײЧ����NPC�б���ÿ֡������������λ�ú��ȡ
	BspTree				m_DynamicCollisionBsp;
	BspTree             m_DynamicFloorBsp;

protected:
	// ��Ⱦ����ͳ��
	int					nRenderPlayerCount;
	int					nRenderVertexCount;
	int					nRenderFaceCount;

	std::vector<MsgNPCEnterMySight> PendingSawNPC;
	std::vector<MsgPlayerEnterMySight> PendingSawPlayer;
	DWORD				m_nSawPlayerNPCCostTime;	// ����������Һ�NPC�������ʱ����ģ�����LOAD_PLAYER_NPC_MAX_TIME�����������֡��������

    unsigned int		m_nPlayerRenderFlag;
	unsigned int		m_nLastPlayerRenderFlag;
    BOOL				m_bTurnRoleToCamera;

    BOOL				m_bUseSkillBuf;
	D3DXVECTOR3			m_vFrom;
	D3DXVECTOR3			m_vDir;

    DWORD				m_dwLastUpdateNpcActionTime;  // �ϴθ���NPC���ж���ʱ�䣬ÿ1�����һ��

    BOOL m_bCanReceivePlayerMsg;    // ���ص�ͼʱ�����ò�������ҽ���/�뿪��Ұ�����ƶ���Ϣ

    DWORD m_dwLastReqScriptTime; // ����ű���Ϣ����1��CD������:MsgReqScript(����ű�)��MsgScriptAckShowQuestDlg(��������)��MsgAbandonTask����������

	std::map<std::string, GameObjectId> m_mapVipPlayer;

	bool m_bNeedUpdateRoleUI;

	bool                m_bClickTheTerrain;
	bool                m_bRelivedByPlayer;
	FLOAT				m_fFarRole;
	int					m_nPlayerRenderLimit;	// ͬ����������
	///////////////////////////////////////////////////////////////////////
	//��Ա����
public:
	void				OnSeeIntonate(int iSkill, int iSkillLevel, GameObjectId ScNPcID, GameObjectId TagNpcID, int iPercent, unsigned short usType );
	void				OnSeeHoldSkill( int iSkill,int iSkillLevel,GameObjectId iSrcChar,int iPercent );
	//
	//void				OnSeeExpression(short stNpcID, short stActionID);					// ɾ���ɱ��鶯������
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
	void				DisHitch();		//�½�ͨ����
	void				DisDrome();		//����	
	void				ChangeDrome( short nId );
	void				LockMe();
	CPlayer*			FindNearItemNpc(void);
	BOOL				CheckViewPlayerBBox( Vector &vDir ,float fMaxDis);

	void                SetReLivedByPlayer(bool bIs){m_bRelivedByPlayer = bIs;}
    bool                IsRelivedByPlayer() { return m_bRelivedByPlayer; }
	FLOAT				GetFarRole()		{ return m_fFarRole; }
	VOID				SetFarRole(FLOAT fRole)		{ if( fRole > 0 ) m_fFarRole = fRole; }	// ȡ����Ⱦ��������
	
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

	// ������ͬID
	int					FindSameID( GameObjectId stID );

	// ���ݷ�������Id����Player
	CPlayer*			FindByID( GameObjectId	stID );
	// �������ݿ��еĽ�ɫID����Player
	CPlayer*			FindPlayerByCharacterID( DWORD dwCharacterID );

	// ���ݿͻ��˵�Id����Player
	CPlayer*			FindByClientID( int nID );
	// ���ݷ���˵�Id�����������в���Player
	CPlayer*			FindByServerIDInDeath( GameObjectId shID );
	// ���ݿͻ��˵�Id�����������в���Player
	CPlayer*			FindByClientIDInDeath( GameObjectId nID );
	
	// ����Player
	void					AddNoLogicPlayer( CPlayer* pPlayer );
	void					ClearNoLogicPlayer( CPlayer* pPlayer );
	CPlayer*			AddPlayer( GameObjectId stID,int iCharType, bool bIsMe = false );
	BOOL				PlayerExit( GameObjectId stId );
	BOOL				RemovePlayerFromActiveList( GameObjectId stId, DWORD dwFlag = 0);
	BOOL				RemovePlayerFromActiveList( CPlayer* pPlayer, DWORD dwFlag = 0 );
	BOOL				AddPlayerToKeepList( CPlayer* pPlayer, BOOL bFast = FALSE );    //bFast = TRUE, ��Ҫ������ʧ
	BOOL				DeleteDeathPlayer( CPlayer* pPlayer );
	void				DeletePlayersExceptMe();
	void				ReqRelive( bool bBornCity,bool bBySkill = false,short stOriginRelieveType = -1,BYTE byAddtion=0);
	GameObjectId				GetMouseTargetPlayerSeverID(){ return m_shMouseTargetPlayerSeverID; }
	GameObjectId     			GetLockPlayerID(){return m_controldata.LockNpcID;}
	void    			SetLockPlayerID(GameObjectId npc_id);
	void				RequestGetOnOtherPet( CPlayer* pPlayer ); //�������ϱ��˵ĳ���
	void				SetCurUseSkill(int skill, int level = 0){m_controldata.iUseSkill = skill, m_controldata.iUseSkillLevel = level;};
	int 				GetCurUseSkill(void){return m_controldata.iUseSkill;}
	int 				GetCurUseSkillLevel(void){return m_controldata.iUseSkillLevel;}

	// �����Ӧ -->�����ƶ�ָ��
	void				TurnRoleTo( CPlayer* pTargetPlayer );
	bool				MoveRoleToNPC(const NpcCoordInfo* pInfo);
	bool				MoveRoleTo( float x, float y, bool bNeedShowTargetPoint = true ,bool bSync = false, bool bHideTargetPoint = true,bool bUseZ = false);

	bool				ProcessShift(  float x, float y );
	void				HideTargetPointEffect();
	void				MoveRoleToPlayer( CPlayer* pTargetPlayer, BOOL bClose = TRUE, float fCorrect = 0.0f, BOOL bPick = FALSE ,BOOL bInRuning = FALSE, BOOL bCalibrate = FALSE );
	// �ո����Ӧ -->��������ָ��
	void				UseSpecialSkill();
	void				ReadytoUseSpecialSkill();
	// �Ҽ���Ӧ -->��������ָ��
	void				RoleAttackToDead(int tag_player_id, int x, int y, int skill_id, int skill_level = 1);
	void				RoleAttack(int tag_player_id, int x, int y, int skill_id, int skill_level = 1,
						bool bAttackToDead = false,bool bHoldAttack = false );

	//����ʹ�ü���
	void				RoleUseSkill( int nTag_Player_ID, int x, int y, int nSkill_ID, int nSkill_Level );
	//
	void				UseRecordSkillAttackToDead(void);
	void				UseRecordSkill(void);
	//
	void	            RoleIdle(short x, short y);//����
	void				RoleChangeDir(short x, short y);//ת��
	void				ClearRoleGetRangeItem(void);	//��npc���Ƶ�npc�´�ָ�ȡ����Χ�ĵ���
	void				RoleDropItem(short x, short y);	//��npc���Ƶ�npc�´�ָ���������ϵĵ���
	void				RoleDoAction(int ActionID);		//��npc���Ƶ�npc�´�ָ���ĳ�����鶯��

	CPlayer*			FindByPt( int x, int y );
	CPlayer*			FindByName( const char*szName );

	void				Destroy();

	void				RenderPlayer( LPDIRECT3DDEVICE9 pDevice,int iPlayerID );

	//������Ϣ
	bool				ProcessMsg( Msg* pMsg );

	const BOOL			GetLoginSuccess() const	{ return m_bLoginSucc; }

	void				SetLoginSuccess( const BOOL b )	{ m_bLoginSucc = b; }
	//�Ƿ�Ӧ�û���Ѫ��
	bool				WillHPShow( GameObjectId nIDWho );
	//ȡ��ϵͳ��PING.
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

	//--��������ѡ����գ����б�
	void				CleaNpcInfos()	{ m_vectorNpcInfo.clear(); }

	// ���ͳ�������
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

	//�Ϳ�����صĺ���
	BOOL    MouseShortCutClear(void);//��տ�ݷ�ʽ
	BOOL	MouseControlFunction( float x, float y, int type, int xMouse, int yMouse, bool bPicked ); //�����Ƶ����
	BOOL	KeyboardControlFunction(int type, BOOL bDxInput=FALSE);
	BOOL	KeyboardKeyUpControlFunction(int type, BOOL bDxInput=FALSE);
	BOOL	BreakInputMessage( DWORD dwType );
 	BOOL	ControlLButDownProc( float x, float y, bool bPicked );
	BOOL	ControlLButUpProc( float x, float y, bool bPicked );

	void    UseSilllToSelectPoint();

	void	OnClickNon_object( float x, float y );
	void	BeginDialog(float xDst,float yDst);
	BOOL    ControlRButDownProc(int x, int y);  //�Ҽ�����
	BOOL    ControlRButUpProc(int x, int y);  

	BOOL    ControlHotKeyProc(int HotKeyIdnex); //���ȼ��Ĵ���
	BOOL	AutoControlClear(void);				//����Զ����Ƶ�һЩ��־
	BOOL    AutoLockAttacker(int AttackerID);				//	�Զ����������Լ���npc
	//
	BOOL	AutoSkillProc(void);				//�ƶ�ʹ�ü��ܵĴ���
	//��Ping��Ϣ��������
	BOOL	PingServer(void);
	// ����Ƿ���ҵĸ����̵�
	BOOL	CheckPrivateShop( int x, int y );

	void	SwitchScabbard();

	DWORD	GetQuestRankColor( SQuest* pQuest);

	// ���ͽ�ɫ�γ���������Ϣ
	void	SendDrawWeapon();

	// ���ͽ�ɫ������������Ϣ
	void	SendDrawInWeapon();

	void	ProcessPendingSawPlayerNPC();					// ÿ֡�ڴ���Net messageǰ���ã�������֡δ�����������
	void	PreloadMapMonsterAndNpc(const char* szMapName);	// Ԥ���ص�ͼ�Ĺ���ģ��

	void    SetPlayerRenderFlag(unsigned int _flag){m_nPlayerRenderFlag = _flag;}
    void	AddPlayerRenderFlag(unsigned int flag) { m_nPlayerRenderFlag |= flag; }
    void	RemovePlayerRenderFlag(unsigned int flag) { m_nPlayerRenderFlag &= ~flag; }
    BOOL	IsPlayerTypeRender(unsigned int flag) { return m_nPlayerRenderFlag & flag; }
    void	SetPlayerRenderPriority(unsigned short pri);
    void	TogglePlayerRenderPriority();
    unsigned short GetPlayerRenderFlag() { return m_nPlayerRenderFlag; }
    BOOL	IsPlayerCanRender(CPlayer* pPlayer, BOOL bDist = FALSE);   // bDist = TRUE���Ƿ���PLAYER_RENDER_DIST_MIN��Χ���ж�
	BOOL    IsPlayerCanRenderEX(CPlayer* pPlayer, BOOL bDist = FALSE);
	/*
	 * 2012.6.25 wangshuai
	 * ���2���ӿ�, ����ģ�����ͻָ��Ĺ���, �ֱ���Suspend/Resume
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

    /** ȡ�������Ϊ
    */
    bool    cancelBehavior();

	void	ClearPlayerQueue()
	{ 		// �����Ⱦ����
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

	// ����NPC�Ի��б���ͷ���ֶ�
	short ProcessExpHead(const char* szText, std::string& strRet);

protected:
		// ��������Ƶ��ʱ��(����)
	static DWORD ms_dwUpdateAnimTimeStep;
public:
	void SetUpdateAnimTimeStep( DWORD dwTime ){ ms_dwUpdateAnimTimeStep = dwTime; }
	DWORD GetUpdateAnimTimeStep() { return ms_dwUpdateAnimTimeStep; }

protected:	
	//����һ����
	CPlayer* SawOneNPC( Msg *pMsg );
	CPlayer* SawOnePlayer( Msg *pMsg );

	void DestroyPlayer( CPlayer *pPlayer );

	bool CreateDynamicCollision(CPlayer* pPlayer);

	// ���ͽ�ɫ����Ծ��Ϣ
	void SendJumpMsg();

	// �ڴ治������£���Ҳ�����Ұ�ڣ��������ǳ���30�ף��������һ����Ⱦ����5�룬���ͷŶ������ݣ������ڴ�ѹ��
	void CheckDestroyAnimLowMemory(CPlayer* pPlayer);
	void ResetDestroyAnimNum(){ m_iDestroyCharLimitPerFrame = 3; }	// ÿ֡��CheckDestroyAnimLowMemoryǰ����
	short m_iDestroyCharLimitPerFrame;

	void	AttackPlayer( CPlayer* pPlayer );

	//��Ϣ����
	/////////////////////////////////////////////////////////////////
public:
	//�� �̳ǻ��ֹ����̳ǵ�
	void OnMsgRMBConsumeScoreChange(Msg* pMsg); 
	void OnMsgRMBGoldChange( Msg* pMsg );
	void OnAckGlodCovSilver( Msg* pMsg );
	void OnRetResetTime( Msg* pMsg );
	//���ܵ�����Idle��״̬����Ϣ
	void OnMsgChangeSubAction(Msg* pMsg);
	// ���յ�ȷ���ƶ�ָ��
	void OnMsgAckMove( Msg* pMsg );

	// ���յ���NPC�����ҵ���Ұ(�����ƶ�״̬��)
	void OnMsgNPCEnterMySightMovingAStep( Msg* pMsg );

	// ���յ���Player�����ҵ���Ұ
	void OnMsgPlayerEnterMySight( Msg* pMsg, BOOL bCheckLoadingCost = TRUE );
	// ���յ���Player�����ҵ���Ұ(�����ƶ�״̬��)
	void OnMsgPlayerEnterMySightMovingAStep( Msg* pMsg );

    //���յ���Player������Ұ�İ�
    void OnMsgPlayerEnterMySightPack(Msg* pMsg);
	// ���յ���NPC�����ҵ���Ұ
	void OnMsgNPCEnterMySight( Msg* pMsg, BOOL bCheckLoadingCost = TRUE );    

	// ���յ��ı��������Ϣ
	void OnMsgChangeDrome( Msg* pMsg );

	// ���յ���Ʒ�����ҵ���Ұ
	void OnMsgItemEnterMySight( Msg* pMsg );
	// ���յ���ɫ�뿪�ҵ���Ұ(������Ʒ)
	void OnMsgExitMySight( Msg* pMsg );
	// ���յ�ĳ���ƶ����������Ϣ
	void OnMsgMoveToTarget( Msg* pMsg );
	// ���յ���ɫ����ʾ����
	void OnMsgAckDisplayName( Msg* pMsg );
	// ֪ͨ����Ա���Ա��
	void OnMsgGuildMemberValueChange( Msg* pMsg );
	// ���յ���ҹ�����Ϣ
	void OnMsgCharGuildInfo( Msg* pMsg );
	// ���յ���ɫ��ѯ����
	void OnMsgAckCharInfo( Msg* pMsg );
	// ���յ��˳�ָ��( ʲô�˳�����ʲô�˳���)
	void OnMsgExit( Msg* pMsg );
	// ���յ�ȷ�Ϲ�����Ϣ
	void OnMsgAckAttack( Msg* pMsg );
	// ���յ�������Ϸ����(?!)
	void OnMsgAckAllGameProperty( Msg* pMsg );
	// ���յ��л���ͼ��Ϣ
	void OnMsgChangeMap( Msg* pMsg );
	// ���յ�������Ϣ               
	void OnMsgChat( Msg* pMsg );
	// ���յ��¼���Χ(�����¼���Χ�����ڿͻ��˱��ֶ���)
	void OnMsgEventRange( Msg* pMsg );
	// ���յ����������ӳٵ���Ϣ
	void OnMsgGetLag( Msg* pMsg );
	// ���յ�ĳ�˵�������Ϣ     
	void OnMsgCharLevelUp( Msg* pMsg );
	// ���յ�ĳ���������
	void OnMsgDoneQuest( Msg* pMsg );
	// ���յ�ĳ�˵ļ���������Ϣ     
	void OnMsgCharSkillLevelUp( Msg* pMsg ); 
	//������ɫ���ϳ��ַ���Ч��
	void OnMsgCharShowEff( Msg* pMsg );    

	// ���յ�ˢ�½�ɫ��Ϣ
	void OnMsgRefreshChar( Msg* pMsg );
	// ���յ����Ǯ����Ϣ
	//void OnMsgGetMoney( Msg* pMsg );
	// ���յ��ı乫����Ϣ
	void OnMsgChangeGuild( Msg* pMsg );

	// ������ҵ���Ծ��Ϣ
	void OnMsgRecevingJump( Msg* pMsg );

	// ���յ���Ұγ���������Ϣ
	void OnMsgRecevingDrawWeapon( Msg* pMsg );

	// ���յ����������������Ϣ
	void OnMsgRecevingDrawInWeapon( Msg* pMsg );

	// ���ܵ�������ʾ��Ϣ
	void OnMsgUseSkillHintMessage( Msg* pMsg );

	// ���յ�����ĳ��Player��������Ϣ
	void OnMsgSawPlayerDead( Msg* pMsg );

	// ���յ������ƶ���Ϣ
	void OnMsgMoveAStep( Msg* pMsg );

	// ���ܵ�����ҽ�ɫ������Ŀ��
	void OnMsgUnPlayerClosingToLockTarget( Msg* pMsg );

	// ���յ�������ƶ�����Ϣ
	void OnMsgUnPlayerMovingToPos( Msg* pMsg );

	// ���յ�����ҽ����������Ϣ
	void OnMsgUnPlayerVerifyPos( Msg* pMsg );

	// ���յ���ҽ����������Ϣ
	void OnMsgPlayerVerifyPos( Msg* pMsg );

	//// ���յ������ƶ�����Ϣ
	//void OnMsgPlayerMoving( Msg* pMsg );

	// ���յ��ƶ������λ�øı����Ϣ
	void OnMsgPlayerMovingPos( Msg* pMsg );

	// ���յ��ƶ������λ�úͳ���ı����Ϣ
	void OnMsgPlayerMovingPosAndDir( Msg* pMsg );

	// ���յ��ƶ������λ�úͳ���ı����Ϣ���Զ�Ѱ·
	void OnMsgPlayerMovingPosAndDir_TargetDir( Msg* pMsg );

	// ���յ�ԭ�ز�����ҵ�λ����Ϣ
	void OnMsgPlayerPos( Msg* pMsg );

	// ���յ�ԭ�ز�����ҵĳ�����Ϣ
	void OnMsgPlayerDir( Msg* pMsg );

	// ���յ�ԭ�ز�����ҵ�λ�úͳ�����Ϣ
	void OnMsgPlayerPosAndDir( Msg* pMsg );

	// ���յ�����ƶ�����Ϣ��
	void OnMsgPosChange( Msg* pMsg );

	// ���յ�����ƶ�Ҫ�ƶ���Ŀ���
	void OnMsgHitchMoveTargetPos( Msg* pMsg );

	// ���յ�����ܷ���Ƶ��ƶ�����Ϣ
	void OnMsgCanControlMoving( Msg* pMsg );

	// ���յ��������������Ƿ�����ƶ���״̬
	void OnMsgPermitMove( Msg* pMsg );
	// ���յ�λ��ȷ����Ϣ
	void OnMsgVerifyPos( Msg* pMsg );    
	//����ͬ��
	void OnMsgSyncPos( Msg* pMsg );
	// ���յ��ӵ���Ʒ����Ϣ
	void OnMsgRemoveSomething(Msg* pMsg);
	// ���յ�ʹ����Ʒ����Ϣ
	void OnMsgRemoveItem(Msg* pMsg);
	// ���յ�����鿴��Ʒ����Ϣ
	void OnMsgGetShop(Msg* pMsg);
	// ���յ��򶫶�����Ϣ
	void OnAckMsgBuyOrSellGoods(Msg* pMsg);
	//// ���յ����Ը�����Ϣ
	void OnMsgAttrChanged(Msg* pMsg);
	// ���յ�����������Ϣ
	void OnMsgAttrLevelUp(Msg* pMsg);
	// ���ܵ����÷�ʯ��Ϣ
	void OnMsgPlaceStone( Msg* pMsg );
	// ���ܵ��Ƴ���ʯ��Ϣ
	void OnMsgRemoveStone( Msg* pMsg );
	// ���ܵ�������ʽƬ����Ϣ
	void OnMsgPlaceSubSkill( Msg* pMsg );
	// ���ܵ��Ƴ���ʽƬ����Ϣ
	void OnMsgRemoveSubSkill( Msg* pMsg );
	// ���ܵ�������Ʒ����Ϣ
	void OnMsgProduceItem( Msg* pMsg );
	//
	//����һ��Ч��������Ұ
	void OnMsgEffectEnterMySight( Msg *pMsg );
	void OnMsgBuildingEnterMySight( Msg *pMsg );

	//�յ��·��ĳ�����ħ��Ч�����˺�
	void OnMsgDamageOfEffect( Msg *pMsg );
	//	���������ܵ����˺�
	void OnMsgSeeDamage( Msg *pMsg );
	//�յ��·��Ŀ�����������Ϣ
	void OnMsgSeeAttack( Msg *pMsg );
	//�յ��·��Ŀ�����Ч��ʩ�ż��ܵ���Ϣ
	void OnMsgSeeCastInefficacySkill( Msg *pMsg );
	//������ս���ش�
	void OnMsgAckAttack3( Msg *pMsg );
	//�����������ʳ�
	void OnMsgSeeIntonate(Msg *pMsg);
	//��ʼ����
	void OnMsgIntonateStart(Msg *pMsg);
	//��������
    void OnMsgIntonateEnd(Msg *pMsg);
	//�����ж�
	void OnMsgIntonateInterrupt(Msg* pMsg=NULL);

	void OnMsgHoldSkillEnd(Msg*pMsg);
	void OnMsgSkillCanceled( Msg* pMsg );
	void OnMsgSkillStatus(Msg*pMsg);
	//	���������������鶯��
	void OnMsgSeeExpression(Msg*pMsg);
	//���յ�װ��������Ϣ
	void OnMsgEquipChanged2( Msg* pMsg );
	//���ص�����Ʒ
	void OnMsgAckDropItem2( Msg*pMsg );
	//
	void OnMsgEquip( Msg* pMsg );
	//--���½�ɫ����������
	void OnMsgUpdateBag( Msg*pMsg );
	//���¿��
	void OnMsgUpdateShortCutBag( Msg*pMsg );
	//����player����װ���ĵ���
	void OnMsgUpdateVisualEquip(Msg* pMsg);
	//����player����װ��������
	void OnMsgUpdateEquipData( Msg* pMsg );
	//�õ���Ʒ
	void OnMsgGetItem2( Msg*pMsg );
	// Ǯ�仯��
	void OnMsgMoneyChange( Msg* pMsg );
	//ĳ�˵�ͼ�������
	void OnMsgMapLoaded( Msg*pMsg );
	//����ĳ�˵�Ѫ��
	void OnMsgAckHPInfo( Msg *pMsg );
	//------- �������    (   at 2004-2-19)
	void OnMsgAddMissionIntro( Msg* pMsg );
	//------- ��������    (   at 2004-2-19)
	void OnMsgDelMissionIntro( Msg* pMsg );
	// ����ĳ��������
	void OnMsgSeeAction( Msg* pMsg );
	// show image
	void OnMsgScriptShow( Msg* pMsg );

	//���յ���ɫ��Ϣ
	void OnMsgAckGetPlayerInfo(Msg * pMsg);

	//����������
	void OnMsgAckFriendLeave(Msg * pMsg);
	//�յ����������ͻ�����Ping��Ϣ
	void OnMsgPing(Msg * pMsg);
	//վ�� ״̬�л�
	void	OnMsgSitStatusChange(Msg * pMsg);
	//ս��״̬�л�
	void	OnMsgFightStatusChange(Msg * pMsg);
	//���յ����ڶ��齨���������Ϣ
	void	OnMsgCreateTeam(Msg* pMsg);
	//���յ����˼���������Ϣ
	void	OnMsgJoinTeam(Msg* pMsg);
	//��Ա������
	void	OnMsgTeamOutLine(Msg* pMsg);
	//���յ�����ģ���Ϣ
	void	OnMsgTeamInfo(Msg* pMsg);
	//���˼������
	void	OnMsgAddTeamMember(Msg* pMsg);
	//�����˳��˶���
	void	OnMsgDeleteAMember(Msg* pMsg);
	//�Լ��뿪�˶���
	void	OnMsgExitTeam(Msg* pMsg);//
	//����С��
	void	OnChangeManipleFromTeamRet(Msg* pMsg);
	//����С�Ӷӳ���ʶ
	void	OnRetFlagHeaderFromTeam(Msg* pMsg);
	//ˢ�¹�ϵ
	void	OnRefreshSocialty(Msg* pMsg);

	//��������Ϣ������ָ�����ӵ���Ʒ������
	void	OnMsgCloseItemFormIdx(Msg *pMsg);
	

	//�������ģʽ2��������Ʒ��ʾ��ȡ���߷���
	void	OnMsgAssign_Item_Team(Msg* pMsg );
	void	OnMsgTeamMemberAck(Msg* pMsg);
	//ѯ�ʶӳ�
	void	OnMsgInquireTeamHeader(Msg* pMsg);
	void	OnMsgAddTeamCancel( Msg* pMsg );
	void	OnMsgChange_AssignMode( Msg* pMsg );
	void	OnMsgChange_AssignMode_Result( Msg* pMsg );

	//ѯ�ʱ�������
	void	OnMsgInquireInvitee(Msg* pMsg);
	//	����npc���ϵ�ս��״̬
	void	OnMsgUpdateCharacterBodyStatus(Msg* pMsg);
	//	���npc���ϵ�ս��״̬
	void	OnMsgClearBodyStatus(Msg* pMsg);
	//	������������ת�����Ϣ
	void	OnMsgChangeDir(Msg* pMsg);
	//HP��MP�ĸı�
	void	OnMsgHPMPModify(Msg* pMsg);
	void	OnMsgFirstEvent(Msg* pMsg);
	void	OnMsgGetGuildIcon(Msg* pMsg);
	void	OnMsgGetReputeName(Msg* pMsg);
	void	OnMsgInviteAddRelationAck(Msg* pMsg);
	void	OnMsgGuildIconUIOpen(Msg* pMsg);
	//����״̬
	void	OnMsgBuildStatus( Msg* pMsg );
	void	OnMsgBuildDestroyed( Msg *pMsg );
	void	OnMsgBuildSelfDestroyed( Msg *pMsg );
	void	OnMsgBuildFailed( Msg *pMsg );

	
	void	OnMsgGuildAckDismiss( Msg* pMsg );
	void	OnMsgGuildMemberOnline( Msg* pMsg );
	//-------------------------------------------------------------------------------------------------------------
	//���
	void	OnMsgGuildAckCreateNotice(Msg*);// ��Ӧ���󴴽�����
	void OnMsgFamilyNameChangeNotice(Msg*); //�޸ļ��������ص���ʾ
	void OnMsgGuildTanHeNotice( Msg*);// ���뵯������notice
	void OnMsgGuildOfferbuildNotice(Msg*);// ��Ӧ�ﹱ����notice
	void OnMsgGuildReleaseNotice(Msg*);//�����ͻ��˷�������notice
	void OnMsgGuildDiabandTime(Msg*);// ��ʾ������Ὣ��ĳ���ڽ�ɢ
	void OnMsgGuildDutyStatus(Msg*);// ֪ͨ�ͻ��˰������񷢲�״̬
	void OnMsgGuildDonate(Msg*);// ����ļ��������ͻ���
    void OnMsgFamilyNameChange( Msg*); //�޸ļ�����
	void OnMsgUpdateMemberData(Msg*);//���Ա��Ϣ�ı�
	void OnMsgUpDateGuildData(Msg*);//�����Ϣ�ı�
	void OnMsgAddGuildMember(Msg*);//֪ͨ����Ա�����˼���
	void OnMsgSomeOneJoinGuild(Msg*);// ֪ͨ�������ĳ�˼��������
	void OnMsgSomeOneLeaveGuild(Msg*);// ֪ͨ�������ĳ���뿪������
	void OnMsgDelGuildMember(Msg*);//֪ͨ����Ա�������뿪
	void MeLeaveGuild();
	void OnMsgGuildMemberLeave( Msg* pMsg );//���뿪���
	void OnMsgJoinGuildNotice( Msg* pMsg );// ��Ӧ����������notice
	void OnMsgReciveGuildList(Msg*);//�ͻ��˽������а����б�
	void OnMsgGuildDelateResult(Msg*);//�������
	void OnMsgAddNewGuild(Msg*);//���°��ɴ���
	void OnMsgFamilyChangeNotice(Msg*);// ��������Ӧ�޸ļ���
	void OnMsgGuildAssignPositionNotice(Msg*);//ְλ����notice
	void OnMsgGuildTransferAck(Msg*); //�ظ�ת��ְλ
	void OnMsgRemoveGuildMemberNotice(Msg*);//���˳���notice
	void OnMsgGuildCreateNotice(Msg*);//��������notice
	void OnMsgGuildLevelUpNotice(Msg*);// �������������Ϣ
	void OnMsgGuildDisband(Msg*);// ֪ͨ�ͻ��˰��ɽ�ɢ��
	void OnMsgGuildShopLevelUpNotice(Msg*);// ���������̵꼤����Ϣ
	void OnMsgGuildBuyItemNotice( Msg*);//����̵������Ļ���
	void OnMsgGuildMemberMoveNotice(Msg* pMsg);//ת�ư���notice
	void OnMsgInviteGuildNotice(Msg*);// ��Ӧ����������notice
	void OnMsgGuildMasterConvent(Msg*);// �����ټ����� ��ĳ����ͼ
	void OnMsgResetGuildMemberActive(Msg*);// ֪ͨ�����г�Ա���ܻ�Ծ�����õ�����, ��������ܵĻ�Ծ��
	void OnMsgStudentLevelUp(Msg*);//ͽ��������ʦ����������
	void	OnMsgGuildReqInvite( Msg* pMsg );
	void OnMsgApplyJoinGuild(Msg*);//��Ӧ����������
	void ShowGuildInfo(const char*);
	//-------------------------------------------------------------------------------------------------------------
	/*���ս*/
	void OnMsgFlyToCampBattleReq(Msg*);// ������֪ͨ�ͻ����Ƿ�Ҫ���������Ӫս��
	void OnMsgGetCampBattleInfo(Msg*);// ��Ӫս����ɱ����Ϣ
	void OnMsgGetMyFightCampType(Msg*);// ֪ͨ�ͻ�����Ӫ��Ϣ
	void OnMsgShowCampGuildBattleEnter(Msg*);// ��ʾ��������ս���봰��
	void OnMsgEnterCampBattleNotice(Msg*);//����ս���������notice
	void OnMsgGetGuildBattleResult(Msg*);//֪ͨ��������ս���
	void OnMsgCampBattleSignNotice(Msg*);//�����������notice
	void OnMsgGuildBattleStatus(Msg*);// ֪ͨ��Ӫս��״̬
	void OnMsgGuildFightInfo(Msg*);// ֪ͨ��Ӫս��ɱ��
	void OnMsgGetCampBattleResource(Msg*);// ͬ��ս����Դ��
	void OnMsgSignGuildCampBattleFailed(Msg*);// ֪ͨ����, ��İ������һ������û��ƥ����, ���ܲμӰ�������ս
	void OnMsgGetGuildCampBattleMatch(Msg*);// ֪ͨ��Ӫս�������б�
	void OnMsgKillCampBattleMonster(Msg*);// ս��ɱ������
	void OnMsgCampBattleSignUpReplace(Msg*);// ֪ͨ���ɰ���, ��ı����б��������ɶ�����
	void OnMsgCampGuildMonsterRefresh(Msg*);// ֪ͨս�������, ĳĳ��ˢ������
	void ShowGuildBattleInfo(const char* szText);

	void OnMsgCountryBattleGuild(Msg*);// ȫ���㲥ĳ�����ɻ����ս���ʸ�
	void OnMsgCountryBattleResult(Msg*);// ֪ͨ����ս�����
	void OnMsgCountryBattlePlayerCount(Msg*);// ����ս����Ա����, �Լ������������� ( �췽�������޷�, �����������޷� )
	void OnMsgTellCampBattleDeathCount(Msg*);//��ǰ����������
	/*void ShowCampBattleInfo(const char* szText);*/
	//-------------------------------------------------------------------------------------------------------------
	//void	OnMsgGuildMemberDismiss( Msg* pMsg );// �����ȥ����ְ��
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

	// ֪ͨ�ͻ������ĳ�ֹ�ϵ��ʣ��ʱ��
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

	// ����
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

	// --�������--Luo
	void	OnMsgAckGuildList( Msg* pMsg);

    void    OnMsgUpdateGuildInfo( Msg* pMsg );
    void    OnMsgAckGuildIcon( Msg* pMsg );
    void    OnMsgAckGuildRelationChanged( Msg* pMsg );
    void    OnMsgInviteLeague( Msg* pMsg );

	//ʦͽ
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

	//-------����---------------------
	void	OnMsgAckScript(Msg* pMsg);
	void	OnMsgAckResult( Msg* pMsg );
	void	OnMsgScriptEnd( Msg* pMsg );
	//-------����ָ��-----------------
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
	// added, jiayi, [2009/9/21], �ƺ�
	////////////////////////////////////////
	//// �ƺ�
	void	OnMsgTellCurrentTitle( Msg* pMsg );
	void	OnMsgTellTitleList( Msg* pMsg );
	void	OnMsgAddTitleAck( Msg* pMsg );
	void	OnMsgRemoveTitleAck( Msg* pMsg );

	void	OnMsgMapInfoReady( Msg* pMsg );

	////////////////////////////////////////
	//// �䷽
	void	OnMsgAddRecipeAck( Msg* pMsg );

    // ʰȡ��������Ʒ����
    void    OnMsgTellPackageAccess( Msg* pMsg );
    void    OnMsgPackageViewAck( Msg* pMsg );
    void    OnMsgPickPackageItemAck( Msg* pMsg );
    void    OnMsgPackageItemBoultReq( Msg* pMsg );
    void    OnMsgPackageItemBoultNumber( Msg* pMsg );
    void    OnMsgPackageItemNeedToAssign( Msg* pMsg );
    void    OnMsgPackageItemAssignAck( Msg* pMsg );

    // ��ӷ���ģʽ
    void    OnMsgTellTeamAssignInfo( Msg* pMsg );
    void    OnMsgChangeAssignItemLevelAck( Msg* pMsg );
    void    OnMsgPackageitemAccessAck( Msg* pMsg );
    void    OnMsgTellPickPackageItem( Msg* pMsg );

    // �ֿ��Ǯ
    void    OnMsgStorageMoneyAck( Msg* pMsg );

    // ��������ʱ
    void    OnMsgEctypeStageTimeRemain( Msg* pMsg );

    // ��ռ���CD
    void    OnMsgClearSkillCollDown( Msg* pMsg );

	// ������֤��
	void	OnMsgReqGraphicCode( Msg* pMsg );

	// ��ֵ����
	void	OnMsgAccountPoint( Msg* pMsg );

	//////////////////////////////���˴󴳹�///////////////////////////////////
	// �����ͻ��ˣ���ʾ����
	void	OnMsgTellLuckReward( Msg* pMsg );
	void	OnMsgLuckRewardAck( Msg* pMsg );
	void	OnMsgLuckRewardResult( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////����//////////////////////////////////////
	void OnMsgShowTreasureBox( Msg* pMsg );
	void OnMsgTreasureBoxResult( Msg* pMsg );
	void OnMsgTreasureBoxAck( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////�ƹ�����//////////////////////////////////
	void OnMsgResetPubQuestAck( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////

	void OnMsgTellGameStage( Msg* pMsg );

	////////////////////////////////����//////////////////////////////////////
	void OnMsgMoveStarAck( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////��������//////////////////////////////////
	void OnMsgSpecialRepairItemAck( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////װ������//////////////////////////////////
	void OnMsgEquipUpdateItemAck( Msg* pMsg );
	//////////////////////////////////////////////////////////////////////////
    /** ʹ���ػ���ʹ
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

    // �����Ʒ�����������
    void    OnMsgMoveGoodsAck(Msg* pMsg);

	// ������Ʒ����
	void    OnMsgLockItemAck(Msg* pMsg);
	// ������Ʒ����
    void    OnMsgUnLockItemAck(Msg* pMsg);

	// ��Ʒ����
	void    OnMsgCheckUnLockItemAck( Msg* pMsg );

	// �����
	void	OnMsgCheckCheatReq( Msg* pMsg );
	void	OnMsgGetProcessListReq( Msg* pMsg );

	// ��ȡ����ʱ����
	void	OnMsgOnLineRewardAck( Msg* pMsg );
	void    OnMsgTellTurenReward(Msg* pMsg);
	

	// �Ӳֿ��ƶ�ռ���ֶѵ�����Ʒ�����������������°����и���ƷGUID
	void	OnMsgMoveStorageItemAck( Msg* pMsg );

	// �ع�
	void	OnMsgBuyBackItemAck( Msg* pMsg );
	void	OnMsgBuyBackItemListAck( Msg* pMsg );

	// ��̨
	void    OnMsgShowBattleSignUpDlg( Msg* pMsg );
	void    OnMsgBattleSignUpAck( Msg* pMsg );
	void    OnMsgTellBattleSignUpCount( Msg* pMsg );

	// �ۼ�����ʱ��
	void	OnMsgWallowAbout( Msg* pMsg );

	void	OnMsgCheckSecondPassword( Msg* pMsg );
	void	OnMsgSetSecondPassword( Msg* pMsg );
	void	OnMsgClearSecondPassword( Msg* pMsg );
	void	OnMsgCheckSecondPasswordResult( Msg* pMsg );

	//�����̳�
	void	OnMsgJiFengShopItemListAck( Msg* pMsg );
	//�����̳���Ϣ
	void    OnMsgUpdateTradeShopConfig( Msg* pMsg );
	void    OnMsgTradeShopChange( Msg* pMsg );
public:
    void   OnMsgMailList(Msg* pMsg);  //���ʼ��б�
    void   OnMsgMailOnAck(Msg* pMsg);   //�ʼ�����
    void   OnMsgMailNotify(Msg* pMsg);  //���ʼ�֪ͨ
    void   OnMsgMailOpAck(Msg* pMsg);   //�ʼ���������
public:
	//����ʯ����
	void	OnMsgMoveStarLevelUpAck( Msg* pMsg );
	//���Ǳ��ǲ�������
	void	OnMsgItemComposeAck( Msg* pMsg );
	//Ԫ������
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
//------------------ɱ��--------------------------------
    void   OnMsgKillNumProcess(Msg *pMsg);          //֪ͨɱ��������
//---------------------------------------------------------

//--------------����ת��ϵͳ------------------------------
    void OnMsgFiveXingMoveAck(Msg *pMsg);
//--------------------------------------------------------
	// ʦͽ��Ϣ
	//void	OnMsgMasterReportAck(Msg* pMsg);		// ʦ��ָ����
	void	OnMsgMasterReportResult(Msg* pMsg);		// ʦ��ָ��ɹ��󷢸�ͽ����Ϣ
	//void	OnMsgPrenticeReportAck(Msg* pMsg);		// ͽ�ܻ㱨���
	//void	OnMsgPrenticeReportResult(Msg* pMsg);	// ͽ�ܻ㱨�ɹ��󷢸�ʦ����Ϣ

	//С��ս��
	void    OnMsgTellBattleRecord(Msg* pMsg);//С��ս���ɼ�
	void    OnMsgTellBattleTeamRecord(Msg* pMsg);//С��ս���ɼ�
	void    OnMsgTellBattleSignUpInfo(Msg* pMsg);//С����Ϣ
	void	OnMsgEnterTeamBattleReq(Msg* pMsg);//֪ͨ����ս��
	void	OnMsgBattleTeamInfo(Msg* pMsg);
	void	OnMsgQueryBattleSignUpTimeAck(Msg *pMsg);

	// ������������
	void	OnMsgShowViewUseItemToPlayer(Msg *pMsg);// ֪ͨ�������, ĳ�˸�ĳ��ʹ����ĳ����Ʒ( ����Χ�ڿͻ�����ʾ��Ч�� )
	void	OnMsgShowAllUseItemToPlayer(Msg *pMsg);	// ȫ������, ĳ�˸�ĳ��ʹ����ĳ��Ʒ���ٸ�

	// Э�����
	void	OnMsgDelFriendCheckReq(Msg *pMsg);		// �յ�Э���������
	void	OnMsgDelFriendCheckAck(Msg *pMsg);		// �����յ�Э�������

    //��ӽ��Ӹı�
    void   OnMsgJiaoZiChange(Msg *pMsg);            //���Ӹı���Ϣ

	// NPC����/��ʾ
	void	OnMsgTellHideStatus(Msg *pMsg);

	//������λ��
	void OnMsgTellProtectPetPos(Msg*);

    void    OnMsgMountAckBreed( Msg *pMsg );        // ����ɹ�
    void    OnMsgAckOfflineHook( Msg *pMsg );       // ��ʼ���߹һ�

//-------------------------����---------------------------       added by zhuomeng.hu		[8/25/2010]
	void OnMsgTellCountryBattleSignUp( Msg *pMsg );					    // ����ս��������ʼ
	void OnMsgTellCountryBattleEnter( Msg *pMsg );                      // ����ս����ʼ����
	void OnMsgTellCountryBattleFight( Msg *pMsg );                      // ����ս��ս����ʼ
	void OnMsgTellCounterBattleResult( Msg *pMsg );                     // ����ս������, ͨ����
	void OnMsgCountryBattleSignUpAck( Msg *pMsg );                      // ����ս����������
	void OnMsgEnterCounterBattleAck( Msg *pMsg );                       // �������ս��
	//void OnMsgQueryCountryBattleSignUpAck( Msg *pMsg );                 // ��ѯ����ս����������
	void OnMsgTellCountryTitleInfo( Msg *pMsg );                        // �㲥���ҳƺ�
//	void OnMsgQueryCountryInfoReq( Msg *pMsg );                         // �鿴������Ϣ
	void OnMsgQueryCountryInfoAck( Msg *pMsg );                         // �鿴������Ϣ
	void OnMsgTellCountryQueryStatus( Msg *pMsg );                      // ֪ͨ��������״̬
//	void OnMsgCountryNoticeChangeReq( Msg *pMsg );                      // ������Ĺ��ҹ���
	void OnMsgCountryNoticeChangeAck( Msg *pMsg );                      // ���Ĺ��ҹ������
	void OnMsgAddCountryInfoReq(Msg* pMsg);
	void OnMsgLoadCountryInfoAck(Msg* pMsg);
//	void OnMsgCountryQuestStateChangeReq( Msg *pMsg );                  // ���󷢲���������
	void OnMsgCountryQuestStateChangeAck( Msg *pMsg );                  // ���󷢲������������
//	void OnMsgCountryOfficialAppointReq( Msg *pMsg );                   // �����������ҹ�Ա
	void OnMsgCountryOfficialAppointAck( Msg *pMsg );                   // �����������ҹ�Ա����
//	void OnMsgCountryOfficialRecallReq( Msg *pMsg );                    // ����������ҹ�Ա
	void OnMsgCountryOfficialRecallAck( Msg *pMsg );                    // ������ҹ�Աְλ����
	void OnMsgCountryQuestStatusStop( Msg *pMsg );                      // ֪ͨ���ҷ������������
	void OnMsgTellCountryKillPosition( Msg *pMsg );                     // ȫ����㲥ɱ����ĳ����Ա
	void OnMsgCountryRequestRaiseReq( Msg *pMsg );                      // �ͻ�������ļ�������ʽ�
	void OnMsgCountryRequestRaiseAck( Msg *pMsg );                      // ����ļ��������������
	void OnMsgCountryRaiseToPlayerReq( Msg *pMsg );                     // ����������ļ����������, �ͻ����жϵȼ�
//	void OnMsgCountryRaiseToPlayerAck( Msg *pMsg );                     // ���ļ�����
	void OnMsgCountryRaiseTellPlayer( Msg *pMsg );                      // ֪ͨ���ļ�����
	void OnMsgCountryReceiveMountAck( Msg *pMsg );                      // ��ȡ�����������
	void OnMsgTellCountryBordersFight( Msg *pMsg );                     // ��¼���ұ���ս��������( �ͻ�Ҳ��¼, ��¼���г�����CountryConfig���� )
	void OnMsgTellCountryKillEnemy( Msg *pMsg );                        // ֪ͨ�ͻ��� ĳĳĳ���������
//	void OnMsgCountryFlyToBordersReq( Msg *pMsg );                      // ���Ҳ������������
//	void OnMsgCountryOperateToPlayerReq( Msg *pMsg );                   // �ͻ����������
	void OnMsgCountryOperateToPlayerAck( Msg *pMsg );                   // �ͻ��˲�������
	void OnMsgCountryTellOperateToPlayer( Msg *pMsg );                  // ֪ͨ�������� �㱻������
    void OnMsgTellOperateToCountry( Msg *pMsg );                        // ��ұ�����OOXX��
	void OnMsgCountryConveneResult( Msg *pMsg );                        // ��������ټ���� 
	void OnMsgCountryConveneReq( Msg *pMsg );                           // ���������ͻ����ټ�����
//	void OnMsgCountryConveneAck( Msg *pMsg );                           // �Ƿ�ͬ���ټ� ( ��ͬ�ⲻ�û���Ϣ )
	void OnMsgCountryCountryAppoint( Msg *pMsg );						// ֪ͨ���������߱���ְ
    void OnMsgTellCountryBattleGuild( Msg *pMsg );                      // ȫ���㲥ĳ�����ɻ����ս���ʸ�
    void OnMsgCountryChangeAck( Msg *pMsg );                            // �ѹ�����
    void OnMsgCountryTellCountryID( Msg *pMsg );                        // �ѹ���֪ͨ����ID
    void OnMsgCountryTellWeak( Msg *pMsg );                             // ������
	void OnMsgCountryTellStrong( Msg *pMsg );                             // ��ǿ��
    void OnMsgCountryBattleReplace( Msg *pMsg );                        // ֪ͨ���ɰ���, ��İ����ڹ�������ս�����б��������ɶ�����
    void OnMsgTellCountryName( Msg *pMsg );                             // ��ʼ������
    void OnMsgChangeCountryNameAck( Msg *pMsg );                        // ���Ĺ��Ż���
    void OnMsgTellCountryNameChange( Msg *pMsg );                       // �㲥���Ÿı�
    void OnMsgTellMassacreCountry( Msg *pMsg );                         // ����ս
    void OnMsgUpdateCountryWarFightKill( Msg *pMsg );                   // ����սɱ�˼���
    void OnMsgTellCountryPlayerRaise( Msg *pMsg );                      // ļ�蹫��
	void OnMsgUpdateCountryDate(Msg *pMsg);								// ��Ʒ���»���
	void OnMsgGuildSQACK(Msg *pMsg);		
	void OnMsgGuildAddSQ(Msg *pMsg);
	void OnMsgGuildDElSQ(Msg *pMsg);
	void OnMsgFlyMap(Msg *pMsg);
	void OnMsgTellCountryPlayerRaiseItem(Msg *pMsg);
	void OnMsgTellGuildPlayerRaiseItem(Msg *pMsg);
    //------------------------------------------------------------

	void OnMsgActionInterrupt( Msg* pMsg );								// ���������Ϣ

	//----------------------��ʷ��--------------------------------
	void OnMsgOnOffNpcShip(Msg *pMsg);

    //---------------------�µĽ���-------------------------------      added by ZhuoMeng.Hu		[12/15/2010]
    void OnMsgBargainingAck( Msg* pMsg );                               // �����������
    void OnMsgBargainingRequestReq( Msg* pMsg );                        // ֪ͨ�ͻ���, ĳ���������㽻��
    void OnMsgBargainingStart( Msg* pMsg );                             // ֪ͨ�ͻ���  ��ĳ�˵Ľ��׿�ʼ
    void OnMsgBargainingFinish( Msg* pMsg );                            // ֪ͨ�ͻ���  ���׽���
    void OnMsgBargainingStatus( Msg* pMsg );                            // ֪ͨ�ͻ��� ĳ��ҵĽ���״̬
    void OnMsgBargainingDataAck( Msg* pMsg );                           // ֪ͨ��Ҽ�������Ʒ����������
    void OnMsgShowBargainingData( Msg* pMsg );                          // ֪ͨ�Է���ҽ��׵�����
    void OnMsgRemoveBargainingDataAck( Msg* pMsg );                     // ��Ӧ�Ƴ�������Ʒ, �ͻ���ɾ����λ�õ���Ʒ
    void OnMsgBargainingDataError( Msg* pMsg );                         // ֪ͨ�ͻ��˽�����Ʒ�ĸ������             
    //------------------------------------------------------------

    //---------------------����ֿ�-------------------------------      added by ZhuoMeng.Hu		[12/17/2010]
    void OnMsgUpdateMountStorage( Msg* pMsg );                          // ����ֿ����ݸ���
    void OnMsgUpdateCharMount( Msg* pMsg );                             // ������������б����
    //------------------------------------------------------------

    //---------------------�µİ�̯-------------------------------      added by ZhuoMeng.Hu		[12/20/2010]
    void OnMsgAddSellDataAck( Msg* pMsg );                              // ���һ�����۵���Ʒ������Ϣ
    void OnMsgAddBuyDataAck( Msg* pMsg );                               // ��������չ���Ʒ�Ĵ�����Ϣ
    void OnMsgStartStallAck( Msg* pMsg );                               // ������̯�������
    void OnMsgBuyOrSellStallAck( Msg* pMsg );                           // ����������߳��۵Ĵ���
    void OnMsgUpdateStallData( Msg* pMsg );                             // ����̯λ����Ϣ���ͻ���
    void OnMsgTellStartStall( Msg* pMsg );                              // ֪ͨ�������, ĳ�˰�̯��
    void OnMsgTellCloseStall( Msg* pMsg );                              // ֪ͨ������ҹر�̯λ
    void OnMsgShowStallData( Msg* pMsg );                               // ����̯λ���ݵ��ͻ���
    void OnMsgTellBuyOrSellStallData( Msg* pMsg );                      // ֪̯ͨ�� ��� ���� ���� ���۸��Լ�����
    void OnMsgTellStallDataCount( Msg* pMsg );                          // ֪ͨ�򿪰�̯�����������������
    void OnMsgTellStallTitleToView( Msg* pMsg );                        // ֪ͨ��Χ���ĳ��ҵ�̯λ����ı���
    void OnMsgTellStallPrice( Msg* pMsg );                              // ֪̯ͨλ��ĳ����Ʒ��Ǯ
    void OnMsgTellTotalStallData( Msg* pMsg );                          // ֪̯ͨ��, �Լ�̯λ�ϵ�������Ϣ
    //------------------------------------------------------------

    void OnMsgTellServerExpModulus( Msg* pMsg );                        // ���鱶�ʵ���
    void OnMsgUpdateQuestVar( Msg* pMsg );                              // �������������ShowText�����

    void OnMsgOfflineFightOpAck( Msg* pMsg );                           // ս�����ֿ��ػ���

	//�������Ե㷴��
	void OnMsgCharAssignPotentialAck(Msg* pMsg); 

	//added by zilong. 2011-02-18. -----------------------------------
	//---------------------------�ķ����-----------------------------
	void On_MSG_CHANGEXINFA(Msg *pMsg);
	//added by zilong. end. ------------------------------------------

	//added by zilong. 2011-02-28. -----------------------------------
	//---------------------------̯λ��ѯϵͳ���-----------------------------
	void On_MSG_ACKSTALLQUERY(Msg *pMsg);
	//added by zilong. end. ------------------------------------------
	void OnMsgGotOnOffDrome(Msg *pMsg);
	void OnMsgReqGotOnDrome(Msg *pMsg);
	void OnMsgReqGotOnDromeAck(Msg *pMsg);

	//added by zilong. 2011-03-18. -----------------------------------
	//---------------------------��ɫ����-----------------------------
	void On_MSG_SHOWSIGNATURE(Msg *pMsg);
	void On_MSG_CHANGESIGNATUREREQ(Msg *pMsg);
	//added by zilong. end. ------------------------------------------
	
	//--------����---------------------
	void OnMsgAddUpdatePet(Msg *pMsg);           //��Ӹ��³���
	void OnMsgChangePet(Msg *pMsg);              //�ı����״̬
	void OnMsgPetBreedReqAck(Msg *pMsg);         //���ﷱֳ����
	void OnMsgPetBreedChoiceAck(Msg *pMsg);      //����ѡ����
	void OnMsgPetBreedStatus(Msg *pMsg);         //������������
	void OnMsgPetBreedFinish(Msg *pMsg);         //���ｻ�׷���
	void OnMsgPetBreedAcquireAck(Msg *pMsg);     //���ﷱֳ���䷴��
	void OnMsgPetCardList(Msg *pMsg);						//���µ�������ͼ��
	void OnMsgPetCardListAll(Msg *pMsg);				//���г���ͼ��
	void OnMsgPetSavvyUpack(Msg *pMsg);				//�����������Խ��
	void OnMsgPetUpdateChar(Msg *pMsg);				//���³����ɫ��Ϣ
	void OnMsgPetDead(Msg *pMsg);							//��ս����������Ϣ
	void OnMsgPetLearnSkill(Msg *pMsg);					//����ѧϰ�õ�����
	void OnMsgLookOtherPet(Msg *pMsg);				//�鿴�����˵ĳ���
	void OnMsgPetBreedCancelLock(Msg *pMsg);	//ȡ����������	
	void OnMsgRepeatedlyPet(Msg *pMsg);       //�ظ�ע�ḱ��
	//--------����----------------------
	void OnMsgCreateFamilyAck(Msg *pMsg);		//�ظ���������
	void OnMsgTellFamilyInfo(Msg *pMsg);
	void OnMsgTellCreateFmily(Msg *pMsg);		//ȫ���㲥�����˼���
	void OnMsgRequestJoinFamilyReq(Msg *pMsg);	//�峤�յ�������������
	void OnMsgInviteJoinFamilyReq(Msg *pMsg);
	void OnMsgInviteFamilyAck(Msg *pMsg);
	void OnMsgFamilyAimAck(Msg *pMsg);

	//------����--------------------------
	void OnMsgEquipTalismanAck(Msg* pMsg);   //װ������
	void OnMsgUnEquipTalismanAck(Msg* pMsg); //ж�ط���
	void OnMsgChangeTalisman(Msg* pMsg);     //�����ı�

	//-----��Ƶ����---------------------
	void OnMsgPlayMovieReq( Msg* pMsg );                                // �ű����󲥷���Ƶ
	void OnMsgPlayScene(Msg *pMsg);

	void OnMsgMoviceScreen(Msg *pMsg);

	//-----------san guo add--------------------
	void OnMsgG2CReqBianShen(Msg* pMsg);
	void OnMsgTellHeroAddAttr(Msg* pMsg);

	//------------̫ƽ�þ�----------------------
	void OnMsgTellTPHJRank(Msg* msg);

	//------------֪ͨ����ʱ��------------------
	void OnMsgTellQuestTime(Msg* msg);

	//----------------�ڳ����----------------//
	void OnMsgChangeToBiaocheAck(Msg* pMsg);
	void OnMsgRestoreFromBiaocheAck(Msg* pMsg);

	//player���Ŷ���
	void	OnMsgPlayerPlayAnim(Msg* pMsg);
	//----------------֪ͨ����buff------------//
	void OnMsgTellReliveBuff(Msg* pMsg);

	void OnMsgReqChangeHero(Msg* pMsg);
	void OnMsgInitLevelLimit(Msg* pMsg);
	void OnMsgDoneLimit(Msg* pMsg);

	//�Ӵ�ָ��װ���İ�
	void OnMsgUnBindEquip(Msg* pMsg);

	void OnMsgTimeStep(Msg* pMsg);

	//������ɾ��װ�� �ͻ���ͬ��
	void OnMsgRemoveItemByType(Msg* pMsg);

	//ƽ̨��Ӧ�������󷵻���ʾ
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
	void InitMustData();     //��ʼ���������������
	void InitBaseData();     //��ʼ������
	void ShowMonsterArea();  //��ʾˢ������
	void ResetRevice();      //��Դ����
	void ClearMustData();    //�ͷ���Դ
	void SetShowMonsterArea(bool bValue){m_bShowMonsterArea = bValue;}
private:
	std::vector<IDirect3DTexture9*> m_NumTexSet;  //����������
	ID3DXFont *m_pFont;     //����
	bool       m_bShowMonsterArea;
public:
	void SetPlayerLod(float fValue){m_fPlayerLod = fValue;}
private:
	float   m_fPlayerLod;  //�������ʱ��Mipmap����ֵ
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
