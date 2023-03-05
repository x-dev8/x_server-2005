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
#include "MessageDefine.h"
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
#include "color_config.h"
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
#include "ui/SelectAssignMode.h"
#include "ui/Team.h"
#include "AttackInfoMan.h"
#include "ProcessCharInfo.h"
#include "SystemConfig.h"
#include "ErrorLog.h"
#include "MeUi/MouseManager.h"
#include "ui\FriendDlg.h"
#include "ui\rbtnmenu.h"
#include "ui/PetRbtnMenu.h"
#include "ui/MiniMapUI.h"
#include "MiniMap.h"
#include "ui/Progress.h"
#include "ShowScreenText.h"
#include "ui/topinfo.h"
#include "ui/Gang.h"
#include "ui/FaceDlg1.h"
#include "ui/ActionUI.h"
#include "ui/AllNpcList.h"
#include "shortcutkey_configure.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "CrossMapPF.h"
#include "PathDirection.h"
#include "Dxsdk/dinput.h"
#include "ui/ExitGame.h"
#include "Cfg.h"
#include "ui/PrivateShop.h"
#include "WorldMap.h"
#include "../GameUI/AutoAttackSet.h"
#include "ui/GameSettingTab.h"
#include "WSModelEffect.h"
#include "wsCamera.h"
#include "Common.h"
#include "NpcTaskDialogBox.h"
#include "ScreenInfoManager.h"
#include "ui/FriendDlgRight.h"
#include "SystemStallage.h"
#include "ui/SuAnimalMenu.h"
#include "IntroductionManager.h"
#include "PositionInfo.h"
#include "..\GameUI\AutoAttackSet.h"
#include "PlayerInfoMgr.h"
#include "ItemDetailConfig.h"
#include "MonsterDefine.h"
#include "EffectCharConfig.h"

extern float			g_fTheRoleDirCorrect;
extern BOOL				g_bTheRoleMoveToTargetPos;
extern D3DXVECTOR3		g_vTheRoleTargetPos;
extern D3DXVECTOR3		g_vTheRoleTargetDir;
extern D3DXVECTOR3		g_vTheRoleJumpingDir;
extern int				g_nTargetPointEffectContainerID;
extern int				g_nTargetPointEffectID;
extern float			g_fTheRoleJumpingRotate;
extern float			g_fTheRoleRotateZCorrect;
extern BOOL				g_bAutoRunForward;
extern BOOL				g_bTheRoleMovingByDir;
extern BOOL				g_bTheRoleAttackLockTarget;
extern BOOL				g_bMouseMoveMode;
extern BOOL				g_bTheRoleJumping;
extern DWORD			g_dwTheRoleJumpingEndTime;
extern BOOL				g_bTheRoleJumpingCountermarch;
extern BOOL				g_bTheRoleCountermarch;
extern DWORD			g_dwTheRoleJumpTime;
extern BOOL				g_bKeyboardVK_XIsDown;
extern DWORD			g_dwLastFrameBeginTime;
extern DWORD			g_dwTheRoleSlipStartTime;
extern BOOL				g_bTheRoleSlipJumping;
extern D3DXVECTOR3		g_vTheRoleAttackTargetPos;
extern int              g_nRoleCommonAttackStatus;
DWORD g_dwStartMountNeighTime = 0;
extern BOOL IsFlagModel(int iModelID);
extern short GetKeyboardInput( int iKey );
extern int ComparePlayerDist( const VOID* arg1, const VOID* arg2 );
extern BOOL g_bRoleMoveByLRButtonDown;
extern BOOL g_bMouseLButtonRotate;
extern BOOL g_bMouseRButtonRotate;
extern BOOL g_bAutoPlayInteractionWithTarget;
extern BOOL g_bAutoOpenPrivateShop;
extern DWORD   g_dw25DLButtonDownStartTime;
extern BOOL g_b25DRoleMoveFollowMouse;
extern BOOL g_b25DMouseLButtonDownOnTerrain;
extern float g_PickedZFromMouse;
extern BOOL g_b25DRoleMoveFollowMouseFocusOnUI;
extern BOOL g_bPackagePickAll;

// 采集技能等级判断
// 采草
BOOL CanLootHerb(CPlayer* pTargetPlayer, ItemDefine::SItemSkill* pCurSkill, BOOL bShowText)
{
    SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(ItemDefine::eCSI_CaiYao);
    if( !pCharSkill )
        return FALSE;
	// 判断是否采草技能
	ItemDefine::SItemSkill* pLootSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_CaiYao, pCurSkill->ustLevel );
	if( pLootSkill != pCurSkill )
	{
		// 使用技能非采草技能
		if( bShowText )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
		return FALSE;
	}
    if( pCharSkill->stSkillLevel < pTargetPlayer->GetLevel() || pCurSkill->ustLevel < pTargetPlayer->GetLevel() )
    {
        // 采药技能等级不够
        if( bShowText )
        {
            char skillfailed_msg[MAX_PATH] = {0};
            MeSprintf_s(skillfailed_msg,sizeof(skillfailed_msg)/sizeof(char) - 1, theXmlString.GetString( eText_LootFailed_HerbLevelNotMatch ), pTargetPlayer->GetLevel());
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, skillfailed_msg );
        }
        return FALSE;
    }
    return TRUE;
}

// 捕虫
BOOL CanLootInsect( CPlayer* pTargetPlayer, ItemDefine::SItemSkill* pCurSkill, BOOL bShowText )
{
    SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_BuChong );
    if( !pCharSkill )
        return FALSE;
    // 判断是否捕虫技能
    ItemDefine::SItemSkill* pLootSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_BuChong, pCurSkill->ustLevel );
    if( pLootSkill != pCurSkill )
    {
        // 使用技能非捕虫技能
        if( bShowText )
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
        return FALSE;
    }
    if( pCharSkill->stSkillLevel < pTargetPlayer->GetLevel() || pCurSkill->ustLevel < pTargetPlayer->GetLevel() )
    {
        // 捕虫技能等级不够
        if( bShowText )
        {
            char skillfailed_msg[MAX_PATH] = {0};
            MeSprintf_s( skillfailed_msg,sizeof( skillfailed_msg ) / sizeof( char ) - 1, theXmlString.GetString( eText_LootFailed_InsectLevelNotMatch ),
                pTargetPlayer->GetLevel() );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, skillfailed_msg );
        }
        return FALSE;
    }
    return TRUE;
}

// 挖矿
BOOL CanLootMine(CPlayer* pTargetPlayer, ItemDefine::SItemSkill* pCurSkill, BOOL bShowText)
{
    SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(ItemDefine::eCSI_CaiKuang);
    if( !pCharSkill )
        return FALSE;
	// 判断是否采矿技能
    ItemDefine::SItemSkill* pLootSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_CaiKuang, pCurSkill->ustLevel );
    if( pLootSkill != pCurSkill )
    {
        // 使用技能非挖矿技能
        if( bShowText )
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
        return FALSE;
    }

    if( pCharSkill->stSkillLevel < pTargetPlayer->GetLevel() || pCurSkill->ustLevel < pTargetPlayer->GetLevel() )
    {
        // 挖矿技能等级不够
        if( bShowText )
        {
            char skillfailed_msg[MAX_PATH] = {0};
            MeSprintf_s(skillfailed_msg,sizeof(skillfailed_msg)/sizeof(char) - 1, theXmlString.GetString( eText_LootFailed_MineLevelNotMatch ), pTargetPlayer->GetLevel());
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, skillfailed_msg );
        }
        return FALSE;
    }
    return TRUE;
}

BOOL CPlayerMgr::ControlLButDownProc( float x, float y, bool bPicked )
{
    // 2.5D鼠标操作
    if( getwsCamera()->GetLock45DegreeCameraMode() && GetMe() && !GetMe()->IsSelectingPoint() )
    {
		if (theHeroGame.getshCur25Direction() == CHeroGame::EMD_NONE)
		{
			g_b25DMouseLButtonDownOnTerrain = TRUE;
			if( !g_b25DRoleMoveFollowMouse )
			{
				g_dw25DLButtonDownStartTime = HQ_TimeGetTime();
			}
		}
    }
    return TRUE;
}

void CPlayerMgr::UseSilllToSelectPoint()
{
	m_pMe->SetIsSelectingPoint( false );
	//jiayi todo : 释放技能
	//...
	int nCurUseSkillID = GetCurUseSkill();
	int nCurUseSkillLevel = GetCurUseSkillLevel();
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( nCurUseSkillID, nCurUseSkillLevel );
	if( !pSkill )
	{
		theUiManager.SetFocus(NULL);
		return;
	}

	// 判断是否特殊目标类型
	if( pSkill->usSpecialTargetType == ItemDefine::STT_NONE )
		m_pMe->TryUseSkill( 0, pSkill );
	else
	{
		// 单体并且需要选特殊目标
		if( pSkill->shCastType == ItemDefine::casttype_singletarget && pSkill->usSpecialTargetType != ItemDefine::STT_NONE )
		{
			float fDamageMaxDist = m_pMe->GetDistToTarget(m_pMe->GetPointAoePos().x, m_pMe->GetPointAoePos().y) + pSkill->fAOEradius;
			if( m_nPlayerQueueCount <= 0 )
			{
				theUiManager.SetFocus(NULL);
				return;
			}

			int iPickTarget = -1;
			unsigned int fPickTargetParam = 0xffffffff;
			float fAOEradiusSqr = pSkill->fAOEradius * pSkill->fAOEradius;
			if( m_nPlayerRenderLimit < PLAYER_RENDER_MAX && m_nPlayerQueueCount > 1 && m_nPlayerQueueCount <= m_nPlayerRenderLimit )
			{
				// 远近排序，按同屏人数限制及优先级高低进行渲染
				qsort(m_PlayerDistQueue, m_nPlayerQueueCount, sizeof(PlayerRenderLimitData), ComparePlayerDist);
			}

			for(int i=0; i<m_nPlayerQueueCount; i++)
			{
				CPlayer* pPlayer = m_PlayerDistQueue[i].pPlayer;
				if( !pPlayer 
					|| ! m_PlayerDistQueue[i].bRendered
					|| (!GetMe()->canAttack(pPlayer))
					)
					continue;

				if( pPlayer->GetDistanceToRole() < fDamageMaxDist )
				{
					float fXOffset = pPlayer->GetPos().x - m_pMe->GetPointAoePos().x;
					float fYOffset = pPlayer->GetPos().y - m_pMe->GetPointAoePos().y;
					float fDistToPointSqr = fXOffset*fXOffset + fYOffset*fYOffset;
					if( fDistToPointSqr < fAOEradiusSqr )
					{
						switch(pSkill->usSpecialTargetType)
						{
						case ItemDefine::STT_MINHP:
							if( fPickTargetParam > pPlayer->GetHp() )
							{
								iPickTarget = i;
								fPickTargetParam = pPlayer->GetHp();
							}
							break;
						case ItemDefine::STT_MINMP:
							if( fPickTargetParam > pPlayer->GetMp() )
							{
								iPickTarget = i;
								fPickTargetParam = pPlayer->GetMp();
							}
							break;
						case ItemDefine::STT_MINLEVEL:
							if( fPickTargetParam > pPlayer->GetLevel() )
							{
								iPickTarget = i;
								fPickTargetParam = pPlayer->GetLevel();
							}
							break;
						}
					}
				}
				else    // 超出AOE最远点到人的距离
					break;
			}

			if( iPickTarget >= 0 )
			{
				CPlayer* pPlayer = m_PlayerDistQueue[iPickTarget].pPlayer;
				if( GetLockPlayerID() != pPlayer->GetID() )
				{
					cancelBehavior();
					SetLockNpc(pPlayer->GetID());
				}
				m_pMe->TryUseSkill( pPlayer, pSkill );
			}
			else
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eUI_SillTyps_Target_no ) );     
			}
		}
	}

	theUiManager.SetFocus(NULL);
}

///////////////////////////////////////////
BOOL	CPlayerMgr::ControlLButUpProc( float x, float y, bool bPicked )
{
	guardfunc;

	//如果跟随状态，取消点击地面行走效果
	if ( s_CUI_ID_FRAME_Team.GetTeamFollowID() >= 0 )
	{
		return FALSE;
	}

	if( g_bMouseMoveMode && g_bAutoRunForward)
		g_bAutoRunForward = FALSE;

	if( !m_pMe )
		return FALSE;

	if( m_pMe->IsWillDie() || m_pMe->IsDead() || !m_pMe->IsCanMove() )
	{
		// added, jiayi, [2009/7/20], point aoe
		m_pMe->SetIsSelectingPoint( false );
		theUiManager.SetFocus(NULL);
		return FALSE;
	}

	if( m_pMe->IsSelectingPoint() )
	{
		UseSilllToSelectPoint();
		return true;
	}

	s_CUI_ID_FRAME_RBTNMENU.SetVisable( FALSE );
	s_CUI_ID_FRAME_SelfRBMenu.SetVisable(false);
	s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(false);
	s_CUI_ID_FRAME_PetRBMenu.SetVisable(false);
	s_CUI_ID_FRAME_FACE.SetVisable( false );
 	s_CUI_ID_FRAME_FriendDlgRight.SetVisable(false);

	//deleted by zhuomeng.hu		[9/14/2010]
	//s_CUI_ID_FRAME_Chat_Tips.SetTipListVisable(false);
	//s_CUI_ID_FRAME_Chat_Tips.SetPicture6527(false);
	CPlayer* pPlayer = FindByID( m_nPickId);

	if( !pPlayer )
	{
		pPlayer = FindByID( m_shMouseTargetPlayerSeverID  );
	}

	//RequestGetOnOtherPet( pPlayer );
	s_CUI_ID_FRAME_Team.CheckOnPlayerClick(pPlayer);
	//清理PickId
	m_nPickId = -1;
	if (NULL != pPlayer )
	{
        if( GetLockPlayerID() < 0 || (GetLockPlayerID() > 0 && GetLockPlayerID() != pPlayer->GetID()) )
        {
            // 无锁定目标，或已锁定目标与选中目标不同，锁定选定目标
            g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
            //判断是否是道具
            if (pPlayer->IsItem())
            {
                if( pPlayer->m_bCanPick && pPlayer->IsItemDropDelayOver() )
				{
					// 隐藏目标头像，放在SetLockPlayerID前调用
					s_CUI_ID_FRAME_Target.SetPlayer( -1 );
					SetLockPlayerID(pPlayer->GetID());
				}
            }
            else if( pPlayer->IsNpc() )
            {
                const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pPlayer->GetNpcID());
                if( pInfo && pInfo->_nType == eNT_Item )    // NPC是Item类型，则不显示选中头像
                {
					// 隐藏目标头像，放在SetLockPlayerID前调用
					s_CUI_ID_FRAME_Target.SetPlayer( -1 );
                    SetLockPlayerID(pPlayer->GetID());
                }
                else
                    SetLockNpc( pPlayer->GetID() );
            }
            else
            {
				/*
				 * Author: 2013-1-7 14:24:19 wangshuai
				 * Desc:   阴挡怪也可以选中
				 */
				//if(!( pPlayer->IsMonster() && pPlayer->GetMonsterType() == eMT_Collision ) )
				{
					//战斗指引
					if( pPlayer->IsMonster() && !pPlayer->IsPet() && thePlayerRole.IsFinishedIntroduce(INTRO_MONSTER_KILL) == false )
					{
						CIntroductionManager::Instance()->ShowTipWithPlayer( INTRO_MONSTER_KILL, pPlayer );
						thePlayerRole.SetFinishedIntroduce(INTRO_MONSTER_KILL);
					}

					//特效怪
					if(pPlayer->IsEffect())
					{
						EFFECTCHARCONFIG _Config;
						if(theEffectCharConfig.FindEffectCharConfigBySkillID(_Config,pPlayer->GetEffectCharSkillID()))
						{
							SetLockNpc(-1);
						   if(_Config.bCanBeAttack)
						   {
                              SetLockNpc( pPlayer->GetID() );
						   }
						}
                       
					}else
					{
                       SetLockNpc( pPlayer->GetID() );
					}
					

					//// add by zmy, 当锁定怪物的时候立即进入战斗状态
					//if ( m_pMe != NULL )
					//{
					//	if( ( pPlayer->IsMonster() && !pPlayer->IsPet() ) || thePlayerRole.GetDuelTarget() == pPlayer->GetID() )
					//	{
					//		//if ( !m_pMe->HasFightFlag(eFighting) )
					//		//{
					//		//	m_pMe->AddFightFlag( eFighting );
					//		//}
					//		if ( !m_pMe->IsFightPose() )
					//		{
					//			m_pMe->ChangeToFightPose();
					//		}
					//	}
					//	else
					//	{
					//		if ( m_pMe->HasFightFlag(eFighting) )
					//		{
					//			m_pMe->ClearFightFlag( eFighting );
					//		}
					//	}
					//}

				}
            }
            
			if (pPlayer->IsNpc())
			{
				float fX = 0;
				float fY = 0;
				pPlayer->GetPFPos(fX, fY);
				if (ProcessShift(fX,fY))
				{
					return TRUE;
				}
			}
        }
        else    // 锁定目标与选中目标相同
        {
            m_bClickTheTerrain = false;
            float xSrc = m_pMe->GetPos().x;
            float ySrc = m_pMe->GetPos().y;
            float xDst = pPlayer->GetPos().x;
            float yDst = pPlayer->GetPos().y;
            float x = xDst - xSrc;
            float y = yDst - ySrc;
            float fDistToRole = sqrtf( x*x + y*y );
            float fPickDist = PackagePickDistance;	//拾取距离

            //判断是否是道具
            if (pPlayer->IsItem())
            {
                if( pPlayer->m_bCanPick && pPlayer->IsItemDropDelayOver() )
                {
                    g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
                    // 判断是否拾取全部
                    if( GetKeyboardInput(DIK_LSHIFT) )
                        g_bPackagePickAll = TRUE;
                    else
                        g_bPackagePickAll = FALSE;

                    if( fDistToRole > fPickDist )
                    {
                        MoveRoleToPlayer( pPlayer, TRUE, 0.0f, TRUE );
                    }
                    else
                    {
                        m_pMe->TryPickItem( pPlayer );
                    }
                }
            }
            //判断是否是可采集物品
            else if( pPlayer->IsCollection() )
            {
                if( !GetMe()->IsIntonating() )
                {
                    // 是否抓马，是否能改为捕捉(待修改)
                    if( pPlayer->IsMonsterType(eMT_Mount) )
                    {
                        // 判断兽栏空间
                        if( thePlayerRole.IsSkillCanUse( ItemDefine::eCSI_BuZhuo, 1 ) )
                        {
                            if( thePlayerRole.HasMountSpace() )
                            {
                                g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
                                MoveRoleToPlayer( pPlayer );
                            }
                            else
                                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBag_NotSpace ) );
                        }
                    }
                    else
                    {
                        g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
                        MoveRoleToPlayer( pPlayer );
                    }
                }
            }
            //判定是否是脚本npc
            else if( pPlayer->IsNpc() ||
				(pPlayer->IsMonster() 
				&& (pPlayer->GetTypeStatus() == MonsterDefine::StatusUnMoveNpc || pPlayer->GetTypeStatus() == MonsterDefine::StatusMoveNpc ))) //lyh++ npc 和 像ncp一样的怪物 都可以请求脚本
            {
                 if(pPlayer->IsMonster()) //不可攻击的monster 像npc一样
				 {
					 m_controldata.bLeftDownFlag = FALSE;//这样在对话的时候人就不会到处跑了

					 if( fDistToRole < 6.0f )
					 {
						 BeginDialog(xDst,yDst);
						 //SetLockNpc(pPlayer->GetID());

						 m_pMe->SetMoving( FALSE );
						 //m_pMe->TryTalkWithNpc( pPlayer );
						 MsgReqScript msg;
						 msg.stNpcId = pPlayer->GetID();
						 GettheNetworkInput().SendMsg( &msg );
					 }
					 else// if( g_bMouseMoveMode )
					 {
						 // 鼠标左键点NPC，直接跑过去交谈
						 MoveRoleToPlayer( pPlayer, TRUE, 0.0f, TRUE );
					 }
					 g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;

				 }else
				 {
					 float fX = 0;
					 float fY = 0;
					 pPlayer->GetPFPos(fX, fY);
					 if (ProcessShift(fX,fY))
					 {
						 return TRUE;
					 }
					 if (GetMe()->canAttack(pPlayer))
					 {//可攻击的npc
						 AttackPlayer(pPlayer);
					 }
					 else
					 {
						 m_controldata.bLeftDownFlag = FALSE;//这样在对话的时候人就不会到处跑了

						 if( fDistToRole < 6.0f )
						 {
							 BeginDialog(xDst,yDst);
							 SetLockNpc(pPlayer->GetID());

							 m_pMe->SetMoving( FALSE );
							 m_pMe->TryTalkWithNpc( pPlayer );
						 }
						 else// if( g_bMouseMoveMode )
						 {
							 // 鼠标左键点NPC，直接跑过去交谈
							 MoveRoleToPlayer( pPlayer, TRUE, 0.0f, TRUE );
						 }
						 g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
					 }

				 }

				
            }
            else
            {
				// 鼠标左键选怪物或切磋对象，直接跑过去并攻击
				if( GetMe()->canAttack(pPlayer) )
				{
					AttackPlayer(pPlayer);
				}
            }
        }
	}
	else
	{
        if( !getwsCamera()->GetLock45DegreeCameraMode() )   // 3D视角操作
        {
		    if( bPicked && g_bMouseMoveMode && !g_bRoleMoveByLRButtonDown && !g_bMouseLButtonRotate )
		    {
				if (ProcessShift(x,y))
				{
					return TRUE;
				}
				OnClickNon_object(x, y);
			}
        }
        else
        {
            if(g_b25DMouseLButtonDownOnTerrain )
            {
                g_b25DRoleMoveFollowMouse = FALSE;
                g_b25DRoleMoveFollowMouseFocusOnUI = FALSE;
                theMouseManager.SetUICursor(MouseManager::Type_Arrow);

				if(theHeroGame.getshCur25Direction() == CHeroGame::EMD_NONE)
					OnClickNon_object(x, y);
            }
        }
	}
	g_b25DMouseLButtonDownOnTerrain = FALSE;
    g_bMouseLButtonRotate = FALSE;
	theUiManager.SetFocus(NULL);
	return TRUE;
	unguard;
}

void CPlayerMgr::OnClickNon_object( float x, float y )
{
	{
		if( m_pMe )
			m_pMe->ClearActionTarget();
		m_SkillBufTargetID = -1;
		SetCurUseSkill( 0, 0 );

		//如果玩家鼠标在拖动 icon中 ，则不进行移动
		if(theIconDragManager.IsIconMoved())
			return;

		MoveRoleTo( x, y ,true,false,true,true);

		// 判断是否打断跟随
		if( s_CUI_ID_FRAME_Target.GetFollowPlayerId() >= 0 )
		{
			s_CUI_ID_FRAME_Target.SetFollowPlayerId(-1);
		}

        if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
            s_CUI_ID_FRAME_AutoAttackSet.ID_BUTTON_StopOnButtonClick(NULL);
		CrossMapPF::Instance()->Reset();
		CPathDirection::Instance()->Reset();
		s_CUI_ID_FRAME_MiniMap.SetAutoRuning(false);
	}
}

//----
//右键处理
//----
BOOL    CPlayerMgr::ControlRButDownProc(int x, int y)
{
	guardfunc;

	s_CUI_ID_FRAME_Team.CheckOnPlayerClick(NULL);
	if( !GetMe() )
		return FALSE;
    CPlayer* pTargetPlayer = NULL;
    if( GetLockPlayerID() >= 0 )
    {
        pTargetPlayer = FindByID(theHeroGame.GetPlayerMgr()->GetLockPlayerID());
    }
    // 无目标，或有目标但不是NPC也不是采集物品，或者目标为采集物品但不在采集
// 	if( (!pTargetPlayer 
// 		|| ( pTargetPlayer && !pTargetPlayer->IsNpc() && !pTargetPlayer->IsCollection(false)) 
// 		|| ( pTargetPlayer && pTargetPlayer->IsCollection(false) && !GetMe()->IsIntonating())) 
// 		&& m_nMouseRDownTargetPlayerServerID < 0 /*&& m_shMouseTargetPlayerSeverID < 0*/ 
// 		&& !getwsCamera()->GetLock45DegreeCameraMode() )
	//不做特殊处理
	if(!getwsCamera()->GetLock45DegreeCameraMode())
		SetTurnRoleToCamera(TRUE);

	m_nMouseRDownTargetPlayerServerID = m_shMouseTargetPlayerSeverID;
	return TRUE;
	unguard;
}

BOOL    CPlayerMgr::ControlRButUpProc(int x, int y)
{
	guardfunc;
	m_controldata.bRightDownFlag = TRUE;
	int iTargetID = -1;

	if( m_nMouseRDownTargetPlayerServerID != m_shMouseTargetPlayerSeverID )
		return FALSE;

	if( !m_pMe )
		return FALSE;

    if( m_pMe->IsWillDie() || m_pMe->IsDead() || !m_pMe->IsCanMove() )
    {
        return FALSE;
    }

	m_nMouseRDownTargetPlayerServerID = -1;

	s_CUI_ID_FRAME_RBTNMENU.SetVisable( false );
	s_CUI_ID_FRAME_SelfRBMenu.SetVisable(false);
	s_CUI_ID_FRAME_PetRBMenu.SetVisable(false);
	s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(false);
	s_CUI_ID_FRAME_FACE.SetVisable( false );
 	s_CUI_ID_FRAME_FriendDlgRight.SetVisable(false);

	//deleted by zhuomeng.hu		[9/14/2010]
	//s_CUI_ID_FRAME_Chat_Tips.SetTipListVisable(false);
	//s_CUI_ID_FRAME_Chat_Tips.SetPicture6527(false);

    CPlayer* pPlayer = FindByID( m_shMouseTargetPlayerSeverID );

	if( pPlayer )
	{
        m_bClickTheTerrain = false;
        float xSrc = 0;
        float ySrc = 0;
        float xDst = 0;
        float yDst = 0;
        float x = 0;
        float y = 0;
        float Dist = 0;
        float BodyDist = 0;
        float TargetDir = 0;

        xSrc = m_pMe->GetPos().x;
        ySrc = m_pMe->GetPos().y;
        xDst = pPlayer->GetPos().x;
        yDst = pPlayer->GetPos().y;
        //		BodyDist = m_pMe->GetBodySize() + pPlayer->GetBodySize();
        BodyDist = PackagePickDistance;	//拾取距离

        x = xDst - xSrc;
        y = yDst - ySrc;
        Dist = sqrtf( x*x + y*y );
        TargetDir = atan2f( y, x );

        //判断是否是道具
        if (pPlayer->IsItem())
        {
            if( pPlayer->m_bCanPick && pPlayer->IsItemDropDelayOver() )
            {
                g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
                // 判断是否拾取全部
                if( GetKeyboardInput(DIK_LSHIFT) )// modified, jiayi, [2009/11/20]
                    g_bPackagePickAll = TRUE;
                else
                    g_bPackagePickAll = FALSE;

				// 隐藏目标头像，放在SetLockPlayerID前调用
				s_CUI_ID_FRAME_Target.SetPlayer( -1 );
                SetLockPlayerID(pPlayer->GetID());

                if( Dist > BodyDist )
                {
                    MoveRoleToPlayer( pPlayer, TRUE, 0.0f, TRUE );
                }
                else
                {
                    m_pMe->TryPickItem( pPlayer );
                }
            }
        }
        //判断是否是可采集物品
        else if( pPlayer->IsCollection())
        {
            if( !GetMe()->IsIntonating() )
            {
                // 是否抓马，是否能改为捕捉(待修改)
                if( pPlayer->IsMonsterType(eMT_Mount) )
                {
                    // 判断兽栏空间
                    if( thePlayerRole.IsSkillCanUse( ItemDefine::eCSI_BuZhuo, 1 ) )
                    {
                        if( thePlayerRole.HasMountSpace() )
                        {
                            g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
                            MoveRoleToPlayer( pPlayer );
                            SetLockNpc( pPlayer->GetID() );
                        }
                        else
                            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBag_NotSpace ) );
                    }
                }
                else
                {
                    if( pPlayer->IsMonsterType(eMT_Herb) || pPlayer->IsMonsterType(eMT_Mine) || pPlayer->IsMonsterType( eMT_Insect ) )
                    {
                        // 材料包是否已满
                        if( thePlayerRole.m_bagMaterial.GetNullItemCount() <= 0 )
                            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_MaterialPackFull ) );
                    }
                    g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
                    MoveRoleToPlayer( pPlayer );
                    SetLockNpc( pPlayer->GetID() );
                }
           }
        }

        //判定是否是脚本npc
        else if( pPlayer->IsNpc() )
        {
            m_controldata.bLeftDownFlag = FALSE;//这样在对话的时候人就不会到处跑了

            const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pPlayer->GetNpcID());
            if( pInfo && pInfo->_nType == eNT_Item )    // NPC是Item类型，则不显示选中头像
            {
				// 隐藏目标头像，放在SetLockPlayerID前调用
				s_CUI_ID_FRAME_Target.SetPlayer( -1 );
                SetLockPlayerID(pPlayer->GetID());
            }
            else
                SetLockNpc( pPlayer->GetID() );

			if ((GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT) ))
			{
				float fX = 0;
				float fY = 0;
				pPlayer->GetPFPos(fX, fY);
				CWorldTile* pCurrTile = CURRENTTILE;
				s_CUI_ID_FRAME_AllNpcList.ShowTile(pCurrTile,(int)fX,(int)fY);
				return TRUE;
			}
			if (GetMe()->canAttack(pPlayer))
			{//可攻击的npc
				AttackPlayer(pPlayer);
			}
			else
			{
				if( Dist <  6.0f )
				{
					BeginDialog(xDst,yDst);
					SetLockNpc(pPlayer->GetID());
					m_pMe->SetMoving( FALSE );
					m_pMe->TryTalkWithNpc( pPlayer );
				}
				else
				{
					// 鼠标左键点NPC，直接跑过去，QL，2009/05/31
					//if( g_bMouseMoveMode )
					if( s_CUI_ID_FRAME_Team.GetTeamFollowID() == -1 ) //要求在跟随状态点击npc不会跑过去
					{
						MoveRoleToPlayer( pPlayer, TRUE, 0.0f, TRUE );
					}
				}
				g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
				SetTurnRoleToCamera(FALSE);
			}
		}
		else if (pPlayer->GetSubMonsterType() == Object_MonsterProtected)
		{
			/*
			// 右击镖车上车
			// 只要在镖车是能骑的状态下，不是在坐骑上，不是跳的过程中才可以变身镖车
			if (m_pMe != NULL && !m_pMe->IsMounting() && !m_pMe->IsJumping() && pPlayer->IsCanRide())
			{
				CPlayer *master = FindByID(pPlayer->GetMasterID());
				if (master != NULL && master == m_pMe)
				{
					ItemDefine::SMonster *biaocheMonster = theItemDetailConfig.GetMonsterById(pPlayer->GetMonsterID());
					if (biaocheMonster != NULL)
					{
						MsgBiaoche msg;
						msg.state = 1;
						msg.monsterID = pPlayer->GetMonsterID();
						// 角色模型大小乘以怪物的体型修正
						msg.scale = PlayerInfoMgr::Instance()->GetScaleForPlayer(m_pMe, false) * biaocheMonster->fBodySize;
						msg.moveSpeed = biaocheMonster->fMoveSpeed;
						GettheNetworkInput().SendMsg(&msg);
					}
				}
			}
			*/
		}
		else 
        {
			// 鼠标左键选怪物或切磋对象，直接跑过去并攻击
			if(GetMe()->canAttack(pPlayer) && !g_bRoleMoveByLRButtonDown && !g_bMouseRButtonRotate)
			{                        
				AttackPlayer(pPlayer);
			}
        }
		return TRUE;
	}
	else
	{
		// 取消选中
		if( GetLockPlayerID() >= 0 && fabs(getwsCamera()->GetCameraRotateXWhenRButtonIsDown() - getwsCamera()->GetCameraRotateX()) < 0.001f
			&& !g_bRoleMoveByLRButtonDown )
		{
			cancelBehavior();
		}
        SetTurnRoleToCamera(FALSE);
	}
	return TRUE;
	unguard;
}
//----
//对热键的处理
//----
BOOL    CPlayerMgr::ControlHotKeyProc(int HotKeyIdnex)
{
	guardfunc;
	return TRUE;
	unguard;
}
//清空快捷方式
BOOL    CPlayerMgr::MouseShortCutClear(void)
{
	guardfunc;
	MsgHitItemBag	msg;
	msg.BagIndex = 0;
	msg.BagType = BagTypeMax;//最多的背包类型
	GettheNetworkInput().SendMsg(&msg, msg.GetLength());
	return TRUE;
	unguard;
}

BOOL CPlayerMgr::CheckPrivateShop( int x, int y )
{
	if( !GetMe() )
		return FALSE;
	std::map<GameObjectId, CPlayer*>::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); it++ )
	{
		CPlayer* pPlayer = it->second;
		if ( !pPlayer || !pPlayer->IsPlayer() )
			continue;
		if ( pPlayer == GetMe() )
		{
			continue;
		}
		if ( pPlayer->IsPtInPrivateShopInfo( x, y ) )
		{
			CPlayer *pMe = GetMe();
			float fSrcX, fSrcY, fSrcZ;
			float fDstX, fDstY, fDstZ;
			pMe->GetPos( &fSrcX, &fSrcY, &fSrcZ );
			pPlayer->GetPos( &fDstX, &fDstY, &fDstZ );
			float x = fDstX - fSrcX;
			float y = fDstY - fSrcY;
			float dist = sqrtf( x*x + y*y );
			if( dist > 10.0f )
			{
				g_bAutoOpenPrivateShop = TRUE;
				theHeroGame.GetPlayerMgr()->MoveRoleToPlayer(pPlayer, TRUE, 0, 0);
				return FALSE;
			}
            CSystemStallage::Instance()->QuerryPlayerStallageRequest( pPlayer->GetID() );
			return TRUE;
		}
	}
	return FALSE;
}

//鼠标控制的入口
BOOL	CPlayerMgr::MouseControlFunction( float x, float y, int type, int xMouse, int yMouse, bool bPicked )
{
	guardfunc;
	switch (type)
	{
	case WM_LBUTTONUP:
		{
			if ( CheckPrivateShop( xMouse, yMouse ) == TRUE )
			{
                if( g_b25DMouseLButtonDownOnTerrain )
                    g_b25DMouseLButtonDownOnTerrain = FALSE;

				return TRUE;
			}
			ControlLButUpProc( x, y, bPicked );
		}
		break;
	case WM_RBUTTONUP:
		ControlRButUpProc( xMouse, yMouse ); //右键处理
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			ControlLButDownProc( x, y, bPicked );
		}
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		ControlRButDownProc( xMouse, yMouse );
		break;
	}
	return TRUE;
	unguard;
}

BOOL CPlayerMgr::KeyboardKeyUpControlFunction(int type, BOOL bDxInput/*=FALSE*/)
{
	guardfunc;

	if( (!bDxInput && type == VK_SPACE ) || (bDxInput && type == DIK_SPACE ))
	{

	}
	else if( (!bDxInput && type == 'X') || (bDxInput && type == DIK_X) )
	{
		g_bKeyboardVK_XIsDown = FALSE;
	}

	return TRUE;
	unguard;
}

//----
//	客户端下达攻击目标到死的指令
//----
void CPlayerMgr::RoleAttackToDead(int tag_player_id, int x, int y, int skill_id, int skill_level)
{
	guardfunc;
	RoleAttack(tag_player_id, x, y, skill_id, skill_level);
	if( m_pMe )
		m_pMe->GetOperation()->bAttackToDeadFlag = true;
	unguard;
}
//----
//	客户端下达攻击的目标npc的指令
//----
void CPlayerMgr::RoleAttack(int tag_player_id, int x, int y, int skill_id, int skill_level,
							bool bAttackToDead,bool bHoldAttack )
{

	guardfunc;
	CPlayer*	pPlayer = NULL;
	pPlayer =  FindByID( tag_player_id );

	//技能的判定流程
	if( pPlayer )
		SetAttackTarget( pPlayer->GetID() );
	//
	if( m_pMe )
		m_pMe->AddOperationGotoAttackTarget( tag_player_id, x, y, skill_id, skill_level );
	unguard;
}

//主角使用技能
void CPlayerMgr::RoleUseSkill( int nTag_Player_ID, int x, int y, int nSkill_ID, int nSkill_Level )
{
	guardfunc;
	if( m_pMe )
		m_pMe->AddOperationUseSkill( nTag_Player_ID, x, y, nSkill_ID, nSkill_Level );
	unguard;
}

void	CPlayerMgr::RoleIdle(short x, short y)
{
	guardfunc;
	if( m_pMe )
		m_pMe->AddOperationIdle();
	unguard;
}
void	CPlayerMgr::RoleChangeDir(short x, short y)
{
	guardfunc;
	if( m_pMe )
		m_pMe->AddOperationChangeDir(x, y);
	unguard;
}

void	CPlayerMgr::ClearRoleGetRangeItem(void)
{
	guardfunc;
	if( m_pMe )
		if (SOperation::eOpMoveGetRangeItem == m_pMe->GetOperation()->dwType)
			RoleIdle(0, 0);
	unguard;
}
void	CPlayerMgr::RoleDropItem(short x, short y)
{
	guardfunc;
	if( m_pMe )
		m_pMe->AddOperationGotoDropItem(x, y);
	unguard;
}

//给npc控制的npc下达指令。作某个表情动作
void	CPlayerMgr::RoleDoAction(int ActionID)
{
	guardfunc;
	//
	if( m_pMe )
		m_pMe->AddOperationDoAction(ActionID);
	unguard;
}

BOOL    CPlayerMgr::AutoLockAttacker(int AttackerID)
{
	guardfunc;
	if( !GetMe() )
		return FALSE;
	if (GetMe()->GetID() == AttackerID)
	{
		return FALSE;
	}

	if (GetLockPlayerID() >= 0)
	{
		return FALSE;
	}

	SetLockNpc(AttackerID);
	//
	return TRUE;
	unguard;
}
//----
//	自动使用技能
//----
BOOL	CPlayerMgr::AutoSkillProc(void)
{
	guardfunc;
	if( !GetMe() )
		return FALSE;
	if (m_controldata.iUseSkill <= 0)
	{
		switch (GetMe()->GetProfession())
		{
			//战士
		case EArmType_Warrior:
			m_controldata.iUseSkill = ConstSkillId_NormalAttack_Combat;
			m_controldata.iUseSkillLevel = 0;
			break;
		case EArmType_Taoist:
			m_controldata.iUseSkill = ConstSkillId_NormalAttack_Combat;
			m_controldata.iUseSkillLevel = 0;
			break;
		case EArmType_Assassin:
			m_controldata.iUseSkill = ConstSkillId_NormalAttack_Combat;
			m_controldata.iUseSkillLevel = 0;
			break;
			//魔法师
		case EArmType_Mage:
			m_controldata.iUseSkill = ConstSkillId_NormalAttack_Combat;
			m_controldata.iUseSkillLevel = 0;
			break;
			/*	case Profession_ChurchMan:
			m_controldata.iUseSkill = const_ustNormalAttack4;
			m_controldata.iUseSkillLevel = 0;
			break;*/
		case EArmType_Hunter:
			m_controldata.iUseSkill = ConstSkillId_NormalAttack_Combat;
			m_controldata.iUseSkillLevel = 0;
			break;
			//case Profession_Beginner:
		default:
			m_controldata.iUseSkill = ConstSkillId_NormalAttack_Combat;
			m_controldata.iUseSkillLevel = 0;
			break;
		}
		m_controldata.iUseSkill = ConstSkillId_NormalAttack_Combat;
	}
	return TRUE;
	unguard;
}

//键盘控制接入口
BOOL CPlayerMgr::KeyboardControlFunction(int type, BOOL bDxInput/*=FALSE*/)
{
	guardfunc;

	if( (!bDxInput && type == g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_autoRun))
		|| (bDxInput && type == g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_autoRun)))
	{
		if( g_bMouseMoveMode )
		{
			g_bAutoRunForward = FALSE;
		}
		else
		{
			g_bAutoRunForward = !g_bAutoRunForward;
		}
	}
	else if( (!bDxInput && type == g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_openAreaMap))
		|| (bDxInput && type == g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_openAreaMap)) )
	{

		s_CUI_ID_FRAME_AllNpcList.SetVisable( !s_CUI_ID_FRAME_AllNpcList.IsVisable() );
		s_CUI_ID_FRAME_AllNpcList.init();
	}
	else if ( (!bDxInput && type == g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_openBigMap))
		|| (bDxInput && type == g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_openBigMap)) )
	{
		s_CUI_ID_FRAME_WorldMap.SetVisable(!s_CUI_ID_FRAME_WorldMap.IsVisable());
	}
	else if ((!bDxInput && type == g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_ShowPlayer))
        || (bDxInput && type == g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_ShowPlayer)))
	{
        TogglePlayerRenderPriority();
	}
	

	else if( (!bDxInput && type == 'X') || (bDxInput && type == DIK_X) )
	{
		if( !g_bKeyboardVK_XIsDown )
		{
			g_bKeyboardVK_XIsDown = TRUE;
			if( m_pMe && !m_pMe->IsJumping() )	// 跳跃状态下不让切战斗姿态
			{
				if( m_pMe->HasFightFlag(eFighting) )
				{
					// 战斗中下不让收刀
				}
				else if( m_pMe->CanScabbard() )
				{
                    BOOL bCanScabbard = FALSE;
                    if( m_pMe->IsMounting() )
                    {
                        if( m_pMe->IsHaveWeapon() )
                        {
                            // 是否装备着旗子
                            if( m_pMe->GetProfession() == EArmType_Taoist && IsFlagModel(m_pMe->GetWeaponModelID()) )
                            {
                                // 举旗
                                if( !m_pMe->GetLiftFlagStatus() )
                                {
                                    m_pMe->SetLiftFlagStatus(1);
                                    m_pMe->SwitchLiftFlagAnim();
                                    // 广播给其他玩家
                                    SendDrawWeapon();
                                }
                                else    // 收旗
                                {
                                    m_pMe->SetLiftFlagStatus(0);
									if( m_pMe->GetAnim() )
										m_pMe->GetAnim()->ForceCurrAnimLoopTime(-1,TRUE);
                                    // 广播给其他玩家
                                    SendDrawInWeapon();
                                }
                            }
                        }
                    }
				}
			}
		}
	}
	return TRUE;
	unguard;
}

//----
//清除自动控制的一些标志
//----
BOOL    CPlayerMgr::AutoControlClear(void)
{
	guardfunc;
	m_controldata.LockNpcID = -1;
	m_controldata.bLeftDownFlag = FALSE;
	m_controldata.bRightDownFlag = FALSE;
	m_controldata.bAutoProcFlag = FALSE;
	m_controldata.dwAutoProcTime = 0;
	m_controldata.dwAutoPressTime = 0;
	//
	if (NULL != m_pMe)
		m_pMe->AddOperationIdle();
	//
	return TRUE;
	unguard;
}

void CPlayerMgr::UseSpecialSkill()
{
	guardfunc;
	if( thePlayerRole.CanUseSpecialSkill() )
	{
		MsgUseSpecialSkill msg;
		if( m_pMe )
			msg.header.stID = m_pMe->GetID();

		if( GettheNetworkInput().SendMsg(&msg) == -1 )
		{

		}
	}
	else
	{
		ReadytoUseSpecialSkill();
	}
	unguard;
}

void CPlayerMgr::ReadytoUseSpecialSkill()
{
	guardfunc;
	if( !m_pMe )
		return;
	m_pMe->StopMoving();

	MsgReadytoUseSpecialSkill msg;

	msg.header.stID = m_pMe->GetID();

	if( GettheNetworkInput().SendMsg(&msg) == -1 )
	{

	}
	unguard;
}

bool CPlayerMgr::MoveRoleTo( float x, float y, bool bNeedShowTargetPoint ,bool bSync, bool bHideTargetPoint,bool bUseZ )
{
	guardfunc;
	s_CUI_ID_FRAME_AutoAttackSet.EndAutoAttack();//zhuxincong 8.29 2012 寻路过去后 就停止挂机

	if(m_SkillBufTargetID != -1)
		m_SkillBufTargetID = -1;  //lyh移动到一个目标点时 ，如果上一次有目标 则清空，不然寻路走的逻辑出错


	if (!bSync&& ProcessShift(x, y))
	{
		return false;
	}
	if( !m_pMe )
		return false;

	g_vTheRoleTargetPos.x = x;
	g_vTheRoleTargetPos.y = y;
	g_vTheRoleTargetPos.z = 0;
	g_bTheRoleMoveToTargetPos = TRUE;
	m_pMe->SetMoving( TRUE );

	bool bRet = m_pMe->CalcRoleMovePath(g_vTheRoleTargetPos,bSync);
	g_bTheRoleCountermarch = FALSE;

	if( bNeedShowTargetPoint )
	{
		CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( g_nTargetPointEffectID );
		if( pModelEffect )
		{
			pModelEffect->m_dwBornTime = HQ_TimeGetTime();
			int nNum = pModelEffect->m_nNumInstance;

			for( int nInst = 0; nInst < nNum; nInst++ )
			{
				CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

				if( !pInstance )
					continue;

				pInstance->dwBornTime = HQ_TimeGetTime() + pInstance->fDelay;
				pInstance->bVisible = true;
			}
		}

		CCharEffectContainer* pTargetPointEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nTargetPointEffectContainerID );
		if( pTargetPointEffectContainer )
		{
			float fEffectHelperZ = 0;
			IEffectHelper* pEffectHelper = NULL;

			{
				BOOL bInFloor = FALSE;
				float fFromZ = WORLD_HEIGHT;
				if (bUseZ)
				{
					fFromZ = g_PickedZFromMouse + 1.0;
				}
				fEffectHelperZ = SwGlobal::GetWorldPicker()->GetZByXY( fFromZ,  x, y, 0 ,&bInFloor);

				CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
				CWorldChunk* pChunk = pTile->GetChunkFromPos(x, y);

				if( pChunk )
				{
					if( pChunk->GetLiquidHeight() > fEffectHelperZ )
					{
						fEffectHelperZ =  pChunk->GetLiquidHeight();
					}
				}
			}

			pEffectHelper = pTargetPointEffectContainer->GetEffectHelper( eEffectBindPart_Body );
			pEffectHelper->SetPos( x, y, fEffectHelperZ );
		}
		s_CUI_ID_FRAME_AllNpcList.SetSelectedPos(x,y);
	}
	else if( bHideTargetPoint )
	{
		HideTargetPointEffect();
	}
	return bRet;
	unguard;
}

void CPlayerMgr::HideTargetPointEffect()
{
	CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( g_nTargetPointEffectID );
	if( pModelEffect )
	{
		int nNum = pModelEffect->m_nNumInstance;
		for( int nInst = 0; nInst < nNum; nInst++ )
		{
			CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );
			if( !pInstance )
				continue;

			if( pInstance->bVisible )
			{
				pInstance->bVisible = false;
				pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
			}
		}
	}
}
// 移动主角到目标
void CPlayerMgr::MoveRoleToPlayer( CPlayer* pTargetPlayer, BOOL bClose /* = TRUE */, float fCorrect /* = 0.0f  */, BOOL bPick/*=FALSE*/, BOOL bInRuning/*=FALSE*/, BOOL bCalibrate/* = FALSE*/ )
{
	guardfunc;
	if( !m_pMe )
		return;

	//lyh++duorenzuoji //多人坐骑下 非驾驶员不能释放技能
	if(m_pMe->IsMultiMounting() && 
		m_pMe->GetCarrierPlayerID() != m_pMe->GetID())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotDoIt ) );
		return ;
	}

	float fXOff = 0;
	float fYOff = 0;
	float fDist = 0;
	float f = 0;
	float fRange = 0;
	float fAttackRange = 0;

	fXOff = pTargetPlayer->GetPos().x - m_pMe->GetPos().x;
	fYOff = pTargetPlayer->GetPos().y - m_pMe->GetPos().y;
	fDist = sqrtf( fXOff*fXOff + fYOff*fYOff );

	fRange += pTargetPlayer->GetBodyLengthSize();
	if( !bPick )
	{
		if( !bClose )
		{
			fRange += m_pMe->GetBodyLengthSize();
		}
	}

	if( !bClose )
	{
		fRange += m_pMe->GetWeaponAttackRange();
	}

	if( bCalibrate ) // 缩小判断范围，避免与服务器不同步
	{
		fRange -= pTargetPlayer->GetBodyLengthSize();
		fRange -= 1.f;
	}

	fAttackRange = m_pMe->GetWeaponAttackRange() + 1.f;
	if( fAttackRange < 2.f )
		fAttackRange = 2.f;

	float fDir = atan2f(fYOff,fXOff);
	m_pMe->SetLowerDir( fDir );
	m_pMe->SetDir(fDir);

	if( fDist > fRange )
	{
		f = fRange/fDist;

		static D3DXVECTOR3 lVector;
		D3DXVECTOR3* pTargetPos = &lVector;
		if (!bInRuning)
		{
			pTargetPos = &g_vTheRoleTargetPos; 
		}
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pTargetPlayer->GetNpcID());
		if (pInfo && pInfo->_bNpc && pInfo->_bPFPossible)
		{
			pTargetPos->x = pInfo->_pfMapX;
			pTargetPos->y = pInfo->_pfMapY;
		}
		else
		{
			pTargetPos->x = m_pMe->GetPos().x + fXOff*((fDist-fRange+fCorrect)/fDist);
			pTargetPos->y = m_pMe->GetPos().y + fYOff*((fDist-fRange+fCorrect)/fDist);
		}
		pTargetPos->z = 0;
		g_vTheRoleAttackTargetPos.x = pTargetPlayer->GetPos().x;
		g_vTheRoleAttackTargetPos.y = pTargetPlayer->GetPos().y;
		g_vTheRoleAttackTargetPos.z = 0;
		g_bTheRoleMoveToTargetPos = TRUE;
		m_pMe->SetMoving( TRUE );
		m_pMe->CalcRoleMovePath(*pTargetPos,false);
		m_pMe->SetActionTarget(pTargetPlayer->GetID());
		g_bTheRoleCountermarch = FALSE;

		HideTargetPointEffect();

		if( fDist < fAttackRange && g_nRoleCommonAttackStatus == CAS_NEED_AUTO_ATTACK )
		{
			//发消息通知服务器，攻击锁定的目标
			MsgAttackLockTarget	msg;

			if( GettheNetworkInput().SendMsg(&msg) == -1 )
			{

			}
			g_nRoleCommonAttackStatus = CAS_ATTACK_AGAIN_WHEN_FAILED;
		}
		return;
	}
	else
	{
		if( g_nRoleCommonAttackStatus == CAS_NEED_AUTO_ATTACK )
		{

			//发消息通知服务器，攻击锁定的目标
			MsgAttackLockTarget	msg;

			if( GettheNetworkInput().SendMsg(&msg) == -1 )
			{

			}
			g_nRoleCommonAttackStatus = CAS_ATTACK_AGAIN_WHEN_FAILED;
			if (GetMe() && GetMe()->IsMounting() && GetMe()->GetAutoDismount()&&!GetMe()->IsGoudaOperaMode())
			{
				int nSkillID = GetNormalAttackByProfession( GetMe()->GetProfession() );
				ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(nSkillID, 1);
				GetMe()->AutoDisMount(pSkill);
			}
		}
		// 采集
		if( pTargetPlayer->IsCollection())
		{
			if( m_pMe->HasFightFlag(eFighting) )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotLoot_InFight ) );
			}
			/*else if( m_pMe->IsMounting() )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotLoot_WhenMounting ) );
			}*/
			else if( pTargetPlayer->GetMonsterType() == eMT_Mine )
			{
				theHeroGame.GetPlayerMgr()->DisDrome();
				SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(ItemDefine::eCSI_CaiKuang);
				if( pCharSkill && pCharSkill->bAvailable)
				{
					// 使用和采集物相同等级的技能采集
					int iSkillLevel = pCharSkill->stSkillLevel;
					if( pCharSkill->stSkillLevel > pTargetPlayer->GetLevel() )
						iSkillLevel = pTargetPlayer->GetLevel();
					ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_CaiKuang, iSkillLevel );
					if( g_bMouseMoveMode )
						m_pMe->SetMoving( FALSE );
					m_pMe->TryUseSkill( pTargetPlayer, pSkill );
				}
				else
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_NoSkillForMine ) );
				}
			}
			else if( pTargetPlayer->GetMonsterType() == eMT_Herb )
			{
				theHeroGame.GetPlayerMgr()->DisDrome();
				SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(ItemDefine::eCSI_CaiYao);
				if( pCharSkill && pCharSkill->bAvailable)
				{
					// 使用和采集物相同等级的技能采集
					int iSkillLevel = pCharSkill->stSkillLevel;
					if( pCharSkill->stSkillLevel > pTargetPlayer->GetLevel() )
						iSkillLevel = pTargetPlayer->GetLevel();
					ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_CaiYao, iSkillLevel );
					if( g_bMouseMoveMode )
						m_pMe->SetMoving( FALSE );
					m_pMe->TryUseSkill( pTargetPlayer, pSkill );
				}
				else
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_NoSkillForHerb ) );
				}
			}
            // 增加捕虫         added by zhuomeng.hu		[11/9/2010]
            else if( pTargetPlayer->GetMonsterType() == eMT_Insect )
            {
				theHeroGame.GetPlayerMgr()->DisDrome();
                SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_BuChong );
                if( pCharSkill && pCharSkill->bAvailable)
                {
                    // 使用和采集物相同等级的技能采集
                    int iSkillLevel = pCharSkill->stSkillLevel;
                    if( pCharSkill->stSkillLevel > pTargetPlayer->GetLevel() )
                        iSkillLevel = pTargetPlayer->GetLevel();
                    ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_BuChong, iSkillLevel );
                    if( g_bMouseMoveMode )
                        m_pMe->SetMoving( FALSE );
                    m_pMe->TryUseSkill( pTargetPlayer, pSkill );
                }
                else
                {
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_NoSkillForCatch ) );
                }
            }
			else if( pTargetPlayer->GetMonsterType() == eMT_Treasure )
			{
				theHeroGame.GetPlayerMgr()->DisDrome();
				if( thePlayerRole.IsSkillCanUse( ItemDefine::eCSI_Treasure, 1 ) )
				{
					ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_Treasure, 1 );
					if( g_bMouseMoveMode )
						m_pMe->SetMoving( FALSE );
					m_pMe->TryUseSkill( pTargetPlayer, pSkill );
				}
			}
            // 捕马
			else if( pTargetPlayer->GetMonsterType() == eMT_Mount )
			{
				theHeroGame.GetPlayerMgr()->DisDrome();
				if( thePlayerRole.IsSkillCanUse( ItemDefine::eCSI_BuZhuo, 1 ) )
				{
					ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_BuZhuo, 1 );
					if( g_bMouseMoveMode )
						m_pMe->SetMoving( FALSE );
					m_pMe->TryUseSkill( pTargetPlayer, pSkill );
				}
				else
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_NoSkillForCatch ) );
				}
			}
		}
		if( g_bMouseMoveMode )
			m_pMe->SetMoving( FALSE );
	}

	unguard;
}

//
void CPlayerMgr::TurnRoleTo( CPlayer* pTargetPlayer )
{
	guardfunc;
	if( !m_pMe )
		return;
	if(pTargetPlayer &&  pTargetPlayer != m_pMe && m_pMe->m_cFightStatus.IsCanMove() )
	{
		D3DXVECTOR3 vDir = D3DXVECTOR3( 0,0,0 );

		vDir.x = pTargetPlayer->GetPos().x - m_pMe->GetPos().x;
		vDir.y = pTargetPlayer->GetPos().y - m_pMe->GetPos().y;
		D3DXVec3Normalize( &vDir, &vDir );
		m_pMe->SetCurDir( vDir );

		float fDir = atan2f(vDir.y, vDir.x);
		m_pMe->SetLowerDir(fDir);
		m_pMe->SetDir(fDir);
		m_pMe->SetCurDir(fDir);
        if( getwsCamera()->GetLock45DegreeCameraMode() )
            m_pMe->SetForceTurnRole(TRUE);
        
        SetTurnRoleToCamera(FALSE);
	}
	unguard;
}

void CPlayerMgr::UseRecordSkillAttackToDead(void)
{
	guardfunc;
	RoleAttackToDead(m_controldata.LockNpcID, 0, 0, GetCurUseSkill(), GetCurUseSkillLevel());
	//
	unguard;
}
void CPlayerMgr::UseRecordSkill(void)
{
	guardfunc;
	RoleAttack(m_controldata.LockNpcID, 0, 0, GetCurUseSkill(), GetCurUseSkillLevel());
	//
	unguard;
}

CPlayer* FindPlayerOfNextFar(std::vector<CPlayer*>& v, CPlayer* pSelPlayer)
{
	CPlayer* pLockPlayer = NULL;
	for( int nPlayer = 0; nPlayer < v.size(); nPlayer++ )
	{
		CPlayer* pPlayer = v[nPlayer];

		if(pPlayer && pPlayer->HaveMaster() && !gCfg.GetIsOpenPetAtter())
			continue;

		if( pPlayer->GetDistanceToRole() >= pSelPlayer->GetDistanceToRole() && pSelPlayer != pPlayer)
		{
			if( pLockPlayer )
			{
				if( pPlayer->GetDistanceToRole() <= pLockPlayer->GetDistanceToRole() && pLockPlayer != pPlayer)
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
	return pLockPlayer;
}

CPlayer* FindNearestPlayer(std::vector<CPlayer*>& v)
{
	CPlayer* pLockPlayer = NULL;
	if (v.size() > 0)
	{
		/*pLockPlayer = v[0];*/

		for( int nPlayer = 0; nPlayer < v.size(); nPlayer++ )
		{
			CPlayer* pPlayer = v[nPlayer];

			if (!pLockPlayer)
			{
				pLockPlayer = pPlayer;
			}

			if(pPlayer && pPlayer->HaveMaster() && !gCfg.GetIsOpenPetAtter())
				continue;

			//if( GetMonsterType() == eMT_IllusionMonster ) 镖车类型判断

			if( pPlayer->GetDistanceToRole() <= pLockPlayer->GetDistanceToRole() && pLockPlayer != pPlayer)
			{
				pLockPlayer = pPlayer;
			}
		}
	}

	if (pLockPlayer)
	{
		if(pLockPlayer->HaveMaster() && !gCfg.GetIsOpenPetAtter())
			return NULL;
	}
	return pLockPlayer;
}

void CPlayerMgr::TabSelectPlayer()
{
	guardfunc;
	if( !m_pMe )
		return;
	if( m_pMe->IsDead() )
		return;

	Frustum frustum;

	frustum.Build( *(MeMatrix*)&getwsCamera()->GetMeCamera()->GetViewMatrix(),
			*(MeMatrix*)&getwsCamera()->GetMeCamera()->GetProjMatrix() );


	// 设置以玩家自身的为观察点的Frustum
	static float adjustLookAtDist = 1.0f;
	Frustum frustumSelectArea;
	CD3DCamera tempCamera;
	D3DXVECTOR3 vUp = D3DXVECTOR3(0, 0, 1);
	D3DXVECTOR3 vDir = getwsCamera()->GetMeCamera()->GetViewDir();
	vDir.z = 0;
	D3DXVECTOR3 vEyePos = GetMe()->GetPos() - vDir * gCfg.m_fTabFrutomToEyeDist;
	D3DXVECTOR3 vLookAt = GetMe()->GetPos() + vDir * adjustLookAtDist;
	tempCamera.SetViewParams(vEyePos, vLookAt, vUp);
	tempCamera.SetProjParams(gCfg.m_fTabFrutomFov, 1, gCfg.m_fTabFrutomNearDist, gCfg.m_fTabFrutomFarDist);

	frustumSelectArea.Build( *(MeMatrix*)&tempCamera.GetViewMatrix(),
		*(MeMatrix*)&tempCamera.GetProjMatrix() );

	std::vector<CPlayer*> vectorSelPlayer;
	std::vector<CPlayer*> vec120DegreeOfFrontSelPlayer;

	std::map< GameObjectId, CPlayer* >::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); it++ )
	{
		CPlayer* pPlayer = it->second;
		if (!CanTab(pPlayer))
		{
			continue;
		}

		if( pPlayer->GetDistanceToRole() > gCfg.m_fNameShowDistance )
			continue;

		if( pPlayer->NeedRemove() )
			continue;

		if( pPlayer->GetCurRenderAlpha() < 0.0618f )
			continue;

		if( pPlayer->IsMonster() && pPlayer->GetMonsterType() == eMT_Collision )
			continue;

		if( pPlayer )
		{
			Box *pBox = pPlayer->GetWorldBBox();

			if( pBox )
			{
				if( pBox->v[4].z - pBox->v[0].z < 0.001f )
				{
					vectorSelPlayer.push_back( pPlayer );
				}

				if( frustum.Cull( *pBox ) )
				{
					if (frustumSelectArea.Cull( *pBox ))
					{
						vec120DegreeOfFrontSelPlayer.push_back(pPlayer);
					}
					else if (pPlayer->GetDistanceToRole() < gCfg.m_fTabBackRadius)
						vectorSelPlayer.push_back( pPlayer );
				}
			}
		}
	}

	if( vec120DegreeOfFrontSelPlayer.size() > 0 || vectorSelPlayer.size() > 0)
	{
		if( vec120DegreeOfFrontSelPlayer.size() == 1 && GetLockPlayerID() < 0 )
		{
			CPlayer* pSelPlayer =FindByID(vec120DegreeOfFrontSelPlayer[0]->GetID());
			if(pSelPlayer && pSelPlayer->HaveMaster() && !gCfg.GetIsOpenPetAtter())
				return;
			SetLockNpc( vec120DegreeOfFrontSelPlayer[0]->GetID() );
		}
		else if( vectorSelPlayer.size() == 1 && vec120DegreeOfFrontSelPlayer.size() == 0)
		{
			CPlayer* pSelPlayer =FindByID(vectorSelPlayer[0]->GetID());
			if(pSelPlayer && pSelPlayer->HaveMaster() && !gCfg.GetIsOpenPetAtter())
				return;
			SetLockNpc( vectorSelPlayer[0]->GetID() );
		}
		else
		{
			CPlayer* pLockPlayer = NULL;

			if( GetLockPlayerID() < 0 )
			{
				// 优先120度内的人物
				pLockPlayer = FindNearestPlayer(vec120DegreeOfFrontSelPlayer);
				
				if (!pLockPlayer)
					pLockPlayer = FindNearestPlayer(vectorSelPlayer);
			}
			else
			{
				CPlayer* pSelPlayer = NULL;
				bool is120ListPlayer = false;

				for( int nPlayer = 0; nPlayer < vec120DegreeOfFrontSelPlayer.size(); nPlayer++ )
				{
					if( GetLockPlayerID() == vec120DegreeOfFrontSelPlayer[nPlayer]->GetID() )
					{
						pSelPlayer = vec120DegreeOfFrontSelPlayer[nPlayer];
						is120ListPlayer = true;
					}
				}

				for( int nPlayer = 0; nPlayer < vectorSelPlayer.size(); nPlayer++ )
				{
					if( GetLockPlayerID() == vectorSelPlayer[nPlayer]->GetID() )
					{
						pSelPlayer = vectorSelPlayer[nPlayer];
					}
				}

				if( pSelPlayer )
				{
					if (is120ListPlayer)
					{
						pLockPlayer = FindPlayerOfNextFar(vec120DegreeOfFrontSelPlayer, pSelPlayer);

						if( !pLockPlayer )
							pLockPlayer = FindNearestPlayer(vectorSelPlayer);

						if( !pLockPlayer )
							pLockPlayer = FindNearestPlayer(vec120DegreeOfFrontSelPlayer);
					}
					else
					{
						pLockPlayer = FindPlayerOfNextFar(vectorSelPlayer, pSelPlayer);

						if( !pLockPlayer )
							pLockPlayer = FindNearestPlayer(vec120DegreeOfFrontSelPlayer);

						if( !pLockPlayer )
							pLockPlayer = FindNearestPlayer(vectorSelPlayer);
					}
				}
				else 
				{
					if( !pLockPlayer )
						pLockPlayer = FindNearestPlayer(vec120DegreeOfFrontSelPlayer);

					if( !pLockPlayer )
						pLockPlayer = FindNearestPlayer(vectorSelPlayer);
				}
			}

			if( pLockPlayer )
			{
// 				if(pLockPlayer->HaveMaster() && !gCfg.GetIsOpenPetAtter())
// 					return;
				SetLockNpc( pLockPlayer->GetID() );
			}
			pLockPlayer = NULL;
		}
	}
	unguard;
}

CPlayer* CPlayerMgr::FindNearItemNpc(void)
{
	guardfunc;
	if( !GetMe() )
		return NULL;

	std::map< GameObjectId, CPlayer* >::iterator it;
	std::vector <CPlayer *> vtPlayer; 

	FLOAT fDestX = 0.0f;
	FLOAT fDestY = 0.0f;
	FLOAT fMeX = 0.0f;
	FLOAT fMeY = 0.0f;

	FLOAT dX;
	FLOAT dY;
	FLOAT d;

	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); it++ )
	{
		CPlayer* pPlayer = it->second;
		if (pPlayer->IsItem() && pPlayer->m_bCanPick && pPlayer->IsItemDropDelayOver() )
		{
			fDestX = pPlayer->GetPos().x;
			fDestY = pPlayer->GetPos().y;

			fMeX = GetMe()->GetPos().x;
			fMeY = GetMe()->GetPos().y;

			dX = abs( fMeX - fDestX );
			dY = abs( fMeY - fDestY );
			d =  sqrtf( (dX*dX+dY*dY) );
			if( d < 7*WORLD_CHUNKSIZE*WORLD_SCALE )
				vtPlayer.push_back( pPlayer );
		}
	}
	if( vtPlayer.size() <= 0 )
		return NULL;


	std::vector<FLOAT> vtDest;
	for( int i=0; i<vtPlayer.size(); i++ )
	{
		CPlayer *pItem = vtPlayer[i];
		fDestX = pItem->GetPos().x;
		fDestY = pItem->GetPos().y;

		fMeX = GetMe()->GetPos().x;
		fMeY = GetMe()->GetPos().y;

		dX = abs( fMeX - fDestX );
		dY = abs( fMeY - fDestY );
		d =  sqrtf( (dX*dX+dY*dY) );

		//
		{
			vtDest.push_back( d );
		}	

	}

	INT nNearstId = 0;
	if( vtDest.size() == 1 )
		return vtPlayer[0];
	FLOAT fMin = vtDest[0];
	for( int i = 1; i<vtDest.size(); i++ )
	{
		float fDist  =	vtDest[i];
		if( fDist < fMin )
		{
			fMin = fDist;
			nNearstId = i;
		}
	}
	return vtPlayer[nNearstId];
	unguard;
}


CPlayer* CPlayerMgr::FindItemNpc(void)
{
	guardfunc;
	std::map< GameObjectId, CPlayer* >::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); it++ )
	{
		CPlayer* pPlayer = it->second;
		if (pPlayer->IsItem())
		{
			return pPlayer;
		}
	}
	return NULL;
	unguard;
}

CPlayer* CPlayerMgr::FindNearItemNpc(int x, int y, int range)
{
	guardfunc;
	CPlayer* pRetPlayer = NULL;

	std::map< GameObjectId, CPlayer* >::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); it++ )
	{
		CPlayer* pPlayer = it->second;
		if (NULL != pPlayer)
		{
			if (pPlayer->IsItem())
			{
				int npc_x, npc_y;
				pPlayer->GetMapPos(npc_x, npc_y);
				if (abs(npc_x - x) + abs(npc_y - y) <= range)
				{
					if (NULL != pRetPlayer)
					{
						int ret_npc_x, ret_npc_y;
						pRetPlayer->GetMapPos(ret_npc_x, ret_npc_y);
						if ((abs(npc_x - x) + abs(npc_y - y)) < 
							(abs(ret_npc_x - x) + abs(ret_npc_y - y)))
							pRetPlayer = pPlayer;
					}
					else
					{
						pRetPlayer = pPlayer;
					}
				}
			}
		}
	}

	return pRetPlayer;
	unguard;
}

BOOL     CPlayerMgr::IsHaveItemHere(int x, int y)
{
	guardfunc;
	std::map< GameObjectId, CPlayer* >::iterator it;
	for( it = m_mapPlayers.begin(); it != m_mapPlayers.end(); it++ )
	{
		CPlayer* pPlayer = it->second;
		if (pPlayer->IsItem())
		{
			int map_x, map_y;
			pPlayer->GetMapPos(map_x, map_y);
			if ((map_x == x) && (map_y == y))
				return TRUE;
		}
	}

	return FALSE;
	unguard;
}

void CPlayerMgr::LockMe()
{
	guardfunc;
	if( !m_pMe )
		return;
	GameObjectId shID = m_pMe->GetID();
	m_showhp.nIDLockNpc = shID;	

	SetLockPlayerID(shID);

	// 设置目标信息
	s_CUI_ID_FRAME_Target.SetPlayer(shID);

	//没有锁定的目标需要清空，默认使用的技能
	if ( shID < 0 )
	{
		GetMe()->GetOperation()->skill.iSkillID = GetCurUseSkill();
		GetMe()->GetOperation()->skill.iSkillLevel = GetCurUseSkillLevel();
	}
	unguard;
}

void CPlayerMgr::SetMouseOver( GameObjectId nIDWho )
{
	guardfunc;
	CPlayer *pPlayer = FindByID( nIDWho );
	if( !pPlayer )
	{
		m_showhp.nIDMouseOver = -1;
		return;
	}
	switch( pPlayer->GetCharType() )
	{
	case Object_Player:
	case Object_Monster:	
		break;
	default:
		return;
	}
	CheckHPInfo( nIDWho );

	m_showhp.nIDMouseOver = nIDWho;
	unguard;
}

void CPlayerMgr::SetLockPlayerID(GameObjectId npc_id)
{
	guardfunc;

	//add by zmy, 在取消选中的时候不保持战斗姿势
	if ( npc_id == -1 )
	{
		if( m_pMe != NULL && m_pMe->HasFightFlag(eFighting) == false && m_pMe->IsFightPose() ) //这里只处理没进入战斗状态，但是有战斗姿态处理收刀
		{
			m_pMe->SetFightPose(FALSE);
			m_pMe->SwitchScabbardAnim();	//做收刀动作single_scabbard
		}
	}

    if( m_bUseSkillBuf && m_SkillBufTargetID > -1 && m_SkillBufTargetID == GetLockPlayerID() )
    {
        ClearSkillBuf();
        if( m_pMe && m_pMe->IsMoving() )
            m_pMe->StopMoving();
    }

	if ( m_controldata.LockNpcID != npc_id )
	{
		m_controldata.LockNpcID = npc_id;
		//发消息通知服务器，锁定目标
		MsgLockTarget msg;
		msg.stWho = npc_id;
		if( GettheNetworkInput().SendMsg(&msg) == -1 )
		{

		}
	}
	//
 	s_CUI_ID_FRAME_ActionUI.Process();
	unguard;
}

void  CPlayerMgr::RequestGetOnOtherPet( CPlayer* pPlayer )
{
	if (!pPlayer) return;
    if (!m_pMe) return;
 
	if( m_pMe == pPlayer )
	{
		return;
	}

	D3DXVECTOR3 PosMe = m_pMe->GetPos();
	D3DXVECTOR3 PosOther = pPlayer->GetPos();
	float len = D3DXVec3Length(&(PosOther - PosMe));

	


	if ( pPlayer )
	{
		if( pPlayer->IsMultiMounting() == true && m_pMe->IsMounting() == false )
		{

			if (len>4.f)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed,theXmlString.GetString( eText_InteractionFailed_TargetToFarAway ) );
				return;
			}
			//if ( thePlayerRole.IsTeamMember(pPlayer->GetName()) )
			//{
				//MsgReqGotOnDromeAck reqMsg;
				//reqMsg.type = MsgReqGotOnDromeAck::EOperateType::EOperateType_Agree;
				//reqMsg.driverId = pPlayer->GetID();
				//reqMsg.riderId = m_pMe->GetID();
				//GettheNetworkInput().SendMsg( &reqMsg );
				MsgReqGotOnDrome reqMsg;
				reqMsg.type = MsgReqGotOnDrome::EOperateType_Request;
				reqMsg.driverId = pPlayer->GetID();
				reqMsg.riderId = m_pMe->GetID();
				GettheNetworkInput().SendMsg( &reqMsg );
			//}
			//else
			//{
			//	//提示无法请求上车原因
			//	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SameTeamLimit), theXmlString.GetString(eTextPlayer_Faild), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
			//}
		}
		else if ( pPlayer->IsPlayer() && m_pMe->IsMultiMounting() ) //是玩家且自己在坐骑上则是邀请
		{
			if (len>4.f)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed,theXmlString.GetString( eText_InteractionFailed_TargetToFarAway ));
				return;
			}

			MsgReqGotOnDrome reqMsg;
			reqMsg.type = MsgReqGotOnDrome::EOperateType_Invite;
			reqMsg.driverId = m_pMe->GetID();
			reqMsg.riderId = pPlayer->GetID();
			GettheNetworkInput().SendMsg( &reqMsg );
			
		}
	}

}

void  CPlayerMgr::SetLockNpc(GameObjectId iIDLockNpc)
{
	guardfunc;
	guard( test1 );
	if( GetLockPlayerID() == iIDLockNpc )
	{
		return;
	}
	unguard;

	guard( test2 );
	g_bTheRoleAttackLockTarget = FALSE;
    g_bAutoPlayInteractionWithTarget = FALSE;
	g_bAutoOpenPrivateShop = FALSE;
	CheckHPInfo(iIDLockNpc);
	m_showhp.nIDLockNpc = iIDLockNpc;	
	SetLockPlayerID(iIDLockNpc);
	unguard;

	guard( test5 );
	// 设置目标信息
	s_CUI_ID_FRAME_Target.SetPlayer( iIDLockNpc );
#ifdef _DEBUG
	char szBuf[256];
	MeSprintf_s( szBuf, 256, "当前选中目标ID = %d.", iIDLockNpc );
	s_CUI_ChatInfoBox.AddInfo( szBuf, 0xffff0000);				
#endif //_DEBUG
	unguard;

	//没有锁定的目标需要清空，默认使用的技能
	if (iIDLockNpc < 0 && GetMe())
	{
		guard( test6 );
		GetMe()->GetOperation()->skill.iSkillID = GetCurUseSkill();
		GetMe()->GetOperation()->skill.iSkillLevel = GetCurUseSkillLevel();
		unguard;
	}
	unguard;
}

void CPlayerMgr::SetAttackTarget( GameObjectId nIDWho )
{
	guardfunc;
	CheckHPInfo( nIDWho );
	m_showhp.nIDAttackTarget = nIDWho;	
	unguard;
}

bool CPlayerMgr::DoJumpAction()
{
	guardfunc;
	if( !m_pMe )
		return false;

	// 如果开着个人商店则不让跳
	if( m_pMe->IsOpenPrivateShop() )
	{
		return false;
	}

	if(GetMe()->IsCarrierint())
		return false;

	if(GetMe()->IsUncontrolMoving() )
	{
		return false;
	}

	if( m_pMe->GetAnim() && m_pMe->GetAnim()->IsUpperBodyPlayingComAnim() )
	{
		return false;
	}

	if( m_pMe->IsCanOverIntonation())
		return false;

    // 是否变身为镖车
    if( m_pMe->m_cFightStatus.IsHaveStatus(ItemDefine::eCJS_StatusID1) || m_pMe->m_cFightStatus.IsHaveStatus(ItemDefine::eCJS_StatusID2) )
    {
        return false;
    }

	if( !g_bTheRoleJumping && !m_pMe->IsInWater() && m_pMe->m_cFightStatus.IsCanMove() && m_pMe->IsDropEnd() && m_pMe->IsCanJump() )
	{
		m_pMe->RoleSlipProcess();

		if( g_bTheRoleSlipJumping )
		{
			return false;
		}

		if( !m_pMe->IsInFloor() && g_dwLastFrameBeginTime < g_dwTheRoleSlipStartTime + 600 )
		{
			 return false;
		}

		D3DXVECTOR3 vStart;
		D3DXVECTOR3 vDir = D3DXVECTOR3(0,0,1);

		vStart.x = m_pMe->GetPos().x;
		vStart.y = m_pMe->GetPos().y;
		vStart.z = m_pMe->GetPos().z + m_pMe->GetPlayerHeight()/2;
		FLOAT fDistToCollision = 0.0f;

		thePlayerRole.GetDistToCollision( vStart, vDir, &fDistToCollision );
		if( fDistToCollision > 0.0f && fDistToCollision < 2.7f )
		{
			OutputDebugString( "撞到头了，不能跳" );
			return false;
		}

		g_bTheRoleJumping = TRUE;
		g_bTheRoleJumpingCountermarch = g_bTheRoleCountermarch;
		g_vTheRoleJumpingDir = g_vTheRoleTargetDir;
		g_fTheRoleJumpingRotate = g_fTheRoleRotateZCorrect + g_fTheRoleDirCorrect;
		g_dwTheRoleJumpTime = g_dwLastFrameBeginTime + 100;
		m_pMe->SetJumpingSpeed( m_pMe->GetMoveRate() );

		if( m_pMe->IsMounting() )
		{
			if( m_pMe->IsMoving() )
			{
				if( m_pMe->IsCountermarch() )
				{
					g_bTheRoleJumping = FALSE;
					g_dwTheRoleJumpingEndTime = HQ_TimeGetTime();
					g_vTheRoleJumpingDir = g_vTheRoleTargetDir;
					g_fTheRoleJumpingRotate = g_fTheRoleRotateZCorrect + g_fTheRoleDirCorrect;
					g_dwTheRoleJumpTime = g_dwLastFrameBeginTime + 100;
				}
			}
			else
			{
				g_bTheRoleJumping = FALSE;
				g_dwTheRoleJumpingEndTime = HQ_TimeGetTime();
				g_vTheRoleJumpingDir = g_vTheRoleTargetDir;
				g_fTheRoleJumpingRotate = g_fTheRoleRotateZCorrect + g_fTheRoleDirCorrect;
				g_dwTheRoleJumpTime = g_dwLastFrameBeginTime + 100;

				if( g_dwLastFrameBeginTime - g_dwStartMountNeighTime < 1300 )
				{
					return false;
				}
				g_dwStartMountNeighTime = g_dwLastFrameBeginTime;
			}
		}
		m_pMe->Jump();
        SendJumpMsg();
		return true;
	}
	else
	{
		return false;
	}
	unguard;
}

bool CPlayerMgr::cancelBehavior()
{
    if( GetLockPlayerID() >= 0 )
    {
        //s_CUI_ID_FRAME_NpcChatDialogBox.SetNpc(-1);
		//s_CUI_NpcTaskDialogBox.SetNpc(-1);
        SetLockNpc(-1);
        if( m_pMe && m_pMe->IsIntonating() )
        {
            Msg_IntonateInterrupt msg;
            GettheNetworkInput().SendMsg( &msg );
            OnMsgIntonateInterrupt();
        }
        g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
        return true;
	}
	s_CUI_ID_FRAME_Target.SetVisable(false);
    return s_CUI_ID_FRAME_Target.IsVisable();
}

void CPlayerMgr::SwitchScabbard()
{
	if(!m_pMe)
		return;

	if( m_pMe->IsJumping() )	// 跳跃状态下不让切战斗姿态
		return;
	
	if( m_pMe->HasFightFlag(eFighting) )
	{
		// 战斗中下不让收刀
	}
	else if( m_pMe->CanScabbard() )
	{
		BOOL bCanScabbard = FALSE;
		if( m_pMe->IsMounting() )
		{
			if( m_pMe->IsHaveWeapon() )
			{
				// 是否装备着旗子
				if( m_pMe->GetProfession() == EArmType_Warrior && IsFlagModel(m_pMe->GetWeaponModelID()) )
				{
					// 举旗
					if( !m_pMe->GetLiftFlagStatus() )
					{
						m_pMe->SetLiftFlagStatus(1);
						m_pMe->SwitchLiftFlagAnim();
						// 广播给其他玩家
						SendDrawWeapon();
					}
					else    // 收旗
					{
						m_pMe->SetLiftFlagStatus(0);
						if( m_pMe->GetAnim() )
							m_pMe->GetAnim()->ForceCurrAnimLoopTime(-1,TRUE);
						// 广播给其他玩家
						SendDrawInWeapon();
					}
				}
			}
		}
		else if( m_pMe->IsHaveWeapon() && !m_pMe->IsInWater() && !(m_pMe->GetSitStatus() && !m_pMe->GetSitInterrupt()) )
		{
			bCanScabbard = TRUE;
		}

		if( bCanScabbard )
		{
			if( m_pMe->IsFightPose() )
			{
				// 战斗姿态，收刀
				m_pMe->SetFightPose(FALSE);
				m_pMe->SwitchScabbardAnim();
				// 广播给其他玩家
				SendDrawInWeapon();
			}
			else
			{
				// 非战斗姿态，拔刀
				m_pMe->SetFightPose(TRUE);
				m_pMe->SwitchScabbardAnim();
				// 广播给其他玩家
				SendDrawWeapon();
			}
			// 打断吟唱
			if( m_pMe->IsIntonating() )
			{
				Msg_IntonateInterrupt msg;
				GettheNetworkInput().SendMsg( &msg );
				OnMsgIntonateInterrupt();
			}
		}
	}
}
