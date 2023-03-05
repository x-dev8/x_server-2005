/********************************************************************
	Created by UIEditor.exe
	FileName: D:\SVNClient\sg_pro\3Guo_Main\FullClient\Data\Ui\LeaveExp.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "LeaveExp.h"
#include "ActivityList.h"
#include "NetworkInput.h"
#include "MessageDefine.h"
CUI_ID_FRAME_LeaveExp s_CUI_ID_FRAME_LeaveExp;
MAP_FRAME_RUN( s_CUI_ID_FRAME_LeaveExp, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_LeaveExp, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LeaveExp, ID_BUTTON_GetExpOnButtonClick )
CUI_ID_FRAME_LeaveExp::CUI_ID_FRAME_LeaveExp()
{
// Member
m_pID_FRAME_LeaveExp = NULL;
m_pID_TEXT_AllKillSum = NULL;
m_pID_TEXT_MaxKillSum = NULL;
m_pID_TEXT_ExpRad = NULL;
m_pID_TEXT_LeaveHour = NULL;
m_pID_TEXT_ExpSum = NULL;
m_pID_BUTTON_GetExp = NULL;

}
// Frame
bool CUI_ID_FRAME_LeaveExp::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_LeaveExp::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_LeaveExp::ID_BUTTON_GetExpOnButtonClick( ControlObject* pSender )
{
	MsgGetLeaveExpReq msg;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_LeaveExp::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\LeaveExp.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\LeaveExp.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_LeaveExp::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_LeaveExp, s_CUI_ID_FRAME_LeaveExpOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_LeaveExp, s_CUI_ID_FRAME_LeaveExpOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_LeaveExp, ID_BUTTON_GetExp, s_CUI_ID_FRAME_LeaveExpID_BUTTON_GetExpOnButtonClick );

	m_pID_FRAME_LeaveExp = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_LeaveExp );
	m_pID_TEXT_AllKillSum = (ControlText*)theUiManager.FindControl( ID_FRAME_LeaveExp, ID_TEXT_AllKillSum );
	m_pID_TEXT_MaxKillSum = (ControlText*)theUiManager.FindControl( ID_FRAME_LeaveExp, ID_TEXT_MaxKillSum );
	m_pID_TEXT_ExpRad = (ControlText*)theUiManager.FindControl( ID_FRAME_LeaveExp, ID_TEXT_ExpRad );
	m_pID_TEXT_LeaveHour = (ControlText*)theUiManager.FindControl( ID_FRAME_LeaveExp, ID_TEXT_LeaveHour );
	m_pID_TEXT_ExpSum = (ControlText*)theUiManager.FindControl( ID_FRAME_LeaveExp, ID_TEXT_ExpSum );
	m_pID_BUTTON_GetExp = (ControlButton*)theUiManager.FindControl( ID_FRAME_LeaveExp, ID_BUTTON_GetExp );
	assert( m_pID_FRAME_LeaveExp );
	assert( m_pID_TEXT_AllKillSum );
	assert( m_pID_TEXT_MaxKillSum );
	assert( m_pID_TEXT_ExpRad );
	assert( m_pID_TEXT_LeaveHour );
	assert( m_pID_TEXT_ExpSum );
	assert( m_pID_BUTTON_GetExp );
	m_pID_FRAME_LeaveExp->SetFather(s_CUI_ID_FRAME_ActivityList.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_LeaveExp::_UnLoadUI()
{
	m_pID_FRAME_LeaveExp = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\LeaveExp.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_LeaveExp::_IsVisable()
{
	return m_pID_FRAME_LeaveExp->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_LeaveExp::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_LeaveExp->SetVisable( bVisable );
}
void CUI_ID_FRAME_LeaveExp::OnShow()
{
	Clear();
	//1.发送命令请求数据
	MsgLeaveExpReq msg;
	GettheNetworkInput().SendMsg(&msg);
	SetVisable( true );
}
void CUI_ID_FRAME_LeaveExp::Clear()
{
	if(!m_pID_FRAME_LeaveExp)
		return;
	m_pID_TEXT_AllKillSum->SetText("0");
	m_pID_TEXT_MaxKillSum->SetText("0");
	m_pID_TEXT_ExpRad->SetText("100");
	m_pID_TEXT_LeaveHour->SetText("0");
	m_pID_TEXT_ExpSum->SetText("0");
	m_pID_BUTTON_GetExp->SetEnable(true);
}
void CUI_ID_FRAME_LeaveExp::SetInfo(unsigned int KillSum,unsigned int MaxKillSum,float Rad,unsigned int Hour,unsigned int Exp)
{
	if(!m_pID_FRAME_LeaveExp)
		return;
	if(!IsVisable())
		return;
	m_pID_BUTTON_GetExp->SetEnable(true);
	char strInfo[64] = {0};
	_ui64toa(KillSum,strInfo,10);
	m_pID_TEXT_AllKillSum->SetText(strInfo);

	memset(strInfo,0,64);
	_ui64toa(MaxKillSum,strInfo,10);
	m_pID_TEXT_MaxKillSum->SetText(strInfo);

	memset(strInfo,0,64);
	sprintf(strInfo,"%0.2f%s",Rad*100,"%");
	m_pID_TEXT_ExpRad->SetText(strInfo);

	memset(strInfo,0,64);
	_ui64toa(Hour,strInfo,10);
	m_pID_TEXT_LeaveHour->SetText(strInfo);

	memset(strInfo,0,64);
	_ui64toa(Exp,strInfo,10);
	m_pID_TEXT_ExpSum->SetText(strInfo);

	if(Exp == 0)
		m_pID_BUTTON_GetExp->SetEnable(false);
}