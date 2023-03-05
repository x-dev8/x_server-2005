#include <assert.h>
#include "MeUi/UiManager.h"
#include "SeeSuAnimal.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Common.h"
#include "Skill.h"
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
#include "PetSettingConfig.h"
#include "SuAnimal.h"
CUI_ID_FRAME_SeeSuAnimal s_CUI_ID_FRAME_SeeSuAnimal;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SeeSuAnimal, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SeeSuAnimal, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_ZhuDongOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_ZhuDongOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_ZhuDongOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_ZhuDongOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_CureOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetIconOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_QiChengOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_QiChengOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_QiChengOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_QiChengOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_GaiMingOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_BeiDongOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_BeiDongOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_BeiDongOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_BeiDongOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_FangShengOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_XiuXiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_LockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_RenewOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_ChuZhanOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_UnLockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_HELPOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LIST_ShouLanOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LIST_WarOnListSelectChange )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_FeedOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_ZengShouOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_ZhaoHuiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_TuJianOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_CHECKBOX_BaseOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_CHECKBOX_ZZUpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_CHECKBOX_ZZDownOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_CHECKBOX_ZhanDouOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusLiLiangOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractLiLiangOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_ConfirmOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusMinJieOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractMinJieOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusTiZhiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractTiZhiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusZhiLiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractZhiLiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_BUTTON_ChengHaoOnButtonClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquipOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquipOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal,ID_LISTIMG_PetEquipOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquipOnIconRButtonUp )


MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal,ID_LISTIMG_PetEquip1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip1OnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal,ID_LISTIMG_PetEquip2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip2OnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal,ID_LISTIMG_PetEquip3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip3OnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal,ID_LISTIMG_PetEquip4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip4OnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip5OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip5OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal,ID_LISTIMG_PetEquip5OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip5OnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillXTOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillXTOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal,ID_LISTIMG_SkillXTOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillXTOnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillHTOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillHTOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal,ID_LISTIMG_SkillHTOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillHTOnIconRButtonUp )

CUI_ID_FRAME_SeeSuAnimal::CUI_ID_FRAME_SeeSuAnimal()
{
	// Member
	m_pID_FRAME_SeeSuAnimal = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_DJ = NULL;
	m_pID_PICTURE_Yingxiang = NULL;
	m_pID_LISTIMG_ZhuDong = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_TEXT_TakeNum = NULL;
	m_pID_BUTTON_Cure = NULL;
	m_pID_LISTIMG_PetIcon = NULL;
	m_pID_LISTIMG_QiCheng = NULL;
	m_pID_TEXT_MountName = NULL;
	m_pID_BUTTON_GaiMing = NULL;
	m_pID_LISTIMG_BeiDong = NULL;
	m_pID_TEXT_Generation = NULL;
	m_pID_BUTTON_FangSheng = NULL;
	m_pID_BUTTON_XiuXi = NULL;
	m_pID_BUTTON_Lock = NULL;
	m_pID_BUTTON_Renew = NULL;
	m_pID_TEXT_SYDJ = NULL;
	m_pID_BUTTON_ChuZhan = NULL;
	m_pID_BUTTON_UnLock = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_LIST_ShouLan = NULL;
	m_pID_LIST_War = NULL;
	m_pID_PICTURE_XBXiong = NULL;
	m_pID_PICTURE_LeiBieWu = NULL;
	m_pID_TEXT_XingGe = NULL;
	m_pID_TEXT_MountLv = NULL;
	m_pID_PICTURE_XBCi = NULL;
	m_pID_TEXT_Level = NULL;
	m_pID_PROGRESS_Exp = NULL;
	m_pID_PROGRESS_Hp = NULL;
	//m_pID_PROGRESS_Happy = NULL;
	m_pID_PROGRESS_Life = NULL;
	//m_pID_BUTTON_Feed = NULL;
	m_pID_BUTTON_ZengShou = NULL;
	m_pID_BUTTON_ZhaoHui = NULL;
	m_pID_BUTTON_TuJian = NULL;
	m_pID_PICTURE_WXJin = NULL;
	m_pID_PICTURE_WXMu = NULL;
	m_pID_PICTURE_WXShui = NULL;
	m_pID_PICTURE_WXHuo = NULL;
	m_pID_PICTURE_WXTu = NULL;
	m_pID_PICTURE_ZhongZu1 = NULL;
	m_pID_PICTURE_ZhongZu2 = NULL;
	m_pID_TEXT_name = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_CHECKBOX_Base = NULL;
	m_pID_CHECKBOX_ZZUp = NULL;
	m_pID_CHECKBOX_ZZDown = NULL;
	m_pID_CHECKBOX_ZhanDou = NULL;
	m_pID_TEXT_LIL = NULL;
	m_pID_BUTTON_PlusLiLiang = NULL;
	m_pID_BUTTON_SubtractLiLiang = NULL;
	m_pID_TEXT_Star = NULL;
	m_pID_TEXT_LL = NULL;
	m_pID_TEXT_NL = NULL;
	m_pID_TEXT_MJ = NULL;
	m_pID_TEXT_Point = NULL;
	m_pID_BUTTON_Confirm = NULL;
	m_pID_TEXT_Exp = NULL;
	m_pID_TEXT_KLD = NULL;
	//m_pID_TEXT_Happy = NULL;
	m_pID_TEXT_Life = NULL;
	m_pID_TEXT_ZDL = NULL;
	m_pID_BUTTON_PlusMinJie = NULL;
	m_pID_BUTTON_SubtractMinJie = NULL;
	m_pID_BUTTON_PlusTiZhi = NULL;
	m_pID_BUTTON_SubtractTiZhi = NULL;
	m_pID_BUTTON_PlusZhiLi = NULL;
	m_pID_BUTTON_SubtractZhiLi = NULL;
	m_pID_PICTURE_LeiBieFa = NULL;
	m_pID_PICTURE_Base = NULL;
	m_pID_TEXT_ChengZhangLv = NULL;
	m_pID_TEXT_LILZZ = NULL;
	m_pID_TEXT_LLZZ = NULL;
	m_pID_TEXT_NLZZ = NULL;
	m_pID_TEXT_MJZZ = NULL;
	m_pID_PICTURE_ZZ = NULL;
	m_pID_TEXT_DaoHang = NULL;
	m_pID_TEXT_WLGJ = NULL;
	m_pID_TEXT_FSGJ = NULL;
	m_pID_TEXT_WLFY = NULL;
	m_pID_TEXT_FSFY = NULL;
	m_pID_TEXT_MZ = NULL;
	m_pID_TEXT_DB = NULL;
	m_pID_TEXT_HXGJ = NULL;
	m_pID_TEXT_HXFY = NULL;
	m_pID_PICTURE_ZhanDou = NULL;
	m_pID_TEXT_WuXing = NULL;
	m_pID_TEXT_GenGu = NULL;
	m_pID_TEXT_FZCS = NULL;
	m_pID_TEXT_CWName = NULL;
	//m_pID_BUTTON_ChengHao = NULL;
	m_pID_TEXT_ChengHao = NULL;
	m_pID_LISTIMG_PetEquip = NULL;

	m_pID_LISTIMG_PetEquip1 = NULL;
	m_pID_LISTIMG_PetEquip2=NULL;
	m_pID_LISTIMG_PetEquip3=NULL;
	m_pID_LISTIMG_PetEquip4=NULL;
	m_pID_LISTIMG_PetEquip5=NULL;
	m_pID_LISTIMG_SkillXT=NULL;
	m_pID_LISTIMG_SkillHT=NULL;

}
// Frame
bool CUI_ID_FRAME_SeeSuAnimal::OnFrameRun()
{
	if(s_CUI_ID_FRAME_SeeSuAnimal.IsVisable())
	{
		if (m_bRotate && m_pID_BUTTON_Right->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			//m_fRotateZ += 1.5f*theHeroGame.GetFrameElapsedTime();
			RenderAnim_RotateZ(true, 0.05);
		}
		else if (m_bRotate && m_pID_BUTTON_Left->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			//m_fRotateZ -= 1.5f*theHeroGame.GetFrameElapsedTime();
			RenderAnim_RotateZ(false, 0.05);
		}
		else 
			m_bRotate = false;
	}
	
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::OnFrameRender()
{
	/*GetEngine()->GetRenderer()->EndScene();
	RenderViewport();
	GetEngine()->GetRenderer()->BeginScene();*/
	RECT rc;
	m_pID_PICTURE_Yingxiang->GetRealRect( &rc );
	RenderAnim_Update(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, D3DXVECTOR3(0, -7, 0));
	/*
	* Author: 2012-9-13 22:08:49 wangshuai
	* Desc:   老的模型比较大，以新的模型为准，缩放1.0
	*/
	RenderAnim(D3DXVECTOR3(0, -3, -1.0), Config::m_fMdlSpaceScale * 1.4f);
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_ZhuDongOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															  ControlIconDrag::S_ListImg* pItemDrag,
															  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_ZhuDongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_ZhuDongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_ZhuDongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_CureOnButtonClick( ControlObject* pSender )
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															  ControlIconDrag::S_ListImg* pItemDrag,
															  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_QiChengOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															  ControlIconDrag::S_ListImg* pItemDrag,
															  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_QiChengOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_QiChengOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_QiChengOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_GaiMingOnButtonClick( ControlObject* pSender )
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_BeiDongOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															  ControlIconDrag::S_ListImg* pItemDrag,
															  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_BeiDongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_BeiDongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_BeiDongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_FangShengOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_XiuXiOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_LockOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_RenewOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_ChuZhanOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_UnLockOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	return true;
}
// List
void CUI_ID_FRAME_SeeSuAnimal::ID_LIST_ShouLanOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_SeeSuAnimal::ID_LIST_WarOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Button
//bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_FeedOnButtonClick( ControlObject* pSender )
//{
//	return true;
//}

// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_ZengShouOnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_ZhaoHuiOnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_TuJianOnButtonClick( ControlObject* pSender )
{
	return true;
}

// CheckBox
void CUI_ID_FRAME_SeeSuAnimal::ID_CHECKBOX_BaseOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_GroupBase.SetVisible(true);
	m_GroupGrowing.SetVisible(false);
	m_GroupFight.SetVisible(false);
}

// CheckBox
void CUI_ID_FRAME_SeeSuAnimal::ID_CHECKBOX_ZZUpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(m_GroupBase.IsVisible())
		return;

	m_GroupBase.SetVisible(false);
	m_GroupGrowing.SetVisible(true);
	m_GroupFight.SetVisible(false);
}

// CheckBox
void CUI_ID_FRAME_SeeSuAnimal::ID_CHECKBOX_ZZDownOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(m_GroupFight.IsVisible())
		return;

	m_GroupBase.SetVisible(false);
	m_GroupGrowing.SetVisible(true);
	m_GroupFight.SetVisible(false);
}

// CheckBox
void CUI_ID_FRAME_SeeSuAnimal::ID_CHECKBOX_ZhanDouOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_GroupBase.SetVisible(false);
	m_GroupGrowing.SetVisible(false);
	m_GroupFight.SetVisible(true);
}

// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_PlusLiLiangOnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_SubtractLiLiangOnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_ConfirmOnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_PlusMinJieOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_SubtractMinJieOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_PlusTiZhiOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_SubtractTiZhiOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_PlusZhiLiOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_SubtractZhiLiOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SeeSuAnimal::ID_BUTTON_ChengHaoOnButtonClick( ControlObject* pSender )
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SeeSuAnimal::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SeeSuAnimal.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SeeSuAnimal.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SeeSuAnimal::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SeeSuAnimal, s_CUI_ID_FRAME_SeeSuAnimalOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SeeSuAnimal, s_CUI_ID_FRAME_SeeSuAnimalOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_help, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_ZhuDongOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_ZhuDongOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_ZhuDongOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_ZhuDongOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_Right, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_Left, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_LeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_Cure, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_CureOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetIconOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetIconOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetIconOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetIconOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_QiChengOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_QiChengOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_QiChengOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_QiChengOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_GaiMing, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_GaiMingOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_BeiDongOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_BeiDongOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_BeiDongOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_BeiDongOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_FangSheng, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_FangShengOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_XiuXi, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_XiuXiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_Lock, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_LockOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_Renew, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_RenewOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_ChuZhan, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_ChuZhanOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_UnLock, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_UnLockOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_HELP, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_HELPOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_SeeSuAnimal, ID_LIST_ShouLan, s_CUI_ID_FRAME_SeeSuAnimalID_LIST_ShouLanOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_SeeSuAnimal, ID_LIST_War, s_CUI_ID_FRAME_SeeSuAnimalID_LIST_WarOnListSelectChange );
	//theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_Feed, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_FeedOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_ZengShou, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_ZengShouOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_ZhaoHui, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_ZhaoHuiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_TuJian, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_TuJianOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SeeSuAnimal, ID_CHECKBOX_Base, s_CUI_ID_FRAME_SeeSuAnimalID_CHECKBOX_BaseOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SeeSuAnimal, ID_CHECKBOX_ZZUp, s_CUI_ID_FRAME_SeeSuAnimalID_CHECKBOX_ZZUpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SeeSuAnimal, ID_CHECKBOX_ZZDown, s_CUI_ID_FRAME_SeeSuAnimalID_CHECKBOX_ZZDownOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SeeSuAnimal, ID_CHECKBOX_ZhanDou, s_CUI_ID_FRAME_SeeSuAnimalID_CHECKBOX_ZhanDouOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusLiLiang, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_PlusLiLiangOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractLiLiang, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_SubtractLiLiangOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_Confirm, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_ConfirmOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusMinJie, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_PlusMinJieOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractMinJie, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_SubtractMinJieOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusTiZhi, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_PlusTiZhiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractTiZhi, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_SubtractTiZhiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusZhiLi, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_PlusZhiLiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractZhiLi, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_SubtractZhiLiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeeSuAnimal, ID_BUTTON_ChengHao, s_CUI_ID_FRAME_SeeSuAnimalID_BUTTON_ChengHaoOnButtonClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquipOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquipOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquipOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquipOnIconRButtonUp );


	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip1, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip1, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip1, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip1, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip1OnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip2, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip2, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip2, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip2, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip2OnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip3, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip3, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip3, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip3, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip3OnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip4, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip4, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip4, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip4, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip4OnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip5, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip5OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip5, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip5OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip5, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip5OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip5, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_PetEquip5OnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillXT, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_SkillXTOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillXT, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_SkillXTOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillXT, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_SkillXTOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillXT, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_SkillXTOnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillHT, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_SkillHTOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillHT, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_SkillHTOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillHT, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_SkillHTOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillHT, s_CUI_ID_FRAME_SeeSuAnimalID_LISTIMG_SkillHTOnIconRButtonUp );

	m_pID_FRAME_SeeSuAnimal = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SeeSuAnimal );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_help );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_CLOSE );
	m_pID_TEXT_DJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_DJ );
	m_pID_PICTURE_Yingxiang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_Yingxiang );
	m_pID_LISTIMG_ZhuDong = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_ZhuDong );
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_Right );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_Left );
	m_pID_TEXT_TakeNum = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_TakeNum );
	m_pID_BUTTON_Cure = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_Cure );
	m_pID_LISTIMG_PetIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetIcon );
	m_pID_LISTIMG_QiCheng = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_QiCheng );
	m_pID_TEXT_MountName = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_MountName );
	m_pID_BUTTON_GaiMing = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_GaiMing );
	m_pID_LISTIMG_BeiDong = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_BeiDong );
	m_pID_TEXT_Generation = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_Generation );
	m_pID_BUTTON_FangSheng = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_FangSheng );
	m_pID_BUTTON_XiuXi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_XiuXi );
	m_pID_BUTTON_Lock = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_Lock );
	m_pID_BUTTON_Renew = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_Renew );
	m_pID_TEXT_SYDJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_SYDJ );
	m_pID_BUTTON_ChuZhan = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_ChuZhan );
	m_pID_BUTTON_UnLock = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_UnLock );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_HELP );
	m_pID_LIST_ShouLan = (ControlList*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LIST_ShouLan );
	m_pID_LIST_War = (ControlList*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LIST_War );
	m_pID_PICTURE_XBXiong = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_XBXiong );
	m_pID_PICTURE_LeiBieWu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_LeiBieWu );
	m_pID_TEXT_XingGe = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_XingGe );
	m_pID_TEXT_MountLv = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_MountLv );
	m_pID_PICTURE_XBCi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_XBCi );
	m_pID_TEXT_Level = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_Level );
	m_pID_PROGRESS_Exp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PROGRESS_Exp );
	m_pID_PROGRESS_Hp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PROGRESS_Hp );
	//m_pID_PROGRESS_Happy = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PROGRESS_Happy );
	m_pID_PROGRESS_Life = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PROGRESS_Life );
	//m_pID_BUTTON_Feed = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_Feed );
	m_pID_BUTTON_ZengShou = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_ZengShou );
	m_pID_BUTTON_ZhaoHui = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_ZhaoHui );
	m_pID_BUTTON_TuJian = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_TuJian );
	m_pID_PICTURE_WXJin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_WXJin );
	m_pID_PICTURE_WXMu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_WXMu );
	m_pID_PICTURE_WXShui = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_WXShui );
	m_pID_PICTURE_WXHuo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_WXHuo );
	m_pID_PICTURE_WXTu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_WXTu );
	m_pID_PICTURE_ZhongZu1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_ZhongZu1 );
	m_pID_PICTURE_ZhongZu2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_ZhongZu2 );
	m_pID_TEXT_name = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_name );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_Info );
	m_pID_CHECKBOX_Base = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_CHECKBOX_Base );
	m_pID_CHECKBOX_ZZUp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_CHECKBOX_ZZUp );
	m_pID_CHECKBOX_ZZDown = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_CHECKBOX_ZZDown );
	m_pID_CHECKBOX_ZhanDou = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_CHECKBOX_ZhanDou );
	m_pID_TEXT_LIL = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_LIL );
	m_pID_BUTTON_PlusLiLiang = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusLiLiang );
	m_pID_BUTTON_SubtractLiLiang = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractLiLiang );
	m_pID_TEXT_LL = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_LL );
	m_pID_TEXT_NL = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_NL );
	m_pID_TEXT_MJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_MJ );
	m_pID_TEXT_Point = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_Point );
	m_pID_BUTTON_Confirm = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_Confirm );
	m_pID_TEXT_Exp = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_Exp );
	m_pID_TEXT_KLD = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_KLD );
	//m_pID_TEXT_Happy = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_Happy );
	m_pID_TEXT_Life = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_Life );
	m_pID_TEXT_ZDL = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_ZDL );
	m_pID_BUTTON_PlusMinJie = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusMinJie );
	m_pID_BUTTON_SubtractMinJie = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractMinJie );
	m_pID_BUTTON_PlusTiZhi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusTiZhi );
	m_pID_BUTTON_SubtractTiZhi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractTiZhi );
	m_pID_BUTTON_PlusZhiLi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_PlusZhiLi );
	m_pID_BUTTON_SubtractZhiLi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_SubtractZhiLi );
	m_pID_PICTURE_LeiBieFa = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_LeiBieFa );
	m_pID_PICTURE_Base = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_Base );
	m_pID_TEXT_ChengZhangLv = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_ChengZhangLv );
	m_pID_TEXT_LILZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_LILZZ );
	m_pID_TEXT_LLZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_LLZZ );
	m_pID_TEXT_NLZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_NLZZ );
	m_pID_TEXT_MJZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_MJZZ );
	m_pID_PICTURE_ZZ = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_ZZ );
	m_pID_TEXT_DaoHang = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_DaoHang );
	m_pID_TEXT_WLGJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_WLGJ );
	m_pID_TEXT_FSGJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_FSGJ );
	m_pID_TEXT_WLFY = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_WLFY );
	m_pID_TEXT_FSFY = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_FSFY );
	m_pID_TEXT_MZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_MZ );
	m_pID_TEXT_DB = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_DB );
	m_pID_TEXT_HXGJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_HXGJ );
	m_pID_TEXT_HXFY = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_HXFY );
	m_pID_PICTURE_ZhanDou = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_PICTURE_ZhanDou );
	m_pID_TEXT_WuXing = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_WuXing );
	m_pID_TEXT_GenGu = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_GenGu );
	m_pID_TEXT_FZCS = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_FZCS );
	m_pID_TEXT_CWName = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_CWName );
	//m_pID_BUTTON_ChengHao = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_BUTTON_ChengHao );
	m_pID_TEXT_ChengHao = (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_ChengHao );

	m_pID_LISTIMG_PetEquip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip );

	m_pID_LISTIMG_PetEquip1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip1 );
	m_pID_LISTIMG_PetEquip2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip2 );
	m_pID_LISTIMG_PetEquip3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip3 );
	m_pID_LISTIMG_PetEquip4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip4 );
	m_pID_LISTIMG_PetEquip5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_PetEquip5 );
	m_pID_LISTIMG_SkillXT = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillXT );
	m_pID_LISTIMG_SkillHT = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_LISTIMG_SkillHT );

	m_pID_TEXT_Star= (ControlText*)theUiManager.FindControl( ID_FRAME_SeeSuAnimal, ID_TEXT_Star );

	m_pPetEquip[0] = m_pID_LISTIMG_PetEquip1;
	m_pPetEquip[1] = m_pID_LISTIMG_PetEquip2;
	m_pPetEquip[2] = m_pID_LISTIMG_PetEquip3;
	m_pPetEquip[3] = m_pID_LISTIMG_PetEquip4;
	m_pPetEquip[4] = m_pID_LISTIMG_PetEquip5;

	assert( m_pID_FRAME_SeeSuAnimal );
	assert( m_pID_BUTTON_help );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_DJ );
	assert( m_pID_PICTURE_Yingxiang );
	assert( m_pID_LISTIMG_ZhuDong );
	assert( m_pID_BUTTON_Right );
	assert( m_pID_BUTTON_Left );
	assert( m_pID_TEXT_TakeNum );
	assert( m_pID_BUTTON_Cure );
	assert( m_pID_LISTIMG_PetIcon );
	assert( m_pID_LISTIMG_QiCheng );
	assert( m_pID_TEXT_MountName );
	assert( m_pID_BUTTON_GaiMing );
	assert( m_pID_LISTIMG_BeiDong );
	assert( m_pID_TEXT_Generation );
	assert( m_pID_BUTTON_FangSheng );
	assert( m_pID_BUTTON_XiuXi );
	assert( m_pID_BUTTON_Lock );
	assert( m_pID_BUTTON_Renew );
	assert( m_pID_TEXT_SYDJ );
	assert( m_pID_BUTTON_ChuZhan );
	assert( m_pID_BUTTON_UnLock );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_LIST_ShouLan );
	assert( m_pID_LIST_War );
	assert( m_pID_PICTURE_XBXiong );
	assert( m_pID_PICTURE_LeiBieWu );
	assert( m_pID_TEXT_XingGe );
	assert( m_pID_TEXT_MountLv );
	assert( m_pID_PICTURE_XBCi );
	assert( m_pID_TEXT_Level );
	assert( m_pID_PROGRESS_Exp );
	assert( m_pID_PROGRESS_Hp );
	//assert( m_pID_PROGRESS_Happy );
	assert( m_pID_PROGRESS_Life );
	//assert( m_pID_BUTTON_Feed );
	assert( m_pID_BUTTON_ZengShou );
	assert( m_pID_BUTTON_ZhaoHui );
	assert( m_pID_BUTTON_TuJian );
	assert( m_pID_PICTURE_WXJin );
	assert( m_pID_PICTURE_WXMu );
	assert( m_pID_PICTURE_WXShui );
	assert( m_pID_PICTURE_WXHuo );
	assert( m_pID_PICTURE_WXTu );
	assert( m_pID_PICTURE_ZhongZu1 );
	assert( m_pID_PICTURE_ZhongZu2 );
	assert( m_pID_TEXT_name );
	assert( m_pID_TEXT_Info );
	assert( m_pID_CHECKBOX_Base );
	assert( m_pID_CHECKBOX_ZZUp );
	assert( m_pID_CHECKBOX_ZZDown );
	assert( m_pID_CHECKBOX_ZhanDou );
	assert( m_pID_TEXT_LIL );
	assert( m_pID_BUTTON_PlusLiLiang );
	assert( m_pID_BUTTON_SubtractLiLiang );
	assert( m_pID_TEXT_LL );
	assert( m_pID_TEXT_NL );
	assert( m_pID_TEXT_MJ );
	assert( m_pID_TEXT_Point );
	assert( m_pID_BUTTON_Confirm );
	assert( m_pID_TEXT_Exp );
	assert( m_pID_TEXT_KLD );
	//assert( m_pID_TEXT_Happy );
	assert( m_pID_TEXT_Life );
	assert( m_pID_TEXT_ZDL );
	assert( m_pID_BUTTON_PlusMinJie );
	assert( m_pID_BUTTON_SubtractMinJie );
	assert( m_pID_BUTTON_PlusTiZhi );
	assert( m_pID_BUTTON_SubtractTiZhi );
	assert( m_pID_BUTTON_PlusZhiLi );
	assert( m_pID_BUTTON_SubtractZhiLi );
	assert( m_pID_PICTURE_LeiBieFa );
	assert( m_pID_PICTURE_Base );
	assert( m_pID_TEXT_ChengZhangLv );
	assert( m_pID_TEXT_LILZZ );
	assert( m_pID_TEXT_LLZZ );
	assert( m_pID_TEXT_NLZZ );
	assert( m_pID_TEXT_MJZZ );
	assert( m_pID_PICTURE_ZZ );
	assert( m_pID_TEXT_DaoHang );
	assert( m_pID_TEXT_WLGJ );
	assert( m_pID_TEXT_FSGJ );
	assert( m_pID_TEXT_WLFY );
	assert( m_pID_TEXT_FSFY );
	assert( m_pID_TEXT_MZ );
	assert( m_pID_TEXT_DB );
	assert( m_pID_TEXT_HXGJ );
	assert( m_pID_TEXT_HXFY );
	assert( m_pID_PICTURE_ZhanDou );
	assert( m_pID_TEXT_WuXing );
	assert( m_pID_TEXT_GenGu );
	assert( m_pID_TEXT_FZCS );
	assert( m_pID_TEXT_CWName );
	//assert( m_pID_BUTTON_ChengHao );
	assert( m_pID_TEXT_ChengHao );
	assert( m_pID_LISTIMG_PetEquip );
	
	assert( m_pID_LISTIMG_PetEquip1);
	assert( m_pID_LISTIMG_PetEquip2);
	assert( m_pID_LISTIMG_PetEquip3);
	assert( m_pID_LISTIMG_PetEquip4);
	assert( m_pID_LISTIMG_PetEquip5);
	assert( m_pID_LISTIMG_SkillXT);
	assert( m_pID_LISTIMG_SkillHT);

	assert( m_pID_TEXT_Star);
	
	/*m_pPlayerAnim = MeNew CPlayerAnim;
	m_pPlayer = MeNew CPlayer;
	m_pPlayer->SetAnim( m_pPlayerAnim );
	m_pPlayerAnim->SetPlayer( m_pPlayer );
	theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayer );*/
	RenderAnim_Create(CUIRenderAnim::RTWUI_FUJIANG);

    SortControlGroup();
	_SetVisable( false );
	m_pID_BUTTON_Left->SetLButtonDownFun(UIPetSee_LeftLBD);
	m_pID_BUTTON_Right->SetLButtonDownFun(UIPetSee_RightLBD);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_SeeSuAnimal::_UnLoadUI()
{
	/*if (m_pPlayer)
	{
		theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer( m_pPlayer );
		m_pPlayer->Destroy();	
		delete m_pPlayer;
		m_pPlayer = 0;
		m_pPlayerAnim = 0;
	}*/
	RenderAnim_Destroy();
	m_pID_FRAME_SeeSuAnimal = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SeeSuAnimal.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_SeeSuAnimal::_IsVisable()
{
	if(!m_pID_FRAME_SeeSuAnimal)
		return false;

	return m_pID_FRAME_SeeSuAnimal->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_SeeSuAnimal::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_SeeSuAnimal)
		return;

	m_fRotateZ = 0.0f;
	m_nModelId = -1;
	m_pID_FRAME_SeeSuAnimal->SetVisable( bVisable );
	if (bVisable)
	{
		m_GroupBase.SetVisible(true);
		m_GroupGrowing.SetVisible(false);
		m_GroupFight.SetVisible(true);
	}
	
}

void CUI_ID_FRAME_SeeSuAnimal::RefreshProperty(SPetItem *pPetItem)
{
	if(!pPetItem)
		return;

	ItemDefine::SPetMonster *pPetMonster = GettheItemDetail().GetPetById(pPetItem->baseInfo.petId);
	if(!pPetMonster)
		return;

	
	//m_pID_TEXT_Generation->SetText( theXmlString.GetString( eText_MountGeneration_First + mount.baseInfo.generation ) );
	m_pID_TEXT_CWName->SetText("");

	PetSettingConfig::STitle* pTitle = thePetSettingConfig.GetPetTitle( pPetItem->baseInfo.savvy, pPetItem->baseInfo.growStar, pPetItem->baseInfo.aptitudeLevel );
	/*if ( pTitle != NULL )
		m_pID_TEXT_ChengHao->SetText(pTitle->strTitleName.c_str());*/

	DWORD dwColor = 0;
	//dwColor = S_IconInfoHero::GetQualityColor( pPetItem->baseInfo.quality );//这个是服务器读取怪物表的品质的，错了

	int nQuality=0;
	if ( pTitle != NULL )
		dwColor = thePetSettingConfig.GetTitleColorByTitleName(pTitle->strTitleName,nQuality);
	if (dwColor == 0)
	{
		dwColor = S_IconInfoHero::GetQualityColor(nQuality);
	}



	DWORD dwDJColor = 0x00ffffff;
	if( pPetMonster->takeLevel > thePlayerRole.GetLevel() )
		dwDJColor = 0xff0000;

	m_pID_TEXT_SYDJ->SetText(pPetMonster->takeLevel, dwDJColor);
	m_pID_TEXT_MountName->SetText(pPetMonster->GetName(), dwColor);        // 宠物原始名称
	m_pID_TEXT_name->SetText(pPetItem->baseInfo.szName,dwColor);

	if ( pTitle != NULL )
		m_pID_TEXT_ChengHao->SetText(pTitle->strTitleName.c_str(), dwColor);

	SetIntText(m_pID_TEXT_MountLv,pPetItem->baseInfo.takeLevel);           //携带等级
	SetIntText(m_pID_TEXT_Level,pPetItem->baseInfo.level);                 //等级

	SetIntText(m_pID_TEXT_WuXing,pPetItem->baseInfo.savvy);                //悟性
	SetIntText(m_pID_TEXT_GenGu,pPetItem->baseInfo.bone);                  //根骨
	SetIntText(m_pID_TEXT_FZCS,pPetItem->baseInfo.breedNum);               //繁殖次数

	//SetIntText(m_pID_TEXT_XingGe,pPetItem->baseInfo.characterize);         //性格
	m_pID_TEXT_XingGe->SetText("");
	m_pID_TEXT_XingGe->SetText(s_CUI_ID_FRAME_SuAnimal.GetPetXingeString(pPetItem->baseInfo.characterize));
	int nValue = 0;
	if ( pPetItem->baseInfo.GetFightAttribute(CharAttr_HPMax) != 0 )
	{
		nValue = pPetItem->baseInfo.hp*1000/pPetItem->baseInfo.GetFightAttribute(CharAttr_HPMax);
		m_pID_PROGRESS_Hp->SetValue(nValue);
	}
	//m_pID_PROGRESS_Hp->SetMaxValue(pPetItem->baseInfo.fightAttribute[CharAttr_HPMax]);	//血量

	char szInfo[256] = {0};
	MeSprintf_s(szInfo,sizeof(szInfo),"%d/%d",pPetItem->baseInfo.hp,pPetItem->baseInfo.GetFightAttribute(CharAttr_HPMax));
	m_pID_TEXT_KLD->SetText(szInfo);

	//nValue = pPetItem->baseInfo.loyalty*1000/100;
	//m_pID_PROGRESS_Happy->SetValue(nValue);	//快乐
	//m_pID_PROGRESS_Happy->SetMaxValue(100.0f);

	//不要快乐度这个鬼东西了   by liaojie  11.21
	//MeSprintf_s(szInfo,sizeof(szInfo),"%d/100",pPetItem->baseInfo.loyalty);
	//m_pID_TEXT_Happy->SetText(szInfo);

	if(pPetMonster->duration != 0)
	{
		nValue = pPetItem->baseInfo.duration*1000/pPetMonster->duration;
		m_pID_PROGRESS_Life->SetValue(nValue);	//寿命
		//m_pID_PROGRESS_Life->SetMaxValue(pPetMonster->duration);    //寿命上线
	}

	MeSprintf_s(szInfo,sizeof(szInfo),"%d/%d",pPetItem->baseInfo.duration,pPetMonster->duration);
	m_pID_TEXT_Life->SetText(szInfo);

	// 经验
	__int64 dwTotalExp = theExpStage.GetPetLevelupExp(pPetItem->baseInfo.level );
	__int64 dwLastLevelExp = 0;
	if (pPetItem->baseInfo.level > 1)
	{
		dwLastLevelExp = theExpStage.GetPetLevelupExp(pPetItem->baseInfo.level - 1);
	}

	__int64 iExp = pPetItem->baseInfo.exp - dwLastLevelExp;
	if(iExp != 0 && (dwTotalExp - dwLastLevelExp != 0))
	{
		__int64 iValue = iExp * 1000/(dwTotalExp - dwLastLevelExp);
		m_pID_PROGRESS_Exp->SetValue(iValue);          //经验
		//m_pID_PROGRESS_Exp->SetMaxValue(theExpStage.GetPetLevelupExp(pPetItem->baseInfo.level));
	}

	MeSprintf_s(szInfo,sizeof(szInfo),"%I64u/%I64u",pPetItem->baseInfo.exp - dwLastLevelExp,dwTotalExp - dwLastLevelExp);
	m_pID_TEXT_Exp->SetText(szInfo);

	SetIntText(m_pID_TEXT_LIL, pPetItem->baseInfo.GetCurrentBaseAttr(EBaseAttr_Strength));	    // 力量
	SetIntText(m_pID_TEXT_MJ, pPetItem->baseInfo.GetCurrentBaseAttr(EBaseAttr_Agility));		    // 敏捷
	SetIntText(m_pID_TEXT_NL, pPetItem->baseInfo.GetCurrentBaseAttr(EBaseAttr_Stamina));		    // 耐力
	SetIntText(m_pID_TEXT_LL, pPetItem->baseInfo.GetCurrentBaseAttr(EBaseAttr_Intelligence));	    // 术法
	SetIntText(m_pID_TEXT_Point, pPetItem->baseInfo.nPotentialPoint);                           //潜力
	SetIntText(m_pID_TEXT_ChengZhangLv,pPetItem->baseInfo.growRate);                            //成长率
	SetIntText(m_pID_TEXT_LILZZ,pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Strength));        //力量资质
	SetIntText(m_pID_TEXT_MJZZ,pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Agility));          //敏捷资质
	SetIntText(m_pID_TEXT_NLZZ,pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Stamina));          //耐力资质
	SetIntText(m_pID_TEXT_LLZZ,pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Intelligence));    //灵力资质
	SetIntText(m_pID_TEXT_DaoHang,pPetItem->baseInfo.daoxing);                                  //道行
	SetIntText(m_pID_TEXT_WLGJ,pPetItem->baseInfo.GetFightAttribute(CharAttr_AttackPhysics));      //物理攻击
	SetIntText(m_pID_TEXT_FSGJ,pPetItem->baseInfo.GetFightAttribute(CharAttr_AttackMagic));        //法术攻击
	SetIntText(m_pID_TEXT_WLFY,pPetItem->baseInfo.GetFightAttribute(CharAttr_DefendPhysics));      //物理防御
	SetIntText(m_pID_TEXT_FSFY,pPetItem->baseInfo.GetFightAttribute(CharAttr_DefendMagic));        //法术防御
	SetIntText(m_pID_TEXT_MZ,pPetItem->baseInfo.GetFightAttribute(CharAttr_Exact));                //命中
	SetIntText(m_pID_TEXT_DB,pPetItem->baseInfo.GetFightAttribute(CharAttr_Dodge));                //躲避
	SetIntText(m_pID_TEXT_HXGJ,pPetItem->baseInfo.GetFightAttribute(CharAttr_Critical));           //会心攻击
	SetIntText(m_pID_TEXT_HXFY,pPetItem->baseInfo.GetFightAttribute(CharAttr_Tenacity));           //会心防御

	//战斗力
	MeSprintf_s(szInfo,sizeof(szInfo),"%d",pPetItem->baseInfo.battleValue);
	m_pID_TEXT_ZDL->SetText(szInfo);

	//性别
	m_pID_PICTURE_XBCi->SetVisable(false);
	m_pID_PICTURE_XBXiong->SetVisable(false);
	if(pPetItem->baseInfo.sex == Sex_Male)
		m_pID_PICTURE_XBXiong->SetVisable(true);
	else if(pPetItem->baseInfo.sex == Sex_Female)
		m_pID_PICTURE_XBCi->SetVisable(true);

	//攻击方式
	m_pID_PICTURE_LeiBieWu->SetVisable(false);
	m_pID_PICTURE_LeiBieFa->SetVisable(false);
	if(pPetItem->baseInfo.attackType == EPetAttack_Physical)
		m_pID_PICTURE_LeiBieWu->SetVisable(true);
	else if(pPetItem->baseInfo.attackType == EPetAttack_Magic)
		m_pID_PICTURE_LeiBieFa->SetVisable(true);

	//五行
	m_pID_PICTURE_WXJin->SetVisable(false);
	m_pID_PICTURE_WXMu->SetVisable(false);
	m_pID_PICTURE_WXShui->SetVisable(false);
	m_pID_PICTURE_WXHuo->SetVisable(false);
	m_pID_PICTURE_WXTu->SetVisable(false);
	switch(pPetItem->baseInfo.element)
	{
	case FiveElements_Metal:        // 金
		m_pID_PICTURE_WXJin->SetVisable(true);
		break;
	case FiveElements_Wood:         // 木
		m_pID_PICTURE_WXMu->SetVisable(true);
		break;
	case FiveElements_Water:        // 水
		m_pID_PICTURE_WXShui->SetVisable(true);
		break;
	case FiveElements_Fire:         // 火
		m_pID_PICTURE_WXHuo->SetVisable(true);
		break;
	case FiveElements_Earth:        // 土
		m_pID_PICTURE_WXTu->SetVisable(true);
		break;
	}

	//种族
	m_pID_PICTURE_ZhongZu1->SetVisable(false);
	m_pID_PICTURE_ZhongZu2->SetVisable(false);
	int m_Generation = pPetItem->baseInfo.generation;
	if (m_Generation >= 1)
	{//一代以上即显示几代宠物
		char temp[16];
		memset(temp,0,sizeof(temp));
		MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetNameGen),(m_Generation+1),pPetMonster->GetName());
		m_pID_TEXT_CWName->SetText(temp);
	}
	else
	{
		m_pID_TEXT_CWName->SetText(pPetMonster->GetName());
	}
	// 	switch(pPetItem->baseInfo.phyle)
	// 	{
	// 		case 
	// 	}

	//设置副将的装备
	m_pID_LISTIMG_PetEquip->Clear();
	for(int i =0;i<SPetItem::PetEquip_MaxSum;++i)
	{
		SCharItem& pEquip = pPetItem->baseInfo.PetEquip[i];
		if(pEquip.itembaseinfo.ustItemID ==0 || pEquip.itembaseinfo.ustItemID == InvalidLogicNumber)
			continue;
		//将装备设置上去
		ControlIconDrag::S_ListImg pItems;
		pItems.SetData(&pEquip);
		m_pID_LISTIMG_PetEquip->SetItem(&pItems,i);	

		m_pPetEquip[i]->SetItem(&pItems,0);	
	}

	RefreshMountStar(pPetItem);
}

void  CUI_ID_FRAME_SeeSuAnimal::RenderViewport()
{
	if( !IsVisable() )
		return;

	RECT rc;
	m_pID_PICTURE_Yingxiang->GetRealRect( &rc );
	s_CUI_ID_FRAME_SeeSuAnimal.RenderMount( m_nModelId, m_pPlayerAnim, m_fRotateZ, rc );
}

void CUI_ID_FRAME_SeeSuAnimal::UpdatePetInfo()
{
	s_CUI_ID_FRAME_SeeSuAnimal.ChangeModel(m_pCurrPet,m_pPlayerAnim,m_nModelId);
	RefreshProperty(&m_pCurrPet);
    RefreshPetSkill(m_pCurrPet);
}

void  CUI_ID_FRAME_SeeSuAnimal::SetPetItem(SPetItem &pItem)
{
	memcpy(&m_pCurrPet,&pItem,sizeof(SPetItem));
	UpdatePetInfo();
}

void CUI_ID_FRAME_SeeSuAnimal::SortControlGroup()
{
	m_GroupBase.Clear();
	// 	m_GroupBase.AddControl(m_pID_TEXT_LIL);
	// 	m_GroupBase.AddControl(m_pID_TEXT_NL);
	// 	m_GroupBase.AddControl(m_pID_TEXT_LL);
	// 	m_GroupBase.AddControl(m_pID_TEXT_MJ);
	// 	m_GroupBase.AddControl(m_pID_TEXT_Point);
	// 	m_GroupBase.AddControl(m_pID_BUTTON_Confirm);
	// 	m_GroupBase.AddControl(m_pID_BUTTON_PlusLiLiang);
	// 	m_GroupBase.AddControl(m_pID_BUTTON_SubtractLiLiang);
	// 	m_GroupBase.AddControl(m_pID_BUTTON_PlusTiZhi);
	// 	m_GroupBase.AddControl(m_pID_BUTTON_PlusMinJie);
	// 	m_GroupBase.AddControl(m_pID_BUTTON_PlusZhiLi);
	// 	m_GroupBase.AddControl(m_pID_BUTTON_SubtractTiZhi);
	// 	m_GroupBase.AddControl(m_pID_BUTTON_SubtractMinJie);
	// 	m_GroupBase.AddControl(m_pID_BUTTON_SubtractZhiLi);

	m_GroupBase.AddControl(m_pID_PICTURE_Base);
	m_GroupBase.AddControl(m_pID_TEXT_ChengZhangLv);
	m_GroupBase.AddControl(m_pID_TEXT_LILZZ);
	m_GroupBase.AddControl(m_pID_TEXT_LLZZ);
	m_GroupBase.AddControl(m_pID_TEXT_NLZZ);
	m_GroupBase.AddControl(m_pID_TEXT_MJZZ);

	m_GroupGrowing.Clear();
	m_GroupGrowing.AddControl(m_pID_TEXT_DaoHang);
	m_GroupGrowing.AddControl(m_pID_TEXT_WLGJ);
	m_GroupGrowing.AddControl(m_pID_TEXT_WLFY);
	m_GroupGrowing.AddControl(m_pID_TEXT_FSGJ);
	m_GroupGrowing.AddControl(m_pID_TEXT_FSFY);
	m_GroupGrowing.AddControl(m_pID_TEXT_MZ);
	m_GroupGrowing.AddControl(m_pID_TEXT_DB);
	m_GroupGrowing.AddControl(m_pID_TEXT_HXGJ);
	m_GroupGrowing.AddControl(m_pID_TEXT_HXFY);
	m_GroupGrowing.AddControl(m_pID_PICTURE_ZZ);

	m_GroupFight.Clear();
	m_GroupFight.AddControl(m_pID_PICTURE_ZhanDou);
	m_GroupFight.AddControl(m_pID_TEXT_WuXing);
	m_GroupFight.AddControl(m_pID_TEXT_GenGu);
	m_GroupFight.AddControl(m_pID_TEXT_FZCS);
}

void CUI_ID_FRAME_SeeSuAnimal::SetIntText(ControlText* pText, float v)
{
	pText->SetText(v);
}

void CUI_ID_FRAME_SeeSuAnimal::SetFloatText(ControlText* pText, float v)
{
	char szTemp[32];
	sprintf( szTemp, "%.2f", v );
	pText->SetText(szTemp);
}

void CUI_ID_FRAME_SeeSuAnimal::RefreshPetSkill(SPetItem &pet)
{
	CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
		GetPage(CUISkillMgr::ePetSkill);
	if (!pSkillTree)
		return;

	SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

	ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( pet.GetPetID() );
	if ( pPetMonster == NULL ) 
		return;
	
	m_pID_LISTIMG_ZhuDong->Clear();
	m_pID_LISTIMG_SkillXT->Clear();
	m_pID_LISTIMG_SkillHT->Clear();
	for ( int i = 0; i < SPetItem::PetDefine_MaxSkillCount; ++i)
	{
		unsigned short usSkillId = pet.skillInfo.skills[i].ustSkillID;
		if ( usSkillId == 0)
			continue;

		unsigned short usLevel = pet.skillInfo.skills[i].stSkillLevel;

		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(usSkillId,usLevel);
		if (!pItemSkill)
			continue;
		const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue(usSkillId);
		if (!pIcon)
			continue;

		ControlIconDrag::S_ListImg stItem;
		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
		stItem.SetData( usSkillId, usLevel, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
		stItem.SetFlags(CUISkillMgr::ePetSkill);

		SkillBag::SColdTime *pTime = NULL;
		pTime = thePlayerRole.m_PetSkillBag.GetColdTimeById( usSkillId );
		if ( pTime )
		{
			stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
		}

		m_pID_LISTIMG_ZhuDong->SetItem(&stItem);

		if (pPetMonster->talentSkillId == usSkillId)
		{
			m_pID_LISTIMG_SkillXT->SetItem(&stItem);
		}
		else
		{
			m_pID_LISTIMG_SkillHT->SetItem(&stItem);
		}
	}
}

void CUI_ID_FRAME_SeeSuAnimal::RenderMount(int nMountId, CPlayerAnim* pAnim, float fRotateZ, const RECT& rt)
{
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
		pAnim->SetScale(1.4f);
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

void CUI_ID_FRAME_SeeSuAnimal::ChangeModel(SPetItem& mount, CPlayerAnim* pAnim, int& iOldModelId)
{
	int nModelId = mount.baseInfo.petId;
	if( iOldModelId == nModelId )
		return;

	iOldModelId = nModelId;

	int	nResMexID = -1;
	ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById(mount.baseInfo.petId);
	if(!pPetMonster)
		return;
	//if( pAnim )
	//{
	//	pAnim->MyChangeModel( pPetMonster->iModelID, TRUE, NULL/*GettheItemDetail().GetDromeByID( nModelId )->GetSkinName()*/ );
	//	pAnim->SetCurAnimType(-1);
	//}

	RenderAnim_SetModelID(pPetMonster->iModelID);
}

bool CUI_ID_FRAME_SeeSuAnimal::UIPetSee_RightLBD(INT nX,INT nY)
{
	s_CUI_ID_FRAME_SeeSuAnimal.SetRotate(true);
	return true;
}

bool CUI_ID_FRAME_SeeSuAnimal::UIPetSee_LeftLBD(INT nX,INT nY)
{
	s_CUI_ID_FRAME_SeeSuAnimal.SetRotate(true);
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}

bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
	
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}

bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}

bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}

bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip5OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_PetEquip5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}

bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_SkillXTOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_SkillXTOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_SkillXTOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_SkillXTOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}

bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_SkillHTOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_SkillHTOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_SkillHTOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SeeSuAnimal::ID_LISTIMG_SkillHTOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeeSuAnimal )
		return false;
	return true;
}
void CUI_ID_FRAME_SeeSuAnimal::RefreshMountStar(SPetItem* mount)
{
	m_pID_TEXT_Star->SetText("");
	if(mount->baseInfo.quality== 0)
	{
		//一星
		m_pID_TEXT_Star->SetText("{#77701}");
	}
	else if(mount->baseInfo.quality== 1)
	{
		m_pID_TEXT_Star->SetText("{#77702}");
	}
	else if(mount->baseInfo.quality == 2)
	{
		m_pID_TEXT_Star->SetText("{#77703}");
	}
	else if(mount->baseInfo.quality ==3)
	{
		m_pID_TEXT_Star->SetText("{#77704}");
	}
	else if(mount->baseInfo.quality== 4)
	{
		m_pID_TEXT_Star->SetText("{#77705}");
	}
}