#include "ShopMgr.h"
#include "GameTime.h"
#include "DataChunkMgr.h"
#include "FuncPerformanceLog.h"
//#include "TradeCenterConfig.h"
#include "ItemDetail.h"

#define DCSID_SHOPMGR		0x6b4b6f64, 0x644b4f30
#define DCID_SHOPMGR_DATA	0xb420fa4, 0x22eb15c6

CShopMgr* GetShopMgr()
{
	static CShopMgr shop;
	return &shop;
}

SShopItem* CShopMgr::SShop::GetItemById( int nId )
{
	for ( int n=0; n<nItemCount; n++)
	{
		if ( stItem[n].nId == nId )
		{
			return &stItem[n];
		}
	}
	return NULL;
}

bool CShopMgr::SShop::AddItem( const SShopItem* pItem )
{
	if (nItemCount < 0 || nItemCount >= eShopItemMax )
		return false;
	stItem[nItemCount++] = *pItem;
	return true;
}

void CShopMgr::SShop::RefreshCount()
{
	SShopItem* pItem;
	for ( int i=0; i<nItemCount; i++ )
	{
		pItem = &stItem[i];
		// 初始化数量
		if ( pItem->nCurCount == -1 )
		{
			//pItem->nCurCount = pItem->nMaxCount/3;
            pItem->nCurCount = pItem->nMaxCount;
		}
		// 补足数量
// 		else if ( pItem->nCurCount < pItem->nMinCount )
// 		{
// 			pItem->nCurCount = pItem->nMinCount;
// 		}
	}
}

void CShopMgr::SShop::RefreshPrice()
{
	SShopItem* pItem;
	for ( int i=0; i<nItemCount; i++ )
	{
		pItem = &stItem[i];
		if ( pItem->nCurCount <= 0 || pItem->nMaxCount <= 0 || pItem->nPerCount <= 0 )
			continue;
        if (pItem->nBasePrice <= 0)
        {
            ItemDefine::SItemCommon* item = GettheItemDetail().GetItemByID( pItem->nId );
            if(item == NULL)
            { continue; }
            pItem->nBasePrice = item->dwCost;                
            pItem->costType   = item->costType;
            pItem->costItemID  = item->costItemID;
        }

		// 收购价:商品出售价格/(0.75*(库存总量/系数+库存数量)/ 库存总量)
        //float f = 0.75f*
        //			(((float)pItem->nMaxCount/pItem->nX+pItem->nCurCount)/
        //			(float)pItem->nMaxCount);
          // 收购价:商品出售价格*20%
        //   float f = pItem->dwBuyPrice*0.2;
        //if ( f <= 0 )
        //{
        //	continue;
        //}
        ////最高收购价格不能大于原始价格的2倍
        //if (f < 0.51f)
        //{
        //	f = 0.51f;
        //}

		pItem->dwBuyPrice = pItem->nBasePrice*0.2;

		// 出售价格: 110% *(收购价格*商品数量+出售价格*库存数量)/(收购数量+库存数量/系数) 
		//pItem->dwSellPrice = 1.1f*
		//					((float)pItem->dwBuyPrice*pItem->nPerCount+
		//					pItem->nBasePrice*pItem->nCurCount)/
		//					((float)pItem->nPerCount+pItem->nCurCount/pItem->nX);
		// 出售价格: 130%*收购价格
		pItem->dwSellPrice = pItem->nBasePrice;/*1.3f * pItem->dwBuyPrice;*/
		//
		if( pItem->dwBuyPrice > pItem->dwSellPrice )
		{
			pItem->dwBuyPrice = pItem->dwSellPrice;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
CShopMgr::CShopMgr(void)
{
	m_dwTime = 0;
	LoadData();
}

CShopMgr::~CShopMgr(void)
{
}

bool CShopMgr::LoadData()
{
	CDataChunkMgr *pDataMgr = NULL;
	CAppDataChunk* pDataChunk =  NULL;
	pDataMgr = GetDataChunkMgr();
	pDataChunk = pDataMgr->GetAppDataChunk( CAppDataChunkClassID(DCID_SHOPMGR_DATA), 
											CAppDataChunkClassID(DCSID_SHOPMGR),
											0 );
	if ( !pDataChunk )
		return false;
	if( pDataChunk->m_dwLength == sizeof(m_stShopData) )
	{
		memcpy( &m_stShopData, pDataChunk->m_pbyData, sizeof(m_stShopData) );
	}
	return true;
}

bool CShopMgr::SaveData()
{
	CDataChunkMgr *pDataMgr = NULL;
	pDataMgr = GetDataChunkMgr();
	pDataMgr->RemoveAppDataChunk( CAppDataChunkClassID(DCID_SHOPMGR_DATA), 
									CAppDataChunkClassID(DCSID_SHOPMGR), 
									0 );
	pDataMgr->AddAppDataChunk( CAppDataChunkClassID(DCID_SHOPMGR_DATA), 
								CAppDataChunkClassID(DCSID_SHOPMGR), 
								0,
								sizeof(m_stShopData),
								&m_stShopData );
	return true;
}

void CShopMgr::Run()
{
	static DWORD dwLastTime = 0;
	if ( !GameTime::IsPassCurrentTime( dwLastTime, 60000 ) )
		return;
	dwLastTime = HQ_TimeGetTime();
	//
	m_dwTime++;
	SShop* pShop;
	for ( int n=0; n<m_stShopData.nShopCount; n++ )
	{
		pShop = &m_stShopData.stShop[n];
		if ( pShop->dwRefreshRate == 0)
			continue;
		if ( m_dwTime%pShop->dwRefreshRate == 0 )
		{
			pShop->RefreshCount();
		}
	}
    //theTradeCenterConfig.RefurbishCount(m_dwTime);
	//theShopCenterData.Refurbish( m_dwTime );
}

bool CShopMgr::AddShop( const SShop* shop )
{
	if (m_stShopData.nShopCount < 0 || m_stShopData.nShopCount >= SShopMgr::eMaxShopCount )
		return false;
	m_stShopData.stShop[m_stShopData.nShopCount++] = *shop;
	return true;
}

CShopMgr::SShop* CShopMgr::GetShopByIndex( unsigned int nIndex )
{
	if ( nIndex >= m_stShopData.nShopCount )
		return NULL;
	return &m_stShopData.stShop[nIndex];
}

CShopMgr::SShop* CShopMgr::GetShopById( int nId )
{
	for ( int n=0; n<m_stShopData.nShopCount; n++ )
	{
		if ( m_stShopData.stShop[n].nShopId == nId )
			return &m_stShopData.stShop[n];
	}
	return NULL;
}
