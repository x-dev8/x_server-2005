//
//#pragma once
//#include "..\..\common\More.h"
//
//class CStoreTradeBag
//{
//public:
//	CStoreTradeBag( );
//	~CStoreTradeBag( );
//
//	//��ʼ��ָ��
//	bool CreateFromData( SCharStore *pStoreItem,
//						 SCharTrade *pTradeItem,
//						 int iStoreBagSize, int iTradeBagSize );
//
//
//
//	//������Ʒ
//	bool PushItem( short stWhichBag, SCharItem &item, short stIndex=-1 );
//	//ȡ����Ʒ
//	bool PopItem( short stWhichBag, SCharItem &item );
//	bool PopItem( short stWhichBag, short stIndex );
//
//
//	//�����Ǯ
//	bool PushMoney( short stWhichBag, DWORD dwMoney );
//	//ȡ����Ǯ
//	bool PopMoney( short stWhichBag, DWORD dwMoney );
//
//	//��ȡ��Ǯ����
//	int  GetMoney( short stWhichBag );
//
//	//��ȡָ������,��������Ϣ
//	bool GetItem( short stWhichBag, short stIndex, SCharItem *pItem );
//
//	//���ָ������,��������Ϣ
//	bool ClearItem( short stWhichBag, short stIndex );
//
//	//��ȡָ������,������״��...�жϸ�λ������
//	bool IsHaveItem( short stWhichBag, short stIndex );
//	//add by ^^
//	int  GetItemCount( int iItemID );
//
//private:
//	//�ҳ�ָ�������Ŀ���λ��
//	int FindNullItemOffset( short stWhichBag );
//
//	//���ݱ���������ȡ��ָ��
//	SCharItem* GetBagPointByType( short stWhichBag );
//
//	//���ݱ���������ȡ�������Ŀ
//	short GetBagSizeByType( short stWhichBag );
//
//	//�ֿⱳ���������Ŀ
//	int m_iStoreBagSize;
//
//	//���ױ����������Ŀ
//	int m_iTradeBagSize;
//
//	//���ָ��
//	SCharStore *m_pStoreItem;
//	SCharTrade *m_pTradeItem;
//};
//
