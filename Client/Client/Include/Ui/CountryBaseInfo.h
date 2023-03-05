/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CountryBaseInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "CountryMessage.h"
#include "CountryConfig.h"
#include "NetworkInput.h"
#include "Common.h"
#include "XmlStringLanguage.h"
#include "MessageBox.h"
#include "color_config.h"
#include "ScreenInfoManager.h"
#include "UiBase.h"
#ifndef ID_FRAME_BaseInfo
#define ID_FRAME_BaseInfo		"ID_FRAME_BaseInfo"
#endif  ID_FRAME_BaseInfo
#ifndef ID_CHECKBOX_Info
#define ID_CHECKBOX_Info		"ID_CHECKBOX_Info"
#endif  ID_CHECKBOX_Info
#ifndef ID_CHECKBOX_Quest
#define ID_CHECKBOX_Quest		"ID_CHECKBOX_Quest"
#endif  ID_CHECKBOX_Quest
#ifndef ID_CHECKBOX_Position
#define ID_CHECKBOX_Position		"ID_CHECKBOX_Position"
#endif  ID_CHECKBOX_Position
//#ifndef ID_TEXT_CountryName
//#define ID_TEXT_CountryName		"ID_TEXT_CountryName"
//#endif  ID_TEXT_CountryName
#ifndef ID_BUTTON_JinYan
#define ID_BUTTON_JinYan		"ID_BUTTON_JinYan"
#endif  ID_BUTTON_JinYan
#ifndef ID_BUTTON_Common
#define ID_BUTTON_Common		"ID_BUTTON_Common"
#endif  ID_BUTTON_Common
#ifndef ID_BUTTON_Quest
#define ID_BUTTON_Quest		"ID_BUTTON_Quest"
#endif  ID_BUTTON_Quest
#ifndef ID_BUTTON_RewardMoney
#define ID_BUTTON_RewardMoney		"ID_BUTTON_RewardMoney"
#endif  ID_BUTTON_RewardMoney
#ifndef ID_BUTTON_SheMian
#define ID_BUTTON_SheMian		"ID_BUTTON_SheMian"
#endif  ID_BUTTON_SheMian
#ifndef ID_BUTTON_QiuJin
#define ID_BUTTON_QiuJin		"ID_BUTTON_QiuJin"
#endif  ID_BUTTON_QiuJin

#ifndef ID_CHECKBOX_CountryInfo
#define ID_CHECKBOX_CountryInfo		"ID_CHECKBOX_CountryInfo"
#endif  ID_CHECKBOX_CountryInfo


const static string COUNTRYEQUIPNAME = "..\\Data\\Config\\CountryAecorativeClothing.config";

struct	CountryPlayerDisPlayer
{
	uint16		header;
	uint16		face;
	uint8		sex;
	uint16		profession;
};

struct CountryOfficeModeInfo
{
	uint32		OfficeID;
	uint32		MaleModeID;
	uint32		FeMaleModeID;
	float		X;
	float		Y;
	float		Z;
	float		ScaleMale;
	float		ScaleFeMale;
	float		RotationZ;
};

class CUI_ID_FRAME_BaseInfo :public CUIBase
{
public:
	enum EAppointType
	{
		eShowType_None = 0,
		eShowType_AppointJiangJun,
		eShowType_AppointSiMa,
		eShowType_AppointChengXiang,
		eShowType_AppointZuoJiangJun,
		eShowType_AppointYouJiangJun,
		eShowType_JinYan,
		eShowType_QiuJin,
		eShowType_SheMian,
        eShowType_Rename,      
        eShowType_Max
    };
public:	
	 CUI_ID_FRAME_BaseInfo();
	 ControlFrame*		m_pID_FRAME_BaseInfo;
	 ControlCheckBox*	m_pID_CHECKBOX_Info;
	 ControlCheckBox*	m_pID_CHECKBOX_Quest;
	 ControlCheckBox*	m_pID_CHECKBOX_CountryInfo;
	 ControlCheckBox*	m_pID_CHECKBOX_Position;
	 //ControlText*		m_pID_TEXT_CountryName;
	 ControlButton*		m_pID_BUTTON_JinYan;
	 ControlButton*		m_pID_BUTTON_Common;
	 ControlButton*		m_pID_BUTTON_Quest;
	 ControlButton*		m_pID_BUTTON_RewardMoney;
	 ControlButton*		m_pID_BUTTON_SheMian;
	 ControlButton*		m_pID_BUTTON_QiuJin;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_InfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_QuestOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_CountryInfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PositionOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_JinYanOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CommonOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_QuestOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RewardMoneyOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SheMianOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_QiuJinOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual void InitializeAtEnterWorld();
	

	//UI信息处理
	void GetCountryInfo( const MsgQueryCountryInfoAck* pMsg );			// 获取国家信息
	void GetCountryDate(const MsgUpdateCountryDate* pMsg);				// 获得帮贡等信息
	void GetRaiseResult( uint8 result );								// 获取募集结果
	void GetReceiveMountResult( uint8 result );							// 领取坐骑结果
	void GetKillOfficialInfo( const MsgTellCountryKillPosition* pMsg );	// 获取杀死官员信息
	void GetCountryTitleInfo( uint16 title );							// 获取国家称号信息，计算权力
	void TellCountryDonateResult( uint8 result );                       // 国家募捐结果
	void TryToUpdate();

	// 由于国家召集无专有界面，故将逻辑放于此处
	void GetConveneResult( uint8 result );
	void ShowCountryConvene();
	static bool ProcessConveneReply( const char bYesPress, void *pData );
    // 国家战场报名结果，无专有界面
    void GetBattleSignUpResult( uint8 result );
    void TellCountryBattleSignUp( uint8 nType, uint32 nTime );
    void TellGuildCountryBattleQualify( uint8 nBattleType, uint32 nGuildID );
    void TellCountryBattleEnterBegin( uint8 nBattleType, uint32 nTime );
    void TellCountryBattleBegin( uint8 nBattleType, uint32 nTime );
    void TellCountryBattleResult( uint8 nBattleType, uint8 nWinType, uint32 nGuildID );
    void TellEnterCountryBattle( uint8 nBattleType, uint8 nResult );
    //void TellCountryBattleQuery( uint8 nBattleType, uint8 nResult, uint32 nGuildID );
    void TellBetrayCountryResult( uint8 nResult );
    void TellBetrayCountry( uint8 nCountry, GameObjectId nPlayerId );
    void TellCountryBattleReplace( uint8 nBattleType );
    void TellCountryWeak( uint8 nWeakCountry );
	void TellCountryStrong( uint8 nStrongCountry );
    void TellCountryNameChange( uint8 nCountryId, char* szName, char* szKingName );
    void TellCountryNameInit( char* szName );
    void TellChangeCountryNameResult( int nResult );
    void TellCountryWarStatus( int nStatus );
    void TellPlayerRaiseResult( const char* pName, int nMoney );

	void OnAddCountryInfo(const char * szInfo,__int64 Time,int Value);
	void OnLoadCountryInfo(MsgLoadCountryInfoAck * pMsg);

	ControlFrame *GetFrame() { return m_pID_FRAME_BaseInfo;}
private:
	enum CountryUIStates
	{
		CUS_Info = 0,
		CUS_Quest = 1,
		CUS_Official = 2,
		CUS_CountryInfo = 3,
	};
protected:
	static void OnVisibleChange( ControlObject* pUIObject ); 
	void RefreshCountryNameBelongs();   
	void ResetProperties();
private:
	void OnShowUI(CountryUIStates Type = CUS_Official);
	void UpdateUIInfo();
	void LoadConfig();
	void OnUpdateUI();

	bool CheckNeedGetCountryInfo();
public:
	//国家的基本信息
	
	std::string		m_strBroadcastText;									// 公告文本
	std::string		m_strOfficalName[ Position_Max ];	                // 官员玩家名
	std::string		m_strMoney;											// 国家资源 string
	uint32			m_nMoney;											// 国家资源 int
	uint32			m_nCountryRight;									// 国家权力
	uint32			m_nStrongth;										// 国家本周实力
	int				m_nTribute;											//zhuxincong 9.17 国家贡品
	MsgQueryCountryInfoAck::QuestStatus		m_taskStatus[ QuestType_Max ];		// 任务状态

	CountryPlayerDisPlayer m_OfficialDisPlayer[Position_Max];

	CountryOfficeModeInfo	m_ModeInfo[Position_Max];

	char szCountryInfo[CountryDefine::MaxCountryInfoSum][CountryDefine::MaxCountryInfoLength];    //国家的基本信息
	__int64 szCountryTime[CountryDefine::MaxCountryInfoSum];//国家信息的时间记录
	int szCountryValue[CountryDefine::MaxCountryInfoSum];
	bool IsLoad;

};
extern CUI_ID_FRAME_BaseInfo s_CUI_ID_FRAME_BaseInfo;//国家Ui基本窗体
