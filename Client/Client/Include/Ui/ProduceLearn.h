/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\ProduceLearn.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "PlayerRole.h"

#ifndef ID_ProduceLearn
#define ID_ProduceLearn		        "ID_ProduceLearn"
#endif  ID_ProduceLearn
#ifndef ID_TEXT_ProduceName
#define ID_TEXT_ProduceName		    "ID_TEXT_ProduceName"
#endif  ID_TEXT_ProduceName
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		        "ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		        "ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_TEXT_ProduceLevel
#define ID_TEXT_ProduceLevel		"ID_TEXT_ProduceLevel"
#endif  ID_TEXT_ProduceLevel
#ifndef ID_TEXT_ProduceDesc
#define ID_TEXT_ProduceDesc		    "ID_TEXT_ProduceDesc"
#endif  ID_TEXT_ProduceDesc
#ifndef ID_TEXT_NeedLevel
#define ID_TEXT_NeedLevel		    "ID_TEXT_NeedLevel"
#endif  ID_TEXT_NeedLevel
#ifndef ID_TEXT_NeedNum
#define ID_TEXT_NeedNum		        "ID_TEXT_NeedNum"
#endif  ID_TEXT_NeedNum
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		        "ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_Tip
#define ID_TEXT_Tip		            "ID_TEXT_Tip"
#endif  ID_TEXT_Tip
#ifndef ID_LISTIMG_ProduceIcon
#define ID_LISTIMG_ProduceIcon		"ID_LISTIMG_ProduceIcon"
#endif  ID_LISTIMG_ProduceIcon


class CUI_ID_ProduceLearn : public CUIBase
{
private:
    ControlFrame*	    m_pID_ProduceLearn;
    ControlText*	    m_pID_TEXT_ProduceName;
    ControlButton*	    m_pID_BUTTON_CLOSE;
    ControlButton*	    m_pID_BUTTON_OK;
    ControlText*	    m_pID_TEXT_ProduceLevel;
    ControlText*	    m_pID_TEXT_ProduceDesc;
    ControlText*	    m_pID_TEXT_NeedLevel;
    ControlText*	    m_pID_TEXT_NeedNum;
    ControlText*	    m_pID_TEXT_Money;
    ControlText*        m_pID_TEXT_Tip;
    ControlListImage*	m_pID_LISTIMG_ProduceIcon;

public:
    CUI_ID_ProduceLearn();
    bool OnFrameRun();
    bool OnFrameRender();
    bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
    bool ID_LISTIMG_ProduceIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

    void ShowByType( int nRecipeType );
    void Refresh();

protected:
    virtual bool _LoadUI();				// 载入UI
    bool DoControlConnect();	        // 关连控件
    virtual bool _UnLoadUI();			// 卸载UI
    virtual bool _IsVisable();			// 是否可见
    virtual void _SetVisable( const bool bVisable );			// 设置是否可视

    void ResetMembers();

private:
    int m_nSkillId;
    int m_nSkillType;
    int m_nLearnLevel;
};

extern CUI_ID_ProduceLearn s_CUI_ID_ProduceLearn;
