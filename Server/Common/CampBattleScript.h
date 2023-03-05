
public:

    // 以下所有nBattleType( 战场类型 )
    // 帮派争夺战( nType = 1 )
    // 国王争夺战( nType = 2 )
    // 青龙争夺战( nType = 3 )
    // 朱雀争夺战( nType = 4 )
    // 野猪大作战( nType = 5 )

    // 获得战场阵营
    virtual int GetBattleCamp();  

    // 获得战场状态
    // 0     // 初始状态 
    // 1     // 报名状态
    // 2     // 准备状态
    // 3     // 进入战场状态
    // 4     // 战场战斗状态
    // 5     // 结束状态
    // 6     // 战场销毁, 释放资源
    virtual int GetCampBattleStatus( int nBattleType ,int countryid);

    // 显示报名窗口 成功返回1, 失败返回0
    virtual bool ShowCampBattleSignUp( int nBattleType );

    // 报名阵营战场 成功返回1, 失败返回0
    virtual bool SignUpCampBattle( int nBattleType );

    // 查询国家战场报名( 国王争夺战, 青龙争夺战, 朱雀争夺战有效 )
    virtual void QueryCampBattleSignUp( unsigned char nBattleType );

    // 显示进入阵营战场窗口 成功返回1, 失败返回0
    virtual bool ShowCampBattleEnter( int nBattleType );

    // 进入阵营战场
    virtual bool EnterCampBattle( int nBattleType );

    // 添加战场积分
    virtual void AddCampBattleResource( int nAddValue );

    // 获得战场积分
    virtual int GetCampBattleResource();

    // 杀死阵营怪物( nAddResource 添加积分 )
    virtual void KillCampBattleMonster( int nMonsterID );

    // 刷新阵营怪
    virtual void CreateCampMonster( int nMonsterID, int nCount, int nMapId, float fPosX, float fPosY, int nFightCamp, float fRadius, float fBodySize, int nRouteID );
    virtual void CreateCampMonster( int nMonsterID, int nCount, float fRadius, float fBodySize, int nRouteID );

	virtual void ChangeCampBattleScore(int IsRadOrBlue,int ChangeType,int Value);

	virtual int GetCampBattleFight();
