//
// 
//#include "skillbag.h"
//#include "symbolstonebag.h"
//#include "ItemDetail.h"
//extern CItemDetail GettheItemDetail();
//
//
//
//CSymbolStoneBag::CSymbolStoneBag( )
//{
//	m_iBagSize = 0;
//	m_pStoneData = NULL;
//}
//
//CSymbolStoneBag::~CSymbolStoneBag( )
//{
//
//}
//
//void CSymbolStoneBag::SetSkillBagPoint( CSkillBag *pSkillBag )
//{
//	m_pSkillBag = pSkillBag;
//}
//
//void CSymbolStoneBag::CreateFromData( SCharSymbolStone *pStoneData, int iBagSize )
//{
//	m_iBagSize = iBagSize;
//	m_pStoneData = pStoneData;
//}
//
//int CSymbolStoneBag::FindNullStoneOffSet( )
//{
//	int iLoop;
//	for( iLoop=0; iLoop<m_iBagSize; iLoop++ )
//	{
//		if( ErrorUnsignedShortID==m_pStoneData[iLoop].ustStoneID )
//			return iLoop;
//	}
//	return -1;
//}
//
//bool CSymbolStoneBag::AddStone( unsigned short ustStoneID, short stIndex )
//{
//	CItemDetail::SSymbolStone *pStone;
//	pStone = (CItemDetail::SSymbolStone *)(GettheItemDetail().GetItemByID(ustStoneID));
//	if(!pStone)
//		return false;
//
//	int iOffset = stIndex;
//	if( iOffset==-1 )
//	{
//		iOffset = FindNullStoneOffSet( );
//		if( iOffset==-1 )
//			return false;
//	}
//	else
//	{
//		if( iOffset<0 || iOffset>=m_iBagSize )
//			return false;
//	}
//
//	if(m_pStoneData[iOffset].ustStoneID!=ErrorUnsignedShortID)
//		return false;
//
//	//增加新的符石
//	m_pStoneData[iOffset].ustStoneID = ustStoneID;
//	m_pStoneData[iOffset].bAvailable = true;
//	m_pStoneData[iOffset].stBelongSkillIndex = -1;
//
//	return true;
//}
//
//bool CSymbolStoneBag::RemoveStone( short stStoneIndex )
//{
//	if( stStoneIndex < 0 || stStoneIndex >= m_iBagSize )
//		return false;
//
//	//清除元素
//	if( m_pStoneData[stStoneIndex].ustStoneID==ErrorUnsignedShortID )
//		return false;
//
//	m_pStoneData[stStoneIndex].ustStoneID = ErrorUnsignedShortID;
//	return true;
//}
//
////获取指定索引的符石信息
//bool CSymbolStoneBag::GetStone( short stIndex, SCharSymbolStone *pStone )
//{
//	if( stIndex<0 || stIndex >= m_iBagSize )
//		return false;
//
//	memcpy( pStone, &m_pStoneData[stIndex], sizeof(SCharSymbolStone) );
//	return true;
//}
//
////获取指定索引的状况...判断该位置是有
//bool CSymbolStoneBag::IsHaveStone( short stIndex )
//{
//	return ( m_pStoneData[stIndex].ustStoneID!=ErrorUnsignedShortID );
//}
//
////清空指定索引的符石
//bool CSymbolStoneBag::ClearStone( short stIndex )
//{
//	m_pStoneData[stIndex].ustStoneID = ErrorUnsignedShortID;
//	return true;
//}
//
////连接到技能上
//void CSymbolStoneBag::AttachToSkill( short stStoneIndex, short stSkillIndex )
//{
//	m_pStoneData[stStoneIndex].stBelongSkillIndex = stSkillIndex;
//	m_pStoneData[stStoneIndex].bAvailable = false;
//}
//
////从技能脱离
//void CSymbolStoneBag::DetachFromSkill( short stStoneIndex )
//{
//	m_pStoneData[stStoneIndex].stBelongSkillIndex = -1;
//	m_pStoneData[stStoneIndex].bAvailable = true;
//}
//
