/********************************************************************
Created by UIEditor.exe
FileName: D:\Tj\Client\UI\AllNpcList.cpp
*********************************************************************/
#include "MeTerrain/stdafx.h"
#include <assert.h>
#include "MeUi/UiManager.h"
#include "AllNpcList.h"
#include "FuncPerformanceLog.h"
// #include "../map_configure.h"
#include "../color_config.h"
#include "create.h"
#include <map>
#include "UIBase.h"
#include"MiniMap.h"
#include "GameMain.h"
#include "../Player.h"
#include "PlayerMgr.h"
#include "WorldMap.h"
#include "MeUi/ExpressionManager.h"
#include "XmlStringLanguage.h"
#include "Dxsdk/dinput.h"
#include "CommonChatFrame.h"
#include "RegionMap.h"
#include "ui/MiniMapUI.h"
#include "MessageBox.h"
#include "Common.h"
#include "NpcInfo.h"
#include "Task.h"
#include "CountryDefine.h"
#include "CountryFunction.h"
#include "Cfg.h"
#include "ScreenInfoManager.h"
#include "MeUi/UiRender.h"
#include "Pet.h"
#include "../GameUI/FindTheRoad.h"
#include "../GameUI/SelectChannel.h"

extern HWND g_hWnd;
extern short GetKeyboardInput(int iKey);
int  g_nsrcPixelEdgeLength  = (1024);

#define srcPixelChangeStepLength (100)

CUI_ID_FRAME_AllNpcList s_CUI_ID_FRAME_AllNpcList;
MAP_FRAME_RUN( s_CUI_ID_FRAME_AllNpcList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AllNpcList, OnFrameRender )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AllNpcList, PostFrameRender )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AllNpcList, OnFrameRenderNeedRedraw )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_CloseOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_LIST_NpcNameOnListSelectChange )
MAP_LIST_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_LIST_NpcNameOnListDBClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_DirectOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_quxiaozhiyinOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_COMBOBOX_MaplistOnComboBoxChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_NpcOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_MonsterOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_WorldMapOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_helpOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_ShopOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_MaterialOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_StorageOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_StarOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_GuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_SkillOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_TransportOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_SpecialPlaceOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_SpecialItemOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_ActivityOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_OtherNpcOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_Monster1OnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_TopOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_ButtonOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_BigOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_SmallOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_EDIT_SearchOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_StoryMapOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_LIST_NpcFunctionOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_ShowFunctionNPCOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_ShowTaskNPCOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_ShowMonsterOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_ShowMapLinkOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_CHECKBOX_ShowTransportOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_SearchOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_EDIT_InputXOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_EDIT_InputYOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AllNpcList, ID_BUTTON_GoOnButtonClick )
CUI_ID_FRAME_AllNpcList::CUI_ID_FRAME_AllNpcList()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_AllNpcList = NULL;
	//m_pID_PICTURE_12378 = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_PICTURE_BG = NULL;
	m_pID_LIST_NpcName = NULL;
	//m_pID_BUTTON_Direct = NULL;
	m_pID_PICTURE_WorldMap = NULL;
// 	m_pID_BUTTON_quxiaozhiyin = NULL;
// 	m_pID_TEXT_PuTong = NULL;
// 	m_pID_TEXT_MaiMai = NULL;
// 	m_pID_TEXT_CaiLiao = NULL;
// 	m_pID_TEXT_CangKu = NULL;
// 	m_pID_TEXT_HeChen = NULL;
// 	m_pID_TEXT_JiaoTong = NULL;
	m_pID_BUTTON_WorldMap = NULL;
	//m_pID_CHECKBOX_Npc = NULL;
// 	m_pID_CHECKBOX_Monster = NULL;
// 	m_pID_TEXT_22486 = NULL;
// 	m_pID_EDIT_Search = NULL;
	m_pID_TEXT_Search = NULL;
	m_pID_BUTTON_Search = NULL;
	m_pID_TEXT_Product = NULL;
	m_pID_BUTTON_Close = NULL;
// 	m_pID_BUTTON_help = NULL;
// 	m_pID_PICTURE_12180 = NULL;
// 	m_pID_CHECKBOX_Shop = NULL;
// 	m_pID_CHECKBOX_Material = NULL;
// 	m_pID_CHECKBOX_Storage = NULL;
// 	m_pID_CHECKBOX_Star = NULL;
// 	m_pID_CHECKBOX_Guild = NULL;
// 	m_pID_CHECKBOX_Skill = NULL;
// 	m_pID_CHECKBOX_Transport = NULL;
// 	m_pID_CHECKBOX_SpecialPlace = NULL;
// 	m_pID_CHECKBOX_SpecialItem = NULL;
// 	m_pID_CHECKBOX_Activity = NULL;
	m_pID_TEXT_30 = NULL;
	m_pID_COMBOBOX_Maplist = NULL;
	m_mapIndex = -1;
	m_selectedPosX = -1.f;
	m_selectedPosY = -1.f;
	m_bIsNpcInList = true;
	m_pID_BUTTON_Top = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Down = NULL;
	m_pID_BUTTON_Big = NULL;
	m_pID_BUTTON_Small = NULL;
	m_pID_TEXT_MousePos = NULL;
// 	m_pID_TEXT_Explain = NULL;
// 	m_pID_PICTURE_BgLine = NULL;
	m_pID_BUTTON_StoryMap = NULL;
	m_pID_TEXT_NPCText = NULL;
	m_pID_LIST_NpcName = NULL;
	m_pID_LIST_NpcFunction = NULL;
	m_pID_TEXT_SelectSceneText = NULL;
	m_pID_CHECKBOX_ShowFunctionNPC = NULL;
	m_pID_CHECKBOX_ShowTaskNPC = NULL;
	m_pID_CHECKBOX_ShowMonster = NULL;
	m_pID_CHECKBOX_ShowMapLink = NULL;
	m_pID_CHECKBOX_ShowTransport = NULL;
	m_pID_TEXT_FunctionNPCText = NULL;
	m_pID_TEXT_TaskNPCText = NULL;
	m_pID_TEXT_MonsterText = NULL;
	m_pID_TEXT_MapLinkText = NULL;
	m_pID_TEXT_TransportText = NULL;
	m_pID_COMBOBOX_Maplist = NULL;
	m_pID_EDIT_InputX = NULL;
	m_pID_EDIT_InputY = NULL;
	m_pID_BUTTON_Go = NULL;
	m_maxDimension = 1024;
	m_xPixelOffset = 0;
	m_yPixelOffset = 0;
	m_ShowType	= 0xFFFF;
	m_bTipActive = false;
	mCurMapID = 0;

	m_selectedPosMap = -1;
	RECT tmp = {0,0,g_nsrcPixelEdgeLength,g_nsrcPixelEdgeLength}; 
	m_rcSrc = tmp;
	m_rcDes = tmp;

	cShowType = eShowAllMap;
	m_bMoveMap = false;
	m_bDragMap = false;
	m_BGTextureId = -1;
	unguard;
}
// Frame
bool CUI_ID_FRAME_AllNpcList::OnFrameRun()
{
	guardfunc;
	if (!IsVisable())
	{
		return false;
	}
	if (!IsWorldMapActivity())
	{
		m_bDragMap =  false;
		m_bMoveMap = false;
	}
	{
		m_pID_FRAME_AllNpcList->SetRedraw();
	}
	float posx = 0,posy = 0;
	if (GetRealPosition(posx, posy))
	{
		{
			char temp[1024] = {0};
			MeSprintf_s(temp, sizeof(temp)-1, theXmlString.GetString(eClient_RegionMap_MousePosition),(int)posx,(int)posy);
			m_pID_TEXT_MousePos->SetText(temp);
		}
	}
	if (m_bMoveMap)
	{
		int nDelta = srcPixelChangeStepLength* theHeroGame.GetFrameElapsedTime();
		if (nDelta < 2)
		{
			nDelta = 2;
		}
		if ( m_pID_BUTTON_Right->IsEnable() && m_pID_BUTTON_Right->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			m_rcSrc.left += nDelta;
			m_rcSrc.right += nDelta;
		}
		else if (m_pID_BUTTON_Left->IsEnable() && m_pID_BUTTON_Left->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			m_rcSrc.left -= nDelta;
			m_rcSrc.right -= nDelta;
		}
		else if (m_pID_BUTTON_Top->IsEnable() && m_pID_BUTTON_Top->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			m_rcSrc.top -= nDelta;
			m_rcSrc.bottom -= nDelta;
		}
		else if (m_pID_BUTTON_Down->IsEnable() && m_pID_BUTTON_Down->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			m_rcSrc.top += nDelta;
			m_rcSrc.bottom += nDelta;
		}
		else
		{
			m_bMoveMap = false;
		}
	}
	if (m_bDragMap)
	{
		// 	if (theUiManager.GetFocus() != m_pID_PICTURE_WorldMap)
		// 	{
		// 		m_bDragMap = false;
		// 	}
		int nDeltaX = theUiManager.m_ptMoust.x - m_lastPoint.x;
		int nDeltaY = theUiManager.m_ptMoust.y - m_lastPoint.y;
		if (nDeltaX != 0 )
		{
			m_rcSrc.left -= nDeltaX;
			m_rcSrc.right -= nDeltaX;
			m_lastPoint.x = theUiManager.m_ptMoust.x;
		}
		if (nDeltaY != 0)
		{
			m_rcSrc.top -= nDeltaY;
			m_rcSrc.bottom -= nDeltaY;
			m_lastPoint.y = theUiManager.m_ptMoust.y;
		}
	}
	if (m_rcSrc.right > g_nsrcPixelEdgeLength)
	{
		m_rcSrc.left -= (m_rcSrc.right - g_nsrcPixelEdgeLength);
		m_rcSrc.right = g_nsrcPixelEdgeLength;
	}
	if (m_rcSrc.left < 0)
	{
		m_rcSrc.right -= m_rcSrc.left;
		m_rcSrc.left = 0;
	}
	if (m_rcSrc.top < 0)
	{
		m_rcSrc.bottom -= m_rcSrc.top;
		m_rcSrc.top = 0;
	}
	if (m_rcSrc.bottom > g_nsrcPixelEdgeLength)
	{
		m_rcSrc.top -= (m_rcSrc.bottom - g_nsrcPixelEdgeLength);
		m_rcSrc.bottom = g_nsrcPixelEdgeLength;
	}
	if (m_bMoveMap || m_bDragMap)
	{
		RefreshButtonStatus();
	}
	int nStartIndex = m_pID_LIST_NpcName->GetShowStartHeight();
	m_pID_LIST_NpcFunction->SetShowStartHeight(nStartIndex);

	return true;
	unguard;
}

extern BOOL g_bRenderUI;
bool CUI_ID_FRAME_AllNpcList::OnFrameRenderNeedRedraw()
{
	guardfunc;

	if( !g_bRenderUI )
		return false;
	int mapId = GetCurrMapId();
	if (mapId == -1 )
	{
		return false;
	}

	CalDrawParameter(false);
	m_PixelPerRealDis = (m_rcDes.right - m_rcDes.left)* g_nsrcPixelEdgeLength
		/((float)m_maxDimension*(m_rcSrc.right - m_rcSrc.left));
 	if (m_BGTextureId != -1)
	{
		RECT bgRect;
		m_pID_PICTURE_BG->GetRealRect(&bgRect);
		theControlPictureManager.BitBlt(&m_BGTextureId,NULL,&bgRect,&gCfg.m_BgSrc,0xffffffff,0,eZWriteDisable);
	}
	RECT rcWorkingArea;
	m_pID_PICTURE_WorldMap->GetRealRect(&rcWorkingArea);
	m_pID_FRAME_AllNpcList->GetFrameRender()->PushWorkingArea(rcWorkingArea);
	if (mapId == m_selectedPosMap)
	{
		GetRegionMap()->RenderRegionMap(m_rcDes,m_rcSrc,mapId,m_selectedPosX,m_selectedPosY,m_PixelPerRealDis,m_xPixelOffset,m_yPixelOffset	);
	}
	else
	{
		GetRegionMap()->RenderRegionMap(m_rcDes,m_rcSrc,mapId,-1,-1,m_PixelPerRealDis,m_xPixelOffset,m_yPixelOffset	);
	}
	m_pID_FRAME_AllNpcList->GetFrameRender()->PopWorkingArea();
	m_bTipActive = false;
	return true;
	unguard;
}
// 	// CheckBox
// 	void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_GuaiWuOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// 	{
// 		if (*pbChecked)
// 		{
// 			m_ShowType |= Monster;
// 		}
// 		else
// 		{
// 			m_ShowType &= (~Monster);
// 		}
// 	}
// 	// CheckBox
// 	void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_WuqiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// 	{
// 		if (*pbChecked)
// 		{
// 			m_ShowType |= Npc_Weapon;
// 		}
// 		else
// 		{
// 			m_ShowType &= (~Npc_Weapon);
// 		}
// 	}
// 	// CheckBox
// 	void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_CaiLiaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// 	{
// 		if (*pbChecked)
// 		{
// 			m_ShowType |= Npc_Material;
// 		}
// 		else
// 		{
// 			m_ShowType &= (~Npc_Material);
// 		}
// 	}
// 	// CheckBox
// 	void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_CangKuOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// 	{
// 		if (*pbChecked)
// 		{
// 			m_ShowType |= Npc_Storage;
// 		}
// 		else
// 		{
// 			m_ShowType &= (~Npc_Storage);
// 		}
// 	}
// 	// CheckBox
// 	void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_ShenChanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// 	{
// 		if (*pbChecked)
// 		{
// 			m_ShowType |= Npc_Enhance;
// 		}
// 		else
// 		{
// 			m_ShowType &= (~Npc_Enhance);
// 		}
// 	}
// 	// CheckBox
// 	void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_YiZhanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// 	{
// 		if (*pbChecked)
// 		{
// 			m_ShowType |= Npc_Transpot;
// 		}
// 		else
// 		{
// 			m_ShowType &= (~Npc_Transpot);
// 		}
// 	}
// 	void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_QiTaOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// 	{
// 
// 		if (*pbChecked)
// 		{
// 			m_ShowType |= Npc_Other;
// 		}
// 		else
// 		{
// 			m_ShowType &= (~Npc_Other);
// 		}
// 	}
// Button
bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_AllNpcList )
		return false;
	SetVisable( false );
	return true;
	unguard;
}
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_ShopOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_Shop;
	}
	else
	{
		m_ShowType &= (~Npc_Shop);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}
// CheckBox
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_MaterialOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_Material;
	}
	else
	{
		m_ShowType &= (~Npc_Material);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}
// CheckBox
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_StorageOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_Storage;
	}
	else
	{
		m_ShowType &= (~Npc_Storage);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}
// CheckBox
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_StarOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_Star;
	}
	else
	{
		m_ShowType &= (~Npc_Star);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}
// CheckBox
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_Gang;
	}
	else
	{
		m_ShowType &= (~Npc_Gang);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}
// CheckBox
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_SkillOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_Skill;
	}
	else
	{
		m_ShowType &= (~Npc_Skill);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}
// CheckBox
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_TransportOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_TranspotNpc;
	}
	else
	{
		m_ShowType &= (~Npc_TranspotNpc);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}
// CheckBox
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_SpecialPlaceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_SpecialPlace;
	}
	else
	{
		m_ShowType &= (~Npc_SpecialPlace);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}
// CheckBox
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_SpecialItemOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_SpecialItem;
	}
	else
	{
		m_ShowType &= (~Npc_SpecialItem);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}
// CheckBox
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_ActivityOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_Activity;
	}
	else
	{
		m_ShowType &= (~Npc_Activity);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_OtherNpcOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_OtherNpc;
	}
	else
	{
		m_ShowType &= (~Npc_OtherNpc);
	}
	GetRegionMap()->SetUpdateStableImage(true);

}

void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_Monster1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return ;
	}

	if (*pbChecked)
	{
		m_ShowType |= Npc_Monster;
	}
	else
	{
		m_ShowType &= (~Npc_Monster);
	}
	GetRegionMap()->SetUpdateStableImage(true);
}

// Button
bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_DirectOnButtonClick( ControlObject* pSender )
{
	guardfunc;

	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return false;
	}

	ControlList::S_List* stItem = m_pID_LIST_NpcName->GetCurSelItem();
	if( stItem )
	{
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(stItem->m_nID);
		if (!pInfo)
		{
			return false;
		}
// 		SetSelectedName(pInfo->_szName.c_str());
		NpcCoord::getInstance()->clickHyberToMiniMap(m_seletedName.c_str(),GetCurrMapId());

		m_selectedPosX = -1.f;
		m_selectedPosY = -1.f;
		GetAdvancedMiniMap()->SetTargetNpc(m_seletedName.c_str());
	}
	return true;
	unguard;
}
bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_quxiaozhiyinOnButtonClick(ControlObject*pSender)
{
	guardfunc;

	if(!m_pID_FRAME_AllNpcList)
	{
		assert(false&&"ui error");
		return false;
	}

	 GetAdvancedMiniMap()->CancelNPCPF();
	
return false;
	unguard;
}
// Edit
void CUI_ID_FRAME_AllNpcList::ID_EDIT_InputXOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_AllNpcList )
		return;
}
// Edit
void CUI_ID_FRAME_AllNpcList::ID_EDIT_InputYOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_AllNpcList )
		return;
}
// Button
bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_GoOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AllNpcList )
		return false;
	int nMapId = GetCurrMapId();
	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapId); 
	if (pTile == NULL)
	{
		return false;
	}
	
	const char*pCharX = m_pID_EDIT_InputX->GetText();
	if (pCharX[0] == '\0')
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_MapError, theXmlString.GetString(eText_PlsInputRightXY) );
		return false;
	}
	int posx = atoi(pCharX);
	const char*pCharY = m_pID_EDIT_InputY->GetText();
	if (pCharY[0] == '\0')
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_MapError, theXmlString.GetString(eText_PlsInputRightXY) );
		return false;
	}
	int posy = atoi(pCharY);
	MoveToXY(posx,posy,nMapId);

	return true;
}

// 装载UI
bool CUI_ID_FRAME_AllNpcList::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\AllNpcList.meui", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\AllNpcList.UI]失败")
			return false;
	}
// 	else if ( dwResult != 0/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[UI\\AllNpcList.UI]与源代码版本不一样")
// 	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_AllNpcList::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_AllNpcList, s_CUI_ID_FRAME_AllNpcListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_AllNpcList, s_CUI_ID_FRAME_AllNpcListOnFrameRender ,true);
    theUiManager.OnFrameRender( ID_FRAME_AllNpcList, s_CUI_ID_FRAME_AllNpcListPostFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_Close, s_CUI_ID_FRAME_AllNpcListID_BUTTON_CloseOnButtonClick );
	theUiManager.OnListLDBClick( ID_FRAME_AllNpcList, ID_LIST_NpcName, s_CUI_ID_FRAME_AllNpcListID_LIST_NpcNameOnListDBClick  );
	theUiManager.OnListSelectChange( ID_FRAME_AllNpcList, ID_LIST_NpcName,  s_CUI_ID_FRAME_AllNpcListID_LIST_NpcNameOnListSelectChange);
	theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_Direct, s_CUI_ID_FRAME_AllNpcListID_BUTTON_DirectOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_quxiaozhiyin, s_CUI_ID_FRAME_AllNpcListID_BUTTON_quxiaozhiyinOnButtonClick );
theUiManager.OnComboBoxChange( ID_FRAME_AllNpcList, ID_COMBOBOX_Maplist, s_CUI_ID_FRAME_AllNpcListID_COMBOBOX_MaplistOnComboBoxChange );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Npc, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_NpcOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Monster, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_MonsterOnCheckBoxCheck );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_WorldMap, s_CUI_ID_FRAME_AllNpcListID_BUTTON_WorldMapOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_help, s_CUI_ID_FRAME_AllNpcListID_BUTTON_helpOnButtonClick );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Shop, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_ShopOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Material, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_MaterialOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Storage, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_StorageOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Star, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_StarOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Guild, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_GuildOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Skill, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_SkillOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Transport, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_TransportOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_SpecialPlace, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_SpecialPlaceOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_SpecialItem, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_SpecialItemOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Activity, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_ActivityOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_OtherNpc, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_OtherNpcOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_Monster1, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_Monster1OnCheckBoxCheck );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_Top, s_CUI_ID_FRAME_AllNpcListID_BUTTON_TopOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_Left, s_CUI_ID_FRAME_AllNpcListID_BUTTON_LeftOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_Right, s_CUI_ID_FRAME_AllNpcListID_BUTTON_RightOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_Button, s_CUI_ID_FRAME_AllNpcListID_BUTTON_ButtonOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_Big, s_CUI_ID_FRAME_AllNpcListID_BUTTON_BigOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_Small, s_CUI_ID_FRAME_AllNpcListID_BUTTON_SmallOnButtonClick );
theUiManager.OnEditEnter( ID_FRAME_AllNpcList, ID_EDIT_Search, s_CUI_ID_FRAME_AllNpcListID_EDIT_SearchOnEditEnter );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_StoryMap, s_CUI_ID_FRAME_AllNpcListID_BUTTON_StoryMapOnButtonClick );
theUiManager.OnListSelectChange( ID_FRAME_AllNpcList, ID_LIST_NpcName, s_CUI_ID_FRAME_AllNpcListID_LIST_NpcNameOnListSelectChange );
theUiManager.OnListSelectChange( ID_FRAME_AllNpcList, ID_LIST_NpcFunction, s_CUI_ID_FRAME_AllNpcListID_LIST_NpcFunctionOnListSelectChange );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_ShowFunctionNPC, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_ShowFunctionNPCOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_ShowTaskNPC, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_ShowTaskNPCOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_ShowMonster, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_ShowMonsterOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_ShowMapLink, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_ShowMapLinkOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_AllNpcList, ID_CHECKBOX_ShowTransport, s_CUI_ID_FRAME_AllNpcListID_CHECKBOX_ShowTransportOnCheckBoxCheck );
theUiManager.OnComboBoxChange( ID_FRAME_AllNpcList, ID_COMBOBOX_Maplist, s_CUI_ID_FRAME_AllNpcListID_COMBOBOX_MaplistOnComboBoxChange );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_Search, s_CUI_ID_FRAME_AllNpcListID_BUTTON_SearchOnButtonClick );
theUiManager.OnEditEnter( ID_FRAME_AllNpcList, ID_EDIT_InputX, s_CUI_ID_FRAME_AllNpcListID_EDIT_InputXOnEditEnter );
theUiManager.OnEditEnter( ID_FRAME_AllNpcList, ID_EDIT_InputY, s_CUI_ID_FRAME_AllNpcListID_EDIT_InputYOnEditEnter );
theUiManager.OnButtonClick( ID_FRAME_AllNpcList, ID_BUTTON_Go, s_CUI_ID_FRAME_AllNpcListID_BUTTON_GoOnButtonClick );

	m_pID_FRAME_AllNpcList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_AllNpcList );
// 	CUILayout::GetInstance()->AddFrame( m_pID_FRAME_AllNpcList );
	//m_pID_PICTURE_12378 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_PICTURE_12378 );
		m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_Close );
		m_pID_PICTURE_BG = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_PICTURE_BG );
		m_pID_LIST_NpcName = (ControlList*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_LIST_NpcName );
		//m_pID_BUTTON_Direct = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_Direct );
		m_pID_PICTURE_WorldMap = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_PICTURE_WorldMap );
// 		m_pID_BUTTON_quxiaozhiyin = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_quxiaozhiyin );
// 		m_pID_TEXT_PuTong = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_PuTong );
// 		m_pID_TEXT_MaiMai = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_MaiMai );
// 		m_pID_TEXT_CaiLiao = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_CaiLiao );
// 		m_pID_TEXT_CangKu = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_CangKu );
// 		m_pID_TEXT_HeChen = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_HeChen );
// 		m_pID_TEXT_JiaoTong = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_JiaoTong );
		m_pID_COMBOBOX_Maplist = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_COMBOBOX_Maplist );
// 		m_pID_CHECKBOX_Npc = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Npc );
// 		m_pID_CHECKBOX_Monster = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Monster );
		m_pID_BUTTON_WorldMap = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_WorldMap );
		//m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_help );
// 		m_pID_EDIT_Search = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_EDIT_Search );
		m_pID_TEXT_Search = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_Search );
		m_pID_BUTTON_Search = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_Search );
		m_pID_TEXT_Product = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_Product );
		//m_pID_PICTURE_12180 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_PICTURE_12180 );
		m_pID_TEXT_30 = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_30 );
// 		m_pID_CHECKBOX_Shop = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Shop );
// 		m_pID_CHECKBOX_Material = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Material );
// 		m_pID_CHECKBOX_Storage = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Storage );
// 		m_pID_CHECKBOX_Star = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Star );
// 		m_pID_CHECKBOX_Guild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Guild );
// 		m_pID_CHECKBOX_Skill = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Skill );
// 		m_pID_CHECKBOX_Transport = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Transport );
// 		m_pID_CHECKBOX_SpecialPlace = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_SpecialPlace );
// 		m_pID_CHECKBOX_SpecialItem = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_SpecialItem );
// 		m_pID_CHECKBOX_Activity = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Activity );
// 		m_pID_CHECKBOX_OtherNpc = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_OtherNpc );
// 		m_pID_TEXT_OtherNpc = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_OtherNpc );
// 		m_pID_CHECKBOX_Monster1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_Monster1 );
// 		m_pID_TEXT_Monster = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_Monster );
// 		m_pID_PICTURE_OtherNpc = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_PICTURE_OtherNpc );
// 		m_pID_PICTURE_Monster = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_PICTURE_Monster );
		m_pID_BUTTON_Top = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_Top );
		m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_Left );
		m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_Right );
		m_pID_BUTTON_Down = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_Button );
		m_pID_BUTTON_Big = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_Big );
		m_pID_BUTTON_Small = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_Small );
		m_pID_TEXT_MousePos = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_MousePos );
		m_pID_BUTTON_StoryMap = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_StoryMap );
		m_pID_LIST_NpcName = (ControlList*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_LIST_NpcName );
		m_pID_LIST_NpcFunction = (ControlList*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_LIST_NpcFunction );
		m_pID_TEXT_SelectSceneText = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_SelectSceneText );
		m_pID_CHECKBOX_ShowFunctionNPC = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_ShowFunctionNPC );
		m_pID_CHECKBOX_ShowTaskNPC = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_ShowTaskNPC );
		m_pID_CHECKBOX_ShowMonster = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_ShowMonster );
		m_pID_CHECKBOX_ShowMapLink = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_ShowMapLink );
		m_pID_CHECKBOX_ShowTransport = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_CHECKBOX_ShowTransport );
		m_pID_TEXT_FunctionNPCText = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_FunctionNPCText );
		m_pID_TEXT_TaskNPCText = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_TaskNPCText );
		m_pID_TEXT_MonsterText = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_MonsterText );
		m_pID_TEXT_MapLinkText = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_MapLinkText );
		m_pID_TEXT_TransportText = (ControlText*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_TEXT_TransportText );
		m_pID_COMBOBOX_Maplist = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_COMBOBOX_Maplist );
		m_pID_PICTURE_BG = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_PICTURE_BG );
		m_pID_EDIT_InputX = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_EDIT_InputX );
		m_pID_EDIT_InputY = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_EDIT_InputY );
		m_pID_BUTTON_Go = (ControlButton*)theUiManager.FindControl( ID_FRAME_AllNpcList, ID_BUTTON_Go );
// 		assert( m_pID_FRAME_AllNpcList );
// 		assert( m_pID_PICTURE_12378 );
// 		assert( m_pID_BUTTON_Close );
// 		assert( m_pID_PICTURE_BG );
// 		assert( m_pID_LIST_NpcName );
// 		assert( m_pID_BUTTON_Direct );
// 		assert( m_pID_PICTURE_WorldMap );
// 		assert( m_pID_BUTTON_quxiaozhiyin );
// 		assert( m_pID_TEXT_PuTong );
// 		assert( m_pID_TEXT_MaiMai );
// 		assert( m_pID_TEXT_CaiLiao );
// 		assert( m_pID_TEXT_CangKu );
// 		assert( m_pID_TEXT_HeChen );
// 		assert( m_pID_TEXT_JiaoTong );
// 		assert( m_pID_COMBOBOX_Maplist );
// 		assert( m_pID_CHECKBOX_Npc );
// 		assert( m_pID_CHECKBOX_Monster );
// 		assert( m_pID_BUTTON_WorldMap );
// 		assert( m_pID_BUTTON_help );
// // 		assert( m_pID_EDIT_Search );
// 		assert( m_pID_TEXT_Search );
// 		assert( m_pID_BUTTON_Search );
// 		assert( m_pID_TEXT_Product );
// 		assert( m_pID_PICTURE_12180 );
// 		assert( m_pID_TEXT_30 );

// 	m_pID_BUTTON_ShowMap->SetButtonClickFun( ID_BUTTON_ShowMapOnButtonClick );
// 	m_pID_LIST_NpcName->SetRBClickFun( ID_LIST_NpcNameOnListSelectChange );
// 	m_pID_BUTTON_Search->SetButtonClickFun( ID_BUTTON_StartSearchOnButtonClick );

// 		m_pID_CHECKBOX_Shop->SetCheck(true);
// 		m_pID_CHECKBOX_Material->SetCheck(true);
// 		m_pID_CHECKBOX_Storage->SetCheck(true);
// 		m_pID_CHECKBOX_Star->SetCheck(true);
// 		m_pID_CHECKBOX_Guild->SetCheck(true);
// 		m_pID_CHECKBOX_Skill->SetCheck(true);
// 		m_pID_CHECKBOX_Transport->SetCheck(true);
// 		m_pID_CHECKBOX_SpecialPlace->SetCheck(true);
// 		m_pID_CHECKBOX_SpecialItem->SetCheck(true);
// 		m_pID_CHECKBOX_Activity->SetCheck(true);
// 		m_pID_CHECKBOX_OtherNpc->SetCheck(true);
// 		m_pID_CHECKBOX_Monster1->SetCheck(true);
		assert( m_pID_EDIT_InputX );
		assert( m_pID_EDIT_InputY );
		assert( m_pID_BUTTON_Go );

		m_pID_CHECKBOX_ShowFunctionNPC->SetCheck(true);
		m_pID_CHECKBOX_ShowTaskNPC->SetCheck(true);
		m_pID_CHECKBOX_ShowMonster->SetCheck(true);
		m_pID_CHECKBOX_ShowMapLink->SetCheck(true);
		m_pID_CHECKBOX_ShowTransport->SetCheck(true);

		SetShowNpc(true);

 // 		if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
// 		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

	m_pID_PICTURE_WorldMap->SetButtonClickFun(On_PICTURE_WorldMapButtonClick);
	m_pID_PICTURE_WorldMap->SetOnMouseOn(On_PICTURE_WorldMapMouseOn);
	m_pID_PICTURE_WorldMap->SetOnMouseLeave(On_PICTURE_WorldMapMouseLeave);
	m_pID_PICTURE_WorldMap->SetRClickFun(UIRegionMap_RMouseDown);
	m_pID_PICTURE_WorldMap->SetFunOnRButtonUp(UIRegionMap_RMouseUp);
		assert( m_pID_BUTTON_Top );
		assert( m_pID_BUTTON_Left );
		assert( m_pID_BUTTON_Right );
		assert( m_pID_BUTTON_Down );
		assert( m_pID_BUTTON_Big );
		assert( m_pID_BUTTON_Small );
 		assert( m_pID_TEXT_MousePos );
		m_pID_BUTTON_Top->SetLButtonDownFun(UIRegionMap_MoveButtonDown);
		m_pID_BUTTON_Left->SetLButtonDownFun(UIRegionMap_MoveButtonDown);
		m_pID_BUTTON_Right->SetLButtonDownFun(UIRegionMap_MoveButtonDown);
		m_pID_BUTTON_Down->SetLButtonDownFun(UIRegionMap_MoveButtonDown);

	if (m_BGTextureId == -1)
	{
		char fileName[MAX_PATH*2] = {0};
		MeSprintf_s( fileName, sizeof(fileName)/sizeof(char) - 1,"%s", gCfg.m_strMapPath.c_str()/*"data\\Ui\\Common\\HudEquip.dds"*/);
		_strlwr(fileName);
		theControlPictureManager.RegisterTexture(&m_BGTextureId,fileName);
// 		ITextureManager* pMgr = GetEngine()->GetTextureManager();
// 		if( pMgr )
// 		{
// 			m_BGTextureId = pMgr->RegisterTexture(  fileName, FALSE,FALSE);
// 		}	
	}
	char temp[1024] = {0};
	MeSprintf_s(temp,sizeof(temp)/sizeof(char) - 1,theXmlString.GetString(eClient_RegionMap_MousePosition),0,0);
	m_pID_TEXT_MousePos->SetText(temp);

	m_pID_LIST_NpcName->setShowTip(true);
	m_pID_LIST_NpcName->SetItemMaxCount( 200 );
	m_pID_LIST_NpcName->SetCurSelIndex(-1);

	m_pID_LIST_NpcFunction->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_NpcFunction->SetItemMaxCount( 200 );
	m_pID_LIST_NpcFunction->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_NpcFunction->SetCurSelIndex(-1);

	m_pID_EDIT_InputX->SetIsNumber(true);
	m_pID_EDIT_InputY->SetIsNumber(true);
	SetVisable( false );
	m_pID_FRAME_AllNpcList->SetRenderNeedRedraw( s_CUI_ID_FRAME_AllNpcListOnFrameRenderNeedRedraw, true );
    m_pID_FRAME_AllNpcList->SetRenderFun( s_CUI_ID_FRAME_AllNpcListPostFrameRender );

// #define SHOW_BUTTON_TIP(ui)	\
// 	ui->SetShowTip(true);	\
// 	ui->setTip(ui->GetData()->m_szCaption);
// 
// 	SHOW_BUTTON_TIP(m_pID_BUTTON_Big);
// 	SHOW_BUTTON_TIP(m_pID_BUTTON_Small);
 	RefreshMapList();
 	RefreshButtonStatus();
	return true;
	unguard;
}

// 卸载UI
bool CUI_ID_FRAME_AllNpcList::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_AllNpcList = NULL;
	//m_pID_PICTURE_12378 = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_PICTURE_BG = NULL;
	m_pID_LIST_NpcName = NULL;
	//m_pID_BUTTON_Direct = NULL;
	m_pID_PICTURE_WorldMap = NULL;
// 	m_pID_BUTTON_quxiaozhiyin = NULL;
// 	m_pID_TEXT_PuTong = NULL;
// 	m_pID_TEXT_MaiMai = NULL;
// 	m_pID_TEXT_CaiLiao = NULL;
// 	m_pID_TEXT_CangKu = NULL;
// 	m_pID_TEXT_HeChen = NULL;
// 	m_pID_TEXT_JiaoTong = NULL;
	m_pID_BUTTON_WorldMap = NULL;
// 	m_pID_CHECKBOX_Npc = NULL;
// 	m_pID_CHECKBOX_Monster = NULL;
// 	m_pID_TEXT_22486 = NULL;
// 	m_pID_EDIT_Search = NULL;
	m_pID_TEXT_Search = NULL;
	m_pID_BUTTON_Search = NULL;
	m_pID_TEXT_Product = NULL;
	m_pID_BUTTON_Close = NULL;
// 	m_pID_BUTTON_help = NULL;
// 	m_pID_PICTURE_12180 = NULL;
// 	m_pID_CHECKBOX_Shop = NULL;
// 	m_pID_CHECKBOX_Material = NULL;
// 	m_pID_CHECKBOX_Storage = NULL;
// 	m_pID_CHECKBOX_Star = NULL;
// 	m_pID_CHECKBOX_Guild = NULL;
// 	m_pID_CHECKBOX_Skill = NULL;
// 	m_pID_CHECKBOX_Transport = NULL;
// 	m_pID_CHECKBOX_SpecialPlace = NULL;
// 	m_pID_CHECKBOX_SpecialItem = NULL;
// 	m_pID_CHECKBOX_Activity = NULL;
	m_pID_TEXT_30 = NULL;
	m_pID_COMBOBOX_Maplist = NULL;
	m_pID_BUTTON_Top = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Down = NULL;
	m_pID_BUTTON_Big = NULL;
	m_pID_BUTTON_Small = NULL;
	m_pID_TEXT_MousePos = NULL;
	m_pID_EDIT_InputX = NULL;
	m_pID_EDIT_InputY = NULL;
	m_pID_BUTTON_Go = NULL;
	m_mapIndex = -1;
	if (m_BGTextureId != -1)
	{
		theControlPictureManager.UnregisterTexture(m_BGTextureId);
// 		ITextureManager* pMgr = GetEngine()->GetTextureManager();
// 		if( pMgr )
// 		{
// 			pMgr->UnRegisterTexture(m_BGTextureId);
// 		}	
	}
	return theUiManager.RemoveFrame( "data\\ui\\AllNpcList.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_AllNpcList::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_AllNpcList )
		return false;
	return m_pID_FRAME_AllNpcList->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_AllNpcList::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_AllNpcList )
		return;
	m_pID_FRAME_AllNpcList->SetVisable( bVisable );

	m_bDragMap = false;
 	if( bVisable == true)
 	{
		CalDrawParameter();
		RefreshButtonStatus();
		theUiManager.ToTop(m_pID_FRAME_AllNpcList);
 		s_CUI_ID_FRAME_WorldMap.SetVisable(false);
 	}
	unguard;
}
void CUI_ID_FRAME_AllNpcList::ID_LIST_NpcNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem)
{
	guardfunc;

	if( pItem )
	{
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pItem->m_nID);
		if (!pInfo)
		{
			return ;
		}
		GetAdvancedMiniMap()->SetTargetNpc(Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
		{
				m_selectedPosX = -1.f;
				m_selectedPosY = -1.f;
		}
	}
	unguard;
}

void CUI_ID_FRAME_AllNpcList::init()
{
	guardfunc;

	CWorldTile* pCurrTile = CURRENTTILE;
	InitByTile(pCurrTile);

	unguard;
}

#include "ShowScreenText.h"

void CUI_ID_FRAME_AllNpcList::searchNpc( const char* npcname,int mapId) 
{
	guardfunc;

	if (*npcname == '\0')
	{
		char temp[1024];
		MeSprintf_s(temp,sizeof(temp)/sizeof(char) - 1,theXmlString.GetString(eText_NameNoNull),npcname);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_BigMapFindPath, temp );
		return;
	}
	const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(npcname,mapId);
	if (!pInfo)
	{
		char temp[1024];
		MeSprintf_s(temp,sizeof(temp)/sizeof(char) - 1,theXmlString.GetString(eText_StringNoPlayer)/*"没有这个名字“%s”的npc或怪物！\n"*/,npcname);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_BigMapFindPath, temp );
		return;
	}
	RetriveMapIndex(pInfo->_mapId);

	SetShowNpc(pInfo->_bNpc);

		m_selectedPosX = -1.f;
		m_selectedPosY = -1.f;
// 		SetSelectedName(npcname);
		GetAdvancedMiniMap()->SetTargetNpc(npcname);
		unguard;
}


bool SortNpcByName(NpcCoordInfo& pInfo1,NpcCoordInfo& pInfo2)
{
	if(pInfo1._szPinyin.compare(pInfo2._szPinyin) < 0)
		return true;

	return false;
}

void CUI_ID_FRAME_AllNpcList::RefreshNpcNameList(  )
{
	guardfunc;
	int mapId = GetCurrMapId();
	m_pID_LIST_NpcName->Clear();
	m_pID_LIST_NpcName->SetScrollValue(0);
	ControlList::S_List	stItem;
	stItem.clear();
	stItem.UseSelColor = false;
	std::vector<NpcCoordInfo>& npcMap = NpcCoord::getInstance()->getNpcVec();
	if( m_bIsNpcInList )
	{
		std::list<CAdvancedMiniMap::SortNpcType> listSet = GetAdvancedMiniMap()->GetNpcSortList();
		typedef std::list<CAdvancedMiniMap::SortNpcType>::iterator Iter;
		Iter it = listSet.begin();

		bool bInsert = false;
		for (;it != listSet.end();++it)
		{
			bInsert = true;

			std::vector<NpcCoordInfo> vecSet;
			vecSet.clear();
			for( int i=0; i<npcMap.size(); ++i )
			{
				NpcCoordInfo& ThisInfo = npcMap[i];
				if (ThisInfo._nType == eNT_Item)
				{
					continue;
				}

				if(std::find(it->vecSet.begin(),it->vecSet.end(),ThisInfo._nType) == it->vecSet.end())
					continue;

				if(ThisInfo._bPFPossible && ThisInfo._mapId == mapId && ThisInfo._bNpc)
					vecSet.push_back(ThisInfo);
			}

			std::sort(vecSet.begin(),vecSet.end(),SortNpcByName);
			for (int i = 0;i < vecSet.size();++i)
			{
				NpcCoordInfo& ThisInfo = vecSet[i];

				stItem.clear();
				stItem.m_nHiberarchy = 1;
				std::string  listContext;
				// 				int nImageType = GetAdvancedMiniMap()->GetImageMap(ThisInfo._nType);
				// 				CAdvancedMiniMap::Image* pImage = GetAdvancedMiniMap()->GetImage(nImageType);
				// 				if (pImage->shortcut[0] != '\0')
				// 				{
				// 					listContext= pImage->shortcut;
				// 				}
				// 				else
				// 				{
				// 					listContext= "      ";
				// 				}
				listContext += Common::_tstring::toNarrowString(ThisInfo._szName.c_str()).c_str();
				NpcInfo::Npc* pNpc = NpcInfo::Instance().GetNpcByStaticId(ThisInfo._nID);
				if (pNpc)
				{
					for (int n = listContext.length();n < 10;++n)
						listContext += " ";

					listContext += pNpc->tip.c_str();
				}

				// 				ExpressionManager::GetInstance().AddExpressionAni(listContext);

				D3DCOLOR col = 0;
				if(ThisInfo._nType == eNT_Normal  ) 
				{
					//stItem.SetData( listContext.c_str(), ThisInfo._nID, NULL, Color_Config.getColor(CC_NPCLIST_NPCTYPE_1) );
					col = Color_Config.getColor(CC_NPCLIST_NPCTYPE_1);
				}
				if( ThisInfo._nType == eNT_Restore || ThisInfo._nType == eNT_Weapon || ThisInfo._nType == eNT_Jewelry || ThisInfo._nType == eNT_Dress || ThisInfo._nType == eNT_SpecialSale)
				{
					//stItem.SetData( listContext.c_str(), ThisInfo._nID, NULL, Color_Config.getColor(CC_NPCLIST_NPCTYPE_2) );
					col = Color_Config.getColor(CC_NPCLIST_NPCTYPE_2);
				}
				if( ThisInfo._nType == eNT_Material || ThisInfo._nType == eNT_Cavalry)
				{
					//stItem.SetData( listContext.c_str(), ThisInfo._nID, NULL, Color_Config.getColor(CC_NPCLIST_NPCTYPE_3) );
					col = Color_Config.getColor(CC_NPCLIST_NPCTYPE_3);
				}
				if( ThisInfo._nType == eNT_Transport || ThisInfo._nType == eNT_YiZhan)
				{
					//stItem.SetData( listContext.c_str(), ThisInfo._nID, NULL, Color_Config.getColor(CC_NPCLIST_NPCTYPE_4) );
					col = Color_Config.getColor(CC_NPCLIST_NPCTYPE_4);
				}
				if( ThisInfo._nType == eNT_Storage || ThisInfo._nType == eNT_Sale || ThisInfo._nType == eNT_PeiJian || ThisInfo._nType == eNT_ShiWu || ThisInfo._nType == eNT_ZaHuo)
				{
					//stItem.SetData( listContext.c_str(), ThisInfo._nID, NULL, Color_Config.getColor(CC_NPCLIST_NPCTYPE_5) );
					col = Color_Config.getColor(CC_NPCLIST_NPCTYPE_5);
				}

				if( ThisInfo._nType == eNT_MakeItemNpc || ThisInfo._nType == eNT_Star || ThisInfo._nType == eNT_KeepWord2
					|| ThisInfo._nType == eNT_KeepWord3|| ThisInfo._nType == eNT_KeepWord4|| ThisInfo._nType == eNT_KeepWord5
					||ThisInfo._nType == eNT_KeepWord6||ThisInfo._nType == eNT_KeepWord7)
				{
					//stItem.SetData( listContext.c_str(), ThisInfo._nID, NULL, Color_Config.getColor(CC_NPCLIST_NPCTYPE_6) );
					col = Color_Config.getColor(CC_NPCLIST_NPCTYPE_6);
				}
				if( ThisInfo._nType == eNT_Activity || ThisInfo._nType == eNT_Feudal || (ThisInfo._nType >= eNT_GongXun && ThisInfo._nType <=eNT_JiNeng))
				{
					//stItem.SetData( listContext.c_str(), ThisInfo._nID, NULL, Color_Config.getColor(CC_NPCLIST_NPCTYPE_7) );
					col = Color_Config.getColor(CC_NPCLIST_NPCTYPE_7);
				}
				stItem.SetData(listContext.c_str(), ThisInfo._nID, NULL,col);
				if (stItem.m_szText[0] != '\0')
				{
					if(bInsert)
					{
						ControlList::S_List	stParentItem;
						stParentItem.clear();

						stParentItem.UseSelColor = false;
						stParentItem.m_nHiberarchy = 0;
						stParentItem.SetData((*it).strType.c_str(),-1);
						m_pID_LIST_NpcName->AddItem( &stParentItem,NULL, false);
						bInsert = false;
					}

					const NpcCoordInfo* pNpcInPrimaryMap = NpcCoord::getInstance()->/*getNpcCoordInPrimaryMap*/getNpcCoord(ThisInfo._nID);
					s_CUI_ID_FRAME_Task.FillMapPosTip(pNpcInPrimaryMap,&stItem);
					ControlList::S_List* pList = m_pID_LIST_NpcName->AddItem( &stItem,NULL, false);
				}
			}
		}
		RefreshNpcFunction();
	}
	else
	{
		for( int i=0; i<npcMap.size(); ++i )
		{
			NpcCoordInfo& ThisInfo = npcMap[i];
			if(ThisInfo._bPFPossible && ThisInfo._mapId == mapId && !ThisInfo._bNpc && ThisInfo._bMask)
				{
					stItem.SetData( Common::_tstring::toNarrowString(ThisInfo._szName.c_str()).c_str(), ThisInfo._nID, NULL, Color_Config.getColor(CC_ENTITY_MONSTER_PASSIVITY) );
					m_pID_LIST_NpcName->AddItem( &stItem,NULL, false);
				}
		}
	}
	unguard;
}
bool CUI_ID_FRAME_AllNpcList::EditInputIsVisable()
{
	guardfunc;
	if( m_pID_EDIT_InputX && m_pID_EDIT_InputY)
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_InputX) || (theUiManager.GetFocus() == m_pID_EDIT_InputY) ;
	}
	return FALSE;
	unguard;
}

bool CUI_ID_FRAME_AllNpcList::ID_LIST_NpcNameOnListDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( pItem )
	{
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pItem->m_nID,GetCurrMapId());
		if (!pInfo)
		{
			return false;
		}
		NpcCoord::getInstance()->clickHyberToMiniMap(pInfo);

	}
	return true;
}


void CUI_ID_FRAME_AllNpcList::ID_COMBOBOX_MaplistOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	std::string strTmp = szData;
	CWorldTile * pTile = NULL;
	std::string::size_type pos = strTmp.find(":");
	if (pos != std::string::npos)
	{
		std::string strCountry = strTmp.substr(0,pos);
		short sCountryId = CountryFunction::GetCountryIdByName(strCountry.c_str());
		strTmp = strTmp.substr(pos + 1);
		pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromTileName(strTmp.c_str(),sCountryId);
	}
	else
	{
		pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromTileName(strTmp.c_str());
	}
	if( pTile )
		InitByTile(pTile);
// 		RetriveMapIndex(pTile->GetMapId()); 
}

void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_NpcOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (false == m_bIsNpcInList)
	{
		SetShowNpc(true);
	}
// 	m_pID_CHECKBOX_Npc->SetCheck(true);
// 	m_pID_CHECKBOX_Monster->SetCheck(false);

}
void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_MonsterOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (true == m_bIsNpcInList)
	{
		SetShowNpc(false);
	}
// 	m_pID_CHECKBOX_Npc->SetCheck(false);
// 	m_pID_CHECKBOX_Monster->SetCheck(true);
}

bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_WorldMapOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	RECT rcWindow;
	s_CUI_ID_FRAME_WorldMap.SetVisable(true,true);
	/*m_pID_FRAME_AllNpcList->GetRealRect(&rcWindow);
	s_CUI_ID_FRAME_WorldMap.SetPos(rcWindow.top,rcWindow.left);*/
	//zhuxincong 9.21 修改
	SetVisable(false);
	return true;
	unguard;
}

bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	return true;

}

void CUI_ID_FRAME_AllNpcList::ID_EDIT_SearchOnEditEnter( ControlObject* pSender, const char* szData )
{
	guardfunc;
	unguard;

}

bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_SearchOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	return true;
	unguard;
}

void CUI_ID_FRAME_AllNpcList::RetriveMapIndex( int mapId )
{
// 	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(mapId);
// 	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
// 	if (!pMe || (pMe->GetLevel() < pTile->GetMinLevel()))
// 	{
// 		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_BigMapFindPath, theXmlString.GetString(eText_LevelNotReachable) );
// 		int MapId = GetCurrMapId();
// 		CWorldTile* pSelTile  = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(MapId);
// 		char tmp[256];
// 		if (pSelTile->GetCountry()!=0)
// 		{
// 			std::string strCountryName = CountryFunction::GetCountryNameById(pSelTile->GetCountry());
// 			sprintf_s(tmp,256,"%s:%s",strCountryName.c_str(),pSelTile->GetTileName());
// 		}
// 		else
// 		{
// 			sprintf_s(tmp,256,"%s",pTile->GetTileName());
// 		}
// 
// 		m_pID_COMBOBOX_Maplist->GetEditInput().SetText(tmp);
// 		return;
// 	}
	ControlList& mapList = m_pID_COMBOBOX_Maplist->GetListBox();
	for (int i = 0; i < mapList.GetListItemCnt(); ++i)
	{
		if (mapList.GetListItem(i)->m_nID == mapId)
		{
			m_mapIndex = i;
			m_pID_COMBOBOX_Maplist->GetListBox().SetCurSelIndex( m_mapIndex );
			RegionMapChanged(mapId);
		}		
	}
}

void CUI_ID_FRAME_AllNpcList::RegionMapChanged( int mapId )
{
	CWorldTile* worldTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(mapId);
	if (worldTile )
	{
			flt32 worldWidth = worldTile->GetWidth();
			flt32 worldHeight = worldTile->GetDepth();

			if (worldWidth > worldHeight )
			{
				m_maxDimension = (worldWidth * worldTile->GetRegionEdge()) /(g_nsrcPixelEdgeLength);
				m_xPixelOffset = 0 - worldTile->GetRegionOffsetX()*worldWidth/g_nsrcPixelEdgeLength;
				m_yPixelOffset = (worldWidth - worldHeight)/2 - worldTile->GetRegionOffsetY()*worldWidth/g_nsrcPixelEdgeLength;
			}
			else
			{
				m_maxDimension = (worldHeight * worldTile->GetRegionEdge()) /(g_nsrcPixelEdgeLength);
				m_xPixelOffset = (worldHeight - worldWidth)/2 - worldTile->GetRegionOffsetX()*worldHeight/g_nsrcPixelEdgeLength;
				m_yPixelOffset = 0 - worldTile->GetRegionOffsetY()*worldHeight/g_nsrcPixelEdgeLength;
			}
		if (m_maxDimension == 0)
		{
			m_maxDimension = 1024;
		}
		CalDrawParameter();
	}

}
void CUI_ID_FRAME_AllNpcList::On_PICTURE_WorldMapMouseOn( ControlObject* pSender )
{
	s_CUI_ID_FRAME_AllNpcList.m_bTipActive = true;
}

void CUI_ID_FRAME_AllNpcList::On_PICTURE_WorldMapMouseLeave( ControlObject* pSender )
{
	s_CUI_ID_FRAME_AllNpcList.m_bTipActive = false;
	s_CUI_ID_FRAME_AllNpcList.m_bMoveMap = false;
	s_CUI_ID_FRAME_AllNpcList.m_bDragMap = false;

}

#include "../CrossMapPF.h"

bool CUI_ID_FRAME_AllNpcList::On_PICTURE_WorldMapButtonClick( ControlObject* pSender )
{
	if(!pSender->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
	{
		return false;
	}

	float posx = 0,posy = 0;
	if( !s_CUI_ID_FRAME_AllNpcList.GetRealPosition(posx, posy))
		return false;

	{
		CRegionMap::RegionMapImage* pNpcCursorOn = GetRegionMap()->GetNpcCursorOn();
		if (pNpcCursorOn)
		{
			if (pNpcCursorOn->pInfo)
			{
				GetAdvancedMiniMap()->SetTargetNpc(Common::_tstring::toNarrowString(pNpcCursorOn->pInfo->_szName.c_str()).c_str());
				NpcCoord::getInstance()->clickHyberToMiniMap(pNpcCursorOn->pInfo);
			}
			else
			{
				assert(-1 != pNpcCursorOn->nPlayerId);
// 				std::map< short, CPlayer* >& playArr = theHeroGame.GetPlayerMgr()->m_mapPlayers;
				CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(pNpcCursorOn->nPlayerId);
				if (pPlayer)
				{
					theHeroGame.GetPlayerMgr()->MoveRoleToPlayer(pPlayer);
				}
			}
			s_CUI_ID_FRAME_AllNpcList.m_selectedPosX = -1.f;
			s_CUI_ID_FRAME_AllNpcList.m_selectedPosY = -1.f;
			GetAdvancedMiniMap()->SetTargetNpc(pNpcCursorOn->GetName());
		}
		else
		{
			s_CUI_ID_FRAME_AllNpcList.m_selectedPosX = posx;
			s_CUI_ID_FRAME_AllNpcList.m_selectedPosY = posy;
			int nSelTileId  = s_CUI_ID_FRAME_AllNpcList.GetCurrMapId();
			s_CUI_ID_FRAME_AllNpcList.m_selectedPosMap = nSelTileId;
			s_CUI_ID_FRAME_MiniMap.SetLastPFPoint(posx,posy,nSelTileId);
			s_CUI_ID_FRAME_AllNpcList.MoveToXY(posx,posy,nSelTileId);
			s_CUI_ID_FRAME_AllNpcList.m_seletedName.clear();
			GetAdvancedMiniMap()->SetTargetNpc(NULL);

		}
	}

	return true;
}

void CUI_ID_FRAME_AllNpcList::SetShowNpc( bool flag )
{
// 	if (flag)
// 	{
// 		m_pID_CHECKBOX_Npc->SetCheck(true);
// 		m_pID_CHECKBOX_Monster->SetCheck(false);
// 	}
// 	else
// 	{
// 		m_pID_CHECKBOX_Npc->SetCheck(false);
// 		m_pID_CHECKBOX_Monster->SetCheck(true);
// 	}
	{
		m_bIsNpcInList = flag;
	}
}

void CUI_ID_FRAME_AllNpcList::SetSelectedName( const char* npcname )
{
	m_seletedName = npcname;
	int npcNameIndex = m_pID_LIST_NpcName->FindItemByItem(npcname);
	if( npcNameIndex != -1)
	{
		m_pID_LIST_NpcName->SetCurSelIndex( npcNameIndex );
	}
}

void CUI_ID_FRAME_AllNpcList::SetSelectedPos( int x,int y )
{
	if( !m_pID_FRAME_AllNpcList )
		return;
	CWorldTile* pCurrTile = CURRENTTILE;
	
	if (GetCurrMapId() == pCurrTile->GetMapId())
	{
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pCurrTile->GetMapId(),x,y);
		if (pInfo)
		{
			s_CUI_ID_FRAME_AllNpcList.m_selectedPosX = -1.f;
			s_CUI_ID_FRAME_AllNpcList.m_selectedPosY = -1.f;
			GetAdvancedMiniMap()->SetTargetNpc(Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
		}
		else
		{
			s_CUI_ID_FRAME_AllNpcList.m_selectedPosX = x;
			s_CUI_ID_FRAME_AllNpcList.m_selectedPosY = y;
			s_CUI_ID_FRAME_AllNpcList.m_selectedPosMap = pCurrTile->GetMapId();
			GetAdvancedMiniMap()->SetTargetNpc(NULL);
		}
	}

}

int CUI_ID_FRAME_AllNpcList::GetCurrMapId()
{
	return mCurMapID;
	/*if (m_mapIndex == -1)
	{
		return -1;
	}
	ControlList::S_List* pMapItem = m_pID_COMBOBOX_Maplist->GetListBox().GetListItem(m_mapIndex);

	if (pMapItem)
	{
		return pMapItem->m_nID;
	}
	return -1;*/
}


void CUI_ID_FRAME_AllNpcList::InitByTile( CWorldTile* pCurrTile )
{
	if( !m_pID_FRAME_AllNpcList )
		return;
	if (pCurrTile == NULL)
	{
		return;
	}

	mCurMapID = pCurrTile->GetMapId();
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
 	if (!pMe || (pMe->GetLevel() < pCurrTile->GetMinLevel()))
 	{
 		//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_BigMapFindPath, theXmlString.GetString(eText_LevelNotReachable) );
 		return;
 	}
	RegionMapChanged(pCurrTile->GetMapId());
	char tmp[256];
	//if (pCurrTile->GetCountry()!=0)
	//{
	//	std::string strCountryName = CountryFunction::GetCountryNameById(pCurrTile->GetCountry());
	//	sprintf_s(tmp,256,"%s:%s",strCountryName.c_str(),pCurrTile->GetTileName());
	//}
	//else
	//{
	//	sprintf_s(tmp,256,"%s",pCurrTile->GetTileName());
	//}
sprintf_s(tmp,256,"%s",pCurrTile->GetTileName());
	std::string strTmp = tmp;
	/*if ( theSepatatePartConfig.IsPartMap( pCurrTile->GetMapId() ) )
	{
		std::string str = theSepatatePartConfig.GetName( thePlayerRole.m_nSepatatePartVar );
		if ( !str.empty() )
		{
			strTmp += str;
		}
	}*/
	/*std::string str = s_CUI_ID_FRAME_SelectChannel.GetChannelName();
	if ( str.length() > 0 && theHeroGame.GetLandID() == mCurMapID )
	{
		strTmp += "（";
		strTmp += str;
		strTmp += "）";
	}*/

	m_pID_COMBOBOX_Maplist->GetEditInput().SetText(strTmp);
	RetriveMapIndex(pCurrTile->GetMapId());
	RefreshNpcNameList();
	m_pID_EDIT_InputX->SetNumberLimit(true,0,pCurrTile->GetWidth());
	m_pID_EDIT_InputY->SetNumberLimit(true,0,pCurrTile->GetDepth());
	if (m_seletedName.length() != 0)
	{
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(m_seletedName.c_str(),pCurrTile->GetMapId());
		if (pInfo)
		{
			SetShowNpc(pInfo->_bNpc);
		}
		else
		{

		}
	}
	else
	{

	}
}

// void CUI_ID_FRAME_AllNpcList::UpdateEctypeName()
// {
// 	if( !m_pID_FRAME_AllNpcList )
// 		return;
// 
// 	SetVisable(false);
// 	if(m_addEctype)
// 	{
// 		m_addEctype = false;
// 		int nMapCount = m_pID_COMBOBOX_Maplist->GetListBox().GetListItemCnt();
// 		m_pID_COMBOBOX_Maplist->GetListBox().RemoveListItem( nMapCount - 1 );
// 	}
// 	{
// 		CWorldTile* pTile = CURRENTTILE;
// 		if (pTile->GetMapType() != 0 || pTile->GetOrder() == 0)
// 		{//副本地图
// 			m_addEctype = true;
// 			ControlList::S_List	stItem;
// 			stItem.SetData( pTile->GetTileName(), pTile->GetMapId(), NULL, Color_Config.getColor(CC_NPCLIST_MAPNAME) );
// 			m_pID_COMBOBOX_Maplist->GetListBox().AddItem( &stItem,NULL, false);
// 		}
// 		RefreshMapList();
// 		InitByTile(pTile);
// 
// 	}
// }

void CUI_ID_FRAME_AllNpcList::RefreshMapList()
{
	if (NULL == m_pID_FRAME_AllNpcList)
	{
		return;
	}
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (!pMe)
	{
		return;
	}

	ControlList& mapList = m_pID_COMBOBOX_Maplist->GetListBox();
	mapList.Clear();
	std::vector<CWorldTile*>& SortArr = SwGlobal::GetWorld()->GetWorldBuffer()->GetMapSortbyLevelArr();
	std::vector<CWorldTile*>::iterator iter = SortArr.begin();
	ControlList::S_List	stItem;
	CWorldTile* pCurrTile = CURRENTTILE;
	while(iter != SortArr.end())
	{
		CWorldTile* pTile = (*iter);
		if (pTile
			&& ((pTile == pCurrTile) || (pTile->GetCountry() == pMe->GetRealCountry()))
			)
		{
			char tmp[256];
			//if (pTile->GetCountry()!=0)
			//{
			//	std::string strCountryName = CountryFunction::GetCountryNameById(pTile->GetCountry());
			//	sprintf_s(tmp,256,"%s:%s",strCountryName.c_str(),pTile->GetTileName());
			//}
			//else
			//{
			//	sprintf_s(tmp,256,"%s",pTile->GetTileName());
			//}
sprintf_s(tmp,256,"%s",pTile->GetTileName());
			/*std::string strTmp = tmp;
			if ( theSepatatePartConfig.IsPartMap( pCurrTile->GetMapId() ) )
			{
				std::string str = theSepatatePartConfig.GetName( thePlayerRole.m_nSepatatePartVar );
				if ( !str.empty() )
				{
					strTmp += "(";
					strTmp += str;
					strTmp += ")";
				}
			}*/

			stItem.SetData( tmp, pTile->GetMapId(), NULL, Color_Config.getColor(CC_NPCLIST_MAPNAME) );
			stItem.SetMargin( 5 );
			mapList.AddItem( &stItem,NULL, false);
		}
		++iter;
	}
	if (pCurrTile->GetMapType() != 0 || pCurrTile->GetOrder() == 0)
	{//副本地图
		ControlList::S_List	stItem;
		stItem.SetData( pCurrTile->GetTileName(), pCurrTile->GetMapId(), NULL, Color_Config.getColor(CC_NPCLIST_MAPNAME) );
		stItem.SetMargin( 5 );
		mapList.AddItem( &stItem,NULL, false);
	}
}

void CUI_ID_FRAME_AllNpcList::ShowTile( CWorldTile* pCurrTile,int x,int y )
{
	SetVisable(true);
	if( !m_pID_FRAME_AllNpcList )
		return;
	if (pCurrTile == NULL)
	{
		return;
	}
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (!pMe || (pMe->GetLevel() < pCurrTile->GetMinLevel()))
	{
		//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_BigMapFindPath, theXmlString.GetString(eText_LevelNotReachable) );
		return;
	}
	InitByTile(pCurrTile);
	const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pCurrTile->GetMapId(),x,y);
	if (pInfo)
	{
		m_selectedPosX = -1.f;
		m_selectedPosY = -1.f;
		GetAdvancedMiniMap()->SetTargetNpc(Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str());
	}
	else
	{
		m_selectedPosX = x;
		m_selectedPosY = y;
		m_selectedPosMap = pCurrTile->GetMapId();
		GetAdvancedMiniMap()->SetTargetNpc(NULL);
	}
}

bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_TopOnButtonClick( ControlObject* pSender )
{
	m_bMoveMap = false;
	return true;
}

bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	m_bMoveMap = false;
	return true;
}

bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	m_bMoveMap = false;
	return true;
}

bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_ButtonOnButtonClick( ControlObject* pSender )
{
	m_bMoveMap = false;
	return true;
}

bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_BigOnButtonClick( ControlObject* pSender )
{
	cShowType = eShowOriginalMap;
	CalDrawParameter();
	RefreshButtonStatus();
	return true;
}

bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_SmallOnButtonClick( ControlObject* pSender )
{
	cShowType = eShowAllMap;
	CalDrawParameter();
	RefreshButtonStatus();
	return true;
}

void CUI_ID_FRAME_AllNpcList::RefreshButtonStatus()
{
	if (cShowType == eShowOriginalMap)
	{
		m_pID_BUTTON_Small->SetVisable(true);
		m_pID_BUTTON_Big->SetVisable(false);

		m_pID_BUTTON_Top->SetEnable(m_rcSrc.top > 0);
		m_pID_BUTTON_Left->SetEnable(m_rcSrc.left > 0);
		m_pID_BUTTON_Right->SetEnable(m_rcSrc.right < g_nsrcPixelEdgeLength);
		m_pID_BUTTON_Down->SetEnable(m_rcSrc.bottom < g_nsrcPixelEdgeLength);
	}
	else
	{
		m_pID_BUTTON_Small->SetVisable(false);
		m_pID_BUTTON_Big->SetVisable(true);
		m_pID_BUTTON_Top->SetEnable(false);
		m_pID_BUTTON_Left->SetEnable(false);
		m_pID_BUTTON_Right->SetEnable(false);
		m_pID_BUTTON_Down->SetEnable(false);
	}
}

void CUI_ID_FRAME_AllNpcList::CalDrawParameter(bool bReCalSrcRect)
{
	if( !m_pID_FRAME_AllNpcList )
		return;
	if( m_pID_PICTURE_WorldMap )
		m_pID_PICTURE_WorldMap->GetRealRect( &m_rcDes );
	LONG lWidth = m_rcDes.right - m_rcDes.left;
	LONG lHeight = m_rcDes.bottom - m_rcDes.top;
	if (cShowType == eShowAllMap)
	{
		m_rcSrc.left = 0;
		m_rcSrc.right = g_nsrcPixelEdgeLength;
		m_rcSrc.top = 0;
		m_rcSrc.bottom = g_nsrcPixelEdgeLength;
		if (lWidth > lHeight)
		{
			LONG lDelta = (lWidth - lHeight)/2;
			m_rcDes.right -= lDelta;
			m_rcDes.left += lDelta;
		}
		else
		{
			LONG lDelta = (lHeight - lWidth)/2;
			m_rcDes.bottom -= lDelta;
			m_rcDes.top += lDelta;
		}
	}
	else
	{
		if (lWidth > g_nsrcPixelEdgeLength)
		{
			LONG lDelta = (lWidth - g_nsrcPixelEdgeLength)/2;
			m_rcDes.right -= lDelta;
			m_rcDes.left += lDelta;
			m_rcSrc.left = 0;
			m_rcSrc.right = g_nsrcPixelEdgeLength;
		}
		else
		{
			if (bReCalSrcRect)
			{
				if (theHeroGame.GetPlayerMgr()->GetMe())
				{
					float fMeX;
					theHeroGame.GetPlayerMgr()->GetMe()->GetPos(&fMeX,NULL,NULL);
					LONG x = (m_xPixelOffset + fMeX)*g_nsrcPixelEdgeLength/m_maxDimension;
					m_rcSrc.right = x + lWidth/2;
					m_rcSrc.left = x - lWidth/2;
					if (m_rcSrc.left < 0)
					{
						m_rcSrc.left = 0;
						m_rcSrc.right = lWidth;
					}
					if (m_rcSrc.right > g_nsrcPixelEdgeLength)
					{
						m_rcSrc.left = g_nsrcPixelEdgeLength - lWidth;
						m_rcSrc.right = g_nsrcPixelEdgeLength;
					}
				}
			}
		}
		if (lHeight > g_nsrcPixelEdgeLength)
		{
			LONG lDelta = (lHeight - g_nsrcPixelEdgeLength)/2;
			m_rcDes.bottom -= lDelta;
			m_rcDes.top += lDelta;
			m_rcSrc.top = 0;
			m_rcSrc.bottom = g_nsrcPixelEdgeLength;
		}
		else
		{
			if (bReCalSrcRect)
			{
				if (theHeroGame.GetPlayerMgr()->GetMe())
				{
					float fMeY;
					theHeroGame.GetPlayerMgr()->GetMe()->GetPos(NULL,&fMeY,NULL);
					LONG y = (m_maxDimension - (m_yPixelOffset + fMeY))*g_nsrcPixelEdgeLength/m_maxDimension;
					m_rcSrc.top = y - lHeight/2;
					m_rcSrc.bottom = y + lHeight/2;
					if (m_rcSrc.top < 0)
					{
						m_rcSrc.top = 0;
						m_rcSrc.bottom = lHeight;
					}
					if (m_rcSrc.bottom > g_nsrcPixelEdgeLength)
					{
						m_rcSrc.top = g_nsrcPixelEdgeLength - lHeight;
						m_rcSrc.bottom = g_nsrcPixelEdgeLength;
					}
				}
			}
		}
	}
	if (bReCalSrcRect)
	{
		RefreshButtonStatus();
	}

}

bool CUI_ID_FRAME_AllNpcList::UIRegionMap_MoveButtonDown( INT nX, INT nY )
{
	s_CUI_ID_FRAME_AllNpcList.m_bMoveMap = true;
	return true;
}

bool CUI_ID_FRAME_AllNpcList::UIRegionMap_RMouseDown( INT nX, INT nY )
{
	s_CUI_ID_FRAME_AllNpcList.m_bDragMap = true;
	s_CUI_ID_FRAME_AllNpcList.m_lastPoint.x = nX;
	s_CUI_ID_FRAME_AllNpcList.m_lastPoint.y = nY;
	return true;

}

bool CUI_ID_FRAME_AllNpcList::UIRegionMap_RMouseUp( INT nX, INT nY )
{
	s_CUI_ID_FRAME_AllNpcList.m_bDragMap = false;
	return true;

}

bool CUI_ID_FRAME_AllNpcList::GetRealPosition( float &posx, float &posy )
{
	if (!m_pID_PICTURE_WorldMap->PtInObject(theUiManager.m_ptMoust.x,theUiManager.m_ptMoust.y,false))
	{
		return false;
	}
	posx = (m_rcSrc.left + (theUiManager.m_ptMoust.x - (m_rcDes.left)))/(m_PixelPerRealDis ) - m_xPixelOffset;
	posy = ((g_nsrcPixelEdgeLength - m_rcSrc.bottom)+((m_rcDes.bottom) - theUiManager.m_ptMoust.y ))/(m_PixelPerRealDis) - m_yPixelOffset;
	int MapId = GetCurrMapId();
	CWorldTile* pSelTile  = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(MapId);
	if (!pSelTile || posx < 0 || posx > pSelTile->GetWidth() || posy < 0 || posy > pSelTile->GetDepth())
	{
		return false;
	}
	return true;
}

bool CUI_ID_FRAME_AllNpcList::IsWorldMapActivity()
{
	return (m_pID_PICTURE_WorldMap->IsVisable())
		&& (m_pID_PICTURE_WorldMap->PtInObject(theUiManager.m_ptMoust.x,theUiManager.m_ptMoust.y))
		&& (theUiManager.getUIVec()[UI_Render_LayerThree][0]->m_pUI == m_pID_FRAME_AllNpcList);
}

bool CUI_ID_FRAME_AllNpcList::ID_BUTTON_StoryMapOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_WorldMap.SetVisable(true,false);
	RECT rcWindow;
	m_pID_FRAME_AllNpcList->GetRealRect(&rcWindow);
	s_CUI_ID_FRAME_WorldMap.SetPos(rcWindow.left,rcWindow.top);
	SetVisable(false);
	return true;
}



void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_ShowFunctionNPCOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (*pbChecked)
	{
		m_ShowType |= Npc_Shop;
		m_ShowType |= Npc_Material;
		m_ShowType |= Npc_Storage;
		m_ShowType |= Npc_Star;
		m_ShowType |= Npc_Gang;
		m_ShowType |= Npc_Skill;
		m_ShowType |= Npc_SpecialPlace;
		m_ShowType |= Npc_SpecialItem;
		m_ShowType |= Npc_Activity;
	}
	else
	{
		m_ShowType &= (~Npc_Shop);
		m_ShowType &= (~Npc_Material);
		m_ShowType &= (~Npc_Storage);
		m_ShowType &= (~Npc_Star);
		m_ShowType &= (~Npc_Gang);
		m_ShowType &= (~Npc_Skill);
		m_ShowType &= (~Npc_SpecialPlace);
		m_ShowType &= (~Npc_SpecialItem);
		m_ShowType &= (~Npc_Activity);
	}
	GetRegionMap()->SetUpdateStableImage(true);

}

void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_ShowTaskNPCOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (*pbChecked)
	{
		m_ShowType |= Npc_TaskNpc;
	}
	else
	{
		m_ShowType &= (~Npc_TaskNpc);
	}
	GetRegionMap()->SetUpdateStableImage(true);

}

void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_ShowMonsterOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (*pbChecked)
	{
		m_ShowType |= Npc_Monster;
	}
	else
	{
		m_ShowType &= (~Npc_Monster);
	}
	GetRegionMap()->SetUpdateStableImage(true);

}

void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_ShowMapLinkOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (*pbChecked)
	{
		m_ShowType |= Npc_Transpot;
	}
	else
	{
		m_ShowType &= (~Npc_Transpot);
	}
	GetRegionMap()->SetUpdateStableImage(true);

}

void CUI_ID_FRAME_AllNpcList::ID_CHECKBOX_ShowTransportOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (*pbChecked)
	{
		m_ShowType |= Npc_TranspotNpc;
	}
	else
	{
		m_ShowType &= (~Npc_TranspotNpc);
	}
	GetRegionMap()->SetUpdateStableImage(true);

}

void CUI_ID_FRAME_AllNpcList::ID_LIST_NpcFunctionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{

}

void CUI_ID_FRAME_AllNpcList::RefreshNpcFunction()
{
	if( !m_pID_LIST_NpcFunction || !m_pID_LIST_NpcName )
		return;

	return;

	m_pID_LIST_NpcFunction->Clear(false);
	for (int i = 0; i < m_pID_LIST_NpcName->GetListItemCnt(); ++i)
	{
		ControlList::S_List stItem;
		int nNpcId = m_pID_LIST_NpcName->GetListItem(i)->m_nID;
		if (nNpcId != -1)
		{
			NpcInfo::Npc* pNpc = NpcInfo::Instance().GetNpcByStaticId(nNpcId);
			if (pNpc)
			{
				stItem.SetData(pNpc->tip.c_str());
			}
		}
		m_pID_LIST_NpcFunction->AddItem(&stItem);
	}

	int nStartIndex = m_pID_LIST_NpcName->GetShowStartHeight();
	m_pID_LIST_NpcFunction->SetShowStartHeight(nStartIndex);
}

void CUI_ID_FRAME_AllNpcList::MoveToXY( int posx, int posy, int nSelTileId )//zhuxincong 大地图上，点击坐标，上马寻路过去
{
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();

	float fXOff = 0;
	float fYOff = 0;
	float fDist = 0;
	
	fXOff = posx - pMe->GetPos().x;
	fYOff = posy - pMe->GetPos().y;
	fDist = sqrtf(fXOff*fXOff+fYOff*fYOff);
	
	CWorldTile* ptile = CURRENTTILE;

	if (thePlayerRole.GetActivedMount())
	{
		//zhuxincong 8.2 2012 寻路上马
		if (!(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting()) && fDist>=50)
		{
			// 压镖状态下寻路禁止上马
			if (!theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
				s_CUI_ID_FRAME_Pet.Mount();
		}
	}

	if (ptile && ptile->GetMapId() == nSelTileId)
	{
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			theHeroGame.GetPlayerMgr()->GetMe()->SetActionTarget(-1);

		theHeroGame.GetPlayerMgr()->MoveRoleTo(posx, posy);
	}
	else if( theHeroGame.GetPlayerMgr()->GetMe() )
	{	
		float startPosx,startPosy;
		theHeroGame.GetPlayerMgr()->GetMe()->GetPos(&startPosx,&startPosy,NULL);
		bool bRet = CrossMapPF::Instance()->CrossMapFindPath(ptile->GetMapId(),startPosx,startPosy,nSelTileId,posx,posy);
		if (!bRet)
		{
			if (ptile->GetMapId() != nSelTileId)
			{
				s_CUI_ID_FRAME_FindRoad.ResetRoadInfo();
				s_CUI_ID_FRAME_FindRoad.SetTargetInfo(ptile->GetMapId(),nSelTileId,posx,posy);
				s_CUI_ID_FRAME_FindRoad.SetVisable(true);
				s_CUI_ID_FRAME_FindRoad.RefreshRoadInfo();
			}
			//s_CUI_ID_FRAME_AllNpcList.m_selectedPosX = -1.f;
			//s_CUI_ID_FRAME_AllNpcList.m_selectedPosY = -1.f;
			/*CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_BigMapFindPath, theXmlString.GetString(eText_CannotCrossMapPathFindAddress) );*/
		}
	}
}

bool CUI_ID_FRAME_AllNpcList::OnFrameRender()
{
	return true;
}

void CUI_ID_FRAME_AllNpcList::SetPos( int x,int y )
{
	if (m_pID_FRAME_AllNpcList)
	{
		m_pID_FRAME_AllNpcList->SetPos(x,y);
	}
}

bool CUI_ID_FRAME_AllNpcList::PostFrameRender()
{
    if( !IsUILoad() || !IsVisable() )
        return true;

    if( !CPlayer::IsServerTerrainRectShow() )
        return true;

    CWorldTile* pTile = CURRENTTILE;
    if( !pTile )
        return true;

    if( GetCurrMapId() != pTile->GetMapId() )
        return true;

    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
    if( !pPlayerMgr )
        return true;

    CPlayer* pMe = pPlayerMgr->GetMe();
    if( !pMe )
        return true;

    float fMapWidth = pTile->GetWidth();
    float fMapLength = pTile->GetDepth();

    D3DXVECTOR3 vPos = pMe->GetPos();
    if( vPos.x < 0 || vPos.x > fMapWidth || vPos.y < 0 || vPos.y > fMapLength )
        return true;

    float fBigRectSize = MAPTILESIZE * dr_stageAreaSize;
    int nBigRectRCount = fMapWidth / fBigRectSize;
    int nBigRectVCount = fMapLength / fBigRectSize;

    int nMeRIndex = vPos.x / fBigRectSize;
    int nMeVIndex = vPos.y / fBigRectSize;

    // 计算边框 (平面直角坐标系,y轴原点在下)
    float fRectSizeInMap = fBigRectSize * m_PixelPerRealDis;
    float fXBegin = m_rcDes.left + m_xPixelOffset * m_PixelPerRealDis;
    float fXEnd = m_rcDes.left + ( fMapWidth + m_xPixelOffset ) * m_PixelPerRealDis;
    float fYBegin = m_rcDes.bottom - m_yPixelOffset * m_PixelPerRealDis;
    float fYEnd = m_rcDes.bottom - ( fMapLength + m_yPixelOffset ) * m_PixelPerRealDis;

    // 画田
    for( int i = 0; i <= nBigRectRCount; ++i )
    {
        float fX = fXBegin + i * fRectSizeInMap;
        GetDrawer()->DrawLine2D( fX, fYBegin, fX, fYEnd, 0xffffff00 );
    }
    for( int i = 0; i <= nBigRectVCount; ++i )
    {
        float fY = fYBegin - i * fRectSizeInMap;
        GetDrawer()->DrawLine2D( fXBegin, fY, fXEnd, fY, 0xffffff00 );
    }

    GetDrawer()->DrawLine2D( fXBegin, fYEnd, fXEnd, fYEnd, 0xffffff00 );
    GetDrawer()->DrawLine2D( fXEnd, fYBegin, fXEnd, fYEnd, 0xffffff00 );

    // 画自己所在的方格
    float fXMeBegin = fXBegin + nMeRIndex * fRectSizeInMap;
    float fXMeEnd = ( nMeRIndex == nBigRectRCount ) ? fXEnd : ( fXMeBegin + fRectSizeInMap );
    float fYMeBegin = fYBegin - nMeVIndex * fRectSizeInMap;
    float fYMeEnd = ( nMeVIndex == nBigRectVCount ) ? fYEnd : ( fYMeBegin - fRectSizeInMap );
    GetDrawer()->DrawLine2D( fXMeBegin, fYMeBegin, fXMeEnd, fYMeBegin, 0xffff00ff );
    GetDrawer()->DrawLine2D( fXMeBegin, fYMeEnd, fXMeEnd, fYMeEnd, 0xffff00ff );
    GetDrawer()->DrawLine2D( fXMeBegin, fYMeBegin, fXMeBegin, fYMeEnd, 0xffff00ff );
    GetDrawer()->DrawLine2D( fXMeEnd, fYMeBegin, fXMeEnd, fYMeEnd, 0xffff00ff );

    return true;
}
