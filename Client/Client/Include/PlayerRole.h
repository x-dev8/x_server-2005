#pragma once

#include "Dxsdk/D3DX9Math.h"
#include "MessageDefine.h"

#include "GlobalDef.h"
#include "ItemDetail.h"
#include "bag\ItemBag2.h"
#include "Bag/SkillBag.h"
#include "XinFaManager.h"
#include "Storage.h"
#include "RestoreColdDown.h"
#include "EquipmentDoll.h"
#include "GuildIcon.h"
#include "suit.h"
#include "SystemMail.h"  //邮件系统
#include "RelationDefine.h"
#include "GuildDefine.h"
#include "CampBattleDefine.h"
#include "QuestManager.h"
#include "SevenDays.h"

#define MAX_ITEM_COUNT	99
#define MAX_DUEL_TIPS 10
#define CHANGE_MAP_WAIT_TIME 20			// 切地图倒计时，单位秒
#define ADD_TEACHER_STUDENT_MAX_DIST 10 // 拜师收徒最大距离

class CPlayer;

struct TeamInfo
{
	TeamInfo()
	{
		nID = -1;
		bHeader = false; 
		usProfession = 0;
		nMapID = -1;
		x = 0;
		y = 0;
		fx = 0.f;
		fy = 0.f;
		ucSex = 0;
		bHeader2 = false;
		bOnline = true;
		nHairId = 0 ;
		nFaceId = 0 ;
		AssignMode = 0;
	}
	int	  nID;
	std::string  szName;  //名字
	int nHp;	 
	int nMaxHp;
	int nMp;
	int nMaxMp;

//	bool		bCorps;
	bool		bOnline;
	bool		bHeader;		//是否大队长,目前只有大队长的逻辑2009.10.12
	short		stManiple;		//第几小队
	unsigned char ucSex;		//性别
	unsigned char usProfession; //职业
	bool	use_flag;
	bool		bHeader2;			//小队队长

	int		nLvl;
	unsigned int nMapID;// modified, jiayi, [2009/11/25]
	int		x,y;
	float	fx,fy;
	bool	bIsNewAdd;                 //是否新加入的队员

	int nHairId; //头发
	int nFaceId; //脸
    int nHeadPicId; //头像

	unsigned char    AssignMode; //分配模式 lrt
};

class CGangMgr
{
public:
	CGangMgr();
	~CGangMgr();

	//member functions
	void Clear();
    void InitGuildData(Msg* pMsg);
	/*void GetGuildCreateTime(std::string& strDate);*/
	/*bool isMaster( unsigned int nDbId ) const { return (m_GangInfo.GetMasterID() ==nDbId );}*/
	/*bool IsSameGang( const std::string& strName );*/
	/*bool IsMemberOnline(int nId);*/
	/*void ChangeMemberTong(GuildMember* pSrcMember,char newTong );*/
	/*BOOL DelMember( GuildMember* pMember );*/
	/*void EraseFromTongMember( GuildMember *pMember );*/
	/*void	updateGuildRelation( int guildId, char relation ,bool bSilence = false);*/
	/*const char* GetGuildViceMasterName();*/
	GuildMember*	FindByDBId( int nDBId );
	GuildMember*	FindByName( const char* pszName );
	bool					AddMember( GuildMember* pSrcMember );
	BOOL				DelMember( int nID);
	int					GetMemberCount(){ return m_vMember.size(); }
    int					GetMemberOnlineCount();

	GuildMember*	GetMember( int i ){ return m_vMember[i]; }

	const char*		GetGuildMasterName();

	void					SetGuildName( const char* m_szName );
	const char*		GetGuildName(){ return m_GangInfo.GetName(); }
	const char*		GetGuildNotice() {return m_GangInfo.GetNotice();}
	
	unsigned int		GetGuildID() const { return m_GangInfo.GetID(); }
	int					GetFamilyNumber() {return m_GangInfo.GetFamliyCount(); }
	const char*		GetFamilyName( unsigned char uchID ) { return m_GangInfo.GetFamilyName(uchID); }
	void					SetFamilyName(unsigned char uchID, const char* szName) { m_GangInfo.GetFamily(uchID)->SetName(szName); }

	const char*		GetGuildNotice() const {return m_GangInfo.GetNotice(); }
	const char *GetGuildAim(void) const{return m_GangInfo.GetAim();}
	int					GetGuildLevel() { return m_GangInfo.GetLevel(); }
	unsigned int		GetGuildMoney() { return m_GangInfo.GetMoney(); }
	int					GetGuildExp() { return m_GangInfo.GetExp(); }
	unsigned int		GetGuildMission() const { return m_GangInfo.GetMission(); }
	int					GetGuildShopLevel() { return m_GangInfo.GetShopLevel(); }
	unsigned int		GetGuildMasterID(){return m_GangInfo.GetMasterID();}

	GuildData& GetData(){return m_GangInfo;}

	void SetGuildNotice(const char* pszGuildNotice) { m_GangInfo.SetNotice(pszGuildNotice); }
	void SetGuildAim(const char *content_){m_GangInfo.SetAim(content_);}
	void SetGuildLevel(int nLevel) { m_GangInfo.SetLevel(nLevel); }
	void SetGuildMoney(unsigned int nValue) { m_GangInfo.SetMoney(nValue); }
	void SetGuildExp(unsigned int nValue) {m_GangInfo.SetExp(nValue); }
	void SetGuildMission(unsigned int nValue) { m_GangInfo.SetMission(nValue); }
	void SetGuildMasterID(unsigned int nValue) { m_GangInfo.SetMasterID(nValue); }
	void SetGuildShopLevel(unsigned int nValue) { m_GangInfo.SetShopLevel(nValue); }
	
	void ResetMemberActive();
	bool CheckShopActive(unsigned char uchLevel) const { return m_GangInfo.CheckShopActive(uchLevel); }
	int GetGuildStrength();
protected:
	GuildData  m_GangInfo;
	int m_nMemberNum;
	std::vector<GuildMember*> m_vMember;
	
private:
	void	ClearMember();
	void StoreAllMember();
};

typedef GuildListInfo CGuildInfo;

//用户数据
class CPlayerRole
{
public:	

	enum enUpdataType
	{
		TYPE_PROFESSION,					// 职业
		TYPE_LEVEL,							// 等级
		TYPE_EXP,							// 经验
		TYPE_EXPNOTUSED,					// 未用经验
		TYPR_SKILLEXP,						// 技能经验
		TYPR_SKILLEXPNOTUSE,				// 未用技能经验
		TYPE_Pkvalue,
		TYPE_ExPower,						// 斗气
		TYPE_Exploit,						// 功勋
		TYPE_Reputation,					// 声望
		TYPE_Glory,							// 荣誉
		TYPE_CountryScore,					// 国战积分
		TYPE_AreaRepulation,				// 地区声望
		TYPE_MONEY,							// 钱
		TYPE_Silver,						// 银
		TYPE_GLOD,							// 金 
		TYPE_JinDing,						// 金锭
		TYPE_JinPiao,						// 金票
		TYPE_TradeMoney,					// 账户资金 金钱
		TYPE_TradeJinDing,					// 账户资金 金锭
		TYPE_JiaoZi,                        // 帐户资金 交子
		
		TYPE_HP,							// 血
		TYPE_MP,							// 魔
		TYPE_HPRESTORE,						// 回血
		TYPE_MPRESTORE,						// 回魔	
		TYPE_HPMAX,							// 血上限
		TYPE_MPMAX,							// 魔上限
		TYPE_Strength,				     	// 力量
		TYPE_Agility,					    // 敏捷
		TYPE_Stamina,					    // 耐力
		TYPE_Intelligence,					// 智力
		TYPE_ATTACKPHYSICS,					// 物理攻击力
		TYPE_AttackMagic,                   // 魔法攻击力
		TYPE_DefendPhysics,					// 物理防御
		TYPE_DefendMagic,					// 魔法防御
		TYPE_EXACT,							// 命中
		TYPE_DODGE,							// 闪避
		TYPE_CRITICLE,						// 暴率
		TYPE_CRITICLEINTENSITY,				// 暴击倍数
		TYPE_TENACITY,						// 韧性
		TYPE_MOVESPEED,						// 移速
		TYPE_ATTACKSPEED,					// 攻速

		TYPE_BackStrike,                    // 背击伤害
		TYPE_BackStrikeResist,              // 背击抗性
		TYPE_BreakStrike,                   // 破甲伤害
		TYPE_StabStrike,                    // 贯穿伤害
		TYPE_ElementStrike,                 // 元素伤害
		TYPE_ToxinStrike,                   // 毒素伤害
		TYPE_SpiritStrike,                  // 精神伤害
		TYPE_BreakResist,                   // 破甲抗性
		TYPE_StabResist,                    // 贯穿抗性
		TYPE_ElementResist,                 // 元素抗性
		TYPE_ToxinResist,                   // 毒素抗性
		TYPE_SpiritResist,                  // 精神抗性


		TYPE_ENERGY,						// 活力值
		TYPE_ENERGY_MAX,
		TYPE_VIGOR,							// 精力值				
		TYPE_VIGOR_MAX,

        TYPE_CaoYao,                        // 草药
        TYPE_ZhuBao,                        // 珠宝
        TYPE_DuanZao,                       // 锻造
        TYPE_ZhuJia,                        // 铸甲
        TYPE_GongYi,                        // 工艺
        TYPE_XunMa,                         // 驯马
        TYPE_CaiKuang,                      // 采矿
        TYPE_CaiYao,                        // 采药
        TYPE_BuChong,                       // 捕虫
        TYPE_BuZhuo,                        // 捕捉     (不是生活技能)
        TYPE_Storage,                       //仓库
		TYPE_PetSrorage,                    //宠物仓库

		TYPE_FreeReliveCount,			   // 今天已经复活了多少次

		TYPE_Daoxing,                       // 当前道行
		TYPE_CurGetDaoxing,                 // 当前获得道行
		TYPE_BasePotential,                 //当前潜力点
		TYPE_ShopCenterScore,               //lyh++ 商城积分
	};

	// 任务状态
	struct QuestInfo
	{
		QuestInfo()
		{
			bDone = false;
			time = 0;
			// 			bReqInfoed = false;
		}
		int nQuestId;
		short chState;
		bool bDone;
		__int64 time; //任务开始时间
		//
		// 		bool bReqInfoed;
	};

	// 任务对话的标示位
	class QuestTalkState
	{
	public:
		QuestTalkState()
		{
			m_nQuestId = -1;
			for( int i = 0 ; i < QuestManager::HSTT_Count; ++ i )
				m_abSawStates[i] = false;
		}

		// Set/Get quest id
		void SetQuestId( int nQuestId ){ m_nQuestId = nQuestId; }
		int GetQuestId() const{ return m_nQuestId; }

		// Set/Get saw states
		void SetSawStates( int nPos, bool bValue )
		{ 
			if( nPos < 0 || nPos >= QuestManager::HSTT_Count )
				return;

			m_abSawStates[nPos] = bValue;
		}
		bool GetSawStates( int nPos )
		{
			if( nPos < 0 || nPos >= QuestManager::HSTT_Count )
				return false;

			return m_abSawStates[nPos];
		}

	private:
		// 任务id
		int m_nQuestId;
		// 状态
		bool m_abSawStates[QuestManager::HSTT_Count];		
	};
	typedef std::map<int, QuestTalkState> QuestTalkStates;

public:
	CPlayerRole(void);
	~CPlayerRole(void);
	void                initialize( const SCharInfoClient& charinfo, DWORD dwDBID );

	SCharInfoClient&	GetCharInfo2(){ return m_charinfo; }
	void				SetCharInfo( const SCharInfoClient& charinfo );
	//void				SetMoveSerial( char cMoveSerial ){ m_cMoveSerial = cMoveSerial; }
	//char				GetMoveSerial(void){ return m_cMoveSerial; }

	// 获得斗气值
	short				GetExPower(){ return m_charinfo.baseinfo.liveinfo.nXp; }
	//技能相关操作函数
	short				GetSkillLevel( short stSkillIndex );
	short				GetSkillLevelById( short stSkillId );
	void				SetSkillLevel( short stSkillIndex, short stNewLevel );
	//对技能进行分类组织
	void				ReOrganizeSkill( );	
	//
	bool				IsCanEquip(SCharItem *pItem);
	bool				IsCanEquip(SCharItem *pItem, ItemDefine::TagEquipRequest *pEquipReq);
	//取得
	int					GetMyHP(void);
	int					GetMyMP(void);
	//short				GetTP(void);

	void				SetCountry( int iCountry );
	int					GetCountry( void );

	//设置角色数据
	void				SetPlayerMP( int nMPDec);
	void				DecPlayerMP( short stMPDec );
	void				IncPlayerMP( short stMPInc );
	void				SetPlayerHP( int nHPDec);
	void				DecPlayerHP( short stHPDec );
	void				IncPlayerHP( short stHPInc );
	//void				IncPlayerTP( short stTPInc );
	void				Levelup(unsigned short ustNewLevel);
	void                SkillLevelUp(unsigned short ustSkillLevel,unsigned short ustSkillID);
	//void				SetCurSkill( int iSkill = ErrorUnsignedShortID ) { m_iSkill = iSkill; }
	//int					GetCurSkill(){ return m_iSkill; }
	void                SkillExpChang(unsigned short ustSkillID,DWORD dwSkillExp);
	//void                ChangePower(short stPower,short stPowerMax);
	//void                ChangePowerPoint(short stPowerPoint,short stPowerPointMax);

	//装备背包
	int					GetEquipBagItemCount(const int BagIndex);

	void				FreshEquipData( SCharAttributeUpdate* pFightData );				//刷新装备数据
	bool				Equip( const SCharItem* pCharItem, const int nWhere );			// 装备
	bool				UnEquip( const int nWhere );									// 卸载
	bool				Update( enUpdataType enType, const double dwValue );			// 更新人物属性
	DWORD				GetData( enUpdataType enType );                                // 获得人物属性
	void				UpdateUI();														// 更新界面
	bool				IsNeedUpdateUI();
	void				SetID( GameObjectId nID ){ m_nID = nID; }
	GameObjectId		GetID(){ return m_nID; }
	DWORD			GetDBID(){ return m_dwPlayerDBID; }
	char*				GetName(){ return m_charinfo.baseinfo.aptotic.szCharacterName; }
	int					GetLevel(){ return m_charinfo.baseinfo.liveinfo.ustLevel; }

	unsigned short		GetStr()         { return m_charinfo.baseinfo.baseProperty.baseAttr.baseAttrValue[EBaseAttr_Strength].final; }
	unsigned short		GetAgi()         { return m_charinfo.baseinfo.baseProperty.baseAttr.baseAttrValue[EBaseAttr_Agility].final; }
	unsigned short		GetSta()         { return m_charinfo.baseinfo.baseProperty.baseAttr.baseAttrValue[EBaseAttr_Stamina].final; }	
	unsigned short		GetIntelligence(){ return m_charinfo.baseinfo.baseProperty.baseAttr.baseAttrValue[EBaseAttr_Intelligence].final; }
    unsigned short		GetMag()         { return 0; }

    // 人物经验  added by zhuomeng.hu		[10/9/2010]
    int64               GetExp()         { return m_pBaseInfo->liveinfo.dwExp; }
    int64               GetExpNotUsed()  { return m_pBaseInfo->liveinfo.dwExpNotUsed; }
    void                SetExpNotUsed( int64 exp ){ m_pBaseInfo->liveinfo.dwExpNotUsed = exp; }

	void				SetWeekKillSum(uint32 num);
	void				SetAllKillSum(uint32 num);
	uint32				GetAllKillSum();
	uint32				GetWeekKillSum();

	//技能点数
	uint32 GetSkillExp(){return m_pBaseInfo->liveinfo.dwSkillExp;}
	uint32 GetSkillExpNotUsed(){return m_pBaseInfo->liveinfo.dwSkillExpNotUsed;}
	void SetSkillExpNotUsed(uint32 exp){m_pBaseInfo->liveinfo.dwSkillExpNotUsed = exp;}

	float GetBaseSpeed(){return m_pBaseInfo->baseProperty.fightAttr.moveSpeed.base;}
	//bool				IsFriend( short stCharID,int iCharType,int iTeamID = -1,int iGuildID = -1 );	//根据角色类型判断是否主角的朋友
	void				UpdateArmourUI();												// 更新界面中的套装信息
	unsigned char		GetSex( ){ return m_pBaseInfo->aptotic.ucSex; }					//取得性别
	unsigned char		GetProfession( ){ return m_pBaseInfo->aptotic.usProfession;	}	//获得职业
	const SCharItem*	GetEquipItem( short stPart ){ return &(m_pVisual->equipitem[stPart]); }	//获得道具

	BOOL				IsDie();

	int					GetValidFreeReliveCount();// 当前还可以复活的次数

	bool				IsFinishedIntroduce( int id );
	void				SetFinishedIntroduce( int id );

	//取得主角的身体状态
	//	short				GetBuff(void);
protected:
	void HPChanged();
	void MPChanged();

public:
	//角色数据
	SCharInfoClient		m_charinfo;
	SBaseProperty		m_charLastBaseProperty;		//变身前一次属性
	//异地从仓库取物件收费费率
	float				fCostOfFetchItem[STORAGE_ITEMGRID_MAX];
	//仓库城市名字
	char				CityName[STORAGE_ITEMGRID_MAX][MAX_NAME_STRING];
	//物品加密密码
	char				szItem_PWD [PWD_OF_ITEM];
	// 坐骑技能
	SCharSkill			m_MountSkill[ More_iMaxSkillKnown ];
	SkillBag			m_MountSkillBag;
	//装备
	SCharVisual			*m_pVisual;
	//基础属性
	SCharBaseInfo		*m_pBaseInfo;
	CEquipmentDoll		m_doll;
private:
	// 动态ID
	GameObjectId	    m_nID;
	//角色DB ID 
	DWORD				m_dwPlayerDBID;
	// 属性改变后需要更新界面
	bool				m_bUpdateUI;

    //--------------------------------------------------------------
    //------------------------- 国家 -------------------------------
public:
    void SetWeakCountry( int iCountry );
	void SetStrongCountry( int iCountry );
    bool IsInWeakCountry();
	bool IsInStrongCountry();
	int  GetWeakCountryID(){return m_nWeakCountryId;}
	int	 GetStrongthCountryID(){return m_nStrongCountryId;}
private:
    int                 m_nWeakCountryId;       // 弱国国家ID
	int					m_nStrongCountryId;		// 强国国家ID

	//--------------------------------------------------------------
	//------------------------- 包裹 -------------------------------
public:
	CItemBag2			m_bag;
	CItemBag2			m_bagMaterial;
	CItemBag2			m_bagTask;
	SkillBag			m_SkillBag;
	SkillBag			m_HeroSkillBag;
	XinFaManager m_xinFaBag;
	// added, jiayi, [2009/9/11]
	// 通过guid获得包裹数据，包括各种包裹
	bool				GetBagItemByGUID( __int64 nGUID, SCharItem* pItem );
	bool				GetBagTypeByItemGUID( __int64 nGUID, EBagType& eType, int* pIndex = 0 );		
	bool				GetBagByItemGUID( __int64 nGUID, CItemBag2*& pBag );
	int                 GetBagTypeByItemType( int nItemType );              //added by ZhuoMeng.Hu		[1/17/2011]
	CItemBag2*			GetBagByItemType(int nItemType);
	CItemBag2*			GetBagByItemID(unsigned int ItemID);
	//--------------------------------------------------------------
	//------------------------- 仓库 -------------------------------
public:
    bool				GetStorageItemByGUID( __int64 nGUID, SCharItem* pItem );
    bool                GetStorageMountByGUID( __int64 nGUID, SMountItem* pItem );
	void				SetNpcID(int id) { m_nNpcID = id; }
	int					GetNpcID() { return m_nNpcID; }
	SCharStorageData	m_stStorage;								// 仓库数据
	void				SetIsSecondPassword( bool b );				// 仓库二级密码
	bool				GetIsSecondPassword();
	void				SetSecondPasswordUnlockTime( uint32 time );
	uint32				GetSecondPasswordUnlockTime();
private:
	int					m_nNpcID;									// 仓库NPC
	BOOL				m_bSecondPassword;							//仓库二级密码
	uint32				m_nSecondPasswordUnlockTime;				//仓库密码解除剩余时间

	//--------------------------------------------------------------
	//------------------------ 快捷键 ------------------------------
public:
	//------ 快捷背包序号变更 维护策划不停的更改变化 -------------- |  0--5  扩展快捷栏用 s_CUI_ID_FRAME_Exmain.m_pID_LISTIMG_exmain
	//HotKey Point													|  6--9  没用
	SMouseItem			m_pHotKeyBag[More_iHotkey];	//快捷背包		| 10--27 主界面用 s_CUI_ID_FRAME_MAIN.m_pID_LISTIMG_Hotkey(0,1,2各用6个)
	//																| 28	 右键快捷用 s_CUI_ID_FRAME_SelectSkill.m_pID_LISTIMG_skill
	//															    | 所以	enumConst::More_iHotkey 设为29 
	void				InitHotKey();
	void				SendHotKeyToServer();
	void				refreshHotKey();							// 更新快捷键


	//--------------------------------------------------------------
	//------------------------ 任务相关 ----------------------------
public:
	void				RefreshQuestDone();
	std::vector<QuestInfo*>& GetActiveQuestInfo(){ return m_vectorActiveQuestInfo; }
	void				FillRequirementQuestArr();
	// added, jiayi, [2009/9/22], 任务信息是否完全加载了
	bool				IsQuestInitialized();
	void				QuestInfoInitialized();
	// 更改任务状态
	QuestInfo*			FindQuestInfoById( int nQuestId );
	QuestInfo*			FindVariableInfoById( int nVariableId );
	void				FilterQuest( int nQuestId  );
	bool				ChangeQuestState( int nQuestId, short chState);
	void				UpdateActiveQuestState( BOOL bUpDataUI = TRUE,BOOL bRefreshAll = TRUE );
	bool				UpdateActiveQuestStateByVariable(QuestInfo* pVariableInfo );
	bool				UpdateActiveQuestStateByQuest(QuestInfo* pQuestInfo );
	bool				UpdateActiveQuestStateByItem(int ustItemID);
	void				ReqQuestInfo( int nQuestId );
	int					GetVariableValue( int number );
	bool				TaskNeedRemind(SQuest* pQuest);
	bool				AddToActiveQuestInfo(QuestInfo* info);
	bool				IsQuestDone(SQuest *pQuest);
	// 任务对话-如果没有这个任务的对话状态，则添加，如果有了，则刷新。
	// stValue是合成值，需要分解处理。
	void				RefreshTalkStates( int nQuestId, short stValue );
	// 任务对话-根据任务id，状态类型，返回状态值
	bool				GetTalkStates( int nQuestId, int nType );
private:
	typedef std::map<int, QuestInfo> QuestInfos;
	QuestInfos			m_VariableInfos;
	QuestInfos			m_questInfos;
	std::vector<QuestInfo*> m_vectorActiveQuestInfo;					// 当前进行的任务
	std::vector<int>	m_vectorRequirementVariableQuestId;				// 变量前置任务
	std::vector<int>	m_vectorRequirementItemQuestId;					// 物品前置任务
	bool				m_bQuestInitialized;
	QuestTalkStates		m_QuestTalkStates;

	//--------------------------------------------------------------
	//------------------------ 技能相关 ----------------------------
public:
	//主要提供给界面显示使用！
	int					GetNormalSkillNum( ){ return m_iNormalSkillNum; }
	int					GetNormalSkillIndex( int iIndex ){ return m_iNormalSkillIndexArray[iIndex];	}
	int					GetMagicSkillNum( ){ return m_iMagicSkillNum; }
	int					GetMagicSkillIndex( int iIndex ){ return m_iMagicSkillIndexArray[iIndex]; }
private:
	int					m_iNormalSkillNum;								//普通技能的个数
	int					m_iNormalSkillIndexArray[More_iMaxSkillKnown];	//存放普通技能索引的数组
	int					m_iMagicSkillNum;								//魔法技能的个数
	int					m_iMagicSkillIndexArray[More_iMaxSkillKnown];	//存放魔法技能索引的数组



	//--------------------------------------------------------------
	//------------------------- 称号 -------------------------------
public:
	void				SetTitleListInfo( SCharBaseInfo::SCharLiveInfo* pMsg );
	void				AddNewTitleId( short stId,__int64 n64AcquireTime,uint32 nActiveTime);
	void				RemoveTitleId( short stId );
	const std::vector<TitleData>& GetTitleArray() const	{ return m_vTitleArray;	}
private:
	std::vector<TitleData> m_vTitleArray;


	//--------------------------------------------------------------
	//------------------------- 帮派 -------------------------------
public:
	CGangMgr*			GetGangMgr(){ return &m_GuildMgr; }
	std::vector<CGuildInfo>* GetGuildVct() { return &m_vctGuild;}
	void StoreAllGuildInfo(int nNUm, CGuildInfo*);
	int GetGuildNum() { return m_vctGuild.size(); }
	CGuildInfo* GetGuild(int nIndex) { return nIndex >= m_vctGuild.size()? NULL : &m_vctGuild[nIndex]; }
	void AddNewGuild(CGuildInfo&);
	const CGuildInfo* GetGuildById(int nGuildId) const;
	const char* GetGuildNameById(int nGuildId) const;
private:
	void ResetGuildData();

private:
	CGangMgr			m_GuildMgr;
	std::vector<CGuildInfo> m_vctGuild;
	/*int m_nGuildNum;*/

public:
	// 下面两个貌似没用了
	int					m_nCompoundRateAdd;
	int					m_nIntensifyRateAdd;

	// 商城
	int					m_nShopCenterOffSell;
	//--------------------------------------------------------------
	//------------------------- 切磋 -------------------------------
public:
    void				InitDuelTips();
    void				DuelProcess();
    void				SetDuelTarget(GameObjectId shID) { m_shDuelTarget = shID; }
    GameObjectId				GetDuelTarget() { return m_shDuelTarget; }
    void				SetDuelName(const char* szName) { strncpy(m_szDuelName, szName, sizeof(m_szDuelName)-1); }
    const char*			GetDuelName() { return m_szDuelName; }
    void				SetDuelPos(D3DXVECTOR3 vPos) { m_vDuelPos = vPos; }
	D3DXVECTOR3&		GetDuelPos() { return m_vDuelPos; }
    void				SetDuelMapID( int iID ) { m_iDuelMapID = iID; }
    int					GetDuelMapID() { return m_iDuelMapID; }
    void				SetDuelTime(unsigned int nTime) { m_nDuelTime = nTime; }
    unsigned int		GetDuelTime() { return m_nDuelTime; }
	void				SetSelfOutTime(int time) { m_nSelfOutTime = time; }
	void				SetDuelOutTime(int time) { m_nDuelOutTime = time; }
private:
	GameObjectId				m_shDuelTarget;									// 切磋对象
	char				m_szDuelName[dr_MaxPlayerName];					// 切磋对象名字
	D3DXVECTOR3			m_vDuelPos;										// 切磋位置
	unsigned int		m_nDuelTime;
	bool				m_bDuelTipsLoaded;
	int					m_iDuelMapID;
	int					m_nSelfOutTime;									// 脱离切磋范围计时
	int					m_nDuelOutTime;


public:
    //--------------------------------------------------------------
	//-------------------------　　组队相关	------------------------
	std::vector<TeamInfo>	m_TeamData;									//队伍里面队友的数据
	BOOL				m_bCorps;										//是否是团队
	BOOL				IsTeamMember(const char* playername);
	BOOL				IsTeamMember(DWORD dwId){ return GetTeamInfo(dwId) != NULL; }
	DWORD				GetTeamMemberId(const char* playername);
	TeamInfo*			GetTeamInfo(DWORD dwId);
	TeamInfo*			GetMeTeamInfo();
	BOOL				IsRole(DWORD dwId);
	int					GetTeamMemberNum(){ return m_TeamData.size(); }
	std::vector<TeamInfo>& GetTeamInfo(){ return m_TeamData; }
	//short				stManiple;
	BOOL				IsTeamHeader();
	BOOL				IsManipleHeader();
	void				OnAddTeamMember(TeamInfo &InInfo);				//增加队友
	void				OnDeleteTeamMember(int nID);					//删除队友
	void				UpdataPlayerInfo( TeamInfo &InInfo, BOOL OnlyRefeashHPUI = FALSE );
	void				OnExitTeam(void);								//离开队伍
	void				ClearTeam()		{ m_TeamData.clear(); }
	void				SetGroupId( int id )				{ m_GroupId = id; }
	int					GetGroupId() const					{ return m_GroupId; }
private:
	int					m_GroupId;										// 队伍ID


	//--------------------------------------------------------------
    //---------------------------分配模式---------------------------
public:
    short				GetAssignMode() { return m_shAssignMode; }
    void				SetAssignMode(short nAssignMode)
    {
        m_shAssignMode = nAssignMode;
        if( m_shAssignMode < AssignMode_FreeMode )
            m_shAssignMode = AssignMode_FreeMode;
        else if( m_shAssignMode > AssignMode_Assign )
            m_shAssignMode = AssignMode_Assign;
    }
    //物品品质
    short				GetItemRollLevel() { return m_shItemRollLevel; }
    void				SetItemRollLevel(short nLevel)
    {
        m_shItemRollLevel = nLevel;
        if( m_shItemRollLevel < eIL_Choiceness )
            m_shItemRollLevel = eIL_Choiceness;
        else if( m_shItemRollLevel > eIL_Nonsuch )
            m_shItemRollLevel = eIL_Nonsuch;
    }
private:
	short               m_shItemRollLevel;								// 掷骰子的物品品质
	short               m_shAssignMode;									// 分配模式


public:
	//-------------------------		-----------------------------------------------------------------------
	//使用恢复药品
	void				OnRestoreItem(int ItemID, int TagNpcID);
	//使用基本动作
	void				OnBaseAction(int ItemID, int TagNpcID);
	//社群动作
	void				OnCorporation(int ItemID, int TagNpcID);
	//社交动作
	void				OnSociality(int ItemID, int TagNpcID);
	//	生成背包中道具的注解
//	bool				CreateBagItemDesc(int iBagType, int iBagIndex, char (*pString)[256], DWORD* pdwColor, int iMaxLineNum, int* pFactLineNum);
	//	判段使用的技能是否能用
	BOOL				IsSkillCanUse( ItemDefine::SItemSkill* pSkill );
	bool				IsSkillCanUse(int iSkillID, int iSkillLevel);
	//设置玩家身上的钱
	void				SetMoneyOnPlayer(DWORD dwMoney );
	//SCharSkill*		GetSkill( int iSkillID)


	//--------------------------------------------------------------
	//---------------------- 人物移动 ------------------------------
public:
	void				StartMoving( GameObjectId id, DWORD dwStartingTime, float x, float y, float z, float DirX, float DirY, short shMovingType );
	void				SendMoveMessage( GameObjectId id, float x, float y, float z, float DirX, float DirY, DWORD dwCurTime, BOOL bMoving, short shMovingType, BOOL bLastFrameMoving );
	BOOL				CanSendMoveMessage( DWORD dwCurTime );
	BOOL				IsCollectPos();
	BOOL				CanSendActionMessage();
	void				SetLastStopMovingTime(DWORD time) { m_dwLastStopMovingTime = time; }
	DWORD				GetLastStopMovingTime() { return m_dwLastStopMovingTime; }
	// 沿给定方向获得最近碰撞物距离，bNeedAdjust等于FALSE，不需要任何纠正
	BOOL				GetDistToCollision( D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, float* fDistToCollision, D3DXVECTOR3* vCollisionDir = NULL,
		D3DXVECTOR3* vCollisionNormal = NULL, float* fAngleToCollision = NULL, BOOL bNeedAdjustWithAngle = TRUE, BOOL bNeedAdjust = TRUE );
	void				SetLastPos(float fPosX, float fPosY){m_vLastSavePos.x = fPosX; m_vLastSavePos.y = fPosY;};
	void				SetLastDir(float fDirX, float fDirY){m_cLastSaveDirX = fDirX*127.f; m_cLastSaveDirY = fDirY*127.f;};

	float               GetLastPosX(){return m_vLastSavePos.x;}
	float               GetLastPosY(){return m_vLastSavePos.y;}
	float               GetLastDirX(){return m_cLastSaveDirX;}
	float               GetLastDirY(){return m_cLastSaveDirY;}
	
	void                SetStartCollectPosTime(DWORD time){m_dwStartCollectPosTime = time;}
	DWORD               GetStartCollectPosTime(){return m_dwStartCollectPosTime;}
private:
	D3DXVECTOR3			m_vLastSavePos;
	//D3DXVECTOR3 m_vLastSaveDir;
	char				m_cLastSaveDirX;
	char				m_cLastSaveDirY;
	char				m_cLastSaveDirZ;
    BOOL				m_bNeedSendLastPos;								// 人物停下后需要再发一遍位置信息

	BOOL				m_bStartCollectPos;
	DWORD				m_dwStartCollectPosTime;						//开始记录坐标点的时间
	BOOL				m_bCanSendActionMessage;						//是否可以发送动作信息
	DWORD				m_dwLastStopMovingTime;							//最后不移动的时间
	BOOL				m_bMustSendMovingMessage;						//第一个移动包不发，等第二帧人物方向正确后再发


	//--------------------------------------------------------------
	//---------------------- 特殊技能 ------------------------------
public:
	BOOL				CanUseSpecialSkill();
	void				SetCanUseSpecialSkill( BOOL bCan );
private:
	BOOL				m_bCanUseSpecialSkill;


	//--------------------------------------------------------------
	//---------------------- 战斗状态 ------------------------------
public:
	bool				IsFighting(){ return m_bFighting; }
	void				SetFighting( bool b ){ m_bFighting = b; }
	void				CheckFight();
private:
	bool				m_bFighting;


	//--------------------------------------------------------------
	//---------------------- 地图跳转 ------------------------------
public:
	// 行走中判断是否进传送点[QL]
	bool				IsInTransport( float posx, float posy, int& nMapId, int& nTargetId, int& nEntranceId );
	void				SetCanChangeMap(bool v) { m_bWaitforTransport = !v; }
	bool				GetCanChangeMap() const { return !m_bWaitforTransport; }   // 传送超时后，如果玩家走出传送区域，m_bWaitforTransport会值成false
    bool				IsShowingWaitforTransport() { return m_bShowingWaitforTransport; }
    void				CloseShowingWaitforTransport() { m_bShowingWaitforTransport = false; }
	void				SetShowingWaitforTransport(bool IsShow){m_bShowingWaitforTransport =IsShow; }
private:
	bool				m_bWaitforTransport;							// 已经发送跳转请求，避免重复请求
    bool				m_bShowingWaitforTransport;						// 是否正在显示等待跳转提示


	//--------------------------------------------------------------
	//----------------------- 物品CD -------------------------------
public:
	RestoreColdDown*	GetRestoreCoolDown();
private:
	RestoreColdDown		m_RestoreCoolDown;


public:
	int					CalcShowPropertyValue(float value)
	{
		return value + 10.5f;
	}


	//--------------------------------------------------------------
	//------------------------ 骑宠 --------------------------------
public:
	size_t				AddMount(const SMountItem& mountItem);
	void 				RemoveMountByIndex(int nIndex);
	void 				RemoveMountByGUID( __int64 nGUID );
	SMountItem&			GetMount(int nId);
	SMountItem&			GetMountByIndex(size_t nIndex);
	SMountItem*			GetMountByGUID( __int64 nGUID );
	size_t				GetMountCount();
	bool				HasMountSpace() const;
	void				AddMountSkill(const SMountItem& mountItem);
	void				RemoveMountSkill(const SMountItem& mountItem);
	SMountItem*			GetActivedMount();
	int					GetActivedMountIndex();
	__int64				GetActivedMountGUID();
	void				ActiveMount(size_t nIndex);
	void				UnactiveMount(size_t nIndex);
	void				ActiveMountByGUID( __int64 nGUID );
	void				UnactiveMountByGUID( __int64 nGUID );

	//--------------------------------------------------------------
	//-----------------------宠物-----------------------------------
public:
	size_t              AddPet(const SPetItem& petItem);
	void                RemovePetByIndex(int nIndex);
	void 				RemovePetByGUID( __int64 nGUID );
	SPetItem&			GetPet(int nId);
	SPetItem&			GetPetByIndex(size_t nIndex);
	uint8					GetPetIndexByName(const char *m_name);
	SPetItem*			GetPetByGUID( __int64 nGUID );
	size_t				GetPetCount();
	bool				HasPetSpace() const;
	void				AddPetSkill(const SPetItem& mountItem);
	void				RemovePetSkill(const SPetItem& mountItem);
	SPetItem*			GetActivedPet();
	int					GetActivedPetIndex();
	__int64				GetActivedPetGUID();
	void				ActivePet(size_t nIndex);
	void				UnactivePet(size_t nIndex);
	void				ActivePetByGUID( __int64 nGUID );
	void				UnactivePetByGUID( __int64 nGUID );
	//get the pet's index in the bag.
	int GetPetIndex(__int64 nGUID);

	SCharSkill          m_PetSkill[SPetItem::PetDefine_MaxSkillCount];
	SkillBag            m_PetSkillBag;
	//--------------------------------------------------------------
	//------------------------ 金币 --------------------------------
public:
    // 从铜转成金银铜 GSC: GoldSilverCopper
    void				GetGSCFromMoney(DWORD inputMoney, int& iGold, int& iSilver, int& iCopper);
    void				GetGSCStringFromMoney(DWORD inputMoney, std::string& strText);		// 从金钱获得string显示
	void				GetGSCStringFromCurrentMoney(std::string& strText);					// 从当前背包货币获得string
	// 交子
	void				GetGSCStringFromJiaoZi(DWORD inputJiaoZi, std::string& strText);	// 从交子获得string显示
	void				GetGSCStringFromCurrentJiaoZi(std::string& strText);	// 从当前背包交子获得string显示
    DWORD				GetMoneyFromGSC(int iGold, int iSilver, int iCopper);
    // 背包里钱够不够
    bool				PackHasEnoughMoney(int iGold, int iSilver, int iCopper);
    bool				PackHasEnoughMoney(DWORD dwMoney);
    // 仓库里钱够不够
    bool				StorageHasEnoughMoney(int iGold, int iSilver, int iCopper);
    bool				StorageHasEnoughMoney(DWORD dwMoney);

    void				SetStorageMoney(DWORD dwMoney) { m_stStorage.dwStorageMoney = dwMoney; }

    bool                HaveEnoughMoney(DWORD dwMoney);
public:
	void				SetTradeGold( uint32 gold ){ m_nTradeGold = gold; }
	void				SetTradeMoney( uint32 money ){ m_nTradeMoney = money; }
private:
	uint32				m_nTradeGold;									//账户资金金锭
	uint32				m_nTradeMoney;									//账户资金金钱


	//--------------------------------------------------------------
	//----------------------- 禁言 ---------------------------------
public:
	DWORD   			GetBanSpeakEndingTime() { return m_dwBanSpeakEndingTime; }
	void    			SetBanSpeakEndingTime(DWORD time) { m_dwBanSpeakEndingTime = time; }
protected:
    DWORD				m_dwBanSpeakEndingTime;							// 禁言结束时间（毫秒）


	//--------------------------------------------------------------
	//-------- 是否接收到复活消息并等待传送去地狱 ------------------
public:
    void 				SetIsReliveAndWaitingToHell(BOOL bflag) { m_bIsReliveAndWaitingToHell = bflag; }
    BOOL 				IsReliveAndWaitingToHell() { return m_bIsReliveAndWaitingToHell; }
protected:
	BOOL				m_bIsReliveAndWaitingToHell;


	//--------------------------------------------------------------
    //----------------------- 动态地图ID ---------------------------
public:
    void				SetGameMapId(DWORD nGameMapId) { m_dwGameMapId = nGameMapId; }
    DWORD				GetGameMapId() { return m_dwGameMapId; }
protected:
    DWORD				m_dwGameMapId;


	//--------------------------------------------------------------
	//----------------------- 套装管理器 ---------------------------
public:
	SuitManager			suitManager;


	//--------------------------------------------------------------
	// 是否被玩家攻击
	bool				m_isPlayerHitMe;
	// 被玩家攻击图片当前的开始时间
	DWORD				m_dwPlayerHitMeAlphaStartTime;


	//--------------------------------------------------------------
	//------------------------ 物品锁 ------------------------------
public:
	int					GetLockNum() { return m_nLockNum; }
	void 				SetLockNum(int num) { m_nLockNum = num; }
	void 				SetLockNumMax(int max) { m_nLockNumMax = max; }
	bool 				IsLockNumLimit() { return (m_nLockNum >= m_nLockNumMax); }
	void 				UpdateLockItem();								//更新物品锁信息
protected:
	int 				m_nLockNum;										//加锁的数量
	int 				m_nLockNumMax;
	float 				m_fUpdateLockItemTime;							// 解锁请求发送时间
	float 				m_fUnLockTimeCount;
	float 				m_UnLockTimeCount;


	//--------------------------------------------------------------
	//---------------------- 邮件系统 ------------------------------
public:
    bool				IsHaveMoneyInMail(uint32 uMailID){return m_SysMail.IsHaveMoney(uMailID);}
    bool 				IsHaveItemInMail(uint32  uMailID){return m_SysMail.IsHaveItem(uMailID);}

    const char*			GetMailTitle(uint32 uMailID){return m_SysMail.GetMailTitle(uMailID);}
    const char*			GetMailSender(uint32 uMailID){return m_SysMail.GetMailSender(uMailID);}
    const char*			GetMailContent(uint32 uMailID){return m_SysMail.GetMailContent(uMailID);}

    void  				UpdateMailByID(uint32 uMailID,SMail &mail){return m_SysMail.UpdateMailByID(uMailID,mail);}
    void  				ClearMailList(){m_SysMail.Clear();}
    void 				SendMail(){m_SysMail.SendMail();}
    void 				AddMail(SMail& mail){m_SysMail.AddMail(mail);}
    void 				DeleteMailByID(uint32 uID){m_SysMail.DeleteByID(uID);}
    void 				DeleteMailByTime(__int64 dwTime){m_SysMail.DeleteByTime(dwTime);}

    void 				FilterMail(MailFilter filterType){m_SysMail.FilterMail(filterType);}
    SMail* 				ReadMail(int nIndex){return m_SysMail.ReadMail(nIndex);}

    int  				GetCurrentMailSize(){return m_SysMail.GetCurrentMail();}
    bool 				RefreshReadStateByID(uint32 uMailID){return m_SysMail.RefreshReadStateByID(uMailID);}
    bool 				RefreshMoneyByID(uint32 uMailID){return m_SysMail.RefreshMoneyByID(uMailID);}
    bool 				RefreshItemByID(uint32 uMailID){return m_SysMail.RefreshItemByID(uMailID);}
    bool 				IsHaveNewMail(){return m_SysMail.IsHaveNewMail();}
	CSystemMail			GetMailSys(){return m_SysMail;}
private:
    CSystemMail			m_SysMail;  //邮件系统


	//--------------------------------------------------------------
	//------------------- 小队战场 ---------------------------------
public:
    bool				IsTeamBattleInMap();

	//--------------------------------------------------------------
	//阵营战
private:
	unsigned char m_nInfluence; // 阵营
	unsigned char m_nCampType;
	unsigned int m_nRedCampResource;
	unsigned int m_nBlueCampResource;
	unsigned int m_nRedCampGuildId;
	unsigned int m_nBlueCampGuildId;
	void InitCampData();

public:
	void InitInfluence();
	unsigned char GetCampType() const { return m_nCampType; }
	void SetInfluence(int nValue);
	unsigned char GetInfluence() const { return m_nInfluence; }
	void SetRedCampResource(unsigned int nValue) { m_nRedCampResource = nValue; }
	unsigned int GetRedCampResource() const { return m_nRedCampResource; }
	void SetBlueCampResource(unsigned int nValue) { m_nBlueCampResource = nValue; }
	unsigned int GetBlueCampResource() const { return m_nBlueCampResource; }

	void SetRedCampGuildId(unsigned int nId) { m_nRedCampGuildId = nId;}
	unsigned int GetRedCampGuildId() const { return m_nRedCampGuildId; }
	void SetBlueCampGuildId(unsigned int nId) { m_nBlueCampGuildId = nId;}
	unsigned int GetBlueCampGuildId() const { return m_nBlueCampGuildId; }

	//--------------------------------------------------------------
public:
	std::map<int, RelationDataToClient>& GetMapFriendInfo()  { return m_mapFriendInfo; }

	int  				GetdbID(const char* szName);		//通过名字得到好友id
	const char*			GetNameByDBID(uint32 uiDBID);		// 根据DBID获得好友名字
	bool 				IsOnline( const char* szName);		//检测玩家是否在线
	bool 				IsFriend(const char* szName);		//是否好友
	bool 				IsTempFriend(const char* szName);		//是否temp好友
	bool 				IsPlayerLock(const char* szName);		//是否锁定
	bool 				CanAddFriend(const char* szName);	//是否好友，黑名单，或仇人
	bool 				CheckNewFriendName(const char* szName, bool onlyCheck = true);
	bool 				CheckNewBlackName(const char* szName);
	bool 				isFrdInBlackList(uint32 nDBId);	//by DB Id
	bool 				isFrdInBlackList(const char* name);
	bool 				isChouRen(const char* name);
    const char*			GetMarryerName();					//获得配偶的名字

	void 				OnA2CAddFriend(Msg* pMsg);
	void 				OnA2CRelationAttribute(Msg* pMsg);
	void 				OnA2CTellRelationGroup(Msg* pMsg);
	void 				OnA2CRelationGroupChange(Msg* pMsg);
	void 				OnA2CGetFriendList(Msg* pMsg);
	void 				OnA2CDelFriend(Msg *pMsg);
	void 				OnA2CFriendOnline(Msg *pMsg);
	void 				OnA2CFriendOutline(Msg *pMsg);
	void 				OnA2CUpdateFriendInfo(Msg *pMsg);
	void 				OnInviteAddRelation(Msg *pMsg);
	void 				OnUpdateFriendly(Msg *pMsg);
	void				OnA2CUpdateLockInfo(Msg *pMsg);
	RelationGroup&		GetFrdGroup(int index) { return xGroup[index]; }
	int                 GetFriendGroupCount() const;
	void				SetSignature(const char* val);
	const char*			GetSignature() const { return szSignature; }
	int					GetGroupIndex(const char* pGroupName);
private:
	std::map<int, RelationDataToClient>	m_mapFriendInfo;
	char szSignature[ RelationDefine::MaxSignLength ];      // 个性签名
	RelationGroup xGroup[ RelationDefine::GroupCount ];     // 分组信息

	//--------------------------------------------------------------
	//--------------------- 师徒 -----------------------------------
public:
	bool				IsCanReceivePrentice();
	void				SetCanReceivePrentice();
	// 师徒属性改变
	void				SetMasterLevel(unsigned char level);
	unsigned char		GetMasterLevel();
	void				SetMasterValue(DWORD value);
	DWORD				GetMasterValue();
	void				SetStudentExperience(DWORD exp);
	DWORD				GetStudentExperience();
	bool				CanAddTeacher(GameObjectId playerID, bool bShowInfo);
	bool				CanAddTeacher(const char* szName, bool bShowInfo);
	bool				CanAddStudent(GameObjectId playerID, bool bShowInfo);
	bool				CanAddStudent(const char* szName, bool bShowInfo);
	void				CalculateTeacherStudent(bool& hasTeacher, int& iStudentNum);	// 显示右键菜单，或显示师徒界面时，需要调用重新计算师徒情况
	int					GetTeacherDBID();
	const char* GetStudentNameById(unsigned int nId) const;
	bool				IsTeacher( const char* szName );
	bool				IsStudent( const char* szName );
private:
	bool				CanAddTeacher(CPlayer* pTeacher, bool bShowInfo);
	bool				CanAddStudent(CPlayer* pStudent, bool bShowInfo);
public:
	void				OnCloseShopAnCK();

//	//master
//public:
//	std::map<int, RelationDataToClient>& GetMapMasterInfo()  { return m_mapMasterInfo; }
//private:
//	std::map<int, RelationDataToClient>	m_mapMasterInfo;


	//--------------------------------------------------------------
	//---------------------- 小队技能 ------------------------------
public:
	struct PlayerTeamSkill
	{
		unsigned int nSkillID;
		unsigned char uchLevel;
	};
	typedef std::vector< PlayerTeamSkill > PlayerTeamSkillVector;

	const PlayerTeamSkillVector* GetTeamSkillVector();
	void				CalcTeamSkillLevel();					// 加队员成功或移除队员时调用
protected:
	PlayerTeamSkillVector m_pVecTeamSkill;
	float				m_fCalcTeamSkillCD;						// 每n秒刷新小队技能，单位秒，n默认2


	//--------------------------------------------------------------
	//---------------- 防外挂，跳跃高度验证 ------------------------
public:
	void 				SetStartJumpPos(float x, float y, float z)	{ m_fRoleStartJumpX = x; m_fRoleStartJumpY = y; m_fRoleStartJumpZ = z; m_bRoleJump = true; }
	void 				EndJump() { m_bRoleJump = false; }
	bool 				IsRoleJump() { return m_bRoleJump; }
	float 				GetStartJumpX() { return m_fRoleStartJumpX; }
	float 				GetStartJumpY() { return m_fRoleStartJumpY; }
	float 				GetStartJumpZ() { return m_fRoleStartJumpZ; }
private:
	float				m_fRoleStartJumpX;
	float 				m_fRoleStartJumpY;
	float 				m_fRoleStartJumpZ;
	bool 				m_bRoleJump;							// 按空格键跳跃


	//--------------------------------------------------------------
	//---------------- 太平幻境			    ------------------------
public:
	bool				IsInTPHJ(){return m_charinfo.otherdataclient.sBornPos.dwMapID != 1;}
	SCharPosData		GetPrePosition(){return m_charinfo.otherdataclient.sBornPos;}
	void				SetPrePosition(SCharPosData pos){m_charinfo.otherdataclient.sBornPos = pos;}
	char				GetTPHJRank(){return m_charinfo.baseinfo.liveinfo.TPHJRank;}
	void				SetTPHJRank(char value,int operType=EOT_Set);
	//--------------------------------------------------------------
	//---------------- 主将变身				------------------------
	void				SetHeroAddAttr(SCharHeroInfo heroAttr);
	void				ShowHeroAttrInfo();

	//收回坐骑
	void				SetPetUnactive();

private:
	unsigned int		WorldBattleCountryID;
public:
	void				SetWorldBattleCountryID(unsigned int ID){WorldBattleCountryID = ID;}
	unsigned int		GetWorldBattleCountryID(){return WorldBattleCountryID;}
public:
	void		DelCountryOfficial();
private:
	unsigned int		PetDuration;
public:
	void		SetPetDuration(unsigned int Value){GetCharInfo2().otherdataclient.PetDuration = Value;}
	unsigned int GetPetDuration(){return GetCharInfo2().otherdataclient.PetDuration;}

	//---------------- 七天乐				------------------------
public:
	short m_taskState[SevenDaysConfig::TD_Max];
	short m_taskVar[SevenDaysConfig::TD_Max];

	//---------------- 分线var				------------------------
public:
	int m_nSepatatePartVar;

	void SetFlyPosition(unsigned int MapID,float X,float Y,unsigned int Type);
	void GetFlyPosition(unsigned int& MapID,float& X,float& Y);
	unsigned int GetLogType(){return LogType;}
private:
	unsigned int LogMapID;
	float LogX;
	float LogY;
	DWORD EndTime;
	unsigned int LogType;

private:
	unsigned int m_YuanBaoTotle;
	unsigned int m_YuanBaoStates;
public:
	unsigned int GetYuanBaoStates(){return m_YuanBaoStates;}
	void SetYuanBaoStates(unsigned int Value){m_YuanBaoStates = Value;}

	unsigned int GetYuanBaoTotle(){return m_YuanBaoTotle;}
	void SetYuanBaoTotle(unsigned int Value){m_YuanBaoTotle = Value;}

	__int64 GetBeginGameGeneralBattleTime(){return m_charinfo.otherdataclient.nBeginGameGeneralBattleTime;}
	void SetBeginGameGeneralBattleTime(__int64 Time){m_charinfo.otherdataclient.nBeginGameGeneralBattleTime = Time;}
//public:
//	SCompoundItem		*m_pCompound;
//	Skill Point
//		SCharSkill			*m_pSkillBag;
//
//	是否申请清除密码功能
//	bool				bIfApp_ClearPwd;
//
//	//强化背包
//	SIntensfyItem  *m_Intensify;
//	分解背包
//	SReduceItem *m_ReduceItem;
//	//解除绑定
//	SUnSoulBound *m_UnSoulBound;
//	//锁强化
//	SLockIntensify *m_sLockIntensify;
//	
//	struct S_SkillColdTime
//	{
//		S_SkillColdTime()
//		{
//			dwSkillColdStartTime = dwSkillColdTime = 0;
//		}
//		DWORD dwSkillColdStartTime;
//		DWORD dwSkillColdTime;
//	} m_stSkillColdTime[More_iMaxSkillKnown];
//
//	D3DXVECTOR3	m_Pos;
//	float m_f; //计算当前位置的系数
//	float m_fDistPerSecond;//每秒的位移
//
//public:
//	DWORD GetSmoothFrame();
//	void SetSmoothFrame( DWORD dwFrame );
//private:
//	DWORD m_dwSmoothFrame;

//private:
//	bool							m_bHitchMoving; //搭乘移动
//	std::vector<D3DXVECTOR3>		m_veHitchPath; //搭乘移动的路径点
//
//public:
//	bool							DoHitchMoving( char* pHitchPathFile ); //进行搭乘移动
//public:
//	//下滑时间
//	void SetStartSlipTime( DWORD dwtime );
//	DWORD GetStartSlipTime();
//	void SetSlipDir( float fX, float fY );
//	float GetSlipDirX();
//	float GetSlipDirY();
//private:
//	DWORD m_dwStartSlipTime;
//	float m_fSlipDirX;
//	float m_fSlipDirY;
//public:
//void   SetPower(short stPower);
//void   SetPowerPoint(short stPoint);
//short GetPower();
//short GetPowerPoint();

//private:
//	void		ApplySpecialAttr( int iWhichAttr,USpecialAttrValue *pValue,bool bAdd );
//	
//	当前技能
//	short int	m_iSkill;
//	下个动作的时间
//	DWORD		m_dwNextDoingTime;
//
//	移动序列号
//	char		m_cMoveSerial;
//	聚气
//	BOOL m_bIsCanPower;
//
//	int GetItemCount( unsigned short ustItemID )
//	{
//		return 1;
//	}
//
//	void SetCanPower(BOOL bFlag)
//	{
//		m_bIsCanPower = bFlag;
//	}
//	BOOL GetCanPower()
//	{
//		return m_bIsCanPower;
//	}
//
//	short				m_shTipsTexture[MAX_DUEL_TIPS];
};

extern CPlayerRole	thePlayerRole;
