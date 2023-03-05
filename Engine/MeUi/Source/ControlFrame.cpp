#include "MeUi/ControlFrame.h"
#include <assert.h>
#include "MeUi/MeUi.h"
#include "MeUi/UiManager.h"
#include "FuncPerformanceLog.h"
#include "MeUi/Animation/SmartAnimation.h"
#include "MeUi/UiRender.h"
#include "MeUi/ExpressionManager.h"
#include "MeFont/NewFont/MeFontRender.h"
#include "MeFont/MeFontSystem.h"

extern std::string g_UIZipFile;

ControlFrame::ControlFrame(void)
{
	m_bLButtonDrag = false;
	memset( &m_ptLBDOffset, 0, sizeof(m_ptLBDOffset) );
	m_pRun = NULL;
	//m_bUseAutoClose = false;
	memset( &m_rcAutoClose, 0, sizeof(m_rcAutoClose) );
	m_pOnClick = NULL;
    m_pOnDBClick = NULL;
	_pOnRBtnDown = NULL;
	_pOnMouseMoveOn = NULL;
	_pOnMouseMoveLevel = NULL;
	_pOnTab = NULL;
	_pFrameMove = NULL;

    for( int i = 0; i < ERenderTypeMax; ++i )
    {
        m_pRender[i] = NULL;
        m_pRenderNeedRedraw[i] = NULL;
        m_pRenderIndexedFrame[i] = NULL;
    }

	_luaTableName.clear();
	_funOnClickName.clear();
	_funOnRBtnDownName.clear();
	_funOnMouseMoveOnName.clear();
	_funOnMouseMoveLevelName.clear();
	_funOnOnFrameMoveName.clear();
	_funRunName.clear();
	_funRenderName.clear();
	_funOnTabName.clear();

    _enableEscKey = true;
	m_bMouseLButtonDown = false;
	m_bLControlDown = false;
	m_index			= -1;
	m_pRunIndexedFrame = NULL;

	m_pSecondFrame = NULL;

	m_pFrameRender = NULL;
	m_pUiAniManage = NULL;
	m_pExpressionUpdater = NULL;
	m_bRedraw		= true;
	m_eOnEscResponseType = EscResponse_Normal;
	m_bSolidScale	= false;

	m_bSettingWork = false;
	m_nFadeCurColorA = 0xFF;
}

ControlFrame::~ControlFrame(void)
{
	ReleaseUI();
}

void ControlFrame::ReleaseUI()
{
	for( UINT n=0; n<m_vtChild.size(); n++ )
	{
		if( n == 2 )
		{
			int k = 0;
		}
		if ( m_vtChild[n] )
		{
			ControlObject* p = m_vtChild[n];
			delete p;
			p = NULL;
		}
	}
	m_vtChild.clear();
	if (NULL != m_pFrameRender)
	{
		delete m_pFrameRender;
		m_pFrameRender = NULL;
	}
	if (NULL != m_pUiAniManage)
	{
		delete m_pUiAniManage;
		m_pUiAniManage = NULL;
	}
	if (NULL != m_pExpressionUpdater)
	{
		delete m_pExpressionUpdater;
		m_pExpressionUpdater = NULL;
	}
	if (m_pFather != NULL)
	{
		ControlFrame* pFatherFrame = (ControlFrame*)m_pFather;
		pFatherFrame->RemoveChildFrame(this);
	}
	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		m_vtChildFrame[i]->SetFather(NULL);
	}
//	ControlObject::ReleaseUI();
}

void ControlFrame::Run()
{
// 	if (m_bFadeInorFadeOut )
// 	{
// 		SetRedraw();
// 	}

// 	if( NULL != state.Get() && _luaTableName.length() > 0 && _funRunName.length() > 0 )
// 	{
// 		try
// 		{
// 			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
// 			if( table1Obj.IsTable() )
// 			{
// 				LuaFunction<void> function_( table1Obj[_funRunName.c_str()] );
// 				function_();
// 			}
// 		}
// 		catch (LuaPlus::LuaException &e)
// 		{
// 			char szErr[256] = {0};
// 			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funRunName.c_str(), e.GetErrorMessage());
// 			print_error( szErr );
// 		}
// 	}
// 	else
	{
		if ( m_pRun )
		{
			m_pRun();
		}
		else if (m_pRunIndexedFrame)
		{
			m_pRunIndexedFrame(m_index);
		}
	}
	// 淡入淡出
	if( m_bInFade )
	{
		if ( IsVisable() )
		{
			m_nFadeCurColorA = m_FadeSpeed*(HQ_TimeGetTime()-m_dwFadeLastTime);
			if ( m_nFadeCurColorA >= m_nMaxFade )
			{
				m_nFadeCurColorA = m_nMaxFade;
				m_bInFade = false;
			}
		}
		else
		{
			m_nFadeCurColorA = 0xFF - m_FadeSpeed*(HQ_TimeGetTime()-m_dwFadeLastTime);
			if ( m_nFadeCurColorA <= m_nMinFade )
			{
				if (m_pOnVisibleChanged)
				{
					m_pOnVisibleChanged( this );
				}
				m_nFadeCurColorA = m_nMinFade;
				m_bInFade = false;
			}
		}
		GetFrameRender()->SetAlpha(m_nFadeCurColorA);
		if ( !m_bInFade )
		{
			theUiManager.Compositor();
		}
	}

// 	ControlObject::Run();
	for( UINT n=0; n<m_vtChild.size(); n++ )
	{
        if( m_vtChild[n] )
		    m_vtChild[n]->Run();
	}
}

static int LeaveSecondFrameDistance = 3;

void ControlFrame::SetWorking(RECT &rc)
{
	m_bSettingWork = true;
	m_ShowRect.left = rc.left;
	m_ShowRect.right = rc.right;
	m_ShowRect.top   = rc.top;
	m_ShowRect.bottom = rc.bottom;
}

void ControlFrame::Render()
{
	if ( IsNeedRender() )
	{
        if( m_pRender[EBeforeUIRender] )
            m_pRender[EBeforeUIRender]();
        else if( m_pRenderIndexedFrame[EBeforeUIRender] )
            m_pRenderIndexedFrame[EBeforeUIRender]( m_index );

        g_uiRenderCurrFrame = GetFrameRender();
		if (!GetFrameRender()->isQueueingEnabled() || m_bRedraw)
		{
			m_bRedraw = false;
			GetFrameRender()->clearRenderList();
			if(m_bSettingWork)
		      	GetFrameFather()->GetFrameRender()->PushWorkingArea(m_ShowRect);

            if( m_pRenderNeedRedraw[EBeforeUIRender] )
                m_pRenderNeedRedraw[EBeforeUIRender]();
			
// 			if (GetUiAniManage())
// 			{
// 				GetUiAniManage()->StopAllAnimation();
// 			}
			if (GetExpressionUpdater())
			{
				GetExpressionUpdater()->Clear();
			}

			//frame的m_nFadeCurColorA已经用在了uirender，自身绘制的时候不在叠加这个值
			int nThisFadeAlpha = m_nFadeCurColorA;
			m_nFadeCurColorA = 0xFF;
			ControlObject::Render();
			m_nFadeCurColorA = nThisFadeAlpha;

			for( UINT n=0; n<m_vtChild.size(); n++ )
			{
				m_vtChild[n]->Render();
			}

            if( m_pRenderNeedRedraw[EAfterUIRender] )
                m_pRenderNeedRedraw[EAfterUIRender]();

			if(m_bSettingWork)
			{
				GetFrameFather()->GetFrameRender()->PopWorkingArea();
				m_bSettingWork = false;
			}
		}
		else
		{
			if (GetUiAniManage())
			{
				GetUiAniManage()->Update(HQ_TimeGetTime());
			}
			if (GetExpressionUpdater())
			{
				GetExpressionUpdater()->Update();
			}
		}
		FontSystem::BeginRender();
		GetFrameRender()->doRender();
		FontSystem::EndRender();
		g_uiRenderCurrFrame = NULL;  

// 		if ( m_bUseAutoClose == true )
// 		{
// 			RECT rcReal;
// 			GetRealRect( &rcReal );
// 			m_rcAutoClose.left = rcReal.right-20;
// 			m_rcAutoClose.top = rcReal.top;
// 			m_rcAutoClose.right = rcReal.right;
// 			m_rcAutoClose.bottom = rcReal.top+20;
// 			UiDrawer::DrawRect2D( m_rcAutoClose, 0xff00ff00 );
// 		}

        if( m_pRender[EAfterUIRender] )
            m_pRender[EAfterUIRender]();
        else if( m_pRenderIndexedFrame[EAfterUIRender] )
            m_pRenderIndexedFrame[EAfterUIRender]( m_index );

		for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
		{
			if (m_vtChildFrame[i] != m_pSecondFrame)
				m_vtChildFrame[i]->Render();
		}

		if (m_pSecondFrame)
		{
			m_pSecondFrame->SetFather(this);

			int w  = m_pSecondFrame->GetData()->m_rcRealSize.right - m_pSecondFrame->GetData()->m_rcRealSize.left;
			m_pSecondFrame->GetData()->m_rcRealSize.left = -(m_pSecondFrame->GetData()->m_rcRealSize.right - m_pSecondFrame->GetData()->m_rcRealSize.left) + LeaveSecondFrameDistance;
			m_pSecondFrame->GetData()->m_rcRealSize.right = m_pSecondFrame->GetData()->m_rcRealSize.left + w;
			m_pSecondFrame->SetHeight(GetHeight());
			m_pSecondFrame->SetVisable(true);

			ControlObject* pPic = m_pSecondFrame->FindControl("ID_PICTURE_ShopItemWall", GetControlID());
			if (pPic)
			{
				// 500为"ID_PICTURE_ShopItemWall"原始的高，590为"ID_FRAME_Trade"原始的高
				pPic->SetHeight(500.0f / 590.0f * GetHeight());
			}


			S_BaseData::S_Pic* pOldPic = 0;
			ControlButton* pBtn = (ControlButton*)m_pSecondFrame->FindControl("ID_BUTTON_Shopping", GetControlID());
			if (pBtn && !pBtn->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y,false))
			{
				pOldPic = pBtn->GetPic();
				pBtn->SetNormalPic();
			}

			m_pSecondFrame->Render();
			m_pSecondFrame->SetVisable(false);

			if (pOldPic)
			{
				pBtn->SetPic(pOldPic);
			}
		}
	}
}

ControlObject* ControlFrame::FindFrame( IN const char *szFrameID )
{
	// 找子控件
	for( UINT n=0; n<m_vtChild.size(); n++ )
	{
		if( strcmp( m_vtChild[n]->GetControlID(), szFrameID) == 0 )
		{
			return m_vtChild[n];
		}
	}
	// 找子控件的控件
	ControlObject* pControl = NULL;
	for( UINT n=0; n<m_vtChild.size(); n++ )
	{
		pControl = m_vtChild[n]->FindFrame( szFrameID );
		if ( pControl )
		{
			return pControl;
		}
	}
	return NULL;
}

ControlObject* ControlFrame::FindControl( IN const char* szControlID,
											IN const char* szFrameID )
{
	if (szControlID == NULL)
	{
		return NULL;
	}
	// 找子控件
	for( UINT n=0; n<m_vtChild.size(); n++ )
	{
		if( strcmp( m_vtChild[n]->GetControlID(), szControlID) == 0 )
		{
			return m_vtChild[n];
		}
	}
	if (szFrameID == NULL)
	{
		return NULL;
	}
	// 找子控件的控件
	ControlObject* pControl = NULL;
	for( UINT n=0; n<m_vtChild.size(); n++ )
	{
		pControl = m_vtChild[n]->FindControl( szControlID, szFrameID );
		if ( pControl )
		{
			return pControl;
		}
	}
	return NULL;
}

//------- 载入文件    (By   at 2004-6-2)
DWORD ControlFrame::LoadUIFormUnit(IN const char* szZipFileName, IN const char* szUnitName, IN ControlObject* pFather )
{
	//guard( ControlFrame::LoadUIFormFile );
    //guard( ControlFrame::LoadUIFormUnit);
//	//assert( szUnitName );
//	//assert( szUnitName[0] != 0 );
//	//ReleaseUI();
//
//    //Tony:取得Unit大小
//    unsigned int len = 0;
//    len = CZipManager::getSingletonInstance()->getZipUnitSize(szZipFileName,szUnitName);
//    
//    if(!len) //如果载入Unit失败，则返回0
//    {
//        MESSAGE_BOX("载入文件失败!")
//        return 0;
//    }
//    //申请由Len返回的缓冲
//    void* pDst = malloc(len);
//
//    //将被截压缩的Unit内容写入pDst
//    CZipManager::getSingletonInstance()->getZipUnitToMemory(szZipFileName,szUnitName,pDst, len);	
//
//    std::string _szUnitName = szUnitName;
//    std::string _strExtern = _szUnitName.substr( _szUnitName.length() - 3, 3 );
//    S_UIData	stUIData;
//
//    //压缩包内的Unit文件可能是XML
//    //如果是XML文件则使用MeXmlDocument的LoadFileFromBuffer方法
//    if( strcmp( _strExtern.c_str(), "xml") == 0 )
//    {        
//        stUIData.LoadUnit_XML(pDst,len);        
//    }
//	else //普通UI文件，使用缓冲读取并初始化对象
//	{        
//        if (0 ==stUIData.LoadUnit( pDst ))
//        {
//            MESSAGE_BOX("载入文件失败!")
//		    return 0;
//        }
//	}
//    //释放解压Unit文件内存
//    free(pDst);
//
//    if ( theUiManager.FindFrame(stUIData.m_stHead.m_stFrameData.m_szID) )
//	{
//#ifdef _DEBUG
//		char szDebug[128];
//		sprintf( szDebug, "[%s]中已有此ID的框架[%s]",
//					szUnitName, stUIData.m_stHead.m_stFrameData.m_szID );
//		MESSAGE_BOX( szDebug )
//#endif
//		return 0;
//	}
//
//	// 生成自身数据
//	S_FrameData *pstData = MeNew S_FrameData;
//	m_bNeedRelease = true;
//	*pstData = stUIData.m_stHead.m_stFrameData;
//	InitUIData( pFather, pstData );
//
//	// 生成子控件数据
//	for( int n=0; n<stUIData.m_stHead.m_nControlsCount; n++ )
//	{
//		if( strcmp( "UI/Pack.UI", szUnitName ) == 0 )
//		{
//		//	MessageBox(NULL,"4", "AddFrame", MB_OK );
//			guard(UIPack.UI);
//			if( stUIData.m_pstControlData[n] == NULL )
//			{
//		//		MessageBox(NULL,"5", "stUIData.m_pstControlData", MB_OK );
//			}
//			unguard;
//		}
//		if ( FindControl(stUIData.m_pstControlData[n]->m_szID) )
//		{
//#ifdef _DEBUG
//			assert(false);
//			char szDebug[128];
//			sprintf( szDebug, "[%s]中已有此ID的控件[%s]", szUnitName, stUIData.m_pstControlData[n]->m_szID );
//			MESSAGE_BOX( szDebug )
//#endif
//			ReleaseUI();
//			return 0;
//		}
//		
//		ControlObject *pUIObject = NULL;
//		//--------------
//		pUIObject = theUiManager.CreateWidget(stUIData.m_pstControlData[n], this);		
//	}
//	
//	return stUIData.m_stHead.m_dwCreatedDate;
	//unguard;
	return 0;
}

DWORD ControlFrame::LoadUIFormFile( IN const char* szFileName, IN ControlObject* pFather,int index )
{
	guard( ControlFrame::LoadUIFormFile );
	assert( szFileName );
	assert( szFileName[0] != 0 );
	ReleaseUI();
    m_index = index;
    //return LoadUIFormUnit(g_UIZipFile.c_str(),szFileName,pFather);
	S_UIData	stUIData;
	if ( stUIData.LoadFile( szFileName ) == false )
	{
		MESSAGE_BOX("载入文件失败!")
		return 0;
	}
	else 
	{
		AddPosfixByIndex(index, stUIData.m_stHead.m_stFrameData.m_szID);
		if ( theUiManager.FindFrame(stUIData.m_stHead.m_stFrameData.m_szID) )
		{
#ifdef _DEBUG
			char szDebug[128];
			sprintf( szDebug, "[%s]中已有此ID的框架[%s]",
				szFileName, stUIData.m_stHead.m_stFrameData.m_szID );
			MESSAGE_BOX( szDebug )
#endif
				return 0;
		}

	}

	// 生成自身数据
	S_FrameData *pstData = MeNew S_FrameData;
	m_bNeedRelease = true;
	*pstData = stUIData.m_stHead.m_stFrameData;
	InitUIData( pFather, pstData );

	// 生成子控件数据
	for( int n=0; n<stUIData.m_stHead.m_nControlsCount; n++ )
	{
#ifdef _DEBUG
		char lwrName[MAX_PATH];
		strcpy( lwrName, szFileName );
		strlwr(lwrName);
		if( strstr( lwrName, "data\\ui\\pack.ui" ) )
		{
		//	MessageBox(NULL,"4", "AddFrame", MB_OK );
			guard(UIPack.UI);
			if( stUIData.m_pstControlData[n] == NULL )
			{
		//		MessageBox(NULL,"5", "stUIData.m_pstControlData", MB_OK );
			}
			unguard;
		}
#endif
		if ( FindControl(stUIData.m_pstControlData[n]->m_szID) )
		{
#ifdef _DEBUG
			assert(false);
			char szDebug[128];
			sprintf( szDebug, "[%s]中已有此ID的控件[%s]", szFileName, stUIData.m_pstControlData[n]->m_szID );
			MESSAGE_BOX( szDebug )
#endif
			ReleaseUI();
			return 0;
		}
		
		ControlObject *pUIObject = NULL;
		//--------------
		pUIObject = theUiManager.CreateWidget(stUIData.m_pstControlData[n], this);
		//--------------
		//switch( stUIData.m_stHead.m_nControlsType[n] )
		//{
		//case Type_Button:
		//	pUIObject = MeNew ControlButton;
		//	break;
		//case Type_CheckBox:
		//	pUIObject = MeNew ControlCheckBox;
		//	break;
		//case Type_Edit:
		//	pUIObject = MeNew ControlEdit;
		//	break;
		//case Type_Text:
		//	pUIObject = MeNew ControlText;
		//	break;
		//case Type_List:
		//	pUIObject = MeNew ControlList;
		//	break;
		//case Type_ListImg:
		//	pUIObject = MeNew ControlListImage;
		//	break;
		//case Type_ScrollBar:
		//	pUIObject = MeNew ControlScrollBar;
		//	break;
		//case Type_ScrollBarEx:
		//	pUIObject = MeNew ControlScrollBarEx;
		//	break;
		//case Type_ComboBox:
		//	pUIObject = MeNew ControlComboBox;
		//	break;
		//case Type_Picture:
		//	pUIObject = MeNew ControlPicture;
		//	break;
		//case Type_Progress:
		//	pUIObject = MeNew ControlProgress;
		//	break;
		//case Type_Tab:
		//	pUIObject = MeNew ControlTab;
		//	break;
		//case Type_ListEx:
		//	pUIObject = MeNew ControlListEx;
		//	break;
		//default:
		//	MESSAGE_BOX("类型超出!")
		//	break;
		//}
		//if ( theUiManager.m_pFocus == NULL && pUIObject->UseFocus() )
		//{
		//	pUIObject->SetActivate();
		//}
		//pUIObject->InitUIData( this, stUIData.m_pstControlData[n] );
		//pUIObject->m_bNeedRelease = true;
		//m_vtChild.push_back( pUIObject );
	}
	
	return stUIData.m_stHead.m_dwCreatedDate;
	unguard;
}

void ControlFrame::AppendChild(ControlObject* pChild)
{
	if(pChild)
		m_vtChild.push_back(pChild);
}

void ControlFrame::RemoveChild( ControlObject* pChild )
{
	std::vector<ControlObject*>::iterator iter = std::find(m_vtChild.begin(), m_vtChild.end(), pChild);
	if (iter != m_vtChild.end())
	{
		m_vtChild.erase(iter);
	}

}

bool ControlFrame::OnMouseLeave()
{
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnMouseMoveLevelName.length() > 0 )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funOnMouseMoveLevelName.c_str()] );
				function_();
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnMouseMoveLevelName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
		return true;
	}
	else
	{
		if( _pOnMouseMoveLevel )
		{
			_pOnMouseMoveLevel( this );

			return true;
		}
	}

	return false;
}

struct SecondFrameGuard
{
	ControlFrame* m_pSecondFrame;

	SecondFrameGuard(ControlFrame* pFrame, ControlFrame* pFatherFrame)
	{
		m_pSecondFrame = pFrame;
		if (m_pSecondFrame)
		{
			m_pSecondFrame->SetFather(pFatherFrame);

			int w  = m_pSecondFrame->GetData()->m_rcRealSize.right - m_pSecondFrame->GetData()->m_rcRealSize.left;
			m_pSecondFrame->GetData()->m_rcRealSize.left = -(m_pSecondFrame->GetData()->m_rcRealSize.right - m_pSecondFrame->GetData()->m_rcRealSize.left) + LeaveSecondFrameDistance;
			m_pSecondFrame->GetData()->m_rcRealSize.right = m_pSecondFrame->GetData()->m_rcRealSize.left + w;
			m_pSecondFrame->SetHeight(pFatherFrame->GetHeight());
			m_pSecondFrame->SetVisable(true);
			ControlObject* pPic = m_pSecondFrame->FindControl("ID_PICTURE_ShopItemWall", pFatherFrame->GetControlID());
			if (pPic)
			{
				// 500为"ID_PICTURE_ShopItemWall"原始的高，590为"ID_FRAME_Trade"原始的高
				pPic->SetHeight(500.0f / 590.0f * pFatherFrame->GetHeight());
			}
		}
	}

	~SecondFrameGuard()
	{
		if (m_pSecondFrame)
		{
			m_pSecondFrame->SetVisable(false);
		}
	}
};

bool ControlFrame::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnMouseMove(nFlags, nX, nY))
			return true;
	}

	bool bUsed = false;
	if ( !m_bMouseLButtonDown/*!GetAsyncKeyState(VK_LBUTTON)*/ )
	{
		m_bLButtonDrag = false;
	}
#ifdef _DEBUG
	if ( /*GetAsyncKeyState(VK_LCONTROL)*/m_bLControlDown && m_bLButtonDrag == true )
	{
		int x = nX - m_ptLBDOffset.x;
		int y = nY - m_ptLBDOffset.y;
		SetPos( x, y );
		return true;
	}
#endif
	if ( ((S_FrameData*)m_pstData)->m_bMoveable == true && m_bLButtonDrag == true )
	{
		int x = nX - m_ptLBDOffset.x;
		int y = nY - m_ptLBDOffset.y;
		if( x < 0 )
		{
			x = 0;
		}
		if( x > SCREEN_WIDTH-m_nWidth )
		{
			x = SCREEN_WIDTH-m_nWidth;
		}
		if( y < 0 )
		{
			y = 0;
		}
		if( y > SCREEN_HEIGHT-m_nHeight )
		{
			y = SCREEN_HEIGHT-m_nHeight;
		}
		//SetPos( x, y );
		if (m_pFather)
			m_pFather->SetPos( x, y );
		else
			SetPos(x, y);

		if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnOnFrameMoveName.length() > 0 )
		{
			try
			{
				LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
				if( table1Obj.IsTable() )
				{
					LuaFunction<void> function_( table1Obj[_funOnOnFrameMoveName.c_str()] );
					function_();
				}
			}
			catch (LuaPlus::LuaException &e)
			{
				char szErr[256] = {0};
				_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnOnFrameMoveName.c_str(), e.GetErrorMessage());
				print_error( szErr );
			}
		}
		else
		{
			if( _pFrameMove )
			{
				_pFrameMove( this );
			}
		}

		return true;
	}
	for( int n = m_vtChild.size()-1; n >= 0; --n )
	{
		if ( m_vtChild[n]->IsVisable() && !m_vtChild[n]->IsSkipAllMsg() )
		{
			if ( m_vtChild[n]->OnMouseMove( nFlags, nX, nY ) == true )
			{
				//test
				return true;
			}
		}
	}
	if ( PtInOnlyFrame(nX,nY) == true )
	{
		if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnMouseMoveOnName.length() > 0 )
		{
			try
			{
				LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
				if( table1Obj.IsTable() )
				{
					LuaFunction<void> function_( table1Obj[_funOnMouseMoveOnName.c_str()] );
					function_();
				}
			}
			catch (LuaPlus::LuaException &e)
			{
				char szErr[256] = {0};
				_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnMouseMoveOnName.c_str(), e.GetErrorMessage());
				print_error( szErr );
			}
		}
		else
		{
			if( _pOnMouseMoveOn )
			{
				_pOnMouseMoveOn( this );
			}
		}


		bUsed =true;
	}

	return bUsed;
}

bool ControlFrame::OnMouseWheel( bool bUp, const int nX, const int nY )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnMouseWheel(bUp, nX, nY))
			return true;
	}

	bool bUsed = false;
	for( int n = m_vtChild.size()-1; n >= 0; --n )
	{
		if ( m_vtChild[n]->IsVisable() && !m_vtChild[n]->IsSkipAllMsg() )
		{
			if ( m_vtChild[n]->OnMouseWheel( bUp, nX, nY ) == true )
			{
				return true;
			}
		}
	}
	return bUsed;
}

bool ControlFrame::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnLButtonDown(nFlags, nX, nY))
			return true;
	}

	bool bUsed = false;
	m_bMouseLButtonDown = true;

	for( int n = m_vtChild.size()-1; n >= 0; --n )
	{
		if ( m_vtChild[n]->IsVisable() && !m_vtChild[n]->IsSkipAllMsg() )
		{
			if ( m_vtChild[n]->OnLButtonDown( nFlags, nX, nY ) == true )
			{
				return true;
				//break;
			}
		}
	}
	if ( bUsed == false && m_bMsgHoldup)
	{
		if ( ControlObject::PtInObject(nX,nY,true) == true )
		{
			if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnClickName.length() > 0 )
			{
				try
				{
					LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
					if( table1Obj.IsTable() )
					{
						LuaFunction<void> function_( table1Obj[_funOnClickName.c_str()] );
						function_();
					}
				}
				catch (LuaPlus::LuaException &e)
				{
					char szErr[256] = {0};
					_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnClickName.c_str(), e.GetErrorMessage());
					print_error( szErr );
				}
			}
			else
			{
				if ( m_pOnClick )
				{
					m_pOnClick( this );
				}
			}

			RECT rc;
			if (m_pFather)
				m_pFather->GetRealRect(&rc);
			else
				GetRealRect( &rc );
			m_bLButtonDrag = true;
			m_ptLBDOffset.x = nX - rc.left;
			m_ptLBDOffset.y = nY - rc.top;

			bUsed = m_bMsgHoldup;
		}
	}
	return bUsed;
}

bool ControlFrame::OnRButtonDown( UINT nFlags, const int nX, const int nY )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnRButtonDown(nFlags, nX, nY))
			return true;
	}

	bool bUsed = false;
	for( int n = m_vtChild.size()-1; n >= 0; --n )
	{
		if ( m_vtChild[n]->IsVisable() && !m_vtChild[n]->IsSkipAllMsg() )
		{
			if ( m_vtChild[n]->OnRButtonDown( nFlags, nX, nY ) == true )
			{
				return true;
			}
		}
	}
	if ( bUsed == false && m_bMsgHoldup)
	{
		if ( ControlObject::PtInObject(nX,nY,true) == true )
		{
			if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnRBtnDownName.length() > 0 )
			{
				try
				{
					LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
					if( table1Obj.IsTable() )
					{
						LuaFunction<void> function_( table1Obj[_funOnRBtnDownName.c_str()] );
						function_();
					}
				}
				catch (LuaPlus::LuaException &e)
				{
					char szErr[256] = {0};
					_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnRBtnDownName.c_str(), e.GetErrorMessage());
					print_error( szErr );
				}
			}
			else
			{
				if( _pOnRBtnDown )
				{
					_pOnRBtnDown( this );
				}
			}

			bUsed = m_bMsgHoldup;
		}
	}
	return bUsed;
}

bool ControlFrame::OnLButtonUp( UINT nFlags, const int nX, const int nY )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnLButtonUp(nFlags, nX, nY))
			return true;
	}

	bool bUsed = false;
	bool bTop  = false;	//是否是顶层窗体
	m_bMouseLButtonDown = false;

	for( int n = m_vtChild.size()-1; n >= 0; --n )	
	{
		if ( m_vtChild[n]->IsVisable() && !m_vtChild[n]->IsSkipAllMsg() )
		{
			if ( m_vtChild[n]->OnLButtonUp( nFlags, nX, nY ) == true )
			{
			//	没有return ,因为有2个界面重叠，并且后面的排序在后面的需要响应的情况发生
			//	return true;
				bTop = true;
				break;
			}
		}
	}

	if ( bTop )	//等到遍历完整的控件后决定是否返回
	{
		return true;
	}

	if ( bUsed == false && m_bMsgHoldup)
	{
 		if ( PtInObject(nX,nY,true) == true )
 		{
 			bUsed = m_bMsgHoldup;
 		}
// 		if ( m_bUseAutoClose )
// 		{
// 			POINT pt={nX,nY};
// 			if ( PtInRect( &m_rcAutoClose, pt) == TRUE )
// 			{
// 				SetVisable( false );
// 				bUsed = m_bMsgHoldup;
// 			}
// 		}
	}
	m_bLButtonDrag = false;
	return bUsed;
}

bool ControlFrame::OnRButtonUp( UINT nFlags, const int nX, const int nY )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnRButtonUp(nFlags, nX, nY))
			return true;
	}

	bool bUsed = false;
	for( int n = m_vtChild.size()-1; n >= 0; --n )
	{
		if ( m_vtChild[n]->IsVisable() && !m_vtChild[n]->IsSkipAllMsg() )
		{
			if ( m_vtChild[n]->OnRButtonUp( nFlags, nX, nY ) == true )
			{
				return true;
			}
		}
	}
	if ( bUsed == false && m_bMsgHoldup)
	{
		if ( ControlObject::PtInObject(nX,nY,true) == true )
		{
			bUsed = m_bMsgHoldup;
		}
	}
	return bUsed;
}

bool ControlFrame::OnLButtonDBClick( UINT nFlags, const int nX, const int nY )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnLButtonDBClick(nFlags, nX, nY))
			return true;
	}

	bool bUsed = false;
	for( int n = m_vtChild.size()-1; n >= 0; --n )
	{
		if ( m_vtChild[n]->IsVisable() )
		{
			if ( m_vtChild[n]->OnLButtonDBClick( nFlags, nX, nY ) == true )
			{
				return true;
			}
		}
	}
	if ( bUsed == false && m_bMsgHoldup)
	{
		if ( PtInObject( nX, nY ,true) == true )
		{
            // 增加回调     added by zhuomeng.hu		[11/26/2010]
            if( m_pOnDBClick )
            {
                if( m_pOnDBClick( this ) )
                    return true;
            }
			bUsed = true;
		}
	}
	return bUsed;
}

bool ControlFrame::OnRButtonDBClick( UINT nFlags, const int nX, const int nY )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnRButtonDBClick(nFlags, nX, nY))
			return true;
	}

	bool bUsed = false;
	for( int n = m_vtChild.size()-1; n >= 0; --n )
	{
		if ( m_vtChild[n]->IsVisable() )
		{
			if ( m_vtChild[n]->OnRButtonDBClick( nFlags, nX, nY ) == true )
			{
				return true;
			}
		}
	}
	if ( bUsed == false && m_bMsgHoldup)
	{
		if ( PtInObject( nX, nY ,true) == true )
		{
			bUsed = true;
		}
	}
	return bUsed;
}

bool ControlFrame::OnKeyDown( UINT nChar )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnKeyDown(nChar))
			return true;
	}

	bool bUsed = false;
	if( nChar == VK_LCONTROL )
		m_bLControlDown = true;

	for( int n = m_vtChild.size()-1; n >= 0; --n )
	{
		if ( m_vtChild[n]->IsVisable() )
		{
			if ( m_vtChild[n]->OnKeyDown( nChar ) == true )
			{
				return true;
			}
		}
	}
	if ( bUsed == false )
	{
		if ( nChar == VK_TAB )
		{
			if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnTabName.length() > 0 )
			{
				try
				{
					LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
					if( table1Obj.IsTable() )
					{
						LuaFunction<void> function_( table1Obj[_funOnTabName.c_str()] );
						function_();
					}
				}
				catch (LuaPlus::LuaException &e)
				{
					char szErr[256] = {0};
					_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnTabName.c_str(), e.GetErrorMessage());
					print_error( szErr );
				}
				return true;
			}
			else
			{
				if( _pOnTab )
				{
					_pOnTab( );
					return true;
				}
			}

			//if( theUiManager.GetFocus() )
			//{
			//	if( theUiManager.GetFocus()->GetControlType() == Type_Edit)	//zizi add 在输入框情况下return 为了 聊天用
			//		return true;
			//}
			// 设置焦点
			for ( UINT n=0; n<m_vtChild.size(); n++ )
			{
				if ( m_vtChild[n]->IsActivated() )
				{
					for ( UINT m = n+1; m<m_vtChild.size(); m++ )
					{
						if( m_vtChild[m]->UseFocus() )
						{
							m_vtChild[m]->SetActivate();
							if (m_vtChild[m]->GetControlType() == Type_Edit)
							{
								ControlEdit* pEdit = (ControlEdit*)m_vtChild[m];
								pEdit->OnTab(NULL);
							}
							return true;
						}
					}
					for ( UINT m = 0; m<n; m++ )
					{
						if( m_vtChild[m]->UseFocus() )
						{
							m_vtChild[m]->SetActivate();
							if (m_vtChild[m]->GetControlType() == Type_Edit)
							{
								ControlEdit* pEdit = (ControlEdit*)m_vtChild[m];
								pEdit->OnTab(NULL);
							}
							return true;
						}
					}
					return true;
				}
			}
		}
	}

	return bUsed;
}

bool ControlFrame::OnKeyUp( UINT nChar )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnKeyUp(nChar))
			return true;
	}

	bool bUsed = false;
	if( nChar == VK_LCONTROL )
		m_bLControlDown = false;

	for( int n = m_vtChild.size()-1; n >= 0; --n )
	{
		if ( m_vtChild[n]->IsVisable() )
		{
			if ( m_vtChild[n]->OnKeyUp( nChar ) == true )
			{
				return true;
			}
		}
    }

    if ( _enableEscKey && (GetArrayMode() == ArrayMode_Top || GetArrayMode() == ArrayMode_SingleModal) && nChar == VK_ESCAPE )
    {
        SetVisable( false );
        return true;
    }

	return bUsed;
}

bool ControlFrame::OnChar( UINT nChar )
{
	SecondFrameGuard SFGuard(m_pSecondFrame, this);

	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsVisable() && m_vtChildFrame[i]->IsEnable() &&
			m_vtChildFrame[i]->OnChar(nChar))
		{
			m_bRedraw=true; //## add by pyj
			return true;
		}
	}

	bool bUsed = false;
	for( int n = m_vtChild.size()-1; n >= 0; --n )
	{
		if ( m_vtChild[n]->IsVisable() )
		{
			if ( m_vtChild[n]->OnChar( nChar ) == true )
			{
				m_bRedraw=true; //## add by pyj
				return true;
			}
		}
	}
	return bUsed;
}

bool ControlFrame::IsChild( IN const ControlObject* pChild )
{
	assert( pChild );
	for ( int n=0; n<m_vtChild.size(); n++ )
	{
		if ( m_vtChild[n] == pChild )
		{
			return true;
		}
	}
	for ( UINT n=0; n<m_vtChild.size(); n++ )
	{
		if ( m_vtChild[n]->IsChild( pChild ) == true )
		{
			return true;
		}
	}
	for( int i = 0; i < m_vtChildFrame.size(); ++ i )
	{
		if( m_vtChildFrame[i]->IsChild( pChild ) == true )
		{
			return true;
		}
	}
	return false;
}

// void ControlFrame::SetAllBlendColor( const int nColor )
// {
// 	SetBlendColor( nColor );
// 	for( UINT nLoop = 0; nLoop<m_vtChild.size(); nLoop++)
// 	{
// 		m_vtChild[nLoop]->SetBlendColor( nColor );
// 	}
// }

//设置全部渐变值
// void ControlFrame::SetAllFadeVal( const int nMaxFade, const int nMinFade )
// {
// 	SetMaxMinFade( nMaxFade, nMinFade );
// 	for( UINT nLoop = 0; nLoop<m_vtChild.size(); nLoop++)
// 	{
// 		m_vtChild[nLoop]->SetMaxMinFade( nMaxFade, nMinFade );
// 	}
// }

// void ControlFrame::SetAllVisable( const bool bVisable)
// {
// 	SetVisable( bVisable);
// 	for ( UINT n=0; n<m_vtChild.size(); n++ )
// 	{
// 		if( !m_vtChild[n]->IsFadeInval() )
// 			m_vtChild[n]->SetVisable( bVisable);
// 	}
// }

void ControlFrame::StartFlash( const int nFlashCount, const bool bAutoClose, const bool bFadeIn )
{
	ControlObject::StartFlash( nFlashCount, bAutoClose, bFadeIn );
	for ( UINT n=0; n<m_vtChild.size(); n++ )
	{
		m_vtChild[n]->StartFlash( nFlashCount, bAutoClose, bFadeIn );
	}
}

void ControlFrame::Create( IN const RECT* pRect, const D3DCOLOR colBack,
							IN funRun pRunFun, IN funRender pRenderFun )
{
	assert( pRect );
	ReleaseUI();
	S_FrameData *pFrame = MeNew S_FrameData;
	m_bNeedRelease = true;
	pFrame->m_nType = Type_Frame;
	sprintf( pFrame->m_szID, "ID_FRAME_AUTO_%d", rand() );
	pFrame->m_rcRealSize = *pRect;
	InitUIData( NULL, pFrame );
	m_colBackColor = colBack;

	//m_bUseAutoClose = true;

	m_pRun = pRunFun;
	m_pRender[EAfterUIRender] = pRenderFun;
}
bool ControlFrame::PtInOnlyFrame( const int x, const int y)
{
	if ( ControlObject::PtInObject(x,y,true) == true )
	{
		return true;
	}
	return false;
}
bool ControlFrame::PtInObject( const int nX, const int nY ,bool bCheckMsgHold)
{
	if ( ControlObject::PtInObject(nX,nY,bCheckMsgHold) == true )
	{
		return true;
	}
	if ( IsVisable() )
	{
		for ( UINT n=0; n<m_vtChild.size(); n++ )
		{
			if( m_vtChild[n]->PtInObject(nX,nY,bCheckMsgHold) == true )
			{
				return true;
			}
		}
	}

	if (m_pSecondFrame)
	{
		m_pSecondFrame->SetVisable(true);
		m_pSecondFrame->SetFather(this);
		bool ret = m_pSecondFrame->PtInObject(nX, nY,bCheckMsgHold);
		m_pSecondFrame->SetVisable(false);
		return ret;
	}

	return false;
}

bool ControlFrame::IsMouseInUI( const int nX, const int nY )
{
	if ( ControlObject::IsMouseInUI(nX,nY) == true )
	{
		return true;
	}
	if ( IsVisable() )
	{
		for ( UINT n=0; n<m_vtChild.size(); n++ )
		{
			if( m_vtChild[n]->IsMouseInUI(nX,nY) == true )
			{
				return true;
			}
		}
	}

	if (m_pSecondFrame)
	{
		m_pSecondFrame->SetVisable(true);
		m_pSecondFrame->SetFather(this);
		bool ret = m_pSecondFrame->IsMouseInUI(nX, nY);
		m_pSecondFrame->SetVisable(false);
		return ret;
	}

	return false;

}

void ControlFrame::SetRenderFun( IN funRender pFun, const bool bBeforeRender )
{
    if( bBeforeRender )
	    m_pRender[EBeforeUIRender] = pFun;
    else
        m_pRender[EAfterUIRender] = pFun;
}

void ControlFrame::SetRenderNeedRedraw( IN funRender pFun, const bool bBeforeRender )
{
    if( bBeforeRender )
        m_pRenderNeedRedraw[EBeforeUIRender] = pFun;
    else
        m_pRenderNeedRedraw[EAfterUIRender] = pFun;
}

UiRender* ControlFrame::GetFrameRender() 
{
	if (NULL == m_pFrameRender)
	{
		m_pFrameRender = new UiRender;
		m_pFrameRender->Initialize();
	}
	return m_pFrameRender;
}

CSmartAniManage* ControlFrame::GetUiAniManageNotNULL() 
{
	if (NULL == m_pUiAniManage)
	{
		m_pUiAniManage = new CSmartAniManage(this);
	}
	return m_pUiAniManage;
}

CExpressionUpdater* ControlFrame::GetExpressionUpdaterNotNULL()
{
	if (NULL == m_pExpressionUpdater)
	{
		m_pExpressionUpdater = new CExpressionUpdater();
	}
	return m_pExpressionUpdater;
}

void ControlFrame::SetRedraw()
{
	m_bRedraw = true;
	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		if (m_vtChildFrame[i]->IsEnable())
		{
			m_vtChildFrame[i]->SetRedraw();
		}
	}
}

void ControlFrame::RemoveChildFrame( ControlFrame* pChild )
{
	std::vector<ControlFrame*>::iterator iter = std::find(m_vtChildFrame.begin(), m_vtChildFrame.end(), pChild);
	if (iter != m_vtChildFrame.end())
	{
		m_vtChildFrame.erase(iter);
	}

}

//void ControlFrame::_renderCallback( bool bAlwaysRender )
//{
//	if( NULL != state.Get() && _luaTableName.length() > 0 && _funRenderName.length() > 0 )
//	{
//		try
//		{
//			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
//			if( table1Obj.IsTable() )
//			{
//				LuaFunction<void> function_( table1Obj[_funRenderName.c_str()] );
//				function_();
//			}
//		}
//		catch (LuaPlus::LuaException &e)
//		{
//			char szErr[256] = {0};
//			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funRenderName.c_str(), e.GetErrorMessage());
//			print_error( szErr );
//		}
//	}
//	else
//	{
//		if( bAlwaysRender )
//		{
//			if( m_pRender )
//            {
//                m_pRender();
//            }
//			else if( m_pRenderIndexedFrame )
//			{
//				m_pRenderIndexedFrame( m_index );
//			}
//		}
//		else
//		{
//			if( m_pRenderNeedRedraw )
//			{
//				m_pRenderNeedRedraw();
//			}
//		}
//	}
//}

void ControlFrame::SetRunFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funRunName = funName;
	unguard;
}
void ControlFrame::SetRenderFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funRenderName = funName;
	unguard;
}
void ControlFrame::SetOnClickFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnClickName = funName;
	unguard;
}
void ControlFrame::SetOnRBtnDown_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnRBtnDownName = funName;
	unguard;
}
void ControlFrame::SetMouseMoveOn_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnMouseMoveOnName = funName;
	unguard;
}
void ControlFrame::SetMouseMoveLevel_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnMouseMoveLevelName = funName;
	unguard;
}
void ControlFrame::SetOnTab_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnTabName = funName;
	unguard;
}
void ControlFrame::SetFrameMove_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnOnFrameMoveName = funName;
	unguard;
}
void ControlFrame::ResetDevice()
{
	SetRedraw();
	ControlObject::ResetDevice();

	for( UINT n=0; n<m_vtChild.size(); n++ )
	{
		m_vtChild[n]->ResetDevice();
	}
}
void ControlFrame::SetEnable( bool b )
{
	for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
	{
		m_vtChildFrame[i]->SetEnable(b);
	}

	ControlObject::SetEnable(b);

	for( UINT n=0; n<m_vtChild.size(); n++ )
	{
		m_vtChild[n]->SetEnable(b);
	}
}


void ControlFrame::SetFather(ControlObject* pFather)
{
	m_pFather = pFather;
	if (m_pFather)
	{
		ControlFrame* pFatherFrame = (ControlFrame*)m_pFather;
		if (std::find(pFatherFrame->m_vtChildFrame.begin(), pFatherFrame->m_vtChildFrame.end(), this) == pFatherFrame->m_vtChildFrame.end())
			pFatherFrame->AddChildFrame(this);
	}
}

void ControlFrame::SetVisable( const bool bVisable)
{
	bool bChanged = m_bVisable != bVisable;
	if (!bChanged)
		return;
	m_bVisable = bVisable;

	if ( m_pOnVisibleChanged && bChanged )
	{
		if (m_bVisable)
		{
			m_pOnVisibleChanged( this );
		}
		else
		{
			if (!m_bFadeInorFadeOut)
			{
				m_pOnVisibleChanged( this );
			}
		}
	}


	if ( m_bFadeInorFadeOut == true )
	{
		m_bInFade = true;
		m_dwFadeLastTime = HQ_TimeGetTime();
		if (bVisable)
		{
			m_nFadeCurColorA = 0;
		}
		else
		{
			m_nFadeCurColorA = 0xFF;
		}
		GetFrameRender()->SetAlpha(m_nFadeCurColorA);
	}

	if( m_bVisable )
	{
		theUiManager.ShowFrame( this );
		theUiManager.ToTop( this );


		ControlFrame* pTradeFrame = (ControlFrame*)theUiManager.FindFrame("ID_FRAME_Trade");
		if (pTradeFrame && this != pTradeFrame && NeedTradeViewerFunc && NeedTradeViewerFunc(this))
		{
			m_pSecondFrame = pTradeFrame;
			m_pSecondFrame->SetFather(this);
		}
		else
			m_pSecondFrame = NULL;
	}
	else
	{
// 		SetRedraw();//隐藏后绘制使用的某些资源可能被释放，所以在重新显示的时候重绘,这个问题解决了
		m_pSecondFrame = NULL;
	}

	theUiManager.Compositor();

	if (!bVisable)
	{
		for (size_t i = 0; i < m_vtChildFrame.size(); ++i)
		{
			m_vtChildFrame[i]->SetVisable(bVisable);
		}
		for( UINT n=0; n<m_vtChild.size(); n++ )
		{
			if (m_vtChild[n]->GetOnVisibleChangedFun())
			{
				m_vtChild[n]->GetOnVisibleChangedFun()(m_vtChild[n]);
			}
		}
	}
}

void ControlFrame::AddPosfixByIndex( int index, char* szID )
{
	if (index >= 0 && index < 100)
	{
		int length = strlen(szID);
		if (length < 61)
		{
			char cIndex[3] = {0};
			sprintf(cIndex,"%d",index);
			szID[length] = cIndex[0];
			szID[length + 1] = cIndex[1];
			szID[length + 2] = '\0';
		}
	}
}

void ControlFrame::SetIndexedFrameRenderFun( IN funRenderIndexedFrame pFun, const bool bBeforeRender )
{
    if( bBeforeRender )
	    m_pRenderIndexedFrame[EBeforeUIRender] = pFun;
    else
        m_pRenderIndexedFrame[EAfterUIRender] = pFun;
}

ControlFrame::NeedTradeViewer ControlFrame::NeedTradeViewerFunc = NULL;