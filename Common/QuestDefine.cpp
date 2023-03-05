#include "QuestDefine.h"
#include "XmlStringLanguage.h"
#include "NpcInfo.h"

const char* SQuest::GetQuestName()
{
    return theXmlString.GetString(QuestName);
}

const char* SQuest::GetRewardNpcName()
{
    NpcInfo::Npc* NpcName = theNpcInfo.GetNpcByStaticId(ReplyTargetId);
    if (NpcName == NULL)
    { return NULL; }

    return NpcName->name.c_str();
}

const char* SQuest::GetAcceptNpcName()
{
    NpcInfo::Npc* NpcName = theNpcInfo.GetNpcByStaticId(AcceptTargetId);
    if (NpcName == NULL)
    { return NULL; }
    return NpcName->name.c_str();
}

const char*  SQuest::GetQuestStateInfo()
{ return theXmlString.GetString(TargetStringId); }

const char* SQuest::GetQuestInfo()
{ return theXmlString.GetString(IntroStringId); }