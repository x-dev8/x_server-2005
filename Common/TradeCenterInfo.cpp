#include "TradeCenterInfo.h"
#include "tstring.h"
#include "zlib/zlib.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"

#ifndef GAME_CLIENT
#include "ConfigReloader.h"
#endif

class CMyFind
{
public:
    CMyFind()
    {

    }

    CMyFind(CTradeCenterInfo::cTypeSort &sort)
    {
        m_sort = sort;
    }
    ~CMyFind()
    {

    }
public:
    bool operator()(CTradeCenterInfo::cTypeSort &sort2)
    {
        if(m_sort.m_Name.compare(sort2.m_Name.c_str()) != 0)
            return false;
        return true;
    }
    CTradeCenterInfo::cTypeSort m_sort;
};

CTradeCenterInfo::CTradeCenterInfo()
{
    m_TradeMap.m_DisCountPercent = 100;
    m_TradeMap.m_Radio = 5;
    m_TradeMap.m_vecDisSet.clear();
    m_TradeMap.m_vecShortcuts.clear();
    m_itemSet.clear();
    m_itemAllVec.clear();
	nReloadSignal = 0;

    gnFileBufferSize = 0;
    gnZibFileBufferSize = 0;
    memset( gszFileBuffer, 0, sizeof(gszFileBuffer));
    memset( gszZibFileBuffer, 0, sizeof(gszZibFileBuffer));
}

CTradeCenterInfo::~CTradeCenterInfo()
{
    m_TradeMap.m_vecDisSet.clear();
    m_TradeMap.m_vecShortcuts.clear();
	m_itemSet.clear();
	m_itemAllVec.clear();
}

bool CTradeCenterInfo::LoadResourceConfig(const char* pszConfig)
{
    if(pszConfig == NULL)	{ return false; }

    Clear();

    {
        MeXmlDocument xiDoc;
        if(!xiDoc.LoadFile(pszConfig))
        {
            char szWord[261];
            sprintf_s(szWord,sizeof(szWord) - 1,"%s Open File failed!",pszConfig);
            MessageBox(NULL,szWord,"Warnning",MB_OK);
            return false;
        }

        MeXmlElement *pElemItem = xiDoc.FirstChildElement("Project");
        if(pElemItem == NULL)
            return false;

        //遍历TradeCenter
        pElemItem = pElemItem->FirstChildElement("TradeCenter");
        if(NULL == pElemItem)
            return false;

        int nValue = -1;
        pElemItem->Attribute("DiscountPercent",&nValue);
        m_TradeMap.m_DisCountPercent = nValue;

        pElemItem->Attribute("Radio",&nValue);
        m_TradeMap.m_Radio = nValue;
        if(m_TradeMap.m_Radio <=0)
            return false;
        
        bool bResult = false;
        bResult = LoadTypes(pElemItem);  //载入Types类型
        if(!bResult)
            return false;

        bResult = LoadShortCut(pElemItem);  //载入快捷键
        if(!bResult)
            return false;

        GetNewItem(m_New);  //获得新品
        GetHotItem(m_Hot);  //获得热卖
		/*GetYuanbaoItem();
		GetJifenItem();
		GetBangjinItem();*/
#ifndef _TRADECENTER_
        GetAllItemByType();
#endif
    }

    // 保存文件到内存
    std::fstream file;
    file.open(_tUNICODECHAR(pszConfig), std::ios::in | std::ios::binary );
    if ( !file.is_open() )
    { return false; }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    if ( size >= ECD_ConfigBufferMaxSize)
    { return false; }
    gnFileBufferSize = size;
    file.seekp(0, std::ios::beg);
    file.read( gszFileBuffer, static_cast<std::streamsize>(gnFileBufferSize) );
    file.close();

    gnZibFileBufferSize = ECD_ConfigBufferMaxSize;
    compress( gszZibFileBuffer, (uLongf*)&gnZibFileBufferSize, (uint8*)gszFileBuffer, gnFileBufferSize ); 

    if ( gnZibFileBufferSize>= ECD_ConfigBufferMaxSize )
    { return false; }
    return true;
}

bool CTradeCenterInfo::LoadConfigFromBuffer(const uint8* buffer, uint32 bufferSize, bool bBufferIsZip /*= true*/ )
{
    if( NULL == buffer || 0 == bufferSize || bufferSize >= ECD_ConfigBufferMaxSize)
    { return false; }
    
    Clear();

    {
        MeXmlDocument xiDoc;

        if ( bBufferIsZip )
        { // 如果是压缩buffer
            gnZibFileBufferSize = bufferSize;
            memcpy_s( gszZibFileBuffer, sizeof(gszZibFileBuffer), buffer, bufferSize );

            gnFileBufferSize = sizeof(gszFileBuffer);
            uncompress( (uint8*)gszFileBuffer, &gnFileBufferSize, gszZibFileBuffer, gnZibFileBufferSize);
            if ( gnFileBufferSize >= ECD_ConfigBufferMaxSize)
            { return false; }
        }
        else
        {
            gnFileBufferSize = bufferSize;
            memcpy_s( gszFileBuffer, sizeof(gszFileBuffer), buffer, bufferSize );

            gnZibFileBufferSize = sizeof( gszZibFileBuffer );
            compress( gszZibFileBuffer, (uLongf*)&gnZibFileBufferSize, (uint8*)gszFileBuffer, gnFileBufferSize ); 
            if ( gnZibFileBufferSize >= ECD_ConfigBufferMaxSize)
            { return false; }
        }
        
        xiDoc.Parse( (char*)gszFileBuffer );
//         if( xiDoc.Error() )
//         { return false; }

        MeXmlElement *pElemItem = xiDoc.FirstChildElement("Project");
        if(pElemItem == NULL)
        { return false; }

        //遍历TradeCenter
        pElemItem = pElemItem->FirstChildElement("TradeCenter");
        if(NULL == pElemItem)
        { return false; }

        int nValue = -1;
        pElemItem->Attribute("DiscountPercent",&nValue);
        m_TradeMap.m_DisCountPercent = nValue;

        pElemItem->Attribute("Radio",&nValue);
        m_TradeMap.m_Radio = nValue;
        if(m_TradeMap.m_Radio <=0)
        { return false; }

        bool bResult = false;
        bResult = LoadTypes(pElemItem);  //载入Types类型
        if(!bResult)
            return false;

        bResult = LoadShortCut(pElemItem);  //载入快捷键
        if(!bResult)
            return false;

        GetNewItem(m_New);  //获得新品
        GetHotItem(m_Hot);  //获得热卖
		/*GetYuanbaoItem();
		GetJifenItem();
		GetBangjinItem();*/
#ifndef _TRADECENTER_
        GetAllItemByType();
#endif
    }

    return true;
}

#ifdef _TRADECENTER_
bool CTradeCenterInfo::SaveConfig(const char* pszPath)
{
    if(!pszPath)
        return false;

    MeXmlDocument tiDoc;

    Common::_tstring strXml = "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\" ?>  \
        <!--\n\
        DiscountPercent    总体折扣 \n \
        Name               商品类型 \n \
        ItemId             物品id \n  \
        OriginalPrice      原始价格 \n  \
        FinalDiscountPrice 最终价格 \n  \
          TicketPrice        所需购物券\n \
        Count              商品数量 \n     \
        RefreshInterval    刷新间隔（分钟）\n \
        IsHot              热卖 \n \
        IsNew              新品 \n-->";

	tiDoc.InsertEndChild(MeXmlDeclaration("1.0","UTF-8","yes"));
	MeXmlElement* pRoot = tiDoc.InsertEndChild(("Project"))->ToElement();
	if (pRoot == NULL) 
	{ return false; }
	pRoot->append_node(tiDoc.RetriveCommentElement(strXml.toUTF8().c_str()));

//     if(!tiDoc.Parse(strXml.toUTF8().c_str()))
    {
        MeXmlElement *pElem = tiDoc.InsertEndChild(("Project"))->ToElement();
        if(pElem == NULL)
            return false;

        pElem->SetAttribute("Name","HeroOnline");
        pElem->SetAttribute("Version","");

        //TradeCenter
        pElem = pElem->InsertEndChild(("TradeCenter"))->ToElement();
        if(pElem == NULL)
            return false;

        MeXmlElement *pElemCenter = pElem;

        pElem->SetAttribute("DiscountPercent",m_TradeMap.m_DisCountPercent);

        pElem->SetAttribute("Radio",m_TradeMap.m_Radio);

        if(!SaveTypes(pElem,m_TradeMap.m_vecDisSet))
            return false;

        if(!SaveShortCut(pElemCenter))
            return false;

        return tiDoc.SaveFile(pszPath);
    }
    return false;
}

bool CTradeCenterInfo::SaveShortCut(MeXmlElement *pElemItem)
{
    if(!pElemItem)
        return false;

    MeXmlElement *pElemShortcuts = pElemItem->InsertEndChild(("Shortcuts"))->ToElement();
    if(NULL == pElemShortcuts)
        return false;

    int nSize = m_TradeMap.m_vecShortcuts.size();
    for (int i = 0;i < nSize;++i)
    {
        MeXmlElement* pShortType  = pElemShortcuts->InsertEndChild(("Type"))->ToElement();
        Common::_tstring strValue = m_TradeMap.m_vecShortcuts[i].m_UiName;

        pShortType->SetAttribute("Name",strValue.toUTF8().c_str());

        MeXmlElement* pElemItems = pShortType->InsertEndChild(("Items"))->ToElement();

        int nItemAmount = m_TradeMap.m_vecShortcuts[i].m_vecItemIdSet.size();
        for (int n = 0;n < nItemAmount;++n)
        {
            MeXmlElement* pElemItem = pElemItems->InsertEndChild(("Item"))->ToElement();
            pElemItem->SetAttribute("ItemId",m_TradeMap.m_vecShortcuts[i].m_vecItemIdSet[n]);

        }
    }

    return true;
}


bool CTradeCenterInfo::SaveTypes(MeXmlElement *pElemItem,std::vector<cTypeSort> &typeSort)
{
    if(!pElemItem)
        return false;

    //Types
    MeXmlElement *pElemSubItem = pElemItem->InsertEndChild(("Types"))->ToElement();
    if(pElemSubItem == NULL)
        return false;

    //Type
    cTradeGlobalData::Iter iterDis    = typeSort.begin(); 
    cTradeGlobalData::Iter iterDisEnd = typeSort.end();
    for (;iterDis != iterDisEnd;++iterDis)
    {
        MeXmlElement *pElemType;
        pElemType = pElemSubItem->InsertEndChild(("Type"))->ToElement();
        if(pElemType == NULL)
            return false;

        Common::_tstring typeStr = iterDis->m_Name;
        pElemType->SetAttribute("Name",typeStr.toUTF8().c_str());

        cTypeSort::Iter iter = iterDis->m_vecSet.begin();
        cTypeSort::Iter iterEnd = iterDis->m_vecSet.end();
        for (;iter != iterEnd;++iter)
        {
            MeXmlElement *pSubType = NULL;
            pSubType = pElemType->InsertEndChild(("TypeChild"))->ToElement();
            if(!pSubType)
                return false;

            Common::_tstring strValue = iter->m_NameSort;
            pSubType->SetAttribute("Name",strValue.toUTF8().c_str());

            if(!SaveBroadCast(pSubType,iter->m_mapTradeInfo1))
                return false;

            if(!SaveItem(pSubType,iter->m_vecItemSet1))
                return false;
        }
    }

    return true;
}


bool CTradeCenterInfo::SaveBroadCast(MeXmlElement *pElemSubItem,std::map<int,cTradeInfo> &mapSet)
{
    if(!pElemSubItem)
        return false;

    MeXmlElement *pBroadcasts = pElemSubItem->InsertEndChild(("Broadcasts"))->ToElement();
    if(pBroadcasts != NULL)
    {
        cTradeSubSort::IterMap1 iter = mapSet.begin();
        cTradeSubSort::IterMap1 iterEnd = mapSet.end();

        for (;iter != iterEnd;++iter)
        {
            MeXmlElement *pElemSubItem = pBroadcasts->InsertEndChild(("Broadcast"))->ToElement();
            if(pElemSubItem == NULL)
                return false;

            pElemSubItem->SetAttribute("Id",iter->second.nId);
            Common::_tstring strValue = iter->second.infoString;

            pElemSubItem->SetAttribute("Value",strValue.toUTF8().c_str());
        }
    }

    return true;
}

bool CTradeCenterInfo::SaveItem(MeXmlElement* pElemSubItem,std::vector<cTradeItem> &itemSet)
{
    if(!pElemSubItem)
        return false;

    MeXmlElement *pElemItems = pElemSubItem->InsertEndChild(("Items"))->ToElement();
    if(pElemItems != NULL)
    {
        cTradeSubSort::Iter1 iterSort  = itemSet.begin();
        cTradeSubSort::Iter1 iterSorEnd = itemSet.end();

        for (;iterSort != iterSorEnd;++iterSort)
        {
            MeXmlElement *pElemSubItem = pElemItems->InsertEndChild(("Item"))->ToElement();
            if(pElemSubItem == NULL)
                return false;

            pElemSubItem->SetAttribute("ItemId",iterSort->m_ItemID);
            pElemSubItem->SetAttribute("OriginalPrice",iterSort->m_OriginalPrice);
            pElemSubItem->SetAttribute("FinalDiscountPrice",iterSort->m_FinalDiscountPrice);
            pElemSubItem->SetAttribute("TicketPrice",iterSort->m_TicketPrice);
            pElemSubItem->SetAttribute("Count",iterSort->m_Count);
            pElemSubItem->SetAttribute("RefreshInterval",iterSort->m_RefreshInterval);
            pElemSubItem->SetAttribute("IsHot",iterSort->m_isHot);
            pElemSubItem->SetAttribute("IsNew",iterSort->m_isNew);

            Common::_tstring strValue = iterSort->m_strTimeLimit;
            pElemSubItem->SetAttribute("TimeLimit",strValue.toUTF8().c_str());

            pElemSubItem->SetAttribute("ShowRank",iterSort->m_Rank);

            pElemSubItem->SetAttribute("IsNeedNpc",iterSort->m_bNeedNpc);

            pElemSubItem->SetAttribute("MapId",iterSort->m_nMapId);

            pElemSubItem->SetAttribute("NpcId",iterSort->m_nNpcId);
        }
    }

    return true;
}

#endif

void CTradeCenterInfo::OnReloadFinished()
{
#ifndef GAME_CLIENT
	nReloadSignal = 1;
	theConfigReloader.OnReloadFinishedForRegister(eRCFGTYPE_SHOPCENTER,this);
#endif
	
}
CTradeCenterInfo::cTypeSort* CTradeCenterInfo::GetTradeParentSort(const char* pszName)
{
    cTradeGlobalData::Iter iter = m_TradeMap.m_vecDisSet.begin();
    cTradeGlobalData::Iter end  = m_TradeMap.m_vecDisSet.end();
    for (;iter != end;++iter)
    {
        if(strcmp(iter->m_Name.c_str(),pszName) == 0)
            return &(*iter);
    }
    return NULL;
}


CTradeCenterInfo::cTradeSubSort* CTradeCenterInfo::GetTradeSubSort(cTypeSort* pTypeSort,const char* pszName)
{
    if(!pTypeSort || !pszName)
        return NULL;

    cTypeSort::Iter it = pTypeSort->m_vecSet.begin();
    cTypeSort::Iter end = pTypeSort->m_vecSet.end();

    for(;it != end;++it)
    {
        if(it->m_NameSort.compare(pszName) == 0)
            return &(*it);
    }

    return NULL;
}


char CTradeCenterInfo::GetParentType(const char *pszName)
{
	if(!pszName)
	{
		return ECD_ParentType_Yuanbao;
	}
	
	if (strcmp(pszName,theXmlString.GetString(eText_ShopCenter_YuanBao)) == 0)
	{
		return ECD_ParentType_Yuanbao;
	}
	else if(strcmp(pszName,theXmlString.GetString(eText_ShopCenter_Bangjin)) == 0)
	{
		return ECD_ParentType_Bangjin;
	}
	else if (strcmp(pszName,theXmlString.GetString(eText_ShopCenter_Jifen)) == 0)
	{
		return ECD_ParentType_Jifen;
	}
	return ECD_ParentType_Yuanbao;

}
bool CTradeCenterInfo::InsertTradeParentType(const char *pszName)
{
    cTradeGlobalData::Iter iter = m_TradeMap.m_vecDisSet.begin();
    cTradeGlobalData::Iter end  = m_TradeMap.m_vecDisSet.end();

    CTradeCenterInfo::cTypeSort sort;
    sort.m_Name = pszName;
    sort.m_vecSet.clear();
    cTradeGlobalData::Iter itt = find_if(iter,end,CMyFind(sort));
    if(itt != end)
        return false;

    cTypeSort tradeSort;
    tradeSort.m_Name = pszName;
	tradeSort.chType = GetParentType(pszName);
    tradeSort.m_vecSet.clear();
    m_TradeMap.m_vecDisSet.push_back(tradeSort);

    return true;
}

bool  CTradeCenterInfo::InsertTradeSubType(const char *pParentName,const char* pszName)
{
    if(!pParentName || !pszName)
        return false;

    cTypeSort *pSort = GetTradeParentSort(pParentName);
    if(!pSort)
        return false;

    cTypeSort::Iter it = pSort->m_vecSet.begin();
    cTypeSort::Iter end = pSort->m_vecSet.end();

    for (;it != end;++it)
    {
        if(it->m_NameSort.compare(pszName) == 0)
            return false;
    }

    cTradeSubSort tradeSort;
    tradeSort.m_NameSort = pszName;
    tradeSort.m_vecItemIdSet.clear();
    tradeSort.m_mapTradeInfo.clear();

    pSort->m_vecSet.push_back(tradeSort);

    return true;
}


bool CTradeCenterInfo::DelTradeParentType(const char *pszName)
{
    cTradeGlobalData::Iter iter = m_TradeMap.m_vecDisSet.begin();
    cTradeGlobalData::Iter end  = m_TradeMap.m_vecDisSet.end();

    for (;iter != end;++iter)
    {
        if(strcmp(iter->m_Name.c_str(),pszName) == 0)
        {
                m_TradeMap.m_vecDisSet.erase(iter);
                return true;
        }
    }
    return false;
}

bool  CTradeCenterInfo::DelTradeSubType(const char* pParentName,const char *pszName)
{
    assert(0&&"字符串为空");
    if(!pszName || !pParentName)
        return false;

    cTypeSort *pSort = GetTradeParentSort(pParentName);
    if(!pSort)
        return false;

    cTypeSort::Iter it = pSort->m_vecSet.begin();
    cTypeSort::Iter end = pSort->m_vecSet.end();

    for (;it != end;++it)
    {
        if(it->m_NameSort.compare(pszName) == 0)
        {
            pSort->m_vecSet.erase(it);
            return true;
        }
    }

    return false;
}


bool CTradeCenterInfo::SetTradeDiscount(int nDiscount)
{
    if(nDiscount < 0 || nDiscount > 100)
        return false;

    m_TradeMap.m_DisCountPercent = nDiscount;
    return true;
}

void CTradeCenterInfo::Clear()
{
    m_TradeMap.m_vecDisSet.clear();
    m_TradeMap.m_vecShortcuts.clear();

    m_New.clear();
    m_Hot.clear();
	
    m_TradeInfo.clear();

	m_mapYuanbao.clear();
	m_mapBangjin.clear();
	m_mapJifen.clear();

	gnFileBufferSize = 0;
	gnZibFileBufferSize = 0;
	memset( gszFileBuffer, 0, sizeof(gszFileBuffer));
	memset( gszZibFileBuffer, 0, sizeof(gszZibFileBuffer));
	m_itemSet.clear();
	m_itemAllVec.clear();

	m_itemAllVec.resize(500);
}

bool CTradeCenterInfo::SetTradeParentType(const char* pszSrc,const char* pszDes)
{
    if(pszSrc == NULL || pszDes == NULL)
        return false;

    cTradeGlobalData::Iter iter = m_TradeMap.m_vecDisSet.begin();
    cTradeGlobalData::Iter end  = m_TradeMap.m_vecDisSet.end();


    CTradeCenterInfo::cTypeSort sort;
    sort.m_Name = pszSrc;
    sort.m_vecSet.clear();
    cTradeGlobalData::Iter itt = find_if(iter,end,CMyFind(sort));
    if(itt == end)
        return false;

    itt->m_Name = pszDes;
    return true;
}

bool  CTradeCenterInfo::SetTradeSubType(const char* pParentName,const char* pszSrcName,const char *pszDestName)
{
    if(!pParentName || !pszSrcName || !pszDestName)
       return false;

    cTypeSort *pSort = GetTradeParentSort(pParentName);
    if(!pSort)
        return false;

    cTypeSort::Iter it = pSort->m_vecSet.begin();
    cTypeSort::Iter end = pSort->m_vecSet.end();

    for (;it != end;++it)
    {
        if(it->m_NameSort.compare(pszSrcName) == 0)
        {
            it->m_NameSort = pszDestName;
            return true;
        }
    }
    return false;
}


CTradeCenterInfo::cTradeItem* CTradeCenterInfo::GetTradeItemByIndex( unsigned int nIndex ,char chType)
{
	map<uint16,cTradeItem*>::iterator iter;
	map<uint16,cTradeItem*>::iterator end;
	switch(chType)
	{
	case ECD_ParentType_Yuanbao:
		 iter = m_mapYuanbao.begin();
		 end  = m_mapYuanbao.end();
		for (int i = 0;iter != end; ++iter,++i)
		{
			if(i == nIndex)
				return (iter->second);
		}
		return NULL;
		break;
	case ECD_ParentType_Bangjin:
		 iter = m_mapBangjin.begin();
		 end  = m_mapBangjin.end();
		for (int i = 0;iter != end; ++iter,++i)
		{
			if(i == nIndex)
				return (iter->second);
		}
		return NULL;
		break;
	case ECD_ParentType_Jifen:
		 iter = m_mapJifen.begin();
		 end  = m_mapJifen.end();
		for (int i = 0;iter != end; ++iter,++i)
		{
			if(i == nIndex)
				return (iter->second);
		}
		return NULL;
		break;
	default:
		return NULL;
	}
    return NULL;
}

CTradeCenterInfo::cTradeItem* CTradeCenterInfo::GetTradeItemByItemID( unsigned short nItemId ,char chType)
{
	map<uint16,cTradeItem*>::iterator itr;
	switch(chType)
	{
	case ECD_ParentType_Yuanbao:
		itr = m_mapYuanbao.find(nItemId);
		if(itr != m_mapYuanbao.end())
			return itr->second;
		break;
	case ECD_ParentType_Bangjin:
		itr = m_mapBangjin.find(nItemId);
		if(itr != m_mapBangjin.end())
			return itr->second;
		break;
	case ECD_ParentType_Jifen:
		itr = m_mapJifen.find(nItemId);
		if(itr != m_mapJifen.end())
			return itr->second;
		break;
	default:
		return NULL;
	}

    IterItem iter = m_itemSet.find(nItemId);
    if(iter != m_itemSet.end())
        return iter->second;

    return NULL;
}

uint32  CTradeCenterInfo::GetTradeItemIndexByItemID( unsigned short nItemId )
{
    IterItem iter = m_itemSet.find(nItemId);
    if(iter != m_itemSet.end())
        return iter->second->m_ItemID;

    return -1;
}


uint32 CTradeCenterInfo::GetTradeStringIndexByID(uint32 nId)
{
    IterInfo iter = m_TradeInfo.begin();
    IterInfo end  = m_TradeInfo.end();
    for (;iter != end;++iter)
    {
        if(iter->nId == nId)
            return (m_TradeInfo.begin() - iter);
    }
    return -1;
}

CTradeCenterInfo::cTradeInfo*  CTradeCenterInfo::GetTradeStringByID(uint32 nId)
{
    IterInfo iter = m_TradeInfo.begin();
    IterInfo end  = m_TradeInfo.end();
    for (;iter != end;++iter)
    {
        if(iter->nId == nId)
            return &(*iter);
    }
    return NULL;
}

CTradeCenterInfo::cTradeInfo*  CTradeCenterInfo::GetTradeStringByIndex(uint32 nIndex)
{
    if(nIndex <0 || nIndex>= m_TradeInfo.size())
        return NULL;

    return &m_TradeInfo[nIndex];
}

long CTradeCenterInfo::GetHotItem(std::vector<uint16> &itemSet)
{
    IterItem iter = m_itemSet.begin();
    IterItem end  = m_itemSet.end();
    for (;iter != end;++iter)
    {
        if(iter->second->m_isHot)
            itemSet.push_back(iter->second->m_ItemID);
    }
    return itemSet.size();
}

long CTradeCenterInfo::GetNewItem(std::vector<uint16> &itemSet)
{
    IterItem iter = m_itemSet.begin();
    IterItem end  = m_itemSet.end();
    for (;iter != end;++iter)
    {
        if(iter->second->m_isNew)
            itemSet.push_back(iter->second->m_ItemID);
    }
    return itemSet.size();
}

long CTradeCenterInfo::GetYuanbaoItem()
{
	IterItem iter = m_itemSet.begin();
	IterItem end  = m_itemSet.end();
	for (;iter != end;++iter)
	{
		if(iter->second->m_FinalDiscountPrice != 0)
		{
			m_mapYuanbao.insert(std::make_pair(iter->second->m_ItemID,iter->second));			
			if (iter->second->m_isHot)
			{
				m_mapYuanbaoHot.insert(std::make_pair(iter->second->m_ItemID,iter->second));
			}
			if (iter->second->m_isNew)
			{
				m_mapYuanbaoNew.insert(std::make_pair(iter->second->m_ItemID,iter->second));
			}
		}
	}
	return m_mapYuanbao.size();
}

long CTradeCenterInfo::GetBangjinItem()
{
	IterItem iter = m_itemSet.begin();
	IterItem end  = m_itemSet.end();
	for (;iter != end;++iter)
	{
		if(iter->second->m_TicketPrice != 0)
		{
			m_mapBangjin.insert(std::make_pair(iter->second->m_ItemID,iter->second));			
			if (iter->second->m_isHot)
			{
				m_mapBangjinHot.insert(std::make_pair(iter->second->m_ItemID,iter->second));
			}
			if (iter->second->m_isNew)
			{
				m_mapBangjinNew.insert(std::make_pair(iter->second->m_ItemID,iter->second));
			}
		}
	}
	return m_mapBangjin.size();
}

long CTradeCenterInfo::GetJifenItem()
{
	IterItem iter = m_itemSet.begin();
	IterItem end  = m_itemSet.end();
	for (;iter != end;++iter)
	{
		if(iter->second->m_ConsumeScore != 0)
		{
			m_mapJifen.insert(std::make_pair(iter->second->m_ItemID,iter->second));
		}
	}
	return m_mapJifen.size();
}

bool CTradeCenterInfo::InsertYuanbaoItem(cTradeItem* pTradeItem)
{
	if (!pTradeItem)
	{
		return false;
	}
	if(pTradeItem->m_FinalDiscountPrice != 0)
	{
		mapYuanbao::iterator itr = m_mapYuanbao.find(pTradeItem->m_ItemID);
		if (itr == m_mapYuanbao.end())
		{
			m_mapYuanbao.insert(std::make_pair(pTradeItem->m_ItemID,pTradeItem));
			return true;
		}
	}
	return false;
}

bool CTradeCenterInfo::InsertJifenItem(cTradeItem* pTradeItem)
{
	if (!pTradeItem)
	{
		return false;
	}
	if(pTradeItem->m_ConsumeScore != 0)
	{
		mapJifen::iterator itr = m_mapJifen.find(pTradeItem->m_ItemID);
		if (itr == m_mapJifen.end())
		{
			m_mapJifen.insert(std::make_pair(pTradeItem->m_ItemID,pTradeItem));
			return true;
		}
	}
	return false;
}

bool CTradeCenterInfo::InsertBangjinItem(cTradeItem* pTradeItem)
{
	if (!pTradeItem)
	{
		return false;
	}
	if(pTradeItem->m_TicketPrice != 0)
	{
		mapBangjin::iterator itr = m_mapBangjin.find(pTradeItem->m_ItemID);
		if (itr == m_mapBangjin.end())
		{
			m_mapBangjin.insert(std::make_pair(pTradeItem->m_ItemID,pTradeItem));
			return true;
		}
	}
	return false;
}

CTradeCenterInfo::cTradeItem* CTradeCenterInfo::GetNextItem(bool bFirstItem)
{
    if(bFirstItem)
    { 
        _curIt = m_itemSet.begin();
    }
    
    if(_curIt == m_itemSet.end())
    {
        return NULL; 
    }

    cTradeItem* p = _curIt->second;
    ++_curIt;
    return p;
}

CTradeCenterInfo::cTradeItem*   CTradeCenterInfo::GetNextNewItem(bool bFirstItem)
{
    if(bFirstItem)
        m_curNewIt = m_New.begin();

    if(m_curNewIt == m_New.end())
        return NULL;

    cTradeItem* pItem = m_itemSet[*m_curNewIt];
    ++m_curNewIt;
    return pItem;
}

CTradeCenterInfo::cTradeItem*   CTradeCenterInfo::GetNextHotItem(bool bFirstItem)
{
    if(bFirstItem)
        m_curHotIt = m_Hot.begin();

    if(m_curHotIt == m_Hot.end())
        return NULL;

    cTradeItem* p = m_itemSet[*m_curHotIt];
    
    ++m_curHotIt;
    return p;
}

bool CTradeCenterInfo::GetShortcutsItems(const std::string &type, std::vector<int>* itemIds)
{
    int nSize = m_TradeMap.m_vecShortcuts.size();
    for (int i = 0; i < nSize;++i)
    {
        cTradeShortcuts *pShortcuts = &m_TradeMap.m_vecShortcuts[i];
        if(pShortcuts != NULL && pShortcuts->m_UiName.compare(type) == 0)
        {
            if(itemIds)
            {
                *itemIds = pShortcuts->m_vecItemIdSet;
            }
            return true;
        }
    }
    return false;
}

std::string CTradeCenterInfo::GetShortcutsShopTypeUIID(const std::string& type)
{
    std::string resultType = "ID_CHECKBOX_Type";

    int nSize = m_TradeMap.m_vecShortcuts.size();
    for (int i = 0; i < nSize;++i)
    {
        cTradeShortcuts *pShortcuts = &m_TradeMap.m_vecShortcuts[i];
        if(pShortcuts != NULL && pShortcuts->m_UiName.compare(type) == 0)
        {
            char szWord[43];
            sprintf_s(szWord, sizeof( szWord ) - 1, "%d",pShortcuts->m_TypeID);
            resultType += szWord;
            return resultType;
        }
    }
    return NULL;
}

bool CTradeCenterInfo::LoadItem(MeXmlElement* pElemSubItem,CTradeCenterInfo::cTradeSubSort &cSubSort)
{
    if(!pElemSubItem)
        return false;

    int nValue = -1;
    //Items
    MeXmlElement *pElemItems = pElemSubItem->FirstChildElement("Items");
    if(pElemItems != NULL)
    {
        MeXmlElement *pElemItem = pElemItems->FirstChildElement("Item");

        for (;pElemItem != NULL;pElemItem = pElemItem->NextSiblingElement())
        {
            cTradeItem tradeItem;
            pElemItem->Attribute("ItemId",&nValue);
            tradeItem.m_ItemID = static_cast<unsigned int>(nValue);

            pElemItem->Attribute("OriginalPrice",&nValue);
            tradeItem.m_OriginalPrice = static_cast<unsigned int>(nValue);

            pElemItem->Attribute("FinalDiscountPrice",&nValue);
            tradeItem.m_FinalDiscountPrice = static_cast<unsigned int>(nValue);

            pElemItem->Attribute("TicketPrice",&nValue);
            tradeItem.m_TicketPrice = static_cast<unsigned int>(nValue);

			if(pElemItem->Attribute("ConsumeScore",&nValue)) //lyh++ 商城道具所需 商城积分
			tradeItem.m_ConsumeScore = static_cast<unsigned int>(nValue);

            pElemItem->Attribute("Count",&nValue);
            tradeItem.m_Count = static_cast<unsigned int>(nValue);

            pElemItem->Attribute("RefreshInterval",&nValue);
            tradeItem.m_RefreshInterval = static_cast<unsigned int>(nValue);

            pElemItem->Attribute("IsHot",&nValue);
            tradeItem.m_isHot = static_cast<bool>(nValue);

            pElemItem->Attribute("IsNew",&nValue);
            tradeItem.m_isNew = static_cast<bool>(nValue);

            const char* timeLimit = pElemItem->Attribute("TimeLimit");
            if (timeLimit)
            {
                Common::_tstring time;
                time.fromUTF8(timeLimit);
                tradeItem.m_strTimeLimit = time;
            }

            pElemItem->Attribute("ShowRank", &tradeItem.m_Rank);

            pElemItem->Attribute("IsNeedNpc",&nValue);
            tradeItem.m_bNeedNpc = static_cast<bool>(nValue);

            pElemItem->Attribute("MapId",&tradeItem.m_nMapId);

            pElemItem->Attribute("NpcId",&tradeItem.m_nNpcId);

			m_itemAllVec.push_back(tradeItem);
			cTradeItem* pItem = &m_itemAllVec.back();
			uint32 nIndex = GetTradeItemIndexByItemID(pItem->m_ItemID);
            if(nIndex == -1)
                m_itemSet.insert(make_pair(pItem->m_ItemID,pItem));
            cSubSort.m_vecItemIdSet.push_back(pItem->m_ItemID);

			InsertBangjinItem(pItem);//添加购物卷类商品
			InsertJifenItem(pItem);	//添加积分类商品
			InsertYuanbaoItem(pItem);//添加元宝类商品
#ifdef _TRADECENTER_    
            cSubSort.m_vecItemSet1.push_back(*tradeItem);
#endif
        }
    }

    return true;
}

bool CTradeCenterInfo::LoadBroadCast(MeXmlElement* pElemSubItem,cTradeSubSort &cSubSort)
{
    if(!pElemSubItem)
        return false;

    MeXmlElement *pElemBroad = pElemSubItem->FirstChildElement("Broadcasts");
    if(pElemBroad != NULL)
    {
        MeXmlElement *pElemSubBroad = pElemBroad->FirstChildElement("Broadcast");
        for (;pElemSubBroad != NULL;pElemSubBroad = pElemSubBroad->NextSiblingElement())
        {
            cTradeInfo info;
            pElemSubBroad->Attribute("Id",&info.nId);

            Common::_tstring strTrans;
            strTrans.fromUTF8(pElemSubBroad->Attribute("Value"));

            info.infoString = strTrans;


            uint32 nIndex = -1;
            nIndex = GetTradeStringIndexByID(info.nId);
            if(nIndex == -1)
                nIndex = m_TradeInfo.size();

            cSubSort.m_mapTradeInfo.push_back(nIndex);

            m_TradeInfo.push_back(info);
#ifdef _TRADECENTER_
            cSubSort.m_mapTradeInfo1.insert(make_pair(info.nId,info));
#endif
        }
    }

    return true;
}

bool CTradeCenterInfo::LoadShortCut(MeXmlElement *pElemSubItem)
{
    if(!pElemSubItem)
        return false;

    MeXmlElement *pElemShortcuts = pElemSubItem->FirstChildElement("Shortcuts");
    if(pElemShortcuts)
    {
        MeXmlElement* pShortType = pElemShortcuts->FirstChildElement("Type");
        for (;pShortType != NULL;pShortType = pShortType->NextSiblingElement() )
        {
            cTradeShortcuts shortCuts;
            int nTypeValue = 0;
            pShortType->Attribute("LinkTypeId",&nTypeValue);
            shortCuts.m_TypeID = nTypeValue;

            Common::_tstring strName;
            strName.fromUTF8(pShortType->Attribute("Name"));
            shortCuts.m_UiName = strName;

            MeXmlElement* pElemItems = pShortType->FirstChildElement("Items");
            MeXmlElement* pElemItem  = pElemItems->FirstChildElement("Item");
            for (;pElemItem != NULL; pElemItem = pElemItem->NextSiblingElement() )
            {
                int nItemID = 0;
                pElemItem->Attribute("ItemId",&nItemID);
                shortCuts.m_vecItemIdSet.push_back(nItemID);
            }

            m_TradeMap.m_vecShortcuts.push_back(shortCuts);
        }
    }

    return true;
}

bool CTradeCenterInfo::LoadChildType(MeXmlElement* pElemSubItem,cTypeSort &typeSort)
{
    if(!pElemSubItem)
        return false;

    MeXmlElement *pElemChildType = pElemSubItem->FirstChildElement("TypeChild");

    for (;pElemChildType != NULL;pElemChildType = pElemChildType->NextSiblingElement())
    {
        cTradeSubSort tradeSort;//小类型

        Common::_tstring str;
        str.fromUTF8(pElemChildType->Attribute("Name"));
        tradeSort.m_NameSort = str;
        tradeSort.m_vecItemIdSet.clear();

        if(!LoadBroadCast(pElemChildType,tradeSort))  //载入广告
            return false;

        if(!LoadItem(pElemChildType,tradeSort))       //载入item
            return false;

        typeSort.m_vecSet.push_back(tradeSort);
    }

    return true;
}

bool CTradeCenterInfo::LoadTypes(MeXmlElement* pElemSubItem)
{
    if(!pElemSubItem)
        return false;

    //遍历Type
    MeXmlElement *pElemItem = pElemSubItem->FirstChildElement("Types");
    if(NULL == pElemItem)
        return false;

    pElemItem = pElemItem->FirstChildElement("Type");
    for (;pElemItem != NULL;pElemItem = pElemItem->NextSiblingElement() )
    {
        cTypeSort typeSort;

        Common::_tstring str;
        str.fromUTF8(pElemItem->Attribute("Name"));
        typeSort.m_Name = str;
		typeSort.chType = GetParentType(typeSort.m_Name.c_str());
        typeSort.m_vecSet.clear();

        if(!LoadChildType(pElemItem,typeSort))   //载入ChildTpe
            return false;

        m_TradeMap.m_vecDisSet.push_back(typeSort);
    }

    return true;
}

void  CTradeCenterInfo::GetAllItemByType()
{
    cTradeGlobalData::Iter it = m_TradeMap.m_vecDisSet.begin();
    cTradeGlobalData::Iter end = m_TradeMap.m_vecDisSet.end();

    for (;it != end;++it)
    {
        cTradeSubSort subSort;
        subSort.m_NameSort = theXmlString.GetString(eText_ShopCenterTypeAll);
        subSort.m_vecItemIdSet.clear();

        cTypeSort::Iter iter = it->m_vecSet.begin();
        cTypeSort::Iter iterEnd = it->m_vecSet.end();
        for(;iter != iterEnd;++iter)
            std::copy(iter->m_vecItemIdSet.begin(),iter->m_vecItemIdSet.end(),std::back_inserter(subSort.m_vecItemIdSet));

        it->m_vecSet.insert(it->m_vecSet.begin(),subSort);
    }
}
