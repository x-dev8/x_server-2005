#ifndef AN_CONFIG_TIP_H_
#define AN_CONFIG_TIP_H_

//#include <Windows.h>
#include <string>
#include <map>

enum TipConfigure
{
	//---��ɫ����test_tip��ʾ
	Tip_Configure_Name = 0,			//����
	Tip_Configure_Job,				//ְҵ
	Tip_Configure_Level,			//�ȼ�
	Tip_Configure_Title,			//�ƺ�
	Tip_Configure_Official,			//����
	Tip_Configure_Guild,			//����
	Tip_Configure_Distinction,		//����
	Tip_Configure_Marry,			//��ż
	Tip_Configure_KillNum,			//��ɱ
	Tip_Configure_Credit,			//����
	Tip_Configure_Str,				//����
	Tip_Configure_Con,				//����
	Tip_Configure_Agi,				//����
	Tip_Configure_Int,				//����
	Tip_Configure_App,				//��֪
	Tip_Configure_Luck,				//����
	Tip_Configure_Blaze_Att,		//���湥��
	Tip_Configure_Frost_Att,		//��˪����
	Tip_Configure_Poison_Att,		//���Թ���
	Tip_Configure_Thunder_Att,		//�׵繥��
	Tip_Configure_Blaze_Def,		//���濹��
	Tip_Configure_Frost_Def,		//��˪����	
	Tip_Configure_Poison_Def,		//���Կ���
	Tip_Configure_Thunder_Def,		//�׵翹��
	Tip_Configure_HP,				//����
	Tip_Configure_MP,				//ħ��
	Tip_Configure_RightHand,		//����
	Tip_Configure_LeftHand,			//����
	Tip_Configure_MDef,				//����
	Tip_Configure_Phy_Def,			//�������
	Tip_Configure_Phy_DoubleAtt,	//������
	Tip_Configure_Phy_ResistDA,		//��������
	Tip_Configure_Mag_Def,			//ħ������
	Tip_Configure_Mag_DoubleAtt,	//��������
	Tip_Configure_Mag_ResistDA,		//����������
	Tip_Configure_Hit,				//����
	Tip_Configure_Dodge,			//���
	Tip_Configure_CsRate,			//��������
	Tip_Configure_WardRate,			//�мܼ���
	

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