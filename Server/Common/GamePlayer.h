/********************************************************************
    Filename:     GamePlayer.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_GAMEPLAYER_H__
#define __GAMESERVER_GAMEPLAYER_H__

#pragma once

#include "BaseCharacter.h"
#include "ScriptVM.h"
#include "GraphicCodeCheck.h"
#include "Dxsdk/d3dx9math.h"
#include "ItemBag.h"
#include "Bag/SkillBag.h"
#include "Bag/ActionBag.h"
#include "Bag/StoreTradeBag.h"
#include "Bag/HotkeyBag.h"
#include "Bag/MouseBag.h"
#include "Bag/ProduceItemBag.h"
#include "ItemDetail.h"
#include "ScriptKeyWord.h"
#include "ScriptFunctionDefine.h"
#include "SuitManager.h"
#include "ShopMgr.h"
#include "StorageMgr.h"
#include "Enmity.h"
#include "RestoreColdDown.h"
#include "Mutex.h"
#include "FileDB.h"
#include "NpcBaseEx.h"
#include "YuanBaoHandle.h"
#include "RestoreColdDown.h"
#include "TitleServerManager.h"
#include "TitleConfig.h"
#include "Trigger.h"
#include "RecipeConfig.h"
#include "ActionWatchManager.h"
#include "BuyBackPack.h"
#include "MailManagerPlayer.h"
#include "GuideQuestConfig.h"
#include "GameDefinePlayer.h"
#include "RelationManager.h"
#include "CountryManager.h"
#include "GuildManager.h"
#include "StarLevelUpConfig.h"
#include "RunningScriptControl.h"
#include "StallManager.h"
#include "Configure.h"
#include "AchieveServerManager.h"
#include "BargainingManager.h"
#include "PasswordDefine.h"
#include "XinFaManager.h"
#include "PetManager.h"
#include "StallConfig.h"
#include "FamilyManager.h"
#include "GameFamily.h"
#include "TPHJManger.h"
#include "SevenDayManager.h"
#ifdef NPGUARD
#include "CSAuth.h"
#endif
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#pragma warning(disable:4101)

#define HINTMESSAGESENDRATE 10000 //��ʾ��Ϣ�ķ���Ƶ��m

// ��������Tip����ı����ĸ�λ�͵�λByte
#define TIPVARHIGH 6
#define TIPVARLOW 7

class PKCopyScene;
class CodeData;
class LuckReward;
class MonsterBaseEx;
class GamePlayer : public BaseCharacter, public DPlayerChar,public BuffEvent,
                   public TPlayerEnmity<EnmitySize>, 
                   INHERIT_POOL_PARAM( GamePlayer,50 )
                   /*,public RunningScriptControl*/
{
//////////////////////////////////////////////////////////////////////////
public: // �ṹ��

    enum EGMPermission
    {   
        GP_FLYTOMAP       = 1<<0, // �ɵ�ͼ
        GP_BECKONPLAYER   = 1<<1, // ����
        GP_FLYTOPLAYER    = 1<<2,
        GP_KILLTARGET     = 1<<3,
        GP_SUNMMONMONSTER = 1<<4,
        GP_BULL           = 1<<5,
        GP_SHOWPOS        = 1<<6,

        GP_SETADDEXP      = 1<<7,
        GP_NPCLIST        = 1<<8,
        GP_CREATEGUILD    = 1<<9,
        GP_LEARNSKILL     = 1<<10,
        GP_ADDITEM        = 1<<11,

        GP_IAMGOD         = 1<<12,
        GP_SETMONEY       = 1<<13,
        GP_ADDEXP         = 1<<14,
        GP_CAPTURE        = 1<<15,
        GP_ADDSKILLEXP    = 1<<16,

        GP_GETYUANBAO     = 1<<17,
        GP_UPDATEYUANBAO  = 1<<18,  
        GP_KICKCHAR       = 1<<19, // ����

        GP_ADDMONSTER     = 1<<20,
        GP_ONDEATH        = 1<<21,

        GP_PERPETUAL      = 1<<22,
        GP_DETROY         = 1<<23,

        GP_LOW     = GP_FLYTOMAP + GP_BECKONPLAYER + GP_FLYTOPLAYER + GP_KILLTARGET + GP_BULL + GP_SHOWPOS,
        GP_MEDIUN  = GP_LOW + GP_SETADDEXP +  GP_NPCLIST + GP_CREATEGUILD + GP_LEARNSKILL + GP_ADDITEM,
        GP_HIGH    = GP_MEDIUN + GP_IAMGOD + GP_SETMONEY + GP_ADDEXP + GP_CAPTURE + GP_ADDSKILLEXP,
        GP_HIGHEST = GP_HIGH + GP_GETYUANBAO + GP_UPDATEYUANBAO,

        GP_ROOT           = 0x7fffffff,
    };

    enum EConstDefine
    {
        // ϵͳ��������
        SystemServer = 0,
        SystemWorld,
        SystemSingle,

        // ���볡������
        EnterStage = 1,     // ���볡��
        LeaveStage = 2,     // �뿪����, ���뵽�µĳ���

        PlayerChangeStage = 0,  // ������ת
        TeamChangeStage   = 1,  // ������ת
        GuildChangeStage  = 2,  // ������ת

        // �ֶη���Ϣ����
        SendQuestMessage= 1    ,  //�����ȷ�
        SendGuildMessage,		//����
		SendRelationMessage,    //����
        SendOtherMessage,       //����
        SendIdentifyMessage,   //ͼ����Ϣ
        SendFamilyMessage,     //����
        SendMessageEnd,

		//���ڵ�ս������
		Battle_Non = 0,  //����ս��
		Battle_Team = 1,  //С��ս��
		Battle_Camp = 2,  //��Ӫս������
    };

	enum EScriptStates
	{
		EScriptStates_Init = 0,
		EScriptStates_OnDead = 1,
	};

    struct SDBInfo
    {
        SDBInfo() 
        {
            memset( this, 0, sizeof( SDBInfo ) );
			pdwCharacterID.clear();
			pdwCharacterMapId.clear();
			ustCountryID.clear();
			pdwSlot.clear();
        }

        uint32 dwAccountID;
        uint32 dwCharacterID;
		std::vector<uint32> pdwCharacterID;
		std::vector<uint32> pdwCharacterMapId;
		std::vector<short> ustCountryID;
		std::vector<uint32> pdwSlot;
        //uint32 pdwCharacterID[More_iCharPerAccount];
        //uint32 pdwCharacterMapId[More_iCharPerAccount];
        //short  ustCountryID[More_iCharPerAccount];
    };

    struct SReliveInfo
    {
        SReliveInfo()
        {
            bFreeRelive  = false;
            bSendMessage = true;
            bFlyToMap    = true;
            bDeathExit   = false;
            nReliveHP    = 10;
            nReliveMP    = 10;
			byAddition	 = 0;
        }

        bool bFreeRelive;   // �Ƿ���Ѹ���
        bool bSendMessage;  // �Ƿ�����Ϣ���ͻ���
        bool bFlyToMap;     // �Ƿ�Ҫ���е�ͼ
        bool bDeathExit;    // �Ƿ������˳�

        int nReliveHP;      // �ظ�HP( �ٷֱ� )
        int nReliveMP;      // �ظ�MP( �ٷֱ� )

		BYTE byAddition;	//������Ϣ���Ӹ�buf�ȵȣ�
    };

    typedef std::vector<unsigned short> ItemContainer;
    typedef ItemContainer::iterator     ItrItemContainer;

//////////////////////////////////////////////////////////////////////////
    struct UseItemInfo
    {
        UseItemInfo()
        {
            Clear();
        }
        unsigned char uchItemBagType;
        ItemBag* pItemBag;
        short stIndex;
        short stItemID;
        short stCount;
        __int64 nGuid;

        void Clear()
        {
            uchItemBagType = 0;
            pItemBag = NULL;
            stIndex = -1;
            stItemID = -1;
            stCount = 0;
            nGuid = 0;
        }

        bool IsValid() { return ( pItemBag != NULL && stIndex != -1 && stItemID != -1 && nGuid != 0 ); }
    };

    struct WaitChangeStage
    {
        WaitChangeStage() : uchType( 0 ), dwMapID( 0 ), dwCurrentMapID( 0 ) {}

        uint8 uchType;              // ����
        DWORD dwCurrentMapID;       // ��ǰ��Map
        DWORD dwMapID;              // Ҫ����ĵ�ͼ
        float fX;
        float fY;
        float fDir;
        GameTimerEx xTimer;         
    };

    struct SkillItemRelive
    {
        uint8 uchType;
        int nItemID;
        int nValue;
        GameTimerEx xTimer;
    };

public: // ����
    DECLARE_POOL_FUNC( GamePlayer )

    GamePlayer();
    virtual ~GamePlayer();

    // �ƶ�ģ��
#include "PlayerMoveActionModule.h"

public:
    // IBaseCharProperty
    virtual SCharFightAttr* GetCharFightAttr();
    virtual void            SetHPMax( uint32 hpMax );
    virtual uint32          GetHPMax()              ;
    virtual void            SetMPMax( uint32 hpMax );
    virtual uint32          GetMPMax()              ;
    virtual int             GetHP()                 ;
    virtual int             GetMP()                 ;
    virtual void            SetHP( int nHp )        ;
    virtual void            SetMP( int nMp )        ;
    virtual void            OperateHP( uint8 uchOperateType, int nValue );
    virtual void            OperateMP( uint8 uchOperateType, int nValue );

    virtual bool            HasHPMaxChange()        ;
    virtual bool            HasMPMaxChange()        ;

    virtual float           GetMoveSpeed()              
	{ 
		if (mBiaocheState&&m_BiaoCheSpeed > 0.0f)
		{//����ڳ�״̬�����ڳ��ٶ�
			return m_BiaoCheSpeed;
		}
		return GetCharFightAttr()->moveSpeed.final; 
	}
    virtual void            SetMoveSpeed( float fMove ) { GetCharFightAttr()->moveSpeed.base = fMove; GetCharFightAttr()->moveSpeed.UpdateFinal(); }

    void  SetXP( int xp );      // ����XPֵ
    int   GetXP() { return gCharInfoServer.baseinfo.liveinfo.nXp; } // ���XPֵ

    virtual bool IsPlayer() { return true; }

    // ��ʼ���������
    virtual void  Initialize();

    virtual void  ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue ); // �ڴ�����Ϣǰ����
    virtual void  Run( DWORD dwCostTime );                                           // ����ִ�� ������

    virtual void  EnterMySight( BaseCharacter* pWho );    
    virtual void  ExitMySight( BaseCharacter* pWho );
    virtual Msg*  FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize);
    virtual void  RefreshCharData( DWORD dwCostTime);                // ˢ����������[����Ƶ��1��һ��]
    virtual short IsSkillCanUse(BaseCharacter *pDst, int skill_no, int skill_level);      // �Ƿ����ʹ�ü���
    virtual bool  CheckWalkPreconditionState();                      // �жϿɷ��ƶ�
    virtual bool  CheckUseSkillPreconditionState();                  // �ж�NPC�Ƿ���һ������ʹ��һ�����ܵ�״̬

    virtual bool  OnScriptSkill( ItemDefine::SItemSkill* pItemSkill );
    virtual short ApplySkillCost( ItemDefine::SItemSkill *pSkill );  // Ӧ�ü�������
    virtual long  ApplyBufferStatus(int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue); // Ӧ��buff
    virtual void  OnBuffStatusChanged( bool bSendMessage );
    virtual void  OnSitDownRestore( );   // ���µĻָ�����
    virtual void  OnStandUpRestore( );   // վ��Ļָ�����
    virtual void  IncreaseSingleSkillExp( int nSkillExp );
    virtual void  IncreaseTotalSkillExp( int& nSkillExp );    
    virtual void  OnEnterFightState(); // ��ս��״̬
    virtual void  OnOutFightState();   // ��ս��״̬

    virtual bool  TryPassivenessTriggerAttack();    // ���Ա�����������
    bool  TrySelfPassivenessTriggerAttack();        // ���Դ�������������
    bool  TryMountPassivenessTriggerAttack();       // ���Դ������ﱻ������

    
    // �ж��ܹ������Է�
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // �ж��Ƿ��ܱ�����
    virtual bool CheckCanBeAttack();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    // �ж��Ƿ�������
    bool IsHaveWeapon( int16 weapontype );  

    // ����װ�����ݵ��������
    void UpdateAllEquipData(); 

    // ����������װ����
    void UpdateAllSuitData();

    // �Ƿ���װ��ĳ��Ʒ
    bool IsCanEquip( uint8 part, SCharItem* pItem, bool bCheck = false );

    // װ��ĳ��Ʒ
    bool Equip( uint8 part, SCharItem& item, bool bJustSetItem );

    // װ������
    bool EquipArmour( uint8 part, SCharItem* pitem);

    // װ����Ʒ
    bool EquipWeapon( uint8 part, SCharItem* pItem);

    // ж��װ��
    void UnEquip( uint8 part, uint16 stPackIndex );

	//ж�²���ɾ��װ��
	void UnEquipAndRemove( uint8 part);

    // ж���������е�װ��
    void RemoveAllEquip();                            

    // ���ĳ��λװ��
    SCharItem* GetVisualEquipItem( uint8 stPart );       

    // ɾ��ָ�㲿λ��װ������װ
    void DeleteVisualEquipItem   ( uint8 stPart ); 

    // ɾ��װ������
    void RemoveEquipItemSkill    ( uint8 stPart );

    // ����ָ����λװ��
    void SetEquip( uint8 part, const SCharItem& rItem ); 

    // �����Ʒ����
    short GetWeaponType( char cWhichHand );

    // �ж��Ƿ���ĳװ��
    bool IsHaveEquipItem( uint16 nItemId );      

    // ������е���ʱ��, ��������
    void CheckAllItemOperate();

    // ������ʱ��, ��������
    bool CheckItemOperate( SCharItem* pCharItem );

    // ����װ���;ö� 
    void  SubEquipHp( short index, float fDropHp, bool& bNeedUpdateEquipHp );   

    int  GetWeaponAttack( int nType );
    int  GetArmourDefend( int nType );

    // ��÷���
    SCharItem* GetTalismanItem();
    void SetTalismanItem( SCharItem* pCharItem );
    void DeleteTalismanItem();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    // �������
    virtual void OnDeath();

    // ��Ҹ���
    void ProcessRelive( uint8 uchReliveType, SReliveInfo& xReliveInfo );
    void ProcessReliveBySkill( SReliveInfo& xReliveInfo );
    void ProcessReliveToMap( DWORD dwMapId, float fX, float fY, float fDir, SReliveInfo& xReliveInfo ); 
    void ProcessDeathExitRelive();
    
    // �������ʱ��
    SkillItemRelive& GetSkillItemRelive() { return m_xSkillItemRelive; }

    // �õ�����������Ҫ����Ʊ��
    int GetReliveOriginAllHpMp() { return m_nReliveOriginAllHpMp; } 

     // ��������������Ҫ����Ʊ��
    void SetReliveOriginAllHpMp(int nValue) { m_nReliveOriginAllHpMp = nValue; }

    // ��������ͷ�
    void PunishWhenDeath( BaseCharacter* pAttacker );

    // ����Ƿ���������
    bool CheckDeathRemit();

    // �������������Ʒ
    void DropItemWhenDeath( BaseCharacter* pAttacker );

	// ������������������
	void DropExpHonourWhenDeath( BaseCharacter* pAttacker );

    // ���������װ���־�
    void CalcEquipHpWhenDeath();

    // �����������ѹ����Ʒ
    void DropItemWhenDeadByGuildQuest();

    // ��������������߼�
    void ProcessMountAndPetWhenDeath();

    // ���������
    MapConfig::RelivePosition* GetRelivePosition( MapConfig::MapData* pMapData );
	const MapConfig::SpecRelivePosition* GetSpecRelivePosition( MapConfig::MapData* pMapData );
	short IsInBattle(MapConfig::MapData* pMapData);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // ���±仯װ���� ����Ļ�������(������������)
    // ����װ������������
    void ApplyAttrTypeToChar( uint16 attrType, uint16 part, CustomValue value );

    void ApplyEquipRandAttributesToChar     ( SCharItem* pItem, uint16 part );
    void ApplyTalismanRandAttributesToChar  ( SCharItem* pItem, uint16 part );

    void ApplyRandAttributeToChar( uint16 stRandID,   uint16 part );				// �����������
	void ApplyRandAttributeToChar( uint16 stRandID,   uint16 part, uint8 nQuality );// �����������

    void ApplyGemsToChar( SCharItem *pItem, uint16 part );
    void ApplyGemAttributeToChar( unsigned short ustItemID, uint16 part );      // ���㱦ʯ����

    void ApplySuitEquipAttributesToChar( unsigned short ustItemID );            // ������װ�������
    void ApplyStarActivationAttribute  ( SStarActivation::SEffect* pEffect  );  // �����Ǽ�������
    void ApplyStampActivationAttribute ( SStampActivation::SEffect* pEffect );

    ///////////////////////////////////////////////////////////////////////////////////////////////
    
    // ����    
    short  GetRideId(){ return m_nDromeId; }
    void   SetRideId( short sMountId ){ m_nDromeId = sMountId; }
	uint16 GetRideLevel(){ return m_nMountLevel;}
	void   SetRideLevel( uint16 nMountLevel){ m_nMountLevel = nMountLevel;}
    uint8  GetRidePos() { return m_nDromePos; }
    void   SetRidePos( uint8 pos ) { m_nDromePos = pos; }
    GameObjectId GetRideDriverId() { return m_nDriverId; }
    void   SetRideDriverId( GameObjectId nCharId ) { m_nDriverId = nCharId; }

    // �����������
    unsigned char GetMountCount() { return gCharInfoServer.baseinfo.liveinfo.ucMountCount; }
        
    // ������������
    void SetMountCount( int nValue ) { gCharInfoServer.baseinfo.liveinfo.ucMountCount = nValue; }

    // �ж��Ƿ�������
    bool IsCanRide();

    // ������, nid == -1ʱ��, ������
    bool DoRide( int nId );

	bool IsCanPet(void);
	//�ٻ�����
	bool DoPet(int nIndex);

    // ���һƥ����
    bool DoRideFristMount();

    // ����һƥ�������������
    bool AddSkillToFristMount( uint16 skillId, uint8 level );
    
    // ��õ�ǰ��ս������
    short GetRidingMountIdInDb() { return gCharInfoServer.otherdata.stMountId; }

    // ɾ������
    bool RemoveMountByGuid( __int64 nGuild );
    bool RemoveMountByIndex( uint8 uchIndex );
	bool RemoveMountByid(unsigned short usMountId,bool _All);//��������IDɾ������
    
    // �������
    __int64 AddMount( unsigned short usMountId ); // ��������guid
    int AddMount( const SMountItem& xMount );
	bool IsMountFull();

    // ��������״̬
    void SetActiveBeRiding( bool bBeRiding ) { _mountManager.SetActiveBeRiding( bBeRiding ); }

    // ��ó�ս���������
    int GetActiveMountIndex() { return _mountManager.GetActiveMountIndex(); }

    // �������
    SMountItem* GetMountByIndex( uint8 uchIndex ) { return _mountManager.GetMountByIndex( uchIndex ); }
    SMountItem* GetMountByGuid( __int64 n64Guid ) { return _mountManager.GetMountByGuid( n64Guid ); }

    // ��ó�ս����
    SMountItem* GetActiveMount() { return _mountManager.GetActiveMount(); }

    // �¶�������
    bool GotOffMultiMount();

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // �ϴ�����
    bool OnNpcShip();

    // �´�����
    bool OffNpcShip();

    // �õ��������ObjectId
    void SetNpcShipId( GameObjectId npcId ){ m_nBigShipId = npcId; }

    // �õ��������ObjectId
    GameObjectId GetNpcShipId() { return m_nBigShipId; }
    
    //////////////////////////////////////////////////////////////////////////

    // ��ӳ���
    int   AddPet( const SPetItem& xPet , uint8 source = EPetSource_Other );
    int64 AddPet( int monsterId, int quality, int sex, int generation = 0 , uint8 source = EPetSource_Other );

    bool  AddPetIdentify ( uint16 petType );
    SPetIdentify* GetPetIdentify( uint16  petType );
    ItemDefine::SItemSkill* GetPetTalentSkillByType ( uint16 petType ) ;

    // ɾ������
    bool RemovePetByGuid( __int64 nGuild, int source = EDS_Discard  );
    bool RemovePetByIndex( uint8 uchIndex, int source = EDS_Discard );

    // ��ȡ��ֳ����
    void PetBreedAcquire();

    // ��������
    bool PetBreedGenerate();

    // �㲥��ֳ��Ϣ
    void PetBreedBroadcast( int64 nOldGuid , int64 nNewGuid );

    //////////////////////////////////////////////////////////////////////////
    
    // �ȼ��ı�
    void ChangeLevel(int nNewLevel); // �ı�ȼ�

	/*
	*	Author 2012-9-11 zhuxincong
	*	DESC: �ı����
	*/

	void ChangeCountry (int& nCountryID);

    // ����ı�
    void ChangeExp( __int64 exp );

    // ������Ӿ���
    void IncreaseExp( int iRewardExp, int nSkillExp, BaseCharacter* pKillTarget = NULL );  

    // ������Ӷ��龭��
    void IncreaseTeamExp( BaseCharacter *pKillTarget );

    // ������Ҿ���
    void SetPlayerExp(int64 dwExp) { gCharInfoServer.baseinfo.liveinfo.dwExp = dwExp; }

    // �����Ҿ���
    int64 GetPlayerExp(){ return gCharInfoServer.baseinfo.liveinfo.dwExp; }

    // �������δʹ�õľ���
    void SetPlayerExpUnUsed( int64 dwExpNotUsed ) { gCharInfoServer.baseinfo.liveinfo.dwExpNotUsed = dwExpNotUsed; }

    // ������δʹ�õľ���
    int64 GetPlayerExpUnUsed() { return gCharInfoServer.baseinfo.liveinfo.dwExpNotUsed; }

    // �����ҵ��ܾ���, ����ʹ�õĺ�δʹ�õľ���
    int64 GetPlayerCurrentExp() { return GetPlayerExp() + GetPlayerExpUnUsed(); }

    // ��Ӿ���
    int IncreasePlayerExp( int& dwExp); //��������ĺ���

    // ���������ߵľ���
    void GetOfflineHookExp( uint8 nHookLevel );

    // ���߹һ�ÿ���Ӿ���ֵ
    int32 GetOfflineHookMinuteExp ( uint8 hookLevel );   

    // ����ɱ�����Ӿ���
    void ProcessKillMonsterExp( BaseCharacter* pTarget, int iRewardExp, int iRewardSkillExp );

    // ���ӵ���
    void IncreaseDaoxing( int nDaoxing );


    // ����仯��
    float GetExpChangePer() { return m_fChangeExpPer; }
    void  SetExpChangePer(float fValue) { m_fChangeExpPer = fValue; }
    float GetSkillExpChangePer() { return m_fChangeSkillExpPer; }
    void  SetSkillExpChangePer(float fValue) { m_fChangeSkillExpPer = fValue; }

    bool  IsOpenDoubleExp() { return m_bIsOpenDoubleExp; }

    bool  AddSysDoubleExpTime ( int nValue ) ;
    bool  AddItemDoubleExpTime( int nValue ) ;
    void  ClearDoubleExpStatus();

    void           SetSkillExp(uint32 dwSkillExp) { gCharInfoServer.baseinfo.liveinfo.dwSkillExp = dwSkillExp; }
    uint32         GetSkillExp() { return gCharInfoServer.baseinfo.liveinfo.dwSkillExp; }

    void           SetSkillExpUnUsed(uint32 dwSkillExpNotUsed) { gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed = dwSkillExpNotUsed; }
    uint32         GetSkillExpUnUsed() { return gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed; }

    void           SetSkillExpForSkillID( unsigned short ustSkillID ) { gCharInfoServer.baseinfo.liveinfo.ustSkillExpForSkillID = ustSkillID; } // ������Ҫ�����ļ���
    unsigned short GetSkillExpForSkillID() { return gCharInfoServer.baseinfo.liveinfo.ustSkillExpForSkillID; } // �õ���ǰ��Ҫ�����ļ���

    unsigned short GetSkillExpForSkillLevel(unsigned short ustSkillID);             // �õ����ܵĵȼ�    

    void           SetSkillExpToSkill(uint32 dwSkillExp,unsigned short ustSkillID);
    uint32         GetSkillExpToSkill(unsigned short ustSkillID);                   // �õ�ָ�����ܵļ��ܾ���

    void           OperateSkillExp( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine );
    void           OperateRecipeSkillPoint( uint8 uchOperateType, uint16 skillId, uint32 nValue, char* szFunction, int nLine );

    // ����ģ��
    #include "PlayerSkillModule.h"

    //////////////////////////////////////////////////////////////////////
    // BufferStatus
    short GetMeAddStatus        ( int i );
    short GetMeAddStatusLvl     ( int i );
    short GetDstAddStatus       ( int i );
    short GetDstAddStatusLvl    ( int i );
    float GetDstStatusRate      ( int i );
    float GetMeStatusRate       ( int i );
    int8  GetDstAddStatusTrigger( int i );
    int8  GetMeAddStatusTrigger ( int i );

    virtual void  ApplyBuffStatusToCharAttr();
    virtual SCharBaseAttr* GetCharBaseAttr(){ return &gCharInfoServer.baseinfo.baseProperty.baseAttr; }

    SBaseAttrType* GetBaseAttr( uint8 nWhich );
    SBaseAttrType* GetAddSubBaseAttr( uint8 nWhich );

    void ApplyBaseAttrToFightAttr( bool total, uint16 part, bool bAdd = true);

    void SetCharAllBaseAttributeBase( int16* atttrBaseArray, int nSize);
  
    bool IsNeedDropTaskItem( short stQuestId, short stTaskState,int nItemId );

    // Update
    void RunUpdateTime( uint32 dwCostTime );   // ����һЩʱ�����ƹ���

    // PK    
    void       SetDstPlayerId( int nId ){ m_nDstPlayerId = nId; }
    int        GetDstPlayerId(){ return m_nDstPlayerId; }
    void       GetBirthday( int *pYear, int *pMonth, int *pDay );

    void       KillCapturePet();
    bool       CreateProtectMonster( int monsterId, int varId, bool isCanRide = false);   // ������������ ͬʱ��һ����������
    //void       LostProtectChar();                               // ʧȥ��������
	void       ResetLostProtectCharData();						// ʧȥ��������ʱ���ñ��� 
    void       KillProtectChar();                               // ɱ��Ҫ�����Ķ���
    bool       HaveProtectChar() { return m_ProtectCharID>=0; } // �Ƿ��б�������
    GameObjectId GetProtectCharID(){ return m_ProtectCharID; } // ��ñ��������ID
    int        GetProtectCharMonsterId();                       // ��ñ�������Ĺ�������
    void       SetCurZoneID( int id ){ m_nCurZoneID = id; }
    int        GetCurZoneID(){ return m_nCurZoneID; }
//     bool       IsInPrivateShopZone();
//     void       SetInPrivateShopZone( bool bInPrivateShopZone );
    void       GuardExpError();                // ���������쳣         
    void       SendCharAttibuteToClient();    // ���½�ɫ������ֵ���ͻ���
    void       SendVisualEquipDataToClient(); // ���½�ɫ��װ�����ͻ���	

    int  GetNormalAttackSkillId(int nAttackHand);
    void UpdateNormalAttackSkillId();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // �����ͨ��������
    void AddNormalBagNowSize( unsigned short ustNum );

    // ��Ӳ��ϱ�������
    void AddMaterialBagNowSize( unsigned short usNum );

    // �����ͨ��������
    unsigned char GetNormalBagSize() { return gCharInfoServer.baseinfo.liveinfo.ucNormalBagSize;  }

    // ��ò��ϱ�������
    unsigned char GetMaterialBagSize() { return gCharInfoServer.baseinfo.liveinfo.ucMaterialBagSize;}

    // ������񱻸�����
    unsigned char GetTaskBagSize() { return ITEM_BAGTASK_MAX; }
    
    // ��òֿ⿪����������
    unsigned char GetStorageItemGrid() { return gCharInfoServer.baseinfo.liveinfo.nStorageItemGrid; }
    unsigned char GetStorageMountGrid() { return gCharInfoServer.baseinfo.liveinfo.nStorageMountGrid; }

    // ��Ӳֿ��������
    bool AddStorageItemGrid (unsigned char nValue);

    bool AddStorageMountGrid( unsigned char nValue );

    // �����ͨ������Ʒ����
    SCharItem* GetNormalBagPointerByIndex( int nIndex );

    // ��ò��ϱ�����Ʒ����
    SCharItem* GetMaterialBagPointerByIndex( int nIndex );

    // ������񱳰���Ʒ����
    SCharItem* GetTaskBagPointerByIndex( int nIndex );

    // ��ñ�����Ʒ����
    SCharItem* GetBagItemByGuid( int64 guid );

	//lyh++ ������Ʒid��ø���Ʒ��GUID
    int64 GetItemGUIDByItemID(unsigned short ustItemId);

    // ɾ��������Ʒ����
    bool  RemoveBagItemByGuid( int64 guid, int count );

    // �Ƿ���ĳ�ֵ���
    int GetItemCount( unsigned short ustItemId );
    
    // ��ñ����ո�����
    int GetNullItemCount( unsigned char ucItemBagType );
    
    // ���һ����Ʒ
    short AddItem(int nItemId, short nCount, uint8 nItemSource = 0, bool bIsBound = true, int64* pGuid = NULL,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 );
    short AddEquipItem(int nItemId, short nCount, uint8 nItemSource = 0, bool bIsBound = true, int64* pGuid = NULL, bool bStarRandom = false, int16 nStarLevel = 0 ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 );
    short AddItemToBag(SCharItem &item, unsigned short &nCount, uint8 nItemSource = 0, int sysType = 0, int typeID = -1);
	short AddItemToBagByIndex(SCharItem &item,int Index, unsigned short &nCount, uint8 nItemSource = 0);
	short AddEquipRandAttrItem(int nItemId, short nCount, uint8 nItemSource = 0, bool bIsBound = true, int64* pGuid = NULL, int nRandId1 = 0, int nRandId2 = 0, int nRandId3 = 0, int nRandId4 = 0, int nRandId5 = 0, int nRandId6 = 0, int nRandId7 = 0, int sysType = 0, int typeID = -1 );
	void  AddItemSystemChat(int sysType, int typeID, SCharItem &item);
	const char* GetDefaultCountryNameById( int Id );

    // ɾ��һ����Ʒ
    bool RemoveItem( unsigned short ustItemId, unsigned short ustCount );
    bool RemoveItem( uint8 uchBagType, uint8 uchIndex, int nCount, int64 n64Guid );

	void RemoveAllItem( uint8 uchBagType );															//�Ƴ�ָ��������������Ʒluo.qin 3.21
	int	 ReturnItemID( uint8 uchBagType ,unsigned short ustItemId );								//����ָ��ID�ŵ�װ������Ӧ�����е�λ��luo.qin 3.22

	

    // ��ñ���ָ��
    ItemBag* GetItemBagByItemType( uint16 ustItemType );
    ItemBag* GetItemBagByBagType( uint8 uchBagType );

    // ��ñ�������
    uint8 GetItemBagType( uint16 ustItemType );

    // ��ȡ����
    bool  PickPackageItem( int nItemPackageID );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool RecalcHpMp        ( uint8 ucFullHpMp, uint8 ucSendMsg );
    bool RecalcBaseProperty( bool bInitBase, uint8 ucFullHpMp, uint8 ucSendMsg, uint8 ucWherefore ); // ���������������� ����һ�����ԺͶ�������

    bool IsInLoginStage() { return _bInLoginStage; }
	unsigned long GetLastEnterWorldTime(){ return m_dwLastEnterWorldReqTime;}

    void  SetGateID( short stGateID ){ m_stGateID = stGateID; }
    short GetGateID(){ return m_stGateID; }

    bool IsWantSwitchGameWaitSaveInfoOk(){ return _bWantSwitchGameWaitSaveInfoOk; }
    void SendClientSwitchGateInfo();

    // ���ݿ�
    bool IsCanAutoSaveToDB();   // �ж��ܷ��Զ�����

    void SaveCharacterToDB();	// ������
    SCharDBInfo& GetCharInfo() { return gCharInfoServer; }

    // ����ʱ������
    void BuildRuntimeInfo( SRuntimeInfo& runtimeInfo );

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // ��û���ֵ
    unsigned short GetActivity() { return gCharInfoServer.baseinfo.liveinfo.activity; }
    unsigned short GetActivityMax() { return gCharInfoServer.baseinfo.liveinfo.activityMax; }
    void OperateActivity( uint8 uchOperateType, int value, bool bSendMessage = true  );

    // ��þ���ֵ
    unsigned short GetVigor() { return gCharInfoServer.baseinfo.liveinfo.vigor;  }
    unsigned short GetVigorMax() { return gCharInfoServer.baseinfo.liveinfo.vigorMax;  }

    // ���þ���ֵ
    void SetVigor( unsigned short ustValue ) { gCharInfoServer.baseinfo.liveinfo.vigor = ustValue; }

    // ����������ܵ�
    unsigned short GetRecipeSkillPoint( unsigned char recipeType );
    
    // ���óɲ����ܵ�
    unsigned short SetRecipeSkillPoint( unsigned char recipeType, unsigned short pointValue );
    
    // ���ְҵ
    short GetProfession() { return gCharInfoServer.baseinfo.aptotic.usProfession; }

    // ����ְҵ
    void SetProfession(unsigned short usPro) {  gCharInfoServer.baseinfo.aptotic.usProfession = usPro ; }

    // ����Ա�
    unsigned char GetSex() { return gCharInfoServer.baseinfo.aptotic.ucSex; }

    // ���ͷ��
    unsigned char GetHeadPic() { return gCharInfoServer.baseinfo.aptotic.ucHeadPic; }

    // �������
    int GetFaceID() { return gCharInfoServer.visual.faceId; }

    // ��÷���
    int GetHairID() { return gCharInfoServer.visual.hairId; }

    // ������DBID
    DWORD GetDBCharacterID() { return m_dbinfo.dwCharacterID; }

    // ����ʺ�ID
    DWORD GetAccountID(){ return m_dbinfo.dwAccountID; }

    // �����ʺ�ID
    void SetAccountID( DWORD nAccountId ) { m_dbinfo.dwAccountID = nAccountId; }

    // ����ʺ�
    const char* GetAccount() { return m_szLoginName; }

    // �����ʺ�
    void SetAccount(const char *AccountName){ strncpy_s( m_szLoginName,sizeof( m_szLoginName ),AccountName,sizeof( m_szLoginName ) - 1); }

    // ��õ�¼IP
    const char* GetLoginIP() { return m_szLoginIP; }

    // ����IP��ַ
    void SetIp( const std::string& ip){ _strIp = ip; }

    // ���IP��ַ
    const char* GetIp(){ return _strIp.c_str();}

    // Session
    /*char**/__int64        GetSessionKey(){ return _SessionKey; }
    bool         SetSessionKey ( __int64 SessionKey/*const char* szSessionKey*/ );

    // Log
    void         CheckCheatLog( const char* szFormat, ... ); // ���LOG
    void         Log          ( const char* szFormat, ... ); // Log
	void         DebugLog     ( const char* szFormat, ... ); // Log
    void         ShoppingLog  ( const char* szFormat, ... ); // �̳ǹ�����־


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    short GetPlayerAttrDataBaseTop10(int nType); //��ѯ���ݿ�������,�������еڼ�, û�в鵽 ���� -1

    void AddCharToFirstList(GameObjectId shCharID);
    void RemoveCharToFirstList(GameObjectId shCharID);    

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    int64   GetTimeVar( uint8 nVarId);
    void    SetTimeVar( uint8 nVarId, int64 n64Time );

    uint32  Get32TimeVar( uint8 nVarId);
    void    Set32TimeVar( uint8 nVarId, uint32 n32Time );
    
    // ��������ʱ��
    void SetEnterTime() { gTransferRuntimeInfo.OnLineTime = HQ_TimeGetTime(); }

    // �������ʱ��
    uint32 GetEnterTime() { return gTransferRuntimeInfo.OnLineTime; }

    // ����������ʱ��
    uint32 GetOnLineTime();

	void    SetEnterRealTime() 
	{ _nEnterRealTime = TimeEx::GetCurrentTime().GetTime(); }

	__int64 GetEnterRealTime()
	{ return _nEnterRealTime; }

	// �������ߵ�����
	uint32 GetOnlineRealTime();

    // ��������ʱ��
    void SetOffline() { m_nOfflineTime = HQ_TimeGetTime(); }

    // �������ʱ��
    uint32 GetOfflineTime() { return m_nOfflineTime; }

    //�����ϴε�¼����һ��
    bool IsLastLoginPassOneDay();
    void ProcessLoginHandle ();
    void ProcessLastLoginPassOneDay();

    //�����ϴμ�¼ʱ���Ƿ��������
    bool IsPassSunday( int64 nRecordTime );

    // ������������
    void SetOfflineType( unsigned char exitType ){ _exitType = exitType; }

    // �����������
    uint32 GetOfflineType(){ return _exitType; }

    // ��¼��ǰ�ű�ʱ�����
    void RecordNowTimeVar( int nVarID );

    // �ж�ʱ������Ƿ����һ��
    bool IsTimeVarPassOneDay( int nVarID );

    // �жϼ���������0ʱ��
    void ProcessCheckVarClearTime();

    // ����ʱ�������0
    void ProcessClearTimeVar();
	void FirstEnterWorldClearTimeVar();

	//�жϾ���ٺ»��ȡʱ���Ƿ����һ��
	void ProessClearSalary();
    ////////////////////////////////////////////////////////////////////////////////////////////////////


    void        SetNewPlayerName( const int8* newName ){ strncpy_s( _newPlayerName, sizeof(_newPlayerName), newName, sizeof(_newPlayerName)-1); }
    const int8* GetNewPlayerName() { return _newPlayerName; } // ȡ���µ�����    

    // ���ݿ�
    bool IsCanSaveToDB(); // �жϿɷ񱻱���
    bool IsSaveTime();

    // ����
    void ResetHignShoutCount( void ) { gCharInfoServer.baseinfo.liveinfo.nHighShoutCount = 0;}
    void AddCurrentHighShoutCount( int nValue ) { gCharInfoServer.baseinfo.liveinfo.nHighShoutCount += nValue; }
    int  GetCurrentHighShoutCount( void ) const { return gCharInfoServer.baseinfo.liveinfo.nHighShoutCount; }
    bool IsCanChat() { return m_bCanChat; }
    void SetCanChat(bool bCan) { m_bCanChat = bCan; }
    bool IsBanSpeak() { return m_nBanSpeakTime > 0; }
    unsigned int GetBanSpeakTime() { return m_nBanSpeakTime; }
    void SetBanSpeakTime( unsigned int dwTime, bool bSendToClient = false );

    bool IsCanHighShout();      // �Ƿ��ܸߺ�


    ////////////////////////////////////////////////////////////////////////////////////////////////////////
   
    // ��õ�ǰ�ƺ�
    short GetCurrentTitle() { return m_xTitleEx.GetCurrentTitle(); }

    // ���õ�ǰ�ƺ�
    bool SetCurrentTitle(short stTitleID) { return m_xTitleEx.SetCurrentTitle(stTitleID); }

    // �Ƿ�ӵ�гƺ�
    bool IsHaveTitle(short stTitleID) { return m_xTitleEx.IsHaveTitle(stTitleID); }

    // ��ʼ���ƺ��б�
    void InitPlayerTitleList();                 

    // ����ƺ��б�
    void SavePlayerTitleList();                
     // ��ӳƺ�
    bool AddTitle( short nTitleID );    

    // ɾ���ƺ�
    bool RemoveTitle(short nTitleID, bool bSendMessage = true );    

    // �������а�ƺ��б�
    void UpdateTitleListByDataBaseTop10(bool bSendToClient = false);                        

    // �������ͳƺ�
    void UpdateTitleListByConditionType(short nConditionType, bool bSendToClient = false);  

    // ���·���������
    void UpdatePlayerCounterByCount(short nConditionType, int nID);        

    // �Ƿ�ӵ��ĳ���ͳƺ�
    bool IsHaveTypeTitle( unsigned char uchType ){ return m_xTitleEx.IsHaveTypeTitle( uchType ); }

    // ɾ��ĳ�������гƺ�
    void RemoveTypeTitle( unsigned char uchType );

    // ���������óƺ�
    void UpdateTitleCounter();

    // ���³ƺŸ��ӵ�����
    bool UpdateBaseAttrByTitle(bool bSendToClient, unsigned short nCurrentTitleID, unsigned short nLastTitleID = TitleConfig::Init_ID, bool bRemoveLastAttr = true);

    // �������гƺŸ��ӵ�����
    bool UpdateBaseAttrByAllTitle(bool bSendToClient = false);

    // ���³ƺŸ��ӵ�ս������
    bool UpdateFightAttrByTitle(bool bSendToClient,ItemDefine::SItemStatus* pStatus, bool bIsAdd = true);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    // �����������ʱ����
    void ClearCharRunTimeData();
    
    void SetShop( CShopMgr::SShop* pShop ){ m_pstShop = pShop; }
    
    void CheckMissionAndInform(); // �������״̬����֪ͨ�ͻ���
    void AddMission(char *pVarName);
    void DelMission(char *pVarName);

    // ����
    DWORD GetTeamID() { return m_dwTeamSessionId; }
    void  SetTeamID(DWORD dwSessionId) { m_dwTeamSessionId = dwSessionId; }
    bool  HaveTeam() ;

    uint32 GetPetBreedID() { return  m_dwPetBreedId; }
    void   SetPetBreedID( uint32 ID ) { m_dwPetBreedId = ID; }

    void   SetBreedPetPrompt( bool bValue ) { m_bBreedPetPrompt = bValue; }

    unsigned long GetRecordSystemTime();
    bool IsExpired( int nVarId, int keyHour, int keyMinute, int minDuration );
    bool RecordTimeVar( int nVarId );

    virtual bool IsTeamMember(BaseCharacter *pChar);
    void TellTeamInfoChange( char positon );

    // ���ó���(������)ͬ����Ϣ
    void SetRunTimePetInfo( RunTimePetInfo& xPetInfo,MonsterBaseEx* pAiPet, int nSummonSkillID = -1, int nPetIndex = -1 );

    long ProcessSkillAboutPetModule( const ItemDefine::SItemSkill* pSkill, SAttackTarget* pTarget ); // �������г���ģ��
    long ProcessAfterIllusionModule( const ItemDefine::SItemSkill* pSkill, SAttackTarget* pTarget ); // �������о���ģ��

    bool IsInProtectLockTime() { return m_nProtectLockLeaveTime != 0; }

    // ʹ�õ���Ʒ���
    UseItemInfo& GetUseItemInfo() { return m_xUseItemInfo; }
    void SetUseItemInfo( UseItemInfo& xInfo ){ m_xUseItemInfo = xInfo; }
    bool CheckUseItemValid();
    void ShowTreasureBox();
    bool IsTreasureBoxItem( unsigned short ustItemID );

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // ��������15��
    void EnterLuckReward();

    // ��������15����Ϣ
    void UpdateLuckReward( int nType );

    // ��õ�ǰ����15�صڼ���
    int GetLuckRewardLevel( bool bCheckType = false );

    // �������15������ָ��
    LuckReward* GetLuckReward( bool bIsTeam );

    // ��ʾ����15�ؽ���
    void ShowReceiveLuckReward( LuckReward* pLuckReward, bool bIsTeam );

    // ֪ͨ�ͻ��˵������濪ʼ
    void ShowRandLuckReward( LuckReward* pLuckReward, bool bIsTeam );  

    // �����콱�߼�
    void ProcessReceiveLuckReward( LuckReward* pLuckReward, bool bIsTeam, bool bReceive );

    // ��������15��ҡ���߼�
    void RunLuckReward( LuckReward* pLuckReward, bool bIsTeam );

    // �Ƿ�������15�ػ��
    bool IsInLuckReward();         

    // ֪ͨ�ͻ��˿�ʼҡ��
    void StartLuckReward( LuckReward* pLuckReward, bool bIsTeam ); 

    // �ж��ܷ�ҡ�� 
    bool IsCanLuckReward();         

    // �ж��ܷ���һ��
    bool IsCanNextLuckLevel();     

    // �ж��ܷ������
    bool IsCanAcceptQuest( unsigned char uchLevel );   

    // �ж��Ƿ�����ȡ��Ʒ
    bool IsCanReceiveReward(); 

    // ���ÿ���ҡ��
    void SetCanLuckReward();

    // ��������15��ˢ������
    void SetLuckSummonCount( unsigned short ustCount );

    // �������15��ˢ������
    unsigned short GetLuckSummonCount();
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    // ��õ���ɱ������
    unsigned long GetRecordKillMonsterCount() { return gCharInfoServer.otherdata.dwRecordKillMonsterCount; }

    // �������ɱ������
    void ClearRecordKillMonsterCount() { gCharInfoServer.otherdata.dwRecordKillMonsterCount = 0; }

    // �ۼӵ���ɱ������
    void AddRecordKillMonsterCount( int nCount = 1 ) { gCharInfoServer.otherdata.dwRecordKillMonsterCount += nCount; }

    // �жϼ�¼ɱ��ʱ���Ƿ��Ѿ��ı�
    bool CheckRecordKillMonsterTime( unsigned short ustYear, unsigned char uchMonth, unsigned char uchDay );

    // ���ɱ�־���ϵ��
    float GetKillMonsterModulus();       
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // ������ұ�T����
    void ProcessBeBlock( uint8 type, uint32 time );

    // ���ͼ�������ͻ���
    bool ProcessSendCheckCheatData( CodeData* pCodeData, unsigned char uchCodeType );

    // ��⵽���,��������������
    bool ProcessKickByCheckCheat( unsigned int dwErrorResult );        

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // ��ʽ��������Ʒ����
    int FormatChatItemData( const MsgChat* pChatMsg, char* szData, int nLength );
    
    // ����ƷƷ�ʻ����Ʒ����
    static void ReplaceSpecifiedName( unsigned short ustLevel, Common::_tstring& tstrName );

    // ����ϵͳ��Ϣ
    void ProcessSystem( const char* szCommand, uint8 uchType, const MsgChat* pMsgChat = NULL );
    void ProcessSystem( uint8 uchType, const char* szCommand, const char* szItemHyberMem, int nItemCount = 1 );
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    // ��ʾ�ƹ�����
    void ShowPubQuestDlg( int nNpcID, int nType, const char* szInfo );

    void ShowBattleSignUpDlg( int nNpcID, int nType, const char* szInfo );

    void TellGameStage( short stTotalStage, short stStage, uint32 dwTime );
    
    uint32 GetPreSaveTime() { return m_PreSaveTime; }
    void   SetPreSaveTimeNow() { m_PreSaveTime = HQ_TimeGetTime(); }

    void CheckRemoveSecondPassword();

    uint32 GetLastUpdateTime() { return m_dwLastUpdateTime; }
    void SetLastUpdateTime( uint32 dwValue ) { m_dwLastUpdateTime = dwValue; }

    void AddTeamBattleIntegral( int nIntegral, int nKillCount, int nDeathCount, bool bSendMessage = true );

    void ProcessGuideQuest( int nType );    // �������������߼�

    // ������ﵱǰ��ͼ
    MapConfig::MapData* GetMapData() const { return m_pMapData; }

    // ��������ǰ��ͼ
    void SetMapData( MapConfig::MapData* pMapData ) { m_pMapData = pMapData; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // ��õ�ǰ��Ǯ
    uint32 GetMoney() const { return gCharInfoServer.baseinfo.liveinfo.dwMoney; }

    // ��ý�ɫ��Я��������Ǯ
    uint32 GetMaxMoney();     

    // ����Ƿ��ܸ���ɫ��ӽ�Ǯ
    bool CheckCanAddMoney( DWORD dwAddMoney );

    // ��Ǯ����
    void OperateMoney( uint8 uchOperateType, uint32 nValue, bool bSendMessage, char* szFunction, int nLine,int16 sourcetype );

    // ��õ�ǰ��������
    uint32 GetJiaoZi() const { return gCharInfoServer.baseinfo.liveinfo.jiaoZi; }

    // ��ý��� �� ��Ǯ����
    uint32 GetJiaoZiMoney() const { return GetMoney() + GetJiaoZi(); }

    // �������� ����
    void OperateJiaoZi( uint8 uchOperateType, uint32 nValue, bool bSendMessage, char* szFunction, int nLine ,int16 sourcetype);

    // ��ý�ɫ��Я���������
    uint32 GetMaxJiaoZi();    

    // ����Ƿ��ܸ���ɫ��ӽ���
    bool CheckCanAddJiaoZi( DWORD dwAddJiaoZi );

    // ��ý�
    uint32 GetJinDing() const { return gCharInfoServer.baseinfo.liveinfo.jinDing; }

    // �𶧲��� Ԫ��
    void OperateJinDing( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype,bool bSyncToDB = true); 

	//����̳ǻ���
	uint32 GetConsumeScore() const {return gCharInfoServer.baseinfo.liveinfo.ConsumeScore ;}

	//�̳ǻ��ֲ��� �̳ǻ���
	 void OperateConsumeScore( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype,bool bSyncToDB = true); 

    // ��ý�Ʊ����
    uint32 GetJinPiao() const { return gCharInfoServer.baseinfo.liveinfo.jinPiao; }

    // ��Ʊ���� ���
    void OperateJinPiao( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine ,int16 sourcetype); 
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    // �������
    uint32 GetRecordReliveTime(){ return gCharInfoServer.baseinfo.liveinfo.nRecordReliveTime; }
    uint8  GetReliveCount() { return gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount;  }
    bool   IsCanFreeRelive();
    
    // �ɾ�
    uint32 GetAchievePoint() { return gCharInfoServer.achieveData.achievePoint; }
    void   AddAchievePoint( uint32 nPoint ) { gCharInfoServer.achieveData.achievePoint += nPoint; }

    // ����
    uint32 GetDaoxing()  { return gCharInfoServer.baseinfo.liveinfo.daoxing;  }
    void   OperateDaoxing( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine );

    // ���� 
    uint32 GetHonour() const    { return gCharInfoServer.baseinfo.liveinfo.honour;  }
    uint32 GetHonourRecord()    { return gCharInfoServer.otherdata.nRecordHonourCount; }
    uint32 GetHonourRecordTime(){ return gCharInfoServer.otherdata.nRecordHonourTime;  }
    void   ClearHonourRecord()  { gCharInfoServer.otherdata.nRecordHonourCount = 0; }
    void OperateHonour( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype );

    // ��ѫ
    uint32 GetExploit() const { return gCharInfoServer.baseinfo.liveinfo.exploit; }
    void OperateExploit( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype );

    // ����
    uint32 GetReputation() const { return gCharInfoServer.baseinfo.liveinfo.reputation; }
    void OperateReputation( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine ,int16 sourcetype );

    // ��������
    uint32 GetEctypeScore(){ return gCharInfoServer.baseinfo.liveinfo.battleScore; }
    void OperateEctypeScore( uint8 uchOperateType, uint32 nValue );

    // ��ս����
    uint32 GetCountryScore() { return gCharInfoServer.baseinfo.liveinfo.dwCountryScore; }
    void OperateCountryScore( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine );
    void OperateTeamCountryScore( uint8 uchOperateType, uint32 nValue );

    // �����������ʱ��
    void  SetProtectTime( DWORD dwValue ) { dwProtectTime = dwValue;}        
    DWORD GetProtectTime() const { return dwProtectTime; }

    void SetClearDuelFight (bool bValue) { m_bIsClearDuelFight = bValue; }
    bool GetClearDuelFight () { return m_bIsClearDuelFight; }

    void SetDuelFightLoser( GameObjectId nID) { m_nDuelFightLoser = nID; }
    GameObjectId GetDuelFightLoser() { return m_nDuelFightLoser; }

	//��ù���ID
	int GetCountryId()
	{
		return gCharInfoServer.baseinfo.aptotic.ucCountry;
	}
	void SetCountryId( int uchCountry )
	{
		gCharInfoServer.baseinfo.aptotic.ucCountry = uchCountry;
		if ( gCharInfoServer.baseinfo.aptotic.ucCountry < 0 || gCharInfoServer.baseinfo.aptotic.ucCountry > 3)
		{
			gCharInfoServer.baseinfo.aptotic.ucCountry = 0;
		}
		TellClientCountryID();
		HandlePlayerCountryBuff();//���������ͱ仯��ʱ�� �������BUFF
	}
	
	void TellClientCountryID();

	//̫ƽ�þ��ȼ�
	char GetTPHJRank()
	{
		return gCharInfoServer.baseinfo.liveinfo.TPHJRank;
	}
	void SetTPHJRank(char value,int operType=EOT_Set)
	{
		switch (operType)
		{
		case EOT_Set:			//ֱ�Ӹ�ֵ
			gCharInfoServer.baseinfo.liveinfo.TPHJRank = value;
			break;
		case EOT_Add:			//+
			gCharInfoServer.baseinfo.liveinfo.TPHJRank = gCharInfoServer.baseinfo.liveinfo.TPHJRank+value;
			break;
		case EOT_Sub:			//-
			gCharInfoServer.baseinfo.liveinfo.TPHJRank = gCharInfoServer.baseinfo.liveinfo.TPHJRank-value;
			break;
		case EOT_Mul:			//*
			gCharInfoServer.baseinfo.liveinfo.TPHJRank = gCharInfoServer.baseinfo.liveinfo.TPHJRank*value;
			break;
		case EOT_Div:			// /
			if (value!=0)
			{
				gCharInfoServer.baseinfo.liveinfo.TPHJRank = gCharInfoServer.baseinfo.liveinfo.TPHJRank/value;
			}
			break;
		}
		if (gCharInfoServer.baseinfo.liveinfo.TPHJRank<0)
		{
			gCharInfoServer.baseinfo.liveinfo.TPHJRank = 0;
		}
		TellClientTPHJRank();
	}
	void TellClientTPHJRank();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // �����л���ĳ����ͼ
    bool FlyToMapReq(DWORD iMapID, float x, float y, float dir, bool bCheckCanFly = true );   
	void ReviceByFlyToMap();

	void CheckIsNeedLeaveTeam();
private:
    // �л���ĳ����ͼ��ʵ���߼�
    bool FlyToMapAction( DWORD iMapID, int nTileX, int nTileY, float dir );

	// �л�����ͼ��ʵ���߼�
    bool ChangeToMap( GameStage* pGameStage, int nTileX, int nTileY, float dir, const char* szFile, uint32 line );

	// �л���������ͼ��ʵ���߼�
    bool FlyToEctypeMapAction( DWORD iMapID, int nTileX, int nTileY, float dir );

	bool IsCanFlyToMapAction(DWORD iMapID, int nTileX, int nTileY, float dir,DWORD& dwMapDataId,unsigned short& ustLevel,uint32& dwEctypeMapID,DWORD& dwReserveValue);

	void SetClientShowMapTimeStep(bool IsOpen,uint32 TimeStep);

	void StartChangeServerTimer(uint32 TimeStep);
public:
    // �����л�����ͼǰ��������Դ�߼�
    void ProcessChangeToMap();

    // ���ö����л�����
    void SetChangeStageType( uint8 nValue ) { m_nChangeStageType = nValue; }

    // ���õȴ��л���ͼ
    void SetWaitChangeStage( uint8 uchType, uint32 nMapID, float fX, float fY, float fDir, uint32 nSpaceTime, bool bSendMessage );
    
    // ����ȴ��л���ͼ�߼�
    void ProcessWaitChangeStage();

    // �����л���ͼ��, ��Դ׼���߼�
    void ProcessChangeMap( bool lastEnterState );

    // �����л���ͼ�� ֪ͨ�ͻ�����Ϣ
    void ProcessChangeMapMsg( bool bFirstEnterGameServer );

    // �����л���ͼ��Ӫ��Ϣ�仯
    void ProcessChangeMapFightCamp(bool bFirstEnterGameServer);
	void ProcessChangeMapFightGame(bool bFirstEnterGameServer);

    // ��һ�ν�����Ϸ����
    void FirstEnterGameWorld( char* szMacAddress );

    // ��һ�ν�����Ϸ������
    void FirstEnterGameServer( char* szMacAddress );

    // �뿪��Ϸ������
    void PlayerExitGameServer( unsigned char exitType );

    // ��ҽ����ͼ
    void ProcessMapLoaded( bool bFirstEnterGameServer );

    void ProcessSummonObjectEnterGameServer();

    // �����л���ͼ
    void ProcessSummonObjectChangeMap( GameObjectId objectId );

    // ������Ϸ��鲢������ҵ�ͼ��Ϣ
    void CheckEnterWorldMapID( DBMsgAckEnterWorld* pEnterWord, DWORD& dwMapID, int& nMapX, int& nMapY );

    // �ɵ�ĳ������
    bool FlyToPlayer( int nType );

    // ���볡��
    void OnEnterStage();

    // �뿪����
    void OnLeaveStage();

    // �Ƿ�����л���ͼ
    uint8 GetChangeStageType() const { return m_nChangeStageType; }

    // �ж�����ȼ��Ƿ�С�ڵ�ͼ�ȼ�
    bool IsLessThenMapLevel( uint32 nMapID );

    // �ж��Ƿ��ܴӵ��������
    bool CheckPunishHell( uint32 nMapID );

	bool CheckFlyToJianYu(uint32 nMapID);

    // �ж��Ƿ��ڳ������ͼ
    bool IsInBornMap();
    
    // ���߾�����ͼID
    void CorrectMapID(); 

    // ���㸱����ͼ�ȼ�
    unsigned short GetPlayerEctypeMapLevel( uint32 nMapID, float fX, float fY, uint8 nMapType );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
    friend class CFileDB;

    virtual void _OnHPChanged( float underPercent ); // HP�ı�ʱ��������
    virtual void _OnMPChanged( float underPercent ); // MP�ı�ʱ��������

    void InitCharacter( const SCharDBInfo& dbSaveInfo, const SRuntimeInfo& dbRunInfo  ); // ��ʼ����������
    void UpdateCommonData( unsigned char bForSaveDb ); // ������ֵ bDeriveToCommon true���������ൽ������� false���������������

    void SendTipVar();   // ��ʾ����
    void SendRealTime(); // ������ʱ��
  
    void SetAttackLockCharState( bool bAttack ) { m_bAttackLockChar = bAttack ; } // �Ƿ�ʼ����������Ŀ��

    void OnMsgReqSkillIdToClient(unsigned short ustSkillID);

    //void TryAttackLockChar();                   // ��������Ŀ��
    long TryNormalAttack();                     // ��
    void _ProcessSwitchGameServerRuntimeInfo(); // �����з�����ʱ����������ʱ����

    void _RefreshEnergyAbout( DWORD dwCostTime ); // ˢ�»���ֵ
    void _RefreshVigorAbout ( DWORD dwCostTime ); // ˢ�¾���ֵ

    // ����
    bool ResetItemTime( SCharItem *pItem );
    int CalcGuildQuestReleaseRewardModulus( int nQuestID );

    long DistanceNowTime( unsigned char year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute );

    //����
    void    SetCurActionId( uint16 nActionId ) { m_nCurActionId = nActionId ; }
    uint16  GetCurActionId() { return m_nCurActionId; }

    void    SetCurActionPlayTime( uint32 nPlayTime ) { m_nCurActionPlayTime = nPlayTime + HQ_TimeGetTime() ; }
    uint32  GetCurActionPlayTime() 
    { 
        if ( m_nCurActionPlayTime > HQ_TimeGetTime() )
        { 
            return  m_nCurActionPlayTime - HQ_TimeGetTime(); 
        }

        return 0; 
    }

    void    SetFlyMoving( bool bFly ) { m_bIsFlyMoving = bFly; }
    bool    IsFlyMoving() { return m_bIsFlyMoving; }

    // �Ƿ��ھ����һ�
    bool IsBeginVigorOfflineFight();

    // �Ƿ���Ծ����һ�
    bool IsCanVigorOfflineFight();

    // ��ǰ�¼�
    uint16	GetCurEventID() { return m_nCurEventID; }
    void	SetCurEventID( uint16 nValue ) { m_nCurEventID = nValue; }

	// ��ü���ָ��
	GameFamily* GetFamily();

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // ʹ��ҩƷ
    bool UseRestoreItem( ItemDefine::SItemRestore* pRestore, int bagIndex, BaseCharacter* target );

    // ���±���ҩƷ��ֵ
    void UpdateRestoreItemValue( ItemDefine::SItemRestore* pRestore, int bagIndex );
    
    // ���ָ��Ŀ���Ƿ���ʹ����Ʒ
    BaseCharacter* GetTargetCanUseGood(GameObjectId ustCharId,unsigned short ustTargetType,unsigned short ustItemID);

    // ������ʹ����Ʒ
    void _ProcessUseItemToMount( MsgUseGoodsToMount* pUseGoodsToMount, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );
    void _ProcessUseRestoreItemToMount( MsgUseGoodsToMount* pUseGoodsToMount, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );
    void _ProcessUseReelItemToMount   ( MsgUseGoodsToMount* pUseGoodsToMount, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );

    // �Գ���ʹ����Ʒ
    void _ProcessUseItemToPet( MsgUseGoodsToPet* pUseGoodsToPet, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );
    void _ProcessUseRestoreItemToPet( MsgUseGoodsToPet* pUseGoodsToPet, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );
    void _ProcessUseReelItemToPet( MsgUseGoodsToPet* pUseGoodsToPet, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemCommonConfig );

    // �Խ�ɫʹ����Ʒ
    void _ProcessUseItemToChar( MsgUseGoods* pUseGoods, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig ); 
    void _ProcessUseRestoreItemToChar( MsgUseGoods* pUseGoods, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig ); 
    bool _ProcessUsePetIdentifyItemToChar( MsgUseGoods* pUseGoods, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );

    // �Ժ���ʹ����Ʒ
    void _ProcessUseItemToFriend( MsgUseGoods* pUseGoods, ItemBag* pItemBag, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void _ProcessRefreshProtectTime ( uint32 dwCurTime );

    void _ProcessRefreshProtectChar ( uint32 dwCurTime );

    void _ProcessRefreshRestore     ( uint32 dwCurTime );

    void _ProcessCurrentAction      ( uint32 dwCurTime );

    void _ProcessDoubleExpTime      ( uint32 dwCurTime );

    void _ProcessLongIntervalTimer  ( uint32 dwCurTime );
    
    //////////////////////////////////////////////////////////////////////////

    // ������Ϸ������LOG
    void EnterGameServerLog( char* szMacAddress );

    // �뿪��Ϸ������LOG
    void ExitGameServerLog();

    // �������LOG
    void LogCharData( bool bExit = true );

    // ��ҽ��뱳����ƷLOG
    void LogForBagItem(int nBagType, SCharItem *pPackItem, int iBagSize,bool bIsDbCome = true);

    // ����˳���Ϸ������ƷLOG
    void LogBagItemByExit(int nBagType, SCharItem *pPackItem, int iBagSize);

    // ��ҽ�����Ϸ����װ��LOG
    void LogForPlayerVisual(SCharItem* pVisualItem);

    // ����˳���Ϸ����װ��LOG
    void LogForPlayerVisualByExit(SCharItem* pVisualItem);

    // �����������LOG
    void LogOtherBagItem(SCharOtherData *pOtherData,bool bIsInWorld);

    // ������ƷLOG
    void LogItem(SCharItem* pCharItem,int nStringIndex);

    // �ֿ�LOG
    void LogStorage();

    // ����LOG
    void LogMountData();

    // ��������������
    void ClearEspecialItemCounter() { _itemCounter.clear(); }

    // ���ָ����������
    void AddEspecialItemCounter( uint16 itemId, uint32 itemCount);

    // ָ������LOG
    void LogEspecialItemCounter();

    // ���ÿ�ʼ�ֽ׶η�����Ϣ
    void StartSendOnLineMessaage();

    // �������߷ֶη�����Ϣ
    void ProcessSendOnLineMessage( uint32 nCurrentTime );

    //////////////////////////////////////////////////////////////////////////////////
    // ��½��ʼ
    void StatusLoginStart();     

    // ��Ĭ�ϸı䵽�����ֵ�ȴ��ͻ��˷��͹�����֤��Ϣ
    void StatusLoginCheck();   
    // �յ���¼
    void StatusLoginLogin();    

    // �ȴ�����
    void StatusLoginWaitDBRet();

    // ����Ϣת�������ݿ�
    void StatusLoginLoginToDB(); 

    // ����Ϣת�������ݿ�
    void StatusLoginDBLoginED(); 

//////////////////////////////////////////////////////////////////////////
#include "PlayerMessageHandle.h"
#include "PlayerCommandModule.h"
#include "PlayerScriptModule.h"
#include "PlayerEnmityModule.h"
#include "CountryPlayerHandle.h"
#include "RelationPlayerHandle.h"
#include "GuildPlayerHandle.h"
#include "StallPlayerHandle.h"
#include "ConsignmentPlayerHandle.h"
#include "PlayerSpecialQuestModule.h"
#include "GamePlayerEquipEvolve.h"
#include "BargainingPlayerHandle.h"
#include "PasswordPlayerHandle.h"
#include "CampBattlePlayerHandle.h"
#include "PlayerBuffEvent.h"
#include "PlayerPKModule.h"
#include "PlayerSummonPetModule.h"
#include "PlayerQuestModule.h"
#include "FamilyPlayerHandle.h"
//xuda #include "WantedPlayerHandle.h"
#include "QuestEntrustPlayerHandle.h"
#include "GameBattlePlayerHandle.h"
#include "CSAuthPlayerMessageHandle.h"
//////////////////////////////////////////////////////////////////////////
// ������
#include "PlayerAntiAddictionModule.h"

public: // ����
    SDBInfo                   m_dbinfo;
    SCharDBInfo               gCharInfoServer; 
    SRuntimeInfo              gTransferRuntimeInfo; // ��ת����������ʱ����
    ItemBag                   _NormalItemBag;       // ���߱���
    ItemBag                   _MaterialItemBag;     // ���ϱ���
    ItemBag                   _TaskItemBag;         // ���񱳰�
    SkillBag                  _SkillBag;            // ���＼�ܱ���
	SkillBag				  _HeroSkillBag;		// �������ܱ���
    SCharStorageData          _StorageBag;          // �ֿⱳ��
    XinFaManager              _XinFaManager;        // �ķ�����
    SuitManager< GamePlayer > _suitManager;         // ��װ����
    MountManager              _mountManager;        // �������
    PetManager                _petManager;          // �������
    AchieveServerManager      _achieveManager;      // �ɾ͹���
    RecipeManager             _recipeManager;       // ��������
    GraphicCodeManager        _graphicCodeManager;  // ��֤��
    ActionWatchManager        _actionManager;       // ��Ϊ��ع���
    MailPlayerManager         _mailManager;         // ����ʼ�����
	SevenDayManager			  _sevenDayManager;		// ����7���ֹ���
	#ifdef NPGUARD
	CSAuthManager			  _authManager;
	#endif
    bool                      m_bStorageDBFlag;         // �ֿ��ѯ��־ �ֿ��Ƿ񱻴򿪹�
    bool                      m_bInDuelReq;             // �Ƿ��ڵȴ��д�ظ�
    clock_t                   m_tmChatCoolDownTime;     // ��¼9���񺰻���ʱ��
    unsigned long             m_dwLastEnterWorldReqTime;// ���µ����������Ϸ�����ʱ��
    int                       m_nProtectLockLeaveTime;  // ����������ʣ��ʱ��
    unsigned int              m_nBanSpeakTime;          // ����ʱ��

    SCharBaseAttr             addSubBaseAttr;                                   // ��¼������������
    SCharAttributeUpdate      lastFightAttr;                                    // ��¼��һ�ε�ս������
    bool                      fightAttrChangeRecord[CharAttr_AttributMaxCount]; // ��¼��һ�ε�ս����!�Ա仯���

    float                     m_fChangeExpPer;      // ����ı仯��
    float                     m_fChangeSkillExpPer; // ���ܾ���ı仯��
    bool                      m_bIsOpenDoubleExp;   // �Ƿ����˫������

    // for debug
    bool bAlwayCritical; // �Ƿ����Ǳ���
    bool bShowFightInfo; // �Ƿ���ʾս����Ϣ

protected: // ����
    __int64                _SessionKey;
    char                m_szLoginName[ dr_MaxNameString ];
    char                m_szLoginIP[ dr_MaxNameString ];
    GameObjectId       m_ProtectCharID;         // Ҫ���������ID
    int                 m_nProtectCharMonsterId; // Ҫ��������Ĺ�����е�Id
    short               m_stMeAddStatus         [ EEquipPartType_MaxEquitPart ]; // װ��bufferStatus
    short               m_stMeAddStatusLvl      [ EEquipPartType_MaxEquitPart ];
    short               m_stDstAddStatus        [ EEquipPartType_MaxEquitPart ];
    short               m_stDstAddStatusLvl     [ EEquipPartType_MaxEquitPart ];
    float               m_fDstStatusRate        [ EEquipPartType_MaxEquitPart ];
    float               m_fMeStatusRate         [ EEquipPartType_MaxEquitPart ];  
    int8                m_nMeAddStatusTrigger   [ EEquipPartType_MaxEquitPart ];
    int8                m_nDstAddStatusTrigger  [ EEquipPartType_MaxEquitPart ];
    uint32              m_PreSaveTime;                  // �ϴα����ʱ��,�����Զ���������
    int                 m_nReliveOriginAllHpMp;         // ��������RMB
    bool                m_bIsStatusChangeHpMpMax;       // �Ƿ�Ϊ״̬�����ı�HP MP ���ֵ
    bool                m_bIsClearDuelFight;            // �Ƿ����������Ϣ
    GameObjectId       m_nDuelFightLoser;             // ������ʤ���ID

protected:
    // ��ͼ��������
    bool                _bWantSwitchGameWaitSaveInfoOk; // �Ƿ����ڵȴ��з������������
    MsgSwitchGate       _GateInfo;                      // �з�������GateServer����Ϣ
    short               m_stGateID;                     // ��ɫλ�ڵ�GateID
    bool                _bFirstEnterGameServer;         // �Ƿ��ǵ�һ�ν�����̨GameServer
    bool                _bFirstEnterWorld;              // �Ƿ��һ�ν�����Ϸ����
    std::string         _strIp;                         // ���ip
    bool                _bInLoginStage;                 // �Ƿ���LoginStage��, �չ�������,Ĭ�϶���

    int                 m_nCurZoneID;
    //bool                m_bInPrivateShopZone;   

protected:
    // �ű����
    VMScriptContainer   m_lsScript;
    unsigned long       m_dwScriptSleep;
    unsigned long       m_dwScriptSleepStartTime;
    int                 m_nTempVars[More_iMaxTempVars]; // ��ʱ�ű�����
    int                 m_nScriptNpcId;                 // �����NpcObjectId

protected:
    // ʱ�����
    unsigned int        m_nOfflineTime;
    unsigned char       _exitType;                      // �˳�����
    //unsigned int        m_nEnterTime;                   // ������Ϸʱ��
	__int64             _nEnterRealTime;                // ������Ϸ����ʵʱ��
    
    BOOL                m_bAttackLockChar;
    RestoreColdDown     m_RestoreColdDown;
    int                 m_nDstPlayerId;
    DWORD               m_dwLastDoRideTime;
    DWORD               m_dwLastHintMessageSendTime;    // ��ʾ��Ϣ���͵����ʱ��
    DWORD               m_dwReqShopTime;
    unsigned long       _accumulateEneryTime;           // �������µ��ۼ�ʱ��
    unsigned long       _accumulateVigorTime;           // �������µ��ۼ�ʱ��
    CShopMgr::SShop*    m_pstShop;
    TitleEx             m_xTitleEx;                     // �ƺ�
    DWORD               m_dwLastChatTime;
    MsgEnterWorld       _msgEnterWorldCache;
    UseItemInfo         m_xUseItemInfo;
    uint32              _blockTime;                     // ����blockʱ��
    uint32              dwCharSaveDelay;
    DWORD               m_dwTeamSessionId;              // ��ӵ�seesionid   0 ��ʾû��
    uint32              m_dwLastUpdateTime;
    uint32              m_dwExpressionTime;             // ��һ�η��ͱ����ʱ��
    uint32              m_dwPetBreedId;                 // ���ﷱֳID
    bool                m_bBreedPetPrompt;              // ���ﷱֳ��ʾ

    BuyBackPack< SCharItem >   m_xBuyBackItem;              // ��Ҫ�ع�����Ʒ
    int8                       _newPlayerName[dr_MaxPlayerName];

    typedef std::map<uint16, uint32>       ItemCounterContainer;
    typedef ItemCounterContainer::iterator ItrItemCounterContainer;
    ItemCounterContainer                   _itemCounter;    //������߼���,�����ռ���ɫ���ϵ�ĳЩ��Ʒ��������Ϣ

    MapConfig::MapData* m_pMapData;
    //////////////////////////////////////////////////////////////////////////////
    DWORD           dwProtectTime;          // �������ܱ�����ʱ��
    uint32          m_dwCheckProtectTimePer;

    uint8           m_nChangeStageType;     // �Ƿ����һ���л���ͼ
    WaitChangeStage m_xWaitChangeStage;     // �ȴ��л���ͼ
    GameTimerEx     m_xChangeServerTimer;   // �л�������Timer;

    ///////////////////////////////////////////////////////////////////////////////
    unsigned char m_uchSendOnLineMessageStatus;  // ��һ������ ��Ϣ�ֶη��ͽ׶�   
    GameTimerEx m_xSendOnLineMessageTimer;       // ��һ������ ��Ϣ�ֶη��Ͷ�ʱ��

    unsigned int m_nVarClearTime;                // ��¼ʱ���Ƿ����12��    
    GameTimerEx m_xVarClearTimer;                // ������ʱ��

    SkillItemRelive m_xSkillItemRelive;          // ������Ʒ����
    
    //  ����Ŀǰ����״̬���
    int     m_nDromeId          ;   // ����ID
	uint16	m_nMountLevel		;	// ����ȼ�
    uint8   m_nDromePos         ;   // ��λ
    GameObjectId  m_nDriverId   ;   // ��ʻԱID
    uint16  m_nCurActionId      ;   // ��ǰ����
    uint32  m_nCurActionPlayTime;   // ��ǰ��������ʱ��
    GameObjectId m_nBigShipId   ;   // �������Id
    uint8   m_nNpcShipPos       ;   // �������λ��
    bool    m_bMoving           ;   // ���ƶ���
    bool    m_bIsFlyMoving      ;   // �Ƿ����
    uint16	m_nCurEventID		;	// ��Ҫ�㲥���¼�ID

    GameTimerEx _offlineFightTime;  //
	bool        _bGetWallowInfo; // �Ƿ�õ��˷���������Ҫ������ ��DB

	// �Ƿ��Ǳ����ڳ�״̬
	bool      mBiaocheState;
	float     m_BiaoCheSpeed;//�ڳ��ٶ�
	//�ܹ����Ի�õľ���
	__int64		ulCanTakeExp;

public:
	///////////////////san guo add:///////////////////////////////
	void SetHeroId( uint16 hero_id)
	{
		gCharInfoServer.baseinfo.liveinfo.hero_id = hero_id;
	}
	void ClearHeroId()
	{
		gCharInfoServer.baseinfo.liveinfo.hero_id = INVALID_HERO_ID;
	}
	uint16 GetHeroId(){return gCharInfoServer.baseinfo.liveinfo.hero_id;}

	//̫ƽ�þ�
	void SetMapID_TPHJ(DWORD map_id)
	{
		gCharInfoServer.otherdata.sBornPos.dwMapID = map_id;
	}
	void SetPrePosition_TPHJ(D3DXVECTOR3 pos)
	{
		gCharInfoServer.otherdata.sBornPos.vPos = pos;
	}

	bool IsBiaocheState() const { return mBiaocheState; }

	void RefreshHeroAttr();
	void RefreshHeroSkill();
	void RefreshMountAttr(bool IsInit = false);
	void RefreshLieutenantAttr(bool IsDoPet);//ˢ�¸�������ҵ�����
	void GetHeroAddAttr(SCharHeroInfo* pHeroAddAttr);
	//bool ApplyHeroPassiveSkillEffect();

	void ApplyPetAttrToChar(ItemDefine::SItemSkill* pPetSkill,bool bCancelApply);

	//�����̫ƽ�þ��˳���Ϸ
	void ProcessExitGameInTPHJ(DBMsgSaveCharacter& msg);

	__int64 GetCanTakeExp(){return ulCanTakeExp;}
	void CalcCanTakeExp();        //������Ի�õ���߾���
	void SendLevelLimitInfo();    //����ȫ���ķ�ӡ���ݸ��ͻ���
	void CheckToSendAddLimitPlayerCount();

	bool UnBindBagEquip(__int64 bagEquipGuid);
	//������ҵĹ��ҷ���Ĵ���
	void HandlePlayerCountryInfo();
	void HandleGuildSQ();
	void SetPlayerCountryPosition(uint8 Position);
	void SendProcessTimeToClient(int StringID,int TimeStep);
	void UpdateMountWrongData(SMountItem* mount);
	void SetPetDuration(int Value);
	int	 GetPetDuration();
	void OnUpdatePetExp();
	void SetPetMode(__int64 PetGuID,uint32 ModeID,int LastTime = -1);
	void AddCard(short stCardID, short stLevel);
	bool SetCardAchieve(int nachID);

	void TriggerSevenDays();
	int  AddFriendPoint(int Distance , int FriendlyPoint);
	void OnHandleScriptStates();
	void SetScriptStatesID(unsigned short Type =  EScriptStates_Init){m_ScriptStatesID = Type;}

	void ClearGetSalary();

	int GetTodayHuntingCount() { return gCharInfoServer.otherdata.sHunting.nCount; }
	void OperateHuntingCount( int nType, int nValue );
	void DoneHuntingQuest( int nQuestId );
private:
	int64		m_DeadPetID;
	DWORD		m_PetExpUpdateLog;
	unsigned char	m_ScriptStatesID;//��ǰ�ű�ִ��״̬ �ޱ�ʾΪ0 ���ű�������ʱ�� �Զ���ԭΪ0 ����״̬�ɽű��Զ�����
	bool		m_IsCanDead;
	DWORD		m_LogTime;
	uint32		m_LogTeamID;

	bool		m_IsGameBattle;
public:
	void		OnRoleOnLineQuestEntrustHandle();
private:
	void		SendChangeEquipErrorInfo();
private:
	void		UpdataThreeDayInfo();

private:
	unsigned int m_YuanBaoTotle;
	unsigned int m_YuanBaoStates;
public:
	unsigned int GetYuanBaoStates(){return m_YuanBaoStates;}
	void SetYuanBaoStates(unsigned int Value){m_YuanBaoStates = Value;}

	unsigned int GetYuanBaoTotle(){return m_YuanBaoTotle;}
	void SetYuanBaoTotle(unsigned int Value){m_YuanBaoTotle = Value;}

	bool IsInBattleMap();

	bool ChangeMountStarLevel(__int64 MountOnlyID,unsigned int StarLevel,bool IsMoveLevel= false);

	void HandlePlayerCountryBuff();

	void SendLeaveExpInfo();
	void GetLeaveExp();
};

//////////////////////////////////////////////////////////////////////////
// inline
inline SBaseAttrType* GamePlayer::GetBaseAttr( uint8 nWhich)
{
    if (nWhich < 0||nWhich >EBaseAttr_MaxSize)
    { return NULL; }
    return &gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[nWhich];
}

inline SBaseAttrType* GamePlayer::GetAddSubBaseAttr( uint8 nWhich )
{
    if (nWhich < 0||nWhich >EBaseAttr_MaxSize)
    { return NULL; }
    return &addSubBaseAttr.baseAttrValue[nWhich];
}

inline void GamePlayer::SetCharAllBaseAttributeBase(int16* atttrBaseArray, int nSize)
{
    for( int i=0; i<nSize; ++i)
    { GetBaseAttr(i)->base = *(atttrBaseArray + i); }
}

inline SCharItem* GamePlayer::GetVisualEquipItem( uint8 stPart )
{
    if (stPart < 0 || stPart >= EEquipPartType_MaxEquitPart)
    { return NULL; }
    
    SCharItem* pCharItem = gCharInfoServer.visual.GetVisual(stPart);
    if ( NULL == pCharItem)
    { return NULL; }

    if ( pCharItem->itembaseinfo.ustItemID == InvalidLogicNumber || pCharItem->itembaseinfo.nOnlyInt == InvalidLogicNumber )
    { return NULL; }
    return pCharItem;
}

inline SCharItem*  GamePlayer::GetTalismanItem()
{
    SCharItem* pCharItem = &gCharInfoServer.visual.talisman;
    if ( NULL == pCharItem)
    { return NULL; }

    if ( pCharItem->itembaseinfo.ustItemID == InvalidLogicNumber || pCharItem->itembaseinfo.nOnlyInt == InvalidLogicNumber )
    { return NULL; }

    return pCharItem;
}

inline void GamePlayer::SetTalismanItem( SCharItem* pCharItem )
{
    if (pCharItem == NULL)
    { return ; }

    gCharInfoServer.visual.talisman = *pCharItem;
}

inline void GamePlayer::DeleteVisualEquipItem( uint8 stPart )
{
    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction ) )
    { return;}  // �Ʋ��������޷�ж��װ����ɾ��װ��

	if(CS_INTONATE == GetStatus())
	{
		//����״̬�޷��л�װ��
		SendChangeEquipErrorInfo();
		return;
	}

    if ( stPart >= EEquipPartType_MaxEquitPart)
    { return; }

    SCharItem* pCharItem = gCharInfoServer.visual.GetVisual(stPart);
    if ( NULL == pCharItem)
    { return; }

    pCharItem->itembaseinfo.ustItemID  = InvalidLogicNumber;
    pCharItem->itembaseinfo.nOnlyInt   = InvalidLogicNumber;
}

inline void GamePlayer::DeleteTalismanItem()
{
    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction ) )
    { return;}  // �Ʋ��������޷�ж��װ��

	if(CS_INTONATE == GetStatus())
	{
		//����״̬�޷��л�װ��
		SendChangeEquipErrorInfo();
		return;
	}

    SCharItem* pCharItem = GetTalismanItem();
    if ( NULL == pCharItem)
    { return; }

    pCharItem->itembaseinfo.ustItemID  = InvalidLogicNumber;
    pCharItem->itembaseinfo.nOnlyInt   = InvalidLogicNumber;
}

inline short GamePlayer::GetMeAddStatus( int i )
{
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_stMeAddStatus[i];
    return -1;
}

inline short GamePlayer::GetMeAddStatusLvl( int i )
{
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_stMeAddStatusLvl[i];
    return -1;
}

inline short GamePlayer::GetDstAddStatus( int i )
{
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_stDstAddStatus[i];
    return -1;
}

inline short GamePlayer::GetDstAddStatusLvl( int i )
{
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_stDstAddStatusLvl[i];
    return -1;
}

inline float GamePlayer::GetDstStatusRate( int i )
{
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_fDstStatusRate[i];
    return 0.0f;
}

inline float GamePlayer::GetMeStatusRate( int i )
{    
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_fMeStatusRate[i];
    return 0.0f;
}

inline int8 GamePlayer::GetDstAddStatusTrigger( int i )
{    
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_nDstAddStatusTrigger[i];
    return 0;
}

inline int8 GamePlayer::GetMeAddStatusTrigger( int i )
{    
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_nMeAddStatusTrigger[i];
    return 0;
}

inline void GamePlayer::SetXP( int xp )
{ 
    gCharInfoServer.baseinfo.liveinfo.nXp = xp;
    if ( gCharInfoServer.baseinfo.liveinfo.nXp < 0 )
    { gCharInfoServer.baseinfo.liveinfo.nXp = 0; }

    if ( gCharInfoServer.baseinfo.liveinfo.nXp > DEF_CHAR_XP_LIMIT )
    { gCharInfoServer.baseinfo.liveinfo.nXp = DEF_CHAR_XP_LIMIT; }
}

inline SCharItem* GamePlayer::GetNormalBagPointerByIndex( int nIndex )
{
    if ( nIndex < 0 || nIndex >= ITEM_BAGMAX || nIndex >= GetNormalBagSize() )
        return NULL;

    return &gCharInfoServer.itemData.stPackItems[nIndex];
}

inline SCharItem* GamePlayer::GetMaterialBagPointerByIndex( int nIndex )
{
    if ( nIndex < 0 || nIndex >= ITEM_BAGMATERIAL_MAX || nIndex >= GetMaterialBagSize() )
        return NULL;

    return &gCharInfoServer.itemData.ciMaterialItems[nIndex];
}

inline SCharItem* GamePlayer::GetTaskBagPointerByIndex( int nIndex )
{
    if ( nIndex < 0 || nIndex >= ITEM_BAGTASK_MAX || nIndex >= GetTaskBagSize() )
        return NULL;

    return &gCharInfoServer.itemData.ciTaskItems[nIndex];
}

inline void GamePlayer::SetEquip( uint8 part, const SCharItem& rItem )
{        
    if( part >= EEquipPartType_MaxEquitPart )
    { return; }

	if(CS_INTONATE == GetStatus())
	{
		//����״̬�޷��л�װ��
		SendChangeEquipErrorInfo();
		return;
	}
 
    SCharItem* pCharItem = gCharInfoServer.visual.GetVisual( part );
    if ( pCharItem == NULL )
    { return; }

    *pCharItem = rItem;
}

inline unsigned short GamePlayer::GetRecipeSkillPoint( unsigned char recipeType )
{   
    if ( recipeType >= ERT_MaxType )
    { return 0; }

    return gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ];
}

inline unsigned short GamePlayer::SetRecipeSkillPoint( unsigned char recipeType, unsigned short pointValue)
{
    if ( recipeType >= ERT_MaxType )
    { return 0; }

    return gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ] = pointValue;
}

inline bool GamePlayer::CheckUseItemValid()
{
    if ( !m_xUseItemInfo.IsValid() )
    { return false; }

    return true;
}

inline bool GamePlayer::SetSessionKey ( __int64 SessionKey )
{
    if ( 0 == SessionKey)
    { return false; }
	_SessionKey = SessionKey;
    //strncpy_s( _szSessionKey,sizeof(_szSessionKey),szSessionKey,sizeof(_szSessionKey)-1);
    return true;
}

#endif // __GAMESERVER_GAMEPLAYER_H__