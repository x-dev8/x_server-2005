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
    bool SetNextAward(int time, int index);		// ��λ����

	/// ����ʾ�����ͼƬ�� 
	void ShowOnlyRewardBox( bool bVisible );

	/// ��ʾ�����Ч
	void ShowRewardBoxEffect( bool bShow );

	/// ��Ⱦ�����Ч
	void RenderRewardBoxEffect();

	// ����´ν�����id
	int GetNextAwardIndex() const{ return m_iNextAwardIndex; }

	bool IsRunning() const;
	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	        // �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
    void Reset();


protected:
	DWORD	m_dwNextAwardTime;	// ��������ȡʱ��
	int		m_iNextAwardIndex;	// ������ID
	int		m_iAwardDeltaTime;	// ����deltaʱ�䣬��ֹ̫��������
    int     m_nLastFrameTimeLeft;       // ��¼��һ֡������ʣ��ʱ��     added by ZhuoMeng.Hu		[9/30/2010]
	bool	m_bRenderEffectBoxEffect;

	CPlaneEffect	m_kRewardBox;

    ControlFrame*	m_pID_FRAME_OnlineAward;
    ControlPicture*	m_pID_PICTURE_PageWall;
	ControlText*	m_pID_TEXT_Num;
	ControlButton*	m_pID_BUTTON_Gift;
	ControlText*	m_pID_TEXT_Time;
};
extern CUI_ID_FRAME_OnlineAward s_CUI_ID_FRAME_OnlineAward;
