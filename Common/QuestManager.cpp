#include "QuestManager.h"
#include "QuestData.h"
#include "RapidXml/MeRapidXml.h"

#define QuestRandRoot           "QuestRand"
#define QuestRandElement        "QuestRank"
#define QuestIdAttribute        "Id"
#define QuestRandAttribute      "Rand"

QuestManager::QuestManager()
{

}
QuestManager::~QuestManager()
{

}

QuestManager& QuestManager::Instance()
{
    static QuestManager s_QuestMgr;
    return s_QuestMgr;
}

short QuestManager::SetQuestState( short questValue, uint8 questState )
{
    return questState | ((uint16)(questValue & ~(uint16)ECD_C));
}

uint8 QuestManager::GetQuestState( short questValue )
{
    return (questValue & (uint16)ECD_C);
}

bool QuestManager::IsQuestDone( uint8 questState )
{
    return eQuestDone == questState; 
}

bool QuestManager::IsQuestActive( uint8 questState )
{
    if( IsQuestDone( questState ) )
    { return false; }

    if ( eQuestCantGain == questState )
    { return false; }

    if( IsQuestNotGain( questState ))
    { return false; }

    return true;
}

bool QuestManager::IsQuestNotGain( uint8 questState )
{ 
    return eQuestNotGain == questState; 
}

bool QuestManager::IsQuestIdValid( int nQuestId )
{
    if( nQuestId < dr_MinQuestId || nQuestId > dr_MaxQuestId )
    { return false; }

    return true;
}

bool QuestManager::IsHaveSaw( uint8 type, short questValue )
{
    switch ( type )
    {
    case HSTT_ToGain:
        return _HAS_FLAG( questValue, ECD_A );
        break;
    case HSTT_ToDone:
        return _HAS_FLAG( questValue, ECD_B );
        break;
    }

    return true;
}

short QuestManager::SetHaveSaw( uint8 type, short questValue )
{
    switch ( type )
    {
    case HSTT_ToGain:
        return ECD_A | ((uint16)(questValue & ~(uint16)ECD_A));
        break;
    case HSTT_ToDone:
        return ECD_B | ((uint16)(questValue & ~(uint16)ECD_B));
        break;
    }

    return questValue;
}

SQuest* QuestManager::GetQuest( int nQuestId )
{
    if( nQuestId < dr_MinQuestId || nQuestId > dr_MaxQuestId )
    { return NULL; }

    QuestInfo::itrSQuests finditr = theQuestInfo.m_pQuests.find(nQuestId);
    if (finditr == theQuestInfo.m_pQuests.end())
    { return NULL; }

    SQuest* pQuest = finditr->second;
    if ( pQuest == NULL )
    { return NULL; }

    if ( pQuest->Id == theQuestInfo.DeleteQuest)
    { return NULL; }

    return pQuest;
}

typedef std::map< int, std::vector< int > > mapQuestIDContainer;
typedef mapQuestIDContainer::iterator       mapQuestIDContainerItr;

SQuest* QuestManager::GetQuestByTheQuests( std::list<int>& QuestIds )
{
    if ( QuestIds.empty() )
    { return NULL; }

    if ( _QuestTotalRand == 0 )          // 获得概率总值
    {
        PubQuestRankMap::iterator itr = _QuestRankMap.begin();
        PubQuestRankMap::iterator itrEnd = _QuestRankMap.end();
        for(; itr != itrEnd; ++itr )
        { _QuestTotalRand += itr->second; }
    }
    if ( _QuestTotalRand == 0 )
    { return NULL; }       // 没有概率值

    int RandNum = theRand.rand32() % _QuestTotalRand;
    int nValue = 0;
    int nQuestRank = -1;        // 任务品质

    ItrPubQuestRankMap itrPubQuests    = _QuestRankMap.begin();
    ItrPubQuestRankMap itrPubQuestsEnd = _QuestRankMap.end();
    for ( ; itrPubQuests != itrPubQuestsEnd; ++itrPubQuests )
    {
        nValue += itrPubQuests->second;
        if ( RandNum <= nValue ) 
        { // 判断概率区间, 满足条件得到该次随机得到的任务品质
            nQuestRank = itrPubQuests->first;
            break;
        }
    }

    if ( nQuestRank == -1 )
    { return NULL; }        // 没有符合条件的品质

    // 把传入的任务 按品质分类
    mapQuestIDContainer mapQuestID;
    mapQuestID.clear();
    for ( std::list< int >::iterator iter = QuestIds.begin(); iter != QuestIds.end(); ++iter )
    {
        SQuest* pQuest = GetQuest( *iter );
        if ( pQuest == NULL )
        { continue; }

        mapQuestIDContainerItr miter = mapQuestID.find( pQuest->RankId );
        if ( miter == mapQuestID.end() )
        {
            std::vector< int > vecQuestID( 0 );
            vecQuestID.push_back( pQuest->Id );
            mapQuestID.insert( make_pair( pQuest->RankId, vecQuestID ) );
        }
        else
        {
            miter->second.push_back( pQuest->Id );
        }
    }

    // 用随机到得 nQuestRank 来的到该品质的所有任务
    mapQuestIDContainerItr iter = mapQuestID.find( nQuestRank );
    if ( iter == mapQuestID.end() || iter->second.empty() )
    { 
        iter = mapQuestID.find( SQuest::eQuestRank_Nor );
        if ( iter == mapQuestID.end() || iter->second.empty() )
        { return NULL; }
    }

    // 在该品质队列中 随机一个任务
    int nIndex = theRand.rand32() % iter->second.size();
    return GetQuest( iter->second.at( nIndex ) );
}

bool QuestManager::LoadQuestRandConfigFile(const char* Path)
{
    MeXmlDocument Doc;
    if (!Doc.LoadFile(Path))
        return false;

    // 初始化
    _QuestRankMap.clear();
    _QuestRankMap.insert(PubQuestRankMap::value_type(SQuest::eQuestRank_Nor,100));
    _QuestRankMap.insert(PubQuestRankMap::value_type(SQuest::eQuestRank_Nic,0));
    _QuestRankMap.insert(PubQuestRankMap::value_type(SQuest::eQuestRank_Exc,0));
    _QuestRankMap.insert(PubQuestRankMap::value_type(SQuest::eQuestRank_Gold,0));
    _QuestRankMap.insert(PubQuestRankMap::value_type(SQuest::eQuestRank_Legend,0));
    
    MeXmlElement* RootNode = Doc.RootElement();
    if (NULL == RootNode)
    { return false; }

    // 长安酒馆
    MeXmlElement* QuestNode = RootNode->FirstChildElement(QuestRandRoot);
    if (NULL == QuestNode)
    { return false;}

    MeXmlElement* QuestRankNode = QuestNode->FirstChildElement(QuestRandElement);
    if (NULL == QuestRankNode)
    { return false;}

    while (QuestRankNode)
    {
        int QuestRankId = 0;
        if (NULL == QuestRankNode->Attribute(QuestIdAttribute,&QuestRankId))
        {
            return false;
        }
        if (QuestRankId < SQuest::eQuestRank_Nor || QuestRankId > SQuest::eQuestRank_Legend)
        {
            QuestRankId = SQuest::eQuestRank_Nor;
        }
        ItrPubQuestRankMap itr = _QuestRankMap.find(QuestRankId);
        if (itr == _QuestRankMap.end())
        {
            return false;
        }
        int PubQuestRand = 0;
        if (NULL == QuestRankNode->Attribute(QuestRandAttribute,&PubQuestRand))
        {
            return false;
        }
        itr->second = PubQuestRand;

        QuestRankNode  = QuestRankNode->NextSiblingElement();
    }

    if (!CheckQuestRand(_QuestRankMap))
    { return false;}


    //if (!QuestInfo::Instance().m_pQuests.empty())
    //{
    //    ParseAllSpecializationQuestByQuest();
    //}

    return true;
}

bool QuestManager::SaveQuestRandConfigFile(const char* Path)
{
    MeXmlDocument XmlDoc;
    XmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
    MeXmlElement* pRoot = XmlDoc.InsertEndChild(("Project"))->ToElement();
    pRoot->SetAttribute("Name","HeroOnline");

    MeXmlElement* pQuestRandRoot = pRoot->InsertEndChild((QuestRandRoot))->ToElement();
    for (ItrPubQuestRankMap itr = _QuestRankMap.begin();itr!=_QuestRankMap.end();++itr)
    {
        MeXmlElement* NewQuestRandElement = pQuestRandRoot->InsertEndChild((QuestRandElement))->ToElement();
        NewQuestRandElement->SetAttribute(QuestIdAttribute,itr->first);
        NewQuestRandElement->SetAttribute(QuestRandAttribute,itr->second);
    }

    return XmlDoc.SaveFile(Path);
}

bool QuestManager::CheckQuestRand( PubQuestRankMap &_PubQuestRankMap )
{
    int TotalRandNum = 0;
    for (ItrPubQuestRankMap itr = _PubQuestRankMap.begin();itr != _PubQuestRankMap.end();++itr)
    {
        TotalRandNum += itr->second;
    }
    if (TotalRandNum != 100)
    {
        return false;
    }
    return true;
}



//调用此函数对所有的任务进行解析
void QuestManager::ParseAllSpecializationQuestByQuest()
{
    //_PubQuestByQuestRank.clear();
    //_RoyalQuestByQuestRank.clear();

    //for (QuestInfo::SQuests::iterator itr = QuestInfo::Instance().m_pQuests.begin();itr != QuestInfo::Instance().m_pQuests.end();++itr)
    //{
    //    if ( itr->second->chQuestType == SQuest::Type_Pub )
    //    {
    //        _PubQuestByQuestRank.push_back(itr->second->Id);
    //    }

    //    if ( itr->second->chQuestType == SQuest::Type_Royal )
    //    {
    //        _RoyalQuestByQuestRank.push_back(itr->second->Id);
    //    }
    //}
}
