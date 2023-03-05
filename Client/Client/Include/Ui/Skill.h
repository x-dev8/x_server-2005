/********************************************************************
Created by UIEditor.exe
FileName: F:\workspace\ShenWang\Hero\Program\trunk\Skill.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "IOXMLObject.h"
#include "MeRapidXml.h"

#ifndef ID_FRAME_SKILL
#define ID_FRAME_SKILL		"ID_FRAME_SKILL"
#endif  ID_FRAME_SKILL
#ifndef ID_PICTURE_Di
#define ID_PICTURE_Di		"ID_PICTURE_Di"
#endif  ID_PICTURE_Di
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
// #ifndef ID_PICTURE_Title
// #define ID_PICTURE_Title		"ID_PICTURE_Title"
// #endif  ID_PICTURE_Title
#ifndef ID_PICTURE_skillback
#define ID_PICTURE_skillback		"ID_PICTURE_skillback"
#endif  ID_PICTURE_skillback
#ifndef ID_PICTURE_skillback0
#define ID_PICTURE_skillback0		"ID_PICTURE_skillback0"
#endif  ID_PICTURE_skillback0
#ifndef ID_PICTURE_skillback1
#define ID_PICTURE_skillback1		"ID_PICTURE_skillback1"
#endif  ID_PICTURE_skillback1
#ifndef ID_PICTURE_skillback2
#define ID_PICTURE_skillback2		"ID_PICTURE_skillback2"
#endif  ID_PICTURE_skillback2
#ifndef ID_LISTIMG_SKILL_0
#define ID_LISTIMG_SKILL_0		"ID_LISTIMG_SKILL_0"
#endif  ID_LISTIMG_SKILL_0
#ifndef ID_LISTIMG_SKILL_1
#define ID_LISTIMG_SKILL_1		"ID_LISTIMG_SKILL_1"
#endif  ID_LISTIMG_SKILL_1
#ifndef ID_LISTIMG_SKILL_2
#define ID_LISTIMG_SKILL_2		"ID_LISTIMG_SKILL_2"
#endif  ID_LISTIMG_SKILL_2
#ifndef ID_CHECKBOX_Job
#define ID_CHECKBOX_Job		"ID_CHECKBOX_Job"
#endif  ID_CHECKBOX_Job
#ifndef ID_CHECKBOX_Currency
#define ID_CHECKBOX_Currency		"ID_CHECKBOX_Currency"
#endif  ID_CHECKBOX_Currency
#ifndef ID_CHECKBOX_SkillTree
#define ID_CHECKBOX_SkillTree		"ID_CHECKBOX_SkillTree"
#endif  ID_CHECKBOX_SkillTree
#ifndef ID_TEXT_Fuzhu
#define ID_TEXT_Fuzhu		"ID_TEXT_Fuzhu"
#endif  ID_TEXT_Fuzhu
#ifndef ID_TEXT_Beidong
#define ID_TEXT_Beidong		"ID_TEXT_Beidong"
#endif  ID_TEXT_Beidong
#ifndef ID_TEXT_Zhudong
#define ID_TEXT_Zhudong		"ID_TEXT_Zhudong"
#endif  ID_TEXT_Zhudong
#ifndef ID_PICTURE_TDi
#define ID_PICTURE_TDi		"ID_PICTURE_TDi"
#endif  ID_PICTURE_TDi
#ifndef ID_LISTIMG_Tongyong
#define ID_LISTIMG_Tongyong		"ID_LISTIMG_Tongyong"
#endif  ID_LISTIMG_Tongyong
#ifndef ID_TEXT_SkillPoint
#define ID_TEXT_SkillPoint		"ID_TEXT_SkillPoint"
#endif  ID_TEXT_SkillPoint
#ifndef ID_PICTURE_Spear
#define ID_PICTURE_Spear		"ID_PICTURE_Spear"
#endif  ID_PICTURE_Spear
#ifndef ID_PICTURE_Sword
#define ID_PICTURE_Sword		"ID_PICTURE_Sword"
#endif  ID_PICTURE_Sword
#ifndef ID_PICTURE_Bow
#define ID_PICTURE_Bow		"ID_PICTURE_Bow"
#endif  ID_PICTURE_Bow
#ifndef ID_PICTURE_Fan
#define ID_PICTURE_Fan		"ID_PICTURE_Fan"
#endif  ID_PICTURE_Fan
#ifndef ID_PICTURE_Staff
#define ID_PICTURE_Staff		"ID_PICTURE_Staff"
#endif  ID_PICTURE_Staff
#ifndef ID_PICTURE_skillback20
#define ID_PICTURE_skillback20		"ID_PICTURE_skillback20"
#endif  ID_PICTURE_skillback20
#ifndef ID_CHECKBOX_Produce
#define ID_CHECKBOX_Produce		"ID_CHECKBOX_Produce"
#endif  ID_CHECKBOX_Produce
#ifndef ID_TEXT_SkillName1
#define ID_TEXT_SkillName1		"ID_TEXT_SkillName1"
#endif  ID_TEXT_SkillName1
#ifndef ID_TEXT_SkillName2
#define ID_TEXT_SkillName2		"ID_TEXT_SkillName2"
#endif  ID_TEXT_SkillName2
#ifndef ID_TEXT_SkillName3
#define ID_TEXT_SkillName3		"ID_TEXT_SkillName3"
#endif  ID_TEXT_SkillName3
#ifndef ID_TEXT_SkillName4
#define ID_TEXT_SkillName4		"ID_TEXT_SkillName4"
#endif  ID_TEXT_SkillName4
#ifndef ID_TEXT_SkillName5
#define ID_TEXT_SkillName5		"ID_TEXT_SkillName5"
#endif  ID_TEXT_SkillName5
#ifndef ID_TEXT_SkillName6
#define ID_TEXT_SkillName6		"ID_TEXT_SkillName6"
#endif  ID_TEXT_SkillName6
#ifndef ID_TEXT_SkillName7
#define ID_TEXT_SkillName7		"ID_TEXT_SkillName7"
#endif  ID_TEXT_SkillName7
#ifndef ID_TEXT_SkillName8
#define ID_TEXT_SkillName8		"ID_TEXT_SkillName8"
#endif  ID_TEXT_SkillName8
#ifndef ID_TEXT_SkillDesc1
#define ID_TEXT_SkillDesc1		"ID_TEXT_SkillDesc1"
#endif  ID_TEXT_SkillDesc1
#ifndef ID_TEXT_SkillDesc2
#define ID_TEXT_SkillDesc2		"ID_TEXT_SkillDesc2"
#endif  ID_TEXT_SkillDesc2
#ifndef ID_TEXT_SkillDesc3
#define ID_TEXT_SkillDesc3		"ID_TEXT_SkillDesc3"
#endif  ID_TEXT_SkillDesc3
#ifndef ID_TEXT_SkillDesc4
#define ID_TEXT_SkillDesc4		"ID_TEXT_SkillDesc4"
#endif  ID_TEXT_SkillDesc4
#ifndef ID_TEXT_SkillDesc5
#define ID_TEXT_SkillDesc5		"ID_TEXT_SkillDesc5"
#endif  ID_TEXT_SkillDesc5
#ifndef ID_TEXT_SkillDesc6
#define ID_TEXT_SkillDesc6		"ID_TEXT_SkillDesc6"
#endif  ID_TEXT_SkillDesc6
#ifndef ID_TEXT_SkillDesc7
#define ID_TEXT_SkillDesc7		"ID_TEXT_SkillDesc7"
#endif  ID_TEXT_SkillDesc7
#ifndef ID_TEXT_SkillDesc8
#define ID_TEXT_SkillDesc8		"ID_TEXT_SkillDesc8"
#endif  ID_TEXT_SkillDesc8
#ifndef ID_TEXT_SkillName9
#define ID_TEXT_SkillName9		"ID_TEXT_SkillName9"
#endif  ID_TEXT_SkillName9
#ifndef ID_TEXT_SkillName10
#define ID_TEXT_SkillName10		"ID_TEXT_SkillName10"
#endif  ID_TEXT_SkillName10
#ifndef ID_TEXT_SkillName11
#define ID_TEXT_SkillName11		"ID_TEXT_SkillName11"
#endif  ID_TEXT_SkillName11
#ifndef ID_TEXT_SkillName12
#define ID_TEXT_SkillName12		"ID_TEXT_SkillName12"
#endif  ID_TEXT_SkillName12
#ifndef ID_TEXT_SkillDesc9
#define ID_TEXT_SkillDesc9		"ID_TEXT_SkillDesc9"
#endif  ID_TEXT_SkillDesc9
#ifndef ID_TEXT_SkillDesc10
#define ID_TEXT_SkillDesc10		"ID_TEXT_SkillDesc10"
#endif  ID_TEXT_SkillDesc10
#ifndef ID_TEXT_SkillDesc11
#define ID_TEXT_SkillDesc11		"ID_TEXT_SkillDesc11"
#endif  ID_TEXT_SkillDesc11
#ifndef ID_TEXT_SkillDesc12
#define ID_TEXT_SkillDesc12		"ID_TEXT_SkillDesc12"
#endif  ID_TEXT_SkillDesc12
#ifndef ID_CHECKBOX_Pet
#define ID_CHECKBOX_Pet		"ID_CHECKBOX_Pet"
#endif  ID_CHECKBOX_Pet
#ifndef ID_CHECKBOX_Equip
#define ID_CHECKBOX_Equip		"ID_CHECKBOX_Equip"
#endif  ID_CHECKBOX_Equip
#ifndef ID_CHECKBOX_XpSkill
#define ID_CHECKBOX_XpSkill		"ID_CHECKBOX_XpSkill"
#endif  ID_CHECKBOX_XpSkill
#ifndef ID_PICTURE_1
#define ID_PICTURE_1		"ID_PICTURE_1"
#endif  ID_PICTURE_1
#ifndef ID_PICTURE_2
#define ID_PICTURE_2		"ID_PICTURE_2"
#endif  ID_PICTURE_2
#ifndef ID_PICTURE_3
#define ID_PICTURE_3		"ID_PICTURE_3"
#endif  ID_PICTURE_3
#ifndef ID_PICTURE_4
#define ID_PICTURE_4		"ID_PICTURE_4"
#endif  ID_PICTURE_4
#ifndef ID_PICTURE_5
#define ID_PICTURE_5		"ID_PICTURE_5"
#endif  ID_PICTURE_5
#ifndef ID_PICTURE_6
#define ID_PICTURE_6		"ID_PICTURE_6"
#endif  ID_PICTURE_6
#ifndef ID_PICTURE_7
#define ID_PICTURE_7		"ID_PICTURE_7"
#endif  ID_PICTURE_7
#ifndef ID_PICTURE_TongYong
#define ID_PICTURE_TongYong		"ID_PICTURE_TongYong"
#endif  ID_PICTURE_TongYong
#ifndef ID_PICTURE_XinFa
#define ID_PICTURE_XinFa		"ID_PICTURE_XinFa"
#endif  ID_PICTURE_XinFa
#ifndef ID_PICTURE_ShengChan
#define ID_PICTURE_ShengChan		"ID_PICTURE_ShengChan"
#endif  ID_PICTURE_ShengChan

#include "UiBase.h"
class CUI_ID_FRAME_SKILL :public CUIBase
{
	// Member
private:
	void ResetMembers();
	ControlFrame*	    m_pID_FRAME_SKILL;
	//ControlPicture*	    m_pID_PICTURE_Di;
	ControlButton*	    m_pID_BUTTON_CLOSE;
	//ControlButton*	    m_pID_BUTTON_help;
// 	ControlPicture*	    m_pID_PICTURE_Title;
	//ControlPicture*	    m_pID_PICTURE_skillback;
	ControlPicture*	    m_pID_PICTURE_skillback0;
	ControlPicture*	    m_pID_PICTURE_skillback1;
	ControlPicture*	    m_pID_PICTURE_skillback2;
	ControlListImage*	m_pID_LISTIMG_SKILL_0;
	ControlListImage*	m_pID_LISTIMG_SKILL_1;
	ControlListImage*	m_pID_LISTIMG_SKILL_2;
	ControlCheckBox*	m_pID_CHECKBOX_Job;
	ControlCheckBox*	m_pID_CHECKBOX_Currency;
	ControlCheckBox*	m_pID_CHECKBOX_SkillTree;
	ControlText*	    m_pID_TEXT_Fuzhu;
	ControlText*	    m_pID_TEXT_Beidong;
	ControlText*	    m_pID_TEXT_Zhudong;
	ControlPicture*	    m_pID_PICTURE_TDi;
	ControlListImage*	m_pID_LISTIMG_Tongyong;
	ControlText*	    m_pID_TEXT_SkillPoint;

	ControlGroup        m_professionGroup;
	ControlGroup        m_commonGroup;
	ControlGroup        m_commonDescGroup;
	ControlRadioGroup m_skillTypeRadioGroup;
//      ControlPicture*	m_pID_PICTURE_Spear;
//      ControlPicture*	m_pID_PICTURE_Sword;
//      ControlPicture*	m_pID_PICTURE_Bow;
//      ControlPicture*	m_pID_PICTURE_Fan;
//      ControlPicture*	m_pID_PICTURE_Staff;
// 	 ControlPicture*	m_pID_PICTURE_skillback20;
	 ControlCheckBox*	m_pID_CHECKBOX_Produce;
	 ControlText*	m_pID_TEXT_SkillName1;
	 ControlText*	m_pID_TEXT_SkillName2;
	 ControlText*	m_pID_TEXT_SkillName3;
	 ControlText*	m_pID_TEXT_SkillName4;
	 ControlText*	m_pID_TEXT_SkillName5;
	 ControlText*	m_pID_TEXT_SkillName6;
	 ControlText*	m_pID_TEXT_SkillName7;
	 ControlText*	m_pID_TEXT_SkillName8;
	 ControlText*	m_pID_TEXT_SkillDesc1;
	 ControlText*	m_pID_TEXT_SkillDesc2;
	 ControlText*	m_pID_TEXT_SkillDesc3;
	 ControlText*	m_pID_TEXT_SkillDesc4;
	 ControlText*	m_pID_TEXT_SkillDesc5;
	 ControlText*	m_pID_TEXT_SkillDesc6;
	 ControlText*	m_pID_TEXT_SkillDesc7;
	 ControlText*	m_pID_TEXT_SkillDesc8;
// 	 ControlText*	m_pID_TEXT_SkillName9;
// 	 ControlText*	m_pID_TEXT_SkillName10;
// 	 ControlText*	m_pID_TEXT_SkillName11;
// 	 ControlText*	m_pID_TEXT_SkillName12;
// 	 ControlText*	m_pID_TEXT_SkillDesc9;
// 	 ControlText*	m_pID_TEXT_SkillDesc10;
// 	 ControlText*	m_pID_TEXT_SkillDesc11;
// 	 ControlText*	m_pID_TEXT_SkillDesc12;
	 ControlCheckBox* m_pID_CHECKBOX_Pet;
//	 ControlCheckBox*	m_pID_CHECKBOX_Equip;
	 ControlCheckBox*	m_pID_CHECKBOX_XpSkill;

	 ControlPicture*	m_pID_PICTURE_1;
	 ControlPicture*	m_pID_PICTURE_2;
	 ControlPicture*	m_pID_PICTURE_3;
	 ControlPicture*	m_pID_PICTURE_4;
	 ControlPicture*	m_pID_PICTURE_5;
	 ControlPicture*	m_pID_PICTURE_6;
	 ControlPicture*	m_pID_PICTURE_7;

	 ControlPicture*	m_pID_PICTURE_TongYong;
	 ControlPicture*	m_pID_PICTURE_XinFa;
	 ControlPicture*	m_pID_PICTURE_ShengChan;

public:	
	enum EWherefore
	{
		EWherefore_NpcLearn,
		EWherefore_SkillBagLearn
	};
	CUI_ID_FRAME_SKILL();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_SKILL_0OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SKILL_0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SKILL_0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SKILL_0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SKILL_1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SKILL_1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SKILL_1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SKILL_1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SKILL_2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SKILL_2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SKILL_2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SKILL_2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_CHECKBOX_JobOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_CurrencyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SkillTreeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_LISTIMG_TongyongOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_TongyongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TongyongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TongyongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_CHECKBOX_ProduceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_XpSkillOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	//void ID_CHECKBOX_EquipOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	ControlFrame* GetFrame() { return m_pID_FRAME_SKILL; }
	ControlCheckBox* GetSkillTree(){return m_pID_CHECKBOX_SkillTree;}
	ControlCheckBox* GetCurrency(){return m_pID_CHECKBOX_Currency;}
	ControlCheckBox* GetProduce(){return m_pID_CHECKBOX_Produce;}
	void SetObjectVisable(ControlObject* obj,bool bVisable)
	{
		obj->SetVisable(bVisable);
	}
	void SetVisableWherefore(const bool bVisable,EWherefore eWherefore);
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
public:


// 	ControlPicture* GetPICTURE_skillback20();
// 	void PICTURE_Staff_SetVisable(bool bVisible);
// 	void PICTURE_Spear_SetVisable(bool bVisible);
// 	void PICTURE_Sword_SetVisable(bool bVisible);
// 	void PICTURE_Bow_SetVisable(bool bVisible);
// 	void PICTURE_Fan_SetVisable(bool bVisible);
	bool CHECKBOX_Job_IsChecked();

	void RefreshCommon();
	bool IsSkillList( const ControlObject* pObject );
	void RefreshEquipSkill();
	bool InitSkillTree();
	void NeedRefresh(){ m_bNeedRefresh = true; }
    void UseSkill(ControlIconDrag::S_ListImg* pItem);

	static void IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

private:
	void Refresh();
	//void RefreshProfession();
	//void RefreshSkillTree();
    void RefreshSkillProduce();
	void RefreshSkillXpSkill();
	void RefreshPet();
	void RefreshSkillSpirit();

	//void ToggleProfession();
	void ToggleCommon();
	//void ToggleSkillTree();
    void ToggleSkillProduce();
	void ToggleSkillXpSkill();
	void TogglePet();
	void ToggleEquipSkill();
	void ToggleSkillSpirit();

    void UpdateCommonSkillInfo(int iIconId, int index);
	void ClearCommonSkillInfo();

	bool	m_bNeedRefresh;
private:
	std::map<unsigned short,unsigned short> SuitSkillMap;
public:
	void    AddCommonSkillBySuitEquip(unsigned short SkillID,unsigned short SkillLevel);
	void    ClearCommonSkillBySuitEquip(unsigned short SkillID);
	void    CheckClearAllCommonSkill();
};
extern CUI_ID_FRAME_SKILL s_CUI_ID_FRAME_SKILL;


class SUIIconSet
{
public:
	struct SIconSet
	{
		SIconSet()
		{
			index = 0;
			x = 0;
			y = 0;
			bVis = false;
			iconid = 0;
			iconSize = 0;
			row = 0;
			column = 0;
		}
		int				index;
		int				x;
		int				y;
		bool			bVis;
		int				iconid;
		std::string		image;		// icon使用的图片
		int				iconSize;	// icon的大小
		int				row;		// 对应图片的第几行，行高，列宽为iconSize
		int				column;		// 对应图片的第几列，行高，列宽为iconSize
	};
	SUIIconSet()
	{
	}
	void	AddAllPos(SIconSet pt)
	{
		m_vtIcon.push_back( pt );
	}
	void	Clear()
	{
		m_vtIcon.clear();
	}
	size_t	GetLength()
	{
		return m_vtIcon.size();
	}

	const SIconSet* GetValue( int id )
	{
		for (int i = 0; i < m_vtIcon.size(); ++i)
		{
			if (m_vtIcon[i].iconid == id)
				return &m_vtIcon[i];
		}
		return 0;
	}

public:
	vector<SIconSet>	m_vtIcon;

	int type;
};	

//class UISkillIcon
class CUISkillTreeConfig
{
public:
	struct SkillTreePage
	{
		SkillTreePage()
		{
			strcpy( szBgPath , "" );
		}
		SUIIconSet		UISkillIcons;
		char			szBgPath[MAX_PATH];			
	}; 
public:
	CUISkillTreeConfig();
public:
	//IOXMLInstance Interface 
	virtual bool loadXMLSettings( const char *path  );
	virtual bool loadXMLSettings( MeXmlElement *element);

	virtual bool exportXMLSettings( std::ofstream &xmlFile  ) { return false; }
	virtual bool exportXMLSettings( const char* xmlPath ) { return false; }

	bool		 SetProfession( string szString );
	const std::string& GetProfessionName() { return m_strProfession; }

	bool		 ReadProfession( MeXmlElement *element );
	bool		 AddPos( MeXmlElement *child, int type );
	SkillTreePage*	 GetPage( int nPage )
	{
		map<int, SkillTreePage>::iterator it = m_UISkillIconSet.find(nPage);
		if( it == m_UISkillIconSet.end() )
			return NULL;
		return &it->second;
	}

	bool	ReadMountSkill(MeXmlElement *element);
public:
	map<int, SkillTreePage>		m_UISkillIconSet;
	string						m_strProfession;

};
/*------------------------------------------------------
desc	: 心法图标管理类
------------------------------------------------------*/
class CUIXinFaConfig
{
public:
	CUIXinFaConfig();
	~CUIXinFaConfig();

	bool LoadIconConfig(const char *fileName_);
	const SUIIconSet::SIconSet* GetXinFaIconSet(int id);

private:
	SUIIconSet m_icons;
};

class CUISkillMgr
{
public:
	enum
	{
		// 枚举顺序要和AddPos顺序一致
		eProfession = 0,
		eCommon,
		eProduce,
		ePetSkill,
		eEquipSkill,
		eMountSkill,
		eXpSkill,
	};
public:
	CUISkillMgr();
	~CUISkillMgr();
public:
	// 进入游戏的时候,加载Skill以前传入职业信息 
	void	Init( int nProfession );
	void	InitialAllProfession();
	void	Release();
	void	AddBgPic(ControlPicture* pPic);
	void	AddBgSkillicon(ControlListImage* pImg);
	void	AddButtonSkillUp(ControlButton* pBtn);

	bool	OnRButtonUP( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	void	setSkillEducateId(int id)	{ m_nSkillEducateId = id; }

	SUIIconSet::SIconSet* GetSkillIconSet(int id);
	SUIIconSet::SIconSet* GetAllSkillIconSet(int id);
	//const SUIIconSet::SIconSet* GetXinFaIconSet(int id);

private:
	bool	LearnSkill( ControlIconDrag::S_ListImg* pItem );

public:
	CUISkillTreeConfig		m_SkillTreeConfig;
	std::vector<CUISkillTreeConfig> m_vtAllSkillTreeConfig;	//保存所有职业的技能，方便不同客户端查询
	//CUIXinFaConfig m_xinFaIconConfig;
	vector<ControlListImage*> m_vtSkillicon;	//技能升级ICON 容器
	vector<ControlPicture*> m_vtBgPic;		
	vector<ControlButton*>	m_vtBtnSkillUp;	//技能升级的22个按钮 容器
	int						m_nProfession;

	int						m_nSkillEducateId;
};
extern CUISkillMgr g_UISkillMgr;
