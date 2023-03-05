// NpcPosUpdate.cpp : implementation file
//

#include "stdafx.h"
#include "NpcPosUpdate.h"
#include "NpcInfo.h"
#include "NpcEditDlg.h"

// CNpcPosUpdate dialog

IMPLEMENT_DYNAMIC(CNpcPosUpdate, CDialog)

CNpcPosUpdate::CNpcPosUpdate(CWnd* pParent /*=NULL*/)
	: CDialog(CNpcPosUpdate::IDD, pParent)
	, m_mapID(0)
	, m_fXPos(0)
	, m_fYPos(0)
{

}

CNpcPosUpdate::~CNpcPosUpdate()
{
}

void CNpcPosUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_mapID);
	DDV_MinMaxInt(pDX, m_mapID, 0, 999);
	DDX_Text(pDX, IDC_EDIT2, m_fXPos);
	DDX_Text(pDX, IDC_EDIT3, m_fYPos);
}


BEGIN_MESSAGE_MAP(CNpcPosUpdate, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CNpcPosUpdate::OnBnClickedButton1)
END_MESSAGE_MAP()


// CNpcPosUpdate message handlers

void CNpcPosUpdate::OnBnClickedButton1()
{
	if(theNpcInfo.GetNpcCount() <= 0)
	{
		::MessageBox(NULL,"Npc.config未载入!","Warnning",MB_OK);
		return;
	}
	UpdateData();

	if(m_fXPos == 0 &&m_fYPos == 0)
	{
		::MessageBox(NULL,"坐标x和坐标y都为0，不需要更新!","Warnning",MB_OK);
		return;
	}
	int nCount = theNpcInfo.GetNpcCount();
	if(nCount <=0)
	{
		::MessageBox(NULL,"Npc.config未加载,无法更新!","Warnning",MB_OK);
		return;
	}

	NpcInfo::Npcs::iterator iter = theNpcInfo.npcs_.begin();
	NpcInfo::Npcs::iterator end  = theNpcInfo.npcs_.end();

	for ( ; iter != end; ++iter)
	{
		if(iter->second.mapId == m_mapID)
		{
			iter->second.x -= m_fXPos;
			iter->second.y -= m_fYPos;
		}
	}
	//清空数据
	m_mapID = 0;
	m_fXPos = 0;
	m_fYPos = 0;
	UpdateData(false);
	::MessageBox(NULL,"update complete!","Warnning",MB_OK);
}
