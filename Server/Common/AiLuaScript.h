
public:
    
    // 初始化Lua脚本
    void InitLuaScript();

    // 初始化脚本函数
    void ProcessInitLuaFunction();

    // 释放脚本
    void ReleaseLuaScript();

    // 导出Lua函数
    virtual bool RegisterLuaFunction();

    // 处理lua脚本执行
    virtual void ProcessLuaRunThinking();

    // 获得lua函数
    LuaFunction<int> GetLuaFunction( LPSTR cFuncName ) { return m_xLuaScript->GetGlobal( cFuncName ); }

    // 被攻击的LUA回调函数支持 告诉LUA脚本攻击者的ID，施放的技能ID，造成的伤害
    virtual void LuaBeAttackedCallBack( GameObjectId nAttackerID, int nSkillID, int nSkillLevel, int nDamage ); 

    // 怪物死亡回调LUA函数
    virtual void LuaDeathCallBack( GameObjectId nKillerID ); 

public:

    // 开启定时器
    void LuaTimerStart( unsigned int nIndex, int nSpaceTime, unsigned int nStartTime = 0 );

    // 停止定时器
    void LuaTimerStop( unsigned int nIndex );

    // 判断是否响应了定时器
    bool LuaTimerDone( unsigned int nIndex, int bContinue );

    // 是否开始了定时器
    bool LuaTimerHaveStart( unsigned int nIndex );

    // int变量
    void SetParamValue( unsigned int nIndex, int nValue );
    int GetParamValue( unsigned int nIndex );

    // 获得HP MP
    int LuaGetHP() { return GetHP(); }
    int LuaGetMP() { return GetMP(); }

    // 瞬间失血
    void LoseHPInstant( int nValue );

    // 瞬间失魔
    void LoseMPInstant( int nValue );

    // 瞬间回血
    void RestoreHPInstant( int nValue ); 

    // 瞬间回魔 
    void RestoreMPInstant( int nValue );  

    // 使用技能
    void LuaUseSkill ( int nSkillID, int nSkillLevel );
    void LuaTryAttack( GameObjectId nID, int nSkillID, int nSkillLevel );

    // 怪物说话
    void LuaSay( int nType, const char* szValue );

    // 获得一个随即数
    int GetRandNumber( int nValue );

    // 获得等级
    int LuaGetLevel() { return GetLevel();  }

    uint32 LuaGetHPMax() { return GetHPMax(); }

    uint32 LuaGetMPMax() { return GetMPMax(); }

    // 获得目标名称
    const char*  GetTargetName( GameObjectId nID = InvalidGameObjectId );

    // 获得目标HP
    int GetTargetHP     ( GameObjectId nID = InvalidGameObjectId );

    // 获得目标MP
    int GetTargetMP     ( GameObjectId nID = InvalidGameObjectId );

    // 获得目标最大HP
    int GetTargetHPMax  ( GameObjectId nID = InvalidGameObjectId );

    // 获得目标最大MP
    int GetTargetMPMax  ( GameObjectId nID = InvalidGameObjectId );

    // 获得目标等级
    int GetTargetLevel  ( GameObjectId nID = InvalidGameObjectId );

    // 获得目标的仇恨值
    int GetTargetEnmity ( GameObjectId nID = InvalidGameObjectId );

    // 获得目标的伤害值
    int GetTargetDamage ( GameObjectId nID = InvalidGameObjectId );

    // 设置目标的仇恨值
    void SetTargetEnmity( int nValue,  GameObjectId nID = InvalidGameObjectId  );

    // 获得锁定目标的记录
    int GetTargetDistance   ( GameObjectId nID = InvalidGameObjectId );

    // 获得目标职业
    int GetTargetProfession ( GameObjectId nID = InvalidGameObjectId );

    // 获得目标怪物的坐标
    float LuaGetTargetPosX  ( GameObjectId nID = InvalidGameObjectId );
    float LuaGetTargetPosY  ( GameObjectId nID = InvalidGameObjectId );

    // 获得自己的动态ID
    GameObjectId LuaGetSelfID() { return GetID(); }
    // 获得锁定ID
    GameObjectId LuaGetLockID() { return GetLockID(); }

    // 设置锁定ID
    void LuaSetLockID( GameObjectId nID ) { SetLockID( nID ); }

    // 怪物消失
    void LuaKillTarget( GameObjectId nID = InvalidGameObjectId );
    void LuaMonsterMurder() { CharacterMurder(); }

    // 召唤怪物
    void LuaSummonMonster( int nMonsterID, int nCount, float fRadius, int nFightCamp, int nCountry, int nForce, int nRouteID );
    void LuaSummonMonsterPos( int nMonsterID, float fX, float fY, int nFightCamp, int nCountry, int nForce, int nRouteID );

    // 被攻击时, 周围的怪物都警觉
    void LuaMAlarmWhenBeAttack( unsigned int nDistance, bool bSameMonsterID = false, bool bSamePhyle = false );

    // 根据职业获得玩家ID
    GameObjectId GetPlayerIdByProfession( int nProfession );
    // 根据等级获得玩家ID
    GameObjectId GetPlayerIdByLevel( int nMinLevel, int nMaxLevel );
    // 根据血量获得玩家ID
    GameObjectId GetPlayerIdByHp( int nMinHp, int nMaxHp );
    // 根据MP获得玩家ID
    GameObjectId GetPlayerIdByMp( int nMinMp, int nMaxMp );

    // 获得周围怪物ID
    GameObjectId LuaGetMonsterIdByType( int nType );
    GameObjectId LuaGetMonsterIdByID  ( int nID   );
	int LuaGetIDByMonsterId(GameObjectId ID);

    // 增加清除BUFF 
    void LuaAddStatusBuff   ( int statusId, int statusLevel );
    void LuaClearStatusBuff ( int statusId );
    void LuaAddTargetStatusBuff   ( int statusId, int statusLevel );
    void LuaClearStatusBuffByType ( int statusType );
    bool LuaIsHaveStatus          ( int statusId );
    bool LuaIsTargetHaveStatus    ( int statusId, GameObjectId nTargetId = InvalidGameObjectId );

    // 动画
    void LuaPlayAnim    ( const char* szName, const char* szEndName, int nTimes );
    void LuaPlayScene   ( int nSceneID );

    void LuaTargetPlayAnim  ( GameObjectId nID, const char* szName, const char* szEndName, int nTimes );
    void LuaTargetPlayScene ( GameObjectId nID, int nSceneID );

	// 获得仇恨列表ID,无视仇恨值,仇恨值为0也加入
	void LuaGetEnmityListIDNoExcept ( float fDistance );
    // 获得仇恨列表ID
    void LuaGetEnmityListID ( float fDistance );

    // 获得周围怪物列表ID
    void LuaGetMonsterListID( float fDistance );

    // 移动到某一点
    void LuaMoveToPoint( float fX, float fY );

    // 是否到达指定位置( nDistance 表示角色与指定位置之间的偏移值，默认为0 )
    bool IsInPointRange( int xPos, int yPos, float fDistance = 0.0f );

    // 改变怪物状态
    void LuaChangeMonsterStatus( int nMosnterID, int nMonsterCount, int nMonsterStatusID );

    // 掉落包裹
    void LuaDropItemPackage ( int nDropPackIndex );

    // 处理移动到目标点
    void LuaMoveBackToAttacker( GameObjectId nAttackerID, int nDistance );
	//获得某个角色的变量值
	int GetTargetVar(int varid ,GameObjectId nID = InvalidGameObjectId);
	//设置某个角色的变量值
	void SetTargetVar(int varid,int _value,int nOp,int needsend,GameObjectId nID = InvalidGameObjectId);
	//获得召唤怪物主人id
	 GameObjectId LuaGetMasterId() ;

protected:
    bool m_bLuaScriptLoaded;

    // 创建Lua解释器
    LuaStateOwner m_xLuaScript; 

    // Lua脚本定时器
    GameTimerEx m_xLuaTimer[ AiDefine::LuaTimerCount ];

    // 变量数组
    int m_nParamValue[ AiDefine::LuaValueArrayCount ];
