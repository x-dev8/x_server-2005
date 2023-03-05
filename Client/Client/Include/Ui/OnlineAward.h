/********************************************************************
	Created by UIEditor.exe
	FileName: E:\OnlineAward.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "PlaneEffect.h"

#ifndef ID_FRAME_OnlineAward
#define ID_FRAME_OnlineAward		"ID_FRAME_OnlineAward"
#endif  ID_FRAME_OnlineAward
#ifndef ID_PICTURE_PageWall
#define ID_PICTURE_PageWall		"ID_PICTURE_PageWall"
#endif  ID_PICTURE_PageWall
#ifndef ID_TEXT_Num
#define ID_TEXT_Num		"ID_TEXT_Num"
#endif  ID_TEXT_Num
#ifndef ID_BUTTON_Gift
#define ID_BUTTON_Gift		"ID_BUTTON_Gift"
#endif  ID_BUTTON_Gift
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time

#include "UiBase.h"
class CUI_ID_FRAME_OnlineAward :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_OnlineAward();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_GiftOnButtonClick( ControlObject* pSender );
    virtual void InitializeAtEnterWorld();
    bool SetNextAward(int time, int index);		// 单位分钟

	/// 仅显示礼包的图片。 
	void ShowOnlyRewardBox( bool bVisible );

	/// 显示礼包特效
	void ShowRewardBoxEffect( bool bShow );

	/// 渲染礼包特效
	void RenderRewardBoxEffect();

	// 获得下次奖励的id
	int GetNextAwardIndex() const{ return m_iNextAwardIndex; }

	bool IsRunning() const;
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	        // 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
    void Reset();


protected:
	DWORD	m_dwNextAwardTime;	// 个礼物领取时间
	int		m_iNextAwardIndex;	// 个礼物ID
	int		m_iAwardDeltaTime;	// 增加delta时间，防止太早领礼物
    int     m_nLastFrameTimeLeft;       // 记录上一帧的送礼剩余时间     added by ZhuoMeng.Hu		[9/30/2010]
	bool	m_bRenderEffectBoxEffect;

	CPlaneEffect	m_kRewardBox;

    ControlFrame*	m_pID_FRAME_OnlineAward;
    ControlPicture*	m_pID_PICTURE_PageWall;
	ControlText*	m_pID_TEXT_Num;
	ControlButton*	m_pID_BUTTON_Gift;
	ControlText*	m_pID_TEXT_Time;
};
extern CUI_ID_FRAME_OnlineAward s_CUI_ID_FRAME_OnlineAward;
