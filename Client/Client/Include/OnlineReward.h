#pragma once

#include <Windows.h>

// 2012.6.29 wangshuai
// �������, ��������ۼ�����ʱ����������
// �����ļ�:OnlineRewardConfig.h/cpp
// ����:OnlineAward.h/cpp, OnlineAward2.h/cpp
// ��CPlayerRole���Ƴ���Ϊ����ʹ��
class COnlineReward
{
public:
	enum EOnlineRewardStatus
	{
		ORS_FIRST,		// ��һ�ο�����Ϸ
		ORS_TIMEFINISH,	// ����ʱ����
		ORS_CLICKOK,	// ���ȷ������ȡ�����ȷ����ť��
		ORS_CLICKBOX,	// ������
		ORS_GOT,		// �����ȡ����
		ORS_GOTEND,		// ��ȡ������
		ORS_OVER		// û�н�����
	};
public:
	COnlineReward(void);
	virtual ~COnlineReward(void) {}

	static COnlineReward&	Instance()
	{
		static COnlineReward xOnlineReward;
		return xOnlineReward;
	}

	// ����״̬
	void				Reset();

	// ÿ֡ˢ��
	void				UpdateOnlineReward();

	// ÿ֡����ʱ��
	void				UpdateTime();

	// �����Ƿ�ÿ֡ˢ��
	void				SetUpdateOnlineReward() {m_bUpdateOnlineReward = TRUE;}

	// �������
	void				GotOnlineReward(unsigned char rewardId);

	// ��õ�ǰ������ʱ��
	DWORD				GetCurrentOnlineTime();

	DWORD				GetOnlineTime();//��ȡ��ǰ����ʱ��

	// ��õ�ǰ����ȡ�������id.�������Ѿ��������Ҫ�����ж�
	short				GetMaxCanGetRewardId();

	// �����һ������id
	short				GetNextRewardId();

	// ��ʾ��ǰ����ui( ����������� )
	void				ShowCurrentRewardUI();

	// ���õ�ǰ״̬
	void				SetCurrentStatus( EOnlineRewardStatus status );

	// �Ƿ��н���
	bool				HaveReward();

private:
	// ��ȡ��ǰ��������Index��С����
	short				GetAvailableOnlineReward(int iMaxReward);

	// ���ø���ʱ��
	void				EnableUpdateTime( bool bUpdate ){ m_bUpdateTime = bUpdate; }

	// ������û�죬����Ҫ����ʱ����
	BOOL				m_bUpdateOnlineReward;

	// �ۼ�������Ϸʱ��
	DWORD				m_dwEnterWorldTime;

	// ��ǰ�������Id����0��ʼ
	short				m_shCurrentReward;

	// ������������Id����0��ʼ
	short				m_shCanGetMaxReward;

	// �Ƿ����ʱ��
	bool				m_bUpdateTime;

	// ��ǰ״̬
	EOnlineRewardStatus m_eStatus;
};