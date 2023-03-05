/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\StoryTip.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "StoryTip.h"
#include "Common.h"
#include "XmlStringLanguage.h"

extern const char* GetRootPath();
CUI_ID_FRAME_StoryTip s_CUI_ID_FRAME_StoryTip;
MAP_FRAME_RUN( s_CUI_ID_FRAME_StoryTip, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_StoryTip, OnFrameRender )
CUI_ID_FRAME_StoryTip::CUI_ID_FRAME_StoryTip()
{
	// Member
	m_pID_FRAME_StoryTip = NULL;
	m_pID_PICTURE_Bg = NULL;
	m_pID_PICTURE_Word = NULL;
// 	m_pID_TEXT_23250 = NULL;
}

// Frame
bool CUI_ID_FRAME_StoryTip::OnFrameRun()
{
	if(m_pAnim.IsPlaying())
	{
	   m_pAnim.Update();
// 	   m_pID_FRAME_StoryTip->GetFrameRender()->SetWorkingArea(m_pAnim.ShowRect);
	}
	else
	{
		SetVisable( false );
	}
	return true;
}

bool CUI_ID_FRAME_StoryTip::OnFrameRender()
{
	if(m_pAnim.IsPlaying())
	   m_pAnim.Render();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_StoryTip::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\StoryTip.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\StoryTip.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_StoryTip::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_StoryTip, s_CUI_ID_FRAME_StoryTipOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_StoryTip, s_CUI_ID_FRAME_StoryTipOnFrameRender );

	m_pID_FRAME_StoryTip = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_StoryTip );
	m_pID_PICTURE_Bg = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StoryTip, ID_PICTURE_Bg );
	m_pID_PICTURE_Word = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StoryTip, ID_PICTURE_Word );
// 	m_pID_TEXT_23250 = (ControlText*)theUiManager.FindControl( ID_FRAME_StoryTip, ID_TEXT_23250 );
	assert( m_pID_FRAME_StoryTip );
	assert( m_pID_PICTURE_Bg );
	assert( m_pID_PICTURE_Word );
// 	assert( m_pID_TEXT_23250 );

	m_pID_FRAME_StoryTip->enableEscKey(false);
	m_pID_FRAME_StoryTip->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_StoryTip::_UnLoadUI()
{
	m_pID_FRAME_StoryTip = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\StoryTip.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_StoryTip::_IsVisable()
{
	if(!m_pID_FRAME_StoryTip)
		return false;

	return m_pID_FRAME_StoryTip->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_StoryTip::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_StoryTip)
		return;

	m_pID_FRAME_StoryTip->SetVisable( bVisable );
}

void CUI_ID_FRAME_StoryTip::ShowAnim(int nTitleId,int nStringId)
{
	if(!m_pID_FRAME_StoryTip)
		return;

	std::string strInfo = theXmlString.GetString(nStringId);  //格式: [移动速度]绘制的信息
	std::string strBgPic = theXmlString.GetString(nTitleId);

	std::string::size_type nBegin = strInfo.find("[");
	std::string::size_type nEnd   = strInfo.find("]");
	if(nBegin == std::string::npos || nBegin == std::string::npos)
		return;

	std::string strTime = strInfo.substr(1,nEnd - 1);
	std::string strTip = strInfo.substr(nEnd - nBegin + 1);

	DWORD dwTime = 0;
	if(sscanf_s(strTime.c_str(),"%d",&dwTime) != 1)
		return;

 	char szBgPic[256] ={0}; 
 	MeSprintf_s(szBgPic,sizeof(szBgPic),"%s\\%s",GetRootPath(),strBgPic.c_str());

	RECT rc;
	m_pID_PICTURE_Bg->GetRealRect(&rc);
	if(m_pAnim.InitAnim(strBgPic.c_str(),strTip.c_str(),rc,dwTime,m_pID_FRAME_StoryTip->GetFontIndex(),m_pID_FRAME_StoryTip->GetFontColor()))
	   m_pAnim.BeginAnim();
}
