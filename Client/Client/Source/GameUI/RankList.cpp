/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\RankList.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "RankList.h"
#include "script_manager.h"
#include "GameMain.h"
#include "client_tolua.h"
#include "SystemConfig.h"
#include "Cfg.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "Target.h"
#include "RbtnMenu.h"
#include "XmlStringLanguage.h"
#include "MessageBox.h"
#include "ChatInfoBox.h"
#include "color_config.h"
#include "Common.h"
#include "Ui/InfoList.h"
#include "CountryFunction.h"
#include "core/Name.h"
#include "json/reader.h"

extern int RetrieveFileFromInternet(CHAR* pHttpAddress,CHAR* pFileFullPath);

CUI_ID_FRAME_RankList s_CUI_ID_FRAME_RankList;
MAP_FRAME_RUN( s_CUI_ID_FRAME_RankList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_RankList, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankList, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankList, ID_BUTTON_HelpOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_RankList, ID_LIST_SubTypeListOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_RankList, ID_CHECKBOX_TypeOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankList, ID_BUTTON_LeftHeadOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankList, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankList, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankList, ID_BUTTON_RightHeadOnButtonClick )

CUI_ID_FRAME_RankList::CUI_ID_FRAME_RankList()
{
	// Member
	ResetMembers();
}
void CUI_ID_FRAME_RankList::ResetMembers()
{
	m_pID_FRAME_RankList = NULL;
	//m_pID_PICTURE_TitleDi = NULL;
	//m_pID_TEXT_Title = NULL;
	m_pID_PICTURE_TitleLeftMiddle = NULL;
	m_pID_PICTURE_TitleRightMiddle = NULL;
	m_pID_PICTURE_TitleLeft = NULL;
	m_pID_PICTURE_TitleRight = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Help = NULL;
	//m_pID_PICTURE_Wall = NULL;
	m_pID_CHECKBOX_Type0 = NULL;
	m_pID_CHECKBOX_Type1 = NULL;
	m_pID_CHECKBOX_Type2 = NULL;
	m_pID_CHECKBOX_Type3 = NULL;
	m_pID_CHECKBOX_Type4 = NULL;
	m_pID_CHECKBOX_Type5 = NULL;
	m_pID_PICTURE_TypeWall = NULL;
	m_pID_PICTURE_ExplainWall = NULL;
	m_pID_LIST_SubTypeList = NULL;
	m_pID_TEXT_TypeText = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_CHECKBOX_Type4 = NULL;
	m_pID_BUTTON_LeftHead = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_RightHead = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_TEXT_Information = NULL;
	m_nShowNumPerPage = 16;
	m_nCurrentPage = 1;
	m_nCurrentRow = 0;
}
// Frame
bool CUI_ID_FRAME_RankList::OnFrameRun()
{
	if( IsVisable() )
	{
		RelativeSet::iterator it, end = m_relativeSet.end();
		for (it = m_relativeSet.begin(); it != end; ++it)
		{
			int nStartIndex = it->first->GetShowStartHeight();
			for (int i = 0; i < it->second.size(); ++i)
				it->second[i]->SetShowStartHeight(nStartIndex);
			
			if (m_relativeImgSet.find(it->first) != m_relativeImgSet.end())
			{
				m_relativeImgSet[it->first]->SetShowStartHeight(nStartIndex);
			}
		}
	}
	return true;
}
bool CUI_ID_FRAME_RankList::OnFrameRender()
{
	if (m_bNeedUpdate)
	{
		m_pID_TEXT_Wait->SetVisable(false);
		m_pID_TEXT_Information->SetVisable(true);
		m_pID_TEXT_Explain->SetVisable(true);
		InterlockedExchange(&s_CUI_ID_FRAME_RankList.m_bNeedUpdate, 0);
		_ReadRankInfos();
	}
	return true;
}
// Button
bool CUI_ID_FRAME_RankList::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RankList )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_RankList::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RankList )
		return false;
	return true;
}
// List
void CUI_ID_FRAME_RankList::ID_LIST_SubTypeListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_RankList )
		return;
	try
	{
		m_nCurrentPage = 1;
		SetCurrentPageText();
		std::string subType;
		if (m_pID_LIST_SubTypeList->GetCurSelItem())
			subType = m_pID_LIST_SubTypeList->GetCurSelItem()->m_szText;

		RankInfoSet::iterator it = m_rankInfoSets.find(subType);
		if (it != m_rankInfoSets.end())
		{
			m_pCurrRankInfos = &(it->second);
		}
		
		LuaFunction<void> RefreshRankContentsFunc( ScriptManager::instance().getLuaStateOwner(m_luaFilename), "RefreshRankContents" );
		RefreshRankContentsFunc( /*m_pActivedCheckBox->GetData()->m_szID, */subType.c_str() );
	}
	catch ( const LuaPlus::LuaException& e )
	{
		Log( e.GetErrorMessage() );
	}
}
// CheckBox
void CUI_ID_FRAME_RankList::ID_CHECKBOX_TypeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_RankList )
		return;
	for (int i = 0; i < m_pageCheckBoxs.size(); ++i)
	{
		if (pSender == m_pageCheckBoxs[i])
		{
			m_pageCheckBoxs[i]->SetCheck(true);
			m_pActivedCheckBox = m_pageCheckBoxs[i];

			//// 设置排行榜描述
			//m_pID_TEXT_Explain->SetText(
			//	GetSystemConfig()->GetRankDescription(m_pActivedCheckBox->GetData()->m_szCaption).description);
		}
		else
			m_pageCheckBoxs[i]->SetCheck(false);
	}
	//设置默认选中第一行,显示该选中类型
	m_pID_LIST_SubTypeList->SetCurSelIndex(0);
	m_nCurrentRow = 0; 
	m_nCurrentPage = 1; //设置为第一页
	SetCurrentPageText();
	// 排序并刷新排行榜界面
	_SortAndRefreshRankInfos();
}

// 装载UI
bool CUI_ID_FRAME_RankList::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\RankList.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\RankList.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_RankList::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_RankList, s_CUI_ID_FRAME_RankListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_RankList, s_CUI_ID_FRAME_RankListOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_RankList, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_RankListID_BUTTON_CLOSEOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_RankList, ID_BUTTON_Help, s_CUI_ID_FRAME_RankListID_BUTTON_HelpOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_RankList, ID_LIST_SubTypeList, s_CUI_ID_FRAME_RankListID_LIST_SubTypeListOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_RankList, ID_BUTTON_LeftHead, s_CUI_ID_FRAME_RankListID_BUTTON_LeftHeadOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RankList, ID_BUTTON_Left, s_CUI_ID_FRAME_RankListID_BUTTON_LeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RankList, ID_BUTTON_Right, s_CUI_ID_FRAME_RankListID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RankList, ID_BUTTON_RightHead, s_CUI_ID_FRAME_RankListID_BUTTON_RightHeadOnButtonClick );

	m_pID_FRAME_RankList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_RankList );
	//m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_RankList, ID_PICTURE_TitleDi );
	//m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_RankList, ID_TEXT_Title );
	m_pID_PICTURE_TitleLeftMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_RankList, ID_PICTURE_TitleLeftMiddle );
	m_pID_PICTURE_TitleRightMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_RankList, ID_PICTURE_TitleRightMiddle );
	m_pID_PICTURE_TitleLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_RankList, ID_PICTURE_TitleLeft );
	m_pID_PICTURE_TitleRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_RankList, ID_PICTURE_TitleRight );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_RankList, ID_BUTTON_CLOSE );
	//m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_RankList, ID_BUTTON_Help );
	//m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_RankList, ID_PICTURE_Wall );
	m_pID_BUTTON_LeftHead = (ControlButton*)theUiManager.FindControl( ID_FRAME_RankList, ID_BUTTON_LeftHead );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_RankList, ID_BUTTON_Left );
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_RankList, ID_BUTTON_Right );
	m_pID_BUTTON_RightHead = (ControlButton*)theUiManager.FindControl( ID_FRAME_RankList, ID_BUTTON_RightHead );
	m_pID_CHECKBOX_Type0 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_RankList, ID_CHECKBOX_Type0 );
	m_pID_CHECKBOX_Type1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_RankList, ID_CHECKBOX_Type1 );
	m_pID_CHECKBOX_Type2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_RankList, ID_CHECKBOX_Type2 );
	m_pID_CHECKBOX_Type3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_RankList, ID_CHECKBOX_Type3 );
	m_pID_CHECKBOX_Type4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_RankList, ID_CHECKBOX_Type4 );
	m_pID_CHECKBOX_Type5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_RankList, ID_CHECKBOX_Type5 );
	m_pID_PICTURE_TypeWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_RankList, ID_PICTURE_TypeWall );
	m_pID_PICTURE_ExplainWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_RankList, ID_PICTURE_ExplainWall );
	m_pID_LIST_SubTypeList = (ControlList*)theUiManager.FindControl( ID_FRAME_RankList, ID_LIST_SubTypeList );
	m_pID_TEXT_TypeText = (ControlText*)theUiManager.FindControl( ID_FRAME_RankList, ID_TEXT_TypeText );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_RankList, ID_TEXT_Explain );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_RankList, ID_TEXT_Page );
	m_pID_TEXT_Information = (ControlText*)theUiManager.FindControl( ID_FRAME_RankList, ID_TEXT_Information);
	m_pID_CHECKBOX_Type4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_RankList, ID_CHECKBOX_Type4 );
	m_pID_TEXT_Wait = (ControlText*)theUiManager.FindControl( ID_FRAME_RankList, ID_TEXT_Wait );
	m_pID_TEXT_Wait->SetText(theXmlString.GetString(eText_WaitingServerUpdate));
	assert( m_pID_FRAME_RankList );
	//assert( m_pID_PICTURE_TitleDi );
	//assert( m_pID_TEXT_Title );
	/*assert( m_pID_PICTURE_TitleLeftMiddle );
	assert( m_pID_PICTURE_TitleRightMiddle );
	assert( m_pID_PICTURE_TitleLeft );
	assert( m_pID_PICTURE_TitleRight );*/
	assert( m_pID_BUTTON_CLOSE );
	//assert( m_pID_BUTTON_Help );
	//assert( m_pID_PICTURE_Wall );
	assert( m_pID_CHECKBOX_Type0 );
	assert( m_pID_CHECKBOX_Type1 );
	assert( m_pID_CHECKBOX_Type2 );
	assert( m_pID_CHECKBOX_Type3 );
	assert( m_pID_CHECKBOX_Type4 );
	assert( m_pID_CHECKBOX_Type5 );
	//assert( m_pID_PICTURE_TypeWall );
	//assert( m_pID_PICTURE_ExplainWall );
	assert( m_pID_LIST_SubTypeList );
	assert( m_pID_TEXT_Explain );
	assert(m_pID_TEXT_TypeText);
	assert( m_pID_CHECKBOX_Type4 );
	assert( m_pID_BUTTON_LeftHead );
	assert( m_pID_BUTTON_Left );
	assert( m_pID_BUTTON_Right );
	assert( m_pID_BUTTON_RightHead );
	assert( m_pID_TEXT_Page);
	assert( m_pID_TEXT_Information);

	m_rankSortInfos.clear();
	m_rankInfoSets.clear();
	m_allRankInfos.clear();
	m_allBackgroupRankInfos.clear();
	m_pageCheckBoxs.clear();
	m_relativeSet.clear();
	m_relativeImgSet.clear();
	m_pCurrRankInfos = NULL;
	m_pActivedFrame = m_pID_FRAME_RankList;
	m_pActivedCheckBox = NULL;
	m_bNeedUpdate = 0;
	m_hThread = 0;
	m_loadTime = -1;

	char filename[MAX_PATH] = {0};
	//MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/Data/Config/Rank.config", GetRootPath());
	MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/Data/script/RankFunction.string", GetRootPath());
	m_luaFilename = filename;

	char buf[64];
	int index = 0;
	sprintf(buf, "ID_CHECKBOX_Type%d", index);
	ControlCheckBox* pCheckBox = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_RankList, buf );
	while (pCheckBox)
	{
		theUiManager.OnCheckBoxCheck( ID_FRAME_RankList, buf, s_CUI_ID_FRAME_RankListID_CHECKBOX_TypeOnCheckBoxCheck );
		m_pageCheckBoxs.push_back(pCheckBox);

		++index;
		sprintf(buf, "ID_CHECKBOX_Type%d", index);
		pCheckBox = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_RankList, buf );
	}

	if (!m_pageCheckBoxs.empty())
		m_pActivedCheckBox = m_pageCheckBoxs[0];

	try
	{
		LuaStateOwner& luaStateOwner = ScriptManager::instance().getLuaStateOwner(s_CUI_ID_FRAME_RankList.m_luaFilename);
		tolua_compile_open( luaStateOwner.Get()->GetCState() );

		ScriptManager::instance().executeFile( s_CUI_ID_FRAME_RankList.m_luaFilename );

		LuaFunction<void> InitializeFunc( ScriptManager::instance().getLuaStateOwner(s_CUI_ID_FRAME_RankList.m_luaFilename),
			"Initialize" );
		InitializeFunc();

		for (int i = 0; i < m_pageCheckBoxs.size(); ++i)
		{
			if (i == 0)
			{
				bool check = true;
				m_pageCheckBoxs[i]->SetCheck(true);
				m_pActivedCheckBox = m_pageCheckBoxs[i];

				// 设置排行榜描述
				m_pID_TEXT_Explain->SetText(
					GetSystemConfig()->GetRankDescription(m_pActivedCheckBox->GetData()->m_szCaption).description);
				
				// 刷新排行榜界面
				_RefreshRankInfos();
			}
			else
				m_pageCheckBoxs[i]->SetCheck(false);
		}
	}
	catch ( const LuaPlus::LuaException& e )
	{
		Log(e.GetErrorMessage(), LOG_PRIORITY_ERROR);
	}

	SetVisable(false);
	
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_RankList::_UnLoadUI()
{
	if (m_hThread)
	{
		TerminateThread( m_hThread, 0 );
		CloseHandle( m_hThread );
		m_hThread = 0;
	}

	try
	{
        if (m_luaFilename != "")
        {
            LuaFunction<void> ShutdownFunc( ScriptManager::instance().getLuaStateOwner(s_CUI_ID_FRAME_RankList.m_luaFilename),
                "Shutdown" );
            ShutdownFunc();

            m_luaFilename = "";
        }
	}
	catch ( const LuaPlus::LuaException& e )
	{
		Log(e.GetErrorMessage(), LOG_PRIORITY_ERROR);
	}

	m_rankSortInfos.clear();
	m_rankInfoSets.clear();
	m_allRankInfos.clear();
	m_allBackgroupRankInfos.clear();
	m_pageCheckBoxs.clear();
	m_relativeSet.clear();

	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\RankList.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_RankList::_IsVisable()
{
	if( !m_pID_FRAME_RankList )
		return false;
	return m_pID_FRAME_RankList->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_RankList::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_RankList )
		return;
	if( thePlayerRole.GetLevel() < 15 && bVisable )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RankList, theXmlString.GetString(eText_UnderLevel15RankList) );
		return;
	}
	m_pID_FRAME_RankList->SetVisable( bVisable );
	if (bVisable)
	{
		m_pID_TEXT_Wait->SetVisable(false);

		// 激活当前排行榜
		try
		{
			ScriptManager::instance().executeFile( s_CUI_ID_FRAME_RankList.m_luaFilename );

			LuaFunction<void> RefreshRankTypeFunc( ScriptManager::instance().getLuaStateOwner(m_luaFilename), "RefreshRankType" );
			RefreshRankTypeFunc( m_pActivedCheckBox->GetData()->m_szID );
		}
		catch ( const LuaPlus::LuaException& e )
		{
			Log( e.GetErrorMessage() );
		}

		// 时间相差一天就重新下载Rank.config，并更新界面内容
		time_t ltime;
		time(&ltime);

		//m_loadTime = 1355127940;
		///////////////////////////////////////////////////////////////////////////////////
		////////////////////////////测试代码//////////////////////////////////////////////
		//std::string filename = "UserData\\Rank.config";
		//MeXmlDocument	doc;
		//try
		//{
		//	if( !doc.LoadFile(filename.c_str()) )
		//	{
		//		assert(false && "读取UserData\\Rank.config文件失败");
		//		return ;
		//	}
		//}
		//catch(...)
		//{
		//	return ;
		//}
		//MeXmlElement* pProject = doc.FirstChildElement("Project");
		//if (!pProject)
		//{
		//	return ;
		//}
		//MeXmlElement* pTime = pProject->FirstChildElement("Ranks");
		//if (pTime)
		//{
		//	double time = 0;
		//	pTime->QueryDoubleAttribute("LastUpdateTime", &time);
		//	s_CUI_ID_FRAME_RankList.m_loadTime = time;
		//}

		//MeXmlElement* pType = pProject->FirstChildElement("Ranks")->FirstChildElement("Type");
		//for( ; pType; pType = pType->NextSiblingElement() )
		//{
		//	const char* szType = pType->Attribute("Name");
		//	if (szType)
		//	{
		//		MeXmlElement* pRank = pType->FirstChildElement("Rank");
		//		for ( ; pRank; pRank = pRank->NextSiblingElement() )
		//		{
		//			RankInfo rankInfo;
		//			//rankInfo.type = _tstring::toNarrowString(_tstring::UTF8towcs(szType).c_str());
		//			rankInfo.type = szType;

		//			const MeXmlAttribute* pAttribute = pRank->first_attribute();
		//			for ( ; pAttribute; pAttribute = pAttribute->next_attribute())
		//			{
		//				rankInfo.values[pAttribute->name()] = _tstring::toNarrowString(
		//					_tstring::UTF8towcs(pAttribute->value()).c_str());
		//			}

		//			s_CUI_ID_FRAME_RankList.m_allBackgroupRankInfos.push_back(rankInfo);
		//		}
		//	}
		//}
		//m_allRankInfos = m_allBackgroupRankInfos;
		//InterlockedExchange(&s_CUI_ID_FRAME_RankList.m_bNeedUpdate, 1);
		///////////////////////////////////////////////////////////////////////////////////
		double elapsedTime = difftime(ltime, m_loadTime);
		if (elapsedTime >= 60 * 60 * 24 || m_allRankInfos.empty())
		{
			m_loadTime = ltime;

			if (m_hThread)
			{
				TerminateThread( m_hThread, 0 );
				CloseHandle( m_hThread );
				m_hThread = 0;
			}

			m_pID_TEXT_Wait->SetVisable(true);
			m_hThread = CreateThread( NULL, 0, _BackgroupLoadRank, 0, 0, NULL );
		}
	}

	SetCurrentPageText();
}

//-----------------------------------------------------------------------
void CUI_ID_FRAME_RankList::Log(const std::string& log)
{
	Log(log, LOG_PRIORITY_INFO);
}

void CUI_ID_FRAME_RankList::Log(const std::string& log, int priority)
{
	LOG_MESSAGE( ERROR_INFO_LOG, priority, "");
	LOG_MESSAGE( ERROR_INFO_LOG, priority, "Lua Filename: " + m_luaFilename);
//	LOG_MESSAGE( ERROR_INFO_LOG, priority, log);
	LOG_MESSAGE( ERROR_INFO_LOG, priority, "");
	OutputDebugString( ( log + "\n" ).c_str() );
}

bool CUI_ID_FRAME_RankList::_RankSortFunc(const RankInfo* v1, const RankInfo* v2)
{
	try
	{
		RankInfo::ValueSet& values1 = const_cast<RankInfo::ValueSet&>(v1->values);
		RankInfo::ValueSet& values2 = const_cast<RankInfo::ValueSet&>(v2->values);

		RankSortFuncInfo& sortInfo = s_CUI_ID_FRAME_RankList.m_currPageSortFuncInfos[
			s_CUI_ID_FRAME_RankList.m_pActivedFrame->GetData()->m_szID];

		LuaFunction<bool> SortFunc( ScriptManager::instance().getLuaStateOwner(s_CUI_ID_FRAME_RankList.m_luaFilename),
			sortInfo.luaFunc.c_str() );
		if (!sortInfo.isUpperSort)
		{
			return SortFunc(
				values1[sortInfo.key].c_str(),
				values2[sortInfo.key].c_str());
		}
		return SortFunc(
			values2[sortInfo.key].c_str(),
			values1[sortInfo.key].c_str());
	}
	catch ( const LuaPlus::LuaException& e )
	{
		s_CUI_ID_FRAME_RankList.Log(e.GetErrorMessage(), LOG_PRIORITY_ERROR);
	}

	return false;
}

void CUI_ID_FRAME_RankList::_SortRank()
{
	if (m_pCurrRankInfos)
	{
		std::sort(m_pCurrRankInfos->begin(), m_pCurrRankInfos->end(), _RankSortFunc);

		try
		{
			ScriptManager::instance().executeFile( s_CUI_ID_FRAME_RankList.m_luaFilename );

			// 通过lua刷新排行榜内容
			std::string strType;
			if (m_pID_LIST_SubTypeList->GetCurSelItem())
				strType = m_pID_LIST_SubTypeList->GetCurSelItem()->m_szText;

			LuaFunction<void> RefreshRankContentsFunc( ScriptManager::instance().getLuaStateOwner(m_luaFilename), "RefreshRankContents" );
			RefreshRankContentsFunc( /*m_pActivedCheckBox->GetData()->m_szID, */strType.c_str() );
		}
		catch ( const LuaPlus::LuaException& e )
		{
			Log( e.GetErrorMessage() );
		}
	}
}

bool CUI_ID_FRAME_RankList::ID_BUTTON_SortOnButtonClick( ControlObject* pSender )
{
	if( !s_CUI_ID_FRAME_RankList.GetFrame() )
		return false;
	RankSortFuncInfo& info = s_CUI_ID_FRAME_RankList.m_rankSortInfos[pSender->GetFather()->GetData()->m_szID][pSender->GetData()->m_szID];
	info.isUpperSort = !info.isUpperSort;

	s_CUI_ID_FRAME_RankList.m_currPageSortFuncInfos[
		s_CUI_ID_FRAME_RankList.m_pActivedFrame->GetData()->m_szID] = info;

	RankSortInfoSet::iterator it, end = s_CUI_ID_FRAME_RankList.m_rankSortInfos.end();
	for (it = s_CUI_ID_FRAME_RankList.m_rankSortInfos.begin(); it != end; ++it)
	{
		std::map<std::string, RankSortFuncInfo>::iterator itInfo, itInfoEnd = it->second.end();
		for (itInfo = it->second.begin(); itInfo != itInfoEnd; ++itInfo)
		{
			if (itInfo->second.button == pSender)
			{
				itInfo->second.arrow->SetVisable(true);
				if (itInfo->second.isUpperSort)
					itInfo->second.arrow->SetText("{#204}");
				else
					itInfo->second.arrow->SetText("{#203}");
			}
			else
				itInfo->second.arrow->SetVisable(false);
		}
	}
	
	s_CUI_ID_FRAME_RankList._SortRank();
	return true;
}

//bool CUI_ID_FRAME_RankList::LoadRank(const std::string& filename)
//{	
//	using namespace Common;
//
//	RetrieveFileFromInternet("http://121.52.213.218:50004/web/rank.config", const_cast<char*>(filename.c_str()));
//
//	MeXmlDocument	doc;
//	if( !doc.LoadFile(filename.c_str()) )
//	{
//		assert(false && "读取Rank.config文件失败");
//		return false;
//	}
//
//// 	MeXmlHandle hDoc(&doc);
//
//	MeXmlElement* pType = doc.FirstChildElement("Project")->FirstChildElement("Ranks")->FirstChildElement("Type");
//	for( ; pType; pType = pType->NextSiblingElement() )
//	{
//		const char* szType = pType->Attribute("Name");
//		if (szType)
//		{
//			MeXmlElement* pRank = pType->FirstChildElement("Rank");
//			for ( ; pRank; pRank = pRank->NextSiblingElement() )
//			{
//				RankInfo rankInfo;
//				rankInfo.type = _tstring::toNarrowString(
//					_tstring::UTF8towcs(szType).c_str());
//
//				const MeXmlAttribute* pAttribute = pRank->first_attribute();
//				for ( ; pAttribute; pAttribute = pAttribute->next_attribute())
//				{
//					rankInfo.values[pAttribute->name()] = _tstring::toNarrowString(
//						_tstring::UTF8towcs(pAttribute->value()).c_str());
//				}
//
//				m_allRankInfos.push_back(rankInfo);
//				m_rankInfoSets[rankInfo.type].push_back(&m_allRankInfos.back());
//			}
//		}
//	}
//
//	return true;
//}

void CUI_ID_FRAME_RankList::LoadFrame(const std::string& filename, const char* frameName)
{
	theUiManager.AddFrame( filename.c_str() );
	ControlObject* pObj = theUiManager.FindFrame( frameName );
	if (pObj)
	{
		pObj->SetMsgHoldup(false);
		pObj->SetFather(m_pID_FRAME_RankList);
	}
}

void CUI_ID_FRAME_RankList::UnLoadFrame(const std::string &filename)
{
	m_pID_FRAME_RankList = NULL;
	theUiManager.RemoveFrame( filename.c_str() );
}

void CUI_ID_FRAME_RankList::SetFrameVisible(const char* frameName, bool visible)
{
	ControlFrame* pObj = (ControlFrame*)theUiManager.FindFrame( frameName );
	if (pObj)
	{
		pObj->SetVisable(visible);

		if (visible)
			m_pActivedFrame = pObj;
	}
}

void CUI_ID_FRAME_RankList::SetRankSortFunc(const char* frameName, const char* relativeControlId, const char* relativeArrowControlId, const char* luaFunc, const char* key)
{
	m_rankSortInfos[frameName][relativeControlId].luaFunc = luaFunc;
	m_rankSortInfos[frameName][relativeControlId].key = key;
	m_rankSortInfos[frameName][relativeControlId].arrow = (ControlText*)theUiManager.FindControl(frameName, relativeArrowControlId);
	m_rankSortInfos[frameName][relativeControlId].button = (ControlButton*)theUiManager.FindControl(frameName, relativeControlId);
	theUiManager.OnButtonClick( frameName, relativeControlId, ID_BUTTON_SortOnButtonClick );
}

void CUI_ID_FRAME_RankList::SetControlCheckBoxText(const char* frameName, const char* controlId, const char* text)
{
	ControlCheckBox* pCheckBox = (ControlCheckBox*)theUiManager.FindControl(frameName, controlId);
	if (pCheckBox)
		pCheckBox->SetCaption(text);
}

void CUI_ID_FRAME_RankList::SetControlText(const char* frameName, const char* controlId, const char* text)
{
	ControlText* pText = (ControlText*)theUiManager.FindControl(frameName, controlId);
	if (pText)
		pText->SetText(text);
}

void CUI_ID_FRAME_RankList::SetControlButtonText(const char* frameName, const char* controlId, const char* text)
{
	ControlButton* pBtn = (ControlButton*)theUiManager.FindControl(frameName, controlId);
	if (pBtn)
		pBtn->SetCaption(text);
}

void CUI_ID_FRAME_RankList::AddListItem(const char* frameName, const char* controlId, const char* text, unsigned int color, const char* data, bool bMiddleModle)
{
	ControlList* pList = (ControlList*)theUiManager.FindControl(frameName, controlId);
	if (pList)
	{
		ControlList::S_List	stItem;
		stItem.SetData(text, 0, 0, color, const_cast<char*>(data));
		if (bMiddleModle)
		{
			stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		}
		pList->AddItem( &stItem,NULL, false);
	}
}

void CUI_ID_FRAME_RankList::AddListImageItem(const char* frameName, const char* controlId, const char* text, unsigned int color, const char* data/*, int nRow, int nCol*/)
{
	ControlListImage* pListImage = (ControlListImage*)theUiManager.FindControl(frameName, controlId);
	if (!pListImage)
	{
		return;
	}

	ControlIconDrag::S_ListImg stImgItem;
	int nRowItemCount = pListImage->GetRowItemCnt();
	int nItemId = atoi(text);
	stImgItem.SetData(nItemId, 1);
	pListImage->SetMsgHoldup(false);
	pListImage->SetItem(&stImgItem, (m_nCurrentRow++) * nRowItemCount/* + nCol*/);
}
 
void CUI_ID_FRAME_RankList::AddListImageCharItem(const char* frameName, const char* controlId, const char* text, unsigned int color, const char* data/*, int nRow, int nCol*/)
{
	ControlListImage* pListImage = (ControlListImage*)theUiManager.FindControl(frameName, controlId);
	if (!pListImage||!data)
	{
		return;
	}
	Json::Reader reader;
	Json::Value root;
	bool ret = reader.parse(data, root);
	if (ret)
	{		
		const Json::Value& itemid    =root["id"];
		const Json::Value& baserands    =root["baserands"];
		const Json::Value& gemhole    =root["gemhole"];
		const Json::Value& gemids    =root["gemids"];
		const Json::Value& level    =root["level"];
		const Json::Value& purplerands    =root["purplerands"];
		const Json::Value& quality    =root["quality"];
		const Json::Value& score    =root["score"];
		const Json::Value& suitrands    =root["suitrands"];
		const Json::Value& soulper    =root["soulper"];
		Json::Value tempValue;

		ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(itemid.asInt());
		if (!pItemCanEquip)
		{
			return;
		}

		SCharItem itemtemp;
		itemtemp.itembaseinfo.ustItemID = itemid.asInt();
		itemtemp.itembaseinfo.ustItemCount = 1;
		itemtemp.equipdata.usHP = pItemCanEquip->stHPMax;
		for(int n =0;n < SCharItem::EConstDefine_BaseRandMaxCount;n++)// 基本附加随机属性
		{
			tempValue = baserands[n];
			itemtemp.equipdata.baseRands[n] = tempValue.asUInt();
		}
		for(int n =0;n < SCharItem::EConstDefine_PurpleRandMaxCount;n++)// 紫色附加随机属性
		{
			tempValue = purplerands[n];
			itemtemp.equipdata.purpleRands[n] = tempValue.asUInt();
		}
		for(int n =0;n < SCharItem::EConstDefine_SuitRandMaxCount;n++)// 技能套装附加随机属性
		{
			tempValue = suitrands[n];
			itemtemp.equipdata.suitRands[n] = tempValue.asUInt();
		}
		for(int n =0;n < SCharItem::EConstDefine_GemHoleMaxCount;n++)// 嵌套宝石
		{
			tempValue = gemids[n];
			itemtemp.equipdata.gemIds[n] = tempValue.asUInt();
		}
		itemtemp.equipdata.gemHoleCount = gemhole.asInt();
		itemtemp.equipdata.ucLevel = level.asInt();
		itemtemp.equipdata.quality = quality.asInt();
		itemtemp.equipdata.fScore = score.asDouble();
		itemtemp.equipdata.ucSoulPer = soulper.asInt();

		if (itemtemp.equipdata.ucSoulPer > 0)
		{
			itemtemp.SetSoulStamp(true);
		}

		ControlIconDrag::S_ListImg stImgItem;
		int nRowItemCount = pListImage->GetRowItemCnt();
		stImgItem.SetData(&itemtemp);
		pListImage->SetMsgHoldup(false);
		pListImage->SetItem(&stImgItem, (m_nCurrentRow++) * nRowItemCount/* + nCol*/);
	}	
}


void CUI_ID_FRAME_RankList::ClearList(const char* frameName, const char* controlId)
{
	ControlList* pList = (ControlList*)theUiManager.FindControl(frameName, controlId);
	if (pList)
		pList->Clear();
}

void CUI_ID_FRAME_RankList::ClearListImage(const char* frameName, const char* controlId)
{
	ControlListImage* pListImage = (ControlListImage*)theUiManager.FindControl(frameName, controlId);
	if (!pListImage)
		return;
	pListImage->Clear();
	m_nCurrentRow = 0;
}

void CUI_ID_FRAME_RankList::AssociateListImg(const char* frameName, const char* fatherControlId, const char* controlId, int drawFormat)
{
	ControlList* pFatherList = (ControlList*)theUiManager.FindControl(frameName, fatherControlId);
	ControlListImage* pListImg = (ControlListImage*)theUiManager.FindControl(frameName, controlId);
	if (pFatherList && pListImg)
	{
		m_relativeImgSet[pFatherList] = pListImg;
	}
}

void CUI_ID_FRAME_RankList::AssociateList(const char* frameName, const char* fatherControlId, const char* childControlId, int drawFormat)
{
	ControlList* pFatherList = (ControlList*)theUiManager.FindControl(frameName, fatherControlId);
	ControlList* pChildList = (ControlList*)theUiManager.FindControl(frameName, childControlId);
	if (pFatherList && pChildList)
	{
		pFatherList->SetRBClickFun(ListRBClick);

		pChildList->SetMsgHoldup(false);	//不接受消息
		pChildList->SetItemMaxCount( 100 );
		pChildList->HaveSelBar( false );	//没有绿色cur选中地图
		pChildList->SetCurSelIndex(-1);
		pChildList->SetDrawFlags(drawFormat|DT_NOCLIP);

		m_relativeSet[pFatherList].push_back(pChildList);
	}
}

int CUI_ID_FRAME_RankList::GetRankRowSize(const char* type)
{
	RankInfoSet::iterator it = m_rankInfoSets.find(type);
	if (it != m_rankInfoSets.end())
		return it->second.size();
	return 0;
}

const char* CUI_ID_FRAME_RankList::GetRankContent(const char *type, int row, const char *column)
{
	RankInfoSet::iterator it = m_rankInfoSets.find(type);
	if (it != m_rankInfoSets.end() && it->second.size() > row)
	{
		return it->second[row]->values[column].c_str();
	}
	return "";
}

void CUI_ID_FRAME_RankList::_RefreshRankInfos()
{
	try
	{
		ScriptManager::instance().executeFile( s_CUI_ID_FRAME_RankList.m_luaFilename );

		// 通过lua设置子窗口类型，和排序规则
		LuaFunction<void> RefreshRankTypeFunc( ScriptManager::instance().getLuaStateOwner(m_luaFilename), "RefreshRankType" );
		RefreshRankTypeFunc( m_pActivedCheckBox->GetData()->m_szID );
		
		// 通过lua刷新排行榜内容
		std::string filterType;
		if (m_pID_LIST_SubTypeList->GetCurSelItem())
			filterType = m_pID_LIST_SubTypeList->GetCurSelItem()->m_szText;

		LuaFunction<void> RefreshRankContentsFunc( ScriptManager::instance().getLuaStateOwner(m_luaFilename), "RefreshRankContents" );
		RefreshRankContentsFunc( /*m_pActivedCheckBox->GetData()->m_szID, */filterType.c_str() );
	}
	catch ( const LuaPlus::LuaException& e )
	{
		Log( e.GetErrorMessage() );
	}
}

DWORD WINAPI CUI_ID_FRAME_RankList::_BackgroupLoadRank(LPVOID lpParam)
{
	using namespace Common;

	InterlockedExchange(&s_CUI_ID_FRAME_RankList.m_bNeedUpdate, 0);

	s_CUI_ID_FRAME_RankList.m_allBackgroupRankInfos.clear();

	std::string filename = "UserData\\Rank.config";

	char webPath[MAX_PATH];
	//根据需求获得下载地址
	//这里的m_strHttp地址从serverlist.config里读取
	sprintf(webPath, "%s", gCfg.m_strHttp.c_str());

	//这里的m_strRanklistWebPath地址从gamesetting.config里读取
	//sprintf(webPath, "%s", gCfg.m_strRanklistWebPath.c_str());

	// 下载Rank.config文件
	RetrieveFileFromInternet(webPath, const_cast<char*>(filename.c_str()));
	/*RetrieveFileFromInternet("http://121.52.213.218:50004/web/rank.config", const_cast<char*>(filename.c_str()));*/

	// 读取Rank.config数据到临时m_allBackgroupRankInfos队列中
	MeXmlDocument	doc;
	try
	{
		if( !doc.LoadFile(filename.c_str()) )
		{
			assert(false && "读取UserData\\Rank.config文件失败");
			return false;
		}
	}
	catch(...)
	{
		return false;
	}

	//if( !doc.LoadFile(filename.c_str()) )
	//{
	//	assert(false && "读取UserData\\Rank.config文件失败");
	//	return false;
	//}

// 	MeXmlHandle hDoc(&doc);
	MeXmlElement* pProject = doc.FirstChildElement("Project");
	if (!pProject)
	{
		return false;
	}
	MeXmlElement* pTime = pProject->FirstChildElement("Ranks");
	if (pTime)
	{
		double time = 0;
		pTime->QueryDoubleAttribute("LastUpdateTime", &time);
		s_CUI_ID_FRAME_RankList.m_loadTime = time;
	}

	MeXmlElement* pType = pProject->FirstChildElement("Ranks")->FirstChildElement("Type");
	for( ; pType; pType = pType->NextSiblingElement() )
	{
		const char* szType = pType->Attribute("Name");
		if (szType)
		{
			MeXmlElement* pRank = pType->FirstChildElement("Rank");
			for ( ; pRank; pRank = pRank->NextSiblingElement() )
			{
				RankInfo rankInfo;
				rankInfo.type = _tstring::toNarrowString(
					_tstring::UTF8towcs(szType).c_str());

				const MeXmlAttribute* pAttribute = pRank->first_attribute();
				for ( ; pAttribute; pAttribute = pAttribute->next_attribute())
				{
					rankInfo.values[pAttribute->name()] = _tstring::toNarrowString(
						_tstring::UTF8towcs(pAttribute->value()).c_str());
				}

				s_CUI_ID_FRAME_RankList.m_allBackgroupRankInfos.push_back(rankInfo);
			}
		}
	}

	InterlockedExchange(&s_CUI_ID_FRAME_RankList.m_bNeedUpdate, 1);

	return 0;
}

void CUI_ID_FRAME_RankList::SetSort()
{
	// 设置当前排行榜队列指针，用于排序
	RankInfoSet::iterator it = m_rankInfoSets.find(m_pActivedCheckBox->GetData()->m_szCaption);
	if (it != m_rankInfoSets.end())
	{
		m_pCurrRankInfos = &(it->second);
	}
	else
		m_pCurrRankInfos = 0;

	// 设置排序方法为当前激活的排行榜窗口的第一列排序方法
	if (m_rankSortInfos[m_pActivedFrame->GetData()->m_szID].size() > 0)
	{
		m_currPageSortFuncInfos[m_pActivedFrame->GetData()->m_szID] =
			m_rankSortInfos[m_pActivedFrame->GetData()->m_szID].begin()->second;
	}

	// 设置排序箭头
	RankSortFuncInfo& sortInfo = m_currPageSortFuncInfos[m_pActivedFrame->GetData()->m_szID];

	RankSortInfoSet::iterator itSort, endSort = s_CUI_ID_FRAME_RankList.m_rankSortInfos.end();
	for (itSort = s_CUI_ID_FRAME_RankList.m_rankSortInfos.begin(); itSort != endSort; ++itSort)
	{
		std::map<std::string, RankSortFuncInfo>::iterator itInfo;
		for (itInfo = itSort->second.begin(); itInfo != itSort->second.end(); ++itInfo)
		{
			if (itInfo->second.button == sortInfo.button)
			{
				itInfo->second.arrow->SetVisable(true);
				if (itInfo->second.isUpperSort)
					itInfo->second.arrow->SetText("{#204}");
				else
					itInfo->second.arrow->SetText("{#203}");
			}
			else
				itInfo->second.arrow->SetVisable(false);
		}
	}

	// 排序
	if (m_pCurrRankInfos)
	{
		std::sort(m_pCurrRankInfos->begin(), m_pCurrRankInfos->end(), _RankSortFunc);
	}
}

void CUI_ID_FRAME_RankList::_SortAndRefreshRankInfos()
{
	// 激活当前排行榜
	try
	{
		ScriptManager::instance().executeFile( s_CUI_ID_FRAME_RankList.m_luaFilename );

		LuaFunction<void> RefreshRankTypeFunc( ScriptManager::instance().getLuaStateOwner(m_luaFilename), "RefreshRankType" );
		RefreshRankTypeFunc( m_pActivedCheckBox->GetData()->m_szID );
	}
	catch ( const LuaPlus::LuaException& e )
	{
		Log( e.GetErrorMessage() );
	}

	SetSort();
	m_pID_LIST_SubTypeList->SetCurSelIndex(0);
	try
	{
		std::string strType;
		if (m_pID_LIST_SubTypeList->GetCurSelItem())
		{
			strType = m_pID_LIST_SubTypeList->GetCurSelItem()->m_szText;
			m_pCurrRankInfos = &m_rankInfoSets[strType];
		}
		
		LuaFunction<void> RefreshRankContentsFunc( ScriptManager::instance().getLuaStateOwner(m_luaFilename), "RefreshRankContents" );
		RefreshRankContentsFunc( /*m_pActivedCheckBox->GetData()->m_szID, */strType.c_str() );
	}
	catch ( const LuaPlus::LuaException& e )
	{
		Log( e.GetErrorMessage() );
	}
}

void CUI_ID_FRAME_RankList::_ReadRankInfos()
{
	m_pCurrRankInfos = 0;
	m_allRankInfos = m_allBackgroupRankInfos;
	m_allBackgroupRankInfos.clear();
	m_rankInfoSets.clear();

	// 填充所有排行榜数据
	RankInfoList::iterator it, end = m_allRankInfos.end();
	for (it = m_allRankInfos.begin(); it != end; ++it)
	{
		m_rankInfoSets[it->type].push_back(&(*it));
	}

	// 排序并刷新排行榜界面
	_SortAndRefreshRankInfos();
}

const char* CUI_ID_FRAME_RankList::GetProfessionName(int type)
{
	CProfessionInfo* info = GetSystemConfig()->GetProessionInfoFromID(type);
	if (info)
		return info->m_strProShow.c_str();
	return "";
}

const char* CUI_ID_FRAME_RankList::GetMeName()
{
	return thePlayerRole.GetName();
}

const char* CUI_ID_FRAME_RankList::GetGuildName()
{
	return thePlayerRole.GetGangMgr()->GetGuildName();
}

void CUI_ID_FRAME_RankList::ListRBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	if (std::string("") == pItem->m_szNote)
		return;

	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByName( pItem->m_szNote );
	if (pPlayer)
		s_CUI_ID_FRAME_Target.SetPlayer(pPlayer->GetID());

	int x,y;
	x = theUiManager.m_ptMoust.x;
	y = theUiManager.m_ptMoust.y;
	s_CUI_ID_FRAME_RBTNMENU.SetPrivateName( pItem->m_szNote );
	s_CUI_ID_FRAME_RBTNMENU.SetVisable( true);
	s_CUI_ID_FRAME_RBTNMENU.SetPos( x, y );
	if( s_CUI_ID_FRAME_RBTNMENU.GetFrame() )
		theUiManager.ToTop( s_CUI_ID_FRAME_RBTNMENU.GetFrame() );
	theUiManager.Compositor();
}

namespace Rank
{
	CUI_ID_FRAME_RankList* GetRank()
	{
		return &s_CUI_ID_FRAME_RankList;
	}
}

//第一页
bool CUI_ID_FRAME_RankList::ID_BUTTON_LeftHeadOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RankList )
		return false;

	m_nCurrentPage = 1;
	RefreshPageInfo();
	SetCurrentPageText();
	return true;
}

// 上一页
bool CUI_ID_FRAME_RankList::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RankList )
		return false;
	
	if (m_nCurrentPage <= 1)
	{
		return false;
	}
	
	--m_nCurrentPage;
	RefreshPageInfo();
	SetCurrentPageText();
	return true;
}

//下一页
bool CUI_ID_FRAME_RankList::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RankList )
		return false;

	if (!m_pCurrRankInfos)
	{
		return false;
	}
	
	if (m_nCurrentPage * m_nShowNumPerPage >= m_pCurrRankInfos->size())
	{
		return false;
	}

	++m_nCurrentPage;
	RefreshPageInfo();
	SetCurrentPageText();
	return true;
}

// 最终页
bool CUI_ID_FRAME_RankList::ID_BUTTON_RightHeadOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RankList )
		return false;

	if (!m_pCurrRankInfos)
	{
		return false;
	}

	int nNum = m_pCurrRankInfos->size();
	m_nCurrentPage = nNum / m_nShowNumPerPage + 1;
	SetCurrentPageText();
	RefreshPageInfo();
	return true;
}

void CUI_ID_FRAME_RankList::RefreshPageInfo()
{
	try
	{
		std::string strType;
		if (m_pID_LIST_SubTypeList->GetCurSelItem())
			strType = m_pID_LIST_SubTypeList->GetCurSelItem()->m_szText;

		LuaFunction<void> RefreshRankContentsFunc( ScriptManager::instance().getLuaStateOwner(m_luaFilename), "RefreshRankContents" );
		RefreshRankContentsFunc( /*m_pActivedCheckBox->GetData()->m_szID, */strType.c_str() );
	}
	catch ( const LuaPlus::LuaException& e )
	{
		Log( e.GetErrorMessage() );
	}
}

void CUI_ID_FRAME_RankList::SetCurrentPageText()
{
	if ( !m_pID_FRAME_RankList )
		return;

	m_pID_TEXT_Page->SetText(m_nCurrentPage);	
}

void CUI_ID_FRAME_RankList::SetExplain(int nStringIndex)
{
	if (!m_pID_TEXT_Explain)
	{
		return;
	}

	// 设置排行榜描述
	char szContent[256] = {0};
	MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(nStringIndex));
	m_pID_TEXT_Explain->SetText(szContent);
}

void CUI_ID_FRAME_RankList::SetInfomation(const char* szType)
{
	if (m_pID_TEXT_Wait->IsVisable())
	{
		m_pID_TEXT_Information->SetVisable(false);
		m_pID_TEXT_Explain->SetVisable(false);
	}
	
	if (!m_pID_TEXT_Information)
	{
		return;
	}
	
	RankInfoSet::iterator it = m_rankInfoSets.find(szType);
	if (it == m_rankInfoSets.end())
	{
		return;
	}
	
	std::vector<RankInfo*>* pRankInfo = &(it->second);

	if (!pRankInfo)
	{
		return;
	}

	char szText[256] = {0};
	std::vector<RankInfo*>::iterator iter;
	for (iter = pRankInfo->begin(); iter != pRankInfo->end(); ++iter)
	{
		if ((*iter)->values["CharacterName"] == GetMeName())
		{
			MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Rank_MeLevelIn), (*iter)->values["Rank"].c_str());
			m_pID_TEXT_Information->SetText(szText);
			return;
		}
	}

	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Rank_MeLevelOut));
	m_pID_TEXT_Information->SetText(szText);
}

const char* CUI_ID_FRAME_RankList::GetCountryName(int nCountryId) const
{
	m_strCountryName = CountryFunction::GetCountryNameById(nCountryId);
	return m_strCountryName.c_str();
}

void CUI_ID_FRAME_RankList::SetTileText(const char* szText)
{
	if (!m_pID_TEXT_TypeText)
	{
		return;
	}

	m_pID_TEXT_TypeText->SetText(szText);
}