/********************************************************************
Created by UIEditor.exe
FileName: F:\project\Turbo\Bin\Client\Data\Ui\SkillLearn.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SkillLearn.h"
#include "PlayerRole.h"
#include "UIMgr.h"
#include "NetworkInput.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "../Player.h"
#include "ScreenInfoManager.h"
#include "Helper/XinFaHelper.h"
#include "MainMenu.h"

//---------------------------------------------------------------
//desc	: 判断角色的当前条件是否能够升级心法

enum ECanLearnXinFa
{
	E_CanLearn_XinFa_success,	//满足条件
	E_CanLearn_XinFa_level,		//不满足等级限制
	E_CanLearn_XinFa_money,		//不满足金钱限制
	E_CanLearn_XinFa_experience,//不满足经验限制
	E_CanLearn_XinFa_PreXinFa,	//不满足前置心法限制
	E_CanLearn_XinFa_Profession,//不满足职业限制
};

ECanLearnXinFa CanLearnXinFa(const XinFaConfig::STalentXinFa *pXinFa_)
{
	assert(pXinFa_ != NULL);
	
	// 等级
	if(thePlayerRole.GetLevel() < pXinFa_->nNeedLevel || thePlayerRole.GetLevel() + 4 < pXinFa_->nLevel)
	{
		return E_CanLearn_XinFa_level;
	}
	// 经验
	if(thePlayerRole.GetExpNotUsed() < pXinFa_->nNeedExp)
	{
		return E_CanLearn_XinFa_experience;
	}
	// 金钱
	//if(thePlayerRole.m_charinfo.baseinfo.liveinfo.jiaoZi + thePlayerRole.m_charinfo.baseinfo.liveinfo.dwMoney < pXinFa_->nNeedMoney)
	if(thePlayerRole.GetData(CPlayerRole::TYPE_JiaoZi) + thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) < pXinFa_->nNeedMoney)
	{
		return E_CanLearn_XinFa_money;
	}
	//前置心法
	if(pXinFa_->nPrevXinFa != 0)
	{
		if(NULL == thePlayerRole.m_xinFaBag.GetXinFaByID(pXinFa_->nPrevXinFa))
		{
			return E_CanLearn_XinFa_PreXinFa;
		}
	}

	//职业
	if(!IsValidProfession(pXinFa_, thePlayerRole.GetProfession()))
	{
		return E_CanLearn_XinFa_Profession;
	}
	
	
	return E_CanLearn_XinFa_success;
}

//desc	: 得到要升级的心法，即当前心法的下一级心法。
const XinFaConfig::STalentXinFa *GetLearningXinFa(const XinFaConfig::STalentXinFa *pXinFa_)
{
	if(pXinFa_ != NULL) 
		return XinFaConfig::Instance().GetXinFaByID(pXinFa_->nId, pXinFa_->nLevel + 1);
	return NULL;
}
//---------------------------------------------------------------

bool CUI_ID_FRAME_SKILL_LEARN::m_bStartLearn = false;
CUI_ID_FRAME_SKILL_LEARN s_CUI_ID_FRAME_SKILL_LEARN;

MAP_FRAME_RUN( s_CUI_ID_FRAME_SKILL_LEARN, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SKILL_LEARN, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillBookOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillBookOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillBookOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillBookOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_BUTTON_LearnOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_LIST__BookNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SKILL_LEARN, ID_LIST_AdditionalOnListSelectChange )

CUI_ID_FRAME_SKILL_LEARN::CUI_ID_FRAME_SKILL_LEARN()
{
	// Member
	m_pID_FRAME_SKILL_LEARN = NULL;
	m_pID_LISTIMG_SkillBook = NULL;
	m_pID_LISTIMG_Skill = NULL;
	m_pID_LIST__BookName = NULL;
	m_pID_LIST__BookLv = NULL;
	m_pID_LIST__Book = NULL;
	m_pID_TEXT_SkillName = NULL;
	m_pID_TEXT_SkillIntroduce = NULL;
	m_pID_TEXT_PointNeed = NULL;
	m_pID_TEXT_PointNow = NULL;
	m_pID_TEXT_Cost = NULL;
	m_pID_TEXT_Jiaozi = NULL;
	m_pID_TEXT_Jinqian = NULL;
	m_pID_BUTTON_Learn = NULL;

	m_pID_TEXT_NoPoint = NULL;
	m_pID_TEXT_NoMoney = NULL;
	m_pID_LIST_Additional = NULL;
	m_pID_TEXT_SkillNextIntroduce = NULL;

}
// Frame
bool CUI_ID_FRAME_SKILL_LEARN::OnFrameRun()
{
/*
	if ( !IsVisable() )
	{
		return false;
	}
	CPlayer* pNpc = NULL;
	CPlayer* pMe = NULL;
	pNpc = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );
	pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if ( !pMe || !pNpc || !pNpc->IsNpc() )
	{
		SetVisable(false);
		return false;
	}
	float fNpcX, fNpcY, fNpcZ;
	float fMeX,fMeY,fMeZ;
	pNpc->GetPos( &fNpcX, &fNpcY, &fNpcZ );
	pMe->GetPos( &fMeX, &fMeY, &fMeZ );
	float x = fNpcX - fMeX;
	float y = fNpcY - fMeY;
	float dist = sqrtf( x*x + y*y );
	if( dist > 12.0f )
	{
		SetVisable( false );
	}
*/

	return true;
}
bool CUI_ID_FRAME_SKILL_LEARN::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SKILL_LEARN::ID_LISTIMG_SkillBookOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SKILL_LEARN::ID_LISTIMG_SkillBookOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SKILL_LEARN::ID_LISTIMG_SkillBookOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	bool ret = m_xinFaUIHelper.ClickXinFaIcon(pItem);
	int index = m_pID_LISTIMG_SkillBook->GetItemIndex(pItem);
	m_pID_LIST_Additional->SetCurSelIndex(index);
	//m_pID_LIST__BookName->SetCurSelIndex(index);
	UpdateOtherInfo();
	return ret;
}

bool CUI_ID_FRAME_SKILL_LEARN::ID_LISTIMG_SkillBookOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SKILL_LEARN::ID_LISTIMG_SkillOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItemDrag,
															ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SKILL_LEARN::ID_LISTIMG_SkillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SKILL_LEARN::ID_LISTIMG_SkillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	/*bool ret = m_xinFaUIHelper.ClickXinFaIcon(pItem);
	UpdateOtherInfo();
	return ret;*/
	return m_xinFaUIHelper.ClickSkillIcon(pItem);
}
bool CUI_ID_FRAME_SKILL_LEARN::ID_LISTIMG_SkillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

void CUI_ID_FRAME_SKILL_LEARN::ID_LIST__BookNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	int index = m_pID_LIST__BookName->GetCurSelIndex();
	ControlIconDrag::S_ListImg* pSelItem = m_pID_LISTIMG_SkillBook->GetItemByIndex(index);
	m_xinFaUIHelper.ClickXinFaIcon(pSelItem);
}

void CUI_ID_FRAME_SKILL_LEARN::ID_LIST_AdditionalOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	int index = m_pID_LIST_Additional->GetCurSelIndex();
	ControlIconDrag::S_ListImg* pSelItem = m_pID_LISTIMG_SkillBook->GetItemByIndex(index);
	m_xinFaUIHelper.ClickXinFaIcon(pSelItem);
	UpdateOtherInfo();
}

// Button
bool CUI_ID_FRAME_SKILL_LEARN::ID_BUTTON_LearnOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SKILL_LEARN )
		return false;

	const XinFaConfig::STalentXinFa *pXinFa = GetLearningXinFa(m_xinFaUIHelper.GetSelectedXinFa());
	if(NULL == pXinFa)
		return false;

	ECanLearnXinFa result = CanLearnXinFa(pXinFa);
	if(E_CanLearn_XinFa_success == result)
	{
		//发送升级心法的消息
		MsgLearnXinFa msg;
		msg.nXinFaID = pXinFa->nId;
		msg.nXinFaLevel = pXinFa->nLevel;
		GettheNetworkInput().SendMsg( &msg );
	}
	else
	{
		eName failureReason;
		switch(result)
		{
		case E_CanLearn_XinFa_level:
			failureReason = eText_LearnXinFa_LevelNotEnough;
			break;
		case E_CanLearn_XinFa_experience:
			failureReason = eText_LearnXinFa_ExpNotEnough;
			break;
		case E_CanLearn_XinFa_money:
			failureReason = eText_LearnXinFa_GoldNotEnough;
			break;
		case E_CanLearn_XinFa_PreXinFa:
			failureReason = eText_LearnXinFa_PreXinFaNotOk;
			break;
		case E_CanLearn_XinFa_Profession:
			failureReason = eText_LearnXinFa_ProfessionNotOk;
			break;
		default:
			assert(false);
		}

		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, theXmlString.GetString(failureReason));
	}
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SKILL_LEARN::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SkillLearn.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SkillLearn.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SKILL_LEARN::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SKILL_LEARN, s_CUI_ID_FRAME_SKILL_LEARNOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SKILL_LEARN, s_CUI_ID_FRAME_SKILL_LEARNOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillBook, s_CUI_ID_FRAME_SKILL_LEARNID_LISTIMG_SkillBookOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillBook, s_CUI_ID_FRAME_SKILL_LEARNID_LISTIMG_SkillBookOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillBook, s_CUI_ID_FRAME_SKILL_LEARNID_LISTIMG_SkillBookOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillBook, s_CUI_ID_FRAME_SKILL_LEARNID_LISTIMG_SkillBookOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SKILL_LEARN, ID_LISTIMG_Skill, s_CUI_ID_FRAME_SKILL_LEARNID_LISTIMG_SkillOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SKILL_LEARN, ID_LISTIMG_Skill, s_CUI_ID_FRAME_SKILL_LEARNID_LISTIMG_SkillOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SKILL_LEARN, ID_LISTIMG_Skill, s_CUI_ID_FRAME_SKILL_LEARNID_LISTIMG_SkillOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SKILL_LEARN, ID_LISTIMG_Skill, s_CUI_ID_FRAME_SKILL_LEARNID_LISTIMG_SkillOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SKILL_LEARN, ID_BUTTON_Learn, s_CUI_ID_FRAME_SKILL_LEARNID_BUTTON_LearnOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_SKILL_LEARN, ID_LIST__BookName, s_CUI_ID_FRAME_SKILL_LEARNID_LIST__BookNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_SKILL_LEARN, ID_LIST_Additional, s_CUI_ID_FRAME_SKILL_LEARNID_LIST_AdditionalOnListSelectChange );

	m_pID_FRAME_SKILL_LEARN = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SKILL_LEARN );
	m_pID_LISTIMG_SkillBook = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_LISTIMG_SkillBook );
	m_pID_LISTIMG_Skill = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_LISTIMG_Skill );
	
	m_pID_TEXT_SkillName = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_TEXT_SkillName );
	m_pID_TEXT_SkillIntroduce = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_TEXT_SkillIntroduce );
	m_pID_TEXT_PointNeed = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_TEXT_PointNeed );
	m_pID_TEXT_PointNow = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_TEXT_PointNow );
	m_pID_TEXT_Cost = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_TEXT_Cost );
	m_pID_TEXT_Jiaozi = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_TEXT_Jiaozi );
	m_pID_TEXT_Jinqian = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_TEXT_Jinqian );
	m_pID_BUTTON_Learn = (ControlButton*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_BUTTON_Learn );
	m_pID_LIST__BookName = (ControlList*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_LIST__BookName );
	m_pID_LIST__BookLv = (ControlList*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_LIST__BookLv );
	m_pID_LIST__Book = (ControlList*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_LIST__Book );

	m_pID_TEXT_NoPoint = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_TEXT_NoPoint );
	m_pID_TEXT_NoMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_TEXT_NoMoney );

	m_pID_LIST_Additional = (ControlList*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_LIST_Additional );
	m_pID_TEXT_SkillNextIntroduce = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL_LEARN, ID_TEXT_SkillNextIntroduce );

	assert( m_pID_FRAME_SKILL_LEARN );
	assert( m_pID_LISTIMG_SkillBook );
	assert( m_pID_LISTIMG_Skill );

	assert( m_pID_TEXT_SkillName );
	assert( m_pID_TEXT_SkillIntroduce );
	assert( m_pID_TEXT_PointNeed );
	assert( m_pID_TEXT_PointNow );
	assert( m_pID_TEXT_Cost );
	assert( m_pID_TEXT_Jiaozi );
	assert( m_pID_TEXT_Jinqian );
	assert( m_pID_BUTTON_Learn );
	assert( m_pID_LIST__BookName );
	assert( m_pID_LIST_Additional );
	assert( m_pID_LIST__BookLv );
	assert( m_pID_LIST__Book );
	assert( m_pID_TEXT_NoPoint );
	assert( m_pID_TEXT_NoMoney );
	assert( m_pID_TEXT_SkillNextIntroduce );

	GetFrame()->SetFather(s_CUI_ID_FRAME_SKILL.GetFrame());
	char buf[64];
	for(int i=1; i<=UI_XINFACOUNT; ++i)
	{
		sprintf(buf, "ID_TEXT_SkillCondition%d%d", i, i );
		m_pID_TEXT_SubSkillCondition[i - 1] = (ControlText*)theUiManager.FindControl(ID_FRAME_SKILL_LEARN, buf);
		assert(m_pID_TEXT_SubSkillCondition[i - 1] != NULL);

		sprintf(buf, "ID_TEXT_SkiillLevel%d%d", i , i );
		m_pID_TEXT_SubSkillLevel[i - 1] = (ControlText*)theUiManager.FindControl(ID_FRAME_SKILL_LEARN, buf);
		assert(m_pID_TEXT_SubSkillLevel[i - 1] != NULL);

		sprintf(buf, "ID_TEXT_SkillName%d%d", i , i );
		m_pID_TEXT_SubSkillName[i - 1] = (ControlText*)theUiManager.FindControl(ID_FRAME_SKILL_LEARN, buf);
		assert(m_pID_TEXT_SubSkillName[i - 1] != NULL);
	}

	m_xinFaUIHelper.Init(m_pID_LISTIMG_SkillBook, m_pID_LISTIMG_Skill,  
		m_pID_TEXT_SkillName, m_pID_TEXT_SkillIntroduce, m_pID_LIST__BookLv, m_pID_LIST__BookName, 
		m_pID_TEXT_SubSkillName, m_pID_TEXT_SubSkillCondition, m_pID_TEXT_SubSkillLevel, 
		UI_XINFACOUNT,m_pID_LIST_Additional, m_pID_TEXT_SkillNextIntroduce);

	m_pID_LISTIMG_SkillBook ->SetEnableDragIn(false);
	m_pID_LISTIMG_SkillBook ->SetEnableDragOut(false);
	m_pID_LISTIMG_Skill->SetEnableDragIn(false);
	

	//m_pID_LIST__Book->SetMsgHoldup(false);
	m_pID_LIST__BookLv->SetMsgHoldup(false);
	m_pID_LIST__BookName->SetMsgHoldup(false);
	m_pID_LIST_Additional->SetMsgHoldup(true);
	m_pID_LIST__BookName->HaveSelBar(false);
	m_pID_LIST_Additional->HaveSelBar(true);
	m_pID_LIST__BookLv->HaveSelBar(false);
	m_pID_LIST__Book->HaveSelBar(false);
	m_pID_LIST__BookName->SetEnable(false);
	m_pID_LIST_Additional->SetEnable(true);
	m_pID_LIST__BookLv->SetEnable(false);

	m_pID_TEXT_NoMoney->SetVisable(false);
	m_pID_TEXT_NoPoint->SetVisable(false);

	SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SKILL_LEARN::_UnLoadUI()
{
	m_pID_FRAME_SKILL_LEARN = NULL;
	
	m_xinFaUIHelper.Reset();

	return theUiManager.RemoveFrame( "Data\\UI\\SkillLearn.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_SKILL_LEARN::_IsVisable()
{
	if( !m_pID_FRAME_SKILL_LEARN )
		return false;
	return m_pID_FRAME_SKILL_LEARN->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_SKILL_LEARN::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_SKILL_LEARN )
		return;
	m_pID_FRAME_SKILL_LEARN->SetVisable( bVisable );
	if (bVisable)
	{
		m_nNpcId = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
		Refresh();

		m_pID_LIST_Additional->SetCurSelIndex(0);
		ControlIconDrag::S_ListImg* pSelItem = m_pID_LISTIMG_SkillBook->GetItemByIndex(0);
		m_xinFaUIHelper.ClickXinFaIcon(pSelItem);
		UpdateOtherInfo();
	}
	else
	{		
		m_xinFaUIHelper.ClearSelectedInfo();
	}
}

void CUI_ID_FRAME_SKILL_LEARN::Refresh()
{
	if( !m_pID_FRAME_SKILL_LEARN )
		return;

	m_xinFaUIHelper.RefreshXinFa();
	UpdateOtherInfo();
}

void CUI_ID_FRAME_SKILL_LEARN::UpdateOtherInfo(void)
{
	if(m_pID_TEXT_PointNow != NULL)
	{
		char exp[256]={0};
		sprintf_s(exp,sizeof(exp)/sizeof(char),"%I64d",thePlayerRole.GetExpNotUsed());
		m_pID_TEXT_PointNow->SetText(exp);
	}

	if(m_pID_TEXT_Jiaozi != NULL)
	{
// 		char buf[32];
// 		sprintf(buf, "%d金", thePlayerRole.m_charinfo.baseinfo.liveinfo.jiaoZi);
// 		m_pID_TEXT_Jiaozi->SetText(buf);

		std::string text;
		thePlayerRole.GetGSCStringFromCurrentJiaoZi(text);
		*m_pID_TEXT_Jiaozi = text; 
	}

	if(m_pID_TEXT_Jinqian != NULL)
	{
// 		char buf[32];
// 		sprintf(buf, "%d金", thePlayerRole.m_charinfo.baseinfo.liveinfo.dwMoney);
// 		m_pID_TEXT_Jinqian->SetText(buf);

		std::string text;
		thePlayerRole.GetGSCStringFromCurrentMoney(text);
		*m_pID_TEXT_Jinqian = text;
	}

	const XinFaConfig::STalentXinFa *pXinFa = GetLearningXinFa(m_xinFaUIHelper.GetSelectedXinFa());
	if(pXinFa != NULL)
	{
		if(m_pID_TEXT_PointNeed != NULL)
		{
			m_pID_TEXT_PointNeed->SetText(pXinFa->nNeedExp);
			if (thePlayerRole.GetExpNotUsed()<pXinFa->nNeedExp)
			{m_pID_TEXT_NoPoint->SetVisable(true);}
			else
			{m_pID_TEXT_NoPoint->SetVisable(false);}
		}

		if(m_pID_TEXT_Cost != NULL)
		{
// 			char buf[32];
// 			sprintf(buf, "%d金", pXinFa->nNeedMoney);
// 			m_pID_TEXT_Cost->SetText(buf);

			std::string text;
			//thePlayerRole.GetGSCStringFromMoney(pXinFa->nNeedMoney, text);
			thePlayerRole.GetGSCStringFromJiaoZi(pXinFa->nNeedMoney, text);
			*m_pID_TEXT_Cost = text;
			if (thePlayerRole.GetData(CPlayerRole::TYPE_JiaoZi) + thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) < pXinFa->nNeedMoney)
			{m_pID_TEXT_NoMoney->SetVisable(true);}
			else
			{m_pID_TEXT_NoMoney->SetVisable(false);}
		}

		if(m_pID_BUTTON_Learn != NULL)
		{
			ECanLearnXinFa eResult = CanLearnXinFa(pXinFa);
			if(E_CanLearn_XinFa_success == eResult)
			{
				m_pID_BUTTON_Learn->SetEnable(true);
			}
			else
			{
				m_pID_BUTTON_Learn->SetEnable(false);
				if (E_CanLearn_XinFa_level == eResult)
				{
					CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_RiseInfo_RandomTip,
						theXmlString.GetString(eText_SkillLearn__LevelLess),pXinFa->nNeedLevel );
				}
			}
		}
	}
	else
	{
		if(m_pID_TEXT_PointNeed != NULL)
		{
			m_pID_TEXT_PointNeed->Clear();
		}

		if(m_pID_TEXT_Cost != NULL)
		{
			m_pID_TEXT_Cost->Clear();
		}

		if(m_pID_BUTTON_Learn != NULL)
		{
			m_pID_BUTTON_Learn->SetEnable(false);
		}
	}

}

void CUI_ID_FRAME_SKILL_LEARN::CheckLevel()
{
	if ( m_xinFaUIHelper.CheckXinFaLevel() )
		s_CUI_ID_FRAME_MainMenu.SetSkillHighLight( true );
}