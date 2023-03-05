/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\AchieveFinish.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "AchieveFinish.h"
#include "Achivement.h"
#include "AchieveConfig.h"
#include "GameDefinePlayer.h"
#include "Cfg.h"
#include "Common.h"
#include "MeUi/Animation/XmlAnimation.h"
#include "MeUi/UiRender.h"
#include "Meaudio/MeAudio.h"

extern const char* GetRootPath();
extern HRSound GSound;

CUI_ID_FRAME_AchieveFinish s_CUI_ID_FRAME_AchieveFinish;
MAP_FRAME_RUN( s_CUI_ID_FRAME_AchieveFinish, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AchieveFinish, OnFrameRender )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AchieveFinish, OnFrameRenderNeedRedraw )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_AchieveFinish, ID_LISTIMG_Icon0OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_AchieveFinish, ID_LISTIMG_Icon0OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AchieveFinish, ID_LISTIMG_Icon0OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_AchieveFinish, ID_LISTIMG_Icon0OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_AchieveFinish, ID_LISTIMG_Award0OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_AchieveFinish, ID_LISTIMG_Award0OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AchieveFinish, ID_LISTIMG_Award0OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_AchieveFinish, ID_LISTIMG_Award0OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AchieveFinish, ID_BUTTON_Award0OnButtonClick )
CUI_ID_FRAME_AchieveFinish::CUI_ID_FRAME_AchieveFinish()
{
	// Member
	m_pID_FRAME_AchieveFinish = NULL;
	m_pID_LISTIMG_Icon0 = NULL;
	m_pID_TEXT_Number0 = NULL;
	m_pID_LISTIMG_Award0 = NULL;
	m_pID_TEXT_Content0 = NULL;
	m_pID_TEXT_Data0 = NULL;
	m_pID_BUTTON_Award0 = NULL;
	m_pID_PICTURE_AchivementComplete0 = NULL;
	m_pID_TEXT_Top0 = NULL;

	m_currAchieve = -1;
	m_ShowBeginTime = 0;
	m_UIShowBeginTime = 0;
	m_pCoolDownAni = NULL;
	m_bAnimationShowOnce = false;
}
// Frame
bool CUI_ID_FRAME_AchieveFinish::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	if( IsVisable() )
	{
		DWORD thisTime = HQ_TimeGetTime();
		/*if (m_ShowBeginTime == 0 )
		{
			if (m_pCoolDownAni == NULL || !m_pCoolDownAni->IsInAnimation())
			{
				if (m_bAnimationShowOnce && thisTime - m_UIShowBeginTime > gCfg.m_nAnimationDelayTime )
				{
					m_ShowBeginTime = thisTime;
					m_bAnimationShowOnce = false;
					m_pID_FRAME_AchieveFinish->SetRedraw();
				}			
			}
			
		}
		else
		{
			if (m_pCoolDownAni != NULL)
			{
				if (!m_pCoolDownAni->IsInAnimation())
				{
					m_ShowBeginTime = 0;
					m_pID_PICTURE_AchivementComplete0->SetVisable(true);
				}					
			}				
		}*/
		
		if (thisTime - m_UIShowBeginTime > gCfg.m_nAchievementFinishHoldTime)
		{
			SetVisable(false);
		}
	}
	return true;
}
bool CUI_ID_FRAME_AchieveFinish::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_AchieveFinish::ID_LISTIMG_Icon0OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_AchieveFinish )
		return false;
	return false;
}
bool CUI_ID_FRAME_AchieveFinish::ID_LISTIMG_Icon0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_AchieveFinish )
		return false;
	return false;
}
bool CUI_ID_FRAME_AchieveFinish::ID_LISTIMG_Icon0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_AchieveFinish )
		return false;
	return false;
}
bool CUI_ID_FRAME_AchieveFinish::ID_LISTIMG_Icon0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_AchieveFinish )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_AchieveFinish::ID_LISTIMG_Award0OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_AchieveFinish )
		return false;
	return false;
}
bool CUI_ID_FRAME_AchieveFinish::ID_LISTIMG_Award0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_AchieveFinish )
		return false;
	return false;
}
bool CUI_ID_FRAME_AchieveFinish::ID_LISTIMG_Award0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_AchieveFinish )
		return false;
	return false;
}
bool CUI_ID_FRAME_AchieveFinish::ID_LISTIMG_Award0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_AchieveFinish )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_AchieveFinish::ID_BUTTON_Award0OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_AchieveFinish )
		return false;
	if (m_currAchieve != -1)
	{
		//s_CUI_ID_FRAME_Achivement.ShowAchieve(m_currAchieve);
	}	
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_AchieveFinish::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\AchieveFinish.MEUI" , false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\AchieveFinish.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_AchieveFinish::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_AchieveFinish, s_CUI_ID_FRAME_AchieveFinishOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_AchieveFinish, s_CUI_ID_FRAME_AchieveFinishOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_AchieveFinish, ID_LISTIMG_Icon0, s_CUI_ID_FRAME_AchieveFinishID_LISTIMG_Icon0OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_AchieveFinish, ID_LISTIMG_Icon0, s_CUI_ID_FRAME_AchieveFinishID_LISTIMG_Icon0OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_AchieveFinish, ID_LISTIMG_Icon0, s_CUI_ID_FRAME_AchieveFinishID_LISTIMG_Icon0OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_AchieveFinish, ID_LISTIMG_Icon0, s_CUI_ID_FRAME_AchieveFinishID_LISTIMG_Icon0OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_AchieveFinish, ID_LISTIMG_Award0, s_CUI_ID_FRAME_AchieveFinishID_LISTIMG_Award0OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_AchieveFinish, ID_LISTIMG_Award0, s_CUI_ID_FRAME_AchieveFinishID_LISTIMG_Award0OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_AchieveFinish, ID_LISTIMG_Award0, s_CUI_ID_FRAME_AchieveFinishID_LISTIMG_Award0OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_AchieveFinish, ID_LISTIMG_Award0, s_CUI_ID_FRAME_AchieveFinishID_LISTIMG_Award0OnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_AchieveFinish, ID_BUTTON_Award0, s_CUI_ID_FRAME_AchieveFinishID_BUTTON_Award0OnButtonClick );

	m_pID_FRAME_AchieveFinish = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_AchieveFinish );
	m_pID_LISTIMG_Icon0 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_AchieveFinish, ID_LISTIMG_Icon0 );
	m_pID_TEXT_Number0 = (ControlText*)theUiManager.FindControl( ID_FRAME_AchieveFinish, ID_TEXT_Number0 );
	m_pID_LISTIMG_Award0 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_AchieveFinish, ID_LISTIMG_Award0 );
	m_pID_TEXT_Content0 = (ControlText*)theUiManager.FindControl( ID_FRAME_AchieveFinish, ID_TEXT_Content0 );
	m_pID_TEXT_Data0 = (ControlText*)theUiManager.FindControl( ID_FRAME_AchieveFinish, ID_TEXT_Data0 );
	m_pID_BUTTON_Award0 = (ControlButton*)theUiManager.FindControl( ID_FRAME_AchieveFinish, ID_BUTTON_Award0 );
	m_pID_PICTURE_AchivementComplete0 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AchieveFinish, ID_PICTURE_AchivementComplete0 );
	m_pID_TEXT_Top0 = (ControlText*)theUiManager.FindControl( ID_FRAME_AchieveFinish, ID_TEXT_Top0 );

	assert( m_pID_FRAME_AchieveFinish );
	assert( m_pID_LISTIMG_Icon0 );
	assert( m_pID_TEXT_Number0 );
	assert( m_pID_LISTIMG_Award0 );
	assert( m_pID_TEXT_Content0 );
	assert( m_pID_TEXT_Data0 );
	assert( m_pID_BUTTON_Award0 );
	assert( m_pID_PICTURE_AchivementComplete0 );
	assert( m_pID_TEXT_Top0 );

	SetVisable(false);
	m_pID_FRAME_AchieveFinish->SetFadeInorFadeOut(true);
	m_pID_FRAME_AchieveFinish->SetRenderNeedRedraw(s_CUI_ID_FRAME_AchieveFinishOnFrameRenderNeedRedraw);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_AchieveFinish::_UnLoadUI()
{
	m_pID_FRAME_AchieveFinish = NULL;
	m_pID_LISTIMG_Icon0 = NULL;
	m_pID_TEXT_Number0 = NULL;
	m_pID_LISTIMG_Award0 = NULL;
	m_pID_TEXT_Content0 = NULL;
	m_pID_TEXT_Data0 = NULL;
	m_pID_BUTTON_Award0 = NULL;
	m_pID_PICTURE_AchivementComplete0 = NULL;
	m_pID_TEXT_Top0 = NULL;
	if(m_pCoolDownAni)
	{
		delete m_pCoolDownAni;
		m_pCoolDownAni = NULL;
	}
	return theUiManager.RemoveFrame( "Data\\UI\\AchieveFinish.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_AchieveFinish::_IsVisable()
{
	if ( !m_pID_FRAME_AchieveFinish )
		return false;
	return m_pID_FRAME_AchieveFinish->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_AchieveFinish::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_AchieveFinish )
		return ;
	m_pID_FRAME_AchieveFinish->SetVisable( bVisable );
	if (bVisable)
	{
		m_UIShowBeginTime = HQ_TimeGetTime();
		m_bAnimationShowOnce = true;
		m_pID_PICTURE_AchivementComplete0->SetVisable(false);

		AchieveConfig::Achieve* pAchieve = theAchieveConfig.GetAchieve(m_currAchieve);
		if(pAchieve == NULL)
		{
			return;
		}
		char szSoundPath[MAX_PATH] = {0};
		sprintf_s(szSoundPath,sizeof(szSoundPath),"%s\\%s",GetRootPath(),gCfg.m_strAchieveSoundPath.c_str());
		GSound.PlaySound(szSoundPath,false,NULL);
		m_pID_TEXT_Top0->SetVisable(true);
		m_pID_TEXT_Top0->SetText(pAchieve->GetName());

		m_pID_TEXT_Content0->SetVisable(true);
		m_pID_TEXT_Content0->SetText(pAchieve->GetDesc());

		m_pID_TEXT_Number0->SetVisable(true);
		char cTemp[16] = {0};
		sprintf_s(cTemp,16,"%d",pAchieve->GetRewardPoint());
		m_pID_TEXT_Number0->SetText(cTemp);

		m_pID_LISTIMG_Icon0->SetVisable(true);
		ControlIconDrag::S_ListImg ImgItem;
		ImgItem.SetData(pAchieve->GetIconID(),1);
		m_pID_LISTIMG_Icon0->SetItem(&ImgItem,0);

		if (pAchieve->GetRewardItem() != 0)
		{
			m_pID_LISTIMG_Award0->SetVisable(true);
			ControlIconDrag::S_ListImg ImgAward;
			ImgAward.SetData(pAchieve->GetRewardItem(),1);
			m_pID_LISTIMG_Award0->SetItem(&ImgAward,0);
		}
		else
		{
			m_pID_LISTIMG_Award0->SetVisable(false);
		}

		{
			m_pID_TEXT_Data0->SetVisable(true);
			tm finishTime;
			_localtime64_s(&finishTime, &m_64FinishTime);
			char cDate[128];
			MeSprintf_s(cDate, sizeof(cDate)/sizeof(char) - 1, "%04d:%02d:%02d", finishTime.tm_year + 1900, finishTime.tm_mon, finishTime.tm_mday);
			m_pID_TEXT_Data0->SetText(cDate);
		}

	}
	
}

void CUI_ID_FRAME_AchieveFinish::SetCurrAchieve( int val ,int64 dwFinishTime)
{
	m_currAchieve = val;
	m_64FinishTime = dwFinishTime;
}

CSmartAnimation* CUI_ID_FRAME_AchieveFinish::GetCoolDownAniNotNULL()
{
	if (NULL == m_pCoolDownAni)
	{
		char fullname[MAX_PATH] = {0};
		MeSprintf_s(fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\ui\\UIAni\\AchieveFinish.2DAni", GetRootPath());

		m_pCoolDownAni = new CXmlAnimation( m_pID_FRAME_AchieveFinish->GetFrameRender() );
		MeXmlDocument doc;
		if(!doc.LoadFile(fullname))
		{
			assert(0);
			return m_pCoolDownAni;
		}
		MeXmlElement* pElement = doc.FirstChildElement("AchieveFinish");
		if (pElement)
		{
			CXmlAnimation* pSmart = (CXmlAnimation*)m_pCoolDownAni;
			pSmart->Initialize(pElement);
		}

		RECT rcPlay;
		m_pID_PICTURE_AchivementComplete0->GetRealRect(&rcPlay);
		int nWidth = rcPlay.right -rcPlay.left;
		int nHeight = rcPlay.bottom - rcPlay.top;
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
//  		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Width, nWidth, NULL );
// 		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Height, nHeight, NULL );

// 		CLinearFunctor* pWidthFunctor = (CLinearFunctor*)CFunctorMaker::GetInstance()->CreateFunctor("Linear");
// 		pWidthFunctor->InitializeByTime(nWidth,m_nAnimationTotalTime,nWidth);
// 		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Width, 0, pWidthFunctor );
// 		CLinearFunctor* pHeightFunctor = (CLinearFunctor*)CFunctorMaker::GetInstance()->CreateFunctor("Linear");
// 		pHeightFunctor->InitializeByTime(nHeight,m_nAnimationTotalTime,nHeight);
// 		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Height, 0, pHeightFunctor );

// 		static int nPicId = -1;
// 		std::string strPicName = GetRootPath();
// 		strPicName += "/Data/Ui/Common/UIAchivement.tga";
// 		ControlPictureManager::S_Pic* pPic = theControlPictureManager.RegisterTexture( &nPicId, strPicName.c_str() );
// 		m_pCoolDownAni->SetUiPicture( pPic->m_pd3dTexture );
	}
	return m_pCoolDownAni;


}

bool CUI_ID_FRAME_AchieveFinish::OnFrameRenderNeedRedraw()
{
	{
		DWORD dwCurTime = HQ_TimeGetTime();
		if (m_ShowBeginTime != 0)
		{
			// 未创建动画则创建
			CSmartAnimation* coolDownAni = GetCoolDownAniNotNULL();
			if( !coolDownAni->IsInAnimation() && coolDownAni->GetD3DTexture() )
			{
				RECT rcPlay;
				m_pID_PICTURE_AchivementComplete0->GetRealRect(&rcPlay);
				int nWidth = rcPlay.right -rcPlay.left;
				int nHeight = rcPlay.bottom - rcPlay.top;
				m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
				m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
// 				m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Width, nWidth, NULL );
// 				m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Height, nHeight, NULL );
				m_pID_FRAME_AchieveFinish->GetUiAniManageNotNULL()->AddAnimation( coolDownAni );
				coolDownAni->StartAnimation( dwCurTime,dwCurTime - m_ShowBeginTime, false );
			}
			else
			{
				coolDownAni->Redraw(dwCurTime);
			}
		}
		else
		{
			m_pID_PICTURE_AchivementComplete0->SetVisable(true);
		}
	}
	return true;
}

void CUI_ID_FRAME_AchieveFinish::ResetDevice()
{
	if(m_pCoolDownAni && m_pCoolDownAni->GetD3DTexture() )
	{
		RECT rcPlay;
		m_pID_PICTURE_AchivementComplete0->GetRealRect(&rcPlay);
		int nWidth = rcPlay.right -rcPlay.left;
		int nHeight = rcPlay.bottom - rcPlay.top;
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
	}
}