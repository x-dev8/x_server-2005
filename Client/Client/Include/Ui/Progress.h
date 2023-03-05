/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Progress.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef Progress
#define Progress						"Progress"
#endif  Progress
#ifndef ID_PROGRESS
#define ID_PROGRESS						"ID_PROGRESS"
#endif  ID_PROGRESS
#ifndef ID_CASTINGBAR_BORDER
#define ID_CASTINGBAR_BORDER		"ID_CASTINGBAR_BORDER"
#endif  ID_CASTINGBAR_BORDER
#ifndef ID_CASTINGBAR_Full
#define ID_CASTINGBAR_Full		"ID_CASTINGBAR_Full"
#endif  ID_CASTINGBAR_Full

#ifndef ID_CASTINGBAR_Intermit
#define ID_CASTINGBAR_Intermit		"ID_CASTINGBAR_Intermit"
#endif  ID_CASTINGBAR_Intermit
#ifndef ID_TEXT_NAME
#define ID_TEXT_NAME					"ID_TEXT_NAME"
#endif  ID_TEXT_NAME

#include "UIBase.h"
class CUI_Progress : public CUIBase
{
	// SGuildMember
private:
	ControlFrame*	m_pProgress;
	ControlProgress*	m_pID_PROGRESS;
	ControlPicture*	m_pID_CASTINGBAR_BORDER;
	ControlPicture*	m_pID_CASTINGBAR_Intermit;
	ControlPicture*	m_pID_CASTINGBAR_Full;
	ControlText*		m_pID_Text_Name;

public:
	CUI_Progress();


	// Frame
	bool ProgressOnFrameRun();
	bool ProgressOnFrameRender();

	///////////////////////////////
	
private:
	virtual bool _LoadUI();								// ����UI
	bool DoControlConnect();					// �����ؼ�
	virtual bool _UnLoadUI();							// ж��UI
	virtual bool _IsVisable();							// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );		// �����Ƿ����
public:


	enum E_ShowType
	{
		Type_Normal = 0
		,Type_Value
		,Type_Time
	};

	void SetProgressComplete();					// �������
	void ShowByTime( DWORD dwStartTime, DWORD dwPeriod, bool bUp = true,
		int nFlashCount = 0, bool bAutoClose = false, bool bFadeIn = false,
		const char* pName = NULL, bool bIsInterrupt = false, bool bConnectLastProgress = false,
		DWORD dwCorrectValue = 0, BOOL bClientCompletedDisappear = TRUE );
	bool IsInterrupt();							// �Ƿ���
	void BackupPeriodTime( int nBackupPercent );
private:
	void ShowByValue( int nCurValue, int nLowValue = 0, int nHighValue = 1000,
		int nFlashCount = 0, bool bAutoClose = false, bool bFadeIn = false );


	E_ShowType m_enShowType;
	int		m_nFlashCount;
	BOOL	m_bAutoClose;
	BOOL	m_bFadeIn;
	DWORD	m_dwStartTime;
	DWORD	m_dwPeriod;
	BOOL	m_bUp;
	BOOL	m_bProgressComplete;			//�������
	BOOL	m_bIsInterrupt;					//���ж���
	BOOL	m_bClientCompletedDisappear;	//�ͻ��˽�����ɺ����ʧ
};
extern CUI_Progress s_CUI_Progress;
