/********************************************************************
    Filename:     ServerVarInterface.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_SERVERVARINTERFACE_H__
#define __GAMESERVER_SERVERVARINTERFACE_H__

/*    服务器系统变量接口
1.什么是服务器系统变量接口
    服务器系统变量中保存了当前系统中一些重要的信息，如变量，对象和文档，
    服务器系统变量接口提供了这些内容的访问接口，
    外部程序可以通过这些接口对系统变量进行存储，修改，操纵，查询，
2.为什么需要服务器系统变量接口
    为了和服务器脚本配合，系统需要将内部的信息公开给脚本对象，
3.服务器系统变量使用方法
    对服务器系统变量的控制，使用下面的方法，
    void SetVar( int nVarId, int nValue );
    int  GetVar( int nVarId );
    服务器系统变量包括一个线性的变量数组和一些属性
    变量数组通过id访问，
    当SerVar和GetVar的参数nVarId>=0时，
    认为访问的是变量数组
    反之，认为访问的是属性
    属性分为当前触发脚本的char的属性(金钱，等级，职业等等)
    和系统内部属性(未定义)
*/

#include "BaseCharacter.h"
#include "ScriptAbstract.h"

class CServerVarInterface : public IScriptInterface
{
public:
    CServerVarInterface();

    BOOL    HasVarTable(){ return TRUE; }
    void    HighLightSourceLine( int nLine ){}
    void    MarkSourceLine( int nLine ){}
    void    SetVar( int nVarId, int nOp, void* pParams, int nParamCount = 1 );
    void    SetTeamVar( int nVarId, int nOp, void* pParams, int nParamCount = 1 );
    void    SetAreaVar( int nVarId, int nValue, int nRadius, int nType );   //设置区域计数变量
    bool    IsTeamVarAllLess( int nVarId, int nValue );  // 是否队伍中成员的nVarId小于nValue
    bool    IsTeamVarAllGreater( int nVarID, int nValue ); 
    int     GetVar( int nVarId, GameObjectId nPlayerId = -1 );
    const char* GetStringFormVar( int nVarId );

    void    SetCurCharId( GameObjectId nCharId ){ m_nCurCharId = nCharId; }
    GameObjectId     GetCurCharId()             { return m_nCurCharId; }
    void    SetDstId( GameObjectId nId )        { m_nDstId = nId; }
    GameObjectId     GetDstId()                 { return m_nDstId; }

    void    RecordIds() { m_recordCurCharId = m_nCurCharId; m_recordDstId = m_nDstId; }
    void    ResumeIds() { m_nCurCharId = m_recordCurCharId; m_nDstId = m_recordDstId; m_recordCurCharId = -1; m_recordDstId = -1; }

    void    Dlg( const char* pszText , int iButtonFLag , int iValue);
    void    NpcMainDlg( const char* pszText , int iButtonFLag , int iValue);
    void    Tell( const char *pszText );  //私聊
    void    Talk( /*DWORD time,*/ int type, const char *pszText );
    void    TalkToAll( /*DWORD time,*/ int type, const char *pszText );
    void    TalkToTeam( /*DWORD time,*/ int type, const char *pszText );
	void    TalkToMap( int map_id, int type, const char *pszText );
	void    TalkToCountry( int country_id, int type, const char *pszText );
    void    TalkToArea( int nMapId, int nX, int nY,/*DWORD time,*/ int type, const char *pszText );
    void    Broadcast( int nType, const char *pszText );       //广播
    void    AddMonster( void*  pMonster, int iPosX, int iPosY );
    bool    FlyToMap( FlyMapParam& xFlyMapParam );
    bool    CallAllTeamPlayerFlyToMap( int nMapId, int x, int y, float fDir = 0.0f);
    bool    InitShop(int nShopId, int nRefreshRate, int nType, bool bIsBound, SShopItem pItems[], int nCount);
    void    Shop( int nShopId, GameObjectId nDstPlayerId, int nNpcId = -1 );
    void    DoCommand( const char* command );
    void    Ask( short stVarId, const char* pszText );
    void    Show( short stImageId, int x, int y, DWORD dwLife, DWORD dwFlag, DWORD dwFlagTime );
    void    Printf( const char* string, ... );
    void    DBGPrint( const char* string );
    void    RemoveAllEquip( );
    void    SetBornPoint( DWORD dwMapID, int iPosX, int iPosY );
    int     HaveThisItem( char *pItemName );
    void    RemoveThisItem( char *pItemName, int iNumber  );
    bool    IsThisItemEquipped ( char *pItemName  );
    bool    IsThisSkillActived ( unsigned short ustSkillItemID,unsigned short ustSkillLevel );

	int		GetWeekKillNum();
	int		GetAllKillNum();
	int		GetSeriesKillNum();

	void	ProcTimeStep(int StringID,int TimeStep);

    int     GetMapIdByName( const char* pszMapName );
//void    GiveExploit( int nExploit );
//void    SetOfficialLevel( int nLevel );
    void    TeashSkill( std::vector<int>&vectorSkill );
    void    AddSkill( int nSkillId, int level, bool bMessageDialog = true  );
    int     GetSkillLevel( int nSkillId );

    void    AddXinFa        ( int nXinFaId, int level, bool bCheck = true, bool bMessageDialog = true );
    void    GMAddXinFa      ( int nXinFaId, int level );
    int     GetXinFaLevel   ( int nXinFaId );
    int     GetXinFaMaxLevel();

    virtual void AddItem( const char* pszItemName, int nItemCount ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 );
    virtual void AddItemByItemid( const unsigned short ustItemid, int nItemCount, bool bIsBound = true ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 );
    virtual void AddEquipByItemId( const unsigned short ustItemid, bool bStarRandom, int16 nStarLevel, bool bIsBound = true ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 );
    virtual void AddItemInWorld( unsigned short ustItemid, int nItemCount ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 );
	virtual void AddEquipRandAttrItem( unsigned short ustItemid, bool bIsBound = true ,int nRandId1 = 0, int nRandId2 = 0, int nRandId3 = 0, int nRandId4 = 0, int nRandId5 = 0, int nRandId6 = 0, int nRandId7 = 0, int sysType = 0, int typeID = -1 );

    virtual void AddRecipe ( unsigned short ustRecipeID );
    virtual bool HaveRecipe( unsigned short ustRecipeID );

//void    Quest_CastQuest( int nQuestID );
//void    Quest_GetQuest( int nQuestID );
    void    Quest_CancelQuest( int nQuestID );
    bool    Quest_DoneQuest( int nQuestID );
    bool    Quest_SetQuestState( int nQuestID, int nState );
    void    Quest_GetQuestState( int nQuestID, int nVarID );
    void    Quest_RelateQuest( int nQuestID, int nState, int nEnter );
    bool    Quest_CanGetNewQuest( int nVarID );
    //称号
    virtual void    AddTitle(unsigned short nstTitleID);
    virtual void    RemoveTitle(unsigned short nstTitleID);
    int     HaveThisTitle(unsigned short nTitleID);

    void    GetPlayerCountVar( int nQuestID, int nVarID );

    void    RefreshMonster( int nMapId, int x, int y, const char* szArea );
    void    PlayerMusic( const char *szFileName, short stParameter );

    void    MakeItem(  BYTE byCreatNewOrOld, /*int nMakeType,*/ int nRate, /*BYTE byEquipType, BYTE byItemType,
                        float fX1,float fX2,float fX3,float fX4,
                        float fY, float fA,float fX,*/int nIdBegin[], int nIdEnd[], int nCount/*,
                        float fw*/ );
    void    ShowQuestDlg( int nVarid, const char* szInfo );
    void    ShowPubQuestDlg( int nVarid, int nType, const char* szInfo );
    void    UseSkill( int nSkillId, int nSkillLevel );
    void    AddStatusByScript( int nStatusID, int nStatusLevel );
    void    PopNpcList();
    int     GetWorldTime( const char *pszTimeType, bool bRealTime );
    int     GetBirthday( int nTimeType );
    void    ShowBank();
    BOOL    SetStorage();
    BOOL    SetMountStorage();
    void    ShowMail();
    void    NpcMoveNext();
    void    NpcStopMove();
    void    NpcStartMove();
    void    NpcPlayAnim( const char* szName, int nTimes, const char* szEndName, bool bForView, int nNpcId );
    BOOL    IsNpcPlayAnim( int nNpcId, const char* szName );

    void    ScenePlay( int nSceneID, bool bView );
    void    NpcScenePlay( int nNpcID, int nSceneID, bool bView );

    void    BlackScreen ( int nTime, bool bView );

	bool	IsCanPet( void );
	bool	DoPet(int nIndex);

    BOOL    CanLearnSkill( int nSkillId, int nSkillLevel );
    bool    IsCanRide( void );
    void    DoRide( int nId );
    void    DoRideFristMount( );
    void    AddSkillToFristMount( uint16 skillId, uint8 level );
    void    DoHitch( int nID, bool bBack );
	void    DoHitchByTeam(int nID,int TeamnID,bool bBack);
    virtual short GetRideId();
	virtual uint16 GetRideLevel();
    void    SetDialogName( const char* szName );
    void    SetHotkey( int nIndex, int nID );
    BOOL    LogInfoToDB( const char* szInfo );
    int     GetTeamPlayerCount();
    int     GetTeamID();
    int     GetTeamPlayerLevel( int nType );
    int     GetTeamAverageLevel();
    int     GetTeamPlayerID( unsigned int nIndex );
    bool    IsTeamHeader();
    int     AddTeamFriendly(int nValue);
    void    SetDstPlayer( int nId );
    void    CreateMonster( int nMapId, float fPosX, float fPosY, float fRadius, float fBodySize, int nMonsterIndex, int nMonsterNum );
    void    CreateSpecialMonster( int nMapId, float fPosX, float fPosY, float fRadius, float fBodySize, int nMonsterIndex, int nMonsterNum );
    void    CreateMonsterEx( int nMapId, float fPosX, float fPosY, float fRadius, int nMonsterIndex, int nFightCamp, int nForce, int nRouteID, int nCountry = 0);
    void    CreateSpecialMonsterEx( int nMapId, float fPosX, float fPosY, float fRadius, int nMonsterIndex, int nFightCamp, int nForce, int nRouteID);
    void    CreateRouteMonster( int nMapId, float fPosX, float fPosY, float fRadius, int nMonsterIndex, int nRouteID );
    virtual int GetNullItemCount( unsigned short usItemBagItem );
    void    Sleep( DWORD dwTime );
    virtual void CallScript( const char* szFileName,int nEnterId, GameObjectId nPlayerId, bool bDbId );
    void    CloseDlg();
    int     GetMapId();
    bool    IsInZone( const char* pszName );
    void    PlayEffect( const char* pszName, float fX, float fY, float fZ, bool bIsCast );
    void    ShowIntonateBar( DWORD dwTime, int nStringID, int nActionID, int nType, int nID );

    void    AddPkValue(int nValue,bool dailypkvale);
    void    DecPkValue(int nValue);
    void    SetPkValue(int nValue);
    int     GetPkValue();
    int     GetPkState();
    int     GetPkMode ();
    bool    SetPkMode (int nMode);    
    void    OpenClientUI(int UIFlag, int openType = 0, int64 openParam = 0 );
    void    NotarizationSuccess( int nMember1,int nMember2,int nValue);
    void    NoticeNotarizationResult(GameObjectId iPlayer1,const char *pszAnd,GameObjectId iPlayer2,const char *pszText,int nMapId, int nX, int nY,DWORD time, DWORD color);
    int     GetBagSize( int bagType );
    virtual void AddBagSize( int bagType, int nSize );    
    bool    IsEverybodyAllReady(GameObjectId iPlayerId,int nValue);
	bool    IsEverybodyAllHere();    BOOL    IsMapActive( int nMapId );
    int     GetMapCount( DWORD dwId );

    void    GetOfflineHookExp(uint8 nHookLevel);
    bool    IsOfflinePassOneWeek();

    bool    AddSysDoubleExpTime ( int nValue );
    bool    AddItemDoubleExpTime( int nValue );

    // 创建保护对象
    virtual void CreateProtectChar( int monsterId, int varId, bool isCanRide );
    virtual void LostProtectChar();

    // 获得保护对象的怪物索引
    int     GetProtectCharMonsterIndex();
    int     GetRankLevel(int index);
    
    bool IsHaveStatus(short shStatusID);

    void AddPlayerIntegralMax( int nSize );

    int     HaveThisItem_Byid( unsigned short ustItemID );
    void    RemoveThisItem_Byid( unsigned short ustItemID, int iNumber  );
    bool    IsThisItemEquipped_Byid ( unsigned short ustItemID);

    virtual int  GetStorageItemGrid ();
    virtual int  GetStorageMountGrid(); 
    virtual bool AddStorageItemGrid(unsigned char nValue); 
    virtual bool AddStorageMountGrid(unsigned char nValue);

    void UpdatePkValueMaxDaily(int offset);
    void SetStatusByScript( int nStatusID, int nStatusLevel );
    void InsertDelayScript(int delaytime,int scriptindex,bool forplayer = false);
    void ScriptLog(const char* pszKeyWord,const char* pszContent);
    void RemoveDelayScript(int scriptindex,bool forplayer = false);
    void ShowTimeTop(DWORD showtime);
    void ShutDownTimeTop();

    virtual void BeckonPlayer( GameObjectId nPlayerId );
    virtual void CallScriptTeam( const char* szFileName, int nEnterId ); 
    virtual int  AddMount( unsigned short usMountId );
    virtual bool HasMount( unsigned short usMountId );
    virtual int  RestoreMountEnjoyment( );
	virtual bool IsMountFull();

    virtual bool IsPetFull();
    virtual int  GetPetNumber();
    virtual int  AddPet( int monsterId, int quality, int sex );
    virtual bool HaveBreedPet();
    virtual void PetBreedAcquire() ;
    virtual bool AddPetIdentify ( uint16 petType );
    virtual int  GetPetMaxLevel();
    virtual int  GetActivePetIndex();

    virtual int  GetDaoxing();
    virtual void AddDaoxing( int nValue );
    
    virtual void AddLevel(int level);
    virtual bool IsInArea(int Lx,int Ly,int Rx,int Ry);
    virtual int  SelfPosX();
    virtual int  SelfPosY();
    virtual void DropItem(int ItemId,int ItemNum,bool belong = true);
    virtual bool CreateScriptNpc(int NpcId,int MapId,int PosX,int PoxY,unsigned int unOnTime);
    // virtual bool DeleteScriptNpc(int beginNpcId,int endNpcId);

    virtual bool RecordTime( int nVarId );  // 纪录当前时间
    virtual bool IsExpired( int nVarId, int keyHour, int keyMinute, int minDuration );   // 是否到过了HourTime这个时间点

    virtual bool RecordTeamTime( int nVarId );  // 纪录当前时间
    virtual bool IsTeamExpired( int nVarId, int keyHour, int keyMinute, int minDuration );   // 是否到过了HourTime这个时间点
    virtual void ClearTeamExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId );  // 清除队伍中所有超过这个时间点的变量值

    virtual void RecordExploitTime ();

    // 新加的时间脚本接口
    virtual void RecordTimeVar( int nVarID );
    virtual bool IsTimeVarPassOneDay( int nVarID );
    virtual void RecordTeamTimeVar( int nVarID );
    virtual bool IsTeamTimeVarPassOneDay( int nVarID );
    virtual void ClearTeamTimeVar( int nVarID, int nClearVarID );

    virtual bool ScriptCreateStage( const DWORD dwMapID, int nCount, bool bUsePlayerLevel, unsigned short ustMapLevel );
    virtual bool IsStageExist( const unsigned short dwMapID );
    virtual bool IsStageWaitRelease(  unsigned int nMapID );
    virtual bool LeaveStage( unsigned short ustMapID, float fX, float fY, bool bTeamLeave, unsigned short ustTime );

    // 幸运15关相关
    virtual int GetLuckRewardLevel();
    virtual void EnterLuckReward();
    virtual void UpdateLuckReward( int nType );
    virtual bool IsCanLuckReward();
    virtual bool IsCanNextLuckLevel();
    virtual bool IsCanAcceptQuest( unsigned char uchLevel );
    virtual bool IsCanReceiveReward();
    virtual void SetCanLuckReward();
    virtual void SetLuckSummonCount( unsigned short ustCount );
    virtual unsigned short GetLuckSummonCount();

   
    virtual bool OperateJinDing( bool bOperate, int nValue ); // 兑换金锭
    virtual bool OperateJinPiao( bool bOperate, int nValue ); // 金票兑换

    virtual bool OperateHonour ( bool bOperate, int nValue );

    // 显示宝箱界面
    virtual void ShowTreasureBox();
    virtual void DrawFromPlatform( uint16 infoType );

    virtual void SetAreaCurrentReputation( int nMapID, int nValue );
    virtual void AddAreaCurrentReputation( int nMapID, int nValue );
    virtual void SubAreaCurrentReputation( int nMapID, int nValue );
    virtual int GetAreaCurrentReputation( int nMapID );

    virtual void SetAreaMaxReputation( int nMapID, int nValue );
    virtual void AddAreaMaxReputation( int nMapID, int nValue );
    virtual void SubAreaMaxReputation( int nMapID, int nValue );
    virtual int GetAreaMaxReputation( int nMapID );

    virtual bool SetNextStage( int nNextStage );

    // 战场相关 
    virtual bool InitBattle( int nMapID, int nType, int nLevel, unsigned char uchTurns, int nSignTime, int nFightTime, int nMaxUnitCount );
    virtual bool ShowBattleSignUpDlg( int nType, const char* szInfo );

    virtual void SetChallengeScore( int nValue, int nOp );
    virtual int  GetChallengeScore();
	virtual bool checkSecondPassword(int checkop);

    virtual void CallMailList();

    virtual bool FlyToPlayer( int nType );

    // 小队混战战场相关
    virtual void AddTeamBattleIntegral( int nIntegral );

    virtual void SetNpcShow( GameObjectId ustNpcID, unsigned int nSpaceTime );
    virtual void SetNpcHide( GameObjectId ustNpcID, unsigned int nSpaceTime );

    virtual void AddSkillPoint( int nType, int nValue );
    virtual void SubSkillPoint( int nType, int nValue );
    virtual void SetSkillPoint( int nType, int nValue );
    virtual unsigned short GetSkillPoint( int nType );

    //成就
    virtual void TriggerAchieveByType( uint16 nValueType, int32 nValue, bool bAddValue );
    virtual void TriggerAchieveByID  ( uint16 nId );
    virtual void TriggerDeathAchieveByType( uint16 nValueType );

    virtual int  OnNpcShip();
    // 获得ID
    virtual int GetTargetId();

    //
    virtual void PlayMovie( unsigned int nMovieId, DWORD dwPlayTime );

    // 获得怪物的状态
    virtual int GetMonsterTypeStatus();

    // 改变怪物的状态
    virtual void ChangeMonsterTypeStatus( int nStatus = 0 );

    // 开始某事件
    virtual void StartEventByID( uint16 nEventID, bool bBroadcast = false );

    static uint8 GetOperateType( int nOp )
    {
        switch( nOp )
        {
        case SKW_SETADD:
            return EOT_Add;
            break;
        case SKW_SETSUB:
            return EOT_Sub;
            break;
        case SKW_SETMUL:
            return EOT_Mul;
            break;
        case SKW_SETDIV:
            return EOT_Div;
            break;
        default:
            break;
        }

        return EOT_Set;
    }

	virtual char GetTPHJRank();
	virtual void SetTPHJRank(char value,int operType=0);

	virtual void SetPetUnactive();
	virtual void PlayAnim(const char* chanim,int times,const char* endanim);//角色播放动作

	virtual void AskPlatformActivity(int _type);//

	virtual bool IsOnBiaoChe();

	virtual void ClearStatusByid(int status_id);
    
    virtual void ChangeTimeHandleStates(unsigned int Index,int Value);
	virtual void ResetTimeHandleStates(unsigned int Index);
	virtual void ClearTimeHandle(unsigned int Index);
	virtual void SetWorldBattleCountry(int CountryID);
	virtual void ChangeGamePlayerDuration(int Count);
	virtual void ChangePetMode(int ModeID,int Sec);

	virtual void UseItem(unsigned short ustItemId);
	virtual void AddCard(short stCardID, short stLevel);
	virtual void TriggerSevenDays();
	virtual int AddFriendPoint(int distance , int FriendlyPoint);

	virtual unsigned short GetPlayerStates();

	virtual int GetGamePlayerDuration();

	virtual int IsInFight();

	virtual void SetScriptStates(unsigned short StatesID);

	virtual bool CanFlyToCouple();

	virtual void DropQuestEntrust();

	virtual void DoneQuestEntrust();

	//狩猎任务相关
	virtual int GetTodayHuntingCount(); //获得今天已经做了几次狩猎任务
	virtual void OperateHuntingCount( int nType, int nValue ); //设置狩猎任务次数，0表示加，1表示减，4表示设置
	virtual void DoneHuntingQuest( int nQuestId ); //完成nQuestId任务并添加一个随机狩猎任务
	virtual void CanelQuestEntrust(int nQuestID);
	virtual int FlytoPosition(int Type);
	virtual void AddHonourByTeam(int Num);
	virtual int GetStrongCountry();
	virtual int GetWeakCountry();

	virtual void ChangePlayerPoint(int Op,int Value,int States);

	virtual void SetMonsterArray(int Index,int Value);
	virtual int	 GetMonsterArray(int Index);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 国家相关
#include "CountryScript.h"
#include "RelationScript.h"
#include "GuildScript.h"
#include "CampBattleScript.h"
#include "FamilyScript.h"
#include "GameBattleScript.h"
protected:
    GameObjectId     m_recordCurCharId; // 保留一份 嵌套调用脚本会占用m_nCurCharId
    GameObjectId     m_recordDstId;     // 保留一份 嵌套调用脚本会占用m_nDstId
    GameObjectId	 m_nCurCharId;
    GameObjectId     m_nDstId;
};

extern CServerVarInterface g_svi;

#endif // __GAMESERVER_SERVERVARINTERFACE_H__
