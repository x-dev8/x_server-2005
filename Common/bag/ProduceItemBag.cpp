//
//#include "itembag2.h"
//#include "produceitembag.h"
//#include "..\ItemDetail.h"
//extern CItemDetail GettheItemDetail();
//
//
//
//CProduceItemBag::CProduceItemBag( )
//{
//	m_pProduceItem = NULL;
//}
//
//CProduceItemBag::~CProduceItemBag( )
//{
//
//}
//
////初始化指针
//bool CProduceItemBag::CreateFromData( SProduceItem *pProduceItem )
//{
//	m_pProduceItem = pProduceItem;
//	return true;
//}
//
////物品背包的指针
//void CProduceItemBag::SetItemBagPoint( CItemBag2 *pItemBag )
//{
//	m_pItemBag = pItemBag;
//}
//
////放入原料（包括工具）
//void CProduceItemBag::PushItem( SCharItem &item, short stPos )
//{
//	//位置超出范围
//	if( stPos < ItemPos_Material1 || stPos > ItemPos_Tool )
//	{
//		return;
//	}
//
//	//放置工具
//	if(stPos==ItemPos_Tool)
//	{
//		m_pProduceItem->toolBag.ustItemID = item.ustItemID;
//		m_pProduceItem->toolBag.extdata.ustItemCount = 1;
//	}
//	//放置原料
//	else
//	{
//		if( m_pProduceItem->materialBag[stPos].ustItemID!=item.ustItemID )
//		{
//			m_pProduceItem->materialBag[stPos].ustItemID = item.ustItemID;
//			m_pProduceItem->materialBag[stPos].extdata.ustItemCount = item.extdata.ustItemCount;
//		}
//		else
//		{
//			m_pProduceItem->materialBag[stPos].extdata.ustItemCount += item.extdata.ustItemCount;
//		}
//	}
//}
//
////取出原料（包括工具）
//void CProduceItemBag::PopItem( short stPos, unsigned short &ustCount )
//{
//	//位置超出范围
//	if( stPos < ItemPos_Material1 || stPos > ItemPos_Tool )
//	{
//		return;
//	}
//
//	//取出工具
//	if(stPos==ItemPos_Tool)
//	{
//		m_pProduceItem->toolBag.ustItemID = ErrorUnsignedShortID;
//		m_pProduceItem->toolBag.extdata.ustItemCount = 0;
//	}
//	//取出原料
//	else
//	{
//		//实际的取出数量
//		if( m_pProduceItem->materialBag[stPos].extdata.ustItemCount < ustCount )
//			ustCount = m_pProduceItem->materialBag[stPos].extdata.ustItemCount;
//
//		m_pProduceItem->materialBag[stPos].extdata.ustItemCount -= ustCount;
//		if(m_pProduceItem->materialBag[stPos].extdata.ustItemCount<=0)
//		{
//			m_pProduceItem->materialBag[stPos].extdata.ustItemCount = 0;
//			m_pProduceItem->materialBag[stPos].ustItemID = ErrorUnsignedShortID;
//		}
//	}
//}
//
////获取指定位置的信息
//bool CProduceItemBag::GetItem( short stPos, SCharItem *pItem )
//{
//	//位置超出范围
//	if( stPos < ItemPos_Material1 || stPos > ItemPos_Tool )
//	{
//		return false;
//	}
//
//	//工具信息
//	if(stPos==ItemPos_Tool)
//	{
//		memcpy( pItem, &m_pProduceItem->toolBag, sizeof(SCharItem) );
//	}
//	//原料信息
//	else
//	{
//		memcpy( pItem, &m_pProduceItem->materialBag[stPos], sizeof(SCharItem) );
//	}
//
//	return true;
//}
//
////清空指定位置的信息
//bool CProduceItemBag::ClearItem( short stPos )
//{
//	//位置超出范围
//	if( stPos < ItemPos_Material1 || stPos > ItemPos_Tool )
//	{
//		return false;
//	}
//
//	//工具信息
//	if(stPos==ItemPos_Tool)
//	{
//		m_pProduceItem->toolBag.ustItemID = ErrorUnsignedShortID;
//		m_pProduceItem->toolBag.extdata.ustItemCount = 0;
//	}
//	//原料信息
//	else
//	{
//		m_pProduceItem->materialBag[stPos].ustItemID = ErrorUnsignedShortID;
//		m_pProduceItem->materialBag[stPos].extdata.ustItemCount = 0;
//	}
//
//	return true;
//}
//
////判断指定位置是否有信息
//bool CProduceItemBag::IsHaveItem( short stPos )
//{
//	//位置超出范围
//	if( stPos < ItemPos_Material1 || stPos > ItemPos_Tool )
//	{
//		return false;
//	}
//
//	//工具信息
//	if(stPos==ItemPos_Tool)
//	{
//		return (m_pProduceItem->toolBag.ustItemID!=ErrorUnsignedShortID);
//	}
//	//原料信息
//	else
//	{
//		return (m_pProduceItem->materialBag[stPos].ustItemID!=ErrorUnsignedShortID);	
//	}
//}
//
////进行制造物品的操作！！
//bool CProduceItemBag::ProduceItem( )
//{
//	//使用背包里的原料进行物品的制造
//	//搜索一下是否符合某种制造组合条件
//	int i,j;
//	int iCorrectCombo = -1;
//
//	for( i=0; i<GettheItemDetail().GetProduceItemSize( ); i++ )
//	{
//		CItemDetail::SProduceItem *pProduceItem;
//		pProduceItem = GettheItemDetail().GetProduceItem( i );
//		if(!pProduceItem)
//			continue;
//
//		//工具是否配对？
//		if( m_pProduceItem->toolBag.ustItemID != pProduceItem->ustToolID )
//		{
//			continue;
//		}
//
//		//原料是否正确，数目是否够？
//		bool bExit = false;
//		for( j=0;j<3;j++ )
//		{
//			if( m_pProduceItem->materialBag[ i ].ustItemID != pProduceItem->ustMaterialID[ i ] 
//			||( pProduceItem->ustMaterialID[ i ] != ErrorUnsignedShortID 
//			&&  m_pProduceItem->materialBag[ i ].extdata.ustItemCount < pProduceItem->ustMaterialNum[ i ] ))
//			{
//				bExit = true;
//				break;
//			}
//		}
//		if(bExit)
//		{
//			continue;
//		}
//
//		//小精灵的技能是否符合要求？
//		//unsigned short ustSpriteSkillID;
//		//unsigned short ustSpriteSkillLevel;
//		
//		//找到一个正确的组合关系
//		iCorrectCombo = i;
//		break;
//	}
//
//	//是否找到组合关系？ 
//	if( iCorrectCombo==-1 )
//		return false;
//
//	//使用的组合关系
//	CItemDetail::SProduceItem *pProduceCombo;
//	pProduceCombo = GettheItemDetail().GetProduceItem( iCorrectCombo );
//	if(!pProduceCombo)
//		return false;
//
//	//是否在成功概率之内
///*	srand( timeGetTime( ) );
//	if( rand( )%100 > pProduceCombo->ustSuccessRate )
//	{
//		return false;
//	}*/
//
//	//使用组合关系iCorrectCombo进行物品制造
//	
//	//最后制造出的物品数量取决于原料的数量
//	int num[ 3 ];
//	int iProduceNum;
//	memset( num, -1, 3*sizeof(int) );
//
//	for( i=0;i<3;i++ )
//	{
//		if( pProduceCombo->ustMaterialID[ i ] != ErrorUnsignedShortID )
//		{
//			num[ i ] = m_pProduceItem->materialBag[ i ].extdata.ustItemCount/pProduceCombo->ustMaterialNum[ i ];
//			iProduceNum = num[ i ];
//		}
//	}
//	
//	//最后制造物品的数量（根据原料数目的最少一方确定）
//	for( i=0;i<3;i++ )
//	{
//		if(num[ i ]!=-1)
//		{
//			if(num[ i ]<iProduceNum)
//			{
//				iProduceNum = num[ i ];
//			}
//		}
//	}
//
//	//进行原料和物品的转换！
//	//（原料消失,增加物品(iProduceNum个数)，工具没有反应）
//
//	//原料消失！
//	for( i=0;i<3;i++ )
//	{
//		if( pProduceCombo->ustMaterialID[ i ] != ErrorUnsignedShortID )
//		{
//			unsigned short ustMateUseNum;
//			ustMateUseNum = iProduceNum*pProduceCombo->ustMaterialNum[ i ];
//
//			PopItem( i, ustMateUseNum );
//		}
//	}
//
///*
//	//增加物品！(//唯一标识	DWORD dwGlobalID)
//	SCharItem item;
//	item.ustItemID = pProduceCombo->ustResultGoodID;
//	item.extdata.ustItemCount = iProduceNum;
//
//	unsigned short ustCount;
//	m_pItemBag->PushItem( item, ustCount );
//*/
//
////	根据原料和工具的组合关系，以及各自的需求数目，确定最后的物品数目
////	表格给的只是原料的基本数目，最后制造出的物品数量为１
//
//	return true;
//}
