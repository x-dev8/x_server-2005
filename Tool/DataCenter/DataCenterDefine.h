#pragma once

#include "GlobalDef.h"
#include "GuildDefine.h"

namespace DataCenterDefine
{
	//个人排行榜
	//等级排行榜|财富排行榜|荣誉排行榜|军功排行榜|功勋排行榜|杀敌排行榜|魅力排行榜|红名排行榜
	struct sPersonalRank
	{
		sPersonalRank()
		{
			memset(this,0,sizeof(sPersonalRank));
		}
		uint16 usRank;					//排行
		char   chName[dr_MaxPlayerName];//玩家名字
		uint32 ulValue;					//排行数值
		uint16 usCountryID;				//国家ID
		char   chGuildName[GuildDefine::MaxNameLength];			//工会名字
		uint16 usReward;				//奖励
	};
	//军团排行榜
	struct sGuildRank
	{
		sGuildRank()
		{
			memset(this,0,sizeof(sGuildRank));
		}
		uint16 usRank;					//排行
		char   chGuildName[GuildDefine::MaxNameLength];			//工会名字
		uint32 ulGuildPower;			//军团实力
		uint16 usGuildMemberCount;		//军团成员数量
		uint16 usGuildLevel;			//军团等级
		uint16 usCountryID;				//所属国家
	};
	//国家排行
	struct sCountryRank
	{
		sCountryRank()
		{
			memset(this,0,sizeof(sCountryRank));
		}
		uint16 usRank;										//排行
		uint16 usCountryID;									//国家ID
		char   chKingName[dr_MaxPlayerName];				//国王名字
		uint32 ulValue;										//排行数值
	};

	//装备评分排行
	struct sEquipScore
	{
		sEquipScore()
		{
			memset(this,0,sizeof(sEquipScore));
		}
		uint16 usRank;					//排行
		char   chName[dr_MaxPlayerName];//玩家名字
		uint32 score;					//装备评分
		//uint16 usCountryID;				//国家ID
		//uint16 usLV;					//玩家等级
		//char   chGuildName[GuildDefine::MaxNameLength];			//工会名字
		uint16 usReward;				//奖励
		SCharItem sItem;				//物品结构
	};

	struct sGuildCampBattlePoint
	{
		sGuildCampBattlePoint()
		{
			memset(this,0,sizeof(sGuildCampBattlePoint));
		}
		char   chGuildName[GuildDefine::MaxNameLength];			//工会名字
		unsigned int Point;
		uint32 usRank;					//排行
		uint16 usCountryID;				//国家ID
		uint16 usGuildMemberCount;		//军团成员数量
		uint16 usGuildLevel;			//军团等级
	};
}