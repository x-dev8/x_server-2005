#ifndef __DATABASERELATIONHANDLE_H__
#define __DATABASERELATIONHANDLE_H__

public:
    virtual void OnQueryLoadRelationReq ( BaseSqlMessage* pSqlMessage );
    virtual void OnAddRelationReq( BaseSqlMessage* pSqlMessage );
    virtual void OnUpdateRelationDataReq( BaseSqlMessage* pSqlMessage );
    virtual void OnAddAttributeReq( BaseSqlMessage* pSqlMessage );
    virtual void OnUpdateAttributeReq( BaseSqlMessage* pSqlMessage );
    virtual void OnQueryAttributeReq( BaseSqlMessage* pSqlMessage );
    virtual void OnUpdateRelationGroup( BaseSqlMessage* pSqlMessage );
	virtual void OnUpdatePersonalInfo( BaseSqlMessage* pSqlMessage );
	virtual void OnFindPerson( BaseSqlMessage* pSqlMessage );

protected:
    void LoadRelationAttribute( BaseSqlMessage* pSqlMessage );
    void LoadRelationData( BaseSqlMessage* pSqlMessage );

#endif