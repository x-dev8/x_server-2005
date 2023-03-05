// EditorView.cpp : implementation of the CEditorView class
//

#include "stdafx.h"
#include "EventEditor.h"

#include "EventEditorDoc.h"
#include "EventEditorView.h"

#include "MapConfig.h"
#include "NpcInfo.h"
#include "ItemDetail.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define HOTLEFTRGB   RGB(255,200,200)
#define HOTRIGHTRGB  RGB(255,50,50)

#define DEFAULTLEFTRGB  RGB(196,220,247)
#define DEFAULTRIGHTRGB RGB( 128, 160, 255 )
// CEditorView

IMPLEMENT_DYNCREATE(CEditorView, CFormView)

BEGIN_MESSAGE_MAP(CEditorView, CFormView)
    //ON_EN_CHANGE(IDC_ED_NAME3, &CEditorView::OnEnChangeEdName3)
    ON_NOTIFY(TVN_SELCHANGED, IDC_CALENDARTREE, &CEditorView::OnTvnSelchangedEventTree)
    ON_CBN_SELCHANGE(IDC_COMBO_PERIODTYPE, &CEditorView::OnCbnSelchangeComboPeriodtype)
    ON_CBN_EDITCHANGE(IDC_COMBO_PERIODTYPE, &CEditorView::OnCbnEditchangeComboPeriodtype)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_BROADCASTS, &CEditorView::OnNMDBLclkListBroadcasts)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_REWARD, &CEditorView::OnNMDBLclkListReward)
    ON_NOTIFY(NM_CLICK, IDC_LIST_BROADCASTS, &CEditorView::OnNMClickListBroadcasts)
    ON_NOTIFY(NM_CLICK, IDC_LIST_REWARD, &CEditorView::OnNMClickListReward)
    ON_REGISTERED_MESSAGE(WM_XLISTCTRL_EDIT_END, OnEditEnd)
    ON_REGISTERED_MESSAGE(WM_XLISTCTRL_COMBO_SELECTION,OnSelectList)
    //ON_COMMAND(ID_APPLYEVENT, &CEditorView::OnApplyEvent)
    ON_COMMAND(ID_DELETEVENT, &CEditorView::OnMsgDeletEvent)
    ON_COMMAND(ID_SAVEEVENT, &CEditorView::OnSaveEvent)
    ON_NOTIFY(NM_DBLCLK, IDC_CALENDARTREE, &CEditorView::OnNMDblclkEventTree)
    ON_COMMAND(ID_APPLYEVENT, &CEditorView::OnApplyEvent)
    ON_COMMAND(ID_ADD_B_OR_R, &CEditorView::OnAddBroadcastOrReward)
END_MESSAGE_MAP()

// CEditorView construction/destruction

CEditorView::CEditorView()
	: CFormView(CEditorView::IDD)
    , ValueDescription(_T(""))
    , ValueName(_T(""))
    , ValueConunt(0)
    , ValueDuration(0)
    , ValueYear(0)
    , ValueMonth(0)
    , ValueDay(0)
    , ValueHour(0)
    , ValueMinute(0)
    , ValueCompleteId(0)
    , ValueMapPosY(0)
    , ValueMapPosX(0)
    , CurListCtrl(NULL)
    , CurItem(-1)
    , CurSubItem(-1)
    , ValueDurationDes(_T(""))
    , ValueHot(FALSE)
    , ValueScriptId(0)
    , ValueItemId(0)
{
	// TODO: add construction code here
}

CEditorView::~CEditorView()
{
}

void CEditorView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ED_DESCRIPTION, ValueDescription);
    DDX_Control(pDX, IDC_CALENDARTREE, EventViewTree);
    DDX_Text(pDX, IDC_ED_NAME, ValueName);
    DDX_Control(pDX, IDC_COMBO_QUALITY, ValueQualty);
    DDX_Control(pDX, IDC_COMBO_MAPID, ComboControlMapId);
    DDX_Text(pDX, IDC_ED_COUNT, ValueConunt);
    DDX_Text(pDX, IDC_ED_DURATION, ValueDuration);
    DDX_Control(pDX, IDC_COMBO_NPCID, ComboControlNpcId);
    DDX_Control(pDX, IDC_COMBO_NEEDLEVEL, ValueNeedLevel);
    DDX_Control(pDX, IDC_COMBO_PERIODTYPE, ComboControlPeriodType);
    DDX_Control(pDX, IDC_COMBO_PERIODVALUE, ComboControlTypeValue);
    DDX_Text(pDX, IDC_ED_YEAR, ValueYear);
    DDX_Text(pDX, IDC_ED_MONTH, ValueMonth);
    DDV_MinMaxInt(pDX, ValueMonth, 0, 12);
    DDX_Text(pDX, IDC_ED_DAY, ValueDay);
    DDV_MinMaxInt(pDX, ValueDay, -1, 31);
    DDX_Text(pDX, IDC_ED_HOUR, ValueHour);
    DDV_MinMaxInt(pDX, ValueHour, -1, 23);
    DDX_Text(pDX, IDC_ED_MINUTE, ValueMinute);
    DDV_MinMaxInt(pDX, ValueMinute, -1, 59);
    DDX_Text(pDX, IDC_ED_COMPLETEID, ValueCompleteId);
    DDX_Control(pDX, IDC_LIST_BROADCASTS, ControlBroadcasts);
    DDX_Control(pDX, IDC_LIST_REWARD, ControlRewards);
    DDX_Text(pDX, IDC_ED_MAPPOSY, ValueMapPosY);
    DDV_MinMaxFloat(pDX,ValueMapPosY,-1,999);
    DDX_Text(pDX, IDC_ED_MAPPOSX, ValueMapPosX);
    DDV_MinMaxFloat(pDX,ValueMapPosX,-1,999);
    DDV_MaxChars(pDX, ValueName, 18);
    DDV_MinMaxInt(pDX, ValueYear, -1, 2109);
    DDX_Text(pDX, IDC_ED_DURATION_DESCRIPTION, ValueDurationDes);
    DDV_MaxChars(pDX, ValueDurationDes, 100);

    DDX_Check(pDX, IDC_CHECK_ISHOT, ValueHot);
    DDX_Text(pDX, IDC_EDIT_SCRIPTID, ValueScriptId);
    DDV_MinMaxInt(pDX, ValueScriptId, -1, 32767);
    DDX_Check(pDX, IDC_CHECK_PIVOTEVENT, ValuePivot);
    DDX_Text(pDX, IDC_EDIT_EVENTICONID, ValueItemId);
	DDV_MinMaxInt(pDX, ValueItemId, 0, 65535);
}

BOOL CEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CEditorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
    // 每次重新载入都会执行支持这里

    InitBroadcastListCtrl();
    InitRewardListCtrl();
    InitNpc();
    InitMap();
    InitPeriodType();
    InitRewardType();
    InitEventName();
    InitItemStringArray();
    InitNeedLevel();
    InitQuality();
    ControlDayElement(FALSE);
}

void CEditorView::ControlClearBaseEventElement()
{
    ValueDescription = "";
    ValueName = "";
    ValueQualty.SetWindowText("");
    ValueConunt = -1;
    ValueDuration = -1;
    ValueNeedLevel.SetWindowText("");
    ValueCompleteId = -1;
    ValueMapPosY = -1 ;
    ValueMapPosX = -1;
    ValueHot = false;
    ValueScriptId = -1;
    ValueItemId = ErrorUnsignedShortID;
//     CWnd* pWindows = NULL;
//     pWindows = GetDlgItem(IDC_ED_NAME);
//     if (NULL != pWindows)
//     {
//         pWindows->SetWindowText("");
//         pWindows->UpdateData(FALSE);
//     }
// 
//     pWindows = GetDlgItem(IDC_ED_DESCRIPTION);
//     if (NULL != pWindows)
//     {
//         pWindows->SetWindowText("");
//         //pWindows->UpdateData(FALSE);
//     }
// 
//     pWindows = GetDlgItem(IDC_ED_QUALITY);
//     if (NULL != pWindows)
//     {
//         pWindows->SetWindowText("");
//         //pWindows->UpdateData(FALSE);
//     }
// 
//     pWindows = GetDlgItem(IDC_ED_COUNT);
//     if (NULL != pWindows)
//     {
//         pWindows->SetWindowText("");
//         //pWindows->UpdateData(FALSE);
//     }
// 
//     pWindows = GetDlgItem(IDC_ED_DURATION);
//     if (NULL != pWindows)
//     {
//         pWindows->SetWindowText("");
//         //pWindows->UpdateData(FALSE);
//     }
// 
//     pWindows = GetDlgItem(IDC_ED_NEEDLEVEL);
//     if (NULL != pWindows)
//     {
//         pWindows->SetWindowText("");
//         //pWindows->UpdateData(FALSE);
//     }
//     pWindows = GetDlgItem(IDC_COMBO_MAPID);
//     if (NULL != pWindows)
//     {
//         pWindows->SetWindowText("");
//         //pWindows->UpdateData(FALSE);
//     }
// 
//     pWindows = GetDlgItem(IDC_ED_MAPPOSX);
//     if (NULL != pWindows)
//     {
//         pWindows->SetWindowText("");
//         //pWindows->UpdateData(FALSE);
//     }
//     pWindows = GetDlgItem(IDC_ED_MAPPOSY);
//     if (NULL != pWindows)
//     {
//         pWindows->SetWindowText("");
//         //pWindows->UpdateData(FALSE);
//     }
    UpdateData(FALSE);
}

void CEditorView::ControlBaseCalendarElement(BOOL IsOpen)
{
    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_NAME);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_DESCRIPTION);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_QUALITY);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_COUNT);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_DURATION);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_NEEDLEVEL);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_COMBO_MAPID);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_MAPPOSX);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_MAPPOSY);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);
}

void CEditorView::ControlBroadcastsElement(BOOL IsOpen)
{
    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_LIST_BROADCASTS);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);
}

void CEditorView::ControlClearBroadcastsElement()
{
    CXListCtrl* pWindows = (CXListCtrl*)GetDlgItem(IDC_LIST_BROADCASTS);
    if (NULL != pWindows)
    {
        pWindows->DeleteAllItems();
        pWindows->UpdateData(FALSE);
    }
}

void CEditorView::InitEventName()
{
    EventViewTree.DeleteAllItems();
    for (int i = 0;i < theEventManager.GetAllEventSize();++i)
    {
        Event* pEven = theEventManager.GetEventByIndex(i);
        if (NULL != pEven)
        {
            HTREEITEM CurHTREEITEM = EventViewTree.InsertItem(pEven->name.c_str());
            if (pEven->isHot == TRUE)
                EventViewTree.SetItemBgColor(CurHTREEITEM,HOTLEFTRGB,HOTRIGHTRGB);
        }
    }
}

void CEditorView::InitNeedLevel()
{
    ValueNeedLevel.ResetContent();
    for (int level=1;level<=70;++level)
    {
        char showbuf[10];
        sprintf_s(showbuf,sizeof(showbuf),"%d",level);
        ValueNeedLevel.AddString(showbuf);
    }
}

void CEditorView::InitQuality()
{
    ValueQualty.ResetContent();
    for (int level=1;level<=5;++level)
    {
        char showbuf[10];
        sprintf_s(showbuf,sizeof(showbuf),"%d",level);
        ValueQualty.AddString(showbuf);
    }
}

void CEditorView::ShowBaseEventElement(const Event* pEven)
{
    if (NULL == pEven)
        return;

    std::string strName = pEven->name.substr(0,pEven->name.find_first_of("@"));
    ValueName        = strName.c_str();
    ValueDescription = pEven->description.c_str();
    ValueConunt      = pEven->count;
    ValueCompleteId  = pEven->completeTimeVarIndex;
    ValueMapPosY     = pEven->mapPosY;
    ValueMapPosX     = pEven->mapPosX;
    ValueDuration    = pEven->duration;
    ValueDurationDes = pEven->durationDescription.c_str();
    ValueHot         = pEven->isHot;
    ValuePivot       = pEven->isPivot;
    ValueScriptId    = pEven->scriptId;
    ValueItemId      = pEven->eventItemId;

    ValueNeedLevel.SetCurSel(pEven->needLevel-1);
    ValueQualty.SetCurSel(pEven->quality-1);
    UpdateData(FALSE);
}

int CEditorView::SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle)
{
    xList.SetExtendedStyle(dwStyle);

    RECT rect;
    xList.GetClientRect(&rect);

    return (rect.right - rect.left);
}

void CEditorView::InitBroadcastListCtrl()
{
    ControlBroadcasts.DeleteAllItems();
    DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    int nWidth = SetListCtrlStyle(ControlBroadcasts, dwStyle);
    ControlBroadcasts.InsertColumn(0, "OFFSET_TIME", 0, (25 * nWidth) / 100);
    ControlBroadcasts.InsertColumn(1, "OFFSET_CONTENT", 0, (70 * nWidth) / 100);
    ControlBroadcasts.InsertColumn(2, "Select", 0, (5 * nWidth) / 100);
    ControlBroadcasts.UpdateData(FALSE);
}

void CEditorView::InitRewardListCtrl()
{
    ControlRewards.DeleteAllItems();
    DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    int nWidth = SetListCtrlStyle(ControlRewards, dwStyle);
    ControlRewards.InsertColumn(0, "RewardType", 0, (25 * nWidth) / 100);
    ControlRewards.InsertColumn(1, "Id", 0, (35 * nWidth) / 100);
    ControlRewards.InsertColumn(2, "Count", 0, (35 * nWidth) / 100);
    ControlRewards.InsertColumn(3, "Select", 0, (5 * nWidth) / 100);
    ControlRewards.UpdateData(FALSE);
}

void CEditorView::ShowBroadcastsElement(const Event* pEven)
{
    if (NULL == pEven)
        return;

    ControlBroadcasts.DeleteAllItems();

    for (int i = 0;i < pEven->broadcast.size();++i)
    {
        char szOffsetTime[50] = { 0 };
        sprintf_s(szOffsetTime,sizeof(szOffsetTime),"%d",pEven->broadcast[i].offsetTime);

        ControlBroadcasts.InsertItem(i,szOffsetTime);
        ControlBroadcasts.SetItemText(i,1,pEven->broadcast[i].content.c_str());
        ControlBroadcasts.SetEdit(i,0);
        ControlBroadcasts.SetEdit(i,1);
    }

    ControlBroadcasts.UpdateData(FALSE);
}

void CEditorView::ShowDayElement(const Event* pEven)
{
    if (NULL == pEven)
        return;

    ValueYear = pEven->year+1;
    ValueMonth = pEven->month+1;// 底层是0-11，表现为1-12
    ValueDay = pEven->day+1;
    ValueHour = pEven->hour;
    ValueMinute = pEven->minute;
    UpdateData(FALSE);
}

void CEditorView::ShowRewardsElement(const Event* pEven)
{
    if (NULL == pEven)
        return ;

    ControlRewards.DeleteAllItems();
    for (int i = 0;i < pEven->rewards.size();++i)
    {
        char sztypeId[150] = { 0 };
        EventRewardType* pEventRewardType = theEventManager.GetEventRewardType(pEven->rewards[i].typeId);
        if (NULL == pEventRewardType)
            continue;
        
        sprintf_s(sztypeId,sizeof(sztypeId),"%s",pEventRewardType->description.c_str());

//         char szId[50] = { 0 };
//         sprintf_s(szId,sizeof(szId),"%d",pEven->rewards[i].id);
        CItemDetail::SItemCommon * pItem = GettheItemDetail().GetItemByID(pEven->rewards[i].id);


        char szCount[50] = { 0 };
        sprintf_s(szCount,sizeof(szCount),"%d",pEven->rewards[i].count);

        ControlRewards.InsertItem(i,sztypeId);
        ControlRewards.SetComboBox(i, 0, TRUE, &RewardStringArray, RewardStringArray.GetCount(), pEventRewardType->id);
        if (NULL != pItem)
        {
            int result = GetItemStringIndexByName(pItem->GetItemName());
            if (result != -1)
            {
                ControlRewards.SetComboBox(i,1,TRUE,&ItemStringArray,ItemStringArray.GetCount(),result);
            }
            else
                ControlRewards.SetComboBox(i,1,TRUE,&ItemStringArray,ItemStringArray.GetCount(),0);
        }
        else
            ControlRewards.SetComboBox(i,1,TRUE,&ItemStringArray,ItemStringArray.GetCount(),0);
        //ControlRewards.SetItemText(i,1,szId);
        ControlRewards.SetEdit(i,2);
        ControlRewards.SetItemText(i,2,szCount);
    }

    ControlRewards.UpdateData(FALSE);
}

void CEditorView::ControlClearDayElement()
{
    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_YEAR);
    if (NULL != pWindows)
    {
        pWindows->SetWindowText("");
        pWindows->UpdateData(FALSE);
    }

    pWindows = GetDlgItem(IDC_ED_MONTH);
    if (NULL != pWindows)
    {
        pWindows->SetWindowText("");
        pWindows->UpdateData(FALSE);
    }

    pWindows = GetDlgItem(IDC_ED_DAY);
    if (NULL != pWindows)
    {
        pWindows->SetWindowText("");
        pWindows->UpdateData(FALSE);
    }

    pWindows = GetDlgItem(IDC_ED_HOUR);
    if (NULL != pWindows)
    {
        pWindows->SetWindowText("");
        pWindows->UpdateData(FALSE);
    }
    pWindows = GetDlgItem(IDC_ED_MINUTE);
    if (NULL != pWindows)
    {
        pWindows->SetWindowText("");
        pWindows->UpdateData(FALSE);
    }
}

void CEditorView::ControlDayElement(BOOL IsOpen)
{
    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_YEAR);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_MONTH);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_DAY);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_HOUR);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

    pWindows = GetDlgItem(IDC_ED_MINUTE);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);

//     pWindows = GetDlgItem(IDC_COMBO_PERIODVALUE);
//     if (NULL != pWindows)
//     {
//         pWindows->EnableWindow(FALSE);
//         pWindows->SetWindowText("");
//         pWindows->UpdateData(FALSE);
//     }
}

void CEditorView::ControlRewardsElement(BOOL IsOpen)
{
    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_LIST_REWARD);
    if (NULL != pWindows)
        pWindows->EnableWindow(IsOpen);
}

void CEditorView::ControlClearMap()
{
    ComboControlMapId.SetWindowText("");
    ComboControlMapId.UpdateData(FALSE);
}

void CEditorView::InitMap()
{
    ComboControlMapId.ResetContent();
    for (int i = 0;i < theMapConfig.MapDataCount(); ++i)
    {
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataByIndex(i);
        if (NULL != pMapData)
        {
            if (!pMapData->MapName.empty())
                ComboControlMapId.AddString(pMapData->MapName.c_str());
        }
    }
    ComboControlMapId.SetWindowText("");
    ComboControlMapId.UpdateData();
}

int CEditorView::GetMapView2Data()
{
    UpdateData();
    CString MapName;
    ComboControlMapId.GetWindowText(MapName);
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataByName(MapName.GetBuffer(MapName.GetLength()));
    if (NULL != pMapData)
    {
        return pMapData->Id;
    }
    return -1;
}

int CEditorView::GetNpcView2Data()
{
    UpdateData();
    CString NpcName;
    ComboControlNpcId.GetWindowText(NpcName);
    NpcInfo::Npc* pNpcData = theNpcInfo.GetNpcByName(NpcName.GetBuffer(NpcName.GetLength()));
    if (NULL != pNpcData)
    {
        return pNpcData->id;
    }
    return -1;
}

void CEditorView::InitNpc()
{
    ComboControlNpcId.ResetContent();
    for (NpcInfo::Npcs::iterator itr = theNpcInfo.npcs_.begin();itr != theNpcInfo.npcs_.end(); ++itr)
    {
        if(!itr->second.name.empty())
        {
            ComboControlNpcId.AddString(itr->second.name.c_str());
        }
//         NpcInfo::Npc* pNpcData = theNpcInfo.GetNpcByStaticId(i);
//         if (NULL != pNpcData)
//         {
//             ComboControlNpcId.AddString(pNpcData->name.c_str());
//         }
    }
    ComboControlNpcId.SetWindowText("");
    ComboControlNpcId.UpdateData();
}

void CEditorView::ControlClearPeriodType()
{
    ComboControlPeriodType.ResetContent();
    ComboControlPeriodType.SetWindowText("");
    ComboControlPeriodType.UpdateData(FALSE);
}

void CEditorView::InitPeriodType()
{
    ComboControlPeriodType.Clear();
    for (int i = 0;i < theEventManager.GetEventPeriodTypeSize();++i)
    {
        EventPeriodType* pEventPeriodType = theEventManager.GetEventPeriodTypeByIndex(i);
        if (pEventPeriodType->id >= 10)
            break;

        if (NULL != pEventPeriodType)
        {
            ComboControlPeriodType.AddString(pEventPeriodType->description.c_str());
        }
    }
}

void CEditorView::ShowPeriodType(const Event* pEven)
{
    if (NULL == pEven)
        return;
    EventPeriodType* pEventPeriodType = theEventManager.GetEventPeriodTypeById(pEven->periodTypeId);
    if (NULL != pEventPeriodType)
    {
        ComboControlPeriodType.SetWindowText(pEventPeriodType->description.c_str());
        if (pEven->periodTypeId == 2)
        {
            InitWday();
            char szValue[50] = {0};
            sprintf_s(szValue,sizeof(szValue),"%d",pEven->periodParameter);
            ComboControlTypeValue.SetWindowText(szValue);
        }
        else if (pEven->periodTypeId == 3)
        {
            InitMonthDay();
            char szValue[50] = {0};
            sprintf_s(szValue,sizeof(szValue),"%d",pEven->periodParameter);
            ComboControlTypeValue.SetWindowText(szValue);
        }
        ComboControlPeriodType.SetCurSel(pEven->periodTypeId);
    }
}

void CEditorView::ControlCleaRewardType()
{
    ControlRewards.DeleteAllItems();
    ControlRewards.UpdateData(FALSE);
}

void CEditorView::InitItemStringArray()
{
    ItemStringArray.RemoveAll();
    int Total = GettheItemDetail().GetItemCount();
    for (int i = 0;i < Total;++i)
    {
        CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(i);
        if (NULL != pItem)
        {
            ItemStringArray.Add(pItem->GetItemName());
        }
    }
}

int CEditorView::GetItemStringIndexByName(const std::string &name)
{
    if (name.empty())
    { return -1; }

    for (int i = 0;i < ItemStringArray.GetSize();++i)
    {
        std::string compString = ItemStringArray.GetAt(i);
        if (name == compString)
        {
            return i;
        }
    }
    return -1;
}

void CEditorView::InitRewardType()
{
    RewardStringArray.RemoveAll();
    for (int i = 0;i < theEventManager.GetEventRewardTypeSize();++i)
    {
        EventRewardType* pEventRewardType = theEventManager.GetEventRewardType(i);
        if (NULL != pEventRewardType)
        {
            RewardStringArray.Add(pEventRewardType->description.c_str());
        }
    }
}

void CEditorView::ControlCleaTypeValue()
{
    ComboControlTypeValue.ResetContent();
    ComboControlTypeValue.SetWindowText("");
    ComboControlTypeValue.UpdateData(FALSE);
}

void CEditorView::InitWday()
{
    ComboControlTypeValue.ResetContent();

    for (int i = 0;i < 7; ++i)
    {
        char buf[20] = {0};
        sprintf_s(buf,sizeof(buf),"%d",i);
        ComboControlTypeValue.AddString(buf);
    }
    ComboControlTypeValue.UpdateData( FALSE );
}

void CEditorView::InitMonthDay()
{
    ComboControlTypeValue.ResetContent();
    for (int i = 1;i <= 31; ++i)
    {
        char buf[20] = {0};
        sprintf_s(buf,sizeof(buf),"%d",i);
        ComboControlTypeValue.AddString(buf);
    }
    ComboControlTypeValue.UpdateData( FALSE );
}

void CEditorView::OnTvnSelchangedEventTree(NMHDR *pNMHDR, LRESULT *pResult)
{
    if (NULL != pNMHDR)
    {
        LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    }
    // TODO: Add your control notification handler code here
    EventViewTree.SetFocus();
    HTREEITEM select = EventViewTree.GetCursorItem();
    ControlClearBaseEventElement();
    ShowEventInfo(select);
    OnCbnSelchangeComboPeriodtype();
    if (NULL != pResult)
    {
        *pResult = 0;
    }
}

void CEditorView::ShowMap(const Event* pEven)
{
    if (NULL == pEven)
        return ;
    MapConfig::MapData* pMap = theMapConfig.GetMapDataById(pEven->mapId);
    if (NULL != pMap)
    {
        ComboControlMapId.SetWindowText(pMap->MapName.c_str());
        ComboControlMapId.UpdateData(FALSE);
        return;
    }
    if (pEven->mapId == -1)
        ComboControlMapId.SetWindowText("-1");
    else
        ComboControlMapId.SetWindowText("");
    ComboControlMapId.UpdateData(FALSE);
}

void CEditorView::ControlClearNpc()
{
    ComboControlNpcId.Clear();
    ComboControlNpcId.SetWindowText("");
}

void CEditorView::ShowNpc(const Event* pEven)
{
    if (NULL == pEven)
        return ;
    NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(pEven->npcId);
    if (NULL != pNpc)
    {
        ComboControlNpcId.SetWindowText(pNpc->name.c_str());
        ComboControlNpcId.UpdateData(FALSE);
        return;
    }
    if (pEven->npcId == -1)
        ComboControlNpcId.SetWindowText("-1");
    else
        ComboControlNpcId.SetWindowText("");
    ComboControlNpcId.UpdateData(FALSE);
}

void CEditorView::ShowEventInfo(const HTREEITEM &hItem)
{
    if (NULL != hItem)
    {
        CString EventName = EventViewTree.GetItemText(hItem);
        Event* pEvent = theEventManager.GetEventByName(EventName.GetBuffer(EventName.GetLength()));

        ShowBaseEventElement(pEvent);
        ShowBroadcastsElement(pEvent);
        ShowRewardsElement(pEvent);
        ShowDayElement(pEvent);
        ShowMap(pEvent);
        ShowNpc(pEvent);
        ShowPeriodType(pEvent);
        if (NULL != pEvent)
        {
            if (pEvent->isHot == TRUE)
                EventViewTree.SetItemBgColor(hItem,HOTLEFTRGB,HOTRIGHTRGB);
            else
                EventViewTree.SetItemBgColor(hItem,DEFAULTLEFTRGB,DEFAULTRIGHTRGB);
        }
    }
}

// CEditorView diagnostics

#ifdef _DEBUG
void CEditorView::AssertValid() const
{
    CFormView::AssertValid();
}

void CEditorView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

CEditorDoc* CEditorView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)));
    return (CEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CEditorView message handlers

void CEditorView::OnCbnSelchangeComboPeriodtype()
{
    // TODO: Add your control notification handler code here
    ComboControlPeriodType.UpdateData();
    CString Doc;
    ComboControlPeriodType.GetWindowText(Doc);
    if (Doc.IsEmpty())
    {
        ComboControlTypeValue.SetWindowText("");
        ComboControlTypeValue.EnableWindow(FALSE);
        ComboControlTypeValue.UpdateData(FALSE);
    }

    int Select = ComboControlPeriodType.GetCurSel();
    EventPeriodType* pEventPeriodType = theEventManager.GetEventPeriodTypeByIndex(Select);
    if (NULL != pEventPeriodType)
    {
        std::string FullName = ValueName.GetBuffer();
        FullName += "@";
        char szAddNameBuff[20];
        sprintf_s(szAddNameBuff,sizeof(szAddNameBuff),"%d",ValueHour);
        FullName += szAddNameBuff;
        Event* pEvent = theEventManager.GetEventByName(FullName.c_str());

        if ("每周" == pEventPeriodType->description )
        {
            InitWday();
            char szValue[50] = {0};
            if (NULL != pEvent)
            {
                sprintf_s(szValue,sizeof(szValue),"%d",pEvent->periodParameter);
                ComboControlTypeValue.EnableWindow(TRUE);
                ComboControlTypeValue.SetWindowText(szValue);
                ComboControlTypeValue.UpdateData();
                //闭关到月,设置值为-1
                ControlDayElement(FALSE);
                CWnd* pWindows = NULL;
                pWindows = GetDlgItem(IDC_ED_HOUR);
                if (NULL != pWindows)
                {
                    pWindows->EnableWindow(TRUE);
                    //pWindows->SetWindowText("");
                    pWindows->UpdateData(FALSE);
                }
                pWindows = GetDlgItem(IDC_ED_MINUTE);
                if (NULL != pWindows)
                {
                    pWindows->EnableWindow(TRUE);
                    //pWindows->SetWindowText("");
                    pWindows->UpdateData(FALSE);
                }
            }
        }
        else if("每月" == pEventPeriodType->description)
        {
            InitMonthDay();
            char szValue[50] = {0};
            if (NULL != pEvent)
            {
                sprintf_s(szValue,sizeof(szValue),"%d",pEvent->periodParameter);
                ComboControlTypeValue.EnableWindow(TRUE);
                ComboControlTypeValue.SetWindowText(szValue);
                ComboControlTypeValue.UpdateData();
            }
            ControlDayElement(FALSE);
            CWnd* pWindows = NULL;
            pWindows = GetDlgItem(IDC_ED_HOUR);
            if (NULL != pWindows)
            {
                pWindows->EnableWindow(TRUE);
                //pWindows->SetWindowText("");
                pWindows->UpdateData(FALSE);
            }
            pWindows = GetDlgItem(IDC_ED_MINUTE);
            if (NULL != pWindows)
            {
                pWindows->EnableWindow(TRUE);
                //pWindows->SetWindowText("");
                pWindows->UpdateData(FALSE);
            }
        }
        else if ("每日" == pEventPeriodType->description)
        {
            ControlDayElement(FALSE);
            CWnd* pWindows = NULL;
            pWindows = GetDlgItem(IDC_COMBO_PERIODVALUE);
            if (NULL != pWindows)
            {
                pWindows->EnableWindow(FALSE);
                pWindows->SetWindowText("");
                pWindows->UpdateData(FALSE);
            }
            pWindows = GetDlgItem(IDC_ED_HOUR);
            if (NULL != pWindows)
            {
                pWindows->EnableWindow(TRUE);
                //pWindows->SetWindowText("");
                pWindows->UpdateData(FALSE);
            }
            pWindows = GetDlgItem(IDC_ED_MINUTE);
            if (NULL != pWindows)
            {
                pWindows->EnableWindow(TRUE);
                //pWindows->SetWindowText("");
                pWindows->UpdateData(FALSE);
            }
        }
        else if ("自定义" == pEventPeriodType->description)
        {
            ControlDayElement(TRUE);
            ComboControlTypeValue.EnableWindow(FALSE);
            ComboControlTypeValue.SetWindowText("");
            ComboControlTypeValue.ResetContent();
            ComboControlTypeValue.UpdateData(FALSE);
            CWnd* pWindows = NULL;
            pWindows = GetDlgItem(IDC_COMBO_PERIODVALUE);
            if (NULL != pWindows)
            {
                pWindows->EnableWindow(FALSE);
                //pWindows->SetWindowText("");
                pWindows->UpdateData(FALSE);
            }
        }
        else
        {
            ControlDayElement(FALSE);
            ComboControlTypeValue.SetWindowText("");
            ComboControlTypeValue.ResetContent();
            ComboControlTypeValue.UpdateData(FALSE);
        }
    }
    UpdateData( );
}

void CEditorView::OnCbnEditchangeComboPeriodtype()
{
    // TODO: Add your control notification handler code here

}

void CEditorView::OnNMClickListReward(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    if (pNMIA)
    {
        CurItem = pNMIA->iItem;
        CurSubItem = pNMIA->iSubItem;
    }

    CurListCtrl = &ControlRewards;
    *pResult = 0;
}

void CEditorView::OnNMClickListBroadcasts(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (pNMIA)
    {
        CurItem = pNMIA->iItem;
        CurSubItem = pNMIA->iSubItem;
    }

    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_NAME);
    if (NULL != pWindows)
        pWindows->UpdateData();

    if (ValueName.IsEmpty())
        return;
    ControlBroadcasts.SetFocus();

    CurListCtrl = &ControlBroadcasts;
    *pResult = 0;
}

void CEditorView::OnNMDBLclkListBroadcasts(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    int nItem = -1;
    int nSubItem = -1;
    if (pNMIA)
    {
        nItem = pNMIA->iItem;
        nSubItem = pNMIA->iSubItem;
    }
    

    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_NAME);
    if (NULL != pWindows)
        pWindows->UpdateData();
    
    if (ValueName.IsEmpty())
        return;

    ControlRewards.SetFocus();

    CurListCtrl = &ControlBroadcasts;

    if ( nItem == -1)
        OnAddBroadcasts();

    *pResult = 0;
}

void CEditorView::OnNMDBLclkListReward(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    int nItem = -1;
    int nSubItem = -1;
    if (pNMIA)
    {
        nItem = pNMIA->iItem;
        nSubItem = pNMIA->iSubItem;
    }

    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_NAME);
    if (NULL != pWindows)
        pWindows->UpdateData();

    if (ValueName.IsEmpty())
        return;

    CurListCtrl = &ControlRewards;

    if (nItem == -1)
        OnAddReward();
    
    *pResult = 0;
}

void CEditorView::OnAddBroadcasts()
{
    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_NAME);
    if (NULL != pWindows)
        pWindows->UpdateData();

    std::string FullName = ValueName.GetBuffer();
    FullName += "@";
    char szAddNameBuff[20];
    sprintf_s(szAddNameBuff,sizeof(szAddNameBuff),"%d",ValueHour);
    FullName += szAddNameBuff;
    Event* pEvent = theEventManager.GetEventByName(FullName.c_str());
    if (NULL != pEvent)
    {
        Event::Broadcast broadcast;
        broadcast.content = "";
        broadcast.offsetTime = -1;
        pEvent->AddEventBroadcast(broadcast);
        AddBroadcastsElement(broadcast);
    }
    //UpdateData(FALSE);
}

void CEditorView::OnAddReward()
{
    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_NAME);
    if (NULL != pWindows)
        pWindows->UpdateData();

    std::string FullName = ValueName.GetBuffer();
    FullName += "@";
    char szAddNameBuff[20];
    sprintf_s(szAddNameBuff,sizeof(szAddNameBuff),"%d",ValueHour);
    FullName += szAddNameBuff;

    Event* pEvent = theEventManager.GetEventByName(FullName.c_str());
    if (NULL != pEvent)
    {
        Event::Reward reward;
        reward.typeId = 0;
        reward.id = -1;
        reward.count = -1;
        pEvent->AddEventReward(reward);
        AddRewardElement(reward);
    }
    UpdateData(FALSE);
}

void CEditorView::AddBroadcastsElement(Event::Broadcast &broadcast)
{
    int TotalNum = ControlBroadcasts.GetItemCount();
    char szOffset[50]={0};
    sprintf_s(szOffset,sizeof(szOffset),"%d",broadcast.offsetTime);
    ControlBroadcasts.InsertItem(TotalNum,szOffset);
    ControlBroadcasts.SetItemText(TotalNum,1,broadcast.content.c_str());
    ControlBroadcasts.SetEdit(TotalNum,0);
    ControlBroadcasts.SetEdit(TotalNum,1);
    ControlBroadcasts.UpdateData(FALSE);
}

void CEditorView::AddRewardElement(Event::Reward &reward)
{
    int TotalNum = ControlRewards.GetItemCount();
    char sztypeId[150] = { 0 };
    EventRewardType* pEventRewardType = theEventManager.GetEventRewardType(reward.typeId);
    if (NULL != pEventRewardType)
        sprintf_s(sztypeId,sizeof(sztypeId),"%s",pEventRewardType->description.c_str());

    char szId[50] = { 0 };
    sprintf_s(szId,sizeof(szId),"%d",reward.id);

    char szCount[50] = { 0 };
    sprintf_s(szCount,sizeof(szCount),"%d",reward.count);

    ControlRewards.InsertItem(TotalNum,sztypeId);
    ControlRewards.SetItemText(TotalNum,1,szId);
    ControlRewards.SetItemText(TotalNum,2,szCount);
    ControlRewards.SetComboBox(TotalNum, 0, TRUE, &RewardStringArray, RewardStringArray.GetCount(), 0);
    ControlRewards.SetComboBox(TotalNum,1,TRUE,&ItemStringArray,ItemStringArray.GetCount(),0);
    ControlRewards.SetEdit(TotalNum,2);
    ControlRewards.UpdateData(FALSE);
}

LRESULT CEditorView::OnSelectList(WPARAM m_nComboItem, LPARAM m_nSubComboItem)
{
    if (m_nComboItem >= 0 && m_nSubComboItem >= 0)
    {
        OnEndControlRewardsEnd(m_nComboItem,m_nSubComboItem);
//         if (CurListCtrl == &ControlBroadcasts)
//         {
//             OnEditControlBroadcastsEnd(nItem,nSubItem);
//             return 1;
//         }
//         else if(CurListCtrl == &ControlRewards)
//         {
//             OnEndControlRewardsEnd(nItem,nSubItem);
//             return 2;
//         }
    }
    return ERROR_SUCCESS;
}

LRESULT CEditorView::OnEditEnd(WPARAM nItem, LPARAM nSubItem)
{
    if (nItem >= 0 && nSubItem >= 0)
    {
        if (CurListCtrl == &ControlBroadcasts)
        {
            OnEditControlBroadcastsEnd(nItem,nSubItem);
            return 1;
        }
        else if(CurListCtrl == &ControlRewards)
        {
            OnEndControlRewardsEnd(nItem,nSubItem);
            return 2;
        }
    }
    return ERROR_SUCCESS;
}

void CEditorView::OnEditControlBroadcastsEnd(int Item,int SubItem)
{
    CString OffsetValue =  ControlBroadcasts.GetItemText(Item,0);
    CString DesValue =  ControlBroadcasts.GetItemText(Item,1);

    std::string FullName = ValueName.GetBuffer();
    FullName += "@";
    char szAddNameBuff[20];
    sprintf_s(szAddNameBuff,sizeof(szAddNameBuff),"%d",ValueHour);
    FullName += szAddNameBuff;
    Event* pEven = theEventManager.GetEventByName(FullName.c_str());
    if (NULL != pEven)
    {
        Event::Broadcast* pBroadcast = pEven->GetEventBroadcastByIndex(Item);
        if (NULL != pBroadcast)
        {
            int offset = 0;
            if (IsNum(OffsetValue.GetBuffer()))
                 offset = atoi(OffsetValue.GetBuffer());
            if (offset > pEven->duration)
            {
                MessageBox("不可以超过持续时间","Warning",MB_ICONERROR|MB_OK);
                return;
            }
            pBroadcast->offsetTime  = offset;
            pBroadcast->content     = DesValue.GetBuffer();
        }
    }
    ControlBroadcasts.UpdateData(FALSE);
}

void CEditorView::OnEndControlRewardsEnd(int Item,int SubItem)
{
    CString TypeValue =  ControlRewards.GetItemText(Item,0);
    CString Value =  ControlRewards.GetItemText(Item,1);
    CString CountValue =  ControlRewards.GetItemText(Item,2);
    std::string FullName = ValueName.GetBuffer();
    FullName += "@";
    char szAddNameBuff[20];
    sprintf_s(szAddNameBuff,sizeof(szAddNameBuff),"%d",ValueHour);
    FullName += szAddNameBuff;
    Event* pEven = theEventManager.GetEventByName(FullName.c_str());
    if (NULL != pEven)
    {
        Event::Reward* pReward = pEven->GetEventRewardByIndex(Item);
        if (NULL != pReward)
        {
            int TypeId = theEventManager.GetRewardTypeByDes(TypeValue.GetBuffer());
            if (TypeId != -1)
                pReward->typeId = TypeId;
            CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(Value);
            if (NULL != pItem)
                pReward->id  = pItem->ustItemID;
            else
                pReward->id = -1;

            if (IsNum(CountValue))
                pReward->count= atoi(CountValue.GetBuffer());
            else
                pReward->count = -1;
        }
    }
    ControlRewards.UpdateData(FALSE);
}

bool CEditorView::IsNum(const char* string)
{
    if (NULL == string)
        return false;

    if( *string == '-' )
        *string++;

    if( *string == 0 )
        return false;

    while( *string != 0 )
    {
        if( *string < '0' || *string > '9' )
            return false;
        string++;
    }
    return true; 
}

void CEditorView::OnAddEvent()
{
    // TODO: Add your command handler code here
    Event addEvent;
    addEvent.needLevel = 1;
    addEvent.quality = 5;
    addEvent.year = -1;
    addEvent.month = -1;
    addEvent.day = -1;
    addEvent.hour = 1;
    addEvent.minute = 1;
    addEvent.name = "添加@";
    char buf[20];
    sprintf_s(buf,sizeof(buf),"%d",addEvent.hour);
    addEvent.name += buf;
    addEvent.mapId = -1;
    addEvent.mapPosX = -1;
    addEvent.mapPosY = -1;
    addEvent.npcId = -1;
    addEvent.duration = 0;
    addEvent.count = -1;
    addEvent.completeTimeVarIndex = -1;
    addEvent.durationDescription = "";
    addEvent.isHot = false;
    addEvent.isPivot = FALSE;
    addEvent.periodParameter = 0;
    addEvent.periodTypeId = 0;
    addEvent.scriptId = -1;
    addEvent.eventItemId = ErrorUnsignedShortID;

    theEventManager.AddEvent(addEvent);
    EventViewTree.InsertItem(addEvent.name.c_str());
    EventViewTree.SetFocus();
    UpdateData(FALSE);
}



void CEditorView::OnMsgDeletEvent()
{
    // TODO: Add your command handler code here
    CWnd* pWnd = GetFocus();
    if (NULL == pWnd)
    { return; }

    if (ValueName.IsEmpty())
    { return; }

    int Id = pWnd->GetDlgCtrlID();
    if ( IDC_LIST_BROADCASTS == Id )
    {
        OnDeleteBroadcast();
        return;
    }
    else if ( IDC_LIST_REWARD == Id )
    {
        OnDeleteReward();
        return;
    }
    else if (IDC_CALENDARTREE == Id)
    {
        OnDeleteEvent();
    }
}

void CEditorView::OnDeleteEvent()
{
    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_NAME);
    if (NULL != pWindows)
        pWindows->UpdateData();
    else
        return;

    HTREEITEM pHtreeitem = EventViewTree.GetSelectedItem();
    if (NULL != pHtreeitem)
    {
        CString Name = EventViewTree.GetItemText(pHtreeitem);
        if ( theEventManager.DeleteEvent(Name.GetBuffer()) )
        {
            HTREEITEM pNextHtreeitem = NULL;
            pNextHtreeitem = EventViewTree.GetNextSiblingItem(pHtreeitem);
            if (NULL == pNextHtreeitem)
            {
                pNextHtreeitem = EventViewTree.GetPrevSiblingItem(pHtreeitem);
            }
            // 清理树
            if ( EventViewTree.DeleteItem(pHtreeitem) )
            {
                ControlClearBaseEventElement();
                ControlClearNpc();
                ControlCleaTypeValue();
                ControlCleaRewardType();
                ControlClearBroadcastsElement();
                ControlClearDayElement();
                ControlClearMap();
                
                if (NULL != pNextHtreeitem)
                {
                    EventViewTree.SelectItem(pNextHtreeitem);
                    OnTvnSelchangedEventTree(NULL,NULL);
                }
            }
        }
    }
    EventViewTree.SetFocus();
}

bool CEditorView::ApplyEvent()
{
    if (!UpdateData())
    {
        MessageBox("请检查数据,然后保存","Warning",MB_OK|MB_ICONWARNING);
        return false;
    }

    HTREEITEM pHtreeitem = EventViewTree.GetSelectedItem();
    if ( NULL == pHtreeitem )
        return false;

    CString strOldEventName;
    strOldEventName = EventViewTree.GetItemText(pHtreeitem);
    if (strOldEventName.IsEmpty())
        return false;
    //Event* pEvent = theEventManager.GetEventByName(strOldEventName.GetBuffer());
    Event event;
    event.description = ValueDescription;
    event.duration = ValueDuration;
    event.durationDescription = ValueDurationDes.GetBuffer();
    event.isHot = ValueHot;
    event.isPivot = ValuePivot;
    event.scriptId = (short)ValueScriptId;
    event.eventItemId = (unsigned short)ValueItemId;

    CString NPCName;
    ComboControlNpcId.GetWindowText(NPCName);
    if (NPCName != "-1")
    {
        NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByName(NPCName.GetBuffer());
        if (NULL == pNpc)
        {
            MessageBox("没有找到对应的NPC，请检查输入的NPC名是否正确","Warning",MB_ICONWARNING|MB_OK);
            return false;
        }
        event.npcId = pNpc->id;
    }
    else
        event.npcId = -1;

    CString MapName;
    ComboControlMapId.GetWindowText(MapName);
    if (MapName != "-1")
    {
        MapConfig::MapData* pData = theMapConfig.GetMapDataByName(MapName.GetBuffer());
        if (NULL == pData)
        {
            MessageBox("没有找到对应的地图，请检查输入的地图名是否正确","Warning",MB_ICONWARNING|MB_OK);
            return false;
        }
        event.mapId = pData->Id;
    }
    else
        event.mapId = -1;
    
    event.mapPosX = ValueMapPosX;
    event.mapPosY = ValueMapPosY;
    event.count = ValueConunt;
    int SelectLevel = ValueNeedLevel.GetCurSel()+1;
    if (SelectLevel == 0)
        SelectLevel = -1;
    event.needLevel = SelectLevel;
    event.completeTimeVarIndex = ValueCompleteId;

//     if (ValueQualty< 1|| ValueQualty > 5)
//     {
//         ValueQualty = 5;
//     }
    event.quality = ValueQualty.GetCurSel()+1;
    if (event.quality == 0)
        event.quality = -1;

    CString PeriodTypeName;
    ComboControlPeriodType.GetWindowText(PeriodTypeName);

    EventPeriodType* pEventPeriodType = theEventManager.GetEventPeriodTypeByDes(PeriodTypeName.GetBuffer());
    if (NULL == pEventPeriodType)
    {
        MessageBox("没有找到对应的PeriodType，请检查输入是否正确","Warning",MB_ICONWARNING|MB_OK);
        return false;
    }
    event.periodTypeId  = pEventPeriodType->id;
    if (PeriodTypeName == "每月"||PeriodTypeName == "每周")
    {
        CString Value;
        ComboControlTypeValue.GetWindowText(Value);
        if (Value.IsEmpty())
        {
            Value = "-1";
        }
        if (!IsNum(Value.GetBuffer()))
        {
            return false;
        }
        event.periodParameter = atoi(Value.GetBuffer());
    }
    else
        event.periodParameter = -1;

    SYSTEMTIME st;
    GetSystemTime(&st);
#if 0
    if (ValueYear-1 < st.wYear && ValueYear-1 !=-1)
    {
        MessageBox("设置的时间小于当前年份，已经校正为当前系统年份","Warning",MB_ICONWARNING|MB_OK);
        ValueYear = st.wYear;
    }
    event.year = ValueYear-1;
    event.month = ValueMonth-1;
    if (ValueDay == 0)
    {
        ValueDay = -1;
    }
    event.day = ValueDay;
    event.hour = ValueHour;
    event.minute = ValueMinute;
#endif
#if 1
	event.year=ValueYear;
	event.month=ValueHour;
	event.day=ValueDay;
	event.hour=ValueHour;
	event.minute=ValueMinute;
#endif

    event.name = ValueName.GetBuffer();
    event.name += "@";
    char buf[20];
    sprintf_s(buf,sizeof(buf),"%d",event.hour);
    event.name += buf;
    if (event.name == strOldEventName.GetBuffer())
    {
        if (event.isHot == TRUE)
            EventViewTree.SetItemBgColor(pHtreeitem,HOTLEFTRGB,HOTRIGHTRGB);
        else
            EventViewTree.SetItemBgColor(pHtreeitem,DEFAULTLEFTRGB,DEFAULTRIGHTRGB);
        return theEventManager.ModifiyEvent(event.name.c_str(),event);
    }
    if (theEventManager.ModifiyEvent(strOldEventName.GetBuffer(),event))
    {
        EventViewTree.SetItemText(pHtreeitem,event.name.c_str());
        if (event.isHot == TRUE)
            EventViewTree.SetItemBgColor(pHtreeitem,HOTLEFTRGB,HOTRIGHTRGB);
        else
            EventViewTree.SetItemBgColor(pHtreeitem,DEFAULTLEFTRGB,DEFAULTRIGHTRGB);
    }
    return true;
}

void CEditorView::OnDeleteBroadcast()
{
    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_NAME);
    if (NULL != pWindows)
        pWindows->UpdateData();

    std::string FullName = ValueName.GetBuffer();
    FullName += "@";
    char szAddNameBuff[20];
    sprintf_s(szAddNameBuff,sizeof(szAddNameBuff),"%d",ValueHour);
    FullName += szAddNameBuff;
    Event* pEvent = theEventManager.GetEventByName(FullName.c_str());
    if (NULL != pEvent)
    {
        int Offset = 0;
        char szOffset[512] = {0};
        ControlBroadcasts.GetItemText(CurItem,0,szOffset,sizeof(szOffset));
        if (IsNum(szOffset))
            Offset = atoi(szOffset);
        if ( pEvent->DeleteEventBroadcast(Offset) )
            ControlBroadcasts.DeleteItem(CurItem);
    }
    UpdateData(FALSE);
}

void CEditorView::OnDeleteReward()
{
    CWnd* pWindows = NULL;
    pWindows = GetDlgItem(IDC_ED_NAME);
    if (NULL != pWindows)
        pWindows->UpdateData();

    std::string FullName = ValueName.GetBuffer();
    FullName += "@";
    char szAddNameBuff[20];
    sprintf_s(szAddNameBuff,sizeof(szAddNameBuff),"%d",ValueHour);
    FullName += szAddNameBuff;
    Event* pEvent = theEventManager.GetEventByName(FullName.c_str());
    if (NULL != pEvent)
    {
        if (pEvent->DeleteEventRewardByIndex(CurItem))
            ControlRewards.DeleteItem(CurItem);
//         int TypeId = 0;
//         char szTypeId[512] = {0};
//         ControlRewards.GetItemText(CurItem,0,szTypeId,sizeof(szTypeId));
//         int Type = theEventManager.GetEventRewardType(szTypeId);
// //         if (IsNum(szTypeId))
// //             TypeId = atoi(szTypeId);
//         if ( pEvent->DeleteEventReward(Type) )
//             ControlRewards.DeleteItem(CurItem);
    }
    UpdateData(FALSE);
}

void CEditorView::OnSaveEvent()
{
    // TODO: Add your command handler code here
    if (!ApplyEvent())
        return;
    if (!theEventManager.Save("..\\Data\\Config\\Event.Config"))
    {
        MessageBox("保存..\\Data\\Config\\Event.Config失败!请检查是否存在路径","warning",MB_ICONWARNING|MB_OK);
    }
    else
    {
        MessageBox("保存..\\Data\\Config\\Event.Config OK!","通知",MB_OK);
    }
}

void CEditorView::OnNMDblclkEventTree(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    OnAddEvent();
    *pResult = 0;
}

void CEditorView::OnApplyEvent()
{
    // TODO: Add your command handler code here
    //ApplyEvent();
    if (ApplyEvent())
    {
        CWnd* pFocus = GetFocus();
        MessageBox("修改成功","成功",MB_OK);
        EventViewTree.SetFocus();
        if (pFocus)
            pFocus->SetFocus();
    }
}
void CEditorView::OnAddBroadcastOrReward()
{
    // TODO: Add your command handler code here
    if (CurListCtrl == &ControlBroadcasts)
    {
        OnAddBroadcasts();
    }
    else if (CurListCtrl == &ControlRewards)
    {
        OnAddReward();
    }
}
