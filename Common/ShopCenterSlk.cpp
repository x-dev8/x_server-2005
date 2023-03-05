#include "ShopCenterSlk.h"
// #include "Tinyxml\tinyxml.h"
#include "application_config.h"
#include "tstring.h"
#include "SlkReader.h"
#include <assert.h>

#include "FuncPerformanceLog.h"

CShopCenterData theShopCenterData;

CShopCenterData::CShopCenterData()
{
    //10. Min
    dwRefurbishTime = 1000*60*10;
    dwSrcTime = 0;
}

CShopCenterData::~CShopCenterData()
{
}

INT					CShopCenterData::GetShelfItemSize(INT nShelf)
{
    if( nShelf < 0 || nShelf >= eMax_Shelf )
        return 0;

    return ItemShelfData[nShelf].size();
}

CShopCenterNode*	CShopCenterData::GetShelfItemNode( INT nShelf, INT nIdx )
{
    if( nShelf < 0 || nShelf >= eMax_Shelf )
        return NULL;

    if( nIdx < 0 || nIdx >= ItemShelfData[nShelf].size() )
        return NULL;

    return &ItemShelfData[nShelf][nIdx];
}

CShopCenterNode*	CShopCenterData::GetItemNode( INT nIdx )
{
    if( nIdx < 0 || nIdx >= ItemData.size() )
    {
        return NULL;
    }

    return &ItemData[nIdx];
}

BOOL				CShopCenterData::Refurbish( DWORD dwTime )
{
    //dwSrcTime = HQ_TimeGetTime();
    for( int i=0; i< GetItemSize(); i++ )
    {
        CShopCenterNode* pNode = GetItemNode(i);
        if( pNode )
        {
            if ( pNode->Refurbish == 0 )
                continue;
            if ( dwTime%pNode->Refurbish == 0 )
            {
                pNode->CurNumber = pNode->Number;
            }
        }
    }
    return TRUE;

}

//////////////////////////////////////////////////////////////////////////
//取得的是货价上的
CShopCenterNode*	CShopCenterData::GetItemNodeFromID( unsigned short Id )
{
    //for( int i=0; i< GetItemSize(); i++ )
    //{
    //	CShopCenterNode* pNode = GetItemNode(i);
    //	if( pNode && pNode->ItemID == Id )
    //	{
    //		return pNode;
    //	}
    //}

    for( int i=0; i< eMax_Shelf; i++ )
    {
        INT nShelfSize = GetShelfItemSize( i );
        for( int nLoop = 0; nLoop < nShelfSize; nLoop++ )
        {
            CShopCenterNode* pNode = GetShelfItemNode( i, nLoop );
            if( pNode && pNode->ItemID == Id )
            {
                return pNode;
            }
        }
    }
    return NULL;
}


bool CShopCenterData::LoadFromSlk( char* szFileName )
{
    CSlkReader reader;
    if( !reader.ReadFromFile( szFileName ) )
    {
        return false;
    }
    int nLine = 3;
    int	nIndex = 0;
    CSlkReader::SField* pField = NULL;
    int iRet;
    static int line = 0;
    int iValue = 0;
    float fValues = 0.0f;


    while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( nLine++ ) ) ) 
    {
        if( CSlkReader::ret_nothisline == iRet )
        {
            continue;
        }

        CShopCenterNode ItemNode;

        if (reader.GetIntFieldByName("id",iValue))	
        {
            ItemNode.ItemID = iValue;
        }
        else
        {

        }

        if (reader.GetStringFieldByName("ItemName",ItemNode.ItemName ))	//
        {

        }

        if (reader.GetIntFieldByName("Shelf",iValue))	//
        {
            ItemNode.ShelfType = iValue;
        }

        if (reader.GetIntFieldByName("Price",iValue))	//
        {
            ItemNode.Price = iValue;
        }

        if (reader.GetIntFieldByName("VIPPrice",iValue))	//
        {
            ItemNode.VIPPrice = iValue;
        }

        if (reader.GetIntFieldByName("Price2",iValue))	//
        {
            ItemNode.Price2 = iValue;
        }

        if (reader.GetIntFieldByName("VIPPrice2",iValue))	//
        {
            ItemNode.VIPPrice2 = iValue;
        }

        if (reader.GetFloatFieldByName("Agio",fValues))	//
        {
            ItemNode.Agio = fValues;
        }

        if (reader.GetIntFieldByName("Number",iValue))	//
        {
            ItemNode.CurNumber = iValue;
            ItemNode.Number = iValue;
        }

        if (reader.GetIntFieldByName("Refurbish",iValue))	//
        {
            ItemNode.Refurbish = iValue;
        }
        if (reader.GetStringFieldByName("Description",ItemNode.Description))	//
        {
        }
        if (reader.GetStringFieldByName("ImagePath",ItemNode.ImagePath))	//
        {
        }
        if (reader.GetIntFieldByName("Hot",iValue))	//
        {
            ItemNode.bHot = iValue;
        }

        ItemData.push_back( ItemNode );

        if( ItemNode.ShelfType >= 0 && ItemNode.ShelfType< eMax_Shelf )
            ItemShelfData[ItemNode.ShelfType].push_back( ItemNode );
    }

    return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
