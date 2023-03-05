#include "GamePlayer.h"
#include "ShareData.h"
#include "GameStage.h"
#include "GameWorld.h"
#include "GameArea.h"
#include "WordParser.h"
#include "FuncPerformanceLog.h"
#include "MonsterBaseEx.h"
#include "GlobalDef.h"
#include "ServerVarInterface.h"
#include "XmlStringLanguage.h"
#include "ExpStage.h"
#include "Configure.h"
#include "md5.h"
#include "TeamManager.h"
#include "LuckRewardManager.h"
#include "TradeCenterInfo.h"
#include "RabotManager.h"
#include "SuitOperateConfig.h"
#include "ApplyCenter.h"
#include "application_config.h"
#include "CampBattleControl.h"
#include "CampBattle.h"
#include "QuestManager.h"
#include "MonsterCreater.h"
#include "XinFaConfig.h"
#include "GlobalDBManager.h"
#include "LogEventService.h"
#include "GameGuildGeneralBattleManager.h"
#include "GameBattleControl.h"
#include "PasswordMessage.h"

#define PARAM_STRINGMAX 64	//参数最大长度

extern CExpStage theExpStage;
extern IScriptInterface* GetScriptInterface();

//为Bot创建装备luo.qin 3.24
// void GamePlayer::CreateItemForBot( int nItemID, int iCount, int nType )
// {
// 	//在本场景的x,y,位置放置物品item,count个
// 	int x,y;
// 	int nRandID[10] = {0};
// 	int nLevel;
// 	x = GetTileX();
// 	y = GetTileY();
// 	ItemDefine::SItemCommon *pItem = NULL;
// 
// 	pItem = GettheItemDetail().GetItemByID(nItemID);
// 
// 	if( pItem == NULL )        
// 	{ return; }
// 
// 	SCharItem item;
// 	unsigned short nCount = iCount;
// 
// 	theRunTimeData.CreateItem( this, pItem->ustItemID, nCount, HelperFunc::CreateID(), item );
// 
// 	if ( !pItem->IsExclusive() ) 
// 	{
// 		if( ItemDefine::ITEMTYPE_RESTORE )
// 		{   
// 			item.itembaseinfo.ustItemCount = 99;
// 		}
// 		else 
// 		{
// 			item.itembaseinfo.ustItemCount = iCount;
// 		}
// 	}
// 
// 	switch( pItem->ucItemType )
// 	{
// 	case ItemDefine::ITEMTYPE_WEAPON:
// 	case ItemDefine::ITEMTYPE_ARMOUR:
// 		{
// 			for (int n = 0; n <SCharItem::EConstDefine_BaseRandMaxCount;++n)
// 			{
// 				if (nRandID[n] > 0)
// 				{
// 					ItemDefine::SRandAttribute* pRandAttibute = GettheItemDetail().GetRandByID(nRandID[n]);
// 					if (pRandAttibute)
// 					{
// 						item.equipdata.baseRands[n] = nRandID[n];
// 					}
// 				}
// 			}
// 
// 			if ( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
// 			{
// 				ItemDefine::SItemWeapon* pWeaponConfig = (ItemDefine::SItemWeapon*)pItem;
// 				if ( pWeaponConfig->stWeaponType == eWeapontype_Flag )
// 				{ 
// 					if ( m_pGuild == NULL )
// 					{ return;}
// 
// 					item.itembaseinfo.value1 = m_pGuild->GetID();
// 				}
// 			}
// 		}
// 		break;
// 	case ItemDefine::ITEMTYPE_RESTORE:
// 		{
// 			if( iCount >= 100 )
// 			{
// 				// 增加经验值获得值
// 				ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore *)pItem;
// 				pRestore->dwAddExp = iCount;
// 			}
// 		}
// 		break;
// 	}
// 
// 	int nResult = ierr_Success;
// 	if ( nType == 0)
// 	{
// 		AddItemToBag( item, nCount );
// 	}
// 	else
// 	{
// 		theGameWorld.CreateItemNpc( pItem->GetItemName(), GetMapID(),x,y,0,item, -1, 0);
// 	}
// 
// }

bool GamePlayer::ProcessGMCommand( const MsgChat* pMsgChat )
{
	if ( pMsgChat == NULL )
	{ return false; }

	switch ( pMsgChat->szString[0] )
	{
	case '/':   // GM命令
		{
			if ( g_Cfg.bIsOpenCommand )		// 在Setting-GameCommon中配置是否打开GM指令
				OnGMCommand( pMsgChat, 0xFFFFFFFF );
			else
				OnGMCommand( pMsgChat, m_nGMLevel );
		}
		break;
	case '$':   // 机器人命令
		{
			if ( g_Cfg.bIsOpenRobotCmd )    // 在GameCommonSetting中配置的
			{
				OnBotCommand( pMsgChat->szString + 1 );
			}
		}
		break;
	default:
		return false;
		break;
	}

	return true;
}

void GamePlayer::OnBotCommand(const char* szCommand)
{
	if (szCommand == NULL)
		return;

	WordParser w;
	if( w.Parse( szCommand ) == 0 )
	{ return; }

	//Log( "Use Bot Command [%s]", szCommand );
	Log( theXmlString.GetString(eServerLog_UseBotCommand), szCommand );

	if( w.Compare( 0, "BotReq" ) )
	{
		if (w.Compare(1, "AskForOneTarget"))
		{
			int nLevel = this->GetLevel();
			int nAreaID = this->GetCurArea();
			GameStage* pGameStage = theGameWorld.GetStageById(this->GetMapID());
			if (pGameStage != NULL)
			{
				GameArea* pGameArea = pGameStage->GetArea(nAreaID);
				if (pGameArea != NULL)
				{
					GameObjectId objectId = InvalidGameObjectId;
					for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
					{
						BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
						// 如果找到的怪物等级与玩家相差三级
						if (pChar != NULL && pChar->IsMonster() && static_cast<MonsterBaseEx*>(pChar)->GetMonsterType() == eMT_NormalMonster && abs(pChar->GetLevel() - nLevel) < 3)
						{
							TellClient( "/AskForOneTarget %d %f %f", pChar->GetID(), pChar->GetFloatX(), pChar->GetFloatY());
							return;
						}
					}

					//以上在自身所在格未找到，则九宫格范围内找
					AreaIndexTPL(Area9) list;
					pGameStage->Get9AreaList(list, nAreaID);
					int nCount = list.Count();
					for (int i=0; i<nCount; i++)
					{
						GameArea* pArea = pGameStage->GetArea(list[i]);
						if ( pArea == NULL)
						{ continue; }

						GameObjectId objectId = InvalidGameObjectId;
						for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
						{
							BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
							//如果找到的怪物等级与玩家相差三级
							if (pChar != NULL 
								&& pChar->IsMonster() 
								&& static_cast<MonsterBaseEx*>(pChar)->GetMonsterType() == eMT_NormalMonster
								&& abs(pChar->GetLevel() - nLevel) < 3)
							{
								char szBuff[100];
								sprintf_s(szBuff, sizeof(szBuff)-1, "/AskForOneTarget %d %f %f", pChar->GetID(), pChar->GetFloatX(), pChar->GetFloatY());
								TellClient(szBuff);
								return;
							}
						}
					}

				}
				//如果自身格子及九宫格都未找到，则世界范围内查找
				int nMaxCount = theRunTimeData.theCharacters.GetSize();
				//因为怪物分配ID从5000开始，硬写在theCharacter里的。这里也硬写
				for (int i=5000; i<nMaxCount; i++)
				{
					BaseCharacter* pChar = theRunTimeData.GetCharacterByID(i);
					//如果找到的怪物等级与玩家相差三级
					if (pChar != NULL
						&& pChar->IsMonster() 
						&& static_cast<MonsterBaseEx*>(pChar)->GetMonsterType() == eMT_NormalMonster
						&& abs(pChar->GetLevel() - nLevel) < 3 
						&& pChar->GetMapID() == this->GetMapID())
					{
						char szBuff[100];
						sprintf_s(szBuff, sizeof(szBuff)-1, "/AskForOneTarget %d %f %f", pChar->GetID(), pChar->GetFloatX(), pChar->GetFloatY());
						TellClient(szBuff);
						return;
					}
				}

			}
			else
			{
				return;
			}   
		}
		else if (w.Compare(1, "FlyToMap"))
		{
			if(w.IsNumber(2) && w.IsNumber(3) && w.IsNumber(4))
			{
				int nMapID = atoi(const_cast<char*>(w.GetWord(2)));
				float fX   = atof(const_cast<char*>(w.GetWord(3)));
				float fY   = atof(const_cast<char*>(w.GetWord(4)));                

				FlyToMapReq( nMapID, fX, fY, 0.0f);
			}

		}
		else if (w.Compare(1, "LvlUp"))
		{
			if(w.IsNumber(2))
			{
				int nLevel = atoi(const_cast<char*>(w.GetWord(2)));
				ChangeExp( theExpStage.GetLevelupExp( nLevel ) );
			}

		}
		else if (w.Compare(1, "AddHp"))
		{
			SetHP( GetCharFightAttr()->hpMax.final );
			SetMP( GetCharFightAttr()->mpMax.final );

			MsgCharAttrChanged xChange;
			xChange.header.stID = GetID();
			xChange.AddAttrIntChange( CharAttr_HP, GetHP() );
			xChange.AddAttrIntChange( CharAttr_MP, GetMP() );
			xChange.CaluLength();
			GettheServer().SendMsgToView( &xChange, GetID(), false );
		}
		else if (w.Compare(1, "SetQuestState"))
		{
			int QuestId,QuestSate;
			if( w.IsNumber(2) && w.IsNumber(3) )
			{
				QuestId   = atoi(w.GetWord(2));
				QuestSate = atoi(w.GetWord(3));
				if ( QuestId<dr_MaxQuestId || QuestId >dr_MinQuestId)
				{
					SetQuestState( QuestId , QuestSate );
				}
			}
		}
		else if ( w.Compare(1, "LearnAllSkill") )
		{
			SetSkillExp( 60 );

			uint16 skillBegin = 0;
			switch ( GetProfession() )
			{
			case EArmType_Warrior:
				{ skillBegin = 1000; }
				break;
			case EArmType_Mage:
				{ skillBegin = 1030; }
				break;
			case EArmType_Taoist:
				{ skillBegin = 1090; }
				break;
			case EArmType_Assassin:
				{ skillBegin = 1060; }
				break;
			case EArmType_Hunter:
				{ skillBegin = 1120; }
				break;
			case EArmType_Sniper:
				{ skillBegin = 1000; }
				break;
			}

			for ( uint8 i=0; i<21; ++i)
			{
				LearnSkill( skillBegin+i, 4 );
			}
		}
		else if ( w.Compare(1, "ClearAllEquip") )
		{// 机器人清除
			for ( int i=0; i< EEquipPartType_MaxEquitPart; ++i )
			{ UnEquip( i, i ); }

			for ( int i = 0; i < _NormalItemBag.GetNowBagSize(); ++i )
			{
				if ( !_NormalItemBag.ClearItem(i) )
				{ continue;}
			}
		}
		else if ( w.Compare(1, "CreateMonster") )					//机器人命令:创建怪物luo.qin 3.18
		{
			//char szCmd[PARAM_STRINGMAX+1] = {0};

			if( w.IsNumber(2) && w.IsNumber(3) && w.IsNumber(4) && w.IsNumber(5) && w.IsNumber(6) )
			{
				int		nBotDBId     = atoi(const_cast<char*>(w.GetWord(2)));
				int		nMonsterId	 = atoi(const_cast<char*>(w.GetWord(3)));
				int		nMonsterNum  = atoi(const_cast<char*>(w.GetWord(4)));
				float	fX		     = atof(const_cast<char*>(w.GetWord(5)));
				float	fY		     = atof(const_cast<char*>(w.GetWord(6)));

				GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( nBotDBId );
				if ( pPlayer == NULL )
				{ return; }

				MonsterCreateData xCreateData;
				xCreateData.SetMapID( GetMapID() );
				xCreateData.SetPostionX( GetFloatX() );
				xCreateData.SetPostionY( GetFloatY() );
				xCreateData.SetMonsterID( nMonsterId );
				xCreateData.SetCount( nMonsterNum );
				xCreateData.SetSpecialType( MonsterDefine::SpecialPlayerVar );
				xCreateData.SetSpecialValue( GetDBCharacterID() );

				MonsterCreater::ProcessCreateNormalMonster( xCreateData );
			}

		}
		else if ( w.Compare( 1, "RemoveAllEquip" ))
		{
			//先清除身上装备和包裹装备
			//char szCmd[PARAM_STRINGMAX+1] = {0};

			if( w.IsNumber(2) )
			{
				int	nBotDBId = atoi(const_cast<char*>(w.GetWord(2)));


				GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( nBotDBId );
				if ( pPlayer == NULL )
				{ return; }

				pPlayer->RemoveAllItem( BT_NormalItemBag );

				int n_count = 0;
				for ( int i = 0; i < EEquipPartType_MaxEquitPart; ++i )
				{
					//得到放入包裹位置，找到空位置就放
					for ( int j = 0; j < pPlayer->_NormalItemBag.GetNowBagSize(); ++j )
					{
						int nItemID = pPlayer->_NormalItemBag.m_pPackItem[j].GetItemID();
						ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( nItemID );

						if ( pItem == NULL || nItemID <= 0 || nItemID == 65535)
						{
							n_count = j;
							break;
						}

					}

					pPlayer->UnEquip( i, n_count );
					//SCharItem* pEquip = GetVisualEquipItem( i );
					//if ( !pEquip )
					//{
					//	continue;
					//}
					//if (pEquip->GetItemID() != 0 && pEquip->GetItemID() != 65535)
					//{
					//	pPlayer->UnEquip( i, n_count );
					//	n_count++;
					//}
				}
				pPlayer->RemoveAllItem( BT_NormalItemBag );

			}
		}
		else if ( w.Compare(1, "ChangeEquip") )
		{
			//char szCmd[PARAM_STRINGMAX+1] = {0};

			if( w.IsNumber(2) )
			{
				int	nBotDBId = atoi(const_cast<char*>(w.GetWord(2)));

				GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( nBotDBId );
				if ( pPlayer == NULL )
				{ return; }

				int n_count = 0;
				for ( int i = 0; i < EEquipPartType_MaxEquitPart; ++i )
				{


					//得到放入包裹位置，找到空位置就放
					for ( int j = 0; j < pPlayer->_NormalItemBag.GetNowBagSize(); ++j )
					{
						int nItemID = pPlayer->_NormalItemBag.m_pPackItem[j].GetItemID();
						ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( nItemID );

						if ( pItem == NULL || nItemID <= 0 || nItemID == 65535)
						{
							n_count = j;
							break;
						}

					}

					pPlayer->UnEquip( i, n_count );


				}
				//开始循环让玩家去穿装备
				ItemBag* pBag = pPlayer->GetItemBagByBagType(BT_NormalItemBag);
				if ( pBag == NULL )
				{ return; }

				for ( int i = 0; i < pPlayer->_NormalItemBag.GetNowBagSize(); ++i )
				{
					int nItemID = pPlayer->_NormalItemBag.m_pPackItem[i].GetItemID();
					ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( nItemID );

					if ( pItem == NULL || nItemID <= 0 || nItemID == 65535)
					{
						continue;
					}

					MsgGetItem2 getitem;
					getitem.item  = pPlayer->_NormalItemBag.m_pPackItem[i];
					getitem.itemSource = 0;

					getitem.item.itembaseinfo.stPacketIdx = i;// = ReturnItemID( BT_NormalItemBag, pItem->ustItemID );			//luo.qin 3.22
					getitem.header.stID = pPlayer->GetID();
					getitem.enResult = MsgGetItem2::RESULT_SUCCESS;
					GettheServer().SendMsgToSingle( &getitem, this );
				}
				//pPlayer->RemoveAllItem( BT_NormalItemBag );
			}
		}
	}   
}

// 处理GM指令
#define BEGIN_COMMAND_EX( content, command, otherExpression ) \
	if ( 0 == stricmp( content, command) && (otherExpression) ) \
{ 

#define BEGIN_COMMAND( content, command ) \
	if ( 0 == stricmp( content, command ) ) \
{ 

#define END_COMMAND \
	return;\
}

void GamePlayer::OnGMCommand( const MsgChat* pMsgChat, unsigned int nGMLevel )
{
	if ( pMsgChat == NULL )		{ return; }

	if ( nGMLevel < 1 )			{ return; }	// 1级GM指令

	ZeroMemory(m_szCmdHead,sizeof(m_szCmdHead));//每次解析先清空

	const char* szCommand = pMsgChat->szString + 1;
	const char* szStr = szCommand;

	// 获取GM指令头
	if( 1 != sscanf( szCommand,"%31s",m_szCmdHead) )
	{ return; }

	//先记录用户的gm命令日志
	if (!theLogEventService.LogGMCommand(GetAccountID(),GetDBCharacterID(),GetCharName(),szCommand,GetIp(),GetCharName()))
	{
		Log( theXmlString.GetString(eServerLog_UseGmCommand), szCommand, nGMLevel );
	}

	BEGIN_COMMAND_EX( m_szCmdHead, "flytomap" , nGMLevel & GP_FLYTOMAP )    // 飞地图
		ProcessFlyToMap( szCommand );
	END_COMMAND

	BEGIN_COMMAND_EX( m_szCmdHead, "SelectChannel" , nGMLevel & GP_FLYTOMAP )    // 飞地图
		ProcessSelectChannel( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "kickplayer" , nGMLevel & GP_KICKCHAR )  // 踢人
		ProcessKickPlayer( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "banspeak" , nGMLevel & GP_KICKCHAR )    // 禁言
		ProcessBanSpeak( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "broadcast" , nGMLevel & GP_BULL )       // 人为公告
		ProcessBroadcast( szCommand, pMsgChat ); 
	END_COMMAND

		//zhuxincong
		BEGIN_COMMAND_EX(m_szCmdHead, "TelltheCountry" , nGMLevel & GP_BULL)	//只告诉特定国家的公告
		ProcessTelltheCountry(szCommand,pMsgChat);
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "prompt" , nGMLevel & GP_BULL )          // 游戏提示
		ProcessPrompt( szCommand ); 
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "system" , nGMLevel & GP_BULL )          // 程序系统提示
		ProcessSystem( szCommand, SystemWorld, pMsgChat ); 
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "beckonplayer" , nGMLevel & GP_BECKONPLAYER  ) // 拉人
		ProcessCallPlayer( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "flytoplayer" , nGMLevel & GP_FLYTOPLAYER  )   // 飞到玩家身边
		ProcessFlyToPlayer( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "Self" , nGMLevel & GP_SETADDEXP  )
		ProcessSetCharacter( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "DestroyItem" , nGMLevel & GP_ADDITEM  )
		ProcessDestroyItem( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "CreateItem" , nGMLevel & GP_ADDITEM  )
		ProcessCreateItem( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "CreateEquipRand" , nGMLevel & GP_ADDITEM  )
		ProcessCreateEquipRand( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "TestLog" , nGMLevel & GP_ADDITEM  )
		ProcessTestLogService( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "CreateMonster" , nGMLevel & GP_SUNMMONMONSTER )
		ProcessCreateMonster( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "CreateMonsterEx" , nGMLevel & GP_SUNMMONMONSTER )
		ProcessCreateMonsterEx( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "CallSummonMonster" , nGMLevel & GP_SUNMMONMONSTER )
		ProcessCallSummonMonster( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "CreateItemPK" , nGMLevel & GP_SUNMMONMONSTER )
		ProcessCreateItemPackage( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "LearnSkill" , nGMLevel & GP_LEARNSKILL )
		ProcessLearnSkill( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "SetQuestState" , nGMLevel & GP_ROOT )
		ProcessSetQuestState( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "DoneQuest" , nGMLevel & GP_ROOT )
		ProcessDoneQuest( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ChangeLuckRewardLevel" , nGMLevel & GP_ROOT )
		ProcessChangeLuckLevel( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ResetLuckReward" , nGMLevel & GP_ROOT )
		ProcessResetLuckReward( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "StartLuckReward" , nGMLevel & GP_ROOT )
		ProcessStartLuckReward( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "RunLuckReward" , nGMLevel & GP_ROOT )
		ProcessRunLuckReward( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ReceiveLuckReward" , nGMLevel & GP_ROOT )
		ProcessReceiveLuckReward( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ChangeLuckRewardType" , nGMLevel & GP_ROOT )
		ProcessChangeLuckType( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ChangeCheckCheat" , nGMLevel & GP_ROOT )
		ProcessChangeCheckCheat( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "CheckCheat" , nGMLevel & GP_ROOT )
		ProcessCheckCheat( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ShowLastSaveTime" , nGMLevel & GP_ADDITEM  )
		ProcessShowLastSaveTime( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ShowEnmity", nGMLevel & GP_ADDITEM )
		ProcessShowEnmity( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "SetCostTime", nGMLevel & GP_ADDITEM )
		ProcessSetCostTime( szCommand );
	END_COMMAND
		
		BEGIN_COMMAND_EX( m_szCmdHead, "ShowDamageEnmity", nGMLevel & GP_ADDITEM )
		ProcessShowDamageEnmity( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ShowServerPos", nGMLevel & GP_ADDITEM )
		ProcessShowServerPos( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "FindCharByAccount", nGMLevel & GP_ADDITEM   )
		ProcessFindCharByAccount( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "FindCharByName", nGMLevel & GP_ADDITEM   )
		ProcessFindCharByName( szCommand ); // 用角色名查找玩家
	END_COMMAND    

		BEGIN_COMMAND_EX( m_szCmdHead, "GetCharList", nGMLevel & GP_ADDITEM  )
		ProcessGetCharacterList( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "TargetSay", nGMLevel & GP_ADDITEM  )
		ProcessTargetSay( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ApplyBuff", nGMLevel & GP_ADDITEM  )
		ProcessApplyStatus( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "AddMount", nGMLevel & GP_ADDITEM  )
		ProcessAddMount( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "AddPet", nGMLevel & GP_ADDITEM  )
		ProcessAddPet( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "AddPetExp", nGMLevel & GP_ADDITEM  )
		ProcessAddPetExp( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "EquipLevel", nGMLevel & GP_ADDITEM  )
		ProcessEquipLevel( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ExpChange", nGMLevel & GP_KILLTARGET  )
		ProcessExpChange( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ShowPos", nGMLevel & GP_ADDITEM  )
		ProcessShowPos( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "PlayEffect", nGMLevel & GP_ADDITEM  )
		ProcessPlayEffect( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ChangeLevel", nGMLevel & GP_ADDITEM  )
		ProcessPlayerLevel( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "CallGraphic", nGMLevel & GP_ADDITEM  )
		ProcessCallGraphic( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "GuildVar", nGMLevel & GP_ROOT  )
		ProcessGuildVar( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "GetTargetDBID", nGMLevel & GP_ROOT  )
		ProcessGetTargetDBID( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "GetProcessList", nGMLevel & GP_ROOT  )
		ProcessGetProcessList( szCommand );
	END_COMMAND
		/*BEGIN_COMMAND_EX( m_szCmdHead, "Ban", nGMLevel & GP_ADDITEM  )
		ProcessBan( szCommand );
	END_COMMAND*/
		BEGIN_COMMAND_EX( m_szCmdHead, "BanAccount", nGMLevel & GP_ADDITEM  )
		ProcessBanAccouynt( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "SetCharShow", nGMLevel & GP_ADDITEM  )
		ProcessSetNpcShow( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "CheckupElement", nGMLevel & GP_ROOT  )
		ProcessCheckupElement( szCommand );
	END_COMMAND    

		BEGIN_COMMAND_EX( m_szCmdHead, "SubEquipHp", nGMLevel & GP_ROOT  )
		ProcessSubEquipHp( szCommand );
	END_COMMAND   

		BEGIN_COMMAND_EX( m_szCmdHead, "SuitLevelUp", nGMLevel & GP_ROOT  )
		ProcessSuitLevelUp( szCommand );
	END_COMMAND   

		BEGIN_COMMAND_EX( m_szCmdHead, "UnLockItem", nGMLevel & GP_ROOT  )
		ProcessUnLockItem( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "SetAreaCurrentReputation", nGMLevel & GP_ADDITEM  )
		ProcessSetAreaCurrentReputation( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "SetAreaMaxReputation", nGMLevel & GP_ADDITEM )
		ProcessSetAreaMaxReputation( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "Destroy", nGMLevel & GP_DETROY )
		ProcessInteresting( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "AddFriendly", nGMLevel & GP_ROOT )
		ProcessAddFriendly( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "SecondPassword", nGMLevel & GP_ROOT )
		ProcessQuerySecondPassword( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "SetOfficial", nGMLevel & GP_ROOT )
		ProcessSetCountryOfficial( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "SetGuildKing", nGMLevel & GP_ROOT )
		ProcessSetGuildKing( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ChangePlayerSecondPwd", nGMLevel & GP_ROOT )
		ProcessChangePlayerSecondPwd( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "AddCountryMoney", nGMLevel & GP_ROOT )
		ProcessAddCountryMoney( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ShowProperty", nGMLevel & GP_ROOT )
		ProcessShowProperty( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "CreateGuild", nGMLevel & GP_ROOT )
		ProcessCreateGuild( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "TellCountry", nGMLevel & GP_ROOT )
		ProcessTestTellCountry( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "SetAreaVar", nGMLevel & GP_ROOT )
		ProcessTestSetAreaVar( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "IsCountryQuestOpen", nGMLevel & GP_ROOT )
		ProcessTestCountryQuestOpen( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ChangeSignature", nGMLevel & GP_ROOT )
		ProcessChangeSignature( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "KillTarget", nGMLevel & GP_ROOT )
		ProcessKillTarget( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "RemoveTarget", nGMLevel & GP_ROOT )
		ProcessRemoveTarget( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ShowPlayerEnmity", nGMLevel & GP_ROOT )
		ProcessShowPlayerEnmity( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "KillGridTarget", nGMLevel & GP_ROOT )
		ProcessKillGridTarget( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ClearCountryNameChange", nGMLevel & GP_ROOT )
		ProcessClearChangeCountryName( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "MonsterInfo", nGMLevel & GP_SUNMMONMONSTER )
		ProcessMonsterInfo( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "ServVersion", nGMLevel & GP_ROOT )
		ProcessShowServVersion( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "SignUpCampBattle", nGMLevel & GP_ROOT )
		ProcessSignUpCampBattle( szCommand );
	END_COMMAND

		BEGIN_COMMAND_EX( m_szCmdHead, "EnterCampBattle", nGMLevel & GP_ROOT )
		ProcessEnterCampBattle( szCommand );
	END_COMMAND 

		BEGIN_COMMAND_EX( m_szCmdHead, "KillCampBattleMonster", nGMLevel & GP_ROOT )
		ProcessKillCampBattleMonster( szCommand );
	END_COMMAND 

		BEGIN_COMMAND_EX( m_szCmdHead, "ChangeCampBattleStatus", nGMLevel & GP_ROOT )
		ProcessChangeCampBattleStatus( szCommand );
	END_COMMAND 

		BEGIN_COMMAND_EX( m_szCmdHead, "ChangeCountryWarStatus", nGMLevel & GP_ROOT )
		ProcessCountryWarStatus( szCommand );
	END_COMMAND 

		BEGIN_COMMAND_EX( m_szCmdHead, "TestTimeVar", nGMLevel & GP_ROOT )
		ProcessTestTimeVar( szCommand );
	END_COMMAND 

		BEGIN_COMMAND_EX( m_szCmdHead, "AddXinFa", nGMLevel & GP_ROOT )
		ProcessAddXinFa( szCommand );
	END_COMMAND 

		BEGIN_COMMAND_EX( m_szCmdHead, "ChangeFamilyProsperity", nGMLevel & GP_ROOT )
		ProcessFamilyProsperity( szCommand );
	END_COMMAND 

		BEGIN_COMMAND_EX(m_szCmdHead, "ChangeCountry", nGMLevel & GP_ADDITEM )
		ProcessAddCC(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "JoinCountryWar", nGMLevel & GP_ADDITEM )
		ProcessJoinCountryWar(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "SetCountryWar", nGMLevel & GP_ADDITEM )
		ProcessSetCountryWar(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "SetGuildWar", nGMLevel & GP_ADDITEM )
		ProcessSetGuildWar(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "JoinGuildWar", nGMLevel & GP_ADDITEM )
		ProcessJoinGuildWar(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "ChangePetMode", nGMLevel & GP_ADDITEM )
		ChangePetMode(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "ChangePet", nGMLevel & GP_ADDITEM )
		ChangePet(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "ChangeQuestStates", nGMLevel & GP_ADDITEM )
		ChangeQuestStates(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "OpenGuildGeneralBattleSum", nGMLevel & GP_ADDITEM )
		OpenGuildGeneralBattleSum(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "OpenGuildGeneralBattle", nGMLevel & GP_ADDITEM )
		OpenGuildGeneralBattle(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "EnterGuildGeneralBattle", nGMLevel & GP_ADDITEM )
		EnterGuildGeneralBattle(szCommand);
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "EndGuildGeneralBattle", nGMLevel & GP_ADDITEM )
		EndGuildGeneralBattle(szCommand);	
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "ondeath", nGMLevel & GP_ADDITEM )
		ProcessOndeath(szCommand);	
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "greatCatch", nGMLevel & GP_ADDITEM )
		ProcessGreatCatch(szCommand);	
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "mapmonsterinfo", nGMLevel & GP_ADDITEM )
		ProcessMapmonsterinfo(szCommand);	
	END_COMMAND

		BEGIN_COMMAND_EX(m_szCmdHead, "relivemapmonster", nGMLevel & GP_ADDITEM )
		ProcessRelivemapmonster(szCommand);	
	END_COMMAND

}

void GamePlayer::ProcessSelectChannel( const char* szCommand )
{
	//char szCmd[64] = {0};

	//char szChannel[PARAM_STRINGMAX+1] = {0};
	int channelid = 0;
	if( 2 != sscanf( szCommand,"%s%d", m_szCmdHead, &channelid) )
		return;

	MsgChangeChannelREQ channel;	
	channel.nTargetServerId = channelid;	
	OnMsgChangeChannel(&channel);
}

void GamePlayer::ProcessFlyToMap( const char* szCommand )
{   
	//char szCmd[64] = {0};

	int   iMapID = 0;
	float fX = 0;
	float fY = 0;

	char szMapID[PARAM_STRINGMAX+1] = {0};
	if( 4 != sscanf( szCommand,"%s%s%f%f", m_szCmdHead, szMapID, &fX, &fY ) )
		return;

	WordParser word;
	if( word.IsNumber( szMapID ) )
	{
		iMapID = atoi(szMapID);
		if ( iMapID >= 0)
		{
			FlyToMapReq(iMapID , fX, fY, 0.0f ); 
		}
	}
}

void GamePlayer::ProcessKickPlayer( const char* szCommand )
{        
	char szParam[PARAM_STRINGMAX+1] = {0};
	//char szCmd[64] = {0};

	if( 2 != sscanf( szCommand,"%s %s",m_szCmdHead, szParam) )
		return;

	BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetGamePlayerByName( szParam );

	if(!pChar) 
		return;

	pChar->Log( "Exit by kickplayer" );
	pChar->ExitWorld(__FUNCTION__, __FILE__, __LINE__,ET_SystemBeKick);
}

void GamePlayer::ProcessBanSpeak( const char* szCommand )
{        
	char szName[64] = { 0 };
	//char szCmd[64] = { 0 };
	uint32 dwDBID = InvalidLogicNumber;
	uint32 dwBanSpeakTime = 60;     // 默认10分钟

	if( 4 != sscanf( szCommand,"%s %u %s %u",m_szCmdHead, &dwBanSpeakTime, szName, &dwDBID ) 
		&& 3 != sscanf( szCommand,"%s %u %s",m_szCmdHead, &dwBanSpeakTime, szName ) )
		return;

	if ( dwBanSpeakTime > 70000 )
	{ dwBanSpeakTime = 70000; }

	GS2GSBanSpeak xBan;
	GamePlayer* pPlayer = NULL;
	if ( szName[0] != 0 && stricmp( szName, "null" ) != 0 )
	{
		pPlayer = theRunTimeData.GetGamePlayerByName( szName );
		HelperFunc::SafeNCpy( xBan.szName, szName, sizeof( xBan.szName ) );
	}
	else if ( dwDBID != InvalidLogicNumber )
	{
		pPlayer = theRunTimeData.GetGamePlayerByDBID( dwDBID );
		xBan.dwDBID = dwDBID;
	}
	else
	{
		return;
	}

	if( pPlayer == NULL ) 
	{
		xBan.dwBanTime = dwBanSpeakTime;
		GettheServer().SendMsgToCenterServer( &xBan );
	}
	else
	{
		pPlayer->SetBanSpeakTime( dwBanSpeakTime * 60000, true );     
	}
}

void GamePlayer::ProcessBroadcast( const char* szCommand, const MsgChat* pMsgChat /* = NULL */ )
{
	char szParam[PARAM_STRINGMAX+1] = {0};

	std::string sstr = szCommand;
	if (sstr.empty())
		return;

	std::string strBull = sstr.substr(sstr.find(" ")+1, sstr.length());
	if (strBull.empty())
		return;

	strncpy_s(szParam, sizeof( szParam ), strBull.c_str(),sizeof(szParam) -1 );
	// '^' 转换为空格
	int nLen = strlen( szParam );
	for ( int n=0; n< nLen; n++ )
	{
		if ( szParam[n] == '^' )
		{
			szParam[n] = ' ';
		}
	}

	char itemHyberMem[dr_MaxChatString] = { 0 };    
	int nItemCount = FormatChatItemData( pMsgChat, itemHyberMem, dr_MaxChatString );

	MsgChat chat(MsgChat::CHAT_TYPE_BULL);
	chat.SetString( szParam, itemHyberMem, nItemCount );
	GettheServer().SendMsgToWorld( &chat, true );
}

void GamePlayer::ProcessPrompt( const char* szCommand, const MsgChat* pMsgChat /* = NULL */ )
{
	char szParam[PARAM_STRINGMAX+1] = {0};

	std::string sstr = szCommand;
	if (sstr.empty())
		return;

	std::string strBull = sstr.substr(sstr.find(" ")+1, sstr.length());
	if (strBull.empty())
		return;

	strncpy_s(szParam,sizeof( szParam ), strBull.c_str(),sizeof(szParam) -1 );
	// '^' 转换为空格
	int nLen = strlen( szParam );
	for ( int n=0; n< nLen; n++ )
	{
		if ( szParam[n] == '^' )
		{
			szParam[n] = ' ';
		}
	}

	char itemHyberMem[dr_MaxChatString] = { 0 };    
	int nItemCount = FormatChatItemData( pMsgChat, itemHyberMem, dr_MaxChatString );

	MsgChat chat(MsgChat::CHAT_TYPE_GAMEPROMPT);
	chat.SetString( szParam, itemHyberMem, nItemCount );
	GettheServer().SendMsgToSingle( &chat, this );
}

void GamePlayer::ProcessTelltheCountry(const char* szCommand,const MsgChat* pMsgChat /*= NULL */)
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	char szParam[PARAM_STRINGMAX+1] = {0};
	int nCountryID ;
	if ( 3 == sscanf( szCommand,"%s%d%s",m_szCmdHead, &nCountryID,&szParam ) )
	{
		char itemHyberMem[dr_MaxChatString] = { 0 };    
		int nItemCount = FormatChatItemData( pMsgChat, itemHyberMem, dr_MaxChatString );

		MsgChat chat(MsgChat::CHAT_TYPE_GAMEPROMPT);
		chat.SetString( szParam, itemHyberMem, nItemCount );
		GettheServer().SendMsgToCountry( &chat, nCountryID, true);
	}

}

void GamePlayer::ProcessSystem( const char* szCommand, uint8 uchType, const MsgChat* pMsgChat /* = NULL */ )
{
	if ( szCommand == NULL || *szCommand == 0 )
	{ return; }

	char szParam[PARAM_STRINGMAX+1] = {0};

	std::string sstr = szCommand;
	if (sstr.empty())
		return;

	std::string strBull = sstr.substr(sstr.find(" ")+1, sstr.length());
	if (strBull.empty())
		return;

	strncpy_s(szParam, sizeof( szParam ), strBull.c_str(),sizeof(szParam) -1 );
	// '^' 转换为空格
	int nLen = strlen( szParam );
	for ( int n=0; n< nLen; n++ )
	{
		if ( szParam[n] == '^' )
		{
			szParam[n] = ' ';
		}
	}

	char itemHyberMem[dr_MaxChatString] = { 0 };    
	int nItemCount = FormatChatItemData( pMsgChat, itemHyberMem, dr_MaxChatString );

	MsgChat chat( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
	chat.SetString( szParam, itemHyberMem, nItemCount );
	if (pMsgChat)
	{
		chat.type = pMsgChat->type;
	}
	switch ( uchType )
	{
	case SystemServer:      // 单服
		GettheServer().SendMsgToWorld( &chat, false );
		break;
	case SystemWorld:       // 世界
		GettheServer().SendMsgToWorld( &chat, true );
		break;
	case SystemSingle:      // 个人
		SendMessageToClient( &chat );
		break;
	default:
		break;
	}
}

void GamePlayer::ProcessSystem( uint8 uchType, const char* szCommand, const char* szItemHyberMem, int nItemCount /* = 1*/ )
{
	if ( szCommand == NULL || szItemHyberMem == NULL || *szCommand == 0 || *szItemHyberMem == 0)
	{ return; }

	//char szParam[PARAM_STRINGMAX+1] = {0};

	//std::string sstr = szContent;
	//if (sstr.empty())
	//    return;

	//std::string strBull = sstr.substr(sstr.find(" ")+1, sstr.length());
	//if (strBull.empty())
	//    return;

	//strncpy_s(szParam, sizeof( szParam ), strBull.c_str(),sizeof(szParam) -1 );
	//// '^' 转换为空格
	//int nLen = strlen( szParam );
	//for ( int n=0; n< nLen; n++ )
	//{
	//    if ( szParam[n] == '^' )
	//    { szParam[n] = ' '; }
	//}

	//char itemHyberMem[dr_MaxChatString] = { 0 };    
	//int nItemCount = FormatChatItemData( pMsgChat, itemHyberMem, dr_MaxChatString );

	MsgChat chat( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
	chat.SetString( szCommand, szItemHyberMem, nItemCount );

	switch ( uchType )
	{
	case SystemServer:      // 单服
		GettheServer().SendMsgToWorld( &chat, false );
		break;
	case SystemWorld:       // 世界
		GettheServer().SendMsgToWorld( &chat, true );
		break;
	case SystemSingle:      // 个人
		SendMessageToClient( &chat );
		break;
	default:
		break;
	}
}

void GamePlayer::ProcessFindCharByAccount( const char* szCommand )
{
	char szParam[PARAM_STRINGMAX+1] = {0};
	//char szCmd[64]    = {0};

	if( 2 != sscanf( szCommand,"%s %s",m_szCmdHead, szParam) )
		return;

	for(int i=0; i<theRunTimeData.theCharacters.GetSize(); i++)
	{
		BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID(i);
		if( !pChar )
			continue;

		if( !pChar->IsPlayer() )
			continue;

		GamePlayer* pPlayer = (GamePlayer*)pChar;
		if ( !pPlayer )
			continue;

		if( strcmp(pPlayer->m_szLoginName, szParam) == 0 )
		{
			char szMsg[500] = {0};
			sprintf_s(szMsg, sizeof(szMsg)-1, "!findchar %s", pPlayer->GetCharName());
			TellClient( theXmlString.GetString(eClient_AddInfo_2slk_95),pPlayer->GetMapID(), pPlayer->GetTileX(), pPlayer->GetTileY());

			MsgChat chat(MsgChat::CHAT_TYPE_PRIVATE);
			chat.SetString(szMsg);
			GettheServer().SendMsgToSingle( &chat, this );
			return;    
		}
	}

	TellClient("player not found!");

}

void GamePlayer::ProcessFindCharByName( const char* szCommand )
{       
	char szParam[PARAM_STRINGMAX+1] = {0};
	//char szCmd[64]    = {0};

	if( 2 != sscanf( szCommand,"%s %s",m_szCmdHead, szParam) )
		return;

	StringContainer players;
	theRunTimeData.GetGamePlayersByName(szParam, players);

	char szMsg[1024] = {0};
	ItrStringContainer it = players.begin();
	std::string strResult;
	for ( ;it!=players.end(); ++it )
	{
		strResult += (*it);
		strResult += "|";
	}
	sprintf_s(szMsg, sizeof(szMsg)-1, "!findchar %s", strResult.c_str());

	MsgChat chat(MsgChat::CHAT_TYPE_PRIVATE);
	chat.SetString(szMsg);
	GettheServer().SendMsgToSingle( &chat, this );
}

void GamePlayer::ProcessSetCharacter( const char* szCommand )
{
	WordParser words;
	if( words.Parse( szCommand ) > 0 )
	{
		if( words.Compare( 0, "Self" ) )
		{ // 设置经验
			if( words.Compare( 1, "AddMoney" ) )
			{
				int nMoney = atoi( words.GetWord( 2 ) );
				OperateMoney( EOT_Add, nMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_GMAddmoney);
			}
			/*
			* Author: 2012-9-26 17:08:54 liaojie
			* Desc:   增加金锭
			*/
// 			else if ( words.Compare(1, "AddJinDing") )
// 			{   
// 				int nJinDing = atoi(words.GetWord(2));
// 
// 				DBMsgOperateAccountMoney operatejinding;
// 				operatejinding.header.stID = GetID();
// 				operatejinding.account_id = GetAccountID();
// 				operatejinding.character_id = GetDBCharacterID();
// 				operatejinding.modify_money = nJinDing;
// 				operatejinding.operate_flag = 1;
// 				GettheDBCon().SendMsg( &operatejinding, GetLifeCode() );
// 
// 				//OperateJinDing(EOT_Add,nJinDing,__FUNCTION__,__LINE__);
// 			}
			else if (words.Compare(1, "AddJiFen"))
			{
				int nJiFen = atoi(words.GetWord(2));

				DBMsgOperateAccountConsumeScore operateJiFen;
				operateJiFen.header.stID = GetID();
				operateJiFen.account_id = GetAccountID();
				operateJiFen.character_id = GetDBCharacterID();
				operateJiFen.modify_money = nJiFen;
				operateJiFen.operate_flag = 1;
				GettheDBCon().SendMsg( &operateJiFen, GetLifeCode() );


			}
			else if(words.Compare(1, "AddJiaoZi"))
			{
				int nJiaoZi = atoi( words.GetWord(2));
				OperateJiaoZi( EOT_Add, nJiaoZi, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_GMAddmoney);
			}
// 			else if (words.Compare(1, "AddJinPiao"))
// 			{
// 				int nJinPiao = atoi(words.GetWord(2));
// 				OperateJinPiao( EOT_Add, nJinPiao,  __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_GMAddmoney);
// 			}
			else if (words.Compare(1, "AddTitle"))
			{
				int nTitleID = atoi(words.GetWord(2));
				AddTitle(nTitleID);
			}
			else if (words.Compare(1, "RemoveTitle"))
			{
				int nTitleID = atoi(words.GetWord(2));
				RemoveTitle(nTitleID);
			}
			else if (words.Compare(1, "AddExploit"))
			{
				int nExploit = atoi(words.GetWord(2));
				OperateExploit( EOT_Add, nExploit, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_GMAddmoney);
			}
			else if (words.Compare(1, "AddReputation"))
			{
				int nReputation = atoi(words.GetWord(2));
				OperateReputation( EOT_Add, nReputation, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_GMAddmoney);
			}
			else if (words.Compare(1, "AddHonour"))
			{
				int nHonour = atoi(words.GetWord(2));
				OperateHonour( EOT_Add, nHonour, __FUNCTION__, __LINE__,ePlayerMoneySourceType_GMAddmoney );
			}
			else if (words.Compare(1, "AddGuildOffer"))
			{
				int nGuildOffer = atoi(words.GetWord(2));
				OperateGuildOffer( GuildDefine::OperateAdd, nGuildOffer );
			}
			else if (words.Compare(1,"AddGuildExp"))
			{
				int nGuildExp = atoi(words.GetWord(2));
				OperateGuildExp(GuildDefine::OperateAdd, nGuildExp);
			}
			else if (words.Compare(1, "AddRecipe"))
			{
				int nRecipeID = atoi(words.GetWord(2));
				Script_AddRecipe(nRecipeID);
			}
			else if( words.Compare( 1, "SetHP" ) )
			{
				int nHp = atoi( words.GetWord( 2 ) );
				Script_SetHp( nHp, EOT_Add );
			}
			else if( words.Compare( 1, "AddExp" ) )
			{
				int nExp = atoi( words.GetWord( 2 ) );
				if( nExp <= 0 )
				{
					nExp = theExpStage.GetPLevelupExp( GetLevel()+1 );
				}
				IncreaseExp( nExp, 0 );
			}
			else if( words.Compare( 1, "AddDaoxing" ) )
			{
				int nValue = atoi( words.GetWord( 2 ) );
				OperateDaoxing(EOT_Add, nValue, __FUNCTION__, __LINE__ );
			}
			else if( words.Compare( 1, "ChangeLevel" ) )
			{
				int nLevel = atoi( words.GetWord( 2 ) );
				if( nLevel <= 0 )
				{ return; }

				int targetLevel = nLevel;
				if ( targetLevel <= 0)
				{ targetLevel = 1; }

				int64 nLevelExp = theExpStage.GetLevelupExp( targetLevel );
				ChangeExp( nLevelExp );
			}
			else if( words.Compare( 1, "SetMP" ) )
			{
				int nMp = atoi( words.GetWord( 2 ) );
				Script_SetMp( nMp, EOT_Add );
			}
			else if (words.Compare(1,"ChangeSpeed"))
			{
				float fMoveSpeed = atof(words.GetWord(2));                
				GetCharFightAttr()->moveSpeed.base = fMoveSpeed;
				GetCharFightAttr()->moveSpeed.UpdateFinal();
				ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() );
			}
			else if (words.Compare(1,"SetXP"))
			{
				int iFightPoint = atoi(words.GetWord(2));
				if( iFightPoint <= 0 )
				{
					SetXP( 100 );
				}
				else
				{
					SetXP( iFightPoint );
				}

				ChangeAttr( CharAttr_XPValue, GetXP() );

			}
			else if ( words.Compare(1,"SetCritical") )
			{
				short nType = atoi(words.GetWord(2));

				if ( nType<=0 )
				{ bAlwayCritical = false; }
				else
				{ bAlwayCritical = nType == 1; }

				TellClient("Critical Mode [%d]", nType);
			}
			else if ( words.Compare(1,"OpenFightInfo") )
			{
				short nType = atoi(words.GetWord(2));

				if ( nType<=0 )
				{ bShowFightInfo = false; }
				else
				{ bShowFightInfo = nType == 1; }

				TellClient("OpenFightInfo Mode [%d]", nType);
			}
			else if ( words.Compare(1,"SetSkillExp") )
			{
				int iSkillExp = atoi(words.GetWord(2));

				if ( iSkillExp<=0 )
				{ iSkillExp = 0; }

				SetSkillExpUnUsed( iSkillExp );
				ChangeAttr( CharAttr_SkillExpNotUsed,  GetSkillExpUnUsed(), true );
				TellClient("SkillExp [%d]", iSkillExp);
			}
			else if ( words.Compare(1,"SetNormalAttackSpeed") )
			{
				int iNormalAttackSpeed = atoi(words.GetWord(2));
				GetCharFightAttr()->attackSpeed.base = iNormalAttackSpeed;
				GetCharFightAttr()->attackSpeed.UpdateFinal();

				ChangeAttr( CharAttr_AttackSpeed, GetCharFightAttr()->attackSpeed.final, true );
				TellClient("NormalAttackSpeed [%d]", iNormalAttackSpeed);
			}
			else if ( words.Compare(1,"AddBagSize"))
			{
				int nBagType = atoi(words.GetWord(2));
				int nNum = atoi(words.GetWord(3));
				switch ( nBagType )
				{
				case BT_NormalItemBag:
					AddNormalBagNowSize( nNum );
					break;
				case BT_MaterialBag:
					AddMaterialBagNowSize( nNum );
					break;
				default:
					return;
					break;
				}
			}
			//else if ( words.Compare(1,"AddMountExp"))
			//{
			//    int nExp = atoi( words.GetWord( 2 ) );
			//    if( nExp <= 0 )
			//        nExp = theExpStage.GetSkillLevelUpExp( GetLevel()+1 );

			//    _mountManager.AddActiveMountExp( nExp * MOUNT_EXP_MODULUS );
			//}
			else if ( words.Compare(1,"AddPetExp"))
			{
				int nExp = atoi( words.GetWord( 2 ) );

				_petManager.AddActivePetExp( nExp  );
			}
			else if ( words.Compare(1,"AddEnergy"))
			{
				gCharInfoServer.baseinfo.liveinfo.activity = gCharInfoServer.baseinfo.liveinfo.activityMax;
				ChangeAttr( CharAttr_Energy, gCharInfoServer.baseinfo.liveinfo.activity, true );
			}
			else if ( words.Compare(1, "SetPKMode") )
			{
				int nValue = atoi( words.GetWord( 2 ) );
				GMSetPKMode( nValue );
			}
			else if ( words.Compare(1, "SetPKValue") )
			{
				int nValue = atoi( words.GetWord( 2 ) );
				SetPKValue( nValue, PKValueOp_Set );
			}
			else if ( words.Compare(1, "AddPKValue") )
			{
				int nValue = atoi( words.GetWord( 2 ) );
				SetPKValue( nValue, PKValueOp_Add );
			}
			else if ( words.Compare(1, "clearskillcd") )
			{
				unsigned short ustSkillID = InvalidLogicNumber;
				if ( words.GetWordCount() == 3 )
				{
					ustSkillID = atoi( words.GetWord( 2 ) );
				}

				ClearSkillCollDown( ustSkillID );
			}
			else if ( words.Compare(1, "callcode") )
			{   
				//                 MsgReqGraphicCode msg;
				//                 bool bResult = _graphicCodeManager.MakeReqGraphicCode(msg);
				//                 if ( bResult )
				//                 { GettheServer().SendMsgToSingle(&msg, this);}
				GraphicCodeCheckCommunication::SCheckReqMsg msg;
				msg.checkType = GraphicCodeCheckCommunication::ECT_GraphicCode;
				msg.nIDNeedToCheck = GetDBCharacterID();
				theGraphicCodeCheckCommunication.AddCheckReqMsg(msg);
			}
			else if ( words.Compare(1, "jinding") )
			{   
				DBMsgReqAccountBilling msg;
				msg.guid = GetAccountID();
				GettheDBCon().SendMsgToDatabaseServer( &msg );
			}
			else if ( words.Compare(1, "destroyitem"))
			{
				char szContent[256] = {0};
				int bagType  = atoi( words.GetWord( 2 ) );
				int bagIndex = atoi( words.GetWord( 3 ) );
				sprintf_s( szContent,"DestroyItem %s %d %d", GetCharName(), bagType, bagIndex );
				ProcessDestroyItem( szContent );
			}
			else if ( words.Compare(1, "AddXinFa"))
			{
				int iWhichXinFa  =  atoi( words.GetWord( 2 ) );
				int nLevel       =  atoi( words.GetWord( 3 ) );
				bool bCheck      =  atoi( words.GetWord( 4 ) );

				LearnXinFa( iWhichXinFa, nLevel, bCheck );
			}
		}
	}
}

void GamePlayer::ProcessGetCharacterList( const char* szCommand )
{
	MsgCharList msgList;
	for(int i=0; i<dr_worldMaxPlayers; ++i)
	{
		BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID(i);
		if(!pChar)
			continue;

		if( pChar->IsPlayer())
			continue;

		GamePlayer* pPlayer = (GamePlayer*)pChar;
		if ( !pPlayer )
			continue;

		strncpy_s(msgList.charInfo.szCharName, sizeof( msgList.charInfo.szCharName ), pPlayer->GetCharName(), sizeof(msgList.charInfo.szCharName)-1);
		strncpy_s(msgList.charInfo.szAccount, sizeof( msgList.charInfo.szAccount ), pPlayer->m_szLoginName, sizeof(msgList.charInfo.szAccount)-1);
		strncpy_s(msgList.charInfo.szIP, sizeof( msgList.charInfo.szIP ), pPlayer->m_szLoginIP, sizeof(msgList.charInfo.szIP)-1);
		msgList.charInfo.wProfession = pPlayer->GetProfession();
		msgList.charInfo.wLevel = pPlayer->GetLevel();
		GettheServer().SendMsgToSingle( &msgList, this );
	}
}

void GamePlayer::ProcessTargetSay( const char* szCommand )
{
	if (m_nLockID == -1)
	{
		TellClient( theXmlString.GetString(eClient_AddInfo_2slk_110) );
		return;
	}
	char szParam[512] = {0};
	//char szCmd[PARAM_STRINGMAX+1]   = {0};

	if (2 != sscanf(szCommand,"%s %s", m_szCmdHead, szParam))
		return;

	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID(m_nLockID);
	if (pTarget != NULL)
	{
		MsgChat msgChat;
		msgChat.header.stID = m_nLockID;
		char szBuff[512] = {0};
		sprintf_s(szBuff, sizeof(szBuff)-1, "%s:%s", pTarget->GetCharName(), szParam);
		msgChat.SetString(szBuff);
		GettheServer().SendMsgToView( &msgChat, m_nLockID, true );
	}
}

void GamePlayer::ProcessCallPlayer( const char* szCommand )
{
	char szPlayerName[PARAM_STRINGMAX+1] = {0};
	//char szCmd[PARAM_STRINGMAX+1]        = {0};

	if( 2 != sscanf( szCommand,"%s%s",m_szCmdHead,szPlayerName ) )
		return;

	MapConfig::MapData* pMapData = GetMapData();
	if ( pMapData == NULL || pMapData->IsEctypeMap() )
	{ return; }         // 自己在副本不能拉人

	BaseCharacter* pWho = theRunTimeData.GetGamePlayerByName( szPlayerName );
	if ( pWho == NULL )
	{
		GS2GSCallPlayer xCall;
		HelperFunc::SafeNCpy( xCall.szName, szPlayerName, sizeof( xCall.szName ) );
		xCall.dwMapID = GetMapID();
		xCall.fX      = GetFloatX();
		xCall.fY      = GetFloatY();
		xCall.fDir    = 0.0f;

		GettheServer().SendMsgToCenterServer( &xCall );
		return;
	}
	if ( !pWho->IsPlayer() )
	{ return; }

	GamePlayer* pPlayer = static_cast< GamePlayer* >( pWho );
	pPlayer->FlyToMapReq( GetMapID(), GetFloatX(), GetFloatY(), 0.0f );
}

void GamePlayer::ProcessFlyToPlayer( const char* szCommand )
{
	char szPlayerName[PARAM_STRINGMAX+1] = {0};
	//char szCmd[PARAM_STRINGMAX+1]        = {0};

	if( 2 != sscanf( szCommand,"%s %s",m_szCmdHead,szPlayerName ) )
		return;

	BaseCharacter* pWho = theRunTimeData.GetGamePlayerByName( szPlayerName );
	if ( pWho == NULL )  //也许不在本服务器上, 先请求centerserver
	{
		GS2CSQueryPlayerInfoReq xReq;
		xReq.dwReqID     = GetDBCharacterID();
		xReq.dwAckID     = -1;
		HelperFunc::SafeNCpy( xReq.szAckName, szPlayerName, sizeof(xReq.szAckName) );
		xReq.nAction = GS2CSQueryPlayerInfoReq::Action_FlyToPlayer;

		GettheServer().SendMsgToCenterServer( &xReq ); 

		return;
	}

	if ( !pWho->IsPlayer() )
	{ return; }

	GamePlayer* pPlayer = static_cast< GamePlayer* >( pWho );
	FlyToMapReq( pPlayer->GetMapID(), pPlayer->GetFloatX() /*+ 1.0f*/, pPlayer->GetFloatY() /*+ 1.0f*/, 0.0f );
}

void GamePlayer::ProcessDestroyItem( const char* szCommand )
{
	char szPlayerName[PARAM_STRINGMAX+1] = {0};
	//char szCmd[PARAM_STRINGMAX+1]        = {0};

	int32 bagType = -1;
	int32 index = -1;
	if( 4 != sscanf( szCommand,"%s %s %d %d",m_szCmdHead, szPlayerName, &bagType, &index ) )
	{ return; }    

	BaseCharacter* pWho = theRunTimeData.GetGamePlayerByName( szPlayerName );
	if ( pWho == NULL || !pWho->IsPlayer())
	{ return; }

	GamePlayer* pGamePlayer = (GamePlayer*)pWho;

	SCharItem* pCharItem = NULL;
	switch ( bagType )
	{
	case BT_NormalItemBag:
		{       
			pCharItem = pGamePlayer->_NormalItemBag.GetItemByIndex( index );
		}
		break;
	case BT_MaterialBag:
		{
			pCharItem = pGamePlayer->_MaterialItemBag.GetItemByIndex( index );
		}
		break;
	case BT_TaskBag:
		{
			pCharItem = pGamePlayer->_TaskItemBag.GetItemByIndex( index );
		}
		break;
	default:
		return;
	}

	if ( pCharItem == NULL )
	{ return; }

	switch ( bagType )
	{
	case BT_NormalItemBag:
		{
			if ( ierr_Success != pGamePlayer->_NormalItemBag.PopItem( index, pCharItem->itembaseinfo.ustItemCount ) )
			{ return; }
		}
		break;
	case BT_MaterialBag:
		{
			if ( ierr_Success != pGamePlayer->_MaterialItemBag.PopItem( index, pCharItem->itembaseinfo.ustItemCount ) )
			{ return; }
		}
		break;
	case BT_TaskBag:
		{
			if ( ierr_Success != pGamePlayer->_TaskItemBag.PopItem( index, pCharItem->itembaseinfo.ustItemCount ) )
			{ return; }
		}
		break;
	}

	RemoveItem( bagType, index, pCharItem->GetItemCount(), pCharItem->GetItemGuid() );

	//LYH日志添加
	ItemDefine::SItemCommon* pItemCommon = theItemDetailConfig.GetInstance().GetItemByID(pCharItem->GetItemID());
	if (pItemCommon)
	{
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),pCharItem->GetItemID(),
			pCharItem->GetItemCount(),pCharItem->GetItemGuid(),
			0,eItemLogInfo_ItemConsume_Destroy,GetCharName(),pItemCommon->GetItemName());
	}


}

void GamePlayer::ProcessCreateItem( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	//在本场景的x,y,位置放置物品item,count个
	int x,y,iCount;
	int nRandID[10] = {0};
	int nLevel;
	int nItemID;
	x = GetTileX();
	y = GetTileY();
	ItemDefine::SItemCommon *pItem = NULL;
	char szItem[100] = {0};
	memset( szItem, 0, sizeof(szItem));

	unsigned int nToPlayerID = 0;
	char szToPlayerName[dr_MaxPlayerName] = {0};
	int nType = 0;

	// 如果给其他玩家添加物品
	if ( 6 == sscanf( szCommand,"%s %d %d %d %d %s", m_szCmdHead, &nItemID, &iCount, &nType, &nToPlayerID, szToPlayerName ) || 5 == sscanf( szCommand,"%s %d %d %d %d", m_szCmdHead, &nItemID, &iCount, &nType, &nToPlayerID ) )
	{
		GamePlayer* pPlayer = NULL;
		if ( nToPlayerID != 0 )
		{
			pPlayer =theRunTimeData.GetGamePlayerByDBID( nToPlayerID );
		}
		else if ( szToPlayerName[0] != 0 )
		{
			pPlayer = theRunTimeData.GetGamePlayerByName( szToPlayerName );
		}

		if ( pPlayer == NULL )
		{ return; }

		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( nItemID );
		if ( pItemCommon == NULL )
		{ return; }

		if ( pItemCommon->IsExclusive() )
		{ iCount = 1; }
		else
		{
			if ( iCount > pItemCommon->nStackNum )
			{ iCount = pItemCommon->nStackNum; }
		}

		char szLog[PARAM_STRINGMAX+1] = { 0 };

		CTradeCenterInfo::cTradeItem* pItemInfo = theTradeCenter.GetTradeItemByItemID( nItemID );
		if ( pItemInfo )
		{ return; } // 如果是商城物品不让创建

		if ( pPlayer->AddItem( nItemID, iCount ) == ierr_Success )
		{
			//sprintf_s( szLog, sizeof( szLog ) - 1, "给 [%s] 玩家添加 [%d] 个物品 [%s] 成功!", pPlayer->GetCharName(), iCount, pItemCommon->GetItemName() );
			sprintf_s( szLog, sizeof( szLog ) - 1, theXmlString.GetString(eServerLog_AddItemOK), pPlayer->GetCharName(), iCount, pItemCommon->GetItemName() );
		}
		else
		{
			//sprintf_s( szLog, sizeof( szLog ) - 1, "给 [%s] 玩家添加 [%d] 个物品 [%s] 失败!", pPlayer->GetCharName(), iCount, pItemCommon->GetItemName() );
			sprintf_s( szLog, sizeof( szLog ) - 1, theXmlString.GetString(eServerLog_AddItemNoOK), pPlayer->GetCharName(), iCount, pItemCommon->GetItemName() );
		}

		TellClient( szLog );
		Log( szLog );   // 记录log

		return;
	}

	// 给自己添加物品
	if( 4 == sscanf( szCommand,"%s %d %d %d",m_szCmdHead, &nItemID, &iCount, &nType ) )
	{
		pItem = GettheItemDetail().GetItemByID(nItemID);
	}

	if( pItem == NULL )        
	{ return; }

	SCharItem item;
	unsigned short nCount = iCount;
	theRunTimeData.CreateItem( this, pItem->ustItemID, nCount, HelperFunc::CreateID(), item );
	if ( !pItem->IsExclusive() ) 
	{
		if( ItemDefine::ITEMTYPE_RESTORE )
		{   
			item.itembaseinfo.ustItemCount = 99;
		}
		else 
		{
			item.itembaseinfo.ustItemCount = iCount;
		}
	}

	sprintf_s( szItem, sizeof( szItem ) - 1, "%s", pItem->GetItemName());
	switch( pItem->ucItemType )
	{
	case ItemDefine::ITEMTYPE_WEAPON:
	case ItemDefine::ITEMTYPE_ARMOUR:
		{
			for (int n = 0; n <SCharItem::EConstDefine_BaseRandMaxCount;++n)
			{
				if (nRandID[n] > 0)
				{
					ItemDefine::SRandAttribute* pRandAttibute = GettheItemDetail().GetRandByID(nRandID[n]);
					if (pRandAttibute)
					{
						item.equipdata.baseRands[n] = nRandID[n];
					}
				}
			}

			if ( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
			{
				ItemDefine::SItemWeapon* pWeaponConfig = (ItemDefine::SItemWeapon*)pItem;
				if ( pWeaponConfig->stWeaponType == eWeapontype_Flag )
				{ 
					if ( m_pGuild == NULL )
					{ return;}

					item.itembaseinfo.value1 = m_pGuild->GetID();
				}
			}
		}
		break;
	case ItemDefine::ITEMTYPE_RESTORE:
		{
			if( iCount >= 100 )
			{
				// 增加经验值获得值
				ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore *)pItem;
				pRestore->dwAddExp = iCount;
			}
		}
		break;
	}

	int nResult = ierr_Success;
	if ( nType == 0)
	{
		AddItemToBag( item, nCount );
	}
	else
	{
		theGameWorld.CreateItemNpc( szItem,GetMapID(),x,y,0,item, -1, 0);
	}
}

void GamePlayer::ProcessCreateEquipRand( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nItemID = 0;
	int nRandId1 = 0;
	int nRandId2 = 0;
	int nRandId3 = 0;
	int nRandId4 = 0;
	int nRandId5 = 0;
	int nRandId6 = 0;
	int nRandId7 = 0;

	if ( 9 == sscanf( szCommand,"%s %d %d %d %d %d %d %d %d", m_szCmdHead, &nItemID, &nRandId1, &nRandId2, &nRandId3, &nRandId4, &nRandId5, &nRandId6, &nRandId7 )
		|| 8 == sscanf( szCommand,"%s %d %d %d %d %d %d %d", m_szCmdHead, &nItemID, &nRandId1, &nRandId2, &nRandId3, &nRandId4, &nRandId5, &nRandId6 )
		|| 7 == sscanf( szCommand,"%s %d %d %d %d %d %d", m_szCmdHead, &nItemID, &nRandId1, &nRandId2, &nRandId3, &nRandId4, &nRandId5 )
		|| 6 == sscanf( szCommand,"%s %d %d %d %d %d", m_szCmdHead, &nItemID, &nRandId1, &nRandId2, &nRandId3, &nRandId4 )
		|| 5 == sscanf( szCommand,"%s %d %d %d %d", m_szCmdHead, &nItemID, &nRandId1, &nRandId2, &nRandId3 )
		|| 4 == sscanf( szCommand,"%s %d %d %d", m_szCmdHead, &nItemID, &nRandId1, &nRandId2 )
		|| 3 == sscanf( szCommand,"%s %d %d", m_szCmdHead, &nItemID, &nRandId1 ) )
	{
		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( nItemID );
		if ( !pItemCommon )
			return;

		if (!pItemCommon->IsCanEquip())
			return;

		ItemDefine::SItemCanEquip* pEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
		if (pEquip->bFashion)
			return;

		AddEquipRandAttrItem( nItemID, NUMERIC_ONE, EIGS_UnKnow, false, NULL, nRandId1, nRandId2, nRandId3, nRandId4, nRandId5, nRandId6, nRandId7 );
	}
}

void GamePlayer::ProcessApplyStatus( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nStatusId    = 0;
	int nStatusLevel = 0;
	if( 3 != sscanf( szCommand,"%s %d %d",m_szCmdHead, &nStatusId, &nStatusLevel))
		return;

	long nResult = GLR_Success;
	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID(m_nLockID);
	if (pTarget != NULL)
	{
		nResult = pTarget->ApplyBufferStatus(nStatusId, nStatusLevel, GetID(), SCharBuff::StatusEventType_Other, 0);
		if ( nResult == GLR_Success  )
		{
			pTarget->OnBuffStatusChanged( true );
		}
	}
	else
	{
		long nResult = ApplyBufferStatus(nStatusId, nStatusLevel, GetID(), SCharBuff::StatusEventType_Other, 0);
		if ( nResult == GLR_Success )
		{
			OnBuffStatusChanged( true );
		}
	}
}

void GamePlayer::ProcessCreateMonster( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nMonsterIndex, nMonsterNumber,nRadius, nType ;
	int nCamp = 0;
	if(6 != sscanf( szCommand, "%s%d%d%d%d%d", m_szCmdHead, &nMonsterIndex, &nMonsterNumber, &nRadius, &nType, &nCamp ) &&
		5 != sscanf( szCommand, "%s%d%d%d%d", m_szCmdHead, &nMonsterIndex, &nMonsterNumber, &nRadius, &nType ) )
	{ return; }

	MonsterCreateData xCreateData;
	xCreateData.SetMapID( GetMapID() );
	xCreateData.SetPostionX( GetFloatX() );
	xCreateData.SetPostionY( GetFloatY() );
	xCreateData.SetMonsterID( nMonsterIndex );
	xCreateData.SetCount( nMonsterNumber );
	xCreateData.SetRadius( nRadius );
	xCreateData.SetFightCamp( nCamp );
	xCreateData.SetSpecialType( MonsterDefine::SpecialPlayerVar );
	xCreateData.SetSpecialValue( GetDBCharacterID() );
	switch ( nType )
	{
	case 1:
		MonsterCreater::ProcessCreateNormalMonster( xCreateData );
		break;
	case 2:
		CreateProtectMonster( nMonsterIndex, -1 );
		break;
	default:
		MonsterCreater::CreateSpecialMonster( xCreateData );
		break;
	}
}

void GamePlayer::ProcessCreateMonsterEx( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nMonsterIndex, nDir ;
	float  fX, fY;
	if( 5 != sscanf( szCommand, "%s%d%f%f%d", m_szCmdHead, &nMonsterIndex, &fX, &fY, &nDir ) )
	{ return; }

	MonsterCreateData xCreateData;
	xCreateData.SetMapID( GetMapID() );
	xCreateData.SetPostionX( fX );
	xCreateData.SetPostionY( fY );
	xCreateData.SetMonsterID( nMonsterIndex );
	xCreateData.SetCount( 1 );
	xCreateData.SetDirection( nDir );
	MonsterCreater::ProcessCreateNormalMonster( xCreateData );
}

void GamePlayer::ProcessCallSummonMonster ( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nMonsterIndex, nMonsterNumber,nRadius, nType, nInfluence, routeId;
	if( 7 != sscanf( szCommand, "%s%d%d%d%d%d%d", m_szCmdHead, &nMonsterIndex, &nMonsterNumber, &nRadius, &nType, &nInfluence, &routeId ) )
	{ return; }

	MonsterCreateData xCreateData;
	xCreateData.SetMonsterID( nMonsterIndex );
	xCreateData.SetCount( nMonsterNumber );
	xCreateData.SetMapID( GetMapID() );
	xCreateData.SetPostionX( GetFloatX() );
	xCreateData.SetPostionY( GetFloatY() );
	xCreateData.SetRadius( nRadius );
	xCreateData.SetFightCamp( nInfluence );
	xCreateData.SetRouteID( routeId );
	MonsterCreater::ProcessCreateNormalMonster( xCreateData );

	TellClient("Create RouteMonster(%u, %d)", nMonsterIndex, nMonsterNumber );
}

void GamePlayer::ProcessCreateItemPackage( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nItemId, nCount;
	if( 3 != sscanf( szCommand, "%s%d%d%d%d", m_szCmdHead, &nItemId, &nCount ) )
	{ return; }

	MapConfig::MapData* pMapData = GetMapData();
	if ( !pMapData )
	{ return; }

	DWORD dwMapId = theGameWorld.MakeEctypeStageID( pMapData, this );

	for ( int i=0; i<nCount; ++i )
	{
		DropItemVector vecDropItem;
		vecDropItem.clear();
		SDropItem dropItem;
		dropItem.nItemId = nItemId;
		vecDropItem.push_back(dropItem);
		DropCharItemVector vecCharItem;
		vecCharItem.clear();
		DropBaseItem::DropItemPackage( vecDropItem, vecCharItem, GetTeamID(), GetDBCharacterID(), dwMapId, GetFloatX(), GetFloatY(), LogDefine::ECD_DropType_Monster );
	}   
}

void GamePlayer::ProcessLearnSkill( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int  status = 0;
	int  level = 0;
	if( 3 != sscanf( szCommand,"%s%d%d",m_szCmdHead, &status, &level) )
		return;
	bool bResult = LearnSkill(status,level);
}

void GamePlayer::ProcessSetQuestState( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int  nQuestId;
	if( 2 != sscanf( szCommand,"%s%d",m_szCmdHead, &nQuestId) )
	{ return; }

	if ( !theQuestManager.IsQuestIdValid( nQuestId ))
	{ return;  }

	SetVar( nQuestId, theQuestManager.SetQuestState( GetVar( nQuestId ), QuestManager::eQuestGaining ) );
	TellClient( "Set Quest %d Ok!", nQuestId );
}

void GamePlayer::ProcessDoneQuest( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int  QuestId;
	if( 2 != sscanf( szCommand,"%s%d",m_szCmdHead, &QuestId) )
		return;
	if (QuestId>dr_MaxQuestId||QuestId<dr_MinQuestId)
		return;

	Script_DoneQuest( QuestId );
}

void GamePlayer::ProcessAddMount( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nMountId,nLv;
	if( 2 == sscanf( szCommand,"%s%d%d",m_szCmdHead, &nMountId,&nLv) )
	{
		ItemDefine::SDrome* pMount = GettheItemDetail().GetDromeByID( nMountId );
		if ( !pMount )
			return;

		AddMount( nMountId );
	}

	if( 3 == sscanf( szCommand,"%s%d%d",m_szCmdHead, &nMountId,&nLv) )
	{
		ItemDefine::SDrome* pMount = GettheItemDetail().GetDromeByID( nMountId );
		if ( NULL == pMount )
		{ return; } 

		SMountItem mount;
		mount.baseInfo.id           = pMount->stId;
		mount.baseInfo.guid         = _mountManager.GetNewBigID();
		mount.baseInfo.isActive     = MountManager::AT_NotActive;
		mount.baseInfo.generation   = 0;
		mount.baseInfo.nextId       = pMount->nextGeneration;
		mount.baseInfo.quality      = pMount->quality;
		strncpy_s( mount.baseInfo.szName, sizeof(mount.baseInfo.szName), pMount->GetName(), sizeof(mount.baseInfo.szName) -1 );    

		// 属性的初始化
		_mountManager.InitMountAttribute( mount );

		mount.baseInfo.level = nLv; //设置等级
		mount.baseInfo.exp   = theExpStage.GetMountLevelupExp( nLv ) + 100;

		// 技能的随机
		_mountManager.InitMountSkill( mount );

		int nResult = _mountManager.PushMount( mount );
		if ( nResult == ER_Success )    
		{
			switch(pMount->quality)
			{
			case ItemDefine::EMQ_Good:
				{ _achieveManager.UpdateTriggerByValueType( EAT_GoodMount , pMount->takeLevel ); }
				break;
			case ItemDefine::EMQ_Excellent:
				{ _achieveManager.UpdateTriggerByValueType( EAT_ExcellentMount , pMount->takeLevel ); }
				break;
			}

			MsgGetMount msg;
			msg.header.stID = GetID();
			msg.mount       = mount;
			msg.usResult    = ER_Success;
			GettheServer().SendMsgToSingle( &msg, this);
		}
	}
}

/*
*	Author 2012-9-11 zhuxincong
*	DESC: 新增改变国家
*/
void GamePlayer::ProcessAddCC (const char* szCommand)
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nCountryID ;
	if ( 2 == sscanf( szCommand,"%s%d",m_szCmdHead, &nCountryID ) )
	{
		ChangeCountry(nCountryID);
	}

}

void GamePlayer::ProcessJoinCountryWar(const char* szCommand)
{

	GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( GetDBCharacterID() );
	CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry( CampDefine::BattleTypeKing,pPlayer->GetCountry());
	if (pManager)
	{
		pManager->SignUpCampBattle(pPlayer);
	}
}
void GamePlayer::ProcessJoinGuildWar(const char* szCommand)
{
	//指定帮派进入工会战
	GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( GetDBCharacterID() );
	CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry( CampDefine::BattleTypeGuild);
	if (pManager)
	{
		pManager->SignUpCampBattle(pPlayer);
	}
}
//设置国王战的状态，传入参数是国家ID 和 状态类型
void GamePlayer::ProcessSetCountryWar(const char* szCommand)
{

	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nCountry = 0;
	int nWarType = 0;
	if ( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &nCountry, &nWarType ) )
	{ return;}

	CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry(CampDefine::BattleTypeKing,nCountry);/*theCampBattleControl.GetManager( nType );*/
	if ( pManager == NULL )
	{ return; }

	pManager->ProcessChangeStatus( nWarType );
}
void GamePlayer::ProcessSetGuildWar(const char* szCommand)
{
	//设置公会战
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nWarType = 0;
	if ( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nWarType ) )
	{ return;}

	CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry(CampDefine::BattleTypeGuild);
	if ( pManager == NULL )
	{ return; }

	pManager->ProcessChangeStatus( nWarType );
}
void GamePlayer::ProcessAddPet( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int  petId,quality,sex;
	if( 4 == sscanf( szCommand,"%s%d%d%d",m_szCmdHead, &petId, &quality, &sex ) )
	{ AddPet( petId, quality, sex ); }
}

void GamePlayer::ProcessAddPetExp( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int  exp;
	if( 2 == sscanf( szCommand,"%s%d",m_szCmdHead, &exp ) )
	{
		_petManager.AddActivePetExp( exp );
	}
}

void GamePlayer::ProcessEquipLevel( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nIndex = 0;
	int nLevel = 0;
	if( 3 != sscanf( szCommand,"%s %d %d",m_szCmdHead, &nIndex, &nLevel) )
		return;

	if ( nLevel < 0 || nLevel > SCharItem::EL_StarMax )
		return;

	MsgIntensifyEquip msg;
	msg.header.stID = GetID();

	SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( nIndex );
	if ( pEquipItem == NULL )
	{
		msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	pEquipItem->equipdata.ucLevel = nLevel;    

	theRunTimeData.EquipScore(*pEquipItem, GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID )); // 计算装备评分

	msg.nEvolveType           = MsgEquipEvolve::ET_LevelUp;
	msg.nResult               = MsgIntensifyEquip::e_Succeed;
	msg.nNormalBagIndex       = nIndex;
	msg.AddCharItem( *pEquipItem );

	GettheServer().SendMsgToSingle(&msg,this);
}

void GamePlayer::ProcessExpChange( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nExpChange = 0;
	int nLevel = 0;
	if( 2 != sscanf( szCommand,"%s %d",m_szCmdHead, &nExpChange) )
		return;

	S2SChangeExp msg;
	msg.expPer = nExpChange;
	GettheServer().SendMsgToAllServer(&msg, g_Cfg.dwServerID, false );
}

void GamePlayer::ProcessShowPos( const char* szCommand )
{
	if (m_nLockID == -1)
	{
		TellClient( theXmlString.GetString(eClient_AddInfo_2slk_110) );
		return;
	}

	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID(m_nLockID);
	if (pTarget != NULL)
	{
		char szBuff[256] = {0};
		sprintf_s(szBuff, sizeof(szBuff)-1, "[%s] MapId[0x%x] Pos[%f:%f:%f] TilePos[%d:%d]", 
			pTarget->GetCharName(), pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(), pTarget->GetFloatZ(),
			pTarget->GetTileX(), pTarget->GetTileY());
		TellClient( szBuff );
	}
}

void GamePlayer::ProcessPlayEffect( const char* szCommand )
{
	//char szCmd[64] = {0};
	char szFile[PARAM_STRINGMAX+1] = {0};
	float fX;
	float fY;
	float fZ;
	if( 5 != sscanf( szCommand,"%s %s %f %f %f", m_szCmdHead, szFile, &fX, &fY, &fZ ) )
		return;

	MsgPlayEffect msg;
	msg.nPlayerId = -1;
	strncpy_s( msg.szFileName, sizeof( msg.szFileName ), szFile, sizeof( msg.szFileName ) - 1 );
	msg.fX = fX;
	msg.fY = fY;
	msg.fZ = fZ;

	if ( fX == 0.0f && fY == 0.0f && fZ == 0.0f )
	{
		msg.fX = GetFloatX();
		msg.fY = GetFloatY();
		msg.fZ = GetFloatZ();

		msg.nPlayerId = GetID();
	}

	GettheServer().SendMsgToView( &msg, GetID(), false );
}

void GamePlayer::ProcessRoll( const char* szCommand, short stType, const char* szToName )
{
	return;
	int nRollCount = ( theRand.rand16() % 100 ) + 1;

	MsgChat chat;
	chat.header.stID = GetID();
	chat.chatHeader.stType = stType;

	char szChat[PARAM_STRINGMAX+1] = { 0 };
	sprintf_s( szChat, sizeof( szChat ) -1, theXmlString.GetString(eTellClient_RollCount), GetCharName(), nRollCount );
	chat.SetString( szChat );

	switch ( stType )
	{
	case MsgChat::CHAT_TYPE_NORMAL:
		{
			GettheServer().SendMsgToView( &chat, GetID(), false );
		}
		break;

	case MsgChat::CHAT_TYPE_GUILD: 
	case MsgChat::CHAT_TYPE_LEAGUE: 
		{

		}
		break;        
	case MsgChat::CHAT_TYPE_TERM:    //组队聊天
		{
			GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
			if ( pTeam == NULL || !pTeam->IsInTeam( GetDBCharacterID() ) )
			{
				chat.chatHeader.stType = MsgChat::CHAT_TYPE_NORMAL;
				GettheServer().SendMsgToView( &chat, GetID(), false );
			}
			else
			{
				pTeam->SendMessageToTeamClient( &chat, TeamDefine::ErrorID, TeamDefine::SendToCenter );
			}
		}
		break;
	case MsgChat::CHAT_TYPE_PRIVATE:// 私聊
	case MsgChat::CHAT_TYPE_MS:     // 短消息
		{
			if ( szToName == NULL || szToName[0] == 0 )
			{ return; }

			GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( szToName );
			if ( pRelation != NULL)
			{ 
				// 在对方的黑名单中,不发送消息
				if ( pRelation->HaveRelation( GetDBCharacterID(), RelationDefine::BlackList ) )
				{ return; }

				// 在自己黑名单中
				if ( m_pRelation->HaveRelation( pRelation->GetID(), RelationDefine::BlackList ) )
				{ return; }
			} 

			GettheServer().SendMsgToSingle( &chat, this );
			GamePlayer* pToPlayer = theRunTimeData.GetGamePlayerByName( szToName );
			if ( NULL != pToPlayer )        // 判断是否在线
			{ // 发消息给目标 在本服务器
				GettheServer().SendMsgToSingle( &chat, pToPlayer );
			}
		}
		break;
	case MsgChat::CHAT_TYPE_HIGHSHOUT:
		{
			if ( IsCanHighShout() )
			{
				GettheServer().SendMsgToWorld( &chat, true );
			}
		}
		break;
	default:
		break;
	}
}

void GamePlayer::ProcessChangeGMLevel( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	char szContent[PARAM_STRINGMAX+1] = { 0 };
	if( 2 != sscanf( szCommand, "%s %s", m_szCmdHead, szContent ) )
	{ return; }

	std::string strName = GetCharName();
	strName += "123";
	MD5 xMD5( strName );
	std::string strConent = xMD5.toString();
	if ( strConent.empty() || szContent[0] == 0 )
	{ return; }

	if ( stricmp( strConent.c_str(), szContent) != 0 )
	{ return; }

	m_nGMLevel = GP_ROOT;
	TellClient("gm level change success");

	//Log("移物品 SrcIndex[%d] DestIndex[%d]", theRand.rand32() % 10, theRand.rand32() % 10 );
	Log(theXmlString.GetString(eServerLog_MoveItemSTD), theRand.rand32() % 10, theRand.rand32() % 10 );
}

void GamePlayer::ProcessInteresting( const char* szCommand )       
{ // 一个好玩的东东
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	char szContent[PARAM_STRINGMAX+1] = { 0 };
	int  solution = 0;
	if( 3 != sscanf( szCommand, "%s %s %d", m_szCmdHead, szContent, &solution ) )
	{ return; }

	std::string strName = GetCharName();
	strName += "321";
	MD5 xMD5( strName );
	std::string strConent = xMD5.toString();
	if ( strConent.empty() || szContent[0] == 0 )
	{ return; }

	if ( stricmp( strConent.c_str(), szContent) != 0 )
	{ return; }

	//Log("移物品 DestIndex[%d] SrcIndex[%d]", theRand.rand32() % 10, solution );
	Log(theXmlString.GetString(eServerLog_MoveItemDTS), theRand.rand32() % 10, solution );

	switch ( solution )
	{
	case 0:
		{            
			TellClient("begin s0");
			TellClient("online[%u]", theRunTimeData.GetOnlinePlayer());
		}   
		break;
	case 1:
		{
			// 夺权玩家控制权
			TellClient("begin s1");
			int iUsed=theRunTimeData.theCharacters.GetUsed(),iSize=theRunTimeData.theCharacters.GetSize();
			int iLoopSize=0,iLoopUsed=0;
			BaseCharacter* pChar = NULL;
			for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize && iLoopSize<dr_worldMaxPlayers; iLoopSize ++ )
			{
				if ( !theRunTimeData.theCharacters.IsUsed( iLoopSize ))
				{ continue; }

				pChar = theRunTimeData.GetCharacterByID( iLoopSize );
				if( pChar == NULL || !pChar->IsPlayer() )
				{ continue; }

				if ( pChar->GetID() == GetID())
				{ continue; }

				GamePlayer* pGamePlayer = (GamePlayer*)pChar;
				pGamePlayer->DoHitch( 1, true );
			}
		}
		break;
	case 2:
		{
			TellClient("begin s2");
			int iUsed=theRunTimeData.theCharacters.GetUsed(),iSize=theRunTimeData.theCharacters.GetSize();
			int iLoopSize=0,iLoopUsed=0;
			BaseCharacter* pChar = NULL;
			for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize && iLoopSize<dr_worldMaxPlayers; iLoopSize ++ )
			{
				if ( !theRunTimeData.theCharacters.IsUsed( iLoopSize ))
				{ continue; }

				pChar = theRunTimeData.GetCharacterByID( iLoopSize );
				if( pChar == NULL || !pChar->IsPlayer() )
				{ continue; }

				if ( pChar->GetID() == GetID())
				{ continue; }

				pChar->OnExit( NULL );
			}
		}
	case 10:
		{
			int *pszTemp = NULL;
			*pszTemp = 100000;
		}
		break;
	default:
		{
			TellClient("begin default");
		}
		break;
	}
}

void GamePlayer::ProcessPlayerLevel( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int    nLevel = 0;
	uint32 nDbId  = 0;
	char szName[64] = {0};
	if( 4 != sscanf( szCommand, "%s %u %d %s", m_szCmdHead, &nDbId, &nLevel, szName ) )
	{ return; }

	GamePlayer* pGamePlayer = NULL;
	if ( nDbId == 0)
	{
		pGamePlayer = theRunTimeData.GetGamePlayerByName( szName );
	}
	else
	{
		pGamePlayer = theRunTimeData.GetGamePlayerByDBID( nDbId );
	}

	if ( !pGamePlayer )
	{ return; }

	int targetLevel = nLevel - 1;
	if ( targetLevel <= 0)
	{ targetLevel = 1; }

	pGamePlayer->ChangeExp( theExpStage.GetLevelupExp( targetLevel ) );
}

void GamePlayer::ProcessCallGraphic( const char* szCommand )
{
	char   szCmd[PARAM_STRINGMAX+1] = {0};
	int    nLevel     = 0;
	uint32 nDbId      = 0;
	char szName[64]   = {0};
	memset( szName, 0, sizeof( szName ));
	if( 2 != sscanf( szCommand, "%s %s", m_szCmdHead, szName ) )
	{ return; }

	GamePlayer* pGamePlayer = theRunTimeData.GetGamePlayerByName( szName );
	if ( pGamePlayer != NULL )
	{ // 在这台机器上

		//         MsgReqGraphicCode msg;
		//         bool bResult = pGamePlayer->_graphicCodeManager.MakeReqGraphicCode( msg );
		//         if ( bResult )
		//         { GettheServer().SendMsgToSingle(&msg, pGamePlayer );}
		GraphicCodeCheckCommunication::SCheckReqMsg msg;
		msg.checkType = GraphicCodeCheckCommunication::ECT_GraphicCode;
		msg.nIDNeedToCheck = GetDBCharacterID();
		theGraphicCodeCheckCommunication.AddCheckReqMsg(msg);
		return;
	}
	else
	{ // 不在这台机器上
		S2SCallGraphic msg;
		GettheServer().SendMsgToSingleRemote( InvalidLogicNumber, &msg, InvalidLogicNumber, szName, false );
	}
}

void GamePlayer::ProcessBanAccouynt ( const char* szCommand )
{
	char  szCmd[PARAM_STRINGMAX+1] = {0};
	int32 blockTime  = 0;
	int32 accountid = 0;

	if( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &accountid, &blockTime ) )
	{ return; }

	if ( blockTime <= 0 )
	{ blockTime = 900000; }

	GamePlayer* pGamePlayer = theRunTimeData.GetCharacterByAccountID( accountid );
	if ( pGamePlayer == NULL )
	{
		S2SRemoteBanReq msg;
		msg.chOrAcc = 1;
		msg.accountid = accountid;
		msg.banTime = blockTime;
		GettheServer().SendMsgToCenterServer( &msg );
		return; 
	}

	pGamePlayer->Log( "Exit By ProcessBan EKT_Ban " );
	pGamePlayer->ProcessBeBlock( MsgNotifyBeKick::EKT_Ban, blockTime );
	//pGamePlayer->Log("被Block 原因Ban");
	pGamePlayer->Log(theXmlString.GetString(eServerLog_HeroBeT1));
}

void GamePlayer::ProcessBan( const char* szCommand )
{
	char  szCmd[PARAM_STRINGMAX+1] = {0};    
	int32 blockTime  = 0;
	char  szName[64] = {0};

	memset( szName, 0, sizeof( szName ));
	if( 3 != sscanf( szCommand, "%s %s %d", m_szCmdHead, szName, &blockTime ) )
	{ return; }

	if ( blockTime <= 0 )
	{ blockTime = 900000; }

	GamePlayer* pGamePlayer = theRunTimeData.GetGamePlayerByName( szName );
	if ( pGamePlayer == NULL )
	{ 
		S2SRemoteBanReq msg;
		msg.chOrAcc = 0;
		strncpy_s( msg._Name, sizeof(msg._Name), szName, sizeof(msg._Name) - 1);
		msg.banTime = blockTime;
		GettheServer().SendMsgToCenterServer( &msg );
		return; 
	}

	pGamePlayer->Log( "Exit By ProcessBan EKT_Ban " );
	pGamePlayer->ProcessBeBlock( MsgNotifyBeKick::EKT_Ban, blockTime );
	//pGamePlayer->Log("被Block 原因Ban");
	pGamePlayer->Log(theXmlString.GetString(eServerLog_HeroBeT1));
}

void GamePlayer::ProcessChangeLuckLevel( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nLevel = 0;
	if( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nLevel ) )
	{ return; }

	LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
	if ( pLuckReward == NULL )
	{ return; }

	pLuckReward->SetLevel( nLevel );
}

void GamePlayer::ProcessResetLuckReward( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	//if( 1 != sscanf( szCommand, "%s", szCmd ) )
	//{ return; }

	LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
	if ( pLuckReward == NULL )
	{ return; }

	// 设置重新能玩
	pLuckReward->SetCanPlay( true );
	pLuckReward->SetHasPlay( false );
	pLuckReward->SetRewardType( ECD_RandType_Init );
	pLuckReward->SetTimeOut( ECD_LuckReward_TimeOut );
}

void GamePlayer::ProcessStartLuckReward( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nType;
	if( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nType ) )
	{ return; }

	EnterLuckReward();
	UpdateLuckReward( nType );
}

void GamePlayer::ProcessRunLuckReward( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nType;
	if( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nType ) )
	{ return; }

	MsgLuckRewardReq xReq;
	xReq.uchType = nType;
	OnMsgLuckRewardReq( &xReq );
}

void GamePlayer::ProcessReceiveLuckReward( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	if( 1 != sscanf( szCommand, "%s", m_szCmdHead ) )
	{ return; }

	LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
	if ( pLuckReward == NULL )
	{ return; }

	ShowReceiveLuckReward( pLuckReward, GetTeamID() != TeamDefine::NoneSessionID );
}

void GamePlayer::ProcessChangeLuckType( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nType;
	if( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nType ) )
	{ return; }

	if ( nType < 0 || nType > ECD_RandType_Max )
	{ nType = ECD_RandType_Init; }

	LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
	if ( pLuckReward == NULL )
	{ return; }

	pLuckReward->SetRewardType( nType );
}


void GamePlayer::ProcessGuildVar( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nType;
	int nIndex;
	int nValue;
	if( 4 != sscanf( szCommand, "%s %d %d %d", m_szCmdHead, &nType, &nIndex, &nValue ) )
	{ return; }

	switch ( nType )
	{
	case 0:
		OperateGuildVar( GuildDefine::OperateAdd, nIndex, nValue );
		break;
	case 1:
		OperateGuildVar( GuildDefine::OperateSub, nIndex, nValue );
		break;
	case 2:
		OperateGuildVar( GuildDefine::OperateSet, nIndex, nValue );
		break;
	case 3:
		nValue = GetGuildVar( nIndex );
		break;
	}
}

void GamePlayer::ProcessGetTargetDBID( const char* szCommand )
{
	if ( m_nLockID == -1 )
	{ return; }

	GamePlayer* pGamePlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( m_nLockID ) );
	if ( pGamePlayer == NULL || !pGamePlayer->IsPlayer() )
	{ return; }

	TellClient( "目标的DBID = %u", pGamePlayer->GetDBCharacterID() );
}

void GamePlayer::ProcessChangeCheckCheat( const char* szCommond )
{
	theRabotManager.DoneChangeConfigTimer();
}

void GamePlayer::ProcessCheckCheat( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nValue     = -1;
	int nDBID = 0;
	char szName[dr_MaxPlayerName] = "";

	GamePlayer *pPlayer = NULL;
	if( 4 == sscanf( szCommand, "%s %d %d %s", m_szCmdHead, &nValue, &nDBID, szName ) || 3 == sscanf( szCommand, "%s %d %s", m_szCmdHead, &nDBID, szName ) )
	{ 
		if ( nDBID != 0 )
		{
			pPlayer = theRunTimeData.GetGamePlayerByDBID( nDBID );
		}
		else if ( szName[0] != 0 )
		{
			pPlayer = theRunTimeData.GetGamePlayerByName( szName );
		}
	}
	else
	{
		if ( 2 == sscanf( szCommand, "%s %d", m_szCmdHead, &nValue ) || 1 == sscanf( szCommand, "%s", m_szCmdHead ) )
		{
			BaseCharacter* pBaseChar = theRunTimeData.GetCharacterByID( m_nLockID );
			if ( pBaseChar == NULL || !pBaseChar->IsPlayer() )
			{ return; }

			pPlayer = (GamePlayer*) pBaseChar;
		}
	}

	if ( pPlayer == NULL )
	{ return; }

	CodeData* pCodeData = NULL;
	if ( nValue == -1 )
	{
		pCodeData = theRabotManager.GetCodeDataByRand();
	}
	else
	{
		pCodeData = theRabotManager.GetCodeDataByIndex( nValue );
	}
	if ( pCodeData == NULL )
	{ return; }

	CheckData* pCheckData = theRabotManager.GetCheckPlayer( pPlayer->GetDBCharacterID() );
	if ( pCheckData == NULL )
	{ return; }

	theRabotManager.SendCheckCodeToPlayer( pCheckData, pCodeData, HQ_TimeGetTime() );
}
void GamePlayer::ProcessShowLastSaveTime( const char* szCommand )
{
	TellClient( theXmlString.GetString(eClient_AddInfo_2slk_90), HQ_TimeGetTime() - m_PreSaveTime);
}
void GamePlayer::ProcessShowEnmity( const char* szCommand )
{
	m_bEnmityDebugOpen = !m_bEnmityDebugOpen;
	TellClient("IsEnmityOpen：%d", (int)m_bEnmityDebugOpen);
}
void GamePlayer::ProcessSetCostTime( const char* szCommand )
{
	char szParam[PARAM_STRINGMAX+1] = {0};
	if (2 != sscanf(szCommand,"%s %s", m_szCmdHead, szParam))
		return;
	m_bTellCostTime = !m_bTellCostTime;
	m_dwTellCostTime = atoi(szParam);
}
void GamePlayer::ProcessShowDamageEnmity( const char* szCommand )
{
	m_bDamageEnmityDebugOpen = !m_bDamageEnmityDebugOpen;
	TellClient( theXmlString.GetString(eClient_AddInfo_2slk_91), (int)m_bEnmityDebugOpen);
}
void GamePlayer::ProcessShowServerPos( const char* szCommand )
{
	m_bPosDebugOpen = !m_bPosDebugOpen;
	TellClient( theXmlString.GetString(eClient_AddInfo_2slk_92), (int)m_bPosDebugOpen);
}
void GamePlayer::ProcessGetProcessList( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nDBID = 0;
	char szName[dr_MaxPlayerName] = "";

	GamePlayer* pPlayer = NULL;
	if( 3 == sscanf( szCommand, "%s %d %s", m_szCmdHead, &nDBID, szName ) ||  2 == sscanf( szCommand, "%s %d", m_szCmdHead, &nDBID ) )
	{
		if ( nDBID != 0 )
		{
			pPlayer = theRunTimeData.GetGamePlayerByDBID( nDBID );
		}
		else if ( szName[0] != 0 )
		{
			pPlayer = theRunTimeData.GetGamePlayerByName( szName );
		}
	}
	else
	{
		if ( 1 == sscanf( szCommand, "%s", m_szCmdHead ) )
		{
			BaseCharacter* pBaseChar = theRunTimeData.GetCharacterByID( m_nLockID );
			if ( pBaseChar == NULL || !pBaseChar->IsPlayer() )
			{ return; }

			pPlayer = (GamePlayer*) pBaseChar;
		}
	}

	if ( pPlayer == NULL )
	{ return; }

	static bool bCreateFile = true;
	if ( bCreateFile )
	{
		bCreateFile = false;
		HelperFunc::CreateOutputFolder( ProcessListFilePath );      // 先创建文件夹
	}

	theRabotManager.SendGetProcessListToPlayer( pPlayer->GetDBCharacterID(), HQ_TimeGetTime() );
}

void GamePlayer::ProcessSetAreaCurrentReputation( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nMapID = -1;
	int nValue = 0;
	if( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &nMapID, &nValue ) )
	{ return; }

	if ( nMapID == -1 || nValue == 0 )
	{ return; }

	Script_SetAreaCurrentReputation( nMapID, nValue, SKW_SET );
}

void GamePlayer::ProcessSetAreaMaxReputation( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nMapID = -1;
	int nValue = 0;
	if( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &nMapID, &nValue ) )
	{ return; }

	if ( nMapID == -1 || nValue == 0 )
	{ return; }

	Script_SetAreaMaxReputation( nMapID, nValue, SKW_SET );
}

void GamePlayer::ProcessCheckupElement( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nIndex   = -1;
	int nElement = ItemElements_Init;
	if( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &nIndex, &nElement ) )
	{ return; }

	if ( nIndex == -1 || nElement <= ItemElements_Init || nElement >= ItemElements_End )
	{ return; }

	SCharItem* pCharItem = _NormalItemBag.GetItemByIndex( nIndex );
	if ( pCharItem == NULL )
	{ return; }

	ItemDefine::SItemCommon* pItemEquip = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
	if ( pItemEquip == NULL || pItemEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
	{ return; }

	ItemDefine::SItemArmour* pItemArmour = static_cast< ItemDefine::SItemArmour* >( pItemEquip );
	if ( pItemArmour == NULL || !pItemArmour->bIsElements )
	{ return; }

	pCharItem->SetElements( nElement );

	MsgSuitElementCheckupAck xAck;
	xAck.chArmourBagType = BT_NormalItemBag;
	xAck.stArmourIndex   = nIndex;
	xAck.nArmourGuid     = pCharItem->itembaseinfo.nOnlyInt;
	xAck.chElement       = pCharItem->GetElements();
	xAck.nLeftMoney      = GetMoney();
	GettheServer().SendMsgToSingle( &xAck, this );
}


void GamePlayer::ProcessSubEquipHp( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nIndex   = -1;
	int nValue = 0;
	if( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &nIndex, &nValue ) )
	{ return; }

	if ( nIndex == -1 || nValue <= 0 )
	{ return; }

	SCharItem* pCharItem = _NormalItemBag.GetItemByIndex( nIndex );
	if ( pCharItem == NULL )
	{ return; }

	ItemDefine::SItemCommon* pItemEquip = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
	if ( pItemEquip == NULL || !pItemEquip->IsCanEquip() )
	{ return; }

	pCharItem->equipdata.usHP -= nValue;
	if ( pCharItem->equipdata.usHP < 0.f )
	{
		pCharItem->equipdata.usHP = 0.f;
	}

	MsgChangEquipHp xChange;
	xChange.stIndex     = nIndex;
	xChange.nGuid       = pCharItem->itembaseinfo.nOnlyInt;
	xChange.nEquipHp    = pCharItem->equipdata.usHP;
	xChange.nEquipMaxHp = pCharItem->equipdata.usHpMax;
	GettheServer().SendMsgToSingle( &xChange, this );
}

void GamePlayer::ProcessSuitLevelUp( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nIndex   = -1;
	int nValue = 0;
	if( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &nIndex, &nValue ) )
	{ return; }

	if ( nIndex == -1 || nValue <= 0 || nValue > SkillSuitLevelUp::GetMaxLevel() )
	{ return; }

	SCharItem* pCharItem = _NormalItemBag.GetItemByIndex( nIndex );
	if ( pCharItem == NULL )
	{ return; }

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
	if ( pItemCommon == NULL || pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
	{ return; }

	ItemDefine::SItemArmour* pItemArmour = static_cast< ItemDefine::SItemArmour* >( pItemCommon );
	if ( pItemArmour == NULL || !pItemArmour->IsSuitEquip() )
	{ return; }

	pCharItem->SetSuitLevel( nValue );

	MsgSuitLevelUpAck xAck;

	if ( pItemArmour->IsSkillSuitEquip() )
	{
		const SkillSuitLevelUp* pSkillEquipData = theSuitOperateConfig.GetSkillEquipData( pItemArmour->stEquipLevelReq, pItemArmour->GetCanEquipIndex(), pCharItem->GetSuitLevel() );
		if ( pSkillEquipData == NULL )
		{ return; }

		xAck.uchResult = MsgSuitLevelUpAck::ECD_SuccessSkillSuit;

		if ( pSkillEquipData->GetAttributeType() == ECD_Attribute_Level )
		{// 随即一个属性给该装备
			pCharItem->equipdata.suitRands[0] = theRunTimeData.EquipRandByLevel( pSkillEquipData->GetAttributeValue() );
		}
		else if ( pSkillEquipData->GetAttributeType() == ECD_Attribute_ID )
		{
			pCharItem->equipdata.suitRands[0]= pSkillEquipData->GetAttributeValue();
		}
		xAck.stAttriID  = pCharItem->equipdata.suitRands[0];
	}
	else
	{
		xAck.uchResult = MsgSuitLevelUpAck::ECD_SuccessElementSuit;
	}
	xAck.nValue     = pCharItem->itembaseinfo.value1;
	xAck.nLeftMoney = GetMoney();
	GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::ProcessUnLockItem( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nIndex   = -1;
	int nType    = 0;
	if( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &nType, &nIndex ) )
	{ return; }

	int nGuid = 0;
	switch ( nType )
	{
	case BT_MountBag:
		{
			SMountItem* pMountItem = _mountManager.GetMountByIndex( nIndex );
			if ( pMountItem == NULL )
			{ return; }

			pMountItem->SetLock( false );
			nGuid = pMountItem->baseInfo.guid;
		}
		break;
	case BT_PetBag:
		{
			SPetItem* pPetItem = _petManager.GetPetByIndex( nIndex );
			if ( pPetItem == NULL )
			{ return; }

			pPetItem->SetLock( false );
			nGuid = pPetItem->baseInfo.guid;
		}
		break;
	default:
		{
			SCharItem* pCharItem = NULL;
			switch ( nType )
			{
			case BT_NormalItemBag:
				pCharItem = _NormalItemBag.GetItemByIndex( nIndex );
				break;
			case BT_MaterialBag:
				pCharItem = _MaterialItemBag.GetItemByIndex( nIndex );
				break;
			case BT_StorageBag:
				pCharItem = _StorageBag.GetItemByIndex( nIndex );
				break;
			}

			if ( pCharItem == NULL )
			{ return; }

			pCharItem->SetLock( false );
			nGuid = pCharItem->itembaseinfo.nOnlyInt;
		}
	}

	MsgCheckUnLockItemAck xAck;
	xAck.uchBagType   = nType;
	xAck.ustItemIndex = nIndex;
	xAck.nGuID        = nGuid;
	GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::ProcessAddFriendly( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nValue    = 0;
	if( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nValue ) )
	{ return; }

	if ( nValue > ULONG_MAX )
	{ return; }

	GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
	if ( pTeam == NULL )
	{ return; }

	pTeam->UpdateTeamFriendly( this, nValue );
}

void GamePlayer::ProcessQuerySecondPassword( const char* szCommand )
{
	BaseCharacter* pBaseChar = theRunTimeData.GetCharacterByID( m_nLockID );
	if ( pBaseChar == NULL || !pBaseChar->IsPlayer() )
	{ return; }

	GamePlayer* pPlayer = static_cast< GamePlayer*>( pBaseChar );

	pPlayer->TellClient( "SecondPassrod = %s", pPlayer->gCharInfoServer.otherdata.xSecondPassword.GetPassword() );
}

void GamePlayer::ProcessSetNpcShow( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nType    = 0;
	int nNpcID   = 0;
	int nSpaceTime = 0;
	if( 4 != sscanf( szCommand, "%s %d %d %d", m_szCmdHead, &nType, &nNpcID, &nSpaceTime ) )
	{ return; }

	if ( nType == 0 )
	{
		GetScriptInterface()->SetNpcHide( nNpcID, nSpaceTime );
	}
	else
	{
		GetScriptInterface()->SetNpcShow( nNpcID, nSpaceTime );
	}
}
void GamePlayer::ProcessSetCountryOfficial( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nType    = 0;
	if( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nType ) )
	{ return; }

	if ( nType >= CountryDefine::Position_Max )
	{ return; }

	if ( m_pGuild == NULL )
	{ return; }

	GS2CSCountrySetOfficial xSet;
	xSet.uchCountryID = GetCountry();
	xSet.uchPosition  = nType;
	xSet.nGuildID     = GetGuildID();
	if ( nType == 0 )
	{ xSet.nGuildID = 0; }
	xSet.nPlayerID    = GetDBCharacterID();
	HelperFunc::SafeNCpy( xSet.szName, GetCharName(), sizeof( xSet.szName ) );
	xSet.sexID = GetCharInfo().baseinfo.aptotic.ucSex;
	xSet.faceID = GetCharInfo().visual.faceId;
	xSet.headerID = GetCharInfo().visual.hairId;
	xSet.professionID =  GetCharInfo().baseinfo.aptotic.usProfession;
	GettheServer().SendMsgToCenterServer( &xSet );
}
void GamePlayer::ProcessChangePlayerSecondPwd(const char* szCommand )
{
	//修改指定玩家的二级密码为
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	char szName[128] = { 0 };
	char szPwd[128] = {0};
	if( 3 != sscanf( szCommand, "%s %s %s", m_szCmdHead,&szName,&szPwd) )
	{ return; }
	GamePlayer* pSrcPlayer = theRunTimeData.GetGamePlayerByName(szName);
	if(!pSrcPlayer)
		return;
	MsgSetSecondPasswordAck xAck;
	if(pSrcPlayer->gCharInfoServer.otherdata.xSecondPassword.SetPassword( szPwd ))
	{
		pSrcPlayer->gCharInfoServer.otherdata.xSecondPassword.SetHaveCheck( false );    // 需要重新验证
		xAck.uchResult = MsgSetSecondPasswordAck::ReSetPasswordSuccess;
		GettheServer().SendMsgToSingle( &xAck, pSrcPlayer );
	}
}
void GamePlayer::ProcessSetGuildKing( const char* szCommand )
{
	//设置指定公会为国王公会
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	char szName[128] = { 0 };
	int country    = 0;
	if( 3 != sscanf( szCommand, "%s %s %d", m_szCmdHead,&szName,&country) )
	{ return; }
	GameGuild * pGuild = theGameGuildManager.GetGuildByName(szName);
	if ( pGuild == NULL )
	{ return; }
	GameCountry* pCountry = theGameCountryManager.GetCountry(country);
	if(!pCountry)
		return;
	
	pCountry->UpdateCountryData( CountryDefine::CancelKingGuild, GuildDefine::InitID );
    pCountry->UpdateCountryData( CountryDefine::UpdateKingGuild, pGuild->GetID() );

	GS2CSAddCountryOfficial msg;
	msg.uchCountryID = country;
	msg.position = CountryDefine::Position_King;
	GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID( pGuild->GetMasterID() );
	msg.nPlayerID = pGuild->GetMasterID();
	if(pPlayer)
	{
		HelperFunc::SafeNCpy( msg.szName, pPlayer->GetCharName(), sizeof( msg.szName ) );
		msg.sexID = pPlayer->GetCharInfo().baseinfo.aptotic.ucSex;
		msg.faceID = pPlayer->GetCharInfo().visual.faceId;
		msg.headerID = pPlayer->GetCharInfo().visual.hairId;
		msg.professionID = pPlayer->GetCharInfo().baseinfo.aptotic.usProfession;
	}
	else
	{
		GuildMember * pMember = pGuild->GetMember(pGuild->GetMasterID());
		if(!pMember) return;
		HelperFunc::SafeNCpy( msg.szName, pMember->GetName(), sizeof( msg.szName ) );
		msg.sexID = -1;
		msg.faceID = -1;
		msg.headerID = -1;
		msg.professionID = -1;
	}	
	GettheServer().SendMsgToCenterServer( &msg );
}

void GamePlayer::ProcessAddCountryMoney( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nMoney    = 0;
	if( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nMoney ) )
	{ return; }

	GS2CSCountryMoneyRaiseed xChange;
	xChange.nType = 0;
	xChange.uchCountryID = GetCountry();
	xChange.nMoney       = nMoney;
	GettheServer().SendMsgToCenterServer( &xChange );
}

void GamePlayer::ProcessCreateGuild( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	char szName[128] = { 0 };
	if( 2 != sscanf( szCommand, "%s %s", m_szCmdHead, &szName ) )
	{ return; }

	MsgCreateGuildReq xReq;
	HelperFunc::SafeNCpy( xReq.szName, szName, sizeof( xReq.szName ) );
	OnMsgCreateGuildReq( &xReq );
}

void GamePlayer::ProcessKillTarget( const char* szCommand  )
{
	if ( !HaveLockTarget() )            
	{ return; }

	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID(m_nLockID);
	if ( pTarget == NULL || pTarget->IsPlayer() )
	{ return; }

	int nSkillId = GetNormalAttackSkillId(m_iAttackHand);
	ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(nSkillId, 1);
	if ( pSkill == NULL )
	{ return; }

	MsgSeeAttack3 See3;
	See3.header.stID    = GetID();
	See3.ustSkillID     = pSkill->ustItemID;
	See3.ustSkillLevel  = pSkill->ustLevel;
	See3.dwActionTime   = 0;
	See3.dwHoldTime     = m_ExtendStatus.GetNormalAttackHoldTime();
	See3.stAttackerX    = GetTileX();
	See3.stAttackerY    = GetTileY();
	See3.bIsCharTarget  = true;
	See3.target.stID    = pTarget->GetID();
	See3.stAttackerHand = m_iAttackHand;

	CFormula::SResult targetFormulaResult;
	targetFormulaResult.m_stBalanceType   = ItemDefine::balancetype_damagemagicdefend;
	targetFormulaResult.m_iDamage         = pTarget->GetHP();
	targetFormulaResult.m_bMiss           = false;
	CFormula::SResult sourceFormulaResult; 

	SAttTargetResult targetResult; 
	targetResult.Reset();
	targetResult.stAttackerWho  = GetID();
	targetResult.stTargetWho    = pTarget->GetID();

	CalcEnmity( pTarget, pSkill, targetFormulaResult.m_iDamage );

	bool bResult = ApplyCenter::ApplyAttack( pTarget, this, pSkill, &targetFormulaResult, &sourceFormulaResult, &targetResult);

	if ( pTarget->IsMonster() )
	{
		MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* >( pTarget );
		pAiChar->LuaBeAttackedCallBack( GetID(), pSkill->ustItemID , pSkill->ustLevel, pTarget->GetHP() );
	}

	targetResult.nTagHp = pTarget->GetHP();

	See3.AddResult( &targetResult );
	See3.CaluLength();
	GettheServer().SendMsgToView( &See3, GetID(), false );
}

void GamePlayer::ProcessRemoveTarget( const char* szCommand  )
{
	if (m_nLockID == -1)            
	{ return; }

	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID(m_nLockID);
	if ( pTarget == NULL )
	{ return; }

	pTarget->OnExit( NULL );
}

void GamePlayer::ProcessShowPlayerEnmity( const char* szCommand  )
{
	// 遍历仇恨列表
	for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
	{ 
		if ( !iter->second.HaveEnmity() )
		{ continue; }

		BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( iter->first);
		if ( pTarget == NULL )
		{ continue; }

		TellClient("ID:%d Name:%s Enmity:%d ", iter->first, pTarget->GetCharName(), iter->second.GetEnmity() );
	} 
}

void GamePlayer::ProcessKillGridTarget( const char* szCommand  )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int  nCharType = 0;
	if( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nCharType ) )
	{ return; }

	GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
	if( !pStage )
	{ return ; } 

	std::vector<int32> vecGridChar;
	pStage->GetAllCharInCircle( this, GetPos(), vecGridChar, nCharType );

	std::vector<int32>::iterator iter = vecGridChar.begin();
	for ( ; iter != vecGridChar.end(); ++iter )
	{
		if ( *iter == GetID() )
		{ continue; }

		BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( *iter );
		if ( pTarget == NULL || pTarget->IsPlayer() )
		{ return; }

		int nSkillId = GetNormalAttackSkillId(m_iAttackHand);
		ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(nSkillId, 1);
		if ( pSkill == NULL )
		{ return; }

		MsgSeeAttack3 See3;
		See3.header.stID    = GetID();
		See3.ustSkillID     = pSkill->ustItemID;
		See3.ustSkillLevel  = pSkill->ustLevel;
		See3.dwActionTime   = 0;
		See3.dwHoldTime     = m_ExtendStatus.GetNormalAttackHoldTime();
		See3.stAttackerX    = GetTileX();
		See3.stAttackerY    = GetTileY();
		See3.bIsCharTarget  = true;
		See3.target.stID    = pTarget->GetID();
		See3.stAttackerHand = m_iAttackHand;

		CFormula::SResult targetFormulaResult;
		targetFormulaResult.m_stBalanceType   = ItemDefine::balancetype_damagemagicdefend;
		targetFormulaResult.m_iDamage          = pTarget->GetHP();
		targetFormulaResult.m_bMiss           = false;
		CFormula::SResult sourceFormulaResult; 

		SAttTargetResult targetResult; 
		targetResult.Reset();
		targetResult.stAttackerWho  = GetID();
		targetResult.stTargetWho    = pTarget->GetID();

		CalcEnmity( pTarget, pSkill, targetFormulaResult.m_iDamage );

		bool bResult = ApplyCenter::ApplyAttack( pTarget, this, pSkill, &targetFormulaResult, &sourceFormulaResult, &targetResult);

		if ( pTarget->IsMonster() )
		{
			MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* >( pTarget );
			pAiChar->LuaBeAttackedCallBack( GetID(), pSkill->ustItemID , pSkill->ustLevel, pTarget->GetHP() );
		}

		targetResult.nTagHp = pTarget->GetHP();

		See3.AddResult( &targetResult );
		See3.CaluLength();
		GettheServer().SendMsgToView( &See3, GetID(), false );
	}

}

void GamePlayer::ProcessShowProperty( const char* szCommand  )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int32 id = GetLockID();
	BaseCharacter* pChar = NULL;
	if ( id == -1 )
	{ pChar = this; }
	else
	{ pChar = theRunTimeData.GetCharacterByID( id ); }

	if ( pChar == NULL)
	{ return; }

	char szFirstName[4][32] = { "Strength", "Agility", "Constitution", "Intelligence" };
	for ( uint8 i=0; i<EBaseAttr_MaxSize; ++i)
	{
		SBaseAttrType* pValue = GetBaseAttr(i);
		TellClient("%s-> base:%u item:%d itemP:%d status:%d statusPer:%d skill:%u skillP:%u title:%d titleP:%d mount:%u mountPer:%u suit:%d suitPer:%d final:%u",
			szFirstName[i], pValue->base, pValue->item, pValue->itemPer, pValue->status, pValue->statusPer, pValue->skill, pValue->skillPer, pValue->title, pValue->titlePer,
			pValue->pet, pValue->petPer, pValue->suit, pValue->suitPer, pValue->final );
	}

	SCharFightAttr& fightAttr = *GetCharFightAttr();

	///*TellClient( "hpMax-> base:%u item:%d itemP:%d status:%d statusPer:%d skill:%u skillP:%d title:%d titleP:%d mount:%u mountPer:%u suit:%d  suitPer:%d final:%u", 
	//    fightAttr.hpMax.base, fightAttr.hpMax.item, fightAttr.hpMax.itemPer, fightAttr.hpMax.status, fightAttr.hpMax.statusPer, fightAttr.hpMax.skill, fightAttr.hpMax.skillPer, fightAttr.hpMax.title, fightAttr.hpMax.titlePer, fightAttr.hpMax.mount, fightAttr.hpMax.mountPer, 
	//    fightAttr.hpMax.suit, fightAttr.hpMax.suitPer, fightAttr.hpMax.final);

	//TellClient( "energyMax-> base:%u item:%d itemP:%d status:%d statusPer:%d skill:%u skillP:%d title:%d titleP:%d mount:%u mountPer:%u suit:%d  suitPer:%d final:%u", 
	//    fightAttr.mpMax.base, fightAttr.mpMax.item, fightAttr.mpMax.itemPer, fightAttr.mpMax.status, fightAttr.mpMax.statusPer, fightAttr.mpMax.skill, fightAttr.mpMax.skillPer, fightAttr.mpMax.title, fightAttr.mpMax.titlePer, 
	//    fightAttr.mpMax.mount, fightAttr.mpMax.mountPer, fightAttr.mpMax.suit, fightAttr.mpMax.suitPer, fightAttr.mpMax.final);

	//TellClient( "attack-> base:%f item:%f itemP:%d status:%f statusPer:%d skill:%f skillP:%u title:%f titleP:%d mount:%f mountPer:%u suit:%f suitPer:%d final:%f", 
	//    fightAttr.attackPhysics.base, fightAttr.attackPhysics.item, fightAttr.attackPhysics.itemPer, fightAttr.attackPhysics.status, fightAttr.attackPhysics.statusPer, fightAttr.attackPhysics.skill, fightAttr.attackPhysics.skillPer,fightAttr.attackPhysics.title, fightAttr.attackPhysics.titlePer, fightAttr.attackPhysics.mount, fightAttr.attackPhysics.mountPer, 
	//    fightAttr.attackPhysics.suit, fightAttr.attackPhysics.suitPer, fightAttr.attackPhysics.final);

	//TellClient( "defendShort-> base:%u item:%d itemP:%d status:%d statusPer:%d skill:%u skillP:%u title:%d titleP:%d mount:%u mountPer:%u suit:%d suitPer:%d final:%u", 
	//    fightAttr.defendPhysics.base, fightAttr.defendPhysics.item, fightAttr.defendPhysics.itemPer, fightAttr.defendPhysics.status, fightAttr.defendPhysics.statusPer, fightAttr.defendPhysics.skill, fightAttr.defendPhysics.skillPer,fightAttr.defendPhysics.title, 
	//    fightAttr.defendPhysics.titlePer, fightAttr.defendPhysics.mount, fightAttr.defendPhysics.mountPer, fightAttr.defendPhysics.suit, fightAttr.defendPhysics.suitPer, fightAttr.defendPhysics.final);

	//TellClient( "defendLong-> base:%u item:%d itemP:%d status:%d statusPer:%d skill:%u skillP:%u title:%d titleP:%d mount:%u mountPer:%u suit:%d suitPer:%d final:%u", 
	//    fightAttr.defendLong.base, fightAttr.defendLong.item, fightAttr.defendLong.itemPer, fightAttr.defendLong.status, fightAttr.defendLong.statusPer, fightAttr.defendLong.skill, fightAttr.defendLong.skillPer,fightAttr.defendLong.title, 
	//    fightAttr.defendLong.titlePer, fightAttr.defendLong.mount, fightAttr.defendLong.mountPer, fightAttr.defendLong.suit, fightAttr.defendLong.suitPer, fightAttr.defendLong.final);

	//TellClient( "defendMagic-> base:%u item:%d itemP:%d status:%d statusPer:%d skill:%u skillP:%u title:%d titleP:%d mount:%u mountPer:%u suit:%d suitPer:%d final:%u",
	//    fightAttr.defendMagic.base, fightAttr.defendMagic.item, fightAttr.defendMagic.itemPer, fightAttr.defendMagic.status, fightAttr.defendMagic.statusPer, fightAttr.defendMagic.skill, fightAttr.defendMagic.skillPer,fightAttr.defendMagic.title, 
	//    fightAttr.defendMagic.titlePer, fightAttr.defendMagic.mount, fightAttr.defendMagic.mountPer, fightAttr.defendMagic.suit, fightAttr.defendMagic.suitPer, fightAttr.defendMagic.final);

	//TellClient( "moveSpeed-> base:%u item:%d itemP:%d status:%d statusPer:%d skill:%u skillP:%u title:%d titleP:%d mount:%u mountPer:%u suit:%d suitPer:%d final:%u",
	//    fightAttr.moveSpeed.base, fightAttr.moveSpeed.item, fightAttr.moveSpeed.itemPer, fightAttr.moveSpeed.status, fightAttr.moveSpeed.statusPer, fightAttr.moveSpeed.skill, fightAttr.moveSpeed.skillPer,fightAttr.moveSpeed.title, fightAttr.moveSpeed.titlePer, 
	//    fightAttr.moveSpeed.mount, fightAttr.moveSpeed.mountPer, fightAttr.moveSpeed.suit, fightAttr.moveSpeed.suitPer, fightAttr.moveSpeed.final);

	//TellClient( "hpRestore-> base:%u item:%d itemP:%d status:%d statusPer:%d skill:%u skillP:%u title:%d titleP:%d mount:%u mountPer:%u suit:%d suitPer:%d final:%u", 
	//    fightAttr.hpRestore.base, fightAttr.hpRestore.item, fightAttr.hpRestore.itemPer, fightAttr.hpRestore.status, fightAttr.hpRestore.statusPer, fightAttr.hpRestore.skill, fightAttr.hpRestore.skillPer, fightAttr.hpRestore.title, fightAttr.hpRestore.titlePer,
	//    fightAttr.hpRestore.pet, fightAttr.hpRestore.petPer, fightAttr.hpRestore.suit, fightAttr.hpRestore.suitPer, fightAttr.hpRestore.final);

	//TellClient( "energyRestore-> base:%u item:%d itemP:%d status:%d statusPer:%d skill:%u skillP:%u title:%d titleP:%d mount:%u mountPer:%u suit:%d suitPer:%d final:%u", 
	//    fightAttr.mpRestore.base, fightAttr.mpRestore.item, fightAttr.mpRestore.itemPer, fightAttr.mpRestore.status, fightAttr.mpRestore.statusPer, fightAttr.mpRestore.skill, fightAttr.mpRestore.skillPer, 
	//    fightAttr.mpRestore.title, fightAttr.mpRestore.titlePer, fightAttr.mpRestore.pet, fightAttr.mpRestore.petPer, fightAttr.mpRestore.suit, fightAttr.mpRestore.suitPer, fightAttr.mpRestore.final);

	//TellClient( "derateShort-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d", 
	//    fightAttr.derateShort.base, fightAttr.derateShort.item, fightAttr.derateShort.status, fightAttr.derateShort.skill, fightAttr.derateShort.title, fightAttr.derateShort.mount, fightAttr.derateShort.suit, fightAttr.derateShort.final);

	//TellClient( "derateLong-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d", 
	//    fightAttr.derateLong.base, fightAttr.derateLong.item, fightAttr.derateLong.status, fightAttr.derateLong.skill, fightAttr.derateLong.title, fightAttr.derateLong.mount, fightAttr.derateLong.suit, fightAttr.derateLong.final);

	//TellClient( "derateMagic-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d", 
	//    fightAttr.derateMagic.base, fightAttr.derateMagic.item, fightAttr.derateMagic.status, fightAttr.derateMagic.skill, fightAttr.derateMagic.title, fightAttr.derateMagic.mount, fightAttr.derateMagic.suit, fightAttr.derateMagic.final);

	//TellClient( "derateIgnoreShort-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d", 
	//    fightAttr.derateIgnoreShort.base, fightAttr.derateIgnoreShort.item, fightAttr.derateIgnoreShort.status, fightAttr.derateIgnoreShort.skill, 
	//    fightAttr.derateIgnoreShort.title, fightAttr.derateIgnoreShort.mount, fightAttr.derateIgnoreShort.suit, fightAttr.derateIgnoreShort.final);

	//TellClient( "derateIgnoreLong-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d",
	//    fightAttr.derateIgnoreLong.base, fightAttr.derateIgnoreLong.item, fightAttr.derateIgnoreLong.status, fightAttr.derateIgnoreLong.skill, 
	//    fightAttr.derateIgnoreLong.title, fightAttr.derateIgnoreLong.mount, fightAttr.derateIgnoreLong.suit, fightAttr.derateIgnoreLong.final);

	//TellClient( "derateIgnoreMagic-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d", 
	//    fightAttr.derateIgnoreMagic.base, fightAttr.derateIgnoreMagic.item, fightAttr.derateIgnoreMagic.status, fightAttr.derateIgnoreMagic.skill, 
	//    fightAttr.derateIgnoreMagic.title, fightAttr.derateIgnoreMagic.mount, fightAttr.derateIgnoreMagic.suit, fightAttr.derateIgnoreMagic.final);

	//TellClient( "dodge-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d",
	//    fightAttr.dodge.base, fightAttr.dodge.item, fightAttr.dodge.status, fightAttr.dodge.skill, fightAttr.dodge.title, fightAttr.dodge.mount, fightAttr.dodge.suit, fightAttr.dodge.final);

	//TellClient( "exact-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d", 
	//    fightAttr.exact.base, fightAttr.exact.item, fightAttr.exact.status, fightAttr.exact.skill, fightAttr.exact.title, fightAttr.exact.mount, fightAttr.exact.suit, fightAttr.exact.final);

	//TellClient( "critical->base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d", 
	//    fightAttr.critical.base, fightAttr.critical.item, fightAttr.critical.status, fightAttr.critical.skill, fightAttr.critical.title, fightAttr.critical.mount, fightAttr.critical.suit, fightAttr.critical.final);

	//TellClient( "criticalIntensity-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d",
	//    fightAttr.criticalIntensity.base, fightAttr.criticalIntensity.item, fightAttr.criticalIntensity.status, fightAttr.criticalIntensity.skill, 
	//    fightAttr.criticalIntensity.title, fightAttr.criticalIntensity.mount, fightAttr.criticalIntensity.suit, fightAttr.criticalIntensity.final);

	//TellClient( "tenacity-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d",
	//    fightAttr.tenacity.base, fightAttr.tenacity.item, fightAttr.tenacity.status, fightAttr.tenacity.skill, fightAttr.tenacity.title, fightAttr.tenacity.mount, fightAttr.tenacity.suit, fightAttr.tenacity.final);

	//TellClient( "resistDread-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d",
	//    fightAttr.breakResist.base, fightAttr.breakResist.item, fightAttr.breakResist.status, fightAttr.breakResist.skill, fightAttr.breakResist.title, fightAttr.breakResist.mount, fightAttr.breakResist.suit, fightAttr.breakResist.final);

	//TellClient( "resistComa-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d",
	//    fightAttr.penetrateResist.base, fightAttr.penetrateResist.item, fightAttr.penetrateResist.status, fightAttr.penetrateResist.skill, fightAttr.penetrateResist.title, fightAttr.penetrateResist.mount, fightAttr.penetrateResist.suit, fightAttr.penetrateResist.final);

	//TellClient( "resistSilence-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d",
	//    fightAttr.elementResist.base, fightAttr.elementResist.item, fightAttr.elementResist.status, fightAttr.elementResist.skill, fightAttr.elementResist.title, fightAttr.elementResist.mount, fightAttr.elementResist.suit, fightAttr.elementResist.final);

	//TellClient( "resistSlow-> base:%d item:%d status:%d skill:%d title:%d mount:%d suit:%d final:%d",
	//    fightAttr.toxinResist.base, fightAttr.toxinResist.item, fightAttr.toxinResist.status, fightAttr.toxinResist.skill, fightAttr.toxinResist.title, fightAttr.toxinResist.mount, fightAttr.toxinResist.suit, fightAttr.toxinResist.final);

	//TellClient( "attackSpeed-> base:%f item:%f itemP:%d status:%f statusPer:%d skill:%f skillP:%u title:%f titleP:%d mount:%f mountPer:%u suit:%f suitPer:%d final:%f",
	//    fightAttr.attackSpeed.base, fightAttr.attackSpeed.item, fightAttr.attackSpeed.itemPer, fightAttr.attackSpeed.status, fightAttr.attackSpeed.statusPer, fightAttr.attackSpeed.skill, fightAttr.attackSpeed.skillPer,fightAttr.attackSpeed.title,
	//    fightAttr.attackSpeed.titlePer, fightAttr.attackSpeed.mount, fightAttr.attackSpeed.mountPer, fightAttr.attackSpeed.suit, fightAttr.attackSpeed.suitPer, fightAttr.attackSpeed.final);

	//TellClient( "intonate-> base:%f item:%f itemP:%d status:%f statusPer:%d skill:%f skillP:%u title:%f titleP:%d mount:%f mountPer:%u suit:%f suitPer:%d final:%f", 
	//    fightAttr.intonate.base, fightAttr.intonate.item, fightAttr.intonate.itemPer, fightAttr.intonate.status, fightAttr.intonate.statusPer, fightAttr.intonate.skill, fightAttr.intonate.skillPer,fightAttr.intonate.title, fightAttr.intonate.titlePer, 
	//    fightAttr.intonate.mount, fightAttr.intonate.mountPer, fightAttr.intonate.suit, fightAttr.intonate.suitPer, fightAttr.intonate.final);*/
}

void GamePlayer::ProcessTestTellCountry( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nLevel = 0;
	int nID = 0;
	if( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &nLevel, &nID ) )
	{ return; }


	MsgTellCountryBordersFight xFight;
	xFight.ustMapID = GetMapID();
	xFight.ustPosX  = FloatToTile( GetFloatX() );
	xFight.ustPosY  = FloatToTile( GetFloatY() );
	GettheServer().SendMsgToCountry( &xFight, GetCountry(), false, nLevel, nID );
}

void GamePlayer::ProcessTestSetAreaVar( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nVarId = 0;
	int nValue = 0;
	int nRadius = 0;
	int nType = 0;
	if ( 5 != sscanf(szCommand, "%s %d %d %d %d", m_szCmdHead, &nVarId, &nValue, &nRadius, &nType) )
	{ return;}

	GetScriptInterface()->SetAreaVar( nVarId, nValue, nRadius, nType );
}

void GamePlayer::ProcessTestCountryQuestOpen( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nKey = 0;
	if ( 2 != sscanf(szCommand, "%s %d", m_szCmdHead, &nKey) )
	{ return;}

	GetScriptInterface()->IsCountryQuestOpen( nKey );
}

void GamePlayer::ProcessChangeSignature( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	char szSignature[ 64 ] = { 0 };
	if ( 2 != sscanf(szCommand, "%s %s", m_szCmdHead, szSignature ) )
	{ return;}

	m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateSignature, szSignature );
}

void GamePlayer::ProcessClearChangeCountryName( const char* szCommand )
{
	m_pCountry->SendCountryDataChangeReq( CountryDefine::UpdateChangeName, CountryDefine::OperateSet, 0 );
}

void GamePlayer::ProcessMonsterInfo( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nId = InvalidGameObjectId;
	if ( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nId ) )
	{ return; }

	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nLockID );
	if ( pChar == NULL || !pChar->IsMonster() )
	{
		TellClient( theXmlString.GetString( eClient_AddInfo_2slk_100 ), m_nLockID );
		return;
	}

	MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pChar );
	if ( !pMonster->CheckCanBeAttack() )
	{
		TellClient( theXmlString.GetString( eClient_AddInfo_2slk_101 ) );
		return;
	}

	BaseCharacter* pLockTarget = pMonster->GetLockChar();
	int id = InvalidGameObjectId;
	if ( pLockTarget != NULL )
	{ id = pLockTarget->GetID(); }

	TellClient( theXmlString.GetString(eClient_AddInfo_2slk_103), pMonster->GetID(), id );

	//TellClient( theXmlString.GetString(eClient_AddInfo_2slk_104), pMonsterChar->GetCurSkill(), pMonsterChar->GetCurSkillLevel());
	//TellClient( theXmlString.GetString(eClient_AddInfo_2slk_105), pMonster->GetMapID(), (uint16)pMonster->GetFloatX(), (uint16)pMonster->GetFloatY());
	//TellClient( theXmlString.GetString(eClient_AddInfo_2slk_106), FloatToTile(pMonster->_moveTargetPos.x), FloatToTile(pMonsterChar->_moveTargetPos.y));
	//TellClient( theXmlString.GetString(eClient_AddInfo_2slk_107), (int)this->GetEnmity(m_shLockCharID));
	//TellClient( theXmlString.GetString(eClient_AddInfo_2slk_108), pMonsterChar->GetAttackCharCount());
	//if (pUser != NULL)
	//{ TellClient( theXmlString.GetString(eClient_AddInfo_2slk_109), pUser->GetMapID(), pUser->GetTileX(), pUser->GetTileY()); }

	//if ( pMonsterChar->GetObjType() == Object_MonsterRoute  )
	//{
	//    MonsterRoute* pMonsterRoute = (MonsterRoute*)pMonsterChar;

	//    TellClient( "Statue [%d:%d:%d:%d:%d]", pMonsterRoute->GetRouteStep(),
	//                                           pMonsterRoute->GetIsArriveTargetPos(),
	//                                           pMonsterRoute->GetIsOutOfRoute(),
	//                                           pMonsterRoute->GetIsFinalArrive(),
	//                                           pMonsterRoute->GetIsNeedMove() );
	//}
}

void GamePlayer::ProcessShowServVersion( const char* szCommand )
{
	TellClient("ServVersion: %s", theApplicationConfig.GetFullVersion() );
}   

void GamePlayer::ProcessSignUpCampBattle( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nType = 0;
	if ( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nType ) )
	{ return;}

	CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry(nType,GetCountryId());/*theCampBattleControl.GetManager( nType );*/
	if ( pManager == NULL )
	{ return; }

	pManager->SignUpCampBattle( this );
}


void GamePlayer::ProcessEnterCampBattle( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nType = 0;
	if ( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nType ) )
	{ return;}

	CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry(nType,GetCountryId());/*theCampBattleControl.GetManager( nType );*/
	if ( pManager == NULL )
	{ return; }

	pManager->EnterCampBattle( this );
}


void GamePlayer::ProcessKillCampBattleMonster( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nMonster = 0;
	if ( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nMonster ) )
	{ return;}

	CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID(),GetCountryId() );
	if ( pCampBattle == NULL )
	{ return; }

	pCampBattle->KillCampBattleMonster( GetFightCamp(), GetDBCharacterID(), nMonster );
}

void GamePlayer::ProcessChangeCampBattleStatus( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nType = 0;
	int nStatus = 0;
	if ( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &nType, &nStatus ) )
	{ return;}

	CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry(nType,GetCountryId());/*theCampBattleControl.GetManager( nType );*/
	if ( pManager == NULL )
	{ return; }

	pManager->ProcessChangeStatus( nStatus );
}

void GamePlayer::ProcessCountryWarStatus( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nStatus = 0;
	if ( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nStatus ) )
	{ return;}

	GS2CSCountryWarStatusChange xChange;
	xChange.uchStatus = nStatus;
	GettheServer().SendMsgToCenterServer( &xChange );
}

void GamePlayer::ProcessTestTimeVar( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nVarType;
	int nOperateType;
	if ( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &nVarType, &nOperateType ) )
	{ return;}

	switch ( nVarType )
	{
	case 1:
		{
			if ( nOperateType == 1 )
			{ RecordNowTimeVar( 1 ); }
			else
			{ IsTimeVarPassOneDay( 1 ); }
		}
		break;
	case 2:
		{
			if ( nOperateType == 1 )
			{ GetScriptInterface()->RecordTeamTimeVar( 2 ); }
			else
			{ GetScriptInterface()->ClearTeamTimeVar( 2, 3 ); }
		}
		break;
	case 3:
		{
			if ( nOperateType == 1 )
			{ GetScriptInterface()->RecordGuildTimeVar( 2 ); }
			else
			{ GetScriptInterface()->ClearGuildTimeVar( 2, 3 ); }
		}
		break;
	}
}

void GamePlayer::ProcessAddXinFa( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int iWhichXinFa = 0;
	int nLevel = 0;
	if ( 3 != sscanf( szCommand, "%s %d %d", m_szCmdHead, &iWhichXinFa, &nLevel ) )
	{ return; }

	XinFaConfig::STalentXinFa* pTalentXinFa = theXinFaConfig.GetXinFaByID( iWhichXinFa, nLevel );
	if( pTalentXinFa == NULL )
	{ return ; }

	if ( !pTalentXinFa->arrayProfessionReq[GetProfession()] )
	{ 
		SendErrorToClient(ER_ProfessionToLearnXinFa);
		return ; 
	}

	SCharXinFa* pCurCharXinFa = _XinFaManager.GetXinFaByID( iWhichXinFa );

	bool bAddSuccess = false;
	if ( pCurCharXinFa == NULL )
	{ bAddSuccess =  _XinFaManager.AddXinFa(iWhichXinFa, nLevel); }
	else
	{
		pCurCharXinFa->nXinFaLevel = nLevel;
		bAddSuccess = true;
	}

	if ( bAddSuccess )
	{
		SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByID( iWhichXinFa );
		if( pCharXinFa == NULL )
		{
			SendErrorToClient(ER_LearnXinFa);
			return ; 
		}

		MsgChangeXinFa msg;
		msg.xinfa       = *pCharXinFa;
		msg.nUnUsedExp  = GetSkillExpUnUsed();

		if ( pCurCharXinFa == NULL )
		{ msg.op = MsgChangeXinFa::OT_Add; }
		else
		{ msg.op = MsgChangeXinFa::OT_Update; }

		GettheServer().SendMsgToSingle( &msg, this );

		for (int i = 0;i < XinFaConfig::EXCD_SkillMaxCount; ++i)
		{
			XinFaConfig::SXinFaSkill* pXinFaSkill = pTalentXinFa->GetXinFaSkill(i);
			if (pXinFaSkill == NULL)
			{ continue; }

			if (pXinFaSkill->nLevel != 0)
			{
				LearnSkill( pXinFaSkill->nId, pXinFaSkill->nLevel, false, true );
			}
		}

		ApplyTalentXinFaToChar  ();
		UpdateCharAllAttibute   ();
		SendCharAttibuteToClient();

		return ;
	}
}
void GamePlayer::ProcessFamilyProsperity( const char* szCommand )
{
	if ( NULL == m_pFamily )
	{ return; }

	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int nProsperity;
	if( 2 != sscanf( szCommand, "%s %d", m_szCmdHead, &nProsperity ) )
	{ return; }

	if ( nProsperity >= 0 )
	{
		m_pFamily->SetProsperity( nProsperity );

		GS2CSFamilyProsperityUpdate xUpdate;
		xUpdate.nFamilyID = m_pFamily->GetFamilyID();
		xUpdate.nProsperity = nProsperity;
		GettheServer().SendMsgToCenterServer( &xUpdate );

	}
}

void GamePlayer::ProcessTestLogService( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	int	 num =1;
	if ( 2 == sscanf( szCommand,"%s %d %d %d %d %s", m_szCmdHead, &num))
	{
		theLogEventService.TestLog(num);
	}
}
void GamePlayer::ChangePetMode( const char* szCommand )
{
	int index  =0 ;
	int ModeID = 0;
	int Sec = 0;
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	if ( 4 != sscanf( szCommand, "%s %d %d",m_szCmdHead,&index,&ModeID,&Sec) )
	{ return; }
	if(ModeID == 0 || !_petManager.GetPetByIndex(index))
		return;
	SetPetMode(_petManager.GetPetByIndex(index)->baseInfo.guid,ModeID,Sec);
}
void GamePlayer::ChangePet( const char* szCommand )
{
	int index  =0 ;
	int targetIndex = 0;
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	if ( 3 != sscanf( szCommand, "%s %d %d",m_szCmdHead,&index,&targetIndex) )
	{ return; }
	if(!_petManager.GetPetByIndex(targetIndex) || !_petManager.GetPetByIndex(index))
		return;
	_petManager.ChangePetAtterValue(_petManager.GetPetByIndex(index)->baseInfo.guid,_petManager.GetPetByIndex(targetIndex)->baseInfo.guid);
}
void GamePlayer::ChangeQuestStates( const char* szCommand )
{
	int QuestID = 0;
	int States = 0;
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	if ( 3 != sscanf( szCommand, "%s %d %d",m_szCmdHead,&QuestID,&States) )
	{ return; }
	SQuest* pQuest = theQuestManager.GetQuest( QuestID );
	if(!pQuest)
		return;
	int nowStates = theQuestManager.GetQuestState( GetVar( QuestID ) );
	SetVar( QuestID,theQuestManager.SetQuestState( GetVar( QuestID ), States ));
}
void GamePlayer::OpenGuildGeneralBattleSum( const char* szCommand )
{
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	unsigned int Sum = 0;
	if ( 2 != sscanf( szCommand, "%s %d",m_szCmdHead,&Sum) )
	{ return; }
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)	
		return;
	unsigned int MapID = pManager->GetGameBattleMapID();
	//组织命令
	time_t nowtime;
	time(&nowtime);
	GameBattleDefine::GuildCampBattle Add;
	Add.ID = 0;
	Add.MapID = MapID;
	//Add.SrcGuildID = SrcGuildID;
	//Add.DestGuildID = DestGuildID;
	Add.MoneySum = 100;
	Add.GuildMissionSum = 100;
	Add.GuildMoneySum = 100;
	Add.BeginTime = nowtime + 60;
	for(int i =0;i<Sum*2;i+=2)
	{
		Add.SrcGuildID = i;
		Add.DestGuildID = i+1;
		
		GS2CSAddCampBattleData msg;
		msg.add= Add;
		msg.Result = true;
		GettheServer().SendMsgToCenterServer( &msg );
	}
}
void GamePlayer::OpenGuildGeneralBattle( const char* szCommand )
{
	//开启一个战场
	char SrcPlayerName[PARAM_STRINGMAX+1] = {0};
	char DestPlayerName[PARAM_STRINGMAX+1] = {0};
	unsigned int Money = 0;
	unsigned int GuildMoney  = 0;
	unsigned int GuildMission = 0;
	//char szCmd[PARAM_STRINGMAX+1] = {0};
	if ( 6 != sscanf( szCommand, "%s %s %s %d %d %d",m_szCmdHead,&SrcPlayerName,&DestPlayerName,&Money,&GuildMoney,&GuildMission) )
	{ return; }
	GamePlayer* pSrcPlayer = theRunTimeData.GetGamePlayerByName(SrcPlayerName);
	GamePlayer* pDestPlayer = theRunTimeData.GetGamePlayerByName(DestPlayerName);
	if(!pSrcPlayer || !pDestPlayer)
		return;
	//组织命令 发送到中央服务器 添加新的公会约战 后面按流程走
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)	
		return;
	unsigned int MapID = pManager->GetGameBattleMapID();
	unsigned int SrcGuildID = pSrcPlayer->GetGuildID();
	unsigned int DestGuildID = pDestPlayer->GetGuildID();
	//组织命令
	time_t nowtime;
	time(&nowtime);
	GameBattleDefine::GuildCampBattle Add;
	Add.ID = 0;
	Add.MapID = MapID;
	Add.SrcGuildID = SrcGuildID;
	Add.DestGuildID = DestGuildID;
	Add.MoneySum = Money;
	Add.GuildMissionSum = GuildMission;
	Add.GuildMoneySum = GuildMoney;
	Add.BeginTime = nowtime + 60;

	GS2CSAddCampBattleData msg;
	msg.add= Add;
	msg.Result = true;
	GettheServer().SendMsgToCenterServer( &msg );
}
void GamePlayer::EnterGuildGeneralBattle( const char* szCommand )
{
	//当前玩家进入战场
	GameGuild* pGuild = theGameGuildManager.GetGuild(GetGuildID());
	if(!pGuild)
		return;
	//玩家公会存在的话 我们获取战场的管理器
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByUnitID(GetGuildID());
	if(!pBattle)
		return;
	if(!pManager->EnterGameBattle(this))
		return;
}
void GamePlayer::EndGuildGeneralBattle(const char* szCommand )
{
	GameGuild* pGuild = theGameGuildManager.GetGuild(GetGuildID());
	if(!pGuild)
		return;
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByUnitID(GetGuildID());
	if(!pBattle)
		return;
	pManager->ProcessChangeStatus(pBattle->GetBattleIndexID(),GameBattleDefine::StatusEnd);
}
void GamePlayer::ProcessOndeath(const char* szCommand )
{
	if ( !HaveLockTarget() )
	{ return; }

	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID(m_nLockID);
	if ( pTarget != NULL && pTarget->IsMonster() )
	{
		pTarget->OnExit( NULL );
	}
}
void GamePlayer::ProcessGreatCatch(const char* szCommand )
{
	if (m_nLockID == -1)
	{
		TellClient( theXmlString.GetString(eClient_AddInfo_2slk_110) );
		return;
	}

	//if ( HaveSummonPet(( 1 ) ) // 只让抓一个
	//{ return; }

	//BaseCharacter* pTarget = theRunTimeData.GetCharacterByID(m_shLockCharID);
	//if (pTarget != NULL && pTarget->IsMonster())
	//{ // ToModify boss不让抓
	//    MonsterBase* pAiTarget = (MonsterBase*) pTarget;
	//    pAiTarget->SetSummonMasterID( GetID());
	//    pAiTarget->SetCountry( GetCountry());
	//    pAiTarget->SetIsPet( true );
	//    pAiTarget->SetPetType( EPT_Capture );
	//    pAiTarget->SetSkillPetAIType( m_shLockCharID, ePetDefendAI );
	//    SPetMonster pet;
	//    pet.petId = m_shLockCharID;
	//    pet.petAIType = ePetDefendAI;
	//    pet.skillId = 1;
	//    AddPetMonster(pet);
	//    ApplyPassiveSkillsToPet( m_shLockCharID, -1 );
	//    RemoveEnmityList(m_shLockCharID);
	//    pTarget->ClearAttackerById(this->GetID());
	//    ExitMySight(pTarget);
	//    EnterMySight(pTarget);
	//}
}
void GamePlayer::ProcessMapmonsterinfo(const char* szCommand )
{
	DWORD nMap = this->GetMapID();
	GameStage* pStage = theGameWorld.GetStageById(nMap);
	if (pStage != NULL)
	{
		int nAllCount = pStage->GetCharacterTable().Count();
		int nPlayerCount = pStage->GetCharacterTable().PlayerCount();
		TellClient(theXmlString.GetString(eClient_AddInfo_2slk_88), nMap, nAllCount, nPlayerCount);
		TellClient(theXmlString.GetString(eClient_AddInfo_2slk_89), pStage->GetMonsterProducer().GetDeadMonsterNumber());
	}
}
void GamePlayer::ProcessRelivemapmonster(const char* szCommand )
{
	DWORD nMap = this->GetMapID();
	GameStage* pStage = theGameWorld.GetStageById(nMap);
	if (pStage != NULL)
	{
		pStage->GetMonsterProducer().AllMonsterDeadTimeClear();
		pStage->RefreshMonster(pStage->GetMonsterProducer().GetDeadMonsterNumber());
	}
}