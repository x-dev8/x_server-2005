#ifndef ItemSkillSpecialAttr_Inc
#define ItemSkillSpecialAttr_Inc
#include <vector>

//AddPhysicAtt			������������							int
//AddPhysicDef			�������������							int
//AddMagicAtt				����ħ��������							int
//AddMagicDef				����ħ��������							int
//AddBonusDamageRange		�˺�����ֵ								string(short short)					short,short
//AddCriticalAttackFactor	����һ���˺���������					float								
//AddNormalAttackRate		���ӹ���Ƶ��							float								
//AddMoveRate				�����ƶ��ٶ�							float								
//AddHPRestoreRate		���������ָ��ٶ�						int									int	
//AddMagicCastRate		����ħ�������ٶ�						float
//DecTPCost				������������							int									int(�ٷֱ�)
//AddPosionResist			���Ӷ��صֿ�							int									int
//
//DispelPoison			�ⶾ									
//DispelSilence			������Ĭ���������ܣ�				
//NormalRelive			��ͨ����																		
//FullRelive				ȫ״̬����
//DispelStone				����ʯ��		
//Identify				��������		
//MagicImmunity			ħ������
//PhysicImmunity			��������	
//HPHeal				��Ѫ

//PoisonRate			�ж�����	short(�ٷֱȣ��ж�����),short(�ж��̶�),short������ʱ�䣬100���룩
//FrostRate				��������	short(�ٷֱȣ���������),short������ʱ�䣬100���룩
//StoneRate				ʯ������	short(�ٷֱȣ�ʯ������),short������ʱ�䣬100���룩
//SleepRate				��˯����	short(�ٷֱȣ���˯����),short������ʱ�䣬100���룩


//�������ԵĶ���
enum enumItemSkillSpecialAttr
{ // ToCheck
	SpecialAttr_AddPhysicAtt					= 0			
	,SpecialAttr_AddPhysicDef			
	,SpecialAttr_AddMagicAtt			
	,SpecialAttr_AddMagicDef			
	,SpecialAttr_AddBonusDamageRange	
	,SpecialAttr_AddCriticalAttackFactor
	,SpecialAttr_AddNormalAttackRate	
	,SpecialAttr_AddMoveRate			
	,SpecialAttr_AddHPRestoreRate		
	,SpecialAttr_AddMagicCastRate		
	,SpecialAttr_DecTPCost				
	,SpecialAttr_AddPosionResist		

	,SpecialAttr_DispelPoison			
	,SpecialAttr_DispelSilence			
	,SpecialAttr_NormalRelive			
	,SpecialAttr_FullRelive			
	,SpecialAttr_DispelStone			
	,SpecialAttr_Identify				
	,SpecialAttr_MagicImmunity			
	,SpecialAttr_PhysicImmunity		

	//�ָ�����ҩ
	,SpecialAttr_HPHeal
	//
	,SpecialAttr_PoisonRate
	,SpecialAttr_FrostRate
	,SpecialAttr_StoneRate
	,SpecialAttr_SleepRate
	,SpecialAttr_AddPhysicAttMax
	,SpecialAttr_AddPhysicAttMin
	,SpecialAttr_AddPhysicDefMax
	//,SpecialAttr_AddPhysicDefMin
	,SpecialAttr_AddMagicAttMax
	//,SpecialAttr_AddMagicAttMin
	,SpecialAttr_AddMagicDefMax
	//,SpecialAttr_AddMagicDefMin
	//

	,SpecialAttr_Max
};

struct S2Short
{
	short stValue0,stValue1;
};
struct S3Short
{
	short stValue0,stValue1,stValue2;
};
union USpecialAttrValue
{
	int iValue;
	float fValue;
	S2Short short2;
	S3Short short3;
};	

struct SSpecialAttr
{
	short stWhichAttr;
	USpecialAttrValue value;
};

extern char *g_ItemSkillSpecialAttrName[ SpecialAttr_Max ];

class CFlyMemAllocer;
//����ĸ�������Ʒ�ϵ�attr
class CItemSpecialAttr
{
public:
	enum enumConst
	{
		const_iMaxSpecialAttrOfItem = 3
	};
	struct SItemSpecialAttr
	{
		//short stID;
		//������������
		char *szName;
		//����
		char *szDesc;
		//����
		short stLevel;
		//���ӵĻ������Ը���
		int iBonusAttrNum;
		SSpecialAttr bonusAttr[ const_iMaxSpecialAttrOfItem ];
		//���Ը��ӵ�װ������
		unsigned short ustEquipCanApply;
		//װ��ģ����ɫ
		char cModelColor;
		//װ��������ɫ
		char cHaloColor;
	};
	
	CItemSpecialAttr();
	~CItemSpecialAttr();
	bool LoadFromSlk( char *szFile );

	void SetMemAllocer( CFlyMemAllocer *pAllocer ){ m_pMemAllocer = pAllocer; }

	SItemSpecialAttr *GetItemSpecialAttrByID( short stID );
	int	GetItemSpecialAttrNum(void){ return (int)(m_vecItemSpecialAttr.size()); }
private:
	typedef std::vector< SItemSpecialAttr* > vectorItemSpecialAttr;
	vectorItemSpecialAttr m_vecItemSpecialAttr;

	CFlyMemAllocer *m_pMemAllocer;
};

//���� ��ȥ����Ч��
#define APPLY_SPECIALATTR(bAdd,value,valueAttr)\
	if(bAdd)\
	value += valueAttr;\
	else\
	value -= valueAttr;


extern CItemSpecialAttr theItemSpecialAttr;
void CaluBonusAttr( char *szString,SSpecialAttr *pSpecialAttr,int &iCount,int iMaxCount );
#endif