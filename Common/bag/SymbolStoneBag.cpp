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
//	//�����µķ�ʯ
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
//	//���Ԫ��
//	if( m_pStoneData[stStoneIndex].ustStoneID==ErrorUnsignedShortID )
//		return false;
//
//	m_pStoneData[stStoneIndex].ustStoneID = ErrorUnsignedShortID;
//	return true;
//}
//
////��ȡָ�������ķ�ʯ��Ϣ
//bool CSymbolStoneBag::GetStone( short stIndex, SCharSymbolStone *pStone )
//{
//	if( stIndex<0 || stIndex >= m_iBagSize )
//		return false;
//
//	memcpy( pStone, &m_pStoneData[stIndex], sizeof(SCharSymbolStone) );
//	return true;
//}
//
////��ȡָ��������״��...�жϸ�λ������
//bool CSymbolStoneBag::IsHaveStone( short stIndex )
//{
//	return ( m_pStoneData[stIndex].ustStoneID!=ErrorUnsignedShortID );
//}
//
////���ָ�������ķ�ʯ
//bool CSymbolStoneBag::ClearStone( short stIndex )
//{
//	m_pStoneData[stIndex].ustStoneID = ErrorUnsignedShortID;
//	return true;
//}
//
////���ӵ�������
//void CSymbolStoneBag::AttachToSkill( short stStoneIndex, short stSkillIndex )
//{
//	m_pStoneData[stStoneIndex].stBelongSkillIndex = stSkillIndex;
//	m_pStoneData[stStoneIndex].bAvailable = false;
//}
//
////�Ӽ�������
//void CSymbolStoneBag::DetachFromSkill( short stStoneIndex )
//{
//	m_pStoneData[stStoneIndex].stBelongSkillIndex = -1;
//	m_pStoneData[stStoneIndex].bAvailable = true;
//}
//
