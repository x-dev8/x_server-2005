/********************************************************************
Created by UIEditor.exe
FileName: F:\workspace\ShenWang\Hero\Program\trunk\Bin\Client\Data\Ui\CharacterExp.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CharacterExp.h"
#include "Core/Name.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "ExMenu.h"
#include "MeUi/Animation/XmlAnimation.h"
#include "MeUi/UiRender.h"
#include "RapidXml/rapidxml.h"
CUI_ID_FRAME_CharacterExp s_CUI_ID_FRAME_CharacterExp;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CharacterExp, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CharacterExp, OnFrameRender )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CharacterExp, OnFrameRenderNeedRedraw )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CharacterExp, ID_BUTTON_OtherOnButtonClick )

// bool g_bShow = false;
CUI_ID_FRAME_CharacterExp::CUI_ID_FRAME_CharacterExp()
{
	// Member
	m_pID_FRAME_CharacterExp = NULL;
	m_pID_PROGRESS_CharacterExp_Exp = NULL;
// 	m_pID_PROGRESS_CharacterExp_ExpTip = NULL;
// 	//m_pID_TEXT_Exp = NULL;
	m_pID_PICTURE_Effect = NULL;

    m_CurKillMonster  = 0;    //当前杀怪数量
    m_TotalKillMonster = 0;  //总杀怪数量
	m_pCoolDownAni = NULL;
	m_dwStartTime = 0;
	m_bRenderAnim = false;
}
// Frame
bool CUI_ID_FRAME_CharacterExp::OnFrameRun()
{
	if( !m_pID_FRAME_CharacterExp || !IsVisable() )
		return false;

	if( m_pID_FRAME_CharacterExp->PtInObject( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y ) )
	{
		EnableAnim( true );
	}
	else
	{
		if( m_bRenderAnim )
		{
			EnableAnim(false);
			if (NULL != m_pCoolDownAni)
			{
				m_pID_FRAME_CharacterExp->GetUiAniManageNotNULL()->StopAnimation(m_pCoolDownAni);
				m_dwStartTime = 0;
				m_pID_FRAME_CharacterExp->SetRedraw();
			}
		}
	}
	return true;
}
bool CUI_ID_FRAME_CharacterExp::OnFrameRender()
{
//      if(g_bShow&&m_pID_PICTURE_MonsterNum != NULL)
//     {
//             char szWord[64];
//              MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_TodayKillMonster),m_CurKillMonster,m_TotalKillMonster);
//              m_pID_PICTURE_MonsterNum->setTip(szWord);
//      }
	//      g_bShow = false;
	return true;
}
bool CUI_ID_FRAME_CharacterExp::ID_BUTTON_OtherOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_CharacterExp )
		return false;
 	s_CUI_ID_FRAME_ExMenu.SetVisable( !s_CUI_ID_FRAME_ExMenu.IsVisable() );
	return true;
}

void CUI_ID_FRAME_CharacterExp::InitializeAtEnterWorld()
{
    if( !m_pID_FRAME_CharacterExp )
        return;

    m_pID_FRAME_CharacterExp->SetMsgHoldup(false);
    m_CurKillMonster = 0;    //当前杀怪数量
    m_TotalKillMonster = 0;  //总杀怪数量

    //     m_pID_PICTURE_MonsterNum->SetOnMouseOn(MyMouseMove);
    //     m_pID_PICTURE_MonsterNum->setShowTip();   //显示TIP
}

// 装载UI
bool CUI_ID_FRAME_CharacterExp::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CharacterExp.MEUI", true, UI_Render_LayerFirst );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CharacterExp.MEUI]失败")
			return false;
	}
// 	else if ( dwResult != 1/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[Data\\UI\\CharacterExp.MEUI]与源代码版本不一样")
// 	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CharacterExp::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CharacterExp, s_CUI_ID_FRAME_CharacterExpOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CharacterExp, s_CUI_ID_FRAME_CharacterExpOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_CharacterExp, ID_BUTTON_Other,  s_CUI_ID_FRAME_CharacterExpID_BUTTON_OtherOnButtonClick );

	m_pID_FRAME_CharacterExp = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CharacterExp );
	m_pID_PROGRESS_CharacterExp_Exp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_CharacterExp, ID_PROGRESS_CharacterExp_Exp );
	//m_pID_PROGRESS_CharacterExp_ExpTip = (ControlProgress*)theUiManager.FindControl( ID_FRAME_CharacterExp, ID_PROGRESS_CharacterExp_ExpTip );
	m_pID_TEXT_Exp = (ControlText*)theUiManager.FindControl( ID_FRAME_CharacterExp, ID_TEXT_Exp );
	m_pID_PICTURE_Effect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CharacterExp, ID_PICTURE_Effect );
	m_pID_BUTTON_Other = (ControlButton*)theUiManager.FindControl( ID_FRAME_CharacterExp, ID_BUTTON_Other );

    assert( m_pID_FRAME_CharacterExp );
	assert( m_pID_PROGRESS_CharacterExp_Exp );
	//assert( m_pID_PROGRESS_CharacterExp_ExpTip );
	assert( m_pID_TEXT_Exp );
    assert( m_pID_PICTURE_Effect);
	
	m_pID_FRAME_CharacterExp->SetRenderNeedRedraw(s_CUI_ID_FRAME_CharacterExpOnFrameRenderNeedRedraw);
	m_pID_BUTTON_Other->SetButtonMouseOnFun(OnMouseOnOther);
    _SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_CharacterExp::_UnLoadUI()
{
	m_pID_FRAME_CharacterExp = NULL;
	m_pID_PROGRESS_CharacterExp_Exp = NULL;
// 	m_pID_PROGRESS_CharacterExp_ExpTip = NULL;
 	m_pID_PICTURE_Effect = NULL;
	if(m_pCoolDownAni)
	{
		delete m_pCoolDownAni;
		m_pCoolDownAni = NULL;
	}

	return theUiManager.RemoveFrame( "Data\\UI\\CharacterExp.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CharacterExp::_IsVisable()
{
	if(!m_pID_FRAME_CharacterExp)
		return false;

	return m_pID_FRAME_CharacterExp->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CharacterExp::_SetVisable( const bool bVisable )
{
	if( m_pID_FRAME_CharacterExp )
		m_pID_FRAME_CharacterExp->SetVisable( bVisable );
}

void  CUI_ID_FRAME_CharacterExp::MyMouseMove( ControlObject* pSender )
{
//     g_bShow = true;
}

void CUI_ID_FRAME_CharacterExp::SetExpValue( __int64 exp )
{
	if(m_pID_PROGRESS_CharacterExp_Exp)
		m_pID_PROGRESS_CharacterExp_Exp->SetValue(exp);
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_CharacterExp::SetTextExp( const char* chr )
{
	if(m_pID_TEXT_Exp)
		m_pID_TEXT_Exp->SetText(chr);
	else
		assert(false&&"ui error");
}

bool CUI_ID_FRAME_CharacterExp::IsPtOnOtherButton()
{
	return m_pID_BUTTON_Other && m_pID_BUTTON_Other->PtInObject(theUiManager.m_ptMoust.x,theUiManager.m_ptMoust.y);
}

bool CUI_ID_FRAME_CharacterExp::OnFrameRenderNeedRedraw()
{
	if (m_bRenderAnim)
	{
		DWORD dwCurTime = HQ_TimeGetTime();
		// 未创建动画则创建
		CSmartAnimation* coolDownAni = GetCoolDownAniNotNULL();
		if( !coolDownAni->IsInAnimation() )
		{
			m_pID_FRAME_CharacterExp->GetUiAniManageNotNULL()->AddAnimation( coolDownAni );

			coolDownAni->StartAnimation( dwCurTime,dwCurTime - m_dwStartTime, true );
		}
		else
		{
			coolDownAni->Redraw(dwCurTime);
		}
	}
	else
	{
		if (NULL != m_pCoolDownAni)
		{
			m_pID_FRAME_CharacterExp->GetUiAniManageNotNULL()->StopAnimation(m_pCoolDownAni);
			m_dwStartTime = 0;
		}
	}	
	return true;
}
extern const char* GetRootPath();
CSmartAnimation* CUI_ID_FRAME_CharacterExp::GetCoolDownAniNotNULL()
{
	if (NULL == m_pCoolDownAni)
	{
		char fullname[MAX_PATH] = {0};
		MeSprintf_s(fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\ui\\UIAni\\OtherButton.2DAni", GetRootPath());
		m_pCoolDownAni = new CXmlAnimation(m_pID_FRAME_CharacterExp->GetFrameRender());

		MeXmlDocument doc;
		if(!doc.LoadFile(fullname))
		{
			assert(0);
			return m_pCoolDownAni;
		}
		MeXmlElement* pElement = doc.FirstChildElement("OtherButton");
		if (pElement)
		{
			CXmlAnimation* pSmart = (CXmlAnimation*)m_pCoolDownAni;
			pSmart->Initialize(pElement);
		}

// 		CIntervalFunctor* pSrcXFunctor = (CIntervalFunctor*)CFunctorMaker::GetInstance()->CreateFunctor("Interval");
// 		m_pCoolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_SrcX,0,pSrcXFunctor);
// 		assert(pSrcXFunctor);
// 		pSrcXFunctor->SetParamA( 0 );
// 		pSrcXFunctor->SetParamB( 100 );
// 		pSrcXFunctor->SetParamC( 500/15 );
// 		pSrcXFunctor->SetTotalTime( 500 );

		RECT rcPlay;
		m_pID_PICTURE_Effect->GetRealRect(&rcPlay);
		int nWidth = rcPlay.right -rcPlay.left;
		int nHeight = rcPlay.bottom - rcPlay.top;
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Width, rcPlay.right -rcPlay.left, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Height, rcPlay.bottom - rcPlay.top, NULL );
// 		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_SrcY, 0, NULL );
// 		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_SrcWidth, 100, NULL );
// 		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_SrcHeight, 100, NULL );

// 		static int nPicId = -1;
// 		std::string strPicName = GetRootPath();
// 		strPicName += "/Data/Ui/Common/Longtoutexiao.dds";
// 		ControlPictureManager::S_Pic* pPic = theControlPictureManager.RegisterTexture( &nPicId, strPicName.c_str() );
// 		m_pCoolDownAni->SetUiPicture( pPic->m_pd3dTexture );
	}
	return m_pCoolDownAni;

}

void CUI_ID_FRAME_CharacterExp::OnMouseOnOther( ControlObject* pSender )
{
	//s_CUI_ID_FRAME_ExMenu.SetVisable( true);
	if (s_CUI_ID_FRAME_CharacterExp.m_dwStartTime == 0)
	{
		s_CUI_ID_FRAME_CharacterExp.m_dwStartTime = HQ_TimeGetTime();
		s_CUI_ID_FRAME_CharacterExp.m_pID_FRAME_CharacterExp->SetRedraw();
	}

}

void CUI_ID_FRAME_CharacterExp::ResetDevice()
{
	if(m_pCoolDownAni  )
	{
		RECT rcPlay;
		m_pID_PICTURE_Effect->GetRealRect(&rcPlay);
		int nWidth = rcPlay.right -rcPlay.left;
		int nHeight = rcPlay.bottom - rcPlay.top;
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Width, rcPlay.right -rcPlay.left, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Height, rcPlay.bottom - rcPlay.top, NULL );
	}

}
