// DlgNpcString.cpp : implementation file
//

#include "stdafx.h"
#include "DlgNpcString.h"
#include "..\\..\\Edit\NpcString.h"

// CDlgNpcString dialog

IMPLEMENT_DYNAMIC(CDlgNpcString, CDialog)

CDlgNpcString::CDlgNpcString(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNpcString::IDD, pParent)
	, m_StringID(0)
	, m_strTalk(_T(""))
{

}

CDlgNpcString::~CDlgNpcString()
{
}

void CDlgNpcString::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREESTRINGID, m_treeCtrl);
	DDX_Text(pDX, IDC_STRINGID, m_StringID);
	DDX_Text(pDX, IDC_STRING, m_strTalk);
}


BEGIN_MESSAGE_MAP(CDlgNpcString, CDialog)
	ON_BN_CLICKED(IDC_LOADSTRING, &CDlgNpcString::OnBnClickedLoadstring)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREESTRINGID, &CDlgNpcString::OnTvnSelchangedTreestringid)
	ON_BN_CLICKED(IDC_STRINGADD, &CDlgNpcString::OnBnClickedStringadd)
	ON_BN_CLICKED(IDC_STRINGDEL, &CDlgNpcString::OnBnClickedStringdel)
	ON_BN_CLICKED(IDC_STRINGSAVE, &CDlgNpcString::OnBnClickedStringsave)
END_MESSAGE_MAP()


// CDlgNpcString message handlers

void CDlgNpcString::OnBnClickedLoadstring()
{
	m_treeCtrl.DeleteAllItems();

	CFileDialog dlgFile(true);
	CString fileName;
	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(1024);
	dlgFile.GetOFN().nMaxFile  = 1024;
	dlgFile.GetOFN().lpstrFilter = "Config(*.config)\0*.config\0All File(*.*)\0*.*\0\0";

	INT_PTR hr = dlgFile.DoModal();
	if(hr == IDCANCEL)
		return;


	if(theNpcString.LoadConfig(fileName.GetBuffer()))
	{
		InitTreeCtrlData();
	}

	fileName.ReleaseBuffer();	
}

bool CDlgNpcString::InitTreeCtrlData()
{
	//if(theNpcString.LoadConfig("..\\Data\\Config\\Npc.string"))
	{
		CNpcString::NPCTALKSET::iterator iter = theNpcString.m_TalkSet.begin();
		CNpcString::NPCTALKSET::iterator iterEnd = theNpcString.m_TalkSet.end();

		for (;iter != iterEnd;++iter)
		{
			char szWord[32];
			sprintf_s(szWord,sizeof(szWord),"%d",iter->second.m_Id);
			m_treeCtrl.InsertItem(szWord);
		}		
	}
	return true;
}
void CDlgNpcString::OnTvnSelchangedTreestringid(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	CString  cItemText = m_treeCtrl.GetItemText(hItem);

	int nTalkID = atoi(cItemText.GetBuffer());

	CNpcString::npcTalk* pTalkDate = theNpcString.GetDataByID(nTalkID);
	SetStringProtery(*pTalkDate);
}


void CDlgNpcString::SetStringProtery(CNpcString::npcTalk &cNpcTalk)
{
	m_StringID = cNpcTalk.m_Id;
	m_strTalk = cNpcTalk.m_strTalk.c_str();

	UpdateData(false);
}

bool CDlgNpcString::GetStringProtery(CNpcString::npcTalk &cNpcTalk)
{
	UpdateData();
	if(m_StringID == 0)
	{
		::MessageBox(NULL,"StringID 为空!","Warnning",MB_OK);
		return false;
	}
	cNpcTalk.m_Id = m_StringID;
	cNpcTalk.m_strTalk = m_strTalk.GetBuffer();
	return true;
}

void CDlgNpcString::OnBnClickedStringadd()
{
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	CString   cItemText = m_treeCtrl.GetItemText(hItem);
	if(cItemText.IsEmpty())
	{
		::MessageBox(NULL,"请选择一个节点!","Warnning",MB_OK);
		return;	
	}

	CNpcString::npcTalk cNpcTalk;
	GetStringProtery(cNpcTalk);

	CNpcString::npcTalk* pNpcTalk = NULL;
	pNpcTalk = theNpcString.GetDataByID(cNpcTalk.m_Id);
	if(pNpcTalk != NULL)
	{
		::MessageBox(NULL,"StringID重复!","Warnning",MB_OK);
		return;
	}


	theNpcString.InsertData(cNpcTalk);

	char szWord[32];
	sprintf_s(szWord,sizeof(szWord),"%d",cNpcTalk.m_Id);
	m_treeCtrl.InsertItem(szWord,TVI_ROOT,hItem);
}

void CDlgNpcString::OnBnClickedStringdel()
{
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	CString   cItemText = m_treeCtrl.GetItemText(hItem);

	if(cItemText.IsEmpty())
	{
		::MessageBox(NULL,"请选择一个节点!","Warnning",MB_OK);
		return;
	}

	int nValue = 0;
	if(_sntscanf_s(cItemText.GetBuffer(),cItemText.GetLength(),"%d",&nValue) != 1)
	{
		::MessageBox(NULL,"删除失败!","Warnning",MB_OK);
		return;
	}
	
	theNpcString.DelData(nValue);
	m_treeCtrl.DeleteItem(m_treeCtrl.GetSelectedItem());
}

void CDlgNpcString::OnBnClickedStringsave()
{
	if(theNpcString.GetCount() <= 0)
		return;

// 	CFileDialog dlgFile(false);
// 	CString fileName;
// 	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(1024);
// 	dlgFile.GetOFN().nMaxFile  = 1024;
// 
// 	INT_PTR hr = dlgFile.DoModal();
// 	if(hr == IDCANCEL)
// 		return;

	//if(!theNpcString.SaveConfig(fileName.GetBuffer()))

	CNpcString::npcTalk npcTalk;
	if(GetStringProtery(npcTalk))
	{
		CNpcString::npcTalk* pNpcTalk = NULL;
		pNpcTalk = theNpcString.GetDataByID(npcTalk.m_Id);
		if(pNpcTalk != NULL)
		{
			pNpcTalk->m_Id = npcTalk.m_Id;
			pNpcTalk->m_strTalk = npcTalk.m_strTalk;
		}

        CString DirPath = GetRootPath();
        CString FullPath = DirPath + "\\Data\\Config\\Npc.string";
		if( theNpcString.SaveConfig(FullPath) )
		{
			char szWord[32];
			sprintf_s(szWord,sizeof(szWord),"%d 保存成功!",npcTalk.m_Id);
			::MessageBox(NULL,szWord,"Warnning",MB_OK);
		}
        else
        {
            char szTmp[50];
            sprintf_s(szTmp, sizeof(szTmp) - 1, "StringID=%d 保存失败，请检查！", npcTalk.m_Id);
            ::MessageBox(NULL, szTmp, _T("Warning"), MB_OK);
        }
	}

	//fileName.ReleaseBuffer();
}

void CDlgNpcString::OnClose()
{
   //OutputDebugStr(TEXT("FF"));
   OutputDebugString("FF");
}

LRESULT CDlgNpcString::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_ENABLE:
		::OutputDebugString("FF");
		break;
	}
	return CDialog::WindowProc(message,wParam,lParam);
}

void CDlgNpcString::OnCancel()
{
	m_treeCtrl.DeleteAllItems();
	m_StringID = 0;
	m_strTalk = "";
	
	theNpcString.Clear();
	UpdateData(false);
	CDialog::OnCancel();
}