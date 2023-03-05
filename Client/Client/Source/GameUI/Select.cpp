/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Select.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Select.h"
#include "Create.h"
#include "Login.h"
#include "MessageBox.h"
#include "Player.h"
#include "..\playerequip.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "AvatarSystemSetting.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Engine/Engine.h"
#include "SystemConfig.h"
#include "../Cfg.h"
#include "MeAudio/MeAudio.h"
#include "XmlStringLanguage.h"
#include "../color_config.h"
#include "MeTerrain/STSkyBox.h"
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
#include "LoadMap.h"
#include "SystemSetting.h"
#include "core/Name.h"
#include "UserData.h"
#include "Me3d/Model/Mex2.h"
#include "Me3d/Shader.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Engine/RendererDX.h"
#include "GameMain.h"
#include "Common.h"
#include "DeleteCase.h"
#include "CountryFunction.h"
#include "SoundConfig.h"
#include "PlayerInfoMgr.h"
#include "ItemHero.h"
#include "Me3d\PostProcess\PostProcess.h"
#include "Me3d\PostProcess\PostProcessManager.h"
#include "ExitGame.h"
#include "ChangeName.h"
#include "SelectChannel.h"
#include "GuildGeneralBattleList.h"

extern char* GetFullFileName(const char* filename);
extern bool isShowDisconnetMsg;

#define SELECT_CAMERA_MEX		"select.mex"
#define SELECT_CAMERA_MODEL		"selectcamera"
#define SELECT_CAMERA_TARGET	"selecttarget"
#define SELECT_CHARACTOR_MEX	"character.mex"
//#define SELECT2_CAMERA_MEX		"select2.mex"

extern void SetAllEquip(int iProfession, int iSex,  CPlayer_SEquipment* pEquip, SCharVisual* pVisual, CPlayer* pPlayer ,bool isShowHero,int& source_hair,int& source_face);
extern bool g_bCloseApp;
extern short GetKeyboardInput( int iKey );
extern int g_nCharacterDBID;
extern BOOL g_bMultiThreadLoadingMex; //多线程加载MEX
extern GAME_STATE	g_GameState;
extern BOOL g_bIsEnteringWorld;
static D3DXVECTOR3 g_eye(61.0f, 36.45f, 6.3f), g_lookat(66.5f, 44.0f, 7.3f);

BOOL	g_bCreateOk = FALSE;



static char* GetFullFileName(const char* filename)
{
    static char strFullName[MAX_PATH] = {0};
    if (filename)
    {
        MeSprintf_s(strFullName, sizeof(strFullName)-1, "%s\\%s", GetRootPath(), filename);
        return strFullName;
    }
    return NULL;
}


time_t CUI_ID_FRAME_Select::m_time = 0;
int CUI_ID_FRAME_Select::m_CurrentSelectIndex = -1;
bool CUI_ID_FRAME_Select::m_IsSetCameraForCreate = false;
CUI_ID_FRAME_Select s_CUI_ID_FRAME_Select;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Select, OnFrameRun)
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Select, OnFrameRender)
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_Select,ID_BUTTON_CREATEOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_Select,ID_BUTTON_ENTEROnButtonClick)
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_Select,ID_BUTTON_DELETEOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_Select,ID_BUTTON_LEAVEOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_Select,ID_BUTTON_RESTOREOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Select, ID_BUTTON_PLAYER0OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Select, ID_BUTTON_PLAYER1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Select, ID_BUTTON_PLAYER2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Select, ID_BUTTON_PLAYER3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Select, ID_BUTTON_PLAYER4OnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Select, ID_CHECKBOX_PLAYER0OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Select, ID_CHECKBOX_PLAYER1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Select, ID_CHECKBOX_PLAYER2OnCheckBoxCheck )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Select, ID_LIST_PLAYEROnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Select, ID_CHECKBOX_KEYBDOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Select, ID_CHECKBOX_MOUSEOnCheckBoxCheck )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Select, ID_BUTTON_UpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Select, ID_BUTTON_DownOnButtonClick )
static bool TurnOnLButtonDown( INT nX, INT nY )
{
    s_CUI_ID_FRAME_Select.SetRotateValue(true);
    return true;
}

static bool TurnOnLButtonUp( INT nX, INT nY )
{
    s_CUI_ID_FRAME_Select.SetRotateValue(false);
    return true;
}

bool EnterWorldFailed(const char bPressYesButton, void *pData)
{
    if (!bPressYesButton)
    {
        if (s_CUI_ID_FRAME_MessageBox.IsTimeOut())
        {
            s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_EnterGame_Error), "", 
                CUI_ID_FRAME_MessageBox::eTypeConfirm, true ,CUI_ID_FRAME_ExitGame::BackToLogin);
			s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
			s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);

			isShowDisconnetMsg = true;
        }
        if( !g_bIsEnteringWorld )
        {
            s_CUI_ID_FRAME_Select.SetButEnableOnEnter(true);
            s_CUI_ID_FRAME_Select.SetEnterWorldState(false);
        }
        else
            g_bIsEnteringWorld = FALSE;
    }
    return true;
}

bool DeletePlayer( const char bPressYes, void *pData )
{
    guardfunc;
    if( bPressYes != 0 )
    {
        int* pnIndex = (int*)pData;

        if ( *pnIndex >= 0 && *pnIndex < MAX_PLAYER_COUNT )
        {
            if(!s_CUI_ID_FRAME_Select.GetDel(*pnIndex))
            {
                MsgDeleteChar msg;
                msg.stWhichSlot = s_CUI_ID_FRAME_Select.GetSlotByIndex(*pnIndex);
                GettheNetworkInput().SendMsg( &msg,msg.GetLength() );
            }
            else
            {
                MsgCancelDelChar cancel;
                cancel.stWhichSlot = s_CUI_ID_FRAME_Select.GetSlotByIndex(*pnIndex);
                GettheNetworkInput().SendMsg( &cancel, cancel.GetLength() );
                //GettheNetworkInput().CheckSendReq();
            }
            return true;
        }
    }
    return false;
    unguard;
}

CUI_ID_FRAME_Select::CUI_ID_FRAME_Select()
{
    // SGuildMember
    m_pID_CHECKBOX_KEYBD = NULL;	//键盘控制
    m_pID_CHECKBOX_MOUSE = NULL;	//鼠标控制

    m_pID_FRAME_SELECT = NULL;
    m_pID_BUTTON_CREATE = NULL;
    m_pID_BUTTON_ENTER = NULL;
    m_pID_BUTTON_DELETE = NULL;
    m_pID_BUTTON_LEAVE = NULL;
    m_pID_BUTTON_RESTORE = NULL;
    m_pID_TEXT_NAME = NULL;
    m_pID_TEXT_LEVEL = NULL;
    m_pID_TEXT_Job = NULL;
    m_pID_TEXT_BIRTHDAY = NULL;
    m_pID_TEXT_LastIP = NULL;
    m_pID_TEXT_LastTime = NULL;
    m_pID_TEXT_LastPlace = NULL;
    m_pID_LIST_PLAYER = NULL;

	m_pID_BUTTON_PLAYER0 = NULL;
	m_pID_BUTTON_PLAYER1 = NULL;
	m_pID_BUTTON_PLAYER2 = NULL;
	m_pID_BUTTON_PLAYER3 = NULL;
	m_pID_BUTTON_PLAYER4 = NULL;

	m_pID_CHECKBOX_PLAYER0 = NULL;
	m_pID_CHECKBOX_PLAYER1 = NULL;
	m_pID_CHECKBOX_PLAYER2 = NULL;

    m_pID_BUTTON_Left = NULL;
    m_pID_BUTTON_Right = NULL;
	m_pID_TEXT_COUNTRY = NULL;		//added by zhuomeng.hu		[8/20/2010]
	m_pID_TEXT_currectsever = NULL;	//added by zhuomeng.hu		[8/20/2010]

	m_pID_TEXT_DeleteInfo0 = NULL;
	m_pID_TEXT_DeleteInfo1 = NULL;
	m_pID_TEXT_DeleteInfo2 = NULL;

    m_bToLogin = false;
    m_bToCreate = false;
    m_nControlMode = 0;


    m_pRenderPlayer = NULL;

    for (int i = 0; i < MAX_PLAYER_COUNT;++i )
    {
        m_pID_PICTURE_CreateBg[i] = NULL;
        m_bIsDel[i] = false;
        m_bSlotIsUsed[i] = false;
        m_pPlayerAnim[i] = NULL;
		m_dwDelTime[i] = 0;
		m_pPlayer[i] = NULL;
		m_EffectID[i] = -1;
    }
    ZeroMemory(m_bSlotCharacterID,sizeof(m_bSlotCharacterID));

    m_nSlotEmpty = 0;
    m_bUpdateOnce = FALSE;
    //m_vPlayerPos	=	D3DXVECTOR3(0,0,0);
	memset(m_vPlayerPos,0,sizeof(m_vPlayerPos));
	memset(m_fPlayerRotate,0,sizeof(m_fPlayerRotate));
    m_pCameraModel = NULL;
	m_pBGModel		= NULL;
    m_pDoorModel = NULL;
    m_bMoveCamera = TRUE;
    m_bMoveBackCamera = FALSE;
    m_bForceUpdateCamera = FALSE;
    m_vCameraStartPos = Vector(0,0,0);
    m_dwCameraStartMoveTime = 0;
    m_bPlayCameraAnim = FALSE;

    m_pCamera = NULL;

	m_fPlayerBaseScale = 1.f;

    m_OldSelPlayerList = -1;

    m_vEye   = D3DXVECTOR3(45.f, 11.f, 6.9f);
    m_vLookat=D3DXVECTOR3(66.5f, 44.5f, 5.8f);


	m_RotateZ = 0;

    m_bIsTileLoaded = false;
    m_bRotate = false;
    m_bNeedSetLastLogin = true;
    m_bNeedReadUserData = true;
    ZeroMemory(m_pszLastLoginRole,sizeof(m_pszLastLoginRole));

    m_nEnterWorldCount = 3;
    m_isEnterWorld = false;

    m_strLastIp.clear();
    m_strLastAddress.clear();
    m_strLastTime.clear();

	m_pID_TEXT_PageInfo= NULL;
	m_pID_BUTTON_Up= NULL;
	m_pID_BUTTON_Down= NULL;



	m_strLastSel = "no";
    m_nCurrSel = -1;
    m_Group.Clear();

	m_PlayerInfoList.m_NowPage = 0;
}

ControlFrame* CUI_ID_FRAME_Select::GetFrame() { return m_pID_FRAME_SELECT; }

void CUI_ID_FRAME_Select::Release()
{
    guardfunc;
    for( int i = 0; i < MAX_PLAYER_COUNT; i++ )
    {
        if( m_pPlayerAnim[i] )
        {
            m_pPlayerAnim[i]->Destroy();
            delete m_pPlayerAnim[i];
            m_pPlayerAnim[i] = NULL;
        }

		if(m_pPlayer[i])
		{
         delete m_pPlayer[i];
		 m_pPlayer[i] = NULL;

		}


		IEffect *pEffect = GetEffectMgr()->GetEffect(m_EffectID[i] ); //销毁之前的特效
		if (pEffect)
		{
			pEffect->SetDead();
			m_EffectID[i] = -1;
		}
		
    }

    for( int i=0; i<MAX_PLAYER_COUNT;i++)
    {
        m_bSlotIsUsed[i] = FALSE;
    }
    unguard;
}

void CUI_ID_FRAME_Select::LoadScene()
{
    // 加载场景
    CWorldBuffer* pbuffer = SwGlobal::GetWorld()->GetWorldBuffer();
    if (pbuffer && !m_bIsTileLoaded )
    {
//         char pszSelectScene[MAX_PATH] = {0};
//         MeSprintf_s(pszSelectScene, sizeof(pszSelectScene)-1, "%s\\%s.mew", gCfg.m_pszSelectSceneName, gCfg.m_pszSelectSceneName);
//         pbuffer->SetMaxTileCacheNum(2);             // 如果从游戏返回选人界面，需要设置cache地图个数

		// change skybox
		/*char szSkyMapID[64] = {0};
		MeSprintf_s(szSkyMapID,sizeof(szSkyMapID),"%d",gCfg.m_nSelectPlayerMapId);
		if( GetSTSkyBox() && GetSTSkyBox()->GetSkybox() )
			GetSTSkyBox()->GetSkybox()->ChangeAvatarSetting( szSkyMapID );*/

		pbuffer->SetActiveTile(pbuffer->GetTile(gCfg.m_nSelectPlayerMapId));
        m_bIsTileLoaded = true;

        // 获取相机和人物位置
        BOOL bFindCamera = FALSE;
        BOOL bFindCharacter = FALSE;
		BOOL bFindBG = FALSE;

        CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
        if( pTile )
        {
            CResMgr* pResMgr = pTile->GetCResMgr();
            assert( pResMgr );
            if( pResMgr )
            {
                char pszName[MAX_PATH] = {0};
                for (size_t i = 0; i < pResMgr->GetStaticModelList().size(); ++i )
                {
                    TObjectInfo* pInfo = pResMgr->GetStaticModel(i);
                    if( pInfo->model && pInfo->model->GetMex() )
                    {
                        strncpy(pszName, pInfo->model->GetMex()->GetFilename(), sizeof(pszName)-1);
                        strlwr(pszName);
                        if( strstr(pszName, "character1"/*SELECT_CHARACTOR_MEX*/) )
                        {
							SetAnimPos(0,pInfo);
                            //bFindCharacter = TRUE;
                        }
						else if(strstr(pszName,"character2"))
						{
							SetAnimPos(1,pInfo);
						}
						else if(strstr(pszName,"character3"))
						{
							SetAnimPos(2,pInfo);
						}
// 						else if(strstr(pszName,"character4"))
// 						{
// 							SetAnimPos(3,pInfo);
// 						}
// 						else if(strstr(pszName,"character5"))
// 						{
// 							SetAnimPos(4,pInfo);
// 						}
                        else if( strstr(pszName, SELECT_CAMERA_MEX))
                        {
                            m_pCameraModel = pInfo->model;
                            bFindCamera = TRUE;
                        }
						/*else if( strstr(pszName, SELECT2_CAMERA_MEX))
						{
							m_pCameraModel = pInfo->model;
							bFindCamera = TRUE;
						}*/
						//else if( strstr(pszName, "selectbg.mex"))
						//{
						//	m_pBGModel = pInfo->model;
						//	if( m_pBGModel->GetMexCfg()->GetSequence("idle") )
						//	{
						//		m_pBGModel->PlayAnimByName("idle", 0, TRUE);
						//	}
						//	bFindBG = TRUE;
						//}
						//if( bFindCharacter && bFindCamera /*&& bFindBG*/)
						//	break;
                    }
                }

				if(m_pCameraModel)
			         m_pCameraModel->PlayAnimByName("no_no", 0, FALSE); //播放默认相机
            }
        }

        m_bPlayCameraAnim = TRUE;
    }
}

// Frame
bool CUI_ID_FRAME_Select::OnFrameRun()
{
    guardfunc;
    if( !m_bUpdateOnce )
	{
		if (m_time != 0)
		{
			//         m_time = 0;
			m_pID_TEXT_LastIP->SetText(m_strLastIp);
			m_pID_TEXT_LastTime->SetText(m_strLastTime);
			m_bUpdateOnce = TRUE;
		}
	}

    return true;
    unguard;
}

bool CUI_ID_FRAME_Select::OnFrameRender()
{
    guardfunc;

	if( !m_bIsTileLoaded )
	{
		LoadScene();
	}
	if (m_IsSetCameraForCreate && m_CurrentSelectIndex != -1 &&  _IsVisable())
	{
		PlayAnimByIndex(m_CurrentSelectIndex);
		Refeash(m_CurrentSelectIndex-1);
		m_IsSetCameraForCreate = false;
		m_CurrentSelectIndex = -1;
	}
    if( SystemSetting::Instance()->IsLowLevelCard() )
    {
        SwGlobal::GetRender()->SetRenderDoodad( false );
        graphics::ShaderManager::instance()->useShader(false);			
    }

    IRenderer* RI = GetEngine()->GetRenderer();
    RI->SetRenderState( D3DRS_FOGENABLE, true );

    float fOldBias = GetMe3dConfig()->GetMipLodBais();
    GetMe3dConfig()->SetMipLodBais(0);

    // 加载场景挪到LoadScene函数里，在LoadUI时执行
    if( m_bPlayCameraAnim )
    {
        m_bPlayCameraAnim = FALSE;
        // 播放场景动画
    }

    // render shadow
    LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();					
    CShaderMgr* ShaderMgr=GetShaderMgr();
    bool bSupportShadow = false;
    D3DCAPS9 Caps;
    if( FAILED( pDev->GetDeviceCaps( &Caps ) ) )
    {
        return false;
    }

    // Check for vertex/pixel shaders 2.0 support
    if (Caps.VertexShaderVersion < D3DVS_VERSION( 2, 0 ) || Caps.PixelShaderVersion < D3DPS_VERSION(2, 0))
        bSupportShadow = false;
    else
        bSupportShadow = true;

    ControlList::S_List *pstList = m_pID_LIST_PLAYER->GetCurSelItem();
    int nPlayerIndex = 0;
	for (int n = 0;n < MAX_PLAYER_COUNT;++n)
    {
        int nIndex = n;;
        nPlayerIndex = nIndex;
        if( m_pPlayerAnim[nIndex] )
        {
            D3DXMATRIX matTransform;
            m_pPlayerAnim[nIndex]->SetPosition(*((Vector*)&m_vPlayerPos[nIndex]));
			m_pPlayerAnim[nIndex]->SetScale(PlayerInfoMgr::Instance()->GetScale4SelectUI(m_stPlayerInfo[nIndex].aptotic.ucSex, m_fPlayerScale[nIndex]));

            if (m_bRotate && m_pID_BUTTON_Left->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
            {
                m_RotateZ -= 1.5f * theHeroGame.GetFrameElapsedTime();
            }
            else if (m_bRotate && m_pID_BUTTON_Right->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
            {
                m_RotateZ += 1.5f * theHeroGame.GetFrameElapsedTime();
            }
            else
                m_bRotate = false;

            m_pPlayerAnim[nIndex]->SetRotationZ(m_fPlayerRotate[nIndex]);

            m_pPlayerAnim[nIndex]->CalcTransformMatrix( (MeMatrix*)&matTransform );
            m_pPlayerAnim[nIndex]->Update( HQ_TimeGetTime(), (MeMatrix*)&matTransform );	
            m_pPlayerAnim[nIndex]->UpdateComponents( HQ_TimeGetTime(), (MeMatrix*)&matTransform );

        }
    }

    if (bSupportShadow && ShaderMgr && ShaderMgr->IsCanUseShader())
    {
		D3DXVECTOR3 vEyeAt = m_pCamera->GetEyePt();
		D3DXVECTOR3 vLookat = m_pCamera->GetLookatPt();
		D3DXVECTOR3 vViewDir = m_pCamera->GetViewDir();
		RendererDx* pMeRenderer = (RendererDx*)GetEngine()->GetRenderer();
		D3DXVECTOR3 vLightDir = pMeRenderer->GetLightDir( LIGHT_INDEX_TERRAIN );
		graphics::ShaderManager::instance()->beginRenderShadow(vEyeAt, vLookat, vViewDir, vLightDir);
		for (int i = 0;i < MAX_PLAYER_COUNT;++i)
		{
			if(m_pPlayerAnim[i])
			{
				m_pPlayerAnim[i]->RenderShadow();
			}
		}
		MeRenderManager::Instance()->DoRender(false);
		graphics::ShaderManager::instance()->endRenderShadow();
    }

    float fAspect = (float)SCREEN_WIDTH/SCREEN_HEIGHT;
	if (m_bMoveBackCamera && m_pCameraModel )
	{
		m_bMoveBackCamera = FALSE;
	}
	{
		BOOL bUpdateCamera = FALSE;
		BOOL bUpdateTarget = FALSE;
		D3DXVECTOR3 vNewCameraPos = D3DXVECTOR3(0,0,0);
		D3DXVECTOR3 vNewTargetPos = D3DXVECTOR3(0,0,0);
		if (m_pCameraModel && m_pCameraModel->GetMex())
		{
			m_pCameraModel->UpdateByParam( HQ_TimeGetTime() );
			for (int nChunk = 0; nChunk < m_pCameraModel->GetMex()->GetGeometry()->GetChunkCount(); nChunk++ )
			{
				Mex2GeoChunk* pChunk = (Mex2GeoChunk*)m_pCameraModel->GetMex()->GetGeometry()->GetChunk(nChunk);
				Vector* vertices = (Vector*)pChunk->GetWorldVertices();
				int nVertexCount = pChunk->GetVertexCount();
				char lwrName[MAX_PATH] = {0};
				const char* pszName = pChunk->GetName();
				strncpy( lwrName, pszName, MAX_PATH-1 );
				strlwr(lwrName);
				if (strstr(lwrName, SELECT_CAMERA_MODEL) )
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
				else if (strstr(lwrName, SELECT_CAMERA_TARGET) )
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
	}

	GetMe3dConfig()->GetCamera()->SetViewParams(
		*(D3DXVECTOR3*)&m_vEye,
		*(D3DXVECTOR3*)&m_vLookat,
		D3DXVECTOR3( 0, 0, 1 ) );

	m_pCamera->SetViewParams(
		*(D3DXVECTOR3*)&m_vEye,
		*(D3DXVECTOR3*)&m_vLookat,
		D3DXVECTOR3( 0, 0, 1 ) );

	m_pCamera->SetProjParams( D3DX_PI/4.f, fAspect,  1.0, 18000.0f );
	FrustumEx frustum;
	frustum.BuildFrustum( m_pCamera->GetProjMatrix(),m_pCamera->GetViewMatrix() );

	RI->SetEyePt( (float*)&m_vEye );
	RI->SetLookatPt( (float*)&m_vLookat );

	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&m_pCamera->GetViewMatrix() );
	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&m_pCamera->GetProjMatrix() );

	// render shadow
	bool bRenderShadow = bSupportShadow && ShaderMgr->IsCanUseShader();

	graphics::ShaderManager::instance()->enableShadow(bRenderShadow);

	GetSTSkyBox()->m_bCanRender = TRUE;
	SwGlobal::GetRender()->RenderSkyBox( SwGlobal::GetWorld(), D3DXVECTOR3(64.0f, 41.0f, 4.5f) );		
	GetSTSkyBox()->m_bCanRender = FALSE;

	SwGlobal::GetRender()->RenderWorld( SwGlobal::GetWorld(), frustum, m_vEye, 0, 0 );

	graphics::ShaderManager::instance()->enableShadow(false);
	SwGlobal::GetRender()->RenderLiquid();

	SwGlobal::GetRender()->RenderEffect();
	MeRenderManager::Instance()->DoRender(true);

	RI->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );
	for (int n = 0; n < MAX_PLAYER_COUNT;++n )
	{
		if(m_pPlayerAnim[n])
		{
			if(n == m_nMouseIndex)
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
				m_pPlayerAnim[n]->Render();

				GetEngine()->GetRenderer()->LightEnable(LIGHT_INDEX_PLAYER,FALSE);
				//设置回去
				((RendererDx*)GetEngine()->GetRenderer())->SetLightAmbient(LIGHT_INDEX_TERRAIN, oldLightAmbient);
				((RendererDx*)GetEngine()->GetRenderer())->SetLightDiffuse(LIGHT_INDEX_TERRAIN, oldLightDiffuse);
			}
			else
		       m_pPlayerAnim[n]->Render();
		}
	}
	GetEngine()->GetRenderer()->Flush( eSortByFarZ );
	GetMe3dConfig()->SetMipLodBais(fOldBias);
	MeRenderManager::Instance()->DoRender(true);


//==========================================
	//LYH选人界面加入强化特效
	for (int n = 0; n < MAX_PLAYER_COUNT;++n )
	{
		if(m_pPlayer[n])
		{
			if(m_pPlayer[n]->GetAnim() && m_pPlayer[n]->GetAnim()->GetMex())
			{
				if(m_pPlayer[n]->GetAnim()->GetMex()->GetSkeleton())
				{
					int _nSpineBoneID =     m_pPlayer[n]->GetAnim()->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine1" );
					int _nRightHandBoneID = m_pPlayer[n]->GetAnim()->GetMex()->GetSkeleton()->FindBone( "Bip01 R Finger11" );
					int _nLeftHandBoneID =  m_pPlayer[n]->GetAnim()->GetMex()->GetSkeleton()->FindBone( "Bip01 L Finger11" );
					int _nBackBoneID =      m_pPlayer[n]->GetAnim()->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine2" );

					m_pPlayer[n]->SetSpineBoneID(_nSpineBoneID) ;
					m_pPlayer[n]->SetRightHandBoneID(_nRightHandBoneID);
					m_pPlayer[n]->SetLeftHandBoneID(_nLeftHandBoneID);
					m_pPlayer[n]->SetBackBoneID(_nBackBoneID);

				    m_pPlayer[n]->SetCurUpperDir(m_fPlayerRotate[n] - D3DX_PI/2);
					m_pPlayer[n]->SetLowerDir(m_fPlayerRotate[n] - D3DX_PI/2);


				}
			}
			m_pPlayer[n]->UpdateEffectHelper();

			m_EffectID[n] = m_pPlayer[n]->GetEffectID();
		}
	}


	GetEffectMgr()->SetTheLookerPos( m_vEye );
	GetEffectMgr()->Update( HQ_TimeGetTime() );
	GetEffectMgr()->Render();
	GetEngine()->GetRenderer()->Flush( eSortByFarZ );
	GetMe3dConfig()->SetMipLodBais(fOldBias);
    MeRenderManager::Instance()->DoRender(true);
//==========================================

    RI->SetRenderState( D3DRS_FOGENABLE, false );
	
    return true;
    unguard;
}
// Button
bool CUI_ID_FRAME_Select::ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender )
{
    guardfunc;
	if( !m_pID_FRAME_SELECT )
		return false;
	if(m_PlayerInfoList.m_PlayerList.size() >= MAX_PLAYER_COUNT)
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(ePlayerCountIsFull) );
		return false;
	}
	int nUse = 0;
    for( int n=0; n<MAX_PLAYER_COUNT; n++ )
    {
        if( m_bSlotIsUsed[n] == false )
        {
            m_nSlotEmpty = n;
            m_bToCreate = true;
			if(s_CUI_ID_FRAME_ChangeName.IsVisable())
				s_CUI_ID_FRAME_ChangeName.SetVisable(false);
            return true;
        }
        else
        {
            nUse++;
        }
    }		
    s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(ePlayerCountIsFull) );
    return false;
    unguard;
}

// Button
bool CUI_ID_FRAME_Select::ID_BUTTON_ENTEROnButtonClick( ControlObject* pSender )
{
    guardfunc;
	if( !m_pID_FRAME_SELECT )
		return false;

    // 重新计数
    if (pSender)
        m_nEnterWorldCount = 3;

    m_nControlMode = 2;
 
//    ControlList::S_List *pstList = m_pID_LIST_PLAYER->GetCurSelItem();
//    if ( pstList )
//    {
//        int nIndex = pstList->m_nID;
	   if(m_nCurrSel != -1)
	   {
		  EnterGame(m_nCurrSel);
	   }

//    }
    return false;
    unguard;
}

// Button
bool CUI_ID_FRAME_Select::ID_BUTTON_DELETEOnButtonClick( ControlObject* pSender )
{
    guardfunc;
	if( !m_pID_FRAME_SELECT )
		return false;
    ControlList::S_List *pstList = m_pID_LIST_PLAYER->GetCurSelItem();
    if ( pstList )
    {
		s_CUI_ID_FRAME_DeleteCase.SetVisable(true);
        return true;
    }
    return false;
    unguard;
}

// Button
bool CUI_ID_FRAME_Select::ID_BUTTON_RESTOREOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SELECT )
		return false;

	if(m_nCurrSel == -1)
		return false;

    int nIndex = m_nCurrSel;
    //确定恢复此玩家
    s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_CancelDel_Check),
        theXmlString.GetString(eUI_ask),
        CUI_ID_FRAME_MessageBox::eTypeYesNo, true,
        DeletePlayer, &nIndex, sizeof(nIndex) );
    return true;
}

// Button
bool CUI_ID_FRAME_Select::ID_BUTTON_LEAVEOnButtonClick( ControlObject* pSender )
{
    guardfunc;
	if( !m_pID_FRAME_SELECT )
		return false;
    MsgExit msg;
    GettheNetworkInput().SendMsg( &msg );

    if (m_pID_FRAME_SELECT)
    {
        m_pID_TEXT_NAME->Clear();
        m_pID_TEXT_LEVEL->Clear();
        m_pID_TEXT_Job->Clear();
        m_pID_TEXT_BIRTHDAY->Clear();
        m_pID_TEXT_LastIP->Clear();
        m_pID_TEXT_LastTime->Clear();
        m_pID_TEXT_LastPlace->Clear();
        m_pID_LIST_PLAYER->Clear();
        m_pID_LIST_PLAYER->SetCurSelIndex(NULL);
        m_bToLogin = true;
        memset( &m_stPlayerInfo, 0, sizeof(SCharBaseInfo)*MAX_PLAYER_COUNT );
        memset( &m_pVisual, 0, sizeof(SCharVisual)*MAX_PLAYER_COUNT );
        for( int i=0; i<MAX_PLAYER_COUNT;i++)
        {
            m_bSlotIsUsed[i] = FALSE;

			IEffect *pEffect = GetEffectMgr()->GetEffect(m_EffectID[i] ); //销毁之前的特效
			if (pEffect)
			{
				pEffect->SetDead();
				m_EffectID[i] = -1;
			}
        }
		if (m_PlayerInfoList.m_bClear)
		{
			m_PlayerInfoList.m_PlayerList.clear();
		}
		m_PlayerInfoList.m_NowPage = 0;

		if(s_CUI_ID_FRAME_ChangeName.IsVisable())
			s_CUI_ID_FRAME_ChangeName.SetVisable(false);
    }

    return true;
    unguard;
}
// List
void CUI_ID_FRAME_Select::ID_LIST_PLAYEROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
    guardfunc;
	if( !m_pID_FRAME_SELECT )
		return;

    // 选中空地直接返回
    ControlList::S_List* pList = m_pID_LIST_PLAYER->GetCurSelItem();
    if( pList )
    {
        std::string strTemp = pList->m_szText;
        if( strTemp.empty() )
        {
            m_pID_LIST_PLAYER->SetCurSelIndex( m_pID_LIST_PLAYER->GetLastCurSelIndex() );
            Refeash();
            return;
        }
    }

    if( m_OldSelPlayerList != m_pID_LIST_PLAYER->GetCurSelIndex() )
    {
        Refeash();
    }

    m_OldSelPlayerList = m_pID_LIST_PLAYER->GetCurSelIndex();

    unguard;
}
void CUI_ID_FRAME_Select::ID_LIST_PLAYEROnListLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
    guardfunc;
	if( !s_CUI_ID_FRAME_Select.GetFrame() )
		return;

    // 郑亮需求:    双击空地创建人物,否则进游戏
    ControlList* pPlayerList = s_CUI_ID_FRAME_Select.GetListOnSelect();
    if( !pPlayerList )
    {
        s_CUI_ID_FRAME_Select.ID_BUTTON_ENTEROnButtonClick( s_CUI_ID_FRAME_Select.GetButOnEnter() );
        return;
    }

    ControlList::S_List* pList = pPlayerList->GetCurSelItem();
    if( pList )
    {
        std::string strTemp = pList->m_szText;
        if( strTemp.empty() )
        {
            pPlayerList->SetCurSelIndex( pPlayerList->GetLastCurSelIndex() );
            s_CUI_ID_FRAME_Select.ID_BUTTON_CREATEOnButtonClick( NULL );
            return;
        }
        else
        {
            s_CUI_ID_FRAME_Select.ID_BUTTON_ENTEROnButtonClick( s_CUI_ID_FRAME_Select.GetButOnEnter() );
            return;
        }
    }
    else
    {
        s_CUI_ID_FRAME_Select.ID_BUTTON_ENTEROnButtonClick( s_CUI_ID_FRAME_Select.GetButOnEnter() );
        return;
    }
    unguard;
}
void CUI_ID_FRAME_Select::ID_LIST_PLAYEROnListRBClick( ControlObject* pSender, ControlList::S_List* pItem)
{
    guardfunc;
	if( !s_CUI_ID_FRAME_Select.GetFrame() )
		return;
    s_CUI_ID_FRAME_Select.Refeash();
    unguard;
}

// Button
bool CUI_ID_FRAME_Select::ID_BUTTON_PLAYER0OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SELECT )
		return false;

	PlayAnimByIndex(1);
	Refeash(0);

	return true;
}
// Button
bool CUI_ID_FRAME_Select::ID_BUTTON_PLAYER1OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SELECT )
		return false;

	PlayAnimByIndex(2);
	Refeash(1);

	return true;
}
// Button
bool CUI_ID_FRAME_Select::ID_BUTTON_PLAYER2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SELECT )
		return false;

	PlayAnimByIndex(3);
	Refeash(2);

	return true;
}
bool CUI_ID_FRAME_Select::ID_BUTTON_UpOnButtonClick( ControlObject* pSender )
{
	//上一页
	if ( !m_pID_FRAME_SELECT )
		return false;
	int Page = m_PlayerInfoList.m_NowPage-1;
	ChangePageShowPlayerInfo(Page);
	return true;

}
bool CUI_ID_FRAME_Select::ID_BUTTON_DownOnButtonClick( ControlObject* pSender )
{
	//下一页
	if ( !m_pID_FRAME_SELECT )
		return false;
	int Page = m_PlayerInfoList.m_NowPage+1;
	ChangePageShowPlayerInfo(Page);
	return true;
}
// Button
bool CUI_ID_FRAME_Select::ID_BUTTON_PLAYER3OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SELECT )
		return false;

	PlayAnimByIndex(4);
	Refeash(3);

	return true;
}
// Button
bool CUI_ID_FRAME_Select::ID_BUTTON_PLAYER4OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SELECT )
		return false;

	PlayAnimByIndex(5);
	Refeash(4);

	return true;
}

// CheckBox
void CUI_ID_FRAME_Select::ID_CHECKBOX_PLAYER0OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_SELECT )
		return;

	PlayAnimByIndex(1);
	Refeash(0);
	return;
}

// CheckBox
void CUI_ID_FRAME_Select::ID_CHECKBOX_PLAYER1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_SELECT )
		return;

	PlayAnimByIndex(2);
	Refeash(1);
	return;
}

// CheckBox
void CUI_ID_FRAME_Select::ID_CHECKBOX_PLAYER2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_SELECT )
		return;

	PlayAnimByIndex(3);
	Refeash(2);
	return;
}

// 装载UI
bool CUI_ID_FRAME_Select::_LoadUI()
{
    guardfunc;
	PostProcessManager::instance().enableProcess( "Bloom", true );
    DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Select.meui");

    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[UI\\Select.UI]失败")
            return false;
    }
    m_bUpdateOnce = FALSE;
    bool ret = DoControlConnect();
	s_CUI_ID_FRAME_DeleteCase.LoadUI();
	
    return ret;
    unguard;
}
// 关连控件
bool CUI_ID_FRAME_Select::DoControlConnect()
{
    guardfunc;
    theUiManager.OnFrameRun( ID_FRAME_SELECT, s_CUI_ID_FRAME_SelectOnFrameRun );
    theUiManager.OnFrameRender( ID_FRAME_SELECT, s_CUI_ID_FRAME_SelectOnFrameRender, true );
    theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_CREATE, s_CUI_ID_FRAME_SelectID_BUTTON_CREATEOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_ENTER, s_CUI_ID_FRAME_SelectID_BUTTON_ENTEROnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_DELETE, s_CUI_ID_FRAME_SelectID_BUTTON_DELETEOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_LEAVE, s_CUI_ID_FRAME_SelectID_BUTTON_LEAVEOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_RESTORE, s_CUI_ID_FRAME_SelectID_BUTTON_RESTOREOnButtonClick );
    theUiManager.OnListSelectChange( ID_FRAME_SELECT, ID_LIST_PLAYER, s_CUI_ID_FRAME_SelectID_LIST_PLAYEROnListSelectChange );
    theUiManager.OnListLDBClick( ID_FRAME_SELECT, ID_LIST_PLAYER, ID_LIST_PLAYEROnListLDBClick );

	theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_PLAYER0, s_CUI_ID_FRAME_SelectID_BUTTON_PLAYER0OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_PLAYER1, s_CUI_ID_FRAME_SelectID_BUTTON_PLAYER1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_PLAYER2, s_CUI_ID_FRAME_SelectID_BUTTON_PLAYER2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_PLAYER3, s_CUI_ID_FRAME_SelectID_BUTTON_PLAYER3OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_PLAYER4, s_CUI_ID_FRAME_SelectID_BUTTON_PLAYER4OnButtonClick );

	theUiManager.OnCheckBoxCheck( ID_FRAME_SELECT, ID_CHECKBOX_PLAYER0, s_CUI_ID_FRAME_SelectID_CHECKBOX_PLAYER0OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SELECT, ID_CHECKBOX_PLAYER1, s_CUI_ID_FRAME_SelectID_CHECKBOX_PLAYER1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SELECT, ID_CHECKBOX_PLAYER2, s_CUI_ID_FRAME_SelectID_CHECKBOX_PLAYER2OnCheckBoxCheck );

    theUiManager.OnCheckBoxCheck( ID_FRAME_SELECT, ID_CHECKBOX_KEYBD, s_CUI_ID_FRAME_SelectID_CHECKBOX_KEYBDOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_SELECT, ID_CHECKBOX_MOUSE, s_CUI_ID_FRAME_SelectID_CHECKBOX_MOUSEOnCheckBoxCheck );

	theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_Up, s_CUI_ID_FRAME_SelectID_BUTTON_UpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SELECT, ID_BUTTON_Down, s_CUI_ID_FRAME_SelectID_BUTTON_DownOnButtonClick );

    m_pID_CHECKBOX_KEYBD = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SELECT, ID_CHECKBOX_KEYBD );
    m_pID_CHECKBOX_MOUSE = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SELECT, ID_CHECKBOX_MOUSE );

    m_pID_FRAME_SELECT = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SELECT );
    m_pID_BUTTON_CREATE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_CREATE );
    m_pID_BUTTON_ENTER = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_ENTER );
    m_pID_BUTTON_DELETE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_DELETE );
    m_pID_BUTTON_LEAVE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_LEAVE );
    m_pID_BUTTON_RESTORE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_RESTORE );
    m_pID_TEXT_NAME = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_NAME );

	m_pID_CHECKBOX_PLAYER0 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SELECT, ID_CHECKBOX_PLAYER0 );
	m_pID_CHECKBOX_PLAYER1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SELECT, ID_CHECKBOX_PLAYER1 );
	m_pID_CHECKBOX_PLAYER2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SELECT, ID_CHECKBOX_PLAYER2 );

    m_pID_TEXT_LEVEL = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_LEVEL );
    m_pID_TEXT_Job = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_JOB);
    m_pID_TEXT_BIRTHDAY = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_BIRTHDAY);
    m_pID_TEXT_LastIP = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_LastIP);
    m_pID_TEXT_LastTime = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_LastTime);
    m_pID_TEXT_LastPlace = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_LastPlace);
    m_pID_LIST_PLAYER = (ControlList*)theUiManager.FindControl( ID_FRAME_SELECT, ID_LIST_PLAYER );
    assert( m_pID_FRAME_SELECT );
    m_pID_FRAME_SELECT->SetMsgProcFun( frame_msg );

    m_pID_BUTTON_LEAVE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_LEAVE );
    m_pID_BUTTON_RESTORE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_RESTORE );

    m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_Left );
    m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_Right );
	//added by zhuomeng.hu		[8/20/2010]
	m_pID_TEXT_COUNTRY = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_COUNTRY );
	m_pID_TEXT_currectsever = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_currectsever );
    m_pID_PICTURE_CreateBg[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_CreateBg1 );
    m_pID_PICTURE_CreateBg[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_CreateBg2 );
    m_pID_PICTURE_CreateBg[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_CreateBg3 );
    /*m_pID_PICTURE_CreateBg[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_CreateBg4 );
    m_pID_PICTURE_CreateBg[4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_CreateBg5 );*/

	m_pID_BUTTON_PLAYER0 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_PLAYER0 );
	m_pID_BUTTON_PLAYER1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_PLAYER1 );
	m_pID_BUTTON_PLAYER2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_PLAYER2 );
	m_pID_BUTTON_PLAYER3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_PLAYER3 );
	m_pID_BUTTON_PLAYER4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_PLAYER4 );
	
	m_pID_TEXT_Jobs[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_JOB0 );
	m_pID_TEXT_Levs[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_LEVEL0 );
	m_pID_TEXT_Names[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_Name0 );
	
	m_pID_TEXT_Jobs[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_JOB1 );
	m_pID_TEXT_Levs[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_LEVEL1 );
	m_pID_TEXT_Names[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_Name1 );
	
	m_pID_TEXT_Jobs[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_LEVEL2 );
	m_pID_TEXT_Levs[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_JOB2 );
	m_pID_TEXT_Names[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_Name2 );
	
 	/*m_pID_TEXT_Jobs[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_LEVEL3 );
 	m_pID_TEXT_Levs[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_JOB3 );
 	m_pID_TEXT_Names[3] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_Name3 );
 	
 	m_pID_TEXT_Jobs[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_LEVEL4 );
 	m_pID_TEXT_Levs[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_JOB4 );
 	m_pID_TEXT_Names[4] = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_Name4 );*/
	
	m_pID_PICTURE_Jobs[0][0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Spear0 );
	m_pID_PICTURE_Jobs[0][1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Sword0 );
	m_pID_PICTURE_Jobs[0][2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Fan0 );
	m_pID_PICTURE_Jobs[0][3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Bow0);
	m_pID_PICTURE_Jobs[0][4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Staff0 );
	
	m_pID_PICTURE_Jobs[1][0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Spear1 );
	m_pID_PICTURE_Jobs[1][1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Sword1 );
	m_pID_PICTURE_Jobs[1][2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Fan1 );
	m_pID_PICTURE_Jobs[1][3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Bow1 );
	m_pID_PICTURE_Jobs[1][4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Staff1 );

	
	m_pID_PICTURE_Jobs[2][0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Spear2 );
	m_pID_PICTURE_Jobs[2][1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Sword2 );
	m_pID_PICTURE_Jobs[2][2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Fan2 );
	m_pID_PICTURE_Jobs[2][3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Bow2 );
	m_pID_PICTURE_Jobs[2][4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Staff2 );
	
 	/*m_pID_PICTURE_Jobs[3][0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Spear3 );
 	m_pID_PICTURE_Jobs[3][1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Sword3 );
 	m_pID_PICTURE_Jobs[3][2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Fan3 );
 	m_pID_PICTURE_Jobs[3][3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Bow3 );
 	m_pID_PICTURE_Jobs[3][4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Staff3 );
 	
 	m_pID_PICTURE_Jobs[4][0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Spear4 );
 	m_pID_PICTURE_Jobs[4][1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Sword4 );
 	m_pID_PICTURE_Jobs[4][2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Fan4 );
 	m_pID_PICTURE_Jobs[4][3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Bow4 );
 	m_pID_PICTURE_Jobs[4][4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SELECT, ID_PICTURE_Staff4 );*/


	m_pID_TEXT_DeleteInfo0 = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_DeleteInfo0 );
	m_pID_TEXT_DeleteInfo1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_DeleteInfo1 );
	m_pID_TEXT_DeleteInfo2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_DeleteInfo2 );


	m_pID_TEXT_PageInfo= (ControlText*)theUiManager.FindControl( ID_FRAME_SELECT, ID_TEXT_PageInfo );
	m_pID_BUTTON_Up= (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_Up );
	m_pID_BUTTON_Down= (ControlButton*)theUiManager.FindControl( ID_FRAME_SELECT, ID_BUTTON_Down );

    assert( m_pID_BUTTON_CREATE );
    assert( m_pID_BUTTON_ENTER );
    assert( m_pID_BUTTON_DELETE );
    assert( m_pID_BUTTON_LEAVE );
    assert( m_pID_BUTTON_RESTORE );
    assert( m_pID_TEXT_NAME );
    assert( m_pID_TEXT_LEVEL );
    assert( m_pID_TEXT_Job );
    assert( m_pID_TEXT_BIRTHDAY );
    assert( m_pID_LIST_PLAYER );
	assert( m_pID_TEXT_COUNTRY );		//added by zhuomeng.hu		[8/20/2010]
	assert( m_pID_TEXT_currectsever );	//added by zhuomeng.hu		[8/20/2010]
	assert( m_pID_BUTTON_PLAYER0 );
	assert( m_pID_BUTTON_PLAYER1 );
	assert( m_pID_BUTTON_PLAYER2 );
	assert( m_pID_BUTTON_PLAYER3 );
	assert( m_pID_BUTTON_PLAYER4 );
	assert( m_pID_CHECKBOX_PLAYER0 );
	assert( m_pID_CHECKBOX_PLAYER1 );
	assert( m_pID_CHECKBOX_PLAYER2 );
	assert( m_pID_TEXT_DeleteInfo0 );
	assert( m_pID_TEXT_DeleteInfo1 );
	assert( m_pID_TEXT_DeleteInfo2 );

	assert( m_pID_TEXT_PageInfo );
	assert( m_pID_BUTTON_Up );
	assert( m_pID_BUTTON_Down );

    for( int i = 0; i < MAX_PLAYER_COUNT; ++i )
    {
        assert( m_pID_PICTURE_CreateBg[i] );

		IEffect *pEffect = GetEffectMgr()->GetEffect(m_EffectID[i] ); //销毁之前的特效
		if (pEffect)
		{
			pEffect->SetDead();
			m_EffectID[i] = -1;
		}
    }

	


	
    m_pID_LIST_PLAYER->SetRBClickFun(ID_LIST_PLAYEROnListRBClick);
    //m_pID_FRAME_SELECT->SetMouseDBClickFun( FrameOnDBClick );
	m_pID_FRAME_SELECT->SetOnClickFun(SelectModelLButtonDown);

	// 显示当前服务器	added by zhuomeng.hu		[8/20/2010]
    char szWindowName[256] = {0};
    sprintf_s(szWindowName, sizeof(szWindowName)-1, "%s %s", s_CUI_ID_FRAME_LOGIN.GetArea().c_str(),
        s_CUI_ID_FRAME_LOGIN.GetServer().c_str() );
    theHeroGame.SetWindowText(szWindowName);
	std::string strCurrentServer = "";
	if( !s_CUI_ID_FRAME_LOGIN.GetArea().empty() && !s_CUI_ID_FRAME_LOGIN.GetServer().empty() )
		strCurrentServer = s_CUI_ID_FRAME_LOGIN.GetArea() + "     " + s_CUI_ID_FRAME_LOGIN.GetServer();
	m_pID_TEXT_currectsever->SetText( strCurrentServer.c_str() );
    
    m_strWindowText = theHeroGame.GetWindowText();

    assert( m_pID_CHECKBOX_KEYBD );
    assert( m_pID_CHECKBOX_MOUSE );

    m_pID_FRAME_SELECT->SetWidth( SCREEN_WIDTH );
    m_pID_FRAME_SELECT->SetHeight( SCREEN_HEIGHT );

    m_pID_BUTTON_Left->SetLButtonDownFun(TurnOnLButtonDown);
    m_pID_BUTTON_Left->SetLButtonUpFun(TurnOnLButtonUp);
    m_pID_BUTTON_Right->SetLButtonDownFun(TurnOnLButtonDown);
    m_pID_BUTTON_Right->SetLButtonUpFun(TurnOnLButtonUp);

    m_pCamera = MeNew MeCamera;
    D3DXVECTOR3 vFromPt	 = D3DXVECTOR3( 0.0f, 300.0f, 200.0f );
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec	  = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
    m_pCamera->SetViewParams( vFromPt, vLookatPt, vUpVec );

    float fAspect = (float)SCREEN_WIDTH/SCREEN_HEIGHT;
    m_pCamera->SetProjParams( D3DX_PI/4, fAspect,  1.0f, 18000.0f );

    SetControlMode(s_CUI_ID_FRAME_LOGIN.GetControlMode());

    SetVisable(false);

    m_bNeedReadUserData = true;
    if( m_pID_BUTTON_CREATE && !gCfg.m_bCanCreatePlayer )
        m_pID_BUTTON_CREATE->SetEnable(false);

	m_totalRole = 0;
	m_RotateZ = gCfg.m_fSelectRoleRotateZ;
    Refeash();
	InitPlayerAnim();

	m_PlayerInfoList.m_bClear = true;


	m_pID_BUTTON_Up->SetVisable(false);
	m_pID_BUTTON_Down->SetVisable(false);
	m_pID_TEXT_PageInfo->SetVisable(false);

	return true;
    unguard;
}
// 卸载UI
bool CUI_ID_FRAME_Select::_UnLoadUI()
{
    guardfunc;
    if(m_pID_FRAME_SELECT == NULL)
    {
        return true;
    }
	s_CUI_ID_FRAME_DeleteCase.UnLoadUI();
	m_isEnterWorld = false;

    m_OldSelPlayerList = -1;
    if( m_pCamera )
    {
        delete m_pCamera;
        m_pCamera = NULL;
    }
    for( int i=0; i<MAX_PLAYER_COUNT; i++ )
    {
        if( m_pPlayerAnim[i] )
        {
            m_pPlayerAnim[i]->Destroy();
            delete m_pPlayerAnim[i];
            m_pPlayerAnim[i] = NULL;

			if(m_pPlayer[i])
            delete m_pPlayer[i];
			m_pPlayer[i] = NULL;

			IEffect *pEffect = GetEffectMgr()->GetEffect(m_EffectID[i] ); //销毁之前的特效
			if (pEffect)
			{
				pEffect->SetDead();	
				m_EffectID[i] = -1;
			}

			
        }
    }
    CLOSE_SCRIPT( eUI_OBJECT_Select );

    m_bIsTileLoaded = false;
    m_pCameraModel = NULL;
	m_pBGModel		= NULL;
    m_pDoorModel = NULL;

    ControlList::S_List *pstList = m_pID_LIST_PLAYER->GetCurSelItem();
    if( pstList )
    {
        int nIndex = pstList->m_nID;
        if( nIndex >= 0 && m_bSlotIsUsed[nIndex] == true )
        {
            CUserData::Instance()->SetRoleString( m_stPlayerInfo[nIndex].aptotic.szCharacterName );
        }
    }
    m_pID_FRAME_SELECT = NULL;
    m_pID_CHECKBOX_KEYBD = NULL;	//键盘控制
    m_pID_CHECKBOX_MOUSE = NULL;	//鼠标控制
    m_pID_FRAME_SELECT = NULL;
    m_pID_BUTTON_CREATE = NULL;
    m_pID_BUTTON_ENTER = NULL;
    m_pID_BUTTON_DELETE = NULL;
    m_pID_BUTTON_LEAVE = NULL;
    m_pID_BUTTON_RESTORE = NULL;
    m_pID_TEXT_NAME = NULL;
    m_pID_TEXT_LEVEL = NULL;
    m_pID_TEXT_Job = NULL;
    m_pID_TEXT_BIRTHDAY = NULL;
    m_pID_TEXT_LastIP = NULL;
    m_pID_TEXT_LastTime = NULL;
    m_pID_TEXT_LastPlace = NULL;
    m_pID_LIST_PLAYER = NULL;
    m_pID_BUTTON_Left = NULL;
    m_pID_BUTTON_Right = NULL;
	m_pID_TEXT_COUNTRY = NULL;			//added by zhuomeng.hu		[8/20/2010]
	m_pID_TEXT_currectsever = NULL;		//added by zhuomeng.hu		[8/20/2010]
	m_pID_TEXT_DeleteInfo0 = NULL;
	m_pID_TEXT_DeleteInfo1 = NULL;
	m_pID_TEXT_DeleteInfo2 = NULL;
	m_CurrentSelectIndex = -1;
	m_IsSetCameraForCreate = false;
    for( int i = 0; i < MAX_PLAYER_COUNT; ++i )
    {
        m_pID_PICTURE_CreateBg[i] = NULL;
    }

	//m_PlayerInfoList.m_PlayerList.clear();
	//m_PlayerInfoList.m_NowPage = 0;

	ClearPlayerData();
	Release();
	if (m_PlayerInfoList.m_bClear)
	{
		m_PlayerInfoList.m_PlayerList.clear();
	}

    return theUiManager.RemoveFrame( "data\\ui\\Select.meui" );

    unguard;
}
// 是否可视
bool CUI_ID_FRAME_Select::_IsVisable()
{
    guardfunc;
    if( !m_pID_FRAME_SELECT )
        return false;
    return m_pID_FRAME_SELECT->IsVisable();
    unguard;
}
// 设置是否可视
void CUI_ID_FRAME_Select::LoadPlayer()
{
	if(m_PlayerInfoList.m_PlayerList.size() > 0)
	{
		for(int i =0;i<MAX_PLAYER_COUNT;++i)
		{
			if(m_stPlayerInfo[i].liveinfo.ustLevel ==0 && m_bSlotIsUsed[i] == FALSE)
				continue;
			else
				return;
		}
		//有玩家 但是没显示 
		ChangePageShowPlayerInfo(0);
	}
}
void CUI_ID_FRAME_Select::_SetVisable( const bool bVisable )
{
    guardfunc;
    if (NULL == m_pID_FRAME_SELECT)
    {
        return ;
    }
    m_pID_FRAME_SELECT->SetVisable( bVisable );

    if (m_pID_LIST_PLAYER->GetListItemCnt() < 1)
    {
        m_pID_BUTTON_ENTER->SetEnable(false);
        m_pID_BUTTON_DELETE->SetEnable(false);
        m_pID_BUTTON_RESTORE->SetEnable(false);
    }

    m_isEnterWorld = false;

    if( bVisable )
    {
        //GMusic.PlayMusic( gCfg.m_szSelectPageMusic, TRUE, TRUE );
//         GMusic.StopMusic();
        GSound.StopSound();
		string strFullPath(CWorld::GetAppDataCharDir());
		strFullPath += '\\';
		strFullPath += theSoundConfig.GetSoundFile( SoundConfig::EST_SelectScene );
		GMusic.PlayMusic( strFullPath.c_str(), TRUE, TRUE );
		LoadPlayer();

		s_CUI_ID_FRAME_SelectChannel.SetSelectFlag( false );
		s_CUI_ID_FRAME_SelectChannel.SetLastChannelIndex( -1 );
		s_CUI_ID_FRAME_SelectChannel.ClearData();

		s_CUI_ID_FRAME_GuildGeneralBattleList.ClearData();
    }
	else
	{
		s_CUI_ID_FRAME_ChangeName.SetVisable(false);
	}
	m_strLastSel = "no";
	m_nCurrSel = -1;
	m_nMouseIndex = -1;
    unguard;
}

void CUI_ID_FRAME_Select::Refeash(int index)
{
    guardfunc;
    guard(test0);
	if( !m_pID_FRAME_SELECT )
		return;
    m_pID_LIST_PLAYER->BeginUpdate();
    m_pID_LIST_PLAYER->Clear();
    unguard;

    DWORD dwColor;
    bool bHasUpdate = false;
	m_totalRole = 0;

    for( int n = 0; n < MAX_PLAYER_COUNT; ++n )
    {
        if ( m_bSlotIsUsed[n] == true )
        {
            ControlList::S_List stList;
            if(m_bIsDel[n])
            {
                dwColor = Color_Config.getColor(CC_CHARACTER_DEL);
                stList.SetData( m_stPlayerInfo[n].aptotic.szCharacterName, n, 0, dwColor );
                stList.SetAlignMode( ControlList::S_List::LIST_ALIGNMODE_MIDDLE );
            }
            else
            {
                stList.SetData( m_stPlayerInfo[n].aptotic.szCharacterName, n );
                stList.SetAlignMode( ControlList::S_List::LIST_ALIGNMODE_MIDDLE );
            }
            m_pID_LIST_PLAYER->AddItem( &stList );
            bHasUpdate = true;
			++m_totalRole;
            m_pID_PICTURE_CreateBg[n]->SetVisable( false );
        }
        else
        {
            ControlList::S_List stList;
            stList.SetData( "", n );
            m_pID_LIST_PLAYER->AddItem( &stList );
            m_pID_PICTURE_CreateBg[n]->SetVisable( true );
        }

		// 设置角色信息
		SetPlayerInfo(n);
    }
    m_pID_LIST_PLAYER->EndUpdate();

    if( bHasUpdate )
    {
        if( m_bNeedReadUserData )
        {
            // 获取最后一次登录人物
            if( CUserData::Instance()->ReadUserData() )
            {
                if( CUserData::Instance()->GetRole() && m_pID_LIST_PLAYER )
                {
                    strcpy( m_pszLastLoginRole, CUserData::Instance()->GetRole() );
                    m_bNeedSetLastLogin = true;
                }
            }
            m_bNeedReadUserData = false;
        }

        if( strlen(m_pszLastLoginRole) > 0 && m_bNeedSetLastLogin )
        {
            if( m_pID_LIST_PLAYER )
            {
                for(int i=0; i<m_pID_LIST_PLAYER->GetListItemCnt(); ++i)
                {
                    ControlList::S_List *pstList = m_pID_LIST_PLAYER->GetListItem()[i];
                    if( pstList )
                    {
                        int nIndex = pstList->m_nID;
                        if( nIndex >= 0 && m_bSlotIsUsed[nIndex] == true )
                        {
                            if( !stricmp(m_stPlayerInfo[nIndex].aptotic.szCharacterName, m_pszLastLoginRole ) )
                            {
                                m_pID_LIST_PLAYER->SetCurSelIndex(nIndex);
                                m_pID_LIST_PLAYER->SetLastCurSelIndex(nIndex);
                                m_OldSelPlayerList = nIndex;
                                m_bNeedSetLastLogin = false;
                            }
                        }
                    }
                }
            }
        }
        else
            m_bNeedSetLastLogin = false;
    }

    if( g_bCreateOk && index >= 0)
    {
        m_pID_LIST_PLAYER->SetCurSelIndex(index);
        g_bCreateOk = FALSE;
    }

   // ControlList::S_List *pstList = m_pID_LIST_PLAYER->GetCurSelItem();
   // if ( pstList )
    {
        //int nIndex = pstList->m_nID;
		int nIndex = index;
        if( nIndex >= 0 && m_bSlotIsUsed[nIndex] == true )
        {
            m_pID_BUTTON_ENTER->SetEnable(!m_bIsDel[nIndex]);
            m_pID_BUTTON_DELETE->SetEnable(!m_bIsDel[nIndex]);
            m_pID_BUTTON_RESTORE->SetEnable(m_bIsDel[nIndex]);
            char szData[128];
            ::ZeroMemory(szData,128);
            sprintf( szData, "%s", m_stPlayerInfo[nIndex].aptotic.szCharacterName );
            *m_pID_TEXT_NAME = szData;

            if (szData[0] != 0)					
            {
                sprintf( szData, "%d", m_stPlayerInfo[nIndex].liveinfo.ustLevel );
                *m_pID_TEXT_LEVEL = szData;
                CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( m_stPlayerInfo[nIndex].aptotic.usProfession );
                if( pProInfo )
                    strcpy( szData, pProInfo->m_strProShow.c_str());
                *m_pID_TEXT_Job = szData;

				// 显示所属国家		added by zhuomeng.hu		[8/20/2010]
				uint8 nCountryID = m_stPlayerInfo[nIndex].aptotic.ucCountry;
                m_pID_TEXT_COUNTRY->SetText( CountryFunction::GetDefaultCountryNameById( nCountryID ) );

                ////
                //// 元年一月一日子时
                //char szBuf[128];
                //std::string strGameTime = m_stPlayerInfo[nIndex].aptotic.szYearName;
                //if ( m_stPlayerInfo[nIndex].aptotic.byYear == 1 )
                //	strGameTime += theXmlString.GetString( eTime_Yuan );
                //else
                //	strGameTime += itoa( m_stPlayerInfo[nIndex].aptotic.byYear, szBuf, 10 );
                //strGameTime += theXmlString.GetString( eTime_Year );		// 年
                //strGameTime += itoa( m_stPlayerInfo[nIndex].aptotic.byMonth, szBuf, 10 );
                //strGameTime += theXmlString.GetString( eTime_Month );		// 月
                //strGameTime += itoa( m_stPlayerInfo[nIndex].aptotic.byDay, szBuf, 10 );
                //strGameTime += theXmlString.GetString( eTime_Day );		// 日
                //*m_pID_TEXT_BIRTHDAY = strGameTime;
            }
		}
	}
    unguard;
}

void CUI_ID_FRAME_Select::AddPlayer( MsgAckChar* pAckChar, SCharBaseInfo* pPlayerInfo,SCharVisual* pVisual,const int nIndex, DWORD dwCharacterID, bool IsDel, DWORD dwDelTime,bool bRefeash )
{
    guardfunc;
    /*if( nIndex < 0 || nIndex >= MAX_PLAYER_COUNT )
    {
        assert( false );
        return;
    }*/
	//将角色加入列表

	SelectPlayerInfo pInfo(pPlayerInfo,pVisual,nIndex,dwCharacterID,IsDel,dwDelTime,pAckChar->visual.fModelPercent);
	m_PlayerInfoList.AddPlayerInfo(pInfo);
	int newIndex = m_PlayerInfoList.GetIndexByNowPage(nIndex);
	UpdatePageInfo();
	if(newIndex == -1)
		return;

    m_stPlayerInfo[newIndex] = *pPlayerInfo;
    m_bSlotIsUsed[newIndex] = true;
    m_bSlotCharacterID[newIndex] = dwCharacterID;
    m_pVisual[newIndex] = *pVisual;
    m_bIsDel[newIndex] = IsDel;
    m_fPlayerScale[newIndex] = pAckChar->visual.fModelPercent;
	//m_fPlayerRotate[nIndex] = 0.0f;
	m_dwDelTime[newIndex] = dwDelTime;

    if (m_pID_FRAME_SELECT && bRefeash == true )
    {
		InitPlayerAnim();
        Refeash(newIndex);
    }
    unguard;
}
void CUI_ID_FRAME_Select::UpdatePageInfo()
{
	if(!m_pID_FRAME_SELECT)
	{
		SetVisable(true);
	}
	if(!m_pID_FRAME_SELECT)
		return;
	int MaxPage = ((m_PlayerInfoList.m_PlayerList.size()%MAX_PLAYER_COUNT == 0)?(m_PlayerInfoList.m_PlayerList.size()/MAX_PLAYER_COUNT):(m_PlayerInfoList.m_PlayerList.size()/MAX_PLAYER_COUNT +1)) -1;
	if(m_PlayerInfoList.m_NowPage <0 || m_PlayerInfoList.m_NowPage>MaxPage)
	{
		ChangePageShowPlayerInfo(0);
	}
	char pageInfo[24];
	sprintf_s(pageInfo,23,"%d/%d",m_PlayerInfoList.m_NowPage+1,MaxPage+1);
	m_pID_TEXT_PageInfo->SetText(pageInfo);
	if(MaxPage == 0)
	{
		m_pID_BUTTON_Up->SetVisable(false);
		m_pID_BUTTON_Down->SetVisable(false);
		m_pID_TEXT_PageInfo->SetVisable(false);
		return;
	}
	m_pID_TEXT_PageInfo->SetVisable(true);
	m_pID_BUTTON_Up->SetVisable(true);
	m_pID_BUTTON_Down->SetVisable(true);
	m_pID_BUTTON_Up->SetEnable(true);
	m_pID_BUTTON_Down->SetEnable(true);
	if(m_PlayerInfoList.m_NowPage == 0)
	{
		m_pID_BUTTON_Up->SetEnable(false);
	}
	else if(m_PlayerInfoList.m_NowPage == MaxPage)
	{
		m_pID_BUTTON_Down->SetEnable(false);
	}
	if(m_nCurrSel != -1)
	{
		//修改当前的选择
		PlayAnimByIndex(m_nCurrSel+1);
		Refeash(m_nCurrSel);
	}
}
void CUI_ID_FRAME_Select::ChangePageShowPlayerInfo(int Page)
{
	//改变人物页面
	/*if(Page == m_PlayerInfoList.m_NowPage)
		return;*/
	int MaxPage = ((m_PlayerInfoList.m_PlayerList.size()%MAX_PLAYER_COUNT == 0)?(m_PlayerInfoList.m_PlayerList.size()/MAX_PLAYER_COUNT):(m_PlayerInfoList.m_PlayerList.size()/MAX_PLAYER_COUNT +1)) -1;
	if(Page > MaxPage || MaxPage<0)
		return;
	m_PlayerInfoList.m_NowPage = Page;
	UpdatePageInfo();
	//1.先清空当前显示的玩家数据
	ClearPlayerData();
	//2.清空模型
	Release();
	//3.填充新的玩家数据
	int beginSlot = Page * MAX_PLAYER_COUNT;
	int endSlot = beginSlot + MAX_PLAYER_COUNT -1;
	for(int i =beginSlot;i<= endSlot;++i)
	{
		//将数据显示到上面去
		size_t Index =m_PlayerInfoList.GetInfoBySlot(i);
		if(Index == 0xFFFFFFFF)
			continue;
		SelectPlayerInfo& pInfo = m_PlayerInfoList.m_PlayerList[Index];
		int newIndex = m_PlayerInfoList.GetIndexByNowPage(i);
		if(newIndex == -1)
			continue;
		m_stPlayerInfo[newIndex] = pInfo.m_stPlayerInfo;
		m_bSlotIsUsed[newIndex] = true;
		m_bSlotCharacterID[newIndex] = pInfo.m_bSlotCharacterID;
		m_pVisual[newIndex] = pInfo.m_pVisual;
		m_bIsDel[newIndex] = pInfo.m_bIsDel;
		m_fPlayerScale[newIndex] = pInfo.m_fPlayerScale;
		m_dwDelTime[newIndex] = pInfo.m_dwDelTime;
		if (m_pID_FRAME_SELECT)
		{
			InitPlayerAnim();
			Refeash(newIndex);
		}
	}
}
bool CUI_ID_FRAME_Select::GetStateToLogin()
{
    guardfunc;
    return m_bToLogin;
    unguard;
}

void CUI_ID_FRAME_Select::SetStateToLogin(bool bState)
{
    guardfunc;
    m_bToLogin = bState;
    unguard;
}

bool CUI_ID_FRAME_Select::GetStateToCreate()
{
    guardfunc;
    return m_bToCreate;
    unguard;
}

void CUI_ID_FRAME_Select::SetStateToCreate(bool bState)
{
    guardfunc;
    m_bToCreate = bState;
    unguard;
}

void CUI_ID_FRAME_Select::ID_CHECKBOX_KEYBDOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    guardfunc;
	if( !m_pID_FRAME_SELECT )
		return;
    m_pID_CHECKBOX_KEYBD->SetCheck(*pbChecked);
    m_nControlMode = 1;
    m_pID_CHECKBOX_MOUSE->SetCheck( !m_pID_CHECKBOX_KEYBD->IsChecked() );
    unguard;
}
// CheckBox
void CUI_ID_FRAME_Select::ID_CHECKBOX_MOUSEOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    guardfunc;
	if( !m_pID_FRAME_SELECT )
		return;
    m_pID_CHECKBOX_MOUSE->SetCheck( *pbChecked);
    m_nControlMode = 2;
    m_pID_CHECKBOX_KEYBD->SetCheck( !m_pID_CHECKBOX_MOUSE->IsChecked() );
    unguard;
}
void CUI_ID_FRAME_Select::SetControlMode( int nMode)
{
    guardfunc;
    m_nControlMode = nMode;

    if(m_nControlMode != 0)
    {
        if(m_nControlMode == 1)
            m_pID_CHECKBOX_KEYBD->SetCheck(true);
        else if(m_nControlMode == 2)
            m_pID_CHECKBOX_MOUSE->SetCheck(true);
    }
    unguard;
}
int	 CUI_ID_FRAME_Select::GetControlMode()
{
    guardfunc;
    return m_nControlMode;
    unguard;
}

bool CUI_ID_FRAME_Select::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
    guardfunc;
//     if ( bMsgUsed == true || g_GameState != G_SELECT )
//         return false;
// 
//     D3DXVECTOR3 vDir = g_lookat - g_eye;
//     D3DXVec3Normalize( &vDir, &vDir );
//     vDir *= 0.2f;

	if(!s_CUI_ID_FRAME_Select.IsVisable())
		return false;

    switch( msg ) 
    {
	case WM_MOUSEMOVE:
		{
			int nIndex = s_CUI_ID_FRAME_Select.GetPlayAnimBySel();
			s_CUI_ID_FRAME_Select.SetMouseMoveIndex(nIndex - 1);
		}
		break;
    case WM_KEYUP:
        {
//             if( wParam == VK_RETURN )
//             {
// 				if(s_CUI_ID_FRAME_DeleteCase.IsVisable())
// 				{
// 					return false;
// 				}
// 
//                 bool bHasPlayer = false;
//                 for ( int n=0; n<MAX_PLAYER_COUNT; n++ )
//                 {
//                     if ( s_CUI_ID_FRAME_Select.GetSlotIsUsed(n) )
//                     {
//                         bHasPlayer = true;
//                         break;
//                     }
//                 }
//                 if( bHasPlayer )
//                 {
//                     if( s_CUI_ID_FRAME_Select.GetButEnableOnEnter() && !s_CUI_ID_FRAME_Select.GetEnterWorldState() )
//                         s_CUI_ID_FRAME_Select.ID_BUTTON_ENTEROnButtonClick( s_CUI_ID_FRAME_Select.GetButOnEnter());
//                 }
//                 else
//                 {
//                     if( s_CUI_ID_FRAME_Select.GetButEnableOnCreate() )
//                         s_CUI_ID_FRAME_Select.ID_BUTTON_CREATEOnButtonClick( s_CUI_ID_FRAME_Select.GetButOnCreate() );
//                 }
//                 return true;
//             }
// 
//             if (wParam == 'W')
//             {
// 
//                 g_eye = g_eye + vDir;
//                 g_lookat = g_lookat + vDir;
//             }
//             else if (wParam == 'S')
//             {
//                 g_eye = g_eye - vDir;
//                 g_lookat = g_lookat - vDir;
//             }
//             else if (wParam == 'A')
//             {
//                 g_eye.x += 0.1f;
//                 g_lookat.x += 0.1f;
//             }
//             else if (wParam == 'D')
//             {
//                 g_eye.x -= 0.1f;
//                 g_lookat.x -= 0.1f;
//             }
//             else if (wParam == 'Q')
//             {
//                 g_eye.z += 0.05f;
//                 g_lookat.z += 0.05f;
//             }
//             else if (wParam == 'E')
//             {
//                 g_eye.z -= 0.05f;
//                 g_lookat.z -= 0.05f;
//             }
//             if (wParam == VK_LEFT)
//             {
//                 g_lookat.x += 0.1f;
//             }
//             else if (wParam == VK_RIGHT)
//             {
//                 g_lookat.x -= 0.1f;
//             }
//             else if (wParam == VK_UP)
//             {
//                 g_lookat.z += 0.1f;
//             }
//             else if (wParam == VK_DOWN)
//             {
//                 g_lookat.z -= 0.1f;
//             }
        }
        break;
    }

    return false;

    unguard;
}

void CUI_ID_FRAME_Select::EnableMoveCamera(BOOL bMove)
{
    m_bMoveCamera = bMove;
}

void CUI_ID_FRAME_Select::BackToSelect()
{
    m_bMoveBackCamera = TRUE;
}

void CUI_ID_FRAME_Select::ClearPlayerData()
{
    memset( &m_stPlayerInfo, 0, sizeof(SCharBaseInfo)*MAX_PLAYER_COUNT );
    memset( &m_pVisual, 0, sizeof(SCharVisual)*MAX_PLAYER_COUNT );
    for( int i=0; i<MAX_PLAYER_COUNT;i++)
    {
        m_bSlotIsUsed[i] = FALSE;
    }
}

void CUI_ID_FRAME_Select::SetButEnableOnEnter(bool bValue)
{
    if(!m_pID_FRAME_SELECT)
        return;

    m_pID_BUTTON_ENTER->SetEnable(bValue);
}

bool  CUI_ID_FRAME_Select::GetButEnableOnEnter()
{
    if(!m_pID_FRAME_SELECT)
        return false;

    return m_pID_BUTTON_ENTER->IsEnable();
}

bool  CUI_ID_FRAME_Select::GetButEnableOnCreate()
{
    if(!m_pID_FRAME_SELECT)
        return false;

    return m_pID_BUTTON_CREATE->IsEnable();
}


void CUI_ID_FRAME_Select::SetDel(int nIndex,bool bValue,DWORD dwLeftTime)
{
    if(nIndex < 0 || nIndex >= MAX_PLAYER_COUNT)
	{
		m_PlayerInfoList.m_PlayerList[m_PlayerInfoList.GetInfoBySlot(nIndex)].m_bIsDel = bValue;
		m_PlayerInfoList.m_PlayerList[m_PlayerInfoList.GetInfoBySlot(nIndex)].m_dwDelTime = dwLeftTime;
		int Index = m_PlayerInfoList.GetIndexByNowPage(nIndex);
		if(Index == -1)
			return;
		m_bIsDel[Index] = bValue;
		m_dwDelTime[Index] = dwLeftTime;
        return;
	}
     m_bIsDel[nIndex] = bValue;
	 m_dwDelTime[nIndex] = dwLeftTime;

	 int Index = m_PlayerInfoList.GetSlotByPageIndex(nIndex);
	 m_PlayerInfoList.m_PlayerList[m_PlayerInfoList.GetInfoBySlot(Index)].m_bIsDel = bValue;
	 m_PlayerInfoList.m_PlayerList[m_PlayerInfoList.GetInfoBySlot(Index)].m_dwDelTime = dwLeftTime;
}

bool CUI_ID_FRAME_Select::GetDel(int nIndex)
{
    if(nIndex < 0 || nIndex >= MAX_PLAYER_COUNT)
        return false;

    return m_bIsDel[nIndex];
}

bool CUI_ID_FRAME_Select::GetSlotIsUsed(int nIndex)
{
    if(nIndex < 0 || nIndex >= MAX_PLAYER_COUNT)
        return false;

    return m_bSlotIsUsed[nIndex];
}

void CUI_ID_FRAME_Select::SetSlotIsUsed(int nIndex,bool bValue)
{
    if(nIndex < 0 || nIndex >= MAX_PLAYER_COUNT)
	{
		m_PlayerInfoList.m_PlayerList[m_PlayerInfoList.GetInfoBySlot(nIndex)].m_bSlotIsUsed = bValue;
		int Index = m_PlayerInfoList.GetIndexByNowPage(nIndex);
		if(Index == -1)
			return;
		m_bSlotIsUsed[Index] = bValue;
        return;
	}
    m_bSlotIsUsed[nIndex] = bValue;
	int Index = m_PlayerInfoList.GetSlotByPageIndex(nIndex);
	m_PlayerInfoList.m_PlayerList[m_PlayerInfoList.GetInfoBySlot(Index)].m_bSlotIsUsed = bValue;
}



ControlButton* CUI_ID_FRAME_Select::GetButOnEnter()
{
    if(!m_pID_FRAME_SELECT)
        return NULL;

    return m_pID_BUTTON_ENTER;
}

ControlButton* CUI_ID_FRAME_Select::GetButOnCreate()
{
    if(!m_pID_FRAME_SELECT)
        return NULL;

    return m_pID_BUTTON_CREATE;
}

ControlList* CUI_ID_FRAME_Select::GetListOnSelect()
{ 
    if(!m_pID_FRAME_SELECT)
       return NULL;

    return m_pID_LIST_PLAYER;
}

CPlayerAnim* CUI_ID_FRAME_Select::GetPlayerAnim(int nIndex)
{
    if(nIndex < 0 || nIndex >= MAX_PLAYER_COUNT)
        return NULL;

    return m_pPlayerAnim[nIndex];
}

SCharBaseInfo CUI_ID_FRAME_Select::GetCurSelPlayerInfo()
{
	int sel = m_pID_LIST_PLAYER->GetCurSelIndex();
	
	if(sel!=-1)
	{
		int count = 0;
		for(int i=0;i<=sel;++i)
		{
			if(!m_bSlotIsUsed[i])
				++count;
		}
		return m_stPlayerInfo[sel+count];
	}
	else
	{
		assert(false);

		return SCharBaseInfo();
	}
}

int CUI_ID_FRAME_Select::GetTotalRole()
{
	return m_totalRole;
}

bool CUI_ID_FRAME_Select::FrameOnDBClick( ControlObject* pSender )
{
    return s_CUI_ID_FRAME_Select.CheckFocusOnModel();
}

bool CUI_ID_FRAME_Select::CheckFocusOnModel()
{
    D3DXVECTOR3 vFrom, vDir;
    m_pCamera->BuildPickRay( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y, vFrom, vDir, SCREEN_WIDTH, SCREEN_HEIGHT );
    TPickResult castResult;
    if( SwGlobal::GetWorldPicker()->Pick( *(Vector*)&vFrom, *(Vector*)&vDir, castResult, emPT_CollisionObj, true, 1000 ) )
    {
        if( !m_bSlotIsUsed[0] )
            return false;

        int nSelectPlayer = m_pID_LIST_PLAYER->GetCurSelIndex();
        if( nSelectPlayer < 0 || nSelectPlayer > MAX_PLAYER_COUNT )
            return false;

        if( !m_pPlayerAnim[nSelectPlayer] )
            return false;

        Box* pBBox = m_pPlayerAnim[nSelectPlayer]->GetWorldBBox();
        if( !pBBox )
            return false;

        int nDeltaX = vFrom.x - m_vEye.x;
        int nDeltaY = vFrom.y - m_vEye.y;
        float fDis = sqrtf( nDeltaX * nDeltaX + nDeltaY * nDeltaY );
        if( pBBox->IntersectCircle( *(Vector*)&vFrom, *(Vector*)&vDir, fDis ) )
        {
            ID_BUTTON_ENTEROnButtonClick( NULL );
            return true;
        }
    }
    return false;
}

void CUI_ID_FRAME_Select::SetAnimPos(int nIndex,TObjectInfo* pInfo)
{
	if(!pInfo)
		return;

	if(!pInfo->model)
		return;

	if(!pInfo->model->GetMex())
		return;

	MeMatrix* pMatrix = (MeMatrix*)pInfo->model->GetTransform();
	if(!pMatrix)
		return;

	m_vPlayerPos[nIndex].x = pMatrix->m[3][0];
	m_vPlayerPos[nIndex].y = pMatrix->m[3][1];
	m_vPlayerPos[nIndex].z = pMatrix->m[3][2];
	//m_fPlayerScale[nIndex] = pInfo->model->GetScale();
	m_fPlayerScale[nIndex] = 1.0f;

	float fx = 0,fy = 0,fz = 0;
	pInfo->model->GetRotation(fx,fy,fz);
	m_fPlayerRotate[nIndex] = fz;
}


void CUI_ID_FRAME_Select::InitPlayerAnim()
{
	initEquipIntensifyEffect();
	LoadScene();
	for (int nIndex = 0; nIndex < MAX_PLAYER_COUNT; ++nIndex)
	{
		if(!m_bSlotIsUsed[nIndex])
			continue;

		if ( !m_pPlayerAnim[nIndex] )
		{
			m_pPlayerAnim[nIndex] = MeNew CPlayerAnim;
			m_pPlayerAnim[nIndex]->EnableChildrenUpdateAndRender( false );
			m_pPlayerAnim[nIndex]->SetChangeAllEquipComplete( FALSE );
		}
		else
			continue;

		CPlayer_SEquipment equip[ eKeyAll_Max ];
		SCharBaseInfo info = m_stPlayerInfo[nIndex];
		SCharVisual visual = m_pVisual[nIndex];

		/*
		 * Author:	2012-7-26 wangshuai
		 * Desc: 	这个时候没有生成CPlayer对象, 但是如果变身为主将则需要换身
		 */
		if (info.liveinfo.hero_id != INVALID_HERO_ID)
		{
			CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(info.liveinfo.hero_id);
			if (itemHero != NULL&&visual.IsShowHero())
			{
				visual.hairId = itemHero->hero_faxing;
				visual.faceId = itemHero->hero_lianxing;
			}
		}
		int hair_id = -1;
		int face_id = -1;
		SetAllEquip( info.aptotic.usProfession, info.aptotic.ucSex, equip, &visual, NULL,visual.IsShowHero(),hair_id,face_id);

		int nHairColorIndex = /*visual.nHairColorIndex > 5 ? 1 : visual.nHairColorIndex < 1 ?  1 : visual.nHairColorIndex*/0;
		BOOL bMultiThreadLoadingMex = g_bMultiThreadLoadingMex;
		g_bMultiThreadLoadingMex = FALSE;

		// 时装时候带武器
		/*
		if( visual.GetViewSuitIndex() == 1 )//当前是时装
		{
		    SCharItem* pCharItem = &visual.GetAttriSuitArray()[EPT_RHandItem];
		    ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
		    if( pCommon )
		    {
		        ItemDefine::SItemWeapon* pWeapon = ( ItemDefine::SItemWeapon* )pCommon;						
		        equip[EPT_RHandItem].item = *pCharItem;
		        equip[EPT_RHandItem].iModelID  = pWeapon->ustModelID[0];
		        equip[EPT_RHandItem].iModelID2  = pWeapon->ustModelID[1];
		        equip[EPT_RHandItem].iModelID3 = pWeapon->ustIdleModelID;							
		    }
		    pCharItem = &visual.GetAttriSuitArray()[EPT_LHandItem];
		    pCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
		    if( pCommon )
		    {
		        ItemDefine::SItemWeapon* pWeapon = ( ItemDefine::SItemWeapon* )pCommon;						
		        equip[EPT_LHandItem].item = *pCharItem;
		        equip[EPT_LHandItem].iModelID  = pWeapon->ustModelID[0];
		        equip[EPT_LHandItem].iModelID2  = pWeapon->ustModelID[1];
		        equip[EPT_LHandItem].iModelID3 = pWeapon->ustIdleModelID;							
		    }
		}*/

		//===========================================================================
		
		m_pPlayer[nIndex] = MeNew CPlayer;
		m_pPlayer[nIndex]->SetAnim( m_pPlayerAnim[nIndex] );
		m_pPlayerAnim[nIndex]->SetPlayer( m_pPlayer[nIndex] );
		m_pPlayer[nIndex]->SetPos(m_vPlayerPos[nIndex].x,m_vPlayerPos[nIndex].y,m_vPlayerPos[nIndex].z);
		int _nIndex = GetEffectMgr()->RegisterCharEffectContainer();
		if( _nIndex >= 0 )
		{
			m_pPlayer[nIndex]->SetCharEffectContainer( GetEffectMgr()->GetCharEffectContainer( _nIndex ) );
		}

		//===========================================================================


		bool showHelmet = visual.IsShowHelmet() || visual.IsShowAecorative();

		//加角色
		m_pPlayerAnim[nIndex]->ChangeSkeletonAndEquipAll( equip, info.aptotic.ucSex, info.aptotic.usProfession, nHairColorIndex,
			visual.IsShowHelmet(), visual.IsShowAecorative(),visual.defaultModelIndex,info.liveinfo.hero_id,visual.IsShowHero());

		
		g_bMultiThreadLoadingMex = bMultiThreadLoadingMex;
		m_pPlayerAnim[nIndex]->UpdateHardItem( false, equip );

		if ( equip[eKeyAll_LHandItem].iModelID != 0 || equip[eKeyAll_RHandItem].iModelID != 0 )
		{
			m_pPlayerAnim[nIndex]->PlayAnimByActionName( "single_idle", MexAnimCtrl::eNormalPlay, 0, MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout, 0, "single_idle", MexAnimCtrl::eNormalPlay );
			if ( m_pPlayerAnim[nIndex]->GetAvatar() )
			{
				// 装备右手武器
				CAvatar::Component *pRightHandItem = m_pPlayerAnim[nIndex]->GetAvatar()->GetComponent(eKeyAll_RHandItem);
				BOOL bHoldFlag = FALSE;
				SCharItem *pCharItem = &visual.GetVisualArray()[EEquipPartType_Weapon];
				ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
				if ( pCommon )
				{
					if( pCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
					{
						ItemDefine::SItemWeapon *pWeapon = (ItemDefine::SItemWeapon *)pCommon;
						if( pWeapon->stWeaponType == eWeapontype_Flag )
							bHoldFlag = TRUE;
					}
				}
				if ( pRightHandItem && bHoldFlag )
				{
					// 拿着旗子
					for( int nAnim = 0; nAnim < CAvatar::eMaxPartAnim; nAnim++ )
					{
						MexAnimCtrl* pFlagAnim = pRightHandItem->GetMexAnim(nAnim);
						if( pFlagAnim && pFlagAnim->GetMexCfg() )
						{
							MexAnimCtrl::SPlayTask* pPlayTask = pFlagAnim->GetPlayTask(0);
							if( pPlayTask && stricmp(pPlayTask->szActionname, "single_idle") )
								pFlagAnim->PlayAnimByName( "single_idle", 0, TRUE );
						}
					}
				}
				for ( int i = 0; i < m_pPlayerAnim[nIndex]->GetAvatar()->GetComponentCount(); ++i)
				{
					CAvatar::Component* pComponent = m_pPlayerAnim[nIndex]->GetAvatar()->GetComponent(i);
					if( !pComponent )
						continue;

					IMex* pMex = pComponent->pMex;
					if( !pMex )
						continue;

					IMexGeometry* pGeometry = pMex->GetGeometry();
					if ( pGeometry )
					{
						for( int i = 0; i < pGeometry->GetChunkCount(); i++ )
						{
							IRenderable* pChunk = pGeometry->GetChunk( i );
							if ( pChunk == NULL )
								continue;

							pChunk->SetAvatarComponent();
						}
					}
				}
			}
		}
		else
		{
			m_pPlayerAnim[nIndex]->PlayAnimByActionName( "idle", MexAnimCtrl::eNormalPlay, 0, MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout, 0, "idle", MexAnimCtrl::eNormalPlay );
		}
	}
}

bool CUI_ID_FRAME_Select::SelectModelLButtonDown(OUT ControlObject* pSender)
{
	s_CUI_ID_FRAME_Select.PlayControlAnim();
	return true;
}

int  CUI_ID_FRAME_Select::GetPlayAnimBySel()
{
	int nResult = 0;
	if (m_pCamera == NULL || m_pCameraModel == NULL)
		return nResult;

	D3DXVECTOR3 vFrom,vDir;
	m_pCamera->BuildPickRay( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y, vFrom, vDir, SCREEN_WIDTH, SCREEN_HEIGHT );
	TPickResult castResult;
	if(SwGlobal::GetWorldPicker()->Pick( *(Vector*)&vFrom, *(Vector*)&vDir, castResult, emPT_ObjBBox, false, 1000 ) )
	{
		float fMinDis = 1000.0f;
		Vector vecCameraPos = m_pCameraModel->GetPosition();

		for(int i = 0;i < castResult.pickResultCount;++i)
		{
			TObjectInfo *pModelInfo = castResult.pickResultInfo[i].resultObjInfo;
			if (pModelInfo == NULL || pModelInfo->GetAlpha() <= 0.5f)
				continue;

			MexAnimCtrl* pAnimCtrl = castResult.pickResultInfo[i].resultObjInfo->model;
			if(!pAnimCtrl)
				continue;

			IMex* pMex = pAnimCtrl->GetMex();
			if(!pMex)
				continue;

			char pszName[MAX_PATH] = {0};
			strncpy(pszName, pMex->GetFilename(), sizeof(pszName)-1);
			strlwr(pszName);
			if(strstr(pszName, "p1"))
			{
				if(!m_bSlotIsUsed[0])
					continue;

				Vector vec = pAnimCtrl->GetPosition();
				Vector vecLen = vec - vecCameraPos;
				float fLen = vecLen.length();
				if(fLen < fMinDis)
				{
					nResult = 1;
					fMinDis = fLen;
				}
			}
			else if(strstr(pszName, "p2"))
			{
				if(!m_bSlotIsUsed[1])
					continue;

				Vector vec = pAnimCtrl->GetPosition();
				Vector vecLen = vec - vecCameraPos;
				float fLen = vecLen.length();
				if(fLen < fMinDis)
				{
					nResult = 2;
					fMinDis = fLen;
				}
			}
			else if(strstr(pszName, "p3"))
			{
				if(!m_bSlotIsUsed[2])
					continue;

				Vector vec = pAnimCtrl->GetPosition();
				Vector vecLen = vec - vecCameraPos;
				float fLen = vecLen.length();
				if(fLen < fMinDis)
				{
					nResult = 3;
					fMinDis = fLen;
				}
			}
			else if(strstr(pszName, "p4"))
			{
				if(!m_bSlotIsUsed[3])
					continue;

				Vector vec = pAnimCtrl->GetPosition();
				Vector vecLen = vec - vecCameraPos;
				float fLen = vecLen.length();
				if(fLen < fMinDis)
				{
					nResult = 4;
					fMinDis = fLen;
				}
			}
			else if(strstr(pszName, "p5"))
			{
				if(!m_bSlotIsUsed[4])
					continue;

				Vector vec = pAnimCtrl->GetPosition();
				Vector vecLen = vec - vecCameraPos;
				float fLen = vecLen.length();
				if(fLen < fMinDis)
				{
					nResult = 5;
					fMinDis = fLen;
				}
			}
		}
	}
	return nResult;
}

void  CUI_ID_FRAME_Select::PlayControlAnim()
{
	int nIndex = GetPlayAnimBySel();
	if(nIndex == 0)
		return;

	PlayAnimByIndex(nIndex);
	Refeash(nIndex - 1);
}

void CUI_ID_FRAME_Select::PlayAnimByIndex(int nIndex)
{
	if(!m_pCameraModel)
		return;

	if(!m_bSlotIsUsed[nIndex - 1])
	{
		//判断是否可以创建角色
		if(m_PlayerInfoList.m_PlayerList.size() >= MAX_PLAYER_COUNT)
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(ePlayerCountIsFull) );
			return;
		}
		m_nSlotEmpty = nIndex - 1;
		m_bToCreate = true;
		return;
	}

	char szAnim[64] = {0};
	MeSprintf_s(szAnim,sizeof(szAnim),"p%d",nIndex);

	if(m_strLastSel.compare(szAnim) == 0)
		return;

	char szWord[64] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s_%s",m_strLastSel.c_str(),szAnim);
	m_pCameraModel->PlayAnimByName(szWord, 0, FALSE);

	m_strLastSel = szAnim;
	m_nCurrSel = nIndex - 1;

	SetCheckBoxByIndex(m_nCurrSel);

	char szText[64] = {0};
	MeSprintf_s(szText,sizeof(szText),"播放动画为:%s\n",szWord);
	::OutputDebugStr(szText);

	if(s_CUI_ID_FRAME_ChangeName.IsVisable())
		s_CUI_ID_FRAME_ChangeName.SetVisable(false);
}

void CUI_ID_FRAME_Select::SetPlayerInfo(int nIndex)
{
	if(!m_pID_FRAME_SELECT)
		return;

	if(nIndex < 0 || nIndex >= MAX_PLAYER_COUNT)
		return;

    if ( !m_bSlotIsUsed[nIndex] )
	{
		//设置等级
		m_pID_TEXT_Levs[nIndex]->SetVisable(false);

		//设置名字
		//zhuxincong

		//m_pID_TEXT_Names[nIndex]->SetVisable(false);
		if(m_PlayerInfoList.m_PlayerList.size() < MAX_PLAYER_COUNT)
		{
			char szInfo[256] = {0};
			MeSprintf_s(szInfo,sizeof(szInfo),"%s",theXmlString.GetString( eText_ClickCreatePlayer ));
			m_pID_TEXT_Names[nIndex]->SetText(szInfo);
			m_pID_TEXT_Names[nIndex]->SetVisable(true);
		}
		else
		{
			m_pID_TEXT_Names[nIndex]->SetText("");
			m_pID_TEXT_Names[nIndex]->SetVisable(true);
		}

		//设置职业
		m_pID_TEXT_Jobs[nIndex]->SetVisable(false);

		//设置职业图标
		for (int i = 0;i < EArmType_MaxSize;++i)
		{
			if(m_pID_PICTURE_Jobs[nIndex][i])
				m_pID_PICTURE_Jobs[nIndex][i]->SetVisable(false);
		}


		switch(nIndex)
		{
		case 0:
			m_pID_TEXT_DeleteInfo0->SetVisable(false);
			break;
		case 1:
			m_pID_TEXT_DeleteInfo1->SetVisable(false);
			break;
		case 2:
			m_pID_TEXT_DeleteInfo2->SetVisable(false);
			break;
		default:
			break;
		}
	}
	else
	{
		//设置等级
		char szInfo[256] = {0};
		MeSprintf_s( szInfo, sizeof(szInfo), "%d",m_stPlayerInfo[nIndex].liveinfo.ustLevel );
		m_pID_TEXT_Levs[nIndex]->SetText(szInfo);
		m_pID_TEXT_Levs[nIndex]->SetVisable(true);

		//设置名字
		MeSprintf_s(szInfo,sizeof(szInfo),"%s",m_stPlayerInfo[nIndex].aptotic.szCharacterName);
		m_pID_TEXT_Names[nIndex]->SetText(szInfo);
		m_pID_TEXT_Names[nIndex]->SetVisable(true);

		//设置职业
		CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( m_stPlayerInfo[nIndex].aptotic.usProfession );

		m_pID_TEXT_Jobs[nIndex]->SetText(pProInfo->m_strProShow.c_str());
		m_pID_TEXT_Jobs[nIndex]->SetVisable(true);

		//设置职业图标
		for (int i = 0;i < EArmType_MaxSize;++i)
		{
			if(m_pID_PICTURE_Jobs[nIndex][i])
				m_pID_PICTURE_Jobs[nIndex][i]->SetVisable(false);
		}

		int nJob = m_stPlayerInfo[nIndex].aptotic.usProfession;
		if(nJob < 0 || nJob >= eWeaponType_Max)
			return;

		if(m_pID_PICTURE_Jobs[nIndex][nJob])
			m_pID_PICTURE_Jobs[nIndex][nJob]->SetVisable(true);
		
		char szData[256] = {0};
		if(m_bIsDel[nIndex])
		{
			int nDay = m_dwDelTime[nIndex]/OneDaySecond;
			MeSprintf_s(szData,sizeof(szData),theXmlString.GetString(eText_SelPlayerDelLifeTime),nDay);
		}
		switch(nIndex)
		{
		case 0:
			{
				m_pID_TEXT_DeleteInfo0->SetVisable(m_bIsDel[nIndex]);
				m_pID_TEXT_DeleteInfo0->SetText(szData);
			}
			break;
		case 1:
			{
				m_pID_TEXT_DeleteInfo1->SetVisable(m_bIsDel[nIndex]);
				m_pID_TEXT_DeleteInfo1->SetText(szData);
			}
			break;
		case 2:
			{
				m_pID_TEXT_DeleteInfo2->SetVisable(m_bIsDel[nIndex]);
				m_pID_TEXT_DeleteInfo2->SetText(szData);
			}
			break;
		default:
			break;
		}
	}
}


void CUI_ID_FRAME_Select::EnterGame(int nIndex)
{
	if ( nIndex >= 0 && nIndex < MAX_PLAYER_COUNT &&
		m_bSlotIsUsed[nIndex] == true )
	{
		if(m_bIsDel[nIndex])
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_IsDelChar) );
			return;
		}

		if(m_stPlayerInfo[nIndex].liveinfo.ChangeName !=0)
		{
			s_CUI_ID_FRAME_ChangeName.SetVisable(true);
			s_CUI_ID_FRAME_ChangeName.Clear();
			return;
		}
		else
		{
			s_CUI_ID_FRAME_ChangeName.SetVisable(false);
		}
		CUserData::Instance()->ReadUserData();
		// 窗口名称显示国家 added by ZhuoMeng.Hu		[10/20/2010]
		uint8 nCountryID = m_stPlayerInfo[nIndex].aptotic.ucCountry;
		std::string strWindowName = m_strWindowText + " " + CountryFunction::GetDefaultCountryNameById( nCountryID );
		theHeroGame.SetWindowText( strWindowName.c_str() );

		MsgEnterWorld msg;
		msg.stWhichSlot = m_PlayerInfoList.GetSlotByPageIndex(nIndex);
		msg.dwCharacterID = m_bSlotCharacterID[nIndex];
		msg.dwEnterWorldTime = HQ_TimeGetTime();
		msg.dwAccountId = theHeroGame.GetPlayerMgr()->m_dwAccountID;
		g_nCharacterDBID = m_bSlotCharacterID[nIndex];
		theHeroGame.GetPlayerMgr()->sPlayerSlot = m_PlayerInfoList.GetSlotByPageIndex(nIndex);
		GettheNetworkInput().SendMsg(&msg, msg.GetLength() );
		//GettheNetworkInput().CheckSendReq();

		s_CUI_ID_FRAME_LOGIN.SetControlMode(m_nControlMode);

		m_pID_BUTTON_ENTER->SetEnable(false);

		m_isEnterWorld = true;

		//if (pSender)
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_WaitEnterWorld), "", CUI_ID_FRAME_MessageBox::eTypeCancel, true, EnterWorldFailed);
			s_CUI_ID_FRAME_MessageBox.SetAutoClose(30, false);

			s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false);
			s_CUI_ID_FRAME_MessageBox.SetButVisableCancel(false);
		}
	}
}

bool CUI_ID_FRAME_Select::IsHavePlayer()
{
	for (int n = 0;n < MAX_PLAYER_COUNT;++n)
	{
		if( m_bSlotIsUsed[n] )
			return false;
	}
	return true;
}

void CUI_ID_FRAME_Select::SetCurrSelectPlayer()
{
	m_IsSetCameraForCreate = true;
}

void CUI_ID_FRAME_Select::SetCheckBoxByIndex(int nIndex)
{
	if(!m_pID_FRAME_SELECT)
		return;

	m_pID_CHECKBOX_PLAYER0->SetCheck(false);
	m_pID_CHECKBOX_PLAYER1->SetCheck(false);
	m_pID_CHECKBOX_PLAYER2->SetCheck(false);

	switch(nIndex)
	{
	case 0:
		m_pID_CHECKBOX_PLAYER0->SetCheck(true);
		break;
	case 1:
		m_pID_CHECKBOX_PLAYER1->SetCheck(true);
		break;
	case 2:
		m_pID_CHECKBOX_PLAYER2->SetCheck(true);
		break;
	default:
		assert(0&&"索引错误");
		break;
	}
}

#define  EffectModeNum 14 
const char *EquipIntensifyModePatch[EffectModeNum] =
{
	"Data\\Magic\\Common\\Star\\Level_6\\6_body.mex",
	"Data\\Magic\\Common\\Star\\Level_9\\9_body.mex",
	"Data\\Magic\\Common\\Star\\Level_9\\9_hand.mex",
	"Data\\Magic\\Common\\Star\\Level_9\\9_hand.mex",
	"Data\\Magic\\Common\\Star\\Level_12\\12_body.mex",
	"Data\\Magic\\Common\\Star\\Level_12\\12_hand.mex",
	"Data\\Magic\\Common\\Star\\Level_15\\15_body.mex",
	"Data\\Magic\\Common\\Star\\Level_15\\15_hand.mex",
	"Data\\Magic\\Common\\Star\\Level_15\\15_foot.mex",
	"Data\\Magic\\Common\\Star\\Level_18\\18_body.mex",
	"Data\\Magic\\Common\\Star\\Level_18\\18_back.mex",
	"Data\\Magic\\Common\\Star\\Level_18\\18_foot.mex",
	"Data\\Magic\\Common\\Star\\Level_18\\18_LeftHand.mex",
	"Data\\Magic\\Common\\Star\\Level_18\\18_RightHand.mex",
	
};	

bool  CUI_ID_FRAME_Select::initEquipIntensifyEffect()
{
	for (int i = 0; i< EffectModeNum ; i++)
	{
		 GetMexResMgr()->CreateModel( EquipIntensifyModePatch[i], false );
	}
   
	return false;
}
void CUI_ID_FRAME_Select::ChangeName()
{
	m_pID_TEXT_Names[m_nCurrSel]->SetText(s_CUI_ID_FRAME_ChangeName.GetTextName().c_str());//设置新的名称
	m_stPlayerInfo[m_nCurrSel].liveinfo.ChangeName = 0;
	int Index = m_PlayerInfoList.GetSlotByPageIndex(m_nCurrSel);
	//应该设置到集合里面去
	std::vector<SelectPlayerInfo>::iterator Iter = m_PlayerInfoList.m_PlayerList.begin();
	for(;Iter != m_PlayerInfoList.m_PlayerList.end();++Iter)
	{
		if(Iter->m_SlotID == Index)
		{
			Iter->m_stPlayerInfo.liveinfo.ChangeName = 0;
			strcpy_s(Iter->m_stPlayerInfo.aptotic.szCharacterName,dr_MaxPlayerName-1,s_CUI_ID_FRAME_ChangeName.GetTextName().c_str());
			return;
		}
	}
}
int  CUI_ID_FRAME_Select::GetCurSelectPlayerID()
{
	return m_stPlayerInfo[m_nCurrSel].liveinfo.ChangeName;
}