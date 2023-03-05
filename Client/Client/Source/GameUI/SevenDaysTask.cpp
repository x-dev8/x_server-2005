/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\SevenDaysTask.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SevenDaysTask.h"
#include "PlayerRole.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "SevenDays.h"
#include "color_config.h"
#include "XmlStringLanguage.h"

const ColorConfigure nStatusColor[5] = 
{
	CC_PetColor_Red,//红色, 未开启
	CC_WhiteName, //白色, 可接取
	CC_ItemTip_ItemBind,//黄色, 进行中
	CC_PetColor_Green, //绿色, 完成，未领奖
	CC_PetColor_Taupe,//灰色, 完成
};

CUI_ID_FRAME_SevenDays_Task s_CUI_ID_FRAME_SevenDays_Task;

MAP_FRAME_RUN( s_CUI_ID_FRAME_SevenDays_Task, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SevenDays_Task, OnFrameRender )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_BUTTON_CLOSEOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LIST_NameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LIST_StateOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LIST_SelectOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item1OnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item1OnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item1OnIconButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item2OnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item2OnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item2OnIconButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_BUTTON_GainTaskOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_BUTTON_RewardOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item3OnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item3OnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item3OnIconButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item4OnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item4OnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SevenDays_Task, ID_LISTIMG_Item4OnIconButtonClick )

CUI_ID_FRAME_SevenDays_Task::CUI_ID_FRAME_SevenDays_Task()
{
	// Member
	m_pID_FRAME_SevenDays_Task = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_LIST_State = NULL;
	m_pID_LIST_Select = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_TEXT_Condition = NULL;
	m_pID_TEXT_Tips = NULL;
	m_pID_LISTIMG_Item1 = NULL;
	m_pID_TEXT_ItemName1 = NULL;
	m_pID_LISTIMG_Item2 = NULL;
	m_pID_TEXT_ItemName2 = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_BUTTON_GainTask = NULL;
	m_pID_BUTTON_Reward = NULL;
	m_pID_LISTIMG_Item3 = NULL;
	m_pID_TEXT_ItemName3 = NULL;
	m_pID_LISTIMG_Item4 = NULL;
	m_pID_TEXT_ItemName4 = NULL;
	m_pID_TEXT_GiftTip = NULL;

	m_lastSelectIndex = 0;

}
CUI_ID_FRAME_SevenDays_Task::~CUI_ID_FRAME_SevenDays_Task()
{
	m_ItemGroup.Clear();
	m_NameGroup.Clear();
}
// Frame
bool CUI_ID_FRAME_SevenDays_Task::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SevenDays_Task::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SevenDays_Task::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// List
void CUI_ID_FRAME_SevenDays_Task::ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_SevenDays_Task::ID_LIST_StateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_SevenDays_Task::ID_LIST_SelectOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	m_lastSelectIndex = m_pID_LIST_Select->GetCurSelIndex();
	InitIntroduce();
	SetIntroduceData();
}
// ListImg / ListEx
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_SevenDays_Task::ID_BUTTON_GainTaskOnButtonClick( ControlObject* pSender )
{
	if ( m_lastSelectIndex < SevenDaysConfig::TD_FirstDay || m_lastSelectIndex > SevenDaysConfig::TD_SeventhDay )
		return false;

	MsgAskSevenDaysTask msg;
	msg.index = m_lastSelectIndex;
	GettheNetworkInput().SendMsg( &msg );

	return true;
}
// Button
bool CUI_ID_FRAME_SevenDays_Task::ID_BUTTON_RewardOnButtonClick( ControlObject* pSender )
{
	if ( m_lastSelectIndex < SevenDaysConfig::TD_FirstDay || m_lastSelectIndex > SevenDaysConfig::TD_SeventhDay )
		return false;

	MsgAskSevenDaysReward msg;
	msg.index = m_lastSelectIndex;
	GettheNetworkInput().SendMsg( &msg );

	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															   ControlIconDrag::S_ListImg* pItemDrag,
															   ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															   ControlIconDrag::S_ListImg* pItemDrag,
															   ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SevenDays_Task::ID_LISTIMG_Item4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// 装载UI
bool CUI_ID_FRAME_SevenDays_Task::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SevenDaysTask.meui", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SevenDaysTask.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SevenDays_Task::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SevenDays_Task, s_CUI_ID_FRAME_SevenDays_TaskOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SevenDays_Task, s_CUI_ID_FRAME_SevenDays_TaskOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SevenDays_Task, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SevenDays_TaskID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_SevenDays_Task, ID_LIST_Name, s_CUI_ID_FRAME_SevenDays_TaskID_LIST_NameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_SevenDays_Task, ID_LIST_State, s_CUI_ID_FRAME_SevenDays_TaskID_LIST_StateOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_SevenDays_Task, ID_LIST_Select, s_CUI_ID_FRAME_SevenDays_TaskID_LIST_SelectOnListSelectChange );
	theUiManager.OnIconDragOn( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item1, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item1, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item1OnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item1, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item1OnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item1, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item1OnIconButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item2, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item2, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item2OnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item2, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item2OnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item2, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item2OnIconButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SevenDays_Task, ID_BUTTON_GainTask, s_CUI_ID_FRAME_SevenDays_TaskID_BUTTON_GainTaskOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SevenDays_Task, ID_BUTTON_Reward, s_CUI_ID_FRAME_SevenDays_TaskID_BUTTON_RewardOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item3, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item3, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item3OnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item3, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item3OnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item3, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item3OnIconButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item4, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item4, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item4OnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item4, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item4OnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item4, s_CUI_ID_FRAME_SevenDays_TaskID_LISTIMG_Item4OnIconButtonClick );

	m_pID_FRAME_SevenDays_Task = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SevenDays_Task );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_BUTTON_CLOSE );
	m_pID_LIST_Name = (ControlList*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_LIST_Name );
	m_pID_LIST_State = (ControlList*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_LIST_State );
	m_pID_LIST_Select = (ControlList*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_LIST_Select );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_TEXT_Title );
	m_pID_TEXT_Condition = (ControlText*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_TEXT_Condition );
	m_pID_TEXT_Tips = (ControlText*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_TEXT_Tips );
	m_pID_LISTIMG_Item1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item1 );
	m_pID_TEXT_ItemName1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_TEXT_ItemName1 );
	m_pID_LISTIMG_Item2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item2 );
	m_pID_TEXT_ItemName2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_TEXT_ItemName2 );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_TEXT_Money );
	m_pID_BUTTON_GainTask = (ControlButton*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_BUTTON_GainTask );
	m_pID_BUTTON_Reward = (ControlButton*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_BUTTON_Reward );
	m_pID_LISTIMG_Item3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item3 );
	m_pID_TEXT_ItemName3 = (ControlText*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_TEXT_ItemName3 );
	m_pID_LISTIMG_Item4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_LISTIMG_Item4 );
	m_pID_TEXT_ItemName4 = (ControlText*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_TEXT_ItemName4 );
	m_pID_TEXT_GiftTip = (ControlText*)theUiManager.FindControl( ID_FRAME_SevenDays_Task, ID_TEXT_GiftTip );

	assert( m_pID_FRAME_SevenDays_Task );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_LIST_Name );
	assert( m_pID_LIST_State );
	assert( m_pID_LIST_Select );
	assert( m_pID_TEXT_Title );
	assert( m_pID_TEXT_Condition );
	assert( m_pID_TEXT_Tips );
	assert( m_pID_LISTIMG_Item1 );
	assert( m_pID_TEXT_ItemName1 );
	assert( m_pID_LISTIMG_Item2 );
	assert( m_pID_TEXT_ItemName2 );
	assert( m_pID_TEXT_Money );
	assert( m_pID_BUTTON_GainTask );
	assert( m_pID_BUTTON_Reward );
	assert( m_pID_LISTIMG_Item3 );
	assert( m_pID_TEXT_ItemName3 );
	assert( m_pID_LISTIMG_Item4 );
	assert( m_pID_TEXT_ItemName4 );
	assert( m_pID_TEXT_GiftTip );

	m_ItemGroup.Clear();
	m_NameGroup.Clear();

	m_ItemGroup.AddControl( m_pID_LISTIMG_Item1 );
	m_ItemGroup.AddControl( m_pID_LISTIMG_Item2 );
	m_ItemGroup.AddControl( m_pID_LISTIMG_Item3 );
	m_ItemGroup.AddControl( m_pID_LISTIMG_Item4 );

	m_NameGroup.AddControl( m_pID_TEXT_ItemName1 );
	m_NameGroup.AddControl( m_pID_TEXT_ItemName2 );
	m_NameGroup.AddControl( m_pID_TEXT_ItemName3 );
	m_NameGroup.AddControl( m_pID_TEXT_ItemName4 );

	m_pID_LIST_Name->SetMsgHoldup(false);
	m_pID_LIST_State->SetMsgHoldup(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SevenDays_Task::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\SevenDaysTask.meui" );
}
// 是否可视
bool CUI_ID_FRAME_SevenDays_Task::_IsVisable()
{
	return m_pID_FRAME_SevenDays_Task->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SevenDays_Task::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_SevenDays_Task->SetVisable( bVisable );
	
	if ( bVisable )
	{
		Refresh();
	}
	
}

void CUI_ID_FRAME_SevenDays_Task::Init()
{
	m_pID_LIST_Name->Clear();
	m_pID_LIST_State->Clear();
	m_pID_LIST_Select->Clear();

	InitIntroduce();

	//m_lastSelectIndex = 0;
}

void CUI_ID_FRAME_SevenDays_Task::InitIntroduce()
{
	m_pID_TEXT_Title->SetText("");
	m_pID_TEXT_Condition->SetText("");
	m_pID_TEXT_Tips->SetText("");
	m_pID_LISTIMG_Item1->Clear();
	m_pID_TEXT_ItemName1->SetText("");
	m_pID_LISTIMG_Item2->Clear();
	m_pID_TEXT_ItemName2->SetText("");
	m_pID_TEXT_Money->SetText("");
	m_pID_LISTIMG_Item3->Clear();
	m_pID_TEXT_ItemName3->SetText("");
	m_pID_LISTIMG_Item4->Clear();
	m_pID_TEXT_ItemName4->SetText("");
	m_pID_TEXT_GiftTip->SetText("");

	m_pID_BUTTON_GainTask->SetEnable( false );
	m_pID_BUTTON_Reward->SetEnable( false );
}

const char* CUI_ID_FRAME_SevenDays_Task::GetStatesText(int state)
{
	switch (state)
	{
	case 0:
		return theXmlString.GetString( eText_SevenDays_UnStart );
	case 1:
		return theXmlString.GetString( eText_SevenDays_CanGain );
	case 2:
		return theXmlString.GetString( eText_SevenDays_UnderWay );
	case 3:
		return theXmlString.GetString( eText_SevenDays_DoneUnGet );
	case 4:
		return theXmlString.GetString( eText_SevenDays_DoneGet );
	default:
		break;
	}
	
	return "";
}

void CUI_ID_FRAME_SevenDays_Task::SetListNameState()
{
	SevenDaysConfig::DataCommonVec vecCommon = theSevenDaysConfig.GetDataCommonVec();

	ControlList::S_List stList;

	for (int i = 0; i < SevenDaysConfig::TD_Max; i++)
	{
		short nstate = thePlayerRole.m_taskState[i];

		stList.SetData("");
		m_pID_LIST_Select->AddItem( &stList );

		stList.SetData( vecCommon[i].strName.c_str() );
		stList.setColor( Color_Config.getColor( nStatusColor[nstate] ) );
		stList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_Name->AddItem( &stList );

		stList.SetData( GetStatesText(nstate) );
		stList.setColor( Color_Config.getColor( nStatusColor[nstate] ) );
		stList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_State->AddItem( &stList );
	}

	if ( m_lastSelectIndex < 0 || m_lastSelectIndex >= m_pID_LIST_Select->GetListItemCnt() )
		m_lastSelectIndex = 0;

	m_pID_LIST_Select->SetCurSelIndex( m_lastSelectIndex );
	
}

void CUI_ID_FRAME_SevenDays_Task::Refresh()
{
	Init();
	SetListNameState();
	SetIntroduceData();
}

void CUI_ID_FRAME_SevenDays_Task::ShowItemName(ControlText* pText, int itemID)
{
	if ( !pText )
		return;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( itemID );
	if (!pItemCommon)
		return;

	char temp[128] = {0};
	sprintf(temp, "%s", pItemCommon->GetItemName());

	pText->SetText(temp);
}

void CUI_ID_FRAME_SevenDays_Task::SetIntroduceData()
{
	if ( m_lastSelectIndex < SevenDaysConfig::TD_FirstDay || m_lastSelectIndex > SevenDaysConfig::TD_SeventhDay )
		return;

	SevenDaysConfig::DataCommonVec dataVec = theSevenDaysConfig.GetDataCommonVec();
	SevenDaysConfig::DataCommon curData = dataVec[m_lastSelectIndex];

	m_pID_TEXT_Title->SetText( curData.strName1 );

	char buff[128] = {0};
	if ( thePlayerRole.m_taskState[m_lastSelectIndex] == 2 ) //进行中的任务
		sprintf_s( buff, sizeof(buff) - 1, "%s  %d/%d", curData.strCondition.c_str(), thePlayerRole.m_taskVar[m_lastSelectIndex], curData.nVarNum );
	else
		sprintf_s( buff, sizeof(buff) - 1, "%s", curData.strCondition.c_str() );

	m_pID_TEXT_Condition->SetText( buff );

	m_pID_TEXT_Tips->SetText( curData.strTips );

	ControlIconDrag::S_ListImg stListItem;
	for (int i = 0; i < SevenDaysConfig::TD_ItemMax; i++)
	{
		if ( curData.itemdata[i].nItemID > 0 && curData.itemdata[i].nItemCount > 0 )
		{
			stListItem.SetData( curData.itemdata[i].nItemID, curData.itemdata[i].nItemCount );
			ControlListImage* pItem = (ControlListImage*)m_ItemGroup.GetControl(i);
			if ( pItem )
				pItem->SetItem( &stListItem );

			ControlText* pText = (ControlText*)m_NameGroup.GetControl(i);
			if ( pText )
				ShowItemName( pText, curData.itemdata[i].nItemID );
		}
	}

	if ( curData.nMoneyType == (int)CPlayerRole::TYPE_JiaoZi )
	{
		std::string text;
		thePlayerRole.GetGSCStringFromJiaoZi(curData.nMoney, text);
		m_pID_TEXT_Money->SetText( text );
	}

	if ( curData.nMoneyType == (int)CPlayerRole::TYPE_JinPiao )
	{
		std::stringstream str;
		str <<curData.nMoney <<"{#1104}";
		m_pID_TEXT_Money->SetText( str.str() );
	}
	
	m_pID_TEXT_GiftTip->SetText( curData.strGift );

	if ( thePlayerRole.m_taskState[m_lastSelectIndex] == 1 ) //可接的任务
		m_pID_BUTTON_GainTask->SetEnable( true );
	if ( thePlayerRole.m_taskState[m_lastSelectIndex] == 3 ) //可领奖
		m_pID_BUTTON_Reward->SetEnable( true );
}