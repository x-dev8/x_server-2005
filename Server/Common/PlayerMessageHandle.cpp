#include "GamePlayer.h"
#include "Dxsdk/d3dx9math.h"
#include "BaseCharacter.h"
#include "ShareData.h"
#include "GameTime.h"
#include "GameWorld.h"
#include "LoginStage.h"
#include "MathLib.h"
#include "DBMessageDefine.h"
#include "MonsterBaseEx.h"
#include "MonsterSummonPet.h"
#include "MonsterNurturePet.h"
#include "ServerVarInterface.h"
#include "Scriptcompiler.h"
#include "ScriptVarMgr.h"
#include "ItemCharacter.h"
#include "ItemDetail.h"
#include "ExpStage.h"
#include "helper.h" 
#include "Configure.h"
#include "MissionList.h"
#include "DatabaseConnectors.h"
#include "TimeClock.h"
#include "WordParser.h"
#include "AvatarSystemSetting.h"
#include "QuestManager.h"
#include "WordParser.h"
#include "RestoreColdDown.h"
#include "ProcessCharInfo.h"
#include "SystemConfig.h"
#include "NpcBaseEx.h"
#include "FuncPerformanceLog.h"
#include "DropQuestItem.h"
#include "ShareData.h"
#include "DataChunkWriter.h"
#include "ServerVarInterface.h"
#include "GlobalDef.h"
#include "ChatCheck.h"
#include "DuelHandler.h"
#include "XmlStringLanguage.h"
//#include "TradeCenterConfig.h"
#include "TimeEx.h"
#include "TeamManager.h"
#include "TradeCenterInfo.h"
#include "LuckRewardManager.h"
#include "DataCenter.h"
#include "SplitItemConfig.h"
#include "TreasureBoxConfig.h"
#include "GlobalFunction.h"
#include "RabotManager.h"
#include "DropItemManager.h"
#include "SpecialQuestManager.h"
#include "StarLevelUpConfig.h"
#include "TeamManager.h"
#include "OnLineRewardConfig.h"
#include "BattleManager.h"
#include "ExpActionConfig.h"
#include "CountryManager.h"
#include "CharacterAttributeConfig.h"
#include "CountryConfig.h"
#include "GameWorldTimer.h"
#include "RewardProfessionItemConfig.h"
#include "NpcShop.h"
#include "NpcShipEx.h"
#include "CampBattle.h"
#include "CampBattleControl.h"
#include "PetBreedManager.h"
#include "PetSettingConfig.h"
#include "FamilyConfig.h"
#include "ItemHero.h"
#include "ItemBag.h"
#include "TPHJManger.h"
#include "PocketShop.h"
#include "PasswordMessage.h"
#include "ResourcePath.h"
#include "LevelLimitDefine.h"
#include "LevelLimitGameManager.h"
#include "MountStrengthenConfig.h"
#include "LogEventService.h"
#include "CardIconConfig.h"
#include "CardAchieveConfig.h"
#include "SevenDays.h"
#include "CountryConfig.h"
#include "RankTitleConfig.h"
#include "HuntingQuestConfig.h"
#include "HuntingQuestManager.h"
#include "YuanBaoTotleConfig.h"
#include "GameBattleDataManager.h"
#include "MountMoveStarConfig.h"
extern IScriptInterface* GetScriptInterface();

#pragma warning( push )
#pragma warning( disable : 4293 )

bool GamePlayer::ProcessMsg(Msg* pMsg)
{ // 处理过的消息 return true
    int nStatus  = GetStatus();
    DWORD dwType = pMsg->GetType();

    if ( IsWantSwitchGameWaitSaveInfoOk() )
    { // 等待库返回
       // Log("收到不处理消息[%u],InWaitSaveInfo...", dwType );
		Log(theXmlString.GetString(eServerLog_ContGetMsg), dwType );
        return false;
    }

    switch ( nStatus )
    {
    case CS_LOGINTODB:
        {
            GAMESERVER_MESSAGE_MAPPING_BEGIN
                GAMESERVER_MESSAGE_HANDLE( DBMSG_ACKLOGIN, OnDBAckLogin )
            GAMESERVER_MESSAGE_MAPPING_END
        }
        break;
    case CS_LOGIN:
    case CS_WAITDBRET:
    case CS_DBLOGINED:
        {
            GAMESERVER_MESSAGE_MAPPING_BEGIN
                GAMESERVER_MESSAGE_HANDLE( DBMSG_ACKENTERWORD,         OnDBAckEnterWorld       )
                GAMESERVER_MESSAGE_HANDLE( MSG_ACK_RESULT,             OnMsgAckResult          )
                GAMESERVER_MESSAGE_HANDLE( MSG_GETCHARACTER,           OnGetCharacter          )
                GAMESERVER_MESSAGE_HANDLE( DBMSG_ACKCHAR,              OnDBAckChar             )
                GAMESERVER_MESSAGE_HANDLE( DBMSG_ENDACKCHAR,           OnDBAckCharEnd          )
                GAMESERVER_MESSAGE_HANDLE( MSG_CREATECHAR,             OnCreateChar            )
                GAMESERVER_MESSAGE_HANDLE( MSG_DELETECHAR,             OnDeleteChar            )
                GAMESERVER_MESSAGE_HANDLE( DBMSG_ACKCANCELDELCHAR,     OnDBAckCancelDelChar    )
                GAMESERVER_MESSAGE_HANDLE( MSG_CANCELDELCHAR,          OnCancelDelChar         )
                GAMESERVER_MESSAGE_HANDLE( DBMSG_ACKDELETECHAR,        OnDBAckDeleteChar       )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_CREATECHECKNAME,    OnMsgReqCreateCheckName )
				GAMESERVER_MESSAGE_HANDLE( MSG_NEWCHANGENAMEREQ,		OnMsgNewChangeNameReq )
                GAMESERVER_MESSAGE_HANDLE( DBMSG_ACKCREATECHAR,        OnDBAckCreateChar       )
                GAMESERVER_MESSAGE_HANDLE( DBMSG_ACKLOGIN,             OnDBAckLogin            )
                // GAMESERVER_MESSAGE_HANDLE( DBMSG_ACKCREATECHAR,     OnDBAckCreateChar       )
				GAMESERVER_MESSAGE_HANDLE( DB2DB_LOADCAMPBATTLEDATA,    OnLoadCampBattleData    )

            GAMESERVER_MESSAGE_MAPPING_END    
        }
        break; 
        //游戏状态
    case CS_LOADINGMAP:
        {
            GAMESERVER_MESSAGE_MAPPING_BEGIN
                GAMESERVER_MESSAGE_HANDLE( MSG_MAPLOADED        , OnMsgMapLoaded               )
                GAMESERVER_MESSAGE_HANDLE( MSG_QUERYDISPLAYNAME , OnQueryDisplayName           )
            GAMESERVER_MESSAGE_MAPPING_END 
        }
        break;
    case CS_IDLE:
    case CS_WALK:
    case CS_ATTACK:
    case CS_HURT:
    case CS_INTONATE:
    case CS_HOLDSKILL:
    case CS_DOACTION:
    case CS_READYTOUSESPEICALSKILL:
        {
            //强行更改SubAction为Normal.实际上SubAction现在是Idle的子状态     
            //if( nStatus != CS_IDLE
            //    || dwType == MSG_PLAYERMOVINGPOSANDDIRTOSERVER
            //    || dwType == MSG_PLAYERMOVINGPOSTOSERVER 
            //    || dwType == MSG_PLAYERPOSTOSERVER
            //    || dwType == MSG_PLAYERPOSANDDIRTOSERVER 
            //    || dwType == MSG_PLAYERDIRTOSERVER
            //    || dwType == MSG_JUMP 
            //    || dwType == MSG_DRAWWEAPON
            //    || dwType == MSG_DRAWINWEAPON
            //    )
            //{
                //if( !HaveFighteFlag(eFighting) )
                //    ChangeSubAction( CS_SubAction_Normal );
            //}

            GAMESERVER_MESSAGE_MAPPING_BEGIN
                GAMESERVER_MESSAGE_HANDLE( MSG_QUERYMOVE,                         OnQueryMove                        )
                GAMESERVER_MESSAGE_HANDLE( MSG_PLAYERMOVINGPOSTOSERVER,           OnMsgPlayerMovingPos               )
                GAMESERVER_MESSAGE_HANDLE( MSG_PLAYERMOVINGPOSANDDIRTOSERVER,     OnMsgPlayerMovingPosToDir          )
                GAMESERVER_MESSAGE_HANDLE( MSG_PLAYERPOSTOSERVER,                 OnMsgPlayerPos                     )
                GAMESERVER_MESSAGE_HANDLE( MSG_PLAYERDIRTOSERVER,                 OnMsgPlayerDir                     )
                GAMESERVER_MESSAGE_HANDLE( MSG_PLAYERPOSANDDIRTOSERVER,           OnMsgPlayerPosAndDir               )
                GAMESERVER_MESSAGE_HANDLE( MSG_INTONATEINTERRUPT,                 OnMsgIntonateInterrupt             )
                GAMESERVER_MESSAGE_HANDLE( MSG_JUMP,                              OnMsgJump                          )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHANGINGDIR,                       OnReqChangeDir                     )

                GAMESERVER_MESSAGE_HANDLE( MSG_DRAWWEAPON,                        OnMsgDrawWeapon                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_DRAWINWEAPON,                      OnMsgDrawInWeapon                  )
                GAMESERVER_MESSAGE_HANDLE( MSG_READYTOUSESPECIALSKILL,            OnMsgReadytoUseSpecialSkill        )
                GAMESERVER_MESSAGE_HANDLE( MSG_QUERYCHARAROUND,                   OnQueryCharAround                  )
                GAMESERVER_MESSAGE_HANDLE( MSG_GETPLAYERINFO,                     OnGetPlayerInfo                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_QUERYDISPLAYNAME,                  OnQueryDisplayName                 )
                GAMESERVER_MESSAGE_HANDLE( MSG_GETLAG,                            OnGetLag                           )
                GAMESERVER_MESSAGE_HANDLE( MSG_CLEANUP_BAG,                       OnMsgCleanUpBag                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQSKILLATTACK,                    OnMsgReqSkillAttack                )
                GAMESERVER_MESSAGE_HANDLE( MSG_EQUIP_EVOLVE,                      OnEquipEvolve                      )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEMOUNTNAME,                   OnMsgChangeMountName               )
                GAMESERVER_MESSAGE_HANDLE( MSG_RETURNTO_CHARACTERSERVER,          OnMsgReturnToCharacterServer       )
                GAMESERVER_MESSAGE_HANDLE( MSG_QUERY_COMPOUND_NEW,                OnMsgRecipeCompoundItem            )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_RMB_OP,                        OnMsgReqRmbOp                      ) // 获得金锭
                GAMESERVER_MESSAGE_HANDLE( S2S_CALL_GRAPHIC,                      OnS2SCallGraphic                   ) // 呼叫验证码
                //GAMESERVER_MESSAGE_HANDLE( MSG_MONEYITEMEXCHANGEREQ,              OnMsgMoneyItemExchange             ) // 实物申领
                GAMESERVER_MESSAGE_HANDLE( MSG_CHANGENAMEREQ,                     OnMsgChangeNameReq                 ) // 改名字
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_RESETTIME,                     OnResetItemTime                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQCANCELSKILL,                    OnReqCancelSkill                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_DROPITEM,                          OnDropItem                         )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_UP_ATTR_LEVEL,                 OnReqUpAttrLevel                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_REFRESHHOTKEY,                     OnRefreshHotKey                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQATTACKGROUND,                   OnReqAttackGround                  )
                GAMESERVER_MESSAGE_HANDLE( MSG_USEGOODSTOMOUNT,                   OnUseGoods                         )
                GAMESERVER_MESSAGE_HANDLE( MSG_USEGOODS,                          OnUseGoods                         )
                GAMESERVER_MESSAGE_HANDLE( MSG_BUYORSELLGOODS,                    OnBuyOrSellGoods                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHAT,                              OnChatMsg                          )
                // GAMESERVER_MESSAGE_HANDLE( MSG_QUERYSERVERINFO,                OnQueryServerInfo                  )
                GAMESERVER_MESSAGE_HANDLE( MSG_QUERYCONTINUOUSSKILL,              OnMsgQueryContinuousSkill          )
                GAMESERVER_MESSAGE_HANDLE( MSG_QUERYHPINFO,                       OnMsgQueryHPInfo                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_SCRIPT,                        OnQueryScript                      )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_UPSKILL,                       OnReqUpSkill                       )
                GAMESERVER_MESSAGE_HANDLE( MSG_CREATETEAM,                        OnCreateTeam                       )
				GAMESERVER_MESSAGE_HANDLE( MSG_REQUESTTEAM,                       OnRequestTeam                      )
                GAMESERVER_MESSAGE_HANDLE( MSG_KICKFROMTEAM,                      OnKickFromTeam                     )
				GAMESERVER_MESSAGE_HANDLE( MSG_DISBANDTEAM,                       OnDisbandTeam                      )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEDIR,                         OnChangeDir                        )
                GAMESERVER_MESSAGE_HANDLE( MSG_EQUIP,                             OnEquipNew                         )
                GAMESERVER_MESSAGE_HANDLE( MSG_EQUIPTOWHERE,                      OnEquipToWhere                     )
                GAMESERVER_MESSAGE_HANDLE( MSG_UNEQUIP,                           OnUnEquip                          )
                GAMESERVER_MESSAGE_HANDLE( MSG_LEARNSKILL,                        OnLearnSkill                       )                
                GAMESERVER_MESSAGE_HANDLE( MSG_QUERY_COMPOUND,                    OnQueryCompound                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_SCRIPT_ACK_SHOW_QUEST_DLG,         OnAckScriptShowQuestDlg            )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_QUEST_INFO,                    OnReqQuestInfo                     )
                GAMESERVER_MESSAGE_HANDLE( MSG_GETSHOPCENTER,                     OnGetShopCenter                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_GETSHOP,                           OnGetShop                          )
                GAMESERVER_MESSAGE_HANDLE( MSG_ABANDON_TASK,                      OnAbandonTask                      )
                GAMESERVER_MESSAGE_HANDLE( MSG_QUERY_SCRIPTVAR,                   OnQueryScriptVar                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_MOVE_STORAGE_ITEM,                 OnMoveStorageItem                  )  
                GAMESERVER_MESSAGE_HANDLE( MSG_STORAGEMONEYREQ,                   OnMsgStorageMoneyReq               )  
                GAMESERVER_MESSAGE_HANDLE( MSG_REPAIRITEM,                        OnMsgRepairItem                    )  
                GAMESERVER_MESSAGE_HANDLE( MSG_SPECIALREPAIRITEMREQ,              OnMsgSpecialRepairItem             )  
                GAMESERVER_MESSAGE_HANDLE( MSG_SHOPCENTERBUY,                     OnShopCenterBuy                    )  
                
                GAMESERVER_MESSAGE_HANDLE( MSG_MOVE_INTENSIFY_ITEM,               OnMoveIntensifyItem                )
                GAMESERVER_MESSAGE_HANDLE( MSG_WANTPEEK,                          OnMsgPeekPlayerEquip               )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_DUEL,                          OnMsgReqDuel                       )
                GAMESERVER_MESSAGE_HANDLE( MSG_ACK_DUEL,                          OnMsgAckDuel                       )
                GAMESERVER_MESSAGE_HANDLE( MSG_DUEL_START,                        OnMsgDuelStart                     )
                GAMESERVER_MESSAGE_HANDLE( MSG_DUEL_STOP,                         OnMsgDuelStop                      )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHANGE_PKFLAG,                     OnChangePKFlag                     )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_ECTYPEMAP_INFO,                OnReqEctypeMapInfo                 )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_FLYTOMAP,                      OnReqFlytomap                      )
                GAMESERVER_MESSAGE_HANDLE( MSG_ACK_ASSIGN_TEAM,                   OnAckMsgAssignTeam                 )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_CHANGE_ASSIGNMODE,             OnReqChangeAssignMode              )
                GAMESERVER_MESSAGE_HANDLE( MSG_TEAMCHANGEASSIGNITEMLEVELREQ,      OnReqChangeAssignItemLevel         )
                GAMESERVER_MESSAGE_HANDLE( MSG_ACK_CHANGE_ASSIGNMODE_ANSWER,      OnReqChangeAssignMode_Answer       )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_UPGRADE_TEAM,                  OnReqUpgradeTeam                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_SKILLEXPTOSKILL,                   OnMsgForSkillExpToSkill            )
                GAMESERVER_MESSAGE_HANDLE( MSG_ACK_FIRSTTIP,                      OnMsgSetTipVar                     )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_CHANGESUBACTION,               OnMsgReqChangeSubAction            )
                GAMESERVER_MESSAGE_HANDLE( MSG_ADDTITLEREQ,                       OnMsgAddTitleReq                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHANGETITLEREQ,                    OnMsgChangeTitle                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_REFER_INVITE_RESULT,               OnMsgInviterResult                 )   
                GAMESERVER_MESSAGE_HANDLE( MSG_ASK_EXECUTE_SCRIPT,                OnMsgAskExecuteScript              ) // 请求执行脚本
                GAMESERVER_MESSAGE_HANDLE( MSG_SWITCHSUIT,                        OnSwitchSuit                       )
                GAMESERVER_MESSAGE_HANDLE( MSG_SHOW_HELMET,                       OnMsgShowHelmet                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEPROTECTLOCKTIMEREQ,          OnMsgChangeProtectLockTimeReq      )
                GAMESERVER_MESSAGE_HANDLE( MSG_INQUIREINVITEE,                    OnMsgTeamInvitee                   )
				GAMESERVER_MESSAGE_HANDLE( MSG_REQTEAMFOLLOW,					  OnReqTeamFollow                    )
				GAMESERVER_MESSAGE_HANDLE( MSG_ACKTEAMFOLLOW,					  OnAckTeamFollow                    )
				GAMESERVER_MESSAGE_HANDLE( MSG_HEADERCANCELTEAMFOLLOW,			  OnHeaderCancelTeamFollow           )
				GAMESERVER_MESSAGE_HANDLE( MSG_CANCELTEAMFOLLOW,				  OnCancelTeamFollow				 )
                GAMESERVER_MESSAGE_HANDLE( MSG_RECEIVEQUESTREQ,                   OnMsgReceiveQuestReq               )
                GAMESERVER_MESSAGE_HANDLE( MSG_RETPUBQUESTREQ,                    OnMsgResetPubQuestReq              )
                GAMESERVER_MESSAGE_HANDLE( MSG_CLIENTTEAMINFO,                    OnMsgClientTeamInfo                )
                GAMESERVER_MESSAGE_HANDLE( MSG_MOVESTARREQ,                       OnMsgMoveStarReq                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_SUITELEMENTCHECKUPREQ,             OnMsgSuitElementCheckupReq         )
                GAMESERVER_MESSAGE_HANDLE( MSG_EQUIPUPGRADEREQ,                   OnMsgEquipUpgradeReq               )
                GAMESERVER_MESSAGE_HANDLE( MSG_SUITLEVELUPREQ,                    OnMsgSuitLevelUpReq                )
                GAMESERVER_MESSAGE_HANDLE( MSG_SUITCHANGEREQ,                     OnMsgSuitChangeReq                 )
                GAMESERVER_MESSAGE_HANDLE( MSG_ONLINEREWARDREQ,                   OnMsgOnLineRewardReq               )
                GAMESERVER_MESSAGE_HANDLE( MSG_BUYBACKITEMREQ,                    OnMsgBuyBackItemReq                )
                GAMESERVER_MESSAGE_HANDLE( MSG_BUYBACKITEMLISTREQ,                OnMsgBuyBackItemListReq            )
                GAMESERVER_MESSAGE_HANDLE( MSG_BATTLESIGNUPREQ,                   OnMsgBattleSignUpReq               )
                GAMESERVER_MESSAGE_HANDLE( MSG_CANCELBUFF,                        OnMsgCancelBuff                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_SENDMAILREQ,                       OnMsgSendMailReq                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_OPMAILREQ,                         OnMsgOpMailReq                     )       
                GAMESERVER_MESSAGE_HANDLE( MSG_ENTERTEAMBATTLEACK,                OnMsgEnterTeamBattleAck            )   
                GAMESERVER_MESSAGE_HANDLE( MSG_SUITELEMENTMOVEREQ,                OnMsgSuitElementMoveReq            )   
                GAMESERVER_MESSAGE_HANDLE( MSG_EXPRESSION,                        OnMsgQueryExpression               )  
                GAMESERVER_MESSAGE_HANDLE( MSG_ITEMRECLAIM,                       OnMsgItemReclaim                   ) 
                GAMESERVER_MESSAGE_HANDLE( MSG_ITEMCOMPOSEGEM,                    OnMsgItemComposeGem                )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQPRESSKEYSUIT,                   OnMsgReqPressKeySuit               )
                GAMESERVER_MESSAGE_HANDLE( MSG_PRESSKEYSUIT,                      OnMsgPressKeySuit                  )
                GAMESERVER_MESSAGE_HANDLE( MSG_PRESSKEYSUITRENAME,                OnMsgPressKeySuitName              )
                GAMESERVER_MESSAGE_HANDLE( MSG_EQUIPPRESSKEYSUIT,                 OnMsgEquipPressKeySuit             )
				GAMESERVER_MESSAGE_HANDLE( MSG_REQACHIEVEDATA,                    OnMsgReqAchieveData                )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQACHIEVEREWARD,                  OnMsgReqAchieveReward              )
                GAMESERVER_MESSAGE_HANDLE( MSG_LEARNALLSKILL,                     OnLearnAllSkill                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_MOVESTORAGEMOUNT,                  OnMoveStorageMount                 )
                GAMESERVER_MESSAGE_HANDLE( MSG_MOUNTPOTENTIAL,                    OnMsgMountPotential                )
                //GAMESERVER_MESSAGE_HANDLE( MSG_CHARLEVELUP,                       OnMsgCharacterLevelUp              )
                GAMESERVER_MESSAGE_HANDLE( MSG_MOUNTBREED,                        OnMsgMountBreed                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_SETOFFLINEHOOK,                    OnMsgSetOfflineHook                )
                GAMESERVER_MESSAGE_HANDLE( MSG_GETOFFLINEHOOKEXP,                 OnMsgGetOfflineHookExp             )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQDOUBLEEXP,                      OnMsgReqDoubleExp                  )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHARASSIGNPOTENTIAL,               OnMsgCharAssignPotential           )
                GAMESERVER_MESSAGE_HANDLE( MSG_LEARNXINFA,                        OnMsgLearnXinFa                    )

                GAMESERVER_MESSAGE_HANDLE( MSG_REQGOTONDROME,                     OnMsgReqGotOnDrome                 )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQGOTONDROMEACK,                  OnMsgReqGotOnDromeAck              )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQGOTOFFDROME,                    OnMsgReqGotOffDrome                )
				 GAMESERVER_MESSAGE_HANDLE(MSG_RIDEROFFDROME,                     OnMsgRiderOffDrome                 )

                GAMESERVER_MESSAGE_HANDLE( MSG_SHOWSIGNATURE,                     OnMsgShowSignature                 )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQDONEQUEST ,                     OnMsgReqDoneQuest                  )

                GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEPETNAME ,                    OnMsgChangePetName                 )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEPET     ,                    OnMsgChangePet                     )
                GAMESERVER_MESSAGE_HANDLE( MSG_PETPOTENTIAL  ,                    OnMsgPetPotential                  )
                GAMESERVER_MESSAGE_HANDLE( MSG_USEGOODSTOPET,                     OnUseGoods                         )
                GAMESERVER_MESSAGE_HANDLE( MSG_PETSAVVYUP,                        OnMsgPetSavvyUp                    )

                GAMESERVER_MESSAGE_HANDLE( MSG_PETBREEDREQ      ,                OnMsgPetBreedReq                    )
                GAMESERVER_MESSAGE_HANDLE( MSG_PETBREEDCHOICE   ,                OnMsgPetBreedChoice                 )
                GAMESERVER_MESSAGE_HANDLE( MSG_PETBREEDLOCK     ,                OnMsgPetBreedLock                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_PETBREEDCANCELLOCK,               OnMsgPetBreedCancelLock             )
                GAMESERVER_MESSAGE_HANDLE( MSG_PETBREEDCONFIRM  ,                OnMsgPetBreedConfirm                )
                GAMESERVER_MESSAGE_HANDLE( MSG_PETBREEDCANCELREQ,                OnMsgPetBreedCancelReq              )
                GAMESERVER_MESSAGE_HANDLE( MSG_PETBREEDACQUIRE  ,                OnMsgPetBreedAcquire                )
                GAMESERVER_MESSAGE_HANDLE( MSG_VIEWACTIVEPET    ,                OnMsgViewActivePet                  )

                GAMESERVER_MESSAGE_HANDLE( MSG_SAWTALKREQ,                       OnMsgSawTalkReq                     )
                GAMESERVER_MESSAGE_HANDLE( MSG_PLAYMOVIEACK,                     OnMsgPlayMovieAck                   )
                GAMESERVER_MESSAGE_HANDLE( MSG_ENDEVENTREQ,					     OnMsgEndEventReq				     )

                GAMESERVER_MESSAGE_HANDLE( MSG_MAILLISTREQ,					     OnMsgMailListReq				     )

                GAMESERVER_MESSAGE_HANDLE( MSG_REQIDENTIFYDATA,					 OnMsgReqIdentifyData				 )

                GAMESERVER_MESSAGE_HANDLE( MSG_EQUIPTALISMAN,					 OnMsgEquipTalisman 				 )
                GAMESERVER_MESSAGE_HANDLE( MSG_UNEQUIPTALISMAN,				     OnMsgUnEquipTalisman    			 )

                GAMESERVER_MESSAGE_HANDLE( MSG_UPDATEGUIDEREQ,				     OnMsgUpdateGuideReq    			 )
				GAMESERVER_MESSAGE_HANDLE( MSG_ACK_LIMITINFO,				     OnMsgAckLimitInfo    			 )

				GAMESERVER_MESSAGE_HANDLE( MSG_ZHUJIANGCOMPOSE,				     OnMsgZhuJiangCompose    			 )
				GAMESERVER_MESSAGE_HANDLE( MSG_REQ_FLYTOKINGDOM,				 OnMsgFlytoKingdom    			 )

				GAMESERVER_MESSAGE_HANDLE( MSG_TRANSFER_STAR,					 OnMsgTransferStar					)
				GAMESERVER_MESSAGE_HANDLE( MSG_MOUNT_STRENGTHEN,				 OnMsgMountStrengthen				)

				GAMESERVER_MESSAGE_HANDLE( MSG_UNBINDEQUIPREQ,					OnMsgUnBindEquipReq         )//装备解绑定
				GAMESERVER_MESSAGE_HANDLE( MSG_ASKFORPRESENT,					OnMsgAskForPresent         )
				GAMESERVER_MESSAGE_HANDLE( MSG_RANDATTRIBUTE_REQ,               OnMsgRandAttribute         )
				GAMESERVER_MESSAGE_HANDLE( MSG_ADDPETEQUIP,						OnMsgAddPetEquip         )
				GAMESERVER_MESSAGE_HANDLE( MSG_REMOVEPETEQUIP,					OnMsgRemovePetEquip         )
				GAMESERVER_MESSAGE_HANDLE( MSG_PETCOMPOSE,						OnMsgPetCompose         )
				GAMESERVER_MESSAGE_HANDLE( MSG_OPENBAGSTORAGE,					OnMsgOpenBagStorage)
				

				GAMESERVER_MESSAGE_HANDLE( MSG_RECARDACHIEVE,					 OnMsgCardAchieve         )
				GAMESERVER_MESSAGE_HANDLE( MSG_ASKSEVENDAYSDATA,				 OnMsgSevenDaysData         )
				GAMESERVER_MESSAGE_HANDLE( MSG_ASKSEVENDAYSTASK,				 OnMsgAskSevenDaysTask      )
				GAMESERVER_MESSAGE_HANDLE( MSG_ASKSEVENDAYSREWARD,				 OnMsgAskSevenDaysReward    )
				GAMESERVER_MESSAGE_HANDLE( MSG_CHANGECHANNEL_REQ,				 OnMsgChangeChannel    )
				GAMESERVER_MESSAGE_HANDLE( MSG_CLEARTEAMMAPREQ,					OnMsgClearTeamMapReq   )

				GAMESERVER_MESSAGE_HANDLE( MSG_ASKGETSALARY,					OnMsgAskGetSalary    )
				GAMESERVER_MESSAGE_HANDLE( MSG_ASKADVANCEMENT,					OnAskAdvancement   )				
				GAMESERVER_MESSAGE_HANDLE( MSG_SHOWRANKTITLE,				 OnMsgShowRankTitle )
				GAMESERVER_MESSAGE_HANDLE( MSG_HUNTING_ASKFORLIST,				 OnMsgAskHuntingList )
				GAMESERVER_MESSAGE_HANDLE( MSG_HUNTING_REFRESH,				 OnMsgHuntingReFresh )
				GAMESERVER_MESSAGE_HANDLE( MSG_HUNTING_ACCEPT_QUEST,				 OnMsgAcceptHuntingQuest )
            GAMESERVER_MESSAGE_MAPPING_END
        }
		break;
    case CS_DIEING:
        {
            //死的时候只能聊天，和等待复活
            GAMESERVER_MESSAGE_MAPPING_BEGIN
                GAMESERVER_MESSAGE_HANDLE( MSG_REQRELIVE,         OnRelive      )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHAT,              OnChatMsg     )
                GAMESERVER_MESSAGE_HANDLE( MSG_REQ_SCRIPT,        OnQueryScript )
                GAMESERVER_MESSAGE_HANDLE( MSG_ISRELIVEYESORNO,   OnMsgReLive   )
				GAMESERVER_MESSAGE_HANDLE( MSG_RETURNTO_CHARACTERSERVER,          OnMsgReturnToCharacterServer       )
            GAMESERVER_MESSAGE_MAPPING_END
        }
        break;
    case CS_ONSHIP:
        {
            GAMESERVER_MESSAGE_MAPPING_BEGIN
                GAMESERVER_MESSAGE_HANDLE( MSG_REQOFFNPCSHIP, OnMsgReqOffNpcShip )
                GAMESERVER_MESSAGE_HANDLE( MSG_CHAT         , OnChatMsg          )
            GAMESERVER_MESSAGE_MAPPING_END
        }
        break;
    default:
        break;
    }        
    
    // 公共消息 不论玩家处于什么状态都能进行处理
    GAMESERVER_MESSAGE_MAPPING_BEGIN
        GAMESERVER_MESSAGE_HANDLE( MSG_PING,                         OnPingMsg                         )
        GAMESERVER_MESSAGE_HANDLE( DBMSG_ACK_CREATE_CHECKNAME,       OnMsgAckCreateCheckName           )
		GAMESERVER_MESSAGE_HANDLE( DBMSG_CHANGENAMEACK,				 OnDBMsgChangeNameAck              )
        GAMESERVER_MESSAGE_HANDLE( MSG_ACKINQUIREINVITEE,            OnAckMsgInquireInvitee            )
        GAMESERVER_MESSAGE_HANDLE( MSG_ACKFORREDUCE,                 OnMsgSplitItem                    )
        GAMESERVER_MESSAGE_HANDLE( MSG_ACKGRAPHICCODE,               OnMsgAckGraphiccode               ) //任何情况下都能发送图片验证码
        GAMESERVER_MESSAGE_HANDLE( MSG_ACKNUMBERCODE,                OnMsgAckNumberCode                ) //任何情况下都能发送图片验证码
        GAMESERVER_MESSAGE_HANDLE( MSG_LOCKTARGET,                   OnMsgLockTarget                   )
        GAMESERVER_MESSAGE_HANDLE( MSG_SELECTCHANNEL,                OnMsgSelectChannel                )
        GAMESERVER_MESSAGE_HANDLE( MSG_ENTERWORLD,                   OnEnterWorld                      )
        GAMESERVER_MESSAGE_HANDLE( MSG_PETCOMMAND,                   OnMsgPetCommand                   )
        GAMESERVER_MESSAGE_HANDLE( MSG_DISDROME,                     OnMsgDisDrome                     )
        GAMESERVER_MESSAGE_HANDLE( MSG_ATTACKLOCKTARGET,             OnMsgAttackLockTarget             )
        GAMESERVER_MESSAGE_HANDLE( MSG_DISHITCH,                     OnMsgDisHitch                     )
        GAMESERVER_MESSAGE_HANDLE( MSG_LOCK_ITEM,                    OnLockItemReq                     )
        GAMESERVER_MESSAGE_HANDLE( MSG_CHECKUNLOCK_ITEMREQ,          OnCheckUnLockItemReq              )
        GAMESERVER_MESSAGE_HANDLE( MSG_UNLOCK_ITEM,                  OnUnLockItemReq                   )
        GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEITEMPOS,                OnMsgChangeItemPos                )
        GAMESERVER_MESSAGE_HANDLE( MSG_MOVEGOODSREQ,                 OnMoveGoods                       )
        GAMESERVER_MESSAGE_HANDLE( MSG_SCRIPTCANCEL,                 OnScriptCancel                   )
        GAMESERVER_MESSAGE_HANDLE( MSG_MOVE_REDUCE,                  OnMsgMoveReduceItem               )
        GAMESERVER_MESSAGE_HANDLE( MSG_CALLUNSOULBOUND,              OnMsgUnSoulBound                  )
        GAMESERVER_MESSAGE_HANDLE( MSG_MOVE_UNSOULBOUND,             OnMsgMoveUnSoulBound              )
        GAMESERVER_MESSAGE_HANDLE( MSG_FARREPAIRCOSTRMB,             OnMsgCostSilverRepair             )
        GAMESERVER_MESSAGE_HANDLE( MSG_REQ_CHANGE_OWNATTRIBUTE,      OnChange_OwnAttribute             )
        GAMESERVER_MESSAGE_HANDLE( MSG_MODIFY_PLAYER_HELP_FLAG,      OnMsgModifyHelpFlag               )
        GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEDROME,                  OnMsgChangeDrome                  )
        GAMESERVER_MESSAGE_HANDLE( MSG_PACKAGEVIEWREQ,               OnMsgPackageViewReq               )
        GAMESERVER_MESSAGE_HANDLE( MSG_PACKAGEVIEWEND,               OnMsgPackageViewEnd               )
        GAMESERVER_MESSAGE_HANDLE( MSG_PICKPACKAGEITEMREQ,           OnMsgPickPackageItemReq           )
        GAMESERVER_MESSAGE_HANDLE( MSG_PICKPACKAGEITEMBOULTACK,      OnMsgPackageItemBoultAck          )
        GAMESERVER_MESSAGE_HANDLE( MSG_PICKPACKAGEITEMASSIGNREQ,     OnMsgPackageItemAssignReq         )
        GAMESERVER_MESSAGE_HANDLE( MSG_PACKAGEITEMACCESSREQ,         OnMsgPackageItemAccessReq         )
        GAMESERVER_MESSAGE_HANDLE( MSG_QUERYCHARINFO,                OnQueryCharInfo                   )
        GAMESERVER_MESSAGE_HANDLE( MSG_LUCKREWARDREQ,                OnMsgLuckRewardReq                )
        GAMESERVER_MESSAGE_HANDLE( MSG_TREASUREBOXREQ,               OnMsgTreasureBoxReq               )
        GAMESERVER_MESSAGE_HANDLE( MSG_CHECKCHEATACK,                OnMsgCheckCheatAck                )
        GAMESERVER_MESSAGE_HANDLE( MSG_GETPROCESSLISTACK,            OnMsgGetProcesslistAck            )
        GAMESERVER_MESSAGE_HANDLE( MSG_JIFENGSHOPITEMSLISTREQ,       OnMsgJiFengShopItemsListReq       )
        GAMESERVER_MESSAGE_HANDLE( MSG_JIFENGSHOPITEMSGAIN,          OnMsgJiFengShopItemsGain          )
        GAMESERVER_MESSAGE_HANDLE( DBMSG_JIFENGSHOPITEMSLISTACK,     OnDBMsgJiFengShopItemsListAck     )
        GAMESERVER_MESSAGE_HANDLE( DBMSG_JIFENGSHOPITEMSGAINACK,     OnDBMsgJiFengShopItemsGainAck     )
        GAMESERVER_MESSAGE_HANDLE( MSG_TRADESHOPCONFIGREQ,           OnMsgUpdateTradeShopConfigReq     )
        GAMESERVER_MESSAGE_HANDLE( MSG_MOVESTARLEVELUPREQ,           OnMsgMoveStarLevelUpReq           )
        GAMESERVER_MESSAGE_HANDLE( MSG_ITEMCOMPOSEREQ,               OnMsgItemComposeReq               )
        GAMESERVER_MESSAGE_HANDLE( MSG_LEAVEBATTLEREQ,               OnMsgLeaveBattleReq               )
        GAMESERVER_MESSAGE_HANDLE( MSG_QUERYBATTLETEAMINFOREQ,	     OnMsgQueryBattleTeamInfoReq       )
        GAMESERVER_MESSAGE_HANDLE( MSG_QUERYTEAMRECORDREQ,	         OnMsgQueryTeamRecordReq           )
        GAMESERVER_MESSAGE_HANDLE( MSG_QUERYBATTLESIGNUPTIMEREQ,	 OnMsgQueryBattleSignUpTimeReq     )
        GAMESERVER_MESSAGE_HANDLE( MSG_EXITTEAM,                     OnExitTeam                        )
        GAMESERVER_MESSAGE_HANDLE( MSG_OFFLINEFIGHTOPREQ,            OnMsgOfflineFightOp               )
        GAMESERVER_MESSAGE_HANDLE( DBMSG_PETBREEDQUERYACK,           OnDBMsgPetBreedQueryAck           )
		GAMESERVER_MESSAGE_HANDLE( MSG_C2G_ASK_BIANSHEN,			 OnMsgBianShen					   )
		GAMESERVER_MESSAGE_HANDLE( MSG_REQ_FLYTOTPHJ,				 OnMsgFlyToTPHJ					   )
		GAMESERVER_MESSAGE_HANDLE( MSG_CHANGE_2_BIAOCHE_REQ,		 OnMsgChangeToBiaocheReq		   )
		GAMESERVER_MESSAGE_HANDLE( MSG_RESTORE_FROM_BIAOCHE_REQ,	 OnMsgRestoreFromBiaocheReq		   )
		GAMESERVER_MESSAGE_HANDLE( MSG_SHOW_HEROSUIT,				 OnMsgChangeHeroType		   )
		GAMESERVER_MESSAGE_HANDLE( MSG_ACK_LEVELUP,					 OnMsgAckLevelUp		   )
		GAMESERVER_MESSAGE_HANDLE( MSG_ACK_ACTIVELIMIT,				 OnMsgAckActiveLimit		   )
		GAMESERVER_MESSAGE_HANDLE( DBMSG_SETBILLINGMONEY,            OnDBMsgSetBillingMoney           )
		GAMESERVER_MESSAGE_HANDLE( DBMSG_SETCONSUMESCORE,            OnDBMsgSetConsumeScore           )
		GAMESERVER_MESSAGE_HANDLE( MSG_RECONNECT,					 OnMsgReConnect )

		GAMESERVER_MESSAGE_HANDLE( MSG_FLYTOPOSITIONACK,			 OnMsgFlyToPositionAck )
		GAMESERVER_MESSAGE_HANDLE( MSG_GETTHREEDAYITEM,				 OnMsgGetThreeDayItem )

		GAMESERVER_MESSAGE_HANDLE( MSG_UPDATEYUANBAODATAREQ,		  OnMsgUpdateYuanBaoDataReq )

		GAMESERVER_MESSAGE_HANDLE( DB2GS_UPDATEYUANBAODATA,		  OnDB2GSUpdateYuanBaoData )

		GAMESERVER_MESSAGE_HANDLE( MSG_MOUNTMOVESTAR,		  OnMsgMountMoveStar )

		GAMESERVER_MESSAGE_HANDLE( DB2GS_UPDATEPLAYERPOINT,		  OnDB2GSUpdatePlayerPoint )

		GAMESERVER_MESSAGE_HANDLE( MSG_LEAVEEXPREQ,		  OnMsgLeaveExpReq )
		GAMESERVER_MESSAGE_HANDLE( MSG_GETLEAVEEXPREQ,		  OnMsgGetLeaveExpReq )

		GAMESERVER_MESSAGE_MAPPING_END

    switch ( pMsg->GetModuleType() )
    {
    case EMessageModule_Relation: // 处理关系消息
        return ProcessRelationMsg( pMsg );
        break;
    case EMessageModule_Country:  // 处理国家消息 
        return ProcessCountryMsg( pMsg ); 
        break;
    case EMessageModule_Guild:    // 处理关系消息
        return ProcessGuildMsg( pMsg );
        break;
    case EMessageModule_Consignment: // 处理寄售消息
        return ProcessConsignmentMessage( pMsg );
        break;
    case EMessageModule_Stall:  // 处理摆摊消息
        return ProcessStallMsg( pMsg );
        break;
    case EMessageModule_Bargaining:  // 处理交易消息
        return ProcessBargainingMsg( pMsg );
        break;
    case EMessageModule_Password:    // 处理密码模块
        return ProcessPasswordMsg( pMsg );
        break;
    case EMessageModule_CampBattle:
        return ProcessCampBattleMsg( pMsg );
        break;
	case EMessageModule_Family:		// 处理家族消息
		return ProcessFamilyMsg( pMsg );
		break;
	//xuda 
	/*case EMessageModule_Wanted:
		return ProcessWantedMsg( pMsg );
		break;*/
	case EMessageModule_QuestEntrust:
		return ProcessQuestEntrustMsg( pMsg );
		break;
	case EMessageModule_GameBattle:
		return ProcessGameBattleMsg( pMsg );
		break;
	case EMessageModule_CSAuth:
		return ProcessCSAuthMsg(pMsg);
		break;
    default:
        break;
    }

    if(MSG_EXIT == dwType)
    {   
        SetOffline();
        return false;
    }

    //如果一个用户有很多。。不需要处理的消息。。那么说明这用户的客户端是有问题的。。
    //错误的消息，增加用户的错误计数，多次后
    //关闭连接
#if 0
    LOG_MESSAGE( CHECKCHEATOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:%u:%s:%d message(%u) status(%d)]",  GetAccountID(), GetAccount(), GetDBCharacterID(), GetCharName(), GetID(), dwType, GetStatus() );
#endif

    return false;
}

void GamePlayer::SendMessageToClient( Msg* pMessage )
{
    GettheServer().SendMsgToSingle( pMessage, this );
}

void GamePlayer::SendErrorToClient( uint16 nErrorCode, int32 nValue )
{
    MsgAckResult msg;
    msg.header.stID = GetID();
    msg.result = nErrorCode;
    msg.value  = nValue;
    GettheServer().SendMsgToSingle( &msg, this );
}

bool GamePlayer::OnGetCharacter( Msg* pMessage )
{
	//printf("13,keylogin:ready geting character:%d\n",HQ_TimeGetTime());
    MsgGetCharacter* pMsg = (MsgGetCharacter*)pMessage;
    if ( pMsg == NULL )
    { return false; }

    SLoginInfoBase* pLoginInfoBase = GettheServer().GetLoginInfo( pMsg->SessionKey );
    if ( NULL == pLoginInfoBase )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "OnGetCharacter SessionKey[-][%s][%d]",/*pMsg->SessionKey, */pMsg->szAccount, pMsg->nAccountID );
        MsgAckResult msg;
        msg.result = ER_SessionKeyOverTime;
		msg.value = pMsg->nAccountID;
        GettheServer().SendMsgToSingle( &msg, this );
        OnExit( NULL , ET_ExceptionKick );
        return false;
    }

//#ifdef _DEBUG
//    _bNeedAntiAddiction = true;
//#else
    _bNeedAntiAddiction = pLoginInfoBase->isWallow == 1 ? true : false;
//#endif

    SetAccountID( pLoginInfoBase->nAccountID );
    SetSessionKey( pMsg->SessionKey );
    theRunTimeData.AddMapAccountID( pLoginInfoBase->nAccountID, GetID() );

    GettheServer().RemoveLoginInfo( pMsg->SessionKey );
	////////////////////////////////////////////////////////
	MsgDelLoginInfo msg1;
	msg1.accountId = pMsg->nAccountID;
	//strncpy_s( msg1.szSessionKey, sizeof(msg1.szSessionKey), pMsg->SessionKey, sizeof(msg1.szSessionKey) - 1 );
	msg1.SessionKey = pMsg->SessionKey;
	GettheServer().SendMsgToSingle( &msg1 ,this);
	////////////////////////////////////////////////////////

    DBMsgQueryAccountChar query; 
    query.header.stID    = GetID();
    query.bQueryAllChars = g_Cfg.dwServerID == CHARACTERSERVERID; // 是否需要全部角色
    query.dwAccountId    = GetAccountID();
    query.dwCharacterId  = pMsg->dwCharacterId;
    query.stWitchSlot    = pMsg->stWitchSlot;
    query.needEnd        = 1;
    GettheDBCon().SendMsg( &query,GetLifeCode() );

    // 同步消息给CenterServer
    GS2CSPlayerSynInServerInfo msg;
    msg.header.stID            = GetID();
    msg.uchCountry             = 0;
    msg.nAccountId             = GetAccountID();
    msg.serverInfo.nServerId   = g_Cfg.dwServerID;
    msg.serverInfo.nServerType = g_Cfg.dwServerID == CHARACTERSERVERID ? ST_CharacterServer : ST_GameServer;
    msg.ucStatus               = GS2CSPlayerSynInServerInfo::ES_InServerLoginStage;
    GettheServer().SendMsgToCenterServer( &msg );

    return false;
}

void GamePlayer::OnDBAckLogin( Msg*pMsg )       // 回答数据库登录
{  
    DBMsg *pDBMsg = (DBMsg*)pMsg;
    if( pDBMsg->ustLifeCode != GetLifeCode() )
    {
        GettheDBCon().OnDBMsgHandlerMiss( pDBMsg );
    }
    else
    {
        //DBMsgAckLogin2 *pDBMsg = ( DBMsgAckLogin2* )pMsg;
        //MsgAckLogin msg;
        //msg.header.stID = GetControl()->GetID();
        //msg.stErrorCode = pDBMsg->stRet;

        //if( MsgAckLogin::ret_succ != pDBMsg->stRet )
        //{
        //    //登录失败        
        //    GettheServer().SendMsgToSingle( &msg, this );
        //    SetStatus( CS_LOGIN );
        //    // 
        //    if ( pDBMsg->stRet == MsgAckLogin::ret_alreadyaloginthisaccount )
        //    {
        //        theGameWorld.KickCharByAccount( pDBMsg->dwAccountID );
        //        GetTheLoginStage().KickCharByAccount( pDBMsg->dwAccountID );
        //    }
        //    return;
        //}

        ////发消息通知客户端。说明已经通过了数据库验证
        //GettheServer().SendMsgToSingle( &msg, this );

        //m_dbinfo.dwAccountID = pDBMsg->dwAccountID;
        //m_dbinfo.stflag = pDBMsg->stflag;

        ////向账号数据库请求当前角色信息
        //DBMsgQuerySelChars query;
        //query.header.stID = GetControl()->GetID();
        //query.dwAccountID = m_dbinfo.dwAccountID;

        //GettheDBCon().SendMsg( &query,GetLifeCode() );

        ////改变状态到。读取角色数据
        //SetStatus(CS_WAITDBRET);
    }
}

void GamePlayer::OnDBAckChar( Msg *pMsg )
{ // 回答角色信息
    //改变状态到。已经通过了数据库验证
    DBMsgAckCharInfo* pDBAckChar =(DBMsgAckCharInfo *)pMsg;
  //  if( pDBAckChar->stWhichSlot < 0 || pDBAckChar->stWhichSlot >= More_iCharPerAccount )
  //  {
  //      //Log( "DBMsgAckCharInfo 消息出错了[%d]", pDBAckChar->stWhichSlot );
		//Log( theXmlString.GetString(eServerLog_DBAkCharInfoError), pDBAckChar->stWhichSlot );
  //      return;
  //  }
	m_dbinfo.pdwCharacterID.push_back(pDBAckChar->dwCharacterID);
	m_dbinfo.pdwCharacterMapId.push_back(pDBAckChar->nMapId);
	m_dbinfo.ustCountryID.push_back(pDBAckChar->baseinfo.aptotic.ucCountry);
	m_dbinfo.pdwSlot.push_back(pDBAckChar->stWhichSlot);

    //m_dbinfo.pdwCharacterID[pDBAckChar->stWhichSlot]    = pDBAckChar->dwCharacterID;
    //m_dbinfo.pdwCharacterMapId[pDBAckChar->stWhichSlot] = pDBAckChar->nMapId;
   // m_dbinfo.ustCountryID[pDBAckChar->stWhichSlot]      = pDBAckChar->baseinfo.aptotic.ucCountry;

    if ( g_Cfg.dwServerID != CHARACTERSERVERID )
    { // 是游戏服务器 只要为了拿数据填充服务器 不要再发给客户端
        return;
    }

    MsgAckChar msgAckChar;
    msgAckChar.dwCharacterID = pDBAckChar->dwCharacterID;
    msgAckChar.header.stID   = pDBAckChar->header.stID;
    msgAckChar.stWhichSlot   = pDBAckChar->stWhichSlot;
    msgAckChar.bIsDel        = pDBAckChar->bIsDel;
    msgAckChar.baseinfo      = pDBAckChar->baseinfo;
    msgAckChar.visual        = pDBAckChar->visual;
    msgAckChar.dwDelTimes    = pDBAckChar->dwDelTimes;

    // 发送对应的角色数据给客户端
    GettheServer().SendMsgToSingle( &msgAckChar, this );
}

void GamePlayer::OnDBAckCharEnd( Msg *pMsg )
{       
    DBMsgEndAckChar *pDBEndAckChar = (DBMsgEndAckChar *)pMsg;

    //改变状态到。读取角色数据
    SetStatus(CS_DBLOGINED);

    MsgEndAckChar ackMsg;
    ackMsg.header.stID = pDBEndAckChar->header.stID;
    GettheServer().SendMsgToSingle( &ackMsg, this );
}

void GamePlayer::OnDBAckCreateChar( Msg *pMsg ) // 回答创建角色
{   
    DBMsgCreateCharAck* pMsgCreateChar = (DBMsgCreateCharAck*)pMsg;

    MsgAckCreateChar msgAckCreateChar;
    msgAckCreateChar.header.stID = GetID();
    msgAckCreateChar.bCreateSucc = pMsgCreateChar->result == ER_Success ? true : false;
	msgAckCreateChar.stWhichSlot = pMsgCreateChar->stWhichSlot;
    GettheServer().SendMsgToSingle( &msgAckCreateChar, this );

    if ( RESULT_SUCCESS( pMsgCreateChar->result ))
    {
        DBMsgQueryAccountChar query;
        query.header.stID    = pMsgCreateChar->header.stID;
        query.bQueryAllChars = 0; // 要固定的角色
        query.dwAccountId    = pMsgCreateChar->accountId;
        query.dwCharacterId  = pMsgCreateChar->dwCharacterId;
        query.needEnd        = 1;
        GettheDBCon().SendMsg( &query, pMsgCreateChar->ustLifeCode);
    }
}

void GamePlayer::OnDBAckDeleteChar( Msg *pMsg ) // 回答删除角色
{       
    DBMsgAckDeleteChar2 *pDBmsg = (DBMsgAckDeleteChar2*)pMsg;
    MsgAckDeleteChar OutMsg;
    OutMsg.header.stID = GetControl()->GetID();
    OutMsg.bDeleteSucc = pDBmsg->bSuccessed ;
    OutMsg.dwDelTimes  = 7 * OneDaySecond   ;
    GettheServer().SendMsgToSingle( &OutMsg, this );        
}

void GamePlayer::OnDBAckCancelDelChar( Msg *pMsg )
{        
    DBMsgAckCancelDelChar *pDBCancel = (DBMsgAckCancelDelChar*)pMsg;
    MsgAckCancelDelChar cancel;
    cancel.header.stID = GetControl()->GetID();
    cancel.bSucc = pDBCancel->bSuccessed;
    cancel.stWhichSlot = pDBCancel->stWhichSlot;
    GettheServer().SendMsgToSingle( &cancel, this );
}

void GamePlayer::OnMsgAckResult( Msg* pMsg )
{
    MsgAckResult* pAckResult = (MsgAckResult*)pMsg; 
    if ( !pAckResult)
        return;

    switch ( pAckResult->result )
    {
    case ER_EnterWorldRequstDataBusy:
    case ER_EnterDatabaseBusy:
    case ER_EnterWorldDbSqlException:
        {   
            MsgAckResult msg;
            msg.header.stID = GetID();
            msg.result = ER_EnterWorldRequstDataBusy;
            GettheServer().SendMsgToSingle( &msg, this );
        }
        break;
    }
}

void GamePlayer::OnDBAckEnterWorld( Msg *pMsg )
{ // Database 回答进入游戏世界
    DBMsgAckEnterWorld* pDBWorld = (DBMsgAckEnterWorld*)pMsg; 

    // 对在线角线进行检查，是否游戏世界中已经存在此角色
    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pDBWorld->dwCharacterID );
    if ( pPlayer != NULL )
    { // 两个都下线
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "OnDBAckEnterWorld 被T下线 CharDbId[%u] szSessionKey[-]", pDBWorld->dwCharacterID/*, GetSessionKey()*/ );
        //Log( "OnDBAckEnterWorld 被T下线" );

        Log( theXmlString.GetString(eServerLog_DBAkEnterWorldBeT) );
	
        pPlayer->OnExit( NULL, ET_BeKick );
    }

    if ( pDBWorld->bRet != ER_Success )
    { // 失败告诉客户端
        MsgAckResult msg;
        msg.header.stID = GetID();
        msg.result      = ER_EnterWorldDbSqlException;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    m_cMoveSerial              = theRand.rand32() % RAND_NUM;
    m_nGMLevel                 = ( (pDBWorld->nGMLevel & GP_PERPETUAL) != 0 ? pDBWorld->nGMLevel : 0 );
    _StorageBag                = pDBWorld->stStorage;      // 参考
    m_dbinfo.dwCharacterID     = pDBWorld->dwCharacterID;  // 人物id

    if ( pDBWorld->ucNeedUseMessageMapInfo == BV_NeedUseMessageMapInfo && pDBWorld->ucNeedTellClientCharInfo == BV_NotNeedTellClientCharInfo )
    { _bFirstEnterWorld = false; } // 切服务器过来的 副本一定要是在本服, 所以直接坐飞机,否则副本是飞不进去的
    else
    { _bFirstEnterWorld = true; }

    // 角色数据初始化
	int NowHp = pDBWorld->charinfo.baseinfo.liveinfo.nHp;
	int NowMp = pDBWorld->charinfo.baseinfo.liveinfo.nMp;
    InitCharacter( pDBWorld->charinfo, pDBWorld->runtimeInfo ); 
	RefreshHeroAttr();//刷新主将属性	
	RefreshMountAttr(true);//刷新坐骑属性
	SetHP( NowHp );
    SetMP( NowMp );	

	//二级密码
	//if (gCharInfoServer.otherdata.xSecondPassword.HavePassword())
	//{
	//	MsgSetSecondPasswordAck MsgPsw;
	//	MsgPsw.uchResult = MsgSetSecondPasswordAck::AlreadyHavePassword;
	//	GettheServer().SendMsgToSingle( &MsgPsw, this );
	//}

    // 登录处理
    ProcessLoginHandle();

    // PK值
    SetPKValue( pDBWorld->nPKValue, PKValueOp_Set, BV_NotSendMessage );
    SetPKMode( pDBWorld->stPKProtectFlag, BV_NotSendMessage );

    // 修正地图 Pos
    if ( pDBWorld->ucNeedUseMessageMapInfo == BV_NeedUseMessageMapInfo  )
    { // 第一次上线，但是数据库中位置不对，被纠正 或者是 切服务器过来
        SetMapID( pDBWorld->nMapId );
        SetTileX( pDBWorld->nTileX );
        SetTileY( pDBWorld->nTileY );
    }

    // 地图位置信息
    DWORD dwMapId = GetMapID();
    int nMapX     = GetTileX();
    int nMapY     = GetTileY();

    // 上线纠正地图
    CheckEnterWorldMapID( pDBWorld, dwMapId, nMapX, nMapY );
    theGameWorld.GetCharPosInWorld( this, dwMapId, nMapX, nMapY );
    CheckPos( &dwMapId, &nMapX , &nMapY, false );           

    // 大地图发生了纠正 添加了一个判断,应为在设置坐标的时候会把float坐标设置为格子坐标的中心,告诉客户端以后就会出现偏差
    if ( dwMapId != GetMapID() || nMapX != GetTileX() || nMapY != GetTileY() )
    {
        if ( dwMapId != GetMapID() )
        { SetFloatZ( WORLD_HEIGHT ); }

        SetMapID(dwMapId);
        SetTileX( (int16)nMapX );
        SetTileY( (int16)nMapY );
    }

    if ( !gCharInfoServer.otherdata.bNewChar )
    { // 一定要直接使用数据库中的坐标值！
        int nX = FloatToTile(pDBWorld->charinfo.otherdata.pos.vPos.x);
        int nY = FloatToTile(pDBWorld->charinfo.otherdata.pos.vPos.y);
        if (nX != nMapX)
        { pDBWorld->charinfo.otherdata.pos.vPos.x = TileToFloat(nMapX); }

        if (nY != nMapY)
        { pDBWorld->charinfo.otherdata.pos.vPos.y = TileToFloat(nMapY); }
    }
	else
	{
		SetHP( GetHPMax() );
		SetMP( GetMPMax() );
	}

    // 初始化查找
    theRunTimeData.AddMapDBID( pDBWorld->dwCharacterID, GetID() );
    theRunTimeData.AddMapNameToID( pDBWorld->charinfo.baseinfo.aptotic.szCharacterName, GetID() );

    // 同步消息给CenterServer
    GS2CSPlayerSynInServerInfo msg;
    msg.header.stID            = GetID();
    msg.uchCountry             = GetCountry();
    msg.nAccountId             = GetAccountID();
    msg.nCharacterDbId         = GetDBCharacterID();
    msg.serverInfo.nServerId   = g_Cfg.dwServerID;
    msg.serverInfo.nServerType = ST_GameServer;
    msg.ucStatus               = ( _bFirstEnterWorld ? GS2CSPlayerSynInServerInfo::ES_FirstInMapStagePlaying : GS2CSPlayerSynInServerInfo::ES_InMapStagePlaying );
    strncpy_s( msg.szCharacterName, GetCharName(), sizeof(msg.szCharacterName) - 1 );
    GettheServer().SendMsgToCenterServer( &msg );

	if(gTransferRuntimeInfo.OnLineTime == 0)
		SetEnterTime(); // 设置上线时间
	SetEnterRealTime();

	//处理玩家的国家方面的数据
	HandlePlayerCountryInfo();//处理玩家上线后国家职位的操作

	SetYuanBaoTotle(pDBWorld->dwAccountYuanBaoTotle);
	SetYuanBaoStates(pDBWorld->dwAccountYuanBaoStates);//设置值

    // 进入游戏世界 后续工作
    if ( !_bFirstEnterWorld )
    { // 切服务器过来的 副本一定要是在本服, 所以直接坐飞机,否则副本是飞不进去的
        // 同步玩家国家 等级信息给GateServer
        Msg_GW2GSyncCharInfo xSyncCharInfo;
        xSyncCharInfo.header.stID  = GetID();
        xSyncCharInfo.uchCountryID = GetCountry();
        xSyncCharInfo.ustLevel     = GetLevel();
        GettheServer().SendMsgToGates( &xSyncCharInfo );

        SetStatus( CS_IDLE );
        FlyToMapReq( GetMapID(), GetFloatX(), GetFloatY(), pDBWorld->fDir );       
    }
    else
    { // 第一次进入游戏世界
        SetStatus( CS_LOADINGMAP );
        CheckAllItemOperate();           // 检查物品是否过期, 是否解锁等...

        MsgAckEnterWorld ackMsg;
        ackMsg.header.stID         = GetID();
        ackMsg.nResult             = pDBWorld->bRet;//  需要修改返回不同的错误
        ackMsg.dwPlayerCharacterID = m_dbinfo.dwCharacterID;			
		ackMsg.dwPlayerDBID        = GetDBCharacterID();
        // 修复属性
        ackMsg.charinfo.baseinfo        = gCharInfoServer.baseinfo;
        ackMsg.charinfo.visual          = gCharInfoServer.visual;
        ackMsg.charinfo.otherdataclient = gCharInfoServer.otherdata;    
        ackMsg.charinfo.ItemBagData     = gCharInfoServer.itemData;
        ackMsg.cMoveSerial              = m_cMoveSerial;

        //设置当前时间
        ackMsg.dwCurrentTime = 0;
        ackMsg.dwStartTime   = theRunTimeData.serverStartTime;

        DWORD dwClientMap = EctypeId2MapId( dwMapId );
        ackMsg.nGameMapId = GetMapID(); // 用于大地图显示队友是否在不同副本里
        ackMsg.charinfo.otherdataclient.pos.dwMapID = dwClientMap;
        ackMsg.charinfo.otherdataclient.pos.stX     = nMapX;
        ackMsg.charinfo.otherdataclient.pos.stY     = nMapY;

        if ( gCharInfoServer.otherdata.bNewChar )
        { // 一定要直接使用数据库中的坐标值！
            ackMsg.charinfo.otherdataclient.pos.vPos.x = GetFloatX();
            ackMsg.charinfo.otherdataclient.pos.vPos.y = GetFloatY();
        }
        else
        {
            ackMsg.charinfo.otherdataclient.pos.vPos = pDBWorld->charinfo.otherdata.pos.vPos;
        }

		ackMsg.dwAccountYuanBaoStates = pDBWorld->dwAccountYuanBaoStates;//第一次上线设置下状态值
		ackMsg.dwAccountYuanBaoTotle = pDBWorld->dwAccountYuanBaoTotle;

		//SetYuanBaoTotle(pDBWorld->dwAccountYuanBaoTotle);
		//SetYuanBaoStates(pDBWorld->dwAccountYuanBaoStates);//设置值

		GettheServer().SendMsgToSingle( &ackMsg, this );

		//LYH日志添加
		//theLogEventService.LogPlayerInOut(GetAccountID(),m_dbinfo.dwCharacterID,GetLevel(),GetCountry(),0,GetIp(),ePlayerLogInfo_login,GetCharName());
		
		//二级密码
		/*if (gCharInfoServer.otherdata.xSecondPassword.HavePassword())
		{
			MsgSetSecondPasswordAck MsgPsw;
			MsgPsw.uchResult = MsgSetSecondPasswordAck::AlreadyHavePassword;
			GettheServer().SendMsgToSingle( &MsgPsw, this );
		}*/
		
		if(!g_Cfg.IsMapRun(GetMapID()))
		{
			//上线后发现地图不在当前GameServer
			FlyToMapReq( GetMapID(), GetFloatX(), GetFloatY(), pDBWorld->fDir );    
		}	

		//设置玩家上线
		GS2CSUpdateGuildMemberOnLineTime msgOnLine;
		msgOnLine.PlayerID = GetDBCharacterID();
		msgOnLine.GuildID = GetGuildID();
		time_t now;
		time(&now);
		msgOnLine.OnLineTime = now;
		GettheServer().SendCenterServerMsg( &msgOnLine );

		gCharInfoServer.otherdata.SetLeaveHourSum();//上线的时设置离线的小时的数量
    }

    ResetCheckMoving();
    SendTipVar();
    SendRealTime();
    UpdateTitleCounter(); // 更新称号和记数的关系
	SendLevelLimitInfo();

	OpenConsignmentMoneyWindow(false);

    // 距上一次离线过了一天
	ProcessLastLoginPassOneDay();


	//处理帮派的申请处理
	HandleGuildSQ();

	//玩家上线 处理为处理的约战
	GameGuild* pSrcGuild = theGameGuildManager.GetGuild(GetGuildID());
	if(_bFirstEnterWorld && pSrcGuild && pSrcGuild->GetMasterID() == GetDBCharacterID())
	{
		//公会存在 并且为会长
		if(theGameCampBattleDataManager.IsExitesNeedWriteData(GetGuildID()))
		{
			GameBattleDefine::GuildCampBattle* pInfo = theGameCampBattleDataManager.GetWriteInfoByDestID(GetGuildID());
			if(pInfo)
			{
				//发送命令道客户端去
				MsgCampBattleNewDataAck msg;
				msg.add = *pInfo;
				strcpy_s(msg.info,sizeof(msg.info)-1,"");
				strcpy_s(msg.srcGuildName,sizeof(msg.srcGuildName)-1,pSrcGuild->GetName());
				SendMessageToClient( &msg );
			}
		}
	}
}

void GamePlayer::ProcessLoginHandle()
{
    if (  RecordTime::CheckRecordTime( gCharInfoServer.extendData.n32TimeVars[ETV32_RewardTime] )  
        && theOnLineRewardConfig.GetRewardType() == OnLineRewardConfig::EConstDefine_RewardType_Daily )
    { 
        if ( GetLevel() >= theOnLineRewardConfig.GetLevelLowLimit() && GetLevel() <= theOnLineRewardConfig.GetLevelUpLimit() )
        { gCharInfoServer.baseinfo.liveinfo.dwRewardItemInfo = 0; }

        RecordTime::SaveRecordTime( gCharInfoServer.extendData.n32TimeVars[ETV32_RewardTime] );
    }

    // 荣誉值上限
    if ( RecordTime::CheckRecordTime( gCharInfoServer.otherdata.nRecordHonourTime ) )
    {
        gCharInfoServer.otherdata.nRecordHonourCount = 0;
        RecordTime::SaveRecordTime( gCharInfoServer.otherdata.nRecordHonourTime );
    }
}

void GamePlayer::ProcessLastLoginPassOneDay()
{
    if ( !IsLastLoginPassOneDay() )
    { return; }

    // 处理成就
    _achieveManager.UpdateTriggerByValueType( EAT_LoginDay , 1, true ); 
}

void GamePlayer::OnExit( Msg* pMsg, unsigned char exitType /*= ET_ExitGame*/)
{
	// 退出都要发
	if ( g_Cfg.dwServerID != CHARACTERSERVERID )
	{ 
		ExitGameServerLog();        // 退出游戏LOG

		//////////////////////////////////////////////////////////////////////////////////////////////////
		// 下线保存前，首先执行下下线脚本
		if ( exitType != ET_SwitchGameServer )
		{
			uint32 dwTime = GetOnLineTime();
			uint32 nMinute = gCharInfoServer.baseinfo.liveinfo.dwOnlineTime + ( dwTime / OneMinuteMicroSecond ); // 总在线时间
			// by cloud 修改 当次 在线时间
			uint32 nCurrentOnLineMinute = (/* gTransferRuntimeInfo.dwOnLineTime + */dwTime ) / OneMinuteMicroSecond; // 本次在线时间 

			//LYH日志添加
			if(!theLogEventService.LogPlayerInOut(GetAccountID(),m_dbinfo.dwCharacterID,GetLevel(),GetCountry(), nCurrentOnLineMinute,GetIp(),"NOMAC",ePlayerLogInfo_logout,GetCharName()))
			{
				Log( theXmlString.GetString(eLog_info_2slk_54), GetIp(), nCurrentOnLineMinute, nMinute );
			}
			GetScriptMgr()->StartupVM( ST_OFFLINE, 0, this );
		}
		ExitSaveAntiAddiction(); 
	}

    switch( GetStatus() )
    {
    case CS_CHECK:     // PlayerChar会默认改变到这个数值等待客户端发送过来验证消息
    case CS_LOGIN:     // 收到登录
    case CS_LOGINTODB: // 将消息转发到数据库
    case CS_WAITDBRET: // 等待从数据库读取Player角色数据
    case CS_DBLOGINED:
        {
            _bInLoginStage = false;
        }
        break;
    default:        // 其他已经在游戏中了
        { 
            PlayerExitGameServer( exitType );
        }
        break;
    }

    // 删除玩家离线
    theRunTimeData.ReleaseObject( GetID() , __FILE__, __LINE__);

    GS2CSPlayerExit msg; 
    msg.header.stID = GetID();
    msg.nAccountId  = GetAccountID();
    msg.dwDBID      = GetDBCharacterID();
    msg.cExitType   = exitType;
    msg.blockTime   = _blockTime;
    //strncpy_s( msg.szSessionKey, sizeof(msg.szSessionKey), GetSessionKey(), sizeof(msg.szSessionKey)-1);
	msg.SessionKey = GetSessionKey();
    GettheServer().SendMsgToCenterServer( &msg );
    _blockTime = 0;
}


void GamePlayer::OnDropItem( Msg*pMsg) 
{       
    const float fDistance = 3.0f;

    MsgDropItem2 *pDrop = (MsgDropItem2*)pMsg;
    MsgAckDropItem2 ackDrop;
    ackDrop.stResut = MsgAckDropItem2::Result_Failed;
    ackDrop.ustPackIndex = pDrop->ustPackIndex;
    // 判断丢弃的距离会不会太远了
    if ( abs( GetFloatX() - pDrop->fX ) > fDistance || abs( GetFloatY() - pDrop->fY ) > fDistance)
        return;

    SCharItem stItem;
    switch ( pDrop->ucItemBagType )
    {
    case BT_NormalItemBag:
        {
            if( !_NormalItemBag.GetItem( pDrop->ustPackIndex, &stItem ) )
                return;            
        }
        break;
    case BT_MaterialBag:
        {
            if( !_MaterialItemBag.GetItem( pDrop->ustPackIndex, &stItem ) )
                return;
        }
        break;
    case BT_TaskBag:
        {
            if( !_TaskItemBag.GetItem( pDrop->ustPackIndex, &stItem ) )
                return;
        }
        break;
    default:
        return;
    };

    if ( stItem.IsBounded()|| stItem.IsLock() )
        return;

    if( const_ustItemMoney == stItem.itembaseinfo.ustItemID )
        return;

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(stItem.itembaseinfo.ustItemID);
    if ( !pItemCommon)
        return;

    if ( pItemCommon->bIsCanDrop == false)
    {
        ackDrop.stResut = MsgAckDropItem2::Result_CanNotDrop;
        GettheServer().SendMsgToSingle( &ackDrop, this );
        return;
    }

    if( theGameWorld.CreateItemNpc( pItemCommon->GetItemName(), GetMapID(), pDrop->fX, pDrop->fY, 0, stItem, -1, 0, false) )
    {
        unsigned short ustCount = stItem.itembaseinfo.ustItemCount;
        char szID[40] = {0};
        Log(theXmlString.GetString(eLog_info_2slk_56),pItemCommon->GetItemName(), BigInt2String(stItem.itembaseinfo.nOnlyInt, szID), ustCount);

        switch ( pDrop->ucItemBagType )
        {
        case BT_NormalItemBag:
            {
                _NormalItemBag.PopItem( pDrop->ustPackIndex, ustCount );         
            }
            break;
        case BT_MaterialBag:
            {
                _MaterialItemBag.PopItem( pDrop->ustPackIndex, ustCount );
            }
            break;
        case BT_TaskBag:
            {
                _TaskItemBag.PopItem( pDrop->ustPackIndex, ustCount );
            }
            break;
        default:
            return;
        };
        ackDrop.stResut = MsgAckDropItem2::Result_Success;
    }
    GettheServer().SendMsgToSingle( &ackDrop, this );
}

void GamePlayer::OnRefreshHotKey( Msg* pMsg )
{       
    MsgRefreshHotkey* pKey = (MsgRefreshHotkey *)pMsg;    
    gCharInfoServer.otherdata.hotkeys = pKey->hotkeys;
}

//释放 持续性的魔法
void GamePlayer::OnReqAttackGround( Msg *pMsg )
{

    MsgReqAttackGround *pAttack = (MsgReqAttackGround *)pMsg;
    SAttackTarget target;
    target.bIsCharTarget = false;

    //这类型的技能应该是没有的 所以用0 level 
    ItemDefine::SItemSkill *pSkill = (ItemDefine::SItemSkill *)GettheItemDetail().GetSkillByID( pAttack->stWhichSkill, 0);
    if( pSkill == NULL )
    { return; }

    TryAttack( &target,pSkill,pAttack->stWhichSkill, 0); 

}

void GamePlayer::OnMoveGoods( Msg* pMsg )
{ // 移动物品    
    MsgMoveGoodsReq* pMoveGoods = (MsgMoveGoodsReq*)pMsg;


	if (pMoveGoods->ustCount == 0)
	{//物品移动0个没意义，-1表示全部
		return;
	}

    SCharItem* pCharItem = NULL;
    switch ( pMoveGoods->ucItemBagType )
    {
    case BT_NormalItemBag:
        pCharItem = _NormalItemBag.GetItemByIndex( pMoveGoods->ustSrcIndex );
        break;
    case BT_MaterialBag:
        pCharItem = _MaterialItemBag.GetItemByIndex( pMoveGoods->ustSrcIndex );
        break;
    case BT_TaskBag:
        pCharItem = _TaskItemBag.GetItemByIndex( pMoveGoods->ustSrcIndex );
        break;
    default:
        break;
    }

    if ( pCharItem == NULL || pCharItem->GetItemGuid() != pMoveGoods->nGuID )
    { return; }

    if ( pMoveGoods->ustDstIndex == ITEM_DISTORY )
    { 
        // 删除物品
        if ( pCharItem->IsLock() )
        { return; }
		// 脚本线程挂起的时候不让删
// 		if ( GetScript() && GetScript()->thread.IsHangup())
// 		{
// 			ShowInfo( false, 271, theXmlString.GetString(eClient_CantUseGood_ByDiffState) );
// 			return;
// 		}
        ItemDefine::SItemCommon* pItemCommonConfig = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
        if( pItemCommonConfig == NULL )
        { return; }

        if ( pItemCommonConfig->bIsCanDestory ) 
        {
            if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_ThrowAway, PasswordDefine::OP_InitAction ) )
            { return;}  // 财产保护下无法丢弃物品

            ItemBag* pItemBag = GetItemBagByBagType( pMoveGoods->ucItemBagType );


			SCharItem * _Item = GetBagItemByGuid(pMoveGoods->nGuID);//LYH日志添加
			if (_Item)
			{
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_Item->GetItemID(),pMoveGoods->ustCount,_Item->GetItemGuid(),
				_Item->GetItemCount()-pMoveGoods->ustCount>=0?_Item->GetItemCount()-pMoveGoods->ustCount:0,eItemLogInfo_ItemConsume_Destroy,
				                              GetCharName(),pItemCommonConfig->GetItemName());
			}
				

            if ( pItemBag->PopItem( pMoveGoods->ustSrcIndex, pMoveGoods->ustCount ) != ierr_Success )
            { return; }

			
            char szID[40] = {0};
            Log(theXmlString.GetString(eLog_info_2slk_61),pItemCommonConfig->GetItemName(), BigInt2String(pMoveGoods->nGuID, szID));
        }
        else
        {
            pMoveGoods->ustSrcIndex = ITEM_DISTORY;
        }

        // 遗忘装备技能
        switch ( pItemCommonConfig->ucItemType )
        {
        case ItemDefine::ITEMTYPE_ARMOUR:
        case ItemDefine::ITEMTYPE_WEAPON:
            {
                ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItemCommonConfig;
                if ( pItemCanEquip->skillId > 0 )
                { ForgetSkill( pItemCanEquip->skillId );}
            }
            break;
        }

        GettheServer().SendMsgToSingle( pMoveGoods, this );
        return;
    }

    SCharItem* pDstPosPointer = NULL;
    SCharItem* pSrcPosPointer = NULL;
    ItemBag* pItemBag = NULL;
    switch ( pMoveGoods->ucItemBagType )
    {
    case BT_NormalItemBag:
        {
            pDstPosPointer = GetNormalBagPointerByIndex( pMoveGoods->ustDstIndex );
            pSrcPosPointer = GetNormalBagPointerByIndex( pMoveGoods->ustSrcIndex );
            pItemBag       = &_NormalItemBag;
        }
        break;
    case BT_MaterialBag:
        {
            pDstPosPointer = GetMaterialBagPointerByIndex( pMoveGoods->ustDstIndex );
            pSrcPosPointer = GetMaterialBagPointerByIndex( pMoveGoods->ustSrcIndex );
            pItemBag       = &_MaterialItemBag;
        }
        break;
    case BT_TaskBag:
        {
            pDstPosPointer = GetTaskBagPointerByIndex( pMoveGoods->ustDstIndex );
            pSrcPosPointer = GetTaskBagPointerByIndex( pMoveGoods->ustSrcIndex );
            pItemBag       = &_TaskItemBag;
        }
        break;
    }

    unsigned short usDstItemId    = 0;    
    unsigned short usDstItemCount = 0;

    unsigned short usSrcItemId    = 0;
    unsigned short usSrcItemCount = 0;

    if ( pDstPosPointer )
    {
        usDstItemId    = pDstPosPointer->itembaseinfo.ustItemID;
        usDstItemCount = pDstPosPointer->itembaseinfo.ustItemCount;
    }

    if ( pSrcPosPointer )
    {
        usSrcItemId    = pSrcPosPointer->itembaseinfo.ustItemID;
        usSrcItemCount = pSrcPosPointer->itembaseinfo.ustItemCount;
    }

    Log(theXmlString.GetString(eLog_info_2slk_158),pMoveGoods->ustDstIndex, usSrcItemId, usDstItemCount, pMoveGoods->ustSrcIndex, usSrcItemId, usSrcItemCount);

    int nResult = ItemBag::MoveItem( pDstPosPointer, (EBagType)pMoveGoods->ucItemBagType, pSrcPosPointer, (EBagType)pMoveGoods->ucItemBagType, pItemBag, pMoveGoods->ustCount );
    switch ( nResult )      // 处理移动的结果
    {
    case ItemBag::ECD_MoveGood_Error:
        {
            pMoveGoods->ulResult = ER_Failed;
            GettheServer().SendMsgToSingle( pMoveGoods, this );
        }
        break;
    case ItemBag::ECD_MoveGood_Split:
        {
            MsgMoveGoodsAck xMoveAck;
            xMoveAck.ustSrcIndex   = pMoveGoods->ustSrcIndex;
            xMoveAck.ustDstIndex   = pMoveGoods->ustDstIndex;
            xMoveAck.ustCount      = pMoveGoods->ustCount;
            xMoveAck.ucItemBagType = pMoveGoods->ucItemBagType;
            xMoveAck.nGuID         = pDstPosPointer->itembaseinfo.nOnlyInt;

            GettheServer().SendMsgToSingle( &xMoveAck, this );
        }
        break;
    default:
        break;
    }
}

void GamePlayer::OnBuyGoods( Msg *pMsg )
{   
    MsgBuyOrSellGoods* pmsgBuyOrSellGoods = (MsgBuyOrSellGoods*)pMsg;
	// 财产保护下无法进行金钱交易，购买
	if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_Bargaining, PasswordDefine::OP_InitAction ) )
	{ return;}  
	SShopItem* pShopItem = NULL;
	NpcBaseEx* pNpcChar = NULL;
	if (!pmsgBuyOrSellGoods->bIsPocketShop)
	{
		// 商人是否在本区块中
		BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_pstShop->nShopNpcId );
		if ( pChar == NULL || !pChar->IsNpc() )
		{ return; }

		pNpcChar = (NpcBaseEx*)pChar;
		if ( pNpcChar == NULL )
		{ return; }

		if ( !IsInMapArea( pNpcChar->GetMapID(), pNpcChar->GetFloatX(), pNpcChar->GetFloatY(), fSellBuyToNpcRange ) )
		{ return; }

		m_pstShop->RefreshPrice();
		pShopItem = m_pstShop->GetItemById( pmsgBuyOrSellGoods->ustItemId );
		if ( pShopItem == NULL )
		{ return; }

		// 没有这么多的量
		if ( pmsgBuyOrSellGoods->ustCount > pShopItem->nCurCount )
		{ pmsgBuyOrSellGoods->ustCount = pShopItem->nCurCount; }
		
		if ( pmsgBuyOrSellGoods->ustCount > pShopItem->nPerCount )
		{ pmsgBuyOrSellGoods->ustCount = pShopItem->nPerCount; }
	}
	else
	{
		//随身商店
		if (!thePocketShopManager.IsLoad())
		{
			thePocketShopManager.LoadConifg(POCKETSHOP_FILEPATH);
		}
		CPocketShopManger::SPocketShop* pBuyItem = thePocketShopManager.GetPocketShopItemByID(pmsgBuyOrSellGoods->ustItemId);
		if (pBuyItem)
		{
			SShopItem tempItem = CPocketShopManger::SPocketShopToSShopItem(pBuyItem);
			pShopItem = &tempItem;
			pShopItem->bIsBound = pBuyItem->bIsBound;
		}
		else
		{
			return;
		}
	}

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pmsgBuyOrSellGoods->ustItemId/*pShopItem->nId*/ );
    if( pItemCommon == NULL )
    { return; }        

    ItemBag* pBuyItemBag = GetItemBagByItemType( pItemCommon->ucItemType );
    if ( pBuyItemBag->GetItemEmptyCount() == 0 )
    { return; }
	
	int nCostValue=0;
	int nCostType = 0;
	if (!pmsgBuyOrSellGoods->bIsPocketShop)
	{
		nCostValue = pShopItem->dwSellPrice * pmsgBuyOrSellGoods->ustCount;
		nCostType  = theNpcShop.GetShopItemCostType( pItemCommon,pShopItem );
	}
	else
	{
		if (pShopItem->nPerCount <= 0)
		{
			pShopItem->nPerCount = 1;
		}
		nCostValue = (pmsgBuyOrSellGoods->ustCount) * (pShopItem->dwBuyPrice/pShopItem->nPerCount);
		nCostType = pShopItem->costType;
	}

	//判断购买物品是否需要打折
	float N = 1;
	/*if(theGameCountryManager.GetStrongCountry() == GetCountryId() && GetCountryId() != CountryDefine::Country_Init && theGameCountryManager.GetStrongCountry() !=CountryDefine::Country_Init && pmsgBuyOrSellGoods->bIsPocketShop)
		N = 0.85;*/
	nCostValue = N * nCostValue;
    switch ( nCostType )
    {
    case ItemDefine::CT_Money:                             // 游戏币
        {
            if ( GetMoney() < nCostValue )
            { 
                SendErrorToClient( ER_BuyGoodsNoMoney );
                return; 
            } 

            OperateMoney( EOT_Sub, nCostValue, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_NPCShop); 
        }
        break;
    case ItemDefine::CT_JiaoZi:                            // 交子
        {
            if( GetJiaoZiMoney() < nCostValue )
            { 
                SendErrorToClient( ER_BuyGoodsNoMoney );
                return; 
            }

            OperateJiaoZi( EOT_Sub, nCostValue, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_NPCShop);
        }
        break;
    case ItemDefine::CT_Reputation:                        // 声望
        {
            if ( GetReputation() < nCostValue )
            { return; }

            OperateReputation( EOT_Sub, nCostValue, __FUNCTION__, __LINE__,ePlayerMoneySourceType_NPCShop );
        }
        break;
    case ItemDefine::CT_Honour:                            // 荣誉
        {
            if ( GetHonour() < nCostValue )
            { return; }

            OperateHonour( EOT_Sub, nCostValue, __FUNCTION__, __LINE__,ePlayerMoneySourceType_NPCShop );
        }
        break;
    case ItemDefine::CT_Exploit:                           // 功勋
        {
            if ( GetExploit() < nCostValue )
            { return; }

            OperateExploit( EOT_Sub, nCostValue, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_NPCShop);
        }
        break;
    case ItemDefine::CT_Item:                              // 用物品买卖
        {
            int nCostCount = pItemCommon->dwCost * pmsgBuyOrSellGoods->ustCount;
            if ( GetItemCount( pItemCommon->costItemID ) < nCostCount )
            { return; }

            RemoveItem( pItemCommon->costItemID, nCostCount );
        }
        break;
    case ItemDefine::CT_GuildOffer:                        // 帮贡
        {
            if ( GetGuildOffer() < nCostValue )
            { return; }

            OperateGuildOffer( GuildDefine::OperateSub, nCostValue );
        }
        break;
    case ItemDefine::CT_GuildMoney:                        // 帮会资金
        {
            if ( m_pGuild == NULL || !m_pGuild->IsMaster( GetDBCharacterID() ) )
            { return; }

            if ( GetGuildMoney() < nCostValue )
            { return; }

            OperateGuildMoney( GuildDefine::OperateSub, nCostValue );
        }
        break;
    case ItemDefine::CT_GuildBuild:                        // 帮会建设度( 经验 )
        {
            if ( m_pGuild == NULL || !m_pGuild->IsMaster( GetDBCharacterID() ) )
            { return; }

            if ( GetGuildExp() < nCostValue )
            { return; }

            OperateGuildExp( GuildDefine::OperateSub, nCostValue );
        }
        break;
    case ItemDefine::CT_MasterValue:                       // 师门声望
        {
            if ( GetMasterValue() < nCostValue )
            { return; }

            OperateMasterValue( EOT_Sub, nCostValue );
        }
        break;
    case ItemDefine::CT_CountryScore:                      // 国战积分
        {
            if ( GetCountryScore() < nCostValue )
            { return; }

            OperateCountryScore( EOT_Sub, nCostValue, __FUNCTION__, __LINE__ );
        }
        break;
    default:
        return;
    }

    // 加入物品
    int nResult = AddItem( pShopItem->nId, pmsgBuyOrSellGoods->ustCount, EIGS_NpcShop, pShopItem->bIsBound );
    if ( nResult != ierr_Success ) 
    { return; }
	if(!pmsgBuyOrSellGoods->bIsPocketShop)
	{
		GetScriptInterface()->Shop( m_pstShop->nShopId, GetID(), pNpcChar->GetID() );
	}
    //////////////////////////////////////////////////////////////////////////
    // 刷新成就
    switch ( pItemCommon->ucItemType )
    {
    case ItemDefine::ITEMTYPE_WEAPON:
        {
            _achieveManager.UpdateTriggerByValueType( EAT_BuyWeapon );
        }
        break;
    case ItemDefine::ITEMTYPE_ARMOUR:
        {
            ItemDefine::SItemCanEquip* pItemCanEquip = static_cast<ItemDefine::SItemCanEquip*> ( pItemCommon );
            if ( (pItemCanEquip->ustEquipType & ItemDefine::equip_Ring) || (pItemCanEquip->ustEquipType & ItemDefine::equip_Bangle) )
            { _achieveManager.UpdateTriggerByValueType( EAT_BuyOrnament ); }
            else
            { _achieveManager.UpdateTriggerByValueType( EAT_BuyArmour   ); }
        }
        break;
    case ItemDefine::ITEMTYPE_RESTORE:
        {
            ItemDefine::SItemRestore* pRestore = static_cast<ItemDefine::SItemRestore*> ( pItemCommon );
            switch ( pRestore->nRestoreType )
            {
            case ItemDefine::EIRT_RestoreMP:
            case ItemDefine::EIRT_RestoreHP:
                _achieveManager.UpdateTriggerByValueType( EAT_BuyRestore );
                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }

    //买走了减去商店物品数量
    //////////////////////////////////////////////////////////////////////////

}

void GamePlayer::OnSellGoods( Msg *pMsg )
{   
    MsgBuyOrSellGoods* pmsgBuyOrSellGoods = (MsgBuyOrSellGoods*)pMsg;

	NpcBaseEx* pNpcChar = NULL;
	if (!pmsgBuyOrSellGoods->bIsPocketShop)
	{
		// 商人是否在本区块中
		BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_pstShop->nShopNpcId );
		if ( pChar == NULL || !pChar->IsNpc() )
		{ return; }

		pNpcChar = (NpcBaseEx*)pChar;
		if ( pNpcChar == NULL )
		{ return; }
		
		if ( !IsInMapArea( pNpcChar->GetMapID(), pNpcChar->GetFloatX(), pNpcChar->GetFloatY(), fSellBuyToNpcRange ) )
		{
			TellClient(theXmlString.GetString(eLog_info_2slk_65), fSellBuyToNpcRange );
			return;
		}
		m_pstShop->RefreshPrice();
	}

    MsgAckBuyOrSellGoods msgAck;
    msgAck.ustResult     = MsgAckBuyOrSellGoods::error_shop_no_this_item;
    msgAck.ustItemId     = pmsgBuyOrSellGoods->ustItemId;
    msgAck.ustPackIndex  = pmsgBuyOrSellGoods->ustPackIndex;
    msgAck.ustCount      = pmsgBuyOrSellGoods->ustCount;
    msgAck.bIsBuy        = pmsgBuyOrSellGoods->bIsBuy;    
    msgAck.ucItemBagType = pmsgBuyOrSellGoods->ucItemBagType;

    SCharItem* pCharItem = NULL;

    switch ( pmsgBuyOrSellGoods->ucItemBagType )
    {
    case BT_NormalItemBag:
        {
            pCharItem = _NormalItemBag.GetItemByIndex( pmsgBuyOrSellGoods->ustPackIndex );
        }
        break;
    case BT_MaterialBag:
        {
            pCharItem = _MaterialItemBag.GetItemByIndex( pmsgBuyOrSellGoods->ustPackIndex );
        }
        break;
    default:
        return;
        break;
    }

    if ( pCharItem == NULL || pCharItem->itembaseinfo.ustItemID != pmsgBuyOrSellGoods->ustItemId || pCharItem->itembaseinfo.nOnlyInt != pmsgBuyOrSellGoods->nGuid )
    {
        TellClient( theXmlString.GetString(eLog_info_2slk_74) );
        return;
    }

    if ( !ProcessSecondPasswordOperate(PasswordDefine::EProtect_SellItem, PasswordDefine::OP_InitAction) )
    { return;}  // 财产保护下无法卖入商店

    if ( pCharItem->IsLock() )
    { return; } // 加了锁不能卖

    if ( pCharItem->itembaseinfo.ustItemCount < pmsgBuyOrSellGoods->ustCount )
    {   
        TellClient( theXmlString.GetString(eLog_info_2slk_75) );
        return;
    }

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if( pItem == NULL || !pItem->bIsCanSellShop )
    { // 是否可买卖
        TellClient( theXmlString.GetString(eLog_info_2slk_77), pItem->GetItemName() );
        return;
    }
	int nCost = 0;

	nCost = theNpcShop.GetPlayerSellNpcItemCost( pItem->ustItemID , pmsgBuyOrSellGoods->ustCount );
	/*if (!pmsgBuyOrSellGoods->bIsPocketShop)
	{
		nCost = theNpcShop.GetPlayerSellNpcItemCost( pItem->ustItemID , pmsgBuyOrSellGoods->ustCount );
	}
	else
	{
		if (!thePocketShopManager.IsLoad())
		{
			thePocketShopManager.LoadConifg(POCKETSHOP_FILEPATH);
		}
		SShopItem tempItem;
		CPocketShopManger::SPocketShop* pSellItem = thePocketShopManager.GetPocketShopItemByID(pmsgBuyOrSellGoods->ustItemId);
		if (pSellItem)
		{
			if (pSellItem->nPerCount <= 0)
			{
				pSellItem->nPerCount = 1;
			}
			tempItem = CPocketShopManger::SPocketShopToSShopItem(pSellItem);
			nCost = (pmsgBuyOrSellGoods->ustCount) * (pSellItem->nBuyPrice/pSellItem->nPerCount)*fSellDiscountRate+1;
		}
		else
		{
			nCost = theNpcShop.GetPlayerSellNpcItemCost( pItem->ustItemID , pmsgBuyOrSellGoods->ustCount );
		}
		
	}*/

    int nSellMoney = 0;
    int nJiaoZi = 0;
    switch ( pItem->costType )
    {
    case ItemDefine::CT_Money:
    case ItemDefine::CT_JiaoZi:
        {
			//需求是卖东西都得的是绑银
			nJiaoZi = nCost;
            //if (pCharItem->IsBounded())
            //{ nJiaoZi = nCost;    }
            //else
            //{ nSellMoney = nCost; }

        }
        break;
    default:
        {// 非金钱购买装备建议玩家去装备回收 
            TellClient(theXmlString.GetString(eClient_AddInfo_2slk_35));
            SendErrorToClient( ER_SellItemReclaim );
            return;
        }
        break;
    }

    // 扣去物品
    int nResult = ierr_Success;
    __int64 nGuid = pCharItem->itembaseinfo.nOnlyInt;
    SCharItem xSellItem = *pCharItem; 
	theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),xSellItem.GetItemID(),
		                              pmsgBuyOrSellGoods->ustCount,xSellItem.GetItemGuid(),
									  pCharItem->GetItemCount()-pmsgBuyOrSellGoods->ustCount>=0?pCharItem->GetItemCount()-pmsgBuyOrSellGoods->ustCount:0,
									  eItemLogInfo_ItemConsume_SellNpc,GetCharName(),pItem->GetItemName());//LYH日志添加
    switch ( pmsgBuyOrSellGoods->ucItemBagType )
    {
    case BT_NormalItemBag:
        {
            nResult = _NormalItemBag.PopItem( pmsgBuyOrSellGoods->ustPackIndex, pmsgBuyOrSellGoods->ustCount );
        }
        break;
    case BT_MaterialBag:
        {
            nResult = _MaterialItemBag.PopItem( pmsgBuyOrSellGoods->ustPackIndex, pmsgBuyOrSellGoods->ustCount );
        }
        break;
    default:
        return;
        break;
    }

    if( nResult == ierr_Success )
    {
        char szID[60] = {0};
		char szName[60] = {0};
		if (!pmsgBuyOrSellGoods->bIsPocketShop)
		{
			memcpy_s(szName,sizeof(szName),pNpcChar->GetCharName(),sizeof(szName));
		}
		else
		{
			strcpy(szName,"pocket shop");
		}
        Log(theXmlString.GetString(eLog_info_2slk_80),pItem->GetItemName(), BigInt2String( nGuid, szID ), pmsgBuyOrSellGoods->ustCount, szName);
        //OperateMoney( EOT_Add, nSellMoney, false, __FUNCTION__, __LINE__ );
        OperateJiaoZi( EOT_Add, nJiaoZi, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_NPCShop );
    }
    // 处理回购物品,目前是一堆一堆的卖掉, 所以不需要处理guid
    xSellItem.itembaseinfo.ustItemCount = pmsgBuyOrSellGoods->ustCount; // 设置正确的卖出数量
    m_xBuyBackItem.AddItem( xSellItem );

    msgAck.ustResult = MsgAckBuyOrSellGoods::error_sucess;

    // 回复消息
    msgAck.dwCurMoney = GetMoney();
    GettheServer().SendMsgToSingle( &msgAck, this );
	if (!pmsgBuyOrSellGoods->bIsPocketShop)
	{
		GetScriptInterface()->Shop( m_pstShop->nShopId, GetID(), pNpcChar->GetID() );
	}
}

void GamePlayer::OnBuyOrSellGoods( Msg *pMsg )
{   
    MsgBuyOrSellGoods* pmsgBuyOrSellGoods = (MsgBuyOrSellGoods*)pMsg;

    if ( pmsgBuyOrSellGoods->ustCount == 0 )
    { return; }

    if ( m_pstShop == NULL && !pmsgBuyOrSellGoods->bIsPocketShop)
    {
        Log(theXmlString.GetString(eLog_info_2slk_63));
        return;
    }

    if ( pmsgBuyOrSellGoods->bIsBuy )
    { // 买
        OnBuyGoods( pmsgBuyOrSellGoods  );
    }    
    else
    { // 卖        
        OnSellGoods( pmsgBuyOrSellGoods );
    }
}


void GamePlayer::OnMsgMapLoaded( Msg* pMsg )
{   
    MsgMapLoaded* pMapLoad = static_cast< MsgMapLoaded* >( pMsg );
    if ( pMapLoad == NULL )
    { return; }
    HelperFunc::CheckStringValid( pMapLoad->szMacAddress, sizeof( pMapLoad->szMacAddress ) );

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( GetMapID() ) );
    if ( pMapData == NULL )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "[%s]OnMsgMapLoaded Error!  MapId=[0x%x]", EctypeId2MapId( GetMapID() ) );
        OnExit( NULL );
        return;
    }

    // 设置当前地图信息
    SetMapData( pMapData ); 

    // 玩家第一次登陆发送相应消息　再过图的时候这些消息不应该发送了
    // 玩家是否是第一次进入这台游戏服务器,否则则只是飞地图
    bool bFirstEnterGameServer = _bFirstEnterGameServer;
    if ( !_bFirstEnterGameServer )  // 不是第一次进入这台游戏服务器
    {
        // 离开老的场景
        if( !theGameWorld.GlobalMessage( GameWorld::ExtMsg_LeaveStage, GetID() ) )
        { // 失败了,退出,从世界中删除
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "ExtMsg_LeaveStage Error! LastMapID = [0x%x] MapId=[0x%x]", GetLastMapID(), GetMapID() );
        }

        // 进入新的场景
        if( !theGameWorld.GlobalMessage( GameWorld::ExtMsg_EnterStage, GetID() ) )
        { // 失败了,退出,从世界中删除 
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "[%s]ExtMsg_EnterStage Error! LastMapID = [0x%x] MapId=[0x%x]", GetCharName(), GetLastMapID(), GetMapID() );
            OnExit( NULL ); // 进入新的场景错误, 从游戏中断开( 否则旧的场景离开了, 新的场景进不去, 该玩家无法Update了 )
            return;
        }

		/**********************************************************************
		date:2012/08/28
		Desc:收回副将
		**********************************************************************/
		if ( !pMapData->CanPet)
		{
			DoPet(-1);
		}
		else
		{
			//判断当前是否有副将  有副将 重新计算副将的BUFF 
			SPetItem* pActivePetItem = _petManager.GetActivePet();
			if(pActivePetItem)
			{
				for (int indexSkill=0; indexSkill<pActivePetItem->skillInfo.GetCurrentSkillCount(); indexSkill++)
				{
					ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pActivePetItem->skillInfo.skills[indexSkill].ustSkillID, pActivePetItem->skillInfo.skills[indexSkill].stSkillLevel );
					if(pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
					{
						//有资质类的被动技能，增加属性到人物身上
						ApplyPetAttrToChar(pPetSkill,false);
					}
				}
				RefreshLieutenantAttr(true);
				int64 ID = pActivePetItem->GetPetGuid();
				int index = _petManager.GetPetIndexByGuid(ID);
				MsgChangePet changeAck;
				changeAck.header.stID = GetID();
				changeAck.ucOpType    = MsgChangePet::EOT_Active;
				changeAck.nIndex      = index;
				changeAck.guid        = ID;
				GettheServer().SendMsgToSingle( &changeAck, this );
			}
		}	
        // 吟唱动作打断
        IntonateInterrupt( ItemDefine::EIT_Map, __FUNCTION__ );
    }
    else    // 第一次进入这台游戏服务器
    {
        FirstEnterGameServer( pMapLoad->szMacAddress );
    }

    // 副本不允许骑马的则下马
	if ( !pMapData->CanRide )
	{ DoRide( -1 ); }


    ProcessMapLoaded( bFirstEnterGameServer );     // 处理加载地图逻辑
    if (m_pRelation && m_pRelation && m_pRelation->GetMapID() != GetMapID() )
    { m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateMapID, GetMapID() ); }
}


void GamePlayer::OnQueryScript( Msg* pMsg )
{
    // 脚本等行中,暂时不接收脚本请求
    if ( m_dwScriptSleep != 0 )
    { goto result;}

    // 交易中不可与NPC对话
    if ( HaveBargaining() )
    { goto result; }

    MsgReqScript* pReq = (MsgReqScript*)pMsg;

    uint32 result = _actionManager.Action( pReq->GetType() );
    if ( RESULT_FAILED( result ) )
    { goto result; }

    EScriptType nScriptType = ST_NPC;   // 脚本执行类型
    uint32 nDestID = pReq->stNpcId;     // 绑定的ID
    uint32 nScriptEnter = 1;            // 脚本入口( 怪物的入口为2, 1是以前的死亡脚本入口 )

    if ( pReq->stNpcId >= 0 )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( pReq->stNpcId );
        if ( pChar == NULL || !pChar->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), 10.f ) )
        { goto result; }

        if ( pChar->IsNpc() )   // npc
        {
            if ( pChar->GetCountry() != CountryDefine::Country_Init && pChar->GetCountry() != GetCountry() )
            { goto result; }
        }
        else if ( pChar->IsMonster() )  // 怪物, 需要判断怪物类型
        {
            MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pChar );
            if ( !pMonster->CanQueryScriptTypeStatus() ||
                pMonster->GetCountry() != CountryDefine::Country_Init && pMonster->GetCountry() != GetCountry() )
            { goto result; }

            nScriptType  = ST_MONSTER;
            nScriptEnter = pMonster->GetMonsterStatusScriptEnter();
            nDestID      = pMonster->GetMonsterID();
        }
    }

    SScript* pScript = GetScript();
    if ( pScript != NULL )
    {
        pScript->nVar = pReq->chSelItem;
        if ( pReq->stNpcId >= 0 )
        { // 继续执行脚本 npc 挂起脚本
            GetScriptMgr()->ExecuteVM( nScriptType, nDestID, this );
        }
        else
        { // 继续执行脚本 其他 挂起脚本
            GetScriptMgr()->ExecuteVM( ST_UNKNOW, -1, this );
        }
    }
    else
    { // 无脚本的时候
        if ( pReq->stNpcId >= 0 )
        {
            GetScriptMgr()->StartupVM( nScriptType, nDestID, this, false, nScriptEnter, pReq->stNpcId );
        }
        else
        { }
    }

    return;

result:
    // CancelCurScript( __FILE__, __FUNCTION__ );
    CancelAllScript();
    return;
}

void GamePlayer::OnScriptCancel( Msg* pMsg )
{
    CancelCurScript( __FILE__, __FUNCTION__ );
}

void GamePlayer::OnMsgChangeTitle(Msg* pMsg)
{
    MsgChangeTitleReq* pChange = static_cast< MsgChangeTitleReq* >( pMsg );
    if ( pChange == NULL || pChange->nTitleID < TitleConfig::Init_ID )
    { return; }

    short nLastTitleID = m_xTitleEx.GetCurrentTitle();

    MsgTellCurrentTitle xTell;
    xTell.header.stID = GetID();
    xTell.nTitleID = pChange->nTitleID;
    GetRelationNameByTitle( xTell.nTitleID, xTell.szTitleTargetName, sizeof( xTell.szTitleTargetName ) );

    if (m_xTitleEx.SetCurrentTitle(pChange->nTitleID))           //设置当前称号成功
    {
        //设置成功,需要重新设置任务属性
        //AddBaseAtrtByTitle(pChange->nTitleID, nLastTitleID);  //策划==> 所有称号属性都累加在玩家身上了, 所以这里不用改变属性
        GettheServer().SendMsgToView(&xTell, GetID(), false);

        if ( m_pRelation->GetTitleID() != GetCurrentTitle() )
        { m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateTitle, GetCurrentTitle() ); }

		TitleConfig::Title* pTitleConfig = NULL;

		if ( nLastTitleID != TitleConfig::Init_ID )
		{
			//删除Buff
			pTitleConfig = theTitleConfig.GetTitleByTitleID( nLastTitleID );
			if ( pTitleConfig )
			{
				if (_buffManager.ClearBuffByBuffIdLevel( pTitleConfig->GetBuffId(), pTitleConfig->GetBuffLevel() ))
					OnBuffStatusChanged( true );
			}
		}

		// Buff
		pTitleConfig = theTitleConfig.GetTitleByTitleID( GetCurrentTitle() );
		if ( pTitleConfig )
		{
			if ( ApplyBufferStatus( pTitleConfig->GetBuffId(), pTitleConfig->GetBuffLevel(), GetID(), SCharBuff::StatusEventType_Other, 0) == GLR_Success )
				OnBuffStatusChanged( true );
		}

		//if ( GetCurrentTitle() == TitleConfig::Init_ID || GetCurrentTitle() != nLastTitleID )
		//{
		//	//删除Buff
		//	pTitleConfig = theTitleConfig.GetTitleByTitleID( nLastTitleID );
		//	if ( pTitleConfig )
		//	{
		//		if (_buffManager.ClearBuffByBuffIdLevel( pTitleConfig->GetBuffId(), pTitleConfig->GetBuffLevel() ))
		//			OnBuffStatusChanged( true );
		//	}
		//}
    }
    else
    {
        //失败了,就发送消息给客户端, 失败
        xTell.nError = MsgTellCurrentTitle::TellNoThisTile;
        GettheServer().SendMsgToSingle(&xTell, this);
    }
}

//请求添加一个称号
void GamePlayer::OnMsgAddTitleReq(Msg* pMsg)
{
    MsgAddTitleReq* pReq = static_cast< MsgAddTitleReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    AddTitle( pReq->nTitleID );
}

//询问被邀请者的返回消息
void GamePlayer::OnAckMsgInquireInvitee(Msg *pMsg)
{
    MsgAckInquireInvitee * pMsgAck = static_cast< MsgAckInquireInvitee* >( pMsg );
    if ( pMsgAck == NULL )
    { return; }

    HelperFunc::CheckStringValid( pMsgAck->name, sizeof( pMsgAck->name ) );

    if ( pMsgAck->bAgree == MsgAckInquireInvitee::result_nonAgree )      //如果不同意
    {
        MsgAckJoinTeam xJoinMsg;
        xJoinMsg.stError = MsgAckJoinTeam::error_targetcancel;
        GamePlayer* pReqPlayer = theRunTimeData.GetGamePlayerByDBID( pMsgAck->dwReqID );
        if ( pReqPlayer != NULL )
        {
            GettheServer().SendMsgToSingle( &xJoinMsg, pReqPlayer );
        }
        else
        {
            GettheServer().SendMsgToSingleRemote( GetDBCharacterID(), &xJoinMsg, pMsgAck->dwReqID, pMsgAck->name );
        }
    }

    if ( IsInLuckReward() )
    { return; }

    //发消息给centerserver,由centerserver来判断是否加入成功
    GS2CSPlayerTeamInviteeAck xTeamInviteeAck;
    xTeamInviteeAck.AssignMode      = pMsgAck->AssignMode;
    xTeamInviteeAck.dwReqID         = pMsgAck->dwReqID;
    xTeamInviteeAck.dwAckID         = GetDBCharacterID();
    xTeamInviteeAck.AssignItemLevel = pMsgAck->AssignItemLevel;
    xTeamInviteeAck.nHp             = GetHP();
    xTeamInviteeAck.nHpMax          = GetCharFightAttr()->hpMax.final;
    xTeamInviteeAck.nMp             = GetMP();
    xTeamInviteeAck.nMpMax          = GetCharFightAttr()->mpMax.final;
    xTeamInviteeAck.stLevel         = GetLevel();
    xTeamInviteeAck.chProfession    = GetProfession();
    xTeamInviteeAck.chSex           = GetSex();
    xTeamInviteeAck.nFaceId         = GetFaceID();
    xTeamInviteeAck.nHairId         = GetHairID();
    xTeamInviteeAck.nHeadPicId      = GetHeadPic();
	xTeamInviteeAck.bAgree          = pMsgAck->bAgree;
    HelperFunc::SafeNCpy( xTeamInviteeAck.szAckName, GetCharName(), sizeof( xTeamInviteeAck.szAckName ) );
    GettheServer().SendMsgToCenterServer( &xTeamInviteeAck );
}

void GamePlayer::OnMsgTeamInvitee( Msg* pMsg )
{
    // 在幸运15关中不能组队
    if ( IsInLuckReward() )
    { return; }

    GettheServer().SendMsgToSingle( pMsg, this );
}

// 队长请求队伍跟随
void GamePlayer::OnReqTeamFollow( Msg* pMsg )
{
	MsgReqTeamFollow* pReq = static_cast< MsgReqTeamFollow* >( pMsg );
	if ( NULL == pReq )
	{ return; }

	GameTeam *pTeam = theGameTeamManager.GetTeam( GetTeamID() );
	if ( NULL == pTeam || !pTeam->IsTeamHeader( GetDBCharacterID() ) )
	{ return; }

	pTeam->SetLastTeamFollowMember( GetDBCharacterID() );

	for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
	{
		unsigned int nMemberID = pTeam->GetMemberIDByIndex(i);
		GamePlayer* pMember = static_cast< GamePlayer* >( theRunTimeData.GetGamePlayerByDBID(nMemberID) );
		if ( pMember && pMember->GetDBCharacterID() != GetDBCharacterID() )
		{
			if ( GetMapID() == pMember->GetMapID() )
			{
				D3DXVECTOR3 pos = GetPos();
				pos.z = 0;
				D3DXVECTOR3 memberPos = pMember->GetPos();
				memberPos.z = 0;
				float fDistance = D3DXVec3Length( &(memberPos - pos) );
				if ( fDistance < 30 )
				{
					GettheServer().SendMsgToSingle( pMsg, pMember );
				}
			}
		}
	}
}

// 回复队伍跟随
void GamePlayer::OnAckTeamFollow( Msg* pMsg )
{
	MsgAckTeamFollow* pAck = static_cast< MsgAckTeamFollow* >( pMsg );
	if ( NULL == pAck )
	{ return; }

	if ( pAck->blAccept == false )
	{ 
		GameTeam *pTeam = theGameTeamManager.GetTeam( GetTeamID() );
		if ( pTeam )
		{
			unsigned long nTeamLeaderID = pTeam->GetTeamHeaderID();
			GamePlayer* pLeader = theRunTimeData.GetGamePlayerByDBID( nTeamLeaderID );
			if ( pLeader )
			{
				MsgTeamMemberAck memberAck;
				HelperFunc::SafeNCpy( memberAck.strMemberName, this->GetCharName(),MAX_NAME_STRING /*sizeof( memberAck.strMemberName )*/ );
				memberAck.nType     = MsgTeamMemberAck::ECD_RefuseFollow;
				GettheServer().SendMsgToSingle( &memberAck, pLeader );
			}

		}

		return; 
	}

	GameTeam *pTeam = theGameTeamManager.GetTeam( GetTeamID() );
	if ( NULL == pTeam || !pTeam->IsInTeam( GetDBCharacterID() ) )
	{ return; }

	unsigned int nFollowMember = pTeam->GetLastTeamFollowMember();
	GamePlayer* pMember = theRunTimeData.GetGamePlayerByDBID(nFollowMember);
	if ( pMember && GetMapID() == pMember->GetMapID() )
	{
		D3DXVECTOR3 pos = GetPos();
		pos.z = 0;
		D3DXVECTOR3 memberPos = pMember->GetPos();
		memberPos.z = 0;
		float fDistance = D3DXVec3Length( &(memberPos - pos) );
		if ( fDistance < 30 * 2 )
		{
			MsgFollowTeamMember msg;
			msg.nMemberID = pMember->GetID();
			GettheServer().SendMsgToSingle( &msg, this );

			GameTeamMember* pMem = pTeam->GetTeamMemberByID( GetDBCharacterID() );
			if ( pMem )
			{ pMem->SetTeamFollowMemberID( nFollowMember ); }
			pTeam->SetLastTeamFollowMember( GetDBCharacterID() );

			// 通知队长有几个队员在队伍跟随
			int count = 0;
			for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
			{
				pMem = pTeam->GetTeamMemberByIndex(i);
				if ( pMem && pMem->GetTeamFollowMemberID() > 0 )
				{ ++count; }
			}
			unsigned long nTeamLeaderID = pTeam->GetTeamHeaderID();
			GamePlayer* pLeader = theRunTimeData.GetGamePlayerByDBID( nTeamLeaderID );
			if ( pLeader )
			{
				MsgMemberCountInTeamFollow msg;
				msg.nMemberCountInTeamFollow = count;
				GettheServer().SendMsgToSingle( &msg, pLeader );

				MsgTeamMemberAck memberAck;
				HelperFunc::SafeNCpy( memberAck.strMemberName, this->GetCharName(), MAX_NAME_STRING/*sizeof( this->GetCharName() )*/ );
				memberAck.nType     = MsgTeamMemberAck::ECD_AgreeFollow;
				GettheServer().SendMsgToSingle( &memberAck, pLeader );
			}
		}
	}
}

// 队长取消队伍跟随
void GamePlayer::OnHeaderCancelTeamFollow( Msg* pMsg )
{
	MsgHeaderCancelTeamFollow* pReq = static_cast< MsgHeaderCancelTeamFollow* >( pMsg );
	if ( NULL == pReq )
	{ return; }

	GameTeam *pTeam = theGameTeamManager.GetTeam( GetTeamID() );
	if ( NULL == pTeam || !pTeam->IsTeamHeader( GetDBCharacterID() ) )
	{ return; }

	for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
	{
		unsigned int nMemberID = pTeam->GetMemberIDByIndex(i);
		GamePlayer* pMember = theRunTimeData.GetGamePlayerByDBID( nMemberID );
		if ( pMember && pMember->GetDBCharacterID() != GetDBCharacterID() )
		{
			GettheServer().SendMsgToSingle( pMsg, pMember );
			
			// 如果玩家处于跟随状态
			GameTeamMember* pMemberFellow = pTeam->GetTeamMemberByID( pMember->GetDBCharacterID() );
			if ( pMemberFellow )
			{
				// 通知队长玩家取消跟随
				MsgTeamMemberAck memberAck;
				HelperFunc::SafeNCpy( memberAck.strMemberName, this->GetCharName(), MAX_NAME_STRING/*sizeof( this->GetCharName() )*/ );
				memberAck.nType     = MsgTeamMemberAck::ECD_LeaderCancelFollow;
				GettheServer().SendMsgToSingle( &memberAck, pMember );

				GameTeamMember* pMember = pTeam->GetTeamMemberByID( nMemberID );
				if ( pMember )
				{ pMember->SetTeamFollowMemberID( 0 ); }
			}
		}
	}

	// 通知队长有几个队员在队伍跟随
	MsgMemberCountInTeamFollow msg;
	msg.nMemberCountInTeamFollow = 0;
	GettheServer().SendMsgToSingle( &msg, this );
}

// 取消队伍跟随
void GamePlayer::OnCancelTeamFollow( Msg* pMsg )
{
	MsgCancelTeamFollow* pReq = static_cast< MsgCancelTeamFollow* >( pMsg );
	if ( NULL == pReq )
	{ return; }

	GameTeam *pTeam = theGameTeamManager.GetTeam( GetTeamID() );
	if ( NULL == pTeam )
	{ return; }

	GameTeamMember* pMember = pTeam->GetTeamMemberByID( GetDBCharacterID() );
	GameTeamMember* pMemberFellow = pTeam->GetTeamMemberByID( pMember->GetTeamFollowMemberID()); //我是跟随状态的时候 才向队长发我取消跟随提示。


	if ( pMember )
	{ pMember->SetTeamFollowMemberID( 0 ); }

	// 通知队长有几个队员在队伍跟随
	int count = 0;
	for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
	{
		pMember = pTeam->GetTeamMemberByIndex(i);
		if ( pMember && pMember->GetTeamFollowMemberID() > 0 )
		{ ++count; }
	}
	unsigned long nTeamLeaderID = pTeam->GetTeamHeaderID();
	GamePlayer* pLeader = theRunTimeData.GetGamePlayerByDBID( nTeamLeaderID );
	if ( pLeader && pMemberFellow)
	{
		MsgMemberCountInTeamFollow msg;
		msg.nMemberCountInTeamFollow = count;
		GettheServer().SendMsgToSingle( &msg, pLeader );

		// 通知队长玩家取消跟随
		MsgTeamMemberAck memberAck;
		HelperFunc::SafeNCpy( memberAck.strMemberName, this->GetCharName(), MAX_NAME_STRING/*sizeof( this->GetCharName() ) */);
		memberAck.nType     = MsgTeamMemberAck::ECD_CancelFollow;
		GettheServer().SendMsgToSingle( &memberAck, pLeader );
	}

	MsgCancelTeamFollow _msg;//重新把这个消息返回到客户端 ，让客户端设置队伍跟随目标位-1
	GettheServer().SendMsgToSingle(&_msg,this);

}

// 创建单人队伍
void GamePlayer::OnCreateTeam( Msg* pMsg )
{
	MsgCreateTeam* pRequest = static_cast< MsgCreateTeam* >( pMsg );
	if ( pRequest == NULL )
	{ return; }

	HelperFunc::CheckStringValid( pRequest->szTeamName, sizeof( pRequest->szTeamName ) );

	// 在幸运15关中不能组队
	if ( IsInLuckReward() )
	{ return; }

	//战场中不可以创建队伍
	/*if(GetFightCamp() != CampDefine::NoneCamp)
	{
		return;
	}*/


	GS2CSCreateTeam req;
	req.dwReqID = GetDBCharacterID();
	strncpy_s( req.szReqName, sizeof( req.szReqName ), GetCharName(), sizeof( req.szReqName ) - 1 );
	req.uchCountry      = GetCountry();
	req.nHp             = GetHP();
	req.nHpMax          = GetCharFightAttr()->hpMax.final;
	req.nMp             = GetMP();
	req.nMpMax          = GetCharFightAttr()->mpMax.final;
	req.chProfession    = GetProfession();
	req.chSex           = GetSex();
	req.stLevel         = GetLevel();
	req.nFaceId         = GetFaceID();
	req.nHairId         = GetHairID();
	req.nHeadPicId      = GetHeadPic();
	req.AssignMode = pRequest->AssignMode;
	req.AssignItemLevel = pRequest->AssignItemLevel;
	GettheServer().SendMsgToCenterServer( &req );
}

//客户端发过来的请求加入队伍的消息
//策划案  组队最多允许五人，包括玩家在内。队伍中第一个主动组队的人为队长，只有队长有组队的权限。
//组队流程为右键点击玩家后出现动态菜单，选择其中的组队项，若该玩家已在组队状态，则无此选项
void GamePlayer::OnRequestTeam( Msg* pMsg )
{ 
    MsgRequestTeam* pRequest = static_cast< MsgRequestTeam* >( pMsg );
    if ( pRequest == NULL )
    { return; }

    HelperFunc::CheckStringValid( pRequest->szNewbieName, sizeof( pRequest->szNewbieName ) );

    if ( GetDBCharacterID() == pRequest->dwNewbieID || strcmp( GetCharName(), pRequest->szNewbieName ) == 0 )
    { return; }     // 如果是自己

    // 在幸运15关中不能组队
    if ( IsInLuckReward() )
    { return; }

	//战场不可以组队
	/*if(GetFightCamp() != CampDefine::NoneCamp)
	{
		return;
	}*/

	GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByName( pRequest->szNewbieName );
	//if(!pPlayer)
	//	return;
	if(pPlayer&&pPlayer->GetOfflineTime() !=0 && pPlayer->GetOfflineTime() == pPlayer->GetOfflineStallEndTime())
	{
		MsgAckJoinTeam xJoinMsg;
        HelperFunc::SafeNCpy( xJoinMsg.name, pRequest->szNewbieName, sizeof( xJoinMsg.name ) );
        xJoinMsg.stError = MsgAckJoinTeam::error_notonline;
		GettheServer().SendMsgToSingle(&xJoinMsg,this);
        return; 
	}

	//判断2个玩家是否可以再当前地图上做跨国组队
	bool result = false;
	if(pPlayer && pPlayer->GetCountryId() != GetCountryId())
	{
		if(pPlayer->GetMapID() == GetMapID() && GetCurZoneID() == pPlayer->GetCurZoneID())
		{
			MapConfig::MapData* pMapData = GetMapData();
			if ( pMapData != NULL )
			{
				int nMapPKMode  = pMapData->CanPk ;
				GameStage *pStage = theGameWorld.GetStageById( GetMapID() );
				if(pStage != NULL)
				{
					GameZone *pZone =  pStage->GetZone(GetCurZoneID());
					if ( pZone != NULL && pZone->GetZonePKMode() != nMapPKMode )
						nMapPKMode = pZone->GetZonePKMode();
				}
				//获取到最后的PK模式后 我们判断当前模式是否可以组队 跨国
				if( MapConfig::MapData::EPKM_UnAllow_PK  == nMapPKMode || MapConfig::MapData::EPKM_None_PK  == nMapPKMode)
					result = true;
			}
		}
	}

    // 由center来做判断
	/*
	 *	Author 2012-11-21 zhuxincong
	 *	DESC: 王帅新定义了消息，用这个
	 */
	//GS2CSPlayerTeamInviteeAck xReq;
	GS2CSPlayerTeamInviteeReq xReq;

	strncpy_s( xReq.szReqName, sizeof( xReq.szReqName ), GetCharName(), sizeof( xReq.szReqName ) - 1 );
    strncpy_s( xReq.szAckName, sizeof( xReq.szAckName ), pRequest->szNewbieName, sizeof( xReq.szAckName ) - 1 );
    xReq.uchCountry      = GetCountry();
    xReq.dwReqID         = GetDBCharacterID();
    xReq.nHp             = GetHP();
    xReq.nHpMax          = GetCharFightAttr()->hpMax.final;
    xReq.nMp             = GetMP();
    xReq.nMpMax          = GetCharFightAttr()->mpMax.final;
    xReq.chProfession    = GetProfession();
    xReq.chSex           = GetSex();
    xReq.stLevel         = GetLevel();
    xReq.nFaceId         = GetFaceID();
    xReq.nHairId         = GetHairID();
    xReq.nHeadPicId      = GetHeadPic();
    xReq.AssignMode      = pRequest->AssignMode;
    xReq.AssignItemLevel = pRequest->AssignItemLevel;
	xReq.countryTeam	 = result;

    GettheServer().SendMsgToCenterServer( &xReq );
}

//客户端发过来的消息请求离开队伍
void GamePlayer::OnExitTeam( Msg* pMsg )
{
    unsigned long dwSessionID = GetTeamID();
    if ( dwSessionID != TeamDefine::NoneSessionID )
    {
        //pMsg != NULL 时, 客户端请求退出队伍
        if ( IsInLuckReward() )     // 在幸运15关不让离队
        { return; }                 // 自己sb要离队 没办法

        GS2CSPlayerRemoveFromTeamReq xRemove;

        xRemove.dwSessionId  = dwSessionID;
        xRemove.dwDataBaseId = GetDBCharacterID();
        xRemove.bKick        = true;
        GettheServer().SendMsgToCenterServer( &xRemove );
    }
}

//客户端发过来的消息要把人丛队伍里面踢出去
void GamePlayer::OnKickFromTeam( Msg* pMsg )
{
    MsgKickFromTeam *pKick = static_cast< MsgKickFromTeam* >( pMsg );
    if ( pKick == NULL )
    { return; }

    if ( pKick->dwWho == InvalidLogicNumber )
    { return; }

    if ( IsInLuckReward() )         // 在幸运15关活动部能T人
    { return; }

    GameTeam *pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if( pTeam == NULL || !pTeam->IsTeamHeader( GetDBCharacterID() ) || !pTeam->IsInTeam( pKick->dwWho ) ) 
    { return; }

    GS2CSPlayerRemoveFromTeamReq xRemove;
    xRemove.dwSessionId  = pTeam->GetID();
    xRemove.dwDataBaseId = pKick->dwWho;
    xRemove.bKick = true;
    GettheServer().SendMsgToCenterServer(&xRemove);
}

// 队长解散队伍
void GamePlayer::OnDisbandTeam( Msg* pMsg )
{
	MsgDisbandTeam* pDisband = static_cast< MsgDisbandTeam* >( pMsg );
	if ( NULL == pDisband )
	{ return; }

	GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
	if ( NULL == pTeam || ! pTeam->IsTeamHeader( GetDBCharacterID() ) )
	{ return; }

	GS2CSPlayerDisbandTeam disbandTeam;
	disbandTeam.dwDataBaseID = GetDBCharacterID();
	disbandTeam.dwTeamSessionID = pTeam->GetID();
	GettheServer().SendMsgToCenterServer(&disbandTeam);
}

void GamePlayer::OnMsgClientTeamInfo( Msg* pMsg )
{
    MsgClientTeamInfo* pInfo = static_cast< MsgClientTeamInfo* >( pMsg );
    if ( pInfo == NULL )
    { return; }

    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL || !pTeam->IsInTeam( GetDBCharacterID() ))
    {   // 没有队伍了,要离队
        SetTeamID( TeamDefine::NoneSessionID );
        if ( pInfo->nCount != 0 )
        {
            MsgExitTeam xExit;
			xExit.header.stID = GetID();
            GettheServer().SendMsgToSingle( &xExit, this );
        }
        return;
    }

    // 遍历客户端队伍的信息
    if ( pInfo->nCount > TeamMaxManipleMember )
    { pInfo->nCount = TeamMaxManipleMember; }
    for ( int i = 0; i < pInfo->nCount; ++i )
    {
        if ( !pTeam->IsInTeam( pInfo->dwTeamMemberID[i] ) )
        {
            MsgDeleteTeamMember xDelete;
            xDelete.dwMemberID = pInfo->dwTeamMemberID[i];
            GettheServer().SendMsgToSingle( &xDelete, this );
        }
    }

    // 遍历服务器的队伍
    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GameTeamMember* pTeamMember = pTeam->GetTeamMemberByIndex( i );
        if ( pTeamMember == NULL || pTeamMember->GetID() == GetDBCharacterID() )
        { continue; }

        bool bFind = false;
        for ( int k = 0; k < pInfo->nCount; ++k )
        {
            if ( pTeamMember->GetID() == pInfo->dwTeamMemberID[k] )
            {
                bFind = true;
                break;
            }         
        }

        if ( !bFind )       // 不在客户端的队伍里
        {
            MsgAddTeamMember xAddTeam;

            HelperFunc::SafeNCpy(xAddTeam.szName, pTeamMember->GetName(), sizeof(xAddTeam.szName) );
            xAddTeam.bIsNewAdd  = true;
            xAddTeam.dwMemberID = pTeamMember->GetID();
            xAddTeam.nHp        = pTeamMember->GetHP();
            xAddTeam.nHpMax     = pTeamMember->GetHPMax();
            xAddTeam.nMp        = pTeamMember->GetMP();
            xAddTeam.nMpMax     = pTeamMember->GetMPMax();
            xAddTeam.stLvl      = pTeamMember->GetLevel();
            xAddTeam.Profession = pTeamMember->GetProfession();
            xAddTeam.shSex      = pTeamMember->GetSex();
            xAddTeam.bHeader    = pTeam->IsTeamHeader( pTeamMember->GetID() );
            xAddTeam.bHeader2   = pTeamMember->GetManipleHeader();
            xAddTeam.dwGroupId  = pTeam->GetID();
            xAddTeam.nFaceId    = pTeamMember->GetFaceID();
            xAddTeam.nHairId    = pTeamMember->GetHairID();
            xAddTeam.nHeadPicId = pTeamMember->GetHeadPicID();

            GettheServer().SendMsgToSingle( &xAddTeam, this );
        }
    }
}


void GamePlayer::OnRelive( Msg *pMsg )
{ 
    MsgReqRelive* pRelive = static_cast< MsgReqRelive* >( pMsg );

    SReliveInfo xReliveInfo;
    switch ( pRelive->byBornPos )
    {
    case eReliveTypeOrigin:
    case eReliveTypeOriginFullHpMP:
        {
            //CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID() ,GetCountryId());
            //if ( pCampBattle != NULL && pCampBattle->GetBattleManager()->IsCountryBattle() )
            //{ 
            //    // 判断是否在国家战场里面( 不能原地复活 )
            //    pRelive->byBornPos = eReliveTypeNearPos;
            //}
            //else
            {
				xReliveInfo.bFreeRelive = IsCanFreeRelive() || (/*pRelive->byAddtion*/m_byReliveBuff & MsgReqRelive::EFreeRelive);
                if ( !xReliveInfo.bFreeRelive )
                {
					const CountryConfig::ReliveSetting& pCountryReliveSetting = theCountryConfig.GetReliveSetting();
					uint8 nFreeReliveLimit =pCountryReliveSetting.GetReilvelSum(GetLevel());
					int Num = ceil(max(0,GetReliveCount() - nFreeReliveLimit-5)*0.6 + 1.0) * theCountryConfig.GetReliveSetting().GetReliveItemCount();
                    if ( ( _NormalItemBag.GetItemCount( /*CItemDetail::ESRI_ReliveItem*/pCountryReliveSetting.GetReliveItemId() ) < Num ) && ( GetJiaoZi()+GetMoney() < pCountryReliveSetting.GetReviceMoney(GetLevel(),gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount)/*g_Cfg.m_nReliveOriginNon*/ ) )
                    {
                        SendErrorToClient( ER_NoMoneyReliveOrigin, g_Cfg.m_nReliveOriginNon );
                        return;
                    }
                }
            }
        }
        break;
    case eReliveTypeSkill:  // 技能复活不是在消息这边处理
        return;
        break;
    default:
        {
            // 10级复活在地图复活点复活
            if ( GetLevel() <= CHAR_RELIVEMAP_LEVEL )
            { pRelive->byBornPos = eReliveTypeBorn; }
        }
        break;
    }
	xReliveInfo.byAddition = pRelive->byAddtion;
    ProcessRelive( pRelive->byBornPos, xReliveInfo );
}

void GamePlayer::OnReqChangeAssignItemLevel( Msg* pMsg )
{
    MsgChangeAssignItemLevelReq* pChange = (MsgChangeAssignItemLevelReq*) pMsg;

    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if(pTeam == NULL)
    { return; }

    if ( !pTeam->IsTeamHeader( GetDBCharacterID() ) )
    { return; }

    if ( pTeam->GetTeamAssignItemLevel() == pChange->chAssignItemLevel )
    { return; }

    GS2CSTeamChangeAssignItemLevelReq xReq;
    xReq.dwTeamSessionID    = pTeam->GetID();
    xReq.dwTeamHeaderID     = GetDBCharacterID();
    xReq.chAssignItemLevlel = pChange->chAssignItemLevel;
    GettheServer().SendMsgToCenterServer(&xReq);
}

//请求改变模式
void GamePlayer::OnReqChangeAssignMode(Msg *pMsg)
{
    MsgReqChangeAssignMode *pChangeReq = (MsgReqChangeAssignMode*)pMsg;

    //先获得该队伍的队伍
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if(pTeam == NULL)
    { return; }

    if ( !pTeam->IsTeamHeader( GetDBCharacterID() ) )
    { return; }

    if ( pTeam->GetTeamAssignModeType() == pChangeReq->AssignMode )
    { return; }

    GS2CSTeamChangeAssignModeReq xReq;
    xReq.dwTeamSessionID = pTeam->GetID();
    xReq.dwTeamHeaderID  = GetDBCharacterID();
    xReq.chAssignMode    = pChangeReq->AssignMode;
    GettheServer().SendMsgToCenterServer(&xReq);
}


void GamePlayer::OnReqChangeAssignMode_Answer(Msg *pMsg)
{
    MsgAckChangeAssignModeAnswer *msg = (MsgAckChangeAssignModeAnswer*)pMsg;
}

void GamePlayer::OnAckMsgAssignTeam(Msg *pMsg)    //返回的组队分配
{
    MsgAckAssginTeam *msg = (MsgAckAssginTeam*)pMsg;
}

void GamePlayer::OnReqUpgradeTeam( Msg *pMsg )    //请求提升队长
{
    MsgReqUpgradeTeam* msgUpgrade = (MsgReqUpgradeTeam*)pMsg;

    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if( pTeam == NULL || !pTeam->IsInTeam( GetDBCharacterID() ) )
    {
        SetTeamID( TeamDefine::NoneSessionID );
        return;
    }

    if ( !pTeam->IsTeamHeader( GetDBCharacterID() ) )
    { return; }    //不是队长       

    if ( !pTeam->IsInTeam( msgUpgrade->dwID ) )
    { return; }   //不在队伍中

    if ( IsInLuckReward() )         // 在幸运15关不让改变队长
    { return; }

	// 如果队伍处于组队跟随状态，则取消组队跟随
	MsgHeaderCancelTeamFollow msgReq;
	OnHeaderCancelTeamFollow( &msgReq );

    //发送给centerserver,有center来判断
    GS2CSPlayerUpgradeTeamReq xUpgradeTeamReq;
    xUpgradeTeamReq.dwDataBaseId = msgUpgrade->dwID;
    xUpgradeTeamReq.dwSessionId  = pTeam->GetID();
    GettheServer().SendMsgToCenterServer(&xUpgradeTeamReq);
}

//////////////////////////////////////////////////////////////////////////
void GamePlayer::ReplaceSpecifiedName( unsigned short ustLevel, Common::_tstring& tstrName )
{    
    switch( ustLevel )
    {
    case 2: // green
        if( tstrName.Find( theXmlString.GetString( ePreItemText_LiangPin ) ) < 2 )
            tstrName.Replace( theXmlString.GetString( ePreItemText_LiangPin ), "" );
        break;
    case 3: // blue
        if( tstrName.Find( theXmlString.GetString( ePreItemText_JingPin ) ) < 2 )
            tstrName.Replace( theXmlString.GetString( ePreItemText_JingPin ), "" );
        break;
    case 4: // purple
        if( tstrName.Find( theXmlString.GetString( ePreItemText_JiPin ) ) < 2 )
            tstrName.Replace( theXmlString.GetString( ePreItemText_JiPin ), "" );
        break;
    case 5: // yellow
        if( tstrName.Find( theXmlString.GetString( ePreItemText_ShenPin ) ) < 2 )
            tstrName.Replace( theXmlString.GetString( ePreItemText_ShenPin ), "" );
        break;
    }
}

int GamePlayer::FormatChatItemData( const MsgChat* pChatMsg, char* szData, int nLength )
{
    if ( pChatMsg == NULL || szData == NULL || nLength == 0 )
    { return 0; }

    for( int i=0; i<pChatMsg->nHyberItemCnt; ++i )
    {
        if (pChatMsg->ehyberType[i] != MsgChat::HYBERTYPE_ITEM)
        { continue; }

        switch ( pChatMsg->type )
        {
        case BT_NormalItemBag:
            {
                SCharItem stItem;
                _NormalItemBag.GetItemByOnlyBigId( pChatMsg->onlyId[i], &stItem );
                if( stItem.itembaseinfo.ustItemID == InvalidLogicNumber )
                { // 这里说明现在处理的是可以叠加的一些物品 没有特殊属性的
                    _NormalItemBag.GetItemByItemID( pChatMsg->itemId[i], &stItem );
                    if( stItem.itembaseinfo.ustItemID == InvalidLogicNumber )
                    {   
                        return 0;
                    }
                }

                if (nLength > ((i+1)*sizeof(SCharItem)))
                {
                    memcpy( szData+i*sizeof(SCharItem), &stItem, sizeof(SCharItem) );
                }
            }
            break;
        case BT_MaterialBag:
            {
                SCharItem stItem;
                _MaterialItemBag.GetItemByOnlyBigId( pChatMsg->onlyId[i], &stItem );
                if( stItem.itembaseinfo.ustItemID == InvalidLogicNumber )
                { // 这里说明现在处理的是可以叠加的一些物品 没有特殊属性的
                    _MaterialItemBag.GetItemByItemID( pChatMsg->itemId[i], &stItem );
                    if( stItem.itembaseinfo.ustItemID == InvalidLogicNumber )
                    {   
                        return 0;
                    }
                }

                if (nLength > ((i+1)*sizeof(SCharItem)))
                {
                    memcpy( szData+i*sizeof(SCharItem), &stItem, sizeof(SCharItem) );
                }
            }
            break;
        case BT_MountBag:
            {
                SMountItem* pMountItem = _mountManager.GetMountByGuid( pChatMsg->onlyId[i] );
                if( pMountItem == NULL )
                { // 这里说明现在处理的是可以叠加的一些物品 没有特殊属性的
                    return 0;
                }

                if (nLength > ((i+1)*sizeof(SMountItem)))
                {
                    memcpy( szData+i*sizeof(SMountItem), pMountItem, sizeof(SMountItem) );
                }
            }
            break;
        case BT_PetBag:
            {
                SPetItem* pPetItem = _petManager.GetPetByGuid( pChatMsg->onlyId[i] );
                if( pPetItem == NULL )
                { // 这里说明现在处理的是可以叠加的一些物品 没有特殊属性的
                    return 0;
                }

                if (nLength > ((i+1)*sizeof(SPetItem)))
                {
                    memcpy( szData+i*sizeof(SPetItem), pPetItem, sizeof(SPetItem) );
                }
            }
            break;
        }
    }

    return pChatMsg->nHyberItemCnt;
}

// 聊天系统
void GamePlayer::OnChatMsg( Msg *pMsg )
{
    MsgChat* pClientChat = static_cast< MsgChat* >( pMsg );
    if ( pClientChat == NULL )
    { return; }

    HelperFunc::CheckStringValid( pClientChat->chatHeader.szToName, sizeof( pClientChat->chatHeader.szToName ) );
    if ( pClientChat->nHyberItemCnt < 0 || pClientChat->nHyberItemCnt > MsgChat::Item_Hyber_Cnt_Max )
    { return; }

    if ( !GameTime::IsPassCurrentTime( m_dwLastChatTime, 1000 ) )      // 时间限制以后要写在配置档里 1秒发一次  
    { return; }

    if ( IsBanSpeak() )                 // 被禁言了
    {
        MsgAckResult xResult;           // 同步时间给客户端 
        xResult.result = ER_BanSpeakTime;
        xResult.value  = ( GetBanSpeakTime() + 59999 ) / 60000;                   // 客户端显示分钟
        GettheServer().SendMsgToSingle( &xResult, this );
        return;
    }

    if( !IsCanChat() )
    { return; }     //禁言功能

    if ( ProcessGMCommand( pClientChat ) )
    { return; } // 处理GM指令

    MsgChat xChat;
    xChat.header.stID = GetID();
    HelperFunc::SafeNCpy( xChat.chatHeader.szToName, pClientChat->chatHeader.szToName, sizeof( xChat.chatHeader.szToName ) );
    HelperFunc::SafeNCpy( xChat.chatHeader.szSpeakName, GetCharName(), sizeof( xChat.chatHeader.szSpeakName ) );
    xChat.chatHeader.stType            = pClientChat->chatHeader.stType;
    xChat.chatHeader.stExpressionId    = pClientChat->chatHeader.stExpressionId;
    xChat.chatHeader.dwSpeakPlayerDBID = GetDBCharacterID();
    xChat.chatHeader.uchSpeakCountry   = GetCountry();
    xChat.chatHeader.uchSpeakerTitle   = m_pCountry->GetPosition( GetDBCharacterID() );
    xChat.chatHeader.dwGuildID         = GetGuildID();
    xChat.type                         = pClientChat->type;
    xChat.bIsRreply                    = pClientChat->bIsRreply;

    // 屏蔽第三放聊天字数
    static char szChatContent[CHAT_STRINGMAX + 1] = { 0 };
    //memset( szChatContent, 0, sizeof( szChatContent ) );
	for(int i =0;i<CHAT_STRINGMAX+1;++i)
	{
		szChatContent[i]=0;
	}
	if(pClientChat->nStringLen<0)
		pClientChat->nStringLen = 0;
    memcpy_s( szChatContent, CHAT_STRINGMAX, pClientChat->szString, min( (size_t)pClientChat->nStringLen, CHAT_STRINGMAX ) );
    HelperFunc::VerifyString( szChatContent );

	unsigned long targetid = 0; //专门为log server用的私聊的目标db id
    std::string strChat;
    strChat = strChat + GetCharName() + theXmlString.GetString(eClient_Chat_Begin) + szChatContent;

    // 格式化道具数据Data
	// 修正客户端发送3个物品链接, 只有一个有效的BUG
	//if ( pClientChat->nHyberItemCnt > 1 )
    //{ pClientChat->nHyberItemCnt = 1; }  // 只给一个

    static char itemHyberMem[dr_MaxChatString] = { 0 };
    memset( itemHyberMem, 0, sizeof( itemHyberMem ) );
    memcpy_s( xChat.ehyberType, sizeof(xChat.ehyberType), pClientChat->ehyberType,  sizeof(pClientChat->ehyberType) );
    memcpy_s( xChat.onlyId,     sizeof(xChat.onlyId),     pClientChat->onlyId,      sizeof(pClientChat->onlyId)     );
    memcpy_s( xChat.itemId,     sizeof(xChat.itemId),    pClientChat->itemId,       sizeof(pClientChat->itemId)     );
    xChat.nHyberItemCnt = FormatChatItemData( pClientChat, itemHyberMem, dr_MaxChatString );
    xChat.SetString( szChatContent, itemHyberMem, xChat.nHyberItemCnt );

    switch ( pClientChat->chatHeader.stType )
    {
    case MsgChat::CHAT_TYPE_NORMAL:     // 普通聊天
        { 
            GettheServer().SendMsgToView( &xChat, GetID(), false );

            strChat = "[Normal] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_GUILD:      // 公会聊天
        { 
            if( m_pGuild == NULL )
            { return; }

            m_pGuild->SendMessageToGuild( &xChat, GuildDefine::InitID, 0, true );

            strChat = "[Guild] " + strChat;
        }
        break;
	case MsgChat::CHAT_TYPE_FAMILY:		// 家族聊天
		{
			if ( m_pFamily == NULL )
			{ return; }

			m_pFamily->SendMessageToFamily( &xChat, FamilyDefine::InitFamilyID, 0, true );
			strChat = "[Family]" + strChat;
		}
		break;
    case MsgChat::CHAT_TYPE_LEAGUE:     // 联盟聊天
        { 
            //if( m_pGuild == NULL || !m_pGuild->HasBundGuild() )
            //{ return; }

            //m_pGuild->SendMessageToGuild( &xChat );
            //m_pGuild->SendChatToBundOrganize( &xChat );

            strChat = "[League] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_TERM:    // 组队聊天
        {
            GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
            if( pTeam == NULL )
            { return; }

            pTeam->SendMessageToTeamClient( &xChat, TeamDefine::ErrorID, TeamDefine::SendToCenter );

            strChat = "[Team] " + strChat;
        }
        break;
	case MsgChat::CHAT_TYPE_COUNTRYOFFICIAL:
		{
			//在国家的官员频道聊天
			//判断玩家是否为官员
			if(gCharInfoServer.baseinfo.liveinfo.uchPosition <= CountryDefine::Position_None || gCharInfoServer.baseinfo.liveinfo.uchPosition >= CountryDefine::Position_Max)
				return;
			//当确定为官员后 可以发生官员聊天信息 到自己国家
            GettheServer().SendMsgToCountry( &xChat, GetCountry(), true );
            strChat = "[CountryOFFICIAL] " + strChat;
		}
		break;
    case MsgChat::CHAT_TYPE_PRIVATE:    // 私聊
    case MsgChat::CHAT_TYPE_MS:         // 短消息
        {
            if ( GetLevel() < g_Cfg.ustPrivateChatLevel )
            { return; }

            GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( xChat.chatHeader.szToName );
            if ( pRelation == NULL || !pRelation->GetOnLine() )
            {
                std::string strContent = xChat.chatHeader.szToName; 
                strContent += theXmlString.GetString( eClient_AddInfo_2slk_149 );
                TellClient( strContent.c_str() );
                return;
            }

            if ( pRelation->GetLevel() < g_Cfg.ustPrivateChatLevel )
            {
                MsgAckResult xResult;
                xResult.result = ER_PrivateChatLevelLimit;
                xResult.value  = g_Cfg.ustPrivateChatLevel;
                SendMessageToClient( &xResult );
                return;
            }

			targetid = pRelation->GetID();
            xChat.chatHeader.dwToPlayerDBID = pRelation->GetID();

            // 在自己黑名单中
            RelationDataToServer* pData = m_pRelation->GetRelationData( pRelation->GetID() );
            if ( pData != NULL && pData->HaveRelation( RelationDefine::BlackList ) )
            { return; }

            // 先发送给自己
            SendMessageToClient( &xChat );

            strChat = "[Private] " + strChat;

            // 添加到自己的临时好友
            if ( pData == NULL )
            { AddRelation( xChat.chatHeader.szToName, RelationDefine::TempFriend ); }

            // 判断对方的关系逻辑
            RelationDataToServer* pTargetData = pRelation->GetRelationData( GetDBCharacterID() );
            if ( pTargetData != NULL && pTargetData->HaveRelation( RelationDefine::BlackList ) )
            { return; }     // 在对方黑名单中

            // 如果对方设置了拒绝接受陌生人短消息
            switch( pRelation->GetMessageRefuse() )
            {
            case RelationDefine::Refuse_AllPlayer:
                return; // 不接收任何消息
                break;
            case RelationDefine::Refuse_Stranger:
                {
                    if ( pTargetData == NULL || !pTargetData->HaveRelation( RelationDefine::Friend ) )
                    { return; } // 自己不是对方的好友, 不发送消息
                }
                break;
            default:
                break;
            }

            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pRelation->GetID() );
            if ( pPlayer != NULL )        // 判断是否在线
            { 
                pPlayer->SendMessageToClient( &xChat );

                if ( pTargetData == NULL )
                { pPlayer->AddRelation( GetCharName(), RelationDefine::TempFriend ); }
            }
            else        // 在其他服务器上
            {
                GS2CSPlayerChatMessage xChatMessage;
                xChatMessage.header.stID = GetID();
                xChatMessage.dwRecvID    = pRelation->GetID();
                memcpy_s( xChatMessage.szBuf, sizeof( xChatMessage.szBuf ), &xChat, xChat.GetLength() );
                GettheServer().SendMsgToCenterServer( &xChatMessage );
            }
        }
        break;
    case  MsgChat::CHAT_TYPE_COUNTRY:       // 国家发言
        {
            if ( !CheckCanCountrySpeak() )
            { return; }

            GettheServer().SendMsgToCountry( &xChat, GetCountry(), true );

            strChat = "[Country] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_HIGHSHOUT:      // 世界喊话
        {
            if ( !IsCanHighShout() )
            { return; }

            GettheServer().SendMsgToWorld( &xChat, true );

            strChat = "[World] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_SHOUT_VIP:            //世界喊话( 使用小喇叭 )
        {
            uint16 itemId = theDataCenter.GetItemSymbol(AN_LIC_small_bugle);
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

           
			//LYH日志添加 小喇叭
			
		SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
		ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
		if(_CharItem && _pItem) 
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
			_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,
			                                 GetCharName(),_pItem->GetItemName());
			

		    RemoveItem( itemId, 1 );
            GettheServer().SendMsgToRegion( &xChat, GetID() );
            strChat = "[ShoutVIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_BATTLE:         // 阵营战场频道
        {

        }
        break;
    case MsgChat::CHAT_TYPE_GM: 
        { // GM求助
            //xChat.SetString( strChat.c_str() );
            //strChat = "[GM] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_SHOUT:
        {
            clock_t tmNow = clock();
            if( tmNow - m_tmChatCoolDownTime < 1000*120 )
            {
                char temp2Client[1024] = {0};
                sprintf_s( temp2Client, sizeof(temp2Client)-1, theXmlString.GetString(eClient_AddInfo_2slk_141), (int)(1000*120 - (tmNow - m_tmChatCoolDownTime))/1000 );
                TellClient( temp2Client );
                return;
            }

            m_tmChatCoolDownTime = tmNow;
            GettheServer().SendMsgToRegion( &xChat, GetID() );

            strChat = "[Shout] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_HIGHSHOUT_VIP:      // 全服公告--其实用于玩家
        { 
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_microphone );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

           

			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_CharItem && _pItem)
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
				_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,
				                                  GetCharName(),_pItem->GetItemName());

			 RemoveItem( itemId, 1 );
            itemId = theDataCenter.GetItemSymbol( AN_LIC_ZZVIP6 );
            if ( InvalidLogicNumber != itemId && _NormalItemBag.IsHaveItemById( itemId ))
            { xChat.chatHeader.speakerPlayerType = MsgChat::EST_ZhiZunHuangGuan; }

            GettheServer().SendMsgToWorld( &xChat, true );
            strChat = "[HighShoutVIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_BULL_VIP:
        {   
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_loudhailer );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }         

			//LYH日志添加 小喇叭
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_CharItem && _pItem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
			_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,
			                                  GetCharName(),_pItem->GetItemName());

			  RemoveItem( itemId, 1 );
            GettheServer().SendMsgToWorld( &xChat );

            strChat = "[BullVIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_PARTICAL1_VIP:
        {
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_bywaynews1 );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

           

			//LYH日志添加 小喇叭
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
            ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_CharItem && _pItem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
			_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,
			                                  GetCharName(),_pItem->GetItemName());

			 RemoveItem( itemId, 1 );
            GettheServer().SendMsgToWorld( &xChat );

            strChat = "[Partical1VIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_PARTICAL2_VIP:
        {
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_bywaynews2 );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

            
			//LYH日志添加 小喇叭

			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_CharItem && _pItem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
			_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,
			                                  GetCharName(),_pItem->GetItemName());

			RemoveItem( itemId, 1 );
            GettheServer().SendMsgToWorld( &xChat );

            strChat = "[Partical2VIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_PARTICAL3_VIP:
        {
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_bywaynews3 );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

            
			//LYH日志添加 小喇叭
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_pItem && _CharItem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,0,
			_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,GetCharName(),_pItem->GetItemName());

			RemoveItem( itemId, 1 );
            GettheServer().SendMsgToWorld( &xChat );

            strChat = "[Partical3VIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_PARTICAL4_VIP:
        {
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_bywaynews4 );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

            RemoveItem( itemId, 1 );
			//LYH日志添加 小喇叭
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_pItem && _CharItem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,0,
				_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,
			                                 GetCharName(),_pItem->GetItemName());

            GettheServer().SendMsgToWorld( &xChat );

            strChat = "[Partical4VIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_PARTICAL5_VIP:
        {
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_bywaynews5 );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

            RemoveItem( itemId, 1 );
			//LYH日志添加 小喇叭
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_pItem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,0,
			_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,GetCharName(),_pItem->GetItemName());

            GettheServer().SendMsgToWorld( &xChat );

            strChat = "[Partical5VIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_PARTICAL6_VIP:
        {
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_bywaynews6 );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

            

			//LYH日志添加 
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_CharItem && _pItem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
			_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,GetCharName(),_pItem->GetItemName());

			RemoveItem( itemId, 1 );
            GettheServer().SendMsgToWorld( &xChat );
            strChat = "[Partical6VIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_PARTICAL7_VIP:
        {
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_bywaynews7 );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

			//LYH日志添加 
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
            ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_CharItem && _pItem)
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
				_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,
				                                  GetCharName(),_pItem->GetItemName());

            RemoveItem( itemId, 1 );
			
            GettheServer().SendMsgToWorld( &xChat );

			

            strChat = "[Partical7VIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_PARTICAL8_VIP:
        {
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_bywaynews8 );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

          

			//LYH日志添加 
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			 ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_CharItem && _pItem)
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
				_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,GetCharName(),_pItem->GetItemName());

			RemoveItem( itemId, 1 );

			GettheServer().SendMsgToWorld( &xChat );

            strChat = "[Partical8VIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_PARTICAL9_VIP:
        {
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_bywaynews9 );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

          

			//LYH日志添加 
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			 ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_CharItem && _pItem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
			_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,GetCharName(),_pItem->GetItemName());

			RemoveItem( itemId, 1 );
			GettheServer().SendMsgToWorld( &xChat );

            strChat = "[Partical9VIP] " + strChat;
        }
        break;
    case MsgChat::CHAT_TYPE_PARTICAL10_VIP:
        {
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_bywaynews10 );
            if ( itemId == InvalidLogicNumber )
            { return; }

            // 这里检测有没有 小喇叭
            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { return; }

          

			//LYH日志添加 
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			 ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_CharItem && _pItem)
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
				_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,GetCharName(),_pItem->GetItemName());

			RemoveItem( itemId, 1 );
			GettheServer().SendMsgToWorld( &xChat );
            strChat = "[Partical10VIP] " + strChat;
        }
        break;
    default:
        {
            strChat = "[Other] " + strChat;
        }
        break;
    }

    m_dwLastChatTime = HQ_TimeGetTime(); // 设置上次发言时间

    if ( g_Cfg.isSendChatToCenter )
    {
		if (targetid > 0 )
		{
			if (!theLogEventService.LogChatInfo(GetAccountID(),GetDBCharacterID(),targetid,szChatContent,pClientChat->chatHeader.stType,GetCharName(),xChat.chatHeader.szToName))
			{
				S2SRecordChatContent msg;
				msg.BuildString( "account[%u:%s:%u:%s]:%s", GetAccountID(), GetAccount(), GetDBCharacterID(), GetCharName(), strChat.c_str() );
				GettheServer().SendMsgToCenterServer( &msg );
			}
		}else
		{

			if (!theLogEventService.LogChatInfo(GetAccountID(),GetDBCharacterID(),targetid,szChatContent,pClientChat->chatHeader.stType,GetCharName(),"NULL"))
			{
				S2SRecordChatContent msg;
				msg.BuildString( "account[%u:%s:%u:%s]:%s", GetAccountID(), GetAccount(), GetDBCharacterID(), GetCharName(), strChat.c_str() );
				GettheServer().SendMsgToCenterServer( &msg );
			}
		}

    }

#if 1
    // GettheServer().SendGMMsg(strChat.c_str(), strChat.length());
#else
    // GettheServer().SendGMMsg( &chat );
#endif
}

bool GamePlayer::OnMsgCleanUpBag( Msg* pMsg )
{
    CHECK_MSGLEN_BOOL( pMsg, MsgCleanUpBag);
    MsgCleanUpBag* pMessage = (MsgCleanUpBag*)pMsg;

    switch ( pMessage->ucItemBagType)
    {
    case BT_NormalItemBag:
        {
            _NormalItemBag.CleanUp();
        }
        break;
    case BT_MaterialBag:
        {
            _MaterialItemBag.CleanUp();
        }
        break;
    case BT_TaskBag:
        {
            _TaskItemBag.CleanUp();
        }
        break;
    case  BT_StorageBag:
        {
            _StorageBag.CleanUp();

            MsgUpdateStorage xUpdate;
            xUpdate.SetCompress();
            xUpdate.stStorage   = _StorageBag;
            xUpdate.nNpcId      = InvalidLogicNumber;
            SendMessageToClient( &xUpdate );
        }
        break;
    default:
        break;
    }
    return true;
}

void GamePlayer::OnS2STransmitResult( Msg* pMsg )
{
    S2STransmitResult* pMessage = (S2STransmitResult* )pMsg;

    switch ( pMessage->ucSessionType )
    {
    case S2STransmit::SESSTONT_Single:
        {
            switch ( pMessage->msgType )
            {
            case MSG_CHAT:
                {
                    switch ( pMessage->nResult )
                    {
                    case S2STransmitResult::ETR_ClientPeerNotExist:
                        {
                            HelperFunc::CheckStringValid( pMessage->targetData.character.szName, sizeof( pMessage->targetData.character.szName ) );

                            std::string strContent = pMessage->targetData.character.szName; 
                            strContent += theXmlString.GetString(eClient_AddInfo_2slk_149);
                            TellClient( strContent.c_str() );
                        }
                        break;
                    case S2STransmitResult::ETR_GamePeerNotExist:
                        break;
                    }
                }
                break;
            }
        }
        break;    
    }
}

void GamePlayer::OnMsgModifyHelpFlag( Msg* pMsg )
{
    MsgModifyHelpFlagC2S* pHFMsg = (MsgModifyHelpFlagC2S*)pMsg;
    gCharInfoServer.baseinfo.liveinfo.dwHelpFlag = pHFMsg->dwHelpFlag;
}

void GamePlayer::OnMsgAskExecuteScript( Msg* pMsg )
{
    MsgAskExecuteScript* msg = (MsgAskExecuteScript*)pMsg;
    GetScriptMgr()->StartupVM( ST_USE_ITEM, msg->scriptId, this );
    //GetScriptMgr()->StartupVM( ST_USE_ITEM, msg->scriptId, this, false, 1, GetID() );   //???
}

// 锁定目标
void GamePlayer::OnMsgLockTarget( Msg* pMsg )
{
    MsgLockTarget* msg = (MsgLockTarget*)pMsg;

    m_nLockID = msg->stWho;
    SetAttackLockCharState( false );
    return;
}

void GamePlayer::OnMsgPetCommand( Msg* pMsg )
{ // 宠物命令消息

    MonsterSummonPet* pSummonPet   = (MonsterSummonPet*)  GetMonsterSummonPet();
    MonsterNurturePet* pNurturePet = (MonsterNurturePet*) _petManager.GetMonsterNurturePet();

    if( pSummonPet == NULL && pNurturePet == NULL )
    { return; }

    MsgPetCommand* petcommand = (MsgPetCommand*)pMsg;
    switch( petcommand->shPetCommandIndex )
    {
    case MsgPetCommand::eAttackTarget:
        {
            //if ( pSummonPet != NULL )
            //{ 
            //    pSummonPet->SetAiStatus( AiDefine::ThinkingAttackTarget );
            //    pSummonPet->ProcessLockTarget( GetLockID() ); 
            //}
			
			//宠物进行攻击 先判断主人和目标之间的攻击状态
			BaseCharacter * pBase = GetLockChar();
			if( CheckAttack::CanNotAttack == this->CheckCanAttackResult(pBase))
				return;
            if ( pNurturePet != NULL )
            { 
                pNurturePet->SetAiStatus( AiDefine::ThinkingAttackTarget );
                pNurturePet->ProcessLockTarget( GetLockID() ); 
            }

        }
        break;
    case MsgPetCommand::eFollowMe:
        {
            //if ( pSummonPet != NULL )
            //{ pSummonPet->SetAiStatus( AiDefine::ThinkingFollowMaster ); }

            if ( pNurturePet != NULL )
            { 
                pNurturePet->SetAiStatus( AiDefine::ThinkingFollowMaster );
                //pNurturePet->SetAIType( ePetDefendAI );
                //pNurturePet->ClearAllEnmity(); 
                //pNurturePet->AskToFollowMaster(); 
            }
        }
        break;
    case MsgPetCommand::eDismiss:
        {
            if ( pSummonPet != NULL )
            { pSummonPet->CharacterMurder(); }

            if ( pNurturePet != NULL )
            { _petManager.LostActivePetMonster();  }
        }
        break;
    case MsgPetCommand::eAttackAI:
        {
            for (int i=0;i<CharSummonPetMaxCount; ++i)
            {
                SetSkillPetAIType( m_xSummonPets[i].petId, ePetAttackAI );
            }
        }
        break;
    case MsgPetCommand::eDefendAI:
        {
            for (int i=0;i<CharSummonPetMaxCount; ++i)
            {
                SetSkillPetAIType( m_xSummonPets[i].petId, ePetDefendAI );
            }
        }
        break;
    case MsgPetCommand::eCommandAI:
        {
            if ( pSummonPet != NULL )
            { pSummonPet->SetAiStatus( AiDefine::ThinkingFollowMaster ); }

            if ( pNurturePet != NULL )
            { pNurturePet->SetAiStatus( AiDefine::ThinkingIdle ); }
        }
        break;
    case MsgPetCommand::eUseSkill:
        {
            if( _petManager._activeSkillBag.IsSkillCoolDownById( petcommand->skillId ) )
            { return; }

            if ( pNurturePet != NULL && petcommand->skillId != 0 && petcommand->skillLevel != 0 )
            {
                pNurturePet->ProcessLockTarget( GetLockID() );
                pNurturePet->SetUseSkill( petcommand->skillId, petcommand->skillLevel );
            }
        }
        break;
    default:
        {
            // ToLog( false );
            return;
        }
    }
}

// 改变坐骑
void GamePlayer::OnMsgChangeDrome( Msg* pMsg )
{
    MsgChangeDrome* pChange = (MsgChangeDrome*)pMsg;

    MsgChangeDrome changedrome;
    changedrome.header.stID = GetID();
    changedrome.ucOpType    = pChange->ucOpType;
    changedrome.nIndex      = pChange->nIndex;
    changedrome.guid        = pChange->guid;
	changedrome.nMountLevel = pChange->nMountLevel;

    SMountItem* pMount = _mountManager.GetMountByIndex( pChange->nIndex );
    if ( pMount == NULL || pMount->baseInfo.guid != pChange->guid )
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountData;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    long nResult = ER_Success;
    switch ( pChange->ucOpType )
    {

	case MsgChangeDrome::EOT_Ride:
		{
				//if ( HaveFighteFlag(eFighting ) )
				//{ // 战斗状态不能出战
				//	MsgAckResult msg;
				//	msg.result = ER_InFightNotActiveMount;
				//	GettheServer().SendMsgToSingle( &msg, this );
				//	return; 
				//}

				if ( IsDead() )
				{ // 死亡状态不能出战
					MsgAckResult msg;
					msg.result = ER_InDeadNotActiveMount;
					GettheServer().SendMsgToSingle( &msg, this );
					return; 
				}

				//清除当前出战战马状态
				//_mountManager._activeSkillBag.SaveSkillColdTime();
				//_mountManager.ClearPassiveSkillAffect();

				// 得到当前要出战的马
				int currentIndex = _mountManager.GetMountIndexByGuid( pChange->guid );
				if ( currentIndex == -1 )
				{ 
					MsgAckResult msg;
					msg.header.stID = GetID();
					msg.result      = ER_NotHaveThisMount;
					GettheServer().SendMsgToSingle( &msg, this );
					return;
				}

				if ( currentIndex != _mountManager.GetActiveMountIndex() )
				{
					currentIndex = _mountManager.GetActiveMountIndex() ;
				}

				GettheServer().SendMsgToSingle( &changedrome, this );
				//_mountManager.UpdateActiveSkillBag();
				//_mountManager.ApplyMountAttributeToChar( false, true );				
				//_mountManager.UpdateMountHP( currentIndex );
				DoRide(-2);//zhuxincong 这里是按F8上马 消息
		}
	break;

    case MsgChangeDrome::EOT_Active:
        {
            //if ( HaveFighteFlag(eFighting ) )
            //{ // 战斗状态不能出战
            //    MsgAckResult msg;
            //    msg.result = ER_InFightNotActiveMount;
            //    GettheServer().SendMsgToSingle( &msg, this );
            //    return; 
            //}

            if ( IsDead() )
            { // 死亡状态不能出战
                MsgAckResult msg;
                msg.result = ER_InDeadNotActiveMount;
                GettheServer().SendMsgToSingle( &msg, this );
                return; 
            }

            //清除当前出战战马状态
            _mountManager._activeSkillBag.SaveSkillColdTime();
            _mountManager.ClearPassiveSkillAffect();

            // 得到当前要出战的马
            int currentIndex = _mountManager.GetMountIndexByGuid( pChange->guid );
            if ( currentIndex == -1 )
            { 
                MsgAckResult msg;
                msg.header.stID = GetID();
                msg.result      = ER_NotHaveThisMount;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            if ( currentIndex != changedrome.nIndex)
            { changedrome.nIndex = currentIndex;}

            nResult = _mountManager.SetMountActiveStatus( currentIndex, true);
            if ( RESULT_FAILED( nResult ))
            {   
                MsgAckResult msg;
                msg.header.stID = GetID();
                msg.result      = nResult;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

			RefreshMountAttr();
			//_mountManager.ApplyMountAttributeToChar( false, true );
			////////////属性操作///////////////////////////////////
			//SMountItem* pCurrentMount = _mountManager.GetActiveMount();
			//if (!pCurrentMount)
			//{
			//	return;
			//}
			//// 清除一级属性
			//ClearAllBaseAttrByPart ( ECustomDataPart_pet );
			//// 清除二级属性
			//ClearAllFightAttrByPart( ECustomDataPart_pet );

			//for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
			//{ 
			//	
			//	gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].pet += pCurrentMount->baseInfo.currentAttribute[i];
			//	gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].petPer += 0;		//直接把坐骑的属性加到人物身上；
			//	gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].UpdateFinal();
			//}
			//// 一级属性作用二级属性
			//ApplyBaseAttrToFightAttr(true,ECustomDataPart_pet);
			///*for (int i=CharAttr_Strength;i<CharAttr_AttributMaxCount;i++)
			//{
			//fightAttrChangeRecord[i] = true;
			//}*/
			//
			//UpdateCharAllAttibute();
			
			//////////////////////////////////////////////////////////////////////////////////////
			SendCharAttibuteToClient();
            GettheServer().SendMsgToSingle( &changedrome, this );
            _mountManager.UpdateActiveSkillBag();
            _mountManager.UpdateMountHP( currentIndex );
            DoRide(-1);//zhuxincong 需求是 点击出战不需要上马  本来是-2
        }
        break;
    case MsgChangeDrome::EOT_UnActive:
        {
            // 得到当前要休息的马
            int currentIndex = _mountManager.GetMountIndexByGuid( pChange->guid );
            SMountItem* pMountItem = _mountManager.GetMountByGuid( pChange->guid );
            if ( currentIndex == -1 || pMountItem == NULL )
            { 
                MsgAckResult msg;
                msg.header.stID = GetID();
                msg.result      = ER_NotHaveThisMount;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            if ( currentIndex != changedrome.nIndex)
            { changedrome.nIndex = currentIndex;}

            bool bActiveMountIndex = _mountManager.GetActiveMountIndex() == currentIndex;
            if ( bActiveMountIndex )
            {
                //清除当前出战战马状态
                _mountManager._activeSkillBag.SaveSkillColdTime();
                _mountManager.ClearPassiveSkillAffect();
            }

            nResult = _mountManager.SetMountActiveStatus( currentIndex, false );

            if ( RESULT_FAILED( nResult )  )
            {   
                MsgAckResult msg;
                msg.header.stID = GetID();
                msg.result      = nResult;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }
			
			//////////属性操作///////////////////////////////////
			SMountItem* pCurrentMount = _mountManager.GetActiveMount();
			// 清除一级属性
			ClearAllBaseAttrByPart ( ECustomDataPart_pet );
			// 清除二级属性
			ClearAllFightAttrByPart( ECustomDataPart_pet );

			// 一级属性作用二级属性
			ApplyBaseAttrToFightAttr(true,ECustomDataPart_pet);
			/*for (int i=CharAttr_Strength;i<CharAttr_AttributMaxCount;i++)
			{
			fightAttrChangeRecord[i] = true;
			}*/
			UpdateCharAllAttibute();
			_mountManager.ApplyMountAttributeToChar( false, true );
			//////////////////////////////////////////////////////////////////////////////////////

			_mountManager.UpdateActiveSkillBag();
			
			SendCharAttibuteToClient();
            GettheServer().SendMsgToSingle( &changedrome, this );
			DoRide(-1);
        }
        break;
    case MsgChangeDrome::EOT_Discard:
        {
            if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_FreeMount, PasswordDefine::OP_InitAction ) )
            { return;} // 财产保护下坐骑无法放生

            bool bActiveIndex = false;
            SMountItem* pMountItem = _mountManager.GetMountByGuid( pChange->guid );
            if ( pMountItem == NULL )
            { 
                MsgAckResult msg;
                msg.header.stID = GetID();
                msg.result      = ER_NotHaveThisMount;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            if ( pMountItem->IsLock() )
            { return; }

            int currentIndex = _mountManager.GetMountIndexByGuid( pChange->guid );
            if ( currentIndex == -1 )
            { 
                MsgAckResult msg;
                msg.header.stID = GetID();
                msg.result      = ER_NotHaveThisMount;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            if ( currentIndex != changedrome.nIndex)
            { changedrome.nIndex = currentIndex;}

            if ( _mountManager.GetActiveMountIndex() == currentIndex)
            {
                //清除当前出战战马状态
                _mountManager.ClearPassiveSkillAffect();
            }

            int nResult = _mountManager.PopMountByBigId( pChange->guid, bActiveIndex );
            if ( nResult == ER_Success)
            {
                GettheServer().SendMsgToSingle( &changedrome, this );
                if ( bActiveIndex )
                { _mountManager.ApplyMountAttributeToChar( false, true ); }
            }
        }
        break;
    }
}

void GamePlayer::OnMsgDisDrome( Msg* pMsg )
{
    //MsgChangeDrome changedrome;
    //changedrome.header.stID = GetID();
    //changedrome.nDromeID    = -1;
    //GettheServer().SendMsgToView( &changedrome, GetID(), true );

    //SetRideMountId(-1);
    //SetActiveBeRiding( false );
    //ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() );
    DebugLog("OnMsgDisDrome DoRide( -1 )");
    DoRide( -1 );
}

void GamePlayer::OnMsgDisDrome1( Msg* pMsg )
{
	//MsgChangeDrome changedrome;
	//changedrome.header.stID = GetID();
	//changedrome.nDromeID    = -1;
	//GettheServer().SendMsgToView( &changedrome, GetID(), true );

	//SetRideMountId(-1);
	//SetActiveBeRiding( false );
	//ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() );
	DebugLog("OnMsgDisDrome DoRide( -2 )");
	DoRide( -2 );
}

void GamePlayer::OnMsgDisHitch( Msg* pMsg )
{
    if( m_bHitchMoving )
    {
        m_bHitchMoving = false;
        m_bHitchBack = false;
        m_nTrafficID = -1;
        m_dwRouteStep = 0;

        //让玩家重新获得控制权
        MsgCanControlMoving msg;
        msg.header.stID = GetID();
        msg.bCanControlMoving = true;
        msg.bIsFlyMoving      = false;
        SetFlyMoving( msg.bIsFlyMoving );
        GettheServer().SendMsgToView( &msg, GetID() );
    }

    //让玩家下坐骑
    if( GetRideId() > InvalidLogicNumber )
    { 
        DebugLog("OnMsgDisHitch DoRide( -1 )");
        DoRide( -1 ); 
    }
}

// 攻击锁定的目标
void GamePlayer::OnMsgAttackLockTarget( Msg* pMsg )
{
    MsgAttackLockTarget* pMessage = (MsgAttackLockTarget*)pMsg;
    if ( pMessage->cAttack != MsgAttackLockTarget::AT_Attack )
    {
        SetAttackLockCharState( false );
        return;
    }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nLockID );
    if ( pChar == NULL )
    {
        SetAttackLockCharState( false );
        ClearLockID();
        return;
    }

    if ( !CheckCanAttackTarget( pChar ) )
    {
        SetAttackLockCharState( false );
        return;
    }

    SetAttackLockCharState( true );

	//停止读条
	if(GetCurActionPlayTime()>0)
		CancelCurScript( __FILE__, __FUNCTION__ );
}

void GamePlayer::OnMsgReqSkillAttack( Msg* pMsg )
{ 
    CHECK_MSGLEN( pMsg, MsgReqSkillAttack);

    MsgReqSkillAttack* pMsgReqSkillAttack = (MsgReqSkillAttack*)pMsg;
    int        nSkillID    = pMsgReqSkillAttack->stSkill;
    int        nSkillLevel = pMsgReqSkillAttack->stSkillLevel;
    GameObjectId TargetID  = pMsgReqSkillAttack->stWho;
    short      sResult     = MsgUseSkillHintMessage::eNormal;
    bool       bIsAction   = pMsgReqSkillAttack->isAction;

    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(pMsgReqSkillAttack->stSkill, pMsgReqSkillAttack->stSkillLevel);
    if ( pSkill == NULL )
    {
        sResult = MsgUseSkillHintMessage::eServerCannotFindSkill;
        goto FailProcess;
    }  

    // 如果是普通攻击 走 TryNormalAttack 流程
    if ( GetNormalAttackSkillId(m_iAttackHand) == nSkillID )
    { 
        SetAttackLockCharState( true );
        return ;
    }

    BaseCharacter* pCharTarget = NULL;
    if ( pSkill->shCastType == ItemDefine::casttype_singletarget )
    { // 单体技能攻击
        pCharTarget = theRunTimeData.GetCharacterByID( pMsgReqSkillAttack->stWho );
        if( !pCharTarget)
        {
            sResult = MsgUseSkillHintMessage::eSkillTargetNotExist;
            goto FailProcess;
        }

        if ( !IsInAttackRange( pCharTarget,pSkill, 1.0f ) )
        {
            sResult = MsgUseSkillHintMessage::eOutAttackRangeHint;
            goto FailProcess;
        }


        if ( pSkill->bMustInBackUse && !IsInTargetBack( pCharTarget, D3DX_PI*0.7f ))
        {            
            sResult = MsgUseSkillHintMessage::eNoInTargetBack;
            goto FailProcess;
        }

        if( pSkill->bNeedTestAngle )
        {
            if( !IsTargetInFront( pCharTarget, pSkill->fAngle ) )
            { // 没有正对着施法目标
                MsgUseSkillHintMessage HintMsg;
                HintMsg.header.stID = GetID();
                HintMsg.shHintId    = MsgUseSkillHintMessage::eUnfaceToTarget;
                GettheServer().SendMsgToSingle( &HintMsg, this );
            }
        }
    }

    if ( !_SkillTaskManager.IsTaskEmpty() )
    {
        sResult = MsgUseSkillHintMessage::eCannotUseSkillWhenTaskIsnotEmpty;
        goto FailProcess;
    }

    if ( GetRideId() > InvalidLogicNumber && !(pSkill->iSkillActionFlags & ItemDefine::CAN_MOUNT_CAST))
    { 
        sResult = MsgUseSkillHintMessage::eCannotUseSkillWhenMounting;
        goto FailProcess;
    }

    if( m_bHitchMoving )
    {
        sResult = MsgUseSkillHintMessage::eCannotUseSkillWhenMounting;
        goto FailProcess;
    }

    if ( IsOpenStall() )
    { // 如果在开店
        sResult = MsgUseSkillHintMessage::eCannotUseSkillWhenPrivateShop;
        goto FailProcess;
    }

    sResult = IsSkillCanUse( pCharTarget, pMsgReqSkillAttack->stSkill, pMsgReqSkillAttack->stSkillLevel );
    if(  sResult != MsgUseSkillHintMessage::eNormal )
    {  // 技能不能用
        goto FailProcess;
    }

    if (IsCollectSkill(pMsgReqSkillAttack->stSkill))
    {// 采集技能
        MonsterBaseEx* pMonsterTarget = static_cast<MonsterBaseEx*> (pCharTarget);
        if (pMonsterTarget == NULL)
        { 
            sResult = MsgUseSkillHintMessage::eSkillTargetNotExist;
            goto FailProcess; 
        }
    }

    // 清除当前动作
    if( GetActionId() != -1 ) 
        SetActionId( -1 );

    if ( !_SkillTaskManager.SetTasks( SSkillTask::STT_SingleSkill, pMsgReqSkillAttack->bCharTarget, pMsgReqSkillAttack->stWho, pMsgReqSkillAttack->vPos, nSkillID, nSkillLevel ) )
    {
        sResult = MsgUseSkillHintMessage::eCannotUseSkillWhenTaskIsnotEmpty;
        goto FailProcess;
    }

    // 是否继续普通攻击
    if (!pSkill->bContinueAtt)
    { SetAttackLockCharState(false); }
    else
    { SetAttackLockCharState(true);  }

    return;

FailProcess:
    MsgUseSkillHintMessage HintMsg;
    HintMsg.header.stID  = GetID();
    HintMsg.shHintId     = sResult;
    HintMsg.TargetID     = TargetID;
    HintMsg.nSkillID     = nSkillID;
    HintMsg.shSkillLevel = nSkillLevel;
    HintMsg.isAction     = bIsAction;
    GettheServer().SendMsgToSingle( &HintMsg, this );
}

void GamePlayer::OnMsgQueryHPInfo( Msg*pMsg )
{ // ToCheck
    MsgQueryHPInfo* pHpinfo = (MsgQueryHPInfo*) pMsg;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(pHpinfo->sNpcID);
    if (NULL == pChar)
    { return; }

    if ( !pChar->IsHaveHpObject())
    { return; }

    MsgAckHPInfo ack;    
    ack.header.stID = pMsg->header.stID;
    ack.sNpcID      = pChar->GetID();
    ack.nHp         = pChar->GetHP();
    ack.nHpMax      = pChar->GetCharFightAttr()->hpMax.final;    
    GettheServer().SendMsgToSingle( &ack, this );
}

//客户端发来的 创建人物 检测同名
void GamePlayer::OnMsgReqCreateCheckName( Msg* pMsg)
{
    MsgReqCreateCheckName* pCreateCheckName = (MsgReqCreateCheckName*)pMsg;
    HelperFunc::CheckStringValid( pCreateCheckName->szName, sizeof( pCreateCheckName->szName ) );

    DBMsgReqCreateCheckName msgDBCreateCheckName;
    msgDBCreateCheckName.header.stID = GetID();
    strncpy_s( msgDBCreateCheckName.szName, sizeof( msgDBCreateCheckName.szName ), pCreateCheckName->szName, sizeof(msgDBCreateCheckName.szName)-1 );
    GettheDBCon().SendMsg( &msgDBCreateCheckName, GetLifeCode() );
}
void GamePlayer::OnMsgNewChangeNameReq( Msg* pMsg)
{
	//检查名称是否符合规定 是否重复
	MsgNewChangeNameReq* pCreateCheckName = (MsgNewChangeNameReq*)pMsg;
    HelperFunc::CheckStringValid( pCreateCheckName->szName, sizeof( pCreateCheckName->szName ) );
	//1.进行基本的过滤
	if(!CChatCheck::getInstance()->CheckStringInLow(pCreateCheckName->szName))
		return;
	//发送到数据库去
	DBMsgChangeNameReq msg;
	msg.PlayerID = pCreateCheckName->PlayerID;
	msg.header.stID = GetID();
	strncpy_s( msg.szName, sizeof( msg.szName ), pCreateCheckName->szName, sizeof(msg.szName)-1 );
    GettheDBCon().SendMsg( &msg, GetLifeCode() );
}
void GamePlayer::OnMsgAckCreateCheckName( Msg* pMsg )
{
    DBMsgAckCreateCheckName* pAck = (DBMsgAckCreateCheckName*)pMsg;

    switch ( pAck->checkType)
    {
    case DBMsgReqCreateCheckName::ECT_CreateChar:
        {
            MsgAckCreateCheckName msg;
            msg.header.stID = GetID();
            msg.bResult = pAck->bResult;
            GettheServer().SendMsgToSingle( &msg, this );
        }
        break;
    case DBMsgReqCreateCheckName::ECT_ChangeName:
        {
            if ( !pAck->bResult )
            {
                MsgAckCreateCheckName msg;
                msg.header.stID = GetID();
                msg.bResult = pAck->bResult;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }
            uint16 itemId = theDataCenter.GetItemSymbol( AN_LIC_ChangeNameItemID );
            if ( itemId == InvalidLogicNumber )
            { return; }

            if ( !_NormalItemBag.IsHaveItemById( itemId ) )
            { 
                MsgAckResult msg;
                msg.result = ER_ChangeNameItemNotExist;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            
			//LYH日志添加 
			SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(itemId);
			ItemDefine::SItemCommon* _pItem = GettheItemDetail().GetItemByID( itemId );
			if(_CharItem && _pItem)
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),itemId,	1,_CharItem->GetItemGuid(),
				_CharItem->GetItemCount()-1 >= 0 ? _CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,
				                                  GetCharName(),_pItem->GetItemName());

			RemoveItem( itemId, 1 );

            SetNewPlayerName( pAck->szName );

            MsgNotifyBeKick msg;
            msg.kickType = MsgNotifyBeKick::EKT_ChangeNameKick;
            GettheServer().SendMsgToSingle( &msg, this );
            CriticalError( __FUNCTION__, __FILE__, __LINE__ ); 
        }
        break;
    }
}
void  GamePlayer::OnDBMsgChangeNameAck(Msg* pMsg)
{
	DBMsgChangeNameAck* pCN = (DBMsgChangeNameAck*)pMsg;
	if(!pCN)
		return;
	MsgNewChangeNameAck msg;
	msg.Result = pCN->Result;
	GettheServer().SendMsgToSingle(&msg, this);
	//玩家修改名称后
	if(pCN->Result)
	{
		//1.发送命令道公会去 修改公会的全部成员的命令
		//发送命令道中央服务器区 修改公会成员名称
		GS2CSGuildMemberChangeName msgCS;
		msgCS.PlayerID = pCN->PlayerID;
		msgCS.GuildID = pCN->GuildID;
		strcpy_s(msgCS.szName,sizeof(msgCS.szName)-1,pCN->szName);
		GettheServer().SendMsgToCenterServer( &msgCS );
		//2.发送关系里的所有在线玩家 告诉他们改名称
		GS2CSRelationUpdateName msgRe;
		msgRe.PlayerID = pCN->PlayerID;
		strcpy_s(msgRe.szName,sizeof(msgRe.szName)-1,pCN->szName);
		GettheServer().SendMsgToCenterServer( &msgRe );
	}
}
void  GamePlayer::OnMsgForSkillExpToSkill(Msg* pMsg)
{
    MsgSkillExpForSkill *pSkillExpForSkill = (MsgSkillExpForSkill *)pMsg;

    SetSkillExpForSkillID(pSkillExpForSkill->stSkillId);

    OnMsgReqSkillIdToClient(pSkillExpForSkill->stSkillId);
}

void  GamePlayer::OnMsgSetTipVar(Msg* pMsg)
{
    MsgAckFirstTip* pAckTip = static_cast< MsgAckFirstTip* >( pMsg );
    if ( pAckTip == NULL )
    { return; }

    SetVar(TIPVARLOW, pAckTip->usFirstInfo<<8>>8);
    SetVar(TIPVARHIGH, pAckTip->usFirstInfo>>8);
}

void  GamePlayer::SendTipVar()
{
    //将Tip所需的变量发至客户端
    //因为玩家变量存的是byte，但获取函数GetVar实际上返回的却是一个int值。所以需要强转一下
    MsgReqFirstTip tipmsg;
    unsigned char bHigh = static_cast<unsigned char>(GetVar(TIPVARHIGH));
    unsigned char bLow = static_cast<unsigned char>(GetVar(TIPVARLOW));

    tipmsg.usFirstInfo = bHigh;
    tipmsg.usFirstInfo <<= 8;
    tipmsg.usFirstInfo += bLow;

    GettheServer().SendMsgToSingle(&tipmsg, this);
}

void GamePlayer::SendLevelLimitInfo()
{
	//if (!theLevelLimitGameManager.IsInit())
	//{
	//	return;
	//}
	MsgFIRSTLIMITINFO flinfo;
	//memcpy(&flinfo.sllinfo,theLevelLimitGameManager.GetLevelLimitInfo(),sizeof(flinfo.sllinfo));
	//memset(&flinfo.sllinfo,0,sizeof(flinfo.sllinfo));
	flinfo.max_lv = g_Cfg.m_nLevelLimt;
	GettheServer().SendMsgToSingle(&flinfo, this);
}

void GamePlayer::SendRealTime()
{ // 这里将服务器计算机时间发向客户端
    MsgSendRealTime msg;
    struct tm* newTime;
    time_t     szClock;
    time( &szClock );
    newTime = localtime( &szClock );
    strncpy_s( msg.strTime, sizeof( msg.strTime ), asctime( newTime ), sizeof(msg.strTime)-1 );

    __time64_t ltime;
    _time64(&ltime);
    msg.time = ltime;
    GettheServer().SendMsgToSingle(&msg, this);
}

void GamePlayer::OnResetItemTime( Msg* pMsg )
{
    MsgReqResetTime *pTime = static_cast< MsgReqResetTime* >( pMsg );
    if ( pTime == NULL )
    { return; }

    MsgRetResetTime RetMsg;
    if( pTime->ustBagType == BT_NormalItemBag )
    {
        SCharItem CharItem;
        if ( !_NormalItemBag.GetItem( pTime->ustIdx, &CharItem ))
            return ;

        ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( CharItem.itembaseinfo.ustItemID );
        if( !pItemDetail )
            return;

        if ( !pItemDetail->IsExclusive() )
            return ;

        if( CharItem.itembaseinfo.n64UseTime == TimeEx::UNDEF_TIME )
            return ;

        if( !CharItem.IsOverdue() )
        {   
            RetMsg.szMsg = MsgRetResetTime::eRet_Faild_NotOverdue;
            GettheServer().SendMsgToSingle( &RetMsg, this );
            return;
        }

        SCharItem* pOpCharItem = _NormalItemBag.GetItemByIndex(pTime->ustIdx);
        if( pOpCharItem )
        {            
            ItemDefine::SItemCommon *pOpItemDetail = NULL;
            pOpItemDetail = GettheItemDetail().GetItemByID( pOpCharItem->itembaseinfo.ustItemID );
            if( !pOpItemDetail )
                return;
            if( pOpItemDetail->nBill < 0 )
            {
                GetErrorLog()->logString(theXmlString.GetString(eLog_info_2slk_128), pItemDetail->GetItemName() );
                ShoppingLog( theXmlString.GetString(eLog_info_2slk_128), pItemDetail->GetItemName() );
                Log( theXmlString.GetString(eLog_info_2slk_128), pItemDetail->GetItemName() );
                return;
            }

            if( /*OperateJinDing( FALSE, pOpItemDetail->nBill ) */
                pOpItemDetail->nBill <= GetJinDing()
                )
            {
                //////////////////////////////////////////////////////////////////////////
                //钱已经减去了
                char szID[60] = { 0 };
                if( ResetItemTime( pOpCharItem ) )
                {
                    OperateJinDing( EOT_Sub, pOpItemDetail->nBill, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ResetItemTime);
                    {
                        TimeEx time( pOpCharItem->itembaseinfo.n64UseTime );
                        GetErrorLog()->logString(
                            theXmlString.GetString(eLog_info_2slk_129),
                            pItemDetail->GetItemName(),
                            BigInt2String(pOpCharItem->itembaseinfo.nOnlyInt, szID), 
                            time.GetYear(),time.GetMonth(), time.GetDay(),
                            time.GetHour(),time.GetMinute()                            
                            );
                        Log(
                            theXmlString.GetString(eLog_info_2slk_129),
                            pItemDetail->GetItemName(),
                            BigInt2String(pOpCharItem->itembaseinfo.nOnlyInt, szID), 
                            time.GetYear(),time.GetMonth(), time.GetDay(),
                            time.GetHour(),time.GetMinute()                            
                            );
                        ShoppingLog(
                            theXmlString.GetString(eLog_info_2slk_129),
                            pItemDetail->GetItemName(),
                            BigInt2String(pOpCharItem->itembaseinfo.nOnlyInt, szID), 
                            time.GetYear(),time.GetMonth(), time.GetDay(),
                            time.GetHour(),time.GetMinute()                            
                            );
                        RetMsg.szMsg = MsgRetResetTime::eRet_Sucess;
                        RetMsg.ustBagType = BT_NormalItemBag;
                        RetMsg.ustIdx = pTime->ustIdx;
                        RetMsg.n64UseTime = pOpCharItem->itembaseinfo.n64UseTime;
                        GettheServer().SendMsgToSingle( &RetMsg, this );

                        return;
                    }
                }
                else
                {
                    Log(
                        theXmlString.GetString(eLog_info_2slk_130),
                        pItemDetail->GetItemName(),
                        BigInt2String(pOpCharItem->itembaseinfo.nOnlyInt, szID) 
                        );
                }


            }
            else
            {
                RetMsg.szMsg = MsgRetResetTime::eRet_Faild_ForNotMoney;
                GettheServer().SendMsgToSingle( &RetMsg, this );
            }
        }
        else
        {
            GetErrorLog()->logString(theXmlString.GetString(eLog_info_2slk_130) );
            return ;
        }

    }
}

void GamePlayer::OnMsgShowHelmet(Msg *pMsg)
{       
    MsgShowHelmet* msg = (MsgShowHelmet*)pMsg;
    gCharInfoServer.visual.ShowHelmet(msg->showHelmet);

    // 发给周围的人
    GettheServer().SendMsgToView( msg, GetID(), true );
}

void GamePlayer::OnMsgShowSignature(Msg *pMsg)
{       
    MsgShowSignature* pMsgShow = (MsgShowSignature*)pMsg;
    gCharInfoServer.visual.ShowSignature(pMsgShow->showSignature);
    HelperFunc::SafeNCpy( pMsgShow->szSignature, m_pRelation->GetSignature()  , RelationDefine::MaxSignLength );

    // 发给周围的人
    GettheServer().SendMsgToView( pMsgShow, GetID(), true );
}

void GamePlayer::OnMsgShowRankTitle( Msg* pMsg )
{
	MsgShowRankTitle* pMsgShow = ( MsgShowRankTitle* )pMsg;
	if ( !pMsgShow )
		return;

	gCharInfoServer.visual.ShowRankTitle(pMsgShow->bshowTitle);
	// 发给周围的人
	GettheServer().SendMsgToView( pMsgShow, GetID(), true );
}

void GamePlayer::OnMsgReqRmbOp( Msg* pMsg )
{
    MsgReqRmbOp* pMessage = (MsgReqRmbOp*)pMsg;
    switch ( pMessage->op )
    {
    case MsgReqRmbOp::ET_ExchangeJinDing:
        {   
            if ( GetLevel() < g_Cfg.exchangeJindingLevelLimit )
            {
                MsgAckResult msg;
                msg.result = ER_ExchangeJinDingLevelLow;
                msg.value  = 40;
                GettheServer().SendMsgToSingle( &msg, this);
                return;
            }

            DBMsgReqAccountBilling msg;
            msg.guid  = GetAccountID();
            msg.op    = DBMsgReqAccountBilling::ET_ExchangeJinDing;
            msg.value = pMessage->value;
            GettheDBCon().SendMsgToDatabaseServer( &msg );
        }
        break;
    case MsgReqRmbOp::ET_QueryPoint:
        {  
            DBMsgReqAccountBilling msg;
            msg.guid  = GetAccountID();
            msg.op    = DBMsgReqAccountBilling::ET_QueryPoint;
            GettheDBCon().SendMsgToDatabaseServer( &msg );
        }
        break;
    }
}

void GamePlayer::OnMsgAckJinDing( Msg* pMsg )
{
    DBMsgAckAccountBilling* pMessage = (DBMsgAckAccountBilling*)pMsg;    
    if ( pMessage->result == ER_Failed )
    {
        MsgAckResult msg;
        msg.header.stID = GetID();
        msg.result      = ER_ChangeJinDingFail;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    switch ( pMessage->op)
    {
    case DBMsgReqAccountBilling::ET_ExchangeJinDing:
        {   
            if ( pMessage->point < pMessage->value )
            {
                MsgAckResult msg;
                msg.header.stID = GetID();
                msg.result      = ER_JinDingOperateFail;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            uint32 jinDing = pMessage->value * theTradeCenter.GetTradeRadio(); 
            Log( theXmlString.GetString( eLog_JinDing_FromDb ) );
            OperateJinDing( EOT_Add, jinDing, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Unkown );
     
            MsgAccountPoint msgPoint;
            msgPoint.header.stID = GetID();
            msgPoint.point       = pMessage->point - pMessage->value;
            GettheServer().SendMsgToSingle( &msgPoint, this );  

            LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_INFO,"[%u:%u:%s] 领取点数[%u] 当前点数[%u] 成功 ", GetAccountID(), GetDBCharacterID(),GetCharName(), pMessage->value, msgPoint.point );

            DBMsgReqAccountBillingOp msg;
            msg.op = DBMsgReqAccountBillingOp::EBOT_Sub;
            msg.guid  = GetAccountID();
            msg.point = pMessage->value; // 扣除的点
            GettheDBCon().SendMsg( &msg, GetLifeCode() );
        }
        break;
    case DBMsgReqAccountBilling::ET_QueryPoint:
        {
            MsgAccountPoint msg;
            msg.header.stID = GetID();
            msg.point       = pMessage->point;
            GettheServer().SendMsgToSingle( &msg, this );     
        }
        break;
    }
}

void GamePlayer::MoveStorageToPack( Msg* pMsg )
{
    MsgMoveStorageItem* pMoveItem = (MsgMoveStorageItem*)pMsg;

    SCharItem* pSrc = _StorageBag.GetItemByIndex( pMoveItem->ustSrcIndex );
    if ( pSrc == NULL || pSrc->itembaseinfo.nOnlyInt != pMoveItem->nGuid )
    { return; }

    switch ( pMoveItem->ucItemBagType )
    {
    case BT_NormalItemBag:
        {
            if( _NormalItemBag.IsHaveItem( pMoveItem->ustDstIndex ))
            { return; }
        }
        break;
    case BT_MaterialBag:
        {   
            if( _MaterialItemBag.IsHaveItem( pMoveItem->ustDstIndex ))
            { return; }
        }
        break;
    default:
        return;
        break;
    }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pSrc->itembaseinfo.ustItemID );
    if ( pItemCommon == NULL )
    { return; }

    if ( pItemCommon->IsExclusive() )
    { pMoveItem->ustCount = 1; }        // 独占的话只能取一个出来

    unsigned short ustCount = pMoveItem->ustCount;
    if ( ustCount > pSrc->itembaseinfo.ustItemCount || ustCount == 0 )
    { ustCount = pSrc->itembaseinfo.ustItemCount; }

    SCharItem stPackItem;
    stPackItem = *pSrc;            
    stPackItem.itembaseinfo.ustItemCount = ustCount;

    unsigned short ustCountTemp = pSrc->itembaseinfo.ustItemCount; // 清除仓库里的物品
    int nCountLast = ustCountTemp - ustCount;
    if (nCountLast > 0)
    {
        stPackItem.itembaseinfo.nOnlyInt = _NormalItemBag.GetNewItemID();
    }

    int nResult = ierr_Success; 
    switch ( pMoveItem->ucItemBagType )
    {
    case BT_MaterialBag:
        nResult = _MaterialItemBag.PushItem( stPackItem, ustCount, pMoveItem->ustDstIndex );
        break;
    default:
        nResult = _NormalItemBag.PushItem( stPackItem, ustCount, pMoveItem->ustDstIndex );
        break;
    }

    char szID[40] = {0};
    if ( nResult == ierr_Success )
    {
        pSrc->itembaseinfo.ustItemCount -= ustCount;
        if( pSrc->itembaseinfo.ustItemCount == 0 )
        {
            pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
            pSrc->itembaseinfo.nOnlyInt  = 0;
        }

        Log(theXmlString.GetString(eLog_info_2slk_161),BigInt2String(stPackItem.itembaseinfo.nOnlyInt, szID), stPackItem.itembaseinfo.ustItemID, ustCount);
    }

    memset( szID, 0, sizeof( szID ) );
    Log(theXmlString.GetString(eLog_info_2slk_90),pItemCommon->GetItemName(), BigInt2String(stPackItem.itembaseinfo.nOnlyInt, szID),stPackItem.itembaseinfo.ustItemCount/*, pMoveItem->ustSrcIndex, pMoveItem->ustDstIndex*/ );//lyh-- 后两个多余

    // 同步guid 给客户端
    MsgMoveStorageItemAck xAck;
    xAck.ucItemBagType = pMoveItem->ucItemBagType;
    xAck.ustItemIndex  = pMoveItem->ustDstIndex;
    xAck.ustItemID     = stPackItem.itembaseinfo.ustItemID;
    xAck.nGuid         = stPackItem.itembaseinfo.nOnlyInt;
    GettheServer().SendMsgToSingle( &xAck, this );

}

void GamePlayer::MovePackToStorage( Msg* pMsg )
{
    MsgMoveStorageItem* pMoveItem = (MsgMoveStorageItem*)pMsg;

    if ( pMoveItem->ustDstIndex > GetStorageItemGrid() )
    { return; }

    SCharItem* pStorageItem = _StorageBag.GetItemByIndex( pMoveItem->ustDstIndex );
    if ( pStorageItem != NULL )
    { return; }

    SCharItem stPackItem;
    switch ( pMoveItem->ucItemBagType )
    {
    case BT_NormalItemBag:
        if( !_NormalItemBag.GetItem( pMoveItem->ustSrcIndex, &stPackItem ) )
            return;
        break;
    case BT_MaterialBag:
        if( !_MaterialItemBag.GetItem( pMoveItem->ustSrcIndex, &stPackItem ) )
            return;
        break;
    default:
        return;
        break;
    }

    if ( stPackItem.itembaseinfo.nOnlyInt != pMoveItem->nGuid )
    { return; }

    if ( pMoveItem->ustCount > stPackItem.itembaseinfo.ustItemCount || pMoveItem->ustCount == 0 )
        return;

    ItemDefine::SItemCommon* pItemCommon = theItemDetailConfig.GetItemByID( stPackItem.itembaseinfo.ustItemID );
    if ( NULL == pItemCommon )
    { return; }

    if ( pMoveItem->ustCount > pItemCommon->nStackNum )
    { pMoveItem->ustCount = pItemCommon->nStackNum; }

    if ( pMoveItem->ustCount < stPackItem.itembaseinfo.ustItemCount )
    { stPackItem.itembaseinfo.nOnlyInt = _NormalItemBag.GetNewItemID(); }

    stPackItem.itembaseinfo.ustItemCount = pMoveItem->ustCount;            
    stPackItem.storageinfo.nStorageNpcId = pMoveItem->nNpcID;            
    _StorageBag.stStorageItems[pMoveItem->ustDstIndex] = stPackItem;

    switch ( pMoveItem->ucItemBagType )
    {
    case BT_NormalItemBag:
        _NormalItemBag.ClearItem(pMoveItem->ustSrcIndex,pMoveItem->ustCount);
        break;
    case BT_MaterialBag:                
        _MaterialItemBag.ClearItem(pMoveItem->ustSrcIndex,pMoveItem->ustCount);
        break;
    default:
        return;
        break;
    }
    // Log pItemCommon前面已经判断NULL
    char szID[40] = {0};
    Log(theXmlString.GetString(eLog_info_2slk_89),pItemCommon->GetItemName(), BigInt2String(stPackItem.itembaseinfo.nOnlyInt, szID),stPackItem.itembaseinfo.ustItemCount/*, pMoveItem->ustSrcIndex, pMoveItem->ustDstIndex*/ );//lyh-- 后两个参数
}

void GamePlayer::MoveStorageToStorage( Msg* pMsg )
{
    MsgMoveStorageItem* pMoveItem = (MsgMoveStorageItem*)pMsg;

    if ( pMoveItem->ustDstIndex >= STORAGE_ITEMGRID_MAX || pMoveItem->ustSrcIndex >= STORAGE_ITEMGRID_MAX )
    { return; }

    SCharItem* pSrc = &_StorageBag.stStorageItems[pMoveItem->ustSrcIndex];
    SCharItem* pDst = &_StorageBag.stStorageItems[pMoveItem->ustDstIndex];

    if ( pSrc->itembaseinfo.ustItemID == InvalidLogicNumber || pSrc->itembaseinfo.nOnlyInt != pMoveItem->nGuid )
    { return; }

    //同一物品
    if( pDst->itembaseinfo.ustItemID == pSrc->itembaseinfo.ustItemID )
    {
        ItemDefine::SItemCommon* pItemWeapon = NULL;
        pItemWeapon    = GettheItemDetail().GetItemByID( pDst->itembaseinfo.ustItemID );
        if(!pItemWeapon)
        { return; }

        //物品是否独占
        if(pItemWeapon->IsExclusive())
        { return; }
        else
        {
            //不是同一城市的话
            //if( pDst->storageinfo.nStorageNpcId != pSrc->storageinfo.nStorageNpcId)
            //{ return; }

            if( pDst != NULL && pSrc != NULL )
            {
                char szID[40] = { 0 };
                Log(theXmlString.GetString(eLog_info_2slk_159),pDst->itembaseinfo.ustItemID, pDst->itembaseinfo.ustItemCount,pSrc->itembaseinfo.ustItemID ,pSrc->itembaseinfo.ustItemCount);
            }

            ItemBag::MoveItem( pDst, BT_StorageBag, pSrc, BT_StorageBag, &_NormalItemBag );
        }
    }
    else if( pDst->itembaseinfo.ustItemID == InvalidLogicNumber ) //不同物品
    {     
        *pDst = *pSrc;
        pSrc->itembaseinfo.ustItemID = InvalidLogicNumber;
    }
    else
    { return; }
}

void GamePlayer::OnMoveStorageItem( Msg* pMsg )
{
    MsgMoveStorageItem* pMoveItem = (MsgMoveStorageItem*)pMsg;
    
    switch( pMoveItem->enMoveType ) 
    {
    case MsgMoveStorageItem::Type_PackToStorage:
        { MovePackToStorage( pMsg ); }
        break;
    case MsgMoveStorageItem::Type_StorageToPack:
        { MoveStorageToPack( pMsg ); }
        break;
    case MsgMoveStorageItem::Type_StorageToStorage:
        { MoveStorageToStorage( pMsg ); }
        break;
    default:    
        return;
    }   
}

void GamePlayer::MoveMountToStorage ( Msg* pMsg )
{
    MsgMoveStorageMount* pMoveItem = (MsgMoveStorageMount*)pMsg;

    if (pMoveItem->nDstIndex > GetStorageMountGrid() )
    { return; }

    SMountItem* pStorageMount = _StorageBag.GetMountByIndex( pMoveItem->nDstIndex );
    if ( pStorageMount != NULL )
    { return; }

    SMountItem* pCharMount = _mountManager.GetMountByIndex( pMoveItem->nSrcIndex );
    if (pCharMount == NULL)
    { return; }

    if ( pCharMount->baseInfo.guid != pMoveItem->nGuid )
    { return; }

    if ( IsCountryMount( pCharMount ) )
    { 
        SendErrorToClient( ER_CountryMountStorage ); 
        return;
    }

    SMountItem* pActiveMount = _mountManager.GetActiveMount();
    if (pActiveMount != NULL)
    {
        if (pActiveMount->baseInfo.guid == pCharMount->baseInfo.guid)
        { 
            SendErrorToClient( ER_ActiveMountStorage ); 
            return;
        }
    }

    ItemDefine::SDrome * pDrome = GettheItemDetail().GetDromeByID( pCharMount->baseInfo.id );
    if ( pDrome == NULL )
    { return; }

    SMountItem mountItem = *pCharMount;
        
    _StorageBag.xStorageMounts[pMoveItem->nDstIndex] = mountItem;

    RemoveMountByIndex( pMoveItem->nSrcIndex );

    char szID[40] = {0};
    Log(theXmlString.GetString(eLog_info_2slk_89),pDrome->GetName(), BigInt2String(mountItem.baseInfo.guid, szID), NUMERIC_ONE );
}

void GamePlayer::MoveStorageToMount ( Msg* pMsg )
{
    MsgMoveStorageMount* pMoveMount = (MsgMoveStorageMount*)pMsg;

    SMountItem* pSrcMount = _StorageBag.GetMountByIndex( pMoveMount->nSrcIndex );
    if ( pSrcMount == NULL || pSrcMount->baseInfo.guid != pMoveMount->nGuid )
    { return; }

    ItemDefine::SDrome * pDrome = GettheItemDetail().GetDromeByID( pSrcMount->baseInfo.id );
    if ( pDrome == NULL )
    { return; }

    SMountItem mountItem = *pSrcMount;            

    if ( AddMount( mountItem ) != ierr_Success )
    {
        MsgAckResult msgack;
        msgack.result = ER_GetStorageMountFail;
        GettheServer().SendMsgToSingle( &msgack, this );
        return;
    }

    pSrcMount->baseInfo.id   = InvalidLogicNumber;
    pSrcMount->baseInfo.guid = 0;

    char szID[40] = {0};
    Log(theXmlString.GetString(eLog_info_2slk_90),pDrome->GetName(), BigInt2String(mountItem.baseInfo.guid, szID), NUMERIC_ONE );
}

void GamePlayer::OnMoveStorageMount( Msg* pMsg )
{
    MsgMoveStorageMount* pMoveMount = (MsgMoveStorageMount*)pMsg;

    switch( pMoveMount->nMoveType ) 
    {
    case MsgMoveStorageMount::Type_StorageToChar:
        { MoveStorageToMount( pMsg ); }
        break;
    case MsgMoveStorageMount::Type_CharToStorage:
        { MoveMountToStorage( pMsg ); }
        break;
    case MsgMoveStorageMount::Type_StorageToStorage:
        {  }
        break;
    default:    
        return;
    }   

    MsgUpdateMountStorage xUpdate;
    xUpdate.header.stID = GetID();
    memcpy(xUpdate.xStorageMounts,_StorageBag.xStorageMounts, sizeof(_StorageBag.xStorageMounts));
    SendMessageToClient( &xUpdate );

    MsgUpdateCharMount charMountMsg;
    charMountMsg.header.stID = GetID();
    memcpy(charMountMsg.xMounts,gCharInfoServer.itemData.miItems, sizeof(gCharInfoServer.itemData.miItems));
    SendMessageToClient( &charMountMsg );
}

void GamePlayer::OnMsgStorageMoneyReq( Msg* pMsg )
{
    MsgStorageMoneyReq* pReq = (MsgStorageMoneyReq*) pMsg;
    if ( pReq == NULL )
    { return; }        

    //不能操作负的钱
    if ( pReq->dwMoney < 0 )
    {
        //Log( "存取钱作弊, 修改协议[%u][%d]", pReq->chOperation, pReq->dwMoney );
		Log( theXmlString.GetString(eServerLog_GetMoneyZuoBi), pReq->chOperation, pReq->dwMoney );
        return;
    }

    //(以后要做放作弊,通过npcid找到出售的npc位置,判断位置距离,不符合要求的不能存取钱);

    if ( pReq->chOperation == MsgStorageMoneyReq::Save )
    {
        if (GetMoney() == 0)         
        { return; }             // 身上没钱

        uint32 dwSaveMoney = 0;     // 实际存入的钱
        if ( pReq->dwMoney >= GetMoney() )     //不能大于身上的钱
        {
            dwSaveMoney = GetMoney();
        }
        else
        {
            dwSaveMoney = pReq->dwMoney;
        }

        DWORD dwCanSave = ULONG_MAX - _StorageBag.dwStorageMoney;
        if ( dwCanSave < dwSaveMoney )
        { dwSaveMoney = dwCanSave; }
        if ( dwSaveMoney == 0 )
        { return; }

        OperateMoney( EOT_Sub, dwSaveMoney, false, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Storage);
        _StorageBag.dwStorageMoney += dwSaveMoney;
        /*Log( "存入金钱[%u], 当前: 身上金钱[%u], 仓库金钱[%u]", dwSaveMoney, GetMoney(), _StorageBag.dwStorageMoney );*/
		Log( theXmlString.GetString(eServerLog_CunMoney), dwSaveMoney, GetMoney(), _StorageBag.dwStorageMoney );
    }
    else if (pReq->chOperation == MsgStorageMoneyReq::TakeOut)
    {
        if (_StorageBag.dwStorageMoney == 0)
        { return; }             // 仓库里没钱

        uint32 dwTakeMoney = 0;     // 实际取出来的钱
        if (pReq->dwMoney >= _StorageBag.dwStorageMoney)
        {
            dwTakeMoney = _StorageBag.dwStorageMoney;
        }
        else
        {
            dwTakeMoney = pReq->dwMoney;
        }

        // 判断背包的最大数量,
        int dwCanTake = g_Cfg.m_nMoneyMax - GetMoney();
        if ( dwCanTake < dwTakeMoney )
            dwTakeMoney = dwCanTake;

        OperateMoney( EOT_Add, dwTakeMoney, false, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Storage);
        _StorageBag.dwStorageMoney -= dwTakeMoney;
       // Log( "取出金钱[%u], 当前: 身上金钱[%u], 仓库金钱[%u]", dwTakeMoney, GetMoney(), _StorageBag.dwStorageMoney );
		Log( theXmlString.GetString(eServerLog_QuMoney), dwTakeMoney, GetMoney(), _StorageBag.dwStorageMoney );
    }
    else
    {
       // Log( "存取钱作弊, 修改协议[%u][%u]", pReq->chOperation, pReq->dwMoney );
		Log( theXmlString.GetString(eServerLog_CunMoneyZuoBi), pReq->chOperation, pReq->dwMoney );
        return;
    }

    MsgStorageMoneyAck xAck;
    xAck.dwPackageMoney = GetMoney();
    xAck.dwStorageMoney = _StorageBag.dwStorageMoney;
    GettheServer().SendMsgToSingle(&xAck, this);
}

void GamePlayer::OnLockItemReq( Msg* pMsg )
{       
    MsgLockItemReq* pLockItem = static_cast< MsgLockItemReq* >( pMsg );
    if ( pLockItem == NULL )
    { return; }

    switch ( pLockItem->uchBagType )
    {
    case BT_MountBag:
        {
            SMountItem* pMountItem = _mountManager.GetMountByIndex( pLockItem->ustItemIndex );
            if ( pMountItem == NULL || pMountItem->baseInfo.guid != pLockItem->nGuID )
            { return; }

            if ( pMountItem->IsLock() && pMountItem->GetUnLockTime() == 0 )
            { return; }

            pMountItem->SetLock( true );
        }
        break;
    case BT_PetBag:
        {
            SPetItem* pPetItem = _petManager.GetPetByIndex( pLockItem->ustItemIndex );
            if ( pPetItem == NULL || pPetItem->baseInfo.guid != pLockItem->nGuID )
            { return; }

            if ( pPetItem->IsLock() && pPetItem->GetUnLockTime() == 0 )
            { return; }

            pPetItem->SetLock( true );
        }
        break;
    default:
        {
            SCharItem* pCharItem = NULL;
            switch( pLockItem->uchBagType )
            {
            case BT_NormalItemBag:
                pCharItem = _NormalItemBag.GetItemByIndex( pLockItem->ustItemIndex );
                break;
            case BT_MaterialBag:
                pCharItem = _MaterialItemBag.GetItemByIndex( pLockItem->ustItemIndex );
                break;
            case BT_TaskBag:
                pCharItem = _TaskItemBag.GetItemByIndex( pLockItem->ustItemIndex );
                break;
            case BT_StorageBag:
                pCharItem = _StorageBag.GetItemByIndex( pLockItem->ustItemIndex );
                break;
            }

            if ( pCharItem == NULL || pCharItem->itembaseinfo.nOnlyInt != pLockItem->nGuID )
            { return; }

            if ( pCharItem->IsLock() && pCharItem->GetUnLockTime() == 0 )
            { return; }

            pCharItem->SetLock( true );
        }
    }

    MsgLockItemAck xAck;
    xAck.uchBagType   = pLockItem->uchBagType;
    xAck.ustItemIndex = pLockItem->ustItemIndex;
    xAck.nGuID        = pLockItem->nGuID;
    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnUnLockItemReq( Msg* pMsg )
{
    MsgUnLockItemReq* pUnLockItem = static_cast< MsgUnLockItemReq* >( pMsg );
    if ( pUnLockItem == NULL )
    { return; }

    uint32 nTime = ItemUnLockTime;
    TimeSpan timespan( nTime );
    TimeEx DestTime = TimeEx::GetCurrentTime() + timespan;
    __int64 nUnLockTime = DestTime.GetTime();

    switch ( pUnLockItem->uchBagType )
    {
    case BT_MountBag:
        {
            SMountItem* pMountItem = _mountManager.GetMountByIndex( pUnLockItem->ustItemIndex );
            if ( pMountItem == NULL || pMountItem->GetMountGuid() != pUnLockItem->nGuID || pMountItem->GetMountGuid() == m_nCountryMountGUID )
            { return; } // 如果是国家坐骑不能解锁

            if ( !pMountItem->IsLock() || pMountItem->GetUnLockTime() != 0 )
            { return; }

            pMountItem->SetUnLockTime( nUnLockTime );
            pMountItem->SetUnLockLeftTime( timespan.GetTimeSpan() );
        }
        break;
    case BT_PetBag:
        {
            SPetItem* pPetItem = _petManager.GetPetByIndex( pUnLockItem->ustItemIndex );
            if ( pPetItem == NULL || pPetItem->GetPetGuid() != pUnLockItem->nGuID )
            { return; } 

            if ( !pPetItem->IsLock() || pPetItem->GetUnLockTime() != 0 )
            { return; }

            pPetItem->SetUnLockTime( nUnLockTime );
            pPetItem->SetUnLockLeftTime( timespan.GetTimeSpan() );
        }
        break;
    default:
        {
            SCharItem* pCharItem = NULL;
            switch( pUnLockItem->uchBagType )
            {
            case BT_NormalItemBag:
                pCharItem = _NormalItemBag.GetItemByIndex( pUnLockItem->ustItemIndex );
                break;
            case BT_MaterialBag:
                pCharItem = _MaterialItemBag.GetItemByIndex( pUnLockItem->ustItemIndex );
                break;
            case BT_TaskBag:
                pCharItem = _TaskItemBag.GetItemByIndex( pUnLockItem->ustItemIndex );
                break;
            case BT_StorageBag:
                pCharItem = _StorageBag.GetItemByIndex( pUnLockItem->ustItemIndex );
                break;
            }

            if ( pCharItem == NULL || pCharItem->itembaseinfo.nOnlyInt != pUnLockItem->nGuID )
            { return; }

            if ( !pCharItem->IsLock() || pCharItem->GetUnLockTime() != 0 )
            { return; }

            pCharItem->SetUnLockTime( nUnLockTime );
            pCharItem->SetUnLockLeftTime( timespan.GetTimeSpan() );
        }
    }

    MsgUnLockItemAck xAck;
    xAck.uchBagType      = pUnLockItem->uchBagType;
    xAck.ustItemIndex    = pUnLockItem->ustItemIndex;
    xAck.nGuID           = pUnLockItem->nGuID;
    xAck.n64UnLockTime   = nUnLockTime;
    xAck.nUnLockLeftTime = timespan.GetTimeSpan();
    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnCheckUnLockItemReq( Msg* pMsg )
{
    MsgCheckUnLockItemReq* pReq = static_cast< MsgCheckUnLockItemReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    switch ( pReq->uchBagType )
    {
    case BT_MountBag:
        {
            SMountItem* pMountItem = _mountManager.GetMountByIndex( pReq->ustItemIndex );
            if ( pMountItem == NULL || pMountItem->baseInfo.guid != pReq->nGuID )
            { return; }

            if ( !pMountItem->IsLock() || pMountItem->GetUnLockTime() == 0 )
            { return; }

            if ( !TimeEx::IsPassCurrentTime( pMountItem->GetUnLockTime() - 10 ) )
            { return; }

            pMountItem->SetLock( false );
        }
        break;
    case BT_PetBag:
        {
            SPetItem* pPetItem = _petManager.GetPetByIndex( pReq->ustItemIndex );
            if ( pPetItem == NULL || pPetItem->baseInfo.guid != pReq->nGuID )
            { return; }

            if ( !pPetItem->IsLock() || pPetItem->GetUnLockTime() == 0 )
            { return; }

            if ( !TimeEx::IsPassCurrentTime( pPetItem->GetUnLockTime() - 10 ) )
            { return; }

            pPetItem->SetLock( false );
        }
        break;
    default:
        {
            SCharItem* pCharItem = NULL;
            switch( pReq->uchBagType )
            {
            case BT_NormalItemBag:
                pCharItem = _NormalItemBag.GetItemByIndex( pReq->ustItemIndex );
                break;
            case BT_MaterialBag:
                pCharItem = _MaterialItemBag.GetItemByIndex( pReq->ustItemIndex );
                break;
            case BT_TaskBag:
                pCharItem = _TaskItemBag.GetItemByIndex( pReq->ustItemIndex );
                break;
            case BT_StorageBag:
                pCharItem = _StorageBag.GetItemByIndex( pReq->ustItemIndex );
                break;
            }

            if ( pCharItem == NULL || pCharItem->itembaseinfo.nOnlyInt != pReq->nGuID )
            { return; }

            if ( !pCharItem->IsLock() )
            { return; }

            if ( pCharItem->GetUnLockTime() != 0 )
            {
                if ( !TimeEx::IsPassCurrentTime( pCharItem->GetUnLockTime() - 10 ) )
                { return; }
            }

            pCharItem->SetLock( false );
        }
    }

    MsgCheckUnLockItemAck xAck;
    xAck.uchBagType   = pReq->uchBagType;
    xAck.ustItemIndex = pReq->ustItemIndex;
    xAck.nGuID        = pReq->nGuID;
    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnLearnSkill( Msg* pMsg )
{       
    CHECK_MSGLEN( pMsg, MsgLearnSkill)
    MsgLearnSkill* pLearnSkill = (MsgLearnSkill*)pMsg;
    if ( NULL == pLearnSkill)
    { return; }

    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pLearnSkill->stSkillId, 1 );//根据技能ID来获得技能的信息
    if ( !pSkill)
    { return; }

    LearnSkill( pLearnSkill->stSkillId );//学习技能
}

void GamePlayer::OnLearnAllSkill( Msg* pMsg )
{       
    MsgLearnAllSkill* pLearnAllSkill = (MsgLearnAllSkill*)pMsg;
    if ( NULL == pLearnAllSkill)
    { return; }

    const CItemDetail::vectorSkill& vecSkill = GettheItemDetail().GetProfessionSkill( GetProfession() );
    
    for (int lv = 1 ; lv < NUMERIC_NINE; ++lv )
    {
        CItemDetail::vectorSkill::const_iterator iter = vecSkill.begin();
        for ( ; iter != vecSkill.end(); ++iter )
        {
            ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( *iter, 1 );
            if (NULL == pSkill)
            { return; }

            SCharSkill* pCharSkill = _SkillBag.GetSkillByID( pSkill->ustItemID );
            if (pCharSkill != NULL)
            {
                if (lv <= pCharSkill->stSkillLevel)
                { continue; }
            }

            if (lv >= pSkill->ustSkillMaxLvl)
            { continue; }

            if ( !CanLearnSkill( pSkill->ustItemID, lv ) )
            { continue; }

            if ( lv == 1)
            {
                LearnSkill( pSkill->ustItemID, lv , true , true );
            }
            else
            {
                LearnSkill( pSkill->ustItemID, lv , true , false );
            }
        }
    }
}

void GamePlayer::OnQueryCompound( Msg* pMsg )
{ // 合成
    //    MsgQueryCompound* pQueryCompound = (MsgQueryCompound*)pMsg;
    //    if ( !pQueryCompound )
    //        return;
    //
    //    MsgScriptMakeItem* pMakeItemInfo = GetMakeItemInfo();
    //
    //    short stPrescription = pQueryCompound->stPrescriptionId;
    //
    //    SCompoundItem* pCompound = &gCharInfoServer.otherdata.stCompoundItem;
    //
    //    // 是否有材料
    //    int nMaterialCount = 0;
    //    for( int n=0; n<ITEM_COMPOUND_BAGMAX; ++n )
    //    {
    //        if ( pCompound->stMaterial[n].itembaseinfo.ustItemID != ErrorUnsignedShortID )
    //        {
    //            ++nMaterialCount;
    //        }
    //    }
    //
    //    if ( nMaterialCount == 0 )
    //        return;
    //
    //    BOOL bOverdue = FALSE;
    //    for( int n=0; n<ITEM_COMPOUND_BAGMAX; ++n )
    //    {
    //        if ( pCompound->stMaterial[n].itembaseinfo.ustItemID != ErrorUnsignedShortID )
    //        {
    //            if ( pCompound->stMaterial[n].IsOverdue() )
    //            { // 是否过期
    //                bOverdue = TRUE;
    //                break;
    //            }
    //        }
    //    }
    //    if ( pCompound->stPrescription.itembaseinfo.ustItemID != ErrorUnsignedShortID && pCompound->stPrescription.IsOverdue())
    //        bOverdue = TRUE;
    //
    //    if( bOverdue )
    //    { // 过期错误返回
    //        TellClient( theXmlString.GetString(eSystemInfo_ResetTime_CantCompound) );
    //        return;
    //    }
    //
    //    // 目标位是否有东西 不合成
    //    if ( pCompound->stAim.itembaseinfo.ustItemID != ErrorUnsignedShortID )
    //        return;
    //
    //    MsgAckCompound msg;
    //
    //    int nMaxMakeItemCount = 0;
    //    
    //    if ( stPrescription == ErrorUnsignedShortID )
    //    { // 合成宝石
    //        GemCompound();
    //        return;
    //    }
    //
    //    ItemDefine::SItemCreateItemRule* pCreateItem = (ItemDefine::SItemCreateItemRule*)GettheItemDetail().GetItemByID(stPrescription);
    //    if ( !pCreateItem )
    //        return;
    //
    //    int iCrystalNumber= -1;
    //    int iCrystalLevel = 0;
    //    int iConut = 0;
    //
    //    int iNeedMaterialTypeCount = pCreateItem->iMaterialNum;
    //
    //    if ( pCreateItem->ucItemType != CItemDetail::ITEMTYPE_CREATEITEMRULE )
    //        return;
    //
    //    bool bFoundMaterial = false;
    //    int nRightMaterial = 0;
    //    
    //    ItemDefine::SItemCommon* pMaterialItem = NULL;
    //    int nTempCount[ITEM_COMPOUND_BAGMAX] = {0};
    //    for ( int n=0; n<ITEM_COMPOUND_BAGMAX; n++ )
    //    {
    //        if (pCompound->stMaterial[n].itembaseinfo.ustItemID == ErrorUnsignedShortID)
    //            continue;
    //
    //        for (int m=0; m<iNeedMaterialTypeCount; m++)
    //        {
    //            if (pCompound->stMaterial[n].itembaseinfo.ustItemID == pCreateItem->material[m].ustItemID)
    //            {
    //                pMaterialItem = GettheItemDetail().GetItemByID( pCreateItem->material[m].ustItemID );
    //
    //                if (!pMaterialItem)
    //                    continue;
    //
    //                if ( !pMaterialItem->IsExclusive() && m < 4)
    //                {
    //                    if (pCreateItem->material[m].ustCount <= pCompound->stMaterial[n].itembaseinfo.ustItemCount )
    //                    {
    //                        int i = pCreateItem->material[m].ustCount;
    //                        int j = pCompound->stMaterial[n].itembaseinfo.ustItemCount;
    //
    //                        if (i > 0 && j > 0)
    //                        {
    //                            nTempCount[n] = j/i; // 倍数
    //
    //                            bFoundMaterial = true;
    //                            nRightMaterial++;
    //                            break;
    //                        }                            
    //                    }
    //                }
    //            }        
    //        }
    //    }
    //
    //    // 是否足够的材料
    //    if ( nRightMaterial != iNeedMaterialTypeCount )
    //    {
    //        msg.stResult = MsgAckCompound::eResultMaterialUnconformity;
    //        goto tagEnd;
    //    }
    //
    //    // 计算生成的个数
    //    for (int nNum = 0; nNum <ITEM_COMPOUND_BAGMAX; ++nNum )
    //    {
    //        if (pCompound->stMaterial[nNum].itembaseinfo.ustItemID != ErrorUnsignedShortID)
    //        {
    //            if (nNum == 0)
    //            { // 如果是第一次
    //                nMaxMakeItemCount = nTempCount[nNum];
    //                continue;
    //            }
    //            
    //            if (nTempCount[nNum] < nMaxMakeItemCount)
    //            {
    //                nMaxMakeItemCount = nTempCount[nNum];
    //            }
    //        }
    //    }
    //        
    //    if ( !pCreateItem->bIntensify)
    //    { //合成   
    //        // 钱是否够
    //        if( nMaxMakeItemCount * pCreateItem->nNeedMenoy > GetMoney() )
    //        {
    //            msg.stResult = MsgAckCompound::eResultNotEnoughMoney;
    //            goto tagEnd;
    //        }
    //
    //        int  nSuccRate = 0;
    //        int  nSuccRate1 = 0;
    //        int  nSuccRate2 = 0;
    //        int  nLuck = m_cFightStatus.GetCompoundRate();
    //        bool bIsSucc = false;
    //        int  nRandNum = theRand.rand32()%100;
    //
    //        nSuccRate = pCreateItem->iCreateSuccRate / 100;
    //        if (nSuccRate == 0)
    //        {
    //            nSuccRate = pMakeItemInfo->m_nRate;
    //        }
    //        nSuccRate += nSuccRate * nLuck / 100;
    //
    //        if (pCreateItem->iCreateSuccRate1 > 0)
    //        {
    //            nSuccRate1 = pCreateItem->iCreateSuccRate1 * (100 + nLuck) / 100;
    //        }
    //
    //        if (pCreateItem->iCreateSuccRate2 > 0)
    //        {
    //            nSuccRate2 = pCreateItem->iCreateSuccRate2 * (100 + nLuck) / 100;
    //        }
    //
    //        unsigned short ustAimId = ErrorUnsignedShortID;
    //
    //        // nSuccRate2是最小端
    //        if (pCreateItem->pItemTarget2 != NULL && nRandNum <= nSuccRate2 )
    //        { // 第一次
    //            ustAimId = pCreateItem->pItemTarget2->ustItemID;
    //            bIsSucc = true;
    //        }
    //        else if (pCreateItem->pItemTarget1 != NULL && nRandNum > nSuccRate2 && nRandNum <= nSuccRate1 )
    //        { // 第二次
    //            ustAimId = pCreateItem->pItemTarget1->ustItemID;
    //            bIsSucc = true;
    //        }
    //        else if (pCreateItem->pItemTarget != NULL && nRandNum >nSuccRate1 && nRandNum <= nSuccRate )
    //        {  // 第三次
    //            ustAimId = pCreateItem->pItemTarget->ustItemID;
    //            bIsSucc = true;
    //        }
    //
    //        if ( !bIsSucc )
    //        {
    //            msg.stResult = MsgAckCompound::eResultFaild;
    //            goto tagEnd;
    //        }
    //
    //        // 确认个数        
    //        if ( pCreateItem->pItemTarget != NULL && pCreateItem->pItemTarget->IsExclusive())
    //        {
    //            nMaxMakeItemCount = 1;
    //        }            
    //        if ( pCreateItem->pItemTarget1 != NULL && pCreateItem->pItemTarget1->IsExclusive())
    //        {
    //            nMaxMakeItemCount = 1;
    //        }
    //        if ( pCreateItem->pItemTarget2 != NULL && pCreateItem->pItemTarget2->IsExclusive())
    //        {
    //            nMaxMakeItemCount = 1;
    //        }
    //
    //        __int64 nBigId = _NormalItemBag.GetNewItemID();
    //        if ( nBigId == -1)
    //            return;
    //
    //        SCharItem stItem;
    //        bool bOk = theRunTimeData.CreateItem(ustAimId, nMaxMakeItemCount,nBigId, stItem);
    //
    //        if (!bOk)
    //            return;
    //
    //        pCompound->stAim = stItem;
    //        msg.stAim = stItem;
    //        msg.stResult = MsgAckCompound::eResultSuccess;
    //        char szID[40];
    //        Log(theXmlString.GetString(eLog_info_2slk_97),stItem.itembaseinfo.ustItemID ,BigInt2String(stItem.itembaseinfo.nOnlyInt,szID));
    //        
    //    }
    //
    //    // 消除
    //    pCompound->stPrescription.itembaseinfo.ustItemID = ErrorUnsignedShortID;
    //
    //    // 脚本扣钱
    //    Script_AddMoney((pCreateItem->nNeedMenoy)*nMaxMakeItemCount,EOT_Sub);
    //    
    //    for( int p=0; p<ITEM_COMPOUND_BAGMAX; p++ )
    //    {
    //        msg.nMaterialNum[p] = 0;
    //    }
    //
    //    for( int iloop=0; iloop<ITEM_COMPOUND_BAGMAX; iloop++ )
    //    {
    //        int nUsedCount = 0;
    //        int nLastCount = 0;
    //        
    //        for (int nm = 0; nm<iNeedMaterialTypeCount;nm++ )
    //        {
    //            if (pCompound->stMaterial[iloop].itembaseinfo.ustItemID == pCreateItem->material[nm].ustItemID)
    //            {
    //                nUsedCount = nMaxMakeItemCount*(pCreateItem->material[nm].ustCount);
    //                nLastCount = pCompound->stMaterial[iloop].itembaseinfo.ustItemCount;
    //                nLastCount -= nUsedCount;
    //
    //                if (nLastCount <= 0)
    //                {
    //                    pCompound->stMaterial[iloop].itembaseinfo.ustItemID = ErrorUnsignedShortID;
    //                    pCompound->stMaterial[iloop].itembaseinfo.ustItemCount = 0;
    //                    msg.nMaterialNum[iloop] = 0;
    //                }
    //                else
    //                {
    //                    pCompound->stMaterial[iloop].itembaseinfo.ustItemCount = nLastCount;
    //                    msg.nMaterialNum[iloop] = pCompound->stMaterial[iloop].itembaseinfo.ustItemCount;
    //                }
    //                break;
    //            }
    //        }
    //    }
    //    memcpy(&gCharInfoServer.otherdata.stCompoundItem.stAim,&pCompound->stAim,sizeof(SCharItem));
    //     
    //tagEnd:
    //    GettheServer().SendMsgToSingle( &msg, this );

}

void GamePlayer::OnMsgMoveReduceItem(Msg* pMsg)
{       
    //if (!pMsg)
    //{ return; }

    //MsgMoveReduceItem *pMove = (MsgMoveReduceItem*)pMsg;
    //SReduceItem *pReduce = NULL;
    //pReduce = &gCharInfoServer.otherdata.sReduceItem;

    //if (!pReduce||!pMove)
    //{
    //    return;
    //}
    //switch( pMove->stMoveType )
    //{
    //case MsgMoveReduceItem::ePackToReduce:
    //    {
    //        if( _NormalItemBag.IsHaveItem( pMove->stSrcIndex ) == false )
    //            return;
    //        if (gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].storageinfo.bIsLocked)
    //            return;
    //        char szID[40] = {0};
    //        Log(theXmlString.GetString(eLog_info_2slk_115),
    //            ::BigInt2String(gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.nOnlyInt,szID),
    //            gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.ustItemID,
    //            gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.ustItemCount);

    //        ItemBag::MoveItem( &pReduce->siSrcItem, BT_ReduceBag, &gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex], BT_NormalItemBag, &_NormalItemBag,pMove->stCount);
    //    }
    //    break;
    //case MsgMoveReduceItem::eReduceToPack:
    //    {
    //        if (pMove->stDstIndex >= GetNormalBagSize())
    //            return;
    //        char szID[40] = {0};
    //        Log( theXmlString.GetString(eLog_info_2slk_116),
    //            ::BigInt2String(pReduce->siSrcItem.itembaseinfo.nOnlyInt,szID),
    //            pReduce->siSrcItem.itembaseinfo.ustItemID,
    //            pReduce->siSrcItem.itembaseinfo.ustItemCount);

    //        ItemBag::MoveItem( &gCharInfoServer.itemData.stPackItems[pMove->stDstIndex], BT_NormalItemBag, 
    //            &pReduce->siSrcItem, BT_ReduceBag, &_NormalItemBag,pMove->stCount);
    //    }
    //    break;
    //case MsgMoveReduceItem::eAimToPack:
    //    {
    //        if (pMove->stDstIndex >= GetNormalBagSize())
    //            return;
    //        char szID[40] = {0};
    //        Log(theXmlString.GetString(eLog_info_2slk_117),
    //            ::BigInt2String(pReduce->siAimItem.itembaseinfo.nOnlyInt,szID),
    //            pReduce->siAimItem.itembaseinfo.ustItemID,
    //            pReduce->siAimItem.itembaseinfo.ustItemCount);

    //        ItemBag::MoveItem(&gCharInfoServer.itemData.stPackItems[pMove->stDstIndex], BT_NormalItemBag, 
    //            &pReduce->siAimItem, BT_CompoundBag, &_NormalItemBag,pMove->stCount);
    //    }
    //    break;
    //default:
    //    break;
    //}
    //    
}

void GamePlayer::OnMsgUnSoulBound(Msg* pMsg)
{       
    return;
    //if (!pMsg)
    //{ return; }

    //MsgCallUnSoulBound* pCall = (MsgCallUnSoulBound*)pMsg;
    //if (!pCall)
    //{ return; }

    //int nNeed = 0;
    //MsgUnSoulBound msg;
    //msg.header.stID = GetID();
    //if (gCharInfoServer.otherdata.sUnSoulBound.siItem.equipdata.bIsSoulBounded == true
    //    &&gCharInfoServer.otherdata.sUnSoulBound.siItem.itembaseinfo.ustItemID != ErrorUnsignedShortID )
    //{
    //    ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(gCharInfoServer.otherdata.sUnSoulBound.siItem.itembaseinfo.ustItemID);
    //    if (pItemCommon)
    //    {
    //        if (pItemCommon->bIsCanBound)
    //        {
    //            bool bTemp = OperateJinDing(false,nNeed);
    //            if (bTemp)
    //            {
    //                if (gCharInfoServer.otherdata.sUnSoulBound.siItem.itembaseinfo.ustItemID != ErrorUnsignedShortID)
    //                {
    //                    gCharInfoServer.otherdata.sUnSoulBound.siItem.equipdata.bIsSoulBounded = false;
    //                    msg.stRec = MsgUnSoulBound::eSuc;
    //                    char szID2[40];
    //                    Log(theXmlString.GetString(eLog_info_2slk_120),gCharInfoServer.otherdata.sUnSoulBound.siItem.itembaseinfo.ustItemID ,
    //                                                    BigInt2String(gCharInfoServer.otherdata.sUnSoulBound.siItem.itembaseinfo.nOnlyInt,szID2));
    //                }
    //                else
    //                {
    //                    msg.stRec = MsgUnSoulBound::eNotBound;
    //                }
    //            }
    //            else
    //            {
    //                msg.stRec = MsgUnSoulBound::eNotEnoughMoney;
    //            }
    //        }
    //    }
    //}
    //else
    //{
    //    msg.stRec = MsgUnSoulBound::eNotBound;
    //}
    //GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnMsgMoveUnSoulBound(Msg* pMsg)
{
    //if (!pMsg)
    //{ return; }

    //MsgMoveUnSoulBound* pMove = (MsgMoveUnSoulBound*)pMsg;
    //if (!pMove)
    //{ return; }

    //SUnSoulBound* pUnSoulBound = NULL;
    //pUnSoulBound = &gCharInfoServer.otherdata.sUnSoulBound;

    //switch(pMove->stMoveType)
    //{
    //case MsgMoveUnSoulBound::ePackToIcon:
    //    {
    //        if( _NormalItemBag.IsHaveItem( pMove->stSrcIndex ) == false )
    //            return;
    //        if (gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].storageinfo.bIsLocked
    //            ||!gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].equipdata.bIsSoulBounded)
    //            return;
    //        
    //        char szID[40] = {0};
    //        Log(theXmlString.GetString(eLog_info_2slk_121),
    //            ::BigInt2String(gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.nOnlyInt,szID),
    //            gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.ustItemID,
    //            gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.ustItemCount);
    //        ItemBag::MoveItem( &pUnSoulBound->siItem, BT_CompoundBag, &gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex], BT_NormalItemBag, 
    //        &_NormalItemBag,pMove->stCount);
    //    }
    //    break;
    //case MsgMoveUnSoulBound::eIconToPack:
    //    {
    //        if (pMove->stDstIndex >= GetNormalBagSize())
    //            return;
    //        char szID[40] = {0};
    //        Log( theXmlString.GetStringWithName(eLog_info_2slk_122),
    //            ::BigInt2String(pUnSoulBound->siItem.itembaseinfo.nOnlyInt,szID),
    //            pUnSoulBound->siItem.itembaseinfo.ustItemID,
    //            pUnSoulBound->siItem.itembaseinfo.ustItemCount);

    //        ItemBag::MoveItem( &gCharInfoServer.itemData.stPackItems[pMove->stDstIndex], BT_NormalItemBag, 
    //            &pUnSoulBound->siItem, BT_CompoundBag, &_NormalItemBag,pMove->stCount);
    //    }
    //    break;
    //default:
    //    break;
    //}
}

void GamePlayer::OnMsgSelectChannel( Msg* pMsg )
{
    MsgSelectChannel* pMessage = (MsgSelectChannel*) pMsg;

    MsgS2SSelectChannel msg;
    msg.header.stID = GetID();
    strncpy_s( msg.channel.szChannelName, pMessage->channel.szChannelName, sizeof(msg.channel.szChannelName));

    msg.channel = pMessage->channel;
    msg.nAccountId = pMessage->nAccountId;
    msg.nServerType =  ST_GameServer;
    msg.nServerId = g_Cfg.dwServerID;
    GettheServer().SendCenterServerMsg( &msg );

	_buffManager.ClearBuffByBuffIdLevel(g_Cfg.nChannelStatusId, g_Cfg.nChannelStatusLevel);
}

void GamePlayer::SendQuestFail( int16 questID )
{
    MsgAckResult msg;
    msg.result = ER_QuestFail;
    msg.value = questID;
    SendMessageToClient( &msg );
}

void GamePlayer::OnAckScriptShowQuestDlg( Msg* pMsg )
{        
    MsgScriptAckShowQuestDlg* pQuestDlg = (MsgScriptAckShowQuestDlg*)pMsg;

    uint32 result = _actionManager.Action( pQuestDlg->GetType() );
    if ( RESULT_FAILED( result ) )
    {
        SendQuestFail( pQuestDlg->stQuestId );
        return;
    }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nScriptNpcId );
    if( !pChar || !pChar->IsNpc() )
    {
        SendQuestFail( pQuestDlg->stQuestId );
        return;
    }

    NpcBaseEx* pNpc = (NpcBaseEx*)pChar;

    SScript* pScript = GetScript();
    if ( !pScript )
    { 
        SendQuestFail( pQuestDlg->stQuestId );
        return; 
    }

    pScript->nVar = pQuestDlg->stQuestId;
    GetScriptMgr()->ExecuteVM( ST_NPC, pChar->GetID(), this ); // 走完原来的脚本  Ask 功能1 功能2 任务

    if ( pQuestDlg->stQuestId == 0 || pQuestDlg->stQuestId == -1 )
    { 
        SendQuestFail( pQuestDlg->stQuestId );
        return; 
    }

    // 是否有这个任务
    SQuest* pQuest = theQuestManager.GetQuest(pQuestDlg->stQuestId );
    if ( pQuest == NULL )
    { 
        SendQuestFail( pQuestDlg->stQuestId );
        return; 
    }

    // 得到任务前置
    SQuestRequirement* pSQuestReq = pQuest->GetReceiveRequirement(SQuest::eRequirement_Quest);

    uint8 byState = GetQuestState( pQuestDlg->stQuestId );
    // 检查前置任务有没有完成，没有完成就不执行脚本
    for( int n = 0; n < pNpc->GetQuestScriptCount(); ++n )
    {
        QuestScript* pRelateQuestInfo = pNpc->GetQuestScriptByIndex( n );
        if ( pRelateQuestInfo == NULL )
        { continue; }

        // 判断前置任务有没有做完
        if ( pSQuestReq )
        { // 如果前置任务存在
            if ( pSQuestReq->Value == pRelateQuestInfo->stQuestId )
            {
                if (!IsQuestDone( GetVar(pSQuestReq->Value)))
                { continue; }
            }
        }

        // 条件符合 开始任务脚本
        if ( pRelateQuestInfo->stQuestId == pQuestDlg->stQuestId && pRelateQuestInfo->chState == byState )
        {
            CScriptMgr::CallQuestScript( pRelateQuestInfo, this, m_nScriptNpcId );
            return;
        }
    }

    SendQuestFail( pQuestDlg->stQuestId );
}

void GamePlayer::OnReqQuestInfo( Msg* pMsg )
{       
    MsgReqQuestInfo* pQuestInfo = (MsgReqQuestInfo*)pMsg;

    SQuest* pQuest = theQuestManager.GetQuest( pQuestInfo->stQuestId );
    if( pQuest == NULL )
    {
        if( pQuestInfo->stQuestId < dr_MinQuestId || pQuestInfo->stQuestId > dr_MaxQuestId )
        { 
            ProcessBeBlock( MsgNotifyBeKick::EKT_Hook, 1000 * 10 );
            LOG_MESSAGE( CHECKCHEATOBJECT, LOG_PRIORITY_INFO, "[%s] 作弊请求 quest%d.quest 被踢", GetCharName(), pQuestInfo->stQuestId  );
        }

        //Log( "查询quest%d.quest文件不存在", GetCharName(), pQuestInfo->stQuestId );
		Log( theXmlString.GetString(eServerLog_QuestNoFind), GetCharName(), pQuestInfo->stQuestId );
        return;
    }

    if ( theQuestManager.IsQuestDone( GetQuestState( pQuestInfo->stQuestId ) ) )
    { return; }

    MsgAckQuestInfo msg;
    msg.header.stID = GetID();
    msg.stQuest = *pQuest;
    GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnGetShop( Msg* pMsg )
{       
    if ( !m_pstShop )
        return;
    g_svi.Shop( m_pstShop->nShopId, GetID() );
}

void GamePlayer::OnAbandonTask( Msg* pMsg )
{       
    MsgAbandonTask* pTask = (MsgAbandonTask*)pMsg;
    if ( pTask->stTaskId < dr_MinQuestId ||  pTask->stTaskId > dr_MaxQuestId )
    { return; }

	//已经冻结的任务无法放弃
	if(theQuestManager.GetQuestState( GetVar( pTask->stTaskId ) ) ==  QuestManager::eQuestFrozen )
		return;

    uint32 result = _actionManager.Action( pTask->GetType() );
    if ( RESULT_FAILED( result ) )
    { return; }

	if (GetScript() && GetScript()->thread.IsHangup())
	{
		return;
	}
	
    Script_CancelQuest( pTask->stTaskId );
}

void GamePlayer::OnQueryScriptVar( Msg* pMsg )
{

    MsgQueryScriptVar *pVar = (MsgQueryScriptVar*)pMsg;
    int nKey = GetScriptVarMgr()->GetVarId( pVar->szVar );
    int nVale = GetVar( nKey );
    TellClient( "Var:%s=%d", pVar->szVar, nVale );
}

void GamePlayer::OnMsgReqChangeSubAction( Msg *pMsg )
{
    MsgReqChangeSubAction* pReq = static_cast< MsgReqChangeSubAction* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( GetStatus() != CS_IDLE || HaveFighteFlag(eFighting) )
    { return; }

    switch ( pReq->action )
    {
    case CS_SubAction_Embrace:
        {
        }
        break;
    default:
        ChangeSubAction( pReq->action, -1 );
        break;
    }
}

void GamePlayer::OnGetShopCenter( Msg *pMsg )
{
    if( m_dwReqShopTime !=0 && !GameTime::IsPassCurrentTime( m_dwReqShopTime, 60 * 1000 * 10) )
    { return; }

    MsgGetShopCenter* pShop = (MsgGetShopCenter*)pMsg;

    MsgAckGetShopCenter msg;
    msg.header.stID = GetID();    
	
	for (int n =0;n < CTradeCenterInfo::ECD_ParentType_max;n++)
	{
		uint32 count = 0;
		switch(n)
		{
		case CTradeCenterInfo::ECD_ParentType_Jifen:
			count = theTradeCenter.GetJifenItemCount();
			break;
		case CTradeCenterInfo::ECD_ParentType_Bangjin:
			count = theTradeCenter.GetBangjinItemCount();
			break;
		case CTradeCenterInfo::ECD_ParentType_Yuanbao:
			count = theTradeCenter.GetYuanbaoItemCount();
			break;
		default:
			break;
		}

		for ( int i=0; i<count; ++i )
		{
			CTradeCenterInfo::cTradeItem* pNode = theTradeCenter.GetTradeItemByIndex( i,n);
			if ( pNode == NULL )
			{ continue; }

			msg.info[ msg.nCount ].id    = pNode->m_ItemID;
			msg.info[ msg.nCount ].count = pNode->m_Count;
			++msg.nCount;
			if ( msg.nCount>=MsgAckGetShopCenter::eMaxItem)
			{
				msg.CalcLength();
				GettheServer().SendMsgToSingle( &msg, this );
				msg.Reset();
			}
		}

	}
//	theTradeCenter.GetTradeItemCount();
  

    if ( msg.nCount>0)
    {
        msg.CalcLength();
        GettheServer().SendMsgToSingle( &msg, this );
        msg.Reset();
    }

    m_dwReqShopTime = HQ_TimeGetTime();
}

void GamePlayer::OnShopCenterBuy( Msg *pMsg )
{ // 买物品从商城
    MsgShopCenterBuy* pBuy = (MsgShopCenterBuy*)pMsg;
	uint32 OldJinPiao ,NewJinPiao , OldConsumeScore, NewConsumeScore= 0;
    if ( pBuy == NULL || pBuy->ustCount <= 0 )
    { return; }

    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_BuyStoreItem, PasswordDefine::OP_InitAction ) )
    { return;}

    // 检查在商城里面是否有这个物品
    CTradeCenterInfo::cTradeItem* pTradeItem = theTradeCenter.GetTradeItemByItemID( pBuy->ustItemId,pBuy->chType);
    if ( pTradeItem == NULL )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"Error:not this item in shop");
        return;
    }

    ItemDefine::SItemCommon* pItemCommonConfig = GettheItemDetail().GetItemByID( pTradeItem->m_ItemID);
    if ( pItemCommonConfig == NULL )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"物品表里没有ID为: %d 物品", pTradeItem->m_ItemID);
        return;
    }

    MsgAckBuyOrSellGoods msgAck;
    msgAck.header.stID  = GetID();
    msgAck.ustResult    = MsgAckBuyOrSellGoods::error_sucess;
    uint32 jinDingPrice = pTradeItem->m_FinalDiscountPrice * pBuy->ustCount;
    uint32 jinPiaoPrice = pTradeItem->m_TicketPrice * pBuy->ustCount;
	uint32 ConsumeScore = pTradeItem->m_ConsumeScore * pBuy->ustCount;

	uint32 __ConsumeScore = GetConsumeScore();

    if ( GetJinDing() < jinDingPrice || GetJinPiao() < jinPiaoPrice || GetConsumeScore() < ConsumeScore)
    {
        msgAck.ustResult    = MsgAckBuyOrSellGoods::error_money_not_enough; 
        GettheServer().SendMsgToSingle( &msgAck, this);
        return;
    }

    // 没有这么多的量
    if ( pBuy->ustCount > pTradeItem->m_Count)
    {
        msgAck.ustResult = MsgAckBuyOrSellGoods::error_no_stock_item;
        GettheServer().SendMsgToSingle( &msgAck, this );

        MsgRetShopCenterItemCnt Ret;
        Ret.ustCount  = pTradeItem->m_Count;
        Ret.ustItemId = pTradeItem->m_ItemID;
        GettheServer().SendMsgToSingle( &Ret, this );
        return;
    }

    msgAck.ustItemId    = pBuy->ustItemId;
    msgAck.ustPackIndex = -1;
    msgAck.ustCount     = pBuy->ustCount;
    msgAck.bIsBuy       = true;


    ItemBag* pItemBag = GetItemBagByItemType( pItemCommonConfig->ucItemType );
    __int64 nBigId = pItemBag->GetNewItemID();;
    if ( nBigId == InvalidLogicNumber )
    { return; }

    SCharItem stItem;
    if( !theRunTimeData.CreateItem( this, pTradeItem->m_ItemID, pBuy->ustCount , nBigId, stItem ) )
    {
        msgAck.ustResult = MsgAckBuyOrSellGoods::error_system_busy;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return;
    }

    msgAck.ucItemBagType = GetItemBagType( pItemCommonConfig->ucItemType );
    // 加上物品
	if ( jinPiaoPrice > 0 ) //如果使用绑金购买则物品绑定
	stItem.SetBounded( true );

    uint32 nResult = pItemBag->PushItem( stItem, pBuy->ustCount );
    if ( nResult != ierr_Success)
    {
        msgAck.ustResult = MsgAckBuyOrSellGoods::error_additem_fail;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return;
    }

	OldJinPiao = GetJinPiao();
	OldConsumeScore = GetConsumeScore();

    // 扣去钱
    jinDingPrice = jinDingPrice * (g_Cfg.m_nOffSetInShopCenter / 100.0);
    jinPiaoPrice = jinPiaoPrice * (g_Cfg.m_nOffSetInShopCenter / 100.0);
	ConsumeScore = ConsumeScore * (g_Cfg.m_nOffSetInShopCenter / 100.0);



    if ( jinDingPrice > 0)
    { OperateJinDing( EOT_Sub, jinDingPrice, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ShopCenter,false); }

    if ( jinPiaoPrice > 0 )
    { OperateJinPiao( EOT_Sub, jinPiaoPrice, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ShopCenter ); }

	if ( ConsumeScore > 0 )
	{ OperateConsumeScore( EOT_Sub, ConsumeScore, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ShopCenter ); } //后一位默认为true 将写 ConsumeScore 表存积分 并且在 shopping_log 表中写日志


	NewJinPiao = GetJinPiao();
	NewConsumeScore = GetConsumeScore();

    msgAck.nOnlyInt           = nBigId;
    msgAck.bCanUse            = stItem.bCanUse;
    msgAck.n64UseTime         = stItem.itembaseinfo.n64UseTime;
    msgAck.ustResult          = MsgAckBuyOrSellGoods::error_centerbuysuccess;    
    //pTradeItem->m_Count -= pBuy->ustCount;
	msgAck.flag				  = stItem.itembaseinfo.flag;

    msgAck.dwCurMoney    = GetMoney(); 
    GettheServer().SendMsgToSingle( &msgAck, this );

    MsgRetShopCenterItemCnt Ret;
    Ret.ustCount  = pTradeItem->m_Count;
    Ret.ustItemId = pTradeItem->m_ItemID;
    GettheServer().SendMsgToSingle( &Ret, this );

	//同步给DB SERVER在商城购买物品
	if (jinDingPrice > 0)
	{
		DBMsgShopping shopping;
		shopping.header.stID = GetID();
		shopping.account_id  =  GetAccountID();
		shopping.character_id = GetDBCharacterID();
		shopping.cost_money = jinDingPrice;
		shopping.item_count = pBuy->ustCount;
		shopping.item_id = pBuy->ustItemId;
		shopping.Unit_price = pTradeItem->m_FinalDiscountPrice;
		shopping.flag = 0; //0为元宝
		shopping.oldValue = 0;
		shopping.newValue = 0;
		GettheDBCon().SendMsg( &shopping, GetLifeCode() );
	}

	//同步给DB SERVER在商城购买物品 存绑金操作到数据库
	if (jinPiaoPrice > 0) 
	{
		DBMsgShopping shopping;
		shopping.header.stID = GetID();
		shopping.account_id  =  GetAccountID();
		shopping.character_id = GetDBCharacterID();
		shopping.cost_money = jinPiaoPrice;
		shopping.item_count = pBuy->ustCount;
		shopping.item_id = pBuy->ustItemId;
		shopping.Unit_price = pTradeItem->m_FinalDiscountPrice;
		shopping.flag = 1; //绑金
		shopping.oldValue = OldJinPiao;
		shopping.newValue = NewJinPiao;
		GettheDBCon().SendMsg( &shopping, GetLifeCode() );
	}


	if (ConsumeScore > 0) 
	{
		DBMsgShopping shopping;
		shopping.header.stID = GetID();
		shopping.account_id  =  GetAccountID();
		shopping.character_id = GetDBCharacterID();
		shopping.cost_money = ConsumeScore;
		shopping.item_count = pBuy->ustCount;
		shopping.item_id = pBuy->ustItemId;
		shopping.Unit_price = pTradeItem->m_FinalDiscountPrice;
		shopping.flag = 2; //商城积分
		shopping.oldValue = OldConsumeScore;
		shopping.newValue = NewConsumeScore;
		GettheDBCon().SendMsg( &shopping, GetLifeCode() );
	}

    // 记录log
    char szID[60] ={ 0 };
	//"[:T9224]	商城购买物品[%s]INDEX[%d]GUID[%s]数量[%d]花费元宝[%d]花费绑金[%d]"
    Log( theXmlString.GetString(eLog_info_2slk_136), pItemCommonConfig->GetItemName(), pTradeItem->m_ItemID, BigInt2String(stItem.itembaseinfo.nOnlyInt, szID), pBuy->ustCount, jinDingPrice, jinPiaoPrice );
    ShoppingLog( theXmlString.GetString( eLog_info_2slk_136 ), pItemCommonConfig->GetItemName(), pTradeItem->m_ItemID, BigInt2String(stItem.itembaseinfo.nOnlyInt, szID), pBuy->ustCount, jinDingPrice, jinPiaoPrice );
}

void GamePlayer::OnMsgReLive( Msg* pMsg )
{
    if ( !m_xSkillItemRelive.xTimer.CheckStart() )
    { return SendErrorToClient( ER_BeReliveTimeOver ); }

    SReliveInfo xReliveInfo;
    switch ( m_xSkillItemRelive.uchType )
    {
    case MsgAgRelive::useskill:
        {
            ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( m_xSkillItemRelive.nItemID, m_xSkillItemRelive.nValue );
            if ( pSkill == NULL )
            { return; }

            xReliveInfo.nReliveHP = pSkill->fReliveHp * 100;
            if ( xReliveInfo.nReliveHP < 0 || xReliveInfo.nReliveHP > 100 )
                xReliveInfo.nReliveHP = 10;
            xReliveInfo.nReliveMP = pSkill->fReliveMp * 100;
            if ( xReliveInfo.nReliveMP < 0 || xReliveInfo.nReliveMP > 100 )
                xReliveInfo.nReliveMP = 10;
        }
        break;
    case MsgAgRelive::usegoods:
        {
        }
        break;
    default:
        return;
        break;
    }

    ProcessReliveBySkill( xReliveInfo );
}

void GamePlayer::OnMsgChangeMountName( Msg* pMessage )
{   
    MsgChangeMountName* pChange = (MsgChangeMountName*)pMessage;
    if ( pChange == NULL )
        return;

    HelperFunc::CheckStringValid( pChange->szName, sizeof( pChange->szName ) );

    SMountItem* pMountItem = _mountManager.GetMountByIndex( pChange->usIndex );
    if ( !pMountItem )
        return;

    strncpy_s( pMountItem->baseInfo.szName, sizeof(pMountItem->baseInfo.szName), pChange->szName, sizeof(pMountItem->baseInfo.szName)-1);
}

void GamePlayer::OnMsgReturnToCharacterServer( Msg* pMsg )
{
    MsgReturnToCharacterServer* pMessage = (MsgReturnToCharacterServer*)pMsg;
    if ( GetStatus() == CS_WAITRETURNTOCHARACTER )
    { return; }

    GS2CSSwitchStageReq msg;
    msg.header.stID      = GetID();
    msg.nSwitchStageType = SSRT_EnterToCharacterLogin;
    msg.nMapId           = 0;
    msg.fX               = 0;
    msg.fY               = 0;
    msg.fDir             = 0;
    msg.nAccountId       = GetAccountID();
    msg.nCharacterDbId   = GetDBCharacterID();
    msg.dwTime           = HQ_TimeGetTime();
    msg.nServerId        = g_Cfg.dwServerID;
    msg.ustCountryID     = GetCountry();
    GettheServer().SendMsgToCenterServer( &msg );

    SetStatus( CS_WAITRETURNTOCHARACTER );
}

void GamePlayer::OnSwitchSuit( Msg* pMsgParam  )
{       
    if ( HaveFighteFlag(eFighting) )
    { return; }

    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction ) )
    { return;}  // 财产保护下无法卸下装备

    MsgSwitchSuit* pMsg = (MsgSwitchSuit*)pMsgParam;

    gCharInfoServer.visual.ShowAecorative( pMsg->nSuitIndex > 0);

	MsgAckSwitchSuit switchSuit;
	switchSuit.header.stID = GetID();
	switchSuit.nSuitIndex = pMsg->nSuitIndex;
	GettheServer().SendMsgToView( &switchSuit, GetID(), false );

    // 更新人物身上的道具
    SendVisualEquipDataToClient(); 
}

void GamePlayer::OnEquipNew( Msg* pMsg )
{
    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UseItemInBag, PasswordDefine::OP_InitAction ) )
    { return;}  // 财产保护下无法使用包裹中物品

    //// 战斗状态不让穿，修改：战斗状态能换装
    //if ( HaveFighteFlag(eFighting) )
    //{ return; }

    MsgEquip* pEquip = (MsgEquip*)pMsg;
    if ( pEquip == NULL )
    { return; }

    // 是否有这个装备
    SCharItem stItem;
    _NormalItemBag.GetItem( pEquip->ustPackIndex, &stItem );    
    if( stItem.itembaseinfo.ustItemID == InvalidLogicNumber )
    { return; }

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
    if ( pItem == NULL || !pItem->IsCanEquip() )
    { return; }

    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip *)pItem;
    if ( pItemCanEquip == NULL )
    { return; }

    // 玩家成功换上新的装备，并取出旧的装备
    SCharItem* pOldEquipItem = NULL;
    int nWhere = pEquip->nEquipWhere; 
    if ( nWhere == -1 )
    {
        for( int nPartLoop=0; nPartLoop<EEquipPartType_MaxEquitPart; )
        {
            if( IsCanEquip( nPartLoop, &stItem ))
            { // 如果可以装备
                nWhere = nPartLoop;
                if ( nWhere == EEquipPartType_Ring1 || nWhere == EEquipPartType_Bangle1 )
                { // 如果是戒指 或者 手镯 优先填左边
                    SCharItem* pItem1 = GetVisualEquipItem( nWhere );
                    SCharItem* pItem2 = GetVisualEquipItem( nWhere + 1 );

                    // 如果左边有 右边为空 填右边
                    if ( pItem1 != NULL &&  pItem2==NULL) 
                    { nWhere = nPartLoop + 1; }
                }

                pOldEquipItem = GetVisualEquipItem( nWhere );
                break;
            }

            if ( nPartLoop == EEquipPartType_Ring1 || nWhere == EEquipPartType_Bangle1 )
            { nPartLoop += 2; } // 跳过右边所以跳两位
            else
            { ++nPartLoop; } // 其他位置跳一位
        }
    }
    else
    {
        // 不可以装备该位置
        if( !IsCanEquip( pEquip->nEquipWhere, &stItem ))
        { 
            MsgAckEquip msg;
            msg.stResult = MsgAckEquip::Result_Failed;
            GettheServer().SendMsgToSingle( &msg, this );
            return;
        }

        pOldEquipItem = GetVisualEquipItem( nWhere );
    }

    if ( nWhere != -1 )
    { // 如果有适合的位置
        //将装备从背包中取出
        unsigned short ustCount = 1;
        if (ierr_Success == _NormalItemBag.PopItem( pEquip->ustPackIndex, ustCount ))
        {
            Log( theXmlString.GetString(eLog_info_2slk_152),pItem->GetItemName(),pItemCanEquip->ustItemID);

            if( pOldEquipItem != NULL )
            {
                if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction ) )
                { return;}  // 财产保护下无法卸下装备

                //如果有旧的装备，则放回背包内
                Log( theXmlString.GetString(eLog_info_2slk_153),pOldEquipItem->itembaseinfo.ustItemID,ustCount);
                int nSucc = _NormalItemBag.PushItem( *pOldEquipItem, ustCount, pEquip->ustPackIndex);
                if(nSucc != ierr_Success)
                { // 放回背包失败                    
                    Log(theXmlString.GetString(eLog_OnEquip_PushError),stItem.itembaseinfo.ustItemID,1);
                    _NormalItemBag.PushItem( stItem, ustCount, pEquip->ustPackIndex);
                    return;
                }
                
                RemoveEquipItemSkill ( nWhere );
                DeleteVisualEquipItem( nWhere );
            }

            MsgAckEquip msg;
            msg.stResult = MsgAckEquip::Result_Success;
            if ( !Equip( nWhere, stItem, pOldEquipItem != NULL ) )
            {   
                msg.stResult = MsgAckEquip::Result_Failed;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            msg.stResult     = MsgAckEquip::Result_Success;
            msg.ustPackIndex = pEquip->ustPackIndex;
            msg.ustWhere     = nWhere;
            GettheServer().SendMsgToSingle( &msg, this );

            bool bAecorative = (nWhere == EEquipPartType_AecorativeGoods || nWhere == EEquipPartType_AecorativeClothing );

            SendVisualEquipDataToClient();

            //if ( !bAecorative ) //时装也计算属性
            {
                // 有脱的行为
                if ( pOldEquipItem )
                { // 重新算一次
                    UpdateAllEquipData();
                    UpdateAllSuitData() ;
                }
                else
                {
                    //只算加的部分
                    ApplyBaseAttrToFightAttr( false, ECustomDataPart_item, true );
                    UpdateAllSuitData() ;
                }

                ApplyPassiveSkillsToChar();
                RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Equip ); 
            }

            //if ( (bAecorative && gCharInfoServer.visual.IsShowAecorative() )|| (!bAecorative && ! gCharInfoServer.visual.IsShowAecorative()) )
            { // 如果是时装位同时现在是时装show 或者 不是时装位同时现在不是时装show
                // 发消息通知其它player有人换装,某个部件的装备改变了
				//不管什么情况都要发 vvx 2013.6.8
                MsgEquipChanged2 changed;
                changed.header.stID = GetID();
                changed.cWhere      = nWhere;
                SCharItem* pCharItem = GetVisualEquipItem(nWhere);
                if ( pCharItem )
                { changed.equip = *pCharItem;}
                changed.nSuitIndex  = gCharInfoServer.visual.IsShowAecorative();
                GettheServer().SendMsgToView( &changed, GetID(), true );
            }
        }
    }
    else
    {   
        MsgAckEquip msg;
        msg.stResult = MsgAckEquip::Result_Failed;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }
}

void GamePlayer::OnEquipToWhere( Msg* pMsg )
{
    return;

    if (HaveFighteFlag(eFighting))
    { return; }

    MsgEquipToWhere *pEquip = (MsgEquipToWhere*)pMsg;

    SCharItem stItem;
    _NormalItemBag.GetItem( pEquip->ustPackIndex, &stItem );
    if( stItem.itembaseinfo.ustItemID ==InvalidLogicNumber )
    { return; }

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );

    if ( NULL == pItem || !pItem->IsCanEquip() )
    { return; }

    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip *)pItem;
    if ( pItemCanEquip == NULL )
    { return; }

    SCharItem sOldItem;
    //玩家成功换上新的装备，并取出旧的装备（如果有的话）
    int nWhere = -1;
    int nPart = pEquip->ustWhere;
    if( IsCanEquip( nPart, &stItem ) )
    {
        SCharItem* pCharItem = GetVisualEquipItem(nPart);
        if ( pCharItem != NULL )
        { sOldItem = *pCharItem; }

        nWhere = nPart;
    }

    if ( nWhere != -1 )
    {
        //将装备从背包中取出！
        Log(theXmlString.GetString(eLog_info_2slk_150),pItem->GetItemName(),pItem->ustItemID);

        unsigned short ustCount;
        if (_NormalItemBag.PopItem( pEquip->ustPackIndex, ustCount ) == ierr_Success)
        {
            //如果有旧的装备，则放回背包内！
            if( sOldItem.itembaseinfo.ustItemID != InvalidLogicNumber )
            {
                Log(theXmlString.GetString(eLog_info_2slk_151),sOldItem.itembaseinfo.ustItemID,ustCount);

                int nSucc = _NormalItemBag.PushItem( sOldItem, ustCount , pEquip->ustPackIndex);
                if(nSucc != ierr_Success)
                {
                    Log(theXmlString.GetString(eLog_info_2slk_151),stItem.itembaseinfo.ustItemID,ustCount);
                    _NormalItemBag.PushItem( stItem, ustCount);
                    return;
                }
            }

            MsgAckEquip msg;
            msg.stResult = MsgAckEquip::Result_Success;
            if ( !Equip( nWhere, stItem, sOldItem.itembaseinfo.ustItemID != InvalidLogicNumber ) )
            {
                msg.stResult = MsgAckEquip::Result_Failed;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            msg.ustPackIndex = pEquip->ustPackIndex;
            msg.ustWhere = nWhere;
            GettheServer().SendMsgToSingle( &msg, this );

            bool bAecorative = (nWhere == EEquipPartType_AecorativeGoods || nWhere == EEquipPartType_AecorativeClothing );

            SendVisualEquipDataToClient();

            if ( !bAecorative )
            {
                if ( sOldItem.itembaseinfo.ustItemID != InvalidLogicNumber )
                { 
                    UpdateAllEquipData();
                    UpdateAllSuitData() ;
                }
                else
                {
                    ApplyBaseAttrToFightAttr( false, ECustomDataPart_item, true );
                    UpdateAllSuitData() ;
                }

                ApplyPassiveSkillsToChar();
                RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Equip ); 
            }

            //if ( (bAecorative && gCharInfoServer.visual.IsShowAecorative() )|| (!bAecorative && ! gCharInfoServer.visual.IsShowAecorative()) )
            { // 如果是时装位同时现在是时装show 或者 不是时装位同时现在不是时装show
                // 发消息通知其它player有人换装,某个部件的装备改变了
				//不管什么情况都要发 vvx 2013.6.8
                MsgEquipChanged2 changed;
                changed.header.stID = GetID();
                changed.cWhere      = nWhere;
                SCharItem* pCharItem = GetVisualEquipItem(nWhere);
                if ( pCharItem )
                { changed.equip = *pCharItem;}                
                changed.nSuitIndex  = gCharInfoServer.visual.IsShowAecorative();
                GettheServer().SendMsgToView( &changed, GetID(), true );
            }
        }
    }
    else
    {   
        MsgAckEquip msg;
        msg.stResult = MsgAckEquip::Result_Failed;
        GettheServer().SendMsgToSingle( &msg, this );
    }
}

//请求取消技能
void GamePlayer::OnReqCancelSkill( Msg* pMsg )
{ CancelSkill(); }

void GamePlayer::OnQueryServerInfo(Msg* pMsg)
{

    MsgAckQueryServerInfo ack;
    ack.dwOnlineCount = theRunTimeData.GetOnlinePlayer();
    GettheServer().SendMsgToSingle( &ack, this );

}

//请求转身
void    GamePlayer::OnChangeDir(Msg* pMsg)
{

    MsgChangeDir  *pChangeDirMsg = (MsgChangeDir*)pMsg;
    //
    pChangeDirMsg->header.stID = GetControl()->GetID();
    pChangeDirMsg->stNpcID = GetControl()->GetID();
    //
    GettheServer().SendMsgToView( pChangeDirMsg, GetID(), true );

}

//查询角色数据
void GamePlayer::OnQueryCharInfo( Msg *pMsg )
{       
    MsgQueryCharInfo* pQueryInfo = ( MsgQueryCharInfo* )pMsg;
    if ( pQueryInfo == NULL )
    { return; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( pQueryInfo->stChar );
    if( pChar == NULL || pChar->IsIllusionChar() )
    { return; }

    MsgAckCharInfo info;
    info.stChar = pQueryInfo->stChar;
    HelperFunc::SafeNCpy( info.szDisplayName, pChar->GetCharName(), sizeof( info.szDisplayName ) );

    info.stModelID = pChar->GetModelId();
    info.nMp       = pChar->GetMP();
    info.nMpMax    = pChar->GetCharFightAttr()->mpMax.final;
    info.dwSpecialID = pChar->GetSpecialValue();
    GettheServer().SendMsgToSingle( &info, this );

    // 状态发送给客户端
    pChar->SendBuffs( this, true  );

	// 如果是变身镖车状态，让我看到人Player变身
	GamePlayer *pGamePlayer = dynamic_cast<GamePlayer *>(pChar);
	if (pGamePlayer != NULL && pGamePlayer->IsBiaocheState())
	{
		MsgChangeToBiaocheAck msg;
		msg.header.stID = pGamePlayer->GetID();
		msg.monsterID = pGamePlayer->GetProtectCharMonsterId();
		GettheServer().SendMsgToSingle(&msg, this);
	}
}

void GamePlayer::OnReqUpSkill(Msg*pMsg)
{ // 请求升级技能
    MsgReqUpSkill* pUp = (MsgReqUpSkill *)pMsg;
    if ( NULL == pUp)
    { return; }

    unsigned short uSkillId = pUp->stSkillId;
    SCharSkill* pCharSkill = _SkillBag.GetSkillByID( uSkillId );
    if ( !pCharSkill )
    { return; }

    unsigned short ustSkillId = pCharSkill->ustSkillID;
    unsigned short ustLevel   = pCharSkill->stSkillLevel;

    ItemDefine::SItemSkill* pUpSkillItem = GettheItemDetail().GetSkillByID(ustSkillId,ustLevel+1);
    if ( !pUpSkillItem)
    { return; }

    if ( pUpSkillItem->cLearnProfessionReq != -1 && pUpSkillItem->cLearnProfessionReq != GetProfession())//判读职业的需求，和判读是否是属于职业的
    { return; }

    if ( ustLevel >= pUpSkillItem->ustSkillMaxLvl)
    { return; }

    int nLearnLevelReq  = pUpSkillItem->stLearnLevelReq;
    int nMoneyNeed      = pUpSkillItem->stMoneyNeed;
    int nSkillExp       = pUpSkillItem->nLearnNeedExp;

    if (nLearnLevelReq > GetLevel())
    { 
        MsgAckResult msg;
        msg.result = ER_NoLevelToLearnSkill;
        GettheServer().SendMsgToSingle( &msg, this );
        return; 
    }

    if ( nMoneyNeed > GetJiaoZiMoney() )
    { 
        MsgAckResult msg;
        msg.result = ER_NoMoneyToLearnSkill;
        GettheServer().SendMsgToSingle( &msg, this );
        return; 
    }

    if (!IsRecipeSkill(ustSkillId))
    {// 普通技能升级扣除经验
        if (nSkillExp > GetSkillExpUnUsed())
        { 
            MsgAckResult msg;
            msg.result = ER_NoExpToLearnSkill;
            GettheServer().SendMsgToSingle( &msg, this );
            return; 
        }

        uint32 nCurExp = GetSkillExpUnUsed();
        SetSkillExpUnUsed(nCurExp - nSkillExp);
    }
    else
    {// 生活技能升级扣除对应熟练度
        int nType = theRecipeConfig.GetRecipeTypeBySkillId(ustSkillId);
        if (nType < 0 || nType >= ERT_MaxType)
        {
            MsgAckResult msg;
            msg.result = ER_NoPointToLearnSkill;
            GettheServer().SendMsgToSingle( &msg, this );
            return;
        }
        
        int nPoint = GetRecipeSkillPoint(nType);
        if (nSkillExp > nPoint)
        { 
            MsgAckResult msg;
            msg.result = ER_NoPointToLearnSkill;
            GettheServer().SendMsgToSingle( &msg, this );
            return; 
        }

        OperateRecipeSkillPoint( EOT_Sub, ustSkillId, nSkillExp, __FUNCTION__, __LINE__ );
        
        unsigned short which = GetCharAttrByRecipeType( nType );        // 获得类型
        MsgCharAttrChanged msgChanged;
        msgChanged.iChangeCount = 0;
        msgChanged.header.stID = GetID();
        msgChanged.AddAttrShortChange( which, GetRecipeSkillPoint(nType) );
        msgChanged.CaluLength();
        GettheServer().SendMsgToSingle( &msgChanged, this ); 
    }
    
    OperateJiaoZi( EOT_Sub, nMoneyNeed, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_UpSkill);

    ++pCharSkill->stSkillLevel;

    MsgCharSkillLevelup msgSeeCharSkillLevelup;
    msgSeeCharSkillLevelup.header.stID      = GetID();
    msgSeeCharSkillLevelup.ustSkillNewLevel = pCharSkill->stSkillLevel;
    msgSeeCharSkillLevelup.ustSkillID       = pCharSkill->ustSkillID;
    msgSeeCharSkillLevelup.nUnUsedExp       = GetPlayerExpUnUsed();
    GettheServer().SendMsgToView( &msgSeeCharSkillLevelup, GetID(), false );

	//ChangeAttr( CharAttr_ExpNotUsed, GetSkillExpUnUsed(), true );
	ChangeAttr( CharAttr_ExpNotUsed, GetPlayerExpUnUsed(), true );  

    Log(theXmlString.GetString(eLog_info_2slk_60),pUpSkillItem->GetItemName(), pCharSkill->ustSkillID, pCharSkill->stSkillLevel );

    if( pUpSkillItem->stGeneralType == ItemDefine::generaltype_passive )
    { ApplyPassiveSkillsToChar(); }

    RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Skill );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//检包裹相关
void GamePlayer::OnMsgPackageViewReq( Msg* pMsg )
{
    MsgPackageViewReq* pViewReq = (MsgPackageViewReq*) pMsg;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( pViewReq->nItemPackageID );
    if ( pChar == NULL || !pChar->IsItem() )
    {
        if ( pChar != NULL )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "[%s]请求查看包裹时传过来的包裹ID = [%u]是错误的! pChar = [0x%x]", GetCharName(), pViewReq->nItemPackageID, pChar );
        }
        return; 
    }

    ItemCharacter* pItemChar = ( ItemCharacter* ) pChar;
    if ( !IsInMapArea(pItemChar->GetMapID(), pItemChar->GetFloatX(), pItemChar->GetFloatY(), PickAuttonDistance + 1.0f) )
    { return; }             // 距离太远了 

	//zhuxincong 9.28 注释 为了测试 我在不停的动，看是否能正常拾取包裹
  //  if ( !pItemChar->IsOverPackageViewLastTime(GetDBCharacterID()) )        
    //{ return; }             // 点的太快了

    if ( !pItemChar->IsCanViewItemPackage(GetDBCharacterID()) )               
    { return; }             // 没有权限查看包裹

    if ( pItemChar->GetCharItemCount() == 0 )                                 
    { return; }             // 包裹已经空了

    uint16 nPolistItemCount = pItemChar->GetPolistItemCount();
    if ( nPolistItemCount > 0 )       // 有需要丢筛子决定或者队长分配的物品
    {
        uint8 chAssign = pItemChar->GetPackageAssignType();
        switch ( chAssign )
        {
        case AssignMode_Assign:         // 队长分配
            {
                //先找到队长玩家, 如果队长不在有效范围内(包括死亡,掉线) 则由队员丢筛子来决定物品归属
                uint32 dwTeamHeaderID = pItemChar->GetPackageAssignTeamHeaderID();
                GamePlayer* pTeamHeader = theRunTimeData.GetGamePlayerByDBID(dwTeamHeaderID);
                if (pTeamHeader != NULL  && pTeamHeader->IsInMapArea(GetMapID(), GetFloatX(), GetFloatY(), TEAM_EXP_DIS))
                {
                    //队长是有效玩家,否则跳到下面处理, 丢筛子来决定归属
                    if (pItemChar->IsInPackageAccessList(dwTeamHeaderID))
                    {
                        if (GetDBCharacterID() == dwTeamHeaderID)       //只有队长拾取,才弹出分配框
                        {
                            MsgPackageItemNeedToAssign xAssign;
                            xAssign.nItemPackageID = pItemChar->GetID();

                            // 设置能分配给谁
                            ItemCharacter::PickAccessVector vecAccess = pItemChar->GetItemPackageAccessList();
                            for (ItemCharacter::PickAccessVector::iterator iter = vecAccess.begin(); iter != vecAccess.end(); ++iter)
                            {
                                xAssign.AddPackageItemAssignToPlayer(iter->dwPlayerDBID);
                            }

                            // 需要分配的物品
                            for (int i = 0; i < nPolistItemCount; ++i)
                            {
                                SCharItem* pPolistItem = pItemChar->GetPolistItemByIndex(i);
                                if (pPolistItem != NULL)
                                {
                                    xAssign.AddPackageItemNeedToAssign(pPolistItem->itembaseinfo.nOnlyInt);

                                    //队长分配没有超时, 直到物品消失
                                    //pItemChar->AddPackageItemBoultTime(pPolistItem->itembaseinfo.nOnlyInt, HQ_TimeGetTime() + ItemCharacter::ServerBoultTimeOut);
                                }
                            }

                            GettheServer().SendMsgToSingle(&xAssign, pTeamHeader);
                        }

                        break;
                    }
                }
            }
        case AssignMode_Team:               // 队伍分配
        case AssignMode_Random:             // 随即分配
            {
                if (!pItemChar->GetPackageAlreadyBoult())        //如果是第一次打开包裹
                {
                    MsgPackageItemBoultReq xBoultReq;
                    xBoultReq.nItemPackageID = pItemChar->GetID();
                    xBoultReq.nTimeOut = ItemCharacter::ClientBoultTimeOut;            //客户端为30秒
                    for (int i = 0; i < nPolistItemCount; ++i)
                    {
                        SCharItem* pPolistItem = pItemChar->GetPolistItemByIndex(i);
                        if ( pPolistItem != NULL )
                        {
                            xBoultReq.AddPackageItemBoult(*pPolistItem);

                            pItemChar->AddPackageItemBoultTimeOut( pPolistItem->itembaseinfo.nOnlyInt, HQ_TimeGetTime() );
                        }
                    }

                    //发送给所有有效玩家
                    pItemChar->SendMsgToAllPackageEffectPlayer(&xBoultReq);
                    pItemChar->SetPackageAlreadyBoult(true);
                }
            }
            break;
        case AssignMode_FreeMode:
            break;
        default:
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "包裹的分配模式[%u]有错误!", chAssign);
        }

    }

    pItemChar->AddPackageViewTime(GetDBCharacterID());

    //如果掉落方式是散落直接捡取
    if ( pItemChar->GetDropItemType() == PackDropType_Around )
    {
        if ( PickPackageItem( pViewReq->nItemPackageID ) )
        { return; }       
    }

    //回应包裹的物品列表
    MsgPackageViewAck xViewAck;
    xViewAck.nItemPackageID = pItemChar->GetID();

    // 有效玩家个数大于1 ,并且是拥有者打开的包裹, 才需要客户端回消息
    if (!pItemChar->GetPackageViewEnd() && pItemChar->GetItemPackageAccessCount() > 1 && pItemChar->GetPackageHoldPlaerID() == GetDBCharacterID())
    {
        xViewAck.bSendViewEnd = true;
    }

    int nItemCount = pItemChar->GetCharItemCount();
    for (int i = 0; i < nItemCount; ++i)
    {
        SCharItem* pItem = pItemChar->GetCharItemByIndex(i);
        if (pItem == NULL) { continue; }

        uint8 chPickLevel = pItemChar->GetItemPickLevel(pItem->itembaseinfo.nOnlyInt, GetDBCharacterID());
        xViewAck.AddPackageItem( *pItem, chPickLevel | eIPL_View );       // 能打开至少要能看
    }

    GettheServer().SendMsgToSingle(&xViewAck, this);            // 发送给点包裹的玩家
}

void GamePlayer::OnMsgPackageViewEnd( Msg* pMsg )           // 服务器通知其他有效成员可以拾取这个包裹了
{       
    MsgPackageViewEnd* pViewEnd = (MsgPackageViewEnd*) pMsg;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(pViewEnd->nItemPackageID);
    if ( pChar == NULL || !pChar->IsItem() )
    { return; }

    ItemCharacter* pItemChar = ( ItemCharacter* ) pChar;

    pItemChar->ChangePackageAccessAllCanView();
    pItemChar->SetPackageViewEnd();
}

void GamePlayer::OnMsgPackageItemAccessReq( Msg* pMsg )
{
    MsgPackageItemAccessReq* pAccessReq = (MsgPackageItemAccessReq*) pMsg;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(pAccessReq->nItemPackageID);
    if ( pChar == NULL || !pChar->IsItem() )
    { return; }

    ItemCharacter* pItemChar = ( ItemCharacter* ) pChar;

    pItemChar->PackageItemAccessReq(this);
}

void GamePlayer::OnMsgPickPackageItemReq( Msg* pMsg )
{
    MsgPickPackageItemReq* pPickReq = (MsgPickPackageItemReq*) pMsg;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( pPickReq->nItemPackageID );
    if ( pChar == NULL || !pChar->IsItem() )
    { return; }

    ItemCharacter* pItemChar = ( ItemCharacter* ) pChar;
    //if (!pItemChar->IsCanViewItemPackage(GetDBCharacterID()))
    //{
    //    return;             //都不能查看包裹 不能拾取
    //}

    std::vector<__int64> vecPickItem;
    if (pPickReq->bAllPick) // 全部拾取
    {
        //得到所有能检的物品
        pItemChar->GetCharItemList( vecPickItem );
    }
    else
    {
        vecPickItem.push_back( pPickReq->nItemID );
    }

    Log( theXmlString.GetString( eLog_PickPackage ), pItemChar->GetPackageDropType() );

	bool TeamCheckOk =false;  //lyh 添加下面4行，解决队伍中只有主角1个人的时候，可以直接全部获取掉落中的所有物品，不需要 请求需求了
	GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
	if (pTeam)
	{
		TeamCheckOk = (pTeam->TeamMemberCount() == 1);
	}

    std::vector<__int64>::iterator end = vecPickItem.end();
    for (std::vector<__int64>::iterator iter = vecPickItem.begin(); iter != end; ++iter)
    {
        //先判断这个东西在不在
        SCharItem* pItem = pItemChar->GetCharItem( *iter );
        if (pItem == NULL)
        {
            MsgPickPackageItemAck xPickAck;
            xPickAck.nItemPackageID = pPickReq->nItemPackageID;
            xPickAck.nItemID        = *iter;
            xPickAck.nResult        = MsgPickPackageItemAck::Result_AlreadyPick;
            GettheServer().SendMsgToSingle(&xPickAck, this);
            continue;
        }

        //判断权限
        if (!pItemChar->IsCanPickUpItem(*iter, GetDBCharacterID()) && !TeamCheckOk)
        {
            MsgPickPackageItemAck xPickAck;
            xPickAck.nItemPackageID = pPickReq->nItemPackageID;
            xPickAck.nItemID        = *iter;
            xPickAck.nResult        = MsgPickPackageItemAck::Result_NoPurview;
            GettheServer().SendMsgToSingle(&xPickAck, this);
            continue;
        }

        uint16 nItemCount = pItem->itembaseinfo.ustItemCount;
        short nResult = AddItemToBag( *pItem, nItemCount, EIGS_DropItem, 3, pItemChar->GetDropMonsterID() );
        switch( nResult )
        {
        case ierr_Success:                  // 检完了
            {
                MsgPickPackageItemAck xPickAck;
                xPickAck.nItemPackageID = pPickReq->nItemPackageID;
                xPickAck.nItemID        = *iter;
                xPickAck.nItemCount     = pItem->itembaseinfo.ustItemCount;
                xPickAck.nResult        = MsgPickPackageItemAck::Result_Success;
                GettheServer().SendMsgToSingle(&xPickAck, this);

                GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
                if ( pTeam != NULL )          // 有队伍
                {
                    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
                    if ( pItemCommon != NULL && pItemCommon->ustLevel >= pTeam->GetTeamAssignItemLevel() )
                    {
                        //大于品质以上物品,通知其他玩家
                        MsgTellPickPackageItem xPickItem;
                        xPickItem.xItem = *pItem;
                        HelperFunc::SafeNCpy(xPickItem.szPlayerName, GetCharName(), sizeof(xPickItem.szPlayerName));

                        pItemChar->SendMsgToAllPackageEffectPlayer( &xPickItem, GetDBCharacterID() );
                    }
                }

                pItemChar->RemoveCharItem( pItem->itembaseinfo.nOnlyInt, pItem->itembaseinfo.ustItemCount );
            }
            break;
            //case ierr_notallitempushed:         //没有检完
            //    {
            //        MsgPickPackageItemAck xPickAck;
            //        xPickAck.nItemPackageID = pPickReq->nItemPackageID;
            //        xPickAck.nItemID        = pPickReq->nItemID;
            //        xPickAck.nItemCount     = pItem->itembaseinfo.ustItemCount;
            //        xPickAck.nResult        = MsgPickPackageItemAck::Result_Success;

            //        GettheServer().SendMsgToSingle(&xPickAck, this);

            //        pItemChar->RemoveCharItem(pItem->itembaseinfo.nOnlyInt, pItem->itembaseinfo.ustItemCount);
            //    }
            //    break;
        }
    }
}

void GamePlayer::OnMsgPackageItemBoultAck( Msg* pMsg )
{
    MsgPackageItemBoultAck* pBoultAck = (MsgPackageItemBoultAck*) pMsg;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(pBoultAck->nItemPackageID);
    if ( pChar == NULL || !pChar->IsItem() )
    { return; }

    ItemCharacter* pItemChar = ( ItemCharacter* ) pChar;

    //SCharItem* pItem = pItemChar->GetCharItem(pBoultAck->nItemID);
    //if (pItem == NULL)          //要投筛子的物品一定要存在哦
    //{
    //    return;
    //}

    if (!pItemChar->IsPolistItem(pBoultAck->nItemID))       // 已经不是需要分配的物品了
    {
        return;
    }

    if (pBoultAck->nResult == MsgPackageItemBoultAck::Boult_Abandon)
    {
        pItemChar->AddPackageItemBoult(pBoultAck->nItemID, GetDBCharacterID(), 0);      //放弃 给他 0 点数
    }
    else
    {
        int nRand = ( theRand.rand32() % RAND_NUM + 1);         // 1 - 100 之间
        pItemChar->AddPackageItemBoult(pBoultAck->nItemID, GetDBCharacterID(), nRand);
    }

    if (pItemChar->IsAllPackageItemBoult(pBoultAck->nItemID))           //全部人都丢筛子了
    {
        pItemChar->PackageItemBoultEnd(pBoultAck->nItemID);   
    }
}

void GamePlayer::OnMsgPackageItemAssignReq( Msg* pMsg )
{
    MsgPackageItemAssignReq* pAssignReq = (MsgPackageItemAssignReq*) pMsg;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(pAssignReq->nItemPackageID);
    if ( pChar == NULL || !pChar->IsItem() )
    { return; }

    ItemCharacter* pItemChar = ( ItemCharacter* ) pChar;

    if (!pItemChar->IsPolistItem(pAssignReq->nItemID))       // 已经不是需要分配的物品了
    { return; }

    if (GetDBCharacterID() != pItemChar->GetPackageAssignTeamHeaderID())        //自己没权利分配
    { return; }

    if (!pItemChar->IsInPackageAccessList(pAssignReq->dwPlayerID))
    { return; }         // 不是有权限分配物品的玩家

    SCharItem* pItem = pItemChar->GetCharItem(pAssignReq->nItemID);
    if (pItem == NULL)          //物品一定要存在哦
    { return; }

    MsgPackageItemAssignAck xAssignAck;
    xAssignAck.nItemPackageID = pAssignReq->nItemPackageID;
    xAssignAck.dwPlayerID     = pAssignReq->dwPlayerID;
    xAssignAck.xItem          = *pItem;

    GamePlayer* pHoldPlayer = theRunTimeData.GetGamePlayerByDBID(pAssignReq->dwPlayerID);
    //有效玩家才分配
    if (pHoldPlayer != NULL && pHoldPlayer->IsInMapArea(pItemChar->GetMapID(), pItemChar->GetFloatX(), pItemChar->GetFloatY(), TEAM_EXP_DIS))
    {
        pItemChar->SetItemHoldByPlayer(pAssignReq->nItemID, pAssignReq->dwPlayerID);
        pItemChar->RemovePolistItem(pAssignReq->nItemID);        //在优质物品列表中删除

        short nResult = pHoldPlayer->AddItemToBag( *pItem, pItem->itembaseinfo.ustItemCount, EIGS_DropItem, 3, pItemChar->GetDropMonsterID() );
        if (nResult == ierr_Success)        //添加成功以后,删除包裹中的这个物品
        {
            pItemChar->RemoveCharItem(pAssignReq->nItemID, pItem->itembaseinfo.ustItemCount);
            xAssignAck.bRemove = true;
        }
        HelperFunc::SafeNCpy(xAssignAck.szPlayerName, pHoldPlayer->GetCharName(), sizeof(xAssignAck.szPlayerName));
    }
    else
    {
        xAssignAck.SetAssignResult(MsgPackageItemAssignAck::Result_Fail);
    }

    if (xAssignAck.chAssignResult == MsgPackageItemAssignAck::Result_Success)
    {
        pItemChar->SendMsgToAllPackageEffectPlayer(&xAssignAck);
    }
    else
    {
        GettheServer().SendMsgToSingle(&xAssignAck, this);      //失败只发给队长
    }
}

void GamePlayer::OnUseGoods( Msg* pMsg )
{ // 使用物品

    MsgUseGoods* pUseGoods = (MsgUseGoods*)pMsg;

    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UseItemInBag, PasswordDefine::OP_InitAction ) )
    { return;}  // 财产保护下无法使用物品

    if( m_bHitchMoving )
    {        
        ShowInfo( false, 271, theXmlString.GetString(eClient_CantUseGood_ByDiffState) );
        return;
    }

    if (!_buffManager.IsCanUseItem())
    { return; }

    if ( IsOpenStall() )
    { return; }

    SCharItem* pCharItem = NULL;
    ItemBag* pItemBag = NULL;
    switch ( pUseGoods->ucItemBagType )
    {
    case BT_NormalItemBag:
        {
            pCharItem = _NormalItemBag.GetItemByIndex( pUseGoods->ustItemIndex );
            pItemBag  = &_NormalItemBag;
        }
        break;
    case BT_MaterialBag:
        {
            pCharItem = _MaterialItemBag.GetItemByIndex( pUseGoods->ustItemIndex );
            pItemBag  = &_MaterialItemBag;
        }
        break;
    case BT_TaskBag:
        {
            pCharItem = _TaskItemBag.GetItemByIndex( pUseGoods->ustItemIndex );
            pItemBag  = &_TaskItemBag;
        }
        break;
    default:
        return;
    }

    if ( pCharItem == NULL || pItemBag == NULL )
    { return; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if( pItemCommon == NULL )
    { return; }

    if ( pCharItem->itembaseinfo.nOnlyInt != pUseGoods->nGuid )
    {
        pItemBag->CleanUp();
        //Log( "使用了错误的guid物品[%s][%I64u] != [%I64u]", pItemCommon->GetItemName(), pCharItem->itembaseinfo.nOnlyInt, pUseGoods->nGuid );
		Log( theXmlString.GetString(eServerLog_UseItemError), pItemCommon->GetItemName(), pCharItem->itembaseinfo.nOnlyInt, pUseGoods->nGuid );
        return;
    }

    if( pCharItem->IsOverdue() )
    {
        ShowInfo( false, 271, theXmlString.GetString(eClient_AddInfo_2slk_53) );
        return;
    }
	
	if (GetScriptMgr()->GetVMByDstId(ST_USE_ITEM,pItemCommon->ustItemID) 
		&&GetScript() && GetScript()->thread.IsHangup())
	{
		ShowInfo( false, 271, theXmlString.GetString(eClient_CantUseGood_ByDiffState) );
		return;
	}
	
    switch ( pItemCommon->byUserTarget )
    {
    case ItemDefine::eTargetMount:
        { // 坐骑
            _ProcessUseItemToMount( (MsgUseGoodsToMount*)pUseGoods, pCharItem, pItemCommon );
        }
        break;
    case ItemDefine::eTargetFriend:
        {
            _ProcessUseItemToFriend( pUseGoods, pItemBag, pCharItem, pItemCommon );
        }
        break;
    case ItemDefine::eTargetPet:
        {
            _ProcessUseItemToPet( (MsgUseGoodsToPet*)pUseGoods, pCharItem, pItemCommon );
        }
    default:
        {
            _ProcessUseItemToChar( pUseGoods, pCharItem, pItemCommon );
        }
        break;
    }
}

void GamePlayer::OnChangePKFlag( Msg* pMsg )
{
    MsgChangePKFlag* flag = (MsgChangePKFlag*)pMsg;
    SetPKMode( flag->shFlag, BV_SendMessage );
}

void GamePlayer::OnMsgChangeProtectLockTimeReq( Msg* pMsg )
{
    MsgChangeProtectLockTimeReq* pReq = (MsgChangeProtectLockTimeReq*) pMsg;

    MsgChangeProtectLockTimeAck xAck;

    if ( pReq->chTime == 0 || pReq->chTime == gCharInfoServer.otherdata.chProtectLockTime )
    {
        xAck.chResult = MsgChangeProtectLockTimeAck::Result_Fail;
    }
    else
    {
        gCharInfoServer.otherdata.chProtectLockTime = pReq->chTime;
    }

    GettheServer().SendMsgToSingle( &xAck, this );
}

bool GamePlayer::OnMsgInviterResult( Msg* pMsg )
{// 以后将邀请动作记在任务身上
    //MsgReferInviteResult* pReq = (MsgReferInviteResult*)pMsg;

    //// 邀请人是否还在线 (邀请好友时,可能在其他服务器, 这个时候需要在其他服判断邀请记录
    //GamePlayer* pInviter = theRunTimeData.GetGamePlayerByDBID( pReq->nInviteId );

    //// 是否有这个邀请纪录
    //InviteProxy::InviteLetter* pLetter = InviteProxy::Instance().getInviterLeter( pReq->nInviteId, GetDBCharacterID(), pReq->cInviteType );
    //if ( !pLetter)
    //    return false;

    ////相依相偎
    //if ( pLetter->type == InviteProxy::InviteLetter::ILT_EMBRACE)
    //{
    //    InviteProxy::Instance().ProcessEmbraceResult( this, pReq );
    //    InviteProxy::Instance().deleteLetter( pReq->nInviteId, GetDBCharacterID(), pReq->cInviteType );
    //    return true;
    //}

    //// 是否真的是受邀人
    //if ( pLetter->invitee != GetDBCharacterID() )
    //    return false;

    //// 是否是有限的验证码
    //if ( pLetter->sn != pReq->nSn )
    //    return false;

    //InviteProxy::Instance().deleteLetter( pReq->nInviteId, GetDBCharacterID(), pReq->cInviteType );
    return true;        
}


void GamePlayer::OnMsgLuckRewardReq( Msg* pMsg )
{
    MsgLuckRewardReq* pLuckReq = ( MsgLuckRewardReq* ) pMsg;

    bool bIsTeam = ( GetTeamID() != TeamDefine::NoneSessionID );
    if ( bIsTeam )              // 队伍情况 只有队长能操作
    {
        GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
        if ( pTeam == NULL || !pTeam->IsInTeam( GetDBCharacterID() ) )
        { return; }

        if ( !pTeam->IsTeamHeader( GetDBCharacterID() ) )
        { return; }
    }

    LuckReward* pLuckReward = GetLuckReward( bIsTeam );
    if ( pLuckReward == NULL )
    { return; }

    switch( pLuckReq->uchType )
    {
    case MsgLuckRewardReq::ECD_Start:   // 客户端开始转
        {
            StartLuckReward( pLuckReward, bIsTeam );    
        }
        break;
    case MsgLuckRewardReq::ECD_Luck:    // 客户端停止,服务器处理逻辑
        {
            RunLuckReward( pLuckReward, bIsTeam );      
        }
        break;
    case MsgLuckRewardReq::ECD_Get:     // 客户端请求领取物品 
        {
            ProcessReceiveLuckReward( pLuckReward, bIsTeam, true );
        }
        break;
    case MsgLuckRewardReq::ECD_Close:   // 关闭窗口( 服务器清除状态 )
        {
            ProcessReceiveLuckReward( pLuckReward, bIsTeam, false );
        }
        break;
    default:
        break;
    }
}

void GamePlayer::OnMsgSplitItem(Msg* pMsg)
{
    MsgAckReduceItem* pMessage = (MsgAckReduceItem*)pMsg;

    SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( pMessage->index );
    if ( pEquipItem == NULL )
    {
        MsgAckResult msg;
        msg.result = ER_SplitItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->itembaseinfo.nOnlyInt != pMessage->guid )
    {
        MsgAckResult msg;
        msg.result = ER_SplitItemIndexGuidError;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 锁定的物品不能拆分
    if ( pEquipItem->IsLock() )
    {
        MsgAckResult msg;
        msg.result = ER_SplitItemCantBeSplit;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

	bool IsBiunded = pEquipItem->IsBounded();

    ItemDefine::SItemCommon* pItemCommonConfig = GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemCommonConfig == NULL )
    { return; }

    // 装备是否分解
    if ( GettheItemDetail().IsCanSplitItem(pEquipItem->itembaseinfo.ustItemID) != ER_Success)
    {
        MsgAckResult msg;
        msg.result = ER_SplitItemCantBeSplit;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    MsgReqReduceItem msg;
    msg.header.stID = GetID();


    SplitItemConfig::SProductItem* pProductItem = theItemSplitConfig.GetSplitItemProduct( pItemCommonConfig->ustItemID );
    if ( pProductItem == NULL )
    {   
        MsgAckResult msg;
        msg.result = ER_SplitItemProductNotExit;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    ItemDefine::SItemCommon* pProductItemConfig = GettheItemDetail().GetItemByID( pProductItem->id );
    if ( pProductItemConfig == NULL )
    { return; }

	SCharItem stItem;
    if ( !theRunTimeData.CreateItem( this, pProductItem->id, pProductItem->count, HelperFunc::CreateID(), stItem ) )
    { 
        MsgAckResult msg;
        msg.result = ER_SplitItemCreateFail;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }
	stItem.SetBounded(IsBiunded);

	unsigned short SplitItemID = pEquipItem->itembaseinfo.ustItemID;

	if ( !RemoveItem( BT_NormalItemBag, pMessage->index, 1, pMessage->guid ) )
	{   
		MsgAckResult msg;
		msg.result = ER_SplitItemPopFail;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

    uint8 productItemBagType = GetItemBagType( pProductItemConfig->ucItemType );
	ItemBag* pItemBag = GetItemBagByItemType( pProductItemConfig->ucItemType );
    uint32 result = pItemBag->PushItem( stItem, stItem.itembaseinfo.ustItemCount );
    if ( result != ierr_Success )
    {
        MsgAckResult msg;
        msg.result = ER_SplitItemPushFail;
        msg.value  = result;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    msg.index       = pMessage->index;
    msg.guid        = pMessage->guid;
    msg.product     = stItem;
    msg.itemBagType = productItemBagType;
    msg.result      = MsgReqReduceItem::eSuc;
    GettheServer().SendMsgToSingle( &msg, this );

   SCharItem* _CharItem = pItemBag->GetItemByIndex(pMessage->index);
   if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),SplitItemID,1,pMessage->guid,
	   _CharItem?_CharItem->GetItemCount():0,eItemLogInfo_ItemConsume_Decompose,GetCharName(),pItemCommonConfig->GetItemName()))	
   {
	   char szID[60] = {0};
	   Log( theXmlString.GetString(eLog_info_2slk_118),SplitItemID,BigInt2String(pMessage->guid, szID ));
	   Log( theXmlString.GetString(eLog_info_2slk_119),stItem.itembaseinfo.ustItemID , BigInt2String(stItem.itembaseinfo.nOnlyInt,szID));
   }
   // 获得分解的物品 log
   theLogEventService.LogItemGain(GetAccountID(),GetDBCharacterID(),stItem.GetItemID(),stItem.itembaseinfo.ustItemCount,stItem.GetItemGuid(),EIGS_Decompose,GetCharName(),pProductItemConfig->GetItemName());
}

void GamePlayer::OnMsgTreasureBoxReq( Msg* pMsg )
{
    MsgTreasureBoxReq* pReq = static_cast< MsgTreasureBoxReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    SCharItem* pBoxCharItem = NULL;
    switch ( pReq->ucBoxItemBagType )
    {
    case BT_NormalItemBag:
        pBoxCharItem = _NormalItemBag.GetItemByIndex( pReq->stBoxIndex );
        break;
    case BT_MaterialBag:
        pBoxCharItem = _MaterialItemBag.GetItemByIndex( pReq->stBoxIndex );
        break;
    default:
        return;
    }

    if ( pBoxCharItem == NULL || pBoxCharItem->itembaseinfo.nOnlyInt != pReq->nBoxGuid )
    { return; }

    ItemDefine::SItemCommon* pBoxItemCommon = GettheItemDetail().GetItemByID( pBoxCharItem->itembaseinfo.ustItemID );
    if ( pBoxItemCommon == NULL || pBoxItemCommon->ucItemType != ItemDefine::ITEMTYPE_TREASUREBOX )
    { return; }
    ItemDefine::SItemTreasureBox* pItemTreasureBox = static_cast< ItemDefine::SItemTreasureBox* >( pBoxItemCommon );
    if ( pItemTreasureBox == NULL )
    { return; }

    switch ( pReq->uchOperate )
    {
    case MsgTreasureBoxReq::ECD_Type_Luck:  // 摇奖
        {
            if ( pItemTreasureBox->uchBoxType != ItemDefine::SItemTreasureBox::BoxType_Luck || pItemTreasureBox->ustNewItemID == 0 )
            { return; }

            if( pBoxCharItem->itembaseinfo.value1 != 0 )
            { return; }

            // 判断是否有钥匙
            SCharItem* pKeyCharItem = NULL;
            switch ( pReq->ucKeyItemBagType )
            {
            case BT_NormalItemBag:
                pKeyCharItem = _NormalItemBag.GetItemByIndex( pReq->stKeyIndex );
                break;
            case BT_MaterialBag:
                pKeyCharItem = _MaterialItemBag.GetItemByIndex( pReq->stKeyIndex );
                break;
            default:
                return;
            }

            if ( pKeyCharItem == NULL || pKeyCharItem->itembaseinfo.nOnlyInt != pReq->nKeyGuid )
            { return; }     // guid不一样

            ItemDefine::SItemCommon* pKeyItemCommon = GettheItemDetail().GetItemByID( pKeyCharItem->itembaseinfo.ustItemID );
            if ( pKeyItemCommon == NULL || pKeyItemCommon->ucItemType != ItemDefine::ITEMTYPE_TREASUREBOX )
            { return; }     // 不是宝箱类型
            ItemDefine::SItemTreasureBox* pItemTreasureKey = static_cast< ItemDefine::SItemTreasureBox* >( pKeyItemCommon );
            if ( pItemTreasureKey == NULL || pItemTreasureKey->uchBoxType != ItemDefine::SItemTreasureBox::BoxType_BoxKey )        
            { return; }     // 不是开箱子的钥匙

            if ( pItemTreasureBox->uchLevel != pItemTreasureKey->uchLevel )
            { return; }     // 箱子和钥匙等级不匹配

            if ( pItemTreasureBox->ustCorrItemID != pKeyCharItem->itembaseinfo.ustItemID )
            { return; }     // 箱子需要的钥匙ID 不匹配

            unsigned char uchIndex = theTreasureBoxConfig.GetRandTreasureData( pItemTreasureBox->uchLevel, pItemTreasureBox->ustNewItemID, theRand.rand32() );
            if ( uchIndex == -1 )
            { return; }

            const TreasureData* pTreasureData = theTreasureBoxConfig.GetTreasureData( pItemTreasureBox->uchLevel, pItemTreasureBox->ustNewItemID, uchIndex );
            if ( pTreasureData == NULL )
            { return; }

            // 判断阈值, 如果不产出, 就用设定的那个物品
            if ( !theDropItemManager.CheckItemCanDrop( pTreasureData->GetItemID(), pTreasureData->GetCount() ) )
            {
                uchIndex = theTreasureBoxConfig.GetSpecificValue( pItemTreasureBox->uchLevel, pItemTreasureBox->ustNewItemID );
                if ( uchIndex >= TreasureData::GetMaxIndex() )
                { return; }     // 数据错误 不能出

                // 重新获得宝箱属性
                pTreasureData = theTreasureBoxConfig.GetTreasureData( pItemTreasureBox->uchLevel, pItemTreasureBox->ustNewItemID, uchIndex );
                if ( pTreasureData == NULL )
                { return; }
            }

            pBoxCharItem->itembaseinfo.ustItemID = pItemTreasureBox->ustNewItemID;
            pBoxCharItem->itembaseinfo.value1    = pItemTreasureBox->uchLevel;   // 把箱子等级存入value1中
            pBoxCharItem->itembaseinfo.value2    = uchIndex;                     // 把箱子摇奖得到的索引存入value2中

            // 通知客户端结果
            MsgTreasureBoxResult xResult;
            xResult.ucItemBagType  = pReq->ucBoxItemBagType;
            xResult.nGuid          = pBoxCharItem->itembaseinfo.nOnlyInt;
            xResult.stIndex        = pReq->stBoxIndex;
            xResult.uchLevel       = pItemTreasureBox->uchLevel;
            xResult.uchResultIndex = uchIndex;        
            xResult.nNewItemID     = pItemTreasureBox->ustNewItemID;
            GettheServer().SendMsgToSingle( &xResult, this );

            // 把钥匙删除掉
            unsigned short ustCount = pKeyCharItem->itembaseinfo.ustItemCount;
            RemoveItem( pReq->ucKeyItemBagType, pReq->stKeyIndex, ustCount, pReq->nKeyGuid );

			ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pTreasureData->GetItemID() );
			if ( pItemCommon != NULL )
			{
				//LYH日志添加 
				
				SCharItem *_item = GetBagItemByGuid(pReq->nKeyGuid);
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),pKeyCharItem->itembaseinfo.ustItemID,ustCount,pReq->nKeyGuid,
					_item?_item->GetItemCount():0,eItemLogInfo_ItemConsume_UseLuck,
					GetCharName(),pBoxItemCommon->GetItemName());

				//Log( "删除了[%d]级宝箱钥匙[ID:%I64u, 数量:%d]", pItemTreasureKey->uchLevel, pReq->nKeyGuid, ustCount );

				// 记录LOG


				Log( theXmlString.GetString( eLog_OpenTreasureBox ), pBoxItemCommon->GetItemName(), pBoxCharItem->GetItemID(), pBoxCharItem->GetItemGuid(),  pItemCommon->GetItemName(), pTreasureData->GetCount() );
			}
        }
        break;
    case MsgTreasureBoxReq::ECD_Type_Receive:  // 领取
        {
            if ( pItemTreasureBox->uchBoxType != ItemDefine::SItemTreasureBox::BoxType_Receive )
            { return; }     // 不是领取物品的箱子

            if( pBoxCharItem->itembaseinfo.value1 == 0 )
            { return; }     // 还没有摇奖的箱子

            const TreasureData* pTreasureData = theTreasureBoxConfig.GetTreasureData( pBoxCharItem->itembaseinfo.value1, pBoxCharItem->itembaseinfo.ustItemID, pBoxCharItem->itembaseinfo.value2 );
            if ( pTreasureData == NULL )
            {
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "宝箱配置档里找不到等级[%d] ID = [%d]的第[%d]个奖励", pBoxCharItem->itembaseinfo.value1, pBoxCharItem->itembaseinfo.ustItemID, pBoxCharItem->itembaseinfo.value2 );
                return;
            }

            __int64 nGuild = 0;
            uint16 ustItemID = pBoxCharItem->GetItemID();
            if ( AddItem( pTreasureData->GetItemID(), pTreasureData->GetCount(), EIGS_TreasureBox, true, &nGuild ) == ierr_Success )
            {
                unsigned short ustCount = pBoxCharItem->itembaseinfo.ustItemCount;
                RemoveItem( pReq->ucBoxItemBagType, pReq->stBoxIndex, ustCount, pReq->nBoxGuid );

				//LYH日志添加 摇奖领取
				SCharItem *_pitem = GetBagItemByGuid(pReq->nBoxGuid);
				 ItemDefine::SItemCommon* _item = GettheItemDetail().GetItemByID(ustItemID);
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),pBoxCharItem->itembaseinfo.ustItemID,ustCount,pReq->nKeyGuid,
					_pitem?_pitem->GetItemCount():0,eItemLogInfo_ItemConsume_UseLuck,
					                             GetCharName(),_item->GetItemName());

                //Log( "领取后删除了[%d]级宝箱[ID:%u, GUID:%I64u, 数量:%d]", pItemTreasureBox->uchLevel, ustItemID, pReq->nBoxGuid, ustCount );
              
                // 判断是否要广播
                if ( pTreasureData->GetNoticeWorld() )
                {
                    ItemDefine::SItemCommon* pNewItemCommon = GettheItemDetail().GetItemByID( pTreasureData->GetItemID() );
                    if ( pNewItemCommon == NULL )
                    { return; }

                    MsgChat chat(MsgChat::CHAT_TYPE_PROGRAM_SYSTEM);
                    chat.type = GetItemBagType( pNewItemCommon->ucItemType );
                    chat.nHyberItemCnt = 1;
                    chat.onlyId[0] = nGuild;
                    chat.itemId[0] = pTreasureData->GetItemID();

                    Common::_tstring strName = pNewItemCommon->GetItemName();
                    ReplaceSpecifiedName( pNewItemCommon->ustLevel, strName );

                    char szBuff[256] = { 0 };
                    sprintf_s( szBuff, sizeof( szBuff ) - 1,theXmlString.GetString( eText_OpenTreasureBox ), GetCharName(), pItemTreasureBox->GetItemName(), strName.c_str(), pTreasureData->GetCount() );

                    ProcessSystem( szBuff, SystemWorld, &chat );
                }
            }
        }
        break;
    default:
        return;
    }
}

uint32 GetResultByPlatformQueryType( uint32 queryType )
{
    switch ( queryType )
    {
    case ECT_XinShouCard:
        return ER_XinShouCardAbout;
    case ECT_17173Card:
        return ER_17173CardAbout;
    case ECT_ZhiZunCardLevel:
        return ER_ZhiZunCardLevelAbout;
    case ECT_ZhiZunVipGift:
        return ER_ZhiZunVipGiftAbout;
    case ECT_HuiGuiGift:
        return ER_HuiGuiGiftAbout;
    case ECT_ChongZhiFirstGift:
        return ER_ChongZhiGiftAbout;
    case ECT_ChongZhiBackGift:
        return ER_ChongZhiBackGiftAbout;
    }

    return ER_Failed;
}

uint16 GetTargetIdByPlatformQueryType( uint32 queryType, uint32 value )
{
    // 只有 ECT_ZhiZunCardLevel 是tileId 其他都是 itemId
    uint16 targetId = InvalidLogicNumber;
    switch ( queryType )
    {
    case ECT_XinShouCard:
        {
            switch( value )
            {
            case 1:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_TTJYLK ); }
                break;
            case 2:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_TTJYLK_1 ); }
                break;
            }
        }
        break;
    case ECT_17173Card:
        {
            targetId = theDataCenter.GetItemSymbol( AN_LIC_17173TQK );
        }
        break;
    case ECT_ZhiZunCardLevel:
        {
            targetId = theDataCenter.GetTileSymbol( value );
        }
        break;
    case ECT_ZhiZunVipGift:
        {
            switch( value )
            {
            case 1:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_ZZVIP1 ); }
                break;
            case 2:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_ZZVIP2 ); }
                break;
            case 3:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_ZZVIP3 ); }
                break;
            case 4:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_ZZVIP4 ); }
                break;
            case 5:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_ZZVIP5 ); }
                break;
            case 6:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_ZZVIP6 ); }
                break;
            }
        }
        break;
    case ECT_HuiGuiGift:
        {
            switch( value )
            {
            case 1:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_QQBH ); }
                break;
            case 2:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_BHBG ); }
                break;
            }
        }
        break;
    case ECT_ChongZhiFirstGift:
        {
            targetId = theDataCenter.GetItemSymbol( AN_LIC_SCCZLB );
        }
        break;
    case ECT_ChongZhiBackGift:
        {
            switch( value )
            {
            case 1:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_30CZLB ); }
                break;
            case 2:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_100CZLB ); }
                break;
            case 3:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_300CZLB ); }
                break;
            case 4:
                { targetId = theDataCenter.GetItemSymbol( AN_LIC_1000CZLB ); }
                break;
            }

        }
        break;
    }

    return targetId;
}

void GamePlayer::OnDrawFromPlatformAck( Msg* pMsg )
{
    CS2GSDrawFromPlatformAck* pMessage = (CS2GSDrawFromPlatformAck*) pMsg;
    switch ( pMessage->drawType )
    {
    case ECT_XinShouCard:
    case ECT_17173Card:
    case ECT_ZhiZunVipGift:
    case ECT_HuiGuiGift:
    case ECT_ChongZhiFirstGift:
    case ECT_ChongZhiBackGift:
        {
            uint32 valueAbout = GetResultByPlatformQueryType( pMessage->drawType );
            if ( ESR_NotExist == pMessage->result || ESR_HaveGet == pMessage->result )
            { // 不存在
                MsgAckResult msg;
                msg.result = valueAbout;
                msg.value  = pMessage->result;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            uint16 itemId = GetTargetIdByPlatformQueryType( pMessage->drawType, pMessage->result );
            if ( itemId == InvalidLogicNumber )
            { 
                MsgAckResult msg;
                msg.result = valueAbout;
                msg.value  = ESR_ResourceFail;
                GettheServer().SendMsgToSingle( &msg, this );
                return; 
            }

            ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( itemId );
            if( pItemDetail == NULL )
            { 
                MsgAckResult msg;
                msg.result = valueAbout;
                msg.value  = ESR_ResourceFail;
                GettheServer().SendMsgToSingle( &msg, this );
                return; 
            }

            uint16 nCount = 1;
            __int64 n64Guid = 0;
            if ( AddItem( itemId, nCount, EIGS_FromPlat, true, &n64Guid ) != ierr_Success )
            {
                MsgAckResult msg;
                msg.result = valueAbout;
                msg.value  = ESR_BagFull;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            switch ( pMessage->drawType )
            {
            case ECT_HuiGuiGift:
                {
                    int16 varId = theDataCenter.GetVarSymbol( VS_LaoWanJiaFanhui );
                    if ( varId != -1)
                    { SetVar( varId, 1 ); }
                }
                break;
            case ECT_ChongZhiBackGift:
                { // 还送钱
                    uint32 nValue = 0;
                    switch ( pMessage->result )
                    {
                    case 1: // 一等级 送50金锭
                        { nValue = 50; }
                        break;
                    case 2: // 二等级 送200金锭
                        { nValue = 200; }
                        break;
                    case 3: // 三等级 送900金锭
                        { nValue = 900; }
                        break;
                    case 4: // 四等级 送4000金锭
                        { nValue = 4000; }
                        break;
                    }

                    if ( 0 != nValue )
                    {
                        LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_INFO,"[%u:%s:%u:%s]得到多冲多送返还金锭[%u]", GetAccountID(), GetAccount(), GetDBCharacterID(),GetCharName(), nValue );
                        //Log("得到多冲多送返还金锭[%u]", nValue);
						Log(theXmlString.GetString(eServerLog_GetMoreJingDing), nValue);
                        OperateJinDing( EOT_Add, nValue, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Unkown);
                    }
                }
                break;
            }

            //Log("获得卡[%d][%d] Item[%s][%I64u]", pMessage->drawType, pMessage->result, pItemDetail->GetItemName(), n64Guid );
            //ShoppingLog("获得卡[%d][%d] Item[%s][%I64u]", pMessage->drawType, pMessage->result, pItemDetail->GetItemName(), n64Guid );

            Log(theXmlString.GetString(eServerLog_GetKard), pMessage->drawType, pMessage->result, pItemDetail->GetItemName(), n64Guid );
            ShoppingLog(theXmlString.GetString(eServerLog_GetKard), pMessage->drawType, pMessage->result, pItemDetail->GetItemName(), n64Guid );
		
		}
        break;
    case ECT_ZhiZunCardLevel:
        {
            uint16 tileId = GetTargetIdByPlatformQueryType( pMessage->drawType, pMessage->result );
            AddTitle( tileId );
            MsgAckResult msg;
            msg.result = GetResultByPlatformQueryType( pMessage->drawType );
            msg.value  = pMessage->result;
            GettheServer().SendMsgToSingle( &msg, this );
        }
        break;
    }
}

void GamePlayer::OnS2SCallGraphic( Msg* pMsg )
{
//     MsgReqGraphicCode msg;
//     bool bResult = _graphicCodeManager.MakeReqGraphicCode( msg );
//     if ( bResult )
//     { GettheServer().SendMsgToSingle(&msg, this);}
	GraphicCodeCheckCommunication::SCheckReqMsg msg;
	msg.checkType = GraphicCodeCheckCommunication::ECT_GraphicCode;
	msg.nIDNeedToCheck = GetDBCharacterID();
	theGraphicCodeCheckCommunication.AddCheckReqMsg(msg);
}

void GamePlayer::OnMsgCheckCheatAck( Msg* pMsg )
{
    MsgCheckCheatAck* pAck = static_cast< MsgCheckCheatAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    // CheckCheatLog( "返回防外挂检测结果 [%0x]", pAck->nResult );
    theRabotManager.ProcessResult( GetDBCharacterID(), pAck->nResult );
}

void GamePlayer::OnMsgGetProcesslistAck( Msg* pMsg )
{
    MsgGetProcessListAck* pAck = static_cast< MsgGetProcessListAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    // CheckCheatLog( "返回防外挂检测结果 [%0x]", pAck->nResult );
    theRabotManager.ProcessResult( GetDBCharacterID(), pAck->nResult );

    // 把该玩家的客户端进程列表记录下来

    char szFilePath[256] = {0};
    sprintf_s( szFilePath, sizeof( szFilePath ) - 1, "%sProcesslist.dat", ProcessListFilePath );

    std::ofstream outfile;
    outfile.open( szFilePath, ios_base::app );
    if ( !outfile )
    { return; }

    outfile << "===============================================================================\r\n";
    outfile << "玩家帐号: " << GetAccountID() << "  玩家DBID: " << GetDBCharacterID() << "  玩家角色名: " << GetCharName() << "\r\n";
    outfile << "移动速度: " << pAck->fSpeed << " 是否骑马: " << pAck->bRideMount << "\r\n";

    std::string strList = pAck->szList;

    std::string::size_type nPos = strList.find( ";" );
    std::string strModule = strList.substr( 0, nPos );
    std::string strProcess = strList.substr( nPos + 1 );
    outfile << " 当前进程加载的所有模块 : \r\n";
    outfile << strModule << "\r\n";

    outfile << " 当前所有进程列表 : \r\n";
    outfile << strProcess << "\r\n";

    outfile.clear();
    outfile.close();
}


void GamePlayer::OnMsgReceiveQuestReq( Msg* pMsg )
{
    MsgReceiveQuestReq* pReceive = static_cast< MsgReceiveQuestReq* >( pMsg );
    if ( pReceive == NULL )
    { return; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( pReceive->stNpcID );
    if ( pChar == NULL || !pChar->IsNpc() )
    { return; }

    NpcBaseEx* pNpc = static_cast< NpcBaseEx* >( pChar );

    if ( !IsInMapArea( pNpc->GetMapID(), pNpc->GetFloatX(), pNpc->GetFloatY(), 15.0f ) )
    { return; }

    SQuest* pQuest = theQuestManager.GetQuest( pReceive->stQuestID );
    if ( pQuest == NULL )
    { return; }

    switch ( pQuest->chQuestType )
    {
    case SQuest::Type_Pub:  // 酒馆任务
    case SQuest::Type_Royal:
        {
            if ( !thePubQuestManager.CanReceiveSpecialQuest( this, GetDBCharacterID(), pNpc->GetNpcID(), pReceive->stQuestID ) )
            { return; }
        }
        break;
    case SQuest::Type_ConQuest: // 征伐任务
        {
            if ( !theConQuestManager.CanReceiveSpecialQuest( this, GetDBCharacterID(), pNpc->GetNpcID(), pReceive->stQuestID ) )
            { return; }
        }
        break;
    default:
        return;
        break;
    }

    if ( SetQuestState( pReceive->stQuestID, QuestManager::eQuestGaining ) )        // 设置任务已接
    {
        CScriptMgr::CallQuestScript( pNpc->GetQuestScriptByQuestID( pReceive->stQuestID ), this,  m_nScriptNpcId );       // 调脚本
    }
}

// 行酒令效果
void GamePlayer::OnMsgResetPubQuestReq( Msg* pMsg )
{
    MsgResetPubQuestReq* pReset = static_cast< MsgResetPubQuestReq* >( pMsg );
    if ( pReset == NULL )
    { return; }

    MsgResetPubQuestAck xAck;
    xAck.chType  = pReset->chType;
    xAck.stNpcID = pReset->stNpcID;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( pReset->stNpcID );
    if ( pChar == NULL || !pChar->IsNpc() )
    { 
        xAck.stResult = MsgResetPubQuestAck::ECD_Fail;
        GettheServer().SendMsgToSingle( &xAck, this );
        return; 
    }

    NpcBaseEx* pNpc = static_cast< NpcBaseEx* >( pChar );
    // 距离太远了
    if ( !IsInMapArea( pNpc->GetMapID(), pNpc->GetFloatX(), pNpc->GetFloatY(), 15.0f ) )
    { 
        xAck.stResult = MsgResetPubQuestAck::ECD_Fail;
        GettheServer().SendMsgToSingle( &xAck, this );
        return; 
    }         

    int nItemID = 0;
    switch( pReset->chType )
    {
    case SQuest::Type_Pub:      // 酒馆任务
        nItemID = ResetPubQuestItemID2;
        break;
    case SQuest::Type_Royal:    // 皇榜任务
        nItemID = ResetPubQuestItemID1;
        break;
    default:
        {
            xAck.stResult = MsgResetPubQuestAck::ECD_Fail;
            GettheServer().SendMsgToSingle( &xAck, this );
            return;
        }
        break;
    }

    // 先判断是否有行酒令
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( nItemID );
    if ( pItemCommon == NULL )
    { 
        xAck.stResult = MsgResetPubQuestAck::ECD_Fail;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    int nCount = GetItemCount( nItemID );
    if ( nCount == 0 )
    {
        xAck.stResult = MsgResetPubQuestAck::ECD_Fail;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    PubQuest* pPubQuest = thePubQuestManager.GetSpecialQuest( GetDBCharacterID() );
    if ( pPubQuest == NULL )
    { 
        xAck.stResult = MsgResetPubQuestAck::ECD_Fail;
        GettheServer().SendMsgToSingle( &xAck, this );
        return; 
    }

  

	//LYH日志添加 酒馆任务行酒令

	//LYH日志添加 
	SCharItem *_CharItem =	_NormalItemBag.GetItemByItemID(nItemID);
	if(!_CharItem)
	{
		_CharItem =	_MaterialItemBag.GetItemByItemID(nItemID);
	  if(!_CharItem)
		_CharItem =	_TaskItemBag.GetItemByItemID(nItemID);
	}

	ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(nItemID);
    if(_CharItem && _pitem)
	theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),nItemID,1,_CharItem->GetItemGuid(),
	_CharItem->GetItemCount()-1>=0?_CharItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,GetCharName(),_pitem->GetItemName());


	// 删除行酒令
	RemoveItem( nItemID, 1 );

    pPubQuest->ClearRecordTime( pNpc->GetNpcID() );
    pPubQuest->ShowQuestList( pReset->stNpcID );

    // 刷新成功 发送消息给客户端
    GettheServer().SendMsgToSingle( &xAck, this );
}


void GamePlayer::OnMsgMoveStarReq( Msg* pMsg )
{
    MsgMoveStarReq* pReq = static_cast< MsgMoveStarReq* >( pMsg );

    // 判断移星道具
    SCharItem* pCharItem = NULL;
    switch ( pReq->chItemBagType )
    {
    case BT_MaterialBag:
        {
            pCharItem = _MaterialItemBag.GetItemByIndex( pReq->stItemIndex );
        }
        break;
    case BT_NormalItemBag:
        {
            pCharItem = _NormalItemBag.GetItemByIndex( pReq->stItemIndex );
        }
        break;
    default:
        return;
    }

    if ( pCharItem == NULL || pCharItem->itembaseinfo.nOnlyInt != pReq->nItemGuid )
    { return; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if ( pItemCommon == NULL )
    { return; }

    if ( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_CHECKUP )
    {
        MsgMoveStarAck xAck;
        xAck.chResult = MsgMoveStarAck::ECD_IsNotMoveStarItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCheckUp* pItemCheckUp = static_cast< ItemDefine::SItemCheckUp* >( pItemCommon );
    if ( pItemCheckUp->stCheckUpType != ItemDefine::SItemCheckUp::ECD_MoveStar )
    {
        MsgMoveStarAck xAck;
        xAck.chResult = MsgMoveStarAck::ECD_IsNotMoveStarItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    // 判断装备
    SCharItem* pCharEquip = NULL;
    ItemBag* pEquipBag    = NULL;
    switch ( pReq->chEquipBagType )
    {
    case BT_NormalItemBag:
        {
            pCharEquip = _NormalItemBag.GetItemByIndex( pReq->stEquipIndex );
            pEquipBag  = &_NormalItemBag;
        }
        break;
    case BT_MaterialBag:
        {
            pCharEquip = _MaterialItemBag.GetItemByIndex( pReq->stEquipIndex );
            pEquipBag  = &_MaterialItemBag;
        }
        break;
    default:
        return;
    }

    if ( pCharEquip == NULL || pEquipBag == NULL || pCharEquip->itembaseinfo.nOnlyInt != pReq->nEquipGuid )
    { return; }

    ItemDefine::SItemCommon* pEquipCommon = GettheItemDetail().GetItemByID( pCharEquip->itembaseinfo.ustItemID );
    if ( pEquipCommon == NULL || !pEquipCommon->IsCanEquip() )
    {
        MsgMoveStarAck xAck;
        xAck.chResult = MsgMoveStarAck::ECD_IsNotEquip;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCanEquip* pItemCanEquip = static_cast< ItemDefine::SItemCanEquip* >( pEquipCommon );
    if ( pItemCanEquip == NULL || pItemCanEquip->bFashion )
    { return; }

    // 计算等级区间 ( 0 - 9 是一个区间 , 后面类推)
    int nItemLevel = pItemCheckUp->stEquipLevel / 10;       // 移星道具区间
    int nEquipLevel = pItemCanEquip->stEquipLevelReq / 10;   // 装备区间

    // 移星操作
    switch( pReq->chOperate )
    {
    case MsgMoveStarReq::ECD_MoveToItem:        // 转移到道具上
        {
            MsgMoveStarAck xAck;

            if ( pCharEquip->equipdata.ucLevel == 0 )
            {
                xAck.chResult = MsgMoveStarAck::ECD_EquipNotStar;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            // 判断区间, 
            if ( nEquipLevel < nItemLevel )       // 不能转移给高级移星道具上
            {
                xAck.chResult = MsgMoveStarAck::ECD_LessItemLevel;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            if ( pCharItem->equipdata.ucLevel > 0 )         // 不能转移多次
            {
                xAck.chResult = MsgMoveStarAck::ECD_MoveStarItemError;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            pCharItem->SetBounded( true );
            pCharItem->equipdata.ucLevel  = pCharEquip->equipdata.ucLevel;
            pCharEquip->equipdata.ucLevel = 0;    // 装备星级的清除,由客户端自己清除    

            xAck.chResult    = MsgMoveStarAck::ECD_SuccessToItem;
            xAck.bBound      = true;
            xAck.chStarLevel = pCharItem->equipdata.ucLevel;
            GettheServer().SendMsgToSingle( &xAck, this );
        }
        break;
    case MsgMoveStarReq::ECD_MoveToEquip:       // 转移到装备上
        {
            MsgMoveStarAck xAck;

            if ( pCharItem->equipdata.ucLevel == 0 )
            {
                xAck.chResult = MsgMoveStarAck::ECD_ItemNotStar;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            if ( nItemLevel < nEquipLevel )
            {
                xAck.chResult = MsgMoveStarAck::ECD_LessEquipLevel;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            if ( pCharItem->equipdata.ucLevel <= pCharEquip->equipdata.ucLevel )
            {
                xAck.chResult = MsgMoveStarAck::ECD_LessEquipStar;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            pCharEquip->SetBounded( true );
            pCharEquip->equipdata.ucLevel = pCharItem->equipdata.ucLevel;

            // 删除道具
            int nCount = pCharItem->itembaseinfo.ustItemCount;
            RemoveItem( pReq->chItemBagType, pReq->stItemIndex, nCount, pReq->nItemGuid );

			SCharItem *_item = GetBagItemByGuid(pReq->nItemGuid);
			//LYH日志添加
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),pCharItem->GetItemID(),nCount,pReq->nItemGuid,
				_item?_item->GetItemCount():0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),pItemCheckUp->GetItemName());


            //Log( "移星操作成功,删除移星道具[%s] GUID[%I64u] [%d]个", pItemCheckUp->GetItemName(), pReq->nItemGuid, nCount );

            xAck.chResult    = MsgMoveStarAck::ECD_SuccessToEquip;
            xAck.bBound      = true;
            xAck.chStarLevel = pCharEquip->equipdata.ucLevel;
            GettheServer().SendMsgToSingle( &xAck, this );
        }
        break;
    default:
        return;
    }
}

void GamePlayer::OnMsgMoveStarLevelUpReq( Msg* pMsg )
{
    MsgMoveStarLevelUpReq* pReq = static_cast< MsgMoveStarLevelUpReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    MsgMoveStarLevelUpAck xAck;
    xAck.ustItemIndex = pReq->ustItemIndex;
    xAck.n64ItemGuid  = pReq->n64ItemGuid;

    // 判断移星石
    SCharItem* pMoveStarItem = _NormalItemBag.GetItemByIndex( pReq->ustItemIndex );
    if ( pMoveStarItem == NULL || pMoveStarItem->GetItemGuid() != pReq->n64ItemGuid )
    {
        xAck.uchResult = MsgMoveStarLevelUpAck::ECD_ErrorMoveStarItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCommon* pMoveStarCommon = GettheItemDetail().GetItemByID( pMoveStarItem->GetItemID() );
    if ( pMoveStarCommon == NULL || pMoveStarCommon->ucItemType != ItemDefine::ITEMTYPE_CHECKUP )
    {
        xAck.uchResult = MsgMoveStarLevelUpAck::ECD_ErrorMoveStarItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCheckUp* pCheckUp = static_cast< ItemDefine::SItemCheckUp* >( pMoveStarCommon );
    if ( pCheckUp == NULL || pCheckUp->stCheckUpType != ItemDefine::SItemCheckUp::ECD_MoveStar )
    {
        xAck.uchResult = MsgMoveStarLevelUpAck::ECD_ErrorMoveStarItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    const MoveStarLevelUp* pMoveStartLevelUp = theStarLevelUpConfig.GetMoveStarLevelUp( pMoveStarItem->GetItemID() );
    if ( pMoveStarItem == NULL )
    {
        xAck.uchResult = MsgMoveStarLevelUpAck::ECD_CanNotLevelUp;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    // 判断辅助材料
    SCharItem* pMaterial1 = NULL;
    switch ( pReq->uchItemBagType1 )
    {
    case BT_MaterialBag:
        pMaterial1 = _MaterialItemBag.GetItemByIndex( pReq->ustMaterialIndex1 );
        break;
    default:
        pMaterial1 = _NormalItemBag.GetItemByIndex( pReq->ustMaterialIndex1 );
    }

    if ( pMaterial1 == NULL || pMaterial1->GetItemGuid() != pReq->n64MaterialGuid1 || pMaterial1->GetItemID() != pMoveStartLevelUp->GetMaterialID() )
    {
        xAck.uchResult = MsgMoveStarLevelUpAck::ECD_ErrorMaterial;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    if ( pMaterial1->GetItemCount() < pReq->ustMaterialCount )
    { 
        xAck.uchResult = MsgMoveStarLevelUpAck::ECD_ErrorMaterialCount;
        GettheServer().SendMsgToSingle( &xAck, this );
        return; 
    }

    if ( pReq->ustMaterialCount > pMoveStartLevelUp->GetMaxCount() )
    { pReq->ustMaterialCount = pMoveStartLevelUp->GetMaxCount(); }

    // 判断钱是否足够
    if ( GetJiaoZiMoney() < pMoveStartLevelUp->GetCostMoney() )
    {
        xAck.uchResult = MsgMoveStarLevelUpAck::ECD_NotEnoughMoney;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    // 计算成功概率
    float fModulus = pMoveStartLevelUp->GetModulus( pReq->ustMaterialCount );
    uint16 ustRand = theRand.rand16() % RAND_NUM;
    if ( ustRand < fModulus * RAND_NUM )
    {
        xAck.ustNewItemID = pMoveStartLevelUp->GetNewItemID();
        pMoveStarItem->itembaseinfo.ustItemID = pMoveStartLevelUp->GetNewItemID();
    }
    else
    {
        xAck.uchResult = MsgMoveStarLevelUpAck::ECD_Failed;
    }

    GettheServer().SendMsgToSingle( &xAck, this );

    // 扣钱
    OperateJiaoZi( EOT_Sub, pMoveStartLevelUp->GetCostMoney(), true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_MoveStarLevelUp);
    xAck.dwCurrentMoney = GetMoney();

   

	//LYH日志添加
	SCharItem * cItem =  GetBagItemByGuid(pReq->n64MaterialGuid1);
  
	if(cItem)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(cItem->GetItemID());
		if(_pitem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),cItem->GetItemID(),pReq->ustMaterialCount,
			                                  pReq->n64MaterialGuid1,
											  cItem->GetItemCount()-pReq->ustMaterialCount?cItem->GetItemCount()-pReq->ustMaterialCount:0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
	}

	// 扣除物品
	RemoveItem( pReq->uchItemBagType1, pReq->ustMaterialIndex1, pReq->ustMaterialCount, pReq->n64MaterialGuid1 );
}

void GamePlayer::OnMsgSuitElementCheckupReq( Msg* pMsg )
{
    MsgSuitElementCheckupReq* pReq = static_cast< MsgSuitElementCheckupReq* >( pMsg );

    // 判断鉴定道具
    SCharItem* pCharItem = NULL;
    switch( pReq->chItemBagType )
    {
    case BT_NormalItemBag:
        {
            pCharItem = _NormalItemBag.GetItemByIndex( pReq->stItemIndex );
        }
        break;
    case BT_MaterialBag:
        {
            pCharItem = _MaterialItemBag.GetItemByIndex( pReq->stItemIndex );
        }
        break;
    default:
        return;
    }

    if ( pCharItem == NULL || pCharItem->itembaseinfo.nOnlyInt != pReq->nItemGuid )
    { return; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if ( pItemCommon == NULL || pItemCommon->ucItemType != ItemDefine::ITEMTYPE_CHECKUP )
    { return; }

    ItemDefine::SItemCheckUp* pItemCheckUp = static_cast< ItemDefine::SItemCheckUp* >( pItemCommon );
    if ( pItemCheckUp == NULL )
    { return; }

    // 判断五行套装装备
    SCharItem* pCharEquip = NULL;
    switch( pReq->chArmourBagType )
    {
    case BT_NormalItemBag:
        {
            pCharEquip = _NormalItemBag.GetItemByIndex( pReq->stArmourIndex );
        }
        break;
    case BT_MaterialBag:
        {
            pCharEquip = _MaterialItemBag.GetItemByIndex( pReq->stArmourIndex );
        }
        break;
    default:
        return;
    }

    if ( pCharEquip == NULL || pCharEquip->itembaseinfo.nOnlyInt != pReq->nArmourGuid )
    { return; }

    ItemDefine::SItemCommon* pItemEquip = GettheItemDetail().GetItemByID( pCharEquip->itembaseinfo.ustItemID );
    if ( pItemEquip == NULL || pItemEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    ItemDefine::SItemArmour* pItemArmour = static_cast< ItemDefine::SItemArmour* >( pItemEquip );
    if ( pItemArmour == NULL )
    { return; }

    MsgSuitElementCheckupAck xAck;
    xAck.chArmourBagType = pReq->chArmourBagType;
    xAck.stArmourIndex   = pReq->stArmourIndex;
    xAck.nArmourGuid     = pReq->nArmourGuid;

    if ( !pItemArmour->bIsElements )    // 判断是否五行套装
    {
        xAck.chResult = MsgSuitElementCheckupAck::ECD_NotElement;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    if ( pItemArmour->stEquipLevelReq > pItemCheckUp->stEquipLevel )   // 等级不符合
    {
        xAck.chResult = MsgSuitElementCheckupAck::ECD_LevelError;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    StarLevelUpData* pLevelUpData = theStarLevelUpConfig.GetStarLevelUpData( pItemArmour->stEquipLevelReq, 0 );
    if ( pLevelUpData == NULL )
    { return; }

    if ( GetJiaoZiMoney() < pLevelUpData->GetCostMoney() * 5 )    // 判断钱够不够
    {
        xAck.chResult = MsgSuitElementCheckupAck::ECD_NotEnoughMoney;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    switch ( pReq->chOperate )
    {
    case MsgSuitElementCheckupReq::ECD_Checkup: // 鉴定
        {
            if ( pCharEquip->GetElements() != ItemElements_Init )
            {
                xAck.chResult = MsgSuitElementCheckupAck::ECD_ElementAlready;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            if ( pItemCheckUp->stEffectType != ItemDefine::SItemCheckUp::ECD_ElementsCheckUp )
            {
                xAck.chResult = MsgSuitElementCheckupAck::ECD_NotCheckupItem;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            xAck.chResult = MsgSuitElementCheckupAck::ECD_CheckupSuccess;
            pCharEquip->SetElements( theRand.rand16() % ItemElements_Earth + ItemElements_Metal ); // 随即一个五行元素
        }
        break;
    case MsgSuitElementCheckupReq::ECD_Clear:   // 清除
        {
            if ( pCharEquip->GetElements() == ItemElements_Init )
            {
                xAck.chResult = MsgSuitElementCheckupAck::ECD_HaveNotElement;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            if ( pItemCheckUp->stEffectType != ItemDefine::SItemCheckUp::ECD_ElementsClear )
            {
                xAck.chResult = MsgSuitElementCheckupAck::ECD_NotClearItem;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            xAck.chResult = MsgSuitElementCheckupAck::ECD_ClearSuccess;
            pCharEquip->SetElements( ItemElements_Init );
            pCharEquip->SetSuitLevel( 0 );      // 五行提纯等级也出去掉
        }
        break;
    default:
        return;
    }

    OperateJiaoZi( EOT_Sub, pLevelUpData->GetCostMoney() * 5, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_SuitElementCheck);
    
	//LYH日志添加
	SCharItem * cItem =  GetBagItemByGuid(pReq->nItemGuid);
	ItemDefine::SItemCommon *pCommon =  GettheItemDetail().GetItemByID(cItem->GetItemID());
	if(cItem && pCommon)
	theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),cItem->GetItemID(),1,pReq->nItemGuid,
	cItem->GetItemCount()-1>=0?cItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),pCommon->GetItemName());

	RemoveItem( pReq->chItemBagType, pReq->stItemIndex, 1, pReq->nItemGuid );

    xAck.chElement  = pCharEquip->GetElements();
    xAck.nLeftMoney = GetMoney();
    GettheServer().SendMsgToSingle( &xAck, this );
}

//void GamePlayer::OnMsgMoneyItemExchange( Msg* pMsg )
//{
//    MsgMoneyItemExchangeReq* pMessage = (MsgMoneyItemExchangeReq*)pMsg;
//
//    // 判断鉴定道具
//    SCharItem* pCharItem = _NormalItemBag.GetItemByIndex( pMessage->index );
//    if ( pCharItem == NULL || pCharItem->itembaseinfo.nOnlyInt != pMessage->itemguid )
//    { return; }
//
//    uint16 itemId   = pCharItem->itembaseinfo.ustItemID;
//    int64  itemguid = pCharItem->itembaseinfo.nOnlyInt;
//    // 记录log
//    ItemDefine::SItemCommon* pItemCommonConfig = GettheItemDetail().GetItemByID( itemId );
//    if ( pItemCommonConfig == NULL )
//    { return; }
//
//    if ( pItemCommonConfig->ucItemType != CItemDetail::ITEMTYPE_REALAWARD )
//    { return; }
//
//    unsigned short count = 1;
//    if ( _NormalItemBag.PopItem( pMessage->index, count ) != ierr_Success )
//    {
//        MsgAckResult msg;
//        msg.result = ER_MoneyItemExchangePopFail;
//        GettheServer().SendMsgToSingle( &msg, this );
//        return; 
//    }
//
//    // T0005 兑换 %s %d %s %s %s %s
//    ShoppingLog( theXmlString.GetString(eLog_MoneyItemChange), pCharItem->itembaseinfo.nOnlyInt, pItemCommonConfig->GetItemName(), pCharItem->itembaseinfo.ustItemID, pMessage->linkman, pMessage->telephone, pMessage->email, pMessage->identityCard );
//
//    // 发消息给Centerserver
//    GS2CSMoneyItemExchange cmsg;    
//    cmsg.guid = GetAccountID();
//    cmsg.itemId   = itemId;
//    cmsg.itemguid = itemguid;
//    strncpy_s( cmsg.charName, sizeof(cmsg.charName), GetCharName(), sizeof(cmsg.charName)-1);
//    strncpy_s( cmsg.itemName, sizeof(cmsg.itemName), pItemCommonConfig->GetItemName(), sizeof(cmsg.itemName)-1);
//    strncpy_s( cmsg.linkman, sizeof(cmsg.linkman), pMessage->linkman, sizeof(cmsg.linkman)-1);
//    strncpy_s( cmsg.telephone, sizeof(cmsg.telephone), pMessage->telephone, sizeof(cmsg.telephone)-1);
//    strncpy_s( cmsg.email, sizeof(cmsg.email), pMessage->email, sizeof(cmsg.email)-1);
//    strncpy_s( cmsg.identityCard, sizeof(cmsg.identityCard), pMessage->identityCard, sizeof(cmsg.identityCard)-1);
//    strncpy_s( cmsg.passport, sizeof(cmsg.passport), GetAccount(), sizeof(cmsg.passport)-1);
//    GettheServer().SendCenterServerMsg( &cmsg );
//
//    MsgMoneyItemExchangeAck ack;
//    ack.result   = ER_Success;
//    ack.index    = pMessage->index;
//    ack.itemId   = itemId;
//    ack.itemguid = itemguid;
//    GettheServer().SendMsgToSingle( &ack, this );
//
//    RemoveItem( BT_NormalItemBag, pMessage->index, 1, itemguid );
//}

void GamePlayer::OnMsgChangeItemPos( Msg* pMsg )
{       
    MsgChangeItemPos* pChangeItemPos = (MsgChangeItemPos*)pMsg;
    if ( pChangeItemPos == NULL )
    { return; }

    SCharStorageData* pStorageItem = &_StorageBag;

    SCharItem* pDst = NULL;
    SCharItem* pSrc = NULL;
    if(pChangeItemPos->nWhichIs == 0)
    {
        switch ( pChangeItemPos->ucItemBagType )
        {
        case BT_NormalItemBag:
            {
                if(pChangeItemPos->ustDstIndex >= GetNormalBagSize() || pChangeItemPos->ustSrcIndex >= GetNormalBagSize())
                    return;

                pDst = GetNormalBagPointerByIndex(pChangeItemPos->ustDstIndex);
                pSrc = GetNormalBagPointerByIndex(pChangeItemPos->ustSrcIndex);
            }
            break;
        case BT_MaterialBag:
            {
                if(pChangeItemPos->ustDstIndex >= GetMaterialBagSize() || pChangeItemPos->ustSrcIndex >= GetMaterialBagSize())
                    return;

                pDst = GetMaterialBagPointerByIndex(pChangeItemPos->ustDstIndex);
                pSrc = GetMaterialBagPointerByIndex(pChangeItemPos->ustSrcIndex);
            }
            break;
        case BT_TaskBag:
            {   
                if(pChangeItemPos->ustDstIndex >= GetTaskBagSize() || pChangeItemPos->ustSrcIndex >= GetTaskBagSize())
                    return;

                pDst = GetTaskBagPointerByIndex(pChangeItemPos->ustDstIndex);
                pSrc = GetTaskBagPointerByIndex(pChangeItemPos->ustSrcIndex);
            }
            break;
        default:
            return;
            break;
        }

    }
    else if(pChangeItemPos->nWhichIs == 1)
    {
        if ( pChangeItemPos->ustDstIndex >= STORAGE_ITEMGRID_MAX || pChangeItemPos->ustSrcIndex >= STORAGE_ITEMGRID_MAX )
        { return; }

        pDst = &pStorageItem->stStorageItems[pChangeItemPos->ustDstIndex];
        pSrc = &pStorageItem->stStorageItems[pChangeItemPos->ustSrcIndex];
    }

    if ( pDst == NULL || pSrc == NULL )
    { return; }

   // Log("物品位置更改\t%d\t%d\t%d\t%d", pDst->itembaseinfo.ustItemID ,pDst->itembaseinfo.ustItemCount, pSrc->itembaseinfo.ustItemID ,pSrc->itembaseinfo.ustItemCount);
	Log(theXmlString.GetString(eServerLog_ItemPosChange), pDst->itembaseinfo.ustItemID ,pDst->itembaseinfo.ustItemCount, pSrc->itembaseinfo.ustItemID ,pSrc->itembaseinfo.ustItemCount);
    ItemBag::ExchangeItem( pDst, pSrc);
}


void GamePlayer::OnMoveIntensifyItem(Msg* pMsg)
{       
    return;
    //MsgMoveIntensifyItem* pMove = (MsgMoveIntensifyItem*)pMsg;
    //if (!pMove)
    //    return;

    //SIntensfyItem* pIntensify = &gCharInfoServer.otherdata.sIntensifyItem;

    //switch( pMove->stMoveType )
    //{
    //case MsgMoveIntensifyItem::ePackToGem:
    //    {
    //        SCharItem charItem;
    //        SCharItem* pSrcItemPointer = NULL;
    //        ItemBag*   pItemBag        = NULL;
    //        switch( pMove->ucItemBagType )
    //        {
    //        case BT_NormalItemBag:
    //            if( !_NormalItemBag.GetItem( pMove->stSrcIndex,&charItem ))
    //                return;

    //            pSrcItemPointer = GetNormalBagPointerByIndex(pMove->stSrcIndex);
    //            pItemBag        = &_NormalItemBag;
    //            break;
    //        case BT_MaterialBag:
    //            if( !_MaterialItemBag.GetItem( pMove->stSrcIndex,&charItem ))
    //                return;
    //            pSrcItemPointer = GetMaterialBagPointerByIndex(pMove->stSrcIndex);
    //            pItemBag        = &_MaterialItemBag;
    //            break;
    //        default:
    //            return;
    //            break;
    //        }
    //        if ( !pSrcItemPointer || !pItemBag)
    //            return;
    //                    
    //        if (charItem.storageinfo.bIsLocked)
    //            return;

    //        char szID[40] = {0};
    //        Log(theXmlString.GetString(eLog_info_2slk_109),::BigInt2String(charItem.itembaseinfo.nOnlyInt,szID),
    //            charItem.itembaseinfo.ustItemID,charItem.itembaseinfo.ustItemCount);
    //        ItemBag::MoveItem( &pIntensify->stGem, BT_IntensifyBag, pSrcItemPointer,(EBagType) pMove->ucItemBagType, pItemBag, pMove->stCount);            
    //    }
    //    break;
    //case MsgMoveIntensifyItem::eGemToPack:
    //    {
    //        if ( pMove->stDstIndex >= GetNormalBagSize() )
    //            return;
    //        char szID[40] = {0};
    //        Log(theXmlString.GetString(eLog_info_2slk_110),
    //            ::BigInt2String(pIntensify->stGem.itembaseinfo.nOnlyInt,szID),
    //            pIntensify->stGem.itembaseinfo.ustItemID,
    //            pIntensify->stGem.itembaseinfo.ustItemCount);

    //        ItemBag::MoveItem( &gCharInfoServer.itemData.stPackItems[pMove->stDstIndex], BT_NormalItemBag, 
    //            &pIntensify->stGem, BT_IntensifyBag, &_NormalItemBag,
    //            pIntensify->stGem.itembaseinfo.ustItemCount);
    //    }
    //    break;
    //case MsgMoveIntensifyItem::ePackToEquip:
    //    {
    //        if( _NormalItemBag.IsHaveItem( pMove->stSrcIndex ) == false )
    //            return;
    //        if (gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].storageinfo.bIsLocked)
    //            return;
    //        char szID[40] = {0};
    //        Log(theXmlString.GetString(eLog_info_2slk_111),
    //            ::BigInt2String(gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.nOnlyInt,szID),
    //            gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.ustItemID,
    //            gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.ustItemCount);
    //        ItemBag::MoveItem( &pIntensify->stEquip, BT_EquipBag, &gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex], BT_NormalItemBag, 
    //            &_NormalItemBag,pMove->stCount);            
    //    }
    //    break;
    //case MsgMoveIntensifyItem::eEquipToPack:
    //    {
    //        if ( pMove->stDstIndex >= GetNormalBagSize()/*ITEM_BAGMAX*/ )
    //            return;
    //        char szID[40] = {0};
    //        Log(theXmlString.GetString(eLog_info_2slk_112),
    //            ::BigInt2String(pIntensify->stEquip.itembaseinfo.nOnlyInt,szID),
    //            pIntensify->stEquip.itembaseinfo.ustItemID,
    //            pIntensify->stEquip.itembaseinfo.ustItemCount);

    //        ItemBag::MoveItem( &gCharInfoServer.itemData.stPackItems[pMove->stDstIndex], BT_NormalItemBag, 
    //            &pIntensify->stEquip, BT_EquipBag, &_NormalItemBag,pIntensify->stEquip.itembaseinfo.ustItemCount);
    //    }
    //    break;
    //case MsgMoveIntensifyItem::ePackToLuck:
    //    {
    //        if( _NormalItemBag.IsHaveItem( pMove->stSrcIndex ) == false )
    //            return;
    //        if (gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].storageinfo.bIsLocked)
    //            return;
    //        char szID[40] = {0};
    //        Log(theXmlString.GetString(eLog_info_2slk_113),
    //            ::BigInt2String(gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.nOnlyInt,szID),
    //            gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.ustItemID,
    //            gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex].itembaseinfo.ustItemCount);

    //        ItemBag::MoveItem( &pIntensify->stLuck, BT_IntensifyBag, &gCharInfoServer.itemData.stPackItems[pMove->stSrcIndex], BT_NormalItemBag, &_NormalItemBag,pMove->stCount);            
    //    }
    //    break;
    //case MsgMoveIntensifyItem::eLuckToPack:
    //    {
    //        if ( pMove->stDstIndex >=GetNormalBagSize()/*ITEM_BAGMAX*/ )
    //            return;
    //        char szID[40] = {0};
    //        LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_INFO, theXmlString.GetString(eLog_info_2slk_114),
    //            ::BigInt2String(pIntensify->stLuck.itembaseinfo.nOnlyInt,szID),
    //            pIntensify->stLuck.itembaseinfo.ustItemID,
    //            pIntensify->stLuck.itembaseinfo.ustItemCount);

    //        ItemBag::MoveItem( &gCharInfoServer.itemData.stPackItems[pMove->stDstIndex], BT_NormalItemBag, 
    //            &pIntensify->stLuck, BT_IntensifyBag, &_NormalItemBag,
    //            pIntensify->stLuck.itembaseinfo.ustItemCount);
    //    }
    //    break;
    //default:
    //    // ToLog(false);
    //    break;
    //}   
}

void GamePlayer::OnMsgPeekPlayerEquip(Msg* pMsg)
{       
    MsgWantPeek* pWant = (MsgWantPeek*)pMsg;
    if ( pWant == NULL )
    { return; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(pWant->stTargetID);    
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;
    if ( !pGamePlayer )
        return;

    switch ( pWant->type )
    {
    case MsgWantPeek::EPT_Char:
        {
            MsgPeekEquip msg;
            msg.header.stID = pWant->header.stID;
            msg.playerId = pWant->stTargetID;
            msg.hairId   = pGamePlayer->GetCharInfo().visual.hairId ; 
            msg.faceId   = pGamePlayer->GetCharInfo().visual.faceId ;      
            msg.showFlag = pGamePlayer->GetCharInfo().visual.showFlag ;    
            msg.fModelPercent = pGamePlayer->GetCharInfo().visual.fModelPercent ;

            SCharItem* pItem = pGamePlayer->gCharInfoServer.visual.GetVisualArray();
            if (pItem == NULL)
            { return; }

            memcpy( &msg.playerequipitem, pItem, (EEquipPartType_MaxEquitPart*sizeof(SCharItem)));
            GettheServer().SendMsgToSingle(&msg,this);
        }
        break;
    case MsgWantPeek::EPT_Mount:
        {
            SMountItem* pMount = pGamePlayer->_mountManager.GetActiveMount();
            if ( pMount == NULL )
            {
                MsgAckResult msg;
                msg.result = ER_TargetNotActiveMount;
                GettheServer().SendMsgToSingle(&msg,this);
                return;
            }
            MsgUpdateMount msg;
            msg.header.stID = pGamePlayer->GetID();
            msg.mount = *pMount;
            GettheServer().SendMsgToSingle(&msg,this);
        }
        break;
    }   
}

void GamePlayer::OnReqEctypeMapInfo( Msg* pMsg )
{       
    // GetEctypeMapMgr()->UpdateEctypeInfoToClient( this );
}

void GamePlayer::OnReqFlytomap( Msg* pMsg )
{       
    MsgReqFlyToMap *pMsgFlytoMap = (MsgReqFlyToMap*)pMsg;
    // GetEctypeMapMgr()->CharReqFlytoMap( this, pMsgFlytoMap->dwMapId, pMsgFlytoMap->dwX, pMsgFlytoMap->dwY );
}


void GamePlayer::OnMsgReqDuel( Msg* pMsg )
{
    MsgReqDuel* req = (MsgReqDuel*)pMsg;

    //// 自己在战斗状态 不切磋
    //if ( HaveFighteFlag(eFighting) )
    //{
    //    TellClient( theXmlString.GetString(eClient_Error_Me_InFightCanNotDuel) );
    //    return;
    //}            

    if ( IsOpenStall() )      // 摆摊状态下不能决斗
    { return; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(req->shTargetID);
    if ( !pChar || !pChar->IsPlayer() )
    { return; }

    //if ( pChar->HaveFighteFlag(eFighting) )
    //{
    //    TellClient( theXmlString.GetString(eClient_Error_Target_InFightCanNotDuel) );
    //    return;
    //}

    GamePlayer* pPlayer = (GamePlayer*)pChar;

    if ( pPlayer->IsOpenStall() )
    { return; }

    if ( CheckBlackListPlayer( pPlayer ) )
    { return; }     // 对方在自己的黑名单中

    // 是否在对方黑名单中
    if ( pPlayer->CheckBlackListPlayer( this ) )       // 自己在对方的黑名单中
    {   
        TellClient(theXmlString.GetString(eClient_OpFailReasonInBlacklist), pPlayer->GetCharName() );
        return;
    }

    //判断两者距离
	D3DXVECTOR3 pCharPos = pChar->GetPos();
	D3DXVECTOR3 Pos = GetPos();
	pCharPos.z = 0;
	Pos.z = 0;
	 D3DXVECTOR3 vDist = pCharPos - Pos;
	
    float fDistSq = D3DXVec3LengthSq( &vDist );

    if( fDistSq >= fDuelLength * fDuelLength)
    {
        TellClient( theXmlString.GetString(eClient_AddInfo_2slk_115) );
        return;  
    }

    // 是否已经在切磋
    if(theDuelHandler()->IsInDuel(req->shTargetID) ||  static_cast<GamePlayer*>(pChar)->m_bInDuelReq || m_bInDuelReq)
    {
        TellClient( theXmlString.GetString(eClient_AddInfo_2slk_116) );
        return;
    }

	//战场不可以比武
	//if(pPlayer->GetFightCamp() != CampDefine::NoneCamp || GetFightCamp() != CampDefine::NoneCamp)
	//{
	//	//战场不可以比武
	//	TellClient( theXmlString.GetString(eClient_AddInfo_CampBattleDuel) );
 //       return;
	//}

	//判断地图是否可以切磋
	bool canDuel = true;
	MapConfig::MapData* pTargetMapData = pPlayer->GetMapData();
	if ( pTargetMapData == NULL )
	{ return; }

	canDuel  = pTargetMapData->CanDuel ;

	if (!canDuel)
	{
		TellClient(theXmlString.GetString(eClient_AddInfo_CurMapCantDuel));
		return;
	}

	//判断当前所在区块是否可以切磋
	GameStage *pStage = theGameWorld.GetStageById( pPlayer->GetMapID() );
	if ( pStage == NULL )
	{ return ; }

	GameZone *pZone =  pStage->GetZone( pPlayer->GetCurZoneID() );
	GameZone *pZone1 =  pStage->GetZone( GetCurZoneID() );
    
	bool canDuel1 = true;
	bool canDuel2 = true;
	if ( pZone  )
		canDuel1 = pZone->GetZoneCanDuel();

	if(pZone1)
       canDuel2 = pZone1->GetZoneCanDuel();
	
 //两个人只要有一个在不能pk的区域，就不能切磋
	if(!canDuel1 || !canDuel2)
      canDuel = false;

	if (!canDuel)
	{
		TellClient(theXmlString.GetString(eClient_AddInfo_CurZoomCantDuel));
		return;
	}

    MsgReqDuel duel;
    duel.shTargetID = GetID();
    GettheServer().SendMsgToSingle(&duel, pChar);

    static_cast<GamePlayer*>(pChar)->m_bInDuelReq = true;

    m_bInDuelReq = TRUE;
}

void GamePlayer::OnMsgAckDuel( Msg* pMsg )
{
    MsgAckDuel* pAck = (MsgAckDuel*)pMsg;
    if ( pAck == NULL )
    { return; }

    m_bInDuelReq = false;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(pAck->shDuelID);

    if ( !pChar || !pChar->IsPlayer())
        return;

    static_cast<GamePlayer*>(pChar)->m_bInDuelReq = false;

    if(pAck->shResult == MsgAckDuel::ResultRefuse)
    {
        MsgAckDuel msg;
        msg.shDuelID = GetControl()->GetID();
        msg.shResult = MsgAckDuel::ResultRefuse;
        GettheServer().SendMsgToSingle( &msg, pChar );
        return;
    }
    else if( pAck->shResult == MsgAckDuel::ResultInBlackList )
    {
        MsgAckDuel msg;
        msg.shDuelID = GetControl()->GetID();
        msg.shResult = MsgAckDuel::ResultInBlackList;
        GettheServer().SendMsgToSingle( &msg, pChar );
        return;
    }

    // 已经在决斗了
    if(theDuelHandler()->IsInDuel(pAck->shDuelID))
        return;

    // 决斗
    theDuelHandler()->CreateDuel(pAck->shDuelID, GetID());
}

void GamePlayer::OnMsgCostSilverRepair(Msg* pMsg)
{       
    if ( pMsg == NULL )
    { return; }

    MsgRepairCostRmb costmsg;
    costmsg.header.stID = GetID();
    costmsg.nSilver = g_Cfg.m_nReqairRmb;

    GettheServer().SendMsgToSingle(&costmsg,this);
}


void GamePlayer::OnMsgDuelStart( Msg* pMsg )
{
    theDuelHandler()->DuelReady(GetID());
}

void GamePlayer::OnMsgDuelStop( Msg* pMsg)
{
    MsgDuelStop* pStop = (MsgDuelStop*)pMsg;
    if( pStop == NULL )
    { return; }

    if(pStop->shStopCharID == GetID())
    {
        theDuelHandler()->RemoveDuel(GetID());
    }
    else
    {
        if( theDuelHandler()->IsDuelFight(GetID(), pStop->shStopCharID) )
        {
            theDuelHandler()->OutDuleRange(pStop->shStopCharID);
        }
    }
}

void GamePlayer::OnChange_OwnAttribute(Msg* pMsg)
{
    MsgReqChangeOwnAttribute* pOwnAttribute = (MsgReqChangeOwnAttribute*)pMsg;
}

void GamePlayer::OnMsgRepairItem(Msg* pMsg)
{
    CHECK_MSGLEN( pMsg, MsgRepairItem);

    MsgRepairItem* pRepair = (MsgRepairItem*)pMsg;

    MsgRepairItemAck msgRepairAck;
    msgRepairAck.header.stID = GetID();
    int nItemHp = 0, nItemMaxHp = 0 ;
    int nAllSprice = 0;

    switch ( pRepair->eType )
    {
    case MsgRepairItem::RT_Pack:
    case MsgRepairItem::RT_Equip:
        {
            SCharItem* pCharItem = NULL;
            if ( pRepair->eType == MsgRepairItem::RT_Pack)
            {
                if ( pRepair->stIndex < 0 || pRepair->stIndex>_NormalItemBag.GetNowBagSize())
                { return; }
                pCharItem = _NormalItemBag.GetItemByIndex(pRepair->stIndex);
            }
            else if ( pRepair->eType == MsgRepairItem::RT_Equip )
            {
                if ( pRepair->stIndex < 0 || pRepair->stIndex>EEquipPartType_MaxEquitPart)
                { return; }
                pCharItem = GetVisualEquipItem( pRepair->stIndex );
            }

            if ( pCharItem == NULL || pCharItem->itembaseinfo.nOnlyInt != pRepair->nGuid )
            { return; }

            unsigned short usItemId = pCharItem->itembaseinfo.ustItemID;

            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(usItemId); 
            if ( pItemCommon == NULL || !pItemCommon->IsCanEquip() )
            { return; }

            ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*) pItemCommon;
            if ( pItemCanEquip == NULL || pItemCanEquip->uchRepairType != ItemDefine::SItemCanEquip::ECD_Repair_Normal )
            { return; }

            if ( pItemCanEquip->stHPMax != pCharItem->equipdata.usHpMax )
            {
                pCharItem->equipdata.usHpMax = pItemCanEquip->stHPMax;
            }

            nItemHp    = pCharItem->equipdata.usHP;
            nItemMaxHp = pCharItem->equipdata.usHpMax;
            if( nItemHp >= 0 && nItemHp < nItemMaxHp )
            {//这里说明耐久已经下降了　应该计算修理
                nAllSprice += pItemCanEquip->stRepairPrice * (nItemMaxHp - nItemHp);
            }

            if( nAllSprice > GetJiaoZiMoney() )
            {
                msgRepairAck.result = MsgRepairItemAck::error_noMoney;
                GettheServer().SendMsgToSingle(&msgRepairAck,this);
                return;
            }

            OperateJiaoZi( EOT_Sub, nAllSprice, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_RepairItem);

            pCharItem->equipdata.usHP = nItemMaxHp;

            msgRepairAck.eType        = pRepair->eType;
            msgRepairAck.stIndex      = pRepair->stIndex;
            msgRepairAck.nGuid        = pCharItem->itembaseinfo.nOnlyInt;
            msgRepairAck.nHp          = nItemMaxHp;
            msgRepairAck.fMaxHp       = nItemMaxHp;
            msgRepairAck.result       = MsgRepairItemAck::success;
            GettheServer().SendMsgToSingle(&msgRepairAck,this);

        }
        break;
    case MsgRepairItem::RT_All:
        {
            for( int i = 0; i < EEquipPartType_MaxEquitPart; ++i)
            {
                SCharItem* pCharItem = GetVisualEquipItem(i);
                if ( !pCharItem)
                { continue; }

                unsigned short usItemId = pCharItem->itembaseinfo.ustItemID;
                if ( usItemId == InvalidLogicNumber )
                { continue; }

                ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(usItemId); 
                if ( pItemCommon == NULL || !pItemCommon->IsCanEquip() )
                { continue; }

                ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*) pItemCommon;
                if ( pItemCanEquip == NULL || pItemCanEquip->uchRepairType != ItemDefine::SItemCanEquip::ECD_Repair_Normal )
                { continue; }

                if (pItemCanEquip->stHPMax != pCharItem->equipdata.usHpMax)
                {
                    pCharItem->equipdata.usHpMax = pItemCanEquip->stHPMax;
                }

                nItemHp    = pCharItem->equipdata.usHP;
                nItemMaxHp = pCharItem->equipdata.usHpMax;

                if( nItemHp >= 0 && nItemHp < nItemMaxHp )
                {//这里说明耐久已经下降了　应该计算修理
                    nAllSprice += pItemCanEquip->stRepairPrice * (nItemMaxHp - nItemHp);
                }
            }

            if( nAllSprice > GetJiaoZiMoney() )
            {
                msgRepairAck.result = MsgRepairItemAck::error_noMoney;
                GettheServer().SendMsgToSingle(&msgRepairAck,this);
                return;
            }

            OperateJiaoZi( EOT_Sub, nAllSprice, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_RepairItem);

            for( int i=0; i<EEquipPartType_MaxEquitPart; ++i)
            {
                SCharItem* pCharItem = GetVisualEquipItem(i);
                if ( pCharItem == NULL || pCharItem->itembaseinfo.ustItemID == InvalidLogicNumber || pCharItem->itembaseinfo.nOnlyInt <= 0 )
                { continue; }

                ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID ); 
                if ( pItemCommon == NULL || !pItemCommon->IsCanEquip() )
                { continue; }

                ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*) pItemCommon;
                if ( pItemCanEquip == NULL || pItemCanEquip->uchRepairType != ItemDefine::SItemCanEquip::ECD_Repair_Normal )
                { continue; }

                nItemHp    = pCharItem->equipdata.usHP;
                nItemMaxHp = pCharItem->equipdata.usHpMax;
                if( nItemHp >= 0 && nItemHp < nItemMaxHp )
                {
                    pCharItem->equipdata.usHP = nItemMaxHp;

                    msgRepairAck.eType   = MsgRepairItem::RT_Equip;//pRepair->eType;
                    msgRepairAck.stIndex = i;
                    msgRepairAck.nGuid   = pCharItem->itembaseinfo.nOnlyInt;
                    msgRepairAck.nHp     = nItemMaxHp;
                    msgRepairAck.fMaxHp  = nItemMaxHp;
                    msgRepairAck.result  = MsgRepairItemAck::success;
                    GettheServer().SendMsgToSingle(&msgRepairAck,this);
                }        
            }

            UpdateAllEquipData();
            UpdateAllSuitData() ;
            RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Equip );
        }
        break;
    default:
        break;
    }
}

void GamePlayer::OnMsgSpecialRepairItem( Msg* pMsg )
{
    MsgSpecialRepairItemReq* pReq = static_cast< MsgSpecialRepairItemReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    SCharItem* pCharItem = _NormalItemBag.GetItemByIndex( pReq->stEquipIndex );
    if ( pCharItem == NULL || pCharItem->itembaseinfo.nOnlyInt != pReq->nEquipGuid )
    { return; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if ( pItemCommon == NULL || !pItemCommon->IsCanEquip() )
    { return; }

    ItemDefine::SItemCanEquip* pItemCanEquip = static_cast< ItemDefine::SItemCanEquip* >( pItemCommon );
    if ( pItemCanEquip == NULL )
    { return; }

    MsgSpecialRepairItemAck xAck;
    xAck.stEquipIndex = pReq->stEquipIndex;
    xAck.nEquipGuid   = pReq->nEquipGuid;

    // 先计算钱
    int nCostMoney = ( pCharItem->equipdata.usHpMax - pCharItem->equipdata.usHP ) * pItemCanEquip->stRepairPrice;
    if ( GetJiaoZiMoney() < nCostMoney )
    {
        xAck.chResult = MsgSpecialRepairItemAck::ECD_NotEnoughMoney;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    switch ( pItemCanEquip->uchRepairType )
    {
    case ItemDefine::SItemCanEquip::ECD_Repair_Normal:     // 普通修理
        {
        }
        break;
    case ItemDefine::SItemCanEquip::ECD_Repair_Item:       // 需要道具
        {
            int nCount = GetItemCount( pItemCanEquip->nRepairValue );
            if ( nCount == 0 )
            {
                xAck.chResult = MsgSpecialRepairItemAck::ECD_NotItem;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

			SCharItem * _CItem = _NormalItemBag.GetItemByItemID(pItemCanEquip->nRepairValue);
			if(!_CItem)
			{
				_CItem = _MaterialItemBag.GetItemByItemID(pItemCanEquip->nRepairValue);
				if(!_CItem)
				 _CItem = _TaskItemBag.GetItemByItemID(pItemCanEquip->nRepairValue);
			}
             //LYH日志添加
			if(_CItem)
			{
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_CItem->GetItemID());
				if(_pitem)
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_CItem->GetItemID(),1,_CItem->GetItemGuid(),
					_CItem->GetItemCount()-1>=0?_CItem->GetItemCount()-1:0,eItemLogInfo_ItemConsume_Use,GetCharName(),_pitem->GetItemName());
			}

			 RemoveItem( pItemCanEquip->nRepairValue, 1 );
        }
        break;
    case ItemDefine::SItemCanEquip::ECD_Repair_Exploit:    // 需要功勋
        {
            if ( GetExploit() < pItemCanEquip->nRepairValue )
            {
                xAck.chResult = MsgSpecialRepairItemAck::ECD_NotEnoughExploit;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            OperateExploit( EOT_Sub, pItemCanEquip->nRepairValue, __FUNCTION__, __LINE__,ePlayerMoneySourceType_RepairItem );
        }
        break;
    case ItemDefine::SItemCanEquip::ECD_Repair_Reputation: // 需要名望
        {
            if ( GetReputation() < pItemCanEquip->nRepairValue )
            {
                xAck.chResult = MsgSpecialRepairItemAck::ECD_NotEnoughReputation;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            OperateReputation( EOT_Add, pItemCanEquip->nRepairValue, __FUNCTION__, __LINE__,ePlayerMoneySourceType_RepairItem );
        }
        break;
    case ItemDefine::SItemCanEquip::ECD_Repair_GuildOffer: // 需要帮贡
        {
            if ( GetGuildOffer() < pItemCanEquip->nRepairValue )
            {
                xAck.chResult = MsgSpecialRepairItemAck::ECD_NotEnoughGuildOffer;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            OperateGuildOffer( GuildDefine::OperateSub, pItemCanEquip->nRepairValue );
        }
        break;
    default:
        break;
    }

    pCharItem->equipdata.usHP = pCharItem->equipdata.usHpMax;

    OperateJiaoZi( EOT_Sub, nCostMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_RepairItem);

    xAck.fEquipHp = pCharItem->equipdata.usHP;
    xAck.nLeftMoney = GetMoney();
    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnMsgOnLineRewardReq( Msg* pMsg )
{
    MsgOnLineRewardReq* pReq = static_cast< MsgOnLineRewardReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( !g_Cfg.bOpenOnlineReward )
    { return; }

    MsgOnLineRewardAck xAck;
    xAck.nIndex = pReq->nIndex;

    //if ( GetLevel() < theOnLineRewardConfig.GetLevelLowLimit() || GetLevel() > theOnLineRewardConfig.GetLevelUpLimit() )
    //{ 
    //    xAck.uchResult = MsgOnLineRewardAck::ECD_NotReward;
    //    GettheServer().SendMsgToSingle( &xAck, this );
    //    return; 
    //}

    if ( BitValue< unsigned long >::GetBitValue( pReq->nIndex, gCharInfoServer.baseinfo.liveinfo.dwRewardItemInfo ) != BitValue< unsigned long >::NoneValue )
    {
        xAck.uchResult = MsgOnLineRewardAck::ECD_Already;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    const OnLineRewardConfig::OnLineReward* pReward = theOnLineRewardConfig.GetOnLineReward( pReq->nIndex );
    if ( pReward == NULL )
    { 
        xAck.uchResult = MsgOnLineRewardAck::ECD_NotReward;
        GettheServer().SendMsgToSingle( &xAck, this );
        return; 
    }

    // 转换成分钟计算 判断总在线时间
    if ( ( gCharInfoServer.baseinfo.liveinfo.dwOnlineTime + ( GetOnLineTime() + 59999 ) / 60000 ) < pReward->dwOnLineTime )
    {
        xAck.uchResult = MsgOnLineRewardAck::ECD_TimeLess;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    //判断背包是否有足够的地方
    int nNormalCnt( 0 ), nMaterialCnt( 0 ), nTaskCnt( 0 );
    for (int i = 0; i < OnLineRewardConfig::EConstDefine_RewardItemMaxSize; ++i)
    {
        if ( pReward->nItemID[i] == InvalidLogicNumber )
        { continue; }

        ItemDefine::SItemCommon *pItemDetail = NULL;
        pItemDetail = GettheItemDetail().GetItemByID( pReward->nItemID[i] );
        if( !pItemDetail )
            continue;

        SCharItem charItem;
        charItem.itembaseinfo.ustItemID = pItemDetail->ustItemID;
        charItem.itembaseinfo.ustItemCount = pReward->nCount[i];
        charItem.SetBounded( pReward->bIsBound[i] );
        
        bool bUseNewGrid = false;
        switch( GetBagTypeByItemType( pItemDetail->ucItemType ) )
        {
        case BT_NormalItemBag:
            {
                if( !_NormalItemBag.CanPushItem( charItem, bUseNewGrid ) )
                { 
					xAck.uchResult = MsgOnLineRewardAck::ECD_NormalPageFull;
					GettheServer().SendMsgToSingle( &xAck, this );
					return ; 
				}

                if (bUseNewGrid)
                { ++nNormalCnt; }
            }
            break;
        case BT_MaterialBag:
            {
                if( !_MaterialItemBag.CanPushItem( charItem, bUseNewGrid ) )
				{ 
					xAck.uchResult = MsgOnLineRewardAck::EDC_MaterialPageFull;
					GettheServer().SendMsgToSingle( &xAck, this );
					return ; 
				}

                if (bUseNewGrid)
                { ++nMaterialCnt; }
            }
            break;
        case BT_TaskBag:
            {
                if( !_TaskItemBag.CanPushItem( charItem, bUseNewGrid ) )
				{ 
					xAck.uchResult = MsgOnLineRewardAck::EDC_TaskBagFull;
					GettheServer().SendMsgToSingle( &xAck, this );
					return ; 
				}

                if (bUseNewGrid)
                { ++nTaskCnt; }
            }
            break;
        default:
            break;
        }
    }

    if( _NormalItemBag.GetNullItemCount() < nNormalCnt )
    {
        xAck.uchResult = MsgOnLineRewardAck::ECD_NormalPageFull;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    if( _MaterialItemBag.GetNullItemCount() < nMaterialCnt )
    {
        xAck.uchResult = MsgOnLineRewardAck::EDC_MaterialPageFull;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    if( _TaskItemBag.GetNullItemCount() < nTaskCnt )
    {
        xAck.uchResult = MsgOnLineRewardAck::EDC_TaskBagFull;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    bool bIsSuccess = true;
    int  errorIndex = 0;

    for (int i = 0; i < OnLineRewardConfig::EConstDefine_RewardItemMaxSize; ++i)
    {
        if ( pReward->nItemID[i] == InvalidLogicNumber )
        { continue; }

        if ( GettheItemDetail().IsEquipItem(pReward->nItemID[i]) )
        {
            if( AddEquipItem( pReward->nItemID[i], pReward->nCount[i], EIGS_OnlineReward, pReward->bIsBound[i], NULL, pReward->bIsStarRandom[i], pReward->nStarLevel[i] ) != ierr_Success )
            {
                bIsSuccess = false;
                errorIndex = i;
                break;
            }
        }
        else
        {
            if( AddItem( pReward->nItemID[i], pReward->nCount[i], EIGS_OnlineReward, pReward->bIsBound[i], NULL ) != ierr_Success )
            {
                bIsSuccess = false;
                errorIndex = i;
                break;
            }
        }

        
    }

    if (bIsSuccess)
    {
        BitValue< unsigned long >::SetBitValue( pReq->nIndex, gCharInfoServer.baseinfo.liveinfo.dwRewardItemInfo );
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }
    else
    {// 失败删除已领取物品
        for (int i = 0; i <= errorIndex; ++i)
        {
            if ( pReward->nItemID[i] == InvalidLogicNumber )
            { continue; }

           

			//LYH日志添加
			SCharItem * _CItem = _NormalItemBag.GetItemByItemID(pReward->nItemID[i]);
			if(!_CItem)
			{
				_CItem = _MaterialItemBag.GetItemByItemID(pReward->nItemID[i]);
				if(!_CItem)
					_CItem = _TaskItemBag.GetItemByItemID(pReward->nItemID[i]);
			}
			//LYH日志添加
			if(_CItem)
			{
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_CItem->GetItemID());
				if(_pitem)
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),pReward->nItemID[i],pReward->nCount[i],_CItem->GetItemGuid(),
					_CItem->GetItemCount()-pReward->nCount[i]>=0?_CItem->GetItemCount()-pReward->nCount[i]:0,eItemLogInfo_ItemConsume_OnLineReward,
					GetCharName(),_pitem->GetItemName());
			}
			 RemoveItem( pReward->nItemID[i], pReward->nCount[i] );
        }

        xAck.uchResult = MsgOnLineRewardAck::ECD_NormalPageFull;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }    
}

void GamePlayer::OnMsgBuyBackItemReq( Msg* pMsg )
{
    MsgBuyBackItemReq* pReq = static_cast< MsgBuyBackItemReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    SCharItem* pCharItem = m_xBuyBackItem.GetItemByIndex( pReq->uchIndex );
    if ( pCharItem == NULL )
    { return; }

    MsgBuyBackItemAck xAck;
    xAck.uchBuyBackPackIndex = pReq->uchIndex;
    xAck.n64BuyBackPackGuid  = pReq->n64Guid;
    if ( pCharItem->GetItemGuid() != pReq->n64Guid )
    {
        xAck.uchResult = MsgBuyBackItemAck::PackError;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if ( pItemCommon == NULL )
    { return; }

    int nCost = theNpcShop.GetPlayerSellNpcItemCost( pItemCommon->ustItemID , pCharItem->itembaseinfo.ustItemCount );

    // 扣钱
    int nSellMoney = 0;
    int nSellJiaoZi = 0;
    switch ( pItemCommon->costType )
    {
    case ItemDefine::CT_Money:
    case ItemDefine::CT_JiaoZi:
        {
           /* if (pCharItem->IsBounded())
            { nSellJiaoZi = nCost; }
            else
            { nSellMoney = nCost;  }*/
			nSellJiaoZi = nCost;
        }
        break;
    default:
        {// 非金钱购买装备建议玩家去装备回收 
            TellClient(theXmlString.GetString(eClient_AddInfo_2slk_35));
            return;
        }
        break;
    }

    if ( nSellMoney > GetMoney() )
    {
        xAck.uchResult = MsgBuyBackItemAck::NotEnoughMoney;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }
    if( nSellJiaoZi > GetJiaoZi() + GetMoney() )
    {
        xAck.uchResult = MsgBuyBackItemAck::NotEnoughMoney;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemBag* pItemBag = GetItemBagByItemType( pItemCommon->ucItemType );
    unsigned short ustCount = 0;
    if ( pItemBag->PushItem( *pCharItem, ustCount ) != ierr_Success )
    {
        xAck.uchResult = MsgBuyBackItemAck::PackFull;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    //Log( "回购物品[%s] [%I64u] 数量:[%d]", pItemCommon->GetItemName(), pCharItem->GetItemGuid(), pCharItem->GetItemCount() );
	Log( theXmlString.GetString(eServerLog_GetItemByHuiGou), pItemCommon->GetItemName(), pCharItem->GetItemGuid(), pCharItem->GetItemCount() );

    // 扣钱
    if ( nSellMoney > 0 )
    {
        OperateMoney( EOT_Sub, nSellMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_BuyBack);
    }
    if( nSellJiaoZi > 0)
    {
        OperateJiaoZi( EOT_Sub, nSellJiaoZi, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_BuyBack);
    }

    xAck.nLeftMoney  = GetMoney();
    xAck.ustBagIndex = pItemBag->GetItemIndexByGuid( pCharItem->itembaseinfo.nOnlyInt );
    GettheServer().SendMsgToSingle( &xAck, this );

    m_xBuyBackItem.RemoveItemByIndex( pReq->uchIndex ); // 删除回购背包中这个物品
}

void GamePlayer::OnMsgBuyBackItemListReq( Msg* pMsg )
{
    MsgBuyBackItemListAck xAck;

    m_xBuyBackItem.GetPack( xAck.xItemList, xAck.nCount, MsgBuyBackItemListAck::MaxItemCount );
    xAck.CalcLength();

    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnMsgBattleSignUpReq( Msg* pMsg )
{
    MsgBattleSignUpReq* pReq = static_cast< MsgBattleSignUpReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    MsgBattleSignUpAck xAck;
    xAck.uchType = pReq->ustType;

    switch ( pReq->ustType )
    {
    case BattleDefine::PlayerType:
        {
            if ( thePlayerBattleManager.IsAlreadySignUp( GetDBCharacterID() ) )
            {
                xAck.uchResult = MsgBattleSignUpAck::AlreadySignUp;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            PlayerBattleData* pBattleData = thePlayerBattleManager.GetBattleDateByMapID( pReq->ustMapID );
            if ( pBattleData == NULL )
            {
                xAck.uchResult = MsgBattleSignUpAck::BattleClosed;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            bool bErrorLevel = false;
            if ( pBattleData->GetMapLevel() == 55 ) // 55 级以上玩家 都能报名 55级 1v1擂台
            {
                if ( GetLevel() < 55 )
                { bErrorLevel = true; }
            }
            else
            {
                if ( GetLevel() < pBattleData->GetMapLevel() || GetLevel() > pBattleData->GetMapLevel() + 4 )
                { bErrorLevel = true; }
            }

            if ( bErrorLevel )
            {
                xAck.uchResult = MsgBattleSignUpAck::LevelLimit;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( pBattleData->GetWaitMapID() );
            if ( pMapData == NULL )
            { return; }

            // 不判断等级, 如果此类场景存在, 则说明战场已经开启
            uint32 dwMapId = theGameWorld.MakeEctypeStageID( pMapData, this );
            GameStage* pStage = theGameWorld.GetStageById( dwMapId );
            if ( pStage == NULL )
            {
                xAck.uchResult = MsgBattleSignUpAck::ErrorTime;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            if ( pBattleData->GetStatus() != BattleDefine::Status_SignUp )
            {
                xAck.uchResult = MsgBattleSignUpAck::ErrorTime;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            if ( !pBattleData->CheckCanSignUp( GetDBCharacterID() ) )
            {
                xAck.uchResult = MsgBattleSignUpAck::SignUpLimit;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            unsigned short ustResult = pBattleData->AddUnit( GetDBCharacterID() );
            if ( ustResult != BattleDefine::Success )
            {
                xAck.uchResult = ustResult;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            GettheServer().SendMsgToSingle( &xAck, this );  // 报名成功
            // 报名成功 飞入等待地图
            pBattleData->EnterWaitMap( GetDBCharacterID() );
        }
        break;
    case BattleDefine::TeamType:
        {
            GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
            if ( pTeam == NULL )
            {
                xAck.uchResult = MsgBattleSignUpAck::MustHaveTeam;
                SendMessageToClient( &xAck );
                return;
            }

            if ( !pTeam->IsTeamHeader( GetDBCharacterID() ) )
            {
                xAck.uchResult = MsgBattleSignUpAck::MustTeamHeader;
                SendMessageToClient( &xAck );
                return;
            }

            if ( theTeamBattleManager.IsAlreadySignUp( GetTeamID() ) )
            {
                xAck.uchResult = MsgBattleSignUpAck::AlreadySignUp;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            TeamBattleData* pBattleData = theTeamBattleManager.GetBattleDateByMapID( pReq->ustMapID );
            if ( pBattleData == NULL )
            {
                xAck.uchResult = MsgBattleSignUpAck::BattleClosed;
                SendMessageToClient( &xAck );
                return;
            }

            if ( pBattleData->GetStatus() != BattleDefine::Status_SignUp )
            {
                xAck.uchResult = MsgBattleSignUpAck::ErrorTime;
                SendMessageToClient( &xAck );
                return;
            }

            if ( !pBattleData->CheckCanSignUp( GetTeamID() ) )
            {
                xAck.uchResult = MsgBattleSignUpAck::SignUpLimit;
                SendMessageToClient( &xAck );
                return;
            }

            unsigned short ustResult = pBattleData->AddUnit( GetTeamID() );
            if ( ustResult != BattleDefine::Success )
            {
                xAck.uchResult = ustResult;
                SendMessageToClient( &xAck );
                return;
            }

            SendMessageToClient( &xAck );
        }
        break;
    case BattleDefine::GuildType:
        break;
    default:
        return;
    }
}

void GamePlayer::OnMsgChangeNameReq( Msg* pMsg )
{
    MsgChangeNameReq* pReq = static_cast< MsgChangeNameReq* >( pMsg );

    HelperFunc::CheckStringValid( pReq->name, sizeof( pReq->name ) );
    if (!CChatCheck::getInstance()->CheckStringInLow( pReq->name ))
    { return; }

    DBMsgReqCreateCheckName msgDBCreateCheckName;
    msgDBCreateCheckName.header.stID = GetID();
    strncpy_s( msgDBCreateCheckName.szName, sizeof( msgDBCreateCheckName.szName ), pReq->name, sizeof(msgDBCreateCheckName.szName)-1 );
    msgDBCreateCheckName.checkType = DBMsgReqCreateCheckName::ECT_ChangeName;
    GettheDBCon().SendMsg( &msgDBCreateCheckName, GetLifeCode() );
}

void GamePlayer::OnMsgCancelBuff( Msg* pMsg )
{
    MsgCancelBuff* pMessage = (MsgCancelBuff*)pMsg;

    int index = _buffManager.GetBufferStatusIndexById( pMessage->buffId );
    if ( index < 0)
    { return; }

    SCharBuff* pStatus = _buffManager.GetBuff( index );
    if ( NULL == pStatus)
    { return; }

    ItemDefine::SItemStatus* pItemStatusConfig = GettheItemDetail().GetStatus( pStatus->StatusID, pStatus->iLevel);
    if ( NULL == pItemStatusConfig || !pItemStatusConfig->canCancel )
    { return; }

    if ( _buffManager.ClearBuff( index  ))
    { 
        OnBuffStatusChanged( true );
        Log( theXmlString.GetString( eLog_CancelStatus ), pItemStatusConfig->GetItemName());
    }
}

void GamePlayer::OnMsgJiFengShopItemsListReq ( Msg* pMsg )
{
    DBMsgJiFengShopItemsListReq msg;
    msg.header.stID = GetID();
    msg.accountId   = GetAccountID();
    GettheDBCon().SendMsg( &msg, GetLifeCode() );
}

void GamePlayer::OnMsgJiFengShopItemsGain( Msg* pMsg )
{
    MsgJiFengShopItemsGain* pMessage = (MsgJiFengShopItemsGain*)pMsg;
    if ( pMessage->count > gJiFengGainMaxCount )
    { return; }

    uint16 nNormalBagItemIndexCount = 0, nMaterialBagItemIndexCount = 0;
    for ( int i=0; i<pMessage->count; ++i )
    {
        if ( pMessage->record[i].itemId == 0)
        { continue; }

        ItemDefine::SItemCommon* pItemCommonConfig = GettheItemDetail().GetItemByID( pMessage->record[i].itemId );
        if ( NULL == pItemCommonConfig)
        { 
            MsgAckResult msg;
            msg.result = ER_SystemException;
            GettheServer().SendMsgToSingle( &msg, this );
            return;
        }

        switch ( pItemCommonConfig->ucItemType )
        {
        case ItemDefine::ITEMTYPE_MATERIAL:
            { ++nMaterialBagItemIndexCount; }
            break;
        default:
            { ++nNormalBagItemIndexCount; }
            break;
        }
    }

    uint16 nNormalBagItemEmptyCount = _NormalItemBag.GetItemEmptyCount();
    uint16 nMaterialItemEmptyCount  = _MaterialItemBag.GetItemEmptyCount();

    if ( pMessage->count > (nNormalBagItemEmptyCount + nMaterialItemEmptyCount ) || 
        nNormalBagItemIndexCount > nNormalBagItemEmptyCount || 
        nMaterialBagItemIndexCount > nMaterialItemEmptyCount )
    {
        MsgGetItem2 ack;
        ack.enResult = MsgGetItem2::RESULT_NOSPACE;
        GettheServer().SendMsgToSingle( &ack, this );
        return;
    }

    DBMsgJiFengShopItemsGainReq dbReq;
    dbReq.header.stID = GetID();
    dbReq.accountId = GetAccountID();
    dbReq.count = pMessage->count;
    for ( int i=0; i<pMessage->count; ++i)
    { dbReq.ids[i] = pMessage->record[i].id; }

    dbReq.RecalLength();
    GettheDBCon().SendMsg( &dbReq, GetLifeCode() );
}

void GamePlayer::OnDBMsgJiFengShopItemsListAck( Msg* pMsg )
{
    DBMsgJiFengShopItemsListAck* pMessage = (DBMsgJiFengShopItemsListAck*)pMsg;

    MsgJiFengShopItemsListAck ack;
    ack.isNew = pMessage->isNew;

    SJiFengItemRecordClient info;
    for ( int i=0; i<pMessage->count; ++i )
    {
        if ( i>=MsgJiFengShopItemsListAck::ECD_MaxJiFengItemCount)
        { break; } // 一个发包大小 MsgJiFengShopItemsListAck 与 DBMsgJiFengShopItemsListAck相同 不会出现IsFull

        memset( &info, 0, sizeof(info));
        info.id         = pMessage->items[i].id;
        info.itemType   = pMessage->items[i].info.itemType;
        info.itemId     = pMessage->items[i].info.itemId;
        info.itemCount  = pMessage->items[i].info.itemCount;
        memcpy_s( info.value, sizeof(info.value), pMessage->items[i].info.value, sizeof(info.value) );

        ack.AddItem( info );
    }
    GettheServer().SendMsgToSingle( &ack, this );
}

void GamePlayer::OnDBMsgJiFengShopItemsGainAck( Msg* pMsg )
{
    DBMsgJiFengShopItemsGainAck* pMessage = (DBMsgJiFengShopItemsGainAck*)pMsg;

    if ( pMessage->count == 0)
    { 
        MsgAckResult msg;
        msg.result = ER_JiFengGainNotItem;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    for ( size_t i=0; i<pMessage->count; ++i )
    {
        uint16 itemId    = pMessage->items[i].info.itemId;
        uint16 itemCount = pMessage->items[i].info.itemCount;

        ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( itemId );
        if ( pItemDetail == NULL )
        {
           // Log("积分领取物品[%d:%d]失败 没有物品配置", itemId, itemCount );
			Log(theXmlString.GetString(eServerLog_JiFenDuiHuanNoOk), itemId, itemCount );
            continue;
        }

        __int64 n64Guid = 0;
        if ( AddItem( itemId, itemCount, EIGS_JiFengShop, true, &n64Guid ) != ierr_Success )
        {
           // Log("积分领取物品[%d:%s:%d]失败 背包满", itemId, pItemDetail->GetItemName(), itemCount );
			Log(theXmlString.GetString(eServerLog_JiFenDuiHuanNoOk1), itemId, pItemDetail->GetItemName(), itemCount );
            continue;
        }
       
        //Log("积分领取物品[%d:%s:%d:%I64u]成功", itemId, pItemDetail->GetItemName(), itemCount, n64Guid );        
        //ShoppingLog("积分领取物品[%d:%s:%d:%I64u]成功", itemId, pItemDetail->GetItemName(), itemCount, n64Guid ); 

		Log(theXmlString.GetString(eServerLog_JiFenDuiHuanOk), itemId, pItemDetail->GetItemName(), itemCount, n64Guid );        
		ShoppingLog(theXmlString.GetString(eServerLog_JiFenDuiHuanOk), itemId, pItemDetail->GetItemName(), itemCount, n64Guid ); 
    }

    MsgAckResult msg;
    msg.result = ER_JiFengGainSuccess;
    GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnMsgUpdateTradeShopConfigReq( Msg* pMsg )
{
    MsgUpdateTradeShopConfig tradeShop;
    tradeShop.Clone( theTradeCenter.gszZibFileBuffer, theTradeCenter.gnZibFileBufferSize, true );
    GettheServer().SendMsgToSingle( &tradeShop, this );
}

void GamePlayer::OnMsgSendMailReq( Msg* pMsg )
{ // 发邮件
    MsgSendMailReq* pMessage = (MsgSendMailReq*)pMsg;

    _mailManager.BeginSendMail( pMessage );
}

void GamePlayer::OnMsgOpMailReq( Msg* pMsg )
{
    MsgOpMailReq* pMessage = (MsgOpMailReq*)pMsg;

    switch ( pMessage->op )
    {
    case EMO_Delete:
       // Log("请求删除邮件(%u)",pMessage->mailId);
		Log(theXmlString.GetString(eServerLog_DeleMail),pMessage->mailId);
        break;
    case EMO_Open:
      //  Log("请求打开邮件(%u)",pMessage->mailId);
		 Log(theXmlString.GetString(eServerLog_OpenMail),pMessage->mailId);
        break;
    case EMO_GetMoney:
        //Log("请求领钱邮件(%u)",pMessage->mailId);
		Log(theXmlString.GetString(eServerLog_MoneyMail),pMessage->mailId);
        break;
    case EMO_GetAccessory:
        {
           // Log("请求领物品邮件(%u)",pMessage->mailId);
			Log(theXmlString.GetString(eServerLog_ItemMail),pMessage->mailId);
            switch ( pMessage->accessory )
            {
            case SMail::EAT_Item:
                {
                    if ( (_NormalItemBag.GetItemEmptyCount() < 1 && BT_NormalItemBag == pMessage->bagType) || 
                        (_MaterialItemBag.GetItemEmptyCount() < 1 && BT_MaterialBag == pMessage->bagType))
                    {
                        return;
                    }

                }
                break;
            case SMail::EAT_Mount:
                {
                    if ( _mountManager.GetMountEmptyCount() < 1  )
                    {
                        return;
                    }
                }
                break;
            case SMail::EAT_Pet:
                {
                    if ( _petManager.GetPetEmptyCount() < 1  )
                    {
                        return;
                    }
                }
                break;
            }
        }
        break;
    default:
        return;
        break;
    }

    GS2CSOpMailReq msg;
    msg.op     = pMessage->op;
    msg.mailId = pMessage->mailId;
    msg.accountId = GetAccountID();
    msg.charDbId  = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &msg );
}

void GamePlayer::OnMsgEnterTeamBattleAck( Msg* pMsg )
{
    MsgEnterTeamBattleAck* pAck = static_cast< MsgEnterTeamBattleAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    m_xWaitChangeStage.xTimer.StartTimer( HQ_TimeGetTime(), 60 );
}

void GamePlayer::OnMsgLeaveBattleReq( Msg* pMsg )
{
    MsgLeaveBattleReq* pReq = static_cast< MsgLeaveBattleReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    switch ( pReq->uchType )
    {
    case BattleDefine::PlayerType:
        {
        }
        break;
    case BattleDefine::TeamType:
        {
            TeamBattleData* pBattleData = theTeamBattleManager.GetBattleDateByMapID( EctypeId2MapId( GetMapID() ) );
            if ( pBattleData == NULL )
            { return; }

            MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( pBattleData->GetFightMapID() );
            if ( pMapData == NULL )
            { return; }

            MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
            if ( pRelive != NULL )
            {
                FlyToMapReq( pRelive->MapId, pRelive->PositionX, pRelive->PositionY, pRelive->Direction );
            }
        }
        break;
    default:
        return;
    }
}

// 使用表情动作
void GamePlayer::OnMsgQueryExpression( Msg* pMsg )
{
    MsgQueryExpression* pReq = static_cast< MsgQueryExpression* >( pMsg );
    if ( pReq == NULL )
    { return; }

    // 先判断是否有这个表情动作
    const ExpAction* pExpAction = theExpActionConfig.GetExpAction( pReq->ustActionID );
    if ( pExpAction == NULL )
    { return; }

    // 判断冷却时间
    if ( !GameTime::IsPassCurrentTime( m_dwExpressionTime, theExpActionConfig.GetExpActionCD() ) )
    { return; }

    // 判断状态是否能使用表情
    if ( _mountManager.GetActiveBeRiding() || IsOpenStall() || !IsCanDoAction() )     
    { return; }

    // 判断对象是否在范围内
    if ( pReq->stTargetID != -1 )
    {
        BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( pReq->stTargetID );
        if ( pTarget == NULL || !pTarget->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), static_cast< float >( theExpActionConfig.GetTargetMaxDist() ) ) )
        { return; }
    }

    m_dwExpressionTime = HQ_TimeGetTime();  // 保存发表情的时间

    // 发送给周围玩家
    MsgAckExpression xAck;
    xAck.header.stID = GetID();
    xAck.ustActionID = pReq->ustActionID;
    xAck.stTargetID  = pReq->stTargetID;
    GettheServer().SendMsgToView( &xAck, GetID(), false );

    // 处理引导任务
    ProcessGuideQuest( GuideQuest::Guide_Expression );
}

void GamePlayer::OnMsgQueryBattleTeamInfoReq( Msg* pMsg )
{
    MsgQueryBattleTeamInfoReq* pReq = static_cast< MsgQueryBattleTeamInfoReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    TeamBattleData* pBattleData = theTeamBattleManager.GetBattleDateByMapID( pReq->ustMapID );
    if ( pBattleData == NULL )
    { return; }

    GameTeam* pTeam = pBattleData->GetUnit( pReq->dwTeamID );
    if ( pTeam == NULL )
    { return; }

    MsgQueryBattleTeamInfoAck xAck;
    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
        if ( pMember == NULL )
        { continue; }

        MsgQueryBattleTeamInfoAck::MemberInfo xInfo;
        strncpy_s( xInfo.szName, sizeof( xInfo.szName ), pMember->GetName(), sizeof( xInfo.szName ) - 1 );
        xInfo.uchProfession = pMember->GetProfession();
        xInfo.ustLevel = pMember->GetLevel();
        xAck.AddMemberInfo( xInfo );
    }

    SendMessageToClient( &xAck );
}

void GamePlayer::OnMsgQueryTeamRecordReq( Msg* pMsg )
{
    MsgQueryTeamRecordReq* pReq = static_cast< MsgQueryTeamRecordReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    TeamBattleData* pBattleData = theTeamBattleManager.GetBattleDateByMapID( pReq->ustMapID );
    if ( pBattleData == NULL )
    { return; }

    BattleDefine::BattleRecord* pRecord = pBattleData->GetBattleRecord( GetTeamID() );
    if ( pRecord == NULL )
    { return; }

    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    { return; }

    MsgQueryTeamRecordAck xAck;
    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
        if ( pMember == NULL )
        { continue; }

        MsgQueryTeamRecordAck::RecordInfo xInfo;
        strncpy_s( xInfo.szName, sizeof( xInfo.szName ), pMember->GetName(), sizeof( xInfo.szName ) - 1 );
        BattleDefine::KillInfo* pInfo = pBattleData->GetBattleKillInfo( pMember->GetID() );
        if ( pInfo != NULL )
        {
            xInfo.nIntegral   = pInfo->GetIntegral();
            xInfo.nKillCount  = pInfo->GetKillCount();
            xInfo.nDeathCount = pInfo->GetBeKillCount();
        }

        xAck.AddRecord( xInfo );
    }

    SendMessageToClient( &xAck );
}

void GamePlayer::OnMsgQueryBattleSignUpTimeReq( Msg* pMsg )
{
    MsgQueryBattleSignUpTimeReq* pReq = static_cast< MsgQueryBattleSignUpTimeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    switch ( pReq->uchType )
    {
    case BattleDefine::PlayerType:
        {

        }
        break;
    case BattleDefine::TeamType:
        {
            MsgQueryBattleSignUpTimeAck xAck;
            xAck.uchType  = pReq->uchType;
            xAck.ustMapID = pReq->ustMapID;

            TeamBattleData* pBattleData = theTeamBattleManager.GetBattleDateByMapID( pReq->ustMapID );
            if ( pBattleData == NULL || pBattleData->GetStatus() == BattleDefine::Status_Close )  // 战场结束了
            { 
                xAck.dwLeftTime = ErrorUnsignedLongID;
                SendMessageToClient( &xAck );
                return; 
            }

            if ( pReq->bIsPassSignTime )
            {
                if ( pBattleData->GetStatus() != BattleDefine::Status_SignUp )
                {
                    xAck.dwLeftTime = pBattleData->GetFightTime() - ( HQ_TimeGetTime() - pBattleData->GetStartFightTime() );
                    if ( xAck.dwLeftTime > pBattleData->GetFightTime() )
                    { return; }
                    SendMessageToClient( &xAck );
                }
            }
            else
            {
                if ( pBattleData->GetStatus() == BattleDefine::Status_SignUp )
                {
                    xAck.bIsAlreadlySignUp = true;
                    xAck.dwLeftTime = pBattleData->GetSignUpTime() - ( HQ_TimeGetTime() - pBattleData->GetStartSignUpTime() );
                    if ( xAck.dwLeftTime > pBattleData->GetSignUpTime() || xAck.dwLeftTime < 1500 )
                    { return; }
                    SendMessageToClient( &xAck );
                }
            }

        }
        break;
    default:
        break;
    }
}

void GamePlayer::OnMsgCharAssignPotential( Msg* pMsg )
{
    MsgCharAssignPotential* pPotential = static_cast< MsgCharAssignPotential* >( pMsg );
    if ( pPotential == NULL )
    { return; }

    int nPotential = 0;
    for (int i=0;i<EBaseAttr_MaxSize;i++)
    {
        if ( pPotential->nValue[i] < 0 )
        {
            MsgAckResult msg;
            msg.result = ER_CharAssignPotential;
            GettheServer().SendMsgToSingle( &msg, this );
            return;
        }

        nPotential += pPotential->nValue[i];
    }

    if ( gCharInfoServer.baseinfo.liveinfo.basePotential < nPotential )
    {
        MsgAckResult msg;
        msg.result = ER_CharAssignPotential;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }
    
    for (int i=0;i<EBaseAttr_MaxSize;i++)
    {
        gCharInfoServer.baseinfo.liveinfo.basePotential   -= pPotential->nValue[i];
        gCharInfoServer.baseinfo.liveinfo.baseAssignValue[i] += pPotential->nValue[i];
    }

    RecalcBaseProperty( true, BV_NotFullHp, BV_SendMessage, EWRP_Potential ); 

    MsgCharAssignPotentialAck msg;
    msg.basePotential = gCharInfoServer.baseinfo.liveinfo.basePotential;
    memcpy(msg.nValue, gCharInfoServer.baseinfo.liveinfo.baseAssignValue, sizeof(msg.nValue));
    GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnMsgLearnXinFa( Msg* pMsg )
{
    MsgLearnXinFa* pLearnXinFa = static_cast< MsgLearnXinFa* >( pMsg );
    if ( pLearnXinFa == NULL )
    { return; }

    LearnXinFa( pLearnXinFa->nXinFaID, pLearnXinFa->nXinFaLevel );
}

uint16 GetProtectMatrialID(uint16 item_level, uint16& protectLevel)
{
	if (item_level >= 4 && item_level < 7)
	{
		protectLevel = 4;
		return SID_ProtectMountFour;
	}
	else if (item_level >= 7 && item_level < 10)
	{
		protectLevel = 7;
		return SID_ProtectMountSeven;
	}
	else if (item_level >= 10)
	{
		protectLevel = 10;
		return SID_ProtectMountTen;
	}
	else
	{
		protectLevel = 0;
		return 0xffff;
	}
}
void GamePlayer::OnMsgMountStrengthen( Msg* pMsg )
{
	MsgMountStrengthen* pMountStrengthen = static_cast<MsgMountStrengthen*>(pMsg);
	if (!pMountStrengthen)
		return;
	SMountItem* pMount = _mountManager.GetMountByIndex(pMountStrengthen->mountIndex);
	if (!pMount || pMount->GetMountGuid() != pMountStrengthen->mountGuid)
		return;
	ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( pMount->baseInfo.id );
	if ( !pDrome ) 
		return;
	// 是否有材料
	SCharItem* pMaterialItem = _MaterialItemBag.GetItemByIndex(pMountStrengthen->materialIndex);
	if (!pMaterialItem || pMaterialItem->GetItemGuid() != pMountStrengthen->materialGuid )
	{
		_MaterialItemBag.CleanUp();
		return;
	}
	ItemDefine::SCreateMaterial* pMeterialItemConfig = (ItemDefine::SCreateMaterial*) GettheItemDetail().GetItemByID( pMaterialItem->itembaseinfo.ustItemID );
	if ( !pMeterialItemConfig )
		return; 
	if ( pMeterialItemConfig->stMaterialType != ItemDefine::ematerial_mountrune )
		return;
	// 已经是最高星级
	if (pMount->baseInfo.level >= SMountItem::MICD_MountMaxLevel)
		return;

	unsigned short oldLev[1] = {pMount->baseInfo.level};

	const MountStrengthenData* pData = theMountStrengthenConfig.GetMountStrengthenData(pMount->baseInfo.id);
	if (!pData)
		return;
	//先判断钱够不够
	if ( pData->GetPrice(pMount->baseInfo.level) > GetJiaoZiMoney() )
		return;

	float fProbability = pData->GetProbability(pMount->baseInfo.level);
	int nMomey = pData->GetPrice(pMount->baseInfo.level);

	uint16 nResult = MsgMountStrengthenAck::eR_Success;
	uint8  nRandNum = theRand.rand16() % RAND_NUM;

	uint16 protectLevel = 0; //被保护到的等级
	uint16 protectItemId = GetProtectMatrialID(pMount->baseInfo.level, protectLevel);
	uint16 nLossLevel = 0;
	uint16 nLevel = pMount->baseInfo.level;

	//LYH日志添加
	SCharItem* _SCharItem = GetBagItemByGuid(pMountStrengthen->materialGuid);
	// 扣除材料
	if (!RemoveItem(BT_MaterialBag, pMountStrengthen->materialIndex, NUMERIC_ONE, pMountStrengthen->materialGuid))
		return;
	else
	{
        ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_SCharItem->GetItemID());
		SCharItem* _SCharItem2 = GetBagItemByGuid(pMountStrengthen->materialGuid);
		if(_SCharItem && _pitem)		
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_SCharItem->GetItemID(),NUMERIC_ONE,pMountStrengthen->materialGuid,
		_SCharItem2?_SCharItem2->GetItemCount():0 ,eItemLogInfo_ItemConsume_UpItem,
		                                  GetCharName(),_pitem->GetItemName());
	}

	if ( nRandNum > fProbability * RAND_NUM )
	{
		nResult = MsgMountStrengthenAck::eR_Fail;
		if (pMountStrengthen->protectNum && protectLevel > 0)
		{
			//扣除保星材料
		 int64 _Guid = GetItemGUIDByItemID(protectItemId);
			bool ReMoveOK = false;
		    ReMoveOK = RemoveItem(protectItemId, NUMERIC_ONE);
			if (protectItemId == 0xffff|| !ReMoveOK)
				pMount->baseInfo.level = pData->GetLossToLevel(pMount->baseInfo.level);
			else
				pMount->baseInfo.level = protectLevel;

			if(ReMoveOK)
			{   //LYH日志添加
				 ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(protectItemId);
				 SCharItem* _SCharItem2 = GetBagItemByGuid(_Guid);
				 if (_pitem)
				      theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),protectItemId,1,_Guid,
					  _SCharItem2?_SCharItem2->GetItemCount():0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
			}
		}
		else
			pMount->baseInfo.level = pData->GetLossToLevel(pMount->baseInfo.level);

		nLossLevel = nLevel - pMount->baseInfo.level;
	}
	else
	{
		pMount->baseInfo.level += 1;

		if (pMountStrengthen->protectNum && protectItemId != 0xffff)
		{
			
			//LYH日志添加
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(protectItemId);
			SCharItem *_item = GetBagItemByGuid(GetItemGUIDByItemID(protectItemId));
			if(_pitem && _item)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),protectItemId,1,GetItemGUIDByItemID(protectItemId),
			_item->GetItemCount()-1>0?_item->GetItemCount()-1:0, eItemLogInfo_ItemConsume_UpItem,
			                                  GetCharName(),_pitem->GetItemName());

			RemoveItem(protectItemId, NUMERIC_ONE);

			
		}
			
	}

	if (nMomey > 0)
		OperateJiaoZi( EOT_Sub, nMomey, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_MountStreng);

	//计算加的属性
	if (nLossLevel > 0 && nResult == MsgMountStrengthenAck::eR_Fail)
	{
		for (int i = (int)(nLevel - 1); i >= (nLevel - nLossLevel); i--)
		{
			pMount->baseInfo.potentialAttribute[EBaseAttr_Strength] -= pData->GetStrength(i);
			pMount->baseInfo.potentialAttribute[EBaseAttr_Agility] -= pData->GetAgility(i);
			pMount->baseInfo.potentialAttribute[EBaseAttr_Stamina] -= pData->GetStamina(i);
			pMount->baseInfo.potentialAttribute[EBaseAttr_Intelligence] -= pData->GetIntelligence(i);
		}

		if (pMount->baseInfo.potentialAttribute[EBaseAttr_Strength] < 0.0f)
			pMount->baseInfo.potentialAttribute[EBaseAttr_Strength] = 0.0f;
		if (pMount->baseInfo.potentialAttribute[EBaseAttr_Agility] < 0.0f)
			pMount->baseInfo.potentialAttribute[EBaseAttr_Agility] = 0.0f;
		if (pMount->baseInfo.potentialAttribute[EBaseAttr_Stamina] < 0.0f)
			pMount->baseInfo.potentialAttribute[EBaseAttr_Stamina] = 0.0f;
		if (pMount->baseInfo.potentialAttribute[EBaseAttr_Intelligence] < 0.0f)
			pMount->baseInfo.potentialAttribute[EBaseAttr_Intelligence] = 0.0f;
	}
	else if (nResult == MsgMountStrengthenAck::eR_Success)
	{
		pMount->baseInfo.potentialAttribute[EBaseAttr_Strength] += pData->GetStrength(pMount->baseInfo.level - 1);
		pMount->baseInfo.potentialAttribute[EBaseAttr_Agility] += pData->GetAgility(pMount->baseInfo.level - 1);
		pMount->baseInfo.potentialAttribute[EBaseAttr_Stamina] += pData->GetStamina(pMount->baseInfo.level - 1);
		pMount->baseInfo.potentialAttribute[EBaseAttr_Intelligence] += pData->GetIntelligence(pMount->baseInfo.level - 1);	
	}
	// 重新计算属性
	pMount->baseInfo.UpdateCurrentAttribute();
	//如果是出战坐骑会对人物属性产生作用
	if (_mountManager.GetActiveMountIndex() == pMountStrengthen->materialIndex)
	{ 
		RefreshMountAttr();
		SendCharAttibuteToClient();
		//_mountManager.ApplyMountAttributeToChar( false, true );	//RefreshMountAttr中已经做了
	}

	 // >=10 系统提示 
	if (nResult == MsgMountStrengthenAck::eR_Success && pMount->baseInfo.level >= 10)
	{
		MsgChat chat(MsgChat::CHAT_TYPE_PROGRAM_SYSTEM);
		chat.type = BT_MountBag;
		chat.nHyberItemCnt = 1;
		chat.onlyId[0] = pMount->GetMountGuid();
		chat.itemId[0] = pMount->GetMountID();

		//Common::_tstring strName = pMount->GetMountName();

		char bufStr[BUFSIZ] = {0};
		sprintf_s( bufStr,sizeof(bufStr),theXmlString.GetString(eTellClient_MountLevelUpTo10), GetCharName(), /*strName.c_str()*/pDrome->GetName(), s_szChineseNumericString[pMount->baseInfo.level] );

		ProcessSystem( bufStr, SystemWorld, &chat );
	}

	//添加卡牌
	if ( nResult == MsgMountStrengthenAck::eR_Success )
	{
		short stCardId = theCardIconConfig.GetCardIdByTypeId( pMount->baseInfo.id );
		if ( stCardId != -1 )
		{
			AddCard( stCardId, pMount->baseInfo.level );
		}
	}
	
	MsgMountStrengthenAck msg;
	msg.mount = *pMount;
	msg.result = nResult;
	msg.loselevel = nLossLevel;
	GettheServer().SendMsgToSingle( &msg, this);

	//触发7天乐
	_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_FifthDay );

	//触发坐骑强化
	_achieveManager.UpdateTriggerByValueType( EAT_MountLevel , pMount->baseInfo.level );

	//LYH日志添加
	unsigned short curLev[1] = {pMount->baseInfo.level};
	theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pMount->GetMountID(),1,pMount->GetMountGuid(),eItemLogInfo_ItemUpgrade_MountIntensify,
		                              nResult,oldLev,curLev,GetCharName(),pMount->GetMountName());
}

//分配坐骑潜力点
void GamePlayer::OnMsgMountPotential( Msg* pMsg )
{
    MsgMountPotential* pPotential = static_cast< MsgMountPotential* >( pMsg );
    if ( pPotential == NULL )
    { return; }

    SMountItem* pMount = _mountManager.GetMountByIndex(pPotential->index);
    if ( pMount == NULL || pMount->GetMountGuid() != pPotential->guid )
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountData;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    int nPotential = 0;
    for (int i=0;i<EBaseAttr_MaxSize;i++)
    {
        nPotential += pPotential->value[i];
    }

    if (pMount->baseInfo.nPotentialPoint < nPotential)
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountPotential;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    for (int i=0;i<EBaseAttr_MaxSize;i++)
    {
        pMount->baseInfo.potentialAttribute[i] += pPotential->value[i];
        pMount->baseInfo.nPotentialPoint -= pPotential->value[i];
    }
    // 重新计算属性
    pMount->baseInfo.UpdateCurrentAttribute();

	//如果是出战坐骑会对人物属性产生作用
	if (_mountManager.GetActiveMountIndex() == pPotential->index)
	{ 
		RefreshMountAttr();
		SendCharAttibuteToClient();
		//_mountManager.ApplyMountAttributeToChar( false, true );	//RefreshMountAttr中已经做了
	}

    MsgUpdateMount msg;
    msg.header.stID = this->GetID();
    msg.mount = *pMount;
    GettheServer().SendMsgToSingle( &msg, this);
}

//void GamePlayer::OnMsgCharacterLevelUp( Msg* pMsg )
//{
//    MsgCharacterLevelup* pMsgLevelUp = static_cast< MsgCharacterLevelup* >( pMsg );
//    if (pMsgLevelUp == NULL)
//    { return; }
//
//    int64 nCurExp = this->GetPlayerCurrentExp();
//
//    // 每次升1级
//    int nNewLevel = theExpStage.GetLevel( nCurExp ); 
//    int nOldLevel = this->GetLevel();
//    if( nOldLevel < nNewLevel && nNewLevel <= g_Cfg.m_nLevelLimt )
//    {
//        this->ChangeLevel( nOldLevel + 1 );    
//        this->Log(theXmlString.GetString(eLog_info_2slk_29),nOldLevel,nNewLevel);
//
//		// 玩家达到30级，广播给所有帮派帮主其升级消息 luo.qin 4.20 begin
//		int nLevel = theGuildConfig.GetJoinSetting().GetLevel();
//		if ( ( nOldLevel < nLevel ) && ( nNewLevel >= nLevel ) )
//		{
//			GameGuild* pGuild = theGameGuildManager.GetGuildByPlayerID( GetDBCharacterID() );
//			if ( !pGuild )
//			{
//				// 通知CenterServer处理
//				GS2CSPlayerLvUpToThirtyMessage xReq;
//				xReq.nPlayerID	= GetDBCharacterID();
//				xReq.nPlayerLv  = this->GetLevel();
//				HelperFunc::SafeNCpy( xReq.szSpeakName, GetCharName(), sizeof( xReq.szSpeakName ) );
//				GettheServer().SendMsgToCenterServer( &xReq );
//			}
//
//			return;
//		}
//
//		// 玩家达到10级，广播给所有的家族族长其升级消息 
//		nLevel = theFamilyConfig.GetJoinSetting().GetLevelLimit();
//		if ( ( nOldLevel < nLevel ) && ( nNewLevel >= nLevel ) )
//		{
//			GameFamily* pFamily = theGameFamilyManager.GetFamilyByPlayerID( GetDBCharacterID() );
//			if ( !pFamily )
//			{
//				// 通知CenterServer处理
//				GS2CSFamilyPlayerLvUpToTenMessage xReq;
//				xReq.nPlayerID	= GetDBCharacterID();
//				xReq.nPlayerLv  = this->GetLevel();
//				HelperFunc::SafeNCpy( xReq.szSpeakName, GetCharName(), sizeof( xReq.szSpeakName ) );
//				GettheServer().SendMsgToCenterServer( &xReq );
//			}
//
//			return;
//		}
//		//luo.qin 4.20 end
//    }
//}

void GamePlayer::OnMsgMountBreed( Msg* pMsg )
{
    MsgMountBreed* pMountBreed = static_cast< MsgMountBreed* >( pMsg );
    if ( pMountBreed == NULL )
    { return; }

    _mountManager.MountBreed( pMountBreed->masterGuid, pMountBreed->assistantGuid );
}

void GamePlayer::OnMsgSetOfflineHook( Msg* pMsg )
{
    MsgSetOfflineHook* pSetOfflineHook = static_cast< MsgSetOfflineHook* >( pMsg );
    if ( pSetOfflineHook == NULL )
    { return; }

    gCharInfoServer.extendData.isOfflineHook = pSetOfflineHook->bSetOfflineHook  ; 

    // 通知客户端离线
    MsgAckOfflineHook msg;
    msg.header.stID     = this->GetID();
    msg.bIsOfflineHook  = gCharInfoServer.extendData.isOfflineHook;
    GettheServer().SendMsgToSingle( &msg, this);
}

void GamePlayer::OnMsgGetOfflineHookExp( Msg* pMsg )
{
    MsgGetOfflineHookExp* pGetOfflineHookExp = static_cast< MsgGetOfflineHookExp* >( pMsg );
    if ( pGetOfflineHookExp == NULL )
    { return; }

    //if (pGetOfflineHookExp->nHookLevel >= EHookLevel_MaxSize)
    //{
    //    MsgAckResult msg;
    //    msg.result = ER_HookLevelNotHas;
    //    GettheServer().SendMsgToSingle( &msg, this );
    //    return;
    //}
    
    int totalMin = (int) ceil( (double)gCharInfoServer.extendData.totalHookTime / ONE_MIN ) ;
    int totalMoney = totalMin * g_Cfg.minuteOfflineHookMoney;
    
    if ( totalMoney > GetJiaoZiMoney() )
    {
        MsgAckResult msg;
        msg.result = ER_NoMoneyGetHookExp;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    int minExp   = GetOfflineHookMinuteExp( pGetOfflineHookExp->nHookLevel );
    int totalExp = totalMin * minExp;

    IncreaseExp( totalExp, 0 );
}

void GamePlayer::OnMsgReqDoubleExp ( Msg* pMsg )
{
    MsgReqDoubleExp* pReqDoubleExp = static_cast< MsgReqDoubleExp* >( pMsg );
    if ( pReqDoubleExp == NULL )
    { return; }

    m_bIsOpenDoubleExp = pReqDoubleExp->bState;

    if ( m_bIsOpenDoubleExp )
    { 
        if ( ApplyBufferStatus( ItemDefine::ESSI_DoubleExpStatus, 1, GetID(), SCharBuff::StatusEventType_Other, 0 ) != GLR_Success )
        { 
            m_bIsOpenDoubleExp = false;
            return; 
        }

        OnBuffStatusChanged( true );
        m_restoretime.dwLastDoubleExpTime = HQ_TimeGetTime();
    }
    else
    {
        if ( !_buffManager.ClearBuffByBuffId( ItemDefine::ESSI_DoubleExpStatus ) )
        {
            m_bIsOpenDoubleExp = true;
            return; 
        }

        OnBuffStatusChanged( true );
        m_restoretime.dwLastDoubleExpTime = 0 ;
    }

    MsgDoubleExpAck msgack;
    msgack.bState = m_bIsOpenDoubleExp;
    msgack.nSysDoubleExpTime  = gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime;
    msgack.nItemDoubleExpTime = gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime;

    GettheServer().SendMsgToSingle( &msgack , this );
}

void GamePlayer::OnUnEquip( Msg* pMsg )
{       
    MsgUnEquip* pUnEquip = (MsgUnEquip*)pMsg;

    UnEquip( pUnEquip->ustWhere, pUnEquip->stPackIndex  );
}

void GamePlayer::OnCreateChar( Msg* pMsg ) // 创建角色
{
    MsgCreateHeroChar* pCreateChar = (MsgCreateHeroChar*)pMsg;

    HelperFunc::LimitStringEight( pCreateChar->create.szCharacterName, MAX_NAME_CREATE );
    if (!CChatCheck::getInstance()->CheckStringInLow( pCreateChar->create.szCharacterName ))
    { 
		//lyh添加，如果名字里面有屏蔽字符，则给用户提示角色创建失败
		MsgAckCreateChar msgAckCreateChar;
		msgAckCreateChar.header.stID = GetID();
		msgAckCreateChar.bCreateSucc = false;
			msgAckCreateChar.stWhichSlot = 0;
		GettheServer().SendMsgToSingle( &msgAckCreateChar, this );
		return; 
	}



    if (!CheckCreateName(pCreateChar->create.szCharacterName))
    { return; }

    DBMsgCreateHeroChar dbCreateChar;
    dbCreateChar.header.stID  = GetID();
    dbCreateChar.accoundId    = m_dbinfo.dwAccountID;
    dbCreateChar.stWhichSlot  = pCreateChar->stWhichSlot;
    dbCreateChar.charinfo.visual.fModelPercent = pCreateChar->fModelPercent;  // 模型大小
    if ( dbCreateChar.charinfo.visual.fModelPercent > g_Cfg.m_fMaxModelPercent ) // 纠正大小
    { dbCreateChar.charinfo.visual.fModelPercent = g_Cfg.m_fMaxModelPercent; }

    if ( dbCreateChar.charinfo.visual.fModelPercent < g_Cfg.m_fMinModelPercent )
    { dbCreateChar.charinfo.visual.fModelPercent = g_Cfg.m_fMinModelPercent; }

    MsgCreateHeroChar::SCreateData* pCreate = &pCreateChar->create;

    switch( pCreate->ucSex )
    { // 性别
    case Sex_Male:
    case Sex_Female:
        break;
    default:
        pCreate->ucSex = Sex_Male;
    }

    // 兵种
    if( pCreate->usProfession >= EArmType_MaxSize)
    { return; }

    SLevelAttribute* pLevelAttribute = theCharacterAttributeConfig.GetCharacterAttribute( pCreate->usProfession, 1 );
    if ( NULL == pLevelAttribute )
    {
        //Log( "创建角色失败\t%s\t%d", pCreateChar->create.szCharacterName, pCreate->usProfession );
		Log(theXmlString.GetString(eServerLog_CreateRoleNoOk), pCreateChar->create.szCharacterName, pCreate->usProfession );
        return;
    }

    SetProfession( pCreate->usProfession ); 

    HelperFunc::SafeNCpy( dbCreateChar.charinfo.baseinfo.aptotic.szCharacterName,pCreate->szCharacterName, sizeof(dbCreateChar.charinfo.baseinfo.aptotic.szCharacterName) );
    
    HelperFunc::SafeNCpy( dbCreateChar.charinfo.baseinfo.aptotic.szYearName, GetGameWorldTimer()->GetYearName(), dr_MaxYearName );
    dbCreateChar.charinfo.baseinfo.aptotic.byYear  = 0;
    dbCreateChar.charinfo.baseinfo.aptotic.byMonth = pCreate->byMonth;
    dbCreateChar.charinfo.baseinfo.aptotic.byDay   = pCreate->byDay;

    dbCreateChar.charinfo.otherdata.bNewChar                  = true;
	dbCreateChar.charinfo.otherdata.PetDuration			      = g_Cfg.InitPetDuration;
    dbCreateChar.charinfo.baseinfo.liveinfo.nHp               = 100 ;
    dbCreateChar.charinfo.baseinfo.liveinfo.nMp               = 1   ;
    dbCreateChar.charinfo.baseinfo.liveinfo.ustLevel          = 1;
    dbCreateChar.charinfo.baseinfo.liveinfo.dwExp             = 0;
    dbCreateChar.charinfo.baseinfo.liveinfo.dwExpNotUsed      = 0;

    dbCreateChar.charinfo.baseinfo.liveinfo.ucNormalBagSize   = g_Cfg.m_nCreatBagSize;
    dbCreateChar.charinfo.baseinfo.liveinfo.ucMaterialBagSize = g_Cfg.m_nCreateMaterialSize;
    dbCreateChar.charinfo.baseinfo.liveinfo.ucMountCount      = ITEM_MOUNT_MAXCOUNT;
    dbCreateChar.charinfo.baseinfo.liveinfo.nStorageItemGrid  = g_Cfg.m_nStorageItemGrid;
    dbCreateChar.charinfo.baseinfo.liveinfo.nStorageMountGrid = g_Cfg.m_nStorageMountGrid;
	dbCreateChar.charinfo.baseinfo.liveinfo.hero_id			  = INVALID_HERO_ID;
	dbCreateChar.charinfo.baseinfo.liveinfo.TPHJRank		  = 0;

	//取消创建的时候分配国家  by:vvx 2012.9.11
    // 如果没有选择国家, 服务器按规则分配一个国家
    //if ( pCreate->ucCountry == CountryDefine::Country_Init || pCreate->ucCountry >= CountryDefine::Country_Max )
    //{ pCreate->ucCountry = theRunTimeData.CalcRandCreateCountryID(); }    
    //dbCreateChar.charinfo.baseinfo.aptotic.ucCountry = CountryDefine::Country_Init;
	
	/*
	 *	Author 2012-9-17 zhuxincong
	 *	DESC: 多增加了判断，因为有现象表明会出现不是0的国家
	 */
	if (pCreate->ucCountry == CountryDefine::Country_Init || pCreate->ucCountry >= CountryDefine::Country_Max)
	{
		//赋值两次 是为了保险
		pCreate->ucCountry = CountryDefine::Country_Init;
		dbCreateChar.charinfo.baseinfo.aptotic.ucCountry = CountryDefine::Country_Init;
	}
    // 根据国家获得出生点地图,
    //const CountryConfig::BornMapSetting* pSetting = theCountryConfig.GetBornMapSetting( pCreate->ucCountry );
    const CountryConfig::BornMapSetting* pSetting = theGameWorld.GetPlayerBornMap( pCreate->ucCountry );
    if ( pSetting == NULL )
    { return; }

    // 坐标
    dbCreateChar.charinfo.otherdata.sBornPos.dwMapID = pSetting->GetMapID();
    dbCreateChar.charinfo.otherdata.sBornPos.stX     = FloatToTile( pSetting->GetPosX() );
    dbCreateChar.charinfo.otherdata.sBornPos.stY     = FloatToTile( pSetting->GetPosY() );
    dbCreateChar.charinfo.otherdata.sBornPos.vPos.x  = pSetting->GetPosX();
    dbCreateChar.charinfo.otherdata.sBornPos.vPos.y  = pSetting->GetPosY();
    dbCreateChar.charinfo.otherdata.pos.dwMapID      = pSetting->GetMapID();
    dbCreateChar.charinfo.otherdata.pos.stX          = FloatToTile( pSetting->GetPosX() );
    dbCreateChar.charinfo.otherdata.pos.stY          = FloatToTile( pSetting->GetPosY() );    
    dbCreateChar.charinfo.otherdata.pos.vPos.x       = pSetting->GetPosX();
    dbCreateChar.charinfo.otherdata.pos.vPos.y       = pSetting->GetPosY();

    // 朝向
    dbCreateChar.charinfo.otherdata.fDirX = pSetting->GetDirX();
    dbCreateChar.charinfo.otherdata.fDirY = pSetting->GetDirY();
    
    // 角色
    dbCreateChar.charinfo.baseinfo.aptotic.ucSex        = pCreate->ucSex;
    dbCreateChar.charinfo.baseinfo.aptotic.ucHeadPic    = pCreate->ucHeadPic;
    dbCreateChar.charinfo.baseinfo.aptotic.usProfession = pCreate->usProfession;

    CAvatarSystemSetting* pAvatarSetting = GetAvatarSystemSetting();
    if ( pAvatarSetting == NULL )
    { return; }

    CAvatarSystemSetting::SDefSetting* pVisualSetting = NULL;
    SCharItem* pEquip = NULL;

    // 头发颜色
    if( Sex_Male == pCreate->ucSex )
    { pVisualSetting = pAvatarSetting->GetSettingMaleHairId(); }
    else
    { pVisualSetting = pAvatarSetting->GetSettingFemaleHairId(); }

    if( pCreate->ucHairModelIndex >= pVisualSetting->nCount )
    { pCreate->ucHairModelIndex = 0; }

    if ( pVisualSetting )
    { dbCreateChar.charinfo.visual.hairId = pVisualSetting->SItems[ pCreate->ucHairModelIndex ].stItem; }

    // 脸部直接使用模型编号
    pVisualSetting = NULL;
    if( Sex_Male == pCreate->ucSex )
    { pVisualSetting = pAvatarSetting->GetSettingMaleFaceId(); }
    else
    { pVisualSetting = pAvatarSetting->GetSettingFemaleFaceId(); }

    if ( pVisualSetting )
    { 
        if( pCreate->ucFaceIndex >= pVisualSetting->nCount )
        { pCreate->ucFaceIndex = 0; }
        dbCreateChar.charinfo.visual.faceId = pVisualSetting->SItems[ pCreate->ucFaceIndex ].stItem; 
    }

    // 默认显示头盔
    dbCreateChar.charinfo.visual.ShowHelmet( true );

    // 身体
    pVisualSetting = NULL;
    if( Sex_Male == pCreate->ucSex )
    { pVisualSetting = pAvatarSetting->GetSettingMaleDressId(); }
    else
    { pVisualSetting = pAvatarSetting->GetSettingFemaleDressId(); }

    if ( pVisualSetting )
    { 
        //if( pCreate->ucModelIndex >= pVisualSetting->nCount )
        //{ pCreate->ucModelIndex = 0; }
		//dbCreateChar.charinfo.visual.defaultModelID = pVisualSetting->SItems[ pCreate->ucModelIndex ].stItem;
		dbCreateChar.charinfo.visual.defaultModelIndex = pCreate->ucModelIndex;
    }

    //////////////////////////////////////////////////////////////////////////
    //  赠送道具
    //////////////////////////////////////////////////////////////////////////
    const uint16* rewardProfessionItems = theRewardProfessionItemConfig.GetRewardProfessionItemList(pCreate->usProfession);

	// 根据职业获得默认武器
    SCharItem charItem;
    theRunTimeData.CreateItem(rewardProfessionItems[0],1,HelperFunc::CreateID(), charItem);
    dbCreateChar.charinfo.visual.equipitem[EEquipPartType_Weapon] = charItem;   //装配主武器

    int nPackIndex = 0;
    for (int i = 1;i < RewardProfessionItemConfig::EConstDefine_RewardItemMaxSize; ++i )
    {
        if ( InvalidLogicNumber == rewardProfessionItems[i])
        { break; }

        SCharItem& charPackItem = dbCreateChar.charinfo.itemData.stPackItems[nPackIndex];
        theRunTimeData.CreateItem(rewardProfessionItems[i],1,HelperFunc::CreateID(), charPackItem);
        ++nPackIndex;
    }

    dbCreateChar.charinfo.baseinfo.liveinfo.xMasterData.SetMasterLevel( 1 );
    dbCreateChar.withFlag |= DBMsgCreateHeroChar::EF_WithNormalBag;

    GettheDBCon().SendMsg( &dbCreateChar,GetLifeCode() );

    //Log( "创建角色\t%s\t%d", pCreateChar->create.szCharacterName, pCreate->usProfession );
	Log( theXmlString.GetString(eServerLog_CreateRole), pCreateChar->create.szCharacterName, pCreate->usProfession );
}

void GamePlayer::OnDeleteChar( Msg *pMsg )
{  // 如果玩家从属于某个公会
    MsgDeleteChar* pMsgDel = (MsgDeleteChar*)pMsg;
    if( pMsgDel->stWhichSlot < 0)
    { return; }

    DBMsgDeleteChar2 msgDBMsgDel;
    msgDBMsgDel.header.stID = GetID();
    msgDBMsgDel.dwAccountID = m_dbinfo.dwAccountID;
    msgDBMsgDel.stWhichSlot = pMsgDel->stWhichSlot;
	vector<uint32>::iterator Iter = m_dbinfo.pdwSlot.begin();
	int i = 0;
	bool IsEx = false;
	for(;Iter !=  m_dbinfo.pdwSlot.end();++Iter)
	{
		if(*Iter == pMsgDel->stWhichSlot)
		{
			msgDBMsgDel.dwCharId    = m_dbinfo.pdwCharacterID[i];
			IsEx = true;
			break;
		}
		++i;
	}
	if(!IsEx)
		return;
    //msgDBMsgDel.dwCharId    = m_dbinfo.pdwCharacterID[pMsgDel->stWhichSlot];
    GettheDBCon().SendMsg( &msgDBMsgDel,GetLifeCode() );
}

void GamePlayer::OnCancelDelChar( Msg* pMsg )
{
    MsgCancelDelChar* pCancel = (MsgCancelDelChar*)pMsg;
    if( pCancel->stWhichSlot < 0)
    { return; }

    DBMsgCancelDelChar DBCancelDel;
    DBCancelDel.header.stID = GetID();
    DBCancelDel.dwAccountID = m_dbinfo.dwAccountID;
    DBCancelDel.stWhichSlot = pCancel->stWhichSlot;

	bool IsEx = false;
	vector<uint32>::iterator Iter = m_dbinfo.pdwSlot.begin();
	int i = 0;
	for(;Iter !=  m_dbinfo.pdwSlot.end();++Iter)
	{
		if(*Iter == pCancel->stWhichSlot)
		{
			DBCancelDel.dwCharId     = m_dbinfo.pdwCharacterID[i];
			IsEx = true;
			break;
		}
		++i;
	}
	if(!IsEx)
		return;
    //DBCancelDel.dwCharId    = m_dbinfo.pdwCharacterID[pCancel->stWhichSlot];
    GettheDBCon().SendMsg( &DBCancelDel,GetLifeCode() );
}

void GamePlayer::OnReqUpAttrLevel(Msg* pMsg) //请求升级基本属性
{       
    // ToCheck
    //    MsgReqUpAttrLevel *pUp = (MsgReqUpAttrLevel *)pMsg;
    //    MsgAckUpAttrLevel ack;    
    //
    //    if( AttrUp_CharBaseAttr == pUp->attrup.cType )
    //    {
    //        if( UpBaseAttrLevel( pUp->attrup.stWhichAttr ) )
    //            goto ret_succ;
    //    }
    //    return;
    //ret_succ:
    //    ack.header.stID = GetControl()->GetID();
    //    ack.attrup = pUp->attrup;
    //    GettheServer().SendMsgToSingle( &ack, this );
}

void GamePlayer::OnMsgReqAchieveData( Msg* pMsg )
{
    MsgReqAchieveData* pMsgReqAchieveData = static_cast< MsgReqAchieveData* >( pMsg );
    if ( pMsgReqAchieveData == NULL )
    { return; }

    MsgAllAchieveData msg;
    msg.achieveData = gCharInfoServer.achieveData;
    GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnMsgReqAchieveReward( Msg* pMsg )
{
    MsgReqAchieveReward* pMsgReqAchieveReward = static_cast< MsgReqAchieveReward* >( pMsg );
    if ( pMsgReqAchieveReward == NULL )
    { return; }

    uint16 nIndex = pMsgReqAchieveReward->nIndex;

    AchieveConfig::Achieve* pAchieve = theAchieveConfig.GetAchieve(nIndex);
    if (pAchieve == NULL)
    { return; }

    if ( nIndex >= MAX_ACHIVEVMENT_COUNT )
    { return; }

    SCharAchieve* pCharAchieve = &gCharInfoServer.achieveData.xAchievements[nIndex];
    if (pCharAchieve == NULL)
    { return; }

    if (pCharAchieve->finishState != ECS_Finished)
    { return; }

    if (pAchieve->GetRewardItem() != InvalidLogicNumber)
    {
        if (AddItem( pAchieve->GetRewardItem(), NUMERIC_ONE, EIGS_Achieve ) != ierr_Success)
        { return; }

        Log("AchieveReward AddItem %u ", pAchieve->GetRewardItem());

        AddAchievePoint( pAchieve->GetRewardPoint() );
    }
    else
    {
        AddAchievePoint( pAchieve->GetRewardPoint() );
    }

    pCharAchieve->finishState = ECS_GetReward;

    MsgReqAchieveRewardAck msg;
    msg.nIndex = nIndex;
    msg.nAchievePoint = GetAchievePoint();
    msg.xCharAchieve = *pCharAchieve;
    GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnMsgReqOffNpcShip( Msg* pMsg )
{
    if ( m_nBigShipId == InvalidGameObjectId )
    { return; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nBigShipId );
    if ( pChar == NULL || pChar->GetObjType() != Object_NpcShip)
    {
        OffNpcShip();
        return;
    }

    NpcShipEx* pNpcShip = (NpcShipEx*)pChar;
    pNpcShip->OffShip( GetID() );

    OffNpcShip();
}

void GamePlayer::OnMsgOfflineFightOp( Msg* pMsg )
{
    MsgOfflineFightOpReq* pMessage = static_cast< MsgOfflineFightOpReq* >( pMsg );
    if ( pMessage == NULL )
    { return; }

    switch ( pMessage->op )
    {
    case EOfflineFightOP_Begin:
        {
            MsgOfflineFightOpAck msg;
            msg.op = pMessage->op;
            if ( !IsCanVigorOfflineFight() )
            {
                msg.result = ER_VigorNotEnoughBeginOfflineFight;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            _offlineFightTime.StartTimer( HQ_TimeGetTime(), 1000 * 60 );

            msg.result = ER_Success;
            GettheServer().SendMsgToSingle( &msg, this );
        }
        break;
    case EOfflineFightOP_End:
        {
            _offlineFightTime.StopTimer();

            MsgOfflineFightOpAck msg;
            msg.op = pMessage->op;
            msg.result = ER_Success;
            GettheServer().SendMsgToSingle( &msg, this );
        }
        break;
    }
}

void GamePlayer::OnMsgReqGotOnDrome     ( Msg* pMsg )
{
    MsgReqGotOnDrome* pMsgReqGotOnDrome = static_cast< MsgReqGotOnDrome* >( pMsg );

    BaseCharacter* pCharDriver = theRunTimeData.GetCharacterByID( pMsgReqGotOnDrome->driverId );
    BaseCharacter* pCharRider = theRunTimeData.GetCharacterByID( pMsgReqGotOnDrome->riderId );

    if (pCharDriver == NULL || pCharRider == NULL || !pCharDriver->IsPlayer() || !pCharRider->IsPlayer())
    { return; }

    if (pCharDriver->GetID() == GetID())
    {
        if ( !IsInMapArea( pCharRider->GetMapID(), pCharRider->GetFloatX(), pCharRider->GetFloatY(),    TARGET_VIEW_DIS ) )
        {
            SendErrorToClient(ER_TargetNotInRange);
            return; 
        }
    }
    else
    {
        if ( !IsInMapArea( pCharDriver->GetMapID(), pCharDriver->GetFloatX(), pCharDriver->GetFloatY(), TARGET_VIEW_DIS ) )
        { 
            SendErrorToClient(ER_TargetNotInRange);
            return; 
        }
    }
    
    if (pMsgReqGotOnDrome->type == MsgReqGotOnDrome::EOperateType_Request)
    { 
        GamePlayer* pDriver = static_cast< GamePlayer* >( pCharDriver );
        GamePlayer* pRider  = static_cast< GamePlayer* >( pCharRider );

        if (pRider->GetTeamID() == InvalidLogicNumber || pRider->GetTeamID() != pDriver->GetTeamID())
        {
            SendErrorToClient(ER_NoTeamMultiMount);
            return; 
        }
        
        GettheServer().SendMsgToSingle( pMsgReqGotOnDrome, pCharDriver ); 
    }
    else
    { GettheServer().SendMsgToSingle( pMsgReqGotOnDrome, pCharRider );  }
}

void GamePlayer::OnMsgReqGotOnDromeAck  ( Msg* pMsg )
{
    MsgReqGotOnDromeAck* pMsgAck = static_cast< MsgReqGotOnDromeAck* >( pMsg );

    BaseCharacter* pCharDriver = theRunTimeData.GetCharacterByID( pMsgAck->driverId );
    BaseCharacter* pCharRider = theRunTimeData.GetCharacterByID( pMsgAck->riderId );

    if (pCharDriver == NULL || pCharRider == NULL || !pCharDriver->IsPlayer() || !pCharRider->IsPlayer())
    { return; }

    if (pCharDriver->GetID() == GetID())
    {
        if ( !IsInMapArea( pCharRider->GetMapID(), pCharRider->GetFloatX(), pCharRider->GetFloatY(),    TARGET_VIEW_DIS ) )
        {
            SendErrorToClient(ER_TargetNotInRange);
            return; 
        }
    }
    else
    {
        if ( !IsInMapArea( pCharDriver->GetMapID(), pCharDriver->GetFloatX(), pCharDriver->GetFloatY(), TARGET_VIEW_DIS ) )
        { 
            SendErrorToClient(ER_TargetNotInRange);
            return; 
        }
    }

    if (pMsgAck->type == MsgReqGotOnDromeAck::EOperateType_Reject)
    {
        if (pCharDriver->GetID() == GetID())
        { GettheServer().SendMsgToSingle( pMsgAck, pCharRider ); }
        else
        { GettheServer().SendMsgToSingle( pMsgAck, pCharDriver ); }
    }
    else
    {
        GamePlayer* pDriver = static_cast< GamePlayer* >( pCharDriver );
        GamePlayer* pRider  = static_cast< GamePlayer* >( pCharRider );

        if ( pRider->_mountManager.IsRideMultiMount() )
        {
            SendErrorToClient( ER_HasRideMultiMount );
            return; 
        }

        if ( !pDriver->_mountManager.IsDriveMultiMount() )
        { 
            SendErrorToClient( ER_NoRideMultiMount );
            return; 
        }

        int nResult = pDriver->_mountManager.GotOnMultiMount( pRider->GetID() );
        if (nResult != ER_Success)
        { 
            SendErrorToClient( ER_MultiMountIsFull );
            return; 
        }

        MsgGotOnOffDrome msg;
        msg.type = MsgGotOnOffDrome::EOnOffType_On;
        msg.driverId = pDriver->GetID();
        msg.riderId  = pRider->GetID();
        msg.pos      = pRider->GetRidePos();
        GettheServer().SendMsgToView( &msg, pRider->GetID() );
    }
}

//踢人下坐骑
void GamePlayer::OnMsgRiderOffDrome(Msg* pMsg)
{

	MsgRiderOffDrome* pMsgRiderOffDrome = static_cast< MsgRiderOffDrome* >( pMsg );
	BaseCharacter* pCharDriver = theRunTimeData.GetCharacterByID( pMsgRiderOffDrome->driverId );
	BaseCharacter* pCharRider  = theRunTimeData.GetCharacterByID( pMsgRiderOffDrome->riderId );

	if (pCharDriver == NULL || pCharRider == NULL || !pCharDriver->IsPlayer() || !pCharRider->IsPlayer())
	{ return; }

	GamePlayer* pDriver = static_cast< GamePlayer* >( pCharDriver );
	GamePlayer* pRider  = static_cast< GamePlayer* >( pCharRider );

	MsgGotOnOffDrome msg;
	msg.type = MsgGotOnOffDrome::EOnOffType_Off;
	msg.driverId = pDriver->GetID();
	msg.riderId  = pRider->GetID();
	msg.pos      = pRider->GetRidePos();

	int nResult = pDriver->_mountManager.GotOffMultiMount( pRider->GetID() );
	if (nResult != ER_Success)
	{ 
		SendErrorToClient( ER_GotOffMultiMount );
		return; 
	}

	GettheServer().SendMsgToView( &msg, pRider->GetID() );

}

void GamePlayer::OnMsgReqGotOffDrome     ( Msg* pMsg )
{
    MsgReqGotOffDrome* pMsgReqGotOffDrome = static_cast< MsgReqGotOffDrome* >( pMsg );

    BaseCharacter* pCharDriver = theRunTimeData.GetCharacterByID( pMsgReqGotOffDrome->driverId );
    BaseCharacter* pCharRider  = theRunTimeData.GetCharacterByID( pMsgReqGotOffDrome->riderId );

    if (pCharDriver == NULL || pCharRider == NULL || !pCharDriver->IsPlayer() || !pCharRider->IsPlayer())
    { return; }

    if (pCharDriver->GetID() == GetID())
    {
        DoRide(-1);
    }
    else
    {
        GamePlayer* pDriver = static_cast< GamePlayer* >( pCharDriver );
        GamePlayer* pRider  = static_cast< GamePlayer* >( pCharRider );
        
        MsgGotOnOffDrome msg;
        msg.type = MsgGotOnOffDrome::EOnOffType_Off;
        msg.driverId = pDriver->GetID();
        msg.riderId  = pRider->GetID();
        msg.pos      = pRider->GetRidePos();

        int nResult = pDriver->_mountManager.GotOffMultiMount( pRider->GetID() );
        if (nResult != ER_Success)
        { 
            SendErrorToClient( ER_GotOffMultiMount );
            return; 
        }

        GettheServer().SendMsgToView( &msg, pRider->GetID() );
    }
}

void GamePlayer::OnMsgReqDoneQuest     ( Msg* pMsg )
{
    MsgReqDoneQuest* pMsgReqDoneQuest = static_cast< MsgReqDoneQuest* >( pMsg );

    // 脚本等行中,暂时不接收脚本请求
    if ( m_dwScriptSleep != 0 )
    { 
        CancelAllScript();
        return;
    }

    // 交易中不可与NPC对话
    if ( HaveBargaining() )
    { 
        CancelAllScript();
        return;
    }

    uint32 result = _actionManager.Action( pMsgReqDoneQuest->GetType() );
    if ( RESULT_FAILED( result ) )
    { 
        CancelAllScript();
        return;
    }

    if ( pMsgReqDoneQuest->stNpcId >= 0 )
    {
        NpcBaseEx* pNpcChar = (NpcBaseEx*)theRunTimeData.GetCharacterByID( pMsgReqDoneQuest->stNpcId );
        if( pNpcChar == NULL || !pNpcChar->IsNpc() || ( pNpcChar->GetCountry() != CountryDefine::Country_Init && pNpcChar->GetCountry() != GetCountry() ) 
            || !pNpcChar->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), 10.f ) )
        {
            MsgAckResult msg;
            msg.result = ER_CallNpcScriptFailDistance;
            GettheServer().SendMsgToSingle( &msg, this );

            CancelAllScript();
            return;
        }
    }

    int nQuestId = pMsgReqDoneQuest->nQuestId;

    SQuest* pQuest = theQuestManager.GetQuest( nQuestId );
    if( pQuest == NULL )
    { 
        CancelAllScript();
        return;
    }

    if( !IsQuestActive( pQuest->Id ) )
    {// 如果任务不是出于活动状态
        CancelAllScript();
        return;
    }

    if ( !pQuest->IsSingleRequirement )
    {// 如果不是单个条件任务
        CancelAllScript();
        return;
    }

    bool bIsDoneQuest       = false;
    bool bBreakRequirement  = false;
    int  nRewardID          = 0;
    int  nQuestResult       = ER_NoFoundQuestItem;

    SQuest::RequirementTypeItr itr = pQuest->stCommitRequirement.begin();
    for( ; itr != pQuest->stCommitRequirement.end(); ++itr )
    {
        switch ( itr->byType )
        {
        case SQuest::eRequirement_Item:
            {
                for (int i=0;i<MsgReqDoneQuest::EDoneQuest_CommitItemMax;++i)
                {
                    if (pMsgReqDoneQuest->nGuid[i] == 0)
                    { continue; }

                    SCharItem* pItem = GetBagItemByGuid( pMsgReqDoneQuest->nGuid[i] );
                    if (pItem == NULL || pItem->GetItemID() != itr->Value )
                    { continue; }

                    if ( !RemoveBagItemByGuid( pMsgReqDoneQuest->nGuid[i], itr->MaxNum ) )
                    {
                        bBreakRequirement = true;
                        nQuestResult = ER_QuestItemCommit;
                        break;
                    }

                    if (pQuest->IsSingleRequirement)
                    {
                        nRewardID = itr->nRewardID;
                        bIsDoneQuest = true;
                        bBreakRequirement = true;
                        break;
                    }

                }
            }
            break;
        default:
            break;
        }

        if ( bBreakRequirement )
        { break; }
    }
    
    if ( !bIsDoneQuest )
    { 
        MsgAckResult msg;
        msg.result = nQuestResult;
        GettheServer().SendMsgToSingle( &msg, this );

        CancelAllScript();
        return;
    }

    if (pQuest->IsSingleRequirement)
    { DoneSingleRequirementQuest( pQuest->Id, nRewardID ); }

    SScript* pScript = GetScript();
    if ( pScript != NULL )
    {
        pScript->nVar = pMsgReqDoneQuest->chSelItem;
        if ( pMsgReqDoneQuest->stNpcId >= 0 )
        { // 继续执行脚本 npc 挂起脚本
            GetScriptMgr()->ExecuteVM( ST_NPC, pMsgReqDoneQuest->stNpcId, this );
        }
        else
        { // 继续执行脚本 其他 挂起脚本
            GetScriptMgr()->ExecuteVM( ST_UNKNOW, -1, this );
        }
    }
    else
    { // 无脚本的时候
        if ( pMsgReqDoneQuest->stNpcId >= 0 )
        {
            GetScriptMgr()->StartupVM( ST_NPC, pMsgReqDoneQuest->stNpcId, this, false, 1, pMsgReqDoneQuest->stNpcId );
        }
        else
        { }
    }    
}

void GamePlayer::OnMsgChangePetName( Msg* pMsg )
{   
    MsgChangePetName* pChange = static_cast< MsgChangePetName* >( pMsg );

    HelperFunc::CheckStringValid( pChange->szName, sizeof( pChange->szName ) );

    SPetItem* pPet = _petManager.GetPetByIndex( pChange->index );
    if ( pPet == NULL)
    { return; }

	//判断消耗的材料
	int sum = GetItemCount(SID_SuAnimalChangeName);
	if(sum <1)
		return;

	if(!RemoveItem(SID_SuAnimalChangeName,1))
		return;

    strncpy_s( pPet->baseInfo.szName, sizeof(pPet->baseInfo.szName), pChange->szName, sizeof(pPet->baseInfo.szName)-1);

    if ( pChange->index == _petManager.GetActivePetIndex() )
    {
        MsgAckDisplayName msg;
        msg.header.stID = _petManager.GetActivePetCharId();
        strncpy_s( msg.szDisplayName, sizeof(msg.szDisplayName), pPet->baseInfo.szName, sizeof(msg.szDisplayName)-1);
        GettheServer().SendMsgToView( &msg, GetID() );

        MonsterNurturePet* pNurturePet = (MonsterNurturePet*)_petManager.GetMonsterNurturePet();
        if ( pNurturePet != NULL )
        { pNurturePet->UpdatePetData(); }
    }
}

//分配宠物潜力点
void GamePlayer::OnMsgPetPotential( Msg* pMsg )
{
    MsgPetPotential* pPotential = static_cast< MsgPetPotential* >( pMsg );

    SPetItem* pPet = _petManager.GetPetByIndex( pPotential->index );
    if ( pPet == NULL || pPet->GetPetGuid() != pPotential->guid )
    {
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    int nPotential = 0;
    for (int i=0;i<EBaseAttr_MaxSize;i++)
    {
        if ( pPotential->value[i] < 0 )
        { return; }

        nPotential += pPotential->value[i];
    }

    if (pPet->baseInfo.nPotentialPoint < nPotential)
    {
        MsgAckResult msg;
        msg.result = ER_PetPotential;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    for (int i=0;i<EBaseAttr_MaxSize;i++)
    {
        pPet->baseInfo.potentialAttribute[i] += pPotential->value[i];
        pPet->baseInfo.nPotentialPoint -= pPotential->value[i];
    }

    // 重新计算属性
    //_petManager.UpdatePetAttribute      ( *pPet );

	// 重新计算玩家的战斗力
	_petManager.CalcBattleEffectiveness ( *pPet );

    // 被动技能影响
    //_petManager.ApplyPassiveSkillToPet  ( pPet );

    if ( pPotential->index == _petManager.GetActivePetIndex() )
    { // 出战宠物更新数据
        MonsterNurturePet* pNurturePet = (MonsterNurturePet*) _petManager.GetMonsterNurturePet();
        if ( pNurturePet != NULL )
        { pNurturePet->UpdatePetData(); }
    }

    MsgAddUpdatePet msg;
    msg.header.stID =  GetID();
    msg.pet  = *pPet;
    msg.type = MsgAddUpdatePet::OT_Update;
    GettheServer().SendMsgToSingle( &msg, this);

    //如果是出战宠物会对人物属性产生作用
    //if (_petManager.GetActivePetIndex() == pPotential->index)
    //{ _petManager.ApplyPetAttrToMonster( false, true ); }

	if(_petManager.GetActivePet() == pPet)
	{
		RefreshLieutenantAttr(true);//当前副将一定处于出战状态
	}
}

// 改变坐骑
void GamePlayer::OnMsgChangePet( Msg* pMsg )
{
    MsgChangePet* pChange = static_cast< MsgChangePet* > ( pMsg );

    MsgChangePet changeAck;
    changeAck.header.stID = GetID();
    changeAck.ucOpType    = pChange->ucOpType;
    changeAck.nIndex      = pChange->nIndex;
    changeAck.guid        = pChange->guid;

    SPetItem* pPet = _petManager.GetPetByIndex( pChange->nIndex );
    if ( pPet == NULL || pPet->baseInfo.guid != pChange->guid )
    {
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    int32 nResult = ER_Success;
    switch ( pChange->ucOpType )
    {
    case MsgChangePet::EOT_Active:
        {
			MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( GetMapID() ) );
			if (!pMapData)
			{
				MsgAckResult msg;
				msg.result = ER_MapNotActivePet;
				GettheServer().SendMsgToSingle( &msg, this );
				return; 
			}
			if (!pMapData->CanPet)
			{
				MsgAckResult msg;
				msg.result = ER_MapNotActivePet;
				GettheServer().SendMsgToSingle( &msg, this );
				return; 
			}

            if ( IsDead() )
            { // 死亡状态不能出战
                MsgAckResult msg;
                msg.result = ER_InDeadNotActivePet;
                GettheServer().SendMsgToSingle( &msg, this );
                return; 
            }

            if ( /*pPet->baseInfo.duration*/GetCharInfo().otherdata.PetDuration == 0 )
            { 
                MsgAckResult msg;
                msg.result = ER_LifeNotActivePet;
                GettheServer().SendMsgToSingle( &msg, this );
                return; 
            }

			//不要副将快乐度  by liaojie  11.21
            /*if ( pPet->baseInfo.loyalty < 60 )
            { 
                MsgAckResult msg;
                msg.result = ER_LoyaltyNotActivePet;
                GettheServer().SendMsgToSingle( &msg, this );
                return; 
            }*/

			//不要重生时间
            /*if ( pPet->baseInfo.regenerateTime > HQ_TimeGetTime() )
            { 
                int nSecond = (pPet->baseInfo.regenerateTime - HQ_TimeGetTime()) / ONE_SEC ;
                MsgAckResult msg;
                msg.result = ER_PetRegenerateTime;
                msg.value  = nSecond ;
                GettheServer().SendMsgToSingle( &msg, this );
                return ; 
            }*/

            //清除当前出战宠物状态
            _petManager.LostActivePetMonster()   ;
            //_petManager.ClearPassiveSkillAffect();

            // 得到当前要出战的马
            int currentIndex = _petManager.GetPetIndexByGuid( pChange->guid );
            if ( currentIndex == -1 )
            { 
                MsgAckResult msg;
                msg.result = ER_NotFoundPet;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            if ( currentIndex != changeAck.nIndex)
            { changeAck.nIndex = currentIndex;}

            nResult = _petManager.ProcessSetPetActive( currentIndex );
            if ( RESULT_FAILED( nResult ) )
            {   
                MsgAckResult msg;
                msg.result = nResult;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }
			
            GettheServer().SendMsgToSingle( &changeAck, this );
        }
        break;
    case MsgChangePet::EOT_UnActive:
        {
            // 得到当前要休息的马
            int currentIndex = _petManager.GetPetIndexByGuid( pChange->guid );
            SPetItem* pPetItem = _petManager.GetPetByGuid( pChange->guid );
            if ( currentIndex == -1 || pPetItem == NULL )
            { 
                MsgAckResult msg;
                msg.result      = ER_NotFoundPet;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            if ( currentIndex != changeAck.nIndex)
            { changeAck.nIndex = currentIndex;}

            bool bActiveIndex = (_petManager.GetActivePetIndex() == currentIndex);
            if ( bActiveIndex )
            {
                //清除当前出战战马状态
                _petManager.LostActivePetMonster();
                //_petManager.ClearPassiveSkillAffect();
                _petManager._activeSkillBag.SaveSkillColdTime();
				//这里判断一下出战的副将有没有给人物增加属性的被动技能，有的话就消除buff
				//{
				//	for (int indexSkill=0; indexSkill<pPetItem->skillInfo.GetCurrentSkillCount(); indexSkill++)
				//	{
				//		ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pPetItem->skillInfo.skills[indexSkill].ustSkillID, pPetItem->skillInfo.skills[indexSkill].stSkillLevel );
				//		if(pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
				//		{
				//			//有资质类的被动技能，消除buff
				//			ApplyPetAttrToChar(pPetSkill,true);
				//		}
				//	}
				//}
            }

            GettheServer().SendMsgToSingle( &changeAck, this );
        }
        break;
    case MsgChangePet::EOT_Disappear:
        {
            if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_FreePet, PasswordDefine::OP_InitAction ) )
            { return;} // 财产保护下无法放生

            bool bActiveIndex = false;
            SPetItem* pPetItem = _petManager.GetPetByGuid( pChange->guid );
            if ( pPetItem == NULL )
            { 
                MsgAckResult msg;
                msg.result      = ER_NotFoundPet;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            int currentIndex = _petManager.GetPetIndexByGuid( pChange->guid );
            if ( currentIndex == -1 )
            { 
                MsgAckResult msg;
                msg.result      = ER_NotFoundPet;
                GettheServer().SendMsgToSingle( &msg, this );
                return;
            }

            if ( currentIndex != changeAck.nIndex)
            { changeAck.nIndex = currentIndex;}

            if ( _petManager.GetActivePetIndex() == currentIndex)
            {
                //清除当前出战状态
                _petManager.LostActivePetMonster();
                //_petManager.ClearPassiveSkillAffect();
            }

            int nResult = _petManager.PopPetByBigId( pChange->guid, bActiveIndex );
            if ( nResult == ER_Success )
            { GettheServer().SendMsgToSingle( &changeAck, this ); }
        }
        break;
	case MsgChangePet::EOT_CallButNoActive:			//召唤
		{
			SPetItem* pPetItem = _petManager.GetPetByGuid( pChange->guid );
			for (int indexSkill=0; indexSkill<pPetItem->skillInfo.GetCurrentSkillCount(); indexSkill++)
			{
				ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pPetItem->skillInfo.skills[indexSkill].ustSkillID, pPetItem->skillInfo.skills[indexSkill].stSkillLevel );
				if(pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
				{
					//有资质类的被动技能，消除buff
					//ApplyPetAttrToChar(pPetSkill,false);
					break;
				}
			}
		}
		break;
	case MsgChangePet::EOT_Recall:
		{
			SPetItem* pPetItem = _petManager.GetPetByGuid( pChange->guid );
			for (int indexSkill=0; indexSkill<pPetItem->skillInfo.GetCurrentSkillCount(); indexSkill++)
			{
				ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pPetItem->skillInfo.skills[indexSkill].ustSkillID, pPetItem->skillInfo.skills[indexSkill].stSkillLevel );
				if(pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
				{
					//有资质类的被动技能，消除buff
					ApplyPetAttrToChar(pPetSkill,true);
					break;
				}
			}
		}
    }
}

void GamePlayer::OnMsgPetSavvyUp ( Msg* pMsg )
{
    MsgPetSavvyUp* pMsgPetSavvyUp = static_cast< MsgPetSavvyUp* > ( pMsg );
    
    int nActiveIndex = _petManager.GetActivePetIndex();
    if (pMsgPetSavvyUp->nSrcPetIndex == nActiveIndex || pMsgPetSavvyUp->nDstPetIndex == nActiveIndex)
    {
        MsgAckResult msg;
        msg.result = ER_IsActivePet;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    SPetItem* pSrcPet = _petManager.GetPetByIndex( pMsgPetSavvyUp->nSrcPetIndex );
    if ( pSrcPet == NULL || pSrcPet->GetPetGuid() != pMsgPetSavvyUp->nSrcPetGuid )
    {
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    SPetItem* pDstPet = _petManager.GetPetByIndex( pMsgPetSavvyUp->nDstPetIndex );
    if ( pDstPet == NULL || pDstPet->GetPetGuid() != pMsgPetSavvyUp->nDstPetGuid )
    {
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    if ( pDstPet->baseInfo.savvy == PetSettingConfig::EPetSavvy_LevelMax )
    {
        MsgAckResult msg;
        msg.result = ER_PetSavvyUp;
        GettheServer().SendMsgToSingle( &msg, this );
        return ;
    }

    if ( pDstPet->baseInfo.petType != pSrcPet->baseInfo.petType )
    { 
        MsgAckResult msg;
        msg.result = ER_PetSavvyUp;
        GettheServer().SendMsgToSingle( &msg, this );
        return ;
    }

    if ( pSrcPet->baseInfo.bone <= pDstPet->baseInfo.savvy )
    {
        MsgAckResult msg;
        msg.result = ER_PetSavvyBone;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( pDstPet->baseInfo.petId );
    if ( pMonsterConfig == NULL ) 
    { 
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle( &msg, this );
        return ; 
    }

    if ( !pMonsterConfig->bIsBaby )
    {
        MsgAckResult msg;
        msg.result = ER_PetSavvyUp;
        GettheServer().SendMsgToSingle( &msg, this );
        return ;
    }

    int nSavvyUpRate  = thePetSettingConfig.GetSavvyUpEatRate  ( pMonsterConfig->catchQuality, pMonsterConfig->catchLevel, pDstPet->baseInfo.savvy );
    int nSavvyUpMoney = thePetSettingConfig.GetSavvyUpEatMoney ( pMonsterConfig->catchQuality, pMonsterConfig->catchLevel, pDstPet->baseInfo.savvy );

    if( nSavvyUpMoney > GetMoney() )
    {
        MsgAckResult msg;
        msg.result = ER_PetSavvyUpMoney;
        GettheServer().SendMsgToSingle( &msg, this );
        return ;
    }

    bool bActive = false;
    _petManager.PopPetByBigId( pMsgPetSavvyUp->nSrcPetGuid, bActive );
    OperateMoney( EOT_Sub, nSavvyUpMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_PetSavvyUp);

    MsgChangePet change;
    change.ucOpType    = MsgChangePet::EOT_Disappear;
    change.nIndex      = pMsgPetSavvyUp->nSrcPetIndex;
    change.guid        = pMsgPetSavvyUp->nSrcPetGuid;
    change.source      = EDS_SavvyUp;
    GettheServer().SendMsgToSingle( &change, this );

    int nResult = MsgPetSavvyUpAck::ER_Failed;
    if ( (theRand.rand16() % RAND_NUM) >= nSavvyUpRate )
    {
        int savvy = thePetSettingConfig.GetReduceSavvy( pDstPet->baseInfo.savvy );
        if ( savvy != 0 )
        { 
            pDstPet->baseInfo.savvy = savvy; 
            SendErrorToClient( ER_PetSavvyReduce, savvy );
        }
        nResult = MsgPetSavvyUpAck::ER_Failed;
    }
    else
    {
        pDstPet->baseInfo.savvy += 1;
        nResult = MsgPetSavvyUpAck::ER_Success;
    }

    //_petManager.UpdatePetAttribute( *pDstPet );
    _petManager.CalcBattleEffectiveness( *pDstPet );
    //_petManager.ApplyPassiveSkillToPet( pDstPet );

    if ( pMsgPetSavvyUp->nDstPetIndex == _petManager.GetActivePetIndex() )
    { // 出战宠物更新数据
        MonsterNurturePet* pNurturePet = (MonsterNurturePet*) _petManager.GetMonsterNurturePet();
        if ( pNurturePet != NULL )
        { pNurturePet->UpdatePetData(); }
    }

    MsgAddUpdatePet msg;
    msg.header.stID = GetID();
    msg.pet = *pDstPet;
    msg.type = MsgAddUpdatePet::OT_Update;
    GettheServer().SendMsgToSingle( &msg, this);
    
    MsgPetSavvyUpAck msgAck;
    msgAck.index  = pMsgPetSavvyUp->nDstPetIndex;
    msgAck.result = nResult;
    GettheServer().SendMsgToSingle( &msgAck, this );
}

void GamePlayer::OnMsgPetBreedReq ( Msg* pMsg )
{
    MsgPetBreedReq* pPetBreedReq = static_cast< MsgPetBreedReq* > ( pMsg );
    
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if( pTeam == NULL )
    {
        MsgPetBreedReqAck msgAck;
        msgAck.result = MsgPetBreedReqAck::ER_NoTeam;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    if ( !pTeam->IsTeamHeader( GetDBCharacterID() ) )
    {
        MsgPetBreedReqAck msgAck;
        msgAck.result = MsgPetBreedReqAck::ER_TeamHeader;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    if ( pTeam->TeamMemberCount() != 2 )
    {
        MsgPetBreedReqAck msgAck;
        msgAck.result = MsgPetBreedReqAck::ER_TeamMember;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

   PetBreedInfo* pPetBreedInfo =  thePetBreedManager.CreatePetBreed( GetTeamID() );
   if ( pPetBreedInfo == NULL )
   {
       MsgPetBreedReqAck msgAck;
       msgAck.result = MsgPetBreedReqAck::ER_Failed;
       GettheServer().SendMsgToSingle( &msgAck, this );
       return; 
   }
    
   // 申请的玩家
   pPetBreedInfo->SetPlayerA( GetDBCharacterID() );
   for ( int i=0;i<pTeam->TeamMemberCount(); ++i )
   {
        if( pTeam->GetMemberIDByIndex( i ) != GetDBCharacterID() )
        {
            pPetBreedInfo->SetPlayerB( pTeam->GetMemberIDByIndex( i ) );
        }
   }

   GamePlayer* PlayerB = theRunTimeData.GetGamePlayerByDBID( pPetBreedInfo->GetPlayerB() );
   if ( PlayerB == NULL )
   {
       MsgPetBreedReqAck msgAck;
       msgAck.result = MsgPetBreedReqAck::ER_Failed;
       GettheServer().SendMsgToSingle( &msgAck, this );
       thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishCancel );
       return; 
   }

   if ( !IsInMapArea( PlayerB->GetMapID(), PlayerB->GetFloatX(), PlayerB->GetFloatY(), fSellBuyToNpcRange ) )
   { 
       MsgPetBreedReqAck msgAck;
       msgAck.result = MsgPetBreedReqAck::ER_TeamRange;
       GettheServer().SendMsgToSingle( &msgAck, this );
       thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishCancel );
       return; 
   }

   if ( _petManager.GetBreedPet() != NULL || PlayerB->_petManager.GetBreedPet() != NULL )
   {
       MsgPetBreedReqAck msgAck;
       msgAck.result = MsgPetBreedReqAck::ER_HaveBreed;
       GettheServer().SendMsgToSingle( &msgAck, this );
       thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishHasBreed );
       return; 
   }

   SetPetBreedID( pPetBreedInfo->GetID() );
   PlayerB->SetPetBreedID( pPetBreedInfo->GetID() );
   
   pPetBreedInfo->SetStatusA( EPetBreed_StatusStart );
   pPetBreedInfo->SetStatusB( EPetBreed_StatusStart );

   // 开启定时器
   pPetBreedInfo->StartTimer( HQ_TimeGetTime(), 15 * OneMinuteMicroSecond );

   // 发送消息给双方
   MsgPetBreedReqAck msgAck;
   msgAck.result = MsgPetBreedReqAck::ER_Success;
   GettheServer().SendMsgToSingle( &msgAck, this );
   GettheServer().SendMsgToSingle( &msgAck, PlayerB );
}

void GamePlayer::OnMsgPetBreedChoice ( Msg* pMsg )
{
    MsgPetBreedChoice* pPetBreedChoice = static_cast< MsgPetBreedChoice* > ( pMsg );

    PetBreedInfo* pPetBreedInfo = thePetBreedManager.GetPetBreed( GetPetBreedID() );
    if ( pPetBreedInfo == NULL )
    {
        MsgPetBreedChoiceAck msgAck;
        msgAck.result = MsgPetBreedChoiceAck::ER_Failed;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    GamePlayer* pPlayerA = theRunTimeData.GetGamePlayerByDBID( pPetBreedInfo->GetPlayerA() );
    GamePlayer* pPlayerB = theRunTimeData.GetGamePlayerByDBID( pPetBreedInfo->GetPlayerB() );
    if ( pPlayerA == NULL || pPlayerB == NULL )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishCancel );
        return;
    }

    int nStatus = EPetBreed_StatusInit;
    if ( pPlayerA->GetDBCharacterID() == GetDBCharacterID() )//判断繁殖的状态由哪位玩家确定
    { nStatus = pPetBreedInfo->GetStatusA(); }
    else
    { nStatus = pPetBreedInfo->GetStatusB(); }

    if ( nStatus == EPetBreed_StatusLock || nStatus == EPetBreed_StatusConfirm )//判断繁殖的状态
    {
        MsgPetBreedChoiceAck msgAck;
        msgAck.result = MsgPetBreedChoiceAck::ER_Failed;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    int nActiveIndex = _petManager.GetActivePetIndex();//获得出战宠物的下标位置
    if ( pPetBreedChoice->index == nActiveIndex )
    {
        MsgAckResult msg;
        msg.result = ER_IsActivePet;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    SPetItem* pPet = _petManager.GetPetByIndex( pPetBreedChoice->index );//根据副将下标获得副将信息
    if ( pPet == NULL )
    {
        MsgPetBreedChoiceAck msgAck;
        msgAck.result = MsgPetBreedChoiceAck::ER_Failed;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    if ( pPet->baseInfo.breedNum >= thePetSettingConfig.GetPetBreedNum( pPet->baseInfo.level ) )
    {
        MsgPetBreedChoiceAck msgAck;
        msgAck.result = MsgPetBreedChoiceAck::ER_Failed;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    if ( GetDBCharacterID() == pPetBreedInfo->GetPlayerA() )//确定是两个玩家谁的副将繁殖，可能
    { pPetBreedInfo->SetPetA( *pPet ); }
    else
    { pPetBreedInfo->SetPetB( *pPet ); }

    // 发送消息给双方
    MsgPetBreedChoiceAck msgAck;
    msgAck.header.stID = GetID();
    msgAck.result = MsgPetBreedChoiceAck::ER_Success;
    msgAck.pet    = *pPet;
    GettheServer().SendMsgToSingle( &msgAck, pPlayerA );
    GettheServer().SendMsgToSingle( &msgAck, pPlayerB );
}

void GamePlayer::OnMsgPetBreedLock ( Msg* pMsg )
{
    MsgPetBreedLock* pPetBreedLock = static_cast< MsgPetBreedLock* > ( pMsg );

    PetBreedInfo* pPetBreedInfo = thePetBreedManager.GetPetBreed( GetPetBreedID() );
    if ( pPetBreedInfo == NULL )
    { return; }

    GamePlayer* pPlayerA = theRunTimeData.GetGamePlayerByDBID( pPetBreedInfo->GetPlayerA() );
    GamePlayer* pPlayerB = theRunTimeData.GetGamePlayerByDBID( pPetBreedInfo->GetPlayerB() );
    if ( pPlayerA == NULL || pPlayerB == NULL )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishCancel );
        return;
    }

    if ( GetDBCharacterID() == pPetBreedInfo->GetPlayerA() )
    { 
        if ( pPetBreedInfo->GetPetA() == NULL )
        {
            MsgPetBreedStatus msgStatus;
            msgStatus.status = pPetBreedInfo->GetStatusA();
            GettheServer().SendMsgToSingle( &msgStatus, pPlayerA );
        }
        else
        {
            pPetBreedInfo->SetStatusA( EPetBreed_StatusLock );
        }
    }
    else
    {
        if ( pPetBreedInfo->GetPetB() == NULL )
        {
            MsgPetBreedStatus msgStatus;
            msgStatus.status = pPetBreedInfo->GetStatusB();
            GettheServer().SendMsgToSingle( &msgStatus, pPlayerB );
        }
        else
        {
            pPetBreedInfo->SetStatusB( EPetBreed_StatusLock );
        }
    }

    // 发送消息给双方
    MsgPetBreedStatus msgStatus;
    msgStatus.header.stID = GetID();
    msgStatus.status = EPetBreed_StatusLock;
    GettheServer().SendMsgToSingle( &msgStatus, pPlayerA );
    GettheServer().SendMsgToSingle( &msgStatus, pPlayerB );
}

void GamePlayer::OnMsgPetBreedCancelLock ( Msg* pMsg )
{
    MsgPetBreedCancelLock* pPetBreedCancelLock = static_cast< MsgPetBreedCancelLock* > ( pMsg );

    PetBreedInfo* pPetBreedInfo = thePetBreedManager.GetPetBreed( GetPetBreedID() );
    if ( pPetBreedInfo == NULL )
    { return; }

    GamePlayer* pPlayerA = theRunTimeData.GetGamePlayerByDBID( pPetBreedInfo->GetPlayerA() );
    GamePlayer* pPlayerB = theRunTimeData.GetGamePlayerByDBID( pPetBreedInfo->GetPlayerB() );
    if ( pPlayerA == NULL || pPlayerB == NULL )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishCancel );
        return;
    }

    pPetBreedInfo->SetStatusA( EPetBreed_StatusStart );
    pPetBreedInfo->SetStatusB( EPetBreed_StatusStart );


    // 发送消息给双方
    MsgPetBreedCancelLock msgCancelLock;
    msgCancelLock.header.stID = GetID();
    GettheServer().SendMsgToSingle( &msgCancelLock, pPlayerA );
    GettheServer().SendMsgToSingle( &msgCancelLock, pPlayerB );
}

void GamePlayer::OnMsgPetBreedCancelReq ( Msg* pMsg )
{
    PetBreedInfo* pPetBreedInfo = thePetBreedManager.GetPetBreed( GetPetBreedID() );
    if ( pPetBreedInfo != NULL )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishCancel );
        return; 
    }
}

void GamePlayer::OnMsgPetBreedConfirm ( Msg* pMsg )
{
    MsgPetBreedConfirm* pPetBreedLock = static_cast< MsgPetBreedConfirm* > ( pMsg );

    PetBreedInfo* pPetBreedInfo = thePetBreedManager.GetPetBreed( GetPetBreedID() );
    if ( pPetBreedInfo == NULL )
    { return; }

    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if( pTeam == NULL )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    if ( pTeam->TeamMemberCount() != 2 )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    GamePlayer* pPlayerA = theRunTimeData.GetGamePlayerByDBID( pPetBreedInfo->GetPlayerA() );
    GamePlayer* pPlayerB = theRunTimeData.GetGamePlayerByDBID( pPetBreedInfo->GetPlayerB() );
    if ( pPlayerA == NULL || pPlayerB == NULL )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    for ( int i=0;i<pTeam->TeamMemberCount(); ++i )//pTeam->TeamMemberCount() 肯定等于2
    {
        uint32 nMemberID = pTeam->GetMemberIDByIndex( i );
        if( nMemberID != pPlayerA->GetDBCharacterID() && nMemberID != pPlayerB->GetDBCharacterID() )
        { 
            thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
            return;
        }
    }

    if ( GetDBCharacterID() == pPetBreedInfo->GetPlayerA() )
    { 
        if ( pPetBreedInfo->GetPetA() == NULL )
        {
            MsgPetBreedStatus msgStatus;
            msgStatus.status = pPetBreedInfo->GetStatusA();
            GettheServer().SendMsgToSingle( &msgStatus, pPlayerA );
        }
        else
        {
            pPetBreedInfo->SetStatusA( EPetBreed_StatusConfirm );
        }
    }
    else
    {
        if ( pPetBreedInfo->GetPetB() == NULL )
        {
            MsgPetBreedStatus msgStatus;
            msgStatus.status = pPetBreedInfo->GetStatusB();
            GettheServer().SendMsgToSingle( &msgStatus, pPlayerB );
        }
        else
        {
            pPetBreedInfo->SetStatusB( EPetBreed_StatusConfirm );
        }
    }

    // 发送消息给双方
    MsgPetBreedStatus msgStatus;
    msgStatus.header.stID = GetID();
    msgStatus.status = EPetBreed_StatusConfirm;
    GettheServer().SendMsgToSingle( &msgStatus, pPlayerA );
    GettheServer().SendMsgToSingle( &msgStatus, pPlayerB );

    // 如果双方都确认,则进行繁殖
    if (pPetBreedInfo->GetStatusA() != EPetBreed_StatusConfirm ||  pPetBreedInfo->GetStatusB() != EPetBreed_StatusConfirm)
    { return; }

    SPetItem* petA = pPetBreedInfo->GetPetA();
    SPetItem* petB = pPetBreedInfo->GetPetB();
    if (petA == NULL || petB == NULL)
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    ItemDefine::SPetMonster* pMonsterConfigA = GettheItemDetail().GetPetById( petA->GetPetID() );
    if ( pMonsterConfigA == NULL ) 
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    ItemDefine::SPetMonster* pMonsterConfigB = GettheItemDetail().GetPetById( petB->GetPetID() );
    if ( pMonsterConfigB == NULL ) 
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    int costMoneyA = thePetSettingConfig.GetPetBreedMoney( pMonsterConfigA->catchQuality, pMonsterConfigA->catchQuality ); 
    int costMoneyB = thePetSettingConfig.GetPetBreedMoney( pMonsterConfigB->catchQuality, pMonsterConfigB->catchQuality );

    if ( costMoneyA > pPlayerA->GetMoney() )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    if ( costMoneyB > pPlayerB->GetMoney() )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    if (!pMonsterConfigA->bIsBaby || !pMonsterConfigB->bIsBaby )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    if (petA->baseInfo.petType != petB->baseInfo.petType )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

	//by liaojie 11.21
    /*if (petA->baseInfo.loyalty < 100 || petB->baseInfo.loyalty < 100)
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }*/

    if (/*petA->baseInfo.duration < 1000 || petB->baseInfo.duration < 1000*/ GetCharInfo().otherdata.PetDuration < 1000)
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    if (petA->baseInfo.sex == petB->baseInfo.sex )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    if (petA->baseInfo.generation != 0 || petB->baseInfo.generation != 0 )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishFailed );
        return;
    }

    petA->breedInfo.targetGuid     = petB->baseInfo.guid;
    petA->breedInfo.targetQuality  = petB->baseInfo.quality;
    petA->breedInfo.targetCharDBID = pPlayerB->GetDBCharacterID();
    petA->breedInfo.commitTime     = TimeEx::GetNowTime();

    petB->breedInfo.targetGuid     = petA->baseInfo.guid;
    petB->breedInfo.targetQuality  = petA->baseInfo.quality;
    petB->breedInfo.targetCharDBID = pPlayerA->GetDBCharacterID();
    petB->breedInfo.commitTime     = TimeEx::GetNowTime();
    
    
    pPlayerA->_petManager.SetBreedPet( petA );
    pPlayerB->_petManager.SetBreedPet( petB );

    bool bActive;
    pPlayerA->_petManager.PopPetByBigId( petA->baseInfo.guid, bActive );
    pPlayerB->_petManager.PopPetByBigId( petB->baseInfo.guid, bActive );

    pPlayerA->OperateMoney( EOT_Sub, costMoneyA, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_PetBreedConfirm ); 
    pPlayerB->OperateMoney( EOT_Sub, costMoneyB, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_PetBreedConfirm ); 

    pPlayerA->SetBreedPetPrompt( false );
    pPlayerB->SetBreedPetPrompt( false );

    MsgChangePet changeA;
    changeA.ucOpType    = MsgChangePet::EOT_Disappear;
    changeA.nIndex      = pPlayerA->_petManager.GetPetIndexByGuid( petA->baseInfo.guid );
    changeA.guid        = petA->baseInfo.guid;
    changeA.source      = EDS_Breed;
    GettheServer().SendMsgToSingle( &changeA, pPlayerA );

    MsgChangePet changeB;
    changeB.ucOpType    = MsgChangePet::EOT_Disappear;
    changeB.nIndex      = pPlayerB->_petManager.GetPetIndexByGuid( petB->baseInfo.guid );
    changeB.guid        = petB->baseInfo.guid;
    changeB.source      = EDS_Breed;
    GettheServer().SendMsgToSingle( &changeB, pPlayerB );

    thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishSuccess );

    //繁殖操作需要立即保存数据
    GettheFileDB().SaveCharAllData( pPlayerA, EST_Time );
    GettheFileDB().SaveCharAllData( pPlayerB, EST_Time );
}

void  GamePlayer::OnMsgPetBreedAcquire ( Msg* pMsg )
{
    MsgPetBreedAcquire* pPetBreedAcquire = static_cast< MsgPetBreedAcquire* > ( pMsg );

    SPetItem* pBreedPet = _petManager.GetBreedPet();
    if ( pBreedPet == NULL )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_NoBreedPet;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( pBreedPet->GetPetID() );
    if ( pMonsterConfig == NULL ) 
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_NoBreedPet;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    int costMoney =  0.5 * thePetSettingConfig.GetPetBreedMoney( pMonsterConfig->catchQuality, pMonsterConfig->catchQuality ); 
    if ( costMoney > GetMoney() )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_NoMoney;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    int64 interval = TimeEx::GetNowTime() - pBreedPet->breedInfo.commitTime;
    int32 petBreedIntervalTime = OneMinuteSecond * g_Cfg.petBreedIntervalTime ;
    if ( interval < petBreedIntervalTime )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_Interval;
        msgAck.value  = petBreedIntervalTime - interval;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    if ( _petManager.GetPetEmptyCount() < 2 )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_PetFull;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    // 给对方发消息
    GamePlayer* pTargetPlayer = theRunTimeData.GetGamePlayerByDBID( pBreedPet->breedInfo.targetCharDBID );
    if ( pTargetPlayer != NULL )
    {
        MsgPetBreedAcquireAck msgAck2;
        msgAck2.result = MsgPetBreedAcquireAck::ER_TargetAcquired;
        msgAck2.pet    = *pBreedPet;
        HelperFunc::SafeNCpy( msgAck2.szName, GetCharName(), sizeof( msgAck2.szName ) );
        GettheServer().SendMsgToSingle( &msgAck2, pTargetPlayer );
    }

    // 产生宠物
    bool bSuccess = PetBreedGenerate();

    OperateMoney( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__, ePlayerMoneySourceType_PetBreedAcquire); 

    //繁殖操作需要立即保存数据
    GettheFileDB().SaveCharAllData( this, EST_Time );
}

void GamePlayer::OnMsgSawTalkReq( Msg* pMsg )
{
    MsgSawTalkReq* pMessage = static_cast< MsgSawTalkReq* >( pMsg );
    if ( pMessage == NULL )
    { return; }

    // 不是有效的任务
    if ( !theQuestManager.IsQuestIdValid( pMessage->questId ) )
    { return; }

    short questValue = GetVar( pMessage->questId );
    if ( theQuestManager.IsHaveSaw( pMessage->talkType, questValue ))
    { return; }

    SetVar( pMessage->questId, theQuestManager.SetHaveSaw( pMessage->talkType, questValue ) );
}

//////////////////////////////////////////////////////////////////////////
// 播放视频回应
void GamePlayer::OnMsgPlayMovieAck( Msg* pMsg )
{ // 客户端回应此消息，视频设备准备好了，可以播放了
    MsgPlayMovieAck* pPlayMovieMsg = static_cast< MsgPlayMovieAck* >( pMsg );
    if ( pPlayMovieMsg == NULL )
    { return; }

    ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus(  g_Cfg.nProtectStatusId, g_Cfg.nProtectStatusLevel );
    if ( pStatus == NULL )  // 没有状态，直接返回
    { return; }

    /*bool bHaveChange = _buffManager.ApplyBuff( true, pStatus->ustItemID, pStatus->ustLevel, GetID(), HQ_TimeGetTime(), false, pPlayMovieMsg->dwPlayTime, GetDBCharacterID(), SCharBuff::StatusEventType_Other, 0);

    if ( bHaveChange )
    { SendBuffChanged( this ); }*/

	long nResult = GLR_Success;
	nResult = ApplyBufferStatus(pStatus->ustItemID, pStatus->ustLevel, GetID(), SCharBuff::StatusEventType_Other, 0);
	if ( nResult == GLR_Success  )
	{
		OnBuffStatusChanged( true );
	}
}

void GamePlayer::OnMsgEndEventReq(Msg* pMsg)
{
    MsgEndEventReq* pEnd = static_cast< MsgEndEventReq* >( pMsg );
    if ( NULL == pEnd )
    { return; }
    SetCurEventID( 0 );
    MsgEndEvent endAck;
    endAck.header.stID = GetID();
    GettheServer().SendMsgToView( &endAck, GetID(), false );
}

void GamePlayer::OnMsgMailListReq(Msg* pMsg)
{
    GS2CSMailListReq msg;
    msg.accountId = GetAccountID();
    msg.charDbId  = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &msg );
}

void GamePlayer::OnMsgReqIdentifyData( Msg* pMsg )
{
    MsgAllIdentifyData msg;

    msg.identifyData = gCharInfoServer.identifyData;
    GettheServer().SendMsgToSingle( &msg, this );
}


void GamePlayer::OnMsgEquipTalisman( Msg* pMsg )
{
    // 战斗状态不让穿
    if ( HaveFighteFlag(eFighting) )
    { return; }

    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UseItemInBag, PasswordDefine::OP_InitAction ) )
    { return;}  // 财产保护下无法使用包裹中物品

    MsgEquipTalisman* pEquip = (MsgEquipTalisman*)pMsg;
    if ( pEquip == NULL )
    { return; }

    // 是否有这个装备
    SCharItem stItem;
    _NormalItemBag.GetItem( pEquip->ustPackIndex, &stItem );    
    if( stItem.itembaseinfo.ustItemID == InvalidLogicNumber )
    { return; }

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
    if ( pItem == NULL || pItem->ucItemType != ItemDefine::ITEMTYPE_TALISMAN )
    { return; }

    ItemDefine::SItemTalisman* pItemTalisman = static_cast< ItemDefine::SItemTalisman * > ( pItem );
    if ( pItemTalisman == NULL )
    { return; }

    //如果有旧的法宝，则放回背包内
    SCharItem* pOldTalismanItem = GetTalismanItem();

    //将装备从背包中取出
    unsigned short ustCount = 1;
    if (ierr_Success == _NormalItemBag.PopItem( pEquip->ustPackIndex, ustCount ))
    {
        Log( theXmlString.GetString(eLog_info_2slk_152),pItem->GetItemName(),pItemTalisman->ustItemID);

        if( pOldTalismanItem != NULL )
        {
            if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction ) )
            { return;}  // 财产保护下无法卸下装备

            ItemDefine::SItemTalisman* pOldItemTalismanConfig = ( ItemDefine::SItemTalisman * ) GettheItemDetail().GetItemByID( pOldTalismanItem->itembaseinfo.ustItemID ) ;
            if ( pOldItemTalismanConfig == NULL )
            { return; }

            if ( pOldItemTalismanConfig->skillId > 0 )
            { ForgetSkill( pOldItemTalismanConfig->skillId, false ); }
            
            Log( theXmlString.GetString(eLog_info_2slk_153),pOldTalismanItem->itembaseinfo.ustItemID,ustCount);
            int nSucc = _NormalItemBag.PushItem( *pOldTalismanItem, ustCount, pEquip->ustPackIndex);
            if(nSucc != ierr_Success)
            { // 放回背包失败                    
                Log(theXmlString.GetString(eLog_OnEquip_PushError),stItem.itembaseinfo.ustItemID,1);
                _NormalItemBag.PushItem( stItem, ustCount, pEquip->ustPackIndex);
                return;
            }

            DeleteTalismanItem();
        }

        SetTalismanItem( &stItem );

        if ( pItemTalisman->skillId > 0 )
        { LearnSkill( pItemTalisman->skillId, pItemTalisman->skillLevel, false, false, false ); }

        UpdateAllEquipData();
        UpdateAllSuitData() ;

        ApplyPassiveSkillsToChar();
        RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Equip ); 

        MsgEquipTalismanAck msg;
        msg.stResult     = MsgEquipTalismanAck::Result_Success;
        msg.ustPackIndex = pEquip->ustPackIndex;
        GettheServer().SendMsgToSingle( &msg, this );

        MsgTalismanChange changed;
        changed.header.stID = GetID();
        changed.opType   = MsgTalismanChange::EOT_Equip;
        changed.nItemID  = pItemTalisman->ustItemID;
        GettheServer().SendMsgToView( &changed, GetID(), true );
    }
    else
    {
        MsgEquipTalismanAck msg;
        msg.stResult = MsgEquipTalismanAck::Result_Failed;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

}

void GamePlayer::OnMsgUnEquipTalisman ( Msg* pMsg )
{
    if (HaveFighteFlag(eFighting))
    { return; }

    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction ) )
    { return;}  // 财产保护下无法卸下自身装备

    MsgUnEquipTalisman* pMsgUnEquip = (MsgUnEquipTalisman*)pMsg;
    if ( pMsgUnEquip == NULL )
    { return; }
    
    SCharItem* pTalisman = GetTalismanItem();
    if ( NULL == pTalisman )
    { return; }

    MsgUnEquipTalismanAck msgAck;
    msgAck.result       = MsgUnEquipTalismanAck::Result_Success;
    msgAck.stPackIndex  = pMsgUnEquip->stPackIndex;
    msgAck.talisman     = *pTalisman;

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pTalisman->itembaseinfo.ustItemID);
    if ( NULL == pItemCommon )
    { return; }

    ItemDefine::SItemTalisman* pItemTalisman = static_cast< ItemDefine::SItemTalisman * > ( pItemCommon );
    if ( pItemTalisman == NULL )
    { return; }

    unsigned short ustCount = 0;

    Log( theXmlString.GetString( eLog_info_2slk_154), pTalisman->itembaseinfo.ustItemID,pTalisman->itembaseinfo.ustItemCount);
    int nRes = _NormalItemBag.PushItem( *pTalisman, ustCount, pMsgUnEquip->stPackIndex );
    if ( nRes != ierr_Success )
    { 
        msgAck.result = MsgUnEquipTalismanAck::Result_Failed;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    pTalisman->itembaseinfo.ustItemID = InvalidLogicNumber;
    pTalisman->itembaseinfo.nOnlyInt  = 0;

    if ( pItemTalisman->skillId > 0 )
    { ForgetSkill( pItemTalisman->skillId, false ); }

    UpdateAllEquipData();
    UpdateAllSuitData() ;

    ApplyPassiveSkillsToChar();
    RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Equip ); 

    //发送成功消息
    GettheServer().SendMsgToSingle( &msgAck, this );

    MsgTalismanChange changed;
    changed.header.stID = GetID();
    changed.opType      = MsgTalismanChange::EOT_UnEquip;
    changed.nItemID     = InvalidLogicNumber;
    GettheServer().SendMsgToView( &changed, GetID(), true );
}

void GamePlayer::OnMsgViewActivePet  ( Msg* pMsg )
{
    MsgViewActivePet* pMsgViewActivePet = (MsgViewActivePet*)pMsg;

    BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( pMsgViewActivePet->masterId );
    if ( pMaster == NULL || !pMaster->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pMaster );
    SPetItem* pPetItem  = pPlayer->_petManager.GetActivePet();
    if ( pPetItem == NULL )
    {
        SendErrorToClient( ER_NotFoundPet );
        return;
    }

    MsgViewActivePetAck msgAck;
    msgAck.masterId = pMsgViewActivePet->masterId;
    msgAck.pet      = *pPetItem;
    GettheServer().SendMsgToSingle( &msgAck, this );
}

void GamePlayer::OnDBMsgPetBreedQueryAck  ( Msg* pMsg )
{
    DBMsgPetBreedQueryAck* pDBMsgPetBreedQueryAck = (DBMsgPetBreedQueryAck*)pMsg;

    SPetItem* pBreedPet = _petManager.GetBreedPet();
    if ( pBreedPet == NULL )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_NoBreedPet;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( pBreedPet->GetPetID() );
    if ( pMonsterConfig == NULL ) 
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_NoBreedPet;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    if ( !pDBMsgPetBreedQueryAck->bIsAcquired )
    {
        int costMoney =  0.5 * thePetSettingConfig.GetPetBreedMoney( pMonsterConfig->catchQuality, pMonsterConfig->catchQuality ); 
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_NeedMoney;
        msgAck.value  = costMoney;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return;
    }

    int64 interval = TimeEx::GetNowTime() - pBreedPet->breedInfo.commitTime;
    int32 petBreedIntervalTime = OneMinuteSecond * g_Cfg.petBreedIntervalTime ;
    if ( interval < petBreedIntervalTime )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_Interval;
        msgAck.value  = petBreedIntervalTime - interval;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    if ( _petManager.GetPetEmptyCount() < 2 )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_PetFull;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    // 给对方发消息
    GamePlayer* pTargetPlayer = theRunTimeData.GetGamePlayerByDBID( pBreedPet->breedInfo.targetCharDBID );
    if ( pTargetPlayer != NULL )
    {
        MsgPetBreedAcquireAck msgAck2;
        msgAck2.result = MsgPetBreedAcquireAck::ER_TargetAcquired;
        msgAck2.pet    = *pBreedPet;
        HelperFunc::SafeNCpy( msgAck2.szName, GetCharName(), sizeof( msgAck2.szName ) );
        GettheServer().SendMsgToSingle( &msgAck2, pTargetPlayer );
    }

    // 产生宠物
    bool bSuccess = PetBreedGenerate();

    //繁殖操作需要立即保存数据
    GettheFileDB().SaveCharAllData( this, EST_Time );
}


void GamePlayer::OnMsgReqPressKeySuit      ( Msg* pMsg )
{
    //MsgReqPressKeySuit* pMsgReqPressKeySuit = static_cast< MsgReqPressKeySuit* >( pMsg );
    //if ( pMsgReqPressKeySuit == NULL )
    //{ return; }

    //MsgAllPressKeySuit msg;

    //memcpy(msg.xPressKeySuit,gCharInfoServer.extendData.xPressKeySuit,sizeof( SPressKeySuit ) * MAX_PRESSKEYSUIT_COUNT );
    //GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnMsgPressKeySuit      ( Msg* pMsg )
{
    //MsgPressKeySuit* pMsgPressKeySuit = static_cast< MsgPressKeySuit* >( pMsg );
    //if ( pMsgPressKeySuit == NULL )
    //{ return; }

    //MsgPressKeySuitAck msgAck;
    //msgAck.nResult = MsgPressKeySuitAck::ECD_Failed;
    //msgAck.nIndex  = pMsgPressKeySuit->nIndex;

    //for (int i = 0;i < EEquipPartType_MaxEquitPart; ++i)
    //{
    //    int64 nGuid = pMsgPressKeySuit->equipitem[ i ];
    //    SCharItem* pCharItem = _NormalItemBag.GetItemByOnlyBigId(nGuid);
    //    if (pCharItem == NULL)
    //    {
    //        msgAck.nResult = MsgPressKeySuitAck::ECD_NotFoundEquip;
    //        GettheServer().SendMsgToSingle( &msgAck, this );
    //        return;
    //    }
    //}

    //msgAck.AddEquipItem( pMsgPressKeySuit->equipitem );
    //msgAck.nResult = MsgPressKeySuitAck::ECD_Success;
    //GettheServer().SendMsgToSingle( &msgAck, this );
}

void GamePlayer::OnMsgPressKeySuitName  ( Msg* pMsg )
{
    //MsgPressKeySuitName* pMsgPressKeySuitName = static_cast< MsgPressKeySuitName* >( pMsg );
    //if ( pMsgPressKeySuitName == NULL )
    //{ return; }

    //MsgPressKeySuitNameAck msgAck;
    //msgAck.nIndex  = pMsgPressKeySuitName->nIndex;

    //HelperFunc::SafeNCpy( msgAck.keySuitName ,pMsgPressKeySuitName->keySuitName, sizeof(pMsgPressKeySuitName->keySuitName) );
    //GettheServer().SendMsgToSingle( &msgAck, this );
}

void GamePlayer::OnMsgEquipPressKeySuit ( Msg* pMsg )
{
    //MsgEquipPressKeySuit* pMsgEquipPressKeySuit = static_cast< MsgEquipPressKeySuit* >( pMsg );
    //if ( pMsgEquipPressKeySuit == NULL )
    //{ return; }

    //int nIndex = pMsgEquipPressKeySuit->nIndex;
    //if ( nIndex > MAX_PRESSKEYSUIT_COUNT )
    //{
    //    MsgAckResult msgAck;
    //    msgAck.result = ER_EquipPressKeySuit;
    //    GettheServer().SendMsgToSingle( &msgAck, this );
    //    return;
    //}

    //SPressKeySuit keySuit = gCharInfoServer.extendData.xPressKeySuit[nIndex];

    //for (int i = 0; i < EEquipPartType_MaxEquitPart; ++i)
    //{
    //    int64 nGuid = keySuit.equipitem[ i ];
    //    SCharItem* pCharItem = _NormalItemBag.GetItemByOnlyBigId(nGuid);
    //    if (pCharItem == NULL)
    //    { continue; }

    //    if( pCharItem->itembaseinfo.ustItemID == InvalidLogicNumber )
    //    { continue; }

    //    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    //    if ( pItem == NULL || !pItem->IsCanEquip() )
    //    { continue; }

    //    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip *)pItem;
    //    if ( pItemCanEquip == NULL )
    //    { continue; }

    //    // 玩家成功换上新的装备，并取出旧的装备
    //    SCharItem* pOldEquipItem = NULL;
    //    int nWhere = -1; 

    //    if( IsCanEquip( i, pCharItem ))
    //    { // 如果可以装备
    //        nWhere = i;
    //        if ( nWhere == EEquipPartType_Ring1 || nWhere == EEquipPartType_Bangle1 )
    //        { // 如果是戒指 或者 手镯 优先填左边
    //            SCharItem* pItem1 = GetVisualEquipItem( nWhere );
    //            SCharItem* pItem2 = GetVisualEquipItem( nWhere + 1 );

    //            // 如果左边有 右边为空 填右边
    //            if ( pItem1 != NULL &&  pItem2==NULL) 
    //            { nWhere = i + 1; }
    //        }

    //        pOldEquipItem = GetVisualEquipItem( nWhere );
    //        break;
    //    }

    //    if ( i == EEquipPartType_Ring1 || nWhere == EEquipPartType_Bangle1 )
    //    { i += 2; } // 跳过右边所以跳两位
    //    else
    //    { ++i; } // 其他位置跳一位

    //    if ( nWhere != -1 )
    //    { // 如果有适合的位置
    //        //将装备从背包中取出
    //        unsigned short ustCount = 1;
    //        if (ierr_Success == _NormalItemBag.PopItem( pCharItem->itembaseinfo.stPacketIdx, ustCount ))
    //        {
    //            Log( theXmlString.GetString(eLog_info_2slk_152),pItem->GetItemName(),pItemCanEquip->ustItemID);

    //            if( pOldEquipItem != NULL )
    //            { //如果有旧的装备，则放回背包内
    //                Log( theXmlString.GetString(eLog_info_2slk_153),pOldEquipItem->itembaseinfo.ustItemID,ustCount);
    //                int nSucc = _NormalItemBag.PushItem( *pOldEquipItem, ustCount, pCharItem->itembaseinfo.stPacketIdx);
    //                if(nSucc != ierr_Success)
    //                { // 放回背包失败                    
    //                    Log(theXmlString.GetString(eLog_OnEquip_PushError), pCharItem->itembaseinfo.ustItemID, 1);
    //                    _NormalItemBag.PushItem( *pCharItem, ustCount, pCharItem->itembaseinfo.stPacketIdx);
    //                    return;
    //                }

    //                DeleteVisualEquipItem( nWhere );
    //            }

    //            MsgAckEquip msg;
    //            msg.stResult = MsgAckEquip::Result_Success;
    //            if ( !Equip( nWhere, *pCharItem, pOldEquipItem != NULL ) )
    //            {   
    //                msg.stResult = MsgAckEquip::Result_Failed;
    //                GettheServer().SendMsgToSingle( &msg, this );
    //                return;
    //            }

    //            msg.stResult     = MsgAckEquip::Result_Success;
    //            msg.ustPackIndex = pCharItem->itembaseinfo.stPacketIdx;
    //            msg.ustWhere     = nWhere;
    //            GettheServer().SendMsgToSingle( &msg, this );
    //        }
    //    }
    //}

    ////发送人物装备
    //SendVisualEquipDataToClient();

    //// 重新算一次人物属性
    //UpdateAllEquipData();
    //UpdateAllSuitData() ;

    //RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Equip ); 
    //return;
}

void GamePlayer::OnMsgUpdateGuideReq ( Msg* pMsg )
{
    MsgUpdateGuideReq* pMsgUpdateGuideReq = (MsgUpdateGuideReq*)pMsg;

    gCharInfoServer.otherdata.SetGuideVar( pMsgUpdateGuideReq->nGuidId, pMsgUpdateGuideReq->nState );

    MsgUpdateGuideAck ack;
    ack.nGuidId = pMsgUpdateGuideReq->nGuidId;
    ack.nState  = pMsgUpdateGuideReq->nState;
    GettheServer().SendMsgToSingle( &ack, this );
}

void GamePlayer::OnGS2CSUpdateAntiaddictionInfoAck( Msg* pMsg )
{
	CS2GSUpdateAntiaddictionInfoAck* pMessage = static_cast< CS2GSUpdateAntiaddictionInfoAck* > ( pMsg );

	//Log("[%d]CS2GSUpdateAntiaddictionInfoAck Result[%u][%u:%u:%u]", _bNeedAntiAddiction, pMessage->nResult, pMessage->nType, pMessage->nOnlineTime, pMessage->nDuration );
	Log(theXmlString.GetString(eServerLog_FangChenMi1), _bNeedAntiAddiction, pMessage->nResult, pMessage->nType, pMessage->nOnlineTime, pMessage->nDuration );

	// 没打开防沉迷系统或者玩家不是小孩时返回
	if ( !_bNeedAntiAddiction )
	{ return; }

	if ( ER_Failed == pMessage->nResult)
	{
		Log("AntiAddiction Type[%d] Fail[%u]", pMessage->nType, pMessage->nDuration );
		return;
	}

	// 成功 设置信息
	gTransferRuntimeInfo.nAntiAddictionDbOnlineTime = pMessage->nOnlineTime;
	AntiAddictionState curState = CalcAntiAddictionStatus( pMessage->nOnlineTime );

	switch ( pMessage->nType )
	{
	case GS2CSUpdateAntiaddictionInfoReq::EUpdateReqType_Init:
		{
			// 得到总的时间
			gTransferRuntimeInfo.nAntiAddicationStatus = curState;

			// 已经得到防沉迷信息
			if ( !gTransferRuntimeInfo.bGetAntiAddictionInfo )
			{ gTransferRuntimeInfo.bGetAntiAddictionInfo = true; }

			/*Log("AntiAddiction Init status=%d onlinetime:%d t1:%d %d t2:%d %d t3:%d %d",
				gTransferRuntimeInfo.nAntiAddicationStatus, GetAntiAddictionOnlineTime(),
				g_Cfg.xAntiAddictionInfo._normal._playTime, g_Cfg.xAntiAddictionInfo._normal._notifyTime,
				g_Cfg.xAntiAddictionInfo._tired._playTime, g_Cfg.xAntiAddictionInfo._tired._notifyTime,
				g_Cfg.xAntiAddictionInfo._rest._playTime, g_Cfg.xAntiAddictionInfo._rest._notifyTime );*/

			Log(theXmlString.GetString(eServerLog_FangChenMi2),
				gTransferRuntimeInfo.nAntiAddicationStatus, GetAntiAddictionOnlineTime(),
				g_Cfg.xAntiAddictionInfo._normal._playTime, g_Cfg.xAntiAddictionInfo._normal._notifyTime,
				g_Cfg.xAntiAddictionInfo._tired._playTime, g_Cfg.xAntiAddictionInfo._tired._notifyTime,
				g_Cfg.xAntiAddictionInfo._rest._playTime, g_Cfg.xAntiAddictionInfo._rest._notifyTime );



			// 通知客户端防沉迷信息
			SendMsgWallowAbout( MsgWallowAbout::ENotifyType_Init );
		}
		break;
	case GS2CSUpdateAntiaddictionInfoReq::EUpdateReqType_Update:
		{
			// 累积在线时长单位分钟
			_nHaveSaveAntiAddtionDuration += pMessage->nDuration;

			if ( gTransferRuntimeInfo.nAntiAddicationStatus != curState )
			{
				//Log("Antiaddiction change status from [%d->%d] %d ", gTransferRuntimeInfo.nAntiAddicationStatus, curState, GetAntiAddictionOnlineTime() );
				Log(theXmlString.GetString(eServerLog_FangChenMi3), gTransferRuntimeInfo.nAntiAddicationStatus, curState, GetAntiAddictionOnlineTime() );

				// 设置信息
				gTransferRuntimeInfo.nAntiAddicationStatus = curState;

				// 通知计数重置
				ResetAntiAddictionNotifyIndex();

				// 通知客户端防沉迷信息
				SendMsgWallowAbout( MsgWallowAbout::ENotifyType_StatusChange );
			}

			//Log("AntiAddiction Update status[%d] +[%d] time[%u] Update Success", gTransferRuntimeInfo.nAntiAddicationStatus, pMessage->nDuration, GetAntiAddictionOnlineTime() );
			Log(theXmlString.GetString(eServerLog_FangChenMi4), gTransferRuntimeInfo.nAntiAddicationStatus, pMessage->nDuration, GetAntiAddictionOnlineTime() );
				
				
		}
		break;
	case GS2CSUpdateAntiaddictionInfoReq::EUpdateReqType_Exit:
		{ // 应该收不到
			// 累积在线时长单位分钟
			_nHaveSaveAntiAddtionDuration += pMessage->nDuration;
			//Log("AntiAddiction Exit status[%d] +[%d] time[%u] Update Success", gTransferRuntimeInfo.nAntiAddicationStatus, pMessage->nDuration, GetAntiAddictionOnlineTime()  );
			Log(theXmlString.GetString(eServerLog_FangChenMi5), gTransferRuntimeInfo.nAntiAddicationStatus, pMessage->nDuration, GetAntiAddictionOnlineTime()  );
		}
		break;
	}
}

void GamePlayer::OnMsgBianShen( Msg* pMsg )
{
	if (!pMsg)
	{
		return;
	}
	MsgC2GAskBianShen* pBianShen = (MsgC2GAskBianShen*)pMsg;
	if (!pBianShen)
	{
		return;
	}

	MsgG2CReqBianShen msg_req;
	msg_req.header.stID = GetID();

	CItemHero::SItemHero* pHero = theItemHero.FindHeroByHeroID(pBianShen->hero_id);
	if (!pHero)
	{
		//todo:告诉客户端主将不存在
		msg_req.result = MsgG2CReqBianShen::eResult_NoHero;
		goto todo;
	}
	
	//没有足够金钱
	if (GetJiaoZiMoney() < pHero->need_money)
	{
		msg_req.result = MsgG2CReqBianShen::eResult_NoMoney;
		goto todo;
	}

	//没有足够等级
	if (GetLevel()< pHero->need_lv)
	{
		msg_req.result = MsgG2CReqBianShen::eResult_NoLevel;
		goto todo;
	}
	
	if (GetSex()!=pHero->hero_sex && (pHero->hero_sex == 1 || pHero->hero_sex ==0))
	{
		msg_req.result = MsgG2CReqBianShen::eResult_diffSex;
		goto todo;
	}
	if (GetItemCount(pHero->material_id)< pHero->material_count)
	{
		msg_req.result = MsgG2CReqBianShen::eResult_NoMataril;
		goto todo;
	}
	//todo:判断可不可以变身
	//通过物品ID找到物品，在那个背包
	//popitem
	//找到物品
	//删除道具
	ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( pHero->itemd_id );
	if (!pCommon)
	{
		return;
	}
	ItemBag* pItemBag = GetItemBagByItemType( pCommon->ucItemType );
	if (!pItemBag)
	{
		return;
	}

	/*SCharItem charItem;
	charItem.itembaseinfo.ustItemID = pCommon->ustItemID;
	charItem.itembaseinfo.ustItemCount = 1;*/
	//SCharItem* charItem = pItemBag->GetItemByItemID(pHero->itemd_id);
	SCharItem* charItem = pItemBag->GetItemByIndex(pBianShen->nItemIndex);
	if(!charItem)
	{
		return;
	}
	if(charItem->GetItemID() != pHero->itemd_id )
	{
		return;
	}
	/*if (!(pItemBag->CanPopItem(*charItem)))
	{
		msg_req.result = MsgG2CReqBianShen::eResult_popItemFail;
		goto todo;
	}*/

	//处理材料
	ItemDefine::SItemCommon* pMaterial = GettheItemDetail().GetItemByID( pHero->material_id );
	if (!pMaterial)
	{
		return;
	}
	ItemBag* pMaterialBag = GetItemBagByItemType( pMaterial->ucItemType );
	if (!pMaterialBag)
	{
		return;
	}
	SCharItem* charItem1 = pMaterialBag->GetItemByItemID( pHero->material_id );
	//charItem1.itembaseinfo.ustItemID = pHero->material_id;
	//charItem1.itembaseinfo.ustItemCount = pHero->material_count;

	if (!(pMaterialBag->CanPopItem(*charItem1)))
	{
		msg_req.result = MsgG2CReqBianShen::eResult_popItemFail;
		goto todo;
	}

	if (pMaterialBag->PopItemByID(pHero->material_id, pHero->material_count) != ierr_Success)
	{
		msg_req.result = MsgG2CReqBianShen::eResult_popItemFail;
		goto todo;
	}
	//处理材料end

	if (!charItem->IsBounded())
	{
		charItem->SetBounded(true);
	}
	msg_req.result = MsgG2CReqBianShen::eResult_succ;
	msg_req.hero_id = pHero->hero_id;
	msg_req.nItemIndex = pBianShen->nItemIndex;

	OperateJiaoZi( EOT_Sub, pHero->need_money, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_BianShen);

	//添加主将技能到角色
	if (GetCharInfo().baseinfo.liveinfo.hero_id!=pHero->hero_id)
	{
		_HeroSkillBag.ClearAllSkills();
	}
	SetHeroId(pHero->hero_id);

	_HeroSkillBag.AddSkill(pHero->hero_skill1,pHero->skill1_lv);
	_HeroSkillBag.AddSkill(pHero->hero_skill2,pHero->skill2_lv);
	_HeroSkillBag.AddSkill(pHero->hero_skill3,pHero->skill3_lv);

	//////////属性操作///////////////////////////////////
	SCharBaseAttr* pCharBase =GetCharBaseAttr();
	if (!pCharBase)
	{
		return;
	}
	// 清除一级属性
	ClearAllBaseAttrByPart ( ECustomDataPart_hero );
	// 清除二级属性
	ClearAllFightAttrByPart( ECustomDataPart_hero );

	for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
	{ 
		pCharBase->baseAttrValue[i].hero += 0;
		pCharBase->baseAttrValue[i].heroPer += pHero->heroAttr[i];/*pHero->[i]*/
		pCharBase->baseAttrValue[i].UpdateFinal();
	}
	// 一级属性作用二级属性
	ApplyBaseAttrToFightAttr(true,ECustomDataPart_hero);
	for (int i=CharAttr_Strength;i<CharAttr_AttributMaxCount;i++)
	{
		fightAttrChangeRecord[i] = true;
	}
	UpdateCharAllAttibute();
	RefreshHeroAttr();
	SCharHeroInfo sHeroAddAttr;
	GetHeroAddAttr(&sHeroAddAttr);
	MsgTellHeroAddAttr msg_heroAttr;
	msg_heroAttr.heroAttr = sHeroAddAttr;
	GettheServer().SendMsgToSingle( &msg_heroAttr, this );

	SendCharAttibuteToClient();

	//添加卡牌
	short stCardId = theCardIconConfig.GetCardIdByTypeId( pHero->hero_id );
	if ( stCardId != -1 )
	{
		short stlevel = pCommon->ustLevel;
		if ( stlevel > 1 )
			stlevel -= 1;
		AddCard( stCardId, stlevel );
	}
	//////////////////////////////////////////////////////////
todo:
	GettheServer().SendMsgToView(&msg_req,GetID(),false);
}


void GamePlayer::OnMsgFlyToTPHJ( Msg* pMsg )
{
	MsgC2GReqFLYTOTPHJ* pTPHJ = (MsgC2GReqFLYTOTPHJ*) pMsg;
	if (pTPHJ->in_or_out)
	{
		if (m_bDeathAndWaitForRelive||GetStatus() == CS_ONSHIP||m_bHitchMoving )
		{
			return;
		}
		DWORD mapid = EctypeId2MapId( GetMapID() );
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(mapid);
		if ( pMapData == NULL||pMapData->IsEctypeMap() || !theTPHJManager.MapCanEnterTphj(mapid))
		{ return; }

		SetLastMapID_BeforeTPHJ(mapid);
		SetLastX_BeforeTPHJ(GetFloatX());
		SetLastY_BeforeTPHJ(GetFloatY());
		char rankID = GetTPHJRank();
		FlyToMapReq(theTPHJManager.GetMapIdByRank(rankID),theTPHJManager.GetPosXByRank(rankID),theTPHJManager.GetPosYByRank(rankID),theTPHJManager.GetPosZByRank(rankID));
	}
	else
	{
		FlyToMapReq(GetLastMapID_BeforeTPHJ(),GetLastX_BeforeTPHJ(),GetLastY_BeforeTPHJ(),0.0f);
	}	
}

void GamePlayer::OnMsgChangeToBiaocheReq( Msg* pMsg )
{
	MsgChangeToBiaocheReq *pMessage = (MsgChangeToBiaocheReq *) pMsg;
	
	ItemDefine::SMonster *biaoche_monster = theItemDetailConfig.GetMonsterById(pMessage->monsterID);
	if (biaoche_monster == NULL)
		return;

	// 玩家变身为镖车
	mBiaocheState = true;

	// 设置玩家的速度为镖车的速度
	m_BiaoCheSpeed = biaoche_monster->fMoveSpeed;
	/*GetCharFightAttr()->moveSpeed.base = biaoche_monster->fMoveSpeed;
	GetCharFightAttr()->moveSpeed.UpdateFinal();*/
	ChangeAttr(CharAttr_MoveSpeed, GetMoveSpeed());

	// 应用Buff，保护玩家
	if ( ApplyBufferStatus( g_Cfg.nOnBiaoCheBuffId, g_Cfg.nOnBiaoCheBuffLevel, GetID(), SCharBuff::StatusEventType_Other, 0) == GLR_Success )
		OnBuffStatusChanged( true );

	// 通知视野内的玩家
	MsgChangeToBiaocheAck msg;
	msg.header.stID = GetID();
	msg.monsterID = pMessage->monsterID;
	GettheServer().SendMsgToView(&msg, GetID(), false);
}

void GamePlayer::OnMsgRestoreFromBiaocheReq( Msg* pMsg )
{
	MsgChangeToBiaocheReq *pMessage = (MsgChangeToBiaocheReq *) pMsg;
	
	// 玩家从镖车变回人形
	mBiaocheState = false;
	m_BiaoCheSpeed = 0.0f;
	// 在此从变身镖车恢复人形的时候，将速度设置为5
	/*GetCharFightAttr()->moveSpeed.base = 5.0;
	GetCharFightAttr()->moveSpeed.UpdateFinal();*/
	ChangeAttr(CharAttr_MoveSpeed, GetMoveSpeed());

	//删除Buff
	if (_buffManager.ClearBuffByBuffIdLevel( g_Cfg.nOnBiaoCheBuffId, g_Cfg.nOnBiaoCheBuffLevel ))
		OnBuffStatusChanged( true );
	
	// 通知视野内的玩家
	MsgRestoreFromBiaocheAck msg;
	msg.header.stID = GetID();
	GettheServer().SendMsgToView(&msg, GetID(), false);
}

void GamePlayer::OnMsgChangeHeroType( Msg* pMsg )
{
	if ( HaveFighteFlag(eFighting) )
	{ return; }

	if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction ) )
	{ return;}  // 财产保护下无法卸下装备

	MsgShowHeroSuit* pSuit = (MsgShowHeroSuit*)pMsg;

	if (pSuit->flag == MsgShowHeroSuit::eHeroSuitFlag::eHeroSuitFlag_show)
	{
		gCharInfoServer.visual.ShowHero( true);
	}
	else
	{
		gCharInfoServer.visual.ShowHero( false);
	}
	pSuit->header.stID = GetID();
	GettheServer().SendMsgToView( pSuit, GetID(), false );
}

void GamePlayer::OnMsgAckLevelUp(Msg* pMsg)
{
	MsgAckLevelUp* pAckLVUp = (MsgAckLevelUp*)pMsg;
	if (!pAckLVUp)
	{
		return;
	}
	int nOldLevel = GetLevel();
	if (nOldLevel < manual_levelup)
	{
		return;
	}
	int nNewLevel = nOldLevel+1;
	int64 nCurExp = GetPlayerCurrentExp();
	unsigned long need_exp = theExpStage.GetExpDistance(nOldLevel);
	if( nOldLevel < nNewLevel && nNewLevel <= g_Cfg.m_nLevelLimt&&nCurExp >= need_exp)
	{
		ChangeLevel( nNewLevel );
		//LYH日志添加
		if (!theLogEventService.LogLevelChange(GetAccountID(),GetDBCharacterID(),nOldLevel,nNewLevel,GetCharName()))
		{
         Log(theXmlString.GetString(eLog_info_2slk_29),nOldLevel,nNewLevel);
		}
		
	}
}

void GamePlayer::OnMsgAckActiveLimit(Msg* pMsg)
{
	MsgAckActiveLimit* pAckActive = (MsgAckActiveLimit*)pMsg;
	if (!pAckActive)
	{
		return;
	}

	if (GetLevel() < theLevelLimitGameManager.GetLimitLevel()||theLevelLimitGameManager.GetLimitLevel() <= 0)
	{
		return;
	}

	theLevelLimitGameManager.ActiveLimitToCS(GetCharName());
}

void GamePlayer::OnMsgAckLimitInfo( Msg* pMsg )
{
	MsgAckLimitInfo* pAck = (MsgAckLimitInfo*)pMsg;
	if (pAck)
	{
		SendLevelLimitInfo();
	}
}

//从dbserver 设置数据库的时候发过来的
void GamePlayer::OnDBMsgSetConsumeScore( Msg* pMsg )
{
	DBMsgSetConsumeScore* pSetBilling = (DBMsgSetConsumeScore*)pMsg;
	if (!pSetBilling)
	{
		return;
	}
	if (pSetBilling->account_id != GetAccountID()
		||pSetBilling->character_id != GetDBCharacterID())
	{
		//todo:如果收到的消息里面帐号ID或者角色ID与GS中的不同,则怎么办?暂时return
		return;
	}

	if(pSetBilling->money != GetConsumeScore())
	{
		//todo:如果收到的点数与GS中的角色身上的不符合则?暂时下发给CLIENT重置
		MsgRMBConsumeScore xChange;
		xChange.header.stID = GetID();
		xChange.jifen     = pSetBilling->money;
		SendMessageToClient( &xChange );

		OperateConsumeScore( EOT_Set, pSetBilling->money, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Cache,false);
	}
}

void GamePlayer::OnDBMsgSetBillingMoney( Msg* pMsg )
{
	DBMsgSetBillingMoney* pSetBilling = (DBMsgSetBillingMoney*)pMsg;
	if (!pSetBilling)
	{
		return;
	}
	if (pSetBilling->account_id != GetAccountID()
		||pSetBilling->character_id != GetDBCharacterID())
	{
		//todo:如果收到的消息里面帐号ID或者角色ID与GS中的不同,则怎么办?暂时return
		return;
	}

	if(pSetBilling->money != GetJinDing())
	{
		////todo:如果收到的点数与GS中的角色身上的不符合则?暂时下发给CLIENT重置
		MsgRMBGoldChange xChange;
		xChange.header.stID = GetID();
		xChange.jinDing     = pSetBilling->money;
		xChange.jinPiao     = GetJinPiao();
		SendMessageToClient( &xChange );

		OperateJinDing( EOT_Set, pSetBilling->money, __FUNCTION__, __LINE__,ePlayerMoneySourceType_DBMsgSetBillingMoney,false);
	}
}

void GamePlayer::OnMsgFlytoKingdom( Msg* pMsg )
{
	if (!pMsg)
	{
		return;
	}
	MsgFlytoKindom* pFly = (MsgFlytoKindom*)pMsg;
	if (!pFly)
	{
		return;
	}
	if(IsOpenStall())
	{
		return;
	}
	FlyToMapReq(pFly->map_id,pFly->map_x,pFly->map_y,0.0f);
}
void GamePlayer::OnMsgUnBindEquipReq(Msg* pMsg)
{
	if (!pMsg)
	{
		return;
	}
	MsgUnBindEquipReq* pUn = (MsgUnBindEquipReq*)pMsg;
	if (!pUn)
	{
		return;
	}
	//处理指定装备的解绑定
	MsgUnBindEquipAck ack;
	if(UnBindBagEquip(pUn->nEquipGuid))
		ack.nEquipGuid = pUn->nEquipGuid;
	else
		ack.nEquipGuid = -1;
	//发送命令通知客户端 告诉客户端装备解绑成功
	GettheServer().SendMsgToSingle( &ack,this);
}

void GamePlayer::OnMsgAskForPresent( Msg* pMsg )
{
	if (!pMsg)
	{
		return;
	}
	MsgAskForPresent* pPresent = (MsgAskForPresent*)pMsg;
	if (!pPresent||strlen(pPresent->sn) == 0)
	{
		return;
	}

	MsgGS2CSAskForPresent askfor;
	askfor.accountid = GetAccountID();
	askfor.characterid = GetDBCharacterID();
	strncpy_s(askfor.sn,sizeof(askfor.sn),pPresent->sn,sizeof(askfor.sn) - 1);
	strncpy_s(askfor.charactername,sizeof(askfor.charactername),GetCharName(),sizeof(askfor.charactername) - 1);
	GettheServer().SendMsgToCenterServer(&askfor);
}
void GamePlayer::OnMsgAddPetEquip( Msg* pMsg )
{
	//让副将穿上装备
	MsgAddPetEquip * pE = (MsgAddPetEquip *)pMsg;
	if(!pE)
		return;
	SCharItem* pBagItem = GetBagItemByGuid(pE->ItemOnlyID);
	if(!pBagItem)
		return;
	//获取 装备的位置ID
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pBagItem->itembaseinfo.ustItemID);
	if(!pItemCommon)
		return;
	ItemDefine::SItemPetEquip * pPetEquip = (ItemDefine::SItemPetEquip *)pItemCommon;
	_petManager.ChangePetEquip(pE->PetGuID,pE->ItemOnlyID,pPetEquip->iPos);
}
void GamePlayer::OnMsgRemovePetEquip( Msg* pMsg )
{
	MsgRemovePetEquip * pR = (MsgRemovePetEquip *)pMsg;
	if(!pR)
		return;
	//获取副将身上待拖掉的装备
	SPetItem * pPet = _petManager.GetPetByGuid(pR->PetGuID);
	if(!pPet)
		return;
	for(int i =0;i<SPetItem::PetEquip_MaxSum;++i)
	{
		if(pPet->baseInfo.PetEquip[i].itembaseinfo.nOnlyInt == pR->PetEquipOnlyID)
		{
			SCharItem* pBagItem =&pPet->baseInfo.PetEquip[i];
			ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pBagItem->itembaseinfo.ustItemID);
			if(!pItemCommon)
				return;
			ItemDefine::SItemPetEquip * pPetEquip = (ItemDefine::SItemPetEquip *)pItemCommon;
			_petManager.RemovePetEquip(pR->PetGuID,pPetEquip->iPos,pR->BagIndex);
		}
	}
}
void GamePlayer::OnMsgPetCompose( Msg* pMsg )
{
	//将2个副将进行合成
	MsgPetCompose * pCompose = (MsgPetCompose *)pMsg;
	if(!pCompose)
		return;
	__int64 MainPetID = pCompose->MainPetGuid;
	__int64 SecPetID = pCompose->SecPetGuid;
	SPetItem * pMainPet = _petManager.GetPetByGuid(MainPetID);
	SPetItem * pSecPet = _petManager.GetPetByGuid(SecPetID);
	if(!pMainPet || !pSecPet)
		return;
	if(pMainPet == _petManager.GetActivePet() || pSecPet == _petManager.GetActivePet())
		return;
	for(int i =0;i<SPetItem::PetEquip_MaxSum;++i)
	{
		if(pSecPet->baseInfo.PetEquip[i].GetItemGuid() != 0)
		{
			return;
		}
	}
	int ItemID =SID_PetComPose;
	int ItemSum = 1;
	if(!RemoveItem(ItemID,ItemSum))
		return;
	_petManager.ChangePetAtterValue(MainPetID,SecPetID);//合成2个副将
}

void GamePlayer::OnMsgCardAchieve( Msg* pMsg )
{
	MsgCardAchieve* pCard = (MsgCardAchieve*)pMsg;
	if ( !pCard )
		return;

	if ( pCard->stAchieveId < 0 || pCard->stAchieveId >= More_nCardAchieve )
		return;

	if ( _NormalItemBag.GetItemEmptyCount() < NUMERIC_ONE ) //判断背包有没有空位
		return;

	if ( !SetCardAchieve( pCard->stAchieveId ) )
		return;

	CardAchieveConfig::CardAchieveVector vecAchieve = theCardAchieveConfig.GetCardVec();

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( vecAchieve[pCard->stAchieveId].unItemID );
	if ( !pItemCommon )
		return;

	if ( AddItem( vecAchieve[pCard->stAchieveId].unItemID, NUMERIC_ONE, EIGS_UnKnow ) != ierr_Success )
		return;

	MsgCardAchieveAck msg;
	msg.stAchieveId = pCard->stAchieveId;
	GettheServer().SendMsgToSingle( &msg, this );

	GetScriptMgr()->StartupVM( ST_CARD_ACHIEVE, pCard->stAchieveId, this );
}

void GamePlayer::OnMsgOpenBagStorage( Msg* pMsg )
{
	//打开随身仓库
	if(!_petManager.GetActivePet())
		return;
	MsgUpdateStorage xUpdate;
    xUpdate.SetCompress();
    xUpdate.stStorage   = _StorageBag;
    xUpdate.nNpcId      = InvalidLogicNumber;
    SendMessageToClient( &xUpdate );
}

void GamePlayer::OnMsgSevenDaysData( Msg* pMsg )
{
	/*if ( !pMsg )
		return;*/

	MsgSevenDaysDataAck msg;

	for (int i = 0; i < SevenDaysConfig::TD_Max; i++)
	{
		msg.taskState[i] = _sevenDayManager.GetTaskState(i);
		msg.taskVar[i] = _sevenDayManager.GetTaskVar(i);
	}

	GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnMsgAskSevenDaysTask( Msg* pMsg )
{
	MsgAskSevenDaysTask* pAsk = (MsgAskSevenDaysTask*)pMsg;
	if (!pAsk)
		return;
	if ( pAsk->index < SevenDaysConfig::TD_FirstDay || pAsk->index > SevenDaysConfig::TD_SeventhDay )
		return;

	MsgAskSevenDaysTaskAck msg;

	if ( !_sevenDayManager.GainTask( pAsk->index ) )
		msg.result = MsgAskSevenDaysTaskAck::R_Fail;

	GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnMsgAskSevenDaysReward( Msg* pMsg )
{
	MsgAskSevenDaysReward* pReward = (MsgAskSevenDaysReward*)pMsg;
	if ( !pReward )
		return;
	if ( pReward->index < SevenDaysConfig::TD_FirstDay || pReward->index > SevenDaysConfig::TD_SeventhDay )
		return;

	if ( _NormalItemBag.GetItemEmptyCount() < NUMERIC_ONE ) //判断背包有没有空位
		return;

	if ( !_sevenDayManager.GainReward( pReward->index ) )
		return;

	SevenDaysConfig::DataCommonVec dataVec = theSevenDaysConfig.GetDataCommonVec();

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( dataVec[pReward->index].nGiftID );
	if ( !pItemCommon )
		return;

	AddItem( dataVec[pReward->index].nGiftID, NUMERIC_ONE, EIGS_UnKnow );
}

void GamePlayer::OnMsgChangeChannel ( Msg* pMsg )
{
	MsgChangeChannelREQ* pChangeChannel = (MsgChangeChannelREQ*)pMsg;
	MsgChangeChannelACK ack;
	if (!pChangeChannel||pChangeChannel->nTargetServerId < 0)
	{
		ack.uResult = eChangeChannelRet_Error;
		GettheServer().SendMsgToSingle( &ack, this );
		return;
	}

	if (g_Cfg.dwServerID == pChangeChannel->nTargetServerId)
	{
		ack.uResult = eChangeChannelRet_Same;
		GettheServer().SendMsgToSingle( &ack, this );
		return;
	}

	if ( IsDead() )
	{
		ack.uResult = eChangeChannelRet_Dead;
		GettheServer().SendMsgToSingle( &ack, this );
		return;
	}

	if ( HaveFighteFlag( eFighting ) )
	{
		ack.uResult = eChangeChannelRet_Fight;
		GettheServer().SendMsgToSingle( &ack, this );
		return;
	}

	ack.uResult = eChangeChannelRet_Succ;
	GettheServer().SendMsgToSingle( &ack, this );

	GS2CSSwitchStageReq msg;//请求道其他GameServer上的地图
	msg.header.stID      = GetID();
	msg.nSwitchStageType = SSRT_CHANGECHANNEL;
	msg.nMapId           = GetMapID();
	msg.fX               = GetFloatX();
	msg.fY               = GetFloatY();
	msg.fDir             = GetDir();
	msg.nAccountId       = GetAccountID();
	msg.nCharacterDbId   = GetDBCharacterID();
	msg.dwTime           = HQ_TimeGetTime();
	msg.nServerId        = g_Cfg.dwServerID;
	msg.ustCountryID     = GetCountry();
	msg.nTargetServerId  = pChangeChannel->nTargetServerId;
	GettheServer().SendMsgToCenterServer( &msg );
	SetFloatZ( WORLD_HEIGHT );     // 地图不相同, 设置z点坐标
	// 切服后启动定时器
	StartChangeServerTimer(OneMinuteMicroSecond);
}
void GamePlayer::OnMsgClearTeamMapReq( Msg* pMsg )
{
	MsgClearTeamMapReq* pClearTeamMapReq = (MsgClearTeamMapReq*)pMsg;
	if(!pClearTeamMapReq)
		return;
	if(!HaveTeam())
		return;
	GameTeam *pTeam = theGameTeamManager.GetTeam( GetTeamID() );
	if(!pTeam)
		return;
	if(!pTeam->IsTeamHeader(GetDBCharacterID()))
		return;
	//判断地图
	int Sum = pTeam->TeamMemberCount();
	for(int i=0;i<Sum;++i)
	{
		GameTeamMember * pMember = pTeam->GetTeamMemberByIndex(i);
		if(!pMember)
			continue;
		GamePlayer* pMemberPlayer =pTeam->GetMemberPlayer( pMember->GetID() );
        if ( pMemberPlayer == NULL )
        { continue; }
		MapConfig::MapData* pMap =  theMapConfig.GetMapDataById(pMemberPlayer->GetMapID());
		if(!pMap)
			continue;
		if(pMap->GetMapType() == MapConfig::MT_SingleTeam)
		{
			MsgClearTeamMapAck msg;
			msg.Result = false;
			GettheServer().SendMsgToSingle( &msg, this );
			return;
		}
	}
	//发送命令道Center去
	GS2CSClearTeamMapReq msg;
	msg.TeamID = GetTeamID();
	msg.PlayerID = GetDBCharacterID();
	GettheServer().SendMsgToCenterServer( &msg );
}

void GamePlayer::OnMsgAskGetSalary( Msg* pMsg )
{
	MsgAskGetSalary* pAsk = ( MsgAskGetSalary* )pMsg;
	if ( !pAsk )
		return;

	if ( gCharInfoServer.otherdata.rankTitle.bGetSalary )
	{
		//已经领取了奖励
		MsgShowCenterInfo msg;
		msg.ID = eText_GetSalary_CD;
		GettheServer().SendMsgToSingle( &msg, this );
		return;
	}

	RankTitleConfig::RankTitleVector& vecTitle = theRankTitleConfig.GetRankTitleVec();
	int nShowCount = theRankTitleConfig.GetShowCount();

	short shCurId = gCharInfoServer.otherdata.rankTitle.shCurRankTitleId;

	if ( shCurId < 0 || shCurId >= /*vecTitle.size()*/nShowCount )
		return;

	//安远将军之前给绑银，之后给银币
	if ( shCurId < RankTitleConfig::ED_AnYuan )
		OperateJiaoZi( EOT_Add, vecTitle[ shCurId ].nCurSalary, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Unkown);
	else
		OperateMoney( EOT_Add, vecTitle[ shCurId ].nCurSalary, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Unkown);

	gCharInfoServer.otherdata.rankTitle.bGetSalary = 1;

	MsgAskGetSalaryAck msg;
	msg.bGet = gCharInfoServer.otherdata.rankTitle.bGetSalary;
	GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnAskAdvancement( Msg* pMsg )
{
	MsgAskAdvancement* pAck = ( MsgAskAdvancement* )pMsg;
	if ( !pAck )
		return;

	short shCurId = gCharInfoServer.otherdata.rankTitle.shCurRankTitleId;
	if ( shCurId + 1 != pAck->shTitleId )
		return;

	RankTitleConfig::RankTitleVector& vecTitle = theRankTitleConfig.GetRankTitleVec();
	int nShowCount = theRankTitleConfig.GetShowCount();

	if ( pAck->shTitleId < 0 || pAck->shTitleId >= /*vecTitle.size()*/nShowCount )
		return;

	MsgAskAdvancementAck msg;

	if ( GetHonour() < vecTitle[pAck->shTitleId].nNeedHonour || GetJiaoZiMoney() < vecTitle[pAck->shTitleId].nNeedMoney )
	{
		GettheServer().SendMsgToSingle( &msg, this );
		return;
	}

	OperateHonour( EOT_Sub, vecTitle[pAck->shTitleId].nNeedHonour, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Unkown );
	OperateJiaoZi( EOT_Sub, vecTitle[pAck->shTitleId].nNeedMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Unkown);

	gCharInfoServer.otherdata.rankTitle.shCurRankTitleId += 1;

	if ( shCurId >= 0 && shCurId < vecTitle.size() )
	{
		if (_buffManager.ClearBuffByBuffIdLevel( vecTitle[shCurId].nBuffId, vecTitle[shCurId].nBuffLevel ))
			OnBuffStatusChanged( true );
	}

	if ( shCurId + 1 >= 0 && shCurId + 1 < vecTitle.size() )
	{
		if ( ApplyBufferStatus( vecTitle[shCurId+1].nBuffId, vecTitle[shCurId+1].nBuffLevel, GetID(), SCharBuff::StatusEventType_Other, 0) == GLR_Success )
			OnBuffStatusChanged( true );
	}

	msg.bResult = true;
	msg.shCurTitleId = gCharInfoServer.otherdata.rankTitle.shCurRankTitleId;
	GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnMsgReConnect ( Msg* pMsg )
{
	MsgReConnect* pReConnect = static_cast<MsgReConnect*>( pMsg );
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID(pReConnect->header.stID);
	if(pChar&&pChar->IsPlayer())
	{//
		GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
		if (pPlayer->IsDead())
		{
			MsgTellReliveBuff msgBuff;
			msgBuff.header.stID = pReConnect->header.stID;
			msgBuff.byBuff = pPlayer->GetReliveBuff();
			pPlayer->SendMessageToClient(&msgBuff);

			MsgSawSomeoneDead msg;
			msg.header.stID = pReConnect->header.stID;
			msg.shReliveCnt = pPlayer->gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount;
			GettheServer().SendMsgToView( &msg, pPlayer->GetID(), false );

			MsgReconnectResetState mrrs;
			mrrs.header.stID = pReConnect->header.stID;
			mrrs.reset_state = MsgReconnectResetState::eResetState_death;
			pPlayer->SendMessageToClient(&mrrs);
		}
		else
			FlyToMapReq( pPlayer->GetMapID(), pPlayer->GetFloatX(), pPlayer->GetFloatY() , 0.0f );
	}
}
void GamePlayer::OnLoadCampBattleData( Msg* pMsg )
{
	//读取到数据库的数据后
	bool IStrue = false;
}
void GamePlayer::OnMsgAskHuntingList( Msg* pMsg )
{
	MsgHuntingAskForList* pList = (MsgHuntingAskForList*)pMsg;
	if ( !pList )
		return;

	theHuntingQuestManager.SendQuestList( this );
}

void GamePlayer::OnMsgHuntingReFresh( Msg* pMsg )
{
	MsgReFreshHunting* pFresh = (MsgReFreshHunting*)pMsg;
	if ( !pFresh )
		return;

	bool bCanFresh = true;
	switch ( pFresh->eType )
	{
	case MsgReFreshHunting::eFreshType_Free:
		{
			DWORD dwCurTime = HQ_TimeGetTime();
			DWORD dwLastTime = gCharInfoServer.otherdata.sHunting.dFreeRefreshTime;

			DWORD leftTime = 0;

			if ( dwCurTime >= dwLastTime )
				leftTime = ( dwCurTime - dwLastTime ) / 1000;
			else
				leftTime = ( dwLastTime - dwCurTime ) / 1000;

			if ( leftTime < theHuntingQuestConfig.GetFreshTime() )
				bCanFresh = false;
			else
			{
				gCharInfoServer.otherdata.sHunting.dFreeRefreshTime = dwCurTime;
			}
		}
		break;
	case MsgReFreshHunting::eFreshType_Gold:
		{
			if ( GetJinPiao() < theHuntingQuestConfig.GetFreshGold() )
				bCanFresh = false;
			else
				OperateJinPiao( EOT_Sub, theHuntingQuestConfig.GetFreshGold(), __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Unkown );
		}
		break;
	case MsgReFreshHunting::eFreshType_Money:
		{
			if ( GetMoney() < theHuntingQuestConfig.GetFreshMoney() )
				bCanFresh = false;
			else
				OperateMoney( EOT_Sub, theHuntingQuestConfig.GetFreshMoney(), true, __FUNCTION__, __LINE__, ePlayerMoneySourceType_Unkown );
		}
		break;
	default:
		return;
	}

	if ( !bCanFresh )
		return;

	theHuntingQuestManager.ReFreshQuest( this );
	theHuntingQuestManager.SendQuestList( this );
}

void GamePlayer::OnMsgAcceptHuntingQuest( Msg* pMsg )
{
	MsgHuntingAcceptQuest* pQuest = (MsgHuntingAcceptQuest*)pMsg;
	if ( !pQuest )
		return;

	theHuntingQuestManager.AcceptQuest( pQuest->nId, this );
}
void GamePlayer::OnMsgFlyToPositionAck( Msg* pMsg )
{
	MsgFlyToPositionAck* pAck = (MsgFlyToPositionAck*)pMsg;
	if ( !pAck )
		return;
	if(IsOpenStall())
	{
		return;
	}
	if ( HaveProtectChar() )
	{
		MsgShowCenterInfo msg;
		msg.ID = eText_YaBiao_Flytomap;
		SendMessageToClient( &msg );
		return;
	}
	MapConfig::MapData* pMapData =  theMapConfig.GetMapDataById(pAck->MapID);
	if(!pMapData || pMapData->IsEctypeMap())
		return;
	FlyToMapReq(pAck->MapID,pAck->Pos_X,pAck->Pos_Y,0);
}
void GamePlayer::OnMsgGetThreeDayItem( Msg* pMsg )
{
	MsgGetThreeDayItem * pAck = (MsgGetThreeDayItem*)pMsg;
	if ( !pAck )
		return;
	UpdataThreeDayInfo();
}
void GamePlayer::OnMsgUpdateYuanBaoDataReq ( Msg* pMsg )
{
	MsgUpdateYuanBaoDataReq * pAck = (MsgUpdateYuanBaoDataReq*)pMsg;
	if ( !pAck )
		return;
	unsigned int OnlyID = pAck->ChangeYuanBaoStatesValue;//玩家需要获取奖励的值
	//1.判断玩家是否可以获取奖励
	if(!YuanBaoTotleConfig::Instance().IsCanGetReward(GetYuanBaoTotle(),GetYuanBaoStates(),OnlyID))
		return;
	//2.可以获取了 我们修改gameserver里玩家的数据
	unsigned int NowPlayerStates = OnlyID | (GetYuanBaoStates()==0?1:GetYuanBaoStates());
	//SetYuanBaoStates(NowPlayerStates);
	//3.发送数据修改到数据库去
	GS2DBUpdateYuanBaoData msgDB;
	msgDB.AccountID = GetAccountID();
	msgDB.States = NowPlayerStates;
	msgDB.header.stID     = GetID();
	GettheDBCon().SendMsg( &msgDB,GetLifeCode());
}
void GamePlayer::OnDB2GSUpdateYuanBaoData( Msg* pMsg )
{
	//DB回馈的消息
	DB2GSUpdateYuanBaoData * pAck = (DB2GSUpdateYuanBaoData*)pMsg;
	if ( !pAck )
		return;
	if(pAck->result)
	{
		//发送奖励到背包 或者到邮件
		//1.创建一个物品
		unsigned int OnlyValue = pAck->States ^ (GetYuanBaoStates()==0?1:GetYuanBaoStates());
		SetYuanBaoStates(pAck->States);
		OnceYuanBaoReward * pInfo = YuanBaoTotleConfig::Instance().GetInfoByOnlyValue(OnlyValue);
		if(pInfo)
		{
			unsigned int ItemID = pInfo->LastItemID;
			if(GetNullItemCount(BT_NormalItemBag) >=1)
			{
				//直接放入到背包
				AddItem(ItemID,1,EIGS_UnKnow,true,NULL);
			}
			else
			{
				//发送邮件
				GS2CSSendMailReq xReq;
				xReq.charDbId = RelationDefine::InitID;
				xReq.mail.type  = SMail::EMT_System;
				xReq.mail.state = SMail::EMS_NotOpen;
				xReq.mail.sendTime = TimeEx::GetNowTime();        
				// 发信人
				xReq.mail.owners[EM_FromIndex].charDbId = 0;
				sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
				// 收件人
				xReq.mail.owners[EM_ToIndex].charDbId = GetDBCharacterID();	
				HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetCharInfo().baseinfo.aptotic.szCharacterName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
				//内容
				sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_YuanBaoStates_Context ) );
				//标题
				sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_YuanBaoStates_Title ) );
				SCharItem item;
				if(theRunTimeData.CreateItem(ItemID, 1,HelperFunc::CreateID(),item))
				{
					xReq.mail.accessory.type = SMail::EAT_Item;
					memcpy( &xReq.mail.accessory.content, &item, sizeof(SCharItem)); 
				}
				GettheServer().SendCenterServerMsg( &xReq );
			}
		}
		//发送命令到客户端去 修改已经改变的值
		MsgUpdateYuanBaoData msg;
		msg.dwAccountYuanBaoTotle = GetYuanBaoTotle();
		msg.dwAccountYuanBaoStates = GetYuanBaoStates();
		SendMessageToClient(&msg);
		return;
	}
}
void GamePlayer::OnMsgMountMoveStar( Msg* pMsg )
{
	MsgMountMoveStar * pAck = (MsgMountMoveStar*)pMsg;
	if ( !pAck )
		return;
	__int64 OldMountID = pAck->OldMountID;
	__int64 NewMountID = pAck->NewMountID;
	if(OldMountID ==0 || NewMountID == 0)
		return;
	SMountItem* pOldMount = _mountManager.GetMountByGuid(OldMountID);
	SMountItem* pNewMount = _mountManager.GetMountByGuid(NewMountID);
	if(!pOldMount || !pNewMount)
		return;
	if( _mountManager.GetActiveMount() == pOldMount || _mountManager.GetActiveMount() == pNewMount)
		return;
	//同一坐骑不可以转星
	if(pOldMount == pNewMount)
		return;
	//不可以强化的坐骑不可以
	const MountStrengthenData* pDataOld = theMountStrengthenConfig.GetMountStrengthenData(pOldMount->baseInfo.id);
	if (!pDataOld)
		return;
	const MountStrengthenData* pDataNew = theMountStrengthenConfig.GetMountStrengthenData(pNewMount->baseInfo.id);
	if (!pDataNew)
		return;
	//只可以高等级转移到低等级
	if(pOldMount->baseInfo.level <= pNewMount->baseInfo.level)
		return;
	MountMoveStatStruct* pConfig = MountMoveStarConfig::Instance().GetConfigStruct(pOldMount->baseInfo.level);
	if(!pConfig)
		return;
	//1.设置完毕后 我们开始处理下 扣除金钱
	if(GetJiaoZiMoney() < pConfig->Money)
		return;
	//GetItemCount
	if(!pConfig->ItemMap.empty())
	{
		std::map<unsigned int,unsigned int>::iterator Iter = pConfig->ItemMap.begin();
		for(;Iter != pConfig->ItemMap.end();++Iter)
		{
			unsigned int ItemID = Iter->first;
			unsigned int ItemSum = Iter->second;
			if(GetItemCount(ItemID) < ItemSum)
				return;
		}
	}
	//2.材料足够 我们开始扣除材料和金钱
	OperateJiaoZi( EOT_Sub, pConfig->Money, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_MountStreng);
	if(!pConfig->ItemMap.empty())
	{
		std::map<unsigned int,unsigned int>::iterator Iter = pConfig->ItemMap.begin();
		for(;Iter != pConfig->ItemMap.end();++Iter)
		{
			unsigned int ItemID = Iter->first;
			unsigned int ItemSum = Iter->second;
			RemoveItem(ItemID,ItemSum);
		}
	}
	//3.材料扣除完毕后 我们强化坐骑 需要判断几率
	unsigned int LoseLevel = pConfig->GetDowmStar();
	unsigned int OleMountLevel = pOldMount->baseInfo.level;
	OleMountLevel -= LoseLevel;
	ChangeMountStarLevel(OldMountID,0,true);
	ChangeMountStarLevel(NewMountID,OleMountLevel,true);
}
void GamePlayer::OnDB2GSUpdatePlayerPoint( Msg* pMsg )
{
	DB2GSUpdatePlayerPoint * pAck = (DB2GSUpdatePlayerPoint*)pMsg;
	if ( !pAck )
		return;
	//提示玩家 操作数据库点数已经成功 转发到客户端去 提示玩家 
	MsgUpdatePlayerPoint msg;
	msg.PlayerID = pAck->PlayerID;
	msg.ID = pAck->ID;
	msg.States = pAck->States;
	msg.Op = pAck->Op;
	msg.Value = pAck->Value;
	msg.ChangeValue = pAck->ChangeValue;
	SendMessageToClient(&msg);
}
void GamePlayer::OnMsgLeaveExpReq( Msg* pMsg )
{
	SendLeaveExpInfo();//将数据发送到客户端去
}
void GamePlayer::OnMsgGetLeaveExpReq( Msg* pMsg )
{
	GetLeaveExp();
}
#pragma warning( pop )