
public:
    
    // 以下所有nBattleType( 战场类型, 帮派争夺战( nType = 1 ) )

    // 获得战场阵营
    virtual int GetBattleCamp() = 0;   

    // 获得战场状态
    virtual int GetCampBattleStatus( int nBattleType,int countryid ) = 0;

    // 显示报名窗口
    virtual bool ShowCampBattleSignUp( int nBattleType ) = 0;

    // 查询报名信息( 国王争夺战, 青龙争夺战, 朱雀争夺战有效 )
    virtual void QueryCampBattleSignUp( unsigned char nBattleType ) = 0;

    // 报名阵营战场 
    virtual bool SignUpCampBattle( int nBattleType ) = 0;

    // 显示进入阵营战场窗口
    virtual bool ShowCampBattleEnter( int nBattleType ) = 0;

    // 进入阵营战场
    virtual bool EnterCampBattle( int nBattleType ) = 0;

    // 添加战场积分
    virtual void AddCampBattleResource( int nAddValue ) = 0;

    // 获得战场积分
    virtual int GetCampBattleResource() = 0;

    // 杀死阵营怪物
    virtual void KillCampBattleMonster( int nMonsterID ) = 0;

    // 刷新阵营怪
    virtual void CreateCampMonster( int nMonsterID, int nCount, int nMapId, float fPosX, float fPosY, int nFightCamp, float fRadius, float fBodySize, int nRouteID ) = 0;
    virtual void CreateCampMonster( int nMonsterID, int nCount, float fRadius, float fBodySize, int nRouteID ) = 0;

	//设置战场双方的任意一方的积分
	virtual void ChangeCampBattleScore(int IsRadOrBlue,int ChangeType,int Value) = 0;

	virtual int GetCampBattleFight() = 0;