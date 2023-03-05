/********************************************************************
Created by UIEditor.exe
FileName: E:\work\Client\UI\Guild_Pic.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Guild_Pic.h"
#include "../color_config.h"
#include "MessageBox.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "core/Name.h"

CUI_ID_FRAME_Guild_Pic s_CUI_ID_FRAME_Guild_Pic;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Guild_Pic, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Guild_Pic, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Guild_Pic, ID_BUTTON_COMFIRMOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Guild_Pic, ID_BUTTON_CancelOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Guild_Pic, ID_LIST_TextListOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Guild_Pic, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_Guild_Pic::CUI_ID_FRAME_Guild_Pic()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_Guild_Pic = NULL;
	m_pID_PICTURE_12234 = NULL;
	m_pID_BUTTON_COMFIRM = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_PICTURE_20150 = NULL;
	m_pID_PICTURE_12235 = NULL;
	m_pID_LIST_TextList = NULL;
	m_pID_PICTURE_Image = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	unguard;
}
// Frame
bool CUI_ID_FRAME_Guild_Pic::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Guild_Pic::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_Guild_Pic::ID_BUTTON_COMFIRMOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_Guild_Pic )
		return false;

	if( flst.size() <= 0 )
		return false;

	LOADRESULT	result = CTgaManager::GetTgaManager()->LoadAndCheckIconFromLocal(flst.at(index).c_str());
	switch(result)
	{
    case    LR_SUCCESS:         //成功后什么不做，等待服务器返回
        break;
	case 	LR_FALSE:			//失败
	default:
		break;
	}		
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_Guild_Pic::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_Guild_Pic )
		return false;
	SetVisable(false);
	return true;
	unguard;
}
// List
void CUI_ID_FRAME_Guild_Pic::ID_LIST_TextListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	guardfunc;
	if( !m_pID_FRAME_Guild_Pic )
		return;
	index = m_pID_LIST_TextList->GetCurSelIndex();
	if (index < flst.size())
	{
		S_BaseData::S_Pic pPic;
		RECT rcClient = {0, 0, 32, 32};
		pPic.SetPicStruct(flst.at(index).c_str(), &rcClient, &rcClient);
		m_pID_PICTURE_Image->SetPic(&pPic, true);
		m_pID_PICTURE_Image->SetPicName(flst.at(index).c_str());
	}
	unguard;
}
bool CUI_ID_FRAME_Guild_Pic::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_Guild_Pic )
		return false;
	SetVisable(false);
	return true;
	unguard;
}
// 装载UI
bool CUI_ID_FRAME_Guild_Pic::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Guild_Pic.meui", false, UI_Render_LayerSecond );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Guild_Pic.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_Guild_Pic::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Guild_Pic, s_CUI_ID_FRAME_Guild_PicOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Guild_Pic, s_CUI_ID_FRAME_Guild_PicOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Guild_Pic, ID_BUTTON_COMFIRM, s_CUI_ID_FRAME_Guild_PicID_BUTTON_COMFIRMOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Guild_Pic, ID_BUTTON_Cancel, s_CUI_ID_FRAME_Guild_PicID_BUTTON_CancelOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Guild_Pic, ID_LIST_TextList, s_CUI_ID_FRAME_Guild_PicID_LIST_TextListOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Guild_Pic, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_Guild_PicID_BUTTON_CLOSEOnButtonClick );
	m_pID_FRAME_Guild_Pic = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Guild_Pic );
	m_pID_PICTURE_12234 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Guild_Pic, ID_PICTURE_12234 );
	m_pID_BUTTON_COMFIRM = (ControlButton*)theUiManager.FindControl( ID_FRAME_Guild_Pic, ID_BUTTON_COMFIRM );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Guild_Pic, ID_BUTTON_Cancel );
	m_pID_PICTURE_20150 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Guild_Pic, ID_PICTURE_20150 );
	m_pID_PICTURE_12235 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Guild_Pic, ID_PICTURE_12235 );
	m_pID_LIST_TextList = (ControlList*)theUiManager.FindControl( ID_FRAME_Guild_Pic, ID_LIST_TextList );
	m_pID_PICTURE_Image = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Guild_Pic, ID_PICTURE_Image );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Guild_Pic, ID_BUTTON_CLOSE );
	assert( m_pID_FRAME_Guild_Pic );
	m_pID_FRAME_Guild_Pic->SetVisable( false );
	assert( m_pID_PICTURE_12234 );
	assert( m_pID_BUTTON_COMFIRM );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_PICTURE_20150 );
	assert( m_pID_PICTURE_12235 );
	assert( m_pID_LIST_TextList );
	assert( m_pID_PICTURE_Image );
	assert( m_pID_BUTTON_CLOSE);
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_Guild_Pic::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_Guild_Pic = NULL;
	m_pID_PICTURE_12234 = NULL;
	m_pID_BUTTON_COMFIRM = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_PICTURE_20150 = NULL;
	m_pID_PICTURE_12235 = NULL;
	m_pID_LIST_TextList = NULL;
	m_pID_PICTURE_Image = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\Guild_Pic.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_Guild_Pic::_IsVisable()
{
	guardfunc;
    if(!m_pID_FRAME_Guild_Pic)
        return false;

	return m_pID_FRAME_Guild_Pic->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_Guild_Pic::_SetVisable( const bool bVisable )
{
    if(!m_pID_FRAME_Guild_Pic)
        return;

	guardfunc;
	flst.clear();
	m_pID_LIST_TextList->Clear();
	if (bVisable)
	{
		flst = CTgaManager::GetTgaManager()->FindTgaFile();
		std::string strPath = CTgaManager::GetTgaManager()->FindTgaPath();
		WORD _count =  strPath.size();
		ControlList::S_List	stItem;
		for (WORD i = 0; i < flst.size(); i++)
		{
			std::string str = flst.at(i).c_str();
			str.erase(0,_count);
			stItem.SetData(str.c_str(), 0, NULL,Color_Config.getColor(CC_NPCLIST_NPCTYPE_1));
			m_pID_LIST_TextList->AddItem(&stItem,NULL,true);
		}
	}
	m_pID_FRAME_Guild_Pic->SetVisable( bVisable );
	unguard;
}
