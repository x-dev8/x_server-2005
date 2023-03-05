#include "ProcessCharInfo.h"
#include "DataCenter.h"
#include "ItemDetail.h"
#include "PetSettingConfig.h"

std::string ProcessCharInfo::ProcessProfession(unsigned short usArmsType)
{
    SArmsParamModulusExtend* pArmsParamModulusExtend = theDataCenter.GetArmsParamModulus(usArmsType);
    if ( NULL == pArmsParamModulusExtend )
    { return ""; }

    return pArmsParamModulusExtend->armsName;
}

//void ProcessCharInfo::Effect( uint8 type, uint16 part, SAttrType0* pValue, uint16 armType, SCharFightAttr& fightAttri )
//{
//    if ( pValue == NULL )
//    { return; }
//
//    switch ( armType )
//    {
//    case EArmType_Warrior:
//        { 
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    float attackMod = 0.3;
//                    int32 exactMod  = 1;
//
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.attack.base = pValue->base * attackMod;
//                        fightAttri.exact.base  = pValue->base * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.attack.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                        fightAttri.exact.item    += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                        fightAttri.exact.status  += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.attack.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                        fightAttri.exact.skill   += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.attack.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                        fightAttri.exact.title   += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.attack.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                        fightAttri.exact.mount   += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.attack.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                        fightAttri.exact.suit    += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    int32 dodgeMod  = 2;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.dodge.base = pValue->base * dodgeMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod  = 5;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                }
//                break;
//            }
//        }
//        break;
//    case EArmType_Mage:
//        {
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    int32 exactMod = 2;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.exact.base = pValue->base * exactMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    int32 dodgeMod = 2;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.dodge.base = pValue->base * dodgeMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod = 5;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                    float  attackMod = 0.4;
//                    uint32 energyMod = 17;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.attack.base = pValue->base * attackMod; 
//                        fightAttri.energyMax.base = pValue->base * energyMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.attack.item    += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                        fightAttri.energyMax.item += pValue->GetPartFinal( ECustomDataPart_item   ) * energyMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.attack.status    += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                        fightAttri.energyMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * energyMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.attack.skill    += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                        fightAttri.energyMax.skill += pValue->GetPartFinal( ECustomDataPart_skill  ) * energyMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.attack.title    += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                        fightAttri.energyMax.title += pValue->GetPartFinal( ECustomDataPart_title  ) * energyMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.attack.mount    += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                        fightAttri.energyMax.mount += pValue->GetPartFinal( ECustomDataPart_mount  ) * energyMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.attack.suit    += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                        fightAttri.energyMax.suit += pValue->GetPartFinal( ECustomDataPart_suit   ) * energyMod;
//                    }
//                }
//                break;
//            }
//        }
//        break;
//    case EArmType_Taoist:
//        {
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    int32 exactMod = 2;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.exact.base = pValue->base * exactMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    int32 dodgeMod = 2;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.dodge.base = pValue->base * dodgeMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod = 5;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                    float  attackMod = 0.3;
//                    uint32 energyMod = 17;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.attack.base = pValue->base * attackMod; 
//                        fightAttri.energyMax.base = pValue->base * energyMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.attack.item    += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                        fightAttri.energyMax.item += pValue->GetPartFinal( ECustomDataPart_item   ) * energyMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.attack.status    += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                        fightAttri.energyMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * energyMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.attack.skill    += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                        fightAttri.energyMax.skill += pValue->GetPartFinal( ECustomDataPart_skill  ) * energyMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.attack.title    += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                        fightAttri.energyMax.title += pValue->GetPartFinal( ECustomDataPart_title  ) * energyMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.attack.mount    += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                        fightAttri.energyMax.mount += pValue->GetPartFinal( ECustomDataPart_mount  ) * energyMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.attack.suit    += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                        fightAttri.energyMax.suit += pValue->GetPartFinal( ECustomDataPart_suit   ) * energyMod;
//                    }
//                }
//                break;
//            }
//        }
//        break;
//    case EArmType_Assassin:
//        { 
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    float attackMod = 0.4;
//                    int32 exactMod  = 1;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.attack.base = pValue->base * attackMod; 
//                        fightAttri.exact.base  = pValue->base * exactMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.attack.item += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                        fightAttri.exact.item  += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                        fightAttri.exact.status  += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.attack.skill += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                        fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.attack.title += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                        fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.attack.mount += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                        fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.attack.suit += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                        fightAttri.exact.suit  += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    int32 dodgeMod  = 2;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.dodge.base = pValue->base * dodgeMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod  = 5;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                }
//                break;
//            }
//        }
//        break;
//    case EArmType_Hunter:
//        {
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    int32 exactMod = 2;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.exact.base = pValue->base * exactMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    float attackMod = 0.4;
//                    int32 dodgeMod  = 1;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.attack.base = pValue->base * attackMod; 
//                        fightAttri.dodge.base  = pValue->base * dodgeMod;  
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.attack.item += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                        fightAttri.dodge.item  += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                        fightAttri.dodge.status  += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.attack.skill += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                        fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.attack.title += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                        fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.attack.mount += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                        fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.attack.suit += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                        fightAttri.dodge.suit  += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod  = 5;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.hpMax.base = pValue->base * hpMaxMod;   
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                }
//                break;
//            }
//        }
//        break;
//    case EArmType_Sniper:
//        {
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    int32 exactMod = 2;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.exact.base = pValue->base * exactMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    float attackMod = 0.3;
//                    int32 dodgeMod  = 1;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.attack.base = pValue->base * attackMod; 
//                        fightAttri.dodge.base  = pValue->base * dodgeMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.attack.item += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                        fightAttri.dodge.item  += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                        fightAttri.dodge.status  += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.attack.skill += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                        fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.attack.title += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                        fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.attack.mount += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                        fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.attack.suit += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                        fightAttri.dodge.suit  += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod  = 5;
//                    if ( _HAS_FLAG( part, ECustomDataPart_base ) )
//                    {
//                        fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_item ) )
//                    {
//                        fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_status ) )
//                    {
//                        fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_skill ) )
//                    {
//                        fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_title ) )
//                    {
//                        fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_mount ) )
//                    {
//                        fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                    }
//                    if ( _HAS_FLAG( part, ECustomDataPart_suit ) )
//                    {
//                        fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                }
//                break;
//            }
//        }
//        break;
//    }
//}

//void ProcessCharInfo::Effect( uint8 type, uint16 part, SAttrType0* pValue, uint16 armType, SCharFightAttr& fightAttri )
//{
//    if ( pValue == NULL )
//    { return; }
//
//    switch ( armType )
//    {
//    case EArmType_Warrior:
//        { 
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    float attackMod = 0.3;
//                    int32 exactMod  = 1;
//
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.exact.base  = pValue->base * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.attack.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.exact.item    += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.exact.status  += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.attack.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.exact.skill   += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.attack.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.exact.title   += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.attack.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.exact.mount   += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.attack.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                            fightAttri.exact.suit    += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.attack.base    = pValue->base * attackMod;
//                            fightAttri.attack.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.attack.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.attack.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.attack.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.attack.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//
//                            fightAttri.exact.base     = pValue->base * exactMod;
//                            fightAttri.exact.item    += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                            fightAttri.exact.status  += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                            fightAttri.exact.skill   += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                            fightAttri.exact.title   += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                            fightAttri.exact.mount   += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                            fightAttri.exact.suit    += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    int32 dodgeMod  = 2;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.dodge.base = pValue->base * dodgeMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.dodge.base = pValue->base * dodgeMod; 
//                            fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                            fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                            fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod  = 5;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                }
//                break;
//            }
//        }
//        break;
//    case EArmType_Mage:
//        {
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    int32 exactMod = 2;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.exact.base = pValue->base * exactMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.exact.base = pValue->base * exactMod; 
//                            fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                            fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                            fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                            fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                            fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                            fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    int32 dodgeMod = 2;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.dodge.base = pValue->base * dodgeMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.dodge.base = pValue->base * dodgeMod; 
//                            fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                            fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                            fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod = 5;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                    float  attackMod = 0.4;
//                    uint32 energyMod = 17;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.energyMax.base = pValue->base * energyMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.attack.item    += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.energyMax.item += pValue->GetPartFinal( ECustomDataPart_item   ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.attack.status    += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.energyMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.attack.skill    += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.energyMax.skill += pValue->GetPartFinal( ECustomDataPart_skill  ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.attack.title    += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.energyMax.title += pValue->GetPartFinal( ECustomDataPart_title  ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.attack.mount    += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.energyMax.mount += pValue->GetPartFinal( ECustomDataPart_mount  ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.attack.suit    += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                            fightAttri.energyMax.suit += pValue->GetPartFinal( ECustomDataPart_suit   ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.attack.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.attack.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.attack.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.attack.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.attack.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//
//                            fightAttri.energyMax.base   = pValue->base * energyMod; 
//                            fightAttri.energyMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * energyMod;
//                            fightAttri.energyMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * energyMod;
//                            fightAttri.energyMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * energyMod;
//                            fightAttri.energyMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * energyMod;
//                            fightAttri.energyMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * energyMod;
//                            fightAttri.energyMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * energyMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            }
//        }
//        break;
//    case EArmType_Taoist:
//        {
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    int32 exactMod = 2;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.exact.base = pValue->base * exactMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.exact.base = pValue->base * exactMod; 
//                            fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                            fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                            fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                            fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                            fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                            fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    int32 dodgeMod = 2;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.dodge.base = pValue->base * dodgeMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.dodge.base = pValue->base * dodgeMod; 
//                            fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                            fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                            fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod = 5;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                    float  attackMod = 0.3;
//                    uint32 energyMod = 17;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.energyMax.base = pValue->base * energyMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.attack.item    += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.energyMax.item += pValue->GetPartFinal( ECustomDataPart_item   ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.attack.status    += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.energyMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.attack.skill    += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.energyMax.skill += pValue->GetPartFinal( ECustomDataPart_skill  ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.attack.title    += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.energyMax.title += pValue->GetPartFinal( ECustomDataPart_title  ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.attack.mount    += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.energyMax.mount += pValue->GetPartFinal( ECustomDataPart_mount  ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.attack.suit    += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                            fightAttri.energyMax.suit += pValue->GetPartFinal( ECustomDataPart_suit   ) * energyMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.attack.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.attack.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.attack.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.attack.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.attack.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//
//                            fightAttri.energyMax.base   = pValue->base * energyMod; 
//                            fightAttri.energyMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * energyMod;
//                            fightAttri.energyMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * energyMod;
//                            fightAttri.energyMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * energyMod;
//                            fightAttri.energyMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * energyMod;
//                            fightAttri.energyMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * energyMod;
//                            fightAttri.energyMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * energyMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            }
//        }
//        break;
//    case EArmType_Assassin:
//        { 
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    float attackMod = 0.4;
//                    int32 exactMod  = 1;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.exact.base  = pValue->base * exactMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.attack.item += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.exact.item  += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.exact.status  += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.attack.skill += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.attack.title += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.attack.mount += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.attack.suit += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                            fightAttri.exact.suit  += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.attack.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.attack.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.attack.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.attack.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.attack.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//
//                            fightAttri.exact.base = pValue->base * exactMod;
//                            fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                            fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                            fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                            fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                            fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                            fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    int32 dodgeMod  = 2;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.dodge.base = pValue->base * dodgeMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.dodge.base = pValue->base * dodgeMod; 
//                            fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                            fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                            fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod  = 5;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                }
//                break;
//            }
//        }
//        break;
//    case EArmType_Hunter:
//        {
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    int32 exactMod = 2;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.exact.base = pValue->base * exactMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.exact.base = pValue->base * exactMod; 
//                            fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                            fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                            fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                            fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                            fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                            fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    float attackMod = 0.4;
//                    int32 dodgeMod  = 1;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        {
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.dodge.base  = pValue->base * dodgeMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.attack.item += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.dodge.item  += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.dodge.status  += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.attack.skill += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.attack.title += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.attack.mount += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.attack.suit += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                            fightAttri.dodge.suit  += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.attack.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.attack.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.attack.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.attack.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.attack.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//
//                            fightAttri.dodge.base = pValue->base * dodgeMod;
//                            fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                            fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                            fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod  = 5;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                }
//                break;
//            }
//        }
//        break;
//    case EArmType_Sniper:
//        {
//            switch ( type )
//            {
//            case EBaseAttr_Strength:
//                {
//                    int32 exactMod = 2;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.exact.base = pValue->base * exactMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.exact.base = pValue->base * exactMod; 
//                            fightAttri.exact.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * exactMod;
//                            fightAttri.exact.status += pValue->GetPartFinal( ECustomDataPart_status ) * exactMod;
//                            fightAttri.exact.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * exactMod;
//                            fightAttri.exact.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * exactMod;
//                            fightAttri.exact.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * exactMod;
//                            fightAttri.exact.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * exactMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Agility:
//                {
//                    float attackMod = 0.3;
//                    int32 dodgeMod  = 1;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        {
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.dodge.base  = pValue->base * dodgeMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.attack.item += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.dodge.item  += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.dodge.status  += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.attack.skill += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.attack.title += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.attack.mount += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.attack.suit += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//                            fightAttri.dodge.suit  += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.attack.base = pValue->base * attackMod; 
//                            fightAttri.attack.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * attackMod;
//                            fightAttri.attack.status += pValue->GetPartFinal( ECustomDataPart_status ) * attackMod;
//                            fightAttri.attack.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * attackMod;
//                            fightAttri.attack.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * attackMod;
//                            fightAttri.attack.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * attackMod;
//                            fightAttri.attack.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * attackMod;
//
//                            fightAttri.dodge.base = pValue->base * dodgeMod;
//                            fightAttri.dodge.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * dodgeMod;
//                            fightAttri.dodge.status += pValue->GetPartFinal( ECustomDataPart_status ) * dodgeMod;
//                            fightAttri.dodge.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * dodgeMod;
//                            fightAttri.dodge.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * dodgeMod;
//                            fightAttri.dodge.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * dodgeMod;
//                            fightAttri.dodge.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * dodgeMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Constitution:
//                {
//                    int32 hpMaxMod  = 5;
//                    switch ( part )
//                    {
//                    case ECustomDataPart_base:
//                        { 
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                        }
//                        break;
//                    case ECustomDataPart_item:
//                        {
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_status:
//                        {
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_skill:
//                        {
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_title:
//                        {
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_mount:
//                        {
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_suit:
//                        {
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    case ECustomDataPart_all:
//                        {
//                            fightAttri.hpMax.base = pValue->base * hpMaxMod; 
//                            fightAttri.hpMax.item   += pValue->GetPartFinal( ECustomDataPart_item   ) * hpMaxMod;
//                            fightAttri.hpMax.status += pValue->GetPartFinal( ECustomDataPart_status ) * hpMaxMod;
//                            fightAttri.hpMax.skill  += pValue->GetPartFinal( ECustomDataPart_skill  ) * hpMaxMod;
//                            fightAttri.hpMax.title  += pValue->GetPartFinal( ECustomDataPart_title  ) * hpMaxMod;
//                            fightAttri.hpMax.mount  += pValue->GetPartFinal( ECustomDataPart_mount  ) * hpMaxMod;
//                            fightAttri.hpMax.suit   += pValue->GetPartFinal( ECustomDataPart_suit   ) * hpMaxMod;
//                        }
//                        break;
//                    }
//                }
//                break;
//            case EBaseAttr_Intelligence:
//                {
//                }
//                break;
//            }
//        }
//        break;
//    }
//}


void ProcessCharInfo::BaseAttrEffectFightAttr( uint8 baseType, uint16 part, SBaseAttrType& baseValue, uint16 armType, SCharFightAttr& fightAttr, bool bAdd /*= true*/ )
{
    int8 addOrSub = bAdd ? 1 : -1;

#define DECORATE_RESULT( baseValue )  baseValue * addOrSub

    SArmsParamModulusExtend* pArmsParamModulusExtend = theDataCenter.GetArmsParamModulus(armType);
    if ( NULL == pArmsParamModulusExtend )
    { return ; }

    switch ( baseType )
    {
    case EBaseAttr_Strength:
        {// 力量影响人物 物理攻击
            float fPhysicsAttackMod = pArmsParamModulusExtend->baseFightAttr.fStrengthToPhysicsAttack;

            switch ( part )
            {
            case ECustomDataPart_base:
                { fightAttr.attackPhysics.base = baseValue.base * fPhysicsAttackMod; }
                break;
            case ECustomDataPart_assign:
                { fightAttr.attackPhysics.assign = baseValue.assign * fPhysicsAttackMod; }
                break;
            case ECustomDataPart_item:
                { fightAttr.attackPhysics.item   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_item   ) * fPhysicsAttackMod ); }
                break;
            case ECustomDataPart_status:
                { fightAttr.attackPhysics.status += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_status ) * fPhysicsAttackMod ); }
                break;
            case ECustomDataPart_skill:
                { fightAttr.attackPhysics.skill  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_skill  ) * fPhysicsAttackMod ); }
                break;
            case ECustomDataPart_title:
                { fightAttr.attackPhysics.title  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_title  ) * fPhysicsAttackMod ); }
                break;
            case ECustomDataPart_pet:
                { fightAttr.attackPhysics.pet    += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_pet  )   * fPhysicsAttackMod ); }
                break;
            case ECustomDataPart_suit:
                { fightAttr.attackPhysics.suit   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_suit   ) * fPhysicsAttackMod ); }
                break;
			case ECustomDataPart_hero:
				{ fightAttr.attackPhysics.hero   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_hero   ) * fPhysicsAttackMod ); }
				break;
			case ECustomDataPart_lieutenant:
				{ fightAttr.attackPhysics.lieutenant   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_lieutenant   ) * fPhysicsAttackMod ); }
				break;
            }
        }
        break;
    case EBaseAttr_Agility:
        {// 敏捷影响人物的 命中 闪避 暴击 韧性
            float fExactMod  = pArmsParamModulusExtend->baseFightAttr.fAgilityToExact;
            float fDodgeMod  = pArmsParamModulusExtend->baseFightAttr.fAgilityToDodge;
            float fCriticalMod  = pArmsParamModulusExtend->baseFightAttr.fAgilityToCritical * DEF_PERCENT;
            float fTenacityMod  = pArmsParamModulusExtend->baseFightAttr.fAgilityToTenacity * DEF_PERCENT;

            switch ( part )
            {
            case ECustomDataPart_base:
                { 
                    fightAttr.exact.base = baseValue.base * fExactMod;
                    fightAttr.dodge.base = baseValue.base * fDodgeMod; 
                    fightAttr.critical.base = baseValue.base * fCriticalMod; 
                    fightAttr.tenacity.base = baseValue.base * fTenacityMod; 
                }
                break;
            case ECustomDataPart_assign:
                { 
                    fightAttr.exact.assign = baseValue.assign * fExactMod;
                    fightAttr.dodge.assign = baseValue.assign * fDodgeMod; 
                    fightAttr.critical.assign = baseValue.assign * fCriticalMod; 
                    fightAttr.tenacity.assign = baseValue.assign * fTenacityMod; 
                }
                break;
            case ECustomDataPart_item:
                {
                    fightAttr.exact.item   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_item   ) * fExactMod );
                    fightAttr.dodge.item   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_item   ) * fDodgeMod );
                    fightAttr.critical.item   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_item   ) * fCriticalMod );
                    fightAttr.tenacity.item   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_item   ) * fTenacityMod );
                }
                break;
            case ECustomDataPart_status:
                {
                    fightAttr.exact.status += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_status ) * fExactMod );
                    fightAttr.dodge.status += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_status ) * fDodgeMod );
                    fightAttr.critical.status += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_status ) * fCriticalMod );
                    fightAttr.tenacity.status += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_status ) * fTenacityMod );
                }
                break;
            case ECustomDataPart_skill:
                {
                    fightAttr.exact.skill  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_skill  ) * fExactMod );
                    fightAttr.dodge.skill  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_skill  ) * fDodgeMod );
                    fightAttr.critical.skill  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_skill  ) * fCriticalMod );
                    fightAttr.tenacity.skill  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_skill  ) * fTenacityMod );
                }
                break;
            case ECustomDataPart_title:
                {
                    fightAttr.exact.title  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_title  ) * fExactMod );
                    fightAttr.dodge.title  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_title  ) * fDodgeMod );
                    fightAttr.critical.title  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_title  ) * fCriticalMod );
                    fightAttr.tenacity.title  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_title  ) * fTenacityMod );
                }
                break;
            case ECustomDataPart_pet:
                {
                    fightAttr.exact.pet  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_pet  ) * fExactMod );
                    fightAttr.dodge.pet  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_pet  ) * fDodgeMod );
                    fightAttr.critical.pet  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_pet  ) * fCriticalMod );
                    fightAttr.tenacity.pet  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_pet  ) * fTenacityMod );
                }
                break;
            case ECustomDataPart_suit:
                {
                    fightAttr.exact.suit   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_suit   ) * fExactMod );
                    fightAttr.dodge.suit   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_suit   ) * fDodgeMod );
                    fightAttr.critical.suit   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_suit   ) * fCriticalMod );
                    fightAttr.tenacity.suit   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_suit   ) * fTenacityMod );
                }
                break;
			case ECustomDataPart_hero:
				{
					fightAttr.exact.hero   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_hero   ) * fExactMod );
					fightAttr.dodge.hero   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_hero   ) * fDodgeMod );
					fightAttr.critical.hero   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_hero   ) * fCriticalMod );
					fightAttr.tenacity.hero   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_hero   ) * fTenacityMod );
				}
				break;
			case ECustomDataPart_lieutenant:
				{
					fightAttr.exact.lieutenant   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_lieutenant   ) * fExactMod );
					fightAttr.dodge.lieutenant   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_lieutenant   ) * fDodgeMod );
					fightAttr.critical.lieutenant   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_lieutenant   ) * fCriticalMod );
					fightAttr.tenacity.lieutenant   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_lieutenant   ) * fTenacityMod );
				}
				break;
            }
        }
        break;
    case EBaseAttr_Stamina:
        {//耐力影响人物 血量上限 物防 魔防
            float fHPMaxMod  = pArmsParamModulusExtend->baseFightAttr.fStaminaToHPMax;
            float fPhysicsDefendMod = pArmsParamModulusExtend->baseFightAttr.fStaminaToPhysicsDefend;
            float fMagicDefendMod   = pArmsParamModulusExtend->baseFightAttr.fStaminaToMagicDefend;

            switch ( part )
            {
            case ECustomDataPart_base:
                { 
                    fightAttr.hpMax.base = baseValue.base * fHPMaxMod; 
                    fightAttr.defendPhysics.base = baseValue.base * fPhysicsDefendMod; 
                    fightAttr.defendMagic.base   = baseValue.base * fMagicDefendMod; 
                }
                break;
            case ECustomDataPart_assign:
                { 
                    fightAttr.hpMax.assign = baseValue.assign * fHPMaxMod; 
                    fightAttr.defendPhysics.assign = baseValue.assign * fPhysicsDefendMod; 
                    fightAttr.defendMagic.assign   = baseValue.assign * fMagicDefendMod; 
                }
                break;
            case ECustomDataPart_item:
                {
                    fightAttr.hpMax.item   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_item   ) * fHPMaxMod );
                    fightAttr.defendPhysics.item   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_item   ) * fPhysicsDefendMod );
                    fightAttr.defendMagic.item     += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_item   ) * fMagicDefendMod );
                }
                break;
            case ECustomDataPart_status:
                {
                    fightAttr.hpMax.status += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_status ) * fHPMaxMod );
                    fightAttr.defendPhysics.status += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_status ) * fPhysicsDefendMod );
                    fightAttr.defendMagic.status   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_status ) * fMagicDefendMod );
                }
                break;
            case ECustomDataPart_skill:
                {
                    fightAttr.hpMax.skill  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_skill  ) * fHPMaxMod );
                    fightAttr.defendPhysics.skill  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_skill  ) * fPhysicsDefendMod );
                    fightAttr.defendMagic.skill    += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_skill  ) * fMagicDefendMod );
                }
                break;
            case ECustomDataPart_title:
                {
                    fightAttr.hpMax.title  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_title  ) * fHPMaxMod );
                    fightAttr.defendPhysics.title += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_title  ) * fPhysicsDefendMod );
                    fightAttr.defendMagic.title   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_title  ) * fMagicDefendMod );
                }
                break;
            case ECustomDataPart_pet:
                {
                    fightAttr.hpMax.pet  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_pet  ) * fHPMaxMod );
                    fightAttr.defendPhysics.pet += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_pet  ) * fPhysicsDefendMod );
                    fightAttr.defendMagic.pet   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_pet  ) * fMagicDefendMod );
                }
                break;
            case ECustomDataPart_suit:
                {
                    fightAttr.hpMax.suit   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_suit   ) * fHPMaxMod );
                    fightAttr.defendPhysics.suit += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_suit   ) * fPhysicsDefendMod );
                    fightAttr.defendMagic.suit   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_suit   ) * fMagicDefendMod );
                }
                break;
			case ECustomDataPart_hero:
				{
					fightAttr.hpMax.hero   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_hero   ) * fHPMaxMod );
					fightAttr.defendPhysics.hero += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_hero   ) * fPhysicsDefendMod );
					fightAttr.defendMagic.hero   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_hero   ) * fMagicDefendMod );
				}
				break;
			case ECustomDataPart_lieutenant:
				{
					fightAttr.hpMax.lieutenant   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_lieutenant   ) * fHPMaxMod );
					fightAttr.defendPhysics.lieutenant += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_lieutenant   ) * fPhysicsDefendMod );
					fightAttr.defendMagic.lieutenant   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_lieutenant   ) * fMagicDefendMod );
				}
				break;
            }
        }
        break;
    case EBaseAttr_Intelligence:
        {// 智力影响人物 法术攻击
            float fMagicAttackMod = pArmsParamModulusExtend->baseFightAttr.fIntelligenceToMagicAttack;

            switch ( part )
            {
            case ECustomDataPart_base:
                { fightAttr.attackMagic.base = baseValue.base * fMagicAttackMod; }
                break;
            case ECustomDataPart_assign:
                { fightAttr.attackMagic.assign = baseValue.assign * fMagicAttackMod; }
                break;
            case ECustomDataPart_item:
                { fightAttr.attackMagic.item   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_item   ) * fMagicAttackMod ); }
                break;
            case ECustomDataPart_status:
                { fightAttr.attackMagic.status += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_status ) * fMagicAttackMod ); }
                break;
            case ECustomDataPart_skill:
                { fightAttr.attackMagic.skill  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_skill  ) * fMagicAttackMod ); }
                break;
            case ECustomDataPart_title:
                { fightAttr.attackMagic.title  += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_title  ) * fMagicAttackMod ); }
                break;
            case ECustomDataPart_pet:
                { fightAttr.attackMagic.pet    += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_pet  ) * fMagicAttackMod );   }
                break;
            case ECustomDataPart_suit:
                { fightAttr.attackMagic.suit   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_suit ) * fMagicAttackMod ); }
                break;
			case ECustomDataPart_hero:
				{ fightAttr.attackMagic.hero   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_hero ) * fMagicAttackMod ); }
				break;
			case ECustomDataPart_lieutenant:
				{ fightAttr.attackMagic.lieutenant   += DECORATE_RESULT( baseValue.GetPartFinal( ECustomDataPart_lieutenant ) * fMagicAttackMod ); }
				break;
            }
        }
        break;
    }
}