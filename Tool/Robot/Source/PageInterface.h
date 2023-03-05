#pragma once
#include "stdafx.h"
#include "resource.h"
#include "GmCommandRobot.h"
// Platform_ShutdownServer dialog
#ifndef __PAGEINTERFACE__
#define __PAGEINTERFACE__
class PageInterface : public CPropertyPage
{
    DECLARE_DYNAMIC(PageInterface)

public:
    enum EPageType
    {
        ShutDownServerPage = 0,
        BroadcastPage = 1,
        ChangeMapRatePage = 2,
        KickPlayerPage = 3,
        AddPointsPage = 4,
        ReLoadTradShopPage = 5,
        CreateCharacterPage = 6,
        ChangeCharacterNamePage = 7,
        ReqAddItemPage = 8,
        EPT_TOTAL,
    };

    virtual ~PageInterface();
    PageInterface(int value);
    // Dialog Data
    /*enum { IDD = IDD_DIALOG_PLATFORM_SHUTDOWNSERVER };*/

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeEdShutdownTime();
    afx_msg BOOL OnInitDialog();

    void SetBot(GmCommandRobot *Bot)
    {
        if (NULL == Bot)
            return;
        this->Bot = Bot;
    }

    bool PushPlatformWork(OperationMsg *work)
    {
        if (NULL == Bot||NULL == work)
            return false;
        Bot->PushWork(work);
        return true;
    }

    unsigned short GetType(){return EnumType;}
    void SetType(unsigned short us)
    {
        if (us < ShutDownServerPage || us >=EPT_TOTAL)
            return;
        EnumType = us;
    }
private:
    unsigned short EnumType;
protected:
    GmCommandRobot *Bot;
public:
    afx_msg void OnBnClickedBtnSendSd();
};
#endif 