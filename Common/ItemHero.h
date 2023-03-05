/*****************************************
	Filename:     ItemHero.h
	Writer:		zhuxincong 2012.7.11
*****************************************/

#ifndef _Hero_H_
#define _Hero_H_
#pragma once
#include <string>
#include <map>
#include "ItemDetail.h"
#include "GameDefineChar.h"

using namespace std;
class  CItemHeroString
{
public:

	CItemHeroString();
	~CItemHeroString();
	typedef map<int32,string> _mapHeroString;
public:
	bool LoadHeroString(const char* filename);

	const char* GetStringById(int32 id);

	static CItemHeroString& Instance()
	{
		static CItemHeroString cihs;
		return cihs;
	}

	_mapHeroString& GetHeroString(){return m__mapHeroString;}

private:
	_mapHeroString m__mapHeroString;
};

#define TheHeroString CItemHeroString::Instance()

class CItemHero
{
public:
	struct SItemHero 
	{
		int hero_id;						// 主将ID
		string hero_name;					// 主将名字
		string namePicAddr;					// 主将名字图片地址
		char hero_sex;						// 主将性别
		int itemd_id;						// 对应道具ID
		int need_lv;						// 物品道具使用等级
		int material_id;					// 所需材料ID
		int material_count;					// 所需材料数量
		int need_money;						// 所需金钱
		//string head_malepic;				// 男主将2D头像资源
		//string head_femalepic;			// 女主将2D头像资源
		string Pic_Head;					// 左上角的头像资源
		string Pic_BianShenUI;				// 主将变身UI的头像资源
		string Pic_TuJianUI;				// 主将图鉴UI的头像资源
		string Pic_BasePro;					// 人物属性UI的头像资源
		string icon_addr;					// 主将属性四维图
		string explain_hero;				// 主将传记简介
		string property_hero;				// 主将兵法属性
		string proPicAddr;					// 主将兵法属性图片地址
		int hero_skill1;					// 主将技能1
		int hero_skill2;					// 主将技能2
		int hero_skill3;					// 主将技能3
		int skill1_lv;						// 主将技能1等级
		int skill2_lv;						// 主将技能2等级
		int skill3_lv;						// 主将技能3等级
		int heroAttr[EBaseAttr_MaxSize];	// 主将各项属性
		int heroAttrPer[EBaseAttr_MaxSize]; // 主将各项属性百分比
		//int hero_wuli;					// 主将武力天赋
		//int hero_zhili;					// 主将智力天赋
		//int hero_tongyuli;				// 主将统御天赋
		//int hero_shenfa;					// 主将身法天赋
		int hero_lianxing;					// 主将变身脸型
		int hero_faxing;					// 主将变身发型
		string hero_fuse;					// 主将变身肤色
		float hero_rate;					// 模型放大倍数

		int TellOther;						// 标志，变身该主将时是否全服通告
		SItemHero()
		{
			memset(this,0,sizeof(SItemHero));
			hero_id = INVALID_HERO_ID;
		}
	};

	// 主将变身的音效可以配置在特效里
	struct ZhujiangExtraInfo
	{
		unsigned char Class;			// 职业
		unsigned char Gender;			// 性别
		std::string Effect;				// 主将变身特效
		unsigned short SceneActionID;	// 镜头托管ID(动作什么在在这配置)
	};

	typedef map<unsigned short,SItemHero> mapItemHero;

public:
	static CItemHero & Instance()
	{
		static CItemHero cth;
		return cth;
	}

	CItemHero(void);
	~CItemHero(void);

	bool LoadHeroItemSlk(const char* szFileName);
	bool SaveHeroConfig(const char* szFileName,const char* szStringName = NULL);

	bool LoadHeroConfig(const char* szFileName,const char* stringName);

	SItemHero* FindHeroByItemID(unsigned short item_id);
	SItemHero* FindHeroByHeroID(unsigned short hero_id);

	CItemHero::ZhujiangExtraInfo * FindZhujiangExtraInfo(unsigned char profession, unsigned sex);

private:
	mapItemHero _mapItemHeroItemId;
	mapItemHero _mapItemHeroHeroId;

	std::vector<ZhujiangExtraInfo> mZhujiangExtraInfos;
};
//extern CItemHero& GetItemHero();

#define theItemHero CItemHero::Instance()

#endif 

