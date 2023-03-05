/********************************************************************
    Filename:     ScriptAbstract.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SCRIPTABSTRACT_H_
#define __COMMON_SCRIPTABSTRACT_H_

#include "Globaldef.h"

struct FlyMapParam 
{
    FlyMapParam()
    {
        fDir         = 0.0f;
        chFlyType    = 0;
        bCheckHeader = false;
        m_nQuestID   = -1;
    }

    int           nMapId      ;
    int           x           ;
    int           y           ; 
    float         fDir        ; 
    unsigned char chFlyType   ;
    bool          bCheckHeader;
    int           m_nQuestID  ;
};

class IScriptInterface
{
public:
    virtual const char* GetStringFormVar( int nVarId ) = 0;

    virtual BOOL HasVarTable() = 0; 
    virtual void HighLightSourceLine( int nLine ) = 0;
    virtual void MarkSourceLine( int nLine ) = 0;
    virtual void SetVar( int nVarId, int nOp, void* pParams, int nParamCount = 1 ) = 0;
    virtual void SetTeamVar( int nVarId, int nOp, void* pParams, int nParamCount = 1 ) = 0;
    virtual void SetAreaVar( int nVarId, int nValue, int nRadius, int nType ) = 0; //设置区域计数变量
    virtual bool IsTeamVarAllLess( int nVarId, int nValue ) = 0;            // 是否队伍中成员的nVarId小于nValue
    virtual bool IsTeamVarAllGreater( int nVarID, int nValue ) = 0;
    virtual int  GetVar( int nVarId, GameObjectId nPlayerId = -1 ) = 0;

    virtual void SetCurCharId( GameObjectId nCharId ) = 0;
    virtual GameObjectId  GetCurCharId() = 0;
    virtual void SetDstId( GameObjectId nId ) = 0;
    virtual GameObjectId  GetDstId() = 0;
    virtual void RecordIds() = 0;
    virtual void ResumeIds() = 0;

    virtual void Dlg( const char* pszText , int iButtonFLag ,int iValue) = 0;
    virtual void NpcMainDlg( const char* pszText , int iButtonFLag ,int iValue) = 0;

    virtual void Tell( const char *pszText ) = 0;
    virtual void Talk( int type, const char *pszText ) = 0;
    virtual void TalkToAll( int type, const char *pszText ) = 0;
    virtual void TalkToTeam( int type, const char *pszText ) = 0;
	virtual void TalkToMap( int map_id, int type, const char *pszText ) = 0;
    virtual void TalkToArea( int nMapId, int nX, int nY, int type, const char *pszText ) = 0;
	virtual void TalkToCountry( int country_id, int type, const char *pszText ) = 0;
    virtual void Broadcast( int nType, const char *pszText ) = 0;
    virtual bool FlyToMap( FlyMapParam& xFlyMapParam ) = 0;
    virtual bool CallAllTeamPlayerFlyToMap( int nMapId, int x, int y, float fDir = 0.0f) = 0;
    virtual bool InitShop( int nShopId, int nRefreshRate, int nType, bool bIsBound, SShopItem pItems[], int nCount) = 0;
    virtual void Shop( int nShopId, GameObjectId nDstPlayerId, int nNpcId = -1 ) = 0;
    virtual void DoCommand( const char* command ) = 0;    
    virtual void Ask( short stVarId, const char* pszText ) = 0;    
    virtual void Show( short stImageId, int x, int y, DWORD dwLife, DWORD dwFlag, DWORD dwFlagTime ) = 0;
    virtual void RemoveAllEquip( ) = 0;    
    virtual void SetBornPoint( DWORD dwMapID, int iPosX, int iPosY ) = 0;    
    virtual int  HaveThisItem( char *pItemName ) = 0;
    virtual void RemoveThisItem ( char *pItemName, int iNumber  ) = 0;
    virtual bool IsThisItemEquipped ( char *pItemName  ) = 0;
    virtual bool IsThisSkillActived ( unsigned short ustSkillItemID,unsigned short ustSkillLevel ) = 0;  
	virtual void ProcTimeStep(int StringID,int TimeStep) = 0;

	virtual int	GetWeekKillNum() =0;
	virtual int	GetAllKillNum()=0;
	virtual int	GetSeriesKillNum()=0;

    virtual int  GetMapIdByName( const char* pszMapName ) = 0;
    virtual void TeashSkill( std::vector<int>&vectorSkill ) = 0;
    virtual void AddSkill( int nSkillId, int level,bool bMessageDialog = true ) = 0;
    virtual int  GetSkillLevel( int nSkillId ) = 0;
    virtual void AddItem( const char* pszItemName, int nItemCount ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 ) = 0;
    virtual void AddItemByItemid( const unsigned short ustItemid, int nItemCount, bool bIsBound = true ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 ) = 0;
    virtual void AddEquipByItemId( const unsigned short ustItemid, bool bStarRandom, int16 nStarLevel, bool bIsBound = true ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 ) = 0;
    virtual void AddItemInWorld( unsigned short ustItemid, int nItemCount  ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 ) = 0;
	virtual void AddEquipRandAttrItem( unsigned short ustItemid, bool bIsBound = true ,int nRandId1 = 0, int nRandId2 = 0, int nRandId3 = 0, int nRandId4 = 0, int nRandId5 = 0, int nRandId6 = 0, int nRandId7 = 0, int sysType = 0, int typeID = -1 ) = 0;

    virtual void AddRecipe ( unsigned short ustRecipeID ) = 0;
    virtual bool HaveRecipe( unsigned short ustRecipeID ) = 0;

    virtual void AddXinFa       ( int nXinFaId, int level, bool bCheck = true , bool bMessageDialog = true ) = 0;
    virtual void GMAddXinFa     ( int nXinFaId, int level ) = 0;
    virtual int  GetXinFaLevel  ( int nXinFaId ) = 0;
    virtual int  GetXinFaMaxLevel() = 0;

    // 任务相关
    //virtual void Quest_CastQuest( int nQuestID ) = 0;
    //virtual void Quest_GetQuest( int nQuestID ) = 0;
    virtual void Quest_CancelQuest( int nQuestID ) = 0;
    virtual bool Quest_DoneQuest( int nQuestID ) = 0;
    virtual bool Quest_SetQuestState( int nQuestID, int nState ) = 0;
    virtual void Quest_GetQuestState( int nQuestID, int nVarID ) = 0;
    virtual void Quest_RelateQuest( int nQuestID, int nState, int nEnter ) = 0;
    virtual bool Quest_CanGetNewQuest( int nVarID ) = 0;
    virtual void DropItem(int ItemId,int ItemNum,bool nobelong = true ) = 0;

    //称号
    virtual void AddTitle(unsigned short nstTitleID) = 0;
    virtual void RemoveTitle(unsigned short nstTitleID) = 0;
    virtual int  HaveThisTitle(unsigned short nstTitleID) = 0;

    //人物相关
    virtual void AddLevel(int level) = 0;
    virtual bool IsInArea(int Lx,int Ly,int Rx,int Ry) = 0;
    virtual int  SelfPosX() = 0;
    virtual int  SelfPosY() = 0;
    virtual void Printf( const char* string, ... ) = 0;
    virtual void DBGPrint( const char* string ) = 0;
    virtual void GetPlayerCountVar( int nQuestID, int nVarID ) = 0;
    virtual void RefreshMonster( int nMapId, int x, int y, const char* szArea ) = 0;
    virtual void PlayerMusic( const char *szFileName, short stParameter ) = 0;
    virtual void MakeItem(BYTE byCreatNewOrOld,/* int nMakeType,*/ int nRate,/* BYTE byEquipType, BYTE byItemType,
                            float fX1,float fX2,float fX3,float fX4,
                            float fY, float fA,float fX,*/int nIdBegin[], int nIdEnd[], int nCount/*,
                            float fw */) = 0;
    virtual void  ShowQuestDlg( int nVarid, const char* szInfo ) = 0;
    virtual void  ShowPubQuestDlg( int nVarid, int nType, const char* szInfo ) = 0;
    virtual void  UseSkill( int nSkillId, int nSkillLevel ) = 0;
    virtual void  AddStatusByScript( int nStatusID, int nStatusLevel ) = 0;
    virtual void  PopNpcList() = 0;
    virtual void  ShowBank() = 0;
    virtual BOOL  SetStorage() = 0;
    virtual BOOL  SetMountStorage() = 0;
    virtual int   GetWorldTime( const char *pszTimeType, bool bRealTime ) = 0;
    virtual int   GetBirthday( int nTimeType ) = 0;
    virtual void  NpcMoveNext() = 0;
    virtual void  NpcStopMove() = 0;
    virtual void  NpcStartMove() = 0;
    virtual void  NpcPlayAnim( const char* szName, int nTimes, const char* szEndName, bool bForView, int nNpcId ) = 0;
    virtual BOOL  IsNpcPlayAnim( int nNpcId, const char* szName ) = 0;

    virtual void  ScenePlay ( int nSceneID, bool bView ) = 0;
    virtual void  NpcScenePlay( int nNpcID, int nSceneID, bool bView ) = 0;

    virtual void  BlackScreen ( int nTime, bool bView ) = 0;

	virtual bool  IsCanPet(void) = 0;
	virtual	bool  DoPet(int nIndex) = 0;

    virtual BOOL  CanLearnSkill( int nSkillId, int nSkillLevel ) = 0;
    virtual bool  IsCanRide( void ) = 0;
    virtual void  DoRide( int nId ) = 0;
    virtual void  DoRideFristMount( ) = 0;
    virtual void  AddSkillToFristMount( uint16 skillId, uint8 level ) = 0;
    virtual void  DoHitch( int nID, bool bBack ) = 0;
	virtual void  DoHitchByTeam(int nID,int TeamnID,bool bBack) = 0;
    virtual short GetRideId() = 0;
	virtual uint16 GetRideLevel() = 0;
    virtual void  SetDialogName( const char* szName ) = 0;
    virtual void  SetHotkey( int nIndex, int nID ) = 0;
    virtual BOOL  LogInfoToDB( const char* szInfo ) = 0;

    virtual int   GetTeamPlayerCount() = 0;
    virtual int   GetTeamID() = 0;
    virtual int   GetTeamPlayerLevel( int nType ) = 0;
    virtual int   GetTeamAverageLevel() = 0;
    virtual int   GetTeamPlayerID( unsigned  int nIndex ) = 0;
    virtual bool  IsTeamHeader() = 0;
    virtual int   AddTeamFriendly(int nValue) = 0;

    virtual void  SetDstPlayer( int nId ) = 0;
    virtual void  CreateMonster( int nMapId, float fPosX, float fPosY, float fRadius, float fBodySize, int nMonsterIndex, int nMonsterNum ) = 0;
    virtual void  CreateSpecialMonster( int nMapId, float fPosX, float fPosY, float fRadius, float fBodySize, int nMonsterIndex, int nMonsterNum ) = 0;

    virtual void  CreateMonsterEx( int nMapId, float fPosX, float fPosY, float fRadius, int nMonsterIndex, int nFightCamp, int nForce, int nRouteID, int nCountry = 0 ) = 0;
    virtual void  CreateSpecialMonsterEx( int nMapId, float fPosX, float fPosY, float fRadius, int nMonsterIndex, int nFightCamp, int nForce, int nRouteID ) = 0;

    virtual void  CreateRouteMonster( int nMapId, float fPosX, float fPosY, float fRadius, int nMonsterIndex, int nRouteID ) = 0;
    virtual int   GetNullItemCount( unsigned short usItemBagItem ) = 0;
    virtual void  Sleep( DWORD dwTime ) = 0;
    virtual void  CallScript( const char* szFileName, int nEnterId, GameObjectId nPlayerId, bool bDbId ) = 0;
    virtual void  CloseDlg() = 0;
    virtual int   GetMapId() = 0;
    virtual bool  IsInZone( const char* pszName ) = 0;
    virtual void  PlayEffect( const char* pszName, float fX, float fY, float fZ, bool bIsCast ) = 0;
    virtual void  ShowIntonateBar( DWORD dwTime, int nStringID, int nActionID, int nType, int nID ) = 0;
    virtual void  AddPkValue(int nValue,bool dailypkvale) = 0;
    virtual void  DecPkValue(int nValue) = 0;
    virtual void  SetPkValue(int nValue) = 0;
    virtual int   GetPkValue() = 0;
    virtual int   GetPkState() = 0;
    virtual int   GetPkMode()  = 0;
    virtual bool  SetPkMode(int nMode)   = 0;
    //virtual void OpenStoryBook( int nValue ) = 0;//sbw_add
    //virtual void OpenTgaIconDlg( int nValue) = 0;
    virtual void  OpenClientUI(int UIFlag, int openType = 0, int64 openParam = 0 ) = 0;
    virtual void  NotarizationSuccess( int nMember1,int nMember2,int nValue) = 0;
    virtual int   GetBagSize( int bagType ) = 0;
    virtual void  AddBagSize( int bagType, int nSize ) = 0;
    virtual void  NoticeNotarizationResult(GameObjectId iPlayer1,const char *pszAnd,GameObjectId iPlayer2,const char *pszText,int nMapId, int nX, int nY,DWORD time, DWORD color) = 0;
    virtual bool  IsEverybodyAllReady(GameObjectId iPlayerId,int nValue) = 0;
    virtual bool  IsEverybodyAllHere() = 0;    
    virtual BOOL  IsMapActive( int nMapId ) = 0;
    virtual int   GetMapCount( DWORD dwId ) = 0;

    virtual void  GetOfflineHookExp(uint8 nHookLevel)  = 0;
    virtual bool  IsOfflinePassOneWeek() = 0;

    virtual bool  AddSysDoubleExpTime ( int nValue ) = 0;
    virtual bool  AddItemDoubleExpTime( int nValue ) = 0;

    // 创建保护对象
    virtual void CreateProtectChar( int monsterId, int varId, bool isCanRide ) = 0; // 保护对象Id, 计数变量
    virtual void LostProtectChar() = 0;

    // 获得保护对象的怪物索引
    virtual int GetProtectCharMonsterIndex() = 0;
    virtual int  GetRankLevel(int index) = 0;

    //////////////////////////////////////////////////////////////////////////
    virtual bool IsHaveStatus( short shStatusID ) = 0;
    virtual void AddPlayerIntegralMax( int nSize ) = 0;
    virtual int  HaveThisItem_Byid( unsigned short ustItemid ) = 0;
    virtual void RemoveThisItem_Byid ( unsigned short ustItemid, int iNumber  ) = 0;
    virtual bool IsThisItemEquipped_Byid ( unsigned short ustItemid ) = 0;
    virtual int  GetStorageItemGrid () = 0;
    virtual int  GetStorageMountGrid() = 0; 
    virtual bool AddStorageItemGrid(unsigned char nValue) = 0; // 开启仓库格数
    virtual bool AddStorageMountGrid(unsigned char nValue) = 0; 
    virtual void UpdatePkValueMaxDaily(int offset) = 0;//每天PK最大值计算
    virtual void SetStatusByScript( int nStatusID, int nStatusLevel ) = 0;
    virtual void InsertDelayScript(int delaytime,int scriptindex,bool forplayer = false ) = 0;
    virtual void ScriptLog(const char* pszKeyWord,const char* pszContent) = 0;
    virtual void RemoveDelayScript(int scriptindex,bool forplayer = false) = 0;
    virtual void ShowTimeTop(DWORD showtime) = 0;
    virtual void ShutDownTimeTop() = 0;

    virtual void BeckonPlayer( GameObjectId nPlayerId ) = 0;
    virtual void CallScriptTeam( const char* szFileName, int nEnterId ) = 0;

    virtual int  AddMount( unsigned short usMountId ) = 0;
    virtual bool HasMount( unsigned short usMountId ) = 0;
    virtual int  RestoreMountEnjoyment( ) = 0;                   // 恢复坐骑生命值全满
	virtual bool IsMountFull() = 0;

    virtual bool IsPetFull() = 0;
    virtual int  GetPetNumber() = 0;
    virtual int  AddPet( int monsterId, int quality, int sex ) = 0;
    virtual bool HaveBreedPet() = 0;
    virtual void PetBreedAcquire() = 0;
    virtual bool AddPetIdentify ( uint16 petType ) = 0;
    virtual int  GetPetMaxLevel() = 0;
    virtual int  GetActivePetIndex() = 0;

    virtual int  GetDaoxing( ) = 0;
    virtual void AddDaoxing( int nValue ) = 0;

    virtual bool CreateScriptNpc(int NpcId,int MapId,int PosX,int PoxY, unsigned int unOnTime) = 0;
    //virtual bool DeleteScriptNpc(int beginNpcId,int endNpcId) = 0;

    virtual bool RecordTime( int nVarId ) = 0;                                                 // 纪录当前时间
    virtual bool IsExpired( int nVarId, int keyHour, int keyMinute, int minDuration ) = 0;     // 是否到过了keyTime这个时间点minDuration这个时间长度
    virtual bool RecordTeamTime( int nVarId ) = 0;                                             // 纪录队伍中所有成员当前时间
    virtual bool IsTeamExpired( int nVarId, int keyHour, int keyMinute, int minDuration ) = 0; // 是否到过了keyTime这个时间点minDuration这个时间长度
    virtual void ClearTeamExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId ) = 0;  // 清除队伍中所有超过这个时间点的变量值
    virtual void RecordExploitTime () = 0;

    // 新加的时间脚本接口
    virtual void RecordTimeVar( int nVarID ) = 0;
    virtual bool IsTimeVarPassOneDay( int nVarID ) = 0;
    virtual void RecordTeamTimeVar( int nVarID ) = 0;
    virtual bool IsTeamTimeVarPassOneDay( int nVarID ) = 0;
    virtual void ClearTeamTimeVar( int nVarID, int nClearVarID ) = 0;

    // 创建一个副本
    virtual bool ScriptCreateStage( const DWORD dwMapID, int nCount, bool bUsePlayerLevel, unsigned short ustMapLevel ) = 0;
    // 判断一个队伍副本是否存在
    virtual bool IsStageExist( const unsigned short dwMapID ) = 0;
    virtual bool IsStageWaitRelease( unsigned int nMapID ) = 0;
    // 离开一个场景
    virtual bool LeaveStage( unsigned short ustMapID, float fX, float fY, bool bTeamLeave, unsigned short ustTime ) = 0;

    // 幸运15关相关
    virtual int GetLuckRewardLevel() = 0;
    virtual void EnterLuckReward() = 0;
    virtual void UpdateLuckReward( int nType ) = 0;
    virtual bool IsCanLuckReward() = 0;
    virtual bool IsCanNextLuckLevel() = 0;
    virtual bool IsCanAcceptQuest( unsigned char uchLevel ) = 0;
    virtual bool IsCanReceiveReward() = 0;
    virtual void SetCanLuckReward() = 0;
    virtual void SetLuckSummonCount( unsigned short ustCount ) = 0;
    virtual unsigned short GetLuckSummonCount() = 0;

     // 兑换金锭
    virtual bool OperateJinDing( bool bOperate, int nValue ) = 0;
    virtual bool OperateJinPiao( bool bOperate, int nValue ) = 0;


	virtual void AddGuildBuffByMapID(int MapID,int BuffID,int Level) = 0;
    // 
    virtual bool OperateHonour ( bool bOperate, int nValue ) = 0;

    // 宝箱
    virtual void ShowTreasureBox() = 0;

    // 领取平台物品
    virtual void DrawFromPlatform( uint16 itemType ) = 0;

    // 区域声望
    virtual void SetAreaCurrentReputation( int nMapID, int nValue ) = 0;
    virtual void AddAreaCurrentReputation( int nMapID, int nValue ) = 0;
    virtual void SubAreaCurrentReputation( int nMapID, int nValue ) = 0;
    virtual int GetAreaCurrentReputation( int nMapID ) = 0;

    virtual void SetAreaMaxReputation( int nMapID, int nValue ) = 0;
    virtual void AddAreaMaxReputation( int nMapID, int nValue ) = 0;
    virtual void SubAreaMaxReputation( int nMapID, int nValue ) = 0;
    virtual int GetAreaMaxReputation( int nMapID ) = 0;

    virtual bool SetNextStage( int nNextStage ) = 0;            // 设置定时刷怪的下一个阶段

    // 战场相关 
    virtual bool InitBattle( int nMapID, int nType, int nLevel, unsigned char uchTurns, int nSignTime, int nFightTime, int nMaxUnitCount ) = 0;
    virtual bool ShowBattleSignUpDlg( int nType, const char* szInfo ) = 0;

    virtual void SetChallengeScore( int nValue, int nOp ) = 0;
    virtual int  GetChallengeScore() = 0;

    virtual void CallMailList() = 0;
    
    //检测二次密码
    virtual bool checkSecondPassword(int checkop) = 0;

    virtual bool FlyToPlayer( int nType ) = 0;

    // 小队混战战场相关
    virtual void AddTeamBattleIntegral( int nIntegral ) = 0;

    virtual void SetNpcShow( GameObjectId ustNpcID, unsigned int nSpaceTime ) = 0;
    virtual void SetNpcHide( GameObjectId ustNpcID, unsigned int nSpaceTime ) = 0;
    
    virtual void AddSkillPoint( int nType, int nValue ) = 0;
    virtual void SubSkillPoint( int nType, int nValue ) = 0;
    virtual void SetSkillPoint( int nType, int nValue ) = 0;
    virtual unsigned short GetSkillPoint( int nType ) = 0;

    //成就
    virtual void TriggerAchieveByType( uint16 nValueType, int32 nValue, bool bAddValue ) = 0;
    virtual void TriggerAchieveByID  ( uint16 nId ) = 0;
    virtual void TriggerDeathAchieveByType( uint16 nValueType ) = 0;
    
    virtual int  OnNpcShip() = 0;
    // 获得Id
    virtual int GetTargetId() = 0;

    // 播放视频
    virtual void PlayMovie( unsigned int nMovieId, DWORD dwPlayTime ) = 0;

    // 获得怪物的状态
    virtual int GetMonsterTypeStatus() = 0;

    // 改变怪物的状态
    virtual void ChangeMonsterTypeStatus( int nStatus = 0 ) = 0;

    // 开始某一事件
    virtual void StartEventByID( uint16 nEventID, bool bBroadcast = false ) = 0;

	//获得太平幻境等级
	virtual char  GetTPHJRank() = 0;
	virtual void  SetTPHJRank(char value,int operType=0) = 0;

	//收回副将
	virtual void SetPetUnactive() = 0;
	//角色播放动作
	virtual void PlayAnim(const char* chanim,int times,const char* endanim) = 0;

	virtual void AskPlatformActivity(int _type) = 0;

	virtual bool IsOnBiaoChe() = 0;

	virtual void ClearStatusByid(int status_id) = 0;

	virtual void ChangeTimeHandleStates(unsigned int Index,int Value) = 0;
	virtual void ResetTimeHandleStates(unsigned int Index) = 0;
	virtual void ClearTimeHandle(unsigned int Index) = 0;
	virtual void SetWorldBattleCountry(int CountryID) = 0;
	virtual void ChangeGamePlayerDuration(int Count) = 0;

	virtual void ChangePetMode(int ModeID,int Sec) = 0;
	virtual void UseItem(unsigned short ustItemId) = 0;
	virtual void AddCard(short stCardID, short stLevel) = 0;
	virtual void TriggerSevenDays() = 0;

	virtual unsigned short GetPlayerStates() =0;

	virtual int GetGamePlayerDuration() = 0;
	virtual int AddFriendPoint(int distance , int FriendlyPoint) = 0;

	virtual int IsInFight() = 0;

	virtual void SetScriptStates(unsigned short StatesID) = 0;

	virtual bool CanFlyToCouple() = 0;

	virtual void DropQuestEntrust() = 0;

	virtual void DoneQuestEntrust() = 0;

	//狩猎任务相关
	virtual int GetTodayHuntingCount() = 0; //获得今天已经做了几次狩猎任务
	virtual void OperateHuntingCount( int nType, int nValue ) = 0; //设置狩猎任务次数，0表示加，1表示减，4表示设置
	virtual void DoneHuntingQuest( int nQuestId ) = 0; //完成nQuestId任务并添加一个随机狩猎任务

	virtual void CanelQuestEntrust(int nQuestID) = 0;

	virtual int FlytoPosition(int Type) = 0;

	virtual void AddHonourByTeam(int Num)=0;
	virtual int GetStrongCountry() = 0;
	virtual int GetWeakCountry() = 0;

	virtual void ChangePlayerPoint(int Op,int Value,int States) = 0;

	virtual void SetMonsterArray(int Index,int Value)= 0;
	virtual int	 GetMonsterArray(int Index)= 0;

#include "CountryScriptAbstract.h"
#include "RelationScriptAbstract.h"
#include "GuildScriptAbstract.h"
#include "CampBattleScriptAbstract.h"
#include "FamilyScriptAbstract.h"
#include "GameBattleScriptAbstract.h"

};

#endif

