/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\zhuomeng.hu\桌面\PetMore.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PetMore.h"
#include "PlayerRole.h"
#include "IconManagerClient.h"
#include "XmlStringLanguage.h"
#include "GameDefinePlayer.h"
#include "Skill.h"
#include "Pet.h"
#include "NetworkInput.h"
#include "ScreenInfoManager.h"

CUI_ID_FRAME_PetMore s_CUI_ID_FRAME_PetMore;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PetMore, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PetMore, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetMore, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetMore, ID_BUTTON_CLOSEOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_PetMore, ID_COMBOBOX_SelectPet1OnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_PetMore, ID_COMBOBOX_SelectPet2OnComboBoxChange )

CUI_ID_FRAME_PetMore::CUI_ID_FRAME_PetMore()
{
    m_pAnim1 = NULL;
    m_pAnim2 = NULL;
    m_nMountId1 = -1;
    m_nMountId2 = -1;
    ResetMembers();
}

void CUI_ID_FRAME_PetMore::ResetMembers()
{
    m_pID_FRAME_PetMore = NULL;
    m_pID_BUTTON_OK = NULL;
    m_pID_BUTTON_CLOSE = NULL;
    m_pID_PICTURE_Pet1 = NULL;
    m_pID_PICTURE_Pet2 = NULL;
    m_pID_COMBOBOX_SelectPet1 = NULL;
    m_pID_COMBOBOX_SelectPet2 = NULL;
    m_pID_TEXT_Result1 = NULL;
    m_pID_TEXT_Result2 = NULL;
    m_pID_TEXT_Level1 = NULL;
    m_pID_TEXT_Level2 = NULL;
    m_pID_TEXT_Generation1 = NULL;
    m_pID_TEXT_Generation2 = NULL;
    m_pID_TEXT_StrengthZ = NULL;
    m_pID_TEXT_AgilityZ = NULL;
    m_pID_TEXT_StaminaZ = NULL;
    m_pID_TEXT_IntellectZ = NULL;
    m_pID_TEXT_Strength = NULL;
    m_pID_TEXT_Agility = NULL;
    m_pID_TEXT_Stamina = NULL;
    m_pID_TEXT_Intellect = NULL;
    m_pID_TEXT_NeedMoney = NULL;
    m_pID_TEXT_CurrentMoney = NULL;
    m_pID_LISTIMG_Skill1 = NULL;
    m_pID_LISTIMG_Skill2 = NULL;
}

// Frame
bool CUI_ID_FRAME_PetMore::OnFrameRun()
{
    return true;
}
bool CUI_ID_FRAME_PetMore::OnFrameRender()
{
    if( !IsVisable() )
        return true;

    RenderViewport();

    return true;
}

void CUI_ID_FRAME_PetMore::RenderViewport()
{
    if( !IsVisable() )
        return;

    RECT rc1,rc2;
    m_pID_PICTURE_Pet1->GetRealRect( &rc1 );
    m_pID_PICTURE_Pet2->GetRealRect( &rc2 );
    //s_CUI_ID_FRAME_Pet.RenderMount( m_nMountId1, m_pAnim1, D3DX_PI / 2, rc1 );
    //s_CUI_ID_FRAME_Pet.RenderMount( m_nMountId2, m_pAnim2, D3DX_PI / 2, rc2 );
}

// Button
bool CUI_ID_FRAME_PetMore::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_PetMore )
        return false;

    // 发送交配消息
    int nMountLimitCnt = thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount;
    int iSelId1 = m_pID_COMBOBOX_SelectPet1->GetListBox().GetCurSelIndex();
    int iSelId2 = m_pID_COMBOBOX_SelectPet2->GetListBox().GetCurSelIndex();
    if( iSelId1 < 0 || iSelId2 < 0 || iSelId1 > nMountLimitCnt || iSelId2 > nMountLimitCnt || iSelId1 == iSelId2 )
        return true;
    SMountItem mount1 = thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId1];
    SMountItem mount2 = thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId2];
    
    ItemDefine::SDrome* pDrome1 = ( ItemDefine::SDrome* )GettheItemDetail().GetItemByID( mount1.baseInfo.id );
    ItemDefine::SDrome* pDrome2 = ( ItemDefine::SDrome* )GettheItemDetail().GetItemByID( mount2.baseInfo.id );
    if( !pDrome1 || !pDrome2 )
        return true;
    if( pDrome1->stType != pDrome2->stType )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountType_CannotBreed ) );
        return true;
    }
    if( !mount1.IsCanBreed() || !mount2.IsCanBreed() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBreed_Unable ) );
        return true;
    }
    
    MsgMountBreed msg;
    msg.masterGuid = mount1.baseInfo.guid;
    msg.assistantGuid = mount2.baseInfo.guid;
    GettheNetworkInput().SendMsg( &msg );

    return true;
}
// Button
bool CUI_ID_FRAME_PetMore::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
    return true;
}
// ComboBox
void CUI_ID_FRAME_PetMore::ID_COMBOBOX_SelectPet1OnComboBoxChange( ControlObject* pSender, const char* szData )
{
    if( !m_pID_FRAME_PetMore )
        return;

    int iSelId1 = m_pID_COMBOBOX_SelectPet1->GetListBox().GetCurSelIndex();
    int iSelId2 = m_pID_COMBOBOX_SelectPet2->GetListBox().GetCurSelIndex();
    if( iSelId2 > -1 && iSelId1 == iSelId2 )
    {
        m_pID_COMBOBOX_SelectPet1->GetListBox().SetCurSelIndex( -1 );
        m_pID_COMBOBOX_SelectPet1->GetEditInput().SetText( "" );
        m_nMountId1 = -1;
    }
    else if( iSelId1 > -1 && iSelId1 < thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount )
    {
        //s_CUI_ID_FRAME_Pet.ChangeModel( thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId1], m_pAnim1, m_nMountId1 );
    }

    Refresh();
}
// ComboBox
void CUI_ID_FRAME_PetMore::ID_COMBOBOX_SelectPet2OnComboBoxChange( ControlObject* pSender, const char* szData )
{
    if( !m_pID_FRAME_PetMore )
        return;
    
    int iSelId1 = m_pID_COMBOBOX_SelectPet1->GetListBox().GetCurSelIndex();
    int iSelId2 = m_pID_COMBOBOX_SelectPet2->GetListBox().GetCurSelIndex();
    if( iSelId1 > -1 && iSelId1 == iSelId2 )
    {
        m_pID_COMBOBOX_SelectPet2->GetListBox().SetCurSelIndex( -1 );
        m_pID_COMBOBOX_SelectPet2->GetEditInput().SetText( "" );
        m_nMountId2 = -1;
    }
    else if( iSelId2 > -1 && iSelId2 < thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount )
    {
       //s_CUI_ID_FRAME_Pet.ChangeModel( thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId2], m_pAnim2, m_nMountId2 );
    }

    Refresh();
}

// 装载UI
bool CUI_ID_FRAME_PetMore::_LoadUI()
{
    DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PetMore.MEUI", false, UI_Render_LayerThree );
    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[Data\\UI\\PetMore.MEUI]失败")
        return false;
    }
    return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PetMore::DoControlConnect()
{
    theUiManager.OnFrameRun( ID_FRAME_PetMore, s_CUI_ID_FRAME_PetMoreOnFrameRun );
    theUiManager.OnFrameRender( ID_FRAME_PetMore, s_CUI_ID_FRAME_PetMoreOnFrameRender );
    theUiManager.OnButtonClick( ID_FRAME_PetMore, ID_BUTTON_OK, s_CUI_ID_FRAME_PetMoreID_BUTTON_OKOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_PetMore, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_PetMoreID_BUTTON_CLOSEOnButtonClick );
    theUiManager.OnComboBoxChange( ID_FRAME_PetMore, ID_COMBOBOX_SelectPet1, s_CUI_ID_FRAME_PetMoreID_COMBOBOX_SelectPet1OnComboBoxChange );
    theUiManager.OnComboBoxChange( ID_FRAME_PetMore, ID_COMBOBOX_SelectPet2, s_CUI_ID_FRAME_PetMoreID_COMBOBOX_SelectPet2OnComboBoxChange );

    m_pID_FRAME_PetMore = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetMore );
    m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetMore, ID_BUTTON_OK );
    m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetMore, ID_BUTTON_CLOSE );
    m_pID_PICTURE_Pet1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetMore, ID_PICTURE_Pet1 );
    m_pID_PICTURE_Pet2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetMore, ID_PICTURE_Pet2 );
    m_pID_COMBOBOX_SelectPet1 = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_PetMore, ID_COMBOBOX_SelectPet1 );
    m_pID_COMBOBOX_SelectPet2 = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_PetMore, ID_COMBOBOX_SelectPet2 );
    m_pID_TEXT_Result1 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_Result1 );
    m_pID_TEXT_Result2 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_Result2 );
    m_pID_TEXT_Level1 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_Level1 );
    m_pID_TEXT_Level2 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_Level2 );
    m_pID_TEXT_Generation1 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_Generation1 );
    m_pID_TEXT_Generation2 = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_Generation2 );
    m_pID_TEXT_StrengthZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_StrengthZ );
    m_pID_TEXT_AgilityZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_AgilityZ );
    m_pID_TEXT_StaminaZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_StaminaZ );
    m_pID_TEXT_IntellectZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_IntellectZ );
    m_pID_TEXT_Strength = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_Strength );
    m_pID_TEXT_Agility = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_Agility );
    m_pID_TEXT_Stamina = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_Stamina );
    m_pID_TEXT_Intellect = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_Intellect );
    m_pID_TEXT_NeedMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_NeedMoney );
    m_pID_TEXT_CurrentMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PetMore, ID_TEXT_CurrentMoney );
    m_pID_LISTIMG_Skill1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetMore, ID_LISTIMG_Skill1 );
    m_pID_LISTIMG_Skill2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetMore, ID_LISTIMG_Skill2 );

    assert( m_pID_FRAME_PetMore );
    assert( m_pID_BUTTON_OK );
    assert( m_pID_BUTTON_CLOSE );
    assert( m_pID_PICTURE_Pet1 );
    assert( m_pID_PICTURE_Pet2 );
    assert( m_pID_COMBOBOX_SelectPet1 );
    assert( m_pID_COMBOBOX_SelectPet2 );
    assert( m_pID_TEXT_Result1 );
    assert( m_pID_TEXT_Result2 );
    assert( m_pID_TEXT_Level1 );
    assert( m_pID_TEXT_Level2 );
    assert( m_pID_TEXT_Generation1 );
    assert( m_pID_TEXT_Generation2 );
    assert( m_pID_TEXT_StrengthZ );
    assert( m_pID_TEXT_AgilityZ );
    assert( m_pID_TEXT_StaminaZ );
    assert( m_pID_TEXT_IntellectZ );
    assert( m_pID_TEXT_Strength );
    assert( m_pID_TEXT_Agility );
    assert( m_pID_TEXT_Stamina );
    assert( m_pID_TEXT_Intellect );
    assert( m_pID_TEXT_NeedMoney );
    assert( m_pID_TEXT_CurrentMoney );
    assert( m_pID_LISTIMG_Skill1 );
    assert( m_pID_LISTIMG_Skill2 );

    m_pID_LISTIMG_Skill1->SetDisableCanbePick( false );
    m_pID_LISTIMG_Skill2->SetDisableCanbePick( false );
    m_pID_LISTIMG_Skill1->ShowPressEffect( false );
    m_pID_LISTIMG_Skill2->ShowPressEffect( false );
    m_pID_FRAME_PetMore->SetOnVisibleChangedFun( OnVisibleChange );
    
    m_pAnim1 = MeNew CPlayerAnim;
    m_pAnim2 = MeNew CPlayerAnim;

    _SetVisable( false );
    return true;
}
// 卸载UI
bool CUI_ID_FRAME_PetMore::_UnLoadUI()
{
    if( m_pAnim1 )
    {
        m_pAnim1->Destroy();
        delete m_pAnim1;
        m_pAnim1 = NULL;
    }
    if( m_pAnim2 )
    {
        m_pAnim2->Destroy();
        delete m_pAnim2;
        m_pAnim2 = NULL;
    }
    ResetMembers();
    return theUiManager.RemoveFrame( "Data\\UI\\PetMore.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PetMore::_IsVisable()
{
    if( !m_pID_FRAME_PetMore )
        return false;

    return m_pID_FRAME_PetMore->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PetMore::_SetVisable( const bool bVisable )
{
    if( !m_pID_FRAME_PetMore )
        return;

    m_pID_FRAME_PetMore->SetVisable( bVisable );
}

void CUI_ID_FRAME_PetMore::OnVisibleChange( ControlObject* pUIObject )
{
    if( s_CUI_ID_FRAME_PetMore.IsVisable() )
    {
        s_CUI_ID_FRAME_PetMore.ResetControls();
    }
}

void CUI_ID_FRAME_PetMore::ResetControls()
{
    m_nMountId1 = -1;
    m_nMountId2 = -1;
    if( m_pID_FRAME_PetMore )
    {
        int nMountLimitCnt = thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount;
        m_pID_COMBOBOX_SelectPet1->GetListBox().Clear();
        m_pID_COMBOBOX_SelectPet2->GetListBox().Clear();
        for( int i = 0; i < nMountLimitCnt; ++i )
        {
            SMountItem::SBaseInfo mountInfo = thePlayerRole.m_charinfo.ItemBagData.miItems[i].baseInfo;
            if( mountInfo.id != InvalidLogicNumber )
            {
                ControlList::S_List	stItem;

                // 取颜色
                ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( mountInfo.id );
                if( !pCommon )
                    continue;
                DWORD dwColor = S_IconInfoHero::GetQualityColor( pCommon->ustLevel );
                stItem.SetData( mountInfo.szName, mountInfo.id, 0, dwColor );
                m_pID_COMBOBOX_SelectPet1->GetListBox().AddItem( &stItem,NULL, false );
                m_pID_COMBOBOX_SelectPet2->GetListBox().AddItem( &stItem,NULL, false );
            }
        }
        m_pID_COMBOBOX_SelectPet1->GetListBox().SetCurSelIndex( -1 );
        m_pID_COMBOBOX_SelectPet2->GetListBox().SetCurSelIndex( -1 );
        m_pID_COMBOBOX_SelectPet1->GetEditInput().SetText( "" );
        m_pID_COMBOBOX_SelectPet2->GetEditInput().SetText( "" );
    }
    Refresh();
}

void CUI_ID_FRAME_PetMore::RefreshMoney()
{
    if( !m_pID_FRAME_PetMore )
        return;

    // 所需和现有交子
    std::string strMoney;
    DWORD dwNeedJiaoZi = MOUNT_BREED_MONEY;
    thePlayerRole.GetGSCStringFromJiaoZi( dwNeedJiaoZi, strMoney );
    *m_pID_TEXT_NeedMoney = strMoney;

    strMoney = "";
    thePlayerRole.GetGSCStringFromCurrentJiaoZi( strMoney );
    *m_pID_TEXT_CurrentMoney = strMoney;
}

void CUI_ID_FRAME_PetMore::Refresh()
{
    if( !m_pID_FRAME_PetMore )
        return;

    int nMountLimitCnt = thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount;
    int iSelId1 = m_pID_COMBOBOX_SelectPet1->GetListBox().GetCurSelIndex();
    int iSelId2 = m_pID_COMBOBOX_SelectPet2->GetListBox().GetCurSelIndex();

    RefreshMoney();
	bool bCanBreed1 = false;
	bool bCanBreed2 = false;
    if( iSelId1 > -1 && iSelId1 < nMountLimitCnt )
    {
        // 主坐骑资质
        SMountItem mount = thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId1];
        SMountItem::SBaseInfo mountInfo1 = mount.baseInfo;
        *m_pID_TEXT_StrengthZ = mountInfo1.aptitudeAttribute[EBaseAttr_Strength];
        *m_pID_TEXT_AgilityZ = mountInfo1.aptitudeAttribute[EBaseAttr_Agility];
        *m_pID_TEXT_StaminaZ = mountInfo1.aptitudeAttribute[EBaseAttr_Stamina];
        *m_pID_TEXT_IntellectZ = mountInfo1.aptitudeAttribute[EBaseAttr_Intelligence];

        // 等级、辈分、能否繁殖
        *m_pID_TEXT_Level1 = mountInfo1.level;
        *m_pID_TEXT_Generation1 = theXmlString.GetString( eText_MountGeneration_First + mountInfo1.generation );
        *m_pID_TEXT_Result1 = theXmlString.GetString( eText_Mount_Mate_Unable + mount.IsCanBreed() );
		bCanBreed1 = mount.IsCanBreed();

        // 技能Icon
        m_pID_LISTIMG_Skill1->Clear();
        m_pID_LISTIMG_Skill2->Clear();
        m_pID_LISTIMG_Skill1->SetEnableCnt( mount.skillInfo.initiativeSkillNumber );
        CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.GetPage( CUISkillMgr::eMountSkill );
        if( pSkillTree )
        {
            SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
            for( int i = 0; i < SMountItem::MICD_MaxSkillCount; ++i )
            {
                unsigned short usSkillId = mount.skillInfo.skills[i].ustSkillID;
                if( usSkillId == 0 )
                    continue;
                unsigned short usLevel = mount.skillInfo.skills[i].stSkillLevel;
                ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID( usSkillId, usLevel );
                if( !pItemSkill )
                    continue;
                const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue( usSkillId );
                if( !pIcon )
                    continue;

                ControlIconDrag::S_ListImg stItem;
                stItem.m_pkIconInfo->SetIconImageInfo( pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column );
                stItem.SetData( usSkillId, usLevel, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
                stItem.SetFlags( CUISkillMgr::eMountSkill );

                switch( pItemSkill->sSkillCategory )
                {
                case ItemDefine::SCT_MountPassive:
                case ItemDefine::SCT_MountMasterInitiativeUnControl:
                    m_pID_LISTIMG_Skill2->SetItem( &stItem );
                    break;
                case ItemDefine::SCT_MountMasterInitiativeControl:
                    m_pID_LISTIMG_Skill1->SetItem( &stItem );
                    break;
                }
            }
        }
    }
    else
    {
        // 主坐骑默认值
        *m_pID_TEXT_StrengthZ = "";
        *m_pID_TEXT_AgilityZ = "";
        *m_pID_TEXT_StaminaZ = "";
        *m_pID_TEXT_IntellectZ = "";
        *m_pID_TEXT_Level1 = "";
        *m_pID_TEXT_Generation1 = "";
        *m_pID_TEXT_Result1 = "";
        m_pID_LISTIMG_Skill1->Clear();
        m_pID_LISTIMG_Skill2->Clear();
        m_pID_LISTIMG_Skill1->SetEnableCnt( SMountItem::MICD_PassiveSkillIndex );
    }

    if( iSelId2 > -1 && iSelId2 < nMountLimitCnt )
    {
        // 副坐骑属性
        SMountItem::SBaseInfo mountInfo2 = thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId2].baseInfo;
        *m_pID_TEXT_Strength = mountInfo2.baseAttribute[EBaseAttr_Strength];
        *m_pID_TEXT_Agility = mountInfo2.baseAttribute[EBaseAttr_Agility];
        *m_pID_TEXT_Stamina = mountInfo2.baseAttribute[EBaseAttr_Stamina];
        *m_pID_TEXT_Intellect = mountInfo2.baseAttribute[EBaseAttr_Intelligence];

        // 等级、辈分、能否繁殖
        *m_pID_TEXT_Level2 = mountInfo2.level;
        *m_pID_TEXT_Generation2 = theXmlString.GetString( eText_MountGeneration_First + mountInfo2.generation );
        *m_pID_TEXT_Result2 = theXmlString.GetString( eText_Mount_Mate_Unable + thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId2].IsCanBreed() );
		bCanBreed2 = thePlayerRole.m_charinfo.ItemBagData.miItems[iSelId2].IsCanBreed();
    }
    else
    {
        // 副坐骑默认值
        *m_pID_TEXT_Strength = "";
        *m_pID_TEXT_Agility = "";
        *m_pID_TEXT_Stamina = "";
        *m_pID_TEXT_Intellect = "";
        *m_pID_TEXT_Level2 = "";
        *m_pID_TEXT_Generation2 = "";
        *m_pID_TEXT_Result2 = "";
    }

	if (bCanBreed1 && bCanBreed2)
	{
		m_pID_BUTTON_OK->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_OK->SetEnable(false);
	}
}
