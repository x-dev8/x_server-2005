/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\HeroRuntime\Client\UI\Tips.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include <string.h>
#ifndef ID_FRAME_Tips
#define ID_FRAME_Tips		"ID_FRAME_Tips"
#endif  ID_FRAME_Tips

#include "UiBase.h"
class CUI_ID_FRAME_Tips :public CUIBase 
{

	// SGuildMember
private:	
	 ControlFrame*	m_pID_FRAME_Tips;

public :
	CUI_ID_FRAME_Tips();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:


	void SetText ( std::string szText );
private:
	std::string m_szData;
};
extern CUI_ID_FRAME_Tips s_CUI_ID_FRAME_Tips;