/********************************************************************
	Created by UIEditor.exe
	FileName: E:\OnlineAward2.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "OnLineRewardConfig.h"

#ifndef ID_FRAME_OnlineAward2
#define ID_FRAME_OnlineAward2		"ID_FRAME_OnlineAward2"
#endif  ID_FRAME_OnlineAward2
#ifndef ID_PICTURE_PageWall
#define ID_PICTURE_PageWall		"ID_PICTURE_PageWall"
#endif  ID_PICTURE_PageWall
#ifndef ID_LISTIMG_Hotkey
#define ID_LISTIMG_Hotkey		"ID_LISTIMG_Hotkey"
#endif  ID_LISTIMG_Hotkey
#ifndef ID_TEXT_Word
#define ID_TEXT_Word		"ID_TEXT_Word"
#endif  ID_TEXT_Word
#ifndef ID_BUTTON_GetAward
#define ID_BUTTON_GetAward		"ID_BUTTON_GetAward"
#endif  ID_BUTTON_GetAward
#ifndef ID_PICTURE_ItemWall
#define ID_PICTURE_ItemWall		"ID_PICTURE_ItemWall"
#endif  ID_PICTURE_ItemWall

#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_TEXT_Tips
#define ID_TEXT_Tips		"ID_TEXT_Tips"
#endif  ID_TEXT_Tips

#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_PROGRESS_Effect
#define ID_PROGRESS_Effect		"ID_PROGRESS_Effect"
#endif  ID_PROGRESS_Effect
#ifndef ID_PROGRESS_Effect2
#define ID_PROGRESS_Effect2		"ID_PROGRESS_Effect2"
#endif  ID_PROGRESS_Effect2

#include "UiBase.h"
class CUI_ID_FRAME_OnlineAward2 :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_OnlineAward2();
    virtual void InitializeAtEnterWorld();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_HotkeyOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_HotkeyOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HotkeyOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HotkeyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_GetAwardOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	        // �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
	void Reset();
	bool SetOnlineReward( short index, unsigned short usItemID, unsigned short usItemCount);

    void DisplaySparkEffect();          // ������

public:
	void ClearList();
    void SetButGetAwardEnable(bool bEnable);
	bool ShowOnlineReward( short index, const OnLineRewardConfig::OnLineReward* pReward );

	// ��ʾչʾ����(���text��buttonΪȷ����
	void ShowConfirmAward( int nIndex, const OnLineRewardConfig::OnLineReward* pReward );
	// ��ʾ��ȡ���棨û��text��buttonΪ��ȡ��
	void ShowGetAward();

protected:
	short m_shRewardIndex;
	unsigned short m_usItemID;
	unsigned short m_usItemCount;

    ControlFrame*	m_pID_FRAME_OnlineAward2;
    ControlPicture*	m_pID_PICTURE_PageWall;
    ControlListImage*	m_pID_LISTIMG_Hotkey;
    ControlText*	m_pID_TEXT_Word;
	ControlButton*	m_pID_BUTTON_GetAward;
	ControlButton*	m_pID_BUTTON_OK;
	ControlText*	m_pID_TEXT_Tips;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlProgress*	m_pID_PROGRESS_Effect;
   //ControlPicture*	m_pID_PICTURE_ItemWall;
	 ControlProgress*	m_pID_PROGRESS_Effect2;

private:
    DWORD       m_dwElapse;     // ������Ч��ʱ��
    bool        m_bChange;      // ��������̬�ı�ʶ

};
extern CUI_ID_FRAME_OnlineAward2 s_CUI_ID_FRAME_OnlineAward2;
