
#ifndef __CHAT_MESSAGE_MANAGE_H__
#define __CHAT_MESSAGE_MANAGE_H__
#include "MeUi/MeUi.h"
#include "Singleton.h"
#include "CommonChatFrame.h"


class MessageInfoMgr : public Singleton<MessageInfoMgr>
{
public:
	~MessageInfoMgr();
	MessageInfoMgr();
	struct MessageInfo : public MeCommonAllocObj<MessageInfoMgr::MessageInfo>
	{
		MessageInfo()
			:cntHyber(0),items(0)
		{

		}
		~MessageInfo();
		std::string					text;
		bool						IsToMe;
		int							cntHyber;
		SCharItem*					items;
		SYSTEMTIME					time;
		const char*					GetDateTimeRecord();
		const char*					GetTimeRecord();
	};
	struct InfoList : public MeCommonAllocObj<MessageInfoMgr::InfoList>
	{
		InfoList()
			:mSavedIndex(0)
		{

		}
		std::vector<MessageInfo*>		messageList;
		int								mSavedIndex;
		void							Reset();
	};
	void								Reset();

	std::map<std::string, InfoList*>				m_InfoMap;
	MessageInfo*					AddInfoMap(const char* pPlayerName,bool isToMe,const char* pInfo,int cntHyber = 0,char* itemData = NULL);
	InfoList*						GetInfoList(const char* pPlayerName);

	bool							IsNeedSave();
	void							SaveChatMessage(const char* pPlayerName);
	
	void							SaveInfoList( InfoList* pInfoList, const char* pPlayerName);
protected:
	
};





#include "UiBase.h"
class CUI_ID_FRAME_Message_Chat;
class ChatMessageMgr 
{
public:
	ChatMessageMgr();
	~ChatMessageMgr();
	void					Reset();
	void					Clear();
	void					Hide();
	void					Refresh();
public://CUI_ID_FRAME_Message_Chat
	bool OnFrameRunIndexedFrame(int index);
	bool OnFrameRenderIndexedFrame(int index);
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MinimizeOnButtonClick( ControlObject* pSender );
// 	void ID_LIST_CharOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_SaveOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_ClearOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_faceOnButtonClick( ControlObject* pSender );
	void ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_HistoryOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EnterOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AddFriendOnButtonClick(ControlObject* pSender) ;

	BOOL EditInputIsVisable();

	void ShowChatMessageFrame(const char* pPlayerName);
	void RefreshSaveMessageCheckBox();

	void SetActiveChatFrameByEdit(ControlEdit*	pID_EDIT_INPUT);
	int  GetFrameIndexByChildWidget(ControlObject* pSender);

	CUI_ID_FRAME_Message_Chat*				GetActiveMessageFrame();

	bool	AddChatMessage(const char* pPlayerName,const std::string& str, const D3DCOLOR col = 0xffffffff, const UINT nType = MsgChat::CHAT_TYPE_PRIVATE, char *szToName = NULL, 
		char* itemData = NULL, int cntHyber = 0, int nBagType = BT_All );

	bool		IsPtInCloseBtn(int nMouseX, int nMouseY);
private: 
	void AddInfo(  );

	std::vector<CUI_ID_FRAME_Message_Chat*>			mMessageFrameArr;

	int	m_ActiveIndex;
	RECT m_defaultRect;

};

extern ChatMessageMgr chatMessageManage;


#endif