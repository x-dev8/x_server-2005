#include "ItemDefine.h"
#include "ItemDetail.h"
#pragma warning( push, 0 )

using namespace ItemDefine;

const char* SItemCommon::GetItemName()
{
    return  GettheItemDetail().GetString( dwItemNameAddr );
}

const char* SItemCommon::GetItemDesc()
{
    return GettheItemDetail().GetString( dwItemDescAddr );
}

const char* SItemCommon::GetIconInItemBag()
{
    return GettheItemDetail().GetString( dwIconInItemBagAddr );
}

const char* SItemCommon::GetIconTile()
{
    return GettheItemDetail().GetString( dwIconTileAddr );
}

const char* SItemCommon::GetIconSoundFile()
{
    return GettheItemDetail().GetString( dwIconSoundAddr );
}
const char* SItemCommon::GetSingEffect()
{
    return GettheItemDetail().GetString( dwSingEffect );
}
const char* SItemCommon::GetAssoilEffect()
{
    return GettheItemDetail().GetString( dwAssoilEffect );
}
const char* SItemCommon::GetHurtEffect()
{
    return GettheItemDetail().GetString( dwHurtEffect );
}
const char* SItemCanEquip::GetReplaceSkin()
{
    return GettheItemDetail().GetString( dwReplaceSkinAddr );
}

const char* SProfession::GetName()
{
    return GettheItemDetail().GetString( dwNameAddr );
}

const char* SDrome::GetName()
{
    return GettheItemDetail().GetString( dwNameAddr );
}

const char* SDrome::GetModelPath()
{
    return GettheItemDetail().GetString( dwModelAddr );
}

const char* SDrome::GetSkinName()
{
    return GettheItemDetail().GetString( dwSkinAddr );
}

const char* SDrome::GetMountEffectPath()
{
    return GettheItemDetail().GetString( dwMountEffectAddr );
}

const char* SDrome::GetDisMountEffectPath()
{
    return GettheItemDetail().GetString( dwDisMountEffectAddr );
}

const char* SDrome::GetRunSoundOfLeftFootPath()
{
    return GettheItemDetail().GetString( dwRunSoundOfLeftFootAddr );
}

const char* SDrome::GetRunSoundOfRightFootPath()
{
    return GettheItemDetail().GetString( dwRunSoundOfRightFootAddr );
}

const char* SDrome::GetNeightSoundPath()
{
    return GettheItemDetail().GetString( dwNeightSoundAddr );
}

const char* SDrome::GetMountAction( int Index )
{
    if( Index < 0 || Index >= MountMaxActionNum )
        Index = 0;

    return GettheItemDetail().GetString( dwMountAction[Index] );
}

const char* SDrome::GetFrontFootPrintPath()
{
    return GettheItemDetail().GetString( dwFrontFootPrintAddr );
}

const char* SDrome::GetBackFootPrintPath()
{
    return GettheItemDetail().GetString( dwBackFootPrintAddr );
}

const char* SDrome::GetHeadPicPath()
{
    return GettheItemDetail().GetString( dwHeadPicAddr );
}

const char* STraffic::GetName()
{
    return GettheItemDetail().GetString( dwNameAddr );
}

const char* SMonster::GetName()
{
    return GettheItemDetail().GetString( dwNameAddr );
}

const char* SMonster::GetNamePrefix()
{
    return GettheItemDetail().GetString( dwNamePrefix );
}

const char* SMonster::GetCreatureSound()
{
    return GettheItemDetail().GetString( dwCreatureSoundAddr );
}

const char* SPetMonster::GetPetDesc()
{
    return GettheItemDetail().GetString( dwPetDescAddr );
}

const char* SPetMonster::GetPetBornDesc()
{
    return GettheItemDetail().GetString( dwPetBornDescAddr );
}

const char* SPetMonster::GetPetTypeName()
{
    return GettheItemDetail().GetString( dwPetTypeNameAddr );
}

/*const char* SMonster::GetGroupName()
{
return GettheItemDetail().GetString( dwGroupName );
}*/

const char* SMonster::GetSkin()
{
    return GettheItemDetail().GetString( dwSkinAddr );
}

const char* SMonster::GetDeadScript()
{
    return GettheItemDetail().GetString( dwDeadScriptAddr );
}

const char* SMonster::GetAILuaScript()
{
    return GettheItemDetail().GetString( dwAILuaScriptAddr );
}

const char* SMonster::GetWeaponSound()
{
    return GettheItemDetail().GetString(dwWeaponSoundAddr);
}

const char* SMonster::GetArmourSound()
{
    return GettheItemDetail().GetString(dwArmourSoundAddr);
}

const char* SMonster::GetFrontFootPrintPath()
{
    return GettheItemDetail().GetString( dwFrontFootPrintAddr );
}

const char* SMonster::GetBackFootPrintPath()
{
    return GettheItemDetail().GetString( dwBackFootPrintAddr );
}

const char* SMonster::GetTitle()
{
    return GettheItemDetail().GetString( strTitleAddress );
}

const char* SCreatureSound::GetName()
{
    return GettheItemDetail().GetString( dwCreatureNameAddr );
}

const char* SItemSkill::GetSkillName()
{
    return GettheItemDetail().GetString( dwSkillNameAddr );
}

const char* SItemSkill::GetSkillRideAction()
{
	return GettheItemDetail().GetString( dwRideAction );
}

const char* SItemSkill::GetSkillAction( int Index )
{
    if( Index < 0 || Index > 9 )
        Index = 0;

    return GettheItemDetail().GetString( dwSkillAction[Index] );
}

const char* SItemSkill::GetIntonateAction()
{
    return GettheItemDetail().GetString( dwIntonateAction );
}

const char* SItemSkill::GetRideIntonateAction()
{
	return GettheItemDetail().GetString( dwRideIntonateAction );
}

const char* SItemSkill::GetIntonateEffectName()
{
    return GettheItemDetail().GetString( dwIntonateEffectAddr );
}

const char* SItemSkill::GetAttackerEffectName()
{
    return GettheItemDetail().GetString( dwAttackerEffectAddr );
}

const char* SItemSkill::GetTargetEffectName()
{
    return GettheItemDetail().GetString( dwTargetEffectAddr );
}

const char* SItemSkill::GetSkillEffectName()
{
    return GettheItemDetail().GetString( dwSkillEffectAddr );
}

const char* SItemSkill::GetIntonateEffectName2()
{
    return GettheItemDetail().GetString( dwIntonateEffectAddr2 );
}

const char* SItemSkill::GetAttackerEffectName2()
{
    return GettheItemDetail().GetString( dwAttackerEffectAddr2 );
}

const char* SItemSkill::GetTargetEffectName2()
{
    return GettheItemDetail().GetString( dwTargetEffectAddr2 );
}

const char* SItemSkill::GetSkillEffectName2()
{
    return GettheItemDetail().GetString( dwSkillEffectAddr2 );
}

const char* SItemSkill::GetSkillDescription()
{
    return GettheItemDetail().GetString( dwSkillDescription );
}

const char* SItemStatus::GetStatusEffectName()
{
    return GettheItemDetail().GetString( dwStatusEffectAddr );
}

const char* SItemStatus::GetStatusAction()
{
    return GettheItemDetail().GetString( dwStatusActionAddr );
}

const char* SItemStatus::GetAnimationName()
{
    return GettheItemDetail().GetString( dwAnimationAddr );
}
bool SItemStatus::IsHaveContinueValueChange()
{
	//TODO: 如果Status Buff 不起作用，请检查此处
	if (0 != stChanged_HP || 0 != stChanged_MP || 0 != attackModulus || 0 != defendModulus || 
		0 != stChangedFightPoint ||  0 != recoverHPBasePer || 0 != recoverMPBasePer || 0 != recoverHPMaxPer || 
		0 != recoverMPMaxPer || stBalanceType == balance_status_type_timeexp )
	{ return true;}

	return false;
}



const char* SItemCanEquip::GetSound()
{
    return GettheItemDetail().GetString( dwSoundAddr );
}

bool SItemCanEquip::HasEquipHp()
{
    switch( ustEquipType )
    {
    case equip_LeaderCard:
    case equip_Amulet:
        return false;
        break;
    default:
        break;
    }

    return true;
}

//const char* SCreatItemMod::GetCreatItemName()
//{
//    return GettheItemDetail().GetString(dwName);
//}

bool SItemCommon::IsExclusive()    // 是否独占
{ // 是否独占
    //switch( ucItemType )
    //{    
    //    //case ItemDefine::ITEMTYPE_MATERIAL:
    //    //    {
    //    //        ItemDefine::SCreateMaterial* pMaterial = static_cast<ItemDefine::SCreateMaterial*>(this);
    //    //        if (!pMaterial)
    //    //        {
    //    //            return false;
    //    //        }
    //    //        if (pMaterial->stMaterialType == CItemDetail::ematerial_metal || 
    //    //            pMaterial->stMaterialType == CItemDetail::ematerial_pelage||
    //    //            pMaterial->stMaterialType == CItemDetail::ematerial_wood  ||
    //    //            pMaterial->stMaterialType == CItemDetail::ematerial_uplevel ||
    //    //            pMaterial->stMaterialType == CItemDetail::ematerial_compound )
    //    //            return true;
    //    //        else
    //    //            return false;
    //    //    }
    //    //    break;
    //case ItemDefine::ITEMTYPE_RESTORE:
    //    {
    //        ItemDefine::SItemRestore* pItemDetail = (ItemDefine::SItemRestore*)this;
    //        return pItemDetail->bExclusive;
    //    }
    //    break;
    //case ItemDefine::ITEMTYPE_CHECKUP:
    //    {
    //        ItemDefine::SItemCheckUp* pItemCheckup = static_cast< ItemDefine::SItemCheckUp* >( this );
    //        return pItemCheckup->bExclusive;
    //    }
    //    break;
    //case ItemDefine::ITEMTYPE_SPECIAL:
    //    {
    //        ItemDefine::SItemSpecial* pItemSpecial = static_cast< ItemDefine::SItemSpecial* >( this );
    //        return pItemSpecial->bExclusive;
    //    }
    //    break;

    //case ItemDefine::ITEMTYPE_GEM:
    //case CItemDetail::ITEMTYPE_CREATEITEMRULE:
    //case ItemDefine::ITEMTYPE_TASK:
    //case ItemDefine::ITEMTYPE_MATERIAL:
    //case ItemDefine::ITEMTYPE_OTHER:
    //case ItemDefine::ITEMTYPE_GUILD: 
    //case ItemDefine::ITEMTYPE_WEAPON:
    //case ItemDefine::ITEMTYPE_ARMOUR:
    //    {
    //        return nStackNum == 1;
    //    }
    //    break;
    //} 

    //return true;
    return nStackNum == 1; // 如果可堆叠数量 = 1 则是独占，否则是是非独占
}

uint16 SItemCommon::GetStackNum()
{
    return nStackNum;
}

#pragma warning( pop )
