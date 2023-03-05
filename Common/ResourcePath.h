/********************************************************************
	Filename: 	ResourcePath.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_RESOURCEPATH_H__
#define __COMMON_RESOURCEPATH_H__

#include "MeRTLibs.h"

//////////////////////////////////////////////////////////////////////////
#define OUTPUT_DIRECTORY                   		"..\\Output"
#define SYSTEM_DIRECTORY                   		"..\\System"
#define DATACHUNK_FILEPATH                 		"\\SysVarChunk\\"


#define STAGEROOTDIRECTORY                     	"..\\Data\\World"
#define GRAPHICCODE_BACKGROUNDDIR              	"..\\Data\\GraphicCode\\Background\\"
#define GRAPHICCODE_NUMBERPICDIR               	"..\\Data\\GraphicCode\\Pics\\"
#define ITEMDETAILDIRECTORY                    	"..\\Data\\Config\\Item"

#define SOFTKEYBOARD_CONFIGUREFILENAME     		"..\\Data\\Config\\SoftKeyboard.xml"
#define WORLDMAPCONFIG_FILEPATH                	"..\\Data\\Config\\Map.config"
#define GAMESERVER_MAPCONFIG_FILEPATH          	".\\Data\\Config\\Map.config"
#define STRINGSLK_FILEPATH                     	"..\\Data\\Config\\String.config"
//#define RELIVEPOS_FILEPATH                     "..\\Data\\Config\\RelivePos.slk"

//////////////////////////////////////////////////////////////////////////
//掉落
#define COMMONDROPITEM_FILEPATH                	"..\\Data\\Config\\DropItemCommon.config"
#define MONSTERDROPITEM_FILEPATH               	"..\\Data\\Config\\DropItemMonster.config"
#define TASKDROPITEM_FILEPATH                  	"..\\Data\\Quest\\Server\\QuestMonsterDropItem.config"

//主将
#define ITEMHERO_FILEPATH						"..\\Data\\Config\\SanGuoLord.config"
#define ITEMHERO_STRINGPATH						"..\\Data\\Config\\SanGuoLord.string"

#define TPHJ_FILEPATH							"..\\Data\\Config\\tphj.config"
#define SPECIALTASK_FILEPATH					"..\\Data\\Config\\SpecialTask.config"

//////////////////////////////////////////////////////////////////////
//任务脚本相关
// Script四张SLK表整合为一个Config文件 Add Begin Script相关的四张SLK表 [11/25/2010 pengbo.yang]
#define LEVELUPSCRIPTSLK_FILEPATH              "..\\Data\\Config\\ScriptLevelUp.slk"
#define USEITEMSCRIPTSLK_FILEPATH              "..\\Data\\Config\\ScriptUseItem.slk"
#define TIMESCRIPTSLK_FILEPATH                 "..\\Data\\Config\\ScriptTime.slk"
#define DELAYTIMESCRIPTSLK_FILEPATH            "..\\Data\\Config\\ScriptDelayTime.slk"
#define SCRIPTCONFIG_FILEPATH                  "..\\Data\\Config\\Script.config"
#define QUESTS_FILE_FOMAT                      "%d.quest"
#define QUESTS_FILEPATH                        "..\\Data\\Quest"
#define QUESTRAND_FILEPATH                     "Server\\RandQuest.config"
#define QUESTS_SCRIPT_FILEPATH_FORMAT          "..\\Data\\Script\\Quest\\Quest%04ld.script"
#define CANCELQUESTS_SCRIPT_FILEPATH_FORMAT    "..\\Data\\Script\\Quest\\DelQuest%04ld.script"
#define SCRIPT_PLAYERONLINE_FILEPATH           "..\\Data\\Script\\PlayerOnline.script"
#define SCRIPT_BANGUILDMEMBER_FILEPATH         "..\\Data\\Script\\BanSwornMember.script"
#define SCRIPT_PLAYEROFFLINE_FILEPATH          "..\\Data\\Script\\PlayerOffline.script"
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
#define SCRIPT_KILLCHAR_FILEPATH			   "..\\Data\\Script\\KillPlayer.script"

//////////////////////////////////////////////////////////////////////////

#define GAMESERVER_CONFIGFILENAME              ".\\Data\\GameServer.ini"
#define GAMESERVER_COMMON_CONFIGNAME           "Setting-GameCommon.config"
#define GATESERVER_COMMON_CONFIGNAME           "Setting-GateCommon.Config"
#define NETSETTING_FILEPATH                    "..\\Setting\\Setting-Net.config"

// CenterServer
#define CENTERSERVER_PERFORMANCELOG_FILEPATH   "..\\Output\\Performance-Center.log"
// CenterServer
#define CENTERLOGIN_PERFORMANCELOG_FILEPATH   "..\\Output\\Performance-CenterLogin.log"



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
#define SCRIPT_ROOTDIRECTORY                   "..\\"
#define GAMESERVER_PERFORMANCELOG_FILEPATH     "..\\Output\\Performance-%s.log"
#define GAMESERVER_USERLOG                     "..\\Output\\UserLog_%s"
#define PLAYER_LOGDIRECTORY_FORMAT             ".\\%s\\PlayerGameLog_%u_%u"
#define PLAYER_SHOPPINGLOG_LOGDIRECTORY_FORMAT ".\\%s\\PlayerShoppingLog_%u_%u"
#define MSSQL_LOGDIRECTORY_FORMAT              ".\\%s\\MsSqlLog"

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
//config
#define TITLE_FILEPATH							"..\\Data\\Config\\Title.config"

#define RECIPE_FILEPATH							"..\\Data\\Config\\Recipe.config"

#define MONSTERCONFIG_FILEPATH                 	"..\\Data\\Config\\Monster.config"

#define PETCONFIG_FILEPATH                     	"..\\Data\\Config\\Pet.config"

#define MONSTERSOUNDCFG_FILEPATH               	"..\\Data\\Config\\CreatureSound.config"

#define MOUNTCONFIG_FILEPATH                   	"..\\Data\\Config\\Mount.config"

#define EQUIPMENTRANDOM_FILEPATH               	"..\\Data\\Config\\EquipmentRandom.config"

#define EQUIPQUALITYINTENSITY_FILEPATH         	"..\\Data\\Config\\EquipQualityIntensity.config"

#define EQUIPSTILETTO_FILEPATH				   	"..\\Data\\Config\\EquipStiletto.config"

#define EQUIPUNKNOWIDENTIFY_FILEPATH		   	"..\\Data\\Config\\EquipUnknowIdentify.config"

#define TRAFFIC_FILEPATH                       	"..\\Data\\Config\\Traffic.config"

#define ACHIEVECONFIG_FILEPATH                 	"..\\Data\\Config\\Achieve.config"

#define UNDUEWORD_FILEPATH                     	"..\\Data\\Config\\FilterString.config"

#define SPECIALCHARFILTER_FILEPATH             	"..\\Data\\Config\\SpecialCharFilter.config"

#define ITEM_SYMBOL_FILEPATH                   	"..\\Data\\Config\\ItemSymbols.config"

#define CHARACTERBASESECONDATTRIBUTE_FILEPATH  	"..\\Data\\Config\\CharacterBaseSecondAttribute.config"

#define PARAMMODULUS_FILEPATH                  	"..\\Data\\Config\\ArmsParamModulus.config"

#define NPC_FILEPATH                           	"..\\Data\\Config\\Npc.config"

#define NPCROUTE_FILEPATH                       "..\\Data\\Config\\NpcRoute.config"

#define AVATARSYSTEMSETTING_FILEPATH           	"..\\Data\\Config\\AvatarSystemSetting.config"

#define BINDATA_FILEPATH                       	"..\\Data\\Config\\Data.config"

#define EVENT_FILEPATH                         	"..\\Data\\Config\\Event.config"

#define LUCKREWARD_FILEPATH                    	"..\\Data\\Config\\Luck.config"

#define SPLITITEM_FILEPATH                     	"..\\Data\\Config\\SplitItem.config"

#define TREASUREBOX_FILEPATH                   	"..\\Data\\Config\\TreasureBox.config"

#define GAMESTAGE_FILEPATH                     	"..\\Data\\Config\\GameStage.config"

#define ARMOURELEMENTS_FILEPATH                	"..\\Data\\Config\\ArmourElements.config"

#define EQUIPUPGRADE_FILEPATH                  	"..\\Data\\Config\\EquipUpgrade.config"

#define SUITOPERATE_FILEPATH                   	"..\\Data\\Config\\SuitOperate.config"

#define ONLINEREWARD_FILEPATH                  	"..\\Data\\Config\\OnLineTimeReward.config"

#define KILLMONSTERCOUNT_FILEPATH              	"..\\Data\\Config\\KillMonsterCount.config"

#define RELATIONCONFIG_FILEPATH                	"..\\Data\\Config\\Relation.config"

#define ITEMCOMPOSECONFIG_FILEPATH             	"..\\Data\\Config\\ItemCompose.config"

#define ITEMCOMPOSECONFIG_FILEPATH2            	"..\\Data\\Config\\ItemCompose2.config"

#define EXPACTION_FILEPATH                     	"..\\Data\\Config\\ExpAction.config"

#define TIMEHANDEL_CONFIG					   	"..\\Data\\Config\\TimeHandle.config"

#define GUILDCAMPBATTLE_FILEPATH			   	"..\\Data\\Config\\GuildCampBattle.config"

#define COUNTRY_CONFIG                         	"..\\Data\\Config\\Country.config"

#define COUNTRY_REWARD							"..\\Data\\Config\\CountryReward.config"

#define GUIDEQUEST_FILEPATH                    	"..\\Data\\Config\\GuideQuest.config"

#define CAMPGUILDBATTLE_FILEPATH               	"..\\Data\\Config\\GuildBattle.config"

#define CAMPGUILDUNIONBATTLE_FILEPATH		   	"..\\Data\\Config\\GuildUnionBattle.config"

#define CAMPBATTLECLIENTINFO_FILEPATH		   	"..\\Data\\Config\\CampBattleClientInfo.config"

#define CAMPWORLDBATTLE_FILEPATH			   	"..\\Data\\Config\\WorldBattle.config"

#define CAMPKINGBATTLE_FILEPATH                	"..\\Data\\Config\\KingBattle.config"

#define CAMPDRAGONBATTLE_FILEPATH              	"..\\Data\\Config\\DragonBattle.config"

#define CAMPROSEFINCHBATTLE_FILEPATH           	"..\\Data\\Config\\RosefinchBattle.config"

#define TALISMANCONFIG_FILEPATH                	"..\\Data\\Config\\TalismanSetting.Config"

#define MONSTERGROUPCONFIG_FILEPATH            	"..\\Data\\Config\\MonsterGroup.Config"

#define GUILDSETTING_FILEPATH                  	"..\\Data\\Config\\GuildSetting.config"

#define GUILDMISSION_FILEPATH                  	"..\\Data\\Config\\GuildMission.config"

#define FAMILYSETTING_FILEPATH                  "..\\Data\\Config\\FamilySetting.config"

#define REWARDPROFESSIONITEM_CONFIG             "..\\Data\\Config\\RewardProfessionItem.config"

#define EXPSTAGE_FILEPATH                      	"..\\Data\\Config\\LevelExperience.config"

#define SHOPCENTER_FILEPATH                    	"..\\Data\\Config\\TradeCenter.config"
//等级封印配置文件
#define CENTERSERVER_LEVELLIMIT_CONFIG          "..\\Data\\Config\\LevelLimit.config"

#define MOUNTMOVESTAR_FILEPATH_CONFIG			"..\\Data\\Config\\MountMoveStar.config"

#define VARCLEARCONFIG_FILEPATH                	"..\\Data\\Config\\VarClear.config"

#define MONSTERSTATUS_FILEPATH                 	"..\\Data\\Config\\MonsterStatus.config"

#define PHYLECHASTEN_FILEPATH				   	"..\\Data\\Config\\PhyleSetting.config"

#define DAOXING_FILEPATH                       	"..\\Data\\Config\\Daoxing.config"

#define XINFACONFIG_FILEPATH                   	"..\\Data\\Config\\XinFa.config"

#define PETSETINGCONFIG_FILEPATH               	"..\\Data\\Config\\PetSetting.config"

#define STALLCONFIG_FILEPARTH				   	"..\\Data\\Config\\Stall.config"

#define PETDEFINECONFIG_FILEPATH			    "..\\Data\\Config\\PetDefine.config"

#define STARLEVELUP_FILEPATH                    "..\\Data\\Config\\StarLevelUp.config"

#define POCKETSHOP_FILEPATH						"..\\Data\\Config\\pocketshop.config"

#define MOUNTSTRENGTHEN_FILEPATH				"..\\Data\\Config\\MountStrengthen.config"

#define RAISECONFIG_FILEPATH					"..\\Data\\Config\\Raise.config"

#define COUNTRYQUESTFLYMAP						"..\\Data\\Config\\CountryQuestFlyMap.config"

#define PKDEFINECONFIG_FILEPATH					"..\\Data\\Config\\PKDefine.config"

#define SUITDEFINECONFIG_FILEPATH   			"..\\Data\\Config\\SuitDefine.config"

#define EQUIPSCORERATIO_FILEPATH				"..\\Data\\Config\\EquipScoreRatio.config"

#define CARDICONDONFIG_FILEPATH					"..\\Data\\Config\\CardIcon.config"

#define CARDACHIEVECONFIG_FILEPATH				"..\\Data\\Config\\CardAchieve.config"

#define SEVENDAYSCONFIG_FILEPATH				"..\\Data\\Config\\SevenDays.config"

#define BROADCASTCONFIG_FILEPATH				"..\\Data\\Config\\broadcast.config"

#define EFFECTCHAR_FILEPATH		    			"..\\Data\\Config\\EffectChar.config"

#define RANKTITLECONFIG_FILEPATH				"..\\Data\\Config\\RankTitle.config"

#define CREATEMONSTERCONFIG_FILEPATH			"..\\Data\\Config\\CreateMonster.config"

#define QUESTENTRUSTCONFIG_FILEPATH				"..\\Data\\Config\\QuestEntrust.config"

#define HUNTINGQUESTCONFIG_FILEPATH				"..\\Data\\Config\\HuntingQuest.config"

#define GAMEGUILDGENERALBATTLE_FILEPATH			"..\\Data\\Config\\GameGuildGeneralBattle.config"

#define SOULCONFIG_FILEPATH						"..\\Data\\Config\\Soul.config"

#define THREEDAYCONFIGPATH						"..\\Data\\Config\\ThreeDay.config"

#define YUANBAOCONFIGPATH						"..\\Data\\Config\\YuanBaoTotle.config"

#define PETSPEAKPATH							"..\\Data\\Config\\PetSpeak.config"

#define TEXTHYBEROTHERPATH						"..\\Data\\Config\\TextHyberOther.config"


//////////////////////////////////////////////////////////////////////////
//资源配置文件类型--这里是记录可被支持的热加载--在增加的时候要考虑到centerserver 和 gameserver
enum eResourceCfgType
{
	eRCFGTYPE_SHOPCENTER,
	eRCFGTYPE_MOUNTSTRENGTHEN,
	eRCFGTYPE_STARLEVELUP,
	eRCFGTYPE_MAX
};
//这个数组的大小要和上面的eResourceCfgType是一一对应的,注意大小
static char* g_szResourceCfgPath[] = 
{
	SHOPCENTER_FILEPATH  ,			// 商城配置文件 这个gs不加载是center消息传过去的
	MOUNTSTRENGTHEN_FILEPATH ,		// 坐骑 强化
	STARLEVELUP_FILEPATH,			// 装备 升星
};
#endif // __COMMON_RESOURCEPATH_H__
