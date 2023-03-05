/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\liheng.duan\桌面\ExitTip.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ExitTip.h"
#include "ExitGame.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "ActivityList.h"
#include "PlayerRole.h"
#include "NpcCoord.h"
#include "UIMgr.h"
#include "MeTerrain/stdafx.h"
#include "ActivityDay.h"
#include "color_config.h"
#include "NetworkInput.h"
#include "ActivityList.h"
extern bool g_bCloseApp;

const char* gStarStr[] = {
	"{#SSSS0}",
	"{#SSSS1}",
	"{#SSSS2}",
	"{#SSSS3}",
	"{#SSSS4}"
};

struct ExitTipCallbackData : public UiCallbackDataBase
{
	ExitTipCallbackData(){}
	~ExitTipCallbackData(){}
	std::string mNpcName;

	virtual void* GetData()
	{
		if ( mNpcName.empty() )
		{
			return NULL;
		}

		return (void*)mNpcName.c_str();
	}

	virtual int GetType()
	{
		return eExipTip_UI_Callback;
	}
};

struct MoreData
{
	DWORD mCol;
	int mEvtIdx;
};

struct MoreCallbackData : public UiCallbackDataBase
{
	MoreCallbackData(){}
	~MoreCallbackData(){}
	MoreData mData;
	
	virtual void* GetData()
	{
		return (void*)&mData;
	}

	virtual int GetType()
	{
		return eMore_UI_Callback;
	}
};

const int MAX_LEVEL = 5;
const int MAX_LEVELOFFSET = 10;



CUI_ID_FRAME_ExitTip s_CUI_ID_FRAME_ExitTip;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ExitTip, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ExitTip, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitTip, ID_BUTTON_BackOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitTip, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitTip, ID_BUTTON_ExitOnButtonClick )

MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ExitTip, ID_LIST_FunctionLevelOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ExitTip, ID_LIST_StarOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ExitTip, ID_LIST_QuestOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ExitTip, ID_LIST_NewFunctionOnListSelectChange )
CUI_ID_FRAME_ExitTip::CUI_ID_FRAME_ExitTip()
{
	// Member
	m_pID_FRAME_ExitTip = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Exit = NULL;
	
	m_pID_LIST_Star = NULL;
	m_pID_LIST_Quest = NULL;

	//m_pID_LIST_NewFunction = NULL;
	//m_pID_LIST_FunctionLevel = NULL;
   m_bByOpenUi = false;
}
// Frame
bool CUI_ID_FRAME_ExitTip::OnFrameRun()
{

	if(CUI_ID_FRAME_ExitGame::ExitGameToServerIsReturned)
	{
		//开始计时1秒钟 1秒后强制结束客户端进程。
		static DWORD BeginTime = timeGetTime();
		       DWORD CurTime   = timeGetTime();
        if (CurTime - BeginTime >= 1500)
        {
			  CUI_ID_FRAME_ExitGame::ExitGameToServerIsReturned = false;
			  CUI_ID_FRAME_ExitGame::TellExitGame(true,NULL);
			  g_bCloseApp = true; //直接退出游戏
        }
	   return true;
	}

	if(!IsVisable())
		return false;

	// 让list同步滚动
	int nStartIndex = m_pID_LIST_Quest->GetShowStartHeight();
	m_pID_LIST_Star->SetShowStartHeight( nStartIndex );
	m_pID_LIST_More->SetShowStartHeight( nStartIndex );

	//nStartIndex = m_pID_LIST_NewFunction->GetShowStartHeight();
	//m_pID_LIST_FunctionLevel->SetShowStartHeight(nStartIndex);

	return true;
}

bool CUI_ID_FRAME_ExitTip::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_ExitTip::ID_BUTTON_BackOnButtonClick( ControlObject* pSender )
{
	SetVisable( false );
	return true;
}

// Button
bool CUI_ID_FRAME_ExitTip::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_ExitTip::ID_BUTTON_ExitOnButtonClick( ControlObject* pSender )
{
	if(m_bByOpenUi)
	{
		SetVisable( false );
		MsgSetOfflineHook msg;
		msg.bSetOfflineHook = true;
		GettheNetworkInput().SendMsg( &msg );
	}
	else
	{
		SetVisable( false );

		s_CUI_ID_FRAME_MessageBox.Show(
			theXmlString.GetString(eText_ExitGameCountDown),
			theXmlString.GetString(eText_ExitGameCountDown),
			CUI_ID_FRAME_MessageBox::eTypeCancel,
			true,
			CUI_ID_FRAME_ExitGame::/*TellExitGame*/TellExitGameToServer );
		s_CUI_ID_FRAME_MessageBox.SetAutoClose(6);
		s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(true);//.m_pID_BUTTON_Cancel->SetEnable(true);
		UiDrawer::StartFillFullScreen( 500, true ); // 屏幕变黑

	}
	return true;
}

// ListImg / ListEx


// List
void CUI_ID_FRAME_ExitTip::ID_LIST_FunctionLevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// List
void CUI_ID_FRAME_ExitTip::ID_LIST_QuestOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// List
void CUI_ID_FRAME_ExitTip::ID_LIST_StarOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// List
void CUI_ID_FRAME_ExitTip::ID_LIST_NewFunctionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

void CUI_ID_FRAME_ExitTip::SetChildList( ControlList* pLIST )
{
	pLIST->SetMsgHoldup(false);	//不接受消息
	pLIST->HaveSelBar( false );	//没有绿色cur选中地图
	pLIST->SetCurSelIndex(-1);
	pLIST->SetDrawFlags(DT_LEFT|DT_NOCLIP);
}

// 装载UI
bool CUI_ID_FRAME_ExitTip::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ExitTip.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ExitTip.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ExitTip::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ExitTip, s_CUI_ID_FRAME_ExitTipOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ExitTip, s_CUI_ID_FRAME_ExitTipOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ExitTip, ID_BUTTON_Back, s_CUI_ID_FRAME_ExitTipID_BUTTON_BackOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExitTip, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ExitTipID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExitTip, ID_BUTTON_Exit, s_CUI_ID_FRAME_ExitTipID_BUTTON_ExitOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_ExitTip, ID_LIST_FunctionLevel, s_CUI_ID_FRAME_ExitTipID_LIST_FunctionLevelOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ExitTip, ID_LIST_Star, s_CUI_ID_FRAME_ExitTipID_LIST_StarOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ExitTip, ID_LIST_Quest, s_CUI_ID_FRAME_ExitTipID_LIST_QuestOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_ExitTip, ID_LIST_NewFunction, s_CUI_ID_FRAME_ExitTipID_LIST_NewFunctionOnListSelectChange );

	m_pID_FRAME_ExitTip = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ExitTip );
	m_pID_BUTTON_Back = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExitTip, ID_BUTTON_Back );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExitTip, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Exit = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExitTip, ID_BUTTON_Exit );
	m_pID_LIST_Star = (ControlList*)theUiManager.FindControl( ID_FRAME_ExitTip, ID_LIST_Star );

	m_pID_LIST_Quest = (ControlList*)theUiManager.FindControl( ID_FRAME_ExitTip, ID_LIST_Quest );

	m_pID_LIST_More = (ControlList*)theUiManager.FindControl( ID_FRAME_ExitTip, ID_LIST_More );

	//m_pID_LIST_FunctionLevel = (ControlList*)theUiManager.FindControl( ID_FRAME_ExitTip, ID_LIST_FunctionLevel );
	//m_pID_LIST_NewFunction = (ControlList*)theUiManager.FindControl( ID_FRAME_ExitTip, ID_LIST_NewFunction );

	assert( m_pID_FRAME_ExitTip );
	assert( m_pID_BUTTON_Back );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Exit );
	assert( m_pID_LIST_Star );
	assert( m_pID_LIST_Quest );
	assert( m_pID_LIST_More );

	//assert( m_pID_LIST_NewFunction );
	//assert( m_pID_LIST_FunctionLevel );


	// 双击list自动寻路
	m_pID_LIST_Quest->SetLDBClickFun(ID_LIST_LDBClick);
	m_pID_LIST_Quest->HaveSelBar( false );

	m_pID_LIST_More->SetLBtnDownFun( ID_LISTMore_LBClick );

	//	模态		截获消息
//	m_pID_FRAME_ExitTip->SetMsgProcFun( Exit_MsgProc );
//	m_pID_FRAME_ExitTip->SetArrayMode( ArrayMode_Top );

	SetChildList( m_pID_LIST_Star );

	m_pID_LIST_More->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_More->SetDrawFlags(DT_LEFT|DT_NOCLIP);

	//SetChildList( m_pID_LIST_FunctionLevel );
	m_pID_LIST_Quest->setShowTip( true );

	return true;
}

bool CUI_ID_FRAME_ExitTip::Exit_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if( !s_CUI_ID_FRAME_ExitTip.IsVisable() )
		return false;

	switch( msg ) 
	{		
	case WM_KEYUP:
		{
			/*if( wParam == VK_ESCAPE )
			{
				s_CUI_ID_FRAME_ExitTip.ID_BUTTON_BackOnButtonClick( NULL );
				return true;
			}*/
			if( wParam == VK_RETURN )
			{
				s_CUI_ID_FRAME_ExitTip.ID_BUTTON_ExitOnButtonClick( NULL );
				return true;
			}
		}
		break;
	}
	return false;
}

void CUI_ID_FRAME_ExitTip::ID_LISTMore_LBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( pSender == s_CUI_ID_FRAME_ExitTip.m_pID_LIST_More )
	{
		int idx = s_CUI_ID_FRAME_ExitTip.m_pID_LIST_More->GetCurSelIndex();

		if ( idx == -1 )
		{
			return;
		}

		s_CUI_ID_FRAME_ExitTip.m_pID_LIST_Quest->SetCurSelIndex( idx );
		s_CUI_ID_FRAME_ExitTip.m_pID_LIST_Star->SetCurSelIndex( idx );

		SortEventContents data = GetTodayEvtContents();
		int maxCount = data.size();

		ControlList::S_List* stItem = s_CUI_ID_FRAME_ExitTip.m_pID_LIST_Quest->GetListItem( idx );

		if ( stItem->m_nID > -1 && stItem->m_nID < maxCount )
		{
			const Event& content = *data[stItem->m_nID];
			s_CUI_ID_FRAME_ActivityDay.ShowAndPitchByName( content.category, content.name.c_str() );
		}
	}
}

void CUI_ID_FRAME_ExitTip::ChangeCol( void* data, DWORD* col )
{
	*col = ( (MoreData*)data )->mCol;
}

void CUI_ID_FRAME_ExitTip::ClickMore( void* data )
{
	if ( data )
	{
		MoreData* pMoreData = (MoreData*)data;

		SortEventContents data = GetTodayEvtContents();
		int maxCount = data.size();

		if ( pMoreData->mEvtIdx > -1 && pMoreData->mEvtIdx < maxCount )
		{
			//const Event& content = *data[pMoreData->mEvtIdx];
			//int Type = content.category;//活动类型
			int Type = pMoreData->mEvtIdx;
			s_CUI_ID_FRAME_ActivityList.SetVisable(!s_CUI_ID_FRAME_ActivityList.IsVisable());
			s_CUI_ID_FRAME_ActivityList.ShowActionByType(Type);
		}
	}
}

void CUI_ID_FRAME_ExitTip::ID_LIST_LDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	
}

// 卸载UI
bool CUI_ID_FRAME_ExitTip::_UnLoadUI()
{
	m_pID_FRAME_ExitTip = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Exit = NULL;
	m_pID_LIST_Star = NULL;
	m_pID_LIST_Quest = NULL;
	m_pID_LIST_More = NULL;
    mAllNoteName.clear();
	//m_pID_LIST_FunctionLevel = NULL;
	//m_pID_LIST_NewFunction = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\ExitTip.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_ExitTip::_IsVisable()
{
	return m_pID_FRAME_ExitTip->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_ExitTip::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_ExitTip->SetVisable( bVisable );
	if(!bVisable)
		m_bByOpenUi = false;
}
bool CUI_ID_FRAME_ExitTip::SortByStar(Event* lhs, Event* rhs)
{
	return lhs->quality > rhs->quality;
}

void CUI_ID_FRAME_ExitTip::RefreshInfo()
{
	m_pID_LIST_Star->Clear();
	m_pID_LIST_Quest->Clear();
	m_pID_LIST_More->Clear();

	//m_pID_LIST_FunctionLevel->Clear();
	//m_pID_LIST_NewFunction->Clear();

	mAllNoteName.clear();

	SortEventContents data = GetTodayEvtContents();

	std::stable_sort(data.begin(),data.end(),SortByStar);

	int maxCount = data.size();

	for ( int idx = 0; idx < maxCount; ++idx )
	{
		if ( !IsPushTopList( *data[idx] ) )
		{
			continue;
		}
		
		if (data[idx]->country!=0 && data[idx]->country!=thePlayerRole.GetCountry())
		{
			continue;
		}

		// 设置名字
		ControlList::S_List	stItem;
		std::string temp;
		temp = "<";
		temp = temp + data[idx]->name.c_str();
		temp = temp + ">";

		char countStr[256] = {0};
		int count = thePlayerRole.GetVariableValue( data[idx]->completeTimeVarIndex );
		int maxCount = data[idx]->count;
		sprintf( countStr, "(%d/%d)", count,maxCount );
		temp = temp + countStr;

		// 设置超连接的回调函数
		std::vector<UiCallbackDataBase*> CallBackDataArr;
		ExitTipCallbackData* pNew = MeNew ExitTipCallbackData();
		pNew->mNpcName = data[idx]->npc;
		CallBackDataArr.push_back( pNew );


		// 设置Tips
		const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->/*getNpcCoordInPrimaryMap*/getNpcCoord(data[idx]->npcId);
		if (pNpcInfo)
		{
			CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
			if (pTile)
			{
				char cTip[256] = {0};
				sprintf(cTip,"%s(%d,%d)",pTile->GetTileName(),(int)pNpcInfo->_pfMapX,(int)pNpcInfo->_pfMapY);
				pNew->SetTip( cTip );
			}
		}

		// 插入数据
		stItem.SetData( temp.c_str() );
		stItem.m_nID = idx;
		m_pID_LIST_Quest->AddItem( &stItem, &CallBackDataArr, false );

		// 插入星级
		int level = data[idx]->quality;

		if ( level >= 1 && level <= MAX_LEVEL )
		{
			stItem.SetData( gStarStr[level - 1] );
			m_pID_LIST_Star->AddItem( &stItem, NULL, false);
		}
		else
		{
			// 防止策划填错了，加个空的在里面
			ControlList::S_List	temp;
			temp.SetData("");
			m_pID_LIST_Star->AddItem( &temp, NULL, false);
		}

		//InsertMoreList( idx );
		InsertMoreList( data[idx]->category );
	}
}

void CUI_ID_FRAME_ExitTip::InsertMoreList( int eventIdx )
{
	ControlList::S_List	stItem;

	// 设置超连接的回调函数
	std::vector<UiCallbackDataBase*> CallBackDataArr;
	MoreCallbackData* pNew = MeNew MoreCallbackData();
	pNew->mData.mEvtIdx = eventIdx;
	pNew->mData.mCol = Color_Config.getColor( CC_OrangeName );
	CallBackDataArr.push_back( pNew );

	// 插入策划要的文字
	std::string temp;
	temp = "[";
	temp += theXmlString.GetString( eExitTip_InfoMore );
	temp += "]";
	stItem.SetData( temp.c_str() );

	m_pID_LIST_More->AddItem( &stItem, &CallBackDataArr, false );
}

bool CUI_ID_FRAME_ExitTip::IsPushTopList( Event content )
{
	if ( thePlayerRole.GetVariableValue( content.completeTimeVarIndex ) < content.count 
		&& thePlayerRole.GetLevel() >= content.needLevel )
	{
		return true;
	}

	return false;
}

bool CUI_ID_FRAME_ExitTip::IsPushBottomList( Event content )
{
	int offsetLevel = content.needLevel - thePlayerRole.GetLevel();

	if ( offsetLevel < 1 || offsetLevel > MAX_LEVELOFFSET )
	{
		return false;
	}

	if ( mAllNoteName.count( content.name ) > 0 )
	{
		return false;
	}
	
	return true;
}

