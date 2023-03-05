public:

    // 技能
    bool   OnSkillLevelUp();

    SkillBag* GetSkillBagBySkill( ItemDefine::SItemSkill* pSkill );

    CDTIME StartSkillCoolDown( ItemDefine::SItemSkill* pSkill );
    CDTIME StartSkillCoolDown( unsigned short ustSkillID, short stSkillLevel );    

    void   ClearSkillCollDown( unsigned short ustSkillID, bool bSendToClient = true );

    bool   CanLearnSkill( int nSkillId, int nLevel );
    bool   LearnSkill( int iWhichSkill, int level=1, bool bCheckSkillExp=true,bool bMessageDialog=true, bool bRecalc=true );  // 学习技能
    bool   ForgetSkill( int iWhichSkill,bool bMessageDialog = true ); // 遗忘技能

    bool   CanLearnXinFa( int nXinFaId, int nLevel );
    bool   LearnXinFa   ( int iWhichXinFa, int nLevel=1, bool bCheckCondition=true, bool bMessageDialog=true );
    bool   ForgetXinFa  ( int iWhichXinFa );

    void   GetXinFaSkillEffect( uint16 nSkillId, OUT int* pSkillAttr );
    void   GetXinFaSkillEffect( const ItemDefine::SItemSkill* pSkill, OUT int* pSkillAttr );
    int    GetXinFaSkillEffectValue( uint16 nSkillId, int attrType );
    int    GetXinFaSkillEffectValue( const ItemDefine::SItemSkill* pSkill, int attrType );

    virtual uint32 ProcessCaptureSkill  ( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster );
    virtual uint32 ProcessSuckFetchSkill( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster );
    virtual uint32 ProcessBreakOutSkill ( const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster );
    virtual uint32 ProcessCallGraphicSkill( const ItemDefine::SItemSkill* pSkillConfig );
    virtual uint32 ProcessTeamRelive( const ItemDefine::SItemSkill* pSkillConfig );
    virtual uint32 ProcessXPSkill ( const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster );
    virtual uint32 ProcessTeamFlyToHeader( const ItemDefine::SItemSkill* pSkillConfig );
    virtual uint32 ProcessPetActive      ( const ItemDefine::SItemSkill* pSkillConfig );

    void   ApplyPassiveSkillToChar      ( const ItemDefine::SItemSkill* pSkill );    
    void   ApplyPassiveSkillToCharEquip ( const ItemDefine::SItemSkill* pSkill );
    void   ApplyPassiveSkillsToChar     ();
    void   ApplyTalentXinFaToChar       ();
