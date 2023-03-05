/********************************************************************
Created by UIEditor.exe
FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\DroitList.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "DroitList.h"

CUI_ID_FRAME_DroitList s_CUI_ID_FRAME_DroitList;
MAP_FRAME_RUN( s_CUI_ID_FRAME_DroitList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_DroitList, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DroitList, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DroitList, ID_BUTTON_HelpOnButtonClick )
CUI_ID_FRAME_DroitList::CUI_ID_FRAME_DroitList()
{
	// Member
	m_pID_FRAME_DroitList = NULL;
	m_pID_PICTURE_30101 = NULL;
	m_pID_PICTURE_TitleDi = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_PICTURE_TitleLeftMiddle = NULL;
	m_pID_PICTURE_TitleRightMiddle = NULL;
	m_pID_PICTURE_TitleLeft = NULL;
	m_pID_PICTURE_TitleRight = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Help = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_PICTURE_Wall20 = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_PICTURE_Wall3 = NULL;
	m_pID_PICTURE_Wall4 = NULL;
	m_pID_PICTURE_Wall5 = NULL;
	m_pID_PICTURE_Wall6 = NULL;
	m_pID_PICTURE_Wall7 = NULL;
	m_pID_PICTURE_Wall8 = NULL;
	m_pID_PICTURE_Wall9 = NULL;
	m_pID_PICTURE_Wall10 = NULL;
	m_pID_PICTURE_Wall11 = NULL;
	m_pID_PICTURE_Wall12 = NULL;
	m_pID_PICTURE_Wall13 = NULL;
	m_pID_TEXT_Q1 = NULL;
	m_pID_TEXT_PlayerLvlZ = NULL;
	m_pID_TEXT_PlayerLvlZ2 = NULL;
	m_pID_TEXT_PlayerLvlZ3 = NULL;
	m_pID_TEXT_PlayerLvlZ4 = NULL;
	m_pID_TEXT_PlayerLvlZ5 = NULL;
	m_pID_TEXT_Q2 = NULL;
	m_pID_TEXT_Q3 = NULL;
	m_pID_TEXT_Q4 = NULL;
	m_pID_TEXT_Q5 = NULL;
	m_pID_TEXT_Q6 = NULL;
	m_pID_TEXT_Q7 = NULL;
	m_pID_TEXT_Q8 = NULL;
	m_pID_TEXT_Q9 = NULL;
	m_pID_TEXT_Q10 = NULL;
	m_pID_TEXT_Q11 = NULL;
	m_pID_TEXT_Q12 = NULL;
	m_pID_TEXT_Q13 = NULL;
	m_pID_TEXT_Q14 = NULL;
	m_pID_PICTURE_1 = NULL;
	m_pID_PICTURE_2 = NULL;
	m_pID_PICTURE_3 = NULL;
	m_pID_PICTURE_4 = NULL;
	m_pID_PICTURE_5 = NULL;
	m_pID_PICTURE_6 = NULL;
	m_pID_PICTURE_7 = NULL;
	m_pID_PICTURE_8 = NULL;
	m_pID_PICTURE_9 = NULL;
	m_pID_PICTURE_10 = NULL;
	m_pID_PICTURE_11 = NULL;
	m_pID_PICTURE_12 = NULL;
	m_pID_PICTURE_13 = NULL;
	m_pID_PICTURE_14 = NULL;
	m_pID_PICTURE_15 = NULL;
	m_pID_PICTURE_16 = NULL;
	m_pID_PICTURE_17 = NULL;
	m_pID_PICTURE_18 = NULL;
	m_pID_PICTURE_19 = NULL;
	m_pID_PICTURE_20 = NULL;
//	m_pID_PICTURE_21 = NULL;
	m_pID_PICTURE_22 = NULL;
	//m_pID_PICTURE_23 = NULL;
	m_pID_PICTURE_24 = NULL;
	m_pID_PICTURE_25 = NULL;
	m_pID_PICTURE_26 = NULL;
	m_pID_PICTURE_27 = NULL;
	m_pID_PICTURE_28 = NULL;
	m_pID_TEXT_E1 = NULL;

}
// Frame
bool CUI_ID_FRAME_DroitList::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_DroitList::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_DroitList::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_DroitList::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_DroitList::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\DroitList.MEUI",false,UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\DroitList.MEUI]失败")
			return false;
	}
	else if ( dwResult != 1/*文件版本号*/ )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\DroitList.MEUI]与源代码版本不一样")
		//	return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_DroitList::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_DroitList, s_CUI_ID_FRAME_DroitListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_DroitList, s_CUI_ID_FRAME_DroitListOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_DroitList, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_DroitListID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_DroitList, ID_BUTTON_Help, s_CUI_ID_FRAME_DroitListID_BUTTON_HelpOnButtonClick );

	m_pID_FRAME_DroitList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_DroitList );
	m_pID_PICTURE_30101 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_30101 );
	m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_TitleDi );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Title );
	m_pID_PICTURE_TitleLeftMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_TitleLeftMiddle );
	m_pID_PICTURE_TitleRightMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_TitleRightMiddle );
	m_pID_PICTURE_TitleLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_TitleLeft );
	m_pID_PICTURE_TitleRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_TitleRight );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_DroitList, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_DroitList, ID_BUTTON_Help );
	m_pID_PICTURE_Wall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall1 );
	m_pID_PICTURE_Wall20 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall20 );
	m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall2 );
	m_pID_PICTURE_Wall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall3 );
	m_pID_PICTURE_Wall4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall4 );
	m_pID_PICTURE_Wall5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall5 );
	m_pID_PICTURE_Wall6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall6 );
	m_pID_PICTURE_Wall7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall7 );
	m_pID_PICTURE_Wall8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall8 );
	m_pID_PICTURE_Wall9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall9 );
	m_pID_PICTURE_Wall10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall10 );
	m_pID_PICTURE_Wall11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall11 );
	m_pID_PICTURE_Wall12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall12 );
	m_pID_PICTURE_Wall13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_Wall13 );
	m_pID_TEXT_Q1 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q1 );
	m_pID_TEXT_PlayerLvlZ = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_PlayerLvlZ );
	m_pID_TEXT_PlayerLvlZ2 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_PlayerLvlZ2 );
	m_pID_TEXT_PlayerLvlZ3 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_PlayerLvlZ3 );
	m_pID_TEXT_PlayerLvlZ4 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_PlayerLvlZ4 );
	m_pID_TEXT_PlayerLvlZ5 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_PlayerLvlZ5 );
	m_pID_TEXT_Q2 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q2 );
	m_pID_TEXT_Q3 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q3 );
	m_pID_TEXT_Q4 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q4 );
	m_pID_TEXT_Q5 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q5 );
	m_pID_TEXT_Q6 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q6 );
	m_pID_TEXT_Q7 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q7 );
	m_pID_TEXT_Q8 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q8 );
	m_pID_TEXT_Q9 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q9 );
	m_pID_TEXT_Q10 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q10 );
	m_pID_TEXT_Q11 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q11 );
	m_pID_TEXT_Q12 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q12 );
	m_pID_TEXT_Q13 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q13 );
	m_pID_TEXT_Q14 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_Q14 );
	m_pID_PICTURE_1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_1 );
	m_pID_PICTURE_2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_2 );
	m_pID_PICTURE_3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_3 );
	m_pID_PICTURE_4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_4 );
	m_pID_PICTURE_5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_5 );
	m_pID_PICTURE_6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_6 );
	m_pID_PICTURE_7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_7 );
	m_pID_PICTURE_8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_8 );
	m_pID_PICTURE_9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_9 );
	m_pID_PICTURE_10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_10 );
	m_pID_PICTURE_11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_11 );
	m_pID_PICTURE_12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_12 );
	m_pID_PICTURE_13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_13 );
	m_pID_PICTURE_14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_14 );
	m_pID_PICTURE_15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_15 );
	m_pID_PICTURE_16 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_16 );
	m_pID_PICTURE_17 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_17 );
	m_pID_PICTURE_18 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_18 );
	m_pID_PICTURE_19 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_19 );
	m_pID_PICTURE_20 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_20 );
//	m_pID_PICTURE_21 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_21 );
	m_pID_PICTURE_22 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_22 );
	//m_pID_PICTURE_23 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_23 );
	m_pID_PICTURE_24 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_24 );
	m_pID_PICTURE_25 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_25 );
	m_pID_PICTURE_26 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_26 );
	m_pID_PICTURE_27 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_27 );
	m_pID_PICTURE_28 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DroitList, ID_PICTURE_28 );
	m_pID_TEXT_E1 = (ControlText*)theUiManager.FindControl( ID_FRAME_DroitList, ID_TEXT_E1 );
	assert( m_pID_FRAME_DroitList );
	assert( m_pID_PICTURE_30101 );
	assert( m_pID_PICTURE_TitleDi );
	assert( m_pID_TEXT_Title );
	assert( m_pID_PICTURE_TitleLeftMiddle );
	assert( m_pID_PICTURE_TitleRightMiddle );
	assert( m_pID_PICTURE_TitleLeft );
	assert( m_pID_PICTURE_TitleRight );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Help );
	assert( m_pID_PICTURE_Wall1 );
	assert( m_pID_PICTURE_Wall20 );
	assert( m_pID_PICTURE_Wall2 );
	assert( m_pID_PICTURE_Wall3 );
	assert( m_pID_PICTURE_Wall4 );
	assert( m_pID_PICTURE_Wall5 );
	assert( m_pID_PICTURE_Wall6 );
	assert( m_pID_PICTURE_Wall7 );
	assert( m_pID_PICTURE_Wall8 );
	assert( m_pID_PICTURE_Wall9 );
	assert( m_pID_PICTURE_Wall10 );
	assert( m_pID_PICTURE_Wall11 );
	assert( m_pID_PICTURE_Wall12 );
	assert( m_pID_PICTURE_Wall13 );
	assert( m_pID_TEXT_Q1 );
	assert( m_pID_TEXT_PlayerLvlZ );
	assert( m_pID_TEXT_PlayerLvlZ2 );
	assert( m_pID_TEXT_PlayerLvlZ3 );
	assert( m_pID_TEXT_PlayerLvlZ4 );
	assert( m_pID_TEXT_PlayerLvlZ5 );
	assert( m_pID_TEXT_Q2 );
	assert( m_pID_TEXT_Q3 );
	assert( m_pID_TEXT_Q4 );
	assert( m_pID_TEXT_Q5 );
	assert( m_pID_TEXT_Q6 );
	assert( m_pID_TEXT_Q7 );
	assert( m_pID_TEXT_Q8 );
	assert( m_pID_TEXT_Q9 );
	assert( m_pID_TEXT_Q10 );
	assert( m_pID_TEXT_Q11 );
	assert( m_pID_TEXT_Q12 );
	assert( m_pID_TEXT_Q13 );
	assert( m_pID_TEXT_Q14 );
	assert( m_pID_PICTURE_1 );
	assert( m_pID_PICTURE_2 );
	assert( m_pID_PICTURE_3 );
	assert( m_pID_PICTURE_4 );
	assert( m_pID_PICTURE_5 );
	assert( m_pID_PICTURE_6 );
	assert( m_pID_PICTURE_7 );
	assert( m_pID_PICTURE_8 );
	assert( m_pID_PICTURE_9 );
	assert( m_pID_PICTURE_10 );
	assert( m_pID_PICTURE_11 );
	assert( m_pID_PICTURE_12 );
	assert( m_pID_PICTURE_13 );
	assert( m_pID_PICTURE_14 );
	assert( m_pID_PICTURE_15 );
	assert( m_pID_PICTURE_16 );
	assert( m_pID_PICTURE_17 );
	assert( m_pID_PICTURE_18 );
	assert( m_pID_PICTURE_19 );
	assert( m_pID_PICTURE_20 );
	//assert( m_pID_PICTURE_21 );
	assert( m_pID_PICTURE_22 );
	//assert( m_pID_PICTURE_23 );
	assert( m_pID_PICTURE_24 );
	assert( m_pID_PICTURE_25 );
	assert( m_pID_PICTURE_26 );
	assert( m_pID_PICTURE_27 );
	assert( m_pID_PICTURE_28 );
	assert( m_pID_TEXT_E1 );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_DroitList::_UnLoadUI()
{
	m_pID_FRAME_DroitList = NULL;
	m_pID_PICTURE_30101 = NULL;
	m_pID_PICTURE_TitleDi = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_PICTURE_TitleLeftMiddle = NULL;
	m_pID_PICTURE_TitleRightMiddle = NULL;
	m_pID_PICTURE_TitleLeft = NULL;
	m_pID_PICTURE_TitleRight = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Help = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_PICTURE_Wall20 = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_PICTURE_Wall3 = NULL;
	m_pID_PICTURE_Wall4 = NULL;
	m_pID_PICTURE_Wall5 = NULL;
	m_pID_PICTURE_Wall6 = NULL;
	m_pID_PICTURE_Wall7 = NULL;
	m_pID_PICTURE_Wall8 = NULL;
	m_pID_PICTURE_Wall9 = NULL;
	m_pID_PICTURE_Wall10 = NULL;
	m_pID_PICTURE_Wall11 = NULL;
	m_pID_PICTURE_Wall12 = NULL;
	m_pID_PICTURE_Wall13 = NULL;
	m_pID_TEXT_Q1 = NULL;
	m_pID_TEXT_PlayerLvlZ = NULL;
	m_pID_TEXT_PlayerLvlZ2 = NULL;
	m_pID_TEXT_PlayerLvlZ3 = NULL;
	m_pID_TEXT_PlayerLvlZ4 = NULL;
	m_pID_TEXT_PlayerLvlZ5 = NULL;
	m_pID_TEXT_Q2 = NULL;
	m_pID_TEXT_Q3 = NULL;
	m_pID_TEXT_Q4 = NULL;
	m_pID_TEXT_Q5 = NULL;
	m_pID_TEXT_Q6 = NULL;
	m_pID_TEXT_Q7 = NULL;
	m_pID_TEXT_Q8 = NULL;
	m_pID_TEXT_Q9 = NULL;
	m_pID_TEXT_Q10 = NULL;
	m_pID_TEXT_Q11 = NULL;
	m_pID_TEXT_Q12 = NULL;
	m_pID_TEXT_Q13 = NULL;
	m_pID_TEXT_Q14 = NULL;
	m_pID_PICTURE_1 = NULL;
	m_pID_PICTURE_2 = NULL;
	m_pID_PICTURE_3 = NULL;
	m_pID_PICTURE_4 = NULL;
	m_pID_PICTURE_5 = NULL;
	m_pID_PICTURE_6 = NULL;
	m_pID_PICTURE_7 = NULL;
	m_pID_PICTURE_8 = NULL;
	m_pID_PICTURE_9 = NULL;
	m_pID_PICTURE_10 = NULL;
	m_pID_PICTURE_11 = NULL;
	m_pID_PICTURE_12 = NULL;
	m_pID_PICTURE_13 = NULL;
	m_pID_PICTURE_14 = NULL;
	m_pID_PICTURE_15 = NULL;
	m_pID_PICTURE_16 = NULL;
	m_pID_PICTURE_17 = NULL;
	m_pID_PICTURE_18 = NULL;
	m_pID_PICTURE_19 = NULL;
	m_pID_PICTURE_20 = NULL;
//	m_pID_PICTURE_21 = NULL;
	m_pID_PICTURE_22 = NULL;
	//m_pID_PICTURE_23 = NULL;
	m_pID_PICTURE_24 = NULL;
	m_pID_PICTURE_25 = NULL;
	m_pID_PICTURE_26 = NULL;
	m_pID_PICTURE_27 = NULL;
	m_pID_PICTURE_28 = NULL;
	m_pID_TEXT_E1 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\DroitList.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_DroitList::_IsVisable()
{
	if( !m_pID_FRAME_DroitList )
		return false;
	return m_pID_FRAME_DroitList->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_DroitList::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_DroitList )
		return;
	m_pID_FRAME_DroitList->SetVisable( bVisable );
}
