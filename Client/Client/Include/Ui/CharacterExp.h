/********************************************************************
Created by UIEditor.exe
FileName: F:\workspace\ShenWang\Hero\Program\trunk\Bin\Client\Data\Ui\CharacterExp.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_CharacterExp
#define ID_FRAME_CharacterExp		"ID_FRAME_CharacterExp"
#endif  ID_FRAME_CharacterExp
#ifndef ID_PROGRESS_CharacterExp_Exp
#define ID_PROGRESS_CharacterExp_Exp		"ID_PROGRESS_CharacterExp_Exp"
#endif  ID_PROGRESS_CharacterExp_Exp
#ifndef ID_PROGRESS_CharacterExp_ExpTip
#define ID_PROGRESS_CharacterExp_ExpTip		"ID_PROGRESS_CharacterExp_ExpTip"
#endif  ID_PROGRESS_CharacterExp_ExpTip
#ifndef ID_TEXT_Exp 
#define ID_TEXT_Exp		"ID_TEXT_Exp"
#endif  ID_TEXT_Exp
#ifndef ID_PICTURE_MonsterNum
#define ID_PICTURE_MonsterNum		"ID_PICTURE_MonsterNum"
#endif  ID_PICTURE_MonsterNum
#ifndef ID_PICTURE_Effect
#define ID_PICTURE_Effect		"ID_PICTURE_Effect"
#endif  ID_PICTURE_Effect
#ifndef ID_BUTTON_Other
#define ID_BUTTON_Other		"ID_BUTTON_Other"
#endif  ID_BUTTON_Other
class CSmartAnimation;
#include "UiBase.h"
class CUI_ID_FRAME_CharacterExp :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_CharacterExp();
private:
	ControlFrame*	m_pID_FRAME_CharacterExp;
	ControlProgress*	m_pID_PROGRESS_CharacterExp_Exp;
	//ControlProgress*	m_pID_PROGRESS_CharacterExp_ExpTip;
	ControlText*	m_pID_TEXT_Exp;
    ControlPicture*	m_pID_PICTURE_Effect;
	ControlButton*	m_pID_BUTTON_Other;
public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool OnFrameRenderNeedRedraw();
	bool ID_BUTTON_OtherOnButtonClick( ControlObject* pSender );

	virtual bool	IsHoldInMemory() const { return true; }
    virtual void	InitializeAtEnterWorld();
	bool			IsPtOnOtherButton();
	virtual void	ResetDevice( );
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void SetRedraw()
	{
		if (m_pID_FRAME_CharacterExp)
		{
			m_pID_FRAME_CharacterExp->SetRedraw();
		}
	}

	void EnableAnim( bool bEnable ){ m_bRenderAnim = bEnable; }

    void SetCurrKillNum(DWORD dwValue){m_CurKillMonster = dwValue;}
    void SetTotalKillNum(DWORD dwValue){m_TotalKillMonster = dwValue;}
    int  GetTotalKillNum(){return m_TotalKillMonster;}

    static void  MyMouseMove( ControlObject* pSender );

	void SetExpValue( __int64 exp );
	void SetTextExp( const char* chr );

private:
	static	void OnMouseOnOther( ControlObject* pSender );
    DWORD     m_CurKillMonster;    //当前杀怪数量
    DWORD     m_TotalKillMonster;  //总杀怪数量
	CSmartAnimation*			m_pCoolDownAni;
	CSmartAnimation*			GetCoolDownAniNotNULL() ;
	DWORD						m_dwStartTime;
	bool	m_bRenderAnim;
};

extern CUI_ID_FRAME_CharacterExp s_CUI_ID_FRAME_CharacterExp;
