/********************************************************************
Created by UIEditor.exe
FileName: E:\Code\RunTime\CLIENT\Data\UI\Compound.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Skill.h"
#include "MessageDefine.h"
#include <vector>
#include <map>
#include "RecipeConfig.h"
using namespace std;

#ifndef ID_FRAME_Compound
#define ID_FRAME_Compound		"ID_FRAME_Compound"
#endif  ID_FRAME_Compound
#ifndef ID_PICTURE_DI2
#define ID_PICTURE_DI2		"ID_PICTURE_DI2"
#endif  ID_PICTURE_DI2
#ifndef ID_LISTIMG_Prescription
#define ID_LISTIMG_Prescription		"ID_LISTIMG_Prescription"
#endif  ID_LISTIMG_Prescription
#ifndef ID_EDIT_Info
#define ID_EDIT_Info		"ID_EDIT_Info"
#endif  ID_EDIT_Info
#ifndef ID_PICTURE_Wall
#define ID_PICTURE_Wall		"ID_PICTURE_Wall"
#endif  ID_PICTURE_Wall
#ifndef ID_PICTURE_14165
#define ID_PICTURE_14165		"ID_PICTURE_14165"
#endif  ID_PICTURE_14165
#ifndef ID_PICTURE_Wall2
#define ID_PICTURE_Wall2		"ID_PICTURE_Wall2"
#endif  ID_PICTURE_Wall2
#ifndef ID_PICTURE_Wall3
#define ID_PICTURE_Wall3		"ID_PICTURE_Wall3"
#endif  ID_PICTURE_Wall3
#ifndef ID_LISTIMG_M4
#define ID_LISTIMG_M4		"ID_LISTIMG_M4"
#endif  ID_LISTIMG_M4
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_LIST_ComName
#define ID_LIST_ComName		"ID_LIST_ComName"
#endif  ID_LIST_ComName
#ifndef ID_PICTURE_29268
#define ID_PICTURE_29268		"ID_PICTURE_29268"
#endif  ID_PICTURE_29268
#ifndef ID_PICTURE_Ying
#define ID_PICTURE_Ying		"ID_PICTURE_Ying"
#endif  ID_PICTURE_Ying
#ifndef ID_LISTIMG_M1
#define ID_LISTIMG_M1		"ID_LISTIMG_M1"
#endif  ID_LISTIMG_M1
#ifndef ID_PICTURE_9134
#define ID_PICTURE_9134		"ID_PICTURE_9134"
#endif  ID_PICTURE_9134
#ifndef ID_LISTIMG_M2
#define ID_LISTIMG_M2		"ID_LISTIMG_M2"
#endif  ID_LISTIMG_M2
#ifndef ID_PICTURE_9132
#define ID_PICTURE_9132		"ID_PICTURE_9132"
#endif  ID_PICTURE_9132
#ifndef ID_LISTIMG_M3
#define ID_LISTIMG_M3		"ID_LISTIMG_M3"
#endif  ID_LISTIMG_M3
#ifndef ID_PICTURE_Jin
#define ID_PICTURE_Jin		"ID_PICTURE_Jin"
#endif  ID_PICTURE_Jin
#ifndef ID_LISTIMG_Aim1
#define ID_LISTIMG_Aim1		"ID_LISTIMG_Aim1"
#endif  ID_LISTIMG_Aim1
#ifndef ID_BUTTON_Compound
#define ID_BUTTON_Compound		"ID_BUTTON_Compound"
#endif  ID_BUTTON_Compound
#ifndef ID_PICTURE_22632
#define ID_PICTURE_22632		"ID_PICTURE_22632"
#endif  ID_PICTURE_22632
#ifndef ID_TEXT_ResultInfo
#define ID_TEXT_ResultInfo		"ID_TEXT_ResultInfo"
#endif  ID_TEXT_ResultInfo
#ifndef ID_TEXT_ComSpr
#define ID_TEXT_ComSpr		"ID_TEXT_ComSpr"
#endif  ID_TEXT_ComSpr
#ifndef ID_PICTURE_10164
#define ID_PICTURE_10164		"ID_PICTURE_10164"
#endif  ID_PICTURE_10164

#ifndef ID_PICTURE_Forging
#define ID_PICTURE_Forging		"ID_PICTURE_Forging"
#endif  ID_PICTURE_Forging

#ifndef ID_TEXT_Rate
#define ID_TEXT_Rate		"ID_TEXT_Rate"
#endif  ID_TEXT_Rate
#ifndef ID_TEXT_Rate1
#define ID_TEXT_Rate1		"ID_TEXT_Rate1"
#endif  ID_TEXT_Rate1
#ifndef ID_TEXT_List
#define ID_TEXT_List		"ID_TEXT_List"
#endif  ID_TEXT_List
#ifndef ID_TEXT_M
#define ID_TEXT_M		"ID_TEXT_M"
#endif  ID_TEXT_M
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_TEXT_M1Name
#define ID_TEXT_M1Name		"ID_TEXT_M1Name"
#endif  ID_TEXT_M1Name
#ifndef ID_TEXT_M1Info
#define ID_TEXT_M1Info		"ID_TEXT_M1Info"
#endif  ID_TEXT_M1Info
#ifndef ID_TEXT_M2Name
#define ID_TEXT_M2Name		"ID_TEXT_M2Name"
#endif  ID_TEXT_M2Name
#ifndef ID_TEXT_M2Info
#define ID_TEXT_M2Info		"ID_TEXT_M2Info"
#endif  ID_TEXT_M2Info
#ifndef ID_TEXT_M3Name
#define ID_TEXT_M3Name		"ID_TEXT_M3Name"
#endif  ID_TEXT_M3Name
#ifndef ID_TEXT_M3Info
#define ID_TEXT_M3Info		"ID_TEXT_M3Info"
#endif  ID_TEXT_M3Info
#ifndef ID_TEXT_M4Name
#define ID_TEXT_M4Name		"ID_TEXT_M4Name"
#endif  ID_TEXT_M4Name
#ifndef ID_TEXT_M4Info
#define ID_TEXT_M4Info		"ID_TEXT_M4Info"
#endif  ID_TEXT_M4Info
#ifndef ID_TEXT_Especial
#define ID_TEXT_Especial		"ID_TEXT_Especial"
#endif  ID_TEXT_Especial
#ifndef ID_BUTTON_Stop
#define ID_BUTTON_Stop		"ID_BUTTON_Stop"
#endif  ID_BUTTON_Stop
#ifndef ID_LISTIMG_Especial
#define ID_LISTIMG_Especial		"ID_LISTIMG_Especial"
#endif  ID_LISTIMG_Especial
#ifndef ID_TEXT_ExpendEnergy2
#define ID_TEXT_ExpendEnergy2		"ID_TEXT_ExpendEnergy2"
#endif  ID_TEXT_ExpendEnergy2
#ifndef ID_TEXT_ExpendMoney
#define ID_TEXT_ExpendMoney		"ID_TEXT_ExpendMoney"
#endif  ID_TEXT_ExpendMoney
#ifndef ID_TEXT_Jin
#define ID_TEXT_Jin		"ID_TEXT_Jin"
#endif  ID_TEXT_Jin
#ifndef ID_TEXT_Ying
#define ID_TEXT_Ying		"ID_TEXT_Ying"
#endif  ID_TEXT_Ying
#ifndef ID_TEXT_ExpendEnergy
#define ID_TEXT_ExpendEnergy		"ID_TEXT_ExpendEnergy"
#endif  ID_TEXT_ExpendEnergy
#ifndef ID_TEXT_Nunber
#define ID_TEXT_Nunber		"ID_TEXT_Nunber"
#endif  ID_TEXT_Nunber
#ifndef ID_EDIT_Number
#define ID_EDIT_Number		"ID_EDIT_Number"
#endif  ID_EDIT_Number
#ifndef ID_BUTTON_Up
#define ID_BUTTON_Up		"ID_BUTTON_Up"
#endif  ID_BUTTON_Up
#ifndef ID_BUTTON_Down
#define ID_BUTTON_Down		"ID_BUTTON_Down"
#endif  ID_BUTTON_Down
#ifndef ID_BUTTON_Man
#define ID_BUTTON_Man		"ID_BUTTON_Man"
#endif  ID_BUTTON_Man
#ifndef ID_TEXT_NpcName
#define ID_TEXT_NpcName		"ID_TEXT_NpcName"
#endif  ID_TEXT_NpcName
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_30406
#define ID_BUTTON_30406		"ID_BUTTON_30406"
#endif  ID_BUTTON_30406
#ifndef ID_LISTIMG_Aim
#define ID_LISTIMG_Aim		"ID_LISTIMG_Aim"
#endif  ID_LISTIMG_Aim
#ifndef ID_TEXT_Aim
#define ID_TEXT_Aim		"ID_TEXT_Aim"
#endif  ID_TEXT_Aim
#ifndef ID_LISTIMG_Aim2
#define ID_LISTIMG_Aim2		"ID_LISTIMG_Aim2"
#endif  ID_LISTIMG_Aim2
#ifndef ID_TEXT_Rate2
#define ID_TEXT_Rate2		"ID_TEXT_Rate2"
#endif  ID_TEXT_Rate2
#ifndef ID_TEXT_EspecialName
#define ID_TEXT_EspecialName		"ID_TEXT_EspecialName"
#endif  ID_TEXT_EspecialName
#ifndef ID_TEXT_EspecialInfo
#define ID_TEXT_EspecialInfo		"ID_TEXT_EspecialInfo"
#endif  ID_TEXT_EspecialInfo
#ifndef ID_TEXT_AllRate
#define ID_TEXT_AllRate		"ID_TEXT_AllRate"
#endif  ID_TEXT_AllRate
#ifndef ID_TEXT_AllRate2
#define ID_TEXT_AllRate2		"ID_TEXT_AllRate2"
#endif  ID_TEXT_AllRate2
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_Money2
#define ID_TEXT_Money2		"ID_TEXT_Money2"
#endif  ID_TEXT_Money2
#ifndef ID_TEXT_Energy2
#define ID_TEXT_Energy2		"ID_TEXT_Energy2"
#endif  ID_TEXT_Energy2
#ifndef ID_TEXT_Energy
#define ID_TEXT_Energy		"ID_TEXT_Energy"
#endif  ID_TEXT_Energy
#ifndef ID_CHECKBOX_Forging
#define ID_CHECKBOX_Forging		"ID_CHECKBOX_Forging"
#endif  ID_CHECKBOX_Forging
#ifndef ID_CHECKBOX_Sewing
#define ID_CHECKBOX_Sewing		"ID_CHECKBOX_Sewing"
#endif  ID_CHECKBOX_Sewing
#ifndef ID_CHECKBOX_Cooking
#define ID_CHECKBOX_Cooking		"ID_CHECKBOX_Cooking"
#endif  ID_CHECKBOX_Cooking
#ifndef ID_CHECKBOX_Tea
#define ID_CHECKBOX_Tea		"ID_CHECKBOX_Tea"
#endif  ID_CHECKBOX_Tea
#ifndef ID_CHECKBOX_Drug
#define ID_CHECKBOX_Drug		"ID_CHECKBOX_Drug"
#endif  ID_CHECKBOX_Drug
#ifndef ID_CHECKBOX_Brewing
#define ID_CHECKBOX_Brewing		"ID_CHECKBOX_Brewing"
#endif  ID_CHECKBOX_Brewing

#ifndef ID_TEXT_AimName
#define ID_TEXT_AimName	"ID_TEXT_AimName"
#endif  ID_TEXT_AimName
#ifndef ID_TEXT_Aim1Name
#define ID_TEXT_Aim1Name		"ID_TEXT_Aim1Name"
#endif  ID_TEXT_Aim1Name
#ifndef ID_TEXT_Aim2Name
#define ID_TEXT_Aim2Name		"ID_TEXT_Aim2Name"
#endif  ID_TEXT_Aim2Name
#ifndef ID_TEXT_SkillLvl
#define ID_TEXT_SkillLvl		"ID_TEXT_SkillLvl"
#endif  ID_TEXT_SkillLvl

#ifndef ID_TEXT_Skill
#define ID_TEXT_Skill		"ID_TEXT_Skill"
#endif  ID_TEXT_Skill


using namespace std;

//class UISkillIcon
class CUICompoundConfig :public IOXMLObjectInstance
{
public:
	struct CompoundPage
	{
		SUIIconSet		UICompoundIcons;
		string								szBgPath;			
	}; 
public:
	CUICompoundConfig();
public:
	//IOXMLInstance Interface 
	virtual bool loadXMLSettings( const char *path  );
	virtual bool loadXMLSettings( XMLElement *element);

	virtual bool exportXMLSettings( std::ofstream &xmlFile  ) { return false; }
	virtual bool exportXMLSettings( const char* xmlPath ) { return false; }
	bool		 ReadUI( XMLElement *element );
	bool		 AddPos( XMLElement *child );
	CompoundPage*	 GetPage( int nPage )
	{
		if( nPage < 0 || nPage > m_UICompoundIconSet.size() )
			return NULL;
		return &m_UICompoundIconSet[nPage];
	}
public:
	vector<CompoundPage>		m_UICompoundIconSet;
	string						m_strProfession;
};

class CUICompoundMgr
{
public:
	enum
	{
		eCompound = 0,	//合成
		eReFine,		//精炼
		eIntensify,		//强化
		eMaxCompound
	};
	enum 
	{
		eCompoundMaxGrid = 4
	};
public:
	CUICompoundMgr();
	~CUICompoundMgr();
public:
	// 进入游戏的时候,加载Skill以前传入职业信息
	void	Init( ControlFrame* pCompoundFrame );
	void	Release();
	//void	AddBgPic(ControlPicture* pPic);
	void	AddBgCompoundicon(ControlListImage* pImg);
	void	ChangeUI( int nCompound );

	void	Destroy( );

	//	bool	AddPos( XMLElement *child );
private:
	CUICompoundConfig		m_CompoudConfig;
	vector<ControlListImage*> m_vtCompoundicon;
	ControlFrame*			m_pCompoundFrame;
	//	vector<ControlPicture*> m_vtBgPic;		
	int						m_nCompound;
};
extern CUICompoundMgr g_UICompoundMgr;

#include "UiBase.h"
class CUI_ID_FRAME_Compound :public CUIBase
{
private:
	// SGuildMember
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_Compound;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlListImage*	m_pID_LISTIMG_Prescription;
	ControlButton*	m_pID_BUTTON_Compound;
	ControlListImage*	m_pID_LISTIMG_Material;
	ControlListImage*	m_pID_LISTIMG_Aim;
// 	ControlListImage*	m_pID_LISTIMG_Aim1;
// 	ControlListImage*	m_pID_LISTIMG_Aim2;
	ControlEdit*	m_pID_EDIT_Info;
	ControlText*	m_pID_TEXT_ResultInfo;
	ControlText*	m_pID_TEXT_Rate;
// 	ControlText*	m_pID_TEXT_Rate1;
// 	ControlText*	m_pID_TEXT_Rate2;
	ControlListImage*	m_pID_LISTIMG_M1;
	ControlListImage*	m_pID_LISTIMG_M2;
	ControlListImage*	m_pID_LISTIMG_M3;
	ControlListImage*	m_pID_LISTIMG_M4;

	ControlList	*m_pID_LIST_ComName;	//配方名字
	ControlText	*m_pID_TEXT_Info;		//配方说明

	ControlText	*m_pID_TEXT_M1Name;
	ControlText	*m_pID_TEXT_M1Info;
	ControlText	*m_pID_TEXT_M2Name;
	ControlText	*m_pID_TEXT_M2Info;
	ControlText	*m_pID_TEXT_M3Name;
	ControlText	*m_pID_TEXT_M3Info;
	ControlText	*m_pID_TEXT_M4Name;
	ControlText	*m_pID_TEXT_M4Info;

	//ControlText	*m_pID_TEXT_Jin;
	ControlText	*m_pID_TEXT_Ying;

	ControlEdit	*m_pID_EDIT_Number;

	ControlButton*	m_pID_BUTTON_Man;

	ControlText	*m_pID_TEXT_NpcName;
	//ControlText *m_pID_TEXT_Skill;
	ControlPicture*	m_pID_PICTURE_Jin;
	ControlPicture*	m_pID_PICTURE_Ying;
	//ControlPicture*	m_pID_PICTURE_Forging;


	//ControlButton*		m_pID_BUTTON_help;
	ControlButton*	m_pID_BUTTON_Stop;

	ControlText*	m_pID_TEXT_Money;

	ControlText* m_pID_TEXT_ExpendEnergy;
	ControlText* m_pID_TEXT_Energy;

	ControlButton*	m_pID_BUTTON_Up;
	ControlButton*	m_pID_BUTTON_Down;

	//ControlListImage* m_pID_LISTIMG_Especial;

	ControlText* m_pID_TEXT_AimName;
// 	ControlText* m_pID_TEXT_Aim1Name;
// 	ControlText* m_pID_TEXT_Aim2Name;
// 	ControlText* m_pID_TEXT_SkillLvl;
// 	ControlText* m_pID_TEXT_EspecialName;


	bool m_bDirty;
	int m_nRuleID;
	bool m_bIsCando;
	int m_nPrescriptionId;
	int m_nNpcId;

	DWORD m_dwLastTime;

	int m_nSingTime;

	int m_nCompoundCount;
	int m_nCompoundMaxCount;
	int m_nCompoundCurrCount;

	int m_nSingleMoney;
	int m_nSingleEnergy;
	int m_stEspecialBagIndex;

	bool m_bEspecialBagEnable;

	int m_CurrRecipeType;

	struct TreeStatusRecord 
	{
		short m_nSubType;
		bool m_isCollapse;
		TreeStatusRecord(int nSubType,bool isCollapse)
			:m_nSubType(nSubType),m_isCollapse(isCollapse)
		{;}
	};

	typedef std::vector<TreeStatusRecord>  RecordArr;
	RecordArr					m_RecordArr[ERT_MaxType];
public:
	static bool helpOnClick( ControlObject* pSender );

	struct ComDescription		//配方描述
	{
		string  _szItemName;
		int		_nID;
		string	_szOneName;
		int		_nOneCnt;
		string	_szTwoName;
		int		_nTwoCnt;
		string	_szThreeName;
		int		_nThreeCnt;

		int     _nMenoy;
	};

	enum
	{
		MAX_ID = 512
	};

	CUI_ID_FRAME_Compound();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	// Button
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	// ListImg / ListEx
	bool ID_LISTIMG_PrescriptionOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
		ControlIconDrag::S_ListImg* pItemDrag,
		ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PrescriptionOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PrescriptionOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	// Button
	bool ID_BUTTON_CompoundOnButtonClick( ControlObject* pSender );
	// ListImg / ListEx
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
		ControlIconDrag::S_ListImg* pItemDrag,
		ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	// ListImg / ListEx
	bool ID_LISTIMG_AimOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
		ControlIconDrag::S_ListImg* pItemDrag,
		ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_AimOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AimOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	// Edit
	void ID_EDIT_InfoOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_LISTIMG_M1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_M1OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M1OnIconRDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_M2OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M2OnIconRDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_M3OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M3OnIconRDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_M4OnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M4OnIconRDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_LIST_ComNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_StopOnButtonClick( ControlObject* pSender );
// 	bool ID_LISTIMG_EspecialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
// 	bool ID_LISTIMG_EspecialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_EspecialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_EspecialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_M4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_BUTTON_UpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DownOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_ManOnButtonClick( ControlObject* pSender );

	static void ID_EDIT_NumberOnTextChanged( ControlObject* pSender, const char* szData );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	// 获取控件
	ControlFrame* GetFrame(){ return m_pID_FRAME_Compound; }
	ControlListImage* GetPrescription()
	{
		if( !m_pID_FRAME_Compound || !m_pID_LISTIMG_Prescription )
			return NULL;
		return m_pID_LISTIMG_Prescription; 
	}
	ControlListImage* GetMaterial()
	{
		if( !m_pID_FRAME_Compound || !m_pID_LISTIMG_Material )
			return NULL;
		return m_pID_LISTIMG_Material;
	}
	ControlListImage* GetAim()
	{
		if( !m_pID_FRAME_Compound || !m_pID_LISTIMG_Aim )
			return NULL;
		return m_pID_LISTIMG_Aim;
	}
	ControlEdit*	  GetEditNumber()
	{
		if( !m_pID_FRAME_Compound || !m_pID_EDIT_Number )
			return NULL;
		return m_pID_EDIT_Number;
	}

	void	RefreshBagEnable();
	void	RefreshPlayerProperty();
	void	RefreshSelectRecipe();
	void	Refeash();

	bool	IsGrid(const ControlObject* pSender);
	int		GetItemIndexFromGrid( const ControlIconDrag::S_ListImg *pImg );
	void	Compound( MsgAckCompound* pAckCompound );
	void	UpdateCompoundItems();
	void	SetNpcId(int nNpcId);
    void    ShowByType( int nType );
    void    ForgetRecipesByType( int nType );

private:
	void FillMaterial( RecipeConfig::SMaterial* pMat, ControlListImage* pListImg, ControlText* pCtrlName, ControlText* pCtrlInfo );
	void RefreshTargetItem( bool bHaveEspecial );
	void SetDirty( bool bDirty );

	void	OpenUI( int nType );

	void SetBegin(int nBegin);
	void SetEnd(int nEnd);

	void SetCreatRuloId(int nCreatRoleID,int nCount);

	RecipeConfig::SRecipe* GetCompoundRuleById(int nId);

	int GetBegin();
	int GetEnd();

	void ClearComSpr();

	void ClearResultInfo();

	void ChangeMoney(int count);

	void RecordCollapseInfo();
	bool LoadCollapseInfo();
	bool SaveCollapseInfo();

	ControlButton*	GetButton(){ return m_pID_BUTTON_Compound; }

	ControlText*	  GetTextResultInfo(){ return m_pID_TEXT_ResultInfo; }

	int GetCompoundCount(){ return m_nCompoundCount; }
	void SetCompoundCount( int n ){ m_nCompoundCount = n; }

	void SetSingTime( int n ){ m_nSingTime = n; };
	int GetSingTime(){ return m_nSingTime; }

	void HelpCanCompound();
	static void Compound_OnVisiableChanged( ControlObject* pSender );

	static bool CanCompound( const char bPressYesButton, void *pData  );

	void SetEspecialBagEnable( bool b ){ m_bEspecialBagEnable = b; }

	void LoadCompound( const char *szName );	//load 配方slk文件
	ComDescription& GetComDescription( const char *szName );	//得到配方描述
	void RetrieveRuleList();

	map<string, ComDescription>		MapCompundInfo;
	/*extern vector<string, ComDescription>		m_vecCompundInfo;*/
	int		_begin;
	int		_end;

};
extern CUI_ID_FRAME_Compound s_CUI_ID_FRAME_Compound;