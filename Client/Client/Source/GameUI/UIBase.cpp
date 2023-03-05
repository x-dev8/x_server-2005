#include "UIBase.h"
#include "LuaFuns.h"
#include "SortLuaScript.h"
#include "FuncPerformanceLog.h"
#include "GameMain.h"
#include "PlayerRole.h"
#include "ActionUI.h"
#include "baseProperty.h"
#include "Task.h"
//#include "Guild.h"
#include "Gang.h"
#include "Skill.h"
#include "ErrorLog.h"
#include "GameMain.h"
#include "FriendDlg.h"
#include "ChatInfoBox.h"
// #include "../event_timeable.h"
#include "MiniMap.h"
#include "Shopping_InputBox.h"
#include "Shopping_Messagebox.h"
#include "GroupPanel.h"
#include "Pet.h"
#include "ActivityList.h"
#include "ui/UiTitle.h"
#include "Task_Track.h"
#include "MainMenu.h"
#include "ExMenu.h"
#include "RankList.h"
#include "ShopCenter.h"
#include "customShortcutKey.h"
#include "AutoAttackSet.h"
#include "MoveStar.h"
#include "SpecialRepair.h"
#include "SkillEquipUpdate.h"
#include "SkillEquipChange.h"
#include "ChangeEquip.h"
#include "Action.h"
#include "UIMgr.h"
#include "Player.h"
#include "PlayerAnimCtrl.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Engine/RendererDX.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "wsRender.h"
#include "wsCamera.h"
#include "Me3d/Engine/MeRenderManager.h"

extern LuaStateOwner state;

CUIBase::CUIBase()
{
	guardfunc;
	m_bUILoad = false;
	m_BornTime = 0;
	m_LastVisibleTime = 0;
    m_bLastUiVisable = false;
    CUIMgr::Instance()->AddUIToList(this);
	unguard;
}

CUIBase::CUIBase(int nType)
{
	guardfunc;
	// 这个构造仅仅为不接受ui管理器的Frame提供，一般为menew出来的
	m_bUILoad = false;
	m_BornTime = 0;
	m_LastVisibleTime = 0;
    m_bLastUiVisable = false;
	unguard;  
}

CUIBase::~CUIBase()
{
	guardfunc;
	unguard;
}

// 设置是否可视
void CUIBase::_SetVisable( const bool bVisable )
{
	guardfunc;
#if 0
	int nRet = 2;
	// Param : Type Visable
	int nTopIndex = 0;
	LuaScript *pScript = (LuaScript*)g_GetScript(LUA_UIMAIN);
	if( pScript )
	{
		//pScript->SafeCallBegin(&nTopIndex);
		//pScript->CallFunction( LUAEVENT_ON_VISABLE, nRet, "dd", GetType(), bVisable );
		//pScript->SafeCallEnd(nTopIndex);
		int nVis = bVisable;
			pScript->GetGlobalFun(LUAEVENT_ON_VISABLE)(GetType(), nVis);

		//pScript->GetOwner()->GetGlobal(LUAEVENT_ON_VISABLE);
	}
#endif

	return;
	unguard;
}

//////////////////////////////////////////////////////////////////////////
// 悬停
void CUIBase::OnPoise( int x, int y )
{
	guardfunc;
	return;
	unguard;
}

//////////////////////////////////////////////////////////////////////////
// Mouse Move
void CUIBase::OnMouseMove(int x, int y)
{
	guardfunc;
	return;
	unguard;
}

//////////////////////////////////////////////////////////////////////////
// 左键落下
void CUIBase::OnLButtonDown(int x, int y)
{
	guardfunc;
	return;
	unguard;
}

//////////////////////////////////////////////////////////////////////////
// 左键抬起
void CUIBase::OnLButtonUp(int x, int y)
{
	guardfunc;
	return;
	unguard;
}


//////////////////////////////////////////////////////////////////////////
// 右键落下
void CUIBase::OnRButtonDown(int x, int y)
{
	guardfunc;
	return;
	unguard;
}


//////////////////////////////////////////////////////////////////////////
// 左键抬起
void CUIBase::OnRButtonUp(int x, int y)
{
	guardfunc;
	return;
	unguard;
}

//////////////////////////////////////////////////////////////////////////
// 右键双击
void CUIBase::OnRDBClick(int x, int y)
{
	guardfunc;
	return;
	unguard;

}


//////////////////////////////////////////////////////////////////////////
// 左键双击
void CUIBase::OnLDBClick(int x, int y)
{
	guardfunc;
	return;
	unguard;

}

//////////////////////////////////////////////////////////////////////////
// KeyDown
bool CUIBase::OnKeyDown( WPARAM wParam, LPARAM lParam )
{
	return false;
}

bool CUIBase::OnKeyUp( WPARAM wParam, LPARAM lParam )
{
	return false;
}


void CUIBase::SetVisable( const bool bVisable )
{
	if (bVisable)
	{
		if (!m_bUILoad)
		{
			m_bUILoad = true;
			m_BornTime = HQ_TimeGetTime();
			CUIMgr::Instance()->AddUI(this);
			_LoadUI();
		}
	}
	if (m_bUILoad)
	{
		_SetVisable(bVisable);
	}
}

bool CUIBase::LoadUI()
{
	bool ret = false;
	if (IsHoldInMemory())
	{
		if (!m_bUILoad)
		{
			m_bUILoad = true;
			m_BornTime = HQ_TimeGetTime();
			CUIMgr::Instance()->AddUI(this);
			ret = _LoadUI();
		}
	}
	return ret;
}

bool CUIBase::UnLoadUI()
{
	if (m_bUILoad)
	{
		m_bUILoad = false;
		return _UnLoadUI();
	}
	return false;
}

bool CUIBase::IsVisable()
{
	if (!m_bUILoad)
	{
		return false;
	}
	return _IsVisable();
}
// void CUILayout::SetVisable(ControlFrame* pFrame)
// {
// 
// 	for(int i=0; i<_vecFrame.size(); ++i)
// 	{
// 		if(_vecFrame[i] == pFrame)
// 		{//找到这个窗体
// 			if( !pFrame->IsVisable() )
// 			{//显示这个窗体
// 				switch(_nShowCnt)
// 				{
// 				case 0://将这个窗体显示到第一个的位置
// 					{
// 						_FristShow = pFrame;
// 						++_nShowCnt;
// 
// 						_FristShow->SetVisable(true);
// 					}
// 					break;
// 				case 1://将第一个窗体隐藏 腾出位置 这个窗体显示到第一个的位置
// 					{
// 						if( s_CUI_ID_FRAME_Bargaining.GetFrame() && _FristShow == s_CUI_ID_FRAME_Bargaining.GetFrame())
// 						{
// 							s_CUI_ID_FRAME_Bargaining.SendCancelMsg();
// 						}
// 
// 						if( s_CUI_ID_FRAME_PACK.IsSameFrame(_FristShow) )
// 						{	
// 							s_CUI_ID_FRAME_PACK.showInUILayout( false );
// 						}
// 						else
// 							_FristShow->SetVisable(false);
// 						_FristShow = pFrame;
// 
// 						_FristShow->SetVisable(true);
// 
// 					}
// 					break;
// 				}
// 			}
// 			else
// 			{//隐藏这个窗体
// 				if(pFrame == _FristShow)
// 				{//隐藏 释放第一个位置
// 					if(_nShowCnt == 2)
// 					{
// 						if( !_FristShow || !_FristShow)
// 							return;
// 						if( s_CUI_ID_FRAME_Bargaining.GetFrame() && _FristShow == s_CUI_ID_FRAME_Bargaining.GetFrame())
// 						{
// 							s_CUI_ID_FRAME_Bargaining.SendCancelMsg();
// 						}
// 						_FristShow->SetVisable(false);
// 						//重新排列第二个窗体的位置 走到第一个窗体去
// 						_FristShow = _SecondShow;
// 						--_nShowCnt;
// 
// 						_SecondShow->SetVisable(false);
// 
// 						_FristShow->SetXPos( 4 );
// 
// 						_FristShow->SetYPos( SCREEN_HEIGHT - SCREEN_HEIGHT/2 - SCREEN_HEIGHT*0.35 );
// 
// 						if( s_CUI_ID_FRAME_PACK.IsSameFrame(_FristShow) )
// 						{
// 							s_CUI_ID_FRAME_PACK.showInUILayout( true );
// 						}
// 						else
// 							_FristShow->SetVisable(true);
// 					}
// 					else if(_nShowCnt == 1)
// 					{
// 						if( !_FristShow )
// 							return;
// 
// 						--_nShowCnt;
// 						if( s_CUI_ID_FRAME_Bargaining.GetFrame() && _FristShow == s_CUI_ID_FRAME_Bargaining.GetFrame())
// 						{
// 							s_CUI_ID_FRAME_Bargaining.SendCancelMsg();
// 						}
// 						_FristShow->SetVisable(false);
// 					}
// 				}
// 				else if(pFrame == _SecondShow)
// 				{//隐藏 第二个窗体
// 					if( !_SecondShow )
// 						return;
// 
// 					--_nShowCnt;
// 					if( s_CUI_ID_FRAME_Bargaining.GetFrame() && _SecondShow == s_CUI_ID_FRAME_Bargaining.GetFrame())
// 					{
// 						s_CUI_ID_FRAME_Bargaining.SendCancelMsg();
// 					}
// 					_SecondShow->SetVisable(false);
// 				}
// 			}
// 		}
// 	}
// 	theUiManager.Compositor();
// }

CUIRenderAnim::CUIRenderAnim()
	: mRenderer(0), mPlayer(0), mRotateZ(0.0)
{
	
}

void CUIRenderAnim::RenderAnim_Create(RenderToWhichUI which, float rotate)
{
	if (mPlayer != NULL)
		return;

	mWhichUI = which;
	mRotateZ = rotate;

	mRenderer = GetEngine()->GetRenderer();

	mPlayer = MeNew CPlayer;
	CPlayerAnim *playerAnim = MeNew CPlayerAnim;

	mPlayer->SetAnim(playerAnim);
	playerAnim->SetPlayer(mPlayer);
	theHeroGame.GetPlayerMgr()->AddNoLogicPlayer(mPlayer);
}

void CUIRenderAnim::RenderAnim_Destroy()
{
	if (mPlayer != NULL)
	{
		if (theHeroGame.GetPlayerMgr() != NULL)
		{
			theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer(mPlayer);
			mPlayer->Destroy();

			MeDelete mPlayer;
			mPlayer = NULL;
		}
	}
}

void CUIRenderAnim::RenderAnim_SetModelID(int modelID)
{
	if (mPlayer != NULL && mPlayer->GetAnim() != NULL)
	{
		mPlayer->GetAnim()->MyChangeModel(modelID, FALSE, NULL);
		mPlayer->GetAnim()->SetCurAnimType(-1);
	}	
}

void CUIRenderAnim::RenderAnim_PlayAction(const char *action, int times, const char *nextAction)
{
	if (mPlayer != NULL)
	{
		mPlayer->PlayAnim(action, times, nextAction);
	}
}

void CUIRenderAnim::RenderAnim_RotateReset()
{
	mRotateZ = 0.0;
}

void CUIRenderAnim::RenderAnim_RotateZ(bool isClockwise, float step)
{
	if (isClockwise)
		mRotateZ += step;
	else
		mRotateZ -= step;
}

void CUIRenderAnim::RenderAnim_Update(DWORD x,  DWORD y, DWORD w, DWORD h, const D3DXVECTOR3 &eyePos)
{
	mViewport.X = x;
	mViewport.Y = y;
	mViewport.Width = w;
	mViewport.Height = h;
	mViewport.MinZ = 0.0;
	mViewport.MaxZ = 1.0;

	mCamera.SetProjParams(D3DX_PI / 180 * 45, mViewport.Width / (float) mViewport.Height, 1.0f, 8000.0);
	mCamera.SetViewParams(eyePos, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 1));

	mRenderer->SetTransform(D3DTS_VIEW, (FLOAT *) &mCamera.GetViewMatrix());
	mRenderer->SetTransform(D3DTS_PROJECTION, (FLOAT *) &mCamera.GetProjMatrix());

	Config::SetCamera(&mCamera);
}

void CUIRenderAnim::RenderAnim(const D3DXVECTOR3 &modelPos, float scale)
	{
	if (mPlayer != NULL)
	{
		DWORD dwTime = HQ_TimeGetTime();
		PreRender();
		{
			mRenderer->BeginScene();
			mRenderer->Clear(0, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0, 0);

			mPlayer->GetAnim()->SetScale(scale);
			mPlayer->GetAnim()->SetPosition(modelPos.x, modelPos.y, modelPos.z);
			mPlayer->GetAnim()->SetRotationZ(mRotateZ);
			mPlayer->SetPos(modelPos.x, modelPos.y, modelPos.z);

			D3DXMATRIX transMatrix;
			mPlayer->GetAnim()->CalcTransformMatrix((MeMatrix *) &transMatrix);
			mPlayer->GetAnim()->Update(dwTime, (MeMatrix *) &transMatrix);
			mPlayer->GetAnim()->UpdateComponents(dwTime, (MeMatrix *) &transMatrix);
			int vertCount = 0, faceCount = 0;
			mPlayer->GetAnim()->Render(1.0, NULL, &vertCount, &faceCount, FALSE, TRUE, FALSE, FALSE);

			// update effect
			mPlayer->SetCurUpperDir( mRotateZ - D3DX_PI/2);
			mPlayer->SetLowerDir( mRotateZ - D3DX_PI/2);
			mPlayer->UpdateEffectHelper();
			mPlayer->_UpdateFullStarEffect(0, 0, true, mPlayer->GetAnim()->GetScale());
			//mPlayer->_UpdateFiveElementEffect(true, mPlayer->GetAnim()->GetScale());

			GetEffectMgr()->SetTheLookerPos(mCamera.GetEyePt());
			GetEffectMgr()->SetTheLookerViewDistance(50);
			GetEffectMgr()->Update(dwTime);

			mPlayer->_RenderFullStarEffect();
			//mPlayer->_RenderFiveElement();

			GetEngine()->GetRenderer()->Flush(eSortByFarZ);
			MeRenderManager::Instance()->DoRender(false);
			MeRenderManager::Instance()->DoRender(true);
		}
		PostRender();
	}
}

void CUIRenderAnim::PreRender()
{
	mRenderer->EndScene();

	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) mRenderer->GetRealDevice();

	mOldLodBias = GetMe3dConfig()->GetMipLodBais();
	mOldLight = SwGlobal::GetRender()->GetD9Light();
	device->GetRenderState(D3DRS_ALPHABLENDENABLE, &mOldRS[0]);
	device->GetRenderState(D3DRS_LIGHTING, &mOldRS[1]);
	device->GetRenderState(D3DRS_FOGENABLE, &mOldRS[2]);

	GetMe3dConfig()->SetMipLodBais(-1.2);
	mRenderer->SetViewport(&mViewport);
	mRenderer->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	mRenderer->SetRenderState(D3DRS_LIGHTING, TRUE);
	mRenderer->SetRenderState(D3DRS_FOGENABLE, FALSE);
	mRenderer->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	mRenderer->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	mRenderer->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	D3DLIGHT9 light;
	light.Type = D3DLIGHT_DIRECTIONAL;	
	light.Ambient = D3DXCOLOR(0.3152, 0.3152, 0.3152, 1.0);
	light.Diffuse = D3DXCOLOR(0.3152, 0.3152, 0.3152, 1.0);
	light.Specular = D3DXCOLOR(0.6, 0.6, 0.6, 1.0);
	D3DXVECTOR3 lightDir = D3DXVECTOR3(0.5, 6, -0.5);
	D3DXVec3Normalize(&lightDir, &lightDir);
	light.Direction = lightDir;
	mRenderer->SetLight(LIGHT_INDEX_TERRAIN, (void *) &light);
}

void CUIRenderAnim::PostRender()
{
	GetMe3dConfig()->SetMipLodBais(mOldLodBias);
	mRenderer->SetLight(LIGHT_INDEX_TERRAIN, (void *) &mOldLight);
	mRenderer->SetRenderState(D3DRS_ALPHABLENDENABLE, mOldRS[0]);
	mRenderer->SetRenderState(D3DRS_LIGHTING, mOldRS[1]);
	mRenderer->SetRenderState(D3DRS_FOGENABLE, mOldRS[2]);

	Config::SetCamera(getwsCamera()->GetMeCamera());
	mRenderer->SetTransform(D3DTS_VIEW, (FLOAT *) &getwsCamera()->GetMeCamera()->GetViewMatrix());
	mRenderer->SetTransform(D3DTS_PROJECTION, (FLOAT *) &getwsCamera()->GetMeCamera()->GetProjMatrix());
	getwsCamera()->ResetViewport();

	mRenderer->BeginScene();
}

CUIIntonationUtility::CUIIntonationUtility()
	: mIntonating(false), mIntonateStartTime(0), mIntonatingDuration(0), mCallback(0), mCallbackData(0)
{

}

CUIIntonationUtility::~CUIIntonationUtility()
{
	DestroyCallbackData();
}

void CUIIntonationUtility::IntonationUtility_Start(DWORD duration, const char *name, AFTER_INTONATION callback, void *data, int dataLength)
{
	mIntonating = true;
	mIntonateStartTime = HQ_TimeGetTime();
	mIntonatingDuration = duration;
	s_CUI_Progress.ShowByTime(mIntonateStartTime, mIntonatingDuration, true, 1, true, true, name);
	mCallback = callback;
	mCallbackData = new byte[dataLength];
	memcpy(mCallbackData, data, dataLength);
}

void CUIIntonationUtility::IntonationUtility_Tick()
{
	// 移动或者跳跃都会打断读条
	CPlayer *me = theHeroGame.GetPlayerMgr()->GetMe();
	if (me != NULL)
	{
		if (me->IsMoving() || me->IsJumping())
		{
			mIntonating = false;
			s_CUI_Progress.SetProgressComplete();
		}
	}

	DWORD currentTime = HQ_TimeGetTime();
	// 吟唱结束
	if (mIntonating && currentTime > (mIntonateStartTime + mIntonatingDuration))
	{
		mIntonating = false;
		s_CUI_Progress.SetProgressComplete();

		if (mCallback != NULL)
		{
			mCallback(mCallbackData);
			DestroyCallbackData();
		}
	}
}

void CUIIntonationUtility::DestroyCallbackData()
{
	if (mCallbackData != NULL)
	{
		delete mCallbackData;
		mCallbackData = NULL;
	}
}