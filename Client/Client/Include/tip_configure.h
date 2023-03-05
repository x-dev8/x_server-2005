#ifndef AN_CONFIG_TIP_H_
#define AN_CONFIG_TIP_H_

//#include <Windows.h>
#include <string>
#include <map>

enum TipConfigure
{
	//---角色属性test_tip显示
	Tip_Configure_Name = 0,			//名字
	Tip_Configure_Job,				//职业
	Tip_Configure_Level,			//等级
	Tip_Configure_Title,			//称号
	Tip_Configure_Official,			//官制
	Tip_Configure_Guild,			//公会
	Tip_Configure_Distinction,		//声望
	Tip_Configure_Marry,			//配偶
	Tip_Configure_KillNum,			//击杀
	Tip_Configure_Credit,			//信誉
	Tip_Configure_Str,				//力量
	Tip_Configure_Con,				//体质
	Tip_Configure_Agi,				//敏捷
	Tip_Configure_Int,				//智力
	Tip_Configure_App,				//感知
	Tip_Configure_Luck,				//运气
	Tip_Configure_Blaze_Att,		//火焰攻击
	Tip_Configure_Frost_Att,		//冰霜攻击
	Tip_Configure_Poison_Att,		//毒性攻击
	Tip_Configure_Thunder_Att,		//雷电攻击
	Tip_Configure_Blaze_Def,		//火焰抗性
	Tip_Configure_Frost_Def,		//冰霜抗性	
	Tip_Configure_Poison_Def,		//毒性抗性
	Tip_Configure_Thunder_Def,		//雷电抗性
	Tip_Configure_HP,				//生命
	Tip_Configure_MP,				//魔法
	Tip_Configure_RightHand,		//右手
	Tip_Configure_LeftHand,			//左手
	Tip_Configure_MDef,				//法防
	Tip_Configure_Phy_Def,			//物理防御
	Tip_Configure_Phy_DoubleAtt,	//物理暴击
	Tip_Configure_Phy_ResistDA,		//物理暴击抗
	Tip_Configure_Mag_Def,			//魔法防御
	Tip_Configure_Mag_DoubleAtt,	//法术暴击
	Tip_Configure_Mag_ResistDA,		//法术暴击抗
	Tip_Configure_Hit,				//命中
	Tip_Configure_Dodge,			//躲避
	Tip_Configure_CsRate,			//暴击几率
	Tip_Configure_WardRate,			//招架几率
	

	Tip_Configure_Max
};

struct Occuption_Tip_Info
{
	std::string	tip_configure[Tip_Configure_Max];
};

class CTip_Configure
{
public:
	CTip_Configure();
	virtual ~CTip_Configure();

public:
	void	load();

	const char*	getTip(int occuption, TipConfigure type);

private:
	std::map<int, Occuption_Tip_Info>	mapOccuption_TipInfo;
};

extern CTip_Configure Tip_Configure;

#endif