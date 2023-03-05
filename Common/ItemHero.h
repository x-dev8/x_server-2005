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
		int hero_id;						// ����ID
		string hero_name;					// ��������
		string namePicAddr;					// ��������ͼƬ��ַ
		char hero_sex;						// �����Ա�
		int itemd_id;						// ��Ӧ����ID
		int need_lv;						// ��Ʒ����ʹ�õȼ�
		int material_id;					// �������ID
		int material_count;					// �����������
		int need_money;						// �����Ǯ
		//string head_malepic;				// ������2Dͷ����Դ
		//string head_femalepic;			// Ů����2Dͷ����Դ
		string Pic_Head;					// ���Ͻǵ�ͷ����Դ
		string Pic_BianShenUI;				// ��������UI��ͷ����Դ
		string Pic_TuJianUI;				// ����ͼ��UI��ͷ����Դ
		string Pic_BasePro;					// ��������UI��ͷ����Դ
		string icon_addr;					// ����������άͼ
		string explain_hero;				// �������Ǽ��
		string property_hero;				// ������������
		string proPicAddr;					// ������������ͼƬ��ַ
		int hero_skill1;					// ��������1
		int hero_skill2;					// ��������2
		int hero_skill3;					// ��������3
		int skill1_lv;						// ��������1�ȼ�
		int skill2_lv;						// ��������2�ȼ�
		int skill3_lv;						// ��������3�ȼ�
		int heroAttr[EBaseAttr_MaxSize];	// ������������
		int heroAttrPer[EBaseAttr_MaxSize]; // �����������԰ٷֱ�
		//int hero_wuli;					// ���������츳
		//int hero_zhili;					// ���������츳
		//int hero_tongyuli;				// ����ͳ���츳
		//int hero_shenfa;					// �������츳
		int hero_lianxing;					// ������������
		int hero_faxing;					// ����������
		string hero_fuse;					// ���������ɫ
		float hero_rate;					// ģ�ͷŴ���

		int TellOther;						// ��־�����������ʱ�Ƿ�ȫ��ͨ��
		SItemHero()
		{
			memset(this,0,sizeof(SItemHero));
			hero_id = INVALID_HERO_ID;
		}
	};

	// �����������Ч������������Ч��
	struct ZhujiangExtraInfo
	{
		unsigned char Class;			// ְҵ
		unsigned char Gender;			// �Ա�
		std::string Effect;				// ����������Ч
		unsigned short SceneActionID;	// ��ͷ�й�ID(����ʲô����������)
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

