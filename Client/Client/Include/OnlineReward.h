#pragma once

#include <Windows.h>

// 2012.6.29 wangshuai
// 在线礼包, 根据玩家累计在线时间赠送礼物
// 配置文件:OnlineRewardConfig.h/cpp
// 界面:OnlineAward.h/cpp, OnlineAward2.h/cpp
// 从CPlayerRole里移出作为单件使用
class COnlineReward
{
public:
	enum EOnlineRewardStatus
	{
		ORS_FIRST,		// 第一次开启游戏
		ORS_TIMEFINISH,	// 倒计时结束
		ORS_CLICKOK,	// 点击确定（领取界面的确定按钮）
		ORS_CLICKBOX,	// 点击礼盒
		ORS_GOT,		// 点击获取奖励
		ORS_GOTEND,		// 获取奖励后
		ORS_OVER		// 没有奖励了
	};
public:
	COnlineReward(void);
	virtual ~COnlineReward(void) {}

	static COnlineReward&	Instance()
	{
		static COnlineReward xOnlineReward;
		return xOnlineReward;
	}

	// 重置状态
	void				Reset();

	// 每帧刷新
	void				UpdateOnlineReward();

	// 每帧更新时间
	void				UpdateTime();

	// 设置是否每帧刷新
	void				SetUpdateOnlineReward() {m_bUpdateOnlineReward = TRUE;}

	// 获得礼物
	void				GotOnlineReward(unsigned char rewardId);

	// 获得当前总在线时间
	DWORD				GetCurrentOnlineTime();

	DWORD				GetOnlineTime();//获取当前在线时间

	// 获得当前可领取的最大奖励id.但可能已经领过，需要另外判断
	short				GetMaxCanGetRewardId();

	// 获得下一个奖励id
	short				GetNextRewardId();

	// 显示当前奖励ui( 可能是最大奖励 )
	void				ShowCurrentRewardUI();

	// 设置当前状态
	void				SetCurrentStatus( EOnlineRewardStatus status );

	// 是否还有奖励
	bool				HaveReward();

private:
	// 获取当前能领的礼物，Index从小到大
	short				GetAvailableOnlineReward(int iMaxReward);

	// 设置更新时间
	void				EnableUpdateTime( bool bUpdate ){ m_bUpdateTime = bUpdate; }

	// 有礼物没领，则需要倒计时更新
	BOOL				m_bUpdateOnlineReward;

	// 累计在线游戏时间
	DWORD				m_dwEnterWorldTime;

	// 当前领的礼物Id，从0开始
	short				m_shCurrentReward;

	// 能领的最大礼物Id，从0开始
	short				m_shCanGetMaxReward;

	// 是否更新时间
	bool				m_bUpdateTime;

	// 当前状态
	EOnlineRewardStatus m_eStatus;
};