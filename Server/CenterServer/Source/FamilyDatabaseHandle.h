
/************************************************************************/
/* include in NormalLogicWorkThread.h                                   */
/************************************************************************/

protected:
	void LoadFamilyData( BaseSqlMessage* pSqlMessage );
	void LoadFamilyMember( BaseSqlMessage* pSqlMessage );

	void UpdateFamilyMember( FamilyDefine::FamilyMember& xMember );
public:
	virtual void OnFamilyDataLoadReq ( BaseSqlMessage* pSqlMessage );
	virtual void OnFamilyDataUpdateReq( BaseSqlMessage* pSqlMessage );
	virtual void OnFamilyMemberUpdateReq( BaseSqlMessage* pSqlMessage );
	virtual void OnFamilyMemberLeaveReq( BaseSqlMessage* pSqlMessage );
	virtual void OnFamilyDisbandReq( BaseSqlMessage* pSqlMessage );