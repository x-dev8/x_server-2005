/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CountryChangeInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CountryChangeInfo.h"
#include "CountryBaseInfo.h"
CUI_ID_FRAME_CountryInfo s_CUI_ID_FRAME_CountryInfo;

MAP_FRAME_RUN( s_CUI_ID_FRAME_CountryInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CountryInfo, OnFrameRender )

MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CountryInfo, ID_LIST_TimeOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CountryInfo, ID_LIST_InfoOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CountryInfo, ID_LIST_ValueOnListSelectChange )
CUI_ID_FRAME_CountryInfo::CUI_ID_FRAME_CountryInfo()
{
	// Member
	m_pID_FRAME_CountryInfo = NULL;
	m_pID_LIST_Time = NULL;
	m_pID_LIST_Info = NULL;
	m_pID_LIST_Value = NULL;

}
CUI_ID_FRAME_CountryInfo::~CUI_ID_FRAME_CountryInfo()
{
}
// Frame
bool CUI_ID_FRAME_CountryInfo::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_CountryInfo::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_CountryInfo::ID_LIST_TimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_CountryInfo::ID_LIST_InfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_CountryInfo::ID_LIST_ValueOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// 装载UI
bool CUI_ID_FRAME_CountryInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CountryChangeInfo.meui" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CountryChangeInfo.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CountryInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CountryInfo, s_CUI_ID_FRAME_CountryInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CountryInfo, s_CUI_ID_FRAME_CountryInfoOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_CountryInfo, ID_LIST_Time, s_CUI_ID_FRAME_CountryInfoID_LIST_TimeOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_CountryInfo, ID_LIST_Info, s_CUI_ID_FRAME_CountryInfoID_LIST_InfoOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_CountryInfo, ID_LIST_Value, s_CUI_ID_FRAME_CountryInfoID_LIST_ValueOnListSelectChange );

	m_pID_FRAME_CountryInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CountryInfo );
	m_pID_LIST_Time = (ControlList*)theUiManager.FindControl( ID_FRAME_CountryInfo, ID_LIST_Time );
	m_pID_LIST_Info = (ControlList*)theUiManager.FindControl( ID_FRAME_CountryInfo, ID_LIST_Info );
	m_pID_LIST_Value = (ControlList*)theUiManager.FindControl( ID_FRAME_CountryInfo, ID_LIST_Value );
	assert( m_pID_FRAME_CountryInfo );
	assert( m_pID_LIST_Time );
	assert( m_pID_LIST_Info );
	assert( m_pID_LIST_Value );
	m_pID_FRAME_CountryInfo->SetFather(s_CUI_ID_FRAME_BaseInfo.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CountryInfo::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\CountryChangeInfo.meui" );
}
// 是否可视
bool CUI_ID_FRAME_CountryInfo::_IsVisable()
{
	return m_pID_FRAME_CountryInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CountryInfo::_SetVisable( const bool bVisable )
{
	if(bVisable)
	{
		OnShow();
	}
	m_pID_FRAME_CountryInfo->SetVisable( bVisable );
}
void CUI_ID_FRAME_CountryInfo::OnInitUIInfo()
{
	OnShow();
}
void CUI_ID_FRAME_CountryInfo::OnShow()
{
	//当UI显示的时候 我们刷新UI上全部的值
	m_pID_LIST_Time->Clear();
	m_pID_LIST_Info->Clear();
	m_pID_LIST_Value->Clear();
	for(int i =0;i<CountryDefine::MaxCountryInfoSum;++i)
	{
		int Value = s_CUI_ID_FRAME_BaseInfo.szCountryValue[i];
		__int64 Time = s_CUI_ID_FRAME_BaseInfo.szCountryTime[i];
		const char * info = s_CUI_ID_FRAME_BaseInfo.szCountryInfo[i];
		if(Time == 0)
			continue;
		//设置到UI上面去
		ControlList::S_List	stItem;
		char szText[128] = {0};
		//信息
		stItem.SetData(info);
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_Info->AddItem(&stItem, NULL, false);
		stItem.clear();
		//值	
		MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", Value);
		stItem.SetData(szText);
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_Value->AddItem(&stItem, NULL, false);
		stItem.clear();
		memset(szText, 0, sizeof(szText));
		//日期
		time_t tLog = Time;
		struct tm sysLogTime(*localtime(&tLog));	
		char szTime[128];	
		_stprintf( szTime, _T("%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d"),
			sysLogTime.tm_year+1990, sysLogTime.tm_mon+1, sysLogTime.tm_mday,
			sysLogTime.tm_hour, sysLogTime.tm_min,sysLogTime.tm_sec);

		stItem.SetData(szTime);
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_Time->AddItem(&stItem, NULL, false);
		stItem.clear();
	}
}