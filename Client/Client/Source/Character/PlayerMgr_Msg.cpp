#include <windows.h>
#include <Psapi.h>
#include <math.h> 
#include <assert.h>
#include <list>
#include <helper.h>
#include "Me3d\Include.h"
#include "player.h"
#include "playermgr.h"
#include "../Resource/Resource.h"
#include "GameMain.h"
#include "NetworkInput.h"
#include "Effect.h"
#include "Font3DManager.h"
#include "SoundConfig.h"
#include "PlayerRole.h"
#include "MultiThreadMexLoading.h"
#include "XinFaConfig.h"
#include "Me3d/PostProcess/PostProcessManager.h"
#include "PlayerAnimCtrl.h"
#include "itemdetail.h"
#include "Me3d/MoreAction.h"
#include "XmlStringLanguage.h"
#include "QuestManager.h"
#include "GlobalDef.h"
#include "FuncPerformanceLog.h"
#include "MeUi/UiManager.h"
#include "ui/UiTitle.h"
#include "ui/FiveXing.h"
#include "ui/Pack.h"
#include "ui/UIStorage.h"
#include "ui/MessageBox.h"
#include "ui/ChatInfoBox.h"
#include "ui/Shop.h"
#include "ui/LoadMap.h"
#include "ui/Target.h"
#include "ui/Group.h"
#include "ui/Group_Me.h"
#include "ui/PlayerPrivateShop.h"
#include "ui/GoldPlating.h"
#include "ui/LotteryGameUI.h"
#include "ui/Property.h"
#include "ui/Bargaining.h"
#include "ui/Compound.h"
#include "UI\SelectBox.h"
#include "ui/baseProperty.h"
#include "ui/Task.h"
#include "ui/TutorialBox.h"
#include "LotteryAwardExplainUI.h"
#include "UI\NpcChatDialogBox.h"
#include "ui/Main.h"
#include "ui/FriendDlg.h"
#include "ui/SelfRbtnMenu.h"
#include "ui/Group_Me.h"
#include "UI\PrivateShop.h"
#include "ui/Experience.h"
#include "ui/Team.h"
#include "AttackInfoMan.h"
#include "ProcessCharInfo.h"
#include "MeTerrain/SwDebug.h"
#include "SystemConfig.h"
#include "GlobalDef.h"
#include "ErrorLog.h"
#include "MeUi/MouseManager.h"
#include "ui\FriendDlg.h"
#include "ui\rbtnmenu.h"
#include "ui/LuckGameUI.h"
#include "MiniMap.h"
#include "ui/Progress.h"
#include "ShowScreenText.h"
#include "MeAudio/MeAudio.h"
#include "ui/topinfo.h"
#include "ui/Gang.h"
#include "ui/Guild_Create.h"
#include "ui/CodeCheck.h"
#include "ui/GuideTip2.h"
//#include "ui/Guild.h"
#include "ShopCenterSlk.h"
#include "PosChangePackage.h"
#include "EnterMySightPackage.h"
#include "AckEnterWorldPackage.h"
#include "ui/SeekEquip.h"
#include "ui/MiniMapUI.h"
#include "ui/Group_Me.h"
#include "ui/Team_Player.h"
#include "chatcheck.h"
#include "DuelTips.h"
#include "color_config.h"
#include "MotionBillBoard.h"
#include "ActionManager.h"
#include "UI/Pack_Ex.h"
#include "ui/escdlg.h"
#include "ui/chat_particular.h"
#include "Cfg.h"
// #include "event_timeable.h"
#include "ui/BullSystem.h"
#include"PlayerRole.h"
#include "Logger.h"
#include "TimeEx.h"
#include "WordParser.h"
#include "Sociality.h"
#include "script_manager.h"
#include "ui/exmain.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/SwPublicFunc.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "wsRender.h"
#include "ui/NpcTaskDialogBox.h"
#include "MeFont/MeFontSystem.h"
// #include "ui/ChatSystem.h"
#include "ui/SkillLearn.h"
#include "MeAudio/meaudio.h"
#include "ChatMessageMgr.h"
#include "GroupPanel_NearPlayer.h"
#include "ui/ExitGame.h"
#include "ui/SkillTree.h"
#include "MeUi/ExpressionManager.h"
#include "ui/PrivateShop.h"
#include "ui/Star.h"
#include "ui/AllNpcList.h"
#include "ui/Pet.h"
#include "TitleConfig.h"
#include "ui/MainMenu.h"
#include "ui/chat_list.h"
#include "ui/SeekPet.h"
#include "CrossMapPF.h"
#include "PathDirection.h"
#include "ui/PickUp.h"
#include "ui/DemandItem.h"
#include "Task_Track.h"
#include "ui/Protect.h"
#include "GameSetting.h"
#include "ui/NewSkillMain.h"
#include "ui/ShopCenter.h"
#include "ui/ShopChangePoint.h"
#include "IntroductionManager.h"
#include "logmgr.h"
#include "Speaker.h"
#include "ui/Decompound.h"
#include "ui/CharacterExp.h"
#include "ui/EspecialTask.h"
#include "ui/MoveStar.h"
//#include "ui/WebAward.h"
#include "ui/SpecialRepair.h"
#include "RegionMap.h"
#include "ui/EquipUpgrade.h"
#include "ui/FiveXingChange.h"
#include "ui/FiveXingUpdate.h"
#include "ui/SkillEquipUpdate.h"
#include "ui/SkillEquipChange.h"
#include "ui/EspecialTask2.h"
#include "ui/ShowScriptGif.h"
#include "../GameUI\AutoAttackSet.h"
#include "ui/OnlineAward2.h"
#include "ui/JoinFight.h"
#include "ui/FamilyTenet.h"
#include "WSModelEffect.h"
#include "../GameUI/PlayerRename.h"
#include "KillMonsterCountConfig.h"
#include "SuperPassword.h"
#include "SuperPasswordReset.h"
#include "SuperPasswordRegister.h"
#include "PointShop.h"
#include "BatchShop.h"
#include "GoldTrade.h"
#include "GoldTradeRegiste.h"
#include "TeamBattleRequest.h"
#include "TeamBattleResult.h"
#include "TeamBattleState.h"
#include "TeamBattleRule.h"
#include "TeamBattleShowTeamInfo.h"
#include "MoveStarUpgrade.h"
#include "StarMaterialUpgrade.h"
#include "../GameUI\MailReceive.h"
#include "../GameUI/MailMain.h"
#include "../GameUI/MailReceive2.h"
#include "Master.h"
#include "FiveXingDisplace.h"
#include "GivePresent.h"
#include "Login.h"
#include "ExpressionAction.h"
#include "IntensifyStar.h"
#include "Common.h"
#include "WealthProtect.h"
#include "OnlineReward.h"
#include "PreventWallow.h"
#include "GivePresentLogic.h"
#include "../GameUI/OnlineAward3.h"
#include "wsCamera.h"				//added by ZhuoMeng.Hu		[9/19/2010]
#include "Ui/Gang.h"
#include "SkillProduce.h"
#include "PetMore.h"
// 国家消息 added by ZhuoMeng.Hu		[9/1/2010]
#include "CountryMessage.h"
#include "Country.h"
#include "CountryBroadcast.h"
#include "CountryInput.h"
#include "CountryQuestPost.h"
#include "InfoTips.h"
#include "InfoList.h"
#include "CountryFunction.h"
#include "GameDefinePlayer.h"
#include "NpcTaskDialogBox.h"
#include "Mex2LoadReq.h"
#include <MeFoundation/MeLoopThreadMan.h>
#include "RelationMessage.h"
#include "PetMore.h"
#include "ProduceLearn.h"
#include "Ui/SearchTeacher.h"
#include "ui/Soul.h"
#include "ui/Hole.h"
#include "ui/Gem.h"
#include "ui/GemRemove.h"
#include "ui/GemReplace.h"
#include "Ui/Purple.h"
#include "Ui/Repurple.h"
#include "Ui/EquipCopy.h"
#include "Ui/EquipReturn.h"
#include "Ui/Symbol.h"
#include "Ui/Amulet.h"
#include "Ui/GemUp.h"
#include "Ui/GemMaterialUp.h"
#include "ui/GuildApply.h"
#include "GuildConfig.h"
#include "ui/ActivityTrack.h"
#include "PasswordMessage.h"
#include "BargainingMessage.h"
#include "Only.h"
#include "PetStorage.h"
#include "PetList.h"
#include "PetMain.h"
#include "CampBattleMessage.h"
#include "ui/GuildBattle.h"
#include "ui/GuildBattleEnter.h"
#include "ui/ScoreTip.h"
#include "StallMessage.h"
#include "SystemStallage.h"
#include "CountryBattleKillNum.h"
#include "PackItemEnableManager.h"
#include "../GameUI/ExitTip.h"
#include "Ui/KingBattleEnter.h"
#include "Ui/KingScoreTip.h"
#include "ui/PropertyDlg.h"
#include "Ui/IdentifyQuality.h"
#include "ui/SkillSpirit.h"
#include "ui/SkillLearn.h"
#include "StallQuerySystem.h"
#include "ui/SearchPrivateShop.h"
#include "ui/CorpsTask.h"
#include "ui/Editor.h"
#include "ui/FamilyCreate.h"
#include "ui/FamilyApply.h"
#include "ui/FamilyMessageBox.h"
#include "SuAnimal.h"
#include "SuAnimalMore.h"
#include "SuAnimalMain.h"
#include "SuAnimalCard.h"
#include "SuAnimalCardList.h"
#include "SuAnimalStudy.h"
#include "SuAnimalMaterialUp.h"
#include "SuAnimalUp.h"
#include "FamilyMessage.h"
#include "SystemFamily.h"
#include "ui/Target.h"
#include "ui/Achivement.h"
#include "TaliExercise.h"
#include "Talisman.h"
#include "TalismanRenovate.h"
#include "Gut.h"
#include "MovieManager.h"
#include "IntroductionManager.h"
#include "ui/Lens.h"
#include "ui/CarryMain.h"
#include "ui/SelectPet.h"
#include "ui/SeeBasePropertyBGFrame.h"
#include "WeatherEventManager.h"
#include "..\GameUI\zhujiangbianshen.h"
#include "ItemHero.h"
#include "..\GameUI\AutoAttackSet.h"
#include "..\GameUI\ChangeCountry.h"
#include "..\GameUI\OnBiaoChe.h"
//#include "..\GameUI\ItemTrade.h"
#include "ui\ActivityList.h"
#include "../GameUI/FindTheRoad.h"
#include "Ui/ManualLevelUp.h"
#include "ui/ManualLevelUp.h"
#include "ui/Master.h"
#include "ui/UiTitle.h"
#include "ui/SeeSuAnimal.h"
#include "../GameUI/zhujiangUp.h"
#include "Ui/TransferStar.h"
#include "ui/jiebang.h"
#include "Ui/MountStrengthen.h"
#include "ui/OtherInfo.h"
#include "ui/CountryResource.h"
#include "ui/CountryQuest.h"
#include "ui/GuildBaseInfo.h"
#include "ui/GuildSQ.h"
#include "Ui/AskPresent.h"
#include "ui/KingScoreTipMin.h"
#include "ui/MoveCountry.h"
#include "ItemDetailConfig.h"
#include "GuildUnionBattleEnter.h"
#include "PlatformDefine.h"
#include "CampBattleGuildUnion.h"
#include "..\GameUI\RandAttribute.h"
#include "Ui/GuildCampBattle.h"
#include "ui/PetCompose.h"
#include "../GameUI/UseItem.h"
#include "../GameUI/Card.h"
#include "GuildBattleInfo.h"
#include "ui/GuildBattlResultInfo.h"
#include "SevenDays.h"
#include "../GameUI/SevenDaysButton.h"
#include "../GameUI/SevenDaysTask.h"
#include "ui/GuildChangeName.h"
#include "../GameUI/SelectChannel.h"
#include "../GameUI/ChannelInfo.h"
#include "EffectCharConfig.h"
#include "../GameUI/RankTitle.h"
#include "ui/QuestEntrust.h"
#include "QuestEntrustMessage.h"
#include "Ui/InputBox.h"
#include "PlayerRole.h"
#include "../GameUI/HuntingQuest.h"
#include "HuntingQuestConfig.h"
#include "GameBattleMessage.h"
#include "GameBattleDefine.h"
#include "ui/NewGuildGeneralBattleInfo.h"
#include "ui/GuildGeneralBattleList.h"
#include "MapConfig.h"
#include "ui/AddGuildGeneralBattle.h"
#include "ui/MountMoveStar.h"
#include "..//..//Source/GameUI/RankTitle.h"
#include "RankTitleConfig.h"
#include "ui/BasePropertyBGFrame.h"
#include "ui/LeaveExp.h"
#include "CSAuthMessage.h"
#ifdef NPGUARD
	//LYH NP
	#include <NP/NPGameLib.h>
	extern CNPGameLib *npgl;
#endif


//extern void ClearMexLoadingList();
float g_fNeedVerifyDistance = NeedVerifyDistance; // 需要纠正的距离

extern int	g_nPKFlagEffectID;
extern int	g_nPKFlagEffectContainerID;
extern		CActionManager		g_ActionManager;
extern		DWORD				g_dwLastFrameBeginTime;
extern      DWORD               g_dwLastFrameRealCostTime;

extern void	World2Screen( D3DXVECTOR3 vPos,int &x,int &y );

extern int PlayEffect ( const char* pEffectName, 
					   CPlayer* pSrcPlayer = NULL, 
					   float fScale = 0 ,
					   DWORD dwFlyTime = 0,
					   CPlayer* pDestPlayer = NULL,
					   int nSlot = 0
					   ,bool bCalDist = true);

extern char* GetFullFileName(const char* filename);

#define IS_MSG( type ) ( type == pMsg->GetType() )

extern int g_nCharacterDBID;
extern int g_nRoleCommonAttackStatus;

static short g_selectQuestId = -1;
extern BOOL g_bNextNotIntonate;
extern BOOL	g_bTheRoleAttackLockTarget;
//extern BOOL g_bAutoCounterattack;
extern BOOL g_bPackagePickAll;
extern GAME_STATE	g_GameState;
extern bool IsCollectSkill( unsigned short ustSkillID );
extern void	GetAngleTo2D( float fangle, float* fdirx, float* fdiry );
extern BOOL g_bIsShowSceneAndPlayer;
extern BOOL g_bCanUpdateQuest;
extern void GetMACAddressString( std::string* pStrMacString );
extern const char* GetMPTypeString( int nProfession );
extern bool isShowDisconnetMsg;


extern unsigned int g_dwServerNumber;
// bool ScriptShowQuestDlgCallbackFun( const int nSelectIndex, void *pData )
// {
// 	guardfunc;
// 	if (!pData)
// 	{
// 		return false;
// 	}
// 	ControlList::S_List *pItem = (ControlList::S_List*)pData;
// 
// 	// 判断能否请求脚本
// 	if( !theHeroGame.GetPlayerMgr() || !theHeroGame.GetPlayerMgr()->CanReqScript() )
// 		return false;
// 
// 	MsgScriptAckShowQuestDlg msg;
// 	msg.stQuestId = pItem->m_nID;
// 	g_selectQuestId = msg.stQuestId;
// 	GettheNetworkInput().SendMsg( &msg );
// 	return true;
// 	unguard;
// }

bool GuildReqInviteCallback( const char bPressYesButton, void *pData )
{
	guardfunc;
	MsgInviteJoinGuildReq* pInvite = (MsgInviteJoinGuildReq*)pData;
	MsgInviteJoinGuildAck query;
	query.nGuildID = pInvite->nGuildID;
	if( bPressYesButton )
	{
		query.bAgreeJoin = true;
	}
	else
	{
		query.bAgreeJoin = false;
	}
	GettheNetworkInput().SendMsg( &query );

	thePlayerRole.UpdateUI();
	return true;
	unguard;
}

//被邀请队员的回答
bool InquireInvitee( const char bPressYesButton, void *pData )
{
	guardfunc;
	MsgInquireInvitee * pMsgInquireInvitee = (MsgInquireInvitee *)pData;
	MsgAckInquireInvitee msg;
	if( bPressYesButton )
		msg.bAgree = MsgAckInquireInvitee::result_agree;
	else 
		msg.bAgree = MsgAckInquireInvitee::result_nonAgree;
	msg.dwReqID = pMsgInquireInvitee->dwReqID;
	msg.AssignMode = pMsgInquireInvitee->AssignMode;
	msg.AssignItemLevel = pMsgInquireInvitee->AssignItemLevel;
	GettheNetworkInput().SendMsg(&msg);

	return true;
	unguard;
}

BOOL IsFlagModel(int iModelID)
{
	if( iModelID >= ItemDefine::eFMI_Start && iModelID <= ItemDefine::eFMI_End )
		return TRUE;
	return FALSE;
}
#define INFO_LOG		"Info.log"

void CPlayerMgr::OnRetResetTime( Msg* pMsg )
{
	guardfunc;

	MsgRetResetTime *pRetMsg = (MsgRetResetTime*)pMsg;

	switch( pRetMsg->szMsg )
	{
	case MsgRetResetTime::eRet_Sucess:
		{
			if( pRetMsg->ustBagType == BT_NormalItemBag )
			{
				SCharItem* pCharItem = thePlayerRole.m_bag.GetCharItemFromIdx( pRetMsg->ustIdx );
				if( pCharItem )
				{
					char szBuffer [512] = {0};
					pCharItem->bCanUse = TRUE;
					pCharItem->itembaseinfo.n64UseTime = pRetMsg->n64UseTime;
					TimeEx kTime(pCharItem->itembaseinfo.n64UseTime);
					ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
					if( pItemDetail )
					{
						assert("name.h"&&0);
					}


				}

			}
		}
		break;
	case MsgRetResetTime::eRet_Faild_ForNotMoney:
		{
			assert(0 && "name.h");
		}
		break;
	case MsgRetResetTime::eRet_Faild_NotOverdue:
		{
			assert(0 && "name.h");
		}
		break;
	default:
		{
		}
		break;
	}

	return;
	unguard;
}
// 接收到所有游戏属性(?!)
void CPlayerMgr::OnMsgAckAllGameProperty        ( Msg* pMsg )
{
	guardfunc;
	unguard;
}

// 接收到切换地图消息
void CPlayerMgr::OnMsgChangeMap( Msg* pMsg )
{
	guardfunc;
	//切换地图
	if( !CanReceivePlayerMsg() )
		return;

	if( !m_pMe )
		return;
	CHECK_MSGLEN( pMsg, MsgChangeMap );
	MsgChangeMap *pChangeMap = (MsgChangeMap*)pMsg;   


	DebugLogout( "%s", "Begin DeletePlayersExceptMe" );
	DeletePlayersExceptMe();
	DebugLogout( "%s", "DeletePlayersExceptMe End" );

	//切换地图，清除动作队列
	//死人是不可能切换地图的
	DebugLogout( "%s", "Begin m_pMe->ClearActionQueue()" );
	m_pMe->ClearActionQueue();
	DebugLogout( "%s", "m_pMe->ClearActionQueue() End" );


	BOOL bNeedChangedMap = TRUE;

	if( theHeroGame.m_iLandID == pChangeMap->dwMapId )
	{
		bNeedChangedMap = FALSE;
	}

	// 关闭等待传送的MessageBox
	s_CUI_ID_FRAME_MessageBox.closeAll(false);

    s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
    s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(true);
    s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
    s_CUI_ID_FRAME_MessageBox.SetButVisableCancel(true);
	UiDrawer::StartFillFullScreen( 500, false );

	if( bNeedChangedMap )
	{
		// 加载地图时，设置不接收玩家进入/离开视野，和移动消息
		SetCanReceivePlayerMsg(FALSE);
		MeLoopThreadMan::Instance()->ClearLoadingList();

		//设置角色位置
		s_CUI_ID_FRAME_LoadMap.SetFloatX(pChangeMap->fX);
		s_CUI_ID_FRAME_LoadMap.SetFloatY(pChangeMap->fY);
		s_CUI_ID_FRAME_LoadMap.SetFloatZ( WORLD_HEIGHT );
		s_CUI_ID_FRAME_LoadMap.randomLoginMap();
		DebugLogout( "%s", "Begin UI_ID_FRAME_LoadMap::LoadMap" );
		s_CUI_ID_FRAME_LoadMap.LoadMap( pChangeMap->dwMapId,
			pChangeMap->new_map_x,
			pChangeMap->new_map_y,
			pChangeMap->fDirX
			,pChangeMap->fDirY
			,pChangeMap->nGameMapId );
		DebugLogout( "%s", "UI_ID_FRAME_LoadMap::LoadMap End" );

		// 清除没用的模型
		GetMexResMgr()->RemoveUnusedModelWhenChangeMap();

		/*if ( !s_CUI_ID_FRAME_SelectChannel.IsChannelSelected() )
			s_CUI_ID_FRAME_SelectChannel.ClearData();

		s_CUI_ID_FRAME_SelectChannel.SetSelectFlag( false );*/
	}

	if( !bNeedChangedMap )
	{
		PauseThread();

		CWorldTile* tile = CURRENTTILE;
		tile->SetRolePosition(pChangeMap->fX,pChangeMap->fY);
		tile->RefreshChunkLoadLevel(SwGlobal::GetRender()->GetFogProperty()->fFogFar,false);
		UnpauseThread();
		DebugLogout( "%s", "Begin m_pMe->JumpToMapPos2" );
		if( m_pMe->IsJumping() )
			m_pMe->StopJump();
		m_pMe->JumpToMapPos(pChangeMap->fX,pChangeMap->fY, WORLD_HEIGHT, pChangeMap->fDirX,pChangeMap->fDirY);
		DebugLogout( "%s", "m_pMe->JumpToMapPos2 End" );

		std::string macAddr;
		GetMACAddressString( &macAddr );

		MsgMapLoaded msg;
		msg.header.stID = GetMe()->GetID();
		strncpy(msg.szMacAddress, macAddr.c_str(), sizeof(msg.szMacAddress)-1);
		GettheNetworkInput().SendMsg( &msg,msg.GetLength() );
		LOG_MESSAGE(INFO_LOG, LOG_PRIORITY_INFO, "LogInfo: Send MsgMapLoaded\n");

		CrossMapPF::Instance()->Reset();
		CPathDirection::Instance()->Reset();
		s_CUI_ID_FRAME_MiniMap.SetAutoRuning(false);
		// 可以切换地图
		thePlayerRole.SetCanChangeMap(true);
		GetMe()->SetIntonating(0);
	}
	thePlayerRole.DuelProcess();
	DebugLogout( "%s", "================================================Flytomap End============================" );

		s_CUI_ID_FRAME_Speaker.SetVisable(false);

	//added by ZhuoMeng.Hu		[9/19/2010]
	if( getwsCamera() )
	{
		//if( getwsCamera()->Is45DegreeMode() )
		/*
		 * Author:	2012-8-31 wangshuai
		 * Desc: 	飞同一张地图时强制设置为2.5D视角
		 */
		getwsCamera()->Set45DegreeCameraMode( true );
	}

	unguard;
}

void CPlayerMgr::OnMsgAckFriendLeave(Msg * pMsg)
{
	guardfunc;

	unguard;
}

void CPlayerMgr::OnMsgAckGetPlayerInfo(Msg * pMsg)
{
	guardfunc;

	unguard;
}

extern bool g_bVipDisplay;
//-----------------------------------------------------------------------------

// 接收到聊天消息               
void CPlayerMgr::OnMsgChat( Msg* pMsg )
{
	guardfunc;
	if( !GetMe() )
	{
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	//聊天是变长消息
	//CHECK_MSGLEN( pMsg, MsgChat );
	MsgChat* msgChat = (MsgChat*)pMsg;
	CPlayer* pPlayer = FindByID( msgChat->header.stID );

	if (pPlayer != NULL && msgChat->chatHeader.stType == MsgChat::CHAT_TYPE_NORMAL)
	{
		if( pPlayer->IsMonster() || pPlayer->IsPlayer() || pPlayer->IsNpc())
		{
			std::wstring strTemp = Common::_tstring::toWideString( msgChat->szString );
// 			int nPos = strTemp.find( Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_Begin) ) );
			std::wstring strChat1;
// 			if( nPos != -1 )
// 				strChat1 = strTemp.substr(nPos + Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_Begin) ).length() );
// 			else
				strChat1 = strTemp;
			std::string strChatPlayer = Common::_tstring::toNarrowString( strChat1.c_str() );			
			char acChatTemp[500] = {0};
			MeSprintf_s( acChatTemp, sizeof(acChatTemp)-1, "%s", strChatPlayer.c_str() );
			std::string strChat = CChatCheck::getInstance()->CheckStringInLowMark( acChatTemp, '*');

			pPlayer->SetChatInfo( strChat );

			// 怪物和NPC聊天信息，不显示在聊天框里
			if(/*pPlayer->IsMonster() ||*/ pPlayer->IsNpc())
			{
				return;
			}
		}
	}

	// 判断玩家是否在黑名单中
	if( msgChat->chatHeader.dwSpeakPlayerDBID != ErrorUnsignedLongID /*&& msgChat->chatHeader.stType != MsgChat::CHAT_TYPE_HIGHSHOUT_VIP*/ 
		&& thePlayerRole.isFrdInBlackList(msgChat->chatHeader.dwSpeakPlayerDBID) )
		return;

	std::string szBull;
	char szStr[500] = {0};
	memcpy( szStr, msgChat->szString, min(msgChat->nStringLen, sizeof(szStr)) );

	//在接收端字符再次检验一便
// 	std::string strChat = szStr;
// 	std::string srcStr(szStr);
// 	std::string destStr1;
	std::string destStr2(szStr);
	if( msgChat->chatHeader.stType != MsgChat::CHAT_TYPE_PROGRAM_SYSTEM &&
		msgChat->chatHeader.stType != MsgChat::CHAT_TYPE_BULL )
	{
// 		size_t findPos = srcStr.find(szBull = theXmlString.GetString( eClient_Chat_Begin ));
// 		if (findPos != std::string::npos)
// 		{
// 			destStr1 = srcStr.substr(0, findPos);
// 			destStr2 = srcStr.substr(findPos);
// 		}

		destStr2 = CChatCheck::getInstance()->CheckStringInLowMark((char*)destStr2.c_str(), '*');

// 		strChat = /*destStr1 + */destStr2;
	}	
	memset( szStr, 0, sizeof(szStr) );
	strncpy(szStr, destStr2.c_str(), sizeof(szStr)-1 );

	// 世界聊天，则修改回调函数，用于判断至尊卡VIP用户
	bool bNeedResetCallback = false;
	if( MsgChat::CHAT_TYPE_HIGHSHOUT == msgChat->chatHeader.stType 
		|| MsgChat::CHAT_TYPE_HIGHSHOUT_VIP == msgChat->chatHeader.stType )
	{
		if( msgChat->chatHeader.speakerPlayerType == MsgChat::EST_ZhiZunHuangGuan && theHeroGame.GetPlayerMgr() )
		{
			// 修改回调函数
// 			ControlList::ms_pfGlobalParseText = S_IconInfoHero::GlobalParseText_HighShout;
			g_bVipDisplay = true; //yanli [2010-8-10] 
			bNeedResetCallback = true;

			// 获取玩家名称
			std::string ChatName;

			if(msgChat->header.stID == GetMyID()) 
			{
				ChatName = msgChat->chatHeader.szToName;
			}
			else
			{
				ChatName = msgChat->chatHeader.szSpeakName;
// 				std::string info = msgChat->szString;
// 				int pos = info.find(theXmlString.GetString(eClient_Chat_Begin));
// 				int nLeftLength = 0;
// 				if (pos != std::string::npos)
// 					ChatName = info.substr(nLeftLength, pos - nLeftLength);
			}
			theHeroGame.GetPlayerMgr()->PushVipPlayer(ChatName.c_str(), msgChat->header.stID);
		}
	}

	switch(msgChat->chatHeader.stType)
	{
	case MsgChat::CHAT_TYPE_NORMAL:	//普通聊天
		{
			guard(MsgChat::CHAT_TYPE_NORMAL);
			szBull = theXmlString.GetString( eText_Chat_6 );
			szBull += msgChat->chatHeader.szSpeakName;
			szBull += theXmlString.GetString( eClient_Chat_Head_End );
			szBull += szStr;

			if (pPlayer && pPlayer->IsMonster())
			{
				szBull = theXmlString.GetString( eChatType_Near );;
				szBull += " "; //+个空格好看点
				szBull += msgChat->chatHeader.szSpeakName;
				szBull += theXmlString.GetString( eClient_Chat_Begin );
				szBull += szStr;
			}

			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_NORMAL)
					, MsgChat::CHAT_TYPE_NORMAL, msgChat->chatHeader.szToName, 
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type, false, msgChat );
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_NORMAL)
					, MsgChat::CHAT_TYPE_NORMAL, msgChat->chatHeader.szToName, NULL, 0, 0, false, msgChat );
			}

			unguard;
			break;
		}
	case MsgChat::CHAT_TYPE_LEAGUE:	//同盟聊天
		{
			szBull = theXmlString.GetString( eText_Chat_Alignment );
			szBull += msgChat->chatHeader.szSpeakName;
			szBull += theXmlString.GetString( eClient_Chat_Head_End );
			szBull += szStr;

			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_LEAGUE)
					, MsgChat::CHAT_TYPE_LEAGUE, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type );
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_LEAGUE)
					, MsgChat::CHAT_TYPE_LEAGUE, msgChat->chatHeader.szToName );
			}
		}
		break;
	case MsgChat::CHAT_TYPE_GUILD:	//公会聊天
		{
			szBull = theXmlString.GetString( eText_Chat_3 );
			szBull += msgChat->chatHeader.szSpeakName;
			szBull += theXmlString.GetString( eClient_Chat_Head_End );
			szBull += szStr;

			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_GUILD)
					, MsgChat::CHAT_TYPE_GUILD, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt,msgChat->type );
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_GUILD)
					, MsgChat::CHAT_TYPE_GUILD, msgChat->chatHeader.szToName );
			}
		}
		break;
	case MsgChat::CHAT_TYPE_TERM:	//小队聊天
		{
			szBull = theXmlString.GetString( eText_Chat_2 );
			szBull += msgChat->chatHeader.szSpeakName;
			szBull += theXmlString.GetString( eClient_Chat_Head_End );
			szBull += szStr;

			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_TEAM)
					, MsgChat::CHAT_TYPE_TERM, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type);
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_TEAM)
					, MsgChat::CHAT_TYPE_TERM, msgChat->chatHeader.szToName );
			}

			s_CUI_Group.show_talktip( msgChat->szString, msgChat->header.stID );
		}
		break;
	case MsgChat::CHAT_TYPE_MS:
		{
			{
				std::string playerName;
				std::string ToName;
				std::string ChatName;



				if(msgChat->header.stID == GetMyID()) 
				{
					ToName = msgChat->chatHeader.szToName;
					playerName = GetMe()->GetName();
					ChatName = ToName;
				}
				else
				{
					ToName = GetMe()->GetName();
					playerName = msgChat->chatHeader.szSpeakName;
// 					std::string info = msgChat->szString;
// 					int pos = info.find(theXmlString.GetString(eClient_Chat_DuiNiShuo));
// 					int nLeftLength = 1;
// 					if (pos != std::string::npos)
// 						playerName = info.substr(nLeftLength, pos - nLeftLength);
					ChatName = playerName;
				}
				if (GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseAllMsg ))
				{
					return;
				}
				if (GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseStrangerMsg ))
				{
					if (!thePlayerRole.IsFriend(ChatName.c_str()))
					{
						return;
					}
				}
				if( thePlayerRole.isFrdInBlackList(ChatName.c_str()) )
				{
					return;
				}
				{
					// 播放短消息声音
					PlaySoundConfig( SoundConfig::EST_FriendMsg );
					chatMessageManage.AddChatMessage(playerName.c_str(),szStr, Color_Config.getColor(CC_CHAT_PERSONAL)
						, MsgChat::CHAT_TYPE_MS, (char*)ToName.c_str(),
						msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type);
					return;
				}
			}

		}
		break;
	case MsgChat::CHAT_TYPE_PRIVATE:	//私聊
		{
			std::string playerName;
			std::string ToName;
			std::string ChatName;


			szBull = theXmlString.GetString( eText_Chat_0 );

			if(msgChat->header.stID == GetMyID()) 
			{
				ToName = msgChat->chatHeader.szToName;
				playerName = GetMe()->GetName();
				ChatName = ToName;
				szBull += theXmlString.GetString( eClient_Chat_NiDui );
				szBull += ToName;
				szBull += theXmlString.GetString( eClient_Chat_Shuo );
			}
			else
			{
				ToName = GetMe()->GetName();
				playerName = msgChat->chatHeader.szSpeakName;

// 				std::string info = msgChat->szString;
// 				int pos = info.find(theXmlString.GetString(eClient_Chat_DuiNiShuo));
// 				int nLeftLength = 0;
// 				if (pos != std::string::npos)
// 					playerName = info.substr(nLeftLength, pos - nLeftLength);
				ChatName = playerName;
				szBull += theXmlString.GetString( eClient_Private_Begin );
				szBull += ChatName;
				szBull += theXmlString.GetString( eClient_Chat_DuiNiShuo );
			}
			if( thePlayerRole.isFrdInBlackList(ChatName.c_str()) )
			{
				return;
			}

			s_CUI_ChatInfoBox.SetPrivateName( ChatName.c_str() );
			szBull += szStr;

			chatMessageManage.AddChatMessage(playerName.c_str(),szStr, Color_Config.getColor(CC_CHAT_PERSONAL)
				, MsgChat::CHAT_TYPE_PRIVATE, (char*)ToName.c_str(),
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type);
			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo(szBull.c_str(), Color_Config.getColor(CC_CHAT_PERSONAL)
					, MsgChat::CHAT_TYPE_PRIVATE, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type, msgChat->bIsRreply );

			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo(szBull.c_str(), Color_Config.getColor(CC_CHAT_PERSONAL)
					, MsgChat::CHAT_TYPE_PRIVATE, msgChat->chatHeader.szToName, 0, 0, 0, msgChat->bIsRreply );
			}
		}
		break;
	case MsgChat::CHAT_TYPE_GAMEPROMPT:	//系统
		{
			int nIntroId = CIntroductionManager::Instance()->RetrieveIntroductionId(msgChat->szString);
			if (nIntroId == -1)
			{
				szBull = theXmlString.ParseAtString( msgChat->szString );

// 				szBull = theXmlString.GetString( eText_SystemBull );
				if( msgChat->nHyberItemCnt > 0 )
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_ChatSys, szBull, msgChat->chatHeader.szToName, 
						msgChat->szString + msgChat->nStringLen, msgChat->nHyberItemCnt, msgChat->type );
				}
				else
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_ChatSys, szBull );
				}
			}
			else
			{//新手引导
				CIntroductionManager::Instance()->ShowTip(nIntroId);
				return;	
			}			
		}
		break;
	case MsgChat::CHAT_TYPE_BULL:	//全服公告 -- 用于script
		{
			//szBull = theXmlString.GetString( eText_Bull );
			//szBull += msgChat->chatHeader.szSpeakName;
			//szBull += theXmlString.GetString( eClient_Chat_Begin );
			//szBull += szStr;
			szBull = theXmlString.GetString( eText_Bull );
			szBull += " ";//加个空格好看点 -,-
			szBull += szStr;

			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_BULL)
					, MsgChat::CHAT_TYPE_BULL, msgChat->chatHeader.szToName, 
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type);
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_BULL)
					, MsgChat::CHAT_TYPE_BULL );
			}
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Bull_Broadcast, szBull, 2 );
		}
		break;
	case MsgChat::CHAT_TYPE_PROGRAM_SYSTEM: // gm打的公告
		{
			//std::string strTarget = msgChat->szString;
			//std::vector<UiCallbackDataBase*> CallBackDataArr;
			//CallBackDataArr.clear();
			//NpcCoord::getInstance()->addNpcHyberForText(strTarget,NpcCoord::eMapId, CURRENTTILE->GetMapId(),&CallBackDataArr,false,true);
			//sprintf_s( msgChat->szString, dr_MaxChatString - 1, "%s", strTarget.c_str() );

			szBull = theXmlString.GetString( eText_SystemBull );
			szBull += " ";//加个空格好看点 -,-
			szBull += theXmlString.ParseAtString(msgChat->szString);
// 			szBull += szStr;

			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_SYSTEM)
					, MsgChat::CHAT_TYPE_PROGRAM_SYSTEM, msgChat->chatHeader.szToName, 
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type);
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_SYSTEM)
					, MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
			}
            //CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Bull_System, szBull, 2 );
		}
		break;
	case MsgChat::CHAT_TYPE_SHOUT:	//大喊
		{
			szBull = theXmlString.GetString( eText_Chat_4 );
			szBull += msgChat->chatHeader.szSpeakName;
			szBull += theXmlString.GetString( eClient_Chat_Head_End );
			szBull += szStr;
			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_HIGHSHOUT)
					, MsgChat::CHAT_TYPE_SHOUT, msgChat->chatHeader.szToName, 
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type);
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_HIGHSHOUT)
					, MsgChat::CHAT_TYPE_SHOUT, msgChat->chatHeader.szToName );
			}
		}
		break;
	case MsgChat::CHAT_TYPE_HIGHSHOUT://全服公告 -- 用于玩家
		{
			std::string ChatName;

			if(msgChat->header.stID == GetMyID()) 
			{
				ChatName = msgChat->chatHeader.szToName;
			}
			else
			{
				ChatName = msgChat->chatHeader.szSpeakName;
// 				std::string info = msgChat->szString;
// 				int pos = info.find(theXmlString.GetString(eClient_Chat_Begin));
// 				int nLeftLength = 0;
// 				if (pos != std::string::npos)
// 					ChatName = info.substr(nLeftLength, pos - nLeftLength);
			}
			if( thePlayerRole.isFrdInBlackList(ChatName.c_str()) )
			{
				return;
			}
			szBull = theXmlString.GetString( eText_Chat_5 );
// 			if (GetMe()/* && (GetMe()->GetRealCountry() != msgChat->chatHeader.uchSpeakCountry)*/)
// 			{
// 				std::string strCountry;
// 				strCountry = CountryFunction::GetCountryNameById(msgChat->chatHeader.uchSpeakCountry);
// 				szBull += theXmlString.GetString( eText_Chat_Spec_LeftMark );
// 				szBull += strCountry;
// 				szBull += theXmlString.GetString( eText_Chat_Spec_RightMark );
// 			}
			std::string strOfficial = CountryFunction::GetOfficialForChat(msgChat->chatHeader.uchSpeakerTitle);
			if (!strOfficial.empty())
			{
				std::string str = CountryFunction::GetCountryNameById(msgChat->chatHeader.uchSpeakCountry);
				char buf[128] = {0};
				sprintf_s(buf, sizeof(buf)-1, strOfficial.c_str(), str.c_str());

				szBull += buf;
			}
            szBull += theXmlString.GetString( eText_Chat_Spec_LeftMark );
			szBull += '~';
			szBull += msgChat->chatHeader.szSpeakName;
			szBull += theXmlString.GetString( eClient_Chat_Head_End );
			szBull += szStr;


			if (pPlayer && pPlayer->IsMonster()) //lyh++ 怪物在世界频道的说话
			{
				szBull = theXmlString.GetString( eText_Chat_5 );

				szBull += " ";
				szBull += msgChat->chatHeader.szSpeakName;
				szBull += theXmlString.GetString( eClient_Chat_Begin );
				szBull += szStr;
			}


			if( msgChat->nHyberItemCnt > 0 )
			{
				/*s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_HIGHSHOUT)
					, MsgChat::CHAT_TYPE_HIGHSHOUT, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type);*/

				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_HIGHSHOUT)
					, MsgChat::CHAT_TYPE_HIGHSHOUT, msgChat->chatHeader.szToName, 
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type, false, msgChat );

			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_HIGHSHOUT)
					, MsgChat::CHAT_TYPE_HIGHSHOUT, msgChat->chatHeader.szToName );
			}
		}
		break;
	case MsgChat::CHAT_TYPE_BULL_VIP:	//全服公告 -- 用于gm
		{
			szBull = theXmlString.GetString( eText_SystemBull );
			szBull += szStr;

			s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_SYSTEM)
				, MsgChat::CHAT_TYPE_BULL );
		}
		break;
	case MsgChat::CHAT_TYPE_SHOUT_VIP:	//大喊
		{
			szBull = theXmlString.GetString( eText_Chat_4 );
			szBull += szStr;
			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_XIAOLABA)
					, MsgChat::CHAT_TYPE_SHOUT, msgChat->chatHeader.szToName, 
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type);
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_XIAOLABA)
					, MsgChat::CHAT_TYPE_SHOUT, msgChat->chatHeader.szToName );
			}
		}
		break;
	case MsgChat::CHAT_TYPE_HIGHSHOUT_VIP://全服公告 -- 用于玩家
		{
			szBull = theXmlString.GetString( eChatType_XiaoLaBa );
			if (GetMe()/* && (GetMe()->GetRealCountry() != msgChat->chatHeader.uchSpeakCountry)*/)
			{
				if(msgChat->chatHeader.uchSpeakCountry != CountryDefine::Country_Init)
				{
					std::string strCountry = CountryFunction::GetCountryNameById(msgChat->chatHeader.uchSpeakCountry);
					szBull += theXmlString.GetString( eText_Chat_Spec_LeftMark );
					if (strCountry.length() > 0)
						szBull += strCountry;
					else
						szBull += theXmlString.GetString( eText_HIGHSHOUT_VIP_NoCountry );
					szBull += theXmlString.GetString( eText_Chat_Spec_RightMark );
				}
			}
			szBull += theXmlString.GetString( eText_Chat_Spec_LeftMark );
			szBull += '~';
			szBull += msgChat->chatHeader.szSpeakName;
			szBull += theXmlString.GetString( eClient_Chat_Head_End );
			szBull += szStr;
			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ID_FRAME_Speaker.AddInfo( szBull, Color_Config.getColor(CC_CHAT_XIAOLABA)
					, MsgChat::CHAT_TYPE_HIGHSHOUT_VIP, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type);
				//s_CUI_ID_FRAME_Speaker.AddInfo( szBull, Color_Config.getColor(CC_CHAT_XIAOLABA)
					/*, MsgChat::CHAT_TYPE_HIGHSHOUT_VIP, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type*/
			}
			else
			{
				/*s_CUI_ChatInfoBox.AddInfo( szBull, Color_Config.getColor(CC_CHAT_XIAOLABA)
					, MsgChat::CHAT_TYPE_HIGHSHOUT_VIP, msgChat->chatHeader.szToName );*/
				s_CUI_ID_FRAME_Speaker.AddInfo( szBull, Color_Config.getColor(CC_CHAT_XIAOLABA)
					/*, MsgChat::CHAT_TYPE_HIGHSHOUT_VIP, msgChat->chatHeader.szToName */);
			}
		}
		break;
	case MsgChat::CHAT_TYPE_BATTLE:	//阵营聊天
		{
			szBull = theXmlString.GetString( eText_Chat_ZhenYing );
			szBull += msgChat->chatHeader.szSpeakName;
			szBull += theXmlString.GetString( eClient_Chat_Head_End );
			szBull += szStr;

			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_ZHENYING)
					, MsgChat::CHAT_TYPE_BATTLE, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type );
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_ZHENYING)
					, MsgChat::CHAT_TYPE_BATTLE, msgChat->chatHeader.szToName );
			}
		}
		break; 
	case MsgChat::CHAT_TYPE_COUNTRY:	//国家聊天
		{
			szBull = theXmlString.GetString( eChatType_Country );
            std::string strOfficial = CountryFunction::GetCountryOfficialNameById(msgChat->chatHeader.uchSpeakerTitle);
			if(!strOfficial.empty())
			{
				std::string str = CountryFunction::GetCountryNameById(msgChat->chatHeader.uchSpeakCountry);
				str += "-";
				str += strOfficial;

				szBull += theXmlString.GetString( eText_Chat_Spec_LeftMark );
				szBull += str;
				szBull += theXmlString.GetString( eText_Chat_Spec_RightMark );
			}
			szBull += theXmlString.GetString( eText_Chat_Spec_LeftMark );
			szBull += "~";
			szBull += msgChat->chatHeader.szSpeakName;
			szBull += theXmlString.GetString( eClient_Chat_Head_End );
			szBull += szStr;

			if (pPlayer && pPlayer->IsMonster()) //lyh++ 怪物在国家频道的说话
			{
				szBull = theXmlString.GetString( eChatType_Country );

				szBull += " ";
				szBull += msgChat->chatHeader.szSpeakName;
				szBull += theXmlString.GetString( eClient_Chat_Begin );
				szBull += szStr;
			}

			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_COUNTRY)
					, MsgChat::CHAT_TYPE_COUNTRY, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type );
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_COUNTRY)
					, MsgChat::CHAT_TYPE_COUNTRY, msgChat->chatHeader.szToName );
			}
		}
		break;
	//lyh++ guanyuanpindao xiaoxi 
	case MsgChat::CHAT_TYPE_COUNTRYOFFICIAL:
		{
				szBull = theXmlString.GetString( eChatType_GuanYuan ); // 官员图标
				std::string strOfficial = CountryFunction::GetCountryOfficialNameById(msgChat->chatHeader.uchSpeakerTitle);
				if(!strOfficial.empty())
				{
					std::string str = CountryFunction::GetCountryNameById(msgChat->chatHeader.uchSpeakCountry);
					str += "-";
					str += strOfficial;

					szBull += theXmlString.GetString( eText_Chat_Spec_LeftMark );
					szBull += str;
					szBull += theXmlString.GetString( eText_Chat_Spec_RightMark );
				}
				szBull += theXmlString.GetString( eText_Chat_Spec_LeftMark );
				szBull += "~";
				szBull += msgChat->chatHeader.szSpeakName;
				szBull += theXmlString.GetString( eClient_Chat_Head_End );
				szBull += szStr;

				if( msgChat->nHyberItemCnt > 0 )
				{
					s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_Chat_ChatGuanYuan)
						, MsgChat::CHAT_TYPE_COUNTRYOFFICIAL, msgChat->chatHeader.szToName,
						msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type );
				}
				else
				{
					s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_Chat_ChatGuanYuan)
						, MsgChat::CHAT_TYPE_COUNTRYOFFICIAL, msgChat->chatHeader.szToName );
				}
			
		}
		break;
	case MsgChat::CHAT_TYPE_FAMILY:	//家族聊天
		{
			szBull = theXmlString.GetString( eChatType_Country );		//这个图标是可以配置的
			//std::string strOfficial = CountryFunction::GetCountryOfficialNameById(msgChat->chatHeader.uchSpeakerTitle);
			//if(!strOfficial.empty())
			//{
			//	szBull += theXmlString.GetString( eText_Chat_Spec_LeftMark );
			//	szBull += strOfficial;
			//	szBull += theXmlString.GetString( eText_Chat_Spec_RightMark );
			//}
			szBull += theXmlString.GetString( eText_Chat_Spec_LeftMark );
			szBull += "~";
			szBull += msgChat->chatHeader.szSpeakName;
			szBull += theXmlString.GetString( eClient_Chat_Head_End );
			szBull += szStr;

			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_COUNTRY)
					, MsgChat::CHAT_TYPE_FAMILY, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type );
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_COUNTRY)
					, MsgChat::CHAT_TYPE_FAMILY, msgChat->chatHeader.szToName );
			}
		}
		break;
	case MsgChat::CHAT_TYPE_PARTICAL1_VIP:
	case MsgChat::CHAT_TYPE_PARTICAL2_VIP:
	case MsgChat::CHAT_TYPE_PARTICAL3_VIP:
	case MsgChat::CHAT_TYPE_PARTICAL4_VIP:
	case MsgChat::CHAT_TYPE_PARTICAL5_VIP:
	case MsgChat::CHAT_TYPE_PARTICAL6_VIP:
	case MsgChat::CHAT_TYPE_PARTICAL7_VIP:
	case MsgChat::CHAT_TYPE_PARTICAL8_VIP:
	case MsgChat::CHAT_TYPE_PARTICAL9_VIP:	//小道消息 -- 用于vip玩家
	case MsgChat::CHAT_TYPE_PARTICAL10_VIP:	//小道消息 -- 用于vip玩家
		{
			if( msgChat->nHyberItemCnt > 0 )
			{
				s_CUI_ChatInfoBox.AddInfo( szStr, Color_Config.getColor(CC_CHAT_HIGHSHOUT)
					, MsgChat::CHAT_TYPE_HIGHSHOUT, msgChat->chatHeader.szToName,
					msgChat->szString+msgChat->nStringLen,  msgChat->nHyberItemCnt, msgChat->type);
			}
			else
			{
				s_CUI_ChatInfoBox.AddInfo( szStr, Color_Config.getColor(CC_CHAT_HIGHSHOUT)
					, MsgChat::CHAT_TYPE_HIGHSHOUT, msgChat->chatHeader.szToName );
			}
		}
		break;
	default:
		break;
	};

// 	if( bNeedResetCallback )
// 		ControlList::ms_pfGlobalParseText = S_IconInfoHero::GlobalParseText; 
		g_bVipDisplay = false; //yanli [2010-8-10]

	unguard;
}

// 接收到测试网络延迟的消息
void CPlayerMgr::OnMsgGetLag                    ( Msg* pMsg )
{
	guardfunc;
	m_lag.RecvAck();
	unguard;
}

void CPlayerMgr::OnMsgDoneQuest( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgDoneQuest );
	MsgDoneQuest* pMsgDoneQuest = (MsgDoneQuest*)pMsg;
	CPlayer *pPlayer = FindByID( pMsgDoneQuest->playerId );
	if( pPlayer )
	{
		char sound_name[MAX_PATH] = {0};
		MeSprintf_s(sound_name,sizeof(sound_name)/sizeof(char) - 1, "%s\\data\\audio\\role\\DoneQuest.wav", SwGlobal::GetWorld()->GetAppDataCharDir() );
		GSound.PlaySound( sound_name,false, &pPlayer->GetPos() );
		//
		if ( pPlayer == GetMe() )
		{
			PlayEffect( gCfg.m_szDoneQuestEffect, pPlayer );

			SQuest* pQuest = theQuestManager.GetQuest( pMsgDoneQuest->nQuestId );
			if ( pQuest )
			{
				char szInfo[128];
				MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eTextPlayer_QuestComp), pQuest->GetQuestName() );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_ChatSys, szInfo );
			}
		}
	}
	unguard;
}

// 接收到某人的升级消息     
void CPlayerMgr::OnMsgCharLevelUp( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgSeeCharacterLevelup );
	MsgSeeCharacterLevelup* pCharacterLevelup = ( MsgSeeCharacterLevelup* )pMsg;

	if( pMsg->header.stID == GetMyID() )
	{
		thePlayerRole.Levelup( pCharacterLevelup->nNewLevel );

        // added by zhuomeng.hu		[10/9/2010]
        thePlayerRole.SetExpNotUsed( pCharacterLevelup->nUnUsedExp );
		s_CUI_ID_FRAME_MAIN.RefreshExp();

		// 设置需要刷新师徒界面，检查是否到达创建师门等级
		s_CUI_ID_FRAME_Master.NeedRefresh();

		CIntroductionManager::Instance()->ShowTipWithLevel( pCharacterLevelup->nNewLevel );

		s_CUI_ID_FRAME_ManualLevelUp.InitExpInfo();
		s_CUI_ID_FRAME_ManualLevelUp.Refresh();
		s_CUI_ID_FRAME_SKILL_LEARN.CheckLevel();
	}

	CPlayer *pPlayer = FindByID( pMsg->header.stID );
	if( pPlayer )
	{
		pPlayer->SetLevel( pCharacterLevelup->nNewLevel );
		PlayEffect( "Common\\LevelUp.ini", pPlayer );

		if( pPlayer == GetMe() )
		{
            s_CUI_ID_FRAME_BaseProperty.ResetLevelUpTip();
			s_CUI_ID_FRAME_BaseProperty.Refresh();
			s_CUI_ID_FRAME_PACK.RefreshNormalPack();
			s_CUI_ID_FRAME_PACK.RefreshTaskPack();

			thePlayerRole.UpdateActiveQuestState();
			s_CUI_ID_FRAME_MiniMap.UpdateByLevelUp();
		}
	}
	unguard;
}
//技能升级
void CPlayerMgr::OnMsgCharSkillLevelUp( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgCharSkillLevelup );
	MsgCharSkillLevelup *pSkillLevelup = (MsgCharSkillLevelup*)pMsg;

	if( pMsg->header.stID == GetMyID() )
	{
		if( m_pMe )
			PlayEffect( gCfg.m_szSkillLevelUpEffect, m_pMe );
		thePlayerRole.SkillLevelUp( pSkillLevelup->ustSkillNewLevel,pSkillLevelup->ustSkillID);	

        // added by zhuomeng.hu		[10/9/2010]
        thePlayerRole.SetExpNotUsed( pSkillLevelup->nUnUsedExp );
        s_CUI_ID_FRAME_MAIN.RefreshExp();
	}
	else
	{
		CPlayer *pPlayer = FindByID( pMsg->header.stID );
		if (pPlayer)
			PlayEffect( gCfg.m_szSkillLevelUpEffect, pPlayer );
	}

	unguard;
}

//-----
//
//-----
//接收到关于队伍建立清况的消息
void	CPlayerMgr::OnMsgCreateTeam(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckCreateTeam );
	unguard;
}

//接收到有人加入队伍的消息
void	CPlayerMgr::OnMsgJoinTeam(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckJoinTeam);
	MsgAckJoinTeam	*pMsgJoinTeam = (MsgAckJoinTeam *)pMsg;

	char szTemp[1024] = {0};
	//
	switch (pMsgJoinTeam->stError)
	{
	case MsgAckJoinTeam::error_Corpsisfull:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString( eClient_AddInfo_2slk_4 ) );
		}
		break;

	case MsgAckJoinTeam::error_targetalreadyinTeam:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_TargetInTeam ) );
		}
		break;
	case MsgAckJoinTeam::error_people_jointeam:
		{

		}
		break;
	case MsgAckJoinTeam::error_cannotfindtarget:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_FindNotPlayer ) );
		}
		break;
	case MsgAckJoinTeam::error_Teamisfull:
		{
			if (thePlayerRole.IsTeamHeader())
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_TeamFull ) );
			}
			else
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_TargetTeamFull ) );
			}
		}
		break;
	case MsgAckJoinTeam::error_sys:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString( eText_TeamFail ) );
		}
		break;
	case MsgAckJoinTeam::error_assignmode:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString( eText_TeamFail_AssignMode ) );
		}
		break;
	case MsgAckJoinTeam::error_targetcancel:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_TeamFail_TargetCancel ) );
		}
		break;
	case MsgAckJoinTeam::error_targetrequesting:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString( eText_Server_TeamTargetResquesting ));
		}
		break;
	case MsgAckJoinTeam::error_RequestOnlyHeader:
		{

		}
		break;
	case MsgAckJoinTeam::error_succeed:
		{

		}
		break;
	case MsgAckJoinTeam::succeed_upgrade:
		{
			if( !thePlayerRole.m_bCorps )
				MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) - 1,theXmlString.GetString( eText_UpgradeTeam_Succeed), pMsgJoinTeam->name );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, szTemp );
		}
		break;
	case MsgAckJoinTeam::error_upgrade:
		{
			MeSprintf_s( szTemp,sizeof(szTemp)/sizeof(char) - 1, theXmlString.GetString(eText_UpgradeTeam_Faild), pMsgJoinTeam->name );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, szTemp );
		}
		break;
	case MsgAckJoinTeam::error_inPlayerBlacklist:
		{
			MeSprintf_s( szTemp,sizeof(szTemp)/sizeof(char) - 1, theXmlString.GetString( eClient_OpFailReasonInBlacklist), pMsgJoinTeam->name );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, szTemp );
		}
		break;
	case MsgAckJoinTeam::error_teamnoexist:
		{
		}
		break;
	case MsgAckJoinTeam::error_headerischange:
		{
		}
		break;
	case MsgAckJoinTeam::error_inMyBlacklsit:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString( eText_AddFriInBlackList ) );
		}
		break;
    case MsgAckJoinTeam::error_notsamecountry:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString( eText_TeamFail_NotSameCountry ) );
        }
        break;
	case MsgAckJoinTeam::error_notonline:
		{
			//提示玩家处于离线摆摊状态
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString( eText_TeamFail_NotOnLine ) );
		}
		break;
	case MsgAckJoinTeam::success_addTeam:
		{
			char tmpStr[256] = {0};
			MeSprintf( tmpStr, sizeof(tmpStr), theXmlString.GetString(eText_Team_JoinOneTeamSuccess), pMsgJoinTeam->name );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, tmpStr );
		}
		break;
	//case MsgAckJoinTeam::success_sendInvite:
	//	{
	//		char tmpStr[256] = {0};
	//		MeSprintf( tmpStr, sizeof(tmpStr), "你已向%s发出组队邀请", pMsgJoinTeam->name );//
	//		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, tmpStr );
	//	}
	//	break;
	}

	s_CUI_Group.Refeash();
	s_CUI_ID_FRAME_Team.RefreshView();
	unguard;
}
//队员下线了
void CPlayerMgr::OnMsgTeamOutLine( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgTeamOutLine );
	MsgTeamOutLine  *pmsgTeamInfo = (MsgTeamOutLine *)pMsg;
	TeamInfo* pInfo = thePlayerRole.GetTeamInfo(pmsgTeamInfo->dwID);
	if( pInfo )
	{
		pInfo->bOnline = false;
		pInfo->nHp		= 0;
		pInfo->nMp		= 0;
		s_CUI_Group.Refeash();
	}
	s_CUI_ID_FRAME_Team.RefreshView();
	unguard;

}
//接收到队伍的，信息
void	CPlayerMgr::OnMsgTeamInfo(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgTeamInfo );
	MsgTeamInfo  *pmsgTeamInfo = (MsgTeamInfo *)pMsg;
	//
	s_CUI_ID_FRAME_Team.RefreshView();
	unguard;
}

void	CPlayerMgr::OnRetFlagHeaderFromTeam(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgRetFlagHeaderFromTeam );
	MsgRetFlagHeaderFromTeam *Ret = (MsgRetFlagHeaderFromTeam*)pMsg;

	if( Ret->bSrcess )
	{
		//Ret->stId;
		char szBuffe[MAX_PATH] = {0};
		for( int i=0; i< thePlayerRole.m_TeamData.size(); i++ )
		{
			TeamInfo *pInfo = &thePlayerRole.m_TeamData[i];
			if( pInfo )
			{
				if( Ret->dwDestID == pInfo->nID )
				{
					pInfo->bHeader2 = true;
				}
				if( Ret->dwSrcID == pInfo->nID )
				{
					pInfo->bHeader2 = false;
				}
			}
		}

		s_CUI_Group.Refeash();
	}

	unguard;
}

void	CPlayerMgr::OnChangeManipleFromTeamRet(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgChangeManipleFromTeamRet );
	MsgChangeManipleFromTeamRet *pRet = (MsgChangeManipleFromTeamRet *)pMsg;

	if( pRet && pRet->bSrcess )
	{
		for( int i=0; i< thePlayerRole.m_TeamData.size(); i++ )
		{
			TeamInfo *pInfo = &thePlayerRole.m_TeamData[i];
			if( pInfo )
			{
				if( pRet->dwDest == pInfo->nID )
				{
					pInfo->stManiple = pRet->stDestManiple;
					pInfo->bHeader2 = false;
				}
				if( pRet->dwSrc == pInfo->nID )
				{
					pInfo->stManiple = pRet->stSrcManiple;
					pInfo->bHeader2 = false;
				}
			}
		}
		s_CUI_Group.Refeash();
	}
	unguard;
}


//有人加入队伍
void	CPlayerMgr::OnMsgAddTeamMember(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAddTeamMember );
	MsgAddTeamMember  *p = (MsgAddTeamMember *)pMsg;

	TeamInfo InInfo;
	InInfo.nID = p->dwMemberID;
	InInfo.szName = p->szName;
	InInfo.nHp = p->nHp;
	InInfo.nMaxHp = p->nHpMax;
	InInfo.nMaxMp = p->nMpMax;
	InInfo.nMp = p->nMp;
	InInfo.nLvl = p->stLvl;
	InInfo.bOnline = p->bOnline;
	if (!InInfo.bOnline)
	{
		InInfo.nHp		= 0;
		InInfo.nMp		= 0;
	}
	InInfo.bHeader = p->bHeader;
	InInfo.usProfession = p->Profession;
	InInfo.stManiple = p->stManiple;
	InInfo.bHeader2 = p->bHeader2;
	InInfo.ucSex = p->shSex;
	InInfo.bIsNewAdd = p->bIsNewAdd;
	InInfo.nHairId = p->nHairId;
	InInfo.nFaceId = p->nFaceId;
    InInfo.nHeadPicId = p->nHeadPicId;
	thePlayerRole.OnAddTeamMember(  InInfo );

	thePlayerRole.SetGroupId( p->dwGroupId );

	s_CUI_ID_FRAME_Team.RefreshView();	//同步刷新组队界面 
	unguard;
}
//有人退出了队伍
void	CPlayerMgr::OnMsgDeleteAMember(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgDeleteTeamMember );
	MsgDeleteTeamMember * pMsgDeleteTeamMember = (MsgDeleteTeamMember *)pMsg;
	thePlayerRole.OnDeleteTeamMember( pMsgDeleteTeamMember->dwMemberID );

	s_CUI_ID_FRAME_Team.RefreshView();
	unguard;
}
//自己离开了队伍
void	CPlayerMgr::OnMsgExitTeam(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgExitTeam );
	MsgExitTeam * pMsgExitTeam = (MsgExitTeam *)pMsg;
	if ( pMsgExitTeam->header.stID == GetMe()->GetID())
	{
		thePlayerRole.OnExitTeam();

		if (pMsgExitTeam->bIsDisband)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString( eText_Server_TeamDisband ) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString( eText_Server_TeamLeaved ) );
		}

		s_CUI_ID_FRAME_Team.RefreshView();
	}
	else
	{
		if (pMsgExitTeam->bIsDisband)
		{
			CPlayer* player = FindByID(pMsgExitTeam->header.stID);
			if (player)
			{
				player->SetTeamId(0);
				player->SetTeamPosition(ETP_None);
			}
		}		
	}

	/*if ( pMsgExitTeam->bIsDisband)
	{
		if(thePlayerRole.GetTeamInfo().size() != 0)
		{
			for (int i = 0; i < thePlayerRole.GetTeamInfo().size(); ++i)
			{
				CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( thePlayerRole.GetTeamInfo()[i].szName.c_str() );
				if (player && !player->IsRole())
				{
					player->SetTeamId(0);
					player->SetTeamPosition(ETP_None);
				}
					
			}
		}
	}*/

	
	unguard;
}
void	CPlayerMgr::OnMsgAssign_Item_Team( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgReqAssginTeam );
	MsgReqAssginTeam *msg = (MsgReqAssginTeam*)pMsg;
	unguard;
}
void CPlayerMgr::OnMsgTeamMemberAck(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgTeamMemberAck );
	MsgTeamMemberAck *msgAck = (MsgTeamMemberAck*)pMsg;

	//CPlayer* pPlayer = FindByID( msgAck->nMemberID );

	//if ( pPlayer == NULL && pPlayer->GetName() == NULL )
	//{
	//	return;
	//}

	if( msgAck->nType == MsgTeamMemberAck::ECD_AgreeFollow )	// 同意跟随
	{	
		char strTmp[256] = {0};
		MeSprintf_s( strTmp, sizeof(strTmp) - 1, theXmlString.GetString(eText_Team_AgreeFollow), msgAck->strMemberName );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, strTmp );
	}
	else if ( msgAck->nType == MsgTeamMemberAck::ECD_RefuseFollow )
	{	
		char strTmp[256] = {0};
		MeSprintf_s( strTmp, sizeof(strTmp) - 1, theXmlString.GetString(eText_Team_RefuseFollow), msgAck->strMemberName );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, strTmp );
	}
	else if ( msgAck->nType == MsgTeamMemberAck::ECD_CancelFollow )
	{
		char strTmp[256] = {0};
		MeSprintf_s( strTmp, sizeof(strTmp) - 1, theXmlString.GetString(eText_Team_CancelFollow), msgAck->strMemberName );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, strTmp );
			
	}
	else if ( msgAck->nType == MsgTeamMemberAck::ECD_LeaderCancelFollow )
	{
		if(s_CUI_ID_FRAME_Team.GetTeamFollowID() != -1)
		{
	      CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_Team_LeaderCancelFollow) );

		  s_CUI_ID_FRAME_Team.SetTeamFollowID( -1 );

		}
	
	}

	unguard;
}
void CPlayerMgr::OnMsgAddTeamCancel( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckInquireInvitee );
	MsgAckInquireInvitee *msg = (MsgAckInquireInvitee*)pMsg;
	unguard;
}
void CPlayerMgr::OnMsgChange_AssignMode( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckChangeAssignMode );
	MsgAckChangeAssignMode* pChangeAssingMode = (MsgAckChangeAssignMode*)pMsg;

	// 通知队员分配模式已改
	thePlayerRole.SetAssignMode(pChangeAssingMode->AssignMode);

	char szBuf[256];
	switch( pChangeAssingMode->AssignMode )
	{
	case AssignMode_FreeMode:
		strcpy( szBuf, theXmlString.GetString(eText_Client_show_assignMode_Freedom) );
		break;
	case AssignMode_Team:
		strcpy( szBuf, theXmlString.GetString(eText_Client_show_assignMode_Team) );
		break;
	case AssignMode_Random:
		strcpy( szBuf, theXmlString.GetString(eText_Client_show_assignMode_Random) );
		break;
	case AssignMode_Assign:
		strcpy( szBuf, theXmlString.GetString(eText_Client_show_assignMode_Assign) );
		break;
	}
	//s_CUI_ChatInfoBox.AddInfo( szBuf, Color_Config.getColor( CC_CHAT_TEAM ));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szBuf );	

	// 更新UI
	if( s_CUI_ID_FRAME_SelfRBMenu.IsVisable() )
	{
		s_CUI_ID_FRAME_SelfRBMenu.UpdateAssignMode();
	}

	unguard;
}
void CPlayerMgr::OnMsgChange_AssignMode_Result( Msg* pMsg )
{
	guardfunc;
	unguard;
}
bool InquireTeamHeader( const bool bPressYesButton, void *pData )
{
	guardfunc;
	MsgInquireTeamHeader* pMsgInquireTeamHeader = (MsgInquireTeamHeader*)pData;
	MsgAckInquireTeamHeader msg;
	msg.bAgree = bPressYesButton;
	msg.dwJoinMenID = pMsgInquireTeamHeader->dwJoinMenID;
	msg.header.stID = theHeroGame.GetPlayerMgr()->GetMyID();
	GettheNetworkInput().SendMsg(&msg);
	return true;
	unguard;
}
void CPlayerMgr::OnMsgInquireTeamHeader(Msg* pMsg)
{
	guardfunc;

	unguard;
}

void CPlayerMgr::OnMsgAckAttack3( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckQueryAttack2 );
	MsgAckQueryAttack2 *pAckAttack = (MsgAckQueryAttack2 *)pMsg;
	//
	switch (pAckAttack->Msgid)
	{
	case MsgAckQueryAttack2::AckQueryAttack2Fail:
		break;
	case MsgAckQueryAttack2::AckQueryAttack2Ok:
	default:
		if( m_pMe )
			m_pMe->ServerAttackFailProc();
		break;
	}
	unguard;
}


//////////////////////////////////////////////////////////////////////////
// 回应请求创建帮派
void CPlayerMgr::OnMsgGuildAckCreateNotice(Msg* pMsg_)
{
	guardfunc;
	CHECK_MSGLEN(pMsg_, MsgCreateGuildAck);
	MsgCreateGuildAck* pMsg = (MsgCreateGuildAck*)pMsg_;
	
	char szText[256] = "0";
	
	switch (pMsg->uchResult)
	{
	case MsgCreateGuildAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_CreateGuildSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgCreateGuildAck::ECD_ErrorName:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_InValideName));
			ShowGuildInfo(szText);
		}
		break;
	case MsgCreateGuildAck::ECD_SaveName:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_SameName));
			ShowGuildInfo(szText);
		}
		break;
	case MsgCreateGuildAck::ECD_HaveGuild:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_AlreadyHadGuild));
			ShowGuildInfo(szText);
		}
		break;
	case MsgCreateGuildAck::ECD_LevelLess:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_LevelLessThanThirty));
			ShowGuildInfo(szText);
		}
		break;
	case MsgCreateGuildAck::ECD_NotEnoughMoney:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NotEnoughMoney));
			ShowGuildInfo(szText);
		}
		break;
	case MsgCreateGuildAck::ECD_NotCountry :
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NotCountry));
			ShowGuildInfo(szText);
		}
		break;
	default:
		break;
	}
	unguard;
}

void CPlayerMgr::OnMsgGuildAckDismiss( Msg* pMsg )
{
	guardfunc;

	unguard;
}

void CPlayerMgr::OnMsgSeeAttack( Msg* pMsg )
{
	guardfunc;
	//////////////////////////////////////////////////////////////////////////
	//变长消息
	MsgSeeAttack3 *pSee3 = (MsgSeeAttack3 *)pMsg;

	if( pSee3->stResultNum <= 0 )
		return;

	if( !GetMe() )
		return;

	{
		CPlayer *pSrc = FindByID( pSee3->header.stID );
		if( !pSrc )
		{
			OutputDebugString( "OnMsgSeeAttack3找不到发动攻击的Player\n" );
			return;
		}

		ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pSee3->ustSkillID, pSee3->ustSkillLevel );
		if (!pSkill)
			return;

		if( IsCollectSkill(pSee3->ustSkillID) )
		{
			// 采集技能，不发攻击动作
			return;
		}

		// 刷新召唤兽血量
		if ( (GetMe()->GetPetID() == pSee3->header.stID) || (GetMe()->GetPetID() == pSee3->results[0].stTargetWho) )
			thePlayerRole.UpdateUI();

		if (pSrc == GetMe())
		{		
	  //      //如果攻击消息发过来 并且正在读条，则打断读条向服务器请求终止当前脚本 并且不是吟唱技能（主要针对持续释放技能）lyh++
			//if(s_CUI_Progress.IsVisable() && !pSkill->ustPrepTime)
			//{
			//	s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), 1, true, 1, true, true, theXmlString.GetString(eTextPlayer_Break), true, false, 0, FALSE );
			//	MsgScriptCancel msg;
			//	GettheNetworkInput().SendMsg( &msg );
			//}
            //lyh注释掉上边下面， 上边的原因是判断的地方太多了，没法做，下面是普通攻击的cd是在客户端放的时候就让cd了。

			if (IsNormalAttack(pSee3->ustSkillID))
			{
				SCharSkill *_pSkill = NULL;
				_pSkill = thePlayerRole.m_SkillBag.GetSkillByID( pSee3->ustSkillID );
				if (_pSkill)
				{
					thePlayerRole.m_SkillBag.StartSkillCoolDown( _pSkill->ustSkillID,
						_pSkill->stSkillLevel,
						_pSkill->nColdTime );
					s_CUI_ID_FRAME_MAIN.RefeashHotKey();
				}
			}

			thePlayerRole.SetPlayerHP(pSee3->results[pSee3->stResultNum-1].nSrcHp);
			thePlayerRole.SetPlayerMP(pSee3->results[0].nSrcMp);
		}

		CPlayer* pDest = FindByID( pSee3->results[0].stTargetWho );
		if( pDest )
		{
			if (pSrc->GetID() == s_CUI_ID_FRAME_Target.GetPlayerID())
			{
				s_CUI_ID_FRAME_Target.SetPlayerTarget(pDest);
			}

			if( pDest->IsPlayer() )
			{
				// 如果玩家被攻击并且没锁定怪，则锁定攻击的怪
				if( pDest == m_pMe )
				{
					// 如果自己是变身镖车状态，受到伤害就下镖车 //lyh屏蔽 在镖车状态的时候，被打不下镖车
					//if (m_pMe->IsYabiaoState())
					//{
					//	MsgRestoreFromBiaocheReq msg;
					//	GettheNetworkInput().SendMsg(&msg);

					//	// 显示上镖车按钮
					//	s_CUI_ID_FRAME_OnBiaoChe.ShowBiaocheGetOnButton();
					//}

					if (!thePlayerRole.m_isPlayerHitMe && pSrc->IsPlayer() && pSrc != m_pMe)
					{
						// 判断是否有伤血
						BOOL bHurt = FALSE;
						for( int i = 0; i < pSee3->stResultNum; i++ )
						{
							if( pSee3->results[i].stTagHpNum + pSee3->results[i].nBackAttack > 0 )
							{
								bHurt = TRUE;
								break;
							}
						}
						if( bHurt )
						{
							thePlayerRole.m_isPlayerHitMe = true;
							thePlayerRole.m_dwPlayerHitMeAlphaStartTime = HQ_TimeGetTime();
						}
					}

					if( GetLockPlayerID() <= 0 && pSkill->sSkillCategory != ItemDefine::SCT_Assistant)
					{
						// 应策划需求，如果没锁定玩家，且对自己施放技能，施放后不锁定自己
						if( pSrc != m_pMe )
						{
							//特效怪
							if(pSrc->IsEffect())
							{

								EFFECTCHARCONFIG _Config;
								if(theEffectCharConfig.FindEffectCharConfigBySkillID(_Config,pSrc->GetEffectCharSkillID()))
								{
									SetLockPlayerID(-1);
									if(_Config.bCanBeAttack)
									{
										SetLockPlayerID(pSee3->header.stID);
										s_CUI_ID_FRAME_Target.SetPlayer(pSee3->header.stID);
									}
								}

							}else
							{
								SetLockPlayerID(pSee3->header.stID);
								s_CUI_ID_FRAME_Target.SetPlayer(pSee3->header.stID);
							}
						}
						g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
					}

					// ui闪烁, 受攻击后闪5次
					//if( pDest != pSrc )
					//{
					//	s_CUI_ID_FRAME_Group_Me.SetPICTURE_Guang1StartFlash( 5, true, true );
					//}

					// 判断是否坐下状态，并且坐下状态没被打断
					if( pDest->GetSitStatus() && !pDest->GetSitInterrupt() )
					{
						// 通知服务器打断坐下状态，但本地先不改动作，等服务器反馈改变SubAction再播站起动作
						ProcessCommand("DoSitDown");
					}
				}
			}
			else if( pDest->IsMonster() )
			{
				//使用技能指引
				if( pDest->IsMonster() && thePlayerRole.IsFinishedIntroduce(INTRO_USESKILL) == false )
				{
					CIntroductionManager::Instance()->ShowTip(INTRO_USESKILL);
					thePlayerRole.SetFinishedIntroduce(INTRO_USESKILL);
				}
			}
		}

		SAttackInfo info;

		info.dwSerialNo = HQ_TimeGetTime();
		info.nSrcId = pSrc->GetID();
		info.iSrcHp = pSee3->results[0].nSrcHp;
		info.iSrcMp = pSee3->results[0].nSrcMp;
		info.iSrcNum = pSee3->results[0].stSrcHpNum;
		info.iSrcMpNum = pSee3->results[0].stSrcMpNum;
		info.iSkill = pSee3->ustSkillID;
		info.iSkillLevel = pSee3->ustSkillLevel;
		info.dwHoldTime = pSee3->dwHoldTime;
		info.dwActionTime = pSee3->dwActionTime;
		info.bIsCharTarget = pSee3->bIsCharTarget;
		// added, jiayi, [2009/7/20]
		if( !info.bIsCharTarget ) // point aoe
		{
			info.pos = pSee3->target.pos;
		}

		BOOL bFight = FALSE;
		info.nTargetId = pSee3->results[0].stTargetWho;

		for( int i = 0; i < pSee3->stResultNum; i++ )
		{
			CPlayer* pDst = FindByID( pSee3->results[i].stTargetWho );
			CPlayer* pAttacker = FindByID( pSee3->results[i].stAttackerWho );
			if( pDst )
			{
				short shMonsterType = pDst->GetMonsterType();
				if( !(shMonsterType == eMT_Mine	|| shMonsterType == eMT_Herb || shMonsterType == eMT_Mount
					|| shMonsterType == eMT_Treasure || shMonsterType == eMT_Insect ) )
				{
					bFight = TRUE;
				}
			}

			SeeAttackParam kSeeAttackParam;
			kSeeAttackParam.pAttacker = pAttacker;
			kSeeAttackParam.pDst = pDst;
			kSeeAttackParam.stAttackerX = pSee3->stAttackerX; 
			kSeeAttackParam.stAttackerY = pSee3->stAttackerY;
			kSeeAttackParam.nTagHp = pSee3->results[i].nTagHp; 
			kSeeAttackParam.iTagNum = pSee3->results[i].stTagHpNum;
			kSeeAttackParam.iSrcHpNum = pSee3->results[i].stSrcHpNum;
			kSeeAttackParam.nTagMp = pSee3->results[i].nTagMp; 
			kSeeAttackParam.iTagMpNum = pSee3->results[i].stTagMpNum;
			kSeeAttackParam.iSrcMpNum = pSee3->results[i].stSrcMpNum;
			kSeeAttackParam.iBalanceType = pSee3->results[i].cBalanceType;
			kSeeAttackParam.stTagBackAttackNum = pSee3->results[i].nBackAttack;
			kSeeAttackParam.nShieldHp          = pSee3->results[i].nShieldHp;
			OnSeeAttack(
				&info,
				pSee3->results[i].nStatusFlag,
				kSeeAttackParam );
		}

		//注册AttackInfo
		SAttackInfo* pAttackInfo = theAttackInfoMan.AddAttackInfo( info );

		if( pAttackInfo )
		{
			pSrc->GetActionQueue()->Push_Attack( pAttackInfo );
		}
		pSrc = NULL;
		pSee3 = NULL;
	}
	unguard;
}

void CPlayerMgr::OnMsgSeeCastInefficacySkill( Msg *pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgCastInefficacySkill );
	MsgCastInefficacySkill *inefficacyskill = (MsgCastInefficacySkill*)pMsg;

	CPlayer *pPlayer = FindByID( inefficacyskill->header.stID );

	if( pPlayer )
	{
		if( pPlayer->IsPlayer() && pPlayer->GetSitStatus() )
		{
			// 发送站起状态给服务器
			if( pPlayer->IsRole() )
			{
				// 坐下状态被打断
				pPlayer->SetSitInterrupt(1);
				ProcessCommand("DoSitDown");
			}
		}
		// added, jiayi, [2009/7/21],point aoe, crack
		if( !inefficacyskill->bIsCharTarget )
		{
			D3DXVECTOR3 vPos( inefficacyskill->target.pos.x, inefficacyskill->target.pos.y, inefficacyskill->target.pos.z );
			pPlayer->SetPointAoePos( vPos );
		}
		if( !pPlayer->CheckAdvanceSkill( inefficacyskill->ustSkillID, inefficacyskill->ustSkillLevel ) )
			pPlayer->SwitchAttackAnim( inefficacyskill->ustSkillID, inefficacyskill->ustSkillLevel );
	}
	pPlayer = NULL;
	unguard;
}

void CPlayerMgr::OnMsgPlayerNameChanged( Msg*pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPlayerNameChanged );
	MsgPlayerNameChanged *pChanged = (MsgPlayerNameChanged*)pMsg;
	CPlayer *pPlayer = FindByID( pChanged->header.stID );

	if( !pPlayer )
		return;

	pPlayer->SetName( pChanged->szPlayerName );
	unguard;
}

void CPlayerMgr::OnMsgCityInfo( Msg *pMsg )
{
}

void CPlayerMgr::OnMsgTeachSkill( Msg *pMsg )
{
	guardfunc;
	unguard;
}

void CPlayerMgr::OnMsgChangePKRecord( Msg *pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgChangePKRecord);
	MsgChangePKRecord *pChangePKRecord = (MsgChangePKRecord*)pMsg;

	unguard;
}
void CPlayerMgr::OnMsgGetAllNpcOnTheMap( Msg* pMsg )
{
	guardfunc;
	return;
	unguard;
}

void CPlayerMgr::OnMsgEquip( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckEquip);
	MsgAckEquip *pAckEquip = (MsgAckEquip*)pMsg;
	switch( pAckEquip->stResult ) 
	{
	case MsgAckEquip::Result_Success:
		{
			s_CUI_ID_FRAME_PACK.Equip( pAckEquip->ustWhere, pAckEquip->ustPackIndex );
		}
		break;
	default:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eTextPlayer_EquipFaild), theXmlString.GetString(eTextPlayer_Faild), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		break;
	}
	unguard;
}

void CPlayerMgr::OnSkillBeginCoolDown( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, Msg_Skill_BeginCoolDown);
	Msg_Skill_BeginCoolDown* pSkillBeginCoolDown = (Msg_Skill_BeginCoolDown*)pMsg;


	ItemDefine::SItemSkill *pItemSkill;
	pItemSkill = GettheItemDetail().GetSkillByID( pSkillBeginCoolDown->ustSkillID,
		pSkillBeginCoolDown->ustSkillLevel );
	if ( !pItemSkill )
		return;

	// modified, [10/21/2010 zhangjiayi]
	// 添加技能延时
	DWORD dwDelay = pSkillBeginCoolDown->dwColdTime - pItemSkill->dwSkillCoolDownTime;
	if (pItemSkill->sSkillCategory == ItemDefine::SCT_MountMasterInitiativeControl)
	{
		thePlayerRole.m_MountSkillBag.StartSkillCoolDown( pSkillBeginCoolDown->ustSkillID,
			pSkillBeginCoolDown->ustSkillLevel,
			dwDelay );
	}
	else if(pItemSkill->sSkillCategory == ItemDefine::SCT_PetMasterManualControl)
	{
		thePlayerRole.m_PetSkillBag.StartSkillCoolDown(pSkillBeginCoolDown->ustSkillID,
			pSkillBeginCoolDown->ustSkillLevel,
			dwDelay );
	}
	else /*if (pItemSkill->sSkillCategory == ItemDefine::SCT_HeroAttack)*/
	{
		{
			thePlayerRole.m_HeroSkillBag.StartSkillCoolDown( pSkillBeginCoolDown->ustSkillID,
				pSkillBeginCoolDown->ustSkillLevel,
				dwDelay );
		}
		{
			thePlayerRole.m_SkillBag.StartSkillCoolDown( pSkillBeginCoolDown->ustSkillID,
				pSkillBeginCoolDown->ustSkillLevel,
				dwDelay );

		}
	}
	

	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_MAIN.RefeashHotNumber();

	s_CUI_ID_FRAME_PetMain.Refresh();
	s_CUI_ID_FRAME_CarryMain.UpdateCD();

	if (s_CUI_ID_FRAME_SKILL.IsVisable())
		s_CUI_ID_FRAME_SKILL.NeedRefresh();
	unguard;
}

void CPlayerMgr::OnMsgTeamPlayerInfo( Msg *pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, Msg_Team_PlayerInfo);
	Msg_Team_PlayerInfo *pInfo = (Msg_Team_PlayerInfo *)pMsg;
	TeamInfo InInfo;

	InInfo.nID = pInfo->dwDataBaseId;
	InInfo.nHp = pInfo->nHp;
	InInfo.nMaxHp = pInfo->nHpMax;
	InInfo.nMaxMp = pInfo->nMpMax;
	InInfo.nMp = pInfo->nMp;
	InInfo.nLvl = pInfo->stLvl;
	InInfo.bHeader = pInfo->bHeader;
	InInfo.usProfession = pInfo->Profession;
	InInfo.nMapID = pInfo->dwMapID;
	InInfo.x = pInfo->x ;
	InInfo.y = pInfo->y ;
	InInfo.fx = pInfo->fx ;
	InInfo.fy = pInfo->fy ;
	InInfo.stManiple = pInfo->stManiple;
	InInfo.bHeader2 = pInfo->bHeader2;
	InInfo.bOnline = true;
	InInfo.AssignMode = pInfo->AssignMode;
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( pInfo->header.stID );

	if( pPlayer )
	{
		pPlayer->SetHPInfo_HP( pInfo->nHp );
	}
	thePlayerRole.UpdataPlayerInfo( InInfo );
	unguard;
}
void CPlayerMgr::OnMsgChangeSkillBySelect( Msg* pMsg )
{
	//在选择人物界面对技能发生变化 一定是套装技能的处理
	CHECK_MSGLEN( pMsg, MsgChangeSkill);
	MsgChangeSkill *pChangeSkill = (MsgChangeSkill*)pMsg;
	if (pChangeSkill->op == MsgChangeSkill::OT_Add)
	{
		//如果为技能套装 我们需要将其加入到通用里面去
		ItemDefine::SItemSkill *pSkill = NULL;
		pSkill = GettheItemDetail().GetSkillByID(pChangeSkill->skill.ustSkillID,pChangeSkill->skill.stSkillLevel );
		if(!pSkill)
			return;
		if ( pSkill->specialSkillType > ItemDefine::ESST_Normal && pSkill->specialSkillType < ItemDefine::ESST_SuitMax )
		{
			s_CUI_ID_FRAME_SKILL.AddCommonSkillBySuitEquip(pChangeSkill->skill.ustSkillID,pChangeSkill->skill.stSkillLevel);
		}
	}
	else if( pChangeSkill->op == MsgChangeSkill::OT_Delete )
	{
		s_CUI_ID_FRAME_SKILL.ClearCommonSkillBySuitEquip(pChangeSkill->skill.ustSkillID);
	}
}
void CPlayerMgr::OnMsgAddSkill( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgChangeSkill);
	MsgChangeSkill *pChangeSkill = (MsgChangeSkill*)pMsg;
	if (pChangeSkill->op == MsgChangeSkill::OT_Add)
	{
		if( thePlayerRole.m_SkillBag.GetSkillByID( pChangeSkill->skill.ustSkillID ) )
		{
			SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID( pChangeSkill->skill.ustSkillID );
			pSkill->stSkillLevel = pChangeSkill->skill.stSkillLevel;
		}
		else if( thePlayerRole.m_SkillBag.AddSkill( pChangeSkill->skill.ustSkillID, pChangeSkill->skill.stSkillLevel ) )
		{
			if (!s_CUI_ID_FRAME_SKILL.IsVisable())
			{
				s_CUI_ID_FRAME_MainMenu.SetNeedSpark(true, CUI_ID_FRAME_MainMenu::ekey_skill);
			}

			thePlayerRole.UpdateUI();
			ItemDefine::SItemSkill *pSkill = NULL;
			pSkill = GettheItemDetail().GetSkillByID(pChangeSkill->skill.ustSkillID,pChangeSkill->skill.stSkillLevel );
			if ( pSkill )
			{
				// 如果属于动作技能则不显示学会技能提示
				if ( pSkill->stGeneralType != 0 )
				{
					char szTemp[128] = {0};
					MeSprintf_s( szTemp,sizeof(szTemp)/sizeof(char) - 1, "%s%s", theXmlString.GetString(eText_StudySkill),pSkill->GetSkillName() );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szTemp );
				}
			}
			//如果为技能套装 我们需要将其加入到通用里面去
			if (pSkill &&  pSkill->specialSkillType > ItemDefine::ESST_Normal && pSkill->specialSkillType < ItemDefine::ESST_SuitMax )
			{
				s_CUI_ID_FRAME_SKILL.AddCommonSkillBySuitEquip(pChangeSkill->skill.ustSkillID,pChangeSkill->skill.stSkillLevel);
			}
		}
		// 添加是否弹出判断
        if( pChangeSkill->bMessageDialog )
		    s_CUI_ID_FRAME_NewSkillMain.AddSkillByCheck( pChangeSkill->skill.ustSkillID );
	}
	else if( pChangeSkill->op == MsgChangeSkill::OT_Delete )
	{
        // 是生产技能则遗忘配方     added by ZhuoMeng.Hu		[12/14/2010]
        int nRecipeType = theRecipeConfig.GetRecipeTypeBySkillId( pChangeSkill->skill.ustSkillID );
        if( nRecipeType > 0 )
        {
            s_CUI_ID_FRAME_Compound.ForgetRecipesByType( nRecipeType );
        }

		thePlayerRole.m_SkillBag.RemoveSkill( pChangeSkill->skill.ustSkillID );

		s_CUI_ID_FRAME_SKILL.ClearCommonSkillBySuitEquip(pChangeSkill->skill.ustSkillID);
	}
	else if(MsgChangeSkill::OT_Update == pChangeSkill->op)
	{
		SCharSkill *pSkill = thePlayerRole.m_SkillBag.GetSkillByID(pChangeSkill->skill.ustSkillID);
		assert(pSkill != NULL);
		if(NULL == pSkill)
			return;

		//检查心法数据的合法性

		//替换技能信息
		*pSkill = pChangeSkill->skill;
		thePlayerRole.UpdateUI();
	}

    // added by zhuomeng.hu		[10/9/2010]
    //thePlayerRole.SetExpNotUsed( pChangeSkill->nUnUsedExp );
    s_CUI_ID_FRAME_MAIN.RefreshExp();

    s_CUI_ID_FRAME_SkillProduce.Refresh();
    s_CUI_ID_ProduceLearn.Refresh();
	s_CUI_ID_FRAME_SKILL.NeedRefresh();
	if(s_CUI_ID_FRAME_SKILL_LEARN.IsVisable())
		s_CUI_ID_FRAME_SKILL_LEARN.Refresh();
	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();;
	s_CUI_ID_FRAME_AutoAttackSet.RefreshSkillUI(true);
	if (pChangeSkill->op == MsgChangeSkill::OT_Add)
	{
		SetSkillAutoToListImage(&(pChangeSkill->skill));
	}

	unguard;
}

void CPlayerMgr::SetSkillAutoToListImage(SCharSkill* pSkill)
{
	if (!pSkill)
	{
		return;
	}

	if (pSkill->stSkillLevel != 1 || !s_CUI_ID_FRAME_SKILL_LEARN.GetStartLearn())
	{
		return;
	}

	if (s_CUI_ID_FRAME_MAIN.IsVisable())
	{
		if (s_CUI_ID_FRAME_MAIN.SetSkillAutoToListImage(pSkill))
		{
			return;
		}
	}

	if (s_CUI_ID_FRAME_Exmain.IsVisable())
	{
		if (s_CUI_ID_FRAME_Exmain.SetSkillAutoToListImage(pSkill))
		{
			return;
		}
	}
}

void CPlayerMgr::OnMsgAckCharInfo( Msg* pMsg )
{
	guardfunc;
	if (!CanReceivePlayerMsg())
	{
		return;
	}
	CHECK_MSGLEN( pMsg, MsgAckCharInfo);
	MsgAckCharInfo* pInfo = (MsgAckCharInfo*)pMsg;
	if( m_pMe && pInfo->stChar == m_pMe->GetID() )
	{
		m_pMe->SetCharInfo( pInfo );

		s_CUI_ID_FRAME_BaseProperty.Refresh();
		s_CUI_ID_FRAME_PACK.RefreshNormalPack();
		s_CUI_ID_FRAME_PACK.RefreshTaskPack();
		s_CUI_ID_FRAME_MAIN.RefreshExp();
		thePlayerRole.UpdateUI();
	}
	else
	{
		CPlayer* pPlayer = FindByID( pInfo->stChar );
		if( pPlayer )
			pPlayer->SetCharInfo( pInfo );

		// 刷新附近玩家
// 		s_CUI_ID_FRAME_TRACK.RefreshPlayerList();
	}
	unguard;
}
//void CPlayerMgr::OnMsgGuildMemberValueChange( Msg* pMsg )
//{
//	guardfunc;
//	CHECK_MSGLEN( pMsg, MsgGuildMemberValueChange);
//	MsgMemberDataUpdate* pValueChange = (MsgGuildMemberValueChange*)pMsg;
//	CGangMgr* pGMM = thePlayerRole.GetGangMgr();
//
//	switch (pValueChange->valueChange.ustWhichAttr)
//	{
//	case EGMVC_CurOffer:
//		{
//			GuildMember* pMember = pGMM->FindByDBId( pValueChange->charDbId );
//			if (pMember)
//			{
//				pMember->m_nGangExps =  pValueChange->valueChange.data.dwValue;
//
//				CPlayer* pPlayer = FindByName(pMember->szName);
//				if (pPlayer)
//				{
//					int dwValue = pMember->m_nGangExps - pPlayer->GetGuildOffer();
//					pPlayer->SetGuildOffer(pMember->m_nGangExps);
//
//					if (pPlayer->IsRole())
//					{
//						char szBuff[256] = {0};
//						if( dwValue > 0 )
//						{
//							D3DXVECTOR3 pos = pPlayer->GetPos();
//							int xEffect,yEffect;
//							World2Screen( pos,xEffect,yEffect );
//							pPlayer->OnShowFlyText( 0, dwValue, 0, GlobalTexture::eAddBangGong );
//							MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouGetGuildOffer ), dwValue );
//						}
//						else
//						{
//							MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouLoseGuildOffer ), -dwValue );
//						}
//						s_CUI_ID_FRAME_InfoList. AddInfo( szBuff, Color_Config.getColor( CC_Exploit ) );
//						s_CUI_ID_FRAME_BaseProperty.Refresh();
//					}
//				}
//			}
//
//		}
//		break;
//	case EGMVC_CurBuild:
//		pGMM->m_GangInfo.m_growingValue = pValueChange->valueChange.data.dwValue;
//		break;
//	case EGMVC_CurMoney:
//		pGMM->m_GangInfo.money = pValueChange->valueChange.data.dwValue;
//		break;
//	case EGMVC_CurLevel:
//		pGMM->m_GangInfo.m_level = pValueChange->valueChange.data.dwValue;
//		break;
//	}
//
//	thePlayerRole.UpdateUI();
//	unguard;
//
//}

//void CPlayerMgr::OnMsgCharGuildInfo( Msg* pMsg )
//{
//	guardfunc;
//	CHECK_MSGLEN( pMsg, MsgCharGuildInfo);
//	MsgCharGuildInfo* pInfo = (MsgCharGuildInfo*)pMsg;
//	CPlayer* pPlayer = FindByID(pInfo->header.stID);
//	if (pPlayer)
//	{
//		if (pInfo->organizeId != GuildDefine::InitID)
//		{
//			pPlayer->SetGuildName(pInfo->m_szName);
//			pPlayer->SetGuildId(pInfo->organizeId, FALSE);
//			pPlayer->SetGuildFlag(pInfo->m_stFlag);
//			pPlayer->SetGangPosition(pInfo->gangPosition);
//		}
//		else
//		{
//			pPlayer->SetGuildName("");
//			pPlayer->SetGuildId(GuildDefine::InitID);
//			pPlayer->SetGangPosition(-1);
//
//		}
//	}
//	unguard;
//
//}

// 接收到角色的显示名称
void CPlayerMgr::OnMsgAckDisplayName( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckDisplayName);
	MsgAckDisplayName *pMsgT = (MsgAckDisplayName*)pMsg;

	if( m_pMe && pMsgT->header.stID == m_pMe->GetID() )
	{
		m_pMe->SetName(pMsgT->szDisplayName);
	}
	else
	{
		CPlayer* pPlayer = FindByID( pMsg->header.stID );
		if( pPlayer )
		{
			pPlayer->SetName(pMsgT->szDisplayName);
		}
	}
	unguard;
}

bool BackToLogin( char bIsTell,void *pData ) 
{
	if (bIsTell)
	{
		CUI_ID_FRAME_ExitGame::BackToLogin(true,NULL);
	}
	
	return true;
}
// 接收到退出指令( 什么退出，是什么退出？)
void CPlayerMgr::OnMsgExit( Msg* pMsg )
{
	guardfunc;
	MsgExit *_ExitMsg = (MsgExit*) pMsg;
	CPlayer *pPlayer = FindByID( pMsg->header.stID );
	if(!pPlayer)
		return;

// 	if( Object_Building == pPlayer->GetCharType() )
// 	{
// 		pPlayer->ClearCountryMask();
// 	}

	//谁退出
	if ( pPlayer == m_pMe )
	{ // 自己
		/*
		 * Author:	2012-8-16 wangshuai
		 * Desc: 	关闭客户端
		 */
		if (isShowDisconnetMsg)
		{
			return;
		}
		switch(_ExitMsg->ExitType)
		{
		case ET_BeKick:
			{
				std::string info = theXmlString.GetString(eText_KickAccounts);
				if (info.empty())
					info = theXmlString.GetString(eText_Disconnect);

				s_CUI_ID_FRAME_ExitGame.IsShowDKLJ = false; //不显示断开链接字样

				//s_CUI_ID_FRAME_MessageBox.closeAll(false);

				s_CUI_ID_FRAME_MessageBox.Show(
					info.c_str(),
					"",
					CUI_ID_FRAME_MessageBox::eTypeConfirm,
					true,
					BackToLogin );
				{
					s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
					s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
				}
				isShowDisconnetMsg = true;
				return;
			}
			break;
		case ET_SystemBeKick:
			{
				std::string info = theXmlString.GetString(eText_Disconnect);
				s_CUI_ID_FRAME_ExitGame.IsShowDKLJ = false; //不显示断开链接字样
				s_CUI_ID_FRAME_MessageBox.Show(
					info.c_str(),
					"",
					CUI_ID_FRAME_MessageBox::eTypeConfirm,
					true,
					BackToLogin );
				{
					s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
					s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
				}
				return;
			}
			break;
		default:
			break;
		}
		//if (_ExitMsg->ExitType == ET_BeKick)
		//{

		//	std::string info = theXmlString.GetString(eText_KickAccounts);
		//	if (info.empty())
		//		info = theXmlString.GetString(eText_Disconnect);

		//	s_CUI_ID_FRAME_ExitGame.IsShowDKLJ = false; //不显示断开链接字样

		//	//s_CUI_ID_FRAME_MessageBox.closeAll(false);

		//	s_CUI_ID_FRAME_MessageBox.Show(
		//		info.c_str(),
		//		"",
		//		CUI_ID_FRAME_MessageBox::eTypeConfirm,
		//		true,
		//		BackToLogin );
		//	{
		//		s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
		//		s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
		//	}
		//	return ;
		//}

		if (gCfg.m_bOpenExitPage)
		{
			ShellExecute( NULL, "open", gCfg.m_strExitPage.c_str(), NULL, NULL, 0 );
		}
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "主角色接收到退出指令!");
		::TerminateProcess(::GetCurrentProcess(), 0);
	}
	else
	{
		// 删除成功并且是玩家，才刷新附件玩家列表
		// modified, [4/30/2010 jiayi],会crash，逻辑重写
		bool bIsPlayer = pPlayer->IsPlayer();

		if( PlayerExit( pMsg->header.stID ) )
		{
// 			if( bIsPlayer )
// 			{
// 				// 刷新附近玩家
// 				s_CUI_ID_FRAME_TRACK.RefreshPlayerList();
// 			}			
		}
	}

	unguard;
}


//看到角色身上出现法术效果
void CPlayerMgr::OnMsgCharShowEff( Msg* pMsg )
{
	guardfunc;

	unguard;
}

// 接收到刷新角色信息
void CPlayerMgr::OnMsgRefreshChar( Msg* pMsg )
{
	guardfunc;

	unguard;
}

//// 接受到非玩家角色贴近其目标
void CPlayerMgr::OnMsgUnPlayerClosingToLockTarget( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgUnPlayerClosingToLockTarget);
	MsgUnPlayerClosingToLockTarget *pMsg1 = (MsgUnPlayerClosingToLockTarget*)pMsg;
	if( m_pMe && pMsg1->header.stID != m_pMe->GetID() )
	{
		CPlayer *pPlayer = FindByID( pMsg1->header.stID );
		guard(test1);
		if( pPlayer )
		{
			if( pPlayer->NeedVerifyPos( pMsg1->vPos, g_fNeedVerifyDistance ) )
			{
				pPlayer->ReSetPos( pMsg1->vPos.x, pMsg1->vPos.y, pMsg1->vPos.z );
			}

			CPlayer* pTargetPlayer = FindByID( pMsg1->LockTargetID );
			float fKeepDistance = 0.0f;

			if ( pTargetPlayer )
			{ fKeepDistance = pPlayer->GetBodyLengthSize() + pTargetPlayer->GetBodyLengthSize(); }
			else
			{ fKeepDistance = pPlayer->GetBodyLengthSize() + 0.9f;  }

			pPlayer->GetMoveQueue()->Push_MovingToTarget( pMsg1->LockTargetID, fKeepDistance );
		}
		pPlayer = NULL;
		unguard;
	}
	unguard;
}

// 接收到非玩家移动的消息
void CPlayerMgr::OnMsgUnPlayerMovingToPos( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgUnPlayerMovingToPos);
	MsgUnPlayerMovingToPos *pMsg1 = (MsgUnPlayerMovingToPos*)pMsg;

	if( m_pMe && pMsg1->header.stID != m_pMe->GetID() )
	{
		CPlayer *pPlayer = FindByID( pMsg1->header.stID );
		guard(test1);
		if( pPlayer )
		{
			if( pPlayer->NeedVerifyPos( pMsg1->vStartPos, g_fNeedVerifyDistance ) )
			{
				pPlayer->ReSetPos( pMsg1->vStartPos.x, pMsg1->vStartPos.y, pMsg1->vStartPos.z );
			}
			if( abs(pMsg1->vEndPos.x - pMsg1->vStartPos.x)>0.001 || abs(pMsg1->vEndPos.y - pMsg1->vStartPos.y)>0.001 )
			{
				pPlayer->GetMoveQueue()->Push_MovingToPos( pMsg1->vEndPos.x, pMsg1->vEndPos.y, pMsg1->vEndPos.x - pMsg1->vStartPos.x, pMsg1->vEndPos.y - pMsg1->vStartPos.y );
				pPlayer->m_movepath.LostLockTarget();
			}
		}
		pPlayer = NULL;
		unguard;
	}
	unguard;
}

// 接收到非玩家移动的消息
void CPlayerMgr::OnMsgUnPlayerVerifyPos( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgUnPlayerVerifyPos);
	//OutputDebugString( "OnMsgUnPlayerVerifyPos" );
	MsgUnPlayerVerifyPos *pMsg1 = (MsgUnPlayerVerifyPos*)pMsg;

	if( m_pMe && pMsg1->header.stID != m_pMe->GetID() )
	{
		CPlayer *pPlayer = FindByID( pMsg1->header.stID );
		guard(test1);
		if( pPlayer )
		{
			if( pPlayer->NeedVerifyPos( pMsg1->vPos, g_fNeedVerifyDistance ) )
			{
				pPlayer->ReSetPos( pMsg1->vPos.x, pMsg1->vPos.y, pMsg1->vPos.z );
				pPlayer->SetMoving( FALSE );
			}
			else
			{
				D3DXVECTOR3 vDir = D3DXVECTOR3( pMsg1->chDirX, pMsg1->chDirY, pMsg1->chDirZ );
				D3DXVec3Normalize( &vDir, &vDir );

				pPlayer->GetMoveQueue()->PushPlayerPosAndDir( pMsg1->vPos, vDir );
			}
		}
		pPlayer = NULL;
		unguard;
	}
	unguard;
}

void CPlayerMgr::OnMsgPlayerVerifyPos( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPlayerVerifyPos);
	MsgPlayerVerifyPos *pMsg1 = (MsgPlayerVerifyPos*)pMsg;
	if( m_pMe && pMsg1->header.stID != m_pMe->GetID() )
	{
		CPlayer *pPlayer = FindByID( pMsg1->header.stID );
		guard(test1);
		if( pPlayer )
		{
			if( pPlayer->IsPlayer() )
			{
				if( pMsg1->vPos.z != 0 )
				{
					pPlayer->SetServerZ( pMsg1->vPos.z );
				}

				// 如果正在做拥抱动作，则直接拽位置
				if( pPlayer->NeedVerifyPos( pMsg1->vPos, g_fNeedVerifyDistance ) || pPlayer->IsEmbraceAnim() )
				{
					pPlayer->ReSetPos( pMsg1->vPos.x, pMsg1->vPos.y, pMsg1->vPos.z );
				}
				else
				{
					pPlayer->GetMoveQueue()->PushPlayerPos( pMsg1->vPos );
				}
			}
			else
			{
				OutputDebugString( "给非玩家角色发了玩家的移动消息\n" );
			}
		}
		pPlayer = NULL;
		unguard;
	}
	unguard;
}

// 接收到移动中玩家位置改变的消息
void CPlayerMgr::OnMsgPlayerMovingPos( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPlayerMovingPos);
	MsgPlayerMovingPos *pMsg1 = (MsgPlayerMovingPos*)pMsg;
	if( m_pMe && pMsg1->header.stID != m_pMe->GetID() )
	{
		CPlayer *pPlayer = FindByID( pMsg1->header.stID );
		guard(test1);
		if( pPlayer )
		{
			if( pPlayer->IsPlayer() )
			{
				if (pPlayer->IsUncontrolMoving() )
				{
					pPlayer->SetUncontrolMoveTargetPos( pMsg1->vPos );
				}
				else
				{
					if( pMsg1->vPos.z != 0 )
					{
						pPlayer->SetServerZ( pMsg1->vPos.z );
					}

					if( pPlayer->NeedVerifyPos( pMsg1->vPos, g_fNeedVerifyDistance ) )
					{
						pPlayer->ReSetPos( pMsg1->vPos.x, pMsg1->vPos.y, pMsg1->vPos.z );
					}

					pPlayer->GetMoveQueue()->PushPlayerKeepMovingPassPos( pMsg1->vPos );
				}
			}
		}
		pPlayer = NULL;
		unguard;
	}
	unguard;
}

// 接收到移动中玩家位置和朝向改变的消息
void CPlayerMgr::OnMsgPlayerMovingPosAndDir( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPlayerMovingPosAndDir);
	MsgPlayerMovingPosAndDir *pMsg1 = (MsgPlayerMovingPosAndDir*)pMsg;

	if( m_pMe && pMsg1->header.stID != m_pMe->GetID() )
	{
		CPlayer *pPlayer = FindByID( pMsg1->header.stID );
		guard(test1);
		if( pPlayer )
		{
			if( pPlayer->IsPlayer() )
			{				
				if( pMsg1->vPos.z != 0 )
				{
					pPlayer->SetServerZ( pMsg1->vPos.z );
				}

				if( pPlayer->NeedVerifyPos( pMsg1->vPos, g_fNeedVerifyDistance ) )
				{
					pPlayer->ReSetPos( pMsg1->vPos.x, pMsg1->vPos.y, pMsg1->vPos.z );
				}

				D3DXVECTOR3 vDir = D3DXVECTOR3( pMsg1->chDirX, pMsg1->chDirY, pMsg1->chDirZ );
				D3DXVec3Normalize( &vDir, &vDir );

				pPlayer->GetMoveQueue()->PushPlayerKeepMovingPassPos( pMsg1->vPos, vDir );				
			}
			else
			{
				OutputDebugString( "给非玩家角色发了玩家的移动消息\n" );
			}
		}
		pPlayer = NULL;
		unguard;
	}
	unguard;
}

// 接收到移动中玩家位置和朝向改变的消息，自动寻路
void CPlayerMgr::OnMsgPlayerMovingPosAndDir_TargetDir( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPlayerMovingPosAndDir);
	MsgPlayerMovingPosAndDir *pMsg1 = (MsgPlayerMovingPosAndDir*)pMsg;

	if( m_pMe && pMsg1->header.stID != m_pMe->GetID() )
	{
		CPlayer *pPlayer = FindByID( pMsg1->header.stID );
		guard(test1);
		if( pPlayer )
		{
			if( pPlayer->IsPlayer() )
			{
				if( pMsg1->vPos.z != 0 )
				{
					pPlayer->SetServerZ( pMsg1->vPos.z );
				}

				if( pPlayer->NeedVerifyPos( pMsg1->vPos, g_fNeedVerifyDistance ) )
				{
					pPlayer->ReSetPos( pMsg1->vPos.x, pMsg1->vPos.y, pMsg1->vPos.z );
				}

				D3DXVECTOR3 vDir = D3DXVECTOR3( pMsg1->chDirX, pMsg1->chDirY, pMsg1->chDirZ );
				D3DXVec3Normalize( &vDir, &vDir );

				pPlayer->GetMoveQueue()->PushPlayerKeepMovingPassPos_TargetDir( pMsg1->vPos, vDir );
			}
			else
			{
				OutputDebugString( "给非玩家角色发了玩家的移动消息\n" );
			}
		}
		pPlayer = NULL;
		unguard;
	}
	unguard;
}


// 接收到原地不动玩家的位置消息
void CPlayerMgr::OnMsgPlayerPos( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPlayerPos);
	MsgPlayerPos *pMsg1 = (MsgPlayerPos*)pMsg;
	
	CPlayer *pPlayer = FindByID( pMsg1->header.stID );
	guard(test1);
	if( pPlayer )
	{
		if( pPlayer->IsPlayer() )
		{
			if( pMsg1->vPos.z != 0 )
			{
				pPlayer->SetServerZ( pMsg1->vPos.z );
			}

			if( pPlayer->NeedVerifyPos( pMsg1->vPos, g_fNeedVerifyDistance ) )
			{
				pPlayer->ReSetPos( pMsg1->vPos.x, pMsg1->vPos.y, pMsg1->vPos.z );
			}

			pPlayer->GetMoveQueue()->PushPlayerPos( pMsg1->vPos );
		}
		else
		{
			OutputDebugString( "给非玩家角色发了玩家的移动消息\n" );
		}
		//}
	}
	pPlayer = NULL;
	unguard;
	
	unguard;
}

// 接收到原地不动玩家的朝向消息
void CPlayerMgr::OnMsgPlayerDir( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPlayerDir);
	MsgPlayerDir *pMsg1 = (MsgPlayerDir*)pMsg;

	if( m_pMe && pMsg1->header.stID != m_pMe->GetID() )
	{
		CPlayer *pPlayer = FindByID( pMsg1->header.stID );
		guard(test1);
		if( pPlayer )
		{
			if( pPlayer->IsPlayer() )
			{
				
				D3DXVECTOR3 vDir = D3DXVECTOR3( pMsg1->chDirX, pMsg1->chDirY, pMsg1->chDirZ );
				D3DXVec3Normalize( &vDir, &vDir );

				pPlayer->GetMoveQueue()->PushPlayerDir( vDir );
				
			}
			else
			{
				OutputDebugString( "给非玩家角色发了玩家的移动消息\n" );
			}
		}
		pPlayer = NULL;
		unguard;
	}
	unguard;
}

// 接收到原地不动玩家的位置和朝向消息
void CPlayerMgr::OnMsgPlayerPosAndDir( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPlayerPosAndDir);
	MsgPlayerPosAndDir *pMsg1 = (MsgPlayerPosAndDir*)pMsg;

	if( m_pMe && pMsg1->header.stID != m_pMe->GetID() )
	{
		CPlayer *pPlayer = FindByID( pMsg1->header.stID );
		guard(test1);
		if( !pPlayer )
			return;
		
		if( pPlayer->IsPlayer() )
		{				
			if( pMsg1->vPos.z != 0 )
			{
				pPlayer->SetServerZ( pMsg1->vPos.z );
			}

			if( pPlayer->NeedVerifyPos( pMsg1->vPos, g_fNeedVerifyDistance ) )
			{
				pPlayer->ReSetPos( pMsg1->vPos.x, pMsg1->vPos.y, pMsg1->vPos.z );
			}

			D3DXVECTOR3 vDir = D3DXVECTOR3( pMsg1->chDirX, pMsg1->chDirY, pMsg1->chDirZ );
			D3DXVec3Normalize( &vDir, &vDir );

			pPlayer->GetMoveQueue()->PushPlayerPosAndDir( pMsg1->vPos, vDir );				
		}
		else
		{
			OutputDebugString( "给非玩家角色发了玩家的移动消息\n" );
		}
		
		pPlayer = NULL;
		unguard;
	}
	unguard;
}

// 接收到相关移动的消息包
void CPlayerMgr::OnMsgPosChange( Msg* pMsg )
{
	guardfunc;
	if( !CanReceivePlayerMsg() )
		return;

	CHECK_MSGLEN( pMsg, MsgPosChange);
	MsgPosChange *pMsg1 = (MsgPosChange*)pMsg;
	CPosChangePackage package;
	package.LoadPackMsg(*pMsg1);

	SPosChangeInfo* pPosMsg = package.PopPosChangeInfo();

	const float fDistDragToPos = 20.f;

	while( pPosMsg )
	{
		/************************************************************************/
		/* 如果有合并包，即pPosMsg->chOptimize != Optimize_None，则遵循下面规则处理:
		1. 如果与目标位置之间有障碍物，则直接拽过去
		2. 移动距离超过fDistDragToPos，则直接拽过去
		3. 针对PACK_MSG_PLAYERMOVINGPOSANDDIR和PACK_MSG_PLAYERPOSANDDIR包，调用
		OnMsgPlayerMovingPosAndDir_TargetDir，先朝目标位置跑，到位后再调整方向*/
		/************************************************************************/
		CPlayer* pPlayer = FindByID(pPosMsg->nID);
		if( !pPlayer )
		{
			pPosMsg = package.PopPosChangeInfo();
			continue;
		}

		bool bDragtoPos = false;
		float fDisttoDest = 0;
		if( pPosMsg->chOptimize != SPosChangeInfo::Optimize_None && pPosMsg->nType != CPosChangePackage::PACK_MSG_PLAYERDIR )
		{
			D3DXVECTOR3 vCurPos = pPlayer->GetPos();
			D3DXVECTOR3 vDestPos = pPosMsg->vPos;
			CWorldTile* pCurrTile = CURRENTTILE;
			if ( !pCurrTile || (vDestPos.x < 0.f )|| (vDestPos.x > pCurrTile->GetWidth() - 1) || (vDestPos.y < 0.f) || (vDestPos.y > pCurrTile->GetDepth() - 1))
			{
				pPosMsg = package.PopPosChangeInfo();
				continue;
			}
			vCurPos.z = 0;
			vDestPos.z = 0;
			fDisttoDest = D3DXVec3Length(&(vDestPos - vCurPos));
			// 判断是否有阻挡，有则直接拽，（其他玩家用自动寻路比较费时，而且寻路结果如果还原得不正确反而造成更多问题，所以直接拽）
			swVec2f kOrgPosition(vCurPos.x,vCurPos.y);
			swVec2f kDestPosition(vDestPos.x,vDestPos.y);
			SwMap& swmap = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile()->ReachableMap();
			if (!swmap.CanMove(kOrgPosition,kDestPosition))
			{
				// 直接拽过去
				pPlayer->ReSetPos( pPosMsg->vPos.x, pPosMsg->vPos.y, pPosMsg->vPos.z );
				bDragtoPos = true;
			}

			// 移动距离大于fDistDragToPos，则直接拽
			if( !bDragtoPos && fDisttoDest >= fDistDragToPos )
			{
				// 直接拽过去
				pPlayer->ReSetPos( pPosMsg->vPos.x, pPosMsg->vPos.y, pPosMsg->vPos.z );
				bDragtoPos = true;
			}
		}

		if( bDragtoPos )
		{
			// 播跑步动作
			pPlayer->SwitchRunAnim();
		}
		else
			switch( pPosMsg->nType )
		{
			case CPosChangePackage::PACK_MSG_PLAYERMOVINGPOS:
				{
					MsgPlayerMovingPos msg;
					msg.header.stID = pPosMsg->nID;
					msg.vPos = pPosMsg->vPos;
					OnMsgPlayerMovingPos( &msg );
				}
				break;
			case CPosChangePackage::PACK_MSG_PLAYERMOVINGPOSANDDIR:
				{
					bool bFindPath = false;
					if( pPosMsg->chOptimize != SPosChangeInfo::Optimize_None )
					{
						// 朝向目标位置跑，跑到位再修正方向
						MsgPlayerMovingPosAndDir msg;
						msg.header.stID = pPosMsg->nID;
						msg.vPos = pPosMsg->vPos;
						msg.chDirX = pPosMsg->chDirX;
						msg.chDirY = pPosMsg->chDirY;
						msg.chDirZ = pPosMsg->chDirZ;
						OnMsgPlayerMovingPosAndDir_TargetDir( &msg );

						bFindPath = true;
					}
					if( !bFindPath )
					{
						MsgPlayerMovingPosAndDir msg;
						msg.header.stID = pPosMsg->nID;
						msg.vPos = pPosMsg->vPos;
						msg.chDirX = pPosMsg->chDirX;
						msg.chDirY = pPosMsg->chDirY;
						msg.chDirZ = pPosMsg->chDirZ;
						OnMsgPlayerMovingPosAndDir( &msg );
					}
				}
				break;
			case CPosChangePackage::PACK_MSG_PLAYERPOS:
				{
					MsgPlayerPos msg;
					msg.header.stID = pPosMsg->nID;
					msg.vPos = pPosMsg->vPos;
					OnMsgPlayerPos( &msg );
				}
				break;
			case CPosChangePackage::PACK_MSG_PLAYERDIR:
				{
					MsgPlayerDir msg;
					msg.header.stID = pPosMsg->nID;
					//msg.vPos = pPosMsg->vPos;
					msg.chDirX = pPosMsg->chDirX;
					msg.chDirY = pPosMsg->chDirY;
					msg.chDirZ = pPosMsg->chDirZ;
					OnMsgPlayerDir( &msg );
				}
				break;
			case CPosChangePackage::PACK_MSG_PLAYERPOSANDDIR:
				{
					bool bFindPath = false;
					{
						// 朝向目标位置跑，跑到位再修正方向
						MsgPlayerMovingPosAndDir msg;
						msg.header.stID = pPosMsg->nID;
						msg.vPos = pPosMsg->vPos;
						msg.chDirX = pPosMsg->chDirX;
						msg.chDirY = pPosMsg->chDirY;
						msg.chDirZ = pPosMsg->chDirZ;
						OnMsgPlayerMovingPosAndDir_TargetDir( &msg );

						bFindPath = true;
					}
				}
				break;
			case CPosChangePackage::PACK_MSG_PLAYERVERIFYPOS:
				{
					MsgPlayerVerifyPos msg;
					msg.header.stID = pPosMsg->nID;
					msg.vPos = pPosMsg->vPos;
					OnMsgPlayerVerifyPos( &msg );
				}
				break;
			case CPosChangePackage::PACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET:
				{
					MsgUnPlayerClosingToLockTarget msg;
					msg.header.stID = pPosMsg->nID;
					msg.LockTargetID = pPosMsg->nTargetID;
					msg.vPos = pPosMsg->vPos;
					OnMsgUnPlayerClosingToLockTarget( &msg );
				}
				break;
			case CPosChangePackage::PACK_MSG_UNPLAYERMOVINGTOPOS:
				{
					MsgUnPlayerMovingToPos msg;
					msg.header.stID = pPosMsg->nID;
					msg.vStartPos = pPosMsg->vPos;
					msg.vEndPos = pPosMsg->vEndPos;
					OnMsgUnPlayerMovingToPos( &msg );
				}
				break;
			case CPosChangePackage::PACK_MSG_UNPLAYERVERIFYPOS:
				{
					MsgUnPlayerVerifyPos msg;
					msg.header.stID = pPosMsg->nID;
					msg.vPos = pPosMsg->vPos;
					msg.chDirX = pPosMsg->chDirX;
					msg.chDirY = pPosMsg->chDirY;
					msg.chDirZ = pPosMsg->chDirZ;
					OnMsgUnPlayerVerifyPos( &msg );
				}
				break;
			default:
				{
					char msg[MAX_PATH] = {0};
					MeSprintf_s(msg,sizeof(msg)/sizeof(char) - 1  ,"Unknown message type, PlayerMgr_Msg.cpp, type:%d\n", pPosMsg->nType);
					OutputDebugString( msg );
				}
				break;
		}
		pPosMsg = package.PopPosChangeInfo();
	}

	unguard;
}


BOOL CPlayerMgr::ProcessCommand( const char* pszCommand )
{
	guardfunc;
	if( pszCommand == NULL )
		return FALSE;

	if( pszCommand[0] == 0 )
		return FALSE;
	
	if( !m_pMe )
		return FALSE;

	WordParser words;

	if( words.Parse( pszCommand ) == 0 )
		return FALSE;

	if( words.Compare(0, "DoSitDown"))
	{
		MsgReqChangeSubAction Req;
		if( !m_pMe->GetSitStatus() )
		{   //lyh 3gejia
			if(m_pMe->IsDead())
			{
             return FALSE; //死亡的时候按坐下，不需要任何提示
			}

			if(m_pMe->IsMorph())
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
				return FALSE;
			}

			if( m_pMe->HasFightFlag(eFighting) )
			{
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString( eText_SitFailed_InFighting ) );
				return FALSE;
			}
			if( m_pMe->IsInWater() )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
				return FALSE;
			}
			if( m_pMe->IsJumping() )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
				return FALSE;
			}
			if( m_pMe->IsMounting() )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
				return FALSE;
			}

			if( !m_pMe->IsPlayStandAnim() && !m_pMe->IsPlaySitAnim() )
			{
				Req.action = CS_SubAction_SitDown;	// 可以坐下
				GettheNetworkInput().SendMsg( &Req );
			}
		}
		else if( m_pMe->GetSitStatus() && !m_pMe->HasFightFlag(eFighting) )	
		{

			if( m_pMe->IsMultiMounting() )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
				return FALSE;
			}

			if( !m_pMe->IsPlaySitAnim() || m_pMe->GetSitInterrupt() )
			{
				Req.action = CS_SubAction_Normal;	// 非战斗状态，可站起
				GettheNetworkInput().SendMsg( &Req );
			}
		}
		return TRUE;
	}

	return FALSE;

	unguard;
}

void CPlayerMgr::OnMsgChangeSubAction(Msg* pMsg)
{
	guardfunc;
	MsgRetChangeSubAction* pChange = (MsgRetChangeSubAction*)pMsg;
	CPlayer *pPlayer = FindByID( pChange->stID1 );
	if( pPlayer )
	{
		switch( pChange->action )
		{
		case CS_SubAction_SitDown:
			if( !pPlayer->GetSitStatus() )
			{
				//坐下
				pPlayer->StopMoving(TRUE);
				pPlayer->SetSitStatus(1);
				pPlayer->SetSitInterrupt(0);
				pPlayer->SwitchSitAnim( 0xFFFFFFFF );
				// play sound
				if( pPlayer == theHeroGame.GetPlayerMgr()->GetMe() )
				{
					if( pPlayer->GetSex() == Sex_Male )
					{
						PlaySoundConfig( SoundConfig::EST_SitM );
					}
					else
					{
						PlaySoundConfig( SoundConfig::EST_SitF );
					}
				}
			}
			break;
		case CS_SubAction_Normal:
			// 站起
			if( pPlayer->GetSitStatus() )
			{
				pPlayer->SetSitStatus(0);
				if( pPlayer->GetSitInterrupt() )	// 坐下状态已被打断
				{
					pPlayer->SetSitInterrupt(0);
				}
				else
				{
					if( pPlayer->IsMoving() )
					{
						pPlayer->SwitchRunAnim();
					}
					else
					{
						pPlayer->SwitchStandAnim();
					}
				}
			}
			break;
		case CS_SubAction_FightAction:
			// 战斗中
			if( pPlayer->GetSitStatus() )
			{
				pPlayer->SetSitStatus(0);
				if( pPlayer->GetSitInterrupt() )	// 坐下状态已被打断
				{
					pPlayer->SetSitInterrupt(0);
				}
				else
				{
					if( pPlayer->IsMoving() )
					{
						pPlayer->SwitchRunAnim();
					}
					else
					{
						pPlayer->SwitchStandAnim();
					}
				}
			}
			break;
		case CS_SubAction_Embrace:  // 拥抱互动动作
			{
				CPlayer *pTargetPlayer = FindByID( pChange->stID2 );
				if( pTargetPlayer )
				{
					pPlayer->SetInteractionMaster(-1);
					pPlayer->SwitchEmbraceAnim();
					pTargetPlayer->SetInteractionMaster(pPlayer->GetID());  // 在SwitchEmbraceAnim()之前调SetInteractionMaster()
					pTargetPlayer->SwitchEmbraceAnim();
					float fDir = 0.f;
					fDir = atan2f(pPlayer->GetPos().y - pTargetPlayer->GetPos().y, pPlayer->GetPos().x - pTargetPlayer->GetPos().x );
					if( fDir > D3DX_PI )
						fDir -= D3DX_PI*2;
					if( fDir < 0 )
						fDir += D3DX_PI*2;
					pTargetPlayer->SetDir(fDir);
					pTargetPlayer->SetCurDir(fDir);
					pTargetPlayer->SetUpperDir(fDir);
					pTargetPlayer->SetLowerDir(fDir);
					pTargetPlayer->SetCurUpperDir(fDir);
					pTargetPlayer->SetCurLowerDir(fDir);

				}
			}
			break;
		case CS_SubAction_Restore:
			{
				pPlayer->SwitchMedicalAnim();
			}
			break;
		}
	}

	unguard;
}

// 接收到单步移动消息
void CPlayerMgr::OnMsgMoveAStep ( Msg* pMsg )
{
	guardfunc;
#ifndef SINGLESTEPLOGIC
	return;
#endif
	CHECK_MSGLEN( pMsg, MsgMoveAStep);
	MsgMoveAStep *pMove = ( MsgMoveAStep* )pMsg;
	if( m_pMe && pMove->sNpcID != m_pMe->GetID() )
	{
		//不处理自己的
		CPlayer *pPlayer = FindByID(pMove->sNpcID);
		if( pPlayer )
		{
			pPlayer->GetActionQueue()->Push_Walk( pMove->byDir );
		}
	}
	unguard;
}

void CPlayerMgr::OnMsgPermitMove( Msg* pMsg )
{

	guardfunc;
	// 如果已经是允许移动状态，则不理会，
	// 因为这条消息已经失效了
	if( !m_pMe )
		return;
	if( m_pMe->IsServerPermitMove() )
		return;
	CHECK_MSGLEN( pMsg, MsgPermitMove);
	MsgPermitMove *permit = ( MsgPermitMove* )pMsg;
	if( _HAS_FLAG( permit->dwReason, eREASON_NOTPERMIT ) )
		m_pMe->ServerPermitMove( FALSE );
	else
		m_pMe->ServerPermitMove( TRUE );
	unguard;
}

// 接收到位置确认消息
void CPlayerMgr::OnMsgVerifyPos( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgVerifyPos);
	OnVerifyPos( (MsgVerifyPos*)pMsg );
	unguard;
}
//坐标同步
void CPlayerMgr::OnMsgSyncPos( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgSyncPos);
	OnSyncPos( (MsgSyncPos*)pMsg );
	unguard;
}

void CPlayerMgr::OnSyncPos(MsgSyncPos* pMsgSyncPos)
{
	guardfunc;
	//对于自己的同步不处理
	CHECK_MSGLEN( pMsgSyncPos, MsgSyncPos);
	if (GetMe() && GetMe()->GetID() == pMsgSyncPos->sNpcID)
		return;
	//
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(pMsgSyncPos->sNpcID);
	if (NULL == pPlayer)
		return;

	GetErrorLog()->logString( "不处理同步SyncPos" );

	unguard;
}

void CPlayerMgr::OnVerifyPos(MsgVerifyPos* pMsgVerifyPos)
{
	guardfunc;

	if( !pMsgVerifyPos )
		return;
	CHECK_MSGLEN( pMsgVerifyPos, MsgVerifyPos);
	if( !m_pMe )
		return;

	if( m_pMe->IsEmbraceAnim() )
		return;

	// 玩家被服务器拽位置，如果是跳跃状态，则设成非跳跃
	if( m_pMe->IsJumping() )
	{
		m_pMe->StopJump();
	}

	m_pMe->SetPos( pMsgVerifyPos->x, pMsgVerifyPos->y, 0 );
	thePlayerRole.SetLastPos(pMsgVerifyPos->x, pMsgVerifyPos->y);   // 不重复发给服务器
	m_pMe->SwitchActionStatus(CPlayerStatus::esk_Idle,CStatusTimer::NoLimitDelay);
	unguard;
}

//////////////////////////////////////////////////////////////////////////

// 接收到确认移动指令
CPlayer* CPlayerMgr::SawOneNPC( Msg *pMsg )
{
	guardfunc;
	if( m_pMe )
	{
		if( pMsg->header.stID == m_pMe->GetID() )
		{
			assert( false );
			char temp[1024];
			MeSprintf_s(temp,1024,"SawOneNPC ID和Me ID相同 %d!",pMsg->header.stID);
			LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
			return NULL;
		}
	}
	CHECK_MSGLEN_NULL( pMsg, MsgNPCEnterMySight);

	MsgNPCEnterMySight *pMsg1 = (MsgNPCEnterMySight *)pMsg;

	// 判断是否在同个（动态）地图ID
	if( thePlayerRole.GetGameMapId() != pMsg1->nMapID )
		return NULL;

	CPlayer* pPlayer = AddPlayer( pMsg->header.stID,pMsg1->stCharType,false );

	uint32 ModeID = pMsg1->ModeID;

	if( pPlayer )
	{
		pPlayer->SetBeLongID(pMsg1->BelongID);
		pPlayer->SetInfluence(pMsg1->influence);
		pPlayer->SetBodySize( 1.0f );
		pPlayer->SetShowFlag( pMsg1->dwShowFlag );
		pPlayer->SetCharType( pMsg1->stCharType );
		pPlayer->JumpToMapPos( pMsg1->fX,pMsg1->fY, pMsg1->fZ);
		pPlayer->SetDirInt( pMsg1->byDir );
		pPlayer->SetRealCountry( pMsg1->ucCountry );

		// NPC隐身
		if( /*pMsg1->stCharType == Object_Player &&*/ !pMsg1->bShow )
		{
			pPlayer->SetHide(true);
		}
		pPlayer->SetMask( pMsg1->bMask );

		float fDir = atan2f( pMsg1->fDirY, pMsg1->fDirX );
		pPlayer->SetDir( fDir );
		pPlayer->SetLowerDir( fDir );
		pPlayer->SetUpperDir( fDir );
	
		pPlayer->SetGuildId( GuildDefine::InitID );
		pPlayer->SetSitStatus(0);
		pPlayer->SetFightStatus(1);
		pPlayer->SetToFightStatus(1);
		pPlayer->SetLevel( pMsg1->stLevel );
		pPlayer->SetName( pMsg1->szDisplayName );
		pPlayer->SetNpcID( pMsg1->npcId );	
		pPlayer->HideSpeicalNpc();

		const char* pszSkinName = NULL;
		if( Object_Monster == pMsg1->stCharType )
		{
			pPlayer->SetCharType(Object_Monster);

			int iMonsterID = pMsg1->stId;
			ItemDefine::SMonster *pMonster;
			pMonster = GettheItemDetail().GetMonsterById( iMonsterID );

			char* pName = NULL;
			char* pSkin = NULL;
			char* pWeaponSound = NULL;
			char* pArmourSound = NULL;

			if( pMonster )
			{
				pName = (char*)pMonster->GetName();
				pSkin = (char*)pMonster->GetSkin();
				pWeaponSound = (char*)pMonster->GetWeaponSound();
				pArmourSound = (char*)pMonster->GetArmourSound();

				pPlayer->SetName( pName);
				pPlayer->SetWeaponSound( pWeaponSound );
				pPlayer->SetArmourSound( pArmourSound );
				pPlayer->SetMonsterID( iMonsterID );
				pPlayer->SetMovingStep( pMonster->fMovingStep );
				pPlayer->SetRunStep( pMonster->fRunStep );
				pPlayer->SetFourFoot( pMonster->nIsHaveFourFoot );
				pPlayer->SetTwoHalfBody( pMonster->nIsHaveTwoHalfBody );
				pPlayer->SetFinalRenderAlpha( pMonster->fAlpha );
				pPlayer->SetDefaultFinalRenderAlpha( pMonster->fAlpha );

				if (pMsg1->nSubMonsterType == Object_MonsterNurturePet)
					pPlayer->SetTitle(pMsg1->szTitleName);
				else
				{
					if (strlen(pMonster->GetTitle()) > 0)
					{
						pPlayer->SetTitleColor(0xff00ff00);
						pPlayer->SetTitle(pMonster->GetTitle());
					}
				}

				if( pMonster->visualType == ItemDefine::EMVT_Normal )
					pPlayer->SetVisibleToOtherPlayer(TRUE);
				else if( pMonster->visualType == ItemDefine::EMVT_MasterVisual )
				{
					if( GetMe() && GetMe()->GetID() == pMsg1->stMasterId )
						pPlayer->SetVisibleToOtherPlayer(TRUE);
					else
						pPlayer->SetVisibleToOtherPlayer(FALSE);
				}
			}

			if( !pMonster )
				pPlayer->SetModelId( -1 );
			else
			{
				pPlayer->SetModelId( ModeID==0?pMonster->iModelID:ModeID );
				pszSkinName = pMonster->GetSkin();
			}

			pPlayer->SetMoveRate( pMsg1->fMoveRate );
			pPlayer->SetNormalAttackRate( pMsg1->fNormalAttackRate );
			pPlayer->SetHPInfo(pMsg1->nHp, pMsg1->nHpMax);

			if( pMonster )
			{
				pPlayer->SetCreatureSound( (char*)pMonster->GetCreatureSound() );
				pPlayer->SetBodySize( pMonster->fBodySize );
				pPlayer->SetBodyLengthSize( pMonster->fBodyLengthSize );
			}

			pPlayer->SetPhysicDefMax( pMsg1->stPhysicDef );
			pPlayer->SetPhysicDefMin( pMsg1->stPhysicDef );
			pPlayer->SetDodge( pMsg1->stDodge );
			pPlayer->SetTargetLevel( pMsg1->stLevel );
			pPlayer->SetLuck( pMsg1->stLuck );
			pPlayer->SetMonsterType( pMsg1->stMonsterType );
			pPlayer->SetSubMonsterType(pMsg1->nSubMonsterType);
			pPlayer->SetMasterID( pMsg1->stMasterId, (m_pMe && pMsg1->stMasterId == m_pMe->GetID()) );
			if (pMsg1->nSubMonsterType == Object_MonsterProtected)
			{
				// 是否能骑
				if (pMsg1->bIsCanRide)
				{
					pPlayer->SetIsCanRide(true);

					// 如果镖车是我的才显示显示镖车控制界面
					if (pMsg1->stMasterId == m_pMe->GetID())
					{
						s_CUI_ID_FRAME_OnBiaoChe.SetBiaoche(pPlayer);
						s_CUI_ID_FRAME_OnBiaoChe.SetVisable(true);
					}					
				}
				else
				{
					pPlayer->SetIsCanRide(false);
				}

				//LYH++ 保护对象前面加上主人名字
				CPlayer* pMasterPlayer = FindByID( pMsg1->stMasterId ); //找主人
				if(pMasterPlayer)
				{
					char NameBuf[64] = {0};
					sprintf(NameBuf,theXmlString.GetString(eClient_MonsterTitle) ,pMasterPlayer->GetName());
					pPlayer->SetTitle(NameBuf);

				}
			}

			// 是否召唤兽
			if (pMonster && pMonster->stMonsterType == eMT_Pet)
			{
				pPlayer->SetPet(TRUE);

				if (m_pMe && pMsg1->stMasterId == m_pMe->GetID())
				{
					s_CUI_ID_FRAME_BaseProperty.SetPetAIType(CUI_ID_FRAME_BaseProperty::TYPE_PETAIDEFEND);
					s_CUI_ID_FRAME_MAIN.RefeashHotKey();
					s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
					s_CUI_ID_FRAME_SKILL.RefreshCommon();
					s_CUI_ID_FRAME_Target.ForceUpdate();
				}
			}

			pPlayer->SetMasterName(pMsg1->szDisplayName);

			CPlayer* pMasterPlayer = FindByID( pMsg1->stMasterId );
			if( pMasterPlayer )
			{
				if( pMasterPlayer == m_pMe )
				{
					if( pMsg1->stMonsterType == eMT_IllusionMonster )
					{
						pPlayer->SetMasterID( pMasterPlayer->GetID(), FALSE );
					}
					else
					{
						if (pPlayer->IsPet())
						{
							
							if (pPlayer->GetSubMonsterType() ==Object_MonsterPet )//召唤宠
							{
								pMasterPlayer->SetSubPetID(pPlayer->GetID());
							}
							else
							{
								pMasterPlayer->SetPetID( pPlayer->GetID() );
							}
						}
						pPlayer->SetMasterID( pMasterPlayer->GetID(), TRUE );
					}
				}
				else
				{
					if( pMsg1->stMonsterType == eMT_IllusionMonster )
					{
						pPlayer->SetMasterID( pMasterPlayer->GetID(), FALSE );
					}
					else
					{
						if (pPlayer->IsPet())
							if (pPlayer->GetSubMonsterType() ==Object_MonsterPet )//召唤宠
							{
								pMasterPlayer->SetSubPetID(pPlayer->GetID());
							}
							else
							{
								pMasterPlayer->SetPetID( pPlayer->GetID() );
							}

						pPlayer->SetMasterID( pMasterPlayer->GetID(), FALSE );
					}
				}

				if( pMsg1->stMonsterType == eMT_IllusionMonster )
				{
					pPlayer->SetCurRenderAlpha( 0 );
					pPlayer->SetCharType( Object_Player );
					pPlayer->SetIsFirstAttack( pMasterPlayer->IsFirstAttack() );
					pPlayer->SetPKKillValue( pMasterPlayer->GetPKKillValue() );
					pPlayer->SetCurRenderAlpha( 1 );
					pPlayer->JumpToMapPos( pMasterPlayer->GetPos().x, pMasterPlayer->GetPos().y, pMasterPlayer->GetPos().z );
					pPlayer->SetName( pMasterPlayer->GetName() );
					pPlayer->SetGuildName( pMasterPlayer->GetGuildName() );
					pPlayer->SetLevel( pMasterPlayer->GetLevel() );
					pPlayer->SetCountry( pMasterPlayer->GetCountry() );
					pPlayer->SetModelId( ModeID==0?pMasterPlayer->GetModelId():ModeID  );
					pPlayer->SetProfession( pMasterPlayer->GetProfession() );			//职业
					pPlayer->SetSex( pMasterPlayer->GetSex() );							//性别
					pPlayer->SetEquip( pMasterPlayer->GetEquip() );
					pPlayer->SetHairColorIndex( pMasterPlayer->GetHairColorIndex() );
					pPlayer->SetRunStep( pMasterPlayer->GetRunStep() );
					pPlayer->SetMovingStep( pMasterPlayer->GetMovingStep() );
					pPlayer->SetMoveRate( pMasterPlayer->GetMoveRate() );

					if( pMasterPlayer->HasFightFlag( eFighting ) )
					{
						pPlayer->AddFightFlag( eFighting );
						pPlayer->SwitchIdleAnim();
					}

					if( pMasterPlayer->GetID() == GetLockPlayerID() )
					{
						SetLockNpc( pPlayer->GetID() );
						SetLockPlayerID( pPlayer->GetID() );
					}
				}
				else
				{
					pPlayer->UpdateCurZPos();
					PlayEffect( "Common\\SummonEffect.ini", pPlayer );
				}
			}
		}
		else
		{
			pPlayer->SetMoveRate( pMsg1->fMoveRate );
			pPlayer->SetMovingStep( pMsg1->fMoveStep );
			pPlayer->SetRunStep( pMsg1->fMoveStep );
			pPlayer->SetModelId( ModeID==0?pMsg1->stId:ModeID );
		}
		

		// NPC血量处理 [12/28/2010 zhangjiayi]
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pPlayer->GetNpcID());
		if( ( pMsg1->stCharType == Object_Npc ) && pInfo && ( pInfo->_nType == eNT_Patrol ) )
		{
			pPlayer->SetHPInfo( pMsg1->nHp, pMsg1->nHpMax );
			if( pMsg1->nHp <= 0 )// NPC dead
			{
				pPlayer->SetCharDead( true );				
			}
		}

		pPlayer->AutoCS( pszSkinName );
		if( pszSkinName && pPlayer->GetAnim() )
		{
			pPlayer->GetAnim()->ChangeAvatarSetting( pszSkinName );
		}

        if(pMsg1->influence != 255 &&pPlayer->GetAnim())
        { 
            pPlayer->SetActionFluence(pMsg1->influence);
            pPlayer->SetUpdateActionFluence(true);
        }
        pPlayer->SetTypeStatus(pMsg1->nTypeStatus);

		///////////////////////////////////
		MsgQueryCharInfo TmpMsg;
		TmpMsg.stChar = pMsg->header.stID;
		GettheNetworkInput().SendMsg( &TmpMsg,TmpMsg.GetLength() );  
	}

	return pPlayer;
	unguard;
}

CPlayer* CPlayerMgr::SawOnePlayer( Msg *pMsg )
{
	guardfunc;
	if ( m_pMe && pMsg->header.stID == m_pMe->GetID() )
	{
		assert( false );
		char temp[1024];
		MeSprintf_s(temp,1024,"SawOnePlayer ID和Me ID相同 %d!",pMsg->header.stID);
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
		return NULL;
	}

	MsgPlayerEnterMySight *pMsg1 = (MsgPlayerEnterMySight *)pMsg;

	// 判断是否在同个（动态）地图ID
	if ( thePlayerRole.GetGameMapId() != pMsg1->nMapID )
		return NULL;

	guard(test1);
	CPlayer* pSamePlayer = FindPlayerByCharacterID( pMsg1->dwPlayerCharacterID );
	if ( pSamePlayer )
	{
		pSamePlayer->Remove( HQ_TimeGetTime() );
		PlayerExit( pSamePlayer->GetID() );
		pSamePlayer->ExcuteClearActionQueue();
		RemovePlayerFromActiveList( pSamePlayer->GetID() );	

		if ( pSamePlayer->Release() )
		{
			DestroyPlayer( pSamePlayer );
			delete pSamePlayer;
		}
		else
		{
			AddPlayerToKeepList( pSamePlayer, TRUE );
		}
	}
	unguard;

	CPlayer* pPlayer = AddPlayer( pMsg->header.stID,pMsg1->stCharType,false );
	if ( pPlayer )
	{
		pPlayer->SetPlayerScale(pMsg1->fModelPercent);
		pPlayer->SetTeamId( pMsg1->teamId );
		pPlayer->SetTeamPosition( pMsg1->teamPosition );
		pPlayer->SetCharacterID( pMsg1->dwPlayerCharacterID );
		pPlayer->SetCharType( pMsg1->stCharType );
		pPlayer->JumpToMapPos( pMsg1->fX, pMsg1->fY, pMsg1->fZ );

		pPlayer->SetDirInt( pMsg1->byDir );

		float fDir = atan2f( pMsg1->fDirY, pMsg1->fDirX );
		pPlayer->SetDir( fDir );
		pPlayer->SetLowerDir( fDir );
		pPlayer->SetUpperDir( fDir );

		pPlayer->m_vDir.x = pMsg1->fDirX;
		pPlayer->m_vDir.y = pMsg1->fDirY;
		pPlayer->m_vDir.z = 0;

		//pPlayer->SetCountry( pMsg1->ucCountry );

		// 上面的Country是阵营，以下才是真的 国家 和 国家称号		added by zhuomeng.hu		[9/10/2010]
		pPlayer->SetRealCountry( pMsg1->uchCountryID );
		pPlayer->SetCountryTitle( pMsg1->uchCountryTitle );
        pPlayer->SetPortraitId( pMsg1->headPicId );
        /*pPlayer->SetGuildName( pMsg1->szGuildName );*/

		pPlayer->SetGuildId( pMsg1->dwGuildId ,FALSE);
		pPlayer->SetGangPosition( pMsg1->nGuildPosition );

		if (thePlayerRole.GetGuildById(pMsg1->dwGuildId))
		{
			pPlayer->SetGuildName(thePlayerRole.GetGuildById(pMsg1->dwGuildId)->GetName());
		}

		pPlayer->SetFamilyID( pMsg1->nFamilyID );

		pPlayer->SetFamilyPos( pMsg1->familyPosition );

		pPlayer->SetInfluence(pMsg1->influence);

        pPlayer->SetPKType( pMsg1->nPKMode );

		pPlayer->SetBodySize( 1.0f );

		pPlayer->SetFightStatus(pMsg1->fight_status);//战斗模式
		pPlayer->SetToFightStatus(pMsg1->fight_status);//战斗模式
		pPlayer->SetSex(pMsg1->sex);//性别
		switch( pMsg1->sex )
		{
		case Sex_Male:
			pPlayer->SetCreatureSound( "male" );
			break;
		case Sex_Female:
			pPlayer->SetCreatureSound( "female" );
			break;
		}
		pPlayer->SetProfession(pMsg1->profession);//职业

		if (pMsg1->bIsFlyMoving)
		{
			pPlayer->SetUncontrolMoving(true,true);
		}
		// 之前这个显示心情的Flag没有设置
		pPlayer->ShowSignature(_HAS_FLAG( pMsg1->showFlag, SCharVisual::EShowFlagType_Signature));
		pPlayer->ShowHelmet(_HAS_FLAG( pMsg1->showFlag, SCharVisual::EShowFlagType_Helmet));
		pPlayer->ShowAecpratove(_HAS_FLAG( pMsg1->showFlag, SCharVisual::EShowFlagType_Aecpratove));
		pPlayer->SetShowHero(_HAS_FLAG( pMsg1->showFlag, SCharVisual::EShowFlagType_Hero));
		pPlayer->ShowRankTitle(_HAS_FLAG( pMsg1->showFlag, SCharVisual::EShowFlagType_RankTitle));
		if(pMsg1->talismanId != InvalidLogicNumber)
		{
			pPlayer->SetTalismanById(pMsg1->talismanId);
		}

		//脸和头发单独处理
		pPlayer->SetEquipPart(eKeyAll_Hair, pMsg1->hairId);
		pPlayer->SetEquipPart(eKeyAll_Face, pMsg1->faceId);
		if (pMsg1->hero_id != INVALID_HERO_ID)
		{
			pPlayer->SetHeroID(pMsg1->hero_id);
			pPlayer->ShapeShift();
		}

		pPlayer->EquipByItemID(pMsg1->stVisualItemID, pMsg1->equipIntensifyTime, pMsg1->equipLevel, pMsg1->equipElements );
		pPlayer->SetModelId( pMsg1->stModelID);
		pPlayer->SetMoveRate( pMsg1->fMoveRate );
		pPlayer->SetNormalAttackRate( pMsg1->fNormalAttackRate );
		//
		pPlayer->SetHPInfo(pMsg1->nHp, pMsg1->nHpMax);
		pPlayer->SetDefAvaterIndex( pMsg1->defaultModelIndex);

		pPlayer->AutoCS();
		if ( pMsg1->nDriverId == pPlayer->GetID() )
		{
			//驾驶员
			pPlayer->MountMonster( pMsg1->shDromeId, pMsg1->nMountLevel, FALSE );
		}
		else if( pMsg1->shDromeId != 0 && pMsg1->nDriverId != ErrorUnsignedShortID )
		{
			//乘客
			CPlayer* driver = FindByID( pMsg1->nDriverId);
			if ( driver != NULL )
			{
				pPlayer->SetCarrierState(true);
				pPlayer->SetCarrierPos(pMsg1->nDromePos);
				pPlayer->SetCarrierDriver(driver->GetID());
				pPlayer->SetOthersPet(true);

				driver->AddPassenger(pPlayer->GetID());
			}
		}
		
		pPlayer->SetSitStatus( 0 );
		//pPlayer->SetIsFirstAttack(pMsg1->bIsFirstAttack);
		pPlayer->SetPKKillValue(pMsg1->nPKValue);
		pPlayer->SetLevel(pMsg1->stLevel);

        // added, jiayi, [2009/9/21]
        // 称号
        pPlayer->SetTitleTargetName( pMsg1->szTitleTargetName );
        pPlayer->SetTitleInfoById( pMsg1->nCurrentTitleID );
		pPlayer->SetSignature(pMsg1->szSignature);
		pPlayer->SetRankTitleId(pMsg1->shRankTitleId);

        /*pPlayer->SetInfluence(pMsg1->influence);*/

		//设置大载体
		//if(pMsg1->bigShipId != ErrorUnsignedShortID)
		//{
		//	pPlayer->SetCarrierState(true);
		//	pPlayer->SetCarrierPos(pMsg1->npcShipPos);
		//	pPlayer->SetCarrierDriver(pMsg1->bigShipId);
		//}
		//else
		//	pPlayer->SetCarrierState(false);

		switch( pMsg1->ucCharStatus )
		{
		case MsgPlayerEnterMySight::charstatus_death:
			pPlayer->AddDeathTask();
			break;
		case MsgPlayerEnterMySight::charstatus_sitdown:
			pPlayer->SetSitStatus( 1 );
			break;
		case MsgPlayerEnterMySight::charstatus_normal_draw:
			if( !pPlayer->HasFightFlag(eFighting) && !pPlayer->IsMounting() && !pPlayer->IsFightPose() )
			{
				pPlayer->SetFightPose(TRUE);
				pPlayer->SwitchScabbardAnim();
			}
			else if( pPlayer->IsMounting() )
			{
				if( pPlayer->IsHaveWeapon() && pPlayer->GetProfession() == EArmType_Assassin && !pPlayer->GetLiftFlagStatus() )
				{
					if( m_pMe && IsFlagModel(m_pMe->GetWeaponModelID()) )
					{
						pPlayer->SetLiftFlagStatus(1);
						pPlayer->SwitchLiftFlagAnim();
					}
				}
			}
			break;
		case MsgPlayerEnterMySight::charstatus_normal_drawin:
			if( !pPlayer->HasFightFlag(eFighting) && pPlayer->IsFightPose() )
			{
				pPlayer->SetFightPose(FALSE);
				pPlayer->SwitchScabbardAnim();
			}
			else if( pPlayer->IsMounting() )
			{
				if( pPlayer->IsHaveWeapon() && pPlayer->GetProfession() == EArmType_Assassin && pPlayer->GetLiftFlagStatus() )
				{
					if( m_pMe && IsFlagModel(m_pMe->GetWeaponModelID()) )
					{
						pPlayer->SetLiftFlagStatus(0);
						if( pPlayer->GetAnim() )
							pPlayer->GetAnim()->ForceCurrAnimLoopTime(-1,TRUE);
					}
				}
			}
			break;
		default:
			break;
		}

		if( pMsg1->bySubAction == CS_SubAction_SitDown )
		{
			pPlayer->SwitchSitLoopAnim( 0xFFFFFFFF );			
		}

		// 正在采集npc，播放动作
		if( pMsg1->stAction > 0 )
		{
			pPlayer->SetWithNPCAnimInfo( pMsg1->stAction, pMsg1->nActionPlayTime );			
		}

		MsgQueryCharInfo TmpMsg;
		TmpMsg.stChar = pMsg->header.stID;
		GettheNetworkInput().SendMsg( &TmpMsg,TmpMsg.GetLength() );
	}
	return pPlayer;
	unguard;
}

void CPlayerMgr::OnMsgHPMPModify(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgUpHpAndMp);
	MsgUpHpAndMp *pmsg = (MsgUpHpAndMp*)pMsg;
	CPlayer* pPlayer = FindByID( pMsg->header.stID );

	if (pPlayer == NULL)
	{
		return;
	}

 	if (pmsg->nHpUp != 0)
 	{
 		pPlayer->OnShowFlyText(pPlayer,pPlayer,ItemDefine::balancetype_restorehpmp,pmsg->nHpUp,pmsg->nHpUp);
 	}
	if (pmsg->nMpUp != 0)
	{
		pPlayer->OnShowFlyText(pPlayer,pPlayer,ItemDefine::balancetype_restorehpmp,pmsg->nMpUp,pmsg->nMpUp);
	}
	unguard;
}

void	CPlayerMgr::OnMsgFirstEvent(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgReqFirstTip);
	MsgReqFirstTip* pmrf = (MsgReqFirstTip*)pMsg;
	unguard;
}
void	CPlayerMgr::OnMsgGetReputeName(Msg* pMsg)
{
}

void	CPlayerMgr::OnMsgDelReputeName(Msg* pMsg)
{

}

//void CPlayerMgr::OnMsgGetGuildIcon(Msg* pMsg)		//sbw_add_guildicon		接受Tga数据
//{
//	guardfunc;
//	CHECK_MSGLEN( pMsg, MsgReqTgaIcon);
//	MsgReqTgaIcon* ptga = (MsgReqTgaIcon*)pMsg;
//	CPlayer* pPlayer = FindByID(ptga->header.stID);
//	if (pPlayer)
//	{
//		pPlayer->RegisterGuildIcon(ptga->stFlag.ulCRC,ptga->stFlag.bFlagData,4140);
//	}
//	unguard;
//}

void CPlayerMgr::OnMsgInviteAddRelationAck(Msg* pMsg)	//sbw_add_brother
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgInviteRelationAck);
	MsgInviteRelationAck*pbrother = (MsgInviteRelationAck*)pMsg;
	unguard;
}


// 接收到有NPC进入我的视野
void CPlayerMgr::OnMsgNPCEnterMySight( Msg* pMsg, BOOL bCheckLoadingCost /*= TRUE*/ )
{
//1234
//  	return;
	guardfunc;
	if( !CanReceivePlayerMsg() )
		return;

	//谁进入视野
	BOOL bCanLoad = TRUE;
	DWORD timeBegin = HQ_TimeGetTime();
	if( bCanLoad )
	{
		SawOneNPC( pMsg );
	}

	if( bCheckLoadingCost )
	{
		m_nSawPlayerNPCCostTime += HQ_TimeGetTime() - timeBegin;
	}

	unguard;
}


// 接收到有NPC进入我的视野(单步移动状态的)
void CPlayerMgr::OnMsgNPCEnterMySightMovingAStep   ( Msg* pMsg )
{
	guardfunc;	
	unguard;
}


// 接收到有玩家进入我的视野
void CPlayerMgr::OnMsgPlayerEnterMySight( Msg* pMsg, BOOL bCheckLoadingCost /*= TRUE*/ )
{
	guardfunc;
	if ( !CanReceivePlayerMsg() )
		return;

	// 谁进入视野
	BOOL bCanLoad = TRUE;
	DWORD timeBegin = HQ_TimeGetTime();
	if ( bCanLoad )
	{
		CPlayer* pPlayer = SawOnePlayer( pMsg );
		if ( pPlayer )
		{
			CHECK_MSGLEN( pMsg, MsgPlayerEnterMySight);
			MsgPlayerEnterMySight *pMsg1 = (MsgPlayerEnterMySight *)pMsg;
		}
	}

	if ( bCheckLoadingCost )
	{
		m_nSawPlayerNPCCostTime += HQ_TimeGetTime() - timeBegin;
	}

	unguard;
}

// 接收到有人进入我的视野(单步移动状态的)
void CPlayerMgr::OnMsgPlayerEnterMySightMovingAStep   ( Msg* pMsg )
{
	guardfunc;		
	unguard;
}

//接收到有Player进入视野的包
void CPlayerMgr::OnMsgPlayerEnterMySightPack(Msg* pMsg)
{
	//1234
// 	return;
	guardfunc;
	if (pMsg == NULL)
	{
		return;
	}
	if( !CanReceivePlayerMsg() )
		return;

	CHECK_MSGLEN( pMsg, MsgEnterMySightPack);
	MsgEnterMySightPack* pPack = static_cast<MsgEnterMySightPack*>(pMsg);
	static CEnterMySightPackage unpacker;
	unpacker.LoadPackMsg(*pPack);

	while (!unpacker.IsEmpty())
	{
		MsgPlayerEnterMySight* pEnterMySight = unpacker.PopEnterMySight();
		OnMsgPlayerEnterMySight(pEnterMySight);
	}
	unguard;
}

// 接收到物品进入我的视野
void CPlayerMgr::OnMsgItemEnterMySight          ( Msg* pMsg )
{
	//1234
//  	return;
	guardfunc;
	if( !CanReceivePlayerMsg() )
		return;

	SawOneItem( pMsg );   
	unguard;
}

void CPlayerMgr::OnMsgDamageOfEffect( Msg*pMsg )
{
	guardfunc;
	return;
	unguard;
}

void CPlayerMgr::OnMsgBuildingEnterMySight( Msg *pMsg )
{
	guardfunc;

	unguard;
}

void CPlayerMgr::OnMsgEffectEnterMySight( Msg *pMsg )
{
	guardfunc;
    if(!pMsg) return;
	MsgEffectEnterMySight *pMsg1 = (MsgEffectEnterMySight *)pMsg;

	if( thePlayerRole.GetGameMapId() != pMsg1->nMapID )
		return ;

	CPlayer* pPlayer = AddPlayer( pMsg->header.stID,Object_Effect,false );

	uint32 ModeID = 4243;

	EFFECTCHARCONFIG _Config;
	if(theEffectCharConfig.FindEffectCharConfigBySkillID(_Config,pMsg1->ustSkillID))
	   ModeID = _Config.ModelID;

	float effectChrScale = 1.0f;
	//获得 effectchar 的大小缩放 
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( pMsg1->ustSkillID, pMsg1->ustSkillLevel);
	if (pSkill)
	{
		effectChrScale = pSkill->fAOEradius;
	}
	 

	if( pPlayer )
	{	
		pPlayer->SetEffectCharSkillID(pMsg1->ustSkillID);
		pPlayer->SetCharType( Object_Effect );
		pPlayer->SetEffectCharSkillID(pMsg1->ustSkillID);
		pPlayer->JumpToMapPos( pMsg1->x,pMsg1->y, 0);
		pPlayer->SetModelId( ModeID );
		pPlayer->SetPlayerScale(effectChrScale);
		pPlayer->UpdateCurZPos();
		pPlayer->AutoCS();
		if (m_pMe)
		{   //设置主人
			pPlayer->SetMasterID( pMsg1->MasterID, (m_pMe && pMsg1->MasterID == m_pMe->GetID()) );
		}
	
		MsgQueryCharInfo TmpMsg;
		TmpMsg.stChar = pMsg->header.stID;
		GettheNetworkInput().SendMsg( &TmpMsg,TmpMsg.GetLength() );  
	}

	unguard;
}

// 接收到角色离开我的视野(包括物品)
void CPlayerMgr::OnMsgExitMySight( Msg* pMsg )
{
	guardfunc;
	if( !CanReceivePlayerMsg() )
		return;

	CPlayer* pPlayer = FindByID( pMsg->header.stID );

	bool bIsPlayer = false;
	if( pPlayer && pPlayer->IsPlayer() )
		bIsPlayer = true;

	PlayerExit( pMsg->header.stID );

	// 刷新附近玩家
// 	if( bIsPlayer )
// 		s_CUI_ID_FRAME_TRACK.RefreshPlayerList();

	unguard;
}

void CPlayerMgr::OnMsgAckCompound( Msg* pMsg )
{
	guardfunc;

	CHECK_MSGLEN( pMsg, MsgAckCompound);
	s_CUI_ID_FRAME_Compound.Compound( (MsgAckCompound*)pMsg );
	return;
	unguard;
}

void CPlayerMgr::OnLobbyMsgRoomInfo( Msg* pMsg )
{
	guardfunc;

	unguard;
}



void CPlayerMgr::OnLobbyMsgAckCreateRoom( Msg* pMsg )
{
	guardfunc;
	unguard;
}

void CPlayerMgr::OnLobbyMsgAckJoinRoom( Msg* pMsg )
{
	guardfunc;
	unguard;
}

void CPlayerMgr::OnLobbyMsgAckLeaveRoom( Msg* pMsg )
{
	guardfunc;

	unguard;
}

void CPlayerMgr::OnLobbyMsgRoomDismiss( Msg* pMsg )
{
	guardfunc;

	unguard;
}

void CPlayerMgr::OnLobbyMsgAckPlayerProfile( Msg* pMsg )
{
	guardfunc;
	unguard;
}

void CPlayerMgr::OnLobbyMsgThirdPartyMsg( Msg* pMsg )
{
	guardfunc;
	unguard;
}

void CPlayerMgr::OnLobbyMsgPlayerCheat( Msg* pMsg )
{

	guardfunc;
	unguard;
}

void CPlayerMgr::OnLobbyMsgAckUseCard( Msg* pMsg )
{
	guardfunc;
	assert( false && "由于没有卡片类型,所以使函数先被屏蔽!");
	unguard;
}

void CPlayerMgr::OnMsgSeekEquip( Msg* pMsg )
{
	guardfunc;

	CHECK_MSGLEN( pMsg, MsgPeekEquip);
	MsgPeekEquip *pPeekEquip = (MsgPeekEquip*)pMsg;
	CPlayer* DestPlayer = FindByID( pPeekEquip->playerId );

	for(int i=0;i<EEquipPartType_MaxEquitPart;++i)
	{
		pPeekEquip->playerequipitem[i].SetLock(false);
	}

	if ( DestPlayer )
	{
		DestPlayer->SetSeekEquipInfo( pPeekEquip->playerequipitem );

		/*s_CUI_ID_FRAME_SeekEqup.SetVisable( true ); 
		s_CUI_ID_FRAME_SeekEqup.SetDestPlayerId(pPeekEquip->playerId);
		s_CUI_ID_FRAME_SeekEqup.SetChangeSkeletonAndEquipAll(pPeekEquip->playerequipitem);*/
		s_CUI_ID_FRAME_SeeBasePropertyBGFrame.SetVisable( true ); 
		s_CUI_ID_FRAME_SeekEqup.OnSeekEquip(pMsg);
	}
	else
	{

		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_SeekEquip, theXmlString.GetString( eText_Chat_NotSeekEquip ) );
	}

	unguard;
}

void CPlayerMgr::OnLobbyMsgReqUseCard( Msg* pMsg )
{

	guardfunc;
	unguard;
}


void CPlayerMgr::OnMsgPlayMusic( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgScriptPlayerMusic);
	MsgScriptPlayerMusic* pMusicMsg = (MsgScriptPlayerMusic*)pMsg;
	char szFileName[MAX_PATH] = {0};
	MeSprintf_s(szFileName, sizeof(szFileName)/sizeof(char) - 1, "%s\\%s", GetRootPath(), pMusicMsg->szFileName);
	switch( pMusicMsg->stParameter ) 
	{
	case 0:
		{
			GSound.PlaySound( szFileName,false , NULL);
		}
		break;
	case 1:
		GSound.PlaySound( szFileName, true , NULL);
		break;
	case -1:
		GSound.StopSound();
		break;
	default:
		assert(false);
		break;
	}
	unguard;
}

void CPlayerMgr::OnMsgScriptMakeItem( Msg* pMsg )
{

	guardfunc;

	CHECK_MSGLEN( pMsg, MsgScriptMakeItem);
	MsgScriptMakeItem* pMakeItem = (MsgScriptMakeItem*)pMsg;
	OutputDebugString("需要以后打开\n");
	unguard;
}

void CPlayerMgr::OnMsgScriptQuestDlg(Msg* pMsg)
{
	guardfunc;
	//s_CUI_ID_FRAME_NpcChatDialogBox.SetVisable( false );
	CHECK_MSGLEN( pMsg, MsgScriptReqShowQuestDlg);
	MsgScriptReqShowQuestDlg *pQuestDlg = (MsgScriptReqShowQuestDlg*)pMsg;

// 	if(s_CUI_NpcTaskDialogBox.SendBuffMsg())
// 		return;

	CPlayer* pNpc = FindByID( pQuestDlg->stNpcId );
	if( !pNpc || !pNpc->IsNpc() )
	{
		assert( false );
		return;
	}

// 	if (pQuestDlg->szInfo[0] == '@')
// 	{
// 		int stringId = atoi(&pQuestDlg->szInfo[1]);
// 		strcpy(pQuestDlg->szInfo,theXmlString.GetString(stringId));
// 	}
	char* szTemp = theXmlString.ParseAtString(pQuestDlg->szInfo);
	std::string strDialog = "";
	short shExpHeadId = ProcessExpHead( (const char*)szTemp, strDialog );
	szTemp = (char*)strDialog.c_str();
	const int nMaxListItem = 64;

	ControlList::S_List pstList[nMaxListItem];
	int questStates[nMaxListItem];
	int nQuestCount  = 0;
	RetriveRelationQuestToNpc(pQuestDlg->stNpcId, nQuestCount, questStates, pstList);

	if(pQuestDlg->chShowType != MsgScriptReqShowQuestDlg::ShowType_Pub
		&&pQuestDlg->chShowType != MsgScriptReqShowQuestDlg::ShowType_Royal
		&&pQuestDlg->chShowType != MsgScriptReqShowQuestDlg::ShowType_ConQuest)
	{
		if (nQuestCount >= 1)
		{
			if(s_CUI_NpcTaskDialogBox.SendBuffMsg())
				return;
		}
		else
		{
			s_CUI_NpcTaskDialogBox.SetBuffItemId(-1);
		}
	}

	s_CUI_ID_FRAME_EspecialTask.SetCanRefresh(true);

	switch (pQuestDlg->chShowType)
	{
	case MsgScriptReqShowQuestDlg::ShowType_Pub:
		{
			s_CUI_ID_FRAME_EspecialTask.Show(pstList, nQuestCount, pQuestDlg->stNpcId, pQuestDlg->chShowType);

			MsgScriptCancel msg;
			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case MsgScriptReqShowQuestDlg::ShowType_Royal:
		{
			s_CUI_ID_FRAME_EspecialTask.Show(pstList, nQuestCount, pQuestDlg->stNpcId, pQuestDlg->chShowType);

			MsgScriptCancel msg;
			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case MsgScriptReqShowQuestDlg::ShowType_ConQuest:
		{
			s_CUI_ID_FRAME_EspecialTask2.Show(pstList, nQuestCount, pQuestDlg->stNpcId, pQuestDlg->chShowType);

			MsgScriptCancel msg;
			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	default:
		{
			if (nQuestCount < 1)
			{
				MsgScriptAckShowQuestDlg msg;
				msg.stQuestId = -1;
				GettheNetworkInput().SendMsg( &msg );
				return;
			}

			if(nQuestCount < nMaxListItem)
			{
				const char *pszQuestEnd = theXmlString.GetString(eText_QUESTEND);
				questStates[nQuestCount] = 2100;
				pstList[nQuestCount++].SetData(pszQuestEnd,-1,NULL,0xffffffff);
			}

			s_CUI_NpcTaskDialogBox.SetNpc(pQuestDlg->stNpcId);
			s_CUI_NpcTaskDialogBox.SetExpHeadId(shExpHeadId);
			s_CUI_NpcTaskDialogBox.Show( szTemp, pstList, nQuestCount,
				pNpc->GetName(), true, CUI_NpcTaskDialogBox::ScriptShowQuestDlgCallbackFun,
				nQuestCount, questStates );
		}
	}

	s_CUI_ID_FRAME_Task.SetVisable(false);

	unguard;
}

void CPlayerMgr::OnMsgAckQuestInfo(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckQuestInfo);
	unguard;
}
void CPlayerMgr::OnMsgPopMapNpcList(Msg*pMag)
{
	guardfunc;
	s_CUI_ID_FRAME_AllNpcList.SetVisable( true );
	unguard;
}

void CPlayerMgr::OnMsgProfessionChangInfo(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgProfessionChangeInfo);
	MsgProfessionChangeInfo *pProfessionChang = (MsgProfessionChangeInfo*)pMsg;
	short stValue = pProfessionChang->stProfession;
	thePlayerRole.Update(CPlayerRole::TYPE_PROFESSION,stValue);
	thePlayerRole.UpdateUI();
	unguard;
}

void CPlayerMgr::OnMsgChangeFightState(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgChangeFightState);
	MsgChangeFightState* pMsgFight = (MsgChangeFightState*)pMsg;
	if( !pMsgFight )
	{
		return;
	}
	CPlayer *pPlayer = FindByID( pMsgFight->playerId );
	if ( !pPlayer )
		return;
	if ( pMsgFight->bFight )
	{
		if (pPlayer->IsDead())
		{
			pPlayer->m_status.ResetDead();
			pPlayer->Relive(0);
		}
		if( pPlayer == GetMe() && pPlayer->GetName() )
		{
			char str[MAX_PATH] = {0};
			MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%s 进入战斗\n",pPlayer->GetName());
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, string(str));
		}
		if( !pPlayer->HasFightFlag(eFighting) )
			pPlayer->AddFightFlag( eFighting );
		if ( pPlayer == GetMe() )
		{
			thePlayerRole.SetFighting( true );
			s_CUI_ID_FRAME_MAIN.RefeashHotKey();
			s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Fight, theXmlString.GetString( eText_BeginFight ) );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_BeginFight ) );
		}
		// 不可见的召唤物，进战斗后可见
		if( !pPlayer->IsVisibleToOtherPlayer() )
		{
			pPlayer->SetVisibleToOtherPlayer(TRUE);
		}
	}
	else
	{
		if (s_CUI_ID_FRAME_Target.GetPlayerID() == pPlayer->GetID())
			s_CUI_ID_FRAME_Target.Get_ttGroup().SetVisible(false);

		if( pPlayer == GetMe() && pPlayer->GetName() )
		{
			char str[MAX_PATH] = {0};
			MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%s 退出战斗\n",pPlayer->GetName());
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, string(str));
		}

		if( pPlayer->HasAttackActionQueue() || (pPlayer->GetAnim() && !pPlayer->GetAnim()->IsUpperAnimPlayOver() ) )
			pPlayer->SetPendingClearFightFlag(TRUE);
		else
		{
			
			//if ( !s_CUI_ID_FRAME_Target.IsVisable() )	//如果头像还在需要保持战斗姿势,只有头像没选中了取消
			//{
				//pPlayer->ChangeToFightPose();
				pPlayer->ClearFightFlag( eFighting );
			//}
			if ( pPlayer == GetMe() )
			{
				thePlayerRole.SetFighting( false );
				s_CUI_ID_FRAME_MAIN.RefeashHotKey();
				s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Fight, theXmlString.GetString( eText_ExitFight ) );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_ExitFight ) );
				//s_CUI_ID_FRAME_Group_Me.PICTURE_Zhandou_SetVisable( false );
			}
		}
	}
	unguard;
}

void CPlayerMgr::OnMsgAgreeUseSpecialSkill()
{
	guardfunc;
	if( m_pMe )
		m_pMe->StartCountDownSpecialSkill();
	unguard;
}

void CPlayerMgr::OnMsgAgreeReadytoUseSpecialSkill(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAgreeReadytoUseSpecialSkill);
	MsgAgreeReadytoUseSpecialSkill* pMsgAgree = (MsgAgreeReadytoUseSpecialSkill*)pMsg;

	// 放在移动消息发完以后做
	if( m_pMe )
	{
		m_pMe->ReadyToLaunchSpecialSkill( pMsgAgree->shCurPermillage );
		m_pMe->m_status.SwitchStatus( CPlayerStatus::esk_ReadyToUseSpecialSkill, 500 );
	}
	unguard;
}

void CPlayerMgr::OnMsgNpcPlayAnim(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgNpcPlayAnim);
	MsgNpcPlayAnim* pPlayAnim = (MsgNpcPlayAnim*)pMsg;
	CPlayer* pPlayer = FindByID( pPlayAnim->nNpcId );
	if( !pPlayer )
		return;

	pPlayer->PlayAnim( pPlayAnim->szActionName,	pPlayAnim->nLoopTimes,
		pPlayAnim->szEndActionName );
	unguard;
}

void CPlayerMgr::OnMsgIntonateInterrupt(Msg* pMsg)
{
	guardfunc;
	if( m_pMe )
	{
		m_pMe->SetIntonating( FALSE );
		m_pMe->SetIntonatingTarget(0);
		if( !m_pMe->IsMoving() )
		{
			if( m_pMe->IsInWater() )
				m_pMe->SwitchSwimIdleAnim();
			else
				m_pMe->SwitchIdleAnim();
		}
	}

	if( s_CUI_Progress.IsVisable() && !s_CUI_Progress.IsInterrupt() )
	{
		s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), 1, true, 1, true, true, theXmlString.GetString(eTextPlayer_Break), true, false, 0, FALSE );

		//吟唱中断掉了后， 手上的特效要释放掉
		if( m_pMe )
		{
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
	}

	if( pMsg )
	{
		CHECK_MSGLEN( pMsg, Msg_IntonateInterrupt);
		Msg_IntonateInterrupt* pInterruptMsg = (Msg_IntonateInterrupt*)pMsg;

		// 删除预拨技能
		if( GetMe() )
			GetMe()->RemoveAdvanceSkillByID(pInterruptMsg->nSkillID);
	}
	unguard;
}

void CPlayerMgr::OnMsgScriptSetHotkey(Msg* pMsg)
{
	guardfunc;
	s_CUI_ID_FRAME_MAIN.SetHotkey(pMsg);
	unguard;
}

void CPlayerMgr::OnMsgChangEquipHp(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgChangEquipHp);
	MsgChangEquipHp *pHp = (MsgChangEquipHp*)pMsg;
	CPlayer* pPlayer = FindByID(pHp->header.stID);
	if( !pPlayer )
		return;

	short stEquipIndex = pHp->stIndex;
	if( stEquipIndex < EEquipPartType_MaxEquitPart )
	{	
		if (pHp->nEquipHp < 0 )
		{
			pHp->nEquipHp = 0;
		}
		thePlayerRole.m_pVisual->GetVisualArray()[stEquipIndex].equipdata.usHP = pHp->nEquipHp;
		thePlayerRole.m_pVisual->GetVisualArray()[stEquipIndex].equipdata.usHpMax = pHp->nEquipMaxHp;

		s_CUI_ID_FRAME_BaseProperty.UpdateEquipUI();
	}
	unguard;	
}

void CPlayerMgr::OnMsgUpdateTime(Msg* pMsg)
{

}


void CPlayerMgr::OnMsgIntensifyEquip(Msg* pMsg)
{
	//
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgIntensifyEquip);
	MsgIntensifyEquip *pIntensify = (MsgIntensifyEquip*)pMsg;

	// success
	if( pIntensify->nResult == MsgIntensifyEquip::e_Succeed )
	{
// 		// 刷新money
// 		thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pIntensify->nMoney );
// 		s_CUI_ID_FRAME_PACK.RefreshMoney();
		// 更新包裹
		if (pIntensify->nEvolveType == MsgEquipEvolve::ET_Charm)
		{
			memcpy( &thePlayerRole.m_bagMaterial.m_pPackItem[pIntensify->nNormalBagIndex], &pIntensify->item, sizeof( SCharItem) );
			s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pIntensify->nNormalBagIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag), &thePlayerRole.m_bagMaterial, BT_MaterialBag );
		}
	    else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_UnknowIdentify)
		{
			s_CUI_ID_FRAME_IdentifyQuality.Clear();
			s_CUI_ID_FRAME_IdentifyQuality.RrefreshItem(pIntensify->item);
			s_CUI_ID_FRAME_IdentifyQuality.ShowMaterialIcon();
			s_CUI_ID_FRAME_IdentifyQuality.RefreshOKButton();
	    }
		else
		{
			memcpy( &thePlayerRole.m_bag.m_pPackItem[pIntensify->nNormalBagIndex], &pIntensify->item, sizeof( SCharItem) );
			// 更新
			s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pIntensify->nNormalBagIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag), &thePlayerRole.m_bag, BT_NormalItemBag );

		}

		///////////////////////
		///  升星
		if( pIntensify->nEvolveType == MsgEquipEvolve::ET_LevelUp )
		{
			// 播放特效
			//PlayEffect( "Common\\Star.effect", GetMe() );
			bool bIntensifyStar = false;	// 流光升星
// 			if( pIntensify->item.equipdata.ucLevel <= 9 )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Success, theXmlString.GetString( eText_Intensify_StarSuccess ) );		
// 			else
// 			{
// 				GetShowScreenText()->AddInfo( theXmlString.GetString( eText_IntensifyStarSucceed ), Color_Config.getColor( CC_Center_OtherInfo ), 1000 );		
// 				bIntensifyStar = true;
// 			}

			if( !bIntensifyStar )
			{
				s_CUI_ID_FRAME_Star.RefreshEquipInfo();
				s_CUI_ID_FRAME_Star.UpdateGem();
				s_CUI_ID_FRAME_Star.UpdateAddRateGem();
				s_CUI_ID_FRAME_Star.UpdateProtectGem();
				s_CUI_ID_FRAME_Star.ProcessAutoLevelUp();
			}
			else
			{
				s_CUI_ID_FRAME_IntensifyStar.UpdateGem();
				s_CUI_ID_FRAME_IntensifyStar.UpdateAddRateGem();
				s_CUI_ID_FRAME_IntensifyStar.RefreshArmour();
			}

			PlaySoundConfig( SoundConfig::EST_StarSuccess );

		}
		///////////////////////
		///  鉴定
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_Identify )
		{
			// 播放特效
			PlayEffect( "Common\\Star.effect", GetMe() );
			s_CUI_ID_FRAME_GoldPlating.RefreshArmour();
			s_CUI_ID_FRAME_GoldPlating.RefreshMaterial();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString( eText_Intensify_IdentifySuccess ) );		
		}
		///////////////////////
		///  开光
// 		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_OpenLight )
// 		{
// 			s_CUI_ID_FRAME_GoldPlating.RefreshArmour();
// 			s_CUI_ID_FRAME_GoldPlating.RefreshMaterial();
// 			GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_Intensify_KaiGuangSuccess ), Color_Config.getColor( CC_Center_OtherInfo ), 1000 );		
// 		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_SoulStamp )
		{
			// 播放特效
			PlayEffect( "Common\\ZhuHun.effect", GetMe() );
			s_CUI_ID_FRAME_Soul.RefreshEquipInfo();
			s_CUI_ID_FRAME_Soul.UpdateGem();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Success, theXmlString.GetString( eText_Soul_Soul_Success ) );
			PlaySoundConfig( SoundConfig::EST_StampSuccess );
		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_OpenLight )
		{
			// 播放特效
			PlayEffect( "Common\\CuiLian.effect", GetMe() );
			s_CUI_ID_FRAME_Purple.RefreshEquipInfo();
			s_CUI_ID_FRAME_Purple.UpdateGem();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseGold_Success, theXmlString.GetString( eText_OpenLight_Success ) );		
			PlaySoundConfig( SoundConfig::EST_GoldSuccess );
		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_ReOpenLight )
		{
			// 播放特效
			PlayEffect( "Common\\HuiLu.effect", GetMe() );
			s_CUI_ID_FRAME_Repurple.RefreshEquipInfo();
			s_CUI_ID_FRAME_Repurple.UpdateGem();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseGold_Success, theXmlString.GetString( eText_OpenLight_Success ) );		
		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_Stiletto )
		{
			// 播放特效
			/*if (s_CUI_ID_FRAME_Hole.m_pUiEffect)
			{
				s_CUI_ID_FRAME_Hole.m_pUiEffect->SetStartTime(timeGetTime());
				s_CUI_ID_FRAME_Hole.m_pUiEffect->SetStatus(UiEffectBase::EffectStatus_Success);
			}
			s_CUI_ID_FRAME_Hole.SetOkButtonEnable(true);*/
			
			PlayEffect( "Common\\DaKong.effect", GetMe() );
			s_CUI_ID_FRAME_Hole.RefreshEquipInfo();
			s_CUI_ID_FRAME_Hole.UpdateGem();
			s_CUI_ID_FRAME_Hole.RefreshMoney();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Success, theXmlString.GetString( eText_Hole_Success ) );		

			PlaySoundConfig( SoundConfig::EST_HoleSuccess );
		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_Inlay )
		{
			// 播放特效
			
			PlayEffect( "Common\\XiangQian.effect", GetMe() );
			s_CUI_ID_FRAME_Gem.RefreshEquipInfo();
			s_CUI_ID_FRAME_Gem.UpdateGem();
			s_CUI_ID_FRAME_Gem.SetRatioVisable(false);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Success, theXmlString.GetString( eText_Gem_Success ) );		

			PlaySoundConfig( SoundConfig::EST_InlaySuccess );
		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_TakeDown )
		{
			// 播放特效
			PlayEffect( "Common\\ChaiXie.effect", GetMe() );
			s_CUI_ID_FRAME_GemRemove.RefreshEquipInfo();
			s_CUI_ID_FRAME_GemRemove.UpdateGem();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Success, theXmlString.GetString( eText_GemRemove_Success ) );		
		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_Replace )
		{
			// 播放特效
			PlayEffect( "Common\\TiHuan.effect", GetMe() );
			s_CUI_ID_FRAME_GemReplace.RefreshEquipInfo();
			s_CUI_ID_FRAME_GemReplace.UpdateGem();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Success, theXmlString.GetString( eText_GemReplace_Success ) );		
		}
		else if (pIntensify->nEvolveType == MsgEquipEvolve::ET_Charm)
		{
			// 播放特效
			PlayEffect( "Common\\SheLi.effect", GetMe() );
			s_CUI_ID_FRAME_Symbol.ClearEquip();
// 			ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pIntensify->item.GetItemID() );
// 			if( pItemDetail )
// 			{
// 				char szInfo[256];
// 				Common::_tstring tstrName( pItemDetail->GetItemName() );
// 				S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
// 				MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_YouGet_N_S), 1, tstrName.c_str() );
// 				s_CUI_ID_FRAME_InfoList. AddInfo( szInfo, Color_Config.getColor( CC_Pick ), MsgChat::CHAT_TYPE_GAMEPROMPT, 0, (char*)&pIntensify->item, 1, BT_MaterialBag );
// 			}

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Amulet_Success, theXmlString.GetString( eWarning_Charm_Success ) );		
		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_Amulet )
		{
			// 播放特效
			PlayEffect( "Common\\KaiGuang.effect", GetMe() );
			s_CUI_ID_FRAME_Amulet.RefreshEquipInfo();
			s_CUI_ID_FRAME_Amulet.ClearSymbol();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Amulet_Success, theXmlString.GetString( eWarning_Amulet_Success ) );		
		}
	}
	// 失败
	else if( pIntensify->nResult == MsgIntensifyEquip::e_Lost )
	{
		///////////////////////
		///  升星
		if( pIntensify->nEvolveType == MsgEquipEvolve::ET_LevelUp )
		{
			// 更新money
// 			thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pIntensify->nMoney );
// 			s_CUI_ID_FRAME_PACK.RefreshMoney();

			//失败
			bool bIntensifyStar = false;	// 流光升星
// 			if( pIntensify->item.equipdata.ucLevel <= 8 )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString( eText_Intensify_StarFailed ) );
// 			else
// 			{
// 				GetShowScreenText()->AddInfo( theXmlString.GetString( eText_IntensifyStarFailed ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 1000);
// 				bIntensifyStar = true;	// 流光升星
// 			}

			// 更新包裹
			memcpy( &thePlayerRole.m_bag.m_pPackItem[pIntensify->nNormalBagIndex], &pIntensify->item, sizeof( SCharItem) );

			// 更新
			// 服务端删物品，材料包不需要刷新
			//s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pIntensify->stLevelupMaterialIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag), &thePlayerRole.m_bagMaterial, BT_MaterialBag );
			s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pIntensify->nNormalBagIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag), &thePlayerRole.m_bag, BT_NormalItemBag );
			if( !bIntensifyStar )
			{
				s_CUI_ID_FRAME_Star.RefreshEquipInfo();
				s_CUI_ID_FRAME_Star.UpdateGem();
				s_CUI_ID_FRAME_Star.UpdateAddRateGem();
				s_CUI_ID_FRAME_Star.UpdateProtectGem();
				s_CUI_ID_FRAME_Star.ProcessAutoLevelUp();
			}
			else
			{
				s_CUI_ID_FRAME_IntensifyStar.UpdateGem();
				s_CUI_ID_FRAME_IntensifyStar.UpdateAddRateGem();
				s_CUI_ID_FRAME_IntensifyStar.RefreshArmour();
			}

			PlaySoundConfig( SoundConfig::EST_StarFailed );
		}
		else if (pIntensify->nEvolveType == MsgEquipEvolve::ET_Charm)
		{
			s_CUI_ID_FRAME_Symbol.ClearEquip();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Amulet_Failed, theXmlString.GetString( eWarning_Charm_Fail ) );		

		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_SoulStamp )
		{
			PlaySoundConfig( SoundConfig::EST_StampFailed );
		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_OpenLight )
		{	
			PlaySoundConfig( SoundConfig::EST_GoldFailed );
		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_Stiletto )
		{			
			PlaySoundConfig( SoundConfig::EST_HoleFailed );
			/*if (s_CUI_ID_FRAME_Hole.m_pUiEffect)
			{
				s_CUI_ID_FRAME_Hole.m_pUiEffect->SetStartTime(timeGetTime());
				s_CUI_ID_FRAME_Hole.m_pUiEffect->SetStatus(UiEffectBase::EffectStatus_Fail);
			}
			s_CUI_ID_FRAME_Hole.SetOkButtonEnable(true);*/
			s_CUI_ID_FRAME_Hole.RefreshEquipInfo();
			s_CUI_ID_FRAME_Hole.UpdateGem();
			s_CUI_ID_FRAME_Hole.RefreshMoney();
			
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Amulet_Failed, theXmlString.GetString(eText_Hole_Failed));
		}
		else if( pIntensify->nEvolveType == MsgEquipEvolve::ET_Inlay )
		{	
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Amulet_Failed, theXmlString.GetString(eText_Gem_Failed));
			PlaySoundConfig( SoundConfig::EST_InlayFailed );
			
		}
	}	
	//失败的时候附加一个reason字段不合理些吗？还要搞这么多情况处理，X，这尼玛太坑爹了
	else if( pIntensify->nResult == MsgIntensifyEquip::e_ItemNotMatch )
	{
		// 装备不匹配
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString( eText_Intensify_EquipNotMatch ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_ErrorLevelRep )
	{
		// 宝石等级不够
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString( eText_Intensify_RepGem ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_IntensifyMax )
	{
		// 强化到了最大等级
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString( eText_Intensify_MaxLevel ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_ItemNotExist )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString( eText_Intensify_NoItem ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_NotEnoughMoney )
	{
		// 没钱
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString( eText_Intensify_NoMoney ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_ErrorMaterialItem )
	{
		// 宝石不对
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString( eText_Intensify_FailedItem ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_ItemCantIdentify )
	{
		// 该物品不能被鉴定
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString( eText_Intensify_CannotIdentify ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_HaveIdentify )
	{
		// 鉴定过了
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString( eText_Intensify_AlreadyIdentify ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_BaseRandNotOpen )
	{
		// 还没有鉴定
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString( eText_Intensify_NotIdentify ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_HaveLiuJin )
	{
		// 开光过了
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString( eText_Intensify_AlreadyKaiGuang ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_MaterialItemLevel )
	{
		// 辅助材料等级不够
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString( eText_Intensify_MaterialItemLevel ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_NotHaveRateMaterial )
	{
		// 缺少增加概率材料
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString( eText_IntensifyStarFailed_LackRateMaterial ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_ErrorRateMaterialCount )
	{
		// 增加概率材料数量不正确
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString( eText_IntensifyStarFailed_WrongRateMaterialNum ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_HaveSameBaseRand )
	{
		// 已有相同蓝色随机属性
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString( eWarning_HaveSameBaseRand ) );
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_ErrorUnknowIdentify)
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Identify,theXmlString.GetString(eText_EquipNoIdentity));
	}
	else if( pIntensify->nResult == MsgIntensifyEquip::e_InlayIsNotExist)
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Gem_Success, theXmlString.GetString(eText_BuhlNoExist));
	}
	else if ( pIntensify->nResult == MsgIntensifyEquip::e_BagIsFull )
	{
		if( pIntensify->nEvolveType == MsgEquipEvolve::ET_UnknowIdentify)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString( eText_NormalPackFull ) );
	}
	
	//
	if(pIntensify->nResult == MsgIntensifyEquip::e_Succeed)
	{
		switch (pIntensify->nEvolveType)
		{
		case MsgEquipEvolve::ET_Stiletto:
			s_CUI_ID_FRAME_Hole.SetEffectStatus(EquipEvolveUI::EffectStatus_Success);
			s_CUI_ID_FRAME_Hole.SetBeginTime(timeGetTime());
			break;
		case MsgEquipEvolve::ET_Inlay:
			s_CUI_ID_FRAME_Gem.SetEffectStatus(EquipEvolveUI::EffectStatus_Success);
			s_CUI_ID_FRAME_Gem.SetBeginTime(timeGetTime());
			break;
		case MsgEquipEvolve::ET_UnknowIdentify:
			s_CUI_ID_FRAME_IdentifyQuality.SetEffectStatus(EquipEvolveUI::EffectStatus_Success);
			s_CUI_ID_FRAME_IdentifyQuality.SetBeginTime(timeGetTime());
			s_CUI_ID_FRAME_IdentifyQuality.RefreshOKButton();
			break;
		case MsgEquipEvolve::ET_LevelUp:
			s_CUI_ID_FRAME_Star.SetEffectStatus(EquipEvolveUI::EffectStatus_Success);
			s_CUI_ID_FRAME_Star.SetBeginTime(timeGetTime());
		}
	}
	else
	{
		switch (pIntensify->nEvolveType)
		{
		case MsgEquipEvolve::ET_Stiletto:
			s_CUI_ID_FRAME_Hole.SetEffectStatus(EquipEvolveUI::EffectStatus_Fail);
			s_CUI_ID_FRAME_Hole.SetBeginTime(timeGetTime());
			break;
		case MsgEquipEvolve::ET_Inlay:
			s_CUI_ID_FRAME_Gem.SetEffectStatus(EquipEvolveUI::EffectStatus_Fail);
			s_CUI_ID_FRAME_Gem.SetBeginTime(timeGetTime());
			break;
		case MsgEquipEvolve::ET_UnknowIdentify:
			s_CUI_ID_FRAME_IdentifyQuality.SetEffectStatus(EquipEvolveUI::EffectStatus_Fail);
			s_CUI_ID_FRAME_IdentifyQuality.SetBeginTime(timeGetTime());
			s_CUI_ID_FRAME_IdentifyQuality.RefreshOKButton();
			break;
		case MsgEquipEvolve::ET_LevelUp:
			s_CUI_ID_FRAME_Star.SetEffectStatus(EquipEvolveUI::EffectStatus_Fail);
			s_CUI_ID_FRAME_Star.SetBeginTime(timeGetTime());
		}
	}
	unguard;
}

void CPlayerMgr::OnMsgRandAttributeAck(Msg* pMsg)
{
	CHECK_MSGLEN( pMsg, MsgRandAttrAck );
	MsgRandAttrAck* pAck = (MsgRandAttrAck*)pMsg;

	memcpy(&thePlayerRole.m_bag.m_pPackItem[pAck->nNormalBagIndex], &pAck->item, sizeof(SCharItem));
	s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pAck->nNormalBagIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag), &thePlayerRole.m_bag, BT_NormalItemBag );

	s_CUI_ID_FRAME_RandAttribute.SetEffectStatus(CUI_ID_FRAME_RandAttribute::EffectStatus_Success);
	s_CUI_ID_FRAME_RandAttribute.SetBeginTime(timeGetTime());
	s_CUI_ID_FRAME_RandAttribute.UpdataAll();
}

void CPlayerMgr::OnMsgFransferStarAck(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgTransferStarAck );
	MsgTransferStarAck* pIntensify = (MsgTransferStarAck*)pMsg;

	if (pIntensify->eresult == MsgTransferStarAck::eR_Fail)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString( eText_TransferStarAck_Fail ) );
		s_CUI_ID_FRAME_TransferStar.SetEffectStatus(CUI_ID_FRAME_TransferStar::EffectStatus_Fail);
		s_CUI_ID_FRAME_TransferStar.SetBeginTime(timeGetTime());
	}
	else
	{
		memcpy(&thePlayerRole.m_bag.m_pPackItem[pIntensify->nSourceBagIndex], &pIntensify->sourceEquip, sizeof(SCharItem));
		s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pIntensify->nSourceBagIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag), &thePlayerRole.m_bag, BT_NormalItemBag );

		memcpy( &thePlayerRole.m_bag.m_pPackItem[pIntensify->nTargetBagIndex], &pIntensify->targetEquip, sizeof( SCharItem) );
		s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pIntensify->nTargetBagIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag), &thePlayerRole.m_bag, BT_NormalItemBag );

		if (pIntensify->eresult == MsgTransferStarAck::eR_Success)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Success, theXmlString.GetString( eText_TransferStarAck_Success ) );
			s_CUI_ID_FRAME_TransferStar.SetEffectStatus(CUI_ID_FRAME_TransferStar::EffectStatus_Success);
			s_CUI_ID_FRAME_TransferStar.SetBeginTime(timeGetTime());
		}
		else
		{
			char sbuff[256] = {0};
			int dropstar = 0;
			switch (pIntensify->eresult)
			{
			case MsgTransferStarAck::eR_DropOne:
				dropstar = 1;
				break;
			case MsgTransferStarAck::eR_DropTwo:
				dropstar = 2;
				break;
			case MsgTransferStarAck::eR_DropThree:
				dropstar = 3;
				break;
			}
			sprintf_s(sbuff, sizeof(sbuff), theXmlString.GetString( eText_TransferStarAck_FailDrop ), dropstar, pIntensify->sourceEquip.equipdata.ucLevel, pIntensify->targetEquip.equipdata.ucLevel);

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, sbuff );
			s_CUI_ID_FRAME_TransferStar.SetEffectStatus(CUI_ID_FRAME_TransferStar::EffectStatus_Fail);
			s_CUI_ID_FRAME_TransferStar.SetBeginTime(timeGetTime());
		}
	}

	s_CUI_ID_FRAME_TransferStar.SetAckMsg(true);
	s_CUI_ID_FRAME_TransferStar.UpdataAll();

	unguard;
}

void CPlayerMgr::OnMsgEquipMaintainAck( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgEquipMaintainAck);
	MsgEquipMaintainAck *pIntensify = (MsgEquipMaintainAck*)pMsg;

	// success
	if( pIntensify->nResult == MsgEquipMaintainAck::e_Succeed )
	{
		memcpy( &thePlayerRole.m_bag.m_pPackItem[pIntensify->nSourceBagIndex], &pIntensify->sourceEquip, sizeof( SCharItem) );
		// 更新
		s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pIntensify->nSourceBagIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag), &thePlayerRole.m_bag, BT_NormalItemBag );

		memcpy( &thePlayerRole.m_bag.m_pPackItem[pIntensify->nTargetBagIndex], &pIntensify->targetEquip, sizeof( SCharItem) );
		// 更新
		s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pIntensify->nTargetBagIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag), &thePlayerRole.m_bag, BT_NormalItemBag );
		// 播放特效
		PlayEffect( "Common\\ChuanCheng.effect", GetMe() );
// 		if (pIntensify->nEvolveType == )
		{
			s_CUI_ID_FRAME_EquipCopy.RefreshEquipInfo();
			s_CUI_ID_FRAME_EquipCopy.UpdateGem();
		}
		if (pIntensify->nEvolveType == MsgEquipEvolve::ET_Maintain)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Success, theXmlString.GetString( eText_Maintain_Success ) );		
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Success, theXmlString.GetString( eText_CrossMaintain_Success ) );	
		}
	}

	unguard;

}


void CPlayerMgr::OnMsgItemReclaim( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgItemReclaimAck);
	MsgItemReclaimAck *pReclaim = (MsgItemReclaimAck*)pMsg;
	ItemDefine::SItemCommon* pItemDetail = 0;
	SCharItem stItem;
	if( pReclaim->nResult == MsgItemReclaimAck::error_sucess )
	{
		PlayEffect( "Common\\HuiShou.effect", GetMe() );
		CItemBag2* pBag = &thePlayerRole.m_bag;
		switch(pReclaim->nItemBagType)
		{
		case BT_MaterialBag:
			pBag = &thePlayerRole.m_bagMaterial;
			break;
		case BT_TaskBag:
			pBag = &thePlayerRole.m_bagTask;
			break;
		default:;
		}
		pBag->GetItem( pReclaim->nPackIndex, &stItem );
		unsigned short stCount = 1;
		pBag->PopItem( pReclaim->nPackIndex, stCount, 0, 0, "" );
			
        // 刷背包的 Enable 统一流程      modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, pReclaim->nPackIndex, true );

// 		char szInfo[256] = {0};
// 		pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
// 		if( pItemDetail )
// 		{
// 			Common::_tstring tstrName( pItemDetail->GetItemName() );
// 			S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
// 			MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_YouLost_N_S), 1, tstrName.c_str() );
// 			s_CUI_ID_FRAME_InfoList. AddInfo( szInfo, Color_Config.getColor( CC_SystemPromp ), MsgChat::CHAT_TYPE_GAMEPROMPT, 0, (char*)&stItem, 1, pReclaim->nItemBagType );
// 		}
// 		thePlayerRole.UpdateActiveQuestStateByItem(stItem.itembaseinfo.ustItemID);

		char szBuff[256] = {0};
		switch ( pReclaim->nCostType)
		{
		case ItemDefine::CT_Reputation:
			{
				//MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouGetXReputation ), pReclaim->nCostReturn );
				//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Reputation_Change, szBuff );
				DWORD dwOldValue = thePlayerRole.GetData(CPlayerRole::TYPE_Reputation);
				thePlayerRole.Update(CPlayerRole::TYPE_Reputation,dwOldValue + pReclaim->nCostReturn );
			}
			break;
		case ItemDefine::CT_Exploit:
			{
				MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouGetXExploit ), pReclaim->nCostReturn );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Exploit_Change, szBuff );
				DWORD dwOldValue = thePlayerRole.GetData(CPlayerRole::TYPE_Exploit);
				thePlayerRole.Update(CPlayerRole::TYPE_Exploit,dwOldValue + pReclaim->nCostReturn );
			}
			break;
		case ItemDefine::CT_GuildOffer:
			{
				if(pReclaim->nCostReturn !=0)
				{
					MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouGetGuildOffer ), pReclaim->nCostReturn );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Invite_Guild, szBuff );
				}
				DWORD dwOldValue = thePlayerRole.GetData(CPlayerRole::TYPE_Exploit);
				thePlayerRole.Update(CPlayerRole::TYPE_Exploit,dwOldValue + pReclaim->nCostReturn );
			}
			break;
		case ItemDefine::CT_Item:
			{
				//std::string szStr;
				//thePlayerRole.GetGSCStringFromMoney(pReclaim->nCostReturn, szStr);
				//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Money_Change, szStr.c_str() );
				s_CUI_ID_FRAME_PACK.ChangeMoney(pReclaim->nCostReturn + thePlayerRole.GetData( CPlayerRole::TYPE_MONEY ));
			}
			break;
		default:
			{ 
				;
			}
			break;
		}

		s_CUI_ID_FRAME_EquipReturn.ClearEquip();
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Success, theXmlString.GetString( eText_Recycle_Success ) );		
	}
	unguard;

}



void CPlayerMgr::OnMsgIITEMCOMPOSEGEM( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgItemComposeGemAck);
	MsgItemComposeGemAck *pComposeGem = (MsgItemComposeGemAck*)pMsg;
	ItemDefine::SItemCommon* pItemDetail = 0;
	SCharItem stItem;
	if( pComposeGem->nResult == MsgItemComposeGemAck::ECD_Success )
	{

		CItemBag2* pBag = &thePlayerRole.m_bag;
		switch(pComposeGem->nItemBagType)
		{
		case BT_MaterialBag:
			pBag = &thePlayerRole.m_bagMaterial;
			break;
		case BT_TaskBag:
			pBag = &thePlayerRole.m_bagTask;
			break;
		default:;
			pBag = &thePlayerRole.m_bag;
			break;
		}

		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pComposeGem->xCharItem.itembaseinfo.ustItemID );
		if( pItemDetail )
		{
			char szInfo[256];
			Common::_tstring tstrName( pItemDetail->GetItemName() );
			S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
			MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_YouGet_N_S), 1, tstrName.c_str() );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)&pComposeGem->xCharItem, 1, pComposeGem->nItemBagType );
		}

		memcpy( &pBag->m_pPackItem[pComposeGem->nPackIndex], &pComposeGem->xCharItem, sizeof( SCharItem) );
		s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pComposeGem->nPackIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(pComposeGem->nItemBagType), pBag, pComposeGem->nItemBagType );

		if(pComposeGem->composeType == MsgItemComposeGem::ECT_GEM)
		{
			PlayEffect( "Common\\BaoShiShengJi.effect", GetMe() );
			// s_CUI_ID_FRAME_GemUp.ClearGems();
			s_CUI_ID_FRAME_GemUp.UpdateAll();
			s_CUI_ID_FRAME_GemUp.SetEffectStatus(CUI_ID_FRAME_GemUp::EffectStatus_Success);
			s_CUI_ID_FRAME_GemUp.SetBeginTime(timeGetTime());
			//ControlIconDrag::S_ListImg* pImg = s_CUI_ID_FRAME_PACK.GetItemByIndex(pComposeGem->nItemBagType,pComposeGem->nPackIndex);
			//s_CUI_ID_FRAME_GemUp.ID_LISTIMG_Gem6OnIconDragOn(s_CUI_ID_FRAME_PACK.GetListImageByBagType(pComposeGem->nItemBagType),NULL,pImg,NULL);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Success, theXmlString.GetString( eText_GemUp_Success ) );		
		}
		else 
		{
			PlayEffect( "Common\\XiShiJiPeiZhi.effect", GetMe() );
			s_CUI_ID_FRAME_GemMaterialUp.RefreshEquipInfo();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Success, theXmlString.GetString( eWarning_XSJUp_Success ) );		
		}
	}
	else if(pComposeGem->nResult == MsgItemComposeGemAck::ECD_Failed)
	{
		if(pComposeGem->composeType == MsgItemComposeGem::ECT_GEM)
		{
			//s_CUI_ID_FRAME_GemUp.ClearGems();
			s_CUI_ID_FRAME_GemUp.UpdateAll();
			s_CUI_ID_FRAME_GemUp.SetEffectStatus(CUI_ID_FRAME_GemUp::EffectStatus_Fail);
			s_CUI_ID_FRAME_GemUp.SetBeginTime(timeGetTime());
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed,theXmlString.GetString(eText_Gem_UpdateFailed));
		}
	}
	else if(pComposeGem->nResult == MsgItemComposeGemAck::ECD_NotEnoughMoney)
	{

	}
	else if(pComposeGem->nResult == MsgItemComposeGemAck::ECD_ErrorMaterialItem)
	{

	}
	else if(pComposeGem->nResult == MsgItemComposeGemAck::ECD_ErrorComposeItem)
	{

	}
	else if(pComposeGem->nResult == MsgItemComposeGemAck::ECD_CanNotCompose)
	{

	}
	else if(pComposeGem->nResult == MsgItemComposeGemAck::ECD_ItemPackFull)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString( eText_MaterialPackFull ) );
	}
	else if(pComposeGem->nResult == MsgItemComposeGemAck::ECD_ErrorComposeRune)
	{

	}
	unguard;
}



void CPlayerMgr::OnMsgZhuJiangCOMPOSE(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgZhuJiangComposeAck);
	MsgZhuJiangComposeAck *pCompose = (MsgZhuJiangComposeAck*)pMsg;
	ItemDefine::SItemCommon* pItemDetail = 0;
	SCharItem stItem;
	if( pCompose->nResult == MsgZhuJiangComposeAck::ECD_Success )
	{

		CItemBag2* pBag = &thePlayerRole.m_bag;
		switch(pCompose->nItemBagType)
		{
		case BT_NormalItemBag:
			pBag = &thePlayerRole.m_bag;
			break;
		case BT_MaterialBag:
			pBag = &thePlayerRole.m_bagMaterial;
			break;
		case BT_TaskBag:
			pBag = &thePlayerRole.m_bagTask;
			break;
		default:
			pBag = &thePlayerRole.m_bag;
			break;
		}

		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pCompose->xCharItem.itembaseinfo.ustItemID );
		if( pItemDetail )
		{
			char szInfo[256];
			Common::_tstring tstrName( pItemDetail->GetItemName() );
			S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
			MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_YouGet_N_S), 1, tstrName.c_str() );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)&pCompose->xCharItem, 1, pCompose->nItemBagType );
		}

		memcpy( &pBag->m_pPackItem[pCompose->nPackIndex], &pCompose->xCharItem, sizeof( SCharItem) );
		s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pCompose->nPackIndex, s_CUI_ID_FRAME_PACK.GetListImageByBagType(pCompose->nItemBagType), pBag, pCompose->nItemBagType );
		s_CUI_ID_FRAME_ZhuJianUp.UpdateAll();
		s_CUI_ID_FRAME_ZhuJianUp.RefreshOkEnable();
		s_CUI_ID_FRAME_ZhuJianUp.SetEffectStatus(CUI_ID_FRAME_ZhuJianUp::EffectStatus_Success);
		s_CUI_ID_FRAME_ZhuJianUp.SetBeginTime(timeGetTime());
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Success,theXmlString.GetString(eText_ZhuJiangUp_Success));
	}
	else if(pCompose->nResult == MsgZhuJiangComposeAck::ECD_Failed)
	{
		s_CUI_ID_FRAME_ZhuJianUp.UpdateAll();
		s_CUI_ID_FRAME_ZhuJianUp.RefreshOkEnable();
		s_CUI_ID_FRAME_ZhuJianUp.SetEffectStatus(CUI_ID_FRAME_ZhuJianUp::EffectStatus_Fail);
		s_CUI_ID_FRAME_ZhuJianUp.SetBeginTime(timeGetTime());
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed,theXmlString.GetString(eText_ZhuJiangUp_Failed));
	}
	else if (pCompose->nResult == MsgZhuJiangComposeAck::ECD_ItemPackFull)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString( eText_NormalPackFull ) );
	}
	unguard;
}

void CPlayerMgr::OnMsgRemoveSomething(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgMoveGoodsReq);
	MsgMoveGoodsReq* pMoveGoods = (MsgMoveGoodsReq*)pMsg;
	if ( pMoveGoods->ustSrcIndex == ITEM_DISTORY) 
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eClient_AddInfo_2slk_14), theXmlString.GetString(eClient_AddInfo_2slk_14), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		return;
	}
	if (pMoveGoods->ustDstIndex == ITEM_DISTORY)					//sbw_modify
	{		

		ItemDefine::SItemCommon* pItemDetail = 0;
		SCharItem stItem;
		bool bExist = false;

		CItemBag2* pBag = 0;
		switch (pMoveGoods->ucItemBagType)
		{
		case BT_NormalItemBag:
			bExist = thePlayerRole.m_bag.GetItem( pMoveGoods->ustSrcIndex, &stItem );
			if( bExist )
			{
				thePlayerRole.m_bag.PopItemByGuID(pMoveGoods->nGuID,pMoveGoods->ustCount,NULL,NULL,"");
				//thePlayerRole.m_bag.PopItem( pMoveGoods->ustSrcIndex, pMoveGoods->ustCount, 0, 0, "" );
				s_CUI_ID_FRAME_AutoAttackSet.RefreshQuestUI(); //lyh++ 当添加物品的时候 刷新下自动挂机的药品ui

                // 物品去掉指定个数后，如果没有物品了，则不锁定该空格   added, jiayi, [2010/1/20]
                // 刷背包的 Enable 统一流程      modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, pMoveGoods->ustSrcIndex, true );

				// 如果分解界面用了同个物品，刷新分解界面，包裹解锁
				if( s_CUI_ID_FRAME_Decompound.IsVisable() )
				{
					if( s_CUI_ID_FRAME_Decompound.IsUseSameItemInNormalBag( pMoveGoods->ustSrcIndex ) )
						s_CUI_ID_FRAME_Decompound.DecompoundSuccess( pMoveGoods->ustSrcIndex );
				}
			}
			break;
		case BT_MaterialBag:
			bExist = thePlayerRole.m_bagMaterial.GetItem( pMoveGoods->ustSrcIndex, &stItem );
			if( bExist )
			{
				thePlayerRole.m_bagMaterial.PopItemByGuID(pMoveGoods->nGuID,pMoveGoods->ustCount,NULL,NULL,"");
				//thePlayerRole.m_bagMaterial.PopItem( pMoveGoods->ustSrcIndex, pMoveGoods->ustCount, 0, 0, "" );

                // 物品去掉指定个数后，如果没有物品了，则不锁定该空格       added, jiayi, [2010/1/20]
                // 刷背包的 Enable 统一流程      modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, pMoveGoods->ustSrcIndex, true );
			}
			break;
		case BT_TaskBag:
			bExist = thePlayerRole.m_bagTask.GetItem( pMoveGoods->ustSrcIndex, &stItem );
			if( bExist )
			{
				thePlayerRole.m_bagTask.PopItemByGuID(pMoveGoods->nGuID,pMoveGoods->ustCount,NULL,NULL,"");
				//thePlayerRole.m_bagTask.PopItem( pMoveGoods->ustSrcIndex, pMoveGoods->ustCount, 0, 0, "" );

                // 物品去掉指定个数后，如果没有物品了，则不锁定该空格       added, jiayi, [2010/1/20]
                // 刷背包的 Enable 统一流程      modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagTask, pMoveGoods->ustSrcIndex, true );
			}
			break;
		}
		if( bExist )
		{
			char szInfo[256] = {0};
			pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
			if( pItemDetail )
			{
				Common::_tstring tstrName( pItemDetail->GetItemName() );
				S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
				MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_YouLost_N_S), pMoveGoods->ustCount, tstrName.c_str() );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)&stItem, 1, pMoveGoods->ucItemBagType );
				PlaySoundConfig( SoundConfig::EST_LoseItem );
			}
		}
		thePlayerRole.UpdateActiveQuestStateByItem(stItem.itembaseinfo.ustItemID);
		//s_CUI_Guild.SetNeedRefreshAlignment(true);
		CUIMgr::Instance()->RefreshByItemChange();
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

	}
	unguard;
}

void CPlayerMgr::OnMsgUseGood(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	CHECK_MSGLEN( pMsg, MsgUseGoods);
	MsgUseGoods* pUseGood = (MsgUseGoods*)pMsg;

	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;
	switch (pUseGood->ucItemBagType)
	{
	case BT_MaterialBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;
		break;
	case BT_TaskBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
		pBag = &thePlayerRole.m_bagTask;
		bagType = BT_TaskBag;
		break;
	default:
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;
		break;
	}

	SCharItem CharItem;
	if ( pBag->GetItem( pUseGood->ustItemIndex, &CharItem ) == false )
		return;	
	ItemDefine::SItemCommon *pItemCommon =GettheItemDetail().GetItemByID(CharItem.itembaseinfo.ustItemID);
	if (!pItemCommon)
	{
		return;
	}

	// 设置物品剩余值
	if ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
	{
		ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;
		// 设置冷却时间
		s_CUI_ID_FRAME_PACK.coolDownRestoreItem( pItemRestore, CharItem );

		if ( pItemRestore->bHPAuto || pItemRestore->bMPAuto )
		{
			pBag->m_pPackItem[pUseGood->ustItemIndex].itembaseinfo.value2 = pUseGood->nRemainValue;
		}
	}
	// 赠送礼物
	if( pItemCommon->byUserTarget == ItemDefine::eTargetFriend )
	{
		ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;
		// 设置冷却时间
		s_CUI_ID_FRAME_PACK.coolDownRestoreItem( pItemRestore, CharItem );
		s_CUI_ID_FRAME_GivePresent.SetVisable(false);
	}

	GSound.PlaySound( (char*)pItemCommon->GetIconSoundFile(), false,  NULL );
	OutputDebugString((char*)pItemCommon->GetIconSoundFile());

	// 如果剩余值小于0表示用完，则删除
	if ( pUseGood->nRemainValue <= 0 )
	{
		pBag->PopItem(pUseGood->ustItemIndex,pUseGood->stItemCount,NULL,NULL,"");
		// 背包道具移除
		SCharItem item;
		if( pBag->GetItem( pUseGood->ustItemIndex, &item ) )
			if ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE && 
				item.itembaseinfo.ustItemID == InvalidLogicNumber )
			{
				ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;
				if ( pItemRestore->bHPAuto || pItemRestore->bMPAuto || pItemRestore->bAutoRelive )
				{
					thePlayerRole.refreshHotKey();
				}
			}
	}

	s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pUseGood->ustItemIndex, pBagListImg, pBag, bagType);
	s_CUI_ID_FRAME_PACK.RefreshCooldown();
	s_CUI_ID_FRAME_MAIN.Refeash();
	unguard;
}

void CPlayerMgr::OnMsgRepairItemByServer(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgRepairItemAck);
	MsgRepairItemAck *pRepair = (MsgRepairItemAck *)pMsg;

	if( pRepair->result == MsgRepairItemAck::error_noMoney )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_MoneyNotEnoungh ) );
		return;
	}

	CPlayer* pPlayer = FindByID(pRepair->header.stID);
	if( !pPlayer)
		return;

	switch (pRepair->eType)
	{
	case MsgRepairItem::RT_Pack:
		{
			thePlayerRole.m_bag.m_pPackItem[pRepair->stIndex].equipdata.usHP = pRepair->nHp;
			thePlayerRole.m_bag.m_pPackItem[pRepair->stIndex].equipdata.usHpMax = pRepair->fMaxHp;
			s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pRepair->stIndex);
		}
		break;
	case MsgRepairItem::RT_Equip:
		{
			short stEquipIndex = pRepair->stIndex;
			if( stEquipIndex < EEquipPartType_MaxEquitPart )
			{
				thePlayerRole.m_pVisual->GetVisualArray()[stEquipIndex].equipdata.usHP = pRepair->nHp;
				thePlayerRole.m_pVisual->GetVisualArray()[stEquipIndex].equipdata.usHpMax = pRepair->fMaxHp;
				s_CUI_ID_FRAME_BaseProperty.UpdateEquipUI();
			}
		}
		break;
	case MsgRepairItem::RT_All:
		{
			for( int i = 0; i < EEquipPartType_MaxEquitPart; ++i)
			{
				ItemDefine::SItemCanEquip *pItemCommon = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(
					thePlayerRole.m_pVisual->GetVisualArray()[i].itembaseinfo.ustItemID );
				if (!pItemCommon)
					continue;

				thePlayerRole.m_pVisual->GetVisualArray()[i].equipdata.usHP = pItemCommon->stHPMax;
				s_CUI_ID_FRAME_BaseProperty.UpdateEquipUI();
			}
			for (int i = 0; i < thePlayerRole.m_bag.GetNowBagSize(); ++i)
			{
				SCharItem* pItem = &thePlayerRole.m_bag.m_pPackItem[i];
				if (pItem->itembaseinfo.ustItemID == InvalidLogicNumber)
					continue;
				ItemDefine::SItemCanEquip *pItemCommon = (ItemDefine::SItemCanEquip *)GettheItemDetail().GetItemByID(
					pItem->itembaseinfo.ustItemID );
				if (!pItemCommon)
					continue;

				int nItemHp = pItem->equipdata.usHP;
				int nItemMaxHp = pItemCommon->stHPMax;
				if( nItemHp >= 0 && nItemHp < nItemMaxHp )
				{
					if ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
						pItemCommon->ucItemType ==  ItemDefine::ITEMTYPE_ARMOUR )
					{
						pItem->equipdata.usHP = nItemMaxHp;
						s_CUI_ID_FRAME_PACK.RefreshPackByIndex(i);
					}
				}
			}
		}
		break;
	}


	unguard;
}

void CPlayerMgr::OnMsgOperateBank(Msg* pMsg)
{
	guardfunc;
	assert("name.h error" && 0);
	unguard;
}

void AddUpLevelInfo(MsgUpInfo *pInfo, int nStringIndex, int battrIndex)
{
	if (pInfo->nInfo[battrIndex] > 0 && thePlayerRole.m_pBaseInfo)
	{
		char szTemp[128] = {0};
		int value = pInfo->nInfo[battrIndex] - thePlayerRole.m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[battrIndex].final + 0.5f;
		MeSprintf_s( szTemp,sizeof(szTemp)/sizeof(char) - 1 ,"%s %d", theXmlString.GetString(nStringIndex), value);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_LevelUp_Belongs, szTemp );
	}
}

void CPlayerMgr::OnMsgShowLevelUpInfo(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgUpInfo);
	MsgUpInfo *pInfo = (MsgUpInfo*)pMsg;

	for (int nloop = 0; nloop<EBaseAttr_MaxSize;nloop++)
	{
		switch(nloop)
		{
		case EBaseAttr_Strength:
			{

			}
			break;
		case EBaseAttr_Stamina:
			{

			}
			break;
		case EBaseAttr_Agility:
			{

			}
			break;
		case EBaseAttr_Intelligence:
			{

			}
			break;
		/*case BA_JinGu:
			{*/

			/*}
			break;*/
		default:
			break;
		}
	}
	unguard;
}

void CPlayerMgr::SendPetCommand( int nCommand )
{
	guardfunc;
	if( m_pMe && m_pMe->HavePet() )
	{
		MsgPetCommand petcommand;
		petcommand.header.stID = m_pMe->GetID();
		petcommand.shPetCommandIndex = nCommand;

		if( -1 == GettheNetworkInput().SendMsg( &petcommand ) )
		{

		}
	}
	unguard;
}

void CPlayerMgr::OnMsgSawPlayerDead( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgSawSomeoneDead);
	MsgSawSomeoneDead* msg = (MsgSawSomeoneDead*)pMsg;
	CPlayer* pPlayer = FindByID( msg->header.stID );

	if( msg->bHaveDieAni )
	{
		if( pPlayer )
		{
			if( pPlayer != m_pMe )
			{
				pPlayer->OnClearAllBodyStatus();
				//lyh删除引用
				if( !pPlayer->IsDead() && pPlayer->GetCharType() != Object_Player &&
					pPlayer->GetCharType() != Object_NpcFight && pPlayer->GetCharType() != Object_Npc ) //lyh++ 后边的并且
					pPlayer->AddRef(); //meiwenti wanjiajinbulai
				pPlayer->SetCharDead( TRUE );
				pPlayer->UpdateBaseData(HQ_TimeGetTime());
				pPlayer->SetHPInfo_HP( 0 );
				//慎重测试！！ [11/10/2010 zhangjiayi]
				//pPlayer->AddRef();

				CPlayer* master = theHeroGame.GetPlayerMgr()->FindByID(pPlayer->GetMasterID());
				if (master)
					master->ReleasePet();

				// 如果是队友，则刷新队友列表
				if ( thePlayerRole.IsTeamMember(msg->header.stID) )
					s_CUI_Group.Refeash();
			}
			else
			{
				if (msg->shReliveCnt != 0xffff)
				{
					int _temp = theCountryConfig.GetReliveSetting().GetFreeReliveLimitByLevel(thePlayerRole.GetLevel()) - msg->shReliveCnt; //剩余复活次数
                     
					_temp = _temp > 0 ? _temp : 0;

					s_CUI_ID_FRAME_ESCDLG.m_HeroReliveCnt = msg->shReliveCnt;
					*(s_CUI_ID_FRAME_ESCDLG.m_pID_TEXT_ReLiveCnt) = _temp;
				}

			    
				assert( "Server send An error ID ( I dead ??? )" );
				OutputDebugString( "Server send An error ID ( I dead ??? )\n" );
			}
		}
	}
	else
	{
		if( pPlayer )
		{
			if( pPlayer != m_pMe )
			{
				pPlayer->OnClearAllBodyStatus();
				pPlayer->UpdateBaseData(HQ_TimeGetTime());
				// 慎重测试。 [11/10/2010 zhangjiayi]
// 				if( pPlayer->GetMonsterType() != eMT_IllusionMonster )
// 					pPlayer->AddRef();
				PlayerExit( pPlayer->GetID() );
				// 如果是队友，则刷新队友列表
				if ( thePlayerRole.IsTeamMember(msg->header.stID) )
					s_CUI_Group.Refeash();
			}
			else
			{

				if (msg->shReliveCnt != 0xffff)
				{
					int _temp = theCountryConfig.GetReliveSetting().GetFreeReliveLimitByLevel(thePlayerRole.GetLevel()) - msg->shReliveCnt; //剩余复活次数

					_temp = _temp > 0 ? _temp : 0;

					s_CUI_ID_FRAME_ESCDLG.m_HeroReliveCnt = msg->shReliveCnt;
					*(s_CUI_ID_FRAME_ESCDLG.m_pID_TEXT_ReLiveCnt) = _temp;
				}


				assert( "Server send An error ID ( I dead ??? )" );
				OutputDebugString( "Server send An error ID ( I dead ??? )\n" );
			}
		}
	}
	pPlayer = NULL;
	unguard;
}

void CPlayerMgr::OnMsgGuildReqInvite( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgInviteJoinGuildReq);
	MsgInviteJoinGuildReq* pInvite = (MsgInviteJoinGuildReq*)pMsg;

	// 判断是否拒绝入帮会
	bool bInFight = false;
	if( theHeroGame.GetPlayerMgr()->GetMe() )
		bInFight = theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting);
	bool bRefuseInFight = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseAddGangInFight );
	bool bRefuse = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseAddGang );
	if( (bInFight && bRefuseInFight) || (!bInFight && bRefuse) )
	{
		GuildReqInviteCallback(false, pInvite);
		return;
	}

	if (!thePlayerRole.GetGuildById(pInvite->nGuildID))
	{
		return;
	}
	char szContent[256];
	MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_GuildInviteMessage ), pInvite->szInviterName, thePlayerRole.GetGuildById(pInvite->nGuildID)->GetName());
	s_CUI_ID_FRAME_MessageBox.Show( szContent, theXmlString.GetString(eText_Guild_GuildInvite),
		CUI_ID_FRAME_MessageBox::eTypeYesNo, false,
		GuildReqInviteCallback, pInvite, pInvite->header.stLength );

	thePlayerRole.UpdateUI();

	unguard;
}

void CPlayerMgr::OnReqMsgCovCorps( Msg *pMsg )
{
	guardfunc;

	thePlayerRole.m_bCorps = TRUE;
	//更新界面
	thePlayerRole.UpdateUI();

	unguard;
}

void CPlayerMgr::OnMsgEquipChanged2( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgEquipChanged2);
	MsgEquipChanged2 *pEquip = (MsgEquipChanged2* )pMsg;

	CPlayer *pPlayer = FindByID( pEquip->header.stID );
	if( !pPlayer )
		return;

	if(pPlayer != GetMe())
	{
		pEquip->equip.SetLock(false);
	}

	int nWhere = pEquip->cWhere;
	nWhere = CEquipPartMap::Instance()->GetLogicPart(nWhere);

	pPlayer->SetEquip( nWhere, &pEquip->equip );
	//从新读取模型
	pPlayer->ChangeSkeletonAndEquipAllItem( pPlayer->HasFightFlag(eFighting) );
	if( pPlayer->GetAnim() )
		pPlayer->GetAnim()->UpdateHardItem( pPlayer->HasFightFlag(eFighting), pPlayer->GetEquip() );

	if( pPlayer == GetMe() )
	{
		s_CUI_ID_FRAME_BaseProperty.RefreshEquip();
	}

	// 更新动作
	if( !(pPlayer->GetSitStatus() && !pPlayer->GetSitInterrupt()) && !pPlayer->IsInWater() )
	{
		pPlayer->SetShowWeapon(TRUE);
		if( pPlayer->IsMoving() )
		{
			if( !pPlayer->IsJumping() )
				pPlayer->SwitchRunAnim();
		}
		else
			pPlayer->SwitchIdleAnim();
	}
	else
		pPlayer->SetShowWeapon(FALSE);

	// added, jiayi, [2010/2/26]
	pPlayer->CalcMinimalStar();
	unguard;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
//返回掉落物品
void CPlayerMgr::OnMsgAckDropItem2( Msg*pMsg )
{
	guardfunc;
	//丢弃物品
	CHECK_MSGLEN( pMsg, MsgAckDropItem2);
	MsgAckDropItem2 *pAckDrop = ( MsgAckDropItem2* )pMsg;
	if ( pAckDrop->stResut == MsgAckDropItem2::Result_Success )
	{
		Assert(0 && "MsgAckDropItem2");
	}
	else if(pAckDrop->stResut == MsgAckDropItem2::Result_CanNotDrop)
	{
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_ThisItemCanNotDrop ) );
	}
	thePlayerRole.UpdateUI();
	unguard;
}

void CPlayerMgr::OnMsgUpdateVisualEquip(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgUpdateVisualEquip);
	MsgUpdateVisualEquip *pVisualEquip = (MsgUpdateVisualEquip *)pMsg;

	bool bUpdateEquip = false;
	for (int i=0; i < EEquipPartType_MaxEquitPart; i++)
	{
		SCharItem* pCharItem = &pVisualEquip->item[i];

		for(int k=0;k<thePlayerRole.m_bag.GetNowBagSize();++k)
		{
			SCharItem myItem = thePlayerRole.m_bag.m_pPackItem[k];
			if(myItem.itembaseinfo.nOnlyInt == pCharItem->itembaseinfo.nOnlyInt
				&& myItem.itembaseinfo.nOnlyInt != 0)
			{
				pCharItem->SetLock(myItem.IsLock());
				pCharItem->SetUnLockTime(myItem.GetUnLockTime());
				pCharItem->SetUnLockLeftTime(myItem.GetUnLockLeftTime());
			}
		}

		thePlayerRole.Equip( pCharItem, i);		
	}

	if(GetMe() )
		GetMe()->UpdateEquip();

	s_CUI_ID_FRAME_BaseProperty.RefreshEquip();

	/*
	* Author:	2012-8-20 wangshuai
	* Desc: 	上马时也要显示武器
	*/

	// 更新动作
	if (GetMe() )
	{
		if (!(GetMe()->GetSitStatus() && !GetMe()->GetSitInterrupt()) && !GetMe()->IsInWater() )
		{
			if ( GetMe()->IsMoving() )
			{
				GetMe()->SwitchRunAnim();
				if (GetMe()->IsMounting())
				{
					GetMe()->SetShowWeapon(TRUE);
				}
				else
				{
					GetMe()->SetShowWeapon(TRUE);
				}
			}
			else if( GetMe()->GetAnim() && GetMe()->GetAnim()->CanSwitchIdleAnim() )
			{
				
				GetMe()->SwitchIdleAnim();
				if (GetMe()->IsMounting())
				{
					GetMe()->SetShowWeapon(TRUE);
				}
				else
				{
					GetMe()->SetShowWeapon(TRUE);
				}
				
			}
			else
				GetMe()->SetShowWeapon(FALSE);
		}
		else
			GetMe()->SetShowWeapon(FALSE);
	}

	//更新界面
	thePlayerRole.UpdateArmourUI();

	if( GetMe() )
		GetMe()->CalcMinimalStar();

	unguard;
}


//更新player身上装备的数据
void CPlayerMgr::OnMsgUpdateEquipData( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgUpdateFightData);
	MsgUpdateFightData *pEquipData = (MsgUpdateFightData *)pMsg;

	thePlayerRole.FreshEquipData( &(pEquipData->fightData) );

	//更新界面
	thePlayerRole.UpdateUI();
	// 更改属性信息
	//Player
	CPlayer *pPlayerMe = theHeroGame.GetPlayerMgr()->GetMe();	
	if(!pPlayerMe)
		return;

	pPlayerMe->SetMoveRate(
		pEquipData->fightData.moveSpeed );

	s_CUI_ID_FRAME_BaseProperty.Refresh();

	unguard;
}

//更新角色背包的数据
void CPlayerMgr::OnMsgUpdateBag(Msg* pMsg)
{
	guardfunc;
	MsgUpdateBag* pUpdateMsg = (MsgUpdateBag* )pMsg;
	switch (pUpdateMsg->ucItemBagType)
	{
	case BT_NormalItemBag:
		// 数据越界检查
		if( pUpdateMsg->stBagIndexBegin + pUpdateMsg->stNum > thePlayerRole.m_bag.GetNowBagSize() )
		{
			Assert(0 && "MsgUpdateBag(BT_NormalItemBag) 数据越界，消息更新失败！");
			LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "MsgUpdateBag(BT_NormalItemBag) 数据越界，消息更新失败！");
			break;
		}
		for (int i = 0; i < thePlayerRole.m_bag.GetNowBagSize(); ++i)
			thePlayerRole.m_bag.m_pPackItem[i].itembaseinfo.ustItemID = InvalidLogicNumber;

		memcpy(thePlayerRole.m_bag.m_pPackItem + pUpdateMsg->stBagIndexBegin,
			pUpdateMsg->stPackItems, pUpdateMsg->stNum * sizeof(SCharItem));

        // 刷背包的 Enable 统一流程      modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshNormalPackEnables();

		// 更新快捷栏物品
		s_CUI_ID_FRAME_PACK.UpdateHotkeyAfterClearupBag();
		break;
	case BT_MaterialBag:
		// 数据越界检查
		if( pUpdateMsg->stBagIndexBegin + pUpdateMsg->stNum > thePlayerRole.m_bagMaterial.GetNowBagSize() )
		{
			Assert(0 && "MsgUpdateBag(BT_MaterialBag) 数据越界，消息更新失败！");
			LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "MsgUpdateBag(BT_MaterialBag) 数据越界，消息更新失败！");
			break;
		}
		for (int i = 0; i < thePlayerRole.m_bagMaterial.GetNowBagSize(); ++i)
			thePlayerRole.m_bagMaterial.m_pPackItem[i].itembaseinfo.ustItemID = InvalidLogicNumber;

		memcpy(thePlayerRole.m_bagMaterial.m_pPackItem + pUpdateMsg->stBagIndexBegin,
			pUpdateMsg->stPackItems, pUpdateMsg->stNum * sizeof(SCharItem));
		
        // 刷背包的 Enable 统一流程      modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshMaterialPackEnables();

		break;
	case BT_TaskBag:
		// 数据越界检查
		if( pUpdateMsg->stBagIndexBegin + pUpdateMsg->stNum > thePlayerRole.m_bagTask.GetNowBagSize() )
		{
			Assert(0 && "MsgUpdateBag(BT_TaskBag) 数据越界，消息更新失败！");
			LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "MsgUpdateBag(BT_TaskBag) 数据越界，消息更新失败！");
			break;
		}
		for (int i = 0; i < thePlayerRole.m_bagTask.GetNowBagSize(); ++i)
			thePlayerRole.m_bagTask.m_pPackItem[i].itembaseinfo.ustItemID = InvalidLogicNumber;

		memcpy(thePlayerRole.m_bagTask.m_pPackItem + pUpdateMsg->stBagIndexBegin,
			pUpdateMsg->stPackItems, pUpdateMsg->stNum * sizeof(SCharItem));
		
        // 刷背包的 Enable 统一流程      modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshTaskPackEnables();
		break;
	case BT_StorageBag:
		// 数据越界检查
		if( pUpdateMsg->stBagIndexBegin + pUpdateMsg->stNum > STORAGE_ITEMGRID_MAX )
		{
			Assert(0 && "MsgUpdateBag(BT_StorageBag) 数据越界，消息更新失败！");
			LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "MsgUpdateBag(BT_StorageBag) 数据越界，消息更新失败！");
			break;
		}
		for (int i = 0; i < STORAGE_ITEMGRID_MAX; ++i)
			thePlayerRole.m_stStorage.stStorageItems[i].itembaseinfo.ustItemID = InvalidLogicNumber;

		memcpy(thePlayerRole.m_stStorage.stStorageItems + pUpdateMsg->stBagIndexBegin,
			pUpdateMsg->stPackItems, pUpdateMsg->stNum * sizeof(SCharItem));
		s_CUI_ID_FRAME_Storage.Refeash();
		break;
	}
	s_CUI_ID_FRAME_LotteryGame.RefreshBoxNKeyIndexByGuid();
	unguard;
}

//卸下成功
void CPlayerMgr::OnMsgUpdateShortCutBag( Msg*pMsg )
{
	guardfunc;
	assert( false && "该函数现在不能用要重写!!!!!!" );
	unguard;
}

void CPlayerMgr::OnAckGlodCovSilver( Msg* pMsg )
{
	guardfunc;
	assert(0);
	unguard;
}

void CPlayerMgr::OnMsgRMBConsumeScoreChange(Msg* pMsg)
{
 guardfunc;
 CHECK_MSGLEN( pMsg, MsgRMBConsumeScore);

 MsgRMBConsumeScore *pChange = (MsgRMBConsumeScore*)(pMsg);
 DWORD ShopCenterScore = thePlayerRole.GetData( CPlayerRole::TYPE_ShopCenterScore );

 char buf[256];
 if(ShopCenterScore > pChange->jifen)
 {
	 MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eText_LoseShopConsumeScore), ShopCenterScore - pChange->jifen);
	 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Money_Change, buf );
 }
 else if (ShopCenterScore < pChange->jifen)
 {
	 MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eText_AddShopConsumeScore),pChange->jifen - ShopCenterScore);
	 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Money_Change, buf );
 }

 thePlayerRole.Update( CPlayerRole::TYPE_ShopCenterScore, pChange->jifen );
 s_CUI_ID_FRAME_ShopCenter.RefreshMoney();
 s_CUI_ID_FRAME_PACK.RefreshMoney();
 
 

 unguard;
}
//MsgRMBConsumeScore
void CPlayerMgr::OnMsgRMBGoldChange( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgRMBGoldChange);
	DWORD dwSrcSilver = thePlayerRole.GetData( CPlayerRole::TYPE_Silver );
	DWORD dwSrcGold = thePlayerRole.GetData( CPlayerRole::TYPE_GLOD );


	MsgRMBGoldChange *pChange = (MsgRMBGoldChange*)(pMsg);
	{
		DWORD dwJinDing = thePlayerRole.GetData(CPlayerRole::TYPE_JinDing);
		DWORD dwJinPiao = thePlayerRole.GetData(CPlayerRole::TYPE_JinPiao);
		if (dwJinDing > pChange->jinDing )
		{
			char buf[256];
			MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eText_LoseJinDing), dwJinDing - pChange->jinDing);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Money_Change, buf );
		}
		else if (dwJinDing < pChange->jinDing)
		{
			char buf[256];
			MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eText_GetJinDing), pChange->jinDing - dwJinDing);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Money_Change, buf );
		}

		if (dwJinPiao > pChange->jinPiao )
		{
			char buf[256];
			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,theXmlString.GetString(eText_LoseJinPiao), dwJinPiao - pChange->jinPiao);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Money_Change, buf );
		}
		else if (dwJinPiao < pChange->jinPiao)
		{
			char buf[256];
			MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1,theXmlString.GetString(eText_GetJinPiao), pChange->jinPiao - dwJinPiao);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Money_Change, buf );
		}

		thePlayerRole.Update( CPlayerRole::TYPE_JinDing, pChange->jinDing );
		thePlayerRole.Update( CPlayerRole::TYPE_JinPiao, pChange->jinPiao );

		s_CUI_ID_FRAME_PACK.RefreshMoney();
		s_CUI_ID_FRAME_ShopCenter.RefreshMoney();
	}

	unguard;
}


void CPlayerMgr::OnMsgMoneyChange( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgMoneyChange);
	DWORD dwMoney = thePlayerRole.GetData( CPlayerRole::TYPE_MONEY );
	MsgMoneyChange* pChange = (MsgMoneyChange*)pMsg;
	thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pChange->dwNumber );
	s_CUI_ID_FRAME_PACK.RefreshMoney();

	//
	std::stringstream sstr;
	if ( pChange->dwNumber > dwMoney )
	{
		int nMoney = pChange->dwNumber - dwMoney;

		int gold = 0, silver = 0,copper = 0;
        thePlayerRole.GetGSCFromMoney(nMoney,gold,silver,copper);

		sstr << theXmlString.GetString(eText_YouGet_Money);
		if (gold > 0)
			sstr << gold << theXmlString.GetString(eText_Money_Gold);
		if (silver > 0)
			sstr << silver << theXmlString.GetString(eText_Money_Silver);
		if (copper > 0)
			sstr << copper << theXmlString.GetString(eText_Money_Copper);
	}
	else if (dwMoney > pChange->dwNumber)
	{
		int nMoney = dwMoney - pChange->dwNumber;

		int gold = 0;
		int silver = 0;
		int copper = 0;
		thePlayerRole.GetGSCFromMoney(nMoney,gold,silver,copper);

		sstr << theXmlString.GetString(eText_YouLost);
		if (gold > 0)
			sstr << gold << theXmlString.GetString(eText_Money_Gold);
		if (silver > 0)
			sstr << silver << theXmlString.GetString(eText_Money_Silver);
		if (copper > 0)
			sstr << copper << theXmlString.GetString(eText_Money_Copper);
	}
	if (sstr.str().length() > 0)
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Money_Change, sstr.str().c_str() );
	unguard;
}

void CPlayerMgr::OnMsgGetItem2( Msg*pMsg )
{
	guardfunc;
	//得到物品
	CHECK_MSGLEN( pMsg, MsgGetItem2);
	MsgGetItem2 *pGetItem = ( MsgGetItem2* )pMsg;

	switch( pGetItem->enResult )
	{
		// 成功
	case MsgGetItem2::RESULT_SUCCESS:
		{	
			if( m_pMe )
				m_pMe->SwitchPickAnim();
			s_CUI_ID_FRAME_PACK.PushGoods( &pGetItem->item );
			s_CUI_ID_FRAME_MainMenu.CheckNeedSparkPack(pGetItem->itemSource);
			s_CUI_ID_FRAME_AutoAttackSet.RefreshQuestUI(); //lyh++ 当添加物品的时候 刷新下自动挂机的药品ui
			theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
		}
		break;
		// 没有空间
	case MsgGetItem2::RESULT_NOSPACE:
		{
			ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pGetItem->item.itembaseinfo.ustItemID );
			if( !pItemDetail )
			{
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_ItemNoPlace ) );
				//没有空间了，就不需要在自动pick道具了
				theHeroGame.GetPlayerMgr()->ClearRoleGetRangeItem();
				return;
			}

			switch (pItemDetail->ucItemType)
			{
			case ItemDefine::ITEMTYPE_MATERIAL:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_MaterialPackFull ) );
				break;
			case ItemDefine::ITEMTYPE_TASK:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_TaskPackFull ) );
				break;
			default:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_NormalPackFull ) );
				break;
			}

			//没有空间了，就不需要在自动pick道具了
			theHeroGame.GetPlayerMgr()->ClearRoleGetRangeItem();
		}
		break;
	case MsgGetItem2::RESULT_ITEMLOCKED:
		{
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_ItemHaveBeenLocked));
			theHeroGame.GetPlayerMgr()->ClearRoleGetRangeItem();
		}
	default:
		{
			//没有空间了，就不需要在自动pick道具了
			theHeroGame.GetPlayerMgr()->ClearRoleGetRangeItem();
		}
		break;
	}

	thePlayerRole.UpdateUI();
	unguard;
}

//
void CPlayerMgr::OnMsgMapLoaded( Msg*pMsg )
{
	guardfunc;
	CPlayer *pPlayer = FindByID( pMsg->header.stID );
	if( !pPlayer )
		return;
	unguard;
}

void CPlayerMgr::OnMsgAckHPInfo( Msg *pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckHPInfo);
	MsgAckHPInfo *pAck = (MsgAckHPInfo*)pMsg;
	//
	CPlayer *pPlayer = FindByID(pAck->sNpcID);
	if( !pPlayer )
		return;
	pPlayer->SetHPInfo( pAck->nHp,pAck->nHpMax );
	unguard;
}

// 接收到改变坐骑的消息
void CPlayerMgr::OnMsgChangeDrome( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgChangeDrome);
	MsgChangeDrome* pchangedrome = (MsgChangeDrome*)pMsg; 
	CPlayer* pPlayer = FindByID( pchangedrome->header.stID );
	if( pPlayer )
	{
		if( pchangedrome->nDromeID >= 0 )
		{
			switch (pchangedrome->ucOpType)
			{
			case MsgChangeDrome::EOT_Active:
				if (thePlayerRole.GetActivedMount())
					thePlayerRole.RemoveMountSkill(*thePlayerRole.GetActivedMount());

				if( thePlayerRole.GetMountByGUID(pchangedrome->guid) )
				{
					thePlayerRole.ActiveMountByGUID(pchangedrome->guid);
					thePlayerRole.AddMountSkill(*thePlayerRole.GetMountByGUID(pchangedrome->guid));

					s_CUI_ID_FRAME_Pet.Refresh();
					s_CUI_ID_FRAME_MAIN.RefeashHotKey();
					s_CUI_ID_FRAME_Exmain.RefeashHotNumber();

					// 出战的逻辑
					s_CUI_ID_FRAME_PetMain.SetVisable( true );
					s_CUI_ID_FRAME_PetMain.Refresh();

					/*SMountItem sMount = s_CUI_ID_FRAME_Pet.GetCurrentMount();
					for (int i=0;i<EBaseAttr_MaxSize;i++)
					{
						thePlayerRole.m_charinfo.baseinfo.baseProperty.baseAttr.baseAttrValue[i].pet = sMount.baseInfo.currentAttribute[i]* sMount.baseInfo.aptitudeAttribute[i]/100;
						thePlayerRole.m_charinfo.baseinfo.baseProperty.baseAttr.baseAttrValue[i].petPer = 0;
						thePlayerRole.m_charinfo.baseinfo.baseProperty.baseAttr.baseAttrValue[i].UpdateFinal();

					}
					
					SCharBaseAttr baseAttr = thePlayerRole.GetCharInfo2().baseinfo.baseProperty.baseAttr;
					SCharFightAttr fightAttr = thePlayerRole.GetCharInfo2().baseinfo.baseProperty.fightAttr;
					for (int j=0;j<EBaseAttr_MaxSize;j++)
					{
						ProcessCharInfo::BaseAttrEffectFightAttr( j, ECustomDataPart_pet, baseAttr.baseAttrValue[j], thePlayerRole.GetProfession(), fightAttr, true ); 
					}*/

					if (s_CUI_ID_FRAME_SKILL.IsVisable())
						s_CUI_ID_FRAME_SKILL.RefreshCommon();
				}				
				break;
			case MsgChangeDrome::EOT_UnActive:
				if (thePlayerRole.GetActivedMountGUID() == pchangedrome->guid)
				{
					thePlayerRole.RemoveMountSkill(*thePlayerRole.GetActivedMount());
					/*SBaseProperty baseProperty = thePlayerRole.GetCharInfo2().baseinfo.baseProperty;
					for (int i=0;i<EBaseAttr_MaxSize;i++)
					{
						thePlayerRole.m_charinfo.baseinfo.baseProperty.baseAttr.ClearPart(ECustomDataPart_pet);
						thePlayerRole.m_charinfo.baseinfo.baseProperty.baseAttr.UpdateFinal();
						ProcessCharInfo::BaseAttrEffectFightAttr( i, ECustomDataPart_pet,baseProperty.baseAttr.baseAttrValue[i], thePlayerRole.GetProfession(), baseProperty.fightAttr, true);
					}*/
				}

				thePlayerRole.UnactiveMountByGUID(pchangedrome->guid);

				s_CUI_ID_FRAME_Pet.Refresh();
				s_CUI_ID_FRAME_MAIN.RefeashHotKey();
				s_CUI_ID_FRAME_Exmain.RefeashHotNumber();

				// 休息的逻辑
				s_CUI_ID_FRAME_PetMain.SetVisable( false );

				if (s_CUI_ID_FRAME_SKILL.IsVisable())
					s_CUI_ID_FRAME_SKILL.RefreshCommon();
				break;
			case MsgChangeDrome::EOT_Ride:
				pPlayer->MountMonster( pchangedrome->nDromeID, pchangedrome->nMountLevel );
				s_CUI_ID_FRAME_MAIN.RefeashHotKey();
				s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
				break;
			case MsgChangeDrome::EOT_Discard:

				if( thePlayerRole.GetMountByGUID(pchangedrome->guid) )
				{
					ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID(
						thePlayerRole.GetMountByGUID(pchangedrome->guid)->baseInfo.id );
					if (pDrome)
					{
						char szInfo[256];
						MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_YouLost_N_S), 1, pDrome->GetName() );					
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)thePlayerRole.GetMountByGUID(pchangedrome->guid), 1, BT_MountBag );
					}

					if (thePlayerRole.GetActivedMountGUID() == pchangedrome->guid)
						thePlayerRole.RemoveMountSkill(*thePlayerRole.GetActivedMount());

					thePlayerRole.RemoveMountByGUID(pchangedrome->guid);
					s_CUI_ID_FRAME_Pet.Refresh();
					s_CUI_ID_FRAME_MAIN.RefeashHotKey();
					s_CUI_ID_FRAME_Exmain.RefeashHotNumber();

					if (s_CUI_ID_FRAME_SKILL.IsVisable())
						s_CUI_ID_FRAME_SKILL.RefreshCommon();
				}


				break;
			}
		}
		else
		{
			pPlayer->DisMount();
			//duorenzuoji 下马的角色是我的司机 
			if (pPlayer->GetID() == m_pMe->GetCarrierPlayerID())
			{
				m_pMe->SetCarrierDriver(-1);
				pPlayer->SetCarrierDriver(-1);
			}
		}
	}
    s_CUI_ID_FRAME_PetList.Refresh();
	unguard;
}

//------- 添加任务    (   at 2004-2-19)
void CPlayerMgr::OnMsgAddMissionIntro( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAddMissionIntro);
	MsgAddMissionIntro* pIntro = (MsgAddMissionIntro*)pMsg;
	unguard;
}
//------- 除非任务    (   at 2004-2-19)
void CPlayerMgr::OnMsgDelMissionIntro( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgDelMissionIntro);
	MsgDelMissionIntro* pIntro = (MsgDelMissionIntro*)pMsg;
	unguard;
}

// 接收到属性更改消息
void CPlayerMgr::OnMsgAttrChanged(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgCharAttrChanged);
	MsgCharAttrChanged* pCharAttrChanged = (MsgCharAttrChanged*)pMsg;
	DWORD dwValue = 0;
	float fValue;
	short stValue;
	int	  nValue;
	__int64 n64Value = 0;
	CPlayer *pPlayer = this->FindByID( pMsg->header.stID );
	if( !pPlayer )
		return;
    CScreenInfoManager::Instance()->SetUnRiseInfoBegin();
	for (int n=0; n<pCharAttrChanged->iChangeCount; n++)
	{
		if(pPlayer == m_pMe&&!m_pMe->IsFirstOnline())
			m_pMe->ShowAttrChangeInfo(pCharAttrChanged->pAttrChanged[n]);
	}
	for( int n=0; n<pCharAttrChanged->iChangeCount; n++ )
	{
		dwValue = pCharAttrChanged->pAttrChanged[n].data.dwValue;
		fValue = pCharAttrChanged->pAttrChanged[n].data.fValue;
		stValue = pCharAttrChanged->pAttrChanged[n].data.stValue;
		nValue = pCharAttrChanged->pAttrChanged[n].data.nValue;
		n64Value = pCharAttrChanged->pAttrChanged[n].data.n64Value;

		//如果放在这里循环，可能造成数据不同步。比如一个数据还没有得到原来的值而已经被新值覆盖
// 		if(pPlayer == m_pMe&&!m_pMe->IsFirstOnline())
// 			m_pMe->ShowAttrChangeInfo(pCharAttrChanged->pAttrChanged[n]);   

		switch( pCharAttrChanged->pAttrChanged[n].ustWhichAttr )
		{
		case CharAttr_Critical://暴
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_CRITICLE, fValue );
			}
			break;
		case CharAttr_Tenacity://暴抗
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_TENACITY, fValue );
			}
			break;
		case CharAttr_CriticalIntensity://暴击倍率
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_CRITICLEINTENSITY, stValue );
			}
			break;
		case CharAttr_MoveSpeed:// 移动速度ter
			{
				pPlayer->SetMoveRate( fValue );
				if( pPlayer->IsMoving() )
				{
					if( pPlayer->IsCountermarch() )
					{
						pPlayer->SwitchWalkBackWardsAnim();
					}
					else
					{
						pPlayer->SwitchRunAnim();
					}
				}
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_MOVESPEED, fValue );					
			}
			break;
		case CharAttr_XPValue:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_ExPower, stValue );

				//pPlayer->SetExPower( stValue );
			}
			break;
		case CharAttr_HP:
			{
				if (pPlayer->IsDead())
				{
					break;
				}
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_HP, nValue );
				
				pPlayer->SetHPInfo_HP( nValue );
			}
			break;
		case CharAttr_ActivePetHP:
			{
				SPetItem *m_pet = thePlayerRole.GetActivedPet();
				if (m_pet != NULL)
				{
					m_pet->baseInfo.hp = nValue;
				}
			}
			break;
		case CharAttr_HPMax:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_HPMAX, nValue );
				pPlayer->SetHPInfo_HPMax( nValue );
			}
			break;
		case CharAttr_MP:
			if( pPlayer == m_pMe )
				thePlayerRole.Update( CPlayerRole::TYPE_MP, nValue );
			
			break;
		case CharAttr_MPMax:
			{	
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_MPMAX, nValue );
			}
			break;
		case CharAttr_Exp:
			{	
				if( pPlayer == m_pMe )
				{
					thePlayerRole.Update( CPlayerRole::TYPE_EXP, n64Value );
					s_CUI_ID_FRAME_MAIN.RefreshExp();
				}
			}
			break;
		case	CharAttr_CurGetExp:
			{
				char szTemp[128] = {0};
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1,theXmlString.GetString(eText_FightGetExp),pPlayer->GetName(),dwValue);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szTemp );
				if( m_pMe )
					m_pMe->OnShowFlyText( 0, dwValue, 0, GlobalTexture::eAddExp );
			}
			break;
		case CharAttr_LostExp:
			{
				if( dwValue > 0 )
				{
					char szBuff[128] = {0};
					MeSprintf_s( szBuff, 128, theXmlString.GetString( eText_CharAttr_LossExp ), dwValue );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Reputation_Change, szBuff );
				}
			}
			break;
		case CharAttr_ActivePetCurGetExp:
			{
				/*char szTemp[128] = {0};
				char m_petName[dr_MaxPlayerName] = {0};
				if (thePlayerRole.GetActivedPet() != NULL)
				{
					strncpy(m_petName,thePlayerRole.GetActivedPet()->baseInfo.szName,sizeof(thePlayerRole.GetActivedPet()->baseInfo.szName)-1);
				}
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1,theXmlString.GetString(eText_FightGetExp),m_petName,dwValue);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szTemp );*/
				/*if( m_pMe )
					m_pMe->OnShowFlyText( 0, dwValue, 0, GlobalTexture::eAddExp );*/
			}
			break;
		case	CharAttr_CurGetSkillExp:
			{
				char szTemp[128] = {0};
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1,theXmlString.GetString(eText_AddSkillExp),dwValue);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szTemp );
				if( m_pMe )
					m_pMe->OnShowFlyText( 0, dwValue, 0, GlobalTexture::eAddSkillExp );
			}
			break;
		case CharAttr_CurGetGuildContribute:     // 当前获得帮贡
			{
				if( dwValue > 0 && m_pMe )
					m_pMe->OnShowFlyText( 0, dwValue, 0, GlobalTexture::eAddBangGong );
			}
			break;

		case CharAttr_ExpNotUsed:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_EXPNOTUSED, dwValue );
				s_CUI_ID_FRAME_MainMenu.CheckNeedSparkBaseProperty();
				break;
			}
		case CharAttr_AttackPhysics:
            if( pPlayer == m_pMe )
            { thePlayerRole.Update( CPlayerRole::TYPE_ATTACKPHYSICS, fValue ); }
			break;
		case CharAttr_AttackMagic:
			if( pPlayer == m_pMe )
            { thePlayerRole.Update( CPlayerRole::TYPE_AttackMagic, fValue ); }
			break;
		case CharAttr_DefendPhysics:
			if( pPlayer == m_pMe )
            { thePlayerRole.Update( CPlayerRole::TYPE_DefendPhysics, fValue ); }
			break;
		case CharAttr_DefendMagic:
			if( pPlayer == m_pMe )
            { thePlayerRole.Update( CPlayerRole::TYPE_DefendMagic, fValue ); }
			break;
		case CharAttr_HPRestore:
			if( pPlayer == m_pMe )
			{
				thePlayerRole.Update( CPlayerRole::TYPE_HPRESTORE, fValue );
			}
			break;
		case CharAttr_MPRestore:
			if( pPlayer == m_pMe )
			{
				thePlayerRole.Update( CPlayerRole::TYPE_MPRESTORE, fValue );
			}
			break;
		case CharAttr_Exact:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_EXACT, stValue );
			}
			break;
		case CharAttr_Dodge:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_DODGE, stValue );
			}
			break;
		case CharAttr_AttackSpeed:
			{				
				pPlayer->SetNormalAttackRate( fValue );
			}
			break;
		case CharAttr_BackStrike:                 // 背击伤害
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_BackStrike, stValue );
			}
			break;
		case CharAttr_BackStrikeResist:           // 背击抗性
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_BackStrikeResist, stValue );
			}
			break;
		case CharAttr_BreakStrike:                // 破甲伤害
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_BreakStrike, stValue );
			}
			break;
		case CharAttr_StabStrike:                 // 贯穿伤害
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_StabStrike, stValue );
			}
			break;
		case CharAttr_ElementStrike:              // 元素伤害
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_ElementStrike, stValue );
			}
			break;
		case CharAttr_ToxinStrike:                // 毒素伤害
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_ToxinStrike, stValue );
			}
			break;
		case CharAttr_SpiritStrike:               // 精神伤害
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_SpiritStrike, stValue );
			}
			break;
		case CharAttr_BreakResist:                // 破甲抗性
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_BreakResist, stValue );
			}
			break;
		case CharAttr_StabResist:                 // 贯穿抗性
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_StabResist, stValue );
			}
			break;
		case CharAttr_ElementResist:              // 元素抗性
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_ElementResist, stValue );
			}
			break;
		case CharAttr_ToxinResist:                // 毒素抗性
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_ToxinResist, stValue );
			}
			break;
		case CharAttr_SpiritResist:               // 精神抗性
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_SpiritResist, stValue );
			}
			break;
// 		case CharAttr_IntonateSpeed:
// 			{
// 				if( pPlayer == m_pMe )
// 					thePlayerRole.Update( CPlayerRole::TYPE_INTONATESPEED, stValue );
// 			}
// 			break;
		case CharAttr_Death:				//死亡
			{			
				pPlayer->AddDeathTask();
			}
			break;
		case CharAttr_Relive:
			{
			
				pPlayer->m_status.ResetDead();
				pPlayer->Relive(stValue);   // stValue为0代表被玩家复活，1代表去地狱
				if( pPlayer == m_pMe ) //lyh++ 解决玩家复活了 ，如果是自己的消息，则关闭复活度对话框
				s_CUI_ID_FRAME_ESCDLG.SetVisable(false);

				if( s_CUI_ID_FRAME_OnlineAward2.IsVisable() && pPlayer == m_pMe )
					s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable(true);
			}
			break;

		case CharAttr_HPHeal:
			{
				//恢复的血，显示效果
				pPlayer->SetHPInfo_HP(nValue);
				if( pPlayer == m_pMe )
					thePlayerRole.SetPlayerHP(nValue);
			}
			break;
		case CharAttr_HPRestoreEatDrug:
			{
				//吃药恢复的血
				//创建效果！
				pPlayer->SetHPInfo_HP(nValue);
				if( pPlayer == m_pMe )
					thePlayerRole.SetPlayerHP(nValue);
			}
			break;

		case CharAttr_Profession:
			{
				if( pPlayer == m_pMe )
				{
					thePlayerRole.Update( CPlayerRole::TYPE_PROFESSION,stValue );
				}
			}
			break;
		case CharAttr_SkillHPCost:
			{
				pPlayer->SetHPInfo_HP(stValue);
				if( pPlayer == m_pMe )
					thePlayerRole.SetPlayerHP(stValue);
			}
			break;
		case CharAttr_SkillMPCost:
			{
				if( pPlayer == m_pMe )
				{
					thePlayerRole.Update( CPlayerRole::TYPE_MP, thePlayerRole.GetData( CPlayerRole::TYPE_MP ) - stValue );
				}
			}
			break;
		case CharAttr_Country:
			{
				pPlayer->ClearCountryMask();
				pPlayer->SetCountry( stValue );
				pPlayer->ApplyCountryMask();

				if( pPlayer == m_pMe )
				{
					thePlayerRole.SetCountry( stValue );
				}
			}
			break;

		case CharAttr_Level:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_LEVEL, fValue );

				pPlayer->SetLevel( fValue );
			}
			break;

		case CharAttr_FreeRelive:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_FreeReliveCount, stValue );
			}
			break;
		case CharAttr_Strength:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_Strength, fValue );
			}
			break;
		case CharAttr_Stamina:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_Stamina, fValue );
			}
			break;
		case CharAttr_Intelligence:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_Intelligence, fValue );
			}
			break;
		case CharAttr_Agility:
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_Agility, fValue );
			}
			break;
		case CharAttr_SkillExp:
			{	
				if( pPlayer == m_pMe && thePlayerRole.m_pBaseInfo )
                {
					if( dwValue > thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp )
					{
						// 获得
	                    DWORD dwAddValue = dwValue - thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp;
						if( m_pMe )
							m_pMe->OnShowFlyText( 0, dwAddValue, 0, GlobalTexture::eAddSkillExp );

                        char szTemp[128] = {0};
                        MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1,theXmlString.GetString(eText_AddSkillExp),dwAddValue);
                        s_CUI_ChatInfoBox.AddInfo(szTemp,Color_Config.getColor(CC_CHAT_TEAM),MsgChat::CHAT_TYPE_FIGHTINFO);
                    }
					else if( dwValue < thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp )
					{
						// 失去
						DWORD dwLoseValue = thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp - dwValue;
						char szTemp[128] = {0};
						MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1,theXmlString.GetString(eText_LoseSkillExp),dwLoseValue);
						s_CUI_ChatInfoBox.AddInfo(szTemp,Color_Config.getColor(CC_CHAT_TEAM));
					}
					thePlayerRole.Update( CPlayerRole::TYPR_SKILLEXP, dwValue );
                }

			}
			break;
		case CharAttr_SkillExpNotUsed:
			if( pPlayer == m_pMe )
				thePlayerRole.Update( CPlayerRole::TYPR_SKILLEXPNOTUSE, dwValue );
			break;
		case CharAttr_Energy:
			if( pPlayer == m_pMe )
				thePlayerRole.Update( CPlayerRole::TYPE_ENERGY, stValue );
			break;
		case CharAttr_EnergyMax:
			if( pPlayer == m_pMe )
				thePlayerRole.Update( CPlayerRole::TYPE_ENERGY_MAX, stValue );
			break;
		case CharAttr_Vigor:
			if( pPlayer == m_pMe )
				thePlayerRole.Update( CPlayerRole::TYPE_VIGOR, stValue );
			break;
		case CharAttr_VigorMax:
			if( pPlayer == m_pMe )
				thePlayerRole.Update( CPlayerRole::TYPE_VIGOR_MAX, stValue );
			break;
		case CharAttr_NextNotIntonate:
			{
				char str[MAX_PATH] = {0};
				MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%s","Get message from server, next skill not intonate");
				LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, string(str));

				g_bNextNotIntonate = TRUE;
			}
			break;
		case CharAttr_MountExp: 
			if (thePlayerRole.GetActivedMount() && pPlayer == m_pMe)
			{
				// modified, jiayi, [2009/10/23]
				int nLevel = theExpStage.GetMountLevel( n64Value );
				thePlayerRole.GetActivedMount()->baseInfo.exp = n64Value;
				thePlayerRole.GetActivedMount()->baseInfo.level = nLevel;
				s_CUI_ID_FRAME_Pet.Refresh();
			}
			break;
		case CharAttr_MountChangeLevel:
			if (thePlayerRole.GetActivedMount() && pPlayer == m_pMe)
			{
				// 小泡泡提醒		added by zhuomeng.hu		[9/14/2010]
				s_CUI_ID_FRAME_InfoTips.AddpetLevelUpTip();

				thePlayerRole.GetActivedMount()->baseInfo.level = dwValue;
				s_CUI_ID_FRAME_Pet.Refresh();
			}
			break;
		case CharAttr_CurMountHP:
			if (pPlayer == m_pMe)
			{
				short stIndex = dwValue >> 24;
				DWORD dwEnjoy = dwValue & 0xffffff;
				thePlayerRole.GetMountByIndex( stIndex ).baseInfo.hp = dwEnjoy;
				s_CUI_ID_FRAME_Pet.Refresh();
				if ( dwEnjoy < MOUNT_LOWEST_ACTIVE_HP )
				{
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountEnjoymentNotEnough ) );
				}
			}
			break;
		case CharAttr_CurMountHPMax:
			if (thePlayerRole.GetActivedMount() && pPlayer == m_pMe)
			{
				thePlayerRole.GetActivedMount()->baseInfo.hpMax = dwValue;
				s_CUI_ID_FRAME_Pet.Refresh();
			}
			break;
        case CharAttr_MountCountLimit:              // 坐骑可拥有数量
            {
                if( pPlayer == m_pMe )
                {
                    thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount = dwValue;
                    s_CUI_ID_FRAME_Pet.Refresh();
                }
            }
            break;
		case CharAttr_CaoYao: 						// 草药
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_CaoYao, stValue );
			}
			break;
		case  CharAttr_ZhuBao: 					    // 珠宝
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_ZhuBao, stValue );
			}
			break;
		case CharAttr_DuanZao: 						// 锻造
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_DuanZao, stValue );
			}
			break;
		case CharAttr_ZhuJia: 						// 铸甲
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_ZhuJia, stValue );
			}
			break;
		case CharAttr_GongYi: 						// 工艺
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_GongYi, stValue );
			}
			break;
		case CharAttr_XunMa:  					    // 驯马
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_XunMa, stValue );
			}
			break;
		case CharAttr_CaiKuang:                     // 采矿
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_CaiKuang, dwValue );
			}
			break;
		case CharAttr_CaiYao:                       // 采药
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_CaiYao, dwValue );
			}
			break;
        case CharAttr_BuZhuo:                       // 捕马
            {
                if( pPlayer == m_pMe )
                    thePlayerRole.Update( CPlayerRole::TYPE_BuZhuo, dwValue );
            }
            break;
		case CharAttr_BuChong:                       // 捕虫
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_BuChong, dwValue );
			}
			break;
		case CharAttr_Exploit:
			{
				DWORD dwOldReputation = pPlayer->GetExploit();
				pPlayer->SetExploit( dwValue );
				if( pPlayer == m_pMe )
				{
					if( dwOldReputation > dwValue )
					{
						// 提示失去名望
						char szBuff[256] = {0};
						MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouLoseXExploit ), dwOldReputation-dwValue );
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Exploit_Change, szBuff );
					}
					thePlayerRole.Update( CPlayerRole::TYPE_Exploit, dwValue );
					s_CUI_ID_FRAME_Experience.Refresh();
				}
			}
			break;
		case CharAttr_Reputation:
			{
				DWORD dwOldReputation = pPlayer->GetReputation();
				pPlayer->SetReputation( dwValue );
				if( pPlayer == m_pMe )
				{
					if( dwOldReputation > dwValue )
					{
						// 提示失去名望
						char szBuff[256] = {0};
						MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouLoseXReputation ), dwOldReputation-dwValue );
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Reputation_Change, szBuff );
					}
					thePlayerRole.Update( CPlayerRole::TYPE_Reputation, dwValue );
					s_CUI_ID_FRAME_Experience.Refresh();
				}
			}
			break;
		case CharAttr_Honour:
			{
				DWORD dwOldGlory = pPlayer->GetGlory();
				if(pPlayer == GetMe())
					dwOldGlory = thePlayerRole.m_pBaseInfo->liveinfo.honour;
				pPlayer->SetGlory( dwValue );
				if( pPlayer == m_pMe )
				{
					if( dwOldGlory > dwValue )
					{
						// 提示失去荣誉
						char szBuff[256] = {0};
						MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouLoseXGlory ), dwOldGlory-dwValue );
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Reputation_Change, szBuff );
					}
					thePlayerRole.Update( CPlayerRole::TYPE_Glory, dwValue );
					s_CUI_ID_FRAME_Experience.Refresh();
				}
			}
			break;
		case CharAttr_CountryScore:
			{
				DWORD dwOldGlory = pPlayer->GetCountryScore();
				pPlayer->SetCountryScore( dwValue );
				if( pPlayer == m_pMe )
				{
					if( dwOldGlory > dwValue )
					{
						// 提示失去荣誉
						char szBuff[256] = {0};
						MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouLoseXCountryScore ), dwOldGlory-dwValue );
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Reputation_Change, szBuff );
					}
					thePlayerRole.Update( CPlayerRole::TYPE_CountryScore, dwValue );
					s_CUI_ID_FRAME_Experience.Refresh();
				}
			}
			break;
		case CharAttr_GuildContribute:
			{
				if(pPlayer && m_pMe && pPlayer == m_pMe)
					GetMe()->SetGuildOffer(dwValue);
			}
			break;
		case CharAttr_CurGetExploit:
			{
				if( pPlayer && m_pMe && pPlayer == m_pMe )
				{
					char szBuff[256] = {0};
					if( dwValue > 0 )
					{
						D3DXVECTOR3 pos = pPlayer->GetPos();
						int xEffect,yEffect;
						World2Screen( pos,xEffect,yEffect );
						MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouGetXExploit ), dwValue );
						m_pMe->OnShowFlyText( 0, dwValue, 0, GlobalTexture::eAddGongXun );
					}
					else
					{
						MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouLoseXExploit ), dwValue );
					}
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Exploit_Change, szBuff );
				}

			}
			break;
		case CharAttr_CurGetHonour:
			{
				if( pPlayer && m_pMe && pPlayer == m_pMe && dwValue != 0 )
				{
					char szBuff[256] = {0};
					if( dwValue > 0 )
					{
						D3DXVECTOR3 pos = pPlayer->GetPos();
						int xEffect,yEffect;
						World2Screen( pos,xEffect,yEffect );
						MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouGetXGlory ), dwValue );
						m_pMe->OnShowFlyText( 0, dwValue, 0, GlobalTexture::eAddRongYu );
					}
					else
					{
						MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouLoseXGlory ), dwValue );
					}
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Exploit_Change, szBuff );
				}
				//判断以前荣誉和现在荣誉 是否在最低军阶之间
				RankTitleConfig::RankTitleVector& vecTitle = theRankTitleConfig.GetRankTitleVec();
				if(!vecTitle.empty())
				{
					int NowHonour = thePlayerRole.GetCharInfo2().baseinfo.liveinfo.honour;
					int OleHonour = NowHonour - dwValue;
					if(OleHonour < vecTitle[0].nNeedHonour && NowHonour >= vecTitle[0].nNeedHonour)
					{
						//引导玩家开启军阶面板
						/*if(s_CUI_ID_FRAME_RankTitle.IsVisable())
							s_CUI_ID_FRAME_RankTitle.SetVisable(false);*/
						s_CUI_ID_FRAME_BasePropertyBGFrame.SetVisable(true);
						s_CUI_ID_FRAME_BasePropertyBGFrame.ID_CHECKBOX_RankOnCheckBoxCheck(NULL,NULL);
						//s_CUI_ID_FRAME_RankTitle.SetVisable(true);
					}
				}
			}
			break;
		case CharAttr_CurGetCountrySocre:
			{
				if( pPlayer && m_pMe && pPlayer == m_pMe )
				{
					char szBuff[256] = {0};
					if( dwValue > 0 )
					{
						D3DXVECTOR3 pos = pPlayer->GetPos();
						int xEffect,yEffect;
						World2Screen( pos,xEffect,yEffect );
						MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouGetXCountryScore ), dwValue );
						//m_pMe->OnShowFlyText( 0, dwValue, 0, GlobalTexture::eAddGongXun );
					}
					else
					{
						MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_YouLoseXCountryScore ), dwValue );
					}
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Exploit_Change, szBuff );
				}

			}
			break;
		case CharAttr_CurGetReputation:
			{
				if( pPlayer && m_pMe && pPlayer == m_pMe )
				{
					char szBuff[256] = {0};
					if( dwValue > 0 )
					{
						D3DXVECTOR3 pos = pPlayer->GetPos();
						int xEffect,yEffect;
						World2Screen( pos,xEffect,yEffect );
						MeSprintf_s( szBuff, sizeof(szBuff)-1, theXmlString.GetString( eText_YouGetXReputation ), dwValue );	
						m_pMe->OnShowFlyText( 0, dwValue, 0, GlobalTexture::eAddMingWang );
					}
					else
					{						
						MeSprintf_s( szBuff, sizeof(szBuff)-1, theXmlString.GetString( eText_YouLoseXReputation ), dwValue );						
					}	
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Reputation_Change, szBuff );
				}				

			}
			break;
		case CharAttr_MaxKillMonsterCount: //最大杀怪数量
			s_CUI_ID_FRAME_CharacterExp.SetTotalKillNum(dwValue);
			break;
		case CharAttr_CurKillMonsterCount:  //当前杀怪数量
			{
				s_CUI_ID_FRAME_CharacterExp.SetCurrKillNum(dwValue);

				char szWord[512] = {0};                
				MeSprintf_s(szWord,sizeof(szWord)-1,theXmlString.GetString(eText_MAXKILLMONSTER),dwValue,(int)(theKillMonsterCountConfig.GetModulus(dwValue) * 100.0f));

				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, szWord );
			}
			break;
		case CharAttr_AreaRepulation: //刷新地区声望
			thePlayerRole.Update( CPlayerRole::TYPE_AreaRepulation, n64Value );
			break;
		case CharAttr_CanReceivePrentice:        // 当前可以招收徒弟，成功创建师门
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_CanInviteStudent) );
			thePlayerRole.SetCanReceivePrentice();
			s_CUI_ID_FRAME_Master.NeedRefresh();
			break;
		case CharAttr_MasterLevel:               // 当前师门等级
			{
				char szText[256] = {0};
				MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_MasterLevelChange), (int)dwValue);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
				thePlayerRole.SetMasterLevel((unsigned char)dwValue);
				s_CUI_ID_FRAME_Master.NeedRefresh();
			}
			break;
		case CharAttr_MasterValue:               // 当前师门威望值
			{
				DWORD oldValue = thePlayerRole.GetMasterValue();
				if( oldValue > dwValue )
				{
					char szText[256] = {0};
					MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_YouLoseWeiWang), oldValue - dwValue);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
				}
				thePlayerRole.SetMasterValue(dwValue);
				s_CUI_ID_FRAME_Master.NeedRefresh();
			}
			break;
		case CharAttr_MasterExperience:          // 当前的历练值
			{
				DWORD oldExp = thePlayerRole.GetStudentExperience();
				if( oldExp > dwValue )
				{
					char szText[256] = {0};
					MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_YouLoseLiLian), oldExp - dwValue);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
				}
				else
				{
					char szText[256] = {0};
					MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_YouGetLiLian), dwValue - oldExp);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
				}
				thePlayerRole.SetStudentExperience(dwValue);
				s_CUI_ID_FRAME_Master.NeedRefresh();
			}
			break;
		case CharAttr_StorageItemGrid:   // 当前的物品仓库格数
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_Storage, stValue );
			}
			break; 
		case CharAttr_StorageMountGrid:  // 当前的坐骑仓库格数
			{
				if( pPlayer == m_pMe )
					thePlayerRole.Update( CPlayerRole::TYPE_PetSrorage, stValue );
			}
			break;
		case CharAttr_Daoxing:
			{
				if(pPlayer == m_pMe)
					thePlayerRole.Update(CPlayerRole::TYPE_Daoxing,stValue);
			}
			break;
		case CharAttr_BasePotential:
			{
				if(pPlayer == m_pMe)
					thePlayerRole.Update(CPlayerRole::TYPE_BasePotential,stValue);

				s_CUI_ID_FRAME_BaseProperty.SetDianShuControlEnable(stValue > 0);
			}
			break;
		default:
			//assert(false);
			break;
		}
	}
	if( pPlayer == m_pMe )
	{
		m_bNeedUpdateRoleUI = true;
		if(m_pMe->IsFirstOnline())
			m_pMe->SetFirstOnline(false);
	}
    CScreenInfoManager::Instance()->SetUnRiseInfoEnd();

	unguard;
}

// 接收到属性升级消息
void CPlayerMgr::OnMsgAttrLevelUp(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckUpAttrLevel);
	MsgAckUpAttrLevel* pArrtLevelUp = (MsgAckUpAttrLevel*)pMsg;
	DWORD dwCurValue = 0;
	switch(pArrtLevelUp->attrup.stWhichAttr)
	{
	case EBaseAttr_Strength:		// 力量
		dwCurValue = thePlayerRole.GetData(CPlayerRole::TYPE_EXPNOTUSED);
		thePlayerRole.Update( CPlayerRole::TYPE_EXPNOTUSED, dwCurValue);
		dwCurValue = thePlayerRole.GetData(CPlayerRole::TYPE_Strength) + 1;
		thePlayerRole.Update( CPlayerRole::TYPE_Strength,  dwCurValue);
		break;
	case EBaseAttr_Stamina:	// 体质
		dwCurValue = thePlayerRole.GetData(CPlayerRole::TYPE_EXPNOTUSED);
		thePlayerRole.Update( CPlayerRole::TYPE_EXPNOTUSED, dwCurValue);
		dwCurValue = thePlayerRole.GetData(CPlayerRole::TYPE_Stamina) + 1;
		thePlayerRole.Update( CPlayerRole::TYPE_Stamina,  dwCurValue);
		break;
	case EBaseAttr_Agility:			// 敏捷
		dwCurValue = thePlayerRole.GetData(CPlayerRole::TYPE_EXPNOTUSED);
		thePlayerRole.Update( CPlayerRole::TYPE_EXPNOTUSED, dwCurValue);
		dwCurValue = thePlayerRole.GetData(CPlayerRole::TYPE_Agility) + 1;
		thePlayerRole.Update( CPlayerRole::TYPE_Agility,  dwCurValue);
		break;
	case EBaseAttr_Intelligence:    // 智力
		dwCurValue = thePlayerRole.GetData(CPlayerRole::TYPE_EXPNOTUSED);
		thePlayerRole.Update( CPlayerRole::TYPE_EXPNOTUSED, dwCurValue);
		dwCurValue = thePlayerRole.GetData(CPlayerRole::TYPE_Intelligence) + 1;
		thePlayerRole.Update( CPlayerRole::TYPE_Intelligence,  dwCurValue);
		break;			
	}
	if( m_pMe )
	{
// 		m_pMe->SetExact( thePlayerRole.GetData( CPlayerRole::TYPE_EXACT ));
// 		m_pMe->SetShortAtt( thePlayerRole.GetData( CPlayerRole::TYPE_ATTACK ));
// 		m_pMe->SetFarAtt( thePlayerRole.GetData( CPlayerRole::TYPE_ATTACK ));
	}
	thePlayerRole.UpdateUI();

	s_CUI_ID_FRAME_BaseProperty.Refresh();

	unguard;
}

// 接受到放置符石消息
void CPlayerMgr::OnMsgPlaceStone( Msg* pMsg )
{
	guardfunc;
	unguard;
}

// 接受到移除符石消息
void CPlayerMgr::OnMsgRemoveStone( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckRemoveStone);
	MsgAckRemoveStone *pRemoveStone = (MsgAckRemoveStone *)pMsg;
	if( !pRemoveStone->bSuccess )
		return;

	short stStoneIndex = pRemoveStone->removestone.stStoneIndex;
	short stSkillIndex = pRemoveStone->removestone.stSkillIndex;
	short stPos		   = pRemoveStone->removestone.stPos;

	thePlayerRole.UpdateUI();
	unguard;
}

// 接受到放置招式片段消息
void CPlayerMgr::OnMsgPlaceSubSkill( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckPlaceSubSkill);
	MsgAckPlaceSubSkill *pPlaceSubSkill = (MsgAckPlaceSubSkill *)pMsg;
	if( !pPlaceSubSkill->bSuccess )
		return;

	short stSubSkillIndex = pPlaceSubSkill->placesubskill.stSubSkillIndex;
	short stSkillIndex    = pPlaceSubSkill->placesubskill.stSkillIndex;
	short stPos			  = pPlaceSubSkill->placesubskill.stPos;
	bool  bMakeSkillAvailable = pPlaceSubSkill->placesubskill.bMakeSkillAvailable;
	unguard;
}

// 接受到移除招式片段消息
void CPlayerMgr::OnMsgRemoveSubSkill( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckRemoveSubSkill);
	MsgAckRemoveSubSkill *pRemoveSubSkill = (MsgAckRemoveSubSkill *)pMsg;

	if( !pRemoveSubSkill->bSuccess )
		return;

	short stSkillIndex    = pRemoveSubSkill->removesubskill.stSkillIndex;
	short stPos			  = pRemoveSubSkill->removesubskill.stPos;
	unguard;
}

// 接受到制造物品的消息
void CPlayerMgr::OnMsgProduceItem( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckProduceItem);
	MsgAckProduceItem *pProduceItem = (MsgAckProduceItem *)pMsg;

	if( pProduceItem->bSuccess )
	{
		//显示成功！
	}
	else
	{
		//显示失败！
	}		
	unguard;
}

//----
//	看到有人在呤唱
//----
void CPlayerMgr::OnMsgSeeIntonate( Msg*pMsg )
{
	guardfunc;
	unguard;

}

void CPlayerMgr::OnMsgIntonateStart(Msg*pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, Msg_IntonateStart);
	Msg_IntonateStart* pIntonate = (Msg_IntonateStart*)pMsg;	
	OnSeeIntonate( pIntonate->ustSkillID, 
		pIntonate->cSkillLevel, 
		pIntonate->header.stID, 
		pIntonate->target.ustTargetID,
		0,
		pIntonate->usType );
	unguard;
}

void CPlayerMgr::OnMsgIntonateEnd(Msg*pMsg)
{
	guardfunc;
	if( !CanReceivePlayerMsg() )
		return;
	CHECK_MSGLEN( pMsg, Msg_IntonateEnd);
	Msg_IntonateEnd* pIntonate = (Msg_IntonateEnd*)pMsg;
	IntonateEndInfo intonateend;
	intonateend.ustSkillId = pIntonate->ustSkillID;
	intonateend.ustSkillLevel = pIntonate->ustSkillLevel;
	memcpy(intonateend.targetList,pIntonate->targetList,sizeof(pIntonate->targetList));

	//intonateend.target.ustTargetID = pIntonate->target.ustTargetID;
	//intonateend.dwEmissionFlyTime = pIntonate->dwEmissionFlyTime;
	CPlayer* pPlayer = FindByID( pIntonate->header.stID );
	if( !pPlayer )
	{
		assert( false );
		return;
	}

	if (pPlayer != GetMe() && pPlayer->m_cFightStatus.IsHide())
		return;

	//如果当前在吟唱，并且技能需要维持，
	pPlayer->GetActionQueue()->Push_HoldSkillStart( &intonateend );
	pPlayer->SetIntonatingTarget(0);

	// 如果是采集技能结束, 播放死亡动作
	CPlayer *pDestPlayer = NULL;
	if (IsCollectSkill(pIntonate->ustSkillID))
	{
		for (int i = 0; i < MAXEMISSIONNUM; ++i)
		{
			pDestPlayer = FindByID(pIntonate->targetList[i].target.ustTargetID);
			if (pDestPlayer != NULL)
			{
				pDestPlayer->GetAnim()->PlayAnimByActionName( "dead",
					MexAnimCtrl::eSingleFrame,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					"unknown",
					MexAnimCtrl::eHideFrame );
			}
		}
	}
	unguard;
}

void CPlayerMgr::OnMsgHoldSkillEnd(Msg*pMsg)
{
	guardfunc;
	if( !CanReceivePlayerMsg() )
		return;
	CHECK_MSGLEN( pMsg, Msg_HoldSkillEnd);
	Msg_HoldSkillEnd* pSkillEnd = (Msg_HoldSkillEnd*)pMsg;
	CPlayer* pPlayer = FindByID( pSkillEnd->header.stID );
	if( !pPlayer )
	{
		assert( false );
		return;
	}
	pPlayer->GetActionQueue()->Push_HoldSkillEnd();
	pPlayer->SetIntonating(FALSE);
	unguard;
}


void CPlayerMgr::OnMsgSkillCanceled( Msg* pMsg )
{
	guardfunc;
	CPlayer* pPlayer = FindByID( pMsg->header.stID );
	if( !pPlayer )
	{
		assert( false && "msg skill canceled error, player not found" );
		return;
	}
	pPlayer->SetIntonating( FALSE );
	pPlayer->GetActionQueue()->Push_CancelSkill();

	unguard;
}
void CPlayerMgr::OnMsgSkillStatus(Msg*pMsg)
{

	guardfunc;
	CHECK_MSGLEN( pMsg, Msg_SkillStatus);
	Msg_SkillStatus* pMsgStatus = (Msg_SkillStatus*)pMsg;
	if( Msg_SkillStatus::skillstatus_intonate == pMsgStatus->cSkillStatusType )
	{
		//吟唱
		OnSeeIntonate( pMsgStatus->ustSkillID,pMsgStatus->cSkillLevel,
			pMsgStatus->header.stID,-1,pMsgStatus->cPercent, 0 );
	}
	else
	{
		//维持
		OnSeeHoldSkill( pMsgStatus->ustSkillID,pMsgStatus->cSkillLevel,
			pMsgStatus->header.stID, pMsgStatus->cPercent );
	}
	unguard;
}
//----
//	看到有人在做表情动作
//----
void CPlayerMgr::OnMsgSeeExpression(Msg*pMsg)
{
	guardfunc;
	//
	CHECK_MSGLEN( pMsg, MsgAckExpression);
	MsgAckExpression  *pExpression = (MsgAckExpression*)pMsg;
	CExpressionAction::Instance().OnSeeExpressionAction(pExpression->header.stID, pExpression->stTargetID, pExpression->ustActionID);

	unguard;
}
//----
//	看到有人受到了伤害
//----
void CPlayerMgr::OnMsgSeeDamage(Msg*pMsg)
{
	guardfunc;

	CHECK_MSGLEN( pMsg, MsgSeeDamage);
	MsgSeeDamage *pSeeDamage = (MsgSeeDamage *)pMsg;

	for (int i=0; i<pSeeDamage->stResultNum; i++)
	{
		SeeDamageParam kSeeDamageParam;
		kSeeDamageParam.nDst = (int)pSeeDamage->results[i].xResult.stTargetWho;
		kSeeDamageParam.nSrc = (int)pSeeDamage->results[i].xResult.stAttackerWho;
		kSeeDamageParam.iTagNum = (int)pSeeDamage->results[i].xResult.stTagHpNum;
		kSeeDamageParam.iSrcNum = (int)pSeeDamage->results[i].xResult.stSrcHpNum;
		kSeeDamageParam.iBalanceType = (int)pSeeDamage->results[i].xResult.cBalanceType;
		kSeeDamageParam.iTagHp = (int)pSeeDamage->results[i].xResult.nTagHp;
		kSeeDamageParam.iSrcHp = (int)pSeeDamage->results[i].xResult.nSrcHp;
		kSeeDamageParam.iTagMp = (int)pSeeDamage->results[i].xResult.nTagMp;
		kSeeDamageParam.iSrcMp = (int)pSeeDamage->results[i].xResult.nSrcMp;
		kSeeDamageParam.iTagMpNum = (int)pSeeDamage->results[i].xResult.stTagMpNum;
		kSeeDamageParam.iSrcMpNum = (int)pSeeDamage->results[i].xResult.stSrcMpNum;
		kSeeDamageParam.stTagBackAttackNum = (int)pSeeDamage->results[i].xResult.nBackAttack;
		kSeeDamageParam.stStatusID  = pSeeDamage->results[i].stStatusID;
		kSeeDamageParam.stLevel     = pSeeDamage->results[i].stLevel;

		OnSeeDamage((DWORD )pSeeDamage->results[i].xResult.nStatusFlag, kSeeDamageParam);

		// 被玩家攻击闪屏特效
		CPlayer *pSrc = FindByID( (int)pSeeDamage->results[i].xResult.stAttackerWho );
		CPlayer* pDest = FindByID( (int)pSeeDamage->results[i].xResult.stTargetWho );
		if( pSrc && pDest && pSrc->IsPlayer() && pDest->IsPlayer() && pDest == m_pMe && pSrc != m_pMe )
		{
			if (!thePlayerRole.m_isPlayerHitMe )
			{
				// 判断是否有伤害
				if( pSeeDamage->results[i].xResult.stTagHpNum + pSeeDamage->results[i].xResult.nBackAttack > 0 )
				{
					thePlayerRole.m_isPlayerHitMe = true;
					thePlayerRole.m_dwPlayerHitMeAlphaStartTime = HQ_TimeGetTime();
				}
			}
		}
	}
	unguard;
}

void CPlayerMgr::OnMsgBuildStatus( Msg* pMsg )
{

	guardfunc;
	unguard;
}

void CPlayerMgr::OnMsgBuildDestroyed( Msg *pMsg )
{
	guardfunc;
	unguard;
}

void CPlayerMgr::OnMsgBuildSelfDestroyed( Msg *pMsg )
{
	guardfunc;
	unguard;
}

void CPlayerMgr::OnMsgBuildFailed( Msg *pMsg )
{
	guardfunc;
	unguard;
}

void	CPlayerMgr::OnMsgInquireInvitee(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgInquireInvitee);
	MsgInquireInvitee * pMsgInquireInvitee = (MsgInquireInvitee *)pMsg;

	// 判断是否拒绝入队邀请
	bool bInFight = false;
	if( theHeroGame.GetPlayerMgr()->GetMe() )
		bInFight = theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting);
	bool bRefuseInFight = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseAddTeamInFight );
	bool bRefuse = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseAddTeam );
	if( (bInFight && bRefuseInFight) || (!bInFight && bRefuse) )
	{
		InquireInvitee(false, pMsg);
		return;
	}

	CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( pMsgInquireInvitee->chProfession );
	if (pProInfo == NULL)
	{
		return;
	}

	char szContent[MAX_PATH] = {0};
	switch( pMsgInquireInvitee->AssignMode )
	{
	case AssignMode_FreeMode:
		if( pMsgInquireInvitee->IsCorps )
		{
			_snprintf( szContent, sizeof(szContent)-1, theXmlString.GetString(eClinet_CorpsAssignMode0), 
				pMsgInquireInvitee->szReqName,pProInfo->m_strProShow.c_str(),pMsgInquireInvitee->stLevel);
		}
		else
		{
			if (thePlayerRole.IsTeamHeader())
			{
				_snprintf( szContent, sizeof(szContent)-1, theXmlString.GetString(eText_AskJoinTeam),
					pMsgInquireInvitee->szReqName,pProInfo->m_strProShow.c_str(),pMsgInquireInvitee->stLevel );
			}
			else
			{
				_snprintf( szContent, sizeof(szContent)-1, theXmlString.GetString(eTextPlayer_GroupAssignMode0),
					pMsgInquireInvitee->szReqName,pProInfo->m_strProShow.c_str(),pMsgInquireInvitee->stLevel );
			}
		}

		break;
	case AssignMode_Team:
		if( pMsgInquireInvitee->IsCorps )
		{
			_snprintf( szContent, sizeof(szContent)-1, theXmlString.GetString(eClinet_CorpsAssignMode1), 
				pMsgInquireInvitee->szReqName,pProInfo->m_strProShow.c_str(),pMsgInquireInvitee->stLevel );
		}
		else
		{
			_snprintf( szContent, sizeof(szContent)-1, theXmlString.GetString(eTextPlayer_GroupAssignMode1), 
				pMsgInquireInvitee->szReqName,pProInfo->m_strProShow.c_str(),pMsgInquireInvitee->stLevel );
		}
		break;
	case AssignMode_Random:
		if( pMsgInquireInvitee->IsCorps )
		{
			_snprintf( szContent, sizeof(szContent)-1, theXmlString.GetString(eClinet_CorpsAssignMode2), 
				pMsgInquireInvitee->szReqName,pProInfo->m_strProShow.c_str(),pMsgInquireInvitee->stLevel );
		}
		else
		{
			_snprintf( szContent, sizeof(szContent)-1, theXmlString.GetString(eTextPlayer_GroupAssignMode2), 
				pMsgInquireInvitee->szReqName,pProInfo->m_strProShow.c_str(),pMsgInquireInvitee->stLevel );
		}
		break;
	case AssignMode_Assign:
		if( pMsgInquireInvitee->IsCorps )
		{
			_snprintf( szContent, sizeof(szContent)-1, theXmlString.GetString(eClinet_CorpsAssignMode3), 
				pMsgInquireInvitee->szReqName,pProInfo->m_strProShow.c_str(),pMsgInquireInvitee->stLevel );
		}
		else
		{
			_snprintf( szContent, sizeof(szContent)-1, theXmlString.GetString(eTextPlayer_GroupAssignMode3), 
				pMsgInquireInvitee->szReqName,pProInfo->m_strProShow.c_str(),pMsgInquireInvitee->stLevel );
		}
		break;
	}

	//zhuxincong 8.25 自动接受组队邀请 挂机，判断是否在挂机，是否勾选。
	if (s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight() && s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsTeamFlag(Team_AcceptInvite) )
	{
		InquireInvitee(true,pMsg);
	}
	else
	{
		s_CUI_ID_FRAME_MessageBox.Show( szContent, "",CUI_ID_FRAME_MessageBox::eTypeYesNo, false,
			InquireInvitee, pMsg, pMsg->GetLength() );
	}

	PlaySoundConfig( SoundConfig::EST_RequestTeam );
	unguard;
}

void CPlayerMgr::OnMsgUpdateCharacterBodyStatus(Msg* pMsg)
{ // 设置npc身上的战斗状态
	guardfunc
	
	MsgBuffsUpdate* pMessageUpdateBodyStatus = (MsgBuffsUpdate*)pMsg;

    // 找到对象
	CPlayer* pPlayer = FindByID( pMessageUpdateBodyStatus->header.stID );
	if ( NULL != pPlayer )
	{
        // 得到buff更新前的隐身状态
		bool bHide = pPlayer->m_cFightStatus.IsHide(); 

        // 更新状态
		pPlayer->OnBuffsUpdate( pMessageUpdateBodyStatus );

        // 判断是否有改变
// 		if ( bHide != pPlayer->m_cFightStatus.IsHide())
//         { s_CUI_ID_FRAME_TRACK.RefreshPlayerList(); }
	}

    // 更新UI
	thePlayerRole.UpdateUI();

	unguard
}

void CPlayerMgr::OnMsgClearBodyStatus(Msg* pMsg)
{ // 清除npc身上的战斗状态
	guardfunc
	
	MsgBuffsChanged* pMsgBuffsChanged = (MsgBuffsChanged*)pMsg;

	CPlayer* pPlayer = FindByID( pMsgBuffsChanged->header.stID );
	if ( NULL == pPlayer)
	{
		OutputDebugString( "找不到要解除状态的Player" );
        return;
    }

    pPlayer->OnBuffsChanged( pMsgBuffsChanged );
	thePlayerRole.RefreshQuestDone();
    unguard;
}
//---
//	服务器发过来转身的消息
//---
void	CPlayerMgr::OnMsgChangeDir(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgChangeDir);
	MsgChangeDir  *pChangeDirMsg = (MsgChangeDir  *)pMsg;
	//
	CPlayer* pPlayer = FindByID(pChangeDirMsg->stNpcID);
	//
	if (NULL != pPlayer)
	{
		pPlayer->SetDir(pChangeDirMsg->fChangeDir);
	}
	unguard;
}

//void CPlayerMgr::OnMsgGuildQueryJoin( Msg* pMsg )
//{
//	guardfunc;
//	unguard;
//}

//家族改名的notice
void CPlayerMgr::OnMsgFamilyNameChangeNotice(Msg* pMsg_)
{
	guardfunc;
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgGuildFamilyChangeAck);
	MsgGuildFamilyChangeAck* pMsg = (MsgGuildFamilyChangeAck*)pMsg_;
	
	char szText[256] = {0};
	//显示提示信息
	switch (pMsg->uchResult)
	{
	case MsgGuildFamilyChangeAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ChangeSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildFamilyChangeAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_HaveNoRightChange));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildFamilyChangeAck::ECD_SaveFamily:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_HaveSameFamily));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildFamilyChangeAck::ECD_EmptyFamily:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_CanNotDeleteOrChangeEmptyFamily));
			ShowGuildInfo(szText);
		}

		break;
	default:
		break;
	}
	
	thePlayerRole.UpdateUI();
	unguard;
}

// 发送募捐请求给客户端
void CPlayerMgr::OnMsgGuildDonate(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgGuildDonateReq);
	MsgGuildDonateReq* pMsg = (MsgGuildDonateReq*)pMsg_;	
	s_CUI_ID_FRAME_InfoTips.AddGuildDonateTip();
}

// 通知客户端帮派任务发布状态
void CPlayerMgr::OnMsgGuildDutyStatus(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgGuildQuestReleaseStatus);
	MsgGuildQuestReleaseStatus* pMsg = (MsgGuildQuestReleaseStatus*)pMsg_;
	const GuildConfig::ReleaseSetting refReleaseSetting = theGuildConfig.GetReleaseSetting();
	const GuildConfig::ReleaseSetting::QuestSetting* pQuestSetting = refReleaseSetting.GetQuestSetting(pMsg->nQuestType);
	if(!pQuestSetting)
		return;

	SpecialActivity activity;
	activity.bVisable = true;
	activity.strName = pQuestSetting->GetName();

	ControlList::S_List	stItem;
	stItem.m_nHiberarchy = 0;
	stItem.m_bCollapse = false;
	stItem.SetData( activity.strName.c_str(), 0, 0, Color_Config.getColor( CC_TASK_NAME ) );
	activity.itemVec.push_back( stItem );
	stItem.clear();

	TimeEx time(pMsg->n64RelasetTime);
	int beginHour = time.GetHour();
	int beginMinute = time.GetMinute();
	int endHour = ( beginHour + ( beginMinute + pQuestSetting->GetKeepTime()) / 60 ) % 24;
	int endMinute = (beginMinute + pQuestSetting->GetKeepTime()) % 60;
	char szBuf[ eMAX_TEMP_BUFF ];
	MeSprintf_s( szBuf, eMAX_TEMP_BUFF - 1, "%s %02d:%02d - %02d:%02d", theXmlString.GetString( eText_Time ), 
		beginHour, beginMinute, endHour, endMinute );

	stItem.m_nHiberarchy = 1;
	stItem.SetData( szBuf );
	activity.itemVec.push_back( stItem );
	if( !s_CUI_ID_FRAME_ActivityTrack.AddSpecialActivity( &activity ) )
		return;
}

//修改家族名
void CPlayerMgr::OnMsgFamilyNameChange(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgTellGuildFamilyChange);
	MsgTellGuildFamilyChange* pMsg = (MsgTellGuildFamilyChange*)pMsg_;

	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if (!pGuild)
	{
		return;
	}

	pGuild->SetFamilyName(pMsg->uchFamilyID, pMsg->szName);
	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
}

//帮成员信息改变
void CPlayerMgr::OnMsgUpdateMemberData(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}
    
	CHECK_MSGLEN(pMsg_, MsgMemberDataUpdate );
	MsgMemberDataUpdate * pMsg = (MsgMemberDataUpdate *)pMsg_;

	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if (!pGuild)
	{
		return;
	}
	
	GuildMember* pGuildMember = pGuild->FindByDBId(pMsg->nPlayerID);
	if (!pGuildMember)
	{
		return;
	}
//============================================================================
	std::string szBull = "";
	szBull = theXmlString.GetString( eChatType_Gang );
	szBull += " ";//加个空格好看点 -,-

	char buff[256] = {0};
	
	
	switch ( pMsg->nUpdateValue )
	{
	case GuildDefine::Position_Member: //家族成员
		sprintf(buff,theXmlString.GetString( eTextGuild_GruntedRight_Set ),pGuildMember->GetName(),theXmlString.GetString( eTextGang_Member ));
		break;
	case GuildDefine::Position_FamilyMaster://家族长 这个貌似没用
		sprintf(buff,theXmlString.GetString( eTextGuild_GruntedRight_Set ),pGuildMember->GetName(),theXmlString.GetString( eTextGang_ViceMaster ));
		break;
	case GuildDefine::Position_ViceMaster: //副帮主
		sprintf(buff,theXmlString.GetString( eTextGuild_GruntedRight_Set ),pGuildMember->GetName(),theXmlString.GetString( eTextGang_ViceMaster ));
		break;
	case GuildDefine::Position_Master: //帮主
		sprintf(buff,theXmlString.GetString( eTextGuild_GruntedRight_Set ),pGuildMember->GetName(),theXmlString.GetString( eTextGang_Master ));
		break;
	default:
		break;
	}
	
	szBull += buff;		
	//==========================================================================
	switch (pMsg->uchUpdateType)
	{
	case GuildDefine::UpdateMemberOnLine:
		pGuildMember->SetOnLine(pMsg->nUpdateValue);
		break;
	case GuildDefine::UpdateMemberLevel:
		pGuildMember->SetLevel(pMsg->nUpdateValue);
		break;
	case GuildDefine::UpdateMemberPosition:  //公会人员只为变动变动
		{	
			//lyh++
		s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_GUILD)
			, MsgChat::CHAT_TYPE_GUILD );

		pGuildMember->SetPosition(pMsg->nUpdateValue);
		}
		break;
	case GuildDefine::UpdateMemberFamily:
		pGuildMember->SetFamilyID(pMsg->nUpdateValue);
		break;
	case GuildDefine::UpdateMemberActivity:
		pGuildMember->SetActivity(pMsg->nUpdateValue);
		break;
	case GuildDefine::UpdateMemberOffer:
		pGuildMember->SetOffer(pMsg->nUpdateValue);
		break;
	case GuildDefine::UpdateMemberProfession:
		pGuildMember->SetProfession(pMsg->nUpdateValue);
		break;
	case GuildDefine::UpdateMemberCampBattleValue:
		{
			pGuildMember->SetCampBattleValue(pMsg->nUpdateValue);
			s_CUI_ID_FRAME_CampBattle.OnUpdateMemberInfo();
		}
		break;
	}

	if (g_nCharacterDBID == pMsg->nPlayerID)
	{
		switch (pMsg->uchUpdateType)
		{
		case GuildDefine::UpdateMemberPosition:
			theHeroGame.GetPlayerMgr()->GetMe()->SetGangPosition(pMsg->nUpdateValue);
			break;
		case GuildDefine::UpdateMemberOffer:
			{

				//lyh++ 军团贡献度提示
			
				int _Value = pMsg->nUpdateValue - theHeroGame.GetPlayerMgr()->GetMe()->GetGuildOffer();
				char buff[256] = {0};
				if(_Value != 0)
				{
					if(_Value>0)
						sprintf(buff,theXmlString.GetString(eText_YouGetGuildOffer),_Value);
					else if(_Value < 0)
					{
						_Value = abs(_Value);
						sprintf(buff,theXmlString.GetString(eText_YouLoseGuildOffer),_Value);
					}
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, buff );
				}
				

				theHeroGame.GetPlayerMgr()->GetMe()->SetGuildOffer(pMsg->nUpdateValue);
				s_CUI_ID_FRAME_SHOP.UpdataCurrentMoney();
			
				
			}
			break;
		case GuildDefine::UpdateMemberProfession:
			theHeroGame.GetPlayerMgr()->GetMe()->SetProfession(pMsg->nUpdateValue);
			break;
		default:
			break;
		}
	}
	
	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
}

void CPlayerMgr::ShowGuildInfo(const char* szText)
{
	if (!szText)
	{
		return;
	}

	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
	//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_GuildInfo, szText );
}

//回应申请加入帮派
void CPlayerMgr::OnMsgApplyJoinGuild(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgRequestJoinGuildAck );
	MsgRequestJoinGuildAck* pMsg = (MsgRequestJoinGuildAck*)pMsg_;
	
	if (pMsg->nPlayerID != g_nCharacterDBID)
	{
		return;
	}

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (!pMe)
	{
		return;
	}

	char szContent[256] = {0};
	if (pMsg->bAgreeJoin)
	{
		MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eInviteAddFriend), pMe->GetName());
		ShowGuildInfo(szContent);
	}
	else
	{
		MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eInviteAddFriend), pMe->GetName());
		ShowGuildInfo(szContent);
	}

}

//帮会信息改变
void CPlayerMgr::OnMsgUpDateGuildData(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgGuildDataUpdate );
	MsgGuildDataUpdate * pMsg = (MsgGuildDataUpdate *)pMsg_;

	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if (!pGuild)
	{
		return;
	}

	int nLastGuildLevel = pGuild->GetGuildLevel();
	int nLastGuildMoney = pGuild->GetGuildMoney();
	int nLastGuildExp = pGuild->GetGuildExp();

	char szText[256] = {0};
	switch (pMsg->uchUpdateType)
	{
	case GuildDefine::UpdateGuildLevel:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_IncreaseGuildLevel), pMsg->nUpdateValue);
			pGuild->SetGuildLevel(pMsg->nUpdateValue);
		}
		break;
	case GuildDefine::UpdateGuildMoney:
		{
			if(pMsg->nUpdateValue - nLastGuildMoney != 0)
			{
				if (pMsg->nUpdateValue > nLastGuildMoney)
				{
					MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_IncreaseGuildMoney), pMsg->nUpdateValue - nLastGuildMoney);
				}
				else
				{
					MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_DecreaseGuildMoney), nLastGuildMoney - pMsg->nUpdateValue);
				}
				pGuild->SetGuildMoney(pMsg->nUpdateValue);
			}
		}
		break;
	case GuildDefine::UpdateGuildExp:
		{
			if(pMsg->nUpdateValue - nLastGuildExp !=0)
			{
				if (pMsg->nUpdateValue > nLastGuildExp)
				{
					MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_IncreaseGuildExp), pMsg->nUpdateValue - nLastGuildExp);
				}
				else
				{
					MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_DecreaseGuildExp), nLastGuildExp - pMsg->nUpdateValue);
				}
				pGuild->SetGuildExp(pMsg->nUpdateValue);
			}
		}
		break;
	case GuildDefine::UpdateGuildMission:
		pGuild->SetGuildMission(pMsg->nUpdateValue);
		break;
	case GuildDefine::UpdateGuildMaster:
		pGuild->SetGuildMasterID(pMsg->nUpdateValue);
		break;
	case GuildDefine::UpdateGuildShopLevel:
		pGuild->SetGuildShopLevel(pMsg->nUpdateValue);
		break;
	case GuildDefine::UpdateGuildVar:
		break;
	case GuildDefine::UpdateGuildDonate:
		break;
	case GuildDefine::UpdateGuildDisbandTime:
		break;
	case GuildDefine::UpdateGuildSalary:
		break;
	default:
		break;
	}

	ShowGuildInfo(szText);
	s_CUI_ID_FRAME_SHOP.RefreshGuildShop();
	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
}


//通知帮会成员，有人加入
void CPlayerMgr::OnMsgAddGuildMember(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgTellJoinGuildToGuild );
	MsgTellJoinGuildToGuild * pMsg = (MsgTellJoinGuildToGuild *)pMsg_;

	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if (!pGuild)
	{
		return;
	}

	if (pGuild->AddMember(&(pMsg->xMember)))
	{
		//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
		s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
	}
	char str[128] = {0};
	MeSprintf_s(str,sizeof(str),theXmlString.GetString(eText_Guild_SomeJoinSomeGuild), pMsg->xMember.GetName(),pGuild->GetGuildName());

	//lyh++ 添加新公会成员 ++
	std::string szBull = "";
	szBull = theXmlString.GetString( eChatType_Gang );
	szBull += " ";//加个空格好看点 -,-
	szBull +=str;
	s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_GUILD)
		, MsgChat::CHAT_TYPE_GUILD );

	ShowGuildInfo(str);
}

// 通知附近玩家某人离开帮派了
void CPlayerMgr::OnMsgSomeOneLeaveGuild(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgTellLeaveGuildToView);
	MsgTellLeaveGuildToView* pMsg = (MsgTellLeaveGuildToView*)pMsg_;

	int nPlayerId = pMsg->header.stID;
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(nPlayerId);
	if (!pPlayer)
	{
		return;
	}

	pPlayer->SetGuildId(GuildDefine::InitID);

	//char szText[256] = {0};
	//MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_SomeLeaveSomeGuild), pPlayer->GetName());

	//ShowGuildInfo(szText);
}

// 通知附近玩家某人加入帮派了
void CPlayerMgr::OnMsgSomeOneJoinGuild(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgTellJoinGuildToView);
	MsgTellJoinGuildToView* pMsg = (MsgTellJoinGuildToView*)pMsg_;

	int nPlayerId = pMsg->header.stID;
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(nPlayerId);
	if (!pPlayer)
	{
		return;
	}

	const CGuildInfo* pGuildInfo = thePlayerRole.GetGuildById(pMsg->nGuildID);
	if (!pGuildInfo)
	{
		return;
	}

	pPlayer->SetGuildId(pGuildInfo->GetID());
	pPlayer->SetGuildName(pGuildInfo->GetName());
	pPlayer->SetGangPosition( pMsg->nGuildPosition );

	//char szText[256] = "0";
	//MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_SomeJoinSomeGuild), pPlayer->GetName(), pGuildInfo->GetName());

	//ShowGuildInfo(szText);
}

//通知帮会成员，有人离开
void CPlayerMgr::OnMsgDelGuildMember(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgTellLeaveGuildToGuild );
	MsgTellLeaveGuildToGuild * pMsg = (MsgTellLeaveGuildToGuild *)pMsg_;

	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if (!pGuild)
	{
		return;
	}

	GuildMember *member = pGuild->FindByDBId(pMsg->nPlayerID);
	if (member != NULL)
	{
		// 某玩家离开公会通知, 策划要求在中间和右下都要提示
		char szInfo[MAX_PATH] = {0};
		MeSprintf( szInfo, MAX_PATH - 1, theXmlString.GetString(eTextGuild_Leave_Member), member->GetName());
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Others_Success, szInfo );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, szInfo );

		//lyh++ 删除公会成员 ++
		std::string szBull = "";
		szBull = theXmlString.GetString( eChatType_Gang );
		szBull += " ";//加个空格好看点 -,-
		szBull +=szInfo;
		s_CUI_ChatInfoBox.AddInfo( szBull.c_str(), Color_Config.getColor(CC_CHAT_GUILD)
			, MsgChat::CHAT_TYPE_GUILD );


		if (pGuild->DelMember(pMsg->nPlayerID))
			s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
			//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	}
}

void CPlayerMgr::MeLeaveGuild()
{
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if (!pGuild)
	{
		return;
	}

	pGuild->Clear();

	if (m_pMe)
	{
		m_pMe->SetGuildName("");
		m_pMe->SetGuildId(GuildDefine::InitID);
	}

	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
}

//Me离开帮会
void CPlayerMgr::OnMsgGuildMemberLeave( Msg* pMsg_ )
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgLeaveGuildAck);
	MsgLeaveGuildAck* pMsg = (MsgLeaveGuildAck*)pMsg_;
	char szText[256] = {0};

	switch (pMsg->uchResult)
	{
	case MsgLeaveGuildAck::ECD_Success:
		{
			MeLeaveGuild();
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_LevelGuild_Succeed));
		}
		break;
	case MsgLeaveGuildAck::ECD_NotHaveGuild:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_LevelGuild_NotHaveGuild));
		}
		break;
	case MsgLeaveGuildAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_LevelGuild_NotHaveRight));
		}
		break;
	}

	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
	ShowGuildInfo(szText);
}

//客户端接收所有帮派列表
void CPlayerMgr::OnMsgReciveGuildList(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellGuildList);
	MsgTellGuildList* pMsg = (MsgTellGuildList*)pMsg_;

	if (pMsg->ustCount == 0)
	{
		return;
	}

	thePlayerRole.StoreAllGuildInfo(pMsg->ustCount, pMsg->xList);
}

//有新帮派创建
void CPlayerMgr::OnMsgAddNewGuild(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCreateGuild);
	MsgTellCreateGuild* pMsg = (MsgTellCreateGuild*)pMsg_;
	CGuildInfo newGuild;
	newGuild.SetID(pMsg->nGuildID);
	newGuild.SetCountry(pMsg->uchCountry);
	newGuild.SetLevel(1);
	newGuild.SetName(pMsg->szName);
	newGuild.SetMasterName(pMsg->szPlayer);
	newGuild.SetMemberNum(1); // lyh++ 两句，设置创始人的名字 和 刚创建的军团人数为1

	thePlayerRole.AddNewGuild(newGuild);

	s_CUI_ID_FRAME_GuildApply.SetNeedRefresh(true);
	s_CUI_ID_FRAME_AddGuildGeneralBattle.UpdateAllGuild();
	
	if (pMsg->uchCountry == thePlayerRole.GetCountry())
	{
		char szText[256] = {0};
		MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_GuildCreateSystemMessage), pMsg->szPlayer, pMsg->szName);
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Bull_System, szText);
	}
}

//弹劾结果
void CPlayerMgr::OnMsgGuildDelateResult(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgGuildDelateResult);
	MsgGuildDelateResult* pMsg = (MsgGuildDelateResult*)pMsg_;

	if (!thePlayerRole.GetGangMgr())
	{
		return;
	}

	GuildMember* pGuildMember = thePlayerRole.GetGangMgr()->FindByDBId(pMsg->nPlayerID);
	if (!pGuildMember)
	{
		return;
	}
	
	char szContent[256] = {0};
	if (pMsg->bDelateSuccess)
	{
		MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ImpeachSuccess), pGuildMember->GetName(), pGuildMember->GetName());	
	}
	else
	{
		MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ImpeachFailed), pGuildMember->GetName());	
	}
	
	ShowGuildInfo(szContent);
}

// 回应申请加入帮派notice
void CPlayerMgr::OnMsgJoinGuildNotice( Msg* pMsg_ )
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgJoinGuildAck);
	MsgJoinGuildAck* pMsg = (MsgJoinGuildAck*)pMsg_;
	
	char szText[256] = {0};
	switch (pMsg->uchResult)
	{
	case MsgJoinGuildAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_JoinGuildSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgJoinGuildAck::ECD_CreateSuccess:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_CreateGuildSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgJoinGuildAck::ECD_AlreadyHaveGuild:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_AlreadyInGuild));
			ShowGuildInfo(szText);
		}
		break;
	case MsgJoinGuildAck::ECD_LevelLess:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_LessThanApplyLevel));
			ShowGuildInfo(szText);
		}
		break;
	case MsgJoinGuildAck::ECD_NotSaveCountry:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NotTheSameCountry));
			ShowGuildInfo(szText);
		}
		break;
	case MsgJoinGuildAck::ECD_TimeLimit:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_MustWaitCoolTime));
			ShowGuildInfo(szText);
		}
		break;
	case MsgJoinGuildAck::ECD_GuildNotExist:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_GuildIsNotExist));
			ShowGuildInfo(szText);
		}
		break;
	case MsgJoinGuildAck::ECD_MemberFull:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_TheDestGuildMemberFull));
			ShowGuildInfo(szText);
		}
		break;
	case MsgJoinGuildAck::ECD_NotAgree:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_RefuseApply));
			ShowGuildInfo(szText);
		}
		break;
	case MsgJoinGuildAck::ECD_NotOnLine:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_TheAdminIsOffline));
			ShowGuildInfo(szText);
		}
		break;
	case MsgJoinGuildAck::ECD_IsCreSQ:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_GuildSQError1));
			ShowGuildInfo(szText);
		}
		break;
	}
}

// 提示帮主帮会将在某日期解散
void CPlayerMgr::OnMsgGuildDiabandTime(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgTellGuildDisbanTime);
	MsgTellGuildDisbanTime* pMsg = (MsgTellGuildDisbanTime*)pMsg_;
	
	if (!theHeroGame.GetPlayerMgr()->GetMe() || theHeroGame.GetPlayerMgr()->GetMe()->GetGangPosition() != GuildDefine::Position_Master)
	{
		return;
	}

	char szTime[128] = {0};
	TimeEx disbandTime(pMsg->n64DisbandTime);
	MeSprintf_s(szTime, sizeof(szTime)/sizeof(char) - 1, "%d-%d-%d %d时%d分", disbandTime.GetYear(), disbandTime.GetMonth(), disbandTime.GetDay(), disbandTime.GetHour(), disbandTime.GetMinute());

	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_DisbandTime), szTime);
	ShowGuildInfo(szText);
	return;	
}

//回馈客户端发布任务notice
void CPlayerMgr::OnMsgGuildReleaseNotice(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgGuildReleaseAck);
	MsgGuildReleaseAck* pMsg = (MsgGuildReleaseAck*)pMsg_;

	char szText[256] = {0};
	switch (pMsg->uchResult)
	{
	case MsgGuildReleaseAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ReleaseSuccess));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildReleaseAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ReleaseNoRight));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildReleaseAck::ECD_GuildLevelLess:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ReleaseLevelNoEnough));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildReleaseAck::ECD_ErrorTime:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ReleaseErrorTime));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildReleaseAck::ECD_AlreadyRelease:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ReleaseAlreadyRelease));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildReleaseAck::ECD_NotEnoughMoney:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ReleaseNotEnoughMoney));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildReleaseAck::ECD_QuestError:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ReleaseQuestError));
			ShowGuildInfo(szText);
		}
		break;
	default:
		break;
	}

}

// 回应帮贡建设
void CPlayerMgr::OnMsgGuildOfferbuildNotice(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgGuildOfferBuildAck);
	MsgGuildOfferBuildAck* pMsg = (MsgGuildOfferBuildAck*)pMsg_;

	char szText[256] = {0};
	switch (pMsg->uchResult)
	{
	case MsgGuildOfferBuildAck::ECD_NotEnoughOffer:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_OfferNotEnoughOffer));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildOfferBuildAck::ECD_MaxGuildExp:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_OfferMaxGuildExp));
			ShowGuildInfo(szText);
		}
		break;
	default:
		break;
	}

}

// 申请弹劾回馈notice
void CPlayerMgr::OnMsgGuildTanHeNotice( Msg* pMsg_ )
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgGuildDelateRequestAck);
	MsgGuildDelateRequestAck* pMsg = (MsgGuildDelateRequestAck*)pMsg_;

	char szText[256] = {0};
	switch (pMsg->uchResult)
	{
	case MsgGuildDelateRequestAck::ECD_ErrorTime:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_UnReachTanHeTime));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildDelateRequestAck::ECD_AlreadyDelate:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_AlreadyBeTanHe));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildDelateRequestAck::ECD_LevelLess:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_LevelLessThanNeed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildDelateRequestAck::ECD_MaxGuildExp:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_MaxExp));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildDelateRequestAck::ECD_NotEnoughMoney:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NoEnoughMoneyTanHe));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildDelateRequestAck::ECD_OnLineLess:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_OnLineLess));
			ShowGuildInfo(szText);
		}
		break;
	default:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ImpeachSend));
			ShowGuildInfo(szText);
		}
		break;
	}
}

// 回馈升级帮会消息
void CPlayerMgr::OnMsgGuildLevelUpNotice( Msg* pMsg_ )
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgGuildLevelUpAck );
	MsgGuildLevelUpAck * pMsg = (MsgGuildLevelUpAck *)pMsg_;

	char szText[256] = {0};
	switch (pMsg->uchResult)
	{
	case MsgGuildLevelUpAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_GuildLevelUpSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildLevelUpAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NoRightLevelUp));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildLevelUpAck::ECD_NotEnoughMoney:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NotEnoughGuildMoney));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildLevelUpAck::ECD_NotEnoughExp:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NotEnoughGuildExp));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildLevelUpAck::ECD_MaxLevel:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_IsMaxGuildLevel));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildLevelUpAck::ECD_NotEnoughMisson:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NotEnoughMission));
			ShowGuildInfo(szText);
		}
		break;
	default:
		break;
	}
}

// 回馈帮派商店激活消息
void CPlayerMgr::OnMsgGuildShopLevelUpNotice( Msg* pMsg_ )
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgGuildShopLevelUpAck);
	MsgGuildShopLevelUpAck* pMsg = (MsgGuildShopLevelUpAck*)pMsg_;

	char szText[256] = {0};
	switch (pMsg->uchResult)
	{
	case MsgGuildShopLevelUpAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ActiveSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildShopLevelUpAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NoRightLevelUp));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildShopLevelUpAck::ECD_GuildLevelLess:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_GuildLevelNotEnough));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildShopLevelUpAck::ECD_NotEnoughExp:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NotEnoughGuildExp));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildShopLevelUpAck::ECD_AlreadActive:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_AlreadyActived));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildShopLevelUpAck::ECD_ErrorLevel:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_FalseLevel));
			ShowGuildInfo(szText);
		}
		break;
	}
}

//帮会商店买东西的回馈
void CPlayerMgr::OnMsgGuildBuyItemNotice( Msg* pMsg_ )
{
	if (!pMsg_)
	{
		return;
	}

	char szText[256] = {0};
	CHECK_MSGLEN(pMsg_, MsgGuildBuyItemAck);
	MsgGuildBuyItemAck* pMsg = (MsgGuildBuyItemAck*)pMsg_;

	switch (pMsg->uchResult)
	{
	case MsgGuildBuyItemAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NoBuyRight));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildBuyItemAck::ECD_LevelNotActive:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_GuildShopNoActive));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildBuyItemAck::ECD_ErrorItem:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ItemNotExist));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildBuyItemAck::ECD_NotEnoughOffer:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NotEnoughOffer));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildBuyItemAck::ECD_ErrorLevel:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ErrorShopLevel));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildBuyItemAck::ECD_PackFull:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_NormalPackFull));
			ShowGuildInfo(szText);
		}
		break;
	}
}

// 通知客户端帮派解散了
void CPlayerMgr::OnMsgGuildDisband( Msg* pMsg_ )
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgTellDisbandGuild );
	MsgTellDisbandGuild * pMsg = (MsgTellDisbandGuild *)pMsg_;
	
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if (!pGuild)
	{
		return;
	}

	if (pGuild->GetGuildID() != pMsg->nGuildID)
	{
		return;
	}

	char szContent[256] = {0};
	MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_GuildDisband), pGuild->GetGuildName());
	ShowGuildInfo(szContent);
}

// 回应邀请进入帮派notice
void CPlayerMgr::OnMsgInviteGuildNotice( Msg* pMsg_ )
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgInviteGuildAck);
	MsgInviteGuildAck* pMsg = (MsgInviteGuildAck*)pMsg_;

	char szText[256] = {0};
	switch (pMsg->uchResult)
	{
	case MsgInviteGuildAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_InviteSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgInviteGuildAck::ECD_NotHaveGuild:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_MeHaveNoGuild));
			ShowGuildInfo(szText);
		}
		break;
	case MsgInviteGuildAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NoRightInvite));
			ShowGuildInfo(szText);
		}
		break;
	case MsgInviteGuildAck::ECD_NotSaveCountry:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_OtherCountry));
			ShowGuildInfo(szText);
		}
		break;
	case MsgInviteGuildAck::ECD_NotOnLine:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_PlayerOffline));
			ShowGuildInfo(szText);
		}
		break;
	case MsgInviteGuildAck::ECD_AlreadyHaveGuild:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_HeHaveGuild));
			ShowGuildInfo(szText);
		}
		break;
	case MsgInviteGuildAck::ECD_LevelLess:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_LevelLessThanTwenty));
			ShowGuildInfo(szText);
		}
		break;
	case MsgInviteGuildAck::ECD_MemberFull:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_MemberFull));
			ShowGuildInfo(szText);
		}
		break;
	case MsgInviteGuildAck::ECD_NotAgree:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_RefuseJoin));
			ShowGuildInfo(szText);
		}
		break;
	case MsgInviteGuildAck::ECD_Agree:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_AgreeJoin));
			ShowGuildInfo(szText);
		}
		break;
	case MsgInviteGuildAck::ECD_LeaveTimeLimit:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_TimeLimit));
			ShowGuildInfo(szText);
		}
		break;
	default:
		break;
	}
}

//转移帮众notice
void CPlayerMgr::OnMsgGuildMemberMoveNotice( Msg* pMsg_ )
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgGuildMemberFamilyChangeAck);
	MsgGuildMemberFamilyChangeAck* pMsg = (MsgGuildMemberFamilyChangeAck*)pMsg_;
	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
	char szText[256] = {0};
	switch (pMsg->uchResult)
	{
	case MsgGuildMemberFamilyChangeAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ChangeBangZhongSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildMemberFamilyChangeAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NoRightChange));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildMemberFamilyChangeAck::ECD_SaveFamily:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_NoNeedChange));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildMemberFamilyChangeAck::ECD_EmptyFamily:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ChangeEmptyFamilyFaild));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildMemberFamilyChangeAck::ECD_AlreadyHaveFamily:			
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_AlreadyHaveFamily));
			ShowGuildInfo(szText);
		}
		break;
// 	case MsgGuildFamilyChangeAck::ECD_Success:
// 		{
// 			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_GuildChangeNameSuccess));
// 			ShowGuildInfo(szText);
// 		}
// 		break;
	case MsgGuildFamilyChangeAck::ECD_IsFamilyMaster:
		{
			MeSprintf_s(szText,sizeof(szText),theXmlString.GetString(eText_Guild_MasterCanNotZC));
			ShowGuildInfo(szText);
		}
		break;
	default:
		break;
	}
}

void CPlayerMgr::OnMsgGuildMasterConvent(Msg* pMsg)// 帮主召集帮众 到某个地图
{
	if (!pMsg)
	{
		return;
	}

	s_CUI_ID_FRAME_InfoTips.AddGuildMasterConvene(pMsg);
}

const char* GetRelationName(unsigned short ekey)
{
	switch (ekey)
	{
	case RelationDefine::Marriage:
		return  theXmlString.GetString(eText_Ralation_Marriage);
	case RelationDefine::Teacher:
		return  theXmlString.GetString(eText_Ralation_Teacher);
	case RelationDefine::Student:
		return  theXmlString.GetString(eText_Ralation_Student);
	case RelationDefine::Brother:
		return  theXmlString.GetString(eText_Ralation_Brother);
	default:
		return "";
	}
}

// 通知客户端添加某种关系的剩余时间
void CPlayerMgr::OnMsgAddRelationCoolDownTime(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellAddRelationTimeLeft);
	MsgTellAddRelationTimeLeft* pMsg = (MsgTellAddRelationTimeLeft*)pMsg_;

	unsigned int nTimeSecond = pMsg->nTimeLeft;
	int hour = nTimeSecond / 3600;
	int minute = (nTimeSecond - hour * 3600) / 60;
	int second = nTimeSecond % 60;
	
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Ralation_AddRelationCoolTime), hour, minute, second, GetRelationName(pMsg->ustRelation));
	CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Teacher_Belongs, szText);
	CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_ShiTu_Belongs_Success, szText);
}

void ShowInfoInCenterOfWindow(const char* szText)
{
	if (!szText)
	{
		return;
	}

	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ShiTu_Belongs_Success, szText );
}

//徒弟升级，师傅威望增加
void CPlayerMgr::OnMsgStudentLevelUp(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgStudentLevelUp);
	MsgStudentLevelUp* pMsg = (MsgStudentLevelUp*)pMsg_;

	const char* szName = NULL;
	char szText[256] = {0};
	if (pMsg->bIsStudent)
	{
		szName = thePlayerRole.GetStudentNameById(pMsg->nStudentID);
		if (szName)
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_ShiTu_GetExpAndMasterValueByYourStudent), szName, pMsg->nRewardExp, pMsg->nRewardMasterValue);
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Teacher_Belongs, szText);
			ShowInfoInCenterOfWindow(szText);
		}
		return;
	}
	
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_ShiTu_GetExpAndMasterValueByYourGrandStudent), pMsg->nRewardExp, pMsg->nRewardMasterValue);
	CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Teacher_Belongs, szText);
	ShowInfoInCenterOfWindow(szText);
}

// 通知将所有成员本周活跃度设置到上周, 并清除本周的活跃度
void CPlayerMgr::OnMsgResetGuildMemberActive(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgGuildClearMemberActivity);
	//MsgGuildClearMemberActivity* pMsg = (MsgGuildClearMemberActivity*)pMsg_;
	
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if (!pGuild)
	{
		return;
	}
	
	pGuild->ResetMemberActive();
}

//void CPlayerMgr::OnMsgGuildMemberDismiss( Msg* pMsg_ )
//{
//	if (!pMsg_)
//	{
//		return;
//	}
//
//	CHECK_MSGLEN( pMsg_, MsgGuildResignPositionReq);
//	MsgGuildResignPositionReq* pMsg = (MsgGuildResignPositionReq*)pMsg;
//	CGangMgr* pGMM = thePlayerRole.GetGangMgr();
//	pGMM->Clear();
//
//	if(s_CUI_ID_FRAME_Gang.IsVisable())
//	{
//		s_CUI_ID_FRAME_Gang.SetVisable(FALSE);
//	}
//	//清除头顶公会名称
//	if( m_pMe )
//	{
//		m_pMe->SetGuildName("");
//		m_pMe->SetGuildId(GuildDefine::InitID);
//	}
//	thePlayerRole.UpdateUI();
//}

//void CPlayerMgr::OnMsgGuildGetAllMemberInfo( Msg* pMsg )
//{
//	guardfunc;
//	unguard;
//}
//void CPlayerMgr::OnMsgGuildAckJoin( Msg* pMsg )
//{
//
//	guardfunc;
//	unguard;
//}
//void CPlayerMgr::OnMsgGuildAckLeave( Msg* pMsg )
//{
//	guardfunc;
//	unguard;
//}
//void CPlayerMgr::OnMsgGuildMemberTellGuildId( Msg* pMsg )
//{
//	guardfunc;
//	unguard;
//}
// 功勋值
void CPlayerMgr::OnMsgTellExploit( Msg* pMsg )
{

	guardfunc;
	CHECK_MSGLEN( pMsg, MsgTellExploit);
	MsgTellExploit* pTell = (MsgTellExploit*)pMsg;
	CPlayer* pPlayer =GetMe();
	if( !pPlayer )
	{
		assert( false );
		return;
	}
	DWORD dwOldExploit = pPlayer->GetExploit();
	pPlayer->SetExploit( pTell->dwExploit );
	s_CUI_ID_FRAME_Experience.Refresh();

	unguard;
}

void CPlayerMgr::OnMsgExploitChange( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgExploitChange);
	MsgExploitChange* pChange = (MsgExploitChange*)pMsg;
	CPlayer* pPlayer = GetMe();
	if( !pPlayer )
	{
		assert( false );
		return;
	}
	pPlayer->SetExploit( pChange->dwCurrentExploit);
	if( thePlayerRole.m_pBaseInfo )
		thePlayerRole.m_pBaseInfo->liveinfo.exploit = pPlayer->GetExploit();

	D3DXVECTOR3 pos = pPlayer->GetPos();

	int xEffect,yEffect;
	World2Screen( pos,xEffect,yEffect );

	g_pFlyTextEffect->Create( CFlyTextEffect::eNumberBlue, xEffect,yEffect, pChange->dwCurrentExploit,pPlayer->GetID() );

	unguard;
}
void CPlayerMgr::OnMsgTellOfficialLevel( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgTellOfficialLevel);
	MsgTellOfficialLevel* pTell = (MsgTellOfficialLevel*)pMsg;
	CPlayer* pPlayer = FindByID( pTell->stCharId );
	if( !pPlayer )
	{
		assert( false );
		return;
	}
	pPlayer->SetOfficialLevel( pTell->byOfficialLevel );
	unguard;
}

////----
////站立 状态切换
////----
void 	CPlayerMgr::OnMsgSitStatusChange(Msg * pMsg)
{
	guardfunc;
	assert( false );
	unguard;
}

//----
//战斗状态切换
//----
void 	CPlayerMgr::OnMsgFightStatusChange(Msg * pMsg)
{
	guardfunc;
	assert( false );
	unguard;
}


// 接收到使用物品的消息
void CPlayerMgr::OnMsgRemoveItem(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgRemoveItem);
	s_CUI_ID_FRAME_PACK.RemoveItem( pMsg );
	unguard;
}
void CPlayerMgr::OnMsgRemoveItemByGuID(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgRemoveItemByGuID);
	s_CUI_ID_FRAME_PACK.RemoveItemByGuID( pMsg );
	unguard;
}
// 接收到请求查看物品
void CPlayerMgr::OnMsgGetShop(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckGetShop);
	MsgAckGetShop* pAckGetShop = (MsgAckGetShop*)pMsg;
	s_CUI_ID_FRAME_SHOP.Refresh(pAckGetShop);
	unguard;
}

void CPlayerMgr::OnMsgRetShopCenterItemCnt( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgRetShopCenterItemCnt);
	MsgRetShopCenterItemCnt *pItemCnt = (MsgRetShopCenterItemCnt*)pMsg;
	s_CUI_ID_FRAME_ShopCenter.SetItemCount(pItemCnt->ustItemId, pItemCnt->ustCount);
	s_CUI_ID_FRAME_ShopCenter.Refresh();
	unguard;
}


void CPlayerMgr::OnMsgAskGetShopCenter(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckGetShopCenter);
	MsgAckGetShopCenter *pShop = (MsgAckGetShopCenter*)pMsg;
	for (int i = 0; i < pShop->nCount; ++i)
	{
		s_CUI_ID_FRAME_ShopCenter.AddShopItem(pShop->info[i].id, pShop->info[i].count);
	}
	s_CUI_ID_FRAME_ShopCenter.Refresh();
	unguard;
}

// 未完成: 接收到买东东的消息
void CPlayerMgr::OnAckMsgBuyOrSellGoods(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckBuyOrSellGoods);
	MsgAckBuyOrSellGoods* pAckBuyOrSellGoods = (MsgAckBuyOrSellGoods*)pMsg;
	s_CUI_ID_FRAME_SHOP.EnableShopItem();
	if ( pAckBuyOrSellGoods->ustResult == MsgAckBuyOrSellGoods::error_sucess
        ||pAckBuyOrSellGoods->ustResult == MsgAckBuyOrSellGoods::error_centerbuysuccess)
	{
		bool bResult = s_CUI_ID_FRAME_PACK.BuyOrSellGoods( pAckBuyOrSellGoods );
		assert( bResult == true );
        if(pAckBuyOrSellGoods->ustResult == MsgAckBuyOrSellGoods::error_centerbuysuccess)
            s_CUI_ID_FRAME_ShopCenter.SetFindPath(pAckBuyOrSellGoods->ustItemId);
	}
	else
	{
		switch(pAckBuyOrSellGoods->ustResult)
		{
		case MsgAckBuyOrSellGoods::error_no_stock_item:
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eClient_ShopCenterNotStock) );
			break;
		default:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, theXmlString.GetString(eExchange_UnKnown) );
			break;
		}

	}
	unguard;
}

// 接受到战斗提示消息
void	CPlayerMgr::OnMsgUseSkillHintMessage( Msg* pMsg )
{
	guardfunc;

	if (!CanReceivePlayerMsg())
	{
		return;
	}
	CHECK_MSGLEN( pMsg, MsgUseSkillHintMessage);
	MsgUseSkillHintMessage* pHintMsg = (MsgUseSkillHintMessage*)pMsg;
	BOOL bInterruptIntonating = FALSE;
	if( m_pMe )
	{
		m_pMe->CheckAdvanceSkill(pHintMsg->nSkillID, pHintMsg->shSkillLevel);

		m_pMe->SetIntonating( FALSE );
	}
	if(pHintMsg->isAction
		&& (pHintMsg->nSkillID >= ItemDefine::StartID_Skill && pHintMsg->nSkillID <= ItemDefine::EndID_Skill) )
		g_ActionManager.Push_UseSkillOperation( pHintMsg->TargetID, pHintMsg->nSkillID, pHintMsg->shSkillLevel, g_dwLastFrameBeginTime );

	switch( pHintMsg->shHintId )
	{
	case MsgUseSkillHintMessage::eOutAttackRangeHint:
		{
			printf_s("不在攻击范围！\n");

			if( g_nRoleCommonAttackStatus == CAS_ATTACK_AGAIN_WHEN_FAILED )
			{
				//发消息通知服务器，攻击锁定的目标
				MsgAttackLockTarget	msg;

				if( GettheNetworkInput().SendMsg(&msg) == -1 )
				{

				}
			}
			else
			{
				bInterruptIntonating = TRUE;
				{
					if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_TooFar ) );
				}
			}
		}
		break;
	case MsgUseSkillHintMessage::eUnfaceToTarget:
		{
			if( g_nRoleCommonAttackStatus == CAS_ATTACK_AGAIN_WHEN_FAILED )
			{
				//发消息通知服务器，攻击锁定的目标
				MsgAttackLockTarget	msg;

				if( GettheNetworkInput().SendMsg(&msg) == -1 )
				{

				}
			}
			else
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotFaceToTarget ) );
				bInterruptIntonating = TRUE;
			}
		}
		break;
	case MsgUseSkillHintMessage::eNoEnoughHpToUseSkill:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotEnoughHP ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eNoEnoughMpToUseSkill:
		{
            std::string strTemp = GetMPTypeString( thePlayerRole.GetProfession() );
            strTemp = strTemp + theXmlString.GetString( eText_SkillFailed_NotEnoughMP );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, strTemp.c_str() );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eNoEnoughItemToUseSkill:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_LackOfSomeItem ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eNoEnoughWeaponToUseSkill:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NeedWeapon ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eCannotUsePassivitySkill:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eTextPlayer_PassiveNotUse ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eCannotUseSkillInCurStatus:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotUseSkillInCurStatus ) );
		}
		break;
	case MsgUseSkillHintMessage::eSkillIsInCoolDown:
		{
			if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())//lyh++ 自动挂机的时候不显示技能在冷却
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_WhenCoolDown ) );
			PlaySoundConfig( SoundConfig::EST_InCoolDown );
		}
		break;
	case MsgUseSkillHintMessage::eBannedPK:
		{
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eServerCannotFindSkill:
		{

		}
		break;
	case MsgUseSkillHintMessage::eSkillTargetNotExist:
		{
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eSkillTargetWrong:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eTargetNumIsZero:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NoTarget ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eCancelSkill:
		{
			OutputDebugString( "取消当前使用的技能\n" );
		}
		break;
	case MsgUseSkillHintMessage::eNoEnoughFpToUseSkill:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotEnoughExPower ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eCannotUseSkillWhenMounting:       // 骑马中不能使用技能
		{
			//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_WhenMounting ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eCannotUseSkillWhenPrivateShop:    // 开个人商店中不能使用技能
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_InPrivateShop ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eCannotUseSkillInSkillAvailable:   // 在SkillAvailable判定技能不能使用
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotUseSkillInCurStatus ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eCannotUseSkillWhenTaskIsnotEmpty: // Task不为空，所以不能使用技能
		{
			if( GetMe() )
			{
				GetMe()->ClearAdvanceSkillList();
			}
			OutputDebugString( "技能操作太频繁\n" );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eCannotUsePhysicsSkill:            // 当前状态不能使用物理技能
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_CannotUsePhysicsSkill ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eCannotUseMagicSkill:              // 当前状态不能使用魔法技能
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_CannotUseMagicSkill ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eMustInFightState:                 // 技能必须在战斗状态
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_UseOnlyInFighting ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eMustOutFightState:                // 技能必须不在战斗状态
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_CannotUseInFighting ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eHpLimitError:                     // 血量限制
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_HpLimit ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eNoInTargetBack:                   // 必须在目标背后才能施放此技能
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_MustAtBack ) );
			bInterruptIntonating = TRUE;
		}
	case MsgUseSkillHintMessage::eNotEnoughVigorToUseSkill:
		{
			if( pHintMsg->nSkillID == ItemDefine::eCSI_CaiYao )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_NotEnoughVigorToHerb ) );
			else if( pHintMsg->nSkillID == ItemDefine::eCSI_CaiKuang )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_NotEnoughVigorToMine ) );
            else if( pHintMsg->nSkillID == ItemDefine::eCSI_BuChong )
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_NotEnoughVigorToInsect ) );
			else
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_LootFailed_VigorNotEnough ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eTeamSkillCanNotUse:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_TeamSkillFailed_NotAvailable ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eTeamSkillInCoolDown:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_TeamSkillFailed_CoolDown ) );
			bInterruptIntonating = TRUE;
		}
		break;
	case MsgUseSkillHintMessage::eHintMax:
		{
			OutputDebugString( "服务端判定技能使用不成立\n" );
			bInterruptIntonating = TRUE;
		}
		break;
// 	case MsgUseSkillHintMessage::eSummonPetPlayerEffect:
// 		{
// 			CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(pHintMsg->TargetID);
// 			if(pPlayer)
// 			{
// 				ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pHintMsg->nSkillID, pHintMsg->shSkillLevel);
// 				if(pSkill)
// 				{
// 					const char *pEffectName = pSkill->GetTargetEffectName();
// 					if(pEffectName)
// 					    pPlayer->SetPetEffect(pEffectName);
// 				}
// 			}
// 		}
// 		break;
	case MsgUseSkillHintMessage::eHurtImmunity:
		{
			CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(pHintMsg->TargetID);
			if(pPlayer)
			{
				int nCount = pPlayer->m_cFightStatus.GetBufferStatusCount();
				for (int i = 0;i < nCount;++i)
				{
					SCharBuff* pCharBuff = pPlayer->m_cFightStatus.GetBuff( i );
					if( !pCharBuff)
						continue; 

					ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
					if ( !pStatus )
					 continue; 

					if(pStatus->hurtImmunity > 0)
					{
						if(!gCfg.m_strImmunity.empty())
						    PlayEffect((char*)gCfg.m_strImmunity.c_str(),pPlayer);
					}
				}
			}
		}
		break;
	}

	if( bInterruptIntonating && s_CUI_Progress.IsVisable() && !s_CUI_Progress.IsInterrupt() )
	{
		s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), 1, true, 1, true, true, theXmlString.GetString(eTextPlayer_Break), true, false, 0, FALSE  );

		// 吟唱中断，在手上的特效也要释放掉
		if( m_pMe )
		{
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
	}

	if( bInterruptIntonating && m_pMe )
	{
		if( !m_pMe->IsMoving() )
		{
			m_pMe->SwitchIdleAnim();
		}
		m_pMe->SetIntonating( FALSE );
	}
	pHintMsg = NULL;
	unguard;
}

// 接收玩家的跳跃信息
void	CPlayerMgr::OnMsgRecevingJump( Msg* pMsg )
{
	guardfunc;

	CHECK_MSGLEN( pMsg, MsgJump);
	MsgJump* pJump = (MsgJump*)pMsg; 
	CPlayer* pPlayer = FindByID( pJump->header.stID );

	if( pPlayer )
	{
		pPlayer->Jump();
	}

	pJump = NULL;
	pPlayer = NULL;
	unguard;
}

// 接收到玩家拔出武器的信息
void CPlayerMgr::OnMsgRecevingDrawWeapon( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgDrawWeapon);
	MsgDrawWeapon* pDraw = (MsgDrawWeapon*)pMsg;
	CPlayer* pPlayer = FindByID( pDraw->header.stID );

	if( pPlayer && pPlayer->IsPlayer() )
	{
		if( !pPlayer->HasFightFlag(eFighting) && !pPlayer->IsMounting() && !pPlayer->IsFightPose() )
		{
			pPlayer->SetFightPose(TRUE);
			pPlayer->SwitchScabbardAnim();
		}
		else if( pPlayer->IsMounting() )
		{
			if( pPlayer->IsHaveWeapon() && pPlayer->GetProfession() == EArmType_Assassin && !pPlayer->GetLiftFlagStatus() )
			{
				if( m_pMe && IsFlagModel(m_pMe->GetWeaponModelID()) )
				{
					pPlayer->SetLiftFlagStatus(1);
					pPlayer->SwitchLiftFlagAnim();
				}
			}
		}
	}
	pDraw = NULL;
	pPlayer = NULL;
	unguard;
}

// 接收到玩家收起武器的信息
void CPlayerMgr::OnMsgRecevingDrawInWeapon( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgDrawInWeapon);
	MsgDrawInWeapon* pDrawIn = (MsgDrawInWeapon*)pMsg;
	CPlayer* pPlayer = FindByID( pDrawIn->header.stID );

	if( pPlayer && pPlayer->IsPlayer() )
	{
		if( !pPlayer->HasFightFlag(eFighting) && pPlayer->IsFightPose() )
		{
			pPlayer->SetFightPose(FALSE);
			pPlayer->SwitchScabbardAnim();
		}

		if( pPlayer->IsMounting() )
		{
			if( pPlayer->IsHaveWeapon() && pPlayer->GetProfession() == EArmType_Assassin && pPlayer->GetLiftFlagStatus() )
			{
				if( m_pMe && IsFlagModel(m_pMe->GetWeaponModelID()) )
				{
					pPlayer->SetLiftFlagStatus(0);
					if( pPlayer->GetAnim() )
						pPlayer->GetAnim()->ForceCurrAnimLoopTime(-1,TRUE);
				}
			}
		}
	}

	pDrawIn = NULL;
	pPlayer = NULL;
	unguard;
}

void CPlayerMgr::OnMsgSeeAction( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgSeeAction);
	MsgSeeAction* sa = (MsgSeeAction*)pMsg;
	OnSeeAction( sa->header.stID, sa->stActionId );
	unguard;
}

void CPlayerMgr::OnMsgScriptShow( Msg* pMsg )
{
	guardfunc;
	unguard;
}

//---
//收到服务器发送回来的Ping消息
//---
void CPlayerMgr::OnMsgPing(Msg * pMsg)
{
	guardfunc;
	if (!CanReceivePlayerMsg())
	{
		return;
	}
	CHECK_MSGLEN( pMsg, MsgPingMsg);
	MsgPingMsg* pPingMsg = (MsgPingMsg *)pMsg;

	if( g_dwLastFrameBeginTime > pPingMsg->dwTime )
	{
		m_dwGamePing = g_dwLastFrameBeginTime - pPingMsg->dwTime;
		if( m_dwGamePing > g_dwLastFrameRealCostTime / 2 )
			m_dwGamePing -= g_dwLastFrameRealCostTime / 2;
	}
	else
		m_dwGamePing = HQ_TimeGetTime() - pPingMsg->dwTime;

	if( g_GameState == G_MAIN )
	{
		s_CUI_ID_FRAME_MiniMap.SetPing(m_dwGamePing);
	}
	unguard;
}

void CPlayerMgr::OnMsgTellMapNpcQuest( Msg* pMsg )
{
	guardfunc;
	return;
	unguard;
}
void CPlayerMgr::OnMsgTellCharVars( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgTellCharVar);
	MsgTellCharVar* pTell = (MsgTellCharVar*)pMsg;
	BOOL bRefreshAll = FALSE;
	for( int i = 0; i < pTell->varCount; i++ )
	{
		thePlayerRole.RefreshTalkStates( pTell->charVars[i].varId, pTell->charVars[i].varValue );

		short stValue = pTell->charVars[i].varValue;
		if( theQuestManager.IsQuestIdValid( pTell->charVars[i].varId ) )
			stValue = theQuestManager.GetQuestState( pTell->charVars[i].varValue );

		bool bRet = thePlayerRole.ChangeQuestState( pTell->charVars[i].varId, stValue );
		if (bRet)
		{
			bRefreshAll = TRUE;
		}
	}
	//thePlayerRole.UpdateActiveQuestState( TRUE, FALSE );
	if( g_bCanUpdateQuest )
	{
		if (bRefreshAll)
		{
			theHeroGame.GetPlayerMgr()->RefreshAllNpcQuest();
			GetRegionMap()->SetUpdateStableImage(true);
			s_CUI_ID_FRAME_Task.SetDirty( true );
		}
		thePlayerRole.RefreshQuestDone( );
		s_CUI_ID_FRAME_Task.Refresh( false);
	}

	if (s_CUI_ID_FRAME_EspecialTask.IsVisable() && 
		s_CUI_ID_FRAME_EspecialTask.GetCanRefresh())
	{
		const int nMaxListItem = 64;
		ControlList::S_List pstList[nMaxListItem];
		int questStates[nMaxListItem];
		int nQuestCount  = 0;
		RetriveRelationQuestToNpc(s_CUI_ID_FRAME_EspecialTask.GetNpcId(), nQuestCount, questStates, pstList);
		s_CUI_ID_FRAME_EspecialTask.Show(pstList, nQuestCount, s_CUI_ID_FRAME_EspecialTask.GetNpcId(), s_CUI_ID_FRAME_EspecialTask.GetTaskType());
	}
	if (s_CUI_ID_FRAME_EspecialTask2.IsVisable())
	{
		const int nMaxListItem = 64;
		ControlList::S_List pstList[nMaxListItem];
		int questStates[nMaxListItem];
		int nQuestCount  = 0;
		RetriveRelationQuestToNpc(s_CUI_ID_FRAME_EspecialTask2.GetNpcId(), nQuestCount, questStates, pstList);
		s_CUI_ID_FRAME_EspecialTask2.Show(pstList, nQuestCount, s_CUI_ID_FRAME_EspecialTask2.GetNpcId(), s_CUI_ID_FRAME_EspecialTask2.GetTaskType());
	}
 	for( int i = 0; i < pTell->varCount; i++ )
 		s_CUI_NpcTaskDialogBox.RefreshTask(pTell->charVars[i].varId);
	if (s_CUI_ID_FRAME_ActivityList.IsVisable())
	{
		s_CUI_ID_FRAME_ActivityList.Refresh(s_CUI_ID_FRAME_ActivityList.GetType());
	}

	if ( s_CUI_ID_FRAME_Hunting.IsVisable() )
	{
		bool bHas = false;
		for( int i = 0; i < pTell->varCount; i++ )
		{
			bHas = s_CUI_ID_FRAME_Hunting.HasVarId( pTell->charVars[i].varId );
			if ( bHas )
				break;
		}
		if ( bHas )
			s_CUI_ID_FRAME_Hunting.Refresh();
	}
	unguard;
}

void    CPlayerMgr::OnMsgReqYuanBaoCnt( Msg *pMsg )
{
	guardfunc;

	MsgReqYuanBaoCnt *pYuanBaoCnt = (MsgReqYuanBaoCnt*)pMsg;
	INT nCnt = pYuanBaoCnt->nYuanBaoCnt;
	unguard;
}

// 角色的跳跃信息
void	CPlayerMgr::SendJumpMsg()
{
	guardfunc;
	if( !m_pMe )
		return;
	MsgJump jump;
	jump.header.stID = m_pMe->GetID();
	jump.shJumpActionId = 0;

	if( -1 == GettheNetworkInput().SendMsg( &jump ) )
	{

	}
	unguard;
}

// 发送角色拔出武器的消息
void CPlayerMgr::SendDrawWeapon()
{
	guardfunc;
	if( !m_pMe )
		return;
	MsgDrawWeapon msg;
	msg.header.stID = m_pMe->GetID();

	if( -1 == GettheNetworkInput().SendMsg( &msg ) )
	{

	}
	unguard;
}

// 发送角色收起武器的消息
void CPlayerMgr::SendDrawInWeapon()
{
	guardfunc;
	if( !m_pMe )
		return;
	MsgDrawInWeapon msg;
	msg.header.stID = m_pMe->GetID();

	if( -1 == GettheNetworkInput().SendMsg( &msg ) )
	{

	}
	// 清除战斗姿态标志
	m_pMe->SetFightPose(FALSE);
	unguard;
}

void CPlayerMgr::OnMsgShowIntensifyUI(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgCallIntensify );
	MsgCallIntensify* pIntensify = (MsgCallIntensify*)pMsg;

	unguard;
}

void CPlayerMgr::OnMsgShowReduceUI(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgCallReduce );
	MsgCallReduce* pReduce = (MsgCallReduce*)pMsg;

	unguard;
}

void CPlayerMgr::OnMsgChangeItemPwd(Msg* pMsg)
{

}

void CPlayerMgr::OnMsgEctypeMapInfo( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckEctypeMapInfo );
	MsgAckEctypeMapInfo* pMsgMapInfo = NULL;
	pMsgMapInfo = (MsgAckEctypeMapInfo*)pMsg;

	unguard;
}

bool ReqDuelCallback( const char bPressYesButton, void *pData )
{
	guardfunc;
	MsgReqDuel* duel = (MsgReqDuel*)pData;
	MsgAckDuel ack;
	ack.shDuelID = duel->shTargetID;
	if( bPressYesButton )
	{
		ack.shResult = MsgAckDuel::ResultAgree;
	}
	else
	{
		ack.shResult = MsgAckDuel::ResultRefuse;     
	}
	GettheNetworkInput().SendMsg(&ack);
	return true;
	unguard;
}

void CPlayerMgr::OnMsgReqDuel( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgReqDuel );
	MsgReqDuel* duel = (MsgReqDuel*)pMsg;

	if(duel->shTargetID == -1)
	{
		return;
	}

	CPlayer* pPlayer = FindByID(duel->shTargetID);
	if(pPlayer != NULL)
	{
		//--zizi add 这里检测玩家是否是在自己黑名单中
		if( thePlayerRole.isFrdInBlackList(pPlayer->GetName()) )
		{
			MsgAckDuel ack;
			ack.shDuelID = duel->shTargetID;
			ack.shResult = MsgAckDuel::ResultInBlackList;     
			GettheNetworkInput().SendMsg(&ack);

			return;
		}

		// 判断是否拒绝比武
		bool bInFight = false;
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			bInFight = theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting);
		bool bRefuseInFight = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseDuelInFight );
		bool bRefuse = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseDuel );
		if( (bInFight && bRefuseInFight) || (!bInFight && bRefuse) )
		{
			ReqDuelCallback(false, duel);
			return;
		}

		char szText[256] = {0};
		_snprintf(szText, sizeof(szText)-1, theXmlString.GetString(eTextPlayer_InterchangeReqQue), pPlayer->GetName());
		s_CUI_ID_FRAME_MessageBox.Show( szText,
			theXmlString.GetString(eTextPlayer_InterchangeReqMsg),
			CUI_ID_FRAME_MessageBox::eTypeYesNo, false,
			ReqDuelCallback, duel, duel->GetLength());
		s_CUI_ID_FRAME_MessageBox.SetAutoClose(30, false);
		PlaySoundConfig( SoundConfig::EST_RequestFight );
	}
	unguard;
}

void CPlayerMgr::OnMsgDuelStart( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgDuelStart );
	MsgDuelStart* start = (MsgDuelStart*)pMsg;

	thePlayerRole.SetDuelTarget(start->shTargetID);
	thePlayerRole.SetDuelPos(start->vFlagPos);
	CWorldTile* pCurrTile = CURRENTTILE;
	if( pCurrTile )
		thePlayerRole.SetDuelMapID(pCurrTile->GetMapId());

	if( m_pMe )
		m_pMe->SetDuel(TRUE);
	CPlayer* TargetPlayer = FindByID( start->shTargetID );
	if( TargetPlayer )
	{
		TargetPlayer->m_bDueler = TRUE;
		if( TargetPlayer->m_nDuelEffectId == -1 )
		{	
			TargetPlayer->m_nDuelEffectId = PlayEffect( "Common\\DuelEffect.ini", TargetPlayer  );
		}		
		thePlayerRole.SetDuelTime(4);
		thePlayerRole.SetDuelName(TargetPlayer->GetName());
	}

	CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( g_nPKFlagEffectID );
	if( pModelEffect )
	{
		pModelEffect->m_dwBornTime = HQ_TimeGetTime();
		int nNum = pModelEffect->m_nNumInstance;

		for( int nInst = 0; nInst < nNum; nInst++ )
		{
			CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

			if( !pInstance )
				continue;

			pInstance->dwBornTime = HQ_TimeGetTime() + /*pEffect->m_dwDelay*nInst*/pInstance->fDelay;
			pInstance->bVisible = true;
		}
	}

	CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nPKFlagEffectContainerID );
	if( pEffectContainer )
	{
		float fEffectHelperZ = 0;
		IEffectHelper* pEffectHelper = NULL;

		{
			fEffectHelperZ = SwGlobal::GetWorldPicker()->GetZByXY( WORLD_HEIGHT, start->vFlagPos.x, start->vFlagPos.y, 0 );

			CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
			CWorldChunk* pChunk = pTile->GetChunkFromPos(start->vFlagPos.x, start->vFlagPos.y);

			if( pChunk )
			{
				if(pChunk->GetLiquidHeight() > fEffectHelperZ )
				{
					fEffectHelperZ =  pChunk->GetLiquidHeight()/*m_fWaterHeight*/;
				}
			}
		}

		pEffectHelper = pEffectContainer->GetEffectHelper( eEffectBindPart_Body );
		pEffectHelper->SetPos( start->vFlagPos.x, start->vFlagPos.y, fEffectHelperZ );
	}
	PlaySoundConfig( SoundConfig::EST_StartFight );
	unguard;
}
void CPlayerMgr::OnMsgAckDuel( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckDuel );
	MsgAckDuel* ack = (MsgAckDuel*)pMsg;

	if( ack->shResult == MsgAckDuel::ResultRefuse )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Dual, theXmlString.GetString(eClient_Deul_NoneAgreen));
	}
	else if( ack->shResult == MsgAckDuel::ResultInBlackList )
	{

	}
	unguard;
}
void CPlayerMgr::OnMsgDuelEnd( Msg* pMsg )
{
	guardfunc;
	if( !m_pMe )
		return;
	CHECK_MSGLEN( pMsg, MsgDuelEnd );
	MsgDuelEnd* end = (MsgDuelEnd*)pMsg;

	char szText[256] = {0};
	if(m_pMe->GetID() != end->shWinCharID && m_pMe->GetID() != end->shLostCharID)
	{
		CPlayer* pWin = FindByID(end->shWinCharID);
		CPlayer* pLost = FindByID(end->shLostCharID);

		if( pWin && pLost )
		{
			_snprintf( szText, sizeof(szText)-1, theXmlString.GetString(eClient_AddInfo_2slk_127),
				pWin?pWin->GetName():theXmlString.GetString(eClient_AddInfo_2slk_128),
				pLost?pLost->GetName():theXmlString.GetString(eClient_AddInfo_2slk_128));

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Dual, szText );
		}
	}
	else
	{
		if(end->shWinCharID == m_pMe->GetID() && end->shLostCharID == thePlayerRole.GetDuelTarget())
		{
			_snprintf(szText, sizeof(szText)-1, theXmlString.GetString(eTextPlayer_WinOver), thePlayerRole.GetDuelName());
			theHeroGame.GetDuelTips()->AddTips(CDuelTips::Image_FIGHT_WIN);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Dual, szText );
		}
		else if(end->shLostCharID == m_pMe->GetID() && (end->shWinCharID == thePlayerRole.GetDuelTarget() || end->shWinCharID == -1) )
		{
			_snprintf(szText, sizeof(szText)-1, theXmlString.GetString(eTextPlayer_Underdog), thePlayerRole.GetDuelName());
			theHeroGame.GetDuelTips()->AddTips(CDuelTips::Image_FIGHT_LOSE);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Dual, szText );
		}

		CPlayer* pPlayer = FindByID(thePlayerRole.GetDuelTarget());
		if(pPlayer != NULL)
		{
			pPlayer->m_bDueler = FALSE;
			if( pPlayer->m_nDuelEffectId != -1 )
			{
				IEffect* pEffect = GetEffectMgr()->GetEffect( pPlayer->m_nDuelEffectId );
				if( pEffect )
				{
					pEffect->SetDead();
				}
				pPlayer->m_nDuelEffectId = -1;
			}
		}
		thePlayerRole.SetDuelTime(0); 
		thePlayerRole.SetDuelTarget(-1);
		thePlayerRole.SetDuelName("");
		m_pMe->SetDuel(FALSE);
		g_bTheRoleAttackLockTarget = FALSE;
		thePlayerRole.SetDuelOutTime(10);
		thePlayerRole.SetSelfOutTime(10);
	}

	CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( g_nPKFlagEffectID );
	if( pModelEffect )
	{
		int nNum = pModelEffect->m_nNumInstance;
		for( int nInst = 0; nInst < nNum; nInst++ )
		{
			CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );
			if( !pInstance )
				continue;
			pInstance->bVisible = false;
		}
	}
	PlaySoundConfig( SoundConfig::EST_EndFight );
	unguard;
}

//void CPlayerMgr::OnMsgGuildMemberPos( Msg* pMsg )
//{
//	guardfunc;
//	CHECK_MSGLEN( pMsg, MsgGuildMemberPos );
//	MsgGuildMemberPos* pos = (MsgGuildMemberPos*)pMsg;
//
//	CGangMgr* theGuild = thePlayerRole.GetGangMgr();
//	if(theGuild == NULL)
//	{
//		return;
//	}
//
//	int nNum = 0;
//	while(pos->PosList[nNum].nDBId != -1)
//	{
//		GuildMember* pMember = theGuild->FindByDBId(pos->PosList[nNum].nDBId);
//		if(pMember != NULL)
//		{
//			pMember->stMapID = pos->PosList[nNum].nMap;
//		}
//		nNum++;
//	}
//
//	s_CUI_Guild.Refeash();
//	unguard;
//}
void CPlayerMgr::OnMsgSetItemAscription( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, Msg2CItemAdscription );

	Msg2CItemAdscription* msg = (Msg2CItemAdscription*)pMsg;

	CPlayer* pItem = FindByID( msg->npcid );
	if( pItem )
	{
		if( msg->adscriptionPlayerId != -1 )
			pItem->SetAdscriptionPlayerId( msg->adscriptionPlayerId );
		if(	msg->adscriptionGroupId != -1 )
			pItem->SetAdscriptinGroupId( msg->adscriptionGroupId );
		if( msg->bAdscription_TeamHeader )
			pItem->SetAdscription_teamHeader( msg->bAdscription_TeamHeader );
		if( msg->bHold_Groupid )
			pItem->SetHold_GroupId( msg->bHold_Groupid );
	}
	unguard;
}

void CPlayerMgr::OnMsgSkillExpChang(Msg *pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgSkillExpUp );
	MsgSkillExpUp* pSkillExpUp = (MsgSkillExpUp*)pMsg;

	if( pMsg->header.stID == GetMyID() )
	{
		thePlayerRole.SkillExpChang(pSkillExpUp->ustSkillID,pSkillExpUp->dwSkillExp);
		ItemDefine::SItemSkill* pSKill = GettheItemDetail().GetSkillByID(pSkillExpUp->ustSkillID,pSkillExpUp->stSkilllevel);
		if (pSKill)
		{

		}		
	}
	unguard;
}

void CPlayerMgr::OnMsgReqSkillID(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgREQSkillExpForSkillID );
	MsgREQSkillExpForSkillID* pReq = (MsgREQSkillExpForSkillID*)pMsg;
	unguard;
}

void  CPlayerMgr::OnMsgKillMonster(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	CHECK_MSGLEN( pMsg, MsgKillMonster );

	MsgKillMonster* pKill = (MsgKillMonster*)pMsg;
	// 吸收经验特效

	// modified, jiayi, [2009/11/15]
	int nSkillExp = 0;
	CPlayer* pMonster = FindByID(pKill->stMonsterID);
	if( !pMonster )
		return;
	int l = pMonster->GetLevel() - thePlayerRole.GetLevel();
	if (l >= -5 && l <= 5)
		nSkillExp = 800;
	else if (l < -5)
		nSkillExp = 601;
	else
		nSkillExp = 1000;

	CPlayer* pPlayer = pMonster;//FindByID( pKill->stMonsterID );

	if( pPlayer && m_pMe && pKill->nExp > 0 )
	{
		int nCount = 0;
		for( int i = 0; i < nSkillExp; )
		{
			int nExpOffset = nSkillExp - i;
			if( nExpOffset > 600 )
			{
				while( nSkillExp - i > 300 )
				{
					int nRand = 50 + rand()%51;
					if( i + nRand > nSkillExp )
					{
						nRand = nSkillExp - i;
						if( nRand > 50 )
						{

						}
					}
					else
					{

					}
					i += nRand;

					if( nCount > 20 )
						break;

					nCount++;
				}
			}
			else if( nExpOffset > 100 )
			{
				while( nSkillExp - i > 50 )
				{
					int nRand = 25 + rand()%26;
					if( i + nRand > nSkillExp )
					{
						nRand = nSkillExp - i;
						if( nRand > 25 )
						{

						}
					}
					else
					{

					}
					i += nRand;

					if( nCount > 20 )
						break;

					nCount++;
				}
			}
			else
			{
				int nRand = 15 + rand()%16;
				if( i + nRand > nSkillExp )
				{
					nRand = nSkillExp - i;
					if( nRand > 15 )
					{
						
					}
					else
					{
						
					}
				}
				else
				{
					
				}
				i += nRand;
			}

			if( nCount > 20 )
				break;

			nCount++;
		}
	}

	return;
	unguard;
}

void CPlayerMgr::OnMsgPKStateChange(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPKStateChange );
	MsgPKStateChange* pChange = (MsgPKStateChange*)pMsg;

	CPlayer* pPlayer = FindByID( pChange->shCharID );

	if(pPlayer != NULL)
	{
		if(pPlayer == GetMe())
		{
			if(pPlayer->GetPKKillValue() < pChange->nPKValue)
			{
				//右下角提示玩家获得PK值
				int Value =  pChange->nPKValue - pPlayer->GetPKKillValue();
				char szTemp[128];
				sprintf_s(szTemp,127,theXmlString.GetString( eClient_PkValue_ADD ),Value);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szTemp );
			}
			else if(pPlayer->GetPKKillValue() > pChange->nPKValue)
			{
				int Value =  pPlayer->GetPKKillValue() - pChange->nPKValue;
				char szTemp[128];
				sprintf_s(szTemp,127,theXmlString.GetString( eClient_PkValue_Del ),Value);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szTemp );
			}
		}
		pPlayer->SetPKType( pChange->nPKMode );
		pPlayer->SetPKKillValue( pChange->nPKValue );
		if( pPlayer == GetMe() )
		{
			s_CUI_Group.Refeash();
			s_CUI_ID_FRAME_BaseProperty.Refresh();
			switch (pChange->nPKMode)
			{
			case PKMode_Normal:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString( eText_PKMode_Off ) );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_PKMode_Off ) );
				break;
			case PKMode_Fight:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString( eText_PKMode_On ) );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_PKMode_On ) );
				break;
			case PKMode_Guild:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString( eText_PKMode_GuildOn ) );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_PKMode_GuildOn ) );
				break;
			case PKMode_Critical:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString( eText_PKMode_Fury ) );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_PKMode_Fury ) );
				break;
			case PKMode_AttackFight:
			case PKMode_AttackGuild:
				break;
			}
		}
	}
	unguard;
}

void CPlayerMgr::OnMsgAckChangePKFlag( Msg* pMsg )
{
	guardfunc;
	if( !m_pMe )
		return;
	CHECK_MSGLEN( pMsg, MsgAckChangePKFlag );
	MsgAckChangePKFlag* pAck = (MsgAckChangePKFlag*)pMsg;

	m_pMe->SetPKType( pAck->shFlag );
    s_CUI_ID_FRAME_Group_Me.RefreshPKShowPicture( pAck->shFlag );
	
	unguard;
}

void CPlayerMgr::OnMsgPlayEffect( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPlayEffect );
	MsgPlayEffect *pMsgEffect = (MsgPlayEffect*)pMsg;

	CPlayer* pPlayer = FindByID( pMsgEffect->nPlayerId );
	if( pPlayer )
	{
		PlayEffect( pMsgEffect->szFileName, pPlayer );
	}
	else
	{
		CWSModelEffect* pEffect = MeNew CWSModelEffect;
		char filename[MAX_PATH] = {0};
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1 ,"%s\\Data\\Effect\\%s", GetRootPath(), pMsgEffect->szFileName);
		if( pEffect->LoadSetting( filename, TRUE ) )
		{
			int nEffectID = GetEffectMgr()->RegisterEffect( pEffect );
			if( nEffectID == -1 )
			{
				pEffect->Release();
			}
			else
			{
				int nEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
				pEffect->m_dwBornTime = HQ_TimeGetTime();
				float fRadius = pEffect->m_fRadius;
				int nNum = pEffect->m_nNumInstance;

				CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( nEffectContainerID );

				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
					if( !pInstance )
					{
						continue;
					}

					pInstance->dwBornTime = HQ_TimeGetTime() + /*pEffect->m_dwDelay**/pInstance->fDelay;

					if( pEffectContainer )
					{
						pEffect->SetEffectQuoter( pEffectContainer );
					}

					pInstance->vBornPos = D3DXVECTOR3( pMsgEffect->fX, pMsgEffect->fY, pMsgEffect->fZ );
					pInstance->vPos = pInstance->vBornPos;
					pInstance->bVisible = true;

					// 把特效绑定
					if( pEffectContainer )
					{
						pInstance->pMaster = pEffectContainer->GetEffectHelper( eEffectBindPart_Body );
					}
				}

				if( pEffectContainer )
				{
					pEffectContainer->ApplyEffect( 0, pEffect->GetID() );
				}
			}
		}
		else
		{
			pEffect->Release();
		}
		pEffect = NULL;
	}
	unguard;
}

void CPlayerMgr::OnMsgShowIntonateBar(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgShowIntonateBar );
	MsgShowIntonateBar *pIntonate = (MsgShowIntonateBar*)pMsg;

	CPlayer* pPlayer = FindByID( pIntonate->header.stID );

	if( !pPlayer )
		return;

	if( pPlayer->IsMoving() )
		pPlayer->StopMoving();
	
	pPlayer->SetWithNPCAnimInfo( pIntonate->nActionID, pIntonate->dwTime );
	if( pIntonate->nType == IntonateType_Item )//判断是否可被打断
	{
		s_CUI_NpcTaskDialogBox.m_TaskProgerss.m_nItemID = pIntonate->nID;
	}

	if( pPlayer == GetMe() )
		s_CUI_NpcTaskDialogBox.ShowIntonateBar(pIntonate->dwTime, theXmlString.GetString(pIntonate->nStringID));


// 	if( gCfg.m_PlayerNpcActions.find( pIntonate->nActionID ) != gCfg.m_PlayerNpcActions.end() )//found
// 	{
// 		const char* pcEndAnim = 0;
// 		if( pPlayer->IsHaveWeapon() )
// 			pcEndAnim = "single_idle";
// 		else
// 			pcEndAnim = "idle";
// 
// 		//pPlayer->PlayAnim( gCfg.m_PlayerNpcActions[pIntonate->nActionID].m_acSingName, pIntonate->dwTime, pcEndAnim );
// 
//  		CPlayerAnim* pAnim = pPlayer->GetAnim();
//  		if( pAnim )
//  		{
//  			pAnim->PlayLowerAnim( gCfg.m_PlayerNpcActions[pIntonate->nActionID].m_acSingName,
//  				MexAnimCtrl::eNormalPlay,
//  				0,
//  				pIntonate->dwTime,
//  				pIntonate->dwTime,
//  				MexAnimCtrl::eDefaultBlendingTime,
//  				pcEndAnim,
// 				MexAnimCtrl::eNormalPlay );
//  		}
// 	}

	unguard;
}


bool TellRelive(char bIsTell,void *pData )
{
	//theHeroGame.GetPlayerMgr()->SetReLived(FALSE);
	if (bIsTell)
	{
		if(theHeroGame.GetPlayerMgr())
		{
			MsgAgRelive msgLive;

			GettheNetworkInput().SendMsg(&msgLive);
			// 关闭之后所有复活弹出框
			s_CUI_ID_FRAME_MessageBox.closeAllMatchString(1, theXmlString.GetString(eUI_IsRelive));
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}	
}

void CPlayerMgr::OnMsgReqRelive(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}

	CHECK_MSGLEN( pMsg, MsgAgRelive );
	MsgAgRelive* pLive = (MsgAgRelive*)pMsg;

	if (pLive)
	{
		CPlayer* pPlayer = FindByID( pLive->activeid );

		if (pPlayer&&pPlayer->IsPlayer())
		{
			m_sttype = pLive->sttype;
			m_activeid = pLive->activeid;

			/*s_CUI_ID_FRAME_ESCDLG.SetVisable(false);*/
			// 施放复活技能的人
			CPlayer* pObliger = FindByID( pLive->activeid );
			if( !pObliger )
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eUI_IsRelive), theXmlString.GetString(eClient_AddInfo_2slk_16),
				CUI_ID_FRAME_MessageBox::eTypeYesNo, true, TellRelive);
			else
			{
				char str[MAX_PATH] = {0};
				MeSprintf_s(str,sizeof(str)/sizeof(char) - 1, "%s %s", pObliger->GetName(), theXmlString.GetString(eUI_IsRelive));
				s_CUI_ID_FRAME_MessageBox.Show( str, theXmlString.GetString(eClient_AddInfo_2slk_16),
					CUI_ID_FRAME_MessageBox::eTypeYesNo, true, TellRelive);
			}
			s_CUI_ID_FRAME_MessageBox.SetAutoClose(60, false);

			//TellRelive(true, 0);
		}
	}
	unguard;
}

void  CPlayerMgr::OnMsgChangPower(Msg* pMsg)
{
	guardfunc;
	unguard;
}

void  CPlayerMgr:: OnMsgChangPowerPoint(Msg* pMsg)
{
	guardfunc;
	unguard;
}

void CPlayerMgr::OnMsgHitchMoveTargetPos( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgHitchMoveTargetPos );
	MsgHitchMoveTargetPos *pMsg1 = (MsgHitchMoveTargetPos*)pMsg;
	D3DXVECTOR3 vTargetPos = pMsg1->vTargetPos;
	CPlayer* pPlayer = FindByID(pMsg1->header.stID);
	if( pPlayer )
	{
		if (!pPlayer->IsUncontrolFlying())
		{
			vTargetPos.z = pPlayer->GetPos().z;
		}
		pPlayer->SetUncontrolMoveTargetPos( vTargetPos );
	}
	unguard;
}

void CPlayerMgr::OnMsgCanControlMoving( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgCanControlMoving );
	MsgCanControlMoving *pMsg1 = (MsgCanControlMoving*)pMsg;
	CPlayer* pPlayer = FindByID(pMsg1->header.stID);
	if( pPlayer )
	{
		pPlayer->SetUncontrolMoving( !pMsg1->bCanControlMoving,pMsg1->bIsFlyMoving );
		if (pPlayer == GetMe())
		{
			if (pPlayer->IsUncontrolMoving() && pPlayer->IsUncontrolFlying())
			{
				SwGlobal::s_SimpleMapLoadDistance = gCfg.m_nSimpleMapLoadDistanceFly;
			}
			else
			{
				SwGlobal::s_SimpleMapLoadDistance = gCfg.m_nSimpleMapLoadDistance;
			}

			//不在托管状态，取消相机托管
			if(pMsg1->bCanControlMoving)
			{
				if(IsTracking())
				   EndTrack();
			}
		}
	}
	unguard;
}

void CPlayerMgr::OnOpenUI( Msg* pMsg )
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgOpenUI );
	MsgOpenUI*	msg = (MsgOpenUI*)pMsg;

	switch( msg->UIFlag )
	{
	case AN_S2A_OpenUI_NULL:
		break;
	case AN_S2A_OpenUI_StoryBook:
		{
		}
		break;
	case AN_S2A_OpenUI_ChatBULL:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatBULL);
		}
		break;
	case AN_S2A_OpenUI_ChatSHOUT:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatSHOUT);
		}
		break;
	case AN_S2A_OpenUI_ChatHIGHSHOUT:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatHIGHSHOUT);
		}
		break;
	case AN_S2A_OpenUI_ChatParticular1:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatParticular1);
		}
		break;
	case AN_S2A_OpenUI_ChatParticular2:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatParticular2);
		}
		break;
	case AN_S2A_OpenUI_ChatParticular3:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatParticular3);
		}
		break;
	case AN_S2A_OpenUI_ChatParticular4:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatParticular4);
		}
		break;
	case AN_S2A_OpenUI_ChatParticular5:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatParticular5);
		}
		break;
	case AN_S2A_OpenUI_ChatParticular6:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatParticular6);
		}
		break;
	case AN_S2A_OpenUI_ChatParticular7:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatParticular7);
		}
		break;
	case AN_S2A_OpenUI_ChatParticular8:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatParticular8);
		}
		break;
	case AN_S2A_OpenUI_ChatParticular9:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatParticular9);
		}
		break;
	case AN_S2A_OpenUI_ChatParticular10:
		{
			s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatParticular10);
		}
		break;
	case AN_S2A_OpenUI_LearnSkill:
		{
			s_CUI_ID_FRAME_SKILL.SetVisableWherefore(true,CUI_ID_FRAME_SKILL::EWherefore_NpcLearn);
			//s_CUI_ID_FRAME_SKILL_LEARN.SetVisable(true);
		}break;
	case AN_S2A_OpenUI_Intensify:
		{
			//通过Npc打开UI就把标志设为false

			if (s_CUI_ID_FRAME_Gem.IsVisable())
			{
				s_CUI_ID_FRAME_Gem.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Hole.IsVisable())
			{
				s_CUI_ID_FRAME_Hole.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_SHOP.IsVisable())
			{
				s_CUI_ID_FRAME_SHOP.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemUp.IsVisable())
			{
				s_CUI_ID_FRAME_GemUp.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_TransferStar.IsVisable())
			{
				s_CUI_ID_FRAME_TransferStar.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_JieBang.IsVisable())
			{
				s_CUI_ID_FRAME_JieBang.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemRemove.IsVisable())
			{
				s_CUI_ID_FRAME_GemRemove.SetVisable(false);
			}

			s_CUI_ID_FRAME_Star.SetIsPocket(false);
			s_CUI_ID_FRAME_Star.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_Star.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{

				s_CUI_ID_FRAME_Star.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_Maintain:
		{
			s_CUI_ID_FRAME_EquipCopy.SetEquipCopyVisable( true ,false);
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_EquipCopy.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{

				s_CUI_ID_FRAME_EquipCopy.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_MaintainCross:
		{
			s_CUI_ID_FRAME_EquipCopy.SetEquipCopyVisable( true ,true);
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_EquipCopy.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{

				s_CUI_ID_FRAME_EquipCopy.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_IntensifyStar:
		{
			s_CUI_ID_FRAME_IntensifyStar.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			if( GetMe() )
			{
				s_CUI_ID_FRAME_IntensifyStar.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_Identify:
		{
			s_CUI_ID_FRAME_GoldPlating.SetVisable( true );
			s_CUI_ID_FRAME_GoldPlating.SetPlatingType( CUI_ID_FRAME_GoldPlating::ePlatingType_Identify );
			s_CUI_ID_FRAME_PACK.SetVisable( true );			
			if( GetMe() )
			{
				s_CUI_ID_FRAME_GoldPlating.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}	
		}
		break;
	case AN_S2A_OpenUI_KaiGuang:
		{
			s_CUI_ID_FRAME_GoldPlating.SetPlatingType( CUI_ID_FRAME_GoldPlating::ePlatingType_KaiGuang );
			s_CUI_ID_FRAME_GoldPlating.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );			
			if( GetMe() )
			{
				s_CUI_ID_FRAME_GoldPlating.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}	
		}
		break;
	case AN_S2A_OpenUI_ShopChangePoint:
		{
			s_CUI_ID_FRAME_ShopChangePoint.SetVisable( true );
		}
		break;
	case AN_S2A_OpenUI_Decompound:
		s_CUI_ID_FRAME_Decompound.SetVisable( true );
		if( GetMe() )
			s_CUI_ID_FRAME_Decompound.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
		break;
	case AN_S2A_OpenUI_LotteryAwards:
		s_CUI_ID_FRAME_LotteryAwardExplain.SetVisable( true );
		break;
	case AN_S2A_OpenUI_MoveStarToEquip:
		s_CUI_ID_FRAME_MoveStar.SetVisable( true, MsgMoveStarReq::ECD_MoveToEquip );
		break;
	case AN_S2A_OpenUI_MoveStarToItem:
		s_CUI_ID_FRAME_MoveStar.SetVisable( true, MsgMoveStarReq::ECD_MoveToItem );
		break;
	case AN_S2A_OpenUI_FiveElement:
		{
			s_CUI_ID_FRAME_FiveXing.SetVisable( true );
			if( GetMe() )
				s_CUI_ID_FRAME_FiveXing.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			s_CUI_ID_FRAME_FiveXing.SetOperate( MsgSuitElementCheckupReq::ECD_Checkup );
			s_CUI_ID_FRAME_FiveXing.SetAtomVisible( MsgSuitElementCheckupReq::ECD_Checkup );
		}
		break;
	case AN_S2A_OpenUI_FiveElementClear:
		{
			s_CUI_ID_FRAME_FiveXing.SetVisable( true );
			if( GetMe() )
				s_CUI_ID_FRAME_FiveXing.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );						
			s_CUI_ID_FRAME_FiveXing.SetOperate( MsgSuitElementCheckupReq::ECD_Clear );
			s_CUI_ID_FRAME_FiveXing.SetAtomVisible( MsgSuitElementCheckupReq::ECD_Clear );
		}
		break;
	//case AN_S2A_OpenUI_RealAward:
	//	{
	//		s_CUI_ID_FRAME_WebAward.SetVisable( true );
	//		if( GetMe() )
	//			s_CUI_ID_FRAME_WebAward.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
	//		s_CUI_ID_FRAME_PACK.SetVisable( true );
	//	}
	//	break;
	case AN_S2A_OpenUI_SpecialRepair:
		{
			s_CUI_ID_FRAME_SpecialRepair.SetVisable( true );
		}
		break;
	case AN_S2A_OpenUI_EquipUpgrade:
		{
			s_CUI_ID_FRAME_EquipUpgrade.SetWeaponUpgrade(false);
			s_CUI_ID_FRAME_EquipUpgrade.SetVisable( true );
			if( GetMe() )
				s_CUI_ID_FRAME_EquipUpgrade.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			s_CUI_ID_FRAME_PACK.SetVisable( true );

			ResetWindowPosition(s_CUI_ID_FRAME_EquipUpgrade.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
		}
		break;
	case AN_S2A_OpenUI_WeaponUpgrade:
		{
			s_CUI_ID_FRAME_EquipUpgrade.SetWeaponUpgrade(true);
			s_CUI_ID_FRAME_EquipUpgrade.SetVisable( true );
			if( GetMe() )
				s_CUI_ID_FRAME_EquipUpgrade.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			s_CUI_ID_FRAME_PACK.SetVisable( true );

			ResetWindowPosition(s_CUI_ID_FRAME_EquipUpgrade.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
		}
		break;
	case AN_S2A_OpenUI_FiveXingChange:
		{
			s_CUI_ID_FRAME_FiveXingChange.SetVisable(true);
			if( GetMe() )
				s_CUI_ID_FRAME_FiveXingChange.SetVisiblePosition(*(Vector*)&GetMe()->GetPos());
			s_CUI_ID_FRAME_PACK.SetVisable(true);

			ResetWindowPosition(s_CUI_ID_FRAME_FiveXingChange.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
		}
		break;
	case AN_S2A_OpenUI_FinvXinigLevel:
		{
			s_CUI_ID_FRAME_FiveXingUpdate.SetVisable(true);
			if( GetMe() )
				s_CUI_ID_FRAME_FiveXingUpdate.SetVisiblePosition(*(Vector*)&GetMe()->GetPos());
			s_CUI_ID_FRAME_PACK.SetVisable(true);

			ResetWindowPosition(s_CUI_ID_FRAME_FiveXingUpdate.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
		}
		break;
	case AN_S2A_OpenUI_UpgradeSkillEquip:
		{
			s_CUI_ID_FRAME_SkillEquipUpdate.SetVisable( true );
		}
		break;
	case AN_S2A_OpenUI_ChangeSkillEquip:
		{
			s_CUI_ID_FRAME_SkillEquipChange.SetVisable( true );
		}
		break;
	case AN_S2A_OpenUI_ShowScriptGif:
		{
			s_CUI_ID_FRAME_ShowScriptGif.SetVisable( true );
		}
		break;
	case AN_S2A_OpenUI_ChangeName:
		{
			s_CUI_ID_FRAME_PlayerRename.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_PointShop:
		{
			s_CUI_ID_FRAME_PointShop.Refresh();
			s_CUI_ID_FRAME_PointShop.SetVisable(true);

			if( GetMe() )
			{
				s_CUI_ID_FRAME_PointShop.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}	

			MsgJiFengShopItemsListReq msg;

			GettheNetworkInput().SendMsg( &msg );

		}
		break;
    case AN_S2A_OpenUI_MailSystem:
        {
             s_CUI_ID_FRAME_MailMain.SetVisable(true);
			if( GetMe() )
			{
				s_CUI_ID_FRAME_MailMain.SetVisiblePosition( GetMe()->GetPos() );
            }
        }
        break;
	case AN_S2A_OpenUI_MoveStarUprade:
		{
			s_CUI_ID_FRAME_MoveStarUpgrade.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );

			ResetWindowPosition(s_CUI_ID_FRAME_MoveStarUpgrade.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
		}
		break;
	case AN_S2A_OpenUI_StarMaterialUpgrade:
		{
			s_CUI_ID_FRAME_StarMaterialUpgrade.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SwitchToBag(BT_MaterialBag);

			ResetWindowPosition(s_CUI_ID_FRAME_StarMaterialUpgrade.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
		}
		break;
	case AN_S2A_OpenUI_GoldTrade:
		{
			s_CUI_ID_FRAME_GoldTrade.Refresh();
			s_CUI_ID_FRAME_GoldTrade.SetVisable(true);

			if( GetMe() )
			{
				s_CUI_ID_FRAME_GoldTrade.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}	

// 			MsgRequestSystemAuction msg;
// 			GettheNetworkInput().SendMsg( &msg );
		}
		break;
    case AN_S2A_OpenUI_FiveXingTrans:
        {
            s_CUI_ID_FRAME_FiveXingDisplace.SetVisable(true);
			s_CUI_ID_FRAME_PACK.SetVisable(true);
            if(GetMe())
            {
                s_CUI_ID_FRAME_FiveXingDisplace.SetVisiblePosition(*(Vector*)&GetMe()->GetPos());
            }

			ResetWindowPosition(s_CUI_ID_FRAME_FiveXingDisplace.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
        }
        break;
    case AN_S2A_OpenUI_HookOffline:         // NPC离线挂机
        {
			s_CUI_ID_FRAME_ExitTip.SetOpenUi(true);
			s_CUI_ID_FRAME_ExitTip.SetVisable( true );
			s_CUI_ID_FRAME_ExitTip.RefreshInfo();
            //s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eIsExitGame ), theXmlString.GetString( eText_HookOffline_Affirm ),
           //     CUI_ID_FRAME_MessageBox::eTypeYesNo, true, CUI_ID_FRAME_ExitGame::ExitByHookOff );
        }
        break;
    case AN_S2A_OpenUI_MountBreed:          // 交配
        {
            s_CUI_ID_FRAME_PetMore.SetVisable( true );
        }
        break;
    case AN_S2A_OpenUI_LearnCaoYao:         //制药学习界面
        {
            s_CUI_ID_ProduceLearn.ShowByType( CPlayerRole::TYPE_CaoYao );
        }
        break;
    case AN_S2A_OpenUI_LearnZhuBao:         //珠宝学习界面
        {
            s_CUI_ID_ProduceLearn.ShowByType( CPlayerRole::TYPE_ZhuBao );
        }
        break;
    case AN_S2A_OpenUI_LearnDuanZao:        //锻造学习界面
        {
            s_CUI_ID_ProduceLearn.ShowByType( CPlayerRole::TYPE_DuanZao );
        }
        break;
    case AN_S2A_OpenUI_LearnZhuJia:         //铸甲学习界面
        {
            s_CUI_ID_ProduceLearn.ShowByType( CPlayerRole::TYPE_ZhuJia );
        }
        break;
    case AN_S2A_OpenUI_LearnGongYi:         //工艺学习界面
        {
            s_CUI_ID_ProduceLearn.ShowByType( CPlayerRole::TYPE_GongYi );
        }
        break;
    case AN_S2A_OpenUI_LearnXunMa:          //驯马学习界面
        {
            s_CUI_ID_ProduceLearn.ShowByType( CPlayerRole::TYPE_XunMa );
        }
        break;
    case AN_S2A_OpenUI_LearnCaiKuang:       //采矿学习界面
        {
            s_CUI_ID_ProduceLearn.ShowByType( CPlayerRole::TYPE_CaiKuang );
        }
        break;
    case AN_S2A_OpenUI_LearnCaiYao:         //采药学习界面
        {
            s_CUI_ID_ProduceLearn.ShowByType( CPlayerRole::TYPE_CaiYao );
        }
        break;
    case AN_S2A_OpenUI_LearnBuZhuo:         //捕捉学习界面      捕捉被改为捕虫
        {
            s_CUI_ID_ProduceLearn.ShowByType( CPlayerRole::TYPE_BuChong );
        }
        break;
	case AN_S2A_OpenUI_DELETESTUDENT:         //删除徒弟
		{
			s_CUI_ID_FRAME_SearchTeacher.ShowMyStudentList();
		}
		break;
	case AN_S2A_OpenUI_CREATEGUILD:         //创建帮会
		{
			s_CUI_ID_FRAME_GUILD_CREATE.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_Soul:         //灵魂
		{
			s_CUI_ID_FRAME_Soul.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_Soul.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{
				s_CUI_ID_FRAME_Soul.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}

			ResetWindowPosition(s_CUI_ID_FRAME_Soul.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
		}
		break;
	case AN_S2A_OpenUI_Hole:         //打孔
		{
			if (s_CUI_ID_FRAME_Gem.IsVisable())
			{
				s_CUI_ID_FRAME_Gem.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Star.IsVisable())
			{
				s_CUI_ID_FRAME_Star.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_SHOP.IsVisable())
			{
				s_CUI_ID_FRAME_SHOP.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemUp.IsVisable())
			{
				s_CUI_ID_FRAME_GemUp.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_TransferStar.IsVisable())
			{
				s_CUI_ID_FRAME_TransferStar.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_JieBang.IsVisable())
			{
				s_CUI_ID_FRAME_JieBang.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemRemove.IsVisable())
			{
				s_CUI_ID_FRAME_GemRemove.SetVisable(false);
			}

			s_CUI_ID_FRAME_Hole.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_Hole.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{

				s_CUI_ID_FRAME_Hole.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_Gem:         //宝石
		{
			if (s_CUI_ID_FRAME_Hole.IsVisable())
			{
				s_CUI_ID_FRAME_Hole.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Star.IsVisable())
			{
				s_CUI_ID_FRAME_Star.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_SHOP.IsVisable())
			{
				s_CUI_ID_FRAME_SHOP.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemUp.IsVisable())
			{
				s_CUI_ID_FRAME_GemUp.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_TransferStar.IsVisable())
			{
				s_CUI_ID_FRAME_TransferStar.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_JieBang.IsVisable())
			{
				s_CUI_ID_FRAME_JieBang.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemRemove.IsVisable())
			{
				s_CUI_ID_FRAME_GemRemove.SetVisable(false);
			}

			s_CUI_ID_FRAME_Gem.SetIsPocket(false);
			s_CUI_ID_FRAME_Gem.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_Gem.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{

				s_CUI_ID_FRAME_Gem.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_GemRemove:         //宝石删除
		{
			if (s_CUI_ID_FRAME_Hole.IsVisable())
			{
				s_CUI_ID_FRAME_Hole.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Star.IsVisable())
			{
				s_CUI_ID_FRAME_Star.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_SHOP.IsVisable())
			{
				s_CUI_ID_FRAME_SHOP.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemUp.IsVisable())
			{
				s_CUI_ID_FRAME_GemUp.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Gem.IsVisable())
			{
				s_CUI_ID_FRAME_Gem.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_JieBang.IsVisable())
			{
				s_CUI_ID_FRAME_JieBang.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_TransferStar.IsVisable())
			{
				s_CUI_ID_FRAME_TransferStar.SetVisable(false);
			}

			s_CUI_ID_FRAME_GemRemove.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_GemRemove.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{
				s_CUI_ID_FRAME_GemRemove.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_GemReplace:         //宝石替换
		{
			s_CUI_ID_FRAME_GemReplace.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_GemReplace.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{
				s_CUI_ID_FRAME_GemReplace.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_Purple:         //鎏金
		{
			s_CUI_ID_FRAME_Purple.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_Purple.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{
				s_CUI_ID_FRAME_Purple.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_ReOpenLight:         //鎏金回炉
		{
			s_CUI_ID_FRAME_Repurple.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_Repurple.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{
				s_CUI_ID_FRAME_Repurple.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_Recycle:
		{
			s_CUI_ID_FRAME_EquipReturn.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_EquipReturn.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{

				s_CUI_ID_FRAME_EquipReturn.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_Charm:
		{
			s_CUI_ID_FRAME_Symbol.SetVisable( true) ;
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_Symbol.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{
				s_CUI_ID_FRAME_Symbol.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_Amulet:         //护身符上色
		{
			s_CUI_ID_FRAME_Amulet.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_Amulet.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{
				s_CUI_ID_FRAME_Amulet.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_GemLevelUp:         //宝石升阶
		{
			if (s_CUI_ID_FRAME_Gem.IsVisable())
			{
				s_CUI_ID_FRAME_Gem.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Star.IsVisable())
			{
				s_CUI_ID_FRAME_Star.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_SHOP.IsVisable())
			{
				s_CUI_ID_FRAME_SHOP.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Hole.IsVisable())
			{
				s_CUI_ID_FRAME_Hole.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_TransferStar.IsVisable())
			{
				s_CUI_ID_FRAME_TransferStar.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_JieBang.IsVisable())
			{
				s_CUI_ID_FRAME_JieBang.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemRemove.IsVisable())
			{
				s_CUI_ID_FRAME_GemRemove.SetVisable(false);
			}

			s_CUI_ID_FRAME_GemUp.SetIsPocket(false);
			s_CUI_ID_FRAME_GemUp.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			//s_CUI_ID_FRAME_PACK.ID_CHECKBOX_MaterialOnCheckBoxCheck(NULL,NULL);
			ResetWindowPosition(s_CUI_ID_FRAME_GemUp.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{
				s_CUI_ID_FRAME_GemUp.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}			
		}
		break;
	case AN_S2A_OpenUI_XSJLevelUp:         //宝石升阶
		{
			s_CUI_ID_FRAME_GemMaterialUp.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			ResetWindowPosition(s_CUI_ID_FRAME_GemMaterialUp.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
			if( GetMe() )
			{
				s_CUI_ID_FRAME_GemMaterialUp.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}	
		}
		break;
	case AN_S2A_OpenUI_ApplyJoinGuild://申请入帮
		{
			s_CUI_ID_FRAME_GuildApply.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_LevelOneGuildShop://1级帮会商店
		{
			s_CUI_ID_FRAME_SHOP.SetGuildShop(1);
		}
		break;
	case AN_S2A_OpenUI_LevelTwoGuildShop://2级帮会商店
		{
			s_CUI_ID_FRAME_SHOP.SetGuildShop(2);
		}
		break;
	case AN_S2A_OpenUI_LevelThreeGuildShop://3级帮会商店
		{
			s_CUI_ID_FRAME_SHOP.SetGuildShop(3);
		}
		break;
	case AN_S2A_OpenUI_LevelFourGuildShop://4级帮会商店
		{
			s_CUI_ID_FRAME_SHOP.SetGuildShop(4);
		}
		break;
	case AN_S2A_OpenUI_LevelFiveGuildShop://5级帮会商店
		{
			s_CUI_ID_FRAME_SHOP.SetGuildShop(5);
		}
		break;
	case AN_S2A_OpenUI_LevelSixGuildShop://6级帮会商店
		{
			s_CUI_ID_FRAME_SHOP.SetGuildShop(6);
		}
		break;
    case AN_S2A_OpenUI_PetStorage:
        {
            s_CUI_ID_FRAME_PetStorage.ShowPetStorage( true );
			if( GetMe() )
			{
				s_CUI_ID_FRAME_PetStorage.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}	
        }
        break;
	case AN_S2A_OpenUI_EquipqualityIdentify:
		{
			s_CUI_ID_FRAME_IdentifyQuality.SetVisable(true);
			if(GetMe())
				s_CUI_ID_FRAME_IdentifyQuality.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
		}
		break;
	case AN_S2A_OpenUI_StallQuery:	//摆摊查询界面
		{
			s_CUI_ID_FRAME_QueryStall.SetVisable(true);
			if(GetMe())
				s_CUI_ID_FRAME_QueryStall.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
		}
		break;

	case AN_S2A_OpenUI_QuestCommitItem:	//任务提交物品
		{
			s_CUI_ID_FRAME_CorpsTask.SetVisable(true);
			s_CUI_ID_FRAME_CorpsTask.SetQuestID( msg->openParam );
		}
		break;
	case AN_S2A_OpenUI_PetBreed: //宠物繁殖
		{
			s_CUI_ID_FRAME_SuAnimalMore.SetVisable(true);
		}
		break;

	case AN_S2A_OpenUI_PetUp:// //使用宠物悟性升级
		{
			s_CUI_ID_FRAME_SuAnimalUp.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_PetStudy://宠物技能学习
		{
			s_CUI_ID_FRAME_SuAnimalStudy.SetVisable(true);
		}
		break;
	case AN_S2A_OPenUI_PetMaterialUp://道具升级悟性
		{
			s_CUI_ID_FRAME_SuAnimalMaterialUp.SetVisable(true);
		}
		break;

	//case AN_S2A_OpenUI_CreateFamily: //创建家族
	//	{
	//		s_CUI_ID_FRAME_GUILD_FamilyCreate.SetVisable(true);
	//	}
	//	break;
	case AN_S2A_OpenUI_CreateFamily: //创建家族
		{
			s_CUI_ID_FRAME_Family_Create.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_ApplyJoinFamily:
		{
			s_CUI_ID_FRAME_FamilyApply.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_ZhujiangBianshen:
		{
			s_CUI_ID_FRAME_zhujiangbianshen._SetVisable(true);
		}
		break;

	case AN_S2A_OpenUI_Achievement:
		{
			s_CUI_ID_FRAME_Achivement.SetVisable(true);
		}
		break;

	case AN_S2A_OpenUI_ChangeCountry:
		{
			s_CUI_ID_FRAME_ChangeCountry.SetVisable(true);
			s_CUI_ID_FRAME_MainMenu.SetVisable(false);
			s_CUI_ID_FRAME_MAIN.SetVisable(false);
			{
				s_CUI_ID_FRAME_BaseProperty.SetVisable(false);
				s_CUI_ID_FRAME_SeeBasePropertyBGFrame.SetVisable(false);
				s_CUI_ID_FRAME_Team.SetVisable(false);
				s_CUI_ID_FRAME_ShopCenter.SetVisable(false);
				s_CUI_ID_FRAME_Pet.SetVisable(false);
				s_CUI_ID_FRAME_SuAnimal.SetVisable(false);
				s_CUI_ID_FRAME_SeeSuAnimal.SetVisable(false);
				s_CUI_ID_FRAME_SeekPet.SetVisable(false);
			}
		}
		break;
	case AN_S2A_OpenUI_ShopCenter:
		{
			s_CUI_ID_FRAME_ShopCenter.SetVisable(true);
		}
		break;

	//case AN_S2A_OpenUI_ItemTrade:
	//	{
	//		s_CUI_ID_FRAME_ItemTrade.SetVisable(true);
	//	}
	//	break;
	//////////////////////////////////////////////////
	case AN_S2A_OpenUI_CaoYao:
		{
			s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_CaoYao );
		}
		break;
	case AN_S2A_OpenUI_ZhuBao:
		{
			s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_ZhuBao );
		}
		break;
	case AN_S2A_OpenUI_DuanZao:
		{
			s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_DuanZao );
		}
		break;
	case AN_S2A_OpenUI_ZhuJia:
		{
			s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_ZhuJia );
		}
		break;
	case AN_S2A_OpenUI_GongYi:
		{
			s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_GongYi );
		}
		break;
	case AN_S2A_OpenUI_XunMa:
		{
			s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_XunMa );
		}
		break;

	case AN_S2A_OpenUI_ShiTu:
		{
			s_CUI_ID_FRAME_ManualLevelUp.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_ShiTu2:
		{
			s_CUI_ID_FRAME_Master.SetVisable(true);
		}
	case AN_S2A_OpenUI_Title:
		{
			s_CUI_ID_FRAME_Title.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_ZhuJianUp:
		{
			s_CUI_ID_FRAME_ZhuJianUp.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_TransferStar:
		{
			if (s_CUI_ID_FRAME_Hole.IsVisable())
			{
				s_CUI_ID_FRAME_Hole.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Star.IsVisable())
			{
				s_CUI_ID_FRAME_Star.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_SHOP.IsVisable())
			{
				s_CUI_ID_FRAME_SHOP.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemUp.IsVisable())
			{
				s_CUI_ID_FRAME_GemUp.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Gem.IsVisable())
			{
				s_CUI_ID_FRAME_Gem.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_JieBang.IsVisable())
			{
				s_CUI_ID_FRAME_JieBang.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemRemove.IsVisable())
			{
				s_CUI_ID_FRAME_GemRemove.SetVisable(false);
			}

			s_CUI_ID_FRAME_TransferStar.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_MountStrengthen:
		{
			s_CUI_ID_FRAME_MountStrengthen.SetVisable(true);
		}
		break;
// 	case 99/*AN_S2A_OpenUI_TrumpFix*/:  //法宝修炼
// 		{
// 			s_CUI_ID_FRAME_TaliExercise.SetVisable(true);
// 		}
// 		break;
// 	case 100/*AN_S2A_OpenUI_TrumpReFix*/://法宝重练
// 		{
// 			s_CUI_ID_FRAME_TalismanRenovate.SetVisable(true);
// 		}
// 		break;
// 	case 101/*AN_S2A_OpenUI_TrumpFuse*/://法宝融合
// 		{
// 			s_CUI_ID_FRAME_Talisman.SetVisable(true);
// 		}
// 		break;
	case AN_S2A_OpenUI_UnBind:
		{
			if (s_CUI_ID_FRAME_Gem.IsVisable())
			{
				s_CUI_ID_FRAME_Gem.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Star.IsVisable())
			{
				s_CUI_ID_FRAME_Star.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_SHOP.IsVisable())
			{
				s_CUI_ID_FRAME_SHOP.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemUp.IsVisable())
			{
				s_CUI_ID_FRAME_GemUp.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_TransferStar.IsVisable())
			{
				s_CUI_ID_FRAME_TransferStar.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_Hole.IsVisable())
			{
				s_CUI_ID_FRAME_Hole.SetVisable(false);
			}
			if (s_CUI_ID_FRAME_GemRemove.IsVisable())
			{
				s_CUI_ID_FRAME_GemRemove.SetVisable(false);
			}
			//s_CUI_ID_FRAME_CountryResource.SetVisable(true);
			s_CUI_ID_FRAME_JieBang.SetVisable(true);
			
		}
		break;
	case AN_S2A_OpenUI_CountryBaseInfo:
		{
			//s_CUI_ID_FRAME_BaseInfo.SetVisable(true);
			s_CUI_ID_FRAME_GuildBaseInfo.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_AskPresent:
		{
			s_CUI_ID_FRAME_AskPresent.SetVisable(true);
			s_CUI_ID_FRAME_AskPresent.Reset();
			if(GetMe())
				s_CUI_ID_FRAME_AskPresent.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );

			theUiManager.SetFocus(s_CUI_ID_FRAME_AskPresent.GetEDIT_AddName());
		}
		break;
	case AN_S2A_OpenUI_MoveCountry:
		{
			s_CUI_ID_FRAME_changecountry.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_MaterialBag:
		{
			bool bChecked = true;
			s_CUI_ID_FRAME_PACK.SetVisable(true);
			s_CUI_ID_FRAME_PACK.ID_CHECKBOX_MaterialOnCheckBoxCheck(NULL, &bChecked);
		}
		break;
	case AN_S2A_OpenUI_TaskBag:
		{
			bool bChecked = true;
			s_CUI_ID_FRAME_PACK.SetVisable(true);
			s_CUI_ID_FRAME_PACK.ID_CHECKBOX_TaskOnCheckBoxCheck(NULL, &bChecked);
		}
		break;
	case AN_S2A_OpenUI_RandAttribute:
		{
			s_CUI_ID_FRAME_RandAttribute.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_PetComPose:
		{
			s_CUI_ID_FRAME_PetCompose.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_GuildChangeName:
		{
			s_CUI_ID_FRAME_GuildChangeName.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_QuestEntrust:
		{	
			s_CUI_ID_FRAME_QuestEntrust.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_Hunting:
		{
			s_CUI_ID_FRAME_Hunting.SetVisable( true );
			if( GetMe() )
			{
				s_CUI_ID_FRAME_Hunting.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
			}	
		}
		break;
	case AN_S2A_OpenUI_Card:
		{	
			s_CUI_ID_FRAME_CARD.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_MountMoveStar:
		{
			s_CUI_ID_FRAME_MountMoveStar.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_AutoAttack:
		{
			s_CUI_ID_FRAME_AutoAttackSet.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_Task:
		{
			s_CUI_ID_FRAME_Task.SetVisable(true);
		}
		break;
	case AN_S2A_OpenUI_ActivityList:
		{
			s_CUI_ID_FRAME_ActivityList.SetVisable(true);
		}
		break;
	default:
		break;
	}
	unguard;
}

void CPlayerMgr::OnMsgIntonatingOverTime(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, Msg_IntonatingOverTime );
	Msg_IntonatingOverTime *pIntonatingOverTimeMsg = (Msg_IntonatingOverTime*)pMsg;
	int nInterruptPercent = pIntonatingOverTimeMsg->cInterruptPercent;

	s_CUI_Progress.BackupPeriodTime( nInterruptPercent );
	unguard;
}

void CPlayerMgr::OnMsgChangeBagSize(Msg* pMsg)
{
	guardfunc
		CHECK_MSGLEN( pMsg, MsgChangeBagSize );
	MsgChangeBagSize* pMsgBagSize = (MsgChangeBagSize*)pMsg;
	CItemBag2* pItemBag = NULL;
	SCharItem* pCharItems = NULL;

	switch (pMsgBagSize->ucItemBagType)
	{
	case BT_NormalItemBag:
		pItemBag = &thePlayerRole.m_bag;
		pCharItems = thePlayerRole.m_charinfo.ItemBagData.stPackItems;
		pItemBag->CreateFromData( pCharItems, pMsgBagSize->ustCurSize );
		s_CUI_ID_FRAME_PACK.RefreshNormalPack();
		break;
	case BT_MaterialBag:
		pItemBag = &thePlayerRole.m_bagMaterial;
		pCharItems = thePlayerRole.m_bagMaterial.m_pPackItem;
		pItemBag->CreateFromData( pCharItems, pMsgBagSize->ustCurSize );
		s_CUI_ID_FRAME_PACK.RefreshMaterialPack();
		break;
	case BT_TaskBag:
		pItemBag = &thePlayerRole.m_bagTask;
		pCharItems = thePlayerRole.m_bagTask.m_pPackItem;
		pItemBag->CreateFromData( pCharItems, pMsgBagSize->ustCurSize );
		s_CUI_ID_FRAME_PACK.RefreshTaskPack();
		break;
	}
	unguard
}

void CPlayerMgr::OnMsgReduceItem(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}

	CHECK_MSGLEN( pMsg, MsgReqReduceItem );
	MsgReqReduceItem* pReqReduce = (MsgReqReduceItem*)pMsg;
	if (!pReqReduce)
	{
		return;
	}

	switch(pReqReduce->result)
	{
	case MsgReqReduceItem::eSuc:
		{
			ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pReqReduce->product.itembaseinfo.ustItemID );
			if( !pItemDetail )
				return;
			s_CUI_ID_FRAME_PACK.RemoveItem(BT_NormalItemBag, pReqReduce->index, 1); //lrt 先移再push物品，要不然有可能把push的物品移掉
			s_CUI_ID_FRAME_PACK.PushGoods( &pReqReduce->product );
			s_CUI_ID_FRAME_PACK.RefreshNormalPack();
			if( pReqReduce->itemBagType == BT_MaterialBag )
				s_CUI_ID_FRAME_PACK.RefreshMaterialPack();
			s_CUI_ID_FRAME_Decompound.DecompoundSuccess(pReqReduce->index);

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Success, theXmlString.GetString(eText_SplitSuccess) );
		}
		break;
	case MsgReqReduceItem::eFail:
		{
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString(eText_SplitFailed) );
		}
		break;
	default:
		break;
	}
	unguard;
}

//void CPlayerMgr::OnMsgGuildGiveExp(Msg* pMsg)
//{
//	guardfunc;
//	CHECK_MSGLEN( pMsg, MsgGuildGiveExp );
//	MsgGuildGiveExp* pGive = (MsgGuildGiveExp*)pMsg;
//	unguard;
//}
void   CPlayerMgr::OnMsgShowUnsoulBoundUI(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	CHECK_MSGLEN( pMsg, MsgCallUnSoulBound );
	MsgCallUnSoulBound* pUnSoulBound = (MsgCallUnSoulBound*)pMsg;
	if (!pUnSoulBound)
	{
		return;
	}

	unguard
}

void   CPlayerMgr::OnMsgUnsoulBound(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	CHECK_MSGLEN( pMsg, MsgUnSoulBound );
	MsgUnSoulBound *pUnSoulBound = (MsgUnSoulBound *)pMsg;
	if (!pUnSoulBound)
	{
		return;
	}
	unguard;
}

void CPlayerMgr::OnMsgSetReliveSilver(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	CHECK_MSGLEN( pMsg, MsgReliveNeedSilver );

	MsgReliveNeedSilver* pSilver = (MsgReliveNeedSilver*)pMsg;
	if (!pSilver)
	{
		return;
	}
	if (pSilver->stSilver >= 0)
	{
		s_CUI_ID_FRAME_ESCDLG.SetReliveOriginNonRmb(pSilver->stSilver);
	}
	if (pSilver->stSilverAllMpHp >= 0)
	{
		s_CUI_ID_FRAME_ESCDLG.SetReliveOriginAllHpMpRmb(pSilver->stSilverAllMpHp);
	}
	unguard;
}

void CPlayerMgr::OnMsgCostSilverReqair(Msg* pMsg)
{
}

void CPlayerMgr::OnMsgCloseItemFormIdx( Msg* pMsg )
{
	guardfunc;
	char szBuffer[512] = {0};
	MsgCloseItemFormIdx *pRemove = (MsgCloseItemFormIdx*)pMsg;
	if( pRemove->ustBagType == BT_NormalItemBag )
	{
		INT nIdx = pRemove->ustIdx;
		unsigned short ustCount = pRemove->ustCount;
		SCharItem item;
		if( thePlayerRole.m_bag.GetItem( nIdx, &item ) )
		{
			ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
			if( pItemDetail )
			{
				assert("name.h"&& 0 );
			}
		}
		//item.bCanUse = FALSE;
		SCharItem* pCharItem = thePlayerRole.m_bag.GetCharItemFromIdx( nIdx );
		if( pCharItem )
		{
			pCharItem->bCanUse = FALSE;
		}

	}
	else if( pRemove->ustBagType == BT_StorageBag )
	{
		SCharItem* pStorageData = NULL;
		pStorageData = thePlayerRole.m_stStorage.stStorageItems;
		if( pStorageData )
		{
			if( pRemove->ustIdx < 0 || STORAGE_ITEMGRID_MAX <= pRemove->ustIdx )
			{
				return;
			}
			SCharItem *StorageItem = &pStorageData[pRemove->ustIdx];
			if( StorageItem )
			{
				ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( StorageItem->itembaseinfo.ustItemID );
				if( pItemDetail )
				{
					assert("name.h"&&0);
				}
				StorageItem->bCanUse = FALSE;
			}
		}
		s_CUI_ID_FRAME_Storage.Refeash();
	}
	else if( pRemove->ustBagType == BT_CompoundBag )
	{

	}
	else if( pRemove->ustBagType == BT_EquipBag )
	{
		SCharItem* pVisual = NULL;

		if( pRemove->ustIdx < 0 || EEquipPartType_MaxEquitPart < pRemove->ustIdx )
		{
			return;
		}

		pVisual = &thePlayerRole.m_pVisual->GetVisualArray()[pRemove->ustIdx ];
		if( pVisual->itembaseinfo.ustItemID != InvalidLogicNumber )
		{
			TimeEx kTime(pVisual->itembaseinfo.n64UseTime);
			ItemDefine::SItemCommon *pItemDetail =
				GettheItemDetail().GetItemByID(pVisual->itembaseinfo.ustItemID );
			if( pItemDetail )
			{
				assert("name.h"&&0);
			}
			pVisual->bCanUse = FALSE;		
			s_CUI_ID_FRAME_BaseProperty.RefreshEquip();
		}
	}
	else 
	{
		GetErrorLog()->logString("没有找到背包类型%d", pRemove->ustBagType );
	}

	thePlayerRole.UpdateUI();
	unguard;
}
void CPlayerMgr::OnMsgLockNum(Msg* pMsg)
{
	guardfunc;
	if(!pMsg)
		return;

	MsgTellCLockNum *pLockNum = (MsgTellCLockNum *)pMsg;
	if (!pLockNum)
		return;

	if (pLockNum->header.stID == GetMyID())
	{
		thePlayerRole.SetLockNum(pLockNum->nLockNum);
		thePlayerRole.SetLockNumMax(pLockNum->nLockNumMax);

		if(thePlayerRole.GetLockNum() < 0)
		{
			thePlayerRole.SetLockNum(0);
		}

		if (pLockNum->bIsShow)
		{

		}		
	}
	unguard;
}
void   CPlayerMgr::OnMsgShowLockIntensifyUI(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	CHECK_MSGLEN( pMsg, MsgCallLockIntensifyUI );
	MsgCallLockIntensifyUI* pLockIntensify = (MsgCallLockIntensifyUI*)pMsg;
	if (!pLockIntensify)
	{
		return;
	}
	unguard
}

void CPlayerMgr::OnMsgLockIntensifyRec(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	CHECK_MSGLEN( pMsg, MsgLockIntensify );

	MsgLockIntensify* pLockIntensify = (MsgLockIntensify*)pMsg;
	if (!pLockIntensify)
	{
		return;
	}

	unguard;
}

void   CPlayerMgr::OnMsgNewCompoound(Msg* pMsg)
{
	guardfunc
		if(!pMsg)
			return;

	MsgAckCompoundNew *pAckCompound = (MsgAckCompoundNew *)pMsg;

	if (!pAckCompound||pAckCompound->recipeId == InvalidLogicNumber)
	{
		return;
	}
	RecipeConfig::SRecipe* pRule = theRecipeConfig.GetItemRuleByRuleId( pAckCompound->recipeId );

	if ( !pRule )
	{
		return;
	}	

	switch(pAckCompound->stResult)
	{
	case MsgAckCompoundNew::eResultSuccess:
		{
			// 合成成功提示			
			unsigned short ustCount = pAckCompound->item.itembaseinfo.ustItemCount;				
			ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pAckCompound->item.itembaseinfo.ustItemID );
			if( pItemDetail )
			{
				char szInfo[256];
				Common::_tstring tstrName( pItemDetail->GetItemName() );
				S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
				MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_YouGet_N_S), ustCount, tstrName.c_str() );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)&pAckCompound->item, 1, BT_NormalItemBag );
                if( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_MATERIAL || pItemDetail->ucItemType == ItemDefine::ITEMTYPE_GEM )
					thePlayerRole.m_bagMaterial.PushItem(pAckCompound->item, ustCount, NULL, NULL, "");
				else if( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_TASK )
					thePlayerRole.m_bagTask.PushItem(pAckCompound->item, ustCount, NULL, NULL, "");
				else
					thePlayerRole.m_bag.PushItem(pAckCompound->item, ustCount, NULL, NULL, "");
			}
				
			// 删除原材料
			//for (int n = 0; n < pRule->PrimaryMaterials.size(); ++n )
			//{
				//thePlayerRole.m_bagMaterial.PopItemByID( pRule->PrimaryMaterials[n].MaterialId, pRule->PrimaryMaterials[n].Count,NULL,NULL,"");
			//}
			// 删除辅助材料
			unsigned short stPopCount = 1;
			for( int n = 0 ; n < MsgAckCompoundNew::ECD_MaxAssistantItemCount ; ++ n )
			{
				if( pAckCompound->assistantItemBagIndex[n] != -1 )
				{
					thePlayerRole.m_bagMaterial.PopItem( pAckCompound->assistantItemBagIndex[n], stPopCount,NULL,NULL,"");
				}
			}

			s_CUI_ID_FRAME_PACK.RefreshNormalPack();
			s_CUI_ID_FRAME_PACK.RefreshMaterialPack();
			s_CUI_ID_FRAME_Compound.RefreshPlayerProperty();
			s_CUI_ID_FRAME_Compound.RefreshSelectRecipe();			
		}
		break;
	case MsgAckCompoundNew::eResultBagFull:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Produce_Belongs, theXmlString.GetString(eClient_AddInfo_2slk_61) );
		// 停止生产
		s_CUI_ID_FRAME_Compound.ID_BUTTON_StopOnButtonClick(NULL);
		break;
	case MsgAckCompoundNew::eResultMaterialUnconformity:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Produce_Belongs, theXmlString.GetString(eText_Material_Error_0) );
		break;
	case MsgAckCompound::eResultGemIsMaxLevel:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eText_Material_error_1) );
	case MsgAckCompoundNew::eResultNotEnoughMoney:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eExchange_NotMoney) );
		break;
	default:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eText_CompFail) );
		break;
	}
	unguard
}

void CPlayerMgr::OnChange_OwnAttribute( Msg* pMsg )
{
	guardfunc;
	MsgReqChangeOwnAttribute* own_attribute = (MsgReqChangeOwnAttribute*)pMsg;

	CPlayer* player = FindByID( own_attribute->header.stID );
	unguard;
}

void CPlayerMgr::OnChangeBattleFlag( Msg* pMsg )
{
	guardfunc;
	MsgChangeBattleFlag* flag = (MsgChangeBattleFlag*)pMsg;

	CPlayer* player = FindByID( flag->shCharID );
	if( player )
	{
		player->SetBattleFlag(flag->shFlag);
	}
	unguard;
}

void   CPlayerMgr::OnMsgCompoundRateAdd(Msg* pMsg)
{
	guardfunc;

	MsgCompoundRateAdd *pAdd = (MsgCompoundRateAdd *)pMsg;
	if (!pAdd)
	{
		return;
	}

	thePlayerRole.m_nCompoundRateAdd = pAdd->stRates;

	unguard;
}
void   CPlayerMgr::OnMsgIntensifyRateAdd(Msg* pMsg)
{
	guardfunc;

	MsgIntensifyRateAdd* pAdd = (MsgIntensifyRateAdd*)pMsg;
	if (!pAdd)
	{
		return;
	}

	thePlayerRole.m_nIntensifyRateAdd = pAdd->stRates;
	unguard;
}

void CPlayerMgr::OnMsgShopCenterOffSell(Msg* pMsg)
{
	guardfunc;
	MsgTellShopCenterOffSet *pTell = (MsgTellShopCenterOffSet *)pMsg;
	if (!pTell)
	{
		return;
	}
	thePlayerRole.m_nShopCenterOffSell = pTell->stOffSell;
	unguard;
}
//L add
//void CPlayerMgr::OnMsgAckGuildList( Msg* pMsg )
//{
//	guardfunc;
//	MsgAckGuildList* msg = (MsgAckGuildList*)pMsg;
//
//	if (msg->opType == MsgAckGuildList::EOT_Afresh)
//	{
//		thePlayerRole.clearGuild();
//	}
//
//	int nCount = 0;
//	SGuildInfoToClient* guildList = msg->guildList;
//	for ( int i = 0; i < msg->nNum; ++i )
//	{
//		if ( 0 == guildList[i].id )
//			break;
//
//		// 填充数据
//		CGuildInfo infoEx(guildList[i]);
//		thePlayerRole.addGuild(infoEx);
//		++nCount;
//	}
//
//	unguard;
//}

void CPlayerMgr::OnMsgEnterWorldS(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}

	unguard;
}

void CPlayerMgr::OnMsgEnterWorldT(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	unguard;
}

void  CPlayerMgr::OnMsgReStudentMsg(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	unguard;
}
void  CPlayerMgr::OnMsgReTeacherMsg(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	unguard;
}

void  CPlayerMgr::OnMsgReSandTRemoveMsg(Msg* pMsg)
{
	guardfunc;
	if (!pMsg)
	{
		return;
	}
	unguard;
}

// add [7/2/2008 whu]
//void CPlayerMgr::OnMsgUpdateGuildInfo(Msg* pMsg )
//{
//	guardfunc
//		MsgUpdateGuildInfo* msg = (MsgUpdateGuildInfo*)pMsg;
//
//	if ( msg->op == MsgUpdateGuildInfo::OT_ADD )
//	{
//		thePlayerRole.addGuild( CGuildInfo( msg->guildInfo ) );
//	}
//	else if ( msg->op == MsgUpdateGuildInfo::OT_UPDATE )
//	{
//		thePlayerRole.updateGuild( CGuildInfo( msg->guildInfo ) );
//	}
//	else if ( msg->op == MsgUpdateGuildInfo::OT_DELETE )
//	{
//		thePlayerRole.deleteGuild( msg->guildInfo.id );
//	}
//	s_CUI_Guild.Refeash();
//	unguard
//}

//void CPlayerMgr::OnMsgAckGuildIcon( Msg* pMsg )
//{
//	guardfunc
//		MsgAckGuildIcon* msg = (MsgAckGuildIcon*)pMsg;
//	thePlayerRole.updateGuildFlag( msg->guildId, msg->stFlag );
//	unguard
//}

//void CPlayerMgr::OnMsgAckGuildRelationChanged(Msg* pMsg )
//{
//	guardfunc
//		MsgAckGuildRelationChanged* msg = (MsgAckGuildRelationChanged*)pMsg;
//	if (msg->chResult == MsgAckGuildRelationChanged::Change_Success)
//	{
//		thePlayerRole.GetGangMgr()->updateGuildRelation( msg->guildId, msg->relation );
//		s_CUI_Guild.Refeash();
//	}
//	else
//	{
//		switch (msg->chResult)
//		{
//		case MsgAckGuildRelationChanged::Change_AlreadlyBund:       // 已经是同盟了
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eGangError_Change_AlreadlyBund), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_BundFull:           // 同盟关系已经达到最大数量
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eGangError_Change_BundFull), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_InBund:             // 目前是同盟关系,不能宣战
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eGangError_Change_InBund), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_AlreadlyRupture:    // 已经是敌对关系
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eGangError_Change_AlreadlyRupture), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_RuptureFull:        // 敌对关系已经达到最大数量
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eGangError_Change_RuptureFull), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_InRupture:          // 目前是敌对关系,不能同盟
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eGangError_Change_InRupture), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_SelfLevelLess:      // 自己帮会等级不足,无法宣战			
//			{
//				char acTemp[256] = {0};
//				MeSprintf_s( acTemp, 256, theXmlString.GetString(eGangError_Change_SelfLevelLess), GuildRuptureLevel );
//				GetShowScreenText() ->AddInfo( acTemp, Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_TargetLevelLess:    // 对方帮会等级不足,无法宣战
//			{
//				char acTemp[256] = {0};
//				MeSprintf_s( acTemp, 256, theXmlString.GetString(eGangError_Change_TargetLevelLess), GuildRuptureLevel );
//				GetShowScreenText() ->AddInfo( acTemp, Color_Config.getColor( CC_Center_WarningErrorInfo ) );				
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_GreaterTargetLevel: // 大于对方帮会的等级,不能宣战
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eGangError_Change_GreaterTargetLevel), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_NotEnoughMoney:     // 帮会没有足够的钱不能宣战
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eGangError_Change_NotEnoughMoney), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_NotEnoughGuild:     // 帮会建设度不够, 不能宣战
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eGangError_Change_NotEnoughGuild), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_NotItem:     // 没有强制解除关系的道具
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eClient_ClearRupture_NoItem), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		case MsgAckGuildRelationChanged::Change_UseItemCountLimit:     //  使用道具解除敌对关系次数限制
//			{
//				GetShowScreenText() ->AddInfo( theXmlString.GetString(eClient_ClearRupture_MaxOnce), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//			}
//			break;
//		}
//	}
//	unguard
//}

struct InviteLeagueInfo
{
	int  nSn;
	int  nInviteId;
	char cInviteType; // 邀请类型 
};

bool inviteLeagueCallback( const char bPressYesButton, void *pData )
{
	guardfunc
	if( pData )
	{
		InviteLeagueInfo* info = (InviteLeagueInfo*)pData;

		MsgReferInviteResult inRes;
		inRes.nInviteId = info->nInviteId;
		inRes.cResult = bPressYesButton;
		inRes.nSn = info->nSn;
		inRes.cInviteType = info->cInviteType;
		GettheNetworkInput().SendMsg( &inRes );
	}
	return true;
	unguard
}

bool DisadverseLeagueCallback( const char bPressYesButton, void *pData )
{
	guardfunc
	if( pData )
	{
		InviteLeagueInfo* info = (InviteLeagueInfo*)pData;

		MsgReferInviteResult inRes;
		inRes.nInviteId = info->nInviteId;
		inRes.cResult = bPressYesButton;
		inRes.nSn = info->nSn;
		inRes.cInviteType = info->cInviteType;
		GettheNetworkInput().SendMsg( &inRes );
	}
	return true;
	unguard
}


bool InviteEmbraceCallback( const char bPressYesButton, void *pData )
{
	guardfunc;
	if( pData )
	{
		InviteLeagueInfo* info = (InviteLeagueInfo*)pData;

		MsgReferInviteResult inRes;
		inRes.nInviteId = info->nInviteId;
		inRes.cResult = bPressYesButton;
		inRes.nSn = info->nSn;
		inRes.cInviteType = info->cInviteType;
		GettheNetworkInput().SendMsg( &inRes );
	}
	return true;
	unguard;
}

void CPlayerMgr::OnMsgInviteLeague(Msg* pMsg )
{
	guardfunc
		MsgInviteInfo* msg = (MsgInviteInfo*)pMsg;

	InviteLeagueInfo info;
	info.nSn = msg->nSn;
	info.nInviteId = msg->nInviteId;
	info.cInviteType = msg->cInviteType;

	char szContent[256] = {0};
	if ( MsgInviteInfo::IT_LEAGUE == msg->cInviteType )
	{   
		MeSprintf_s( szContent,sizeof(szContent)/sizeof(char) - 1, theXmlString.GetString(eInviteLeague), msg->szGuildName );
		s_CUI_ID_FRAME_MessageBox.Show( szContent, theXmlString.GetString(eInviteLeagueCaption),
			CUI_ID_FRAME_MessageBox::eTypeYesNo,
			true, inviteLeagueCallback, &info, sizeof(InviteLeagueInfo) );
	}
	else if( MsgInviteInfo::IT_EMBRACE == msg->cInviteType )
	{
		// 判断是否拒绝拥抱
		bool bInFight = false;
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			bInFight = theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting);
		bool bRefuseInFight = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseHugInFight );
		bool bRefuse = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseHug );
		if( (bInFight && bRefuseInFight) || (!bInFight && bRefuse) )
		{
			InviteEmbraceCallback(false, &info);
			return;
		}

		MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eText_Interaction_InviteEmbrace), msg->szMasterName );
		s_CUI_ID_FRAME_MessageBox.Show( szContent, theXmlString.GetString(eText_Interaction_InviteEmbrace),
			CUI_ID_FRAME_MessageBox::eTypeYesNo,
			false, InviteEmbraceCallback, &info, sizeof(InviteLeagueInfo));
	}
	else if( MsgInviteInfo::IT_DISADVERSE == msg->cInviteType )
	{
		MeSprintf_s( szContent,sizeof(szContent)/sizeof(char) - 1, theXmlString.GetString(eDisadverseLeague), msg->szGuildName );
		s_CUI_ID_FRAME_MessageBox.Show( szContent, theXmlString.GetString(eDisadverseLeagueCaption),
			CUI_ID_FRAME_MessageBox::eTypeYesNo,
			false, DisadverseLeagueCallback, &info, sizeof(InviteLeagueInfo));
	}

	unguard
}

bool AgreeBeTeacher(const char bPressYesButton,void* pData)
{
	guardfunc
		if (bPressYesButton)
		{
			return true;
		}
		else
		{

		}
		return false;
		unguard
}

bool AgreeBeStudent(char bPressYesButton,void* pData)
{
	guardfunc
		if (bPressYesButton)
		{
			return true;
		}
		else
		{
			return false;
		}

		unguard
}

void  CPlayerMgr::OnMsgReqApplySAndT(Msg* pMsg)
{
	guardfunc;
	unguard;
}

//void CPlayerMgr::OnMsgReqShowEMSMrg(Msg* pMsg)
//{
//	guardfunc;
//	if (!pMsg)
//	{
//		return;
//	}
//
//	MsgReqEmsmrg* pEMS = (MsgReqEmsmrg*)pMsg;
//	if (!pEMS)
//	{
//		return;
//	}
//	unguard;
//}

void CPlayerMgr::OnMsgUseAngell(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckUseAngell );

	MsgAckUseAngell *msg = (MsgAckUseAngell*)pMsg;
	CPlayer *pPlayer = FindByID( pMsg->header.stID );
	if( pPlayer )
	{
		PlayEffect( "Taoist/Revive/hit/1080.ini", pPlayer );
	}
	unguard;
}

void CPlayerMgr::OnMsgShowHelmet(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgShowHelmet );

	MsgShowHelmet *msg = (MsgShowHelmet*)pMsg;
	CPlayer *pPlayer = FindByID( pMsg->header.stID );
	if( pPlayer )
	{
		pPlayer->ShowHelmet(msg->showHelmet);
		pPlayer->ChangeSkeletonAndEquipAllItem(pPlayer->HasFightFlag(eFighting));
	}
	if( pPlayer == GetMe() )
	{
		thePlayerRole.m_charinfo.visual.ShowHelmet(msg->showHelmet);
		s_CUI_ID_FRAME_BaseProperty.RefreshEquip();
	}	

	unguard;
}

void CPlayerMgr::OnMsgSwitchSuit(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgAckSwitchSuit );
	MsgAckSwitchSuit *pEquip = (MsgAckSwitchSuit*)pMsg;

	CPlayer *pPlayer = FindByID( pEquip->header.stID );

	if( !pPlayer )
		return;

	pPlayer->ShowAecpratove(pEquip->nSuitIndex);
	if (pPlayer!= GetMe())
	{
		pPlayer->UpdateEquip();
	}
	return;
	/*
	if( pPlayer == GetMe() )
	{
		pPlayer->ShowAecpratove(pEquip->nSuitIndex);
		//s_CUI_ID_FRAME_BaseProperty.RefreshEquip();
		return;
	}*/

	//pPlayer->ShowAecpratove(pEquip->nSuitIndex);
	//pPlayer->ChangeSkeletonAndEquipAllItem(pPlayer->HasFightFlag(eFighting));
	if( pPlayer->GetAnim() )
		pPlayer->GetAnim()->UpdateHardItem( pPlayer->HasFightFlag(eFighting), pPlayer->GetEquip() );

	// 更新动作
	if( !(pPlayer->GetSitStatus() && !pPlayer->GetSitInterrupt()) && !pPlayer->IsInWater() )
	{
		pPlayer->SetShowWeapon(TRUE);
		if( pPlayer->IsMoving() )
			pPlayer->SwitchRunAnim();
		else
			pPlayer->SwitchIdleAnim();
	}
	else
		pPlayer->SetShowWeapon(FALSE);

	pPlayer->CalcMinimalStar();
	unguard;
}


void CPlayerMgr::OnMsgShowTimeTop(Msg* pMsg)
{
	guardfunc
	{
		CHECK_MSGLEN( pMsg, MsgShowTimeTop );
		MsgShowTimeTop* pShowTimeTop = (MsgShowTimeTop*)pMsg;
		if (pShowTimeTop && theHeroGame.GetPlayerMgr()->GetMe() )
		{
			if(pShowTimeTop->header.stID == theHeroGame.GetPlayerMgr()->GetMe()->GetID())
			{

			}
		}
	}
	unguard
}

void CPlayerMgr::OnMsgShutDownTimeTop(Msg* pMsg)
{
	guardfunc
	{
		CHECK_MSGLEN( pMsg, MsgShutDownTimeTop );
		MsgShutDownTimeTop* pShutDown = (MsgShutDownTimeTop*)pMsg;
		if (pShutDown && theHeroGame.GetPlayerMgr()->GetMe())
		{
			if(pShutDown->header.stID == theHeroGame.GetPlayerMgr()->GetMe()->GetID())
			{
				
			}
		}
	}
	unguard
}

void CPlayerMgr::OnMsgSwitchGate(Msg* pMsg)
{
	theHeroGame.ProcessSwitchGateMsg(pMsg);
}

void CPlayerMgr::OnMsgEnterWorld(Msg *pMsg)
{
	static CAckEnterWorldPackage unpacker;
	MsgAckEnterWorld* pAckEnterWorld = unpacker.UnPackageMsg(*static_cast<MsgAckEnterWorldPack*>(pMsg));
	if( GetMe() )
		GetMe()->SetID(pAckEnterWorld->header.stID);
}

void CPlayerMgr::OnMsgEndGetCharacter(Msg *pMsg)
{
	MsgEndAckChar* pEndAckCharMsg = (MsgEndAckChar*)pMsg;
	CUI_ID_FRAME_LOGIN::g_bEndGetCharacter = FALSE;

	if( !GetMe() )
		return;
	std::map< GameObjectId, CPlayer* >::iterator it = m_mapPlayers.find(GetMe()->GetID());
	if (it != m_mapPlayers.end())
	{
		CPlayer* pPlayer = GetMe();
		m_mapPlayers.erase(it);
		pPlayer->SetID(pEndAckCharMsg->header.stID);
		m_mapPlayers.insert(std::map< GameObjectId, CPlayer* >::value_type(pPlayer->GetID(), pPlayer));
	}

	MsgEnterWorld msgEnterWorld;
	msgEnterWorld.stWhichSlot = sPlayerSlot;
	msgEnterWorld.dwCharacterID = g_nCharacterDBID;
	msgEnterWorld.dwEnterWorldTime = HQ_TimeGetTime();
	msgEnterWorld.dwAccountId = m_dwAccountID;
	msgEnterWorld.nSwitchStageType = 1;
	GettheNetworkInput().SendMsg(&msgEnterWorld);
}

std::string CPlayerMgr::ParseText(const std::string& str)
{
	std::string text = str;
	std::string fmt("@PlayerName");
	size_t p = 0;
	while ((p = text.find(fmt, p)) != std::string::npos)
	{
		text.replace(p, fmt.length(), thePlayerRole.GetName());
		p += strlen(thePlayerRole.GetName());
	}

	p = 0;
	fmt = "Var";
	while ((p = text.find("@", p)) != std::string::npos)
	{
		size_t end = text.find(fmt, p + 1);
		if (end != std::string::npos)
		{
			int number = atoi(text.substr(p + 1, end - p - 1).c_str());
			CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById(number);
			std::stringstream sstr;
			if (pInfo)
			{
				sstr << (short)pInfo->chState;
			}
			else
			{
				sstr << '0';
			}
			text.replace(p, end + fmt.length() - p, sstr.str());
			p = end + 3;
		}
		else
			p += 1;
	}

	return text;
}

void CPlayerMgr::RetriveRelationQuestToNpc( GameObjectId npcId, int &nQuestCount, int * questStates, void * pstData , int nWordCount /*= 0*/ )
{
	ControlList::S_List* pstList = (ControlList::S_List*)pstData;
	const int nMaxListItem = 64;
	ControlList::S_List stItemDone[nMaxListItem];
	ControlList::S_List stItemActive[nMaxListItem];
	ControlList::S_List stItemNew[nMaxListItem];
	int nItemDoneCount = 0;
	int nItemNewCount = 0;
	int nItemActiveCount = 0;
	{
		CPlayer* pNpc = FindByID( npcId );
		if( !pNpc || !pNpc->IsNpc() )
		{
			return;
		}


		std::vector<SQuest*> vectorQuest;
		std::vector<void*>			vtNpcRelateState;
		// 得到此npc已知任务描述
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pNpc->GetNpcID());
		GetNpcQuests( pInfo, &vectorQuest, &vtNpcRelateState );
		std::string strInfo;

		for( int i = 0; i < vtNpcRelateState.size(); i++ )
		{
			CPlayerRole::QuestInfo *pNpcQuestInfo = (CPlayerRole::QuestInfo*)vtNpcRelateState[i];
			if ( !pNpcQuestInfo )
				continue;
			SQuest* pQuest = vectorQuest[i];
			if( !pQuest )
			{
				continue;
			}
			/*
			 * Author: 2012-10-8 17:10:04 liaojie
			 * Desc:   增加任务国家条件限制
			 */
			/*CPlayer* me = GetMe();*/
			if (/*!me || */(pQuest->Country!=0 && pQuest->Country!=thePlayerRole.GetCountry()/*me->GetCountry()*/))
			{
				continue;
			}
			strInfo = pQuest->GetQuestName();
            //strInfo = theXmlString.GetString( eText_QuestType_1 + pQuest->chQuestType ) + strInfo;
			char szWord[256] = {0};
			MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_Select)/*"[%s]%d级 "*/,theXmlString.GetString( eText_QuestType_1 + pQuest->chQuestType ),pQuest->HintLevelMin);
			strInfo =  szWord + strInfo;
			DWORD col;
			col = GetQuestRankColor(pQuest);
			// 		// 得到角色任务状态
			assert(!theQuestManager.IsQuestDone( pNpcQuestInfo->chState ) );

			// 如果角色任务状态中没有发现此任务记录,或者任务还没做过
			if( theQuestManager.IsQuestNotGain( pNpcQuestInfo->chState ) )
			{
				assert (thePlayerRole.TaskNeedRemind(pQuest));
				{
					strInfo +=  theXmlString.GetString(eText_Quest_None);//  " (可接取)";
					stItemNew[nItemNewCount++].SetData( strInfo.c_str(), pQuest->Id,
						NULL, col );
					if( nItemNewCount >= nMaxListItem )
						break;
				}
			}
			else
			{
				if ( pNpcQuestInfo->bDone || pNpcQuestInfo->chState == QuestManager::eQuestEntrustDone)
				{
					strInfo += theXmlString.GetString(eText_Quest_Done);//" (已完成)";
					stItemDone[nItemDoneCount++].SetData( strInfo.c_str(), pQuest->Id,
						NULL, col );
					if( nItemDoneCount >= nMaxListItem )
						break;
				}
				else
				{
					strInfo += theXmlString.GetString(eText_Quest_Act);//" (未完成)";
					stItemActive[nItemActiveCount++].SetData( strInfo.c_str(), pQuest->Id,
						NULL, col );
					if( nItemActiveCount >= nMaxListItem )
						break;
				}
			}
		}
	}
	nQuestCount = nItemDoneCount + nItemNewCount + nItemActiveCount;

	int nIndex = nWordCount;
	for ( int n=0; n<nItemDoneCount; n++ )
	{
		questStates[nIndex] = QuestManager::eQuestDone;
		pstList[nIndex++] = stItemDone[n];
		GetErrorLog()->logString("可完成任务:%d", stItemDone[n].m_nID );
	}
	for ( int n=0; n<nItemActiveCount; n++ )
	{
		questStates[nIndex] = QuestManager::eQuestGaining;
		pstList[nIndex++] = stItemActive[n];
		GetErrorLog()->logString("新任务:%d", stItemActive[n].m_nID );
	}
	for ( int n=0; n<nItemNewCount; n++ )
	{
		questStates[nIndex] = QuestManager::eQuestNotGain;
		pstList[nIndex++] = stItemNew[n];
		GetErrorLog()->logString("新任务:%d", stItemNew[n].m_nID );
	}
}


void CPlayerMgr::OnMsgAckScript(Msg *pMsg)
{
		MsgAckScript* pNpcChat = (MsgAckScript*)pMsg;
#ifdef _DEBUG
	char szWord[256] = {0};
	sprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"UIType:%d",pNpcChat->byType);
	::OutputDebugString(szWord);
#endif

	if(s_CUI_NpcTaskDialogBox.SendBuffMsg())
		return;


// 	if (pNpcChat->szString[0] == '@')
// 	{
// 		int stringId = atoi(&pNpcChat->szString[1]);
// 		strcpy(pNpcChat->szString,theXmlString.GetString(stringId));
// 	}
	char* szTemp = theXmlString.ParseAtString(pNpcChat->szString);
	// 分析NPC对话表情头像
	std::string strDialog = "";
	short shExpHeadId = ProcessExpHead( (const char*)szTemp, strDialog );
	szTemp = (char*)strDialog.c_str();

	//s_CUI_ID_FRAME_NpcChatDialogBox.SetChatNpc(pNpcChat->stNpcId);
	s_CUI_NpcTaskDialogBox.SetNpc(pNpcChat->stNpcId);
	std::string title;
	CPlayer* pNpc = FindByID( pNpcChat->stNpcId );
	if (pNpc)
		title = pNpc->GetName();

	s_CUI_ID_FRAME_Task.SetVisable(false);

	switch( pNpcChat->byType ) 
	{
	case MsgAckScript::eNpcDialog:
		{
			std::string text = ParseText(szTemp);

			switch (pNpcChat->dlgType)
			{
			case MsgAckScript::eNDT_Description:
				{
					s_CUI_NpcTaskDialogBox.SetNpc(pNpcChat->stNpcId);
					s_CUI_NpcTaskDialogBox.SetExpHeadId(shExpHeadId);
					s_CUI_NpcTaskDialogBox.ShowChatDialog(text.c_str(),title.c_str(),true);
				}
				break;
			case MsgAckScript::eNDT_Close:
				{
					s_CUI_NpcTaskDialogBox.SetNpc(pNpcChat->stNpcId);
					s_CUI_NpcTaskDialogBox.SetExpHeadId(shExpHeadId);
					s_CUI_NpcTaskDialogBox.ShowChatDialog(text.c_str(),title.c_str(),false);
				}
				break;
			default:
				{
					s_CUI_NpcTaskDialogBox.SetExpHeadId(shExpHeadId);
					s_CUI_NpcTaskDialogBox.Show(pNpcChat->dlgType,
						text.c_str(), pNpcChat->iValue,
						title );
				}
			}
		}
		break;
	case MsgAckScript::eNpcMainDialog:
		{
			std::string text = ParseText(szTemp);
			switch (pNpcChat->dlgType)
			{
			case MsgAckScript::eNDT_Description:
				{

				}
				break;
			case MsgAckScript::eNDT_Close:
				{

				}
				break;
			default:
				{
					s_CUI_NpcTaskDialogBox.SetNeedCancel(false);
					s_CUI_NpcTaskDialogBox.SetVisable(false);
					s_CUI_NpcTaskDialogBox.SetNeedCancel(true);
					s_CUI_ID_FRAME_Gut.SetVisable(true);
					s_CUI_ID_FRAME_Gut.SetNpc(pNpcChat->stNpcId);
					s_CUI_ID_FRAME_Gut.Show(pNpcChat->dlgType,text.c_str(),pNpcChat->iValue,title);
					break;
				}
			}
		}
		break;
	case MsgAckScript::eAskQuestion:
		{
			WordParser words;
			if( words.Parse( szTemp ) == 0 )
			{
				assert( false && "npc choise count is 0" );
			}
			else
			{
				int nWordCount = words.GetWordCount();
				if( nWordCount > 1 )
				{
					const int nMaxListItem = 64;
					ControlList::S_List pstList[nMaxListItem];

					int nQuestCount = 0;

					int questStates[nMaxListItem];
					if(0 == strcmp(theXmlString.GetString(eTitleTypeText_Task),words.GetWord(nWordCount - 1)))
					{
						RetriveRelationQuestToNpc(pNpcChat->stNpcId, nQuestCount, questStates, pstList, 0);
						nWordCount -= 1;
					}
					nWordCount -= 1;//去掉0
					for ( int n=0; n< nWordCount ; n++ )
					{
						if( n + nQuestCount >= nMaxListItem )
							break;

						std::string parse = words.GetWord(n + 1);
						int nId = 0;
						s_CUI_NpcTaskDialogBox.ParseExpressText(parse,nId);
						questStates[n + nQuestCount] = nId;

						pstList[n + nQuestCount].SetData( parse.c_str()/*words.GetWord(n+1)*/, n );
					}

					if(nWordCount + nQuestCount == 1&&pNpc)
					{
						const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pNpc->GetNpcID());
						if( pInfo && 
							(pInfo->_nType == eNT_Restore   //药品
							||pInfo->_nType == eNT_Weapon   //武器
							||pInfo->_nType == eNT_Jewelry  //首饰
							||pInfo->_nType == eNT_Dress    //服装
							||pInfo->_nType == eNT_Feudal   //官府任务
							||pInfo->_nType == eNT_MingWang //名望Npc
							||pInfo->_nType == eNT_ZaHuo)   //杂货
							)
						{
							s_CUI_NpcTaskDialogBox.SetUIType(CUI_NpcTaskDialogBox::UI_Select);
							s_CUI_NpcTaskDialogBox.ScriptSellectCallbackFun(0,(void*)&pstList[0]);
							return;
						}
					}

					int nNum = 0;
					if(nWordCount + nQuestCount < nMaxListItem)
					{
					    questStates[nWordCount + nQuestCount] = 2104;
						pstList[nWordCount + nQuestCount].SetData(theXmlString.GetString(eText_QUESTEND),-1);
						nNum = 1;
					}
					//s_CUI_ID_FRAME_NpcChatDialogBox.SetVisable( false );

					std::string text = ParseText(words.GetWord(0));

					s_CUI_NpcTaskDialogBox.SetNpc(pNpcChat->stNpcId);
					s_CUI_NpcTaskDialogBox.SetExpHeadId(shExpHeadId);
					s_CUI_NpcTaskDialogBox.Show( text.c_str(), pstList, nWordCount + nQuestCount + nNum,
						title.c_str(),
						true, CUI_NpcTaskDialogBox::ScriptSellectCallbackFun, nWordCount + nQuestCount + nNum,questStates);
				}
			}
		}
		break;
	case MsgAckScript::eCloseDlg:
		{
			//s_CUI_ID_FRAME_NpcChatDialogBox.SetVisable( false );
			s_CUI_NpcTaskDialogBox.CloseDialog();
		}
		break;
	default:
		assert(false);
		break;
	}
}

void CPlayerMgr::OnMsgAckResult( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgAckResult );
	MsgAckResult* pResult = ( MsgAckResult* )pMsg;
	switch( pResult->result )
	{
	case ER_QuestFail://任务相关脚本失败，这里刷新下，防止挂起
		{
			s_CUI_NpcTaskDialogBox.RefreshTask( pResult->value );
		}
		break;
	default:
		break;
	}
}

void CPlayerMgr::OnMsgScriptEnd( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgScriptEnd );
	/*MsgScriptEnd* pScript = ( MsgScriptEnd* )pMsg;*/
	s_CUI_NpcTaskDialogBox.SetSending( false );
}

void CPlayerMgr::OnMsgUpdateGuideAck( Msg* pMsg )
{
	MsgUpdateGuideAck* msgAck = (MsgUpdateGuideAck*)pMsg;
	//...
}

void CPlayerMgr::OnMsgGuildNoticeAck(Msg *pMsg)
{
	if (pMsg != NULL)
	{
		MsgGuildNoticeAck *m_msg = (MsgGuildNoticeAck*)pMsg;
		if (m_msg != NULL)
		{
			switch(m_msg->uchResult)
			{
			case MsgGuildNoticeAck::ECD_Success:
				ShowGuildInfo(theXmlString.GetString(eText_Guild_LevelGuild_ChangeNotice));
				break;
			case MsgGuildNoticeAck::ECD_NotHaveRight:
				break;
			default:
				break;
			}
		}
	}
}
void CPlayerMgr::OnMsgGuildNotice( Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellGuildNotice);
	MsgTellGuildNotice* pMsg = (MsgTellGuildNotice*)pMsg_;
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	pGuild->SetGuildNotice(pMsg->szNotice);

	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
	//ShowGuildInfo(theXmlString.GetString(eText_Guild_LevelGuild_ChangeNotice));
}

void CPlayerMgr::OnMsgTellGuildAim(Msg* pMsg)
{
	if(NULL == pMsg)
		return;

	CHECK_MSGLEN(pMsg, MsgTellGuildAim);
	MsgTellGuildAim *pMyMessage = (MsgTellGuildAim *)pMsg;
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	pGuild->SetGuildAim(pMyMessage->szAim);

	s_CUI_ID_FRAME_GuildApply.SetNeedRefresh(true);
	s_CUI_ID_FRAME_AddGuildGeneralBattle.UpdateAllGuild();
	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	ShowGuildInfo(theXmlString.GetString(eText_Guild_TellCreed));
}

void CPlayerMgr::OnMsgChangeGuildAimAck(Msg* pMsg)
{
	if(NULL == pMsg)
		return;

	CHECK_MSGLEN(pMsg, MsgChangeGuildAimAck);
	MsgChangeGuildAimAck *pMyMessage = (MsgChangeGuildAimAck *)pMsg;
	switch(pMyMessage->uchResult)
	{
	case MsgChangeGuildAimAck::ECD_Success:
		break;
	case MsgChangeGuildAimAck::ECD_InCD:
		ShowGuildInfo(theXmlString.GetString(eText_Guild_Creed_Cd_Failed));
		break;
	}
}


 //创建家族notice
void CPlayerMgr::OnMsgGuildCreateNotice(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgGuildCreateFamilyAck);
	MsgGuildCreateFamilyAck* pMsg = (MsgGuildCreateFamilyAck*)pMsg_;
	
	char szText[256] = "0";
	switch (pMsg->uchResult)
	{
	case MsgGuildCreateFamilyAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_CreateFamilySucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildCreateFamilyAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_HaveNoRight));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildCreateFamilyAck::ECD_FamilyFull:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_FamilyFull));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildCreateFamilyAck::ECD_SaveFamily:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_HaveSameFamily));
			ShowGuildInfo(szText);
		}
		break;
	default:
		break;
	} 
}

//踢人出帮notice
void CPlayerMgr::OnMsgRemoveGuildMemberNotice(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgKickGuildAck);
	MsgKickGuildAck* pMsg = (MsgKickGuildAck*)pMsg_;

	char szText[256] = "0";
	switch (pMsg->uchResult)
	{
	case MsgKickGuildAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_KickOutGuildSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgKickGuildAck::ECD_NotHaveGuild:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_HaveNoGuild));
			ShowGuildInfo(szText);
		}
		break;
	case MsgKickGuildAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_KickGuildMemberFaild));
			ShowGuildInfo(szText);
		}
		break;
	default:
		break;
	}
}
//转让职位
void CPlayerMgr::OnMsgGuildTransferAck(Msg* pMsg)
{
	if (pMsg != NULL)
	{
		MsgGuildTransferAck *m_Msg = (MsgGuildTransferAck*)pMsg;
		if (m_Msg != NULL)
		{
			char szText[256] = {0};
			switch(m_Msg->uchResult)
			{
			case MsgGuildTransferAck::ECD_Success:
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_TransferSuccess));
				ShowGuildInfo(szText);
// 				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, 
// 									theXmlString.GetString(eText_Guild_TransferSuccess));
				break;
			case MsgGuildTransferAck::ECD_NotHaveRight:// 你没有权限转让职位
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_TransferNotHaveRight));
				ShowGuildInfo(szText);
				//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs,
									//theXmlString.GetString(eText_Guild_TransferNotHaveRight));
				break;
			case MsgGuildTransferAck::ECD_NotViceMaster:// 帮主只能转让给副帮主，对方不是副帮主	
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_TransferNotViceMaster));
				ShowGuildInfo(szText);
// 				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, 
// 									theXmlString.GetString(eText_Guild_TransferNotViceMaster));
				break;
			case MsgGuildTransferAck::ECD_LevelLess:// 对方等级不足，无法转让
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_TransferLevelLess));
				ShowGuildInfo(szText);
				//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, 
				//					theXmlString.GetString(eText_Guild_TransferLevelLess));
				break;
			case MsgGuildTransferAck::ECD_NotGuildMember:// 对方不是本帮成员
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_TransferNotGuildMember));
				ShowGuildInfo(szText);
				//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, 
				//					theXmlString.GetString(eText_Guild_TransferNotGuildMember));
				break;
			case MsgGuildTransferAck::ECD_NotSameFamily:// 转让族长时，对方必须是同一家族成员
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_TransferNotSameFamily));
				ShowGuildInfo(szText);
				//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, 
				//					theXmlString.GetString(eText_Guild_TransferNotSameFamily));
				break;
			case MsgGuildTransferAck::ECD_IsKing:// 自己是国王， 不能转让帮主
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_TransferIsKing));
				ShowGuildInfo(szText);
				//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, 
				//					theXmlString.GetString(eText_Guild_TransferIsKing));
				break;
			case MsgGuildTransferAck::ECD_GameBattleCD:
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_GameBattleCD));
				ShowGuildInfo(szText);
				break;
			case MsgGuildTransferAck::ECD_GameBattleExites:
				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_GameBattleExites));
				ShowGuildInfo(szText);
				break;
			}
		}
	}
}
//职位任免notice
void CPlayerMgr::OnMsgGuildAssignPositionNotice(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}
	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
	CHECK_MSGLEN( pMsg_, MsgGuildAssignPositionAck);
	MsgGuildAssignPositionAck* pMsg = (MsgGuildAssignPositionAck*)pMsg_;

	char szText[256] = "0";
	switch (pMsg->uchResult)
	{
	case MsgGuildAssignPositionAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_AssignSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildAssignPositionAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_HaveNoRightAssign));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildAssignPositionAck::ECD_SamePosition:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_SamePosition));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildAssignPositionAck::ECD_NotHaveFamily:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_HaveNoFamily));
			ShowGuildInfo(szText);
		}
		break;
	default:
		break;
	}
}

// 服务器回应修改家族
void CPlayerMgr::OnMsgFamilyChangeNotice(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	char szText[256] = "0";
	CHECK_MSGLEN( pMsg_, MsgGuildFamilyChangeAck);
	MsgGuildFamilyChangeAck* pMsg = (MsgGuildFamilyChangeAck*)pMsg_;

	switch (pMsg->uchResult)
	{
	case MsgGuildFamilyChangeAck::ECD_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_ChangeSucceed));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildFamilyChangeAck::ECD_NotHaveRight:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_HaveNoRightChange));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildFamilyChangeAck::ECD_SaveFamily:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_HaveSameFamily));
			ShowGuildInfo(szText);
		}
		break;
	case MsgGuildFamilyChangeAck::ECD_EmptyFamily:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1,theXmlString.GetString(eText_Guild_CanNotDeleteOrChangeEmptyFamily));
			ShowGuildInfo(szText);
		}
		break;
	default:
		break;
	}
}

void CPlayerMgr::OnMsgGetMount(Msg* pMsg)
{
	CHECK_MSGLEN( pMsg, MsgGetMount);
	MsgGetMount* pGetMount = (MsgGetMount*)pMsg;
	switch (pGetMount->usResult)
	{
	case MsgGetMount::ER_Success:
		{
			thePlayerRole.AddMount(pGetMount->mount);
			if (!s_CUI_ID_FRAME_Pet.IsVisable())
			{
				s_CUI_ID_FRAME_MainMenu.SetNeedSpark(true, CUI_ID_FRAME_MainMenu::ekey_pet);
			}
			s_CUI_ID_FRAME_Pet.Refresh(true);
            s_CUI_ID_FRAME_PetList.Refresh();

			ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( pGetMount->mount.baseInfo.id );
			if (pDrome)
			{
				char szInfo[256];
				MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_YouGet_MOUNT), 1, pDrome->GetName() );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)&pGetMount->mount, 1, BT_MountBag );
			}
		}
		break;
	case MsgGetMount::ER_MountFull:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBag_NotSpace ));
		break;
	default:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBag_NotSpace ));
		break;
	}
}

void CPlayerMgr::OnMsgMountStrengthenAck(Msg* pMsg)
{
	CHECK_MSGLEN( pMsg, MsgMountStrengthenAck);
	MsgMountStrengthenAck* pMountStrengthen = (MsgMountStrengthenAck*)pMsg;

	int nMountIndex = s_CUI_ID_FRAME_Pet.GetMountIndexByGuid( pMountStrengthen->mount.baseInfo.guid );
	if (nMountIndex != -1)
	{
		thePlayerRole.GetMountByIndex( nMountIndex ) = pMountStrengthen->mount;
		s_CUI_ID_FRAME_Pet.Refresh();
	}

	if (pMountStrengthen->result == MsgMountStrengthenAck::eR_Success)
	{	
		if(thePlayerRole.GetMountByIndex( nMountIndex ).baseInfo.level != 0 && pMountStrengthen->IsMoveLevel)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_MountMoveLevel_Success));
		}
		else if(!pMountStrengthen->IsMoveLevel)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Success, theXmlString.GetString( eText_MountStrengthen_Success ) );
		}
		s_CUI_ID_FRAME_MountStrengthen.SetEffectStatus(CUI_ID_FRAME_MountStrengthen::EffectStatus_Success);
		s_CUI_ID_FRAME_MountStrengthen.SetBeginTime(timeGetTime());
	}
	else
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString( eText_MountStrengthen_Fail ) );
		s_CUI_ID_FRAME_MountStrengthen.SetEffectStatus(CUI_ID_FRAME_MountStrengthen::EffectStatus_Fail);
		s_CUI_ID_FRAME_MountStrengthen.SetBeginTime(timeGetTime());
	}

	s_CUI_ID_FRAME_MountStrengthen.UpdataAll();
	s_CUI_ID_FRAME_MountStrengthen.SetAckMsg(true);
}

void CPlayerMgr::OnMsgUpdateMount(Msg* pMsg)
{
	CHECK_MSGLEN( pMsg, MsgUpdateMount);
	MsgUpdateMount* pUpdateMount = (MsgUpdateMount*)pMsg;

	if (GetMe() && pUpdateMount->header.stID != GetMe()->GetID())
	{
		s_CUI_ID_FRAME_SeekPet.SetVisable(true);
		s_CUI_ID_FRAME_SeekPet.SetMount(pUpdateMount->mount);
	}
	else 
	{
		int nMountIndex = s_CUI_ID_FRAME_Pet.GetMountIndexByGuid( pUpdateMount->mount.baseInfo.guid );
		if( nMountIndex != -1 )
		{
			thePlayerRole.GetMountByIndex( nMountIndex ) = pUpdateMount->mount;

			if (thePlayerRole.GetActivedMountIndex() == nMountIndex && thePlayerRole.GetActivedMount())
			{
				thePlayerRole.RemoveMountSkill(*thePlayerRole.GetActivedMount());
				thePlayerRole.AddMountSkill(thePlayerRole.GetMountByIndex(nMountIndex));

				s_CUI_ID_FRAME_MAIN.RefeashHotKey();
				s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
			}
			if (!s_CUI_ID_FRAME_Pet.IsVisable())
			{
				s_CUI_ID_FRAME_MainMenu.SetNeedSpark(true, CUI_ID_FRAME_MainMenu::ekey_pet);
			}
			s_CUI_ID_FRAME_Pet.Refresh();
			s_CUI_ID_FRAME_PetMain.SetVisable(true);
		}
	}
}

void CPlayerMgr::OnMsgTellCurrentTitle( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg , MsgTellCurrentTitle );
	MsgTellCurrentTitle* pTellTileMsg = (MsgTellCurrentTitle*)pMsg;
	if( pTellTileMsg->nError == MsgTellCurrentTitle::TellSuccess )//更换当前称号
	{
		CPlayer* pPlayer = FindByID( pTellTileMsg->header.stID );

// 		if(pPlayer == GetMe())
// 		{
// 			if(pTellTileMsg->nTitleID > 0)
// 			{
// 				//发送隐藏心情的消息
// 				s_CUI_ID_FRAME_Editor.SendMoodMsg(false);
// 				theHeroGame.GetPlayerMgr()->GetMe()->ShowSignature(false);
// 			}
// 		}	

		if( pPlayer )
		{
			pPlayer->SetTitleInfoById( pTellTileMsg->nTitleID,pTellTileMsg->szTitleTargetName );
		}

		if(pPlayer == GetMe())
		{
			if(s_CUI_ID_FRAME_Editor.IsVisable())
			{
				s_CUI_ID_FRAME_Editor.RefreshHeadInfo();
				s_CUI_ID_FRAME_Editor.RefreshButtonState();
			}
		}

	}
	else if( pTellTileMsg->nError == MsgTellCurrentTitle::TellNoThisTile) // 没有此称号
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eTitle_TileNotExist ) );
	}

}

void CPlayerMgr::OnMsgTellTitleList( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgTellTitleList );
	MsgTellTitleList* pTellTitleList = (MsgTellTitleList*)pMsg;
}

void CPlayerMgr::OnMsgAddTitleAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgAddTitleAck );
	MsgAddTitleAck* pAck = (MsgAddTitleAck*)pMsg;
	switch( pAck->nError )
	{
	case MsgAddTitleAck::Add_Success:
		{
			TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID( pAck->nTitleID );
			if( pTitle )
			{
                char szBuff[255] = {0};
				TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID( pAck->nTitleID );
				if(pTitle->GetType() == TitleConfig::Title_Marriage)  // 已经修改为类型判断 [12/22/2010 zhangjiayi](//这里硬编码，非常不好,10000表示婚姻ID)
                {
                    const char* pszMarryName = thePlayerRole.GetMarryerName();
                    if(pszMarryName != NULL)
                    {
                        char szTitle[256] = {0};        
                        if(thePlayerRole.GetSex() == 0)
                            MeSprintf_s(szTitle,sizeof(szTitle)/sizeof(char) - 1,pTitle->GetName(),pszMarryName,theXmlString.GetString(eText_MarryHusband) );
                        else if(thePlayerRole.GetSex() == 1)
                            MeSprintf_s(szTitle,sizeof(szTitle)/sizeof(char) - 1,pTitle->GetName(),pszMarryName,theXmlString.GetString(eText_MarryWife));
                        else
                            assert(0&&"性别出错");

                        MeSprintf_s(szBuff,sizeof(szBuff)/sizeof(char) - 1,theXmlString.GetString( eTitle_AddSuccess ),szTitle);
                    }
                }
				else if( pTitle->GetType() == TitleConfig::Title_Student )
				{
					const char* pcTeacherName = thePlayerRole.GetNameByDBID( thePlayerRole.GetTeacherDBID() );
					if( pcTeacherName )
					{
						char szTitle[256] = {0};
						MeSprintf_s( szTitle, sizeof( szTitle ) / sizeof( char ) - 1, pTitle->GetName(), pcTeacherName );
						MeSprintf_s( szBuff, sizeof( szBuff ) / sizeof( char ) - 1, theXmlString.GetString( eTitle_AddSuccess ), szTitle );
					}
				}
                else
				    MeSprintf_s( szBuff, 255, theXmlString.GetString( eTitle_AddSuccess ), pTitle->GetName() );

				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, szBuff );
			}			
			thePlayerRole.AddNewTitleId( pAck->nTitleID,pAck->n64AcquireTime,pAck->nActiveTime );
		}
		break;
	case MsgAddTitleAck::Add_AlreadyExist:
		break;
	case MsgAddTitleAck::Add_ErrorID:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Title_Belongs, theXmlString.GetString( eTitle_ErrorId ) );
		break;
	case MsgAddTitleAck::Add_NoThisTitle:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Title_Belongs, theXmlString.GetString( eTitle_TileNotExist ) );
		break;
	case MsgAddTitleAck::Add_TitleFull:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Title_Belongs, theXmlString.GetString( eTitle_Full ) );
		break;
	case MsgAddTitleAck::Add_Unknow:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Title_Belongs, theXmlString.GetString( eTitle_UnknownError ) );
		break;
	}

	s_CUI_ID_FRAME_Title.NeedRefresh();
}

void CPlayerMgr::OnMsgRemoveTitleAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgRemoveTitleAck );
	MsgRemoveTitleAck* pRemoveAck = (MsgRemoveTitleAck*)pMsg;
	switch( pRemoveAck->nError )
	{
	case MsgRemoveTitleAck::Remove_Success:
		{
			thePlayerRole.RemoveTitleId( pRemoveAck->nTitleID );			
		}
		break;
	case MsgRemoveTitleAck::Remove_NoThisTitle:
		break;
	case MsgRemoveTitleAck::Remove_ErrorID:		
		break;
	case MsgRemoveTitleAck::Remove_Unknow:	
		break;
	}
	s_CUI_ID_FRAME_Title.NeedRefresh();
}

void CPlayerMgr::OnMsgTellReputation( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgTellReputation );
	MsgTellReputation* pRepu = (MsgTellReputation*)pMsg;
	if( !GetMe() )
		return;

	GetMe()->SetReputation( pRepu->dwReputation );
	s_CUI_ID_FRAME_Experience.Refresh();
}

extern std::vector<int> g_vecPendingShowInfo;

void InitBrightContrast()
{
	CWorldTile* pTile = CURRENTTILE;
	if( !pTile )
		return;
	D3DXVECTOR3 vC( pTile->GetContrastOffsetR(), pTile->GetContrastOffsetG(), pTile->GetContrastOffsetB() );
	PostProcessManager::instance().SetBrightNContrast( pTile->GetBrightnessOffset(), vC );
}

// 初始化地图信息中用到的字 [10/29/2010 zhangjiayi]
void InitAllZoneName()
{
	DWORD dwTime = HQ_TimeGetTime();
	CWorldTile* pTile = CURRENTTILE;
	if( !pTile )
		return;

	CResMgr* resMgr = pTile->GetCResMgr();
	if( !resMgr )
		return;

	if( !FontSystem::IsUseNewFont() )
		return;

	std::vector< CWorldRes* >& zoneList = resMgr->GetZoneResList();
	std::vector< CWorldRes* >::iterator it = zoneList.begin();
	for( ; it != zoneList.end(); ++ it )
	{
		if( (*it) && (*it)->GetName() )
		{
			std::wstring wideStr = Common::_tstring::toWideString((*it)->GetName());
			if( !wideStr.empty() )
			{
				FontSystem::GetTextWidth( GetShowScreenText()->GetFontIndex( CShowScreenText::eRiseTextEnd ), 
				wideStr, 0, wideStr.length(), false ); 
				FontSystem::GetTextWidth( GetShowScreenText()->GetFontIndex( CShowScreenText::eInfoBigTileText ), 
					wideStr, 0, wideStr.length(), false ); 				
			}
		}
	}
	dwTime = HQ_TimeGetTime() - dwTime;
	char acCost[256] = {0};
	sprintf_s( acCost, 256, "\n InitZoneNames Cost: %d", dwTime );
	OutputDebugStringA( acCost );
	

	// 取头顶文字index
	RTTFont* pFont = Font3DManager::Instance()->CreateFont3D(RTTFont::RTT_TEX_WIDTH,
		gCfg.m_szNameFontName, gCfg.m_nNameFontSize, false, gCfg.m_isNameFontBold);

	if( !pFont )
		return;

	// 初始化npc,怪文字
	std::vector<NpcCoordInfo>& npcMap = NpcCoord::getInstance()->getNpcVec();	
	for( int i=0; i<npcMap.size(); ++i )
	{
		NpcCoordInfo& ThisInfo = npcMap[i];
		if(ThisInfo._bPFPossible && ThisInfo._mapId == pTile->GetMapId() )
		{
			std::wstring wideStr = ( ThisInfo._szName.c_str());
			std::wstring wideStr2 = Common::_tstring::toWideString( ThisInfo._title.c_str());
			if( !wideStr.empty() )
			{
				FontSystem::GetTextWidth( pFont->GetFontIndex(), 
					wideStr, 0, wideStr.length(), false ); 		
			}
			if( !wideStr2.empty() )
			{
				FontSystem::GetTextWidth( pFont->GetFontIndex(), 
					wideStr2, 0, wideStr2.length(), false ); 		
			}
		}
	}
	Font3DManager::Instance()->DestroyFont3D( pFont );
}

void DisplaySafeOrDangerRegionName(const char* szText)
{
	if (!szText)
	{
		return;
	}

	std::string strSafe = "安全区域";
	std::string strDanger = "危险区域";
	RECT rectSafe = {427, 674, 540, 695};
	RECT rectDanger = {426, 703, 540, 725};
	if (strcmp(strSafe.c_str(), szText) == 0)
	{
		CScreenInfoManager::Instance()->ShowSafeOrDangerName(&rectSafe);
		return;
	}

	if (strcmp(strDanger.c_str(), szText) == 0)
	{
		CScreenInfoManager::Instance()->ShowSafeOrDangerName(&rectDanger);
		return;
	}
}

void CPlayerMgr::OnMsgMapInfoReady( Msg* pMsg )
{
	// 第一次进enterworld
	if( strcmp( s_CUI_ID_FRAME_MessageBox.GetTextCaption(), theXmlString.GetString( eText_NowLoadingGameData ) ) == 0 /*&& s_CUI_ID_FRAME_MessageBox.IsVisable()*/ )
		
	{			
		
		// 财产保护倒计时
		if( CWealthProtect::Instance().IsFirstEnterMap() )
		{
			CWealthProtect::Instance().InitProtectEndingTime(HQ_TimeGetTime());
			//第一次登陆弹出活动UI
			if (thePlayerRole.GetLevel()>=10)
			{
				s_CUI_ID_FRAME_ActivityList.SetVisable(true);
			}

			CWealthProtect::Instance().SetFirstEnterMap(false);
		}
	}

	InitBrightContrast();
	InitAllZoneName();

	MsgClientTeamInfo teamInfo;
	if(thePlayerRole.GetTeamInfo().size() != 0)
	{
		for (int i = 0; i < thePlayerRole.GetTeamInfo().size(); ++i)
		{
			teamInfo.AddTeamMemberID(thePlayerRole.GetTeamInfo()[i].nID);
		}
	}
	GettheNetworkInput().SendMsg( &teamInfo );


	UiDrawer::StartFillFullScreen( 10, false, 0, 255 );
	s_CUI_ID_FRAME_MessageBox.closeAll(false);
    LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_INFO, "MessageBox.CloseAll" );

	g_bIsShowSceneAndPlayer = TRUE;

	// 更新任务状态
	g_bCanUpdateQuest = TRUE;
	thePlayerRole.UpdateActiveQuestState( TRUE, TRUE );

	// 清除购回列表
	s_CUI_ID_FRAME_SHOP.ClearBuyBackPack();

    // 地图名显示
	CWorldTile* pTile = CURRENTTILE;
	if( !pTile )
	{
		g_vecPendingShowInfo.clear();
		return;
	}	


	// 更新天气系统所需要信息
	WeatherEventManager::Instance()->UpdateWorldData( pTile->GetMapId() );
	WeatherEventManager::Instance()->StartWeatherTime( pTile->GetMapId(), 0 );

	if( GetMe() )
	{
		float fx, fy;
		GetMe()->GetPos( &fx, &fy, NULL );
		CWorldChunk* chunk = pTile->GetChunkFromPos( fx, fy );
		if (chunk != NULL && chunk->GetZoneId() != RES_INVALID_ID)
		{
			CResMgr* resMgr = pTile->GetCResMgr();
			const char* pZoneName = resMgr->GetZoneRes( chunk->GetZoneId() )->GetName();

			RECT rect = {0, 0, 0, 0};
			CNdlZoneRes *zoneRes = resMgr->GetZoneRes(chunk->GetZoneId());
			if (zoneRes == NULL)
				return;

			const RECT *pRect = zoneRes->GetFontRect();
			if (pRect != NULL)
			{
				rect.left = pRect->left;
				rect.top = pRect->top;
				rect.right = pRect->right;
				rect.bottom = pRect->bottom;
			}

            // 区域名
			if( pZoneName )
			{
				if (rect.left != 0 && rect.right != 0 && rect.top != 0 && rect.bottom != 0)
				{
					CScreenInfoManager::Instance()->ShowRegionName(&rect);
				}
				else
				{
					CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Map_Name, pZoneName);
				}
			}		
		}	
    }

    // 地图名
    CScreenInfoManager::Instance()->ShowMapNameById( pTile->GetMapId() );

    // 危险区域、安全区域
    if( pTile->GetMapTip() && pTile->GetMapTip()[0] != '\0' )
    {
        //CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_AreaName, pTile->GetMapTip() );
		DisplaySafeOrDangerRegionName(pTile->GetMapTip());
    }

	s_CUI_ID_FRAME_Task.LoadTrackInfo();

	if ( !pTile->GetPointSoundPlay())
	{
		pTile->SetPointSoundPlay(true);

		float fSoundVolume = GSound.m_fSoundVal;
		GSound.SetVolume(0.f);
		CResMgr* pResMgr = pTile->GetCResMgr();
		for (int i = 0; i < pResMgr->GetSoundPointCount(); ++i)
		{
			CSoundPointRes* pSoundRes = pResMgr->SoundPoint(i);
			string strFullPath(CWorld::GetAppDataCharDir());
			strFullPath += '\\';
			strFullPath += pSoundRes->GetMuiscPath();
			GSound.PlaySound((char*)strFullPath.c_str(),true,(D3DXVECTOR3*)(&pSoundRes->GetSoundPoint()),pSoundRes->GetMinDistance(),pSoundRes->GetMaxDistance());
		}
		CPlayer* pMe = GetMe();
		if (pMe)
		{
			GSound.UpdatePos( pMe->GetPos(), pMe->GetCurDir() );
		}
		GSound.SetVolume(fSoundVolume);
	}

	// 切地图后清除战斗状态和吟唱状态
	if( GetMe() )
	{
		if( GetMe()->GetName() )
		{
			char str[MAX_PATH] = {0};
			sprintf(str,"%s 切地图，清除战斗状态\n",GetMe()->GetName());
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, string(str));
		}

		thePlayerRole.SetFighting( false );
		GetMe()->ClearFightFlag(eFighting, TRUE);
		GetMe()->SetIntonating(0);
		// GetMe()->SetExPower( 0 );
		// 清除复活后等待被传送去地狱的状态
		if( thePlayerRole.IsReliveAndWaitingToHell() )
			thePlayerRole.SetIsReliveAndWaitingToHell(FALSE);
	}

	if (s_CUI_ID_FRAME_FindRoad.IsMultMove())
	{
		s_CUI_ID_FRAME_FindRoad.ProcessMultMoving();
	}
	else
		CrossMapPF::Instance()->UpdateAfterTileLoad();

	// 授权新学会技能提示
	s_CUI_ID_FRAME_NewSkillMain.EnableAddSkill(true);

	// 请求商城数据
	/*MsgGetShopCenter getShopCenter;
	GettheNetworkInput().SendMsg( &getShopCenter );*/

	if( g_vecPendingShowInfo.size() > 0 )
	{
		for(int i=0; i<g_vecPendingShowInfo.size(); ++i)
		{
			const char* strWarning = theXmlString.GetString(g_vecPendingShowInfo[i]);
			if( strWarning != Empty_String_Value )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_City, strWarning );
			}
		}
		g_vecPendingShowInfo.clear();
	}

	//如果是摆摊状态，摆摊模型看不到，需要重新加载
	if( GetMe()->IsMorph() && GetMe()->IsOpenPrivateShop() )
	{
		GetMe()->MorphMonster(GetMe()->GetMorphModelID(), true);
	}

	s_CUI_ID_FRAME_TutorialBox.SetVisable(true);
	//if ( !thePlayerRole.IsFinishedIntroduce(INTRO_MOVEPLAYER) )
	//{
	//	//s_CUI_ID_FRAME_TutorialBox.SetTutorialMovePlayer();
	//	s_CUI_ID_FRAME_TutorialBox.StartTutorial();
	//}
	if ( !thePlayerRole.IsFinishedIntroduce(INTRO_MOVEPLAYER_UP) )
	{
		s_CUI_ID_FRAME_TutorialBox.StartTutorial();
	}
	else if ( !thePlayerRole.IsFinishedIntroduce(INTRO_MOVEPLAYER_DOWN) )
	{
		s_CUI_ID_FRAME_TutorialBox.SetTutorialMovePlayerDown();
	}
	else if ( !thePlayerRole.IsFinishedIntroduce(INTRO_MOVEPLAYER_LEFT) )
	{
		s_CUI_ID_FRAME_TutorialBox.SetTutorialMovePlayerLeft();
	}
	else if ( !thePlayerRole.IsFinishedIntroduce(INTRO_MOVEPLAYER_RIGHT) )
	{
		s_CUI_ID_FRAME_TutorialBox.SetTutorialMovePlayerRight();
	}
	else if ( !thePlayerRole.IsFinishedIntroduce(INTRO_LMOUSEOPT) )
	{
		s_CUI_ID_FRAME_TutorialBox.SetTutorialLMouseOpt();
	}
	else if ( !thePlayerRole.IsFinishedIntroduce(INTRO_RMOUSEOPT) )
	{
		s_CUI_ID_FRAME_TutorialBox.SetTutorialRMouseOpt();
	}
	else if ( !thePlayerRole.IsFinishedIntroduce(INTRO_SPACEOPT) )
	{
		s_CUI_ID_FRAME_TutorialBox.SetTutorialSapceOpt();
	}
	else
	{
		s_CUI_ID_FRAME_TutorialBox.SetVisable(false);
	}
}

//告诉客户端该包裹的权限情况，队伍分配时，如果有品质以上物品，所有人都能看包裹，但只有一人能捡品质以下物品
void CPlayerMgr::OnMsgTellPackageAccess( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgTellPackageAccess );
	MsgTellPackageAccess* pPkgAccess = (MsgTellPackageAccess*)pMsg;
	if( !GetMe() )
		return;

	CPlayer* pPkgPlayer = FindByID(pPkgAccess->nItemPackageID);
	if( !pPkgPlayer )
	{
		char msg[MAX_PATH] = {0};
		sprintf(msg, "包裹不存在 ID:%d\n", pPkgAccess->nItemPackageID);
		OutputDebugString(msg);
		return;
	}

	// 判断能否拾取
	BOOL bCanAccess = FALSE;
	if( pPkgAccess->nCount == 0 )	// 对所有人可见
	{
		// 包裹延时显示时间已过，增加包裹拾取特效
		if( pPkgPlayer->IsItemDropDelayOver() && pPkgPlayer->m_nCollectionEffectID == -1 )
		{
			pPkgPlayer->m_nCollectionEffectID = PlayEffect("common\\QuestItem.ini",pPkgPlayer);
		}
		pPkgPlayer->m_bCanPick = true;
		bCanAccess = TRUE;
	}
	else
		for( int iPlayer = 0; iPlayer < pPkgAccess->nCount; ++iPlayer )
		{
			uint32 iPlayerDBID = pPkgAccess->dwPickPlayerID[iPlayer];
			if( thePlayerRole.IsRole(iPlayerDBID) )
			{
				// 包裹延时显示时间已过，增加包裹拾取特效
				if( pPkgPlayer->IsItemDropDelayOver() && pPkgPlayer->m_nCollectionEffectID == -1 )
				{
					pPkgPlayer->m_nCollectionEffectID = PlayEffect("common\\QuestItem.ini",pPkgPlayer);
				}
				pPkgPlayer->m_bCanPick = true;
				bCanAccess = TRUE;
				break;
			}
		}

		if( !bCanAccess )
		{
			// 无法拾取，去掉拾取特效
			if(pPkgPlayer->m_nCollectionEffectID != -1 )
			{
				IEffect* pEffect = GetEffectMgr()->GetEffect( pPkgPlayer->m_nCollectionEffectID );
				if( pEffect )
				{
					pEffect->SetDead();
				}
				pPkgPlayer->m_nCollectionEffectID = -1;
			}
			pPkgPlayer->m_bCanPick = false;
		}

		// 队伍分配，队长和某队员同时打开包裹（如果包裹有有需要掷骰子的物品，队长也能浏览包裹），队长或队员关闭包裹UI时，另一个收到消息后
		if( s_CUI_ID_FRAME_PickUp.IsVisable() && s_CUI_ID_FRAME_PickUp.IsSamePackage(pPkgAccess->nItemPackageID) )
		{
			MsgPackageItemAccessReq kUpdateItemAccess;
			kUpdateItemAccess.nItemPackageID = pPkgAccess->nItemPackageID;
			GettheNetworkInput().SendMsg( &kUpdateItemAccess );
		}
}

//服务器回应的包裹中的物品列表
void CPlayerMgr::OnMsgPackageViewAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgPackageViewAck );
	MsgPackageViewAck* pPkgView = (MsgPackageViewAck*)pMsg;
	if( !GetMe() )
		return;

	CPlayer* pPkgPlayer = FindByID(pPkgView->nItemPackageID);
	if( !pPkgPlayer )
	{
		char msg[MAX_PATH] = {0};
		sprintf(msg, "包裹不存在 ID:%d\n", pPkgView->nItemPackageID);
		OutputDebugString(msg);
		return;
	}

	// 弹出UI显示物品
	bool bCanLoot = false;
	s_CUI_ID_FRAME_PickUp.Reset();
	for(int iItem = 0; iItem < pPkgView->nItemCount; ++iItem)
	{
		if( pPkgView->xPackItem[iItem].chPickLevel & eIPL_View )
		{
			s_CUI_ID_FRAME_PickUp.AddItem(pPkgView->xPackItem[iItem].xItem, pPkgView->xPackItem[iItem].chPickLevel |/*&*/ eIPL_Pick);
			bCanLoot = true;
		}
	}


	/*
	 *	Author 2012-9-28 zhuxincong
	 *	DESC: 多增加了一个判断，是为了当包裹满的时候 给玩家提示包裹满来，无法自动拾取了。s_CUI_ID_FRAME_PickUp 一直显示着无法关掉。
	 */
	int index = -1;
	if( s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag) )
		index = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag)->GetNullItem();
	if (index == -1 || index >= thePlayerRole.m_bag.GetNowBagSize())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook, theXmlString.GetString( eText_NormalPackFull ) );
			s_CUI_ID_FRAME_PickUp.SetVisable(false);
		return;
	}


	if( bCanLoot)
	{
		s_CUI_ID_FRAME_PickUp.SetVisable(true);
		s_CUI_ID_FRAME_PickUp.SetPackageInfo(pPkgView->nItemPackageID, pPkgView->bSendViewEnd);
		// 是否全部拾取
		if( g_bPackagePickAll )
		{
			s_CUI_ID_FRAME_PickUp.PickAll();
			g_bPackagePickAll = FALSE;
		}
	}
}

//发送给客户端拾取了某个物品,包裹列表中删除该物品，只发给拾取人自己，其他人接收不到
void CPlayerMgr::OnMsgPickPackageItemAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgPickPackageItemAck );
	MsgPickPackageItemAck* pPickItemAck = (MsgPickPackageItemAck*)pMsg;
	if( !GetMe() )
		return;

	// 打开的包裹与服务器发的包裹相同
	if( s_CUI_ID_FRAME_PickUp.IsVisable() && s_CUI_ID_FRAME_PickUp.IsSamePackage(pPickItemAck->nItemPackageID) )
	{
		CPlayer* pPkgPlayer = FindByID(pPickItemAck->nItemPackageID);
		//如果包裹不存在，则关闭包裹界面
		if( !pPkgPlayer )
		{
			s_CUI_ID_FRAME_PickUp.SetVisable(false);
		}
		//从包裹界面删除该物品
		else if( pPickItemAck->nResult == MsgPickPackageItemAck::Result_Success || pPickItemAck->nResult == MsgPickPackageItemAck::Result_AlreadyPick )
		{
			s_CUI_ID_FRAME_PickUp.DeleteItem(pPickItemAck->nItemID);
		}
	}
	// 输出拾取信息
	switch( pPickItemAck->nResult )
	{
	case MsgPickPackageItemAck::Result_AlreadyPick:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PickUp, theXmlString.GetString( eText_PackagePickUp_NotExist ) );
		break;
	case MsgPickPackageItemAck::Result_NoPurview:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PickUp, theXmlString.GetString( eText_PackagePickUp_CannotPick ) );
		break;
	default:
		break;
	}
}

//服务器发送给客户端,要求客户端玩丢筛子游戏
void CPlayerMgr::OnMsgPackageItemBoultReq( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgPackageItemBoultReq );


	if(thePlayerRole.m_TeamData.size() == 1 )
	{
		TeamInfo* pInfo = &(thePlayerRole.m_TeamData[0]);

		if ( strcmp(pInfo->szName.c_str() , theHeroGame.GetPlayerMgr()->GetMe()->GetName()) == 0 )
		{
			return;  //lyh++ ,当队伍分配的时候，如果有队伍 ，并且队伍里只有自己，则不需要提示装备需求。
		}       
	}
	MsgPackageItemBoultReq* pItemBoultReq = (MsgPackageItemBoultReq*)pMsg;

	if( pItemBoultReq->nCount )
	{
		for(int iItem=0; iItem < pItemBoultReq->nCount; ++iItem)
		{
			DemandItemFrameManage.AddDemandItem(pItemBoultReq->nItemPackageID, pItemBoultReq->xItem[iItem], pItemBoultReq->nTimeOut );
		}
	}
}

//筛子的点数 (如果筛子点数相同的两个最大,谁先丢出来,谁得到物品)
void CPlayerMgr::OnMsgPackageItemBoultNumber( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgPackageItemBoultNumber );
	MsgPackageItemBoultNumber* pBoultResult = (MsgPackageItemBoultNumber*)pMsg;

	SCharItem *pItem = DemandItemFrameManage.GetItemInResultList(pBoultResult->nItemID);
	if( !pItem )
	{
		char msg[MAX_PATH] = {0};
		sprintf(msg, "包裹不存在 ID:%d\n", pBoultResult->nItemID);
		OutputDebugString(msg);
		return;
	}

	ItemDefine::SItemCommon *pItemCommon =GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
	if( !pItemCommon )
	{
		char msg[MAX_PATH] = {0};
		sprintf(msg, "Item表里找不到物品 ID:%d\n", pItem->itembaseinfo.ustItemID);
		OutputDebugString(msg);
		return;
	}

	if( pBoultResult->dwHoldPlayerID <= -1 )
	{
		// 所有玩家都放弃
		char szBuf[MAX_PATH] = {0};
		Common::_tstring tstrName( pItemCommon->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
		MeSprintf_s( szBuf,sizeof(szBuf)/sizeof(char) - 1 ,theXmlString.GetString(eText_TeamBoultResult_AllAbandon), tstrName.c_str() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szBuf, 0, (char*)pItem, 1, BT_NormalItemBag );

		// 如果包裹界面打开着
		if( s_CUI_ID_FRAME_PickUp.IsVisable() && s_CUI_ID_FRAME_PickUp.IsSamePackage(pBoultResult->nItemPackageID) )
		{
			s_CUI_ID_FRAME_PickUp.UpdateItemCanLoot(pBoultResult->nItemID, true);
		}
	}
	else if( pBoultResult->nCount > 0 )
	{
		// 玩家掷点数
		for(int iPlayer=0; iPlayer < pBoultResult->nCount; ++iPlayer)
		{
			TeamInfo* pTeamInfo = thePlayerRole.GetTeamInfo(pBoultResult->xPackageItemBoult[iPlayer].dwPlayerID);
			if( !pTeamInfo )
			{
				// 玩家已离队，找不到名字
				char msg[MAX_PATH] = {0};
				sprintf(msg, "玩家已离队 ID:%d\n", pBoultResult->xPackageItemBoult[iPlayer].dwPlayerID);
				OutputDebugString(msg);
			}
			else
			{
				char szBuf[MAX_PATH] = {0};
				if( pBoultResult->xPackageItemBoult[iPlayer].nBoultNumber == 0 )
				{
					// 自己放弃
					if( thePlayerRole.IsRole(pBoultResult->xPackageItemBoult[iPlayer].dwPlayerID) )
					{
						Common::_tstring tstrName( pItemCommon->GetItemName() );
						S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
						MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1,theXmlString.GetString(eText_TeamBoultResult_YouAbandon), tstrName.c_str());
					}
					else    // 玩家放弃
					{
						Common::_tstring tstrName( pItemCommon->GetItemName() );
						S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
						MeSprintf_s( szBuf,sizeof(szBuf)/sizeof(char) - 1, theXmlString.GetString(eText_TeamBoultResult_Abandon), pTeamInfo->szName.c_str(), tstrName.c_str());
					}
				}
				else
				{
					// 掷点数
					Common::_tstring tstrName( pItemCommon->GetItemName() );
					S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
					MeSprintf_s( szBuf,sizeof(szBuf)/sizeof(char) - 1, theXmlString.GetString(eText_TeamBoultResult_Choose), pTeamInfo->szName.c_str(), tstrName.c_str(), pBoultResult->xPackageItemBoult[iPlayer].nBoultNumber );
				}
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szBuf, 0, (char*)pItem, 1, BT_NormalItemBag );

			}
		}
		// 玩家获得物品
		TeamInfo* pTeamInfo = thePlayerRole.GetTeamInfo(pBoultResult->dwHoldPlayerID);
		if( !pTeamInfo )
		{
			// 玩家已离队，找不到名字
			char msg[MAX_PATH] = {0};
			sprintf(msg, "玩家已离队 ID:%d\n", pBoultResult->dwHoldPlayerID);
			OutputDebugString(msg);
		}
		else
		{
			char szBuf1[MAX_PATH]={0};
			Common::_tstring tstrName( pItemCommon->GetItemName() );
			S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
			MeSprintf_s( szBuf1, sizeof(szBuf1)/sizeof(char) - 1,theXmlString.GetString(eText_TeamBoultResult_Acquire), pTeamInfo->szName.c_str(), tstrName.c_str() );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szBuf1, 0, (char*)pItem, 1, BT_NormalItemBag );
		}

		// 如果包裹界面打开着
		if( s_CUI_ID_FRAME_PickUp.IsVisable() && s_CUI_ID_FRAME_PickUp.IsSamePackage(pBoultResult->nItemPackageID) )
		{
			// 如果物品已塞进玩家包裹，则删除
			if( pBoultResult->bRemove )
			{
				s_CUI_ID_FRAME_PickUp.DeleteItem(pBoultResult->nItemID);
			}
			else    // 背包已满
			{
				s_CUI_ID_FRAME_PickUp.UpdateItemCanLoot(pBoultResult->nItemID, true);
			}
		}
	}
	DemandItemFrameManage.RemoveItemInResultList(pBoultResult->nItemID);
}

//发消息给队长,需要他来分配物品归属
void CPlayerMgr::OnMsgPackageItemNeedToAssign( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgPackageItemNeedToAssign );
	MsgPackageItemNeedToAssign* pLeadAssignInfo = (MsgPackageItemNeedToAssign*)pMsg;

	/*if( s_CUI_ID_FRAME_PickUp.IsVisable() && s_CUI_ID_FRAME_PickUp.IsSamePackage(pLeadAssignInfo->nItemPackageID) )
	{*/
		s_CUI_ID_FRAME_PickUp.SetAssignItemListMemberList(pLeadAssignInfo->nCount, pLeadAssignInfo->nItemIDArray,
			pLeadAssignInfo->nPlayerCount, pLeadAssignInfo->dwPlayerID);
	/*}*/
}

//服务器回应给客户端其他队员获取物品,做显示用
void CPlayerMgr::OnMsgPackageItemAssignAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgPackageItemAssignAck );
	MsgPackageItemAssignAck* pLeadAssignItem = (MsgPackageItemAssignAck*)pMsg;

	if( pLeadAssignItem->chAssignResult == MsgPackageItemAssignAck::Result_Success )
	{
		// 分配成功
		ItemDefine::SItemCommon *pItemCommon =GettheItemDetail().GetItemByID(pLeadAssignItem->xItem.itembaseinfo.ustItemID);
		if( !pItemCommon )
		{
			char msg[MAX_PATH] = {0};
			sprintf(msg, "Item表里找不到物品 ID:%d\n", pLeadAssignItem->xItem.itembaseinfo.ustItemID);
			OutputDebugString(msg);
			return;
		}

		char szBuf[MAX_PATH] = {0};
		Common::_tstring tstrName( pItemCommon->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
		MeSprintf_s( szBuf, MAX_PATH, theXmlString.GetString(eText_PackagePickUp_AssignItem), tstrName.c_str(), pLeadAssignItem->szPlayerName);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szBuf, 0, (char*)&pLeadAssignItem->xItem, 1, BT_NormalItemBag );

		// 如果包裹打开，则刷新包裹界面
		if( s_CUI_ID_FRAME_PickUp.IsVisable() && s_CUI_ID_FRAME_PickUp.IsSamePackage(pLeadAssignItem->nItemPackageID) )
		{
			// 如果物品已塞进玩家包裹，则删除
			if( pLeadAssignItem->bRemove )
			{
				s_CUI_ID_FRAME_PickUp.DeleteItem(pLeadAssignItem->xItem.itembaseinfo.nOnlyInt);
			}
			else    // 背包已满
			{
				// 刷新物品权限
				s_CUI_ID_FRAME_PickUp.UpdateItemCanLoot(pLeadAssignItem->xItem.itembaseinfo.nOnlyInt, true);
			}
		}
	}
	else
	{
		// 分配失败
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_Arrange, theXmlString.GetString( eText_PackagePickUp_AssignFailed ) );
		// 从分配表里删除玩家
	}
}

//发送给新加入的队员当前队伍的分配模式
void CPlayerMgr::OnMsgTellTeamAssignInfo( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgTellTeamAssignInfo );
	MsgTellTeamAssignInfo* pAssignInfo = (MsgTellTeamAssignInfo*)pMsg;

	thePlayerRole.SetAssignMode(pAssignInfo->chAssignMode);
	thePlayerRole.SetItemRollLevel(pAssignInfo->chAssignItemLevel);
	// 品质字串
	char szItemLevel[MAX_PATH] = {0};
	switch( pAssignInfo->chAssignItemLevel )
	{
	case eIL_Choiceness:
		MeSprintf_s( szItemLevel, MAX_PATH, "%s", theXmlString.GetString(ePreItemText_LiangPin) );
		break;
	case eIL_Polish:
		MeSprintf_s( szItemLevel, MAX_PATH, "%s", theXmlString.GetString(ePreItemText_JingPin) );
		break;
	case eIL_Nonsuch:
		MeSprintf_s( szItemLevel, MAX_PATH, "%s", theXmlString.GetString(ePreItemText_JiPin) );
		break;
	}

	// 需求品质:%s
	char szItemRollLevel[MAX_PATH] = {0};
	MeSprintf_s( szItemRollLevel, MAX_PATH, theXmlString.GetString(eText_Team_ItemRollLevel), szItemLevel);

	// 拼凑分配模式+需求品质字串
	char szBuf[MAX_PATH] = {0};
	switch( pAssignInfo->chAssignMode )
	{
	case AssignMode_FreeMode:
		MeSprintf_s( szBuf, MAX_PATH, "%s\n%s", theXmlString.GetString(eText_Client_show_assignMode_Freedom), szItemRollLevel );
		break;
	case AssignMode_Team:
		MeSprintf_s( szBuf, MAX_PATH, "%s\n%s", theXmlString.GetString(eText_Client_show_assignMode_Team), szItemRollLevel );
		break;
	case AssignMode_Random:
		MeSprintf_s( szBuf, MAX_PATH, "%s\n%s", theXmlString.GetString(eText_Client_show_assignMode_Random), szItemRollLevel );
		break;
	case AssignMode_Assign:
		MeSprintf_s( szBuf, MAX_PATH, "%s\n%s", theXmlString.GetString(eText_Client_show_assignMode_Assign), szItemRollLevel );
		break;
	}
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szBuf );				
	// 更新UI
	if( s_CUI_ID_FRAME_SelfRBMenu.IsVisable() )
	{
		s_CUI_ID_FRAME_SelfRBMenu.UpdateAssignMode();
		s_CUI_ID_FRAME_SelfRBMenu.UpdateSelectQuality();
	}

	if ( s_CUI_ID_FRAME_Team.IsVisable() )
	{
		s_CUI_ID_FRAME_Team.RefreshAssignMode();
		s_CUI_ID_FRAME_Team.RefreshRollMode();
	}
}

//服务器回应队伍物品分配等级给客户端
void CPlayerMgr::OnMsgChangeAssignItemLevelAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgChangeAssignItemLevelAck );
	MsgChangeAssignItemLevelAck* pItemLevelMsg = (MsgChangeAssignItemLevelAck*)pMsg;

	thePlayerRole.SetItemRollLevel(pItemLevelMsg->chAssignItemLevel);
	// 品质字串
	char szItemLevel[MAX_PATH] = {0};
	switch( pItemLevelMsg->chAssignItemLevel )
	{
	case eIL_Choiceness:
		MeSprintf_s( szItemLevel, MAX_PATH, "%s", theXmlString.GetString(ePreItemText_LiangPin) );
		break;
	case eIL_Polish:
		MeSprintf_s( szItemLevel, MAX_PATH, "%s", theXmlString.GetString(ePreItemText_JingPin) );
		break;
	case eIL_Nonsuch:
		MeSprintf_s( szItemLevel, MAX_PATH, "%s", theXmlString.GetString(ePreItemText_JiPin) );
		break;
	}

	// 需求品质:%s
	char szItemRollLevel[MAX_PATH] = {0};
	MeSprintf_s( szItemRollLevel, MAX_PATH, theXmlString.GetString(eText_Team_ItemRollLevel), szItemLevel);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szItemRollLevel );				

	// 更新UI
	if( s_CUI_ID_FRAME_SelfRBMenu.IsVisable() )
	{
		s_CUI_ID_FRAME_SelfRBMenu.UpdateSelectQuality();
	}
}

// 回应玩家请求包裹物品拾取权限
void CPlayerMgr::OnMsgPackageitemAccessAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgPackageitemAccessAck );
	MsgPackageitemAccessAck* pUpdateItemAccess = (MsgPackageitemAccessAck*)pMsg;

	// 如果包裹界面打开，从界面里删除物品
	if( s_CUI_ID_FRAME_PickUp.IsVisable() && s_CUI_ID_FRAME_PickUp.IsSamePackage(pUpdateItemAccess->nItemPackageID) )
	{
		for( int iItem =0; iItem < pUpdateItemAccess->nCount; ++iItem )
		{
			s_CUI_ID_FRAME_PickUp.UpdateItemCanLoot(pUpdateItemAccess->xItemInfo[iItem].nItemID, pUpdateItemAccess->xItemInfo[iItem].chPickLevel & eIPL_Pick);
		}
	}
}

// 通知队伍中的有效成员,某某某玩家拾取了某物品, (只有品质以上物品才广播)
void CPlayerMgr::OnMsgTellPickPackageItem( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgTellPickPackageItem );
	MsgTellPickPackageItem* pUpdateItemAccess = (MsgTellPickPackageItem*)pMsg;

	ItemDefine::SItemCommon *pItemCommon =GettheItemDetail().GetItemByID(pUpdateItemAccess->xItem.itembaseinfo.ustItemID);
	if( !pItemCommon )
	{
		char msg[MAX_PATH] = {0};
		sprintf(msg, "Item表里找不到物品 ID:%d\n", pUpdateItemAccess->xItem.itembaseinfo.ustItemID);
		OutputDebugString(msg);
		return;
	}

	char szBuf1[MAX_PATH]={0};
	Common::_tstring tstrName( pItemCommon->GetItemName() );
	S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
	MeSprintf_s( szBuf1,sizeof(szBuf1)/sizeof(char) - 1, theXmlString.GetString(eText_TeamBoultResult_Acquire), pUpdateItemAccess->szPlayerName, tstrName.c_str() );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szBuf1, 0, (char*)&pUpdateItemAccess->xItem, 1, BT_NormalItemBag );
}

void CPlayerMgr::OnMsgStorageMoneyAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgStorageMoneyAck );
	MsgStorageMoneyAck* pStorageAck = (MsgStorageMoneyAck*)pMsg;

	thePlayerRole.SetStorageMoney(pStorageAck->dwStorageMoney);
	thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pStorageAck->dwPackageMoney );
	if( s_CUI_ID_FRAME_PACK.IsVisable() )
		s_CUI_ID_FRAME_PACK.RefreshMoney();
	if( s_CUI_ID_FRAME_Storage.IsVisable() )
		s_CUI_ID_FRAME_Storage.UpdateMoney();
}

void CPlayerMgr::OnMsgAddRecipeAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgAddRecipeAck );
	MsgAddRecipeAck* pAckMsg = ( MsgAddRecipeAck* )pMsg;
	if( pAckMsg->chResult == MsgAddRecipeAck::Result_Success )
	{
		// 添加到playerrole
		for( int i = 0 ; i < MAX_RECIPE_COUNT; ++i )
		{
			if( thePlayerRole.GetCharInfo2().otherdataclient.recipes[i] != 0 )
				continue;
			thePlayerRole.GetCharInfo2().otherdataclient.recipes[i] = pAckMsg->ustRecipeID;
			break;
		}
	}
	else if( pAckMsg->chResult == MsgAddRecipeAck::Result_AlreadyExist )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Produce_Belongs, theXmlString.GetString( eText_RecipeAlreadyExist ) );
	}
	else if( pAckMsg->chResult == MsgAddRecipeAck::Result_Full )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Produce_Belongs, theXmlString.GetString( eText_RecipeFull ) );
	}
	else if( pAckMsg->chResult == MsgAddRecipeAck::Result_NoThisRecipe )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Produce_Belongs, theXmlString.GetString( eText_RecipeNoThis ) );
	}
	else if( pAckMsg->chResult == MsgAddRecipeAck::Result_Unknow )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Produce_Belongs, theXmlString.GetString( eText_RecipeUnknown ) );
	}	
	s_CUI_ID_FRAME_Compound.UpdateCompoundItems();
}

void CPlayerMgr::OnMsgTellTeamInfo( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgTellTeamInfo );
	MsgTellTeamInfo* pInfoMsg = (MsgTellTeamInfo*)pMsg;
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( pInfoMsg->charId );
	if( !pPlayer )
		return;
	pPlayer->SetTeamId( pInfoMsg->teamId );
	pPlayer->SetTeamPosition( pInfoMsg->teamPosition );
// 	s_CUI_ID_FRAME_TRACK.RefreshPlayerList();

}

void CPlayerMgr::OnMsgChangeProtectLockTimeAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgChangeProtectLockTimeAck );
	MsgChangeProtectLockTimeAck* pChangeProtectMsg = (MsgChangeProtectLockTimeAck*)pMsg;

	if( pChangeProtectMsg->chResult == MsgChangeProtectLockTimeAck::Result_Success )
	{
		s_CUI_ID_FRAME_Protect.SetChangeTimeSuccess();
		CWealthProtect::Instance().SetProtectTime(s_CUI_ID_FRAME_Protect.GetProtectTime());
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Wealth_Protect, theXmlString.GetString( eText_ProtectTime_ChangeSucc ) );
	}
	else
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Wealth_Protect, theXmlString.GetString(eText_ProtectTime_ChangeFailed) );
	}
}

void CPlayerMgr::OnMsgTellTeamMemberList( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgTellTeamMemberList );
	MsgTellTeamMemberList* pTeamMemberList = (MsgTellTeamMemberList*)pMsg;
	std::vector<TeamInfo> teamInfo = thePlayerRole.GetTeamInfo();
	// 添加
	for( int i = 0 ; i < pTeamMemberList->nCount ; ++ i )
	{
		bool bFound = false;
		for( int j = 0 ; j < teamInfo.size() ; ++ j )
		{
			if( pTeamMemberList->xMemberInfo[i].dwDataBaseID == teamInfo[j].nID )
			{
				bFound = true;
				break;
			}
		}
		if( !bFound )
		{
			TeamInfo info;
			info.szName = pTeamMemberList->xMemberInfo[i].szName;
			info.nID = pTeamMemberList->xMemberInfo[i].dwDataBaseID;
			info.nHp = pTeamMemberList->xMemberInfo[i].nHp;
			info.nMp = pTeamMemberList->xMemberInfo[i].nMp;
			info.nMaxHp = pTeamMemberList->xMemberInfo[i].nHpMax;
			info.nMaxMp = pTeamMemberList->xMemberInfo[i].nMpMax;
			info.nLvl = pTeamMemberList->xMemberInfo[i].stLevel;
			info.usProfession = pTeamMemberList->xMemberInfo[i].chProfession;
			info.nFaceId = pTeamMemberList->xMemberInfo[i].nFaceId;
			info.nHairId = pTeamMemberList->xMemberInfo[i].nHairId;
            info.nHeadPicId = pTeamMemberList->xMemberInfo[i].nHeadPicId;
			info.ucSex = pTeamMemberList->xMemberInfo[i].stSex;
			thePlayerRole.OnAddTeamMember( info );
		}		
	}
	// 删除
	for( int i = 0 ; i < teamInfo.size() ; ++ i )
	{
		// 队长
		if( teamInfo[i].nID == pTeamMemberList->dwTeamHeaderID )
			teamInfo[i].bHeader = true;
		else
			teamInfo[i].bHeader = false;

		bool bFound = false;
		for( int j = 0 ; j < pTeamMemberList->nCount ; ++ j )
		{
			if( pTeamMemberList->xMemberInfo[j].dwDataBaseID == teamInfo[i].nID )
			{
				bFound = true;
				break;
			}
		}
		if( !bFound && GetMe() && ( teamInfo[i].nID != GetMe()->GetCharacterID() ) )
		{
			thePlayerRole.OnDeleteTeamMember( teamInfo[i].nID );
		}
	}	
}

void CPlayerMgr::OnMsgTellAntiAddictionAccountInfo(Msg* pMsg)
{

}

// 副本倒计时
void CPlayerMgr::OnMsgEctypeStageTimeRemain( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgEctypeStageTimeRemain );
	MsgEctypeStageTimeRemain* pEctypeMapMsg = (MsgEctypeStageTimeRemain*)pMsg;

	s_CUI_ID_FRAME_MiniMap.SetEctypeMapTimeRemain(pEctypeMapMsg->dwTimeRemain);
	s_CUI_ID_FRAME_TeamBattleResult.SetBeginTime();
}

// 清空技能CD
void CPlayerMgr::OnMsgClearSkillCollDown( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgClearSkillCollDown );
	MsgClearSkillCollDown* pClearSkillCDMsg = (MsgClearSkillCollDown*)pMsg;

	if( thePlayerRole.m_SkillBag.ClearSkillCollDown(pClearSkillCDMsg->ustSkillID) )
	{
		s_CUI_ID_FRAME_MAIN.RefeashHotKey();
		s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
	}
}

// 返回验证码
void CPlayerMgr::OnMsgReqGraphicCode( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgReqGraphicCode );
	MsgReqGraphicCode* pReqMsg = ( MsgReqGraphicCode* )pMsg;	
	s_CUI_ID_FRAME_CodeCheck.SetVisable( true );
	s_CUI_ID_FRAME_CodeCheck.SetStreamInfo( pReqMsg->dwTime, pReqMsg->bitsstream, pReqMsg->glyphBuf );
}

// 返回验证码
void CPlayerMgr::OnMsgAccountPoint( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgAccountPoint );

	MsgAccountPoint* pPointMsg = ( MsgAccountPoint* )pMsg;

	s_CUI_ID_FRAME_ShopChangePoint.SetMaxValue(pPointMsg->point);
	s_CUI_ID_FRAME_ShopChangePoint.YuanBao_SetNumberLimit(true, 0, pPointMsg->point);

	s_CUI_ID_FRAME_ShopChangePoint.SetPoint(pPointMsg->point);

	char buf[256];
	MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eText_RemainRmbPoint), pPointMsg->point);
	s_CUI_ID_FRAME_ShopChangePoint.Point_SetText(buf);


	MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1,theXmlString.GetString(eText_OwnGold),thePlayerRole.GetData(CPlayerRole::TYPE_JinDing));
	s_CUI_ID_FRAME_ShopChangePoint.Hold_SetText(buf);
}
void CPlayerMgr::OnMsgTellLuckReward( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgTellLuckReward );

	MsgTellLuckReward* pTellMsg = (MsgTellLuckReward*)pMsg;
	if( pTellMsg->uchOperator == MsgTellLuckReward::ECD_Operator_ShowReward )
	{		
		s_CUI_ID_FRAME_LuckAward.SetVisable( true );
	}
	else if( pTellMsg->uchOperator == MsgTellLuckReward::ECD_Operator_ShowLuck )
	{		
		// 显示界面
		s_CUI_ID_FRAME_LuckGame.SetVisable( true );
	}	
	s_CUI_ID_FRAME_LuckGame.ClearLastRewards();
	for( int i = 0 ; i < pTellMsg->nCount && i < MsgTellLuckReward::ECD_MaxNumber; ++ i )
	{
		const RewardData* pData = theLuckRewardConfig.GetReward( pTellMsg->uchLevel, pTellMsg->uchIndex[i] );
		if( !pData )
			continue;
		s_CUI_ID_FRAME_LuckGame.AddReward( *pData );
	}
	s_CUI_ID_FRAME_LuckGame.RefreshRewardList();	
	s_CUI_ID_FRAME_LuckGame.ShowMissionText( pTellMsg->uchLevel );
	s_CUI_ID_FRAME_LuckGame.SetCurrentLevel( pTellMsg->uchLevel );
}
void CPlayerMgr::OnMsgLuckRewardAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgLuckRewardAck );
	MsgLuckRewardAck* pLmsg = (MsgLuckRewardAck*)pMsg;
	switch( pLmsg->uchResult )
	{
	case MsgLuckRewardAck::ECD_Start://rolling
		RollSystemStatusMan<RST_LuckyGame>::Instance()->ChangeState( LGS_ROLLING_BEGIN );
		s_CUI_ID_FRAME_LuckGame.SetButtonBeginVisable(false);
		s_CUI_ID_FRAME_LuckGame.SetButtonStopVisable(true);
		s_CUI_ID_FRAME_LuckGame.EnableGetAward( false );
		break;
	case MsgLuckRewardAck::ECD_Close://close
		s_CUI_ID_FRAME_LuckGame.SetVisable( false );
		s_CUI_ID_FRAME_LuckAward.SetVisable( false );
		break;
	}
}
void CPlayerMgr::OnMsgLuckRewardResult( Msg* pMsg )
{
	/** 这个消息是在按了‘停止’按钮后发来的
	*/
	CHECK_MSGLEN( pMsg, MsgLuckRewardResult );
	MsgLuckRewardResult* pLMsg = (MsgLuckRewardResult*)pMsg;	
	s_CUI_ID_FRAME_LuckGame.SetRewardResult( pLMsg->uchRewardType );
	s_CUI_ID_FRAME_LuckGame.UpdateResultByResult();
	s_CUI_ID_FRAME_LuckGame.EnableGetAward( false );
	s_CUI_ID_FRAME_LuckGame.SetButtonStopEnable(false);//m_pID_BUTTON_Stop->SetEnable( false );
}

void CPlayerMgr::OnMsgLockItemAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgLockItemAck );
	MsgLockItemAck* pLockItemMsg = ( MsgLockItemAck* )pMsg;

	CItemBag2* pBag = NULL;
	ControlListImage* pListImage = NULL;
	switch( pLockItemMsg->uchBagType )
	{
	case BT_NormalItemBag:
		pBag = &thePlayerRole.m_bag;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
		break;
	case BT_MaterialBag:
		pBag = &thePlayerRole.m_bagMaterial;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
		break;
	case BT_TaskBag:
		pBag = &thePlayerRole.m_bagTask;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
		break;
	case BT_MountBag:
		for (int i = 0; i < thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
		{
			if (thePlayerRole.m_charinfo.ItemBagData.miItems[i].baseInfo.guid == pLockItemMsg->nGuID)
			{
				thePlayerRole.m_charinfo.ItemBagData.miItems[i].SetLock(true);

				s_CUI_ID_FRAME_Pet.RefreshIconInfo();
			}
		}
		break;
	default:
		break;
	}

	if(pBag)
	{
		SCharItem* stBagItemSrc = NULL;
		if(pBag->IsHaveItem(pLockItemMsg->ustItemIndex))
		{
			stBagItemSrc = pBag->GetCharItemFromIdx( pLockItemMsg->ustItemIndex );

			assert(stBagItemSrc);

			stBagItemSrc->SetLock(true);

			s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex(pLockItemMsg->ustItemIndex);
		}
	}

	//更新图标
}

void CPlayerMgr::OnMsgUnLockItemAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgUnLockItemAck );
	MsgUnLockItemAck* pUnLockItemMsg = ( MsgUnLockItemAck* )pMsg;

	CItemBag2* pBag = NULL;
	ControlListImage* pListImage = NULL;
	switch( pUnLockItemMsg->uchBagType )
	{
	case BT_NormalItemBag:
		pBag = &thePlayerRole.m_bag;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
		break;
	case BT_MaterialBag:
		pBag = &thePlayerRole.m_bagMaterial;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
		break;
	case BT_TaskBag:
		pBag = &thePlayerRole.m_bagTask;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
		break;
	case BT_MountBag:
		for (int i = 0; i < thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
		{
			if (thePlayerRole.m_charinfo.ItemBagData.miItems[i].baseInfo.guid == pUnLockItemMsg->nGuID)
			{
				thePlayerRole.m_charinfo.ItemBagData.miItems[i].SetLock( true );
				thePlayerRole.m_charinfo.ItemBagData.miItems[i].SetUnLockTime( pUnLockItemMsg->n64UnLockTime );
				thePlayerRole.m_charinfo.ItemBagData.miItems[i].SetUnLockLeftTime( pUnLockItemMsg->nUnLockLeftTime );

				s_CUI_ID_FRAME_Pet.RefreshIconInfo();
			}
		}
		break;
		break;
	default:
		break;
	}

	if(pBag)
	{
		SCharItem* stBagItemSrc = NULL;
		if(pBag->IsHaveItem(pUnLockItemMsg->ustItemIndex))
		{
			stBagItemSrc = pBag->GetCharItemFromIdx( pUnLockItemMsg->ustItemIndex );

			assert(stBagItemSrc);

			stBagItemSrc->SetLock( true );
			stBagItemSrc->SetUnLockTime( pUnLockItemMsg->n64UnLockTime );
			stBagItemSrc->SetUnLockLeftTime( pUnLockItemMsg->nUnLockLeftTime);

			s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex(pUnLockItemMsg->ustItemIndex);
		}
	}
}

void CPlayerMgr::OnMsgCheckUnLockItemAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgCheckUnLockItemAck );
	MsgCheckUnLockItemAck* pCheckUnLockItemAck = ( MsgCheckUnLockItemAck* )pMsg;

	CItemBag2* pBag = NULL;
	ControlListImage* pListImage = NULL;
	switch( pCheckUnLockItemAck->uchBagType )
	{
	case BT_NormalItemBag:
		pBag = &thePlayerRole.m_bag;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
		break;
	case BT_MaterialBag:
		pBag = &thePlayerRole.m_bagMaterial;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
		break;
	case BT_TaskBag:
		pBag = &thePlayerRole.m_bagTask;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
		break;
	case BT_MountBag:
		for (int i = 0; i < thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
		{
			if (thePlayerRole.m_charinfo.ItemBagData.miItems[i].baseInfo.guid == pCheckUnLockItemAck->nGuID)
			{
				thePlayerRole.m_charinfo.ItemBagData.miItems[i].SetLock( false );

				s_CUI_ID_FRAME_Pet.RefreshIconInfo();
			}
		}
		break;
		break;
	default:
		break;
	}

	if(pBag)
	{
		SCharItem stBagItemSrc;
		if(pBag->IsHaveItem(pCheckUnLockItemAck->ustItemIndex))
		{
			pBag->m_pPackItem[pCheckUnLockItemAck->ustItemIndex].SetLock( false );

			s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex(pCheckUnLockItemAck->ustItemIndex);
		}
	}
}
// 拆分物品后服务器反馈
void CPlayerMgr::OnMsgMoveGoodsAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgMoveGoodsAck );
	MsgMoveGoodsAck* pMoveGoodsMsg = ( MsgMoveGoodsAck* )pMsg;

	CItemBag2* pBag = NULL;
	ControlListImage* pListImage = NULL;
	switch( pMoveGoodsMsg->ucItemBagType )
	{
	case BT_NormalItemBag:
		pBag = &thePlayerRole.m_bag;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
		break;
	case BT_MaterialBag:
		pBag = &thePlayerRole.m_bagMaterial;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
		break;
	case BT_TaskBag:
		pBag = &thePlayerRole.m_bagTask;
		pListImage = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
		break;
	default:
		break;
	}

	// 判断包裹容量
	if( pMoveGoodsMsg->ustSrcIndex >= pBag->GetNowBagSize() )
	{
		char msg[MAX_PATH] = {0};
		sprintf(msg, "MsgMoveGoodsAck::ustSrcIndex %d 超过包裹（类型 %d）容量 %d", pMoveGoodsMsg->ustSrcIndex, pMoveGoodsMsg->ucItemBagType, pBag->GetNowBagSize());
		Assert(0 && msg);
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, msg);
		return;
	}
	if( pMoveGoodsMsg->ustDstIndex >= pBag->GetNowBagSize() )
	{
		char msg[MAX_PATH] = {0};
		sprintf(msg, "MsgMoveGoodsAck::ustDstIndex %d 超过包裹（类型 %d）容量 %d", pMoveGoodsMsg->ustDstIndex, pMoveGoodsMsg->ucItemBagType, pBag->GetNowBagSize());
		Assert(0 && msg);
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, msg);
		return;
	}

	// 物品解锁
	pBag->m_pPackItem[pMoveGoodsMsg->ustSrcIndex].storageinfo.bIsLocked = false;
	pBag->m_pPackItem[pMoveGoodsMsg->ustDstIndex].storageinfo.bIsLocked = false;

    // 刷背包的 Enable 统一流程      modified by zhuomeng.hu		[12/30/2010]
    CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, pMoveGoodsMsg->ustSrcIndex );
    CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, pMoveGoodsMsg->ustDstIndex );

	if( pMoveGoodsMsg->ustCount == 0 )
	{
		// 删除
		s_CUI_ID_FRAME_PACK.RemoveItem( (EBagType)pMoveGoodsMsg->ucItemBagType, pMoveGoodsMsg->ustDstIndex, pBag->m_pPackItem[pMoveGoodsMsg->ustDstIndex].itembaseinfo.ustItemCount );
	}
	else
	{
		pBag->m_pPackItem[pMoveGoodsMsg->ustDstIndex].itembaseinfo.nOnlyInt = pMoveGoodsMsg->nGuID;
		pBag->m_pPackItem[pMoveGoodsMsg->ustDstIndex].itembaseinfo.ustItemCount = pMoveGoodsMsg->ustCount;
		pBag->m_pPackItem[pMoveGoodsMsg->ustSrcIndex].itembaseinfo.ustItemCount -= pMoveGoodsMsg->ustCount;
	}

	s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pMoveGoodsMsg->ustSrcIndex, pListImage, pBag, pMoveGoodsMsg->ucItemBagType);
	s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pMoveGoodsMsg->ustDstIndex, pListImage, pBag, pMoveGoodsMsg->ucItemBagType);
}
void CPlayerMgr::OnMsgShowTreasureBox( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgShowTreasureBox );
	MsgShowTreasureBox* pkMsg = (MsgShowTreasureBox*)pMsg;
	s_CUI_ID_FRAME_LotteryGame.OnMsgShowTreasureBox(pkMsg);
}
void CPlayerMgr::OnMsgTreasureBoxResult( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgTreasureBoxResult );
	MsgTreasureBoxResult* pkMsg = ( MsgTreasureBoxResult* )pMsg;
	s_CUI_ID_FRAME_LotteryGame.OnMsgTreasureBoxResult(pkMsg);
}
void CPlayerMgr::OnMsgTreasureBoxAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgTreasureBoxAck );
}

static int CheckCheatStatic( MsgCheckCheatReq* pMsg )
{
	LPVOID lpAddress = 0;
	try
	{
		uint32 nRet = 0;
		//char acCode[1024] = {0};
		lpAddress = VirtualAlloc(
			NULL,                 // system selects address
			4096, // size of allocation
			MEM_COMMIT,          // allocate reserved pages
			PAGE_EXECUTE_READWRITE );

		if ( lpAddress == NULL )
		{ return 0; }

		SIZE_T nWriteSize = 0;
		if ( WriteProcessMemory( GetCurrentProcess(), lpAddress, (LPVOID)pMsg->szCode, pMsg->nLength, &nWriteSize ) == FALSE )
		{
			int nError = GetLastError();
			VirtualFree( lpAddress, 0, MEM_RELEASE );
			return 1; 
		}
		_asm
		{
			//lea eax,acTempCode;
			call lpAddress;
			mov nRet,eax;
		}
		VirtualFree( lpAddress, 0, MEM_RELEASE );
		return nRet;

	}
	catch( const char* )
	{
		VirtualFree( lpAddress, 0, MEM_RELEASE );
	}
	return 2;

}
void CPlayerMgr::OnMsgCheckCheatReq( Msg* pMsg )
{

	MsgCheckCheatReq* pkMsg = ( MsgCheckCheatReq* )pMsg;
	int nValue = CheckCheatStatic( pkMsg );
	MsgCheckCheatAck msg;
	msg.nResult = nValue;
	GettheNetworkInput().SendMsg( &msg );
}

static void GetProcessListStatic( Msg* pMsg )
{
	MsgGetProcessListReq* pkMsg = ( MsgGetProcessListReq* )pMsg;
	MsgGetProcessListAck msgAck;

	msgAck.nResult = pkMsg->nLength;

	LPVOID lpAddress = 0;
	try
	{
		// get speed
		msgAck.fSpeed = thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.moveSpeed.final;			
		// is mounting
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			msgAck.bRideMount = theHeroGame.GetPlayerMgr()->GetMe()->IsMounting();

		uint32 nRet = 0;
		lpAddress = VirtualAlloc(
			NULL,                 // system selects address
			MsgGetProcessListReq::ECD_MaxLength, // size of allocation
			MEM_COMMIT,          // allocate reserved pages
			PAGE_EXECUTE_READWRITE );

		if ( lpAddress == NULL )
		{ return ; }

		SIZE_T nWriteSize = 0;
		if ( WriteProcessMemory( GetCurrentProcess(), lpAddress, (LPVOID)pkMsg->szCode, pkMsg->nLength, &nWriteSize ) == FALSE )
		{
			int nError = GetLastError();
			return ; 
		}

		static char szList[MsgGetProcessListAck::ECD_MaxLength] = {0};
		memset( szList, 0, sizeof( szList ) );		
		int nLen = MsgGetProcessListAck::ECD_MaxLength;	
		_asm
		{
			push nLen;
			push offset szList;
			call lpAddress;				
			add esp, 8
		}
		memcpy_s( msgAck.szList, sizeof( msgAck.szList ), szList, MsgGetProcessListAck::ECD_MaxLength );
		GettheNetworkInput().SendMsg( &msgAck );
		VirtualFree( lpAddress, 0, MEM_RELEASE );		

	}
	catch( const char* )
	{
		VirtualFree( lpAddress, 0, MEM_RELEASE );
	}

}
void CPlayerMgr::OnMsgGetProcessListReq( Msg* pMsg )
{
	GetProcessListStatic( pMsg );
}

void CPlayerMgr::OnMsgResetPubQuestAck( Msg* pMsg )
{
	MsgResetPubQuestAck* pkMsg = ( MsgResetPubQuestAck* )pMsg;

	s_CUI_ID_FRAME_EspecialTask.SetCanRefresh(true);
	if (pkMsg->stResult == MsgResetPubQuestAck::ECD_Success)
	{
		const int nMaxListItem = 64;
		ControlList::S_List pstList[nMaxListItem];
		int questStates[nMaxListItem];
		int nQuestCount  = 0;
		RetriveRelationQuestToNpc(pkMsg->stNpcID, nQuestCount, questStates, pstList);

		s_CUI_ID_FRAME_EspecialTask.Show(pstList, nQuestCount, pkMsg->stNpcID, s_CUI_ID_FRAME_EspecialTask.GetTaskType());
	}
}

void CPlayerMgr::OnMsgSuitElementCheckupAck( Msg* pMsg )
{	
    MsgSuitElementCheckupAck* pkMsg = ( MsgSuitElementCheckupAck* )pMsg;
    /*
    switch( pkMsg->chResult ) 
    {
    case MsgSuitElementCheckupAck::ECD_ClearSuccess:
    case MsgSuitElementCheckupAck::ECD_CheckupSuccess:
        {
            CItemBag2* pBag = 0;
            if( thePlayerRole.GetBagByItemGUID( pkMsg->nArmourGuid, pBag ) )
            {
                int nIndex = pBag->GetItemIndexByGUID( pkMsg->nArmourGuid );
                SCharItem* pItem = pBag->GetCharItemFromIdx( nIndex );
                if( pItem )
				{
                    if(pkMsg->chResult == MsgSuitElementCheckupAck::ECD_ClearSuccess)
                        pItem->SetSuitLevel( 0 );

					if( pkMsg->chElement != ItemElements_Init )//clear
						pItem->itembaseinfo.value1 |= pkMsg->chElement;
					else 
						pItem->itembaseinfo.value1 &= 0xffffff00;

					s_CUI_ID_FRAME_FiveXing.RefreshMaterial();
					s_CUI_ID_FRAME_FiveXing.RefreshArmour();
					s_CUI_ID_FRAME_FiveXing.Set_elemType(pkMsg->chElement);
					s_CUI_ID_FRAME_FiveXing.SetAck(true);

					s_CUI_ID_FRAME_PACK.RefreshMoney();
					s_CUI_ID_FRAME_FiveXing.ID_LISTIMG_ArmourOnIconRButtonUp( 0, 0 );
					s_CUI_ID_FRAME_FiveXing.ID_LISTIMG_MaterialOnIconRButtonUp( 0, 0 );	
					if( pkMsg->chElement == ItemElements_Init )//clear
						GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_Error_ClearSuccess), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
				}
			}
			break;
		}
	case MsgSuitElementCheckupAck::ECD_NotElement:
		{
			GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_Error_ItemNotElement), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
			break;
		}
	case MsgSuitElementCheckupAck::ECD_ElementAlready:
		{
			GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_Error_ItemAlreadyDid), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
			break;
		}
	case MsgSuitElementCheckupAck::ECD_NotEnoughMoney:
		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_Error_NotEnoughMoney), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
		break;
	case MsgSuitElementCheckupAck::ECD_HaveNotElement:
		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_Error_HaveNotElement), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
		break;
	case MsgSuitElementCheckupAck::ECD_ClearCountLimit:
		{
			char acError[256] = {0};
			MeSprintf_s( acError, 256, theXmlString.GetString(eText_Error_ClearCountLimit), ClearElementCount );
			GetShowScreenText() ->AddInfo( acError, Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
		}		
		break;
	case MsgSuitElementCheckupAck::ECD_NotCheckupItem:
		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_Error_NotCheckupItem), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
		break;
	case MsgSuitElementCheckupAck::ECD_NotClearItem:
		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_Error_NotClearItem), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
		break;
	case MsgSuitElementCheckupAck::ECD_LevelError:
		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_Error_LevelError), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
		break;
	}*/

}


//void CPlayerMgr::OnMsgMoneyItemExchangeAck( Msg* pMsg )
//{
//	MsgMoneyItemExchangeAck* pAck = (MsgMoneyItemExchangeAck*)pMsg;
//	s_CUI_ID_FRAME_WebAward.SetOkVisible();
//}


void CPlayerMgr::OnMsgTellGameStage( Msg* pMsg )
{
	MsgTellGameStage* pTell = (MsgTellGameStage*)pMsg;
	s_CUI_ID_FRAME_MiniMap.ShowGameStageTime(pTell->stStage, pTell->stTotalStage, pTell->dwTime);
}

void CPlayerMgr::OnMsgMoveStarAck( Msg* pMsg )
{
	MsgMoveStarAck* pAck = (MsgMoveStarAck*)pMsg;

	s_CUI_ID_FRAME_MoveStar.MoveStar(pAck->chResult, pAck->chStarLevel, pAck->bBound);
}

void CPlayerMgr::OnMsgSpecialRepairItemAck( Msg* pMsg )
{
	MsgSpecialRepairItemAck* pAck = (MsgSpecialRepairItemAck*)pMsg;
	s_CUI_ID_FRAME_SpecialRepair.RepairAck(pAck);
}


void CPlayerMgr::OnMsgEquipUpdateItemAck( Msg* pMsg )
{
	MsgEquipUpgradeAck* pAck = (MsgEquipUpgradeAck*)pMsg;
	s_CUI_ID_FRAME_EquipUpgrade.EquipUpdateAck(pAck);

}

void CPlayerMgr::OnMsgOnLineRewardAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgOnLineRewardAck );

 	MsgOnLineRewardAck* pRewardAck = (MsgOnLineRewardAck*)pMsg;
 
 	/*if(pRewardAck->uchType == MsgOnLineRewardReq::Type_NewChar)
 	{*/
 		switch( pRewardAck->uchResult )
 		{
 		case MsgOnLineRewardAck::ECD_Success:
 			s_CUI_ID_FRAME_OnlineAward2.SetVisable(false);
 			COnlineReward::Instance().GotOnlineReward(pRewardAck->nIndex);
			COnlineReward::Instance().SetCurrentStatus( COnlineReward::ORS_GOT );
			COnlineReward::Instance().SetUpdateOnlineReward();
 			break;
 		case MsgOnLineRewardAck::ECD_TimeLess:
 			if( s_CUI_ID_FRAME_OnlineAward2.IsVisable() )
 				s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable(true);
 			break;
 		case MsgOnLineRewardAck::ECD_Already:
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString( eText_OnlineAwardAlreadyGet ) );
 			s_CUI_ID_FRAME_OnlineAward2.SetVisable(false);
 			break;
 		case MsgOnLineRewardAck::ECD_NormalPageFull:
 			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString( eText_NormalPackFull ) );
 			if( s_CUI_ID_FRAME_OnlineAward2.IsVisable() )
 				s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable(true);
 			break;
		case MsgOnLineRewardAck::EDC_MaterialPageFull:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString( eText_MaterialPackFull ) );
			if( s_CUI_ID_FRAME_OnlineAward2.IsVisable() )
				s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable(true);
			break;
		case MsgOnLineRewardAck::EDC_TaskBagFull:
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString( eText_TaskPackFull ) );
			if( s_CUI_ID_FRAME_OnlineAward2.IsVisable() )
				s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable(true);
			break;
 		case MsgOnLineRewardAck::ECD_NotReward:
 			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString( eText_OnineAwardNoReward ) );
 			s_CUI_ID_FRAME_OnlineAward2.SetVisable(false);
 			break;
 		default:
 			// 让领奖按钮恢复可点
 			if( s_CUI_ID_FRAME_OnlineAward2.IsVisable() )
 				s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable(true);
 			break;
 		}
 	/*}
 	else if(pRewardAck->uchType == MsgOnLineRewardReq::Type_TurnOnLine)
 	{
 		switch( pRewardAck->uchResult )
 		{
 		case MsgOnLineRewardAck::ECD_Success:
 			s_CUI_ID_FRAME_OnlineAward3.ProcessResult();
 			break;
 		case MsgOnLineRewardAck::ECD_TimeLess:
 			break;
 		case MsgOnLineRewardAck::ECD_Already:
 			{
 			   GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_OnlineAwardAlreadyGet ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
 			   s_CUI_ID_FRAME_OnlineAward3.ProcessResult();
 			}
 			break;
 		case MsgOnLineRewardAck::ECD_PageFull:
 			GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_NormalPackFull ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
 			break;
 		case MsgOnLineRewardAck::ECD_NotReward:
 			GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_OnineAwardNoReward ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
 			break;
 		}
 	}*/
}

void CPlayerMgr::OnMsgMoveStorageItemAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgMoveStorageItemAck );

	MsgMoveStorageItemAck* pMoveItemAck = (MsgMoveStorageItemAck*)pMsg;

	CItemBag2* pBag = NULL;
	switch( pMoveItemAck->ucItemBagType )
	{
	case BT_MaterialBag:
		pBag = &thePlayerRole.m_bagMaterial;
		break;
	case BT_TaskBag:
		pBag = &thePlayerRole.m_bagTask;
		break;
	case BT_NormalItemBag:
		pBag = &thePlayerRole.m_bag;
		break;
	default:
		break;
	}
	if( pBag && pBag->IsHaveItem(pMoveItemAck->ustItemIndex) )
	{
		if( pBag->m_pPackItem[pMoveItemAck->ustItemIndex].itembaseinfo.ustItemID == pMoveItemAck->ustItemID )
		{
			pBag->m_pPackItem[pMoveItemAck->ustItemIndex].storageinfo.bIsLocked = false;
			pBag->m_pPackItem[pMoveItemAck->ustItemIndex].itembaseinfo.nOnlyInt = pMoveItemAck->nGuid;

            // 刷背包的 Enable 态统一流程     added by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, pMoveItemAck->ustItemIndex, true );
		}
	}
}

void CPlayerMgr::OnMsgBuyBackItemAck(Msg *pMsg)
{
	MsgBuyBackItemAck* ack = (MsgBuyBackItemAck*)pMsg;
	switch (ack->uchResult)
	{
	case MsgBuyBackItemAck::Success:
		{
			SCharItem* pItem = s_CUI_ID_FRAME_SHOP.GetBuyBackPack().GetItemByIndex(ack->uchBuyBackPackIndex);
			if (pItem)
			{
				MsgAckBuyOrSellGoods msg;
				msg.bIsBuy = true;
				msg.ustItemId = pItem->itembaseinfo.ustItemID;
				msg.ustPackIndex = ack->ustBagIndex;
				msg.ucItemBagType = BT_NormalItemBag;
				msg.ustResult = MsgAckBuyOrSellGoods::error_sucess;
				msg.ustCount = pItem->itembaseinfo.ustItemCount;
				msg.bCanUse = pItem->bCanUse;
				msg.n64UseTime = pItem->itembaseinfo.n64UseTime;
				msg.nOnlyInt = pItem->itembaseinfo.nOnlyInt;
				msg.dwCurMoney = ack->nLeftMoney;

				ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
				if ( pItemCommon )
				{
					switch (pItemCommon->ucItemType)
					{
					case ItemDefine::ITEMTYPE_MATERIAL:
                    case ItemDefine::ITEMTYPE_GEM:
						msg.ucItemBagType = BT_MaterialBag;
						break;
					case ItemDefine::ITEMTYPE_TASK:
						msg.ucItemBagType = BT_TaskBag;
						break;
					default:
						msg.ucItemBagType = BT_NormalItemBag;
						break;
					}
				}

				s_CUI_ID_FRAME_PACK.BuyBackOrSellBackGoods(&msg,ack);
			}

			s_CUI_ID_FRAME_SHOP.GetBuyBackPack().RemoveItemByIndex(ack->uchBuyBackPackIndex);
			s_CUI_ID_FRAME_SHOP.ToggleReturnBuyFrame();
		}
		break;
	case MsgBuyBackItemAck::PackError:
		{
			MsgBuyBackItemListReq req;
			GettheNetworkInput().SendMsg( &req );
		}
		break;
	case MsgBuyBackItemAck::PackFull:
		{
			int bagType = BT_NormalItemBag;
			SCharItem* pItem = s_CUI_ID_FRAME_SHOP.GetBuyBackPack().GetItemByIndex(ack->uchBuyBackPackIndex);
			if (pItem)
			{
				ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
				if ( pItemCommon )
					bagType = pItemCommon->ucItemType;
			}
			switch (bagType)
			{
			case BT_MaterialBag:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_MaterialPackFull) );
				break;
			case BT_TaskBag:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_TaskPackFull) );
				break;
			default:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NormalPackFull) );
				break;
			}
		}
		break;
	case MsgBuyBackItemAck::NotEnoughMoney:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eExchange_NotMoney) );
		break;
	}
}

void CPlayerMgr::OnMsgBuyBackItemListAck(Msg *pMsg)
{
	MsgBuyBackItemListAck* ack = (MsgBuyBackItemListAck*)pMsg;
	s_CUI_ID_FRAME_SHOP.GetBuyBackPack().ClearPack();
	for (int i = 0; i < ack->nCount; ++i)
	{
		s_CUI_ID_FRAME_SHOP.GetBuyBackPack().AddItem(ack->xItemList[i]);
	}
	s_CUI_ID_FRAME_SHOP.ToggleReturnBuyFrame();
}

void CPlayerMgr::OnMsgShowBattleSignUpDlg(Msg *pMsg)
{
	MsgShowBattleSignUpDlg* ack = (MsgShowBattleSignUpDlg*)pMsg;
	
	if( ack->uchShowType == MsgShowBattleSignUpDlg::ShowType_Player )
	{
		s_CUI_ID_FRAME_JoinFight.Show(ack);
	}
	else if( ack->uchShowType == MsgShowBattleSignUpDlg::ShowType_Team )
	{
		s_CUI_ID_FRAME_TeamBattleRequest.Show(ack);
		s_CUI_ID_FRAME_TeamBattleShowTeamInfo.Show(ack);
		s_CUI_ID_FRAME_TeamBattleRule.SetVisable(true);

		CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if( pMe )
		{
			s_CUI_ID_FRAME_TeamBattleRule.SetVisiblePosition( *(Vector*)&pMe->GetPos() );
			s_CUI_ID_FRAME_TeamBattleRequest.SetVisiblePosition( *(Vector*)&pMe->GetPos() );
			s_CUI_ID_FRAME_TeamBattleShowTeamInfo.SetVisiblePosition( *(Vector*)&pMe->GetPos() );
		}
		
	}
}

void CPlayerMgr::OnMsgBattleSignUpAck(Msg *pMsg)
{
	MsgBattleSignUpAck* ack = (MsgBattleSignUpAck*)pMsg;
	if( ack->uchType == MsgShowBattleSignUpDlg::ShowType_Player )
	{
		s_CUI_ID_FRAME_JoinFight.OnAck(ack);
	}
	else if( ack->uchType == MsgShowBattleSignUpDlg::ShowType_Team )
	{
		s_CUI_ID_FRAME_TeamBattleRequest.OnAck(ack);
	}
}

void CPlayerMgr::OnMsgTellBattleSignUpCount(Msg *pMsg)
{
	MsgTellBattleSignUpCount* ack = (MsgTellBattleSignUpCount*)pMsg;
	s_CUI_ID_FRAME_JoinFight.OnUpdateCount(ack);
}

void CPlayerMgr::OnMsgQueryBattleSignUpTimeAck(Msg *pMsg)
{
	MsgQueryBattleSignUpTimeAck* ack = (MsgQueryBattleSignUpTimeAck*)pMsg;
	s_CUI_ID_FRAME_TeamBattleRequest.ShowTime(ack);
	s_CUI_ID_FRAME_TeamBattleShowTeamInfo.ShowTime(ack);
}

void CPlayerMgr::OnMsgWallowAbout( Msg* pMsg )
{
	//CHECK_MSGLEN( pMsg, MsgWallowAbout );
	//MsgWallowAbout* pWallowAbout = (MsgWallowAbout*)pMsg;
	//CPreventWallow::Instance().SetFCM(pWallowAbout);
	CPreventWallow::Instance().ProcessWallowMsg( pMsg );
}

void CPlayerMgr::OnMsgCheckSecondPassword( Msg* pMsg )
{
	MsgCheckSecondPasswordReq* pCheckSecondPassword = (MsgCheckSecondPasswordReq*)pMsg;

	if( pCheckSecondPassword->nClearPasswordLeftTime == 0 )
		thePlayerRole.SetIsSecondPassword(true);
	else
		thePlayerRole.SetIsSecondPassword(false);

	s_CUI_ID_FRAME_SuperPassword.SetVisable(true);
	s_CUI_ID_FRAME_SuperPassword.Reset();
	//s_CUI_ID_FRAME_SuperPassword.SetChOperator(pCheckSecondPassword->uchOperator);
	if( GetMe() )
		s_CUI_ID_FRAME_SuperPassword.SetVisiblePosition(*(Vector*)&GetMe()->GetPos());
	if( s_CUI_ID_FRAME_SuperPassword.GetEditAddName() )
		theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPassword.GetEditAddName());

	thePlayerRole.SetSecondPasswordUnlockTime( pCheckSecondPassword->nClearPasswordLeftTime );
	
}

void CPlayerMgr::OnMsgSetSecondPassword( Msg* pMsg )
{
	MsgSetSecondPasswordAck* pSetSecondPassword = (MsgSetSecondPasswordAck*)pMsg;

	switch(pSetSecondPassword->uchResult)
	{
	case MsgSetSecondPasswordAck::SetPasswordSuccess:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordSetSucceed) );
			s_CUI_ID_FRAME_SuperPasswordRegister.Reset();
			s_CUI_ID_FRAME_SuperPasswordRegister.SetVisable(false);
			s_CUI_ID_FRAME_Storage.SetVisable(false);
			thePlayerRole.SetIsSecondPassword(true);
		}
		break;
	case MsgSetSecondPasswordAck::ReSetPasswordSuccess:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString( eText_SecondPasswordChangeSucceed ) );
			s_CUI_ID_FRAME_SuperPasswordReset.Reset();
			s_CUI_ID_FRAME_SuperPasswordReset.SetVisable(false);
			s_CUI_ID_FRAME_Storage.SetVisable(false);
			thePlayerRole.SetIsSecondPassword(true);
		}
		break;
	case MsgSetSecondPasswordAck::OldPasswordError:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString( eText_SecondPasswordWrong ) );
		break;
	case MsgSetSecondPasswordAck::PasswordFormatError:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString( eText_SecondPasswordWrong ) );
		break;
	case MsgSetSecondPasswordAck::AlreadyHavePassword:
		thePlayerRole.SetIsSecondPassword(true);
		if (s_CUI_ID_FRAME_SuperPasswordReset.IsVisable() || s_CUI_ID_FRAME_SuperPasswordRegister.IsVisable())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString( eText_AlreadyHaveSecendPsw ) );
		}
	}
}

void CPlayerMgr::OnMsgClearSecondPassword( Msg* pMsg )
{
	if (!pMsg) return;
	MsgClearSecondPasswordAck * _tPmsg = (MsgClearSecondPasswordAck*)pMsg;

   switch( _tPmsg->uchResult)
   {
   case MsgClearSecondPasswordAck::BUnchaining:
	   {
         //精确到小时吧
		   int time = int(_tPmsg->spareTime / (3600));
		   char buff[1024] = {0};
		   sprintf(buff,theXmlString.GetString(eText_SecondPasswordIsUndo),time);

		   s_CUI_ID_FRAME_MessageBox.Show(
			   buff,
			   "",
			   CUI_ID_FRAME_MessageBox::eTypeConfirm,
			   true );
	   }
	   break;
   case MsgClearSecondPasswordAck::ClearSuccess:
	   {
		   s_CUI_ID_FRAME_SuperPassword.Reset();
		   s_CUI_ID_FRAME_SuperPassword.SetVisable(false);
		   //CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString( eText_SecondPasswordUndo ) );

		   s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SecondPasswordRelieve), theXmlString.GetString(eText_SecondPasswordRelieve),CUI_ID_FRAME_MessageBox::eTypeConfirm,true);
	   }	
	   break;
   }
}

void CPlayerMgr::OnMsgCheckSecondPasswordResult( Msg* pMsg )
{
	MsgCheckSecondPasswordResult* pCheckSecondPassword = (MsgCheckSecondPasswordResult*)pMsg;

	if(pCheckSecondPassword->uchResult == MsgCheckSecondPasswordResult::SecondPasswordError)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString( eText_SecondPasswordWrong ) );
	}
	else if(pCheckSecondPassword->uchResult == MsgCheckSecondPasswordResult::Success)
	{
		s_CUI_ID_FRAME_SuperPassword.Reset();
		s_CUI_ID_FRAME_SuperPassword.SetVisable(false);
		s_CUI_ID_FRAME_SuperPassword.SetChecked(true);
		thePlayerRole.SetIsSecondPassword(true);

	}
	else if(pCheckSecondPassword->uchResult == MsgCheckSecondPasswordResult::SuccessAndClear)
	{
		s_CUI_ID_FRAME_SuperPassword.Reset();
		s_CUI_ID_FRAME_SuperPassword.SetVisable(false);
		s_CUI_ID_FRAME_SuperPassword.SetChecked(true);
		thePlayerRole.SetIsSecondPassword(true);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Store_Password, theXmlString.GetString(eText_SecondPasswordcancel) );
	}
}

void CPlayerMgr::OnMsgJiFengShopItemListAck( Msg* pMsg )
{
	s_CUI_ID_FRAME_PointShop.UpdateItem( pMsg );
}

void CPlayerMgr::OnMsgUpdateTradeShopConfig( Msg* pMsg )
{
	MsgUpdateTradeShopConfig* pTradeShopConfig = (MsgUpdateTradeShopConfig*)pMsg;

	theTradeCenter.LoadConfigFromBuffer( pTradeShopConfig->buffer,pTradeShopConfig->bufferSize,pTradeShopConfig->zip );

	s_CUI_ID_FRAME_ShopCenter.SetUpdateFlag( true );
	s_CUI_ID_FRAME_ShopCenter.SetNeedUpdate(false);
	s_CUI_ID_FRAME_ShopCenter.Refresh();

}

void CPlayerMgr::OnMsgTradeShopChange( Msg* pMsg )
{
	s_CUI_ID_FRAME_ShopCenter.SetNeedUpdate( true );
	s_CUI_ID_FRAME_ShopCenter.SetUpdateFlag( false );

	if( s_CUI_ID_FRAME_ShopCenter.IsVisable() )
	{
		char szInfo[256];
		MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1,"%s" ,theXmlString.GetString(eText_UpdateShopCenter) );
		s_CUI_ID_FRAME_MessageBox.Show( szInfo );
	}
	s_CUI_ID_FRAME_ShopCenter.SetVisable(false);
	s_CUI_ID_FRAME_BatchShop.SetVisable(false);

	theTradeCenter.Clear();

	s_CUI_ID_FRAME_ShopCenter.Refresh();
}


void CPlayerMgr::OnMsgMailList(Msg* pMsg)
{
    MsgMailListAck *pMsgMailList  = (MsgMailListAck*)pMsg;

    if(!pMsgMailList)
        return;

    thePlayerRole.ClearMailList();

    for (int i = 0;i < pMsgMailList->count;++i)
        thePlayerRole.AddMail(pMsgMailList->mails[i]);

    s_CUI_ID_FRAME_MailReceive.ClearContorData();
    s_CUI_ID_FRAME_MailReceive.Refresh();
}

void CPlayerMgr::OnMsgMailOnAck(Msg* pMsg)
{
    MsgSendMailAck *pMsgMailAck  = (MsgSendMailAck*)pMsg;

    if(!pMsgMailAck)
       return;

    switch(pMsgMailAck->result)
    {
    case MsgSendMailAck::ER_Success:           // 成功
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Success, theXmlString.GetString( eText_MailSendSuccess ) );

           s_CUI_ID_FRAME_MailMain.SetButMailState(true);  //开启UI
           s_CUI_ID_FRAME_MailMain.ClearControl();

           //处理钱
           if(pMsgMailAck->currentMoney > 0)
           {
               DWORD dwSrcMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
               dwSrcMoney = dwSrcMoney  - pMsgMailAck->currentMoney;
              //-------------------------------
               if(dwSrcMoney > 0)
               {
                   std::stringstream sstr;
                   int gold = 0, silver = 0,copper = 0;
                   thePlayerRole.GetGSCFromMoney(dwSrcMoney,gold,silver,copper);

                   sstr << theXmlString.GetString(eText_YouLost);
                   if (gold > 0)
                       sstr << gold << theXmlString.GetString(eText_Money_Gold);
                   if (silver > 0)
                       sstr << silver << theXmlString.GetString(eText_Money_Silver);
                   if (copper > 0)
                       sstr << copper << theXmlString.GetString(eText_Money_Copper);

                   CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, sstr.str().c_str() );
               }
             //----------------------------------------------------
                thePlayerRole.Update( CPlayerRole::TYPE_MONEY,  pMsgMailAck->currentMoney);
                s_CUI_ID_FRAME_PACK.RefreshMoney();
           }

           //处理物品
           if(pMsgMailAck->itemBigId == 0)
               return;

           if(pMsgMailAck->bagType == BT_NormalItemBag)
           {
               SCharItem sItem;
               if(!thePlayerRole.m_bag.GetItem(pMsgMailAck->bagIndex,&sItem))
                  return;

               s_CUI_ID_FRAME_PACK.RemoveItem((EBagType)pMsgMailAck->bagType,pMsgMailAck->bagIndex,sItem.GetItemCount());
           }
           else if(pMsgMailAck->bagType == BT_MaterialBag)
           {
               SCharItem sItem;
               if(!thePlayerRole.m_bagMaterial.GetItem(pMsgMailAck->bagIndex,&sItem))
                   return;
               s_CUI_ID_FRAME_PACK.RemoveItem((EBagType)pMsgMailAck->bagType,pMsgMailAck->bagIndex,sItem.GetItemCount());

           }
           else if(pMsgMailAck->bagType == BT_MountBag)
           {
               if( thePlayerRole.GetMountByGUID(pMsgMailAck->itemBigId) )
               {
                   ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID(
                       thePlayerRole.GetMountByGUID(pMsgMailAck->itemBigId)->baseInfo.id );
                   if (pDrome)
                   {
                       char szInfo[256];
                       MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_YouLost_N_S), 1, pDrome->GetName() );					
                       CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)thePlayerRole.GetMountByGUID(pMsgMailAck->itemBigId), 1, BT_MountBag );
                   }

                   if (thePlayerRole.GetActivedMountGUID() == pMsgMailAck->itemBigId)
                       thePlayerRole.RemoveMountSkill(*thePlayerRole.GetActivedMount());

                   thePlayerRole.RemoveMountByGUID(pMsgMailAck->itemBigId);
                   s_CUI_ID_FRAME_Pet.Refresh();
                   s_CUI_ID_FRAME_MAIN.RefeashHotKey();
                   s_CUI_ID_FRAME_Exmain.RefeashHotNumber();

                   if (s_CUI_ID_FRAME_SKILL.IsVisable())
                       s_CUI_ID_FRAME_SKILL.RefreshCommon();
               }
           }
        }
        break;
    case MsgSendMailAck::ER_TargetNotRelation: // 无关系的人
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString( eText_MailSendFriend ) );
        break;
    case MsgSendMailAck::ER_TargetNameInvalid: // 目标名字无效
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailTargetName) );
        break;
    case MsgSendMailAck::ER_AddressError:      // 目标不存在
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailTarget) );
        break;
    case MsgSendMailAck::ER_MoneyNotEnough:    // 钱不够
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailMoneyNoEnough) );
        break;
    case MsgSendMailAck::ER_MoneyTooMuch:      // 邮寄的钱太多
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailTooMuchMoney) );
        break;
    case MsgSendMailAck::ER_AccessoryInvalid:  // 附件无效
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailAccessoryError) );
        break;
    case MsgSendMailAck::ER_MailProcessing://邮件在处理中
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailProcsssing) );
        break;
    case  MsgSendMailAck::ER_TileInvalid:       // title不合法
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailTitleWrong) );
        break;
    case  MsgSendMailAck::ER_ContentInvalid:    // Content不合法
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailContentWrong) );
        break;
    case MsgSendMailAck::ER_InProtectLockTime:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_OperateFailInProtectTime) );
        break;
	case ER_MailTargetQueryFail:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailTargetQueryFail) );
		break;
    }

    if(pMsgMailAck->result != MsgSendMailAck::ER_MailProcessing)
           s_CUI_ID_FRAME_MailMain.SetButMailState(true);  //开启UI
}

void  CPlayerMgr::OnMsgMailNotify(Msg* pMsg)
{
    MsgNotifyMail* pNotifyMail = (MsgNotifyMail*)pMsg;
    if(!pNotifyMail)
        return;

    s_CUI_ID_FRAME_MiniMap.SetSplash(true);
    s_CUI_ID_FRAME_MiniMap.SetMailSender(pNotifyMail->fromAddressName);
    s_CUI_ID_FRAME_MailReceive.ClearContorData();
    s_CUI_ID_FRAME_MailReceive.Refresh();
#ifdef _DEBUG
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Success, "你有新邮件" );
#endif
}

void CPlayerMgr::OnMsgMailOpAck(Msg* pMsg)
{
    MsgOpMailAck* pOpMailAck = (MsgOpMailAck*)pMsg;
    if(!pOpMailAck)
        return;

    switch(pOpMailAck->result)
    {
    case ER_Success:
        {
          if(pOpMailAck->op == EMO_Delete)
          {
              thePlayerRole.DeleteMailByID(pOpMailAck->mailId);

              if(!thePlayerRole.IsHaveNewMail())
                  s_CUI_ID_FRAME_MiniMap.SetTipInMail(false);
          }
          else if(pOpMailAck->op == EMO_Open)
          {
                thePlayerRole.RefreshReadStateByID(pOpMailAck->mailId);

                if(!thePlayerRole.IsHaveNewMail())
                   s_CUI_ID_FRAME_MiniMap.SetTipInMail(false);
          }
          else if(pOpMailAck->op == EMO_GetMoney)
          {
              //-------------------------------------------
              DWORD dwSrcMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
              dwSrcMoney = pOpMailAck->money - dwSrcMoney;
              if(dwSrcMoney > 0)
              { 
                  std::stringstream sstr;
                  int gold = 0, silver = 0,copper = 0;
                  thePlayerRole.GetGSCFromMoney(dwSrcMoney,gold,silver,copper);

                  sstr << theXmlString.GetString(eText_YouGet_Money);
                  if (gold > 0)
                      sstr << gold << theXmlString.GetString(eText_Money_Gold);
                  if (silver > 0)
                      sstr << silver << theXmlString.GetString(eText_Money_Silver);
                  if (copper > 0)
                      sstr << copper << theXmlString.GetString(eText_Money_Copper);
                  CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, sstr.str().c_str() );
              }


              //-------------------------------------------

              thePlayerRole.RefreshMoneyByID(pOpMailAck->mailId);

              thePlayerRole.Update(CPlayerRole::TYPE_MONEY,pOpMailAck->money);
              s_CUI_ID_FRAME_PACK.RefreshMoney();
              s_CUI_ID_FRAME_MailReceive2.ClearItem(0);
          }
          else if(pOpMailAck->op == EMO_GetAccessory)
          {
              thePlayerRole.RefreshItemByID(pOpMailAck->mailId);
              s_CUI_ID_FRAME_MailReceive2.ClearItem(1);

              if(pOpMailAck->accessory.type == SMail::EAT_None)
                  assert(0&&"EMO_GetAccessory 有错误");
              else if(pOpMailAck->accessory.type == SMail::EAT_Item)
              {
                  s_CUI_ID_FRAME_PACK.PushGoods( (SCharItem*)&pOpMailAck->accessory.content );
              }
              else if(pOpMailAck->accessory.type == SMail::EAT_Mount)
              {
                  const SMountItem* pMountItem = (SMountItem*)&pOpMailAck->accessory.content;
                  thePlayerRole.AddMount(*pMountItem);
                  s_CUI_ID_FRAME_Pet.Refresh(true);

                  ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( pMountItem->baseInfo.id );
                  if (pDrome)
                  {
                      char szInfo[256];
                      MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_YouGet_N_S), 1, pDrome->GetName() );
                      CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)pMountItem, 1, BT_MountBag );
                  }
              }
          }
        }
        break;
    case ER_MailAddFail:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailAccessoryError) );
        break;
    case ER_MailCountLimit:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailSize) );
        break;
    case ER_MailNotExit: 
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailNoExist) );
        break;
    case ER_MailCannotDelete: 
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailDelFailed) );
        break;
    case ER_MailProcessing: 
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailProcsssing) );
        break;
    case ER_MailTargetQueryFail: 
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailFindFailed) );
        break;
    case ER_MailItemHaveGet:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Failed, theXmlString.GetString(eText_MailHasGetItem) );
        break;
    }

     s_CUI_ID_FRAME_MailReceive.ClearContorData();
     s_CUI_ID_FRAME_MailReceive.Refresh();
}


void CPlayerMgr::OnMsgMoveStarLevelUpAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgMoveStarLevelUpAck );
	MsgMoveStarLevelUpAck* pArk = (MsgMoveStarLevelUpAck*)pMsg;
	
	switch(pArk->uchResult)
	{
	case MsgMoveStarLevelUpAck::ECD_Success:
		s_CUI_ID_FRAME_PACK.ChangeItemIdbyGuid(BT_NormalItemBag, pArk->n64ItemGuid, pArk->ustNewItemID, pArk->n64ItemGuid);
		thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pArk->dwCurrentMoney );
		s_CUI_ID_FRAME_PACK.RefreshMoney();
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Success, theXmlString.GetString(eText_MoveStarUpgradeSuccess) );
		s_CUI_ID_FRAME_MoveStarUpgrade.ClearAll();
		break;
	case MsgMoveStarLevelUpAck::ECD_Failed:
		thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pArk->dwCurrentMoney );
		s_CUI_ID_FRAME_PACK.RefreshMoney();
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_MoveStarUpgradeFailed) );
		s_CUI_ID_FRAME_MoveStarUpgrade.OnUpgradeFailed();
		break;
	case MsgMoveStarLevelUpAck::ECD_ErrorMoveStarItem:	// 错误的移星石道具
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_UpgradeFailed_IncorrectMaterial1) );
		break;
	case MsgMoveStarLevelUpAck::ECD_ErrorMaterial:		// 错误的材料
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_UpgradeFailed_IncorrectMaterial2) );
		break;
	case MsgMoveStarLevelUpAck::ECD_CanNotLevelUp:		// 该移星石不能升级
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_UpgradeFailed_IncorrectMoveStarItem) );
		break;
	case MsgMoveStarLevelUpAck::ECD_NotEnoughMoney:		// 没有足够的钱
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_UpgradeFailed_NotEnoughMoney) );
		break;
	}
}

void CPlayerMgr::OnMsgItemComposeAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgItemComposeAck );
	MsgItemComposeAck* pArk = (MsgItemComposeAck*)pMsg;

	switch(pArk->uchResult)
	{
	case MsgItemComposeAck::ECD_Success:				// 成功
		thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pArk->dwCurrentMoney );
		s_CUI_ID_FRAME_PACK.RefreshMoney();
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Success, theXmlString.GetString(eText_MaterialUpgradeSuccess) );
		s_CUI_ID_FRAME_StarMaterialUpgrade.ClearAll();
		break;
	case MsgItemComposeAck::ECD_Failed:                 // 失败
		thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pArk->dwCurrentMoney );
		s_CUI_ID_FRAME_PACK.RefreshMoney();
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_MaterialUpgradeFailed) );
		s_CUI_ID_FRAME_StarMaterialUpgrade.ClearAll();
		break;
	case MsgItemComposeAck::ECD_NotEnoughMoney:         // 没有足够的钱
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_MaterialUpgradeFailed_NotEnoughMoney) );
		break;
	case MsgItemComposeAck::ECD_ErrorMaterialItem:      // 错误的材料
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_MaterialUpgradeFailed_IncorrectMaterial1) );
		break;
	case MsgItemComposeAck::ECD_ErrorComposeItem:       // 放入的合成材料不正确
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_MaterialUpgradeFailed_IncorrectMaterial2) );
		break;
	case MsgItemComposeAck::ECD_CanNotCompose:          // 该物品不能被合成
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_MaterialUpgradeFailed_IncorrectStarItem) );
		break;
	case MsgItemComposeAck::ECD_ItemPackFull:           // 背包已经满了
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eText_ItemNoPlace) );
		break;
	}
}

void CPlayerMgr::OnMsgReturnSystemAuction( Msg* pMsg )
{
	MsgShowConsignmentMoneyList* pReturnMoneyList = (MsgShowConsignmentMoneyList*)pMsg;

	if(pReturnMoneyList->uchShowType == MsgShowConsignmentMoneyList::Show_All)
	{
		s_CUI_ID_FRAME_GoldTrade.BuyClear();
		s_CUI_ID_FRAME_GoldTrade.SellClear();
	}
	else if(pReturnMoneyList->uchShowType == MsgShowConsignmentMoneyList::Show_SellRMB)
		s_CUI_ID_FRAME_GoldTrade.SellClear();
	else if(pReturnMoneyList->uchShowType == MsgShowConsignmentMoneyList::Show_BuyRMB)
		s_CUI_ID_FRAME_GoldTrade.BuyClear();

	for (int i = 0;i < pReturnMoneyList->nCount;++i)
		s_CUI_ID_FRAME_GoldTrade.AddReturnExchangeMoney(pReturnMoneyList->xList[i]);

	s_CUI_ID_FRAME_GoldTrade.RefreshList();
	s_CUI_ID_FRAME_GoldTrade.Refresh();

	s_CUI_ID_FRAME_GoldTrade.SetVisable(true);

	if( GetMe() )
	{
		s_CUI_ID_FRAME_GoldTrade.SetVisiblePosition( *(Vector*)&GetMe()->GetPos() );
	}
}

void CPlayerMgr::OnMsgAckHandleSystemAuctionAccountMoney( Msg* pMsg )
{
	MsgShowConsignmentAccount* pAckAccountMoney = (MsgShowConsignmentAccount*)pMsg;

	thePlayerRole.SetTradeGold(pAckAccountMoney->nRMBMoney);
	thePlayerRole.SetTradeMoney(pAckAccountMoney->nGameMoney);

	s_CUI_ID_FRAME_GoldTrade.Refresh();
}

void CPlayerMgr::OnMsgAckExcuteSystemAuction( Msg* pMsg )
{
	MsgConsignmentMoneyAck* pAck = (MsgConsignmentMoneyAck*)pMsg;
	switch(pAck->uchResult)
	{
	case MsgConsignmentMoneyAck::ECD_NotEnoughMoney:     // 账户上没有足够的游戏比
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_NoAccount) );
		break;
	case MsgConsignmentMoneyAck::ECD_NotEnoughjinDing:       // 没有足够的金锭 
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_NoAccount) );
		break;
	case MsgConsignmentMoneyAck::ECD_ConsignmentCountLimit:  // 最少交易25个金锭
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_GoldTrade_TooLess) );
		break;
	case MsgConsignmentMoneyAck::ECD_WaitProcess:            // 上一个操作正在处理中, 请稍后再试
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_SystemBusy) );
		break;
	case MsgConsignmentMoneyAck::ECD_SystemBusy:             // 不要频繁操作
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_SystemBusy) );
		break;
	case MsgConsignmentMoneyAck::ECD_MustFriend:             // 指定的玩家必须是你的好友
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_RegisterNoFriend) );
		break;
	}
}

void  CPlayerMgr::OnMsgAuctionHistroyList(Msg* pMsg)
{
	MsgShowConsignmentHistroy* pHistroyList = (MsgShowConsignmentHistroy*)pMsg;

	s_CUI_ID_FRAME_GoldTradeRegiste.Clear();

	for(int i = 0;i < pHistroyList->nCount; ++i)
		s_CUI_ID_FRAME_GoldTradeRegiste.AddMoneyAuctionHistroy(pHistroyList->xList[i]);

	s_CUI_ID_FRAME_GoldTradeRegiste.Refresh();
}

void  CPlayerMgr::OnMsgOperateMoneyAck(Msg *pMsg)
{
	MsgOperateMoneyAck *pAck = (MsgOperateMoneyAck*)pMsg;

	switch(pAck->uchResult)
	{
	case MsgOperateMoneyAck::ECD_NotEnoughMoney: // 没有足够的钱
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_NoAccount) );
		break;
	case MsgOperateMoneyAck::ECD_NotEnoughJinDing:   // 没有足够的金锭
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_NoAccount) );
		break;
	case MsgOperateMoneyAck::ECD_TooMuchMoney:       // 金钱数量达到上限
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_TooMoney) );
		break;
	case MsgOperateMoneyAck::ECD_TooMuchJinDing:     // 账户金锭数量达到上限
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_TooMoney) );
		break;
	case MsgOperateMoneyAck::ECD_WaitProcess:        // 上一个操作正在处理中, 请稍后再试
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_SystemBusy) );
		break;
	case MsgOperateMoneyAck::ECD_SystemBusy:         // 不要频繁操作
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_SystemBusy) );
		break;
	case MsgOperateMoneyAck::ECD_InProtectLockTime:	//财产保护时间
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_OperateFailInProtectTime) );
		break;
	}
}

void  CPlayerMgr::OnMsgConsignmentOperateAck(Msg *pMsg)
{
	MsgConsignmentOperateAck *pAck = (MsgConsignmentOperateAck*)pMsg;
	switch(pAck->uchResult)
	{
	case  MsgConsignmentOperateAck::ECD_Success:
		s_CUI_ID_FRAME_GoldTrade.DelExchangeMoney(pAck->n64ConsignmentID,pAck->uchConsignmentType);
		if(s_CUI_ID_FRAME_GoldTradeRegiste.UpdateConsignState(pAck->n64ConsignmentID,pAck->uchEndStatus))
			s_CUI_ID_FRAME_GoldTradeRegiste.Refresh();
		break;
	case MsgConsignmentOperateAck::ECD_NotEnoughMoney: // 账户上没有足够的钱
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_NoAccount) );
		break;
	case MsgConsignmentOperateAck::ECD_NotEnoughJinDing:   // 账户上没有足够的金锭
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_NoAccount) );
		break;
	case MsgConsignmentOperateAck::ECD_WaitProcess:        // 上一个操作正在处理中, 请稍后再试
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_SystemBusy) );
		break;
	case MsgConsignmentOperateAck::ECD_SystemBusy:        // 系统错误
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_RegisterError) );
		break;
	case MsgConsignmentOperateAck::ECD_ConsignmentSelled:  // 单子已经出售, 下次请早...
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_NoItem) );
		break;
	case MsgConsignmentOperateAck::ECD_ErrorOperate:       // 错误的操作,( 别人出售, 你要买, 别人收购, 你要卖 )
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_RegisterError) );
		break;
	case MsgConsignmentOperateAck::ECD_CanNotOperateSelf:  // 不能买卖自己的单子
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_RegisterNoBuyMySelf) );
		break;
	case MsgConsignmentOperateAck::ECD_CanNotCancelOther:  // 不能撤销其他玩家的单子
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_RegisterNoCancelOther) );
		break;
	}
}

void CPlayerMgr::OnMsgQueryConsignmentListAck(Msg *pMsg)
{
	MsgQueryConsignmentListAck *pAck = (MsgQueryConsignmentListAck*)pMsg;

	switch(pAck->uchResult)
	{
	case MsgQueryConsignmentListAck::ECD_SystemBusy:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_SystemBusy) );
		break;;
	case  MsgQueryConsignmentListAck::ECD_WaitProcess:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_RegisterWaiting) );
		break;
	}
}

void CPlayerMgr::OnMsgConsignmentMoneyHistroyAck(Msg *pMsg)
{
	MsgConsignmentMoneyHistroyAck *pAck = (MsgConsignmentMoneyHistroyAck*)pMsg;
	switch(pAck->uchResult)
	{
	case MsgConsignmentMoneyHistroyAck::ECD_SystemBusy:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_SystemAuctionError_SystemBusy) );
		break;
	case MsgConsignmentMoneyHistroyAck::ECD_WaitProcess:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Consignment_Failed, theXmlString.GetString(eText_RegisterWaiting) );
		break;
	}
}

void CPlayerMgr::OnMsgTellConsignmentMoney(Msg *pMsg)
{
	MsgTellConsignmentMoney *pMoney = (MsgTellConsignmentMoney*)pMsg;

	int nGold = 0,nSilver = 0,nCopper = 0;
	thePlayerRole.GetGSCFromMoney(pMoney->nPrice,nGold,nSilver,nCopper);

	std::stringstream strs;
	strs.str("");

	if(nGold > 0)
		strs << nGold << theXmlString.GetString(eText_Money_Gold);

	if(nSilver > 0)
		strs << nSilver << theXmlString.GetString(eText_Money_Silver);

	if(nCopper > 0)
		strs << nCopper << theXmlString.GetString(eText_Money_Copper);

	char szWord[256] = {0};
	if(pMoney->uchConsignmentType == ConsignmentDefine::Consignment_SellRMB)
		MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_TellWorldMoneyAuction),strs.str().c_str(),theXmlString.GetString(eText_GoldTrade_Sell),pMoney->nCount);
	else
		MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_TellWorldMoneyAuction),strs.str().c_str(),theXmlString.GetString(eText_GoldTrade_Buy),pMoney->nCount);

	s_CUI_ChatInfoBox.AddInfo(szWord,Color_Config.getColor(CC_CHAT_SYSTEM));
}

void  CPlayerMgr::OnMsgKillNumProcess(Msg *pMsg)
{
    MsgNotifyBattleKillNum *pMsgKill = (MsgNotifyBattleKillNum*)pMsg;
    if(!pMsgKill)
        return;

    char szWord[256] = {0};
    if(pMsgKill->beKillNum >= 0 && pMsgKill->beKillNum <= 2 )
    {
        if(pMsgKill->killNum == 3)
        {
            std::string soundFile = SwGlobal::GetWorld()->GetAppDataCharDir();
            soundFile += "\\data\\audio\\ui\\Battlefield\\Speech_1.wav";

            GSound.PlaySound( soundFile.c_str(),false,NULL );
            MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleKillAmount),pMsgKill->killer);
        }
        else if(pMsgKill->killNum == 5)
            MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleKillControl),pMsgKill->killer);
        else if(pMsgKill->killNum == 7)
        {
            std::string soundFile = SwGlobal::GetWorld()->GetAppDataCharDir();
            soundFile += "\\data\\audio\\ui\\Battlefield\\Speech_3.wav";

            GSound.PlaySound( soundFile.c_str(),false,NULL );
            MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleKillNoPeople),pMsgKill->killer);
        }
        else if(pMsgKill->killNum == 9)
            MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleKillMonster),pMsgKill->killer);
        else if(pMsgKill->killNum >= 10)
        {
            std::string soundFile = SwGlobal::GetWorld()->GetAppDataCharDir();
            soundFile += "\\data\\audio\\ui\\Battlefield\\Speech_5.wav";

            GSound.PlaySound( soundFile.c_str(),false,NULL );
            MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleGoldLike),pMsgKill->killer);
        }
    }
    else if(pMsgKill->beKillNum >= 3 && pMsgKill->beKillNum <= 4 )
    {
        MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleBeKillAmount),pMsgKill->killer,pMsgKill->beKiller);
    }
    else if(pMsgKill->beKillNum >= 5 && pMsgKill->beKillNum <= 6 )
    {
        MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleBeKillControl),pMsgKill->killer,pMsgKill->beKiller);
    }
    else if(pMsgKill->beKillNum >= 7 && pMsgKill->beKillNum <= 8)
    {
        MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleBeKillNoPeople),pMsgKill->killer,pMsgKill->beKiller);
    }
    else if(pMsgKill->beKillNum == 9)
    {
        MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleBeKillMonster),pMsgKill->killer,pMsgKill->beKiller);
    }
    else if(pMsgKill->beKillNum >= 10)
    {
        MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_CampBattleBeKillGoldLike),pMsgKill->killer,pMsgKill->beKiller);
    }

    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Battle_Success, szWord );
}

//void CPlayerMgr::OnMsgMasterReportAck(Msg* pMsg)
//{
//	CHECK_MSGLEN( pMsg, MsgMasterReportAck );
//	MsgMasterReportAck* pArk = (MsgMasterReportAck*)pMsg;
//
//	switch( pArk->uchResult )
//	{
//	case MsgMasterReportAck::ECD_Success:	    // 指点成功
//		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_DirectSucceed), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//		s_CUI_ID_FRAME_InfoList. AddInfo(theXmlString.GetString(eText_DirectSucceed), Color_Config.getColor( CC_SystemPromp ));
//		// 师傅指点特效
//		if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
//		{
//			PlayEffect("Common\\Shifu.effect", theHeroGame.GetPlayerMgr()->GetMe());
//			// 徒弟身上特效
//			CPlayer* pStudent = theHeroGame.GetPlayerMgr()->FindPlayerByCharacterID( pArk->dwPrenticeID );
//			if( pStudent )
//			{
//				PlayEffect("Common\\CommonS.effect", pStudent);
//			}
//		}
//		break;
//	case MsgMasterReportAck::ECD_MustInArea:		// 你的徒弟必须在10米范围之内
//		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_StudentMustInArea), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//		s_CUI_ID_FRAME_InfoList. AddInfo(theXmlString.GetString(eText_StudentMustInArea), Color_Config.getColor( CC_SystemPromp ));
//		break;
//	case MsgMasterReportAck::ECD_TimeLimit:		// 每天只能指点一次
//		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_BeyondDirectMax), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//		s_CUI_ID_FRAME_InfoList. AddInfo(theXmlString.GetString(eText_BeyondDirectMax), Color_Config.getColor( CC_SystemPromp ));
//		break;
//	default:
//		break;
//	}
//}

//void CPlayerMgr::OnMsgMasterReportResult(Msg* pMsg)
//{
//	CHECK_MSGLEN( pMsg, MsgMasterReportResult );
//	MsgMasterReportResult* pResult = (MsgMasterReportResult*)pMsg;
//
//	// 师傅指点成功，给徒弟加经验
//	char szText[256] = {0};
//	MeSprintf_s(szText, sizeof(szText)/sizeof(char)-1, theXmlString.GetString(eText_GetDirectFromTeacher), pResult->dwExpValue);
//	s_CUI_ID_FRAME_InfoList. AddInfo(szText, Color_Config.getColor( CC_SystemPromp ));
//	if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
//	{
//		// 徒弟被指点特效
//		PlayEffect("Common\\CommonS.effect", theHeroGame.GetPlayerMgr()->GetMe());
//		// 师傅身上特效
//		int iTeacherDBID = thePlayerRole.GetTeacherDBID();
//		if( iTeacherDBID != -1 )
//		{
//			CPlayer* pTeacher = theHeroGame.GetPlayerMgr()->FindPlayerByCharacterID( iTeacherDBID );
//			if( pTeacher )
//			{
//				PlayEffect("Common\\Shifu.effect", pTeacher);
//			}
//		}
//	}
//}

//void CPlayerMgr::OnMsgPrenticeReportAck(Msg* pMsg)
//{
//	CHECK_MSGLEN( pMsg, MsgPrenticeReportAck );
//	MsgPrenticeReportAck* pAck = (MsgPrenticeReportAck*)pMsg;
//
//	switch( pAck->uchResult )
//	{
//	case MsgPrenticeReportAck::ECD_Success:                // 汇报成功
//		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_ReportToTeacherSucceed), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//		s_CUI_ID_FRAME_InfoList. AddInfo(theXmlString.GetString(eText_ReportToTeacherSucceed), Color_Config.getColor( CC_SystemPromp ));
//		if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
//		{
//			// 徒弟汇报特效
//			PlayEffect("Common\\Tudi.effect", theHeroGame.GetPlayerMgr()->GetMe());
//			// 师傅身上特效
//			int iTeacherDBID = thePlayerRole.GetTeacherDBID();
//			if( iTeacherDBID != -1 )
//			{
//				CPlayer* pTeacher = theHeroGame.GetPlayerMgr()->FindPlayerByCharacterID( iTeacherDBID );
//				if( pTeacher )
//				{
//					PlayEffect("Common\\CommonS.effect", pTeacher);
//				}
//			}
//		}
//		break;
//	case MsgPrenticeReportAck::ECD_MustInArea:              // 你的师父必须在10米范围之内
//		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_TeacherMustInArea), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//		s_CUI_ID_FRAME_InfoList. AddInfo(theXmlString.GetString(eText_TeacherMustInArea), Color_Config.getColor( CC_SystemPromp ));
//		break;
//	case MsgPrenticeReportAck::ECD_NotEnoughExperience:    // 没有历练值不能汇报
//		GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_CannotReport_NoLiLian), Color_Config.getColor( CC_Center_WarningErrorInfo ) );
//		s_CUI_ID_FRAME_InfoList. AddInfo(theXmlString.GetString(eText_CannotReport_NoLiLian), Color_Config.getColor( CC_SystemPromp ));
//		break;
//	default:
//		break;
//	}
//}
//void CPlayerMgr::OnMsgPrenticeReportResult(Msg* pMsg)
//{
//	CHECK_MSGLEN( pMsg, MsgPrenticeReportResult );
//	MsgPrenticeReportResult* pResult = (MsgPrenticeReportResult*)pMsg;
//
//	// 徒弟向师傅汇报，师傅获得威望
//	char szText[256] = {0};
//	const char* szStudent = thePlayerRole.GetNameByDBID(pResult->dwPrenticeID);
//	if( szStudent )
//	{
//		MeSprintf_s(szText, sizeof(szText)/sizeof(char)-1, theXmlString.GetString(eText_GetReportFromStudent), szStudent, pResult->dwMasterValue);
//		s_CUI_ID_FRAME_InfoList. AddInfo(szText, Color_Config.getColor( CC_SystemPromp ));
//		if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
//		{
//			// 师傅身上特效
//			PlayEffect("Common\\CommonS.effect", theHeroGame.GetPlayerMgr()->GetMe());
//			// 徒弟汇报特效
//			CPlayer* pStudent = theHeroGame.GetPlayerMgr()->FindPlayerByCharacterID( pResult->dwPrenticeID );
//			if( pStudent )
//			{
//				PlayEffect("Common\\Tudi.effect", pStudent);
//			}
//		}
//	}
//	else
//	{
//		assert(0);
//	}
//}

void CPlayerMgr::OnMsgTellBattleRecord(Msg* pMsg)
{
	MsgTellBattleRecord* pRecord = (MsgTellBattleRecord*)pMsg;

	if( pRecord->uchType == 2 )
	{
		s_CUI_ID_FRAME_TeamBattleResult.OnRecord( pRecord );
		s_CUI_ID_FRAME_TeamBattleState.OnRecord( pRecord );
	}
}

void CPlayerMgr::OnMsgTellBattleTeamRecord(Msg* pMsg)
{
	MsgQueryTeamRecordAck* pRecord = (MsgQueryTeamRecordAck*)pMsg;

	s_CUI_ID_FRAME_TeamBattleResult.OnTeamRecord( pRecord );
	
}

void CPlayerMgr::OnMsgTellBattleSignUpInfo(Msg* pMsg)
{
	MsgTellBattleSignUpInfo* pInfo = (MsgTellBattleSignUpInfo*)pMsg;

	if( pInfo->uchType == 2 )
	{
		s_CUI_ID_FRAME_TeamBattleRequest.OnTeamInfo(pInfo);
	}
}

void CPlayerMgr::OnMsgEnterTeamBattleReq(Msg* pMsg)
{
	MsgEnterTeamBattleReq* pReq = (MsgEnterTeamBattleReq*)pMsg;

	s_CUI_ID_FRAME_TeamBattleRequest.NotifyEnter();
}

void CPlayerMgr::OnMsgBattleTeamInfo(Msg* pMsg)
{
	MsgQueryBattleTeamInfoAck* pAck = (MsgQueryBattleTeamInfoAck*)pMsg;

	s_CUI_ID_FRAME_TeamBattleShowTeamInfo.ShowInfo(pAck);
}

void CPlayerMgr::OnMsgShowViewUseItemToPlayer(Msg *pMsg)
{
	CHECK_MSGLEN( pMsg, MsgShowViewUseItemToPlayer );

	MsgShowViewUseItemToPlayer* pUseItemMsg = (MsgShowViewUseItemToPlayer*)pMsg;
	int iEffectNo = -1;
	for(int i=0; i<gCfg.m_vectorGivePresents.size(); ++i)
	{
		if( gCfg.m_vectorGivePresents[i].iItemId == pUseItemMsg->ustItemID )
		{
			iEffectNo = i;
			break;
		}
	}
	CPlayer* pSrcPlayer = FindByID(pUseItemMsg->stSrcPlayerID);
	if( pSrcPlayer && iEffectNo >= 0 )
		PlayEffect(gCfg.m_vectorGivePresents[iEffectNo].szEffect, pSrcPlayer);
	
	CPlayer* pDstPlayer = FindByID(pUseItemMsg->stDestPlayerID);
	if( pDstPlayer && iEffectNo >= 0 )
		PlayEffect(gCfg.m_vectorGivePresents[iEffectNo].szEffect, pDstPlayer);
}

void CPlayerMgr::OnMsgShowAllUseItemToPlayer(Msg *pMsg)
{
	CHECK_MSGLEN( pMsg, MsgShowAllUseItemToPlayer );

	MsgShowAllUseItemToPlayer* pUseItemMsg = (MsgShowAllUseItemToPlayer*)pMsg;
	
	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pUseItemMsg->xCharItem.itembaseinfo.ustItemID );
	if( pItemDetail )
	{
		char szInfo[256] = {0};
		Common::_tstring tstrItemName( pItemDetail->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrItemName );
		MeSprintf_s( szInfo, sizeof(szInfo)-1, theXmlString.GetString(eText_GivePresent_ShowBull), 
			pUseItemMsg->szDestPlayerName, 
			pUseItemMsg->szSrcPlayerName,
			pUseItemMsg->xCharItem.itembaseinfo.ustItemCount,
			tstrItemName.c_str(),
			pUseItemMsg->szDestPlayerName, 
			pUseItemMsg->szSrcPlayerName );
		std::string strMsg = theXmlString.GetString( eText_SystemBull );
		strMsg += szInfo;
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, strMsg, 0, (char*)&pUseItemMsg->xCharItem, 1, BT_NormalItemBag );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Bull_System, strMsg, 2, true );

		CGivePresentLogic::Instance().SetPlayGivePresentEffect(true);
	}
	else
	{
		assert(0&&"MsgShowAllUseItemToPlayer, Item not found!");
	}
}


void CPlayerMgr::OnMsgFiveXingMoveAck(Msg *pMsg)
{
    MsgSuitElementMoveAck *pMoveAck = (MsgSuitElementMoveAck*)pMsg;
    if(!pMoveAck)
        return;

    switch(pMoveAck->uchResult)
    {
    case MsgSuitElementMoveAck::ECD_Success:
    case MsgSuitElementMoveAck::ECD_Failed:
        {
            //成功以后, 转移源的五行属性和提炼等级 到目标装备上

            //获得源装备
            SCharItem *pSrcEquip = NULL;
            SCharItem *pDestEquip = NULL;
            int nSrcIndex = thePlayerRole.m_bag.GetItemIndexByGUID(pMoveAck->n64SrcArmourGuid);
            if(nSrcIndex != pMoveAck->stSrcArmourIndex)
                return;

            pSrcEquip = thePlayerRole.m_bag.GetCharItemFromIdx(nSrcIndex);
            if(!pSrcEquip)
                return;

            //是否为五行装备
            if(pSrcEquip->GetElements() == ItemElements_Init)
                return;

            //获得目标装备
            int nDestIndex = thePlayerRole.m_bag.GetItemIndexByGUID(pMoveAck->n64DestArmourGuid);
            if(nDestIndex != pMoveAck->stDestArmourIndex)
                return;

            pDestEquip = thePlayerRole.m_bag.GetCharItemFromIdx(nDestIndex);
            if(!pDestEquip)
                return;

            //设置目标道具的属性
            if(pMoveAck->uchResult == MsgSuitElementMoveAck::ECD_Success)
            {
                pDestEquip->SetElements( pSrcEquip->GetElements() );
                pDestEquip->SetSuitLevel( pSrcEquip->GetSuitLevel() );
            }

            //清空原来属性
            pSrcEquip->SetElements( ItemElements_Init );
            pSrcEquip->SetSuitLevel( 0 );

            thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pMoveAck->dwCurrentMoney );
			s_CUI_ID_FRAME_PACK.RefreshMoney();

            s_CUI_ID_FRAME_FiveXingDisplace.ClearAll();

            if(pMoveAck->uchResult == MsgSuitElementMoveAck::ECD_Success)
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Success, theXmlString.GetString(eFiveXingDisplace_Success) );
            else
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_Faild) );

        }
        break;
    case MsgSuitElementMoveAck::ECD_EquipNotExist:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_NoExistPart) );
        break;
    case MsgSuitElementMoveAck::ECD_NotHaveElement:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_NoFiveXing) );
        break;
    case MsgSuitElementMoveAck::ECD_NotElement:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_NoFiveXingPart) );
        break;
    case MsgSuitElementMoveAck::ECD_CanEquipIndexError:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_PartWrong) );
        break;
    case MsgSuitElementMoveAck::ECD_EquipLevelError:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_LevelDistance) );
        break;
    case MsgSuitElementMoveAck::ECD_ErrorElementItem:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_JinDingWrong) );
        break;
    case MsgSuitElementMoveAck::ECD_ErrorElementItemLevel:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_JinDingLevel) );
        break;
    case MsgSuitElementMoveAck::ECD_NotEnoughMoney:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eExchange_NotMoney) );
        break;
    case MsgSuitElementMoveAck::ECD_ErrorModulusItem:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_ProbMaterial) );
        break;
    case MsgSuitElementMoveAck::ECD_ErrorModulusItemCount:
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_ProbNum) );
        break;
    }
}

bool DelFriendCheck(char bIsTell,void *pData )
{
	if( !pData )
		return false;

	MsgDeleteRelationCheckAck* msg = (MsgDeleteRelationCheckAck*)pData;
	msg->bDelete = bIsTell;
	GettheNetworkInput().SendMsg(msg);
	return true;
}

void CPlayerMgr::OnMsgDelFriendCheckReq(Msg *pMsg)
{
	CHECK_MSGLEN( pMsg, MsgDeleteRelationCheckReq );
	MsgDeleteRelationCheckReq* pDelFriendCheck = (MsgDeleteRelationCheckReq*)pMsg;

	const char* szFriendName = thePlayerRole.GetNameByDBID(pDelFriendCheck->nPlayerID);
	if( szFriendName )
	{
		// 删除婚姻关系
		if( pDelFriendCheck->ustRelation == RelationDefine::Marriage &&
			thePlayerRole.GetMarryerName() &&
			!stricmp(thePlayerRole.GetMarryerName(), szFriendName) )
		{
			char szText[256] = {0};
			MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_ReqDivorce), szFriendName );
			MsgDeleteRelationCheckAck msg;
			msg.nFriendID = pDelFriendCheck->nPlayerID;
			msg.stRelation = pDelFriendCheck->ustRelation;
			s_CUI_ID_FRAME_MessageBox.Show( szText, szText,
				CUI_ID_FRAME_MessageBox::eTypeYesNo, true, DelFriendCheck, &msg, sizeof(MsgDeleteRelationCheckAck));
		}
	}
	else
	{
		assert(0);	// 没有这个人物关系
	}
}

void CPlayerMgr::OnMsgDelFriendCheckAck(Msg *pMsg)
{
	CHECK_MSGLEN( pMsg, MsgDeleteRelationCheckAck );
	MsgDeleteRelationCheckAck* pDelFriendAck = (MsgDeleteRelationCheckAck*)pMsg;

	if( pDelFriendAck->stRelation == RelationDefine::Marriage)
	{
		if( pDelFriendAck->bDelete )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_DivorceSucceed) );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Success, theXmlString.GetString(eText_DivorceSucceed) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_DivorceFailed) );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_DivorceFailed) );
		}
	}
}

void  CPlayerMgr::OnMsgJiaoZiChange(Msg *pMsg)
{
    CHECK_MSGLEN( pMsg, MsgJiaoZiChange);

    MsgJiaoZiChange *pJiaoZi = (MsgJiaoZiChange*)pMsg;
    if(!pJiaoZi)
        return;

    DWORD dwMoney = thePlayerRole.GetData( CPlayerRole::TYPE_JiaoZi );
    thePlayerRole.Update( CPlayerRole::TYPE_JiaoZi, pJiaoZi->dwJiaoZi );
    s_CUI_ID_FRAME_PACK.RefreshJiaoZi();
    s_CUI_ID_FRAME_PetMore.RefreshMoney();

    std::stringstream sstr;
    int nMoney = pJiaoZi->dwJiaoZi - dwMoney;

    if ( nMoney > 0 )
         sstr << theXmlString.GetString(eText_JiaoZiGet);
    else if (nMoney < 0)
    {
        nMoney = -nMoney;
        sstr << theXmlString.GetString(eText_JiaoZiLost);
    }

    int gold = 0, silver = 0,copper = 0;
    thePlayerRole.GetGSCFromMoney(nMoney,gold,silver,copper);

    if (gold > 0)
        sstr << gold << theXmlString.GetString(eText_Money_Gold);
    if (silver > 0)
        sstr << silver << theXmlString.GetString(eText_Money_Silver);
    if (copper > 0)
        sstr << copper << theXmlString.GetString(eText_Money_Copper);

	if(gold > 0 || silver > 0 || copper > 0)
		sstr<< theXmlString.GetString(eText_JiaoZiCopper);

    if (sstr.str().length() > 0)
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Money_Change, sstr.str().c_str() );

    sstr.str("");

    nMoney = pJiaoZi->dwNumber - thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
    //如果扣金币    
    thePlayerRole.Update(CPlayerRole::TYPE_MONEY,pJiaoZi->dwNumber);
    s_CUI_ID_FRAME_PACK.RefreshMoney();

    if ( nMoney > 0 )
        sstr << theXmlString.GetString(eText_YouGet_Money);
    else if (nMoney < 0)
    {
        nMoney = -nMoney;
        sstr << theXmlString.GetString(eText_YouLost);
    }

	thePlayerRole.GetGSCFromMoney(nMoney,gold,silver,copper);

    if (gold > 0)
        sstr << gold << theXmlString.GetString(eText_Money_Gold);
    if (silver > 0)
        sstr << silver << theXmlString.GetString(eText_Money_Silver);
    if (copper > 0)
        sstr << copper << theXmlString.GetString(eText_Money_Copper);
    if (sstr.str().length() > 0)
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Money_Change, sstr.str().c_str() );   
}

void CPlayerMgr::OnMsgTellHideStatus(Msg *pMsg)
{
	if( !pMsg )
		return;
	CHECK_MSGLEN( pMsg, MsgTellHideStatus);
	MsgTellHideStatus* pNpcHideMsg = (MsgTellHideStatus*)pMsg;

	CPlayer* pPlayer = FindByID(pNpcHideMsg->stID);
	if( !pPlayer || !pPlayer->IsNpc() )
		return;

	pPlayer->SetHide(!pNpcHideMsg->bShow);
	if( pPlayer->IsHide() && GetLockPlayerID() == pNpcHideMsg->stID )
		SetLockNpc(-1);
	//if( s_CUI_ID_FRAME_NpcChatDialogBox.GetChatNpc() == pNpcHideMsg->stID )
	//	s_CUI_ID_FRAME_NpcChatDialogBox.CancelScript();
	if(s_CUI_NpcTaskDialogBox.GetNpc() == pNpcHideMsg->stID)
		s_CUI_NpcTaskDialogBox.CloseDialog();
}

void CPlayerMgr::OnMsgTellTurenReward(Msg* pMsg)
{
	if(!pMsg)
		return;

	CHECK_MSGLEN(pMsg,MsgTellTurnReward);
	s_CUI_ID_FRAME_OnlineAward3.StartTime();

}

void CPlayerMgr::OnMsgMountAckBreed(Msg* pMsg)
{
    if( !pMsg )
        return;

    CHECK_MSGLEN( pMsg, MsgMountAckBreed );
    s_CUI_ID_FRAME_PetMore.SetVisable( false );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBreed_Success ) );
}

void CPlayerMgr::OnMsgAckOfflineHook(Msg* pMsg)
{
    if( !pMsg )
        return;

    CHECK_MSGLEN( pMsg, MsgAckOfflineHook );
    s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_ExitGameCountDown ), theXmlString.GetString( eText_ExitGameCountDown ),
        CUI_ID_FRAME_MessageBox::eTypeNothing, true, CUI_ID_FRAME_ExitGame::TellExitGame );
    s_CUI_ID_FRAME_MessageBox.SetAutoClose( 6 );
    UiDrawer::StartFillFullScreen( 500, true );             // 屏幕变黑
}

//	国家		added by zhuomeng.hu		[8/26/2010]
//void CPlayerMgr::OnMsgTellCountryBattleSignUp( Msg *pMsg )			           // 国家战场报名开始
//{
//	CHECK_MSGLEN( pMsg, MsgTellCountryBattleSignUp );
//	MsgTellCountryBattleSignUp* pSignUpBattleMsg = ( MsgTellCountryBattleSignUp* )pMsg;
//	if( !pSignUpBattleMsg )
//		return;
//    s_CUI_ID_FRAME_Country.TellCountryBattleSignUp( pSignUpBattleMsg->uchBattleType, pSignUpBattleMsg->nTime );
//}

void CPlayerMgr::OnMsgTellCountryBattleGuild( Msg *pMsg )                      // 全国广播某个帮派获得了战场资格
{
    CHECK_MSGLEN( pMsg, MsgTellCountryBattleGuild );
    MsgTellCountryBattleGuild* pBattleGuildMsg = ( MsgTellCountryBattleGuild* )pMsg;
    if( !pBattleGuildMsg )
        return;
    //s_CUI_ID_FRAME_Country.TellGuildCountryBattleQualify( pBattleGuildMsg->uchBattleType, pBattleGuildMsg->nGuildID );
	s_CUI_ID_FRAME_BaseInfo.TellGuildCountryBattleQualify( pBattleGuildMsg->uchBattleType, pBattleGuildMsg->nGuildID );
}

//void CPlayerMgr::OnMsgTellCountryBattleEnter( Msg *pMsg )                      // 国家战场开始进入
//{
//	CHECK_MSGLEN( pMsg, MsgTellCountryBattleEnter );
//	MsgTellCountryBattleEnter* pEnterBattleMsg = ( MsgTellCountryBattleEnter* )pMsg;
//	if( !pEnterBattleMsg )
//		return;
//    s_CUI_ID_FRAME_Country.TellCountryBattleEnterBegin( pEnterBattleMsg->uchBattleType, pEnterBattleMsg->nTime );
//}

//void CPlayerMgr::OnMsgTellCountryBattleFight( Msg *pMsg )                      // 国家战场战斗开始
//{
//	CHECK_MSGLEN( pMsg, MsgTellCountryBattleFight );
//	MsgTellCountryBattleFight* pBattleBeginMsg = ( MsgTellCountryBattleFight* )pMsg;
//	if( !pBattleBeginMsg )
//		return;
//    s_CUI_ID_FRAME_Country.TellCountryBattleBegin( pBattleBeginMsg->uchBattleType, pBattleBeginMsg->nTime );
//}

void CPlayerMgr::OnMsgTellCounterBattleResult( Msg *pMsg )                     // 国家战场结束, 通告结果
{
	CHECK_MSGLEN( pMsg, MsgTellCountryBattleResult );
	MsgTellCountryBattleResult* pBattleResultMsg = ( MsgTellCountryBattleResult* )pMsg;
	if( !pBattleResultMsg )
		return;
	s_CUI_ID_FRAME_BaseInfo.TellCountryBattleResult( pBattleResultMsg->uchBattleType, pBattleResultMsg->uchWinType, pBattleResultMsg->nGuildID );
    //s_CUI_ID_FRAME_Country.TellCountryBattleResult( pBattleResultMsg->uchBattleType, pBattleResultMsg->uchWinType, pBattleResultMsg->nGuildID );
	//战场结束 让UI隐藏
	const CGuildInfo* pGuildInfo = thePlayerRole.GetGuildById( pBattleResultMsg->nGuildID );
    if( !pGuildInfo )
        return;
	if(pGuildInfo->GetCountry() == thePlayerRole.GetCountry())
	{
		s_CUI_ID_FRAME_KingScoreTip.SetVisable(false);
		s_CUI_ID_FRAME_KingScoreMin.SetVisable(false);
	}
}

void CPlayerMgr::OnMsgCountryBattleSignUpAck( Msg *pMsg )                      // 国家战场报名回馈
{
	CHECK_MSGLEN( pMsg, MsgQueryCountryBattleSignUpAck );
	MsgQueryCountryBattleSignUpAck* pSignUpAckMsg = ( MsgQueryCountryBattleSignUpAck* )pMsg;
	if( !pSignUpAckMsg )
		return;
	s_CUI_ID_FRAME_BaseInfo.GetBattleSignUpResult( pSignUpAckMsg->uchResult );
   // s_CUI_ID_FRAME_Country.GetBattleSignUpResult( pSignUpAckMsg->uchResult );
}

//void CPlayerMgr::OnMsgEnterCounterBattleAck( Msg *pMsg )                       // 进入国家战场
//{
//	CHECK_MSGLEN( pMsg, MsgEnterCampBattleAck );
//	MsgEnterCampBattleAck* pEnterBattleAckMsg = ( MsgEnterCampBattleAck* )pMsg;
//	if( !pEnterBattleAckMsg )
//		return;
//    s_CUI_ID_FRAME_Country.TellEnterCountryBattle( MsgEnterCampBattleAck->uchBattleType, MsgEnterCampBattleAck->uchResult );
//}

//void CPlayerMgr::OnMsgQueryCountryBattleSignUpAck( Msg *pMsg )                 // 查询国家战场报名回馈
//{
//	CHECK_MSGLEN( pMsg, MsgQueryCountryBattleSignUpAck );
//	MsgQueryCountryBattleSignUpAck* pQuerySignUpAckMsg = ( MsgQueryCountryBattleSignUpAck* )pMsg;
//	if( !pQuerySignUpAckMsg )
//		return;
//    s_CUI_ID_FRAME_Country.TellCountryBattleQuery( pQuerySignUpAckMsg->uchBattleType, pQuerySignUpAckMsg->uchResult, pQuerySignUpAckMsg->nGuildID );
//}

void CPlayerMgr::OnMsgUpdateCountryDate(Msg *pMsg)							//更新贡品等
{
	CHECK_MSGLEN( pMsg, MsgUpdateCountryDate );
	MsgUpdateCountryDate* pUpdateCountryDate = (MsgUpdateCountryDate*)pMsg;
	if (!pUpdateCountryDate)
	{
		return;
	}
	//s_CUI_ID_FRAME_Country.GetCountryDate(pUpdateCountryDate);
	s_CUI_ID_FRAME_BaseInfo.GetCountryDate(pUpdateCountryDate);
}


void CPlayerMgr::OnMsgCountryChangeAck( Msg *pMsg )                            // 叛国回馈
{
    CHECK_MSGLEN( pMsg, MsgCountryChangeAck );
    MsgCountryChangeAck* pQuerySignUpAckMsg = ( MsgCountryChangeAck* )pMsg;
    if( !pQuerySignUpAckMsg )
        return;
   // s_CUI_ID_FRAME_Country.TellBetrayCountryResult( pQuerySignUpAckMsg->uchResult );
	s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult( pQuerySignUpAckMsg->uchResult );
}

void CPlayerMgr::OnMsgCountryTellCountryID( Msg *pMsg )                        // 叛国，通知国家ID
{
    CHECK_MSGLEN( pMsg, MsgCountryTellCountryID );
    MsgCountryTellCountryID* pTellBetrayCountryMsg = ( MsgCountryTellCountryID* )pMsg;
    if( !pTellBetrayCountryMsg )
        return;
    //s_CUI_ID_FRAME_Country.TellBetrayCountry( pTellBetrayCountryMsg->uchCountry, pTellBetrayCountryMsg->stID );
	s_CUI_ID_FRAME_BaseInfo.TellBetrayCountry( pTellBetrayCountryMsg->uchCountry, pTellBetrayCountryMsg->header.stID);
}

void CPlayerMgr::OnMsgTellCountryTitleInfo( Msg *pMsg )										// 广播国家称号
{
	CHECK_MSGLEN( pMsg, MsgTellCountryTitleInfo );
	MsgTellCountryTitleInfo* pTitleMsg = ( MsgTellCountryTitleInfo* )pMsg;
	if( !pTitleMsg )
		return;	

	CPlayer* pPlayer = FindByID(pTitleMsg->stPlayerID );
	if( pPlayer )
	{
		pPlayer->SetCountryTitle( pTitleMsg->stCountryTitle );
		if( pPlayer == theHeroGame.GetPlayerMgr()->GetMe() )
		{
			s_CUI_ID_FRAME_BaseInfo.GetCountryTitleInfo(  pTitleMsg->stCountryTitle );	
			//s_CUI_ID_FRAME_Country.GetCountryTitleInfo(  pTitleMsg->stCountryTitle );		
		}
	}
}

//	void CPlayerMgr::OnMsgQueryCountryInfoReq( Msg *pMsg )									// 获取国家信息

void CPlayerMgr::OnMsgQueryCountryInfoAck( Msg *pMsg )										// 获取国家信息回馈
{
	CHECK_MSGLEN( pMsg, MsgQueryCountryInfoAck );
	MsgQueryCountryInfoAck* pQueryInfoAckMsg = ( MsgQueryCountryInfoAck* )pMsg;
	if( !pQueryInfoAckMsg )
		return;
	s_CUI_ID_FRAME_BaseInfo.GetCountryInfo( pQueryInfoAckMsg );
	//s_CUI_ID_FRAME_Country.GetCountryInfo( pQueryInfoAckMsg );
}

void CPlayerMgr::OnMsgTellCountryQueryStatus( Msg *pMsg )									// 通知国家任务状态
{
	CHECK_MSGLEN( pMsg, MsgTellCountryQuestStatus );
	MsgTellCountryQuestStatus* pStatusMsg = ( MsgTellCountryQuestStatus* )pMsg;
	if( !pStatusMsg )
		return;
	//s_CUI_ID_FRAME_CountryQuestPost.GetCountryTaskBeginInfo( pStatusMsg );
	s_CUI_ID_FRAME_Quest.GetCountryTaskBeginInfo( pStatusMsg );
}

//	void CPlayerMgr::OnMsgCountryNoticeChangeReq( Msg *pMsg )								// 请求更改国家公告

void CPlayerMgr::OnMsgCountryNoticeChangeAck( Msg *pMsg )									// 更改国家公告回馈
{
	CHECK_MSGLEN( pMsg, MsgCountryNoticeChangeAck );
	MsgCountryNoticeChangeAck* pNoticeChangeAckMsg = ( MsgCountryNoticeChangeAck* )pMsg;
	if( !pNoticeChangeAckMsg )
		return;
	s_CUI_ID_FRAME_CountryBroadcast.GetBroadcastResult( pNoticeChangeAckMsg->uchResult );
}
//	void CPlayerMgr::OnMsgCountryQuestStateChangeReq( Msg *pMsg )							// 请求发布国家任务

void CPlayerMgr::OnMsgCountryQuestStateChangeAck( Msg *pMsg )								// 请求发布国家任务回馈
{
	CHECK_MSGLEN( pMsg, MsgCountryQuestStatusChangeAck ); 
	MsgCountryQuestStatusChangeAck* pStatusChangeMsg = ( MsgCountryQuestStatusChangeAck* )pMsg; 
	if( !pStatusChangeMsg ) 
		return; 
	s_CUI_ID_FRAME_CountryQuestPost.GetDistributeResult( pStatusChangeMsg->uchResult );
}

//	void CPlayerMgr::OnMsgCountryOfficialAppointReq( Msg *pMsg )							// 请求任命国家官员

void CPlayerMgr::OnMsgCountryOfficialAppointAck( Msg *pMsg )								// 请求任命国家官员回馈
{
	CHECK_MSGLEN( pMsg, MsgCountryOfficialAppointAck );
	MsgCountryOfficialAppointAck* pOfficialAppointMsg = ( MsgCountryOfficialAppointAck* )pMsg;
	if( !pOfficialAppointMsg )
		return;
	s_CUI_ID_FRAME_CountryInput.GetAppointResult( pOfficialAppointMsg );
}

//	void CPlayerMgr::OnMsgCountryOfficialRecallReq( Msg *pMsg )								// 请求免除国家官员

void CPlayerMgr::OnMsgCountryOfficialRecallAck( Msg *pMsg )									// 免除国家官员职位回馈
{
	CHECK_MSGLEN( pMsg, MsgCountryOfficialRecallAck );
	MsgCountryOfficialRecallAck* pOfficialRecallMsg = ( MsgCountryOfficialRecallAck* )pMsg;
	if( !pOfficialRecallMsg )
		return;
	s_CUI_ID_FRAME_CountryInput.GetDismissResult( pOfficialRecallMsg );
}

void CPlayerMgr::OnMsgCountryQuestStatusStop( Msg *pMsg )									// 通知国家发布任务结束了
{
	CHECK_MSGLEN( pMsg, MsgCountryQuestStatusStop );
	MsgCountryQuestStatusStop* pQuestStopMsg = ( MsgCountryQuestStatusStop* )pMsg;
	if( !pQuestStopMsg )
		return;
	//s_CUI_ID_FRAME_CountryQuestPost.GetCountryTaskEndInfo( pQuestStopMsg->uchQuestType );
	s_CUI_ID_FRAME_Quest.GetCountryTaskEndInfo( pQuestStopMsg->uchQuestType );
}

void CPlayerMgr::OnMsgTellCountryKillPosition( Msg *pMsg )									// 全世界广播杀死了某国官员
{
	CHECK_MSGLEN( pMsg, MsgTellCountryKillPosition );
	MsgTellCountryKillPosition* pKillOfficialMsg = ( MsgTellCountryKillPosition* )pMsg;
	if( !pKillOfficialMsg )
		return;
	s_CUI_ID_FRAME_BaseInfo.GetKillOfficialInfo( pKillOfficialMsg );
	//s_CUI_ID_FRAME_Country.GetKillOfficialInfo( pKillOfficialMsg );
}

void CPlayerMgr::OnMsgCountryRequestRaiseReq( Msg *pMsg )								// 客户端请求募集国家资金
{
	//开启国家募捐
	s_CUI_ID_FRAME_CountryResource.ShowCountryDonate();
}
void CPlayerMgr::OnMsgCountryRequestRaiseAck( Msg *pMsg )									// 国家募集回馈给申请者
{
	CHECK_MSGLEN( pMsg, MsgCountryRequestRaiseAck );
	MsgCountryRequestRaiseAck* pRaiseMsg = ( MsgCountryRequestRaiseAck* )pMsg;
	if( !pRaiseMsg )
		return;
	s_CUI_ID_FRAME_BaseInfo.GetRaiseResult( pRaiseMsg->uchResult );
	//s_CUI_ID_FRAME_Country.GetRaiseResult( pRaiseMsg->uchResult );
}

void CPlayerMgr::OnMsgCountryRaiseToPlayerReq( Msg *pMsg )									// 服务器发送募捐给所有玩家, 客户端判断等级
{
	CHECK_MSGLEN( pMsg, MsgCountryRaiseToPlayerReq );
	MsgCountryRaiseToPlayerReq* pRaiseMsg = ( MsgCountryRaiseToPlayerReq* )pMsg;
	if( !pRaiseMsg )
		return;

	s_CUI_ID_FRAME_InfoTips.AddRaiseTip();
}

/*void CPlayerMgr::OnMsgCountryRaiseToPlayerAck( Msg *pMsg )								// 玩家募捐回馈
{
	CHECK_MSGLEN( pMsg, MsgCountryRaiseToPlayerAck );
	MsgCountryRaiseToPlayerAck* pRaiseAckMsg = ( MsgCountryRaiseToPlayerAck* )pMsg;
	if( !pRaiseAckMsg )
		return;
}*/

void CPlayerMgr::OnMsgCountryRaiseTellPlayer( Msg *pMsg )									// 通知玩家募集结果
{
	CHECK_MSGLEN( pMsg, MsgCountryRaiseTellPlayer );
	MsgCountryRaiseTellPlayer* pRaiseResultMsg = ( MsgCountryRaiseTellPlayer* )pMsg;
	if( !pRaiseResultMsg )
		return;
	s_CUI_ID_FRAME_BaseInfo.TellCountryDonateResult( pRaiseResultMsg->uchResult );
	//s_CUI_ID_FRAME_Country.TellCountryDonateResult( pRaiseResultMsg->uchResult );
}

void CPlayerMgr::OnMsgCountryReceiveMountAck( Msg *pMsg )									// 领取国家坐骑回馈
{
	CHECK_MSGLEN( pMsg, MsgCountryReceiveMountAck );
	MsgCountryReceiveMountAck* pReceiveMountMsg = ( MsgCountryReceiveMountAck* )pMsg;
	if( !pReceiveMountMsg )
		return;
	s_CUI_ID_FRAME_BaseInfo.GetReceiveMountResult( pReceiveMountMsg->uchResult );
	//s_CUI_ID_FRAME_Country.GetReceiveMountResult( pReceiveMountMsg->uchResult );
}

void CPlayerMgr::OnMsgTellCountryBordersFight( Msg *pMsg )                     // 记录国家边塞战斗的坐标( 客户也记录, 记录队列长队在CountryConfig设置 )
{
	CHECK_MSGLEN( pMsg, MsgTellCountryBordersFight );
	MsgTellCountryBordersFight* pBordersFightMsg = ( MsgTellCountryBordersFight* )pMsg;
	if( !pBordersFightMsg )
		return;

	s_CUI_ID_FRAME_InfoList.GetBorderFightInfo( pBordersFightMsg );
}

void CPlayerMgr::OnMsgTellCountryKillEnemy( Msg *pMsg )										// 通知客户端 某某某抵御了外敌
{
	CHECK_MSGLEN( pMsg, MsgTellCountryKillEnemy );
	MsgTellCountryKillEnemy* pKillEnemyMsg = ( MsgTellCountryKillEnemy* )pMsg;
	if( !pKillEnemyMsg )
		return;

	s_CUI_ID_FRAME_InfoList.GetBorderDefendInfo( pKillEnemyMsg );
}

//	void CPlayerMgr::OnMsgCountryFlyToBordersReq( Msg *pMsg )								// 左右捕请求飞往边塞

//	void CPlayerMgr::OnMsgCountryOperateToPlayerReq( Msg *pMsg )							// 客户端请求操作

void CPlayerMgr::OnMsgCountryOperateToPlayerAck( Msg *pMsg )								// 客户端操作回馈
{
	CHECK_MSGLEN( pMsg, MsgCountryOperateToPlayerAck );
	MsgCountryOperateToPlayerAck* pOperateAckMsg = ( MsgCountryOperateToPlayerAck* )pMsg;
	if( !pOperateAckMsg )
		return;
	s_CUI_ID_FRAME_CountryInput.GetOperateResult( pOperateAckMsg );
}

void CPlayerMgr::OnMsgCountryTellOperateToPlayer( Msg *pMsg )								// 通知被操作者 你被干嘛了
{
	CHECK_MSGLEN( pMsg, MsgCountryTellOperateToPlayer );
	MsgCountryTellOperateToPlayer* pTellOperateMsg = ( MsgCountryTellOperateToPlayer* )pMsg;
	if( !pTellOperateMsg )
		return;
	s_CUI_ID_FRAME_CountryInput.GetBeOperatedInfo( pTellOperateMsg->uchOperate );
}

void CPlayerMgr::OnMsgTellOperateToCountry( Msg *pMsg )
{
    CHECK_MSGLEN( pMsg, MsgTellOperateToCountry );
    MsgTellOperateToCountry* pTellOperateMsg = ( MsgTellOperateToCountry* )pMsg;
    if( !pTellOperateMsg )
        return;
    s_CUI_ID_FRAME_CountryInput.GetPlayerBeOperatedInfo( pTellOperateMsg );
}

void CPlayerMgr::OnMsgCountryConveneResult( Msg *pMsg )										// 申请国家召集结果 
{
	CHECK_MSGLEN( pMsg, MsgCountryConveneResult );
	MsgCountryConveneResult* pConveneResultMsg = ( MsgCountryConveneResult* )pMsg;
	if( !pConveneResultMsg )
		return;
	s_CUI_ID_FRAME_BaseInfo.GetConveneResult( pConveneResultMsg->uchResult );
	//s_CUI_ID_FRAME_Country.GetConveneResult( pConveneResultMsg->uchResult );
}

void CPlayerMgr::OnMsgCountryConveneReq( Msg *pMsg )										// 服务器给客户端召集请求
{
	CHECK_MSGLEN( pMsg, MsgCountryConveneReq );
	MsgCountryConveneReq* pConveneMsg = ( MsgCountryConveneReq* )pMsg;
	if( !pConveneMsg )
		return;

	s_CUI_ID_FRAME_InfoTips.AddConveneTip( pConveneMsg->nOfficialID );
}

//void CPlayerMgr::OnMsgCountryConveneAck( Msg *pMsg )										// 是否同意召集 ( 不同意不用回消息 )
//{
//	CHECK_MSGLEN( pMsg, MsgCountryConveneAck );
//	MsgCountryConveneAck* pConveneAckMsg = ( MsgCountryConveneAck* )pMsg;
//	if( !pConveneAckMsg )
//		return;
//}

void CPlayerMgr::OnMsgCountryCountryAppoint( Msg *pMsg )
{
	CHECK_MSGLEN( pMsg, MsgCountryTellAppoint );
	MsgCountryTellAppoint* pBeAppointMsg = ( MsgCountryTellAppoint* )pMsg;
	if( !pBeAppointMsg )
		return;
	if(pBeAppointMsg->uchType == MsgCountryTellAppoint::ECD_Appoint)
	{
		thePlayerRole.GetCharInfo2().baseinfo.liveinfo.uchPosition = pBeAppointMsg->uchPosition;//获得新官职
	}
	else if(pBeAppointMsg->uchType == MsgCountryTellAppoint::ECD_Recall)
	{
		thePlayerRole.GetCharInfo2().baseinfo.liveinfo.uchPosition = CountryDefine::Position_None;
	}
	s_CUI_ID_FRAME_CountryInput.GetBeAppointInfo( pBeAppointMsg );
}

void CPlayerMgr::OnMsgCountryTellWeak( Msg *pMsg )
{
    CHECK_MSGLEN( pMsg, MsgCountryTellWeak );
    MsgCountryTellWeak* pCountryWeakMsg = ( MsgCountryTellWeak* )pMsg;
    if( !pCountryWeakMsg )
        return;
	s_CUI_ID_FRAME_BaseInfo.TellCountryWeak( pCountryWeakMsg->uchWeakCountryID );
    //s_CUI_ID_FRAME_Country.TellCountryWeak( pCountryWeakMsg->uchWeakCountryID );
}
void CPlayerMgr::OnMsgCountryTellStrong( Msg *pMsg )
{
	CHECK_MSGLEN( pMsg, MsgCountryTellStrong );
    MsgCountryTellStrong* pCountryStrongMsg = ( MsgCountryTellStrong* )pMsg;
    if( !pCountryStrongMsg )
        return;
	s_CUI_ID_FRAME_BaseInfo.TellCountryStrong( pCountryStrongMsg->uchStrongCountryID );
   // s_CUI_ID_FRAME_Country.TellCountryStrong( pCountryStrongMsg->uchStrongCountryID );
}
void CPlayerMgr::OnMsgCountryBattleReplace( Msg *pMsg )
{
    CHECK_MSGLEN( pMsg, MsgCountryBattleReplace );
    MsgCountryBattleReplace* pBattleReplace = ( MsgCountryBattleReplace* )pMsg;
    if( !pBattleReplace )
        return;
	s_CUI_ID_FRAME_BaseInfo.TellCountryBattleReplace( pBattleReplace->uchBattleType );
   // s_CUI_ID_FRAME_Country.TellCountryBattleReplace( pBattleReplace->uchBattleType );
}

void CPlayerMgr::OnMsgTellCountryName( Msg *pMsg )
{
    CHECK_MSGLEN( pMsg, MsgTellCountryName );
    MsgTellCountryName* pCountryName = ( MsgTellCountryName* )pMsg;
    if( !pCountryName )
        return;
	s_CUI_ID_FRAME_BaseInfo.TellCountryNameInit( ( char* )pCountryName->szName );
    //s_CUI_ID_FRAME_Country.TellCountryNameInit( ( char* )pCountryName->szName );
}

void CPlayerMgr::OnMsgChangeCountryNameAck( Msg *pMsg )
{
    CHECK_MSGLEN( pMsg, MsgChangeCountryNameAck );
    MsgChangeCountryNameAck* pChangeNameAck = ( MsgChangeCountryNameAck* )pMsg;
    if( !pChangeNameAck )
        return;
	s_CUI_ID_FRAME_BaseInfo.TellChangeCountryNameResult( pChangeNameAck->uchResult );
    //s_CUI_ID_FRAME_Country.TellChangeCountryNameResult( pChangeNameAck->uchResult );
}

void CPlayerMgr::OnMsgTellCountryNameChange( Msg *pMsg )
{
    CHECK_MSGLEN( pMsg, MsgTellCountryNameChange );
    MsgTellCountryNameChange* pCountryNameChange = ( MsgTellCountryNameChange* )pMsg;
    if( !pCountryNameChange )
        return;
	s_CUI_ID_FRAME_BaseInfo.TellCountryNameChange( pCountryNameChange->uchCountryID, pCountryNameChange->szName, pCountryNameChange->szPlayer );
    //s_CUI_ID_FRAME_Country.TellCountryNameChange( pCountryNameChange->uchCountryID, pCountryNameChange->szName, pCountryNameChange->szPlayer );
}

void CPlayerMgr::OnMsgTellMassacreCountry( Msg *pMsg )
{
    CHECK_MSGLEN( pMsg, MsgTellCountryWarStatus );
    MsgTellCountryWarStatus* pCountryWar = ( MsgTellCountryWarStatus* )pMsg;
    if( !pCountryWar )
        return;
	s_CUI_ID_FRAME_BaseInfo.TellCountryWarStatus( pCountryWar->uchStatus );
    //s_CUI_ID_FRAME_Country.TellCountryWarStatus( pCountryWar->uchStatus );
}

void CPlayerMgr::OnMsgUpdateCountryWarFightKill( Msg *pMsg )
{
    CHECK_MSGLEN( pMsg, MsgUpdateCountryWarFightKill );
    MsgUpdateCountryWarFightKill* pCountryWar = ( MsgUpdateCountryWarFightKill* )pMsg;
    if( !pCountryWar )
        return;

    s_CUI_ID_FRAME_HolyShit.UpdateKillNumber( pCountryWar->nKillCount );
}

void CPlayerMgr::OnMsgTellCountryPlayerRaise( Msg *pMsg )
{
    CHECK_MSGLEN( pMsg, MsgTellCountryPlayerRaise );
    MsgTellCountryPlayerRaise* pCountryRaise = ( MsgTellCountryPlayerRaise* )pMsg;
    if( !pCountryRaise )
        return;
	s_CUI_ID_FRAME_BaseInfo.TellPlayerRaiseResult( pCountryRaise->szName, pCountryRaise->nMoney );
    //s_CUI_ID_FRAME_Country.TellPlayerRaiseResult( pCountryRaise->szName, pCountryRaise->nMoney );
}

void CPlayerMgr::OnMsgActionInterrupt( Msg* pMsg )
{
// 	CHECK_MSGLEN( pMsg, MsgActionInterrupt );
// 	MsgActionInterrupt* pInterrupt = ( MsgActionInterrupt* )pMsg;
// 	if( !pInterrupt )
// 		return;
// 
// 	CPlayer* pPlayer = FindByID( pMsg->header.stID );
// 	if( !pPlayer || !pPlayer->GetAnim() )
// 		return;
// 
// 	if( gCfg.m_PlayerNpcActions.find( pInterrupt->nActionId ) == gCfg.m_PlayerNpcActions.end() )
// 		return;
// 
// 	CPlayerAnim* pAnim = pPlayer->GetAnim();
// 	const char* pcCurrentLowAnim = pAnim->GetCurLowerAnim();
// 	std::string strActionName = gCfg.m_PlayerNpcActions[pInterrupt->nActionId].m_acSingName;
// 	if( strActionName.compare( pcCurrentLowAnim ) == 0 )// the current is the request
// 	{
// 		// stop it!
// 		pAnim->ClearLowerBodyAnims();
// 	}


}

void CPlayerMgr::OnMsgOnOffNpcShip(Msg *pMsg)
{
	MsgOnOffNpcShip *pShip = (MsgOnOffNpcShip*)pMsg;
	if(!pShip)
		return;

	CPlayer *pPlayer = FindByID(pShip->header.stID);
	if(!pPlayer)
		return;

	CPlayer *pNpc = FindByID(pShip->npcObjectId);
	if(!pNpc)
		return;

	if(pShip->type == MsgOnOffNpcShip::EOnOffType_On)
	{
		if(theHeroGame.GetPlayerMgr()->GetMe() == pPlayer)
		   s_CUI_ID_FRAME_Only.SetVisable(true);
		
		pPlayer->SetCarrierState(true);
		pPlayer->SetCarrierPos(pShip->pos);
		pPlayer->SetCarrierDriver(pShip->npcObjectId);
	}
	else if(pShip->type == MsgOnOffNpcShip::EOnOffType_Off)
	{
		//重新设置玩家坐标
		if(GetMe() == pPlayer)
		{
			CPlayer *pPlayer = FindByID(pShip->npcObjectId);
			if(pPlayer)
			{
				float fx,fy,fz;
				pPlayer->GetPos(&fx,&fy,&fz);
				GetMe()->SetPos(fx,fy,fz);
			}
			s_CUI_ID_FRAME_Only.SetVisable(false);
		}

		pPlayer->SetCarrierState(false);
		pPlayer->SetCarrierPos(-1);
		pPlayer->SetCarrierDriver(-1);
	}
	else
		assert(0&&"大载体类型错误");
}

void CPlayerMgr::OnMsgBargainingAck( Msg* pMsg )                               // 交易申请回馈
{
    CHECK_MSGLEN( pMsg, MsgBargainingAck );
    MsgBargainingAck* pBargainAck = ( MsgBargainingAck* )pMsg;
    if( !pBargainAck )
        return;

    s_CUI_ID_FRAME_Bargaining.TellRequestBargainResult( pBargainAck->uchResult );
}

void CPlayerMgr::OnMsgBargainingRequestReq( Msg* pMsg )                        // 通知客户端, 某人申请与你交易
{
    CHECK_MSGLEN( pMsg, MsgBargainingRequestReq );
    MsgBargainingRequestReq* pBargainRequestReq = ( MsgBargainingRequestReq* )pMsg;
    if( !pBargainRequestReq )
        return;

    s_CUI_ID_FRAME_Bargaining.TellPlayerRequestBargain( pBargainRequestReq->ustPlayerID );
}

void CPlayerMgr::OnMsgBargainingStart( Msg* pMsg )                             // 通知客户端  与某人的交易开始
{
    CHECK_MSGLEN( pMsg, MsgBargainingStart );
    MsgBargainingStart* pBargainStart = ( MsgBargainingStart* )pMsg;
    if( !pBargainStart )
        return;

    s_CUI_ID_FRAME_Bargaining.TellBargainStart( pBargainStart->ustPlayerID );
}

void CPlayerMgr::OnMsgBargainingFinish( Msg* pMsg )                            // 通知客户端  交易结束
{
    CHECK_MSGLEN( pMsg, MsgBargainingFinish );
    MsgBargainingFinish* pBargainFinish = ( MsgBargainingFinish* )pMsg;
    if( !pBargainFinish )
        return;

    s_CUI_ID_FRAME_Bargaining.TellBargainFinish( pBargainFinish->uchFinishType );
}

void CPlayerMgr::OnMsgBargainingStatus( Msg* pMsg )                            // 通知客户端 某玩家的交易状态
{
    CHECK_MSGLEN( pMsg, MsgBargainingStatus );
    MsgBargainingStatus* pBargainStatus = ( MsgBargainingStatus* )pMsg;
    if( !pBargainStatus )
        return;

    s_CUI_ID_FRAME_Bargaining.TellBargainStatus( pBargainStatus->ustPlayerID, pBargainStatus->uchStatus );
}

void CPlayerMgr::OnMsgBargainingDataAck( Msg* pMsg )                           // 通知玩家加入了物品到交易栏中
{
    CHECK_MSGLEN( pMsg, MsgBargainingDataAck );
    MsgBargainingDataAck* pBargainDataAck = ( MsgBargainingDataAck* )pMsg;
    if( !pBargainDataAck )
        return;

    s_CUI_ID_FRAME_Bargaining.TellBargainSelfAddData( pBargainDataAck );
}

void CPlayerMgr::OnMsgShowBargainingData( Msg* pMsg )                          // 通知对方玩家交易的数据
{
    CHECK_MSGLEN( pMsg, MsgShowBargainingData );
    MsgShowBargainingData* pShowBargainData = ( MsgShowBargainingData* )pMsg;
    if( !pShowBargainData )
        return;

    s_CUI_ID_FRAME_Bargaining.TellBargainPlayerAddData( pShowBargainData );
}

void CPlayerMgr::OnMsgRemoveBargainingDataAck( Msg* pMsg )                     // 回应移除交易物品, 客户端删除该位置的物品
{
    CHECK_MSGLEN( pMsg, MsgRemoveBargainingDataAck );
    MsgRemoveBargainingDataAck* pRemoveBargain = ( MsgRemoveBargainingDataAck* )pMsg;
    if( !pRemoveBargain )
        return;

    s_CUI_ID_FRAME_Bargaining.TellBargainRemoveData( pRemoveBargain );
}

void CPlayerMgr::OnMsgBargainingDataError( Msg* pMsg )                         // 通知客户端交易物品的各类错误            
{
    CHECK_MSGLEN( pMsg, MsgBargainingDataError );
    MsgBargainingDataError* pBargainError = ( MsgBargainingDataError* )pMsg;
    if( !pBargainError )
        return;

    s_CUI_ID_FRAME_Bargaining.TellBargainErrors( pBargainError->ustPlayerID, pBargainError->uchResult );
}

void CPlayerMgr::OnMsgUpdateMountStorage( Msg* pMsg )                          // 坐骑仓库数据更新
{
    CHECK_MSGLEN( pMsg, MsgUpdateMountStorage );
    MsgUpdateMountStorage* pMountStorage = ( MsgUpdateMountStorage* )pMsg;
    if( !pMountStorage )
        return;

    memcpy_s( thePlayerRole.m_stStorage.xStorageMounts, sizeof( thePlayerRole.m_stStorage.xStorageMounts ),
        pMountStorage->xStorageMounts, sizeof( pMountStorage->xStorageMounts ) );
    s_CUI_ID_FRAME_PetStorage.Refresh();
}

void CPlayerMgr::OnMsgUpdateCharMount( Msg* pMsg )                             // 玩家身上坐骑列表更新
{
    CHECK_MSGLEN( pMsg, MsgUpdateCharMount );
    MsgUpdateCharMount* pCharMount = ( MsgUpdateCharMount* )pMsg;
    if( !pCharMount )
        return;

    memcpy_s( thePlayerRole.m_charinfo.ItemBagData.miItems, sizeof( thePlayerRole.m_charinfo.ItemBagData.miItems ),
        pCharMount->xMounts, sizeof( pCharMount->xMounts ) );
    s_CUI_ID_FRAME_PetList.Refresh();
    s_CUI_ID_FRAME_Pet.Refresh();
}

// 服务器通知客户端是否要进入帮派阵营战场
void CPlayerMgr::OnMsgFlyToCampBattleReq(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgFlyToCampBattleReq);
	MsgFlyToCampBattleReq* pReq = (MsgFlyToCampBattleReq*)pMsg_;

	//判断玩家是否有权限进入指定的战场 无则不显示UI
	unsigned int Value = 0;
	bool isOpen = false;

	switch(pReq->uchBattleType)
	{
	case CampDefine::BattleTypeKing:
		Value = GuildDefine::CampBattleCountry;
		isOpen = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_CountrySetting.IsOpen;
		break;
	case CampDefine::BattleTypeGuild:
		Value = GuildDefine::CampBattleGuild;
		isOpen = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_GuildSetting.IsOpen;
		break;
	case CampDefine::BattleTypeGuildUnion:
		Value = GuildDefine::CampBattleGuildUnion;
		isOpen = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_GuildUnionSetting.IsOpen;
		break;
	}
	GuildMember * pMember = thePlayerRole.GetGangMgr()->FindByDBId(thePlayerRole.GetDBID());
	if(!pMember || (!(pMember->GetCampBattleValue()& Value) && isOpen))
		return;

	switch (pReq->uchBattleType)
	{
	case CampDefine::BattleTypeGuild:
		{
			//s_CUI_ID_FRAME_InfoTips.AddGuildCampTip(pMsg_);
			//弹出公会战场的进入UI 1.传送到合适的地图的NPC旁边 在进入副本
			thePlayerRole.SetRedCampGuildId(pReq->RedID);
			thePlayerRole.SetBlueCampGuildId(pReq->BlueID);
			s_CUI_ID_FRAME_GuildBattleEnter.SetKingdomMapInfo(pReq->nKingdomID,pReq->nKingdomX,pReq->nKingdomY);
			s_CUI_ID_FRAME_GuildBattleEnter.SetVisable(true);
			s_CUI_ID_FRAME_GuildBattleEnter.Refresh();
		}
		break;
	case CampDefine::BattleTypeGuildUnion:
		{
			//s_CUI_ID_FRAME_InfoTips.AddGuildCampTip(pMsg_);
			//添加新的UI
			thePlayerRole.SetRedCampGuildId(pReq->RedID);
			thePlayerRole.SetBlueCampGuildId(pReq->BlueID);
			s_CUI_ID_FRAME_GuildUnionBattleEnter.SetKingdomMapInfo(pReq->nKingdomID,pReq->nKingdomX,pReq->nKingdomY);
			//s_CUI_ID_FRAME_GuildUnionBattleEnter.SetVisable(true);.
			s_CUI_ID_FRAME_GuildUnionBattleEnter.SetVisable(true);
			s_CUI_ID_FRAME_GuildUnionBattleEnter.Refresh();
		}
		break;
	case CampDefine::BattleTypeKing:
		{
			thePlayerRole.SetRedCampGuildId(pReq->RedID);
			thePlayerRole.SetBlueCampGuildId(pReq->BlueID);
			s_CUI_ID_FRAME_KingBattleEnter.SetKingdomMapInfo(pReq->nKingdomID,pReq->nKingdomX,pReq->nKingdomY);
			//s_CUI_ID_FRAME_KingBattleEnter.SetVisable(true);
			//s_CUI_ID_FRAME_InfoTips.AddKingCampTip(pMsg_);
			s_CUI_ID_FRAME_KingBattleEnter.SetVisable(true);
			s_CUI_ID_FRAME_KingBattleEnter.Refresh();
		}
		break;
	default:
		break;			
	}
}

// 阵营战场的杀人信息
void CPlayerMgr::OnMsgGetCampBattleInfo(Msg* pMsg_)
{	
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCampBattlePlayer);
	MsgTellCampBattlePlayer* pMsg = (MsgTellCampBattlePlayer*)pMsg_;
	
	switch (pMsg->uchCampBattleType)
	{
	case CampDefine::BattleTypeGuild:
		{
			s_CUI_ID_FRAME_GuildBattle.InitBattleInfo(pMsg->uchCount, pMsg->xPlayer);
		}		
		break;
	case CampDefine::BattleTypeGuildUnion:
		{
			s_CUI_ID_FRAME_GuildBattle.InitBattleInfo(pMsg->uchCount, pMsg->xPlayer);
		}
		break;
	default:
		break;
	}
}

// 通知客户端阵营消息
void CPlayerMgr::OnMsgTellGameBattleFightCamp(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellGameBattleFightCamp);
	MsgTellGameBattleFightCamp* pMsg = (MsgTellGameBattleFightCamp*)pMsg_;
	
	if (theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->GetID() == pMsg->ustPlayerID)
	{
		thePlayerRole.SetInfluence(pMsg->uchFightCamp);
		if (m_pMe)
		{
			m_pMe->SetInfluence(pMsg->uchFightCamp);
		}

		if (pMsg->uchFightCamp == GameBattleDefine::GameBattle_None)
		{
			s_CUI_ID_FRAME_KingScoreTip.SetVisable(false);
			s_CUI_ID_FRAME_KingScoreMin.SetVisable(false);
			s_CUI_ID_FRAME_Group_Me.SetGuildBattleButtonVisable(false);
		}
		else
		{
			s_CUI_ID_FRAME_InfoTips.DeleteGuildCampTip();
			s_CUI_ID_FRAME_Group_Me.SetGuildBattleButtonVisable(true);
		}
	}
	
}
void CPlayerMgr::OnMsgGetMyFightCampType(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCampBattleFightCamp);
	MsgTellCampBattleFightCamp* pMsg = (MsgTellCampBattleFightCamp*)pMsg_;
	
	if (theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->GetID() == pMsg->ustPlayerID)
	{
		thePlayerRole.SetInfluence(pMsg->uchFightCamp);
		if (m_pMe)
		{
			m_pMe->SetInfluence(pMsg->uchFightCamp);
		}

		if (pMsg->uchFightCamp == CampDefine::NoneCamp)
		{
			s_CUI_ID_FRAME_KingScoreTip.SetVisable(false);
			s_CUI_ID_FRAME_KingScoreMin.SetVisable(false);
			s_CUI_ID_FRAME_Group_Me.SetGuildBattleButtonVisable(false);
		}

		switch (CampDefine::GetBattleTypeByCamp(pMsg->uchFightCamp))
		{
		case CampDefine::BattleTypeGuild:
			{
				s_CUI_ID_FRAME_InfoTips.DeleteGuildCampTip();
				s_CUI_ID_FRAME_Group_Me.SetGuildBattleButtonVisable(true);
			}
			break;
		case CampDefine::BattleTypeKing:
			{
				s_CUI_ID_FRAME_InfoTips.DeleteKingCampTip();
				//清空积分
				s_CUI_ID_FRAME_KingScoreTip.InitCampData();
				s_CUI_ID_FRAME_KingScoreTip.SetVisable(true);
			}
			break;
		case CampDefine::BattleTypeGuildUnion:
			{
				s_CUI_ID_FRAME_InfoTips.DeleteGuildCampTip();
				s_CUI_ID_FRAME_Group_Me.SetGuildBattleButtonVisable(true);
				//s_CUI_ID_FRAME_GuildUnionBattleEnter.SetVisable(true);
			}
			break;
		default:
			break;
		}
	}
}

// 显示帮派争夺战进入窗口
void CPlayerMgr::OnMsgShowCampGuildBattleEnter(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgShowCampGuildBattleEnter);
	MsgShowCampGuildBattleEnter* pMsg = (MsgShowCampGuildBattleEnter*)pMsg_;

	thePlayerRole.SetRedCampGuildId(pMsg->nRedGuildID);
	thePlayerRole.SetBlueCampGuildId(pMsg->nBlueGuildID);

	switch (pMsg->uchBattleType)
	{
	case CampDefine::BattleTypeGuild:
		{
			s_CUI_ID_FRAME_GuildBattleEnter.SetVisable(true);
			s_CUI_ID_FRAME_GuildBattleEnter.Refresh();
		}		
		break;
	case CampDefine::BattleTypeGuildUnion:
		{
			s_CUI_ID_FRAME_GuildUnionBattleEnter.SetVisable(true);
			s_CUI_ID_FRAME_GuildUnionBattleEnter.Refresh();
		}
		break;
	case CampDefine::BattleTypeKing:
		{
			s_CUI_ID_FRAME_KingBattleEnter.SetVisable(true);
			s_CUI_ID_FRAME_KingBattleEnter.Refresh();
		}
	default:
		break;
	}
}

void CPlayerMgr::ShowGuildBattleInfo(const char* szText)
{
	if (!szText)
	{
		return;
	}

	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szText );
}

void ShowCampBattleInfo_new(const char* szText)
{
	if (!szText)
	{
		return;
	}
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, szText );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, szText );
}

void ShowCampBattleInfo(const char* szText)
{
	if (!szText)
	{
		return;
	}

	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Bull_Broadcast, szText );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_GuildCamp_Message, szText );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ShiTu_Belongs_Success, szText );
}

//进入战场结果回馈notice
void CPlayerMgr::OnMsgEnterCampBattleNotice(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgEnterCampBattleAck);
	MsgEnterCampBattleAck* pMsg = (MsgEnterCampBattleAck*)pMsg_;

	switch (pMsg->uchResult)
	{
	case CampDefine::Enter_NotEnterStatus:
		{
			ShowCampBattleInfo_new(theXmlString.GetString(eText_GuildCamp_TimeBeforeBattle));
		}
		break;
	case CampDefine::Enter_MustSignUpGuild:
		{
			ShowCampBattleInfo_new(theXmlString.GetString(eText_GuildCamp_NotSignUp));
		}
		break;
	case CampDefine::Enter_LevelLess:
		{
			ShowCampBattleInfo_new(theXmlString.GetString(eText_Camp_LevelLess));
		}
		break;
	case CampDefine::Enter_MaxCount:
		{
			ShowCampBattleInfo_new(theXmlString.GetString(eText_Camp_MaxCount));
		}
		break;
	case CampDefine::Enter_BattleSumError:
		{
			ShowCampBattleInfo_new(theXmlString.GetString(eText_Enter_BattleSumError));
		}
		break;
	default:
		break;
	}
}

void ShowGuildBattleBullSystemInfo(const char* szText)
{
	if (!szText)
	{
		return;
	}

	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Bull_System, szText );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, szText );
}

//通知帮派争夺战结果
void CPlayerMgr::OnMsgGetGuildBattleResult(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgCampGuildBattleResult);
	MsgCampGuildBattleResult* pMsg = (MsgCampGuildBattleResult*)pMsg_;

	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_GuildCamp_BattleResult), thePlayerRole.GetGuildNameById(pMsg->nWinGuildID), thePlayerRole.GetGuildNameById(pMsg->nLoseGuildID));
	/*CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Bull_System, szText );*/
	ShowGuildBattleBullSystemInfo(szText);
}

//报名结果回馈notice
void CPlayerMgr::OnMsgCampBattleSignNotice(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgCampBattleSignUpAck);
	MsgCampBattleSignUpAck* pMsg = (MsgCampBattleSignUpAck*)pMsg_;

	char szText[256] = {0};
	switch (pMsg->uchResult)
	{
	case CampDefine::SignUp_Success:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_GuildCamp_SignUpSuccess));
		}
		break;
	case CampDefine::SignUp_NotSignUpStatus:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_GuildCamp_WrongTime));
		}
		break;
	case CampDefine::SignUp_MustGuildMaster:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_GuildCamp_MustMaster));
		}
		break;
	case CampDefine::SignUp_GuildMemberLess:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_GuildCamp_MemberNumNotEnough));
		}
		break;
	case CampDefine::SignUp_AlreadySignUp:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_GuildCamp_AlreadySignUp));
		}
		break;
	case CampDefine::SignUp_CanNotSignUp:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_CountryBattle_SignUp_CanNot));
		}
		break;
	case CampDefine::SignUp_GuildLevelLess:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_CountryBattle_SignUp_LevelLess));
		}
		break;
	case CampDefine::SignUp_NotEnoughGuildMoney:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_CountryBattle_SignUp_MoreMoney));
		}
		break;
	case CampDefine::SignUp_GuildStrengthLess:
		{
			/*MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_CountryBattle_SignUp_StrengthLess));*/
			MeSprintf_s( szText, sizeof( szText ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_SignUp_StrengthLess )/*, pMsg->uchWarxishu ,pMsg->unhGuildxishu*/);
		}
		break;
	case CampDefine::SignUp_GuildUnionBattleSumError:
		{
			MeSprintf_s( szText, sizeof( szText ) / sizeof( char ) - 1, theXmlString.GetString( eText_SignUp_GuildUnionBattleSumError ), 
				pMsg->uchWarxishu ,pMsg->unhGuildxishu);	
		}
		break;
	case CampDefine::SignUp_GuildUnionBattleNone:
		{
			MeSprintf_s( szText, sizeof( szText ) / sizeof( char ) - 1, theXmlString.GetString( eText_SignUp_GuildUnionBattleNone ), 
				pMsg->uchWarxishu ,pMsg->unhGuildxishu);
		}
		break;
	case CampDefine::SignUp_GuildBattleFull:
		{
			MeSprintf_s( szText, sizeof( szText ) / sizeof( char ) - 1, theXmlString.GetString( eText_SignUp_GuildBattleFull ), 
				pMsg->uchWarxishu ,pMsg->unhGuildxishu);
		}
		break;
	default:
		break;
	}

	ShowCampBattleInfo_new(szText);
}


// 通知阵营战场状态
void CPlayerMgr::OnMsgGuildBattleStatus(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCampBattleStatus);
	MsgTellCampBattleStatus* pMsg = (MsgTellCampBattleStatus*)pMsg_;
	char szText[256] = {0};

	//guildCamp
	if (pMsg->uchCampBattleType == CampDefine::BattleTypeGuild)
	{
		switch (pMsg->uchCampBattleStatus)
		{
		case CampDefine::StatusInit:
			break;
		case CampDefine::StatusSignUp:
			{
				ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildCamp_BullSystem_SignUp));
			}
			break;
		case CampDefine::StatusPrepare:
			{
				ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildCamp_BullSystem_Prepare));
			}
			break;
		case CampDefine::StatusEnter:
			{
				thePlayerRole.SetRedCampResource(0);
				thePlayerRole.SetBlueCampResource(0);
				s_CUI_ID_FRAME_ScoreTip.SetTime(pMsg->nLeftTime);
				if(s_CUI_ID_FRAME_ScoreTip.GetStringId() != eText_GuildCamp_TimeToCampStart)
					ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildCamp_BullSystem_Enter));
				s_CUI_ID_FRAME_ScoreTip.SetStringId(eText_GuildCamp_TimeToCampStart);
			}
			break;
		case CampDefine::StatusFight:
			{
				s_CUI_ID_FRAME_ScoreTip.SetTime(pMsg->nLeftTime);
				if(s_CUI_ID_FRAME_ScoreTip.GetStringId() != eText_GuildCamp_TimeToCampEnd)
					ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildCamp_BullSystem_Fight));
				s_CUI_ID_FRAME_ScoreTip.SetStringId(eText_GuildCamp_TimeToCampEnd);
			}
			break;
		case CampDefine::StatusEnd:
			{
				ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildCamp_BullSystem_Over));
			}
			break;
		case CampDefine::StatusRelease:
			break;
		default:
			break;
		}

		return;
	}

	if(pMsg->uchCampBattleType ==  CampDefine::BattleTypeGuildUnion)
	{
		switch (pMsg->uchCampBattleStatus)
		{
		case CampDefine::StatusInit:
			break;
		case CampDefine::StatusSignUp:
			{
				ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildUnionCamp_BullSystem_SignUp));
			}
			break;
		case CampDefine::StatusPrepare:
			{
				ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildUnionCamp_BullSystem_Prepare));
			}
			break;
		case CampDefine::StatusEnter:
			{
				thePlayerRole.SetRedCampResource(0);
				thePlayerRole.SetBlueCampResource(0);
				s_CUI_ID_FRAME_ScoreTip.SetTime(pMsg->nLeftTime);
				s_CUI_ID_FRAME_ScoreTip.SetStringId(eText_GuildUnionCamp_TimeToCampStart);
				ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildUnionCamp_BullSystem_Enter));
			}
			break;
		case CampDefine::StatusFight:
			{
				s_CUI_ID_FRAME_ScoreTip.SetTime(pMsg->nLeftTime);
				s_CUI_ID_FRAME_ScoreTip.SetStringId(eText_GuildUnionCamp_TimeToCampEnd);
				ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildUnionCamp_BullSystem_Fight));
			}
			break;
		case CampDefine::StatusEnd:
			{
				ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildUnionCamp_BullSystem_Over));
			}
			break;
		case CampDefine::StatusRelease:
			break;
		default:
			break;
		}

		return;
	}

	//countryCamp
	if (pMsg->uchCampBattleType == CampDefine::BattleTypeKing)
	{
		switch (pMsg->uchCampBattleStatus)
		{
		case CampDefine::StatusInit:
			break;
		case CampDefine::StatusSignUp:
			{
				ShowCampBattleInfo(theXmlString.GetString(eText_KingCamp_SignUpTime));
			}
			break;
		case CampDefine::StatusPrepare:
			break;
		case CampDefine::StatusEnter:
			{
				s_CUI_ID_FRAME_KingScoreTip.SetTime(pMsg->nLeftTime);
				s_CUI_ID_FRAME_KingScoreTip.SetStringId(eText_KingCamp_TimeToCampStart);
				ShowCampBattleInfo(theXmlString.GetString(eText_KingCamp_SignUpEnd_MustBeEnterInThreeMin));
			}
			break;
		case CampDefine::StatusFight:
			{
				s_CUI_ID_FRAME_KingScoreTip.SetTime(pMsg->nLeftTime);
				s_CUI_ID_FRAME_KingScoreTip.SetStringId(eText_KingCamp_TimeToCampEnd);
				//ShowCampBattleInfo(theXmlString.GetString(eText_KingCamp_FightStart));
			}
			break;
		case CampDefine::StatusEnd:
			break;
		case CampDefine::StatusRelease:
			break;
		default:
			break;
		}
		return;
	}
	
}

// 通知阵营战场杀人
void CPlayerMgr::OnMsgGuildFightInfo(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCampBattleKillPlayer);
	MsgTellCampBattleKillPlayer* pMsg = (MsgTellCampBattleKillPlayer*)pMsg_;
	
	char szText[256] = {0};
	switch (pMsg->uchKillType)
	{
	case MsgTellCampBattleKillPlayer::TypeFirstKill:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->ustStringID), pMsg->szKillerName);
		}
		break;
	case MsgTellCampBattleKillPlayer::TypeKeepKill:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->ustStringID), pMsg->szKillerName);
		}
		break;
	case MsgTellCampBattleKillPlayer::TypeBeKill:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->ustStringID), pMsg->szKillerName, pMsg->szBeKillName);
		}
		break;
	case MsgTellCampBattleKillPlayer::TypeTotalKill:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->ustStringID), pMsg->szKillerName);
		}
		break;
	default:
		break;
	}

	ShowGuildBattleBullSystemInfo(szText);
}

// 同步战场资源分
void CPlayerMgr::OnMsgGetCampBattleResource(Msg* pMsg_)
{

	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCampBattleResource);
	MsgTellCampBattleResource* pMsg = (MsgTellCampBattleResource*)pMsg_;
	
	thePlayerRole.SetRedCampResource(pMsg->nRedResource);
	thePlayerRole.SetBlueCampResource(pMsg->nBlueResource);
	
	s_CUI_ID_FRAME_ScoreTip.SetShow();

	//用于控制公会战场的显示
	/*s_CUI_ID_FRAME_GuildBattleInfo.SetVisable(true);*/
	if ( s_CUI_ID_FRAME_GuildBattleInfo.IsVisable() )
	{
		s_CUI_ID_FRAME_GuildBattleInfo.SetData(pMsg->nRedGuildID,pMsg->nRedResource,pMsg->nRedTotleKillSum,pMsg->nRedAtterHp[0],pMsg->nRedAtterHp[1],pMsg->nRedAtterHp[2],pMsg->nRedAtterHp[3]
		,pMsg->nBlueGuildID,pMsg->nBlueResource,pMsg->nBlueTotleKillSum,pMsg->nBlueAtterHp[0],pMsg->nBlueAtterHp[1],pMsg->nBlueAtterHp[2],pMsg->nBlueAtterHp[3]);
	}
	
	//s_CUI_ID_FRAME_GuildBattleInfo.SetShowByNeed();
}

// 通知帮主, 你的帮派最后一个报名没有匹配上, 不能参加帮派争夺战
void CPlayerMgr::OnMsgSignGuildCampBattleFailed(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCampGuildBattleUnMatch);

	if (theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->GetGangPosition() == GuildDefine::Position_Master)
	{
		ShowCampBattleInfo(theXmlString.GetString(eText_GuildCamp_BullSystem_MatchNoTeam));		
	}
}

// 通知阵营战场对阵列表
void CPlayerMgr::OnMsgGetGuildCampBattleMatch(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCampBattleMatch);
	MsgTellCampBattleMatch* pMsg = (MsgTellCampBattleMatch*)pMsg_;

	switch (pMsg->uchBattleType)
	{
	case CampDefine::BattleTypeGuild:
		{
			thePlayerRole.SetRedCampGuildId(pMsg->nRedID);
			thePlayerRole.SetBlueCampGuildId(pMsg->nBlueID);
			s_CUI_ID_FRAME_ScoreTip.SetShow();
		}
		break;
	case CampDefine::BattleTypeGuildUnion:
		{
			thePlayerRole.SetRedCampGuildId(pMsg->nRedID);
			thePlayerRole.SetBlueCampGuildId(pMsg->nBlueID);
			s_CUI_ID_FRAME_ScoreTip.SetShow();
		}
		break;
	case CampDefine::BattleTypeKing:
		{
			thePlayerRole.SetRedCampGuildId(pMsg->nRedID);
			thePlayerRole.SetBlueCampGuildId(pMsg->nBlueID);
			s_CUI_ID_FRAME_KingScoreTip.SetShow();
		}
		break;
	default:
		break;
	}
}

// 通知帮派帮主, 你的报名中被其他帮派顶替了
void CPlayerMgr::OnMsgCampBattleSignUpReplace(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCampBattleSignUpReplace);
	MsgTellCampBattleSignUpReplace* pMsg = (MsgTellCampBattleSignUpReplace*)pMsg_;

	if (!(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->GetGangPosition() == GuildDefine::Position_Master))
	{
		return;
	}

	char szText[256] = {0};
	switch (pMsg->uchBattleType)
	{
	case CampDefine::BattleTypeGuild:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_SignUpReplace), theXmlString.GetString(eText_GuildCamp));
		}
		break;
	case CampDefine::BattleTypeKing:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_SignUpReplace), theXmlString.GetString(eText_CountryBattle_King));
		}
		break;
	case CampDefine::BattleTypeDragon:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_SignUpReplace), theXmlString.GetString(eText_CountryBattle_Dragon));
		}
		break;
	case CampDefine::BattleTypeRosefinch:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_SignUpReplace), theXmlString.GetString(eText_CountryBattle_Rosefinch));
		}
		break;
	case CampDefine::BattleTypeGuildUnion: 
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_SignUpReplace), theXmlString.GetString(eText_GuildUnionCamp));
		}
		break;
	default:
		break;
	}

	ShowCampBattleInfo(szText);
}

// 战场杀死怪物
void CPlayerMgr::OnMsgKillCampBattleMonster(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgKillCampBattleMonster);
	MsgKillCampBattleMonster* pMsg = (MsgKillCampBattleMonster*)pMsg_;

	if ((pMsg->uchBattleType != CampDefine::BattleTypeGuild || pMsg->uchBattleType != CampDefine::BattleTypeGuildUnion) || pMsg->nStringID == 0)
	{
		return;
	}
	
	std::string strKiller, strBeKilled; 
	if (pMsg->uchFightCamp == CampDefine::GuildCampRed)
	{
		strKiller = thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId());
		strBeKilled = thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId());
	}
	else
	{
		strBeKilled = thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId());
		strKiller = thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId());
	}
	
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->nStringID), strKiller.c_str(), strBeKilled.c_str());
	ShowGuildBattleBullSystemInfo(szText);
}

// 通知战场内玩家, 某某怪刷出来了
void CPlayerMgr::OnMsgCampGuildMonsterRefresh(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCampGuildBattleRefreshMonster);
	MsgTellCampGuildBattleRefreshMonster* pMsg = (MsgTellCampGuildBattleRefreshMonster*)pMsg_;

	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->nStringID));
	ShowGuildBattleBullSystemInfo(szText);
}

// 全国广播某个帮派获得了战场资格
void CPlayerMgr::OnMsgCountryBattleGuild(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCountryBattleGuild);
	MsgTellCountryBattleGuild* pMsg = (MsgTellCountryBattleGuild*)pMsg_;

	std::string strGuildName = thePlayerRole.GetGuildNameById(pMsg->nGuildID);
	char szText[256] = {0};
	switch (pMsg->uchBattleType)
	{
	case CampDefine::BattleTypeKing:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_CountryBattleGuild), strGuildName.c_str(), theXmlString.GetString(eText_CountryBattle_King));
		}
		break;
	case CampDefine::BattleTypeDragon:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_CountryBattleGuild), strGuildName.c_str(), theXmlString.GetString(eText_CountryBattle_Dragon));
		}
		break;
	case CampDefine::BattleTypeRosefinch:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_CountryBattleGuild), strGuildName.c_str(), theXmlString.GetString(eText_CountryBattle_Rosefinch));
		}
		break;
	}

	ShowCampBattleInfo(szText);
}

//------------------------------------------------------------------------
const int FourLive = 4;
const int ThreeLive = 3;
const int TwoLive = 2;
const int OnlyOneLive = 1;
const int ZeroLive = 0;

//当前的死亡次数
void CPlayerMgr::OnMsgTellCampBattleDeathCount(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCampBattleDeathCount);
	MsgTellCampBattleDeathCount* pMsg = (MsgTellCampBattleDeathCount*)pMsg_;

	char szText[256] = {0};
	int nLive = pMsg->nMaxCount - pMsg->nDeathCount + 1;//服务器计数与客户端计数差一
	if (nLive < 0)
	{
		return;
	}

	switch (nLive)
	{
	case FourLive:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_KingCamp_HaveFourLive));		
		}
		break;
	case ThreeLive:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_KingCamp_HaveThreeLive));		
		}
		break;
	case TwoLive:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_KingCamp_HaveTwoLive));		
		}
		break;
	case OnlyOneLive:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_KingCamp_HaveOneLive));		
		}
		break;
	case ZeroLive:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_KingCamp_HaveZeroLive));	
		}
		break;
	default:
		break;
	}

	ShowCampBattleInfo_new(szText);
}

// 发送战场队员个数, 以及帮主死亡次数 ( 红方就是守擂方, 蓝方就是抢擂方 )
void CPlayerMgr::OnMsgCountryBattlePlayerCount(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCountryBattlePlayerCount);
	MsgTellCountryBattlePlayerCount* pMsg = (MsgTellCountryBattlePlayerCount*)pMsg_;

	s_CUI_ID_FRAME_KingScoreTip.UpdateData(pMsg);
}

// 通知国家战场结果
void CPlayerMgr::OnMsgCountryBattleResult(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellCountryBattleResult);
	MsgTellCountryBattleResult* pMsg = (MsgTellCountryBattleResult*)pMsg_;

	std::string strGuildName = thePlayerRole.GetGuildNameById(pMsg->nGuildID);
	char szText[256] = {0};
	switch (pMsg->uchBattleType)
	{
	case CampDefine::BattleTypeKing:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_CountryBattleResult), strGuildName.c_str(), theXmlString.GetString(eText_CountryBattle_King));
		}
		break;
	case CampDefine::BattleTypeDragon:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_CountryBattleResult), strGuildName.c_str(), theXmlString.GetString(eText_CountryBattle_Dragon));
		}
		break;
	case CampDefine::BattleTypeRosefinch:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Camp_CountryBattleResult), strGuildName.c_str(), theXmlString.GetString(eText_CountryBattle_Rosefinch));
		}
		break;
	}

	ShowCampBattleInfo(szText);
}

void CPlayerMgr::OnMsgAddSellDataAck( Msg* pMsg )                              // 添加一个出售的物品错误信息
{
    CHECK_MSGLEN( pMsg, MsgAddSellDataAck );
    MsgAddSellDataAck* pAddSell = ( MsgAddSellDataAck* )pMsg;
    if( !pAddSell )
        return;

    CSystemStallage::Instance()->TellAddSellResult( pAddSell->uchResult );
}

void CPlayerMgr::OnMsgAddBuyDataAck( Msg* pMsg )                               // 回馈添加收购物品的错误信息
{
    CHECK_MSGLEN( pMsg, MsgAddBuyDataAck );
    MsgAddBuyDataAck* pAddBuy = ( MsgAddBuyDataAck* )pMsg;
    if( !pAddBuy )
        return;

    CSystemStallage::Instance()->TellAddBuyResult( pAddBuy->uchResult );
}

void CPlayerMgr::OnMsgStartStallAck( Msg* pMsg )                               // 回馈摆摊请求错误
{
    CHECK_MSGLEN( pMsg, MsgStartStallAck );
    MsgStartStallAck* pStartStall = ( MsgStartStallAck* )pMsg;
    if( !pStartStall )
        return;

    CSystemStallage::Instance()->TellQuestStallResult( pStartStall->uchResult );
}

void CPlayerMgr::OnMsgBuyOrSellStallAck( Msg* pMsg )                           // 回馈购买或者出售的错误
{
    CHECK_MSGLEN( pMsg, MsgBuyOrSellStallAck );
    MsgBuyOrSellStallAck* pStalling = ( MsgBuyOrSellStallAck* )pMsg;
    if( !pStalling )
        return;

    CSystemStallage::Instance()->TellErrorsInStall( pStalling->uchResult );
}

void CPlayerMgr::OnMsgUpdateStallData( Msg* pMsg )                             // 更新摊位的信息到客户端
{
    CHECK_MSGLEN( pMsg, MsgUpdateStallData );
    MsgUpdateStallData* pStallData = ( MsgUpdateStallData* )pMsg;
    if( !pStallData )
        return;

    CSystemStallage::Instance()->TellSelfStallageUpdate( pStallData );
}

void CPlayerMgr::OnMsgTellStartStall( Msg* pMsg )                              // 通知附近玩家, 某人摆摊了
{
    CHECK_MSGLEN( pMsg, MsgTellStartStall );
    MsgTellStartStall* pStartStall = ( MsgTellStartStall* )pMsg;
    if( !pStartStall )
        return;

    CSystemStallage::Instance()->TellPlayerStartStall( pStartStall->nPlayerID, pStartStall->nModelID, pStartStall->szTitle, pStartStall->blIsOffline);
}

void CPlayerMgr::OnMsgTellCloseStall( Msg* pMsg )                              // 通知附近玩家关闭摊位
{
    CHECK_MSGLEN( pMsg, MsgTellCloseStall );
    MsgTellCloseStall* pCloseStall = ( MsgTellCloseStall* )pMsg;
    if( !pCloseStall )
        return;

    CSystemStallage::Instance()->TellPlayerCloseStallage( pCloseStall->nPlayerID );
}

void CPlayerMgr::OnMsgShowStallData( Msg* pMsg )                               // 发送摊位数据到客户端
{
    CHECK_MSGLEN( pMsg, MsgShowStallData );
    MsgShowStallData* pStallData = ( MsgShowStallData* )pMsg;
    if( !pStallData )
        return;

    CSystemStallage::Instance()->TellPlayerStallageData( pStallData );
}

void CPlayerMgr::OnMsgTellBuyOrSellStallData( Msg* pMsg )                      // 通知摊主 玩家 购买 或者 出售给自己东西
{
    CHECK_MSGLEN( pMsg, MsgTellBuyOrSellStallData );
    MsgTellBuyOrSellStallData* pStallData = ( MsgTellBuyOrSellStallData* )pMsg;
    if( !pStallData )
        return;

    CSystemStallage::Instance()->AddSelfTradeRecord( pStallData );
}

void CPlayerMgr::OnMsgTellStallDataCount( Msg* pMsg )                          // 通知打开摆摊界面买卖操作的玩家
{
    CHECK_MSGLEN( pMsg, MsgTellStallDataCount );
    MsgTellStallDataCount* pStallDataCount = ( MsgTellStallDataCount* )pMsg;
    if( !pStallDataCount )
        return;

    CSystemStallage::Instance()->TellPlayerStallageCountChange( pStallDataCount->uchIndex, pStallDataCount->uchCount );
}

void CPlayerMgr::OnMsgTellStallTitleToView( Msg* pMsg )                        // 通知周围玩家某玩家的摊位标题改变了
{
    CHECK_MSGLEN( pMsg, MsgTellStallTitleToView );
    MsgTellStallTitleToView* pStallTitle = ( MsgTellStallTitleToView* )pMsg;
    if( !pStallTitle )
        return;

    CSystemStallage::Instance()->TellPlayerTitleChange( pStallTitle->ustPlayerID, pStallTitle->szTitle );
}

//保护怪位置
void CPlayerMgr::OnMsgTellProtectPetPos(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN(pMsg_, MsgProtectPetPos);
	MsgProtectPetPos* pMsg = (MsgProtectPetPos*)pMsg_;

	if (GetMe())
	{
		GetMe()->SetProtectPetPosition(pMsg->pos);
	}
}

void CPlayerMgr::OnMsgTellStallPrice( Msg* pMsg )                              // 通知摊位上某个物品价钱
{
    CHECK_MSGLEN( pMsg, MsgTellStallPrice );
    MsgTellStallPrice* pStallPrice = ( MsgTellStallPrice* )pMsg;
    if( !pStallPrice )
        return;

    CSystemStallage::Instance()->TellSelfGoodsPriceChange( pStallPrice->uchStallIndex, pStallPrice->nGameMoneyPrice, pStallPrice->nRMBMoneyPrice );
}

void CPlayerMgr::OnMsgTellTotalStallData( Msg* pMsg )                          // 通知摊主, 自己摊位上的所有信息
{
    CHECK_MSGLEN( pMsg, MsgTellTotalStallData );
    MsgTellTotalStallData* pTotalStallData = ( MsgTellTotalStallData* )pMsg;
    if( !pTotalStallData )
        return;

    CSystemStallage::Instance()->ShowSelfStallageData( pTotalStallData );
}

void CPlayerMgr::OnMsgTellServerExpModulus( Msg* pMsg )                        // 经验倍率调整广播
{
    CHECK_MSGLEN( pMsg, MsgTellServerExpModulus );
    MsgTellServerExpModulus* pExpModulus = ( MsgTellServerExpModulus* )pMsg;
    if( !pExpModulus )
        return;

    
    if( pExpModulus->nExpModulus > 100 )
    {
        char szTemp[MAX_PATH] = {0};
        MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eTell_Client_ServerExpPer ), pExpModulus->nExpModulus );
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Exp_Change, szTemp );
    }
    if( pExpModulus->nSkillExpModulus > 100 )
    {
        char szTemp[MAX_PATH] = {0};
        MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eTell_Client_ServerSkillExpPer ), pExpModulus->nSkillExpModulus );
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Exp_Change, szTemp );
    }
}

void CPlayerMgr::OnMsgUpdateQuestVar( Msg* pMsg )                               // 任务计数变量从ShowText里分离，针对服务端修改
{
    CHECK_MSGLEN( pMsg, MsgUpdateQuestVar );
    MsgUpdateQuestVar* pQuestVar = ( MsgUpdateQuestVar* )pMsg;
    if( !pQuestVar )
        return;

    ItemDefine::SMonster* monster = GettheItemDetail().GetMonsterById( pQuestVar->ustMonsterId );
    if( !monster )
        return;

    SQuest* pQuest = theQuestManager.GetQuest( pQuestVar->ustQuestId );
    if( !pQuest )
        return;

    char szTemp[MAX_PATH] = {0};
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "@%d", pQuest->QuestName );
    char* szTask = theXmlString.ParseAtString( szTemp );
    
    CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_TeamTask_Success,
        theXmlString.GetString( eClient_AddInfo_2slk_45 ), szTask );
    CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_Server_TeamTask_Success,
        "%s(%d/%d)", monster->GetName(), pQuestVar->nVar, pQuestVar->nMaxVar );
}

void CPlayerMgr::OnMsgOfflineFightOpAck( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgOfflineFightOpAck );
	MsgOfflineFightOpAck* pAutoAttack = ( MsgOfflineFightOpAck* )pMsg;
	if( !pAutoAttack )
		return;

	if( pAutoAttack->result == ER_Success )
	{
		if( pAutoAttack->op == EOfflineFightOP_Begin )
		{
			s_CUI_ID_FRAME_AutoAttackSet.BeginAutoAttack();
		}
		else if( pAutoAttack->op == EOfflineFightOP_End )
		{
			s_CUI_ID_FRAME_AutoAttackSet.EndAutoAttack();
		}
	}
	else
	{
		if( pAutoAttack->result == ER_VigorNotEnoughBeginOfflineFight )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook,
				theXmlString.GetString( eText_AutoAttack_BeginFailed_NoEnergy ) );
		}
		else if( pAutoAttack->result == ER_VigorNotEnoughOnOfflineFight )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Hook,
				theXmlString.GetString( eText_AutoAttack_End_NoEnergy ) );
		}
	}
}

void CPlayerMgr::OnMsgCharAssignPotentialAck(Msg* pMsg)
{
	MsgCharAssignPotentialAck *pAck = (MsgCharAssignPotentialAck*)pMsg;

	thePlayerRole.Update(CPlayerRole::TYPE_BasePotential,pAck->basePotential);
	for (int i = 0;i < (int)EBaseAttr_MaxSize;++i)
	{
		thePlayerRole.m_pBaseInfo->liveinfo.baseAssignValue[i] = pAck->nValue[i];
	}

	//s_CUI_ID_FRAME_PropertyDlg.ClearValue();
	s_CUI_ID_FRAME_BaseProperty.ClearValue();
	int nUsePoint = thePlayerRole.GetData(CPlayerRole::TYPE_BasePotential);
	s_CUI_ID_FRAME_BaseProperty.SetDianShuControlEnable(nUsePoint > 0);
}

void CPlayerMgr::On_MSG_CHANGEXINFA(Msg *pMsg)
{
	MsgChangeXinFa *pMyMessage = (MsgChangeXinFa *)pMsg;
	switch(pMyMessage->op)
	{
	case MsgChangeXinFa::OT_Add:
		if( pMyMessage->header.stID == GetMyID() )
		{
			if( m_pMe )
				PlayEffect( gCfg.m_szSkillLevelUpEffect, m_pMe );
			thePlayerRole.m_xinFaBag.AddXinFa(pMyMessage->xinfa.nXinFaID, pMyMessage->xinfa.nXinFaLevel);
			thePlayerRole.SetExpNotUsed(pMyMessage->nUnUsedExp);
			XinFaConfig::STalentXinFa* pXinFa = theXinFaConfig.GetXinFaByID(pMyMessage->xinfa.nXinFaID, pMyMessage->xinfa.nXinFaLevel);

			char szTemp[128] = {0};
			MeSprintf_s( szTemp,sizeof(szTemp)/sizeof(char) - 1, theXmlString.GetString(eText_ChatSkillLevelUp), pXinFa->strName.c_str(), pMyMessage->xinfa.nXinFaLevel);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szTemp );
		}
		else
		{
			CPlayer *pPlayer = FindByID( pMyMessage->header.stID );
			if (pPlayer)
				PlayEffect( gCfg.m_szSkillLevelUpEffect, pPlayer );
		}
		
		break;
	case MsgChangeXinFa::OT_Update:
		{
			if( pMyMessage->header.stID == GetMyID() )
			{
				if( m_pMe )
					PlayEffect( gCfg.m_szSkillLevelUpEffect, m_pMe );
				SCharXinFa *pXinFa = thePlayerRole.m_xinFaBag.GetXinFaByID(pMyMessage->xinfa.nXinFaID);
				assert(pXinFa != NULL);
				//检查心法数据的合法性
				++pXinFa->nXinFaLevel;
				thePlayerRole.SetExpNotUsed(pMyMessage->nUnUsedExp);
				XinFaConfig::STalentXinFa* pXinFa1 = theXinFaConfig.GetXinFaByID(pMyMessage->xinfa.nXinFaID, pMyMessage->xinfa.nXinFaLevel);

				char szTemp[128] = {0};
				MeSprintf_s( szTemp,sizeof(szTemp)/sizeof(char) - 1, theXmlString.GetString(eText_ChatSkillLevelUp), pXinFa1->strName.c_str(), pMyMessage->xinfa.nXinFaLevel);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szTemp );
			}
			else
			{
				CPlayer *pPlayer = FindByID( pMyMessage->header.stID );
				if (pPlayer)
					PlayEffect( gCfg.m_szSkillLevelUpEffect, pPlayer );
			}
			
		}
		break;
	case MsgChangeXinFa::OT_Delete:
		thePlayerRole.m_xinFaBag.RemoveXinFa(pMyMessage->xinfa.nXinFaID);
		break;

	}

	if(s_CUI_ID_FRAME_Skill_Spirit.IsVisable())
		s_CUI_ID_FRAME_Skill_Spirit.Refresh();
	if(s_CUI_ID_FRAME_SKILL_LEARN.IsVisable())
		s_CUI_ID_FRAME_SKILL_LEARN.Refresh();

	thePlayerRole.RefreshQuestDone();
}

void CPlayerMgr::On_MSG_ACKSTALLQUERY(Msg *pMsg)
{
	assert(pMsg != NULL);

	MsgAckStallQuery *pMessage = (MsgAckStallQuery *)pMsg;
	CStallQueryManager::Instance()->AddStallInfo(pMessage->xData, pMessage->nStallCount, pMessage->IsTheLast());
}

void CPlayerMgr::OnMsgGotOnOffDrome(Msg *pMsg)
{
	MsgGotOnOffDrome* pOnOffDrome = (MsgGotOnOffDrome*)pMsg;
	if ( pOnOffDrome->type == MsgGotOnOffDrome::EOnOffType_On )
	{
		CPlayer* passenger = FindByID( pOnOffDrome->riderId );
		CPlayer* driver = FindByID( pOnOffDrome->driverId );
		if ( passenger != NULL && driver != NULL )
		{
			passenger->SetCarrierState(true);
			passenger->SetCarrierPos(pOnOffDrome->pos);
			passenger->SetCarrierDriver(driver->GetID());
			passenger->SetOthersPet(true);

			driver->AddPassenger(passenger->GetID());
			driver->SetCarrierDriver(pOnOffDrome->driverId);
			//driver->SetCarrierState(true);//duorenzuoji
		}
	}
	else
	{
		CPlayer* passenger = FindByID( pOnOffDrome->riderId );
		CPlayer* driver = FindByID( pOnOffDrome->driverId );
		if ( passenger != NULL && driver != NULL )
		{
			passenger->SetCarrierState(false);
			passenger->SetOthersPet(false);
			passenger->SetCarrierDriver(-1);

			driver->RemovePassenge(passenger->GetID());

			if (passenger == GetMe())
			{
				GetMe()->DisMount();
			}

			float x = 0;
			float y = 0;
			float z = 0;
			passenger->GetPos( &x, &y, &z );
			float dir = 0.0f;
			passenger->GetDir( &dir );
			dir += D3DX_PI / 2;

			float newX = x + 2.5f * cosf(dir);
			float newY = y + 2.5f * sinf(dir);
			
			SwMap& swmap = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile()->ReachableMap();

			bool canReach = false;
			for ( int i = 0; i < 4; i ++ )
			{
				if (!swmap.CanReach( swVec2f( newX, newY ) ))
				{
					dir += D3DX_PI / 2;
					newX = x + 2.5f * cosf(dir);
					newY = y + 2.5f * sinf(dir);
				}
				else
				{
					canReach = true;
					break;
				}
			}
			if ( canReach == false )	//如果周围都是不可达，就在坐骑的下面下
			{
				newX = x;
				newY = y;
			}

			passenger->ReSetPos( newX, newY, z );
			if ( pOnOffDrome->type == MsgGotOnOffDrome::EOnOffType_ForceOff && passenger->IsRole() == TRUE /*== thePlayerRole.GetID()*/ )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString(eText_KickOffByHost) );
			}
		}
	}
}

bool VerifyInvit(char bIsTell,void *pData )
{
	MsgReqGotOnDrome* pGotOn = (MsgReqGotOnDrome*)pData;
	MsgReqGotOnDromeAck ackMsg;
	if ( bIsTell == 1 )
	{
		ackMsg.type = MsgReqGotOnDromeAck::EOperateType_Agree;
	}
	else
	{
		ackMsg.type = MsgReqGotOnDromeAck::EOperateType_Reject;
	}
	
	ackMsg.driverId = pGotOn->driverId;
	ackMsg.riderId = pGotOn->riderId;
	GettheNetworkInput().SendMsg( &ackMsg );

	return true;
}

//bool VerifyRequest(char bIsTell, void *ackMsg )
//{
//
//	return true;
//}

void CPlayerMgr::OnMsgReqGotOnDrome(Msg *pMsg)
{
	MsgReqGotOnDrome* pGotOn = (MsgReqGotOnDrome*)pMsg;

	CPlayer* driver = theHeroGame.GetPlayerMgr()->FindByID( pGotOn->driverId );
	CPlayer* rider = theHeroGame.GetPlayerMgr()->FindByID( pGotOn->riderId );

	if ( !driver || !rider )
	{
		assert(!"driver or rider is null...... ");
		return;
	}

	if ( pGotOn->type == MsgReqGotOnDrome::EOperateType_Invite )
	{
		//接到邀请
		char temp[512] = {0};
		sprintf( temp, theXmlString.GetString(eText_InviteGetOn), driver->GetName() );
		s_CUI_ID_FRAME_MessageBox.Show( temp, theXmlString.GetString(eText_MailSystemTitle), CUI_ID_FRAME_MessageBox::eTypeYesNo, true, VerifyInvit, pMsg, pMsg->GetLength() );
	}
	else
	{
		//接到请求
		char temp[512] = {0};
		sprintf( temp, theXmlString.GetString(eText_RequestGetOn), rider->GetName() );
		s_CUI_ID_FRAME_MessageBox.Show( temp, theXmlString.GetString(eText_MailSystemTitle), CUI_ID_FRAME_MessageBox::eTypeYesNo, true, VerifyInvit, pMsg, pMsg->GetLength() );
	}
}

void CPlayerMgr::OnMsgReqGotOnDromeAck(Msg *pMsg)
{
	MsgReqGotOnDromeAck* pDromeMsg = (MsgReqGotOnDromeAck*)pMsg;
	if ( pDromeMsg->type == MsgReqGotOnDromeAck::EOperateType_Reject )
	{
		//如果自己是驾驶员，拒绝就是邀请失败，如果自己不是驾驶员就是申请失败
		if ( m_pMe->IsMounting() )
		{
			CPlayer* rider = theHeroGame.GetPlayerMgr()->FindByID( pDromeMsg->riderId );
			char temp[512] = {0};
			sprintf( temp, theXmlString.GetString(eText_RejectInvite), rider->GetName() );
			s_CUI_ID_FRAME_MessageBox.Show( temp, theXmlString.GetString(eText_MailSystemTitle), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		}
		else
		{
			CPlayer* driver = theHeroGame.GetPlayerMgr()->FindByID( pDromeMsg->driverId );
			char temp[512] = {0};
			sprintf( temp, theXmlString.GetString(eText_RejectRequest), driver->GetName() );
			s_CUI_ID_FRAME_MessageBox.Show( temp, theXmlString.GetString(eText_MailSystemTitle), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		}
	}
}

void CPlayerMgr::On_MSG_SHOWSIGNATURE(Msg *pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgShowSignature);

	MsgShowSignature *msg = (MsgShowSignature*)pMsg;
	CPlayer *pPlayer = FindByID( pMsg->header.stID );
	if( pPlayer )
	{
		pPlayer->SetSignature(msg->szSignature);
		pPlayer->ShowSignature(msg->showSignature);
		pPlayer->ChangeSkeletonAndEquipAllItem(pPlayer->HasFightFlag(eFighting));
	}

	unguard;
}

void CPlayerMgr::OnMsgShowRankTitle(Msg* pMsg)
{
	MsgShowRankTitle* pShow = ( MsgShowRankTitle* )pMsg;
	CPlayer *pPlayer = FindByID( pMsg->header.stID );
	if ( pPlayer )
	{
		pPlayer->ShowRankTitle( pShow->bshowTitle );
		pPlayer->SetRankTitleId( pShow->shCurTitleId );
		pPlayer->ChangeSkeletonAndEquipAllItem(pPlayer->HasFightFlag(eFighting));
	}
}

void CPlayerMgr::On_MSG_CHANGESIGNATUREREQ(Msg *pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgChangeSignatureReq);

	MsgChangeSignatureReq *msg = (MsgChangeSignatureReq*)pMsg;
	CPlayer *pPlayer = FindByID( pMsg->header.stID );
	if( pPlayer )
	{
//		if(pPlayer->IsShowSignature())
//		{
			pPlayer->SetSignature(msg->szSignature);	
//		}

		if(s_CUI_ID_FRAME_Friend.IsVisable() && s_CUI_ID_FRAME_Friend.IsShowTypeFriend())
		{
			s_CUI_ID_FRAME_Friend.Refresh();
		}
	}

	unguard;
}

//添加更新宠物
void CPlayerMgr::OnMsgAddUpdatePet(Msg* pMsg)
{
	MsgAddUpdatePet *pPetMsg = (MsgAddUpdatePet*)pMsg;
	CHECK_MSGLEN( pMsg, MsgGetMount);
	switch(pPetMsg->type)
	{
	case MsgAddUpdatePet::OT_Add:
		{
			thePlayerRole.AddPet(pPetMsg->pet);
			thePlayerRole.RemovePetSkill(pPetMsg->pet);
			thePlayerRole.AddPetSkill(pPetMsg->pet);
			s_CUI_ID_FRAME_SuAnimal.Refresh(true);

			ItemDefine::SPetMonster *pPetMonster = NULL;
			pPetMonster = GettheItemDetail().GetPetById(pPetMsg->pet.baseInfo.petId);
			if ( pPetMonster )
			{
				if (s_CUI_ID_FRAME_SuAnimalUp.IsVisable())
				{
					s_CUI_ID_FRAME_SuAnimalUp.Refresh_Help(false);
				}
				if (s_CUI_ID_FRAME_SuAnimalMaterialUp.IsVisable())
				{
					s_CUI_ID_FRAME_SuAnimalMaterialUp.Refresh_Help(false);
				}
				if (s_CUI_ID_FRAME_SuAnimalStudy.IsVisable())
				{
					s_CUI_ID_FRAME_SuAnimalStudy.Refresh_Help(false);
				}
				if (s_CUI_ID_FRAME_SuAnimalMore.IsVisable())
				{
					s_CUI_ID_FRAME_SuAnimalMore.ShowAllPet();
				}
			}
			switch(pPetMsg->source)
			{

			case EPetSource_Other:
				{
					char szInfo[64] = {0};
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetSource_Other),pPetMsg->pet.baseInfo.szName);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case EPetSource_Skill:
				{
					char szInfo[64] = {0};
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetSource_Skill),pPetMsg->pet.baseInfo.szName);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case EPetSource_Breed:
				{
					char szInfo[64] = {0};
					if (pPetMsg->pet.baseInfo.generation ==0)
					{
						MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetSource_BabyBreed),pPetMsg->pet.baseInfo.szName);
					}
					else
					{
						MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetSource_Breed),pPetMsg->pet.baseInfo.szName);
					}
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case EPetSource_Stall:
				{
					char szInfo[64] = {0};
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetSource_Stall),pPetMsg->pet.baseInfo.szName);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			}
		}
		break;
	case MsgAddUpdatePet::OT_Update:
		{
// 			if (GetMe() && pUpdateMount->header.stID != GetMe()->GetID())
// 			{
// 				//s_CUI_ID_FRAME_SeekPet.SetVisable(true);
// 				//s_CUI_ID_FRAME_SeekPet.SetMount(pUpdateMount->mount);
// 			}
// 			else 
			{

				SPetItem* pPetItem = thePlayerRole.GetPetByGUID(pPetMsg->pet.baseInfo.guid);
				if(!pPetItem)
					return;

				bool IsNeedUpdateMode = (pPetItem->baseInfo.PetModeID == pPetMsg->pet.baseInfo.PetModeID ) ? false:true;

				memcpy(pPetItem,&pPetMsg->pet,sizeof(SPetItem));

				if (thePlayerRole.GetActivedPet() == pPetItem)
				{
					thePlayerRole.RemovePetSkill(*thePlayerRole.GetActivedPet());
					thePlayerRole.AddPetSkill(*pPetItem);
				}
				s_CUI_ID_FRAME_SuAnimal.clearTemp();
				s_CUI_ID_FRAME_SuAnimal.Refresh(true);
				s_CUI_ID_FRAME_Target.ForceUpdate();

				//当一个宠物的数据发生变化的时候 我们需要重置当前的选择
				if(s_CUI_ID_FRAME_SuAnimal.GetCurrentPet().baseInfo.guid == pPetMsg->pet.baseInfo.guid)
				{
					s_CUI_ID_FRAME_SuAnimal.UpdatePetEquipByNowSelect();
					if(IsNeedUpdateMode)
						s_CUI_ID_FRAME_SuAnimal.ChangeModel(pPetMsg->pet.baseInfo.petId);
				}
			}
		}
		break;

	}
	
	if(pPetMsg->type == MsgAddUpdatePet::OT_Add)
	{
		thePlayerRole.RefreshQuestDone();
	}
}

void CPlayerMgr:: OnMsgChangePet(Msg *pMsg)
{
	MsgChangePet* pPetMsg = (MsgChangePet*)pMsg;
	switch(pPetMsg->ucOpType)
	{
	case MsgChangePet::EOT_Active:
		{
			if (thePlayerRole.GetActivedPet())
			{
				SPetItem *pPet = thePlayerRole.GetActivedPet();
				if(pPet)
				    thePlayerRole.RemovePetSkill(*pPet);
			}

			if( thePlayerRole.GetPetByGUID(pPetMsg->guid) )
			{
				thePlayerRole.ActivePetByGUID(pPetMsg->guid);
				thePlayerRole.AddPetSkill(*thePlayerRole.GetPetByGUID(pPetMsg->guid));

				s_CUI_ID_FRAME_SuAnimal.Refresh();
				s_CUI_ID_FRAME_SuAnimal.SetPetCallIndex(pPetMsg->nIndex);		//出战的时候设置召唤的副将索引
				s_CUI_ID_FRAME_SuAnimal.RefreshButtonGroup();
				s_CUI_Group.Refeash();
				s_CUI_ID_FRAME_SuAnimalMain.SetVisable(true);
				s_CUI_ID_FRAME_SuAnimalMain.RefreshPetSkill();
			}

			s_CUI_ID_FRAME_SelectPet.Refresh(true);
		}
		break;
	case MsgChangePet::EOT_UnActive:
		{
			if (thePlayerRole.GetActivedPetGUID() == pPetMsg->guid)
			{
				SPetItem *pPet = thePlayerRole.GetActivedPet();
				if(pPet)
				    thePlayerRole.RemovePetSkill(*pPet);
				s_CUI_ID_FRAME_SuAnimal.SetPetCallIndex(-1);
				s_CUI_ID_FRAME_SuAnimal.RefreshButtonGroup();
			}
			s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable(false);
			thePlayerRole.UnactivePetByGUID(pPetMsg->guid);
			s_CUI_Group.Refeash();
			s_CUI_ID_FRAME_SuAnimalMain.SetVisable(false);
			s_CUI_ID_FRAME_Target.ForceUpdate();

			s_CUI_ID_FRAME_SelectPet.Refresh(true);
		}
		break;
// 	case MsgChangePet::EOT_Discard:
// 		{
// 			SPetItem *pPetItem = thePlayerRole.GetPetByGUID(pPetMsg->guid);
// 			if(pPetItem)
// 			{				
// 				char szInfo[256] = {0};
// 				MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetLevel), pPetItem->baseInfo.szName);					
// 				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo);
// 				
// 				if (thePlayerRole.GetActivedPetGUID() == pPetMsg->guid)
// 					thePlayerRole.RemovePetSkill(*thePlayerRole.GetActivedPet());
// 				s_CUI_Group.Refeash();
// 				thePlayerRole.RemovePetByGUID(pPetMsg->guid);
// 				s_CUI_ID_FRAME_SuAnimal.Refresh(true);
// 				if (s_CUI_ID_FRAME_SuAnimalUp.IsVisable())
// 				{
// 					s_CUI_ID_FRAME_SuAnimalUp.Refresh_Help(false);
// 				}
// 				if (s_CUI_ID_FRAME_SuAnimalMaterialUp.IsVisable())
// 				{
// 					s_CUI_ID_FRAME_SuAnimalMaterialUp.Refresh_Help(false);
// 				}
// 				if (s_CUI_ID_FRAME_SuAnimalStudy.IsVisable())
// 				{
// 					s_CUI_ID_FRAME_SuAnimalStudy.Refresh_Help(false);
// 				}
// 				if (s_CUI_ID_FRAME_SuAnimalMore.IsVisable())
// 				{
// 					s_CUI_ID_FRAME_SuAnimalMore.ShowAllPet();
// 				}
// 			}
// 		}
// 		break;
	case MsgChangePet::EOT_Disappear:
		{//宠物消失，只刷新当前受影响的界面。
			SPetItem *pPetItem = thePlayerRole.GetPetByGUID(pPetMsg->guid);
			char PetName[32] ={0};//需要先保存当前宠物名字，因为后面的操作会改变当前宠物所指的名字； 
			if (pPetItem != NULL)
			{
				strcpy(PetName,pPetItem->baseInfo.szName);
			}
			if (thePlayerRole.GetActivedPetGUID() == pPetMsg->guid)
				thePlayerRole.RemovePetSkill(*thePlayerRole.GetActivedPet());
			s_CUI_Group.Refeash();
			thePlayerRole.RemovePetByGUID(pPetMsg->guid);

			s_CUI_ID_FRAME_SuAnimal.Refresh(true);
			switch(pPetMsg->source)
			{
			case EDS_Discard: //放生而消失
				{
			
					char szInfo[64] = {0};
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetFangshengLost), PetName);			
					CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,szInfo);

				}
				break;
			case EDS_SavvyUp: //提升悟性而消失
				{
				
					char szInfo[64] = {0};
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetSavvyUpLost), PetName);			
					CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,szInfo);
	
				}
				break;
			case EDS_Breed: //繁殖而消失
				{
						
					char szInfo[64] = {0};
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetBreedLost), PetName);			
					CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,szInfo);
	
				}
				break;
			case EDS_Stall: //因交易而消失
				{
							
					char szInfo[64] = {0};
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetStallLost), PetName);			
					CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,szInfo);
		
				}
				break;
			}
			if (s_CUI_ID_FRAME_SuAnimalUp.IsVisable())
			{
				s_CUI_ID_FRAME_SuAnimalUp.Refresh_Help(false);
			}
			if (s_CUI_ID_FRAME_SuAnimalMaterialUp.IsVisable())
			{
				s_CUI_ID_FRAME_SuAnimalMaterialUp.Refresh_Help(false);
			}
			if (s_CUI_ID_FRAME_SuAnimalStudy.IsVisable())
			{
				s_CUI_ID_FRAME_SuAnimalStudy.Refresh_Help(false);
			}
			if (s_CUI_ID_FRAME_SuAnimalMore.IsVisable())
			{
				s_CUI_ID_FRAME_SuAnimalMore.ShowAllPet();
			}
		}
		break;
	default:
		break;
	}

	thePlayerRole.RefreshQuestDone();
}

void CPlayerMgr::OnMsgPetBreedReqAck(Msg *pMsg)
{
	MsgPetBreedReqAck* pPetMsg = (MsgPetBreedReqAck*)pMsg;
	switch(pPetMsg->result)
	{
	case MsgPetBreedReqAck::ER_Success:   // 开始繁殖操作
		{
			if(!s_CUI_ID_FRAME_SuAnimalMore.IsVisable())
			   s_CUI_ID_FRAME_SuAnimalMore.SetVisable(true);
		}
		break;
	case MsgPetBreedReqAck::ER_Failed:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetFailFanZhi ) );
		}
		break;
	case MsgPetBreedReqAck::ER_NoTeam:   // 您没有处于队伍中
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetNoInTeam ) );
		}
		break;
	case MsgPetBreedReqAck::ER_TeamMember:  // 您的队伍超过了2名
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetMoreTwo ) );
		}
		break;
	case MsgPetBreedReqAck::ER_TeamHeader:  // 您不是队伍的队长
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetNoLeader ) );
		}
		break;
	case MsgPetBreedReqAck::ER_TeamRange:   // 队友不在旁边
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetNoTeamer ) );
		}
		break;
	case MsgPetBreedReqAck::ER_HaveBreed:   // 已经有宠物在繁殖中
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString(eText_PetHaveFanZhi) );
		}
		break;
	}
}

void CPlayerMgr::OnMsgPetBreedChoiceAck(Msg *pMsg)
{
	MsgPetBreedChoiceAck* pPetMsg = (MsgPetBreedChoiceAck*)pMsg;
	switch(pPetMsg->result)
	{
	case MsgPetBreedChoiceAck::ER_Success:
		{
			CPlayer* pPlayer = FindByID( pPetMsg->header.stID );// 根据服务器的Id查找Player
			if(pPlayer == GetMe())//玩家是否是自己
			{
				s_CUI_ID_FRAME_SuAnimalMore.SetMyPetItem(&pPetMsg->pet);//设置自己的宠物
			}
			else
			{
				s_CUI_ID_FRAME_SuAnimalMore.SetTargetPetItem(&pPetMsg->pet);//目标设置宠物
			}
		}
		break;
	case MsgPetBreedChoiceAck::ER_Failed:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetFailSelect ) );
		}
		break;
	default:
		break;
	}
}

void CPlayerMgr::OnMsgPetBreedStatus(Msg *pMsg)
{
	MsgPetBreedStatus *pPet = (MsgPetBreedStatus*)pMsg;
	switch(pPet->status)
	{
	case EPetBreed_StatusInit:
		{

		}
		break;
	case EPetBreed_StatusStart:
		{
			CPlayer* pPlayer = FindByID( pPet->header.stID );
			if(pPlayer == GetMe())
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
					theXmlString.GetString( eText_PetTradeMySelf ) );
			}
			else
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
					theXmlString.GetString( eText_PetTradeTarget ) );
			}
		}
		break;
	case EPetBreed_StatusLock:
		{
			CPlayer* pPlayer = FindByID( pPet->header.stID );
			if(pPlayer == GetMe())
			{
				s_CUI_ID_FRAME_SuAnimalMore.SetMyLockItem(true);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
					theXmlString.GetString( eText_PetLockMySelf ) );
			}
			else
			{
				s_CUI_ID_FRAME_SuAnimalMore.SetTargetLockItem(true);
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
					theXmlString.GetString( eText_PetLockTarget ) );
			}
		}
		break;
	case EPetBreed_StatusConfirm:
		{
			CPlayer* pPlayer = FindByID( pPet->header.stID );
			if(pPlayer == GetMe())
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
					theXmlString.GetString( eText_PetConfirmMySelf ) );
			}
			else
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
					theXmlString.GetString( eText_PetConfirmTarget ) );
			}
		}
		break;
	}
}

void CPlayerMgr::OnMsgPetBreedFinish(Msg *pMsg)
{
	MsgPetBreedFinish *pPet = (MsgPetBreedFinish*)pMsg;
	s_CUI_ID_FRAME_SuAnimalMore.SetVisable(false);
	switch(pPet->nType)
	{
		// 繁殖操作结束
	case EPetBreed_FinishSuccess:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetScessFanZi ) );
		}
		break;
	case EPetBreed_FinishFailed:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetFailFanZi ) );
		}
		break;
	case EPetBreed_FinishTimeOut: 
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetTimeOutFanZi ));
		}
		break;
	case EPetBreed_FinishCancel:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetCancel ) );
			s_CUI_ID_FRAME_SuAnimalMore.ClearTargetStatus();//清除对方的数据
			s_CUI_ID_FRAME_SuAnimalMore.SetMyLockItem(false);//清除自己的锁定状态
		}
		break;
	case EPetBreed_FinishOutLine:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString(eText_PetTargetExit));
		}
		break;
	case EPetBreed_FinishHasBreed:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString(eText_TeamPlayerPeting));
		}
		break;
	}
}

void CPlayerMgr::OnMsgPetBreedCancelLock(Msg *pMsg)
{
	MsgPetBreedCancelLock *m_Msg = (MsgPetBreedCancelLock*)pMsg;
	if (m_Msg != NULL)
	{
		//只要有一方取消锁定，则也强制对方取消锁定状态,双方都可以再重新选择宠物
		CPlayer* pPlayer = FindByID( m_Msg->header.stID );
		if( pPlayer != NULL && pPlayer == GetMe())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString(eText_SelfCancelLockPet));
			  s_CUI_ID_FRAME_SuAnimalMore.SetMyLockItem(false);
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString(eText_TargetCancelLockPet));
				s_CUI_ID_FRAME_SuAnimalMore.SetTargetLockItem(false);
		}
	}
}
bool PetCostAplyCheck(char bIsTell,void *pData )
{
	if (bIsTell)
	{
		MsgPetBreedAcquire msg;
		GettheNetworkInput().SendMsg(&msg);
	}
	return true;
}

void CPlayerMgr::OnMsgPetBreedAcquireAck(Msg *pMsg)
{
	MsgPetBreedAcquireAck* pAck = (MsgPetBreedAcquireAck*)pMsg;
	switch(pAck->result)
	{
	case MsgPetBreedAcquireAck::ER_Success:
		{

		}
		break;
	case MsgPetBreedAcquireAck::ER_Failed:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetConfirmFail ) );
		}
		break;
	case MsgPetBreedAcquireAck::ER_NoBreedPet:  // 没有繁殖宠物
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetNoFanZi ) );
		}
		break;
	case MsgPetBreedAcquireAck::ER_Interval:   // 时间间隔未到
		{
			std::string str;
			char temp[64];
			GetTimeBySecond(pAck->value,str);
			MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetNoElapse),str.c_str());
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,temp);
		}
		break;
	case MsgPetBreedAcquireAck::ER_PetFull:    // 宠物栏已经满
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetNoSpace ) );
		}
		break;
	case MsgPetBreedAcquireAck::ER_TeamMember://队伍队员不正确
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetMoreTwo ) );
		}
		break;
	case MsgPetBreedAcquireAck::ER_TeamHeader://不是队长无法领取
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetNoLeader ) );
		}
		break;
	case MsgPetBreedAcquireAck::ER_NeedMoney://单人领取需要花费
		{
// 			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
// 				theXmlString.GetString( eText_PetNeedMoneySingel ) );
			char temp[32];
			MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetNeedMoneySingel),pAck->value);
			s_CUI_ID_FRAME_MessageBox.Show( temp, "",   
				CUI_ID_FRAME_MessageBox::eTypeYesNo, false, PetCostAplyCheck);

		}
		break;
	case MsgPetBreedAcquireAck::ER_NoMoney://金钱不足无法领取
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString( eText_PetNoEnoughMoney ) );
		}
		break;
	case MsgPetBreedAcquireAck::ER_PetLost:  //宠物伤心过度走了
		{
			char temp[64];
			MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetLost),pAck->pet.baseInfo.szName);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,temp);
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Server_Others_Success,temp);
		}
		break;
	case MsgPetBreedAcquireAck::ER_BreedTime:  //宠物繁殖时间到了快去领取
		{
			char temp[64];
			MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetBreedTime),pAck->pet.baseInfo.szName);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,temp);
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Server_Others_Success,temp);
		}
		break;
	case MsgPetBreedAcquireAck::ER_TargetAcquired: //队友领取了宠物
		{
			char temp[64];
			MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetTeamPlayerGet),pAck->szName);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,temp);
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Server_Others_Success,temp);
		}
		break;
	}
}


void CPlayerMgr::OnMsgRepeatedlyPet(Msg *pMsg)
{
	MsgRepeatedlyPet* pRepeat = (MsgRepeatedlyPet*)pMsg;
	if (!pRepeat)
	{
		return;
	}
	char szInfo[256];
	MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_REPEATEDLY_PET),theItemDetailConfig.GetPetTypeName(pRepeat->petType));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo);	
}

void CPlayerMgr::OnMsgCreateFamilyAck(Msg *pMsg)
{
	MsgCreateFamilyAck* msgAck = (MsgCreateFamilyAck*)pMsg;
	switch(msgAck->uchResult)
	{
	case	MsgCreateFamilyAck::ECD_Success:	// 创建成功
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family,
				theXmlString.GetString( eText_FamilyCreateSuccess ) );
		}
		break;
	case	MsgCreateFamilyAck::ECD_ErrorName:		// 存在屏蔽字符, 非法名字,
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family,
				theXmlString.GetString( eText_FamilyErrorName ) );
		}
		break;
	case	MsgCreateFamilyAck::ECD_SaveName:		// 存在相同名字的帮派
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family,
				theXmlString.GetString( eText_FamilyRepeatName ) );
		}
		break;
	case MsgCreateFamilyAck::ECD_LevelLess:			// 等级不足，不能创建家族
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family,
				theXmlString.GetString(eText_FamilyYourLevelNotEnough) );
		}
		break;
	case MsgCreateFamilyAck::ECD_NotEnoughMoney:	// 背包金钱不足，不能创建家族
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family,
				theXmlString.GetString(eText_FamilyYourMoneyNoteEnough) );
		}
		break;
	case MsgCreateGuildAck::ECD_NotCountry :
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family,
				theXmlString.GetString(eText_FamilyNotCountry) );
		}
		break;
	}
}

void CPlayerMgr::OnMsgTellFamilyInfo(Msg *pMsg)
{
	MsgTellFamilyInfo* msgInfo = (MsgTellFamilyInfo*)pMsg;

}

void CPlayerMgr::OnMsgTellCreateFmily(Msg *pMsg)
{
	MsgTellCreateFamily* msgInfo = (MsgTellCreateFamily*)pMsg;
	char tmpStr[256] = {0};
	sprintf( tmpStr, theXmlString.GetString( eText_FamilyCreateSuccessTip ), msgInfo->szPlayer, msgInfo->szName ); 
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family,
		tmpStr );
}

bool FamilyAplyCheck(char bIsTell,void *pData )
{
	if( !pData )
		return false;

	unsigned int* dbid = (unsigned int*)pData;

	MsgRequestJoinFamilyAck msg;
	msg.bAgreeJoin = bIsTell;
	msg.nPlayerID = *dbid;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

void CPlayerMgr::OnMsgRequestJoinFamilyReq(Msg *pMsg)
{
	MsgRequestJoinFamilyReq* msgReq = (MsgRequestJoinFamilyReq*)pMsg;
	//std::string tmpStr = msgReq->szRequesterName;
	//tmpStr += "申请加入家族";
	//s_CUI_ID_FRAME_MessageBox.Show( tmpStr.c_str(), "申请加入家族",   
	//	CUI_ID_FRAME_MessageBox::eTypeYesNo, true, FamilyAplyCheck, &msgReq->nRequesterID, sizeof(msgReq->nRequesterID));

	s_CUI_ID_FRAME_GUILD_FamilyMessageBox.ShowAsRequestMsgRev();
	s_CUI_ID_FRAME_GUILD_FamilyMessageBox.SetRequestPlayerInfo( msgReq->nRequesterID, msgReq->szRequesterName, msgReq->szNote );
}

bool FamilyInviteCheck(char bIsTell, void *pData )
{
	if( !pData )
		return false;

	unsigned int* familyid = (unsigned int*)pData;

	MsgInviteJoinFamilyAck msg;
	msg.bAgreeJoin = bIsTell;
	msg.nFamilyID = *familyid;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

void CPlayerMgr::OnMsgInviteJoinFamilyReq(Msg *pMsg)
{
	MsgInviteJoinFamilyReq* msgReq = (MsgInviteJoinFamilyReq*)pMsg;
	FamilyDefine::FamilySimpleInfo* info = CSystemFamily::Instance()->GetFamilySimpleInfo( msgReq->nFamilyID );
	if ( info != NULL )
	{
		char tmpStr[256] = {0};
		sprintf_s( tmpStr, 255, theXmlString.GetString( eText_FamilyInviteTip ), msgReq->szInviterName, info->GetFamilyName() );

		s_CUI_ID_FRAME_MessageBox.Show( tmpStr, theXmlString.GetString(eText_FamilyInvite),
			CUI_ID_FRAME_MessageBox::eTypeYesNo, true, FamilyInviteCheck, &msgReq->nFamilyID, sizeof(msgReq->nFamilyID));
	}

}

void CPlayerMgr::OnMsgInviteFamilyAck(Msg *pMsg)
{
	MsgInviteFamilyAck* msgAck = (MsgInviteFamilyAck*)pMsg;
	switch(msgAck->uchResult)
	{
	case MsgInviteFamilyAck::ECD_Success:        // 邀请成功
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
				theXmlString.GetString(eText_FamilyInviteAckSuccess) );
		}
		break;
	case MsgInviteFamilyAck::ECD_NotHaveFamily:       // 自己没有家族, 
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
				theXmlString.GetString(eText_FamilyInviteAckNoFamily) );
		}
		break;
	case MsgInviteFamilyAck::ECD_NotHaveRight:       // 没有邀请权限
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
				theXmlString.GetString(eText_FamilyInviteAckNoRight) );
		}
		break;
	case MsgInviteFamilyAck::ECD_NotOnLine:          // 对方不存在 或者不在线 不在线, 
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
				theXmlString.GetString(eText_FamilyInviteAckOffline) );
		}
		break;
	case MsgInviteFamilyAck::ECD_AlreadyHaveFamily:   // 对方已经有家族了
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
				theXmlString.GetString(eText_FamilyInviteAckHaveFamily) );
		}
		break;
	case MsgInviteFamilyAck::ECD_LevelLess:          // 对方等级不足20级, 不能邀请加入家族
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
				theXmlString.GetString(eText_FamilyInviteAckLevelLimit) );
		}
		break;
	case MsgInviteFamilyAck::ECD_MemberFull:         // 成员数已经满了
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
				theXmlString.GetString(eText_FamilyInviteAckFamilyFull) );
		}
		break;
	case MsgInviteFamilyAck::ECD_NotAgree:           // 拒绝加入家族
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
				theXmlString.GetString(eText_FamilyInviteAckRefuse) );
		}
		break;
	}
}

void CPlayerMgr::OnMsgFamilyAimAck(Msg *pMsg)
{
	MsgFamilyAimAck* msgAck = (MsgFamilyAimAck*)pMsg;
	if ( msgAck->uchResult == MsgFamilyAimAck::ECD_Success )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyModifyAimSucc) );
		s_CUI_ID_FRAME_GUILD_FamilyTenet.UpdateAim();
	}
	else if ( msgAck->uchResult == MsgFamilyAimAck::ECD_TimeLimit )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyOnceInWeek) );
	}
	else
	{
		//修改失败
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyModifyAimFailed) );
	}
}

void CPlayerMgr::OnMsgEquipTalismanAck(Msg* pMsg)
{
	MsgEquipTalismanAck *pAck = (MsgEquipTalismanAck*)pMsg;
	switch(pAck->stResult)
	{
	case MsgEquipTalismanAck::Result_Success:
		{
			if(m_pMe)
			{
				SCharItem stItem;
				if(!thePlayerRole.m_bag.GetItem(pAck->ustPackIndex,&stItem))
					return;

				m_pMe->EquipTalismanById(stItem.itembaseinfo.ustItemID);
				unsigned short stCount = 1;
				thePlayerRole.m_bag.PopItem(pAck->ustPackIndex, stCount, 0, 0, "" );
				s_CUI_ID_FRAME_PACK.RefreshNormalPack();
			}

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString(eText_TalismanEquipSucess) );
		}
		break;
	case MsgEquipTalismanAck::Result_Failed:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString(eText_TalismanEquipFaild) );
		}
		break;
	case MsgEquipTalismanAck::Result_DaoxingNotEnough:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString(eText_TalismanDaoHangNoEnough) );
		}
		break;
	default:
		break;
	}
}

void CPlayerMgr::OnMsgUnEquipTalismanAck(Msg* pMsg)
{
	MsgUnEquipTalismanAck* pAck = (MsgUnEquipTalismanAck*)pMsg;
	switch(pAck->result)
	{
	case MsgUnEquipTalismanAck::Result_Success:
		{
			if(m_pMe)
			{
				m_pMe->UnEquipTalisman();
				if(pAck->stPackIndex >= 0&&pAck->stPackIndex<thePlayerRole.m_bag.GetNowBagSize())
				     memcpy( &thePlayerRole.m_bag.m_pPackItem[pAck->stPackIndex], &pAck->talisman, sizeof( SCharItem) );
				s_CUI_ID_FRAME_PACK.RefreshNormalPack();
			}
		}
		break;
	case MsgUnEquipTalismanAck::Result_Failed:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,
				theXmlString.GetString(eText_TalismanUnEquipFaild) );
		}
		break;
	default:
		break;
	}
}

void CPlayerMgr::OnMsgChangeTalisman(Msg* pMsg)
{
	MsgTalismanChange *pChange = (MsgTalismanChange*)pMsg;

	CPlayer* pPlayer = FindByID(pChange->header.stID);
	if(!pPlayer)
		return;

	switch(pChange->opType)
	{
	case MsgTalismanChange::EOT_Equip:
		{
			if(pPlayer != m_pMe)
			{
				pPlayer->EquipTalismanById(pChange->nItemID);
			}
		}
		break;
	case MsgTalismanChange::EOT_UnEquip:
		{
			pPlayer->UnEquipTalisman();
		}
		break;
	default:
		break;
	}
}

void CPlayerMgr::GetTimeBySecond(int m_second,std::string &str)
{
	int ihour=0;
	int minute = 0;
	int sceond = 0;
	ihour = m_second / 3600;
	minute = (m_second - ihour * 3600) / 60;
	sceond = m_second - ihour * 3600- minute * 60;
	str.clear();
	if (ihour >0)
	{
		str += ihour + theXmlString.GetString(eTimeUnit_Hour);
	}
	if (minute>0)
	{
		str +=minute + theXmlString.GetString(eTimeUnit_Minute);
	}
	if (sceond >0)
	{
		str += sceond + theXmlString.GetString(eTimeUnit_Second);
	}
}


void CPlayerMgr::OnMsgPlayMovieReq( Msg* pMsg )
{
	CHECK_MSGLEN( pMsg, MsgPlayMovieReq );
	MsgPlayMovieReq* pPlayMovie = ( MsgPlayMovieReq* )pMsg;
	if( !pPlayMovie )
		return;

    bool bResult = CMovieManager::Instance()->OpenByType( pPlayMovie->nMovieId );
	MsgPlayMovieAck msg;
	if( bResult )
	{
		msg.dwPlayTime = pPlayMovie->dwPlayTime;
		GettheNetworkInput().SendMsg( &msg );
	}

	GetMe()->SetMoving(FALSE);
}

void CPlayerMgr::OnMsgPlayScene(Msg *pMsg)
{
	MsgScenePlay *pScenePlay = (MsgScenePlay*)pMsg;

	CPlayer* pPlayer = FindByID(pScenePlay->header.stID);
	if(!pPlayer)
		return;

	pPlayer->BeginPlaying(pScenePlay->stSceneId);
}

void CPlayerMgr::OnMsgMoviceScreen(Msg *pMsg)
{ 
	MsgBlackScreen* pScreen = (MsgBlackScreen*)pMsg;

	s_CUI_ID_FRAME_Lens.SetScreenPlay(pScreen->dwTime);
}

void CPlayerMgr::OnMsgPlayerPlayAnim(Msg* pMsg)
{
	guardfunc;
	CHECK_MSGLEN( pMsg, MsgPlayerPlayAnim);
	MsgPlayerPlayAnim* pPlayAnim = (MsgPlayerPlayAnim*)pMsg;
	CPlayer* pPlayer = FindByID( pPlayAnim->header.stID);
	if( !pPlayer )
		return;

	pPlayer->PlayAnim( pPlayAnim->szActionName,	pPlayAnim->nLoopTimes,
		pPlayAnim->szEndActionName );
	unguard;
}
void CPlayerMgr::OnMsgKillPlayerNum(Msg* pMsg)
{
	MsgKillPlayerNumAck* p = (MsgKillPlayerNumAck*)pMsg;
	if(!p) return;
	thePlayerRole.SetWeekKillSum(p->nWeekKillNum);
	thePlayerRole.SetAllKillSum(p->nAllKillNum);
	s_CUI_ID_FRAME_OtherInfo.SetKillPlayerSum(p->nAllKillNum,p->nWeekKillNum);//设置UI上的值
}
void CPlayerMgr::OnMsgConKillPlayer(Msg* pMsg)
{
	MsgConKillPlayerAck* p = (MsgConKillPlayerAck*)pMsg;
	if(!p) return;
	uint32 num = p->KillNum;
	char szText[256] = {0};
	sprintf_s(szText, sizeof(szText)-1,theXmlString.GetString(eText_KillPlayerNUM),num);	
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,szText);
	
	/*CPlayer* pMasterPlayer = FindByID(thePlayerRole.GetDBID());
	if(pMasterPlayer)
	{
		D3DXVECTOR3 pos = pMasterPlayer->GetPos();
		extern float g_fTheRoleBBoxHeight;
		pos.z += g_fTheRoleBBoxHeight;
		int x = 0, y = 0;
		World2Screen(pos, x, y);
		g_pFlyTextEffect->Create(CFlyTextEffect::eNumberAttackWhite, x, y, num, thePlayerRole.GetID(), TRUE, pos, 0, GlobalTexture::eNumber3);

		
	}*/
	//if (g_pPrintTextEffect)
	//{
	//	g_pPrintTextEffect->Create(num,CPrintTextEffect::KILLTARGET);
	//}

	if(GetMe())
	{
	GetMe()->SetHeroKilltargetNum(num);
	GetMe()->SetHeroKillChanged(true);
	}

	if(num == 50)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Kill50Player));
	}
}
void CPlayerMgr::OnMsgRemoveItemByType(Msg* pMsg)
{
	MsgRemoveItemByBagType * pRemove = (MsgRemoveItemByBagType*)pMsg;
	if(!pRemove) return;
	//根据命令里带的参数 处理客户端
	switch(pRemove->ucItemBagType)
	{
	case BT_StorageBag:
		//移除仓库指定位置的物品
		if(thePlayerRole.m_stStorage.stStorageItems[pRemove->ucIndex].itembaseinfo.ustItemID == pRemove->ustItemID)
		{
			thePlayerRole.m_stStorage.stStorageItems[pRemove->ucIndex].itembaseinfo.ustItemID = InvalidLogicNumber;
			s_CUI_ID_FRAME_Storage.Refeash();
		}
		break;
	case BT_EquipBag:
		//移除装备栏指定位置的装备
		{
			SCharItem* pVisual = NULL;
			if( pRemove->ucIndex < 0 || EEquipPartType_MaxEquitPart < pRemove->ucIndex )
				return;
			pVisual = &thePlayerRole.m_pVisual->GetVisualArray()[pRemove->ucIndex ];
			if( pVisual->itembaseinfo.ustItemID != InvalidLogicNumber && pVisual->itembaseinfo.ustItemID == pRemove->ustItemID)
			{
				pVisual->itembaseinfo.ustItemID = InvalidLogicNumber;
				s_CUI_ID_FRAME_BaseProperty.RefreshEquip();
			}
		}
		break;
	}
}
void CPlayerMgr::OnMsgGuildSQACK(Msg *pMsg)
{
	//处理公会的全部申请数据
	MsgGuildSQAck* pGSA = (MsgGuildSQAck *)pMsg;
	for(size_t i =0;i<pGSA->Num;++i)
	{
		GuildSQInfo gsi;
		gsi.ID = pGSA->Info[i].ID;
		gsi.Level = pGSA->Info[i].Level;
		gsi.Profession = pGSA->Info[i].Profession;
		strcpy_s(gsi.Name,32,pGSA->Info[i].szName);
		s_CUI_ID_FRAME_GuildSQ.AddGuildMember(gsi);
	}
	if(pGSA->Num >0)
	{
		//设置指定UI开始闪烁
		s_CUI_ID_FRAME_InfoTips.AddSQInfo();
	}
}
void CPlayerMgr::OnMsgGuildAddSQ(Msg *pMsg)
{
	//处理公会的申请
	MsgGuildAddSQReq * pMSA = (MsgGuildAddSQReq *)pMsg;
	GuildSQInfo pGuildMember;
	pGuildMember.ID =pMSA->ID;
	pGuildMember.Level =pMSA->Level;
	pGuildMember.Profession =pMSA->Profession;
	HelperFunc::SafeNCpy( pGuildMember.Name, pMSA->szName, sizeof( pGuildMember.Name ) );
	s_CUI_ID_FRAME_GuildSQ.AddGuildMember(pGuildMember);
	//设置指定UI开始闪烁
	s_CUI_ID_FRAME_InfoTips.AddSQInfo();
}
void CPlayerMgr::OnMsgGuildDElSQ(Msg *pMsg)
{
	//处理公会的申请
	MsgGuildDelSQReq * pMSA = (MsgGuildDelSQReq *)pMsg;
	s_CUI_ID_FRAME_GuildSQ.DelGuildMember(pMSA->ID);
}
void CPlayerMgr::OnMsgFlyMap(Msg *pMsg)
{
	MsgCountryFlyMap * pFly = (MsgCountryFlyMap*)pMsg;
	//设置弹出显示框
	switch(pFly->uchType)
	{
	case 1:
		s_CUI_ID_FRAME_InfoTips.ADdQuestFlyGY();
		break;
	case 2:
		s_CUI_ID_FRAME_InfoTips.ADdQuestFlyGT();
		break;
	case 3:
		s_CUI_ID_FRAME_InfoTips.ADdQuestFlyBS();
		break;
	case 4:
		s_CUI_ID_FRAME_InfoTips.ADdQuestFlyHL();
		break;
	}
}

void CPlayerMgr::OnMsgPlatformModifyError(Msg* pMsg)
{
	MsgPlatformError* pError = (MsgPlatformError*)pMsg;
	if (!pError)
	{
		return;
	}
	switch(pError->_result)
	{
	case eError_ActivitySucc:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_ActivitySucc), theXmlString.GetString(eText_PlatformCaption), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		break;
	case eError_NoActivity:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NoActivity), theXmlString.GetString(eText_PlatformCaption), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		break;
	case eError_SNError:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SNError), theXmlString.GetString(eText_PlatformCaption), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		break;
	case eError_AccountError:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_AccountError), theXmlString.GetString(eText_PlatformCaption), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		break;
	case eError_CharacterError:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_CharacterError), theXmlString.GetString(eText_PlatformCaption), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		break;
	case eError_PresentSucc:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_PresentSucc), theXmlString.GetString(eText_PlatformCaption), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		break;
	case eError_EpistarPointSucc:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_EpistarPointSucc), theXmlString.GetString(eText_PlatformCaption), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		break;
	case eError_EpistarPointError:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_EpistarPointError), theXmlString.GetString(eText_PlatformCaption), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		break;
	default:
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Unkown), theXmlString.GetString(eText_PlatformCaption), CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
		break;
	}
	
}
void CPlayerMgr::OnMsgWorldBattle(Msg* pMsg)
{
	MsgCampWorldBattleAck* pWB = (MsgCampWorldBattleAck*)pMsg;
	thePlayerRole.SetWorldBattleCountryID(pWB->GlobalDBCOuntryID);//设置好国家
	//客户端的提示信息
	switch(pWB->uchResult)
	{
	case MsgCampWorldBattleAck::WBD_Prepare:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_WorldBattle_Prepare));
		}
		break;
	case MsgCampWorldBattleAck::WBD_Fight:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_WorldBattle_Fight));
		}
		break;
	case MsgCampWorldBattleAck::WBD_End:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_WorldBattle_End));
		}
		break;
	}
}
void CPlayerMgr::OnMsgBattleSum(Msg* pMsg)
{
	MsgGetGlobalDBBattleSumAck* pWB = (MsgGetGlobalDBBattleSumAck*)pMsg;
	if(!pWB) return;
	int Sum = pWB->Sum;
	s_CUI_ID_FRAME_CampBattleGuildUnion.SetGuildUnionSum(Sum);
}
void CPlayerMgr::OnMonsterBeLong(Msg* pMsg)
{
	MsgMonsterBeLongID * pBl = (MsgMonsterBeLongID*)pMsg;
	if(!pBl) return; 
	uint32 MonsterID = pBl->MonsterID;
	uint32 BeLongID = pBl->BeLongID;
	//设置指定怪物的归属
	CPlayer* pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByID(MonsterID);
	if(!pTargetPlayer) return;
	pTargetPlayer->SetBeLongID(BeLongID);//设置怪物的归属
}
void CPlayerMgr::OnMonsterNurtureInfo(Msg* pMsg)
{
	MsgMonsterNurtureInfo * pBl = (MsgMonsterNurtureInfo*)pMsg;
	if(!pBl) return; 
	switch(pBl->InfoID)
	{
	case MsgMonsterNurtureInfo::IS_BuffFiled:
		{
			//提示玩家副将不可以添加BUFF
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MonsterNurtureInfo_Buff));
		}
		break;
	}
}

void CPlayerMgr::OnMsgSendMessageEnd(Msg* pMsg)
{
	MsgMailListReq msg;
	GettheNetworkInput().SendMsg(&msg);
}
extern bool ChangeMapServerBusy( const char bPressYesButton, void *pData );
void CPlayerMgr::OnMsgChangeMapTimeStepReq(Msg* pMsg)
{
	MsgChangeMapTimeStepReq * pBl = (MsgChangeMapTimeStepReq*)pMsg;
	if(!pBl) return; 
	if(pBl->IsOpen)
	{
		s_CUI_ID_FRAME_MessageBox.Show(
        theXmlString.GetString(eText_WaitForChangeMap),
            theXmlString.GetString(eText_WaitForChangeMap),
            CUI_ID_FRAME_MessageBox::eTypeConfirm,
            true,
            ChangeMapServerBusy );
        s_CUI_ID_FRAME_MessageBox.SetAutoClose(pBl->TimeStep/1000);
		s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(false);
		s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(false);
		s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false);
        UiDrawer::StartFillFullScreen( 500, true ); // 屏幕变黑
        thePlayerRole.SetShowingWaitforTransport(true);
	}
}
void CPlayerMgr::OnMsgTellClientLeaveTeam(Msg* pMsg)
{
	MsgTellClientLeaveTeam * pTCL = (MsgTellClientLeaveTeam *)pMsg;
	if(!pTCL)
		return;
	if(pTCL->Result)
	{	
		//提示用户多少秒后离开队伍
		int Sec = pTCL->TimeStep/1000;
		char Text[256];
		sprintf_s(Text,255,theXmlString.GetString(eText_LeaveTeam),Sec);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,Text);
	}
	else
	{
		//提示用户已经回到区域 离开队伍取消
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_NonLeaveTeam));
	}
}
void CPlayerMgr::OnMsgGuildClientUpdate(Msg* pMsg)
{
	MsgGuildClientUpdate * pTCL = (MsgGuildClientUpdate *)pMsg;
	if(!pTCL)
		return;
	unsigned int GuildID = pTCL->ClientInfo.GetID();
	CGuildInfo* pGuildIndo = const_cast<CGuildInfo*>(thePlayerRole.GetGuildById(GuildID));
	if(!pGuildIndo)
		return;
	pGuildIndo->SetID(pTCL->ClientInfo.GetID());
	pGuildIndo->SetMemberNum(pTCL->ClientInfo.GetMemberNum());
	pGuildIndo->SetCountry(pTCL->ClientInfo.GetCountry());
	pGuildIndo->SetLevel(pTCL->ClientInfo.GetLevel());
	pGuildIndo->SetName(pTCL->ClientInfo.GetName());
	pGuildIndo->SetMasterName(pTCL->ClientInfo.GetMasterName());
}
void CPlayerMgr::OnMsgChangePetDuration(Msg* pMsg)
{
	MsgChangePetDuration * pTCL = (MsgChangePetDuration *)pMsg;
	if(!pTCL)
		return;
	unsigned int Value = pTCL->Value;
	thePlayerRole.SetPetDuration(Value);
	s_CUI_ID_FRAME_BaseProperty.UpdatePetPoint();
}
void CPlayerMgr::OnChangePlayerMode(Msg* pMsg)
{
	//修改客户端指定怪物的模型
	MsgUpdatePetMode * pMode = (MsgUpdatePetMode *)pMsg;
	if(!pMode)
		return;
	CPlayer * pPlayer = FindByID(pMode->header.stID);
	if(!pPlayer)
		return;
	if(pPlayer->IsPlayer())
		return;
	uint32 ModeID = pMode->ModeID;
	if(ModeID == 0)
	{
		//将模型还原到配置文件的模型
		ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById(pPlayer->GetMonsterID());
		if (pPetMonster == NULL)
			return;
		ModeID = pPetMonster->iModelID;
	}
	if(ModeID == 0)
		return;
	//修改指定对象的模型
	pPlayer->SetModelId((short)ModeID);
	pPlayer->GetAnim()->ChangeModel(ModeID,TRUE,NULL);
	//更新UI
	s_CUI_Group.Refeash();
	s_CUI_ID_FRAME_Group_Me.Refeash();
}
void CPlayerMgr::OnMsgTellLeaveEctype(Msg* pMsg)
{
	MsgTellLeaveEctype* pLeave = (MsgTellLeaveEctype*)pMsg;
	if (!pLeave)
		return;

	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FamilyEx,theXmlString.GetString(pLeave->nStringID));
}

void CPlayerMgr::OnMsgTellUseItem(Msg* pMsg)
{
	MsgTellUseItem* pUse = (MsgTellUseItem*) pMsg;
	if (!pUse || pUse->ustItemId == 0)
		return;

	s_CUI_ID_FRAME_UseItem.SetVisable( true );
	s_CUI_ID_FRAME_UseItem.SetItem( pUse->ustItemId );
}

void CPlayerMgr::OnMsgUpdateCard(Msg* pMsg)
{
	MsgUpdateCard* pCard = (MsgUpdateCard*)pMsg;
	if ( !pCard || pCard->stCardID < 0 || pCard->stCardID >= More_nCardMax || pCard->stLevel < 0 )
		return;

	short level = thePlayerRole.GetCharInfo2().otherdataclient.cards.shCardLevel[pCard->stCardID];
	if ( level != -1 && level >= pCard->stLevel )
		return;
	
	thePlayerRole.GetCharInfo2().otherdataclient.cards.shCardLevel[pCard->stCardID] = pCard->stLevel;

	if ( s_CUI_ID_FRAME_CARD.IsVisable() )
		s_CUI_ID_FRAME_CARD.Refresh();

	s_CUI_ID_FRAME_MiniMap.SetCardTextShow(true);
}

void CPlayerMgr::OnMsgCardAchieve(Msg* pMsg)
{
	MsgCardAchieveAck* pCard = (MsgCardAchieveAck*)pMsg;
	if ( !pCard || pCard->stAchieveId < 0 || pCard->stAchieveId >= More_nCardAchieve )
		return;

	thePlayerRole.GetCharInfo2().otherdataclient.cards.unCardAchieve[pCard->stAchieveId] = 1;

	if ( s_CUI_ID_FRAME_CARD.IsVisable() )
		s_CUI_ID_FRAME_CARD.Refresh();
}
void CPlayerMgr::OnMsgCampGuildBattleRewardInfo(Msg* pMsg)
{
	//设置工会战的结果
	MsgCampGuildBattleRewardInfo * result = (MsgCampGuildBattleRewardInfo *)pMsg;
	if(!result)
		return;
	s_CUI_ID_FRAME_GuildBattleResult.SetVisable(true);
	s_CUI_ID_FRAME_GuildBattleResult.SetData(result);
	//s_CUI_ID_FRAME_GuildBattleResult.SetShowByNeed();
}
void CPlayerMgr::OnMsgCampBattleSignUpSecc(Msg* pMsg)
{
	//返回配对结果
	MsgCampBattleSignUpSecc * pSecc = (MsgCampBattleSignUpSecc *)pMsg;
	if(!pSecc)
		return;
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildBattle_Secc));
}
void CPlayerMgr::OnMsgCampBattleCheckCampBattleValueSum(Msg* pMsg)
{
	//准备后开始战斗
	MsgCampBattleCheckCampBattleValueSum * pCB = (MsgCampBattleCheckCampBattleValueSum*)pMsg;
	if(!pCB)
		return;
	char Info[128];
	if(pCB->bulelose != pCB->redlose)
	{
		if(pCB->bulelose)
		{
			sprintf_s(Info,127,theXmlString.GetString(eText_GuildBattle_OneLose),thePlayerRole.GetGuildNameById(pCB->redguildid),thePlayerRole.GetGuildNameById(pCB->blueguildid) );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,Info);
		}
		else
		{
			sprintf_s(Info,127,theXmlString.GetString(eText_GuildBattle_OneLose),thePlayerRole.GetGuildNameById(pCB->blueguildid),thePlayerRole.GetGuildNameById(pCB->redguildid));
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,Info);
		}
	}
	else
	{
		sprintf_s(Info,127,theXmlString.GetString(eText_GuildBattle_TwoLose),thePlayerRole.GetGuildNameById(pCB->redguildid),thePlayerRole.GetGuildNameById(pCB->blueguildid));
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,Info);
	}
}	

void CPlayerMgr::OnMsgSevenDaysDataAck(Msg* pMsg)
{
	MsgSevenDaysDataAck* pAck = (MsgSevenDaysDataAck*)pMsg;
	if (!pAck)
		return;

	for(int i = 0; i < MsgSevenDaysDataAck::DL_Max; i++)
	{
		thePlayerRole.m_taskState[i] = pAck->taskState[i];
		thePlayerRole.m_taskVar[i] = pAck->taskVar[i];
	}

	//s_CUI_ID_FRAME_SevenDays_Task.SetVisable( true );
	if ( thePlayerRole.m_taskState[SevenDaysConfig::TD_SeventhDay] == 4 )
		s_CUI_ID_FRAME_SevenDaysButton.SetVisable( false );
	else
		s_CUI_ID_FRAME_SevenDaysButton.SetVisable( true );
}

void CPlayerMgr::OnMsgFreshStateVar(Msg* pMsg)
{
	MsgFreshSevenDayState* pFresh = (MsgFreshSevenDayState*)pMsg;
	if (!pFresh)
		return;

	if ( pFresh->stateIndex >= SevenDaysConfig::TD_FirstDay && pFresh->stateIndex <= SevenDaysConfig::TD_SeventhDay )
	{
		thePlayerRole.m_taskState[pFresh->stateIndex] = pFresh->state;

		if ( ( pFresh->state == 3 || pFresh->state == 1) && !s_CUI_ID_FRAME_SevenDays_Task.IsVisable() )
			s_CUI_ID_FRAME_SevenDaysButton.SetShowText();
	}

	if ( pFresh->varIndex >= SevenDaysConfig::TD_FirstDay && pFresh->varIndex <= SevenDaysConfig::TD_SeventhDay )
		thePlayerRole.m_taskVar[pFresh->varIndex] = pFresh->var;

	if ( s_CUI_ID_FRAME_SevenDays_Task.IsVisable() )
		s_CUI_ID_FRAME_SevenDays_Task.Refresh();
}

void CPlayerMgr::OnMsgTriggerSevenDays(Msg* pMsg)
{
	MsgTriggerSevenDays* pTrigger = (MsgTriggerSevenDays*)pMsg;
	if (!pTrigger)
		return;

	thePlayerRole.GetCharInfo2().otherdataclient.sevenDayStartTime = pTrigger->triggerTime;

	s_CUI_ID_FRAME_SevenDaysButton.SetVisable(true);
	s_CUI_ID_FRAME_SevenDaysButton.SetShowText();
}

void CPlayerMgr::OnMsgAskSevenDaysTaskAck(Msg* pMsg)
{
	MsgAskSevenDaysTaskAck* pAck = (MsgAskSevenDaysTaskAck*)pMsg;
	if (!pAck)
		return;

	if ( pAck->result == MsgAskSevenDaysTaskAck::R_Sucess )
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Success,theXmlString.GetString(eText_SevenDays_GetTask_Sucess));
	else
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed,theXmlString.GetString(eText_SevenDays_GetTask_Fail));
}
void CPlayerMgr::OnMsgChangeGuldNameAck(Msg* pMsg)
{
	MsgChangeGuldNameAck* pAck = (MsgChangeGuldNameAck*)pMsg;
	if (!pAck)
		return;
	if(!pAck->IsCanChange)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_GuildChangeName_Error5 ) );
		return;
	}
	//有一个公会修改改名称 
	CGuildInfo* pGuild = const_cast<CGuildInfo*>(thePlayerRole.GetGuildById(pAck->GuildID));
	if(!pGuild)
		return;
	pGuild->SetName(pAck->Name);//设置好名称
	if(thePlayerRole.GetGangMgr()->GetGuildID() == pAck->GuildID)
	{
		//自己所在的公会
		//1.修改公会UI上的值
		thePlayerRole.GetGangMgr()->SetGuildName(pAck->Name);
		s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
		s_CUI_ID_FRAME_GuildChangeName.SetVisable(false);
	}
}

void CPlayerMgr::OnMsgSelectChannel(Msg* pMsg)
{
	MsgChannelInfo* pMessage = (MsgChannelInfo*)pMsg;
	if (!pMessage)
	{

		return;
	}
	//todo:接受到频道即分线信息,要选择
	/*SChannelInfo* pChannelInfo = pMessage->GetChannelInfo(0);
	if (!pChannelInfo)
	{
		return;
	}
	CheckChannel(pChannelInfo);*/

	s_CUI_ID_FRAME_SelectChannel.AddChannelInfo( pMessage );
	s_CUI_ID_FRAME_SelectChannel.SetChannelInfoOpen( false );

	if ( s_CUI_ID_FRAME_SelectChannel.GetLastChannelIndex() == -1 )
	{
		/*s_CUI_ID_FRAME_SelectChannel.SetVisable( true );*/
		//选择人最少的
		s_CUI_ID_FRAME_SelectChannel.SelectTheRightChannel();
	}
	else
		s_CUI_ID_FRAME_SelectChannel.SelectChannelRandom( s_CUI_ID_FRAME_SelectChannel.GetLastChannelIndex() );
}

bool CPlayerMgr::CheckChannel(SChannelInfo* pChannelInfo)
{
	if (!pChannelInfo)
	{
		return false;
	}
	MsgSelectChannel channel;
	strncpy_s( channel.channel.szChannelName, pChannelInfo->szChannelName, sizeof(channel.channel.szChannelName));
	channel.channel.nServerId = pChannelInfo->nServerId;
	channel.nAccountId = m_dwAccountID;
	GettheNetworkInput().SendMsg(&channel);
	return true;
}

void CPlayerMgr::ChangeChannel( int32 serverId )
{
	if ( serverId < 0 )
		return;

	MsgChangeChannelREQ msg;
	msg.nTargetServerId = serverId;
	GettheNetworkInput().SendMsg(&msg);
}

void CPlayerMgr::OnMsgChangeChannelAck(Msg* pMsg)
{
	MsgChangeChannelACK* pAck = (MsgChangeChannelACK*)pMsg;
	if ( !pAck )
		return;

	int nStrId = -1;

	switch ( pAck->uResult )
	{
	case eChangeChannelRet_Error:
		nStrId = eText_eChangeChannelRet_Error;
		break;
	case eChangeChannelRet_Same:
		nStrId = eText_eChangeChannelRet_Same;
		break;
	case eChangeChannelRet_Dead:
		nStrId = eText_eChangeChannelRet_Dead;
		break;
	case eChangeChannelRet_Fight:
		nStrId = eText_eChangeChannelRet_Fight;
		break;
	default:
		break;
	}

	if ( pAck->uResult == eChangeChannelRet_Succ )
	{
		s_CUI_ID_FRAME_ChannelInfo.ShowChannelName();
	}

	if ( nStrId != -1 )
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( nStrId ) );
}
void CPlayerMgr::OnMsgTellCountryPlayerRaiseItem(Msg *pMsg)
{
	MsgTellCountryPlayerRaiseItem * pMsgRaisa = (MsgTellCountryPlayerRaiseItem *)pMsg;
	char szTemp[256];
	sprintf_s(szTemp,255,theXmlString.GetString(eClient_CountryRaiseItem),CountryFunction::GetDefaultCountryNameById(pMsgRaisa->CountryID).c_str(),pMsgRaisa->szName);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,szTemp);
}
void CPlayerMgr::OnMsgTellGuildPlayerRaiseItem(Msg *pMsg)
{
	MsgTellGuildPlayerRaiseItem * pMsgRaisa = (MsgTellGuildPlayerRaiseItem *)pMsg;
	char szTemp[256];
	sprintf_s(szTemp,255,theXmlString.GetString(eClient_GuildRaiseItem),CountryFunction::GetDefaultCountryNameById(pMsgRaisa->CountryID).c_str(),pMsgRaisa->szName);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,szTemp);
}
void CPlayerMgr::OnMsgClearTeamMapAck(Msg* pMsg)
{
	//告诉玩家 有队员在副本 导致部分副本无法重置
	MsgClearTeamMapAck * pAck = (MsgClearTeamMapAck *)pMsg;
	if(!pAck->Result)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_ClearTeam_TeamMemberError));
		s_CUI_ID_FRAME_Team.Clear_Time = 0;
	}
	else
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_ClearTeam_TeamMemberSucc));	

	return;
}

void CPlayerMgr::OnMsgAskGetSalaryAck(Msg* pMsg)
{
	MsgAskGetSalaryAck* pAck = ( MsgAskGetSalaryAck* )pMsg;
	if ( !pAck )
		return;

	thePlayerRole.GetCharInfo2().otherdataclient.rankTitle.bGetSalary = pAck->bGet;

	if ( s_CUI_ID_FRAME_RankTitle.IsVisable() )
		s_CUI_ID_FRAME_RankTitle.Refresh();
}

void CPlayerMgr::OnMsgAskAdvancementAck(Msg* pMsg)
{
	MsgAskAdvancementAck* pAck = ( MsgAskAdvancementAck* )pMsg;
	if ( !pAck )
		return;

	if ( !pAck->bResult )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed,theXmlString.GetString(eText_Advancement_Fail));
		return;
	}

	thePlayerRole.GetCharInfo2().otherdataclient.rankTitle.shCurRankTitleId = pAck->shCurTitleId;
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Success,theXmlString.GetString(eText_Advancement_Succeed));

	if ( s_CUI_ID_FRAME_RankTitle.IsVisable() )
		s_CUI_ID_FRAME_RankTitle.Refresh();

	if ( theHeroGame.GetPlayerMgr()->GetMe()->IsShowRankTitle() )
		s_CUI_ID_FRAME_RankTitle.ID_BUTTON_ShowTitleOnButtonClick(NULL);
}

void CPlayerMgr::OnMsgAddCountryInfoReq(Msg* pMsg)
{
	CHECK_MSGLEN( pMsg, MsgAddCountryInfoReq );
	MsgAddCountryInfoReq* pNoticeChangeAckMsg = ( MsgAddCountryInfoReq* )pMsg;
	if( !pNoticeChangeAckMsg )
		return;
	s_CUI_ID_FRAME_BaseInfo.OnAddCountryInfo(pNoticeChangeAckMsg->szNotice,pNoticeChangeAckMsg->Time,pNoticeChangeAckMsg->Value);
}
void CPlayerMgr::OnMsgLoadCountryInfoAck(Msg* pMsg)
{
	CHECK_MSGLEN( pMsg, MsgLoadCountryInfoAck );
	MsgLoadCountryInfoAck* pNoticeChangeAckMsg = ( MsgLoadCountryInfoAck* )pMsg;
	if( !pNoticeChangeAckMsg )
		return;
	//加载国家的全部信息
	s_CUI_ID_FRAME_BaseInfo.OnLoadCountryInfo(pNoticeChangeAckMsg);
}
void CPlayerMgr::OnMsgLoadQuestEntrustDataAck(Msg* pMsg)
{
	//加载全部的数据
	MsgLoadQuestEntrustDataAck* pLoad = ( MsgLoadQuestEntrustDataAck* )pMsg;
	s_CUI_ID_FRAME_QuestEntrust.LoadAllQuestEntrust(&pLoad->List[0],pLoad->Sum);
	if(pLoad->IsEnd)
		s_CUI_ID_FRAME_QuestEntrust.SetIsNeedClear();
}
void CPlayerMgr::OnMsgQuestEntrustNeedUpdate(Msg* pMsg)
{
	MsgQuestEntrustNeedUpdate* pUpdate = ( MsgQuestEntrustNeedUpdate* )pMsg;
	s_CUI_ID_FRAME_QuestEntrust.NeedGetAllData();
}

void CPlayerMgr::OnMsgReconnectAck(Msg* pMsg)
{
	MsgReConnectAck* pReCA = (MsgReConnectAck*)pMsg;
	uint16 nResult = MsgReConnectAck::ERR_ErrorPos2;
	if(pReCA)
	{
		nResult = pReCA->nResult;
	}
	switch (nResult)
	{
	case MsgReConnectAck::ERR_Success:
		break;
	default:
		GettheNetworkInput().Close();
		CUI_ID_FRAME_LOGIN::m_bNeedAckAgain = false;
		break;
	}
}

void CPlayerMgr::OnMsgReconnectResetState(Msg* pMsg)
{
	MsgReconnectResetState* pState = (MsgReconnectResetState*)pMsg;

	if (!pState||pState->header.stID != m_pMe->GetID())
	{
		return;
	}

	switch (pState->reset_state)
	{
	case MsgReconnectResetState::eResetState_death:
		//重新做一下死亡状态做的事情
		{
			theHeroGame.GetPlayerMgr()->SetLockNpc(-1);
			s_CUI_ID_FRAME_Target.SetPlayer(-1);

			// 主角攻击目标死亡，主角设成CAS_NOT_ATTACK状态
			g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;

			m_pMe->OnClearAllBodyStatusByDead();
			m_pMe->SetCharDead( TRUE );

			s_CUI_NpcTaskDialogBox.SetNpc(-1);
			theHeroGame.GetPlayerMgr()->SetLockNpc( -1 );
			s_CUI_ID_FRAME_MessageBox.closeAll( false );
			s_CUI_ID_FRAME_PrivateShop.SetVisable(false);
			s_CUI_InputBox.ID_BUTTON_CANCELOnButtonClick(NULL);
			s_CUI_ID_FRAME_Bargaining.SetVisable(false);

			m_pMe->SetHPInfo_HP(0);
			thePlayerRole.SetPlayerHP(0);
			m_pMe->SwitchDieAnim();
		}
		break;
	default:
		break;
	}
}
void CPlayerMgr::OnMsgGuildChangeNameAck(Msg* pMsg)
{
	//修改客户端公会的数据
	MsgGuildChangeNameAck* pCN = (MsgGuildChangeNameAck*)pMsg;
	if(!pCN)
		return;
	if(thePlayerRole.GetGangMgr() && thePlayerRole.GetGangMgr()->GetGuildID() == pCN->GuildID)
	{
		GuildMember* pMember =  thePlayerRole.GetGangMgr()->FindByDBId(pCN->PlayerID);
		if(!pMember || thePlayerRole.GetGangMgr()->GetGuildMasterID() == pCN->PlayerID)
		{
			//需要修改公会的信息的名称	
			CGuildInfo*  pInfo =const_cast<CGuildInfo*>(thePlayerRole.GetGuildById(pCN->GuildID));
			if(!pInfo)
				return;
			pInfo->SetMasterName(pCN->szName);
			if(!pMember)
				return;
		}
		pMember->SetName(pCN->szName);
	}
	else
	{
		CGuildInfo*  pInfo =const_cast<CGuildInfo*>(thePlayerRole.GetGuildById(pCN->GuildID));
		if(!pInfo)
			return;
		pInfo->SetMasterName(pCN->szName);
	}
	//更新UI
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
}
void CPlayerMgr::OnMsgRelationUpdateNameAck(Msg* pMsg)
{
	//客户端的 关系数据需要进行更新
	MsgRelationUpdateNameAck * pAck = (MsgRelationUpdateNameAck *)pMsg;
	if(!pAck)
		return;
	std::map<int, RelationDataToClient>& pMap = thePlayerRole.GetMapFriendInfo();
	if(pMap.count(pAck->PlayerID) != 1)
		return;
	RelationDataToClient& pInfo = pMap[pAck->PlayerID];
	pInfo.SetName(pAck->szName);//修改名称
	//刷新UI
	s_CUI_ID_FRAME_Friend.NeedRefresh();
}

void CPlayerMgr::OnMsgHuntingQuestList(Msg* pMsg)
{
	MsgHuntingQuestList* pList = (MsgHuntingQuestList*)pMsg;
	if ( !pList )
		return;

	for ( int i = 0; i < MaxCount_Show; i++ )
	{
		thePlayerRole.GetCharInfo2().otherdataclient.sHunting.nCurRandIds[i] = pList->nIds[i];
	}

	thePlayerRole.GetCharInfo2().otherdataclient.sHunting.dFreeRefreshTime = pList->dwTime;
	thePlayerRole.GetCharInfo2().otherdataclient.sHunting.nCount = pList->nCount;

	s_CUI_ID_FRAME_Hunting.SetLeftTime( pList->nLeftTime );
	s_CUI_ID_FRAME_Hunting.SetStartTime( timeGetTime() );

	if ( s_CUI_ID_FRAME_Hunting.IsVisable() )
		s_CUI_ID_FRAME_Hunting.Refresh();
}
void CPlayerMgr::OnMsgTellGameBattleStatus(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellGameBattleStatus);
  	MsgTellGameBattleStatus* pMsg = (MsgTellGameBattleStatus*)pMsg_;
	char szText[256] = {0};
	if (pMsg->uchCampBattleType == GameBattleDefine::GameBattle_Type_GuildGeneral)
	{
		switch (pMsg->uchCampBattleStatus)
		{
		case GameBattleDefine::StatusInit:
			break;
		case GameBattleDefine::StatusEnter:
			{
				thePlayerRole.SetRedCampResource(0);
				thePlayerRole.SetBlueCampResource(0);
				s_CUI_ID_FRAME_ScoreTip.SetTime(pMsg->nLeftTime);
				if(s_CUI_ID_FRAME_ScoreTip.GetStringId() != eText_GuildGeneral_TimeToGameBattleStart)
					ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildGeneral_BullSystem_Enter));
				s_CUI_ID_FRAME_ScoreTip.SetStringId(eText_GuildGeneral_TimeToGameBattleStart);
			}
			break;
		case GameBattleDefine::StatusFight:
			{
				s_CUI_ID_FRAME_ScoreTip.SetTime(pMsg->nLeftTime);
				if(s_CUI_ID_FRAME_ScoreTip.GetStringId() != eText_GuildGeneral_TimeToGameBattleEnd)
					ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildGeneral_BullSystem_Fight));
				s_CUI_ID_FRAME_ScoreTip.SetStringId(eText_GuildGeneral_TimeToGameBattleEnd);
			}
			break;
		case GameBattleDefine::StatusEnd:
			{
				ShowGuildBattleBullSystemInfo(theXmlString.GetString(eText_GuildGeneral_BullSystem_Over));
			}
			break;
		case GameBattleDefine::StatusRelease:
			break;
		default:
			break;
		}

		return;
	}
}
void CPlayerMgr::OnMsgShowGameGuildBattleEnter(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgShowGameGuildBattleEnter);
	MsgShowGameGuildBattleEnter* pMsg = (MsgShowGameGuildBattleEnter*)pMsg_;

	thePlayerRole.SetRedCampGuildId(pMsg->nRedGuildID);
	thePlayerRole.SetBlueCampGuildId(pMsg->nBlueGuildID);
	return;
	switch (pMsg->uchBattleType)
	{
	case GameBattleDefine::GameBattle_Type_GuildGeneral:
		{
			s_CUI_ID_FRAME_GuildBattleEnter.Refresh();
		}		
		break;
	default:
		break;
	}
}
void CPlayerMgr::OnMsgEnterGameBattleNotice(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgEnterGameBattleAck);
	MsgEnterGameBattleAck* pMsg = (MsgEnterGameBattleAck*)pMsg_;

	switch (pMsg->uchResult)
	{
	case GameBattleDefine::Enter_NotEnterStatus:
		{
			ShowCampBattleInfo_new(theXmlString.GetString(eText_GuildCamp_TimeBeforeBattle));
		}
		break;
	case GameBattleDefine::Enter_MustSignUpGuild:
		{
			ShowCampBattleInfo_new(theXmlString.GetString(eText_GuildCamp_NotSignUp));
		}
		break;
	case GameBattleDefine::Enter_LevelLess:
		{
			ShowCampBattleInfo_new(theXmlString.GetString(eText_Camp_LevelLess));
		}
		break;
	case GameBattleDefine::Enter_MaxCount:
		{
			ShowCampBattleInfo_new(theXmlString.GetString(eText_Camp_MaxCount));
		}
		break;
	case GameBattleDefine::Enter_BattleSumError:
		{
			ShowCampBattleInfo_new(theXmlString.GetString(eText_Enter_BattleSumError));
		}
		break;
	default:
		break;
	}
}
void CPlayerMgr::OnMsgGetGameBattleResource(Msg* pMsg_)
{

	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellGameBattleResource);
	MsgTellGameBattleResource* pMsg = (MsgTellGameBattleResource*)pMsg_;
	
	thePlayerRole.SetRedCampResource(pMsg->nRedResource);
	thePlayerRole.SetBlueCampResource(pMsg->nBlueResource);
	if(!s_CUI_ID_FRAME_ScoreTip.IsVisable())
		s_CUI_ID_FRAME_ScoreTip.SetVisable(true);//显示UI
	s_CUI_ID_FRAME_ScoreTip.SetShow();

	//用于控制公会战场的显示
	if ( s_CUI_ID_FRAME_GuildBattleInfo.IsVisable() )
	{
		s_CUI_ID_FRAME_GuildBattleInfo.SetData(pMsg->nRedGuildID,pMsg->nRedResource,pMsg->nRedTotleKillSum,pMsg->nRedAtterHp[0],pMsg->nRedAtterHp[1],pMsg->nRedAtterHp[2],pMsg->nRedAtterHp[3]
		,pMsg->nBlueGuildID,pMsg->nBlueResource,pMsg->nBlueTotleKillSum,pMsg->nBlueAtterHp[0],pMsg->nBlueAtterHp[1],pMsg->nBlueAtterHp[2],pMsg->nBlueAtterHp[3]);
	}
}
void CPlayerMgr::OnMsgTellGameBattleKillPlayer(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellGameBattleKillPlayer);
	MsgTellGameBattleKillPlayer* pMsg = (MsgTellGameBattleKillPlayer*)pMsg_;
	
	char szText[256] = {0};
	switch (pMsg->uchKillType)
	{
	case MsgTellCampBattleKillPlayer::TypeFirstKill:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->ustStringID), pMsg->szKillerName);
		}
		break;
	case MsgTellCampBattleKillPlayer::TypeKeepKill:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->ustStringID), pMsg->szKillerName);
		}
		break;
	case MsgTellCampBattleKillPlayer::TypeBeKill:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->ustStringID), pMsg->szKillerName, pMsg->szBeKillName);
		}
		break;
	case MsgTellCampBattleKillPlayer::TypeTotalKill:
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->ustStringID), pMsg->szKillerName);
		}
		break;
	default:
		break;
	}

	ShowGuildBattleBullSystemInfo(szText);
}
void CPlayerMgr::OnMsgGetGameBattleInfo(Msg* pMsg_)
{	
	/*if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellGameBattlePlayer);
	MsgTellGameBattlePlayer* pMsg = (MsgTellGameBattlePlayer*)pMsg_;
	
	switch (pMsg->uchCampBattleType)
	{
	case GameBattleDefine::GameBattle_Type_GuildGeneral:
		{
			s_CUI_ID_FRAME_GuildBattle.InitBattleInfo(pMsg->uchCount, pMsg->xPlayer);
		}		
		break;
	default:
		break;
	}*/
}
void CPlayerMgr::OnMsgTellGameBattleMatch(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgTellGameBattleMatch);
	MsgTellGameBattleMatch* pMsg = (MsgTellGameBattleMatch*)pMsg_;

	switch (pMsg->uchBattleType)
	{
	case GameBattleDefine::GameBattle_Type_GuildGeneral:
		{
			thePlayerRole.SetRedCampGuildId(pMsg->nRedID);
			thePlayerRole.SetBlueCampGuildId(pMsg->nBlueID);
			s_CUI_ID_FRAME_ScoreTip.SetShow();
		}
		break;
	default:
		break;
	}
}
void CPlayerMgr::OnMsgKillGameBattleMonster(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgKillGameBattleMonster);
	MsgKillGameBattleMonster* pMsg = (MsgKillGameBattleMonster*)pMsg_;

	if (pMsg->uchBattleType != GameBattleDefine::GameBattle_Type_GuildGeneral || pMsg->nStringID == 0)
	{
		return;
	}
	
	std::string strKiller, strBeKilled; 
	if (pMsg->uchFightCamp == GameBattleDefine::GameBattle_Red)
	{
		strKiller = thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId());
		strBeKilled = thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId());
	}
	else
	{
		strBeKilled = thePlayerRole.GetGuildNameById(thePlayerRole.GetRedCampGuildId());
		strKiller = thePlayerRole.GetGuildNameById(thePlayerRole.GetBlueCampGuildId());
	}
	
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(pMsg->nStringID), strKiller.c_str(), strBeKilled.c_str());
	ShowGuildBattleBullSystemInfo(szText);
}
void CPlayerMgr::OnMsgGetGameGuildBattleResult(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgGameGuildBattleResult);
	MsgGameGuildBattleResult* pMsg = (MsgGameGuildBattleResult*)pMsg_;

	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_GuildGeneral_BattleResult), thePlayerRole.GetGuildNameById(pMsg->nWinGuildID), thePlayerRole.GetGuildNameById(pMsg->nLoseGuildID));
	ShowGuildBattleBullSystemInfo(szText);
}
void CPlayerMgr::OnMsgCampBattleNewDataAck(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgCampBattleNewDataAck);
	MsgCampBattleNewDataAck* pMsg = (MsgCampBattleNewDataAck*)pMsg_;
	//显示新的数据
	s_CUI_ID_FRAME_NewGuildGeneralBattleInfo.SetDataToUI(&pMsg->add,pMsg->info,pMsg->srcGuildName);
	//让小图标闪烁
	s_CUI_ID_FRAME_InfoTips.AddGuildGeneralInfo();
}
void CPlayerMgr::OnMsgGameBattleErrorAck(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgGameBattleErrorAck);
	MsgGameBattleErrorAck* pMsg = (MsgGameBattleErrorAck*)pMsg_;
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(pMsg->Info));
}
void CPlayerMgr::OnMsgAddCampBattleDataAck(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgAddCampBattleDataAck);
	MsgAddCampBattleDataAck* pMsg = (MsgAddCampBattleDataAck*)pMsg_;
	if(!pMsg->Result)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_AddBattleDel));
	}
	else
	{
		s_CUI_ID_FRAME_GuildGeneralBattleList.AddNewGuildGenetal(pMsg->add);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildGeneral_AddBattleOK));
		//打开约战的面板
		s_CUI_ID_FRAME_GuildBaseInfo.ShowGuildGeneralList();
	}
}
void CPlayerMgr::OnMsgLoadCampBattleDataAck(Msg* pMsg_)
{
	//客户端加载与自己公会相关的数据
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgLoadCampBattleDataAck);
	MsgLoadCampBattleDataAck* pMsg = (MsgLoadCampBattleDataAck*)pMsg_;
	for(int i =0;i<pMsg->Sum;++i)
	{
		s_CUI_ID_FRAME_GuildGeneralBattleList.LoadGuildGeneral(pMsg->info[i]);
	}
	s_CUI_ID_FRAME_GuildGeneralBattleList.ShowGuildInfoByPage();
}
void CPlayerMgr::OnMsgDelCampBattleDataAck(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgDelCampBattleDataAck);
	MsgDelCampBattleDataAck* pMsg = (MsgDelCampBattleDataAck*)pMsg_;
	s_CUI_ID_FRAME_GuildGeneralBattleList.DelGuildGeneral(pMsg->ID);
}
void CPlayerMgr::OnMsgFlyToGameBattleReq(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	CHECK_MSGLEN( pMsg_, MsgFlyToGameBattleReq);
	MsgFlyToGameBattleReq* pMsg = (MsgFlyToGameBattleReq*)pMsg_;
	unsigned int Value = 0;
	bool isOpen = false;

	switch(pMsg->uchBattleType)
	{
	case GameBattleDefine::GameBattle_Type_GuildGeneral:
		Value = GuildDefine::GameBattleGuildGeneral;
		isOpen = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_GuildGeneralSetting.IsOpen;
		break;
	}
	GuildMember * pMember = thePlayerRole.GetGangMgr()->FindByDBId(thePlayerRole.GetDBID());
	if(!pMember || (!(pMember->GetCampBattleValue()& Value) && isOpen))
		return;

	switch (pMsg->uchBattleType)
	{
	case GameBattleDefine::GameBattle_Type_GuildGeneral:
		{
			//s_CUI_ID_FRAME_InfoTips.AddGuildCampTip(pMsg_);
			//弹出公会战场的进入UI 1.传送到合适的地图的NPC旁边 在进入副本
			thePlayerRole.SetRedCampGuildId(pMsg->RedID);
			thePlayerRole.SetBlueCampGuildId(pMsg->BlueID);
			s_CUI_ID_FRAME_GuildBattleEnter.SetKingdomMapInfo(pMsg->nKingdomID,pMsg->nKingdomX,pMsg->nKingdomY);
			s_CUI_ID_FRAME_GuildBattleEnter.Refresh();
			//s_CUI_ID_FRAME_GuildBattleEnter.SetVisable(true);
			s_CUI_ID_FRAME_GuildBattleEnter.SetIsGameBattle();
		}
		break;
	default:
		break;			
	}
}
void CPlayerMgr::OnMsgFlyToPosition(Msg* pMsg)
{
	//弹出闪烁图标 让玩家传送到指定位置
	MsgFlyToPosition* pReq = (MsgFlyToPosition*)pMsg;
	if(!pReq)
		return;
	MapConfig::MapData* pData = theMapConfig.GetMapDataById(thePlayerRole.GetGameMapId());
	if(!pData || pData->IsEctypeMap())
		return;
	thePlayerRole.SetFlyPosition(pReq->MapID,pReq->Pos_X,pReq->Pos_Y,pReq->Type);
	s_CUI_ID_FRAME_InfoTips.AddFlyToPosition();
}
void CPlayerMgr::OnMsgQuestEntrustInfoAck(Msg* pMsg_)
{
	if (!pMsg_)
		return;
	CHECK_MSGLEN( pMsg_, MsgQuestEntrustInfoAck);
	MsgQuestEntrustInfoAck* pMsg = (MsgQuestEntrustInfoAck*)pMsg_;
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(pMsg->ID));
}
void CPlayerMgr::OnMsgShowCenterInfo(Msg* pMsg_)
{
	if (!pMsg_)
		return;
	CHECK_MSGLEN( pMsg_, MsgShowCenterInfo);
	MsgShowCenterInfo* pMsg = (MsgShowCenterInfo*)pMsg_;
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(pMsg->ID));
}
void CPlayerMgr::OnMsgQuestEntrustShowInfo(Msg* pMsg_)
{
	if (!pMsg_)
		return;
	CHECK_MSGLEN( pMsg_, MsgQuestEntrustShowInfo);
	MsgQuestEntrustShowInfo* pMsg = (MsgQuestEntrustShowInfo*)pMsg_;
	//1.显示在右下角的聊天框里
	MsgChat Msg( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
	Msg.header.stID = thePlayerRole.GetID();
	char szChat[CHAT_STRINGMAX+1] = { 0 };
	strcpy_s(szChat,CHAT_STRINGMAX-1,theXmlString.GetString( pMsg->ID ));
	Msg.SetString( szChat );
	OnMsgChat(&Msg);
	//2.弹出提示信息 让玩家知道
	s_CUI_ID_FRAME_GuideTip2.ShowPopInfo( pMsg->ID );
}
void CPlayerMgr::OnMsgGetThreeDayItemAck(Msg* pMsg_)
{
	if (!pMsg_)
		return;
	CHECK_MSGLEN( pMsg_, MsgGetThreeDayItemAck);
	MsgGetThreeDayItemAck* pMsg = (MsgGetThreeDayItemAck*)pMsg_;
	thePlayerRole.GetCharInfo2().otherdataclient.nThreeDayVision = pMsg->vision;
	thePlayerRole.GetCharInfo2().otherdataclient.nThreeDayValue = pMsg->value;
}
void CPlayerMgr::OnMsgUpdateYuanBaoData(Msg* pMsg_)
{
	if (!pMsg_)
		return;
	CHECK_MSGLEN( pMsg_, MsgUpdateYuanBaoData);
	MsgUpdateYuanBaoData* pMsg = (MsgUpdateYuanBaoData*)pMsg_;
	thePlayerRole.SetYuanBaoTotle(pMsg->dwAccountYuanBaoTotle);
	thePlayerRole.SetYuanBaoStates(pMsg->dwAccountYuanBaoStates);
}
void CPlayerMgr::OnMsgUpdateAddCampBattleCD(Msg* pMsg_)
{
	if (!pMsg_)
		return;
	CHECK_MSGLEN( pMsg_, MsgUpdateAddCampBattleCD);
	MsgUpdateAddCampBattleCD* pMsg = (MsgUpdateAddCampBattleCD*)pMsg_;
	thePlayerRole.SetBeginGameGeneralBattleTime(pMsg->Time);
}
void CPlayerMgr::OnMsgUpdateGuildMemberOnLineTime(Msg* pMsg_)
{
	if (!pMsg_)
		return;
	CHECK_MSGLEN( pMsg_, MsgUpdateGuildMemberOnLineTime);
	MsgUpdateGuildMemberOnLineTime* pMsg = (MsgUpdateGuildMemberOnLineTime*)pMsg_;
	unsigned int GuildID = pMsg->GuildID;
	unsigned int PlayerID = pMsg->PlayerID;
	__int64 OnLineTime = pMsg->OnLineTime;
	if(!thePlayerRole.GetGangMgr())
		return;
	if(thePlayerRole.GetGangMgr()->GetGuildID() != GuildID)
		return;
	GuildMember * pMember = thePlayerRole.GetGangMgr()->FindByDBId(PlayerID);
	if(!pMember)
		return;
	pMember->SetOnLineTime(OnLineTime);
	//更新UI
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
}
void CPlayerMgr::OnMsgUpdatePlayerPoint(Msg* pMsg_)
{
	if (!pMsg_)
		return;
	CHECK_MSGLEN( pMsg_, MsgUpdatePlayerPoint);
	MsgUpdatePlayerPoint* pMsg = (MsgUpdatePlayerPoint*)pMsg_;
	//组织语句 显示在客户端 告诉玩家点数的改变
	//个人 国家 公会 增加 减少 设置
	char szTemp[32] = {0};
	switch(pMsg->States)
	{
	case 0:
		{
			strcpy_s(szTemp,31,theXmlString.GetString(eText_PlayerPoint_Info_Player));
		}
		break;
	case 1:
		{
			strcpy_s(szTemp,31,theXmlString.GetString(eText_PlayerPoint_Info_Guild));
		}
		break;
	case 2:
		{
			strcpy_s(szTemp,31,theXmlString.GetString(eText_PlayerPoint_Info_Country));
		}
		break;
	default:
		return;
		break;
	}

	char szChat[CHAT_STRINGMAX+1] = { 0 };
	switch(pMsg->Op)
	{
	case 0:
		{
			//玩家失去点数 eText_PlayerPoint_Del_Info
			sprintf_s(szChat,CHAT_STRINGMAX,theXmlString.GetString(eText_PlayerPoint_Del_Info),pMsg->ChangeValue,szTemp,szTemp,pMsg->Value);
		}
		break;
	case 1:
		{
			sprintf_s(szChat,CHAT_STRINGMAX,theXmlString.GetString(eText_PlayerPoint_Add_Info),pMsg->ChangeValue,szTemp,szTemp,pMsg->Value);
		}
		break;
	case 2:
		{
			sprintf_s(szChat,CHAT_STRINGMAX,theXmlString.GetString(eText_PlayerPoint_Set_Info),pMsg->ChangeValue,szTemp,szTemp,pMsg->Value);
		}
		break;
	default:
		return;
		break;
	}
	MsgChat Msg( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
	Msg.header.stID = thePlayerRole.GetID();
	Msg.SetString( szChat );
	OnMsgChat(&Msg);
}
void CPlayerMgr::OnMsgCheckCSAuthReq(Msg* pMsg_)
{
	//反外挂机制
	MsgCheckCSAuthReq* pMsg = (MsgCheckCSAuthReq*)pMsg_;
	if(!pMsg)
		return;
	if(thePlayerRole.GetDBID() != pMsg->PlayerID)
		return;
	#ifdef NPGUARD
		//将数据送入处理 npgl
		PCSAuth3Data pGGReceive = (PCSAuth3Data)pMsg->packet;
		//设置到数据
		int n = npgl->Auth3( (PBYTE)pGGReceive, pMsg->size,g_dwServerNumber);
	#endif
}
void CPlayerMgr::OnMsgCountryBuffChange(Msg* pMsg)
{
	MsgCountryBuffChangeAck msg;
	GettheNetworkInput().SendMsg(&msg);
}
void CPlayerMgr::OnMsgLeaveExpAck(Msg* pMsg)
{
	MsgLeaveExpAck * pAck = (MsgLeaveExpAck*)pMsg;
	if(!pAck)
		return;
	s_CUI_ID_FRAME_LeaveExp.SetInfo(pAck->KillSum,pAck->MaxKillSum,pAck->RadExp,pAck->Hour,pAck->Exp);
}