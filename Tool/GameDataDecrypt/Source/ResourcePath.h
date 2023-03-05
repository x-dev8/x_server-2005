/********************************************************************
	Filename: 	ResourcePath.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_RESOURCEPATH_H__
#define __COMMON_RESOURCEPATH_H__

#include "MeRTLibs.h"

//////////////////////////////////////////////////////////////////////////
// Data
#define TITLE_FILEPATH  "..\\Data\\Config\\Title.config"
#define RECIPE_FILEPATH "..\\Data\\Config\\Recipe.config"
#define OUTPUT_DIRECTORY                   "..\\Output"
#define SYSTEM_DIRECTORY                   "..\\System"
#define DATACHUNK_FILEPATH                 "\\SysVarChunk\\"
#define WORLDMAPCONFIG_FILEPATH            "..\\Data\\Config\\Map.config"
#define SOFTKEYBOARD_CONFIGUREFILENAME     "..\\Data\\Config\\SoftKeyboard.xml"
#define PLAYER_LOGDIRECTORY_FORMAT             ".\\%s\\PlayerGameLog_%u_%u"
#define PLAYER_SHOPPINGLOG_LOGDIRECTORY_FORMAT ".\\%s\\PlayerShoppingLog_%u_%u"
#define MSSQL_LOGDIRECTORY_FORMAT              ".\\%s\\MsSqlLog"
#define GAMESERVER_CONFIGFILENAME              ".\\Data\\GameServer.ini"
#define GAMESERVER_MAPCONFIG_FILEPATH          ".\\Data\\Config\\Map.config"
#define EXPSTAGE_FILEPATH                      "..\\Data\\Config\\LevelExperience.config"
#define STRINGSLK_FILEPATH                     "..\\Data\\Config\\String.config"
#define SHOPCENTER_FILEPATH                    "..\\Data\\Config\\TradeCenter.config"
//#define RELIVEPOS_FILEPATH                     "..\\Data\\Config\\RelivePos.slk"
#define NPC_FILEPATH                           "..\\Data\\Config\\Npc.config"
#define PARAMFORMULA_FILEPATH                  "..\\Data\\Config\\ParamFormula.slk"
#define PARAMDESC_FILEPATH                     "..\\Data\\Config\\ParamDesc.slk"
#define GAMELOGICCONST_FILEPATH                "..\\Data\\Config\\GameLogicConst.slk"
#define COMMONDROPITEM_FILEPATH                "..\\Data\\Config\\DropItemCommon.config"
#define MONSTERDROPITEM_FILEPATH               "..\\Data\\Config\\DropItemMonster.config"
#define TASKDROPITEM_FILEPATH                  "..\\Data\\Quest\\Server\\QuestMonsterDropItem.config"
// Add Begin Script相关的四张SLK表 [11/25/2010 pengbo.yang]
#define LEVELUPSCRIPTSLK_FILEPATH              "..\\Data\\Config\\ScriptLevelUp.slk"
#define USEITEMSCRIPTSLK_FILEPATH              "..\\Data\\Config\\ScriptUseItem.slk"
#define TIMESCRIPTSLK_FILEPATH                 "..\\Data\\Config\\ScriptTime.slk"
#define DELAYTIMESCRIPTSLK_FILEPATH            "..\\Data\\Config\\ScriptDelayTime.slk"
// Script四张SLK表整合为一个Config文件
#define  SCRIPTCONFIG_FILEPATH                 "..\\Data\\Config\\Script.config"
// Add End [11/25/2010 pengbo.yang]
#define QUESTS_FILEPATH                        "..\\Data\\Quest"
#define QUESTRAND_FILEPATH                     "Server\\RandQuest.config"
#define QUESTS_SCRIPT_FILEPATH_FORMAT          "..\\Data\\Script\\Quest\\Quest%04ld.script"
#define CANCELQUESTS_SCRIPT_FILEPATH_FORMAT    "..\\Data\\Script\\Quest\\DelQuest%04ld.script"
#define SCRIPT_PLAYERONLINE_FILEPATH           "..\\Data\\Script\\PlayerOnline.script"
#define SCRIPT_BANGUILDMEMBER_FILEPATH         "..\\Data\\Script\\PlayerOnline.script"
#define SCRIPT_PLAYEROFFLINE_FILEPATH          "..\\Data\\Script\\BanSwornMember.script"
#define SCRIPT_CREATEPLAYER_FILEPATH           "..\\Data\\Script\\CreatePlayer.script"
#define SCRIPT_PLAYERDEAD_FILEPATH		       "..\\Data\\Script\\PlayerDead.script"
#define SCRIPT_GRAPHICCODECHECKRIGHT_FILEPATH  "..\\Data\\Script\\GraphicCodeCheckRight.script"
#define SCRIPT_CHALLENGE_FILEPATH              "..\\Data\\Script\\Challenge.script"
#define SCRIPT_MARRIAGE_FILEPATH               "..\\Data\\Script\\Marriage.script"
#define SCRIPT_TEACHERSTUDENT_FILEPATH         "..\\Data\\Script\\TeacherStudent.script"
#define SCRIPT_DELAYTIME_FILEPATH              "..\\Data\\Script\\DelayTime.script"
#define SCRIPT_PKBATTLE_FILEPATH               "..\\Data\\Script\\PKBattle.script"
#define SCRIPT_TEAMBATTLE_FILEPATH             "..\\Data\\Script\\TeamBattle.script"
#define SCRIPT_LEAVEGUILD_FILEPATH             "..\\Data\\Script\\LeaveGuild.script"

#define MONSTERCONFIG_FILEPATH                 "..\\Data\\Config\\Monster.config"
#define MONSTERSOUNDCFG_FILEPATH               "..\\Data\\Config\\CreatureSound.config"
#define MOUNTCONFIG_FILEPATH                   "..\\Data\\Config\\Mount.config"
#define EQUIPMENTRANDOM_FILEPATH               "..\\Data\\Config\\EquipmentRandom.config"
#define TRAFFIC_FILEPATH                       "..\\Data\\Config\\Traffic.config"
#define ACHIEVECONFIG_FILEPATH                 "..\\Data\\Config\\Achieve.config"

#define SOFTKEYBOARD_CONFIGUREFILENAME         "..\\Data\\Config\\SoftKeyboard.xml"
#define UNDUEWORD_FILEPATH                     "..\\Data\\Config\\FilterString.config"
#define SPECIALCHARFILTER_FILEPATH             "..\\Data\\Config\\SpecialCharFilter.config"
#define ITEM_SYMBOL_FILEPATH                   "..\\Data\\Config\\ItemSymbols.config"
#define CHARACTERBASESECONDATTRIBUTE_FILEPATH  "..\\Data\\Config\\CharacterBaseSecondAttribute.config"
#define PARAMMODULUS_FILEPATH                  "..\\Data\\Config\\ArmsParamModulus.config"
#define NPCROUTE_FILEPATH                      "..\\Data\\Config\\NpcRoute.config"
#define AVATARSYSTEMSETTING_FILEPATH           "..\\Data\\Config\\AvatarSystemSetting.config"
#define BINDATA_FILEPATH                       "..\\Data\\Config\\Data.config"
#define EVENT_FILEPATH                         "..\\Data\\Config\\Event.config"
#define LUCKREWARD_FILEPATH                    "..\\Data\\Config\\Luck.config"
#define LUCKREWARDRAND_FILEPATH                "..\\Data\\Config\\Luck.config"
#define SPLITITEM_FILEPATH                     "..\\Data\\Config\\SplitItem.config"
#define TREASUREBOX_FILEPATH                   "..\\Data\\Config\\TreasureBox.config"
#define GAMESTAGE_FILEPATH                     "..\\Data\\Config\\GameStage.config"
#define ARMOURELEMENTS_FILEPATH                "..\\Data\\Config\\ArmourElements.config"
#define EQUIPUPGRADE_FILEPATH                  "..\\Data\\Config\\EquipUpgrade.config"
#define SUITOPERATE_FILEPATH                   "..\\Data\\Config\\SuitOperate.config"
#define ONLINEREWARD_FILEPATH                  "..\\Data\\Config\\OnLineTimeReward.config"
#define KILLMONSTERCOUNT_FILEPATH              "..\\Data\\Config\\KillMonsterCount.config"
#define RELATIONCONFIG_FILEPATH                "..\\Data\\Config\\Relation.config"
#define ITEMCOMPOSECONFIG_FILEPATH             "..\\Data\\Config\\ItemCompose.config"
#define ITEMCOMPOSECONFIG_FILEPATH2            "..\\Data\\Config\\ItemCompose2.config"
#define EXPACTION_FILEPATH                     "..\\Data\\Config\\ExpAction.config"
#define COUNTRY_CONFIG                         "..\\Data\\Config\\Country.config"
#define GUIDEQUEST_FILEPATH                    "..\\Data\\Config\\GuideQuest.config"
#define CAMPGUILDBATTLE_FILEPATH               "..\\Data\\Config\\GuildBattle.config"

#define GIFTITEM_CONFIG                        "..\\Data\\Config\\GiftItem.config"
#define GUILDSETTING_FILEPATH                  "..\\Data\\Config\\GuildSetting.config"
#define REWARDPROFESSIONITEM_CONFIG            "..\\Data\\Config\\RewardProfessionItem.config"

#define STAGEROOTDIRECTORY                     "..\\Data\\World"
#define STARLEVELUP_FILEPATH                   "..\\Data\\Config\\StarLevelUp.config"
#define GAMESERVER_COMMON_CONFIGNAME           "Setting-GameCommon.config"
#define GATESERVER_COMMON_CONFIGNAME           "Setting-GateCommon.Config"
#define GRAPHICCODE_BACKGROUNDDIR              "..\\Data\\GraphicCode\\Background\\"
#define GRAPHICCODE_NUMBERPICDIR               "..\\Data\\GraphicCode\\Pics\\"
#define ITEMDETAILDIRECTORY                     "..\\Data\\Config\\Item"

#define NETSETTING_FILEPATH                    "..\\Setting\\Setting-Net.config"//////////////////////////////////////////////////////////////////////////
// CenterServer
#define CENTERSERVER_PERFORMANCELOG_FILEPATH "..\\Output\\Performance-Center.log"

//////////////////////////////////////////////////////////////////////////
// LoginServer

//////////////////////////////////////////////////////////////////////////
// DatabaseServer
#define FILEDATABASE_DIRECTORY  "../FileDatabase"
#define FILEDATABASE_DATA_FILENAME  "AllUnSaveChars.save"
#define DATABASE_PERFORMANCELOG_FILEPATH "..\\Output\\Performance-Database.log"

//////////////////////////////////////////////////////////////////////////
// AccountServer

//////////////////////////////////////////////////////////////////////////
// GateServer
#define GATESERVER_PERFORMANCELOG_FILEPATH "..\\Output\\Performance-Gate%d%s.log"

//////////////////////////////////////////////////////////////////////////
// GameServer
#define QUESTS_FILE_FOMAT                      "%d.quest"
#define SCRIPT_ROOTDIRECTORY                   "..\\"
#define GAMESERVER_PERFORMANCELOG_FILEPATH     "..\\Output\\Performance-%s.log"

//////////////////////////////////////////////////////////////////////////
// CharacterServer
#define LOGINGAMESERVER_PERFORMANCELOG_FILEPATH "..\\Output\\Performance-CharacterServer.log"

//////////////////////////////////////////////////////////////////////////
// Robot
#define QUESTS_ROBOT_FILEPATH "..\\..\\Data\\Quest\\Quest.xml"

//////////////////////////////////////////////////////////////////////////
// BinData
#define OUTPUT_BINDATAPATH    "..\\Data\\Config\\Data.config-Output"
#define BINDATA_ROOTDIRECTORY "..\\Data\\Config\\"


//////////////////////////////////////////////////////////////////////////

#endif // __COMMON_RESOURCEPATH_H__
