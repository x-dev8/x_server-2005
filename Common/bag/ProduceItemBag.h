//
//#pragma once
//
//
//class CItemBag2;
//class CProduceItemBag
//{
//public:
//	CProduceItemBag( );
//	~CProduceItemBag( );
//
//	//��ʼ��ָ��
//	bool CreateFromData( SProduceItem *pProduceItem );
//	void SetItemBagPoint( CItemBag2 *pItemBag );
//
//	//����ԭ�ϣ��������ߣ�
//	void PushItem( SCharItem &item, short stPos );
//	//ȡ��ԭ�ϣ��������ߣ�
//	void PopItem( short stPos, unsigned short &ustCount );
//	
//	//��ȡָ��λ�õ���Ϣ
//	bool GetItem( short stPos, SCharItem *pItem );
//	//���ָ��λ�õ���Ϣ
//	bool ClearItem( short stPos );
//	//�ж�ָ��λ���Ƿ�����Ϣ
//	bool IsHaveItem( short stPos );
//
//	//����������Ʒ�Ĳ�������
//	bool ProduceItem( );
//
//private:
//	CItemBag2 *m_pItemBag;	//��Ʒ������ָ��
//	SProduceItem *m_pProduceItem;
//							//���챳��������
//};
