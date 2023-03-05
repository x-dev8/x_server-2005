#include "QuestData.h"
#include "WordParser.h"
#include "FuncPerformanceLog.h"
#include "NewWithDebug.h"
#include "ResourcePath.h"
#include "StringLanguageTranslator.h"
#include "tstring.h"
#include "application_config.h"
#include "StringLanguage.h"
#include "packet_interface.h"
#include "datafile.h"
//#include "Launcher/DataLauncher.h"
#include "XmlStringLanguage.h"
#include "QuestManager.h"
#include "RapidXml/MeRapidXml.h"
char QuestInfo::RequirementString[SQuest::eRequirement_Max][_nMaxStringLength] = 
{
    "Money",
    "Item",
    "VarId",
    "Profession",
    "Level",
    "Reputation",
    "Sex",
    "Energy",
    "Monster",
    "Quest",
    "Time",
    "SocialRelation"
    "SkillExperience",
    "Experience",
    "VarLimit",
};

char QuestInfo::RewardString[SQuest::eReward_Max][_nMaxStringLength] = 
{
    "Money",
    "Experience",
    "SkillExperience",
    "Item",
    "Reputation",
    "Exploit"
    "ReputeName",
    "Buff",
    "ChangeRoleVar",
    "GuildContribute",
    "SpecialItem",
	"jiaozi",
    "Honor",   //荣誉
	"CountryMoney",
	"ScriptExp"
};

char QuestInfo::RankString[SQuest::eQuestRank_Max][_nMaxStringLength] =
{
    "Normal",    // 普通
    "Nicer",     // 良好的
    "Excellent", // 优秀
    "Gold",      // 卓越
    "Legend",    // 传说
    //  "Epic",      // 史诗
};

QuestInfo::QuestInfo()
{
}

QuestInfo::~QuestInfo()
{
    for (itrSQuests itRelease = m_pQuests.begin();itRelease != m_pQuests.end();)
    {
        CNewWithDebug<SQuest>::Free(itRelease->second);
        itRelease->second = NULL;
        itRelease = m_pQuests.erase(itRelease);
    }
}

int QuestInfo::StrToRequirementType( const char* pszString )
{
    if( !pszString ||strlen(pszString)==0)
        return SQuest::eRequirement_Max;

    for(int i = 0;i<SQuest::eRequirement_Max ;++i)
    {
        if(stricmp(RequirementString[i],pszString) == 0)
            return i;
    }
    return SQuest::eRequirement_Max;

}

int QuestInfo::AddRewardType(int id,const char * RewardType,const int Icon)
{
    if (!RewardType)
    {
        return false;
    }
    RewardTypes::iterator findid = rewardTypes_.find(id);
    if (findid != rewardTypes_.end())
    {
        return AlreadyHaveRewardType;
    }
    SRewardType data;
    data.Value = RewardType;
    data.DefauleIconId = Icon;
    rewardTypes_.insert(RewardTypes::value_type(id ,data ));
    return id;
}

int QuestInfo::AddRewardType(const char * RewardType,const int Icon)
{
    if (!RewardType)
    {
        return false;
    }
    for(RewardTypes::iterator itr =  rewardTypes_.begin();itr != rewardTypes_.end();++itr)
    {
        if(itr->second.Value.compare( RewardType ) == 0)
        {
            return AlreadyHaveRewardType;
        }
    } 
    SRewardType data;
    data.Value = RewardType;
    data.DefauleIconId = Icon;
    rewardTypes_.insert(RewardTypes::value_type(rewardTypes_.size(),data));
    return rewardTypes_.size();
}

int QuestInfo::StrToRewardType( const char* pszString )
{
    if( !pszString||strlen(pszString)==0)
        return SQuest::eReward_Max;

    for(int i = 0;i<SQuest::eReward_Max ;++i)
    {
        if(stricmp(RewardString[i],pszString) == 0)
            return i;
    }
    return SQuest::eReward_Max;
}

bool QuestInfo::ParseReceiveRequirementTypes(MeXmlElement* requirementsElement,SQuest* Quest)
{
    if (!requirementsElement||!Quest)
    {
        return false;
    }
    int nTempValue = 0;
    MeXmlElement* requirementElement = requirementsElement->FirstChildElement();
    while ( requirementElement != NULL )
    {
        nTempValue = 0;
        //Requirement requirement;
        int type = 0;
        requirementElement->Attribute( "Type", &type );
        if (type >= 0  && type < SQuest::Type_End/*type < ReceiveRequirementTypes_.size()*/)
        {
            //int type = StrToRequirementType(ReceiveRequirementTypes_[nTempValue].c_str());
            SQuestRequirement squestrequirement;
            int tempvalue = 0;
            squestrequirement.byType = type;
            requirementElement->Attribute( "Value", &tempvalue );
            squestrequirement.Value = tempvalue;
            requirementElement->Attribute( "Count", &tempvalue );
            if (tempvalue < 0)
            {
                squestrequirement.MaxNum = 0;
            }
            else
                squestrequirement.MaxNum = tempvalue;

            if ( type == SQuest::eRequirement_Var ) // 如果类型是计数变量，则Load计数变量
            {
                requirementElement->Attribute("StringId", &tempvalue);
                squestrequirement.nStringID = tempvalue;
            }

            if( type == SQuest::eRequirement_Var||
                type == SQuest::eRequirement_Monster||
                type == SQuest::eRequirement_Item ||
                type == SQuest::eRequirement_VarLimit )
            {
                MeXmlElement* pParam = requirementElement->FirstChildElement("Param");
                if (pParam)
                {
                    pParam->Attribute("Value",&tempvalue);
                    squestrequirement.wVar = tempvalue;
                }
            }

            Quest->AddReceiveRequirement(&squestrequirement);            
        }
        requirementElement = requirementElement->NextSiblingElement();
    }
    return true;
}

#ifdef __QUEST_EDIT__
bool QuestInfo::CoalitionQuest(QuestInfo &Quests)
{
    return CoalitionQuest(Quests.m_pQuests);
}
bool QuestInfo::CoalitionQuest(QuestInfo::SQuests &Quests)
{
    bool renturnValue = true;
    for (SQuests::iterator itrQuests = Quests.begin();itrQuests != Quests.end();++itrQuests )
    {
        SQuests::iterator findQuest = m_pQuests.find(itrQuests->first);
        if (findQuest != m_pQuests.end())
        {
#if (!_CONVERT_)
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_INFO ,"Warning: CoalitionQuest The Quest %d is Already Exist",itrQuests->first);
#endif
            renturnValue = false;
            continue;
        }

        AddQuest(itrQuests->second);
    }
    return renturnValue;
}

bool QuestInfo::SaveCommonFile(const char* CommonFileName)
{
    if (!CommonFileName || strlen(CommonFileName) == 0)
    {
        return false;
    }

    MeXmlDocument XmlDoc;
    XmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
    MeXmlElement* pRoot = XmlDoc.InsertEndChild(("Project"));
    pRoot->SetAttribute("Name","HeroOnline");


    //1.添加RewardType
    MeXmlElement* pRewardTypes = pRoot->InsertEndChild(("RewardTypes"));
    for (RewardTypes::iterator itrReward = rewardTypes_.begin();itrReward != rewardTypes_.end();++itrReward)
    {
        MeXmlElement* pType = pRewardTypes->InsertEndChild(("Type"));
        pType->SetAttribute("Id",itrReward->first);
        pType->SetAttribute("Value",itrReward->second.Value.c_str());
        pType->SetAttribute("DefaultIcon",itrReward->second.DefauleIconId);
    }

    //2.添加RequirementType
    MeXmlElement* pCommitTypes = pRoot->InsertEndChild(("CommitRequirementTypes"));
    for (RequirementTypes::iterator itrCommitTypes = CommitRequirementTypes_.begin();itrCommitTypes != CommitRequirementTypes_.end();++itrCommitTypes)
    {
        MeXmlElement* pType = pCommitTypes->InsertEndChild(("Type"));
        pType->SetAttribute("Id",itrCommitTypes->first);
        pType->SetAttribute("Value",itrCommitTypes->second.c_str());

    }

    MeXmlElement* pReceiveTypes = pRoot->InsertEndChild(("ReceiveRequirementTypes"));
    for (RequirementTypes::iterator itrReceiveTypes = ReceiveRequirementTypes_.begin();itrReceiveTypes != ReceiveRequirementTypes_.end();++itrReceiveTypes)
    {
        MeXmlElement* pType = pReceiveTypes->InsertEndChild(("Type"));

        pType->SetAttribute("Id",itrReceiveTypes->first);
        pType->SetAttribute("Value",itrReceiveTypes->second.c_str());

    }
    MeXmlElement* QuestRankTypeElement = pRoot->InsertEndChild(("Ranks") );  
    for ( int i = 0; i != SQuest::eQuestRank_Max ; ++i )
    {
        MeXmlElement* typeElement = QuestRankTypeElement->InsertEndChild(("Rank"));
        typeElement->SetAttribute( "Id", i );
        typeElement->SetAttribute("Value" , RankString[i]);
    }
    // 任务类型
    MeXmlElement* QuestTypeElements = pRoot->InsertEndChild("QuestTypes");
    if (QuestTypeElements == NULL)
    { return false;}

    for ( int i=0; i<_QuestType.size(); ++i)
    {
        MeXmlElement* QuestTypeElement = QuestTypeElements->InsertEndChild("Type");
        if (QuestTypeElement == NULL)
        { continue;}

        SQuestType* pQuestType = _QuestType[i];
        if (pQuestType == NULL)
        { continue;}

        QuestTypeElement->SetAttribute("Id", i);

        Common::_tstring strDesc = pQuestType->QuestTypeDesc;
        QuestTypeElement->SetAttribute("Description",strDesc.toUTF8().c_str());

        Common::_tstring strIcon = pQuestType->QuestTypeIcon;
        QuestTypeElement->SetAttribute("Icon", strIcon.toUTF8().c_str());
    }

    if (!XmlDoc.SaveFile(CommonFileName))
        return false;
    return true;
}

bool QuestInfo::SaveQuestFile(const char* QuestFileName , SQuest *itrQuest)
{
    if (!QuestFileName || strlen(QuestFileName) == 0)
    {
        return false;
    }
    if (itrQuest->Id == DeleteQuest)
    {
        return true;
    }

    MeXmlDocument XmlDoc;
    XmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
    MeXmlElement* pRoot = XmlDoc.InsertEndChild(("Project"))->ToElement();
    pRoot->SetAttribute("Name","HeroOnline");


    //MeXmlElement* pQuests = pRoot->InsertEndChild(("Quests"))->ToElement();

    MeXmlElement* pQuest = pRoot->InsertEndChild(("Quest"))->ToElement();
    //3.1 添加quest的描述
    pQuest->SetAttribute("Id",itrQuest->Id);
    pQuest->SetAttribute("Name",itrQuest->QuestName);
    pQuest->SetAttribute("QuestType", itrQuest->chQuestType);
    pQuest->SetAttribute("IntroStringId",itrQuest->IntroStringId);
    pQuest->SetAttribute("TargetStringId",itrQuest->TargetStringId);
    pQuest->SetAttribute("ReplyTargetId",itrQuest->ReplyTargetId);
    pQuest->SetAttribute("AcceptTargetId", itrQuest->AcceptTargetId);
    pQuest->SetAttribute("IsRepeat",itrQuest->IsRepeat);
    pQuest->SetAttribute("HintLevelMin",itrQuest->HintLevelMin);
    pQuest->SetAttribute("HintLevelMax",itrQuest->HintLevelMax);
    pQuest->SetAttribute("MapId",itrQuest->MapId);
    pQuest->SetAttribute("IsCancel",itrQuest->IsCancel);
    pQuest->SetAttribute("CanAssist",itrQuest->CanAssist);
    pQuest->SetAttribute("CanShare",itrQuest->CanShare);
    pQuest->SetAttribute("RankId",itrQuest->RankId);//任务品质
    pQuest->SetAttribute("CanDisplay",itrQuest->CanDisplay);
	pQuest->SetAttribute("DisplayInCanAccept",itrQuest->bDisplayInCanAccept);
    pQuest->SetAttribute("IsSingleRequirement", itrQuest->IsSingleRequirement); // 是否单一条件完成
	pQuest->SetAttribute("Country", itrQuest->Country); // 是否单一条件完成

    // 添加Talk
    for( SQuest::QuestTalkAllIter it = itrQuest->vQuestTalks.begin(); 
        it != itrQuest->vQuestTalks.end(); ++ it )
    {
        MeXmlElement* pTalks = pQuest->InsertEndChild( "Talks" )->ToElement();

        int nPosition = (*it).first;
        QuestTalks& kTalks = (*it).second;
        pTalks->SetAttribute( "Position", nPosition );
        for( int nTalk = 0 ; nTalk < kTalks.size(); ++ nTalk )
        {
            SQuestTalk& kSingleTalk = kTalks[nTalk];
            MeXmlElement* pSingleTalk = pTalks->InsertEndChild( "Talk" )->ToElement();

            pSingleTalk->SetAttribute( "NpcId", kSingleTalk.nNpcId );
            pSingleTalk->SetAttribute( "StringId", kSingleTalk.nStringId );
			pSingleTalk->SetAttribute( "NpcAnim",kSingleTalk.nNpcAnim );
            for( int nOption = 0 ; nOption < kSingleTalk.vOptions.size(); ++ nOption )
            {
                SQuestOption& kOption = kSingleTalk.vOptions[nOption];
                MeXmlElement* pOption = pSingleTalk->InsertEndChild( "Option" )->ToElement();
                pOption->SetAttribute( "StringId", kOption.nStringId );
                for( int nOptionTalk = 0; nOptionTalk < kOption.vTalks.size(); ++ nOptionTalk )
                {
                    MeXmlElement* pOptionTalk = pOption->InsertEndChild( "Talk" )->ToElement();
                    pOptionTalk->SetAttribute( "NpcId", kOption.vTalks[nOptionTalk].nNpcId );
                    pOptionTalk->SetAttribute( "StringId", kOption.vTalks[nOptionTalk].nStringId );
                }
            }
        }
    }

    //3.1 添加quest的Rewards
    MeXmlElement* pRewards = pQuest->InsertEndChild(("Rewards"))->ToElement();
    for (SQuest::RewardType::iterator Rewarditr = itrQuest->stReward.begin();Rewarditr != itrQuest->stReward.end();++Rewarditr)
    {
        int nType = 0;
        MeXmlElement* pReward = pRewards->InsertEndChild(("Reward"))->ToElement();
        switch(Rewarditr->byType)
        {
        case    SQuest::eReward_Money:
        case    SQuest::eReward_Exp:
        case    SQuest::eReward_SkillExp:
        case    SQuest::eReward_Reputation:
        case    SQuest::eReward_Exploit:
        case    SQuest::eReward_Title:
        case    SQuest::eReward_GuildContribute:
        case    SQuest::eReward_JiaoZi:// jiaozi
        case    SQuest::eReward_Honor:  // 荣誉
		case    SQuest::eReward_CountryMoney: //国家金钱
		case    SQuest::eReward_ScriptExp://脚本经验
            {
                nType = Rewarditr->byType;
                pReward->SetAttribute("Type",nType);
                pReward->SetAttribute("Value",Rewarditr->Value);
                pReward->SetAttribute("Icon",Rewarditr->Icon);
            }
            break;
        case SQuest::eReward_Item:
        case SQuest::eReward_SpecialItem:
            {
                nType = Rewarditr->byType;
                pReward->SetAttribute("Type",nType);
                pReward->SetAttribute("Value",Rewarditr->Value);
                pReward->SetAttribute("Icon",Rewarditr->Icon);
                if (Rewarditr->Number > 0)
                {
                    pReward->SetAttribute("Count",Rewarditr->Number);
                }

                pReward->SetAttribute("IsBound", Rewarditr->bIsBound);

                pReward->SetAttribute("IsStarRandom", Rewarditr->bIsStarRandom);
                if (Rewarditr->bIsStarRandom == false)  // 如果随机星级为false，则最大星级无效，置为0
                {
                    Rewarditr->nStarLevel = 0;
                }
                pReward->SetAttribute("StarLevel", Rewarditr->nStarLevel);

                MeXmlElement* pCommit = pReward->InsertEndChild(("CommitRequirementTypes"))->ToElement();

                MeXmlElement* pRequirement1 = pCommit->InsertEndChild(("Requirement"))->ToElement();
                pRequirement1->SetAttribute("Type",SQuest::eRequirement_Sex);
                pRequirement1->SetAttribute("Value", Rewarditr->shSex);

                MeXmlElement* pRequirement2 = pCommit->InsertEndChild(("Requirement"))->ToElement();
                pRequirement2->SetAttribute("Type",SQuest::eRequirement_Profession);//StrToCommitRequirementType("Profession"));
                pRequirement2->SetAttribute("Value", Rewarditr->shProfession);
            }
            break;
        case    SQuest::eReward_Buff:
            {
                nType = SQuest::eReward_Buff;
                pReward->SetAttribute("Type",nType);
                pReward->SetAttribute("Value",Rewarditr->Value);
                pReward->SetAttribute("Icon",Rewarditr->Icon);

                MeXmlElement* pCommit = pReward->InsertEndChild(("CommitRequirementTypes"))->ToElement();
                MeXmlElement* pRequirement1 = pCommit->InsertEndChild(("Requirement"))->ToElement();
                pRequirement1->SetAttribute("Type",SQuest::eRequirement_Level);
                pRequirement1->SetAttribute("Value", Rewarditr->Number);
            }
            break;
        case    SQuest::eReward_ChangeRoleVar:
            {
                nType = SQuest::eReward_ChangeRoleVar;
                pReward->SetAttribute("Type",nType);
                pReward->SetAttribute("Value",Rewarditr->Value);
                pReward->SetAttribute("Icon",Rewarditr->Icon);

                MeXmlElement* pCommit = pReward->InsertEndChild(("CommitRequirementTypes"))->ToElement();
                MeXmlElement* pRequirement1 = pCommit->InsertEndChild(("Requirement"))->ToElement();
                pRequirement1->SetAttribute("Type",SQuest::eRequirement_Var);
                pRequirement1->SetAttribute("Value", Rewarditr->Number);
            }
            break;
        default:
            break;
        }
    }

    //3.1 添加quest的CommitRequirements
    MeXmlElement* pCommitRequirement = pQuest->InsertEndChild(("CommitRequirements"))->ToElement();
    for (SQuest::RequirementType::iterator itrCommitType = itrQuest->stCommitRequirement.begin();itrCommitType != itrQuest->stCommitRequirement.end();++itrCommitType)
    {
        MeXmlElement* pRequirement = pCommitRequirement->InsertEndChild(("Requirement"))->ToElement();
        int writeType = 0;
        writeType = itrCommitType->byType;
        pRequirement->SetAttribute("Type",writeType);
        pRequirement->SetAttribute("Value",itrCommitType->Value);
        if (itrCommitType->MaxNum > 0)
        {
            pRequirement->SetAttribute("Count",itrCommitType->MaxNum);
        }
        if ( writeType == SQuest::eRequirement_Var) //如果类型是计数变量，则保存一个字串ID
        {
            pRequirement->SetAttribute("StringId", itrCommitType->nStringID);   // 保存对应的字串ID
        }
        if(writeType ==  SQuest::eRequirement_Item||
            writeType == SQuest::eRequirement_Monster||
            writeType == SQuest::eRequirement_Var ||
            writeType == SQuest::eRequirement_VarLimit)
        {
            MeXmlElement* Param1 = pRequirement->InsertEndChild(("Param"))->ToElement();
            Param1->SetAttribute("Value",itrCommitType->wVar);
        }
    }


    //3.2 添加quest的ReceiveRequirements
    MeXmlElement* pReceiveRequirements = pQuest->InsertEndChild(("ReceiveRequirements"))->ToElement();
    for (SQuest::RequirementType::iterator itrReceiveType = itrQuest->stReceiveRequirement.begin();itrReceiveType != itrQuest->stReceiveRequirement.end();++itrReceiveType)
    {
        MeXmlElement* pRequirement = pReceiveRequirements->InsertEndChild(("Requirement"))->ToElement();

        int writeType = 0;
        writeType = itrReceiveType->byType;
        pRequirement->SetAttribute("Type",writeType);
        pRequirement->SetAttribute("Value",itrReceiveType->Value);
        if ( itrReceiveType->MaxNum > 0)
        {
            pRequirement->SetAttribute("Count",itrReceiveType->MaxNum);
        }
        if ( writeType == SQuest::eRequirement_Var )    // 如果类型是计数变量，则保存该计数变量对应的字串ID
        {
            pRequirement->SetAttribute("StringId", itrReceiveType->nStringID);  // 对应的字串ID
        }
        if ( writeType ==  SQuest::eRequirement_Item||
            writeType == SQuest::eRequirement_Monster||
            writeType == SQuest::eRequirement_Var ||
            writeType == SQuest::eRequirement_VarLimit )
        {
            MeXmlElement* param = pRequirement->InsertEndChild(("Param"))->ToElement();
            param->SetAttribute("Value",itrReceiveType->wVar);
        }
    }



    if (!XmlDoc.SaveFile(QuestFileName))
    {
#if (!_CONVERT_)
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_INFO ,"Save %d Quests",itrQuest->Id);
#endif
        return false;
    }

    return true;
}

bool QuestInfo::SaveQuest(const char* pFilePath)
{
    if (pFilePath == NULL||strlen(pFilePath) == 0)
    {
        pFilePath = QUESTS_FILEPATH;
    }
    Common::_tstring path = pFilePath;
    if (path[path.size()-1]!= '\\')
    {
        path += "\\";
    }
    path += "Common.quest";
    SaveCommonFile(path.toNarrowString().c_str());

    for (SQuests::iterator iter = m_pQuests.begin();iter != m_pQuests.end();++iter)
    {
        path = pFilePath;
        if (path[path.size()-1]!= '\\')
        {
            path += "\\Client\\";
        }
        char FileFormat[61] = { 0 };
        sprintf_s(FileFormat,sizeof( FileFormat ) - 1,QUESTS_FILE_FOMAT,iter->first);
        path += FileFormat;
        SaveQuestFile(path.toNarrowString().c_str(),iter->second);
    }

    return true;
}

bool    QuestInfo::RemoveQuest(int id)
{
    if (id<dr_MinQuestId||id>dr_MaxQuestId)
    {
        return false;
    }

    itrSQuests itr = m_pQuests.find(id);
    if (itr == m_pQuests.end())
    {
        return false;
    }
    itr->second->Id = DeleteQuest;

    return true;
}

const char* QuestInfo::GetRequirementType(int id)
{
    if (id < 0||id > SQuest::eRequirement_Max)
    {
        return NULL;
    }
    return RequirementString[id];
}

bool    QuestInfo::ModifyRequirementString(int id,char* pString)
{
    if (id <0 || id>SQuest::eRequirement_Max)
    {
        return false;
    }
    if (!pString)
    {
        return false;
    }
    strncpy_s(RequirementString[id],_nMaxStringLength,pString,_nMaxStringLength);
    return true;
}

bool    QuestInfo::ModifyRewardString(int id,char* pString)
{
    if (id <0 || id>SQuest::eRequirement_Max)
    {
        return false;
    }
    if (!pString)
    {
        return false;
    }
    strncpy_s(RewardString[id],_nMaxStringLength,pString,_nMaxStringLength);
    return true;
}

bool    QuestInfo::ModifyQuestRankString(int id,char* pstring)
{
    if (id <0 || id>SQuest::eRequirement_Max)
    {
        return false;
    }
    if (!pstring)
    {
        return false;
    }
    strncpy_s(RewardString[id],_nMaxStringLength,pstring,_nMaxStringLength);
    return true;
}

#endif
const char* QuestInfo::GetRewardType(int id)
{
    if(id < 0 || id >= SQuest::eReward_Max)
    {
        return "";
    }

    return RewardString[id];
}

bool QuestInfo::AddQuest( const SQuest* pQuest )
{
    if (!pQuest)
    {
        return false;
    }

	SQuests::iterator finditr = m_pQuests.find(pQuest->Id);
    if (finditr != m_pQuests.end())
    {
        if (finditr->second->Id == DeleteQuest)
        {
            *(finditr->second) = *pQuest;
            return true;
        }
        return false;
    }
    SQuest* pNewQuest =  CNewWithDebug<SQuest>::Alloc(1, "QuestInfo::CreateQuest中创建SQuest");

    bool isHaveRequirementType = true;

    *pNewQuest = *pQuest;
    m_pQuests.insert(SQuests::value_type(pNewQuest->Id,pNewQuest));

    return true;
}

bool QuestInfo::ParseCommitRequirementTypes( MeXmlElement* requirementsElement, SQuest* Quest )
{
    if (!requirementsElement||!Quest)
    {
        return false;
    }
    int nTempValue = 0;

    MeXmlElement* requirementElement = requirementsElement->FirstChildElement();
    while ( requirementElement != NULL )
    {
        nTempValue = 0;
        int nType = 0;
        //Requirement requirement;

        requirementElement->Attribute( "Type", &nType );
        //int emunid = nType;//StrToRequirementType(CommitRequirementTypes_[nType].c_str());

        SQuestRequirement squestrequirement;
        int tempvalue = 0;
        squestrequirement.byType = nType;
        requirementElement->Attribute( "Value", &tempvalue );
        squestrequirement.Value = tempvalue;
        tempvalue = 0;
        requirementElement->Attribute( "Count", &tempvalue );
        if (tempvalue < 0)
        {
            squestrequirement.MaxNum = 0;
        }
        else
            squestrequirement.MaxNum = tempvalue;

        if ( nType == SQuest::eRequirement_Var ) // 如果类型是计数变量，则Load计数变量
        {
            requirementElement->Attribute("StringId", &tempvalue);
            squestrequirement.nStringID = tempvalue;
        }

        if( nType == SQuest::eRequirement_Var||
            nType == SQuest::eRequirement_Monster||
            nType == SQuest::eRequirement_Item || 
            nType == SQuest::eRequirement_VarLimit )
        {
            MeXmlElement* pParam = requirementElement->FirstChildElement("Param");
            if (pParam)
            {
                pParam->Attribute("Value",&tempvalue);
                squestrequirement.wVar = tempvalue;
            }
        }

        Quest->AddCommitRequirement(&squestrequirement);
        requirementElement = requirementElement->NextSiblingElement();
    }
    return true;
}

bool QuestInfo::ParseCommitRequirementTypes( MeXmlElement* requirementsElement, SQuestReward* QuestReward )
{
    if (!requirementsElement||!QuestReward)
    {
        return false;
    }

    MeXmlElement* CommitElement = requirementsElement->FirstChildElement();

    while ( CommitElement != NULL )
    {
        int Value = 0;
        int type = 0;
        CommitElement->Attribute("Type",&type);
        switch (type)
        {
        case SQuest::eRequirement_Sex:

            {
                CommitElement->Attribute("Value",&Value);
                if (Value < 0||Value > Sex_Max)
                {
                    Value = Sex_Max;
                }
                QuestReward->shSex = Value;
            }
            break;
        case SQuest::eRequirement_Level:
            {
                CommitElement->Attribute("Value",&Value);
                if (Value < 0)
                {
                    Value = 1;//buff level
                }
                QuestReward->Number = Value;
            } 
            break;
        case SQuest::eRequirement_Var:
        case SQuest::eRequirement_VarLimit:

            {
                CommitElement->Attribute("Value",&Value);
                //                 if (Value < 0)
                //                 {
                //                     Value = 0;//变量的值
                //                 }
                QuestReward->Number = Value;
            }
            break;
        case SQuest::eRequirement_Profession:
            {
                if (CommitElement->Attribute("Value",&Value) != NULL)
                {
                    QuestReward->shProfession = Value;
                }                
            }
        default :
            break;
        }

        CommitElement = CommitElement->NextSiblingElement();
    }

    return true;
}
bool QuestInfo::ParseTalks(MeXmlElement* talksElement, SQuest* Quest)
{
    if( !talksElement || !Quest )
        return false;

    int nPosition = 0;
    talksElement->Attribute( "Position", &nPosition );

    MeXmlElement* talkElement = talksElement->FirstChildElement();
    while( talkElement != NULL )
    {
        int nNpcId = InvalidLogicNumber;
        int nStringId = InvalidLogicNumber;
		int nNpcAnim = InvalidLogicNumber;
        SQuestTalk kTalk;

        // read values
        if( !talkElement->Attribute( "NpcId", &nNpcId ) )
        {
            talkElement = talkElement->NextSiblingElement( "Talk" );
            continue;
        }
        if( !talkElement->Attribute( "StringId", &nStringId ) )
        {
            talkElement = talkElement->NextSiblingElement( "Talk" );
            continue;
        }

		if( !talkElement->Attribute( "NpcAnim", &nNpcAnim ) )
		{
            talkElement = talkElement->NextSiblingElement( "Talk" );
            continue;
		}

        // assign values
        kTalk.nNpcId = nNpcId;
        kTalk.nStringId = nStringId;
		kTalk.nNpcAnim  = nNpcAnim;

        // find options
        MeXmlElement* pOption = talkElement->FirstChildElement( "Option" );
        while( pOption )
        {
            int nOptionStringId = InvalidLogicNumber;
            if( !pOption->Attribute( "StringId", &nOptionStringId ) )
            {
                pOption = pOption->NextSiblingElement( "Option" );
                continue;
            }
            SQuestOption kOption;
            kOption.nStringId = nOptionStringId;
            // find talk
            MeXmlElement* pOptionTalk = pOption->FirstChildElement( "Talk" );
            while( pOptionTalk )
            {
                int nOptionTalkNpcId = InvalidLogicNumber;
                int nOptionTalkStringId = InvalidLogicNumber;

                // read values
                if( !pOptionTalk->Attribute( "NpcId", &nOptionTalkNpcId ) )
                {
                    pOptionTalk = pOptionTalk->NextSiblingElement( "Talk" );
                    continue;
                }
                if( !pOptionTalk->Attribute( "StringId", &nOptionTalkStringId ) )
                {
                    pOptionTalk = pOptionTalk->NextSiblingElement( "Talk" );
                    continue;
                }
                SQuestTalk kOptionTalk;
                kOptionTalk.nNpcId = nOptionTalkNpcId;
                kOptionTalk.nStringId = nOptionTalkStringId;

                // add to option's talk list
                kOption.vTalks.push_back( kOptionTalk );

                // next option talk
                pOptionTalk = pOptionTalk->NextSiblingElement( "Talk" );
            }

            // add option to talk
            kTalk.vOptions.push_back( kOption );

            // next option
            pOption = pOption->NextSiblingElement( "Option" );
        }

        // add to container
        if( nPosition >= QuestManager::HSTT_ToGain && 
            nPosition < QuestManager::HSTT_Count )
        {
            Quest->vQuestTalks[nPosition].push_back( kTalk );
        }

        // go ahead
        talkElement = talkElement->NextSiblingElement( "Talk" );
    }
    return true;
}

bool QuestInfo::ParseRewards(MeXmlElement* rewardsElement , SQuest* Quest)
{
    if (!rewardsElement||!Quest)
    {
        return false;
    }
    bool haveError = false;
    int nTempValue = 0; 
    MeXmlElement* rewardElement = rewardsElement->FirstChildElement();
    while ( rewardElement != NULL )
    {
        nTempValue = 0;
        int nTpye = 0;
        //Reward reward;
        SQuestReward reward;
        reward.ClearReward();

        rewardElement->Attribute( "Type", &nTpye );
        //StrToRewardType(GetRewardType(nTpye));
        switch (nTpye)
        {
        case SQuest::eReward_Money:
        case SQuest::eReward_JiaoZi:
        case SQuest::eReward_Exp:
        case SQuest::eReward_SkillExp:
        case SQuest::eReward_Reputation:
        case SQuest::eReward_Exploit:
        case SQuest::eReward_Title:
        case SQuest::eReward_GuildContribute:
        case SQuest::eReward_Honor:
		case SQuest::eReward_CountryMoney:
		case SQuest::eReward_ScriptExp://脚本经验
            {
                int tempValue = 0;
                rewardElement->Attribute("Value",&tempValue);
                reward.byType = nTpye;
                reward.Value  = tempValue;

                int Icon = 0;
                rewardElement->Attribute( "Icon", &Icon);
                reward.Icon   = Icon;
                if (reward.Icon == 0)
                {
                    reward.Icon = FindDefaultIconByType(nTpye);
                }
                Quest->AddReward(&reward);
            }
            break;
        case SQuest::eReward_Item:
        case SQuest::eReward_SpecialItem:
            {
                int ItemId = 0;
                int ItemNum = 0;
                reward.byType = nTpye;
                rewardElement->Attribute("Value",&ItemId);
                reward.Value = ItemId;

                int Icon = 0;
                rewardElement->Attribute( "Icon", &Icon);
                reward.Icon   = Icon;
                if (reward.Icon == 0)
                {
                    reward.Icon = FindDefaultIconByType(nTpye);
                }

                rewardElement->Attribute("Count",&ItemNum);
                MeXmlElement *parameter = rewardElement->FirstChildElement("CommitRequirementTypes");
                ParseCommitRequirementTypes(parameter,&reward);
                if ( ItemNum == 0 )
                {
                    ItemNum = 1;
                }
                reward.Number = ItemNum;

                int nIsStarRandom = 0;
                rewardElement->Attribute("IsStarRandom",&nIsStarRandom);
                reward.bIsStarRandom = nIsStarRandom;

                int nStarLevel = 0;
                rewardElement->Attribute("StarLevel",&nStarLevel);
                reward.nStarLevel = nStarLevel;

                int nBound = 1;
                if ( rewardElement->Attribute("IsBound", &nBound) == NULL ) // 如果没有该字段，则默认为True
                {
                    reward.bIsBound = true;
                }
                else
                {
                    reward.bIsBound = nBound;
                }


                Quest->AddReward(&reward);
            }
            break;
        case SQuest::eReward_Buff:
            {
                int BuffId = 0;
                int ItemNum = 0;
                reward.byType = SQuest::eReward_Buff;
                rewardElement->Attribute("Value",&BuffId);
                reward.Value = BuffId;

                int Icon = 0;
                rewardElement->Attribute( "Icon", &Icon);
                reward.Icon   = Icon;
                if (reward.Icon == 0)
                {
                    reward.Icon = FindDefaultIconByType(nTpye);
                }

                MeXmlElement *parameter = rewardElement->FirstChildElement("CommitRequirementTypes");
                ParseCommitRequirementTypes(parameter,&reward);
                rewardElement->Attribute("Count",&ItemNum);
                if ( ItemNum == 0 )
                {
                    ItemNum = 1;
                }
                reward.Number = ItemNum;
                Quest->AddReward(&reward);
            }
            break;
        case SQuest::eReward_ChangeRoleVar:
            {
                int VarId = 0;
                int ItemNum = 0;
                reward.byType = SQuest::eReward_ChangeRoleVar;
                rewardElement->Attribute("Value",&VarId);
                reward.Value = VarId;

                int Icon = 0;
                rewardElement->Attribute( "Icon", &Icon);
                reward.Icon   = Icon;
                if (reward.Icon == 0)
                {
                    reward.Icon = FindDefaultIconByType(nTpye);
                }

                MeXmlElement *parameter = rewardElement->FirstChildElement("CommitRequirementTypes");
                ParseCommitRequirementTypes(parameter,&reward);
                rewardElement->Attribute("Count",&ItemNum);
                if ( ItemNum == 0 )
                {
                    ItemNum = 1;
                }
                reward.Number = ItemNum;
                Quest->AddReward(&reward);
            }
            break;
        case SQuest::eReward_Max:
            {
                haveError = true;
            }
            break;
        default:
            haveError = true;
            //reward.Value = nTempValue;
            break;
        }


        rewardElement = rewardElement->NextSiblingElement();
    }
    if (haveError)
    {
        return false;
    }
    return true;
}

int     QuestInfo::FindReceiveRequirementType( const char* pszString )
{
    if (!pszString||strlen(pszString) == 0)
    {
        return -1;
    }

    for (RequirementTypes::iterator itr = ReceiveRequirementTypes_.begin();itr!=ReceiveRequirementTypes_.end();++itr)
    {
        if(itr->second.compare(pszString) == 0)
        {
            return (int)itr->first;
        }
    }

    return -1;
}

int QuestInfo::FindCommitRequirementType( const char* pszString )
{
    if( !pszString )
        return -1;

    for(RequirementTypes::iterator iterCommit = CommitRequirementTypes_.begin();iterCommit != CommitRequirementTypes_.end();++iterCommit)
    {
        if(iterCommit->second.compare(pszString) == 0)
        {
            return iterCommit->first;
        }
    }
    return -1;
}


int     QuestInfo::FindRewardTypes( const char* pszString )
{
    if (!pszString)
    {
        return -1;
    }
    for (RewardTypes::iterator itr = rewardTypes_.begin();itr!=rewardTypes_.end();++itr)
    {
        if(itr->second.Value.compare(pszString) == 0)
        {
            return (int)itr->first;
        }
    }

    return -1;
}

bool    QuestInfo::ParseCommondData(const char* FileName)
{
    if (!FileName||strlen(FileName)==0)
    {
        return false;
    }
    MeXmlDocument xmlDoc;
    if (!xmlDoc.LoadFile(FileName))
    {
        return false;
    }
    MeXmlElement* pProjectRoot = xmlDoc.FirstChildElement("Project")->ToElement();
    if (pProjectRoot == NULL)
    {
        return false;
    }
    MeXmlElement* rewardTypeElement = pProjectRoot->FirstChildElement( "RewardTypes" )->ToElement();
    // Reward element.  
    rewardTypes_.clear();
    if ( rewardTypeElement != NULL )
    {
        MeXmlElement* typeElement = rewardTypeElement->FirstChildElement()->ToElement();

        while ( typeElement !=  NULL)
        {
            int id = 0;
            typeElement->Attribute( "Id", &id );
            Common::_tstring strings;
            strings.fromUTF8(typeElement->Attribute( "Value" ));

            int nDefaultIconId = 0;
            typeElement->Attribute("DefaultIcon",&nDefaultIconId);

            RewardTypes::iterator rewardItr = rewardTypes_.find(id);
            if (rewardItr != rewardTypes_.end())
            {
                rewardItr->second.Value = strings;
                rewardItr->second.DefauleIconId = nDefaultIconId;
            }
            else
            {
                SRewardType Date;
                Date.Value = typeElement->Attribute( "Value" ) ;
                Date.DefauleIconId = nDefaultIconId;
                rewardTypes_.insert( RewardTypes::value_type( id, Date ) );
            }
            //AddRewardType( id,strings.c_str() );

            typeElement = typeElement->NextSiblingElement();
        }
    }

    //Requirement element, insert to container.
    ReceiveRequirementTypes_.clear();
    MeXmlElement* ReceiveRequirementTypeElement = pProjectRoot->FirstChildElement( "ReceiveRequirementTypes" )->ToElement();  
    if ( ReceiveRequirementTypeElement != NULL )
    {
        MeXmlElement* typeElement = ReceiveRequirementTypeElement->FirstChildElement()->ToElement();
        while ( typeElement != NULL )
        {
            int id = 0;
            typeElement->Attribute( "Id", &id );
            Common::_tstring strings;
            strings.fromUTF8(typeElement->Attribute( "Value" ));

            RequirementTypes::iterator finditr =  ReceiveRequirementTypes_.find(id);
            if (finditr != ReceiveRequirementTypes_.end())
            {
                finditr->second = strings;
            }
            else
                ReceiveRequirementTypes_.insert( RequirementTypes::value_type( id, typeElement->Attribute( "Value" ) ) );
            typeElement = typeElement->NextSiblingElement();
        }
    }

    CommitRequirementTypes_.clear();
    MeXmlElement* CommitRequirementTypeElement = pProjectRoot->FirstChildElement( "CommitRequirementTypes" )->ToElement();  
    if ( CommitRequirementTypeElement != NULL )
    {
        MeXmlElement* typeElement = CommitRequirementTypeElement->FirstChildElement()->ToElement();
        while ( typeElement != NULL )
        {
            int id = 0;
            typeElement->Attribute( "Id", &id );

            Common::_tstring strings;
            strings.fromUTF8(typeElement->Attribute( "Value" ));
            RequirementTypes::iterator finditr =  CommitRequirementTypes_.find(id);
            if (finditr != CommitRequirementTypes_.end())
            {
                finditr->second = strings;
            }
            else
                CommitRequirementTypes_.insert( RequirementTypes::value_type( id, typeElement->Attribute( "Value" ) ) );
            //strncpy_s(RequirementString[id],_nMaxStringLength, strings.c_str(),strings.size());
            typeElement = typeElement->NextSiblingElement();
        }
    }

    MeXmlElement* QuestRankTypeElement = pProjectRoot->FirstChildElement( "Ranks" )->ToElement();  
    if ( QuestRankTypeElement != NULL )
    {
        MeXmlElement* typeElement = QuestRankTypeElement->FirstChildElement()->ToElement();
        while ( typeElement != NULL )
        {
            int id = 0;
            typeElement->Attribute( "Id", &id );
            if (id<0||id>SQuest::eQuestRank_Max)
            {
                typeElement = typeElement->NextSiblingElement();
                continue;
            }
            Common::_tstring strings;
            strings.fromUTF8(typeElement->Attribute( "Value" ));
            strncpy_s(RankString[id],_nMaxStringLength,strings.c_str(),_nMaxStringLength-1);
            typeElement = typeElement->NextSiblingElement();
        }
    }

    // 任务类型读取
    _QuestType.clear();
    MeXmlElement* QuestTypeElements = pProjectRoot->FirstChildElement( "QuestTypes" )->ToElement();
    if ( QuestTypeElements != NULL )
    {
        MeXmlElement* QuestTypeElement = QuestTypeElements->FirstChildElement("Type")->ToElement();
        while (QuestTypeElement != NULL)
        {
            SQuestType* pQuestType = new SQuestType;
            if (pQuestType == NULL)
            { return false;}

            int typeId = 0;
            QuestTypeElement->Attribute("Id", &typeId);
            pQuestType->Id = typeId;

            Common::_tstring strDesc;
            strDesc.fromUTF8(QuestTypeElement->Attribute("Description"));
            pQuestType->QuestTypeDesc = strDesc;

            Common::_tstring strIcon;
            strIcon.fromUTF8(QuestTypeElement->Attribute("Icon"));
            pQuestType->QuestTypeIcon = strIcon;

            _QuestType.push_back(pQuestType);
            QuestTypeElement = QuestTypeElement->NextSiblingElement();
        }
    }

    return true;
}

char *u_basename(char *s)
{
	int i = 0;
	for (i = strlen(s); i>=0; i--)
	{
		if ((s[i]=='\\') || (s[i]=='/'))
		{
			break;
		}
	}
	return &(s[i+1]);
}
bool QuestInfo::LoadQuest( const char* pFilePath ,bool isCipher)
{
	bool result = true;
	Common::_tstring sourceFilePath = pFilePath;
	if (sourceFilePath[sourceFilePath.size()-1] != '\\')
	{
		sourceFilePath += "\\";
	}

	Common::_tstring FilePath;
	//Init 
	for (itrSQuests itRelease = m_pQuests.begin();itRelease != m_pQuests.end();)
	{
		CNewWithDebug<SQuest>::Free(itRelease->second);
		itRelease->second = NULL;
		itRelease = m_pQuests.erase(itRelease);
	}
	m_pQuests.clear();

	//read Common File
	FilePath  = sourceFilePath;
	char CommFormat[101] = { 0 };
	sprintf_s(CommFormat,sizeof( CommFormat ) - 1,"Common.quest");
	FilePath += CommFormat;
	ParseCommondData( FilePath.toNarrowString().c_str() );

	/*	MeXmlDocument xMeXml;
	std::string path=pFilePath;
	path+="\\quest.xml";
	if (!xMeXml.LoadFile( path.c_str() ))
	{ return false; }
	MeXmlElement* pRoot = xMeXml.FirstChildElement("mapping");
	if(!pRoot)return false;
	MeXmlElement*pconfiginfo1 = pRoot->FirstChildElement("fileMd5");
	while (pconfiginfo1)
	{
	char * file=(char *)pconfiginfo1->Attribute("fileName");
	if(!file)
	{
	pconfiginfo1= pconfiginfo1->NextSiblingElement();
	continue;
	}
	std::string strname = file;
	int  nfilename,nfilesize;
	pconfiginfo1->QueryIntAttribute("md5",&nfilename);
	pconfiginfo1->QueryIntAttribute("file",&nfilesize);
	{
	//检查文件名
	char * filename=u_basename((char *)strname.c_str());
	bool bOk = CheckQuestName(filename);

	std::string s;
	s=filename;

	if(s.find(".string")!=std::string::npos)
	{
	char szStringFile[_MAX_PATH + 1] = "";
	sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%sClient\\%s", sourceFilePath.toNarrowString().c_str(), filename);
	theXmlString.LoadStringFile(szStringFile, false, false, false);
	bOk=false;
	}

	if(s.find(".quest")==std::string::npos)
	{
	bOk=false;
	}

	if( !bOk )
	{
	pconfiginfo1= pconfiginfo1->NextSiblingElement();
	continue;
	}

	char szQuestFile[_MAX_PATH + 1] = {0};
	sprintf_s(szQuestFile, sizeof(szQuestFile) - 1, "%sClient\\%s", sourceFilePath.toNarrowString().c_str(), filename);

	bool nResult = ParseQuest(szQuestFile); //加载
	if (!nResult)
	{
	#ifdef _CLIENT_
	char szMsg[256] = {0};
	sprintf_s(szMsg, sizeof(szMsg)-1, "ParseQuest %s Error!\n", szQuestFile);
	OutputDebugStringA(szMsg);
	#elif (!_CONVERT_)
	LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load %s Quest File Error!",szQuestFile);
	#endif
	//		result = false;
	}
	}
	pconfiginfo1= pconfiginfo1->NextSiblingElement();
	}

	*/
	//packet * pack=packet_namespace::findpacket("..\\data\\Quest.data");
	packet * pack=packet_namespace::findpacket("Data6.tz");
	if(pack)
	{
		string_hash<fileinfo*> m_areas =pack->GetPacketFileList();
		for (packet::AreaHash::iterator itr = m_areas.begin(); itr != m_areas.end(); ++itr)//只增加有用的
		{

			//检查文件名
			char * filename=u_basename(itr->second->area.name);
			bool bOk = CheckQuestName(filename);

			std::string s;
			s=filename;
			if(s.find(".string")!=std::string::npos)
			{
				char szStringFile[_MAX_PATH + 1] = "";
				sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%sClient\\%s", sourceFilePath.toNarrowString().c_str(), filename);
				theXmlString.LoadStringFile(szStringFile, false, false, false);
				bOk=false;
			}
			else if(s.find(".quest")!=std::string::npos)
			{
					char szQuestFile[_MAX_PATH + 1] = {0};
					sprintf_s(szQuestFile, sizeof(szQuestFile) - 1, "%sClient\\%s", sourceFilePath.toNarrowString().c_str(), filename);

					bool nResult = ParseQuest(szQuestFile); //加载
					if (!nResult)
					{
#ifdef _CLIENT_
						char szMsg[256] = {0};
						sprintf_s(szMsg, sizeof(szMsg)-1, "ParseQuest %s Error!\n", szQuestFile);
						OutputDebugStringA(szMsg);
#elif (!_CONVERT_)
						LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load %s Quest File Error!",szQuestFile);
#endif
						//		result = false;
					}
			}
		}
	}
	else
	{
		char szFile[_MAX_PATH + 1] = "";
		sprintf_s(szFile, sizeof(szFile) - 1, "%sClient\\*%s", sourceFilePath.toNarrowString().c_str(), Bin_Quest_Ext);
		WIN32_FIND_DATA xFindData;
		HANDLE hFile = FindFirstFile(szFile, &xFindData);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			do
			{
				std::string s;
				s=xFindData.cFileName;
				if(s.find(".string")!=std::string::npos)
				{
					char szStringFile[_MAX_PATH + 1] = "";
					sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%sClient\\%s", sourceFilePath.toNarrowString().c_str(), xFindData.cFileName);
					theXmlString.LoadStringFile(szStringFile, false, false, false);
					continue;
				}


				//检查文件名
				bool bOk = CheckQuestName(xFindData.cFileName);
				if( !bOk )
					continue;

				char szQuestFile[_MAX_PATH + 1] = {0};
				sprintf_s(szQuestFile, sizeof(szQuestFile) - 1, "%sClient\\%s", sourceFilePath.toNarrowString().c_str(), xFindData.cFileName);

				bool nResult = ParseBinQuest(szQuestFile); //加载
				if (!nResult)
				{
#ifdef _CLIENT_
					char szMsg[256] = {0};
					sprintf_s(szMsg, sizeof(szMsg)-1, "ParseBinQuest %s Error!\n", szQuestFile);
					OutputDebugStringA(szMsg);
#elif (!_CONVERT_)
					LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load %s Quest File Error!",szQuestFile);
#endif
					result = false;
				}
			}while(FindNextFile(hFile, &xFindData));                      
			FindClose(hFile);
		}
		else
		{
			sprintf_s(szFile, sizeof(szFile) - 1, "%sClient\\*.*", sourceFilePath.toNarrowString().c_str());
			WIN32_FIND_DATA xFindData;
			HANDLE hFile = FindFirstFile(szFile, &xFindData);
			if(hFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					std::string s;
					s=xFindData.cFileName;
					if(s.find(".string")!=std::string::npos)
					{
						char szStringFile[_MAX_PATH + 1] = "";
						sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%sClient\\%s", sourceFilePath.toNarrowString().c_str(), xFindData.cFileName);
						theXmlString.LoadStringFile(szStringFile, false, false, false);
					}
					else if(s.find(".quest")!=std::string::npos)
					{
						//检查文件名
						bool bOk = CheckQuestName(xFindData.cFileName);
						if( !bOk )
							continue;

						char szQuestFile[_MAX_PATH + 1] = {0};
						sprintf_s(szQuestFile, sizeof(szQuestFile) - 1, "%sClient\\%s", sourceFilePath.toNarrowString().c_str(), xFindData.cFileName);

						if (isCipher)
						{
							int length = strlen(szQuestFile);
							if (length > 1)
							{
								szQuestFile[length - 1] = '\0';
							}
						}
						bool nResult = ParseQuest(szQuestFile); //加载
						if (!nResult)
						{
#if (!_CLIENT_) && (!_CONVERT_)
							LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load %s Quest File Error!",szQuestFile);
#endif
							result = false;
						}
					}
				}while(FindNextFile(hFile, &xFindData));                      
				FindClose(hFile);
			}
		}
	}
	//     for (int i = dr_MinQuestId;i != dr_MaxQuestId ; ++i)
	//     {
	//         FilePath = pFilePath;
	//         char TashFormat[50];
	//         sprintf_s(TashFormat,50,QUESTS_TASKFILE_FOMAT,i);
	//         FilePath += TashFormat;
	//         
	//         ParseTask(FilePath.toNarrowString().c_str());
	//     }
#if (!_CLIENT_) && (!_CONVERT_)
	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO ,"Total Load %d Quests",m_pQuests.size());

	// 加载概率
	char szStringFile[_MAX_PATH + 1] = "";
	sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%s%s", sourceFilePath.toNarrowString().c_str(), QUESTRAND_FILEPATH );
	theQuestManager.LoadQuestRandConfigFile( szStringFile );

#endif

	return result;
}

QuestInfo& QuestInfo::Instance()
{
    static QuestInfo CQuestInfo;
    return CQuestInfo;
}

bool QuestInfo::ParseQuest(const char* FileName)
{
    if (!FileName||strlen(FileName) == 0)
    {
        return false;
    }

    MeXmlDocument xmlDoc;
    if (!xmlDoc.LoadFile(FileName,1))
    {
        return false;
    }

    MeXmlElement*Root = xmlDoc.FirstChildElement("Project");
    if (Root == NULL)
    {
        return false;
    }

    MeXmlElement* questElement = Root->FirstChildElement("Quest");

    if ( questElement != NULL )
    {
        int nTempValue = 0;
        SQuest Quest ;//= CNewWithDebug<SQuest>::Alloc(1, "QuestInfo::CreateQuest中创建SQuest");

        questElement->Attribute( "Id", &nTempValue);
        if(nTempValue < dr_MinQuestId || nTempValue > dr_MaxQuestId)
        {
#if (!_CLIENT_) && (!_CONVERT_)
            LOG_MESSAGE(SCRIPTOBJECT,LOG_PRIORITY_ERROR,"%d Quest Id Error!Add Quest Fail");
#endif
            return false;
        }
        Quest.Id  = nTempValue;

        questElement->Attribute( "Name" , &nTempValue );
        if (nTempValue < -1)
        {
            nTempValue = -1;
        }
        Quest.QuestName = nTempValue;

        questElement->Attribute( "QuestType" , &nTempValue );
        if (nTempValue < 0) { nTempValue = 0;}
        Quest.chQuestType = nTempValue;

        questElement->Attribute( "IntroStringId" , &nTempValue );
        if (nTempValue < -1)
        {
            nTempValue = -1;
        }
        Quest.IntroStringId = nTempValue;

        questElement->Attribute( "TargetStringId" , &nTempValue );
        if (nTempValue < -1)
        {
            nTempValue = -1;
        }
        Quest.TargetStringId = nTempValue;

        questElement->Attribute( "ReplyTargetId" , &nTempValue );
        if (nTempValue < -1)
        {
            nTempValue = -1;
        }
        Quest.ReplyTargetId = nTempValue;

        questElement->Attribute("AcceptTargetId", &nTempValue);
        if (nTempValue < -1)
        {
            nTempValue = -1;
        }
        Quest.AcceptTargetId = nTempValue;

        int Repeat = 0 ;
        questElement->Attribute( "IsRepeat" ,&Repeat);
        Quest.IsRepeat = Repeat;

        int bCan = 1;
        questElement->Attribute( "CanAssist" ,&bCan );
        Quest.CanAssist = bCan;

        questElement->Attribute( "CanShare" ,&bCan );
        Quest.CanShare = bCan;

        if (questElement->Attribute( "CanDisplay" ,&bCan ) == NULL)
            Quest.CanDisplay = true;
        else
            Quest.CanDisplay = bCan;
		if (questElement->Attribute( "DisplayInCanAccept" ,&bCan ) == NULL)
			Quest.bDisplayInCanAccept = true;
		else
			Quest.bDisplayInCanAccept = bCan;

        int bSingleRequire = 0;
        if (questElement->Attribute("IsSingleRequirement", &bSingleRequire) == NULL)// 如果没有该字段，则为非单一条件
        { Quest.IsSingleRequirement = false;}
        else
        { Quest.IsSingleRequirement = bSingleRequire;}

		if(questElement->Attribute("Country", &nTempValue) == NULL)
		{ Quest.Country = 0;}
		else
		{ Quest.Country = nTempValue;}

        questElement->Attribute("IsCancel",&nTempValue);
        Quest.IsCancel = nTempValue;

        questElement->Attribute("HintLevelMin",&nTempValue);
        if (nTempValue < 0)
        {
            nTempValue = 0;
        }
        if (nTempValue > 200)
        {
            nTempValue = 200;
        }
        Quest.HintLevelMin = (BYTE)nTempValue;

        questElement->Attribute("HintLevelMax",&nTempValue);
        if (nTempValue < 0)
        {
            nTempValue = 0;
        }
        if (nTempValue > 200)
        {
            nTempValue = 200;
        }
        Quest.HintLevelMax = (BYTE)nTempValue;


        questElement->Attribute("MapId",&nTempValue);
        if (nTempValue < -1 )
        {
            nTempValue = -1;
        }
        Quest.MapId = (short)nTempValue;
        questElement->Attribute("RankId",&nTempValue);
        if (nTempValue>SQuest::eQuestRank_Max||nTempValue<SQuest::eQuestRank_Nor)
        {
            nTempValue = SQuest::eQuestRank_Nor;
        }
        Quest.RankId = (short)nTempValue;

        MeXmlElement* pTalks = questElement->FirstChildElement( "Talks" );
        while( pTalks )
        {
            ParseTalks(pTalks, &Quest );
            pTalks = pTalks->NextSiblingElement( "Talks" );
        }		

        ParseRewards(questElement->FirstChildElement( "Rewards" ) , &Quest);

        ParseReceiveRequirementTypes(questElement->FirstChildElement( "ReceiveRequirements" ),&Quest);

        ParseCommitRequirementTypes(questElement->FirstChildElement( "CommitRequirements" ),&Quest);

        AddQuest(&Quest);

#if (!_CLIENT_) && (!_CONVERT_)	// 服务器用
        if ( Quest.chQuestType == SQuest::Type_Pub )
        {
            theQuestManager.AddPubQuest( Quest.Id );
        }
        else if ( Quest.chQuestType == SQuest::Type_Royal )
        {
            theQuestManager.AddPubQuest( Quest.Id );
        }
        else if (Quest.chQuestType == SQuest::Type_ConQuest)
        {
            theQuestManager.AddConQuest(Quest.Id);
        }
#endif

    }

    return true;
}

int QuestInfo::FindDefaultIconByType(unsigned char type)
{
    RewardTypes::iterator itr = rewardTypes_.find((unsigned char)type);
    if (itr != rewardTypes_.end())
    {
        return itr->second.DefauleIconId;
    }

    return 0;
}

bool QuestInfo::SaveBinQuest( const char* pFileName )
{
    if (pFileName == NULL || *pFileName == 0)
    {
        return false;
    }

    if( m_pQuests.size() == 0 )
        return false;

    FILE* fp = fopen( pFileName, "wb" );
    if( !fp )
        return false;

    // 写数据标示和版本号
    char szIdentifier[256] = {0};
    sprintf_s(szIdentifier, sizeof(szIdentifier)-1, "%s", QUEST_DATA_ID);
    int nIdLength = strlen(szIdentifier);
    fwrite( &nIdLength, sizeof(int), 1, fp );
    fwrite( szIdentifier, nIdLength, 1, fp );
    int nVersion = QUEST_DATA_VERSION;
    fwrite( &nVersion, sizeof(int), 1, fp );

    bool bRet = true;
    itrSQuests itQuest = m_pQuests.begin();
    // 数据保存顺序必须与ParseBinQuest里读取顺序一致
    if( itQuest != m_pQuests.end() && itQuest->second )
    {
        SQuest* pQuest = itQuest->second;
        fwrite( &pQuest->Id, sizeof( short ), 1, fp );
        fwrite( &pQuest->QuestName, sizeof( DWORD ), 1, fp );
        fwrite( &pQuest->IntroStringId, sizeof( DWORD ), 1, fp );
        fwrite( &pQuest->IsRepeat, sizeof( bool ), 1, fp );
        fwrite( &pQuest->IsCancel, sizeof( bool ), 1, fp );
        fwrite( &pQuest->HintLevelMin, sizeof( BYTE ), 1, fp );
        fwrite( &pQuest->HintLevelMax, sizeof( BYTE ), 1, fp );
        fwrite( &pQuest->AcceptTargetId, sizeof( DWORD ), 1, fp );
        fwrite( &pQuest->ReplyTargetId, sizeof( DWORD ), 1, fp );
        fwrite( &pQuest->MapId, sizeof( short ), 1, fp );
        fwrite( &pQuest->TargetStringId, sizeof( DWORD ), 1, fp );
        fwrite( &pQuest->CanAssist, sizeof( bool ), 1, fp );
        fwrite( &pQuest->CanShare, sizeof( bool ), 1, fp );
        fwrite( &pQuest->RankId, sizeof( short ), 1, fp );
        fwrite( &pQuest->chQuestType, sizeof( unsigned char ), 1, fp );
        fwrite( &pQuest->CanDisplay, sizeof( bool ), 1, fp );
		fwrite( &pQuest->bDisplayInCanAccept, sizeof( bool ), 1, fp );
        fwrite( &pQuest->IsSingleRequirement, sizeof( bool ), 1, fp );

        // 写talks
        int nTalksCount = pQuest->vQuestTalks.size();
        fwrite( &nTalksCount, sizeof( int ), 1, fp );
        for( SQuest::QuestTalkAllIter it = pQuest->vQuestTalks.begin(); 
            it != pQuest->vQuestTalks.end(); ++ it )
        {
            int nPosition = (*it).first;
            fwrite( &nPosition, sizeof( int ), 1, fp );
            // 写每个talk内容
            QuestTalks& kTalks = (*it).second;
            int nTalkCount = kTalks.size();
            fwrite( &nTalkCount, sizeof( int ) ,1 , fp );
            for( int nTalk = 0 ; nTalk < nTalkCount; ++ nTalk )
            {
                SQuestTalk& kSingleTalk = kTalks[nTalk];
                fwrite( &kSingleTalk.nNpcId, sizeof( int ), 1, fp );
                fwrite( &kSingleTalk.nStringId, sizeof( int ), 1, fp );
				fwrite( &kSingleTalk.nNpcAnim, sizeof( int ), 1, fp );
                // 写每个option内容
                int nOptionCount = kSingleTalk.vOptions.size();
                fwrite( &nOptionCount, sizeof( int ), 1, fp );
                for( int nOption = 0 ; nOption < nOptionCount; ++ nOption )
                {
                    SQuestOption& kOption = kSingleTalk.vOptions[nOption];
                    fwrite( &kOption.nStringId, sizeof( int ) , 1, fp );
                    // 写每个option里面的talk内容
                    int nOptionTalkCount = kOption.vTalks.size();
                    fwrite( &nOptionTalkCount, sizeof( int ) , 1, fp );
                    for( int nOptionTalk = 0 ; nOptionTalk < nOptionTalkCount; ++ nOptionTalk )
                    {
                        SQuestTalk& kOptionTalk = kOption.vTalks[nOptionTalk];
                        fwrite( &kOptionTalk.nNpcId, sizeof( int ) , 1, fp );
                        fwrite( &kOptionTalk.nStringId, sizeof( int ) , 1, fp );
                    }
                }
            }
        }

        int nCount = pQuest->stReward.size();
        fwrite( &nCount, sizeof( int ), 1, fp );
        for(int i=0; i<nCount; ++i)
        {
            fwrite( &pQuest->stReward[i].byType, sizeof( BYTE ), 1, fp );
            fwrite( &pQuest->stReward[i].Number, sizeof( int ), 1, fp );
            fwrite( &pQuest->stReward[i].Value, sizeof( int ), 1, fp );
            fwrite( &pQuest->stReward[i].shSex, sizeof( short ), 1, fp );
            fwrite( &pQuest->stReward[i].shProfession, sizeof( short ), 1, fp );
            fwrite( &pQuest->stReward[i].Icon, sizeof( int ), 1, fp );
        }

        nCount = pQuest->stCommitRequirement.size();
        fwrite( &nCount, sizeof( int ), 1, fp );
        for(int i=0; i<nCount; ++i)
        {
            fwrite( &pQuest->stCommitRequirement[i].byType, sizeof( BYTE ), 1, fp );
            fwrite( &pQuest->stCommitRequirement[i].wVar, sizeof( WORD ), 1, fp );
            fwrite( &pQuest->stCommitRequirement[i].MaxNum, sizeof( WORD ), 1, fp );
            fwrite( &pQuest->stCommitRequirement[i].Value, sizeof( int ), 1, fp );
            fwrite( &pQuest->stCommitRequirement[i].nStringID, sizeof( int ), 1, fp );
        }

        nCount = pQuest->stReceiveRequirement.size();
        fwrite( &nCount, sizeof( int ), 1, fp );
        for(int i=0; i<nCount; ++i)
        {
            fwrite( &pQuest->stReceiveRequirement[i].byType, sizeof( BYTE ), 1, fp );
            fwrite( &pQuest->stReceiveRequirement[i].wVar, sizeof( WORD ), 1, fp );
            fwrite( &pQuest->stReceiveRequirement[i].MaxNum, sizeof( WORD ), 1, fp );
            fwrite( &pQuest->stReceiveRequirement[i].Value, sizeof( int ), 1, fp );
            fwrite( &pQuest->stReceiveRequirement[i].nStringID, sizeof( int ), 1, fp );
        }
    }
    else
        bRet = false;


    if( fp )
        fclose( fp );

    return bRet;
}

// 检查文件大小并读给定大小数据，若检查失败并bCloseFile为true，则关闭文件
static bool ReadAndCheckFileSize(f_Handle* fp, void* pData, int nReadSize, const DWORD dwTotalSize, DWORD& dwCurrentSize, bool bCloseFile)
{
    if( !fp || !pData )
    {
        if( fp && bCloseFile )
            packet_namespace::w_fclose(fp);
        return false;
    }

    if( dwCurrentSize + nReadSize > dwTotalSize )
    {
        if( fp && bCloseFile )
            packet_namespace::w_fclose(fp);
        return false;
    }

    packet_namespace::w_fread( pData, nReadSize, 1, fp );
    dwCurrentSize += nReadSize;
    return true;
}

bool QuestInfo::ParseBinQuest( const char* pFileName )
{
    if (pFileName == NULL || *pFileName == 0)
    {
        return false;
    }

    f_Handle* fp = packet_namespace::w_fopen( pFileName, "rb" );
    if( !fp )
        return false;

    packet_namespace::w_fseek(fp,0,SEEK_END);
    DWORD dwFileSize = packet_namespace::w_ftell(fp);
    packet_namespace::w_rewind(fp);
    DWORD dwSizeCount = 0;

    // 检查数据标识和版本号
    int nIdLength = 0;
    if( !ReadAndCheckFileSize( fp, &nIdLength, sizeof(int), dwFileSize, dwSizeCount, true ) )
        return false;
    if( nIdLength <= 0 )
        return false;

    char szIdentifier[256] = {0};
    if( !ReadAndCheckFileSize( fp, szIdentifier, nIdLength, dwFileSize, dwSizeCount, true ) )
        return false;
    if( 0 != strcmp(szIdentifier, QUEST_DATA_ID) )
        return false;

    int nVersion = 0;
    if( !ReadAndCheckFileSize( fp, &nVersion, sizeof(int), dwFileSize, dwSizeCount, true ) )
        return false;
    if( nVersion < QUEST_DATA_BASE_VERSION )
        return false;

    bool bValue = false;
    short shValue = 0;
    int nValue = 0;
    DWORD dwValue = 0;
    BYTE BValue = 0;
    unsigned char ucValue = 0;

    SQuest xQuest;
    if( !ReadAndCheckFileSize( fp,&shValue, sizeof( short ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.Id = shValue;

    if( !ReadAndCheckFileSize( fp, &dwValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.QuestName = dwValue;

    if( !ReadAndCheckFileSize( fp, &dwValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.IntroStringId = dwValue;

    if( !ReadAndCheckFileSize( fp, &bValue, sizeof( bool ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.IsRepeat = bValue;

    if( !ReadAndCheckFileSize( fp, &bValue, sizeof( bool ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.IsCancel = bValue;

    if( !ReadAndCheckFileSize( fp, &BValue, sizeof( BYTE ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.HintLevelMin = BValue;

    if( !ReadAndCheckFileSize( fp, &BValue, sizeof( BYTE ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.HintLevelMax = BValue;

    if( !ReadAndCheckFileSize( fp, &dwValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.AcceptTargetId = dwValue;

    if( !ReadAndCheckFileSize( fp, &dwValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.ReplyTargetId = dwValue;

    if( !ReadAndCheckFileSize( fp, &shValue, sizeof( short ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.MapId = shValue;

    if( !ReadAndCheckFileSize( fp, &dwValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.TargetStringId = dwValue;

    if( !ReadAndCheckFileSize( fp, &bValue, sizeof( bool ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.CanAssist = bValue;

    if( !ReadAndCheckFileSize( fp, &bValue, sizeof( bool ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.CanShare = bValue;

    if( !ReadAndCheckFileSize( fp, &shValue, sizeof( short ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.RankId = shValue;

    if( !ReadAndCheckFileSize( fp, &ucValue, sizeof( unsigned char ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.chQuestType = ucValue;

    if( !ReadAndCheckFileSize( fp, &bValue, sizeof( bool ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.CanDisplay = bValue;

	if( !ReadAndCheckFileSize( fp, &bValue, sizeof( bool ), dwFileSize, dwSizeCount, true ) )
		return false;
	xQuest.bDisplayInCanAccept = bValue;

    if( !ReadAndCheckFileSize( fp, &bValue, sizeof( bool ), dwFileSize, dwSizeCount, true ) )
        return false;
    xQuest.IsSingleRequirement = bValue;

    // talks
    if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
        return false;

    int nTalksCount = nValue;
    for( int i = 0 ; i < nTalksCount; ++ i )
    {
        int nPosition = 0;
        if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
            return false;
        nPosition = nValue;

        // 读talks
        int nTalkCount = 0;
        if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
            return false;
        nTalkCount = nValue;
        for( int nT = 0; nT < nTalkCount; ++ nT )
        {
            int nNpcId = InvalidLogicNumber;
            int nStringId = InvalidLogicNumber;
			int nNpcAnim  = InvalidLogicNumber;
            SQuestTalk kTalk;

            // read values
            if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
                return false;
            nNpcId = nValue;

            if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
                return false;
            nStringId = nValue;

			if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
				return false;
			nNpcAnim = nValue;

            // assign values
            kTalk.nNpcId = nNpcId;
            kTalk.nStringId = nStringId;
			kTalk.nNpcAnim  = nNpcAnim;

            // find options
            int nOptionCount = 0;
            if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
                return false;
            nOptionCount = nValue;
            for( int nO = 0; nO < nOptionCount; ++ nO )
            {
                int nOptionStringId = InvalidLogicNumber;
                if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
                    return false;;

                nOptionStringId = nValue;

                SQuestOption kOption;
                kOption.nStringId = nOptionStringId;
                // find talk
                int nOptionTalkCount = 0;
                if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
                    return false;
                nOptionTalkCount = nValue;
                for( int nOp = 0; nOp < nOptionTalkCount; ++ nOp )
                {
                    int nOptionTalkNpcId = InvalidLogicNumber;
                    int nOptionTalkStringId = InvalidLogicNumber;

                    // read values
                    if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
                        return false;
                    nOptionTalkNpcId = nValue;

                    if( !ReadAndCheckFileSize( fp, &nValue, sizeof( DWORD ), dwFileSize, dwSizeCount, true ) )
                        return false;
                    nOptionTalkStringId = nValue;

                    SQuestTalk kOptionTalk;
                    kOptionTalk.nNpcId = nOptionTalkNpcId;
                    kOptionTalk.nStringId = nOptionTalkStringId;

                    // add to option's talk list
                    kOption.vTalks.push_back( kOptionTalk );
                }

                // add option to talk
                kTalk.vOptions.push_back( kOption );
            }	


            // add to container
            if( nPosition >= QuestManager::HSTT_ToGain && 
                nPosition < QuestManager::HSTT_Count )
            {
                xQuest.vQuestTalks[nPosition].push_back( kTalk );
            }
        }
    }

    int nCount = 0;
    if( !ReadAndCheckFileSize( fp, &nCount, sizeof( int ), dwFileSize, dwSizeCount, true ) )
        return false;
    if( nCount > 0 )
    {
        for( int i = 0 ; i < nCount ; ++ i )
        {
            SQuestReward xReward;
            if( !ReadAndCheckFileSize( fp, &xReward.byType, sizeof( BYTE ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xReward.Number, sizeof( int ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xReward.Value, sizeof( int ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xReward.shSex, sizeof( short ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xReward.shProfession, sizeof( short ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xReward.Icon, sizeof( int ), dwFileSize, dwSizeCount, true ) )
                return false;
            xQuest.AddReward(&xReward);
        }
    }

    if( !ReadAndCheckFileSize( fp, &nCount, sizeof( int ), dwFileSize, dwSizeCount, true ) )
        return false;
    if( nCount > 0 )
    {
        for( int i = 0 ; i < nCount ; ++ i )
        {
            SQuestRequirement xCommitReq;
            if( !ReadAndCheckFileSize( fp, &xCommitReq.byType, sizeof( BYTE ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xCommitReq.wVar, sizeof( WORD ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xCommitReq.MaxNum, sizeof( WORD ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xCommitReq.Value, sizeof( int ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xCommitReq.nStringID, sizeof( int ), dwFileSize, dwSizeCount, true ) )
                return false;
            xQuest.AddCommitRequirement(&xCommitReq);
        }
    }

    if( !ReadAndCheckFileSize( fp, &nCount, sizeof( int ), dwFileSize, dwSizeCount, true ) )
        return false;
    if( nCount > 0 )
    {
        for( int i = 0 ; i < nCount ; ++ i )
        {
            SQuestRequirement xReceiveReq;
            if( !ReadAndCheckFileSize( fp, &xReceiveReq.byType, sizeof( BYTE ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xReceiveReq.wVar, sizeof( WORD ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xReceiveReq.MaxNum, sizeof( WORD ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xReceiveReq.Value, sizeof( int ), dwFileSize, dwSizeCount, true ) )
                return false;
            if( !ReadAndCheckFileSize( fp, &xReceiveReq.nStringID, sizeof( int ), dwFileSize, dwSizeCount, true ) )
                return false;
            xQuest.AddReceiveRequirement(&xReceiveReq);
        }
    }
    AddQuest(&xQuest);

    if( fp )
        packet_namespace::w_fclose( fp );

    return true;
}

bool QuestInfo::LoadOneQuest( const char* szFilePath, const char* szFileNameNoExt, bool bClear /*= false*/, bool isCipher /*= false*/ )
{
    if (szFilePath == NULL || *szFilePath == 0)
    {
        return false;
    }

    if (szFileNameNoExt == NULL || *szFileNameNoExt == 0)
    {
        return false;
    }

    //检查文件名 
    bool bOk = CheckQuestName(szFileNameNoExt);
    if( !bOk )
        return false;

    if( bClear )
    {
        for (itrSQuests itRelease = m_pQuests.begin();itRelease != m_pQuests.end();)
        {
            CNewWithDebug<SQuest>::Free(itRelease->second);
            itRelease->second = NULL;
            itRelease = m_pQuests.erase(itRelease);
        }
        m_pQuests.clear();
    }

    bool result = true;

    Common::_tstring sourceFilePath = szFilePath;

    char szFile[_MAX_PATH + 1] = {0};
    if (isCipher)
    {
        sprintf_s(szFile, sizeof(szFile) - 1, "%s\\%s%s", sourceFilePath.toNarrowString().c_str(), szFileNameNoExt, Encrypt_Quest_Ext);
    }
    else
    {
        sprintf_s(szFile, sizeof(szFile) - 1, "%s\\%s%s", sourceFilePath.toNarrowString().c_str(), szFileNameNoExt, Quest_Ext);
    }

    if (isCipher)
    {
        int length = strlen(szFile);
        if (length > 1)
        {
            szFile[length - 1] = '\0';
        }
    }
    result = ParseQuest(szFile); //加载

    return result;
}

bool QuestInfo::CheckQuestName( const char* szFileName )
{
    if (szFileName == NULL || *szFileName == 0)
    {
        return false;
    }

    char FileNameNoExt[_MAX_PATH] = {0};
    memset(FileNameNoExt,0,sizeof(FileNameNoExt));
    // 去掉路径
    char *p = strrchr((char*)szFileName, '\\');
    if( p )
    {
        strncpy(FileNameNoExt, p, sizeof(FileNameNoExt)-1);
    }
    else
    {
        strncpy(FileNameNoExt, szFileName, sizeof(FileNameNoExt)-1);
    }

    // 去掉后缀
    p = strchr( FileNameNoExt, '.' );
    if( p )
        *p = 0;

    //检查文件名是否是全数字
    for(int size = 0;size < strlen(FileNameNoExt);++size)
    {
        if ( FileNameNoExt[size] < 0 && FileNameNoExt[size] > 9 )
        {
            return false;
        }
    }

    // 检查文件名是否在有效范围内
    int nFileNum = 0;
    nFileNum = atoi(FileNameNoExt) ;
    if (nFileNum < dr_MinQuestId)
    {
        return false;
    }
    if (nFileNum > dr_MaxQuestId)
    {
        return false;
    }

    return true;
}

bool QuestInfo::LoadOneBinQuest( const char* szFileName )
{
    if (szFileName == NULL || *szFileName == 0)
    {
        return false;
    }

    for (itrSQuests itRelease = m_pQuests.begin();itRelease != m_pQuests.end();)
    {
        CNewWithDebug<SQuest>::Free(itRelease->second);
        itRelease->second = NULL;
        itRelease = m_pQuests.erase(itRelease);
    }
    m_pQuests.clear();

    return ParseBinQuest(szFileName); //加载
}

#ifdef _CONVERT_
bool QuestInfo::SaveOneQuest( const char* szFileName )
{
    if (szFileName == NULL || *szFileName == 0)
    {
        return false;
    }

    if( m_pQuests.size() == 0 )
        return false;

    bool bRet = true;
    itrSQuests itQuest = m_pQuests.begin();
    // 数据保存顺序必须与ParseBinQuest里读取顺序一致
    if( itQuest != m_pQuests.end() && itQuest->second )
    {
        return SaveQuestFile(szFileName, itQuest->second);
    }

    return false;
}

bool QuestInfo::LoadCommondData(const char* szFilePath)
{
    if (szFilePath == NULL || *szFilePath == 0)
    {
        return false;
    }

    //read Commond File
    Common::_tstring FilePath = szFilePath;
    FilePath += "\\Common.quest";
    return ParseCommondData( FilePath.toNarrowString().c_str() );
}
#endif