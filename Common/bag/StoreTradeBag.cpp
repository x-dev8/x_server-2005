//
//#include "storetradebag.h"
//#include "..\..\common\ItemDetail.h"
//
//
//CStoreTradeBag::CStoreTradeBag( )
//{
//	m_pStoreItem = NULL;
//	m_pTradeItem = NULL;
//	m_iStoreBagSize = 0;
//	m_iTradeBagSize = 0;
//
//	int iLoop;
//	for( iLoop=0;iLoop<m_iStoreBagSize;iLoop++ )
//	{
//		m_pStoreItem->itemStore[iLoop].ustItemID = ErrorUnsignedShortID;
//	}
//	for( iLoop=0;iLoop<m_iTradeBagSize;iLoop++ )
//	{
//		m_pTradeItem->itemTrade[iLoop].ustItemID = ErrorUnsignedShortID;
//	}
//}
//
//CStoreTradeBag::~CStoreTradeBag( )
//{
//
//}
//
////初始化指针
//bool CStoreTradeBag::CreateFromData( SCharStore *pStoreItem,
//					 SCharTrade *pTradeItem,
//					 int iStoreBagSize, int iTradeBagSize )
//{
//	m_pStoreItem = pStoreItem;
//	m_pTradeItem = pTradeItem;
//	m_iStoreBagSize = iStoreBagSize;
//	m_iTradeBagSize = iTradeBagSize;
//
//	return true;
//}
//
////找出指定背包的空闲位置
//int CStoreTradeBag::FindNullItemOffset( short stWhichBag )
//{
//	SCharItem *pItem;
//	pItem = GetBagPointByType( stWhichBag );
//	if(!pItem)
//		return -1;
//
//	int iLoopSize = 0;
//	iLoopSize = GetBagSizeByType( stWhichBag );
//
//	int iLoop;
//	for( iLoop=0;iLoop<iLoopSize;iLoop++ )
//	{
//		if( ErrorUnsignedShortID==pItem[iLoop].ustItemID )
//			return iLoop;
//	}
//	return -1;
//}
//
////根据背包的类型取得指针
//SCharItem* CStoreTradeBag::GetBagPointByType( short stWhichBag )
//{
//
//	//if( stWhichBag!=BagTypeStore&&stWhichBag!=BagTypeTrade )
//	//	return NULL;
//
//	//switch(stWhichBag)
//	//{
//	//case BagTypeStore:
//	//	return m_pStoreItem->itemStore;
//	//	break;
//	//case BagTypeTrade:
//	//	return m_pTradeItem->itemTrade;
//	//	break;
//	//default:
//	//	break;
//	//}
//
//	return NULL;
//}
//
////根据背包的类型取得最大数目
//short CStoreTradeBag::GetBagSizeByType( short stWhichBag )
//{
//
//	//if(stWhichBag==BagTypeStore)
//	//	return m_iStoreBagSize;
//
//	//if(stWhichBag==BagTypeTrade)
//	//	return m_iTradeBagSize;
//
//	return 0;
//}
//
////放入物品
//bool CStoreTradeBag::PushItem( short stWhichBag, SCharItem &item, short stIndex )
//{
//	ItemDefine::SItemCommon *pItemDetail = 
//		theItemDetail.GetItemByID( item.ustItemID );
//	if( !pItemDetail )
//		return false;
//	
//	SCharItem *pItem;
//	pItem = GetBagPointByType( stWhichBag );
//	if(!pItem)
//		return false;
//
//	int iOffset = stIndex;
//	if( iOffset==-1 )
//	{
//		iOffset = FindNullItemOffset( stWhichBag );
//		if( -1==iOffset )
//			return false;
//	}
//
//	pItem += iOffset;
//	*pItem = item;
//	return true;
//}
//
////取出物品
//bool CStoreTradeBag::PopItem( short stWhichBag, SCharItem &item )
//{
//	//********************暂时交易背包里的物品,每个占单独一个********************
//	//pItem->ustItemID = ErrorUnsignedShortID;
//	//***************************************************************************
//
//	SCharItem *pItem;
//	pItem = GetBagPointByType( stWhichBag );
//	if(!pItem)
//		return false;
//
//	int iLoopSize = 0;
//	iLoopSize = GetBagSizeByType( stWhichBag );
//
//	int iLoop;
//	for( iLoop=0; iLoop<iLoopSize; iLoop++, pItem++ )
//	{
//		if( pItem->ustItemID == item.ustItemID
//		&&  pItem->extdata.equipdata.special[ 0 ]==item.extdata.equipdata.special[ 0 ]
//		&&  pItem->extdata.equipdata.special[ 1 ]==item.extdata.equipdata.special[ 1 ]
//		&&  pItem->extdata.equipdata.special[ 2 ]==item.extdata.equipdata.special[ 2 ]
//		&&  pItem->extdata.equipdata.special[ 3 ]==item.extdata.equipdata.special[ 3 ]
//		&&  pItem->extdata.equipdata.special[ 4 ]==item.extdata.equipdata.special[ 4 ]
//		&&  pItem->extdata.equipdata.special[ 5 ] ==item.extdata.equipdata.special[ 5 ]
//		&&  pItem->extdata.equipdata.special[ 6 ] ==item.extdata.equipdata.special[ 6 ])
//		{
//			pItem->ustItemID = ErrorUnsignedShortID;
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool CStoreTradeBag::PopItem( short stWhichBag, short stIndex )
//{
//	SCharItem *pItem;
//	pItem = GetBagPointByType( stWhichBag );
//	if(!pItem)
//		return false;
//
//	pItem[stIndex].ustItemID = ErrorUnsignedShortID;
//	return true;
//}
//
////放入金钱
//bool CStoreTradeBag::PushMoney( short stWhichBag, DWORD dwMoney )
//{
//	//if( stWhichBag!=BagTypeStore&&stWhichBag!=BagTypeTrade )
//	//	return false;
//	//	
//	//switch(stWhichBag)
//	//{
//	//case BagTypeStore:
//	//	m_pStoreItem->dwMoney = dwMoney;
//	//	break;
//
//	//case BagTypeTrade:
//	//	m_pTradeItem->dwMoney = dwMoney;
//	//	break;
//
//	//default:
//	//	break;
//	//}
//	//
//	return true;
//}
//
////取出金钱
//bool CStoreTradeBag::PopMoney( short stWhichBag, DWORD dwMoney )
//{
//
//	//if( stWhichBag!=BagTypeStore&&stWhichBag!=BagTypeTrade )
//	//	return false;
//
//	//switch(stWhichBag)
//	//{
//	//case BagTypeStore:
//	//	m_pStoreItem->dwMoney -= dwMoney;
//	//	if(m_pStoreItem->dwMoney<0)
//	//		m_pStoreItem->dwMoney = 0;
//	//	break;
//
//	//case BagTypeTrade:
//	//	m_pTradeItem->dwMoney -= dwMoney;
//	//	if(m_pTradeItem->dwMoney<0)
//	//		m_pTradeItem->dwMoney = 0;
//	//	break;
//
//	//default:
//	//	break;
//	//}
//
//	return true;
//}
//
////获取金钱总数
//int  CStoreTradeBag::GetMoney( short stWhichBag )
//{
//	//switch(stWhichBag)
//	//{
//	//case BagTypeStore:
//	//	return m_pStoreItem->dwMoney;
//	//	break;
//
//	//case BagTypeTrade:
//	//	return m_pTradeItem->dwMoney;
//	//	break;
//	//}
//
//	return 0;
//}
//
//bool CStoreTradeBag::GetItem( short stWhichBag, short stIndex, SCharItem *pItem )
//{
//
//	//if( stWhichBag!=BagTypeStore&&stWhichBag!=BagTypeTrade )
//	//	return false;
//	//
//	//if( stIndex < 0 || stIndex >= GetBagSizeByType( stWhichBag ) )
//	//	return false;
//
//	//SCharItem *pSourceItem;
//	//pSourceItem = GetBagPointByType( stWhichBag );
//	//if(!pSourceItem)
//	//	return false;
//
//	//memcpy( pItem, &pSourceItem[stIndex], sizeof(SCharItem) );
//	return true;
//}
//
////清空指定背包,索引的信息
//bool CStoreTradeBag::ClearItem( short stWhichBag, short stIndex )
//{
//
//	//if( stWhichBag!=BagTypeStore&&stWhichBag!=BagTypeTrade )
//	//	return false;
//
//	//if( stIndex < 0 || stIndex >= GetBagSizeByType( stWhichBag ) )
//	//	return false;
//
//	//SCharItem *pItem;
//	//pItem = GetBagPointByType( stWhichBag );
//	//if(!pItem)
//	//	return false;
//
//	//pItem += stIndex;
//	//pItem->ustItemID = ErrorUnsignedShortID;
//	return true;
//}
//
////获取指定背包,索引的状况...判断该位置是有
//bool CStoreTradeBag::IsHaveItem( short stWhichBag, short stIndex )
//{
//	SCharItem *pItem;
//	pItem = GetBagPointByType( stWhichBag );
//	if(!pItem)
//		return true;
//
//	return (pItem[stIndex].ustItemID!=ErrorUnsignedShortID );
//}
//
////{ add by ^^
//int   CStoreTradeBag::GetItemCount( int iItemID )
//{
//	int i,iNumber1,iNumber2,iNumber;
//	ItemDefine::SItemCommon *pItemDetail;
//	//
//	iNumber1 = iNumber2 = 0;
//	//
//	for( i = 0; i < m_iStoreBagSize; i++ )
//	{
//		if( m_pStoreItem->itemStore[ i ].ustItemID == iItemID )
//		{
//			pItemDetail = theItemDetail.GetItemByID( iItemID );
//			if( !pItemDetail )
//				return ierr_unknown;
//
//			if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE || 
//				pItemDetail->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
//				iNumber1 +=   m_pStoreItem->itemStore[ i ].extdata.ustItemCount;
//			else iNumber1++;
//		}
//	}
//	//
//	for( i = 0; i < m_iTradeBagSize; i++ )
//	{
//		if( m_pTradeItem->itemTrade[ i ].ustItemID == iItemID )
//		{
//			pItemDetail = theItemDetail.GetItemByID( iItemID );
//			if( !pItemDetail )
//				return ierr_unknown;
//
//			if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE || 
//				pItemDetail->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
//				iNumber2 +=   m_pTradeItem->itemTrade[ i ].extdata.ustItemCount;
//			else iNumber2++;
//		}
//	}
//	//
//	iNumber = iNumber1 + iNumber2;
//	//
//	return iNumber;
//}
////} add by ^^
//
//
