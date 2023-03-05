#ifndef __ITEMSPLITCONFIG_H__
#define __ITEMSPLITCONFIG_H__

#pragma once

#include "GlobalDef.h"

class SplitItemConfig
{
public:    
    struct SProductItem
    {
        uint16 id;          // id
        uint8  count;       // 个数
        uint32 probability; // 概率
    };

    typedef std::vector<SProductItem>      ProductItemContainer;
    typedef ProductItemContainer::iterator ItrProductItemContainer;

    struct SSplitItem
    {
        uint16               id;       // id
        ProductItemContainer products; // 拆分的产物
    };

    typedef std::vector<SSplitItem>      SplitItemContainer;
    typedef SplitItemContainer::iterator ItrSplitItemContainer;

    typedef std::map<uint16, uint32>          SplitItemIndexContainer;
    typedef SplitItemIndexContainer::iterator ItrSplitItemIndexContainer;

public:
    static SplitItemConfig& Instance();            // 单件
    uint32        Load( const char* szFileName );  // 加载文件
    uint32        GetSplitItemAllProduct( uint16 itemId, ProductItemContainer& products ); // 得到被拆分物品所有的产出物
    SProductItem* GetSplitItemProduct   ( uint16 itemId );                                 // 得到被拆分物品这次的产出物
    bool          IsHaveSplitItemInfo   ( uint16 itemId );                                 // 是否有此拆分物品信息

protected:
    SplitItemContainer      _splitItems;      // 所有被拆分物品的配置数据
    SplitItemIndexContainer _splitItemIndexs; // 所有被拆分物品的配置数据检索下标
};

#define theItemSplitConfig SplitItemConfig::Instance()   

#endif // __ITEMSPLITCONFIG_H__
