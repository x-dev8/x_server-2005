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
        uint8  count;       // ����
        uint32 probability; // ����
    };

    typedef std::vector<SProductItem>      ProductItemContainer;
    typedef ProductItemContainer::iterator ItrProductItemContainer;

    struct SSplitItem
    {
        uint16               id;       // id
        ProductItemContainer products; // ��ֵĲ���
    };

    typedef std::vector<SSplitItem>      SplitItemContainer;
    typedef SplitItemContainer::iterator ItrSplitItemContainer;

    typedef std::map<uint16, uint32>          SplitItemIndexContainer;
    typedef SplitItemIndexContainer::iterator ItrSplitItemIndexContainer;

public:
    static SplitItemConfig& Instance();            // ����
    uint32        Load( const char* szFileName );  // �����ļ�
    uint32        GetSplitItemAllProduct( uint16 itemId, ProductItemContainer& products ); // �õ��������Ʒ���еĲ�����
    SProductItem* GetSplitItemProduct   ( uint16 itemId );                                 // �õ��������Ʒ��εĲ�����
    bool          IsHaveSplitItemInfo   ( uint16 itemId );                                 // �Ƿ��д˲����Ʒ��Ϣ

protected:
    SplitItemContainer      _splitItems;      // ���б������Ʒ����������
    SplitItemIndexContainer _splitItemIndexs; // ���б������Ʒ���������ݼ����±�
};

#define theItemSplitConfig SplitItemConfig::Instance()   

#endif // __ITEMSPLITCONFIG_H__
