

public:
    virtual int GetGuildId() = 0;
    virtual bool IsHaveGuild() = 0;
    virtual bool IsGuildMaster() = 0;

    virtual bool RecordGuildTimeVar( int nVarID ) = 0;       
    virtual bool IsGuildTimeVarPassOneDay( int nVarID ) = 0; 
    virtual void ClearGuildTimeVar( int nVarID, int nClearVarID ) = 0; 

    virtual int32 GetGuildOffer()               = 0;
    virtual void  AddGuildOffer( int nOffer )   = 0;
    virtual void  DecGuildOffer( int nOffer )   = 0;

    virtual int32 GetGuildActivity()            = 0;           
    virtual void  AddGuildActivity( int nOffer) = 0;
    virtual void  DecGuildActivity( int nOffer) = 0;

    virtual int32 GetGuildBuild()               = 0;
    virtual void  AddGuildBuild(int nCredit)    = 0;
    virtual void  DecGuildBuild(int nCredit)    = 0;
                                              
    virtual int32 GetGuildMoney()               = 0;
    virtual void  AddGuildMoney(int nValue )    = 0;
    virtual void  DecGuildMoney(int nValue )    = 0;
                                              
    virtual int16 GetGuildLevel()               = 0;
    virtual void  SetGuildLevel( int nValue )   = 0;

    virtual int32 GetGuildMission()             = 0;         
    virtual void  AddGuildMission( int nValue ) = 0;    
    virtual void  DecGuildMission( int nValue ) = 0;

    virtual int32 GetGuildSalary()             = 0;         
    virtual void  AddGuildSalary( int nValue ) = 0;    
    virtual void  DecGuildSalary( int nValue ) = 0;

    virtual void GuildLevelUp() = 0;                    // 请求帮派升级
    virtual void GuildOfferBuild() = 0;                 // 帮贡建设
    virtual void GuildCollect() = 0;                    // 帮派募集
    virtual void GuildMasterDelate() = 0;               // 帮派弹劾
    virtual void GuildDonate() = 0;                     // 帮派捐献
    virtual bool GuildQuestRelease( int nValue ) = 0;   // 帮派任务发布
	virtual int16 GetGuildReleaseQuest()	= 0;			// 获得当前开启的帮派任务ID
    virtual bool GuildShopLevelUp( int nValue ) = 0;    // 激活帮派商店等级
    virtual bool GuildConvene() = 0;                    // 帮派召集

    // 公会记数变量
    virtual void AddGuildVar( int nIndex, int nValue ) = 0;
    virtual void SetGuildVar( int nIndex, int nValue ) = 0;
    virtual void DecGuildVar( int nIndex, int nValue ) = 0;
    virtual int GetGuildVar( int nIndex ) = 0;

	virtual int GetGuildMemberPosition() = 0;
