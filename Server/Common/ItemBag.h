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
        ECD_MoveGood_Error = 0,     // 移动物品错误
        ECD_MoveGood_Move  = 1,     // 直接移动
        ECD_MoveGood_Split = 2,     // 移动物品拆分了
    };

public:    
    ItemBag();
    ~ItemBag();

    unsigned char GetItemBagType() { return _nItemBagType; }

    static int  MoveItem( SCharItem* pDst, EBagType DstType, SCharItem* pSrc, EBagType SrcType, ItemBag* pBag, int nCount = -1 );
    static bool ExchangeItem( SCharItem* pDst, SCharItem* pSrc ); //移动物品公共函数

    void CheckItemBag();
    
    bool CreateFromData( GamePlayer* pOwn, SCharItem *pPackItem, int iBagSize, unsigned char nItemBagType ); // 初始化每个背包指针
    bool CleanUp(); // 整理背包

    bool CanPopItem( SCharItem &item );                    // 是否可以取出指定的物品(封装了各个CanPOP函数)
    bool CanPushItem( SCharItem& item, bool& bUseNewGrid); // 是否可以放入指定的物品(封装了各个CanPUSH函数)
    
    int PushItem( SCharItem& item, unsigned short& ustCount, short stIndex=-1, int* pOffSet=NULL, bool* pbNew=NULL ); // 放入指定的物品(封装了各个PUSH函数)

    //取出指定的物品(封装了各个POP函数)    
    //传入一个GUID指针，用于删除单个不允许堆叠的物品返回这个物品的GUID
    int PopItemByID( unsigned short ustItemId, unsigned short ustCount, __int64* pretGUID = NULL );
	int PopItemByGuID(__int64 GuID,unsigned short ustCount);
    int PopItem( short stIndex, unsigned short &ustCount );

	bool RemoveItemByID( unsigned short nItemId, unsigned short nCount, __int64* pretGUID = NULL );
	bool RemoveItemByGuID(__int64 GuID,unsigned short nCount);

    int FindNullItemOffset(); //找出指定背包的空闲位置

    void SetBagIndex(int nIndex);
    int  GetBagIndex(){ return m_nBagIndex; }
    int  GetNowBagSize(){ return m_iBagSize;}

    SCharItem* GetItemByIndex( int nIndex );
    bool GetItem( short stIndex, SCharItem* pItem );                     // 获取指定背包,索引的信息
    bool GetItemByOnlyBigId( __int64 n64Index, SCharItem* pItem );       // 获取指定背包, 通过物品id
    SCharItem* GetItemByOnlyBigId( __int64 nGuid );
    bool PopItemByOnlyBigId( __int64 n64Index, unsigned short usCount, int& nIndex  ); // 删除指定背包, 通过物品id

    bool GetItemByItemID( int itemid, SCharItem* pItem );          // 获取指定背包,索引的信息 唯一ID
    SCharItem* GetItemByItemID( int nItemID );
    
    bool ClearItem( short stIndex );                  // 清空指定背包,索引的信息
    bool ClearItem( unsigned int stIndex ,int Count); // 清空指定背包,索引的信息

    // 获取指定背包,索引的状况...判断该位置是有********累赘 下面有函数 要优化
    bool IsHaveItem( unsigned short stIndex, unsigned short* pItemId = NULL );
    bool IsHaveItemById( int itemID );    

	// 创建一个新的guid **********要优化
    __int64 GetNewItemID(); // 得到可用的BigId
    __int64 GetNewItemID( __int64 nGuid );

	// 一些Get信息
    int GetItemCount( int iItemID );
    int GetItemCount();
    int GetItemEmptyCount(); // 获得包裹空格子数 一样？
    int GetNullItemCount();  // 获得包裹空格子数 一样？
    int GetItemIndex( SCharItem *pItem );		//获得指定物品的位置 从0开始
    int GetItemIndexById( int nId );			//获得指定Id物品的第一个位置 从0开始
    int GetItemIndexByGuid( __int64 n64Guid );	//获得指定guid物品的位置 从0开始
    
    bool SetItemProperty(short stIndex,bool bLocked); //改变物品加密属性

	// 时限相关的
    void SetLiveItemCount(int nCount) { m_nLiveItemCount = nCount;}
    int  GetLiveItemCount(){ return m_nLiveItemCount;}

    static void CalcItemLeftUseTime( SCharItem& xItem );	//计算物品使用时限
    static void CalcItemUnLockLeftTime( SCharItem& xItem ); //计算物品解锁时限

protected:
    //找出指定背包内某个物品的偏移
    int FindItemOffsetByID( unsigned short ustItemID,int iBeginPos = 0 );

    // 每个子背包的操作函数
    bool CanPushExclusiveItem();                                                                         // 是否能放入(独占类)物品
    bool CanPushNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount, bool bBind, bool& bUseNewGrid); // 是否能放入(非独占类)物品

    bool CanPopExclusiveItem( SCharItem &item );                                       // 是否能取出(独占类)物品
    bool CanPopNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount );  // 是否能取出(非独占类)物品
    
    int  PushExclusiveItem( SCharItem &item, short stIndex=-1,  int* pOffSet=NULL, bool* pbNew=NULL );                    // 放入(独占类)物品    
    int  PushNonExclusiveItem( SCharItem &item, short stIndex=-1, int nCount = -1, int* pOffSet=NULL, bool* pbNew=NULL ); // 放入(非独占类)物品

    int  PopExclusiveItemByIndex( short stIndex );                             // 取出(独占类)物品
    int  PopNonExclusiveItemByIndex( short stIndex, unsigned short &ustCount); // 取出(非独占类)物品

    //static int MoveMaterial(SCharItem* pDst, EBagType DstType, SCharItem* pSrc, EBagType SrcType, ItemBag* pBag, int nCount = -1);

public:    
    SCharItem* m_pPackItem; // 相关背包指针 【实际内存数据在角色身上】
    bool*      m_bEnables;  // 可用队列

private:
    //用于背包物品验证，保证背包中物品ID唯一
    typedef std::map<__int64, SCharItem*> ItemContainer;
    typedef ItemContainer::iterator       ItrItemContainer;
    ItemContainer m_mapPackItem;
    
    int         m_iBagSize;       //背包的最大数目
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
