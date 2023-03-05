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
        EDO_Active = 0,   // 出战
        EDO_UnActive = 1, // 取消出战
        EDO_Drop = 2,     // 放生
        EDO_GetDrome = 3, // 获得马
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