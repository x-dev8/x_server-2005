#include "stdafx.h"
#include "AttackBot.h"
#include "ItemDetail.h"

class CMatrixBot;
//CItemDetail::SDrome
class DromeBot:public CAttackBot
{
public:
    typedef std::vector<SMountItem> SDromeContainer;
    typedef SDromeContainer::iterator ItrSDromeContainer;

    enum DromeOperation
    {
        EDO_Active = 0,   // ��ս
        EDO_UnActive = 1, // ȡ����ս
        EDO_Drop = 2,     // ����
        EDO_GetDrome = 3, // �����
        EDO_TotalOperation,
    };
public:
    DromeBot();
    ~DromeBot();

    //method
    void GetDrome();
    void RemoveDrome(int Drome);
    void RandOperationDrome();
    virtual void PlayGame();
    virtual void InitPlayGame();
    SMountItem* FindMountByGuid(__int64 FindGuid);
    SMountItem* FindMountByIndex(int Index);
    //Msg
    virtual void OnMsgGetMount(Msg* pMsg);
    virtual void SwitchMsg(Msg* pMsg);
    virtual void OnMsgAckResult(Msg* pMsg);
    virtual void OnMsgChangeDrome( Msg* Msg);
    virtual void OnMsgAckEnterWorld( Msg* pMsg );
private:
    SDromeContainer  SDromes;
    DWORD   OperationTime;
};