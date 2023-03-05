// Source\PlatFormTest.cpp : implementation file
//

#include "stdafx.h"
#include "GameDefineBot.h"
#include "PlatFormDialog.h"
#include "Proprety.h"
#include "Bot.h"
#include "GmCommandRobot.h"
#include "BotAppDataCenter.h"
// PlatFormTest dialog
volatile bool PlatFormDialog::_exit = false;
volatile bool PlatFormDialog::_alaryExitThread = false;

IMPLEMENT_DYNAMIC(PlatFormDialog, CDialog)

PlatFormDialog::PlatFormDialog(CWnd* pParent /*=NULL*/)
	: CDialog(PlatFormDialog::IDD, pParent)
{

}

PlatFormDialog::~PlatFormDialog()
{
}

void PlatFormDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void PlatFormDialog::RunThreadFunc(void *pVoid)
{
    _alaryExitThread = false;
    BaseRobot *pBot = (BaseRobot*)pVoid;
    if (pBot->GetType() == Bot_PlatformTest)
    {
        GmCommandRobot *pPlatFormBot = (GmCommandRobot*)pBot;
		pBot->_targetGateIp=theBotDataCenter.GetServerIP();
		pBot->_targetGatePort=theBotDataCenter.GetServerPort();
		
    //    pPlatFormBot->SetGLSAddress(theBotDataCenter.GetServerIP(),theBotDataCenter.GetServerPort());
        while (!_exit)
        {
            pPlatFormBot->Update();
            Sleep(1);
        }
    }
    _alaryExitThread = true;
}

BOOL PlatFormDialog::OnInitDialog()
{
    if (CDialog::OnInitDialog() == FALSE)
        return FALSE;

    _exit = false;
    BaseRobot *pBot = new GmCommandRobot();
    short Num = 0;
    const short TotalConnectNum = 100;
 //   pBot->SetGLSAddress(theBotDataCenter.GetServerIP(),theBotDataCenter.GetServerPort());
    while (Num < TotalConnectNum)
    {
        /*if (pBot->IsConnected())
        {
            break;
        }
        pBot->Update();*/
        Sleep(10);
        ++Num;
    }

#ifndef _DEBUG
   /* if (!pBot->IsConnected())
    {
        char buf[512];
        sprintf_s(buf,512,"连接%s:%d服务器失败!",pBot->GetServerIp(),pBot->GetServerPort());
        MessageBox("连接服务器失败!","Warning");
        delete pBot;
        pBot = NULL;
        PostMessage(WM_CLOSE);
        return FALSE;
    }*/
#endif // _DEBUG

    _beginthread(RunThreadFunc,0,pBot);
    ControlsSheet _ControlTab(_T("Table Control"),(GmCommandRobot*)pBot);
    _ControlTab.DoModal();
    _exit = true;
    //等待
    while (!_alaryExitThread)
    {
        Sleep(1);
    }
    delete pBot;
    pBot = NULL;
    PostMessage(WM_CLOSE);
    return FALSE;
}

BEGIN_MESSAGE_MAP(PlatFormDialog, CDialog)
END_MESSAGE_MAP()

