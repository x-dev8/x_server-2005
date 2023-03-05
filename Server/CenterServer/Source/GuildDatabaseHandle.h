
protected:
    void LoadGuildData( BaseSqlMessage* pSqlMessage );
    void LoadGuildMember( BaseSqlMessage* pSqlMessage );

    void UpdateGuileMember( GuildMember& xMember );
public:
    virtual void OnGuildDataLoadReq ( BaseSqlMessage* pSqlMessage );
    virtual void OnGuildDataUpdateReq( BaseSqlMessage* pSqlMessage );
    virtual void OnGuildMemberUpdateReq( BaseSqlMessage* pSqlMessage );
    virtual void OnGuildDisbandReq( BaseSqlMessage* pSqlMessage );
    virtual void OnGuildMemberLeaveReq( BaseSqlMessage* pSqlMessage );