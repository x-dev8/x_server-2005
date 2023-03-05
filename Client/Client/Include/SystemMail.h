#pragma once
#include <vector>
#include "GlobalDef.h"

enum MailFilter
{
    MailFilter_ALL,       //ȫ���ż�
    MailFlter_Player,     //����ż�
    MailFilter_System,    //ϵͳ�ż�
    MailFilter_Read,      //�Ѷ��ż�
    MailFilter_NoRead,    //δ���ż�
    MailFilter_Addtriad,  //�����������ż�
    MailFilter_Max,       //����ʼ�����
};

class CSystemMail
{
public:
    CSystemMail(void);
    ~CSystemMail(void);

public:
    bool IsHaveMoney(uint32 uMailID);                   //�Ƿ���Ǯ
    bool IsHaveItem(uint32  uMailID);                   //�Ƿ�����Ʒ

    const char* GetMailTitle(uint32 uMailID);           //����ʼ�Title
    const char* GetMailSender(uint32 uMailID);          //����ʼ�������
    const char* GetMailContent(uint32 uMailID);         //����ʼ�����


    void AddMail(SMail& mail);                          // �����ʼ�
    void DeleteByID(uint32 uID);                        //ͨ��IDɾ���ʼ�
    void DeleteByTime(__int64 dwTime);                  //ͨ��ʱ��ɾ���ʼ�
    void SendMail();                                    //�����ż�

    void FilterMail(MailFilter filterType);             //�����ż�
    SMail* ReadMail(int nIndex);                        //�Ķ��ʼ�
    void  UpdateMailByID(uint32 uMailID,SMail &mail);   //�����ʼ������ڶ�ȡ�ż���Ʒ�ͽ��
    void  Clear();                                      //����ʼ��б�

    int  GetCurrentMail(){return m_vecFilterMail.size();} //��õ�ǰ��ʾ�����ʼ�����
    bool RefreshReadStateByID(uint32 uMailID);            //ˢ���ʼ���״̬
    bool RefreshMoneyByID(uint32 uMailID);                //ˢ��Ǯ��
    bool RefreshItemByID(uint32 uMailID);                 //ˢ����Ʒ

    bool IsHaveNewMail();                                 //�Ƿ������ʼ�

private:
    std::vector<SMail>  m_VecMail;        //�����ʼ�
    std::vector<int>    m_vecFilterMail;  //�����ʼ��б�,��������,Ĭ��Ϊ�����б�
    MailFilter          m_FilterType;     //��ǰMailFilter����
};
