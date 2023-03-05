/********************************************************************
Created by UIEditor.exe
FileName: E:\Work\HeroRuntime\Client\UI\RbtnMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_RBTNMENU
#define ID_FRAME_RBTNMENU		"ID_FRAME_RBTNMENU"
#endif  ID_FRAME_RBTNMENU
#ifndef ID_BUTTON_TERM
#define ID_BUTTON_TERM		"ID_BUTTON_TERM"
#endif  ID_BUTTON_TERM
#ifndef ID_BUTTON_EXCHANGE
#define ID_BUTTON_EXCHANGE		"ID_BUTTON_EXCHANGE"
#endif  ID_BUTTON_EXCHANGE
#ifndef ID_BUTTON_FRD
#define ID_BUTTON_FRD		"ID_BUTTON_FRD"
#endif  ID_BUTTON_FRD
#ifndef ID_BUTTON_FOLLOWME
#define ID_BUTTON_FOLLOWME		"ID_BUTTON_FOLLOWME"
#endif  ID_BUTTON_FOLLOWME
#ifndef ID_BUTTON_KICKOUT
#define ID_BUTTON_KICKOUT		"ID_BUTTON_KICKOUT"
#endif  ID_BUTTON_KICKOUT
#ifndef ID_BUTTON_Private
#define ID_BUTTON_Private	"ID_BUTTON_Private"
#endif ID_BUTTON_Private
#ifndef ID_BUTTON_SEEK
#define ID_BUTTON_SEEK	"ID_BUTTON_SEEK"
#endif ID_BUTTON_SEEK
#ifndef ID_BUTTON_DUEL
#define ID_BUTTON_DUEL	"ID_BUTTON_DUEL"
#endif ID_BUTTON_DUEL
#ifndef ID_BUTTON_UpgradeTeam
#define ID_BUTTON_UpgradeTeam	"ID_BUTTON_UpgradeTeam"
#endif ID_BUTTON_UpgradeTeam
#ifndef ID_BUTTON_GUILD
#define ID_BUTTON_GUILD	 "ID_BUTTON_GUILD"
#endif ID_BUTTON_GUILD
#ifndef ID_BUTTON_Tuan
#define ID_BUTTON_Tuan	 "ID_BUTTON_Tuan"
#endif ID_BUTTON_Tuan

#ifndef ID_BUTTON_BLACKFRIEND
#define ID_BUTTON_BLACKFRIEND "ID_BUTTON_Heimingdan"
#endif  ID_BUTTON_BLACKFRIEND


class CUI_ID_FRAME_RBTNMENU
{
	// SGuildMember
public:
	CUI_ID_FRAME_RBTNMENU();
public:	
	ControlFrame*	m_pID_FRAME_RBTNMENU;
	ControlButton*	m_pID_BUTTON_TERM;		  // �������
	ControlButton*	m_pID_BUTTON_Tuan;
	ControlButton*	m_pID_BUTTON_EXCHANGE;	  // ����
	ControlButton*	m_pID_BUTTON_FRD;		  // ��Ϊ����
	ControlButton*	m_pID_BUTTON_FOLLOWME;	  // ���� -- ����û��
	ControlButton*	m_pID_BUTTON_KICKOUT;	  // �߳�
	ControlButton*	m_pID_BUTTON_Private;	  // ˽��
	ControlButton*	m_pID_BUTTON_SEEK;		  // �쿴
    ControlButton*	m_pID_BUTTON_DUEL;		  // �д�
	ControlButton*	m_pID_BUTTON_UpgradeTeam; // �����ӳ�
    ControlButton*	m_pID_BUTTON_GUILD;       // �������
    ControlButton*	m_pID_BUTTON_BLACKFRIEND; // ��Ϊ������

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_TERMOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EXCHANGEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FRDOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FOLLOWMEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_KICKOUTOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PrivateOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SeekOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_DuelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UpgradeTeamOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_GUILDOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_BLACKFRIENDOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable, 
public:

		bool bGroupClick = false,
		int index = -1,
		bool showNormal = true,
		BOOL bChat = FALSE );			// �����Ƿ����
	void SetPrivateName( const char* szName)		{ m_szName = szName; }
	const char* GetPrivateName() const				{ return m_szName.c_str(); 	}
	void SetPlayerID( int nID);
	int	 GetPlayerID() const						{ return m_szID; }

	VOID SetPos(INT x, INT y);
	static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	std::string m_szName;	//���������ʱ���� ˽�� ��ҵ����� (��ʱ��Ϊ��ֻ�е�������Ļ���������)
	int			m_szID;		//�������id������Ӻ��� �Ȳ���

	std::vector<ControlButton*>		_vecBtn;

	int			_nGroupID;	//�洢����id

	void SetGroupID(int nID)		{ _nGroupID = nID;}
};
extern CUI_ID_FRAME_RBTNMENU s_CUI_ID_FRAME_RBTNMENU;