/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\zhuomeng.hu\桌面\ProduceLearn.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ProduceLearn.h"
#include "ItemDetail.h"
#include "Common.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "Skill.h"

CUI_ID_ProduceLearn s_CUI_ID_ProduceLearn;

MAP_FRAME_RUN( s_CUI_ID_ProduceLearn, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_ProduceLearn, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_ProduceLearn, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_ProduceLearn, ID_BUTTON_OKOnButtonClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_ProduceLearn, ID_LISTIMG_ProduceIconOnIconButtonClick )

CUI_ID_ProduceLearn::CUI_ID_ProduceLearn()
{
    m_nSkillId = 0;
    m_nSkillType = 0;
    m_nLearnLevel = 0;
    ResetMembers();
}

void CUI_ID_ProduceLearn::ResetMembers()
{
    m_pID_ProduceLearn = NULL;
    m_pID_TEXT_ProduceName = NULL;
    m_pID_BUTTON_CLOSE = NULL;
    m_pID_BUTTON_OK = NULL;
    m_pID_TEXT_ProduceLevel = NULL;
    m_pID_TEXT_ProduceDesc = NULL;
    m_pID_TEXT_NeedLevel = NULL;
    m_pID_TEXT_NeedNum = NULL;
    m_pID_TEXT_Money = NULL;
    m_pID_TEXT_Tip = NULL;
    m_pID_LISTIMG_ProduceIcon = NULL;
}

bool CUI_ID_ProduceLearn::OnFrameRun()
{
    return true;
}

bool CUI_ID_ProduceLearn::OnFrameRender()
{
    return true;
}

bool CUI_ID_ProduceLearn::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
    return true;
}

bool CUI_ID_ProduceLearn::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_ProduceLearn )
        return false;

    if( m_nLearnLevel == 1 )
    {
        MsgLearnSkill msg;
        msg.stSkillId = m_nSkillId;
        GettheNetworkInput().SendMsg( &msg );
    }
    else
    {
        MsgReqUpSkill msg;
        msg.stSkillId = m_nSkillId;
        GettheNetworkInput().SendMsg( &msg );
    }
    return true;
}

bool CUI_ID_ProduceLearn::ID_LISTIMG_ProduceIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )//zhuxincong 学习技能的图标的代码什么都没写 这....
{
    return false;
}

// 装载UI
bool CUI_ID_ProduceLearn::_LoadUI()
{
    DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ProduceLearn.MEUI", false, UI_Render_LayerThree );
    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[Data\\UI\\ProduceLearn.MEUI]失败")
        return false;
    }
    return DoControlConnect();
}
// 关连控件
bool CUI_ID_ProduceLearn::DoControlConnect()
{
    theUiManager.OnFrameRun( ID_ProduceLearn, s_CUI_ID_ProduceLearnOnFrameRun );
    theUiManager.OnFrameRender( ID_ProduceLearn, s_CUI_ID_ProduceLearnOnFrameRender );
    theUiManager.OnButtonClick( ID_ProduceLearn, ID_BUTTON_CLOSE, s_CUI_ID_ProduceLearnID_BUTTON_CLOSEOnButtonClick );
    theUiManager.OnButtonClick( ID_ProduceLearn, ID_BUTTON_OK, s_CUI_ID_ProduceLearnID_BUTTON_OKOnButtonClick );
    theUiManager.OnIconButtonClick( ID_ProduceLearn, ID_LISTIMG_ProduceIcon, s_CUI_ID_ProduceLearnID_LISTIMG_ProduceIconOnIconButtonClick );

    m_pID_ProduceLearn = (ControlFrame*)theUiManager.FindFrame( ID_ProduceLearn );
    m_pID_TEXT_ProduceName = (ControlText*)theUiManager.FindControl( ID_ProduceLearn, ID_TEXT_ProduceName );
    m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_ProduceLearn, ID_BUTTON_CLOSE );
    m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_ProduceLearn, ID_BUTTON_OK );
    m_pID_TEXT_ProduceLevel = (ControlText*)theUiManager.FindControl( ID_ProduceLearn, ID_TEXT_ProduceLevel );
    m_pID_TEXT_ProduceDesc = (ControlText*)theUiManager.FindControl( ID_ProduceLearn, ID_TEXT_ProduceDesc );
    m_pID_TEXT_NeedLevel = (ControlText*)theUiManager.FindControl( ID_ProduceLearn, ID_TEXT_NeedLevel );
    m_pID_TEXT_NeedNum = (ControlText*)theUiManager.FindControl( ID_ProduceLearn, ID_TEXT_NeedNum );
    m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_ProduceLearn, ID_TEXT_Money );
    m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_ProduceLearn, ID_TEXT_Tip );
    m_pID_LISTIMG_ProduceIcon = (ControlListImage*)theUiManager.FindControl( ID_ProduceLearn, ID_LISTIMG_ProduceIcon );

    assert( m_pID_ProduceLearn );
    assert( m_pID_TEXT_ProduceName );
    assert( m_pID_BUTTON_CLOSE );
    assert( m_pID_BUTTON_OK );
    assert( m_pID_TEXT_ProduceLevel );
    assert( m_pID_TEXT_ProduceDesc );
    assert( m_pID_TEXT_NeedLevel );
    assert( m_pID_TEXT_NeedNum );
    assert( m_pID_TEXT_Money );
    assert( m_pID_TEXT_Tip );
    assert( m_pID_LISTIMG_ProduceIcon );

    _SetVisable( false );
    return true;
}
// 卸载UI
bool CUI_ID_ProduceLearn::_UnLoadUI()
{
    ResetMembers();
    return theUiManager.RemoveFrame( "Data\\UI\\ProduceLearn.MEUI" );
}
// 是否可视
bool CUI_ID_ProduceLearn::_IsVisable()
{
    if( !m_pID_ProduceLearn )
        return false;

    return m_pID_ProduceLearn->IsVisable();
}
// 设置是否可视
void CUI_ID_ProduceLearn::_SetVisable( const bool bVisable )
{
    if( !m_pID_ProduceLearn )
        return;

    m_pID_ProduceLearn->SetVisable( bVisable );
}

void CUI_ID_ProduceLearn::ShowByType( int nRecipeType )
{
    m_nSkillId = 0;
    switch( nRecipeType )
    {
    case CPlayerRole::TYPE_CaoYao:           // 草药
        m_nSkillId = ItemDefine::eCSI_LianYao;
        break;
    case CPlayerRole::TYPE_ZhuBao:           // 珠宝
        m_nSkillId = ItemDefine::eCSI_ZhuBao;
        break;
    case CPlayerRole::TYPE_DuanZao:          // 锻造
        m_nSkillId = ItemDefine::eCSI_DuanZao;
        break;
    case CPlayerRole::TYPE_ZhuJia:           // 铸甲
        m_nSkillId = ItemDefine::eCSI_ZhuJia;
        break;
    case CPlayerRole::TYPE_GongYi:           // 工艺
        m_nSkillId = ItemDefine::eCSI_GongYi;
        break;
    case CPlayerRole::TYPE_XunMa:            // 驯马
        m_nSkillId = ItemDefine::eCSI_XunMa;
        break;
    case CPlayerRole::TYPE_CaiKuang:         // 采矿
        m_nSkillId = ItemDefine::eCSI_CaiKuang;
        break;
    case CPlayerRole::TYPE_CaiYao:           // 采药
        m_nSkillId = ItemDefine::eCSI_CaiYao;
        break;
    case CPlayerRole::TYPE_BuZhuo:           // 捕捉
        m_nSkillId = ItemDefine::eCSI_BuZhuo;
        break;
    case CPlayerRole::TYPE_BuChong:          // 捕虫
        m_nSkillId = ItemDefine::eCSI_BuChong;
        break;
    default:
        break;
    }

    if( !m_nSkillId )
        return;

    m_nSkillType = nRecipeType;
    if( !IsUILoad() )
        SetVisable( true );
    else
        _SetVisable( true );

    Refresh();
}

void CUI_ID_ProduceLearn::Refresh()
{
    if( !IsVisable() )
        return;

    if( !m_nSkillId )
        return;

    // 获取下一级信息，如果等级已满，则获取当前等级
    SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( m_nSkillId );
    int nNowLevel( 0 );
    m_nLearnLevel = 0;
    if( pCharSkill )
        nNowLevel = pCharSkill->stSkillLevel;
    int nLearnLevel( nNowLevel + 1 );
    ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID( m_nSkillId, nLearnLevel );
    if( !pItemSkill )
    {
        nLearnLevel = nNowLevel;
        if( nLearnLevel <= 0 )
            return;
        pItemSkill = GettheItemDetail().GetSkillByID( m_nSkillId, nNowLevel );
        if( !pItemSkill )
            return;
    }
    m_nLearnLevel = nLearnLevel;
    // 学习条件和当前条件
    int nNowExp = thePlayerRole.GetData( ( CPlayerRole::enUpdataType )m_nSkillType );
    int nNeedExp = pItemSkill->nLearnNeedExp;
    int nNowPlayerLevel = thePlayerRole.GetLevel();
    int nNeedPlayerLevel = pItemSkill->stLearnLevelReq;
    uint32 nNowMoney = thePlayerRole.m_charinfo.baseinfo.liveinfo.dwMoney + thePlayerRole.m_charinfo.baseinfo.liveinfo.jiaoZi;
    uint32 nNeedMoney = pItemSkill->stMoneyNeed;

    // 控件逻辑
        // 图标
    ControlIconDrag::S_ListImg stItem;
    SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet( m_nSkillId );
    if( iconSet )
    {
        stItem.m_pkIconInfo->SetIconImageInfo( iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column );
        stItem.SetData( m_nSkillId, 1, eIcon_Enable, false, eTipFlag_SkillNoNextLevel );
        stItem.SetFlags( CUISkillMgr::eProduce );
        m_pID_LISTIMG_ProduceIcon->SetItem( &stItem, 0 );
    }
    *m_pID_TEXT_ProduceName = pItemSkill->GetItemName();
    *m_pID_TEXT_ProduceLevel = nLearnLevel;

        // 学习条件
    m_pID_BUTTON_OK->SetEnable( true );
            // 描述
    if( nNowLevel == nLearnLevel )
    {
        m_pID_BUTTON_OK->SetEnable( false );
        *m_pID_TEXT_ProduceDesc = theXmlString.GetString( eText_CaoYao_Dcrb_MaxLevel + m_nSkillType - CPlayerRole::TYPE_CaoYao );
    }
    else
    {
        char szDescribe[MAX_PATH] = {0};
        MeSprintf_s( szDescribe, sizeof( szDescribe ) / sizeof( char ) - 1,
            theXmlString.GetString( eText_CaoYao_Describe + m_nSkillType - CPlayerRole::TYPE_CaoYao ), nLearnLevel );
        *m_pID_TEXT_ProduceDesc = szDescribe;
    }
            // 人物等级
    char szLevel[MAX_PATH] = {0};
    if( nNowPlayerLevel < nNeedPlayerLevel )
    {
        m_pID_BUTTON_OK->SetEnable( false );
        MeSprintf_s( szLevel, sizeof( szLevel ) / sizeof( char ) - 1, "{#FFFF0000=%d / %d#}{#FFFFFFFF=#}", nNowPlayerLevel, nNeedPlayerLevel );
    }
    else
    {
        MeSprintf_s( szLevel, sizeof( szLevel ) / sizeof( char ) - 1, "{#FF00FF00=%d / %d#}{#FFFFFFFF=#}", nNowPlayerLevel, nNeedPlayerLevel );
    }
    *m_pID_TEXT_NeedLevel = szLevel;
            // 熟练度
    char szExp[MAX_PATH] = {0};
    if( nNowExp < nNeedExp )
    {
        m_pID_BUTTON_OK->SetEnable( false );
        MeSprintf_s( szExp, sizeof( szExp ) / sizeof( char ) - 1, "{#FFFF0000=%d / %d#}{#FFFFFFFF=#}", nNowExp, nNeedExp );
    }
    else
    {
        MeSprintf_s( szExp, sizeof( szExp ) / sizeof( char ) - 1, "{#FF00FF00=%d / %d#}{#FFFFFFFF=#}", nNowExp, nNeedExp );
    }
    *m_pID_TEXT_NeedNum = szExp;
            // 金钱
    std::string strTmp;
    thePlayerRole.GetGSCStringFromJiaoZi( nNeedMoney, strTmp );
    *m_pID_TEXT_Money = strTmp;
    if( nNowMoney < nNeedMoney )
    {
        m_pID_BUTTON_OK->SetEnable( false );
        m_pID_TEXT_Tip->SetVisable( true );
    }
    else
    {
        m_pID_TEXT_Tip->SetVisable( false );
    }
}
