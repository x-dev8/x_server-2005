/********************************************************************
    Filename:    QuestData.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/
#ifndef __COMMON_QUESTCONFIG_H__
#define __COMMON_QUESTCONFIG_H__

#pragma once

#include "GlobalDef.h"
#include "RapidXml/MeRapidXml.h"
#include "QuestDefine.h"

#define QUEST_DATA_ID				"M.E.Q.D"	// �����ļ����������ݸ�ʽ��ʶ
#define QUEST_DATA_VERSION			10000		// �����ļ����������ݰ汾����ʼ�汾��10000��ÿ�ε����汾�ŵ���1
#define QUEST_DATA_BASE_VERSION		10000		// �����ļ���ʼ�汾��

#define Quest_Ext ".quest"
#define Encrypt_Quest_Ext ".questc"
#define Bin_Quest_Ext ".questb"

class QuestInfo
{
public:
    typedef std::map< unsigned char, std::string> RequirementTypes;
    struct SRewardType
    {
        std::string Value;
        int DefauleIconId;
    };
    typedef std::map< unsigned char, SRewardType> RewardTypes;
    typedef std::map<int,SQuest*> SQuests;
    typedef SQuests::iterator itrSQuests;

    const static short DeleteQuest = -1;
    const static short NoHaveRewardType = -1;
    const static short NoHaveRequirementType = -1;
    const static short AlreadyHaveRequirementType = -2;
    const static short AlreadyHaveRewardType = -2;
    
private:
    static const int _nMaxStringLength = 128;

public:
    static char RequirementString[SQuest::eRequirement_Max][_nMaxStringLength];
    static char RewardString[SQuest::eReward_Max][_nMaxStringLength];
    static char RankString[SQuest::eQuestRank_Max][_nMaxStringLength];
    SQuests m_pQuests;
public:
    // �����������ݽṹ
    struct SQuestType
    {
        int Id;                     //��������ID
        std::string QuestTypeDesc;  //������������
        std::string QuestTypeIcon;  //��������Icon
    };
    //std::vector<SQuestType*> QuestTypeVec;
    //QuestTypeVec::iterator   QuestTypeVecIter;
    std::vector<SQuestType*> _QuestType;            //�������Ͷ���
    SQuestType* GetQuestTypeByID(int nID)
    {
        if (nID < 0 || _QuestType.size() < nID)
        { return NULL;}

        return _QuestType[nID];
    }
public:
    QuestInfo();
    ~QuestInfo();

    static QuestInfo& Instance();

    const char* GetRewardType(int id);
    bool        AddQuest( const SQuest* pQuest );    
    /*SQuest*   GetQuest( int nQuestId );*/
    bool        LoadQuest(const char* pFilePath = QUESTS_FILEPATH,bool isCipher = false);

	bool		LoadOneQuest(const char* szFilePath, const char* szFileNameNoExt, bool bClear = false, bool isCipher = false);	// szFileNameNoExt: �ļ�����������׺
	// m_pQuests���һ��Quest����������ļ���m_pQuests��ֻ����һ��quest
	// ���SQuest��ʽ�������ú���ҲҪ����������ͻ��˶����ܸ�ʽ��ʧ��
	bool		SaveBinQuest(const char* szFileName);
	// ֻ����һ���������ļ�������ǰ����������飬��MeQuestConvert���ߵ���
	bool		LoadOneBinQuest(const char* szFileName);
#ifdef _CONVERT_
	// m_pQuests���һ��Quest������ı��ļ���m_pQuests��ֻ����һ��quest
	bool		SaveOneQuest(const char* szFileName);
	bool		LoadCommondData(const char* szFileName);
#endif

#ifdef __QUEST_EDIT__
    bool            CoalitionQuest(QuestInfo &Quests);
    bool            CoalitionQuest(QuestInfo::SQuests &Quests);
    bool            SaveQuest(const char* pFilePath = QUESTS_FILEPATH);
    bool            RemoveQuest(int QuestId);
    bool            ModifyRequirementString(int id,char* pstring);
    bool            ModifyRewardString(int id,char* pstring);
    bool            ModifyQuestRankString(int id,char* pstring);
    const char*     GetRequirementType(int id);
    bool            SaveQuestFile(const char* QuestFileName,SQuest *Quest);
    bool            SaveCommonFile(const char* CommonFileName);
    
#endif // __QUEST_EDIT__

public:
    bool        ParseCommondData(const char* FileName); //LoadCommonData
private:
    //��ѯxml�е�id��
    int         FindCommitRequirementType( const char* pszString );
    int         FindReceiveRequirementType( const char* pszString );
    int         FindRewardTypes( const char* pszString );
    int         FindDefaultIconByType(unsigned char type);
    int         AddRewardType(int id,const char * RewardType,const int Icon = 0);
    int         AddRewardType(const char * RewardType,const int Icon = 0);
    bool        ParseCommitRequirementTypes( MeXmlElement* requirementsElement, SQuestReward* Quest );
    bool        ParseReceiveRequirementTypes(MeXmlElement* requirementsElement,SQuest* quest);
    bool        ParseCommitRequirementTypes(MeXmlElement* requirementsElement,SQuest* quest);
    bool        ParseRewards(MeXmlElement* rewardsElement , SQuest* Quest);
	bool		ParseTalks(MeXmlElement* talksElement, SQuest* Quest);
    bool        ParseQuest(const char* FileName);
	// ���������Ƹ�ʽ
	bool		ParseBinQuest(const char* pFileName);
	bool		CheckQuestName(const char* szQuest);	// ��������ļ����Ƿ�ϸ�


    RewardTypes rewardTypes_;
    RequirementTypes CommitRequirementTypes_;
    RequirementTypes ReceiveRequirementTypes_;

    SQuest*     CreateQuest( int nQuestId );

    int         StrToRequirementType( const char* pszString );
    int         StrToRewardType( const char* pszString );

protected:
};

#define theQuestInfo QuestInfo::Instance()

#endif // __COMMON_QUESTCONFIG_H__
