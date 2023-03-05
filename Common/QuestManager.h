/********************************************************************
    Filename:    QuestManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_QUESTMANAGER_H__
#define __COMMON_QUESTMANAGER_H__

#pragma once

#include "GlobalDef.h"
#include "QuestDefine.h"

class QuestManager
{
public:

    // QuestValue 16λ ��Ϊ 1 1 6 8
    // 0 0 000000 00000000
    // | | |    | |      |
    // | | |____| |______|
    // A B    X      C
    // A.��һ��ʾ�������û������ǰ�Ի�
    // B.�ڶ���ʾ�������û������ǰ�Ի�
    // C.��ʾ����״̬
    // X.Ԥ��

    enum EConstDefine
    {
        ECD_A = 0x8000, // A��ȡֵ
        ECD_B = 0x4000, // B��ȡֵ
        ECD_C = 0x00ff, // C��ȡֵ
        ECD_X = 0x3f00, // X��ȡֵ
    };

    enum EHaveSawTalkType
    {
        HSTT_ToGain, // ȥ������
        HSTT_ToDone, // ȥ������
		HSTT_Count
    };

    enum EQuestState
    {
        eQuestCantGain = 0x03, // �޷���ȡ 3         
        eQuestNotGain  = 0x00, // δ�� 0
        eQuestGaining  = 0x01, // �������� 1
        eQuestDone     = 0x02, // ��� 2
		eQuestFrozen   = 0x04, // ������ʱ����
		eQuestEntrustDone = 0x08,
    };

    enum ESpecialQuestGainState
    {
        ESQGS_CannotGain = 0, // ���ɽ�ȡ
        ESQGS_CanGain    = 1, // �ɽ�ȡ
    };

    typedef std::map< int, int >      PubQuestRankMap   ; // <����Ʒ��,�����>
    typedef PubQuestRankMap::iterator ItrPubQuestRankMap;
    typedef std::vector< int >        PubQuestId        ; // <����Id�б�>
    typedef PubQuestId::iterator      ItrPubQuestId     ;

public:
    ~QuestManager();

    static QuestManager& Instance();
    
    // �Ƿ�����Ч��QuestId
    bool IsQuestIdValid( int nQuestId );
    
    // ��������״̬ ���� ����Var�е�ԭʼֵ
    short SetQuestState( short questValue, uint8 questState );

    // ȡ������״ֵ̬ ����Ĳ��� questValueΪ��Var������ȡ��ԭʼֵ
    uint8 GetQuestState( short questValue );
    
    // ��ǰ״̬�Ƿ������״̬
    bool IsQuestDone  ( uint8 questState );

    // ��ǰ״̬�Ƿ���δ��״̬
    bool IsQuestNotGain( uint8 questState );

    // ��ǰ״̬�Ƿ� ���ѽ�ȡ ��������(������)
    bool IsQuestActive( uint8 questState );

    // �Ƿ񿴹��Ի� ����Ĳ������¼����� EHaveSawTalkType. questValueΪ��Var������ȡ��ԭʼֵ
    bool IsHaveSaw( uint8 type, short questValue );

    // ���������Ƿ��Ѿ������Ի�
    short SetHaveSaw( uint8 type, short questValue );

    SQuest*     GetQuest( int nQuestId );                               // ��ȡָ������Id������
    void        AddPubQuest  ( int nQuestID ) { _PubQuestID.push_back( nQuestID ); _AllPubQuestID.push_back( nQuestID ); }
    void        AddRoyalQuest( int nQuestID ) { _RoyalQuestID.push_back( nQuestID ); _AllPubQuestID.push_back( nQuestID ); }
    void        AddConQuest  ( int nQuestID ) { _ConQuestID.push_back( nQuestID );}
    PubQuestId& GetAllPubQuest() { return _AllPubQuestID; } // ��ȡ�ƹݺͻʰ�����
    PubQuestId& GetPubQuest()    { return _PubQuestID   ; } // ��ȡ�ƹ�����
    PubQuestId& GetRoyalQuest()  { return _RoyalQuestID ; } // ��ȡ�ʰ�����
    PubQuestId& GetConQuest()    { return _ConQuestID   ; } // ��ȡ��������
    SQuest*     GetQuestByTheQuests( std::list<int>& QuestIds ); // ͨ�������б�,�������������
    bool        LoadQuestRandConfigFile(const char* Path);       // ��ȡƷ������ļ�
    void        ParseAllSpecializationQuestByQuest();            // ���������б�������ʰ�����;ƹ�����
    bool        SaveQuestRandConfigFile(const char* Path);

protected:
    QuestManager();
    bool    CheckQuestRand( PubQuestRankMap &_PubQuestRankMap );

protected:
    PubQuestRankMap _QuestRankMap  ; // ����Ʒ�ʸ�������
    int             _QuestTotalRand; // ��������ܵ�Ʒ�ʸ�������

    PubQuestId      _PubQuestID   ;
    PubQuestId      _RoyalQuestID ;
    PubQuestId      _AllPubQuestID;
    PubQuestId      _ConQuestID   ;
};

#define theQuestManager QuestManager::Instance()

#endif // __COMMON_QUESTMANAGER_H__