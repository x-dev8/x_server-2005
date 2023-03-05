/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\����\HolyShit.h
*********************************************************************/
#pragma once

#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "CountryDefine.h"

#ifndef ID_FRAME_HolyShit
#define ID_FRAME_HolyShit		"ID_FRAME_HolyShit"
#endif  ID_FRAME_HolyShit
#ifndef ID_TEXT_Country0
#define ID_TEXT_Country0		"ID_TEXT_Country0"
#endif  ID_TEXT_Country0
#ifndef ID_TEXT_Country1
#define ID_TEXT_Country1		"ID_TEXT_Country1"
#endif  ID_TEXT_Country1
#ifndef ID_TEXT_Country2
#define ID_TEXT_Country2		"ID_TEXT_Country2"
#endif  ID_TEXT_Country2
#ifndef ID_TEXT_CountryKill0
#define ID_TEXT_CountryKill0		"ID_TEXT_CountryKill0"
#endif  ID_TEXT_CountryKill0
#ifndef ID_TEXT_CountryKill1
#define ID_TEXT_CountryKill1		"ID_TEXT_CountryKill1"
#endif  ID_TEXT_CountryKill1
#ifndef ID_TEXT_CountryKill2
#define ID_TEXT_CountryKill2		"ID_TEXT_CountryKill2"
#endif  ID_TEXT_CountryKill2

class CUI_ID_FRAME_HolyShit : public CUIBase
{
private:	
	 ControlFrame*	m_pID_FRAME_HolyShit;
     ControlText*	m_pID_TEXT_Country[CountryDefine::Country_Max - 1];
	 ControlText*	m_pID_TEXT_CountryKill[CountryDefine::Country_Max - 1];

public:	
	CUI_ID_FRAME_HolyShit();
	bool OnFrameRun();
	bool OnFrameRender();

	bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	bool _UnLoadUI();			// ж��UI
	bool _IsVisable();			// �Ƿ�ɼ�
	void _SetVisable( const bool bVisable );			// �����Ƿ����

    void SetCountryBattleShow( bool bShow );            // ��ʼ����
    void UpdateKillNumber( uint32* pArray );            // ɱ�����仯

protected:
    void ResetMembers();
};

extern CUI_ID_FRAME_HolyShit s_CUI_ID_FRAME_HolyShit;
