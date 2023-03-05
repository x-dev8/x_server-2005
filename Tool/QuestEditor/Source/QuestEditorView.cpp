// EditorView.cpp : implementation of the CEditorView class
//

#include "stdafx.h"
#include "QuestEditor.h"

#include "QuestEditorDoc.h"
#include "QuestEditorView.h"

#include "StringFileChange.h"
#include "NpcFileChange.h"
#include "QuestFind.h"
#include "DropMonsterDialog.h"
#include "DropItemDialog.h"
#include "QuestStringEdit.h"
#include "ItemDetailConfig.h"
#include "CountryConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CQuestEditorView *theEditor;
// CEditorView

IMPLEMENT_DYNCREATE(CQuestEditorView, CFormView)

BEGIN_MESSAGE_MAP(CQuestEditorView, CFormView)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP

	ON_NOTIFY(NM_CLICK, IDC_LIST4, &CQuestEditorView::OnNMClickListReward)
	ON_NOTIFY(NM_CLICK, IDC_LIST6, &CQuestEditorView::OnNMClickListPreRequiement)
	ON_NOTIFY(NM_CLICK, IDC_LIST7, &CQuestEditorView::OnNMClickListPostRequiement)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CQuestEditorView::OnNMClickListProprety)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CQuestEditorView::OnNMClickTreeItem)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CQuestEditorView::OnTvnSelchangedTreeQuest)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST7, &CQuestEditorView::OnNMDClickListPostRequiement)
	ON_NOTIFY(NM_RCLICK, IDC_LIST7, &CQuestEditorView::OnNMRclickListPostRequeiment)
	
	ON_NOTIFY(NM_RCLICK, IDC_LIST7, &CQuestEditorView::OnNMRclickListPostRequeiment)
	ON_NOTIFY(NM_RCLICK, IDC_LIST6, &CQuestEditorView::OnRClickEditor)
	ON_NOTIFY(NM_RCLICK, IDC_LIST4, &CQuestEditorView::OnRClickEditor)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CQuestEditorView::OnRClickEditor)

	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_REGISTERED_MESSAGE(WM_XLISTCTRL_COMBO_SELECTION, OnComboSelection)
	ON_REGISTERED_MESSAGE(WM_XLISTCTRL_CHECKBOX_CLICKED, OnCheckbox)
	ON_REGISTERED_MESSAGE(WM_XLISTCTRL_EDIT_END, OnEditEnd)
	ON_BN_CLICKED(IDC_CHECK2, &CQuestEditorView::OnBnClickedCheckReadOnly)
END_MESSAGE_MAP()

// CEditorView construction/destruction

CQuestEditorView::CQuestEditorView()
	: CFormView(CQuestEditorView::IDD)
{
	// TODO: add construction code here
	theEditor = this;

	m_pxQuestFind = NULL;
	m_pxDropMonsterDialog = NULL;
	m_pxDropItemDialog = NULL;
	m_pxQuestStringEdit = NULL;
	m_pxListCtrl = NULL;

	m_nItem = -1;
	m_nSubItem = -1;

	m_nShowFindId = -1;
	m_strQuestFile.clear();
	m_strDropItemFile.Empty();

	m_mapViewQuest.clear();

	m_bRemoveReadOnly = true;
}

CQuestEditorView::~CQuestEditorView()
{

}

void CQuestEditorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listProperty);
	DDX_Control(pDX, IDC_LIST4, m_listReward);
	DDX_Control(pDX, IDC_LIST6, m_listPreRequirement);
	DDX_Control(pDX, IDC_LIST7, m_listPostRequiement);
	DDX_Control(pDX, IDC_TREE1, m_xTreeQuest);
	DDX_Control(pDX, IDC_STATIC_PREREQUIEMENT, m_staticPre);
	DDX_Control(pDX, IDC_STATIC_POST, m_staticPost);
	DDX_Control(pDX, IDC_STATIC_REWARD, m_staticReward);
	DDX_Control(pDX, IDC_STATIC_SAVE, m_staticSave);
	DDX_Control(pDX, IDC_CHECK1, m_checkBatch);
	DDX_Control(pDX, IDC_CHECK2, m_checkReadOnly);
}

BOOL CQuestEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CQuestEditorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	InitInformation();   //初始化
}


// CEditorView diagnostics

#ifdef _DEBUG
void CQuestEditorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CQuestEditorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CQuestEditorDoc* CQuestEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQuestEditorDoc)));
	return (CQuestEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CEditorView message handlers

void CQuestEditorView::SetCurrentWorkDir()
{
	//设置当前工作目录
	char szProcPath[_MAX_PATH] = "";
	char szDirve[_MAX_DRIVE] = "";
	char szDir[_MAX_PATH] = "";

	::GetModuleFileName(NULL, szProcPath, sizeof(szProcPath));

	_tsplitpath(szProcPath, szDirve, szDir, NULL, NULL);

	char szWorkDir[_MAX_PATH] = "";
	sprintf_s(szWorkDir, sizeof(szWorkDir), "%s%s", szDirve, szDir);	

	SetCurrentDirectory(szWorkDir);
}

//显示查找窗口
void CQuestEditorView::ShowFindDialog()
{
	if (m_pxQuestFind == NULL)
	{
		m_pxQuestFind = new QuestFind();
		m_pxQuestFind->Create(IDD_DIALOG_FIND, this);
		m_pxQuestFind->InitInformation();
	}

	if (m_pxQuestFind != NULL)
	{
		m_pxQuestFind->ShowWindow(SW_SHOW);
	}
}

//添加一行
void CQuestEditorView::AddListItem()
{
	HWND hWnd = GetFocus()->m_hWnd;
	if (hWnd == m_listPreRequirement.m_hWnd)
	{
		AddQuestRequiremenetList(m_listPreRequirement, m_xStringArray[Enum_Requirement], false);
	}
	else if (hWnd == m_listPostRequiement.m_hWnd)
	{
		AddQuestRequiremenetList(m_listPostRequiement, m_xStringArray[Enum_Requirement], true);
	}
	else if (hWnd == m_listReward.m_hWnd)
	{
		AddQuestRewardList(m_listReward, m_xStringArray[Enum_Reward]);
	}
}

void CQuestEditorView::DeleteListItem()
{
	HWND hWnd = GetFocus()->m_hWnd;
	if (hWnd == m_listPreRequirement.m_hWnd)
	{
		int nIndex = m_listPreRequirement.GetCurSel();
		if (nIndex != -1)
		{
			m_listPreRequirement.DeleteItem(nIndex);
		}
	}
	else if (hWnd == m_listPostRequiement.m_hWnd)
	{
		int nIndex = m_listPostRequiement.GetCurSel();
		if (nIndex != -1)
		{
			//删除 物品掉落关联
			OnDeletedDrop();
			m_listPostRequiement.DeleteItem(nIndex);

			if (m_pxDropMonsterDialog != NULL)
			{
				m_pxDropMonsterDialog->ShowWindow(SW_HIDE);
			}
		}
	}
	else if(hWnd == m_listReward.m_hWnd)
	{
		int nIndex = m_listReward.GetCurSel();
		if (nIndex != -1)
		{
			m_listReward.DeleteItem(nIndex);
		}
	}	
}

void CQuestEditorView::DeleteQuest()
{
	HWND hWnd = GetFocus()->m_hWnd;
	if (hWnd != m_xTreeQuest.m_hWnd)
	{
		return;
	}

	HTREEITEM hItem = m_xTreeQuest.GetSelectedItem();
	if (hItem != NULL && hItem != m_xTreeQuest.GetRootItem())
	{			
		CString strId = m_xTreeQuest.GetItemText(hItem);
		int nId = atoi(strId.GetBuffer());

		if (DeleteQuestFile(nId))
		{
			//删除掉落物品关联
			SQuest *pQuest = theQuestManager.GetQuest(nId);
			if (pQuest != NULL)
			{
				reqiter iter = pQuest->stCommitRequirement.begin();
				reqiter end = pQuest->stCommitRequirement.end();

				for ( ; iter != end; ++iter)
				{
					if (iter->byType == SQuest::eRequirement_Monster)
					{
						m_xDropTaskItem.SubQuest(iter->Value, nId,iter->Value);
						continue;
					}
				}
			}
			
			theQuestInfo.RemoveQuest(nId);
			m_xTreeQuest.DeleteItem(hItem);
			m_staticSave.SetWindowText("删除成功！");

			SetTimer(SaveShow_Timer_Id, 2500, NULL); //2.5秒后清除显示
		}			
	}
}

bool CQuestEditorView::DeleteQuestFile(int nId)
{
	char szInfo[128] = "";
	sprintf_s(szInfo, sizeof(szInfo) - 1, "你需要删除ID为【%d】任务相关的所有文件吗？", nId);

	if (MessageBox(szInfo, "温馨提示！", MB_YESNO) == IDYES)
	{
		string strQuestFile = GetFileFullPath(m_strQuestFile.c_str(), nId, Client_Path, Quest_File_Ext);
		::remove(strQuestFile.c_str());

		string strStringFile = GetFileFullPath(m_strQuestFile.c_str(), nId, Client_Path, String_Ext);
		::remove(strStringFile.c_str());

		//删除Script文件
		return true;
	}

	return false;			
}

void CQuestEditorView::InitInformation()
{	
	/////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	MessageBox("debug","debug",MB_OK);
#endif

	InitListCtrl(true);	

	ShowQuestTreeList();	//显示任务列表
	//////////////////////////////////////////////////////////////////////////
	LoadResourceFiles();
	//////////////////////////////////////////////////////////////////////////////

	InitSetInfo();
	InitPropertyList();		//列表初始化

	m_checkReadOnly.SetCheck(m_bRemoveReadOnly);
}


void CQuestEditorView::LoadResourceFiles()
{
	//还原当前工作目录
	//SetCurrentWorkDir();

	//读取
	//if (!GettheItemDetail().LoadBinFile(Item_File_Path))
	//{
	//	CString strText = "";
	//	strText.Format("加载 %s 失败!",Item_File_Path);
	//	AfxMessageBox(strText);
	//}
  
    if (!theItemDetailConfig.InitItemDetail())
    {
        CString strText = "";
        strText.Format("加载 %s 失败!",ITEMDETAILDIRECTORY);
        AfxMessageBox(strText);
    }

    if (!theItemDetailConfig.LoadXmlMonster(MONSTERCONFIG_FILEPATH))
    {
        CString strText = "";
        strText.Format("加载 %s 失败!",MONSTERCONFIG_FILEPATH);
        AfxMessageBox(strText);
    }

	//载入NPC信息
	if (theNpcInfo.LoadConfig(Npc_File_Path) != File_Success)
	{
		CString strText = "";
		strText.Format("加载 %s 失败!",Npc_File_Path);
		AfxMessageBox(strText);
	}

	//寻路坐标文件
	if (thePositionInfo.LoadConfig(Position_File_Path) != File_Success)
	{
		CString strText = "";
		strText.Format("加载 %s 失败!",Position_File_Path);
		AfxMessageBox(strText);
	}

    if ( !theQuestInfo.ParseCommondData(COMMONQUEST) )
    {
        CString strText = "";
        strText.Format("加载 %s 失败!",COMMONQUEST);
        AfxMessageBox(strText);
    }
}

void CQuestEditorView::InitListCtrl(bool bInsert)
{
	int nWidth = 0;
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

	//属性	
	if (bInsert)
	{		
		nWidth = SetListCtrlStyle(m_listProperty, dwStyle);
		m_listProperty.InsertColumn(0, "【任务属性】", 0, (15 * nWidth) / 100);
		m_listProperty.InsertColumn(1, "【数值 / ID】", 0, (15 * nWidth) / 100);
		m_listProperty.InsertColumn(2, "【名称】", 0, (65 * nWidth) / 100);

		//接任务要求
		nWidth = SetListCtrlStyle(m_listPreRequirement, dwStyle);
		m_listPreRequirement.InsertColumn(0, "【任务前置要求】", 0, (20 * nWidth) / 100);
		m_listPreRequirement.InsertColumn(1, "【数值 / ID】", 0, (20 * nWidth) / 100);
		m_listPreRequirement.InsertColumn(2, "【名称】", 0, (20 * nWidth) / 100);
		m_listPreRequirement.InsertColumn(3, "【数量】", 0, (20 * nWidth) / 100);

		//交任务要求
		nWidth = SetListCtrlStyle(m_listPostRequiement, dwStyle);	
		m_listPostRequiement.InsertColumn(0, "【任务完成要求】", 0, (20 * nWidth) / 100);
		m_listPostRequiement.InsertColumn(1, "【数值 / ID】", 0, (20 * nWidth) / 100);
		m_listPostRequiement.InsertColumn(2, "【名称】", 0, (20 * nWidth) / 100);
		m_listPostRequiement.InsertColumn(3, "【数量】", 0, (20 * nWidth) / 100);
        m_listPostRequiement.InsertColumn(4, "【对应奖励ID】", 0, (20 * nWidth) / 100);

		//奖励
		nWidth = SetListCtrlStyle(m_listReward, dwStyle);
		m_listReward.InsertColumn(0, "【任务完成奖励】", 0, (15 * nWidth) / 100);
		m_listReward.InsertColumn(1, "【数值 / ID】", 0, (10 * nWidth) / 100);
		m_listReward.InsertColumn(2, "【名称】", 0, (10 * nWidth) / 100);
		m_listReward.InsertColumn(3, "【数量】", 0, (10 * nWidth) / 100);	
		m_listReward.InsertColumn(4, "【职业】", 0, (10 * nWidth) / 100);	
		m_listReward.InsertColumn(5, "【性别】", 0, (10 * nWidth) / 100);
        m_listReward.InsertColumn(6, "【Icon】", 0, (8 * nWidth) / 100);
        m_listReward.InsertColumn(7, _T("【是否随机星级】"), 0, (12 * nWidth) / 100);
        m_listReward.InsertColumn(8, _T("【最大星级】"), 0, (10 * nWidth) / 100);
        m_listReward.InsertColumn(9, _T("【是否绑定】"), 0, (10 * nWidth) / 100);
        m_listReward.InsertColumn(10, _T("【奖励ID】"), 0, (10 * nWidth) / 100);
	}
	else
	{
		nWidth = SetListCtrlStyle(m_listProperty, dwStyle);
		m_listProperty.SetColumnWidth(0, (15 * nWidth) / 100);
		m_listProperty.SetColumnWidth(1, (15 * nWidth) / 100);
		m_listProperty.SetColumnWidth(2, (65 * nWidth) / 100);

		//接任务要求
		nWidth = SetListCtrlStyle(m_listPreRequirement, dwStyle);	
		m_listPreRequirement.SetColumnWidth(0, (20 * nWidth) / 100);
		m_listPreRequirement.SetColumnWidth(1, (20 * nWidth) / 100);
		m_listPreRequirement.SetColumnWidth(2, (20 * nWidth) / 100);
		m_listPreRequirement.SetColumnWidth(3, (20 * nWidth) / 100);

		//交任务要求
		nWidth = SetListCtrlStyle(m_listPostRequiement, dwStyle);	
		m_listPostRequiement.SetColumnWidth(0, (20 * nWidth) / 100);
		m_listPostRequiement.SetColumnWidth(1, (20 * nWidth) / 100);
		m_listPostRequiement.SetColumnWidth(2, (20 * nWidth) / 100);
		m_listPostRequiement.SetColumnWidth(3, (20 * nWidth) / 100);
        m_listPreRequirement.SetColumnWidth(4, (20 * nWidth) / 100);

		//奖励
		nWidth = SetListCtrlStyle(m_listReward, dwStyle);
		m_listReward.SetColumnWidth(0, (15 * nWidth) / 100);
		m_listReward.SetColumnWidth(1, (10 * nWidth) / 100);
		m_listReward.SetColumnWidth(2, (10 * nWidth) / 100);
		m_listReward.SetColumnWidth(3, (10 * nWidth) / 100);	
		m_listReward.SetColumnWidth(4, (10 * nWidth) / 100);	
		m_listReward.SetColumnWidth(5, (10 * nWidth) / 100);
        m_listReward.SetColumnWidth(6, (8 * nWidth) / 100);
        m_listReward.SetColumnWidth(7, (12 * nWidth) / 100);
        m_listReward.SetColumnWidth(8, (10 * nWidth) / 100);
        m_listReward.SetColumnWidth(9, (10 * nWidth) / 100);
        m_listReward.SetColumnWidth(10,(10 * nWidth) / 100);
	}
}

void CQuestEditorView::InitSetInfo()
{
	for (int i = 0; i < Enum_End; ++i)
	{
		m_xStringArray[i].Add(Default_Select);
	}

	//地图
	if ( theMapConfig.LoadMapConfig(Map_File_Path) )
	{
		int nCount = theMapConfig.MapDataCount();

		for (int i = 0; i < nCount; ++i)
		{
            char szTmp[30] = {0};
			MapConfig::MapData* pMapData  = theMapConfig.GetMapDataByIndex(i);
			SetInfo xSetInfo;
			xSetInfo.nValue = i;		
			if (pMapData != NULL)
			{
                sprintf_s(szTmp, sizeof(szTmp) - 1, "(MapID=%d)", pMapData->Id);
				xSetInfo.strName = pMapData->MapName;
                xSetInfo.strName += szTmp;
			}
			else
			{
				xSetInfo.strName = "未知地图信息";
			}

			m_xStringArray[Enum_Map].Add(xSetInfo.strName.c_str());
			m_xSetInfo[Enum_Map].push_back(xSetInfo);		
		}
	}
    else
    {
        CString strError = "";
        strError.Format("加载 %s 失败!", Map_File_Path);
        AfxMessageBox(strError);
    }


	//称号
	//if (GettheItemDetail().LoadReputeList(Repute_File_Path) == TRUE)
	if (theTitleConfig.LoadTitleConfig(Repute_File_Path))
	{
		int nCount = theTitleConfig.GetTitleCount();
		for (int i = 0; i < nCount; ++i)
		{

			TitleConfig::Title* pTitle = theTitleConfig.GetTitleByIndex(i);
			if (pTitle != NULL)
			{	
				SetInfo xSetInfo;
				xSetInfo.nValue = pTitle->nID;
				xSetInfo.strName = pTitle->strName;

				m_xStringArray[Enum_Title].Add(pTitle->strName.c_str());
				m_xSetInfo[Enum_Title].push_back(xSetInfo);
			}		
		}
	}

	//任务品质
	for (int i = 0; i < SQuest::eQuestRank_Max; ++i)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszQuality[i];

		m_xStringArray[Enum_Quality].Add(s_pszQuality[i]);
		m_xSetInfo[Enum_Quality].push_back(xSetInfo);
	}


	//要求
	for (int i = 0; i < SQuest::eRequirement_Max; ++i)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszRequement[i];

		m_xStringArray[Enum_Requirement].Add(s_pszRequement[i]);
		m_xSetInfo[Enum_Requirement].push_back(xSetInfo);
	}

	//奖励
	for (int i = 0; i < SQuest::eReward_Max; ++i)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszReward[i];

		m_xStringArray[Enum_Reward].Add(s_pszReward[i]);
		m_xSetInfo[Enum_Reward].push_back(xSetInfo);
	}

	//性别
	for (int i = 0; i < Sex_Max; ++i)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszSex[i];

		m_xStringArray[Enum_Sex].Add(s_pszSex[i]);
		m_xSetInfo[Enum_Sex].push_back(xSetInfo);
	}

	//职业
	for (int i = 0; i < EArmType_MaxSize; ++i)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszProfession[i];

		m_xStringArray[Enum_Profession].Add(s_pszProfession[i]);
		m_xSetInfo[Enum_Profession].push_back(xSetInfo);
	}


	//交任务目标
    NpcInfo::NpcsIter iterBegin = theNpcInfo.npcs_.begin();
    NpcInfo::NpcsIter iterEnd   = theNpcInfo.npcs_.end();
	for( ; iterBegin != iterEnd; ++iterBegin)
	{
        char szTmp[65] = {0}; // 用来显示 Npc名称(Npc地图名 ID=XXX)
		SetInfo xSetInfo;
		xSetInfo.nValue = iterBegin->second.id;
		string strName = "";

        strName = iterBegin->second.name;
        MapConfig::MapData *pMap = theMapConfig.GetMapDataById(iterBegin->second.mapId);
        if (pMap == NULL)
        { continue;}

        sprintf_s(szTmp, sizeof(szTmp) - 1, "(%sID=%d)", pMap->MapName.c_str(), pMap->Id);
        strName += szTmp;    

		xSetInfo.strName = strName;		
		m_xStringArray[Enum_Position].Add(xSetInfo.strName.c_str());
		m_xSetInfo[Enum_Position].push_back(xSetInfo);
	}

	//物品
	int nItemCount = GettheItemDetail().GetItemCount();
	for(int i = 0; i < nItemCount; ++i)
	{
		CItemDetail::SItemCommon *pItem = GettheItemDetail().GetItemByID(GettheItemDetail().GetItemID(i));
		if (pItem != NULL)
		{			
			SetInfo xSetInfo;
			xSetInfo.nValue = pItem->ustItemID;
			xSetInfo.strName = pItem->GetItemName();

			m_xStringArray[Enum_Item].Add(pItem->GetItemName());
			m_xSetInfo[Enum_Item].push_back(xSetInfo);
		}
	}

	//怪物
	int nMonsterCount  = GettheItemDetail().GetMonsterNumber();
	for(int i = 0; i < nMonsterCount; ++i)
	{
		CItemDetail::SMonster *pMonster = GettheItemDetail().GetMonster(i);
		if (pMonster != NULL)
		{			
			SetInfo xSetInfo;
			xSetInfo.nValue = pMonster->stMonsterId;
			xSetInfo.strName = pMonster->GetName();

			m_xStringArray[Enum_Monster].Add(pMonster->GetName());
			m_xSetInfo[Enum_Monster].push_back(xSetInfo);
		}
	}
	//任务类型
    static const int QuestTypeCount = theQuestInfo._QuestType.size();
    for (int i=0; i<QuestTypeCount; ++i)
    {
        QuestInfo::SQuestType* pQuestType = theQuestInfo._QuestType[i];
        SetInfo xSetInfo;
        xSetInfo.nValue = i;
        xSetInfo.strName = pQuestType->QuestTypeDesc.c_str();

        m_xStringArray[Enum_QuestInfoType].Add(pQuestType->QuestTypeDesc.c_str());
        m_xSetInfo[Enum_QuestInfoType].push_back(xSetInfo);
    }
    //是否随机星级
    for (int i=0; i<2; ++i) // 只有“是/否”两种
    {
        SetInfo xSetInfo;
        xSetInfo.nValue = i;
        xSetInfo.strName = s_pszIsRandStar[i];

        m_xStringArray[Enum_IsRandStar].Add(s_pszIsRandStar[i]);
        m_xSetInfo[Enum_IsRandStar].push_back(xSetInfo);
    }
    // 是否绑定
    for (int i=0; i<2; ++i)
    {
        SetInfo xSetInfo;
        xSetInfo.nValue = i;
        xSetInfo.strName = s_pszIsBound[i];

        m_xStringArray[Enum_IsBound].Add(s_pszIsBound[i]);
        m_xSetInfo[Enum_IsBound].push_back(xSetInfo);
    }
}

void CQuestEditorView::InitPropertyList()
{	
	m_listProperty.DeleteAllItems();	
	///////////////////////////////////////////////////////////////////////////
	//////任务属性
	int nItem = 0;
	const int nSubItem = 1;

	m_listProperty.InsertItem(nItem, "任务ID");	
	m_listProperty.SetEdit(nItem, nSubItem);
	m_listProperty.SetComboBox(nItem++, nSubItem + 1, TRUE, &m_xStringArray[Enum_QuestInfoType], m_xStringArray[Enum_QuestInfoType].GetCount(), 0);

	m_listProperty.InsertItem(nItem, "任务名称");	
	m_listProperty.SetEdit(nItem++, nSubItem + 1);

	m_listProperty.InsertItem(nItem, "任务品质");	
	m_listProperty.SetItemText(nItem, nSubItem, "0");
	m_listProperty.SetComboBox(nItem++, nSubItem + 1, TRUE, &m_xStringArray[Enum_Quality], m_xStringArray[Enum_Quality].GetSize(), 1);

	m_listProperty.InsertItem(nItem, "任务内容描述");
	m_listProperty.SetEdit(nItem++, nSubItem + 1);

	m_listProperty.InsertItem(nItem, "任务目标描述");
	m_listProperty.SetEdit(nItem++, nSubItem + 1);

    //接任务目标
    m_listProperty.InsertItem(nItem, "接任务目标");
    SetListItemBGroundColor(m_listProperty, nItem, 1, Red_Ground_Color);
    m_listProperty.SetComboBox(nItem++, nSubItem + 1, TRUE, &m_xStringArray[Enum_Position], m_xStringArray[Enum_Position].GetSize(), 0);

	m_listProperty.InsertItem(nItem, "交任务地图");
	m_listProperty.SetComboBox(nItem++, nSubItem + 1, TRUE, &m_xStringArray[Enum_Map], m_xStringArray[Enum_Map].GetSize(), 0);

	//交任务类型
	m_listProperty.InsertItem(nItem, "交任务目标");
	SetListItemBGroundColor(m_listProperty, nItem, 1, Red_Ground_Color);
	m_listProperty.SetComboBox(nItem++, nSubItem + 1, TRUE, &m_xStringArray[Enum_Position], m_xStringArray[Enum_Position].GetSize(), 0);

	m_listProperty.InsertItem(nItem, "提示等级(xx-yy)");
	m_listProperty.SetEdit(nItem++, nSubItem);

	m_listProperty.InsertItem(nItem, "能否协助执行");	
	m_listProperty.SetCheckbox(nItem, nSubItem, 0);
	m_listProperty.SetItemText(nItem++, nSubItem, "协助执行");

	m_listProperty.InsertItem(nItem, "能否任务共享");	
	m_listProperty.SetCheckbox(nItem, nSubItem, 0);
	m_listProperty.SetItemText(nItem++, nSubItem, "任务共享");

	m_listProperty.InsertItem(nItem, "能否重复执行");	
	m_listProperty.SetCheckbox(nItem, nSubItem, 0);
	m_listProperty.SetItemText(nItem++, nSubItem, "重复任务");

	m_listProperty.InsertItem(nItem, "能否删除任务");	
	m_listProperty.SetCheckbox(nItem, nSubItem, 0);
	m_listProperty.SetItemText(nItem++, nSubItem, "任务删除");

    m_listProperty.InsertItem(nItem, "客户端是否显示");	
    m_listProperty.SetCheckbox(nItem, nSubItem, 0);
    m_listProperty.SetItemText(nItem++, nSubItem, "任务显示");

	m_listProperty.InsertItem(nItem, "在可接任务中显示");	
	m_listProperty.SetCheckbox(nItem, nSubItem, 0);
	m_listProperty.SetItemText(nItem++, nSubItem, "是");

    m_listProperty.InsertItem(nItem, "是否单一条件完成");
    m_listProperty.SetCheckbox(nItem, nSubItem, 0);
    m_listProperty.SetItemText(nItem++, nSubItem, "单一条件");

	//任务所属国家
	m_listProperty.InsertItem(nItem, "任务所属国家");
	m_listProperty.SetEdit(nItem++, nSubItem);

	m_listPreRequirement.DeleteAllItems();
	m_listPostRequiement.DeleteAllItems();
	m_listReward.DeleteAllItems();
}

void CQuestEditorView::ShowQuestTreeList()
{
	m_xTreeQuest.DeleteAllItems();

	HTREEITEM hRoot = m_xTreeQuest.InsertItem(Quest_Root);

	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	for( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			AddQuestInTree(hRoot, *(*iter).second);
		}		
	}

	m_xTreeQuest.ExpandAllTreeNodes(NULL, TRUE);
}

void CQuestEditorView::AddQuestInTree(HTREEITEM hParent, SQuest &xQuest, HTREEITEM hInsertAfter)
{
	CString strId = "";
	strId.Format("%d", xQuest.Id);
	HTREEITEM hItem = m_xTreeQuest.InsertItem(strId, hParent, hInsertAfter);

	//设置背景颜色...
	SetQuestViewColor(&xQuest);
}

void CQuestEditorView::ShowQuestInformation(HTREEITEM hItem)
{
	if (hItem != NULL)
	{
		CString strId = m_xTreeQuest.GetItemText(hItem);
		int nId = atoi(strId.GetBuffer());

		int nListId = GetListItemInt(m_listProperty, 0, 1, -1);
		if (nListId != nId)
		{
			SQuest *pQuest = theQuestManager.GetQuest(nId);

			if (pQuest != NULL)
			{
				ShowQuestInformation(*pQuest);
			}
		}
	}
}

//显示任务信息
void CQuestEditorView::ShowQuestInformation(SQuest &xQuest)
{
	int nIndex = 0;
	const int nSubItem = 1;

	curr_show_quest_id = xQuest.Id;
	//ID
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.Id);	//ID

    // 类型
    m_listProperty.SetItemText(nIndex++, nSubItem + 1, GetSetInfoName(m_xSetInfo[Enum_QuestInfoType], xQuest.chQuestType));

    //名字
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.QuestName);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, theXmlString.GetString(xQuest.QuestName));

	//任务品质
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.RankId);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, GetSetInfoName(m_xSetInfo[Enum_Quality], xQuest.RankId));

	//描述
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.IntroStringId);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, theXmlString.GetString(xQuest.IntroStringId));			

	//目标
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.TargetStringId);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, theXmlString.GetString(xQuest.TargetStringId));	

    //查找到寻路坐标名字,然后显示之
    if (xQuest.AcceptTargetId == -1)    //接任务
    {
        SetListItemBGroundColor(m_listProperty, nIndex, 1, Red_Ground_Color);
        m_listProperty.SetItemText(nIndex, 1, "");

    }
    else
    {
        SetListItemBGroundColor(m_listProperty, nIndex, 1, Default_Grund_Color);
        SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.AcceptTargetId);
    }
    CString strAcceptNpc = GetSetInfoName(m_xSetInfo[Enum_Position], xQuest.AcceptTargetId, Default_Select);
    m_listProperty.SetItemText(nIndex++, nSubItem + 1, strAcceptNpc);

	//地图
	if (xQuest.MapId != -1)
	{
		SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.MapId);
	}
	else
	{
		m_listProperty.SetItemText(nIndex, nSubItem, "");
	}
		
	CString strMap = GetSetInfoName(m_xSetInfo[Enum_Map], xQuest.MapId, Default_Select);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, strMap);	

	//查找到寻路坐标名字,然后显示之
	if (xQuest.ReplyTargetId == -1)
	{
		SetListItemBGroundColor(m_listProperty, nIndex, 1, Red_Ground_Color);
		m_listProperty.SetItemText(nIndex, 1, "");

	}
	else
	{
		SetListItemBGroundColor(m_listProperty, nIndex, 1, Default_Grund_Color);
		SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.ReplyTargetId);
	}
	CString strNpc = GetSetInfoName(m_xSetInfo[Enum_Position], xQuest.ReplyTargetId, Default_Select);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, strNpc);

	//提示等级
	CString strLevel = "";
	strLevel.Format("%d%s%d", xQuest.HintLevelMin, SUB_STRING3, xQuest.HintLevelMax);
	m_listProperty.SetItemText(nIndex++, nSubItem, strLevel);

	m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.CanAssist);			//协助
	m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.CanShare);			//共享
	m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.IsRepeat);			//重复
	m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.IsCancel);			//删除
    m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.CanDisplay);          //显示
	m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.bDisplayInCanAccept); //是否在可接任务中显示
    m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.IsSingleRequirement); //单一条件

	CString	strCountry = "";
	strCountry.Format("%d", xQuest.Country);
	m_listProperty.SetItemText(nIndex++, nSubItem, strCountry); 			//所属国家

	//接任务要求
	ShowRequirementList(m_listPreRequirement, xQuest.stReceiveRequirement, false);
	//交任务要求
	ShowRequirementList(m_listPostRequiement, xQuest.stCommitRequirement, true);

	//任务奖励
	ShowRewardList(xQuest.stReward);
}

void CQuestEditorView::ClearQuestInformation()
{
	int nItem = 0;
    m_listProperty.SetItemText(nItem++, 2, Default_Select);

	//名称
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, "");

	//品质
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, Default_Select);

	//内容
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, "");

	//目标
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, "");

    SetListItemBGroundColor(m_listProperty, nItem, 1, Red_Ground_Color);
    m_listProperty.SetItemText(nItem, 1, "");
    m_listProperty.SetItemText(nItem++, 2, Default_Select);

	//地图
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, Default_Select);

	//Npc
	SetListItemBGroundColor(m_listProperty, nItem, 1, Red_Ground_Color);
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, Default_Select);

	//等级
	m_listProperty.SetItemText(nItem++, 1, "");

	m_listProperty.SetCheckbox(nItem++, 1, 0);
	m_listProperty.SetCheckbox(nItem++, 1, 0);
	m_listProperty.SetCheckbox(nItem++, 1, 0);
	m_listProperty.SetCheckbox(nItem++, 1, 0);
    m_listProperty.SetCheckbox(nItem++, 1, 0);

	m_listPreRequirement.DeleteAllItems();
	m_listPostRequiement.DeleteAllItems();
	m_listReward.DeleteAllItems();
}

//显示任务要求
void CQuestEditorView::ShowRequirementList(CXListCtrl &xRequirementList, vector<SQuestRequirement> &vecRequirement, bool bCommit)
{
	reqiter iter = vecRequirement.begin();
	reqiter end = vecRequirement.end();

	int nCount = xRequirementList.GetItemCount();
	int nIndex = 0;

	int nProfessionIndex = 0;

	for ( ; iter != end; )
	{
		if (nIndex >= nCount)
		{
			AddQuestRequiremenetList(xRequirementList,  m_xStringArray[Enum_Requirement], bCommit);
			++nCount;
		}		

		for (int i = 0; i < xRequirementList.GetColumns(); ++i)
		{
			SetListItemBGroundColor(xRequirementList, nIndex, i, Default_Grund_Color);
		}

		//id 转换成字符串,然后显示之
		xRequirementList.SetItemText(nIndex, 0, GetSetInfoName(m_xSetInfo[Enum_Requirement], (*iter).byType));

		if ((*iter).byType != -1)
		{
			CString strName = "";
			if ((*iter).byType == SQuest::eRequirement_Sex)
			{
				xRequirementList.SetComboBox(nIndex, 2, TRUE, &m_xStringArray[Enum_Sex], m_xStringArray[Enum_Sex].GetCount(), 0);

				strName = GetSetInfoName(m_xSetInfo[Enum_Sex], (*iter).Value);
				if (strName.IsEmpty())
				{
					strName = Default_Select;
				}
			}
			else if ((*iter).byType == SQuest::eRequirement_Quest)
			{
				SQuest *pQuest = theQuestManager.GetQuest((*iter).Value);
				if (pQuest != NULL)
				{
					strName = theXmlString.GetString(pQuest->QuestName);
				}
			}
			
			xRequirementList.SetItemText(nIndex, 2, strName);
			SetListItemText(xRequirementList, nIndex, 3, "%d", (*iter).MaxNum);

			if ((*iter).byType == SQuest::eRequirement_Profession)	//要分析职业限制
			{			
				for ( ; nProfessionIndex < EArmType_MaxSize; ++nProfessionIndex)
				{
					int nValue = 1 << nProfessionIndex;

					if (((*iter).Value & nValue ) != 0)
					{
						SetListItemText(xRequirementList, nIndex, 1, "%d", nProfessionIndex);	
						xRequirementList.SetComboBox(nIndex, 2, TRUE, &m_xStringArray[Enum_Profession], m_xStringArray[Enum_Profession].GetCount(), 0);

						strName = GetSetInfoName(m_xSetInfo[Enum_Profession], nProfessionIndex);
						if (strName.IsEmpty())
						{
							strName = Default_Select;
						}
						xRequirementList.SetItemText(nIndex, 2, strName);
						++nProfessionIndex;
						++nIndex;

						break;
					}
				}						

				if (nProfessionIndex == EArmType_MaxSize)
				{							
					++iter;
				}
				continue;
			}
			else
			{
				if ((*iter).byType == SQuest::eRequirement_Monster)
				{
					for (int i = 0; i < xRequirementList.GetColumns(); ++i)
					{
						SetListItemBGroundColor(xRequirementList, nIndex, i, Green_Ground_Color);
					}

					xRequirementList.SetItemText(nIndex, 0, GetSetInfoName(m_xSetInfo[Enum_Requirement], (*iter).byType));
					xRequirementList.Resume(nIndex, 1);
					xRequirementList.SetComboBox(nIndex, 2, TRUE, &m_xStringArray[Enum_Monster], m_xStringArray[Enum_Monster].GetCount(), 0);
					//查找并显示
					DropTaskItem::STask xTask;
					int nMonsterId = m_xDropTaskItem.FindDropItemByVarId((*iter).wVar, xTask);
					if (nMonsterId != -1)
					{						
						SetListItemBGroundColor(xRequirementList, nIndex, 1, Green_Ground_Color);
						SetListItemText(xRequirementList, nIndex, 1, "%d", nMonsterId);

						CItemDetail::SMonster *pMonster = GettheItemDetail().GetMonsterById(nMonsterId);
						if (pMonster != NULL)
						{
							SetListItemBGroundColor(xRequirementList, nIndex, 2, Green_Ground_Color);
							xRequirementList.SetItemText(nIndex, 2, pMonster->GetName());
						}

						SetListItemText(xRequirementList, nIndex, 3, "%d", xTask.nMaxVar);
					}
					else
					{
						xRequirementList.SetItemText(nIndex, 1, "");
						xRequirementList.SetItemText(nIndex, 2, "");
						xRequirementList.SetItemText(nIndex, 3, Default_Select);
					}					
				}
				else if ((*iter).byType == SQuest::eRequirement_Item)
				{
					for (int i = 0; i < xRequirementList.GetColumns(); ++i)
					{
						SetListItemBGroundColor(xRequirementList, nIndex, i, Blue_Ground_Color);
					}
				
					xRequirementList.SetItemText(nIndex, 0, GetSetInfoName(m_xSetInfo[Enum_Requirement], (*iter).byType));
					xRequirementList.Resume(nIndex, 1);
					xRequirementList.SetComboBox(nIndex, 2, TRUE, &m_xStringArray[Enum_Item], m_xStringArray[Enum_Item].GetCount(), 0);
					//查找并显示					
					SetListItemBGroundColor(xRequirementList, nIndex, 1, Blue_Ground_Color);
					SetListItemText(xRequirementList, nIndex, 1, "%d", iter->Value);

					SetListItemBGroundColor(xRequirementList, nIndex, 2, Blue_Ground_Color);
					CItemDetail::SItemCommon *pItem = GettheItemDetail().GetItemByID(iter->Value);
					if (pItem != NULL)
					{
						xRequirementList.SetItemText(nIndex, 2, pItem->GetItemName());
					}
					else
					{
						xRequirementList.SetItemText(nIndex, 2, Default_Select);
					}

					SetListItemText(xRequirementList, nIndex, 3, "%d", iter->MaxNum);														
				}
				else
				{
					SetListItemText(xRequirementList, nIndex, 1, "%d", (*iter).Value);
				}						
			}

            if (bCommit)
            { SetListItemText(xRequirementList, nIndex, 4, "%d", (*iter).nRewardID); }
		}
		++nIndex;
		++iter;
	}

	//多余的就删除掉
	for (int i = nCount - 1; i >= nIndex; --i)
	{
		xRequirementList.DeleteItem(i);
	}
}

//显示任务奖励
void CQuestEditorView::ShowRewardList(vector<SQuestReward> &vecReward)
{
	rewarditer iter = vecReward.begin();
	rewarditer end = vecReward.end();

	int nCount = m_listReward.GetItemCount();
	int nIndex = 0;
	for ( ; iter != end; ++iter)
	{
		if (nIndex >= nCount)
		{
			AddQuestRewardList(m_listReward, m_xStringArray[Enum_Reward]);
			++nCount;
		}

		if ((*iter).byType != -1)
		{
			m_listReward.SetItemText(nIndex, 0, GetSetInfoName(m_xSetInfo[Enum_Reward], (*iter).byType));

			if ((*iter).Value  != -1)
			{
				SetListItemText(m_listReward, nIndex, 1, "%d", (*iter).Value);
			}

			m_listReward.Resume(nIndex, 2);         // 名称
			m_listReward.Resume(nIndex, 4);         // 职业
			m_listReward.SetItemText(nIndex, 4, "");
			m_listReward.Resume(nIndex, 5);         // 性别
			m_listReward.SetItemText(nIndex, 5, "");
            m_listReward.Resume(nIndex, 7);         // 是否随机属性
            m_listReward.SetItemText(nIndex, 7, "");
			
			//判断类型来显示
			CString strName = "";
            if ((*iter).byType == SQuest::eReward_Item || iter->byType == SQuest::eReward_SpecialItem )
			{
				CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID((*iter).Value);
				if (pItem != NULL)
				{
					strName = pItem->GetItemName();
				}

				m_listReward.Resume(nIndex, 1);
				m_listReward.SetComboBox(nIndex, 4, TRUE, &m_xStringArray[Enum_Profession], m_xStringArray[Enum_Profession].GetCount(), 0);
				m_listReward.SetComboBox(nIndex, 5, TRUE, &m_xStringArray[Enum_Sex], m_xStringArray[Enum_Sex].GetCount(), 0);
                m_listReward.SetComboBox(nIndex, 7, TRUE, &m_xStringArray[Enum_IsRandStar], m_xStringArray[Enum_IsRandStar].GetCount(), 0);
                m_listReward.SetComboBox(nIndex, 9, TRUE, &m_xStringArray[Enum_IsBound], m_xStringArray[Enum_IsBound].GetCount(), 0);

                //先结算偏移
                string strProfession = "";
                if ( iter->shProfession != -1 )
                {
                    int shProfession = log((float)(*iter).shProfession)/log((float)2);
                    strProfession = GetSetInfoName(m_xSetInfo[Enum_Profession], shProfession);
                }
                if (strProfession.empty())
				{
					strProfession = Default_Select;
				}

				m_listReward.SetItemText(nIndex, 4, strProfession.c_str());

				string strSex = GetSetInfoName(m_xSetInfo[Enum_Sex], (*iter).shSex);
				if (strSex.empty())
				{
					strSex = Default_Select;
				}
				m_listReward.SetItemText(nIndex, 5, strSex.c_str());
                
                string strRandStar = GetSetInfoName(m_xSetInfo[Enum_IsRandStar], iter->bIsStarRandom);
                if (strRandStar.empty())
                {
                    strRandStar = "";
                }
                m_listReward.SetItemText(nIndex, 7, strRandStar.c_str());

                SetListItemText(m_listReward, nIndex, 8, "%d", iter->nStarLevel);

                //string strBound = GetSetInfoName(m_xSetInfo[Enum_IsBound], iter->bIsBound);
                //if (strBound.empty())
                //{
                //    strBound = "";
                //}
                //m_listReward.SetItemText(nIndex, 9, strBound.c_str());
                if ( iter->bIsBound)
                {
                    m_listReward.SetItemText(nIndex, 9, "是");
                }
                else
                {
                    m_listReward.SetItemText(nIndex, 9, "否");
                }
			}
			else if ((*iter).byType == SQuest::eReward_Title)
			{
				m_listReward.SetComboBox(nIndex, 2, TRUE, &m_xStringArray[Enum_Title], m_xStringArray[Enum_Title].GetCount(), 0);

				strName = GetSetInfoName(m_xSetInfo[Enum_Title], (*iter).Value);
				if (strName.IsEmpty())
				{
					strName = Default_Select;
				}
			}
			else if ((*iter).byType == SQuest::eReward_Buff)
			{
				m_listReward.SetComboBox(nIndex, 2, TRUE, &m_xStringArray[Enum_Buff], m_xStringArray[Enum_Buff].GetCount(), 0);

				strName = GetSetInfoName(m_xSetInfo[Enum_Buff], (*iter).Value);
				if (strName.IsEmpty())
				{
					strName = Default_Select;
				}
			}

			m_listReward.SetItemText(nIndex, 2, strName);
			SetListItemText(m_listReward, nIndex, 3, "%d", (*iter).Number);		
            SetListItemText(m_listReward,nIndex,6,"%d",iter->Icon);
            SetListItemText(m_listReward,nIndex,10,"%d",iter->RewardID);
			++nIndex;
		}
	}

	//多余的就删除掉
	for (int i = nCount - 1; i >= nIndex; --i)
	{
		m_listReward.DeleteItem(i);
	}
}

///////////////////////////////////////////////////////////////////////////////////

int CQuestEditorView::AddInQuestList()
{
	int nIndex = 0;
	const int nSubItem = 1;

	//任务ID
	int nId = GetListItemInt(m_listProperty, nIndex, nSubItem, -1);
	if (nId == -1)
	{
		//任务ID 不能为空
		return nId;
	}

    //类型
    CString strType = m_listProperty.GetItemText(nIndex++, nSubItem + 1);
    int nType = GetSetInfoValue(m_xSetInfo[Enum_QuestInfoType], strType.GetBuffer());
    if(nType < SQuest::Type_Main)
    {
        nType = SQuest::Type_Main;
    }

	//名字
	int nNameId = GetListItemInt(m_listProperty, nIndex++, nSubItem, Empty_String_Id);
	if (nNameId < Empty_String_Id)
	{
		nNameId = Empty_String_Id;
	}

	//品质
	int nQuestQuality = GetListItemInt(m_listProperty, nIndex++, nSubItem, -1);

	//描述
	int nIntroId = GetListItemInt(m_listProperty, nIndex++, nSubItem, Empty_String_Id);
	if (nIntroId < Empty_String_Id)
	{
		nIntroId = Empty_String_Id;
	}

	//寻找目标
	int nTargetId = GetListItemInt(m_listProperty, nIndex++, nSubItem, Empty_String_Id);
	if (nTargetId < Empty_String_Id)
	{
		nTargetId = Empty_String_Id;
	}

    int nAcceptNpcId = GetListItemInt(m_listProperty, nIndex++, nSubItem, -1);

	//地图
	int nMapId = GetListItemInt(m_listProperty, nIndex++, nSubItem, -1);

	//NPC
	int nNpcId = GetListItemInt(m_listProperty, nIndex++, nSubItem, -1);

	//任务提示等级
	string strLevel = m_listProperty.GetItemText(nIndex++, nSubItem).GetBuffer();	
	string strValue = "";
	SubString(strLevel, strValue, SUB_STRING3);
	int nPlayerLevelMin = atoi(strValue.c_str());
	SubString(strLevel, strValue, SUB_STRING3);
	int nPlayerLevelMax = atoi(strValue.c_str());
	//最大限制
	nPlayerLevelMax = (nPlayerLevelMax == 0 ? Max_Level : nPlayerLevelMax);

	bool CanAssist = m_listProperty.GetCheckbox(nIndex++, nSubItem);	//能否辅助
	bool CanShare = m_listProperty.GetCheckbox(nIndex++, nSubItem);		//能否共享
	bool IsRepeat = m_listProperty.GetCheckbox(nIndex++, nSubItem);		//能否重复
	bool IsCancel = m_listProperty.GetCheckbox(nIndex++, nSubItem);		//能否删除
    bool CanDisplay = m_listProperty.GetCheckbox(nIndex++, nSubItem);		//能否删除
	bool DisplayInCanAccept = m_listProperty.GetCheckbox(nIndex++, nSubItem);		//能否显示
    bool SingleRequirement = m_listProperty.GetCheckbox(nIndex++, nSubItem); // 能否单一条件完成

	string strCountry = m_listProperty.GetItemText(nIndex++, nSubItem).GetBuffer();
	BYTE Country = atoi(strCountry.c_str());  //国家
	//这里直接保存到文件里面去
	string strQuestFile = GetFileFullPath(m_strQuestFile.c_str(), nId, Client_Path, Quest_File_Ext);

	//判断添加的任务是否已经存在, 存在则修改,否则加入之
	SQuest *pQuest = theQuestManager.GetQuest(nId);
	if (pQuest != NULL)
	{
		pQuest->Id = nId;
        pQuest->chQuestType = nType;
		pQuest->QuestName = nNameId;
		pQuest->RankId = nQuestQuality;
		pQuest->IntroStringId = nIntroId;
		pQuest->TargetStringId = nTargetId;
		pQuest->MapId = nMapId;
        pQuest->AcceptTargetId = nAcceptNpcId;
		pQuest->ReplyTargetId = nNpcId;
		pQuest->HintLevelMin = nPlayerLevelMin;
		pQuest->HintLevelMax = nPlayerLevelMax;
		pQuest->CanAssist = CanAssist;
		pQuest->CanShare = CanShare;
		pQuest->IsRepeat = IsRepeat;
		pQuest->IsCancel = IsCancel;
        pQuest->CanDisplay = CanDisplay;
		pQuest->bDisplayInCanAccept = DisplayInCanAccept;
        pQuest->IsSingleRequirement = SingleRequirement;
		pQuest->Country = Country;
		//接任务要求
		GetQuestRequirement(m_listPreRequirement, *pQuest, false);

		//交任务要求
		GetQuestRequirement(m_listPostRequiement, *pQuest, true);	

		//任务奖励
		GetQuestReward(m_listReward, *pQuest);

		bool nResult = SaveQuestAndStringInFile(strQuestFile.c_str(), *pQuest); //保存文件
        if (!nResult)
        {
            return -1; //存储失败
        }

		SetQuestViewColor(pQuest);
	}
	else
	{
		SQuest xQuest;

		xQuest.Id = nId;
        xQuest.chQuestType = nType;
		xQuest.QuestName = nNameId;
		xQuest.RankId = nQuestQuality;
		xQuest.IntroStringId = nIntroId;
		xQuest.TargetStringId = nTargetId;
        xQuest.AcceptTargetId = nAcceptNpcId;
		xQuest.MapId = nMapId;
		xQuest.ReplyTargetId = nNpcId;

		xQuest.HintLevelMin = nPlayerLevelMin;
		xQuest.HintLevelMax = nPlayerLevelMax;
		xQuest.CanAssist = CanAssist;
		xQuest.CanShare = CanShare;
		xQuest.IsRepeat = IsRepeat;
		xQuest.IsCancel = IsCancel;
        xQuest.CanDisplay = CanDisplay;
		xQuest.bDisplayInCanAccept = DisplayInCanAccept;
		xQuest.Country = Country;
		//接任务要求
		GetQuestRequirement(m_listPreRequirement, xQuest, false);

		//交任务要求
		GetQuestRequirement(m_listPostRequiement, xQuest, true);	

		//任务奖励
		GetQuestReward(m_listReward, xQuest);

		bool nResult = SaveQuestAndStringInFile(strQuestFile.c_str(), xQuest); //保存到文件中
        if (!nResult)
        {
            return -1;
        }
		//添加到列表中 
		if (theQuestInfo.AddQuest(&xQuest))
		{			
			HTREEITEM hRoot = m_xTreeQuest.GetRootItem();
			if (hRoot != NULL)
			{
				AddQuestInTree(hRoot, xQuest, TVI_SORT);	

				m_xTreeQuest.ExpandAllTreeNodes(hRoot, TRUE);
			}
		}
	}	

	return nId;
}

void CQuestEditorView::GetQuestStringId(int nQuest, std::vector<int>& vecStringId)
{
	vecStringId.clear();

	if (nQuest < 0)
	{
		return;
	}

	CString strId = "";

	strId.Format("%d%02d", nQuest, 1);
	int nId = atoi(strId.GetBuffer());
	for (int i = 0; i < StringId_Count; ++i)
	{
		vecStringId.push_back(nId + i);
	}
}

bool CQuestEditorView::SaveQuestAndStringInFile(const char* pszFile, SQuest &xQuest)
{
	RemoveFileReadOnly(pszFile);
    // Begin Add For 奖励物品选项不能超过两个 [11/26/2010 pengbo.yang]
    SQuest::RewardType::iterator iterBegin = xQuest.stReward.begin();
    SQuest::RewardType::iterator iterEnd   = xQuest.stReward.end();
    int nRewardItemCount = 0;
    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (iterBegin->byType == SQuest::eReward_Item)
        {
            ++nRewardItemCount;
        }
    }
	//暂时不限数量
    //if (nRewardItemCount > 2)
    //{
    //    MessageBox(_T("Error:任务奖励中奖励物品选项不能超过两个！"), "Error", MB_ICONERROR|MB_OK);
    //    return false;
    //}
    // End [11/26/2010 pengbo.yang]
	if (theQuestInfo.SaveQuestFile(pszFile, &xQuest))  //保存到文件中
	{
		//保存语言文件
		vector<int> vecStringId;
		GetQuestStringId(xQuest.Id, vecStringId);

		string strStringFile = GetFileFullPath(m_strQuestFile.c_str(), xQuest.Id, Client_Path, String_Ext);
		RemoveFileReadOnly(strStringFile.c_str());
		theXmlString.SaveStringFile(strStringFile.c_str(), vecStringId, false);

		//保存Scrpit 文件
		/////////////////////

		m_staticSave.SetWindowText("保存成功！");
		SetTimer(SaveShow_Timer_Id, 2500, NULL);

		return true;
	}
	else
	{
		AfxMessageBox("保存失败！");
	}

	return false;
}

void CQuestEditorView::AddQuestRequiremenetList(CXListCtrl &xRequirementList, CStringArray &xStringArray, bool bCommit)
{
	int nSubItem = 0;
	int nCount = xRequirementList.GetItemCount();

	xRequirementList.InsertItem(nCount, "");	
	xRequirementList.SetComboBox(nCount, 0, TRUE, &xStringArray, xStringArray.GetSize(), 0);
	xRequirementList.SetEdit(nCount, 1);
	xRequirementList.SetEdit(nCount, 3);
    if (bCommit)
    { xRequirementList.SetEdit(nCount, 4); }
    
	if (m_pxDropMonsterDialog != NULL)
	{
		m_pxDropMonsterDialog->ShowWindow(SW_HIDE);
	}
}

void CQuestEditorView::AddQuestRewardList(CXListCtrl &xRewardList, CStringArray &xStringArray)
{
	int nSubItem = 0;
	int nCount = xRewardList.GetItemCount();

	xRewardList.InsertItem(nCount, "");	
	xRewardList.SetComboBox(nCount, 0, TRUE, &xStringArray, xStringArray.GetSize(), 0);
	xRewardList.SetEdit(nCount, 1);
	xRewardList.SetEdit(nCount, 3);
    xRewardList.SetEdit(nCount, 6);
    xRewardList.SetEdit(nCount, 8); // 最大星级
    xRewardList.SetEdit(nCount, 10); 
}

void CQuestEditorView::GetQuestRequirement(CXListCtrl &xRequirementList, SQuest &xQuest, bool bCommit)
{	
	if (bCommit)  //完成要求
	{
		xQuest.ClearCommitRequirement();
	}
	else  //前提要求
	{
		xQuest.ClearReceiveRequirement();
	}

	int nRequirement = xRequirementList.GetItemCount();
	for (int i = 0; i < nRequirement; ++i)
	{
		CString strType = xRequirementList.GetItemText(i, 0);
		if (strType == Default_Select)
		{
			continue;
		}

		SQuestRequirement xRequirement;

		xRequirement.byType = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strType.GetBuffer());
		xRequirement.Value = GetListItemInt(xRequirementList, i, 1, -1);
		xRequirement.MaxNum = GetListItemInt(xRequirementList, i, 3, 0);

        if (bCommit)
        { xRequirement.nRewardID = GetListItemInt(xRequirementList, i, 4, 0); }
        
        if (xRequirement.byType == SQuest::eRequirement_Var)    // 如果类型为计数变量
        {//保存计数变量对应的StringID
            xRequirement.nStringID = GetListItemInt(xRequirementList, i, 2, InvalidLogicNumber);
        }

		if (xRequirement.byType == SQuest::eRequirement_Profession)	//如果是职业限定
		{
			bool bFind = false;

			xRequirement.Value =  1 << xRequirement.Value;
			SQuest::RequirementType::iterator viter = xQuest.stReceiveRequirement.begin();
			SQuest::RequirementType::iterator vend = xQuest.stReceiveRequirement.end();

			for ( ; viter != vend; ++viter)
			{
				if ((*viter).byType == SQuest::eRequirement_Profession)
				{
					(*viter).Value |= xRequirement.Value;					
					bFind = true;
					break;	
				}
			}

			if (bFind)
			{
				continue;
			}
		}
		else if (xRequirement.byType == SQuest::eRequirement_Monster)  //怪物
		{
			DropTaskItem::STask xTask;
			if (m_xDropTaskItem.FindDropItemByMonsterId(xRequirement.Value, xQuest.Id, xTask) != -1)
			{
				xRequirement.wVar = xTask.nVarId;
			}
			else
			{
                CString strError = "";
                strError.Format(_T("任务[%u]找不到怪物[%u]掉落关联！"), xQuest.Id, xRequirement.Value);
				AfxMessageBox(strError);
				continue;
			}			
		}
        else if (xRequirement.byType == SQuest::eRequirement_Var || xRequirement.byType == SQuest::eRequirement_VarLimit )
		{
			xRequirement.wVar = xRequirement.Value;
		}
			
		if (bCommit)  //完成要求
		{
			xQuest.AddCommitRequirement(&xRequirement);
		}
		else  //前提要求
		{
			xQuest.AddReceiveRequirement(&xRequirement);
		}
	}
}

void CQuestEditorView::GetQuestReward(CXListCtrl &xRewardList, SQuest &xQuest)
{
	xQuest.ClearReward();

	int nRewardCount = xRewardList.GetItemCount();
	for (int i = 0; i < nRewardCount; ++i)
	{
		CString strType = xRewardList.GetItemText(i, 0);
		if (strType == Default_Select)
		{
			continue;
		}

		SQuestReward xReward;
		xReward.byType = GetSetInfoValue(m_xSetInfo[Enum_Reward], strType.GetBuffer());
		xReward.Value = GetListItemInt(xRewardList, i, 1, -1);	
		xReward.Number = GetListItemInt(xRewardList, i, 3, 0);	

		CString strProfession = xRewardList.GetItemText(i, 4);
        short shProfession = -1;
		if ( !strProfession.IsEmpty() && strProfession != Default_Select )
		{
			shProfession = GetSetInfoValue(m_xSetInfo[Enum_Profession], strProfession.GetBuffer());

            xReward.shProfession = 1 << shProfession;       //偏移该职业的位置
		}

        
		CString strSex = xRewardList.GetItemText(i, 5);
		if (!strSex.IsEmpty())
		{
			xReward.shSex = GetSetInfoValue(m_xSetInfo[Enum_Sex], strSex.GetBuffer());

			if (xReward.shSex == -1)
			{
				xReward.shSex = Sex_Max;
			}
			else
			{
				//if (shProfession == EA_Fan) //舞娘只能是女性
				//{
				//	xReward.shSex = Sex_Female;
				//}
			}			
		}

        CString ValueIcon = xRewardList.GetItemText(i,6);
        int Id = atoi(ValueIcon);
        if (Id < 0)
        {
            Id = 0;
        }
        xReward.Icon = Id;

        CString strRandStar = xRewardList.GetItemText(i, 7);
        if (!strRandStar.IsEmpty())
        {
            int nRandStar = GetSetInfoValue(m_xSetInfo[Enum_IsRandStar], strRandStar.GetBuffer()); // 0为不随机， 1为随机
            bool bStarRandom = (nRandStar == 0) ? false : true;
            xReward.bIsStarRandom = bStarRandom;
        }
        xReward.nStarLevel = GetListItemInt(xRewardList, i, 8, 0);
        if (xReward.nStarLevel > 10)    // 星级最大为10
        {
            xReward.nStarLevel = 10;
        }

        CString strBound = xRewardList.GetItemText(i, 9);
        if ( !strBound.IsEmpty() )
        {
            int nBound = GetSetInfoValue( m_xSetInfo[Enum_IsBound], strBound.GetBuffer() );
            bool bBound = (nBound == 0) ? false : true;
            xReward.bIsBound = bBound;
        }

        CString strRewardID = xRewardList.GetItemText(i,10);
        xReward.RewardID = atoi(strRewardID);      

		xQuest.AddReward(&xReward);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void CQuestEditorView::GetFormatString(char* szText, int nSize, char* szFormat, va_list &valist)
{
	if (szText == NULL || nSize <= 0 || szFormat == NULL)
	{
		return;
	}
	
	vsprintf_s(szText, nSize, szFormat, valist);
	va_end(valist);
}

void CQuestEditorView::SetEditText(CEdit& xEdit, char *pszFormat, ...)
{
	if (xEdit.m_hWnd != NULL)
	{
		char szValue[100] = "";
	
		va_list valist;
		va_start(valist,pszFormat);
		GetFormatString(szValue, sizeof(szValue) - 1, pszFormat, valist);

		xEdit.SetWindowText(szValue);
	}
}

int CQuestEditorView::GetEditInt(CEdit& xEdit, int nDef)
{
	CString strValue = "";

	xEdit.GetWindowText(strValue);

	if (strValue.IsEmpty())
	{
		return nDef;
	}

	return atoi(strValue.GetBuffer());
}

void CQuestEditorView::InsertItemText(CListCtrl &xList, int nItem, char *pszFormat, ...)
{
	if (xList.m_hWnd != NULL)
	{
		char szValue[100] = "";

		va_list valist;
		va_start(valist,pszFormat);
		GetFormatString(szValue, sizeof(szValue) - 1, pszFormat, valist);

		xList.InsertItem(nItem, szValue);
	}	
}

void CQuestEditorView::SetListItemText(CListCtrl& xList, int nItem, int nSubItem, char *pszFormat, ...)
{
	if (xList.m_hWnd != NULL)
	{
		char szValue[100] = "";

		va_list valist;
		va_start(valist,pszFormat);	
		GetFormatString(szValue, sizeof(szValue) - 1, pszFormat, valist);
	
		xList.SetItemText(nItem, nSubItem, szValue);
	}	
}

int CQuestEditorView::GetListItemInt(CListCtrl &xList, int nItem, int nSubItem, int nDef)
{
	CString strValue = xList.GetItemText(nItem, nSubItem);

	if (strValue.IsEmpty())
	{
		return nDef;
	}

	return (atoi(strValue.GetBuffer()));
}


bool CQuestEditorView::SubString(string &strDest,string &strSub,string strSign)
{
	if(strDest == "")
	{
		strSub = "";
		return false;
	}

	string::size_type nPos = strDest.find(strSign);
	if(nPos == string::npos)
	{
		strSub = strDest;
		strDest = "";
		return true;
	}

	strSub = strDest.substr(0, nPos);
	strDest = strDest.substr(nPos + 1);

	return true;
}

int CQuestEditorView::SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle)
{
	xList.SetExtendedStyle(dwStyle);

	RECT rect;
	xList.GetClientRect(&rect);

	return (rect.right - rect.left);
}

int CQuestEditorView::GetListCtrlCurSel(CListCtrl &xList)
{
	POSITION pos = xList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		return xList.GetNextSelectedItem(pos); 
	}

	return -1;
}

int CQuestEditorView::GetSetInfoValue(vector<SetInfo> &vecSetInfo, string strName)
{
	if (strName.empty())
	{
		return -1;
	}

	setiter iter = vecSetInfo.begin();
	setiter end = vecSetInfo.end();
	for ( ; iter != end; ++iter)
	{

		if ((*iter).strName == strName)
		{
			return (*iter).nValue;
		}
	}

	return -1;
}

const char* CQuestEditorView::GetSetInfoName(vector<SetInfo> &vecSetInfo, int nValue, const char *pszDef /* = ""*/)
{
	if (nValue == -1)
	{
		return pszDef;
	}

	setiter iter = vecSetInfo.begin();
	setiter end = vecSetInfo.end();

	for ( ; iter != end; ++iter)
	{

		if ((*iter).nValue == nValue)
		{
			return (*iter).strName.c_str();
		}
	}

	return pszDef;
}

void CQuestEditorView::OnComboSelectionProperty(WPARAM nItem, LPARAM nSubItem)
{
	CString strName = m_listProperty.GetItemText(nItem, nSubItem);

	if (nItem == 0 && nSubItem == 2)  //任务类型(主线 支线,活动 )显示
	{
		CString strType = m_listProperty.GetItemText(nItem, nSubItem);
		if (strType == Default_Select)
		{
			return;
		}

		//获得已经
		CString strText = m_listProperty.GetItemText(1, 2);
		int nPos = strText.Find("】");
		if (nPos != -1)
		{
			nPos += 2;  //】占2个字符
		}
		strText = strText.Mid(nPos);
		strType.Append(strText);

		m_listProperty.SetItemText(1, 2, strType);
	}
	if (nItem == 2 && nSubItem == 2)  //品质
	{								
		int nQualityId = GetSetInfoValue(m_xSetInfo[Enum_Quality], strName.GetBuffer());
		if (nQualityId != -1)
		{
			SetListItemText(m_listProperty, nItem, 1, "%d", nQualityId);
		}
		else
		{
			m_listProperty.SetItemText(nItem, 1, "");
		}
	}			
	else if (nItem == 6 && nSubItem == 2) //地图
	{
		//int nMapId = GetSetInfoValue(m_xSetInfo[Enum_Map], strName.GetBuffer());
        CString strType = m_listProperty.GetItemText(nItem, nSubItem);
        int startPos = strType.Find('=');
        int lastPos  = strType.Find(')');
        CString strMapID = strType.Mid(startPos+1, lastPos-startPos-1);
		if (!strMapID.IsEmpty())
		{
			SetListItemText(m_listProperty, nItem, 1, "%s", strMapID.GetBuffer());
		}
		else
		{
			m_listProperty.SetItemText(nItem, 1, "");
		}
	}
	else if ((nItem == 5 || nItem == 7) && nSubItem == 2) //交任务目标
	{
		int nNpcId = GetSetInfoValue(m_xSetInfo[Enum_Position], strName.GetBuffer());
		if (nNpcId != -1)
		{
			SetListItemBGroundColor(m_listProperty, nItem, 1, Default_Grund_Color);
			SetListItemText(m_listProperty, nItem, 1, "%d", nNpcId);
		}	
		else
		{
			SetListItemBGroundColor(m_listProperty, nItem, 1, Red_Ground_Color);
			m_listProperty.SetItemText(nItem, 1, "");
		}
	}
}

void CQuestEditorView::OnComboSelectionRequiement(WPARAM nItem, LPARAM nSubItem)
{
	CString strName = m_pxListCtrl->GetItemText(nItem, 0);
	int nType = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strName.GetBuffer()); //类型

	if (nSubItem == 0)  // 第一列 选择类型
	{
		//先恢复默认背景色
		m_pxListCtrl->Resume(nItem, 1);
		for(int i = 0; i < m_pxListCtrl->GetColumns(); ++i)
		{
			SetListItemBGroundColor(*m_pxListCtrl, nItem, i, Default_Grund_Color);
		}

		if (nType == SQuest::eRequirement_Profession)
		{					
			m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Profession], m_xStringArray[Enum_Profession].GetCount(), 0);

			m_pxListCtrl->SetItemText(nItem, 1, "");
			m_pxListCtrl->SetItemText(nItem, 3, "");	
		}
		else if (nType == SQuest::eRequirement_Sex)
		{					
			m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Sex], m_xStringArray[Enum_Sex].GetCount(), 0);

			m_pxListCtrl->SetItemText(nItem, 1, "");
			m_pxListCtrl->SetItemText(nItem, 3, "");	
		}		
		else if (nType == SQuest::eRequirement_Monster)
		{
			m_pxListCtrl->SetItemText(nItem, 1, "");
			m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Monster], m_xStringArray[Enum_Monster].GetCount(), 0);	

			for(int i = 0; i < m_pxListCtrl->GetColumns(); ++i)
			{
				SetListItemBGroundColor(*m_pxListCtrl, nItem, i, Green_Ground_Color);
			}					
		}
		else if (nType == SQuest::eRequirement_Item)
		{
			m_pxListCtrl->SetItemText(nItem, 1, "");
			m_pxListCtrl->SetItemText(nItem, 3, "1");	
			m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Item], m_xStringArray[Enum_Item].GetCount(), 0);

			for(int i = 0; i < m_pxListCtrl->GetColumns(); ++i)
			{
				SetListItemBGroundColor(*m_pxListCtrl, nItem, i, Blue_Ground_Color);
			}	
		}
        else if (nType == SQuest::eRequirement_Var)     // 如果需要类型为计数变量
        {
            m_pxListCtrl->SetEdit(nItem, 1); // 设置计数变量Value可编辑
            m_pxListCtrl->SetEdit(nItem, 2); // 设置计数变量对应的字串ID
        }
		else 
		{
			//恢复
			m_pxListCtrl->SetEdit(nItem, 1);
			m_pxListCtrl->Resume(nItem, 2);								
			m_pxListCtrl->SetItemText(nItem, 2, "");					
		}
	}
	else if (nSubItem == 2)  //第3列
	{
		int nValue = -1;
		CString strType = m_pxListCtrl->GetItemText(nItem, nSubItem);

		if (nType == SQuest::eRequirement_Profession)
		{			
			nValue = GetSetInfoValue(m_xSetInfo[Enum_Profession], strType.GetBuffer());				
		}
		else if (nType == SQuest::eRequirement_Sex)
		{
			nValue= GetSetInfoValue(m_xSetInfo[Enum_Sex], strType.GetBuffer());
		}
		else if (nType == SQuest::eRequirement_Item)
		{
			nValue= GetSetInfoValue(m_xSetInfo[Enum_Item], strType.GetBuffer());
		}
		else if (nType == SQuest::eRequirement_Monster)
		{
			nValue= GetSetInfoValue(m_xSetInfo[Enum_Monster], strType.GetBuffer());
		}

		if (nValue != -1)
		{
			SetListItemText(*m_pxListCtrl, nItem, 1, "%d", nValue);
		}
		else
		{
			m_pxListCtrl->SetItemText(nItem, 1, _T(""));
		}
	}			
}


void CQuestEditorView::OnComboSelectionReward(WPARAM nItem, LPARAM nSubItem)
{
	CString strTypeName = m_pxListCtrl->GetItemText(nItem, 0);
	int nType = GetSetInfoValue(m_xSetInfo[Enum_Reward], strTypeName.GetBuffer());

	if (nSubItem == 0)
	{
        m_pxListCtrl->Resume(nItem, 2);	
		m_pxListCtrl->Resume(nItem, 4);
		m_pxListCtrl->Resume(nItem, 5);

		m_pxListCtrl->SetItemText(nItem, 4, "");
		m_pxListCtrl->SetItemText(nItem, 5, "");

		if (nType == SQuest::eReward_Title)
		{					
			m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Title], m_xStringArray[Enum_Title].GetCount(), 0);

			m_pxListCtrl->SetItemText(nItem, 1, "");
			m_pxListCtrl->SetItemText(nItem, 3, "");					
		}
		else if (nType == SQuest::eReward_Buff)
		{					
			m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Buff], m_xStringArray[Enum_Buff].GetCount(), 0);

			m_pxListCtrl->Resume(nItem, 1);
			m_pxListCtrl->SetItemText(nItem, 1, "");
			m_pxListCtrl->SetItemText(nItem, 3, "");				
		}
        else if ( nType == SQuest::eReward_Item || nType == SQuest::eReward_SpecialItem )
		{
			m_pxListCtrl->Resume(nItem, 1);		
			m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Item], m_xStringArray[Enum_Item].GetCount(), 0);
			m_pxListCtrl->SetComboBox(nItem, 4, TRUE, &m_xStringArray[Enum_Profession], m_xStringArray[Enum_Profession].GetCount(), 0);
			m_pxListCtrl->SetComboBox(nItem, 5, TRUE, &m_xStringArray[Enum_Sex], m_xStringArray[Enum_Sex].GetCount(), 0);
            m_pxListCtrl->SetComboBox(nItem, 7, TRUE, &m_xStringArray[Enum_IsRandStar], m_xStringArray[Enum_IsRandStar].GetCount(), 0);
            m_pxListCtrl->SetComboBox(nItem, 9, TRUE, &m_xStringArray[Enum_IsBound], m_xStringArray[Enum_IsBound].GetCount(), 0);
		}
	}
	else if (nSubItem == 2)
	{
		int nValue = -1;
		CString strType = m_pxListCtrl->GetItemText(nItem, nSubItem);

		if (nType == SQuest::eReward_Title)
		{
			nValue = GetSetInfoValue(m_xSetInfo[Enum_Title], strType.GetBuffer());
		}
		else if (nType == SQuest::eReward_Buff)
		{
			nValue = GetSetInfoValue(m_xSetInfo[Enum_Buff], strType.GetBuffer());
		}
        else if ( nType == SQuest::eReward_Item || nType == SQuest::eReward_SpecialItem )
		{
			CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(strType.GetBuffer());
			if (pItem != NULL)
			{
				nValue = pItem->ustItemID;
			}
		}

		if (nValue != -1)
		{
			SetListItemText(m_listReward, nItem, 1, "%d", nValue);
		}
		else
		{
			m_listReward.SetItemText(nItem, 1, _T(""));
		}
	}
}

LRESULT CQuestEditorView::OnComboSelection(WPARAM nItem, LPARAM nSubItem)
{
	if (nItem >= 0 && nSubItem >= 0)
	{
		CString strName = m_pxListCtrl->GetItemText(nItem, nSubItem);
		if (m_strValue == strName)
		{
			return 0;
		}

		//属性列表
		if (m_pxListCtrl == &m_listProperty)    // 属性
		{
			OnComboSelectionProperty(nItem, nSubItem);
		}
		else if (m_pxListCtrl == &m_listPreRequirement || m_pxListCtrl == &m_listPostRequiement) //任务要求
		{
			OnComboSelectionRequiement(nItem, nSubItem);
		}
		else if (m_pxListCtrl == &m_listReward)     // 奖励
		{			
			OnComboSelectionReward(nItem, nSubItem);
		}
	}

	return 0;
}


void CQuestEditorView::OnEditEndProperty(WPARAM nItem, LPARAM nSubItem)
{
	/////任务ID
	if (nItem == 0 && nSubItem == 1)
	{
		int nQuestId = GetListItemInt(*m_pxListCtrl, nItem, nSubItem, -1);

		SQuest *pQuest = theQuestManager.GetQuest(nQuestId);
		if (pQuest != NULL)
		{
			ShowQuestInformation(*pQuest);
		}
		else
		{
			ClearQuestInformation();

			SetQuestStringId(nQuestId);
		}
	}
	else if ((nItem == 1 || nItem == 3 || nItem == 4) && nSubItem == 2)  //名字,  描述 对象  有编辑需要保存
	{				
		int nNameId = GetListItemInt(*m_pxListCtrl, nItem, 1, Empty_String_Id);
		CString strValue = m_pxListCtrl->GetItemText(nItem, nSubItem);

		if (!strValue.IsEmpty() && strValue != Empty_String_Value)
		{						
			theXmlString.AddString(nNameId, strValue.GetBuffer());												
		}
	}			
}

void CQuestEditorView::OnEditEndRequiement(WPARAM nItem, LPARAM nSubItem)
{
	CString strName = m_pxListCtrl->GetItemText(nItem, 0);
	int nType = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strName.GetBuffer());

	if (nSubItem == 1)
	{
		int nId = GetListItemInt(*m_pxListCtrl, nItem, nSubItem, -1);

		CString strValue = "";

		if (nType == SQuest::eRequirement_Quest)
		{
			SQuest *pQuest = theQuestManager.GetQuest(nId);
			if (pQuest != NULL)
			{
				strValue = theXmlString.GetString(pQuest->QuestName);
			}
		}
		else if (nType == SQuest::eRequirement_Monster)
		{
			CItemDetail::SMonster *pMonster = GettheItemDetail().GetMonsterById(nId);
			if (pMonster != NULL)
			{
				strValue = pMonster->GetName();
			}

			m_pxListCtrl->Resume(nItem, nSubItem);
		}
		else if (nType == SQuest::eRequirement_Item)
		{
			CItemDetail::SItemCommon *pItem = GettheItemDetail().GetItemByID(nId);
			if (pItem != NULL)
			{
				strValue = pItem->GetItemName();
			}

			m_pxListCtrl->Resume(nItem, nSubItem);
		}

		m_pxListCtrl->SetItemText(nItem, 2, strValue);
	}				
}


void CQuestEditorView::OnEditEndReward(WPARAM nItem, LPARAM nSubItem)
{
	if (nSubItem == 1)
	{
		CString strName = m_pxListCtrl->GetItemText(nItem, 0);
		int nType = GetSetInfoValue(m_xSetInfo[Enum_Reward], strName.GetBuffer());					
		int nId = GetListItemInt(*m_pxListCtrl, nItem, nSubItem, -1);

		CString strValue = "";

        if ( nType == SQuest::eReward_Item || nType == SQuest::eReward_SpecialItem )
		{
			CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(nId);
			if (pItem != NULL)
			{
				strValue = pItem->GetItemName();
			}
		}
		else if (nType == SQuest::eReward_Title)
		{
			strValue = GetSetInfoName(m_xSetInfo[Enum_Title], nId, Default_Select);			
		}
		else if (nType == SQuest::eReward_Buff)
		{
			strValue = GetSetInfoName(m_xSetInfo[Enum_Buff], nId, Default_Select);			
		}

		m_pxListCtrl->SetItemText(nItem, 2, strValue);        
	}			
}

LRESULT CQuestEditorView::OnEditEnd(WPARAM nItem, LPARAM nSubItem)
{
	if (nItem >= 0 && nSubItem >= 0)
	{
		//属性列表
		if (m_pxListCtrl == &m_listProperty)
		{
			OnEditEndProperty(nItem, nSubItem);
			
		}	
		else if (m_pxListCtrl == &m_listPreRequirement || m_pxListCtrl == &m_listPostRequiement)
		{
			OnEditEndRequiement(nItem, nSubItem);
			
		}
		else if (m_pxListCtrl == &m_listReward)
		{			
			OnEditEndReward(nItem, nSubItem);
			
		}
	}

	return 0;
}


LRESULT CQuestEditorView::OnCheckbox(WPARAM nItem, LPARAM nSubItem)
{
	if (nItem >= 0 && nSubItem >= 0)
	{

	}

	return 0;
}

void CQuestEditorView::ClickList(CListCtrl &xList, NMHDR *pNMHDR)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nItem = -1;
	int nSubItem = -1;
	if (pNMIA)
	{
		nItem = pNMIA->iItem;
		nSubItem = pNMIA->iSubItem;
	}

	if (nItem >= 0 && nSubItem >= 0)
	{
		m_pxListCtrl = (CXListCtrl*) &xList;  //保存当前的list控件

		m_strValue = xList.GetItemText(nItem, nSubItem);

		m_nItem = nItem;
		m_nSubItem = nSubItem;
	}
	else
	{
		m_nItem = -1;
		m_nSubItem = -1;
	}
}


void CQuestEditorView::OnNMClickListReward(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	ClickList(m_listReward, pNMHDR);

	*pResult = 0;
}

void CQuestEditorView::OnNMClickListPreRequiement(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	ClickList(m_listPreRequirement, pNMHDR);

	*pResult = 0;
}

void CQuestEditorView::OnNMClickListPostRequiement(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	ClickList(m_listPostRequiement, pNMHDR);

	*pResult = 0;
}

void CQuestEditorView::OnNMClickListProprety(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	ClickList(m_listProperty, pNMHDR);

	*pResult = 0;
}

void CQuestEditorView::CheckFilePathExist(const char* pszPath)
{
	if (pszPath == 0 || *pszPath == 0)
	{
		return;
	}

	CString strClient = "";
	strClient.Format("%s%s", pszPath, Client_Path);
	if (GetFileAttributes(strClient) == -1)
	{
		_mkdir(strClient.GetBuffer());
	}

	CString strServer = "";
	strServer.Format("%s%s", pszPath, Server_Path);
	if (GetFileAttributes(strServer) == -1)
	{
		_mkdir(strServer.GetBuffer());
	}
}

void CQuestEditorView::OnFileLoadQuestFile()
{
	// TODO: Add your command handler code here
	SetCurrentWorkDir();

	//int nId = AddInQuestList();
	//if (nId == -1)
	//{
	//	return;
	//}
	CString strFolder = InitPath;

	CFolderDialog xFolderDialog(&strFolder);
	if (xFolderDialog.DoModal() == IDOK)
	{
		//保存当前的String文件夹路径
		m_strQuestFile = strFolder.GetBuffer();

		//判断有无Client 和 Server文件夹
		CheckFilePathExist(m_strQuestFile.c_str());

		m_mapViewQuest.clear();
		m_xTreeQuest.ClearAllItemBgColor();

		//加载任务文件		
		if (theQuestInfo.LoadQuest(m_strQuestFile.c_str()))
		{		
			CString strStringFile = "";
			strStringFile.Format("%s%s", m_strQuestFile.c_str(), Client_Path);
			theXmlString.LoadStringPath(strStringFile.GetBuffer(), true);			
		}
		else
		{
			AfxMessageBox("加载任务文件失败！");
			return;
		}

        CString RandFilePath = m_strQuestFile.c_str();
        RandFilePath += "\\Server\\RandQuest.config";
        if (!theQuestManager.LoadQuestRandConfigFile(RandFilePath.GetBuffer()))
        {
            CString strStringFile = "";
            strStringFile.Format("加载任务概率文件失败！请检查%s",RandFilePath.GetBuffer());
            AfxMessageBox(strStringFile.GetBuffer());
            return;
        }
        theQuestManager.SaveQuestRandConfigFile(RandFilePath.GetBuffer());
		//加载物品掉落设定
		m_strDropItemFile.Format("%s%s\\%s", m_strQuestFile.c_str(), Server_Path, Drop_Item_File);
		m_xDropTaskItem.LoadXmlData(m_strDropItemFile.GetBuffer());
		//////////////////////////////////////////////////////////////////////////////////////////////

		//显示在树控件中
		ShowQuestTreeList();		
	}
}

void CQuestEditorView::OnFileSaveQuestFile()
{
	// TODO: Add your command handler code here


	//CString strID = "";

	/*int nId = AddInQuestList();
	if (nId == -1)
	{
		return;
	}*/

	if(m_strQuestFile.empty())
	{
		OnFileLoadQuestFile();
	}

	//没有设定就返回
	if (m_strQuestFile.empty())
	{
		return;
	}

	int nId = AddInQuestList();
    if (nId == -1)
    {
        return;
    }

	//保存掉落关联文件
	RemoveFileReadOnly(m_strDropItemFile.GetBuffer());
	m_xDropTaskItem.SaveXmlData(m_strDropItemFile.GetBuffer());

	//批量添加
	if (m_checkBatch.GetCheck() == 1 && nId != -1)
	{
		SetListItemText(m_listProperty, 0, 1, "%d", ++nId);
		SetQuestStringId(nId);

		m_listPostRequiement.DeleteAllItems();
	}	
}

//另存为
void CQuestEditorView::OnFileSaveAt()
{
	// TODO: Add your command handler code here
	SetCurrentWorkDir();
	CString strFolder = InitPath;

	CFolderDialog xFolderDialog(&strFolder);
	if (xFolderDialog.DoModal() == IDOK)
	{
		//判断有无Client 和 Server文件夹
		CheckFilePathExist(strFolder.GetBuffer());

		//保存任务文件
		if (!theQuestInfo.SaveQuest(strFolder.GetBuffer()))
		{
			AfxMessageBox("保存任务文件失败！");
			return;
		}
	
		//保存语言文件
		QuestInfo::itrSQuests iter = theQuestInfo.m_pQuests.begin();
		QuestInfo::itrSQuests end = theQuestInfo.m_pQuests.end();
		for ( ; iter != end; ++iter)
		{
			if (iter->second->Id != -1)
			{
				vector<int> vecStringId;
				GetQuestStringId(iter->second->Id, vecStringId);

				string strStringFile = GetFileFullPath(strFolder.GetBuffer(), iter->second->Id, Client_Path, String_Ext);
				theXmlString.SaveStringFile(strStringFile.c_str(), vecStringId, false);
			}
		}

		//保存物品掉落设定
		CString strDropItemFile = "";
		strDropItemFile.Format("%s%s\\%s", strFolder.GetBuffer(), Server_Path, Drop_Item_File);
		m_xDropTaskItem.SaveXmlData(strDropItemFile.GetBuffer());
		//////////////////////////////////////////////////////////////////////////////////////////////

		SaveQuestIdList(strFolder.GetBuffer());
	}
}

void CQuestEditorView::OnFileFind()
{
	// TODO: Add your command handler code here
	ShowFindDialog();
}

void CQuestEditorView::OnNMClickTreeItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_xTreeQuest.GetCursorItem();
	ShowQuestInformation(hItem);

	*pResult = 0;
}

void CQuestEditorView::OnTvnSelchangedTreeQuest(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_xTreeQuest.GetSelectedItem();
	ShowQuestInformation(hItem);

	*pResult = 0;
}


void CQuestEditorView::ShowFindQuest(int nId)
{
	if (nId == -1)
	{
		return;
	}

	CString strId = "";
	strId.Format("%d", nId);

	HTREEITEM hItem = m_xTreeQuest.FindNodeItem(Quest_Root, strId);
	if (hItem != NULL)
	{
		//选中
		m_xTreeQuest.SetFocus();
		m_xTreeQuest.Select(hItem, TVGN_CARET);
		m_xTreeQuest.SelectItem(hItem);
				
		SQuest *pQuest = theQuestManager.GetQuest(nId);
		if (pQuest != NULL)
		{
			ShowQuestInformation(*pQuest);
		}
	}
}

void CQuestEditorView::ShowNextFindQuest()
{
	if (m_vecFindQuestId.empty())
	{
		return;
	}

	vector<int>::iterator iter = find(m_vecFindQuestId.begin(), m_vecFindQuestId.end(), m_nShowFindId);
	if (iter != m_vecFindQuestId.end())
	{
		++iter;		
	}

	if (iter == m_vecFindQuestId.end())
	{
		iter = m_vecFindQuestId.begin();
	}

	m_nShowFindId = (*iter);
	ShowFindQuest(m_nShowFindId);
}

CQuestEditorView::_FindFun CQuestEditorView::FindFun[Enum_QuestMax] = 
{
	&CQuestEditorView::FindByQuestId,
	&CQuestEditorView::FindByQuestNameId,
	&CQuestEditorView::FindByQuestName,
	&CQuestEditorView::FindByQuality,
	&CQuestEditorView::FindByContentId,
	&CQuestEditorView::FindByContent,
	&CQuestEditorView::FindByTargetId,
	&CQuestEditorView::FindByTarget,
	&CQuestEditorView::FindByMapId,
	&CQuestEditorView::FindByMapName,
	&CQuestEditorView::FindByNpcId,
	&CQuestEditorView::FindByNpcName,
	&CQuestEditorView::FindByCanAssist,
	&CQuestEditorView::FindByCanShare,
	&CQuestEditorView::FindByRepeate,
	&CQuestEditorView::FindByCancel,
	&CQuestEditorView::FindByPreRequementItemId,
	&CQuestEditorView::FindByPreRequementItemName,
	&CQuestEditorView::FindByPostRequementItemId,
	&CQuestEditorView::FindByPostRequementItemName,
	&CQuestEditorView::FindByRewardItemId,
	&CQuestEditorView::FindByRewardItemName,
};

//查找函数
int CQuestEditorView::FindQuest(CString strValue, int nType, FindInfo *pFindInfo /* = NULL */)
{
	m_nShowFindId = -1;
	m_vecFindQuestId.clear();

	if (nType < Enum_QuestMax)
	{
		(this->*FindFun[nType])(strValue, pFindInfo);
	}

	if (!m_vecFindQuestId.empty())
	{
		m_nShowFindId = m_vecFindQuestId[0];
	}

	return m_nShowFindId;
}

void CQuestEditorView::FindByQuestId(CString strValue, FindInfo *pFindInfo /* = NULL */)
{
	questiter iter = theQuestInfo.m_pQuests.find(atoi(strValue.GetBuffer()));
	if (iter != theQuestInfo.m_pQuests.end())
	{
		if ((*iter).second->Id != -1)
		{
			m_vecFindQuestId.push_back((*iter).second->Id);
		}
	}
}

void CQuestEditorView::FindByQuestNameId(CString strValue, FindInfo *pFindInfo /* = NULL */)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nNameId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if (nNameId == nNameId)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditorView::FindByQuestName(CString strValue, FindInfo *pFindInfo /* = NULL */)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nFindMatch = 0;
	if (pFindInfo != NULL)
	{
		nFindMatch = pFindInfo->nFindMatch;
	}

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			string strName = theXmlString.GetString((*iter).second->QuestName);

			if (nFindMatch == 0)
			{
				if (strName == strValue.GetBuffer())
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
			else if (nFindMatch == 1)
			{
				if (strName.find(strValue) != string::npos)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}	
}


void CQuestEditorView::FindByQuality(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nQuality = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->RankId ==  nQuality)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}

}

void CQuestEditorView::FindByContentId(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nContentId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->IntroStringId == nContentId)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditorView::FindByContent(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nFindMatch = 0;
	if (pFindInfo != NULL)
	{
		nFindMatch = pFindInfo->nFindMatch;
	}

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			string strName = theXmlString.GetString((*iter).second->IntroStringId);

			if (nFindMatch == 0)
			{
				if (strName == strValue.GetBuffer())
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
			else if (nFindMatch == 1)
			{
				if (strName.find(strValue) != string::npos)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}	
}

void CQuestEditorView::FindByTargetId(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nTargetId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->TargetStringId == nTargetId)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditorView::FindByTarget(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nFindMatch = 0;
	if (pFindInfo != NULL)
	{
		nFindMatch = pFindInfo->nFindMatch;
	}

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			string strName = theXmlString.GetString((*iter).second->TargetStringId);

			if (nFindMatch == 0)
			{
				if (strName == strValue.GetBuffer())
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
			else if (nFindMatch == 1)
			{
				if (strName.find(strValue) != string::npos)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}	
}

void CQuestEditorView::FindByMapId(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nMapId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->MapId == nMapId)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}


void CQuestEditorView::FindByMapName(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	int nMapId = GetSetInfoValue(m_xSetInfo[Enum_Map], strValue.GetBuffer());
	if (nMapId == -1)
	{
		return;
	}

	strValue.Format("%d", nMapId);

	FindByMapId(strValue, pFindInfo);
}

void CQuestEditorView::FindByNpcId(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();


	int nNpcId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->ReplyTargetId == nNpcId)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditorView::FindByNpcName(CString strValue, FindInfo *pFindInfo)
{
	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByName(strValue.GetBuffer());
	if (pNpc == NULL)
	{
		return;
	}

	strValue.Format("%d", pNpc->id);

	FindByNpcId(strValue, pFindInfo);
}



void CQuestEditorView::FindByCanAssist(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	bool nCanAssist = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->CanAssist == nCanAssist)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditorView::FindByCanShare(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	bool nCanShare = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->CanShare == nCanShare)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditorView::FindByRepeate(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	bool nRepeate = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->IsRepeat == nRepeate)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditorView::FindByCancel(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	bool nCancel = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->IsCancel == nCancel)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditorView::FindByPreRequementItemId(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nItemId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			SQuest::RequirementType::iterator viter = (*iter).second->stReceiveRequirement.begin();
			SQuest::RequirementType::iterator vend = (*iter).second->stReceiveRequirement.end();

			for ( ; viter != vend; ++viter)
			{
				if ((*viter).byType == SQuest::eRequirement_Item && (*viter).Value == nItemId)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}
}

void CQuestEditorView::FindByPreRequementItemName(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{
	CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(strValue.GetBuffer());
	if (pItem == NULL)
	{
		return;
	}		

	strValue.Format("%d", pItem->ustItemID);

	FindByPreRequementItemId(strValue, pFindInfo);
}

void CQuestEditorView::FindByPostRequementItemId(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{

	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nItemId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			SQuest::RequirementType::iterator viter = (*iter).second->stCommitRequirement.begin();
			SQuest::RequirementType::iterator vend = (*iter).second->stCommitRequirement.end();

			for ( ; viter != vend; ++viter)
			{
				if ((*viter).byType == SQuest::eRequirement_Item && (*viter).Value == nItemId)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}
}

void CQuestEditorView::FindByPostRequementItemName(CString strValue, FindInfo *pFindInfo /* = NULL */)
{
	CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(strValue.GetBuffer());
	if (pItem == NULL)
	{
		return;
	}		

	strValue.Format("%d", pItem->ustItemID);
	FindByPostRequementItemId(strValue, pFindInfo);
}

void CQuestEditorView::FindByRewardItemId(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nItemId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			SQuest::RewardType::iterator viter = (*iter).second->stReward.begin();
			SQuest::RewardType::iterator vend = (*iter).second->stReward.end();

			for ( ; viter != vend; ++viter)
			{
                if (((*viter).byType == SQuest::eReward_Item || viter->byType == SQuest::eReward_SpecialItem ) && (*viter).Value == nItemId)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}
}

void CQuestEditorView::FindByRewardItemName(CString strValue, FindInfo *pFindInfo /* = NULL */)
{
	CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(strValue.GetBuffer());
	if (pItem == NULL)
	{
		return;
	}		

	strValue.Format("%d", pItem->ustItemID);
	FindByRewardItemId(strValue, pFindInfo);
}


void CQuestEditorView::SetListItemCanEdit()
{		
	if (m_pxListCtrl == &m_listPostRequiement || m_pxListCtrl == &m_listPreRequirement)
	{
		int nIndex = m_pxListCtrl->GetCurSel();
		if (nIndex != -1)
		{
			CString strText = m_pxListCtrl->GetItemText(nIndex, 0);

			int nType = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strText.GetBuffer());
			if (nType == SQuest::eRequirement_Monster || nType == SQuest::eRequirement_Item)
			{
				m_pxListCtrl->SetEdit(nIndex, 1);
			}
            //m_pxListCtrl->SetEdit(nIndex,6);
		}		
	}
}

//Format得到文件的完整路径
string CQuestEditorView::GetFileFullPath(const char* pszParentPath, int nId, const char* pszPath, const char* pExt)
{
	if (pszParentPath == NULL || nId == -1 || pExt == NULL)
	{
		return "";
	}

	char szFlie[_MAX_PATH] = "";
	if (*pszPath != 0)
	{
		sprintf_s(szFlie, sizeof(szFlie) - 1, "%s%s\\%d%s", pszParentPath, pszPath, nId, pExt);
	}
	else
	{
		sprintf_s(szFlie, sizeof(szFlie) - 1, "%s\\%d%s", pszParentPath, nId, pExt);
	}

	return szFlie;
}


void CQuestEditorView::ShowDropMonsterDialog()
{
	if (m_pxDropMonsterDialog == NULL)
	{
		m_pxDropMonsterDialog = new DropMonsterDialog();

		m_pxDropMonsterDialog->Create(IDD_DIALOG_DROPMONSTER, this);

		m_pxDropMonsterDialog->InitInformation();
	}

	if (m_pxDropMonsterDialog != NULL)
	{
		m_pxDropMonsterDialog->UpdateInformation();
		m_pxDropMonsterDialog->ShowWindow(SW_SHOW);
	}
}

void CQuestEditorView::ShowDropItemDialog()
{
	if (m_pxDropItemDialog == NULL)
	{
		m_pxDropItemDialog = new DropItemDialog();

		m_pxDropItemDialog->Create(IDD_DIALOG_DROPITEM, this);

		m_pxDropItemDialog->InitInformation();
	}

	if (m_pxDropItemDialog != NULL)
	{
		m_pxDropItemDialog->UpdateInformation();
		m_pxDropItemDialog->ShowWindow(SW_SHOW);
	}
}


void CQuestEditorView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_xTreeQuest.m_hWnd == NULL)
	{
		return;
	}

	RECT rect;
	GetWindowRect(&rect);

	int nHeight = rect.bottom - rect.top - 30;
	int nWidth = rect.right - rect.left - 180;

	int nPosY = 5;

	m_xTreeQuest.SetWindowPos(NULL,  5, nPosY, 135, nHeight - 10, SWP_SHOWWINDOW);

	int nPropertyHeight = (29 * nHeight / 100);
	m_listProperty.SetWindowPos(NULL, 150, nPosY, nWidth , nPropertyHeight, SWP_SHOWWINDOW);

	//前置
	nPosY += nPropertyHeight + 5;
	int nPreStaticHeight = (22 * nHeight / 100);
	m_staticPre.SetWindowPos(NULL, 150, nPosY , nWidth, nPreStaticHeight, SWP_SHOWWINDOW);

	int nPreRequiementHeight = (195 * nHeight / 1000);
	m_listPreRequirement.SetWindowPos(NULL, 155, nPosY + 15, nWidth - 10, nPreRequiementHeight, SWP_SHOWWINDOW);

	//提交
	nPosY += nPreStaticHeight + 5;
	int nPostStaticHeight = (22 * nHeight / 100);
	m_staticPost.SetWindowPos(NULL, 150, nPosY, nWidth, nPostStaticHeight, SWP_SHOWWINDOW);

	int nPostRequiementHeight = (195 * nHeight / 1000);
	m_listPostRequiement.SetWindowPos(NULL, 155, nPosY + 15, nWidth - 10, nPostRequiementHeight, SWP_SHOWWINDOW);

	//奖励
	nPosY += nPostStaticHeight + 5;
	int nRewardStaticHeight = (22 * nHeight / 100);
	m_staticReward.SetWindowPos(NULL, 150, nPosY, nWidth, nRewardStaticHeight, SWP_SHOWWINDOW);

	int nRewardHeight = (195 * nHeight / 1000);
	m_listReward.SetWindowPos(NULL, 155, nPosY + 15, nWidth - 10, nRewardHeight, SWP_SHOWWINDOW);

	nPosY += nRewardStaticHeight + 5;

	m_staticSave.SetWindowPos(NULL, 18 *(rect.right - rect.left) / 100, nPosY, 0, 0, SWP_NOSIZE);
	m_checkBatch.SetWindowPos(NULL, 40 *(rect.right - rect.left) / 100, nPosY, 0, 0, SWP_NOSIZE);
	m_checkReadOnly.SetWindowPos(NULL, 60 *(rect.right - rect.left) / 100, nPosY, 0, 0, SWP_NOSIZE);

	InitListCtrl(false);
}

void CQuestEditorView::OnNMDClickListPostRequiement(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	int nIndex = m_listPostRequiement.GetCurSel();
	if (nIndex != -1)
	{
		int nQuestId = GetListItemInt(m_listProperty, 0, 1, -1);
		if (nQuestId < 0)
		{
			return;
		}

		CString strType = m_listPostRequiement.GetItemText(nIndex, 0);
		int nType = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strType.GetBuffer());
		
		int nId = GetListItemInt(m_listPostRequiement, nIndex, 1, -1);
		int nCount = GetListItemInt(m_listPostRequiement, nIndex, 3, 0);
		if (nId <= 0 || nCount <= 0)
		{
			return;
		}

		//设置关联内容,然后在关联对话框使用
		m_xMonsterDrop.Clear();

		if (nType == SQuest::eRequirement_Monster)
		{
			m_xMonsterDrop.nMonsterId = nId;
			m_xMonsterDrop.nMonsterCount = nCount;
			m_xMonsterDrop.nQuestId = nQuestId;

			//查找关联内容
			DropTaskItem::STask xTask;
			if (m_xDropTaskItem.FindDropItemByMonsterId(nId, nQuestId, xTask) != -1)
			{
				m_xMonsterDrop.nVarId = xTask.nVarId;
				m_xMonsterDrop.nItemId = xTask.stItem.nItemId;
				m_xMonsterDrop.nItemRate = xTask.stItem.nProbability;
				m_xMonsterDrop.nItemCount = xTask.nMaxItemCount;
			}
			ShowDropMonsterDialog();
		}
		else if (nType == SQuest::eRequirement_Item)
		{
			m_xMonsterDrop.nItemId = nId;
			m_xMonsterDrop.nItemCount = nCount;
			m_xMonsterDrop.nQuestId = nQuestId;

			//查找关联
			DropTaskItem::STask xTask;
			int nMonsterId = m_xDropTaskItem.FindDropItemByItemId(nId, nQuestId, xTask);
			if (nMonsterId != -1)
			{
				m_xMonsterDrop.nVarId = xTask.nVarId;
				m_xMonsterDrop.nMonsterId = nMonsterId;
				m_xMonsterDrop.nMonsterCount = 0;
				m_xMonsterDrop.nItemRate = xTask.stItem.nProbability;
			}			
			ShowDropItemDialog();
		}		
	}
	*pResult = 0;
}


void CQuestEditorView::SetListItemColor(CXListCtrl &xList, int nItem, int nSubItem, COLORREF dwColor)
{
	if (nItem < 0 || nSubItem < 0)
	{
		return;
	}

	COLORREF crText, crBGround;

	xList.GetItemColors(nItem, nSubItem, crText, crBGround);

	xList.SetItemColors(nItem, nSubItem, dwColor, crBGround);
}


void CQuestEditorView::SetListItemBGroundColor(CXListCtrl &xList, int nItem, int nSubItem, COLORREF dwColor)
{
	if (nItem < 0 || nSubItem < 0)
	{
		return;
	}

	COLORREF crText, crBGround;

	xList.GetItemColors(nItem, nSubItem, crText, crBGround);

	xList.SetItemColors(nItem, nSubItem, crText, dwColor);
}

void CQuestEditorView::OnNMRclickListPostRequeiment(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nIndex = m_listPostRequiement.GetCurSel();
	if (nIndex != -1)
	{
		CString strType = m_listPostRequiement.GetItemText(nIndex, 0);
		int nType = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strType.GetBuffer());
		if (nType == SQuest::eRequirement_Item)
		{
			CMenu menu;
			CPoint xPoint;
			GetCursorPos(&xPoint);
			menu.LoadMenu(IDR_MENU_DROPDELETE);
			menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, xPoint.x, xPoint.y, this);
		}
	}
	else
	{
		/*CMenu menu;
		CPoint xPoint;
		GetCursorPos(&xPoint);
		menu.LoadMenu(IDR_MENU_HIDE);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, xPoint.x, xPoint.y, this);*/
	}

	*pResult = 0;
}

void CQuestEditorView::OnRClickEditor(NMHDR *pNMHDR, LRESULT *pResult)
{
	return;
	CMenu menu;
	CPoint xPoint;
	GetCursorPos(&xPoint);
	menu.LoadMenu(IDR_MENU_HIDE);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, xPoint.x, xPoint.y, this);

	*pResult = 0;
}

void CQuestEditorView::OnDeletedDrop()
{
	// TODO: Add your command handler code here
	int nIndex = m_listPostRequiement.GetCurSel();
	if (nIndex != -1)
	{
		int nQuestId = GetListItemInt(m_listProperty, 0, 1, -1);
		int itemid = GetListItemInt(m_listPostRequiement, nIndex, 1, -1);
		m_xDropTaskItem.SubQuest(-1, nQuestId,itemid);
	}
}

void CQuestEditorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == SaveShow_Timer_Id)
	{
		m_staticSave.SetWindowText("");

		KillTimer(SaveShow_Timer_Id);
	}	

	CFormView::OnTimer(nIDEvent);
}


void CQuestEditorView::SetQuestStringId(int nQuestId)//判断输入的ID是否大于0，然后产生ID+01  ID+02
{
	if (nQuestId < 0)
	{
		return;
	}

	static char* p_szFormat = "%d%02d";

	int i = 0; 
	CString strString  = "";

	strString.Format(p_szFormat, nQuestId, ++i);
	m_listProperty.SetItemText(1, 1, strString);     // 设置任务名称字串ID
	m_listProperty.SetItemText(1, 2, "");            // 任务名称字串

	strString.Format(p_szFormat, nQuestId, ++i);
	m_listProperty.SetItemText(3, 1, strString);    // 任务内容描述字串ID
	m_listProperty.SetItemText(3, 2, "");           // 任务内容描述字串

	strString.Format(p_szFormat, nQuestId, ++i);
	m_listProperty.SetItemText(4, 1, strString);    // 任务目标描述字串ID
    m_listProperty.SetItemText(4, 2, "");           // 任务目标描述字串
}


void CQuestEditorView::OnStringChange()
{
	// TODO: Add your command handler code here

	StringFileChange xStringFileChange;
	xStringFileChange.DoModal();
}

void CQuestEditorView::OnNpcChange()
{
	// TODO: Add your command handler code here

	NpcFileChange xNpcFileChange;
	xNpcFileChange.DoModal();
}

void CQuestEditorView::OnDestroy()
{
	SaveQuestIdList(m_strQuestFile.c_str());

	CFormView::OnDestroy();

	if (!m_strQuestFile.empty())
	{
		CString strFile = "";
		strFile.Format("%s\\%s", m_strQuestFile.c_str(), Common_Quest_File);

		theQuestInfo.SaveCommonFile(strFile.GetBuffer());
	}	

	// TODO: Add your message handler code here
	//释放内存
	SafeDelete(m_pxQuestFind);
	SafeDelete(m_pxDropMonsterDialog);	
	SafeDelete(m_pxDropItemDialog);
	SafeDelete(m_pxQuestStringEdit);
}

void CQuestEditorView::ShowStringEditDialog()
{
	if (m_pxQuestStringEdit == NULL)
	{
		m_pxQuestStringEdit = new QuestStringEdit();
		if (m_pxQuestStringEdit != NULL)
		{
			m_pxQuestStringEdit->Create(IDD_DIALOG_QUESTSTRINGEDIT, this);
			m_pxQuestStringEdit->InitInformation();
		}
	}

	if ( m_pxQuestStringEdit != NULL )
	{
		int nId = GetListItemInt(m_listProperty, 0, 1, -1);
		if (nId < 0 || m_strQuestFile.empty())
		{
			return;
		}
		m_pxQuestStringEdit->UpdateInitInformation(m_strQuestFile.c_str(), nId);
		m_pxQuestStringEdit->ShowWindow(SW_SHOW);
	}
}


void CQuestEditorView::SetQuestViewColor(SQuest *pQuest)
{
	if (pQuest == NULL)
	{
		return;
	}

	SQuest::RequirementType::iterator iter = pQuest->stCommitRequirement.begin();
	SQuest::RequirementType::iterator end = pQuest->stCommitRequirement.end();

	for ( ; iter != end; ++iter)
	{
		if (iter->byType == SQuest::eRequirement_Monster)
		{
			return AddQuestView(pQuest->Id, iter->byType, Monster_Left_Color, Monster_Right_Color);
		}
		else if (iter->byType == SQuest::eRequirement_Item)
		{
			return AddQuestView(pQuest->Id, iter->byType, Item_Left_Color, Item_Right_Color);
		}
	}	

	iter = pQuest->stReceiveRequirement.begin();
	end = pQuest->stReceiveRequirement.end();

	for (; iter != end; ++iter)
	{
		if (iter->byType == SQuest::eRequirement_Monster)
		{
			return AddQuestView(pQuest->Id, iter->byType, Monster_Left_Color, Monster_Right_Color);
		}
		else if (iter->byType == SQuest::eRequirement_Item)
		{
			return AddQuestView(pQuest->Id, iter->byType, Item_Left_Color, Item_Right_Color);
		}
	}

	//都没有删除原来的
	RemoveQuestView(pQuest->Id);	
}

//添加显示背景
void CQuestEditorView::AddQuestView(int nQuestId, int Type, COLORREF leftcolor, COLORREF rightcolor)
{
	if (nQuestId < 0 || Type < 0)
	{
		return;
	}

	map<int, int>::iterator iter = m_mapViewQuest.find(nQuestId);
	if (iter != m_mapViewQuest.end())
	{
		//类型相同, 怪物类型优先
		if (iter->second == Type || iter->second == SQuest::eRequirement_Monster)
		{
			return;
		}

		iter->second = Type;
	}
	else
	{
		m_mapViewQuest.insert(make_pair(nQuestId, Type));
	}
	
	SetQuestColor(nQuestId, leftcolor, rightcolor);
}

void CQuestEditorView::RemoveQuestView(int nQuestId)
{
	map<int, int>::iterator iter = m_mapViewQuest.find(nQuestId);
	if (iter != m_mapViewQuest.end())
	{
		m_mapViewQuest.erase(iter);

		SetQuestColor(nQuestId, (COLORREF) -1, (COLORREF) -1);
	}	
}

void CQuestEditorView::SetQuestColor(int nQuestId, COLORREF leftcolor, COLORREF rightcolor)
{
	CString strId = "";
	strId.Format("%d", nQuestId);

	HTREEITEM hItem = m_xTreeQuest.FindNodeItem(Quest_Root, strId);
	if (hItem != NULL)
	{
		m_xTreeQuest.SetItemBgColor(hItem, leftcolor, rightcolor);
	}
}

//去除文件的只读属性
void CQuestEditorView::RemoveFileReadOnly(const char* pszPath)
{
	if (pszPath == NULL || *pszPath == 0)
	{
		return;
	}

	DWORD dwAttr = GetFileAttributes(pszPath);
	if (m_bRemoveReadOnly && (dwAttr & FILE_ATTRIBUTE_READONLY) != 0)
	{
		dwAttr ^= FILE_ATTRIBUTE_READONLY;

		SetFileAttributes(pszPath, dwAttr);
	}
}


void CQuestEditorView::OnBnClickedCheckReadOnly()
{
	// TODO: Add your control notification handler code here

	m_bRemoveReadOnly = m_checkReadOnly.GetCheck();
}


void CQuestEditorView::SaveQuestIdList(const char* szPath)
{
	if (szPath == NULL || *szPath == NULL ) { return; }

	
	//CString strFile = "";
	//strFile.Format("%s%s\\%s", szPath, Client_Path, QuestIndex_File);

	//ofstream outfile;
	//outfile.open(strFile.GetBuffer());
	//if (!outfile) { return; }

	//QuestInfo::itrSQuests iter = theQuestInfo.m_pQuests.begin();
	//QuestInfo::itrSQuests end = theQuestInfo.m_pQuests.end();

	//for ( ; iter != end; ++iter)
	//{
	//	if (iter->second->Id != -1)
	//	{
	//		strFile.Format("%d%s", iter->second->Id, String_Ext);
	//		outfile << strFile.GetBuffer() << "\n";
	//	}
	//}

	//outfile.clear();
	//outfile.close();
}
