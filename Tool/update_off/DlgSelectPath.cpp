// DlgSelectPath.cpp : implementation file
//

#include "stdafx.h"
#include "update.h"
#include "DlgSelectPath.h"


// CDlgSelectPath dialog

IMPLEMENT_DYNAMIC(CDlgSelectPath, CDialog)

CDlgSelectPath::CDlgSelectPath(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectPath::IDD, pParent)
{

}

CDlgSelectPath::~CDlgSelectPath()
{
}

void CDlgSelectPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSelectPath, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDlgSelectPath::OnNMDblclkList1)
END_MESSAGE_MAP()


// CDlgSelectPath message handlers

BOOL CDlgSelectPath::OnInitDialog()
{
	CDialog::OnInitDialog();
	((CListCtrl*)GetDlgItem(IDC_LIST1))->InsertColumn(0,_T("���"),0,40);
	((CListCtrl*)GetDlgItem(IDC_LIST1))->InsertColumn(1,_T("·��"),0,150);
	// TODO:  Add extra initialization here
	((CListCtrl*)GetDlgItem(IDC_LIST1))->SetExtendedStyle(((CListCtrl*)GetDlgItem(IDC_LIST1))->GetExtendedStyle()|LVS_EX_FULLROWSELECT); 
	SetWindowText("ѡ�����·��");	
	HKEY Key;
	CString sKeyPath;
	sKeyPath="Software\\GameSoft\\Path";
	if(RegOpenKey(HKEY_CURRENT_USER,sKeyPath,&Key)!=0 &&RegOpenKey(HKEY_CURRENT_USER,sKeyPath,&Key)!=ERROR_SUCCESS)
	{
	/*	//��ע����м�¼�����õĴ���
		::RegCreateKey(HKEY_CURRENT_USER,sKeyPath,&Key);
		::RegSetValueEx(Key,"TryTime",0,REG_SZ,(unsigned char*)"5",1);
		::RegCloseKey(Key);
    */
	}
	else //�Ѿ�����ע����Ϣ
	{
		BOOL   bResult   =   TRUE; 
		DWORD   lResult; 

		//�_ʼö�e�Iֵ 
		for   (int i   =   0;   ;i++)   //���g���,�]���M��iֵ�ı��^ 
		{ 
			TCHAR   szValueName[_MAX_PATH   +   1]; 
			DWORD   dwValueName   =   sizeof(szValueName); 
			DWORD   dwValueType; 
			lResult   =   RegEnumValue(Key,i,szValueName,&dwValueName, 
				NULL,&dwValueType,NULL,NULL); 
			if   (lResult   !=   ERROR_SUCCESS)   //ͨ�^����˳�ѭ�h 
			{ 
				if   (lResult   !=   ERROR_NO_MORE_ITEMS)   bResult   =   FALSE; 
				break; 
			} 
			szValueName[dwValueName]   =   (TCHAR)   '\n '; 
			//����ɹ�,�t�����@ʾ���� 
			int nIndex = ((CListCtrl*)GetDlgItem(IDC_LIST1))->GetItemCount();
			CString id;
			id.Format("%d",nIndex);
			((CListCtrl*)GetDlgItem(IDC_LIST1))->InsertItem(nIndex,id); 
			((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nIndex,1,szValueName);
		} 	
		::RegCloseKey(Key);			
	}			
	if(((CListCtrl*)GetDlgItem(IDC_LIST1))->GetItemCount()<1)
    ::SendMessage(this->m_hWnd,WM_CLOSE,NULL,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelectPath::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		selPath=((CListCtrl*)GetDlgItem(IDC_LIST1))->GetItemText(pNMListView->iItem,pNMListView->iSubItem);
		::SendMessage(this->m_hWnd,WM_CLOSE,NULL,0);
		// TODO: Add your control notification handler code here
	}
	*pResult = 0;
}
