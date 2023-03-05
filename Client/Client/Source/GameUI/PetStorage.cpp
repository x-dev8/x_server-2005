/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\PetStorage.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PetStorage.h"
#include "PetList.h"
#include "PlayerRole.h"
#include "IconManagerClient.h"
#include "SeekPet.h"
#include "Common.h"
#include "NetworkInput.h"
#include "ScreenInfoManager.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "SuperPassword.h"

CUI_ID_FRAME_PetStorage s_CUI_ID_FRAME_PetStorage;

MAP_FRAME_RUN( s_CUI_ID_FRAME_PetStorage, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PetStorage, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetStorage, ID_BUTTON_InfoOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetStorage, ID_BUTTON_GetOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PetStorage, ID_CHECKBOX_Space1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PetStorage, ID_CHECKBOX_Space2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PetStorage, ID_CHECKBOX_Space3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PetStorage, ID_CHECKBOX_Space4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PetStorage, ID_CHECKBOX_Space5OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PetStorage, ID_CHECKBOX_Space6OnCheckBoxCheck )

CUI_ID_FRAME_PetStorage::CUI_ID_FRAME_PetStorage()
{
    m_nPetSelectIndex = -1;
    m_nMountNumInStorage = 0;
    ResetMembers();
}

void CUI_ID_FRAME_PetStorage::ResetMembers()
{
	m_pID_FRAME_PetStorage = NULL;
	m_pID_BUTTON_Info = NULL;
	m_pID_BUTTON_Get = NULL;
	m_pID_TEXT_Space = NULL;

    for( int i = 0; i < STORAGE_MOUNTGRID_MAX; ++i )
    {
        m_pID_LISTIMG_PetIcon[i] = NULL;
        m_pID_TEXT_PetName[i] = NULL;
        m_pID_TEXT_PetLvl[i] = NULL;
        m_pID_TEXT_Race[i] = NULL;
        m_pID_TEXT_Strength[i] = NULL;
        m_pID_TEXT_Agility[i] = NULL;
        m_pID_TEXT_Stamina[i] = NULL;
        m_pID_TEXT_Intellect[i] = NULL;
        m_pID_PICTURE_Empty[i] = NULL;
        m_pID_PICTURE_Lock[i] = NULL;
        m_pID_CHECKBOX_Space[i] = NULL;
    }

	m_vVisiblePos = Vector(0.0f,0.0f,0.0f);
}

bool CUI_ID_FRAME_PetStorage::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_PetStorage::OnFrameRender()
{
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if ( pMe )
	{
		float fMeX,fMeY,fMeZ;			
		pMe->GetPos( &fMeX, &fMeY, &fMeZ );
		float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
		if( dist > 12.0f )
		{
			SetVisable( false );
		}
	}
	return true;
}

bool CUI_ID_FRAME_PetStorage::ID_BUTTON_InfoOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetStorage )
		return false;

    SeekPetByIndex( m_nPetSelectIndex );
	return true;
}

bool CUI_ID_FRAME_PetStorage::ID_BUTTON_GetOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetStorage )
		return false;

    TakeOutMount();
	return true;
}

void CUI_ID_FRAME_PetStorage::ID_CHECKBOX_Space1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetStorage )
		return;

    SetCurrentSelectIndex( 0 );
}

void CUI_ID_FRAME_PetStorage::ID_CHECKBOX_Space2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetStorage )
		return;

    SetCurrentSelectIndex( 1 );
}

void CUI_ID_FRAME_PetStorage::ID_CHECKBOX_Space3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetStorage )
		return;

    SetCurrentSelectIndex( 2 );
}

void CUI_ID_FRAME_PetStorage::ID_CHECKBOX_Space4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetStorage )
		return;

    SetCurrentSelectIndex( 3 );
}

void CUI_ID_FRAME_PetStorage::ID_CHECKBOX_Space5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetStorage )
		return;

    SetCurrentSelectIndex( 4 );
}

void CUI_ID_FRAME_PetStorage::ID_CHECKBOX_Space6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetStorage )
		return;

    SetCurrentSelectIndex( 5 );
}

// 装载UI
bool CUI_ID_FRAME_PetStorage::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PetStorage.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PetStorage.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_PetStorage::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PetStorage, s_CUI_ID_FRAME_PetStorageOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PetStorage, s_CUI_ID_FRAME_PetStorageOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PetStorage, ID_BUTTON_Info, s_CUI_ID_FRAME_PetStorageID_BUTTON_InfoOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetStorage, ID_BUTTON_Get, s_CUI_ID_FRAME_PetStorageID_BUTTON_GetOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetStorage, ID_CHECKBOX_Space1, s_CUI_ID_FRAME_PetStorageID_CHECKBOX_Space1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetStorage, ID_CHECKBOX_Space2, s_CUI_ID_FRAME_PetStorageID_CHECKBOX_Space2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetStorage, ID_CHECKBOX_Space3, s_CUI_ID_FRAME_PetStorageID_CHECKBOX_Space3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetStorage, ID_CHECKBOX_Space4, s_CUI_ID_FRAME_PetStorageID_CHECKBOX_Space4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetStorage, ID_CHECKBOX_Space5, s_CUI_ID_FRAME_PetStorageID_CHECKBOX_Space5OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetStorage, ID_CHECKBOX_Space6, s_CUI_ID_FRAME_PetStorageID_CHECKBOX_Space6OnCheckBoxCheck );

	m_pID_FRAME_PetStorage = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetStorage );
	m_pID_BUTTON_Info = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_BUTTON_Info );
	m_pID_BUTTON_Get = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_BUTTON_Get );
	m_pID_TEXT_Space = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Space );
	m_pID_LISTIMG_PetIcon[0] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_LISTIMG_PetIcon1 );
	m_pID_LISTIMG_PetIcon[1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_LISTIMG_PetIcon2 );
	m_pID_LISTIMG_PetIcon[2] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_LISTIMG_PetIcon3 );
	m_pID_LISTIMG_PetIcon[3] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_LISTIMG_PetIcon4 );
	m_pID_LISTIMG_PetIcon[4] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_LISTIMG_PetIcon5 );
	m_pID_LISTIMG_PetIcon[5] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_LISTIMG_PetIcon6 );
	m_pID_TEXT_PetName[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetName1 );
	m_pID_TEXT_PetName[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetName2 );
	m_pID_TEXT_PetName[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetName3 );
	m_pID_TEXT_PetName[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetName4 );
	m_pID_TEXT_PetName[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetName5 );
	m_pID_TEXT_PetName[5] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetName6 );
	m_pID_TEXT_PetLvl[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetLvl1 );
	m_pID_TEXT_PetLvl[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetLvl2 );
	m_pID_TEXT_PetLvl[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetLvl3 );
	m_pID_TEXT_PetLvl[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetLvl4 );
	m_pID_TEXT_PetLvl[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetLvl5 );
	m_pID_TEXT_PetLvl[5] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_PetLvl6 );
	m_pID_TEXT_Race[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Race1 );
	m_pID_TEXT_Race[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Race2 );
	m_pID_TEXT_Race[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Race3 );
	m_pID_TEXT_Race[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Race4 );
	m_pID_TEXT_Race[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Race5 );
	m_pID_TEXT_Race[5] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Race6 );
	m_pID_TEXT_Strength[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Strength1 );
	m_pID_TEXT_Strength[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Strength2 );
	m_pID_TEXT_Strength[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Strength3 );
	m_pID_TEXT_Strength[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Strength4 );
	m_pID_TEXT_Strength[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Strength5 );
	m_pID_TEXT_Strength[5] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Strength6 );
	m_pID_TEXT_Agility[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Agility1 );
	m_pID_TEXT_Agility[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Agility2 );
	m_pID_TEXT_Agility[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Agility3 );
	m_pID_TEXT_Agility[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Agility4 );
	m_pID_TEXT_Agility[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Agility5 );
	m_pID_TEXT_Agility[5] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Agility6 );
	m_pID_TEXT_Stamina[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Stamina1 );
	m_pID_TEXT_Stamina[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Stamina2 );
	m_pID_TEXT_Stamina[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Stamina3 );
	m_pID_TEXT_Stamina[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Stamina4 );
	m_pID_TEXT_Stamina[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Stamina5 );
	m_pID_TEXT_Stamina[5] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Stamina6 );
	m_pID_TEXT_Intellect[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Intellect1 );
	m_pID_TEXT_Intellect[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Intellect2 );
	m_pID_TEXT_Intellect[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Intellect3 );
	m_pID_TEXT_Intellect[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Intellect4 );
	m_pID_TEXT_Intellect[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Intellect5 );
	m_pID_TEXT_Intellect[5] = (ControlText*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_TEXT_Intellect6 );
	m_pID_PICTURE_Empty[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Empty1 );
	m_pID_PICTURE_Empty[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Empty2 );
	m_pID_PICTURE_Empty[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Empty3 );
	m_pID_PICTURE_Empty[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Empty4 );
	m_pID_PICTURE_Empty[4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Empty5 );
	m_pID_PICTURE_Empty[5] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Empty6 );
	m_pID_PICTURE_Lock[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Lock1 );
	m_pID_PICTURE_Lock[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Lock2 );
	m_pID_PICTURE_Lock[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Lock3 );
	m_pID_PICTURE_Lock[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Lock4 );
	m_pID_PICTURE_Lock[4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Lock5 );
	m_pID_PICTURE_Lock[5] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_PICTURE_Lock6 );
	m_pID_CHECKBOX_Space[0] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_CHECKBOX_Space1 );
	m_pID_CHECKBOX_Space[1] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_CHECKBOX_Space2 );
	m_pID_CHECKBOX_Space[2] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_CHECKBOX_Space3 );
	m_pID_CHECKBOX_Space[3] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_CHECKBOX_Space4 );
	m_pID_CHECKBOX_Space[4] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_CHECKBOX_Space5 );
	m_pID_CHECKBOX_Space[5] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetStorage, ID_CHECKBOX_Space6 );

	assert( m_pID_FRAME_PetStorage );
	assert( m_pID_BUTTON_Info );
	assert( m_pID_BUTTON_Get );
	assert( m_pID_TEXT_Space );

    for( int i = 0; i < STORAGE_MOUNTGRID_MAX; ++i )
    {
        assert( m_pID_LISTIMG_PetIcon[i] );
        assert( m_pID_TEXT_PetName[i] );
        assert( m_pID_TEXT_PetLvl[i] );
        assert( m_pID_TEXT_Race[i] );
        assert( m_pID_TEXT_Strength[i] );
        assert( m_pID_TEXT_Agility[i] );
        assert( m_pID_TEXT_Stamina[i] );
        assert( m_pID_TEXT_Intellect[i] );
        assert( m_pID_PICTURE_Empty[i] );
        assert( m_pID_PICTURE_Lock[i] );
        assert( m_pID_CHECKBOX_Space[i] );
    }

    for( int i = 0; i < STORAGE_MOUNTGRID_MAX; ++i )
    {
        m_groupPet[i].Clear();
        m_groupPet[i].AddControl( m_pID_LISTIMG_PetIcon[i] );
        m_groupPet[i].AddControl( m_pID_TEXT_PetName[i] );
        m_groupPet[i].AddControl( m_pID_TEXT_PetLvl[i] );
        m_groupPet[i].AddControl( m_pID_TEXT_Race[i] );
        m_groupPet[i].AddControl( m_pID_TEXT_Strength[i] );
        m_groupPet[i].AddControl( m_pID_TEXT_Agility[i] );
        m_groupPet[i].AddControl( m_pID_TEXT_Stamina[i] );
        m_groupPet[i].AddControl( m_pID_TEXT_Intellect[i] );
        m_groupPet[i].AddControl( m_pID_CHECKBOX_Space[i] );

        m_pID_LISTIMG_PetIcon[i]->SetCanbePick( false );
    }

    m_pID_FRAME_PetStorage->SetOnVisibleChangedFun( OnVisibleChange );

    ResetStorageSelect();

	return true;
}

// 卸载UI
bool CUI_ID_FRAME_PetStorage::_UnLoadUI()
{
    for( int i = 0; i < STORAGE_MOUNTGRID_MAX; ++i )
    {
        m_groupPet[i].Clear();
    }
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\PetStorage.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_PetStorage::_IsVisable()
{
	if ( !m_pID_FRAME_PetStorage )
		return false;
	return m_pID_FRAME_PetStorage->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_PetStorage::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_PetStorage )
		return;
	m_pID_FRAME_PetStorage->SetVisable( bVisable );
}

//---------------------- 逻辑 -------------------------
void CUI_ID_FRAME_PetStorage::ShowPetStorage( bool bShow )
{
    SetVisable( bShow );
    s_CUI_ID_FRAME_PetList.ShowPetList( bShow );
    if( bShow )
    {
        Refresh();
    }
}

void CUI_ID_FRAME_PetStorage::OnVisibleChange( ControlObject* pUIObject )
{
    if( !s_CUI_ID_FRAME_PetStorage.IsVisable() )
    {
        s_CUI_ID_FRAME_PetStorage.ShowPetStorage( false );
    }
}

void CUI_ID_FRAME_PetStorage::SeekPetByIndex( int nIndex )
{
    // 查看详情
    int nCurNumInStorage = thePlayerRole.m_charinfo.baseinfo.liveinfo.nStorageMountGrid;
    if( nIndex < 0 || nIndex >= nCurNumInStorage )
        return;

    SMountItem* pMount = &thePlayerRole.m_stStorage.xStorageMounts[nIndex];
    s_CUI_ID_FRAME_SeekPet.SetVisable( true );
    s_CUI_ID_FRAME_SeekPet.SetMount( *pMount );
}

void CUI_ID_FRAME_PetStorage::TakeOutMount()
{
    // 取马报错
    int nCurNumInStorage = thePlayerRole.m_charinfo.baseinfo.liveinfo.nStorageMountGrid;
    if( m_nPetSelectIndex < 0 || m_nPetSelectIndex >= nCurNumInStorage )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_InfoError ) );
        return;
    }

    SMountItem* pMount = &thePlayerRole.m_stStorage.xStorageMounts[m_nPetSelectIndex];
    if( pMount->GetMountID() <= 0 )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_InfoError ) );
        return;
    }

    int nDestIndex = s_CUI_ID_FRAME_PetList.GetCharEmptySlot();
    if( nDestIndex < 0 )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_CharCarryFull ) );
        return;
    }

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (thePlayerRole.GetIsSecondPassword() && !s_CUI_ID_FRAME_SuperPassword.GetChecked() && pMe)
	{
		s_CUI_ID_FRAME_SuperPassword.SetVisiblePosition(*(Vector*)&pMe->GetPos());
		s_CUI_ID_FRAME_SuperPassword.SetVisable(true);

		if( s_CUI_ID_FRAME_SuperPassword.GetEditAddName() )
			theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPassword.GetEditAddName());
		return ;
	}


    // 发送信息
    MsgMoveStorageMount msg;
    msg.nMoveType = MsgMoveStorageMount::Type_StorageToChar;
    msg.nSrcIndex = m_nPetSelectIndex;
    msg.nDstIndex = nDestIndex;
    msg.nGuid = pMount->baseInfo.guid;
    GettheNetworkInput().SendMsg( &msg );
}

int CUI_ID_FRAME_PetStorage::GetStorageEmptySlot()
{
    // 获取仓库内可存放的槽位
    int nCurNumInStorage = thePlayerRole.m_charinfo.baseinfo.liveinfo.nStorageMountGrid;
    if( m_nMountNumInStorage >= nCurNumInStorage )
        return -1;

    for( int i = 0; i < nCurNumInStorage; ++i )
    {
        SMountItem* pMount = &thePlayerRole.m_stStorage.xStorageMounts[i];
        if( pMount->GetMountID() <= 0 )
        {
            return i;
        }
    }

    return -1;
}

//------------------------ UI --------------------------
void CUI_ID_FRAME_PetStorage::Refresh()
{
    if( !IsUILoad() )
        return;

    int nCurNumInStorage = thePlayerRole.m_charinfo.baseinfo.liveinfo.nStorageMountGrid;
    if( nCurNumInStorage > STORAGE_MOUNTGRID_MAX )
        return;

    // 开槽
    for( int i = 0; i < STORAGE_MOUNTGRID_MAX; ++i )
    {
        if( i < nCurNumInStorage )
        {
            m_pID_PICTURE_Lock[i]->SetVisable( false );
        }
        else
        {
            m_pID_PICTURE_Lock[i]->SetVisable( true );
            m_groupPet[i].SetVisible( false );
        }
    }

    // 仓库内坐骑
    m_nMountNumInStorage = 0;
    for( int i = 0; i < nCurNumInStorage; ++i )
    {
        SMountItem* pMount = &thePlayerRole.m_stStorage.xStorageMounts[i];
        if( pMount->GetMountID() <= 0 )
        {
            m_pID_PICTURE_Empty[i]->SetVisable( true );
            m_groupPet[i].SetVisible( false );
        }
        else
        {
            m_pID_PICTURE_Empty[i]->SetVisable( false );
            m_groupPet[i].SetVisible( true );

            // 坐骑图标
            ControlIconDrag::S_ListImg stItem;
            stItem.SetData( pMount->GetMountID(), 1 );
            m_pID_LISTIMG_PetIcon[i]->SetItem( &stItem, 0 );

            // 坐骑名称、等级、品种
            ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( pMount->GetMountID() );
            if( !pDrome )
                continue;
            DWORD dwColor = S_IconInfoHero::GetQualityColor( pMount->baseInfo.quality );
            m_pID_TEXT_PetName[i]->SetText( pMount->baseInfo.szName, dwColor );
            *m_pID_TEXT_PetLvl[i] = pMount->baseInfo.level;
            m_pID_TEXT_Race[i]->SetText( pDrome->GetName(), dwColor );

            // 坐骑四围
            *m_pID_TEXT_Stamina[i] = ( int )pMount->baseInfo.currentAttribute[EBaseAttr_Stamina];
            *m_pID_TEXT_Strength[i] = ( int )pMount->baseInfo.currentAttribute[EBaseAttr_Strength];
            *m_pID_TEXT_Agility[i] = ( int )pMount->baseInfo.currentAttribute[EBaseAttr_Agility];
            *m_pID_TEXT_Intellect[i] = ( int )pMount->baseInfo.currentAttribute[EBaseAttr_Intelligence];

            ++m_nMountNumInStorage;
        }
    }

    // 仓库容量
    char szMountNum[MAX_PATH] = {0};
    MeSprintf_s( szMountNum, sizeof( szMountNum ) / sizeof( char ) - 1, "%d/%d", m_nMountNumInStorage, nCurNumInStorage );
    m_pID_TEXT_Space->SetText( szMountNum );

    ResetStorageSelect();

    // 选中第一个有马的槽
    if( m_nMountNumInStorage > 0 )
    {
        for( int i = 0; i < STORAGE_MOUNTGRID_MAX; ++i )
        {
            if( SetCurrentSelectIndex( i ) )
                break;
        }
    }
}

void CUI_ID_FRAME_PetStorage::ResetStorageSelect()
{
    m_nPetSelectIndex = -1;

    if( !IsUILoad() )
        return;

    for( int i = 0; i < STORAGE_MOUNTGRID_MAX; ++i )
    {
        m_pID_CHECKBOX_Space[i]->SetCheck( false );
    }
    m_pID_BUTTON_Info->SetEnable( false );
    m_pID_BUTTON_Get->SetEnable( false );
}

bool CUI_ID_FRAME_PetStorage::SetCurrentSelectIndex( int nIndex )
{
    // 当前选中
    if( !IsUILoad() )
        return false;

    int nCurNumInStorage = thePlayerRole.m_charinfo.baseinfo.liveinfo.nStorageMountGrid;
    if( nIndex < 0 || nIndex >= nCurNumInStorage )
        return false;

    SMountItem* pMount = &thePlayerRole.m_stStorage.xStorageMounts[nIndex];
    if( pMount->GetMountID() <= 0 )
        return false;

    ResetStorageSelect();
    m_nPetSelectIndex = nIndex;

    m_pID_CHECKBOX_Space[nIndex]->SetCheck( true );
    m_pID_BUTTON_Info->SetEnable( true );
    m_pID_BUTTON_Get->SetEnable( true );

    return true;
}
