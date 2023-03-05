/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\Speaker.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "ChatInfoBox.h"

#ifndef ID_FRAME_Speaker
#define ID_FRAME_Speaker		"ID_FRAME_Speaker"
#endif  ID_FRAME_Speaker
#ifndef ID_PICTURE_EditWall
#define ID_PICTURE_EditWall		"ID_PICTURE_EditWall"
#endif  ID_PICTURE_EditWall
#ifndef ID_EDIT_Info
#define ID_EDIT_Info		"ID_EDIT_Info"
#endif  ID_EDIT_Info
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Msg
#define ID_TEXT_Msg		"ID_TEXT_Msg"
#endif  ID_TEXT_Msg
#ifndef ID_BUTTON_Face
#define ID_BUTTON_Face		"ID_BUTTON_Face"
#endif  ID_BUTTON_Face

#include "UiBase.h"
class CUI_ID_FRAME_Speaker :  public CUI_ChatInfoBox 
{
	// Member
private:
	ControlPicture*	m_pID_PICTURE_EditWall;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlText*	m_pID_TEXT_Msg;
	ControlButton*	m_pID_BUTTON_Face;
	ControlProgress* m_pHornEffect;

public:	
	CUI_ID_FRAME_Speaker();
    virtual bool IsHoldInMemory() const { return false; }

	void AddInfo( const std::string& str, const D3DCOLOR col = 0xffffffff, const UINT nType = MsgChat::CHAT_TYPE_GAMEPROMPT, char *szToName = NULL, 
		char* itemData = NULL, int cntHyber = 0, int nBagType = 0, bool bAutoReply = false );

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FaceOnButtonClick( ControlObject* pSender );
	void SetVisable( const bool bVisable, AN_S2A_OpenClientUI_Flag flag = AN_S2A_OpenUI_ChatBULL );			// 设置是否可视

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable, AN_S2A_OpenClientUI_Flag flag = AN_S2A_OpenUI_ChatBULL );			// 设置是否可视

public:
	ControlListImage* GetListImage();
	void SetListImage( ControlObject* pObject )
	{
		if( !pObject )
			m_pListImage = NULL;
		else
			m_pListImage = (ControlListImage*)pObject; 
	}
	
	int GetItemImgIndex() { return m_nItemImgIndex; }
	void SetItemImgIndex(int index) { m_nItemImgIndex = index; }

	void SetItemId(int id) { m_nItemId = id; }

private:
	ControlListImage* m_pListImage;
	int m_nItemImgIndex;
	int m_nItemId;
	std::list<ChatInfo> m_TempChatInfos;
	DWORD m_dwStartTime; //特效与文字的显示开始时间
	AN_S2A_OpenClientUI_Flag m_flag;

private:
	bool RefreshCharInfo();
	void RenderStarEffect();
	void CheckNeedStopHornEffect();
	void CheckNeedRestartHornEffect();
	void InitMember();

public:
	void RenderEffect();
	void Refresh(int nStartIndex);

protected:
	void _Refresh();
};
extern CUI_ID_FRAME_Speaker s_CUI_ID_FRAME_Speaker;
