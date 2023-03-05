#pragma once

#include "GlobalDef.h"
#include "GuildDefine.h"

namespace DataCenterDefine
{
	//�������а�
	//�ȼ����а�|�Ƹ����а�|�������а�|�������а�|��ѫ���а�|ɱ�����а�|�������а�|�������а�
	struct sPersonalRank
	{
		sPersonalRank()
		{
			memset(this,0,sizeof(sPersonalRank));
		}
		uint16 usRank;					//����
		char   chName[dr_MaxPlayerName];//�������
		uint32 ulValue;					//������ֵ
		uint16 usCountryID;				//����ID
		char   chGuildName[GuildDefine::MaxNameLength];			//��������
		uint16 usReward;				//����
	};
	//�������а�
	struct sGuildRank
	{
		sGuildRank()
		{
			memset(this,0,sizeof(sGuildRank));
		}
		uint16 usRank;					//����
		char   chGuildName[GuildDefine::MaxNameLength];			//��������
		uint32 ulGuildPower;			//����ʵ��
		uint16 usGuildMemberCount;		//���ų�Ա����
		uint16 usGuildLevel;			//���ŵȼ�
		uint16 usCountryID;				//��������
	};
	//��������
	struct sCountryRank
	{
		sCountryRank()
		{
			memset(this,0,sizeof(sCountryRank));
		}
		uint16 usRank;										//����
		uint16 usCountryID;									//����ID
		char   chKingName[dr_MaxPlayerName];				//��������
		uint32 ulValue;										//������ֵ
	};

	//װ����������
	struct sEquipScore
	{
		sEquipScore()
		{
			memset(this,0,sizeof(sEquipScore));
		}
		uint16 usRank;					//����
		char   chName[dr_MaxPlayerName];//�������
		uint32 score;					//װ������
		//uint16 usCountryID;				//����ID
		//uint16 usLV;					//��ҵȼ�
		//char   chGuildName[GuildDefine::MaxNameLength];			//��������
		uint16 usReward;				//����
		SCharItem sItem;				//��Ʒ�ṹ
	};

	struct sGuildCampBattlePoint
	{
		sGuildCampBattlePoint()
		{
			memset(this,0,sizeof(sGuildCampBattlePoint));
		}
		char   chGuildName[GuildDefine::MaxNameLength];			//��������
		unsigned int Point;
		uint32 usRank;					//����
		uint16 usCountryID;				//����ID
		uint16 usGuildMemberCount;		//���ų�Ա����
		uint16 usGuildLevel;			//���ŵȼ�
	};
}