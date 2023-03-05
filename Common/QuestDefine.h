/********************************************************************
    Filename:    QuestDefine.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_QUESTDEFINE_H__
#define __COMMON_QUESTDEFINE_H__

#pragma once

#include "MeRTLibsServer.h"
#include "GameDefineGlobal.h"

#pragma pack ( push ,1 )

struct SQuestReward
{ // ����ر�
    SQuestReward()
    {
        Value = -1;
        shSex = 2;
        shProfession = -1;
        byType = 0;
        Number = 0;
        Icon   = 0;
        bIsBound = true;
        bIsStarRandom = false;
        nStarLevel = 0;
        RewardID = 0;
    }

    BYTE    byType       ; // ����
    int     Number       ; // ��ֵ
    int     Value        ; // ����ֵId
    short   shSex        ; // �����ĵ�����Ʒ���Ա�
    short   shProfession ; // �����ĵ�����Ʒ��
    int     Icon         ; // �����ĵ��ߵ�ͼ��
    bool    bIsBound     ; // �Ƿ��
    bool    bIsStarRandom; // �Ƿ�����Ǽ�
    short   nStarLevel   ; // ����Ǽ�
    BYTE    RewardID     ; // ����ID

    void ClearReward()
    {
        Value = -1;
        shSex = 2;
        shProfession = -1;
        byType = 0;
        Number = 0;
        Icon = 0;
        RewardID = 0;
    }
};

struct SQuestRequirement
{
    SQuestRequirement()
    {
        ClearRequirement();
    }

    BYTE byType   ; // ����
    WORD wVar     ; // ������ID
    WORD MaxNum   ; // �������������ֵ
    int  Value    ; // �����ǵ���Id,������ֵ
    int  nStringID; // ����������Ӧ���ִ�ID������ѡ����Ҫ����Ϊ��������ʱ�洢
    BYTE nRewardID; // ��Ӧ����ID

    void ClearRequirement()
    {
        byType = 0;
        wVar = 0;
        MaxNum = 0;
        Value = InvalidLogicNumber;
        nStringID = InvalidLogicNumber;
        nRewardID = 0;
        //memset(szItem,0,dr_MaxQuestStateDesc);
    }
};

/*
*@desc Npc�ر�Ի�
*/
struct SQuestTalk;
typedef std::vector<SQuestTalk> QuestTalks;
struct SQuestOption
{
    SQuestOption()
    {
        nStringId = InvalidLogicNumber;
    }
    int nStringId;
    QuestTalks vTalks;
};
typedef std::vector<SQuestOption> QuestOptions;
struct SQuestTalk
{
    SQuestTalk()
    {
        nNpcId = InvalidLogicNumber;
        nStringId = InvalidLogicNumber;
		nNpcAnim = InvalidLogicNumber;
    }
    int nNpcId;
    int nStringId;
	int nNpcAnim;
    QuestOptions vOptions;
};

struct SQuest
{
    enum ERequirementTypes
    {
        eRequirement_Money = 0      , // ��Ǯ
        eRequirement_Item           , // ����
        eRequirement_Var            , // ������Ӧ�ļ�������
        eRequirement_Profession     ,
        eRequirement_Level          ,
        eRequirement_Reputation     ,
        eRequirement_Sex            ,
        eRequirement_Energy         ,
        eRequirement_Monster        ,
        eRequirement_Quest          ,
        eRequirement_Time           , // ʱ������(s)
        eRequirement_SocialRelation , // ����ϵ
        eRequirement_Exp            , // ����ֵ
        eRequirement_SkillExp       , // ���ܾ���
        eRequirement_Action         , // ��Ϊ���񣬱��绤��
        eRequirement_VarLimit       , // ��������( С�ڼ���ֵ ������ȡ���� )
        eRequirement_WeakCountry    , // �������ܽ�
        eRequirement_Status         , // ��Ҫ״̬
        eRequirement_NoStatus       , // û��״̬
        eRequirement_XinFaLevel     , // �ķ��ȼ�
        eRequirement_PetNumber      , // ��������
        eRequirement_PetLevel       , // ����ȼ�
        eRequirement_PetID          , // ����ID
        eRequirement_PetType        , // ��������
        eRequirement_PetActive      , // �����ս
        eRequirement_Max            ,
    };

    enum ERewardType
    {
        eReward_Money = 0      , // ��Ǯ
        eReward_Exp            , // ����ֵ
        eReward_SkillExp       , // ���ܾ���
        eReward_Item           , // ����
        eReward_Reputation     ,
        eReward_Exploit        , // ��ѫ
        eReward_Title          ,
        eReward_Buff           ,
        eReward_ChangeRoleVar  ,
        eReward_GuildContribute, // �����ﹱ
        eReward_SpecialItem    , // �ر���Ʒ
        eReward_JiaoZi         , // ����
        eReward_Honor          , // ��������
		eReward_CountryMoney   , // �����ʽ�
		eReward_ScriptExp	  ,  // �������� �ű�����
        eReward_Max,
    };

    enum QuestRank
    {
        eQuestRank_Nor   , // ��ͨ
        eQuestRank_Nic   , // ���õ�
        eQuestRank_Exc   , // ����
        eQuestRank_Gold  , // ׿Խ
        eQuestRank_Legend, // ��˵
        //eQuestRank_Epic  , // ʷʫ
        eQuestRank_Max   ,
    };

    enum QuestType
    {
        Type_Main = 0      , // ��������
        Type_Lateral       , // ֧������
        Type_Campaign      , // �����
        Type_Ectype        , // ��������
        Type_Official      , // �ٸ�����
        Type_Circle        , // ѭ������
        Type_Cruise        , // Ѳ������
        Type_Battalion     , // ��������
        Type_Precious      , // �ر�����
        Type_Title         , // �ƺ����� 
        Type_Gut           , // ��������
        Type_Gout          , // Ȥζ����
        Type_Guild         , // ��������
        Type_Pub           , // �ƹ�����
        Type_Royal         , // �ʰ�����
        Type_ConQuest      , // ��������
        Type_CountryKing   , // ��������
        Type_CountryGeneral, // ��������
        Type_CountryLeft   , // ��������
        Type_CountryRight  , // ̽������
        Type_Adventure     , // ��������
        Type_Achieve       , // �ɾ�����
        Type_End           ,
    };

    typedef std::vector<SQuestReward>       RewardType;
    typedef RewardType::iterator            RewardTypeItr;
    typedef RewardType::iterator			RewardTypeItr;
    typedef std::vector<SQuestRequirement>	RequirementType;
    typedef RequirementType::iterator		RequirementTypeItr;
    typedef map<int, QuestTalks>			QuestTalksAll;
    typedef map<int, QuestTalks>::iterator  QuestTalkAllIter;
    typedef RequirementType::iterator       RequirementTypeItr;

    short           Id                  ; // ����Id
    DWORD           QuestName           ; // ��������
    DWORD           IntroStringId       ; // ����˵��
    RewardType      stReward            ; // ����
    RequirementType stCommitRequirement ; // ������ɵ�����
    RequirementType stReceiveRequirement; // �������������
    bool            IsRepeat            ; // �Ƿ��ظ�����
    bool            IsCancel            ; // �����Ƿ�ɱ�ɾ��,��Ҫ�������ܱ�ɾ��,�������ʱ��Ҳ�����Ӽ���������
    BYTE            HintLevelMin        ; // ��ʾ��������
    BYTE            HintLevelMax        ; // ��ʾ��������
    DWORD           AcceptTargetId      ; // ������Ŀ��
    DWORD           ReplyTargetId       ; // �������NPC����
    short           MapId               ; // ����ĵ�ͼId
    DWORD           TargetStringId      ; // ����Ŀ��
    bool            CanAssist           ; // �ɷ�Э��
    bool            CanShare            ; // �ɷ���
    short           RankId              ; // ����Ʒ��
    unsigned char   chQuestType         ; // ��������
    bool            CanDisplay          ; // �ͻ����Ƿ����ʾ
	bool			bDisplayInCanAccept	; // �Ƿ��ڿɽ���������ʾ
    bool            IsSingleRequirement ; // ���һ�����������������

	//����һ���������������ֶΣ�0��ʾ�����˶��ܽ�
	BYTE			Country				; //����ID

    QuestTalksAll   vQuestTalks;          // ��������Ի�
	

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
        AcceptTargetId = InvalidLogicNumber;
        ReplyTargetId = InvalidLogicNumber;
        RankId = -1;
        chQuestType = Type_Main;
        CanDisplay = true;
        IsSingleRequirement = false;
		Country = 0;
		bDisplayInCanAccept = true;
    }

    const char* GetQuestName();
    const char* GetQuestStateInfo();
    const char* GetRewardNpcName();
    const char* GetAcceptNpcName();
    const char* GetQuestInfo();

    SQuest& operator =(const SQuest& squest)
    {
        if (this == &squest)
        { return *this; }

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
		bDisplayInCanAccept = squest.bDisplayInCanAccept;
        IsSingleRequirement = squest.IsSingleRequirement;
		Country = squest.Country;
        vQuestTalks = squest.vQuestTalks;
        return *this;
    }

    bool HaveQuestTalk( short stPosition )
    {
        return ( vQuestTalks.find( stPosition ) != vQuestTalks.end() );
    }

    int GetPlayerReceiveQuestLevel()
    {
        for ( RequirementTypeItr itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Level)//eRequirement_Level
            { return itrPlayerLevel->Value; }
        }
        return 1;
    }

    int GetPlayerReceiveQuestSex()
    {
        for ( RequirementTypeItr itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Sex)//eRequirement_Level
            { return itrPlayerLevel->Value; }
        }
        return 2;
    }

    int GetPlayerReceiveQuestProfession()
    {
        for ( RequirementTypeItr itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Profession)//eRequirement_Profession
            { return itrPlayerLevel->Value; }
        }
        return 0xff;
    }

    int GetPlayerReceiveQuestReputation()
    {
        for ( RequirementTypeItr itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Reputation)//eRequirement_Reputation
            { return itrPlayerLevel->Value; }
        }
        return 1;
    }

    short AddReceiveRequirement( const SQuestRequirement* pRequirement )
    {
        stReceiveRequirement.push_back(*pRequirement);
        return (short)stReceiveRequirement.size();
    }

    int RemoveReceiveRequirement( const SQuestRequirement* pRequirement )
    {
        if( stReceiveRequirement.empty() )
        { return -1; }

        int i = 0;
        for( RequirementTypeItr it = stReceiveRequirement.begin();it != stReceiveRequirement.end();++it)
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

    SQuestRequirement* GetReceiveRequirement( int Typeid,int* pBeginPos = NULL)
    {
        int nBeginPos = 0;
        if ( pBeginPos )
        { nBeginPos = *pBeginPos; }

        if( stReceiveRequirement.empty() || nBeginPos >= (int)stReceiveRequirement.size())
        { return NULL; }

        int retPos = nBeginPos + 1;

        for( RequirementTypeItr workitr = stReceiveRequirement.begin() + nBeginPos; workitr != stReceiveRequirement.end() ; ++workitr,++retPos)
        {
            if (workitr->byType == Typeid)
            {
                if (pBeginPos)
                { *pBeginPos = retPos; }
                return &(*workitr);
            }            
        }
        return NULL;
    }

    void ClearCommitRequirement()
    { stCommitRequirement.clear(); }

    void ClearReceiveRequirement()
    { stReceiveRequirement.clear(); }

    void ClearReward()
    { stReward.clear(); }

    short AddCommitRequirement( const SQuestRequirement* pRequirement )
    {
        stCommitRequirement.push_back(*pRequirement);        
        return (short)stCommitRequirement.size();
    }

    int RemoveCommitRequirement( const SQuestRequirement* pRequirement )
    {
        if( stCommitRequirement.empty() )
        { return -1; }

        int i = 0;
        for( RequirementTypeItr it = stCommitRequirement.begin();it != stCommitRequirement.end();++it)
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
        { return NULL; }

        for( RequirementTypeItr workitr = stCommitRequirement.begin() ; workitr != stCommitRequirement.end() ; ++workitr)
        {
            if (workitr->byType == Typeid)
            { return &(*workitr); }
        }
        return NULL;
    }

    int AddReward( const SQuestReward* pReward )
    {
        stReward.push_back(*pReward);
        return (int)stReward.size();
    }

    int RemoveReward( const SQuestReward* pReward )
    {
        int i = 0;
        for ( RewardTypeItr it = stReward.begin(); it != stReward.end();++it)
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
        { return NULL; }

        for( RewardTypeItr workitr = stReward.begin() ; workitr != stReward.end() ; ++workitr)
        {
            if (workitr->byType == Typeid)
            { return &(*workitr); }
        }
        return NULL;
    }

    bool IsPubQuest()       { return ( chQuestType == Type_Pub || chQuestType == Type_Royal ); }
    bool IsConQuest()       { return chQuestType == Type_ConQuest;                             }    
};

#pragma pack ( pop )

#endif // __COMMON_QUESTDEFINE_H__
