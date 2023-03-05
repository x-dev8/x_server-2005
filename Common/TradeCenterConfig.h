///********************************************************************
//	Filename: 	ShopCenterSlk.h
//	MaintenanceMan Mail: Luo_157@hotmail.com
//*********************************************************************/
//
#ifndef __TRADECENTERCONFIG_H__
#define __TRADECENTERCONFIG_H__
//
#pragma once
//
//#include "GlobalDef.h"
/*
 * Author: 2012-9-26 16:02:47 liaojie
 * Desc:   ����ļ�ò��ûʲô�ã����ܶ���TradeCenterInfo.h���ˣ��Ȱ����ע�͵�����û������
 */
///************************************************************************
//    DiscountPercent     �����ۿ�
//    Name                ��Ʒ����
//    ItemId              ��Ʒid
//    OriginalPrice       ԭʼ�۸�
//    FinalDiscountPrice  ���ռ۸�
//    TicketPrice         ���蹺��ȯ
//    Count               ��Ʒ����
//    RefreshInterval     ˢ�¼�������ӣ�
//    IsHot               ����
//    IsNew               ��Ʒ                                                            
//************************************************************************/
////��Ʒ��Ϣ
//class TradeItem
//{
//public:
//	TradeItem()
//	{
//		ItemId = InvalidLogicNumber;
//		OriginalPrice = 0;
//		FinalDiscountPrice = 0;
//        TicketPrice = 0;
//		Count = 0;
//		CurrentCount = 0;
//		RefreshInterval = 0;
//		IsHot = false;
//		IsNew = false;
//        TypeName.clear();
//	}
//
//    TradeItem( const TradeItem& xItem )
//    {
//        *this = xItem;
//    }
//
//    TradeItem& operator = ( const TradeItem& xItem )
//    {
//        if ( &xItem != this )
//        {
//            TypeName           = xItem.TypeName;
//            ItemId             = xItem.ItemId;
//            OriginalPrice      = xItem.OriginalPrice;
//            FinalDiscountPrice = xItem.FinalDiscountPrice;
//            TicketPrice        = xItem.TicketPrice;
//            Count              = xItem.Count;
//            CurrentCount       = xItem.CurrentCount;
//            RefreshInterval    = xItem.RefreshInterval;
//            IsHot              = xItem.IsHot;
//            IsNew              = xItem.IsNew;
//        }
//        return *this;
//    }
//
//	bool operator == (const int& nItemId)
//	{
//		return (this->ItemId == nItemId);
//	}
//
//public:
//	static unsigned char DiscountPercent;	//�̳������ۿ۱��ʣ�������DiscountPrice�����ɻ������� ( 1 - 100)
//    
//    std::string TypeName;                   // ��Ʒ����
//	unsigned short ItemId;					// ��ƷID
//	unsigned short OriginalPrice;			// ԭʼ�۸�
//	unsigned short FinalDiscountPrice;		// ���ռ۸�
//    unsigned short TicketPrice;             // ���蹺��ȯ ��
//    unsigned int Count;					    // ��������   ��Ʊ
//	unsigned int CurrentCount;			    // ��ǰ���۵�����
//	unsigned int RefreshInterval;			// ˢ������  ���Ϊÿ��ˢ�£������Է���Ϊ��λˢ��
//	bool IsHot;								// �Ƿ�����, 0���Ϊ��Ч
//	bool IsNew;								// �Ƿ���Ʒ, 0���Ϊ��Ч
//};
//
//#define theTradeCenterConfig TradeCenterConfig::Instance()
//
//class TradeCenterConfig
//{
//public:
//	~TradeCenterConfig();
//
//	static TradeCenterConfig& Instance()
//	{
//		static TradeCenterConfig s_xTradeCenterManger;
//		return s_xTradeCenterManger;
//	}
//
//	bool       LoadTradeItemConfig( const char* szFile );
//	bool       AddTradeItem       ( TradeItem &xShopData, bool bReplace = false );
//	uint32     GetTradeItemCount  () { return static_cast<unsigned int>( m_mapTradeItem.size() ); }
//	TradeItem* GetTradeItemByIndex( unsigned int nIndex );
//	TradeItem* GetTradeItemByItemID( unsigned short nItemId );
//
//    bool AddTradeItemTypeName( std::string& strType, unsigned short ustItemID );
//    bool RemoveTradeItemTypeName( std::string& strType, unsigned short ustItemID );
//    void GetTradeItemIDByType( std::string& strType, std::vector<unsigned short>& vecItemID );
//
//	bool RefurbishCount(DWORD dwTime);			//ˢ�³�������
//
//    //�༭��ʹ�����
//	bool SaveTradeItemConfig(const char* szFile);
//	bool RemoveTradeItem(unsigned short nItemId);
//	bool ChangeDiscountPercent(unsigned char nDiscountPercent);   //�޸��ۿ�
//
//public:
//    typedef std::map< std::string, std::vector< unsigned short > > TypeMap;
//    typedef TypeMap::iterator TypeMapIter;
//
//    typedef std::map< unsigned short, TradeItem > TradeItemMap;
//    typedef TradeItemMap::iterator TradeItemMapIter;
//
//	TradeItemMap m_mapTradeItem; // id ����Ʒ����
//    TypeMap m_mapType;           // ������Ʒ���ͺ͸�����Ʒ�Ĺ���
//
//private:
//	TradeCenterConfig();
//};
//
#endif // __TRADECENTERCONFIG_H__
