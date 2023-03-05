/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\FriendView.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FriendView.h"
#include "RelationDefine.h"
#include "PlayerRole.h"
#include "FriendDlg.h"
#include "CountryFunction.h"
#include "Create.h"
#include "GuildDefine.h"
#include "TitleConfig.h"
#include "MapConfig.h"

extern const char* g_gifFriendStar[];

CUI_ID_FRAME_FriendView s_CUI_ID_FRAME_FriendView;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FriendView, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FriendView, OnFrameRender )
CUI_ID_FRAME_FriendView::CUI_ID_FRAME_FriendView()
{
	// Member
	m_pID_FRAME_FriendView = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_PeopleName = NULL;
	m_pID_PICTURE_PeopleHead = NULL;
	m_pID_TEXT_Level = NULL;
	m_pID_TEXT_PeopleLevel = NULL;
	m_pID_TEXT_Work = NULL;
	m_pID_TEXT_PeopleWork = NULL;
	m_pID_TEXT_FriendFavor = NULL;
	m_pID_TEXT_PeopleFriendFavor = NULL;
	m_pID_TEXT_Position = NULL;
	m_pID_TEXT_PeoplePosition = NULL;
	m_pID_TEXT_Mood = NULL;
	m_pID_TEXT_PeopleMood = NULL;
	m_pID_TEXT_Remark = NULL;
	m_pID_TEXT_RemarkZ = NULL;
	m_pID_TEXT_CountryZ = NULL;
	m_pID_TEXT_CountryName = NULL;
	m_pID_TEXT_ConfraternityJob = NULL;
	m_pID_TEXT_Relation = NULL;

	m_pID_TEXT_Birthday = NULL;
	m_pID_TEXT_BirthdayDate = NULL;

	m_pID_TEXT_Fettle = NULL;
	m_pID_TEXT_FettleName = NULL;

	m_pID_TEXT_Position = NULL;
	m_pID_TEXT_PositionNanme = NULL;

	m_pID_TEXT_Title = NULL;
	m_pID_TEXT_TitleName = NULL;

	m_pID_TEXT_Ip = NULL;

}
// Frame
bool CUI_ID_FRAME_FriendView::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_FriendView::OnFrameRender()
{
// 	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_FriendView::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FriendView.MEUI" , false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FriendView.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_FriendView::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_FriendView, s_CUI_ID_FRAME_FriendViewOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_FriendView, s_CUI_ID_FRAME_FriendViewOnFrameRender );

	m_pID_FRAME_FriendView = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FriendView );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Name );
	m_pID_TEXT_PeopleName = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_PeopleName );
	m_pID_PICTURE_PeopleHead = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FriendView, ID_PICTURE_PeopleHead );
	m_pID_TEXT_Level = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Level );
	m_pID_TEXT_PeopleLevel = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_PeopleLevel );
	m_pID_TEXT_Work = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Work );
	m_pID_TEXT_PeopleWork = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_PeopleWork );
	m_pID_TEXT_FriendFavor = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_FriendFavor );
	m_pID_TEXT_PeopleFriendFavor = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_PeopleFriendFavor );
	m_pID_TEXT_Position = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Position );
	m_pID_TEXT_PeoplePosition = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_PeoplePosition );
	m_pID_TEXT_Mood = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Mood );
	m_pID_TEXT_PeopleMood = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_PeopleMood );
	m_pID_TEXT_Remark = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Remark );
	m_pID_TEXT_RemarkZ = (ControlEdit*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_RemarkZ );
	m_pID_TEXT_CountryZ = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_CountryZ );
	m_pID_TEXT_CountryName = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_CountryName );
	m_pID_TEXT_ConfraternityJob = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_ConfraternityJob );
	m_pID_TEXT_Relation = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Relation );

	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Title );
	m_pID_TEXT_TitleName = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_TitleName );
	m_pID_TEXT_Fettle = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Fettle );
	m_pID_TEXT_FettleName = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_FettleName );
	m_pID_TEXT_Position = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Position );
	m_pID_TEXT_PositionNanme = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_PositionNanme );
	m_pID_TEXT_Birthday = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Birthday );
	m_pID_TEXT_BirthdayDate = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_BirthdayDate );
	m_pID_TEXT_Ip = (ControlText*)theUiManager.FindControl( ID_FRAME_FriendView, ID_TEXT_Ip );

	assert( m_pID_FRAME_FriendView );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_PeopleName );
	assert( m_pID_PICTURE_PeopleHead );
	assert( m_pID_TEXT_Level );
	assert( m_pID_TEXT_PeopleLevel );
	assert( m_pID_TEXT_Work );
	assert( m_pID_TEXT_PeopleWork );
	assert( m_pID_TEXT_FriendFavor );
	assert( m_pID_TEXT_PeopleFriendFavor );
	assert( m_pID_TEXT_Position );
	assert( m_pID_TEXT_PeoplePosition );
	assert( m_pID_TEXT_Mood );
	assert( m_pID_TEXT_PeopleMood );
	assert( m_pID_TEXT_Remark );
	assert( m_pID_TEXT_RemarkZ );
	assert( m_pID_TEXT_CountryZ );
	assert( m_pID_TEXT_CountryName );
	assert( m_pID_TEXT_ConfraternityJob );
	assert( m_pID_TEXT_Relation );
	assert( m_pID_TEXT_Title );
	assert( m_pID_TEXT_TitleName );
	assert( m_pID_TEXT_Fettle );
	assert( m_pID_TEXT_FettleName );
	assert( m_pID_TEXT_Position );
	assert( m_pID_TEXT_PositionNanme );
	assert( m_pID_TEXT_Birthday );
	assert( m_pID_TEXT_BirthdayDate );
	assert( m_pID_TEXT_Ip );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_FriendView::_UnLoadUI()
{
	m_pID_FRAME_FriendView = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_PeopleName = NULL;
	m_pID_PICTURE_PeopleHead = NULL;
	m_pID_TEXT_Level = NULL;
	m_pID_TEXT_PeopleLevel = NULL;
	m_pID_TEXT_Work = NULL;
	m_pID_TEXT_PeopleWork = NULL;
	m_pID_TEXT_FriendFavor = NULL;
	m_pID_TEXT_PeopleFriendFavor = NULL;
	m_pID_TEXT_Position = NULL;
	m_pID_TEXT_PeoplePosition = NULL;
	m_pID_TEXT_Mood = NULL;
	m_pID_TEXT_PeopleMood = NULL;
	m_pID_TEXT_Remark = NULL;
	m_pID_TEXT_RemarkZ = NULL;
	m_pID_TEXT_CountryZ = NULL;
	m_pID_TEXT_CountryName = NULL;
	m_pID_TEXT_ConfraternityJob = NULL;
	m_pID_TEXT_Relation = NULL;

	m_pID_TEXT_Birthday = NULL;
	m_pID_TEXT_BirthdayDate = NULL;

	m_pID_TEXT_Fettle = NULL;
	m_pID_TEXT_FettleName = NULL;

	m_pID_TEXT_Position = NULL;
	m_pID_TEXT_PositionNanme = NULL;

	m_pID_TEXT_Title = NULL;
	m_pID_TEXT_TitleName = NULL;

	m_pID_TEXT_Ip = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\FriendView.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_FriendView::_IsVisable()
{
	if ( !m_pID_FRAME_FriendView )
		return false;
	return m_pID_FRAME_FriendView->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_FriendView::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_FriendView )
		return ;
	m_pID_FRAME_FriendView->SetVisable( bVisable );
}

void CUI_ID_FRAME_FriendView::Refresh( RelationDataToClient* pFriendData)
{
	if (!IsUILoad() || pFriendData == NULL)
	{
		return;
	}
	
	m_pID_TEXT_PeopleName->SetText(pFriendData->GetName());
	m_pID_TEXT_PeopleLevel->SetText(pFriendData->GetLevel());
	
	std::string strSex;
	string strProfession ;
	s_CUI_ID_FRAME_Friend.GetSexProfessionString(*pFriendData, strSex, strProfession);
	m_pID_TEXT_PeopleWork->SetText(strProfession.c_str());	
	
	std::string portraitName = s_CUI_ID_FRAME_CREATE.GetPortraitName( pFriendData->GetSex(), pFriendData->GetHeadPic(),!pFriendData->GetOnLine() );
	portraitName = "Data\\Ui\\" + portraitName;
	m_pID_PICTURE_PeopleHead->SetPicName( portraitName.c_str() );

	m_pID_TEXT_Relation->Clear();
	if (pFriendData->HaveRelation(RelationDefine::Friend))
	{
		m_pID_TEXT_PeopleFriendFavor->SetVisable(true);
		int level = theRelationConfig.GetFriendLevel(pFriendData->GetFriendly());
		if (level > 0 && level <= CUI_ID_FRAME_Friend::m_nFriendStar)
		{
			char Favorbuf[32];			
			sprintf(Favorbuf, "%s (%d)", g_gifFriendStar[level - 1], pFriendData->GetFriendly());
			m_pID_TEXT_PeopleFriendFavor->SetText(Favorbuf);
		}
		m_pID_TEXT_FriendFavor->SetVisable(true);
		int nStringId = -1;
		const LevelInfo* pLevelInfo = theRelationConfig.GetLevelInfo(level);
		if (pLevelInfo)
		{
			nStringId = pLevelInfo->GetStringID();
		}		
		if (pFriendData->HaveRelation(RelationDefine::Marriage))
		{
			if (pFriendData->GetSex() == Sex_Male)
			{
				nStringId = eText_Ralation_Husband;
			}
			else
			{
				nStringId = eText_Ralation_Wife;
			}			
		} 
		else if(pFriendData->HaveRelation(RelationDefine::Teacher))
		{
			nStringId = eText_Ralation_Teacher;
		} 
		else if(pFriendData->HaveRelation(RelationDefine::Student))
		{
			nStringId = eText_Ralation_Student;
		} 
		else if(pFriendData->HaveRelation(RelationDefine::Brother))
		{
			nStringId = eText_Ralation_Brother;
		} 
		if (-1 != nStringId)
		{
			m_pID_TEXT_Relation->SetText(theXmlString.GetString(nStringId));
		}		
	}
	else
	{
		m_pID_TEXT_PeopleFriendFavor->SetVisable(false);
		m_pID_TEXT_FriendFavor->SetVisable(false);
		if (pFriendData->HaveRelation(RelationDefine::TempFriend))
		{
			m_pID_TEXT_Relation->SetText(theXmlString.GetString(eText_TempFriend));
		}
		else if (pFriendData->HaveRelation(RelationDefine::Vendetta))
		{
			m_pID_TEXT_Relation->SetText(theXmlString.GetString(eText_Vendetta));
		}
		else if (pFriendData->HaveRelation(RelationDefine::BlackList))
		{
			m_pID_TEXT_Relation->SetText(theXmlString.GetString(eText_BlackList1));
		}
		
	}

	m_pID_TEXT_CountryName->SetText(CountryFunction::GetCountryNameById(pFriendData->GetCountry()));
	
	m_pID_TEXT_PeoplePosition->SetText(CountryFunction::GetCountryOfficialNameById(CountryDefine::GetCountryPositionByTitle(pFriendData->GetPosition())));

	m_pID_TEXT_Remark->SetText(pFriendData->GetRemark());
	m_pID_TEXT_PeopleMood->SetText(pFriendData->GetSignature());

	m_pID_TEXT_ConfraternityJob->Clear();
	char szGuildName[128] = {0};
	if (pFriendData->GetGuildID() != GuildDefine::InitID)
	{
		const CGuildInfo* pGuildInfo = thePlayerRole.GetGuildById(pFriendData->GetGuildID());
		if (pGuildInfo)
		{
			m_pID_TEXT_ConfraternityJob->SetText(pGuildInfo->GetName());
		}
	}

	const PersonalInfo &info = pFriendData->GetPersonalInfo();

	if(m_pID_TEXT_BirthdayDate != NULL)
	{
		m_pID_TEXT_BirthdayDate->Clear();

		char buf[16];
		//sprintf(buf, "%2d月%2d日", info.GetPersonalMonth(), info.GetPersonalDay());
		sprintf(buf, theXmlString.GetString(eText_FRIEND_BIRTHDAY), info.GetPersonalMonth(), info.GetPersonalDay());
		m_pID_TEXT_BirthdayDate->SetText(buf);
	}

	if(m_pID_TEXT_FettleName != NULL)
	{
		m_pID_TEXT_FettleName->Clear();
		if(pFriendData->GetOnLine())
		{
			m_pID_TEXT_FettleName->SetText(theXmlString.GetString(eText_FRIEND_ONLINE));
		}
		else
		{
			m_pID_TEXT_FettleName->SetText(theXmlString.GetString(eText_FRIEND_OFFLINE));
		}
	}

	//所在地图
	if(m_pID_TEXT_PositionNanme != NULL)
	{
		m_pID_TEXT_PositionNanme->Clear();

		MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(pFriendData->GetMapID());
		if (pMapData !=NULL)
		{
			m_pID_TEXT_PositionNanme->SetText(pMapData->MapName.c_str());
		}
	}

	if(m_pID_TEXT_TitleName != NULL)
	{
		m_pID_TEXT_TitleName->Clear();

		if(pFriendData->GetTitleID() > 0)
		{
			TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID(pFriendData->GetTitleID());
			assert(pTitle != NULL);
			if(pTitle != NULL)
			{
				m_pID_TEXT_TitleName->SetText(pTitle->GetName());
			}
		}
	}

	if(m_pID_TEXT_Ip != NULL)
	{
		m_pID_TEXT_Ip->Clear();
		m_pID_TEXT_Ip->SetText(pFriendData->GetIp());
	}

}