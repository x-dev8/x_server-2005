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
#include "SystemMail.h"  //�ʼ�ϵͳ
#include "RelationDefine.h"
#include "GuildDefine.h"
#include "CampBattleDefine.h"
#include "QuestManager.h"
#include "SevenDays.h"

#define MAX_ITEM_COUNT	99
#define MAX_DUEL_TIPS 10
#define CHANGE_MAP_WAIT_TIME 20			// �е�ͼ����ʱ����λ��
#define ADD_TEACHER_STUDENT_MAX_DIST 10 // ��ʦ��ͽ������

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
	std::string  szName;  //����
	int nHp;	 
	int nMaxHp;
	int nMp;
	int nMaxMp;

//	bool		bCorps;
	bool		bOnline;
	bool		bHeader;		//�Ƿ��ӳ�,Ŀǰֻ�д�ӳ����߼�2009.10.12
	short		stManiple;		//�ڼ�С��
	unsigned char ucSex;		//�Ա�
	unsigned char usProfession; //ְҵ
	bool	use_flag;
	bool		bHeader2;			//С�Ӷӳ�

	int		nLvl;
	unsigned int nMapID;// modified, jiayi, [2009/11/25]
	int		x,y;
	float	fx,fy;
	bool	bIsNewAdd;                 //�Ƿ��¼���Ķ�Ա

	int nHairId; //ͷ��
	int nFaceId; //��
    int nHeadPicId; //ͷ��

	unsigned char    AssignMode; //����ģʽ lrt
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

//�û�����
class CPlayerRole
{
public:	

	enum enUpdataType
	{
		TYPE_PROFESSION,					// ְҵ
		TYPE_LEVEL,							// �ȼ�
		TYPE_EXP,							// ����
		TYPE_EXPNOTUSED,					// δ�þ���
		TYPR_SKILLEXP,						// ���ܾ���
		TYPR_SKILLEXPNOTUSE,				// δ�ü��ܾ���
		TYPE_Pkvalue,
		TYPE_ExPower,						// ����
		TYPE_Exploit,						// ��ѫ
		TYPE_Reputation,					// ����
		TYPE_Glory,							// ����
		TYPE_CountryScore,					// ��ս����
		TYPE_AreaRepulation,				// ��������
		TYPE_MONEY,							// Ǯ
		TYPE_Silver,						// ��
		TYPE_GLOD,							// �� 
		TYPE_JinDing,						// ��
		TYPE_JinPiao,						// ��Ʊ
		TYPE_TradeMoney,					// �˻��ʽ� ��Ǯ
		TYPE_TradeJinDing,					// �˻��ʽ� ��
		TYPE_JiaoZi,                        // �ʻ��ʽ� ����
		
		TYPE_HP,							// Ѫ
		TYPE_MP,							// ħ
		TYPE_HPRESTORE,						// ��Ѫ
		TYPE_MPRESTORE,						// ��ħ	
		TYPE_HPMAX,							// Ѫ����
		TYPE_MPMAX,							// ħ����
		TYPE_Strength,				     	// ����
		TYPE_Agility,					    // ����
		TYPE_Stamina,					    // ����
		TYPE_Intelligence,					// ����
		TYPE_ATTACKPHYSICS,					// ��������
		TYPE_AttackMagic,                   // ħ��������
		TYPE_DefendPhysics,					// �������
		TYPE_DefendMagic,					// ħ������
		TYPE_EXACT,							// ����
		TYPE_DODGE,							// ����
		TYPE_CRITICLE,						// ����
		TYPE_CRITICLEINTENSITY,				// ��������
		TYPE_TENACITY,						// ����
		TYPE_MOVESPEED,						// ����
		TYPE_ATTACKSPEED,					// ����

		TYPE_BackStrike,                    // �����˺�
		TYPE_BackStrikeResist,              // ��������
		TYPE_BreakStrike,                   // �Ƽ��˺�
		TYPE_StabStrike,                    // �ᴩ�˺�
		TYPE_ElementStrike,                 // Ԫ���˺�
		TYPE_ToxinStrike,                   // �����˺�
		TYPE_SpiritStrike,                  // �����˺�
		TYPE_BreakResist,                   // �Ƽ׿���
		TYPE_StabResist,                    // �ᴩ����
		TYPE_ElementResist,                 // Ԫ�ؿ���
		TYPE_ToxinResist,                   // ���ؿ���
		TYPE_SpiritResist,                  // ������


		TYPE_ENERGY,						// ����ֵ
		TYPE_ENERGY_MAX,
		TYPE_VIGOR,							// ����ֵ				
		TYPE_VIGOR_MAX,

        TYPE_CaoYao,                        // ��ҩ
        TYPE_ZhuBao,                        // �鱦
        TYPE_DuanZao,                       // ����
        TYPE_ZhuJia,                        // ����
        TYPE_GongYi,                        // ����
        TYPE_XunMa,                         // ѱ��
        TYPE_CaiKuang,                      // �ɿ�
        TYPE_CaiYao,                        // ��ҩ
        TYPE_BuChong,                       // ����
        TYPE_BuZhuo,                        // ��׽     (���������)
        TYPE_Storage,                       //�ֿ�
		TYPE_PetSrorage,                    //����ֿ�

		TYPE_FreeReliveCount,			   // �����Ѿ������˶��ٴ�

		TYPE_Daoxing,                       // ��ǰ����
		TYPE_CurGetDaoxing,                 // ��ǰ��õ���
		TYPE_BasePotential,                 //��ǰǱ����
		TYPE_ShopCenterScore,               //lyh++ �̳ǻ���
	};

	// ����״̬
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
		__int64 time; //����ʼʱ��
		//
		// 		bool bReqInfoed;
	};

	// ����Ի��ı�ʾλ
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
		// ����id
		int m_nQuestId;
		// ״̬
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

	// ��ö���ֵ
	short				GetExPower(){ return m_charinfo.baseinfo.liveinfo.nXp; }
	//������ز�������
	short				GetSkillLevel( short stSkillIndex );
	short				GetSkillLevelById( short stSkillId );
	void				SetSkillLevel( short stSkillIndex, short stNewLevel );
	//�Լ��ܽ��з�����֯
	void				ReOrganizeSkill( );	
	//
	bool				IsCanEquip(SCharItem *pItem);
	bool				IsCanEquip(SCharItem *pItem, ItemDefine::TagEquipRequest *pEquipReq);
	//ȡ��
	int					GetMyHP(void);
	int					GetMyMP(void);
	//short				GetTP(void);

	void				SetCountry( int iCountry );
	int					GetCountry( void );

	//���ý�ɫ����
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

	//װ������
	int					GetEquipBagItemCount(const int BagIndex);

	void				FreshEquipData( SCharAttributeUpdate* pFightData );				//ˢ��װ������
	bool				Equip( const SCharItem* pCharItem, const int nWhere );			// װ��
	bool				UnEquip( const int nWhere );									// ж��
	bool				Update( enUpdataType enType, const double dwValue );			// ������������
	DWORD				GetData( enUpdataType enType );                                // �����������
	void				UpdateUI();														// ���½���
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

    // ���ﾭ��  added by zhuomeng.hu		[10/9/2010]
    int64               GetExp()         { return m_pBaseInfo->liveinfo.dwExp; }
    int64               GetExpNotUsed()  { return m_pBaseInfo->liveinfo.dwExpNotUsed; }
    void                SetExpNotUsed( int64 exp ){ m_pBaseInfo->liveinfo.dwExpNotUsed = exp; }

	void				SetWeekKillSum(uint32 num);
	void				SetAllKillSum(uint32 num);
	uint32				GetAllKillSum();
	uint32				GetWeekKillSum();

	//���ܵ���
	uint32 GetSkillExp(){return m_pBaseInfo->liveinfo.dwSkillExp;}
	uint32 GetSkillExpNotUsed(){return m_pBaseInfo->liveinfo.dwSkillExpNotUsed;}
	void SetSkillExpNotUsed(uint32 exp){m_pBaseInfo->liveinfo.dwSkillExpNotUsed = exp;}

	float GetBaseSpeed(){return m_pBaseInfo->baseProperty.fightAttr.moveSpeed.base;}
	//bool				IsFriend( short stCharID,int iCharType,int iTeamID = -1,int iGuildID = -1 );	//���ݽ�ɫ�����ж��Ƿ����ǵ�����
	void				UpdateArmourUI();												// ���½����е���װ��Ϣ
	unsigned char		GetSex( ){ return m_pBaseInfo->aptotic.ucSex; }					//ȡ���Ա�
	unsigned char		GetProfession( ){ return m_pBaseInfo->aptotic.usProfession;	}	//���ְҵ
	const SCharItem*	GetEquipItem( short stPart ){ return &(m_pVisual->equipitem[stPart]); }	//��õ���

	BOOL				IsDie();

	int					GetValidFreeReliveCount();// ��ǰ�����Ը���Ĵ���

	bool				IsFinishedIntroduce( int id );
	void				SetFinishedIntroduce( int id );

	//ȡ�����ǵ�����״̬
	//	short				GetBuff(void);
protected:
	void HPChanged();
	void MPChanged();

public:
	//��ɫ����
	SCharInfoClient		m_charinfo;
	SBaseProperty		m_charLastBaseProperty;		//����ǰһ������
	//��شӲֿ�ȡ����շѷ���
	float				fCostOfFetchItem[STORAGE_ITEMGRID_MAX];
	//�ֿ��������
	char				CityName[STORAGE_ITEMGRID_MAX][MAX_NAME_STRING];
	//��Ʒ��������
	char				szItem_PWD [PWD_OF_ITEM];
	// ���＼��
	SCharSkill			m_MountSkill[ More_iMaxSkillKnown ];
	SkillBag			m_MountSkillBag;
	//װ��
	SCharVisual			*m_pVisual;
	//��������
	SCharBaseInfo		*m_pBaseInfo;
	CEquipmentDoll		m_doll;
private:
	// ��̬ID
	GameObjectId	    m_nID;
	//��ɫDB ID 
	DWORD				m_dwPlayerDBID;
	// ���Ըı����Ҫ���½���
	bool				m_bUpdateUI;

    //--------------------------------------------------------------
    //------------------------- ���� -------------------------------
public:
    void SetWeakCountry( int iCountry );
	void SetStrongCountry( int iCountry );
    bool IsInWeakCountry();
	bool IsInStrongCountry();
	int  GetWeakCountryID(){return m_nWeakCountryId;}
	int	 GetStrongthCountryID(){return m_nStrongCountryId;}
private:
    int                 m_nWeakCountryId;       // ��������ID
	int					m_nStrongCountryId;		// ǿ������ID

	//--------------------------------------------------------------
	//------------------------- ���� -------------------------------
public:
	CItemBag2			m_bag;
	CItemBag2			m_bagMaterial;
	CItemBag2			m_bagTask;
	SkillBag			m_SkillBag;
	SkillBag			m_HeroSkillBag;
	XinFaManager m_xinFaBag;
	// added, jiayi, [2009/9/11]
	// ͨ��guid��ð������ݣ��������ְ���
	bool				GetBagItemByGUID( __int64 nGUID, SCharItem* pItem );
	bool				GetBagTypeByItemGUID( __int64 nGUID, EBagType& eType, int* pIndex = 0 );		
	bool				GetBagByItemGUID( __int64 nGUID, CItemBag2*& pBag );
	int                 GetBagTypeByItemType( int nItemType );              //added by ZhuoMeng.Hu		[1/17/2011]
	CItemBag2*			GetBagByItemType(int nItemType);
	CItemBag2*			GetBagByItemID(unsigned int ItemID);
	//--------------------------------------------------------------
	//------------------------- �ֿ� -------------------------------
public:
    bool				GetStorageItemByGUID( __int64 nGUID, SCharItem* pItem );
    bool                GetStorageMountByGUID( __int64 nGUID, SMountItem* pItem );
	void				SetNpcID(int id) { m_nNpcID = id; }
	int					GetNpcID() { return m_nNpcID; }
	SCharStorageData	m_stStorage;								// �ֿ�����
	void				SetIsSecondPassword( bool b );				// �ֿ��������
	bool				GetIsSecondPassword();
	void				SetSecondPasswordUnlockTime( uint32 time );
	uint32				GetSecondPasswordUnlockTime();
private:
	int					m_nNpcID;									// �ֿ�NPC
	BOOL				m_bSecondPassword;							//�ֿ��������
	uint32				m_nSecondPasswordUnlockTime;				//�ֿ�������ʣ��ʱ��

	//--------------------------------------------------------------
	//------------------------ ��ݼ� ------------------------------
public:
	//------ ��ݱ�����ű�� ά���߻���ͣ�ĸ��ı仯 -------------- |  0--5  ��չ������� s_CUI_ID_FRAME_Exmain.m_pID_LISTIMG_exmain
	//HotKey Point													|  6--9  û��
	SMouseItem			m_pHotKeyBag[More_iHotkey];	//��ݱ���		| 10--27 �������� s_CUI_ID_FRAME_MAIN.m_pID_LISTIMG_Hotkey(0,1,2����6��)
	//																| 28	 �Ҽ������ s_CUI_ID_FRAME_SelectSkill.m_pID_LISTIMG_skill
	//															    | ����	enumConst::More_iHotkey ��Ϊ29 
	void				InitHotKey();
	void				SendHotKeyToServer();
	void				refreshHotKey();							// ���¿�ݼ�


	//--------------------------------------------------------------
	//------------------------ ������� ----------------------------
public:
	void				RefreshQuestDone();
	std::vector<QuestInfo*>& GetActiveQuestInfo(){ return m_vectorActiveQuestInfo; }
	void				FillRequirementQuestArr();
	// added, jiayi, [2009/9/22], ������Ϣ�Ƿ���ȫ������
	bool				IsQuestInitialized();
	void				QuestInfoInitialized();
	// ��������״̬
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
	// ����Ի�-���û���������ĶԻ�״̬������ӣ�������ˣ���ˢ�¡�
	// stValue�Ǻϳ�ֵ����Ҫ�ֽ⴦��
	void				RefreshTalkStates( int nQuestId, short stValue );
	// ����Ի�-��������id��״̬���ͣ�����״ֵ̬
	bool				GetTalkStates( int nQuestId, int nType );
private:
	typedef std::map<int, QuestInfo> QuestInfos;
	QuestInfos			m_VariableInfos;
	QuestInfos			m_questInfos;
	std::vector<QuestInfo*> m_vectorActiveQuestInfo;					// ��ǰ���е�����
	std::vector<int>	m_vectorRequirementVariableQuestId;				// ����ǰ������
	std::vector<int>	m_vectorRequirementItemQuestId;					// ��Ʒǰ������
	bool				m_bQuestInitialized;
	QuestTalkStates		m_QuestTalkStates;

	//--------------------------------------------------------------
	//------------------------ ������� ----------------------------
public:
	//��Ҫ�ṩ��������ʾʹ�ã�
	int					GetNormalSkillNum( ){ return m_iNormalSkillNum; }
	int					GetNormalSkillIndex( int iIndex ){ return m_iNormalSkillIndexArray[iIndex];	}
	int					GetMagicSkillNum( ){ return m_iMagicSkillNum; }
	int					GetMagicSkillIndex( int iIndex ){ return m_iMagicSkillIndexArray[iIndex]; }
private:
	int					m_iNormalSkillNum;								//��ͨ���ܵĸ���
	int					m_iNormalSkillIndexArray[More_iMaxSkillKnown];	//�����ͨ��������������
	int					m_iMagicSkillNum;								//ħ�����ܵĸ���
	int					m_iMagicSkillIndexArray[More_iMaxSkillKnown];	//���ħ����������������



	//--------------------------------------------------------------
	//------------------------- �ƺ� -------------------------------
public:
	void				SetTitleListInfo( SCharBaseInfo::SCharLiveInfo* pMsg );
	void				AddNewTitleId( short stId,__int64 n64AcquireTime,uint32 nActiveTime);
	void				RemoveTitleId( short stId );
	const std::vector<TitleData>& GetTitleArray() const	{ return m_vTitleArray;	}
private:
	std::vector<TitleData> m_vTitleArray;


	//--------------------------------------------------------------
	//------------------------- ���� -------------------------------
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
	// ��������ò��û����
	int					m_nCompoundRateAdd;
	int					m_nIntensifyRateAdd;

	// �̳�
	int					m_nShopCenterOffSell;
	//--------------------------------------------------------------
	//------------------------- �д� -------------------------------
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
	GameObjectId				m_shDuelTarget;									// �д����
	char				m_szDuelName[dr_MaxPlayerName];					// �д��������
	D3DXVECTOR3			m_vDuelPos;										// �д�λ��
	unsigned int		m_nDuelTime;
	bool				m_bDuelTipsLoaded;
	int					m_iDuelMapID;
	int					m_nSelfOutTime;									// �����д跶Χ��ʱ
	int					m_nDuelOutTime;


public:
    //--------------------------------------------------------------
	//-------------------------����������	------------------------
	std::vector<TeamInfo>	m_TeamData;									//����������ѵ�����
	BOOL				m_bCorps;										//�Ƿ����Ŷ�
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
	void				OnAddTeamMember(TeamInfo &InInfo);				//���Ӷ���
	void				OnDeleteTeamMember(int nID);					//ɾ������
	void				UpdataPlayerInfo( TeamInfo &InInfo, BOOL OnlyRefeashHPUI = FALSE );
	void				OnExitTeam(void);								//�뿪����
	void				ClearTeam()		{ m_TeamData.clear(); }
	void				SetGroupId( int id )				{ m_GroupId = id; }
	int					GetGroupId() const					{ return m_GroupId; }
private:
	int					m_GroupId;										// ����ID


	//--------------------------------------------------------------
    //---------------------------����ģʽ---------------------------
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
    //��ƷƷ��
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
	short               m_shItemRollLevel;								// �����ӵ���ƷƷ��
	short               m_shAssignMode;									// ����ģʽ


public:
	//-------------------------		-----------------------------------------------------------------------
	//ʹ�ûָ�ҩƷ
	void				OnRestoreItem(int ItemID, int TagNpcID);
	//ʹ�û�������
	void				OnBaseAction(int ItemID, int TagNpcID);
	//��Ⱥ����
	void				OnCorporation(int ItemID, int TagNpcID);
	//�罻����
	void				OnSociality(int ItemID, int TagNpcID);
	//	���ɱ����е��ߵ�ע��
//	bool				CreateBagItemDesc(int iBagType, int iBagIndex, char (*pString)[256], DWORD* pdwColor, int iMaxLineNum, int* pFactLineNum);
	//	�ж�ʹ�õļ����Ƿ�����
	BOOL				IsSkillCanUse( ItemDefine::SItemSkill* pSkill );
	bool				IsSkillCanUse(int iSkillID, int iSkillLevel);
	//����������ϵ�Ǯ
	void				SetMoneyOnPlayer(DWORD dwMoney );
	//SCharSkill*		GetSkill( int iSkillID)


	//--------------------------------------------------------------
	//---------------------- �����ƶ� ------------------------------
public:
	void				StartMoving( GameObjectId id, DWORD dwStartingTime, float x, float y, float z, float DirX, float DirY, short shMovingType );
	void				SendMoveMessage( GameObjectId id, float x, float y, float z, float DirX, float DirY, DWORD dwCurTime, BOOL bMoving, short shMovingType, BOOL bLastFrameMoving );
	BOOL				CanSendMoveMessage( DWORD dwCurTime );
	BOOL				IsCollectPos();
	BOOL				CanSendActionMessage();
	void				SetLastStopMovingTime(DWORD time) { m_dwLastStopMovingTime = time; }
	DWORD				GetLastStopMovingTime() { return m_dwLastStopMovingTime; }
	// �ظ��������������ײ����룬bNeedAdjust����FALSE������Ҫ�κξ���
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
    BOOL				m_bNeedSendLastPos;								// ����ͣ�º���Ҫ�ٷ�һ��λ����Ϣ

	BOOL				m_bStartCollectPos;
	DWORD				m_dwStartCollectPosTime;						//��ʼ��¼������ʱ��
	BOOL				m_bCanSendActionMessage;						//�Ƿ���Է��Ͷ�����Ϣ
	DWORD				m_dwLastStopMovingTime;							//����ƶ���ʱ��
	BOOL				m_bMustSendMovingMessage;						//��һ���ƶ����������ȵڶ�֡���﷽����ȷ���ٷ�


	//--------------------------------------------------------------
	//---------------------- ���⼼�� ------------------------------
public:
	BOOL				CanUseSpecialSkill();
	void				SetCanUseSpecialSkill( BOOL bCan );
private:
	BOOL				m_bCanUseSpecialSkill;


	//--------------------------------------------------------------
	//---------------------- ս��״̬ ------------------------------
public:
	bool				IsFighting(){ return m_bFighting; }
	void				SetFighting( bool b ){ m_bFighting = b; }
	void				CheckFight();
private:
	bool				m_bFighting;


	//--------------------------------------------------------------
	//---------------------- ��ͼ��ת ------------------------------
public:
	// �������ж��Ƿ�����͵�[QL]
	bool				IsInTransport( float posx, float posy, int& nMapId, int& nTargetId, int& nEntranceId );
	void				SetCanChangeMap(bool v) { m_bWaitforTransport = !v; }
	bool				GetCanChangeMap() const { return !m_bWaitforTransport; }   // ���ͳ�ʱ���������߳���������m_bWaitforTransport��ֵ��false
    bool				IsShowingWaitforTransport() { return m_bShowingWaitforTransport; }
    void				CloseShowingWaitforTransport() { m_bShowingWaitforTransport = false; }
	void				SetShowingWaitforTransport(bool IsShow){m_bShowingWaitforTransport =IsShow; }
private:
	bool				m_bWaitforTransport;							// �Ѿ�������ת���󣬱����ظ�����
    bool				m_bShowingWaitforTransport;						// �Ƿ�������ʾ�ȴ���ת��ʾ


	//--------------------------------------------------------------
	//----------------------- ��ƷCD -------------------------------
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
	//------------------------ ��� --------------------------------
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
	//-----------------------����-----------------------------------
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
	//------------------------ ��� --------------------------------
public:
    // ��ͭת�ɽ���ͭ GSC: GoldSilverCopper
    void				GetGSCFromMoney(DWORD inputMoney, int& iGold, int& iSilver, int& iCopper);
    void				GetGSCStringFromMoney(DWORD inputMoney, std::string& strText);		// �ӽ�Ǯ���string��ʾ
	void				GetGSCStringFromCurrentMoney(std::string& strText);					// �ӵ�ǰ�������һ��string
	// ����
	void				GetGSCStringFromJiaoZi(DWORD inputJiaoZi, std::string& strText);	// �ӽ��ӻ��string��ʾ
	void				GetGSCStringFromCurrentJiaoZi(std::string& strText);	// �ӵ�ǰ�������ӻ��string��ʾ
    DWORD				GetMoneyFromGSC(int iGold, int iSilver, int iCopper);
    // ������Ǯ������
    bool				PackHasEnoughMoney(int iGold, int iSilver, int iCopper);
    bool				PackHasEnoughMoney(DWORD dwMoney);
    // �ֿ���Ǯ������
    bool				StorageHasEnoughMoney(int iGold, int iSilver, int iCopper);
    bool				StorageHasEnoughMoney(DWORD dwMoney);

    void				SetStorageMoney(DWORD dwMoney) { m_stStorage.dwStorageMoney = dwMoney; }

    bool                HaveEnoughMoney(DWORD dwMoney);
public:
	void				SetTradeGold( uint32 gold ){ m_nTradeGold = gold; }
	void				SetTradeMoney( uint32 money ){ m_nTradeMoney = money; }
private:
	uint32				m_nTradeGold;									//�˻��ʽ��
	uint32				m_nTradeMoney;									//�˻��ʽ��Ǯ


	//--------------------------------------------------------------
	//----------------------- ���� ---------------------------------
public:
	DWORD   			GetBanSpeakEndingTime() { return m_dwBanSpeakEndingTime; }
	void    			SetBanSpeakEndingTime(DWORD time) { m_dwBanSpeakEndingTime = time; }
protected:
    DWORD				m_dwBanSpeakEndingTime;							// ���Խ���ʱ�䣨���룩


	//--------------------------------------------------------------
	//-------- �Ƿ���յ�������Ϣ���ȴ�����ȥ���� ------------------
public:
    void 				SetIsReliveAndWaitingToHell(BOOL bflag) { m_bIsReliveAndWaitingToHell = bflag; }
    BOOL 				IsReliveAndWaitingToHell() { return m_bIsReliveAndWaitingToHell; }
protected:
	BOOL				m_bIsReliveAndWaitingToHell;


	//--------------------------------------------------------------
    //----------------------- ��̬��ͼID ---------------------------
public:
    void				SetGameMapId(DWORD nGameMapId) { m_dwGameMapId = nGameMapId; }
    DWORD				GetGameMapId() { return m_dwGameMapId; }
protected:
    DWORD				m_dwGameMapId;


	//--------------------------------------------------------------
	//----------------------- ��װ������ ---------------------------
public:
	SuitManager			suitManager;


	//--------------------------------------------------------------
	// �Ƿ���ҹ���
	bool				m_isPlayerHitMe;
	// ����ҹ���ͼƬ��ǰ�Ŀ�ʼʱ��
	DWORD				m_dwPlayerHitMeAlphaStartTime;


	//--------------------------------------------------------------
	//------------------------ ��Ʒ�� ------------------------------
public:
	int					GetLockNum() { return m_nLockNum; }
	void 				SetLockNum(int num) { m_nLockNum = num; }
	void 				SetLockNumMax(int max) { m_nLockNumMax = max; }
	bool 				IsLockNumLimit() { return (m_nLockNum >= m_nLockNumMax); }
	void 				UpdateLockItem();								//������Ʒ����Ϣ
protected:
	int 				m_nLockNum;										//����������
	int 				m_nLockNumMax;
	float 				m_fUpdateLockItemTime;							// ����������ʱ��
	float 				m_fUnLockTimeCount;
	float 				m_UnLockTimeCount;


	//--------------------------------------------------------------
	//---------------------- �ʼ�ϵͳ ------------------------------
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
    CSystemMail			m_SysMail;  //�ʼ�ϵͳ


	//--------------------------------------------------------------
	//------------------- С��ս�� ---------------------------------
public:
    bool				IsTeamBattleInMap();

	//--------------------------------------------------------------
	//��Ӫս
private:
	unsigned char m_nInfluence; // ��Ӫ
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

	int  				GetdbID(const char* szName);		//ͨ�����ֵõ�����id
	const char*			GetNameByDBID(uint32 uiDBID);		// ����DBID��ú�������
	bool 				IsOnline( const char* szName);		//�������Ƿ�����
	bool 				IsFriend(const char* szName);		//�Ƿ����
	bool 				IsTempFriend(const char* szName);		//�Ƿ�temp����
	bool 				IsPlayerLock(const char* szName);		//�Ƿ�����
	bool 				CanAddFriend(const char* szName);	//�Ƿ���ѣ��������������
	bool 				CheckNewFriendName(const char* szName, bool onlyCheck = true);
	bool 				CheckNewBlackName(const char* szName);
	bool 				isFrdInBlackList(uint32 nDBId);	//by DB Id
	bool 				isFrdInBlackList(const char* name);
	bool 				isChouRen(const char* name);
    const char*			GetMarryerName();					//�����ż������

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
	char szSignature[ RelationDefine::MaxSignLength ];      // ����ǩ��
	RelationGroup xGroup[ RelationDefine::GroupCount ];     // ������Ϣ

	//--------------------------------------------------------------
	//--------------------- ʦͽ -----------------------------------
public:
	bool				IsCanReceivePrentice();
	void				SetCanReceivePrentice();
	// ʦͽ���Ըı�
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
	void				CalculateTeacherStudent(bool& hasTeacher, int& iStudentNum);	// ��ʾ�Ҽ��˵�������ʾʦͽ����ʱ����Ҫ�������¼���ʦͽ���
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
	//---------------------- С�Ӽ��� ------------------------------
public:
	struct PlayerTeamSkill
	{
		unsigned int nSkillID;
		unsigned char uchLevel;
	};
	typedef std::vector< PlayerTeamSkill > PlayerTeamSkillVector;

	const PlayerTeamSkillVector* GetTeamSkillVector();
	void				CalcTeamSkillLevel();					// �Ӷ�Ա�ɹ����Ƴ���Աʱ����
protected:
	PlayerTeamSkillVector m_pVecTeamSkill;
	float				m_fCalcTeamSkillCD;						// ÿn��ˢ��С�Ӽ��ܣ���λ�룬nĬ��2


	//--------------------------------------------------------------
	//---------------- ����ң���Ծ�߶���֤ ------------------------
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
	bool 				m_bRoleJump;							// ���ո����Ծ


	//--------------------------------------------------------------
	//---------------- ̫ƽ�þ�			    ------------------------
public:
	bool				IsInTPHJ(){return m_charinfo.otherdataclient.sBornPos.dwMapID != 1;}
	SCharPosData		GetPrePosition(){return m_charinfo.otherdataclient.sBornPos;}
	void				SetPrePosition(SCharPosData pos){m_charinfo.otherdataclient.sBornPos = pos;}
	char				GetTPHJRank(){return m_charinfo.baseinfo.liveinfo.TPHJRank;}
	void				SetTPHJRank(char value,int operType=EOT_Set);
	//--------------------------------------------------------------
	//---------------- ��������				------------------------
	void				SetHeroAddAttr(SCharHeroInfo heroAttr);
	void				ShowHeroAttrInfo();

	//�ջ�����
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

	//---------------- ������				------------------------
public:
	short m_taskState[SevenDaysConfig::TD_Max];
	short m_taskVar[SevenDaysConfig::TD_Max];

	//---------------- ����var				------------------------
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
//	�Ƿ�����������빦��
//	bool				bIfApp_ClearPwd;
//
//	//ǿ������
//	SIntensfyItem  *m_Intensify;
//	�ֽⱳ��
//	SReduceItem *m_ReduceItem;
//	//�����
//	SUnSoulBound *m_UnSoulBound;
//	//��ǿ��
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
//	float m_f; //���㵱ǰλ�õ�ϵ��
//	float m_fDistPerSecond;//ÿ���λ��
//
//public:
//	DWORD GetSmoothFrame();
//	void SetSmoothFrame( DWORD dwFrame );
//private:
//	DWORD m_dwSmoothFrame;

//private:
//	bool							m_bHitchMoving; //����ƶ�
//	std::vector<D3DXVECTOR3>		m_veHitchPath; //����ƶ���·����
//
//public:
//	bool							DoHitchMoving( char* pHitchPathFile ); //���д���ƶ�
//public:
//	//�»�ʱ��
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
//	��ǰ����
//	short int	m_iSkill;
//	�¸�������ʱ��
//	DWORD		m_dwNextDoingTime;
//
//	�ƶ����к�
//	char		m_cMoveSerial;
//	����
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
