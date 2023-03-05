/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\SelectBox.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "..\NpcCoord.h"

#ifndef ID_SelectBox
#define ID_SelectBox		"ID_SelectBox"
#endif  ID_SelectBox
#ifndef ID_TEXT_CAPTION
#define ID_TEXT_CAPTION		"ID_TEXT_CAPTION"
#endif  ID_TEXT_CAPTION
#ifndef ID_LIST_SELECT
#define ID_LIST_SELECT		"ID_LIST_SELECT"
#endif  ID_LIST_SELECT
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_PICTURE_Head
#define ID_PICTURE_Head		"ID_PICTURE_Head"
#endif  ID_PICTURE_Head
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_PICTURE_Y_Gantanhao1
#define ID_PICTURE_Y_Gantanhao1		"ID_PICTURE_Y_Gantanhao1"
#endif  ID_PICTURE_Y_Gantanhao1
#ifndef ID_PICTURE_Y_Gantanhao2
#define ID_PICTURE_Y_Gantanhao2		"ID_PICTURE_Y_Gantanhao2"
#endif  ID_PICTURE_Y_Gantanhao2
#ifndef ID_PICTURE_Y_Gantanhao3
#define ID_PICTURE_Y_Gantanhao3		"ID_PICTURE_Y_Gantanhao3"
#endif  ID_PICTURE_Y_Gantanhao3
#ifndef ID_PICTURE_Y_Gantanhao4
#define ID_PICTURE_Y_Gantanhao4		"ID_PICTURE_Y_Gantanhao4"
#endif  ID_PICTURE_Y_Gantanhao4
#ifndef ID_PICTURE_Y_Gantanhao5
#define ID_PICTURE_Y_Gantanhao5		"ID_PICTURE_Y_Gantanhao5"
#endif  ID_PICTURE_Y_Gantanhao5
#ifndef ID_PICTURE_Y_Wenhao1
#define ID_PICTURE_Y_Wenhao1		"ID_PICTURE_Y_Wenhao1"
#endif  ID_PICTURE_Y_Wenhao1
#ifndef ID_PICTURE_Y_Wenhao2
#define ID_PICTURE_Y_Wenhao2		"ID_PICTURE_Y_Wenhao2"
#endif  ID_PICTURE_Y_Wenhao2
#ifndef ID_PICTURE_Y_Wenhao3
#define ID_PICTURE_Y_Wenhao3		"ID_PICTURE_Y_Wenhao3"
#endif  ID_PICTURE_Y_Wenhao3
#ifndef ID_PICTURE_Y_Wenhao4
#define ID_PICTURE_Y_Wenhao4		"ID_PICTURE_Y_Wenhao4"
#endif  ID_PICTURE_Y_Wenhao4
#ifndef ID_PICTURE_Y_Wenhao5
#define ID_PICTURE_Y_Wenhao5		"ID_PICTURE_Y_Wenhao5"
#endif  ID_PICTURE_Y_Wenhao5
#ifndef ID_PICTURE_W_Gantanhao1
#define ID_PICTURE_W_Gantanhao1		"ID_PICTURE_W_Gantanhao1"
#endif  ID_PICTURE_W_Gantanhao1
#ifndef ID_PICTURE_W_Gantanhao2
#define ID_PICTURE_W_Gantanhao2		"ID_PICTURE_W_Gantanhao2"
#endif  ID_PICTURE_W_Gantanhao2
#ifndef ID_PICTURE_W_Gantanhao3
#define ID_PICTURE_W_Gantanhao3		"ID_PICTURE_W_Gantanhao3"
#endif  ID_PICTURE_W_Gantanhao3
#ifndef ID_PICTURE_W_Gantanhao4
#define ID_PICTURE_W_Gantanhao4		"ID_PICTURE_W_Gantanhao4"
#endif  ID_PICTURE_W_Gantanhao4
#ifndef ID_PICTURE_W_Gantanhao5
#define ID_PICTURE_W_Gantanhao5		"ID_PICTURE_W_Gantanhao5"
#endif  ID_PICTURE_W_Gantanhao5
#ifndef ID_PICTURE_W_Wenhao1
#define ID_PICTURE_W_Wenhao1		"ID_PICTURE_W_Wenhao1"
#endif  ID_PICTURE_W_Wenhao1
#ifndef ID_PICTURE_W_Wenhao2
#define ID_PICTURE_W_Wenhao2		"ID_PICTURE_W_Wenhao2"
#endif  ID_PICTURE_W_Wenhao2
#ifndef ID_PICTURE_W_Wenhao3
#define ID_PICTURE_W_Wenhao3		"ID_PICTURE_W_Wenhao3"
#endif  ID_PICTURE_W_Wenhao3
#ifndef ID_PICTURE_W_Wenhao4
#define ID_PICTURE_W_Wenhao4		"ID_PICTURE_W_Wenhao4"
#endif  ID_PICTURE_W_Wenhao4
#ifndef ID_PICTURE_W_Wenhao5
#define ID_PICTURE_W_Wenhao5		"ID_PICTURE_W_Wenhao5"
#endif  ID_PICTURE_W_Wenhao5
#ifndef ID_PICTURE_NpcHead
#define ID_PICTURE_NpcHead		"ID_PICTURE_NpcHead"
#endif  ID_PICTURE_NpcHead

#define MAX_SELECT_ITEM	32
#include "UIBase.h"
class CUI_SelectBox : public CUIBase
{
	typedef bool (*funCallbackFun)( const int nSelectIndex, void *pData );
private:
	// struct
	struct S_SelectBox
	{
		S_SelectBox()
		{
			m_pCallbackFun = NULL;
			m_bModal = true;
			m_nItemCount = 0;
			memset(m_questState, 0, sizeof(m_questState));
		}
		std::string m_strCaption;
		std::string m_strInfo;
		bool m_bModal;
		ControlList::S_List	m_stItem[MAX_SELECT_ITEM];
		int		m_nItemCount;
		funCallbackFun	m_pCallbackFun;
		int m_nQuestCount;
		int m_questState[MAX_SELECT_ITEM];
	};
	// SGuildMember
	ControlFrame*	m_pID_SelectBox;
	ControlText*		m_pID_TEXT_CAPTION;
	ControlList*		m_pID_LIST_SELECT;
	ControlButton*	m_pID_BUTTON_OK;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlText*		m_pID_TEXT_Info;
	ControlButton*	m_pID_BUTTON_Cancel;

	ControlPicture*	m_pID_PICTURE_Y_Gantanhao1;
	ControlPicture*	m_pID_PICTURE_Y_Gantanhao2;
	ControlPicture*	m_pID_PICTURE_Y_Gantanhao3;
	ControlPicture*	m_pID_PICTURE_Y_Gantanhao4;
	ControlPicture*	m_pID_PICTURE_Y_Gantanhao5;
	ControlPicture*	m_pID_PICTURE_Y_Wenhao1;
	ControlPicture*	m_pID_PICTURE_Y_Wenhao2;
	ControlPicture*	m_pID_PICTURE_Y_Wenhao3;
	ControlPicture*	m_pID_PICTURE_Y_Wenhao4;
	ControlPicture*	m_pID_PICTURE_Y_Wenhao5;
	ControlPicture*	m_pID_PICTURE_W_Gantanhao1;
	ControlPicture*	m_pID_PICTURE_W_Gantanhao2;
	ControlPicture*	m_pID_PICTURE_W_Gantanhao3;
	ControlPicture*	m_pID_PICTURE_W_Gantanhao4;
	ControlPicture*	m_pID_PICTURE_W_Gantanhao5;
	ControlPicture*	m_pID_PICTURE_W_Wenhao1;
	ControlPicture*	m_pID_PICTURE_W_Wenhao2;
	ControlPicture*	m_pID_PICTURE_W_Wenhao3;
	ControlPicture*	m_pID_PICTURE_W_Wenhao4;
	ControlPicture*	m_pID_PICTURE_W_Wenhao5;

	ControlPicture*	m_pID_PICTURE_NpcHead;

	ControlGroup m_flagGroup;

	funCallbackFun	m_pCurCallbackFun;
	std::vector<S_SelectBox> m_vtSelectBox;
	std::vector<ControlPicture*> m_vecY_Gantanhao;
	std::vector<ControlPicture*> m_vecY_Wenhao;
	std::vector<ControlPicture*> m_vecW_Gantanhao;
	std::vector<ControlPicture*> m_vecW_Wenhao;

	int	m_nNpcId;

public:
	CUI_SelectBox();

	void Show( const char* szText, const ControlList::S_List* pItem, const int nItemCount,
				const char* szCaption = "", const bool bModal = true,
				const funCallbackFun pFun = NULL, const int nQuestCount = 0,
				const int* questInfos = 0);

	void RetrieveNpcPic();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	// List
	void ID_LIST_SELECTOnListDBClick( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_TEXT_HyberClick(ControlObject* pSender, const char* szData);
	// Button
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	static void ID_SelectBox_onVisibleChanged( ControlObject* pObject );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	//触发键盘Enter消息事件
	static bool frame_BackmsgClick(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed);

	void Refeash();
    void SetNpc( int nId );
	int GetNpc(){ return m_nNpcId; }
	bool PopSelectBox();
	ControlFrame* GetFrame(){ return m_pID_SelectBox; }

	static void TextInfo_HyberClick( ControlObject* pSender, const char* szData );
	bool			m_bCancelScript;
private:
};
extern CUI_SelectBox s_CUI_ID_FRAME_SelectBox;