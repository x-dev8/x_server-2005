#include <math.h>
#include <assert.h>
#include <list>
#include "Me3d\Include.h"
#include "player.h"
#include "playermgr.h"
#include "../Resource/Resource.h"
#include "GameMain.h"
#include "NetworkInput.h"
#include "Effect.h"
#include "PlayerRole.h"
#include "PlayerAnimCtrl.h"
#include "itemdetail.h"
#include "Me3d/MoreAction.h"
#include "XmlStringLanguage.h"
#include "QuestManager.h"
#include "GlobalDef.h"
#include "FuncPerformanceLog.h"
#include "MeUi/UiManager.h"
#include "ui/Pack.h"
#include "ui/UIStorage.h"
#include "ui/MessageBox.h"
#include "ui/ChatInfoBox.h"
#include "ui/Shop.h"
#include "ui/LoadMap.h"
#include "ui/Target.h"
#include "ui/Group.h"
#include "ui/PlayerPrivateShop.h"  
#include "ui/Property.h"
#include "ui/Bargaining.h"
#include "ui/Compound.h"
#include "UI\SelectBox.h"
#include "ui/baseProperty.h"
#include "ui/Task.h"
#include "UI\NpcChatDialogBox.h"
#include "ui/Main.h"
#include "ui/FriendDlg.h"
#include "ui/SelfRbtnMenu.h"
#include "AttackInfoMan.h"
#include "escdlg.h"
#include "ProcessCharInfo.h"
#include "SystemConfig.h"
#include "GlobalDef.h"
#include "ErrorLog.h"
#include "MeUi/MouseManager.h"
#include "ui\FriendDlg.h"
#include "ui\rbtnmenu.h"
#include "MiniMap.h"
#include "ui/Progress.h"
#include "ShowScreenText.h"
#include "MeAudio/MeAudio.h"
#include "ui/topinfo.h"
#include "ui/Gang.h"
#include "ActionManager.h"
#include "MeFont/MeFont.h"
#include "ui/ExitGame.h"
// #include "ui/ChatSystem.h"
#include "Cfg.h"
#include "MeTerrain/stdafx.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "SystemSetting.h"
#include "wsRender.h"
#include "Me3d/Engine/RendererDX.h"
#include "CrossMapPF.h"
#include "ItemDetailConfig.h"
#include "Dxsdk/dinput.h"
#include "MeTerrain/FootPrint.h"
#include "Me3d/ShaderMgr.h"
#include "tstring.h"
#include "color_config.h"
#include "ui/PickUp.h"
#include "PlayerInfoMgr.h"
#include "ui/Task_Track.h"
#include "ui/GameSettingPlayer.h"
#include "ui/GameSettingSelf.h"
#include "GameSetting.h"
#include "ui/MiniMapUI.h"
#include "../GameUI/AutoAttackSet.h"
#include "NpcInfo.h"
#include "Me3d/Model/Mex2.h"
#include "wsCamera.h"
#include "ExpActionConfig.h"
#include "ExpressionAction.h"
#include "OnlineReward.h"
#include "PreventWallow.h"
#include "MeFont/MeFontSystem.h"
#include "Ui/InfoList.h"
#include "ui/SuAnimalCardList.h"
#include "SuAnimal.h"
#include "MessageDefine.h"
#include "SeeSuAnimal.h"
#include "SuAnimalMenu.h"
#include "SuAnimalUp.h"
#include "SuAnimalStudy.h"
#include "SuAnimalMaterialUp.h"
#include "IntroductionManager.h"
#include "ItemHero.h"
#include "../GameUI/zhujiangbianshen.h"
#include "bag/ItemBag2.h"
#include "Pet.h"
#include "PositionInfo.h"
#include "../GameUI/TimeLimitTask.h"
#include "../GameUI/OnBiaoChe.h"
#include "Ui/ManualLevelUp.h"
#include "SoundConfig.h"
#include "Ui/jiebang.h"
#include "TimeStringConfig.h"
#include "../GameUI/TimeString.h"
#include "NewSkillMain.h"
#include "EffectCharConfig.h"
#include "MonsterDefine.h"
#include "Ui/NpcTaskDialogBox.h"
BOOL		g_bTheRoleMoveToTargetPos = FALSE;
D3DXVECTOR3	g_vTheRoleTargetPos; //主角的目标位置
D3DXVECTOR3	g_vTheRoleTargetDir; //主角的目标方向
D3DXVECTOR3 g_vTheRoleJumpingDir; //主角的跳跃方向
D3DXVECTOR3 g_vTheRoleCurDir; //主角的当前方向
D3DXVECTOR3	g_vTheRoleAttackTargetPos; //主角的攻击目标位置

float g_fTheRoleJumpingRotate = 0.0f;

BOOL	g_bTheRoleAttackLockTarget = FALSE;

BOOL	g_bTheRoleMovingByDir = FALSE; //主角是否以方向移动
BOOL    g_bLastFrameMovebyDir = FALSE;
BOOL	g_bTheRoleCountermarch = FALSE;	//主角是否在倒退移动

DWORD	g_dwTheRoleJumpTime = 0; //主角的起跳时间
DWORD	g_dwTheRoleJumpingEndTime = 0; //主角落地的时间
BOOL	g_bTheRoleJumping = FALSE; //主角是否起跳
BOOL	g_bTheRoleJumpingCountermarch = FALSE; //主角是否在向后跳
BOOL	g_bTheRoleFallJumping = FALSE; //主角下落
D3DXVECTOR3	g_vTheRoleSlipJumpingDir; //主角下滑跳跃的方向

BOOL	g_bRenderRole = TRUE; //是否渲染主角

int     g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;	// 自动攻击状态

BOOL	g_bAutoRunForward = FALSE;

BOOL	g_bKeyboardVK_XIsDown = 0;

extern  short   g_shDeadIngDuration = 1000;     //lyh++ 死亡进行中的时间
short   g_shDeadOverDuration = 2000;    // 死亡动画结束后持续多少时间才删除
BOOL    g_bNextNotIntonate = FALSE;     // 下个吟唱技能是瞬发的
BOOL    g_bAutoPlayInteractionWithTarget = FALSE;   // 标记自动寻路到目标附近后，发送拥抱要求
BOOL	g_bAutoOpenPrivateShop = FALSE; // 走到面前，打开摆摊
DWORD   g_dw25DLButtonDownStartTime = 0;   // 2.5D鼠标操作时，记录左键按下的时间
BOOL    g_b25DRoleMoveFollowMouse = FALSE; // 2.5D鼠标操作，跟随鼠标移动
BOOL    g_b25DMouseLButtonDownOnTerrain = FALSE;    // 2.5D鼠标操作
BOOL    g_b25DRoleMoveFollowMouseFocusOnUI = FALSE; // 2.5D鼠标长按人跟随鼠标移动时，鼠标移动到UI上
BOOL    g_bPackagePickAll = FALSE;      // 是否拾取包裹内全部物品，通过LAlt拾取包裹触发

extern		CActionManager		g_ActionManager;

extern float g_fNeedVerifyDistance; // 需要纠正的距离
extern float g_fTheRoleBBoxHeight;

extern DWORD g_dwLastFrameCostTime;
extern DWORD g_dwLastFrameBeginTime;

extern BOOL g_bMouseMoveMode; //鼠标移动模式

extern float g_fTheRoleRotateZCorrect;
extern BOOL	g_bTheRoleMovingByDir;

extern int g_nPlayerCount;

extern CHeroGame* theApp;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern void	World2Screen( D3DXVECTOR3 vPos,int &x,int &y );
extern BOOL	g_bShowModelBBox;
extern BOOL g_bShowPlayer;
extern MouseManager theMouseManager;
extern int GetDirByOffset( int dx, int dy );
extern void RenderDecal( float x, 
				 float y,
				 int nTextureID, 
				 float fSize, 
				 float fAlpha );
extern BOOL	g_bRotateEnable;
extern short GetKeyboardInput( int iKey );
extern int PlayEffect( const char* pEffectName, CPlayer* pSrcPlayer = NULL, float fScale = 0 , DWORD dwFlyTime = 0, CPlayer* pDestPlayer = NULL, int nSlot = 0 ,bool bCalDist = true );

MexAnimCtrl GTeamFlag[MaxMainpleCnt];

DWORD CPlayerMgr::ms_dwUpdateAnimTimeStep = 0;

int ComparePlayerDist( const VOID* arg1, const VOID* arg2 )
{
	guardfunc;
	CPlayer* player1 = ((PlayerRenderLimitData*)(arg1))->pPlayer;
	CPlayer* player2 = ((PlayerRenderLimitData*)(arg2))->pPlayer;
	if( player1->GetDistanceToRole() > player2->GetDistanceToRole() )return 1;
	if( player1->GetDistanceToRole() < player2->GetDistanceToRole() )return -1;
	return 0;
	unguard;
}

static int ComparePlayerDist2( const VOID* arg1, const VOID* arg2 )
{
	guardfunc;
	CPlayer* player1 = *(CPlayer**)(arg1);
	CPlayer* player2 = *(CPlayer**)(arg2);
	if( player1->GetDistanceToPickRay() > player2->GetDistanceToPickRay() )return 1;
	if( player1->GetDistanceToPickRay() < player2->GetDistanceToPickRay() )return -1;
	return 0;
	unguard;
}

static int ComparePlayerDist3( const VOID* arg1, const VOID* arg2 )
{
	guardfunc;
	CPlayer* player1 = ((PlayerRenderLimitData*)(arg1))->pPlayer;
	CPlayer* player2 = ((PlayerRenderLimitData*)(arg2))->pPlayer;
	if( player1->GetDistanceToPickRay() > player2->GetDistanceToPickRay() )return 1;
	if( player1->GetDistanceToPickRay() < player2->GetDistanceToPickRay() )return -1;
	return 0;
	unguard;
}

static int CompareCollisionDist( const VOID* arg1, const VOID* arg2 )
{
    guardfunc;
    TPickResultInfo* pColi1 = (TPickResultInfo*)arg1;
    TPickResultInfo* pColi2 = (TPickResultInfo*)arg2;
    if( pColi1->dist > pColi2->dist )return 1;
    if( pColi1->dist < pColi2->dist )return -1;
    return 0;
    unguard;
}

bool CanRenderPlayerEffect( int nPlayerID )
{
    // 判断玩家特效隐藏
    if( nPlayerID > -1 )
    {
        CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(nPlayerID);
        if( pPlayer )
        {
            if( pPlayer == theHeroGame.GetPlayerMgr()->GetMe() )    // 自己
            {
                bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfEffect );
                if( !bShow )
                    return FALSE;
            }
            else if( pPlayer->MyTeamMember )    // 队友
            {
                bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerEffect );
                if( !bShow )
                    return FALSE;
            }
            else if( pPlayer->IsPlayer() )      // 其他玩家
            {
                bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerEffect );
                if( !bShow )
                    return FALSE;
            }
            else if( pPlayer->IsMonster() && pPlayer->GetMasterID() > -1 )     // 判断宠物
            {
                CPlayer *pMaster = theHeroGame.GetPlayerMgr()->FindByID(pPlayer->GetMasterID());
                if( pMaster )
                {
                    if( pMaster == theHeroGame.GetPlayerMgr()->GetMe() )    // 自己
                    {
                        bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfEffect );
                        if( !bShow )
                            return FALSE;
                    }
                    else if( pMaster->MyTeamMember )    // 队友
                    {
                        bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerEffect );
                        if( !bShow )
                            return FALSE;
                    }
                    else if( pMaster->IsPlayer() )      // 其他玩家
                    {
                        bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerEffect );
                        if( !bShow )
                            return FALSE;
                    }
                }
            }
        }
    }
    return TRUE;
}

CPlayerMgr::CPlayerMgr()
{
	m_pMe = NULL;
	m_fFarRole = PLAYER_RENDER_DIST_MAX;//38.2f;

	m_bCombineRenderPlayer = false;
	m_nPickId = -1;
	m_SessionKey = 0;
	m_nMouseRDownTargetPlayerServerID = -1;
	m_SkillBufTargetID = -1;
	m_bPlayMapEffect = FALSE;

	m_dwMapId = -1;
	m_nX = -1;
	m_nY = -1;

	m_PlayerID = -1;

	m_bRelivedByPlayer = FALSE;

	m_bShadowColor = TRUE;

	//m_bWaiting = FALSE;

	PendingSawNPC.clear();
	PendingSawPlayer.clear();
	m_nSawPlayerNPCCostTime = 0;

	m_nPlayerRenderLimit = PLAYER_RENDER_MAX;
	m_nPlayerQueueCount = 0;
	memset(m_PlayerDistQueue, 0, PLAYER_RENDER_QUEUE_MAX*sizeof(PlayerRenderLimitData));

    m_nPlayerRenderFlag = EPRF_ALL;
	m_nLastPlayerRenderFlag = EPRF_ALL;

    m_bTurnRoleToCamera = FALSE;
    m_bUseSkillBuf = TRUE; // 使用技能若不在攻击范围内，自动跑过去，此功能默认打开
    m_dwLastUpdateNpcActionTime = 0;
    m_bCanReceivePlayerMsg = TRUE;
    m_dwLastReqScriptTime = 0;
	m_vecDynamicCollison.clear();
	m_mapVipPlayer.clear();
	m_bNeedUpdateRoleUI = false;
	m_iDestroyCharLimitPerFrame = 3;

	InitBaseData();

	m_fPlayerLod = -2;

	m_pCameraAnim = NULL;
	m_bPlayTrack  = NULL;
	m_nCameraModelID = -1;
}

BOOL CPlayerMgr::Init(  )
{
	guardfunc;
	m_pMe = NULL;

	m_bLoginSucc = FALSE;
	m_shMouseTargetPlayerSeverID = -1;
	m_bClickTheTerrain = false;

	m_bNeedBeginDilog = false;

    m_dwGamePing = 0;
    m_dwLastReqScriptTime = 0;
	m_bNeedUpdateRoleUI = false;

	m_iDestroyCharLimitPerFrame = 3;
	ClearMustData();
	return TRUE;
	unguard;
}

void OutputDebugMsg( Msg *pMsg )
{
	guardfunc;
	return;
	unguard;
}

void CPlayerMgr::AutoCS( int iPlayerID )
{
	guardfunc;
	unguard;
}


void CPlayerMgr::Update( DWORD time, Frustum &frustum )
{
	guardfunc;
	if( !g_bShowPlayer )
		return;

	if( !m_pMe )
		return;

	Box* pBBox = m_pMe->GetWorldBBox();
	if( pBBox )
	{
		g_fTheRoleBBoxHeight = pBBox->v[4].z - pBBox->v[0].z;
	}
#ifdef _DEBUG
    POINT point;
    GetCursorPos(&point);
    char szWord[256];
    MeSprintf_s(szWord,sizeof(szWord),"X:%d Y:%d",point.x,point.y);
#endif

	ProcessCamera();
	guard(CPlayerMgr::test2);
	if(m_pMe && m_pMe->IsInWater() && m_pMe->IsMounting() && m_pMe->IsCanDisMount())
	{
		DisDrome();
		m_pMe->DisMount();
	}
	unguard;

	float fX = m_pMe->GetPos().x;
	float fY = m_pMe->GetPos().y;

	std::map<GameObjectId, CPlayer*>::iterator it;
	//检查是否是自己的队员	
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;
		if( pPlayer )
		{
			pPlayer->MyTeamMember = FALSE;
		}
	}	
	if( thePlayerRole.GetTeamMemberNum() > 0 )
	{
		std::vector<TeamInfo> vecPlayer = thePlayerRole.GetTeamInfo();
		for( int i=0; i< vecPlayer.size(); i++ )
		{
			CPlayer* pPlayer = FindByName(vecPlayer[i].szName.c_str());
			if( pPlayer )
			{
				if( pPlayer != GetMe() )
				{
					pPlayer->MyTeamMember = TRUE;
					pPlayer->ManipleID = vecPlayer[i].stManiple;
				}

			}
		}
	}

	// 更新倒计时领礼物
	COnlineReward::Instance().UpdateOnlineReward();

	thePlayerRole.UpdateLockItem();
	
	// 更新防沉迷在线时间---有必要1分钟就跳一次么???
	//CPreventWallow::Instance().UpdatePreventWallow();

	// 更新小队技能
	thePlayerRole.CalcTeamSkillLevel();

	// 更新表情动作CD
	CExpressionAction::Instance().UpdateCoolDown();

	g_nPlayerCount = 0;
	guard(CPlayerMgr::test3);
	bool hasPlayerRemove = false;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;

		if( !pPlayer->IsItem() )
		{
			g_nPlayerCount++;
		}
        else
        {
            // 物品延时显示时间结束后，播拾取特效
            if( pPlayer->m_bCanPick && pPlayer->IsItemDropDelayOver() && pPlayer->m_nCollectionEffectID == -1)
            {
                pPlayer->m_nCollectionEffectID = PlayEffect("common\\QuestItem.ini",pPlayer);
            }
        }

		if( pPlayer->NeedRemove() )                      
		{       
			 /*&& (pPlayer->IsDeadOver() || pPlayer->GetCharType() != Object_MonsterpPlayer->GetCharType() == Object_Player)*/
			if( time - pPlayer->GetStartRemoveTime() > 1000 || pPlayer->GetCharType() == Object_Player) //当是playerde
			{
				if( !GetMexResMgr()->TryLock() )
					continue;
				// 这个try贴图锁，否则容易被锁 [10/29/2010 zhangjiayi]
				if( !GetEngine()->GetTextureManager()->TryLockTextureManager() )
				{
					GetMexResMgr()->UnLock();
					continue;
				}
				BeginGuard

				if( pPlayer->IsPlayer() )
					hasPlayerRemove = true;

				int curEffectId = pPlayer->GetEffectID();
				if(curEffectId > 0)
				{

					IEffect *pEffect = GetEffectMgr()->GetEffect( curEffectId );
					if (pEffect)
					{
						pEffect->SetDead();
					}
					pPlayer->ReSetEffectID();
				}

				//清空动作队列，主要是处理攻击消息
				pPlayer->ExcuteClearActionQueue();
				RemovePlayerFromActiveList( pPlayer->GetID() );	 //这里

				if( pPlayer->Release() ) //没引用了 就直接清除内存
				{
					//pPlayer->Destroy();
					DestroyPlayer( pPlayer );
					delete pPlayer;
					//g_nPlayerCount--;
				}
				else
				{
					//加入暂存队列
					AddPlayerToKeepList( pPlayer );
				}
				EndGuard
				GetEngine()->GetTextureManager()->UnLockTextureManager();
				GetMexResMgr()->UnLock();
				break;
			}
		}
	}
// 	if (hasPlayerRemove)
// 	{
// 		s_CUI_ID_FRAME_TRACK.RefreshPlayerList();
// 	}
	unguard;

	guard(CPlayerMgr::test4);
	m_vecDynamicCollison.clear();
	int iMapId = 0;
	if( SwGlobal::GetWorld() && SwGlobal::GetWorld()->GetWorldBuffer() && SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile() )
		iMapId = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile()->GetMapId();

	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;
        pPlayer->UpdateDistanceToRole( time, fX, fY );

		if( pPlayer->IsNpc() )
		{
			/*
			// 更新带动态碰撞的NPC列表
			NpcInfo::Npc* pNpc = theNpcInfo.GetDynamicCollNpcByName(pPlayer->GetName(), iMapId);
			if( !pNpc )
				continue;

			if( pNpc->isDynamicCollision )
			*/
			// 电梯NPC
			if (pPlayer->GetNpcType() == eNT_Elevator)
				m_vecDynamicCollison.push_back(pPlayer);
		}
		else if( pPlayer->IsMonster() && pPlayer->GetMonsterType() == eMT_Collision )
		{
			// 阻挡怪
			m_vecDynamicCollison.push_back(pPlayer);
		}
	}
	// 创建动态碰撞BspTree
	m_DynamicCollisionBsp.Destroy();
	m_DynamicFloorBsp.Destroy();
	if( m_vecDynamicCollison.size() > 0 )
	{
		m_DynamicCollisionBsp.SetMinLeafSize( 100.f );
		m_DynamicFloorBsp.SetMinLeafSize(100.0f);
		for( int i=0; i<m_vecDynamicCollison.size(); ++i )
		{
			CPlayer* pPlayer = m_vecDynamicCollison[i];
			if( !pPlayer )
				continue;

			CreateDynamicCollision(pPlayer);
		}
		m_DynamicCollisionBsp.CreateTree2();
		m_DynamicFloorBsp.CreateTree2();
	}

    if( m_vectorDeathPlayer.size() > 0 )
    {
        std::vector< CPlayer* >::iterator iter;
        for( iter = m_vectorDeathPlayer.begin(); iter != m_vectorDeathPlayer.end(); ++iter )
        {
            CPlayer* pPlayer = (CPlayer*)*iter;
            if( !pPlayer )
                continue;
            pPlayer->UpdateDistanceToRole( time, fX, fY );
        }
    }

    // 检查锁定目标
    if( GetLockPlayerID() >= 0 )
    {
        CPlayer* pPlayer = FindByID(GetLockPlayerID());
        if( pPlayer && pPlayer->GetDistanceToRole() > PLAYER_LOCK_DIST_MAX )
        {
            cancelBehavior();
            SetLockPlayerID(-1);
        }
    }

    // 检查跟随目标
    if( s_CUI_ID_FRAME_Target.GetFollowPlayerId() >= 0 )
    {
        CPlayer* pPlayer = FindByID(s_CUI_ID_FRAME_Target.GetFollowPlayerId());
        if( !pPlayer )
        {
            s_CUI_ID_FRAME_Target.SetFollowPlayerId(-1);
        }
        else if( pPlayer->GetDistanceToRole() > PLAYER_RENDER_DIST_MAX || pPlayer->IsDead() )
        {
            s_CUI_ID_FRAME_Target.SetFollowPlayerId(-1);
        }
    }
	unguard;

	// 鼠标选择的player
	int x,y;
	x = theUiManager.m_ptMoust.x;
	y = theUiManager.m_ptMoust.y;

	BOOL bNeedToFindTheMouseTargetPlayer = TRUE;
	CPlayer* pCurMouseTargetPlayer = FindByID( m_shMouseTargetPlayerSeverID );

	if( g_bRotateEnable && !pCurMouseTargetPlayer )
	{
		bNeedToFindTheMouseTargetPlayer = FALSE;
	}

	m_shMouseTargetPlayerSeverID = -1;

	static DWORD dwUpdateStep = 0;

	guard(CPlayerMgr::test5);
	if ( !theUiManager.IsMouseInUI() && bNeedToFindTheMouseTargetPlayer )
	{
		if( m_shMouseTargetPlayerSeverID < 0 )
		{			
			getwsCamera()->GetMeCamera()->BuildPickRay( 
				theUiManager.m_ptMoust.x, 
				theUiManager.m_ptMoust.y,
				m_vFrom,
				m_vDir,
				SCREEN_WIDTH,
				SCREEN_HEIGHT );

            // 先获取射线与最近碰撞盒的距离，设定pick距离为1000米
            TPickResult castResult;
            float fNearestColiDist = 10000; // 距离是平方结果，实际距离100米
			bool bIsAlphaModel = false;
            Vector vectorDir = *(Vector*)&m_vDir;
			//LYH修改鼠标点选目标可以透过空气墙
            if(SwGlobal::GetWorldPicker()->Pick(*(Vector*)&m_vFrom, *(Vector*)&m_vDir,castResult,/*emPT_CollisionObj|*/emPT_AlphaBox,false,1000))
            {
                if( castResult.pickResultCount > 1 )
                    qsort(castResult.pickResultInfo, castResult.pickResultCount, sizeof(TPickResultInfo), CompareCollisionDist);

                for( int i=0; i<castResult.pickResultCount; i++)
                {
                    castResult.pickResultInfo[i].normal.normalize();
                    float fDot = vectorDir.dot(castResult.pickResultInfo[i].normal);
                    if( fDot < 0 )
                    {
                        fNearestColiDist = castResult.pickResultInfo[i].dist * castResult.pickResultInfo[i].dist;
						if (castResult.pickResultInfo[i].resultObjInfo)
						{
							bIsAlphaModel = !(abs(castResult.pickResultInfo[i].resultObjInfo->GetAlpha() - 1.0) < 0.0001);
						}
                        break;
                    }
                }
            }

            std::map<GameObjectId, CPlayer*>::iterator it;
			std::vector<CPlayer*> vectorSelPlayer;
			CPlayer* arraySelPlayer[200];	// 鼠标位置覆盖人物，用array便于快速排序，希望200足够大
			int nArrayPlayerCount = 0;
			for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
			{
				CPlayer* pPlayer = it->second;
                if( !pPlayer )
                    continue;

				if( pPlayer->IsItem() && !pPlayer->IsItemDropDelayOver() )
					continue;

				// NPC隐藏
				if( pPlayer->IsNpc() && pPlayer->IsHide() )
					continue;

                // 不可见的召唤物
                if( !pPlayer->IsVisibleToOtherPlayer() )
                {
                    if( GetMe() )
                    {
                        if( GetMe()->GetID() != pPlayer->GetMasterID() )
                            continue;
                    }
                    else
                        continue;
                }

				guard(CPlayerMgr::test5.1);
				if( pPlayer->NeedRemove() )
					continue;

				if( pPlayer->GetMonsterType() == eMT_Building )
					continue;

				if( pPlayer->GetCurRenderAlpha() < 0.0618f )
					continue;

                pPlayer->UpdateDistanceToPickRay(m_vFrom.x, m_vFrom.y);
                if ( (!bIsAlphaModel) && (!pPlayer->IsNpc() && !pPlayer->IsPlayer() && pPlayer->GetDistanceToPickRay() > fNearestColiDist) )
                    continue;

				Box* pBBox = pPlayer->GetWorldBBox();
				if( pPlayer->IsMounting() && pPlayer->GetMountAnim() && pPlayer->GetMountAnim()->GetWorldBBox() )
					pBBox = pPlayer->GetMountAnim()->GetWorldBBox();
				
				if( pBBox && pBBox->IntersectCircle( *(Vector*)&m_vFrom,	*(Vector*)&m_vDir, sqrtf(pPlayer->GetDistanceToPickRay()) ) )
				{
					vectorSelPlayer.push_back( pPlayer );
				}
				unguard;
			}

            // 死亡的玩家也要能选中
            if( !m_vectorDeathPlayer.empty() )
            {
                std::vector< CPlayer* >::iterator iter;
                for( iter = m_vectorDeathPlayer.begin(); iter != m_vectorDeathPlayer.end(); ++iter )
                {
                    CPlayer* pPlayer = (CPlayer*)*iter;
                    if( !pPlayer )
                        continue;

                    // 死亡队列中只取玩家加入队列 这里只只处理玩家的 死亡队列中的玩家
                    if( !pPlayer->GetAnim() || !pPlayer->IsPlayer() )
                        continue;

                    guard(CPlayerMgr::test5.2);
                    if( pPlayer->NeedRemove() )
                        continue;

                    if( pPlayer->GetMonsterType() == eMT_Building )
                        continue;

                    if( pPlayer->GetCurRenderAlpha() < 0.0618f )
                        continue;

                    pPlayer->UpdateDistanceToPickRay(m_vFrom.x, m_vFrom.y);
                    if((!bIsAlphaModel) &&  pPlayer->GetDistanceToPickRay() > fNearestColiDist )
                        continue;

					
                    if( pPlayer->GetWorldBBox() && pPlayer->GetWorldBBox()->IntersectCircle( *(Vector*)&m_vFrom,	*(Vector*)&m_vDir, sqrtf(pPlayer->GetDistanceToPickRay()) ) )
                    {
                        vectorSelPlayer.push_back( pPlayer );
                    }
                    unguard;
                }
            }

            BOOL bPickNPC = FALSE;  // 优先选NPC，bPickNPC记录射线pick的选中列表里是否有NPC
            BOOL bPickItem = FALSE; // 如果item和人站一起，优先pick item
			int nSelPlayerCount = vectorSelPlayer.size();
			if( nSelPlayerCount > 0 )
			{
                Vector vPickFrom = *(Vector*)&m_vFrom;
				std::vector<CPlayer*>::iterator iter;
				for( iter = vectorSelPlayer.begin(); iter != vectorSelPlayer.end(); ++iter )
				{
					if( nArrayPlayerCount >= 200 )	// 超过200就不计算在内，一般不会超过200吧。
						break;

					CPlayer* pPlayer = *iter;
					if( pPlayer->IsItem() && !pPlayer->IsItemDropDelayOver() )
						continue;
					guard(test5.2);
					if( pPlayer->NeedRemove() )
						continue;

					if( pPlayer->GetMonsterType() == eMT_Building )
						continue;

					// 当玩家变身镖车时，则排除在选取列表之外
					if ( pPlayer->IsMonster() && pPlayer->GetSubMonsterType() == Object_MonsterProtected )
					{
						CPlayer *master = FindByID( pPlayer->GetMasterID() );
						if (master != NULL && master->IsYabiaoState())
							continue;
					}

					if( pPlayer->GetCurRenderAlpha() < 0.0618f )
						continue;

					Box* pBBox = pPlayer->GetWorldBBox();
					if( pPlayer->IsMounting() && pPlayer->GetMountAnim() && pPlayer->GetMountAnim()->GetWorldBBox() )
						pBBox = pPlayer->GetMountAnim()->GetWorldBBox();

					//如果是玩家，并且玩家已经死亡，则扩大bbox的显示
					if(pPlayer && pPlayer->GetAnim() && pPlayer->GetAnim()->GetMex() && pPlayer->GetAnim()->GetMex()->GetSkeleton() && pPlayer->IsPlayer() &&pPlayer->IsDead())
					{
						float value_ = 2.5f;
						MeMatrix matTransform;
						Box box;
						int nSpineBoneID = pPlayer->GetAnim()->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine1" );
						if (nSpineBoneID >= 0)
						{	
							Vector vec =  pPlayer->GetAnim()->GetBoneWorldPos(nSpineBoneID);
							
							Vector _vMin = Vector((vec.x - value_), (vec.y - value_), pBBox->v[0].z);
							Vector _vMax = Vector((vec.x + value_), (vec.y + value_),  pBBox->v[7].z);	
							box.BuildAABB( _vMin, _vMax );
						}
						else
						{
							Vector _vMin = Vector((pBBox->v[0].x - value_), (pBBox->v[0].y - value_), pBBox->v[0].z);
							Vector _vMax = Vector((pBBox->v[7].x + value_), (pBBox->v[7].y + value_),  pBBox->v[7].z);
							box.BuildAABB( _vMin, _vMax );
						}


						if( box.Intersect( *(Vector*)&m_vFrom, *(Vector*)&m_vDir ) )
						{
							//if( KEY_DOWN(VK_LMENU) )
							if( GetKeyboardInput(DIK_LMENU) )
							{
								if( !pPlayer->IsPlayer() )
								{
									arraySelPlayer[nArrayPlayerCount++] = pPlayer;
									if( pPlayer->IsNpc() )
										bPickNPC = TRUE;
									else if( pPlayer->IsItem() )
										bPickItem = TRUE;
								}
							}
							else
							{
								arraySelPlayer[nArrayPlayerCount++] = pPlayer;
								if( pPlayer->IsNpc() )
									bPickNPC = TRUE;
								else if( pPlayer->IsItem() )
									bPickItem = TRUE;
							}
						}
						 
					}
					else if( pBBox && pBBox->Intersect( *(Vector*)&m_vFrom, *(Vector*)&m_vDir ) )
					{
						//if( KEY_DOWN(VK_LMENU) )
						if( GetKeyboardInput(DIK_LMENU) )
						{
							if( !pPlayer->IsPlayer() )
							{
								arraySelPlayer[nArrayPlayerCount++] = pPlayer;
                                if( pPlayer->IsNpc() )
                                    bPickNPC = TRUE;
                                else if( pPlayer->IsItem() )
                                    bPickItem = TRUE;
							}
						}
						else
                        {
                            arraySelPlayer[nArrayPlayerCount++] = pPlayer;
                            if( pPlayer->IsNpc() )
                                bPickNPC = TRUE;
                            else if( pPlayer->IsItem() )
                                bPickItem = TRUE;
                        }
					}

					unguard;
				}
			}
			guard(test0.3);
			if( nArrayPlayerCount > 0 )
			{
				// 由近至远快速排序
				if( nArrayPlayerCount > 1 )
					qsort(arraySelPlayer, nArrayPlayerCount, sizeof(CPlayer*), ComparePlayerDist2);
				CPlayer* pMouseTargetPlayer = NULL;
                CPlayer* pMouseTargetPlayerNearest = NULL;   // 保存离玩家最近的人物，如果是pick NPC但搜索不到NPC，则取这个player
				int index = 0;
                float fMaxDist = 3.5f;
                float fItemMaxDist = 3.5f;// modified, jiayi, [2009/11/15]
                float fNearestPlayerToCameraDist = 0;
				for(index = 0; index < nArrayPlayerCount;++index)
				{
					if(arraySelPlayer[index]->IsDisableCollection())
					{
						continue;						
					}
					else if( bPickNPC || bPickItem )
                    {
                        // 找到一个NPC
                        float fSelectPLayerToCameraDist = sqrtf(arraySelPlayer[index]->GetDistanceToPickRay());
                        if( arraySelPlayer[index]->IsNpc() )
                        {
                            // NPC与相机距离超过该player与相机距离3.5米，则跳出循环
                            if( pMouseTargetPlayerNearest 
                                && fSelectPLayerToCameraDist - fNearestPlayerToCameraDist > fMaxDist )
                                break;
                            else
                            {
                                pMouseTargetPlayer = arraySelPlayer[index];
                                break;
                            }
                        }
                        else if( arraySelPlayer[index]->IsItem() )
                        {
                            // Item与相机距离超过该player与相机距离1.5米，则跳出循环
                            if( pMouseTargetPlayerNearest 
                                && fSelectPLayerToCameraDist - fNearestPlayerToCameraDist > fItemMaxDist )
                                break;
                            else
                            {
                                pMouseTargetPlayer = arraySelPlayer[index];
                                break;
                            }
                        }
                        // 非NPC，则保存与相机最近人物
                        else if( !pMouseTargetPlayerNearest )
                        {
                            pMouseTargetPlayerNearest = arraySelPlayer[index];
                            fNearestPlayerToCameraDist = sqrtf(pMouseTargetPlayerNearest->GetDistanceToPickRay());
                        }
                        // 如果当前查询人物与最近人物超过3.5米，则不再找NPC,直接跳出循环
                        else if( pMouseTargetPlayerNearest
                            && fSelectPLayerToCameraDist - fNearestPlayerToCameraDist > fMaxDist )
                            break;
                    }
                    else
					{
						pMouseTargetPlayer = arraySelPlayer[index];
						break;
					}
				}
                if( !pMouseTargetPlayer )
                    pMouseTargetPlayer = pMouseTargetPlayerNearest;
				
				if ( pMouseTargetPlayer == m_pMe )
				{
					++index;
					bool bFound = false;
					for(; index < nArrayPlayerCount;++index)
					{
						if(arraySelPlayer[index]->IsDisableCollection())
						{
							continue;						
						}
						else
						{
							pMouseTargetPlayer = arraySelPlayer[index];
							bFound = true;
							break;
						}
					}
					if (!bFound && !g_bRenderRole)
					{
						pMouseTargetPlayer = NULL;
					}
				}
				if (pMouseTargetPlayer)
				{

					m_shMouseTargetPlayerSeverID = pMouseTargetPlayer->GetID();

					if (pMouseTargetPlayer->IsEffect()) //特效怪
					{
						EFFECTCHARCONFIG _Config;
						if(theEffectCharConfig.FindEffectCharConfigBySkillID(_Config,pMouseTargetPlayer->GetEffectCharSkillID()))
						{
							if (!_Config.bCanBeAttack)
							{
								m_shMouseTargetPlayerSeverID = -1;
							}
							
						}
					}							
				}
			}

			unguard;
		}
	}
	unguard;

	ResetDestroyAnimNum();	// 每帧在CheckDestroyAnimLowMemory前调用
	guard(test6);
	std::vector<int> vctDeadOverPlayers;
	vctDeadOverPlayers.clear();

	INT nPlayerCnt = m_mapPlayers.size();
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;

		if( !pPlayer )
		{
			continue;
		}

		pPlayer->UpdateBaseData( time);	// 包含更新alpha

		if( pPlayer == m_pMe )
		{
			pPlayer->SetNeedRender();
			pPlayer->Update( time);
			continue;
		}

		Box *pBox = pPlayer->GetWorldBBox();

		BOOL bDistanceRender = FALSE;
		if( pPlayer->GetDistanceToRole() < GetFarRole() )
		{
            // 进渲染范围，淡入
			bDistanceRender = TRUE;
			float fAlpha = pPlayer->GetCurRenderAlpha();
			if( fAlpha < 1 && pPlayer->GetMonsterType() != eMT_IllusionMonster )
			{
				pPlayer->SetFinalRenderAlpha( 1 );
				pPlayer->SetDefaultFinalRenderAlpha( 1 );

                // 初始化NPC Idle Action
                if( pPlayer->IsNpc() )
                    pPlayer->InitNpcAction(time);
			}
		}
		else
		{
            // 出渲染范围，淡出
			float fAlpha = pPlayer->GetCurRenderAlpha();
			if( fAlpha > 0 && pPlayer->GetMonsterType() != eMT_IllusionMonster )
			{
				pPlayer->SetFinalRenderAlpha( 0 );
				pPlayer->SetDefaultFinalRenderAlpha( 0 );
				bDistanceRender = TRUE;

                // 结束NPC Idle Action
                if( pPlayer->IsNpc() )
                    pPlayer->ExitNpcAction();

				if(pPlayer->IsMonster())
					pPlayer->EndMonsterAction();
			}
		}

		// 更新NPC Idle Action
        if( pPlayer->IsNpc() && time - m_dwLastUpdateNpcActionTime > 1000)
        {
            pPlayer->UpdateNpcAction(time);
        }

		if(pPlayer->IsMonster())
			pPlayer->UpdateMonsterAction(time);

		if( bDistanceRender )
		{
			if( pBox )
			{
				if( frustum.Cull( *pBox ) || pPlayer->GetNpcType() == eNT_Elevator)
				{
                    pPlayer->SetNeedRender();
				}
				else
				{
					pPlayer->ResetNeedRender();
				}
			}
			else
			{
				pPlayer->ResetNeedRender();
            }

			// 需要更新，不然图形渲染会破面。 [8/4/2008 whu]
			pPlayer->Update( time);
		}
		else
		{
			pPlayer->ResetNeedRender();
        }

		// 玩家不在视野内，距离主角超过30米，且离最近一次渲染超过5秒，则释放动画数据
		if( !pPlayer->IsNeedRender() && pPlayer->IsPlayer() )
		{
			CheckDestroyAnimLowMemory(pPlayer);
		}

		if( pPlayer->IsDeadOver() )
		{
			vctDeadOverPlayers.push_back(pPlayer->GetID());
		}
	}

	//lyh测试++  这个针对死亡用 改用我自己的逻辑
	for( int i=0; i<vctDeadOverPlayers.size(); ++i )
	{
		CPlayer* pPlayer = FindByID(vctDeadOverPlayers[i]);

		if( !pPlayer )
		{
			continue;
		}

		if( pPlayer == m_pMe )
		{
			continue;
		}

		if( pPlayer->IsDeadOver() )
		{
			//if( RemovePlayerFromActiveList( pPlayer->GetID() ) )
			{
				//清空动作队列，主要是处理攻击消息
				pPlayer->ExcuteClearActionQueue();
				RemovePlayerFromActiveList( pPlayer->GetID() );
				if( pPlayer->Release() )
				{
					//删除相关的效果
					DestroyPlayer( pPlayer );
					delete pPlayer;
				}
				else
				{
					//加入暂存队列
					AddPlayerToKeepList( pPlayer );
				}
			}
		}
	}

    if( time - m_dwLastUpdateNpcActionTime > 1000 )
    {
        m_dwLastUpdateNpcActionTime = time;
    }
	unguard;

	AutoSkillProc();

	std::vector<CPlayer*> vectorDelPlayer;
	DWORD dwTime = HQ_TimeGetTime();
	for (int i=0; i<(int)m_vectorDeathPlayer.size(); i++)
	{
		CPlayer* pPlayer = m_vectorDeathPlayer[i];
		if( !pPlayer )
			continue;

		Box *pBox = pPlayer->GetWorldBBox();
		pPlayer->ResetNeedRender();

		//更新角色的Alpha
		pPlayer->UpdateRenderAlpha();

		BOOL bDistanceRender = FALSE;
		if( pPlayer->GetDistanceToRole() < GetFarRole() )
		{
			bDistanceRender = TRUE;
			float fAlpha = pPlayer->GetCurRenderAlpha();
			if( fAlpha < 1 && pPlayer->GetMonsterType() != eMT_IllusionMonster)
			{
				pPlayer->SetFinalRenderAlpha( 1 );
				pPlayer->SetDefaultFinalRenderAlpha( 1 );
			}
		}
		else
		{
			float fAlpha = pPlayer->GetCurRenderAlpha();
			if( fAlpha > 0 && pPlayer->GetMonsterType() != eMT_IllusionMonster)
			{
				pPlayer->SetFinalRenderAlpha( 0 );
				pPlayer->SetDefaultFinalRenderAlpha( 0 );
				bDistanceRender = TRUE;
			}
		}
		if( bDistanceRender && pBox && frustum.Cull( *pBox ) )
		{
			pPlayer->SetNeedRender();
		}

		// 玩家不在视野内，距离主角超过30米，且离最近一次渲染超过5秒，则释放动画数据
		if( !pPlayer->IsNeedRender() && pPlayer->IsPlayer() )
		{
			CheckDestroyAnimLowMemory(pPlayer);
		}
		
		bool bDelete = false;
		
		{
            BOOL bCollectItem = FALSE;
            if( pPlayer->IsMonster() 
                && (pPlayer->IsCollection(false)) )
                    bCollectItem = TRUE;

			if( (!bCollectItem && dwTime - pPlayer->GetDeadOverTime() > g_shDeadOverDuration)
                || (bCollectItem && dwTime - pPlayer->GetDeadOverTime() > 100) )
			{
				//可以删除了
				if( pPlayer->IsNeedToDelete() )
				{
					if( !pPlayer->IsPlayer() )
					{
						if( pPlayer->GetCurRenderAlpha() > 0.01f )
						{
							pPlayer->SetFinalRenderAlpha( 0 );
						}
						else
						{
							vectorDelPlayer.push_back( pPlayer );
							// 这里是为了死亡渐变用,刚死亡的时候会添加一个引用，下同 [11/10/2010 zhangjiayi]
							//lyh去掉引用--
							if( pPlayer->IsDead() )
								pPlayer->DecRef();
							bDelete = true;
						}
					}
					else
					{
						vectorDelPlayer.push_back( pPlayer );
						if( pPlayer->IsDead() )
							pPlayer->DecRef();
						bDelete = true;
					}
				}
			}
		}
		if( !bDelete && bDistanceRender )
		{
			pPlayer->Update( time);
		}
	}

	for (int i=0; i<(int)vectorDelPlayer.size(); i++)
	{
		DeleteDeathPlayer( vectorDelPlayer[i] );
	}

	//登录成功才测lag
	if( m_bLoginSucc )
	{
		if( m_lag.CanSendReq() )
		{
			MsgGetLag msg;
			msg.header.stID = m_pMe->GetID();
			GettheNetworkInput().SendMsg( &msg,msg.GetLength() );
			m_lag.SendReq();
		}
	}

	thePlayerRole.m_SkillBag.Update();
	thePlayerRole.m_MountSkillBag.Update();
	thePlayerRole.m_PetSkillBag.Update();
	thePlayerRole.m_HeroSkillBag.Update();

	g_fNeedVerifyDistance = g_nPlayerCount*0.5f + NeedVerifyDistance;
    
    thePlayerRole.DuelProcess();
	unguard;
}

// 根据客户端的Id查找Player
CPlayer* CPlayerMgr::FindByClientID( int nID )
{
	guardfunc;
	return NULL;
	unguard;
}

// 查找相同ID
int CPlayerMgr::FindSameID( GameObjectId stID )
{
	guardfunc;
	int nPlayerCount = 0;
	std::map< GameObjectId, CPlayer* >::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;
		if ( pPlayer && pPlayer->GetID() == stID )
		{
			nPlayerCount++;
		}
	}
	return nPlayerCount;
	unguard;
}


// 根据服务器的Id查找Player
CPlayer* CPlayerMgr::FindByID( GameObjectId stID )
{
	guardfunc;
    if( m_mapPlayers.size() == 0 || stID < 0 )
        return NULL;
	std::map< GameObjectId, CPlayer* >::iterator it = m_mapPlayers.find(stID);
	if (it != m_mapPlayers.end())
	{
		return it->second;
	}
	
// 	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
// 	{
// 		CPlayer* pPlayer = it->second;
// 		if ( pPlayer && pPlayer->GetID() == stID )
// 		{
// 			return pPlayer;
// 		}
// 	}

	return NULL;
	unguard;
}

// 根据数据库中的角色ID查找Player
CPlayer* CPlayerMgr::FindPlayerByCharacterID( DWORD dwCharacterID )
{
	guardfunc;
	std::map< GameObjectId, CPlayer* >::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;
		if ( pPlayer && pPlayer->IsPlayer() && pPlayer != m_pMe && pPlayer->GetCharacterID() == dwCharacterID )
		{
			return pPlayer;
		}
	}
	return NULL;
	unguard;
}


// 根据服务端的Id在死亡队列中查找Player
CPlayer* CPlayerMgr::FindByServerIDInDeath( GameObjectId shID )
{
	guardfunc;
	for ( int i=0; i<(int)m_vectorDeathPlayer.size(); i++ )
	{
		CPlayer* pPlayer = m_vectorDeathPlayer[i];
		if ( pPlayer && pPlayer->GetID() == shID )
		{
			return pPlayer;
		}
	}
	return NULL;
	unguard;
}

// 根据客户端的Id在死亡队列中查找Player
CPlayer* CPlayerMgr::FindByClientIDInDeath( GameObjectId nID )
{
	guardfunc;
	return NULL;
	unguard;
}

BOOL CPlayerMgr::CreateMe( GameObjectId stID )
{
	guardfunc;

	char szBuf[256] = {0};
	_snprintf( szBuf, 255, "meid = %d", stID );
	OutputDebugString( szBuf );

	CPlayer* pPlayer = AddPlayer( stID,Object_Player,true );
	assert( pPlayer != NULL );
	m_pMe = pPlayer;
	m_pMe->SetRole( TRUE );
	m_pMe->SetBodySize( 1.0f );

	return TRUE;
	unguard;
}

CPlayer* CPlayerMgr::AddPlayer( GameObjectId stID,int iCharType,bool bIsMe )
{
	guardfunc;
	// 测试1得出的结论，如果found，应视为错误
	CPlayer* pPlayer = FindByID( stID );
	if( pPlayer )
	{
		guard(test1)
		PlayerExit( pPlayer->GetID() );
		pPlayer = FindByID( stID );
		if( pPlayer )
		{
			guard(test2)
			pPlayer->ExcuteClearActionQueue();
			RemovePlayerFromActiveList( pPlayer->GetID() );	
			if( pPlayer->Release() )
			{
				guard(test3);
				DestroyPlayer( pPlayer );
				delete pPlayer;
				unguard;
			}
			else
			{
				AddPlayerToKeepList( pPlayer, TRUE );
			}
			unguard;
		}
		unguard;
	}

	pPlayer = MeNew CPlayer;
	int nIndex = GetEffectMgr()->RegisterCharEffectContainer();
	if( nIndex >= 0 )
	{
		pPlayer->SetCharEffectContainer( GetEffectMgr()->GetCharEffectContainer( nIndex ) );
	}

	pPlayer->Reset();
	pPlayer->SetMask( FALSE );
	pPlayer->SetID( stID );
	pPlayer->SetCharType( iCharType );

	m_mapPlayers.insert(std::map< GameObjectId, CPlayer* >::value_type(stID, pPlayer));

	pPlayer->AddRef(); //meiwenti tianjiawanjia
	return pPlayer;
	unguard;
}

BOOL CPlayerMgr::RemovePlayerFromActiveList( GameObjectId stId, DWORD dwFlag )
{
	guardfunc;
	CPlayer* pPlayer = FindByID( stId );
	if( !pPlayer )
	{
		assert( false && "remove player from active list failed" );
		return FALSE;
	}
	if( m_nPlayerQueueCount > 0 )
	{
		for(int i=0; i<m_nPlayerQueueCount; i++)
		{
			if( m_PlayerDistQueue[i].pPlayer == pPlayer )
			{
				m_PlayerDistQueue[i].pPlayer = NULL;
				break;
			}
		}
	}
	 
	m_mapPlayers.erase( stId );

	return TRUE;
	unguard;
}

BOOL CPlayerMgr::AddPlayerToKeepList( CPlayer* pPlayer, BOOL bFast/* = FALSE*/ )
{
	guardfunc;
	//加入这种KeepList的，肯定会由于死亡而被删除
	BOOL bFound = FALSE;
	for( int i = 0; i < m_vectorDeathPlayer.size(); i++ )
	{
		if( pPlayer == m_vectorDeathPlayer[i] )
		{
			bFound = TRUE;
			break;
		}
	}
	if( bFound )
	{
		assert( false && "AddPlayerToKeepList error, same player has found" );
		return FALSE;
	}
	// 不再是激活的
	pPlayer->DeActive();
    if( bFast )
	    pPlayer->SetDeadOverTime( HQ_TimeGetTime() + g_shDeadOverDuration - 100 );
    else
        pPlayer->SetDeadOverTime( HQ_TimeGetTime() );
	m_vectorDeathPlayer.push_back( pPlayer );
	return TRUE;
	unguard;
}


void CPlayerMgr::DeletePlayersExceptMe()
{
	guardfunc;
	std::map<GameObjectId, CPlayer*>::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;
		if( pPlayer && pPlayer == m_pMe )
			continue;
		pPlayer->Destroy();
		delete pPlayer;
	}

	// 这里可能要clear
	m_mapPlayers.clear();
	CleaNpcInfos();

	// 在死亡队列里的人也要清除
	for (int i=0; i<(int)m_vectorDeathPlayer.size(); i++)
	{
		m_vectorDeathPlayer[i]->Destroy();
		delete m_vectorDeathPlayer[i];
	}

	m_vectorDeathPlayer.clear();

	if( m_pMe )
	{
		m_mapPlayers.insert(std::map< GameObjectId, CPlayer* >::value_type(m_pMe->GetID(), m_pMe));
// 		m_mapPlayers[m_pMe->GetID()] = m_pMe;
	}
	ClearPlayerQueue();

	m_DynamicCollisionBsp.Destroy();
	m_DynamicFloorBsp.Destroy();

	m_mapVipPlayer.clear();

	unguard;
}

void CPlayerMgr::DestroyPlayer( CPlayer *pPlayer )
{
	guardfunc;
	pPlayer->ClearAllBodyStatusEff();
	pPlayer->Destroy();
	unguard;
}

BOOL CPlayerMgr::PlayerExit( GameObjectId stId )
{
	guardfunc;

	CPlayer* pPlayer = FindByID( stId );
	if( !pPlayer )
	{
		return FALSE;
	}
	
	// 如果是镖车, 可以骑，在退出前通知它的Master
	if (pPlayer->IsMonster() && pPlayer->GetSubMonsterType() == Object_MonsterProtected && pPlayer->IsCanRide())
	{
		CPlayer *master = FindByID(pPlayer->GetMasterID());
		if (master != NULL && master == m_pMe)
		{
			// 从镖车恢复人形
			MsgRestoreFromBiaocheReq msg;
			GettheNetworkInput().SendMsg(&msg);

			// 隐藏镖车控制界面			
			s_CUI_ID_FRAME_OnBiaoChe.SetVisable(false);
		}
	}	

	// 如果是当前锁定人物，取消锁定
	if( GetLockPlayerID() > -1 && GetLockPlayerID() == stId )
	{
		SetLockPlayerID(-1);
		s_CUI_ID_FRAME_Target.SetPlayer(-1);
	}
	//从活动队列中移出

	if( pPlayer->GetMonsterType() == eMT_IllusionMonster )
	{
		PlayEffect( "Common\\SummonEffect.ini", pPlayer );
		pPlayer->SetFinalRenderAlpha( 0 );
		pPlayer->SetDefaultFinalRenderAlpha( 0 );
        // 等召唤兽alpha为0了再Remove
	}

	else if( pPlayer->IsItem() )
	{
        // 打开包裹与Player ID相同，关闭包裹界面
        if( s_CUI_ID_FRAME_PickUp.IsVisable() && s_CUI_ID_FRAME_PickUp.IsSamePackage(stId) )
        {
            s_CUI_ID_FRAME_PickUp.SetVisable(false);
        }

		if(pPlayer && pPlayer->IsItem())
		{
			s_CUI_ID_FRAME_AutoAttackSet.ReMoveRecordItem(pPlayer->GetID());
		}

		//清空动作队列，主要是处理攻击消息
		pPlayer->ExcuteClearActionQueue();
		RemovePlayerFromActiveList( stId );	

		if( pPlayer->Release() )
		{
			//pPlayer->Destroy();
			DestroyPlayer( pPlayer );
			delete pPlayer;
		}
		else
		{
			//加入暂存队列
			AddPlayerToKeepList( pPlayer );
		}
	}
	else
	{
		pPlayer->Remove( HQ_TimeGetTime() );
	}

	return TRUE;

	unguard;
}

BOOL CPlayerMgr::DeleteDeathPlayer( CPlayer* pPlayer )
{
	guardfunc;
	if( !pPlayer )
	{
		assert( false && "delete death player failed" );
		return FALSE;
	}
	//
	for (int i=0; i<(int)m_vectorDeathPlayer.size(); i++)
	{
		if( pPlayer == m_vectorDeathPlayer[i] )
		{	
			for( int j = 0 ; j < m_nPlayerQueueCount ; ++ j )
			{
				if( m_PlayerDistQueue[j].pPlayer == pPlayer )
				{
					m_PlayerDistQueue[j].bRendered = false;
					m_PlayerDistQueue[j].pPlayer = 0;
					break;
				}
			}
			if( pPlayer->GetRef() <= 0 )
			{
				DestroyPlayer( pPlayer );
				delete pPlayer;
				m_vectorDeathPlayer.erase( m_vectorDeathPlayer.begin()+i );
				
			}			
			return TRUE;
		}
	}
	return FALSE;
	unguard;
}

CPlayer* CPlayerMgr::FindByPt( int x, int y )
{
	guardfunc;
	std::map<GameObjectId, CPlayer*>::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;

		int x1 = 0, y1 = 0;
		if( pPlayer )
		{
			pPlayer->GetMapPos( x1, y1 );
			if( abs(x-x1)<1 && abs(y-y1)<1 )
			{
				if( pPlayer->IsItem() &&
					!pPlayer->IsItemDropDelayOver() )
					continue;
				return pPlayer;
			}
		}
	}
	return NULL;
	unguard;
}

CPlayer* CPlayerMgr::FindByName( const char*szName )
{
	guardfunc;
	std::map<GameObjectId, CPlayer*>::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;
		if( 0 == strcmp( szName,pPlayer->GetName() ) )
			return pPlayer;
	}
	return NULL;

	unguard;
}

//	看到呤唱
//----
void CPlayerMgr::OnSeeIntonate(int iSkill, int iSkillLevel, GameObjectId ScNPcID, GameObjectId TagNpcID, int iPercent, unsigned short usType )
{
	guardfunc;
	CPlayer *pSrc = FindByID(ScNPcID);
	CPlayer *pDst = FindByID(TagNpcID);
	//
	if ((NULL == pSrc))
		return;

	if (pSrc != GetMe() && pSrc->m_cFightStatus.IsHide())
		return;

	IntonateInfo Intonate;
	Intonate.iSkillNo = iSkill;
	Intonate.iSkillLevel = iSkillLevel;

	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( iSkill, iSkillLevel );

	if( pSkill )
	{
		if( pDst )
			pSrc->SetIntonatingTarget( pDst );

		pSrc->SetCanInterruptIntonating(pSkill->bMoveInterrupt);

		if( m_pMe && pSrc == m_pMe )
		{
			m_pMe->SetIntonating( TRUE );
			m_pMe->SetIntonatingStartTime( g_dwLastFrameBeginTime );
			if( usType == 0 ) //吟唱
			{
				short stSingTime = pSkill->ustPrepTime;
// 				if (m_pMe->m_cFightStatus.GetAddIntonateRate() != 0.0f)
// 				{
// 					float fTemp = (1.0f - m_pMe->m_cFightStatus.GetAddIntonateRate())*stSingTime;
// 					stSingTime = fTemp;
// 				}
				if (stSingTime <= 0)
				{
					stSingTime = 1;
				}
				if( pSkill->bShowIntonateBar )      // 需要显示吟唱条
				{
					s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), stSingTime/*pSkill->ustPrepTime*/,
						true, 1, true, true, pSkill->GetSkillName(), false, false, 0, FALSE );
				}				
			}
			else //通道
			{
				if( pSkill->iDurationTime > 0 )
				{
					if( s_CUI_Progress.IsVisable() )
						s_CUI_Progress.SetVisable(false);
					{
						int nDurationTime = pSkill->iDurationTime;										

						s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), nDurationTime/*pSkill->ustPrepTime*/, false,
							1, true, true,
							pSkill->GetSkillName(), false, false,
							0, FALSE );
					}
				}
			}			
		}
		else
		{
			pSrc->SetIntonating( TRUE );
			pSrc->SetIntonatingStartTime( g_dwLastFrameBeginTime );
			pSrc->SwitchIntonateAnim(0,pSkill);
			pSrc-> SetIntonatingDelayTime(pSkill->ustPrepTime) ;
			pSrc-> SetIntonatingName(pSkill->GetSkillName()) ;
		}
	}

	// 引用修改 [11/17/2010 zhangjiayi]
	//lyh去掉引用
	if( pSrc )
		pSrc->AddRef();
	if( pDst )
		pDst->AddRef();

	Intonate.pSrc = pSrc;	//攻击者
	Intonate.pDst = pDst;	//攻击目标
	//
	Intonate.iPercent = iPercent;
	pSrc->GetActionQueue()->Push_Intonate( &Intonate );
	unguard;
}

void CPlayerMgr::OnSeeHoldSkill( int iSkill,int iSkillLevel,GameObjectId iSrcChar,int iPercent )
{
	guardfunc;
	SSeeHoldSkill see;
	see.pSrc = FindByID( iSrcChar );
	if( !see.pSrc )
		return;
	
	see.iSkillID = iSkill;
	see.iSkillLevel = iSkillLevel;
	see.iPercent = iPercent;

	see.pSrc->GetActionQueue()->Push_SeeHoldSkill( &see );
	unguard;
}

void CPlayerMgr::OnSeeDamage(DWORD dwState, const SeeDamageParam& kSeeDamageParam )
{
	guardfunc;
    GameObjectId stDst = kSeeDamageParam.nDst;
    GameObjectId stSrc = kSeeDamageParam.nSrc;
    int iTagNum = kSeeDamageParam.iTagNum;
	int iTagMpNum = kSeeDamageParam.iTagMpNum;
    int iSrcNum = kSeeDamageParam.iSrcNum;
    int iBalanceType = kSeeDamageParam.iBalanceType;
    int iTagHp = kSeeDamageParam.iTagHp;
    int iSrcHp = kSeeDamageParam.iSrcHp;
    int iTagMp = kSeeDamageParam.iTagMp;
    int iSrcMp = kSeeDamageParam.iSrcMp;
    short stTagBackAttackNum = kSeeDamageParam.stTagBackAttackNum;
    short statusId  = kSeeDamageParam.stStatusID;
    short statusLevel = kSeeDamageParam.stLevel;

	//获取攻击者和被攻击者的指针
	CPlayer *pSrc = FindByID( stSrc );
	CPlayer *pDst = FindByID( stDst );

	if ( NULL == pDst )
	{
		// 这是可能的，攻击一个不在视野内player
		return;
	}

	/////////Server对状态施放源的处理有问题，所以下面先屏蔽源的处理

	if( pDst == GetMe() )
	{
		thePlayerRole.SetPlayerHP(iTagHp);
		thePlayerRole.SetPlayerMP(iTagMp);
	}

    if(pDst == GetMe() ||pSrc == GetMe() )
    {
#ifdef _DEBUG
        const char* pszDstName = pDst->GetName();
        const char* srcName = pSrc->GetName();
#endif
        const char* pszName = NULL;
        if(pDst == GetMe() && pSrc == GetMe())
            pszName = theXmlString.GetString(eText_Your);
        else if(pSrc == GetMe())
             pszName = pDst->GetName();
        else if(pDst == GetMe())
            pszName = theXmlString.GetString(eText_Your);

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus(statusId,statusLevel);
        if(pStatus)
        {
            char szWord[128];
            memset(szWord,0,sizeof(szWord));
            if(iTagNum < 0)
                MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_AddHp),pszName,statusLevel,pStatus->GetItemName(),-iTagNum);
            else if(iTagNum > 0)
                MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_ReduceHp),pszName,statusLevel,pStatus->GetItemName(),iTagNum);

            if(iTagNum != 0)
			{
               s_CUI_ChatInfoBox.AddInfo(szWord,Color_Config.getColor(CC_CHAT_TEAM),MsgChat::CHAT_TYPE_FIGHTINFO);
			}
			if(iTagMpNum < 0)
			{
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_RestoreMp),pszName,statusLevel,pStatus->GetItemName(),-iTagMpNum);
				s_CUI_ChatInfoBox.AddInfo(szWord,Color_Config.getColor(CC_CHAT_TEAM),MsgChat::CHAT_TYPE_FIGHTINFO);
			}else if (iTagMpNum > 0) //lyh++
			{
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_ReduceMP),theXmlString.GetString(eText_Your),statusLevel,pStatus->GetItemName(),iTagMpNum);
				s_CUI_ChatInfoBox.AddInfo(szWord,Color_Config.getColor(CC_CHAT_TEAM),MsgChat::CHAT_TYPE_FIGHTINFO);
			}
        }
    }
		
	if (NULL != pDst)
	{
        //pDst->SetHPInfo_HPChange(-iTagNum);
		pDst->SetHPInfo_HP(iTagHp);//by vvx 2013.8.5
		if( iTagNum > 0 )
		{
			if( (pSrc && pSrc == m_pMe) || pDst == m_pMe )
			{
                bool bPlayer = false;
                if(
                    ((pSrc && pSrc == m_pMe) && pDst->IsPlayer())
                    ||((pDst == m_pMe) &&(pSrc&&pSrc->IsPlayer()))
                   )
                    bPlayer = true;
				pDst->OnShowFlyText( iBalanceType, iTagNum,0,0,bPlayer);
			}

		}
		else if( iTagNum < 0 )
		{
			if( pDst )
			{
				D3DXVECTOR3 pos = pDst->GetPos();
				pos.z += g_fTheRoleBBoxHeight;

				int xEffect = 0,yEffect = 0;
				World2Screen( pos,xEffect,yEffect );

				g_pFlyTextEffect->Create(CFlyTextEffect::eNumberGreen, xEffect, yEffect, -1 * iTagNum, pDst->GetID(), FALSE, pos, 0, false );
			}
		}
		if(iTagMpNum < 0)
		{
			if( pDst )
			{
				D3DXVECTOR3 pos = pDst->GetPos();
				pos.z += g_fTheRoleBBoxHeight;

				int xEffect = 0,yEffect = 0;
				World2Screen( pos,xEffect,yEffect );

				g_pFlyTextEffect->Create(CFlyTextEffect::eNumberBlue, xEffect, yEffect, -1 * iTagMpNum, pDst->GetID(), FALSE, pos, 0, false );
			}
		}
	}

	if (NULL != pSrc && pSrc != pDst)
	{
		if( iSrcNum > 0 )
		{
			if( (pDst && pDst == m_pMe) || pSrc == m_pMe )
			{
				pSrc->OnShowFlyText( iBalanceType, iSrcNum, stTagBackAttackNum );
			}
		}
		else if ( iSrcNum < 0 )
		{
			if( pSrc )
			{
				D3DXVECTOR3 pos = pSrc->GetPos();
				pos.z += g_fTheRoleBBoxHeight;

				int xEffect = 0,yEffect = 0;
				World2Screen( pos,xEffect,yEffect );

				g_pFlyTextEffect->Create(CFlyTextEffect::eNumberGreen, xEffect, yEffect, -1 * iSrcNum, pSrc->GetID(), FALSE, pos, 0, false );
			}
		}
	}

	//如果目标死亡，切换到死亡动画
	if (_HAS_FLAG(dwState, eFIGHT_BEKILLED))
	{
		pDst->SetHPInfo_HP(0);
		pDst->WillDie();
		pDst->OnClearAllBodyStatusByDead();
		//pDst->OnClearAllBodyStatus();
		pDst->AddDeathTask();
		//lyh去掉引用
		if( !pDst->IsDead() )
			pDst->AddRef();
		pDst->SetCharDead( TRUE );
		pDst->UpdateBaseData(HQ_TimeGetTime());
		pDst->SwitchDieAnim();
		//设置死亡等待死亡后才释放
		//pDst->AddRef();

        if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight()
            &&(pDst&&pDst->IsMonster())
            &&((pSrc&&pSrc == GetMe())
            ||(pSrc&&pSrc->GetMasterID() > -1 && theHeroGame.GetPlayerMgr()->FindByID(pSrc->GetMasterID()) == GetMe())))
        {//处于自动挂机中
            s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().EnterWait(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().s_dwElapseTime);
            s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().ResetSkillSeq();  //
        }

		// added, jiayi, [2009/12/29]
		// 你被x杀死的提示
        if( pSrc && pDst )
        {
		    if( pDst==GetMe() )
		    {  
		       // 你被人杀了	
		       char szContent[256] = {0};			
		       MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pSrc->GetName());			
			   s_CUI_ID_FRAME_ESCDLG.SetAttackerName( pSrc->GetName() );
		       CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_BeKilled_Info, szContent );
		    }
            else if( pDst->IsPlayer() )// 判断是否玩家攻击玩家，是则显示击杀消息
            {
                if( pSrc->IsPlayer() || (pSrc->IsMonster() && pSrc->GetMasterID() > -1) )
                {
                    char szContent[256] = {0};			
                    char *szDestName = pDst->GetName();
                    char *szMe = NULL;
                    CPlayer* pMaster = NULL;
                    if( pSrc->IsPlayer() )
                        szMe = pSrc->GetName();
                    else
                    {
                        pMaster = theHeroGame.GetPlayerMgr()->FindByID(pSrc->GetMasterID());
                        if( pMaster )
                            szMe = pMaster->GetName();
                    }

                    if( szDestName && szDestName[0] != '\0'&& szMe && szMe[0] != '\0')
                    {
                        char szResult[MAX_PATH] = {0};
                        if( pSrc->IsRole() || (pMaster && pMaster == theHeroGame.GetPlayerMgr()->GetMe()) )
                        {
                            MeSprintf_s(szResult,sizeof(szResult)/sizeof(char) - 1, theXmlString.GetString( eText_PKResult_YouKillPlayer ), szDestName);
                        }
                        else
                        {
                            MeSprintf_s(szResult,sizeof(szResult)/sizeof(char) - 1, theXmlString.GetString( eText_PKResult ), szMe, szDestName);
                        }
                        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Kill_Info, szResult );
                    }
                }
            }
        }
	}
	unguard;
}
//----
//	看到攻击
//----
void CPlayerMgr::OnSeeAttack( SAttackInfo* pAttackInfo, DWORD dwState, const SeeAttackParam& kSeeAttackParam )
{
    CPlayer* pAttacker = kSeeAttackParam.pAttacker;
    CPlayer* pDst = kSeeAttackParam.pDst;
    short stAttackerX = kSeeAttackParam.stAttackerX;
    short stAttackerY = kSeeAttackParam.stAttackerY;
    int nTagHp = kSeeAttackParam.nTagHp; 
    int iTagNum = kSeeAttackParam.iTagNum;
    int iSrcHpNum = kSeeAttackParam.iSrcHpNum;
    int iBalanceType = kSeeAttackParam.iBalanceType;
    short stTagBackAttackNum = kSeeAttackParam.stTagBackAttackNum;

	guardfunc;
	if( !pDst )
	{
		OutputDebugString( "OnSeeAttack目标不存在" );
		return;
	}
	//
	if (pDst == GetMe())
	{
		thePlayerRole.SetPlayerHP(nTagHp);
		thePlayerRole.SetPlayerMP(kSeeAttackParam.nTagMp);
	}
	//调整攻击者的位置	
	if( _HAS_FLAG( dwState, eFIGHT_BEKILLED ) )
	{
		pDst->WillDie();
        if ( pAttacker )
        { 
            if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight()&&(pDst&&pDst->IsMonster())
                &&(pAttacker == GetMe()||(pAttacker->GetMasterID() > -1 && theHeroGame.GetPlayerMgr()->FindByID(pAttacker->GetMasterID()) == GetMe())))
            {//处于自动挂机中
                s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().EnterWait(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().s_dwElapseTime);
                s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().ResetSkillSeq();  //
            }

            char szContent[256] = {0};
            if ( pDst==GetMe() )
            { // 你被人杀了
                if ( pAttacker->GetMasterID() != -1)
                { // 如果是召唤怪
                    CPlayer* pMasterPlayer = FindByID( pAttacker->GetMasterID() );
                    if ( pMasterPlayer )
                        MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pMasterPlayer->GetName());
                    else // 出错补救
                        MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pAttacker->GetName());
                }
                else
                { // 如果不是召唤怪
                    MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pAttacker->GetName());
                }
				s_CUI_ID_FRAME_ESCDLG.SetAttackerName( pAttacker->GetName() );
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_BeKilled_Info, szContent );
            }
        }
	}

    // 攻击者被反伤杀死
	if( _HAS_FLAG( dwState, eFIGHT_SELFBEKILLED ) )
	{
        if( pAttacker )
		    pAttacker->WillDie();
        if ( pDst )
        { 
            char szContent[256] = {0};
            if ( pAttacker==GetMe() )
            { // 你被人杀了
                if ( pDst->GetMasterID() != -1)
                { // 如果是召唤怪
                    CPlayer* pMasterPlayer = FindByID( pDst->GetMasterID() );
                    if ( pMasterPlayer )
                        MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pMasterPlayer->GetName());
                    else // 出错补救
                        MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pDst->GetName());
                }
                else
                { // 如果不是召唤怪
                    MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pDst->GetName());
                }
				s_CUI_ID_FRAME_ESCDLG.SetAttackerName( pAttacker->GetName() );
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_BeKilled_Info, szContent );
            }
        }
	}


	//增加攻击者，使用一个攻击动作的动画
	SAttackInfoRecord r;
	r.dwState = dwState;
	r.iBalanceType = iBalanceType;
	r.iTagHp = nTagHp;
	r.iTagNum = iTagNum;
    r.iSrcHpNum = iSrcHpNum;
	r.iTagMp = kSeeAttackParam.nTagMp;
	r.iSrcMpNum = kSeeAttackParam.iSrcMpNum;
	r.iTagMpNum = kSeeAttackParam.iTagMpNum;
	r.nTargetID = pDst->GetID();
    r.stTagBackAttackNum = stTagBackAttackNum;
	r.nShieldHp = kSeeAttackParam.nShieldHp;
	pAttackInfo->AddRecord( &r );
	unguard;
}

void CPlayerMgr::ReqRelive( bool bBornCity ,bool bBySkill,short stOriginRelieveType,BYTE byAddtion)
{
	guardfunc;
	MsgReqRelive msg;
	if (bBySkill == false)
	{
		if ( bBornCity )
		{
			msg.byBornPos = eReliveTypeCity;
		}
		else
		{
			msg.byBornPos = eReliveTypeNearPos;
		}
	}
	else
	{
		if (bBornCity)
		{
			msg.byBornPos = eReliveTypeCity;
		}
		else
		{
			msg.byBornPos = eReliveTypeOrigin;
		}
	}
	if (stOriginRelieveType > -1)
	{
		switch(stOriginRelieveType)
		{
		case eReliveOriginNon:
			msg.byBornPos = eReliveTypeOrigin;
			break;
		case eReliveOriginAllHpMp:
			msg.byBornPos = eReliveTypeOriginFullHpMP;
		default:
			break;
		}
	}
	msg.byAddtion = byAddtion;
	GettheNetworkInput().SendMsg( &msg,msg.GetLength() );
	if( m_pMe )
		m_pMe->SetDeadOver( false );
	unguard;
}

void CPlayerMgr::Destroy()
{
	guardfunc;
	DeletePlayersExceptMe();
	if( m_pMe )
	{
		int n = m_mapPlayers.erase( m_pMe->GetID() );	
		m_pMe->Destroy();	
		delete m_pMe;
		m_pMe = NULL;
	}

	std::map<GameObjectId, CPlayer*>::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* p = it->second;
		assert( false && "player not released" );
	}
	for( int i=0; i<MaxMainpleCnt; i++ )
	{
		GTeamFlag[i].Destroy();
	}

	m_vectorNoLogicPlayer.clear();
	
	DestroyCamera();
	unguard;
}

void CPlayerMgr::RenderPlayer( LPDIRECT3DDEVICE9 pDevice,int iPlayerID )
{

	guardfunc;
	unguard;
}

void CPlayerMgr::SawOneItem( Msg *pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgItemEnterMySight);
	MsgItemEnterMySight *pItemEnter = (MsgItemEnterMySight *)pMsg;

	//谁进入视野
	if( m_pMe && pMsg->header.stID == m_pMe->GetID() )
	{
		assert( false );
		char temp[1024] = {0};
        MeSprintf_s(temp,1024,"SawOneItem 包裹ID和Me ID相同 %d!",pMsg->header.stID);
        LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
        return;
	}
    // 判断是否在同个（动态）地图ID
    if( thePlayerRole.GetGameMapId() != pItemEnter->nMapID )
        return;

	AddPlayer( pMsg->header.stID,Object_Item,false );
	CPlayer* pPlayer = FindByID( pMsg->header.stID );

	if( pPlayer )
	{
		pPlayer->SetCharType( Object_Item );
		pPlayer->JumpToMapPos( pItemEnter->fX, pItemEnter->fY, 0.0f );

		pPlayer->SetWillPlayDropAnim(pItemEnter-> m_bFirstEnterSight);
		pPlayer->SetGuildId( GuildDefine::InitID );
		pPlayer->SetModelColor( 0 );

		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItemEnter->ustItemId );
		if( pItemDetail )
		{
			char szBuf[MAX_PATH] = {0};

			pPlayer->SetLevel( pItemDetail->ustLevel );
			
			if( const_ustItemMoney == pItemEnter->ustItemId)
			{
				_snprintf( szBuf, sizeof(szBuf)-1, "%s:%d",
					pItemDetail->GetItemName()
					,pItemDetail->dwCost);
			}
			else
			{
				if( !pItemDetail->IsExclusive() && pItemEnter->ustItemCount  > 1 )
				{
					_snprintf( szBuf, sizeof(szBuf)-1, "%s(%d)",
						//pItemDetail->szItemName.c_str(),
						pItemDetail->GetItemName(),
						pItemEnter->ustItemCount /*item.itembaseinfo.ustItemCount */);
				}
				else
				{
					_snprintf( szBuf,sizeof(szBuf)-1, "%s",
						//pItemDetail->szItemName.c_str() );
						pItemDetail->GetItemName() );
				}
			}

			Common::_tstring tstrName( szBuf );
			S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
			strncpy(szBuf, tstrName.c_str(), MAX_PATH-1 );

			pPlayer->SetName( szBuf );			
			pPlayer->SetModelId( pItemDetail->ustModelIDOverGround );
			pPlayer->SetBodySize( 1.0f );//暂定默认为1.0f

            // 判断包裹能否拾取，播放拾取特效
			if( GetMe() /*&&  ( NorPackageItemID == pItemEnter->ustItemId || MidPackageItemID == pItemEnter->ustItemId || AdvPackageItemID == pItemEnter->ustItemId )*/ )
            {
                //pPlayer->SetName("");
                BOOL bCanAccess = FALSE;
				if( pItemEnter->nCount == 0 )	// 对所有人可见
				{
					// 没有延时显示
					if( pItemEnter->byClientDisplayDelaySecond == 0 && pPlayer->m_nCollectionEffectID == -1 )
					{
						pPlayer->m_nCollectionEffectID = PlayEffect("common\\QuestItem.ini",pPlayer);
					}
					bCanAccess = TRUE;
					pPlayer->m_bCanPick = true;
				}
				else
					for( int iPlayer = 0; iPlayer < pItemEnter->nCount; ++iPlayer )
					{
						uint32 iPlayerDBID = pItemEnter->dwPickPlayerID[iPlayer];
						if( thePlayerRole.IsRole(iPlayerDBID) )
						{
							// 没有延时显示
							if( pItemEnter->byClientDisplayDelaySecond == 0 && pPlayer->m_nCollectionEffectID == -1 )
							{
								pPlayer->m_nCollectionEffectID = PlayEffect("common\\QuestItem.ini",pPlayer);
							}
							bCanAccess = TRUE;
							pPlayer->m_bCanPick = true;
							break;
						}
					}

                if( !bCanAccess )
                {
                    if(pPlayer->m_nCollectionEffectID != -1 )
                    {
                        IEffect* pEffect = GetEffectMgr()->GetEffect( pPlayer->m_nCollectionEffectID );
                        if( pEffect )
                        {
                            pEffect->SetDead();
                        }
                        pPlayer->m_nCollectionEffectID = -1;
                    }
                    pPlayer->m_bCanPick = false;
                }
            }

			_snprintf( szBuf, 255, "ustModelIDOverGround = %d\n", pItemDetail->ustModelIDOverGround );
			OutputDebugString( szBuf );

		}
		else
		{
			pPlayer->SetName( "Cannot find the item info!!!" );
		}

		pPlayer->AutoCS();
			
		pPlayer->SetDisplayAfterTime( HQ_TimeGetTime()+pItemEnter->byClientDisplayDelaySecond*1000 );

		//物品掉落指引
		if( thePlayerRole.IsFinishedIntroduce(INTRO_DROPBAG_OPEN) == false )
		{
			CIntroductionManager::Instance()->ShowTipWithPlayer( INTRO_DROPBAG_OPEN, pPlayer );
			thePlayerRole.SetFinishedIntroduce(INTRO_DROPBAG_OPEN);
		}
	}
	unguard;
}

void RenderPlayerInMiniMap( int iCharType,bool bRole,bool bTeammate,int x,int y );
void CPlayerMgr::RenderMiniMap( void )
{
	guardfunc;

	unguard;
}

void CPlayerMgr::RenderPlayerInfo( LPDIRECT3DDEVICE9 pDevice )
{
	guardfunc;

	std::map<GameObjectId, CPlayer*>::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;
		if( pPlayer )
		{
			if( pPlayer == m_pMe && !g_bRenderRole )
			{
				if( pPlayer->IsNeedRender() )
				{
					pPlayer->RenderText(pDevice);

					if (pPlayer->IsNeedShowShadowDecal())
					{
						pPlayer->UpdateDecalShadow();
					}
				}
				continue;
			}

            if( pPlayer->IsNeedRender() )
				pPlayer->Render( pDevice, 0xff00ff00, 1 );
		}
	}
	
	for (int i=0; i<(int)m_vectorDeathPlayer.size(); i++)
	{
		CPlayer* pPlayer = m_vectorDeathPlayer[i];
		if( !pPlayer || !pPlayer->IsNeedRender() )
			continue;
		pPlayer->Render( pDevice, 0xff00ff00, 1 );
	}

    // 统计假影子个数
    BOOL bCombineRenderShadowDecal = FALSE;
    int iShadowCount = 0;
    for( int i = m_nPlayerQueueCount - 1; i >= 0 ; --i )
    {
        // 掉落物品和采集物品不需要画假影子
        if( m_PlayerDistQueue[i].pPlayer
            && !m_PlayerDistQueue[i].pPlayer->IsItem()
            && !(m_PlayerDistQueue[i].pPlayer->IsMonster() && (m_PlayerDistQueue[i].pPlayer->IsCollection(false) ) ) )
        {
            iShadowCount++;
        }
		// 如果在开店，更新与摄像机距离
		if( m_PlayerDistQueue[i].pPlayer &&
			m_PlayerDistQueue[i].pPlayer->IsOpenPrivateShop() )
		{
			m_PlayerDistQueue[i].pPlayer->UpdateDistanceToPickRay( m_vFrom.x, m_vFrom.y );
		}
    }
	
    
//    if( GetShaderMgr()->GetShadowType() == eShadow_Fake ||
//		!SystemSetting::Instance()->IsAdvance() )
    {
        // 可见人物个数超过30则合并渲染假影子
        if( m_nPlayerQueueCount >= 30 && iShadowCount >= 30 )
        {
            bCombineRenderShadowDecal = TRUE;
            ((CWSRender*)SwGlobal::GetRender())->StartCombineShadowDecal();
        }
        // 合并影子数据
        for(int i=0; i<m_nPlayerQueueCount; i++)
        {
            // 掉落物品和采集物品不需要画假影子
            if( m_PlayerDistQueue[i].pPlayer 
                && !m_PlayerDistQueue[i].pPlayer->IsItem()
                && !(m_PlayerDistQueue[i].pPlayer->IsMonster() && (m_PlayerDistQueue[i].pPlayer->IsCollection(false) ) ) )
            {
                m_PlayerDistQueue[i].pPlayer->RenderShadowDecal(bCombineRenderShadowDecal);
            }
        }
        // 合并渲染
        if( bCombineRenderShadowDecal )
        {
            ((CWSRender*)SwGlobal::GetRender())->EndCombineShadowDecal();
            ((CWSRender*)SwGlobal::GetRender())->RenderCombineShadowDecal();
        }
    }

	// 需放在渲染影子后面
	qsort(m_PlayerDistQueue, m_nPlayerQueueCount, sizeof(PlayerRenderLimitData), ComparePlayerDist3);
	for( int i = m_nPlayerQueueCount - 1; i >= 0 ; --i )
	{
		// render shop info
		if( m_PlayerDistQueue[i].pPlayer && m_PlayerDistQueue[i].pPlayer->IsPlayer() )
		{
			m_PlayerDistQueue[i].pPlayer->RenderPrivateShopInfo();
		}
	}

	CFootPrintMgr::Instance()->Render();
	MeRenderManager::Instance()->DoRender(false);
	unguard;
}

void CPlayerMgr::RenderPlayerTeamFlag()
{
	for( int i = m_nPlayerQueueCount - 1; i >= 0 ; --i )
	{
		// render shop info
		if( m_PlayerDistQueue[i].pPlayer && m_PlayerDistQueue[i].pPlayer->IsPlayer() )
		{
			m_PlayerDistQueue[i].pPlayer->RenderTeamFlag();
			m_PlayerDistQueue[i].pPlayer->RenderTeamBattleFlag();
			m_PlayerDistQueue[i].pPlayer->RenderRankTitle(); //这个与队伍无关，是为了减少循环
			m_PlayerDistQueue[i].pPlayer->RenderCountryTitle(); //这个也无关，是为了减少循环
		}
	}
}

void CPlayerMgr::RenderPlayerChatInfo()
{
	std::map<GameObjectId, CPlayer*>::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;
		if( pPlayer )
		{
			if( pPlayer == m_pMe && !g_bRenderRole )
			{
				continue;
			}

			if( pPlayer->IsNeedRender() )
				pPlayer->RenderChatInfo();
		}
	}

	for (int i=0; i<(int)m_vectorDeathPlayer.size(); i++)
	{
		CPlayer* pPlayer = m_vectorDeathPlayer[i];
		if( !pPlayer || !pPlayer->IsNeedRender() )
			continue;
		pPlayer->RenderChatInfo();
	}
}

void CPlayerMgr::RenderAlpha( LPDIRECT3DDEVICE9 pDevice )
{
	guardfunc;
	for( int i=0; i<m_vtAlphaPlayer.size(); i++ )
	{
		CPlayer* pPlayer = FindByID(m_vtAlphaPlayer[i]);
		if( pPlayer )
		{
			if( pPlayer->IsNeedRender() )
				pPlayer->RenderChar( pDevice );
			else
			{
				if( pPlayer->GetDistanceToRole() > GetFarRole() )
				{
					float fAlpha = pPlayer->GetCurRenderAlpha();
					if( fAlpha > 0.0618f )
					{
						fAlpha -= 0.000618f*g_dwLastFrameCostTime;
						if( fAlpha < 0 )
							fAlpha = 0;
						pPlayer->SetCurRenderAlpha( fAlpha );
						pPlayer->RenderChar( pDevice );
					}
				}
			}
		}
		if( g_bShowModelBBox )
		{
			Box *pBox = pPlayer->GetWorldBBox();
			if( pBox )
				GetDrawer()->DrawBox3D( pBox, 0xffffffff );
		}
	}
	MeRenderManager::Instance()->DoRender(false);
	return ;
	unguard;
}

void CPlayerMgr::RenderShadow( LPDIRECT3DDEVICE9 pDevice )
{
	if( !g_bShowPlayer )
		return;

	for( int i = 0 ; i < m_nPlayerQueueCount ; ++ i )
	{
		if( m_PlayerDistQueue[i].bRendered &&
			m_PlayerDistQueue[i].pPlayer &&
			!m_PlayerDistQueue[i].pPlayer->IsCollection( false ) )
			m_PlayerDistQueue[i].pPlayer->RenderShadow(pDevice);
	}
			
	MeRenderManager::Instance()->DoRender(false);
}

int g_iLoadModelPerFrame = 1;	// 每帧加载玩家个数

void CPlayerMgr::Render( LPDIRECT3DDEVICE9 pDevice, int nType )
{
	guardfunc;
	if( !g_bShowPlayer )
		return;

	BOOL bFastRender = FALSE;

	float fOldLod = GetMe3dConfig()->GetMipLodBais();

	GetMe3dConfig()->SetMipLodBais(m_fPlayerLod);
	m_vtAlphaPlayer.clear();
	std::map<GameObjectId, CPlayer*>::iterator it;

	// 清空统计数据
	nRenderPlayerCount	= 0;
	nRenderVertexCount	= 0;
	nRenderFaceCount	= 0;

	{
		// 清空渲染队列
		m_nPlayerQueueCount = 0;
		memset(m_PlayerDistQueue, 0, PLAYER_RENDER_QUEUE_MAX*sizeof(PlayerRenderLimitData));

		for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
		{
			CPlayer* pPlayer = it->second;

			if( !pPlayer )
				continue;

            // 不可拾取包裹，不显示
            if( pPlayer->IsItem() )
            {
                if( !pPlayer->m_bCanPick || !pPlayer->IsItemDropDelayOver() )
                    continue;
            }
            // 不可见的召唤物
            if( !pPlayer->IsVisibleToOtherPlayer() )
            {
                if( GetMe() )
                {
                    if( GetMe()->GetID() != pPlayer->GetMasterID() )
                        continue;
                }
                else
                    continue;
            }

			if( pPlayer->IsNpc() && pPlayer->IsHide() )
				continue;

			if( pPlayer->IsNeedRender() && m_nPlayerQueueCount < PLAYER_RENDER_QUEUE_MAX )
			{
				// 插入渲染队列
				m_PlayerDistQueue[m_nPlayerQueueCount++].pPlayer = pPlayer;
			}
		}
		for (int i=0; i<(int)m_vectorDeathPlayer.size(); i++)
		{
			CPlayer* pPlayer = m_vectorDeathPlayer[i];
			if( !pPlayer )
				continue;

            // 不可拾取包裹，不显示
            if( pPlayer->IsItem() && !pPlayer->m_bCanPick )
                continue;

            // 不可见的召唤物
            if( !pPlayer->IsVisibleToOtherPlayer() )
            {
                if( GetMe() )
                {
                    if( GetMe()->GetID() != pPlayer->GetMasterID() )
                        continue;
                }
                else
                    continue;
            }

			if( pPlayer->IsNeedRender() && m_nPlayerQueueCount < PLAYER_RENDER_QUEUE_MAX )
			{
				// 插入渲染队列
				m_PlayerDistQueue[m_nPlayerQueueCount++].pPlayer = pPlayer;
			}
		}

		//渲染玩家
		int nVertexCount = 0;
		int nFaceCount = 0;

		int iLoadModel = g_iLoadModelPerFrame;	// 每帧只加载3个玩家
		// 如果可用物理内存小于50M，则不加载玩家
#ifdef _DEBUG
		bool bCanLoadPlayer = true;
		bool bWantLoadPlayer = false;
#endif
		if( theHeroGame.GetAvailPhyMemory() < 50 * 1024 * 1024 )
		{
			iLoadModel = 0;
#ifdef _DEBUG
			bCanLoadPlayer = false;
#endif
		}

		if( m_nPlayerRenderLimit < PLAYER_RENDER_MAX && m_nPlayerQueueCount > 1 && m_nPlayerQueueCount > m_nPlayerRenderLimit )
		{
			// 远近排序，按同屏人数限制及优先级高低进行渲染
			qsort(m_PlayerDistQueue, m_nPlayerQueueCount, sizeof(PlayerRenderLimitData), ComparePlayerDist);
			int nRenderedCount = 0;	// 已渲染人数

            // 玩家目标必须显示(例外: 玩家变身镖车状态时，选中镖车也不显示)
            CPlayer* pTargetPlayer = NULL;
            if ( GetLockPlayerID() >= 0 )
            {
                pTargetPlayer = FindByID( GetLockPlayerID() );
				BOOL isNeedShowTargetPlayer = TRUE;
                if ( pTargetPlayer != NULL )
                {
					for (int j=0; j<m_nPlayerQueueCount; j++)
					{
						if ( pTargetPlayer == m_PlayerDistQueue[j].pPlayer /*&& IsPlayerTypeRender(EPRF_TARGET)*/)
						{
							CPlayer *pMaster = FindByID( pTargetPlayer->GetMasterID() );
							if ( pMaster != NULL )
							{
								// 如果在镖车状态，则不渲染
								if ( pMaster->IsYabiaoState() )
								{
									isNeedShowTargetPlayer = FALSE;									
								}							
							}

							m_PlayerDistQueue[j].bRendered = isNeedShowTargetPlayer;
							break;
						}
						else
						{
							m_PlayerDistQueue[j].bRendered = FALSE;
						}
					}
#ifdef NEW_PLAYER_LOAD
					// 如果模型未加载，则加载模型
					if( !pTargetPlayer->GetAnim() )
					{
						// 加载模型
						if( !pTargetPlayer->IsModelLoaded() )
						{
							pTargetPlayer->LoadModel();
							if( iLoadModel > 0 )
								--iLoadModel;
						}
#ifdef _DEBUG
						bWantLoadPlayer = true;
#endif
					}
					else
#endif
					{
						nVertexCount = 0;
						nFaceCount = 0;

						if (isNeedShowTargetPlayer)
							pTargetPlayer->RenderChar( pDevice, nType, &nVertexCount, &nFaceCount);
						// 掉落地上的装备，或可采集物品不算在统计人数判断里
						if( !pTargetPlayer->IsItem() && !pTargetPlayer->IsCollection(false) )
							nRenderedCount++;

						// 统计渲染数据
						nRenderPlayerCount++;
						nRenderVertexCount += nVertexCount;
						nRenderFaceCount += nFaceCount;
					}
                }
            }

            // PLAYER_RENDER_DIST_MIN范围内，渲染优先级最高的人物
			for( int i = 0; i<m_nPlayerQueueCount; i++ )
			{
				CPlayer* pPlayer = m_PlayerDistQueue[i].pPlayer;
				if( !pPlayer || m_PlayerDistQueue[i].bRendered )
					continue;

				if( pPlayer == m_pMe && !g_bRenderRole )
					continue;

				// 渲染距离大于PLAYER_RENDER_DIST_MIN，或渲染人数大于限制人数
				if( pPlayer->GetDistanceToRole() > PLAYER_RENDER_DIST_MIN
				 || nRenderedCount >= m_nPlayerRenderLimit )
					break;

                // 优先渲染自己，NPC，队友，好友，掉落物品，采集物品，和召唤兽
                if( IsPlayerCanRender(pPlayer, TRUE) || IsPlayerCanRenderEX(pPlayer, TRUE))
				{
					m_PlayerDistQueue[i].bRendered = TRUE;
#ifdef NEW_PLAYER_LOAD
					// 如果模型未加载，则加载模型
					if( !pPlayer->GetAnim() )
					{
						// 加载模型
						if( !pPlayer->IsModelLoaded() && iLoadModel > 0 )
						{
							pPlayer->LoadModel();
							--iLoadModel;
						}
#ifdef _DEBUG
						bWantLoadPlayer = true;
#endif
					}
					else
#endif
					{
						nVertexCount = 0;
						nFaceCount = 0;

						pPlayer->RenderChar( pDevice, nType, &nVertexCount, &nFaceCount);
						// 掉落地上的装备，或可采集物品不算在统计人数判断里
						if( pPlayer && !pPlayer->IsItem() && !pPlayer->IsCollection(false) )
							nRenderedCount++;

						// 统计渲染数据
						nRenderPlayerCount++;
						nRenderVertexCount += nVertexCount;
						nRenderFaceCount += nFaceCount;
					}
				}
			}

			// 还能渲染其他玩家
			if( nRenderedCount < m_nPlayerRenderLimit )
			{
				for( int i = 0; i<m_nPlayerQueueCount; i++ )
				{
                    CPlayer* pPlayer = m_PlayerDistQueue[i].pPlayer;
					if( m_PlayerDistQueue[i].bRendered || !pPlayer )
                        continue;

                    if( !IsPlayerCanRender(pPlayer) )
						if (!IsPlayerCanRenderEX(pPlayer))
                        continue;

					m_PlayerDistQueue[i].bRendered = TRUE;
#ifdef NEW_PLAYER_LOAD
					// 如果模型未加载，则加载模型
					if( !pPlayer->GetAnim() )
					{
						// 加载模型
						if( !pPlayer->IsModelLoaded() && iLoadModel > 0 )
						{
							pPlayer->LoadModel();
							--iLoadModel;
						}
#ifdef _DEBUG
						bWantLoadPlayer = true;
#endif
					}
					else
#endif
					{
						nVertexCount = 0;
						nFaceCount = 0;

						pPlayer->RenderChar( pDevice, nType, &nVertexCount, &nFaceCount );
						// 掉落地上的装备，或可采集物品不算在统计人数判断里
						if( !pPlayer->IsItem() && !pPlayer->IsCollection(false) )
							nRenderedCount++;

						// 统计渲染数据
						nRenderPlayerCount++;
						nRenderVertexCount += nVertexCount;
						nRenderFaceCount += nFaceCount;

						if( nRenderedCount >= m_nPlayerRenderLimit )
							break;
					}
				}
			}
			int nNum = min(m_nPlayerQueueCount,m_nPlayerRenderLimit);
			ShowMosterTip(nNum);
		}
		else
		{
            // 玩家目标必须显示(例外: 玩家变身镖车状态时，选中镖车也不显示)
            CPlayer* pTargetPlayer = NULL;

            if( GetLockPlayerID() >= 0 )
            {
                pTargetPlayer = FindByID( GetLockPlayerID() );
				BOOL isNeedShowTargetPlayer = TRUE;
                if( pTargetPlayer )
                {
					for(int j=0; j<m_nPlayerQueueCount; j++)
					{
						if( pTargetPlayer == m_PlayerDistQueue[j].pPlayer /*&& m_nPlayerRenderFlag & EPRF_TARGET*/)
						{
							CPlayer *pMaster = FindByID( pTargetPlayer->GetMasterID() );
							if ( pMaster != NULL )
							{
								// 如果在镖车状态，则不渲染
								if ( pMaster->IsYabiaoState() )
								{
									isNeedShowTargetPlayer = FALSE;									
								}							
							}

							m_PlayerDistQueue[j].bRendered = isNeedShowTargetPlayer;
							break;
						}
					}
#ifdef NEW_PLAYER_LOAD
					// 如果模型未加载，则加载模型
					if( !pTargetPlayer->GetAnim() )
					{
						// 加载模型
						if( !pTargetPlayer->IsModelLoaded() && iLoadModel > 0 )
						{
							pTargetPlayer->LoadModel();
							--iLoadModel;
						}
#ifdef _DEBUG
						bWantLoadPlayer = true;
#endif
					}
					else
#endif
					{
						nVertexCount = 0;
						nFaceCount = 0;

						if (/*m_nPlayerRenderFlag & EPRF_TARGET &&*/ isNeedShowTargetPlayer)
							pTargetPlayer->RenderChar( pDevice, nType, &nVertexCount, &nFaceCount);

						// 统计渲染数据
						nRenderPlayerCount++;
						nRenderVertexCount += nVertexCount;
						nRenderFaceCount += nFaceCount;
					}
                }
            }

            // 不限制人数
			int nRenderMax = min(m_nPlayerQueueCount, PLAYER_RENDER_MAX);
			for( int i = 0; i<nRenderMax; i++ )
			{
				nVertexCount = 0;
				nFaceCount = 0;
				CPlayer* pPlayer = m_PlayerDistQueue[i].pPlayer;				
				if( pPlayer )
				{
					BOOL isRenderPlayer = IsPlayerCanRender(pPlayer);
					if (!isRenderPlayer)
					{
						isRenderPlayer = IsPlayerCanRenderEX(pPlayer);
					}
					
					if (isRenderPlayer)
						pPlayer->SetNeedRender();
					else
						pPlayer->ResetNeedRender();

					//if (pPlayer->IsNpc())
					//pPlayer->SetHide(!isRenderPlayer);

                    if (!isRenderPlayer)							
                        continue;

					m_PlayerDistQueue[i].bRendered = TRUE;
#ifdef NEW_PLAYER_LOAD
					// 如果模型未加载，则加载模型
					if( !pPlayer->GetAnim() )
					{
						// 加载模型
						if( !pPlayer->IsModelLoaded() && iLoadModel > 0 )
						{
							pPlayer->LoadModel();
							--iLoadModel;
						}
#ifdef _DEBUG
						bWantLoadPlayer = true;
#endif
					}
					else
#endif
					{
// 						if( nRenderMax == 1 )
// 							pPlayer->RenderChar( pDevice, nType, &nVertexCount, &nFaceCount );
// 						else
						{
							pPlayer->RenderChar( pDevice, nType, &nVertexCount, &nFaceCount);
						}
						nRenderPlayerCount++;
						nRenderVertexCount += nVertexCount;
						nRenderFaceCount += nFaceCount;
					}
				}
			}

			ShowMosterTip(nRenderMax);
		}

		//显示玩家的BBOX
		if( g_bShowModelBBox )
		{
			for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
			{
				CPlayer* pPlayer = it->second;
				if( pPlayer )
				{
					Box *pBox = pPlayer->GetWorldBBox();
					if( pBox )
					GetDrawer()->DrawBox3D( pBox, 0xffffffff );

					if( pPlayer->GetMountAnim() )
					{
						pBox = pPlayer->GetMountAnim()->GetWorldBBox();
						if( pBox )
							GetDrawer()->DrawBox3D( pBox, 0xffffffff );
					}
				}
			}
		}


		for (int i=0; i<(int)m_vectorDeathPlayer.size(); i++)
		{
			CPlayer* pPlayer = m_vectorDeathPlayer[i];

			if( !pPlayer )
				continue;

			if( g_bShowModelBBox )
			{
				Box *pBox = pPlayer->GetWorldBBox();
				if( pBox )
					GetDrawer()->DrawBox3D( pBox, 0xffffffff );
			}
		}
	}

	RenderPlayerTip();
	MeRenderManager::Instance()->DoRender(false);
	GetMe3dConfig()->SetMipLodBais(fOldLod);

	ShowMonsterArea();
	unguard;
}

int	CPlayerMgr::RenderMouseBag(void)
{
	guardfunc;
	return 0;
	unguard;
}

//----
//	看到有人在使用攻击动作
//----
ItemDefine::SItemSkill* GetSkill( int nSkillId, int nSkillLevel )
{
	guardfunc;
	return GettheItemDetail().GetSkillByID( nSkillId, nSkillLevel );
	unguard;
}

bool GuildQueryJoinCallback( const bool bPressYesButton, void *pData )
{
	guardfunc;
	return true;
	unguard;
}

BOOL CPlayerMgr::CheckViewPlayerBBox( Vector &vDir ,float fMaxDis)
{
	guardfunc;
	if( GetMe() == NULL )
		return FALSE;
	Vector vec(0.f,0.f,0.f);
	GetMe()->GetPos(&vec.x,&vec.y,&vec.z);
// 	Vector nextPos(vec + vDir);
	vec.z += 1.5f;
	std::map< GameObjectId, CPlayer* >::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;
		if( pPlayer == GetMe() || pPlayer->IsHide())
			continue;
		if ( pPlayer->IsMaskPlayer() && pPlayer->IsNpc() && pPlayer->GetAnim())
		{
			float fDis = 0;
			if (pPlayer->GetAnim()->GetWorldBBox()->Intersect(vec,vDir,&fDis,true))
			{
				if (fDis < fMaxDis)
				{
					return TRUE;
				}
			}
// 			Vector playerPos(0.f,0.f,0.f);
// 			pPlayer->GetPos(&playerPos.x,&playerPos.y,NULL);
		}
	}

	return FALSE;
	unguard;
}

void CPlayerMgr::CheckHPInfo( GameObjectId nIDWho )
{
	guardfunc;
	CPlayer *pPlayer = FindByID( nIDWho );
	if( !pPlayer )
		return;
	if( !pPlayer->IsHPInfoValid() )
	{
		//请求查询hp
		MsgQueryHPInfo query;
		query.header.stID = nIDWho;
		query.sNpcID = nIDWho;

		GettheNetworkInput().SendMsg( &query );
	}
	unguard;
}

void CPlayerMgr::ChangeDrome( short nId )
{
	guardfunc;
	MsgChangeDrome changedrome;

	changedrome.nDromeID = nId;

	GettheNetworkInput().SendMsg(&changedrome);
	unguard;
}

void CPlayerMgr::DisDrome()
{
	guardfunc;
	MsgDisDrome disdrome;
	
	GettheNetworkInput().SendMsg(&disdrome);
	unguard;
}

void CPlayerMgr::DisHitch()
{
	guardfunc;
	MsgDisHitch dishitch;

	if( GettheNetworkInput().SendMsg(&dishitch) == -1 )
	{

	}
	unguard;
}

bool CPlayerMgr::WillHPShow( GameObjectId nIDWho )
{
	guardfunc;
	if (nIDWho == m_showhp.nIDAttackTarget ||
		nIDWho == m_showhp.nIDMouseOver ||
		nIDWho == m_showhp.nIDLockNpc)
		return true;
	//
	return false;
	unguard;
}

void CPlayerMgr::OnSeeAction( GameObjectId stPlayerId, short stActionId )
{
	guardfunc;
	CPlayer* pPlayer = FindByID( stPlayerId );
	if( pPlayer && pPlayer->GetAnim() )
	{
		// 如果是临时性动作，那么播放一次，切换到idle
		// 如果是持续性动作，播放一次，停在最后一帧
		switch( MoreAction::GetActionType( stActionId ) )
		{
		case MoreAction::eDurativeAction:
			pPlayer->GetAnim()->PlayAnim2( 
				stActionId,
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				stActionId, 
				MexAnimCtrl::eHoldOnLastFrame );
			break;
		case MoreAction::eTmpAction:
			pPlayer->GetAnim()->PlayAnim2( 
				stActionId,
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				MoreActionClient::Idle, 
				MexAnimCtrl::eNormalPlay );
			break;
		}

	}
	unguard;
}

BOOL CPlayerMgr::BreakInputMessage( DWORD dwType )
{
	if( dwType == VK_ESCAPE && m_pMe && m_pMe->IsSelectingPoint() )
	{
		m_pMe->SetIsSelectingPoint( false );
		return true;
	}
	return false;
}

BOOL CPlayerMgr::OnSkill(BOOL bMouseSelectTarget /* = FALSE */, BOOL bUseSkillBuf /* = FALSE */)
{
	guardfunc;
	if( !m_pMe )
		return FALSE;

	m_pMe->SetIsSelectingPoint( false );

	//当前要使用的技能
	int nCurUseSkillID = -1;
	int nCurUseSkillLevel = -1;

    nCurUseSkillID = GetCurUseSkill();
	nCurUseSkillLevel = GetCurUseSkillLevel();
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( nCurUseSkillID, nCurUseSkillLevel );
	if( !pSkill )
	{
		m_SkillBufTargetID = -1;
		SetCurUseSkill( 0, 0 );
		return FALSE;
	}

	CPlayer *pTarget = NULL;

    // 开关控制是否使用SkillBuf
	if( bUseSkillBuf )
	{
		pTarget = FindByID( m_SkillBufTargetID );
	}
	else
	{
        // 检查目标类型
		switch( pSkill->ustCastTarget )
		{
		case ItemDefine::casttarget_me:
			pTarget = GetMe();
			break;
		case ItemDefine::casttarget_pos:
			//鼠标不用指定目标
			break;
		case ItemDefine::casttarget_friendlive:
			{
				if( bMouseSelectTarget )
				{
					pTarget = FindByID( m_shMouseTargetPlayerSeverID );
				}
				else
				{
					pTarget = FindByID(GetLockPlayerID());
				}

				if ( pTarget == NULL || pTarget->IsItem() || pTarget->IsNpc())
				{
					pTarget = GetMe();
				}
				if (pTarget&&GetMe()&&pTarget->IsMonster()&&pTarget->GetID() != GetMe()->GetPetID())
				{
					pTarget = GetMe();
				}
				break;
			}
		case ItemDefine::casttarget_live:
			{
				if( bMouseSelectTarget )
				{
					pTarget = FindByID( m_shMouseTargetPlayerSeverID );
				}
				else
				{
					pTarget = FindByID(GetLockPlayerID());
				}

				if(!pTarget || !pTarget->IsPlayer() || pTarget->IsDead())
					pTarget = GetMe();
			}
			break;	
		case ItemDefine::casttarget_enemylive:
		case ItemDefine::casttarget_friendcorpse:
		case ItemDefine::casttarget_enemycorpse:
		case ItemDefine::casttarget_corpse:
		case ItemDefine::casttarget_herb:
		case ItemDefine::casttarget_mine:
        case ItemDefine::casttarget_insect:
		case ItemDefine::casttarget_wood:
		case ItemDefine::casttarget_treasure:
        case ItemDefine::casttarget_mount:
			//必须指定目标
			if( bMouseSelectTarget )
			{
				pTarget = FindByID( m_shMouseTargetPlayerSeverID );
			}
			else
			{
				pTarget = FindByID(GetLockPlayerID());
			}

			break;
		case ItemDefine::casttarget_pet:
            // 只能对宠物施放的技能，target直接设成宠物
			if( GetMe() )
			{
				pTarget = FindByID(GetMe()->GetPetID());
				if( !pTarget )
				{
					if( bMouseSelectTarget )
					{
						pTarget = FindByID( m_shMouseTargetPlayerSeverID );
					}
					else
					{
						pTarget = FindByID(GetLockPlayerID());
					}
				}
			}
			break;
		case ItemDefine::casttarget_team:
			{
				if( bMouseSelectTarget )
				{
					pTarget = FindByID( m_shMouseTargetPlayerSeverID );
				}
				else
				{
					pTarget = FindByID(GetLockPlayerID());
				}

				if ( pTarget == NULL || pTarget->IsNpc())
				{
					pTarget = GetMe();
				}
                // 怪物
				if (pTarget->IsMonster())
				{
                    // 判断是否自己或队友召唤兽
                    if( pTarget->GetMasterID() > -1 )
                    {
                        CPlayer* pMaster = FindByID(pTarget->GetMasterID());
                        if( pMaster )
                        {
                            if( GetMe() && pMaster != GetMe() && !GetMe()->IsTeamMember(pMaster->GetName()) )
                            {
                                pTarget = GetMe();
                            }
                        }
                        else
                            pTarget = GetMe();
                    }
                    else
					    pTarget = GetMe();
				}
				// 不是队友，或是队友但是切磋对象，则对自己施放
				if (GetMe() && pTarget->IsPlayer() && pTarget != GetMe() && 
                    (!GetMe()->IsTeamMember(pTarget->GetName()) || (GetMe()->IsDueling() && thePlayerRole.GetDuelTarget() == pTarget->GetID()) ))
				{
					pTarget = GetMe();
				}
			}
			break;
		}
	}

	//Xp技能不能在非受控状态释放
	if (pSkill->specialSkillType == ItemDefine::ESST_XPSkill)
	{
		if (m_pMe->IsUnControlState())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_UnableOperateInCurrentState ) );
			return FALSE;
		}
	}

	// added, jiayi, [2009/7/20]
	if( pSkill->shCastType == ItemDefine::casttype_AOEPointCircleArea )
	{
		m_pMe->SetIsSelectingPoint( true );
		bool bCanUse = m_pMe->TryUseSkill( NULL, pSkill ) ;
		m_pMe->SetIsSelectingPoint( bCanUse );
		return bCanUse;
	}

    if( pSkill->shCastType == ItemDefine::casttype_singletarget 
        && pSkill->usSpecialTargetType != ItemDefine::STT_NONE )
    {
        m_pMe->SetIsSelectingPoint( true );
        bool bCanUse = m_pMe->TryUseSkill( NULL, pSkill ) ;
        m_pMe->SetIsSelectingPoint( bCanUse );
        return bCanUse;
    }

	// 如果没有目标，并且是对一个单位用的，就强行给个目标，策划新要求
	if (  !static_cast<bool>( GameSetting::Instance()->GetLevel( GameSetting::eSSC_CLOSE_AUTO_SELECT ) )
		&&pTarget == NULL 
		&& ( pSkill->shCastType == ItemDefine::casttype_singletarget 
				|| pSkill->shCastType == ItemDefine::casttype_singletargetcircleAOE 
				|| pSkill->shCastType == ItemDefine::casttype_AOETargetcirclearea ) 
		)
	{
		TabSelectPlayer();

		int selId = s_CUI_ID_FRAME_Target.GetSelId();

		pTarget = FindByID( selId );

	}
    if(m_pMe->TryUseSkill( pTarget, pSkill ))
	{
		if(s_CUI_NpcTaskDialogBox.IsVisable())
			s_CUI_NpcTaskDialogBox.EndIntonateBar();
		return true;
	}
	else
	{
		return false;
	}
	unguard;
}
//---
//发Ping消息给服务器
//---
extern GAME_STATE	g_GameState;

BOOL	CPlayerMgr::PingServer(void)
{
	guardfunc;
	static	DWORD s_time_record=0;
    static  bool  bHaveShow = false;
	const	DWORD ping_time = 2000;
	//
	if (HQ_TimeGetTime() - s_time_record > ping_time)
	{
		s_time_record = HQ_TimeGetTime();
		//
		if (GettheNetworkInput().IsClosed())
		{
			bHaveShow = true;
			return FALSE;
		}
		//
		MsgPingMsg  PingMsg;
		//
		PingMsg.dwTime = s_time_record;
		//
 		if ( GettheNetworkInput().SendMsg(&PingMsg) == -1 && !bHaveShow)
		{
			bHaveShow = true;
            return FALSE;
		}
	}
	return TRUE;
	unguard;
}

//---
//	画系统的消息
//---
void	CPlayerMgr::RenderInfo(LPDIRECT3DDEVICE9 pDevice, int x, int y)
{
	guardfunc;
	char string[256];
	//
	sprintf(string, "Ping=%d", m_dwGamePing);
	y+=24;
	//
	unguard;
}


//----
//
//----
int   CPlayerMgr::GenerateNetStreamFluxLen(int val)
{
	guardfunc;
	int   ty, left_val;
	int   i;
	int   temp;
	int   val_size[5]={1024 / 20, 1024 / 20 * 5, 1024 / 20 * 10, 1024 / 20 * 20, 1024 / 20 * 30};
	//
	ty = 0;
	left_val = val;
	temp = 4;
	for (i=0; i<5; i++)
	{
		ty = ty + (left_val % val_size[i]) / temp;
		val = val - val_size[i];
		//
		temp = temp * 4;
		left_val = left_val - left_val % val_size[i];
		//
		if (left_val <= 0 )
			break;
	}
	return ty;
	unguard;
}

//-----
// 绘制网络流量的波纹线
//-----
void    CPlayerMgr::DrawNetStreamFlux(LPDIRECT3DDEVICE9 pDevice, int x, int y, BOOL bDraw/*= TRUE*/, NetStatistics* pRetStatistics/*=NULL*/)
{
	guardfunc;
	enum
	{
		MAX_SHOW_POINT_NUM  =   50,
		SHOW_STEP_WIDTH     =   4 ,
	};
	//
	char	szBuf[256];
	static  int   s_out_record_stack[MAX_SHOW_POINT_NUM];
	static  int   s_in_record_stack[MAX_SHOW_POINT_NUM];
	static  int   s_record_stack_buttom = 0;
	static  int   s_record_stack_top = 0;

	//
	static  DWORD   s_record_time = 0;
	static  int   s_record_out_size = 0;
	static  int   s_record_in_size = 0;
	static  int   s_now_out_size_ps = 0;
	static  int   s_now_in_size_ps = 0;
	static  int   s_avg_out_size_ps = 0;
	static  int   s_avg_in_size_ps = 0;
	static  int   s_max_out_size_ps = 0;
	static  int   s_max_in_size_ps = 0;
	static  int   s_in_count=0;
	static  int   s_out_count=0;
	//
	DWORD   time, off_time;
	int   sx, sy;
	int   ping_num;

 	ping_num = GetGamePing();
	sx = x;
	sy = y;

	//ping
	if( bDraw )
	{
		sy += 15;
		sprintf((char*)szBuf,"Ping:%d",ping_num);

		FontSystem::DrawText( szBuf, sx, sy+5, DT_NOCLIP, 0xFFFF6400, 2 );
		sy += 25;
		//
		//
		sprintf((char*)szBuf,"Netin  avg[%05d]B max[%05d]",
			s_avg_in_size_ps, s_max_in_size_ps);

		FontSystem::DrawText( szBuf, sx, sy+5, DT_NOCLIP, 0xFFFF6400, 2 );
		sy += 25;
		//
		sprintf((char*)szBuf,"NetOut avg[%05d] max[%05d]B",
			s_avg_out_size_ps, s_max_out_size_ps);

		FontSystem::DrawText( szBuf, sx, sy+5, DT_NOCLIP, 0xFFFF6400, 2 );
	}

	time = HQ_TimeGetTime();
	off_time = time - s_record_time;
	if( off_time == 0 )
		off_time = 1;

	s_now_out_size_ps = 0;/*(GettheNetworkInput().GetSocketCtrl()->GetBytesSent() - s_record_out_size) * 1000 / off_time;*/
	s_now_in_size_ps = 0;/*(GettheNetworkInput().GetSocketCtrl()->GetBytesRecved() - s_record_in_size) * 1000 / off_time;*/
	//
	if (s_now_out_size_ps > 0)
	{
		s_avg_out_size_ps = (s_avg_out_size_ps * s_out_count + s_now_out_size_ps) / (s_out_count + 1);
		s_out_count ++;
	}
	if (s_now_in_size_ps > 0)
	{
		s_avg_in_size_ps = (s_avg_in_size_ps * s_in_count + s_now_in_size_ps) / (s_in_count + 1);
		s_in_count++;
	}

	//
	if (s_now_out_size_ps > s_max_out_size_ps)
		s_max_out_size_ps = s_now_out_size_ps ;
	
	if (s_now_in_size_ps > s_max_in_size_ps)
		s_max_in_size_ps = s_now_in_size_ps;

	//
	if (off_time >= 1000)
	{
		s_record_time = time;
	}

	//
	//
	s_record_out_size = 0;/*GettheNetworkInput().GetSocketCtrl()->GetBytesSent();*/;
	s_record_in_size = 0;/*GettheNetworkInput().GetSocketCtrl()->GetBytesRecved();*/
	
	//糤魁帮舼い
	s_out_record_stack[s_record_stack_top] = s_now_out_size_ps;
	s_in_record_stack[s_record_stack_top] = s_now_in_size_ps;
	
	//
	s_record_stack_top ++;
	if (s_record_stack_top >= MAX_SHOW_POINT_NUM)
		s_record_stack_top = 0;
	
	if (s_record_stack_top == s_record_stack_buttom)
		s_record_stack_buttom ++;
	
	if (s_record_stack_buttom >= MAX_SHOW_POINT_NUM)
		s_record_stack_buttom = 0;

	if( pRetStatistics )
	{
		pRetStatistics->iInAvgPerSecond = s_avg_in_size_ps;
		pRetStatistics->iInMaxPerSecond = s_max_in_size_ps;
		pRetStatistics->iOutAvgPerSecond = s_avg_out_size_ps;
		pRetStatistics->iOutMaxPerSecond = s_max_out_size_ps;
	}
	
	unguard;
}

void CPlayerMgr::Release()
{
	guardfunc;
	unguard;
}

GameObjectId CPlayerMgr::GetMyID()
{ 
	guardfunc;
	if( !m_pMe )
		return 0;	// 是否要返回-1？
	return m_pMe->GetID(); 
	unguard;
}

CPlayerMgr::SNpcQuestInfo* CPlayerMgr::FindNpcInfo( const char* pName )
{
	guardfunc;
	for( int i = 0; i < m_vectorNpcInfo.size(); i++ )
	{
		if( m_vectorNpcInfo[i].strName == pName )
		{
			return &m_vectorNpcInfo[i];
		}
	}
	return NULL;
	unguard;

}

void CPlayerMgr::RefreshAllNpcQuest()
{
	guardfunc;
	if (m_vectorNpcInfo.size() == 0)
	{
		CWorldTile* pTile = CURRENTTILE;
		if (NULL == pTile)
		{
			return;
		}
		std::vector<NpcCoordInfo>& npcMap = NpcCoord::getInstance()->getNpcVec();
		for( int i=0; i<npcMap.size(); ++i )
		{
			NpcCoordInfo* pInfo = &npcMap[i];
			if(pInfo->_bNpc && pInfo->_mapId == pTile->GetMapId() )
			{
				SNpcQuestInfo info;
				info.strName	= Common::_tstring::toNarrowString(pInfo->_szName.c_str());
				m_vectorNpcInfo.push_back( info );
			}
		}
	}
	for( int i = 0; i < m_vectorNpcInfo.size(); i++ )
	{
		m_vectorNpcInfo[i].InitialRelateQuestInfo();
	}
	unguard;

}

void CPlayerMgr::GetNpcQuests(const NpcCoordInfo* pCoordInfo, std::vector<SQuest*>* pvectorQuest, std::vector<void*>* pvrState )
{
	if (!pCoordInfo)
	{
		return;
	}
	SNpcQuestInfo* pInfo = FindNpcInfo( Common::_tstring::toNarrowString(pCoordInfo->_szName.c_str()).c_str() );
	if( pInfo )
	{
		guard(test0);
		for( int i = 0; i < pInfo->vectorRelateQuestInfo.size(); i++ )
		{
			pvrState->push_back( pInfo->vectorRelateQuestInfo[i] );
			CPlayerRole::QuestInfo* pQuestInfo = (CPlayerRole::QuestInfo*)pInfo->vectorRelateQuestInfo[i];
			SQuest* pQuest = theQuestManager.GetQuest( pQuestInfo->nQuestId );
			if( pQuest )
				pvectorQuest->push_back( pQuest );
		}
		unguard;
		return;
	}
	std::vector<CPlayerRole::QuestInfo*>& vtQuest = thePlayerRole.GetActiveQuestInfo();
	for ( int n=0; n<vtQuest.size(); n++ )
	{

 		if (vtQuest[n]->nQuestId >= dr_MaxQuestId)
 		{
 			break;
 		}		
		SQuest *pQuest = theQuestManager.GetQuest( vtQuest[n]->nQuestId );
		if (!pQuest)
		{
			continue;
		}
		if (theQuestManager.IsQuestNotGain(vtQuest[n]->chState))
		{
			const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->AcceptTargetId);
			if (pInfo && (pCoordInfo->_nID == pInfo->_nID))
			{
				pvectorQuest->push_back( pQuest);
				pvrState->push_back(vtQuest[n]);
			}
		}
		else
		{
			const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->ReplyTargetId);
			if (pInfo && (pCoordInfo->_nID == pInfo->_nID))
			{
				pvectorQuest->push_back( pQuest);
				pvrState->push_back(vtQuest[n]);
			}
		}
	}

}
int	CPlayerMgr::UpdateNpcTipsType( GameObjectId stNpcId )
{
	guardfunc;
	CPlayer* pPlayer = FindByID(stNpcId);
	const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pPlayer->GetNpcID());
	return UpdateNpcTipsType(pInfo);
	unguard;
}

int CPlayerMgr::UpdateNpcTipsType(const NpcCoordInfo* pCoordInfo )
{
	if (!pCoordInfo)
	{
		return eNpcTips_None;
	}

	if (pCoordInfo->uchCountryID != 0 //不是中立npc
		&&	pCoordInfo->uchCountryID != GetMe()->GetRealCountry()//不是本国npc
		)
	{
		return eNpcTips_None;
	}
	if (pCoordInfo->_nType == eNT_Pub)
		return eNpcTips_HaveQuest;

	std::vector<SQuest*>	vectorQuest;
	std::vector<void*>			vtNpcRelateState;
	// 得到此npc任务描述
	GetNpcQuests( pCoordInfo, &vectorQuest, &vtNpcRelateState );
	bool bHaveQuest = false;
	bool bHaveQuestNotNow = false;
	bool bQuestDone = false;
	bool bQuestNotDone = false;

	for( int i = 0; i < vtNpcRelateState.size(); i++ )
	{
		CPlayerRole::QuestInfo *pNpcQuestInfo = (CPlayerRole::QuestInfo*)vtNpcRelateState[i];
		SQuest* pQuest = vectorQuest[i];
		if( !pQuest )
		{
			continue;
		}
		if ((pQuest->Country!=0 && pQuest->Country!=thePlayerRole.GetCountry()))
		{
			continue;
		}
		assert(!theQuestManager.IsQuestDone( pNpcQuestInfo->chState ) );
		// 如果角色任务状态中没有发现此任务记录,或者任务还没做过
		if( theQuestManager.IsQuestNotGain( pNpcQuestInfo->chState ) )
		{			
			if ( thePlayerRole.GetLevel() < pQuest->GetPlayerReceiveQuestLevel() )
				bHaveQuestNotNow = true;
			else
				bHaveQuest = true;
		}
		else
		{			
			if ( pNpcQuestInfo->bDone )
				bQuestDone = true;
			else
				bQuestNotDone = true;	
		}
	}

	if ( bQuestDone )
		return eNpcTips_QuestDone;
	else if ( bHaveQuest )
		return eNpcTips_HaveQuest;
	else if ( bQuestNotDone )
		return eNpcTips_QuestNotDone;
	else if ( bHaveQuestNotNow )
		return eNpcTips_HaveQuestNotNow;
	else
		return eNpcTips_None;

}
void CPlayerMgr::OnShowText( Msg* pMsg )
{
	MsgShowText *pShowText = (MsgShowText*)pMsg;

	bool bShowMsgBox = false;
	char* szTemp = theXmlString.ParseAtString(pShowText->szText);
	for (int i = 9416; i <= 9422; ++i)
	{
		if (0 == strcmp(szTemp, theXmlString.GetString(i)))
		{
			bShowMsgBox = true;
			break;
		}
	}
	for (int i = 9384; i <= 9385; ++i)
	{
		if (0 == strcmp(szTemp, theXmlString.GetString(i)))
		{
			bShowMsgBox = true;
			break;
		}
	}

	if( bShowMsgBox )
    {
		s_CUI_ID_FRAME_MessageBox.Show(szTemp);
    }
	else
	{
        CScreenInfoManager::Instance()->ShowInfoByType( pShowText->nShowInfoType, szTemp );
	}
}
/*
@added by realking at 06/06/2006
@S-C显示银行和仓库
*/
void CPlayerMgr::OnShowBank( Msg* pMsg )
{
	guardfunc;
	assert( 0 && "deleted, jiayi" );
	s_CUI_ID_FRAME_PACK.Refeash();
	unguard;
}

void CPlayerMgr::SetStorage( Msg* pMsg )
{
	guardfunc;
	MsgUpdateStorage *pUpdateStorage = (MsgUpdateStorage*)pMsg;
	s_CUI_ID_FRAME_Storage.SetVisable(true);
	thePlayerRole.m_stStorage = pUpdateStorage->stStorage;
	thePlayerRole.SetNpcID(pUpdateStorage->nNpcId);
	s_CUI_ID_FRAME_Storage.InitStorageState();
	s_CUI_ID_FRAME_Storage.Refeash();
	if(pUpdateStorage->nNpcId == InvalidLogicNumber)
	{
		s_CUI_ID_FRAME_Storage.SetIsNpcStorage(false);
	}
	else
	{
		s_CUI_ID_FRAME_Storage.SetIsNpcStorage(true);
	}
	unguard;
}

bool CPlayerMgr::DoUseSkillOperation( GameObjectId TargetID, int nSkillID, int nSkillLevel )
{
	guardfunc;
	if( !m_pMe )
		return false;
	//当前要使用的技能
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( nSkillID, nSkillLevel );

	if( !pSkill )
	{
		return false;
	}

	// 技能是否还在colddown
	SkillBag bag = thePlayerRole.m_SkillBag;
	if (pSkill->sSkillCategory>=ItemDefine::SCT_HeroPassive && pSkill->sSkillCategory<=ItemDefine::SCT_HeroAttack)
	{
		bag = thePlayerRole.m_HeroSkillBag;
	}
	if ( bag.IsSkillCoolDownById( pSkill->ustItemID ) )
	{
		return false;
	}

	CPlayer *pTarget = NULL;
	switch( pSkill->ustCastTarget )
	{
	case ItemDefine::casttarget_me:
		pTarget = m_pMe;
		break;
	case ItemDefine::casttarget_pos:
		break;
	case ItemDefine::casttarget_friendlive:
		pTarget = FindByID( TargetID );

		if ( pTarget == NULL || pTarget->IsMonster() || pTarget->IsNpc() )
		{
			pTarget = GetMe();
		}
		break;
	case ItemDefine::casttarget_enemylive:
	case ItemDefine::casttarget_live:
	case ItemDefine::casttarget_herb:
	case ItemDefine::casttarget_mine:
	case ItemDefine::casttarget_wood:
	case ItemDefine::casttarget_treasure:
    case ItemDefine::casttarget_mount:
		pTarget = FindByID( TargetID );
		if( pTarget )
		{
			if( pTarget->IsDead() )
			{
				if( s_CUI_Progress.IsVisable() && !s_CUI_Progress.IsInterrupt() )
				{
					s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), 1, true, 1, true, true, theXmlString.GetString(eTextPlayer_Break), true, false, 0, FALSE );

					// 吟唱中断，在手上的特效也要释放掉
					int nEffectID = m_pMe->GetIntonatingEffectID();
					if( nEffectID >= 0 )
					{
						IEffect* pEffect = GetEffectMgr()->GetEffect( nEffectID );
						if( pEffect )
						{
							pEffect->SetDead();
						}
						pEffect = NULL;
					}
				}

				if( m_pMe )
				{
					if( !m_pMe->IsMoving() )
					{
						m_pMe->SwitchIdleAnim();
					}
					m_pMe->SetIntonating( FALSE );
				}
			}
		}
		break;
	case ItemDefine::casttarget_friendcorpse:
	case ItemDefine::casttarget_enemycorpse:
	case ItemDefine::casttarget_corpse:
		pTarget = FindByID( TargetID );
		break;
	case ItemDefine::casttarget_team:
		pTarget = FindByID( TargetID );

		if ( pTarget == NULL || pTarget->IsNpc() )
		{
			pTarget = GetMe();
		}

		if (pTarget && GetMe() && pTarget->IsMonster() && pTarget->GetID() != GetMe()->GetPetID())
		{
			pTarget = GetMe();
		}

		if (GetMe() && pTarget && pTarget->IsPlayer()&&!GetMe()->IsTeamMember(pTarget->GetName()) && pTarget!=GetMe() )
		{
			pTarget = GetMe();
		}
		break;
	}

	if( pTarget )
	{
		return m_pMe->TryUseSkill( pTarget, pSkill );
	}
	else
	{
		return m_pMe->TryUseSkill( NULL, pSkill );
	}
	return true;
	unguard;
}

bool CPlayerMgr::MoveRoleToNPC(const NpcCoordInfo* pInfo )//zhuxincong大地图上，点击NPC 上马寻路过去
{
	CWorldTile* pTile = CURRENTTILE;
	if(NULL == pTile)
		return false;
	int nMapId = pInfo->_mapId;
	if (!pInfo->_bNpc)
	{//怪物数据只有一份,所以只能寻本国怪
		nMapId = gCfg.GetMyCountryMapId(nMapId,GetMe()->GetRealCountry());
	}
	s_CUI_ID_FRAME_MiniMap.SetLastPFPoint(pInfo->_pfMapX,pInfo->_pfMapY,nMapId);


	float fXOff = 0;
	float fYOff = 0;
	float fDist = 0;

	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();

	fXOff = pInfo->_pfMapX - pMe->GetPos().x;
	fYOff = pInfo->_pfMapY - pMe->GetPos().y;
	fDist = sqrtf(fXOff*fXOff+fYOff*fYOff);
	
	PositionInfo::Position* pos = PositionInfo::Instance().GetPositionById(pInfo->_nID);	
	if (pos == NULL && fDist>=50)
	{
		if (thePlayerRole.GetActivedMount())
		{
			if (!(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting()))//zhuxincong 8.2 2012 寻路上马，没有判断距离长度
			{
				// 压镖状态下寻路禁止上马
				if (!theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
					s_CUI_ID_FRAME_Pet.Mount();
			}
		}
	}

	else if (pos->needMount && fDist>=50)
	{
		if (thePlayerRole.GetActivedMount())
		{
			if (!(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting()))//zhuxincong 8.2 2012 寻路上马，没有判断距离长度
			{
				// 压镖状态下寻路禁止上马
				if (!theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
					s_CUI_ID_FRAME_Pet.Mount();
			}
		}
	}

	if ((pTile->GetMapId() ==  nMapId) 	)
	{
		MoveRoleTo(pInfo->_pfMapX,pInfo->_pfMapY,true,false);
		m_pMe->SetActionTarget(0xFFFFF,Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());//这里不能传入-1
	}
	else
	{//跨地图寻路
		if( GetMe() )
		{
			float x,y;
			GetMe()->GetPos(&x,&y,NULL);
			return CrossMapPF::Instance()->CrossMapFindPath(pTile->GetMapId(),x,y,nMapId,pInfo->_pfMapX,pInfo->_pfMapY/*,pInfo->_nType*/);
		}
	}
	return true;
}

void CPlayerMgr::ProcessPendingSawPlayerNPC()
{
	m_nSawPlayerNPCCostTime = 0;
	DWORD timeBegin = HQ_TimeGetTime();
	DWORD timeEnd = timeBegin;

	if( PendingSawPlayer.size() )
	{
		std::vector<MsgPlayerEnterMySight>::iterator iter = PendingSawPlayer.begin();
		while( iter != PendingSawPlayer.end() && timeEnd - timeBegin < LOAD_PLAYER_NPC_MAX_TIME )
		{
			OnMsgPlayerEnterMySight(&(*iter), FALSE);
			
			iter = PendingSawPlayer.erase(iter);
			timeEnd = HQ_TimeGetTime();
		}
	}
	if( timeEnd - timeBegin < LOAD_PLAYER_NPC_MAX_TIME && PendingSawNPC.size() )
	{
		std::vector<MsgNPCEnterMySight>::iterator iter = PendingSawNPC.begin();
		while( iter != PendingSawNPC.end() && timeEnd - timeBegin < LOAD_PLAYER_NPC_MAX_TIME )
		{
			OnMsgNPCEnterMySight(&(*iter), FALSE);

			iter = PendingSawNPC.erase(iter);
			timeEnd = HQ_TimeGetTime();
		}
	}
	m_nSawPlayerNPCCostTime = timeEnd - timeBegin;
}

void CPlayerMgr::PreloadMapMonsterAndNpc( const char* szMapPath )
{
	char szMapName[MAX_PATH] = {0};
	char szTemp[MAX_PATH] = {0};
	char szMonsterCfg[MAX_PATH] = {0};
	strcpy(szTemp, szMapPath);
	char *p = strchr(szTemp, '\\');
	if( p )
		strcpy(szMapName, p+1);
	else
		strcpy(szMapName, szTemp);
	p = strchr(szMapName, '.');
	if( p )
		*p = '\0';

	// 预加载地图怪模型数据
	MeSprintf_s(szMonsterCfg,sizeof(szMonsterCfg)/sizeof(char) -1 , "%s\\%s\\%s.monster", SwGlobal::GetWorld()->GetWorldPath(), szMapName, szMapName);

	MeXmlDocument	doc;
	{
		if (!doc.LoadFile(szMonsterCfg))
		{
			return;
		}
		MeXmlElement* pRoot = doc.FirstChildElement("Stage")->ToElement();
		if( !pRoot )
			return;

		std::vector<int> vctMonsterIndexList;
		vctMonsterIndexList.clear();

		MeXmlElement* pMonsterNode = pRoot->FirstChildElement( "Monster" );
		while( pMonsterNode )
		{
			MeXmlElement* pMonsterGroup = pMonsterNode->FirstChildElement( "MonsterGroup");
			while( pMonsterGroup )
			{
				MeXmlElement* pMonsterGroupInfo = pMonsterGroup->FirstChildElement( "MonsterGroupInfo" );
				while( pMonsterGroupInfo )
				{
					// 获取Monster Index（Monster.slk里）
					int nMonsterIndex;
					pMonsterGroupInfo->QueryIntAttribute("Index",&nMonsterIndex);
					if( nMonsterIndex != -1 )
					{
						BOOL bFind = FALSE;
						if( vctMonsterIndexList.size() )
						{
							for(UINT i=0; i<vctMonsterIndexList.size(); i++)
							{
								if( vctMonsterIndexList[i] == nMonsterIndex )
								{
									bFind = TRUE;
									break;
								}
							}
						}
						if( !bFind )
						{
							vctMonsterIndexList.push_back(nMonsterIndex);
						}
					}
					pMonsterGroupInfo = pMonsterGroupInfo->NextSiblingElement( "MonsterGroupInfo" );
				}
				pMonsterGroup = pMonsterGroup->NextSiblingElement( "MonsterGroup" );
			}
			pMonsterNode = pMonsterNode->NextSiblingElement( "Monster" );
		}

		if( vctMonsterIndexList.size() )
		{
			for(UINT i=0; i<vctMonsterIndexList.size(); i++)
			{
				ItemDefine::SMonster* pMonster =  GettheItemDetail().GetMonsterById(vctMonsterIndexList[i]);
				if( pMonster )
				{
					GetMexResMgr()->PreloadModel(pMonster->iModelID);
				}
			}
		}
	}

	// 预加载地图NPC模型数据
	std::vector<int> kMapNpcModelList;
	int mapId = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile()->GetMapId();
	NpcCoord::getInstance()->GetNpcListInMap(mapId, &kMapNpcModelList);
	if( kMapNpcModelList.size() )
	{
		for(UINT i=0; i<kMapNpcModelList.size(); i++)
		{
			if( kMapNpcModelList[i] >= 0 )
            {
                BOOL bOK = GetMexResMgr()->PreloadModel(kMapNpcModelList[i]);
                int id = kMapNpcModelList[i];
                if( !bOK )
                {
                    char msg[MAX_PATH] = {0};
                    sprintf(msg, "Preload NPC failed, Model ID %d, Map id %d\n", id, mapId);
                    OutputDebugStringA(msg);
                }
            }
		}
	}
}

void CPlayerMgr::BeginDialog(float xDst,float yDst)
{
	g_vTheRoleTargetDir.x = 0;
	g_vTheRoleTargetDir.y = 0;
	g_bTheRoleMovingByDir = FALSE;
	//标志Npc对话框已经打开 并且记录Npc的位置 用于计算玩家走开离Npc一定距离的时候 关闭NPc 对话框
	m_bNeedBeginDilog = true;
}

void CPlayerMgr::SetPlayerRenderPriority( unsigned short pri )
{
    if( pri == 0 )
    {
        // 渲自己，队友，NPC，和怪物
        m_nPlayerRenderFlag = EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER;
    }
    else
    {
        // 渲染全部
        m_nPlayerRenderFlag = EPRF_ALL;
    }
}

void CPlayerMgr::TogglePlayerRenderPriority()
{
    //if( m_nPlayerRenderFlag == EPRF_ALL )
    //{
    //    // 渲自己，队友，NPC，和怪物
    //    m_nPlayerRenderFlag = EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER;
    //    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect, 0 );
    //    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, 0 );
    //    GameSetting::Instance()->CommitChanges();
    //}
    //else
    //{
    //    // 渲染全部
    //    m_nPlayerRenderFlag = EPRF_ALL;
    //    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect, 1 );
    //    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, 1 );
    //    GameSetting::Instance()->CommitChanges();
    //}
    //if( s_CUI_ID_FRAME_GameSettingPlayer.IsVisable() )
    //    s_CUI_ID_FRAME_GameSettingPlayer.RefreshUI();
    //if( s_CUI_ID_FRAME_GameSettingSelf.IsVisable() )
    //    s_CUI_ID_FRAME_GameSettingSelf.RefreshUI();

	/*
	切换顺序 
	PSM_ShowAll = 0,		    // 显示所有玩家
	PSM_HideAll      ,			// 隐藏所有玩家
	PSM_ShowAmity   ,			// 显示本国的玩家
	PSM_ShowAntagonize	   ,	// 显示他国的玩家。
	
	*/
	unsigned int _RenderFlag = s_CUI_ID_FRAME_MiniMap.GetRenderPlayerFlag();
	//IsPlayerTypeRender()
	if(s_CUI_ID_FRAME_MiniMap.HasRenderFlag(EPRF_ALL)) //全部
	{
	//s_CUI_ID_FRAME_Group_Me.SetRenderPlayerFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER,true); //全部隐藏
		s_CUI_ID_FRAME_MiniMap.ID_BUTTON_PlayerHideALLOnButtonClick( s_CUI_ID_FRAME_MiniMap.m_pID_BUTTON_PlayerHideALL );
	}
	else if(s_CUI_ID_FRAME_MiniMap.HasRenderFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER)) //全部隐藏
	{
		//s_CUI_ID_FRAME_Group_Me.SetRenderPlayerFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER | EPRF_AMITY ,true); //显示本国 友好
		//s_CUI_ID_FRAME_MiniMap.ID_BUTTON_PlayerShowAmityOnButtonClick( s_CUI_ID_FRAME_MiniMap.m_pID_BUTTON_PlayerShowAmity );
		s_CUI_ID_FRAME_MiniMap.ID_BUTTON_PlayerShowALLOnButtonClick( s_CUI_ID_FRAME_MiniMap.m_pID_BUTTON_PlayerShowALL );
	}
	else
		return; //其他什么都不干
	//else if (s_CUI_ID_FRAME_MiniMap.HasRenderFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER | EPRF_AMITY) ) //友好
	//{
	//	//s_CUI_ID_FRAME_Group_Me.SetRenderPlayerFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER | EPRF_ANTAGONIZE ,true); //非友好
	//	s_CUI_ID_FRAME_MiniMap.ID_BUTTON_PlayerShowAntagonizeOnButtonClick( s_CUI_ID_FRAME_MiniMap.m_pID_BUTTON_PlayerShowAntagonize );
	//	
	//}
	//else if(s_CUI_ID_FRAME_MiniMap.HasRenderFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER | EPRF_ANTAGONIZE)) //非友好
	//{
 //          //s_CUI_ID_FRAME_Group_Me.SetRenderPlayerFlag(EPRF_ALL ,true); //全部
	//	s_CUI_ID_FRAME_MiniMap.ID_BUTTON_PlayerShowALLOnButtonClick( s_CUI_ID_FRAME_MiniMap.m_pID_BUTTON_PlayerShowALL );
	//}

	m_nPlayerRenderFlag = s_CUI_ID_FRAME_MiniMap.GetRenderPlayerFlag(); 
	//s_CUI_ID_FRAME_Group_Me.compositor(true); //排序



}

BOOL  CPlayerMgr::IsPlayerCanRenderEX(CPlayer* pPlayer, BOOL bDist)
{
	/*
	  针对IsPlayerCanRender判断后不可显示的玩家进行再一次判断
	  主要针对 本国和非本国的玩家进行隐藏
	*/
	if( !pPlayer )
		return FALSE;

	if(!pPlayer->IsPlayer()) 
		return FALSE;

	if(!GetMe())
		return FALSE;

	// 渲染队友
	if( pPlayer->MyTeamMember )
	{
		if( IsPlayerTypeRender(EPRF_TEAM) )
			return TRUE;
		else
			return FALSE;
	}

	if (!bDist && m_nPlayerRenderFlag == EPRF_ALL )
      return TRUE;

	if (m_nPlayerRenderFlag == (EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER))
          return FALSE;

	if (GetMe()->GetRealCountry() != pPlayer->GetRealCountry()) //外国
	{
		if(IsPlayerTypeRender(EPRF_ANTAGONIZE))
			return TRUE;
		else
			return FALSE;

	}else //本国
	{
		if(IsPlayerTypeRender(EPRF_AMITY))
			return TRUE;
		else
			return FALSE;
	}
	

	return FALSE;
}

BOOL CPlayerMgr::IsPlayerCanRender( CPlayer* pPlayer, BOOL bDist/*= FALSE*/ )
{
    if( !pPlayer )
        return FALSE;

	if ( !bDist && pPlayer->IsMonster() )
	{
		CPlayer *pMaster = FindByID( pPlayer->GetMasterID() );
		if ( pMaster != NULL )
		{
			// 如果玩家在运镖状态, 隐藏镖车(召唤物), 而副将还是照常显示
			if ( pMaster->IsYabiaoState() )
			{
				// 副将
				if ( pPlayer->GetMonsterType() == eMT_Pet )
					return TRUE;

				// 马车
				if ( pPlayer->GetSubMonsterType() == Object_MonsterProtected )
					return FALSE;
			}
		}
	}

	// 是选中目标，则渲染
	if( GetLockPlayerID() > -1 )
	{
		CPlayer* pTargetPlayer = FindByID( GetLockPlayerID() );
		if( pTargetPlayer && pTargetPlayer == pPlayer/* && m_nPlayerRenderFlag & EPRF_TARGET*/)
			return TRUE;
	}

    // 渲染自己，自己召唤兽
    if( pPlayer == m_pMe || (m_pMe && m_pMe->HavePet() && pPlayer->GetID() == m_pMe->GetPetID()) )
    {
        if( g_bRenderRole && IsPlayerTypeRender(EPRF_ME))
            return TRUE;
        else
            return FALSE;
    }

    // 全部渲染
    if( !bDist && m_nPlayerRenderFlag == EPRF_ALL )
        return TRUE;

    // 掉地上装备和采集物品默认渲染
    if( pPlayer->IsItem() || (pPlayer->IsMonster() && pPlayer->IsCollection(false)) )
        return TRUE;

    // 渲染NPC
    if( pPlayer->IsNpc() )
    {
        if( IsPlayerTypeRender(EPRF_NPC) )
            return TRUE;
        else
            return FALSE;
    }

    // 渲染队友
    if( pPlayer->MyTeamMember )
    {
        if( IsPlayerTypeRender(EPRF_TEAM) )
            return TRUE;
        else
            return FALSE;
    }

	//  [1/9/2011 zhangjiayi]
	// 渲染PK对象	
	if( pPlayer->GetID() == thePlayerRole.GetDuelTarget() )
		return TRUE;	

    // 渲染好友
    if( thePlayerRole.IsFriend(pPlayer->GetName()) )
    {
        if( IsPlayerTypeRender(EPRF_FRIEND) )
            return TRUE;
        else
            return FALSE;
    }

    // 渲染怪物
    if( !bDist && pPlayer->IsMonster() )
    {
        if( IsPlayerTypeRender(EPRF_MONSTER) )
        {
            // 如果是宠物，判断其他玩家是否渲染，不渲染则宠物也不渲染
            if( pPlayer->HaveMaster() && pPlayer->GetMasterID() > -1 )
            {
                CPlayer *pMaster = FindByID(pPlayer->GetMasterID());
                if ( pMaster != NULL )
                {
                    // 判断是否自己宠物
                    if ( pMaster == m_pMe )
                    {
                        if( g_bRenderRole && IsPlayerTypeRender(EPRF_ME))
                            return TRUE;
                        else
                            return FALSE;
                    }

                    // 判断是否队友宠物
                    if ( pMaster->MyTeamMember )
                    {
                        if( IsPlayerTypeRender(EPRF_TEAM) )
                            return TRUE;
                        else
                            return FALSE;
                    }

					// 判断是否是pk对象的宠物
					if ( pMaster->GetID() == thePlayerRole.GetDuelTarget() )
						return TRUE;					
                }
                // 非队友宠物，判断其他玩家是否渲染
                if( IsPlayerTypeRender(EPRF_OTHERS) )
                    return TRUE;
                else
                    return FALSE;
            }
            else
                return TRUE;
        }
        else
            return FALSE;
    }

		 if( !bDist && pPlayer->IsEffect() )
		 { //lyhtexiaoguai
			 return true; //特效怪一直渲染
		 }

    // 其他人物
    if( !bDist && IsPlayerTypeRender(EPRF_OTHERS) )
        return TRUE;
    else
        return FALSE;

    return FALSE;
}

void CPlayerMgr::SuspendCurrentRenderFlag()
{
	if( g_GameState != G_MAIN )
		return;
	m_nLastPlayerRenderFlag = m_nPlayerRenderFlag;
	m_nPlayerRenderFlag = 0; 

	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect,0 );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, 0 );
	GameSetting::Instance()->CommitChanges();
}

void CPlayerMgr::ResumeLastRenderFlag()
{
	if( g_GameState != G_MAIN )
		return;
	m_nPlayerRenderFlag = m_nLastPlayerRenderFlag;
	//m_nPlayerRenderFlag = EPRF_ALL;//lyh++ 修改隐藏玩家显示 
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect,1 );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, 1 );
	GameSetting::Instance()->CommitChanges();
}

void CPlayerMgr::ClearSkillBuf()
{
    m_SkillBufTargetID = -1;
    SetCurUseSkill( 0, 0 );
}

void CPlayerMgr::SetSkillBufPlayer( CPlayer* pTarget )
{
    if( pTarget )
    {
        m_SkillBufTargetID = pTarget->GetID();
    }
}

DWORD CPlayerMgr::GetQuestRankColor( SQuest* pQuest )
{
	DWORD col = 0xffffffff;
	switch (pQuest->RankId)
	{
	case SQuest::eQuestRank_Nor:
		{
			col = Color_Config.getColor(CC_TaskRank0);
			break;
		}
	case SQuest::eQuestRank_Nic:
		{
			col = Color_Config.getColor(CC_TaskRank1);
			break;
		}
	case SQuest::eQuestRank_Exc:
		{
			col = Color_Config.getColor(CC_TaskRank2);
			break;
		}
	case SQuest::eQuestRank_Gold:
		{
			col = Color_Config.getColor(CC_TaskRank3);
			break;
		}
	case SQuest::eQuestRank_Legend:
		{
			col = Color_Config.getColor(CC_TaskRank4);
			break;
		}
	}
	return col;
}

void CPlayerMgr::LoadGlobalData()
{
	
}

bool CPlayerMgr::ProcessShift( float x, float y )
{
	if ((GetKeyboardInput(DIK_LALT) || GetKeyboardInput(DIK_RALT) ))
	{
		CWorldTile* pCurrTile = CURRENTTILE;
		if (NULL == pCurrTile)
		{
			return false;
		}
		SwMap& swmap = pCurrTile->ReachableMap();
		swVec2f kPosition(x,y);
		if (!swmap.CanReach(kPosition))
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_MiniMapFindPath, theXmlString.GetString(eClient_AddInfo_PFError) );
		}
		else
		{
			CommonChatFrame::GetActiveChatFrame()->addAddressText( pCurrTile->GetMapId(),kPosition.x,kPosition.y );		
		}
		return true;
	}
	return false;
}
extern BOOL CanLootHerb(CPlayer* pTargetPlayer, ItemDefine::SItemSkill* pCurSkill, BOOL bShowText);
extern BOOL CanLootMine(CPlayer* pTargetPlayer, ItemDefine::SItemSkill* pCurSkill, BOOL bShowText);
extern BOOL CanLootInsect(CPlayer* pTargetPlayer, ItemDefine::SItemSkill* pCurSkill, BOOL bShowText);

void CPlayerMgr::RenderPlayerTip( )
{
	static S_TextTipInfo sTipInfo;
	if (GetMouseTargetPlayerSeverID() == -1)
	{
		sTipInfo.m_nId = -1;
		if(!theUiManager.IsMouseInUI())
		{
			//theIconInfoMouseTip.Clear();
		}
		//
		return;
	}
	CPlayer* pMousePlayer = FindByID(GetMouseTargetPlayerSeverID());
	if( !pMousePlayer )
		return;

	assert(pMousePlayer);
	if (theHeroGame.GetPlayerMgr()->GetMe() == pMousePlayer)
	{
		return;
	}
	DWORD col = 0;
	char cColor[256];
	char cLine[256];
	std::string strTip;
	if (pMousePlayer->IsMonster())
	{
		{
			//ItemDefine::SMonster* pMonster = GettheItemDetail().GetMonsterByName(pMousePlayer->GetName());
			ItemDefine::SMonster* pMonster = GettheItemDetail().GetMonsterById(pMousePlayer->GetMonsterID());
			if (pMonster && pMonster->nIsInitiative)
			{
				if( theHeroGame.GetPlayerMgr()->GetMe() )
				{
					int l = pMousePlayer->GetLevel() - theHeroGame.GetPlayerMgr()->GetMe()->GetLevel();
					if (l >= -5 && l <= 5)
						col = Color_Config.getColor(CC_MonsterLevelRange5);
					else if (l < -5)
						col = Color_Config.getColor(CC_MonsterLevelLow5);
					else
						col = Color_Config.getColor(CC_MonsterLevelUp5);
				}
				else
					col = Color_Config.getColor(CC_MonsterLevelUp5);
			}
			else
			{
				col = Color_Config.getColor(CC_MonsterNormal);
			}

			// 怪物名字
			pMousePlayer->SetNameColorByInfluence(col);
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			strTip += pMousePlayer->GetName();
			strTip += "\n";

			//怪物称号
			if (pMonster && strlen(pMonster->GetTitle()) > 0)
			{
				//col = Color_Config.getColor((ColorConfigure)(CC_NpcTip_Title));
				sprintf(cColor,"<#%8x>",0xff00ff00);
				strTip += cColor;
				strTip += pMonster->GetTitle();
				strTip += "\n";
			}
			// 怪物前缀
			if (pMonster != NULL && strlen(pMonster->GetNamePrefix()) > 0)
			{
				sprintf(cColor,"<#%8x>",0xff00ff00);
				strTip += cColor;
				strTip += pMonster->GetNamePrefix();
				strTip += "\n";
			}
		}
		if (pMousePlayer->GetTitle().length() > 2 && !pMousePlayer->IsMonster())
		{
			col = Color_Config.getColor((ColorConfigure)(CC_NpcTip_Title));
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			if (std::string::npos != pMousePlayer->GetTitle().find("%s"))
			{
				if (pMousePlayer->HaveMaster())
				{
					CPlayer* pMaster = theHeroGame.GetPlayerMgr()->FindByID(pMousePlayer->GetMasterID());
					if (pMaster)
					{
						char buf[256];
						MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1, pMousePlayer->GetTitle().substr(1, pMousePlayer->GetTitle().length() - 2).c_str(),pMaster->GetName());
						strTip += buf;
					}
				}
			}
			else
			{
				strTip += pMousePlayer->GetTitle();//.substr(1, pMousePlayer->GetTitle().length() - 2);
			}
			strTip += "\n";

		}
		if (!pMousePlayer->IsCollection(false))
		{
			col = Color_Config.getColor((ColorConfigure)(CC_NpcTip_Level));
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			sprintf(cLine,theXmlString.GetString(eClient_PlayerTip_Level),pMousePlayer->GetLevel());
			strTip += cLine;
			strTip += "\n";
		}
		if (pMousePlayer->IsCollection(false))
		{
            //技能采集   少捕捉(待加)
			col = Color_Config.getColor(CC_MonsterTip_SkillFail);
			int nStringId = -1;
			if (pMousePlayer->IsMonsterType(eMT_Mine))
			{
				SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(ItemDefine::eCSI_CaiKuang);
				if( pCharSkill && pCharSkill->bAvailable )
				{
					ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_CaiKuang, pCharSkill->stSkillLevel );
					if (CanLootMine(pMousePlayer,pSkill,false))
					{
						col = Color_Config.getColor(CC_MonsterTip_SkillOK);
					}
				}
				nStringId = eClient_MonsterTip_MineLevel;
				nStringId = -1; //lyh++ 如果是矿石类型，则需要最小等级不进行提示，目前 一骑当千 项目中，只有 偷马活动中的马是矿石类型
			}
			else if(pMousePlayer->IsMonsterType(eMT_Herb))
			{
				SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(ItemDefine::eCSI_CaiYao);
				if( pCharSkill && pCharSkill->bAvailable )
				{
					ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_CaiYao, pCharSkill->stSkillLevel );
					if (CanLootHerb(pMousePlayer,pSkill,false))
					{
						col = Color_Config.getColor(CC_MonsterTip_SkillOK);
					}
				}
				nStringId = eClient_MonsterTip_HerbLevel;
			}
            // 增加捕虫     added by zhuomeng.hu		[11/9/2010]
            else if( pMousePlayer->IsMonsterType( eMT_Insect ) )
            {
                SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_BuChong );
                if( pCharSkill && pCharSkill->bAvailable )
                {
                    ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_BuChong, pCharSkill->stSkillLevel );
                    if ( CanLootInsect( pMousePlayer, pSkill, false ) )
                    {
                        col = Color_Config.getColor( CC_MonsterTip_SkillOK );
                    }
                }
                nStringId = eClient_MonsterTip_InsectLevel;
            }
			if (nStringId != -1)
			{
				sprintf(cColor,"<#%8x>",col);
				strTip += cColor;
				sprintf(cLine,theXmlString.GetString(nStringId),pMousePlayer->GetLevel());
				strTip += cLine;
				strTip += "\n";
			}
		}
		else if(!pMousePlayer->IsPet())
		{
			ItemDefine::SMonster* pMonster = GettheItemDetail().GetMonsterByName(pMousePlayer->GetName());
			if (pMonster)
			{
				{
					col = Color_Config.getColor(CC_MonsterTip_Strong);
					sprintf(cColor,"<#%8x>",col);
					strTip += cColor;
					int nStringId = eClient_MonsterTip_Normal;
					if (pMonster->stMonsterType == eMT_LeaderMonster)
					{
						nStringId = eClient_MonsterTip_Enhance;
					}
					else if (pMonster->stMonsterType == eMT_BossMonster)
					{
						nStringId = eClient_MonsterTip_Leader;
					}
					sprintf(cLine,theXmlString.GetString(eClient_MonsterTip_Strong),theXmlString.GetString(nStringId));
					strTip += cLine;
					strTip += "\n";
				}
			}
		}
	}
	else if (pMousePlayer->IsNpc() )
	{
		{
			col = Color_Config.getColor((ColorConfigure)(CC_NpcTip_Name));
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			strTip += pMousePlayer->GetName();
			strTip += "\n";

		}
		if (pMousePlayer->GetTitle().length() > 2)
		{
			col = Color_Config.getColor((ColorConfigure)(CC_NpcTip_Title));
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			//不知道为什么这里要把称号前后截掉。这样会导致乱码。
			//strTip += pMousePlayer->GetTitle().substr(1, pMousePlayer->GetTitle().length() - 2);
			strTip += pMousePlayer->GetTitle();
			strTip += "\n";

		}
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pMousePlayer->GetNpcID());
		if (pInfo && pInfo->_nType == eNT_Item)
		{//采集NPC不显示等级
		}
		else
		{
			col = Color_Config.getColor((ColorConfigure)(CC_NpcTip_Level));
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			sprintf(cLine,theXmlString.GetString(eClient_PlayerTip_Level),pMousePlayer->GetLevel());
			strTip += cLine;
			strTip += "\n";

		}
	}//--end of npc
	else if(pMousePlayer->IsPlayer())
	{
		{
			col = pMousePlayer->GetPkNameColor();
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			strTip += pMousePlayer->GetName();
			strTip += "\n";

		}
		if (pMousePlayer->GetGuildName() && pMousePlayer->GetGuildName()[0] != '\0')
		{
			col = Color_Config.getColor((ColorConfigure)(CC_PlayerTip_Gang));
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			strTip += pMousePlayer->GetGuildName();
			strTip += "\n";
		}
		{
			col = Color_Config.getColor((ColorConfigure)(CC_PlayerTip_Level));
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			sprintf(cLine,theXmlString.GetString(eClient_PlayerTip_Level),pMousePlayer->GetLevel());
			strTip += cLine;
			strTip += "\n";
		}
		{
			col = Color_Config.getColor((ColorConfigure)(CC_PlayerTip_Profession));
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			std::string strProfession = theXmlString.GetString(eProfession_Unknown);
			if (pMousePlayer->GetProfession() != EArmType_MaxSize)
			{
				CProfessionInfo* pInfo = GetSystemConfig()->GetProessionInfoFromID(pMousePlayer->GetProfession());
				if (pInfo)
				{
					strProfession = pInfo->m_strProShow.c_str();
				}
			}
			sprintf(cLine,theXmlString.GetString(eClient_PlayerTip_Profession),strProfession.c_str());
			strTip += cLine;
			strTip += "\n";
		}
	}

	
	sTipInfo.SetInfo( strTip.c_str(),DT_LEFT );
	bool bForceShopTip = false;	
	if( sTipInfo.Id() != GetMouseTargetPlayerSeverID() )
		bForceShopTip = true;
	sTipInfo.m_nId = GetMouseTargetPlayerSeverID();
	RECT rcWindowClient;
	GetClientRect( g_hWnd, &rcWindowClient );
	
	if( s_CUI_ID_FRAME_MiniMap.GetFrame() )
	{

		LONG nTipX = 0;
		LONG nTipY = 0;
		//如果配置文件中配置的都是为0的时候则用鼠标的位置，反之用固定位置
		if ( gCfg.m_TargetTipsOffset.left !=0 && gCfg.m_TargetTipsOffset.top != 0)
		{
		 nTipX = rcWindowClient.right - gCfg.m_TargetTipsOffset.left * ControlObject::GetREAL_SCALE(s_CUI_ID_FRAME_MiniMap.GetFrame());
	     nTipY = rcWindowClient.bottom - gCfg.m_TargetTipsOffset.top * ControlObject::GetREAL_SCALE(s_CUI_ID_FRAME_MiniMap.GetFrame());
		}else
		{
		 POINT CursorPos;
		 GetCursorPos(&CursorPos);
		 ScreenToClient( g_hWnd, &CursorPos );
		 nTipX = CursorPos.x + gCfg.m_TargetTipsOffset.right;
		 nTipY = CursorPos.y + gCfg.m_TargetTipsOffset.bottom;
		}
		


		theIconInfoMouseTip.SetDisplayInfo( &sTipInfo,
			nTipX, nTipY, false,
			s_CUI_ID_FRAME_MiniMap.GetFrame()->GetFontIndex(), 
			s_CUI_ID_FRAME_MiniMap.GetFrame()->GetFontSize() * ControlObject::GetREAL_SCALE(s_CUI_ID_FRAME_MiniMap.GetFrame()),
			s_CUI_ID_FRAME_MiniMap.GetFrame()->GetFontColor(),
			false );
	}
}



void CPlayerMgr::SNpcQuestInfo::InitialRelateQuestInfo()
{
	vectorRelateQuestInfo.clear();
	CWorldTile* pTile = CURRENTTILE;
	if (NULL == pTile)
	{
		return;
	}
	std::vector<CPlayerRole::QuestInfo*>& vtQuestInfo = thePlayerRole.GetActiveQuestInfo();
	for ( int n=0; n<vtQuestInfo.size(); n++ )
	{
		SQuest *pQuest = theQuestManager.GetQuest( vtQuestInfo[n]->nQuestId );
		if (!pQuest)
		{
			continue;
		}
		if (theQuestManager.IsQuestNotGain(vtQuestInfo[n]->chState))
		{
			const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->AcceptTargetId,pTile->GetMapId());
			if (pInfo &&  (Common::_tstring::toNarrowString(pInfo->_szName.c_str()) == strName) )
			{
				vectorRelateQuestInfo.push_back(vtQuestInfo[n]);
			}
		}
		else
		{
			const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->ReplyTargetId,pTile->GetMapId());
			if (pInfo && (Common::_tstring::toNarrowString(pInfo->_szName.c_str()) == strName) && (pTile->GetMapId() == pInfo->_mapId))
			{
				vectorRelateQuestInfo.push_back(vtQuestInfo[n]);
			}
		}
	}
}

BOOL CPlayerMgr::CanReqScript()
{
    if( HQ_TimeGetTime() - m_dwLastReqScriptTime < 1000 )
        return FALSE;

    m_dwLastReqScriptTime = HQ_TimeGetTime();
    return TRUE;
}

BOOL CPlayerMgr::IsPlayerValid( const CPlayer *pCheckPlayer )
{
    if( !m_mapPlayers.empty() )
    {
        std::map<GameObjectId, CPlayer*>::iterator it;
        for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
        {
            CPlayer* pPlayer = it->second;
            if( pPlayer && pCheckPlayer == pPlayer )
                return TRUE;
        }
    }
    if( !m_vectorDeathPlayer.empty() )
    {
        std::vector< CPlayer* >::iterator iter;
        for( iter = m_vectorDeathPlayer.begin(); iter != m_vectorDeathPlayer.end(); ++iter )
        {
            CPlayer* pPlayer = (CPlayer*)*iter;
            if( pPlayer && pCheckPlayer == pPlayer)
                return TRUE;
        }
    }
	if( !m_vectorNoLogicPlayer.empty() )
	{
		std::vector< CPlayer* >::iterator iter;
		for( iter = m_vectorNoLogicPlayer.begin(); iter != m_vectorNoLogicPlayer.end(); ++iter )
		{
			CPlayer* pPlayer = (CPlayer*)*iter;
			if( pPlayer && pCheckPlayer == pPlayer)
				return TRUE;
		}
	}

    return FALSE;
}
void CPlayerMgr::AutoSelectMonster()
{
    guardfunc;
	if(!GetMe())
		return;

    if( m_pMe->IsDead() )
        return;

    std::vector<CPlayer*> vectorSelPlayer;

    std::map< GameObjectId, CPlayer* >::iterator it;
    for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
    {
        CPlayer* pPlayer = it->second;
        if( pPlayer->IsItem() || pPlayer->IsNpc() || pPlayer->IsPet() || pPlayer->IsPlayer() )
            continue;

        if( pPlayer->IsMonster() )
        {
            short shMonsterType = pPlayer->GetMonsterType();
            if( pPlayer->IsCollection(false)
                || shMonsterType == eMT_Building
                || shMonsterType == eMT_Mine
                || shMonsterType == eMT_Mount
                || shMonsterType == eMT_Pet
                || shMonsterType == eMT_Treasure
                || shMonsterType == eMT_Herb
                || shMonsterType == eMT_Insect )
            {
                continue;
            }

            //修改这里，不管可见不可见都要判断
			if(!GetMe())
                continue;

            if( pPlayer->GetMasterID() >= 0 ) //召唤类型怪
                continue;   

			//lyh++ 自动挂机的时候，不能进行攻击的怪物 不去选择它
			if(pPlayer->GetRealCountry() != CountryDefine::Country_Init&&
				thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry != CountryDefine::Country_Init&&
				thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry ==pPlayer->GetRealCountry())
				continue;

			if ((pPlayer->GetTypeStatus() == MonsterDefine::StatusUnMoveNpc 
				|| pPlayer->GetTypeStatus() == MonsterDefine::StatusMoveNpc ))
			{
				continue;
			}

        }

        if( pPlayer->GetDistanceToRole() > gCfg.m_fNameShowDistance )
            continue;

        if( pPlayer->NeedRemove() )
            continue;

        if( pPlayer->GetCurRenderAlpha() < 0.0618f )
            continue;

        D3DXVECTOR3 vCurPos = GetMe()->GetPos();
        D3DXVECTOR3 vDestPos = pPlayer->GetPos();
        swVec2f kOrgPosition(vCurPos.x,vCurPos.y);
        swVec2f kDestPosition(vDestPos.x,vDestPos.y);
        SwMap& swmap = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile()->ReachableMap();
        if (!swmap.CanMove(kOrgPosition,kDestPosition))  //只查找直接到达的怪物
            continue;

        D3DXVECTOR3 pos = pPlayer->GetPos();
        if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsInZone(pos.x,pos.y))  //攻击范围的不打
            continue;

		if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsNoExistMonster(pPlayer->GetMonsterID()))
			continue;

        if( pPlayer )
        {
            CPlayerAnim* pAnim = pPlayer->GetAnim();

            Box *pBox = pAnim->GetWorldBBox();

            if( pBox->v[4].z - pBox->v[0].z < 0.001f )
            {
                vectorSelPlayer.push_back( pPlayer );
            }

           if( pPlayer == m_pMe || pPlayer->MasterIsMe() )
           {
               continue;
           }
           vectorSelPlayer.push_back( pPlayer );
        }
    }

    int nSelPlayerCount = vectorSelPlayer.size();
    int nSelPlayerID = -1;
    if( nSelPlayerCount > 0 )
    {
        if( nSelPlayerCount == 1 )
        {
            SetLockNpc( vectorSelPlayer[0]->GetID() );
        }
        else
        {
            CPlayer* pLockPlayer = NULL;
            if( GetLockPlayerID() < 0 )
            {
                pLockPlayer = vectorSelPlayer[0];

                for( int nPlayer = 1; nPlayer < nSelPlayerCount; nPlayer++ )
                {
                    CPlayer* pPlayer = vectorSelPlayer[nPlayer];

                    if( pPlayer->GetDistanceToRole() < pLockPlayer->GetDistanceToRole() )
                    {
                        pLockPlayer = pPlayer;
                    }
                }
            }
            else
            {
                CPlayer* pSelPlayer = NULL;

                for( int nPlayer = 0; nPlayer < nSelPlayerCount; nPlayer++ )
                {
                    if( GetLockPlayerID() == vectorSelPlayer[nPlayer]->GetID() )
                    {
                        pSelPlayer = vectorSelPlayer[nPlayer];
                    }
                }

                if( pSelPlayer )
                {
                    for( int nPlayer = 0; nPlayer < nSelPlayerCount; nPlayer++ )
                    {
                        CPlayer* pPlayer = vectorSelPlayer[nPlayer];

                        if( pPlayer->GetDistanceToRole() > pSelPlayer->GetDistanceToRole() )
                        {
                            if( pLockPlayer )
                            {
                                if( pPlayer->GetDistanceToRole() < pLockPlayer->GetDistanceToRole() )
                                {
                                    pLockPlayer = pPlayer;
                                }
                            }
                            else
                            {
                                pLockPlayer = pPlayer;
                            }
                        }
                    }

                    if( !pLockPlayer )
                    {
                        pLockPlayer = vectorSelPlayer[0];

                        for( int nPlayer = 1; nPlayer < nSelPlayerCount; nPlayer++ )
                        {
                            CPlayer* pPlayer = vectorSelPlayer[nPlayer];

                            if( pPlayer->GetDistanceToRole() < pLockPlayer->GetDistanceToRole() )
                            {
                                pLockPlayer = pPlayer;
                            }
                        }
                    }
                }
                else
                {
                    pLockPlayer = vectorSelPlayer[0];

                    for( int nPlayer = 1; nPlayer < nSelPlayerCount; nPlayer++ )
                    {
                        CPlayer* pPlayer = vectorSelPlayer[nPlayer];

                        if( pPlayer->GetDistanceToRole() < pLockPlayer->GetDistanceToRole() )
                        {
                            pLockPlayer = pPlayer;
                        }
                    }
                }
            }

            if( pLockPlayer )
            {
                SetLockNpc( pLockPlayer->GetID() );
            }
            pLockPlayer = NULL;
        }
    }
    vectorSelPlayer.clear();
}

void CPlayerMgr::UpdateMonsterType()
{
	if(!GetMe())
		return;

	if( m_pMe->IsDead() )
		return;

	s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().ClearMonsterSet();

	std::map< GameObjectId, CPlayer* >::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
	{
		CPlayer* pPlayer = it->second;
		if( pPlayer->IsItem() || pPlayer->IsNpc() || pPlayer->IsPet() || pPlayer->IsPlayer() )
			continue;

		if( pPlayer->IsMonster() )
		{
			short shMonsterType = pPlayer->GetMonsterType();
			if( pPlayer->IsCollection(false)
				|| shMonsterType == eMT_Building
				|| shMonsterType == eMT_Mine
				|| shMonsterType == eMT_Mount
				|| shMonsterType == eMT_Pet
				|| shMonsterType == eMT_Treasure
				|| shMonsterType == eMT_Herb
				|| shMonsterType == eMT_Insect )
			{
				continue;
			}

			//修改这里，不管可见不可见都要判断
			if(!GetMe())
				continue;

			if( pPlayer->GetMasterID() >= 0 ) //召唤类型怪
				continue;            
		}

		if( pPlayer->GetDistanceToRole() > gCfg.m_fNameShowDistance )
			continue;

		if( pPlayer->NeedRemove() )
			continue;

		if( pPlayer->GetCurRenderAlpha() < 0.0618f )
			continue;

		D3DXVECTOR3 pos = pPlayer->GetPos();
 		//if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsInZone(pos.x,pos.y))  //攻击范围的不打 没用 它以 0 0 0 点为重心点做半径，地图过大的时候，将超出这个范围，就不能选中
 		//	continue;                                                             //下面已经对上边这一行代码做了修复，他以主角位置为中心判断的

		D3DXVECTOR3 mePos = GetMe()->GetPos();

		float xOff = mePos.x - pos.x;
		float yOff = mePos.y - pos.y;
		float fDist = sqrtf(xOff * xOff + yOff * yOff);
		

		if(fDist >= s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().GetZoneRadius())
			continue;

		if( pPlayer )
		{
			CPlayerAnim* pAnim = pPlayer->GetAnim();

			Box *pBox = pAnim->GetWorldBBox();

			if( pPlayer == m_pMe || pPlayer->MasterIsMe() )
			{
				continue;
			}

			s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().AddMonsterSet(pPlayer->GetMonsterID());
		}
	}
}


bool CPlayerMgr::CreateDynamicCollision( CPlayer* pPlayer )
{
	if( !pPlayer || !pPlayer->GetAnim() )
		return false;

	IMex* pMex = pPlayer->GetAnim()->GetMex();
	if( !pMex || !pMex->GetGeometry())
		return false;

	MeMatrix* pMatrices = pPlayer->GetAnim()->GetMatrices();
	// modified, [9/29/2010 zhangjiayi]
	static int s_maxVertexCount = 0;
	int maxVertexCount = 0;
	static std::vector<Vector> vertices;	
	// 统计子模型中，顶点数最大值
	for( int nChunk = 0; nChunk < pMex->GetGeometry()->GetChunkCount(); nChunk++ )
	{
		IRenderable* pChunk = pMex->GetGeometry()->GetChunk(nChunk);
		if (maxVertexCount < pChunk->GetVertexCount())
			maxVertexCount = pChunk->GetVertexCount();
	}
	if( maxVertexCount != s_maxVertexCount )
		vertices.resize(maxVertexCount);

	s_maxVertexCount = maxVertexCount;

	for( int nChunk = 0; nChunk < pMex->GetGeometry()->GetChunkCount(); nChunk++ )
	{
		Mex2GeoChunk* pChunk = (Mex2GeoChunk*)pMex->GetGeometry()->GetChunk(nChunk);

		float* vers = (float*)&vertices[0];

		if( pChunk->IsEffect() )
			continue;

		char lwrName[MAX_PATH] = {0};
		const char* pszName = pChunk->GetName();
		strncpy( lwrName, pszName, MAX_PATH );
		strlwr(lwrName);
		// 假定动态模型只碰撞人，不碰撞相机
		if( strstr(lwrName, "rcoli") || strstr(lwrName, "coli") )	// 只碰撞人，不碰相机
		{
			pChunk->BlendVertex( vers, NULL, s_maxVertexCount, pMex, (float*)pMatrices, NULL );
			m_DynamicCollisionBsp.AddMesh( vers, pChunk->GetVertexCount(), (short*)pChunk->GetIndicesLocked(), pChunk->GetFaceCount() );
		}

		if(strstr(lwrName,"floor"))
		{
			pChunk->BlendVertex( vers, NULL, s_maxVertexCount, pMex, (float*)pMatrices, NULL );
			m_DynamicFloorBsp.AddMesh( vers, pChunk->GetVertexCount(), (short*)pChunk->GetIndicesLocked(), pChunk->GetFaceCount() );
		}
	}
	return true;
}

bool CPlayerMgr::PushVipPlayer( const char* szName, GameObjectId stID )
{
	if( !szName || szName[0] == '\0' || stID < 0 )
		return false;

	std::map< std::string, GameObjectId >::iterator it = m_mapVipPlayer.find(szName);
	if (it == m_mapVipPlayer.end())
	{
		std::string strPlayerName = szName;
		m_mapVipPlayer.insert(std::map< std::string, GameObjectId >::value_type(strPlayerName, stID));
	}
	return true;
}

bool CPlayerMgr::IsVipPlayer( const char* szName )
{
	if( !szName || szName[0] == '\0' )
		return false;

	std::map< std::string, GameObjectId >::iterator it = m_mapVipPlayer.find(szName);
	if (it != m_mapVipPlayer.end())
		return true;

	return false;
}

bool CPlayerMgr::CheckCanTabCampMonster(CPlayer* pPlayer)
{
	if (!pPlayer)
	{
		return false;
	}

	if (thePlayerRole.GetInfluence() != CampDefine::NoneCamp && thePlayerRole.GetInfluence() == pPlayer->GetInfluence())
	{
		return false;
	}

	return true;
}

bool CPlayerMgr::CanTab(CPlayer* pPlayer)
{
    if (!pPlayer)
        return false;

    if (pPlayer->IsItem() )
    {
        return false;
    }
    else if( pPlayer->IsPlayer() || pPlayer->IsNpc())
    {
        // 隐身状态
        if( pPlayer->m_cFightStatus.IsHide() )
            return false;

        // 不攻击不能Tab
        if (!GetMe() || !GetMe()->canAttack(pPlayer))
            return false;
    }
    else if( pPlayer->IsMonster() )
    {
		if (!CheckCanTabCampMonster(pPlayer))
		{
			return false;
		}

        short shMonsterType = pPlayer->GetMonsterType();
        if( pPlayer->IsCollection(false) || shMonsterType == eMT_Building )
        {
            return false;
        }

        // 不可见的召唤物
        if( !pPlayer->IsVisibleToOtherPlayer() )
        {
            if( GetMe() )
            {
                if( GetMe()->GetID() != pPlayer->GetMasterID() )
                    return false;
            }
            else
                return false;
        }

       //没有开启 则不选择宠物
		if(!gCfg.GetIsOpenPetAtter() && pPlayer->HaveMaster())
			return false;

		 // 如果宠物的主人不可攻击，它也不能被Tab
        if ( pPlayer->HaveMaster() )
        {
            CPlayer* pMaster = theHeroGame.GetPlayerMgr()->FindByID(pPlayer->GetMasterID());
			if( !GetMe() )
				return false;
            if (pMaster && !GetMe()->canAttack(pMaster))
                return false;
        }
    }
    return true;
}

void CPlayerMgr::CheckDestroyAnimLowMemory(CPlayer* pPlayer)
{
	if( !pPlayer || !pPlayer->IsPlayer() || !pPlayer->GetAnim() )
		return;

	// 内存大于50M则不销毁动画数据，50M可看情况调整
	if( theHeroGame.GetAvailPhyMemory() > 50 * 1024 * 1024 )
		return;

	if( pPlayer->GetDistanceToRole() > 30 )
	{
		DWORD dwLastRenderTime = pPlayer->GetLastRenderTime();
		if( dwLastRenderTime != 0 && HQ_TimeGetTime() - dwLastRenderTime > 5000 )
		{
			if( m_iDestroyCharLimitPerFrame > 0 )
			{
				--m_iDestroyCharLimitPerFrame;
				pPlayer->DestroyCS();
			}
		}
	}
}

void CPlayerMgr::ShowMosterTip(int nCount)
{
	if(nCount <= 0)
		return;

	typedef std::multimap<int,CPlayer*>::iterator  IterMap;
	std::multimap<int,CPlayer*> mapSet;
	for (int i = 0;i < nCount;++i)
	{
		if(!m_PlayerDistQueue[i].bRendered)
			continue;

		CPlayer *pPlayer = m_PlayerDistQueue[i].pPlayer;
		if(!pPlayer)
			continue;

		if(!pPlayer->IsMonster() || pPlayer->IsPet())
			continue;

		CMapAreaManager* pAreaManager = m_StageDataLoader.GetMapAreaManager();
		if(!pAreaManager)
			return;

		int nMaxArea = pAreaManager->GetMaxArea();
		for (int n = 0;n < nMaxArea;++n)
		{
			SArea* pArea = pAreaManager->GetAreaByID(n);
			if(!pArea)
				return;

			//没有说话区域，不算在内
			if(pArea->vctActionData.empty())
				continue;

			float fx = 0.0f,fy = 0.0f,fz = 0.0f;
			pPlayer->GetPos( &fx, &fy, &fz );
			POINT pt;
			pt.x = fx;
			pt.y = fy;

			RECT rc;
			rc.left = TileToFloat(pArea->m_rcArea.left);
			rc.top  = TileToFloat(pArea->m_rcArea.top);
			rc.right = TileToFloat(pArea->m_rcArea.right);
			rc.bottom = TileToFloat(pArea->m_rcArea.bottom);

			if(!PtInRect(&rc,pt))
				continue;

			mapSet.insert(std::multimap<int,CPlayer*>::value_type(n,pPlayer));
			break;
		}
	}

	std::vector<int> vecSet;
	vecSet.clear();
	std::multimap<int,CPlayer*>::iterator it = mapSet.begin();
	for (;it != mapSet.end();++it)
	{
		std::vector<int>::iterator setIt = std::find(vecSet.begin(),vecSet.end(),it->first);
		if(setIt == vecSet.end())
			vecSet.push_back(it->first);
	}

  	for (int i = 0;i < vecSet.size();++i )
  	{
  		std::multimap<int,CPlayer*>::size_type nSize = mapSet.count(vecSet[i]);
  		if(nSize == 0)
  			return;
  
  		bool bRepeat = false;

		std::pair<IterMap,IterMap> pairResult = mapSet.equal_range(vecSet[i]);
		for(IterMap iter = pairResult.first;iter != pairResult.second;++iter)
		{
			CPlayer *pPlayer = iter->second;
			if(!pPlayer)
				return;

			if(pPlayer->GetMonsterAction())
			{
				bRepeat = true;
				break;
			}
		}

  		if(bRepeat)
  			continue;

		IterMap from = mapSet.lower_bound(vecSet[i]);
  		int nCount = rand()%nSize;
  		std::advance(from,nCount);
  		CPlayer* pPlayer = from->second;
  		if(!pPlayer)
  			return;

		CMapAreaManager* pAreaManager = m_StageDataLoader.GetMapAreaManager();
		if(!pAreaManager)
			return;

		SArea *pArea = pAreaManager->GetAreaByID(vecSet[i]);
		if(!pArea)
			return;

		pPlayer->InitMonsterAction(vecSet[i],pArea);
  	}
}

void CPlayerMgr::LoadMonsterConfig(CWorldTile* worldTile)
{
	if(!worldTile)
		return;

// 	char szMapName[MAX_PATH] = {0};
// 	char szTemp[MAX_PATH] = {0};
	char szMonsterCfg[MAX_PATH] = {0};
// 	strcpy_s(szTemp,sizeof(szTemp) - 1,pszFilePath);
// 	char *p = strchr(szTemp, '\\');
// 	if( p )
// 		strcpy(szMapName, p+1);
// 	else
// 		strcpy(szMapName, szTemp);
// 	p = strchr(szMapName, '.');
// 	if( p )
// 		*p = '\0';
	if (worldTile->GetMonsterPath()[0] == '\0')
	{
		char cTemp[MAX_PATH];
		strcpy_s(cTemp,MAX_PATH,worldTile->GetPathName());
		char* pFind = strstr(cTemp,".mew");
		strcpy(&pFind[1],"monster");
		worldTile->SetMonsterPath(cTemp);
	}
	// 预加载地图怪模型数据
	MeSprintf_s(szMonsterCfg,sizeof(szMonsterCfg)/sizeof(char) -1 , "%s\\%s", SwGlobal::GetWorld()->GetWorldPath(), worldTile->GetMonsterPath());

	m_StageDataLoader.Clear();
	m_StageDataLoader.loadXMLSettings(szMonsterCfg);
}

SArea* CPlayerMgr::GetAreaByIndex(int nIndex)
{
	CMapAreaManager *pAreaManager = m_StageDataLoader.GetMapAreaManager();
	if(!pAreaManager)
		return NULL;

	return pAreaManager->GetAreaByID(nIndex);
}

void CPlayerMgr::AttackPlayer( CPlayer* pPlayer )
{
	
	SetLockNpc(pPlayer->GetID());

	// add by zmy, 当锁定怪物的时候立即进入战斗状态
	if ( m_pMe != NULL )
	{
		if (m_pMe->IsYabiaoState())
		{
			return ; //lyh++ 人在马车上的时候不能进行普通攻击
		}
		if( ( pPlayer->IsMonster() && !pPlayer->IsPet() ) || thePlayerRole.GetDuelTarget() == pPlayer->GetID() )
		{
			//if ( !m_pMe->HasFightFlag(eFighting) )
			//{
			//	m_pMe->AddFightFlag( eFighting );
			//}
			if ( !m_pMe->IsFightPose() )
			{
				m_pMe->ChangeToFightPose();
			}
		}else if(pPlayer->IsEffect())
		{
			//1:特效怪可以攻击的时候 
			EFFECTCHARCONFIG _Config;
			if(theEffectCharConfig.FindEffectCharConfigBySkillID(_Config,pPlayer->GetEffectCharSkillID()))
			{
				if(_Config.bCanBeAttack)
				{
					if ( !m_pMe->IsFightPose() )
					{
						m_pMe->ChangeToFightPose();
					}
				}

			}
			
		}
		else
		{
			if ( m_pMe->HasFightFlag(eFighting) )
			{
				m_pMe->ClearFightFlag( eFighting );
			}
		}
	}


	//发消息通知服务器，攻击锁定的目标
	g_bTheRoleAttackLockTarget = TRUE;

	g_nRoleCommonAttackStatus = CAS_NEED_AUTO_ATTACK;

	MoveRoleToPlayer( pPlayer, FALSE, 0.f, TRUE );

	m_pMe->SetPendingClearFightFlag(FALSE);
}
void	CPlayerMgr::AddNoLogicPlayer( CPlayer* pPlayer )
{
	m_vectorNoLogicPlayer.push_back( pPlayer );
}
void	CPlayerMgr::ClearNoLogicPlayer( CPlayer* pCheckPlayer )
{
	if( !m_vectorNoLogicPlayer.empty() )
	{
		std::vector< CPlayer* >::iterator iter;
		for( iter = m_vectorNoLogicPlayer.begin(); iter != m_vectorNoLogicPlayer.end(); ++iter )
		{
			CPlayer* pPlayer = (CPlayer*)*iter;
			if( pPlayer && pCheckPlayer == pPlayer)
			{
				m_vectorNoLogicPlayer.erase( iter );
				return;
			}
		}
	}	
}


void CPlayerMgr::InitBaseData()
{
	m_NumTexSet.clear();
	m_pFont  = NULL;
	m_bShowMonsterArea = false;
}

void CPlayerMgr::InitMustData()
{
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	HRESULT hr = FALSE;
	IRenderer* r = GetEngine()->GetRenderer();
	int nWidth = 20;
	//创建字体，用于绘制
	if(!m_pFont)
	{
		HDC *pHDC = NULL;
		D3DXCreateFont( pd3dDevice, nWidth, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, 
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, "微软雅黑", &m_pFont );
	}

	//创建1000张小纹理，宽度为20 * 20
	for (int i = 0;i < 1000;++i)
	{
		IDirect3DSurface9 *pOldRs = NULL;
		IDirect3DSurface9 *pNewRs = NULL;
		//获得当前绘制缓冲
		hr = pd3dDevice->GetRenderTarget(0,&pOldRs);
		if(FAILED(hr))
			return;

		//创建绘制纹理
		LPDIRECT3DTEXTURE9 pTex = NULL;
		if(i <= m_NumTexSet.size())
		{
			if (FAILED(pd3dDevice->CreateTexture(
				nWidth,
				nWidth,
				1,
				D3DUSAGE_RENDERTARGET,
				D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&pTex,
				NULL)))
				return;

			m_NumTexSet.push_back(pTex);
		}
		else
			pTex = m_NumTexSet[i];

		if(!pTex)
			return;

		//设置当前绘制缓冲区为改纹理
		hr = pTex->GetSurfaceLevel(0,&pNewRs);
		if(FAILED(hr))
			return;

		//渲染字体到当前纹理上
		pd3dDevice->SetRenderTarget(0,pNewRs);
		pd3dDevice->Clear(0L, NULL, D3DCLEAR_TARGET, 0x00ffffff, 1.0f, 0L);
		RECT fontRect = {0,0,nWidth,nWidth};
		if(m_pFont)
		{
			char szWord[64] = {0};
			MeSprintf_s(szWord,sizeof(szWord),"%d",i);
			m_pFont->DrawTextA( 0, szWord, -1, &fontRect, DT_CENTER|DT_VCENTER, 0xffff0000 );	
		}
		//恢复渲染目标
		pd3dDevice->SetRenderTarget(0, pOldRs);
	}
}

void CPlayerMgr::ResetRevice()
{
	if(m_pFont)
		m_pFont->OnResetDevice();
}

void CPlayerMgr::ShowMonsterArea()
{
	if(!m_bShowMonsterArea)
		return;

	CMapAreaManager* pAreaManager = m_StageDataLoader.GetMapAreaManager();
	if(!pAreaManager)
		return;

	static bool bFirst = true;
	if(bFirst)
	{
		InitMustData();
		bFirst = false;
	}

	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	HRESULT hr = FALSE;
	IRenderer* r = GetEngine()->GetRenderer();
	int nMaxArea = pAreaManager->GetMaxArea();
	for (int n = 0;n < nMaxArea;++n)
	{
		SArea* pArea = pAreaManager->GetAreaByID(n);
		if(!pArea)
			return;

		RECT rc;
		rc.left = TileToFloat(pArea->m_rcArea.left);
		rc.top  = TileToFloat(pArea->m_rcArea.top);
		rc.right = TileToFloat(pArea->m_rcArea.right);
		rc.bottom = TileToFloat(pArea->m_rcArea.bottom);

		CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->GetMe();

		D3DXVECTOR3 vPos = pPlayer->GetPos();

		static float fl = 1.0f;
		vPos.z += fl;

		GetDrawer()->DrawLine3D(D3DXVECTOR3(rc.left,rc.top,vPos.z),D3DXVECTOR3(rc.left,rc.bottom,vPos.z) , 0xFFFFFFFF );

		GetDrawer()->DrawLine3D(D3DXVECTOR3(rc.left,rc.top,vPos.z),D3DXVECTOR3(rc.right,rc.top,vPos.z) , 0xFFFFFFFF );

		GetDrawer()->DrawLine3D(D3DXVECTOR3(rc.right,rc.top,vPos.z),D3DXVECTOR3(rc.right,rc.bottom,vPos.z) , 0xFFFFFFFF );

		GetDrawer()->DrawLine3D(D3DXVECTOR3(rc.left,rc.bottom,vPos.z),D3DXVECTOR3(rc.right,rc.bottom,vPos.z) , 0xFFFFFFFF );

		//---------------------------------------------------------------------

		struct VBS
		{
			D3DXVECTOR3 p;
			DWORD       color;
			float     u,v;
		};

		VBS vertex[4];
		DWORD dwColor = 0xffffffff;
		RECT *lpDestRect = &rc;

		static float u1 = 0.0f,v1 = 0.0f;
		static float u2 = 1.0f,v2 = 0.0f;
		static float u3 = 0.0f,v3 = 1.0f;
		static float u4 = 1.0f,v4 = 1.0f;
		vertex[0].p = D3DXVECTOR3(  lpDestRect->left , lpDestRect->top, vPos.z);
		vertex[0].u = u1;
		vertex[0].v = v1;
		vertex[0].color = dwColor;

		vertex[1].p = D3DXVECTOR3( lpDestRect->left, lpDestRect->bottom, vPos.z);
		vertex[1].u = u2;
		vertex[1].v = v2;
		vertex[1].color = dwColor;

		vertex[2].p = D3DXVECTOR3( lpDestRect->right, lpDestRect->top, vPos.z );
		vertex[2].u = u3;
		vertex[2].v = v3;
		vertex[2].color = dwColor;

		vertex[3].p = D3DXVECTOR3( lpDestRect->right, lpDestRect->bottom, vPos.z );
		vertex[3].u = u4;
		vertex[3].v = v4;
		vertex[3].color = dwColor;

		if( n < m_NumTexSet.size() )
		{
			r->SetTexture(0, m_NumTexSet[n]);
		}

		r->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1);
		r->SetRenderState(D3DRS_LIGHTING, FALSE);
		r->SetRenderState(D3DRS_FOGENABLE, FALSE);
		r->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		r->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		r->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		r->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		r->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE );
		r->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
		r->SetRenderState(D3DRS_ZENABLE,FALSE);

		r->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
		r->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		r->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
		r->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
		r->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		r->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

		r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0);

		r->Commit();

		pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vertex, sizeof(VBS) );
	}
}

void CPlayerMgr::ClearMustData()
{
	if(m_pFont)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	for (int i = 0;i < m_NumTexSet.size();++i)
	{
		IDirect3DTexture9 *pTex = m_NumTexSet[i];
		if(pTex)
			pTex->Release();
	}

	m_NumTexSet.clear();

	m_bShowMonsterArea = false;
}


short CPlayerMgr::ProcessExpHead( const char* szText, std::string& strRet )
{
	short shExpHeadId = -1;
	if( !szText )
		return shExpHeadId;

	std::string strParse = szText;

	std::string::size_type nBegin = strParse.find("[headid=");
	std::string::size_type nEnd   =	strParse.find(']');

	if(nBegin != std::string::npos && nEnd != std::string::npos)
	{
		std::string strHeadId = strParse.substr(nBegin + 8,nEnd - nBegin - 8);
		int nId = 0;
		if(sscanf_s(strHeadId.c_str(),"%d",&nId) == 1)
			shExpHeadId = (short)nId;
	}

	if( shExpHeadId != -1 )
	{
		// 去掉headid字段
		std::string strTemp = strParse;
		char strHeadId[128] = {0};

		sprintf_s(strHeadId, sizeof(strHeadId)-1, "[headid=%d]", shExpHeadId);
		std::string::size_type nFind = strTemp.find(strHeadId);
		if(nFind != std::string::npos )
		{
			strParse = strTemp.substr(0, nFind);
			strParse += strTemp.substr(nFind + strlen(strHeadId), strTemp.length() - nFind - strlen(strHeadId));
		}
	}
	strRet = strParse;
	return shExpHeadId;

}

void CPlayerMgr::OnMsgPetCardList(Msg *m_msg)
{
	s_CUI_ID_FRAME_SuAnimalCardList.UpdateIdentify(m_msg);
	if (GetMe() && !gCfg.m_SuAnimalCardEffect.empty())
	{
		PlayEffect((char*) gCfg.m_SuAnimalCardEffect.c_str(),GetMe());
	}
}

void CPlayerMgr::OnMsgPetCardListAll(Msg *m_msg)
{
	s_CUI_ID_FRAME_SuAnimalCardList.UpdateAllIdentify(m_msg);
}

void CPlayerMgr::OnMsgPetSavvyUpack(Msg *m_msg)
{
	if (m_msg != NULL)
	{
		MsgPetSavvyUpAck * _msg = (MsgPetSavvyUpAck*)m_msg;
		switch (_msg->result)
		{
		case ER_Success:
			if (s_CUI_ID_FRAME_SuAnimalUp.IsVisable())
			{
				s_CUI_ID_FRAME_SuAnimalUp.RefreshProperty();
			}
			if (s_CUI_ID_FRAME_SuAnimalMaterialUp.IsVisable())
			{
				s_CUI_ID_FRAME_SuAnimalMaterialUp.Refresh_Help(false);
			}
			if (s_CUI_ID_FRAME_SuAnimalStudy.IsVisable())
			{
				s_CUI_ID_FRAME_SuAnimalStudy.Refresh(true);
			}
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSavvyUpSuccess) );
			break;
		case ER_Failed:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSavvyUp) );
			if (s_CUI_ID_FRAME_SuAnimalUp.IsVisable())
			{
				s_CUI_ID_FRAME_SuAnimalUp.RefreshProperty();
			}
			if (s_CUI_ID_FRAME_SuAnimalMaterialUp.IsVisable())
			{
				s_CUI_ID_FRAME_SuAnimalMaterialUp.Refresh_Help(false);
			}
			break;
		}
	}
}

void CPlayerMgr::OnMsgPetUpdateChar(Msg *m_msg)
{
	if (m_msg !=NULL)
	{
		MsgUpdatePetChar *msg = (MsgUpdatePetChar*)m_msg;
		if (msg != NULL)
		{
			CPlayer *m_player = theHeroGame.GetPlayerMgr()->FindByID(msg->header.stID );
			if (m_player != NULL)
			{
				if (msg->petLevel > m_player->GetLevel() &&  GetMe()->GetID() == m_player->GetMasterID()) //接收到升级消息
				{
					PlayEffect( "Common\\LevelUp.ini", m_player);
					char temp[64];
					memset(temp,0,sizeof(temp));
					MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetLevelUp),m_player->GetName(),msg->petLevel);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Others_Success, temp);
				}
				std::string strTitle(msg->szTitleName);
				m_player->SetHPInfo(msg->hp,msg->hpMax);
				m_player->SetLevel(msg->petLevel);
				m_player->SetTitle(strTitle);
				s_CUI_Group.Refeash();
				s_CUI_ID_FRAME_Group_Me.Refeash();
			}
		}
	}
	
}

void CPlayerMgr::OnMsgPetLearnSkill(Msg *pMsg)
{
	if (pMsg != NULL)
	{
		MsgPetLearnSkill *m_Msg = (MsgPetLearnSkill*)pMsg;
		if (m_Msg != NULL )
		{
			SPetItem &m_pet = thePlayerRole.GetPetByIndex(m_Msg->index);
			if (m_pet.baseInfo.petId != InvalidLogicNumber)
			{
				char temp[64];
				memset(temp,0,sizeof(temp));
				ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( m_Msg->skillId, m_Msg->skillLevel );
				if (pSkill !=NULL && m_Msg->source == MsgPetLearnSkill::ESource_Realize)
				{
					MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetSavvyLevelUp),m_pet.baseInfo.szName,pSkill->GetSkillName());
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Others_Success, temp);
				}
				if (pSkill != NULL && m_Msg->source == MsgPetLearnSkill::ESource_Item)
				{
					if (m_Msg->replaceSkillId == 0)
					{
						MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetBookLearnSkill),m_pet.baseInfo.szName,pSkill->GetSkillName());
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Others_Success, temp);
						CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,temp);
					}
					else 
					{
						ItemDefine::SItemSkill *pReplaceSkill = GettheItemDetail().GetSkillByID( m_Msg->replaceSkillId, m_Msg->replaceSkillLevel );
						if (pReplaceSkill != NULL)
						{
							if ((pSkill->groupId == pReplaceSkill->groupId) && (pSkill->groupLevel > pReplaceSkill->groupLevel)) //是同一组技能的高级技能替换低级技能
							{
								MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetLearnAdvanceSkillOnBase),m_pet.baseInfo.szName,pReplaceSkill->GetSkillName(),pSkill->GetSkillName());	
							}
							else
							{
								MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetReplaceSkill),m_pet.baseInfo.szName,pSkill->GetSkillName(),pReplaceSkill->GetSkillName());
							}
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Others_Success, temp);
							CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,temp);//正中显示
						}
					}
				}
				if (s_CUI_ID_FRAME_SuAnimalStudy.IsVisable())
				{
					s_CUI_ID_FRAME_SuAnimalStudy.Refresh_Help(false);
					s_CUI_ID_FRAME_SuAnimalStudy.RefreshMountSkill(m_pet);
				}
			}
		}
	}
}

void CPlayerMgr::OnMsgLookOtherPet(Msg *pMsg)
{
	if (pMsg != NULL)
	{
		MsgViewActivePetAck *m_msg = (MsgViewActivePetAck*)pMsg;
		if (m_msg != NULL)
		{
			s_CUI_ID_FRAME_SuAnimalMenu.SetLookOtherPet(false);
			s_CUI_ID_FRAME_SeeSuAnimal.SetVisable(true);
			s_CUI_ID_FRAME_SeeSuAnimal.SetPetItem(m_msg->pet);
		}
	}
}
void CPlayerMgr::OnMsgPetDead(Msg *pMsg)
{
	if (pMsg != NULL)
	{
		MsgPetRegenerate *m_msg = (MsgPetRegenerate*)pMsg;
		if (m_msg != NULL)
		{
			//if (s_CUI_ID_FRAME_SuAnimal.GetCurrentMountIndex() == m_msg->index)
			s_CUI_ID_FRAME_SuAnimal.SetPetDeadTime(m_msg->index,m_msg->regenerateTime);
		}
	}

}

bool CPlayerMgr::GetZByXY(float fCurrentZ,float x,float y,float &fTargetZ)
{
	Vector vPos(x,y,fCurrentZ);
	Vector vDir(0,0,-1);
	BspTree::SIntersect* pIntersect = m_DynamicFloorBsp.GetNearestIntersectCmpZ( vPos, vDir, TRUE,fCurrentZ );
	if(pIntersect)
	{
		fTargetZ = pIntersect->pos.z;
		return true;
	}

	return false;
}

bool CPlayerMgr::InitCamera(int nModelID)
{
	if(nModelID <= 0)
		return false;

	if(!m_pCameraAnim)
		m_pCameraAnim = MeNew MexAnimCtrl;

	if(m_nCameraModelID == nModelID)
		return false;

	m_nCameraModelID = nModelID;

	bool ret = m_pCameraAnim->ChangeModel(nModelID,FALSE,NULL);
	return true;
}

void CPlayerMgr::PlayTaskAnim(const char* pszAnim,float x,float y,float z,float fDir)
{
	if(!m_pCameraAnim)
		return;

	if(!pszAnim)
		return;

	MexCfg* pCfg = m_pCameraAnim->GetMexCfg();
	if(!pCfg)
		return;

	if(!pCfg->GetSequence(pszAnim))
		return;

	m_pCameraAnim->PlayAnimByName(pszAnim,0,FALSE);
	m_pCameraAnim->SetPosition(x,y,z); //设置位置

	//设置角度
	float fDirX = 0.0f, fDirY = 0.0f;
	if( fDir < 0 || fDir > 360 )
	    fDir = 0; 

	fDir = fDir/180*D3DX_PI;
	float fxtoy = tan(fDir);
	float fPosXOff = 0;
	float fPosYOff = 0;

	if( fxtoy == 0 )
	{
		fPosXOff = 1;
	}
	else
	{
		fPosXOff = sqrtf(1/(1+fxtoy*fxtoy));
		fPosYOff = fabs(fxtoy*fPosXOff);
	}
	if( ( fDir >= 0 && fDir <= D3DX_PI/2 ) || ( fDir >= -D3DX_PI*2 && fDir <= -D3DX_PI*3/2 ) )
	{ // 第一象限
		fDirX = fPosXOff;
		fDirY = fPosYOff;
	}
	else if( ( fDir >= D3DX_PI/2 && fDir <= D3DX_PI ) || ( fDir >= -D3DX_PI*3/2 && fDir <= -D3DX_PI ) )
	{ // 第二象限
		fDirX = -fPosXOff;
		fDirY = fPosYOff;
	}
	else if( ( fDir >= D3DX_PI && fDir <= D3DX_PI*3/2 ) || ( fDir >= -D3DX_PI && fDir <= -D3DX_PI/2 ) )
	{ // 第三象限
		fDirX = -fPosXOff;
		fDirY = -fPosYOff;
	}
	else if( ( fDir >= D3DX_PI*3/2 && fDir <= D3DX_PI*2 ) || ( fDir >= -D3DX_PI/2 && fDir <= 0 ) )
	{ // 第四象限
		fDirX = fPosXOff;
		fDirY = -fPosYOff;
	}


	fDir = atan2f( fDirX, fDirY );
	fDir = fmodf( fDir, D3DX_PI*2 );
	if( fDir < 0 )
		fDir += D3DX_PI*2;

	m_pCameraAnim->SetRotationZ(fDir + D3DX_PI/2);
}

void CPlayerMgr::ProcessCamera()
{
	if(!IsTracking())
		return;

	if(!m_pCameraAnim)
		return;

	if(!m_pCameraAnim->GetMex())
		return;

	BOOL bUpdateCamera = FALSE;
	BOOL bUpdateTarget = FALSE;
	Vector vNewCameraPos = Vector(0,0,0);
	Vector vNewTargetPos = Vector(0,0,0);
	m_pCameraAnim->UpdateByParam(HQ_TimeGetTime());

	if(!m_pCameraAnim->GetMex())
		return;

	int nCameraId = m_pCameraAnim->GetMex()->GetSkeleton()->FindBone("SelectCamera01");
	int nTargetEye = m_pCameraAnim->GetMex()->GetSkeleton()->FindBone("SelectCamera01.Target");

	BOOL bGetDataSelect = FALSE,bGetDataTarget = FALSE;
	vNewCameraPos = m_pCameraAnim->GetBoneWorldPos(nCameraId,  &bGetDataSelect);
	vNewTargetPos = m_pCameraAnim->GetBoneWorldPos(nTargetEye, &bGetDataTarget);

	GetMe3dConfig()->GetCamera()->SetViewParams(
		*(D3DXVECTOR3*)&vNewCameraPos,
		*(D3DXVECTOR3*)&vNewTargetPos,
		D3DXVECTOR3(0 , 0, 1));

	getwsCamera()->GetMeCamera()->SetViewParams(*(D3DXVECTOR3*)&vNewCameraPos,*(D3DXVECTOR3*)&vNewTargetPos,
		D3DXVECTOR3(0,0,1));
}

void CPlayerMgr::DestroyCamera()
{
	if(!m_pCameraAnim)
		return;

	m_pCameraAnim->Destroy();
	delete m_pCameraAnim;
	m_pCameraAnim = NULL;

	m_bPlayTrack = false;

	m_nCameraModelID = -1;
}

///////////san guo add-----------------------------------
void CPlayerMgr::OnMsgG2CReqBianShen(Msg* pMsg)
{
	//hero id struct
	if (!pMsg)
	{
		return;
	}
	MsgG2CReqBianShen* pBianShen = (MsgG2CReqBianShen*)pMsg;
	if (!pBianShen)
	{
		return;
	}

	CPlayer *player = FindByID(pBianShen->header.stID);
	if (player == NULL)
	{
		return;
	}

	CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(pBianShen->hero_id);
	if (itemHero == NULL)
	{
		return;
	}

	if (player == GetMe())
	{
		// 变身失敗,根据失败的原因进行处理
		if (pBianShen->result == MsgG2CReqBianShen::eResult_fail)
		{
			CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_UseItem_Error,
				theXmlString.GetString(eText_ZhuJiangFail) );
			return;
		}

		if (pBianShen->result == MsgG2CReqBianShen::eResult_NoHero)
		{
			CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_UseItem_Error,
				theXmlString.GetString(eText_ZhuJiangNoHero) );
			return;
		}

		if (pBianShen->result == MsgG2CReqBianShen::eResult_NoMataril)
		{
			CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_UseItem_Error,
				theXmlString.GetString(eText_ZhuJiangNoMaterial) );
			return;
		}

		if (pBianShen->result == MsgG2CReqBianShen::eResult_NoMoney)
		{
			CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_UseItem_Error,
				theXmlString.GetString(eText_ZhuJiangNoMoney) );
			return;
		}

		if (pBianShen->result == MsgG2CReqBianShen::eResult_NoLevel)
		{
			CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_UseItem_Error,
				theXmlString.GetString(eText_ZhuJiangNoLevel) );
			return;
		}

		if (pBianShen->result == MsgG2CReqBianShen::eResult_popItemFail)
		{
			CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_UseItem_Error,
				theXmlString.GetString(eText_ZhuJiangPopErro) );
			return;
		}

		if (pBianShen->result == MsgG2CReqBianShen::eResult_diffSex)
		{
			CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_UseItem_Error,
				theXmlString.GetString(eText_ZhuJiangSexErro) );
			return;
		}

		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Gem_Success,
			theXmlString.GetString(eText_ZhuJiangSuccess) );

		// 扣钱 //这里再扣钱就扣2次了 lrt
		/*DWORD dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
		thePlayerRole.Update(CPlayerRole::TYPE_MONEY, dwMoney - itemHero->need_money);
		s_CUI_ID_FRAME_PACK.RefreshMoney();*/

		// 删除物品
		CItemBag2 *pBag = &thePlayerRole.m_bag;
		SCharItem* charItem = pBag->GetCharItemFromIdx(pBianShen->nItemIndex);
		if (charItem && !charItem->IsBounded())
			charItem->SetBounded(true);
		//pBag->PopItemByID(itemHero->itemd_id, 1, NULL, NULL, "");
		pBag->PopItemByID(itemHero->material_id, itemHero->material_count, NULL, NULL, "");
		s_CUI_ID_FRAME_PACK.RefreshAllPack();
		if (player->GetHeroID()!=INVALID_HERO_ID && player->GetHeroID()!=0)
		{
			thePlayerRole.m_HeroSkillBag.ClearAllSkills();
		}

		thePlayerRole.m_HeroSkillBag.AddSkill(itemHero->hero_skill1,itemHero->skill1_lv);
		thePlayerRole.m_HeroSkillBag.AddSkill(itemHero->hero_skill2,itemHero->skill2_lv);
		thePlayerRole.m_HeroSkillBag.AddSkill(itemHero->hero_skill3,itemHero->skill3_lv);

		s_CUI_ID_FRAME_NewSkillMain.AddSkill( itemHero->hero_skill1,itemHero->skill1_lv );
		s_CUI_ID_FRAME_NewSkillMain.AddSkill( itemHero->hero_skill2,itemHero->skill2_lv );
		s_CUI_ID_FRAME_NewSkillMain.AddSkill( itemHero->hero_skill3,itemHero->skill3_lv );
		//SCharBaseAttr& baseAttr = thePlayerRole.GetCharInfo2().baseinfo.baseProperty.baseAttr;
		//SCharFightAttr& fightAttr = thePlayerRole.GetCharInfo2().baseinfo.baseProperty.fightAttr;
		//for (int j=0;j<EBaseAttr_MaxSize;j++)
		//{
		//	ProcessCharInfo::BaseAttrEffectFightAttr( j, ECustomDataPart_hero, baseAttr.baseAttrValue[j], thePlayerRole.GetProfession(), fightAttr, true ); 
		//}

		thePlayerRole.m_charLastBaseProperty = thePlayerRole.GetCharInfo2().baseinfo.baseProperty;

		//关闭UI
		s_CUI_ID_FRAME_zhujiangbianshen.SetVisable( false );
		s_CUI_ID_FRAME_PACK.SetVisable(false);

		thePlayerRole.m_charinfo.baseinfo.liveinfo.hero_id = pBianShen->hero_id;
	}

	player->SetHeroID(pBianShen->hero_id);
	player->ShapeShift();

	// 播放动作、特效、镜头托管
	CItemHero::ZhujiangExtraInfo *ei = theItemHero.FindZhujiangExtraInfo(player->GetProfession(), player->GetSex());
	if (ei != NULL)
	{
		PlayEffect(ei->Effect.c_str(), player, 1.0);
		player->BeginPlaying(ei->SceneActionID);
	}
}

void CPlayerMgr::OnMsgTellHeroAddAttr(Msg* msg)
{
	MsgTellHeroAddAttr* pHeroAttr = (MsgTellHeroAddAttr*)msg;
	thePlayerRole.SetHeroAddAttr(pHeroAttr->heroAttr);
}

void CPlayerMgr::OnMsgTellTPHJRank(Msg* msg)
{
	MsgTellTPHJRank* pMsgRank = (MsgTellTPHJRank*)msg;
	if (!pMsgRank)
	{
		return;
	}
	thePlayerRole.SetTPHJRank(pMsgRank->rank);
}

void CPlayerMgr::OnMsgTellQuestTime(Msg* msg)
{
	MsgTellQuestTime* pTellTimeMsg = (MsgTellQuestTime*)msg;
	std::vector<CPlayerRole::QuestInfo*>& activeQuest = thePlayerRole.GetActiveQuestInfo();
	for (int i=0; i<QuestLimitTimeMaxCount; ++i)
	{
		SQuest* pQuestInfo = theQuestManager.GetQuest(pTellTimeMsg->questTimes[i].id);
		if (pQuestInfo)
		{
			typedef std::vector<CPlayerRole::QuestInfo*>::iterator ITER_QUESTINFO;
			for (int j=0;j<activeQuest.size();++j)
			{
				if (pTellTimeMsg->questTimes[i].id == activeQuest[j]->nQuestId)
				{
					if (activeQuest[j]->time==0)
					{
						activeQuest[j]->time = pTellTimeMsg->questTimes[i].time;
					}
				}
			}
		}
	}
	s_CUI_ID_FRAME_TimeLimitTask.RefreshTask();
}

void CPlayerMgr::OnMsgChangeToBiaocheAck(Msg* pMsg)
{
	MsgChangeToBiaocheAck *msg = (MsgChangeToBiaocheAck *) pMsg;

	CPlayer *player = FindByID(msg->header.stID);
	if (player == NULL)
		return;

	ItemDefine::SMonster *biaocheMonster = theItemDetailConfig.GetMonsterById(msg->monsterID);
	if (biaocheMonster == NULL)
		return;

	// 先变身, 后设置状态
	player->MorphMonster(msg->monsterID);
	player->SetYabiaoState(true);
	// 镖车的缩放为:角色模型大小乘以怪物的体型修正
	player->SetBiaocheScale(PlayerInfoMgr::Instance()->GetScaleForPlayer(theHeroGame.GetPlayerMgr()->GetMe(), false) * biaocheMonster->fBodySize);

	{
		s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().EndFight();
		if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString(eText_AutoFightEnd) );
	}

	

	// 隐藏实际的镖车
	// 逻辑在PlayerMgr的IsPlayerCanRender函数中
}

void CPlayerMgr::OnMsgRestoreFromBiaocheAck(Msg* pMsg)
{
	MsgRestoreFromBiaocheAck *msg = (MsgRestoreFromBiaocheAck *) pMsg;

	CPlayer *player = FindByID(msg->header.stID);
	if (player == NULL)
		return;
	
	// 先设置状态, 再变身
	player->SetYabiaoState(false);
	player->MorphMonster(-1);
	player->SetBiaocheScale(0.0);
}

void CPlayerMgr::OnMsgTellReliveBuff(Msg* pMsg)
{
	MsgTellReliveBuff* pBuff = (MsgTellReliveBuff*)pMsg;
	CPlayer *player = FindByID(pBuff->header.stID);
	if (player == NULL)
		return;
	CUI_ID_FRAME_ESCDLG::byGetBuff = pBuff->byBuff;
}

void CPlayerMgr::OnMsgReqChangeHero(Msg* pMsg)
{
	MsgShowHeroSuit* pSuit = (MsgShowHeroSuit*)pMsg;
	if (pSuit)
	{
		CPlayer *player = FindByID(pSuit->header.stID);
		if (player == NULL)
			return;
		bool v = false;
		if (pSuit->flag == MsgShowHeroSuit::eHeroSuitFlag::eHeroSuitFlag_show)
		{
			player->SetShowHero(true);
			if (GetMe() == player)
			{
				v = true;
			}
		}
		else
		{
			player->SetShowHero(false);
			if (GetMe() == player)
			{
				v = true;
			}
		}

		for (int i=0; i < eKeyAll_Max; i++)
		{
			SCharItem* pCharItem = &player->GetEquip()[i].item;
			player->SetEquip( i,pCharItem );
		}
		player->ChangeSkeletonAndEquipAllItem( player->HasFightFlag(eFighting) );
		if (GetMe() == player)
		{
			s_CUI_ID_FRAME_BaseProperty.UpdatePlayerAnimCtrl();
			thePlayerRole.m_charinfo.visual.ShowHero(v);
		}
	}
}

void CPlayerMgr::OnMsgInitLevelLimit(Msg* pMsg)
{
	MsgFIRSTLIMITINFO* pinfo = (MsgFIRSTLIMITINFO*)pMsg;
	if (pinfo)
	{
		s_CUI_ID_FRAME_ManualLevelUp.InitLevelLimitData(NULL/*&pinfo->sllinfo*/,pinfo->max_lv);
	}
}

void CPlayerMgr::OnMsgDoneLimit(Msg* pMsg)
{
	MsgGS2CLimitDone* pDone = (MsgGS2CLimitDone*)pMsg;
	if (!pDone)
	{
		return;
	}
	//todo:封印结束
	s_CUI_ID_FRAME_ManualLevelUp.DoneLimit();
}
void CPlayerMgr::OnMsgUnBindEquip(Msg* pMsg)
{
	//接收到回发命令
	MsgUnBindEquipAck* pDone = (MsgUnBindEquipAck*)pMsg;
	if (!pDone)
	{
		return;
	}
	s_CUI_ID_FRAME_JieBang.UnBindEquipSuc(pDone->nEquipGuid);
}

void CPlayerMgr::OnMsgTimeStep(Msg* pMsg)
{
	MsgProcTimeStepAck* pAck = (MsgProcTimeStepAck*)pMsg;
	if (!pAck)
		return;
	
	if (pAck->TimeStep == 0)
		return;

	if (theTimeStringManager.GetSize() == 0)
		s_CUI_ID_FRAME_TimeShow.SetVisable(true);

	uint32 starttime = timeGetTime();
	theTimeStringManager.AddTimeData(pAck->TimeStep, pAck->StringID, starttime);
}
