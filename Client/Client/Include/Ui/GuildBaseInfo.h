/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildBaseInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#include "GuildDefine.h"
#include "GuildCampBattleConfig.h"
#ifndef ID_FRAME_GuildBaseInfo
#define ID_FRAME_GuildBaseInfo		"ID_FRAME_GuildBaseInfo"
#endif  ID_FRAME_GuildBaseInfo
#ifndef ID_CHECKBOX_GuildMember
#define ID_CHECKBOX_GuildMember		"ID_CHECKBOX_GuildMember"
#endif  ID_CHECKBOX_GuildMember
#ifndef ID_CHECKBOX_GuildInfo
#define ID_CHECKBOX_GuildInfo		"ID_CHECKBOX_GuildInfo"
#endif  ID_CHECKBOX_GuildInfo
#ifndef ID_CHECKBOX_GuildRequest
#define ID_CHECKBOX_GuildRequest		"ID_CHECKBOX_GuildRequest"
#endif  ID_CHECKBOX_GuildRequest

#ifndef ID_CHECKBOX_AddGuildGeneral
#define ID_CHECKBOX_AddGuildGeneral		"ID_CHECKBOX_AddGuildGeneral"
#endif  ID_CHECKBOX_AddGuildGeneral

#ifndef ID_CHECKBOX_GuildGeneralList
#define ID_CHECKBOX_GuildGeneralList		"ID_CHECKBOX_GuildGeneralList"
#endif  ID_CHECKBOX_GuildGeneralList

enum GuildUIType
{
	GUT_Info = 0,
	GUT_Mamber,
	GUT_SQ,
	GUT_Add,
	GUT_List,
};

class CUI_ID_FRAME_GuildBaseInfo  :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GuildBaseInfo();
	 ControlFrame*	m_pID_FRAME_GuildBaseInfo;
	 ControlCheckBox*	m_pID_CHECKBOX_GuildMember;
	 ControlCheckBox*	m_pID_CHECKBOX_GuildInfo;
	 ControlCheckBox*	m_pID_CHECKBOX_GuildRequest;
	 ControlCheckBox*   m_pID_CHECKBOX_AddGuildGeneral;
	 ControlCheckBox*	m_pID_CHECKBOX_GuildGeneralList;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_GuildMemberOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GuildInfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GuildRequestOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_AddGuildGeneralOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GuildGeneralListOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual void InitializeAtEnterWorld();
	virtual bool IsHoldInMemory() const { return true; }

	ControlFrame* GetFrame(){return m_pID_FRAME_GuildBaseInfo;}

	void OnUpdateUiInfo();

	string GetGuildName() const {return m_GuildName;}
	string GetGuildMastrName() const;
	uint32	   GetGuildStrongth() const {return m_GuildStrongth;}
	uint32	   GetGuildMoney() const {return m_GuildMoney;}
	uint32		GetGuildLevel()const {return m_GuildLevel;}
	uint32		GetGuildExp() const {return m_GuildExp;}
	string  GetGuildCommon() const {return m_GuildCommon;}
	uint32		GetGuildAllSum() const {return m_GuildNum;}
	uint32		GetGuildOnLineSum() const {return m_GuildOnLineNum;}
	uint32		GetGuildMission(){return m_Mission;}
	vector<GuildMember*>& GetGuildOnLineMember()  {return m_GuildMemberOnLine;}
	vector<GuildMember*>& GetGuildNonOnLineMember()  {return m_GuildMenberNonOnLine;}
	bool		IsCanCommonByMe();//是否可以发布公告
	bool		IsCanDoByRight(uint32 Right);
	void		ChangeFamilyName( const char* pName );
	void		ShowSQUI();
	void		ShowGuildGeneralList();

	void		SetMemberCampBattleValue(unsigned int Value,GuildMember* pMember);
	void		DelMemberCampBattleValue(unsigned int Value,GuildMember* pMember);
	
	GuildCampBattleConfig& GetGuildCampBattleConfig(){return m_GuildCampBattleConfig;}

	void		ChangeGuildName(const char * NewName);
private:
	bool InitGuildInfo();
	void ShowUI(GuildUIType Type = GUT_Mamber);
private:
	GuildMember*			m_Master;//公会会长
	GuildMember*			m_GuileMe;//本人
	uint32					m_GuildNum;
	uint32					m_GuildOnLineNum;
	string					m_GuildName;
	string					m_GuildCommon;
	uint32					m_GuildMoney;
	uint32					m_GuildExp;
	uint32					m_GuildLevel;
	uint32					m_GuildStrongth;
	vector<GuildMember*>	m_GuildMemberOnLine;
	vector<GuildMember*>	m_GuildMenberNonOnLine;
	uint32					m_Mission;

	GuildCampBattleConfig	m_GuildCampBattleConfig;
};
extern CUI_ID_FRAME_GuildBaseInfo s_CUI_ID_FRAME_GuildBaseInfo;
