/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\ui\Create.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Create.h"
#include "Select.h"
#include "GameMain.h"
#include "GlobalDef.h"
#include "../PlayerAnimCtrl.h"
#include "../PlayerEquip.h"
#include "MessageBox.h"
#include "avatarsystemsetting.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Engine/Engine.h"
#include "SystemConfig.h"
#include "Select.h"
#include "XmlStringLanguage.h"
#include "chatcheck.h"
#include "../Cfg.h"
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
#include "SystemSetting.h"
#include "core/Name.h"
#include "Me3d/ShaderMgr.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Model/Mex2.h"
#include "Me3d/Shader.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Engine/RendererDX.h"
#include "GameMain.h"
#include "Player.h"
#include "Common.h"
#include "CountryDefine.h"		//added by zhuomeng.hu		[8/19/2010]
//#include "Launcher/DataLauncher.h"
#include "CountryFunction.h"
#include "PlayerInfoMgr.h"
#include "Me3d\PostProcess\PostProcess.h"
#include "Me3d\PostProcess\PostProcessManager.h"

extern BOOL g_bMultiThreadLoadingMex; //多线程加载MEX
extern BOOL	g_bCreateOk;
extern CHeroGame* theApp;
extern GAME_STATE	g_GameState;

//应策划需求改为6 原来8  lyh
#define MAX_CREATE_LENGTH	6

//#define SELECT_CAMERA_MEX		"select.mex"
#define SELECT3_CAMERA_MEX		"select3.mex"
#define SELECT_CAMERA_MODEL		"selectcamera"
#define SELECT_CAMERA_TARGET	"selecttarget"
#define SELECT_CHARACTOR_MEX	"character.mex"
#ifndef PORTRAIT_PATH
#define PORTRAIT_PATH			"..\\Data\\Ui\\HeadPicture\\Player\\"		//added by zhuomeng.hu		[8/24/2010]
#endif
#ifndef PORTRAIT_FILE
#define PORTRAIT_FILE			"HeadPicture\\Player\\"						//added by zhuomeng.hu		[8/24/2010]
#endif
#ifndef PORTRAIT_SCALE
#define PORTRAIT_SCALE		64							//added by ZhuoMeng.Hu		[9/19/2010]
#endif

CUI_ID_FRAME_CREATE s_CUI_ID_FRAME_CREATE;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CREATE, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CREATE, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_EDIT_NameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_CheckNameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_HairLOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_HairROnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_HeadLOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_HeadROnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_TurnROnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_TurnLOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_BackOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_ManOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_WomanOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_JiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_DaoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_WuOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_JianOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_QiangOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_JobOtherOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_RandomOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_ResetOnButtonClick )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_SCROLLBAREX_StatureOnScrollBarExUpdatePos )

// 国家  added by zhuomeng.hu		[8/18/2010]
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_Country1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_Country2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_Country3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_Country4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_CountryAutoOnCheckBoxCheck )

// 头像		added by zhuomeng.hu		[8/20/2010]
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_Portrait1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_Portrait2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_Portrait3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_CHECKBOX_Portrait4OnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_HeadUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_HeadDownOnButtonClick )

MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_COMBOBOX_MonthOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_COMBOBOX_DayOnComboBoxChange )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_NearOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_FarnessOnButtonClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_ArmourROnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CREATE, ID_BUTTON_ArmourLOnButtonClick )
static bool s_bRotate = false;
static bool m_bToSelect;	//创建人物-> 选择人物状态的切换标志记录
static bool s_bPressEnter = false;

extern int PlayEffect( const char* pEffectName, CPlayer* pSrcPlayer = NULL, float fScale = 0 , DWORD dwFlyTime = 0, CPlayer* pDestPlayer = NULL, int nSlot = 0 ,bool bCalDist = true);

static bool TurnOnLButtonDown( INT nX, INT nY )
{
	s_bRotate = true;
	return true;
}

static bool TurnOnLButtonUp( INT nX, INT nY )
{
	s_bRotate = false;
	return true;
}

bool FocusToNameEdit( char bIsTell,void *pData )
{
	if(s_CUI_ID_FRAME_CREATE.GetEditName())
		theUiManager.SetFocus( s_CUI_ID_FRAME_CREATE.GetEditName() );
	return true;
}

enum EGetBirthdayInfo
{
	E_Birthday_success = 0,
	E_Birthday_empty,
	E_Birthday_failure,
};

uint8 GetDayCount(uint8 month_)
{
	if(0 == month_ || month_ > 12)
		return 0;

	const uint8 days[] = {31, 29, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31};

	return days[month_ - 1];
}

EGetBirthdayInfo GetBirthday(ControlComboBox* pMonthBox_, ControlComboBox* pDayBox_, uint8 &_month, uint8 &_day)
{
	if(NULL == pMonthBox_ || NULL == pDayBox_)
		return E_Birthday_failure;

	const char *pString = pMonthBox_->GetEditInput().GetText();
	if(NULL == pString || 0 == strlen(pString))
		return E_Birthday_empty;

	_month = atoi(pString);
	if(_month <= 0 || _month > 12)
		return E_Birthday_empty;

	pString = pDayBox_->GetEditInput().GetText();
	if(NULL == pString || 0 == strlen(pString))
		return E_Birthday_empty;

	_day = atoi(pString);
	if(_day <= 0 || _day > GetDayCount(_month))
		return E_Birthday_empty;

	return E_Birthday_success;
}

void CUI_ID_FRAME_CREATE::InitMonthCombobox(ControlComboBox* _pBox_)
{
	assert(_pBox_ != NULL);
	if(NULL == _pBox_)
		return;

	//设置内容
	ControlList& list = _pBox_->GetListBox();
	list.Clear();

	ControlList::S_List stItem;
	stItem.clear();
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	stItem.SetMargin( 5 );

	char buf[3];
	for(int i = 1; i <= 12; ++i)
	{
		sprintf(buf, "%d", i);
		stItem.SetData(buf, i - 1);
		list.AddItem(&stItem);
	}
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	_pBox_->GetEditInput().SetText(sys.wMonth);
	InitDayCombobox(m_pID_COMBOBOX_Day,sys.wMonth);
	m_pID_COMBOBOX_Day->GetEditInput().SetText(sys.wDay);
}

void CUI_ID_FRAME_CREATE::InitDayCombobox(ControlComboBox* _pBox_, uint8 month_)
{
	assert(_pBox_ != NULL && month_ >= 1 && month_ <= 12);
	if(_pBox_ != NULL && month_ >= 1 && month_ <= 12)
	{
		//设置内容
		ControlList& list = _pBox_->GetListBox();
		list.Clear();

		ControlList::S_List stItem;
		stItem.clear();
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		stItem.SetMargin( 5 );

		uint8 days = GetDayCount(month_);
		assert(days >= 1 && days <= 31);
		if(days >= 1 && days <= 31)
		{
			char buf[3];
			for(int i=1; i<=days; ++i)
			{
				sprintf(buf, "%d", i);
				stItem.SetData(buf, i - 1);
				list.AddItem(&stItem);
			}
		}
		_pBox_->GetEditInput().SetText(days);
	}
}


CUI_ID_FRAME_CREATE::CUI_ID_FRAME_CREATE()
{
	// Member
	m_pID_FRAME_CREATE = NULL;
//	m_pID_PICTURE_Property = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_PICTURE_JobWall = NULL;
	m_pID_EDIT_Name = NULL;
	m_pID_BUTTON_CheckName = NULL;
	m_pID_PICTURE_HairWall = NULL;
	m_pID_PICTURE_FaceWall = NULL;
	m_pID_BUTTON_HairL = NULL;
	m_pID_BUTTON_Reset = NULL;
	m_pID_BUTTON_HairR = NULL;
	m_pID_BUTTON_HeadL = NULL;
	m_pID_BUTTON_HeadR = NULL;
	m_pID_PICTURE_TitlePic = NULL;
	m_pID_PICTURE_FenGe = NULL;
	m_pID_BUTTON_TurnR = NULL;
	m_pID_BUTTON_TurnL = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_Hair = NULL;
	m_pID_TEXT_Face = NULL;
	m_pID_TEXT_ProName = NULL;
	m_pID_TEXT_ProInfo = NULL;
// 	m_pID_PICTURE_Spear = NULL;
// 	m_pID_PICTURE_Sword = NULL;
// 	m_pID_PICTURE_Staff = NULL;
// 	m_pID_PICTURE_Fan = NULL;
// 	m_pID_PICTURE_Bow = NULL;
// 	m_pID_TEXT_Sex = NULL;
// 	m_pID_TEXT_Man = NULL;
// 	m_pID_TEXT_Woman = NULL;
	m_pID_CHECKBOX_Man = NULL;
	m_pID_CHECKBOX_Woman = NULL;
	m_pID_CHECKBOX_Spear = NULL;
	m_pID_CHECKBOX_Sword = NULL;
	m_pID_CHECKBOX_Staff = NULL;
	m_pID_CHECKBOX_Bow = NULL;
	m_pID_CHECKBOX_Fan = NULL;
	m_pID_CHECKBOX_JobOther = NULL;
	m_pID_SCROLLBAREX_Stature = NULL;
	//m_pID_TEXT_StatureZ = NULL;
	m_pID_TEXT_Low = NULL;
	m_pID_TEXT_High = NULL;

	// 国家 added by zhuomeng.hu		[8/18/2010]
	m_pID_CHECKBOX_Country1 = NULL;
	m_pID_CHECKBOX_Country2 = NULL;
	m_pID_CHECKBOX_Country3 = NULL;
	m_pID_CHECKBOX_Country4 = NULL;
	m_pID_TEXT_CountryDesc = NULL;
	m_pID_PICTURE_CountryIcon1 = NULL;
	m_pID_PICTURE_CountryIcon2 = NULL;
	m_pID_PICTURE_CountryIcon3 = NULL;
	m_pID_PICTURE_CountryIcon4 = NULL;
	m_pID_PICTURE_CountryIconRandom = NULL;
	m_pID_TEXT_CountryName = NULL;
	m_pID_CHECKBOX_CountryAuto = NULL;
	m_pID_TEXT_CountryAutoText = NULL;
	m_pID_TEXT_CountryAutoDesc = NULL;

	// 头像	added by zhuomeng.hu		[8/20/2010]
	m_pID_CHECKBOX_Portrait1 = NULL;
	m_pID_CHECKBOX_Portrait2 = NULL;
	m_pID_CHECKBOX_Portrait3 = NULL;
	m_pID_CHECKBOX_Portrait4 = NULL;
	m_pID_BUTTON_HeadUp = NULL;
	m_pID_BUTTON_HeadDown = NULL;

	m_pID_TEXT_ShengRi = NULL;
	m_pID_TEXT_Month = NULL;
	m_pID_TEXT_Day = NULL;
	m_pID_COMBOBOX_Month = NULL;
	m_pID_COMBOBOX_Day = NULL;

	m_pID_BUTTON_Near = NULL;
	m_pID_BUTTON_Farness = NULL;

	m_pID_BUTTON_ArmourR = NULL;
	m_pID_BUTTON_ArmourL = NULL;
	m_pID_TEXT_Armour = NULL;

	m_bToSelect     = false;
	//m_bToSelectWeapon   = false;
	s_bPressEnter   = false;

	m_nSex          = 1;
	m_nCountry      = EArmType_Warrior;
	m_nRealCountry	= CountryDefine::Country_Init;//CountryDefine::Country_Init;	// 初始化国家	added by zhuomeng.hu		[8/18/2010]
	m_nFace         = 0;
	m_nHair         = 0;
	m_nCloth        = 0;
	m_nHairColor    = 1;
	m_pPlayerAnim   = NULL;
	m_bUpdateOnce   = FALSE;
	m_vPlayerPos    = D3DXVECTOR3(0,0,0);
	m_vEye          = D3DXVECTOR3(0,0,0);
	m_vLookat       = D3DXVECTOR3(0,0,1);
	m_bIsTileLoaded = false;
	m_fRot          = 0.f;
	m_pCamera		= NULL;
	s_hImcDef       = NULL;
	m_pCameraModel  = NULL;
	m_pBGModel	= NULL;
	m_bNeedZoomIn  = false;
	m_bNeedZoomOut = false;
	m_bCameraZoomIn = false;
	m_fPlayerScale  = 1.f;
	m_fPlayerBaseScale = 1.f;

	m_pPlayer       = NULL;
	m_bNeedPlayEffect = false;
	strcpy(m_szEffectName, "");
	m_iEffectID     = 0;
    m_nSelEquip     = 0;
	             m_nDefaultHair = 0;
	             m_nDefaultFace = 0;
}

// Frame
bool CUI_ID_FRAME_CREATE::OnFrameRun()
{
	guardfunc;
	if( !m_bUpdateOnce )
		m_bUpdateOnce = TRUE;
	if( s_bPressEnter )
	{
		ID_BUTTON_OKOnButtonClick(NULL);
		s_bPressEnter = false;
	}
	return true;
	unguard;
}

bool CUI_ID_FRAME_CREATE::OnFrameRender()
{
	guardfunc;
	if (SystemSetting::Instance()->IsLowLevelCard())
	{
		SwGlobal::GetRender()->SetRenderDoodad(false);
		graphics::ShaderManager::instance()->useShader(false);
	}

	IRenderer* RI = GetEngine()->GetRenderer();
	RI->SetRenderState( D3DRS_FOGENABLE, true );

	CWorldBuffer *pbuffer = SwGlobal::GetWorld()->GetWorldBuffer();
	if (pbuffer && !m_bIsTileLoaded)
	{
 		CWorldTile* pActiveTile = pbuffer->GetTile(gCfg.m_nCreateMapId);
		pbuffer->SetActiveTile(pActiveTile) ;
		m_bIsTileLoaded = true;

		// 获取相机和人物位置
		BOOL bFindCamera = FALSE;
		BOOL bFindCharacter = FALSE;
		BOOL bFindBG = FALSE;

		CResMgr *pResMgr = pActiveTile->GetCResMgr();
		assert( pResMgr );
		char pszName[MAX_PATH] = {0};
		for (size_t i = 0; i < pResMgr->GetStaticModelList().size(); ++i )
		{
			TObjectInfo* pInfo = pResMgr->GetStaticModel(i);
			if( pInfo->model && pInfo->model->GetMex() )
			{
				strncpy(pszName, pInfo->model->GetMex()->GetFilename(), sizeof(pszName)-1);
				strlwr(pszName);
				if( strstr(pszName, SELECT_CHARACTOR_MEX) )
				{
					MeMatrix* pMatrix  = (MeMatrix*)pInfo->model->GetTransform();
					m_vPlayerPos.x = pMatrix->m[3][0];
					m_vPlayerPos.y = pMatrix->m[3][1];
					m_vPlayerPos.z = pMatrix->m[3][2];
					m_fPlayerBaseScale = pInfo->model->GetScale();
					bFindCharacter = TRUE;
					if( m_pPlayer )
					{
						m_pPlayer->SetPos(m_vPlayerPos.x, m_vPlayerPos.y, m_vPlayerPos.z);
						m_pPlayer->SetDir(m_fRot);
						if( m_pPlayer->GetCharEffectContainer() )
						{
							IEffectHelper* pEffectHelper = m_pPlayer->GetCharEffectContainer()->GetEffectHelper( eEffectBindPart_Foot );
							if( pEffectHelper )
								pEffectHelper->SetPos( m_vPlayerPos.x, m_vPlayerPos.y, m_vPlayerPos.z );
						}
					}
				}
				else if (strstr(pszName, SELECT3_CAMERA_MEX)) //暂时用这个代替一下
				{
					m_pCameraModel = pInfo->model;
					m_pCameraModel->PlayAnimByName("farhold",0);
					bFindCamera = TRUE;
				}
				if (bFindCharacter && bFindCamera /*&& bFindBG*/)
					break;
			}
		}
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
	if( m_pPlayerAnim )
	{
		D3DXMATRIX matTransform;
		m_pPlayerAnim->SetPosition(*((Vector*)&m_vPlayerPos));
		m_pPlayerAnim->SetScale(PlayerInfoMgr::Instance()->GetScale4CreateUI(m_nSex, m_fPlayerScale));

		if (s_bRotate && m_pID_BUTTON_TurnR->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			m_fRot += 1.5f * theHeroGame.GetFrameElapsedTime();
		}
		else if (s_bRotate && m_pID_BUTTON_TurnL->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
		{
			m_fRot -= 1.5f * theHeroGame.GetFrameElapsedTime();
		}
		else
			s_bRotate = false;

		m_pPlayerAnim->SetRotationZ(m_fRot);

		//m_pPlayerAnim[nIndex]->SetScale( GetMe3dConfig()->m_fMdlSpaceScale );
		//m_pPlayerAnim[nIndex]->SetRotationZ( D3DX_PI + 5.0265479f );
		//m_pPlayerAnim[nIndex]->SetUpperRot( D3DX_PI + 5.0265479f );
		m_pPlayerAnim->CalcTransformMatrix( (MeMatrix*)&matTransform );
		m_pPlayerAnim->Update( HQ_TimeGetTime(), (MeMatrix*)&matTransform );	
		m_pPlayerAnim->UpdateComponents( HQ_TimeGetTime(), (MeMatrix*)&matTransform );
		GetEffectMgr()->SetTheLookerPos( m_vPlayerPos );
		GetEffectMgr()->SetTheLookerViewDistance( 50 );
	}
	if( m_bNeedPlayEffect && m_szEffectName[0] != '0')
	{
		m_bNeedPlayEffect = false;
		BOOL bBackUp = g_bMultiThreadLoadingMex;
		g_bMultiThreadLoadingMex = FALSE;
		if( m_iEffectID != 0 )
		{
			IEffect *pEffect = GetEffectMgr()->GetEffect( m_iEffectID );
			if( pEffect )
			{
				pEffect->SetDead();
			}
		}
		m_iEffectID = PlayEffect(m_szEffectName, m_pPlayer, 100.f);
		g_bMultiThreadLoadingMex = bBackUp;
		m_szEffectName[0] = '0';
	}

	float fAspect = (float)SCREEN_WIDTH/SCREEN_HEIGHT;
	{
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

	fAspect = (float)SCREEN_WIDTH/SCREEN_HEIGHT;
	m_pCamera->SetProjParams( D3DX_PI/4.f, fAspect,  1.0, 18000.0f );

	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&m_pCamera->GetViewMatrix() );
	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&m_pCamera->GetProjMatrix() );

	RI->SetEyePt( (float*)&m_vEye );
	RI->SetLookatPt( (float*)&m_vLookat );

	FrustumEx frustum;	
	frustum.BuildFrustum( m_pCamera->GetProjMatrix(),m_pCamera->GetViewMatrix() );

	//render shadow
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
	
	//RI->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );

	D3DLIGHT9 kLight;
	kLight.Type = D3DLIGHT_DIRECTIONAL;	
	kLight.Ambient = D3DXCOLOR( 1,1,1,1 );
	kLight.Diffuse = D3DXCOLOR( 1,1,1,1 );
	kLight.Specular = D3DXCOLOR( 1,0.6f,0.6f,0.6f );
	/*kLight.Direction = vNewLightDir;	*/
	RendererDx* pRenderer = (RendererDx*)RI;
// 	bool bUseShader = graphics::ShaderManager::instance()->isUseShader();
// 	if( !bUseShader )
// 		pRenderer->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kLight );

	if( m_pPlayerAnim )
	{        
		m_pPlayerAnim->Render();     
	}
	// 渲染人物特效
	/*GetEffectMgr()->Update( HQ_TimeGetTime() );
	GetEffectMgr()->Render();

	GetEngine()->GetRenderer()->Flush( eSortByFarZ );

	GetMe3dConfig()->SetMipLodBais(fOldBias);*/

	MeRenderManager::Instance()->DoRender(true);

	RI->SetRenderState( D3DRS_FOGENABLE, false );
	return true;
	unguard;
}
// Edit
void CUI_ID_FRAME_CREATE::ID_EDIT_NameOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_CheckNameOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return false;
	}

	if( m_pID_EDIT_Name->GetText() ) 
	{
		std::string strCin =  m_pID_EDIT_Name->GetText();
		if( strCin.length() == 0 )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NeedInputName), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true, FocusToNameEdit );
			return true;
		}
		//接下来需要把这个szName传给服务器数据库搜索名字是否重复
		MsgReqCreateCheckName msg;
		memcpy(msg.szName, strCin.c_str(), strCin.length());
		msg.szName[strCin.length()] = 0;

		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_HairLOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return false;
	}

	int nCount = m_pMaleHairId->nCount;
	if( m_nSex == 1 )
	{
		nCount = m_pFemaleHairId->nCount;
	}
	m_nHair--;
	if ( m_nHair >= nCount || m_nHair < 0 )	
	{
		m_nHair = nCount-1;
	}
	Refresh( false, false );
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_HairROnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return false;
	}

	int nCount = m_pMaleHairId->nCount;
	if( m_nSex == 1 )
	{
		nCount = m_pFemaleHairId->nCount;
	}
	m_nHair++;
	if ( m_nHair >= nCount || m_nHair < 0 )
	{
		m_nHair = 0;
	}
	Refresh( false, false );
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_HeadLOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return false;
	}

	//int nCount = m_pGame->GetSample()->GetFaceCount();
	int nCount = m_pMaleFaceId->nCount;
	if( m_nSex == 1 )
	{
		nCount = m_pFemaleFaceId->nCount;
	}
	m_nFace--;
	if ( m_nFace >= nCount || m_nFace < 0 )
	{
		m_nFace = nCount-1;
	}
	Refresh( false, false );
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_HeadROnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if (!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return false;
	}

	int nCount = m_pMaleFaceId->nCount;
	if ( m_nSex == Sex_Female )
	{
		nCount = m_pFemaleFaceId->nCount;
	}
	m_nFace++;
	if ( m_nFace >= nCount || m_nFace < 0 )
	{
		m_nFace = 0;
	}
	Refresh( false, false );
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_TurnROnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_TurnLOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return false;
	}


	//--		在server端使用存储过程来检测		暂且屏蔽   
    // 增加了玩家名在DB非法的判断 (原先只有DB自己判断)       added by zhuomeng.hu		[1/6/2011]
    if( CChatCheck::getInstance()->CheckStringInLow(m_pID_EDIT_Name->GetText()) == false || !CheckCreateName( std::string( m_pID_EDIT_Name->GetText() ) ) )
	{
		theUiManager.SetFocus(NULL);
        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eCreate_NameError ), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, false, FocusToNameEdit );
        return false;
    }
    //---

	uint8 month, day;
	if (GetBirthday(m_pID_COMBOBOX_Month,m_pID_COMBOBOX_Day,month,day) == E_Birthday_success)
	{
		char temp[64];
		MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_CreateBrithDay),month,day,GetXinZuo(month,day));
		s_CUI_ID_FRAME_MessageBox.Show(temp,"",CUI_ID_FRAME_MessageBox::eTypeYesNo,false,CreateRole);
		return true;
	}
	if(GetBirthday(m_pID_COMBOBOX_Month, m_pID_COMBOBOX_Day, month, day) != E_Birthday_success)
	{
		theUiManager.SetFocus(NULL);
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eCreate_BirthdayError), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, false, FocusToNameEdit );
		return false;
	}
//     if ( /*strcmp(szName,DEF_PLAYER_NAME) != 0 &&*/
//         wcslen(szName) > 0 && wcslen(szName) <= MAX_CREATE_LENGTH/2 )
	return true;
	unguard;
}
void CUI_ID_FRAME_CREATE::SendCreateRoleMsg()
{
	 const WCHAR *szName = m_pID_EDIT_Name->GetTextW();
	if( wcslen(szName) > 0 )
	{
		m_nCloth = m_nSelEquip;
		MsgCreateHeroChar	msg;
		msg.stWhichSlot = s_CUI_ID_FRAME_Select.GetSlotEmpty();         //UI_ID_FRAME_SELECT::m_nSlotEmpty;
		msg.fModelPercent = m_fPlayerScale;
		strncpy( msg.create.szCharacterName, m_pID_EDIT_Name->GetText(), sizeof(msg.create.szCharacterName)-1 );	// 姓名
		msg.create.usProfession = (unsigned char)m_nCountry;        	// 职业
		msg.create.ucSex = m_nSex;										// 性别
		msg.create.ucHairColorIndex = (unsigned char)m_nHairColor;      //头发颜色的索引
		msg.create.ucHairModelIndex = (unsigned char)m_nHair;           //头发模型的索引
		msg.create.ucFaceIndex = (unsigned char)m_nFace;                //脸
		msg.create.ucModelIndex = (unsigned char)m_nCloth;              //身体模型的索引
		msg.create.ucCountry = (unsigned char)m_nRealCountry;		//	国家			added by zhuomeng.hu		[8/18/2010]
		msg.create.ucHeadPic = (unsigned char)m_nSelPortraitId;		//	added by zhuomeng.hu		[8/25/2010]
		uint8 month, day;
		GetBirthday(m_pID_COMBOBOX_Month, m_pID_COMBOBOX_Day, month, day);
		msg.create.byMonth = month;
		msg.create.byDay = day;

		//added by ZhuoMeng.Hu		[9/2/2010]
		m_pID_BUTTON_OK->SetEnable( false );
		GettheNetworkInput().SendMsg( &msg,msg.GetLength() );

		if( m_bCameraZoomIn && m_pCameraModel->GetMexCfg()->GetSequence("select") )
		{
			m_pCameraModel->PlayAnimByName("back", 0, FALSE);
			m_bCameraZoomIn = false;
		}

		g_bCreateOk = TRUE;

	}
	else
	{
		theUiManager.SetFocus(NULL);
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eCreate_NameError ), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, false, FocusToNameEdit );
	}



}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_BackOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return false;
	}

	//m_bToSelectWeapon = true;
	m_bToSelect = true;
	g_bCreateOk = FALSE;
	if( m_bCameraZoomIn && m_pCameraModel->GetMexCfg()->GetSequence("select") )
	{
		m_pCameraModel->PlayAnimByName("back", 0, FALSE);
		m_bCameraZoomIn = false;
	}
	return true;
	unguard;
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_ManOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return ;
	}

	*pbChecked = true;
	if( m_nSex == Sex_Male )
		return;

	m_pID_CHECKBOX_Woman->SetCheck( false );
	SetSex( Sex_Male );

	// 更新头像控件		added by zhuomeng.hu		[8/25/2010]
	m_nSelPortraitId = 0;
	m_nShowRow = 0;
	UpdatePortrait( m_nSex, m_nSelPortraitId, m_nShowRow );

	ResetStature();
	//add by yanli  2010-9-6 策划要求开放创建男性Fan职业
	/*m_pID_CHECKBOX_Fan->SetEnable(false);*/
	//m_pID_CHECKBOX_Fan->SetEnable(true);
	/*		deleted by zhuomeng.hu		[9/6/2010]		
	m_pID_CHECKBOX_Fan->SetEnable(false);
	if (m_pID_CHECKBOX_Fan->IsChecked())
	{
		bool check = true;
		m_pID_CHECKBOX_Spear->SetCheck(true);
		ID_CHECKBOX_JiOnCheckBoxCheck(m_pID_CHECKBOX_Spear, &check);
	}*/
	int nHairCount = m_pMaleHairId->nCount;
	int nFaceCount = m_pMaleFaceId->nCount;
	if( m_nHair > nHairCount )
		m_nHair = 0;
	if( m_nFace > nFaceCount )
		m_nFace = 0;
	Refresh( false );
	RefreshEffect();
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_WomanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return ;
	}

	*pbChecked = true;
	if( m_nSex == Sex_Female )
		return;

	m_pID_CHECKBOX_Man->SetCheck( false );
	SetSex( Sex_Female );

	// 更新头像控件		added by zhuomeng.hu		[8/25/2010]
	m_nSelPortraitId = 0;
	m_nShowRow = 0;
	UpdatePortrait( m_nSex, m_nSelPortraitId, m_nShowRow );

	ResetStature();
	//m_pID_CHECKBOX_Fan->SetEnable(true);
	int nHairCount = m_pFemaleHairId->nCount;
	int nFaceCount = m_pFemaleFaceId->nCount;
	if( m_nHair > nHairCount )
		m_nHair = 0;
	if( m_nFace > nFaceCount )
		m_nFace = 0;
	Refresh( false );
	RefreshEffect();
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_JiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return ;
	}

	m_pID_CHECKBOX_Spear->SetCheck( true );
	m_pID_CHECKBOX_Sword->SetCheck( false );
	m_pID_CHECKBOX_Staff->SetCheck( false );
	m_pID_CHECKBOX_Bow->SetCheck( false );
	m_pID_CHECKBOX_Fan->SetCheck( false );

	int nLastCountry = m_nCountry;
	m_nCountry = EArmType_Warrior;
	ResetStature();
	CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( m_nCountry );
	if (pProInfo)
	{
		m_pID_TEXT_ProInfo->SetText( pProInfo->m_strNote.c_str(), Color_Config.getColor( CC_CreateUI_StrNote ) );
		//m_pID_TEXT_Property->SetText(pProInfo->m_strCreateShow.c_str(), Color_Config.getColor( CC_CreateUI_Property ) );
		m_pID_TEXT_ProName->SetText( pProInfo->m_strProShow.c_str(), Color_Config.getColor( CC_CreateUI_ProName ) );
	}

	Refresh(false, true);
	RefreshEffect();
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_DaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return ;
	}

	m_pID_CHECKBOX_Spear->SetCheck( false );
	m_pID_CHECKBOX_Sword->SetCheck( true );
	m_pID_CHECKBOX_Staff->SetCheck( false );
	m_pID_CHECKBOX_Bow->SetCheck( false );
	m_pID_CHECKBOX_Fan->SetCheck( false );

	int nLastCountry = m_nCountry;
	m_nCountry = EArmType_Assassin;
	ResetStature();
	CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( m_nCountry );
	if (pProInfo)
	{
		m_pID_TEXT_ProInfo->SetText( pProInfo->m_strNote.c_str(), Color_Config.getColor( CC_CreateUI_StrNote ) );
		//m_pID_TEXT_Property->SetText(pProInfo->m_strCreateShow.c_str(), Color_Config.getColor( CC_CreateUI_Property ) );
		m_pID_TEXT_ProName->SetText( pProInfo->m_strProShow.c_str(), Color_Config.getColor( CC_CreateUI_ProName ) );
	}
	Refresh(false, true);
	RefreshEffect();
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_WuOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return ;
	}

	m_pID_CHECKBOX_Spear->SetCheck( false );
	m_pID_CHECKBOX_Sword->SetCheck( false );
	m_pID_CHECKBOX_Staff->SetCheck( true );
	m_pID_CHECKBOX_Bow->SetCheck( false );
	m_pID_CHECKBOX_Fan->SetCheck( false );

	int nLastCountry = m_nCountry;
	m_nCountry = EArmType_Mage;
	ResetStature();
	CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( m_nCountry );
	if (pProInfo)
	{
		m_pID_TEXT_ProInfo->SetText( pProInfo->m_strNote.c_str(), Color_Config.getColor( CC_CreateUI_StrNote ) );
		//m_pID_TEXT_Property->SetText(pProInfo->m_strCreateShow.c_str(), Color_Config.getColor( CC_CreateUI_Property ) );
		m_pID_TEXT_ProName->SetText( pProInfo->m_strProShow.c_str(), Color_Config.getColor( CC_CreateUI_ProName ) );
	}
	Refresh(false, true);
	RefreshEffect();
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_JianOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return ;
	}

	m_pID_CHECKBOX_Spear->SetCheck( false );
	m_pID_CHECKBOX_Sword->SetCheck( false );
	m_pID_CHECKBOX_Staff->SetCheck( false );
	m_pID_CHECKBOX_Bow->SetCheck( true );
	m_pID_CHECKBOX_Fan->SetCheck( false );
	int nLastCountry = m_nCountry;
	m_nCountry = EArmType_Hunter;

	ResetStature();
	CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( m_nCountry );
	if (pProInfo)
	{
		m_pID_TEXT_ProInfo->SetText( pProInfo->m_strNote.c_str(), Color_Config.getColor( CC_CreateUI_StrNote ) );
		//m_pID_TEXT_Property->SetText(pProInfo->m_strCreateShow.c_str(), Color_Config.getColor( CC_CreateUI_Property ) );
		m_pID_TEXT_ProName->SetText( pProInfo->m_strProShow.c_str(), Color_Config.getColor( CC_CreateUI_ProName ) );
	}
	Refresh(false, true);
	RefreshEffect();
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_QiangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return ;
	}

	m_pID_CHECKBOX_Spear->SetCheck( false );
	m_pID_CHECKBOX_Sword->SetCheck( false );
	m_pID_CHECKBOX_Staff->SetCheck( false );
	m_pID_CHECKBOX_Bow->SetCheck( false );
	m_pID_CHECKBOX_Fan->SetCheck( true );

	int nLastCountry = m_nCountry;
	m_nCountry = EArmType_Taoist;
	ResetStature();
	CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( m_nCountry );
	if (pProInfo)
	{
		m_pID_TEXT_ProInfo->SetText( pProInfo->m_strNote.c_str(), Color_Config.getColor( CC_CreateUI_StrNote ) );
		//m_pID_TEXT_Property->SetText(pProInfo->m_strCreateShow.c_str(), Color_Config.getColor( CC_CreateUI_Property ) );
		m_pID_TEXT_ProName->SetText( pProInfo->m_strProShow.c_str(), Color_Config.getColor( CC_CreateUI_ProName ) );
	}
	Refresh(false, true);
	RefreshEffect();
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_JobOtherOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
}
bool CUI_ID_FRAME_CREATE::ID_BUTTON_ResetOnButtonClick( ControlObject* pSender )
{

	m_nHair = m_nDefaultHair;
	m_nFace = m_nDefaultFace;
	m_fPlayerScale = 0.9;
	m_fRot = gCfg.m_fSelectRoleRotateZ;
	m_pID_SCROLLBAREX_Stature->SetValue(500);

Refresh(false, false);
	return true;
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_RandomOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return false;
	}

	int nHairCount = m_pMaleHairId->nCount;
	int nFaceCount = m_pMaleFaceId->nCount;
	if( m_nSex == 1 )
	{
		nHairCount = m_pFemaleHairId->nCount;
		nFaceCount = m_pFemaleFaceId->nCount;
	}
	if( nHairCount > 0 )
		m_nHair = rand()%nHairCount;
	else
		m_nHair = 0;
	if( nFaceCount > 0 )
		m_nFace = rand()%nFaceCount;
	else
		m_nFace = 0;

	Refresh( false, false );
	return true;
}
void CUI_ID_FRAME_CREATE::ID_SCROLLBAREX_StatureOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if(!m_pID_FRAME_CREATE)
	{
		assert(false&&"ui error");
		return ;
	}

	SetPlayerScaleByScrollBarValue(n);
}

//  国家  added by zhuomeng.hu		[8/18/2010]
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_Country1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
	m_pID_CHECKBOX_Country1->SetCheck( true );
	m_pID_CHECKBOX_Country2->SetCheck( false );
	m_pID_CHECKBOX_Country3->SetCheck( false );
	m_pID_CHECKBOX_Country4->SetCheck( false );
	m_pID_CHECKBOX_CountryAuto->SetCheck( false );

	m_pID_PICTURE_CountryIcon1->SetVisable( true );
	m_pID_PICTURE_CountryIcon2->SetVisable( false );
	m_pID_PICTURE_CountryIcon3->SetVisable( false );
	m_pID_PICTURE_CountryIcon4->SetVisable( false );
	m_pID_PICTURE_CountryIconRandom->SetVisable( false );
	m_nRealCountry = CountryDefine::Country_LouLan;
    m_pID_TEXT_CountryName->SetText( CountryFunction::GetDefaultCountryNameById( m_nRealCountry ) );
	m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_LouLan ) );
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_Country2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
	m_pID_CHECKBOX_Country1->SetCheck( false );
	m_pID_CHECKBOX_Country2->SetCheck( true );
	m_pID_CHECKBOX_Country3->SetCheck( false );
	m_pID_CHECKBOX_Country4->SetCheck( false );
	m_pID_CHECKBOX_CountryAuto->SetCheck( false );

	m_pID_PICTURE_CountryIcon1->SetVisable( false );
	m_pID_PICTURE_CountryIcon2->SetVisable( true );
	m_pID_PICTURE_CountryIcon3->SetVisable( false );
	m_pID_PICTURE_CountryIcon4->SetVisable( false );
	m_pID_PICTURE_CountryIconRandom->SetVisable( false );
	m_nRealCountry = CountryDefine::Country_KunLun;
    m_pID_TEXT_CountryName->SetText( CountryFunction::GetDefaultCountryNameById( m_nRealCountry ) );
	m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_KunLun ) );
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_Country3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
	m_pID_CHECKBOX_Country1->SetCheck( false );
	m_pID_CHECKBOX_Country2->SetCheck( false );
	m_pID_CHECKBOX_Country3->SetCheck( true );
	m_pID_CHECKBOX_Country4->SetCheck( false );
	m_pID_CHECKBOX_CountryAuto->SetCheck( false );

	m_pID_PICTURE_CountryIcon1->SetVisable( false );
	m_pID_PICTURE_CountryIcon2->SetVisable( false );
	m_pID_PICTURE_CountryIcon3->SetVisable( true );
	m_pID_PICTURE_CountryIcon4->SetVisable( false );
	m_pID_PICTURE_CountryIconRandom->SetVisable( false );
	m_nRealCountry = CountryDefine::Country_DunHuang;
    m_pID_TEXT_CountryName->SetText( CountryFunction::GetDefaultCountryNameById( m_nRealCountry ) );
	m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_DunHuang ) );
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_Country4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
	//m_pID_CHECKBOX_Country1->SetCheck( false );
	//m_pID_CHECKBOX_Country2->SetCheck( false );
	//m_pID_CHECKBOX_Country3->SetCheck( false );
	//m_pID_CHECKBOX_Country4->SetCheck( true );
	//m_pID_CHECKBOX_CountryAuto->SetCheck( false );

	//m_pID_PICTURE_CountryIcon1->SetVisable( false );
	//m_pID_PICTURE_CountryIcon2->SetVisable( false );
	//m_pID_PICTURE_CountryIcon3->SetVisable( false );
	//m_pID_PICTURE_CountryIcon4->SetVisable( true );
	//m_pID_PICTURE_CountryIconRandom->SetVisable( false );
	//m_nRealCountry = CountryDefine::Country_LaiYin;
    //m_pID_TEXT_CountryName->SetText( theXmlString.GetString( eText_Country_LaiYin ) );
	//m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_LaiYin ) );
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_CountryAutoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
    m_pID_CHECKBOX_Country1->SetCheck( false );
    m_pID_CHECKBOX_Country2->SetCheck( false );
    m_pID_CHECKBOX_Country3->SetCheck( false );
    m_pID_CHECKBOX_Country4->SetCheck( false );
    m_pID_CHECKBOX_CountryAuto->SetCheck( true );

    m_pID_PICTURE_CountryIcon1->SetVisable( false );
    m_pID_PICTURE_CountryIcon2->SetVisable( false );
    m_pID_PICTURE_CountryIcon3->SetVisable( false );
    m_pID_PICTURE_CountryIcon4->SetVisable( false );
    m_pID_PICTURE_CountryIconRandom->SetVisable( true );
    m_nRealCountry = CountryDefine::Country_Init;
    m_pID_TEXT_CountryName->SetText( "" );
    m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_Random ) );

	//if( m_pID_CHECKBOX_CountryAuto->IsChecked() )
	//{
	//	m_pID_CHECKBOX_Country1->SetCheck( false );
	//	m_pID_CHECKBOX_Country2->SetCheck( false );
	//	m_pID_CHECKBOX_Country3->SetCheck( false );
	//	m_pID_CHECKBOX_Country4->SetCheck( false );

	//	m_pID_PICTURE_CountryIcon1->SetVisable( false );
	//	m_pID_PICTURE_CountryIcon2->SetVisable( false );
	//	m_pID_PICTURE_CountryIcon3->SetVisable( false );
	//	m_pID_PICTURE_CountryIcon4->SetVisable( false );
	//	m_pID_PICTURE_CountryIconRandom->SetVisable( true );
	//	m_nRealCountry = CountryDefine::Country_Init;
 //       m_pID_TEXT_CountryName->SetText( "" );
	//	m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_Random ) );
	//}
	//else
	//{
	//	m_pID_PICTURE_CountryIconRandom->SetVisable( false );
	//	m_nRealCountry = rand() % ( CountryDefine::Country_Max - 1 ) + 1;
	//	switch( m_nRealCountry )
	//	{
	//	case CountryDefine::Country_LouLan:
	//		m_pID_CHECKBOX_Country1->SetCheck( true );
	//		m_pID_PICTURE_CountryIcon1->SetVisable( true );
 //           m_pID_TEXT_CountryName->SetText( theXmlString.GetString( eText_Country_LouLan ) );
	//		m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_LouLan ) );
	//		break;
	//	case CountryDefine::Country_KunLun:
	//		m_pID_CHECKBOX_Country2->SetCheck( true );
	//		m_pID_PICTURE_CountryIcon2->SetVisable( true );
 //           m_pID_TEXT_CountryName->SetText( theXmlString.GetString( eText_Country_KunLun ) );
	//		m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_KunLun ) );
	//		break;
	//	case CountryDefine::Country_DunHuang:
	//		m_pID_CHECKBOX_Country3->SetCheck( true );
	//		m_pID_PICTURE_CountryIcon3->SetVisable( true );
 //           m_pID_TEXT_CountryName->SetText( theXmlString.GetString( eText_Country_DunHuang ) );
	//		m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_DunHuang ) );
	//		break;
	//	case CountryDefine::Country_LaiYin:
	//		m_pID_CHECKBOX_Country4->SetCheck( true );
	//		m_pID_PICTURE_CountryIcon4->SetVisable( true );
 //           m_pID_TEXT_CountryName->SetText( theXmlString.GetString( eText_Country_LaiYin ) );
	//		m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_LaiYin ) );
	//		break;
	//	default:
	//		break;
	//	}
	//}
}

// 头像
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_Portrait1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
	int portraitSize = m_nSex == Sex_Male ? m_malePortraitVec.size() : m_femalePortraitVec.size();
	if( portraitSize > m_nShowRow * 2 )
	{
		m_pID_CHECKBOX_Portrait1->SetCheck( true );
		m_pID_CHECKBOX_Portrait2->SetCheck( false );
		m_pID_CHECKBOX_Portrait3->SetCheck( false );
		m_pID_CHECKBOX_Portrait4->SetCheck( false );
		m_nSelPortraitId = m_nShowRow * 2;
	}
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_Portrait2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
	int portraitSize = m_nSex == Sex_Male ? m_malePortraitVec.size() : m_femalePortraitVec.size();
	if( portraitSize > m_nShowRow * 2 + 1 )
	{
		m_pID_CHECKBOX_Portrait1->SetCheck( false );
		m_pID_CHECKBOX_Portrait2->SetCheck( true );
		m_pID_CHECKBOX_Portrait3->SetCheck( false );
		m_pID_CHECKBOX_Portrait4->SetCheck( false );
		m_nSelPortraitId = m_nShowRow * 2 + 1;
	}
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_Portrait3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
	int portraitSize = m_nSex == Sex_Male ? m_malePortraitVec.size() : m_femalePortraitVec.size();
	if( portraitSize > m_nShowRow * 2 + 2 )
	{
		m_pID_CHECKBOX_Portrait1->SetCheck( false );
		m_pID_CHECKBOX_Portrait2->SetCheck( false );
		m_pID_CHECKBOX_Portrait3->SetCheck( true );
		m_pID_CHECKBOX_Portrait4->SetCheck( false );
		m_nSelPortraitId = m_nShowRow * 2 + 2;
	}
}
// CheckBox
void CUI_ID_FRAME_CREATE::ID_CHECKBOX_Portrait4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
	int portraitSize = m_nSex == Sex_Male ? m_malePortraitVec.size() : m_femalePortraitVec.size();
	if( portraitSize > m_nShowRow * 2 + 3 )
	{
		m_pID_CHECKBOX_Portrait1->SetCheck( false );
		m_pID_CHECKBOX_Portrait2->SetCheck( false );
		m_pID_CHECKBOX_Portrait3->SetCheck( false );
		m_pID_CHECKBOX_Portrait4->SetCheck( true );
		m_nSelPortraitId = m_nShowRow * 2 + 3;
	}
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_HeadUpOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return false;
	}
	m_nShowRow -= 1;
	UpdatePortrait( m_nSex, m_nSelPortraitId, m_nShowRow );
	return true;
}
// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_HeadDownOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return false;
	}
	m_nShowRow += 1;
	UpdatePortrait( m_nSex, m_nSelPortraitId, m_nShowRow );
	return true;
}

// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_NearOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CREATE )
		return false;

	m_pID_BUTTON_Farness->SetVisable(true);
	m_pID_BUTTON_Near->SetVisable(false);

	if(m_pCameraModel)
		m_pCameraModel->PlayAnimByName("near_far",0,FALSE);

	return true;
}

// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_FarnessOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CREATE )
		return false;

	m_pID_BUTTON_Farness->SetVisable(false);
	m_pID_BUTTON_Near->SetVisable(true);

	if(m_pCameraModel)
		m_pCameraModel->PlayAnimByName("far_near",0,FALSE);

	return true;
}

// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_ArmourLOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CREATE )
		return false;

	--m_nSelEquip;
	if(m_nSelEquip < 0)
		m_nSelEquip = 0;

	Refresh( false, false );

	return true;
}

// Button
bool CUI_ID_FRAME_CREATE::ID_BUTTON_ArmourROnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CREATE )
		return false;

	int nCount = 0;
	if(m_nSex == Sex_Male)
		nCount = gCfg.m_MaleRoleSetting.size();
	else if(m_nSex == Sex_Female)
		nCount = gCfg.m_FemaleRoleSetting.size();

	if(m_nSelEquip >= nCount)
		m_nSelEquip = nCount - 1;

	++m_nSelEquip;

	if(m_nSelEquip >= nCount)
		m_nSelEquip = nCount - 1;

	Refresh( false, false );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_CREATE::_LoadUI()
{
	guardfunc;

	
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Create.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Create.MEUI]失败")
			return false;
	}
	m_bUpdateOnce = FALSE;
	
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_CREATE::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_CREATE, s_CUI_ID_FRAME_CREATEOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CREATE, s_CUI_ID_FRAME_CREATEOnFrameRender, true );
	theUiManager.OnEditEnter( ID_FRAME_CREATE, ID_EDIT_Name, s_CUI_ID_FRAME_CREATEID_EDIT_NameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_CheckName, s_CUI_ID_FRAME_CREATEID_BUTTON_CheckNameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_HairL, s_CUI_ID_FRAME_CREATEID_BUTTON_HairLOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_HairR, s_CUI_ID_FRAME_CREATEID_BUTTON_HairROnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_HeadL, s_CUI_ID_FRAME_CREATEID_BUTTON_HeadLOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_HeadR, s_CUI_ID_FRAME_CREATEID_BUTTON_HeadROnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_TurnR, s_CUI_ID_FRAME_CREATEID_BUTTON_TurnROnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_TurnL, s_CUI_ID_FRAME_CREATEID_BUTTON_TurnLOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_OK, s_CUI_ID_FRAME_CREATEID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_Back, s_CUI_ID_FRAME_CREATEID_BUTTON_BackOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Man, s_CUI_ID_FRAME_CREATEID_CHECKBOX_ManOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Woman, s_CUI_ID_FRAME_CREATEID_CHECKBOX_WomanOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Spear, s_CUI_ID_FRAME_CREATEID_CHECKBOX_JiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Sword, s_CUI_ID_FRAME_CREATEID_CHECKBOX_DaoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Staff, s_CUI_ID_FRAME_CREATEID_CHECKBOX_QiangOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Bow, s_CUI_ID_FRAME_CREATEID_CHECKBOX_JianOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Fan, s_CUI_ID_FRAME_CREATEID_CHECKBOX_WuOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_JobOther, s_CUI_ID_FRAME_CREATEID_CHECKBOX_JobOtherOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_Random, s_CUI_ID_FRAME_CREATEID_BUTTON_RandomOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_Reset, s_CUI_ID_FRAME_CREATEID_BUTTON_ResetOnButtonClick );

	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_CREATE, ID_SCROLLBAREX_Stature, s_CUI_ID_FRAME_CREATEID_SCROLLBAREX_StatureOnScrollBarExUpdatePos );
	//  国家  added by zhuomeng.hu		[8/18/2010]
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Country1, s_CUI_ID_FRAME_CREATEID_CHECKBOX_Country1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Country2, s_CUI_ID_FRAME_CREATEID_CHECKBOX_Country2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Country3, s_CUI_ID_FRAME_CREATEID_CHECKBOX_Country3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Country4, s_CUI_ID_FRAME_CREATEID_CHECKBOX_Country4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_CountryAuto, s_CUI_ID_FRAME_CREATEID_CHECKBOX_CountryAutoOnCheckBoxCheck );

	// 头像		added by zhuomeng.hu		[8/20/2010]
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Portrait1, s_CUI_ID_FRAME_CREATEID_CHECKBOX_Portrait1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Portrait2, s_CUI_ID_FRAME_CREATEID_CHECKBOX_Portrait2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Portrait3, s_CUI_ID_FRAME_CREATEID_CHECKBOX_Portrait3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CREATE, ID_CHECKBOX_Portrait4, s_CUI_ID_FRAME_CREATEID_CHECKBOX_Portrait4OnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_HeadUp, s_CUI_ID_FRAME_CREATEID_BUTTON_HeadUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_HeadDown, s_CUI_ID_FRAME_CREATEID_BUTTON_HeadDownOnButtonClick );

	theUiManager.OnComboBoxChange( ID_FRAME_CREATE, ID_COMBOBOX_Month, s_CUI_ID_FRAME_CREATEID_COMBOBOX_MonthOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_CREATE, ID_COMBOBOX_Day, s_CUI_ID_FRAME_CREATEID_COMBOBOX_DayOnComboBoxChange );

	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_Near, s_CUI_ID_FRAME_CREATEID_BUTTON_NearOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_Farness, s_CUI_ID_FRAME_CREATEID_BUTTON_FarnessOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_ArmourR, s_CUI_ID_FRAME_CREATEID_BUTTON_ArmourROnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CREATE, ID_BUTTON_ArmourL, s_CUI_ID_FRAME_CREATEID_BUTTON_ArmourLOnButtonClick );
	

	

	m_pID_FRAME_CREATE = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CREATE );
//	m_pID_PICTURE_Property = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_Property );
	m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_Title );
	m_pID_PICTURE_JobWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_JobWall );
	m_pID_EDIT_Name = (ControlEdit*)theUiManager.FindControl( ID_FRAME_CREATE, ID_EDIT_Name );
	m_pID_BUTTON_CheckName = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_CheckName );
	m_pID_PICTURE_HairWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_HairWall );
	m_pID_PICTURE_FaceWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_FaceWall );
	m_pID_BUTTON_HairL = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_HairL );
	m_pID_BUTTON_HairR = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_HairR );
	m_pID_BUTTON_HeadL = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_HeadL );
	m_pID_BUTTON_HeadR = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_HeadR );
	m_pID_PICTURE_TitlePic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_TitlePic );
	m_pID_PICTURE_FenGe = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_FenGe );
	m_pID_BUTTON_TurnR = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_TurnR );
	m_pID_BUTTON_TurnL = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_TurnL );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_OK );
	m_pID_BUTTON_Back = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_Back );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_Name );
	m_pID_TEXT_Hair = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_Hair );
	m_pID_TEXT_Face = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_Face );
	m_pID_TEXT_ProName = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_ProName );
	m_pID_TEXT_ProInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_ProInfo );
// 	m_pID_PICTURE_Spear = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_Spear );
// 	m_pID_PICTURE_Sword = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_Sword );
// 	m_pID_PICTURE_Staff = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_Staff );
// 	m_pID_PICTURE_Fan = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_Fan );
// 	m_pID_PICTURE_Bow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_Bow );
	m_pID_CHECKBOX_JobOther = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_JobOther );
// 	m_pID_TEXT_Sex = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_Sex );
// 	m_pID_TEXT_Man = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_Man );
// 	m_pID_TEXT_Woman = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_Woman );
	m_pID_CHECKBOX_Man = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Man );
	m_pID_CHECKBOX_Woman = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Woman );
	m_pID_CHECKBOX_Spear = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Spear );
	m_pID_CHECKBOX_Sword = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Sword );
	m_pID_CHECKBOX_Staff = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Staff );
	m_pID_CHECKBOX_Bow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Bow );
	m_pID_CHECKBOX_Fan = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Fan );
	//m_pID_TEXT_HairZ = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_HairZ );
	//m_pID_TEXT_FaceZ = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_FaceZ );
	m_pID_BUTTON_Random = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_Random );

	m_pID_BUTTON_Reset = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_Reset );

	m_pID_SCROLLBAREX_Stature = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_CREATE, ID_SCROLLBAREX_Stature );
	//m_pID_TEXT_StatureZ = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_StatureZ );
	m_pID_TEXT_Low = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_Low );
	m_pID_TEXT_High = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_High );

	//  国家  added by zhuomeng.hu		[8/18/2010]
	m_pID_CHECKBOX_Country1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Country1 );
	m_pID_CHECKBOX_Country2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Country2 );
	m_pID_CHECKBOX_Country3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Country3 );
	m_pID_CHECKBOX_Country4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Country4 );
	m_pID_TEXT_CountryDesc = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_CountryDesc );
	m_pID_PICTURE_CountryIcon1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_CountryIcon1 );
	m_pID_PICTURE_CountryIcon2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_CountryIcon2 );
	m_pID_PICTURE_CountryIcon3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_CountryIcon3 );
	m_pID_PICTURE_CountryIcon4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_CountryIcon4 );
	m_pID_PICTURE_CountryIconRandom = (ControlPicture*)theUiManager.FindControl( ID_FRAME_CREATE, ID_PICTURE_CountryIconRandom );
	m_pID_TEXT_CountryName = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_CountryName );
	m_pID_CHECKBOX_CountryAuto = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_CountryAuto );
	m_pID_TEXT_CountryAutoText = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_CountryAutoText );
	m_pID_TEXT_CountryAutoDesc = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_CountryAutoDesc );
	
	// 头像		added by zhuomeng.hu		[8/20/2010]
	m_pID_CHECKBOX_Portrait1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Portrait1 );
	m_pID_CHECKBOX_Portrait2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Portrait2 );
	m_pID_CHECKBOX_Portrait3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Portrait3 );
	m_pID_CHECKBOX_Portrait4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_CHECKBOX_Portrait4 );
	m_pID_BUTTON_HeadUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_HeadUp );
	m_pID_BUTTON_HeadDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_HeadDown );

	m_pID_TEXT_ShengRi = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_ShengRi );
	m_pID_TEXT_Month = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_Month );
	m_pID_TEXT_Day = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_Day );
	m_pID_COMBOBOX_Month = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_COMBOBOX_Month );
	m_pID_COMBOBOX_Day = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_CREATE, ID_COMBOBOX_Day );

	m_pID_BUTTON_Near = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_Near );
	m_pID_BUTTON_Farness = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_Farness );

	m_pID_BUTTON_ArmourR = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_ArmourR );
	m_pID_BUTTON_ArmourL = (ControlButton*)theUiManager.FindControl( ID_FRAME_CREATE, ID_BUTTON_ArmourL );
	m_pID_TEXT_Armour = (ControlText*)theUiManager.FindControl( ID_FRAME_CREATE, ID_TEXT_Armour );

	m_pID_FRAME_CREATE->SetMsgProcFun( frame_msg );
	assert( m_pID_FRAME_CREATE );
	//assert( m_pID_PICTURE_Property );
	assert( m_pID_PICTURE_Title );
	assert( m_pID_PICTURE_JobWall );
	assert( m_pID_EDIT_Name );
	assert( m_pID_BUTTON_CheckName );
	assert( m_pID_PICTURE_HairWall );
	assert( m_pID_PICTURE_FaceWall );
	assert( m_pID_BUTTON_HairL );
	assert( m_pID_BUTTON_HairR );
	assert( m_pID_BUTTON_HeadL );
	assert( m_pID_BUTTON_HeadR );
	assert( m_pID_PICTURE_TitlePic );
	assert( m_pID_PICTURE_FenGe );
	assert( m_pID_BUTTON_TurnR );
	assert( m_pID_BUTTON_TurnL );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Back );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_Hair );
	assert( m_pID_TEXT_Face );
	assert( m_pID_TEXT_ProName );
	assert( m_pID_TEXT_ProInfo );
// 	assert( m_pID_PICTURE_Spear );
// 	assert( m_pID_PICTURE_Sword );
// 	assert( m_pID_PICTURE_Staff );
// 	assert( m_pID_PICTURE_Fan );
// 	assert( m_pID_PICTURE_Bow );
// 	assert( m_pID_TEXT_Sex );
// 	assert( m_pID_TEXT_Man );
// 	assert( m_pID_TEXT_Woman );
	assert( m_pID_CHECKBOX_Man );
	assert( m_pID_CHECKBOX_Woman );
	assert( m_pID_CHECKBOX_Spear );
	assert( m_pID_CHECKBOX_Sword );
	assert( m_pID_CHECKBOX_Staff );
	assert( m_pID_CHECKBOX_Bow );
	assert( m_pID_CHECKBOX_Fan );
	assert( m_pID_CHECKBOX_JobOther );
// 	assert( m_pID_TEXT_HairZ );
// 	assert( m_pID_TEXT_FaceZ );
	assert( m_pID_BUTTON_Random );
	assert( m_pID_SCROLLBAREX_Stature );
	//assert( m_pID_TEXT_StatureZ );
	//assert( m_pID_TEXT_Low );
	//assert( m_pID_TEXT_High );

	//  国家  added by zhuomeng.hu		[8/18/2010]
	assert( m_pID_CHECKBOX_Country1 );
	assert( m_pID_CHECKBOX_Country2 );
	assert( m_pID_CHECKBOX_Country3 );
	assert( m_pID_CHECKBOX_Country4 );
	assert( m_pID_TEXT_CountryDesc );
	assert( m_pID_PICTURE_CountryIcon1 );
	assert( m_pID_PICTURE_CountryIcon2 );
	assert( m_pID_PICTURE_CountryIcon3 );
	assert( m_pID_PICTURE_CountryIcon4 );
	assert( m_pID_PICTURE_CountryIconRandom );
	assert( m_pID_TEXT_CountryName );
	assert( m_pID_CHECKBOX_CountryAuto );
	assert( m_pID_TEXT_CountryAutoText );
	assert( m_pID_TEXT_CountryAutoDesc );

	// 头像		added by zhuomeng.hu		[8/20/2010]
	assert( m_pID_CHECKBOX_Portrait1 );
	assert( m_pID_CHECKBOX_Portrait2 );
	assert( m_pID_CHECKBOX_Portrait3 );
	assert( m_pID_CHECKBOX_Portrait4 );
	assert( m_pID_BUTTON_HeadUp );
	assert( m_pID_BUTTON_HeadDown );

	assert( m_pID_TEXT_ShengRi );
	assert( m_pID_TEXT_Month );
	assert( m_pID_TEXT_Day );
	assert( m_pID_COMBOBOX_Month );
	assert( m_pID_COMBOBOX_Day );

	assert( m_pID_BUTTON_Near );
	assert( m_pID_BUTTON_Farness );
	assert( m_pID_BUTTON_ArmourR );
	assert( m_pID_BUTTON_ArmourL );
	assert( m_pID_TEXT_Armour );

	m_pID_BUTTON_Near->SetVisable(false);
	m_pID_BUTTON_Farness->SetVisable(true);

	m_pID_BUTTON_TurnL->SetLButtonDownFun(TurnOnLButtonDown);
	m_pID_BUTTON_TurnL->SetLButtonUpFun(TurnOnLButtonUp);
	m_pID_BUTTON_TurnR->SetLButtonDownFun(TurnOnLButtonDown);
	m_pID_BUTTON_TurnR->SetLButtonUpFun(TurnOnLButtonUp);

	m_pID_SCROLLBAREX_Stature->SetMaxValue(1000);
	m_pID_SCROLLBAREX_Stature->SetValue(500);
    RandomPression();

	m_pPlayer = MeNew CPlayer;
	int nIndex = GetEffectMgr()->RegisterCharEffectContainer();
	if( nIndex >= 0 )
	{
		m_pPlayer->SetCharEffectContainer( GetEffectMgr()->GetCharEffectContainer( nIndex ) );
	}
	m_bNeedPlayEffect = false;
	strcpy(m_szEffectName, "");

	m_pSetting          = GetAvatarSystemSetting();
	m_pSex			    = m_pSetting->GetSettingSex();
	m_pMaleDressId	    = m_pSetting->GetSettingMaleDressId();
	m_pFemaleDressId	= m_pSetting->GetSettingFemaleDressId();
	m_pMaleFaceId		= m_pSetting->GetSettingMaleFaceId();
	m_pFemaleFaceId	    = m_pSetting->GetSettingFemaleFaceId();
	m_pMaleHairId		= m_pSetting->GetSettingMaleHairId();
	m_pFemaleHairId	    = m_pSetting->GetSettingFemaleHairId();

	SetSex(1);
	//m_nFace = 0;
	//m_nHair = 0;
	// 随机给脸型和发型
	int nHairCount = m_pMaleHairId->nCount;
	int nFaceCount = m_pMaleFaceId->nCount;
	if( m_nSex == 1 )
	{
		nHairCount = m_pFemaleHairId->nCount;
		nFaceCount = m_pFemaleFaceId->nCount;
	}
	if( nHairCount > 0 )
		m_nHair = rand()%nHairCount;
	else
		m_nHair = 0;
	if( nFaceCount > 0 )
		m_nFace = rand()%nFaceCount;
	else
		m_nFace = 0;


	m_nDefaultHair = m_nHair;
	m_nDefaultFace = m_nFace;

	m_nHairColor = 1;
	m_nCloth = 0;

	m_pID_FRAME_CREATE->SetWidth( SCREEN_WIDTH );
	m_pID_FRAME_CREATE->SetHeight( SCREEN_HEIGHT );

	m_pID_EDIT_Name->SetMaxLength( MAX_CREATE_LENGTH );

	m_pCamera = MeNew MeCamera;
	D3DXVECTOR3 vFromPt	 = D3DXVECTOR3( 0.0f, 300.0f, 200.0f );
	D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec	  = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_pCamera->SetViewParams( vFromPt, vLookatPt, vUpVec );

	float fAspect = (float)SCREEN_WIDTH/SCREEN_HEIGHT;
	m_pCamera->SetProjParams( D3DX_PI/3.0f, fAspect,  1.0f, 18000.0f );

	m_bIsTileLoaded = false;

	m_pPlayerAnim = MeNew CPlayerAnim;
	m_pPlayerAnim->SetChangeAllEquipComplete( FALSE );

	if(!gCfg.m_MaleRoleSetting.empty())
	{
	    m_iMaleNum = gCfg.m_MaleRoleSetting[0].GetSpaceSize();
		if( m_iMaleNum > EArmType_MaxSize )
			m_iMaleNum = EArmType_MaxSize;
	}
	else
		m_iMaleNum = EArmType_MaxSize;

	if(!gCfg.m_FemaleRoleSetting.empty())
	{
		m_iFemaleNum = gCfg.m_FemaleRoleSetting[0].GetSpaceSize();
		if( m_iFemaleNum > EArmType_MaxSize )
			m_iFemaleNum = EArmType_MaxSize;
	}
	else
		m_iFemaleNum = EArmType_MaxSize;

	bool bChecked = true;
	if( m_nSex == 0 )
	{
		m_pID_CHECKBOX_Man->SetCheck( true );
		ID_CHECKBOX_ManOnCheckBoxCheck( 0, &bChecked );
	}
	else
	{
		m_pID_CHECKBOX_Woman->SetCheck( true );
		ID_CHECKBOX_WomanOnCheckBoxCheck( 0, &bChecked );
	}

	// 这里没必要
	/*
	switch( m_nCountry )
	{
	case EArmType_Warrior:
		ID_CHECKBOX_JiOnCheckBoxCheck(NULL, NULL);
		break;
	case EArmType_Hunter:
		ID_CHECKBOX_JianOnCheckBoxCheck(NULL, NULL);
		break;
	case EArmType_Mage:
		ID_CHECKBOX_WuOnCheckBoxCheck(NULL, NULL);
		break;
	case EArmType_Assassin:
		ID_CHECKBOX_DaoOnCheckBoxCheck(NULL, NULL);
		break;
	case EArmType_Taoist:
		ID_CHECKBOX_QiangOnCheckBoxCheck(NULL, NULL);
		break;
	}
	*/

	m_pID_CHECKBOX_JobOther->SetEnable( false );

	//	初始化国家CheckBox		added by zhuomeng.hu		[8/19/2010]
	m_pID_CHECKBOX_CountryAuto->SetCheck( true );
	m_pID_PICTURE_CountryIcon1->SetVisable( false );
	m_pID_PICTURE_CountryIcon2->SetVisable( false );
	m_pID_PICTURE_CountryIcon3->SetVisable( false );
	m_pID_PICTURE_CountryIcon4->SetVisable( false );
	m_pID_PICTURE_CountryIconRandom->SetVisable( true );
	//m_pID_TEXT_CountryAutoDesc->SetText( "" );
    m_pID_TEXT_CountryName->SetText( "" );
    m_pID_TEXT_CountryDesc->SetText( theXmlString.GetString( eText_Country_Describe_Random ) );
	switch( m_nRealCountry )
	{
	case CountryDefine::Country_Init:
		break;
	case CountryDefine::Country_LouLan:
		ID_CHECKBOX_Country1OnCheckBoxCheck( 0, &bChecked );
		break;
	case CountryDefine::Country_KunLun:
		ID_CHECKBOX_Country2OnCheckBoxCheck( 0, &bChecked );
		break;
	case CountryDefine::Country_DunHuang:
		ID_CHECKBOX_Country3OnCheckBoxCheck( 0, &bChecked );
		break;
	//case CountryDefine::Country_LaiYin:
	//	ID_CHECKBOX_Country4OnCheckBoxCheck( 0, &bChecked );
	//	break;
	}

	//	初始化人物头像		added by zhuomeng.hu		[8/24/2010]
	m_nSelPortraitId = 0;
	m_nShowRow = 0;
	LoadPortrait();
	UpdatePortrait( m_nSex, m_nSelPortraitId, m_nShowRow );

	m_bNeedPlayEffect = true;
	/////Refresh( false );

	USE_SCRIPT( eUI_OBJECT_Create, this );

	if(	!s_hImcDef )
		s_hImcDef = ImmGetContext(g_hWnd);

	ImmReleaseContext( g_hWnd, s_hImcDef );
	ImmAssociateContext( g_hWnd, s_hImcDef );

	theUiManager.Compositor();
	theUiManager.SetFocus( m_pID_EDIT_Name );

	m_fPlayerScale = 0.9;
	m_fRot = gCfg.m_fSelectRoleRotateZ;
	s_bPressEnter = false;
	m_iEffectID = 0;

	if(m_nRealCountry == CountryDefine::Country_Init)
	{
		m_pID_CHECKBOX_CountryAuto->SetCheck(true);
	}

	if(m_pID_COMBOBOX_Month != NULL)
	{
		m_pID_COMBOBOX_Month->GetEditInput().SetReadOnly(true);
		InitMonthCombobox(m_pID_COMBOBOX_Month);
	}

	if(m_pID_COMBOBOX_Day != NULL)
	{
		m_pID_COMBOBOX_Day->GetEditInput().SetReadOnly(true);
	}

	return true;
	unguard;
}

// 卸载UI
bool CUI_ID_FRAME_CREATE::_UnLoadUI()
{
	guardfunc;
	SAFE_DESTROY_AND_DELETE(m_pPlayerAnim);
	CLOSE_SCRIPT( eUI_OBJECT_Create );
	SAFE_DESTROY_AND_DELETE(m_pPlayer);
	SAFE_DESTROY_AND_DELETE(m_pCamera);
	m_pCameraModel = NULL;
	m_pBGModel  = NULL;

	m_pID_FRAME_CREATE = NULL;
//	m_pID_PICTURE_Property = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_PICTURE_JobWall = NULL;
	m_pID_EDIT_Name = NULL;
	m_pID_BUTTON_CheckName = NULL;
	m_pID_PICTURE_HairWall = NULL;
	m_pID_PICTURE_FaceWall = NULL;
	m_pID_BUTTON_HairL = NULL;
	m_pID_BUTTON_HairR = NULL;
	m_pID_BUTTON_HeadL = NULL;
	m_pID_BUTTON_HeadR = NULL;
	m_pID_PICTURE_TitlePic = NULL;
	m_pID_PICTURE_FenGe = NULL;
	m_pID_BUTTON_TurnR = NULL;
	m_pID_BUTTON_TurnL = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_Hair = NULL;
	m_pID_TEXT_Face = NULL;
	m_pID_TEXT_ProName = NULL;
	m_pID_TEXT_ProInfo = NULL;
// 	m_pID_PICTURE_Spear = NULL;
// 	m_pID_PICTURE_Sword = NULL;
// 	m_pID_PICTURE_Staff = NULL;
// 	m_pID_PICTURE_Fan = NULL;
// 	m_pID_PICTURE_Bow = NULL;
	m_pID_CHECKBOX_JobOther = NULL;
// 	m_pID_TEXT_Sex = NULL;
// 	m_pID_TEXT_Man = NULL;
// 	m_pID_TEXT_Woman = NULL;
	m_pID_CHECKBOX_Man = NULL;
	m_pID_CHECKBOX_Woman = NULL;
	m_pID_CHECKBOX_Spear = NULL;
	m_pID_CHECKBOX_Sword = NULL;
	m_pID_CHECKBOX_Staff = NULL;
	m_pID_CHECKBOX_Bow = NULL;
	m_pID_CHECKBOX_Fan = NULL;
	m_pID_SCROLLBAREX_Stature = NULL;
	//m_pID_TEXT_StatureZ = NULL;
	//m_pID_TEXT_Low = NULL;
	//m_pID_TEXT_High = NULL;

	//  国家  added by zhuomeng.hu		[8/18/2010]
	m_pID_CHECKBOX_Country1 = NULL;
	m_pID_CHECKBOX_Country2 = NULL;
	m_pID_CHECKBOX_Country3 = NULL;
	m_pID_CHECKBOX_Country4 = NULL;
	m_pID_TEXT_CountryDesc = NULL;
	m_pID_PICTURE_CountryIcon1 = NULL;
	m_pID_PICTURE_CountryIcon2 = NULL;
	m_pID_PICTURE_CountryIcon3 = NULL;
	m_pID_PICTURE_CountryIcon4 = NULL;
	m_pID_PICTURE_CountryIconRandom = NULL;
	m_pID_TEXT_CountryName = NULL;
	m_pID_CHECKBOX_CountryAuto = NULL;
	m_pID_TEXT_CountryAutoText = NULL;
	m_pID_TEXT_CountryAutoDesc = NULL;

	// 头像		added by zhuomeng.hu		[8/20/2010]
	m_pID_CHECKBOX_Portrait1 = NULL;
	m_pID_CHECKBOX_Portrait2 = NULL;
	m_pID_CHECKBOX_Portrait3 = NULL;
	m_pID_CHECKBOX_Portrait4 = NULL;
	m_pID_BUTTON_HeadUp = NULL;
	m_pID_BUTTON_HeadDown = NULL;
	DestroyAvatarSystemSetting();
	return theUiManager.RemoveFrame( "Data\\UI\\Create.MEUI" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_CREATE::_IsVisable()
{
	guardfunc;
	if(!m_pID_FRAME_CREATE)
		return false;

	return m_pID_FRAME_CREATE->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_CREATE::_SetVisable( const bool bVisable )
{
	guardfunc;
	if(!m_pID_FRAME_CREATE)
		return ;

	m_pID_FRAME_CREATE->SetVisable( bVisable );
	m_nSelEquip = 0;
	//if( bVisable )
	//    m_bZoomInCamera = TRUE;
	unguard;
}

void CUI_ID_FRAME_CREATE::SetStateToSelect(bool bState/* = false*/)
{
	guardfunc;
	m_bToSelect = bState;
	unguard;
}

bool CUI_ID_FRAME_CREATE::GetStateToSelect()
{
	guardfunc;
	return m_bToSelect;
	unguard;
}

//void CUI_ID_FRAME_CREATE::SetStateToSelectWeapon(bool bState/* = false*/)
//{
//    guardfunc;
//    m_bToSelectWeapon = bState;
//    unguard;
//}
//
//bool CUI_ID_FRAME_CREATE::GetStateToSelectWeapon()
//{
//    guardfunc;
//    return m_bToSelectWeapon;
//    unguard;
//}
void CUI_ID_FRAME_CREATE::RefreshEffect()
{
	int iSelect = -1;
	m_szEffectName[0] = '0';
	// 更新装备
	if( m_pSex->SItems[m_nSex].stItem == Sex_Male )
	{
		// 男
		for(int i=0; i<m_iMaleNum; ++i)
		{
			if( m_nCountry == gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[i].nProfession )
			{
				iSelect = i;
				break;
			}
		}
		if( iSelect >= 0 )
		{
			strcpy(m_szEffectName, gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].szEffectName);
		}
	}
	else
	{
		// 女
		for(int i=0; i<m_iFemaleNum; ++i)
		{
			if( m_nCountry == gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[i].nProfession )
			{
				iSelect = i;
				break;
			}
		}
		if( iSelect >= 0 )
		{
			strcpy(m_szEffectName, gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].szEffectName);
		}
	}
	if( m_szEffectName[0] != '0' )
	{
		m_bNeedPlayEffect = true;
	}
}

void CUI_ID_FRAME_CREATE::Refresh( bool bUseDefault, bool bPlayAnim/* = true*/, bool bResetAnim/* = true*/ )
{
	guardfunc;
	if(!m_pPlayerAnim)
		return;
    
    // 重置相机     added by zhuomeng.hu		[10/8/2010]
    if( bResetAnim )
	{
        //m_fRot = 0.0f;
		m_fRot = gCfg.m_fSelectRoleRotateZ;
	}

	//int iSelect = -1;
	int iSelect = 0;
	// 更新装备
	/*
	if( m_pSex->SItems[m_nSex].stItem == Sex_Male )
	{
		// 男
		for(int i=0; i<m_iMaleNum; ++i)
		{
			if( m_nCountry == gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[i].nProfession )
			{
				iSelect = i;
				break;
			}
		}
		if( iSelect >= 0 )
		{
			m_PlayerEquip[eKeyAll_Face].iModelID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nFaceModelId;
			m_PlayerEquip[eKeyAll_Armour].item.itembaseinfo.ustItemID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nArmourItemId;
			m_PlayerEquip[eKeyAll_Armour].iModelID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nArmourModelId;
			m_PlayerEquip[eKeyAll_Glove].item.itembaseinfo.ustItemID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nGloveItemId;
			m_PlayerEquip[eKeyAll_Glove].iModelID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nGloveModelId;
			m_PlayerEquip[eKeyAll_Shoe].item.itembaseinfo.ustItemID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nShoeItemId;
			m_PlayerEquip[eKeyAll_Shoe].iModelID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nShoeModelId;

			// 左手也可能有武器
			m_PlayerEquip[eKeyAll_LHandItem].iModelID = ErrorUnsignedShortID;			

			m_PlayerEquip[eKeyAll_Badge].iModelID = ErrorUnsignedShortID;
			m_PlayerEquip[eKeyAll_Sash].item.itembaseinfo.ustItemID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nSashItemId;
			m_PlayerEquip[eKeyAll_Sash].iModelID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nSashModelId;
			m_PlayerEquip[eKeyAll_RHandItem].iModelID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nWeaponModelId;
			m_PlayerEquip[eKeyAll_RHandItem].item.itembaseinfo.ustItemID = gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nWeaponItemId;

			//strcpy(m_szEffectName, gCfg.m_vMaleCreateSetting[iSelect].szEffectName);
		}
	}
	else
	{
		// 女
		for(int i=0; i<m_iFemaleNum; ++i)
		{
			if( m_nCountry == gCfg.m_MaleRoleSetting[m_nSelEquip].m_vCreateSetting[i].nProfession )
			{
				iSelect = i;
				break;
			}
		}
		if( iSelect >= 0 )
		{
			m_PlayerEquip[eKeyAll_Face].iModelID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nFaceModelId;
			m_PlayerEquip[eKeyAll_Armour].item.itembaseinfo.ustItemID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nArmourItemId;
			m_PlayerEquip[eKeyAll_Armour].iModelID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nArmourModelId;
			m_PlayerEquip[eKeyAll_Glove].item.itembaseinfo.ustItemID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nGloveItemId;
			m_PlayerEquip[eKeyAll_Glove].iModelID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nGloveModelId;
			m_PlayerEquip[eKeyAll_Shoe].item.itembaseinfo.ustItemID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nShoeItemId;
			m_PlayerEquip[eKeyAll_Shoe].iModelID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nShoeModelId;
			m_PlayerEquip[eKeyAll_LHandItem].iModelID = ErrorUnsignedShortID;
			m_PlayerEquip[eKeyAll_Badge].iModelID = ErrorUnsignedShortID;
			m_PlayerEquip[eKeyAll_Sash].item.itembaseinfo.ustItemID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nSashItemId;
			m_PlayerEquip[eKeyAll_Sash].iModelID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nSashModelId;
			m_PlayerEquip[eKeyAll_RHandItem].iModelID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nWeaponModelId;
			m_PlayerEquip[eKeyAll_RHandItem].item.itembaseinfo.ustItemID = gCfg.m_FemaleRoleSetting[m_nSelEquip].m_vCreateSetting[iSelect].nWeaponItemId;

			//strcpy(m_szEffectName, gCfg.m_vFemaleCreateSetting[iSelect].szEffectName);
		}
	}
	*/

	if( m_pSex->SItems[m_nSex].stItem == Sex_Male )
	{
		// 男
		m_PlayerEquip[eKeyAll_Face].iModelID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nFaceModelId;
		m_PlayerEquip[eKeyAll_Armour].item.itembaseinfo.ustItemID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nArmourItemId;
		m_PlayerEquip[eKeyAll_Armour].iModelID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nArmourModelId;
		m_PlayerEquip[eKeyAll_Glove].item.itembaseinfo.ustItemID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nGloveItemId;
		m_PlayerEquip[eKeyAll_Glove].iModelID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nGloveModelId;
		m_PlayerEquip[eKeyAll_Shoe].item.itembaseinfo.ustItemID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nShoeItemId;
		m_PlayerEquip[eKeyAll_Shoe].iModelID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nShoeModelId;

		// 左手也可能有武器
		m_PlayerEquip[eKeyAll_LHandItem].iModelID = ErrorUnsignedShortID;			

		m_PlayerEquip[eKeyAll_Badge].iModelID = ErrorUnsignedShortID;
		m_PlayerEquip[eKeyAll_Sash].item.itembaseinfo.ustItemID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nSashItemId;
		m_PlayerEquip[eKeyAll_Sash].iModelID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nSashModelId;
		m_PlayerEquip[eKeyAll_RHandItem].iModelID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nWeaponModelId;
		m_PlayerEquip[eKeyAll_RHandItem].item.itembaseinfo.ustItemID = gCfg.m_MaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nWeaponItemId;
	}
	else
	{
		// 女
		m_PlayerEquip[eKeyAll_Face].iModelID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nFaceModelId;
		m_PlayerEquip[eKeyAll_Armour].item.itembaseinfo.ustItemID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nArmourItemId;
		m_PlayerEquip[eKeyAll_Armour].iModelID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nArmourModelId;
		m_PlayerEquip[eKeyAll_Glove].item.itembaseinfo.ustItemID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nGloveItemId;
		m_PlayerEquip[eKeyAll_Glove].iModelID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nGloveModelId;
		m_PlayerEquip[eKeyAll_Shoe].item.itembaseinfo.ustItemID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nShoeItemId;
		m_PlayerEquip[eKeyAll_Shoe].iModelID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nShoeModelId;
		m_PlayerEquip[eKeyAll_LHandItem].iModelID = ErrorUnsignedShortID;
		m_PlayerEquip[eKeyAll_Badge].iModelID = ErrorUnsignedShortID;
		m_PlayerEquip[eKeyAll_Sash].item.itembaseinfo.ustItemID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nSashItemId;
		m_PlayerEquip[eKeyAll_Sash].iModelID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nSashModelId;
		m_PlayerEquip[eKeyAll_RHandItem].iModelID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nWeaponModelId;
		m_PlayerEquip[eKeyAll_RHandItem].item.itembaseinfo.ustItemID = gCfg.m_FemaleRoleSetting[m_nCountry].m_vCreateSetting[iSelect].nWeaponItemId;
	}
	if( iSelect >= 0 )
		memcpy(&m_equip, &m_PlayerEquip, sizeof(CPlayer_SEquipment) * eKeyAll_Max);

	if( !bUseDefault )
	{
		// 男
		if ( m_pSex->SItems[m_nSex].stItem == Sex_Male )
		{
			m_equip[eKeyAll_Hair].iModelID = m_pMaleHairId->SItems[m_nHair].stItem;
			m_equip[eKeyAll_Face].iModelID = m_pMaleFaceId->SItems[m_nFace].stItem;
			m_equip[eKeyAll_Helmet].iModelID = ErrorUnsignedShortID;
			m_equip[eKeyAll_Helmet].iModelID2 = ErrorUnsignedShortID;
			m_pID_TEXT_Hair->SetText(m_pMaleHairId->SItems[m_nHair].strName);
			m_pID_TEXT_Face->SetText(m_pMaleFaceId->SItems[m_nFace].strName);
			m_pID_TEXT_Armour->SetText(gCfg.m_MaleRoleSetting[m_nSelEquip].m_strName.c_str());

		}
		// 女
		else
		{
			m_equip[eKeyAll_Hair].iModelID = m_pFemaleHairId->SItems[m_nHair].stItem;
			m_equip[eKeyAll_Face].iModelID = m_pFemaleFaceId->SItems[m_nFace].stItem;
			m_equip[eKeyAll_Helmet].iModelID = ErrorUnsignedShortID;
			m_equip[eKeyAll_Helmet].iModelID2 = ErrorUnsignedShortID;
			m_pID_TEXT_Hair->SetText(m_pFemaleHairId->SItems[m_nHair].strName);
			m_pID_TEXT_Face->SetText(m_pFemaleFaceId->SItems[m_nFace].strName);
			m_pID_TEXT_Armour->SetText(gCfg.m_FemaleRoleSetting[m_nSelEquip].m_strName.c_str());
		}
	}
	else
	{
		// 男
		if ( m_pSex->SItems[m_nSex].stItem == Sex_Male )
		{
			m_equip[eKeyAll_Hair].iModelID = m_pMaleHairId->SItems[0].stItem;
			m_equip[eKeyAll_Face].iModelID = m_pMaleFaceId->SItems[0].stItem;
			m_equip[eKeyAll_Helmet].iModelID = ErrorUnsignedShortID;
			m_equip[eKeyAll_Helmet].iModelID2 = ErrorUnsignedShortID;
			m_pID_TEXT_Hair->SetText(m_pMaleHairId->SItems[0].strName);
			m_pID_TEXT_Face->SetText(m_pMaleFaceId->SItems[0].strName);
			m_pID_TEXT_Armour->SetText(gCfg.m_MaleRoleSetting[0].m_strName.c_str());
		}
		// 女
		else
		{
			m_equip[eKeyAll_Hair].iModelID = m_pFemaleHairId->SItems[0].stItem;
			m_equip[eKeyAll_Face].iModelID = m_pFemaleFaceId->SItems[0].stItem;
			m_equip[eKeyAll_Helmet].iModelID = ErrorUnsignedShortID;
			m_equip[eKeyAll_Helmet].iModelID2 = ErrorUnsignedShortID;
			m_pID_TEXT_Hair->SetText(m_pFemaleHairId->SItems[0].strName);
			m_pID_TEXT_Face->SetText(m_pFemaleFaceId->SItems[0].strName);
			m_pID_TEXT_Armour->SetText(gCfg.m_FemaleRoleSetting[0].m_strName.c_str());
		}
	}

	BOOL bMultiThreadLoadingMex = g_bMultiThreadLoadingMex;
	g_bMultiThreadLoadingMex = FALSE;

	CPlayer_SEquipment weapon = m_equip[eKeyAll_RHandItem];
	m_equip[eKeyAll_RHandItem].iModelID = ErrorUnsignedShortID;
	m_equip[eKeyAll_RHandItem].item.itembaseinfo.ustItemID = InvalidLogicNumber;

	DWORD dwLastAnimType = m_pPlayerAnim->GetCurAnimType();
	m_equip[eKeyAll_RHandItem] = weapon;
	m_pPlayerAnim->ChangeSkeletonAndEquipAll(m_equip, m_pSex->SItems[m_nSex].stItem, m_nCountry, m_nHairColor, m_nSelEquip);

	m_pPlayerAnim->UpdateHardItem( false, m_equip );
	g_bMultiThreadLoadingMex = bMultiThreadLoadingMex;
	// 恢复动作类型
	m_pPlayerAnim->SetCurAnimType(dwLastAnimType); 

	if ( bPlayAnim )
	{
		if ( bResetAnim )
			m_pPlayerAnim->SetCurAnimType(0);
		int ret = m_pPlayerAnim->PlayAnimByActionName(gCfg.m_pszCreatePlayAnim,MexAnimCtrl::eNormalPlay,0,1,MexAnimCtrl::eMaxTimeout,
			0, "single_idle", MexAnimCtrl::eNormalPlay );
	}
	else
	{
		m_pPlayerAnim->PlayAnimByActionName("single_idle",MexAnimCtrl::eNormalPlay,0,1,MexAnimCtrl::eMaxTimeout,
			0,"single_idle",MexAnimCtrl::eNormalPlay );
	}

// 	m_pID_PICTURE_Spear->SetVisable(false);
// 	m_pID_PICTURE_Sword->SetVisable(false);
// 	m_pID_PICTURE_Staff->SetVisable(false);
// 	m_pID_PICTURE_Fan->SetVisable(false);
// 	m_pID_PICTURE_Bow->SetVisable(false);

// 	switch (m_nCountry)
// 	{
// 	case EArmType_Warrior:
// 		{
// 			m_pID_PICTURE_Spear->SetVisable(true);
// 		}
// 		break;
// 	case EArmType_Mage:
// 		{
// 			m_pID_PICTURE_Staff->SetVisable(true);
// 		}
// 		break;
// 	case EArmType_Assassin:
// 		{
// 			m_pID_PICTURE_Sword->SetVisable(true);
// 		}
// 		break;
// 	case EArmType_Taoist:
// 		{
// 			m_pID_PICTURE_Fan->SetVisable(true);
// 		}
// 		break;
// 	case EArmType_Hunter:
// 		{
// 			m_pID_PICTURE_Bow->SetVisable(true);
// 		}
// 		break;
// 	}
	unguard;
}

void CUI_ID_FRAME_CREATE::InitProfession( int nProfession )
{
	guardfunc;
    // 目前职业索引最大为 EArmType_Hunter， 以后改为 EArmType_Sniper
	if( nProfession < EArmType_Warrior || nProfession > EArmType_Hunter )
		m_nCountry = EArmType_Warrior;
	else
		m_nCountry = nProfession;
	unguard;
}

bool CUI_ID_FRAME_CREATE::PickPlayerOnLButtonUp()
{
	if( !m_pPlayerAnim )
		return false;

	POINT ptMouse;
	GetCursorPos( &ptMouse );
	ScreenToClient( g_hWnd, &ptMouse );

	D3DXVECTOR3 vFrom, vDir;
	m_pCamera->BuildPickRay( 
		ptMouse.x, 
		ptMouse.y,
		vFrom,
		vDir,
		SCREEN_WIDTH,
		SCREEN_HEIGHT );

	std::map<short, CPlayer*>::iterator it;
	std::vector<CPlayer*> vectorSelPlayer;
	int nArrayPlayerCount = 0;
	bool bPickPlayer = false;
	if( m_pPlayerAnim->GetWorldBBox()->Intersect( *(Vector*)&vFrom, *(Vector*)&vDir ) )
	{
		bPickPlayer = true;
		m_pPlayerAnim->PlayAnimByActionName( gCfg.m_pszCreatePlayAnim,
			MexAnimCtrl::eNormalPlay,
			0,
			1,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			"single_idle",
			MexAnimCtrl::eNormalPlay );
	}
	return bPickPlayer;
}

void CUI_ID_FRAME_CREATE::Clear()
{
	m_nFace = 0;
	m_nHair = 0;
	m_nHairColor = 1;
	m_nCloth = 0;
}

bool CUI_ID_FRAME_CREATE::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if ( bMsgUsed == true || g_GameState != G_CREATE )
		return false;

	if( msg == WM_KEYUP )
	{
		if( wParam == VK_ESCAPE )
		{
			m_bToSelect = true;
			g_bCreateOk = FALSE;
			return true;
		}
		else if( wParam == VK_RETURN )
		{
			s_bPressEnter = true;
			return true;
		}
	}

	return false;

	unguard;
}

void CUI_ID_FRAME_CREATE::ResetStature()
{
	m_fPlayerScale = 0.9;
	m_pID_SCROLLBAREX_Stature->SetValue(500);
}

void CUI_ID_FRAME_CREATE::SetSex( int sex )
{
	if( sex < 0 || sex > 1 )
		return;

	m_nSex = sex;
	if( m_pID_FRAME_CREATE && m_pID_TEXT_Low && m_pID_TEXT_High )
	{
		if( m_nSex == 0 )
		{
			m_pID_TEXT_Low->SetText(theXmlString.GetString(eText_CreateChar_MaleShort));
			m_pID_TEXT_High->SetText(theXmlString.GetString(eText_CreateChar_MaleTall));
		}
		else
		{
			m_pID_TEXT_Low->SetText(theXmlString.GetString(eText_CreateChar_FemaleShort));
			m_pID_TEXT_High->SetText(theXmlString.GetString(eText_CreateChar_FemaleTall));
		}
	}
}

ControlEdit* CUI_ID_FRAME_CREATE::GetEditName()
{
	if(!m_pID_EDIT_Name)
		assert(false&&"ui error");

	return m_pID_EDIT_Name;
}

bool g_IsFileExist(const char* lpFileName )
{
// 	if (g_DirectReadInPackage)
// 	{
// 		return swIsFileExist(lpFileName);
// 	}
// 	else
// 	{
		return ( _access_s( lpFileName, 0 ) == 0 );
//	}
}
//	加载头像			added by zhuomeng.hu		[8/24/2010]
void CUI_ID_FRAME_CREATE::LoadPortrait()
{
	m_defPortrait = "";
	m_malePortraitVec.clear();
	m_femalePortraitVec.clear();
	
	HANDLE hFindNml;//, hFindGrey;
	bool bFindNext;
	std::string nmlFilePath, greyFilePath, strFirst, strSecond;
	WIN32_FIND_DATA nmlFileData;//, greyFileData;

	// 缺省背景
	nmlFilePath = PORTRAIT_PATH + std::string( "Default.dds" );
	if(g_IsFileExist(nmlFilePath.c_str()))
	{
		m_defPortrait = PORTRAIT_FILE + std::string( "Default.dds" );
	}

	// Male 头像列表
	nmlFilePath = PORTRAIT_PATH + std::string( "male_*.dds" );
	hFindNml = FindFirstFile( nmlFilePath.c_str(), &nmlFileData );
	bFindNext = true;
	if( hFindNml != INVALID_HANDLE_VALUE )
	{
		while( bFindNext )
		{
			greyFilePath = std::string( nmlFileData.cFileName );
			greyFilePath.replace( 0, 5, "maleGrey_" );
			greyFilePath = PORTRAIT_PATH + greyFilePath;
// 			hFindGrey = FindFirstFile( greyFilePath.c_str(), &greyFileData );
			if(g_IsFileExist(greyFilePath.c_str()))
			{
				strFirst = PORTRAIT_FILE + std::string( nmlFileData.cFileName );
// 				strSecond = PORTRAIT_FILE + std::string( greyFileData.cFileName );
				greyFilePath = std::string( nmlFileData.cFileName );
				greyFilePath.replace( 0, 5, "maleGrey_" );
				greyFilePath = PORTRAIT_FILE + greyFilePath;
				m_malePortraitVec.push_back( make_pair( strFirst, greyFilePath) );
// 				FindClose( hFindGrey );
			}
			bFindNext = FindNextFile( hFindNml, &nmlFileData );	
		}
		FindClose( hFindNml );
	}
	
	// Female 头像列表
	nmlFilePath = PORTRAIT_PATH + std::string( "female_*.dds" );
	hFindNml = FindFirstFile( nmlFilePath.c_str(), &nmlFileData );
	bFindNext = true;
	if( hFindNml != INVALID_HANDLE_VALUE )
	{
		while( bFindNext )
		{
			greyFilePath = std::string( nmlFileData.cFileName );
			greyFilePath.replace( 0, 7, "femaleGrey_" );
			greyFilePath = PORTRAIT_PATH + greyFilePath;
// 			hFindGrey = FindFirstFile( greyFilePath.c_str(), &greyFileData );
			if( g_IsFileExist(greyFilePath.c_str()))
			{
				strFirst = PORTRAIT_FILE + std::string( nmlFileData.cFileName );
// 				strSecond = PORTRAIT_FILE + std::string( greyFileData.cFileName );
				greyFilePath = std::string( nmlFileData.cFileName );
				greyFilePath.replace( 0, 7, "femaleGrey_" );
				greyFilePath = PORTRAIT_FILE + greyFilePath;
				m_femalePortraitVec.push_back( make_pair( strFirst, greyFilePath ) );
// 				FindClose( hFindGrey );
			}
			bFindNext = FindNextFile( hFindNml, &nmlFileData );	
		}
		FindClose( hFindNml );
	}
}

//	更新头像		added by zhuomeng.hu		[8/24/2010]
void CUI_ID_FRAME_CREATE::UpdatePortrait( int sex, int selectId, int showRow )
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
	assert( sex == Sex_Male || sex == Sex_Female );
	int portraitSize = sex == Sex_Male ? m_malePortraitVec.size() : m_femalePortraitVec.size();

	// 设置向上键
	if( showRow == 0 )
		m_pID_BUTTON_HeadUp->SetEnable( false );
	else
		m_pID_BUTTON_HeadUp->SetEnable( true );

	// 设置向下键
	if( ( portraitSize + 1 ) / 2 > showRow + 2 )
		m_pID_BUTTON_HeadDown->SetEnable( true );
	else
		m_pID_BUTTON_HeadDown->SetEnable( false );

	// 控件大小统一
	int nMargin = ( PORTRAIT_SCALE - m_pID_CHECKBOX_Portrait1->GetWidth() ) / 2;
    RECT rct;
	rct.left = nMargin;
	rct.top = nMargin;
	rct.right = PORTRAIT_SCALE - nMargin;
	rct.bottom = PORTRAIT_SCALE - nMargin;

	// 缺省背景
	if( showRow * 2 + 4 > portraitSize )
	{
		m_pID_CHECKBOX_Portrait4->SetCheckPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait4->SetUnCheckPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait4->SetMoveOnPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait4->SetDisablePic( m_defPortrait.c_str(), &rct, &rct );
	}
	if( showRow * 2 + 3 > portraitSize )
	{
		m_pID_CHECKBOX_Portrait3->SetCheckPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait3->SetUnCheckPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait3->SetMoveOnPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait3->SetDisablePic( m_defPortrait.c_str(), &rct, &rct );
	}
	if( showRow * 2 + 2 > portraitSize )
	{
		m_pID_CHECKBOX_Portrait2->SetCheckPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait2->SetUnCheckPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait2->SetMoveOnPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait2->SetDisablePic( m_defPortrait.c_str(), &rct, &rct );
	}
	if( showRow * 2 + 1 > portraitSize )
	{
		m_pID_CHECKBOX_Portrait1->SetCheckPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait1->SetUnCheckPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait1->SetMoveOnPic( m_defPortrait.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait1->SetDisablePic( m_defPortrait.c_str(), &rct, &rct );
	}

	// 显示头像
	std::vector< pair< std::string, std::string > >* pPortraitVec;
	pPortraitVec = sex == Sex_Male ? &m_malePortraitVec : &m_femalePortraitVec;
	if( portraitSize > showRow * 2 )
	{
		m_pID_CHECKBOX_Portrait1->SetCheckPic( ( *pPortraitVec )[ showRow * 2 ].first.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait1->SetUnCheckPic( ( *pPortraitVec )[ showRow * 2 ].second.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait1->SetMoveOnPic( ( *pPortraitVec )[ showRow * 2 ].second.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait1->SetDisablePic( ( *pPortraitVec )[ showRow * 2 ].second.c_str(), &rct, &rct );
	}
	if( portraitSize > showRow * 2 + 1 )
	{
		m_pID_CHECKBOX_Portrait2->SetCheckPic( ( *pPortraitVec )[ showRow * 2 + 1 ].first.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait2->SetUnCheckPic( ( *pPortraitVec )[ showRow * 2 + 1 ].second.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait2->SetMoveOnPic( ( *pPortraitVec )[ showRow * 2 + 1 ].second.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait2->SetDisablePic( ( *pPortraitVec )[ showRow * 2 + 1 ].second.c_str(), &rct, &rct );
	}
	if( portraitSize > showRow * 2 + 2 )
	{
		m_pID_CHECKBOX_Portrait3->SetCheckPic( ( *pPortraitVec )[ showRow * 2 + 2 ].first.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait3->SetUnCheckPic( ( *pPortraitVec )[ showRow * 2 + 2 ].second.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait3->SetMoveOnPic( ( *pPortraitVec )[ showRow * 2 + 2 ].second.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait3->SetDisablePic( ( *pPortraitVec )[ showRow * 2 + 2 ].second.c_str(), &rct, &rct );
	}
	if( portraitSize > showRow * 2 + 3 )
	{
		m_pID_CHECKBOX_Portrait4->SetCheckPic( ( *pPortraitVec )[ showRow * 2 + 3 ].first.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait4->SetUnCheckPic( ( *pPortraitVec )[ showRow * 2 + 3 ].second.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait4->SetMoveOnPic( ( *pPortraitVec )[ showRow * 2 + 3 ].second.c_str(), &rct, &rct );
		m_pID_CHECKBOX_Portrait4->SetDisablePic( ( *pPortraitVec )[ showRow * 2 + 3 ].second.c_str(), &rct, &rct );
	}

	// 拉伸
	//S_ButtonData* pData = &( ( S_CheckBoxData* )m_pID_CHECKBOX_Portrait1->GetData() )->m_stChecked;
	//pData->m_nDrawMode[ S_BaseData::Mode_Middle ] = DrawModeStrectch;
	//pData = &( ( S_CheckBoxData* )m_pID_CHECKBOX_Portrait2->GetData() )->m_stChecked;
	//pData->m_nDrawMode[ S_BaseData::Mode_Middle ] = DrawModeStrectch;
	//pData = &( ( S_CheckBoxData* )m_pID_CHECKBOX_Portrait3->GetData() )->m_stChecked;
	//pData->m_nDrawMode[ S_BaseData::Mode_Middle ] = DrawModeStrectch;
	//pData = &( ( S_CheckBoxData* )m_pID_CHECKBOX_Portrait4->GetData() )->m_stChecked;
	//pData->m_nDrawMode[ S_BaseData::Mode_Middle ] = DrawModeStrectch;

	// 判断选中
	m_pID_CHECKBOX_Portrait1->SetCheck( false );
	m_pID_CHECKBOX_Portrait2->SetCheck( false );
	m_pID_CHECKBOX_Portrait3->SetCheck( false );
	m_pID_CHECKBOX_Portrait4->SetCheck( false );

	if( selectId >= showRow * 2 && selectId <= showRow * 2 + 3 )
	{
		switch( selectId - showRow * 2 )
		{
		case Portrait_First:
			m_pID_CHECKBOX_Portrait1->SetCheck( true );
			break;
		case Portrait_Second:
			m_pID_CHECKBOX_Portrait2->SetCheck( true );
			break;
		case Portrait_Third:
			m_pID_CHECKBOX_Portrait3->SetCheck( true );
			break;
		case Portrait_Forth:
			m_pID_CHECKBOX_Portrait4->SetCheck( true );
			break;
		default:
			break;
		}
	}
}

std::string CUI_ID_FRAME_CREATE::GetPortraitName( int sex, int portraitId, bool bGrey )
{
    sex = sex < Sex_Female ? Sex_Male : Sex_Female;

    if( sex == Sex_Female )
    {
        // 女
        if( m_femalePortraitVec.size() <= portraitId )
        {
            if( bGrey )
                return PORTRAIT_FILE + std::string( "DefaultFemaleGrey.dds" );
            else
                return PORTRAIT_FILE + std::string( "DefaultFemale.dds" );
        }
        else
        {
            if( bGrey )
                return m_femalePortraitVec[ portraitId ].second;
            else
                return m_femalePortraitVec[ portraitId ].first;
        }

    }
    else
    {
        // 男
        if( m_malePortraitVec.size() <= portraitId )
        {
            if( bGrey )
                return PORTRAIT_FILE + std::string( "DefaultMaleGrey.dds" );
            else
                return PORTRAIT_FILE + std::string( "DefaultMale.dds" );
        }
        else
        {
            if( bGrey )
                return m_malePortraitVec[ portraitId ].second;
            else
                return m_malePortraitVec[ portraitId ].first;
        }
    } 
}

//added by zhuomeng.hu		[9/3/2010]
void CUI_ID_FRAME_CREATE::EnableOKBtn()
{
	if ( !m_pID_FRAME_CREATE )
	{
		assert( false && "ui error" );
		return;
	}
	m_pID_BUTTON_OK->SetEnable( true );
}

void CUI_ID_FRAME_CREATE::RandomPression()
{
    // 由于现在没有火枪这个职业，故在前5个随机，以后需将 EArmType_Sniper 改为 EArmType_MaxSize
    if( EArmType_Sniper )
    {
        int nProfession = rand() % EArmType_Sniper;
        InitProfession( nProfession );
    }
    else
    {
        InitProfession( EArmType_Warrior );
    }
}

// ComboBox
void CUI_ID_FRAME_CREATE::ID_COMBOBOX_MonthOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(NULL == m_pID_COMBOBOX_Month || NULL == m_pID_COMBOBOX_Day)
		return;

	m_pID_COMBOBOX_Month->GetEditInput().SetText(szData);

	ControlList& list = m_pID_COMBOBOX_Month->GetListBox();
	InitDayCombobox(m_pID_COMBOBOX_Day, list.GetCurSelIndex() + 1);
}
// ComboBox
void CUI_ID_FRAME_CREATE::ID_COMBOBOX_DayOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(NULL == m_pID_COMBOBOX_Day)
		return;

	m_pID_COMBOBOX_Day->GetEditInput().SetText(szData);
}

void CUI_ID_FRAME_CREATE::RefreshPlayerAnim(int nSex,int nCountry)
{
	if(nCountry < 0)
		return;

	SetSex(nSex);
	m_nCountry = nCountry;

	ResetStature();
	Refresh(false, true);
	RefreshEffect();
}

const char * CUI_ID_FRAME_CREATE::GetXinZuo(int month,int day)
{
	switch(month)
	{
	case 1:
		if (day >19)
		{
			return theXmlString.GetString(eText_ConShuiPing);
		}
		else
		{
			return theXmlString.GetString(eText_ConMoJie);
		}
	case 2:
		if (day >18)
		{
			return theXmlString.GetString(eText_ConShuangYu);
		}
		else
		{
			return theXmlString.GetString(eText_ConShuiPing);
		}
	case 3:
		if (day >20)
		{
			return theXmlString.GetString(eText_ConBaiYang);
		}
		else
		{
			return theXmlString.GetString(eText_ConShuangYu);
		}
	case 4:
		if (day > 20)
		{
			return theXmlString.GetString(eText_ConJinNiu);
		}
		else
		{
			return theXmlString.GetString(eText_ConBaiYang);
		}
	case 5:
		if (day >20)
		{
			return theXmlString.GetString(eText_ConShuangZi);
		} 
		else
		{
			return theXmlString.GetString(eText_ConJinNiu);
		}
	case 6:
		if (day >21)
		{
			return theXmlString.GetString(eText_ConJuXie);
		} 
		else
		{
			return theXmlString.GetString(eText_ConShuangZi);
		}
	case 7:
		if (day >22)
		{
			return theXmlString.GetString(eText_ConShiZi);
		} 
		else
		{
			return theXmlString.GetString(eText_ConJuXie);
		}
	case 8:
		if (day >22)
		{
			return theXmlString.GetString(eText_ConChuNv);
		} 
		else
		{
			return theXmlString.GetString(eText_ConShiZi);
		}
	case 9:
		if (day >22)
		{
			return theXmlString.GetString(eText_ConTianCheng);
		} 
		else
		{
			return theXmlString.GetString(eText_ConChuNv);
		}
	case 10:
		if (day >22)
		{
			return theXmlString.GetString(eText_ConTianXie);
		} 
		else
		{
			return theXmlString.GetString(eText_ConTianCheng);
		}
	case 11:
		if (day >21)
		{
			return theXmlString.GetString(eText_ConSheShou);
		} 
		else
		{
			return theXmlString.GetString(eText_ConTianXie);
		}
	case 12:
		if (day >21)
		{
			return theXmlString.GetString(eText_ConMoJie);
		}
		else
		{
			return theXmlString.GetString(eText_ConSheShou);
		}
	}
	return NULL;
}

bool CUI_ID_FRAME_CREATE::CreateRole(char bIsTell,void* pData)
{
	if(bIsTell)
		s_CUI_ID_FRAME_CREATE.SendCreateRoleMsg();

	return true;
}
