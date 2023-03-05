/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\HelpRemend.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "HelpRemend.h"
#include "IntroductionManager.h"
#include "meui/ExpressionManager.h"
#include "UIMgr.h"
#include "GameSetting.h"
#include "XmlStringLanguage.h"
CUI_ID_FRAME_HelpRemend s_CUI_ID_FRAME_HelpRemend;
MAP_FRAME_RUN( s_CUI_ID_FRAME_HelpRemend, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_HelpRemend, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_HelpRemend, ID_BUTTON_1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_HelpRemend, ID_BUTTON_2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_HelpRemend, ID_BUTTON_3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_HelpRemend, ID_BUTTON_4OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_HelpRemend, ID_BUTTON_5OnButtonClick )
CUI_ID_FRAME_HelpRemend::CUI_ID_FRAME_HelpRemend()
{
	// Member
	m_pID_FRAME_HelpRemend = NULL;
	m_pID_BUTTON_1 = NULL;
	m_pID_BUTTON_2 = NULL;
	m_pID_BUTTON_3 = NULL;
	m_pID_BUTTON_4 = NULL;
	m_pID_BUTTON_5 = NULL;

}
// Frame
bool CUI_ID_FRAME_HelpRemend::OnFrameRun()
{
	if (0 != GameSetting::Instance()->GetLevel( GameSetting::eGSC_IntroductionEnable ))
	{
		SetVisable(true);
	}
	return true;
}
bool CUI_ID_FRAME_HelpRemend::OnFrameRender()
{
	if (false == GameSetting::Instance()->GetLevel( GameSetting::eGSC_IntroductionEnable ))
	{
		SetVisable(false);
		return true;
	}
	
	int nCount = CIntroductionManager::Instance()->GetPopUpCount();
	if (nCount > 5)
	{
		nCount = 5;
	}
	for(int i = 0; i < nCount; ++i)
	{
		m_arrButton[i]->SetVisable(true);
		m_arrButton[i]->GetRealRect(&rcButton[i]);
		ExpressionManager::GetInstance().DrawExpression("#1090",rcButton[i]);
	}
	for(int i = nCount; i < 5; ++i)
	{
		m_arrButton[i]->SetVisable(false);
	}
	
	return true;
}
// Button
bool CUI_ID_FRAME_HelpRemend::ID_BUTTON_1OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_HelpRemend)
		return false;
	CIntroductionManager::Instance()->ShowPopUpTip(0);
	return true;
}
// Button
bool CUI_ID_FRAME_HelpRemend::ID_BUTTON_2OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_HelpRemend)
		return false;
	CIntroductionManager::Instance()->ShowPopUpTip(1);
	return true;
}
// Button
bool CUI_ID_FRAME_HelpRemend::ID_BUTTON_3OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_HelpRemend)
		return false;
	CIntroductionManager::Instance()->ShowPopUpTip(2);
	return true;
}
// Button
bool CUI_ID_FRAME_HelpRemend::ID_BUTTON_4OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_HelpRemend)
		return false;
	CIntroductionManager::Instance()->ShowPopUpTip(3);
	return true;
}
// Button
bool CUI_ID_FRAME_HelpRemend::ID_BUTTON_5OnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_HelpRemend)
		return false;
	CIntroductionManager::Instance()->ShowPopUpTip(4);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_HelpRemend::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\HelpRemend.MEUI",true );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\HelpRemend.MEUI]失败")
		return false;
	}
	else if ( dwResult != 1/*文件版本号*/ )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\HelpRemend.MEUI]与源代码版本不一样")
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_HelpRemend::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_HelpRemend, s_CUI_ID_FRAME_HelpRemendOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_HelpRemend, s_CUI_ID_FRAME_HelpRemendOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_HelpRemend, ID_BUTTON_1, s_CUI_ID_FRAME_HelpRemendID_BUTTON_1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_HelpRemend, ID_BUTTON_2, s_CUI_ID_FRAME_HelpRemendID_BUTTON_2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_HelpRemend, ID_BUTTON_3, s_CUI_ID_FRAME_HelpRemendID_BUTTON_3OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_HelpRemend, ID_BUTTON_4, s_CUI_ID_FRAME_HelpRemendID_BUTTON_4OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_HelpRemend, ID_BUTTON_5, s_CUI_ID_FRAME_HelpRemendID_BUTTON_5OnButtonClick );

	m_pID_FRAME_HelpRemend = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_HelpRemend );
	m_pID_BUTTON_1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_HelpRemend, ID_BUTTON_1 );
	m_pID_BUTTON_2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_HelpRemend, ID_BUTTON_2 );
	m_pID_BUTTON_3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_HelpRemend, ID_BUTTON_3 );
	m_pID_BUTTON_4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_HelpRemend, ID_BUTTON_4 );
	m_pID_BUTTON_5 = (ControlButton*)theUiManager.FindControl( ID_FRAME_HelpRemend, ID_BUTTON_5 );
	assert( m_pID_FRAME_HelpRemend );
	assert( m_pID_BUTTON_1 );
	assert( m_pID_BUTTON_2 );
	assert( m_pID_BUTTON_3 );
	assert( m_pID_BUTTON_4 );
	assert( m_pID_BUTTON_5 );

	m_arrButton[0] = m_pID_BUTTON_1;
	m_arrButton[1] = m_pID_BUTTON_2;
	m_arrButton[2] = m_pID_BUTTON_3;
	m_arrButton[3] = m_pID_BUTTON_4;
	m_arrButton[4] = m_pID_BUTTON_5;

	for(int i = 0; i < 5; ++i)
	{
		m_arrButton[i]->SetShowTip(true);
	}
	USE_SCRIPT ( eUI_OBJECT_HelpRemind, m_pID_FRAME_HelpRemend );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_HelpRemend::_UnLoadUI()
{
    if(!m_pID_FRAME_HelpRemend)
        return false;

	CLOSE_SCRIPT( eUI_OBJECT_HelpRemind );
	m_pID_FRAME_HelpRemend = NULL;
    m_pID_BUTTON_1 = NULL;
    m_pID_BUTTON_2 = NULL;
    m_pID_BUTTON_3 = NULL;
    m_pID_BUTTON_4 = NULL;
    m_pID_BUTTON_5 = NULL;

    m_arrButton[0] = NULL;
    m_arrButton[1] = NULL;
    m_arrButton[2] = NULL;
    m_arrButton[3] = NULL;
    m_arrButton[4] = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\HelpRemend.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_HelpRemend::_IsVisable()
{
    if(!m_pID_FRAME_HelpRemend)
        return false;

	return m_pID_FRAME_HelpRemend->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_HelpRemend::_SetVisable( const bool bVisable )
{
    if(!m_pID_FRAME_HelpRemend)
        return;

	m_pID_FRAME_HelpRemend->SetVisable( bVisable );
}

void CUI_ID_FRAME_HelpRemend::RefreshButtonTips()
{
    if(!m_pID_FRAME_HelpRemend)
        return;

	if (false == GameSetting::Instance()->GetLevel( GameSetting::eGSC_IntroductionEnable ))
	{
		return;
	}
	int nIndex = 0;
	std::list<CIntroductionManager::SIntroductionBase*>& IntroStack = CIntroductionManager::Instance()->GetIntroStack();
	std::list<CIntroductionManager::SIntroductionBase*>::iterator iter = IntroStack.begin();
	for (;(iter != IntroStack.end()) && (nIndex < 5);++iter)
	{
		if (CIntroductionManager::ePopUpIntro == (*iter)->GetIntroductionType())
		{
			CIntroductionManager::SPopUpIntro* pPopUp = (CIntroductionManager::SPopUpIntro*)(*iter);
            if(m_arrButton[nIndex])
            {
                m_arrButton[nIndex]->SetVisable(true);
                m_arrButton[nIndex]->setTip(theXmlString.GetString(pPopUp->nTitleStringId));
            }
			++nIndex;
		}
		
	}
	
}