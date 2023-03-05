// E:\Hero\Program\trunk\Tool\Robot\Source\CommondDialog.cpp : implementation file
//

#include "stdafx.h"
#include "../Resource/resource.h"
#include "CommondDialog.h"
#include "CommondBot.h"
#include "GameBotView.h"
// CCommondDialog dialog

const char *CCommondDialog::CommondChar[] = {"","1",};


IMPLEMENT_DYNAMIC(CCommondDialog, CDialog)

CCommondDialog::CCommondDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCommondDialog::IDD, pParent)
    ,m_CommondParam1(-1)
{

}

CCommondDialog::~CCommondDialog()
{
}

void CCommondDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_COMMONDLIST, m_BotCommondList);
    DDX_Text(pDX, IDC_EDIT_SHOWINFO, m_CommondShow);
    DDX_Text(pDX, IDC_EDIT_INPUT, m_CommondInput);
    DDV_MaxChars(pDX, m_CommondInput, 20);
    DDX_Text(pDX, IDC_EDIT_PARAMETER1, m_CommondParam1);
    DDV_MinMaxInt(pDX,m_CommondParam1,-1,1000000);

    DDX_Text(pDX, IDC_EDIT_PARAMETER2, m_CommondParam2);
    DDV_MaxChars(pDX, m_CommondParam2, 10);

    DDX_Control(pDX, IDC_COMBO_COMMOND, m_CommondCombo);
    DDX_Control(pDX, IDC_COMBO_RUNTIME, m_CommondTimeCombo);
    DDX_Control(pDX, IDC_COMBO_RUN_PRI, m_CommondPriorityCombo);
    DDX_Control(pDX, IDC_BUTTON_ADD_COMMOND, m_AddCommondBtn);
    DDX_Control(pDX, IDC_BUTTON_SUB_COMMOND, m_SubCommondBtn);
    //DDV_MinMaxInt(pDX, ValueDay, -1, 31);
}

BOOL CCommondDialog::OnInitDialog()
{
//     if (GettheMainView() != GetParent())
//         return FALSE;

    if (CDialog::OnInitDialog() == FALSE)
        return FALSE;
    
    m_BotCommondList.DeleteAllItems();
    RECT rect;
    m_BotCommondList.GetClientRect(&rect);
    long nWidth = rect.right - rect.left;

    DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_BotCommondList.SetExtendedStyle(dwStyle); 
    m_BotCommondList.InsertColumn(0, "命令列表", 0, (95 * nWidth) / 100);
    m_BotCommondList.InsertColumn(1, "", 0, (5 * nWidth) / 100);

    // 读取当前选中的BOT的list



    if (GettheMainView()->m_nBotID != -1)
    {
        BaseRobot *pBot = theApp.gBotApplication.GetBot(GettheMainView()->m_nBotID);
        if(pBot != NULL && pBot->GetBotState() != State_Play )// && pBot->GetType() != Bot_Client)
        {
            CommondBot* pCommondBot = (CommondBot*)pBot;
            CommondBot::ItrCommondStructContainer Itr = pCommondBot->GetBotCommondStructs().begin();
            CommondBot::ItrCommondStructContainer ItrEnd = pCommondBot->GetBotCommondStructs().end();
            for (int SubItem = 0 ;Itr != ItrEnd;++Itr,++SubItem)
            {
                char ItemStringBuff[255];
                sprintf_s(ItemStringBuff,sizeof(ItemStringBuff),"%d",Itr->CommondType);
                m_BotCommondList.InsertItem(SubItem,ItemStringBuff);
            }
        }
    }

    m_CommondPriorityCombo.ResetContent();
    m_CommondPriorityCombo.AddString("高");
    m_CommondPriorityCombo.AddString("中");
    m_CommondPriorityCombo.AddString("低");
    m_CommondPriorityCombo.SetCurSel(1);



    UpdateData();
    return TRUE; 
}


void CCommondDialog::OnClickedAddCommondBTN()
{
    if (!UpdateData())
        return;
    if (!m_CommondInput.IsEmpty())
    {
        // 如果有指令就给当前机器人添加指令，没有就读取参数
        char buf = m_CommondInput.GetAt(0);
        if ( buf != '/')
        {
            MessageBox("输入的指令有误,请检查指令,重新输入","警告");
            return;
        }
        CString CommondContext = m_CommondInput.Right(m_CommondInput.GetLength()-1);
        
        return;
    }

    CommondBot::CommondStruct CommondStruct;
    CommondStruct.CommondType = m_CommondCombo.GetCurSel();
    CommondStruct.Param1 = m_CommondParam1;
    CommondStruct.Param2 = m_CommondParam2.GetBuffer(m_CommondParam2.GetLength());
    CommondStruct.Priority = m_CommondPriorityCombo.GetCurSel();
}

void CCommondDialog::OnClickedSubCommondBTN()
{
    if (!UpdateData(FALSE))
        return;


}

BEGIN_MESSAGE_MAP(CCommondDialog, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_ADD_COMMOND, &CCommondDialog::OnClickedAddCommondBTN)
    ON_BN_CLICKED(IDC_BUTTON_SUB_COMMOND, &CCommondDialog::OnClickedSubCommondBTN)
END_MESSAGE_MAP()


// CCommondDialog message handlers
// E:\Hero\Program\trunk\Tool\Robot\Source\CommondDialog.cpp : implementation file
//