/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\����\ChatInfoBox.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
// #include "ChatListDlg.h"
#include "FaceDlg1.h"
#include "UIBase.h"
#include "GlobalDef.h"
#include "meui/ControlIconDrag.h"
#include <time.h>
#include <list>
#include <map>
#include "FreeTip.h"
#include "MessageDefine.h"

const int LAST_INFO_MAX		=	10;
const int MAX_FREETIP_COUNT =	3;

class CommonChatFrame 
{
	// Member
public:	
	CommonChatFrame();

	void _Initialize();

	void ClearHyberLinks();

protected:
	ControlFrame*	m_pChatInfoBox;
	ControlEdit*	m_pID_EDIT_INPUT;
	ControlButton*		m_pID_BUTTON_face;
	ControlText*	m_pChatInfoText;
	ControlButton*	m_pID_BUTTON_Enter;
	ControlButton*	m_pID_BUTTON_Bottom;

 	RECT faceRect;
	virtual	bool			IsShow() = 0;
	virtual	void			SetShow(bool bFlag) = 0;
public:
	virtual void			CalFaceRect();
	//--------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------
// 	enum CHAT_TYPE			//��Ӧ����
// 	{
// 		CHAT_TYPE_NORMAL			= 1 << 1,    //��ͨ����
// 		CHAT_TYPE_GUILD				= 1 << 2,    //��������
// 		CHAT_TYPE_TERM				= 1 << 3,    //С������
// 		CHAT_TYPE_PRIVATE			= 1 << 4,    //˽��
// 		CHAT_TYPE_MS				= 1 << 5,    //����
// 		CHAT_TYPE_GAMEPROMPT		= 1 << 6,    //��Ϸ��ʾ CHAT_TYPE_GAMEPROMPT
// 		CHAT_TYPE_BULL				= 1 << 7,    //ȫ������ GM ��ά
// 		CHAT_TYPE_SHOUT				= 1 << 8,    //���� ����������Ź���
// 		CHAT_TYPE_HIGHSHOUT			= 1 << 9,    //�ߺ� ����ͬȫ��-- ��ʵ�������
// 		CHAT_TYPE_GM				= 1 << 10,   //GM �����GM����������Ϣ
// 		CHAT_TYPE_SHOUT_VIP			= 1 << 11,   //���� ����������Ź��� ����vip�� ����С����
// 		CHAT_TYPE_HIGHSHOUT_VIP		= 1 << 12,   //�ߺ� ����ͬȫ��--     ����vip�� С����
// 		CHAT_TYPE_BULL_VIP			= 1 << 13,   //ȫ������--            ����vip�� ��˷�
// 
// 		CHAT_TYPE_PARTICAL1_VIP		= 1 << 14,   //�����С����Ϣ ����vip
// 		CHAT_TYPE_PARTICAL2_VIP		= 1 << 15,   //�����С����Ϣ ����vip
// 		CHAT_TYPE_PARTICAL3_VIP		= 1 << 16,   //�����С����Ϣ ����vip
// 		CHAT_TYPE_PARTICAL4_VIP		= 1 << 17,   //�����С����Ϣ ����vip
// 		CHAT_TYPE_PARTICAL5_VIP		= 1 << 18,   //�����С����Ϣ ����vip
// 		CHAT_TYPE_PARTICAL6_VIP		= 1 << 19,   //�����С����Ϣ ����vip
// 		CHAT_TYPE_PARTICAL7_VIP		= 1 << 20,   //�����С����Ϣ ����vip
// 		CHAT_TYPE_PARTICAL8_VIP		= 1 << 21,   //�����С����Ϣ ����vip
// 		CHAT_TYPE_PARTICAL9_VIP		= 1 << 22,   //�����С����Ϣ ����vip
// 		CHAT_TYPE_PARTICAL10_VIP	= 1 << 23,   //�����С����Ϣ ����vip
// 		CHAT_TYPE_LEAGUE			= 1 << 24,   //��������
//  		CHAT_TYPE_PROGRAM_SYSTEM	= 1 << 25,   //����ϵͳ֪ͨ
//         CHAT_TYPE_FIGHTINFO         = 1 << 26,   //ս����Ϣ
// 		CHAT_TYPE_BATTLE			= 1 << 27,	 //ս����ӪƵ��
// 
// 		CHAT_TYPE_COUNTRY			= 1 << 28,	 //����Ƶ��
// 
// // 
// // 
// // 		CHAT_TYPE_NORMAL = 0,			//��ͨ����
// // 		CHAT_TYPE_GUILD,			//��������
// // 		CHAT_TYPE_TERM,				//С������
// // 		CHAT_TYPE_PRIVATE,			//˽��
// // 		CHAT_TYPE_MS,				//����Ϣϵͳ
// // 		CHAT_TYPE_GAMEPROMPT,				//ϵͳ
// // 		CHAT_TYPE_LEAGUE,           //��������
// // 
// // 		CHAT_TYPE_BULL,				//ȫ������--Ŀǰֻ����gm
// // 		CHAT_TYPE_SHOUT,			//���� ����������Ź���
// // 		CHAT_TYPE_HIGHSHOUT,		//�ߺ� ����ͬȫ��-- ��ʵ�������
// // 		CHAT_TYPE_GM,				//GM �����GM����������Ϣ
// 
// 		CHANNEL_MAX,
// 	};

// 	enum Hyber_Type
// 	{
// 		hyber_init_none,
// 
// 		hyber_one_firstline,					//***************[��Ʒ]*******
// 		//****************
// 		hyber_one_firstandsecondline,			//*************************[��
// 		//Ʒ]*************
// 		hyber_one_secondline,					//****************************
// 		//*****[��Ʒ]*****
// 
// 		hyber_two_all_firstline,				//*****[��Ʒ]******[��Ʒ]*****
// 		//****************
// 		hyber_two_two_firstandsecondline,		//*****[��Ʒ]**************[��
// 		//Ʒ]*************
// 		hyber_two_two_secondline,				//*****[��Ʒ]*****************
// 		//***[��Ʒ]********
// 		hyber_two_first_firstandsecondline,		//*************************[��
// 		//Ʒ]*[��Ʒ]*******
// 		hyber_two_all_secondline,				//****************************
// 		//*[��Ʒ]***[��Ʒ]*
// 
// 		hyber_three_all_firstline,				//**[��Ʒ]**[��Ʒ]****[��Ʒ]**
// 		//****************
// 		hyber_three_three_firstandsecondline,	//**[��Ʒ]**[��Ʒ]**********[��
// 		//Ʒ]*************
// 		hyber_three_three_secondline,			//**[��Ʒ]**[��Ʒ]************
// 		//**[��Ʒ]********
// 		hyber_three_two_firstandsecondline,		//**[��Ʒ]******************[��
// 		//Ʒ]***[��Ʒ]****
// 		hyber_three_two_secondline,				//**[��Ʒ]********************
// 		//**[��Ʒ]**[��Ʒ]
// 		hyber_three_first_firstandsecondline,	//**************************[��
// 		//Ʒ]**[��Ʒ]*[��Ʒ]
// 		hyber_three_all_secondline,				//*****************************
// 		//[��Ʒ][��Ʒ][��Ʒ]*
// 
// 		hyber_max
// 	};

	virtual void AddMyChatHistories( const char* szData );
	virtual void ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData ) = 0;
	bool ID_BUTTON_faceOnButtonClick( ControlObject* pSender );
	virtual bool ID_BUTTON_EnterOnButtonClick( ControlObject* pSender ){return true;}


	bool OnFrameRun();
	bool OnFrameRender();

	bool	IsFreeTipAllShow() const;

	// ��һ��FreeTip��λ��id
	int		FindFreeTipPosId() const;

	// ��һ�����ص�FreeTip��id
	FreeTipPos		FindFreeTipId() const;

	static void	ClearNoteId( int tipId );

	// �������е�FreeTip
	static void	HideAllFreeTip();

	// esc�رղ���
	static bool	EscCloseFreeTip();

	// ָ�����Ƿ���ָ����FreeTip��Close Btn���л������һ����������
	int		PtInAllFreeTipBtn( int x, int y );

	// ָ�����Ƿ���ָ����FreeTip���л������һ����������
	int		PtInAllFreeTip( int x, int y );

	// ��Ⱦ����FreeTip
	void	RenderAllFreeTip();

	// ��������FreeTip
	void	ResetAllFreeTip();

	int		GetFreeTipState( FreeTipState state );

	// FreeTip�ƶ���ʼ����
	bool	FreeTipMoveBeginProc( int x, int y );
	bool	FreeTipMoveProc( int x, int y );
	bool	FreeTipMoveEndProc( int x, int y );

	// ��ʾ����Ĳ���
	static	int		FreeTipPopStack();
	bool			FreeTipPushStack( int tipId );
	void			FreeTipEraseStack( int tipId );
	void			FreeTipSetTop( int tipId );


public:


	void addHyberText( const char* text, __int64 onlyId = 0, int itemid = 0, int nType = 0 );
	void addHyberTextEx( const char* text, uint8 hyberType, int id, int level ); //���ܣ����񣬳��� ����Ϣ���Ϳ������������

	static void HyberRBtnDown( ControlObject* pSender, const char* szName ,int eHyberType);
	static void HyberItemClick( ControlObject* pSender, unsigned char* pItem);
	static void HyberSkillClick( ControlObject* pSender, void* pData );
	static void HyberTaskClick( ControlObject* pSender, void* pData );
	static void HyberPetClick( ControlObject* pSender, void* pData );
	static void HyberMountClick( ControlObject* pSender, void* pData );

	// ������Ʒ�����ӵĻص�
	static void HyberItemEnter( ControlObject* pSender, unsigned char* pItem );

	// �뿪��Ʒ�����ӵĻص�
	static void HyberItemLevel( ControlObject* pSender, unsigned char* pItem );

	static CommonChatFrame*		GetActiveChatFrame();
	static ControlEdit*			GetActiveEditInput();
	static ControlFrame*		GetActiveChatInfoBox();

	static int m_OptFreeTipId;

	static FreeTip m_FreeTip;

	static	FreeTip m_AllFreeTip[MAX_FREETIP_COUNT];
	static	int		m_NoteSort[MAX_FREETIP_COUNT];			// �����У�����˳��ӵļ�¼����
	static	int		m_RenderSort[MAX_FREETIP_COUNT];			// ������ȹصļ�¼����

	void SetPrivateName(const char* szName) { m_szPrivateToName = szName; }
	void SetPrivateToMe(const char* szName) { m_szPrivateToMe = szName; }

	void SetEditFocus();
	void SetEdtActive(bool bFlag);

	void ChangeImmPos();

	std::string	m_szPrivateToName;				//����˽�Ķ�������
	std::string	m_szPrivateToMe;				//�������������

	bool m_bEdtActive;		//��¼�����ʱ�򼤻�
	bool _bActiveInput;		//�Ƿ񼤻������

	bool m_bSendMsg;

	void SetChatType( DWORD dwChatType ){ m_dwChatType = dwChatType; }
	DWORD GetChatType(){ return m_dwChatType; }


	static void		SetActiveChatFrameByEdit(ControlEdit*	pID_EDIT_INPUT);
	static void Task_HyberOtherClick( ControlObject* pSender, const std::string& content ,int nId );

	void InitialCommonChat();

	void Begin2Input();

	void ShowTextInChatList(const std::string& str, const D3DCOLOR col = 0xffffffff,int nConver = MsgChat::CHAT_TYPE_NORMAL, char *szToName = NULL, 
		char* itemData = NULL,int cntHyber = 0, int nBagType = 0, MsgChat* msg = NULL );

	void SendChatMessage(int nDefaultChannel, const char* szData );

	virtual bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed ,ControlObject* pSender);
	// ������ʷ��¼
	struct ChatHistory
	{
		std::string chatInfo;
		std::vector<__int64> hyberItemInfos;	//�������� ��Ʒ���ӵ�ID
		std::vector<int> hyberItemIds;
		int			nAddressHyberCnt;
	};

	int			ItemHyberCnt;
	bool		IsSetPet;

	__int64		_HyberItemInfo[ITEM_HYBER_MAX_CNT];	//�������� ��Ʒ���ӵ�ID
	int			_HyberItemId[ITEM_HYBER_MAX_CNT];
	std::string	_saveItemHyber[ITEM_HYBER_MAX_CNT];
	uint8		_HyberType[ITEM_HYBER_MAX_CNT];
	int			_nBagType;

	int			nAddressHyberCnt;

	typedef std::deque<ChatHistory> ChatHistories;
	ChatHistories chatHistories_;
	int currChatHistoryIndex_;

	static bool				isChatColdTimeXmlLoad;

	static void CommonChatFrame_EditOnLButtonDown(ControlObject* pSender, const char* szData);


	static bool ChatMsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed ,ControlObject* pSender);

	BOOL EditInputIsVisable();

	static void loadXmlChatColdTime();	//����Ƶ����ȴʱ�� ��xml�ļ���ȡ

	void SetInputText(const char* szText)
	{
		if(szText)
			m_pID_EDIT_INPUT->SetText(szText);
	}

	const char* GetEditText();

	void addText( const char* text);

	bool addAddressText( int nMapId, int nMapX,int nMapY);

	void SendMsgChatNormal(const char* chat);

	void RefreshHyberCnt();
	static void EditDataChange( OUT ControlObject* pSender, OUT const char *szData );

	//---��xml��ȡ�� �߻���д�� ����Ƶ������ȴʱ��
	static clock_t			_tmNormalColdTime;
	static clock_t			_tmGuildColdTime;
	static clock_t			_tmTeamColdTime;
	static clock_t			_tmPrivateColdTime;
	static clock_t			_tmMessageColdTime;
	static clock_t			_tmShoutColdTime;		//�� 9����
	static clock_t			_tmHighShoutColdTime;	//�ߺ�
	static clock_t			_tmLeagueColdTime;	//�ߺ�
	static clock_t			_tmZhenYingColdTime;	//��Ӫ
	static clock_t			_tmCountryColdTime;	//��Ӫ

	clock_t			_tmNormalLastTime;
	clock_t			_tmGuildLastTime;
	clock_t			_tmTeamLastTime;
	clock_t			_tmPrivateLastTime;
	clock_t			_tmMessageLastTime;
	clock_t			_tmShoutLastTime;		//�� 9����
	clock_t			_tmHighShoutLastTime;	//�ߺ�
    clock_t         _tmLeagueLastTime;
	clock_t			_tmZhenYingLastTime;	//��Ӫ
	clock_t			_tmCountryLastTime;	//��Ӫ
private:

	virtual void InializeChatByChannel(){;}

// 	std::vector<std::string> m_lstPrivateName;	//˽�������б�

	//--------------------------

	static std::string		_strNormalError;	
	static std::string		_strGuildError;	
	static std::string		_strTeamError;			//error ������Ϣ
	static std::string		_strPrivateError;	
	static std::string		_strMessageError;	
	static std::string		_strShoutError;	
	static std::string		_strHighShoutError;	
    static std::string		_strLeagueError;
	static std::string		_strZhenYingError;
	static std::string		_strCountryError;
	//-----------------------------------------	

    static int              _iNormalLevel;
    static int              _iGuildLevel;
    static int              _iTeamLevel;
    static int              _iPrivateLevel;
	static int              _iMessageLevel;
    static int              _iShoutLevel;
    static int              _iHighShoutLevel;
    static int              _iLeagueLevel;
	static int				_iZhenYingLevel;
	static int				_iCountryLevel;

	static std::vector<std::string> m_vecHelpInfo;	//��ӡ�İ�����Ϣ ����"/help" ��ʱ��

	std::map< __int64, SMountItem > m_mapReceivedMount;

	bool CommandChat(const char *szCommand);			//������������졡����������顡"\˯��"  "\n ���"

	POINT m_ptMouseMove;

	// tip
// 	void ShowItemTip( bool bShow = true );
// 	bool m_bShowTip;
// 	ControlIconDrag::S_ListImg m_ShowItemTip;	
// 	int m_nTipX;
// 	int m_nTipY;

protected:
	DWORD m_dwChatType;


	bool m_bNeedMoveDown; // �����б���Ҫ�Ƶ����һ��

public:
	int GetFontIndex();
	RECT GetRealRect();
	void SetPos(int x,int y);
	int GetFontSize();
	COLORREF GetFontColor();

	ControlEdit* GetEditInput();
};

inline bool CommonChatFrame::IsFreeTipAllShow() const
{
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		if ( !m_AllFreeTip[idx].IsVisible() )
		{
			return false;
		}
	}

	return true;
}

inline int CommonChatFrame::FindFreeTipPosId() const
{
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		if ( m_NoteSort[idx] == -1 )
		{
			return idx;
		}
	}

	return -1;
}

inline FreeTipPos CommonChatFrame::FindFreeTipId() const
{
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		if ( !m_AllFreeTip[idx].IsVisible() )
		{
			return (FreeTipPos)idx;
		}
	}

	return POS_INVALID;
}

inline void CommonChatFrame::ClearNoteId( int tipId )
{
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		if ( m_NoteSort[idx] == tipId )
		{
			m_NoteSort[idx] = -1;
			return ;
		}
	}
}
