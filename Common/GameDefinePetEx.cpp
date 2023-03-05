#include "GameDefinePet.h"
#include "ItemDetailConfig.h"
#include "PetSettingConfig.h"
#include "ProcessCharInfo.h"

uint16 SPetItem::SBaseInfo::GetCurrentBaseAttr( uint8 attrType )
{
    if ( attrType >= EBaseAttr_MaxSize )
    { return 0; }

	//�������� Ӧ�ð���װ��������
	int Value =  baseAttribute[attrType] + potentialAttribute[attrType];	
	for(int i =0;i<PetEquip_MaxSum;++i)
	{
		if(PetEquip[i].itembaseinfo.ustItemID == 0 || PetEquip[i].itembaseinfo.nOnlyInt == 0 || PetEquip[i].IsOverdue())
			continue;
		int num = 0;
		switch(attrType)
		{
		case EBaseAttr_Strength:
			num = PetEquip[i].petequipdata.Strength;
			break;
		case EBaseAttr_Agility:
			num = PetEquip[i].petequipdata.Agility;
			break;
		case EBaseAttr_Stamina:
			num = PetEquip[i].petequipdata.Stamina;
			break;
		case EBaseAttr_Intelligence:
			num = PetEquip[i].petequipdata.Intelligence;
			break;
		}
		Value += num;
	}
	return Value;
}

uint16 SPetItem::SBaseInfo::GetCurrentAptitude( uint8 attrType )
{
    if ( attrType >= EBaseAttr_MaxSize )
    { return 0; }

    // �������ʼӳ�   
    int     nSavvyAptitude = thePetSettingConfig.GetSavvyAddAptitudePer( savvy ) ;
    return  aptitudeAttribute[attrType] + aptitudeAttribute[attrType] * nSavvyAptitude * DEF_THOUSANDTH;
}

uint32 SPetItem::SBaseInfo::GetFightAttribute( uint8 attrType )
{
    if ( attrType >= CharAttr_AttributMaxCount )
    { return 0; }

    ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( petId );
    if ( pPetMonster == NULL ) 
    { return 0; }

    uint32 finalValue = 0;

    switch( attrType )
    {
    case CharAttr_HPMax:
        {
            // HP
            float fHpAptitudeEffect = GetCurrentBaseAttr( EBaseAttr_Stamina ) * ( thePetSettingConfig.GetFightAttrBaseAttrParam(CharAttr_HPMax) * 
                DEF_TENTHOUSANDTH ) * ( GetCurrentAptitude(EBaseAttr_Stamina) * DEF_PERCENT );

            float fHpLevelEffect = level * (thePetSettingConfig.GetFightAttrLevelParam(CharAttr_HPMax) * DEF_TENTHOUSANDTH) * (growRate * DEF_THOUSANDTH);

            finalValue = pPetMonster->nHPMax + fHpAptitudeEffect + fHpLevelEffect;
        }
        break;
    case CharAttr_AttackPhysics:
        {
            // �﹥
            float fPhyAttackAptitudeEffect = GetCurrentBaseAttr(EBaseAttr_Strength) * ( thePetSettingConfig.GetFightAttrBaseAttrParam(CharAttr_AttackPhysics) * 
                DEF_TENTHOUSANDTH ) * ( GetCurrentAptitude(EBaseAttr_Strength) * DEF_PERCENT ) ;

            float fPhyAttackLevelEffect = level * (thePetSettingConfig.GetFightAttrLevelParam(CharAttr_AttackPhysics) * DEF_TENTHOUSANDTH) * (growRate * DEF_THOUSANDTH);

            finalValue = pPetMonster->fPhysicAtt + fPhyAttackAptitudeEffect + fPhyAttackLevelEffect;
        }
        break;
    case CharAttr_AttackMagic:
        {
            // ħ��
            float fMagAttackAptitudeEffect = GetCurrentBaseAttr(EBaseAttr_Intelligence) * ( thePetSettingConfig.GetFightAttrBaseAttrParam(CharAttr_AttackMagic) * 
                DEF_TENTHOUSANDTH) * (GetCurrentAptitude(EBaseAttr_Intelligence) * DEF_PERCENT);

            float fMagAttackLevelEffect = level * (thePetSettingConfig.GetFightAttrLevelParam(CharAttr_AttackMagic) * DEF_TENTHOUSANDTH) * (growRate * DEF_THOUSANDTH) ;

            finalValue = pPetMonster->fMagicAtt + fMagAttackAptitudeEffect + fMagAttackLevelEffect;
        }
        break;
    case CharAttr_DefendPhysics:
        {
            // ���
            float fPhyDefendAptitudeEffect = GetCurrentBaseAttr(EBaseAttr_Stamina) * (thePetSettingConfig.GetFightAttrBaseAttrParam(CharAttr_DefendPhysics) * 
                DEF_TENTHOUSANDTH) * (GetCurrentAptitude(EBaseAttr_Stamina) * DEF_PERCENT) ;

            float fPhyDefendLevelEffect = level * (thePetSettingConfig.GetFightAttrLevelParam(CharAttr_DefendPhysics) * DEF_TENTHOUSANDTH) * (growRate * DEF_THOUSANDTH);

            finalValue = pPetMonster->fPhysicDef + fPhyDefendAptitudeEffect + fPhyDefendLevelEffect;
        }
        break;
    case CharAttr_DefendMagic:
        {
            // ħ��
            float fMagDefendAptitudeEffect = GetCurrentBaseAttr(EBaseAttr_Stamina) * (thePetSettingConfig.GetFightAttrBaseAttrParam(CharAttr_DefendMagic) * 
                DEF_TENTHOUSANDTH) * (GetCurrentAptitude(EBaseAttr_Stamina) * DEF_PERCENT);

            float fMagDefendLevelEffect = level * (thePetSettingConfig.GetFightAttrLevelParam(CharAttr_DefendMagic) * DEF_TENTHOUSANDTH) * (growRate * DEF_THOUSANDTH);

            finalValue = pPetMonster->fMagicDef + fMagDefendAptitudeEffect + fMagDefendLevelEffect;
        }
        break;
    case CharAttr_Exact:
        {
            // ����
            float fExactAptitudeEffect = GetCurrentBaseAttr(EBaseAttr_Agility) * (thePetSettingConfig.GetFightAttrBaseAttrParam(CharAttr_Exact) * 
                DEF_TENTHOUSANDTH) * (GetCurrentAptitude(EBaseAttr_Agility) * DEF_PERCENT);

            float fExactLevelEffect = level * (thePetSettingConfig.GetFightAttrLevelParam(CharAttr_Exact) * DEF_TENTHOUSANDTH) * (growRate * DEF_THOUSANDTH);

            finalValue = pPetMonster->stExact + fExactAptitudeEffect + fExactLevelEffect;
        }
        break;
    case CharAttr_Dodge:
        {
            // ����
            float fDodgeAptitudeEffect = GetCurrentBaseAttr(EBaseAttr_Agility) * (thePetSettingConfig.GetFightAttrBaseAttrParam(CharAttr_Dodge) * 
                DEF_TENTHOUSANDTH) * (GetCurrentAptitude(EBaseAttr_Agility) * DEF_PERCENT);

            float fDodgeLevelEffect = level * (thePetSettingConfig.GetFightAttrLevelParam(CharAttr_Dodge) * DEF_TENTHOUSANDTH) * (growRate * DEF_THOUSANDTH);

            finalValue = pPetMonster->stDodge + fDodgeAptitudeEffect + fDodgeLevelEffect;
        }
        break;
    case CharAttr_Critical:
        {
            // ����
            float fCriticalAptitudeEffect = GetCurrentBaseAttr(EBaseAttr_Agility) * (thePetSettingConfig.GetFightAttrBaseAttrParam(CharAttr_Critical) * 
                DEF_TENTHOUSANDTH) * (GetCurrentAptitude(EBaseAttr_Agility) * DEF_PERCENT);

            float fCriticalLevelEffect = level * (thePetSettingConfig.GetFightAttrLevelParam(CharAttr_Critical) * DEF_TENTHOUSANDTH) * (growRate * DEF_THOUSANDTH);

            finalValue = pPetMonster->critical + fCriticalAptitudeEffect + fCriticalLevelEffect;
        }
        break;
    case CharAttr_Tenacity:
        {
            // ����
            float fTenacityAptitudeEffect = GetCurrentBaseAttr(EBaseAttr_Agility) * (thePetSettingConfig.GetFightAttrBaseAttrParam(CharAttr_Tenacity) * 
                DEF_TENTHOUSANDTH) * (GetCurrentAptitude(EBaseAttr_Agility) * DEF_PERCENT);

            float fTenacityLevelEffect = level * (thePetSettingConfig.GetFightAttrLevelParam(CharAttr_Tenacity) * DEF_TENTHOUSANDTH) * (growRate * DEF_THOUSANDTH) ;

            finalValue = pPetMonster->tenacity + fTenacityAptitudeEffect + fTenacityLevelEffect;
        }
        break;
    default:
        break;
    }

    return finalValue;
}
uint32 SPetItem::SBaseInfo::GetPetNewModeID()
{
	//��ȡ�����ģ��ID ��Ҫ�ж�ʱ��
	time_t TimeLog(n64ModeUseTime);//��ȡ������ʱ��
	time_t NowTime;
	_time64(&NowTime);
	if(NowTime >= TimeLog && n64ModeUseTime !=-1)
	{
		return 0;
	}
	else
		return PetModeID;
}
void SPetItem::SBaseInfo::SetPetModeID(uint32 ModeID,__int64 EndTime)
{
	//���ø�����ģ��ID
	PetModeID = ModeID;
	n64ModeUseTime = EndTime;
}
bool SPetItem::SBaseInfo::IsExitesEquip()
{
	//�жϸ����Ƿ���װ��������
	for(int i =0;i<PetEquip_MaxSum;++i)
	{
		if(PetEquip[i].itembaseinfo.ustItemID == 0 || PetEquip[i].itembaseinfo.nOnlyInt == 0)
			continue;
		return true;
	}
	return false;
}