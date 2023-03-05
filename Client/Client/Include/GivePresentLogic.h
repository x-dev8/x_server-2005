//=================================================================
//
//	好友赠送礼物，用于增加好友亲密度
//	界面:GivePresent.h/cpp
//
//	从CPlayerRole和CGameMain里抽成单件
//=================================================================
#pragma once
#include <windows.h>

#define GIVE_PRESENT_MAX_DIST	10		// 赠送礼物最大距离

class CGivePresentLogic
{
public:
	CGivePresentLogic(void);
	virtual ~CGivePresentLogic(void) {};

	static CGivePresentLogic&	Instance()
	{
		static CGivePresentLogic xGivePresentLogic;
		return xGivePresentLogic;
	}

	// 能否给该玩家赠送礼物
	bool				CanGivePresent(const char* szName);

	// 是否要播放赠送礼物特效
	bool				IsPlayGivePresentEffect() { return m_bPlayGivePresentEffect; }

	// 播放特效开始时间
	DWORD				GetGivePresentEffectStartTime() { return m_dwGivePresentEffectStartTime; }

	// 设置是否需要播放特效
	void				SetPlayGivePresentEffect(bool bPlay);

	// 重置特效
	void				ResetGivePresentFlash();

	// 特效渲染
	void				RenderPlayerGivePresentEffect();

	// 设置特效参数
	void				SetGivePresentFlashRate(float rate) { if(rate > 0) m_fGivePresentFlashRate = rate; }
	void				SetGivePresentDuration(int duration) { if(duration > 0) m_iGivePresentDuration = duration; }
	void				SetGivePresentScale(float scale) { if(scale > 0) m_fGivePresentFlashScale = scale; }

private:

	// 是否播放特效
	bool				m_bPlayGivePresentEffect;

	// 播放特效开始时间（毫秒）
	DWORD				m_dwGivePresentEffectStartTime;

	// 是否淡入淡出模式
	bool				m_bGivePresentFade;

	// 淡入淡出模式:图片闪烁频率；非淡入淡出:持续时间，秒
	float				m_fGivePresentFlashRate;

	// 淡入淡出透明度
	float				m_fLastFlashAlpha;

	// 效果持续时间（毫秒）
	int					m_iGivePresentDuration;

	// 序列帧编号
	int					m_iFlashNo;

	// 上次序列帧是否淡出，从淡出变为淡入时切下一帧
	bool				m_fLastFlashFadeOut;

	// 非淡入淡出模式，当前帧显示时间（毫秒）
	DWORD				m_dwGivePresentFlashElapseTime;

	// 图片显示缩放
	float				m_fGivePresentFlashScale;
};