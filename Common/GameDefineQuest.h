/********************************************************************
    Filename:    GameDefineQuest.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_GAMEDEFINEQUEST_H__
#define __COMMON_GAMEDEFINEQUEST_H__

#pragma once

#pragma pack(push,1)

#include "MeRTLibs.h"
#include "XmlStringLanguage.h"
#include "NpcInfo.h"
#include "GameDefineSystem.h"

struct SQuestReward
{ // ����ر�
    SQuestReward()
    {
        Value        = -1;
        shSex        = 0;
        shProfession = -1;
        byType       = 0;
        Number       = 0;
        Icon         = 0;
    }

    uint8 byType;       // ����
    int32 Number;       // ��ֵ
    int32 Value;        // ����ֵId
    int16 shSex;        // �����ĵ�����Ʒ���Ա�
    int16 shProfession; // �����ĵ�����Ʒ��
    int32 Icon;         // �����ĵ��ߵ�ͼ��  

    void ClearReward()
    {
        Value        = -1;
        shSex        = 0;
        shProfession = -1;
        byType       = 0;
        Number       = 0;
        Icon         = 0;
    }
};

struct SQuestRequirement
{ // ��������
    SQuestRequirement()
    {
        byType = 0;
        wVar = ErrorUnsignedShortID;
        MaxNum = 0;
        Value = ErrorUnsignedShortID;
    }
    uint8  byType; // ����
    uint16 wVar;   // ������ID
    uint16 MaxNum; // �������������ֵ
    int32  Value;  // �����ǵ���Id,������ֵ

    void ClearRequirement()
    {
        byType = 0;
        wVar = 0;
        MaxNum = 0;
        Value = ErrorUnsignedLongID;
        //memset(szItem,0,dr_MaxQuestStateDesc);
    }
};

struct SQuest
{
    enum ERequirementTypes
    {
        eRequirement_Money = 0, // ��Ǯ
        eRequirement_Item     , // ����
        eRequirement_Var      , // ������Ӧ�ļ�������
        eRequirement_Profession,
        eRequirement_Level,
        eRequirement_Reputation,
        eRequirement_Sex,
        eRequirement_Energy,
        eRequirement_Monster,
        eRequirement_Quest,
        eRequirement_Time,
        eRequirement_SocialRelation,//����ϵ
        eRequirement_Exp      , // ����ֵ
        eRequirement_SkillExp , // ���ܾ���
        eRequirement_Action,    // ��Ϊ���񣬱��绤��
        eRequirement_VarLimit,  // ��������( С�ڼ���ֵ ������ȡ���� )
        eRequirement_Max,
    };


    enum ERewardType
    {
        eReward_Money = 0, // ��Ǯ
        eReward_Exp, // ����ֵ
        eReward_SkillExp , // ���ܾ���
        eReward_Item, // ����
        eReward_Reputation,
        eReward_Exploit,        //��ѫ
        eReward_Title,
        eReward_Buff,
        eReward_ChangeRoleVar,
        eReward_GuildContribute,        // �����ﹱ
        eReward_SpecialItem,            // �ر���Ʒ
        eReward_JiaoZi,                 // ���� 
        eReward_Max,
    };

    enum QuestRank
    {
        eQuestRank_Nor,  //��ͨ
        eQuestRank_Nic,  //���õ�
        eQuestRank_Exc,  //����
        eQuestRank_Gold, //׿Խ
        eQuestRank_Legend,//��˵
        //eQuestRank_Epic,//ʷʫ
        eQuestRank_Max,
    };

    enum QuestType
    {
        Type_Main = 0,      // ��������
        Type_Lateral,       // ֧������
        Type_Campaign,      // �����
        Type_Ectype,        // ��������
        Type_Official,      // �ٸ�����
        Type_Circle,        // ѭ������
        Type_Cruise,        // Ѳ������
        Type_Battalion,     // ��������
        Type_Precious,      // �ر�����
        Type_Title,         // �ƺ����� 
        Type_Gut,           // ��������
        Type_Gout,          // Ȥζ����
        Type_Guild,         // ��������
        Type_Pub,           // �ƹ�����
        Type_Royal,         // �ʰ�����
        Type_ConQuest,      // ��������

        Type_End,
    };

    typedef std::vector<SQuestReward>      RewardType;
    typedef std::vector<SQuestRequirement> RequirementType;

    int16           Id;                   // ����Id
    uint32          QuestName;            // ��������
    uint32          IntroStringId;        // ����˵��
    RewardType      stReward;             // ����
    RequirementType stCommitRequirement;  // ������ɵ�����
    RequirementType stReceiveRequirement; // �������������
    bool            IsRepeat;             // �Ƿ��ظ�����
    bool            IsCancel;             // �����Ƿ�ɱ�ɾ��,��Ҫ�������ܱ�ɾ��,�������ʱ��Ҳ�����Ӽ���������
    uint8           HintLevelMin;         // ��ʾ��������
    uint8           HintLevelMax;         // ��ʾ��������
    uint32          AcceptTargetId;       // ������Ŀ��
    uint32          ReplyTargetId;        // �������NPC����
    int16           MapId;                // ����ĵ�ͼId
    uint32          TargetStringId;       // ����Ŀ��
    bool            CanAssist;            // �ɷ�Э��
    bool            CanShare;             // �ɷ���
    int16           RankId;               // ����Ʒ��
    uint8           chQuestType;          // ��������
    bool            CanDisplay;           // �ͻ����Ƿ����ʾ

    SQuest()
    {
        QuestName = 0;
        IntroStringId = 0;
        Id = 0;
        IsRepeat = false;
        IsCancel = true;
        HintLevelMin = 0;
        HintLevelMax = 100;
        MapId = -1;
        CanAssist = true;
        CanShare = true;
        TargetStringId = 0;
        AcceptTargetId = ErrorUnsignedLongID;
        ReplyTargetId = ErrorUnsignedLongID;
        RankId = -1;
        chQuestType = Type_Main;
        CanDisplay = true;
    }

    const char* GetQuestName();
    const char* GetQuestStateInfo();
    const char* GetRewardNpcName();
    const char* GetAcceptNpcName();
    const char* GetQuestInfo();

    SQuest& operator =(const SQuest& squest)
    {
        if (this == &squest)
        {
            return *this;
        }
        Id = squest.Id;
        IsRepeat = squest.IsRepeat;
        IsCancel = squest.IsCancel;
        HintLevelMin = squest.HintLevelMin;
        HintLevelMax = squest.HintLevelMax;
        MapId = squest.MapId;
        CanAssist = squest.CanAssist;
        CanShare = squest.CanShare;
        TargetStringId = squest.TargetStringId;
        QuestName = squest.QuestName;
        IntroStringId = squest.IntroStringId;
        AcceptTargetId = squest.AcceptTargetId;
        ReplyTargetId = squest.ReplyTargetId;
        RankId = squest.RankId;
        chQuestType = squest.chQuestType;

        stReward = squest.stReward;
        stCommitRequirement = squest.stCommitRequirement;
        stReceiveRequirement = squest.stReceiveRequirement;
        CanDisplay = squest.CanDisplay;
        return *this;
    }

    int GetPlayerReceiveQuestLevel()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Level)//eRequirement_Level
            {
                return itrPlayerLevel->Value;
            }
        }
        return 1;
    }
    int GetPlayerReceiveQuestSex()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Sex)//eRequirement_Level
            {
                return itrPlayerLevel->Value;
            }
        }
        return 2;
    }
    int GetPlayerReceiveQuestProfession()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Profession)//eRequirement_Profession
            {
                return itrPlayerLevel->Value;
            }
        }
        return 0xff;
    }
    int GetPlayerReceiveQuestReputation()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Reputation)//eRequirement_Reputation
            {
                return itrPlayerLevel->Value;
            }
        }
        return 1;
    }
    int16 AddReceiveRequirement( const SQuestRequirement* pRequirement )
    {
        stReceiveRequirement.push_back(*pRequirement);

        return (int16)stReceiveRequirement.size();
    }

    int RemoveReceiveRequirement( const SQuestRequirement* pRequirement )
    {
        if( stReceiveRequirement.empty() )
            return -1;
        int i = 0;
        for( std::vector<SQuestRequirement>::iterator it = stReceiveRequirement.begin();it != stReceiveRequirement.end();++it)
        {
            if(it->byType == pRequirement->byType)
            {
                stReceiveRequirement.erase(it);
                return i;
            }
            ++i;
        }

        return -1;
    }

    SQuestRequirement* GetReceiveRequirement(int Typeid,int* pBeginPos = NULL)
    {
        int nBeginPos = 0;
        if (pBeginPos)
        {
            nBeginPos = *pBeginPos;
        }

        if( stReceiveRequirement.empty() || nBeginPos >= (int)stReceiveRequirement.size())
        { return NULL; }
        int retPos = nBeginPos + 1;
        for(std::vector<SQuestRequirement>::iterator workitr = stReceiveRequirement.begin() + nBeginPos; workitr != stReceiveRequirement.end() ; ++workitr,++retPos)
        {
            if (workitr->byType == Typeid)
            {
                if (pBeginPos)
                {
                    *pBeginPos = retPos;
                }
                return &(*workitr);
            }            
        }
        return NULL;
    }
    void ClearCommitRequirement()
    {
        stCommitRequirement.clear();
    }
    void ClearReceiveRequirement()
    {
        stReceiveRequirement.clear();
    }
    void ClearReward()
    {
        stReward.clear();
    }
    int16 AddCommitRequirement( const SQuestRequirement* pRequirement )
    {
        stCommitRequirement.push_back(*pRequirement);

        return (int16)stCommitRequirement.size();
    }

    int RemoveCommitRequirement( const SQuestRequirement* pRequirement )
    {
        if( stCommitRequirement.empty() )
            return -1;
        int i = 0;
        for( std::vector<SQuestRequirement>::iterator it = stCommitRequirement.begin();it != stCommitRequirement.end();++it)
        {
            if(it->byType == pRequirement->byType)
            {
                stCommitRequirement.erase(it);
                return i;
            }
            ++i;
        }

        return -1;
    }
    SQuestRequirement* GetCommitRequirementt(int Typeid)
    {
        if( stCommitRequirement.empty() )
            return NULL;
        for(std::vector<SQuestRequirement>::iterator workitr = stCommitRequirement.begin() ; workitr != stCommitRequirement.end() ; ++workitr)
        {
            if (workitr->byType == Typeid)
            {
                return &(*workitr);
            }
        }
        return NULL;
    }

    int AddReward( const SQuestReward* pReward )
    {
        // 		for (std::vector<SQuestReward>::iterator iter = stReward.begin(); iter != stReward.end(); ++iter)
        // 		{
        // 			if ((*iter).byType > pReward->byType)
        // 			{
        // 				stReward.insert(iter,*pReward);
        // 				return stReward.size();
        // 			}
        // 		} ���򣬸���С�ֽ���ȥ��
        stReward.push_back(*pReward);
        return (int)stReward.size();
    }

    int RemoveReward( const SQuestReward* pReward )
    {
        int i = 0;
        for (std::vector<SQuestReward>::iterator it = stReward.begin(); it != stReward.end();++it)
        {
            if (it->byType == pReward->byType)
            {
                stReward.erase(it);
                return i;
            }
            ++i;
        }

        return -1;
    }
    SQuestReward* GetReward(int Typeid)
    {
        if( stReward.empty() )
            return NULL;
        for(std::vector<SQuestReward>::iterator workitr = stReward.begin() ; workitr != stReward.end() ; ++workitr)
        {
            if (workitr->byType == Typeid)
            {
                return &(*workitr);
            }
        }
        return NULL;
    }

    bool IsPubQuest() { return ( chQuestType == Type_Pub || chQuestType == Type_Royal ); }
    bool IsConQuest() { return chQuestType == Type_ConQuest; }
};

//////////////////////////////////////////////////////////////////////////
// inline
inline const char* SQuest::GetQuestName()
{ return theXmlString.GetString(QuestName); }

inline const char* SQuest::GetRewardNpcName()
{
    NpcInfo::Npc* NpcName = theNpcInfo.GetNpcByStaticId(ReplyTargetId);
    if (NpcName == NULL)
    { return NULL; }
    return NpcName->name.c_str();
}

inline const char* SQuest::GetAcceptNpcName()
{
    NpcInfo::Npc* NpcName = theNpcInfo.GetNpcByStaticId(AcceptTargetId);
    if (NpcName == NULL)
    { return NULL; }
    return NpcName->name.c_str();
}

inline const char*  SQuest::GetQuestStateInfo()
{ return theXmlString.GetString(TargetStringId); }

inline const char* SQuest::GetQuestInfo()
{ return theXmlString.GetString(IntroStringId);}

#pragma pack(pop) 

#endif // __COMMON_GAMEDEFINEQUEST_H__
