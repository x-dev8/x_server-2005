
public:
    
    // ��ʼ��Lua�ű�
    void InitLuaScript();

    // ��ʼ���ű�����
    void ProcessInitLuaFunction();

    // �ͷŽű�
    void ReleaseLuaScript();

    // ����Lua����
    virtual bool RegisterLuaFunction();

    // ����lua�ű�ִ��
    virtual void ProcessLuaRunThinking();

    // ���lua����
    LuaFunction<int> GetLuaFunction( LPSTR cFuncName ) { return m_xLuaScript->GetGlobal( cFuncName ); }

    // ��������LUA�ص�����֧�� ����LUA�ű������ߵ�ID��ʩ�ŵļ���ID����ɵ��˺�
    virtual void LuaBeAttackedCallBack( GameObjectId nAttackerID, int nSkillID, int nSkillLevel, int nDamage ); 

    // ���������ص�LUA����
    virtual void LuaDeathCallBack( GameObjectId nKillerID ); 

public:

    // ������ʱ��
    void LuaTimerStart( unsigned int nIndex, int nSpaceTime, unsigned int nStartTime = 0 );

    // ֹͣ��ʱ��
    void LuaTimerStop( unsigned int nIndex );

    // �ж��Ƿ���Ӧ�˶�ʱ��
    bool LuaTimerDone( unsigned int nIndex, int bContinue );

    // �Ƿ�ʼ�˶�ʱ��
    bool LuaTimerHaveStart( unsigned int nIndex );

    // int����
    void SetParamValue( unsigned int nIndex, int nValue );
    int GetParamValue( unsigned int nIndex );

    // ���HP MP
    int LuaGetHP() { return GetHP(); }
    int LuaGetMP() { return GetMP(); }

    // ˲��ʧѪ
    void LoseHPInstant( int nValue );

    // ˲��ʧħ
    void LoseMPInstant( int nValue );

    // ˲���Ѫ
    void RestoreHPInstant( int nValue ); 

    // ˲���ħ 
    void RestoreMPInstant( int nValue );  

    // ʹ�ü���
    void LuaUseSkill ( int nSkillID, int nSkillLevel );
    void LuaTryAttack( GameObjectId nID, int nSkillID, int nSkillLevel );

    // ����˵��
    void LuaSay( int nType, const char* szValue );

    // ���һ���漴��
    int GetRandNumber( int nValue );

    // ��õȼ�
    int LuaGetLevel() { return GetLevel();  }

    uint32 LuaGetHPMax() { return GetHPMax(); }

    uint32 LuaGetMPMax() { return GetMPMax(); }

    // ���Ŀ������
    const char*  GetTargetName( GameObjectId nID = InvalidGameObjectId );

    // ���Ŀ��HP
    int GetTargetHP     ( GameObjectId nID = InvalidGameObjectId );

    // ���Ŀ��MP
    int GetTargetMP     ( GameObjectId nID = InvalidGameObjectId );

    // ���Ŀ�����HP
    int GetTargetHPMax  ( GameObjectId nID = InvalidGameObjectId );

    // ���Ŀ�����MP
    int GetTargetMPMax  ( GameObjectId nID = InvalidGameObjectId );

    // ���Ŀ��ȼ�
    int GetTargetLevel  ( GameObjectId nID = InvalidGameObjectId );

    // ���Ŀ��ĳ��ֵ
    int GetTargetEnmity ( GameObjectId nID = InvalidGameObjectId );

    // ���Ŀ����˺�ֵ
    int GetTargetDamage ( GameObjectId nID = InvalidGameObjectId );

    // ����Ŀ��ĳ��ֵ
    void SetTargetEnmity( int nValue,  GameObjectId nID = InvalidGameObjectId  );

    // �������Ŀ��ļ�¼
    int GetTargetDistance   ( GameObjectId nID = InvalidGameObjectId );

    // ���Ŀ��ְҵ
    int GetTargetProfession ( GameObjectId nID = InvalidGameObjectId );

    // ���Ŀ����������
    float LuaGetTargetPosX  ( GameObjectId nID = InvalidGameObjectId );
    float LuaGetTargetPosY  ( GameObjectId nID = InvalidGameObjectId );

    // ����Լ��Ķ�̬ID
    GameObjectId LuaGetSelfID() { return GetID(); }
    // �������ID
    GameObjectId LuaGetLockID() { return GetLockID(); }

    // ��������ID
    void LuaSetLockID( GameObjectId nID ) { SetLockID( nID ); }

    // ������ʧ
    void LuaKillTarget( GameObjectId nID = InvalidGameObjectId );
    void LuaMonsterMurder() { CharacterMurder(); }

    // �ٻ�����
    void LuaSummonMonster( int nMonsterID, int nCount, float fRadius, int nFightCamp, int nCountry, int nForce, int nRouteID );
    void LuaSummonMonsterPos( int nMonsterID, float fX, float fY, int nFightCamp, int nCountry, int nForce, int nRouteID );

    // ������ʱ, ��Χ�Ĺ��ﶼ����
    void LuaMAlarmWhenBeAttack( unsigned int nDistance, bool bSameMonsterID = false, bool bSamePhyle = false );

    // ����ְҵ������ID
    GameObjectId GetPlayerIdByProfession( int nProfession );
    // ���ݵȼ�������ID
    GameObjectId GetPlayerIdByLevel( int nMinLevel, int nMaxLevel );
    // ����Ѫ��������ID
    GameObjectId GetPlayerIdByHp( int nMinHp, int nMaxHp );
    // ����MP������ID
    GameObjectId GetPlayerIdByMp( int nMinMp, int nMaxMp );

    // �����Χ����ID
    GameObjectId LuaGetMonsterIdByType( int nType );
    GameObjectId LuaGetMonsterIdByID  ( int nID   );
	int LuaGetIDByMonsterId(GameObjectId ID);

    // �������BUFF 
    void LuaAddStatusBuff   ( int statusId, int statusLevel );
    void LuaClearStatusBuff ( int statusId );
    void LuaAddTargetStatusBuff   ( int statusId, int statusLevel );
    void LuaClearStatusBuffByType ( int statusType );
    bool LuaIsHaveStatus          ( int statusId );
    bool LuaIsTargetHaveStatus    ( int statusId, GameObjectId nTargetId = InvalidGameObjectId );

    // ����
    void LuaPlayAnim    ( const char* szName, const char* szEndName, int nTimes );
    void LuaPlayScene   ( int nSceneID );

    void LuaTargetPlayAnim  ( GameObjectId nID, const char* szName, const char* szEndName, int nTimes );
    void LuaTargetPlayScene ( GameObjectId nID, int nSceneID );

	// ��ó���б�ID,���ӳ��ֵ,���ֵΪ0Ҳ����
	void LuaGetEnmityListIDNoExcept ( float fDistance );
    // ��ó���б�ID
    void LuaGetEnmityListID ( float fDistance );

    // �����Χ�����б�ID
    void LuaGetMonsterListID( float fDistance );

    // �ƶ���ĳһ��
    void LuaMoveToPoint( float fX, float fY );

    // �Ƿ񵽴�ָ��λ��( nDistance ��ʾ��ɫ��ָ��λ��֮���ƫ��ֵ��Ĭ��Ϊ0 )
    bool IsInPointRange( int xPos, int yPos, float fDistance = 0.0f );

    // �ı����״̬
    void LuaChangeMonsterStatus( int nMosnterID, int nMonsterCount, int nMonsterStatusID );

    // �������
    void LuaDropItemPackage ( int nDropPackIndex );

    // �����ƶ���Ŀ���
    void LuaMoveBackToAttacker( GameObjectId nAttackerID, int nDistance );
	//���ĳ����ɫ�ı���ֵ
	int GetTargetVar(int varid ,GameObjectId nID = InvalidGameObjectId);
	//����ĳ����ɫ�ı���ֵ
	void SetTargetVar(int varid,int _value,int nOp,int needsend,GameObjectId nID = InvalidGameObjectId);
	//����ٻ���������id
	 GameObjectId LuaGetMasterId() ;

protected:
    bool m_bLuaScriptLoaded;

    // ����Lua������
    LuaStateOwner m_xLuaScript; 

    // Lua�ű���ʱ��
    GameTimerEx m_xLuaTimer[ AiDefine::LuaTimerCount ];

    // ��������
    int m_nParamValue[ AiDefine::LuaValueArrayCount ];
