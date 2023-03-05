
public:
    int GetGuildId();
    bool IsHaveGuild();
    bool IsGuildMaster();

    // 新的时间函数
    virtual bool RecordGuildTimeVar( int nVarID );       
    virtual bool IsGuildTimeVarPassOneDay( int nVarID ); 
    virtual void ClearGuildTimeVar( int nVarID, int nClearVarID ); 

    // 帮派
    virtual int32 GetGuildOffer();            // 成员帮贡
    virtual void  AddGuildOffer( int nOffer);
    virtual void  DecGuildOffer( int nOffer);

    virtual int32 GetGuildActivity();            // 成员活跃度
    virtual void  AddGuildActivity( int nOffer);
    virtual void  DecGuildActivity( int nOffer);

    virtual int32 GetGuildBuild();              // 建设度 , 经验
    virtual void  AddGuildBuild( int nCredit );
    virtual void  DecGuildBuild( int nCredit );

    virtual int32 GetGuildMoney();              // 帮派金钱
    virtual void  AddGuildMoney( int nValue );
    virtual void  DecGuildMoney( int nValue );

    virtual int32 GetGuildMission();              // 使命点
    virtual void  AddGuildMission( int nValue );    
    virtual void  DecGuildMission( int nValue );

    virtual int32 GetGuildSalary();         
    virtual void  AddGuildSalary( int nValue );    
    virtual void  DecGuildSalary( int nValue );

    virtual int16 GetGuildLevel();              // 等级
    virtual void  SetGuildLevel( int nValue );

    virtual void GuildLevelUp();                    // 请求帮派升级
    virtual void GuildOfferBuild();                 // 捐献帮贡
    virtual void GuildCollect();                    // 帮派募集
    virtual void GuildMasterDelate();               // 帮派弹劾
    virtual void GuildDonate();                     // 帮派捐献
    virtual bool GuildQuestRelease( int nValue );   // 帮派任务发布
    virtual bool GuildShopLevelUp( int nValue );    // 帮派商店等级激活
    virtual bool GuildConvene();                    // 帮派召集
	virtual	int16 GetGuildReleaseQuest();			// 帮派任务发布

    // 公会记数变量
    virtual void AddGuildVar( int nIndex, int nValue );
    virtual void SetGuildVar( int nIndex, int nValue );
    virtual void DecGuildVar( int nIndex, int nValue );
    virtual int GetGuildVar( int nIndex );

	virtual void AddGuildBuffByMapID(int MapID,int BuffID,int Level);

	virtual int GetGuildMemberPosition();

