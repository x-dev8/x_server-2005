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
    //初始化每个背包指针
    bool CreateFromData( SCharItem *pPackItem, int iBagSize );

    //是否可以取出指定的物品(封装了各个CanPOP函数)
    bool CanPopItem( SCharItem &item );
    //是否可以放入指定的物品(封装了各个CanPUSH函数)
    bool CanPushItem( SCharItem &item );

    //放入指定的物品(封装了各个PUSH函数)
    int PushItem(  SCharItem &item, unsigned short &ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog,
        short stIndex=-1, int *pOffSet=NULL, bool *pbNew	=NULL );

    //ustCount是输出参数

    /*int PushItem( SCharItem& item, unsigned short& ustCount, short stIndex=-1, int* pOffSet=NULL, bool* pbNew=NULL ); // 放入指定的物品(封装了各个PUSH函数)*/
    //取出指定的物品(封装了各个POP函数)	
    //传入一个GUID指针，用于删除单个不允许堆叠的物品返回这个物品的GUID
    int PopItemByID( unsigned short ustItemId, unsigned short ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, __int64* pretGUID = NULL );
    int PopItem( short stIndex, unsigned short &ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog );

    //获取指定背包,索引的信息
    bool GetItem( short stIndex, SCharItem *pItem );
    //Luoz add 获取指定背包, 通过物品id
    bool GetItemByOnlyeID( __int64 n64Index, SCharItem *pItem );
    //Luoz add 获取指定背包,索引的信息 唯一ID
    bool GetItemByItemID( int itemid, SCharItem *pItem );

    //清空指定背包,索引的信息
    bool ClearItem( short stIndex );
    bool ClearItem(unsigned int stIndex ,int Count);

    //获取指定背包,索引的状况...判断该位置是有
    bool IsHaveItem( unsigned short stIndex, unsigned short* pItemId = NULL );
    bool IsHaveItemById( int itemID );
    //add by ^^
    int	 GetItemCount( int iItemID );
    int GetItemCount();
    int GetNullItemCount();
    int  GetItemIndex( SCharItem *pItem );
    int  GetItemIndexById( int nId );
	int  GetItemIndexByGUID( __int64 nGUID );
    //找出指定背包的空闲位置
    int FindNullItemOffset();

    float StatAllItemWeight();
    //改变物品加密属性
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
    //相关背包指针
    SCharItem *m_pPackItem;
    bool					*m_bEnables;;

private:
    //背包的最大数目
    int m_iBagSize;

    int m_nBagIndex;

    int m_nLiveItemCount;

	static unsigned short m_usLastItemIdOfQueryStackCount;
	static unsigned short m_usLastQueryStackCount;

    //找出指定背包内某个物品的偏移
    int FindItemOffsetByID(	unsigned short ustItemID,int iBeginPos = 0 );

    //--------------------每个子背包的操作函数---------------------//

    //是否能放入(独占类)物品
    bool CanPushExclusiveItem();
    //是否能取出(独占类)物品
    bool CanPopExclusiveItem( SCharItem &item );
    ////放入(独占类)物品
    int  PushExclusiveItem( SCharItem &item, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, short stIndex=-1,
        int *pOffSet=NULL, bool *pbNew=NULL );
    //取出(独占类)物品
    //	bool PopExclusiveItem( SCharItem &item );
    bool PopExclusiveItemByIndex( short stIndex, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog );

    //是否能放入(非独占类)物品
    bool CanPushNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount );
    //是否能取出(非独占类)物品
    bool CanPopNonExclusiveItem( unsigned short ustItemID, unsigned short ustCount );
    //放入(非独占类)物品
    int  PushNonExclusiveItem( SCharItem &item, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, short stIndex=-1,
        int *pOffSet=NULL, bool *pbNew=NULL, int nCnt = -1 );
    //取出(非独占类)物品
    //	int  PopNonExclusiveItem( unsigned short ustItemID, unsigned short &ustCount );
    int  PopNonExclusiveItemByIndex( short stIndex, unsigned short &ustCount, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog );

    static int  MoveMaterial(SCharItem* pDst,SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, int nCount = -1);
	// 移动后灰掉
	static int  MoveMaterialGray(SCharItem* pDst,SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, int nCount = -1);
    // static 
public:
    static int MoveItem( SCharItem* pDst, SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, int nCount = -1 );
	// 移动后灰掉
	static int MoveItemGray( SCharItem* pDst, SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog, int nCount = -1 );
    //移动物品公共函数
    static bool ExchangeItem( SCharItem* pDst, SCharItem* pSrc, funPlayerLog pLogFunc, BasePlayer* pPlayer, std::string strLog );
	//得到物品堆叠数
	static int GetItemStackCount(unsigned short ustItemID);
};
