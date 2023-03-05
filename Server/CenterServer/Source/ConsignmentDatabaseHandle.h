#ifndef __DBCONSIGNMENTHANDLE_H__
#define __DBCONSIGNMENTHANDLE_H__

public:
    virtual void OnLoadConsignmentData( BaseSqlMessage* pSqlMessage );   // ��ȡ����
    virtual void OnConsignmnetAccountReq( BaseSqlMessage* pSqlMessage ); // �ʺŽ�Ǯ����
    virtual void OnConsignmnetMoneyReq( BaseSqlMessage* pSqlMessage );   // �ҵ�����
    virtual void OnConsignmnetMoneyOperateReq( BaseSqlMessage* pSqlmessage );

protected:
    bool LoadConsignmentAccount();          // ���ؼ����ʺ��б�
    bool LoadConsignmentMoneyList();        // ���ؼ��۵����б�
    bool LoadConsignmentHistroy();          // ���ؼ�����ʷ

    bool ConsignmnetAccountReq( const ConsignmentAccount& xAccount );

    void InsertConsignmentAccount( mysqlpp::Query& xQuery, const ConsignmentAccount& xAccount );
    void UpdateConsignmentAccount( mysqlpp::Query& xQuery, const ConsignmentAccount& xAccount );

    void InsertConsignmentHistroy( mysqlpp::Query& xQuery, const ConsignmentHistroy& xHistroy );

#endif