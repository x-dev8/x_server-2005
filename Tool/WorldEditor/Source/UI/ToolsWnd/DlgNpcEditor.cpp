// DlgNpcEditor.cpp : implementation file
//

#include "stdafx.h"
#include "WorldEditor.h"
#include "DlgNpcEditor.h"
#include "Edit/ToolManager.h"
#include "Edit/ToolNpc.h"
#include "ui/ToolsWnd/NpcPosUpdate.h"
#include "ui/ToolsWnd/DlgNpcString.h"
#include "tstring.h"
// CDlgNpcEditor dialog

IMPLEMENT_DYNAMIC(CDlgNpcEditor, CDialog)

CDlgNpcEditor::CDlgNpcEditor(CWnd* pParent /*=NULL*/)
	: ScrollableDialog(CDlgNpcEditor::IDD, pParent, SB_VERT)
{

}

CDlgNpcEditor::~CDlgNpcEditor()
{
}

void CDlgNpcEditor::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_NPCLIST, m_TreeNpc);
    DDX_Control(pDX, IDC_COMBO_POS_TYPE, m_ComType);
    DDX_Control(pDX, IDC_NPC_X, m_cNpcX);
    DDX_Control(pDX, IDC_NPC_Y, m_cNpcY);
    DDX_Control(pDX, IDC_NPC_Z, m_cNpcZ);
    DDX_Control(pDX, IDC_NPC_DIR, m_NpcDir);
    DDX_Control(pDX, IDC_NPC_SCALE, m_cNpcScale);
    DDX_Control(pDX, IDC_COMBO_MODID, m_ComModelID);
    DDX_Control(pDX, IDC_POS_X, m_findx);
    DDX_Control(pDX, IDC_POS_Y, m_findY);
    DDX_Control(pDX, IDC_COMBO_SHOW, m_ComShow);
    DDX_Control(pDX, IDC_SHOWLINE, m_chkLine);
    DDX_Control(pDX, IDC_TEXTMAP, m_textMap);
}


BEGIN_MESSAGE_MAP(CDlgNpcEditor, CDialog)
	ON_BN_CLICKED(IDC_RADIO_ADD_NPC, &CDlgNpcEditor::OnBnClickedRadioAddNpc)
	ON_BN_CLICKED(IDC_RADIO_NPC_EDIT, &CDlgNpcEditor::OnBnClickedRadioNpcEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_NPCLIST, &CDlgNpcEditor::OnNMDblclkNpclist)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTUPDAEPOS, &CDlgNpcEditor::OnBnClickedButupdaepos)
	ON_BN_CLICKED(IDC_BUTUPDATESTR, &CDlgNpcEditor::OnBnClickedButupdatestr)
	ON_BN_CLICKED(IDC_SAVEDATA, &CDlgNpcEditor::OnBnClickedSavedata)
	ON_CBN_SELCHANGE(IDC_COMBO_MODID, &CDlgNpcEditor::OnCbnSelchangeComboModid)
	ON_BN_CLICKED(IDC_RADIO_ADD_POS, &CDlgNpcEditor::OnBnClickedRadioAddPos)
	ON_BN_CLICKED(IDC_RADIO_NONE, &CDlgNpcEditor::OnBnClickedRadioNone)
	ON_BN_CLICKED(IDC_BUTDELPOI, &CDlgNpcEditor::OnBnClickedButdelpoi)
	ON_BN_CLICKED(IDC_BUTUPPOI, &CDlgNpcEditor::OnBnClickedButuppoi)
	ON_BN_CLICKED(IDC_SAVEPOS, &CDlgNpcEditor::OnBnClickedSavepos)
	ON_BN_CLICKED(IDC_UPDATENPC, &CDlgNpcEditor::OnBnClickedUpdatenpc)
	ON_BN_CLICKED(IDC_SHOWLINE, &CDlgNpcEditor::OnBnClickedShowline)
    ON_BN_CLICKED(IDC_COPYNPC, &CDlgNpcEditor::OnBnClickedCopynpc)
    ON_BN_CLICKED(IDC_DELNPC, &CDlgNpcEditor::OnBnClickedDelnpc)
    ON_BN_CLICKED(IDC_SAVE_STRING, &CDlgNpcEditor::OnSaveNpcString)
	ON_NOTIFY(TVN_SELCHANGED, IDC_NPCLIST, &CDlgNpcEditor::OnTvnSelchangedNpclist)

	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgNpcEditor message handlers
void	CDlgNpcEditor::SetActive( bool isModify/* = false */)
{
	InitData();
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_NPC );
	CToolNpc* toolNpc = GetToolNpc();

 	Assert( NULL != toolNpc );
 
 	toolNpc->Bind( this );
 	toolNpc->Reset();
}

CToolNpc*	CDlgNpcEditor::GetToolNpc()
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();

	return (CToolNpc*)( toolManager->GetActiveTool() );
}

void CDlgNpcEditor::InitData()
{
	LoadNpcInTheMap();
	LoadComBoxData();

	CheckDlgButton( IDC_RADIO_ADD_NPC, 1 );
	CheckDlgButton( IDC_RADIO_NPC_EDIT, 0 );
	CheckDlgButton( IDC_RADIO_ADD_POS, 0 );
	CheckDlgButton(IDC_RADIO_NONE,1);
}

void CDlgNpcEditor::LoadNpcInTheMap()
{
	m_TreeNpc.DeleteAllItems();
	CWorld* pWorld = SwGlobal::GetWorld();
	if(NULL == pWorld)
		return;

	CWorldTile* pTile = pWorld->GetWorldBuffer()->GetActiveTile();
	if(NULL == pTile)
		return;

	sInt32 mapID = pTile->GetMapId();

	NpcInfo::Npcs::iterator iter = theNpcInfo.npcs_.begin();
	NpcInfo::Npcs::iterator end  = theNpcInfo.npcs_.end();
	for (;iter != end;++iter)
	{
		if(iter->second.mapId == mapID)
		{
			char szWord[64];
			sprintf_s(szWord,sizeof(szWord),"%s(%d)",iter->second.name.c_str(),iter->second.id);
			m_TreeNpc.InsertItem(szWord);
		}
	}
}

void CDlgNpcEditor::LoadComBoxData()
{
    m_ComType.Clear();

	if(!InitComboxData("..\\Data\\Config\\Model.config","Model","Id",&m_ComModelID))
		::MessageBox(NULL,"Load Model.config failed!","Warnning",MB_OK);
}

const char*  CDlgNpcEditor::ParseString(CString& strData)
{
	int  nLeft = static_cast<int>(strData.Find('(')) + 1;
	int  nRight = static_cast<int>(strData.Find(')'));
	strData = strData.Right(strData.GetLength() - nLeft);
	strData = strData.Left(nRight - nLeft);

	return strData.GetBuffer();
}

void CDlgNpcEditor::OnBnClickedRadioAddNpc()
{
	CToolNpc* toolNpc = GetToolNpc();
	CheckDlgButton( IDC_RADIO_ADD_NPC, 1 );
	CheckDlgButton( IDC_RADIO_NPC_EDIT, 0 );
	toolNpc->SetOptMode(CToolNpc::optMode_NPC);

	OnBnClickedRadioNone();
}

void CDlgNpcEditor::OnBnClickedRadioNpcEdit()
{
	CToolNpc* toolNpc = GetToolNpc();
	CheckDlgButton( IDC_RADIO_ADD_NPC, 0 );
	CheckDlgButton( IDC_RADIO_NPC_EDIT, 1 );
	toolNpc->SetOptMode(CToolNpc::optMode_Pick);

	OnBnClickedRadioNone();
}

void CDlgNpcEditor::RefreshNpcPos(CNpcRes *res_)
{
	if(NULL == res_)
		return;

	CString strValue;
	float x,y,z,scale;
	int dir = 0;
	x = res_->GetPosX();
	strValue.Format(_T("%6.2f"),x);
	m_cNpcX.SetWindowText(strValue);

	y = res_->GetPosY();
	strValue.Format(_T("%6.2f"),y);
	m_cNpcY.SetWindowText(strValue);

	z = res_->GetPosZ();
	strValue.Format(_T("%6.2f"),z);
	m_cNpcZ.SetWindowText(strValue);

	dir = res_->GetDirection();
	strValue.Format(_T("%d"),dir);
	m_NpcDir.SetWindowText(strValue);

	scale = res_->GetBodyScale();
	strValue.Format(_T("%6.2f"),scale);
	m_cNpcScale.SetWindowText(strValue);
}

void CDlgNpcEditor::RefreshNpc(CNpcRes* res)
{
	if(NULL == res)
		return;

	CToolNpc* transport		= GetToolNpc();

	CNpcRes* npcRes = static_cast<CNpcRes*>(res);
	CWorldTile*		tile = CURRENTTILE;

	CString strValue;
	float x,y,z,scale;
	int dir = 0;
	x = npcRes->GetPosX();
	strValue.Format(_T("%6.2f"),x);
	m_cNpcX.SetWindowText(strValue);

	y = npcRes->GetPosY();
	strValue.Format(_T("%6.2f"),y);
	m_cNpcY.SetWindowText(strValue);

	z = npcRes->GetPosZ();
	strValue.Format(_T("%6.2f"),z);
	m_cNpcZ.SetWindowText(strValue);

	dir = npcRes->GetDirection();
	strValue.Format(_T("%d"),dir);
	m_NpcDir.SetWindowText(strValue);

	scale = npcRes->GetBodyScale();
	strValue.Format(_T("%6.2f"),scale);
	m_cNpcScale.SetWindowText(strValue);

	//设置模型ID
	char szWord[64];
	sprintf_s(szWord,sizeof(szWord),"%d",npcRes->GetModelId());

	int nCount = m_ComModelID.GetCount();
	for (int i = 0;i < nCount ;++i)
	{
		CString cItemText;
		m_ComModelID.GetLBText(i,cItemText);
		ParseString(cItemText);
		if(cItemText.Compare(szWord) == 0)
		{
			m_ComModelID.SetCurSel(i);
			break;
		}
	}

	//设置寻路点
	PositionInfo::Position *pPos = thePositionInfo.GetPositionById(npcRes->GetNpcId());
	if(pPos != NULL)
	{
		sprintf_s(szWord,sizeof(szWord),"%6.2f",pPos->x);
		m_findx.SetWindowText(szWord);

		sprintf_s(szWord,sizeof(szWord),"%6.2f",pPos->y);
		m_findY.SetWindowText(szWord);

		m_ComType.SetCurSel(pPos->type);
		m_ComShow.SetCurSel(pPos->isShow);
	}
	else
	{
		m_findx.SetWindowText("0.0");
		m_findY.SetWindowText("0.0");

		m_ComType.SetCurSel(0);
		m_ComShow.SetCurSel(0);
	}
}

int CDlgNpcEditor::GetNpcID(const HTREEITEM item_)
{
	assert(item_ != NULL);

	int id = -1;
	if(NULL == item_)
		return id;

	CString cItemText;
	cItemText = m_TreeNpc.GetItemText(item_);
	ParseString(cItemText);

	id = atoi(cItemText.GetBuffer());;

	return id;
}

void CDlgNpcEditor::SetSelectedNpc(int NpcID_)
{
	HTREEITEM hItem = m_TreeNpc.GetNextItem(TVI_ROOT, TVGN_CHILD);
	while(hItem != NULL)
	{
		if(GetNpcID(hItem) == NpcID_)
		{
			m_TreeNpc.SetFocus();
			m_TreeNpc.SelectItem(hItem);
			//m_TreeNpc.Select(hItem, TVGN_CARET | TVGN_FIRSTVISIBLE);
			//m_TreeNpc.SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
			m_TreeNpc.Select(hItem, TVGN_DROPHILITE);
			return;
		}

		hItem = m_TreeNpc.GetNextSiblingItem(hItem);
	}

}
void CDlgNpcEditor::OnNMDblclkNpclist(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR; 

	HTREEITEM selItem	= m_TreeNpc.GetSelectedItem();
	if( NULL == selItem )
		return;

	::OutputDebugString(m_TreeNpc.GetItemText(selItem));

	int npcID = GetNpcID(selItem);
	if(npcID < 0)
		return;

	CToolNpc* pToolNpc = GetToolNpc();
	if(pToolNpc != NULL)
	{
	    pToolNpc->SetCameraByNpcId(npcID);
		pToolNpc->SetSelectedNpc();
	}

	m_DlgNpcEdit.SetNpcId(npcID);
	m_DlgNpcEdit.InitGrapicsData(); //初始化图形数据
	m_DlgNpcEdit.SetMaxNpcInfo();   //设置最大NPC信息
	m_DlgNpcEdit.ShowWindow(SW_SHOW);
	m_DlgNpcEdit.EnableWindow();
}

int CDlgNpcEditor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!m_DlgNpcEdit.Create(CNpcEditDlg::IDD,this))
		return -1;

	m_DlgNpcEdit.ShowWindow(SW_HIDE);
	//m_DlgNpcEdit.EnableWindow();
	return 0;
}

void CDlgNpcEditor::OnBnClickedButupdaepos()
{
	CNpcPosUpdate dlg;
	dlg.DoModal();

}

void CDlgNpcEditor::OnBnClickedButupdatestr()
{
	CDlgNpcString dlg;
	dlg.DoModal();
}

void CDlgNpcEditor::OnBnClickedSavedata()
{
    string strPath = GetRootPath();
#ifdef _DEBUG
    strPath += "\\Data\\Config\\NpcTest.config";
	if( m_DlgNpcEdit.SaveConfig(strPath.c_str()) )
#else
    strPath += "\\Data\\Config\\Npc.config";
	if( m_DlgNpcEdit.SaveConfig(strPath.c_str()) )
#endif
		MessageBox("Npc.config保存成功!");
	else
		MessageBox("Npc.config 文件为只读，保存失败!");
}

void CDlgNpcEditor::InsertNewItem(CNpcRes* pRes)
{
	assert(pRes != NULL);
	if(NULL == pRes)
		return;

	const int npcId = pRes->GetNpcId();

	//应该保证在插入之前是有序的
	//有序插入，按npcid
	HTREEITEM hItem = m_TreeNpc.GetNextItem(TVI_ROOT, TVGN_CHILD);
	HTREEITEM hPreItem = m_TreeNpc.GetRootItem();
	while(hItem != NULL)
	{
		//绝不应该出现两个相等的情况
		if(GetNpcID(hItem) < npcId)
		{
			hPreItem = hItem;
			
		}
		else
		{
			break;
		}

		hItem = m_TreeNpc.GetNextSiblingItem(hItem);
	}

	char szWord[64];
	sprintf_s(szWord,sizeof(szWord),"%s(%d)",pRes->GetNpcName(), npcId);

	m_TreeNpc.InsertItem(szWord,TVI_ROOT, hPreItem);
}

void  CDlgNpcEditor::DelItem(CNpcRes* pRes)
{
	assert(pRes != NULL);

	HTREEITEM hItem;
	CString   cItemText;

	for (hItem = m_TreeNpc.GetRootItem();hItem != NULL; hItem = m_TreeNpc.GetNextVisibleItem(hItem))
	{
		cItemText = m_TreeNpc.GetItemText(hItem);
		ParseString(cItemText);

		if(pRes->GetNpcId() == atoi(cItemText.GetBuffer()))
		{
			m_TreeNpc.DeleteItem(hItem);
			return;
		}
	}
}

void CDlgNpcEditor::OnCbnSelchangeComboModid()
{
	CToolNpc* pTool = GetToolNpc();
	if(pTool != NULL)
	{
/*
		CNpcRes* currNpc = pTool->m_CurrNpc;
		if(currNpc != NULL)
		{
			currNpc->DetachModel(); //取消模型
			int nSel = m_ComModelID.GetCurSel();
			CString comText;
			m_ComModelID.GetLBText(nSel,comText);
			ParseString(comText);
			int modelId = atoi(comText);
			currNpc->SetModelId(modelId);  //设置模型ID
			NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(currNpc->GetNpcId());
			if(pNpc != NULL)
			{
				pNpc->modelId = modelId;
			}
			currNpc->AttachModel();
		}
*/
		int nSel = m_ComModelID.GetCurSel();
		CString comText;
		m_ComModelID.GetLBText(nSel,comText);
		ParseString(comText);
		int modelId = atoi(comText);

		pTool->DoChangeNpcModel(modelId);
	}
}


bool CDlgNpcEditor::InitComboxData(CString strData,const char *pszKeyWord,const char *pszAttribute,CComboBox* comBox)
{
	assert(comBox != NULL);
	assert(pszKeyWord != NULL);

	if(NULL == comBox || NULL == pszKeyWord)
		return false;

	MeXmlDocument xTiDoc;
	if(!xTiDoc.LoadFile(strData.GetBuffer(),1))
		return false;

	MeXmlElement *pSubElem = NULL;
	pSubElem = xTiDoc.FirstChildElement("Project");
	if(NULL == pSubElem)
		return false;

	pSubElem = pSubElem->FirstChildElement();
	if(NULL == pSubElem)
		return false;

	while(pSubElem != NULL)
	{
		//查询该节点下的子节点
		MeXmlElement *pTeamElem = pSubElem;
		for (;pTeamElem != NULL;pTeamElem = pTeamElem->FirstChildElement())
		{
			::OutputDebugString(pTeamElem->name());
			::OutputDebugString("\n");
			if(strcmp(pTeamElem->name(),pszKeyWord) == 0)
			{
				for (;pTeamElem != NULL;pTeamElem = pTeamElem->NextSiblingElement())
				{
					if(strcmp(pszKeyWord,"Map") == 0)
					{
						Common::_tstring strMap;
						strMap.fromUTF8(pTeamElem->Attribute("MapName"));
						if(strMap.length() > 0)
						{
							int mapId;
							pTeamElem->Attribute(pszAttribute,&mapId);
							char szWord[32];
							sprintf_s(szWord,sizeof(szWord),"(%d)",mapId);
							strMap += szWord;
							comBox->AddString(strMap.c_str());
						}
					}
					else if(strcmp(pszKeyWord,"Model") == 0)
					{
						Common::_tstring strModel;
						strModel.fromUTF8(pTeamElem->Attribute("Description"));
						int modelId;
						pTeamElem->Attribute(pszAttribute,&modelId);
						char szWord[32];
						sprintf_s(szWord,sizeof(szWord),"(%d)",modelId);
						strModel += szWord;
						comBox->AddString(strModel.c_str());
					}
					else
					{
						Common::_tstring strId;
						strId.fromUTF8(pTeamElem->Attribute(pszAttribute));
						if(strId.length() > 0)
							comBox->AddString(strId.c_str());
					}
				}
				return true;
			}
		}

		pSubElem = pSubElem->NextSiblingElement();   //查询同一层次节点
	}

	return false;
}

void CDlgNpcEditor::OnBnClickedRadioAddPos()
{
	CToolNpc* toolNpc = GetToolNpc();
	CheckDlgButton( IDC_RADIO_ADD_POS, 1 );
	CheckDlgButton(IDC_RADIO_NONE,0);
	toolNpc->m_npcPointer.SetMode(CToolNpc::NpcPointer::optMode_AddPointer);
}

void CDlgNpcEditor::OnBnClickedRadioNone()
{
	CToolNpc* toolNpc = GetToolNpc();
	CheckDlgButton( IDC_RADIO_ADD_POS, 0 );
	CheckDlgButton(IDC_RADIO_NONE,1);
	toolNpc->m_npcPointer.SetMode(CToolNpc::NpcPointer::optMode_None);
}

void CDlgNpcEditor::OnBnClickedButdelpoi()
{
	CToolNpc* pToolNpc = GetToolNpc();
	if(pToolNpc != NULL)
	{
		//pToolNpc->DelNpcPointer();
		pToolNpc->DoDeleteNpcPosition();
	}
}

void CDlgNpcEditor::OnBnClickedButuppoi()
{
	CToolNpc* pToolNpc = GetToolNpc();
	if(pToolNpc != NULL)
	{
		int nType = m_ComType.GetCurSel();
		int nShow = m_ComShow.GetCurSel();

		nType = m_ComType.GetCurSel();
		CString cWordText;
		
		m_findx.GetWindowText(cWordText);
		float x = atof(cWordText.GetBuffer());
		
		m_findY.GetWindowText(cWordText);
		float y = atof(cWordText.GetBuffer());

		//if(!pToolNpc->UpdateNpcPointer(nType,x,y,nShow))
		if(!pToolNpc->DoChangeNpcPosition(nType, x, y, nShow))
			MessageBox("Npc寻路坐标更新失败!");
	}
}

void CDlgNpcEditor::OnBnClickedSavepos()
{
	char szText[64];
#ifdef _DEBUG
	if(m_DlgNpcEdit.SavePositionConfig("..\\Data\\Config\\PositionTest.config"))
#else
	if(m_DlgNpcEdit.SavePositionConfig("..\\Data\\Config\\Position.config"))
#endif
		sprintf_s(szText,sizeof(szText),"%s","Position.config 保存成功!");
	else
		sprintf_s(szText,sizeof(szText),"%s","Position.config 为只读,保存失败!");

	MessageBox(szText);
}

void CDlgNpcEditor::OnBnClickedUpdatenpc()
{
	CString cText;

	m_cNpcX.GetWindowText(cText);
	float npcX = atof(cText.GetBuffer());

	m_cNpcY.GetWindowText(cText);
	float npcY = atof(cText.GetBuffer());

	m_cNpcZ.GetWindowText(cText);
	float npcZ = atof(cText.GetBuffer());

	m_NpcDir.GetWindowText(cText);
	int npcDir = atoi(cText.GetBuffer());

	m_cNpcScale.GetWindowText(cText);
	float  npcScale = atof(cText.GetBuffer());

	CToolNpc* pToolNpc = GetToolNpc();

/*
	if(pToolNpc != NULL && pToolNpc->m_CurrNpc != NULL)
	{
		pToolNpc->m_CurrNpc->SetPosX(npcX);
		pToolNpc->m_CurrNpc->SetPosY(npcY);
		pToolNpc->m_CurrNpc->SetPosZ(npcZ);
		pToolNpc->m_CurrNpc->SetDirection(npcDir);
		pToolNpc->m_CurrNpc->SetScale(npcScale);

		NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(pToolNpc->m_CurrNpc->GetNpcId());
		if(pNpc != NULL)
		{
			pNpc->x = npcX;
			pNpc->y = npcY;
			pNpc->z = npcZ;
			pNpc->direction = npcDir;
			pNpc->bodyScale = npcScale;
		}
	}
*/

	if(pToolNpc)
	{
		pToolNpc->DoChangeNpcPos(npcX, npcY, npcZ, npcDir, npcScale);
	}
}

void CDlgNpcEditor::OnBnClickedShowline()
{
	CToolNpc* pToolNpc = GetToolNpc();
	if(pToolNpc != NULL)
	{
		if(BST_CHECKED == m_chkLine.GetCheck())
		    pToolNpc->ShowLine(true);
		else
			pToolNpc->ShowLine(false);
	}
}

LRESULT CDlgNpcEditor::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_ENABLE:
		::OutputDebugString("FF");
		break;
	}
	return CDialog::WindowProc(message,wParam,lParam);
}

bool CDlgNpcEditor::CloneNpc(int oldMapID,int newMapID)
{
    NpcInfo::NpcsIter iter = theNpcInfo.npcs_.begin();
    NpcInfo::NpcsIter end  = theNpcInfo.npcs_.end();
    for (;iter != end;++iter)
    {
        if(iter->second.mapId == oldMapID)
        {
            NpcInfo::Npc npc;
            npc       = iter->second;
            npc.mapId = newMapID;

            theNpcInfo.AddNpc(npc);
        }
    }
    return false;
}

bool CDlgNpcEditor::DeleteNpc(int mapID)
{
    NpcInfo::NpcsIter iter = theNpcInfo.npcs_.begin();
    NpcInfo::NpcsIter end  = theNpcInfo.npcs_.end();
    for (;iter != end;++iter)
    {
        if(iter->second.mapId == mapID)
            iter = theNpcInfo.npcs_.erase(iter);
    }
    return true;
}

void CDlgNpcEditor::OnBnClickedCopynpc()
{
    CString str;
    int newMapID = 0;
    
    m_textMap.GetWindowText(str);
    if(sscanf_s(str.GetBuffer(0),"%d",&newMapID) != 1)
        return;

    if(CURRENTTILE)
    {
        CloneNpc(CURRENTTILE->GetMapId(),newMapID);
        CloneNpcPosition(CURRENTTILE->GetMapId(),newMapID);

        MessageBox("Copy success!");
    }    
}

void CDlgNpcEditor::OnBnClickedDelnpc()
{
    CString str;
    m_textMap.GetWindowText(str);
    int nMapID = 0;
    if(sscanf_s(str.GetBuffer(0),"%d",&nMapID) != 1)
        return;

    if(CURRENTTILE)
    {
        DeleteNpc(nMapID);
        DeleteNpcPosition(nMapID);
        MessageBox("Delete success!");
    }
}

void  CDlgNpcEditor::CloneNpcPosition(int nOldMapID,int nNewMapID)
{
    PositionInfo::PositionsIter iter = thePositionInfo.positions_.begin();
    PositionInfo::PositionsIter end  = thePositionInfo.positions_.end();

    for (;iter != end;++iter)
    {
        if(iter->second.mapId == nOldMapID)
        {
            PositionInfo::Position pos;
            pos = iter->second;
            pos.mapId = nNewMapID;
            thePositionInfo.positions_.insert(make_pair(pos.id,pos));
        }
    }
}

void CDlgNpcEditor::DeleteNpcPosition(int mapID)
{
    PositionInfo::PositionsIter iter = thePositionInfo.positions_.begin();
    PositionInfo::PositionsIter end  = thePositionInfo.positions_.end();

    for (;iter != end;++iter)
    {
        if(iter->second.mapId == mapID)
            iter = thePositionInfo.positions_.erase(iter);
    }
}
void CDlgNpcEditor::OnSaveNpcString()
{
    // TODO: Add your control notification handler code here
#ifdef _DEBUG
    if(theNpcStringForMenu.SaveConfigForMenu("..\\Data\\Config\\NpcTest.string"))
        MessageBox("NpcTest.string保存成功!");
    else
        MessageBox("NpcTest.string 文件保存失败,请检查文件属性!");
#else
    if(theNpcStringForMenu.SaveConfigForMenu("..\\Data\\Config\\Npc.string"))

        MessageBox("Npc.string保存成功!");
    else
        MessageBox("Npc.string 文件保存失败,请检查文件属性!");
#endif
}
void CDlgNpcEditor::OnTvnSelchangedNpclist(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR; 

/*
	HTREEITEM selItem	= m_TreeNpc.GetSelectedItem();
	if( NULL == selItem )
		return;

	::OutputDebugString(m_TreeNpc.GetItemText(selItem));

	int npcID = GetNpcID(selItem);
	if(npcID < 0)
		return;

	CToolNpc* pToolNpc = GetToolNpc();
	if(pToolNpc != NULL)
	{
		pToolNpc->SetCameraByNpcId(npcID);
		pToolNpc->SetSelectedNpc();
	}
*/

	*pResult = 0;
}

void CDlgNpcEditor::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	switch (nSBCode)
	{
	case SB_LINEUP:
		Scroll_LineUpDown(-10);
		break;

	case SB_LINEDOWN:
		Scroll_LineUpDown(10);
		break;

	case SB_THUMBTRACK:
		Scroll_To(nPos);
		break;
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDlgNpcEditor::OnSize(UINT nType, int cx, int cy)
{
	ScrollableDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CRect rcClient;
	GetClientRect(&rcClient);
	Scroll_Setup(820, rcClient.Height());
}