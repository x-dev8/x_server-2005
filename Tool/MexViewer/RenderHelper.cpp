#include "StdAfx.h"
#include "RenderHelper.h"

#include "ModelObj.h"
#include "MexViewerApp.h"
#include "Utility.h"
#include "MainFrame.h"
#include "RightWindow.h"
#include "ModelConfigWindow.h"

struct HEADPICPOINT
{
	float x,y,z,w;
	D3DCOLOR color;
	float u,v;
};
#define HEADFVF (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

 LPDIRECT3DTEXTURE9 G_HeadPic = NULL;

 HEADPICPOINT vertex_[4] = 
 {
	 {0.f,0.f,0.f,1.f,0xffffff00,0.f,0.f},
	 {128.f,0.f,0.f,1.f,0xffff00ff,1.f,0.f},
	 {0.f,128.f,0.f,1.f,0xff00ffff,0.f,1.f},
	 {128.f,128.f,0.f,1.f,0xff0000ff,1.f,1.f}
 };




RenderHelper::RenderHelper(HWND hWnd, int w, int h)
{
	ZeroMemory(&mPP, sizeof(D3DPRESENT_PARAMETERS));
	mDevice = NULL;

	mRenderer = NULL;

	mShimmerCollector = NULL;
	mAlphaCollector = NULL;
	mBitSorter = NULL;

	mWidth = w;
	mHeight = h;

	mBackgroundColor = 0xff383838;
	mModelObj = NULL;
	mFramesPerSec = 0;

	this->CreateHardwareDevice(hWnd);
	this->Setup();
}

RenderHelper::~RenderHelper()
{
	Utility_SafeDeleteModel(mModelObj);
	for (std::list<ModelObj *>::iterator iter = mModelCacheLink.begin();
		iter != mModelCacheLink.end();
		++iter)
	{
		Utility_SafeDeleteModel(*iter);
	}

	PostProcessManager::instance().shutdown();
	graphics::ShaderManager::instance()->shutdown();
	MeRenderManager::Release();
	CHRRenderSurface::GlobalDestroy();
	GetEngine()->Release();
	SetEngine(NULL);

	SAFE_RELEASE(mFont);
	SAFE_RELEASE(mDevice);
}

void RenderHelper::Render()
{
	if (mDevice == NULL)
		return;


	this->Update();

	DWORD ret = mRenderer->Clear(0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, mBackgroundColor, 1.0f, 0);

	HRESULT hr = mRenderer->BeginScene();
	if (SUCCEEDED(hr))
	{
		DWORD curTime = HQ_TimeGetTime();
		MeRenderManager::Instance()->DoRender(false);
		{
			this->RenderInfo();
			
			if (gMainFrame->IsShowGrid())
				this->RenderGrid10x10();



			if (mModelObj != NULL)
			{
				mModelObj->Update(curTime);
				//mModelObj->SetAlpha(0.1);
				mModelObj->Render();
				mModelObj->RenderAvatar();

				if (gMainFrame->IsShowSkeleton())
					mModelObj->RenderSkeleton();
				
				if (gMainFrame->IsShowAABB())
					mModelObj->RenderAABBAndRadius();

				if (gMainFrame->IsShowWireframe())
					mModelObj->model->SetRenderFlag(eWireFrame);
				else
					mModelObj->model->SetRenderFlag(0);

				static short index[] = { 0, 1, 2, 2, 1, 3 };
				GetEngine()->GetRenderer()->DirectPushSurface(
					gMainFrame->GetRightWindow()->GetModelConfigWnd()->TextureID,
					-1, 
					OBJECT2D_SHADER, 
					HEADFVF,
					sizeof( HEADPICPOINT ), 
					(BYTE*)vertex_,
					4,
					(BYTE*)index,
					2, eLinearFilter|eLightingDisable );
			
			}
		}
		mRenderer->Flush(eSortByFarZ);
		MeRenderManager::Instance()->DoRender(true);

		mRenderer->EndScene();

		if (false)
		{
			PostProcessManager::instance().ScretchRectToTexture();

			RendererDx *rdx = (RendererDx *) mRenderer;
			PostProcessManager::instance().setParameter( "View",  rdx->GetViewMatrix() );
			PostProcessManager::instance().setParameter( "WorldViewProjection",  rdx->GetWorldViewProjection() );
			PostProcessManager::instance().setParameter( "LightPosition", mLight.Position);
			PostProcessManager::instance().setParameter( "LightDirection", mLight.Direction);
			PostProcessManager::instance().setParameter( "CameraPos", rdx->GetEyePt() );
			PostProcessManager::instance().render();
		}

		mDevice->Present(0, 0, 0, 0);
	}
}

ModelObj * RenderHelper::AppendModelToCacheLink(const wxString &path)
{
	// 先从缓冲链表中取
	// 由于左右手装配同一件武器的事, 暂时去掉从缓冲链表中取的功能
	/*for (std::list<ModelObj *>::iterator iter = mModelCacheLink.begin(); iter != mModelCacheLink.end(); ++iter)
	{
		if ((*iter)->GetFilePath() == path)
		{
			return (*iter);
		}
	}*/

	if (mModelCacheLink.size() > RH_MAX_CACHE_MODEL_OBJ)
	{
		for (int i = 0; i < 10; ++i)
		{
			ModelObj *mo = mModelCacheLink.front();
			Utility_SafeDeleteModel(mo);
			mModelCacheLink.pop_front();
		}
	}
	
	ModelObj *mo = MeNew ModelObj(this, false);
	mo->LoadFromFile(path.mb_str());
	mModelCacheLink.push_back(mo);
	return mo;
}

void RenderHelper::PlayCurrentModelByAnimName(const char *anim)
{
	if (mModelObj == NULL)
		return;

	mModelObj->model->PlayAnimByName(anim, 0);
}

void RenderHelper::RotateCurrentModelAndGrid(const wxPoint &delta)
{
	if (mModelObj == NULL)
		return;
	
	Vector rot;
	mModelObj->model->GetRotation(rot.x, rot.y, rot.z);
	rot.x += delta.y * 0.003;
	rot.z += delta.x * 0.003;

	Utility_WriteDebugInfoToConsole("x: %f, z: %f\n", rot.x, rot.z);

	mModelObj->model->SetRotationX(rot.x);
	mModelObj->model->SetRotationY(rot.y);
	mModelObj->model->SetRotationZ(rot.z);
	mModelObj->ApplyTransform();

	mModelObj->model->CalcTransformMatrix((MeMatrix *) (FLOAT *) &mWorldMatrix);
}

void RenderHelper::MoveCurrentModel(const wxPoint &delta)
{
	Vector pos = mModelObj->model->GetPosition();
	pos.x += delta.x * 0.1;
	pos.y -= delta.y * 0.1;

	mModelObj->model->SetPosition(pos);
	mModelObj->ApplyTransform();
}

void RenderHelper::ReloadCurrentModel()
{
	if (mModelObj == NULL)
		return;

	std::string filePath = mModelObj->GetFilePath();
	float oldScale = mModelObj->GetScale();
	Utility_SafeDeleteModel(mModelObj);

	mModelObj = MeNew ModelObj(this);
	if (!mModelObj->LoadFromFile(filePath.c_str()))
	{
		MeDelete mModelObj;
		mModelObj = NULL;

		wxMessageBox(wxT("加载模型失败"));		
	}
	mModelObj->SetScale(oldScale);
	mModelObj->ApplyTransform();
}

void RenderHelper::AdjustCameraFarAwayOrComeClose(const wxMouseEvent &evt)
{
	int rot = evt.GetWheelRotation();
	int lines = rot / evt.GetWheelDelta();
	// lines < 0: 远离观察点
	bool farAway = lines < 0;

	float delta = farAway ? -120 : 120;
	delta *= 3;
	
	Vector deltaPos;
	deltaPos.x	= delta / 32.0f;
	deltaPos.y  = 0.0f;
	deltaPos.z	= 0.0f;

	Vector pos = mCamera.GetPos();
	D3DXVECTOR3 dDir = mCamera.GetDir();
	Vector kDir;
	kDir.x = dDir.x;
	kDir.y = dDir.y;
	kDir.z = dDir.z;
	pos	+= kDir * deltaPos.x;

	mCamera.SetPos(pos);
	mCamera.Update(0.0f, 0.0f);
}

void RenderHelper::AdjustCamera(const wxPoint &delta, bool rotate)
{
	if (rotate) 
	{
		// 旋转摄像机
		Vector deltaRot;
		deltaRot.x	= delta.y / mHeight * PI;
		deltaRot.y  = 0.0f;
		deltaRot.z	= delta.x / mWidth * PI;
		deltaRot += mCamera.GetRot();
		mCamera.SetRot(deltaRot);
		mCamera.Update(0.0f, 0.0f);
	}
	else 
	{
		// 移动摄像机
		Vector deltaPos;
		deltaPos.x	= -delta.x / mWidth * 64.0f;
		deltaPos.y	= delta.y / mHeight * 64.0f;
		deltaPos.z  = 0.0f;
		if (deltaPos.x > 100.0f)
			deltaPos.x = 100.0f;

		if (deltaPos.y > 100.0f)
			deltaPos.y = 100.0f;

		Vector pos = mCamera.GetPos() + deltaPos;

		// Get the inverse view matrix
		D3DXMATRIX m;
		D3DXMatrixInverse(&m, NULL, &mCamera.GetViewMatrix());

		Vector worldPos;
		worldPos.x  = deltaPos.x*m._11 + deltaPos.y*m._21 + deltaPos.z*m._31;
		worldPos.y  = deltaPos.x*m._12 + deltaPos.y*m._22 + deltaPos.z*m._32;
		worldPos.z  = deltaPos.x*m._13 + deltaPos.y*m._23 + deltaPos.z*m._33;
		worldPos.x = m._41 + worldPos.x;
		worldPos.y = m._42 + worldPos.y;
		worldPos.z = m._43 + worldPos.z;

		mCamera.SetPos(worldPos);
		mCamera.Update(0.0f, 0.0f);
	}
}

void RenderHelper::SetLighting(bool useDefault)
{
	if (useDefault)
	{
		GetDefaultLightParam(mLight);
	}
	mRenderer->LightEnable(0, TRUE);
	mRenderer->SetLight(0, &mLight);
	mRenderer->SetRenderState(D3DRS_LIGHTING, TRUE);
}

bool RenderHelper::CreateHardwareDevice(HWND hWnd)
{
	IDirect3D9 *d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d9 == NULL)
		return false;

	D3DDISPLAYMODE displayMode;
	d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	D3DADAPTER_IDENTIFIER9 adapterIdentifier;
	d3d9->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &adapterIdentifier);
	mVideoCard = Utility_ANSIToUnicode(adapterIdentifier.Description);

	ZeroMemory(&mPP, sizeof(mPP));
	mPP.BackBufferWidth = mWidth;
	mPP.BackBufferHeight = mHeight;
	mPP.BackBufferFormat = displayMode.Format;
	mPP.BackBufferCount = 1;
	mPP.MultiSampleType = GetBestAvailableMultiSampleType(d3d9, displayMode.Format);
	mPP.MultiSampleQuality = 0;
	mPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	mPP.hDeviceWindow = hWnd;
	mPP.Windowed = TRUE;
	mPP.EnableAutoDepthStencil = TRUE;
	mPP.AutoDepthStencilFormat = D3DFMT_D24S8;
	mPP.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	mPP.Flags = 0;

	if (FAILED(d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &mPP, &mDevice)))
	{
		SAFE_RELEASE(d3d9);
		wxMessageBox(wxT("创建设备失败!"));
		return false;
	}

	SAFE_RELEASE(d3d9);
	return true;
}

void RenderHelper::Setup()
{
	// 设置引擎
	SetEngine(new CEngineInstance);
	mRenderer = GetEngine()->GetRenderer();
	mRenderer->SetDevice(mDevice);
	
	GetEngine()->GetTextureManager()->StartTextureLoadingThread();
	GetEngine()->UseAbstractPath(FALSE);
	GetEngine()->UseTextureMultiThreadLoading(FALSE);
	GetEngine()->SetEffectMirror(FALSE);	// 特效不要镜像

	// 设置视口
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = mWidth;
	vp.Height = mHeight;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	mRenderer->SetViewport(&vp);

	mShimmerCollector = MeNew MeShimmerCollector;
	mShimmerCollector->SetEnable(true);

	mAlphaCollector = MeNew MeAlphaCollector;
	mBitSorter = MeNew MeBitSorter;

	MeRenderManager::Instance()->AddCollector(mShimmerCollector);
	MeRenderManager::Instance()->AddCollector(mAlphaCollector);
	MeRenderManager::Instance()->SetSorter(mBitSorter);

	SetRootPath("");

#ifdef MEXVIEWER_PUBLISH
	wxString appFolder = ((MexViewerApp *) wxTheApp)->GetExeFolder();
#else
	wxString appFolder = wxT("D:\\g2_res\\Client\\WorldEditor");//wxGetCwd();
#endif

	int pos = appFolder.rfind(wxT('\\'));
	wxString clientFolder = appFolder.Left(pos);

	graphics::ShaderManager::instance()->initialize(mDevice);
	graphics::ShaderManager::instance()->LoadFxShader(clientFolder.mb_str());
	graphics::ShaderManager::instance()->enableSkeletonShader(true);

	GetShaderMgr()->Enable(true);
	GetShaderMgr()->InitShader();
	GetShaderMgr()->SetBlurVal(0.3f);
	GetShaderMgr()->SetBrightVal(0.5f);
	GetShaderMgr()->SetWaterType(eShadow_RealTime);

	// 全屏特效默认关闭
	{		
		wxString quadFolder = wxString::Format(wxT("%s\\DATA\\SHADER\\PostProcess\\"), clientFolder);
		PostProcessManager::instance().initialize(mDevice, (quadFolder + wxT("Quad.fxo")).mb_str(), true);
		PostProcessManager::instance().enablePostProcess(true);
		//PostProcessManager::instance().restoreDeviceObjects(mDevice, mWidth, mHeight);

		// 全屏泛光
		BloomPostProcessEffect *bloomPost = MeNew BloomPostProcessEffect("Bloom");		
		bloomPost->create(mDevice, quadFolder.mb_str());
		bloomPost->enable(false);
		PostProcessManager::instance().addPostProcessEffect(bloomPost);

		// 体积光
		LightShaftProcessEffect *lightShaftPost = MeNew LightShaftProcessEffect("LightShaft");
		lightShaftPost->create(mDevice, quadFolder.mb_str());
		lightShaftPost->enable(false);
		PostProcessManager::instance().addPostProcessEffect(lightShaftPost);
	}

	this->SetLighting(true);
	this->CameraSetup();

	CHRRenderSurface::GlobalInitialize();

	GetMe3dConfig()->SetRenderHelper((Config::ERenderHelper) gMainFrame->GetCurrentRenderHelper());
	// 设置为工具模式
	GetMe3dConfig()->SetToolMode(TRUE);

	// 销毁当前模型
	Utility_SafeDeleteModel(mModelObj);

	D3DXMatrixIdentity(&mWorldMatrix);

	D3DXCreateFont(mDevice, 14, 0,  FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &mFont);
}

void RenderHelper::CameraSetup()
{
	mCamera.Create();
	mCamera.SetPos(Vector(0, -202, 142));
	mCamera.SetProjectionMatrix(mWidth, mHeight);
	mRenderer->SetTransform(D3DTS_PROJECTION, (const FLOAT *) &mCamera.GetProjMatrix());
}

D3DMULTISAMPLE_TYPE RenderHelper::GetBestAvailableMultiSampleType(LPDIRECT3D9 d3d9, D3DFORMAT fmt)
{
	D3DMULTISAMPLE_TYPE bestMultiSampleType = D3DMULTISAMPLE_16_SAMPLES;
	for (int i = 16; i >= 2; --i)
	{
		bestMultiSampleType = (D3DMULTISAMPLE_TYPE) i;
		if (SUCCEEDED(d3d9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, fmt, TRUE, bestMultiSampleType, NULL)))
		{
			break;
		}
	}

	if (bestMultiSampleType == D3DMULTISAMPLE_2_SAMPLES)
		bestMultiSampleType = D3DMULTISAMPLE_NONE;
	return bestMultiSampleType;
}

void RenderHelper::GetDefaultLightParam(D3DLIGHT9 &light)
{
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient.a = 1; light.Ambient.r = 0.5; light.Ambient.g = 0.5; light.Ambient.b = 0.5;
	light.Diffuse.a = 1; light.Diffuse.r = 0.31; light.Diffuse.g = 0.31; light.Diffuse.b = 0.31;
	light.Specular.a = 0.2; light.Specular.r = 0.3; light.Specular.g = 0.3; light.Specular.b = 0.3;
	light.Position = D3DXVECTOR3(-2.8, 1.6, -2.2);
	light.Direction = light.Position;
	light.Range = 10000;
	light.Falloff = 1;
	light.Attenuation0 = 0.0;
	light.Attenuation1 = 0.7;
	light.Attenuation2 = 0.03;
}

void RenderHelper::Update()
{
	if (mDevice == NULL)
		return;

	// 更新世界矩阵
	mRenderer->SetTransform(D3DTS_WORLD, (CONST FLOAT *) &mWorldMatrix);

	// 更新摄像机
	mCamera.Update(0, 0);
	mRenderer->SetTransform(D3DTS_VIEW, (const FLOAT *) &mCamera.GetViewMatrix());

	mRenderer->SetEyePt((float *) &mCamera.GetEye());
	mRenderer->SetLookatPt((float *) &mCamera.GetLookAt());
}

void RenderHelper::RenderInfo()
{
	static DWORD temp = 0;
	static DWORD elapsedTime = 0;

	DWORD now = ::GetTickCount();
	DWORD delta = now - mLastTime;
	if (elapsedTime > 1000)
	{
		mFramesPerSec = temp;

		temp = 0;
		elapsedTime = 0;
	}
	else
	{
		++temp;
		elapsedTime += delta;
	}
	mLastTime = now;

	static wchar_t buffer[128] = {0};
	swprintf_s(buffer, 127, L"%s FPS: %d", mVideoCard.c_str(), mFramesPerSec);

	RECT rcText = { 2, 2, 0, 0 };
	mFont->DrawText(NULL, buffer, -1, &rcText, DT_NOCLIP | DT_CALCRECT, 0);
	mFont->DrawText(NULL, buffer, -1, &rcText, DT_NOCLIP | DT_SINGLELINE, 0xFF3EBCEF);
}

void RenderHelper::RenderGrid10x10()
{
	static const int size = GRID_SIZE / 4;
	static const int step = GRID_SIZE / 20;

	/*
	 * 2012.6.16 wangshuai 解决了辅助线一暗一亮的问题
	 * 由于是固定管线, Pixel Shader输出的值不一定就是最终像素颜色, 因为各种渲染状态操作会对颜色值产生影响
	 * 如果是用Shader写, Pixel Shader输出的值就是Final Frame Buffer Color
	 */
	mRenderer->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	for (int i = 0; i < 11; ++i)
	{
		GetDrawer()->DrawLine3D(
			D3DXVECTOR3(-size, size - i*step, 0),
			D3DXVECTOR3( size, size - i*step, 0),
			i != 5 ? 0xff7f7f7f : 0xff222222);
	}

	for (int i = 0; i < 11; ++i)
	{
		GetDrawer()->DrawLine3D(
			D3DXVECTOR3(-size + i*step,  size, 0),
			D3DXVECTOR3(-size + i*step, -size, 0),
			i != 5 ? 0xff7f7f7f : 0xff222222);
	}
}

ModelObj * RenderHelper::SetCurrentModel(const wxString &path)
{
	if (mDevice == NULL)
		return NULL;

	Utility_SafeDeleteModel(mModelObj);

	mModelObj = MeNew ModelObj(this);
	if (!mModelObj->LoadFromFile(path.mb_str()))
	{
		SAFE_DELETE(mModelObj);
		wxMessageBox(wxT("加载模型失败"));		
		return NULL;
	}
	return mModelObj;
}