/********************************************************************
    Filename:     ItemBag2.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "GlobalDef.h"

class BasePlayer;

typedef void (*funPlayerLog) (BasePlayer* pPlayer, const char* szFormat, ...);

class RobotItemBag
{
public:	
    RobotItemBag();
    ~RobotItemBag();

    static	__int64 CreateID2();
    //��ʼ��ÿ������ָ��
    bool CreateFromData( SCharItem *pPackItem, int iBagSize );

    //�Ƿ����ȡ��ָ������Ʒ(��װ�˸���CanPOP����)
    bool CanPopItem( SCharItem &item );
    //�Ƿ���Է���ָ������Ʒ(��װ�˸���CanPUSH����)
    bool CanPushItem( SCharItem &item );

    //����ָ������Ʒ(��װ�˸���PUSH����)
    int PushItem(  SCharItem &item, unsigned short &ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog,
        short stIndex=-1, int *pOffSet=NULL, bool *pbNew	=NULL );

    //ustCount���������

    /*int PushItem( SCharItem& item, unsigned short& ustCount, short stIndex=-1, int* pOffSet=NULL, bool* pbNew=NULL ); // ����ָ������Ʒ(��װ�˸���PUSH����)*/
    //ȡ��ָ������Ʒ(��װ�˸���POP����)	
    //����һ��GUIDָ�룬����ɾ������������ѵ�����Ʒ���������Ʒ��GUID
    int PopItemByID( unsigned short ustItemId, unsigned short ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, __int64* pretGUID = NULL );
    int PopItem( short stIndex, unsigned short &ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog );

    //��ȡָ������,��������Ϣ
    bool GetItem( short stIndex, SCharItem *pItem );
    //Luoz add ��ȡָ������, ͨ����Ʒid
    bool GetItemByOnlyeID( __int64 n64Index, SCharItem *pItem );
    //Luoz add ��ȡָ������,��������Ϣ ΨһID
    bool GetItemByItemID( int itemid, SCharItem *pItem );

    //���ָ������,��������Ϣ
    bool ClearItem( short stIndex );
    bool ClearItem(unsigned int stIndex ,int Count);

    //��ȡָ������,������״��...�жϸ�λ������
    bool IsHaveItem( unsigned short stIndex, unsigned short* pItemId = NULL );
    bool IsHaveItemById( int itemID );
    //add by ^^
    int	 GetItemCount( int iItemID );
    int GetItemCount();
    int GetNullItemCount();
    int  GetItemIndex( SCharItem *pItem );
    int  GetItemIndexById( int nId );
	int  GetItemIndexByGUID( __int64 nGUID );
    //�ҳ�ָ�������Ŀ���λ��
    int FindNullItemOffset();

    float StatAllItemWeight();
    //�ı���Ʒ��������
    bool SetItemProperty(short stIndex,bool bLocked);

    void SetBagIndex(int nIndex)
    {
        if (nIndex >= 0 && nIndex < ITEM_BAGMAX)
        {
            m_nBagIndex = nIndex;
        }
    }

    int GetBagIndex(){return m_nBagIndex;}

    int GetNowBagSize(){return m_iBagSize;}

    void SetLiveItemCount(int nCount)
    {
        m_nLiveItemCount = nCount;
    }

    int GetLiveItemCount(){return m_nLiveItemCount;}

    SCharItem * GetCharItemFromIdx( INT nIdx );
public:
    //��ر���ָ��
    SCharItem *m_pPackItem;
    bool					*m_bEnables;;

private:
    //�����������Ŀ
    int m_iBagSize;

    int m_nBagIndex;

    int m_nLiveItemCount;

	static unsigned short m_usLastItemIdOfQueryStackCount;
	static unsigned short m_usLastQueryStackCount;

    //�ҳ�ָ��������ĳ����Ʒ��ƫ��
    int FindItemOffsetByID(	unsigned short ustItemID,int iBeginPos = 0 );

    //--------------------ÿ���ӱ����Ĳ�������---------------------//

    //�Ƿ��ܷ���(��ռ��)��Ʒ
    bool CanPushExclusiveItem();
    //�Ƿ���ȡ��(��ռ��)��Ʒ
    bool CanPopExclusiveItem( SCharItem &item );
    ////����(��ռ��)��Ʒ
    int  PushExclusiveItem( SCharItem &item, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, short stIndex=-1,
        int *pOffSet=NULL, bool *pbNew=NULL );
    //ȡ��(��ռ��)��Ʒ
    //	bool PopExclusiveItem( SCharItem &item );
    bool PopExclusiveItemByIndex( short stIndex, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog );

    //�Ƿ��ܷ���(�Ƕ�ռ��)��Ʒ
    bool CanPushNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount );
    //�Ƿ���ȡ��(�Ƕ�ռ��)��Ʒ
    bool CanPopNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount );
    //����(�Ƕ�ռ��)��Ʒ
    int  PushNonExclusiveItem( SCharItem &item, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, short stIndex=-1,
        int *pOffSet=NULL, bool *pbNew=NULL, int nCnt = -1 );
    //ȡ��(�Ƕ�ռ��)��Ʒ
    //	int  PopNonExclusiveItem( unsigned short ustItemID, unsigned short &ustCount );
    int  PopNonExclusiveItemByIndex( short stIndex, unsigned short &ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog );

    static int  MoveMaterial(SCharItem* pDst,SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, int nCount = -1);
	// �ƶ���ҵ�
	static int  MoveMaterialGray(SCharItem* pDst,SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, int nCount = -1);
    // static 
public:
    static int MoveItem( SCharItem* pDst, SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, int nCount = -1 );
	// �ƶ���ҵ�
	static int MoveItemGray( SCharItem* pDst, SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, int nCount = -1 );
    //�ƶ���Ʒ��������
    static bool ExchangeItem( SCharItem* pDst, SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog );
	//�õ���Ʒ�ѵ���
	static int GetItemStackCount(unsigned short ustItemID);
};
