
public:

    bool IsSummonPetFull()
    {
        for (int i=0;i<CharSummonPetMaxCount; ++i)
        {
            if ( InvalidGameObjectId == m_xSummonPets[i].petId)
            { return false; }
        }

        return true;
    }

    bool AddSummonPet(SSummonPet& pet)
    {
        for (int i=0;i<CharSummonPetMaxCount; ++i)
        {
            if ( InvalidGameObjectId == m_xSummonPets[i].petId)
            {
                m_xSummonPets[i] = pet;
                return true;
            }
        }

        return false;
    }

    SSummonPet* GetSummonPet(uint8 i) 
    { 
        if ( i >= CharSummonPetMaxCount)
        { return NULL; }

        return &m_xSummonPets[i]; 
    }

    void  KillSummonPet(uint16 skillId); 
    bool  HaveSummonPet()              ;
    bool  HaveSummonPet(uint16 skillId);
    bool  IsSelfSummonPet(GameObjectId petId) ;
    void  LostSummonPet(GameObjectId petId)   ;

    short GetSkillPetAIType(GameObjectId petId);
    void  SetSkillPetAIType( GameObjectId petId, uint8 petType );

   MonsterBaseEx* GetMonsterSummonPet()  ;

    // 捕获宠物
    bool  HaveCapturePet()								  { return _capturePetId > -1;      }
    void  SetCapturePetId( GameObjectId capturePetId)    { _capturePetId = capturePetId;   }
    GameObjectId GetCapturePetId()						  { return _capturePetId;           }
    void  LostCapturePet()								  { _capturePetId = -1; _capturePetAIType = ePetCommandAI; }
    uint8 GetCapturePetAIType()							  { return _capturePetAIType;       }
    void  SetCapturePetAIType( uint8 sPetAIType )		  { _capturePetAIType = sPetAIType; }    

protected:
    SSummonPet     m_xSummonPets[CharSummonPetMaxCount];  // 技能召唤宠物

    GameObjectId   _capturePetId;        // 捕获宠物的ID
    uint8           _capturePetAIType;    // 捕获当前AI类型

