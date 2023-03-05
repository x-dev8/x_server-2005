/*
 * Author: 2012-9-26 16:04:04 liaojie
 * Desc:   ����ļ�ò��ûʲô�ã����ܶ���TradeCenterInfo.h���ˣ��Ȱ����ע�͵�����û������
 */
//#include "TradeCenterConfig.h"
//#include "Tinyxml\tinyxml.h"
//#include "application_config.h"
//#include "tstring.h"
//#include "RapidXml\MeRapidXml.h"
//
//unsigned char TradeItem::DiscountPercent = 0;			//�̳�������ۿ�
//
//TradeCenterConfig::TradeCenterConfig()
//{
//	m_mapTradeItem.clear();
//    m_mapType.clear();
//}
//
//TradeCenterConfig::~TradeCenterConfig()
//{
//
//}
//
//
//bool TradeCenterConfig::LoadTradeItemConfig(const char* szFile)
//{
//	if (szFile == NULL || *szFile == 0)
//	{
//		return false;
//	}
//	m_mapTradeItem.clear();
//
//	MeXmlDocument xMeXml;
//	if (!xMeXml.LoadFile(szFile, TIXML_ENCODING_UTF8)) { return false; }
//
//	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
//	if (pRoot == NULL ) { return false; }
//	//int nCount;
//	//if (pRoot->Attribute("TotalItemCount", &nCount) != NULL && nCount > 0) { m_vecTradeItem.resize(nCount); }
//
//	//�汾(�Ƿ���Ҫ���)
//	//////////////////////////////////////////////////////////
//
//	MeXmlElement* pTrade = pRoot->FirstChildElement("TradeCenter");
//	if (pTrade == NULL) { return false; }
//
//	//�ۿ�
//	int nDiscountPercent;
//	if (pTrade->Attribute("DiscountPercent", &nDiscountPercent) == NULL || nDiscountPercent < 0 || nDiscountPercent > 100)
//    { return false; }
//	TradeItem::DiscountPercent = nDiscountPercent;
//
//    MeXmlElement* pTypeElement = pTrade->FirstChildElement("Type");
//    while ( pTypeElement != NULL )
//    {
//        TradeItem xTradeItem;
//
//        Common::_tstring strTypeName = "";          // ��Ʒ����
//        strTypeName.fromUTF8( pTypeElement->Attribute("Name") );
//        xTradeItem.TypeName = strTypeName;
//        if ( !xTradeItem.TypeName.empty() )
//        {
//            MeXmlElement* pItem = pTrade->FirstChildElement("Item");
//            while (pItem != NULL)
//            {	
//                //id
//                int nItemId;
//                if (pItem->Attribute("ItemId", &nItemId) == NULL || nItemId < 0 || nItemId >= InvalidLogicNumber) 
//                { return false; }
//                xTradeItem.ItemId = nItemId;
//
//                //�۸�
//                int nOriginalPrice;
//                if (pItem->Attribute("OriginalPrice", &nOriginalPrice) == NULL || nOriginalPrice < 0)
//                { return false; }
//                xTradeItem.OriginalPrice = nOriginalPrice;
//
//                //���ռ۸�
//                int nFinalDiscountPrice;
//                if (pItem->Attribute("FinalDiscountPrice", &nFinalDiscountPrice) == NULL || nFinalDiscountPrice < 0)
//                { return false; }
//                xTradeItem.FinalDiscountPrice = nFinalDiscountPrice;
//
//                // ���蹺��ȯ
//                int nTicketPrice;
//                if (pItem->Attribute("TicketPrice", &nTicketPrice) == NULL || nTicketPrice < 0)
//                { return false; }
//                xTradeItem.TicketPrice = nTicketPrice;
//
//                //��������
//                int nCount;
//                if (pItem->Attribute("Count", &nCount) == NULL || nCount < 0) 
//                { return false; }
//                xTradeItem.Count = nCount;
//                xTradeItem.CurrentCount = nCount;
//
//                //ˢ������
//                int nRefreshInterval;
//                if (pItem->Attribute("RefreshInterval", &nRefreshInterval) == NULL || nRefreshInterval < 0) 
//                { return false; }
//                xTradeItem.RefreshInterval = nRefreshInterval;
//
//                //�Ƿ�����
//                int nIsHot;
//                if (pItem->Attribute("IsHot", &nIsHot) == NULL || nIsHot < 0 || nIsHot > 1) 
//                { return false; }
//                xTradeItem.IsHot = nIsHot;
//
//                //�Ƿ���Ʒ
//                int nIsNew;
//                if (pItem->Attribute("IsNew", &nIsNew) == NULL || nIsNew < 0 || nIsNew > 1) 
//                { return false; }
//                xTradeItem.IsNew = nIsNew;
//
//                if ( !AddTradeItem(xTradeItem) ) 
//                { return false; }
//
//                //next
//                pItem = pItem->NextSiblingElement();
//            }
//        }
//        pTypeElement = pTypeElement->NextSiblingElement();
//    }
//    return true;
//}
//
//TradeItem* TradeCenterConfig::GetTradeItemByIndex(unsigned int nIndex)
//{
//	if (nIndex < 0 || nIndex >= m_mapTradeItem.size())
//	{
//		return NULL;
//	}
//
//    TradeItemMapIter iter = m_mapTradeItem.begin();
//    advance( iter, nIndex );
//
//    return &( iter->second );
//}
//
//TradeItem* TradeCenterConfig::GetTradeItemByItemID( unsigned short nItemId )
//{
//    TradeItemMapIter iter = m_mapTradeItem.find( nItemId );
//	if (iter != m_mapTradeItem.end())
//	{
//		return &(iter->second );
//	}
//
//	return NULL;
//}
//
////����dwTime���Ƿ�����  ÿ1�����ж�һ��
//bool TradeCenterConfig::RefurbishCount(DWORD dwTime)
//{
//	TradeItemMapIter iter = m_mapTradeItem.begin();
//	TradeItemMapIter end = m_mapTradeItem.end();
//	
//	for ( ; iter != end; ++iter)
//	{
//		if (iter->second.RefreshInterval == 0)		//����ˢ��
//		{
//			//ÿ������5���ˢ��һ��
//			SYSTEMTIME xTime;
//			::GetLocalTime(&xTime);
//			if (xTime.wHour == 17 && xTime.wMinute == 30)
//			{
//				iter->second.CurrentCount = iter->second.Count;
//			}
//		}
//		else 
//		{
//			if (dwTime % iter->second.RefreshInterval == 0)
//			{
//				iter->second.CurrentCount = iter->second.Count;
//			}			
//		}
//	}
//	return TRUE;
//}
//
//bool TradeCenterConfig::AddTradeItemTypeName( std::string& strType, unsigned short ustItemID )
//{
//    TypeMapIter iter = m_mapType.find( strType );
//    if ( iter != m_mapType.end() )
//    {
//        std::vector<unsigned short>::iterator viter = find( iter->second.begin(), iter->second.end(), ustItemID );
//        if ( viter == iter->second.end() )
//        {
//            iter->second.push_back( ustItemID );
//        }
//        else
//        {
//            return false;
//        }
//    }
//    else
//    {
//        std::vector<unsigned short> vecItemID;
//        vecItemID.push_back( ustItemID );
//        m_mapType.insert( make_pair( strType, vecItemID ) );
//    }
//    return true;
//}
//bool TradeCenterConfig::RemoveTradeItemTypeName( std::string& strType, unsigned short ustItemID )
//{
//    TypeMapIter iter = m_mapType.find( strType );
//    if ( iter != m_mapType.end() )
//    {
//        std::vector<unsigned short>::iterator viter = find( iter->second.begin(), iter->second.end(), ustItemID );
//        if ( viter != iter->second.end() )
//        {
//            iter->second.erase( viter );
//            if ( iter->second.empty() )
//            {
//                m_mapType.erase( iter );
//            }
//            return true;
//        }
//    }
//
//    return false;
//}
//
//void TradeCenterConfig::GetTradeItemIDByType( std::string& strType, std::vector<unsigned short>& vecItemID )
//{
//    vecItemID.clear();
//
//    TypeMapIter iter = m_mapType.find( strType );
//    if ( iter != m_mapType.end() )
//    {
//        vecItemID = iter->second;
//    }
//}
//
///////////////////////////////////////////////////////////////////////////////////////////
////�༭�����ʹ��
////////////////////////////////////////////////////////////////////////////////////////////
//bool TradeCenterConfig::SaveTradeItemConfig(const char* szFile)
//{
//	//if (szFile == NULL || *szFile == 0)
//	//{
//	//	return false;
//	//}
//
//	//MeXmlDocument xMeXmlDoc;
//	//xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
//
//	//MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild(MeXmlElement("Project"))->ToElement();
//	//if (pRoot == NULL) { return false; }
//
//	//Common::_tstring strName = "HeroOnline";
//	//pRoot->SetAttribute("Name", strName.toUTF8().c_str());
//
//	////Common::_tstring strVersion = ApplicationConfig::Instance().GetFullVersion();		
//	//pRoot->SetAttribute("Version", ""/*strVersion.toUTF8().c_str()*/);
//
//	////pRoot->SetAttribute("TotalItemCount", GetTradeItemCount());
//
//	//MeXmlElement* pTrade = pRoot->InsertEndChild(MeXmlElement("TradeCenter"))->ToElement();
//	//if(pTrade == NULL) { return false; }
//	//pTrade->SetAttribute("DiscountPercent", TradeItem::DiscountPercent);
//
//	//TradeItemMapIter iter = m_mapTradeItem.begin();
//	//TradeItemMapIter end  = m_mapTradeItem.end();
//	//for (; iter != end; ++iter)
//	//{
//	//	MeXmlElement* pItem = pTrade->InsertEndChild(MeXmlElement("Item"))->ToElement();
//	//	if (pItem == NULL) { return false; }
//	//	
//	//	pItem->SetAttribute("ItemId", iter->ItemId);
//	//	pItem->SetAttribute("Price", iter->Price);
//	//	pItem->SetAttribute("DiscountPrice", iter->DiscountPrice);
//	//	pItem->SetAttribute("Count", iter->Count);
//	//	pItem->SetAttribute("RefreshInterval", iter->RefreshInterval);
//	//	pItem->SetAttribute("IsHot", iter->IsHot);
//	//	pItem->SetAttribute("IsNew", iter->IsNew);		
//	//}
//
//	//return xMeXmlDoc.SaveFile(szFile);
//    return true;
//}
//
////���һ����Ʒ bReplace == true  ��ͬ��Ҫ����
//bool TradeCenterConfig::AddTradeItem( TradeItem &xTradeItem, bool bReplace /* = false */ )
//{
//    TradeItemMapIter iter = m_mapTradeItem.find( xTradeItem.ItemId );
//	if ( iter != m_mapTradeItem.end() )
//	{
//		if ( bReplace )
//		{
//            iter->second = xTradeItem;
//            AddTradeItemTypeName( xTradeItem.TypeName, xTradeItem.ItemId );
//        }
//
//		return bReplace;
//	}
//    else
//    {
//        m_mapTradeItem.insert( make_pair( xTradeItem.ItemId, xTradeItem ) );
//        AddTradeItemTypeName( xTradeItem.TypeName, xTradeItem.ItemId );
//    }
//
//    return true;
//}
//
//bool TradeCenterConfig::RemoveTradeItem( unsigned short nItemId )
//{
//    TradeItemMapIter iter = m_mapTradeItem.find( nItemId );
//	if ( iter != m_mapTradeItem.end() )
//	{
//        RemoveTradeItemTypeName( iter->second.TypeName, nItemId );
//		m_mapTradeItem.erase(iter);
//		return true;
//	}
//
//	return false;
//}
//
//bool TradeCenterConfig::ChangeDiscountPercent(unsigned char nDiscountPercent)
//{
//	if (nDiscountPercent < 0 || nDiscountPercent > 100)
//	{
//		return false;
//	}
//
//	TradeItem::DiscountPercent = nDiscountPercent;
//
//	return true;
//}