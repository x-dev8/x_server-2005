#ifndef __DBCONSIGNMENTHANDLE_H__
#define __DBCONSIGNMENTHANDLE_H__

public:
    virtual void OnLoadConsignmentData( BaseSqlMessage* pSqlMessage );   // 读取属性
    virtual void OnConsignmnetAccountReq( BaseSqlMessage* pSqlMessage ); // 帐号金钱操作
    virtual void OnConsignmnetMoneyReq( BaseSqlMessage* pSqlMessage );   // 挂单操作
    virtual void OnConsignmnetMoneyOperateReq( BaseSqlMessage* pSqlmessage );

protected:
    bool LoadConsignmentAccount();          // 加载寄售帐号列表
    bool LoadConsignmentMoneyList();        // 加载寄售单子列表
    bool LoadConsignmentHistroy();          // 记载寄售历史

    bool ConsignmnetAccountReq( const ConsignmentAccount& xAccount );

    void InsertConsignmentAccount( mysqlpp::Query& xQuery, const ConsignmentAccount& xAccount );
    void UpdateConsignmentAccount( mysqlpp::Query& xQuery, const ConsignmentAccount& xAccount );

    void InsertConsignmentHistroy( mysqlpp::Query& xQuery, const ConsignmentHistroy& xHistroy );

#endif