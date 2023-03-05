/********************************************************************
Created by UIEditor.exe
FileName: F:\work_hero\next\Program\trunk\Bin\Client\Data\Ui\Pet.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Pet.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "GameMain.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "baseProperty.h"
#include "Rename.h"
#include "Dxsdk/dinput.h"
#include "ui/PrivateShop.h"
#include "Me3d/ShaderManager.h"
#include "color_config.h"
#include "PrivateShop.h"
#include "Me3d/Engine/RendererDX.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/SwGlobal.h"
#include "wsRender.h"
#include "exmain.h"
#include "Main.h"
#include "ActionUI.h"
#include "wsCamera.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "WealthProtect.h"
#include "MessageBox.h"
#include "PetMore.h"            // 测试
#include "MainMenu.h"
#include "SoundConfig.h"
#include "SystemStallage.h"
#include "MountStrengthen.h"
#include "ui/MountMoveStar.h"
extern char* GetFullFileName(const char* filename);

extern short GetKeyboardInput( int iKey );

static bool UIPet_RightLBD(INT nX, INT nY)
{
    s_CUI_ID_FRAME_Pet.SetRotate(true);
    return true;
}

static bool UIPet_LeftLBD(INT nX, INT nY)
{
    s_CUI_ID_FRAME_Pet.SetRotate(true);
    return true;
}

bool LockMount( const char bPressYesButton, void *pData )
{
    if(bPressYesButton && pData)
    {
        MsgLockItemReq msg;
        ::CopyMemory(&msg,pData,sizeof(MsgLockItemReq));
        GettheNetworkInput().SendMsg( &msg );
    }
    return true;
}

bool UnLockMount( const char bPressYesButton, void *pData )
{
    if(bPressYesButton && pData)
    {
        MsgUnLockItemReq msg;
        ::CopyMemory(&msg,pData,sizeof(MsgUnLockItemReq));
        GettheNetworkInput().SendMsg( &msg );
    }
    return true;
}

bool PetUseSkill(ControlIconDrag::S_ListImg* pItem)
{
    if( !pItem )
        return false;

    switch (pItem->m_dwFlags)
    {
    case CUISkillMgr::eMountSkill:
        {
            SCharSkill *pSkill = NULL;
            pSkill = thePlayerRole.m_MountSkillBag.GetSkillByID( pItem->m_pkIconInfo->Id() );
            if ( !pSkill )
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_NotActived ) );
                return true;
            }

            theHeroGame.GetPlayerMgr()->SetCurUseSkill( pSkill->ustSkillID,
                pSkill->stSkillLevel );

            thePlayerRole.UpdateUI();
            theHeroGame.GetPlayerMgr()->OnSkill( FALSE );
        }break;
    case CUISkillMgr::eCommon:
        {
            s_CUI_ID_FRAME_ActionUI.SetCurFunction( pItem->m_pkIconInfo->Id() );
            s_CUI_ID_FRAME_ActionUI.UseFunction();
        }break;
    }
    return true;
}

void CUI_ID_FRAME_Pet::UpdateIconInfo()
{
    POINT pos;
    RECT rect;
    GetCursorPos(&pos);
    GetWindowRect(g_hWnd, &rect);

    if(!theHeroGame.IsFullScreen())
    {
        pos.x-=(rect.left + GetSystemMetrics(SM_CXBORDER));
        pos.y-=(rect.top + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXBORDER));
    }

    POINT ptMouseOnSel;
    if ( m_pID_LISTIMG_PetIcon->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
    {
        // 这里tip的位置取当前item的左边界
        // 这样就可以固定tip位置
        RECT rcItem;
        m_pID_LISTIMG_PetIcon->GetItemRect( pos.x, pos.y, rcItem );	
        // 偏移到中间
        rcItem.left += m_pID_LISTIMG_PetIcon->GetItemWidth() / 2;
        rcItem.top += m_pID_LISTIMG_PetIcon->GetItemHeight() / 2;

        bool bHaveCompare = false;
        ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetIcon->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );
        if( !pItem )
            return;

        int nSrcIndex = m_pID_LISTIMG_PetIcon->GetItemIndex( pItem );

        SCharItem stItem;
        SMountItem smItem = thePlayerRole.m_charinfo.ItemBagData.miItems[nSrcIndex];
        memset( &stItem, 0, sizeof(stItem) );
        stItem.itembaseinfo.ustItemID = smItem.baseInfo.id;
        stItem.itembaseinfo.nOnlyInt = smItem.baseInfo.guid;
        stItem.equipdata.usHP = -1;
        bool bEnable = pItem->m_eEnable;

        for( int i = 0 ; i < SCharItem::EConstDefine_BaseRandMaxCount; ++ i )
            stItem.equipdata.baseRands[i] = InvalidLogicNumber;
        for( int i = 0 ; i < SCharItem::EConstDefine_PurpleRandMaxCount; ++i )
            stItem.equipdata.purpleRands[i] = InvalidLogicNumber;

        ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
        if ( !pItemDetail )
        {
            return;
        }

        stItem.itembaseinfo.ustItemCount = 0;
		stItem.equipdata.ucLevel = smItem.baseInfo.level;


        stItem.SetLock(smItem.IsLock());
        stItem.SetUnLockTime(smItem.GetUnLockTime());
        stItem.SetUnLockLeftTime(smItem.GetUnLockLeftTime());

        pItem->SetData( &stItem, (bEnable ? eIcon_Enable : eIcon_Disable) );
    }
}

void CUI_ID_FRAME_Pet::RefreshIconInfo()
{
    if( !m_pID_FRAME_Pet )
        return;

    RefreshPetEnableList();

    for( int i = 0; i < thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount; ++i )
    {
        ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetIcon->GetItemByIndex( i );
        if( !pItem )
            continue;

        int nSrcIndex = m_pID_LISTIMG_PetIcon->GetItemIndex( pItem );
        if( nSrcIndex < 0 || nSrcIndex >= ITEM_MOUNT_MAXCOUNT )
            continue;

        SCharItem stItem;
        SMountItem smItem = thePlayerRole.m_charinfo.ItemBagData.miItems[nSrcIndex];
        memset( &stItem, 0, sizeof(stItem) );
        stItem.itembaseinfo.ustItemID = smItem.baseInfo.id;
        stItem.itembaseinfo.nOnlyInt = smItem.baseInfo.guid;
        stItem.equipdata.usHP = -1;
        bool bEnable = m_PetsEnable[nSrcIndex].bEnable;

        for( int i = 0 ; i < SCharItem::EConstDefine_BaseRandMaxCount; ++i )
            stItem.equipdata.baseRands[i] = InvalidLogicNumber;
        for( int i = 0 ; i < SCharItem::EConstDefine_PurpleRandMaxCount; ++i )
            stItem.equipdata.purpleRands[i] = InvalidLogicNumber;

        ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
        if ( !pItemDetail )
        {
            continue;
        }

        stItem.itembaseinfo.ustItemCount = 0;
		stItem.equipdata.ucLevel = smItem.baseInfo.level;

        stItem.SetLock( smItem.IsLock() );
        stItem.SetUnLockTime( smItem.GetUnLockTime() );
        stItem.SetUnLockLeftTime( smItem.GetUnLockLeftTime() );

        pItem->SetData( &stItem, ( bEnable ? eIcon_Enable : eIcon_Disable ) );
    }
    PetSelectChanged( m_pID_LIST_ShouLan->GetCurSelIndex() );
    m_pID_FRAME_Pet->SetRedraw();
}

CUI_ID_FRAME_Pet s_CUI_ID_FRAME_Pet;

MAP_FRAME_RUN( s_CUI_ID_FRAME_Pet, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Pet, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LIST_ShouLanOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LIST_WarOnListSelectChange )
MAP_LIST_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LIST_WarOnListLDBClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_XiuXiOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_ZhuDongOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_ZhuDongOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_ZhuDongOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_ZhuDongOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_FeedOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_PetIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_PetIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_PetIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_PetIconOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_QiChengOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_QiChengOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_QiChengOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_QiChengOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_ChuZhanOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_FangShengOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_LockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_UnLockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_GaiMingOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_RenewOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_ConfirmOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_BeiDongOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_BeiDongOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_BeiDongOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Pet, ID_LISTIMG_BeiDongOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_PlusLiLiangOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_SubtractLiLiangOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_PlusTiZhiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_PlusMinJieOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_PlusZhiLiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_SubtractTiZhiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_SubtractMinJieOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_SubtractZhiLiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_StrengthenOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Pet, ID_BUTTON_MountMoveStarOnButtonClick )

CUI_ID_FRAME_Pet::CUI_ID_FRAME_Pet()
{
    ResetMembers();
}

void CUI_ID_FRAME_Pet::ResetMembers()
{
    m_pID_FRAME_Pet = NULL;
    m_pID_TEXT_MJ = NULL;
    m_pID_TEXT_LL = NULL;
    m_pID_TEXT_TZ = NULL;
    m_pID_TEXT_SF = NULL;
    m_pID_TEXT_SYDJ = NULL;
    m_pID_TEXT_KLD = NULL;
    m_pID_TEXT_name = NULL;
    m_pID_TEXT_LLZZ = NULL;
    m_pID_TEXT_JRZZ = NULL;
    m_pID_TEXT_TZZZ = NULL;
    m_pID_TEXT_SFZZ = NULL;
    m_pID_LIST_ShouLan = NULL;
    m_pID_BUTTON_XiuXi = NULL;
    m_pID_TEXT_DJ = NULL;
    m_pID_PICTURE_Yingxiang = NULL;
    m_pID_LISTIMG_ZhuDong = NULL;
    m_pID_TEXT_Exp = NULL;
    m_pID_BUTTON_Right = NULL;
    m_pID_BUTTON_Left = NULL;
    m_pID_TEXT_TakeNum = NULL;
    m_pID_BUTTON_Feed = NULL;
    m_pID_LISTIMG_PetIcon = NULL;
    m_pID_LISTIMG_QiCheng = NULL;
    m_pID_TEXT_MountName = NULL;
    m_pID_BUTTON_ChuZhan = NULL;
    m_pID_BUTTON_FangSheng = NULL;
    m_pID_BUTTON_Lock = NULL;
    m_pID_BUTTON_UnLock = NULL;
    m_pID_LIST_War = NULL;
    m_pID_BUTTON_GaiMing = NULL;
    m_pID_BUTTON_Renew = NULL;
    m_pID_BUTTON_Confirm = NULL;
    m_pID_LISTIMG_BeiDong = NULL;
    m_pID_TEXT_Generation = NULL;
    m_pID_TEXT_Point = NULL;
    m_pID_BUTTON_PlusLiLiang = NULL;
    m_pID_BUTTON_SubtractLiLiang = NULL;
    m_pID_BUTTON_PlusTiZhi = NULL;
    m_pID_BUTTON_PlusMinJie = NULL;
    m_pID_BUTTON_PlusZhiLi = NULL;
    m_pID_BUTTON_SubtractTiZhi = NULL;
    m_pID_BUTTON_SubtractMinJie = NULL;
    m_pID_BUTTON_SubtractZhiLi = NULL;
    m_pID_TEXT_MountLv = NULL;
	m_pID_TEXT_PetSpeed = NULL;
	m_pID_TEXT_TransferTotal = NULL;
	m_pID_BUTTON_Strengthen = NULL;
	m_pID_BUTTON_MountMoveStar = NULL;
    InitActivePicState();
}

// Frame
bool CUI_ID_FRAME_Pet::OnFrameRun()
{
    int nScroollBarHeight = 0;
    if (s_CUI_ID_FRAME_Pet.IsVisable())
    {
        m_nLastHeight = m_pID_LIST_ShouLan->GetShowStartHeight();
        if (m_pID_LIST_ShouLan->GetScrollBar())
        {
            nScroollBarHeight = m_pID_LIST_ShouLan->GetScrollBar()->GetValue();
        }
    }

    if (s_CUI_ID_FRAME_Pet.IsVisable() && m_bNeedRefresh)
    {
        RefreshHelp(m_bSelectEnd);
        SetNeedRefresh(false);
    }

    if(s_CUI_ID_FRAME_Pet.IsVisable())
    {		
        int nSelId = m_pID_LIST_ShouLan->GetCurSelIndex();
        SMountItem& mount = thePlayerRole.GetMountByIndex(nSelId);

        bool bChuZhan = true;
        if( nSelId != -1 )
            bChuZhan = m_PetsEnable[nSelId].bEnable;

        m_pID_BUTTON_ChuZhan->SetEnable( ( /*!thePlayerRole.IsFighting() &&*/ m_pID_LIST_ShouLan->GetListItemCnt() > 0 ) && bChuZhan && m_bCanMount );

        if (m_bRotate && m_pID_BUTTON_Right->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
        {
			RenderAnim_RotateZ(true, 0.05);
            //m_fRotateZ += 1.5f * theHeroGame.GetFrameElapsedTime();
        }
        else if (m_bRotate && m_pID_BUTTON_Left->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
        {
			RenderAnim_RotateZ(false, 0.05);
            //m_fRotateZ -= 1.5f * theHeroGame.GetFrameElapsedTime();
        }
        else
            m_bRotate = false;
        UpdateIconInfo();
        SetStateByCoolDownTime(&mount);
        m_pID_LISTIMG_PetIcon->SetShowStartHeight(m_nLastHeight);
        m_pID_LIST_War->SetShowStartHeight(m_nLastHeight);
        m_pID_LIST_ShouLan->SetShowStartHeight(m_nLastHeight);
        m_pID_LIST_ShouLan->SetScrollValue(nScroollBarHeight);

		//lyh++
		if (thePlayerRole.GetMountCount() <= m_pID_LIST_ShouLan->m_nHeight/m_pID_LIST_ShouLan->GetListItemHeight())
		{
			m_pID_LISTIMG_PetIcon->SetShowStartHeight(0);
			m_pID_LIST_War->SetShowStartHeight(0);
			m_pID_LIST_ShouLan->SetShowStartHeight(0);
			m_pID_LIST_ShouLan->SetScrollValue(nScroollBarHeight);
		}

    }
    return true;
}

bool CUI_ID_FRAME_Pet::OnFrameRender()
{
    if (m_pID_LIST_ShouLan->GetListItemCnt() > 0)
    {
		RECT rc;
		m_pID_PICTURE_Yingxiang->GetRealRect(&rc);
		RenderAnim_Update(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, D3DXVECTOR3(0, -6, 0));
		RenderAnim(D3DXVECTOR3(0, -2, -1.2), Config::m_fMdlSpaceScale * 1.0);
    }
    return true;
}

// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_ChuZhanOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Pet )
        return false;
	if (s_CUI_ID_FRAME_MountStrengthen.IsVisable())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
		return false;
	}
    ActivePet(m_pID_LIST_ShouLan->GetCurSelIndex());
    return true;
}

//--------------------------------------------------------------------------------------
// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_LockOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Pet )
        return false;
	if (s_CUI_ID_FRAME_MountStrengthen.IsVisable())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
		return false;
	}

    MsgLockItemReq msg;
    int selIndex = m_pID_LIST_ShouLan->GetCurSelIndex();
    msg.ustItemIndex = selIndex;
    msg.nGuID = thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].baseInfo.guid;
    msg.uchBagType = BT_MountBag;

    s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_MountLockedContext), theXmlString.GetString(eText_MountLockedContext),//是否确定加锁
        CUI_ID_FRAME_MessageBox::eTypeYesNo, false ,
        LockMount, &msg, sizeof(MsgLockItemReq));
    return true;
}

// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_UnLockOnButtonClick(ControlObject* pSender)
{
    if( !m_pID_FRAME_Pet )
        return false;
	if (s_CUI_ID_FRAME_MountStrengthen.IsVisable())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
		return false;
	}

    MsgUnLockItemReq msg;
    int selIndex = m_pID_LIST_ShouLan->GetCurSelIndex();
    msg.ustItemIndex = selIndex;
    msg.nGuID = thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].baseInfo.guid;
    msg.uchBagType = BT_MountBag;

    s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_ItemUnLockedContext), theXmlString.GetString(eText_ItemUnLockedContext),//是否确定解锁
        CUI_ID_FRAME_MessageBox::eTypeYesNo, false ,
        UnLockMount, &msg, sizeof(MsgUnLockItemReq));
    return true;
}
// 
//------------------------------------------------------------------------------------------------
// Button
//重新分配
bool CUI_ID_FRAME_Pet::ID_BUTTON_RenewOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Pet )
        return false;
    SMountItem& rfMount = GetCurrentMount();

    if (rfMount.baseInfo.id != InvalidLogicNumber)
    {
        int sum = 0;
        for ( int i=0; i < EBaseAttr_MaxSize; ++i)
        { 
            float temp = rfMount.baseInfo.baseAttribute[i] + /*rfMount.baseInfo.level-1 +*/ rfMount.baseInfo.potentialAttribute[i];
            sum += rfMount.baseInfo.currentAttribute[i] - temp;
            rfMount.baseInfo.currentAttribute[i] = temp;
        }
        rfMount.baseInfo.nPotentialPoint += sum; 
        UpdataProperty();
    }
    return true;
}

// Button
//确定
const float theta = 0.001;
bool CUI_ID_FRAME_Pet::ID_BUTTON_ConfirmOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Pet )
        return false;
    SMountItem& rfMount = GetCurrentMount();
    if (rfMount.baseInfo.id != InvalidLogicNumber)
    {
        MsgMountPotential msg;
        double value[EBaseAttr_MaxSize];
        for (int i = 0; i < EBaseAttr_MaxSize; ++i)
        {
            value[i] = 0;
        }
        msg.guid = rfMount.baseInfo.guid;
        msg.index = m_pID_LIST_ShouLan->GetCurSelIndex();
        for (int i=0; i < EBaseAttr_MaxSize; ++i)
        { 
            value[i] = rfMount.baseInfo.currentAttribute[i] - (rfMount.baseInfo.baseAttribute[i] + /*rfMount.baseInfo.level - 1 + */rfMount.baseInfo.potentialAttribute[i]);
            //rfMount.baseInfo.potentialAttribute[i] = rfMount.baseInfo.currentAttribute[i] - (rfMount.baseInfo.baseAttribute[i] + rfMount.baseInfo.level - 1);
        }

        for (int i = 0; i < EBaseAttr_MaxSize; ++i)
        {
            msg.value[i] = value[i] + 0.5;
        }

        for (int i=0; i < EBaseAttr_MaxSize; ++i)
        {
            if (msg.value[i] != 0)
            {
                GettheNetworkInput().SendMsg(&msg);
                break;
            }
        }

    }

    if (rfMount.baseInfo.nPotentialPoint > 0)
    {
        SetArrayEnable(true);	
    }
    else
    {
        SetArrayEnable(false);	
    }

    return true;
}

//---------------------------------------------------------------
SMountItem& CUI_ID_FRAME_Pet::GetCurrentMount()
{
    int nIndex( ITEM_MOUNT_MAXCOUNT );
    if( IsUILoad() )
        nIndex = m_pID_LIST_ShouLan->GetCurSelIndex();
    return thePlayerRole.GetMountByIndex(nIndex);
}

//------------------------------------------------------------------
const int pointPerOneTime = 1;
bool CUI_ID_FRAME_Pet::AddPoint( EBaseAttr eKeyType)
{
    if (eKeyType < 0 || eKeyType >  EBaseAttr_MaxSize)
    {
        return false;
    }

    if( !m_pID_FRAME_Pet )
    {
        return false;
    }

    SMountItem& rfMount = GetCurrentMount();
    if (rfMount.baseInfo.id != InvalidLogicNumber)
    {
        if (rfMount.baseInfo.nPotentialPoint >= pointPerOneTime)
        {
            rfMount.baseInfo.nPotentialPoint -= pointPerOneTime;
            rfMount.baseInfo.currentAttribute[eKeyType] += pointPerOneTime;
        }
        UpdataProperty();

    }
    return true;
}

bool CUI_ID_FRAME_Pet::SubtractPoint(EBaseAttr eKeyType)
{
    if (eKeyType < 0 || eKeyType >  EBaseAttr_MaxSize)
    {
        return false;
    }

    if( !m_pID_FRAME_Pet )
    {
        return false;
    }

    SMountItem& rfMount = GetCurrentMount();
    if (rfMount.baseInfo.id != InvalidLogicNumber)
    {
        float temp = rfMount.baseInfo.baseAttribute[eKeyType] + /*rfMount.baseInfo.level-1 +*/ rfMount.baseInfo.potentialAttribute[eKeyType];
        if (rfMount.baseInfo.currentAttribute[eKeyType] - temp >= pointPerOneTime)
        {
            rfMount.baseInfo.nPotentialPoint += pointPerOneTime;
            rfMount.baseInfo.currentAttribute[eKeyType] -= pointPerOneTime;
        }
        UpdataProperty();
    }
    return true;
}

void SetIntText(ControlText* pText, float v)
{
    pText->SetText(v);
}

//-----------------------------------------------------------------------------------------------
void CUI_ID_FRAME_Pet::UpdataProperty()
{
    if( !IsUILoad() )
        return;

    SMountItem& rfMount = GetCurrentMount();
    if (rfMount.baseInfo.id != InvalidLogicNumber)
    {
        SetIntText(m_pID_TEXT_LL, rfMount.baseInfo.currentAttribute[EBaseAttr_Strength]);	    // 力量
        SetIntText(m_pID_TEXT_MJ, rfMount.baseInfo.currentAttribute[EBaseAttr_Agility]);		// 敏捷
        SetIntText(m_pID_TEXT_TZ, rfMount.baseInfo.currentAttribute[EBaseAttr_Stamina]);		// 体质
        SetIntText(m_pID_TEXT_SF, rfMount.baseInfo.currentAttribute[EBaseAttr_Intelligence]);		// 术法
        SetIntText(m_pID_TEXT_Point, rfMount.baseInfo.nPotentialPoint);
    }
}
// 
//--------------------------------------------------------------------------------------------------
// Button
//+力量
bool CUI_ID_FRAME_Pet::ID_BUTTON_PlusLiLiangOnButtonClick( ControlObject* pSender )
{
    return AddPoint(EBaseAttr_Strength);
}

// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_PlusMinJieOnButtonClick( ControlObject* pSender )
{
    return AddPoint(EBaseAttr_Agility);
}

// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_PlusTiZhiOnButtonClick( ControlObject* pSender )
{
    return AddPoint(EBaseAttr_Stamina);
}

// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_PlusZhiLiOnButtonClick( ControlObject* pSender )
{
    return AddPoint(EBaseAttr_Intelligence);
}

//--------------------------------------------------------------------------------------------
// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_SubtractLiLiangOnButtonClick( ControlObject* pSender )
{
    return SubtractPoint(EBaseAttr_Strength);
}

// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_SubtractTiZhiOnButtonClick( ControlObject* pSender )
{
    return SubtractPoint(EBaseAttr_Stamina);
}

// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_SubtractMinJieOnButtonClick( ControlObject* pSender )
{
    return SubtractPoint(EBaseAttr_Agility);
}

// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_SubtractZhiLiOnButtonClick( ControlObject* pSender )
{
    return SubtractPoint(EBaseAttr_Intelligence);
}

void CUI_ID_FRAME_Pet::SetLockAndUnLockState()
{

}
void CUI_ID_FRAME_Pet::ID_LIST_WarOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Pet || !m_pID_LIST_War || m_pID_LIST_War->GetCurSelIndex() == -1)
        return;
	m_pID_LIST_War->SetCurSelIndex(-1);
}
void CUI_ID_FRAME_Pet::ID_LIST_ShouLanOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
    if( !m_pID_FRAME_Pet )
        return;
    SetLockAndUnLockState();

    PetSelectChanged(m_pID_LIST_ShouLan->GetCurSelIndex());

    int selIndex = m_pID_LIST_ShouLan->GetCurSelIndex();

    if(s_CUI_ID_FRAME_PACK.GetLockItem())
    {
        if (thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].baseInfo.id != InvalidLogicNumber)
        {
            if(thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].IsLock()&&!thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].GetUnLockTime())
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString(eText_MountHasLocked) );
                s_CUI_ID_FRAME_PACK.SetLockItem(false);
                m_pID_BUTTON_Lock->SetVisable(false);
                m_pID_BUTTON_UnLock->SetVisable(true);
                return;
            }
        }

        MsgLockItemReq msg;
        msg.ustItemIndex = selIndex;
        msg.nGuID = thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].baseInfo.guid;
        msg.uchBagType = BT_MountBag;

        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_MountLockedContext), theXmlString.GetString(eText_MountLockedContext),//是否确定加锁
            CUI_ID_FRAME_MessageBox::eTypeYesNo, false ,
            LockMount, &msg, sizeof(MsgLockItemReq));

        s_CUI_ID_FRAME_PACK.SetLockItem(false);
    }
    else if(s_CUI_ID_FRAME_PACK.GetUnLockItem())
    {
        if (thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].baseInfo.id != InvalidLogicNumber)
        {
            if(!thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].IsLock())
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString(eText_MountHasNotLocked) );
                s_CUI_ID_FRAME_PACK.SetLockItem(false);
                m_pID_BUTTON_Lock->SetVisable(true);
                m_pID_BUTTON_UnLock->SetVisable(false);
                return;
            }
            else if(thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].GetUnLockTime())
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString(eText_MountCannotUnlock) );
                s_CUI_ID_FRAME_PACK.SetLockItem(false);
                return;
            }
        }

        MsgUnLockItemReq msg;
        msg.ustItemIndex = selIndex;
        msg.nGuID = thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].baseInfo.guid;
        msg.uchBagType = BT_MountBag;

        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_ItemUnLockedContext), theXmlString.GetString(eText_ItemUnLockedContext),//是否确定解锁
            CUI_ID_FRAME_MessageBox::eTypeYesNo, false ,
            UnLockMount, &msg, sizeof(MsgUnLockItemReq));

        s_CUI_ID_FRAME_PACK.SetUnLockItem(false);
    }
}
// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_XiuXiOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Pet )
        return false;
	/*if (s_CUI_ID_FRAME_MountStrengthen.IsVisable())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
		return false;
	}*/
    ActivePet(m_pID_LIST_ShouLan->GetCurSelIndex());
    return true;
}
// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_FangShengOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Pet )
        return false;
	if (s_CUI_ID_FRAME_MountStrengthen.IsVisable())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
		return false;
	}
    // 安全保护
    SMountItem& mount = thePlayerRole.GetMountByIndex(m_pID_LIST_ShouLan->GetCurSelIndex());
    if (mount.baseInfo.id != InvalidLogicNumber)
    {
        if(mount.IsLock())
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString(eText_MountLockedSetFree) );
            return false;
        }
    }

    if( !CWealthProtect::Instance().IsInProtectTime() )
        DiscardPet(m_pID_LIST_ShouLan->GetCurSelIndex());
    return true;
}

//--------------------------------------------------------------------------------------------------------------------
// ListImg / ListEx
bool CUI_ID_FRAME_Pet::ID_LISTIMG_ZhuDongOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                      ControlIconDrag::S_ListImg* pItemDrag,
                                                      ControlIconDrag::S_ListImg* pItemSrc )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return false;
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_ZhuDongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return false;
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_ZhuDongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return PetUseSkill(pItem);
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_ZhuDongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return PetUseSkill(pItem);
}

//--------------------------------------------------------------------------------------------------------------------
// ListImg / ListEx
bool CUI_ID_FRAME_Pet::ID_LISTIMG_BeiDongOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                      ControlIconDrag::S_ListImg* pItemDrag,
                                                      ControlIconDrag::S_ListImg* pItemSrc )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return false;
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_BeiDongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return false;
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_BeiDongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return false;
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_BeiDongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return false;
}
void CUI_ID_FRAME_Pet::ID_LIST_WarOnListLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Pet || !m_pID_LIST_War || m_pID_LIST_War->GetCurSelIndex() == -1)
        return;
	m_pID_LIST_War->SetCurSelIndex(-1);
}
// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_GaiMingOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Pet )
        return false;
    s_CUI_ID_FRAME_Rename.SetType(CUI_ID_FRAME_Rename::eChangeHorse);
    s_CUI_ID_FRAME_Rename.SetVisable(true);
    return true;
}
short CUI_ID_FRAME_Pet::GetCurrentMountIndex()
{
    if( !m_pID_FRAME_Pet )
        return -1;
    return m_pID_LIST_ShouLan->GetCurSelIndex();	
}
// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_FeedOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Pet )
        return false;

    // 判断是否已经满生命值，不喂了
    if( thePlayerRole.GetActivedMount() &&
        ( thePlayerRole.GetActivedMount()->baseInfo.hp == thePlayerRole.GetActivedMount()->baseInfo.hpMax ) )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Mount_Error, theXmlString.GetString( eText_Mount_FeedError_FullHP ) );		
        return false;
    }
  s_CUI_ID_FRAME_PACK.UseMountRestoreItem();
	//UsePetHp(CItemDetail::EMRIF_RestoreHP);
    return true;
}


void CUI_ID_FRAME_Pet::UsePetHp(unsigned char ucValue)
{
	int nCount = thePlayerRole.m_bag.GetItemCount();
	int nId = 0;
	int nIdex = -1;
	for (int i = 0;i < nCount ; ++i)
	{
		SCharItem sItem;
		if (!thePlayerRole.m_bag.GetItem(i,&sItem))
		{
			continue;
		}

		if (s_CUI_ID_FRAME_PACK.IsGrassID(sItem.itembaseinfo.ustItemID))
		{

			ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(sItem.itembaseinfo.ustItemID);
			if (!pItemCommon)
			{
				continue;
			}

			if (pItemCommon->ucItemType != ItemDefine::ITEMTYPE_RESTORE)
			{
				continue;
			}

			ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore*)pItemCommon;
			if(pRestore->specialFunction !=ucValue)
			{
				continue;
			}

			MsgUseGoodsToMount msg;
			msg.nMountIndex = thePlayerRole.GetActivedMountIndex();
			if (msg.nMountIndex != -1)
			{
				msg.nGuid = sItem.itembaseinfo.nOnlyInt;
				msg.ustItemIndex = i;
				msg.stSrcChar = 0;
				msg.stDstChar = 0;
				msg.ucItemBagType = BT_NormalItemBag;
				GettheNetworkInput().SendMsg( &msg );
			}
			break;
		}

	}
}


bool CUI_ID_FRAME_Pet::ID_LISTIMG_PetIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                      ControlIconDrag::S_ListImg* pItemDrag,
                                                      ControlIconDrag::S_ListImg* pItemSrc )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return false;
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_PetIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return false;
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_PetIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;

    int n = m_pID_LISTIMG_PetIcon->GetItemIndex( m_pID_LISTIMG_PetIcon->GetCurSelItem() );
    m_pID_LIST_ShouLan->SetCurSelIndex( n );
    ID_LIST_ShouLanOnListSelectChange( NULL, NULL );

    return false;
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_PetIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;

    if( pItem && pItem->m_eEnable == eIcon_Disable )
        return false;

    if( s_CUI_ID_FRAME_PrivateShop.IsVisable() )
    {
        int nNullIndex = s_CUI_ID_FRAME_PrivateShop.PetList_GetNullItem();
        if( nNullIndex == -1 )
            return false;

        s_CUI_ID_FRAME_PrivateShop.ID_LISTIMG_PetListOnIconDragOn( m_pID_LISTIMG_PetIcon, 0, pItem,
            s_CUI_ID_FRAME_PrivateShop.PetList_GetItemByIndex( nNullIndex ) );
        return true;
    }
    else if( s_CUI_ID_FRAME_Bargaining.IsVisable() )
    {
        int nNullIndex = s_CUI_ID_FRAME_Bargaining.PetList_GetNullItem();
        if( nNullIndex == -1 )
            return false;

        s_CUI_ID_FRAME_Bargaining.ID_LISTIMG_MyPetOnIconDragOn( m_pID_LISTIMG_PetIcon, 0, pItem,
            s_CUI_ID_FRAME_Bargaining.GetLISTIMG_MyPetItem( nNullIndex ) );
        return true;
    }
	else if (s_CUI_ID_FRAME_MountStrengthen.IsVisable())
	{
		s_CUI_ID_FRAME_MountStrengthen.ID_LISTIMG_MountOnIconDragOn(m_pID_LISTIMG_PetIcon, 0, pItem, 0);
		return true;
	}
	else if(s_CUI_ID_FRAME_MountMoveStar.IsVisable())
	{
		//设置坐骑上移星
		s_CUI_ID_FRAME_MountMoveStar.SetMount(pItem);
		return true;
	}

    return false;
}
bool CUI_ID_FRAME_Pet::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Pet )
        return false;
    m_bRotate = false;
    return true;
}
// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Pet )
        return false;
    m_bRotate = false;
    return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Pet::ID_LISTIMG_QiChengOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                      ControlIconDrag::S_ListImg* pItemDrag,
                                                      ControlIconDrag::S_ListImg* pItemSrc )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return false;
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_QiChengOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return false;
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_QiChengOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return PetUseSkill(pItem);
}
bool CUI_ID_FRAME_Pet::ID_LISTIMG_QiChengOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet )
        return false;
    return PetUseSkill(pItem);
}

// 装载UI
bool CUI_ID_FRAME_Pet::_LoadUI()
{
    DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Pet.MEUI", false, UI_Render_LayerThree );
    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[Data\\UI\\Pet.MEUI]失败")
            return false;
    }
    return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Pet::DoControlConnect()
{
    theUiManager.OnFrameRun( ID_FRAME_Pet, s_CUI_ID_FRAME_PetOnFrameRun );
    theUiManager.OnFrameRender( ID_FRAME_Pet, s_CUI_ID_FRAME_PetOnFrameRender);
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_ChuZhan, s_CUI_ID_FRAME_PetID_BUTTON_ChuZhanOnButtonClick );
    theUiManager.OnListSelectChange( ID_FRAME_Pet, ID_LIST_ShouLan, s_CUI_ID_FRAME_PetID_LIST_ShouLanOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Pet, ID_LIST_War, s_CUI_ID_FRAME_PetID_LIST_WarOnListSelectChange);
	theUiManager.OnListLDBClick( ID_FRAME_Pet, ID_LIST_War, s_CUI_ID_FRAME_PetID_LIST_WarOnListLDBClick );
	
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_XiuXi, s_CUI_ID_FRAME_PetID_BUTTON_XiuXiOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_FangSheng, s_CUI_ID_FRAME_PetID_BUTTON_FangShengOnButtonClick );
    theUiManager.OnIconDragOn( ID_FRAME_Pet, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_PetID_LISTIMG_ZhuDongOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_Pet, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_PetID_LISTIMG_ZhuDongOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_Pet, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_PetID_LISTIMG_ZhuDongOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_Pet, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_PetID_LISTIMG_ZhuDongOnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_Pet, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_PetID_LISTIMG_BeiDongOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_Pet, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_PetID_LISTIMG_BeiDongOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_Pet, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_PetID_LISTIMG_BeiDongOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_Pet, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_PetID_LISTIMG_BeiDongOnIconRButtonUp );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_GaiMing, s_CUI_ID_FRAME_PetID_BUTTON_GaiMingOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_Right, s_CUI_ID_FRAME_PetID_BUTTON_RightOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_Left, s_CUI_ID_FRAME_PetID_BUTTON_LeftOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_Feed, s_CUI_ID_FRAME_PetID_BUTTON_FeedOnButtonClick );
    theUiManager.OnIconDragOn( ID_FRAME_Pet, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_PetID_LISTIMG_PetIconOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_Pet, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_PetID_LISTIMG_PetIconOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_Pet, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_PetID_LISTIMG_PetIconOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_Pet, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_PetID_LISTIMG_PetIconOnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_Pet, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_PetID_LISTIMG_QiChengOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_Pet, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_PetID_LISTIMG_QiChengOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_Pet, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_PetID_LISTIMG_QiChengOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_Pet, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_PetID_LISTIMG_QiChengOnIconRButtonUp );

    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_PlusLiLiang, s_CUI_ID_FRAME_PetID_BUTTON_PlusLiLiangOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_PlusTiZhi, s_CUI_ID_FRAME_PetID_BUTTON_PlusTiZhiOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_PlusMinJie, s_CUI_ID_FRAME_PetID_BUTTON_PlusMinJieOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_PlusZhiLi, s_CUI_ID_FRAME_PetID_BUTTON_PlusZhiLiOnButtonClick );

    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_SubtractLiLiang, s_CUI_ID_FRAME_PetID_BUTTON_SubtractLiLiangOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_SubtractTiZhi, s_CUI_ID_FRAME_PetID_BUTTON_SubtractTiZhiOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_SubtractMinJie, s_CUI_ID_FRAME_PetID_BUTTON_SubtractMinJieOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_SubtractZhiLi, s_CUI_ID_FRAME_PetID_BUTTON_SubtractZhiLiOnButtonClick );

    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_Renew, s_CUI_ID_FRAME_PetID_BUTTON_RenewOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_Confirm, s_CUI_ID_FRAME_PetID_BUTTON_ConfirmOnButtonClick );

    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_UnLock, s_CUI_ID_FRAME_PetID_BUTTON_UnLockOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_Lock, s_CUI_ID_FRAME_PetID_BUTTON_LockOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_Strengthen, s_CUI_ID_FRAME_PetID_BUTTON_StrengthenOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Pet, ID_BUTTON_MountMoveStar, s_CUI_ID_FRAME_PetID_BUTTON_MountMoveStarOnButtonClick );

    m_pID_FRAME_Pet = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Pet );
    m_pID_BUTTON_ChuZhan = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_ChuZhan );
    m_pID_TEXT_MJ = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_MJ );
    m_pID_TEXT_LL = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_LL );
    m_pID_TEXT_TZ = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_TZ );
    m_pID_TEXT_SF = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_SF );
    m_pID_TEXT_DJ = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_DJ );
    m_pID_TEXT_KLD = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_KLD );
    m_pID_TEXT_name = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_name );
    m_pID_TEXT_LLZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_LLZZ );
    m_pID_TEXT_JRZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_JRZZ );
    m_pID_TEXT_TZZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_TZZZ );
    m_pID_TEXT_SFZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_SFZZ );
    m_pID_TEXT_Point = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_Point );
    m_pID_TEXT_Generation = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_Generation );
    m_pID_LIST_ShouLan = (ControlList*)theUiManager.FindControl( ID_FRAME_Pet, ID_LIST_ShouLan );
    m_pID_BUTTON_XiuXi = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_XiuXi );
    m_pID_TEXT_SYDJ = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_SYDJ );
    m_pID_BUTTON_FangSheng = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_FangSheng );
    m_pID_PICTURE_Yingxiang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Pet, ID_PICTURE_Yingxiang );
    m_pID_LISTIMG_ZhuDong = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Pet, ID_LISTIMG_ZhuDong );
    m_pID_LISTIMG_BeiDong = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Pet, ID_LISTIMG_BeiDong );
    m_pID_TEXT_Exp = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_Exp );
    m_pID_BUTTON_GaiMing = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_GaiMing );
    m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_Right );
    m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_Left );
    m_pID_BUTTON_Feed = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_Feed );

    m_pID_BUTTON_PlusLiLiang = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_PlusLiLiang );
    m_pID_BUTTON_SubtractLiLiang = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_SubtractLiLiang );
    m_pID_BUTTON_PlusTiZhi = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_PlusTiZhi );
    m_pID_BUTTON_SubtractTiZhi = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_SubtractTiZhi );
    m_pID_BUTTON_PlusMinJie = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_PlusMinJie );
    m_pID_BUTTON_SubtractMinJie = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_SubtractMinJie );
    m_pID_BUTTON_PlusZhiLi = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_PlusZhiLi );
    m_pID_BUTTON_SubtractZhiLi = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_SubtractZhiLi );
    m_pID_LIST_War = (ControlList*)theUiManager.FindControl( ID_FRAME_Pet, ID_LIST_War );
    m_pID_BUTTON_Confirm = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_Confirm );
    m_pID_BUTTON_Renew = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_Renew );

    m_pID_BUTTON_UnLock = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_UnLock);
    m_pID_BUTTON_Lock = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_Lock);	

    m_pID_TEXT_TakeNum = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_TakeNum );

    m_pID_LISTIMG_PetIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Pet, ID_LISTIMG_PetIcon );
    m_pID_LISTIMG_QiCheng = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Pet, ID_LISTIMG_QiCheng );

    m_pID_TEXT_MountName = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_MountName );

    m_pID_TEXT_MountLv = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_MountLv );
	m_pID_TEXT_PetSpeed = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_PetSpeed );

	m_pID_TEXT_TransferTotal = (ControlText*)theUiManager.FindControl( ID_FRAME_Pet, ID_TEXT_TransferTotal );
	m_pID_BUTTON_Strengthen = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_Strengthen );

	m_pID_BUTTON_MountMoveStar = (ControlButton*)theUiManager.FindControl( ID_FRAME_Pet, ID_BUTTON_MountMoveStar );

    assert( m_pID_TEXT_SYDJ );
    assert( m_pID_TEXT_MountLv );
	assert( m_pID_TEXT_PetSpeed );
	assert( m_pID_TEXT_TransferTotal );
	assert( m_pID_BUTTON_Strengthen );

    m_pID_BUTTON_ChuZhan->SetVisable(true);
    m_pID_BUTTON_XiuXi->SetVisable(false);

    m_pID_LISTIMG_ZhuDong->SetDisableCanbePick(true);
    m_pID_LISTIMG_ZhuDong->ShowPressEffect(true);

    m_pID_LISTIMG_BeiDong->SetDisableCanbePick(true);
    m_pID_LISTIMG_BeiDong->ShowPressEffect(true);

    m_pID_LISTIMG_QiCheng->SetDisableCanbePick(true);
    m_pID_LISTIMG_QiCheng->ShowPressEffect(true);

    m_pID_LISTIMG_PetIcon->SetShowCursorOnFrameOnNULLItem(false);

    m_pID_BUTTON_Right->SetLButtonDownFun(UIPet_RightLBD);
    m_pID_BUTTON_Left->SetLButtonDownFun(UIPet_LeftLBD);

    m_bCanMount = true;
    memset( m_PetsEnable, 0, sizeof( PetEnable ) * ITEM_MOUNT_MAXCOUNT );
    for( int i = 0 ; i < ITEM_MOUNT_MAXCOUNT ; ++ i )
    {
        m_PetsEnable[i].bEnable = true;
    }

    m_pID_LISTIMG_ZhuDong->SetEnableCnt( 0 );
	/*
    m_pPlayerAnim = MeNew CPlayerAnim;
	m_pPlayer = MeNew CPlayer;
	m_pPlayer->SetAnim( m_pPlayerAnim );
	m_pPlayerAnim->SetPlayer( m_pPlayer );
	theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayer );
	*/
	RenderAnim_Create(CUIRenderAnim::RTWUI_MOUNT, -4.61);

    SetButtonGroup();
	m_pID_LIST_War->SetSkipAllMsg(true);
    _SetVisable( false );
    return true;
}

void CUI_ID_FRAME_Pet::SetButtonGroup()
{
    m_arrayButton[0] = m_pID_BUTTON_PlusLiLiang;
    m_arrayButton[1] = m_pID_BUTTON_SubtractLiLiang;
    m_arrayButton[2] = m_pID_BUTTON_PlusTiZhi;
    m_arrayButton[3] = m_pID_BUTTON_SubtractTiZhi;
    m_arrayButton[4] = m_pID_BUTTON_PlusMinJie;
    m_arrayButton[5] = m_pID_BUTTON_SubtractMinJie;
    m_arrayButton[6] = m_pID_BUTTON_PlusZhiLi;
    m_arrayButton[7] = m_pID_BUTTON_SubtractZhiLi;

    SetArrayEnable(false);
}

void CUI_ID_FRAME_Pet::SetArrayEnable(bool bEnable)
{
    for (int i = 0; i <= 7; ++i)
    {
        if (!m_arrayButton[i])
        {
            break;
        }
        m_arrayButton[i]->SetEnable(bEnable);
    }

    if (m_pID_BUTTON_Confirm)
    {
        m_pID_BUTTON_Confirm->SetEnable(bEnable);
    }

    if (m_pID_BUTTON_Renew)
    {
        m_pID_BUTTON_Renew->SetEnable(bEnable);
    }
}

// 卸载UI
bool CUI_ID_FRAME_Pet::_UnLoadUI()
{
    ResetMembers();
	RenderAnim_Destroy();
    return theUiManager.RemoveFrame( "Data\\UI\\Pet.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Pet::_IsVisable()
{
    if( !m_pID_FRAME_Pet )
        return false;
    return m_pID_FRAME_Pet->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Pet::_SetVisable( const bool bVisable )
{
    if( !m_pID_FRAME_Pet )
        return;
	if (bVisable)
	{
		ID_BUTTON_RenewOnButtonClick(NULL);
	}
    m_pID_FRAME_Pet->SetVisable( bVisable );
    m_fRotateZ = D3DX_PI / 2;
    m_nModelId = -1;

    if (bVisable)
        Refresh();

    if (bVisable)
    {
        s_CUI_ID_FRAME_MainMenu.SetNeedSpark(false, CUI_ID_FRAME_MainMenu::ekey_pet);
    }
    if( bVisable )
    {
        PlaySoundConfig( SoundConfig::EST_OpenPetUI );
    }
}

void CUI_ID_FRAME_Pet::RefreshEnable( int nIndex, bool bEnable )
{
    if( !m_pID_FRAME_Pet )
        return;
    if( nIndex >= 0 && nIndex < ITEM_MOUNT_MAXCOUNT )
        m_PetsEnable[nIndex].bEnable = bEnable;
    // 更新ui
    if( m_pID_LISTIMG_PetIcon->GetItemByIndex( nIndex ) )
        m_pID_LISTIMG_PetIcon->GetItemByIndex( nIndex )->m_eEnable = (eIconDrawState)bEnable;
    int nSelId = m_pID_LIST_ShouLan->GetCurSelIndex();
    if( nSelId == nIndex )
    {
        m_pID_BUTTON_ChuZhan->SetEnable(bEnable);
        m_pID_BUTTON_XiuXi->SetEnable(bEnable);
        m_pID_BUTTON_FangSheng->SetEnable(bEnable);
        m_pID_BUTTON_GaiMing->SetEnable(bEnable);
        m_pID_BUTTON_Feed->SetEnable(bEnable);
        m_pID_BUTTON_Lock->SetEnable(bEnable);
        m_pID_BUTTON_UnLock->SetEnable(bEnable);
    }

}

void CUI_ID_FRAME_Pet::RefreshPetEnableList()
{
    // 更新enable列表，确保与当前list对应,如果不对应设置为enable
    for( int i = 0 ; i < ITEM_MOUNT_MAXCOUNT ; ++ i )
    {
        bool bFound = false;		
        for( int j = 0 ; j < thePlayerRole.GetCharInfo2().baseinfo.liveinfo.ucMountCount; ++ j )
        {
            if( thePlayerRole.GetCharInfo2().ItemBagData.miItems[j].baseInfo.guid == m_PetsEnable[i].guid && 
                thePlayerRole.GetCharInfo2().ItemBagData.miItems[j].baseInfo.guid != 0 )			
            {
                bFound = true;				
                m_PetsEnable[j].guid = thePlayerRole.GetCharInfo2().ItemBagData.miItems[j].baseInfo.guid;
                m_PetsEnable[j].bEnable = ( !IsMountInPrivateShop( m_PetsEnable[j].guid ) && !IsMountInBargaining( m_PetsEnable[j].guid ) );
                break;
            }

        }
        if( !bFound )
        {
            m_PetsEnable[i].guid = thePlayerRole.GetCharInfo2().ItemBagData.miItems[i].baseInfo.guid;
            m_PetsEnable[i].bEnable = true;
        }		
    }
}

int CUI_ID_FRAME_Pet::GetMountIndexByGuid( __int64 guid )
{
    for (int i = 0; i < thePlayerRole.GetCharInfo2().baseinfo.liveinfo.ucMountCount; ++i)
    {
        if ( thePlayerRole.GetCharInfo2().ItemBagData.miItems[i].baseInfo.guid == guid )
        {
            return i;
        }
    }
    return -1;
}

void CUI_ID_FRAME_Pet::Refresh(bool bSelectEnd)
{
    SetNeedRefresh(true);
    m_bSelectEnd = bSelectEnd;
}

void CUI_ID_FRAME_Pet::SetNeedRefresh(bool bNeed)
{
    m_bNeedRefresh = bNeed;
}

void CUI_ID_FRAME_Pet::RefreshHelp(bool bSelectEnd)
{
    if (!IsVisable())
        return;

    int nSelId = m_pID_LIST_ShouLan->GetCurSelIndex();

    m_pID_LIST_ShouLan->Clear();
    m_pID_LISTIMG_PetIcon->Clear();
    m_pID_PICTURE_Yingxiang->SetVisable(false);
    m_pID_PICTURE_Yingxiang->SetPicName("");

    m_pActivedPet = 0;
    int nActivePetIndex = -1;

    for (int i = 0; i < thePlayerRole.GetCharInfo2().baseinfo.liveinfo.ucMountCount; ++i)
    {
        if (thePlayerRole.GetCharInfo2().ItemBagData.miItems[i].baseInfo.id != InvalidLogicNumber)
        {
            ControlList::S_List sData;

            // 取颜色
            ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( thePlayerRole.GetCharInfo2().ItemBagData.miItems[i].baseInfo.id );
            if( !pCommon )
                continue;
            DWORD dwColor = S_IconInfoHero::GetQualityColor( thePlayerRole.m_charinfo.ItemBagData.miItems[i].baseInfo.quality );
            sData.SetData( thePlayerRole.GetCharInfo2().ItemBagData.miItems[i].baseInfo.szName, 
                thePlayerRole.GetCharInfo2().ItemBagData.miItems[i].baseInfo.id, 
                0, 
                dwColor );
            m_pID_LIST_ShouLan->AddItem(&sData,NULL, false);

            // 添加icon到控件
            ControlListImage::S_ListImg stItemImage;
            stItemImage.SetData( thePlayerRole.GetCharInfo2().ItemBagData.miItems[i].baseInfo.id, 1 );
            ((SCharItem*)stItemImage.m_pkIconInfo->GetData())->itembaseinfo.nOnlyInt = thePlayerRole.GetCharInfo2().ItemBagData.miItems[i].baseInfo.guid;

            m_pID_LISTIMG_PetIcon->SetItem( &stItemImage, i );

            if (thePlayerRole.GetCharInfo2().ItemBagData.miItems[i].baseInfo.isActive)
            {
                m_pActivedPet = &thePlayerRole.GetCharInfo2().ItemBagData.miItems[i];
                nActivePetIndex = i;				
            }
        }
    }

    char buf[64];
    sprintf(buf, "%d/%d", thePlayerRole.GetMountCount(), thePlayerRole.GetCharInfo2().baseinfo.liveinfo.ucMountCount);
    m_pID_TEXT_TakeNum->SetText(buf);

    RefreshFightState(nActivePetIndex);

    if (bSelectEnd)
        m_pID_LIST_ShouLan->SetCurSelIndex(m_pID_LIST_ShouLan->GetListItemCnt() - 1);
    else if (nSelId == -1)
        m_pID_LIST_ShouLan->SetCurSelIndex(0);
    else
        m_pID_LIST_ShouLan->SetCurSelIndex(nSelId);
	     
    RefreshIconInfo();
}

void SetFloatText(ControlText* pText, float v)
{
    char szTemp[32];
    sprintf( szTemp, "%.2f", v );
    pText->SetText(szTemp);
}

void CUI_ID_FRAME_Pet::PetSelectChanged(int nIndex)
{
    SetArrayEnable(false);
    m_pID_TEXT_DJ->SetText("");		// 等级
    m_pID_TEXT_SYDJ->SetText("");	// 携带等级
    m_pID_TEXT_KLD->SetText("");	// 快乐度
    m_pID_TEXT_LL->SetText("");		// 力量
    m_pID_TEXT_MJ->SetText("");		// 敏捷
    m_pID_TEXT_TZ->SetText("");		// 体质
    m_pID_TEXT_SF->SetText("");		// 术法
    m_pID_TEXT_LLZZ->SetText("");	// 力量资质
    m_pID_TEXT_JRZZ->SetText("");	// 敏捷资质
    m_pID_TEXT_TZZZ->SetText("");	// 体质资质
    m_pID_TEXT_SFZZ->SetText("");	// 术法资质
    m_pID_TEXT_name->SetText("");	// 名字
    m_pID_TEXT_Point->SetText("");	// 潜力点
    m_pID_TEXT_Generation->SetText(""); // 辈分

    m_pID_TEXT_MountLv->SetText("");	// 设置携带等级

    m_pID_TEXT_Exp->SetText("");	// 经验
	m_pID_TEXT_PetSpeed->SetText("");//速度
	m_pID_TEXT_TransferTotal->SetText("");//转化

    m_pID_LISTIMG_ZhuDong->Clear();
    m_pID_LISTIMG_BeiDong->Clear();
    m_pID_LISTIMG_QiCheng->Clear();

    m_pID_BUTTON_Lock->SetEnable(false);
    m_pID_BUTTON_UnLock->SetEnable(false);

    m_pID_BUTTON_ChuZhan->SetEnable(false);
    m_pID_BUTTON_XiuXi->SetEnable(false);
    m_pID_BUTTON_FangSheng->SetEnable(false);
    m_pID_BUTTON_GaiMing->SetEnable(false);
    m_pID_BUTTON_Feed->SetEnable( false );

    m_pID_TEXT_MountName->SetText(""); // 宠物原始名称

    if (nIndex < 0)
        return;

    SMountItem& mount = thePlayerRole.GetMountByIndex(nIndex);
    if (mount.baseInfo.id != InvalidLogicNumber)
    {
        if( m_PetsEnable[nIndex].bEnable )
        {
            m_pID_BUTTON_ChuZhan->SetEnable(true);
            m_pID_BUTTON_XiuXi->SetEnable(true);
            m_pID_BUTTON_GaiMing->SetEnable(true);
            m_pID_BUTTON_Feed->SetEnable( true );
            m_pID_BUTTON_UnLock->SetEnable(true);
            m_pID_BUTTON_Lock->SetEnable(true);
            m_pID_BUTTON_FangSheng->SetEnable( !mount.baseInfo.isActive );
        }
        m_pID_BUTTON_ChuZhan->SetVisable( !mount.baseInfo.isActive );
        m_pID_BUTTON_XiuXi->SetVisable( mount.baseInfo.isActive );

        if( mount.xLockInfo.bIsLocked )
        {
            m_pID_BUTTON_Lock->SetVisable( false );
            m_pID_BUTTON_UnLock->SetVisable( true );
            m_pID_BUTTON_FangSheng->SetEnable( false );
            if( mount.xLockInfo.nUnLockLeftTime > 0 )
            {
                m_pID_BUTTON_UnLock->SetEnable( false );
            }
        }
        else
        {
            m_pID_BUTTON_Lock->SetVisable( true );
            m_pID_BUTTON_UnLock->SetVisable( false );
        }

        m_pID_TEXT_DJ->SetText(mount.baseInfo.level);									// 等级

        ItemDefine::SDrome* pTDrome = GettheItemDetail().GetDromeByID( mount.baseInfo.id );

        if( pTDrome )
        {
            m_pID_TEXT_MountLv->SetText( pTDrome->takeLevel );							// 设置携带等级
        }

        char buf[64];
        sprintf( buf, "%d/%d", mount.baseInfo.hp, mount.baseInfo.hpMax );
        m_pID_TEXT_KLD->SetText(buf);													// 快乐度

        SetIntText(m_pID_TEXT_LL,     mount.baseInfo.currentAttribute[EBaseAttr_Strength]);	    // 力量
        SetIntText(m_pID_TEXT_MJ,     mount.baseInfo.currentAttribute[EBaseAttr_Agility]);		// 敏捷
        SetIntText(m_pID_TEXT_TZ,     mount.baseInfo.currentAttribute[EBaseAttr_Stamina]);		// 耐力
        SetIntText(m_pID_TEXT_SF,     mount.baseInfo.currentAttribute[EBaseAttr_Intelligence]);		// 术法

        //SetIntText(m_pID_TEXT_LLZZ,   mount.baseInfo.aptitudeAttribute[EBaseAttr_Strength]);	// 力量资质
        //SetIntText(m_pID_TEXT_JRZZ,   mount.baseInfo.aptitudeAttribute[EBaseAttr_Agility]);		// 敏捷资质
        //SetIntText(m_pID_TEXT_TZZZ,   mount.baseInfo.aptitudeAttribute[EBaseAttr_Stamina]);		// 耐力
        //SetIntText(m_pID_TEXT_SFZZ,   mount.baseInfo.aptitudeAttribute[EBaseAttr_Intelligence]);		// 术法资质
        //SetIntText(m_pID_TEXT_Point,   mount.baseInfo.nPotentialPoint);		// 潜力点
		/*SetIntText(m_pID_TEXT_TransferTotal, mount.baseInfo.aptitudeAttribute[EBaseAttr_Strength]
		+ mount.baseInfo.aptitudeAttribute[EBaseAttr_Agility] + mount.baseInfo.aptitudeAttribute[EBaseAttr_Stamina]
		+ mount.baseInfo.aptitudeAttribute[EBaseAttr_Intelligence]);*/
		char szTransTemp[24]={0};
		sprintf_s(szTransTemp,sizeof(szTransTemp),"%.0f%%",mount.baseInfo.aptitudeAttribute[EBaseAttr_Strength]);
		m_pID_TEXT_TransferTotal->SetText(szTransTemp);
        if (mount.baseInfo.nPotentialPoint > 0)
        {
            //SetArrayEnable(true);
        }

        m_pID_TEXT_name->SetText(mount.baseInfo.szName);
        m_pID_TEXT_Generation->SetText( theXmlString.GetString( eText_MountGeneration_First + mount.baseInfo.generation ) );

        // 经验
        __int64 dwTotalExp = theExpStage.GetMountLevelupExp(mount.baseInfo.level );
        __int64 dwLastLevelExp = 0;
        if (mount.baseInfo.level > 1)
        {
            dwLastLevelExp = theExpStage.GetMountLevelupExp(mount.baseInfo.level - 1);
        }
        char szWord[MAX_PATH] = {0};
        MeSprintf_s( szWord, sizeof(szWord)/sizeof(char) - 1, "%I64u/%I64u", mount.baseInfo.exp - dwLastLevelExp, dwTotalExp - dwLastLevelExp );
        //m_pID_TEXT_Exp->SetText( szWord );
		m_pID_TEXT_Exp->SetText("");

        DWORD dwColor = 0;
        ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( mount.baseInfo.id );
        if( pCommon )
        {
            dwColor = S_IconInfoHero::GetQualityColor( mount.baseInfo.quality );
        }

        ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( mount.baseInfo.id );
        if (pDrome)
        {
            DWORD dwDJColor = 0x00ffffff;
            if( pDrome->takeLevel > thePlayerRole.GetLevel() )
            {
                dwDJColor = 0xff0000;
                m_bCanMount = false;
            }
            else
                m_bCanMount = true;

            m_pID_TEXT_SYDJ->SetText(pDrome->takeLevel, dwDJColor);
            m_pID_TEXT_MountName->SetText(pDrome->GetName(), dwColor); // 宠物原始名称

			RenderAnim_SetModelID(pDrome->modelID[mount.baseInfo.level]);
        }

		//宠物速度改为百分比显示
		char szSpeedTemp[24]={0};
		float fBaseSpeed = (thePlayerRole.GetBaseSpeed()>0.000001? thePlayerRole.GetBaseSpeed():5);
		sprintf_s(szSpeedTemp,sizeof(szSpeedTemp),"%.2f%%",pDrome->fSpeed/fBaseSpeed*100);
		m_pID_TEXT_PetSpeed->SetText(szSpeedTemp);

        // Skill
        RefreshMountSkill(mount);

        if (GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT))
        {
            CommonChatFrame::GetActiveChatFrame()->addHyberText( pDrome->GetName(), 
                mount.baseInfo.guid, mount.baseInfo.id, BT_MountBag );
        }

        //ChangeModel( mount.baseInfo.id );
    }
}

void CUI_ID_FRAME_Pet::ActivePet(int nIndex)
{
    if (nIndex < 0)
        return;

    SMountItem& mount = thePlayerRole.GetMountByIndex(nIndex);
    if (mount.baseInfo.id != InvalidLogicNumber)
        ActivePet(mount, nIndex);
}

void CUI_ID_FRAME_Pet::ActivePet(SMountItem& mount, int nIndex)
{
    if (thePlayerRole.GetActivedMountIndex() != nIndex)
        Dismount();	 

    if (!mount.baseInfo.isActive)
    {
        MsgChangeDrome changedrome;
        changedrome.nIndex = nIndex;
        changedrome.ucOpType = MsgChangeDrome::EOT_Active;
        changedrome.guid = mount.baseInfo.guid;
        GettheNetworkInput().SendMsg(&changedrome);
    }	
    else
    {
        MsgChangeDrome changedrome;
        changedrome.nIndex = nIndex;
        changedrome.ucOpType = MsgChangeDrome::EOT_UnActive;
        changedrome.guid = mount.baseInfo.guid;
        GettheNetworkInput().SendMsg(&changedrome);
    }
}

static bool IfDiscardPet(char bPressYesButton, void *pData)
{
    if (bPressYesButton && pData)
    {
        MsgChangeDrome* changedrome = (MsgChangeDrome*)pData;

        if (changedrome->nIndex == thePlayerRole.GetActivedMountIndex())
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eUI_CanNotDestroyActivedMount ) );
            return false;
        }

        GettheNetworkInput().SendMsg(changedrome);

        return true;
    }
    return false;
}

void CUI_ID_FRAME_Pet::DiscardPet(int nIndex)
{
    if (nIndex < 0)
        return;

    SMountItem& mount = thePlayerRole.GetMountByIndex(nIndex);
    if (mount.baseInfo.id != InvalidLogicNumber)
    {
        if (mount.baseInfo.isActive)
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eUI_CanNotDestroyActivedMount ) );
            return;
        }

        MsgChangeDrome changedrome;
        changedrome.nIndex = nIndex;
        changedrome.guid = mount.baseInfo.guid;
        changedrome.ucOpType = MsgChangeDrome::EOT_Discard;

        DWORD dwColor = 0;
        ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( mount.baseInfo.id );
        if( pCommon )
            dwColor = S_IconInfoHero::GetQualityColor( mount.baseInfo.quality );

        char buf[256];
        char name[MAX_PATH] = {0};
        sprintf(name, "{#%x=%s#}", dwColor, mount.baseInfo.szName);
        sprintf(buf, theXmlString.GetString(eText_QueryDiscardMount), name);
        s_CUI_ID_FRAME_MessageBox.Show( buf, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
            false, IfDiscardPet, &changedrome, sizeof(MsgChangeDrome) );
    }
}

bool CUI_ID_FRAME_Pet::IsActivedPet() const
{
    return thePlayerRole.GetActivedMount();
}

void CUI_ID_FRAME_Pet::Mount()
{
	SMountItem* pMountImte = thePlayerRole.GetActivedMount();
	
	// 玩家变身镖车时禁止上坐骑
	if (theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
		return;
	
    if (pMountImte)
    {
		//判断当前状态是否可以骑马
		if(theHeroGame.GetPlayerMgr()->GetMe() && !theHeroGame.GetPlayerMgr()->GetMe()->m_cFightStatus.IsCanRide())
			return;
		MsgChangeDrome changedrome;
		changedrome.nIndex = thePlayerRole.GetActivedMountIndex();//zhuxincong 这里是在 thePlayerRole.GetActivedMountIndex()获得索引，即获得第几只坐骑
		changedrome.ucOpType = MsgChangeDrome::EOT_Ride;
		changedrome.guid = pMountImte->baseInfo.guid;
		GettheNetworkInput().SendMsg(&changedrome);
    }
    else
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_NotActived ) );
    }
}

void CUI_ID_FRAME_Pet::Dismount()
{
    // 跳跃时不下马
    if( theHeroGame.GetPlayerMgr()->GetMe() && !theHeroGame.GetPlayerMgr()->GetMe()->IsJumping() && theHeroGame.GetPlayerMgr()->GetMe()->IsCanDisMount())
    {
        theHeroGame.GetPlayerMgr()->GetMe()->DisMount();
        theHeroGame.GetPlayerMgr()->DisDrome();
        s_CUI_ID_FRAME_MAIN.RefeashHotKey();
        s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
    }
}

void CUI_ID_FRAME_Pet::ID_LIST_ShouLanOnListLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
    s_CUI_ID_FRAME_Pet.PetSelectChanged(s_CUI_ID_FRAME_Pet.m_pID_LIST_ShouLan->GetCurSelIndex());
    s_CUI_ID_FRAME_Pet.ActivePet(s_CUI_ID_FRAME_Pet.m_pID_LIST_ShouLan->GetCurSelIndex());
}

bool CUI_ID_FRAME_Pet::HasSkill(int nId)
{
    return false;
}

bool CUI_ID_FRAME_Pet::IsSkillList(const ControlObject* pObject)
{
    if( !m_pID_FRAME_Pet )
        return false;
    return m_pID_LISTIMG_ZhuDong == pObject || m_pID_LISTIMG_QiCheng == pObject;
}

void CUI_ID_FRAME_Pet::RefreshMountSkill()
{
    if( !m_pID_FRAME_Pet )
        return;
    if (IsVisable())
    {
        if( m_pID_LIST_ShouLan )
            PetSelectChanged(m_pID_LIST_ShouLan->GetCurSelIndex());
    }
    else
    {
        // 升级后，如果坐骑可以携带，更新按键状态
        if (m_pID_LIST_ShouLan && m_pID_LIST_ShouLan->GetCurSelIndex() >= 0)
        {
            SMountItem& mount = thePlayerRole.GetMountByIndex(m_pID_LIST_ShouLan->GetCurSelIndex());
            if (mount.baseInfo.id != InvalidLogicNumber)
            {
                ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( mount.baseInfo.id );
                if (pDrome)
                {
                    DWORD dwDJColor = 0x00ffffff;
                    if( pDrome->takeLevel > thePlayerRole.GetLevel() )
                    {
                        dwDJColor = 0xff0000;
                        m_bCanMount = false;
                    }
                    else
                        m_bCanMount = true;

                    if( m_pID_TEXT_SYDJ )
                        m_pID_TEXT_SYDJ->SetText(pDrome->takeLevel, dwDJColor);
                }
            }
        }
    }
}

void CUI_ID_FRAME_Pet::RefreshMountSkill(SMountItem &mount)
{
    const SUIIconSet::SIconSet* pIcon = 
        g_UISkillMgr.GetSkillIconSet(CUI_ID_FRAME_BaseProperty::TYPE_MOUNT);
    if (pIcon)
    {
        ControlIconDrag::S_ListImg stItem;
        stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
        stItem.SetData( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT, 1, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
        stItem.SetFlags(CUISkillMgr::eCommon);
        m_pID_LISTIMG_QiCheng->SetItem(&stItem);
    }

    CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
        GetPage(CUISkillMgr::eMountSkill);
    if (!pSkillTree)
        return;

    SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
    m_pID_LISTIMG_ZhuDong->SetEnableCnt( mount.skillInfo.initiativeSkillNumber );

    for ( int i=0; i<SMountItem::MICD_MaxSkillCount; ++i)
    {
        unsigned short usSkillId = mount.skillInfo.skills[i].ustSkillID;
        if ( usSkillId == 0)
            continue;
        unsigned short usLevel = mount.skillInfo.skills[i].stSkillLevel;
        ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(usSkillId,usLevel);
        if (!pItemSkill)
            continue;
        const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue(usSkillId);
        if (!pIcon)
            continue;

        ControlIconDrag::S_ListImg stItem;
        stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
        stItem.SetData( usSkillId, usLevel, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
        stItem.SetFlags(CUISkillMgr::eMountSkill);

        SkillBag::SColdTime *pTime = NULL;
        pTime = thePlayerRole.m_MountSkillBag.GetColdTimeById( usSkillId );
        if ( pTime )
        {
            stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
        }

        switch (pItemSkill->sSkillCategory)
        {
        case ItemDefine::SCT_MountPassive:
        case ItemDefine::SCT_MountMasterInitiativeUnControl:
            m_pID_LISTIMG_BeiDong->SetItem(&stItem);
            break;
        case ItemDefine::SCT_MountMasterInitiativeControl:
            m_pID_LISTIMG_ZhuDong->SetItem(&stItem);
            break;
        }
    }
}

void CUI_ID_FRAME_Pet::ChangePetName(const char* szName)
{
    if( !m_pID_FRAME_Pet )
        return;
    if( !szName )
        return;

    int nSelId = m_pID_LIST_ShouLan->GetCurSelIndex();
    if (nSelId < 0)
        return ;

    strcpy(thePlayerRole.GetMountByIndex(nSelId).baseInfo.szName, szName);

    MsgChangeMountName msg;
    msg.usIndex = nSelId;
    strcpy(msg.szName, szName);
    GettheNetworkInput().SendMsg(&msg);

    Refresh();
}

void CUI_ID_FRAME_Pet::ChangeModel( int mountID )
{
	m_nModelId = -1;
    if( GettheItemDetail().GetDromeByID( mountID ) )
    {
        m_nModelId = GetMexResMgr()->AddExternalFile( GettheItemDetail().GetDromeByID( mountID )->GetModelPath() );
        if( m_nModelId == -1 )
        {
            assert( false );
            return;
        }
    }
    else
        return;

   RenderAnim_SetModelID(m_nModelId);
}

bool CUI_ID_FRAME_Pet::IsMountInBargaining( __int64 guid )
{
    return s_CUI_ID_FRAME_Bargaining.IsSelfItemInBargaining( guid );
}

bool CUI_ID_FRAME_Pet::IsMountInPrivateShop( __int64 guid )
{
    if( !s_CUI_ID_FRAME_PrivateShop.IsVisable() && !s_CUI_ID_FRAME_PrivateShop.IsOpening() )
        return false;

    return CSystemStallage::Instance()->IsMountInStallage( guid );
}

bool CUI_ID_FRAME_Pet::IsEqualToLISTIMG_PetIcon( ControlObject * pListImage )
{
    if( !m_pID_FRAME_Pet || !pListImage )
        return false;
    return (m_pID_LISTIMG_PetIcon == (ControlListImage*)pListImage);
}

int CUI_ID_FRAME_Pet::PenIcon_GetIndexByItem( ControlIconDrag::S_ListImg* pItem )
{
    if( !m_pID_FRAME_Pet || !pItem )
        return -1;

    return m_pID_LISTIMG_PetIcon->GetItemIndex( pItem );
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_Pet::PenIcon_GetItemByIndex( int index )
{
    if( !m_pID_FRAME_Pet || index < 0 )
        return NULL;

    return m_pID_LISTIMG_PetIcon->GetItemByIndex( index );
}

bool CUI_ID_FRAME_Pet::IsListImageByBagType(ControlObject* pObject)
{
    if(!m_pID_FRAME_Pet)
        return false;

    if(m_pID_LISTIMG_PetIcon == pObject)
        return true;

    return false;
}

bool CUI_ID_FRAME_Pet::IsInCoolDownTime(SMountItem* pMount)
{
    for ( int i=0; i<SMountItem::MICD_MaxSkillCount; ++i)
    {
        unsigned short usSkillId = pMount->skillInfo.skills[i].ustSkillID;
        if ( usSkillId == 0)
            continue;	

        SkillBag::SColdTime *pTime = NULL;
        pTime = thePlayerRole.m_MountSkillBag.GetColdTimeById(usSkillId);
        if (!pTime)
        {
            continue;
        }

        if (HQ_TimeGetTime() - pTime->dwColdStartTime <= pTime->dwColdTime)
        {
            return true;
        }
    }

    return false;			
}

void CUI_ID_FRAME_Pet::SetStateByCoolDownTime(SMountItem* pMount)
{
    if (!pMount)
    {
        return;
    }

    if (IsInCoolDownTime(pMount))
    {
        m_pID_BUTTON_XiuXi->SetEnable(false);
    }
    else
    {
        m_pID_BUTTON_XiuXi->SetEnable(true);
    }
}

void CUI_ID_FRAME_Pet::InitActivePicState()
{
    for (int i = 0; i <= ITEM_MOUNT_MAXCOUNT; ++i)
    {
        m_bActivePet[i] = false;
    }

    m_bNeedRefresh = false;
    m_bSelectEnd = false;
}

void CUI_ID_FRAME_Pet::RefreshFightState(int nIndex)
{
    for( int i = 0 ; i < ITEM_MOUNT_MAXCOUNT; ++ i )
    {
        m_bActivePet[i] = false;
    }

    if (nIndex >= 0 && nIndex < ITEM_MOUNT_MAXCOUNT)
    {
        m_bActivePet[nIndex] = true;
    }

    RefreshFightIcon();
}

void CUI_ID_FRAME_Pet::RefreshFightIcon()
{
    if (!m_pID_LIST_War)
    {
        return;
    }

    m_pID_LIST_War->Clear();
    ControlList::S_List stEmptyItem;
    stEmptyItem.SetData("");
    ControlList::S_List stActiveItem;
    stActiveItem.SetData("{#1209}");
    for (int i = 0; i < ITEM_MOUNT_MAXCOUNT; ++i)
    {
        if (m_bActivePet[i])
        {
            m_pID_LIST_War->AddItem(&stActiveItem);
        }
        else
        {
            m_pID_LIST_War->AddItem(&stEmptyItem);
        }
    }
}

// Button
bool CUI_ID_FRAME_Pet::ID_BUTTON_StrengthenOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_MountStrengthen.SetVisable(true);
	return true;
}
bool CUI_ID_FRAME_Pet::ID_BUTTON_MountMoveStarOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_MountMoveStar.SetVisable(true);
	return true;
}