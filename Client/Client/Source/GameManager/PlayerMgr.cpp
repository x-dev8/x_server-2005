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
D3DXVECTOR3	g_vTheRoleTargetPos; //���ǵ�Ŀ��λ��
D3DXVECTOR3	g_vTheRoleTargetDir; //���ǵ�Ŀ�귽��
D3DXVECTOR3 g_vTheRoleJumpingDir; //���ǵ���Ծ����
D3DXVECTOR3 g_vTheRoleCurDir; //���ǵĵ�ǰ����
D3DXVECTOR3	g_vTheRoleAttackTargetPos; //���ǵĹ���Ŀ��λ��

float g_fTheRoleJumpingRotate = 0.0f;

BOOL	g_bTheRoleAttackLockTarget = FALSE;

BOOL	g_bTheRoleMovingByDir = FALSE; //�����Ƿ��Է����ƶ�
BOOL    g_bLastFrameMovebyDir = FALSE;
BOOL	g_bTheRoleCountermarch = FALSE;	//�����Ƿ��ڵ����ƶ�

DWORD	g_dwTheRoleJumpTime = 0; //���ǵ�����ʱ��
DWORD	g_dwTheRoleJumpingEndTime = 0; //������ص�ʱ��
BOOL	g_bTheRoleJumping = FALSE; //�����Ƿ�����
BOOL	g_bTheRoleJumpingCountermarch = FALSE; //�����Ƿ��������
BOOL	g_bTheRoleFallJumping = FALSE; //��������
D3DXVECTOR3	g_vTheRoleSlipJumpingDir; //�����»���Ծ�ķ���

BOOL	g_bRenderRole = TRUE; //�Ƿ���Ⱦ����

int     g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;	// �Զ�����״̬

BOOL	g_bAutoRunForward = FALSE;

BOOL	g_bKeyboardVK_XIsDown = 0;

extern  short   g_shDeadIngDuration = 1000;     //lyh++ ���������е�ʱ��
short   g_shDeadOverDuration = 2000;    // ���������������������ʱ���ɾ��
BOOL    g_bNextNotIntonate = FALSE;     // �¸�����������˲����
BOOL    g_bAutoPlayInteractionWithTarget = FALSE;   // ����Զ�Ѱ·��Ŀ�긽���󣬷���ӵ��Ҫ��
BOOL	g_bAutoOpenPrivateShop = FALSE; // �ߵ���ǰ���򿪰�̯
DWORD   g_dw25DLButtonDownStartTime = 0;   // 2.5D������ʱ����¼������µ�ʱ��
BOOL    g_b25DRoleMoveFollowMouse = FALSE; // 2.5D����������������ƶ�
BOOL    g_b25DMouseLButtonDownOnTerrain = FALSE;    // 2.5D������
BOOL    g_b25DRoleMoveFollowMouseFocusOnUI = FALSE; // 2.5D��곤���˸�������ƶ�ʱ������ƶ���UI��
BOOL    g_bPackagePickAll = FALSE;      // �Ƿ�ʰȡ������ȫ����Ʒ��ͨ��LAltʰȡ��������

extern		CActionManager		g_ActionManager;

extern float g_fNeedVerifyDistance; // ��Ҫ�����ľ���
extern float g_fTheRoleBBoxHeight;

extern DWORD g_dwLastFrameCostTime;
extern DWORD g_dwLastFrameBeginTime;

extern BOOL g_bMouseMoveMode; //����ƶ�ģʽ

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
    // �ж������Ч����
    if( nPlayerID > -1 )
    {
        CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(nPlayerID);
        if( pPlayer )
        {
            if( pPlayer == theHeroGame.GetPlayerMgr()->GetMe() )    // �Լ�
            {
                bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfEffect );
                if( !bShow )
                    return FALSE;
            }
            else if( pPlayer->MyTeamMember )    // ����
            {
                bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerEffect );
                if( !bShow )
                    return FALSE;
            }
            else if( pPlayer->IsPlayer() )      // �������
            {
                bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerEffect );
                if( !bShow )
                    return FALSE;
            }
            else if( pPlayer->IsMonster() && pPlayer->GetMasterID() > -1 )     // �жϳ���
            {
                CPlayer *pMaster = theHeroGame.GetPlayerMgr()->FindByID(pPlayer->GetMasterID());
                if( pMaster )
                {
                    if( pMaster == theHeroGame.GetPlayerMgr()->GetMe() )    // �Լ�
                    {
                        bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfEffect );
                        if( !bShow )
                            return FALSE;
                    }
                    else if( pMaster->MyTeamMember )    // ����
                    {
                        bool bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerEffect );
                        if( !bShow )
                            return FALSE;
                    }
                    else if( pMaster->IsPlayer() )      // �������
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
    m_bUseSkillBuf = TRUE; // ʹ�ü��������ڹ�����Χ�ڣ��Զ��ܹ�ȥ���˹���Ĭ�ϴ�
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
	//����Ƿ����Լ��Ķ�Ա	
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

	// ���µ���ʱ������
	COnlineReward::Instance().UpdateOnlineReward();

	thePlayerRole.UpdateLockItem();
	
	// ���·���������ʱ��---�б�Ҫ1���Ӿ���һ��ô???
	//CPreventWallow::Instance().UpdatePreventWallow();

	// ����С�Ӽ���
	thePlayerRole.CalcTeamSkillLevel();

	// ���±��鶯��CD
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
            // ��Ʒ��ʱ��ʾʱ������󣬲�ʰȡ��Ч
            if( pPlayer->m_bCanPick && pPlayer->IsItemDropDelayOver() && pPlayer->m_nCollectionEffectID == -1)
            {
                pPlayer->m_nCollectionEffectID = PlayEffect("common\\QuestItem.ini",pPlayer);
            }
        }

		if( pPlayer->NeedRemove() )                      
		{       
			 /*&& (pPlayer->IsDeadOver() || pPlayer->GetCharType() != Object_MonsterpPlayer->GetCharType() == Object_Player)*/
			if( time - pPlayer->GetStartRemoveTime() > 1000 || pPlayer->GetCharType() == Object_Player) //����playerde
			{
				if( !GetMexResMgr()->TryLock() )
					continue;
				// ���try��ͼ�����������ױ��� [10/29/2010 zhangjiayi]
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

				//��ն������У���Ҫ�Ǵ�������Ϣ
				pPlayer->ExcuteClearActionQueue();
				RemovePlayerFromActiveList( pPlayer->GetID() );	 //����

				if( pPlayer->Release() ) //û������ ��ֱ������ڴ�
				{
					//pPlayer->Destroy();
					DestroyPlayer( pPlayer );
					delete pPlayer;
					//g_nPlayerCount--;
				}
				else
				{
					//�����ݴ����
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
			// ���´���̬��ײ��NPC�б�
			NpcInfo::Npc* pNpc = theNpcInfo.GetDynamicCollNpcByName(pPlayer->GetName(), iMapId);
			if( !pNpc )
				continue;

			if( pNpc->isDynamicCollision )
			*/
			// ����NPC
			if (pPlayer->GetNpcType() == eNT_Elevator)
				m_vecDynamicCollison.push_back(pPlayer);
		}
		else if( pPlayer->IsMonster() && pPlayer->GetMonsterType() == eMT_Collision )
		{
			// �赲��
			m_vecDynamicCollison.push_back(pPlayer);
		}
	}
	// ������̬��ײBspTree
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

    // �������Ŀ��
    if( GetLockPlayerID() >= 0 )
    {
        CPlayer* pPlayer = FindByID(GetLockPlayerID());
        if( pPlayer && pPlayer->GetDistanceToRole() > PLAYER_LOCK_DIST_MAX )
        {
            cancelBehavior();
            SetLockPlayerID(-1);
        }
    }

    // ������Ŀ��
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

	// ���ѡ���player
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

            // �Ȼ�ȡ�����������ײ�еľ��룬�趨pick����Ϊ1000��
            TPickResult castResult;
            float fNearestColiDist = 10000; // ������ƽ�������ʵ�ʾ���100��
			bool bIsAlphaModel = false;
            Vector vectorDir = *(Vector*)&m_vDir;
			//LYH�޸�����ѡĿ�����͸������ǽ
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
			CPlayer* arraySelPlayer[200];	// ���λ�ø��������array���ڿ�������ϣ��200�㹻��
			int nArrayPlayerCount = 0;
			for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
			{
				CPlayer* pPlayer = it->second;
                if( !pPlayer )
                    continue;

				if( pPlayer->IsItem() && !pPlayer->IsItemDropDelayOver() )
					continue;

				// NPC����
				if( pPlayer->IsNpc() && pPlayer->IsHide() )
					continue;

                // ���ɼ����ٻ���
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

            // ���������ҲҪ��ѡ��
            if( !m_vectorDeathPlayer.empty() )
            {
                std::vector< CPlayer* >::iterator iter;
                for( iter = m_vectorDeathPlayer.begin(); iter != m_vectorDeathPlayer.end(); ++iter )
                {
                    CPlayer* pPlayer = (CPlayer*)*iter;
                    if( !pPlayer )
                        continue;

                    // ����������ֻȡ��Ҽ������ ����ֻֻ������ҵ� ���������е����
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

            BOOL bPickNPC = FALSE;  // ����ѡNPC��bPickNPC��¼����pick��ѡ���б����Ƿ���NPC
            BOOL bPickItem = FALSE; // ���item����վһ������pick item
			int nSelPlayerCount = vectorSelPlayer.size();
			if( nSelPlayerCount > 0 )
			{
                Vector vPickFrom = *(Vector*)&m_vFrom;
				std::vector<CPlayer*>::iterator iter;
				for( iter = vectorSelPlayer.begin(); iter != vectorSelPlayer.end(); ++iter )
				{
					if( nArrayPlayerCount >= 200 )	// ����200�Ͳ��������ڣ�һ�㲻�ᳬ��200�ɡ�
						break;

					CPlayer* pPlayer = *iter;
					if( pPlayer->IsItem() && !pPlayer->IsItemDropDelayOver() )
						continue;
					guard(test5.2);
					if( pPlayer->NeedRemove() )
						continue;

					if( pPlayer->GetMonsterType() == eMT_Building )
						continue;

					// ����ұ����ڳ�ʱ�����ų���ѡȡ�б�֮��
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

					//�������ң���������Ѿ�������������bbox����ʾ
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
				// �ɽ���Զ��������
				if( nArrayPlayerCount > 1 )
					qsort(arraySelPlayer, nArrayPlayerCount, sizeof(CPlayer*), ComparePlayerDist2);
				CPlayer* pMouseTargetPlayer = NULL;
                CPlayer* pMouseTargetPlayerNearest = NULL;   // ����������������������pick NPC����������NPC����ȡ���player
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
                        // �ҵ�һ��NPC
                        float fSelectPLayerToCameraDist = sqrtf(arraySelPlayer[index]->GetDistanceToPickRay());
                        if( arraySelPlayer[index]->IsNpc() )
                        {
                            // NPC��������볬����player���������3.5�ף�������ѭ��
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
                            // Item��������볬����player���������1.5�ף�������ѭ��
                            if( pMouseTargetPlayerNearest 
                                && fSelectPLayerToCameraDist - fNearestPlayerToCameraDist > fItemMaxDist )
                                break;
                            else
                            {
                                pMouseTargetPlayer = arraySelPlayer[index];
                                break;
                            }
                        }
                        // ��NPC���򱣴�������������
                        else if( !pMouseTargetPlayerNearest )
                        {
                            pMouseTargetPlayerNearest = arraySelPlayer[index];
                            fNearestPlayerToCameraDist = sqrtf(pMouseTargetPlayerNearest->GetDistanceToPickRay());
                        }
                        // �����ǰ��ѯ������������ﳬ��3.5�ף�������NPC,ֱ������ѭ��
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

					if (pMouseTargetPlayer->IsEffect()) //��Ч��
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

	ResetDestroyAnimNum();	// ÿ֡��CheckDestroyAnimLowMemoryǰ����
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

		pPlayer->UpdateBaseData( time);	// ��������alpha

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
            // ����Ⱦ��Χ������
			bDistanceRender = TRUE;
			float fAlpha = pPlayer->GetCurRenderAlpha();
			if( fAlpha < 1 && pPlayer->GetMonsterType() != eMT_IllusionMonster )
			{
				pPlayer->SetFinalRenderAlpha( 1 );
				pPlayer->SetDefaultFinalRenderAlpha( 1 );

                // ��ʼ��NPC Idle Action
                if( pPlayer->IsNpc() )
                    pPlayer->InitNpcAction(time);
			}
		}
		else
		{
            // ����Ⱦ��Χ������
			float fAlpha = pPlayer->GetCurRenderAlpha();
			if( fAlpha > 0 && pPlayer->GetMonsterType() != eMT_IllusionMonster )
			{
				pPlayer->SetFinalRenderAlpha( 0 );
				pPlayer->SetDefaultFinalRenderAlpha( 0 );
				bDistanceRender = TRUE;

                // ����NPC Idle Action
                if( pPlayer->IsNpc() )
                    pPlayer->ExitNpcAction();

				if(pPlayer->IsMonster())
					pPlayer->EndMonsterAction();
			}
		}

		// ����NPC Idle Action
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

			// ��Ҫ���£���Ȼͼ����Ⱦ�����档 [8/4/2008 whu]
			pPlayer->Update( time);
		}
		else
		{
			pPlayer->ResetNeedRender();
        }

		// ��Ҳ�����Ұ�ڣ��������ǳ���30�ף��������һ����Ⱦ����5�룬���ͷŶ�������
		if( !pPlayer->IsNeedRender() && pPlayer->IsPlayer() )
		{
			CheckDestroyAnimLowMemory(pPlayer);
		}

		if( pPlayer->IsDeadOver() )
		{
			vctDeadOverPlayers.push_back(pPlayer->GetID());
		}
	}

	//lyh����++  ������������ �������Լ����߼�
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
				//��ն������У���Ҫ�Ǵ�������Ϣ
				pPlayer->ExcuteClearActionQueue();
				RemovePlayerFromActiveList( pPlayer->GetID() );
				if( pPlayer->Release() )
				{
					//ɾ����ص�Ч��
					DestroyPlayer( pPlayer );
					delete pPlayer;
				}
				else
				{
					//�����ݴ����
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

		//���½�ɫ��Alpha
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

		// ��Ҳ�����Ұ�ڣ��������ǳ���30�ף��������һ����Ⱦ����5�룬���ͷŶ�������
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
				//����ɾ����
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
							// ������Ϊ������������,��������ʱ������һ�����ã���ͬ [11/10/2010 zhangjiayi]
							//lyhȥ������--
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

	//��¼�ɹ��Ų�lag
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

// ���ݿͻ��˵�Id����Player
CPlayer* CPlayerMgr::FindByClientID( int nID )
{
	guardfunc;
	return NULL;
	unguard;
}

// ������ͬID
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


// ���ݷ�������Id����Player
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

// �������ݿ��еĽ�ɫID����Player
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


// ���ݷ���˵�Id�����������в���Player
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

// ���ݿͻ��˵�Id�����������в���Player
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
	// ����1�ó��Ľ��ۣ����found��Ӧ��Ϊ����
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
	//��������KeepList�ģ��϶���������������ɾ��
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
	// �����Ǽ����
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

	// �������Ҫclear
	m_mapPlayers.clear();
	CleaNpcInfos();

	// ���������������ҲҪ���
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
	
	// ������ڳ�, ��������˳�ǰ֪ͨ����Master
	if (pPlayer->IsMonster() && pPlayer->GetSubMonsterType() == Object_MonsterProtected && pPlayer->IsCanRide())
	{
		CPlayer *master = FindByID(pPlayer->GetMasterID());
		if (master != NULL && master == m_pMe)
		{
			// ���ڳ��ָ�����
			MsgRestoreFromBiaocheReq msg;
			GettheNetworkInput().SendMsg(&msg);

			// �����ڳ����ƽ���			
			s_CUI_ID_FRAME_OnBiaoChe.SetVisable(false);
		}
	}	

	// ����ǵ�ǰ�������ȡ������
	if( GetLockPlayerID() > -1 && GetLockPlayerID() == stId )
	{
		SetLockPlayerID(-1);
		s_CUI_ID_FRAME_Target.SetPlayer(-1);
	}
	//�ӻ�������Ƴ�

	if( pPlayer->GetMonsterType() == eMT_IllusionMonster )
	{
		PlayEffect( "Common\\SummonEffect.ini", pPlayer );
		pPlayer->SetFinalRenderAlpha( 0 );
		pPlayer->SetDefaultFinalRenderAlpha( 0 );
        // ���ٻ���alphaΪ0����Remove
	}

	else if( pPlayer->IsItem() )
	{
        // �򿪰�����Player ID��ͬ���رհ�������
        if( s_CUI_ID_FRAME_PickUp.IsVisable() && s_CUI_ID_FRAME_PickUp.IsSamePackage(stId) )
        {
            s_CUI_ID_FRAME_PickUp.SetVisable(false);
        }

		if(pPlayer && pPlayer->IsItem())
		{
			s_CUI_ID_FRAME_AutoAttackSet.ReMoveRecordItem(pPlayer->GetID());
		}

		//��ն������У���Ҫ�Ǵ�������Ϣ
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
			//�����ݴ����
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

//	�����ʳ�
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
			if( usType == 0 ) //����
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
				if( pSkill->bShowIntonateBar )      // ��Ҫ��ʾ������
				{
					s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), stSingTime/*pSkill->ustPrepTime*/,
						true, 1, true, true, pSkill->GetSkillName(), false, false, 0, FALSE );
				}				
			}
			else //ͨ��
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

	// �����޸� [11/17/2010 zhangjiayi]
	//lyhȥ������
	if( pSrc )
		pSrc->AddRef();
	if( pDst )
		pDst->AddRef();

	Intonate.pSrc = pSrc;	//������
	Intonate.pDst = pDst;	//����Ŀ��
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

	//��ȡ�����ߺͱ������ߵ�ָ��
	CPlayer *pSrc = FindByID( stSrc );
	CPlayer *pDst = FindByID( stDst );

	if ( NULL == pDst )
	{
		// ���ǿ��ܵģ�����һ��������Ұ��player
		return;
	}

	/////////Server��״̬ʩ��Դ�Ĵ��������⣬��������������Դ�Ĵ���

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

	//���Ŀ���������л�����������
	if (_HAS_FLAG(dwState, eFIGHT_BEKILLED))
	{
		pDst->SetHPInfo_HP(0);
		pDst->WillDie();
		pDst->OnClearAllBodyStatusByDead();
		//pDst->OnClearAllBodyStatus();
		pDst->AddDeathTask();
		//lyhȥ������
		if( !pDst->IsDead() )
			pDst->AddRef();
		pDst->SetCharDead( TRUE );
		pDst->UpdateBaseData(HQ_TimeGetTime());
		pDst->SwitchDieAnim();
		//���������ȴ���������ͷ�
		//pDst->AddRef();

        if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight()
            &&(pDst&&pDst->IsMonster())
            &&((pSrc&&pSrc == GetMe())
            ||(pSrc&&pSrc->GetMasterID() > -1 && theHeroGame.GetPlayerMgr()->FindByID(pSrc->GetMasterID()) == GetMe())))
        {//�����Զ��һ���
            s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().EnterWait(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().s_dwElapseTime);
            s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().ResetSkillSeq();  //
        }

		// added, jiayi, [2009/12/29]
		// �㱻xɱ������ʾ
        if( pSrc && pDst )
        {
		    if( pDst==GetMe() )
		    {  
		       // �㱻��ɱ��	
		       char szContent[256] = {0};			
		       MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pSrc->GetName());			
			   s_CUI_ID_FRAME_ESCDLG.SetAttackerName( pSrc->GetName() );
		       CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_BeKilled_Info, szContent );
		    }
            else if( pDst->IsPlayer() )// �ж��Ƿ���ҹ�����ң�������ʾ��ɱ��Ϣ
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
//	��������
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
		OutputDebugString( "OnSeeAttackĿ�겻����" );
		return;
	}
	//
	if (pDst == GetMe())
	{
		thePlayerRole.SetPlayerHP(nTagHp);
		thePlayerRole.SetPlayerMP(kSeeAttackParam.nTagMp);
	}
	//���������ߵ�λ��	
	if( _HAS_FLAG( dwState, eFIGHT_BEKILLED ) )
	{
		pDst->WillDie();
        if ( pAttacker )
        { 
            if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight()&&(pDst&&pDst->IsMonster())
                &&(pAttacker == GetMe()||(pAttacker->GetMasterID() > -1 && theHeroGame.GetPlayerMgr()->FindByID(pAttacker->GetMasterID()) == GetMe())))
            {//�����Զ��һ���
                s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().EnterWait(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().s_dwElapseTime);
                s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().ResetSkillSeq();  //
            }

            char szContent[256] = {0};
            if ( pDst==GetMe() )
            { // �㱻��ɱ��
                if ( pAttacker->GetMasterID() != -1)
                { // ������ٻ���
                    CPlayer* pMasterPlayer = FindByID( pAttacker->GetMasterID() );
                    if ( pMasterPlayer )
                        MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pMasterPlayer->GetName());
                    else // ������
                        MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pAttacker->GetName());
                }
                else
                { // ��������ٻ���
                    MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pAttacker->GetName());
                }
				s_CUI_ID_FRAME_ESCDLG.SetAttackerName( pAttacker->GetName() );
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_BeKilled_Info, szContent );
            }
        }
	}

    // �����߱�����ɱ��
	if( _HAS_FLAG( dwState, eFIGHT_SELFBEKILLED ) )
	{
        if( pAttacker )
		    pAttacker->WillDie();
        if ( pDst )
        { 
            char szContent[256] = {0};
            if ( pAttacker==GetMe() )
            { // �㱻��ɱ��
                if ( pDst->GetMasterID() != -1)
                { // ������ٻ���
                    CPlayer* pMasterPlayer = FindByID( pDst->GetMasterID() );
                    if ( pMasterPlayer )
                        MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pMasterPlayer->GetName());
                    else // ������
                        MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pDst->GetName());
                }
                else
                { // ��������ٻ���
                    MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eClient_AttackDieInfo_1), pDst->GetName());
                }
				s_CUI_ID_FRAME_ESCDLG.SetAttackerName( pAttacker->GetName() );
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_BeKilled_Info, szContent );
            }
        }
	}


	//���ӹ����ߣ�ʹ��һ�����������Ķ���
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

	//˭������Ұ
	if( m_pMe && pMsg->header.stID == m_pMe->GetID() )
	{
		assert( false );
		char temp[1024] = {0};
        MeSprintf_s(temp,1024,"SawOneItem ����ID��Me ID��ͬ %d!",pMsg->header.stID);
        LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
        return;
	}
    // �ж��Ƿ���ͬ������̬����ͼID
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
			pPlayer->SetBodySize( 1.0f );//�ݶ�Ĭ��Ϊ1.0f

            // �жϰ����ܷ�ʰȡ������ʰȡ��Ч
			if( GetMe() /*&&  ( NorPackageItemID == pItemEnter->ustItemId || MidPackageItemID == pItemEnter->ustItemId || AdvPackageItemID == pItemEnter->ustItemId )*/ )
            {
                //pPlayer->SetName("");
                BOOL bCanAccess = FALSE;
				if( pItemEnter->nCount == 0 )	// �������˿ɼ�
				{
					// û����ʱ��ʾ
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
							// û����ʱ��ʾ
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

		//��Ʒ����ָ��
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

    // ͳ�Ƽ�Ӱ�Ӹ���
    BOOL bCombineRenderShadowDecal = FALSE;
    int iShadowCount = 0;
    for( int i = m_nPlayerQueueCount - 1; i >= 0 ; --i )
    {
        // ������Ʒ�Ͳɼ���Ʒ����Ҫ����Ӱ��
        if( m_PlayerDistQueue[i].pPlayer
            && !m_PlayerDistQueue[i].pPlayer->IsItem()
            && !(m_PlayerDistQueue[i].pPlayer->IsMonster() && (m_PlayerDistQueue[i].pPlayer->IsCollection(false) ) ) )
        {
            iShadowCount++;
        }
		// ����ڿ��꣬���������������
		if( m_PlayerDistQueue[i].pPlayer &&
			m_PlayerDistQueue[i].pPlayer->IsOpenPrivateShop() )
		{
			m_PlayerDistQueue[i].pPlayer->UpdateDistanceToPickRay( m_vFrom.x, m_vFrom.y );
		}
    }
	
    
//    if( GetShaderMgr()->GetShadowType() == eShadow_Fake ||
//		!SystemSetting::Instance()->IsAdvance() )
    {
        // �ɼ������������30��ϲ���Ⱦ��Ӱ��
        if( m_nPlayerQueueCount >= 30 && iShadowCount >= 30 )
        {
            bCombineRenderShadowDecal = TRUE;
            ((CWSRender*)SwGlobal::GetRender())->StartCombineShadowDecal();
        }
        // �ϲ�Ӱ������
        for(int i=0; i<m_nPlayerQueueCount; i++)
        {
            // ������Ʒ�Ͳɼ���Ʒ����Ҫ����Ӱ��
            if( m_PlayerDistQueue[i].pPlayer 
                && !m_PlayerDistQueue[i].pPlayer->IsItem()
                && !(m_PlayerDistQueue[i].pPlayer->IsMonster() && (m_PlayerDistQueue[i].pPlayer->IsCollection(false) ) ) )
            {
                m_PlayerDistQueue[i].pPlayer->RenderShadowDecal(bCombineRenderShadowDecal);
            }
        }
        // �ϲ���Ⱦ
        if( bCombineRenderShadowDecal )
        {
            ((CWSRender*)SwGlobal::GetRender())->EndCombineShadowDecal();
            ((CWSRender*)SwGlobal::GetRender())->RenderCombineShadowDecal();
        }
    }

	// �������ȾӰ�Ӻ���
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
			m_PlayerDistQueue[i].pPlayer->RenderRankTitle(); //���������޹أ���Ϊ�˼���ѭ��
			m_PlayerDistQueue[i].pPlayer->RenderCountryTitle(); //���Ҳ�޹أ���Ϊ�˼���ѭ��
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

int g_iLoadModelPerFrame = 1;	// ÿ֡������Ҹ���

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

	// ���ͳ������
	nRenderPlayerCount	= 0;
	nRenderVertexCount	= 0;
	nRenderFaceCount	= 0;

	{
		// �����Ⱦ����
		m_nPlayerQueueCount = 0;
		memset(m_PlayerDistQueue, 0, PLAYER_RENDER_QUEUE_MAX*sizeof(PlayerRenderLimitData));

		for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); ++it )
		{
			CPlayer* pPlayer = it->second;

			if( !pPlayer )
				continue;

            // ����ʰȡ����������ʾ
            if( pPlayer->IsItem() )
            {
                if( !pPlayer->m_bCanPick || !pPlayer->IsItemDropDelayOver() )
                    continue;
            }
            // ���ɼ����ٻ���
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
				// ������Ⱦ����
				m_PlayerDistQueue[m_nPlayerQueueCount++].pPlayer = pPlayer;
			}
		}
		for (int i=0; i<(int)m_vectorDeathPlayer.size(); i++)
		{
			CPlayer* pPlayer = m_vectorDeathPlayer[i];
			if( !pPlayer )
				continue;

            // ����ʰȡ����������ʾ
            if( pPlayer->IsItem() && !pPlayer->m_bCanPick )
                continue;

            // ���ɼ����ٻ���
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
				// ������Ⱦ����
				m_PlayerDistQueue[m_nPlayerQueueCount++].pPlayer = pPlayer;
			}
		}

		//��Ⱦ���
		int nVertexCount = 0;
		int nFaceCount = 0;

		int iLoadModel = g_iLoadModelPerFrame;	// ÿֻ֡����3�����
		// ������������ڴ�С��50M���򲻼������
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
			// Զ�����򣬰�ͬ���������Ƽ����ȼ��ߵͽ�����Ⱦ
			qsort(m_PlayerDistQueue, m_nPlayerQueueCount, sizeof(PlayerRenderLimitData), ComparePlayerDist);
			int nRenderedCount = 0;	// ����Ⱦ����

            // ���Ŀ�������ʾ(����: ��ұ����ڳ�״̬ʱ��ѡ���ڳ�Ҳ����ʾ)
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
								// ������ڳ�״̬������Ⱦ
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
					// ���ģ��δ���أ������ģ��
					if( !pTargetPlayer->GetAnim() )
					{
						// ����ģ��
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
						// ������ϵ�װ������ɲɼ���Ʒ������ͳ�������ж���
						if( !pTargetPlayer->IsItem() && !pTargetPlayer->IsCollection(false) )
							nRenderedCount++;

						// ͳ����Ⱦ����
						nRenderPlayerCount++;
						nRenderVertexCount += nVertexCount;
						nRenderFaceCount += nFaceCount;
					}
                }
            }

            // PLAYER_RENDER_DIST_MIN��Χ�ڣ���Ⱦ���ȼ���ߵ�����
			for( int i = 0; i<m_nPlayerQueueCount; i++ )
			{
				CPlayer* pPlayer = m_PlayerDistQueue[i].pPlayer;
				if( !pPlayer || m_PlayerDistQueue[i].bRendered )
					continue;

				if( pPlayer == m_pMe && !g_bRenderRole )
					continue;

				// ��Ⱦ�������PLAYER_RENDER_DIST_MIN������Ⱦ����������������
				if( pPlayer->GetDistanceToRole() > PLAYER_RENDER_DIST_MIN
				 || nRenderedCount >= m_nPlayerRenderLimit )
					break;

                // ������Ⱦ�Լ���NPC�����ѣ����ѣ�������Ʒ���ɼ���Ʒ�����ٻ���
                if( IsPlayerCanRender(pPlayer, TRUE) || IsPlayerCanRenderEX(pPlayer, TRUE))
				{
					m_PlayerDistQueue[i].bRendered = TRUE;
#ifdef NEW_PLAYER_LOAD
					// ���ģ��δ���أ������ģ��
					if( !pPlayer->GetAnim() )
					{
						// ����ģ��
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
						// ������ϵ�װ������ɲɼ���Ʒ������ͳ�������ж���
						if( pPlayer && !pPlayer->IsItem() && !pPlayer->IsCollection(false) )
							nRenderedCount++;

						// ͳ����Ⱦ����
						nRenderPlayerCount++;
						nRenderVertexCount += nVertexCount;
						nRenderFaceCount += nFaceCount;
					}
				}
			}

			// ������Ⱦ�������
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
					// ���ģ��δ���أ������ģ��
					if( !pPlayer->GetAnim() )
					{
						// ����ģ��
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
						// ������ϵ�װ������ɲɼ���Ʒ������ͳ�������ж���
						if( !pPlayer->IsItem() && !pPlayer->IsCollection(false) )
							nRenderedCount++;

						// ͳ����Ⱦ����
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
            // ���Ŀ�������ʾ(����: ��ұ����ڳ�״̬ʱ��ѡ���ڳ�Ҳ����ʾ)
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
								// ������ڳ�״̬������Ⱦ
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
					// ���ģ��δ���أ������ģ��
					if( !pTargetPlayer->GetAnim() )
					{
						// ����ģ��
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

						// ͳ����Ⱦ����
						nRenderPlayerCount++;
						nRenderVertexCount += nVertexCount;
						nRenderFaceCount += nFaceCount;
					}
                }
            }

            // ����������
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
					// ���ģ��δ���أ������ģ��
					if( !pPlayer->GetAnim() )
					{
						// ����ģ��
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

		//��ʾ��ҵ�BBOX
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
//	����������ʹ�ù�������
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
		//�����ѯhp
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
		// �������ʱ�Զ�������ô����һ�Σ��л���idle
		// ����ǳ����Զ���������һ�Σ�ͣ�����һ֡
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

	//��ǰҪʹ�õļ���
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

    // ���ؿ����Ƿ�ʹ��SkillBuf
	if( bUseSkillBuf )
	{
		pTarget = FindByID( m_SkillBufTargetID );
	}
	else
	{
        // ���Ŀ������
		switch( pSkill->ustCastTarget )
		{
		case ItemDefine::casttarget_me:
			pTarget = GetMe();
			break;
		case ItemDefine::casttarget_pos:
			//��겻��ָ��Ŀ��
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
			//����ָ��Ŀ��
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
            // ֻ�ܶԳ���ʩ�ŵļ��ܣ�targetֱ����ɳ���
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
                // ����
				if (pTarget->IsMonster())
				{
                    // �ж��Ƿ��Լ�������ٻ���
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
				// ���Ƕ��ѣ����Ƕ��ѵ����д��������Լ�ʩ��
				if (GetMe() && pTarget->IsPlayer() && pTarget != GetMe() && 
                    (!GetMe()->IsTeamMember(pTarget->GetName()) || (GetMe()->IsDueling() && thePlayerRole.GetDuelTarget() == pTarget->GetID()) ))
				{
					pTarget = GetMe();
				}
			}
			break;
		}
	}

	//Xp���ܲ����ڷ��ܿ�״̬�ͷ�
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

	// ���û��Ŀ�꣬�����Ƕ�һ����λ�õģ���ǿ�и���Ŀ�꣬�߻���Ҫ��
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
//��Ping��Ϣ��������
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
//	��ϵͳ����Ϣ
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
// �������������Ĳ�����
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

	//ping��
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
	
	//�W�[��������|��
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
		return 0;	// �Ƿ�Ҫ����-1��
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

	if (pCoordInfo->uchCountryID != 0 //��������npc
		&&	pCoordInfo->uchCountryID != GetMe()->GetRealCountry()//���Ǳ���npc
		)
	{
		return eNpcTips_None;
	}
	if (pCoordInfo->_nType == eNT_Pub)
		return eNpcTips_HaveQuest;

	std::vector<SQuest*>	vectorQuest;
	std::vector<void*>			vtNpcRelateState;
	// �õ���npc��������
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
		// �����ɫ����״̬��û�з��ִ������¼,��������û����
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
@S-C��ʾ���кͲֿ�
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
	//��ǰҪʹ�õļ���
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( nSkillID, nSkillLevel );

	if( !pSkill )
	{
		return false;
	}

	// �����Ƿ���colddown
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

					// �����жϣ������ϵ���ЧҲҪ�ͷŵ�
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

bool CPlayerMgr::MoveRoleToNPC(const NpcCoordInfo* pInfo )//zhuxincong���ͼ�ϣ����NPC ����Ѱ·��ȥ
{
	CWorldTile* pTile = CURRENTTILE;
	if(NULL == pTile)
		return false;
	int nMapId = pInfo->_mapId;
	if (!pInfo->_bNpc)
	{//��������ֻ��һ��,����ֻ��Ѱ������
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
			if (!(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting()))//zhuxincong 8.2 2012 Ѱ·����û���жϾ��볤��
			{
				// ѹ��״̬��Ѱ·��ֹ����
				if (!theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
					s_CUI_ID_FRAME_Pet.Mount();
			}
		}
	}

	else if (pos->needMount && fDist>=50)
	{
		if (thePlayerRole.GetActivedMount())
		{
			if (!(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting()))//zhuxincong 8.2 2012 Ѱ·����û���жϾ��볤��
			{
				// ѹ��״̬��Ѱ·��ֹ����
				if (!theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
					s_CUI_ID_FRAME_Pet.Mount();
			}
		}
	}

	if ((pTile->GetMapId() ==  nMapId) 	)
	{
		MoveRoleTo(pInfo->_pfMapX,pInfo->_pfMapY,true,false);
		m_pMe->SetActionTarget(0xFFFFF,Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());//���ﲻ�ܴ���-1
	}
	else
	{//���ͼѰ·
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

	// Ԥ���ص�ͼ��ģ������
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
					// ��ȡMonster Index��Monster.slk�
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

	// Ԥ���ص�ͼNPCģ������
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
	//��־Npc�Ի����Ѿ��� ���Ҽ�¼Npc��λ�� ���ڼ�������߿���Npcһ�������ʱ�� �ر�NPc �Ի���
	m_bNeedBeginDilog = true;
}

void CPlayerMgr::SetPlayerRenderPriority( unsigned short pri )
{
    if( pri == 0 )
    {
        // ���Լ������ѣ�NPC���͹���
        m_nPlayerRenderFlag = EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER;
    }
    else
    {
        // ��Ⱦȫ��
        m_nPlayerRenderFlag = EPRF_ALL;
    }
}

void CPlayerMgr::TogglePlayerRenderPriority()
{
    //if( m_nPlayerRenderFlag == EPRF_ALL )
    //{
    //    // ���Լ������ѣ�NPC���͹���
    //    m_nPlayerRenderFlag = EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER;
    //    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect, 0 );
    //    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, 0 );
    //    GameSetting::Instance()->CommitChanges();
    //}
    //else
    //{
    //    // ��Ⱦȫ��
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
	�л�˳�� 
	PSM_ShowAll = 0,		    // ��ʾ�������
	PSM_HideAll      ,			// �����������
	PSM_ShowAmity   ,			// ��ʾ���������
	PSM_ShowAntagonize	   ,	// ��ʾ��������ҡ�
	
	*/
	unsigned int _RenderFlag = s_CUI_ID_FRAME_MiniMap.GetRenderPlayerFlag();
	//IsPlayerTypeRender()
	if(s_CUI_ID_FRAME_MiniMap.HasRenderFlag(EPRF_ALL)) //ȫ��
	{
	//s_CUI_ID_FRAME_Group_Me.SetRenderPlayerFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER,true); //ȫ������
		s_CUI_ID_FRAME_MiniMap.ID_BUTTON_PlayerHideALLOnButtonClick( s_CUI_ID_FRAME_MiniMap.m_pID_BUTTON_PlayerHideALL );
	}
	else if(s_CUI_ID_FRAME_MiniMap.HasRenderFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER)) //ȫ������
	{
		//s_CUI_ID_FRAME_Group_Me.SetRenderPlayerFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER | EPRF_AMITY ,true); //��ʾ���� �Ѻ�
		//s_CUI_ID_FRAME_MiniMap.ID_BUTTON_PlayerShowAmityOnButtonClick( s_CUI_ID_FRAME_MiniMap.m_pID_BUTTON_PlayerShowAmity );
		s_CUI_ID_FRAME_MiniMap.ID_BUTTON_PlayerShowALLOnButtonClick( s_CUI_ID_FRAME_MiniMap.m_pID_BUTTON_PlayerShowALL );
	}
	else
		return; //����ʲô������
	//else if (s_CUI_ID_FRAME_MiniMap.HasRenderFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER | EPRF_AMITY) ) //�Ѻ�
	//{
	//	//s_CUI_ID_FRAME_Group_Me.SetRenderPlayerFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER | EPRF_ANTAGONIZE ,true); //���Ѻ�
	//	s_CUI_ID_FRAME_MiniMap.ID_BUTTON_PlayerShowAntagonizeOnButtonClick( s_CUI_ID_FRAME_MiniMap.m_pID_BUTTON_PlayerShowAntagonize );
	//	
	//}
	//else if(s_CUI_ID_FRAME_MiniMap.HasRenderFlag(EPRF_ME | EPRF_TEAM | EPRF_NPC | EPRF_MONSTER | EPRF_ANTAGONIZE)) //���Ѻ�
	//{
 //          //s_CUI_ID_FRAME_Group_Me.SetRenderPlayerFlag(EPRF_ALL ,true); //ȫ��
	//	s_CUI_ID_FRAME_MiniMap.ID_BUTTON_PlayerShowALLOnButtonClick( s_CUI_ID_FRAME_MiniMap.m_pID_BUTTON_PlayerShowALL );
	//}

	m_nPlayerRenderFlag = s_CUI_ID_FRAME_MiniMap.GetRenderPlayerFlag(); 
	//s_CUI_ID_FRAME_Group_Me.compositor(true); //����



}

BOOL  CPlayerMgr::IsPlayerCanRenderEX(CPlayer* pPlayer, BOOL bDist)
{
	/*
	  ���IsPlayerCanRender�жϺ󲻿���ʾ����ҽ�����һ���ж�
	  ��Ҫ��� �����ͷǱ�������ҽ�������
	*/
	if( !pPlayer )
		return FALSE;

	if(!pPlayer->IsPlayer()) 
		return FALSE;

	if(!GetMe())
		return FALSE;

	// ��Ⱦ����
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

	if (GetMe()->GetRealCountry() != pPlayer->GetRealCountry()) //���
	{
		if(IsPlayerTypeRender(EPRF_ANTAGONIZE))
			return TRUE;
		else
			return FALSE;

	}else //����
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
			// ������������״̬, �����ڳ�(�ٻ���), �����������ճ���ʾ
			if ( pMaster->IsYabiaoState() )
			{
				// ����
				if ( pPlayer->GetMonsterType() == eMT_Pet )
					return TRUE;

				// ��
				if ( pPlayer->GetSubMonsterType() == Object_MonsterProtected )
					return FALSE;
			}
		}
	}

	// ��ѡ��Ŀ�꣬����Ⱦ
	if( GetLockPlayerID() > -1 )
	{
		CPlayer* pTargetPlayer = FindByID( GetLockPlayerID() );
		if( pTargetPlayer && pTargetPlayer == pPlayer/* && m_nPlayerRenderFlag & EPRF_TARGET*/)
			return TRUE;
	}

    // ��Ⱦ�Լ����Լ��ٻ���
    if( pPlayer == m_pMe || (m_pMe && m_pMe->HavePet() && pPlayer->GetID() == m_pMe->GetPetID()) )
    {
        if( g_bRenderRole && IsPlayerTypeRender(EPRF_ME))
            return TRUE;
        else
            return FALSE;
    }

    // ȫ����Ⱦ
    if( !bDist && m_nPlayerRenderFlag == EPRF_ALL )
        return TRUE;

    // ������װ���Ͳɼ���ƷĬ����Ⱦ
    if( pPlayer->IsItem() || (pPlayer->IsMonster() && pPlayer->IsCollection(false)) )
        return TRUE;

    // ��ȾNPC
    if( pPlayer->IsNpc() )
    {
        if( IsPlayerTypeRender(EPRF_NPC) )
            return TRUE;
        else
            return FALSE;
    }

    // ��Ⱦ����
    if( pPlayer->MyTeamMember )
    {
        if( IsPlayerTypeRender(EPRF_TEAM) )
            return TRUE;
        else
            return FALSE;
    }

	//  [1/9/2011 zhangjiayi]
	// ��ȾPK����	
	if( pPlayer->GetID() == thePlayerRole.GetDuelTarget() )
		return TRUE;	

    // ��Ⱦ����
    if( thePlayerRole.IsFriend(pPlayer->GetName()) )
    {
        if( IsPlayerTypeRender(EPRF_FRIEND) )
            return TRUE;
        else
            return FALSE;
    }

    // ��Ⱦ����
    if( !bDist && pPlayer->IsMonster() )
    {
        if( IsPlayerTypeRender(EPRF_MONSTER) )
        {
            // ����ǳ���ж���������Ƿ���Ⱦ������Ⱦ�����Ҳ����Ⱦ
            if( pPlayer->HaveMaster() && pPlayer->GetMasterID() > -1 )
            {
                CPlayer *pMaster = FindByID(pPlayer->GetMasterID());
                if ( pMaster != NULL )
                {
                    // �ж��Ƿ��Լ�����
                    if ( pMaster == m_pMe )
                    {
                        if( g_bRenderRole && IsPlayerTypeRender(EPRF_ME))
                            return TRUE;
                        else
                            return FALSE;
                    }

                    // �ж��Ƿ���ѳ���
                    if ( pMaster->MyTeamMember )
                    {
                        if( IsPlayerTypeRender(EPRF_TEAM) )
                            return TRUE;
                        else
                            return FALSE;
                    }

					// �ж��Ƿ���pk����ĳ���
					if ( pMaster->GetID() == thePlayerRole.GetDuelTarget() )
						return TRUE;					
                }
                // �Ƕ��ѳ���ж���������Ƿ���Ⱦ
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
			 return true; //��Ч��һֱ��Ⱦ
		 }

    // ��������
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
	//m_nPlayerRenderFlag = EPRF_ALL;//lyh++ �޸����������ʾ 
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

			// ��������
			pMousePlayer->SetNameColorByInfluence(col);
			sprintf(cColor,"<#%8x>",col);
			strTip += cColor;
			strTip += pMousePlayer->GetName();
			strTip += "\n";

			//����ƺ�
			if (pMonster && strlen(pMonster->GetTitle()) > 0)
			{
				//col = Color_Config.getColor((ColorConfigure)(CC_NpcTip_Title));
				sprintf(cColor,"<#%8x>",0xff00ff00);
				strTip += cColor;
				strTip += pMonster->GetTitle();
				strTip += "\n";
			}
			// ����ǰ׺
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
            //���ܲɼ�   �ٲ�׽(����)
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
				nStringId = -1; //lyh++ ����ǿ�ʯ���ͣ�����Ҫ��С�ȼ���������ʾ��Ŀǰ һ�ﵱǧ ��Ŀ�У�ֻ�� ͵���е����ǿ�ʯ����
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
            // ���Ӳ���     added by zhuomeng.hu		[11/9/2010]
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
			//��֪��Ϊʲô����Ҫ�ѳƺ�ǰ��ص��������ᵼ�����롣
			//strTip += pMousePlayer->GetTitle().substr(1, pMousePlayer->GetTitle().length() - 2);
			strTip += pMousePlayer->GetTitle();
			strTip += "\n";

		}
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pMousePlayer->GetNpcID());
		if (pInfo && pInfo->_nType == eNT_Item)
		{//�ɼ�NPC����ʾ�ȼ�
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
		//��������ļ������õĶ���Ϊ0��ʱ����������λ�ã���֮�ù̶�λ��
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

            //�޸�������ܿɼ����ɼ���Ҫ�ж�
			if(!GetMe())
                continue;

            if( pPlayer->GetMasterID() >= 0 ) //�ٻ����͹�
                continue;   

			//lyh++ �Զ��һ���ʱ�򣬲��ܽ��й����Ĺ��� ��ȥѡ����
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
        if (!swmap.CanMove(kOrgPosition,kDestPosition))  //ֻ����ֱ�ӵ���Ĺ���
            continue;

        D3DXVECTOR3 pos = pPlayer->GetPos();
        if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsInZone(pos.x,pos.y))  //������Χ�Ĳ���
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

			//�޸�������ܿɼ����ɼ���Ҫ�ж�
			if(!GetMe())
				continue;

			if( pPlayer->GetMasterID() >= 0 ) //�ٻ����͹�
				continue;            
		}

		if( pPlayer->GetDistanceToRole() > gCfg.m_fNameShowDistance )
			continue;

		if( pPlayer->NeedRemove() )
			continue;

		if( pPlayer->GetCurRenderAlpha() < 0.0618f )
			continue;

		D3DXVECTOR3 pos = pPlayer->GetPos();
 		//if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsInZone(pos.x,pos.y))  //������Χ�Ĳ��� û�� ���� 0 0 0 ��Ϊ���ĵ����뾶����ͼ�����ʱ�򣬽����������Χ���Ͳ���ѡ��
 		//	continue;                                                             //�����Ѿ����ϱ���һ�д��������޸�����������λ��Ϊ�����жϵ�

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
	// ͳ����ģ���У����������ֵ
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
		// �ٶ���̬ģ��ֻ��ײ�ˣ�����ײ���
		if( strstr(lwrName, "rcoli") || strstr(lwrName, "coli") )	// ֻ��ײ�ˣ��������
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
        // ����״̬
        if( pPlayer->m_cFightStatus.IsHide() )
            return false;

        // ����������Tab
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

        // ���ɼ����ٻ���
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

       //û�п��� ��ѡ�����
		if(!gCfg.GetIsOpenPetAtter() && pPlayer->HaveMaster())
			return false;

		 // �����������˲��ɹ�������Ҳ���ܱ�Tab
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

	// �ڴ����50M�����ٶ������ݣ�50M�ɿ��������
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

			//û��˵�����򣬲�������
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
	// Ԥ���ص�ͼ��ģ������
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

	// add by zmy, �����������ʱ����������ս��״̬
	if ( m_pMe != NULL )
	{
		if (m_pMe->IsYabiaoState())
		{
			return ; //lyh++ �������ϵ�ʱ���ܽ�����ͨ����
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
			//1:��Ч�ֿ��Թ�����ʱ�� 
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


	//����Ϣ֪ͨ������������������Ŀ��
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
	//�������壬���ڻ���
	if(!m_pFont)
	{
		HDC *pHDC = NULL;
		D3DXCreateFont( pd3dDevice, nWidth, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, 
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, "΢���ź�", &m_pFont );
	}

	//����1000��С�������Ϊ20 * 20
	for (int i = 0;i < 1000;++i)
	{
		IDirect3DSurface9 *pOldRs = NULL;
		IDirect3DSurface9 *pNewRs = NULL;
		//��õ�ǰ���ƻ���
		hr = pd3dDevice->GetRenderTarget(0,&pOldRs);
		if(FAILED(hr))
			return;

		//������������
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

		//���õ�ǰ���ƻ�����Ϊ������
		hr = pTex->GetSurfaceLevel(0,&pNewRs);
		if(FAILED(hr))
			return;

		//��Ⱦ���嵽��ǰ������
		pd3dDevice->SetRenderTarget(0,pNewRs);
		pd3dDevice->Clear(0L, NULL, D3DCLEAR_TARGET, 0x00ffffff, 1.0f, 0L);
		RECT fontRect = {0,0,nWidth,nWidth};
		if(m_pFont)
		{
			char szWord[64] = {0};
			MeSprintf_s(szWord,sizeof(szWord),"%d",i);
			m_pFont->DrawTextA( 0, szWord, -1, &fontRect, DT_CENTER|DT_VCENTER, 0xffff0000 );	
		}
		//�ָ���ȾĿ��
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
		// ȥ��headid�ֶ�
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
				if (msg->petLevel > m_player->GetLevel() &&  GetMe()->GetID() == m_player->GetMasterID()) //���յ�������Ϣ
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
							if ((pSkill->groupId == pReplaceSkill->groupId) && (pSkill->groupLevel > pReplaceSkill->groupLevel)) //��ͬһ�鼼�ܵĸ߼������滻�ͼ�����
							{
								MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetLearnAdvanceSkillOnBase),m_pet.baseInfo.szName,pReplaceSkill->GetSkillName(),pSkill->GetSkillName());	
							}
							else
							{
								MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetReplaceSkill),m_pet.baseInfo.szName,pSkill->GetSkillName(),pReplaceSkill->GetSkillName());
							}
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Others_Success, temp);
							CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,temp);//������ʾ
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
	m_pCameraAnim->SetPosition(x,y,z); //����λ��

	//���ýǶ�
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
	{ // ��һ����
		fDirX = fPosXOff;
		fDirY = fPosYOff;
	}
	else if( ( fDir >= D3DX_PI/2 && fDir <= D3DX_PI ) || ( fDir >= -D3DX_PI*3/2 && fDir <= -D3DX_PI ) )
	{ // �ڶ�����
		fDirX = -fPosXOff;
		fDirY = fPosYOff;
	}
	else if( ( fDir >= D3DX_PI && fDir <= D3DX_PI*3/2 ) || ( fDir >= -D3DX_PI && fDir <= -D3DX_PI/2 ) )
	{ // ��������
		fDirX = -fPosXOff;
		fDirY = -fPosYOff;
	}
	else if( ( fDir >= D3DX_PI*3/2 && fDir <= D3DX_PI*2 ) || ( fDir >= -D3DX_PI/2 && fDir <= 0 ) )
	{ // ��������
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
		// ����ʧ��,����ʧ�ܵ�ԭ����д���
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

		// ��Ǯ //�����ٿ�Ǯ�Ϳ�2���� lrt
		/*DWORD dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
		thePlayerRole.Update(CPlayerRole::TYPE_MONEY, dwMoney - itemHero->need_money);
		s_CUI_ID_FRAME_PACK.RefreshMoney();*/

		// ɾ����Ʒ
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

		//�ر�UI
		s_CUI_ID_FRAME_zhujiangbianshen.SetVisable( false );
		s_CUI_ID_FRAME_PACK.SetVisable(false);

		thePlayerRole.m_charinfo.baseinfo.liveinfo.hero_id = pBianShen->hero_id;
	}

	player->SetHeroID(pBianShen->hero_id);
	player->ShapeShift();

	// ���Ŷ�������Ч����ͷ�й�
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

	// �ȱ���, ������״̬
	player->MorphMonster(msg->monsterID);
	player->SetYabiaoState(true);
	// �ڳ�������Ϊ:��ɫģ�ʹ�С���Թ������������
	player->SetBiaocheScale(PlayerInfoMgr::Instance()->GetScaleForPlayer(theHeroGame.GetPlayerMgr()->GetMe(), false) * biaocheMonster->fBodySize);

	{
		s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().EndFight();
		if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString(eText_AutoFightEnd) );
	}

	

	// ����ʵ�ʵ��ڳ�
	// �߼���PlayerMgr��IsPlayerCanRender������
}

void CPlayerMgr::OnMsgRestoreFromBiaocheAck(Msg* pMsg)
{
	MsgRestoreFromBiaocheAck *msg = (MsgRestoreFromBiaocheAck *) pMsg;

	CPlayer *player = FindByID(msg->header.stID);
	if (player == NULL)
		return;
	
	// ������״̬, �ٱ���
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
	//todo:��ӡ����
	s_CUI_ID_FRAME_ManualLevelUp.DoneLimit();
}
void CPlayerMgr::OnMsgUnBindEquip(Msg* pMsg)
{
	//���յ��ط�����
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
