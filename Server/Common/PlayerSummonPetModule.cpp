#include "GamePlayer.h"
#include "ShareData.h"
#include "MonsterBaseEx.h"

void GamePlayer::KillSummonPet(uint16 skillId)
{
    for (int i=0;i<CharSummonPetMaxCount; ++i)
    {
        if (m_xSummonPets[i].skillId == skillId)
        {
            BaseCharacter* pSummonMonsterChar = theRunTimeData.GetCharacterByID(m_xSummonPets[i].petId);
            if( pSummonMonsterChar != NULL && static_cast<MonsterBaseEx*>(pSummonMonsterChar)->IsPet())
            { // ÕÙ»½¹ÖÍË³ö
                pSummonMonsterChar->SetDead();

                MsgExit exit;
                exit.header.stID = pSummonMonsterChar->GetID();
                pSummonMonsterChar->OnExit(&exit);
            }

            m_xSummonPets[i].Clear();
        }
    }
}

bool  GamePlayer::HaveSummonPet() 
{ 
    for (int i=0;i<CharSummonPetMaxCount; ++i)
    {
        if (m_xSummonPets[i].petId != InvalidGameObjectId)
        {
            return true;
        }
    }

    return false;
}

bool  GamePlayer::HaveSummonPet(uint16 skillId) 
{ 
    for (int i=0;i<CharSummonPetMaxCount; ++i)
    {
        if (m_xSummonPets[i].skillId == skillId)
        {
            return true;
        }
    }

    return false;
}

bool  GamePlayer::IsSelfSummonPet(GameObjectId petId) 
{ 
    for (int i=0;i<CharSummonPetMaxCount; ++i)
    {
        if (m_xSummonPets[i].petId == petId)
        {
            return true; 
        }
    }

    return false;
}

void  GamePlayer::LostSummonPet(GameObjectId petId) 
{ 
    for (int i=0;i < CharSummonPetMaxCount; ++i)
    {
        if (m_xSummonPets[i].petId == petId)
        {
            BaseCharacter* pSummonMonsterChar = theRunTimeData.GetCharacterByID(m_xSummonPets[i].petId);
            if( pSummonMonsterChar != NULL && static_cast<MonsterBaseEx*>(pSummonMonsterChar)->IsPet())
            { // ÕÙ»½¹ÖÍË³ö
                pSummonMonsterChar->SetDead();

                MsgExit exit;
                exit.header.stID = pSummonMonsterChar->GetID();
                pSummonMonsterChar->OnExit(&exit);
            }

            m_xSummonPets[i].Clear();
        }
    }
}


MonsterBaseEx*  GamePlayer::GetMonsterSummonPet()
{
    for (int i=0;i<CharSummonPetMaxCount; ++i)
    {
        MonsterBaseEx* pAiChar = (MonsterBaseEx*) theRunTimeData.GetCharacterByID( m_xSummonPets[i].petId );
        if ( pAiChar != NULL && pAiChar->IsPet() && !pAiChar->IsIllusionChar() )
        { return pAiChar; }
    }
    return NULL;
}

short GamePlayer::GetSkillPetAIType(GameObjectId petId)               
{ 
    for (int i=0;i<CharSummonPetMaxCount; ++i)
    {
        if (m_xSummonPets[i].petId == petId)
        {
            return m_xSummonPets[i].petAIType; 
        }
    }

    return ePetCommandAI;
}

void  GamePlayer::SetSkillPetAIType( GameObjectId petId, uint8 petType ) 
{  
    for (int i=0;i<CharSummonPetMaxCount; ++i)
    {
        if (m_xSummonPets[i].petId == petId)
        {
            m_xSummonPets[i].petAIType = petType; 

            switch ( petType )
            {
            case ePetAttackAI:
                break;
            case ePetDefendAI:
                {
                    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_xSummonPets[i].petId );
                    if ( pChar != NULL && pChar->IsMonster() )
                    {
                        MonsterBaseEx* pMonsterPet = static_cast< MonsterBaseEx* >( pChar );
                        pMonsterPet->SetAiStatus( AiDefine::ThinkingFollowMaster );
                        pMonsterPet->ClearEnmity( true );
                    }
                }
                break;
            }
        }
    }
}