/********************************************************************
    Filename:    ItemBag.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_ITEMBAG_H__
#define __COMMON_ITEMBAG_H__

#pragma once

#include "GlobalDef.h"
#include "TimeEx.h"

class GamePlayer;

class ItemBag
{
public:
    typedef std::vector<SCharItem>      ItemSortContainer;
    typedef ItemSortContainer::iterator ItrItemSortContainer;

    enum EConstDefine
    {
        ECD_MoveGood_Error = 0,     // �ƶ���Ʒ����
        ECD_MoveGood_Move  = 1,     // ֱ���ƶ�
        ECD_MoveGood_Split = 2,     // �ƶ���Ʒ�����
    };

public:    
    ItemBag();
    ~ItemBag();

    unsigned char GetItemBagType() { return _nItemBagType; }

    static int  MoveItem( SCharItem* pDst, EBagType DstType, SCharItem* pSrc, EBagType SrcType, ItemBag* pBag, int nCount = -1 );
    static bool ExchangeItem( SCharItem* pDst, SCharItem* pSrc ); //�ƶ���Ʒ��������

    void CheckItemBag();
    
    bool CreateFromData( GamePlayer* pOwn, SCharItem *pPackItem, int iBagSize, unsigned char nItemBagType ); // ��ʼ��ÿ������ָ��
    bool CleanUp(); // ������

    bool CanPopItem( SCharItem &item );                    // �Ƿ����ȡ��ָ������Ʒ(��װ�˸���CanPOP����)
    bool CanPushItem( SCharItem& item, bool& bUseNewGrid); // �Ƿ���Է���ָ������Ʒ(��װ�˸���CanPUSH����)
    
    int PushItem( SCharItem& item, unsigned short& ustCount, short stIndex=-1, int* pOffSet=NULL, bool* pbNew=NULL ); // ����ָ������Ʒ(��װ�˸���PUSH����)

    //ȡ��ָ������Ʒ(��װ�˸���POP����)    
    //����һ��GUIDָ�룬����ɾ������������ѵ�����Ʒ���������Ʒ��GUID
    int PopItemByID( unsigned short ustItemId, unsigned short ustCount, __int64* pretGUID = NULL );
	int PopItemByGuID(__int64 GuID,unsigned short ustCount);
    int PopItem( short stIndex, unsigned short &ustCount );

	bool RemoveItemByID( unsigned short nItemId, unsigned short nCount, __int64* pretGUID = NULL );
	bool RemoveItemByGuID(__int64 GuID,unsigned short nCount);

    int FindNullItemOffset(); //�ҳ�ָ�������Ŀ���λ��

    void SetBagIndex(int nIndex);
    int  GetBagIndex(){ return m_nBagIndex; }
    int  GetNowBagSize(){ return m_iBagSize;}

    SCharItem* GetItemByIndex( int nIndex );
    bool GetItem( short stIndex, SCharItem* pItem );                     // ��ȡָ������,��������Ϣ
    bool GetItemByOnlyBigId( __int64 n64Index, SCharItem* pItem );       // ��ȡָ������, ͨ����Ʒid
    SCharItem* GetItemByOnlyBigId( __int64 nGuid );
    bool PopItemByOnlyBigId( __int64 n64Index, unsigned short usCount, int& nIndex  ); // ɾ��ָ������, ͨ����Ʒid

    bool GetItemByItemID( int itemid, SCharItem* pItem );          // ��ȡָ������,��������Ϣ ΨһID
    SCharItem* GetItemByItemID( int nItemID );
    
    bool ClearItem( short stIndex );                  // ���ָ������,��������Ϣ
    bool ClearItem( unsigned int stIndex ,int Count); // ���ָ������,��������Ϣ

    // ��ȡָ������,������״��...�жϸ�λ������********��׸ �����к��� Ҫ�Ż�
    bool IsHaveItem( unsigned short stIndex, unsigned short* pItemId = NULL );
    bool IsHaveItemById( int itemID );    

	// ����һ���µ�guid **********Ҫ�Ż�
    __int64 GetNewItemID(); // �õ����õ�BigId
    __int64 GetNewItemID( __int64 nGuid );

	// һЩGet��Ϣ
    int GetItemCount( int iItemID );
    int GetItemCount();
    int GetItemEmptyCount(); // ��ð����ո����� һ����
    int GetNullItemCount();  // ��ð����ո����� һ����
    int GetItemIndex( SCharItem *pItem );		//���ָ����Ʒ��λ�� ��0��ʼ
    int GetItemIndexById( int nId );			//���ָ��Id��Ʒ�ĵ�һ��λ�� ��0��ʼ
    int GetItemIndexByGuid( __int64 n64Guid );	//���ָ��guid��Ʒ��λ�� ��0��ʼ
    
    bool SetItemProperty(short stIndex,bool bLocked); //�ı���Ʒ��������

	// ʱ����ص�
    void SetLiveItemCount(int nCount) { m_nLiveItemCount = nCount;}
    int  GetLiveItemCount(){ return m_nLiveItemCount;}

    static void CalcItemLeftUseTime( SCharItem& xItem );	//������Ʒʹ��ʱ��
    static void CalcItemUnLockLeftTime( SCharItem& xItem ); //������Ʒ����ʱ��

protected:
    //�ҳ�ָ��������ĳ����Ʒ��ƫ��
    int FindItemOffsetByID( unsigned short ustItemID,int iBeginPos = 0 );

    // ÿ���ӱ����Ĳ�������
    bool CanPushExclusiveItem();                                                                         // �Ƿ��ܷ���(��ռ��)��Ʒ
    bool CanPushNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount, bool bBind, bool& bUseNewGrid); // �Ƿ��ܷ���(�Ƕ�ռ��)��Ʒ

    bool CanPopExclusiveItem( SCharItem &item );                                       // �Ƿ���ȡ��(��ռ��)��Ʒ
    bool CanPopNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount );  // �Ƿ���ȡ��(�Ƕ�ռ��)��Ʒ
    
    int  PushExclusiveItem( SCharItem &item, short stIndex=-1,  int* pOffSet=NULL, bool* pbNew=NULL );                    // ����(��ռ��)��Ʒ    
    int  PushNonExclusiveItem( SCharItem &item, short stIndex=-1, int nCount = -1, int* pOffSet=NULL, bool* pbNew=NULL ); // ����(�Ƕ�ռ��)��Ʒ

    int  PopExclusiveItemByIndex( short stIndex );                             // ȡ��(��ռ��)��Ʒ
    int  PopNonExclusiveItemByIndex( short stIndex, unsigned short &ustCount); // ȡ��(�Ƕ�ռ��)��Ʒ

    //static int MoveMaterial(SCharItem* pDst, EBagType DstType, SCharItem* pSrc, EBagType SrcType, ItemBag* pBag, int nCount = -1);

public:    
    SCharItem* m_pPackItem; // ��ر���ָ�� ��ʵ���ڴ������ڽ�ɫ���ϡ�
    bool*      m_bEnables;  // ���ö���

private:
    //���ڱ�����Ʒ��֤����֤��������ƷIDΨһ
    typedef std::map<__int64, SCharItem*> ItemContainer;
    typedef ItemContainer::iterator       ItrItemContainer;
    ItemContainer m_mapPackItem;
    
    int         m_iBagSize;       //�����������Ŀ
    int         m_nBagIndex;
    int         m_nLiveItemCount;
    GamePlayer* _pGamePlayer;
    unsigned    _nItemBagType;
};


inline void ItemBag::SetBagIndex(int nIndex)
{
    if ( nIndex <0 || nIndex >= m_iBagSize)
        return;

    m_nBagIndex = nIndex;
}

#endif // __COMMON_ITEMBAG_H__
