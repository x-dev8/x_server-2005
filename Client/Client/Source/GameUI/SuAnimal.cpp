#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimal.h"
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
#include "PetSettingConfig.h"
#include "ItemDetail.h"
#include "SuAnimalCardList.h"
#include "Group_Me.h"
#include "Progress.h"
#include "Common.h"
#include "color_config.h"
#include "SelectPet.h"
#include "GameSetting.h"
#include "MeTerrain/stdafx.h"
#include "MeTerrain/MapDef.h"
#include "MapConfig.h"
#include "SuAnimalRecvie.h"
#include "InfoTips.h"
#include "PetDefineConfig.h"
#include "PetCompose.h"
#include "SuAnimalMaterialUp.h"
#include "PetSpeakConfig.h"
extern char* GetFullFileName(const char* filename);

extern short GetKeyboardInput( int iKey );

CUI_ID_FRAME_SuAnimal s_CUI_ID_FRAME_SuAnimal;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimal, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimal, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LIST_ShouLanOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_SuAnimal,ID_BUTTON_XSCH_OnButtonClick)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_XiuXiOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_ZhuDongOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_ZhuDongOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_ZhuDongOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_ZhuDongOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquipOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquipOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal,ID_LISTIMG_PetEquipOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquipOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_LeftOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetIconOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_QiChengOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_QiChengOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_QiChengOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_QiChengOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_ChuZhanOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_LockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_UnLockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_GaiMingOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_RenewOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_ConfirmOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_BeiDongOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_BeiDongOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_BeiDongOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_BeiDongOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_PlusLiLiangOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_SubtractLiLiangOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_PlusTiZhiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_PlusMinJieOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_PlusZhiLiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_SubtractTiZhiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_SubtractMinJieOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_SubtractZhiLiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_CureOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_FeedOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_ZengShouOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_FangShengOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_CHECKBOX_BaseOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_CHECKBOX_ZZUpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_CHECKBOX_ZZDownOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_CHECKBOX_ZhanDouOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_TuJianOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_ZhaoHuiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_ZhaoHuanOnButtonClick )

MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_SuAnimal,ID_BUTTON_PetCompareOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_WuXinUpperOnButtonClick )


MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal,ID_LISTIMG_PetEquip1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip1OnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal,ID_LISTIMG_PetEquip2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip2OnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal,ID_LISTIMG_PetEquip3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip3OnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal,ID_LISTIMG_PetEquip4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip4OnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip5OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip5OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal,ID_LISTIMG_PetEquip5OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip5OnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_SkillXTOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_SkillXTOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal,ID_LISTIMG_SkillXTOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_SkillXTOnIconRButtonUp )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_SkillHTOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_SkillHTOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal,ID_LISTIMG_SkillHTOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_LISTIMG_SkillHTOnIconRButtonUp )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimal, ID_BUTTON_SuAnimalUpOnButtonClick )

CUI_ID_FRAME_SuAnimal::CUI_ID_FRAME_SuAnimal()
{
	ResetMembers();
	//m_pPlayer = 0;
}
CUI_ID_FRAME_SuAnimal::~CUI_ID_FRAME_SuAnimal()
{
	ResetMembers();
}
void CUI_ID_FRAME_SuAnimal::ResetMembers()
{
	m_pID_FRAME_SuAnimal = NULL;

	m_pID_TEXT_LIL = NULL;
	m_pID_TEXT_NL  = NULL;
	m_pID_TEXT_MJ = NULL;
	m_pID_TEXT_LL = NULL;
	m_pID_TEXT_SYDJ = NULL;
	m_pID_TEXT_KLD = NULL;
	m_pID_TEXT_name = NULL;
	m_pID_TEXT_ChengZhangLv = NULL;
	m_pID_TEXT_LLZZ = NULL;
	m_pID_TEXT_LILZZ = NULL;
	m_pID_TEXT_NLZZ = NULL;
	m_pID_TEXT_MJZZ = NULL;
	m_pID_LIST_ShouLan = NULL;
	m_pID_BUTTON_XiuXi = NULL;
	m_pID_TEXT_DJ = NULL;
	m_pID_PICTURE_Yingxiang = NULL;
	m_pID_LISTIMG_ZhuDong = NULL;
	m_pID_LISTIMG_PetEquip = NULL;
	m_pID_TEXT_Exp = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_TEXT_TakeNum = NULL;
	//m_pID_BUTTON_Feed = NULL;
	m_pID_LISTIMG_PetIcon = NULL;
	m_pID_LISTIMG_QiCheng = NULL;
	m_pID_TEXT_MountName = NULL;
	m_pID_BUTTON_ChuZhan = NULL;
	m_pID_BUTTON_ZhaoHui = NULL;
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
	m_pID_TEXT_WuXing = NULL;
	m_pID_TEXT_GenGu = NULL;
	m_pID_TEXT_FZCS = NULL;
	m_pID_PROGRESS_Exp = NULL;
	m_pID_PROGRESS_Hp = NULL;
	//m_pID_PROGRESS_Happy = NULL;
	m_pID_PROGRESS_Life = NULL;
	m_pID_BUTTON_XSCH = NULL;
	m_pID_BUTTON_Cure = NULL;
	//m_pID_BUTTON_Feed = NULL;
	m_pID_BUTTON_ZengShou = NULL;
	m_pID_BUTTON_FangSheng = NULL;

	m_pID_TEXT_WLGJ = NULL;
	m_pID_TEXT_WLFY = NULL;
	m_pID_TEXT_FSGJ = NULL;
	m_pID_TEXT_FSFY = NULL;
	m_pID_TEXT_MZ = NULL;
	m_pID_TEXT_DB = NULL;
	m_pID_TEXT_HXGJ = NULL;
	m_pID_TEXT_HXFY = NULL;
	m_pID_TEXT_DaoHang = NULL;

	m_pID_PICTURE_Base    = NULL;
	m_pID_PICTURE_ZhanDou = NULL;
	m_pID_PICTURE_ZZ      = NULL;

	m_pID_CHECKBOX_Base = NULL;
	m_pID_CHECKBOX_ZZUp = NULL;
	m_pID_CHECKBOX_ZZDown = NULL;
	m_pID_CHECKBOX_ZhanDou = NULL;

	m_pID_BUTTON_TuJian = NULL;

	m_pID_PICTURE_XBXiong = NULL;
	m_pID_PICTURE_XBCi = NULL;
	m_pID_TEXT_XingGe = NULL;

	//m_pID_TEXT_Happy = NULL;
	m_pID_TEXT_Life = NULL;
	m_pID_TEXT_Level = NULL;
	m_pID_TEXT_ZDL = NULL;
	m_pID_PICTURE_LeiBieFa = NULL;
	m_pID_PICTURE_LeiBieWu = NULL;
	m_pID_TEXT_Star = NULL;
	m_pID_PICTURE_WXJin = NULL;
	m_pID_PICTURE_WXMu = NULL;
	m_pID_PICTURE_WXShui = NULL;
	m_pID_PICTURE_WXHuo = NULL;
	m_pID_PICTURE_WXTu = NULL;
	m_pID_TEXT_ReliveTime = NULL;
	m_pID_PICTURE_ZhongZu1 = NULL;
	m_pID_PICTURE_ZhongZu2 = NULL;
	m_pID_TEXT_CWName = NULL;
	m_pID_TEXT_LILZZPercent = NULL;
	m_pID_TEXT_MJZZPercent = NULL;
	m_pID_TEXT_NLZZPercent = NULL;
	m_pID_TEXT_LLZZPercent = NULL;
	m_pID_TEXT_ChengHao = NULL;


	m_pID_LISTIMG_PetEquip1 = NULL;
	m_pID_LISTIMG_PetEquip2=NULL;
	m_pID_LISTIMG_PetEquip3=NULL;
	m_pID_LISTIMG_PetEquip4=NULL;
	m_pID_LISTIMG_PetEquip5=NULL;
	m_pID_LISTIMG_SkillXT=NULL;
	m_pID_LISTIMG_SkillHT=NULL;

	m_pID_BUTTON_SuAnimalUp = NULL;


	m_IsActivePet = false;
	m_IsStartProgress = false;
	m_IsXiuXi  = false;
	m_dwStartIntonateTime = 0;
	m_pID_TEXT_Info = NULL;
	m_pID_BUTTON_ZhaoHuan = NULL;

	for (int n =0;n < EBaseAttr_MaxSize;n++)
	{
		potentialAttributeTemp[n] =0;
	}
	poten_sum = 0;
	m_CallIndex = -1;
	//m_DeadTime = 0;
	InitActivePicState();

	m_IsInitList = true;
	m_ActPetID = 0;
}

// Frame
bool CUI_ID_FRAME_SuAnimal::OnFrameRun()
{
	int nScroollBarHeight = 0;
	if (s_CUI_ID_FRAME_SuAnimal.IsVisable())
	{
		m_nLastHeight = m_pID_LIST_ShouLan->GetShowStartHeight();
		if (m_pID_LIST_ShouLan->GetScrollBar())
		{
			nScroollBarHeight = m_pID_LIST_ShouLan->GetScrollBar()->GetValue();
		}

		int index = thePlayerRole.GetActivedPetIndex();
		if(index != -1 && m_pID_LIST_ShouLan->GetCurSelIndex() != index && m_IsInitList)
		{
			m_pID_LIST_ShouLan->SetCurSelIndex(index);
			ID_LIST_ShouLanOnListSelectChange(m_pID_LIST_ShouLan,m_pID_LIST_ShouLan->GetCurSelItem());
			m_IsInitList = false;
		}
	}	

	if(thePlayerRole.GetActivedPetIndex() != -1 && m_pID_LIST_ShouLan->GetCurSelIndex() == thePlayerRole.GetActivedPetIndex() && m_ActPetID !=0)
	{
		CPlayer *pPetPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_ActPetID);
		if(pPetPlayer)
		{
			int Hp = pPetPlayer->GetHp();
			int MaxHp = pPetPlayer->GetHpMax();
			//设置血的数量
			int nValue = 0;
			nValue = Hp*1000/MaxHp;
			char szInfo[256] = {0};
			m_pID_PROGRESS_Hp->SetValue(nValue);
			MeSprintf_s(szInfo,sizeof(szInfo),"%d/%d",Hp,MaxHp);
			m_pID_TEXT_KLD->SetText(szInfo);

			s_CUI_Group.UpdatePetInfo(m_ActPetID);
		}
	}
	else
		m_ActPetID = 0;

	if (s_CUI_ID_FRAME_SuAnimal.IsVisable() && m_bNeedRefresh)
	{
		RefreshHelp(m_bSelectEnd);
		SetNeedRefresh(false);
	}
	int nSelId = m_pID_LIST_ShouLan->GetCurSelIndex();
	SPetItem& mount = thePlayerRole.GetPetByIndex(nSelId);
	DWORD m_currenttime = GetPetCoolDownTime(&mount);
	if (m_currenttime >0)
	{
		char m_str[128];
		MeSprintf_s(m_str, sizeof(m_str)/sizeof(char) - 1, theXmlString.GetString(eText_PetAliveTime),m_currenttime/1000);
		*m_pID_TEXT_ReliveTime = m_str;
		m_pID_TEXT_ReliveTime->SetVisable(true);
	}
	else
	{
		m_pID_TEXT_ReliveTime->SetVisable(false);
	}
// 	if ( HQ_TimeGetTime()-m_dwStartIntonateTime <5000 )
// 	{
// 		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
// 		if( pMe && (pMe->IsMoving() || pMe->IsJumping() || pMe->IsIntonating()) )
// 		{
// 			m_IsActivePet = false;
// 			s_CUI_Progress.SetProgressComplete();
// 			m_dwStartIntonateTime = 0;
// 			m_IsStartProgress = false;
// 		}
// 	}
// 	if (m_IsActivePet && m_IsStartProgress && HQ_TimeGetTime()-m_dwStartIntonateTime >5000 )
// 	{
// 		m_IsActivePet = false;
// 		s_CUI_Progress.SetProgressComplete();
// 		ActivePet(mount, nSelId);
// 		m_dwStartIntonateTime = 0;
// 		m_IsStartProgress = false;
// 	}
// 	else if (m_IsActivePet && !m_IsStartProgress)
// 	{
// 		m_IsStartProgress = true;
// 		s_CUI_Progress.ShowByTime(m_dwStartIntonateTime,5000, true, 1, true, true, theXmlString.GetString(eText_PetChuZhan));
// 	}
	bool bChuZhan = true;
	if( nSelId != -1 )
		bChuZhan = m_PetsEnable[nSelId].bEnable;

	m_pID_BUTTON_ChuZhan->SetEnable( (m_pID_LIST_ShouLan->GetListItemCnt() > 0 ) && bChuZhan && m_bCanMount );
	if(s_CUI_ID_FRAME_SuAnimal.IsVisable())
	{		
// 		int nSelId = m_pID_LIST_ShouLan->GetCurSelIndex();
// 		SPetItem& mount = thePlayerRole.GetPetByIndex(nSelId);
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
	}

	if(s_CUI_ID_FRAME_SuAnimalRecvie._IsVisable() && thePlayerRole.GetActivedPet())
	{
		s_CUI_ID_FRAME_SuAnimalRecvie._SetVisable(false);
	}

	UpdatePetSkillByMaxSkillSum();


	if(theHeroGame.GetPlayerMgr()->GetMe())
	{
		static int LogPetSpeak = 0;
		CPlayer *pPetPlayer = theHeroGame.GetPlayerMgr()->FindByID(theHeroGame.GetPlayerMgr()->GetMe()->GetPetID());
		if(pPetPlayer)
		{
			if(thePlayerRole.GetActivedPet())
			{
				std::string strSpeak="";
				if(PetSpeakConfig::Instance().GetNowPetSpeakStr(thePlayerRole.GetActivedPet()->GetPetID(),LogPetSpeak,strSpeak))
				{
					pPetPlayer->SetChatInfo(strSpeak);
					LogPetSpeak = HQ_TimeGetTime();
				}
			}
		}
	}

	return true;
}
void CUI_ID_FRAME_SuAnimal::UpdatePetUIInfo(int Hp,int MaxHp)
{
	SPetItem * pPetItem = thePlayerRole.GetActivedPet();
	if(pPetItem )
	{
		int nValue = 0;
		nValue = Hp*1000/MaxHp;
		char szInfo[256] = {0};
		m_pID_PROGRESS_Hp->SetValue(nValue);
		MeSprintf_s(szInfo,sizeof(szInfo),"%d/%d",Hp,MaxHp);
		m_pID_TEXT_KLD->SetText(szInfo);
	}
	
}
bool CUI_ID_FRAME_SuAnimal::OnFrameRender()
{
	if (m_pID_LIST_ShouLan->GetListItemCnt() > 0)
	{
		RECT rc;
		m_pID_PICTURE_Yingxiang->GetRealRect( &rc );
		RenderAnim_Update(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, D3DXVECTOR3(0, -7, 0));
		/*
		* Author: 2012-9-13 22:08:49 wangshuai
		* Desc:   老的模型比较大，以新的模型为准，缩放1.0
		*/
		RenderAnim(D3DXVECTOR3(0, -3, -1.0), Config::m_fMdlSpaceScale * 1.4f);
	}
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_ChuZhanOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	//m_CallIndex = -1;
	ActivePet(m_pID_LIST_ShouLan->GetCurSelIndex());
	return true;
}
void CUI_ID_FRAME_SuAnimal::InitializeAtEnterWorld()
{
	LoadUI();
}
void CUI_ID_FRAME_SuAnimal::ReviceSuAnimal()
{
	/*if( !m_pID_FRAME_SuAnimal )
	{
		if(!LoadUI())
			return;
	}
	if( !m_pID_FRAME_SuAnimal )
		return ;*/
	ActivePet(m_pID_LIST_ShouLan->GetCurSelIndex());
}
//--------------------------------------------------------------------------------------
// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_LockOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	MsgLockItemReq msg;
	int selIndex = m_pID_LIST_ShouLan->GetCurSelIndex();
	msg.ustItemIndex = selIndex;
	msg.nGuID = thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].baseInfo.guid;
	msg.uchBagType = BT_MountBag;

	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_MountLockedContext), theXmlString.GetString(eText_MountLockedContext),//是否确定加锁
		CUI_ID_FRAME_MessageBox::eTypeYesNo, false ,
		LockPet, &msg, sizeof(MsgLockItemReq));
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_UnLockOnButtonClick(ControlObject* pSender)
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	MsgUnLockItemReq msg;
	int selIndex = m_pID_LIST_ShouLan->GetCurSelIndex();
	msg.ustItemIndex = selIndex;
	msg.nGuID = thePlayerRole.m_charinfo.ItemBagData.miItems[selIndex].baseInfo.guid;
	msg.uchBagType = BT_MountBag;

	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_ItemUnLockedContext), theXmlString.GetString(eText_ItemUnLockedContext),//是否确定解锁
		CUI_ID_FRAME_MessageBox::eTypeYesNo, false ,
		UnLockPet, &msg, sizeof(MsgUnLockItemReq));
	return true;
}
// 
//------------------------------------------------------------------------------------------------
// Button
//重新分配
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_RenewOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	SPetItem& rfMount = GetCurrentPet();

	if (rfMount.baseInfo.petId != InvalidLogicNumber)
	{
		int sum = 0;
		for ( int i=0; i < EBaseAttr_MaxSize; ++i)
		{ 
			/*float temp = rfMount.baseInfo.baseAttribute[i] + rfMount.baseInfo.potentialAttribute[i];
			sum += rfMount.baseInfo.GetCurrentBaseAttr(i) - temp;
			rfMount.baseInfo.potentialAttribute[i] = temp;*/
			sum += potentialAttributeTemp[i];	
			rfMount.baseInfo.potentialAttribute[i] -= potentialAttributeTemp[i];
		}

		if (sum == poten_sum)
		{
			rfMount.baseInfo.nPotentialPoint += sum; 
		}

		for (int n = 0; n < EBaseAttr_MaxSize ; ++n)
		{
			potentialAttributeTemp[n] = 0;
		}
		poten_sum = 0;
		/*if (sum == poten_sum)
		{
			rfMount.baseInfo.nPotentialPoint += sum; 
		}*/
		UpdataProperty();
	}
	return true;
}

// Button
//确定
const float theta = 0.001;
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_ConfirmOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;

	SPetItem& rfMount = GetCurrentPet();
	bool can_send = false;
	if (rfMount.baseInfo.petId != InvalidLogicNumber)
	{
		MsgPetPotential msg;
		msg.index = m_pID_LIST_ShouLan->GetCurSelIndex();
		msg.guid  = rfMount.baseInfo.guid;

		/*int nValue[EBaseAttr_MaxSize];
		for (int i = 0; i < EBaseAttr_MaxSize; ++i)
			nValue[i] = 0;*/

		
		//for (int i=0; i < EBaseAttr_MaxSize; ++i)
		//{ 
		//	nValue[i] = rfMount.baseInfo.potentialAttribute[i];//问题在这里，			
		////rfMount.baseInfo.potentialAttribute[i] = rfMount.baseInfo.currentAttribute[i] - (rfMount.baseInfo.baseAttribute[i] + rfMount.baseInfo.level - 1);
		//}

		for (int i = 0;i < EBaseAttr_MaxSize;++i)
		{
			/*msg.value[i] = nValue[i];*/
			msg.value[i] = potentialAttributeTemp[i];
			if (msg.value[i] > 0)
			{
				can_send = true;
			}
		}

		if (!can_send)
		{
			return false;
		}

		GettheNetworkInput().SendMsg(&msg);
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
SPetItem& CUI_ID_FRAME_SuAnimal::GetCurrentPet()
{
	int nIndex( ITEM_MOUNT_MAXCOUNT );
	if( IsUILoad() )
		nIndex = m_pID_LIST_ShouLan->GetCurSelIndex();

	return thePlayerRole.GetPetByIndex(nIndex);
}

//------------------------------------------------------------------
const int pointPerOneTime = 1;
bool CUI_ID_FRAME_SuAnimal::AddPoint( EBaseAttr eKeyType)
{
	if (eKeyType < 0 || eKeyType >  EBaseAttr_MaxSize)
	{
		return false;
	}

	if( !m_pID_FRAME_SuAnimal )
	{
		return false;
	}

	SPetItem& rfMount = GetCurrentPet();
	if (rfMount.baseInfo.petId != InvalidLogicNumber)
	{
		if (rfMount.baseInfo.nPotentialPoint >= pointPerOneTime)
		{
			rfMount.baseInfo.nPotentialPoint -= pointPerOneTime;
			rfMount.baseInfo.potentialAttribute[eKeyType] += pointPerOneTime;

			//zhuxincong  8.24 在客户端中记录一下
			potentialAttributeTemp[eKeyType] += pointPerOneTime;
			poten_sum++;
		}
		UpdataProperty();
	}
	return true;
}

bool CUI_ID_FRAME_SuAnimal::SubtractPoint(EBaseAttr eKeyType)
{
	if (eKeyType < 0 || eKeyType >  EBaseAttr_MaxSize)
	{
		return false;
	}

	if( !m_pID_FRAME_SuAnimal )
	{
		return false;
	}

	SPetItem& rfMount = GetCurrentPet();
	if (rfMount.baseInfo.petId != InvalidLogicNumber)
	{
		//float temp = rfMount.baseInfo.baseAttribute[eKeyType] + rfMount.baseInfo.potentialAttribute[eKeyType];
		//if (rfMount.baseInfo.GetCurrentBaseAttr(eKeyType) - temp >= pointPerOneTime)
		if (potentialAttributeTemp[eKeyType] > 0) //逻辑，有分配潜力点的话 就可以减去
		{
			rfMount.baseInfo.nPotentialPoint += pointPerOneTime;
			rfMount.baseInfo.potentialAttribute[eKeyType] -= pointPerOneTime;

			//在客户端中记录一下
			potentialAttributeTemp[eKeyType] -= pointPerOneTime;			
			poten_sum--;
		}
		UpdataProperty();
	}
	return true;
}

void CUI_ID_FRAME_SuAnimal::SetIntText(ControlText* pText, float v)
{
	pText->SetText(v);
}

//-----------------------------------------------------------------------------------------------
void CUI_ID_FRAME_SuAnimal::UpdataProperty()
{
	if( !IsUILoad() )
		return;

	SPetItem& rfPet = GetCurrentPet();
	if (rfPet.baseInfo.petId != InvalidLogicNumber)
		RefreshProperty(&rfPet);
}
// 
//--------------------------------------------------------------------------------------------------
// Button
//+力量
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_PlusLiLiangOnButtonClick( ControlObject* pSender )
{
	return AddPoint(EBaseAttr_Strength);
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_PlusMinJieOnButtonClick( ControlObject* pSender )
{
	return AddPoint(EBaseAttr_Agility);
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_PlusTiZhiOnButtonClick( ControlObject* pSender )
{
	return AddPoint(EBaseAttr_Stamina);
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_PlusZhiLiOnButtonClick( ControlObject* pSender )
{
	return AddPoint(EBaseAttr_Intelligence);
}

//--------------------------------------------------------------------------------------------
// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_SubtractLiLiangOnButtonClick( ControlObject* pSender )
{
	return SubtractPoint(EBaseAttr_Strength);
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_SubtractTiZhiOnButtonClick( ControlObject* pSender )
{
	return SubtractPoint(EBaseAttr_Stamina);
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_SubtractMinJieOnButtonClick( ControlObject* pSender )
{
	return SubtractPoint(EBaseAttr_Agility);
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_SubtractZhiLiOnButtonClick( ControlObject* pSender )
{
	return SubtractPoint(EBaseAttr_Intelligence);
}

void CUI_ID_FRAME_SuAnimal::SetLockAndUnLockState()
{

}
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_SuAnimalUpOnButtonClick( ControlObject* pSender )
{
	//打开副将强化的UI
	s_CUI_ID_FRAME_SuAnimalMaterialUp.SetVisable(true);
	return true;
}
void CUI_ID_FRAME_SuAnimal::ID_LIST_ShouLanOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return;

	m_pID_LISTIMG_PetEquip->Clear();

	m_pID_LISTIMG_PetEquip1->Clear();
	m_pID_LISTIMG_PetEquip2->Clear();
	m_pID_LISTIMG_PetEquip3->Clear();
	m_pID_LISTIMG_PetEquip4->Clear();
	m_pID_LISTIMG_PetEquip5->Clear();

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
			LockPet, &msg, sizeof(MsgLockItemReq));

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
			UnLockPet, &msg, sizeof(MsgUnLockItemReq));

		s_CUI_ID_FRAME_PACK.SetUnLockItem(false);
	}
}
// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_PetCompareOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_PetCompose.SetVisable(!s_CUI_ID_FRAME_PetCompose.IsVisable());
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_WuXinUpperOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_SuAnimalMaterialUp.SetVisable(!s_CUI_ID_FRAME_SuAnimalMaterialUp.IsVisable());
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_XiuXiOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	if(theHeroGame.GetPlayerMgr()->GetMe()->IsPrivateShopOpen())
	{
		//提示玩家
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PrivateShopOpen));
		return true;
	}

	m_IsXiuXi = true;
	ActivePet(m_pID_LIST_ShouLan->GetCurSelIndex());
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_FangShengOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	// 安全保护
	SPetItem& mount = thePlayerRole.GetPetByIndex(m_pID_LIST_ShouLan->GetCurSelIndex());
	if (mount.baseInfo.petId != InvalidLogicNumber)
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
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_ZhuDongOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_ZhuDongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_ZhuDongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return PetUseSkill(pItem);
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_ZhuDongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return PetUseSkill(pItem);
}
//--------------------------------------------------------------------------------------------------------------------
// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_BeiDongOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_BeiDongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_BeiDongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_BeiDongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return false;
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_GaiMingOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	//副将修改名称 我们判断材料是否足够
	int sum =thePlayerRole.m_bagMaterial.GetItemCount(SID_SuAnimalChangeName);
	if(sum < 1)
	{
		//提示玩家材料不足
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString(eText_SuAnimalChangeName) );
		return false;
	}

	s_CUI_ID_FRAME_Rename.SetType(CUI_ID_FRAME_Rename::eChangeSuAnimal);
	s_CUI_ID_FRAME_Rename.SetVisable(true);
	return true;
}
short CUI_ID_FRAME_SuAnimal::GetCurrentMountIndex()
{
	if( !m_pID_FRAME_SuAnimal )
	{
		//加载UI
		if(!LoadUI())
			return -1;
	}
	if( !m_pID_FRAME_SuAnimal )
		return -1;
	return m_pID_LIST_ShouLan->GetCurSelIndex();	
}
// Button
//bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_FeedOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_SuAnimal )
//		return false;
//
//	// 判断是否已经满生命值，不喂了
//// 	if( thePlayerRole.GetActivedPet() &&
//// 		( thePlayerRole.GetActivedPet()->baseInfo.loyalty == thePlayerRole.GetActivedPet()->baseInfo.GetFightAttribute(CharAttr_HPMax) ) )
//// 	{
//// 		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Mount_Error, theXmlString.GetString( eText_Mount_FeedError_FullHP ) );		
//// 		return false;
//// 	}
//	UsePetItem(ItemDefine::EPetFunc_AddLoyalty);
//	//s_CUI_ID_FRAME_PACK.UseMountRestoreItem();
//	return true;
//}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;

	int n = m_pID_LISTIMG_PetIcon->GetItemIndex( m_pID_LISTIMG_PetIcon->GetCurSelItem() );
	m_pID_LIST_ShouLan->SetCurSelIndex( n );
	ID_LIST_ShouLanOnListSelectChange( NULL, NULL );

	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
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

	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	m_bRotate = false;
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_QiChengOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_QiChengOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return false;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_QiChengOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return PetUseSkill(pItem);
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_QiChengOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return PetUseSkill(pItem);
}

bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_CureOnButtonClick( ControlObject* pSender )
{
	UsePetItem(ItemDefine::EPetFunc_RestoreHP);
	return true;
}

bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_ZengShouOnButtonClick( ControlObject* pSender )
{
	UsePetItem(ItemDefine::EPetFunc_AddLife);
	return true;
}

// CheckBox
void CUI_ID_FRAME_SuAnimal::ID_CHECKBOX_BaseOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_GroupBase.SetVisible(true);
	m_GroupGrowing.SetVisible(false);
	m_GroupFight.SetVisible(false);
}

// CheckBox
void CUI_ID_FRAME_SuAnimal::ID_CHECKBOX_ZZUpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(m_GroupBase.IsVisible())
		return;

	m_GroupBase.SetVisible(false);
	m_GroupGrowing.SetVisible(true);
	m_GroupFight.SetVisible(false);
}

// CheckBox
void CUI_ID_FRAME_SuAnimal::ID_CHECKBOX_ZZDownOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(m_GroupFight.IsVisible())
		return;
	m_GroupBase.SetVisible(false);
	m_GroupGrowing.SetVisible(true);
	m_GroupFight.SetVisible(false);
}

// CheckBox
void CUI_ID_FRAME_SuAnimal::ID_CHECKBOX_ZhanDouOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_GroupBase.SetVisible(false);
	m_GroupGrowing.SetVisible(false);
	m_GroupFight.SetVisible(true);
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_TuJianOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(!s_CUI_ID_FRAME_SuAnimalCardList.IsVisable());
	if (s_CUI_ID_FRAME_SuAnimalCardList.IsVisable())
	{
		int nIndex = m_pID_LIST_ShouLan->GetCurSelIndex();
		SPetItem& mount = thePlayerRole.GetPetByIndex(nIndex);
		if (mount.baseInfo.petId != InvalidLogicNumber)
		{
			s_CUI_ID_FRAME_SuAnimalCardList.RefreshCheckBoxStatus(mount.baseInfo.phyle);
			s_CUI_ID_FRAME_SuAnimalCardList.RefreshPage(mount.baseInfo.phyle);
			s_CUI_ID_FRAME_SuAnimalCardList.RefreshPetList(mount.baseInfo.phyle);
			s_CUI_ID_FRAME_SuAnimalCardList.SetPhylePic(mount.baseInfo.phyle);
		}
	}
	//s_CUI_ID_FRAME_SuAnimal.SetVisable(!s_CUI_ID_FRAME_SuAnimal.IsVisable());
	return true;
}

// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_ZhaoHuiOnButtonClick( ControlObject* pSender )
{
	//m_IsXiuXi = false;
	//ActivePet(m_pID_LIST_ShouLan->GetCurSelIndex());

	SPetItem mount = thePlayerRole.GetPetByIndex(m_CallIndex);
	MsgChangePet changePet;
	changePet.nIndex = m_CallIndex;
	changePet.ucOpType = MsgChangePet::EOT_Recall;
	changePet.guid = mount.baseInfo.guid;
	GettheNetworkInput().SendMsg(&changePet);
	m_CallIndex = -1;
	RefreshButtonGroup();
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_ZhaoHuanOnButtonClick( ControlObject* pSender )
{
	//todo.判断条件，已经有出战的副将应该不能召唤新的，etc
	int nIndex = m_pID_LIST_ShouLan->GetCurSelIndex();
	SPetItem mount = thePlayerRole.GetPetByIndex(nIndex);
	m_CallIndex = nIndex;
	MsgChangePet changePet;
	changePet.nIndex = nIndex;
	changePet.ucOpType = MsgChangePet::EOT_CallButNoActive;
	changePet.guid = mount.baseInfo.guid;
	GettheNetworkInput().SendMsg(&changePet);
	RefreshButtonGroup();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SuAnimal::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimal.meui", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuAnimal.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuAnimal::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SuAnimal, s_CUI_ID_FRAME_SuAnimalOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SuAnimal, s_CUI_ID_FRAME_SuAnimalOnFrameRender);
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_ChuZhan, s_CUI_ID_FRAME_SuAnimalID_BUTTON_ChuZhanOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_SuAnimal, ID_LIST_ShouLan, s_CUI_ID_FRAME_SuAnimalID_LIST_ShouLanOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_XiuXi, s_CUI_ID_FRAME_SuAnimalID_BUTTON_XiuXiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_FangSheng, s_CUI_ID_FRAME_SuAnimalID_BUTTON_FangShengOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_ZhuDongOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_ZhuDongOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_ZhuDongOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_ZhuDong, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_ZhuDongOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquipOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquipOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquipOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquipOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_BeiDongOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_BeiDongOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_BeiDongOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_BeiDong, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_BeiDongOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_GaiMing, s_CUI_ID_FRAME_SuAnimalID_BUTTON_GaiMingOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_Right, s_CUI_ID_FRAME_SuAnimalID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_Left, s_CUI_ID_FRAME_SuAnimalID_BUTTON_LeftOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_Feed, s_CUI_ID_FRAME_SuAnimalID_BUTTON_FeedOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetIconOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetIconOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetIconOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_PetIcon, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetIconOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_QiChengOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_QiChengOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_QiChengOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_QiCheng, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_QiChengOnIconRButtonUp );
	theUiManager.OnButtonClick(ID_FRAME_SuAnimal,ID_BUTTON_XSCH,s_CUI_ID_FRAME_SuAnimalID_BUTTON_XSCH_OnButtonClick);
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_PlusLiLiang, s_CUI_ID_FRAME_SuAnimalID_BUTTON_PlusLiLiangOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_PlusTiZhi, s_CUI_ID_FRAME_SuAnimalID_BUTTON_PlusTiZhiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_PlusMinJie, s_CUI_ID_FRAME_SuAnimalID_BUTTON_PlusMinJieOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_PlusZhiLi, s_CUI_ID_FRAME_SuAnimalID_BUTTON_PlusZhiLiOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_SubtractLiLiang, s_CUI_ID_FRAME_SuAnimalID_BUTTON_SubtractLiLiangOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_SubtractTiZhi, s_CUI_ID_FRAME_SuAnimalID_BUTTON_SubtractTiZhiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_SubtractMinJie, s_CUI_ID_FRAME_SuAnimalID_BUTTON_SubtractMinJieOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_SubtractZhiLi, s_CUI_ID_FRAME_SuAnimalID_BUTTON_SubtractZhiLiOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_Renew, s_CUI_ID_FRAME_SuAnimalID_BUTTON_RenewOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_Confirm, s_CUI_ID_FRAME_SuAnimalID_BUTTON_ConfirmOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_UnLock, s_CUI_ID_FRAME_SuAnimalID_BUTTON_UnLockOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_Lock, s_CUI_ID_FRAME_SuAnimalID_BUTTON_LockOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_Cure, s_CUI_ID_FRAME_SuAnimalID_BUTTON_CureOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_Feed, s_CUI_ID_FRAME_SuAnimalID_BUTTON_FeedOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_ZengShou, s_CUI_ID_FRAME_SuAnimalID_BUTTON_ZengShouOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_FangSheng, s_CUI_ID_FRAME_SuAnimalID_BUTTON_FangShengOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SuAnimal, ID_CHECKBOX_Base, s_CUI_ID_FRAME_SuAnimalID_CHECKBOX_BaseOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SuAnimal, ID_CHECKBOX_ZZUp, s_CUI_ID_FRAME_SuAnimalID_CHECKBOX_ZZUpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SuAnimal, ID_CHECKBOX_ZZDown, s_CUI_ID_FRAME_SuAnimalID_CHECKBOX_ZZDownOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SuAnimal, ID_CHECKBOX_ZhanDou, s_CUI_ID_FRAME_SuAnimalID_CHECKBOX_ZhanDouOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_TuJian, s_CUI_ID_FRAME_SuAnimalID_BUTTON_TuJianOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_ZhaoHui, s_CUI_ID_FRAME_SuAnimalID_BUTTON_ZhaoHuiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimal, ID_BUTTON_ZhaoHuan, s_CUI_ID_FRAME_SuAnimalID_BUTTON_ZhaoHuanOnButtonClick );

	theUiManager.OnButtonClick(ID_FRAME_SuAnimal,ID_BUTTON_PetCompare,s_CUI_ID_FRAME_SuAnimalID_BUTTON_PetCompareOnButtonClick);
	theUiManager.OnButtonClick(ID_FRAME_SuAnimal,ID_BUTTON_WuXinUpper,s_CUI_ID_FRAME_SuAnimalID_BUTTON_WuXinUpperOnButtonClick);

	theUiManager.OnButtonClick(ID_FRAME_SuAnimal,ID_BUTTON_SuAnimalUp,s_CUI_ID_FRAME_SuAnimalID_BUTTON_SuAnimalUpOnButtonClick);
	
	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip1, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip1, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip1, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip1, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip1OnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip2, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip2, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip2, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip2, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip2OnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip3, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip3, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip3, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip3, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip3OnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip4, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip4, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip4, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip4, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip4OnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip5, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip5OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip5, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip5OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip5, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip5OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip5, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_PetEquip5OnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_SkillXT, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_SkillXTOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_SkillXT, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_SkillXTOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_SkillXT, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_SkillXTOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_SkillXT, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_SkillXTOnIconRButtonUp );

	theUiManager.OnIconDragOn( ID_FRAME_SuAnimal, ID_LISTIMG_SkillHT, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_SkillHTOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SuAnimal, ID_LISTIMG_SkillHT, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_SkillHTOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SuAnimal, ID_LISTIMG_SkillHT, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_SkillHTOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SuAnimal, ID_LISTIMG_SkillHT, s_CUI_ID_FRAME_SuAnimalID_LISTIMG_SkillHTOnIconRButtonUp );


	m_pID_BUTTON_ZhaoHuan = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_ZhaoHuan );
	m_pID_FRAME_SuAnimal = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SuAnimal );
	m_pID_BUTTON_ChuZhan = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_ChuZhan );
	m_pID_TEXT_LIL = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_LIL );
	m_pID_TEXT_MJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_MJ );
	m_pID_TEXT_LL = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_LL );
	m_pID_TEXT_NL = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_NL );
	m_pID_TEXT_Star= (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_Star );
	m_pID_TEXT_ReliveTime = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_ReliveTime );
	m_pID_TEXT_ChengHao = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_ChengHao);
	m_pID_BUTTON_XSCH = (ControlButton *)theUiManager.FindControl(ID_FRAME_SuAnimal,ID_BUTTON_XSCH);
	m_pID_TEXT_DJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_DJ );
	m_pID_TEXT_KLD = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_KLD );
	m_pID_TEXT_name = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_name );
	m_pID_TEXT_ChengZhangLv = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_ChengZhangLv );
	m_pID_TEXT_LILZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_LILZZ );
	m_pID_TEXT_LLZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_LLZZ );
	m_pID_TEXT_NLZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_NLZZ );
	m_pID_TEXT_MJZZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_MJZZ );
	m_pID_TEXT_Point = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_Point );
	m_pID_TEXT_Generation = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_Generation );
	m_pID_LIST_ShouLan = (ControlList*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LIST_ShouLan );
	m_pID_BUTTON_XiuXi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_XiuXi );
	m_pID_TEXT_SYDJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_SYDJ );
	m_pID_BUTTON_FangSheng = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_FangSheng );
	m_pID_PICTURE_Yingxiang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_Yingxiang );
	m_pID_LISTIMG_ZhuDong = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_ZhuDong );
	m_pID_LISTIMG_PetEquip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip );
	m_pID_LISTIMG_BeiDong = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_BeiDong );
	m_pID_TEXT_Exp = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_Exp );
	m_pID_BUTTON_GaiMing = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_GaiMing );
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_Right );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_Left );
	//m_pID_BUTTON_Feed = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_Feed );

	m_pID_BUTTON_PlusLiLiang = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_PlusLiLiang );
	m_pID_BUTTON_SubtractLiLiang = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_SubtractLiLiang );
	m_pID_BUTTON_PlusTiZhi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_PlusTiZhi );
	m_pID_BUTTON_SubtractTiZhi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_SubtractTiZhi );
	m_pID_BUTTON_PlusMinJie = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_PlusMinJie );
	m_pID_BUTTON_SubtractMinJie = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_SubtractMinJie );
	m_pID_BUTTON_PlusZhiLi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_PlusZhiLi );
	m_pID_BUTTON_SubtractZhiLi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_SubtractZhiLi );
	m_pID_LIST_War = (ControlList*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LIST_War );
	m_pID_BUTTON_Confirm = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_Confirm );
	m_pID_BUTTON_Renew = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_Renew );
	m_pID_BUTTON_SuAnimalUp= (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_SuAnimalUp );

	m_pID_BUTTON_UnLock = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_UnLock);
	m_pID_BUTTON_Lock = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_Lock);	

	m_pID_TEXT_TakeNum = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_TakeNum );

	m_pID_LISTIMG_PetIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_PetIcon );
	m_pID_LISTIMG_QiCheng = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_QiCheng );

	m_pID_TEXT_MountName = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_MountName );

	m_pID_TEXT_MountLv = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_MountLv );

	m_pID_TEXT_WuXing = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_WuXing );
	m_pID_TEXT_GenGu = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_GenGu );
	m_pID_TEXT_FZCS = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_FZCS );
	m_pID_PROGRESS_Exp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PROGRESS_Exp );
	m_pID_PROGRESS_Hp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PROGRESS_Hp );
	//m_pID_PROGRESS_Happy = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PROGRESS_Happy );
	m_pID_PROGRESS_Life = (ControlProgress*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PROGRESS_Life );

	m_pID_BUTTON_Cure = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_Cure );
	//m_pID_BUTTON_Feed = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_Feed );
	m_pID_BUTTON_ZengShou = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_ZengShou );
	m_pID_BUTTON_FangSheng = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_FangSheng );

	m_pID_TEXT_WLGJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_WLGJ );
	m_pID_TEXT_WLFY = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_WLFY );
	m_pID_TEXT_FSGJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_FSGJ );
	m_pID_TEXT_FSFY = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_FSFY );
	m_pID_TEXT_MZ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_MZ );
	m_pID_TEXT_DB = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_DB );
	m_pID_TEXT_HXGJ = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_HXGJ );
	m_pID_TEXT_HXFY = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_HXFY );
	m_pID_TEXT_DaoHang = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_DaoHang );

	m_pID_PICTURE_Base = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_Base );
	m_pID_PICTURE_ZZ = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_ZZ );
	m_pID_PICTURE_ZhanDou = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_ZhanDou );

	m_pID_CHECKBOX_Base = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_CHECKBOX_Base );
	m_pID_CHECKBOX_ZZUp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_CHECKBOX_ZZUp );
	m_pID_CHECKBOX_ZZDown = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_CHECKBOX_ZZDown );
	m_pID_CHECKBOX_ZhanDou = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_CHECKBOX_ZhanDou );
	m_pID_BUTTON_TuJian = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_TuJian );

	m_pID_BUTTON_ZhaoHui = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_ZhaoHui );
	m_pID_PICTURE_XBXiong = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_XBXiong );
	m_pID_PICTURE_XBCi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_XBCi );
	m_pID_TEXT_XingGe = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_XingGe );
	m_pID_TEXT_Life = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_Life );
	//m_pID_TEXT_Happy = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_Happy );
	m_pID_TEXT_Level = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_Level );
	m_pID_TEXT_ZDL = (ControlText*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_TEXT_ZDL );
	
	m_pID_PICTURE_LeiBieWu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_LeiBieWu );
	m_pID_PICTURE_LeiBieFa = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_LeiBieFa );

	m_pID_PICTURE_WXJin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_WXJin );
	m_pID_PICTURE_WXMu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_WXMu );
	m_pID_PICTURE_WXShui = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_WXShui );
	m_pID_PICTURE_WXHuo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_WXHuo );
	m_pID_PICTURE_WXTu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_WXTu );

	m_pID_PICTURE_ZhongZu1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_ZhongZu1 );
	m_pID_PICTURE_ZhongZu2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_PICTURE_ZhongZu2 );
	m_pID_TEXT_CWName = (ControlText*)theUiManager.FindControl(ID_FRAME_SuAnimal,ID_TEXT_CWName);

	m_pID_TEXT_LILZZPercent = (ControlText*)theUiManager.FindControl(ID_FRAME_SuAnimal,ID_TEXT_LILZZPercent);
	m_pID_TEXT_MJZZPercent = (ControlText*)theUiManager.FindControl(ID_FRAME_SuAnimal,ID_TEXT_MJZZPercent);
	m_pID_TEXT_NLZZPercent = (ControlText*)theUiManager.FindControl(ID_FRAME_SuAnimal,ID_TEXT_NLZZPercent);
	m_pID_TEXT_LLZZPercent = (ControlText*)theUiManager.FindControl(ID_FRAME_SuAnimal,ID_TEXT_LLZZPercent);
	m_pID_TEXT_Info		   =(ControlText*)theUiManager.FindControl(ID_FRAME_SuAnimal,ID_TEXT_Info);

	m_pID_BUTTON_PetCompare = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_PetCompare );
	m_pID_BUTTON_WuXinUpper = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_BUTTON_WuXinUpper );


	m_pID_LISTIMG_PetEquip1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip1 );
	m_pID_LISTIMG_PetEquip2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip2 );
	m_pID_LISTIMG_PetEquip3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip3 );
	m_pID_LISTIMG_PetEquip4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip4 );
	m_pID_LISTIMG_PetEquip5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_PetEquip5 );
	m_pID_LISTIMG_SkillXT = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_SkillXT );
	m_pID_LISTIMG_SkillHT = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SuAnimal, ID_LISTIMG_SkillHT );

	m_pPetEquip[0] = m_pID_LISTIMG_PetEquip1;
	m_pPetEquip[1] = m_pID_LISTIMG_PetEquip2;
	m_pPetEquip[2] = m_pID_LISTIMG_PetEquip3;
	m_pPetEquip[3] = m_pID_LISTIMG_PetEquip4;
	m_pPetEquip[4] = m_pID_LISTIMG_PetEquip5;

	assert( m_pID_BUTTON_ZhaoHuan);
	assert( m_pID_TEXT_SYDJ );
	assert( m_pID_TEXT_MountLv );
	assert( m_pID_TEXT_WuXing );
	assert( m_pID_TEXT_GenGu );
	assert( m_pID_TEXT_FZCS );
	assert( m_pID_PROGRESS_Exp );
	assert( m_pID_PROGRESS_Hp );
	//assert( m_pID_PROGRESS_Happy );
	assert( m_pID_PROGRESS_Life );
	assert( m_pID_BUTTON_Cure );
	//assert( m_pID_BUTTON_Feed );
	assert( m_pID_BUTTON_ZengShou );
	assert( m_pID_BUTTON_FangSheng );
	assert( m_pID_TEXT_LILZZ );
	assert( m_pID_TEXT_ChengZhangLv );
	assert( m_pID_TEXT_NLZZ );
	assert( m_pID_TEXT_MJZZ );
	assert( m_pID_TEXT_WLGJ );
	assert( m_pID_TEXT_WLFY );
	assert( m_pID_TEXT_FSGJ );
	assert( m_pID_TEXT_FSFY );
	assert(m_pID_TEXT_Star);
	assert( m_pID_TEXT_MZ );
	assert( m_pID_TEXT_DB );
	assert( m_pID_TEXT_HXGJ );
	assert( m_pID_TEXT_HXFY );
	assert( m_pID_TEXT_DaoHang );
	assert( m_pID_PICTURE_Base );
	assert( m_pID_PICTURE_ZZ );
	assert( m_pID_PICTURE_ZhanDou );
	assert( m_pID_CHECKBOX_Base );
	assert( m_pID_CHECKBOX_ZZUp );
	assert( m_pID_CHECKBOX_ZZDown );
	assert( m_pID_CHECKBOX_ZhanDou );
	assert( m_pID_BUTTON_TuJian );
	assert( m_pID_BUTTON_ZhaoHui );
	assert( m_pID_PICTURE_XBXiong );
	assert( m_pID_PICTURE_XBCi );
	assert( m_pID_TEXT_XingGe );
	assert( m_pID_TEXT_Life );
	//assert( m_pID_TEXT_Happy );
	assert( m_pID_TEXT_Level);
	assert( m_pID_TEXT_ZDL );
	assert( m_pID_PICTURE_LeiBieWu );
	assert( m_pID_PICTURE_LeiBieFa );
	assert( m_pID_PICTURE_WXJin );
	assert( m_pID_PICTURE_WXMu );
	assert( m_pID_PICTURE_WXShui );
	assert( m_pID_PICTURE_WXHuo );
	assert( m_pID_PICTURE_WXTu );
	assert( m_pID_PICTURE_ZhongZu1 );
	assert( m_pID_PICTURE_ZhongZu2 );
	assert(m_pID_TEXT_ReliveTime);
	assert(m_pID_TEXT_CWName);
	assert(m_pID_TEXT_LILZZPercent);
	assert(m_pID_TEXT_MJZZPercent);
	assert(m_pID_TEXT_NLZZPercent);
	assert(m_pID_TEXT_LLZZPercent);
	assert(m_pID_TEXT_ChengHao);
	assert(m_pID_BUTTON_XSCH);
	assert(m_pID_TEXT_Info);
	assert(m_pID_BUTTON_ChuZhan);
	assert(m_pID_BUTTON_XiuXi);
	assert(m_pID_BUTTON_ZhaoHuan);
	assert(m_pID_BUTTON_ZhaoHui);

	assert( m_pID_BUTTON_PetCompare);
	assert( m_pID_BUTTON_WuXinUpper );


	assert( m_pID_LISTIMG_PetEquip1);
	assert( m_pID_LISTIMG_PetEquip2);
	assert( m_pID_LISTIMG_PetEquip3);
	assert( m_pID_LISTIMG_PetEquip4);
	assert( m_pID_LISTIMG_PetEquip5);
	assert( m_pID_LISTIMG_SkillXT);
	assert( m_pID_LISTIMG_SkillHT);
	assert(m_pID_BUTTON_SuAnimalUp);

	//m_pID_BUTTON_XiuXi->SetVisable(false);
	//m_pID_BUTTON_ZhaoHuan->SetVisable(true);
	//m_pID_BUTTON_ZhaoHui->SetVisable(false);)
	SortControlGroup();
	m_pID_TEXT_Info->SetVisable(false);
	m_GroupBase.SetVisible(true);
	m_GroupFight.SetVisible(true);
	m_GroupGrowing.SetVisible(false);

	m_pID_BUTTON_ChuZhan->SetVisable(true);
	m_pID_BUTTON_XiuXi->SetVisable(false);

	m_pID_LISTIMG_ZhuDong->SetDisableCanbePick(true);
	m_pID_LISTIMG_ZhuDong->ShowPressEffect(true);

	m_pID_LISTIMG_PetEquip->SetDisableCanbePick(true);
	m_pID_LISTIMG_PetEquip->ShowPressEffect(true);

	m_pID_LISTIMG_PetEquip1->SetDisableCanbePick(true);
	m_pID_LISTIMG_PetEquip1->ShowPressEffect(true);
	m_pID_LISTIMG_PetEquip2->SetDisableCanbePick(true);
	m_pID_LISTIMG_PetEquip2->ShowPressEffect(true);
	m_pID_LISTIMG_PetEquip3->SetDisableCanbePick(true);
	m_pID_LISTIMG_PetEquip3->ShowPressEffect(true);
	m_pID_LISTIMG_PetEquip4->SetDisableCanbePick(true);
	m_pID_LISTIMG_PetEquip4->ShowPressEffect(true);
	m_pID_LISTIMG_PetEquip5->SetDisableCanbePick(true);
	m_pID_LISTIMG_PetEquip5->ShowPressEffect(true);

	m_pID_LISTIMG_SkillXT->SetDisableCanbePick(true);
	m_pID_LISTIMG_SkillXT->ShowPressEffect(true);
	m_pID_LISTIMG_SkillHT->SetDisableCanbePick(true);
	m_pID_LISTIMG_SkillHT->ShowPressEffect(true);

	m_pID_LISTIMG_BeiDong->SetDisableCanbePick(true);
	m_pID_LISTIMG_BeiDong->ShowPressEffect(true);

	m_pID_LISTIMG_QiCheng->SetDisableCanbePick(true);
	m_pID_LISTIMG_QiCheng->ShowPressEffect(true);

	m_pID_LISTIMG_PetIcon->SetShowCursorOnFrameOnNULLItem(false);

	m_pID_BUTTON_Right->SetLButtonDownFun(UISuAnimal_RightLBD);
	m_pID_BUTTON_Left->SetLButtonDownFun(UISuAnimal_LeftLBD);

	m_bCanMount = true;
	memset( m_PetsEnable, 0, sizeof( PetEnable ) * ITEM_MOUNT_MAXCOUNT );
	for( int i = 0 ; i < ITEM_MOUNT_MAXCOUNT ; ++ i )
	{
		m_PetsEnable[i].bEnable = true;
	}

	//m_pID_LISTIMG_ZhuDong->SetEnableCnt( 0 );
	//m_pPlayerAnim = MeNew CPlayerAnim;
	//m_pPlayer = MeNew CPlayer;
	//m_pPlayer->SetAnim( m_pPlayerAnim );
	//m_pPlayerAnim->SetPlayer( m_pPlayer );
	//theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayer );
	RenderAnim_Create(CUIRenderAnim::RTWUI_FUJIANG);

	SetButtonGroup();
	m_pID_LIST_War->SetSkipAllMsg(true);
	_SetVisable( false );
	return true;
}

void CUI_ID_FRAME_SuAnimal::SetButtonGroup()
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

void CUI_ID_FRAME_SuAnimal::SetArrayEnable(bool bEnable)
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
bool CUI_ID_FRAME_SuAnimal::_UnLoadUI()
{
	ResetMembers();
	RenderAnim_Destroy();
	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimal.meui" );
}
// 是否可视
bool CUI_ID_FRAME_SuAnimal::_IsVisable()
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return m_pID_FRAME_SuAnimal->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SuAnimal::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_SuAnimal )
		return;
	m_pID_FRAME_SuAnimal->SetVisable( bVisable );
	m_fRotateZ = 0.0f/*D3DX_PI / 2*/;
	m_nModelId = -1;
	if (bVisable)
		Refresh();

	if (bVisable)
	{
		/*if(thePlayerRole.GetActivedPet())
		{
			m_pID_BUTTON_ChuZhan->SetVisable(false);
			m_pID_BUTTON_ZhaoHui->SetVisable(true);
		}
		else
		{
			m_pID_BUTTON_ChuZhan->SetVisable(true);
			m_pID_BUTTON_ZhaoHui->SetVisable(false);
		}*/

		RefreshButtonGroup();
		s_CUI_ID_FRAME_MainMenu.SetNeedSpark(false, CUI_ID_FRAME_MainMenu::ekey_pet);
	}
	if( bVisable )
	{
		PlaySoundConfig( SoundConfig::EST_OpenPetUI );
		//设置UI上的列表框的选择项 默认为当前出战的 没就为第一个
		SPetItem* pPet = thePlayerRole.GetActivedPet();
		if(pPet)
		{
			//int Index = m_pID_LIST_ShouLan->FindItemByItem(pPet->GetPetName());
			int index = thePlayerRole.GetActivedPetIndex() == -1?0:thePlayerRole.GetActivedPetIndex();
			m_pID_LIST_ShouLan->SetCurSelIndex(index);
			ID_BUTTON_RenewOnButtonClick(m_pID_BUTTON_Renew);
			ID_LIST_ShouLanOnListSelectChange(m_pID_LIST_ShouLan,m_pID_LIST_ShouLan->GetCurSelItem());
		}
	}
}

void CUI_ID_FRAME_SuAnimal::RefreshEnable( int nIndex, bool bEnable )
{
	if( !m_pID_FRAME_SuAnimal )
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
		//m_pID_BUTTON_Feed->SetEnable(bEnable);
		m_pID_BUTTON_Lock->SetEnable(bEnable);
		m_pID_BUTTON_UnLock->SetEnable(bEnable);
	}

}

void CUI_ID_FRAME_SuAnimal::RefreshPetEnableList()
{
	// 更新enable列表，确保与当前list对应,如果不对应设置为enable
	for( int i = 0 ; i < ITEM_PET_MAXCOUNT ; ++ i )
	{
		bool bFound = false;		
		int nMaxCount = thePetSettingConfig.GetPlayerPetLimit(thePlayerRole.GetLevel());
		for( int j = 0 ; j < nMaxCount; ++ j )
		{
			if( thePlayerRole.GetCharInfo2().ItemBagData.petItems[j].baseInfo.guid == m_PetsEnable[i].guid && 
				thePlayerRole.GetCharInfo2().ItemBagData.petItems[j].baseInfo.guid != 0 )			
			{
				bFound = true;				
				m_PetsEnable[j].guid = thePlayerRole.GetCharInfo2().ItemBagData.petItems[j].baseInfo.guid;
				m_PetsEnable[j].bEnable = ( !IsMountInPrivateShop( m_PetsEnable[j].guid ) && !IsMountInBargaining( m_PetsEnable[j].guid ) );
				break;
			}

		}
		if( !bFound )
		{
			m_PetsEnable[i].guid = thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.guid;
			m_PetsEnable[i].bEnable = true;
		}		
	}
}

int CUI_ID_FRAME_SuAnimal::GetMountIndexByGuid( __int64 guid )
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

void CUI_ID_FRAME_SuAnimal::Refresh(bool bSelectEnd)
{
	SetNeedRefresh(true);
	m_bSelectEnd = bSelectEnd;
}

void CUI_ID_FRAME_SuAnimal::SetNeedRefresh(bool bNeed)
{
	m_bNeedRefresh = bNeed;
}

void CUI_ID_FRAME_SuAnimal::RefreshHelp(bool bSelectEnd)
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

			DWORD dwColor =  Color_Config.getColor( CC_ItemTip_Name_Quality0 );
			sData.SetData( thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.szName, 
				thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId, 
				0, 
				dwColor );
			m_pID_LIST_ShouLan->AddItem(&sData,NULL, false);

			// 添加icon到控件
			ControlListImage::S_ListImg stItemImage;
			stItemImage.SetData( thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.petId, 1 );
			((SCharItem*)stItemImage.m_pkIconInfo->GetData())->itembaseinfo.nOnlyInt = thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.guid;

			m_pID_LISTIMG_PetIcon->SetItem( &stItemImage, i );

			if (thePlayerRole.GetCharInfo2().ItemBagData.petItems[i].baseInfo.isActive)
			{
				m_pActivedPet = &thePlayerRole.GetCharInfo2().ItemBagData.petItems[i];
				nActivePetIndex = i;				
			}
		}
	}

	char buf[64];
	sprintf(buf, "%d/%d", thePlayerRole.GetPetCount(), nMaxCount);
	m_pID_TEXT_TakeNum->SetText(buf);

	RefreshFightState(nActivePetIndex);

	if (bSelectEnd)
		m_pID_LIST_ShouLan->SetCurSelIndex(nSelId/*m_pID_LIST_ShouLan->GetListItemCnt() - 1*/);		//为什么要选择最后一个？
	else if (nSelId == -1)
		m_pID_LIST_ShouLan->SetCurSelIndex(0);
	else
		m_pID_LIST_ShouLan->SetCurSelIndex(nSelId);

	RefreshIconInfo();
	if (thePlayerRole.GetPetCount() <= 0)
	{
		//CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,theXmlString.GetString(eText_HaveNonePet));
		m_pID_TEXT_Info->SetVisable(true);
		m_pID_TEXT_Info->SetText(theXmlString.GetString(eText_HaveNonePet),Color_Config.getColor(CC_TwoRedName));
		SetPetProperty(false);
	}
	else
	{
		m_pID_TEXT_Info->SetVisable(false);
		SetPetProperty(true);
	}
}

void CUI_ID_FRAME_SuAnimal::SetFloatText(ControlText* pText, float v)
{
	char szTemp[32];
	sprintf( szTemp, "%.2f", v );
	pText->SetText(szTemp);
}

void CUI_ID_FRAME_SuAnimal::PetSelectChanged(int nIndex)
{
	SetArrayEnable(false);
	m_pID_TEXT_DJ->SetText("");		// 等级
	m_pID_TEXT_SYDJ->SetText("");	// 携带等级
	m_pID_TEXT_KLD->SetText("");	// 快乐度
	m_pID_TEXT_LL->SetText("");		// 灵力
	m_pID_TEXT_MJ->SetText("");		// 敏捷
	m_pID_TEXT_NL->SetText("");		// 体质
	m_pID_TEXT_LIL->SetText("");	// 力量
	m_pID_TEXT_LILZZ->SetText("");  //力量资质
	m_pID_TEXT_LLZZ->SetText("");	// 灵力资质
	m_pID_TEXT_MJZZ->SetText("");	// 敏捷资质
	m_pID_TEXT_NLZZ->SetText("");	// 体质资质
	m_pID_TEXT_LILZZPercent->SetText("");  //力量资质
	m_pID_TEXT_MJZZPercent->SetText("");  //力量资质
	m_pID_TEXT_NLZZPercent->SetText("");  //力量资质
	m_pID_TEXT_LLZZPercent->SetText("");  //力量资质
	m_pID_TEXT_ChengZhangLv->SetText("");//成长率
	m_pID_TEXT_ChengHao->SetText("");//称号

	m_pID_TEXT_name->SetText("");	// 名字
	m_pID_TEXT_Point->SetText("");	// 潜力点
	m_pID_TEXT_Generation->SetText(""); // 辈分

	m_pID_TEXT_MountLv->SetText("");	// 设置携带等级

	m_pID_TEXT_Exp->SetText("");	// 经验

	m_pID_LISTIMG_ZhuDong->Clear();
	m_pID_LISTIMG_PetEquip->Clear();
	m_pID_LISTIMG_PetEquip1->Clear();
	m_pID_LISTIMG_PetEquip2->Clear();
	m_pID_LISTIMG_PetEquip3->Clear();
	m_pID_LISTIMG_PetEquip4->Clear();
	m_pID_LISTIMG_PetEquip5->Clear();

	m_pID_LISTIMG_SkillXT->Clear();
	m_pID_LISTIMG_SkillHT->Clear();

	m_pID_LISTIMG_BeiDong->Clear();
	m_pID_LISTIMG_QiCheng->Clear();

	m_pID_BUTTON_Lock->SetEnable(false);
	m_pID_BUTTON_UnLock->SetEnable(false);

	m_pID_BUTTON_ChuZhan->SetEnable(false);
	m_pID_BUTTON_XiuXi->SetEnable(false);
	m_pID_BUTTON_FangSheng->SetEnable(false);
	m_pID_BUTTON_GaiMing->SetEnable(false);
	//m_pID_BUTTON_Feed->SetEnable( false );

	m_pID_TEXT_MountName->SetText(""); // 宠物原始名称
	m_pID_TEXT_CWName->SetText("");
	if (nIndex < 0)
		return;

	SPetItem& mount = thePlayerRole.GetPetByIndex(nIndex);
	if (mount.baseInfo.petId != InvalidLogicNumber)
	{
		if( m_PetsEnable[nIndex].bEnable )
		{
			m_pID_BUTTON_ChuZhan->SetEnable(true);
			m_pID_BUTTON_XiuXi->SetEnable(true);
			m_pID_BUTTON_GaiMing->SetEnable(true);
			//m_pID_BUTTON_Feed->SetEnable( true );
			m_pID_BUTTON_UnLock->SetEnable(true);
			m_pID_BUTTON_Lock->SetEnable(true);
			m_pID_BUTTON_FangSheng->SetEnable( !mount.baseInfo.isActive );
		}
		m_pID_BUTTON_ChuZhan->SetVisable( !mount.baseInfo.isActive );
		m_pID_BUTTON_XiuXi->SetVisable( mount.baseInfo.isActive );

// 		if( mount.xLockInfo.bIsLocked )
// 		{
// 			m_pID_BUTTON_Lock->SetVisable( false );
// 			m_pID_BUTTON_UnLock->SetVisable( true );
// 			m_pID_BUTTON_FangSheng->SetEnable( false );
// 			if( mount.xLockInfo.nUnLockLeftTime > 0 )
// 			{
// 				m_pID_BUTTON_UnLock->SetEnable( false );
// 			}
// 		}
// 		else
// 		{
// 			m_pID_BUTTON_Lock->SetVisable( true );
// 			m_pID_BUTTON_UnLock->SetVisable( false );
// 		}

		if (mount.baseInfo.nPotentialPoint > 0)
		{
			SetArrayEnable(true);
		}

		//刷新属性
		RefreshProperty(&mount);

		// Skill
		RefreshMountSkill(mount);

		if (GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT))
		{
			ItemDefine::SPetMonster *pPetMonster = GettheItemDetail().GetPetById(mount.baseInfo.petId);
			if(!pPetMonster)
				return;

			if(CommonChatFrame::GetActiveChatFrame()->ItemHyberCnt == 0)
			{
				CommonChatFrame::GetActiveChatFrame()->addHyberText( pPetMonster->GetName(), 
					mount.baseInfo.guid, mount.baseInfo.petId, BT_PetBag );
				CommonChatFrame::GetActiveChatFrame()->IsSetPet = true;
			}
			else
			{
				//CommonChatFrame::GetActiveChatFrame()->ShowTextInChatList( theXmlString.GetString(eText_Char_PetInfo),0xFFAA0000 );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FamilyEx,theXmlString.GetString(eText_Char_PetInfo));
			}
		}

		// Set display model
		ChangeModel( mount.baseInfo.petId );
		UpdatePetEquipByNowSelect();
		RefreshMountStar(mount);
	}
}

void CUI_ID_FRAME_SuAnimal::ActivePet(int nIndex)
{
	// 移动中不能召唤副将
	CPlayer *me = theHeroGame.GetPlayerMgr()->GetMe();
	if (me != NULL && me->IsMoving())
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Info_ChatSys, theXmlString.GetString(eText_CantCallFuJianWhenMoing));
		return;
	}

	if (nIndex < 0)
		return;
	SPetItem &mount = thePlayerRole.GetPetByIndex(nIndex);
// 	if(GetPetCoolDownTime(&mount) >0 )  //冷却时间
// 	{
// 		char temp[32];
// 		MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetNoReLife),(GetPetCoolDownTime(&mount)/1000));
// 		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, temp );
// 		return;
// 	} 

	int petTakeLevel = PET_LEVEL_OVERTOP_MAX + thePetSettingConfig.GetSavvyAddTakeLevel( mount.baseInfo.savvy );
	if ( mount.baseInfo.level > thePlayerRole.GetLevel() + petTakeLevel )
	{//出战等级不足
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString( eText_PetChuZhanLevelNotEnough ) );
		return;
	}
	ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById(mount.baseInfo.petId);
	if (pPetMonster != NULL && pPetMonster->takeLevel > thePlayerRole.GetLevel() )
	{//携带等级不足
		char temp[64];
		MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetLessTakeLevel),pPetMonster->takeLevel);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, temp);
		return;
	}
	if (mount.baseInfo.petId != InvalidLogicNumber )
	{
		ActivePet(mount,nIndex);
		if (!mount.baseInfo.isActive && m_pID_FRAME_SuAnimal)
		{
			m_pID_FRAME_SuAnimal->SetVisable(false);//出战的时候关闭当前界面
		}
		//m_IsActivePet = true;
		//m_dwStartIntonateTime = HQ_TimeGetTime();
	}
}

void CUI_ID_FRAME_SuAnimal::ActivePet(SPetItem& mount, int nIndex)
{
// 	if (thePlayerRole.GetActivedPetIndex() != nIndex)
// 		Dismount();
	
 	if (!mount.baseInfo.isActive)
 	{
		CWorldTile* pCurrTile = CURRENTTILE;
		if(!pCurrTile)
			return;
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(pCurrTile->GetMapId());
		if (!pMapData)
		{
			return;
		}
		if (!pMapData->CanPet)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ListInfo_RandomTip, theXmlString.GetString( eText_PetError_OnActive ) );
			return;
		}
		ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eSSI_PetActive, nIndex+1);
		CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->GetMe();
		if ( pPlayer == NULL )		
		{
			return;
		} 
		//lyh添加移动中不能召唤副将
		if (pPlayer->IsMoving())
		{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MovingContZHFJ ) );
		 return;
		}

			pPlayer->TryUseSkill( pPlayer, pSkill );
		
		
 	}
 	else
 	{
 		MsgChangePet changePet;
 		changePet.nIndex = nIndex;
 		changePet.ucOpType = MsgChangePet::EOT_UnActive;
 		changePet.guid = mount.baseInfo.guid;
 		GettheNetworkInput().SendMsg(&changePet);
 	}
}

static bool IfDiscardPet(char bPressYesButton, void *pData)
{
	if (bPressYesButton && pData)
	{
		MsgChangePet* changepet = (MsgChangePet*)pData;

		if (changepet->nIndex == thePlayerRole.GetActivedPetIndex())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eUI_CanNotDestroyActivedMount ) );
			return false;
		}

		GettheNetworkInput().SendMsg(changepet);

		SPetItem& mount = thePlayerRole.GetPetByIndex(changepet->nIndex);
		mount.baseInfo.nPotentialPoint = 0;
		return true;
	}
	return false;
}

void CUI_ID_FRAME_SuAnimal::DiscardPet(int nIndex)
{
	if (nIndex < 0)
		return;

	SPetItem& mount = thePlayerRole.GetPetByIndex(nIndex);
	if (mount.baseInfo.petId != InvalidLogicNumber)
	{
		if (mount.baseInfo.isActive)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eUI_CanNotDestroyActivedMount ) );
			return;
		}

		MsgChangePet changepet;
		changepet.nIndex = nIndex;
		changepet.guid = mount.baseInfo.guid;
		changepet.ucOpType =MsgChangePet::EOT_Disappear;

		DWORD dwColor = 0;
		ItemDefine::SPetMonster* pCommon = GettheItemDetail().GetPetById( mount.baseInfo.petId );
		//if( pCommon )
			dwColor = Color_Config.getColor(CC_PetColor_White);//S_IconInfoHero::GetQualityColor( mount.baseInfo.quality );

		char buf[256];
		char name[MAX_PATH] = {0};
		sprintf(name, "{#%x=%s#}", dwColor, mount.baseInfo.szName);
		sprintf(buf, theXmlString.GetString(eText_QueryDiscardPet), name);
		s_CUI_ID_FRAME_MessageBox.Show( buf, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
			false, IfDiscardPet, &changepet, sizeof(MsgChangePet) );
	}
}

bool CUI_ID_FRAME_SuAnimal::IsActivedPet() const
{
	return thePlayerRole.GetActivedPet();
}

void CUI_ID_FRAME_SuAnimal::Mount()
{
// 	if (thePlayerRole.GetActivedMount())
// 	{
// 		theHeroGame.GetPlayerMgr()->SetCurUseSkill( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT_SKILL_ID, 1 );
// 		thePlayerRole.UpdateUI();
// 		theHeroGame.GetPlayerMgr()->OnSkill( false );
// 	}
// 	else
// 	{
// 		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_NotActived ) );
// 	}
}

void CUI_ID_FRAME_SuAnimal::Dismount()
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

void CUI_ID_FRAME_SuAnimal::ID_LIST_ShouLanOnListLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	s_CUI_ID_FRAME_SuAnimal.PetSelectChanged(s_CUI_ID_FRAME_SuAnimal.m_pID_LIST_ShouLan->GetCurSelIndex());
	s_CUI_ID_FRAME_SuAnimal.ActivePet(s_CUI_ID_FRAME_SuAnimal.m_pID_LIST_ShouLan->GetCurSelIndex());
}

bool CUI_ID_FRAME_SuAnimal::HasSkill(int nId)
{
	return false;
}

bool CUI_ID_FRAME_SuAnimal::IsSkillList(const ControlObject* pObject)
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return m_pID_LISTIMG_ZhuDong == pObject || m_pID_LISTIMG_QiCheng == pObject || m_pID_LISTIMG_SkillXT == pObject || m_pID_LISTIMG_SkillHT == pObject;
}
void CUI_ID_FRAME_SuAnimal::RefreshMountStar(SPetItem& mount)
{
	//显示副将的星级
	m_pID_TEXT_Star->SetText("");
	if(mount.baseInfo.quality== 0)
	{
		//一星
		m_pID_TEXT_Star->SetText("{#77701}");
	}
	else if(mount.baseInfo.quality== 1)
	{
		m_pID_TEXT_Star->SetText("{#77702}");
	}
	else if(mount.baseInfo.quality == 2)
	{
		m_pID_TEXT_Star->SetText("{#77703}");
	}
	else if(mount.baseInfo.quality ==3)
	{
		m_pID_TEXT_Star->SetText("{#77704}");
	}
	else if(mount.baseInfo.quality== 4)
	{
		m_pID_TEXT_Star->SetText("{#77705}");
	}
}
void CUI_ID_FRAME_SuAnimal::RefreshMountSkill()
{
	if( !m_pID_FRAME_SuAnimal )
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
			SPetItem& mount = thePlayerRole.GetPetByIndex(m_pID_LIST_ShouLan->GetCurSelIndex());
			if (mount.baseInfo.petId != InvalidLogicNumber)
			{
				ItemDefine::SPetMonster* pDrome = GettheItemDetail().GetPetById( mount.baseInfo.petId );
				if (pDrome)
				{
					DWORD dwDJColor = 0x00ffffff;
					if( pDrome->takeLevel > thePlayerRole.GetLevel() )
					{
						dwDJColor = 0xff0000;
						//m_bCanMount = false;
					}
					else
						//m_bCanMount = true;

					if( m_pID_TEXT_SYDJ )
						m_pID_TEXT_SYDJ->SetText(pDrome->takeLevel, dwDJColor);
				}
			}
		}
	}
}

void CUI_ID_FRAME_SuAnimal::RefreshMountSkill(SPetItem &mount)
{
// 	const SUIIconSet::SIconSet* pIcon = 
// 		g_UISkillMgr.GetSkillIconSet(CUI_ID_FRAME_BaseProperty::TYPE_MOUNT);
// 	if (pIcon)
// 	{
// 		ControlIconDrag::S_ListImg stItem;
// 		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
// 		stItem.SetData( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT, 1, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
// 		stItem.SetFlags(CUISkillMgr::eCommon);
// 		m_pID_LISTIMG_QiCheng->SetItem(&stItem);
// 	}

	CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
		GetPage(CUISkillMgr::ePetSkill);
	if (!pSkillTree)
		return;

	SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
	//m_pID_LISTIMG_ZhuDong->SetEnableCnt( mount.skillInfo.initiativeSkillNumber );

	ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( mount.GetPetID() );
	if ( pPetMonster == NULL ) 
		return;

	for ( int i = 0; i < SPetItem::PetDefine_MaxSkillCount; ++i)
	{
		unsigned short usSkillId = mount.skillInfo.skills[i].ustSkillID;
		if ( usSkillId == 0)
			continue;
		unsigned short usLevel = mount.skillInfo.skills[i].stSkillLevel;
		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(usSkillId,usLevel);
		if (!pItemSkill)
			continue;
		//const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue(usSkillId);
		//if (!pIcon)
		//	continue;

		ControlIconDrag::S_ListImg stItem;
		//stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
		stItem.SetData( usSkillId, usLevel, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
		stItem.SetFlags(CUISkillMgr::ePetSkill);

		SkillBag::SColdTime *pTime = NULL;
		pTime = thePlayerRole.m_PetSkillBag.GetColdTimeById( usSkillId );
		if ( pTime )
		{
			stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
		}

		m_pID_LISTIMG_ZhuDong->SetItem(&stItem);


		//设置技能
        if (pPetMonster->talentSkillId == usSkillId)
		{
			m_pID_LISTIMG_SkillXT->SetItem(&stItem);
		}
		else
		{
			m_pID_LISTIMG_SkillHT->SetItem(&stItem);
		}

// 		switch (pItemSkill->sSkillCategory)
// 		{
// 		case ItemDefine::SCT_PetPassive:
// 		case ItemDefine::SCT_PetMasterAutoUnControl:
// 			m_pID_LISTIMG_BeiDong->SetItem(&stItem);
// 			break;
// 		case ItemDefine::SCT_PetMasterManualControl:
// 			m_pID_LISTIMG_ZhuDong->SetItem(&stItem);
// 			break;
// 		}
	}
}

void CUI_ID_FRAME_SuAnimal::ChangePetName(const char* szName)
{
	if( !m_pID_FRAME_SuAnimal )
		return;
	if( !szName )
		return;

	int nSelId = m_pID_LIST_ShouLan->GetCurSelIndex();
	if (nSelId < 0)
		return ;

	strcpy(thePlayerRole.GetPetByIndex(nSelId).baseInfo.szName, szName);

	MsgChangePetName msg;
	msg.index = nSelId;
	strcpy(msg.szName, szName);
	GettheNetworkInput().SendMsg(&msg);

	Refresh();
}

void CUI_ID_FRAME_SuAnimal::ChangeModel(int fujiangID)
{
	ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById(fujiangID);
	if (pPetMonster == NULL)
		return;

	m_nModelId = pPetMonster->iModelID;

	//在获取副将的实际指针
	SPetItem& pPet = thePlayerRole.GetPetByIndex(m_pID_LIST_ShouLan->GetCurSelIndex());
	if(pPet.baseInfo.guid != InvalidLogicNumber && pPet.baseInfo.petId == fujiangID)
	{
		uint32 ModeID = pPet.baseInfo.PetModeID;//不用函数获得 服务器会自动修改设置为0的 
		if(ModeID != 0)
			m_nModelId = ModeID;
	}
	RenderAnim_SetModelID(m_nModelId);
}

bool CUI_ID_FRAME_SuAnimal::IsMountInBargaining( __int64 guid )
{
	return s_CUI_ID_FRAME_Bargaining.IsSelfItemInBargaining( guid );
}

bool CUI_ID_FRAME_SuAnimal::IsMountInPrivateShop( __int64 guid )
{
	if( !s_CUI_ID_FRAME_PrivateShop.IsVisable() && !s_CUI_ID_FRAME_PrivateShop.IsOpening() )
		return false;

	return CSystemStallage::Instance()->IsMountInStallage( guid );
}

bool CUI_ID_FRAME_SuAnimal::IsEqualToLISTIMG_PetIcon( ControlObject * pListImage )
{
	if( !m_pID_FRAME_SuAnimal || !pListImage )
		return false;
	return (m_pID_LISTIMG_PetIcon == (ControlListImage*)pListImage);
}

int CUI_ID_FRAME_SuAnimal::PenIcon_GetIndexByItem( ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal || !pItem )
		return -1;

	return m_pID_LISTIMG_PetIcon->GetItemIndex( pItem );
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_SuAnimal::PenIcon_GetItemByIndex( int index )
{
	if( !m_pID_FRAME_SuAnimal || index < 0 )
		return NULL;

	return m_pID_LISTIMG_PetIcon->GetItemByIndex( index );
}

bool CUI_ID_FRAME_SuAnimal::IsListImageByBagType(ControlObject* pObject)
{
	if(!m_pID_FRAME_SuAnimal)
		return false;

	if(m_pID_LISTIMG_PetIcon == pObject)
		return true;

	return false;
}

bool CUI_ID_FRAME_SuAnimal::IsInCoolDownTime(SPetItem* pPet)
{
// 	for ( int i = 0; i < SPetItem::PetDefine_MaxSkillCount; ++i)
// 	{
// 		unsigned short usSkillId = pPet->skillInfo.skills[i].ustSkillID;
// 		if ( usSkillId == 0)
// 			continue;	
// 
// 		SkillBag::SColdTime *pTime = NULL;
// 		pTime = thePlayerRole.m_PetSkillBag.GetColdTimeById(usSkillId);
// 		if (!pTime)
// 		{
// 			continue;
// 		}
// 
// 		if (HQ_TimeGetTime() - pTime->dwColdStartTime <= pTime->dwColdTime)
// 		{
// 			return true;
// 		}
// 	}
	return GetPetCoolDownTime(pPet) == 0 ? false:true;
	
}

void CUI_ID_FRAME_SuAnimal::SetStateByCoolDownTime(SPetItem* pPet)
{
	if (!pPet)
		return;

	if (IsInCoolDownTime(pPet))
	{
		m_pID_BUTTON_XiuXi->SetEnable(false);
	}
	else
	{
		m_pID_BUTTON_XiuXi->SetEnable(true);
	}
}

void CUI_ID_FRAME_SuAnimal::InitActivePicState()
{
	for (int i = 0; i <= ITEM_MOUNT_MAXCOUNT; ++i)
	{
		m_bActivePet[i] = false;
	}

	m_bNeedRefresh = false;
	m_bSelectEnd = false;
}

void CUI_ID_FRAME_SuAnimal::RefreshFightState(int nIndex)
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

void CUI_ID_FRAME_SuAnimal::RefreshFightIcon()
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

void CUI_ID_FRAME_SuAnimal::SortControlGroup()
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
	m_GroupBase.AddControl(m_pID_TEXT_LILZZPercent);
	m_GroupBase.AddControl(m_pID_TEXT_LLZZPercent);
	m_GroupBase.AddControl(m_pID_TEXT_NLZZPercent);
	m_GroupBase.AddControl(m_pID_TEXT_MJZZPercent);

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


bool CUI_ID_FRAME_SuAnimal::UISuAnimal_RightLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_SuAnimal.SetRotate(true);
	return true;
}

bool CUI_ID_FRAME_SuAnimal::UISuAnimal_LeftLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_SuAnimal.SetRotate(true);
	return true;
}

bool CUI_ID_FRAME_SuAnimal::LockPet( const char bPressYesButton, void *pData )
{
	if(bPressYesButton && pData)
	{
		//MsgLockItemReq msg;
		//::CopyMemory(&msg,pData,sizeof(MsgLockItemReq));
		//GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}

bool CUI_ID_FRAME_SuAnimal::UnLockPet( const char bPressYesButton, void *pData )
{
	if(bPressYesButton && pData)
	{
		//MsgUnLockItemReq msg;
		//::CopyMemory(&msg,pData,sizeof(MsgUnLockItemReq));
		//GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}

bool CUI_ID_FRAME_SuAnimal::PetUseSkill(ControlIconDrag::S_ListImg* pItem)
{
	if( !pItem )
		return false;

	switch (pItem->m_dwFlags)
	{
	case CUISkillMgr::ePetSkill:
		{
			SCharSkill *pSkill = NULL;
			pSkill = thePlayerRole.m_PetSkillBag.GetSkillByID( pItem->m_pkIconInfo->Id() );
			if ( !pSkill )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_FuJiang_NotActived ) );
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

void CUI_ID_FRAME_SuAnimal::UpdateIconInfo()
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

		bool bEnable = pItem->m_eEnable;

		int nSrcIndex = m_pID_LISTIMG_PetIcon->GetItemIndex( pItem );
		SPetItem smItem = thePlayerRole.m_charinfo.ItemBagData.petItems[nSrcIndex];

		pItem->SetData( smItem.baseInfo.petId, 1,(bEnable ? eIcon_Enable : eIcon_Disable) );
	}
	else if ( m_pID_LISTIMG_PetEquip->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		RECT rcItem;
		m_pID_LISTIMG_PetEquip->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += m_pID_LISTIMG_PetEquip->GetItemWidth() / 2;
		rcItem.top += m_pID_LISTIMG_PetEquip->GetItemHeight() / 2;
		
		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetEquip->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );
		if(!pItem)
			return;
		int nSrcIndex = m_pID_LISTIMG_PetEquip->GetItemIndex( pItem );
		SCharItem& smItem = GetCurrentPet().baseInfo.PetEquip[nSrcIndex];
		pItem->SetData(&smItem);
	}
	else if ( m_pID_LISTIMG_PetEquip1->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		RECT rcItem;
		m_pID_LISTIMG_PetEquip1->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += m_pID_LISTIMG_PetEquip1->GetItemWidth() / 2;
		rcItem.top += m_pID_LISTIMG_PetEquip1->GetItemHeight() / 2;
		
		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetEquip1->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );
		if(!pItem)
			return;
		int nSrcIndex = 0;
		SCharItem& smItem = GetCurrentPet().baseInfo.PetEquip[nSrcIndex];
		pItem->SetData(&smItem);
	}
	else if ( m_pID_LISTIMG_PetEquip2->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		RECT rcItem;
		m_pID_LISTIMG_PetEquip2->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += m_pID_LISTIMG_PetEquip2->GetItemWidth() / 2;
		rcItem.top += m_pID_LISTIMG_PetEquip2->GetItemHeight() / 2;
		
		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetEquip2->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );
		if(!pItem)
			return;
		int nSrcIndex = 1;
		SCharItem& smItem = GetCurrentPet().baseInfo.PetEquip[nSrcIndex];
		pItem->SetData(&smItem);
	}
	else if ( m_pID_LISTIMG_PetEquip3->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		RECT rcItem;
		m_pID_LISTIMG_PetEquip3->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += m_pID_LISTIMG_PetEquip3->GetItemWidth() / 2;
		rcItem.top += m_pID_LISTIMG_PetEquip3->GetItemHeight() / 2;
		
		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetEquip3->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );
		if(!pItem)
			return;
		int nSrcIndex = 2;
		SCharItem& smItem = GetCurrentPet().baseInfo.PetEquip[nSrcIndex];
		pItem->SetData(&smItem);
	}
	else if ( m_pID_LISTIMG_PetEquip4->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		RECT rcItem;
		m_pID_LISTIMG_PetEquip4->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += m_pID_LISTIMG_PetEquip4->GetItemWidth() / 2;
		rcItem.top += m_pID_LISTIMG_PetEquip4->GetItemHeight() / 2;
		
		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetEquip4->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );
		if(!pItem)
			return;
		int nSrcIndex = 3;
		SCharItem& smItem = GetCurrentPet().baseInfo.PetEquip[nSrcIndex];
		pItem->SetData(&smItem);
	}
	else if ( m_pID_LISTIMG_PetEquip5->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		RECT rcItem;
		m_pID_LISTIMG_PetEquip5->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += m_pID_LISTIMG_PetEquip5->GetItemWidth() / 2;
		rcItem.top += m_pID_LISTIMG_PetEquip5->GetItemHeight() / 2;
		
		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetEquip5->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );
		if(!pItem)
			return;
		int nSrcIndex = 4;
		SCharItem& smItem = GetCurrentPet().baseInfo.PetEquip[nSrcIndex];
		pItem->SetData(&smItem);
	}
}

void CUI_ID_FRAME_SuAnimal::RefreshIconInfo()
{
	if( !m_pID_FRAME_SuAnimal )
		return;

	RefreshPetEnableList();

	int nMaxCount = thePetSettingConfig.GetPlayerPetLimit(thePlayerRole.GetLevel());

	for( int i = 0; i < nMaxCount; ++i )
	{
		ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_PetIcon->GetItemByIndex( i );
		if( !pItem )
			continue;

		int nSrcIndex = m_pID_LISTIMG_PetIcon->GetItemIndex( pItem );
		if( nSrcIndex < 0 || nSrcIndex >= ITEM_MOUNT_MAXCOUNT )
			continue;

		SPetItem smItem = thePlayerRole.m_charinfo.ItemBagData.petItems[nSrcIndex];
		bool bEnable = m_PetsEnable[nSrcIndex].bEnable;

		pItem->SetData(smItem.baseInfo.petId,1,( bEnable ? eIcon_Enable : eIcon_Disable ));
	}
	PetSelectChanged( m_pID_LIST_ShouLan->GetCurSelIndex() );
	m_pID_FRAME_SuAnimal->SetRedraw();
}

void CUI_ID_FRAME_SuAnimal::RefreshProperty(SPetItem *pPetItem)
{
	if(!pPetItem)
		return;

	ItemDefine::SPetMonster *pPetMonster = GettheItemDetail().GetPetById(pPetItem->baseInfo.petId);
	if(!pPetMonster)
		return;

	
	//m_pID_TEXT_Generation->SetText( theXmlString.GetString( eText_MountGeneration_First + mount.baseInfo.generation ) );


	PetSettingConfig::STitle* pTitle = thePetSettingConfig.GetPetTitle( pPetItem->baseInfo.savvy, pPetItem->baseInfo.growStar, pPetItem->baseInfo.aptitudeLevel );
	/*if ( pTitle != NULL )
		m_pID_TEXT_ChengHao->SetText(pTitle->strTitleName.c_str());*/

    DWORD dwColor = 0;  //lyh修改宠物品质颜色
	int nQuality=0;
	if ( pTitle != NULL )
		dwColor = thePetSettingConfig.GetTitleColorByTitleName(pTitle->strTitleName,nQuality);
	if (dwColor == 0)
	{
		dwColor = S_IconInfoHero::GetQualityColor(nQuality);
	}

	
	//dwColor = S_IconInfoHero::GetQualityColor( pPetItem->baseInfo.quality ); //这个是服务器读取怪物表的品质的，错了

	DWORD dwDJColor = 0x00ffffff;
	if( pPetMonster->takeLevel > thePlayerRole.GetLevel() )
	{
		dwDJColor = 0xff0000;
		//m_bCanMount = false;
	}
	else
		//m_bCanMount = true;

	m_pID_TEXT_SYDJ->SetText(pPetMonster->takeLevel, dwDJColor);
	m_pID_TEXT_MountName->SetText(pPetMonster->GetName(), dwColor);        // 宠物原始名称
	m_pID_TEXT_name->SetText(pPetItem->baseInfo.szName,dwColor);

	if ( pTitle != NULL )
		m_pID_TEXT_ChengHao->SetText(pTitle->strTitleName.c_str(), dwColor);
	
	SetIntText(m_pID_TEXT_MountLv,pPetItem->baseInfo.takeLevel);           //携带等级
	SetIntText(m_pID_TEXT_Level,pPetItem->baseInfo.level);                 //等级
	SetIntText(m_pID_TEXT_WuXing,pPetItem->baseInfo.savvy);                //悟性
	SetIntText(m_pID_TEXT_GenGu,pPetItem->baseInfo.bone);                  //根骨
	//SetIntText(m_pID_TEXT_FZCS,pPetItem->baseInfo.breedNum);               //繁殖次数
	char breedNum[32];
	memset(breedNum,0,sizeof(breedNum));
	int breedMaxNum = thePetSettingConfig.GetPetBreedNum(pPetItem->baseInfo.level);
	MeSprintf_s(breedNum,sizeof(breedNum),"%d/%d",pPetItem->baseInfo.breedNum,breedMaxNum);
	m_pID_TEXT_FZCS->SetText(breedNum);

	m_pID_TEXT_XingGe->SetText("");
	m_pID_TEXT_XingGe->SetText(GetPetXingeString(pPetItem->baseInfo.characterize)); //性格
	//SetIntText(m_pID_TEXT_XingGe,pPetItem->baseInfo.characterize);         //性格

	//设置血量
	int nValue = 0;
	char szInfo[256] = {0};
	
	if ( pPetItem->baseInfo.GetFightAttribute(CharAttr_HPMax) != 0 )
	{
		nValue = pPetItem->baseInfo.hp*1000/pPetItem->baseInfo.GetFightAttribute(CharAttr_HPMax);
		m_pID_PROGRESS_Hp->SetValue(nValue);
	}
	//m_pID_PROGRESS_Hp->SetMaxValue(pPetItem->baseInfo.fightAttribute[CharAttr_HPMax]);	//血量

	
	MeSprintf_s(szInfo,sizeof(szInfo),"%d/%d",pPetItem->baseInfo.hp,pPetItem->baseInfo.GetFightAttribute(CharAttr_HPMax));
	m_pID_TEXT_KLD->SetText(szInfo);

	

	//去掉副将快乐度相关的  by liaojie 11.21
	//nValue = pPetItem->baseInfo.loyalty*1000/100;
	//m_pID_PROGRESS_Happy->SetValue(nValue);	//快乐
	//m_pID_PROGRESS_Happy->SetMaxValue(100.0f);

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
	if(dwTotalExp - dwLastLevelExp != 0)
	{
		__int64 iValue = iExp * 1000/(dwTotalExp - dwLastLevelExp);
		m_pID_PROGRESS_Exp->SetValue(iValue);          //经验
		//m_pID_PROGRESS_Exp->SetMaxValue(dwTotalExp - dwLastLevelExp);
	}

	MeSprintf_s(szInfo,sizeof(szInfo),"%I64u/%I64u",pPetItem->baseInfo.exp - dwLastLevelExp,dwTotalExp - dwLastLevelExp);
	m_pID_TEXT_Exp->SetText(szInfo);

	SetIntText(m_pID_TEXT_LIL, pPetItem->baseInfo.GetCurrentBaseAttr(EBaseAttr_Strength));	    // 力量
	SetIntText(m_pID_TEXT_MJ, pPetItem->baseInfo.GetCurrentBaseAttr(EBaseAttr_Agility));		    // 敏捷
	SetIntText(m_pID_TEXT_NL, pPetItem->baseInfo.GetCurrentBaseAttr(EBaseAttr_Stamina));		    // 耐力
	SetIntText(m_pID_TEXT_LL, pPetItem->baseInfo.GetCurrentBaseAttr(EBaseAttr_Intelligence));	    // 术法
	SetIntText(m_pID_TEXT_Point, pPetItem->baseInfo.nPotentialPoint);                           //潜力
	SetIntText(m_pID_TEXT_ChengZhangLv,pPetItem->baseInfo.growRate);                            //成长率
	
	 int m_AddPrecent = thePetSettingConfig.GetSavvyAddAptitudePer(pPetItem->baseInfo.savvy);
	 if (m_AddPrecent == 0)
	 {//悟性值为零时，无加成。
		 SetIntText(m_pID_TEXT_LILZZ,pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Strength));        //力量资质
		 SetIntText(m_pID_TEXT_MJZZ,pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Agility));          //敏捷资质
		 SetIntText(m_pID_TEXT_NLZZ,pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Stamina));          //耐力资质
		 SetIntText(m_pID_TEXT_LLZZ,pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Intelligence));    //灵力资质
		m_pID_TEXT_LILZZPercent->SetText("");
		m_pID_TEXT_MJZZPercent->SetText("");
		m_pID_TEXT_NLZZPercent->SetText("");
		m_pID_TEXT_LLZZPercent->SetText("");
	 }
	 else
	 {
		 char m_AddChar[16];
		 dwDJColor = Color_Config.getColor(CC_OrangeName);
		 if (pPetItem->baseInfo.savvy >= 6)
		 {
			 memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"%d",pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Strength));
			m_pID_TEXT_LILZZ->SetText(m_AddChar,dwDJColor);
			memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"(+%.1f%%)",(float)m_AddPrecent*0.1);
			m_pID_TEXT_LILZZPercent->SetText(m_AddChar,dwDJColor);

			memset(m_AddChar,0,sizeof(m_AddChar));
			MeSprintf_s(m_AddChar,sizeof(m_AddChar),"%d",pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Agility));
			m_pID_TEXT_MJZZ->SetText(m_AddChar,dwDJColor);
			memset(m_AddChar,0,sizeof(m_AddChar));
			MeSprintf_s(m_AddChar,sizeof(m_AddChar),"(+%.1f%%)",(float)m_AddPrecent*0.1);
			m_pID_TEXT_MJZZPercent->SetText(m_AddChar,dwDJColor);

			memset(m_AddChar,0,sizeof(m_AddChar));
			MeSprintf_s(m_AddChar,sizeof(m_AddChar),"%d",pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Stamina));
			m_pID_TEXT_NLZZ->SetText(m_AddChar,dwDJColor);
			memset(m_AddChar,0,sizeof(m_AddChar));
			MeSprintf_s(m_AddChar,sizeof(m_AddChar),"(+%.1f%%)",(float)m_AddPrecent*0.1);
			m_pID_TEXT_NLZZPercent->SetText(m_AddChar,dwDJColor);

			memset(m_AddChar,0,sizeof(m_AddChar));
			MeSprintf_s(m_AddChar,sizeof(m_AddChar),"%d",pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Intelligence));
			 m_pID_TEXT_LLZZ->SetText(m_AddChar,dwDJColor);
			 memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"(+%.1f%%)",(float)m_AddPrecent*0.1);
			 m_pID_TEXT_LLZZPercent->SetText(m_AddChar,dwDJColor);
		 }
		 else
		 {
			 memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"%d",pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Strength));
			 m_pID_TEXT_LILZZ->SetText(m_AddChar);
			 memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"(+%.1f%%)",(float)m_AddPrecent*0.1);
			 m_pID_TEXT_LILZZPercent->SetText(m_AddChar);

			 memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"%d",pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Agility));
			 m_pID_TEXT_MJZZ->SetText(m_AddChar);
			 memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"(+%.1f%%)",(float)m_AddPrecent*0.1);
			 m_pID_TEXT_MJZZPercent->SetText(m_AddChar);

			 memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"%d",pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Stamina));
			 m_pID_TEXT_NLZZ->SetText(m_AddChar);
			 memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"(+%.1f%%)",(float)m_AddPrecent*0.1);
			 m_pID_TEXT_NLZZPercent->SetText(m_AddChar);

			 memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"%d",pPetItem->baseInfo.GetCurrentAptitude(EBaseAttr_Intelligence));
			 m_pID_TEXT_LLZZ->SetText(m_AddChar);
			 memset(m_AddChar,0,sizeof(m_AddChar));
			 MeSprintf_s(m_AddChar,sizeof(m_AddChar),"(+%.1f%%)",(float)m_AddPrecent*0.1);
			 m_pID_TEXT_LLZZPercent->SetText(m_AddChar);
		 }
		 //SetIntText(m_pID_TEXT_LLZZ,pPetItem->baseInfo.currentAptitude[EBaseAttr_Intelligence]);    //灵力资质
	 }
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
	m_pID_BUTTON_ChuZhan->SetVisable( !pPetItem->baseInfo.isActive);
	m_pID_BUTTON_XiuXi->SetVisable( pPetItem->baseInfo.isActive);
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
}

void CUI_ID_FRAME_SuAnimal::UsePetItem(unsigned char ucValue)
{
	int nCount = thePlayerRole.m_bag.GetItemCount();
	for (int i = 0;i < nCount;++i)
	{
		SCharItem sItem;
		if(!thePlayerRole.m_bag.GetItem(i,&sItem))
			continue;

		ItemDefine::SItemCommon * pItemCommon = GettheItemDetail().GetItemByID(sItem.itembaseinfo.ustItemID);
		if(!pItemCommon)
			continue;

		if(pItemCommon->byUserTarget != ItemDefine::eTargetPet)
			continue;

		if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_RESTORE)
			continue;

		ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore*)pItemCommon;
		if(pRestore->specialFunction != ucValue)
			continue;

		MsgUseGoodsToPet msg;
		msg.nPetIndex = GetCurrentMountIndex();
		if(msg.nPetIndex != -1)
		{
			msg.nGuid = sItem.itembaseinfo.nOnlyInt;
			msg.ustItemIndex = i;
			msg.stItemCount = 1;
			msg.stSrcChar = 0;
			msg.stDstChar = 0;
			msg.ucItemBagType = BT_NormalItemBag;
			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	}
}

ControlProgress * CUI_ID_FRAME_SuAnimal::GetPROGRESS_petHp()
{
	if( !m_pID_FRAME_SuAnimal || !m_pID_PROGRESS_Hp )
		return NULL;
	return m_pID_PROGRESS_Hp;
}

void CUI_ID_FRAME_SuAnimal::LookPet(int index)
{
	if (!m_pID_FRAME_SuAnimal)  return ;
	m_pID_LIST_ShouLan->SetCurSelIndex(index);
	s_CUI_ID_FRAME_SuAnimal.SetVisable(true);
	PetSelectChanged(index);
}

DWORD  CUI_ID_FRAME_SuAnimal::GetPetCoolDownTime(SPetItem *m_pet)
{
	if (!m_pID_FRAME_SuAnimal )  return 0;
	if (m_pet != NULL && m_PetDeadTime.m_petIndex == m_pID_LIST_ShouLan->GetCurSelIndex())
	{
		if ((HQ_TimeGetTime() - m_PetDeadTime.m_StartTime)>m_PetDeadTime.m_DeadTime*1000)
		{
			m_PetDeadTime.m_DeadTime = 0;
			m_PetDeadTime.m_StartTime = 0;
			return 0;
		}
		return m_PetDeadTime.m_DeadTime*1000-(HQ_TimeGetTime()- m_PetDeadTime.m_StartTime);
	}
	else 
		return 0;
}

void CUI_ID_FRAME_SuAnimal::SetPetDeadTime(int m_PetIndex,int m_time)
{
	m_PetDeadTime.m_petIndex = m_PetIndex;
	m_PetDeadTime.m_StartTime = HQ_TimeGetTime();
	m_PetDeadTime.m_DeadTime = m_time;
	
	//当副将死亡的时候 我们弹出UI按钮
	//s_CUI_ID_FRAME_SuAnimalRecvie.InitUI();
	s_CUI_ID_FRAME_SuAnimalRecvie._SetVisable(true);
	//s_CUI_ID_FRAME_InfoTips.ADDSuAnimal();
}

const char* CUI_ID_FRAME_SuAnimal::GetPetXingeString(uint8 m_index)
{
	switch(m_index)
	{
	case 0:
		return theXmlString.GetString( eText_PetPoltroon );
	case 1:
		return theXmlString.GetString( eText_PetWariness );
	case 2:
		return theXmlString.GetString(eText_PetLoyal	);
	case 3:
		return theXmlString.GetString(eText_PetCanniness);
	case 4:
		return theXmlString.GetString(eText_PetBravery);
	default:
		return "";
	}
}

bool CUI_ID_FRAME_SuAnimal::ID_BUTTON_XSCH_OnButtonClick(ControlObject* pSender)
{
	if (!m_pID_FRAME_SuAnimal )  return 0;
	static bool m_isCheck = false;
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfPetTitle, m_isCheck);
	GameSetting::Instance()->CommitChanges();
	m_isCheck = !m_isCheck;
	return true;
}

void CUI_ID_FRAME_SuAnimal::SetPetProperty(bool is_exist)
{
	if (m_pID_FRAME_SuAnimal)
	{
		if (!is_exist)
		{
			m_pID_PICTURE_LeiBieFa->SetVisable(is_exist);
			m_pID_PICTURE_LeiBieWu->SetVisable(is_exist);
			m_pID_PICTURE_WXTu->SetVisable(is_exist);
			m_pID_PICTURE_WXHuo->SetVisable(is_exist);
			m_pID_PICTURE_WXMu->SetVisable(is_exist);
			m_pID_PICTURE_WXShui->SetVisable(is_exist);
			m_pID_PICTURE_WXJin->SetVisable(is_exist);
			m_pID_PICTURE_ZhongZu2->SetVisable(is_exist);
			m_pID_PICTURE_ZhongZu1->SetVisable(is_exist);
			m_pID_PICTURE_XBCi->SetVisable(is_exist);
			m_pID_PICTURE_XBXiong->SetVisable(is_exist);

			m_pID_TEXT_ZDL->SetText("");
			m_pID_TEXT_Level->SetText("");
			//m_pID_PROGRESS_Happy->SetValue(0);
			m_pID_PROGRESS_Life->SetValue(0);
			m_pID_PROGRESS_Hp->SetValue(0);
			m_pID_TEXT_XingGe->SetText("");
			m_pID_TEXT_Life->SetText("");
			//m_pID_TEXT_Happy->SetText("");
		}
		
	}
}

void CUI_ID_FRAME_SuAnimal::clearTemp()
{
	for ( int n =0;n < EBaseAttr_MaxSize; n++)
	{
		potentialAttributeTemp[n] = 0;
	}
	poten_sum = 0;
}

void CUI_ID_FRAME_SuAnimal::RefreshButtonGroup()
{
	if (!_IsVisable())
	{
		return;
	}
	if (m_CallIndex>=0)			//有召唤的副将
	{
		if (thePlayerRole.GetActivedPet())		//有出战的副将
		{
			m_pID_BUTTON_ChuZhan->SetVisable(false);
			m_pID_BUTTON_XiuXi->SetVisable(true);
			m_pID_BUTTON_ZhaoHuan->SetVisable(false);
			m_pID_BUTTON_ZhaoHui->SetVisable(false);
		}
		else					//有召唤的副将，但没出战的副将
		{
			m_pID_BUTTON_ChuZhan->SetVisable(true);
			m_pID_BUTTON_XiuXi->SetVisable(false);
			m_pID_BUTTON_ZhaoHuan->SetVisable(false);
			m_pID_BUTTON_ZhaoHui->SetVisable(true);
		}
	}
	else
	{
		m_pID_BUTTON_ChuZhan->SetVisable(true);
		m_pID_BUTTON_XiuXi->SetVisable(false);
		m_pID_BUTTON_ZhaoHuan->SetVisable(true);
		m_pID_BUTTON_ZhaoHui->SetVisable(false);
	}
}
void CUI_ID_FRAME_SuAnimal::UpdatePetSkillByMaxSkillSum()
{
	//根据当前的副将  设置技能的最大数量
	if(!IsVisable()) 
		return;
	if(!m_pID_LISTIMG_ZhuDong) 
		return;
	if(!m_pID_LIST_ShouLan) 
		return;
	if(!m_pID_LISTIMG_SkillXT || !m_pID_LISTIMG_SkillHT)
		return;
	if(m_pID_LIST_ShouLan->GetCurSelIndex() == -1) 
		return;
	SPetItem &mount = thePlayerRole.GetPetByIndex(m_pID_LIST_ShouLan->GetCurSelIndex());
	if(mount.GetPetID() == 0 || mount.GetPetID() == -1) 
		return;
	ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById(mount.GetPetID());
	if ( pPetMonster == NULL ) 
		return;
	int TFSkill = 0;
    if (pPetMonster->talentSkillId !=InvalidLogicNumber)
		TFSkill =1;
	int MaxSkillSum = thePetDefineConfig.GetLevelSkillSum(mount.baseInfo.level);
	//根据技能数量 设置技能的情况
	for(int i = MaxSkillSum;i<SPetItem::PetDefine_MaxSkillCount;++i)
	{
		ControlIconDrag::S_ListImg* pImg = m_pID_LISTIMG_ZhuDong->GetItemByIndex(i);
		if(!pImg) continue;
		//设置为锁
		pImg->SetEnable(eIcon_Lock);
	}
	for(int i = MaxSkillSum-1;i<SPetItem::PetDefine_MaxSkillCount;++i)
	{
		ControlIconDrag::S_ListImg* pImg = m_pID_LISTIMG_SkillHT->GetItemByIndex(i);
		if(!pImg) continue;
		pImg->SetEnable(eIcon_Lock);
	}
}
void CUI_ID_FRAME_SuAnimal::SetPetEquip(SCharItem* pItem,int EquipIndex)
{
	//设置装备到指定装备栏上面去
	//1.判断目标装备是否可以装备
	if(GetCurrentPet().baseInfo.petId == InvalidLogicNumber)
	{
		//未选择副将 不存在操作对象
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Non));
		return;
	}
	if(!thePlayerRole.GetActivedPet() || thePlayerRole.GetActivedPet()->baseInfo.guid != GetCurrentPet().baseInfo.guid)
	{
		//副将未出战
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Action));
		return;
	}
	if(!pItem)
	{
		//提示物品不存在
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Equip_Non));
		return;
	}
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
	if(!pItemCommon)
	{
		//提示物品不存在
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Equip_Non));
		return;
	}
	if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_PETEQUIP)
	{
		//物品类型错误
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Equip_TypeError));
		return;
	}
	ItemDefine::SItemPetEquip * pPetEquip = (ItemDefine::SItemPetEquip *)pItemCommon;
	if(pPetEquip->iEquipLevelReq > GetCurrentPet().baseInfo.level)
	{
		//等级不够
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Equip_Level));
		return;
	}
	//判断装备的时间
	if(pItem->IsOverdue())
	{
		//装备已经过期 无法装备
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Equip_TimeEnd));
		return;
	}
	if(EquipIndex != -1 && EquipIndex != pPetEquip->iPos)
	{
		//位置不正确
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Equip_Pos));
		return;
	}
	//判断目标栏位是否存在装备
	//if(GetCurrentPet().baseInfo.PetEquip[pPetEquip->iPos].itembaseinfo.ustItemID != 0
	//	&& GetCurrentPet().baseInfo.PetEquip[pPetEquip->iPos].itembaseinfo.ustItemID != InvalidLogicNumber
	//	)
	//{
	//	//副将指定栏位以有装备 我们判断背包空间
	//	int BagType = thePlayerRole.GetBagTypeByItemType(pItemCommon->ucItemType);
	//	//获取到物品的背包类型
	//	int BagNonSum = 0;
	//	switch(BagType)
	//	{
	//	case BT_NormalItemBag:
	//		BagNonSum = thePlayerRole.m_bag.GetNullItemCount();
	//		break;
	//	case BT_MaterialBag:
	//		BagNonSum = thePlayerRole.m_bagMaterial.GetNullItemCount();
	//		break;
	//	case BT_TaskBag:
	//		BagNonSum = thePlayerRole.m_bagTask.GetNullItemCount();
	//		break;
	//	}
	//	if(BagNonSum == 0)
	//	{
	//		//提示 背包已满 无法下装备
	//		return;
	//	}
	//}
	//到目前为止 我们过滤了客户端可以过滤的信息 发送穿装备的命令到服务器端去
	MsgAddPetEquip msg;
	msg.PetGuID = GetCurrentPet().baseInfo.guid;
	msg.ItemOnlyID = pItem->itembaseinfo.nOnlyInt;
	GettheNetworkInput().SendMsg(&msg);
}
void CUI_ID_FRAME_SuAnimal::RemovePetEquip(SCharItem* pItem,int BagIndex)
{
	if(GetCurrentPet().baseInfo.petId == InvalidLogicNumber)
	{
		//未选择副将 不存在操作对象
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Non));
		return;
	}
	if(!thePlayerRole.GetActivedPet() || thePlayerRole.GetActivedPet()->baseInfo.guid != GetCurrentPet().baseInfo.guid)
	{
		//副将未出战
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Action));
		return;
	}
	if(!pItem)
	{
		//提示物品不存在
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Equip_Non));
		return;
	}
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
	if(!pItemCommon)
	{
		//提示物品不存在
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Equip_Non));
		return;
	}
	if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_PETEQUIP)
	{
		//物品类型错误
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Equip_TypeError));
		return;
	}
	//从副将身上将装备脱下来 只涉及到纯粹的拖下装备 不涉及穿装备的情况
	int BagType = thePlayerRole.GetBagTypeByItemType(pItemCommon->ucItemType);
	if(BagIndex == -1)
	{
		int BagNonSum = 0;
		switch(BagType)
		{
		case BT_NormalItemBag:
			BagNonSum = thePlayerRole.m_bag.GetNullItemCount();
			break;
		case BT_MaterialBag:
			BagNonSum = thePlayerRole.m_bagMaterial.GetNullItemCount();
			break;
		case BT_TaskBag:
			BagNonSum = thePlayerRole.m_bagTask.GetNullItemCount();
			break;
		}
		if(BagNonSum == 0)
		{
			//提示背包已经满了无法拖下装备
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Pet_Equip_BagFull));
			return;
		}
	}
	else
	{
		//判断背包指定位置是否是空的 不是空的 不可以拖下装备 IsHaveItem
		bool IsHaveItem = false;
		switch(BagType)
		{
		case BT_NormalItemBag:
			IsHaveItem = thePlayerRole.m_bag.IsHaveItem(BagIndex);
			break;
		case BT_MaterialBag:
			IsHaveItem = thePlayerRole.m_bagMaterial.IsHaveItem(BagIndex);
			break;
		case BT_TaskBag:
			IsHaveItem = thePlayerRole.m_bagTask.IsHaveItem(BagIndex);
			break;
		}
		if(IsHaveItem)
			return;
	}
	//判断完毕 我们可以发生命令道服务器端了
	MsgRemovePetEquip msg;
	msg.PetGuID = GetCurrentPet().baseInfo.guid;
	msg.BagIndex = BagIndex;
	msg.PetEquipOnlyID = pItem->itembaseinfo.nOnlyInt;
	GettheNetworkInput().SendMsg(&msg);
}
void CUI_ID_FRAME_SuAnimal::UpdatePetEquipByNowSelect()
{
	//更新当前副将的装备栏
	if(GetCurrentPet().baseInfo.petId == InvalidLogicNumber)
		return;
	m_pID_LISTIMG_PetEquip->Clear();//先清空装备栏

	m_pID_LISTIMG_PetEquip1->Clear();
	m_pID_LISTIMG_PetEquip2->Clear();
	m_pID_LISTIMG_PetEquip3->Clear();
	m_pID_LISTIMG_PetEquip4->Clear();
	m_pID_LISTIMG_PetEquip5->Clear();
	//遍历副将的装备 我们将其设置好
	for(int i =0;i<SPetItem::PetEquip_MaxSum;++i)
	{
		SCharItem& pEquip = GetCurrentPet().baseInfo.PetEquip[i];
		if(pEquip.itembaseinfo.ustItemID ==0 || pEquip.itembaseinfo.ustItemID == InvalidLogicNumber)
			continue;
		//将装备设置上去
		ControlIconDrag::S_ListImg pItems;
		pItems.SetData(&pEquip);
		m_pID_LISTIMG_PetEquip->SetItem(&pItems,i);	

		m_pPetEquip[i]->SetItem(&pItems,0);	
	}
	if(!thePlayerRole.GetActivedPet() || thePlayerRole.GetActivedPet()->baseInfo.guid != GetCurrentPet().baseInfo.guid)
		m_pID_LISTIMG_PetEquip->SetEnable(false);
	else
		m_pID_LISTIMG_PetEquip->SetEnable(true);
}


bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	//将指定物品设置到副将装备栏上去 我们需要进行基本的过滤
	SCharItem * pItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	int Index = m_pID_LISTIMG_PetEquip->GetItemIndex(pItemSrc);
	SetPetEquip(pItem,Index);
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	if(!pItem)
		return false;
	//设置副将拖下装备
	SCharItem * pEquip = (SCharItem*)pItem->m_pkIconInfo->GetData();
	RemovePetEquip(pEquip);//将副将的装备脱下放入背包
	return true;
}

bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	//将指定物品设置到副将装备栏上去 我们需要进行基本的过滤
	SCharItem * pItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	int Index = 0;
	SetPetEquip(pItem,Index);
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;

	if (!pItem)
	    return false;

	//设置副将拖下装备
	SCharItem * pEquip = (SCharItem*)pItem->m_pkIconInfo->GetData();
	RemovePetEquip(pEquip);//将副将的装备脱下放入背包
	return true;
}

bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	//将指定物品设置到副将装备栏上去 我们需要进行基本的过滤
	SCharItem * pItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	int Index = 1;
	SetPetEquip(pItem,Index);
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	//设置副将拖下装备
	if (!pItem)
	    return false;
	
	SCharItem * pEquip = (SCharItem*)pItem->m_pkIconInfo->GetData();
	RemovePetEquip(pEquip);//将副将的装备脱下放入背包
	return true;
}

bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	//将指定物品设置到副将装备栏上去 我们需要进行基本的过滤
	SCharItem * pItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	int Index = 2;
	SetPetEquip(pItem,Index);
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	if (!pItem)
	    return false;
	//设置副将拖下装备
	SCharItem * pEquip = (SCharItem*)pItem->m_pkIconInfo->GetData();
	RemovePetEquip(pEquip);//将副将的装备脱下放入背包
	return true;
}

bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	//将指定物品设置到副将装备栏上去 我们需要进行基本的过滤
	SCharItem * pItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	int Index = 3;
	SetPetEquip(pItem,Index);
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	if (!pItem)
		return false;
	
	//设置副将拖下装备
	SCharItem * pEquip = (SCharItem*)pItem->m_pkIconInfo->GetData();
	RemovePetEquip(pEquip);//将副将的装备脱下放入背包
	return true;
}

bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip5OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	//将指定物品设置到副将装备栏上去 我们需要进行基本的过滤
	SCharItem * pItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
	int Index = 4;
	SetPetEquip(pItem,Index);
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_PetEquip5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	if (!pItem)
	    return false;
	//设置副将拖下装备
	SCharItem * pEquip = (SCharItem*)pItem->m_pkIconInfo->GetData();
	RemovePetEquip(pEquip);//将副将的装备脱下放入背包
	return true;
}

bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_SkillXTOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_SkillXTOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_SkillXTOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_SkillXTOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}

bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_SkillHTOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_SkillHTOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_SkillHTOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::ID_LISTIMG_SkillHTOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SuAnimal )
		return false;
	return true;
}
bool CUI_ID_FRAME_SuAnimal::IsNowPetEquip(ControlListImage* pDlgDrag) 
{
	if(pDlgDrag == m_pID_LISTIMG_PetEquip ||
		pDlgDrag == m_pID_LISTIMG_PetEquip1 ||
		pDlgDrag == m_pID_LISTIMG_PetEquip2 ||
		pDlgDrag == m_pID_LISTIMG_PetEquip3 ||
		pDlgDrag == m_pID_LISTIMG_PetEquip4 ||
		pDlgDrag == m_pID_LISTIMG_PetEquip5
		)
		return true;
	else
		return false;
}