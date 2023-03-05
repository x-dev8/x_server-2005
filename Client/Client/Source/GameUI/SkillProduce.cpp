/********************************************************************
                modified by zhuomeng.hu		[10/28/2010]
                重写了商业技能，删除了大量冗余的代码
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SkillProduce.h"
#include "ItemDetail.h"
#include "PlayerRole.h"
#include "Cfg.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "MeTerrain/stdafx.h"
#include "ScreenInfoManager.h"
#include "Compound.h"
#include "Common.h"

CUI_ID_FRAME_SkillProduce s_CUI_ID_FRAME_SkillProduce;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SkillProduce, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SkillProduce, OnFrameRender )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill1OnIconButtonClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill2OnIconButtonClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill3OnIconButtonClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill4OnIconButtonClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill5OnIconButtonClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill6OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill1OnIconRButtonUp )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill2OnIconRButtonUp )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill3OnIconRButtonUp )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill4OnIconRButtonUp )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill5OnIconRButtonUp )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_LISTIMG_Skill6OnIconRButtonUp )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_BUTTON_BackOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SkillProduce, ID_BUTTON_NextOnButtonClick )

CUI_ID_FRAME_SkillProduce::CUI_ID_FRAME_SkillProduce()
{
	ResetMembers();
}

void CUI_ID_FRAME_SkillProduce::ResetMembers()
{
    m_pID_FRAME_SkillProduce = NULL;
    m_pID_TEXT_HuoLi = NULL;

    //m_pID_BUTTON_Back = NULL;
    //m_pID_BUTTON_Next = NULL;

    for( int i = 0; i < ICON_PERPAGE; ++i )
    {
        m_pID_LISTIMG_Skill[i] = NULL;
        m_pID_LIST_Npc[i] = NULL;
        m_pID_TEXT_SkillName[i] = NULL;
        m_pID_TEXT_SkillLvl[i] = NULL;
        m_pID_TEXT_SkillNum[i] = NULL;
        m_pID_PICTURE_SkillNum[i] = NULL;
		m_pID_PROGRESS_SkillValue[i] = NULL;
    }

    m_bInited = false;
	m_ucCurPage = 0;
	m_ucPageNum = 0;
	m_ucCurPageSkillNum = 0;
}

// Frame
bool CUI_ID_FRAME_SkillProduce::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_SkillProduce::OnFrameRender()
{
	return true;
}

bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

	OnIconClick( 0 );    
	return false;
}
bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

	OnIconClick(1 );    
	return false;
}
bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

	OnIconClick( 2 );    
	return false;
}
bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

	OnIconClick( 3 );    
	return false;
}
bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

	OnIconClick( 4 );    
	return false;
}
bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

	OnIconClick( 5 );    
	return false;
}


bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

    OnIconClick( 0 );    
	return false;
}

bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

    OnIconClick( 1 );    
	return false;
}

bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

	OnIconClick( 2 );    
	return false;
}

bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

    OnIconClick( 3 );    
	return false;
}

bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

    OnIconClick( 4 );    
	return false;
}

bool CUI_ID_FRAME_SkillProduce::ID_LISTIMG_Skill6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;

    OnIconClick( 5 );    
	return false;
}

/*  等待翻页的扩展
bool CUI_ID_FRAME_SkillProduce::ID_BUTTON_BackOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;
	if( m_ucCurPage > 0 )
	{
		--m_ucCurPage;
		ShowPage(m_ucCurPage);
	}
	return true;
}

bool CUI_ID_FRAME_SkillProduce::ID_BUTTON_NextOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SkillProduce )
		return false;
	if( m_ucCurPage + 1 < m_ucPageNum )
	{
		++m_ucCurPage;
		ShowPage(m_ucCurPage);
	}
	return true;
}
*/

void CUI_ID_FRAME_SkillProduce::InitializeAtEnterWorld()
{
    m_bInited = false;
    m_ucCurPage = 0;
    m_ucPageNum = 0;
    m_ucCurPageSkillNum = 0;

	if ( IsUILoad() )
	{
		for ( int idx = 0; idx < ICON_PERPAGE; ++idx )
		{
			m_pID_PROGRESS_SkillValue[idx]->SetValue( 0 );
			m_pID_PROGRESS_SkillValue[idx]->SetVisable( true );
		}
	}
}

// 装载UI
bool CUI_ID_FRAME_SkillProduce::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SkillProduce.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SkillProduce.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SkillProduce::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SkillProduce, s_CUI_ID_FRAME_SkillProduceOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SkillProduce, s_CUI_ID_FRAME_SkillProduceOnFrameRender );
    theUiManager.OnIconButtonClick( ID_FRAME_SkillProduce, ID_LISTIMG_Skill1, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill1OnIconButtonClick );
    theUiManager.OnIconButtonClick( ID_FRAME_SkillProduce, ID_LISTIMG_Skill2, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill2OnIconButtonClick );
    theUiManager.OnIconButtonClick( ID_FRAME_SkillProduce, ID_LISTIMG_Skill3, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill3OnIconButtonClick );
    theUiManager.OnIconButtonClick( ID_FRAME_SkillProduce, ID_LISTIMG_Skill4, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill4OnIconButtonClick );
    theUiManager.OnIconButtonClick( ID_FRAME_SkillProduce, ID_LISTIMG_Skill5, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill5OnIconButtonClick );
    theUiManager.OnIconButtonClick( ID_FRAME_SkillProduce, ID_LISTIMG_Skill6, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill6OnIconButtonClick );

	theUiManager.OnIconRButtonUp( ID_FRAME_SkillProduce, ID_LISTIMG_Skill1, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill1OnIconRButtonUp );
	theUiManager.OnIconRButtonUp( ID_FRAME_SkillProduce, ID_LISTIMG_Skill2, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill2OnIconRButtonUp );
	theUiManager.OnIconRButtonUp( ID_FRAME_SkillProduce, ID_LISTIMG_Skill3, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill3OnIconRButtonUp );
	theUiManager.OnIconRButtonUp( ID_FRAME_SkillProduce, ID_LISTIMG_Skill4, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill4OnIconRButtonUp );
	theUiManager.OnIconRButtonUp( ID_FRAME_SkillProduce, ID_LISTIMG_Skill5, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill5OnIconRButtonUp );
// 	theUiManager.OnButtonClick( IDID_FRAME_SkillProduce, ID_LISTIMG_Skill6, s_CUI_ID_FRAME_SkillProduceID_LISTIMG_Skill6OnIconButtonClick_FRAME_SkillProduce, ID_BUTTON_Back, s_CUI_ID_FRAME_SkillProduceID_BUTTON_BackOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_SkillProduce, ID_BUTTON_Next, s_CUI_ID_FRAME_SkillProduceID_BUTTON_NextOnButtonClick );

	m_pID_FRAME_SkillProduce = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SkillProduce );
    m_pID_TEXT_HuoLi = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_HuoLi );
//  m_pID_BUTTON_Back = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_BUTTON_Back );
//  m_pID_BUTTON_Next = (ControlButton*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_BUTTON_Next );
	m_pID_LISTIMG_Skill[0] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LISTIMG_Skill1 );
	m_pID_LISTIMG_Skill[1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LISTIMG_Skill2 );
	m_pID_LISTIMG_Skill[2] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LISTIMG_Skill3 );
	m_pID_LISTIMG_Skill[3] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LISTIMG_Skill4 );
	m_pID_LISTIMG_Skill[4] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LISTIMG_Skill5 );
	m_pID_LISTIMG_Skill[5] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LISTIMG_Skill6 );
    m_pID_LIST_Npc[0] = (ControlList*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LIST_Npc1 );
    m_pID_LIST_Npc[1] = (ControlList*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LIST_Npc2 );
    m_pID_LIST_Npc[2] = (ControlList*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LIST_Npc3 );
    m_pID_LIST_Npc[3] = (ControlList*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LIST_Npc4 );
    m_pID_LIST_Npc[4] = (ControlList*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LIST_Npc5 );
    m_pID_LIST_Npc[5] = (ControlList*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_LIST_Npc6 );
	m_pID_TEXT_SkillName[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillName1 );
	m_pID_TEXT_SkillName[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillName2 );
	m_pID_TEXT_SkillName[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillName3 );
	m_pID_TEXT_SkillName[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillName4 );
	m_pID_TEXT_SkillName[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillName5 );
	m_pID_TEXT_SkillName[5] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillName6 );
	m_pID_TEXT_SkillLvl[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillLvl1 );
	m_pID_TEXT_SkillLvl[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillLvl2 );
	m_pID_TEXT_SkillLvl[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillLvl3 );
	m_pID_TEXT_SkillLvl[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillLvl4 );
	m_pID_TEXT_SkillLvl[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillLvl5 );
	m_pID_TEXT_SkillLvl[5] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillLvl6 );

 	m_pID_TEXT_SkillNum[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillNum1 );
 	m_pID_TEXT_SkillNum[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillNum2 );
	m_pID_TEXT_SkillNum[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillNum3 );
 	m_pID_TEXT_SkillNum[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillNum4 );
 	m_pID_TEXT_SkillNum[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillNum5 );
 	m_pID_TEXT_SkillNum[5] = (ControlText*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_TEXT_SkillNum6 );
    m_pID_PICTURE_SkillNum[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PICTURE_SkillNum1 );
    m_pID_PICTURE_SkillNum[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PICTURE_SkillNum2 );
	m_pID_PICTURE_SkillNum[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PICTURE_SkillNum3 );
    m_pID_PICTURE_SkillNum[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PICTURE_SkillNum4 );
    m_pID_PICTURE_SkillNum[4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PICTURE_SkillNum5 );
    m_pID_PICTURE_SkillNum[5] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PICTURE_SkillNum6 );


	m_pID_PROGRESS_SkillValue[0] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PROGRESS_Roll1 );
	m_pID_PROGRESS_SkillValue[1] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PROGRESS_Roll2 );
	m_pID_PROGRESS_SkillValue[2] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PROGRESS_Roll3 );
	m_pID_PROGRESS_SkillValue[3] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PROGRESS_Roll4 );
	m_pID_PROGRESS_SkillValue[4] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PROGRESS_Roll5 );
	m_pID_PROGRESS_SkillValue[5] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SkillProduce, ID_PROGRESS_Roll6 );

 	assert( m_pID_FRAME_SkillProduce );
    assert( m_pID_TEXT_HuoLi );
// 	assert( m_pID_BUTTON_Back );
// 	assert( m_pID_BUTTON_Next );

    for( int i = 0; i < ICON_PERPAGE; ++i )
    {
        assert( m_pID_LISTIMG_Skill[i] );
        assert( m_pID_LIST_Npc[i] );
        assert( m_pID_TEXT_SkillName[i] );
        assert( m_pID_TEXT_SkillLvl[i] );
        assert( m_pID_TEXT_SkillNum[i] );
        assert( m_pID_PICTURE_SkillNum[i] );
		assert( m_pID_PROGRESS_SkillValue[i] );
    }

    for( int nIndex = 0; nIndex < ICON_PERPAGE; ++nIndex )
    {
        m_ProduceSkill[nIndex].kControlGroup.Clear();
        m_ProduceSkill[nIndex].kControlGroup.AddControl( m_pID_LISTIMG_Skill[nIndex] );
        m_ProduceSkill[nIndex].kControlGroup.AddControl( m_pID_TEXT_SkillName[nIndex] );
        m_ProduceSkill[nIndex].kControlGroup.AddControl( m_pID_LIST_Npc[nIndex] );
        m_ProduceSkill[nIndex].kControlGroup.AddControl( m_pID_TEXT_SkillLvl[nIndex] );
        m_ProduceSkill[nIndex].kControlGroup.AddControl( m_pID_TEXT_SkillNum[nIndex] );
        m_ProduceSkill[nIndex].kControlGroup.AddControl( m_pID_PICTURE_SkillNum[nIndex] );
//		m_ProduceSkill[nIndex].kControlGroup.AddControl( m_pID_PROGRESS_SkillValue[nIndex] );
    }

    GetFrame()->SetFather( s_CUI_ID_FRAME_SKILL.GetFrame() );
    m_pID_FRAME_SkillProduce->SetMsgHoldup( false );

	for ( int idx = 0; idx < ICON_PERPAGE; ++idx )
	{
		m_pID_PROGRESS_SkillValue[idx]->SetValue( 0 );
		m_pID_PROGRESS_SkillValue[idx]->SetVisable( true );
	}

    SetVisable( false );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SkillProduce::_UnLoadUI()
{
    for( int i=0; i < ICON_PERPAGE; i++ )
    {
        m_ProduceSkill[i].kControlGroup.Clear();
    }

	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\SkillProduce.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SkillProduce::_IsVisable()
{
	if( !m_pID_FRAME_SkillProduce )
		return false;
	return m_pID_FRAME_SkillProduce->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SkillProduce::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_SkillProduce )
		return;

	m_pID_FRAME_SkillProduce->SetVisable( bVisable );
    if( bVisable )
    {
        if( !m_bInited )
        {
            m_bInited = true;
			m_ucPageNum = ( unsigned char )ZnCeil2Int( SKILL_PRODUCE_NUM * 1.0f / ICON_PERPAGE );
			m_ucCurPage = 0;
			ShowPage( m_ucCurPage );
        }
        Update();
    }
}

void CUI_ID_FRAME_SkillProduce::AddSkillToGroup( int nIndex, int iSkillId, int iSkillPointType )
{
    if( nIndex >= ICON_PERPAGE || nIndex < 0 )
        return;

    const IconManager::IconInfo*    pIcon = NULL;
    ControlIconDrag::S_ListImg      stItem;
    char                szLevel[MAX_PATH] = {0};
    char                szSkillPoint[MAX_PATH] = {0};
    std::string         format = "";
    ProduceSkillInfo*   pInfo = NULL;
    SCharSkill*         pCharSkill = NULL;
    NpcCoordInfo*       pNpcInfo = NULL;
    ControlList::S_List stNpcItem;
    const char*         NpcHyberLeft = "<";
    const char*         NpcHyberRight = ">";
    DWORD               dwSkillPoint = 0;             // 技能熟练度
    DWORD               dwSkillPointLimit = 0;

    m_ProduceSkill[nIndex].iSkillId = iSkillId;
    m_ProduceSkill[nIndex].kSkillPointType = iSkillPointType;

    if( iSkillId >= 0 )
    {
        pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( iSkillId );
        if( pCharSkill )
        {
            pIcon = IconManager::Get().GetIconInfo( iSkillId );
            if( pIcon )
            {
                // 构造技能Icon
                stItem.m_pkIconInfo->SetIconImageInfo( pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column );
                stItem.SetData( pIcon->itemId, pCharSkill->stSkillLevel, eIcon_Enable, true, eTipFlag_SkillWithNextLevel );
            }

            // 技能等级string
            MeSprintf_s( szLevel, sizeof( szLevel ) - 1, theXmlString.GetString( eText_SkillLevel ), pCharSkill->stSkillLevel );
            m_ProduceSkill[nIndex].usSkillLevel = pCharSkill->stSkillLevel;
        }
    }

	pInfo = gCfg.GetProduceSkillInfo( iSkillId );
	std::vector<UiCallbackDataBase*> CallBackDataArr;
    if( pInfo )
    {
        // 构造NPC描述
        pNpcInfo = (NpcCoordInfo *)NpcCoord::getInstance()->/*getNpcCoordInPrimaryMap*/getNpcCoord( pInfo->iLearnSkillNPCId );
        if (pNpcInfo)
        {
            char szText[MAX_PATH] = {0};
			MeSprintf_s( szText, sizeof(szText)-1, theXmlString.GetString(eText_ProduceSkillNpcDesc), pInfo->szSkillName, Common::_tstring::toNarrowString(pNpcInfo->_szName.c_str()).c_str() );
            format = szText;
			NpcCoord::getInstance()->addNpcHyberForText(format, NpcCoord::eMapId,-1,pNpcInfo->_nID,&CallBackDataArr,true);
//             NpcCoord::getInstance()->addNpcHyber(format, NpcHyberLeft, NpcHyberRight,&pNpcInfo);
//             FillMapPosTip(pNpcInfo,&stNpcItem);
            stNpcItem.SetData( format.c_str(), pInfo->iLearnSkillNPCId, NULL,  Color_Config.getColor( CC_TASK_NONE ) );
            stNpcItem.SetHyberOtherColor(Color_Config.getColor( ( ColorConfigure )( CC_PathFindLinker ) ) );
        }
        // 技能熟练度当前等级最大值
        if( pCharSkill )
            dwSkillPointLimit = pInfo->SkillPointLimit[pCharSkill->stSkillLevel-1];
    }
    // 熟练度
    if( iSkillPointType >= 0 )
    {
        dwSkillPoint = thePlayerRole.GetData( ( CPlayerRole::enUpdataType )iSkillPointType );
        MeSprintf_s( szSkillPoint, sizeof( szSkillPoint ) - 1, "%d / %d", dwSkillPoint, dwSkillPointLimit );
    }

    if( pCharSkill && pIcon )
    {
        // 技能Icon
        m_pID_LISTIMG_Skill[nIndex]->Clear();
        m_pID_LISTIMG_Skill[nIndex]->SetItem( &stItem, 0 );

        // 等级
        m_pID_TEXT_SkillLvl[nIndex]->SetText( szLevel );
    }
    else
    {
        m_pID_LISTIMG_Skill[nIndex]->Clear();
        m_pID_TEXT_SkillLvl[nIndex]->SetText( "" );
    }
    // 熟练度
    m_pID_TEXT_SkillNum[nIndex]->SetText( szSkillPoint );

	// 设置熟练度进度的进度值
	__int64 maxValue = m_pID_PROGRESS_SkillValue[nIndex]->GetMaxValue();
	m_pID_PROGRESS_SkillValue[nIndex]->SetValue( maxValue*dwSkillPoint/dwSkillPointLimit );

    if( pInfo )
    {
        // 技能名称
        m_pID_TEXT_SkillName[nIndex]->SetText( pInfo->szSkillName );

        // NPC描述
        if (pNpcInfo)
        {
            m_pID_LIST_Npc[nIndex]->Clear();
            m_pID_LIST_Npc[nIndex]->AddItem( &stNpcItem,&CallBackDataArr, false);
            m_pID_LIST_Npc[nIndex]->setShowTip( true );
            m_pID_LIST_Npc[nIndex]->HaveSelBar( false );	                    //没有绿色cur选中地图
            m_pID_LIST_Npc[nIndex]->SetCurSelIndex( -1 );
//             m_pID_LIST_Npc[nIndex]->SetHyberOtherClick( NPC_HyberOtherClick );
        }
    }
}

void CUI_ID_FRAME_SkillProduce::FillMapPosTip( const NpcCoordInfo* pNpcInfo,ControlList::S_List* pList )
{
	char cTip[256] = {0};
	if (pNpcInfo)
    {
        CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
        if (pTile)
        {
            MeSprintf_s(cTip, sizeof(cTip)-1, "%s(%d,%d)",pTile->GetTileName(),(int)pNpcInfo->_pfMapX,(int)pNpcInfo->_pfMapY);
        }
    }
    if (cTip[0] != '\0')
    {
        pList->setTip( cTip );
        pList->_bOnline = true;
    }
}

void CUI_ID_FRAME_SkillProduce::Refresh()
{
    ShowPage( m_ucCurPage );
    Update();
}

void CUI_ID_FRAME_SkillProduce::Update()
{
	if( !m_pID_FRAME_SkillProduce )
		return;

    // 显示精力和活力
    char szText[MAX_PATH] = {0};
    DWORD dwSkillPoint = thePlayerRole.GetData( ( CPlayerRole::enUpdataType )CPlayerRole::TYPE_ENERGY );
	DWORD dwSkillMaxPoint = thePlayerRole.GetData( ( CPlayerRole::enUpdataType )CPlayerRole::TYPE_ENERGY_MAX );

    MeSprintf_s( szText, sizeof( szText ) - 1, "%d/%d", dwSkillPoint, dwSkillMaxPoint );
    m_pID_TEXT_HuoLi->SetText( szText );

    char szLevel[MAX_PATH] = {0};
    char szSkillPoint[MAX_PATH] = {0};
    ProduceSkillInfo* pInfo = NULL;
    SCharSkill* pCharSkill = NULL;
    dwSkillPoint = 0;                     // 技能熟练度
    DWORD dwSkillPointLimit = 0;
    ControlIconDrag::S_ListImg stItem;
    const IconManager::IconInfo* pIcon = NULL;

    for( int nIndex = 0; nIndex < m_ucCurPageSkillNum; ++nIndex )
    {
        int iSkillId = m_ProduceSkill[nIndex].iSkillId;
        int iSkillPointType = m_ProduceSkill[nIndex].kSkillPointType;
        pIcon = NULL;

		m_ProduceSkill[nIndex].kControlGroup.SetVisible(false);
        if( iSkillId >= 0 )
        {
            pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( iSkillId );
            if( pCharSkill )
            {
				if (pCharSkill->stSkillLevel < 1)
				{
					continue;
				}
				m_ProduceSkill[nIndex].kControlGroup.SetVisible(true);
                // 技能等级string
                MeSprintf_s( szLevel, sizeof(szLevel)-1, theXmlString.GetString(eText_SkillLevel), pCharSkill->stSkillLevel );
                if( m_ProduceSkill[nIndex].usSkillLevel != pCharSkill->stSkillLevel )
                {
                    m_ProduceSkill[nIndex].usSkillLevel = pCharSkill->stSkillLevel;
                    pIcon = IconManager::Get().GetIconInfo(iSkillId);
                    if( pIcon )
                    {
                        // 构造技能Icon
                        stItem.m_pkIconInfo->SetIconImageInfo( pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column );
                        stItem.SetData( pIcon->itemId, pCharSkill->stSkillLevel, eIcon_Enable, true, eTipFlag_SkillWithNextLevel );
                    }
                }
            }
        }
        pInfo = gCfg.GetProduceSkillInfo( iSkillId );
        if( pInfo && pCharSkill )
        {
            // 技能熟练度当前等级最大值
            dwSkillPointLimit = pInfo->SkillPointLimit[pCharSkill->stSkillLevel-1];
        }
        // 熟练度
        if( iSkillPointType >= 0 )
        {
            dwSkillPoint = thePlayerRole.GetData( (CPlayerRole::enUpdataType)iSkillPointType );
            MeSprintf_s( szSkillPoint, sizeof( szSkillPoint ) - 1, "%d / %d", dwSkillPoint, dwSkillPointLimit );
        }

        if( pCharSkill )
        {
            m_pID_TEXT_SkillLvl[nIndex]->SetText( szLevel );
            m_pID_TEXT_SkillNum[nIndex]->SetText( szSkillPoint );

			// 熟练度
			m_pID_TEXT_SkillNum[nIndex]->SetText( szSkillPoint );

			// 设置熟练度进度的进度值
			__int64 maxValue = m_pID_PROGRESS_SkillValue[nIndex]->GetMaxValue();
			m_pID_PROGRESS_SkillValue[nIndex]->SetValue( maxValue*dwSkillPoint/dwSkillPointLimit );

            if( pIcon )
            {
                m_pID_LISTIMG_Skill[nIndex]->Clear();
                m_pID_LISTIMG_Skill[nIndex]->SetItem( &stItem, 0 );
            }
        }
    }
}

void CUI_ID_FRAME_SkillProduce::NPC_HyberOtherClick( ControlObject* pSender, const std::string& content ,int nId )
{
    int nMapId = -1;
    const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord( nId );

	if( pInfo && content == Common::_tstring::toNarrowString(pInfo->_szName.c_str()) )
    {
        nMapId = pInfo->_mapId;
    }

    if( false == NpcCoord::getInstance()->clickHyberToMiniMap( content.c_str(), nMapId ) )
    {
        CWorldTile* pCurrTile = CURRENTTILE;
        if( pCurrTile->GetMapId() != nMapId )
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, theXmlString.GetString( eText_CannotCrossMapPathFind ) );
        }
    }
}

void CUI_ID_FRAME_SkillProduce::OnIconClick( int nIconIndex )
{
    if( nIconIndex < 0 || nIconIndex >= ICON_PERPAGE + 1 )
        return;

    ShowRecipeById( m_ProduceSkill[nIconIndex].iSkillId );
}

void CUI_ID_FRAME_SkillProduce::ShowRecipeById( int nId )
{
    switch( nId )
    {
    case ItemDefine::eCSI_LianYao:
        if( s_CUI_ID_FRAME_Compound.IsVisable() )
            s_CUI_ID_FRAME_Compound.SetVisable( false );
        else
            s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_CaoYao );
        break;
    case ItemDefine::eCSI_ZhuBao:
        if( s_CUI_ID_FRAME_Compound.IsVisable() )
            s_CUI_ID_FRAME_Compound.SetVisable( false );
        else
            s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_ZhuBao );
        break;
    case ItemDefine::eCSI_DuanZao:
        if( s_CUI_ID_FRAME_Compound.IsVisable() )
            s_CUI_ID_FRAME_Compound.SetVisable( false );
        else
            s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_DuanZao );
        break;
    case ItemDefine::eCSI_ZhuJia:
        if( s_CUI_ID_FRAME_Compound.IsVisable() )
            s_CUI_ID_FRAME_Compound.SetVisable( false );
        else
            s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_ZhuJia );
        break;
    case ItemDefine::eCSI_GongYi:
        if( s_CUI_ID_FRAME_Compound.IsVisable() )
            s_CUI_ID_FRAME_Compound.SetVisable( false );
        else
            s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_GongYi );
        break;
    
    case ItemDefine::eCSI_XunMa:
        if( s_CUI_ID_FRAME_Compound.IsVisable() )
            s_CUI_ID_FRAME_Compound.SetVisable( false );
        else
            s_CUI_ID_FRAME_Compound.ShowByType( CPlayerRole::TYPE_XunMa );
        break;
	case ItemDefine::eCSI_CatchPet:
		{
		}
		break;
    }
}

void CUI_ID_FRAME_SkillProduce::RefreshPageButton()
{
    /*
 	m_pID_BUTTON_Back->SetEnable( true );
 	m_pID_BUTTON_Next->SetEnable( true );
 	if( m_ucCurPage == 0 )
 	{
 		m_pID_BUTTON_Back->SetEnable( false );
 	}
 	if( m_ucCurPage == m_ucPageNum - 1 )
 	{
 		m_pID_BUTTON_Next->SetEnable( false );
 	}
    */
}

void CUI_ID_FRAME_SkillProduce::ShowPage( int nPageNo )
{
    if( !IsUILoad() )
        return;

    int nSkillNum( 0 );
    SCharSkill* pCharSkill = NULL;

    // 更新控件信息     由于策划的商业技能 Id 不连续，故不能写成循环
    pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_LianYao );
    if( pCharSkill )
    {
        if( ( nSkillNum + 1 > nPageNo * ICON_PERPAGE ) && ( nSkillNum < ( nPageNo + 1 ) * ICON_PERPAGE ) )
            AddSkillToGroup( nSkillNum, ItemDefine::eCSI_LianYao, CPlayerRole::TYPE_CaoYao );

        nSkillNum++;
    }

	pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_DuanZao );
	if( pCharSkill )
	{
		if( ( nSkillNum + 1 > nPageNo * ICON_PERPAGE ) && ( nSkillNum < ( nPageNo + 1 ) * ICON_PERPAGE ) )
			AddSkillToGroup( nSkillNum, ItemDefine::eCSI_DuanZao, CPlayerRole::TYPE_DuanZao );

		nSkillNum++;
	}

   /* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_ZhuBao );
    if( pCharSkill )
    {
        if( ( nSkillNum + 1 > nPageNo * ICON_PERPAGE ) && ( nSkillNum < ( nPageNo + 1 ) * ICON_PERPAGE ) )
            AddSkillToGroup( nSkillNum, ItemDefine::eCSI_ZhuBao, CPlayerRole::TYPE_ZhuBao );

        nSkillNum++;
    }

    pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_ZhuJia );
    if( pCharSkill )
    {
        if( ( nSkillNum + 1 > nPageNo * ICON_PERPAGE ) && ( nSkillNum < ( nPageNo + 1 ) * ICON_PERPAGE ) )
            AddSkillToGroup( nSkillNum, ItemDefine::eCSI_ZhuJia, CPlayerRole::TYPE_ZhuJia );

        nSkillNum++;
    }

    pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_GongYi );
    if( pCharSkill )
    {
        if( ( nSkillNum + 1 > nPageNo * ICON_PERPAGE ) && ( nSkillNum < ( nPageNo + 1 ) * ICON_PERPAGE ) )
            AddSkillToGroup( nSkillNum, ItemDefine::eCSI_GongYi, CPlayerRole::TYPE_GongYi );

        nSkillNum++;
    }

    pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_XunMa );
    if( pCharSkill )
    {
        if( ( nSkillNum + 1 > nPageNo * ICON_PERPAGE ) && ( nSkillNum < ( nPageNo + 1 ) * ICON_PERPAGE ) )
            AddSkillToGroup( nSkillNum, ItemDefine::eCSI_XunMa, CPlayerRole::TYPE_XunMa );

        nSkillNum++;
    }

    pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_CaiYao );
    if( pCharSkill )
    {
        if( ( nSkillNum + 1 > nPageNo * ICON_PERPAGE ) && ( nSkillNum < ( nPageNo + 1 ) * ICON_PERPAGE ) )
            AddSkillToGroup( nSkillNum, ItemDefine::eCSI_CaiYao, CPlayerRole::TYPE_CaiYao );

        nSkillNum++;
    }

    pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_CaiKuang );
    if( pCharSkill )
    {
        if( ( nSkillNum + 1 > nPageNo * ICON_PERPAGE ) && ( nSkillNum < ( nPageNo + 1 ) * ICON_PERPAGE ) )
            AddSkillToGroup( nSkillNum, ItemDefine::eCSI_CaiKuang, CPlayerRole::TYPE_CaiKuang );

        nSkillNum++;
    }

    pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_BuChong );
    if( pCharSkill )
    {
        if( ( nSkillNum + 1 > nPageNo * ICON_PERPAGE ) && ( nSkillNum < ( nPageNo + 1 ) * ICON_PERPAGE ) )
            AddSkillToGroup( nSkillNum, ItemDefine::eCSI_BuChong, CPlayerRole::TYPE_BuChong );

        nSkillNum++;
    }*/
    m_ucCurPageSkillNum = nSkillNum;
    if( m_ucCurPageSkillNum > ICON_PERPAGE )
        m_ucCurPageSkillNum = ICON_PERPAGE;

	// 显示控件
	for( int i = 0; i < m_ucCurPageSkillNum; ++i )
	{
		m_ProduceSkill[i].kControlGroup.SetVisible( true );
	}
	for( int i = m_ucCurPageSkillNum; i < ICON_PERPAGE; ++i )
	{
		m_ProduceSkill[i].kControlGroup.SetVisible( false );
	}

	RefreshPageButton();
}

bool CUI_ID_FRAME_SkillProduce::IsRecipeSkillList( const ControlObject* pObject )
{
    if( !IsUILoad() )
        return false;

    for( int i = 0; i < ICON_PERPAGE; ++i )
    {
        if( m_pID_LISTIMG_Skill[i] == pObject )
            return true;
    }
    return false;
}
