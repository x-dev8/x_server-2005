#include "QuestEntrustConfig.h"
#include "RapidXml/MeRapidXml.h"
QuestEntrustConfig::QuestEntrustConfig()
{

}
QuestEntrustConfig::~QuestEntrustConfig()
{
	
}
bool QuestEntrustConfig::LoadQuestEntrustConfig(const char* FilePath)
{
	if ( FilePath == NULL || FilePath[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( FilePath, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

	int BuffID = 0;
	if ( pRoot->Attribute( "BuffID", &BuffID ) == NULL )
    { return false; }
	m_BuffID= BuffID;

	int BuffLevel = 0;
	if ( pRoot->Attribute( "BuffLevel", &BuffLevel ) == NULL )
    { return false; }
	m_BuffLevel = BuffLevel;

	int LastTime = 0;
	if ( pRoot->Attribute( "LastTime", &LastTime ) == NULL )
    { return false; }
	m_LastTime = LastTime;

	MeXmlElement* pQuest = pRoot->FirstChildElement( "QuestEntrust" );
    while ( pQuest != NULL )
    {
		int SrcID = 0;
		if ( pQuest->Attribute( "SrcQuestID", &SrcID ) == NULL )
        { return false; }
    
		int DestID = 0;
		if ( pQuest->Attribute( "DestQuestID", &DestID ) == NULL )
        { return false; }

		int MoneySum = 0;
		if ( pQuest->Attribute( "MoneySum", &MoneySum ) == NULL )
        { return false; }

		QuestChangeMap.insert(std::map<unsigned int,unsigned int>::value_type(SrcID,DestID));
		NewQuestToOldMap.insert(std::map<unsigned int,unsigned int>::value_type(DestID,SrcID));
		QuestMoneySumMap.insert(std::map<unsigned int,unsigned int>::value_type(SrcID,MoneySum));

		pQuest = pQuest->NextSiblingElement();
	}
	return true;
}
unsigned int QuestEntrustConfig::GetChangeQuestID(unsigned int QuestID)
{
	if(QuestChangeMap.count(QuestID) == 1)
		return QuestChangeMap[QuestID];
	else
		return 0;
}
unsigned int QuestEntrustConfig::GetOldQuestID(unsigned int QuestID)
{
	if(NewQuestToOldMap.count(QuestID) == 1)
		return NewQuestToOldMap[QuestID];
	else
		return 0;
}
unsigned int QuestEntrustConfig::GetQuestMoneySum(unsigned int QuestID)
{
	if(QuestMoneySumMap.count(QuestID) == 1)
		return QuestMoneySumMap[QuestID];
	else
		return 0;
}