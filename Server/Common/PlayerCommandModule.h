#ifndef __PLAYERCOMMANDHANDLE_H__
#define __PLAYERCOMMANDHANDLE_H__

public:
	// for GM ��Ա����
	unsigned int              m_nGMLevel;				// GM�ȼ� 0Ϊ��Ȩ��
	bool                      m_bCanChat;				// �Ƿ��������
	bool                      m_bEnmityDebugOpen;		// �����ʾ����
	bool                      m_bDamageEnmityDebugOpen; // �˺���ʾ����
	bool					  m_bTellCostTime;			// �Ƿ����Updateʱ��
	DWORD					  m_dwTellCostTime;			// ���õ��ٽ�ֵ
	char					  m_szCmdHead[32];			// û������ͷ �ڱ�д��ʱ��ע�ⳤ����31

protected:
    bool ProcessGMCommand( const MsgChat* pMsgChat );	// ����������Ϣ Ȼ��switch
	void OnGMCommand	 ( const MsgChat* pMsgChat, unsigned int nGMLevel );
    void OnBotCommand	 ( const char* szCommand );
    
    void ProcessFlyToMap          		( const char* szCommand );
	void ProcessSelectChannel     		( const char* szCommand );
    void ProcessKickPlayer        		( const char* szCommand );
    void ProcessBanSpeak          		( const char* szCommand );
    void ProcessBroadcast         		( const char* szCommand, const MsgChat* pMsgChat = NULL );
	//zhuxincong ��������ĳ�����ҷ�������
	void ProcessTelltheCountry	  		( const char* szCommand, const MsgChat* pMsgChat = NULL );
    void ProcessPrompt            		( const char* szCommand, const MsgChat* pMsgChat = NULL );
    void ProcessFindCharByAccount 		( const char* szCommand );
    void ProcessFindCharByName    		( const char* szCommand );
    void ProcessSetCharacter      		( const char* szCommand );
    void ProcessGetCharacterList  		( const char* szCommand );
    void ProcessTargetSay         		( const char* szCommand );
    void ProcessCallPlayer        		( const char* szCommand );
    void ProcessFlyToPlayer       		( const char* szCommand );
    void ProcessDestroyItem       		( const char* szCommand );
    void ProcessCreateItem        		( const char* szCommand );
    void ProcessApplyStatus       		( const char* szCommand );
    void ProcessCreateMonster     		( const char* szCommand );
    void ProcessCreateMonsterEx   		( const char* szCommand );
    void ProcessCallSummonMonster 		( const char* szCommand );
    void ProcessCreateItemPackage 		( const char* szCommand );
    void ProcessLearnSkill        		( const char* szCommand );
    void ProcessSetQuestState     		( const char* szCommand );
    void ProcessDoneQuest         		( const char* szCommand );
    void ProcessAddMount          		( const char* szCommand );
    void ProcessAddPet            		( const char* szCommand );
    void ProcessAddPetExp         		( const char* szCommand );
    void ProcessEquipLevel        		( const char* szCommand );
    void ProcessExpChange         		( const char* szCommand );
    void ProcessRoll              		( const char* szCommand, short stType, const char* szToName );
    void ProcessShowPos           		( const char* szCommand );
    void ProcessPlayEffect        		( const char* szCommand );
    void ProcessChangeLuckLevel   		( const char* szCommand );
    void ProcessResetLuckReward   		( const char* szCommand );
    void ProcessStartLuckReward   		( const char* szCommand );
    void ProcessRunLuckReward     		( const char* szCommand );
    void ProcessReceiveLuckReward 		( const char* szCommand );
    void ProcessChangeLuckType    		( const char* szCommand );
    void ProcessChangeGMLevel     		( const char* szCommand ); // һ������Ķ���
    void ProcessInteresting       		( const char* szCommand ); // һ������Ķ���
    void ProcessPlayerLevel       		( const char* szCommand );
    void ProcessCallGraphic       		( const char* szCommand );
    void ProcessGuildVar          		( const char* szCommand );
    void ProcessGetTargetDBID     		( const char* szCommand );
    void ProcessChangeCheckCheat  		( const char* szCommond );
    void ProcessCheckCheat        		( const char* szCommand );   
	void ProcessShowLastSaveTime		( const char* szCommand );   
	void ProcessShowEnmity				( const char* szCommand );  
	void ProcessSetCostTime				( const char* szCommand );
	void ProcessShowDamageEnmity		( const char* szCommand );
	void ProcessShowServerPos			( const char* szCommand );
    void ProcessGetProcessList    		( const char* szCommand );  // �ѻ���ҿ��ܲ�����Ӧ������Ϣ, �ľͻ�Ҫ��һ����Ϣ, ���ʹ�����ͻ���ִ��
    void ProcessBan               		( const char* szCommand );
	void ProcessBanAccouynt       		( const char* szCommand );
    void ProcessSetAreaCurrentReputation( const char* szCommand );
    void ProcessSetAreaMaxReputation    ( const char* szCommand );
    void ProcessCheckupElement          ( const char* szCommand );
    void ProcessSubEquipHp              ( const char* szCommand );
    void ProcessSuitLevelUp             ( const char* szCommand );
    void ProcessUnLockItem              ( const char* szCommand );
    void ProcessAddFriendly             ( const char* szCommand );
    void ProcessQuerySecondPassword     ( const char* szCommand );
    void ProcessSetNpcShow              ( const char* szCommand );
    void ProcessSetCountryOfficial      ( const char* szCommand );
    void ProcessAddCountryMoney         ( const char* szCommand );
    void ProcessShowProperty            ( const char* szCommand );
    void ProcessCreateGuild             ( const char* szCommand );
    void ProcessKillTarget              ( const char* szCommand );
    void ProcessRemoveTarget            ( const char* szCommand );
    void ProcessShowPlayerEnmity        ( const char* szCommand );
    void ProcessKillGridTarget          ( const char* szCommand );
    void ProcessTestTellCountry         ( const char* szCommand );
    void ProcessTestSetAreaVar          ( const char* szCommand );
    void ProcessTestCountryQuestOpen    ( const char* szCommand );
    void ProcessChangeSignature         ( const char* szCommand );
    void ProcessClearChangeCountryName  ( const char* szCommand );
    void ProcessMonsterInfo             ( const char* szCommand );
    void ProcessShowServVersion         ( const char* szCommand );
    void ProcessSignUpCampBattle        ( const char* szCommand );
    void ProcessEnterCampBattle         ( const char* szCommand );
    void ProcessKillCampBattleMonster   ( const char* szCommand );
    void ProcessChangeCampBattleStatus  ( const char* szCommand );
    void ProcessCountryWarStatus        ( const char* szCommand );
    void ProcessTestTimeVar             ( const char* SzCommand );
    void ProcessAddXinFa                ( const char* SzCommand );
	void ProcessFamilyProsperity		( const char* szCommand );
	void ProcessCreateEquipRand			( const char* szCommand );
	/*
	 *	Author 2012-9-11 zhuxincong
	 *	DESC: �����ı����
	 */
	void ProcessAddCC					( const char* szCommand );
	void ProcessJoinCountryWar			( const char* szCommand );
	void ProcessSetCountryWar			( const char* szCommand );
	void ProcessSetGuildWar				( const char* szCommand );
	void ProcessJoinGuildWar			( const char* szCommand );
	void ProcessTestLogService			( const char* szCommand );
	void ChangePetMode					( const char* szCommand );
	void ChangePet						( const char* szCommand );
	void ChangeQuestStates				( const char* szCommand );
	void OpenGuildGeneralBattle			( const char* szCommand );
	void EnterGuildGeneralBattle		( const char* szCommand );
	void EndGuildGeneralBattle			( const char* szCommand );
	void OpenGuildGeneralBattleSum		( const char* szCommand );

	void ProcessSetGuildKing			( const char* szCommand );
	void ProcessChangePlayerSecondPwd	( const char* szCommand );
	void ProcessOndeath					( const char* szCommand );
	void ProcessGreatCatch				( const char* szCommand );
	void ProcessMapmonsterinfo			( const char* szCommand );
	void ProcessRelivemapmonster		( const char* szCommand );


	//void CreateItemForBot( int nItemID, int iCount, int nType );	//Ϊ�����˴���װ��luo.qin 3.24

#endif