#ifndef ItemSkillSpecialAttr_Inc
#define ItemSkillSpecialAttr_Inc
#include <vector>

//AddPhysicAtt			增加物理攻击力							int
//AddPhysicDef			增加物理防御力							int
//AddMagicAtt				增加魔法攻击力							int
//AddMagicDef				增加魔法防御力							int
//AddBonusDamageRange		伤害浮动值								string(short short)					short,short
//AddCriticalAttackFactor	致命一击伤害倍数浮动					float								
//AddNormalAttackRate		增加攻击频率							float								
//AddMoveRate				增加移动速度							float								
//AddHPRestoreRate		增加生命恢复速度						int									int	
//AddMagicCastRate		增加魔法吟唱速度						float
//DecTPCost				减少体力消耗							int									int(百分比)
//AddPosionResist			增加毒素抵抗							int									int
//
//DispelPoison			解毒									
//DispelSilence			消除沉默（吟唱不能）				
//NormalRelive			普通复活																		
//FullRelive				全状态复活
//DispelStone				消除石化		
//Identify				鉴定卷轴		
//MagicImmunity			魔法免疫
//PhysicImmunity			物理免疫	
//HPHeal				补血

//PoisonRate			中毒几率	short(百分比，中毒几率),short(中毒程度),short（持续时间，100豪秒）
//FrostRate				冰冻几率	short(百分比，冰冻几率),short（持续时间，100豪秒）
//StoneRate				石化几率	short(百分比，石化几率),short（持续时间，100豪秒）
//SleepRate				昏睡几率	short(百分比，昏睡几率),short（持续时间，100豪秒）


//特殊属性的定义
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

	//恢复：吃药
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
//载入的附加于物品上的attr
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
		//特殊属性名字
		char *szName;
		//描述
		char *szDesc;
		//级别，
		short stLevel;
		//附加的基本属性个数
		int iBonusAttrNum;
		SSpecialAttr bonusAttr[ const_iMaxSpecialAttrOfItem ];
		//可以附加的装备类型
		unsigned short ustEquipCanApply;
		//装备模型颜色
		char cModelColor;
		//装备光晕颜色
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

//附加 除去特殊效果
#define APPLY_SPECIALATTR(bAdd,value,valueAttr)\
	if(bAdd)\
	value += valueAttr;\
	else\
	value -= valueAttr;


extern CItemSpecialAttr theItemSpecialAttr;
void CaluBonusAttr( char *szString,SSpecialAttr *pSpecialAttr,int &iCount,int iMaxCount );
#endif