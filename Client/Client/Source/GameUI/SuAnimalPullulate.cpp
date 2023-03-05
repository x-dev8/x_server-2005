/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Turbo\MEUI\3.14-3.19\宠物界面\宠物提升悟性 鉴定成功率 右键菜单界面\SuAnimalPullulate.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimalPullulate.h"
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
#include "ItemDetail.h"
#include "SoundConfig.h"
#include "SystemStallage.h"
#include "PetSettingConfig.h"

CUI_ID_FRAME_SuAnimalPullulate s_CUI_ID_FRAME_SuAnimalPullulate;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimalPullulate, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimalPullulate, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_BUTTON_SureOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_LISTIMG_PetIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_LISTIMG_PetIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_LISTIMG_PetIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_LISTIMG_PetIconOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_BUTTON_HELPOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_LIST_ShouLanOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_LIST_WarOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_BUTTON_SelectOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_BUTTON_LookOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalPullulate, ID_BUTTON_CancelOnButtonClick )
CUI_ID_FRAME_SuAnimalPullulate::CUI_ID_FRAME_SuAnimalPullulate()
{
	// Member
	m_pID_FRAME_SuAnimalPullulate = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_PICTURE_Yingxiang = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_LISTIMG_PetIcon = NULL;
	m_pID_TEXT_Generation = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_LIST_ShouLan = NULL;
	m_pID_LIST_War = NULL;
	m_pID_BUTTON_Select = NULL;
	m_pID_BUTTON_Look = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Cost = NULL;
	m_pID_TEXT_Money1 = NULL;
	m_pID_TEXT_Money2 = NULL;
	m_pID_TEXT_Info = NULL;
	m_nModelId = 0;
}
// Frame
bool CUI_ID_FRAME_SuAnimalPullulate::OnFrameRun()
{
	if (!s_CUI_ID_FRAME_SuAnimalPullulate.IsVisable()) return false;
	if (m_bRotate && m_pID_BUTTON_Right->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
	{
		m_fRotateZ += 1.5f*theHeroGame.GetFrameElapsedTime();
	}
	else if (m_bRotate && m_pID_BUTTON_Left->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
	{
		m_fRotateZ -= 1.5f*theHeroGame.GetFrameElapsedTime();
	}
	else 
		m_bRotate = false;

	return true;
}
bool CUI_ID_FRAME_SuAnimalPullulate::OnFrameRender()
{
	GetEngine()->GetRenderer()->EndScene();
	RenderViewport();
	GetEngine()->GetRenderer()->BeginScene();
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalPullulate::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalPullulate::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
		m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalPullulate::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
		m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalPullulate::ID_BUTTON_SureOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return ReadyOk();
}
// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimalPullulate::ID_LISTIMG_PetIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalPullulate::ID_LISTIMG_PetIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalPullulate::ID_LISTIMG_PetIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimalPullulate::ID_LISTIMG_PetIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_SuAnimalPullulate::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return true;
}
// List
void CUI_ID_FRAME_SuAnimalPullulate::ID_LIST_ShouLanOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return;
	m_fRotateZ = 0.0f;
	PetSelectChange(m_pID_LIST_ShouLan->GetCurSelIndex());
}
// List
void CUI_ID_FRAME_SuAnimalPullulate::ID_LIST_WarOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return;
}
// Button
bool CUI_ID_FRAME_SuAnimalPullulate::ID_BUTTON_SelectOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalPullulate::ID_BUTTON_LookOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalPullulate::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SuAnimalPullulate::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimalPullulate.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuAnimalPullulate.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuAnimalPullulate::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SuAnimalPullulate, s_CUI_ID_FRAME_SuAnimalPullulateOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SuAnimalPullulate, s_CUI_ID_FRAME_SuAnimalPullulateOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalPullulate, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SuAnimalPullulateID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Right, s_CUI_ID_FRAME_SuAnimalPullulateID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Left, s_CUI_ID_FRAME_SuAnimalPullulateID_BUTTON_LeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Sure, s_CUI_ID_FRAME_SuAnimalPullulateID_BUTTON_SureOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimalPullulate, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SuAnimalPullulateID_LISTIMG_PetIconOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimalPullulate, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SuAnimalPullulateID_LISTIMG_PetIconOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimalPullulate, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SuAnimalPullulateID_LISTIMG_PetIconOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimalPullulate, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SuAnimalPullulateID_LISTIMG_PetIconOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalPullulate, ID_BUTTON_HELP, s_CUI_ID_FRAME_SuAnimalPullulateID_BUTTON_HELPOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_SuAnimalPullulate, ID_LIST_ShouLan, s_CUI_ID_FRAME_SuAnimalPullulateID_LIST_ShouLanOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_SuAnimalPullulate, ID_LIST_War, s_CUI_ID_FRAME_SuAnimalPullulateID_LIST_WarOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Select, s_CUI_ID_FRAME_SuAnimalPullulateID_BUTTON_SelectOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Look, s_CUI_ID_FRAME_SuAnimalPullulateID_BUTTON_LookOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SuAnimalPullulateID_BUTTON_CancelOnButtonClick );

	m_pID_FRAME_SuAnimalPullulate = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SuAnimalPullulate );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_BUTTON_CLOSE );
	m_pID_PICTURE_Yingxiang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_PICTURE_Yingxiang );
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Right );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Left );
	m_pID_BUTTON_Sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Sure );
	m_pID_LISTIMG_PetIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_LISTIMG_PetIcon );
	m_pID_TEXT_Generation = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_TEXT_Generation );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_BUTTON_HELP );
	m_pID_LIST_ShouLan = (ControlList*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_LIST_ShouLan );
	m_pID_LIST_War = (ControlList*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_LIST_War );
	m_pID_BUTTON_Select = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Select );
	m_pID_BUTTON_Look = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Look );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_BUTTON_Cancel );
	m_pID_TEXT_Cost = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_TEXT_Cost );
	m_pID_TEXT_Money1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_TEXT_Money1 );
	m_pID_TEXT_Money2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_TEXT_Money2 );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimalPullulate, ID_TEXT_Info );

	assert( m_pID_FRAME_SuAnimalPullulate );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_PICTURE_Yingxiang );
	assert( m_pID_BUTTON_Right );
	assert( m_pID_BUTTON_Left );
	assert( m_pID_BUTTON_Sure );
	assert( m_pID_LISTIMG_PetIcon );
	assert( m_pID_TEXT_Generation );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_LIST_ShouLan );
	assert( m_pID_LIST_War );
	assert( m_pID_BUTTON_Select );
	assert( m_pID_BUTTON_Look );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_Cost );
	assert( m_pID_TEXT_Money1 );
	assert( m_pID_TEXT_Money2 );
	assert( m_pID_TEXT_Info );

	m_pPlayerAnim = MeNew CPlayerAnim;
	m_pPlayer = MeNew CPlayer;
	m_pPlayer->SetAnim( m_pPlayerAnim );
	m_pPlayerAnim->SetPlayer( m_pPlayer );
	theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayer );
	m_pID_BUTTON_Right->SetLButtonDownFun(UIPetPull_RightLBD);
	m_pID_BUTTON_Left->SetLButtonDownFun(UIPetPull_LeftLBD);
	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SuAnimalPullulate::_UnLoadUI()
{
	m_pID_FRAME_SuAnimalPullulate = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_PICTURE_Yingxiang = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_LISTIMG_PetIcon = NULL;
	m_pID_TEXT_Generation = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_LIST_ShouLan = NULL;
	m_pID_LIST_War = NULL;
	m_pID_BUTTON_Select = NULL;
	m_pID_BUTTON_Look = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Cost = NULL;
	m_pID_TEXT_Money1 = NULL;
	m_pID_TEXT_Money2 = NULL;
	m_pID_TEXT_Info = NULL;

	if (m_pPlayer != NULL)
	{
		theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer(m_pPlayer);
		m_pPlayer->Destroy();
		delete m_pPlayer;
		m_pPlayer = 0;
		m_pPlayerAnim = 0;
	}
	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimalPullulate.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SuAnimalPullulate::_IsVisable()
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return false;
	return m_pID_FRAME_SuAnimalPullulate->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SuAnimalPullulate::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )
		return ;
	m_pID_FRAME_SuAnimalPullulate->SetVisable( bVisable );
	m_fRotateZ = 0.0f;
	m_nModelId =-1;
}
void CUI_ID_FRAME_SuAnimalPullulate::Refresh_Help(bool _is)
{
		if (!IsVisable())
		return;

		int nSelId = m_pID_LIST_ShouLan->GetCurSelIndex();
		RefreshMoney();
		m_pID_LIST_ShouLan->Clear();
		//m_pID_LISTIMG_PetIcon->Clear();
		m_pID_PICTURE_Yingxiang->SetVisable(false);
		m_pID_PICTURE_Yingxiang->SetPicName("");

		//m_pActivedPet = 0;
		int nActivePetIndex = -1;

		int nMaxCount = thePetSettingConfig.GetPlayerPetLimit(thePlayerRole.GetLevel());

		for (int i = 0; i < nMaxCount; ++i)
		{
			if (thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId != InvalidLogicNumber)
			{
				ControlList::S_List sData;

				// 取颜色
				ItemDefine::SPetMonster* pCommon = GettheItemDetail().GetPetById( thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId );
				if( !pCommon )
					continue;

				DWORD dwColor = S_IconInfoHero::GetQualityColor( thePlayerRole.m_charinfo.ItemBagData.petItems[i].baseInfo.quality );
				sData.SetData( thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.szName, 
					thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId, 
					0, 
					dwColor );
				m_pID_LIST_ShouLan->AddItem(&sData,NULL, false);

				// 添加icon到控件
				/*	ControlListImage::S_ListImg stItemImage;
				stItemImage.SetData( thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId, 1 );
				((SCharItem*)stItemImage.m_pkIconInfo->GetData())->itembaseinfo.nOnlyInt = thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.guid;

				m_pID_LISTIMG_PetIcon->SetItem( &stItemImage, i );
				*/
// 				if (thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.isActive)
// 				{
// 					m_pActivedPet = &thePlayerRole.GetCharInfo2().ItemBagData.petItems[i];
// 					nActivePetIndex = i;				
// 				}
			}
		}
		if (_is)
		m_pID_LIST_ShouLan->SetCurSelIndex(m_pID_LIST_ShouLan->GetListItemCnt() - 1);
		else if (nSelId == -1)
		m_pID_LIST_ShouLan->SetCurSelIndex(0);
		else
		m_pID_LIST_ShouLan->SetCurSelIndex(nSelId);

		RefreshItemInfo();
}

void CUI_ID_FRAME_SuAnimalPullulate::PetSelectChange(int nindex)
{
	if (!m_pID_FRAME_SuAnimalPullulate)  return;
	RefreshMoney();
	if (nindex <0) return;
	SPetItem &mount = thePlayerRole.GetPetByIndex(nindex);
	if (mount.baseInfo.petId != InvalidLogicNumber)
	{
			ChangeModel(mount,m_pPlayerAnim,m_nModelId);
	}
}

void CUI_ID_FRAME_SuAnimalPullulate::ChangeModel(SPetItem &mount, CPlayerAnim* pAnim, int& iOldModelId )
{
	if ( !m_pID_FRAME_SuAnimalPullulate )		return ;
	int nModelId = mount.baseInfo.petId;
	if( iOldModelId == nModelId )		return;
	iOldModelId = nModelId;
	int	nResMexID = -1;
	ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById(mount.baseInfo.petId);
	if(!pPetMonster)	return;
	if( pAnim )
	{
		pAnim->MyChangeModel( pPetMonster->iModelID, TRUE, NULL );
		pAnim->SetCurAnimType(-1);
	}
}

bool CUI_ID_FRAME_SuAnimalPullulate::ReadyOk()
{
	return true;
}

short CUI_ID_FRAME_SuAnimalPullulate::GetCurrentMountIndex()
{
	if( !m_pID_FRAME_SuAnimalPullulate )
		return -1;
	return m_pID_LIST_ShouLan->GetCurSelIndex();	
}

void CUI_ID_FRAME_SuAnimalPullulate::RenderViewport()
{
	if( !m_pID_FRAME_SuAnimalPullulate )	return ;
	RECT rc;
	m_pID_PICTURE_Yingxiang->GetRealRect(&rc);
	RenderMount(m_nModelId,m_pPlayerAnim,m_fRotateZ,rc);
}

void CUI_ID_FRAME_SuAnimalPullulate::RenderMount(int nMountId, CPlayerAnim *pAnim, float fRotateZ, const RECT &rt)
{
	if (!m_pID_FRAME_SuAnimalPullulate)		return;
	if( nMountId < 0 )
		return;

	MeCamera camera;
	D3DVIEWPORT9 viewPort;
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	IRenderer* r = GetEngine()->GetRenderer();

	viewPort.X = rt.left;
	viewPort.Y = rt.top;
	viewPort.Width = rt.right - rt.left;
	viewPort.Height = rt.bottom - rt.top;
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;

	r->SetViewport( &viewPort );
	r->BeginScene();
	r->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );

	RECT rcDst = 
	{
		viewPort.X, viewPort.Y, viewPort.X+viewPort.Width, viewPort.Y + viewPort.Height
	};

	RECT rcSrc =
	{
		0, 0, viewPort.Width, viewPort.Height
	};

	GetDrawer()->FillRect2D(rcDst, 0);

	FLOAT fAspect = ((FLOAT)viewPort.Width) / (float)viewPort.Height;
	camera.SetProjParams( D3DX_PI/180*45.0f, fAspect, 1.0f, 12000.0f );

	D3DXMATRIX matView;
	D3DXMATRIX matWorld, matOldWorld;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMATRIX matTransform1;

	static float x = 0.f, y = -18.f, z = -1.8f;
	DWORD dwTime = HQ_TimeGetTime();
	if( pAnim )
	{
		pAnim->SetPosition( x, y, z );
		pAnim->CalcTransformMatrix( (MeMatrix*)&matTransform1 );
		pAnim->Update( dwTime, (MeMatrix*)&matTransform1 );
		pAnim->UpdateComponents( dwTime, (MeMatrix*)&matTransform1 );
	}

	static float fDist = 22.79;
	static float fRotate = 0.0f;
	static float fRotateX = 0.98199f;
	static D3DXVECTOR3 vEyePt( 0,-1.2f,1.7f );
	static D3DXVECTOR3 vLookatPt( 0.0f,0.0f,0.0f );

	D3DXVECTOR3 vDist = vEyePt-vLookatPt;
	D3DXVec3Normalize( &vDist, &vDist );

	D3DXVECTOR3 vXAxis( 1, 0, 0 );
	D3DXMATRIX matRotX;
	D3DXMatrixRotationAxis(
		&matRotX,
		&vXAxis,
		fRotateX );

	D3DXVec3TransformCoord( &vDist, &vDist, &matRotX );

	D3DXVECTOR3 vZAxis( 0, 0, -1 );
	D3DXMATRIX matRotZ;
	D3DXMatrixRotationAxis(
		&matRotZ,
		&vZAxis,
		fRotate );

	D3DXVec3TransformCoord( &vDist, &vDist, &matRotZ );

	D3DXVECTOR3 vPos( 0, 0, 0 );
	camera.SetViewParams( vPos+vDist*fDist, vPos, D3DXVECTOR3( 0, 0, 1 ) );
	r->SetTransform( D3DTS_VIEW, (FLOAT*)&camera.GetViewMatrix() );
	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&camera.GetProjMatrix() );
	r->SetEyePt( (float*)&vEyePt );	
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
	r->SetRenderState( D3DRS_LIGHTING, TRUE );	
	r->SetRenderState( D3DRS_FOGENABLE , false );	

	bool bUseShader = graphics::ShaderManager::instance()->isUseShader();

	RendererDx* pRendererDx = (RendererDx*)r;
	D3DXVECTOR3 vOldLightDir = pRendererDx->GetLightDir( LIGHT_INDEX_TERRAIN );
	D3DXVECTOR3 vNewLightDir = vOldLightDir;	
	vNewLightDir = vDist;
	D3DXVec3Normalize( &vNewLightDir, &vNewLightDir );
	D3DLIGHT9 kOldLight = SwGlobal::GetRender()->GetD9Light();
	D3DLIGHT9 kLight;
	kLight.Type = D3DLIGHT_DIRECTIONAL;	
	kLight.Ambient = D3DXCOLOR( 0.6f, 0.6f, 0.6f, 1.0f );
	kLight.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	kLight.Specular = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	kLight.Direction = vNewLightDir;	
	pRendererDx->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kLight );
	Config::SetCamera(&camera);

	pAnim->SetRotationZ( fRotateZ );
	pAnim->SetUpperRot( fRotateZ );

	pAnim->Render( 1.0f );
	GetEngine()->GetRenderer()->Flush( eSortByFarZ );
	MeRenderManager::Instance()->DoRender(false);

	Config::SetCamera(getwsCamera()->GetMeCamera());
	pRendererDx->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kOldLight );

	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&getwsCamera()->GetMeCamera()->GetProjMatrix()  );
	r->SetTransform( D3DTS_VIEW, (FLOAT*)&getwsCamera()->GetMeCamera()->GetViewMatrix()  );
	r->EndScene();

	getwsCamera()->ResetViewport();
}

void CUI_ID_FRAME_SuAnimalPullulate::RefreshItemInfo()
{
	if (!m_pID_FRAME_SuAnimalPullulate) return;
	PetSelectChange(m_pID_LIST_ShouLan->GetCurSelIndex());
	m_pID_FRAME_SuAnimalPullulate->SetRedraw();
}

void CUI_ID_FRAME_SuAnimalPullulate::RefreshMoney()
{
	if (!m_pID_FRAME_SuAnimalPullulate) return;
	std::string text;
	text.clear();
	if (m_pID_TEXT_Money1)
	{
		thePlayerRole.GetGSCStringFromCurrentMoney(text);
		*m_pID_TEXT_Money1 = text;
	}
	if (m_pID_TEXT_Money2)
	{
		thePlayerRole.GetGSCStringFromCurrentJiaoZi(text);
		*m_pID_TEXT_Money2 = text;
	}
}

bool CUI_ID_FRAME_SuAnimalPullulate::UIPetPull_LeftLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_SuAnimalPullulate.SetRotate(true);
	return true;
}
bool CUI_ID_FRAME_SuAnimalPullulate::UIPetPull_RightLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_SuAnimalPullulate.SetRotate(true);
	return true;
}