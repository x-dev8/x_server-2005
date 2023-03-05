/********************************************************************
    Filename:    PlayerQuestModule.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

public:
    void    GetQuestCharVars      ( MsgTellCharVar* pMsg   );
    void    GetQuestTimes         ( MsgTellQuestTime* pMsg );

    uint8   GetQuestState         ( short stQuestId );
    bool    SetQuestState         ( short stQuestId, uint8 chState );
    bool    IsQuestActive         ( short stQuestId );
    bool    IsQuestDone           ( short stQuestId );
    bool    CanGetNewQuest        ();
    char    GetPlayerCountVarState( short nCountVarIdx             );
    bool    Script_CanGetNewQuest ( short stVarId                  );
    void    Script_CancelQuest    ( short stQuestId                );
    bool    Script_DoneQuest      ( short stQuestId                );
    bool    Script_CheckDoneQuest ( short stQuestId                );
    void    Script_GetQuestState  ( short stQuestId, short stVarId );

    bool    DoneSingleRequirementQuest( short stQuestId, int nRewardID );
    
    void    DoneQuestRewardExp    ( SQuest* pQuest, int nRewardModulus = 1);
    __int64 GetQuestTime          ( uint16 questId               );
    bool    SetQuestTime          ( uint16 questId, __int64 time );

	bool    IfCanJoinQuest			(unsigned int QuestID);
    