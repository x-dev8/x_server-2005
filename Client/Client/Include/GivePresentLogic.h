//=================================================================
//
//	������������������Ӻ������ܶ�
//	����:GivePresent.h/cpp
//
//	��CPlayerRole��CGameMain���ɵ���
//=================================================================
#pragma once
#include <windows.h>

#define GIVE_PRESENT_MAX_DIST	10		// ��������������

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

	// �ܷ���������������
	bool				CanGivePresent(const char* szName);

	// �Ƿ�Ҫ��������������Ч
	bool				IsPlayGivePresentEffect() { return m_bPlayGivePresentEffect; }

	// ������Ч��ʼʱ��
	DWORD				GetGivePresentEffectStartTime() { return m_dwGivePresentEffectStartTime; }

	// �����Ƿ���Ҫ������Ч
	void				SetPlayGivePresentEffect(bool bPlay);

	// ������Ч
	void				ResetGivePresentFlash();

	// ��Ч��Ⱦ
	void				RenderPlayerGivePresentEffect();

	// ������Ч����
	void				SetGivePresentFlashRate(float rate) { if(rate > 0) m_fGivePresentFlashRate = rate; }
	void				SetGivePresentDuration(int duration) { if(duration > 0) m_iGivePresentDuration = duration; }
	void				SetGivePresentScale(float scale) { if(scale > 0) m_fGivePresentFlashScale = scale; }

private:

	// �Ƿ񲥷���Ч
	bool				m_bPlayGivePresentEffect;

	// ������Ч��ʼʱ�䣨���룩
	DWORD				m_dwGivePresentEffectStartTime;

	// �Ƿ��뵭��ģʽ
	bool				m_bGivePresentFade;

	// ���뵭��ģʽ:ͼƬ��˸Ƶ�ʣ��ǵ��뵭��:����ʱ�䣬��
	float				m_fGivePresentFlashRate;

	// ���뵭��͸����
	float				m_fLastFlashAlpha;

	// Ч������ʱ�䣨���룩
	int					m_iGivePresentDuration;

	// ����֡���
	int					m_iFlashNo;

	// �ϴ�����֡�Ƿ񵭳����ӵ�����Ϊ����ʱ����һ֡
	bool				m_fLastFlashFadeOut;

	// �ǵ��뵭��ģʽ����ǰ֡��ʾʱ�䣨���룩
	DWORD				m_dwGivePresentFlashElapseTime;

	// ͼƬ��ʾ����
	float				m_fGivePresentFlashScale;
};