/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\����\���ҽ���\Country.h
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

using namespace CountryDefine;

#ifndef ID_FRAME_Country
#define ID_FRAME_Country		"ID_FRAME_Country"
#endif  ID_FRAME_Country
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_CountryTitle
#define ID_TEXT_CountryTitle		"ID_TEXT_CountryTitle"
#endif  ID_TEXT_CountryTitle
#ifndef ID_TEXT_PositionName1
#define ID_TEXT_PositionName1		"ID_TEXT_PositionName1"
#endif  ID_TEXT_PositionName1
#ifndef ID_TEXT_PositionName2
#define ID_TEXT_PositionName2		"ID_TEXT_PositionName2"
#endif  ID_TEXT_PositionName2
#ifndef ID_TEXT_PositionName3
#define ID_TEXT_PositionName3		"ID_TEXT_PositionName3"
#endif  ID_TEXT_PositionName3
#ifndef ID_TEXT_PositionName4
#define ID_TEXT_PositionName4		"ID_TEXT_PositionName4"
#endif  ID_TEXT_PositionName4
#ifndef ID_TEXT_PositionName5
#define ID_TEXT_PositionName5		"ID_TEXT_PositionName5"
#endif  ID_TEXT_PositionName5
#ifndef ID_TEXT_PositionName6
#define ID_TEXT_PositionName6		"ID_TEXT_PositionName6"
#endif  ID_TEXT_PositionName6
#ifndef ID_TEXT_PositionName7
#define ID_TEXT_PositionName7		"ID_TEXT_PositionName7"
#endif  ID_TEXT_PositionName7
#ifndef ID_BUTTON_PositionSet3
#define ID_BUTTON_PositionSet3		"ID_BUTTON_PositionSet3"
#endif  ID_BUTTON_PositionSet3
#ifndef ID_BUTTON_PositionSet4
#define ID_BUTTON_PositionSet4		"ID_BUTTON_PositionSet4"
#endif  ID_BUTTON_PositionSet4
#ifndef ID_BUTTON_PositionSet5
#define ID_BUTTON_PositionSet5		"ID_BUTTON_PositionSet5"
#endif  ID_BUTTON_PositionSet5
#ifndef ID_BUTTON_PositionSet6
#define ID_BUTTON_PositionSet6		"ID_BUTTON_PositionSet6"
#endif  ID_BUTTON_PositionSet6
#ifndef ID_BUTTON_PositionSet7
#define ID_BUTTON_PositionSet7		"ID_BUTTON_PositionSet7"
#endif  ID_BUTTON_PositionSet7
#ifndef ID_TEXT_CountryBroadcast
#define ID_TEXT_CountryBroadcast		"ID_TEXT_CountryBroadcast"
#endif  ID_TEXT_CountryBroadcast
#ifndef ID_TEXT_CountryQuset
#define ID_TEXT_CountryQuset		"ID_TEXT_CountryQuset"
#endif  ID_TEXT_CountryQuset
#ifndef ID_BUTTON_CountryBroadcastNew
#define ID_BUTTON_CountryBroadcastNew		"ID_BUTTON_CountryBroadcastNew"
#endif  ID_BUTTON_CountryBroadcastNew
#ifndef ID_BUTTON_CountryQusetPost
#define ID_BUTTON_CountryQusetPost		"ID_BUTTON_CountryQusetPost"
#endif  ID_BUTTON_CountryQusetPost
#ifndef ID_PICTURE_ResourceGold
#define ID_PICTURE_ResourceGold		"ID_PICTURE_ResourceGold"
#endif  ID_PICTURE_ResourceGold
#ifndef ID_PICTURE_ResourceRock
#define ID_PICTURE_ResourceRock		"ID_PICTURE_ResourceRock"
#endif  ID_PICTURE_ResourceRock
#ifndef ID_PICTURE_ResourceWood
#define ID_PICTURE_ResourceWood		"ID_PICTURE_ResourceWood"
#endif  ID_PICTURE_ResourceWood
#ifndef ID_PICTURE_ResourceFood
#define ID_PICTURE_ResourceFood		"ID_PICTURE_ResourceFood"
#endif  ID_PICTURE_ResourceFood
#ifndef ID_TEXT_ResourceGold
#define ID_TEXT_ResourceGold		"ID_TEXT_ResourceGold"
#endif  ID_TEXT_ResourceGold
#ifndef ID_TEXT_ResourceFood
#define ID_TEXT_ResourceFood		"ID_TEXT_ResourceFood"
#endif  ID_TEXT_ResourceFood
#ifndef ID_TEXT_ResourceRock
#define ID_TEXT_ResourceRock		"ID_TEXT_ResourceRock"
#endif  ID_TEXT_ResourceRock
#ifndef ID_TEXT_ResourceWood
#define ID_TEXT_ResourceWood		"ID_TEXT_ResourceWood"
#endif  ID_TEXT_ResourceWood
#ifndef ID_BUTTON_CollectReasource
#define ID_BUTTON_CollectReasource		"ID_BUTTON_CollectReasource"
#endif  ID_BUTTON_CollectReasource
#ifndef ID_BUTTON_Free
#define ID_BUTTON_Free		"ID_BUTTON_Free"
#endif  ID_BUTTON_Free
#ifndef ID_BUTTON_Prison
#define ID_BUTTON_Prison		"ID_BUTTON_Prison"
#endif  ID_BUTTON_Prison
#ifndef ID_BUTTON_Silence
#define ID_BUTTON_Silence		"ID_BUTTON_Silence"
#endif  ID_BUTTON_Silence
#ifndef ID_BUTTON_Rename
#define ID_BUTTON_Rename		"ID_BUTTON_Rename"
#endif  ID_BUTTON_Rename

#include "UiBase.h"
class CUI_ID_FRAME_Country :public CUIBase
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

private:	
    // Member
    ControlFrame*	m_pID_FRAME_Country;
    ControlButton*	m_pID_BUTTON_Cancel;
    ControlText*	m_pID_TEXT_CountryTitle;
    ControlText*	m_pID_TEXT_PositionName1;
    ControlText*	m_pID_TEXT_PositionName2;
    ControlText*	m_pID_TEXT_PositionName3;
    ControlText*	m_pID_TEXT_PositionName4;
    ControlText*	m_pID_TEXT_PositionName5;
    ControlText*	m_pID_TEXT_PositionName6;
    ControlText*	m_pID_TEXT_PositionName7;
    ControlButton*	m_pID_BUTTON_PositionSet3;
    ControlButton*	m_pID_BUTTON_PositionSet4;
    ControlButton*	m_pID_BUTTON_PositionSet5;
    ControlButton*	m_pID_BUTTON_PositionSet6;
    ControlButton*	m_pID_BUTTON_PositionSet7;
    ControlText*	m_pID_TEXT_CountryBroadcast;
    ControlText*	m_pID_TEXT_CountryQuset;
    ControlButton*	m_pID_BUTTON_CountryBroadcastNew;
    ControlButton*	m_pID_BUTTON_CountryQusetPost;
    ControlPicture*	m_pID_PICTURE_ResourceGold;
    ControlPicture*	m_pID_PICTURE_ResourceRock;
    ControlPicture*	m_pID_PICTURE_ResourceWood;
    ControlPicture*	m_pID_PICTURE_ResourceFood;
    ControlText*	m_pID_TEXT_ResourceGold;
    ControlText*	m_pID_TEXT_ResourceFood;
    ControlText*	m_pID_TEXT_ResourceRock;
    ControlText*	m_pID_TEXT_ResourceWood;
    ControlButton*	m_pID_BUTTON_CollectReasource;
    ControlButton*	m_pID_BUTTON_Free;
    ControlButton*	m_pID_BUTTON_Prison;
    ControlButton*	m_pID_BUTTON_Silence;
    ControlButton*	m_pID_BUTTON_Rename;

public:	
	CUI_ID_FRAME_Country();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PositionSet3OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PositionSet4OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PositionSet5OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PositionSet6OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PositionSet7OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CountryBroadcastNewOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CountryQusetPostOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CollectReasourceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FreeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PrisonOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SilenceOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_RenameOnButtonClick( ControlObject* pSender );
	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	        // �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

public:
	void TryToUpdate();
	void GetCountryInfo( const MsgQueryCountryInfoAck* pMsg );			// ��ȡ������Ϣ
	void GetCountryDate(const MsgUpdateCountryDate* pMsg);				// ��ðﹱ����Ϣ
	void GetRaiseResult( uint8 result );								// ��ȡļ�����
	void GetReceiveMountResult( uint8 result );							// ��ȡ������
	void GetKillOfficialInfo( const MsgTellCountryKillPosition* pMsg );	// ��ȡɱ����Ա��Ϣ
	void GetCountryTitleInfo( uint16 title );							// ��ȡ���ҳƺ���Ϣ������Ȩ��

    void TellCountryDonateResult( uint8 result );                       // ����ļ����
	
	// ���ڹ����ټ���ר�н��棬�ʽ��߼����ڴ˴�
	void GetConveneResult( uint8 result );
	void ShowCountryConvene();
	static bool ProcessConveneReply( const char bYesPress, void *pData );
    // ����ս�������������ר�н���
    void GetBattleSignUpResult( uint8 result );
    void TellCountryBattleSignUp( uint8 nType, uint32 nTime );
    void TellGuildCountryBattleQualify( uint8 nBattleType, uint32 nGuildID );
    void TellCountryBattleEnterBegin( uint8 nBattleType, uint32 nTime );
    void TellCountryBattleBegin( uint8 nBattleType, uint32 nTime );
    void TellCountryBattleResult( uint8 nBattleType, uint8 nWinType, uint32 nGuildID );
    void TellEnterCountryBattle( uint8 nBattleType, uint8 nResult );
    //void TellCountryBattleQuery( uint8 nBattleType, uint8 nResult, uint32 nGuildID );
    void TellBetrayCountryResult( uint8 nResult );
    void TellBetrayCountry( uint8 nCountry, uint8 nPlayerId );
    void TellCountryBattleReplace( uint8 nBattleType );
    void TellCountryWeak( uint8 nWeakCountry );
	void TellCountryStrong( uint8 nStrongCountry );
    void TellCountryNameChange( uint8 nCountryId, char* szName, char* szKingName );
    void TellCountryNameInit( char* szName );
    void TellChangeCountryNameResult( int nResult );
    void TellCountryWarStatus( int nStatus );
    void TellPlayerRaiseResult( const char* pName, int nMoney );

protected:
	static void OnVisibleChange( ControlObject* pUIObject ); 
	void Refresh();
	void ResetProperties();
    void RefreshCountryNameBelongs();                                   // ���Ҹı����Ÿı䵼�µ�ˢ��

private:
	std::string		m_strTaskText;										// �����ı�
	std::string		m_strBroadcastText;									// �����ı�
	std::string		m_strOfficalName[ Position_Max ];	                // ��Ա�����
	std::string		m_strMoney;											// ������Դ string
	uint32			m_nMoney;											// ������Դ int
	uint32			m_nCountryRight;									// ����Ȩ��
	int				m_nTribute;											//zhuxincong 9.17 ���ҹ�Ʒ

	MsgQueryCountryInfoAck::QuestStatus		m_taskStatus[ QuestType_Max ];		// ����״̬

};
extern CUI_ID_FRAME_Country s_CUI_ID_FRAME_Country;
