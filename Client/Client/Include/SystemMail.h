#pragma once
#include <vector>
#include "GlobalDef.h"

enum MailFilter
{
    MailFilter_ALL,       //全部信件
    MailFlter_Player,     //玩家信件
    MailFilter_System,    //系统信件
    MailFilter_Read,      //已读信件
    MailFilter_NoRead,    //未读信件
    MailFilter_Addtriad,  //包含附件的信件
    MailFilter_Max,       //最大邮件数量
};

class CSystemMail
{
public:
    CSystemMail(void);
    ~CSystemMail(void);

public:
    bool IsHaveMoney(uint32 uMailID);                   //是否有钱
    bool IsHaveItem(uint32  uMailID);                   //是否有物品

    const char* GetMailTitle(uint32 uMailID);           //获得邮件Title
    const char* GetMailSender(uint32 uMailID);          //获得邮件收信人
    const char* GetMailContent(uint32 uMailID);         //获得邮件正文


    void AddMail(SMail& mail);                          // 增加邮件
    void DeleteByID(uint32 uID);                        //通过ID删除邮件
    void DeleteByTime(__int64 dwTime);                  //通过时间删除邮件
    void SendMail();                                    //发送信件

    void FilterMail(MailFilter filterType);             //过滤信件
    SMail* ReadMail(int nIndex);                        //阅读邮件
    void  UpdateMailByID(uint32 uMailID,SMail &mail);   //更新邮件，用于读取信件物品和金币
    void  Clear();                                      //清空邮件列表

    int  GetCurrentMail(){return m_vecFilterMail.size();} //获得当前显示类型邮件数量
    bool RefreshReadStateByID(uint32 uMailID);            //刷新邮件读状态
    bool RefreshMoneyByID(uint32 uMailID);                //刷新钱币
    bool RefreshItemByID(uint32 uMailID);                 //刷新物品

    bool IsHaveNewMail();                                 //是否有新邮件

private:
    std::vector<SMail>  m_VecMail;        //所有邮件
    std::vector<int>    m_vecFilterMail;  //过滤邮件列表,保存索引,默认为所有列表
    MailFilter          m_FilterType;     //当前MailFilter类型
};
