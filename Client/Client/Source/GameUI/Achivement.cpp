/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Achivement.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Achivement.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "Core/Name.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "MeUI/ExpressionManager.h"
#include "ShowScreenText.h"
#include "color_config.h"
#include "IconManagerClient.h"
#include "Common.h"
#include "AchieveConfig.h"
#include "GameDefinePlayer.h"
#include "AchieveFinish.h"
#include "MeUi/Animation/XmlAnimation.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "ScreenInfoManager.h"
#include "MainMenu.h"
CUI_ID_FRAME_Achivement s_CUI_ID_FRAME_Achivement;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Achivement, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Achivement, OnFrameRender )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Achivement, OnFrameRenderNeedRedraw )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_Caption1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_Caption2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_Caption4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_Caption3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_Caption5OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_5OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_6OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_7OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_8OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_9OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_CHECKBOX_10OnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_BUTTON_PullDownOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon0OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon0OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon0OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon0OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_BUTTON_Award0OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_BUTTON_LeftHeadOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_BUTTON_RightHeadOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Icon2OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_BUTTON_Award1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_BUTTON_Award2OnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award0OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award0OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award0OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award0OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_LISTIMG_Award2OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Achivement, ID_BUTTON_Award3OnButtonClick )

static int IntCmp(const void* a,const void* b)
{
	return *((int*)a) - *((int*)b);
}

CUI_ID_FRAME_Achivement::CUI_ID_FRAME_Achivement()
{
	for(int nIndex = 0; nIndex < m_nUIAchItem; ++nIndex)
	{
		m_pCoolDownAni[nIndex] = NULL;
		m_ShowBeginTime[nIndex] = 0;
	}
	// Member
	UIReset();
	m_bInitialize = false;
	m_FilterInitialize = false;
	memset(achieveVars,0,sizeof(uint32)*More_iMaxAchieveVars);
}
// Frame
bool CUI_ID_FRAME_Achivement::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	if( IsVisable() )
	{
		if (m_bDirty)
		{
			m_bDirty = false;
			RefreshItemPage();
			RefreshOther();
		}
		else
		{
			for (int nIndex = 0; nIndex < m_nUIAchItem; ++nIndex)
			{
				if (m_ShowBeginTime[nIndex] != 0)
				{
					if (m_pCoolDownAni[nIndex] != NULL)
					{
						if (!m_pCoolDownAni[nIndex]->IsInAnimation())
						{
							m_ShowBeginTime[nIndex] = 0;
						}					
					}				
				}			
			}
		}		
	}
	return true;
}
bool CUI_ID_FRAME_Achivement::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_Caption1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetTitleSelected(0);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_Caption2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetTitleSelected(1);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_Caption4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetTitleSelected(3);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_Caption3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetTitleSelected(2);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_Caption5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetTitleSelected(4);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetChildSelected(1);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetChildSelected(2);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetChildSelected(3);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetChildSelected(4);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetChildSelected(5);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_7OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetChildSelected(6);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_8OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetChildSelected(7);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetChildSelected(0);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_9OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetChildSelected(8);
}
// CheckBox
void CUI_ID_FRAME_Achivement::ID_CHECKBOX_10OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	SetChildSelected(9);
}
// Button
bool CUI_ID_FRAME_Achivement::ID_BUTTON_PullDownOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	bool bExist = false;
	for(int i = 0; i < MAX_ACHIVEVMENT_COUNT; ++i)
	{
		if(xAchievements[i].finishState == ECS_Finished)
		{
			bExist = true;
			SendAchieveReward(i);
		}
	}
	if(!bExist)
	    CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Achievement_Failed,theXmlString.GetString(eText_NoAchievementFinish));
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon0OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_Achivement::ID_BUTTON_Award0OnButtonClick( ControlObject* pSender )
{
	SendAchieveReward(m_CurrentItemArr[m_nCurrentPage*m_nUIAchItem + 0]);

	return true;
}
// Button
bool CUI_ID_FRAME_Achivement::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	if (m_nCurrentPage > 0)
	{
		--m_nCurrentPage;
		StopAwardEffect();
		RefreshItemPage();
	}
	
	return true;
}
// Button
bool CUI_ID_FRAME_Achivement::ID_BUTTON_LeftHeadOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	if (m_nCurrentPage > 0)
	{
		m_nCurrentPage = 0;
		StopAwardEffect();
		RefreshItemPage();
	}
	return true;
}
// Button
bool CUI_ID_FRAME_Achivement::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	if (m_nCurrentPage  < m_nTotalPage - 1)
	{
		++m_nCurrentPage ;
		StopAwardEffect();
		RefreshItemPage();
	}
	return true;
}
// Button
bool CUI_ID_FRAME_Achivement::ID_BUTTON_RightHeadOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	if (m_nCurrentPage  < m_nTotalPage - 1)
	{
		m_nCurrentPage = m_nTotalPage - 1;
		StopAwardEffect();
		RefreshItemPage();
	}
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Icon2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_Achivement::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Achivement::ID_BUTTON_Award1OnButtonClick( ControlObject* pSender )
{
	SendAchieveReward(m_CurrentItemArr[m_nCurrentPage*m_nUIAchItem + 1]);
	return true;
}
// Button
bool CUI_ID_FRAME_Achivement::ID_BUTTON_Award2OnButtonClick( ControlObject* pSender )
{
	SendAchieveReward(m_CurrentItemArr[m_nCurrentPage*m_nUIAchItem + 2]);
	return true;
}
// Button
bool CUI_ID_FRAME_Achivement::ID_BUTTON_Award3OnButtonClick( ControlObject* pSender )
{
	SendAchieveReward(m_CurrentItemArr[m_nCurrentPage*m_nUIAchItem + 3]);
	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award0OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}
bool CUI_ID_FRAME_Achivement::ID_LISTIMG_Award2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return false;
}

// 装载UI
bool CUI_ID_FRAME_Achivement::_LoadUI()
{

	InitializeFilter();
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Achivement.MEUI" , false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Achivement.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Achivement::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Achivement, s_CUI_ID_FRAME_AchivementOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Achivement, s_CUI_ID_FRAME_AchivementOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_Caption1, s_CUI_ID_FRAME_AchivementID_CHECKBOX_Caption1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_Caption2, s_CUI_ID_FRAME_AchivementID_CHECKBOX_Caption2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_Caption4, s_CUI_ID_FRAME_AchivementID_CHECKBOX_Caption4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_Caption3, s_CUI_ID_FRAME_AchivementID_CHECKBOX_Caption3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_Caption5, s_CUI_ID_FRAME_AchivementID_CHECKBOX_Caption5OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_2, s_CUI_ID_FRAME_AchivementID_CHECKBOX_2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_3, s_CUI_ID_FRAME_AchivementID_CHECKBOX_3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_4, s_CUI_ID_FRAME_AchivementID_CHECKBOX_4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_5, s_CUI_ID_FRAME_AchivementID_CHECKBOX_5OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_6, s_CUI_ID_FRAME_AchivementID_CHECKBOX_6OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_7, s_CUI_ID_FRAME_AchivementID_CHECKBOX_7OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_8, s_CUI_ID_FRAME_AchivementID_CHECKBOX_8OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_1, s_CUI_ID_FRAME_AchivementID_CHECKBOX_1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_9, s_CUI_ID_FRAME_AchivementID_CHECKBOX_9OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Achivement, ID_CHECKBOX_10, s_CUI_ID_FRAME_AchivementID_CHECKBOX_10OnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Achivement, ID_BUTTON_PullDown, s_CUI_ID_FRAME_AchivementID_BUTTON_PullDownOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Achivement, ID_LISTIMG_Icon0, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon0OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Achivement, ID_LISTIMG_Icon0, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon0OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Achivement, ID_LISTIMG_Icon0, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon0OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Achivement, ID_LISTIMG_Icon0, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon0OnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Achivement, ID_BUTTON_Award0, s_CUI_ID_FRAME_AchivementID_BUTTON_Award0OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Achivement, ID_BUTTON_Left, s_CUI_ID_FRAME_AchivementID_BUTTON_LeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Achivement, ID_BUTTON_LeftHead, s_CUI_ID_FRAME_AchivementID_BUTTON_LeftHeadOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Achivement, ID_BUTTON_Right, s_CUI_ID_FRAME_AchivementID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Achivement, ID_BUTTON_RightHead, s_CUI_ID_FRAME_AchivementID_BUTTON_RightHeadOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Achivement, ID_LISTIMG_Icon1, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Achivement, ID_LISTIMG_Icon1, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Achivement, ID_LISTIMG_Icon1, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Achivement, ID_LISTIMG_Icon1, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Achivement, ID_LISTIMG_Icon2, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Achivement, ID_LISTIMG_Icon2, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Achivement, ID_LISTIMG_Icon2, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Achivement, ID_LISTIMG_Icon2, s_CUI_ID_FRAME_AchivementID_LISTIMG_Icon2OnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Achivement, ID_BUTTON_HELP, s_CUI_ID_FRAME_AchivementID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Achivement, ID_BUTTON_Award1, s_CUI_ID_FRAME_AchivementID_BUTTON_Award1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Achivement, ID_BUTTON_Award2, s_CUI_ID_FRAME_AchivementID_BUTTON_Award2OnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Achivement, ID_LISTIMG_Award0, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award0OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Achivement, ID_LISTIMG_Award0, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award0OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Achivement, ID_LISTIMG_Award0, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award0OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Achivement, ID_LISTIMG_Award0, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award0OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Achivement, ID_LISTIMG_Award1, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Achivement, ID_LISTIMG_Award1, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Achivement, ID_LISTIMG_Award1, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Achivement, ID_LISTIMG_Award1, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Achivement, ID_LISTIMG_Award2, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Achivement, ID_LISTIMG_Award2, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Achivement, ID_LISTIMG_Award2, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Achivement, ID_LISTIMG_Award2, s_CUI_ID_FRAME_AchivementID_LISTIMG_Award2OnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Achivement, ID_BUTTON_Award3, s_CUI_ID_FRAME_AchivementID_BUTTON_Award3OnButtonClick );

	m_pID_FRAME_Achivement = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Achivement );
	m_pID_PICTURE_BgGrey[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_BgGrey0 );
	m_pID_PICTURE_BgLight[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_BgLight0 );
	m_pID_PICTURE_BgGrey[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_BgGrey1 );
	m_pID_PICTURE_BgGrey[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_BgGrey2 );
	m_pID_PICTURE_BgLight[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_BgLight1 );
	m_pID_PICTURE_BgLight[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_BgLight2 );
	m_pID_CHECKBOX_Caption[0] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_Caption1 );
	m_pID_CHECKBOX_Caption[1] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_Caption2 );
	m_pID_CHECKBOX_Caption[3] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_Caption4 );
	m_pID_CHECKBOX_Caption[2] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_Caption3 );
	m_pID_CHECKBOX_Caption[4] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_Caption5 );
	m_pID_CHECKBOX_Child[1] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_2 );
	m_pID_CHECKBOX_Child[2] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_3 );
	m_pID_CHECKBOX_Child[3] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_4 );
	m_pID_CHECKBOX_Child[4] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_5 );
	m_pID_CHECKBOX_Child[5] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_6 );
	m_pID_CHECKBOX_Child[6] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_7 );
	m_pID_CHECKBOX_Child[7] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_8 );
	m_pID_CHECKBOX_Child[0] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_1 );
	m_pID_CHECKBOX_Child[8] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_9 );
	m_pID_CHECKBOX_Child[9] = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Achivement, ID_CHECKBOX_10 );
	m_pID_TEXT_AchivementTopLeft1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_AchivementTopLeft1 );
	m_pID_BUTTON_PullDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achivement, ID_BUTTON_PullDown );
	m_pID_TEXT_AchivementLeftDown = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_AchivementLeftDown );
	m_pID_TEXT_AchivementLeftRightDown1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_AchivementLeftRightDown1 );
	m_pID_TEXT_Top[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Top0 );
	m_pID_TEXT_Date[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Data0 );
	m_pID_TEXT_Content[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Content0 );
	m_pID_LISTIMG_Icon[0] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Achivement, ID_LISTIMG_Icon0 );
	m_pID_BUTTON_Award[0] = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achivement, ID_BUTTON_Award0 );
	m_pID_TEXT_AchivementNumber[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_AchivementNumber0 );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Page );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achivement, ID_BUTTON_Left );
	m_pID_BUTTON_LeftHead = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achivement, ID_BUTTON_LeftHead );
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achivement, ID_BUTTON_Right );
	m_pID_BUTTON_RightHead = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achivement, ID_BUTTON_RightHead );
	m_pID_TEXT_Top[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Top1 );
	m_pID_PROGRESS_Plan[1] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PROGRESS_Plan1 );
	m_pID_TEXT_Number[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Number1 );
	m_pID_TEXT_Number[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Number2 );
	m_pID_TEXT_Number[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Number0 );
	m_pID_TEXT_Number[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Number3 );
	m_pID_TEXT_Nothing[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Nothing1 );
	m_pID_TEXT_Nothing[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Nothing2 );
	m_pID_TEXT_Nothing[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Nothing0 );
	m_pID_TEXT_Nothing[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Nothing3 );
	m_pID_LISTIMG_Icon[1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Achivement, ID_LISTIMG_Icon1 );
	m_pID_TEXT_Content[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Content1 );
	m_pID_TEXT_Top[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Top2 );
	m_pID_LISTIMG_Icon[2] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Achivement, ID_LISTIMG_Icon2 );
	m_pID_TEXT_Content[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Content2 );
	m_pID_PROGRESS_Plan[2] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PROGRESS_Plan2 );
	m_pID_PROGRESS_Plan[0] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PROGRESS_Plan0 );
	m_pID_TEXT_Date[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Data1 );
	m_pID_TEXT_Date[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Data2 );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achivement, ID_BUTTON_HELP );
	m_pID_TEXT_AchivementNumber[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_AchivementNumber1 );
	m_pID_TEXT_AchivementNumber[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_AchivementNumber2 );
	m_pID_BUTTON_Award[1] = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achivement, ID_BUTTON_Award1 );
	m_pID_BUTTON_Award[2] = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achivement, ID_BUTTON_Award2 );
	m_pID_PICTURE_Caption[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Caption1 );
	m_pID_PICTURE_Caption[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Caption2 );
	m_pID_PICTURE_Caption[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Caption3 );
	m_pID_PICTURE_Caption[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Caption4 );
	m_pID_PICTURE_Caption[4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Caption5 );
	m_pID_LISTIMG_Award[0] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Achivement, ID_LISTIMG_Award0 );
	m_pID_LISTIMG_Award[1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Achivement, ID_LISTIMG_Award1 );
	m_pID_LISTIMG_Award[2] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Achivement, ID_LISTIMG_Award2 );
	m_pID_PICTURE_AchivementComplete[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_AchivementComplete0 );
	m_pID_PICTURE_AchivementComplete[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_AchivementComplete1 );
	m_pID_PICTURE_AchivementComplete[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_AchivementComplete2 );
	m_pID_PICTURE_AchivementComplete[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_AchivementComplete3 );
	m_pID_PICTURE_Already[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Already0 );
	m_pID_PICTURE_Already[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Already1 );
	m_pID_PICTURE_Already[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Already2 );
	m_pID_PICTURE_Already[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Already3 );
	m_pID_PICTURE_BgLight[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_BgLight3 );
	m_pID_PICTURE_BgGrey[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_BgGrey3 );
	m_pID_PROGRESS_Plan[3] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PROGRESS_Plan3 );
	m_pID_TEXT_Top[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Top3 );
	m_pID_TEXT_Content[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Content3 );
	m_pID_BUTTON_Award[3] = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achivement, ID_BUTTON_Award3 );
	m_pID_TEXT_AchivementNumber[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_AchivementNumber3 );
	m_pID_LISTIMG_Award[3] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Achivement, ID_LISTIMG_Award3 );
	m_pID_LISTIMG_Icon[3] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Achivement, ID_LISTIMG_Icon3 );
	m_pID_TEXT_Date[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_Data3 );
	m_pID_TEXT_TopGrey[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_TopGrey0 );
	m_pID_TEXT_TopGrey[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_TopGrey1 );
	m_pID_TEXT_TopGrey[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_TopGrey2 );
	m_pID_TEXT_TopGrey[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_Achivement, ID_TEXT_TopGrey3 );

	m_pID_PICTURE_Case[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Case0 );
	m_pID_PICTURE_Case[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Case1 );
	m_pID_PICTURE_Case[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Case2 );
	m_pID_PICTURE_Case[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_Case3 );

	m_pID_PROGRESS_Award[0] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PROGRESS_Award0 );
	m_pID_PROGRESS_Award[1] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PROGRESS_Award1 );
	m_pID_PROGRESS_Award[2] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PROGRESS_Award2 );
	m_pID_PROGRESS_Award[3] = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PROGRESS_Award3 );

	m_pID_PICTURE_AwardEffect[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_AwardEffect0 );
	m_pID_PICTURE_AwardEffect[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_AwardEffect1 );
	m_pID_PICTURE_AwardEffect[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_AwardEffect2 );
	m_pID_PICTURE_AwardEffect[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achivement, ID_PICTURE_AwardEffect3 );

	assert( m_pID_FRAME_Achivement );
	assert( m_pID_PICTURE_BgGrey[0] );
	assert( m_pID_PICTURE_BgLight[0] );
	assert( m_pID_PICTURE_BgGrey[1] );
	assert( m_pID_PICTURE_BgGrey[2] );
	assert( m_pID_PICTURE_BgLight[1] );
	assert( m_pID_PICTURE_BgLight[2] );
	assert( m_pID_CHECKBOX_Caption[1] );
	assert( m_pID_CHECKBOX_Caption[2] );
	assert( m_pID_CHECKBOX_Caption[3] );
	assert( m_pID_CHECKBOX_Caption[4] );
	assert( m_pID_CHECKBOX_Caption[0] );
	assert( m_pID_CHECKBOX_Child[2] );
	assert( m_pID_CHECKBOX_Child[3] );
	assert( m_pID_CHECKBOX_Child[4] );
	assert( m_pID_CHECKBOX_Child[5] );
	assert( m_pID_CHECKBOX_Child[6] );
	assert( m_pID_CHECKBOX_Child[7] );
	assert( m_pID_CHECKBOX_Child[8] );
	assert( m_pID_CHECKBOX_Child[1] );
	assert( m_pID_CHECKBOX_Child[9] );
	assert( m_pID_CHECKBOX_Child[0] );
	assert( m_pID_TEXT_AchivementTopLeft1 );
	assert( m_pID_BUTTON_PullDown );
	assert( m_pID_TEXT_AchivementLeftDown );
	assert( m_pID_TEXT_AchivementLeftRightDown1 );
	assert( m_pID_TEXT_Top[0] );
	assert( m_pID_TEXT_Date[0] );
	assert( m_pID_TEXT_Content[0] );
	assert( m_pID_LISTIMG_Icon[0] );
	assert( m_pID_BUTTON_Award[0] );
	assert( m_pID_TEXT_AchivementNumber[0] );
	assert( m_pID_TEXT_Page );
	assert( m_pID_BUTTON_Left );
	assert( m_pID_BUTTON_LeftHead );
	assert( m_pID_BUTTON_Right );
	assert( m_pID_BUTTON_RightHead );
	assert( m_pID_TEXT_Top[1] );
	assert( m_pID_PROGRESS_Plan[1] );
	assert( m_pID_TEXT_Number[1] );
	assert( m_pID_LISTIMG_Icon[1] );
	assert( m_pID_TEXT_Content[1] );
	assert( m_pID_TEXT_Top[2] );
	assert( m_pID_LISTIMG_Icon[2] );
	assert( m_pID_TEXT_Content[2] );
	assert( m_pID_TEXT_Number[2] );
	assert( m_pID_PROGRESS_Plan[2] );
	assert( m_pID_PROGRESS_Plan[0] );
	assert( m_pID_TEXT_Number[0] );
	assert( m_pID_TEXT_Date[1] );
	assert( m_pID_TEXT_Date[2] );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_TEXT_AchivementNumber[1] );
	assert( m_pID_TEXT_AchivementNumber[2] );
	assert( m_pID_BUTTON_Award[1] );
	assert( m_pID_BUTTON_Award[2] );
	assert( m_pID_PICTURE_Caption[1] );
	assert( m_pID_PICTURE_Caption[2] );
	assert( m_pID_PICTURE_Caption[3] );
	assert( m_pID_PICTURE_Caption[4] );
	assert( m_pID_PICTURE_Caption[0] );
	assert( m_pID_LISTIMG_Award[0] );
	assert( m_pID_LISTIMG_Award[1] );
	assert( m_pID_LISTIMG_Award[2] );
	assert( m_pID_PICTURE_AchivementComplete[0] );
	assert( m_pID_PICTURE_AchivementComplete[1] );
	assert( m_pID_PICTURE_AchivementComplete[2] );
	assert( m_pID_PICTURE_AchivementComplete[3] );
	assert( m_pID_PICTURE_Already[0] );
	assert( m_pID_PICTURE_Already[1] );
	assert( m_pID_PICTURE_Already[2] );
	assert( m_pID_PICTURE_Already[3] );
	assert( m_pID_PICTURE_BgLight[3] );
	assert( m_pID_PICTURE_BgGrey[3] );
	assert( m_pID_PROGRESS_Plan[3] );
	assert( m_pID_TEXT_Top[3] );
	assert( m_pID_TEXT_Content[3] );
	assert( m_pID_BUTTON_Award[3] );
	assert( m_pID_TEXT_AchivementNumber[3] );
	assert( m_pID_LISTIMG_Award[3] );
	assert( m_pID_LISTIMG_Icon[3] );
	assert( m_pID_TEXT_Number[3] );
	assert( m_pID_TEXT_Date[3] );
	assert( m_pID_TEXT_TopGrey[0] );
	assert( m_pID_TEXT_TopGrey[1] );
	assert( m_pID_TEXT_TopGrey[2] );
	assert( m_pID_TEXT_TopGrey[3] );

	assert( m_pID_PICTURE_Case[0] );
	assert( m_pID_PICTURE_Case[1] );
	assert( m_pID_PICTURE_Case[2] );
	assert( m_pID_PICTURE_Case[3] );

	assert( m_pID_PROGRESS_Award[0] );
	assert( m_pID_PROGRESS_Award[1] );
	assert( m_pID_PROGRESS_Award[2] );
	assert( m_pID_PROGRESS_Award[3] );

	assert( m_pID_PICTURE_AwardEffect[0] );
	assert( m_pID_PICTURE_AwardEffect[1] );
	assert( m_pID_PICTURE_AwardEffect[2] );
	assert( m_pID_PICTURE_AwardEffect[3] );

	SetVisable(false);
	for (int i = 0; i < m_nUIChildTitle; ++i)
	{
		RECT rcFrame = {526,797,651,821};
		RECT rcInner = {536,807,641,811};
		/*
		 * Author: 2012-9-27 18:04:13 liaojie
		 * Desc:   先注释掉
		 */
 		//m_pID_CHECKBOX_Child[i]->SetMoveOnPic("Common/UIAchivement.dds",&rcFrame,&rcFrame);
	}
	
	for(int i = 0; i < m_nUIAchItem; ++i)
	{
		m_pID_LISTIMG_Icon[i]->SetEnableDrag(false);
		m_pID_LISTIMG_Award[i]->SetEnableDrag(false);
	}
	SetDirty();
	SetTitleSelected(0);
    CreateProgressAni();

	m_pID_FRAME_Achivement->SetRenderNeedRedraw(s_CUI_ID_FRAME_AchivementOnFrameRenderNeedRedraw);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Achivement::_UnLoadUI()
{
	UIReset();

	return theUiManager.RemoveFrame( "Data\\UI\\Achivement.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Achivement::_IsVisable()
{
	if ( !m_pID_FRAME_Achivement )
		return false;
	return m_pID_FRAME_Achivement->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Achivement::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Achivement )
		return;
	m_pID_FRAME_Achivement->SetVisable( bVisable);
	if (bVisable /*&& !m_bInitialize*/)
	{
		MsgReqAchieveData msgAchieveData;
		GettheNetworkInput().SendMsg( &msgAchieveData );
	}

	if (bVisable)
	{
		s_CUI_ID_FRAME_MainMenu.SetNeedSpark(false, CUI_ID_FRAME_MainMenu::ekey_achivement);
	}
}

void CUI_ID_FRAME_Achivement::UIReset()
{
	m_pID_FRAME_Achivement = NULL;
	m_pID_PICTURE_BgGrey[0] = NULL;
	m_pID_PICTURE_BgLight[0] = NULL;
	m_pID_PICTURE_BgGrey[1] = NULL;
	m_pID_PICTURE_BgGrey[2] = NULL;
	m_pID_PICTURE_BgLight[1] = NULL;
	m_pID_PICTURE_BgLight[2] = NULL;
	m_pID_CHECKBOX_Caption[1] = NULL;
	m_pID_CHECKBOX_Caption[2] = NULL;
	m_pID_CHECKBOX_Caption[3] = NULL;
	m_pID_CHECKBOX_Caption[4] = NULL;
	m_pID_CHECKBOX_Caption[0] = NULL;
	m_pID_CHECKBOX_Child[2] = NULL;
	m_pID_CHECKBOX_Child[3] = NULL;
	m_pID_CHECKBOX_Child[4] = NULL;
	m_pID_CHECKBOX_Child[5] = NULL;
	m_pID_CHECKBOX_Child[6] = NULL;
	m_pID_CHECKBOX_Child[7] = NULL;
	m_pID_CHECKBOX_Child[8] = NULL;
	m_pID_CHECKBOX_Child[1] = NULL;
	m_pID_CHECKBOX_Child[9] = NULL;
	m_pID_CHECKBOX_Child[0] = NULL;
	m_pID_TEXT_AchivementTopLeft1 = NULL;
	m_pID_BUTTON_PullDown = NULL;
	m_pID_TEXT_AchivementLeftDown = NULL;
	m_pID_TEXT_AchivementLeftRightDown1 = NULL;
	m_pID_TEXT_Top[0] = NULL;
	m_pID_TEXT_Date[0] = NULL;
	m_pID_TEXT_Content[0] = NULL;
	m_pID_LISTIMG_Icon[0] = NULL;
	m_pID_BUTTON_Award[0] = NULL;
	m_pID_TEXT_AchivementNumber[0] = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_BUTTON_LeftHead = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_RightHead = NULL;
	m_pID_TEXT_Top[1] = NULL;
	m_pID_PROGRESS_Plan[1] = NULL;
	m_pID_TEXT_Number[1] = NULL;
	m_pID_LISTIMG_Icon[1] = NULL;
	m_pID_TEXT_Content[1] = NULL;
	m_pID_TEXT_Top[2] = NULL;
	m_pID_LISTIMG_Icon[2] = NULL;
	m_pID_TEXT_Content[2] = NULL;
	m_pID_TEXT_Number[2] = NULL;
	m_pID_PROGRESS_Plan[2] = NULL;
	m_pID_PROGRESS_Plan[0] = NULL;
	m_pID_TEXT_Number[0] = NULL;
	m_pID_TEXT_Date[1] = NULL;
	m_pID_TEXT_Date[2] = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_TEXT_AchivementNumber[1] = NULL;
	m_pID_TEXT_AchivementNumber[2] = NULL;
	m_pID_BUTTON_Award[1] = NULL;
	m_pID_BUTTON_Award[2] = NULL;
	m_pID_PICTURE_Caption[1] = NULL;
	m_pID_PICTURE_Caption[2] = NULL;
	m_pID_PICTURE_Caption[3] = NULL;
	m_pID_PICTURE_Caption[4] = NULL;
	m_pID_PICTURE_Caption[0] = NULL;
	m_pID_LISTIMG_Award[0] = NULL;
	m_pID_LISTIMG_Award[1] = NULL;
	m_pID_LISTIMG_Award[2] = NULL;
	m_pID_PICTURE_AchivementComplete[0] = NULL;
	m_pID_PICTURE_AchivementComplete[1] = NULL;
	m_pID_PICTURE_AchivementComplete[2] = NULL;
	m_pID_PICTURE_AchivementComplete[3] = NULL;
	m_pID_PICTURE_Already[0] = NULL;
	m_pID_PICTURE_Already[1] = NULL;
	m_pID_PICTURE_Already[2] = NULL;
	m_pID_PICTURE_Already[3] = NULL;
	m_pID_PICTURE_BgLight[3] = NULL;
	m_pID_PICTURE_BgGrey[3] = NULL;
	m_pID_PROGRESS_Plan[3] = NULL;
	m_pID_TEXT_Top[3] = NULL;
	m_pID_TEXT_Content[3] = NULL;
	m_pID_BUTTON_Award[3] = NULL;
	m_pID_TEXT_AchivementNumber[3] = NULL;
	m_pID_LISTIMG_Award[3] = NULL;
	m_pID_LISTIMG_Icon[3] = NULL;
	m_pID_TEXT_Number[3] = NULL;
	m_pID_TEXT_Date[3] = NULL;
	m_pID_TEXT_TopGrey[0] = NULL;
	m_pID_TEXT_TopGrey[1] = NULL;
	m_pID_TEXT_TopGrey[2] = NULL;
	m_pID_TEXT_TopGrey[3] = NULL;

	m_nTitleIndex	= 0;
	m_nChildIndex	= -1;
	m_nTotalPage	= 0;
	m_nCurrentPage	= 0;
	m_bDirty		= false;
	for(int nIndex = 0; nIndex < m_nUIAchItem; ++nIndex)
	{
		if (m_pCoolDownAni[nIndex])
		{
			delete m_pCoolDownAni[nIndex];
			m_pCoolDownAni[nIndex] = NULL;
		}		
		m_ShowBeginTime[nIndex] = 0;
	}
	achievePoint = 0;
}

void CUI_ID_FRAME_Achivement::IntializeAchievements( SAchieveData& AchieveData )
{
	m_bInitialize = true;
	achievePoint = AchieveData.achievePoint;
	memcpy_s(achieveVars,sizeof(achieveVars),AchieveData.achieveVars,sizeof(uint32)*More_iMaxAchieveVars);
	memcpy_s(xAchievements,sizeof(xAchievements),AchieveData.xAchievements,sizeof(SCharAchieve)*MAX_ACHIVEVMENT_COUNT);
	SetDirty();
}


void CUI_ID_FRAME_Achivement::InitializeFilter()
{
	if (!m_FilterInitialize)
	{
		m_FilterInitialize = true;
		const std::vector<AchieveConfig::Achieve>& AchieveList = theAchieveConfig.GetAchieveList();
		for (int i = 0; i < AchieveList.size(); ++i)
		{
			AchieveConfig::Achieve* pAchieve = theAchieveConfig.GetAchieve(i);
			if (pAchieve)
			{
				m_AchievementFilter[pAchieve->GetType() - 1][pAchieve->GetSubType() - 1].push_back(i);
			}			
		}
		memset(m_nChildTotal,0, sizeof(int)*m_nUITitleNumber);
		for (int i = 0;i < m_nUITitleNumber; ++i)
		{
			for(int j = 0; j < m_nUIChildTitle; ++j)
			{
				if (m_AchievementFilter[i][j].size() != 0)
				{
					++m_nChildTotal[i];
				}				
			}
		}
		
		
	}
	
}

void CUI_ID_FRAME_Achivement::SetTitleSelected(int nIndex,int nChildIndex)
{
	m_nTitleIndex = nIndex;

	for(int i = 0; i< m_nUITitleNumber; ++i)
	{
		if (i == nIndex)
		{
			m_pID_CHECKBOX_Caption[i]->SetCheck(true);
			m_pID_PICTURE_Caption[i]->SetVisable(true);
		}
		else
		{
			m_pID_CHECKBOX_Caption[i]->SetCheck(false);
			m_pID_PICTURE_Caption[i]->SetVisable(false);
		}		
	}

	int nChildNumber = m_nChildTotal[m_nTitleIndex];
	for(int i = 0; i< m_nUIChildTitle; ++i)
	{
		if (i < nChildNumber)
		{
			m_pID_CHECKBOX_Child[i]->SetVisable(true);
			AchieveConfig::Achieve* pAchieve = theAchieveConfig.GetAchieve(m_AchievementFilter[m_nTitleIndex][i][0]);
			assert(pAchieve);
			m_pID_CHECKBOX_Child[i]->SetCaption(pAchieve->GetSubName().c_str());
		}
		else
		{
			m_pID_CHECKBOX_Child[i]->SetVisable(false);
		}		
	}
	SetChildSelected(nChildIndex);
}

void CUI_ID_FRAME_Achivement::SetChildSelected( int nChildIndex )
{
	m_nChildIndex = nChildIndex;
	for(int i = 0; i< m_nUIChildTitle; ++i)
	{
		if (nChildIndex == i)
		{
			m_pID_CHECKBOX_Child[i]->SetCheck(true);
		}
		else
		{
			m_pID_CHECKBOX_Child[i]->SetCheck(false);
		}
	}
	m_CurrentItemArr.clear();
	if (nChildIndex == -1)
	{
		for(int j = 0; j < m_nUIChildTitle; ++j)
		{
			std::vector<int>& itemVec = m_AchievementFilter[m_nTitleIndex][j];
			/*
			 * Author: 2012-10-12 15:14:49 liaojie
			 * Desc:   按需求把完成的成就放到前面去
			 */
			int finishIndex = 0;
			int alreadyGetIndex = 0;
			for (int nItem = 0; nItem < itemVec.size(); ++nItem)
			{
				if (xAchievements[itemVec[nItem]].finishState == ECS_Finished )
				{
					m_CurrentItemArr.insert(m_CurrentItemArr.begin()+finishIndex,itemVec[nItem]);
					finishIndex++;
					alreadyGetIndex++;
				}
				else if (xAchievements[itemVec[nItem]].finishState == ECS_GetReward )
				{
					m_CurrentItemArr.insert(m_CurrentItemArr.begin()+alreadyGetIndex,itemVec[nItem]);
					alreadyGetIndex++;
				}
				else
				{
					m_CurrentItemArr.push_back(itemVec[nItem]);
				}
			}
			if (finishIndex>0)
			{
				qsort(&m_CurrentItemArr[0],finishIndex,sizeof(int),IntCmp);
			}
			if (alreadyGetIndex>finishIndex)
			{
				qsort(&m_CurrentItemArr[finishIndex],alreadyGetIndex-finishIndex,sizeof(int),IntCmp);
			}
			
		}
	}
	else
	{
		std::vector<int>& itemVec = m_AchievementFilter[m_nTitleIndex][m_nChildIndex];
		for (int nItem = 0; nItem < itemVec.size(); ++nItem)
		{
			m_CurrentItemArr.push_back(itemVec[nItem]);
		}			
	}
	m_nCurrentPage = 0;
	m_nTotalPage = m_CurrentItemArr.size()/m_nUIAchItem;
	if (m_CurrentItemArr.size()%m_nUIAchItem)
	{
		++m_nTotalPage;
	}
	
	StopAwardEffect();
	RefreshItemPage();
}

void CUI_ID_FRAME_Achivement::RefreshItemPage()
{
	RefreshPageControler();
	int nStartIndex = m_nCurrentPage*m_nUIAchItem;
	int nItemCount = min(m_nUIAchItem,m_CurrentItemArr.size() - nStartIndex);
	assert(nItemCount > 0);
	for(int i = 0; i < nItemCount; ++i)
	{
		int nAchieveIndex = m_CurrentItemArr[nStartIndex + i];
		AchieveConfig::Achieve* pAchieve = theAchieveConfig.GetAchieve(nAchieveIndex);
		assert(pAchieve);		

		m_pID_TEXT_Content[i]->SetVisable(true);
		m_pID_TEXT_Content[i]->SetText(pAchieve->GetDesc());

		m_pID_TEXT_AchivementNumber[i]->SetVisable(true);
		char cTemp[16] = {0};
		sprintf_s(cTemp,16,"%d",pAchieve->GetRewardPoint());

		m_pID_LISTIMG_Icon[i]->SetVisable(true);
		ControlIconDrag::S_ListImg ImgItem;
		ImgItem.SetData(pAchieve->GetIconID(),1,eIcon_Enable,false,eTipFlag_Event);
		m_pID_LISTIMG_Icon[i]->SetItem(&ImgItem,0);

		if (pAchieve->GetRewardItem() != 0)
		{
			m_pID_LISTIMG_Award[i]->SetVisable(true);
			m_pID_TEXT_Nothing[i]->SetVisable(false);
			ControlIconDrag::S_ListImg ImgAward;
			ImgAward.SetData(pAchieve->GetRewardItem(),1);
			m_pID_LISTIMG_Award[i]->SetItem(&ImgAward,0);
		}
		else
		{
			m_pID_LISTIMG_Award[i]->SetVisable(false);
			m_pID_TEXT_Nothing[i]->SetVisable(true);
		}
		
		m_pID_TEXT_Top[i]->SetVisable(false);
		m_pID_TEXT_TopGrey[i]->SetVisable(false);
		m_pID_PICTURE_BgGrey[i]->SetVisable(false);
		m_pID_PICTURE_BgLight[i]->SetVisable(false);
		m_pID_TEXT_Date[i]->SetVisable(false);
		m_pID_BUTTON_Award[i]->SetVisable(false);
		m_pID_PICTURE_AchivementComplete[i]->SetVisable(false);
		m_pID_PICTURE_Already[i]->SetVisable(false);
		m_pID_PROGRESS_Plan[i]->SetVisable(false);
		m_pID_TEXT_Number[i]->SetVisable(false);

		m_pID_PICTURE_Case[i]->SetVisable( false );
		m_pID_PROGRESS_Award[i]->SetVisable( false );

		if (xAchievements[nAchieveIndex].finishState == ECS_Unfinished)
		{
			m_pID_TEXT_AchivementNumber[i]->SetText(cTemp,Color_Config.getColor(CC_Achievement_Gray));
			m_pID_PICTURE_BgGrey[i]->SetVisable(true);
			m_pID_TEXT_TopGrey[i]->SetVisable(true);
			m_pID_TEXT_TopGrey[i]->SetText(pAchieve->GetName());
// 			if (pAchieve->GetShowProcess() > 1)
			{
				int nValue = 0;
				if (pAchieve->GetShowProcess() > 1 && (pAchieve->GetValueType() < More_iMaxAchieveVars))
				{
					nValue = achieveVars[pAchieve->GetValueType()];
				}						
				char cNumber[128]={0};
				sprintf_s(cNumber,128,"%d/%d",nValue,pAchieve->GetShowProcess());
				m_pID_TEXT_Number[i]->SetVisable(true);
				m_pID_TEXT_Number[i]->SetText(cNumber);

				m_pID_PROGRESS_Plan[i]->SetVisable(true);

				m_pID_PICTURE_Case[i]->SetVisable( true );

				int nProcessValue = 0;
				if (pAchieve->GetShowProcess() > 0)
				{
					nProcessValue = nValue*1000/pAchieve->GetShowProcess();
				}
				m_pID_PROGRESS_Plan[i]->SetValue(nProcessValue);
			}
			
		}
		else
		{
			m_pID_TEXT_AchivementNumber[i]->SetText(cTemp,Color_Config.getColor(CC_Achievement_OK));
			m_pID_TEXT_Top[i]->SetVisable(true);
			m_pID_TEXT_Top[i]->SetText(pAchieve->GetName());
			m_pID_PICTURE_BgLight[i]->SetVisable(true);
			m_pID_PICTURE_AchivementComplete[i]->SetVisable(true);
			m_pID_TEXT_Date[i]->SetVisable(true);
			tm finishTime;
			_localtime64_s(&finishTime, &xAchievements[nAchieveIndex].finishTime);
			char cDate[128];
			MeSprintf_s(cDate, sizeof(cDate)/sizeof(char) - 1, "%04d/%02d/%02d", finishTime.tm_year + 1900, finishTime.tm_mon + 1, finishTime.tm_mday);
			m_pID_TEXT_Date[i]->SetText(cDate);
			if (xAchievements[nAchieveIndex].finishState == ECS_Finished )
			{
				m_pID_BUTTON_Award[i]->SetVisable(true);
				m_pID_PROGRESS_Award[i]->SetVisable(true);
			}
			else
			{
				m_pID_PICTURE_Already[i]->SetVisable(true);
			}
		}
	}
	for (int i = nItemCount; i < m_nUIAchItem; ++i)
	{
		m_pID_PICTURE_BgGrey[i]->SetVisable(false);
		m_pID_PICTURE_BgLight[i]->SetVisable(false);
		m_pID_TEXT_Top[i]->SetVisable(false);
		m_pID_TEXT_Date[i]->SetVisable(false);
		m_pID_TEXT_Content[i]->SetVisable(false);
		m_pID_LISTIMG_Icon[i]->SetVisable(false);
		m_pID_BUTTON_Award[i]->SetVisable(false);
		m_pID_PROGRESS_Award[i]->SetVisable(true);
		m_pID_TEXT_AchivementNumber[i]->SetVisable(false);
		m_pID_PROGRESS_Plan[i]->SetVisable(false);
		m_pID_TEXT_Number[i]->SetVisable(false);
		m_pID_LISTIMG_Award[i]->SetVisable(false);
		m_pID_PICTURE_AchivementComplete[i]->SetVisable(false);
		m_pID_PICTURE_Already[i]->SetVisable(false);
		m_pID_TEXT_TopGrey[i]->SetVisable(false);
		m_pID_TEXT_Nothing[i]->SetVisable(false);

		m_pID_PICTURE_Case[i]->SetVisable( false );
	}	
}

void CUI_ID_FRAME_Achivement::RefreshPageControler()
{
	char cTemp[256] = {0};
	sprintf_s(cTemp,256,"%d/%d",m_nCurrentPage +1,m_nTotalPage);
	m_pID_TEXT_Page->SetText(cTemp);

	m_pID_BUTTON_Left->SetEnable(m_nCurrentPage != 0);
	m_pID_BUTTON_LeftHead->SetEnable(m_nCurrentPage != 0);
	m_pID_BUTTON_Right->SetEnable(m_nCurrentPage != m_nTotalPage -1);
	m_pID_BUTTON_RightHead->SetEnable(m_nCurrentPage != m_nTotalPage -1);

}

void CUI_ID_FRAME_Achivement::RefreshOther()
{
	char cTemp[16] = {0};
	sprintf_s(cTemp,16,"%d",achievePoint);
	m_pID_TEXT_AchivementLeftRightDown1->SetText(cTemp);
}

void CUI_ID_FRAME_Achivement::SendAchieveReward( int nIndex )
{
	MsgReqAchieveReward reward;
	reward.nIndex = nIndex;
	GettheNetworkInput().SendMsg( &reward );

}

void CUI_ID_FRAME_Achivement::ShowAchieve( int nAchieveIndex )
{
	SetVisable(true);
	AchieveConfig::Achieve* pAchieve = theAchieveConfig.GetAchieve(nAchieveIndex);
	assert(pAchieve);
	SetTitleSelected(pAchieve->GetType() - 1,pAchieve->GetSubType() - 1);
	for(int i = 0; i < m_CurrentItemArr.size();++i)
	{
		if (m_CurrentItemArr[i] == nAchieveIndex)
		{
			int nPage = i/m_nUIAchItem;
			if (nPage != m_nCurrentPage)
			{
				m_nCurrentPage = nPage;
				StopAwardEffect();
				RefreshItemPage();
			}
			break;
		}		
	}	
}

void CUI_ID_FRAME_Achivement::UpdateAchievement( uint16 nIndex,SCharAchieve& achieve )
{
	if (nIndex < MAX_ACHIVEVMENT_COUNT)
	{
		if (xAchievements[nIndex].finishState == ECS_Finished && achieve.finishState == ECS_GetReward)
		{
			PlayAwardEffect(nIndex);
		}
		
		xAchievements[nIndex].finishState =  achieve.finishState;
		xAchievements[nIndex].finishTime =  achieve.finishTime;
		SetDirty();
		if (achieve.finishState == ECS_Finished)
		{
			s_CUI_ID_FRAME_AchieveFinish.SetCurrAchieve(nIndex,xAchievements[nIndex].finishTime);
			s_CUI_ID_FRAME_AchieveFinish.SetVisable(true);
			s_CUI_ID_FRAME_MainMenu.CheckNeedSparkAchivement();
		}
		
	}
}

void CUI_ID_FRAME_Achivement::CreateProgressAni()
{
    if( !IsUILoad() )
        return;

    char fullname[MAX_PATH] = {0};
    MeSprintf_s( fullname, sizeof( fullname ) / sizeof( char ) - 1, "%s\\data\\ui\\UIAni\\AchieveProgress.2DAni", GetRootPath() );
    for( int i = 0; i < m_nUIAchItem; ++i )
    {
        m_pID_PROGRESS_Plan[i]->CreateAnimation( fullname );
    }
}

CSmartAnimation* CUI_ID_FRAME_Achivement::GetCoolDownAniNotNULL( int nIndex )
{
	if (NULL == m_pCoolDownAni[nIndex])
	{
		char fullname[MAX_PATH] = {0};
		MeSprintf_s(fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\ui\\UIAni\\Flower.2DAni", GetRootPath());

		m_pCoolDownAni[nIndex] = new CXmlAnimation( m_pID_FRAME_Achivement->GetFrameRender() );
		MeXmlDocument doc;
		if(!doc.LoadFile(fullname))
		{
			assert(0);
			return m_pCoolDownAni[nIndex];
		}
		MeXmlElement* pElement = doc.FirstChildElement("Flower");
		if (pElement)
		{
			CXmlAnimation* pSmart = (CXmlAnimation*)m_pCoolDownAni[nIndex];
			pSmart->Initialize(pElement);
		}

		RECT rcPlay;
		m_pID_PICTURE_AwardEffect[nIndex]->GetRealRect(&rcPlay);
		int nWidth = rcPlay.right -rcPlay.left;
		int nHeight = rcPlay.bottom - rcPlay.top;
		m_pCoolDownAni[nIndex]->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
		m_pCoolDownAni[nIndex]->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
		m_pCoolDownAni[nIndex]->InitializeFunctor( CSmartAnimation::EFunctorType_Width, nWidth, NULL );
		m_pCoolDownAni[nIndex]->InitializeFunctor( CSmartAnimation::EFunctorType_Height, nHeight, NULL );
	}
	return m_pCoolDownAni[nIndex];

}

void CUI_ID_FRAME_Achivement::ResetDevice()
{
	for (int nIndex = 0; nIndex < m_nUIAchItem; ++nIndex)
	{
		if(m_pCoolDownAni[nIndex] && m_pCoolDownAni[nIndex]->GetD3DTexture() )
		{
			RECT rcPlay;
			m_pID_PICTURE_AwardEffect[nIndex]->GetRealRect(&rcPlay);
			int nWidth = rcPlay.right -rcPlay.left;
			int nHeight = rcPlay.bottom - rcPlay.top;
			m_pCoolDownAni[nIndex]->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
			m_pCoolDownAni[nIndex]->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
			m_pCoolDownAni[nIndex]->InitializeFunctor( CSmartAnimation::EFunctorType_Width, nWidth, NULL );
			m_pCoolDownAni[nIndex]->InitializeFunctor( CSmartAnimation::EFunctorType_Height, nHeight, NULL );
		}
	}	
}

bool CUI_ID_FRAME_Achivement::OnFrameRenderNeedRedraw()
{
	for (int nIndex = 0; nIndex < m_nUIAchItem; ++nIndex)
	{
		if (m_ShowBeginTime[nIndex] != 0)
		{
			DWORD dwCurTime = HQ_TimeGetTime();
			// 未创建动画则创建
			CSmartAnimation* coolDownAni = GetCoolDownAniNotNULL(nIndex);
			if( !coolDownAni->IsInAnimation() && coolDownAni->GetD3DTexture() )
			{
				RECT rcPlay;
				m_pID_PICTURE_AwardEffect[nIndex]->GetRealRect(&rcPlay);
				int nWidth = rcPlay.right -rcPlay.left;
				int nHeight = rcPlay.bottom - rcPlay.top;
				coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
				coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
				coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Width, nWidth, NULL );
				coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Height, nHeight, NULL );
				m_pID_FRAME_Achivement->GetUiAniManageNotNULL()->AddAnimation( coolDownAni );
				coolDownAni->StartAnimation( dwCurTime,dwCurTime - m_ShowBeginTime[nIndex], false );
			}
			else
			{
				coolDownAni->Redraw(dwCurTime);
			}
		}

	}
	return true;

}

void CUI_ID_FRAME_Achivement::PlayAwardEffect( int nAchivementIndex )
{
	int  nEffectIndex = -1;
	int nStartIndex = m_nCurrentPage*m_nUIAchItem;
	int nItemCount = min(m_nUIAchItem,m_CurrentItemArr.size() - nStartIndex);
	for (int nIndex = 0; nIndex < nItemCount; ++nIndex)
	{
		if (m_CurrentItemArr [m_nCurrentPage*m_nUIAchItem + nIndex] == nAchivementIndex)
		{
			nEffectIndex = nIndex;
			break;
		}		
	}
	if (nEffectIndex != -1)
	{
		m_ShowBeginTime[nEffectIndex] = HQ_TimeGetTime();
		m_pID_FRAME_Achivement->SetRedraw();
	}
		
}

void CUI_ID_FRAME_Achivement::StopAwardEffect()
{
	for (int nIndex = 0; nIndex < m_nUIAchItem; ++nIndex)
	{
		if (NULL != m_pCoolDownAni[nIndex])
		{
			m_pID_FRAME_Achivement->GetUiAniManageNotNULL()->StopAnimation(m_pCoolDownAni[nIndex]);
		}
	}
}

void CUI_ID_FRAME_Achivement::SetAchievePoint( uint32 nAchievePoint )
{
	if (achievePoint != nAchievePoint)
	{
		char buffer[256] = {0};
		MeSprintf_s(buffer,256,theXmlString.GetString( eText_GetAchievement ),nAchievePoint - achievePoint);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Achievement, buffer);
		achievePoint = nAchievePoint;
		SetDirty();
	}
	
}

