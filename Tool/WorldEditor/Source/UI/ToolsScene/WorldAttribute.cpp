// WorldAttribute.cpp : implementation file
//

#include "stdafx.h"
#include "WorldEditor.h"
#include "WorldAttribute.h"

#include "MeTerrain/WorldTile.h"
// deleted, [8/18/2010 zhangjiayi]
#include "ItemDetail.h"

// WorldAttribute dialog

IMPLEMENT_DYNAMIC(WorldAttribute, CDialog)

WorldAttribute::WorldAttribute(CWnd* pParent /*=NULL*/)
	: CDialog(WorldAttribute::IDD, pParent)
    , ValueStatusLevel(1)
    , CurMap(NULL)
    //, SystemCreate(FALSE)
	//, SunLightRander(FALSE) //add by yanli 2010-6-21
    , ValueRegionOffsetX(0)
    , ValueRegionOffsetY(0)
    , ValueRegionEdge(1024)
    , m_CStrMapTip(_T(""))
    , m_CStrMapNameColor(_T(""))
{

}

WorldAttribute::~WorldAttribute()
{
}

void WorldAttribute::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_CHINESENAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_SCRIPTFILE, m_editScripFile );
    DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
    DDX_Control(pDX, IDC_EDIT_MINLEVEL, m_editMinLevel);
    
    DDX_Control(pDX, IDC_EDIT_TIME, m_editDuration);
    DDX_Control(pDX, IDC_EDIT_MAPCOUNT, m_editCount);
    DDX_Control(pDX, IDC_EDIT_UNITCOUNT, m_editUnitCount);

    DDX_Control(pDX, IDC_CHECK_SHOWFOOT, m_checkShowFoot);
	DDX_Control(pDX, IDC_CHECK_RIDE, m_checkRide);
	DDX_Control(pDX, IDC_CHECK1, m_checkCanCallPet);
	//DDX_Check(pDX, IDC_CHECK_SYSTEMCREATE, SystemCreate);
	DDX_Control(pDX, IDC_CHECK_SYSTEMCREATE, m_systemCreate);
	DDX_Control(pDX, IDC_CHECK_SUNLIGHTENBLE, m_sunLightRender);		 //add by yanli 2010-6-21
    //DDX_Control(pDX, IDC_CHECK_CANPK, m_checkCanPk);

    DDX_Control(pDX, IDC_TREE_STATUS, StatusTree);
    DDX_Control(pDX, IDC_COMBO_STATUS, ComboStatus);
    DDX_Text(pDX, IDC_EDIT_STATUSLEVEL, ValueStatusLevel);
    DDV_MinMaxShort(pDX, ValueStatusLevel, 1, 10);
    
//	DDX_Check(pDX, IDC_CHECK_SUNLIGHTENBLE, SunLightRander); 

    DDX_Text(pDX, IDC_EDIT_REGIONOFFSETX, ValueRegionOffsetX);
    DDV_MinMaxInt(pDX, ValueRegionOffsetX, 0, 1024);
    DDX_Text(pDX, IDC_EDIT_REGIONOFFSETY, ValueRegionOffsetY);
    DDV_MinMaxInt(pDX, ValueRegionOffsetY, 0, 1024);
    DDX_Text(pDX, IDC_EDIT_REGION_EDGE, ValueRegionEdge);
    DDV_MinMaxInt(pDX, ValueRegionEdge, 0, 1024);
    DDX_Control(pDX, IDC_COMBO_CANPK, m_ComboCanPK);
    DDX_Text(pDX, IDC_ED_MapTip, m_CStrMapTip);
    DDX_Text(pDX, IDC_ED_MapNameColor, m_CStrMapNameColor);
}


BEGIN_MESSAGE_MAP(WorldAttribute, CDialog)
	ON_BN_CLICKED(IDOK, &WorldAttribute::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &WorldAttribute::OnCbnSelchangeComboType)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &WorldAttribute::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &WorldAttribute::OnBnClickedButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_MODIFIY, &WorldAttribute::OnBnClickedButtonModifiy)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_STATUS, &WorldAttribute::OnTvnSelchangedTreeStatus)
END_MESSAGE_MAP()


// WorldAttribute message handlers
BOOL WorldAttribute::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL WorldAttribute::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitInformation();

	CWorldTile* pTile = CURRENTTILE;
	if (pTile == NULL) { return TRUE; }

	m_editName.SetWindowText(pTile->GetTileName());
	m_editScripFile.SetWindowText(pTile->GetScriptFilePath().c_str());
	m_comboType.SetCurSel(pTile->GetMapType());

	ChangeTypeInfo(pTile->GetMapType());

	SetEditInt(m_editMinLevel, pTile->GetMinLevel());
	
	m_checkShowFoot.SetCheck(pTile->GetShowFootPrint());
	m_checkRide.SetCheck(!pTile->GetRide());

	m_sunLightRender.SetCheck(pTile->IsSunLightRender());		//add by yanli 2010-6-21
	m_systemCreate.SetCheck(pTile->GetSystemCreate());
    //SystemCreate = pTile->GetSystemCreate();

    m_ComboCanPK.SetCurSel(pTile->GetCanPk());
	//m_checkCanPk.SetCheck(pTile->GetCanPk());

	int nDuration = pTile->GetDuration();
	if(nDuration > 0) { SetEditInt(m_editDuration, nDuration); }

	int nCount = pTile->GetCount();
	if (nCount > 0) { SetEditInt(m_editCount, nCount); }

	int nUnitCount = pTile->GetUnitCount();
	if ( nUnitCount > 0) { SetEditInt(m_editUnitCount, nUnitCount); }
    
	//SunLightRander = pTile->IsSunLightRender(); 
	//SunLightRander.SetCheck(!pTile->IsSunLightRender());

    
    ValueRegionOffsetX = pTile->GetRegionOffsetX();
    ValueRegionOffsetY = pTile->GetRegionOffsetY();
    ValueRegionEdge    = pTile->GetRegionEdge();
    m_CStrMapTip       = pTile->GetMapTip();
    m_CStrMapNameColor = pTile->GetMapNameColor();

	// deleted, [8/18/2010 zhangjiayi]
    MapConfig::MapData* pMap = theMapConfig.GetMapDataById(pTile->GetMapId());
    if (NULL != pMap)
    {
        CurMap = pMap;
        int MaxIndex = pMap->GetStatusSize();
        for (int statusIndex = 0;statusIndex < MaxIndex;++statusIndex)
        {
            MapConfig::Status* status = pMap->GetStatusByIndex(statusIndex);
            if (NULL != status)
            {
                CItemDetail::SItemCommon* pStatus = GettheItemDetail().GetItemByID(status->Id);
                if (NULL != pStatus)
                {
                    StatusTree.InsertItem(pStatus->GetItemName());
                }
            }
        }
    }

	// 是否允许召唤副将
	m_checkCanCallPet.SetCheck(CurMap->CanPet);

    UpdateData(FALSE);
	return TRUE;
}

void WorldAttribute::InitInformation()
{
	m_comboType.ResetContent();

    //初始化地图类型
	m_comboType.AddString("普通地图");
	m_comboType.AddString("团队副本");
	m_comboType.AddString("人数限定副本");
	m_comboType.AddString("时间副本");
	m_comboType.AddString("多团队副本");
    m_comboType.AddString("帮派副本");

    m_ComboCanPK.ResetContent();
    //初始化pk下拉条
    m_ComboCanPK.InsertString(MapConfig::MapData::EPKM_UnAllow_PK,"禁止PK");
    m_ComboCanPK.InsertString(MapConfig::MapData::EPKM_Allow_PK,"允许PK");
    m_ComboCanPK.InsertString(MapConfig::MapData::EPKM_Free_PK,"自由PK(PK值不变)");
    m_ComboCanPK.InsertString(MapConfig::MapData::EPKM_Challenge_PK,"强制PK(打开保护也可以进行PK)");

	m_comboType.SetCurSel(0);


    ComboStatus.ResetContent();
	// deleted, [8/18/2010 zhangjiayi]
    for (int i = CItemDetail::StartID_Status;i < CItemDetail::EndID_Status;++i)
    {
        CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(i);
        if (NULL != pItem)
        {
            ComboStatus.AddString(pItem->GetItemName());
        }
    }


    ComboStatus.SetWindowText("");
}

void WorldAttribute::SetEditInt(CEdit &xEdit, int nValue)
{
	if (xEdit.m_hWnd != NULL)
	{
		CString strText = "";
		strText.Format("%d", nValue);
		xEdit.SetWindowText(strText);
	}	
}

int WorldAttribute::GetEditInt(CEdit &xEdit, int nDefault)
{
	if (xEdit.m_hWnd == NULL)
	{
		return nDefault;
	}

	CString strValue = "";
	xEdit.GetWindowText(strValue);
	if (strValue.IsEmpty())
	{
		return nDefault;
	}

	return atoi(strValue.GetBuffer());
}

void WorldAttribute::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
    UpdateData();

	CWorldTile* pTile = CURRENTTILE;
	if (pTile == NULL) { OnOK(); return; }

	CString strName = "";
	m_editName.GetWindowText(strName);
	if (strName.IsEmpty())
	{
		AfxMessageBox("请输入地图中文名称！");
		return;
	}

	pTile->SetTileName(strName.GetBuffer());
	CurMap->MapName = strName;

	m_editScripFile.GetWindowText(strName);
	pTile->SetScripFilePath(strName.GetBuffer());
	CurMap->ScriptFile = strName;

	pTile->SetMapType(m_comboType.GetCurSel());
	CurMap->Type = m_comboType.GetCurSel();

	pTile->SetMinLevel( GetEditInt(m_editMinLevel, 1));
	CurMap->MinPlayerLevel = GetEditInt(m_editMinLevel, 1);

	pTile->SetShowFootPrint(m_checkShowFoot.GetCheck());
	CurMap->ShowFootPrint = m_checkShowFoot.GetCheck();
	
	pTile->SetRide(!m_checkRide.GetCheck());
	CurMap->CanRide = !m_checkRide.GetCheck();
	
	CurMap->CanPet = m_checkCanCallPet.GetCheck();

	pTile->SetSystemCreate(m_systemCreate.GetCheck());
	CurMap->SystemCreate = m_systemCreate.GetCheck();

	/*pTile->SetSystemCreate(SystemCreate);
	CurMap->SystemCreate = SystemCreate;*/

	pTile->SetSunLightRender(m_sunLightRender.GetCheck()); //add by yanli 2010-6-21
	CurMap->m_bSunLightRender = m_sunLightRender.GetCheck();
    
	pTile->SetCanPk(m_ComboCanPK.GetCurSel());
	CurMap->CanPk = m_ComboCanPK.GetCurSel();
	
	//pTile->SetCanPk(m_checkCanPk.GetCheck());
	pTile->SetDuration(GetEditInt(m_editDuration, 0));
	CurMap->Duration = GetEditInt(m_editDuration, 0);
	
	pTile->SetCount(GetEditInt(m_editCount, 0));
	CurMap->Count = GetEditInt(m_editCount, 0);
	
	pTile->SetUnitCount(GetEditInt(m_editUnitCount, 0));
	CurMap->UnitCount = GetEditInt(m_editUnitCount, 0);
    
	pTile->SetRegionOffsetX(ValueRegionOffsetX);
	CurMap->m_nRegionOffsetX = ValueRegionOffsetX;
    
	pTile->SetRegionOffsetY(ValueRegionOffsetY);
	CurMap->m_nRegionOffsetY = ValueRegionOffsetY;
    
	pTile->SetRegionEdge(ValueRegionEdge);
	CurMap->m_nRegionEdge = ValueRegionEdge;
    
	pTile->SetMapNameColor(m_CStrMapNameColor.GetBuffer());
	CurMap->MapNameColor = m_CStrMapNameColor;
    
	pTile->SetMapTip(m_CStrMapTip.GetBuffer());
	CurMap->MapTip = m_CStrMapTip;
	
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( pTile );

	OnOK();
}

void WorldAttribute::OnCbnSelchangeComboType()
{
	// TODO: Add your control notification handler code here

	ChangeTypeInfo(m_comboType.GetCurSel());
}


void WorldAttribute::ChangeTypeInfo(int nType)
{
	if (nType <= 0)
	{
		m_editDuration.EnableWindow(FALSE);
		m_editCount.EnableWindow(FALSE);
		m_editUnitCount.EnableWindow(FALSE);
	}
	else
	{
		m_editDuration.EnableWindow(TRUE);
		m_editCount.EnableWindow(TRUE);
		m_editUnitCount.EnableWindow(TRUE);
	}
}

void WorldAttribute::OnBnClickedButtonAdd()
{
    // TODO: Add your control notification handler code here
    if(!UpdateData())
        return;
     MapConfig::Status add;
//     add.Id = CItemDetail::StartID_Status;
     add.Level = ValueStatusLevel;

    CString statusName;
    ComboStatus.GetWindowText(statusName);
    if ( statusName.IsEmpty() )
    { return; }

	// deleted, [8/18/2010 zhangjiayi]
//     CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(statusName);
//     if (NULL != pItem)
//     {
//         StatusTree.InsertItem(pItem->GetItemName());
//         add.Id = pItem->ustItemID;
//     }
//     else
//         return;
// 
    if (NULL != CurMap)
    {
        CurMap->AddStatus(add);
    }
}

void WorldAttribute::OnBnClickedButtonDel()
{
    // TODO: Add your control notification handler code here
    HTREEITEM select = StatusTree.GetSelectedItem();
    if (NULL == select)
    { return; }

    StatusTree.DeleteItem(select);

    int id = GetSelectItemIndex(select);
    if (id != -1 && NULL != CurMap)
    {
        if (!CurMap->DelStatus(id-1))
            MessageBox("删除失败!没找到对应Status","失败");
    }
    
}

void WorldAttribute::OnBnClickedButtonModifiy()
{
    // TODO: Add your control notification handler code here
    if (!UpdateData())
    { return; }

    HTREEITEM select = StatusTree.GetSelectedItem();
    if (NULL == select)
    { return; }

    int id = GetSelectItemIndex(select);
    if (id == -1)
    { return; }

    MapConfig::Status modifiy;

    CString SelectStatueName;
    ComboStatus.GetWindowText(SelectStatueName);
    CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(SelectStatueName.GetBuffer());
    if (NULL != pItem)
    {
        modifiy.Id = pItem->ustItemID;
    }
    modifiy.Level = ValueStatusLevel;
    
    if (NULL != CurMap)
    {
        if (!CurMap->SetStatus(id-1,modifiy))
            MessageBox("修改失败,没有找到对应的Status","失败");
        else
        {
            StatusTree.SetItemText(select,SelectStatueName.GetBuffer());
            CWnd* curFocus = GetFocus();
            StatusTree.SetFocus();
            StatusTree.UpdateData();
            if (curFocus != NULL)
            {
                curFocus->SetFocus();
            }
        }
    }
}

int WorldAttribute::GetSelectItemIndex(HTREEITEM select)
{
    if (NULL == select)
    { return -1; }

    int selectId = 0;
    while (select != NULL)
    {
        select = StatusTree.GetNextItem(select,TVGN_PREVIOUS);
        selectId++;
    }
    return selectId;
}

void WorldAttribute::OnTvnSelchangedTreeStatus(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: Add your control notification handler code here
    ComboStatus.SetWindowText("");
    ComboStatus.UpdateData(FALSE);

    HTREEITEM select = StatusTree.GetSelectedItem();
    int id = GetSelectItemIndex(select);
	// deleted, [8/18/2010 zhangjiayi]
    if (id != -1)
    {
        MapConfig::Status* selectStatus = CurMap->GetStatusByIndex(id-1);
        if (NULL != selectStatus)
        {
            CItemDetail::SItemCommon* pStatus = GettheItemDetail().GetItemByID(selectStatus->Id);
            if (NULL != pStatus)
            {
                ComboStatus.SetWindowText(pStatus->GetItemName());
                ValueStatusLevel = selectStatus->Level;
            }
        }
    }
    UpdateData(FALSE);
    *pResult = 0;
}
