/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\TimeString.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TimeString.h"
#include "TimeStringConfig.h"
#include "Common.h"

CUI_ID_FRAME_TimeShow s_CUI_ID_FRAME_TimeShow;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TimeShow, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TimeShow, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TimeShow, ID_LIST_MemberOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TimeShow, ID_LIST_StringOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TimeShow, ID_LIST_TimeOnListSelectChange )
CUI_ID_FRAME_TimeShow::CUI_ID_FRAME_TimeShow()
{
	// Member
	m_pID_FRAME_TimeShow = NULL;
	m_pID_LIST_Member = NULL;
	m_pID_LIST_String = NULL;
	m_pID_LIST_Time = NULL;

}
// Frame
bool CUI_ID_FRAME_TimeShow::OnFrameRun()
{
	if (!IsVisable())
		return false;

	DWORD nowtime = timeGetTime();
	if (nowtime - m_lastTime >= 500)
	{
		RefreshTime();
		m_lastTime = nowtime;
	}

	return true;
}
bool CUI_ID_FRAME_TimeShow::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_TimeShow::ID_LIST_MemberOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_TimeShow::ID_LIST_StringOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_TimeShow::ID_LIST_TimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// 装载UI
bool CUI_ID_FRAME_TimeShow::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TimeString.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TimeString.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TimeShow::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TimeShow, s_CUI_ID_FRAME_TimeShowOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TimeShow, s_CUI_ID_FRAME_TimeShowOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_TimeShow, ID_LIST_Member, s_CUI_ID_FRAME_TimeShowID_LIST_MemberOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TimeShow, ID_LIST_String, s_CUI_ID_FRAME_TimeShowID_LIST_StringOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_TimeShow, ID_LIST_Time, s_CUI_ID_FRAME_TimeShowID_LIST_TimeOnListSelectChange );

	m_pID_FRAME_TimeShow = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TimeShow );
	m_pID_LIST_Member = (ControlList*)theUiManager.FindControl( ID_FRAME_TimeShow, ID_LIST_Member );
	m_pID_LIST_String = (ControlList*)theUiManager.FindControl( ID_FRAME_TimeShow, ID_LIST_String );
	m_pID_LIST_Time = (ControlList*)theUiManager.FindControl( ID_FRAME_TimeShow, ID_LIST_Time );

	assert( m_pID_FRAME_TimeShow );
	assert( m_pID_LIST_Member );
	assert( m_pID_LIST_String );
	assert( m_pID_LIST_Time );

	m_pID_FRAME_TimeShow->SetMsgHoldup( false );
	m_pID_LIST_Member->SetMsgHoldup( false );
	m_pID_LIST_String->SetMsgHoldup( false );
	m_pID_LIST_Time->SetMsgHoldup( false );
	_SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TimeShow::_UnLoadUI()
{
	m_pID_FRAME_TimeShow = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TimeString.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TimeShow::_IsVisable()
{
	if (!m_pID_FRAME_TimeShow)
		return false;
	return m_pID_FRAME_TimeShow->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TimeShow::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_TimeShow)
		return;

	if (bVisable)
	{
		RefreshTime();
		m_lastTime = timeGetTime();
	}

	m_pID_FRAME_TimeShow->SetVisable( bVisable );
}

void CUI_ID_FRAME_TimeShow::InitializeAtEnterWorld()
{
	RefreshTime();
}

void CUI_ID_FRAME_TimeShow::RefreshTime()
{
	if (!m_pID_LIST_Member || !m_pID_LIST_String || !m_pID_LIST_Time)
		return;
	m_pID_LIST_Member->Clear();
	m_pID_LIST_String->Clear();
	m_pID_LIST_Time->Clear();

	std::list<TimeStringManager::TimeData>& timeDataList = theTimeStringManager.GetTimeData();
	if (timeDataList.size() == 0)
		_SetVisable(false);

	for (std::list<TimeStringManager::TimeData>::iterator iter = timeDataList.begin(); iter != timeDataList.end(); iter++)
	{
		if (iter->nTime != 0)
		{
			int n = timeGetTime() - iter->nStartTime;
			int nTime = (iter->nTime - n)/1000;

			if (nTime > 0)
			{
				ControlList::S_List	stItem;
				char szText[128] = {0};

				stItem.SetData( "" );
				m_pID_LIST_Member->AddItem(&stItem, NULL, false);
				stItem.clear();

				stItem.SetData(theTimeStringConfig.GetString(iter->nStringId));
				stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
				m_pID_LIST_String->AddItem(&stItem, NULL, false);
				stItem.clear();

				MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%02d:%02d:%02d",nTime/3600,(nTime/60)%60,nTime%60);
				stItem.SetData(szText);
				stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
				m_pID_LIST_Time->AddItem(&stItem, NULL, false);
			}
			else
			{
				timeDataList.erase(iter);
				break;
			}

		}
	}
}