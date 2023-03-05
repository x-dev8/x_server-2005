#include <assert.h>
#include "MeUi/UiManager.h"
#include "FirstCREATE.h"
#include "SystemSetting.h"
#include "d3dapp.h"
#include "Browser.h"
#include "MeTerrain/SwDebug.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/STCommon.h"
#include "MeTerrain/SwPublicFunc.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "MeTerrain/NdlRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "wsRender.h"
#include "Me3d/ShaderMgr.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Model/Mex2.h"
#include "Me3d/Shader.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Engine/RendererDX.h"
#include "../Cfg.h"
#include "Me3d/Effect/EffectManager.h"
#include "Create.h"
#include "Common.h"
#include "MeTerrain/STSkyBox.h"
#include "SystemConfig.h"
#include "color_config.h"
#include "GameMain.h"
#include "Me3d\PostProcess\PostProcess.h"
#include "Me3d\PostProcess\PostProcessManager.h"

#include <atlbase.h>
#include <MsHTML.h>
#include <OleIdl.h>

#define SELECT_CAMERA_MEX		"select2.mex"
#define PROCOUNT                5
const char* pszPro[PROCOUNT] = {"zs","ms","fs","ck","lr"};  //职业
const char* pszSex[2]        = {"nan","nv"};

HWND g_hFlashWnd;
void CreateFlashWnd();
void DestryoFlashWnd();

CUI_ID_FRAME_FirstCreate s_CUI_ID_FRAME_FirstCreate;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FirstCreate, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FirstCreate, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FirstCreate, ID_CHECKBOX_WomanOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FirstCreate, ID_CHECKBOX_ManOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FirstCreate, ID_CHECKBOX_JiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FirstCreate, ID_CHECKBOX_DaoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FirstCreate, ID_CHECKBOX_QiangOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FirstCreate, ID_CHECKBOX_JianOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_FirstCreate, ID_CHECKBOX_WuOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FirstCreate, ID_BUTTON_ReturnOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FirstCreate, ID_BUTTON_SelectOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FirstCreate, ID_BUTTON_BackOnButtonClick )

IHTMLDocument2 * GetIDocument2(HWND hWnd)
{
	IWebBrowser2	*webBrowser2;
	IOleObject		*browserObject;

	// Retrieve the browser object's pointer we stored in our window's GWL_USERDATA when
	// we initially attached the browser object to this window.
	browserObject = *((IOleObject **)GetWindowLong(hWnd, GWL_USERDATA));
	browserObject->QueryInterface(IID_IWebBrowser2, (void**) &webBrowser2);

	if (webBrowser2 == NULL)
		return NULL;

	IDispatch *pIDispatch = NULL;
	if (SUCCEEDED(webBrowser2->get_Document(&pIDispatch)) && pIDispatch)
	{
		IHTMLDocument2 *pIDocument2 = NULL;
		if (SUCCEEDED(pIDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&pIDocument2)))
		{
			pIDispatch->Release();
			return pIDocument2;
		}
		pIDispatch->Release();
	}
	return NULL;
}

IDispatch * GetJScript(HWND hWnd)
{
	CComPtr<IHTMLDocument2> doc;  
	doc = GetIDocument2(hWnd);
	if(!doc)
		return NULL;
	IDispatch * dsScript = NULL;
	HRESULT hr = doc->get_Script(&dsScript);
	if(SUCCEEDED(hr) && dsScript)
		return dsScript;
	else
		return NULL;
}

BOOL CallJSFunction(HWND hwnd, LPCTSTR szFunc, VARIANT *vtParams, int cNumberOfParam, VARIANT *vtResult)
{
	if (szFunc == NULL)
		return FALSE;

	CComPtr<IDispatch> spScript;
	spScript = GetJScript(hwnd);
	if (spScript == NULL)
		return FALSE;

	DISPID dispID = NULL;
	CComBSTR bstrFunc(szFunc);
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL, &bstrFunc, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
	if(FAILED(hr))
		return FALSE;

	DISPPARAMS dispParams = {0};
	dispParams.cArgs = cNumberOfParam;
	dispParams.rgvarg = new VARIANT[cNumberOfParam];
	int i = 0;
	for(i = 0; i < cNumberOfParam; ++i)
	{
		VariantInit(&dispParams.rgvarg[i]);
		VariantCopy(&dispParams.rgvarg[i], &vtParams[cNumberOfParam - 1 - i]);
	}
	hr = spScript->Invoke(dispID, IID_NULL, 0, DISPATCH_METHOD, &dispParams, vtResult, NULL, NULL);
	delete [] dispParams.rgvarg;
	if(FAILED(hr))
		return FALSE;
	return TRUE;
}

CUI_ID_FRAME_FirstCreate::CUI_ID_FRAME_FirstCreate()
{
	// Member
	m_pID_FRAME_FirstCreate = NULL;
	m_pID_PICTURE_Bewrite = NULL;
	m_pID_CHECKBOX_Woman = NULL;
	m_pID_CHECKBOX_Man = NULL;
	m_pID_TEXT_ProInfo = NULL;
	m_pID_PICTURE_Spear = NULL;
	m_pID_PICTURE_Sword = NULL;
	m_pID_PICTURE_Fan = NULL;
	m_pID_PICTURE_Bow = NULL;
	m_pID_PICTURE_Staff = NULL;
	m_pID_CHECKBOX_Spear = NULL;
	m_pID_CHECKBOX_Sword = NULL;
	m_pID_CHECKBOX_Fan = NULL;
	m_pID_CHECKBOX_Bow = NULL;
	m_pID_CHECKBOX_Staff = NULL;
	m_pID_BUTTON_Return = NULL;
	m_pID_BUTTON_Select = NULL;
	m_pID_PICTURE_HeiDong = NULL;
	m_pID_PICTURE_Background = NULL;
	m_pID_PICTURE_vedio = NULL;
	m_pID_BUTTON_Back = NULL;

	m_vEye          = D3DXVECTOR3(0,0,0);
	m_vLookat       = D3DXVECTOR3(0,0,1);

	m_bIsTileLoaded = false;

	m_bToCreate = false;
	m_bToSelect = false;

	m_pCameraModel  = NULL;
	memset(m_pPlayerModel,0,sizeof(m_pPlayerModel));

	m_bSex = Sex_Female;

	m_nSelModelIdx = -1;
}

// Frame
bool CUI_ID_FRAME_FirstCreate::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_FirstCreate::OnFrameRender()
{
	MoveToHole(); //更新光圈的位置
	if( SystemSetting::Instance()->IsLowLevelCard() )
	{
		SwGlobal::GetRender()->SetRenderDoodad( false );
		graphics::ShaderManager::instance()->useShader(false);
	}

	IRenderer* RI = GetEngine()->GetRenderer();
	RI->SetRenderState( D3DRS_FOGENABLE, true );

	CWorldBuffer* pbuffer = SwGlobal::GetWorld()->GetWorldBuffer();
	if (pbuffer && !m_bIsTileLoaded)
	{
		/*
		char szSkyMapID[64] = {0};
		MeSprintf_s(szSkyMapID,sizeof(szSkyMapID),"%d",gCfg.m_nSelectPlayerMapId);
		if( GetSTSkyBox() && GetSTSkyBox()->GetSkybox() )
			GetSTSkyBox()->GetSkybox()->ChangeAvatarSetting( szSkyMapID );
		*/

		CWorldTile* pActiveTile = pbuffer->GetTile(gCfg.m_nFirstMapId);
		pbuffer->SetActiveTile(pActiveTile) ;
		m_bIsTileLoaded = true;

		// 获取相机和人物位置
		BOOL bFindCamera = FALSE;
		BOOL bFindCharacter = FALSE;
		BOOL bFindBG = FALSE;

		CResMgr* pResMgr = pActiveTile->GetCResMgr();
		assert( pResMgr );
		char pszName[MAX_PATH] = {0};
		int nCount = 0;
		for (size_t i = 0; i < pResMgr->GetStaticModelList().size(); ++i )
		{
			TObjectInfo* pInfo = pResMgr->GetStaticModel(i);
			if( pInfo->model && pInfo->model->GetMex() )
			{
				strncpy(pszName, pInfo->model->GetMex()->GetFilename(), sizeof(pszName)-1);
				strlwr(pszName);

				if( strstr(pszName, SELECT_CAMERA_MEX))
				{
					m_pCameraModel = pInfo->model;
					//break;
				}

				if(pInfo->model->GetMexCfg())
				{
					MexCfgSequence* pSeq = pInfo->model->GetMexCfg()->GetSequence("single_idle");
					if(pSeq)
						pInfo->model->PlayAnimByName("single_idle",0);
				}

				//保存男女模型指针
				if(strstr(pszName,"nan") || strstr(pszName,"nv"))
				{
					if(nCount < MAX_PLAYER_NUM)
					   m_pPlayerModel[nCount++] = pInfo; 
				}
			}
		}

		if(m_pCameraModel)
			m_pCameraModel->PlayAnimByName("no_no", 0, FALSE); //播放默认相机
	}


	float fOldBias = GetMe3dConfig()->GetMipLodBais();
	GetMe3dConfig()->SetMipLodBais(0);

	// added, jiayi, [2009/8/28], render shadow
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();					
	CShaderMgr* ShaderMgr=GetShaderMgr();
	bool bSupportShadow = false;
	D3DCAPS9 Caps;
	if( FAILED( pDev->GetDeviceCaps( &Caps ) ) )
	{
		return false;
	}

	// Check for vertex/pixel shaders 2.0 support
	if( Caps.VertexShaderVersion < D3DVS_VERSION( 2, 0 ) || Caps.PixelShaderVersion < D3DPS_VERSION( 2, 0 ) )
	{
		bSupportShadow = false;
	}
	else
	{
		bSupportShadow = true;
	}

	int nPlayerIndex = 0;

	float fAspect = (float)SCREEN_WIDTH/SCREEN_HEIGHT;

	BOOL bUpdateCamera = FALSE;
	BOOL bUpdateTarget = FALSE;
	D3DXVECTOR3 vNewCameraPos = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 vNewTargetPos = D3DXVECTOR3(0,0,0);
	if( m_pCameraModel && m_pCameraModel->GetMex() )
	{
		m_pCameraModel->UpdateByParam( HQ_TimeGetTime() );
		for( int nChunk = 0; nChunk < m_pCameraModel->GetMex()->GetGeometry()->GetChunkCount(); nChunk++ )
		{
			Mex2GeoChunk* pChunk = (Mex2GeoChunk*)m_pCameraModel->GetMex()->GetGeometry()->GetChunk(nChunk);
			Vector* vertices = (Vector*)pChunk->GetWorldVertices();
			int nVertexCount = pChunk->GetVertexCount();
			char lwrName[MAX_PATH] = {0};
			const char* pszName = pChunk->GetName();
			strncpy( lwrName, pszName, MAX_PATH-1 );
			strlwr(lwrName);
			if (strstr(lwrName, "selectcamera") )
			{
				pChunk->BlendVertex( m_pCameraModel->GetMex(), (float*)m_pCameraModel->GetMatrices());
				if( nVertexCount > 0 )
				{
					for(int j=0; j<nVertexCount; ++j)
					{
						vNewCameraPos.x += vertices[j].x;
						vNewCameraPos.y += vertices[j].y;
						vNewCameraPos.z += vertices[j].z;
					}
					vNewCameraPos.x /= nVertexCount;
					vNewCameraPos.y /= nVertexCount;
					vNewCameraPos.z /= nVertexCount;
				}
				bUpdateCamera = TRUE;
			}
			else if (strstr(lwrName, "selecttarget") )
			{
				pChunk->BlendVertex( m_pCameraModel->GetMex(), (float*)m_pCameraModel->GetMatrices());
				if( nVertexCount > 0 )
				{
					for(int j=0; j<nVertexCount; ++j)
					{
						vNewTargetPos.x += vertices[j].x;
						vNewTargetPos.y += vertices[j].y;
						vNewTargetPos.z += vertices[j].z;
					}
					vNewTargetPos.x /= nVertexCount;
					vNewTargetPos.y /= nVertexCount;
					vNewTargetPos.z /= nVertexCount;
				}
				bUpdateTarget = TRUE;
			}
			if( bUpdateCamera && bUpdateTarget )
				break;
		}
	}

	m_vEye = vNewCameraPos;
	m_vLookat = vNewTargetPos;
	
	GetMe3dConfig()->GetCamera()->SetViewParams(
		*(D3DXVECTOR3*)&m_vEye,
		*(D3DXVECTOR3*)&m_vLookat,
		D3DXVECTOR3( 0, 0, 1 ) );

	m_Camera.SetViewParams(
		*(D3DXVECTOR3*)&m_vEye,
		*(D3DXVECTOR3*)&m_vLookat,
		D3DXVECTOR3( 0, 0, 1 ) );

	fAspect = (float)SCREEN_WIDTH/SCREEN_HEIGHT;
	m_Camera.SetProjParams( D3DX_PI/4.f, fAspect,  1.0, 18000.0f );

	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&m_Camera.GetViewMatrix() );
	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&m_Camera.GetProjMatrix() );

	RI->SetEyePt( (float*)&m_vEye );
	RI->SetLookatPt( (float*)&m_vLookat );

	FrustumEx frustum;	
	frustum.BuildFrustum( m_Camera.GetProjMatrix(),m_Camera.GetViewMatrix() );

	//render shadow
/*	bool bRenderShadow = ( bSupportShadow 
		&& ShaderMgr->IsCanUseShader() );	*/	

	bool bRenderShadow = false;

	graphics::ShaderManager::instance()->enableShadow(bRenderShadow);

	GetSTSkyBox()->m_bCanRender = TRUE;

	SwGlobal::GetRender()->RenderSkyBox( SwGlobal::GetWorld(), D3DXVECTOR3(64.0f, 41.0f, 4.5f) );		

	GetSTSkyBox()->m_bCanRender = FALSE;

	SwGlobal::GetRender()->RenderWorld( SwGlobal::GetWorld(), frustum, m_vEye, 0, 0 );
	
	if(!m_strMouseAnim.empty())
	{
		for (int i = 0;i < MAX_PLAYER_NUM;++i)
		{
			if (m_pPlayerModel[i] == NULL)
				continue;

			const char* pszName = m_pPlayerModel[i]->model->GetMex()->GetFilename();
			if(m_strMouseAnim.compare(pszName) == 0)
			{
				D3DLIGHT9 light = SwGlobal::GetRender()->GetD9Light(); 
				D3DXCOLOR oldLightAmbient = ((RendererDx*)GetEngine()->GetRenderer())->GetLightAmbient(LIGHT_INDEX_TERRAIN);
				D3DXCOLOR oldLightDiffuse = ((RendererDx*)GetEngine()->GetRenderer())->GetLightDiffuse(LIGHT_INDEX_TERRAIN);
				D3DXCOLOR lightAmbient = oldLightAmbient;
				D3DXCOLOR lightDiffuse = oldLightDiffuse;
				D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, (D3DXVECTOR3*)&light.Direction );

				lightAmbient.a = 1.0f;
				lightAmbient.r = lightAmbient.r * 1.5f;
				lightAmbient.g = lightAmbient.g * 1.5f;
				lightAmbient.b = lightAmbient.b * 1.5f;

				GetEngine()->GetRenderer()->SetLight( LIGHT_INDEX_PLAYER, &light );
				((RendererDx*)GetEngine()->GetRenderer())->SetLightAmbient(LIGHT_INDEX_TERRAIN, lightAmbient);
				((RendererDx*)GetEngine()->GetRenderer())->SetLightDiffuse(LIGHT_INDEX_TERRAIN, lightDiffuse);
				GetEngine()->GetRenderer()->LightEnable(LIGHT_INDEX_PLAYER,TRUE);
				m_pPlayerModel[i]->model->Render(1.0f);

				GetEngine()->GetRenderer()->LightEnable(LIGHT_INDEX_PLAYER,FALSE);
				//设置回去
				((RendererDx*)GetEngine()->GetRenderer())->SetLightAmbient(LIGHT_INDEX_TERRAIN, oldLightAmbient);
				((RendererDx*)GetEngine()->GetRenderer())->SetLightDiffuse(LIGHT_INDEX_TERRAIN, oldLightDiffuse);
			}
		}
	}

	graphics::ShaderManager::instance()->enableShadow(false);

	SwGlobal::GetRender()->RenderLiquid();

	SwGlobal::GetRender()->RenderEffect();

#ifdef _DEBUG
	for (int i = 0;i < MAX_PLAYER_NUM;++i)
	{
		if(m_pPlayerModel[i] != NULL)
			m_pPlayerModel[i]->RenderAABBAndRadius();
	}
#endif

	MeRenderManager::Instance()->DoRender(true);
	RI->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );

	D3DLIGHT9 kLight;
	kLight.Type = D3DLIGHT_DIRECTIONAL;	
	kLight.Ambient = D3DXCOLOR( 1,1,1,1 );
	kLight.Diffuse = D3DXCOLOR( 1,1,1,1 );
	kLight.Specular = D3DXCOLOR( 1,0.6f,0.6f,0.6f );

	RendererDx* pRenderer = (RendererDx*)RI;

	// 渲染人物特效
	GetEffectMgr()->Update( HQ_TimeGetTime() );
	GetEffectMgr()->Render();

	GetEngine()->GetRenderer()->Flush( eSortByFarZ );

	GetMe3dConfig()->SetMipLodBais(fOldBias);

	MeRenderManager::Instance()->DoRender(true);

	RI->SetRenderState( D3DRS_FOGENABLE, false );
	return true;
}

// CheckBox
void CUI_ID_FRAME_FirstCreate::ID_CHECKBOX_WomanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_Woman->SetCheck(true);
	m_pID_CHECKBOX_Man->SetCheck(false);

	//int nIndex = TransLateIndex(m_nCurrSel,false);
	ChangeScene(m_nCurrSel/*nIndex*/,Sex_Female);
}

// CheckBox
void CUI_ID_FRAME_FirstCreate::ID_CHECKBOX_ManOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_Man->SetCheck(true);
	m_pID_CHECKBOX_Woman->SetCheck(false);

	//int nIndex = TransLateIndex(m_nCurrSel,false);
	ChangeScene(m_nCurrSel/*nIndex*/,Sex_Male);
}

// Button
void CUI_ID_FRAME_FirstCreate::ID_CHECKBOX_JiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{//戟
	this->SetManWomanCheckboxState(eManWomanClassState_NvJi);
	m_bSex = false;

	char szWord[265] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s_%s",pszPro[0],pszSex[m_bSex]);
	MoveCameraByIndex(std::string(szWord));
	return;
}

// Button
void CUI_ID_FRAME_FirstCreate::ID_CHECKBOX_DaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	// 刀
	this->SetManWomanCheckboxState(eManWomanClassState_Other);

	char szWord[265] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s_%s",pszPro[1],pszSex[m_bSex]);
	MoveCameraByIndex(std::string(szWord));
	return;
}

// Button
void CUI_ID_FRAME_FirstCreate::ID_CHECKBOX_QiangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	// 枪
	this->SetManWomanCheckboxState(eManWomanClassState_Other);

	char szWord[265] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s_%s",pszPro[2],pszSex[m_bSex]);
	MoveCameraByIndex(std::string(szWord));
	return;
}

// Button
void CUI_ID_FRAME_FirstCreate::ID_CHECKBOX_JianOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	// 剑
	this->SetManWomanCheckboxState(eManWomanClassState_Other);

	char szWord[265] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s_%s",pszPro[3],pszSex[m_bSex]);
	MoveCameraByIndex(std::string(szWord));
	return;
}

// Button
void CUI_ID_FRAME_FirstCreate::ID_CHECKBOX_WuOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	// 舞
	this->SetManWomanCheckboxState(eManWomanClassState_NanWu);
	m_bSex = true;

	char szWord[265] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s_%s",pszPro[4],pszSex[m_bSex]);
	MoveCameraByIndex(std::string(szWord));
	return;
}

// Button
bool CUI_ID_FRAME_FirstCreate::ID_BUTTON_ReturnOnButtonClick( ControlObject* pSender )
{
	m_bToSelect = true;
	return true;
}

// Button
bool CUI_ID_FRAME_FirstCreate::ID_BUTTON_SelectOnButtonClick( ControlObject* pSender )
{
	if(m_nCurrSel == -1)
		return true;

	m_bToCreate = true;
	return true;
}

// Button
bool CUI_ID_FRAME_FirstCreate::ID_BUTTON_BackOnButtonClick( ControlObject* pSender )
{
	m_pID_BUTTON_Select->SetEnable(false); //lyh++
	m_strLastSel = "no";
	m_nCurrSel = -1;
	m_strLastPlayer.clear();
	m_Group.SetVisible(false);
	m_strMouseAnim.clear();

	m_pID_PICTURE_Spear->SetVisable(false);
	m_pID_PICTURE_Sword->SetVisable(false);
	m_pID_PICTURE_Fan->SetVisable(false);
	m_pID_PICTURE_Bow->SetVisable(false);
	m_pID_PICTURE_Staff->SetVisable(false);
	m_pID_BUTTON_Back->SetVisable(false);

	DestryoFlashWnd();
	CreateFlashWnd();

	/*D3DXVECTOR3 vFromPt	 = D3DXVECTOR3( 0.0f, 300.0f, 200.0f );
	D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec	  = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_Camera.SetViewParams(vFromPt,vLookatPt,vUpVec);
	float fAspect = (float)SCREEN_WIDTH/SCREEN_HEIGHT;
	m_Camera.SetProjParams(D3DX_PI/3.0f,fAspect,1.0f,18000.0f);*/

	m_vEye          = D3DXVECTOR3(0,0,0);
	m_vLookat       = D3DXVECTOR3(0,0,1);

	m_bIsTileLoaded = false;

	m_bToCreate = false;
	m_bToSelect = false;

	m_pCameraModel  = NULL;
	memset(m_pPlayerModel,0,sizeof(m_pPlayerModel));

	m_bSex = Sex_Female;

	m_nSelModelIdx = -1;

	return true;
}

// 装载UI
bool CUI_ID_FRAME_FirstCreate::_LoadUI()
{
	PostProcessManager::instance().enableProcess( "Bloom", true );
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FirstCreate.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FirstCreate.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

LRESULT CALLBACK FlashWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
	case WM_CREATE:
		{
			long lstyle = GetWindowLong(hWnd,GWL_STYLE);
			lstyle = WS_OVERLAPPED;
			SetWindowLong(hWnd,GWL_STYLE,lstyle);
			// Embed the browser object into our host window. We need do this only
			// once. Note that the browser object will start calling some of our
			// IOleInPlaceFrame and IOleClientSite functions as soon as we start
			// calling browser object functions in EmbedBrowserObject().
			if ( EmbedBrowserObject( hWnd ) ) return -1;

			return 0; // Success
		}
	case WM_DESTROY:
		{
			// Detach the browser object from this window, and free resources.
			UnEmbedBrowserObject( hWnd );
			g_hFlashWnd = NULL;
			return 0;
		}
	}

	return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
}

void CreateFlashWnd()
{
	if (g_hFlashWnd != NULL)
		return;

	const char FLASH_WINDOW_CLASS_NAME[] = "FlashWindowClsName";

	RECT rcWnd;
	::GetWindowRect(g_hWnd, &rcWnd);
	WNDCLASS wndClass = { CS_HREDRAW | CS_VREDRAW, FlashWndProc, 0, 0, NULL, NULL, LoadCursor(NULL, IDC_ARROW), (HBRUSH) GetStockObject(WHITE_BRUSH), NULL, FLASH_WINDOW_CLASS_NAME };
	::RegisterClass(&wndClass);

	RECT rcPic;
	s_CUI_ID_FRAME_FirstCreate.m_pID_PICTURE_vedio->GetRealRect(&rcPic);
	RECT rcFlashWnd = { 0, 0, s_CUI_ID_FRAME_FirstCreate.m_pID_PICTURE_vedio->GetWidth(),
							  s_CUI_ID_FRAME_FirstCreate.m_pID_PICTURE_vedio->GetHeight()};
	::AdjustWindowRect(&rcFlashWnd, WS_OVERLAPPEDWINDOW, FALSE);

	int nWindowMode = SystemSetting::Instance()->GetLevel( SystemSetting::eSSC_WINDOWMODE );
	if (nWindowMode > 0)
	{
		g_hFlashWnd = ::CreateWindowEx(0, FLASH_WINDOW_CLASS_NAME, _T("UnknownCaption"), WS_OVERLAPPEDWINDOW,
			rcWnd.left + rcPic.left + gCfg.m_noffsizeX, rcWnd.top+ rcPic.top+gCfg.m_noffsizeY, rcFlashWnd.right - rcFlashWnd.left, 
			rcFlashWnd.bottom - rcFlashWnd.top,g_hWnd,NULL, NULL, 0);
	}
	else
	{
		g_hFlashWnd = ::CreateWindowEx(0, FLASH_WINDOW_CLASS_NAME, _T("UnknownCaption"), WS_OVERLAPPEDWINDOW,
			rcWnd.left + rcPic.left, rcWnd.top+ rcPic.top, rcFlashWnd.right - rcFlashWnd.left, 
			rcFlashWnd.bottom - rcFlashWnd.top,g_hWnd,NULL, NULL, 0);
	}	

	LONG lOldWndStyle = ::GetWindowLong(g_hFlashWnd, GWL_STYLE);
	LONG lNewWndStyle = lOldWndStyle & ~(WS_CAPTION | WS_BORDER);
	::SetWindowLong(g_hFlashWnd, GWL_STYLE, lNewWndStyle);
	::SetWindowPos(g_hFlashWnd, NULL, 0, 0, s_CUI_ID_FRAME_FirstCreate.m_pID_PICTURE_vedio->GetWidth(), 
					                        s_CUI_ID_FRAME_FirstCreate.m_pID_PICTURE_vedio->GetHeight(), SWP_NOMOVE | SWP_NOACTIVATE);

	char szFlashPath[MAX_PATH] = {0};
	sprintf_s(szFlashPath, MAX_PATH - 1, "%s/%s", GetRootPath(), "Data/Web/Intro/class_intro.html");
	DisplayHTMLPage(g_hFlashWnd, szFlashPath);

	::SetFocus(g_hWnd);
}

void DestryoFlashWnd()
{
	if (g_hFlashWnd == NULL)
		return;

	RECT rcWnd;
	::GetWindowRect(g_hWnd, &rcWnd);
	DestroyWindow(g_hFlashWnd);
}

void CUI_ID_FRAME_FirstCreate::OnGameWindowMove(int x, int y)
{
	if (g_hFlashWnd == NULL)
		return;

	RECT rcWnd;
	::GetWindowRect(g_hWnd, &rcWnd);
	RECT rcPic;
	s_CUI_ID_FRAME_FirstCreate.m_pID_PICTURE_vedio->GetRealRect(&rcPic);

	int nWindowMode = SystemSetting::Instance()->GetLevel( SystemSetting::eSSC_WINDOWMODE );
	if (nWindowMode > 0)
	{
		::SetWindowPos(g_hFlashWnd, NULL, rcWnd.left + rcPic.left+gCfg.m_noffsizeX, rcWnd.top+rcPic.top+gCfg.m_noffsizeY, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
	}
	else
		::SetWindowPos(g_hFlashWnd, NULL, rcWnd.left + rcPic.left, rcWnd.top+rcPic.top, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
	
}

// 关连控件
bool CUI_ID_FRAME_FirstCreate::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_FirstCreate, s_CUI_ID_FRAME_FirstCreateOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_FirstCreate, s_CUI_ID_FRAME_FirstCreateOnFrameRender, true  );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FirstCreate, ID_CHECKBOX_Woman, s_CUI_ID_FRAME_FirstCreateID_CHECKBOX_WomanOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FirstCreate, ID_CHECKBOX_Man, s_CUI_ID_FRAME_FirstCreateID_CHECKBOX_ManOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FirstCreate, ID_CHECKBOX_Spear, s_CUI_ID_FRAME_FirstCreateID_CHECKBOX_JiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FirstCreate, ID_CHECKBOX_Sword, s_CUI_ID_FRAME_FirstCreateID_CHECKBOX_DaoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FirstCreate, ID_CHECKBOX_Fan, s_CUI_ID_FRAME_FirstCreateID_CHECKBOX_QiangOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FirstCreate, ID_CHECKBOX_Bow, s_CUI_ID_FRAME_FirstCreateID_CHECKBOX_JianOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_FirstCreate, ID_CHECKBOX_Staff, s_CUI_ID_FRAME_FirstCreateID_CHECKBOX_WuOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_FirstCreate, ID_BUTTON_Return, s_CUI_ID_FRAME_FirstCreateID_BUTTON_ReturnOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FirstCreate, ID_BUTTON_Select, s_CUI_ID_FRAME_FirstCreateID_BUTTON_SelectOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FirstCreate, ID_BUTTON_Back, s_CUI_ID_FRAME_FirstCreateID_BUTTON_BackOnButtonClick );

	m_pID_FRAME_FirstCreate = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FirstCreate );
	m_pID_PICTURE_Bewrite = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_PICTURE_Bewrite );
	m_pID_CHECKBOX_Woman = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_CHECKBOX_Woman );
	m_pID_CHECKBOX_Man = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_CHECKBOX_Man );
	m_pID_TEXT_ProInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_TEXT_ProInfo );
	m_pID_PICTURE_Spear = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_PICTURE_Spear );
	m_pID_PICTURE_Sword = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_PICTURE_Sword );
	m_pID_PICTURE_Fan = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_PICTURE_Fan );
	m_pID_PICTURE_Bow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_PICTURE_Bow );
	m_pID_PICTURE_Staff = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_PICTURE_Staff );
	m_pID_CHECKBOX_Spear = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_CHECKBOX_Spear );
	m_pID_CHECKBOX_Sword = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_CHECKBOX_Sword );
	m_pID_CHECKBOX_Fan = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_CHECKBOX_Fan );
	m_pID_CHECKBOX_Bow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_CHECKBOX_Bow );
	m_pID_CHECKBOX_Staff = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_CHECKBOX_Staff );	
	m_pID_BUTTON_Return = (ControlButton*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_BUTTON_Return );
	m_pID_BUTTON_Select = (ControlButton*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_BUTTON_Select );
	m_pID_PICTURE_HeiDong = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_PICTURE_HeiDong );
	m_pID_PICTURE_Background = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_PICTURE_Background );
	m_pID_PICTURE_vedio = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_PICTURE_vedio );
	m_pID_BUTTON_Back = (ControlButton*)theUiManager.FindControl( ID_FRAME_FirstCreate, ID_BUTTON_Back );

	assert( m_pID_FRAME_FirstCreate );
	assert( m_pID_PICTURE_Background);
	assert( m_pID_PICTURE_Bewrite );
	assert( m_pID_CHECKBOX_Woman );
	assert( m_pID_CHECKBOX_Man );
	assert( m_pID_TEXT_ProInfo );
	assert( m_pID_PICTURE_Spear );
	assert( m_pID_PICTURE_Sword );
	assert( m_pID_PICTURE_Fan );
	assert( m_pID_PICTURE_Bow );
	assert( m_pID_PICTURE_Staff );
	assert( m_pID_CHECKBOX_Spear );
	assert( m_pID_CHECKBOX_Sword );
	assert( m_pID_CHECKBOX_Fan );
	assert( m_pID_CHECKBOX_Bow );
	assert( m_pID_CHECKBOX_Staff );
	assert( m_pID_BUTTON_Return );
	assert( m_pID_BUTTON_Select );
	assert( m_pID_PICTURE_HeiDong );
	assert( m_pID_PICTURE_vedio );
	assert( m_pID_BUTTON_Back );

	m_pID_CHECKBOX_Spear->SetShowTip( true );
	m_pID_CHECKBOX_Sword->SetShowTip( true );
	m_pID_CHECKBOX_Fan->SetShowTip( true );
	m_pID_CHECKBOX_Bow->SetShowTip( true );
	m_pID_CHECKBOX_Staff->SetShowTip( true );

	m_pID_PICTURE_Spear->setShowTip( true );
	m_pID_PICTURE_Sword->setShowTip( true );
	m_pID_PICTURE_Fan->setShowTip( true );
	m_pID_PICTURE_Bow->setShowTip( true );
	m_pID_PICTURE_Staff->setShowTip( true );

	if( m_pID_FRAME_FirstCreate )
		m_pID_FRAME_FirstCreate->SetMsgProcFun( MsgProc );

	m_pID_FRAME_FirstCreate->SetWidth( SCREEN_WIDTH );
	m_pID_FRAME_FirstCreate->SetHeight( SCREEN_HEIGHT );


	m_pID_FRAME_FirstCreate->SetOnClickFun(SelectModelLButtonDown);

	SortControl();
	m_bIsTileLoaded = false;

	D3DXVECTOR3 vFromPt	 = D3DXVECTOR3( 0.0f, 300.0f, 200.0f );
	D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec	  = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_Camera.SetViewParams(vFromPt,vLookatPt,vUpVec);
	float fAspect = (float)SCREEN_WIDTH/SCREEN_HEIGHT;
	m_Camera.SetProjParams(D3DX_PI/3.0f,fAspect,1.0f,18000.0f);

	m_strLastSel = "no";  //记录上次选择的模型
	m_nCurrSel = -1;       //当前选择模型
	m_strLastPlayer.clear();

	m_bToCreate = false;
    m_bToSelect = false;

	m_bSex = Sex_Female;

	m_pID_BUTTON_Select->SetEnable(false); //lyh++

	return true;
}

// 卸载UI
bool CUI_ID_FRAME_FirstCreate::_UnLoadUI()
{
	DestryoFlashWnd();

	m_pID_FRAME_FirstCreate = NULL;
	m_pCameraModel = NULL;
	memset(m_pPlayerModel,0L,sizeof(m_pPlayerModel));
	return theUiManager.RemoveFrame( "Data\\UI\\FirstCreate.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_FirstCreate::_IsVisable()
{
	if(!m_pID_FRAME_FirstCreate)
		return false;

	return m_pID_FRAME_FirstCreate->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_FirstCreate::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_FirstCreate)
		return;

	m_pID_PICTURE_HeiDong->SetVisable(false);

	if(bVisable)
	{
		m_strLastSel = "no";
		m_nCurrSel = -1;
		m_strLastPlayer.clear();
		m_Group.SetVisible(false);
		m_strMouseAnim.clear();

		m_pID_PICTURE_Spear->SetVisable(false);
		m_pID_PICTURE_Sword->SetVisable(false);
		m_pID_PICTURE_Fan->SetVisable(false);
		m_pID_PICTURE_Bow->SetVisable(false);
		m_pID_PICTURE_Staff->SetVisable(false);
		m_pID_BUTTON_Back->SetVisable(false);
	}

	m_pID_FRAME_FirstCreate->SetVisable( bVisable );

	if (bVisable)
		CreateFlashWnd();
	else
		DestryoFlashWnd();
}

void CUI_ID_FRAME_FirstCreate::LoadScene()
{

}

std::string CUI_ID_FRAME_FirstCreate::GetPlayAnimBySel()
{
	if (m_pCameraModel == NULL)
		return "";

	std::string strSel("");

	D3DXVECTOR3 vFrom,vDir;
	m_Camera.BuildPickRay( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y, vFrom, vDir, SCREEN_WIDTH, SCREEN_HEIGHT );
	TPickResult castResult;
	if(SwGlobal::GetWorldPicker()->Pick( *(Vector*)&vFrom, *(Vector*)&vDir, castResult, emPT_ObjBBox, false, 1000 ) )
	{
		float fMinDis = 1000.0f;
		Vector vecCameraPos = m_pCameraModel->GetPosition();

		for(int i = 0;i < castResult.pickResultCount;++i)
		{
			TObjectInfo* pModelInfo = castResult.pickResultInfo[i].resultObjInfo;
			if(pModelInfo && pModelInfo->GetAlpha() <= 0.5f)//lyh++ 频繁的点有时候导致角色选择是空的导致 崩溃 
				continue;

			if(!castResult.pickResultInfo[i].resultObjInfo)
				continue;//lyh++ 如上注释

			MexAnimCtrl* pAnimCtrl = castResult.pickResultInfo[i].resultObjInfo->model;
			if(!pAnimCtrl)
				continue;

			IMex* pMex = pAnimCtrl->GetMex();
			if(!pMex)
				continue;

			char pszName[MAX_PATH] = {0};
			strncpy(pszName, pMex->GetFilename(), sizeof(pszName)-1);
			strlwr(pszName);

			for (int nn = 0;nn < PROCOUNT;++nn )
			{
				if(strstr(pszName,pszPro[nn]))
				{
					Vector vec = pAnimCtrl->GetPosition();
					Vector vecLen = vec - vecCameraPos;
					float fLen = vecLen.length();
					if(fLen < fMinDis)
					{
						strSel = pszName;
						fMinDis = fLen;
					}
				}
			}
		}
	}
	
	return std::string(strSel.c_str());
}

int  CUI_ID_FRAME_FirstCreate::PlayerToCamera(const char* pszName)
{
	if(!pszName)
		return 0;

	//装换关系
	//lr_nan ms_nan      = P3
	//lr_nv zs_nv sz_nan = p1
	//ms_nv ck_nan       = p4
	//fs_nan fs_nv ck_nv = p2

	if(strstr(pszName,"lr_nan"))
	{
		return 3;
	}
	else if (strstr(pszName,"lr_nv"))
	{
		return 4;
	}
	else if (strstr(pszName,"ms_nan"))
	{
		return 7;
	}
	else if (strstr(pszName,"ms_nv"))
	{
		return 8;
	}
	else if (strstr(pszName,"zs_nan"))
	{
		return 1;
	}
	else if (strstr(pszName,"zs_nv"))
	{
		return 2;
	}
	else if (strstr(pszName,"fs_nan"))
	{
		return 5;
	}
	else if (strstr(pszName,"fs_nv"))
	{
		return 6;
	}
	else if (strstr(pszName,"ck_nan"))
	{
		return 9;
	}
	else if (strstr(pszName,"ck_nv"))
	{
		return 10;
	}
	/*if(strstr(pszName,"lr_nan") || strstr(pszName,"ms_nan"))
		return 3;
	else if(strstr(pszName,"lr_nv") || strstr(pszName,"zs_nv") || strstr(pszName,"zs_nan"))
		return 1;
	else if(strstr(pszName,"ms_nv") || strstr(pszName,"ck_nan"))
		return 4;
	else if(strstr(pszName,"fs_nan") || strstr(pszName,"fs_nv") || strstr(pszName,"ck_nv"))
		return 2;*/

	return 0;
}

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
void CUI_ID_FRAME_FirstCreate::MoveToHole()
{
	if ( m_nSelModelIdx >= 0 && m_nSelModelIdx < MAX_PLAYER_NUM && m_pPlayerModel[m_nSelModelIdx] )
	{
		int headBoneId = m_pPlayerModel[m_nSelModelIdx]->model->GetMex()->GetSkeleton()->FindBone("Bip01 Head");
		BOOL bRetOk = FALSE;
		Vector vPos = m_pPlayerModel[m_nSelModelIdx]->model->GetBoneWorldPos(headBoneId,&bRetOk);
		if ( bRetOk == TRUE )
		{
			int x = 0;
			int y = 0;
			m_Camera.WorldToScreen( vPos, &x, &y, SCREEN_WIDTH, SCREEN_HEIGHT );

			if( x < 0 )
			{
				x = 0;
			}
			if ( x > SCREEN_WIDTH )
			{
				x = SCREEN_WIDTH;
			}

			if ( y < 0 )
			{
				y = 0;
			}
			
			if ( y > SCREEN_HEIGHT )
			{
				y = SCREEN_HEIGHT;
			}
			

			LocateHole( x, y );
		}
		
	}
	//if(!pszName)
	//	return;

	//if(strstr(pszName,"lr_nan") )
	//{
	//	LocateHole( 472, 216 );
	//}
	//else if(strstr(pszName,"ms_nan"))
	//{
	//	LocateHole( 711, 207 );
	//}
	//else if(strstr(pszName,"lr_nv"))
	//{
	//	LocateHole( 211, 400 );
	//}
	//else if(strstr(pszName,"zs_nv"))
	//{
	//	LocateHole( 571, 234 );
	//}
	//else if(strstr(pszName,"zs_nan"))
	//{
	//	LocateHole( 809, 438 );
	//}
	//else if(strstr(pszName,"ms_nv"))
	//{
	//	LocateHole( 430, 205 );
	//}
	//else if(strstr(pszName,"ck_nan"))
	//{
	//	LocateHole( 681, 248 );
	//}
	//else if(strstr(pszName,"fs_nan"))
	//{
	//	LocateHole( 502, 525 );
	//}
	//else if(strstr(pszName,"fs_nv"))
	//{
	//	LocateHole( 722, 292 );
	//}
	//else if(strstr(pszName,"ck_nv"))
	//{
	//	LocateHole( 530, 137 );
	//}
}

void CUI_ID_FRAME_FirstCreate::LocateHole( int x, int y )
{
	if ( m_pID_PICTURE_HeiDong != NULL )
	{
		int width = m_pID_PICTURE_HeiDong->GetWidth();
		int height = m_pID_PICTURE_HeiDong->GetHeight();
		m_pID_PICTURE_HeiDong->SetPos( x - width / 2, y - height / 2 );
	}
}

void  CUI_ID_FRAME_FirstCreate::PlayControlAnim()
{
	std::string strAnim = GetPlayAnimBySel();
	if(strAnim.empty())
		return;

	MoveCameraByIndex(strAnim);
}

void CUI_ID_FRAME_FirstCreate::ChangeScene(int nIndex,int nSex)
{
	if(nIndex < 0 || nIndex >= PROCOUNT)
		return;

	m_bSex = nSex;

	char szName[256] = {0};
	MeSprintf_s(szName,sizeof(szName),"%s_%s",pszPro[nIndex],pszSex[m_bSex]);

	MoveCameraByIndex(std::string(szName));
// 	char szSrcName[64] = {0};
// 	char szDestName[64] = {0};
// 	if(nSex == Sex_Female)
// 	{
// 	    MeSprintf_s(szSrcName,sizeof(szSrcName),"%s_%s",pszPro[nIndex],"nan");
// 		MeSprintf_s(szDestName,sizeof(szDestName),"%s_%s",pszPro[nIndex],"nv");
// 	}
// 	else if(nSex == Sex_Male)
// 	{
// 		MeSprintf_s(szSrcName,sizeof(szSrcName),"%s_%s",pszPro[nIndex],"nv");
// 		MeSprintf_s(szDestName,sizeof(szDestName),"%s_%s",pszPro[nIndex],"nan");
// 	}
// 	for (int i = 0;i < MAX_PLAYER_NUM;++i)
// 	{
// 		if(m_pPlayerModel[i] != NULL)
// 		{
// 			IMex* pMex = m_pPlayerModel[i]->model->GetMex();
// 			if(!pMex)
// 				continue;
// 
// 			char pszName[MAX_PATH] = {0};
// 			strncpy(pszName, pMex->GetFilename(), sizeof(pszName)-1);
// 			strlwr(pszName);
// 
// 			if(strstr(pszName,szSrcName))
// 				m_pPlayerModel[i]->SetAlpha(0.0f);
// 			else if(strstr(pszName,szDestName))
// 				m_pPlayerModel[i]->SetAlpha(1.0f);
// 
// 		}
// 	}
}

void CUI_ID_FRAME_FirstCreate::MoveCameraByIndex(std::string& strAnim)
{
	if(!m_pPlayerModel)
		return;

	if(m_strLastPlayer.compare(strAnim) == 0)
	{
		if(m_nCurrSel >= 0 && m_nCurrSel < EArmType_MaxSize - 1)
			SetSelCheckBox(m_nCurrSel);

		return;
	}

	m_pID_BUTTON_Select->SetEnable(true); //lyh++


	m_nCurrSel = TransLateIndex(strAnim);

	// 如果连续选中2个都是同一个职业, 则不用重新播放Flash
	bool bNeedChangeSwf = false;
	int pos = strAnim.rfind('\\');
	if (pos != std::string::npos)
	{
		strAnim = strAnim.substr(pos + 1);
	}
	if (strnicmp(strAnim.c_str(), m_strLastPlayer.c_str(), 2) != 0)
		bNeedChangeSwf = true;
	
	if (m_strLastPlayer.empty() || bNeedChangeSwf)
	{
		VARIANT params[1];
		params[0].vt = VT_INT;
		params[0].intVal = m_nCurrSel;
		VARIANT results[1];
		CallJSFunction(g_hFlashWnd, "LoadContent", params, 1, results);
	}
	m_strLastPlayer = strAnim;

	::ShowWindow(g_hFlashWnd, SW_SHOW);

	//角色播放动画
	m_Group.SetVisible(true);

	m_pID_PICTURE_Spear->SetVisable(false);
	m_pID_PICTURE_Sword->SetVisable(false);
	m_pID_PICTURE_Fan->SetVisable(false);
	m_pID_PICTURE_Bow->SetVisable(false);
	m_pID_PICTURE_Staff->SetVisable(false);

	if(m_nCurrSel >= 0 && m_nCurrSel < EArmType_MaxSize - 1)
	{
		if(m_pPic[m_nCurrSel])
			m_pPic[m_nCurrSel]->SetVisable(true);

		SetSelCheckBox(m_nCurrSel);
	}

	if (m_nCurrSel == 0)
		this->SetManWomanCheckboxState(eManWomanClassState_NvJi);
	else if (m_nCurrSel == 4)
		this->SetManWomanCheckboxState(eManWomanClassState_NanWu);
	else
		this->SetManWomanCheckboxState(eManWomanClassState_Other);

	//设置描述
	CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( m_nCurrSel );
	if (pProInfo)
		m_pID_TEXT_ProInfo->SetText( pProInfo->m_strNote.c_str(), Color_Config.getColor( CC_CreateUI_StrNote ) );

	//设置男女控件
	for (int i = 0;i < MAX_PLAYER_NUM;++i)
	{
		if(m_pPlayerModel[i] != NULL)
		{
			IMex* pMex = m_pPlayerModel[i]->model->GetMex();
			if(!pMex)
				continue;

			char pszName[MAX_PATH] = {0};
			strncpy(pszName, pMex->GetFilename(), sizeof(pszName)-1);
			strlwr(pszName);

			if(strstr(pszName,strAnim.c_str()))
			{
				m_nSelModelIdx = i;
				if(m_pPlayerModel[i]->GetAlpha() > 0)
				{
					m_pID_CHECKBOX_Man->SetCheck(false);
					m_pID_CHECKBOX_Woman->SetCheck(false);
					if(strstr(pszName ,"nan"))
					{
						m_pID_CHECKBOX_Man->SetCheck(true);
						m_bSex = Sex_Male;
					}
					else if(strstr(pszName,"nv"))
					{
						m_pID_CHECKBOX_Woman->SetCheck(true);
						m_bSex = Sex_Female;
					}

					PlayAnimByActionName(m_pPlayerModel[i]->model);

					//m_pPlayerModel[i]->model->PlayAnimByName("single_yanwu",0,FALSE);
				}
			}
		}
	}

	int nIndex = PlayerToCamera(strAnim.c_str());
	if(nIndex == 0)
		return;

	//打上光圈
	//m_pID_PICTURE_HeiDong->SetVisable(true);
	MoveToHole();

	//播放相机动画
	char szAnim[64] = {0};
	MeSprintf_s(szAnim,sizeof(szAnim),"p%d",nIndex);

	if(m_strLastSel.compare(szAnim) == 0)
		return;

	MexCfg* pCfg = m_pCameraModel->GetMexCfg();
	if(!pCfg)
		return;

	char szWord[64] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s_%s",m_strLastSel.c_str(),szAnim);
	if(!pCfg->GetSequence(szWord))
		return;
// 	switch (nIndex)
// 	{
// 	case 1:
// 		m_nCurrSel = EArmType_Assassin;
// 		break;
// 	case 2:
// 		m_nCurrSel = EArmType_Hunter;
// 		break;
// 	case 3:
// 		m_nCurrSel = EArmType_Warrior;
// 		break;
// 	case 4:
// 		m_nCurrSel = EArmType_Mage;
// 		break;
// 	case 5:
// 		m_nCurrSel = EArmType_Taoist;
// 		break;
// 	default:
// 		break;
// 	}
	m_pCameraModel->PlayAnimByName(szWord, 0, FALSE);
	m_strLastSel = szAnim;
	m_pID_BUTTON_Back->SetVisable(true);
}

bool CUI_ID_FRAME_FirstCreate::SelectModelLButtonDown(OUT ControlObject* pSender)
{
	s_CUI_ID_FRAME_FirstCreate.PlayControlAnim();
	return true;
}

void CUI_ID_FRAME_FirstCreate::SortControl()
{
	m_Group.Clear();
	m_Group.AddControl(m_pID_PICTURE_Bewrite);
	m_Group.AddControl(m_pID_TEXT_ProInfo);
	m_Group.AddControl(m_pID_CHECKBOX_Man);
	m_Group.AddControl(m_pID_CHECKBOX_Woman);
	m_Group.AddControl(m_pID_PICTURE_Background);

	m_pPic[0] = m_pID_PICTURE_Spear;
	m_pPic[1] = m_pID_PICTURE_Sword;
	m_pPic[2] = m_pID_PICTURE_Fan;
	m_pPic[3] = m_pID_PICTURE_Bow;
	m_pPic[4] = m_pID_PICTURE_Staff;
}

void CUI_ID_FRAME_FirstCreate::PlayAnimByActionName(MexAnimCtrl* pModel)
{
	if(!pModel)
		return;

	pModel->ClearAnims();

	MexAnimCtrl::SPlayTask task0, task1;
	pModel->ResetPlayTask( &task0 );

	const char* szAnimName = "single_yanwu";
	task0.dwOneLoopTime = pModel->GetAnimTimeLength( szAnimName );
	strcpy( task0.szActionname, szAnimName );

	task0.dwLoopTimes = 1;
	task0.dwTimeOut = MexAnimCtrl::eMaxTimeout;
	task0.dwPlayMode = MexAnimCtrl::eNormalPlay;
	task0.dwStartTime = MexAnimCtrl::GetGameTime();
	task0.dwNeedBlendingTime = MexAnimCtrl::eDefaultBlendingTime;
	task0.bLoopPlay = TRUE;

	//设置当前动画
	pModel->PushAnim( &task0 );

	const char* szTargetAnim = "single_idle";
	strcpy( task1.szActionname, szTargetAnim );
	task1.dwOneLoopTime = pModel->GetAnimTimeLength( szTargetAnim );
	task1.dwLoopTimes = MexAnimCtrl::eMaxLoopTimes;
	task1.dwTimeOut = MexAnimCtrl::eMaxTimeout;
	task1.dwPlayMode = MexAnimCtrl::eNormalPlay;
	task1.dwNeedBlendingTime = MexAnimCtrl::eDefaultBlendingTime;
	task1.dwStartTime = task0.dwStartTime + pModel->GetAnimTimeLength( szAnimName );
	task1.bLoopPlay = TRUE;

	pModel->PushAnim( &task1 );
}

int CUI_ID_FRAME_FirstCreate::TransLateIndex(std::string& strPro)
{
	for (int i = 0;i < PROCOUNT;++i)
	{
		if(strstr(strPro.c_str(),pszPro[i]))
			return i;
	}
	return -1;
}

bool CUI_ID_FRAME_FirstCreate::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if(!s_CUI_ID_FRAME_FirstCreate.IsVisable())
		return false;

	switch( msg )
	{
	case WM_MOUSEMOVE:
		{
			std::string strAnim = s_CUI_ID_FRAME_FirstCreate.GetPlayAnimBySel();
			s_CUI_ID_FRAME_FirstCreate.SetMouseMoveAnim(strAnim.c_str());
		}
		break;
	}

	return false;
}

void CUI_ID_FRAME_FirstCreate::SetSelCheckBox(int nIndex)
{
	if(!m_pID_FRAME_FirstCreate)
		return;

	m_pID_CHECKBOX_Spear->SetCheck(false);
	m_pID_CHECKBOX_Sword->SetCheck(false);
	m_pID_CHECKBOX_Fan->SetCheck(false);
	m_pID_CHECKBOX_Bow->SetCheck(false);
	m_pID_CHECKBOX_Staff->SetCheck(false);

	switch(nIndex)
	{
	case 0:
	     m_pID_CHECKBOX_Spear->SetCheck(true);
		break;
	case 1:
	     m_pID_CHECKBOX_Sword->SetCheck(true);
		break;
	case 2:
	     m_pID_CHECKBOX_Fan->SetCheck(true);
		break;
	case 3:
	     m_pID_CHECKBOX_Bow->SetCheck(true);
		break;
	case 4:
		m_pID_CHECKBOX_Staff->SetCheck(true);
		break;
	}
}

void CUI_ID_FRAME_FirstCreate::SetManWomanCheckboxState(eManWomanClassState state)
{
	m_pID_CHECKBOX_Woman->SetEnable(true);
	m_pID_CHECKBOX_Man->SetEnable(true);

	if (state == eManWomanClassState_NvJi)
		m_pID_CHECKBOX_Woman->SetEnable(false);
	else if (state == eManWomanClassState_NanWu)
		m_pID_CHECKBOX_Man->SetEnable(false);
}