/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\AutoAttackSet.h
*********************************************************************/


/*
 *	Author 2012-9-15 zhuxincong
 *	DESC: ID_BUTTON_ProtectionStop ID_BUTTON_ProtectionBegin 这两个按钮是为来不在挂机的时候也能吃喝药水，类似战斗保护的功能
 */

#pragma once
#include "MeUi/MeUi.h"
#include "ItemDetail.h"
#include "MsgBase.h"
#include "Player.h"

#ifndef ID_FRAME_AutoAttackSet
#define ID_FRAME_AutoAttackSet		"ID_FRAME_AutoAttackSet"
#endif  ID_FRAME_AutoAttackSet
#ifndef ID_PICTURE_Tip1
#define ID_PICTURE_Tip1		"ID_PICTURE_Tip1"
#endif  ID_PICTURE_Tip1
#ifndef ID_PICTURE_Tip2
#define ID_PICTURE_Tip2		"ID_PICTURE_Tip2"
#endif  ID_PICTURE_Tip2
#ifndef ID_PICTURE_Tip3
#define ID_PICTURE_Tip3		"ID_PICTURE_Tip3"
#endif  ID_PICTURE_Tip3
#ifndef ID_TEXT_UseItemZ
#define ID_TEXT_UseItemZ		"ID_TEXT_UseItemZ"
#endif  ID_TEXT_UseItemZ
#ifndef ID_CHECKBOX_PickItem
#define ID_CHECKBOX_PickItem		"ID_CHECKBOX_PickItem"
#endif  ID_CHECKBOX_PickItem
#ifndef ID_CHECKBOX_SUODING
#define ID_CHECKBOX_SUODING		"ID_CHECKBOX_SUODING"
#endif  ID_CHECKBOX_SUODING
#ifndef ID_TEXT_PickItemZ
#define ID_TEXT_PickItemZ		"ID_TEXT_PickItemZ"
#endif  ID_TEXT_PickItemZ
#ifndef ID_CHECKBOX_Advance
#define ID_CHECKBOX_Advance		"ID_CHECKBOX_Advance"
#endif  ID_CHECKBOX_Advance
#ifndef ID_TEXT_HpZ
#define ID_TEXT_HpZ		"ID_TEXT_HpZ"
#endif  ID_TEXT_HpZ
#ifndef ID_EDIT_Hp
#define ID_EDIT_Hp		"ID_EDIT_Hp"
#endif  ID_EDIT_Hp
#ifndef ID_TEXT_HpZ2
#define ID_TEXT_HpZ2		"ID_TEXT_HpZ2"
#endif  ID_TEXT_HpZ2
#ifndef ID_LISTIMG_SkillAttack
#define ID_LISTIMG_SkillAttack		"ID_LISTIMG_SkillAttack"
#endif  ID_LISTIMG_SkillAttack
#ifndef ID_TEXT_MpZ
#define ID_TEXT_MpZ		"ID_TEXT_MpZ"
#endif  ID_TEXT_MpZ
#ifndef ID_EDIT_Mp
#define ID_EDIT_Mp		"ID_EDIT_Mp"
#endif  ID_EDIT_Mp
#ifndef ID_TEXT_MpZ2
#define ID_TEXT_MpZ2		"ID_TEXT_MpZ2"
#endif  ID_TEXT_MpZ2
#ifndef ID_TEXT_AutoAttackZ
#define ID_TEXT_AutoAttackZ		"ID_TEXT_AutoAttackZ"
#endif  ID_TEXT_AutoAttackZ
#ifndef ID_CHECKBOX_AutoAttack
#define ID_CHECKBOX_AutoAttack		"ID_CHECKBOX_AutoAttack"
#endif  ID_CHECKBOX_AutoAttack
#ifndef ID_TEXT_SkillAttackZ
#define ID_TEXT_SkillAttackZ		"ID_TEXT_SkillAttackZ"
#endif  ID_TEXT_SkillAttackZ
#ifndef ID_TEXT_SkillBuffZ
#define ID_TEXT_SkillBuffZ		"ID_TEXT_SkillBuffZ"
#endif  ID_TEXT_SkillBuffZ
#ifndef ID_LISTIMG_SkillBuff
#define ID_LISTIMG_SkillBuff		"ID_LISTIMG_SkillBuff"
#endif  ID_LISTIMG_SkillBuff
#ifndef ID_LISTIMG_Hp
#define ID_LISTIMG_Hp		"ID_LISTIMG_Hp"
#endif  ID_LISTIMG_Hp
#ifndef ID_LISTIMG_Mp
#define ID_LISTIMG_Mp		"ID_LISTIMG_Mp"
#endif  ID_LISTIMG_Mp
#ifndef ID_BUTTON_Begin
#define ID_BUTTON_Begin		"ID_BUTTON_Begin"
#endif  ID_BUTTON_Begin
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_BUTTON_Stop
#define ID_BUTTON_Stop		"ID_BUTTON_Stop"
#endif  ID_BUTTON_Stop
#ifndef ID_PICTURE_TitleWord
#define ID_PICTURE_TitleWord		"ID_PICTURE_TitleWord"
#endif  ID_PICTURE_TitleWord
#ifndef ID_EDIT_SkillHp
#define ID_EDIT_SkillHp		"ID_EDIT_SkillHp"
#endif  ID_EDIT_SkillHp
#ifndef ID_LISTIMG_SkillHp
#define ID_LISTIMG_SkillHp		"ID_LISTIMG_SkillHp"
#endif  ID_LISTIMG_SkillHp
#ifndef ID_CHECKBOX_Hp
#define ID_CHECKBOX_Hp		"ID_CHECKBOX_Hp"
#endif  ID_CHECKBOX_Hp
#ifndef ID_CHECKBOX_Mp
#define ID_CHECKBOX_Mp		"ID_CHECKBOX_Mp"
#endif  ID_CHECKBOX_Mp
#ifndef ID_CHECKBOX_Tp
#define ID_CHECKBOX_Tp		"ID_CHECKBOX_Tp"
#endif  ID_CHECKBOX_Tp
#ifndef ID_CHECKBOX_Back
#define ID_CHECKBOX_Back		"ID_CHECKBOX_Back"
#endif  ID_CHECKBOX_Back
#ifndef ID_EDIT_Hp
#define ID_EDIT_Hp		"ID_EDIT_Hp"
#endif  ID_EDIT_Hp
#ifndef ID_EDIT_Mp
#define ID_EDIT_Mp		"ID_EDIT_Mp"
#endif  ID_EDIT_Mp
#ifndef ID_EDIT_BackHp
#define ID_EDIT_BackHp		"ID_EDIT_BackHp"
#endif  ID_EDIT_BackHp
#ifndef ID_BUTTON_Renovate
#define ID_BUTTON_Renovate		"ID_BUTTON_Renovate"
#endif  ID_BUTTON_Renovate
#ifndef ID_BUTTON_Reverse
#define ID_BUTTON_Reverse		"ID_BUTTON_Reverse"
#endif  ID_BUTTON_Reverse
#ifndef ID_BUTTON_All
#define ID_BUTTON_All		"ID_BUTTON_All"
#endif  ID_BUTTON_All
#ifndef ID_LIST_Monster
#define ID_LIST_Monster		"ID_LIST_Monster"
#endif  ID_LIST_Monster
#ifndef ID_CHECKBOX_Normal
#define ID_CHECKBOX_Normal		"ID_CHECKBOX_Normal"
#endif  ID_CHECKBOX_Normal
#ifndef ID_CHECKBOX_Big
#define ID_CHECKBOX_Big		"ID_CHECKBOX_Big"
#endif  ID_CHECKBOX_Big
#ifndef ID_CHECKBOX_Small
#define ID_CHECKBOX_Small		"ID_CHECKBOX_Small"
#endif  ID_CHECKBOX_Small
#ifndef ID_CHECKBOX_PickEquip
#define ID_CHECKBOX_PickEquip		"ID_CHECKBOX_PickEquip"
#endif  ID_CHECKBOX_PickEquip
#ifndef ID_CHECKBOX_PickMaterial
#define ID_CHECKBOX_PickMaterial		"ID_CHECKBOX_PickMaterial"
#endif  ID_CHECKBOX_PickMaterial
#ifndef ID_CHECKBOX_PickMedicine
#define ID_CHECKBOX_PickMedicine		"ID_CHECKBOX_PickMedicine"
#endif  ID_CHECKBOX_PickMedicine
#ifndef ID_CHECKBOX_PickOther
#define ID_CHECKBOX_PickOther		"ID_CHECKBOX_PickOther"
#endif  ID_CHECKBOX_PickOther
#ifndef ID_CHECKBOX_Team1
#define ID_CHECKBOX_Team1		"ID_CHECKBOX_Team1"
#endif  ID_CHECKBOX_Team1
#ifndef ID_CHECKBOX_Team2
#define ID_CHECKBOX_Team2		"ID_CHECKBOX_Team2"
#endif  ID_CHECKBOX_Team2
#ifndef ID_CHECKBOX_Setting1
#define ID_CHECKBOX_Setting1		"ID_CHECKBOX_Setting1"
#endif  ID_CHECKBOX_Setting1
#ifndef ID_CHECKBOX_Setting2
#define ID_CHECKBOX_Setting2		"ID_CHECKBOX_Setting2"
#endif  ID_CHECKBOX_Setting2
#ifndef ID_BUTTON_Default
#define ID_BUTTON_Default		"ID_BUTTON_Default"
#endif  ID_BUTTON_Default
#ifndef ID_BUTTON_Save
#define ID_BUTTON_Save		"ID_BUTTON_Save"
#endif  ID_BUTTON_Save
#ifndef ID_TEXT_TimeText
#define ID_TEXT_TimeText		"ID_TEXT_TimeText"
#endif  ID_TEXT_TimeText
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time
#ifndef ID_CHECKBOX_Energy
#define ID_CHECKBOX_Energy		"ID_CHECKBOX_Energy"
#endif  ID_CHECKBOX_Energy
#ifndef ID_CHECKBOX_TeamNeed
#define ID_CHECKBOX_TeamNeed		"ID_CHECKBOX_TeamNeed"
#endif  ID_CHECKBOX_TeamNeed
#ifndef ID_BUTTON_ProtectionBegin 
#define ID_BUTTON_ProtectionBegin	"ID_BUTTON_ProtectionBegin"  
#endif
#ifndef ID_BUTTON_ProtectionStop 
#define ID_BUTTON_ProtectionStop	"ID_BUTTON_ProtectionStop"
#endif
#ifndef ID_BUTTON_PickOn
#define ID_BUTTON_PickOn			"ID_BUTTON_PickOn"
#endif
#ifndef ID_BUTTON_PickOff
#define ID_BUTTON_PickOff			"ID_BUTTON_PickOff"
#endif
//辅助加血模式
#ifndef ID_CHECKBOX_IsCheckHpTeam
#define ID_CHECKBOX_IsCheckHpTeam		"ID_CHECKBOX_IsCheckHpTeam"
#endif  ID_CHECKBOX_IsCheckHpTeam
#ifndef ID_EDIT_TeamSkillHp
#define ID_EDIT_TeamSkillHp		"ID_EDIT_TeamSkillHp"
#endif  ID_EDIT_TeamSkillHp
#ifndef ID_LISTIMG_SkillHpTeam
#define ID_LISTIMG_SkillHpTeam		"ID_LISTIMG_SkillHpTeam"
#endif  ID_LISTIMG_SkillHpTeam





enum AutoState
{
    Enum_Pick   = 0x0000,      //拾取
    Enum_Attack = 0x0001,      //攻击
    Enum_Wait    = 0x002,      //等待状态,这个状态的作用，主要为了让自动挂机看起来更平滑些，客户端处理速度比网络消息快的多。所有需要设置等待状态
    //  Enum_Move    = 0x004,      //随机移动方向
    Enum_MAX     //最大状态
};


//锁定状态
enum SuoDingState
{
	SuoDing_None = 0x0000,
	SuoDing_All  = 0x0001,
};

//拾取状态
enum PickState
{
	Pick_None    = 0x0000,     //不拾取
	Pick_All     = 0x0001,     //拾取所有
};

//组队状态
enum TeamState
{
	Team_AcceptInvite = 0x0001,   //接受组队邀请
	Team_AcceptComein = 0x0002,   //接受入队邀请
	Team_NeedItem     = 0x0004,   //组队分配全部需求
};

//范围设置
enum AreaState
{
	Area_Nomal,   //一般范围
	Area_Big,     //较大范围
	Area_Small,   //较小范围
};

#define USEMAXSKILL 4   //最大技能数

class AutoFight
{
public:
    AutoFight();
    ~AutoFight();

    void Init();

    void ProcessRecover();   //处理恢复
    void ProcessPick();      //处理拾取
	void ProcessAutoPick();	 //处理挂机中另一个自动拾取 zhuxincong 
    void ProcessAttack();    //处理攻击
    void Process();          //处理挂机
    bool ProcessWait();      //等待处理
	void ProcessTeam(Msg *pMsg);      //处理组队
	void ProcessTeamAssign(Msg *pMsg);


    bool  UseAttackSkill();   //使用攻击技能
    bool  UseBufSkill();      //使用辅助技能
	bool  UseHpSkill();       //使用回血技能
	bool  UseHpSkillInTeam(); //给队伍使用回血技能 无队伍就对直自己使用
	CPlayer* GetTeamPlayerInNeedHPSkill();

    void CheckState();      //判断当前角色是否存在改状态

    void EnterWait(DWORD elpaseTime); //ElpaseTime表示等待的时间


    bool  IsAutoFight();   //是否处于自动挂机状态
	bool  IsProtection();  //是否处于保护状态
	bool  IsPick();			//是否处于自动拾取状态
private:
	DWORD m_dwProtection;

public:

    void  SetState(AutoState state);  //设置状态


    //void  RandMove();
	void BeginProtection(){m_bProtection = true;}
	void EndinProtection(){m_bProtection = false;}
	void BeginPick(){m_bPick = true;}
	void EndinPick(){m_bPick = false;}
    void  BeginFight(){m_bAuto = true; m_OutPutFindMP = true; m_OutPutFindHP = true;}
    void  EndFight(){m_bAuto = false;}

    bool IsHaveItem();  //是否有包裹
    void ResetSkillSeq();  //清空技能索引，当怪物死亡时，清空技能调整到第一个

#ifdef _DEBUG
    void DebugInfo();
#endif

    //攻击区间
    struct AttackZone 
    {
        //区间确定
        D3DXVECTOR3  m_pos;           //取玩家当前位置
        float        m_Radius;        //半径，确定追击范围
		AreaState    m_eAreaState;          //当前范围区域
        AttackZone()
        {
            m_pos    = D3DXVECTOR3(0.0f,0.0f,0.0f);
            m_Radius = 500.0f;//zhuxincong 8.21 当玩家上游戏没有选择范围的时候，默认为150，可以刷新周围的怪物
			m_eAreaState  = Area_Nomal;
        }
    };

    //使用技能
    struct SkillList
    {
        ItemDefine::SItemSkill *m_Skill[USEMAXSKILL];     //技能队列
        int                     m_CurrIndex;           //当前使用的技能索引,策划需求为顺序使用，都不符合就使用刀平砍
		int                     nLimit;
        
		SkillList()
        {
            m_CurrIndex = 0;
            for (int i = 0;i < USEMAXSKILL;++i)
            {
                m_Skill[i] = NULL;
            }
			nLimit = -1;
        }
    };

	struct Action
	{
		bool bDo;        //Action
		int  nLimitPer;  //限制比例
		Action()
		{
			bDo = false;
			nLimitPer = 0;
		}
	};

	struct MonsterSetting
	{
		unsigned int nMonsterId;  //怪物ID
		bool         bKill;       //是否能杀这种类型怪物
		MonsterSetting()
		{
			nMonsterId = -1;
			bKill = false;
		}
	};

public:
//-------自动打怪数据保存
	bool    LoadDefaultData();
    bool    ReadData(int nValue);            //读取数据
    bool    WriteData(int nValue);           //写数据

    static  DWORD s_dwElapseTime;  //当怪物死亡后等待时间

	void	SetIsNeedHpSkillTeam(bool States){m_IsNeedHpSkillTeam = States;}
	bool	GetIsNeedHpSkillTeam(){return m_IsNeedHpSkillTeam;}
private:
	bool		m_bProtection;		//是否在保护中
	bool		m_bPick;			//是否拾取
    bool         m_bAuto;          //是否开始挂机
    AutoState    m_enum;           //挂机状态
    DWORD        m_WaitBeginTime;  //开始计时，物品拣物品只有3秒时间,杀怪后休息1秒

    DWORD        m_dwElapseTime;     //等待时间

    DWORD        m_dwSendMsgTime;   //送消息时间 

	bool		 m_IsNeedHpSkillTeam;



//技能设置
public:
	void    SetAttackSkill(ItemDefine::SItemSkill *pSkill,int nIndex);  //设置攻击技能
	void    SetBufSkill(ItemDefine::SItemSkill *pSkill,int nIndex);     //设置辅助技能
	void    SetRecSkill(ItemDefine::SItemSkill *pSkill,int nIndex,int nLimit);  //设置回血技能
	void    SetRecTeamSkill(ItemDefine::SItemSkill *pSkill,int nIndex,int nLimit);
	void    SetRecSkillLimit(int nValue){m_RecSkill.nLimit = nValue;}
	void    SetRecTeamSkillLimit(int nValue){m_RecTeamSkill.nLimit = nValue;}
	DWORD   GetWaitBeginTime(){return m_WaitBeginTime;}

	ItemDefine::SItemSkill* GetAttackSkill(int nIndex);
	ItemDefine::SItemSkill* GetBufSkill(int nIndex);
	ItemDefine::SItemSkill* GetRecSkill(int nIndex);
	int                      GetRecHpPer(){return m_RecSkill.nLimit;}

	ItemDefine::SItemSkill* GetRecTeamSkill(int nIndex);
	int						 GetRecHpTeamPer(){return m_RecTeamSkill.nLimit;}

private:
	SkillList    m_AttackSkill;    //攻击技能
	SkillList    m_BufSkill;       //辅助技能
	SkillList    m_RecSkill;       //回血技能
	SkillList	 m_RecTeamSkill;  // 队伍回血技能

	//喝药设置
public:
	bool IsUseHpQuest();  //是否需要使用红药
	bool IsUseMpQuset();  //是否需要使用蓝药
	bool IsBackCityNoQuest();   //是否需要没药回程
	bool IsUseEnergy(){return m_actUseEnergy.bDo;} //是否使用精力丹
	bool IsUseHpSkill();


	void SetHp(bool bValue,int nValue);
	void SetHpLimit(int nValue){m_actHp.nLimitPer = nValue;}
	void SetMp(bool bValue,int nValue);
	void SetMpLimit(int nValue){m_actMp.nLimitPer = nValue;}
	void SetBackCityNoQuest(bool bValue);  //没药回程
	void SetUseEnergy(bool bValue);        //使用精力丹
	int SearchQuestIndex(bool bAddHp = true);
//private:
	Action m_actHp;                //HP
	Action m_actMp;                //MP
	Action m_actBackCityNoQuest;   //无药品回程
	Action m_actUseEnergy;         //使用精力丹
	DWORD  m_HpItemId;
	DWORD  m_MpItemId;
	bool   m_OutPutFindHP;
	bool   m_OutPutFindMP;

	//打怪设置,在排除列表中的怪物不会打
public:
	bool IsNoExistMonster(unsigned int usMonsterId);    //是否存在该怪物
	void AddMonsterSet(unsigned int usMonsterId);
	void DelMonsterSet(unsigned int usMonsterId);
	void ClearMonsterSet(){m_MonsSetting.clear();}
	int  GetMonsterSize(){return m_MonsSetting.size();}
	MonsterSetting* GetMonsterByIndex(int nIndex){return &m_MonsSetting[nIndex];}

private:
	std::vector<MonsterSetting> m_MonsSetting;
	typedef std::vector<MonsterSetting>::iterator MonsIter;

	//攻击范围设定
public:
    void  SetPos(D3DXVECTOR3& pos);  //设置攻击区域
	void  SetAreaType(AreaState eValue);  
    bool  IsInZone(float x,float y);     //是否在攻击范围
	float  GetZoneRadius(){return m_AttackZone.m_Radius;}
	AreaState GetZoneType(){return m_AttackZone.m_eAreaState;}
private:
	AttackZone   m_AttackZone;     //攻击区间

	//自动拾取设置
public:
	void AddPickFlag(DWORD val){m_dwPickState |= val;}
	void RemovePickFlag(DWORD val){m_dwPickState &= (~val);}
	bool IsPickFlag(DWORD val){return (bool)(m_dwPickState & val);}
private:
	DWORD       m_dwPickState;     //拾取状态 

	//锁定状态
public:
	void AddSuoDingFlag(DWORD val){m_dwSuoDingState |= val;}
	void RemoveSuoDingFlag(DWORD val){m_dwSuoDingState &= (~val);}
	bool IsSuoDingFlag(DWORD val){return (bool)(m_dwSuoDingState & val);}

private:
	DWORD		m_dwSuoDingState;	//锁定状态

	//组队设置
public:
	void    AddTeamFlag(DWORD val)    { m_dwTeamState |=  val;}
	void	RemoveTeamFlag(DWORD val) { m_dwTeamState &= (~val); }
	bool    IsTeamFlag(DWORD val){ return (bool)(m_dwTeamState & val);}
private:
	DWORD        m_dwTeamState;   //组队状态
public:
	void ClearAreaSetting(){m_vecArea.clear();}
	void AddAreaSetting(int nValue);
	int  GetAreaSetting(AreaState eType);
private:
	std::vector<int> m_vecArea;  //区域范围的长度
};


#include "UiBase.h"
class CUI_ID_FRAME_AutoAttackSet :public CUIBase
{
	// Member
    friend class AutoFight;
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_AutoAttackSet;
// 	 ControlText*	m_pID_TEXT_UseItemZ;
	 ControlCheckBox*	m_pID_CHECKBOX_PickItem;
	 ControlCheckBox*   m_pID_CHECKBOX_SUODING;
// 	 ControlText*	m_pID_TEXT_PickItemZ;
	 ControlCheckBox*	m_pID_CHECKBOX_Advance;
// 	 ControlText*	m_pID_TEXT_HpZ;
	 ControlEdit*	m_pID_EDIT_Hp;
// 	 ControlText*	m_pID_TEXT_HpZ2;
	 ControlListImage*	m_pID_LISTIMG_SkillAttack;
// 	 ControlText*	m_pID_TEXT_MpZ;
	 ControlEdit*	m_pID_EDIT_Mp;
// 	 ControlText*	m_pID_TEXT_MpZ2;
// 	 ControlText*	m_pID_TEXT_AutoAttackZ;
	 ControlCheckBox*	m_pID_CHECKBOX_AutoAttack;
// 	 ControlText*	m_pID_TEXT_SkillAttackZ;
// 	 ControlText*	m_pID_TEXT_SkillBuffZ;
	 ControlListImage*	m_pID_LISTIMG_SkillBuff;
	 ControlListImage*	m_pID_LISTIMG_Hp;
	 ControlListImage*	m_pID_LISTIMG_Mp;
	 ControlButton*	m_pID_BUTTON_Begin;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton* m_pID_BUTTON_ProtectionStop;
	 ControlButton* m_pID_BUTTON_ProtectionBegin;
	 ControlButton* m_pID_BUTTON_PickOff;
	 ControlButton* m_pID_BUTTON_PickOn;
// 	 ControlPicture*	m_pID_PICTURE_Title;
	 ControlButton*	m_pID_BUTTON_Stop;
	 //ControlPicture*	m_pID_PICTURE_TitleWord;
	 ControlEdit*	m_pID_EDIT_SkillHp;
	 ControlListImage*	m_pID_LISTIMG_SkillHp;
	 ControlCheckBox*	m_pID_CHECKBOX_Hp;
	 ControlCheckBox*	m_pID_CHECKBOX_Mp;
	 ControlCheckBox*	m_pID_CHECKBOX_Tp;
	 ControlButton*	m_pID_BUTTON_Renovate;
	 ControlButton*	m_pID_BUTTON_All;
	 ControlButton*	m_pID_BUTTON_Reverse;
	 ControlList*	m_pID_LIST_Monster;
	 ControlCheckBox*	m_pID_CHECKBOX_Normal;
	 ControlCheckBox*	m_pID_CHECKBOX_Big;
	 ControlCheckBox*	m_pID_CHECKBOX_Small;
	 ControlCheckBox*	m_pID_CHECKBOX_Team1;
	 ControlCheckBox*	m_pID_CHECKBOX_Team2;
	 ControlCheckBox*	m_pID_CHECKBOX_Setting1;
	 ControlCheckBox*	m_pID_CHECKBOX_Setting2;
	 ControlButton*	    m_pID_BUTTON_Default;
	 ControlButton*	m_pID_BUTTON_Save;
	 ControlText*	m_pID_TEXT_TimeText;
	 ControlText*	m_pID_TEXT_Time;
	 ControlCheckBox*	m_pID_CHECKBOX_Energy;
	 ControlCheckBox*	m_pID_CHECKBOX_TeamNeed;

	 //队伍辅助加血
	 ControlCheckBox*	m_pID_CHECKBOX_IsCheckHpTeam;
	 ControlEdit*		m_pID_EDIT_TeamSkillHp;
	 ControlListImage*	m_pID_LISTIMG_SkillHpTeam;
public:	
	CUI_ID_FRAME_AutoAttackSet();
	// Frame
	ControlFrame * GetRrame(){return m_pID_FRAME_AutoAttackSet;}
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_PickItemOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SUODINGOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked);
	void ID_CHECKBOX_AdvanceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_EDIT_HpOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_LISTIMG_SkillAttackOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SkillAttackOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillAttackOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillAttackOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_EDIT_MpOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_CHECKBOX_AutoAttackOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_LISTIMG_SkillBuffOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SkillBuffOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillBuffOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillBuffOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HpOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_HpOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HpOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HpOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MpOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MpOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MpOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MpOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_BeginOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ProtectionBeginOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ProtectionStopOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PickOffOnButtonClick( ControlObject* pSender);
	bool ID_BUTTON_PickOnOnButtonClick( ControlObject* pSender);
	bool ID_BUTTON_StopOnButtonClick( ControlObject* pSender );
	void ID_EDIT_SkillHpOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_LISTIMG_SkillHpOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SkillHpOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillHpOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillHpOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_CHECKBOX_HpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BackOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_EDIT_BackHpOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_RenovateOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AllOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ReverseOnButtonClick( ControlObject* pSender );
	void ID_LIST_MonsterOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_NormalOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BigOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SmallOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	void ID_CHECKBOX_Team1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Team2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	void ID_CHECKBOX_Setting1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Setting2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	bool ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SaveOnButtonClick( ControlObject* pSender );

	void ID_CHECKBOX_EnergyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamNeedOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	//队伍辅助加血
	void ID_CHECKBOX_IsCheckHpTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_LISTIMG_SkillHpTeamOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SkillHpTeamOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillHpTeamOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SkillHpTeamOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_EDIT_TeamSkillHpOnEditEnter( ControlObject* pSender, const char* szData );
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可
	virtual bool IsHoldInMemory() const { return true; }
public:

	AutoFight& GetAutoFight() { return m_autoFight; }
	ControlListImage* GetListImage_Hp();
	ControlListImage* GetListImage_Mp();
	ControlListImage* GetListImage_SkillAttack();
	ControlListImage* GetListImage_SkillBuff();
	ControlListImage* GetListImage_SkillHp();
	ControlListImage* GetListImage_SkillHpTeam();

	void SetSave(bool bSave) { m_bSave = bSave; }


	void SetUpdateUI(bool bValue){m_bUpdateUI = bValue;}
	void UpdateUIData();
	void RefreshSkillUI(bool bUpdate);  //刷新技能
	void RefreshSkillImageUI(ItemDefine::SItemSkill* pItemSkill,ControlListImage* pImage,int nIndex,bool bUpdate);

	void RefreshQuestUI();   //刷新药品
	void RefreshMonsterUI(); //刷新怪物设置
	void RefreshAreaUI();      //刷新攻击区域
	void RefreshPickUI();      //刷新拾取
	void RefershTeamUI();      //刷新组队
	void RefershSuoDingUI();   //刷新锁定
	void AddRecordByItemID(GameObjectId id)
	{
        m_PickedItemServerId.push_back(id);
	}

	bool FindBeRecordItem(GameObjectId id);
	void ReMoveRecordItem(GameObjectId id);
private:
    //-----------------------------------------------------------
	void ClearControlData();
    void InitControl();  //初始化控件
    void SetFightState();  //设置战斗状态
    void SetAttackSkill(int nIndex,unsigned short skillId);
    void SetBufSkill(int nIndex,unsigned short skillId);
	void SetHpSkill(int nIndex,unsigned short skillId);
	void SetHpTeamSkill(int nIndex,unsigned short skillId);
    void UpdateCD(const int id,ControlListImage* pImg,int nIndex = 0);

    //--------------------------------
    

	std::vector<GameObjectId> m_PickedItemServerId;	

    //搜索药品
    unsigned int SearchQuse(bool IsAddHp = true);

    void SetDefaultData();

    void LoadConfig();

    AutoFight  m_autoFight;

    bool       m_bSave;

    bool       m_bUILoad;  //是否加载技能,在这里加的原因是因为刚创建的角色学习的技能是脚本创建的，服务器发空的列表过来的
	bool       m_bUpdateUI; //更新UI
public:
	static void EditDataChangeInHpSkill( OUT ControlObject* pSender, OUT const char *szData );
	static void EditDataChangeInHp( OUT ControlObject* pSender, OUT const char *szData );
	static void EditDataChangeInMp( OUT ControlObject* pSender, OUT const char *szData );
	static void EditDataChangeInHpSkillTeam( OUT ControlObject* pSender, OUT const char *szData );

	void BeginAutoAttack();
	void EndAutoAttack();
	long BeginAutoAttackTime;
private:
	int  m_IsNeedTeamHpValue;//0-100
private:
	void OnCheckTeamHpSkill(bool IsCheck);
};
extern CUI_ID_FRAME_AutoAttackSet s_CUI_ID_FRAME_AutoAttackSet;