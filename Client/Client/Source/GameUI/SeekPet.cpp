/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\SeekPet.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SeekPet.h"
#include "Skill.h"
#include "ExpStage.h"
#include "UIMgr.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Engine/RendererDX.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/SwGlobal.h"
#include "wsRender.h"
#include "GameMain.h"
#include "baseProperty.h"
#include "wsCamera.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "MountStrengthenConfig.h"

static bool UISeekPet_RightLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_SeekPet.SetRotate(true);
	return true;
}

static bool UISeekPet_LeftLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_SeekPet.SetRotate(true);
	return true;
}

CUI_ID_FRAME_SeekPet s_CUI_ID_FRAME_SeekPet;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SeekPet, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SeekPet, OnFrameRender )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_BUTTON_CLOSEOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_BUTTON_ChuZhanOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LIST_ShouLanOnListSelectChange )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_BUTTON_XiuXiOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_BUTTON_FangShengOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_ZhuDongOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_ZhuDongOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_ZhuDongOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_ZhuDongOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_BeiDongOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_BeiDongOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_BeiDongOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_BeiDongOnIconRButtonUp )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip1OnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip1OnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip1OnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip1OnIconRButtonUp )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip2OnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip2OnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip2OnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip2OnIconRButtonUp )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip3OnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip3OnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip3OnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_LISTIMG_Equip3OnIconRButtonUp )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_BUTTON_GaiMingOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekPet, ID_BUTTON_LeftOnButtonClick )
CUI_ID_FRAME_SeekPet::CUI_ID_FRAME_SeekPet()
{
	// Member
	ResetMembers();
	m_pPlayerAnim = NULL;
	m_pPlayer = NULL;
}
void CUI_ID_FRAME_SeekPet::ResetMembers()
{
	m_pID_FRAME_SeekPet = NULL;
	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_TEXT_LiLiang = NULL;
// 	m_pID_TEXT_Minjie = NULL;
// 	m_pID_TEXT_TiZhi = NULL;
// 	m_pID_TEXT_ShuFa = NULL;
	//m_pID_TEXT_JingGu = NULL;
	//m_pID_TEXT_ZhuDong = NULL;
	//m_pID_TEXT_KuaiLe = NULL;
// 	m_pID_BUTTON_ChuZhan = NULL;
	//m_pID_TEXT_DengJi = NULL;
	//m_pID_TEXT_CZ = NULL;
	m_pID_TEXT_MJ = NULL;
	m_pID_TEXT_LL = NULL;
	m_pID_TEXT_TZ = NULL;
	m_pID_TEXT_SF = NULL;
	//m_pID_TEXT_JG = NULL;
	m_pID_TEXT_DJ = NULL;
	m_pID_TEXT_KLD = NULL;
	m_pID_TEXT_name = NULL;
	m_pID_TEXT_Point = NULL;
	m_pID_TEXT_Generation = NULL;
	//m_pID_TEXT_liliangZZ = NULL;
	m_pID_TEXT_LLZZ = NULL;
	//m_pID_TEXT_jianrenZZ = NULL;
	m_pID_TEXT_JRZZ = NULL;
	//m_pID_TEXT_TiZhiZZ = NULL;
	m_pID_TEXT_TZZZ = NULL;
	//m_pID_TEXT_ShiFaZZ = NULL;
	m_pID_TEXT_SFZZ = NULL;
// 	m_pID_TEXT_JingGuZZ = NULL;
// 	m_pID_TEXT_JGZZ = NULL;
	//m_pID_TEXT_BeiDongZ = NULL;
	m_pID_LIST_ShouLan = NULL;
// 	m_pID_BUTTON_XiuXi = NULL;
	m_pID_TEXT_SYDJ = NULL;
	//m_pID_BUTTON_FangSheng = NULL;
	//m_pID_TEXT_ExpZ = NULL;
	m_pID_PICTURE_Yingxiang = NULL;
	m_pID_LISTIMG_ZhuDong = NULL;
	m_pID_LISTIMG_BeiDong = NULL;
	//m_pID_LISTIMG_Equip1 = NULL;
//	m_pID_PROGRESS_PetExp = NULL;
	m_pID_TEXT_Exp = NULL;
// 	m_pID_LISTIMG_Equip2 = NULL;
// 	m_pID_LISTIMG_Equip3 = NULL;
	//m_pID_BUTTON_GaiMing = NULL;
//	m_pID_TEXT_Wuxing = NULL;
	//m_pID_TEXT_WX = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	//m_pID_TEXT_TakeNumZ = NULL;
	//m_pID_TEXT_ExpZZ = NULL;
	m_pID_TEXT_TakeNum = NULL;
	//m_pID_TEXT_Exp2 = NULL;
	m_pID_LISTIMG_QiCheng = NULL;
	m_pID_TEXT_MountName = NULL;
// 	m_pID_PICTURE_Quality1 = NULL;
// 	m_pID_PICTURE_Quality2 = NULL;
// 	m_pID_PICTURE_Quality3 = NULL;
// 	m_pID_PICTURE_Quality4 = NULL;
// 	m_pID_PICTURE_Quality5 = NULL;
	m_pID_TEXT_TransferTotal = NULL;
}
// Frame
bool CUI_ID_FRAME_SeekPet::OnFrameRun()
{
	if( IsVisable() )
	{
		if (m_bRotate && m_pID_BUTTON_Right->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			/*m_fRotateZ += 1.5f * theHeroGame.GetFrameElapsedTime();*/
			RenderAnim_RotateZ(true, 0.05);
		}
		else if (m_bRotate && m_pID_BUTTON_Left->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			/*m_fRotateZ -= 1.5f * theHeroGame.GetFrameElapsedTime();*/
			RenderAnim_RotateZ(false, 0.05);
		}
		else
			m_bRotate = false;
	}
	return true;
}
bool CUI_ID_FRAME_SeekPet::OnFrameRender()
{
	/*GetEngine()->GetRenderer()->EndScene();
	RenderViewport();
	GetEngine()->GetRenderer()->BeginScene();*/
	RECT rc;
	m_pID_PICTURE_Yingxiang->GetRealRect(&rc);
	RenderAnim_Update(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, D3DXVECTOR3(0, -6, 0));
	RenderAnim(D3DXVECTOR3(0, -2, -1.2), Config::m_fMdlSpaceScale * 1.0);
	return true;
}
// Button
// bool CUI_ID_FRAME_SeekPet::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return true;
// }
// Button
bool CUI_ID_FRAME_SeekPet::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	return true;
}
// Button
// bool CUI_ID_FRAME_SeekPet::ID_BUTTON_ChuZhanOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return true;
// }
// List
void CUI_ID_FRAME_SeekPet::ID_LIST_ShouLanOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_SeekPet )
		return;

	//add by yanli  2010-9-17
	
}
// Button
// bool CUI_ID_FRAME_SeekPet::ID_BUTTON_XiuXiOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return true;
// }
// Button
// bool CUI_ID_FRAME_SeekPet::ID_BUTTON_FangShengOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_ZhuDongOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_ZhuDongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_ZhuDongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_ZhuDongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_BeiDongOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_BeiDongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_BeiDongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_BeiDongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	return false;
}
// ListImg / ListEx
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
// 														 ControlIconDrag::S_ListImg* pItemDrag,
// 														 ControlIconDrag::S_ListImg* pItemSrc )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// // ListImg / ListEx
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
// 														 ControlIconDrag::S_ListImg* pItemDrag,
// 														 ControlIconDrag::S_ListImg* pItemSrc )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// // ListImg / ListEx
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
// 														 ControlIconDrag::S_ListImg* pItemDrag,
// 														 ControlIconDrag::S_ListImg* pItemSrc )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_SeekPet::ID_LISTIMG_Equip3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return false;
// }
// Button
// bool CUI_ID_FRAME_SeekPet::ID_BUTTON_GaiMingOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_SeekPet )
// 		return false;
// 	return true;
// }
// Button
bool CUI_ID_FRAME_SeekPet::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SeekPet::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	m_bRotate = false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SeekPet::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SeekPet.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SeekPet.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SeekPet::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SeekPet, s_CUI_ID_FRAME_SeekPetOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SeekPet, s_CUI_ID_FRAME_SeekPetOnFrameRender );
	//theUiManager.OnButtonClick( ID_FRAME_SeekPet, ID_BUTTON_help, s_CUI_ID_FRAME_SeekPetID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeekPet, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SeekPetID_BUTTON_CLOSEOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_SeekPet, ID_BUTTON_ChuZhan, s_CUI_ID_FRAME_SeekPetID_BUTTON_ChuZhanOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_SeekPet, ID_LIST_ShouLan, s_CUI_ID_FRAME_SeekPetID_LIST_ShouLanOnListSelectChange );
// 	theUiManager.OnButtonClick( ID_FRAME_SeekPet, ID_BUTTON_XiuXi, s_CUI_ID_FRAME_SeekPetID_BUTTON_XiuXiOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_SeekPet, ID_BUTTON_FangSheng, s_CUI_ID_FRAME_SeekPetID_BUTTON_FangShengOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SeekPet, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SeekPetID_LISTIMG_ZhuDongOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeekPet, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SeekPetID_LISTIMG_ZhuDongOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeekPet, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SeekPetID_LISTIMG_ZhuDongOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeekPet, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SeekPetID_LISTIMG_ZhuDongOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SeekPet, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SeekPetID_LISTIMG_BeiDongOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeekPet, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SeekPetID_LISTIMG_BeiDongOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeekPet, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SeekPetID_LISTIMG_BeiDongOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeekPet, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SeekPetID_LISTIMG_BeiDongOnIconRButtonUp );
// 	theUiManager.OnIconDragOn( ID_FRAME_SeekPet, ID_LISTIMG_Equip1, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip1OnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_SeekPet, ID_LISTIMG_Equip1, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip1OnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_SeekPet, ID_LISTIMG_Equip1, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip1OnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_SeekPet, ID_LISTIMG_Equip1, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip1OnIconRButtonUp );
// 	theUiManager.OnIconDragOn( ID_FRAME_SeekPet, ID_LISTIMG_Equip2, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip2OnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_SeekPet, ID_LISTIMG_Equip2, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip2OnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_SeekPet, ID_LISTIMG_Equip2, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip2OnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_SeekPet, ID_LISTIMG_Equip2, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip2OnIconRButtonUp );
// 	theUiManager.OnIconDragOn( ID_FRAME_SeekPet, ID_LISTIMG_Equip3, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip3OnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_SeekPet, ID_LISTIMG_Equip3, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip3OnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_SeekPet, ID_LISTIMG_Equip3, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip3OnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_SeekPet, ID_LISTIMG_Equip3, s_CUI_ID_FRAME_SeekPetID_LISTIMG_Equip3OnIconRButtonUp );
	//theUiManager.OnButtonClick( ID_FRAME_SeekPet, ID_BUTTON_GaiMing, s_CUI_ID_FRAME_SeekPetID_BUTTON_GaiMingOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeekPet, ID_BUTTON_Right, s_CUI_ID_FRAME_SeekPetID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeekPet, ID_BUTTON_Left, s_CUI_ID_FRAME_SeekPetID_BUTTON_LeftOnButtonClick );

	m_pID_FRAME_SeekPet = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SeekPet );
// 	m_pID_PICTURE_DI2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_DI2 );
// 	m_pID_PICTURE_29797 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_29797 );
// 	m_pID_PICTURE_2574 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_2574 );
// 	m_pID_PICTURE_174 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_174 );
// 	m_pID_PICTURE_11751 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_11751 );
// 	m_pID_PICTURE_29700 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_29700 );
// 	m_pID_PICTURE_14908 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_14908 );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_BUTTON_help );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_BUTTON_CLOSE );
// 	m_pID_PICTURE_title2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_title2 );
// 	m_pID_PICTURE_ExpWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_ExpWall );
// 	m_pID_TEXT_ShiYongDengJi = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_ShiYongDengJi );
// 	m_pID_TEXT_NiChen = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_NiChen );
	//m_pID_PICTURE_Yingxiang2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_Yingxiang2 );
	//m_pID_TEXT_ChengZhang = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_ChengZhang );
// 	m_pID_TEXT_LiLiang = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_LiLiang );
// 	m_pID_TEXT_Minjie = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_Minjie );
// 	m_pID_TEXT_TiZhi = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_TiZhi );
// 	m_pID_TEXT_ShuFa = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_ShuFa );
	//m_pID_TEXT_JingGu = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_JingGu );
//	m_pID_TEXT_ZhuDong = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_ZhuDong );
	//m_pID_TEXT_KuaiLe = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_KuaiLe );
	//m_pID_BUTTON_ChuZhan = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_BUTTON_ChuZhan );
	//m_pID_TEXT_DengJi = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_DengJi );
	//m_pID_TEXT_CZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_CZ );
	m_pID_TEXT_MJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_MJ );
	m_pID_TEXT_LL = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_LL );
	m_pID_TEXT_TZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_TZ );
	m_pID_TEXT_SF = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_SF );
	//m_pID_TEXT_JG = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_JG );
	m_pID_TEXT_DJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_DJ );
	m_pID_TEXT_KLD = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_KLD );
	m_pID_TEXT_name = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_name );
	m_pID_TEXT_Point = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_Point );
	m_pID_TEXT_Generation = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_Generation );
	//m_pID_TEXT_liliangZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_liliangZZ );
	m_pID_TEXT_LLZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_LLZZ );
	//m_pID_TEXT_jianrenZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_jianrenZZ );
	m_pID_TEXT_JRZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_JRZZ );
	//m_pID_TEXT_TiZhiZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_TiZhiZZ );
	m_pID_TEXT_TZZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_TZZZ );
	//m_pID_TEXT_ShiFaZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_ShiFaZZ );
	m_pID_TEXT_SFZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_SFZZ );
// 	m_pID_TEXT_JingGuZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_JingGuZZ );
// 	m_pID_TEXT_JGZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_JGZZ );
//	m_pID_TEXT_BeiDongZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_BeiDongZ );
	m_pID_LIST_ShouLan = (ControlList*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_LIST_ShouLan );
// 	m_pID_BUTTON_XiuXi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_BUTTON_XiuXi );
 	m_pID_TEXT_SYDJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_SYDJ );
// 	m_pID_BUTTON_FangSheng = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_BUTTON_FangSheng );
// 	m_pID_TEXT_ExpZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_ExpZ );
	m_pID_PICTURE_Yingxiang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_Yingxiang );
	m_pID_LISTIMG_ZhuDong = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_LISTIMG_ZhuDong );
	m_pID_LISTIMG_BeiDong = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_LISTIMG_BeiDong );
	//m_pID_LISTIMG_Equip1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_LISTIMG_Equip1 );
	//m_pID_PROGRESS_PetExp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PROGRESS_PetExp );
	m_pID_TEXT_Exp = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_Exp );
// 	m_pID_LISTIMG_Equip2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_LISTIMG_Equip2 );
// 	m_pID_LISTIMG_Equip3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_LISTIMG_Equip3 );
// 	m_pID_BUTTON_GaiMing = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_BUTTON_GaiMing );
// 	m_pID_TEXT_Wuxing = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_Wuxing );
// 	m_pID_TEXT_WX = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_WX );
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_BUTTON_Right );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_BUTTON_Left );
	//m_pID_TEXT_TakeNumZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_TakeNumZ );
	//m_pID_TEXT_ExpZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_ExpZZ );
	m_pID_TEXT_TakeNum = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_TakeNum );
	//m_pID_TEXT_Exp2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_Exp2 );
	m_pID_LISTIMG_QiCheng = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_LISTIMG_QiCheng );
	m_pID_TEXT_MountName = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_MountName );
// 	m_pID_PICTURE_Quality1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_Quality1 );
// 	m_pID_PICTURE_Quality2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_Quality2 );
// 	m_pID_PICTURE_Quality3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_Quality3 );
// 	m_pID_PICTURE_Quality4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_Quality4 );
// 	m_pID_PICTURE_Quality5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_Quality5 );
// 	m_pID_PICTURE_Quality5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_PICTURE_Quality5 );
	m_pID_LISTIMG_PetIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_LISTIMG_PetIcon );
	m_pID_TEXT_TransferTotal = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekPet, ID_TEXT_TransferTotal );

	//assert( m_pID_FRAME_SeekPet );
	//assert( m_pID_PICTURE_DI2 );
	//assert( m_pID_PICTURE_29797 );
	//assert( m_pID_PICTURE_2574 );
	//assert( m_pID_PICTURE_174 );
	//assert( m_pID_PICTURE_11751 );
	//assert( m_pID_PICTURE_29700 );
	//assert( m_pID_PICTURE_14908 );
	//assert( m_pID_BUTTON_help );
	//assert( m_pID_BUTTON_CLOSE );
	//assert( m_pID_PICTURE_title2 );
	//assert( m_pID_PICTURE_ExpWall );
	//assert( m_pID_TEXT_ShiYongDengJi );
	//assert( m_pID_TEXT_NiChen );
	//assert( m_pID_PICTURE_Yingxiang2 );
	//assert( m_pID_TEXT_ChengZhang );
	//assert( m_pID_TEXT_LiLiang );
	//assert( m_pID_TEXT_Minjie );
	//assert( m_pID_TEXT_TiZhi );
	//assert( m_pID_TEXT_ShuFa );
	//assert( m_pID_TEXT_JingGu );
	//assert( m_pID_TEXT_ZhuDong );
	//assert( m_pID_TEXT_KuaiLe );
	//assert( m_pID_BUTTON_ChuZhan );
	//assert( m_pID_TEXT_DengJi );
	//assert( m_pID_TEXT_CZ );
	//assert( m_pID_TEXT_MJ );
	//assert( m_pID_TEXT_LL );
	//assert( m_pID_TEXT_TZ );
	//assert( m_pID_TEXT_SF );
	//assert( m_pID_TEXT_JG );
	//assert( m_pID_TEXT_DJ );
	//assert( m_pID_TEXT_KLD );
	//assert( m_pID_TEXT_name );
	//assert( m_pID_TEXT_Point );
	//assert( m_pID_TEXT_Generation );
	//assert( m_pID_TEXT_liliangZZ );
	//assert( m_pID_TEXT_LLZZ );
	//assert( m_pID_TEXT_jianrenZZ );
	//assert( m_pID_TEXT_JRZZ );
	//assert( m_pID_TEXT_TiZhiZZ );
	//assert( m_pID_TEXT_TZZZ );
	//assert( m_pID_TEXT_ShiFaZZ );
	//assert( m_pID_TEXT_SFZZ );
	//assert( m_pID_TEXT_JingGuZZ );
	//assert( m_pID_TEXT_JGZZ );
	//assert( m_pID_TEXT_BeiDongZ );
	//assert( m_pID_LIST_ShouLan );
	//assert( m_pID_BUTTON_XiuXi );
	assert( m_pID_TEXT_SYDJ );
	//assert( m_pID_BUTTON_FangSheng );
	//assert( m_pID_TEXT_ExpZ );
	//assert( m_pID_PICTURE_Yingxiang );
	//assert( m_pID_LISTIMG_ZhuDong );
	//assert( m_pID_LISTIMG_BeiDong );
	//assert( m_pID_LISTIMG_Equip1 );
	//assert( m_pID_PROGRESS_PetExp );
	//assert( m_pID_TEXT_Exp );
	//assert( m_pID_LISTIMG_Equip2 );
	//assert( m_pID_LISTIMG_Equip3 );
	//assert( m_pID_BUTTON_GaiMing );
	//assert( m_pID_TEXT_Wuxing );
	//assert( m_pID_TEXT_WX );
	//assert( m_pID_BUTTON_Right );
	//assert( m_pID_BUTTON_Left );
	//assert( m_pID_TEXT_TakeNumZ );
	//assert( m_pID_TEXT_ExpZZ );
	//assert( m_pID_TEXT_TakeNum );
	//assert( m_pID_TEXT_Exp2 );
	assert( m_pID_TEXT_TransferTotal );

    m_pID_LISTIMG_ZhuDong->SetEnableCnt( 0 );
	//USE_SCRIPT( eUI_OBJECT_SeekPet, this );

	SetVisable(false);
	m_pID_BUTTON_Right->SetLButtonDownFun(UISeekPet_RightLBD);
	m_pID_BUTTON_Left->SetLButtonDownFun(UISeekPet_LeftLBD);
	
	/*m_pPlayerAnim = MeNew CPlayerAnim;
	m_pPlayer = MeNew CPlayer;
	m_pPlayer->SetAnim( m_pPlayerAnim );
	m_pPlayerAnim->SetPlayer( m_pPlayer );
	theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayer );*/

	RenderAnim_Create(CUIRenderAnim::RTWUI_MOUNT, -4.61);

	m_pID_LISTIMG_PetIcon->SetScrollBarEnable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SeekPet::_UnLoadUI()
{
	/*if (m_pPlayer)
	{
		theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer( m_pPlayer );
		m_pPlayer->Destroy();	
		delete m_pPlayer;
		m_pPlayer = 0;
		m_pPlayerAnim = 0;
	}*/
	CLOSE_SCRIPT( eUI_OBJECT_SeekPet );
	ResetMembers();
	RenderAnim_Destroy();
	return theUiManager.RemoveFrame( "Data\\UI\\SeekPet.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SeekPet::_IsVisable()
{
	if( !m_pID_FRAME_SeekPet )
		return false;
	return m_pID_FRAME_SeekPet->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SeekPet::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_SeekPet )
		return;
	m_pID_FRAME_SeekPet->SetVisable( bVisable );
	m_fRotateZ = D3DX_PI / 2;
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
static void SetFloatText(ControlText* pText, float v)
{
	char szTemp[32];
	sprintf( szTemp, "%.2f", v );
	pText->SetText(szTemp);
}

static void SetIntText(ControlText* pText, float v)
{
	pText->SetText(v);
}

void CUI_ID_FRAME_SeekPet::SetMount(SMountItem& mount)
{
	if( !m_pID_FRAME_SeekPet )
		return;
	m_pID_LIST_ShouLan->Clear();
	m_pID_LISTIMG_PetIcon->Clear();

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

	m_pID_TEXT_Exp->SetText("");	// 经验
	m_pID_TEXT_TransferTotal->SetText("");//转化

	m_pID_LISTIMG_ZhuDong->Clear();
	m_pID_LISTIMG_BeiDong->Clear();
	m_pID_LISTIMG_QiCheng->Clear();

	m_pID_TEXT_MountName->SetText(""); // 宠物原始名称

	if (mount.baseInfo.id != InvalidLogicNumber)
	{
		ControlList::S_List sData;

		// 取颜色
		ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( mount.baseInfo.id );			
		DWORD dwColor = 0;
		if( pCommon )
		{
			dwColor = S_IconInfoHero::GetQualityColor( pCommon->ustLevel );
		}

		sData.SetData( mount.baseInfo.szName, mount.baseInfo.id, 0, dwColor );
		m_pID_LIST_ShouLan->AddItem(&sData,NULL, false);

		m_pID_TEXT_DJ->SetText(mount.baseInfo.level);									// 等级

		char buf[64];
		sprintf( buf, "%d/%d", mount.baseInfo.hp, mount.baseInfo.hpMax );
		m_pID_TEXT_KLD->SetText(buf);													// 快乐度

		SetIntText(m_pID_TEXT_LL,     mount.baseInfo.currentAttribute[EBaseAttr_Strength]);	    // 力量
		SetIntText(m_pID_TEXT_MJ,     mount.baseInfo.currentAttribute[EBaseAttr_Agility]);		// 敏捷
		SetIntText(m_pID_TEXT_TZ,     mount.baseInfo.currentAttribute[EBaseAttr_Stamina]);		// 体质
		SetIntText(m_pID_TEXT_SF,     mount.baseInfo.currentAttribute[EBaseAttr_Intelligence]);		// 术法

		SetIntText(m_pID_TEXT_LLZZ,   mount.baseInfo.aptitudeAttribute[EBaseAttr_Strength]);	// 力量资质
		SetIntText(m_pID_TEXT_JRZZ,   mount.baseInfo.aptitudeAttribute[EBaseAttr_Agility]);		// 敏捷资质
		SetIntText(m_pID_TEXT_TZZZ,   mount.baseInfo.aptitudeAttribute[EBaseAttr_Stamina]);		// 体质资质
		SetIntText(m_pID_TEXT_SFZZ,   mount.baseInfo.aptitudeAttribute[EBaseAttr_Intelligence]);		// 术法资质
		SetIntText(m_pID_TEXT_Point,   mount.baseInfo.nPotentialPoint);		// 潜力点
		m_pID_TEXT_name->SetText(mount.baseInfo.szName);
		m_pID_TEXT_Generation->SetText("初代");

		char szTransTemp[24]={0};
		sprintf_s(szTransTemp,sizeof(szTransTemp),"%.0f%%",mount.baseInfo.aptitudeAttribute[EBaseAttr_Strength]);
		m_pID_TEXT_TransferTotal->SetText(szTransTemp);

		// 经验
        __int64 dwTotalExp = theExpStage.GetMountLevelupExp(mount.baseInfo.level );
        __int64 dwLastLevelExp = 0;
        if (mount.baseInfo.level > 1)
        {
            dwLastLevelExp = theExpStage.GetMountLevelupExp(mount.baseInfo.level - 1);
        }
        char szWord[MAX_PATH] = {0};
		MeSprintf_s( szWord, sizeof(szWord)/sizeof(char) - 1, "%I64u/%I64u", mount.baseInfo.exp - dwLastLevelExp, dwTotalExp - dwLastLevelExp );
		m_pID_TEXT_Exp->SetText( szWord );

		// 添加icon到控件
		ControlListImage::S_ListImg stItemImage;
		stItemImage.SetData( mount.baseInfo.id, 1 );
		stItemImage.m_pkIconInfo->SetOnlyId( mount.baseInfo.guid );

        stItemImage.m_pkIconInfo->SetUsableEffEnable( false );
		m_pID_LISTIMG_PetIcon->SetItem( &stItemImage );

		ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( mount.baseInfo.id );
		if (pDrome)
		{
            DWORD dwDJColor = 0xffffffff;
            if( pDrome->takeLevel > thePlayerRole.GetLevel() )
                dwDJColor = 0xffff0000;

			m_pID_TEXT_SYDJ->SetText(pDrome->takeLevel, dwDJColor);
			m_pID_TEXT_MountName->SetText(pDrome->GetName(), dwColor); // 宠物原始名称

		}

		// Skill
		RefreshMountSkill(mount);

		// Set display model
		ChangeModel(mount);
	}
}

void CUI_ID_FRAME_SeekPet::RefreshMountSkill(SMountItem &mount)
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
    m_pID_LISTIMG_ZhuDong->SetEnableCnt( mount.skillInfo.initiativeSkillNumber );
}

void CUI_ID_FRAME_SeekPet::RenderViewport()
{
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	IRenderer* r = GetEngine()->GetRenderer();

	RECT rt;

	m_pID_PICTURE_Yingxiang->GetRealRect( &rt );

	m_ViewPort.X = rt.left;
	m_ViewPort.Y = rt.top;
	m_ViewPort.Width = rt.right - rt.left;
	m_ViewPort.Height = rt.bottom - rt.top;
	m_ViewPort.MinZ = 0.0f;
	m_ViewPort.MaxZ = 1.0f;

	r->SetViewport( &m_ViewPort );
	r->BeginScene();
	r->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );

	RECT rcDst = 
	{
		m_ViewPort.X, m_ViewPort.Y, m_ViewPort.X+m_ViewPort.Width, m_ViewPort.Y + m_ViewPort.Height
	};

	RECT rcSrc =
	{
		0, 0, m_ViewPort.Width, m_ViewPort.Height
	};

	GetDrawer()->FillRect2D(rcDst, 0);

	FLOAT fAspect = ((FLOAT)m_ViewPort.Width) / (float)m_ViewPort.Height;
	m_Camera.SetProjParams( D3DX_PI/180*45.0f, fAspect, 1.0f, 12000.0f );

	D3DXMATRIX matView;
	D3DXMATRIX matWorld, matOldWorld;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMATRIX matTransform1;

	static float x = 0.f, y = -18.f, z = -1.8f;
	CPlayerAnim* pAnim = m_pPlayerAnim;
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
	m_Camera.SetViewParams( vPos+vDist*fDist, vPos, D3DXVECTOR3( 0, 0, 1 ) );
	r->SetTransform( D3DTS_VIEW, (FLOAT*)&m_Camera.GetViewMatrix() );
	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&m_Camera.GetProjMatrix() );
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

	Config::SetCamera(&m_Camera);

	pAnim->SetRotationZ( m_fRotateZ );
	pAnim->SetUpperRot( m_fRotateZ );

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

void CUI_ID_FRAME_SeekPet::ChangeModel(SMountItem &mount)
{
	int nModelId = mount.baseInfo.id;
	int	nResMexID = -1;
	 ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( mount.baseInfo.id );

	if( pDrome )
	{
		nResMexID = pDrome->modelID[mount.baseInfo.level];
		if( nResMexID == -1 )
		{
			assert( false );
			return;
		}
	}
	else
		return;

	/*if( m_pPlayerAnim )
	{
		m_pPlayerAnim->MyChangeModel( nResMexID, TRUE, GettheItemDetail().GetDromeByID( nModelId )->GetSkinName() );
		m_pPlayerAnim->SetCurAnimType(-1);
	}*/
	RenderAnim_SetModelID(nResMexID);
}

void CUI_ID_FRAME_SeekPet::SetCardMountByIdLevel( int mountId, short level )
{
	if( !m_pID_FRAME_SeekPet )
		return;
	m_pID_LIST_ShouLan->Clear();
	m_pID_LISTIMG_PetIcon->Clear();

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

	m_pID_TEXT_Exp->SetText("");	// 经验
	m_pID_TEXT_TransferTotal->SetText("");//转化

	m_pID_LISTIMG_ZhuDong->Clear();
	m_pID_LISTIMG_BeiDong->Clear();
	m_pID_LISTIMG_QiCheng->Clear();

	m_pID_TEXT_MountName->SetText(""); // 宠物原始名称

	if (mountId == InvalidLogicNumber)
		return;
	ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( mountId );
	if ( !pDrome )
		return;

	ControlList::S_List sData;
	// 取颜色
	ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( mountId );			
	DWORD dwColor = 0;
	if( pCommon )
	{
		dwColor = S_IconInfoHero::GetQualityColor( pCommon->ustLevel );
	}

	sData.SetData( pDrome->GetName(), mountId, 0, dwColor );
	m_pID_LIST_ShouLan->AddItem(&sData,NULL, false);

	m_pID_TEXT_DJ->SetText(level);	

	// 添加icon到控件
	ControlListImage::S_ListImg stItemImage;
	stItemImage.SetData( mountId, 1 );
	//stItemImage.m_pkIconInfo->SetOnlyId( mount.baseInfo.guid );
	stItemImage.m_pkIconInfo->SetUsableEffEnable( false );
	m_pID_LISTIMG_PetIcon->SetItem( &stItemImage );

	DWORD dwDJColor = 0xffffffff;
	if( pDrome->takeLevel > thePlayerRole.GetLevel() )
		dwDJColor = 0xffff0000;

	m_pID_TEXT_SYDJ->SetText(pDrome->takeLevel, dwDJColor);
	m_pID_TEXT_name->SetText(pDrome->GetName()); // 宠物原始名称

	float currentAttribute[EBaseAttr_MaxSize];

	 for ( int i=0; i < EBaseAttr_MaxSize; ++i )
		 currentAttribute[i] = pDrome->baseMax[i];

	 const MountStrengthenData* pData = theMountStrengthenConfig.GetMountStrengthenData(mountId);
	 if ( level > 0 && pData )
	 {
		 for ( int i=0; i < level; ++i)
		 {
			 currentAttribute[EBaseAttr_Strength] += pData->GetStrength(i);
			 currentAttribute[EBaseAttr_Agility] += pData->GetAgility(i);
			 currentAttribute[EBaseAttr_Stamina] += pData->GetStamina(i);
			 currentAttribute[EBaseAttr_Intelligence] += pData->GetIntelligence(i);
		 }
	 }

	 SetIntText(m_pID_TEXT_LL,     currentAttribute[EBaseAttr_Strength]);	    // 力量
	 SetIntText(m_pID_TEXT_MJ,     currentAttribute[EBaseAttr_Agility]);		// 敏捷
	 SetIntText(m_pID_TEXT_TZ,     currentAttribute[EBaseAttr_Stamina]);		// 体质
	 SetIntText(m_pID_TEXT_SF,     currentAttribute[EBaseAttr_Intelligence]);		// 术法

	 char szTransTemp[24]={0};
	 sprintf_s(szTransTemp,sizeof(szTransTemp),"%.0f%%",pDrome->addMax[EBaseAttr_Strength]);
	 m_pID_TEXT_TransferTotal->SetText(szTransTemp);

	 int	nResMexID = -1;
	 nResMexID = pDrome->modelID[level];
	 if( nResMexID == -1 )
		 return;
	 RenderAnim_SetModelID(nResMexID);
}