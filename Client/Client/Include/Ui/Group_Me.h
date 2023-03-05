/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Group_Me.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include <time.h>
#include "GlobalDef.h"
#include "Me3d/Camera.h"
#include "PlaneEffect.h"

#ifndef ID_FRAME_Group_Me
#define ID_FRAME_Group_Me		"ID_FRAME_Group_Me"
#endif  ID_FRAME_Group_Me
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_PROGRESS_Hp
#define ID_PROGRESS_Hp		"ID_PROGRESS_Hp"
#endif  ID_PROGRESS_Hp
#ifndef ID_PROGRESS_Mp
#define ID_PROGRESS_Mp		"ID_PROGRESS_Mp"
#endif  ID_PROGRESS_Mp
#ifndef ID_TEXT_level		
#define ID_TEXT_level		"ID_TEXT_level"
#endif	ID_TEXT_level		
#ifndef ID_PICTURE_pet
#define ID_PICTURE_pet		"ID_PICTURE_pet"
#endif  ID_PICTURE_pet
#ifndef ID_TEXT_petname
#define ID_TEXT_petname		"ID_TEXT_petname"
#endif  ID_TEXT_petname
#ifndef ID_TEXT_petlevel
#define ID_TEXT_petlevel		"ID_TEXT_petlevel"
#endif  ID_TEXT_petlevel
#ifndef ID_PROGRESS_petHp
#define ID_PROGRESS_petHp		"ID_PROGRESS_petHp"
#endif  ID_PROGRESS_petHp
#ifndef ID_PICTURE_FacePic
#define ID_PICTURE_FacePic		"ID_PICTURE_FacePic"
#endif  ID_PICTURE_FacePic
#ifndef ID_PICTURE_Assassin
#define ID_PICTURE_Assassin		"ID_PICTURE_Assassin"
#endif  ID_PICTURE_Assassin
#ifndef ID_PICTURE_Mage
#define ID_PICTURE_Mage		"ID_PICTURE_Mage"
#endif  ID_PICTURE_Mage
#ifndef ID_PICTURE_Warrior
#define ID_PICTURE_Warrior		"ID_PICTURE_Warrior"
#endif  ID_PICTURE_Warrior
#ifndef ID_PICTURE_Taoist
#define ID_PICTURE_Taoist		"ID_PICTURE_Taoist"
#endif  ID_PICTURE_Taoist
#ifndef ID_PICTURE_Hunter
#define ID_PICTURE_Hunter		"ID_PICTURE_Hunter"
#endif  ID_PICTURE_Hunter
#ifndef ID_PICTURE_PetHead
#define ID_PICTURE_PetHead		"ID_PICTURE_PetHead"
#endif  ID_PICTURE_PetHead
#ifndef ID_PICTURE_Corps
#define ID_PICTURE_Corps		"ID_PICTURE_Corps"
#endif  ID_PICTURE_Corps
#ifndef ID_PICTURE_ChoosePet
#define ID_PICTURE_ChoosePet		"ID_PICTURE_ChoosePet"
#endif  ID_PICTURE_ChoosePet
#ifndef ID_BUTTON_PKClose
#define ID_BUTTON_PKClose		"ID_BUTTON_PKClose"
#endif  ID_BUTTON_PKClose
#ifndef ID_BUTTON_PKOpen
#define ID_BUTTON_PKOpen		"ID_BUTTON_PKOpen"
#endif  ID_BUTTON_PKOpen
#ifndef ID_BUTTON_PKFury
#define ID_BUTTON_PKFury		"ID_BUTTON_PKFury"
#endif  ID_BUTTON_PKFury
#ifndef ID_PROGRESS_ExBar
#define ID_PROGRESS_ExBar		"ID_PROGRESS_ExBar"
#endif  ID_PROGRESS_ExBar
#ifndef ID_PROGRESS_Flame
#define ID_PROGRESS_Flame		"ID_PROGRESS_Flame"
#endif  ID_PROGRESS_Flame
#ifndef ID_BUTTON_Faction
#define ID_BUTTON_Faction		"ID_BUTTON_Faction"
#endif  ID_BUTTON_Faction
#ifndef ID_PICTURE_HairPic
#define ID_PICTURE_HairPic		"ID_PICTURE_Hair"
#endif  ID_PICTURE_HairPic
//召唤宠
#ifndef ID_PICTURE_PETHEAD1
#define  ID_PICTURE_PETHEAD1 "ID_PICTURE_PetHead1"
#endif 	ID_PICTURE_PETHEAD1

#ifndef ID_PICTURE_BGPETHEAD1
#define	ID_PICTURE_BGPETHEAD1 "ID_PICTURE_BgPetHead1"  
#endif		ID_PICTURE_BGPETHEAD1

#ifndef ID_TEXT_PETNAME1
#define  ID_TEXT_PETNAME1 "ID_TEXT_petname1"
#endif ID_TEXT_PETNAME1

#ifndef ID_PICTURE_PET1
#define ID_PICTURE_PET1 "ID_PICTURE_pet1"
#endif ID_PICTURE_PET1

#ifndef  ID_PROGRESS_PETHP1
#define ID_PROGRESS_PETHP1 "ID_PROGRESS_petHp1"
#endif ID_PROGRESS_PETHP1

#ifndef ID_PICTURE_CHOOSEPET1
#define  ID_PICTURE_CHOOSEPET1 "ID_PICTURE_ChoosePet1"
#endif ID_PICTURE_CHOOSEPET1

#ifndef ID_TEXT_PETLEVEL1
#define  ID_TEXT_PETLEVEL1 "ID_TEXT_petlevel1"
#endif ID_TEXT_PETLEVEL1

#ifndef ID_TEXT_SelfHp
#define ID_TEXT_SelfHp		"ID_TEXT_SelfHp"
#endif	ID_TEXT_SelfHp
#ifndef ID_TEXT_SelfMp
#define ID_TEXT_SelfMp		"ID_TEXT_SelfMp"
#endif	ID_TEXT_SelfMp
#ifndef ID_TEXT_petHp
#define ID_TEXT_petHp		"ID_TEXT_petHp"
#endif	ID_TEXT_petHp
#ifndef ID_TEXT_petHp1
#define ID_TEXT_petHp1		"ID_TEXT_petHp1"
#endif	ID_TEXT_petHp1
#ifndef ID_BUTTON_PKGuild
#define ID_BUTTON_PKGuild		"ID_BUTTON_PKGuild"
#endif  ID_BUTTON_PKGuild
#ifndef ID_TEXT_Hero
#define ID_TEXT_Hero		"ID_TEXT_Hero"
#endif  ID_TEXT_Hero

//#ifndef ID_BUTTON_PlayerShowALL
//#define ID_BUTTON_PlayerShowALL		     "ID_BUTTON_PlayerShowALL"
//#endif  ID_BUTTON_PlayerShowALL
//#ifndef ID_BUTTON_PlayerShowAmity
//#define ID_BUTTON_PlayerShowAmity		 "ID_BUTTON_PlayerShowAmity"
//#endif  ID_BUTTON_PlayerShowAmity
//#ifndef ID_BUTTON_PlayerHideALL
//#define ID_BUTTON_PlayerHideALL		     "ID_BUTTON_PlayerHideALL"
//#endif  ID_BUTTON_PlayerHideALL
//#ifndef ID_BUTTON_PlayerShowAntagonize
//#define ID_BUTTON_PlayerShowAntagonize	 "ID_BUTTON_PlayerShowAntagonize"
//#endif  ID_BUTTON_PlayerShowAntagonize


#include "UiBase.h"
class CUI_ID_FRAME_Group_Me :public CUIBase
{
public:
    // 斗气动画帧的图片坐标
    struct ExPowerRect
    {
        ExPowerRect()
        {
            pNext = NULL;
            rcFrame.left = 0;
            rcFrame.top = 0;
            rcFrame.right = 0;
            rcFrame.bottom = 0;
        }
        ExPowerRect*    pNext;
        RECT            rcFrame;
    };

private:
	void ResetMembers();
	ControlFrame*		m_pID_FRAME_Group_Me;
	ControlText*		m_pID_TEXT_Name;
	ControlProgress*	m_pID_PROGRESS_Hp;
	ControlProgress*	m_pID_PROGRESS_Mp;
	ControlText*		m_pID_TEXT_LVL;
	ControlPicture*		m_pID_PICTURE_ChoosePet;
	ControlPicture*		m_pID_PICTURE_pet;
	ControlText*		m_pID_TEXT_petname;
	ControlText*		m_pID_TEXT_petlevel;
	ControlProgress*	m_pID_PROGRESS_petHp;
	ControlPicture*		m_pID_PICTURE_FacePic;

	ControlPicture*		m_pID_PICTURE_Assassin;
	ControlPicture*		m_pID_PICTURE_Mage;
	ControlPicture*		m_pID_PICTURE_Warrior;
	ControlPicture*		m_pID_PICTURE_Taoist;
	ControlPicture*		m_pID_PICTURE_Hunter;

	//ControlPicture*		m_pID_PICTURE_sword;				//1
	//ControlPicture*		m_pID_PICTURE_staff;				//1
	//ControlPicture*		m_pID_PICTURE_spear;				//1
	//ControlPicture*		m_pID_PICTURE_Fan;					//1
	//ControlPicture*		m_pID_PICTURE_Bow;					//1
	ControlPicture*		m_pID_PICTURE_Zhandou;
	ControlPicture*		m_pID_PICTURE_PetHead;
	ControlPicture*		m_pID_PICTURE_Corps;
    ControlButton*	    m_pID_BUTTON_PKClose;
    ControlButton*	    m_pID_BUTTON_PKOpen;
    ControlButton*	    m_pID_BUTTON_PKFury;
	ControlButton*		m_pID_BUTTON_PKGuild;
    ControlProgress*	m_pID_PROGRESS_ExBar;
    ControlProgress*    m_pID_PROGRESS_Flame;

	ControlButton*    m_pID_BUTTON_Faction;
	ControlPicture*		m_pID_PICTURE_HairPic;
	ControlGroup m_proPicGroup;
//召唤宠物
	ControlPicture*	m_pID_PICTURE_BgPetHead1;
	ControlPicture*	m_pID_PICTURE_PetHead1;
	ControlText*	m_pID_TEXT_petname1;
	ControlPicture*	m_pID_PICTURE_pet1;
	ControlProgress*	m_pID_PROGRESS_petHp1;
	ControlPicture*	m_pID_PICTURE_ChoosePet1;
	ControlText*	m_pID_TEXT_petlevel1;
	ControlText*	m_pID_TEXT_SelfMp;
	ControlText*	m_pID_TEXT_SelfHp;
	ControlText*	m_pID_TEXT_petHp;
	ControlText*	m_pID_TEXT_petHp1;
	ControlText*	m_pID_TEXT_Hero;

public:
	ControlButton*	m_pID_BUTTON_PlayerShowALL;
	ControlButton*	m_pID_BUTTON_PlayerShowAmity;
	ControlButton*	m_pID_BUTTON_PlayerHideALL;
	ControlButton*	m_pID_BUTTON_PlayerShowAntagonize;

public:
	CUI_ID_FRAME_Group_Me();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	        // 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	ControlFrame* GetFrame() { return m_pID_FRAME_Group_Me; }
	ControlProgress* GetPROGRESS_Hp();
	ControlProgress* GetPROGRESS_Mp();
	ControlText* GetTEXT_Hp(){return m_pID_TEXT_SelfHp;}
	ControlText* GetTEXT_Mp(){return m_pID_TEXT_SelfMp;}
	ControlText* GetTEXT_petHp(){return m_pID_TEXT_petHp;}
	ControlText* GetTEXT_petHp1(){return m_pID_TEXT_petHp1;}
	ControlProgress* GetPROGRESS_ExPower();
	ControlProgress* GetPROGRESS_petHp();
	ControlProgress* GetPROGRESS_petHp1();

	void RefreshPKShowPicture( int pkFlag );
	void SetPetInfoVisable( bool bShow, const char* headPic = 0);
	void SetPetInfoVisable_1(bool bShow1 = false,const char* headpic1 = 0);
	void Destory();
	bool NeedUpdata();
	void Updata();		//这里的updata需要放到 主循环里处理 因为status的时间需要1m更新一次 

	void SetShowHp(bool bShow)
	{
		m_bShowHp = bShow;
	}
	void SetShowMp(bool bShow)
	{
		m_bShowMp = bShow;
	}
	void SetShowFp(bool bShow) { m_bShowFp = bShow; }
	void SetPicHeader( bool bHeader);			// 设置是否可视
	void Refeash();
	void SetTEXT_LVL(const char* text);
	void SetTEXT_Name(const char* text, DWORD color);
	void SetHero_Name(const char* text, DWORD color);

	void SetTEXT_petname(const char* text);
	void SetTEXT_petname1(const char* text);
	void SetTEXT_petlevel(const char* text);
	void SetTEXT_petlevel1(const char* text);
	bool IsClick() { return IsClicked; }
	void SetIsClick(bool bClick) { IsClicked = bClick; }
    bool ID_BUTTON_PKCloseOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PKOpenOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PKFuryOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FactionOnButtonClick(ControlObject* pSender);
	bool ID_BUTTON_PKGuildOnButtonClick(ControlObject* pSender);
	static bool ID_FRAME_Group_MeOnLBtnClick( ControlObject* pSender );

	bool ID_BUTTON_PlayerShowALLOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PlayerShowAmityOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PlayerHideALLOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PlayerShowAntagonizeOnButtonClick( ControlObject* pSender );

	ControlText *GetPetNameControlText(); 

	/*void SetRenderPlayerFlag(unsigned int _flag, bool bCompositor = false)
	{
		m_bCompositor = bCompositor;
	    m_nPlayerRenderFlag = _flag;
	}

	unsigned int GetRenderPlayerFlag(){return m_nPlayerRenderFlag;}

	bool HasRenderFlag(unsigned int flag) { return m_nPlayerRenderFlag == flag; }*/
	void SetOpenPKModeButton();
private:
	static bool ID_FRAME_Group_MeOnClick( ControlObject* pSender );
	static bool ID_FRAME_Pet_OnRClick( INT nX, INT nY  );
	static void ID_FRAME_Group_MeOnMouseMove( ControlObject* pSender );
	static void ID_FRAME_Group_MeLevelMouseMove( ControlObject* pSender );
	static bool ID_FRAME_Group_MeOnPetClick(ControlObject* pSender );
    static bool GroupMe_HotKey_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
	
	
	void SetStatusTime(int nIndex, DWORD dwTime);
	void UpdataEquipView();
    void InitExPowerRect();         // 初始化斗气动画帧纹理坐标     added by zhuomeng.hu		[10/27/2010]
    void CreateProgressAni();

	enum EPetAICommand
	{
		ePetAIAttack		= 937,	// 设置宠物的AI为主动攻击
		ePetAIDefend		= 938,	// 设置宠物的AI为主动防守
		ePetAICommand		= 939	// 设置宠物的AI为服从命令
	};

	bool				m_bShowHp;
	bool				m_bShowMp;
	bool				m_bShowFp;
	bool				IsClicked;	                    //是否点击了 如果点击后 mouseon就不弹出 当前的队伍模式了 
	clock_t				_tBufStart[BodyStatusType_Max];	//这里记录没有个状态 中着的时间 以用于计算updata
	clock_t				_tLastTime[BodyStatusType_Max];
	ControlButton*		m_pPkBtn[ PKMode_MaxValue ];
	ControlButton*      m_pCurPlayerShowBtn;

	//===========================================================
	//ControlButton*		m_pPlayerShowBtn[PSM_Max];
 //   ControlButton*      m_pCurPlayerShowBtn;
	//bool                m_bPlayerShowModeOpen;  //列表是否展

	//public:
	//void  SetPlayerModeOpenOrClose(ControlObject* pSender);
	//void  compositor(bool IsChangeCurShowBtn = false);  //排序
	//unsigned int		m_nPlayerRenderFlag;
	//bool                m_bCompositor;

	//===========================================================
	
    
    CPlaneEffect*       m_pExPowerEffect;               // 满斗气特效

public:
	void SetGuildBattleButtonVisable(bool);
	void ShowButtonSpark();
	void InitEffectAttr();

	/*
	 * Author:	2012-8-4 wangshuai
	 * Desc:    刷新头像
	 */
	void RefreshHeadPic(bool force = false);

	CPlaneEffect m_xEffectSrray;
	bool m_bShowGuildBattleButton;
	bool m_bImageInited;
	bool m_bHeroImgInited;
private:
	int		m_XLog;
	int		m_YLog;

	/*int     ShowPlayerBtnPosX;
	int     ShowPlayerBtnPosY;*/
};
extern CUI_ID_FRAME_Group_Me s_CUI_ID_FRAME_Group_Me;