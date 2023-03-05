// HelpDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ApplicationManager.h"
#include "HelpDialog.h"


// CHelpDialog dialog

IMPLEMENT_DYNAMIC(CHelpDialog, CDialog)

CHelpDialog::CHelpDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpDialog::IDD, pParent)
{

}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialog)
END_MESSAGE_MAP()


// CHelpDialog message handlers
