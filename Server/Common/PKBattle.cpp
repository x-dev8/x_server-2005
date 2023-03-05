/********************************************************************
Filename: 	PKBattle.cpp
MaintenanceMan Mail: lufeipeng@163.com
brief: 阵营战场管理
*********************************************************************/
#include "PKBattle.h"
#include "GameWorld.h"
#include "GlobalDef.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "WordParser.h"
#include "MapConfig.h"
#include "XmlStringLanguage.h"

GameStage* PKCopyScene::CreateStage()
{
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( PKBattle_MapID );
	if ( pMapData == NULL )
	{
		return NULL;
	}	
	
    DWORD dwMapID = GettheWorld().GetEctypeMapID( PKBattle_MapID, true );
	GameStage *pStage = GettheWorld().CreateStage( PKBattle_MapID , dwMapID );
	if (!pStage)
	{
		return NULL;
	}
	return pStage;
}

void PKCopyScene::InitScene()
{	
	//初始化副本信息
	redUsers.clear();
	blueUsers.clear();
	userKillList.clear();
	dotaKillList.clear();
	resourceOccuptList.clear();
	userOccuptResourceList.clear();
    getpresent_user.clear();
	redScore = 0;
	blueScore = 0;
	result = enumBattleInfluence_Max;
	this->SetStage(NULL);

	for(int i = 0; i < enumBattleResource_Max; ++i)
	{
		resourceOccuptList.insert( std::make_pair(i, enumBattleInfluence_Max) );
	}
	freshScoreTimer.next( HQ_TimeGetTime() );
	addScoreTimer.next( HQ_TimeGetTime() );
	waitThrowTimer.next( HQ_TimeGetTime());
	start_pktime = 0;
}

bool PKCopyScene::InitUser(GamePlayer *player, BYTE which, bool firstEnter)
{
	if(!player)
	{
		return false;
	}
	if(firstEnter)
	{
		if(enumBattleInfluence_Red == which)
		{
			redUsers.insert(player->GetDBCharacterID());
		}
		else if(enumBattleInfluence_Blue == which)
		{
			blueUsers.insert(player->GetDBCharacterID());
		}
		else
		{
			player->Log("玩家进入阵营副本初始化失败:%u, %u", player->GetDBCharacterID(), which);
			return false;
		}
		if(HQ_TimeGetTime() - this->GetStartPKTime() < 60 * 1000L)
		{
			std::stringstream oss;
			oss << "保护时间将于" << ( (this->GetStartPKTime()  + 60 * 1000 - HQ_TimeGetTime()) / 1000) << "秒结束";
            player->ShowInfo(false, 253, oss.str().c_str());
		}
	}
    //发送初始化信息
    MsgInitUserBattleData send;
    send.influence = which;
    GettheServer().SendMsgToSingle(&send, player);
	this->SendPKBattleScoreToUser(player);
    this->SendPKBattleState(player);
	player->SetPKBattle(this);
	player->SetPKInfluence(which);
	player->changeMapInfo.Clear();
    MsgExitTeam exitTeam;
    player->OnExitTeam(&exitTeam);
	return true;
}

void PKCopyScene::DestroyBattleUser(GamePlayer *player)
{
	if(!player)
	{
		return;
	}
	player->SetPKBattle(NULL);
	player->SetPKInfluence(enumBattleInfluence_Max);
	player->changeMapInfo.Clear();

	MsgNotifyTimeLeft timeLeft;
	timeLeft.type = MsgNotifyTimeLeft::enumTimeLeft_PKBattleEnd;
	timeLeft.leftTime = 0;
	GettheServer().SendMsgToSingle(&timeLeft, player);
}

enumBattleInfluence PKCopyScene::GetUserInfluence(DWORD characterID)
{
	PKBattleUsers_Iter iter = redUsers.find(characterID);
	if(iter != redUsers.end())
	{
		return enumBattleInfluence_Red;
	}
	iter = blueUsers.find(characterID);
	if(iter != blueUsers.end())
	{
		return enumBattleInfluence_Blue;
	}
	return enumBattleInfluence_Max;
}

enumBattleInfluence PKCopyScene::GetResourcePosOwner(enumBattleResouce pos)
{
	ResourceOccupyList_Iter iter = resourceOccuptList.find(pos);
	if(iter != resourceOccuptList.end())
	{
		return static_cast<enumBattleInfluence>(iter->second);
	}
	return enumBattleInfluence_Max;
}

BaseCharacter* PKCopyScene::GetNpcByResourcePos(enumBattleResouce pos)
{
	DWORD npcID(0);
	switch(pos)
	{
	case enumBattleResource_Beast: npcID = 968;
		break;
	case enumBattleResource_Farm: npcID = 969;
		break;
	case enumBattleResource_Steel: npcID = 970;
		break;
	case enumBattleResource_Wood: npcID = 971;
		break;
	case enumBattleResource_Gold: npcID = 972;
		break;
	default:return NULL;
	};
	return theRunTimeData.GetCharacterByNpcID(npcID);
}

void PKCopyScene::SendPKBattleScoreToUser(GamePlayer *player)
{
	if(!player)
	{
		return;
	}
	MsgFreshBattleScore send;
	send.redFluence = redScore;
	send.blueFluence = blueScore;
	send.maxResourceScore = thePKBattleManager.successScore;
	ResourceOccupyList_Iter iter = resourceOccuptList.begin();
	for(; iter != resourceOccuptList.end(); ++iter)
	{
		if(iter->first < enumBattleConst_ResourcePosNum)
		{
			send.resourcePosOwner[iter->first] = iter->second; 
		}
	}
	GettheServer().SendMsgToSingle(&send, player);
}

void PKCopyScene::SendPKBattleScoreToUser(DWORD characterID)
{
	BaseCharacter* pChar = theRunTimeData.GetGamePlayerByDBID(characterID);
	if(!pChar)
	{
		return;
	}
	GamePlayer *player = static_cast<GamePlayer*>(pChar);
	this->SendPKBattleScoreToUser(player);
}

void PKCopyScene::SendPKBattleScoreToAllUser()
{
	if(!this->GetStage())
	{
		return;
	}
	MsgFreshBattleScore send;
	send.redFluence = redScore;
	send.blueFluence = blueScore;
	send.maxResourceScore = thePKBattleManager.successScore;
	ResourceOccupyList_Iter iter = resourceOccuptList.begin();
	for(; iter != resourceOccuptList.end(); ++iter)
	{
		if(iter->first < enumBattleConst_ResourcePosNum)
		{
			send.resourcePosOwner[iter->first] = iter->second; 
		}
	}
	GettheServer().SendMsgToStage(&send, this->GetStage()->GetMapId());
}

void PKCopyScene::SendPKBattleState(GamePlayer *user)
{
	if(!this->GetStage())
	{
		return;
	}
	MsgAckPKBattleState send;
	PKBattleUsers_Iter iter = redUsers.begin();
	for(; iter != redUsers.end(); ++iter)
	{
		BaseCharacter* pChar = theRunTimeData.GetGamePlayerByDBID(*iter);
		if(!pChar)
		{
			continue;
		}
		GamePlayer *pPlayer = static_cast<GamePlayer*>(pChar);
		DWORD characterID = pPlayer->GetDBCharacterID();
		MsgAckPKBattleState::UserBattleState *battleState= &send.data[send.num++];
		battleState->killNum = userKillList[characterID].first;
		battleState->beKillNUm = userKillList[characterID].second;
		battleState->influence = pPlayer->GetPKInfluence();
		battleState->level = pPlayer->GetLevel();
		battleState->occuptResource = userOccuptResourceList[characterID];
		battleState->profession = pPlayer->GetProfession();
		HelperFunc::SafeNCpy(battleState->userName, pPlayer->GetCharName(), sizeof( battleState->userName ) );
		send.header.stLength += sizeof(MsgAckPKBattleState::UserBattleState);
	}
	iter = blueUsers.begin();
	for(; iter != blueUsers.end(); ++iter)
	{
		BaseCharacter* pChar = theRunTimeData.GetGamePlayerByDBID(*iter);
		if(!pChar)
		{
			continue;
		}
		GamePlayer *pPlayer = static_cast<GamePlayer*>(pChar);
		DWORD characterID = pPlayer->GetDBCharacterID();
	    MsgAckPKBattleState::UserBattleState *battleState= &send.data[send.num++];
	    battleState->killNum = userKillList[characterID].first;
	    battleState->beKillNUm = userKillList[characterID].second;
	    battleState->influence = pPlayer->GetPKInfluence();
	    battleState->level = pPlayer->GetLevel();
	    battleState->occuptResource = userOccuptResourceList[characterID];
	    battleState->profession = pPlayer->GetProfession();
	    HelperFunc::SafeNCpy(battleState->userName, pPlayer->GetCharName(), sizeof( battleState->userName ) );
	    send.header.stLength += sizeof(MsgAckPKBattleState::UserBattleState);
	}
	if(user)
	{
		GettheServer().SendMsgToSingle(&send, user);
	}
	else
	{
		GettheServer().SendMsgToStage(&send, this->GetStage()->GetMapId());
	}
}

void PKCopyScene::NotifyKillUser(GamePlayer *killer, GamePlayer *beKiller)
{
	if(!killer || !beKiller)
	{
		return;
	}
	if(!this->GetStage())
	{
		return;
	}
	//战绩增加杀人数
	UserKillList_Iter iter = userKillList.find(killer->GetDBCharacterID());
	if(iter != userKillList.end())
	{
		iter->second.first += 1;
	}
	else
	{
		userKillList[ killer->GetDBCharacterID() ].first = 1;
	}
	//战绩增加被杀数
	iter = userKillList.find(beKiller->GetDBCharacterID());
	if(iter != userKillList.end())
	{
		iter->second.second += 1;
	}
	else
	{
		userKillList[ beKiller->GetDBCharacterID() ].second = 1;
	}
	//Dota杀人公告
	MsgNotifyBattleKillNum send;
	HelperFunc::SafeNCpy(send.killer, killer->GetCharName(), sizeof(send.killer) );
	HelperFunc::SafeNCpy(send.beKiller, beKiller->GetCharName(), sizeof(send.beKiller) );
	//dota公告杀人次数
	DotaUserKillList_Iter dota_iter = dotaKillList.find(killer->GetDBCharacterID());
	if(dota_iter != dotaKillList.end())
	{
		dota_iter->second += 1;
		send.killNum = dota_iter->second;
	}
	else
	{
		dotaKillList[ killer->GetDBCharacterID() ] = 1;
		send.killNum = 1;
	}
	dota_iter = dotaKillList.find(beKiller->GetDBCharacterID());
	if(dota_iter != dotaKillList.end())
	{
		send.beKillNum = dota_iter->second;
		dota_iter->second = 0;
	}
	GettheServer().SendMsgToStage(&send, this->GetStage()->GetMapId());
}

void PKCopyScene::DoPKScript(GamePlayer *user, DWORD which)
{
	if(!this->GetStage())
	{
		LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "调用阵营脚本发现场景不存在了:%u", which);
		return;
	}
	if(user)
	{
		GetScriptMgr()->StartupVM( ST_PKBATTLE, which, user);
	}
	else
	{
		PKBattleUsers_Iter iterUser = redUsers.begin();
		for(; iterUser != redUsers.end(); ++iterUser)
		{
			BaseCharacter *user = theRunTimeData.GetGamePlayerByDBID(*iterUser);
			if(!user)
			{
				continue;
			}
			if(user->GetMapID() != this->GetStage()->GetMapId())
			{
				continue;
			}
			GamePlayer *player = static_cast<GamePlayer*>(user);
            if(PKScript_AddPresent == which)
            {
                if(this->IsHaveGetPresent(player))
                {
                    continue;
                }
                getpresent_user.insert(player->GetDBCharacterID());
            }
            GetScriptMgr()->StartupVM( ST_PKBATTLE, which, player);
		}
		iterUser = blueUsers.begin();
		for(; iterUser != blueUsers.end(); ++iterUser)
		{
			BaseCharacter *user = theRunTimeData.GetGamePlayerByDBID(*iterUser);
			if(!user)
			{
				continue;
			}
			if(user->GetMapID() != this->GetStage()->GetMapId())
			{
				continue;
			}
			GamePlayer *player = static_cast<GamePlayer*>(user);
            if(PKScript_AddPresent == which)
            {
               if(this->IsHaveGetPresent(player))
               {
                   continue;
               }
                getpresent_user.insert(player->GetDBCharacterID());
            }
			GetScriptMgr()->StartupVM( ST_PKBATTLE, which, player);
		}
        LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "%u调用阵营脚本:%u", this->GetStage()->GetMapId(), which);
	}
}
bool PKCopyScene::IsHaveGetPresent(GamePlayer *user)
{
    if(!user)
    {
        return false;
    }
    std::set<DWORD>::iterator iter = getpresent_user.find(user->GetDBCharacterID());
    if(iter != getpresent_user.end())
    {
        return true;
    }  
    return false;
}
void PKCopyScene::SetHaveGetPresent(GamePlayer *user)
{
    if(!user)
    {
        return;
    }
    getpresent_user.insert(user->GetDBCharacterID());
}
void PKCopyScene::AddPKBattleScore(BYTE influence, WORD score)
{
	if(enumBattleInfluence_Red == influence)
	{
		redScore += score;
	}
	else if(enumBattleInfluence_Blue == influence)
	{
		blueScore += score;
	}
	else
	{
        LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "增加阵营战场积分发现阵营不对:%u, %u", influence, score);
	}
}

void PKCopyScene::AddFailBuff(BYTE influence)
{
	if(enumBattleInfluence_Blue == influence || enumBattleInfluence_Max == influence)
	{
		PKBattleUsers_Iter iterUser = redUsers.begin();
		for(; iterUser != redUsers.end(); ++iterUser)
		{
			BaseCharacter *user = theRunTimeData.GetGamePlayerByDBID(*iterUser);
			if(!user)
			{
				continue;
			}
			GamePlayer *player = (GamePlayer*)user;
			player->ApplyBufferStatus(PKBattle_FAILBUFF, 1, player->GetID(), SCharBuff::StatusEventType_Other, 0);
			player->OnBuffStatusChanged( true );
		}
	}
	
	if(enumBattleInfluence_Red == influence || enumBattleInfluence_Max == influence)
	{
		PKBattleUsers_Iter iterUser = blueUsers.begin();
		for(; iterUser != blueUsers.end(); ++iterUser)
		{
			BaseCharacter *user = theRunTimeData.GetGamePlayerByDBID(*iterUser);
			if(!user)
			{
				continue;
			}
			GamePlayer *player = (GamePlayer*)user;
			player->ApplyBufferStatus(PKBattle_FAILBUFF, 1, player->GetID(), SCharBuff::StatusEventType_Other, 0);
			player->OnBuffStatusChanged( true );
		}
	}
}

void PKCopyScene::FreshBattleResouce()
{
	ResourceOccupyList_Iter iter = resourceOccuptList.begin();
	for(; iter != resourceOccuptList.end(); ++iter)
	{
		if(enumBattleInfluence_Red == iter->second )
		{
			redScore += thePKBattleManager.addScorePerFiveSec;
            if(redScore > thePKBattleManager.successScore)
            {
                redScore = thePKBattleManager.successScore;
            }
		}
		else if(enumBattleInfluence_Blue == iter->second)
		{
			blueScore += thePKBattleManager.addScorePerFiveSec;
            if(blueScore > thePKBattleManager.successScore)
            {
                blueScore = thePKBattleManager.successScore;
            }
		}
	}
}

bool PKCopyScene::SetResourcePosOwner(GamePlayer *player, enumBattleResouce pos)
{
	if( !player || pos >= enumBattleResource_Max)
	{
		return false;
	}
	if(enumCopySceneState_Running != this->GetState())
	{
		return false;
	}
	if(!this->GetStage())
	{
		return false;
	}
	enumBattleInfluence influence = static_cast<enumBattleInfluence>(player->GetPKInfluence());
	if(enumBattleResource_Max == influence || resourceOccuptList[pos] == influence)
	{
		return false;
	}
	resourceOccuptList[pos] = influence;
	userOccuptResourceList[player->GetDBCharacterID()] += 1;
	this->SendPKBattleScoreToAllUser();
	//发送占领公告
	MsgFreshBattleResourceOccuptOwnerChange send;
	send.occupyInfluence = influence;
	send.which = pos;
	HelperFunc::SafeNCpy(send.occupyUser, player->GetCharName(), sizeof(send.occupyUser) );
	GettheServer().SendMsgToStage(&send, this->GetStage()->GetMapId());
	//设置npc阵营
	BaseCharacter *pNpc = this->GetNpcByResourcePos(pos);
	if(pNpc)
	{
		pNpc->SetPKInfluence(influence);
		char szMsgBuff[1024] = {0};
		GettheServer().SendMsgToView( pNpc->FirstSightOnMe(szMsgBuff, sizeof(szMsgBuff)), pNpc->GetID(), false);
	}
	LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "%u的玩家夺取旗子:%u, %u, %u, %p", player->GetDBCharacterID(), influence, pos, this->GetStage()->GetMapId(), pNpc);
	return true;
}

void PKCopyScene::CheckBattleOver()
{
	if(!this->GetStage())
	{
		return;
	}
	if(redScore >= thePKBattleManager.successScore)
	{
		this->EndBattle(enumBattleInfluence_Red);
		this->state = enumCopySceneState_WaitThrow;
		waitThrowTimer.next(HQ_TimeGetTime());
	}
	if(blueScore >= thePKBattleManager.successScore)
	{
		this->EndBattle(enumBattleInfluence_Blue);
		this->state = enumCopySceneState_WaitThrow;
		waitThrowTimer.next(HQ_TimeGetTime());
	}
}

void PKCopyScene::BattleTimeOver()
{
	if(!this->GetStage())
	{
		return;
	}
	if(redScore > blueScore)
	{
		this->EndBattle(enumBattleInfluence_Red);
	}
	else if(blueScore > redScore)
	{
		this->EndBattle(enumBattleInfluence_Blue);
	}
	else
	{	
		this->EndBattle(enumBattleInfluence_Max);
	}
	this->state = enumCopySceneState_WaitThrow;
	waitThrowTimer.next(HQ_TimeGetTime());
    LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "当前副本生存期到,副本ID:%u,积分%u, %u", this->GetStage()->GetMapId(), redScore, blueScore);
}

void PKCopyScene::EndBattle(enumBattleInfluence winner)
{
	this->SetPKBattleResult(winner);
	this->DoPKScript(NULL, PKScript_CheckPackFull);
	this->SendPKBattleState(NULL);
	this->AddFailBuff(winner);

	MsgNotifyBattleEnd result;
	result.winner = winner;
	GettheServer().SendMsgToStage(&result, this->GetStage()->GetMapId());

	MsgNotifyTimeLeft timeLeft;
	timeLeft.type = MsgNotifyTimeLeft::enumTimeLeft_PKBattleEnd;
	timeLeft.leftTime = 60;
	GettheServer().SendMsgToStage(&timeLeft, this->GetStage()->GetMapId());
	LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "%u的阵营战场结束, 胜利方%u, 积分%u, %u", this->GetStage()->GetMapId(), winner, blueScore, redScore);
}
void PKCopyScene::ClearUserData(GamePlayer *user)
{
	if(!user)
	{
		return;
	}
	PKBattleUsers_Iter iter = redUsers.find(user->GetDBCharacterID());
	if(iter != redUsers.end())
	{
		redUsers.erase(iter);
	}
	iter = blueUsers.find(user->GetDBCharacterID());
	if(iter != blueUsers.end())
	{
		blueUsers.erase(iter);
	}
}
void PKCopyScene::SendPKBattleUserPos(GamePlayer *user)
{
	if(!user || !this->GetStage())
	{
		return;
	}
	PKBattleUsers userList;
	if(enumBattleInfluence_Red == user->GetPKInfluence())
	{
		userList = redUsers;
	}
	else if(enumBattleInfluence_Blue == user->GetPKInfluence())
	{
		userList = blueUsers;
	}
	else
	{
        user->Log("请求阵营战场坐标:%u", user->GetPKInfluence());
		return;
	}
	MsgReturnInfluenceUserPos send;
	PKBattleUsers_Iter iterUser = userList.begin();
	for(; iterUser != userList.end(); ++iterUser)
	{
		BaseCharacter *user = theRunTimeData.GetGamePlayerByDBID(*iterUser);
		if(!user)
		{
			continue;
		}
		if(user->GetMapID() != this->GetStage()->GetMapId())
		{
			continue;
		}
		GamePlayer *player = static_cast<GamePlayer*>(user);
		MsgReturnInfluenceUserPos::UserPos *userPos = (MsgReturnInfluenceUserPos::UserPos *)&send.data[send.num++];
		userPos->x = player->GetFloatX();
		userPos->y = player->GetFloatY();
		HelperFunc::SafeNCpy(userPos->name, player->GetCharName(), sizeof(userPos->name) - 1);
		send.header.stLength += sizeof(MsgReturnInfluenceUserPos::UserPos);
	}
	GettheServer().SendMsgToSingle(&send, user);
}
void PKCopyScene::Loop()
{
	switch(state)
	{	
	case enumCopySceneState_Stop:
		{
		}
		break;
	case enumCopySceneState_Running:
		{
			if(freshScoreTimer(HQ_TimeGetTime()))
			{
				this->SendPKBattleScoreToAllUser();
				this->CheckBattleOver();
			}
			if(addScoreTimer(HQ_TimeGetTime()))
			{
				this->FreshBattleResouce();
			}
		}
		break;
	case enumCopySceneState_WaitThrow:
		{
			if( waitThrowTimer(HQ_TimeGetTime()) )
			{
				this->DoPKScript(NULL, PKScript_AddPresent);
				this->state = enumCopySceneState_Stop;
				if(this->GetStage())
				{
					this->GetStage()->SetDelete(true); 
					this->GetStage()->SetStageStartWaitReleaseTime( HQ_TimeGetTime());
					this->SetStage(NULL);
				}
			}
		}
		break;
	default:
		{
			LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "阵营副本运行状态不正确");
		}
		break;
	}
}

void PKCopyScene::SendChatMessageToInfluence( Msg* pMsg, enumBattleInfluence eInfluence )
{
    if ( pMsg == NULL || eInfluence == enumBattleInfluence_Max )
    { return; }

    std::set<DWORD>::iterator begin;
    std::set<DWORD>::iterator end;
    switch ( eInfluence )
    {
    case enumBattleInfluence_Red:
        {
            begin = redUsers.begin();
            end   = redUsers.end();
        }
        break;
    case enumBattleInfluence_Blue:
        {
            begin = blueUsers.begin();
            end   = blueUsers.end();
        }
        break;
    default:
        return;
    }

    for ( ; begin != end; ++begin )
    {
        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( *begin );
        if ( pPlayer == NULL )
        { continue; }

        pPlayer->SendMessageToClient( pMsg );
    }
}

void PKBattleManager::Init()
{
	addScorePerFiveSec = 0;
	successScore = 0;
	queueRed.clear();
	queueBlue.clear();
	copySceneList.clear();
	start = false;
	fiveMinTimer = NULL;
	fightTimer = NULL;
	state = enumPKBattleState_Stop;
	round = 0;
	battleTime = 0;
	wait_time = 0;
	match_num = 0;

	BattleWaitQueue waitQueue;
	for(int i = 0; i < pkBattleWaitQueueSize; ++i)
	{
		queueRed.insert(std::make_pair(i, waitQueue));
		queueBlue.insert(std::make_pair(i, waitQueue));
	}
}

void PKBattleManager::RequestWaitBattleQueue(GamePlayer *user, WORD influence, WORD doorNum)
{
	if(!user)
	{
		return;
	}
	MsgAckEnterBattleQueue send;
	if(influence > enumBattleInfluence_Blue || doorNum >= pkBattleWaitQueueSize)
	{
		send.result = MsgAckEnterBattleQueue::enumEnterBattle_ErrorDoor;
		goto FAIL;
	}
	if(enumPKBattleState_Stop == state)
	{
		send.result = MsgAckEnterBattleQueue::enumEnterBattle_NotStart;
		goto FAIL;
	}
	if(enumPKBattleState_PK == state)
	{
		send.result = MsgAckEnterBattleQueue::enumEnterBattle_IsFighting;
		goto FAIL;
	}
	if(enumBattleInfluence_Red == influence)
	{
		if(queueRed[doorNum].size() >= PKBattle_MaxSignNum)
		{
			send.result = MsgAckEnterBattleQueue::enumEnterBattle_DoorFull;
			goto FAIL;
		}
		this->RemoveFromWaitQueue(user);
		queueRed[doorNum].insert(user->GetDBCharacterID());
	}
	else if(enumBattleInfluence_Blue == influence)
	{
		if(queueBlue[doorNum].size() >= PKBattle_MaxSignNum)
		{
			send.result = MsgAckEnterBattleQueue::enumEnterBattle_DoorFull;
			goto FAIL;
		}
		this->RemoveFromWaitQueue(user);
		queueBlue[doorNum].insert(user->GetDBCharacterID());
	}
	send.result = MsgAckEnterBattleQueue::enumEnterBattle_Success;
	this->RequestSendWaitBattleQueue(user);
	this->RequestPKBattleSignList(user, influence, doorNum);
	user->Log("玩家排队阵营副本:阵营%u, 房间%u", influence, doorNum);
FAIL:
	send.doorNum = doorNum;
	send.which = influence;
	GettheServer().SendMsgToSingle(&send, user);
}

void PKBattleManager::RequestPKBattleSignList(GamePlayer *user, WORD influence, WORD doorNum)
{
	MsgAckEnterBattleQueue send;
	if(!user || influence > enumBattleInfluence_Blue || doorNum >= pkBattleWaitQueueSize)
	{
		send.result = MsgAckEnterBattleQueue::enumEnterBattle_ErrorDoor;
		GettheServer().SendMsgToSingle(&send, user);
		return;
	}
	if(enumPKBattleState_Stop == state)
	{
		send.result = MsgAckEnterBattleQueue::enumEnterBattle_NotStart;
		GettheServer().SendMsgToSingle(&send, user);
		return;
	}
	MsgAckPKBattleSignList signList;
	BattleWaitQueue userQueue;
	if(influence == enumBattleInfluence_Red)
	{
		userQueue = queueRed[doorNum];
	}
	else if(influence == enumBattleInfluence_Blue)
	{
		userQueue = queueBlue[doorNum];
	}
	BattleWaitQueue_Iter iter = userQueue.begin();
	for(; iter != userQueue.end(); ++iter)
	{		
		BaseCharacter *user = theRunTimeData.GetGamePlayerByDBID(*iter);
		if(!user)
		{
			continue;
		}
		GamePlayer *player = (GamePlayer*)user;
	    MsgAckPKBattleSignList::BattleSignList *signData = (MsgAckPKBattleSignList::BattleSignList *)&signList.data[signList.num++];
	    signData->level = player->GetLevel();
	    signData->profression = player->GetProfession();
	    HelperFunc::SafeNCpy(signData->name, player->GetCharName(), sizeof( signData->name ) );
	    if(player->GetGuild())
	    {
		    HelperFunc::SafeNCpy(signData->guidName, player->GetGuild()->GetName(), sizeof(signData->guidName) );
	    }
	    signList.header.stLength += sizeof(MsgAckPKBattleSignList::BattleSignList);
	}
	GettheServer().SendMsgToSingle(&signList, user);
}

void PKBattleManager::RequestSendWaitBattleQueue(GamePlayer *user)
{
	if(!user)
	{
		return;
	}
	int offset(0);
	MsgAckBattleQueueNum send;
	send.maxSignNum = PKBattle_MaxSignNum;
	if(this->fiveMinTimer)
	{
         send.leftTimeType = MsgAckBattleQueueNum::enumLeftTime_Sign;
		send.leftTime = fiveMinTimer->left(HQ_TimeGetTime()) / 1000;
	}
    if(this->fightTimer)
    {
        send.leftTimeType = MsgAckBattleQueueNum::enumLeftTime_PK;
        send.leftTime = fightTimer->left(HQ_TimeGetTime()) / 1000;
    }
	this->GetUserInfluenceAndDoorNum(user, send.which, send.doorNum);

	InfluenceWaitQueue_Iter iter = queueRed.begin();
	for(; iter != queueRed.end(); ++iter)
	{
		send.queueA[offset++] = iter->second.size();
	}
	offset = 0;
	iter = queueBlue.begin();
	for(; iter != queueBlue.end(); ++iter)
	{
		send.queueB[offset++] = iter->second.size();
	}
	GettheServer().SendMsgToSingle(&send, user);
}
PKCopyScene* PKBattleManager::GetCopySceneByID(DWORD nMapID)
{
	PKBattleList_Iter iter = copySceneList.begin();
	for(; iter != copySceneList.end(); ++iter)
	{
		GameStage *stage = (*iter)->GetStage();
		if(stage && nMapID == stage->GetMapId())
		{
			return *iter;
		}
	}
	return NULL;
}
bool PKBattleManager::RequestIntoPKBattle(GamePlayer *user, bool isEnter)
{
	if(!user)
	{
		return false;
	}
	if(!isEnter)
	{
		user->changeMapInfo.Clear();
		user->ApplyBufferStatus(PKCopyScene::PKBattle_FAILBUFF, 3, user->GetID(), SCharBuff::StatusEventType_Other, 0);
		user->OnBuffStatusChanged( true );
		return false;
	}
	if(enumPKBattleState_PK != state)
	{
		return false;
	}
	PKCopyScene *scene = this->GetCopySceneByID(user->changeMapInfo.nMapId);
	if(!scene)
	{
		return false;
	}
	if(user->FlyToMapReq(user->changeMapInfo.nMapId, user->changeMapInfo.x, user->changeMapInfo.y, user->changeMapInfo.fDir))
	{
		scene->InitUser(user, user->changeMapInfo.influence);
		user->Log("玩家进入阵营副本:%u, %u", user->changeMapInfo.nMapId, user->changeMapInfo.influence);
	}
	else
	{
		user->Log("进入阵营副本失败:%u, %u", user->changeMapInfo.nMapId, user->changeMapInfo.influence);
		return false;
	}
	return true;
}

void PKBattleManager::GetUserInfluenceAndDoorNum(GamePlayer *user, uint8 &influence, uint8 &doorNum)
{
	if(!user)
	{
		return;
	}

	int offset(0);
	DWORD characterID = user->GetDBCharacterID();
	InfluenceWaitQueue_Iter iter = queueRed.begin();
	for(; iter != queueRed.end(); ++iter, ++offset)
	{
		BattleWaitQueue_Iter userIter = iter->second.find(characterID);
		if(userIter != iter->second.end())
		{
			doorNum = offset;
			influence = enumBattleInfluence_Red;
			return;
		}
	}
	iter = queueBlue.begin();
	for(offset = 0; iter != queueBlue.end(); ++iter,  ++offset)
	{
		BattleWaitQueue_Iter userIter = iter->second.find(characterID);
		if(userIter != iter->second.end())
		{
			doorNum = offset;
			influence = enumBattleInfluence_Blue;
			return;
		}
	}
}

bool PKBattleManager::CheckUserInWaitBattleQueue(GamePlayer *user)
{
	if(!user)
	{
		return false;
	}
	DWORD characterID = user->GetDBCharacterID();
	InfluenceWaitQueue_Iter iter = queueRed.begin();
	for(; iter != queueRed.end(); ++iter)
	{
		BattleWaitQueue_Iter userIter = iter->second.find(characterID);
		if(userIter != iter->second.end())
		{
			return true;
		}
	}
	iter = queueBlue.begin();
	for(; iter != queueBlue.end(); ++iter)
	{
		BattleWaitQueue_Iter userIter = iter->second.find(characterID);
		if(userIter != iter->second.end())
		{
			return true;
		}
	}
	return false;
}

void PKBattleManager::RemoveFromWaitQueue(GamePlayer *user)
{
	if(!user)
	{
		return;
	}
	DWORD characterID = user->GetDBCharacterID();
	InfluenceWaitQueue_Iter iter = queueRed.begin();
	for(; iter != queueRed.end(); ++iter)
	{
		BattleWaitQueue_Iter userIter = iter->second.find(characterID);
		if(userIter != iter->second.end())
		{
			iter->second.erase(userIter);
			return;
		}
	}
	iter = queueBlue.begin();
	for(; iter != queueBlue.end(); ++iter)
	{
		BattleWaitQueue_Iter userIter = iter->second.find(characterID);
		if(userIter != iter->second.end())
		{
			iter->second.erase(userIter);
			return;
		}
	}
    user->Log("玩家退出阵营副本排队队列");
}
void PKBattleManager::Match()
{
	std::vector<int> matchA;
	std::vector<int> matchB;
	//筛选满足人数的队列
	for(int i = 0; i < pkBattleWaitQueueSize; ++i)
	{
		if(queueRed[i].size() >= match_num)
		{
			matchA.push_back(i);
		}
		if(queueBlue[i].size() >= match_num)
		{
			matchB.push_back(i);
		}
	}
	//匹配
	int round = min(matchA.size(), matchB.size());
	if(!round)
	{
		return;
	}
	std::vector< std::pair<DWORD , DWORD> > matchedTeam;
	while(round--)
	{
		int sizeA = matchA.size();
		int sizeB = matchB.size();
		if(!sizeA|| !sizeB)
		{
			LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "找不到要匹配的队伍了");
			break;
		}
		int indexA = theRand.rand32() % sizeA;
		int indexB = theRand.rand32() % sizeB;
		matchedTeam.push_back( std::make_pair(matchA[indexA], matchB[indexB]) );
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "阵营战场匹配房间号:%u,%u", matchA[indexA], matchB[indexB]);

		std::vector<int>::iterator iter = std::find(matchA.begin(), matchA.end(), matchA[indexA]);
		if(iter != matchA.end())
		{
			matchA.erase(iter);
		}
		iter = std::find(matchB.begin(), matchB.end(), matchB[indexB]);
		if(iter != matchB.end())
		{
			matchB.erase(iter);
		}
	}
	//加入战场
	LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "有%u场阵营战场开启", matchedTeam.size() );
	for(int i = 0; i < matchedTeam.size(); ++i)
	{
		PKCopyScene *scene = this->GetOneReadyCopyScene();	
		if(!scene)
		{
			LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "阵营战场开启失败");
			break;
		}
		scene->SetStartPKTime(HQ_TimeGetTime());
		BattleWaitQueue waitAUsers = queueRed[ matchedTeam[i].first ];
		for(BattleWaitQueue_Iter iter = waitAUsers.begin(); iter != waitAUsers.end(); ++iter)
		{
			this->PushUserToPKBattle(scene, *iter, enumBattleInfluence_Red);
		}
		queueRed[ matchedTeam[i].first ].clear();
		BattleWaitQueue waitBUsers = queueBlue[ matchedTeam[i].second ];
		for(BattleWaitQueue_Iter iter = waitBUsers.begin(); iter != waitBUsers.end(); ++iter)
		{
			this->PushUserToPKBattle(scene, *iter, enumBattleInfluence_Blue);
		}
		queueBlue[ matchedTeam[i].second ].clear();
	}
    this->NotifyPlayerNoMatch();
}
void PKBattleManager::PushUserToPKBattle(PKCopyScene *scene, DWORD pCharID, BYTE which)
{
	if(!scene)
	{
		return;
	}
	BaseCharacter* pChar = theRunTimeData.GetGamePlayerByDBID(pCharID);
	if(!pChar)
	{
		return;
	}
	//记录战场信息
	GamePlayer* user = static_cast<GamePlayer*>(pChar);
	MapConfig::MapData* pMapData = scene->GetStage()->GetMapDataConfig();
	if(!pMapData)
	{
		LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "初始化玩家进入阵营副本信息, 找不到地图的配置文件");
		return;
	}
	MapConfig::TransportDestination *redInPos =  pMapData->GetTransportDestinationById(0);
	MapConfig::TransportDestination *blueInPos =  pMapData->GetTransportDestinationById(1);
	if(!redInPos || !blueInPos)
	{
		LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "初始化玩家进入阵营副本信息, 找不到地图传送点");
		return;
	}
	user->changeMapInfo.nMapId = scene->GetStage()->GetMapId();
	if(enumBattleInfluence_Red == which)
	{
		user->changeMapInfo.x = redInPos->PositionX;
		user->changeMapInfo.y = redInPos->PositionY;
		user->changeMapInfo.fDir = redInPos->Direction;
		user->changeMapInfo.influence = enumBattleInfluence_Red;
	}
	else if(enumBattleInfluence_Blue == which)
	{
		user->changeMapInfo.x = blueInPos->PositionX;
		user->changeMapInfo.y = blueInPos->PositionY;
		user->changeMapInfo.fDir = blueInPos->Direction;
		user->changeMapInfo.influence = enumBattleInfluence_Blue;
	}
	//通知客户端进入战场
	MsgNotifyUserEnterBattle notifyClient;
	GettheServer().SendMsgToSingle(&notifyClient, pChar);
    user->Log("通知玩家进入阵营副本:%u", scene->GetStage()->GetMapId());
}

void PKBattleManager::NotifyPlayerNoMatch()
{
    InfluenceWaitQueue_Iter iter = queueRed.begin();
    for(; iter != queueRed.end(); ++iter)
    {
        BattleWaitQueue_Iter userIter = iter->second.begin();
        for( ; userIter != iter->second.end(); ++userIter)
        {
            GamePlayer *player = theRunTimeData.GetGamePlayerByDBID( *userIter );
            if(!player)
            {
                continue;
            }
            if(this->round > 1)
            {
                player->ShowInfo(false, 253, theXmlString.GetString(eText_PKBattleNoMatch) );
            }
            else
            {
                player->ShowInfo(false, 253, theXmlString.GetString(eText_PKBattleNoMatchRoundEnd) );
            }
        }
    }

    iter = queueBlue.begin();
    for(; iter != queueBlue.end(); ++iter)
    {
        BattleWaitQueue_Iter userIter = iter->second.begin();
        for( ; userIter != iter->second.end(); ++userIter)
        {
            GamePlayer *player = theRunTimeData.GetGamePlayerByDBID( *userIter );
            if(!player)
            {
                continue;
            }
            if(this->round > 1)
            {
                player->ShowInfo(false, /*3000,*/ 253, theXmlString.GetString(eText_PKBattleNoMatch) );
            }
            else
            {
                player->ShowInfo(false, /*3000,*/ 253, theXmlString.GetString(eText_PKBattleNoMatchRoundEnd) );
            }
        }
    }
}

PKCopyScene* PKBattleManager::GetOneReadyCopyScene()
{
	PKBattleList_Iter iter = copySceneList.begin();
	for(; iter != copySceneList.end(); ++iter)
	{
		PKCopyScene *scene = *iter;
		if( (*iter)->GetState() == PKCopyScene::enumCopySceneState_Stop)
		{
			GameStage *pStage = PKCopyScene::CreateStage();
			if(pStage)
			{
				scene->InitScene();
				scene->SetStage(pStage);
				scene->SetState(PKCopyScene::enumCopySceneState_Running);
				return scene;
			}
			continue;
		}
	}
	GameStage *pStage = PKCopyScene::CreateStage();
	if(!pStage)
	{
		return NULL;
	}
	PKCopyScene *scene = NEW_POOL(PKCopyScene);
	if(!scene)
	{
		pStage->Release();
		return NULL;
	}
	scene->InitScene();
	scene->SetStage(pStage);
	scene->SetState(PKCopyScene::enumCopySceneState_Running);
	copySceneList.push_back(scene);
	return scene;
}
void PKBattleManager::TestBattle(GamePlayer *user, const char * param)
{
	if(!user)
	{
		return;
	}
	WordParser word;
	word.Parse(param);
	if( word.Compare(1, "BattleSign"))
	{
		this->ClearPKBattleData();
		this->SetBattleStart( atoi( word.GetWord(2) ), atoi( word.GetWord(3) ), atoi( word.GetWord(4) ), atoi( word.GetWord(5)), atoi( word.GetWord(6)),
			atoi( word.GetWord(7)));
	}
	if( word.Compare(1, "BattleWait"))
	{
		this->RequestWaitBattleQueue(user, atoi( word.GetWord(2) ), atoi( word.GetWord(3) ) );
	}
	if( word.Compare(1, "BattleEnter") )
	{
		this->RequestIntoPKBattle(user, 1);
	}
	if( word.Compare(1, "BattleOccupy"))
	{
		if(user->GetPKBattle())
		{
			user->GetPKBattle()->SetResourcePosOwner(user, (enumBattleResouce)(atoi( word.GetWord(2) )) );
		}
	}
	if(word.Compare(1, "BattleState"))
	{
		if(user->pkBattle)
		{
			user->pkBattle->SendPKBattleState(user);
		}
	}
	if(word.Compare(1, "BattleAddScore"))
	{
		if(user->pkBattle)
		{
			user->pkBattle->AddPKBattleScore( atoi( word.GetWord(2)), atoi( word.GetWord(3)) );
		}
	}
	if(word.Compare(1, "BattleAddBuff"))
	{
		user->ApplyBufferStatus(atoi( word.GetWord((2))), atoi( word.GetWord((3))), user->GetID(), SCharBuff::StatusEventType_Other, 0);
		user->OnBuffStatusChanged( true );
	}
    if(word.Compare(1, "BattleScript"))
    {
        GetScriptMgr()->StartupVM( ST_PKBATTLE, atoi( word.GetWord((2))), user);
    }
}
void PKBattleManager::Loop()
{
	//遍历所有的阵营副本
	switch(state)
	{
	case enumPKBattleState_Stop:
		{
			if(this->CheckBattleStart())
			{
				state = enumPKBattleState_Sign;
				fiveMinTimer = new HRTimer(wait_time * 60 * 1000);
			}
		}
		break;
	case enumPKBattleState_Sign:
		{
			if( fiveMinTimer && (*fiveMinTimer)(HQ_TimeGetTime()) )
			{
				//报名时间到，匹配
				this->Match();
				state = enumPKBattleState_PK;
				SAVE_DELETE_POINTER(fiveMinTimer);
				fightTimer = new HRTimer(battleTime * 60 * 1000);
				std::stringstream oss;
				if(round > 1)
				{
					MsgChat Msg( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
					Msg.SetString( theXmlString.GetString(eText_PKBattleFight) );
					GettheServer().SendMsgToWorld( &Msg , true);  
				}
				else
				{
					MsgChat Msg( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
					Msg.SetString( theXmlString.GetString(eText_PKBattleLastFight) );
					GettheServer().SendMsgToWorld( &Msg , true);  	
				}
			}
		}
		break;
	case enumPKBattleState_PK:
		{
			if( fightTimer && (*fightTimer)(HQ_TimeGetTime()))
			{
				//战斗结束, 下一轮
				SAVE_DELETE_POINTER(fightTimer);
				this->NotifyPKBattleEnd();
                --round;
                if(round >= 1)
                {
                    MsgChat Msg( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
                    Msg.SetString( theXmlString.GetString(eText_PKBattleSign) );
                    GettheServer().SendMsgToWorld( &Msg , true);  
                    state = enumPKBattleState_Sign;
                    fiveMinTimer = new HRTimer(wait_time * 60 * 1000);
                }
			}
		}
		break;
	default:
		break;
	}
    bool isEnd(true);
    PKBattleList_Iter iter = copySceneList.begin();
    for(; iter != copySceneList.end(); ++iter)
    {
        PKCopyScene *scene = *iter;
        if(scene && PKCopyScene::enumCopySceneState_Stop != scene->GetState())
        {
            scene->Loop();
            isEnd = false;
        }		
    }
    if(start && !round && isEnd)
    {
        this->ClearPKBattleData();
    }
}
void PKBattleManager::NotifyPKBattleEnd()
{
	PKBattleList_Iter iter = copySceneList.begin();
	for(; iter != copySceneList.end(); ++iter)
	{
		PKCopyScene *scene = *iter;
		if(scene && scene->GetState() == PKCopyScene::enumCopySceneState_Running)
		{
			scene->BattleTimeOver();
		}
	}
}

void PKBattleManager::ClearPKBattleData()
{
	PKBattleList_Iter iter = copySceneList.begin();
	for(; iter != copySceneList.end(); ++iter)
	{
		PKCopyScene *scene = *iter;
		scene->Release();
	}
	SAVE_DELETE_POINTER(fiveMinTimer);
	SAVE_DELETE_POINTER(fightTimer);
	this->Init();
    LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "今天的战场结束了，清除数据");
}

PKCopyScene* PKBattleManager::GetUserPKBattleScene(GamePlayer *user, BYTE& influence)
{
	if(!user)
	{
		return NULL;
	}
	PKBattleList_Iter iter = copySceneList.begin();
	for(; iter != copySceneList.end(); ++iter)
	{
		PKCopyScene *scene = *iter;
		if(scene && scene->GetState() == PKCopyScene::enumCopySceneState_Running)
		{
			if( (influence = scene->GetUserInfluence( user->GetDBCharacterID() )) != enumBattleInfluence_Max)
			{
				return scene;
			}
		}
	}
	return NULL;
}