#pragma once

#include <string>
#include <vector>
#include "ApplicationInfoPage.h"

struct CPage 
{
    CApplicationInfoPage* pDialog;
    std::string           strTitle;
    int                   nIndex;
};

class CTabSheet : public CTabCtrl
{
public:
    enum
    {
        MAXPAGE = 100,
    };

    static int nPageIndex;

public:
    CTabSheet();

    ~CTabSheet();

    bool AddPage( LPCTSTR title, UINT resourceId );

    bool AddPage( CPage& page );

    CPage* GetPage( const std::string& strTitle);

    void Show( int nItem );

    void Show( const std::string& strTitle);

    void AdjustItemSize( void );

    bool IsExist( LPCTSTR title );

    void ClearAllPage();

    DECLARE_MESSAGE_MAP()

private:
    void _Clear(void);

private:
    typedef std::vector<CPage> PageListType;
    PageListType _PageList;

    CRect _tabRect, _itemRect;
    int _nX, _nY, _nXc, _nYc;
};
