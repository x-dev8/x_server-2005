#pragma once

#include "MeRTLibs.h"
#include <map>
#include <vector>
#include <string>
#include "Singleton.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#define theTradeCenter CTradeCenterInfo::Instance()

class CTradeCenterInfo :public ICfgSingletion<CTradeCenterInfo>
{
public:
    enum EConstDefine
    {
        ECD_ConfigBufferMaxSize = 50 * 1024,

		// tab页
		ECD_ParentType_Yuanbao = 0,
		ECD_ParentType_Bangjin = 1,
		ECD_ParentType_Jifen = 2,
		ECD_ParentType_max,
    };

	// 每个单品的信息
    struct cTradeItem
    {
        unsigned int   m_ItemID;             // 物品类型
        unsigned int   m_OriginalPrice;      // 原始价格
        unsigned int   m_FinalDiscountPrice; // 最终价格
        unsigned int   m_TicketPrice;        // 所需购物券
		unsigned int   m_ConsumeScore;       // 所需商城积分 
        unsigned int   m_Count;              // 商品数量
        unsigned int   m_RefreshInterval;    // 刷新间隔(分钟)
        bool           m_isHot;              // 是否热卖
        bool           m_isNew;              // 是否新品
        std::string	   m_strTimeLimit;		 // 商品期限
        int			   m_Rank;				 // 显示排序
        bool           m_bNeedNpc;           // 是否有Npc寻路
        int            m_nMapId;             // NpcMap
        int            m_nNpcId;             // NpcId

        cTradeItem()
        {
            m_ItemID             = -1;              
            m_OriginalPrice      = 0;       
            m_FinalDiscountPrice = 0;  
            m_TicketPrice        = 0;         
            m_Count              = 0;               
            m_RefreshInterval    = 0;     
            m_isHot              = 0;                
            m_isNew              = 0;
			m_ConsumeScore       = 0;
            m_strTimeLimit.clear();

            m_Rank               = 0;	
            m_bNeedNpc           = 0;           
            m_nMapId             = 0;             
            m_nNpcId             = 0;
        }
    };

    //广告信息
    struct cTradeInfo
    {
        int nId;
        std::string infoString;
    };

	// 小类型快速结构
    struct cTradeSubSort
    {
        std::string m_NameSort;          // 商城类型名
        std::vector<int> m_vecItemIdSet;   // 商城物品id索引
        std::vector<int> m_mapTradeInfo; // 商城广告id索引

        typedef std::vector<int>::iterator Iter;
        typedef std::vector<int>::iterator IterMap;
#ifdef _TRADECENTER_
        std::vector<cTradeItem> m_vecItemSet1;    // 商城物品
        std::map<int,cTradeInfo> m_mapTradeInfo1; // 商城信息

        typedef std::vector<cTradeItem>::iterator Iter1;
        typedef std::map<int,cTradeInfo>::iterator IterMap1;
#endif
    };

	// 大类型快速结构
    struct cTypeSort
    {
        std::string m_Name;				// 商城类型名
		char chType;					// 商城类型枚举
        std::vector<cTradeSubSort> m_vecSet;//大类型下面的所有小类型信息

        typedef std::vector<cTradeSubSort>::iterator Iter;

        cTypeSort()
        {
            m_Name.clear();
            m_vecSet.clear();
        }
    };
    
    struct cTradeShortcuts
    { // Only Client
        std::string      m_UiName;
        int              m_TypeID;
        std::vector<int> m_vecItemIdSet;
        typedef std::vector<int>::iterator Iter;
    };

	// 商城的全局信息数据
    struct cTradeGlobalData
    {
        unsigned int m_DisCountPercent;   // 打折比例
        unsigned int m_Radio;             // 点卷转金锭比例
        std::vector<cTypeSort> m_vecDisSet; // all 类型的信息 包括大 小 类型信息

        std::vector<cTradeShortcuts> m_vecShortcuts;//客户端用

        typedef std::vector<cTypeSort>::iterator       Iter;
        typedef std::vector<cTradeShortcuts>::iterator IterShortcut;
    };

public:
    CTradeCenterInfo();
    ~CTradeCenterInfo();

    virtual bool LoadResourceConfig(const char* pszConfig);      // 从文件中加载商城资源
	virtual void OnReloadFinished();							 // 热加载完成
	bool LoadConfigFromBuffer( const uint8* buffer, uint32 bufferSize, bool bBufferIsZip = true ); // 从内存中加载商城资源
    bool LoadTypes(MeXmlElement* pElemSubItem);
    bool LoadChildType(MeXmlElement* pElemSubItem,cTypeSort &typeSort);
    bool LoadItem(MeXmlElement* pElemSubItem,cTradeSubSort &cSubSort);
    bool LoadBroadCast(MeXmlElement* pElemSubItem,cTradeSubSort &cSubSort);
    bool LoadShortCut(MeXmlElement *pElemSubItem);		// client用的暂时空的

#ifdef _TRADECENTER_
    bool SaveConfig(const char* pszPath);
    bool SaveTypes(MeXmlElement *pElemItem,std::vector<cTypeSort> &typeSort);
    bool SaveBroadCast(MeXmlElement *pElemSubItem,std::map<int,cTradeInfo> &mapSet);
    bool SaveItem(MeXmlElement* pElemSubItem,std::vector<cTradeItem> &itemSet);
    bool SaveShortCut(MeXmlElement *pElemItem);
#endif
    cTypeSort* GetTradeParentSort(const char* pszName);
    cTradeSubSort* GetTradeSubSort(cTypeSort* pTypeSort,const char* pszName);  //通过名字获得子分类

    bool        SetTradeParentType(const char* pszSrc,const char* pszDes);  //设置类型
    bool        SetTradeSubType(const char* pParentName,const char* pszSrcName,const char *pszDestName);   //设置子类型


    bool        InsertTradeParentType(const char *pszName);  // 添加父类型
    bool        InsertTradeSubType(const char *pParentName,const char* pszName);   //添加子类型
	char		GetParentType(const char *pszName);

    bool        DelTradeParentType(const char *pszName);     // 删除类型
    bool        DelTradeSubType(const char* pParentName,const char *pszName);        //删除子类型
    
    bool        SetTradeDiscount(int nDiscount);    //设置折扣
    int         GetTradeDiscount(){return m_TradeMap.m_DisCountPercent; }
    int         GetTradeRadio()          { return m_TradeMap.m_Radio;}
    void        SetTradeRadio(int nValue){ m_TradeMap.m_Radio = nValue;}

    void        Clear();
    bool        GetFileBuffer( char* szBuffer, unsigned long& bufferSize );
    uint32      GetTradeItemCount  () { return static_cast<unsigned int>( m_itemSet.size() ); }
    cTradeItem* GetTradeItemByIndex( unsigned int nIndex,char chType = ECD_ParentType_max );
    cTradeItem* GetTradeItemByItemID( unsigned short nItemId ,char chType = ECD_ParentType_max);
    uint32      GetTradeItemIndexByItemID( unsigned short nItemId );
    uint32      GetTradeStringIndexByID(uint32 nId);
    cTradeInfo* GetTradeStringByID(uint32 nId);
    cTradeInfo* GetTradeStringByIndex(uint32 nIndex);
    long        GetHotItem(std::vector<uint16> &itemSet);
    long        GetNewItem(std::vector<uint16> &itemSet);
	long        GetYuanbaoItem();
	long        GetBangjinItem();
	long        GetJifenItem();
    cTradeItem* GetNextItem(bool bFirstItem);
    cTradeItem* GetNextNewItem(bool bFirstItem);
    cTradeItem* GetNextHotItem(bool bFirstItem);
    cTradeItem* GetNewItem(int index);
    cTradeItem* GetHotItem(int index);
    size_t      GetNewItemCount() { return m_New.size(); }
    size_t      GetHotItemCount() { return m_Hot.size(); }
	size_t		GetYuanbaoItemCount() {return m_mapYuanbao.size();}
	size_t		GetYuanbaoHotItemCount() {return m_mapYuanbaoHot.size();}
	size_t		GetYuanbaoNewItemCount() {return m_mapYuanbaoNew.size();}
	size_t		GetBangjinItemCount() {return m_mapBangjin.size();}
	size_t		GetBangjinNewItemCount() {return m_mapBangjinNew.size();}
	size_t		GetBangjinHotItemCount() {return m_mapBangjinHot.size();}
	size_t		GetJifenItemCount() {return m_mapJifen.size();}
    bool        GetShortcutsItems(const std::string& type, std::vector<int>* itemIds);
    std::string GetShortcutsShopTypeUIID(const std::string& type);   

	// 检查是否重新加载完毕
	bool        CheckReloaded(){ bool result = (nReloadSignal == 1);  nReloadSignal = 0;  return result;} 

    void        GetAllItemByType();

protected:
	bool		InsertYuanbaoItem(cTradeItem* pTradeItem);
	bool		InsertJifenItem(cTradeItem* pTradeItem);
	bool		InsertBangjinItem(cTradeItem* pTradeItem);
public:
    typedef std::map<uint16,cTradeItem*>  TradeItemContainer;
    typedef TradeItemContainer::iterator ItrTradeItemContainer;

    typedef std::vector<cTradeInfo>      TradeInfoContainer;
    typedef TradeInfoContainer::iterator IterInfo;

    typedef std::map<uint16,cTradeItem*>::iterator IterItem; 	

    std::map<uint16,cTradeItem*> m_itemSet;     // 所有物品 id不重复
	std::vector<cTradeItem>		m_itemAllVec;   // 所有物品 id重复 内存所在
    std::vector<cTradeInfo>     m_TradeInfo;    // 商城广告信息
    cTradeGlobalData              m_TradeMap;
    ItrTradeItemContainer       _curIt;

    uint32 gnFileBufferSize;                            // 文件配置大小
    char   gszFileBuffer[ ECD_ConfigBufferMaxSize ];    // 文件配置buffer
    uint32 gnZibFileBufferSize;                         // 文件配置大小(压缩后)
    uint8  gszZibFileBuffer[ ECD_ConfigBufferMaxSize ]; // 文件配置buffer(压缩后)

	uint8  nReloadSignal;
private:
    typedef std::vector<uint16>             TradeNewItemContainer;
    typedef TradeNewItemContainer::iterator TradeNewItemIter;

    typedef std::vector<uint16>             TradeHotItemContainer;
    typedef TradeHotItemContainer::iterator TradeHotItemIter;

    std::vector<uint16> m_New;      // 新品
    TradeNewItemIter    m_curNewIt;
    std::vector<uint16> m_Hot;      // 热卖
    TradeHotItemIter    m_curHotIt;

	typedef map<uint16,cTradeItem*> mapYuanbao;
	typedef map<uint16,cTradeItem*> mapYuanbaoNew;
	typedef map<uint16,cTradeItem*> mapYuanbaoHot;
	typedef map<uint16,cTradeItem*> mapBangjin;
	typedef map<uint16,cTradeItem*> mapBangjinNew;
	typedef map<uint16,cTradeItem*> mapBangjinHot;
	typedef map<uint16,cTradeItem*> mapJifen;

	mapYuanbao m_mapYuanbao;
	mapYuanbaoNew m_mapYuanbaoNew;//没用了都
	mapYuanbaoHot m_mapYuanbaoHot;//没用了都
	mapBangjin m_mapBangjin;
	mapBangjinNew m_mapBangjinNew;//没用了都
	mapBangjinHot m_mapBangjinHot;//没用了都
	mapJifen   m_mapJifen;
};

inline CTradeCenterInfo::cTradeItem* CTradeCenterInfo::GetNewItem(int index)
{
    if (index >= (int)m_New.size())
    { return 0; }

    cTradeItem* pItem = m_itemSet[m_New[index]];
    return pItem;
}

inline CTradeCenterInfo::cTradeItem* CTradeCenterInfo::GetHotItem(int index)
{
    if (index >= (int)m_Hot.size())
    { return 0; }

    cTradeItem* pItem = m_itemSet[m_Hot[index]];
    return pItem;
}

inline 
bool CTradeCenterInfo::GetFileBuffer( char* szBuffer, unsigned long& bufferSize )
{
    if ( bufferSize < gnFileBufferSize || bufferSize < ECD_ConfigBufferMaxSize)
    { return false; }

    memcpy_s( szBuffer, bufferSize, gszFileBuffer, gnFileBufferSize );
    return true;
}
