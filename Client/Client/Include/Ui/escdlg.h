/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\HeroRuntime\Client\UI\escdlg.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include <time.h>

#ifndef ID_FRAME_ESCDLG
#define ID_FRAME_ESCDLG		"ID_FRAME_ESCDLG"
#endif  ID_FRAME_ESCDLG
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
//#ifndef ID_PICTURE_Title
//#define ID_PICTURE_Title		"ID_PICTURE_Title"
//#endif  ID_PICTURE_Title
#ifndef ID_TEXT_TimeText
#define ID_TEXT_TimeText		"ID_TEXT_TimeText"
#endif  ID_TEXT_TimeText
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain
#ifndef ID_TEXT_WaitTime
#define ID_TEXT_WaitTime		"ID_TEXT_WaitTime"
#endif  ID_TEXT_WaitTime
#ifndef ID_BUTTON_Relive
#define ID_BUTTON_Relive		"ID_BUTTON_Relive"
#endif  ID_BUTTON_Relive
#ifndef ID_BUTTON_Money
#define ID_BUTTON_Money		"ID_BUTTON_Money"
#endif  ID_BUTTON_Money
#ifndef ID_BUTTON_Entrance
#define ID_BUTTON_Entrance		"ID_BUTTON_Entrance"
#endif  ID_BUTTON_Entrance
#ifndef ID_BUTTON_Battle
#define ID_BUTTON_Battle		"ID_BUTTON_Battle"
#endif  ID_BUTTON_Battle

#ifndef ID_BUTTON_CurrPlace
#define ID_BUTTON_CurrPlace		"ID_BUTTON_CurrPlace"
#endif  ID_BUTTON_CurrPlace
#ifndef ID_BUTTON_Perfect
#define ID_BUTTON_Perfect		"ID_BUTTON_Perfect"
#endif  ID_BUTTON_Perfect

#ifndef ID_BUTTON_BaoZou
#define ID_BUTTON_BaoZou		"ID_BUTTON_BaoZou"
#endif  ID_BUTTON_BaoZou
#ifndef ID_BUTTON_TrueBZ
#define ID_BUTTON_TrueBZ		"ID_BUTTON_TrueBZ"
#endif  ID_BUTTON_TrueBZ

#ifndef ID_TEXT_CurrMoney
#define ID_TEXT_CurrMoney		"ID_TEXT_CurrMoney"
#endif	ID_TEXT_CurrMoney
#ifndef ID_TEXT_PerMoney
#define ID_TEXT_PerMoney		"ID_TEXT_PerMoney"
#endif	ID_TEXT_PerMoney

#ifndef ID_TEXT_ReLiveCnt
#define ID_TEXT_ReLiveCnt		"ID_TEXT_ReLiveCnt"
#endif	ID_TEXT_ReLiveCnt

#ifndef ID_BUTTON_NPRelive
#define ID_BUTTON_NPRelive		"ID_BUTTON_NPRelive"
#endif	ID_BUTTON_NPRelive


#ifndef ID_TEXT_ReLiveCntConfig
#define ID_TEXT_ReLiveCntConfig		"ID_TEXT_ReLiveCntConfig"
#endif	ID_TEXT_ReLiveCntConfig

#ifndef ID_LISTIMG_Item
#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
#endif  ID_LISTIMG_Item

#ifndef ID_TEXT_ItemCount
#define ID_TEXT_ItemCount		"ID_TEXT_ItemCount"
#endif  ID_TEXT_ItemCount

#include "UiBase.h"
class CUI_ID_FRAME_ESCDLG :public CUIBase 
{
	// SGuildMember
private:	
	ControlFrame*	m_pID_FRAME_ESCDLG;
	ControlButton*	m_pID_BUTTON_HELP;
	ControlButton*	m_pID_BUTTON_CLOSE;
	//ControlPicture*	m_pID_PICTURE_Title;
	ControlText*	m_pID_TEXT_TimeText;
	ControlText*	m_pID_TEXT_Explain;
	ControlText*	m_pID_TEXT_WaitTime;
	ControlButton*	m_pID_BUTTON_Relive;
	ControlButton*	m_pID_BUTTON_Money;
	ControlButton*	m_pID_BUTTON_Entrance;
	ControlButton*	m_pID_BUTTON_Battle;

	ControlButton*  m_pID_BUTTON_CurrPlace;		//原地复活
	ControlButton*  m_pID_BUTTON_Perfect;		//完美复活
	ControlButton*  m_pID_BUTTON_NPRelive;		//涅槃

	ControlButton*  m_pID_BUTTON_BaoZou;		//暴走复活
	ControlButton*  m_pID_BUTTON_TrueBZ;		//真暴走复活

	ControlText*	m_pID_TEXT_CurrMoney;		//原地复活需要多少钱
	ControlText*	m_pID_TEXT_PerMoney;
	ControlText*	m_pID_TEXT_ReLiveCntConfig;
	ControlText*	m_pID_TEXT_ItemCount;
	ControlListImage*	m_pID_LISTIMG_Item;

	
	 clock_t		_tmWaitStart;
	 clock_t		_tmBeginWait;

	 bool			_bPassWaitFor;

	 std::string	m_strAttackerName;
	 
public:
	 CUI_ID_FRAME_ESCDLG();

ControlText*    m_pID_TEXT_ReLiveCnt;
int             m_HeroReliveCnt ;
	 enum
	 {
		 eReliveOriginNon,//只在 原地复活
		 eReliveOriginAllHpMp,//原地复活HPMP全满
	 };

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ReliveOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MoneyOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EntranceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BattleOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CurrPlaceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PerfectOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_NPReliveOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_TrueBZOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BaoZouOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
public:
	static BYTE byGetBuff;
	void Process();
	void SetPassWaitForFalse()		{ _bPassWaitFor = false; }

	void ClearWaitTime();
	void SetReliveOriginNonRmb(short stValue){m_stReliveOriginNonRmb = stValue;}
	void SetReliveOriginAllHpMpRmb(short stValue){m_stReliveOriginAllHpMpRmb = stValue;}
	int ToSecond( DWORD time);
	void SetAttackerName( const std::string& strName ){ m_strAttackerName = strName; }
	const std::string& GetAttackerName() const{ return m_strAttackerName; }
	void UpdateReliveButton( int nMapType );

	void UpdateReviceSum();
private:
	short m_stReliveOriginNonRmb; 
	short m_stReliveOriginAllHpMpRmb;

	DWORD mNoteTime;
	//DWORD mLostTime;
	DWORD mConfigTime;


private:
	bool CheckIsKingCampMap();
	void SetButtonVisableInKingCamp();
	void ReliveNeedMoney(DWORD &NeedMoney);

};
extern CUI_ID_FRAME_ESCDLG s_CUI_ID_FRAME_ESCDLG;