#include "stdafx.h"
#include "TabSheet.h"
#include "ApplicationInfoPage.h"

int CTabSheet::nPageIndex = 0;

CTabSheet::CTabSheet()
{
    _PageList.clear();
}

CTabSheet::~CTabSheet()
{
    _Clear();
}

bool CTabSheet::AddPage( LPCTSTR title, UINT resourceId )
{
    if ( MAXPAGE == _PageList.size())
        return false;

    if ( IsExist(title) )
        return false;

    CPage page;
    page.pDialog    = new CApplicationInfoPage();
    page.pDialog->Create( resourceId, this );

    page.strTitle   = title;
    page.nIndex     = nPageIndex++;
    _PageList.push_back( page );
    InsertItem( page.nIndex, page.strTitle.c_str() );

    return true;
}

CPage* CTabSheet::GetPage( const std::string& strTitle )
{
    PageListType::iterator it = _PageList.begin();
    for ( ; it!=_PageList.end(); ++it )
    {   
        if ( it->strTitle==strTitle )
        {
            return &(*it);   
        }
    }
    return NULL;
}

bool CTabSheet::AddPage( CPage& page )
{
    if ( IsExist(page.strTitle.c_str()) )
        return false;

    page.nIndex     = nPageIndex++;
    _PageList.push_back( page );
    InsertItem( page.nIndex, page.strTitle.c_str() );

    return true;
}

void CTabSheet::Show( int nItem)
{
    if ( _PageList.empty() )
        return;

    PageListType::iterator it = _PageList.begin();
    for ( ; it!=_PageList.end(); ++it )
    {   
        if ( it->nIndex==nItem )
        {
            it->pDialog->ShowWindow( SW_SHOW );            
            this->SetCurSel(it->nIndex);
        }
        else
        {
            it->pDialog->ShowWindow( SW_HIDE );            
        }
    }
}

void CTabSheet::Show( const std::string& strTitle )
{
    if ( strTitle.empty() )
        return;

    if ( _PageList.empty() )
        return;

    PageListType::iterator it = _PageList.begin();
    for ( int i=0 ; it!=_PageList.end(); ++it, ++i)
    {   
        if ( 0 == strcmp(it->strTitle.c_str(), strTitle.c_str() ) )
        {
            it->pDialog->ShowWindow( SW_SHOW );
            it->pDialog->SetWindowPos( &wndTop, _nX, _nY, _nXc, _nYc, SWP_SHOWWINDOW);
            this->SetCurSel(it->nIndex);
        }
        else
        {
            it->pDialog->ShowWindow( SW_HIDE );
            it->pDialog->SetWindowPos( &wndTop, _nX, _nY, _nXc, _nYc, SWP_HIDEWINDOW);
        }
    }
}

void CTabSheet::_Clear(void)
{
    PageListType::iterator it = _PageList.begin();
    for ( int i=0 ; it!=_PageList.end(); ++it, ++i)
    {
        if ( it->pDialog )
        {
            it->pDialog->DestroyWindow();
            delete it->pDialog;
        }
    }
    _PageList.clear();
}

bool CTabSheet::IsExist( LPCTSTR title )
{
    PageListType::iterator it = _PageList.begin();
    for (; it != _PageList.end(); ++it )
    {
        if ( 0 == strcmp( it->strTitle.c_str(), title) )
        {
            return true;
        }
    }

    return false;
}

void CTabSheet::ClearAllPage()
{
    _Clear();

    nPageIndex = 0;

    DeleteAllItems();
}

void CTabSheet::AdjustItemSize( void )
{
    GetClientRect( &_tabRect );
    GetItemRect( 0, &_itemRect );

    _nX = _itemRect.left;
    _nY = _itemRect.bottom + 1;
    _nXc = _tabRect.right - _itemRect.left - 2;
    _nYc = _tabRect.bottom - _nY - 2;
}

BEGIN_MESSAGE_MAP(CTabSheet, CTabCtrl)
END_MESSAGE_MAP()

