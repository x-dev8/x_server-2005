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
////��ʼ��ָ��
//bool CProduceItemBag::CreateFromData( SProduceItem *pProduceItem )
//{
//	m_pProduceItem = pProduceItem;
//	return true;
//}
//
////��Ʒ������ָ��
//void CProduceItemBag::SetItemBagPoint( CItemBag2 *pItemBag )
//{
//	m_pItemBag = pItemBag;
//}
//
////����ԭ�ϣ��������ߣ�
//void CProduceItemBag::PushItem( SCharItem &item, short stPos )
//{
//	//λ�ó�����Χ
//	if( stPos < ItemPos_Material1 || stPos > ItemPos_Tool )
//	{
//		return;
//	}
//
//	//���ù���
//	if(stPos==ItemPos_Tool)
//	{
//		m_pProduceItem->toolBag.ustItemID = item.ustItemID;
//		m_pProduceItem->toolBag.extdata.ustItemCount = 1;
//	}
//	//����ԭ��
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
////ȡ��ԭ�ϣ��������ߣ�
//void CProduceItemBag::PopItem( short stPos, unsigned short &ustCount )
//{
//	//λ�ó�����Χ
//	if( stPos < ItemPos_Material1 || stPos > ItemPos_Tool )
//	{
//		return;
//	}
//
//	//ȡ������
//	if(stPos==ItemPos_Tool)
//	{
//		m_pProduceItem->toolBag.ustItemID = ErrorUnsignedShortID;
//		m_pProduceItem->toolBag.extdata.ustItemCount = 0;
//	}
//	//ȡ��ԭ��
//	else
//	{
//		//ʵ�ʵ�ȡ������
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
////��ȡָ��λ�õ���Ϣ
//bool CProduceItemBag::GetItem( short stPos, SCharItem *pItem )
//{
//	//λ�ó�����Χ
//	if( stPos < ItemPos_Material1 || stPos > ItemPos_Tool )
//	{
//		return false;
//	}
//
//	//������Ϣ
//	if(stPos==ItemPos_Tool)
//	{
//		memcpy( pItem, &m_pProduceItem->toolBag, sizeof(SCharItem) );
//	}
//	//ԭ����Ϣ
//	else
//	{
//		memcpy( pItem, &m_pProduceItem->materialBag[stPos], sizeof(SCharItem) );
//	}
//
//	return true;
//}
//
////���ָ��λ�õ���Ϣ
//bool CProduceItemBag::ClearItem( short stPos )
//{
//	//λ�ó�����Χ
//	if( stPos < ItemPos_Material1 || stPos > ItemPos_Tool )
//	{
//		return false;
//	}
//
//	//������Ϣ
//	if(stPos==ItemPos_Tool)
//	{
//		m_pProduceItem->toolBag.ustItemID = ErrorUnsignedShortID;
//		m_pProduceItem->toolBag.extdata.ustItemCount = 0;
//	}
//	//ԭ����Ϣ
//	else
//	{
//		m_pProduceItem->materialBag[stPos].ustItemID = ErrorUnsignedShortID;
//		m_pProduceItem->materialBag[stPos].extdata.ustItemCount = 0;
//	}
//
//	return true;
//}
//
////�ж�ָ��λ���Ƿ�����Ϣ
//bool CProduceItemBag::IsHaveItem( short stPos )
//{
//	//λ�ó�����Χ
//	if( stPos < ItemPos_Material1 || stPos > ItemPos_Tool )
//	{
//		return false;
//	}
//
//	//������Ϣ
//	if(stPos==ItemPos_Tool)
//	{
//		return (m_pProduceItem->toolBag.ustItemID!=ErrorUnsignedShortID);
//	}
//	//ԭ����Ϣ
//	else
//	{
//		return (m_pProduceItem->materialBag[stPos].ustItemID!=ErrorUnsignedShortID);	
//	}
//}
//
////����������Ʒ�Ĳ�������
//bool CProduceItemBag::ProduceItem( )
//{
//	//ʹ�ñ������ԭ�Ͻ�����Ʒ������
//	//����һ���Ƿ����ĳ�������������
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
//		//�����Ƿ���ԣ�
//		if( m_pProduceItem->toolBag.ustItemID != pProduceItem->ustToolID )
//		{
//			continue;
//		}
//
//		//ԭ���Ƿ���ȷ����Ŀ�Ƿ񹻣�
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
//		//С����ļ����Ƿ����Ҫ��
//		//unsigned short ustSpriteSkillID;
//		//unsigned short ustSpriteSkillLevel;
//		
//		//�ҵ�һ����ȷ����Ϲ�ϵ
//		iCorrectCombo = i;
//		break;
//	}
//
//	//�Ƿ��ҵ���Ϲ�ϵ�� 
//	if( iCorrectCombo==-1 )
//		return false;
//
//	//ʹ�õ���Ϲ�ϵ
//	CItemDetail::SProduceItem *pProduceCombo;
//	pProduceCombo = GettheItemDetail().GetProduceItem( iCorrectCombo );
//	if(!pProduceCombo)
//		return false;
//
//	//�Ƿ��ڳɹ�����֮��
///*	srand( timeGetTime( ) );
//	if( rand( )%100 > pProduceCombo->ustSuccessRate )
//	{
//		return false;
//	}*/
//
//	//ʹ����Ϲ�ϵiCorrectCombo������Ʒ����
//	
//	//������������Ʒ����ȡ����ԭ�ϵ�����
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
//	//���������Ʒ������������ԭ����Ŀ������һ��ȷ����
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
//	//����ԭ�Ϻ���Ʒ��ת����
//	//��ԭ����ʧ,������Ʒ(iProduceNum����)������û�з�Ӧ��
//
//	//ԭ����ʧ��
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
//	//������Ʒ��(//Ψһ��ʶ	DWORD dwGlobalID)
//	SCharItem item;
//	item.ustItemID = pProduceCombo->ustResultGoodID;
//	item.extdata.ustItemCount = iProduceNum;
//
//	unsigned short ustCount;
//	m_pItemBag->PushItem( item, ustCount );
//*/
//
////	����ԭ�Ϻ͹��ߵ���Ϲ�ϵ���Լ����Ե�������Ŀ��ȷ��������Ʒ��Ŀ
////	������ֻ��ԭ�ϵĻ�����Ŀ��������������Ʒ����Ϊ��
//
//	return true;
//}
