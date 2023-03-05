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

		// tabҳ
		ECD_ParentType_Yuanbao = 0,
		ECD_ParentType_Bangjin = 1,
		ECD_ParentType_Jifen = 2,
		ECD_ParentType_max,
    };

	// ÿ����Ʒ����Ϣ
    struct cTradeItem
    {
        unsigned int   m_ItemID;             // ��Ʒ����
        unsigned int   m_OriginalPrice;      // ԭʼ�۸�
        unsigned int   m_FinalDiscountPrice; // ���ռ۸�
        unsigned int   m_TicketPrice;        // ���蹺��ȯ
		unsigned int   m_ConsumeScore;       // �����̳ǻ��� 
        unsigned int   m_Count;              // ��Ʒ����
        unsigned int   m_RefreshInterval;    // ˢ�¼��(����)
        bool           m_isHot;              // �Ƿ�����
        bool           m_isNew;              // �Ƿ���Ʒ
        std::string	   m_strTimeLimit;		 // ��Ʒ����
        int			   m_Rank;				 // ��ʾ����
        bool           m_bNeedNpc;           // �Ƿ���NpcѰ·
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

    //�����Ϣ
    struct cTradeInfo
    {
        int nId;
        std::string infoString;
    };

	// С���Ϳ��ٽṹ
    struct cTradeSubSort
    {
        std::string m_NameSort;          // �̳�������
        std::vector<int> m_vecItemIdSet;   // �̳���Ʒid����
        std::vector<int> m_mapTradeInfo; // �̳ǹ��id����

        typedef std::vector<int>::iterator Iter;
        typedef std::vector<int>::iterator IterMap;
#ifdef _TRADECENTER_
        std::vector<cTradeItem> m_vecItemSet1;    // �̳���Ʒ
        std::map<int,cTradeInfo> m_mapTradeInfo1; // �̳���Ϣ

        typedef std::vector<cTradeItem>::iterator Iter1;
        typedef std::map<int,cTradeInfo>::iterator IterMap1;
#endif
    };

	// �����Ϳ��ٽṹ
    struct cTypeSort
    {
        std::string m_Name;				// �̳�������
		char chType;					// �̳�����ö��
        std::vector<cTradeSubSort> m_vecSet;//���������������С������Ϣ

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

	// �̳ǵ�ȫ����Ϣ����
    struct cTradeGlobalData
    {
        unsigned int m_DisCountPercent;   // ���۱���
        unsigned int m_Radio;             // ���ת�𶧱���
        std::vector<cTypeSort> m_vecDisSet; // all ���͵���Ϣ ������ С ������Ϣ

        std::vector<cTradeShortcuts> m_vecShortcuts;//�ͻ�����

        typedef std::vector<cTypeSort>::iterator       Iter;
        typedef std::vector<cTradeShortcuts>::iterator IterShortcut;
    };

public:
    CTradeCenterInfo();
    ~CTradeCenterInfo();

    virtual bool LoadResourceConfig(const char* pszConfig);      // ���ļ��м����̳���Դ
	virtual void OnReloadFinished();							 // �ȼ������
	bool LoadConfigFromBuffer( const uint8* buffer, uint32 bufferSize, bool bBufferIsZip = true ); // ���ڴ��м����̳���Դ
    bool LoadTypes(MeXmlElement* pElemSubItem);
    bool LoadChildType(MeXmlElement* pElemSubItem,cTypeSort &typeSort);
    bool LoadItem(MeXmlElement* pElemSubItem,cTradeSubSort &cSubSort);
    bool LoadBroadCast(MeXmlElement* pElemSubItem,cTradeSubSort &cSubSort);
    bool LoadShortCut(MeXmlElement *pElemSubItem);		// client�õ���ʱ�յ�

#ifdef _TRADECENTER_
    bool SaveConfig(const char* pszPath);
    bool SaveTypes(MeXmlElement *pElemItem,std::vector<cTypeSort> &typeSort);
    bool SaveBroadCast(MeXmlElement *pElemSubItem,std::map<int,cTradeInfo> &mapSet);
    bool SaveItem(MeXmlElement* pElemSubItem,std::vector<cTradeItem> &itemSet);
    bool SaveShortCut(MeXmlElement *pElemItem);
#endif
    cTypeSort* GetTradeParentSort(const char* pszName);
    cTradeSubSort* GetTradeSubSort(cTypeSort* pTypeSort,const char* pszName);  //ͨ�����ֻ���ӷ���

    bool        SetTradeParentType(const char* pszSrc,const char* pszDes);  //��������
    bool        SetTradeSubType(const char* pParentName,const char* pszSrcName,const char *pszDestName);   //����������


    bool        InsertTradeParentType(const char *pszName);  // ��Ӹ�����
    bool        InsertTradeSubType(const char *pParentName,const char* pszName);   //���������
	char		GetParentType(const char *pszName);

    bool        DelTradeParentType(const char *pszName);     // ɾ������
    bool        DelTradeSubType(const char* pParentName,const char *pszName);        //ɾ��������
    
    bool        SetTradeDiscount(int nDiscount);    //�����ۿ�
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

	// ����Ƿ����¼������
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

    std::map<uint16,cTradeItem*> m_itemSet;     // ������Ʒ id���ظ�
	std::vector<cTradeItem>		m_itemAllVec;   // ������Ʒ id�ظ� �ڴ�����
    std::vector<cTradeInfo>     m_TradeInfo;    // �̳ǹ����Ϣ
    cTradeGlobalData              m_TradeMap;
    ItrTradeItemContainer       _curIt;

    uint32 gnFileBufferSize;                            // �ļ����ô�С
    char   gszFileBuffer[ ECD_ConfigBufferMaxSize ];    // �ļ�����buffer
    uint32 gnZibFileBufferSize;                         // �ļ����ô�С(ѹ����)
    uint8  gszZibFileBuffer[ ECD_ConfigBufferMaxSize ]; // �ļ�����buffer(ѹ����)

	uint8  nReloadSignal;
private:
    typedef std::vector<uint16>             TradeNewItemContainer;
    typedef TradeNewItemContainer::iterator TradeNewItemIter;

    typedef std::vector<uint16>             TradeHotItemContainer;
    typedef TradeHotItemContainer::iterator TradeHotItemIter;

    std::vector<uint16> m_New;      // ��Ʒ
    TradeNewItemIter    m_curNewIt;
    std::vector<uint16> m_Hot;      // ����
    TradeHotItemIter    m_curHotIt;

	typedef map<uint16,cTradeItem*> mapYuanbao;
	typedef map<uint16,cTradeItem*> mapYuanbaoNew;
	typedef map<uint16,cTradeItem*> mapYuanbaoHot;
	typedef map<uint16,cTradeItem*> mapBangjin;
	typedef map<uint16,cTradeItem*> mapBangjinNew;
	typedef map<uint16,cTradeItem*> mapBangjinHot;
	typedef map<uint16,cTradeItem*> mapJifen;

	mapYuanbao m_mapYuanbao;
	mapYuanbaoNew m_mapYuanbaoNew;//û���˶�
	mapYuanbaoHot m_mapYuanbaoHot;//û���˶�
	mapBangjin m_mapBangjin;
	mapBangjinNew m_mapBangjinNew;//û���˶�
	mapBangjinHot m_mapBangjinHot;//û���˶�
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
