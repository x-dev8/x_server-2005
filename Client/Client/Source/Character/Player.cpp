#include <math.h>
#include <assert.h>
#include <list>
#include "Me3d\Include.h"
#include "Stdcharskeleton.h"
#include "GlobalDef.h"
#include "player.h"
#include "BattleFlag.h"
#include "playermgr.h"
#include "../Resource/Resource.h"
#include "Cfg.h"
#include "GameMain.h"
#include "NetworkInput.h"
#include "Effect.h"
#include "PlayerRole.h"
#include "SoundConfig.h"
#include "ItemHero.h"
#include "MonsterStatusMgr.h"
#include "ProfileDefines.h"
#include "Me3d/Decal.h"
#include "Me3d/basegraphics.h"
#include "ErrorLog.h"
#include "TitleConfig.h"
#include "PlayerAnimCtrl.h"
#include "itemdetail.h"
#include "MiniMap.h"
#include "Me3d/MoreAction.h"
#include "XmlStringLanguage.h"
#include "g_assert.h"
#include "FuncPerformanceLog.h"
#include "ui/MessageBox.h"
#include "ui/Progress.h"
#include "ui/ChatInfoBox.h"
#include "ui/ExitGame.h"
#include "ui/NpcChatDialogBox.h"
#include "SkillEffectSlk.h"
#include "AttackInfoMan.h"
#include "official.h"
#include "ui/Group.h"
#include "ui/PrivateShop.h"
#include "ui/PlayerPrivateShop.h"
#include "FuncPerformanceLog.h"
#include "dxutil.h"
#include "ProcessCharInfo.h"
#include "MathLib.h"
#include "Systemconfig.h"
#include "Logger.h"
#include "Me3d/Effect/EffectManager.h"
#include "CfgFileLoader.h"
#include "ShowScreenText.h"
#include "ui/UIStorage.h"
#include "ui/MiniMapUI.h"
#include "ui/Compound.h"
#include "ui/escdlg.h"
#include "FilePath.h"
#include "modelslk.h"
#include "color_config.h"
#include  "SystemConfig.h"
#include "Me3d/effect/MexEffectCtrl.h"
#include "MotionBillBoard.h"
#include "GuildIcon.h"
#include "MeFont/MeFont.h"
#include "CameraStuntManager.h"
#include "Me3d/ShaderMgr.h"
#include "Sociality.h"
#include "Me3d/Md5Manager.h"
#include "ui/InputBox.h"
#include "ui/Shop.h"
#include "ui/GameSettingUI.h"
#include "ui/Team.h"
#include "ui/CrowdCarryMain.h"
#include "ui/CrowdCarryMainMore.h"
#include "Me3d/Engine/RendererDx.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "wsRender.h"
#include "MeTerrain/NdlRes.h"
#include "PathDirection.h"
#include "Font3D.h"
#include "Font3DManager.h"
#include "MeAudio/meaudio.h"
#include "ActionManager.h"
#include "CrossMapPF.h"
#include "MeTerrain/FootPrint.h"
#include "ProgressBar3DManager.h"
#include "ui/SystemSetting.h"
//#include "Launcher/DataLauncher.h"
#include "exmain.h"
#include "ui/PickUp.h"
#include "Dxsdk/dinput.h"
#include "UI/GameSetting.h"
#include "NpcInfo.h"
#include "chatcheck.h"
#include "MapConfig.h"
#include "../GameUI/AutoAttackSet.h"
#include "ui/PropertyDlg.h"
#include "WSModelEffect.h"
#include "wsCamera.h"
#include "TeamBattleResult.h"
#include "Common.h"
#include "SoundConfig.h"
#include "PreventWallow.h"
#include "MeFont/MeFontSystem.h"
#include "CountryDefine.h"			//added by zhuomeng.hu		[9/10/2010]
#include "CountryConfig.h"          //added by zhuomeng.hu		[10/9/2010]
#include "MultiThreadMexLoading.h"
#include "MonsterDefine.h"
#include "Ui/InfoList.h"
#include "CountryFunction.h"
#include "NpcTaskDialogBox.h"
#include <MeFoundation/MeLoopThread.h>
#include <MeFoundation/MeLoopThreadMan.h>
#include "Mex2LoadReq.h"
#include "AttackFunction.h"
#include "SystemStallage.h"
#include "Me3d/Model/Mex2.h"
#include "SystemFamily.h"
#include "FamilyDefine.h"
#include "CarryMain.h"
#include "ScenePlay.h"
#include "PetSettingConfig.h"
#include "PlayerInfoMgr.h"
#include "ModelConfig.h"
#include "GameMain.h"
#include "RankTitleConfig.h"
#include "CountryTitleConfig.h"

#define ROTATECORRECT 0.02f

#define THEROLEANDTERRAINOFFZLIMIT -0.0618f
#define	CHAT_INFO_WIDTH_MAX	32
#define CHAT_PAOPAO_WORDS_MAX   15

#define PRIVATESHOP_LENGTH_FACTOR 0.8f

#define MEX2NOTLOADINGCOMPLETE -2
#define THEBONENOTEXISTINMEX2 -1

/// ����ѹ�����ͣ�ǿ�ƣ����룩
#define USE_ANIMATION_OPTIMIZATION 0// ʹ�ö����Ż���Զ��ģ�ͼ�֡����һ��
#define USE_ANIMATION_OPTIMIZATION_FORCE 1

float g_fLastTheRoleRotateZCorrect = 0;

extern short GetKeyboardInput( int iKey );
extern CCameraStuntManager g_CameraStuntManager;		//������ؼ�������
extern BOOL g_bMultiThreadLoadingMex;
extern	BOOL	g_bRotateEnable;

extern float g_fTheRoleRotateZCorrect;
extern float g_fTheRoleBBoxHeight;

extern  CHeroGame	theHeroGame;
extern CHeroGame* theApp;
extern POINT GetNextPos( int x, int y, BYTE dir );
extern void DrawBloodBar( int x, int y, int h, 
						 int nFrameWidth, 
						 int nBloodWidth, 
						 DWORD dwBloodColor );
extern int				g_nTargetPointEffectContainerID;

extern bool CheckMapCanPk(CPlayer* pSrcPlayer,CPlayer* pTargetPlayer);
extern bool CheckMapCanAssistant(CPlayer* pSrcPlayer,CPlayer* pTargetPlayer);

int g_nPlayerCount = 0;

DWORD	g_dwMovePathLogID = 0;
int		g_nMovePathCount = 0;
extern  short   g_shDeadIngDuration;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern float g_fLookatPtHeight;

extern BOOL	g_bAutoRunForward;

extern MexAnimCtrl GTeamFlag[MaxMainpleCnt];

float g_fPlayerRotateSpeed = 360/180*D3DX_PI;
float g_fPlayerCollisionHeight = 30.0f;
float g_fTheRoleDirCorrect = 0;

extern DWORD g_dwLastFrameCostTime;
extern DWORD g_dwLastFrameBeginTime;

DWORD g_dwSmoothFrame = 30;


extern BOOL			g_bTheRoleMoveToTargetPos;
extern D3DXVECTOR3	g_vTheRoleTargetPos;
extern D3DXVECTOR3	g_vTheRoleTargetDir;
extern D3DXVECTOR3	g_vTheRoleCurDir;
extern D3DXVECTOR3	g_vTheRoleJumpingDir;

extern float g_fTheRoleJumpingRotate;

extern BOOL	g_bTheRoleMovingByDir;
extern BOOL g_bTheRoleCountermarch;
extern BOOL g_bMouseLButtonIsDown;
extern BOOL g_bMouseRButtonIsDown;

extern DWORD g_dwTheRoleJumpTime;

extern DWORD g_dwTheRoleJumpingEndTime;
extern BOOL	g_bTheRoleJumping; //�����Ƿ�����
extern BOOL g_bTheRoleJumpingCountermarch; //�����Ƿ��������
BOOL g_bTheRoleSlipJumping; //�������»���Ծ
extern BOOL g_bTheRoleFallJumping; //��������
extern D3DXVECTOR3 g_vTheRoleSlipJumpingDir; //�����»���Ծ�ķ���

extern BOOL	g_bTheRoleAttackLockTarget;

extern float g_fTheRoleMovingRate;

extern BOOL g_bShowRoleAttackRange; //��ʾ���ǹ�������
extern float g_fAddRoleAttackRange;

float g_fGravitation = 0.0000098f; //��Ϸ�����е��������ٶ�(�������)
float g_fPlayerDefaultJumpingSpeed = 0.0047f; //��Ϸ�н�ɫ��Ĭ����Ծ�߶�
extern BOOL	g_bbshowItemName = FALSE;

extern BOOL	g_bRenderUI;
extern BOOL g_bMouseMoveMode; //����ƶ�ģʽ
BOOL g_bMouseRoleTurn = TRUE;	         //����������Ƕ�ת������ת��
extern float g_fTheRoleSlipJumpingAngle; //�����»��ĽǶ�
DWORD g_dwTheRoleSlipStartTime = 0; //���ǿ�ʼ�»���ʱ��

extern float g_fTheRoleRunningStep;
static float	g_fTheRoleMovingStep = 1.582f;
extern D3DXVECTOR3	g_vTheRoleAttackTargetPos;
extern int g_nRoleCommonAttackStatus;

extern float g_fCamerFOV;
extern CActionManager g_ActionManager;
extern BOOL g_bRenderFootPrint;
int g_nRenderParticleEmittersLevel = 2;
extern BOOL g_bLastFrameMovebyDir;
extern BOOL g_bAutoPlayInteractionWithTarget;
extern BOOL g_bAutoOpenPrivateShop;
extern BOOL g_b25DRoleMoveFollowMouse;
extern DWORD g_dw25DLButtonDownStartTime;
extern BOOL g_b25DMouseLButtonDownOnTerrain;
extern BOOL    g_bReturnTheCamera;
extern bool IsNormalAttack( unsigned short ustSkillID );
extern bool IsCollectSkill( unsigned short ustSkillID );
extern bool IsMountMonsterSkill( unsigned short ustSkillID );
extern BOOL IsFlagModel(int iModelID);
extern bool IsLootMountSkill( unsigned short ustSkillID );
extern bool IsGoBackSkill( unsigned short ustSkillID );
extern BOOL CanLootHerb(CPlayer* pTargetPlayer, ItemDefine::SItemSkill* pCurSkill, BOOL bShowText);
extern BOOL CanLootMine(CPlayer* pTargetPlayer, ItemDefine::SItemSkill* pCurSkill, BOOL bShowText);
extern BOOL CanLootInsect( CPlayer* pTargetPlayer, ItemDefine::SItemSkill* pCurSkill, BOOL bShowText );
extern BOOL g_bNextNotIntonate;
extern bool CanRenderPlayerEffect( int nPlayerID );
extern const char* GetMPTypeString( int nProfession );

bool CPlayer::m_bShowServerRect = false;
bool CPlayer::m_bShowHeightMapRect = false;
bool CPlayer::m_bShowMyCircle = false;
bool CPlayer::m_bShowMouseCircle = false;
bool CPlayer::m_bHeightMapLoad = false;
float CPlayer::m_fMyCircleR = 0.0f;
float CPlayer::m_fMouseCircleR = 0.0f;
CHeightMapData* CPlayer::m_pHeightMapData = NULL;
CBaseGraphics::Vertex3D CPlayer::m_vtHeightMapRect[ HEIGHTMAP_SHOW_RECT_CNT * HEIGHTMAP_SHOW_RECT_CNT * 6 ];

float g_ZSet       = 0.4f;
float g_ZMoveRate  = 0.00018f;

#ifdef _DEBUG
#define LOG_PLAYER_REF 1
#endif //_DEBUG
char* GetFullFileName(const char* filename)
{
	if (filename == NULL || filename[0] == '\0')
	{
		return NULL;
	}
	static char strFullName[MAX_PATH] = {0};

	MeSprintf_s(strFullName, sizeof(strFullName)-1, "%s\\%s", GetRootPath(), filename);
	return strFullName;
}

BOOL IsChainLightingEffect(const char* pEffectName )
{
	guardfunc;
	if( !pEffectName )
	{
		assert( false );
		return FALSE;
	}

	CFilePath path;
	path.Split( pEffectName );
	pEffectName = (char*)path.GetFileName();

	if( _strnicmp( pEffectName, "CL_", 3 ) == 0 )
	{
		return TRUE;
	}
	return FALSE;
	unguard;
}

BOOL IsChainEffect(const char* pEffectName)
{
	if(!pEffectName)
	{
		assert( false );
		return FALSE;
	}

	CFilePath path;
	path.Split( pEffectName );
	pEffectName = (char*)path.GetFileName();

	if( _strnicmp( pEffectName, "CE_", 3 ) == 0 )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL IsMissileEffect(const char* pEffectName )
{
	guardfunc;
	if( pEffectName )
	{
		CFilePath path;

		path.Split( pEffectName );
		pEffectName = (char*)path.GetFileName();

		const char* szString = pEffectName;
		int nLen = strlen(szString);

		if ( nLen < 4 )
			return FALSE;

		// Is HitFlash Effect
		if( _strnicmp( &szString[0], "MI_", 3 ) == 0 )
		{
			return TRUE;
		}
	}
	return FALSE;
	unguard;
}

BOOL IsHitFlashEffect(const char* pEffectName )
{
	guardfunc;
	if( pEffectName )
	{
		CFilePath path;

		path.Split( pEffectName );
		pEffectName = (char*)path.GetFileName();

		const char* szString = pEffectName;
		int nLen = strlen(szString);

		if ( nLen < 4 )
			return FALSE;

		// Is HitFlash Effect
		if( _strnicmp( &szString[0], "HF_", 3 ) == 0 )
		{
			return TRUE;
		}
	}
	return FALSE;
	unguard;
}

int LoadSkillEffect(ItemDefine::SItemSkill *pSkill)
{
	guardfunc;
	if( !thePlayerRole.m_pBaseInfo )
		return -1;
	unsigned char ucSex = thePlayerRole.m_pBaseInfo->aptotic.ucSex;
	const char *pEffectName = NULL;
	if( ucSex == Sex_Female )
		pEffectName = pSkill->GetIntonateEffectName2();
	else
		pEffectName = pSkill->GetIntonateEffectName();

	if( pEffectName  && stricmp( pEffectName, "NULL" ) != 0 )
	{
		if( IsHitFlashEffect( pEffectName ) )
		{
			CHitFlashEffect* pEffect = MeNew CHitFlashEffect;

			char szFilePath[MAX_PATH] = {0};
			_snprintf( szFilePath, MAX_PATH-1, "data\\effect\\%s", pEffectName );

			if( pEffect->LoadSetting( GetFullFileName(szFilePath) ) )
			{
				int nEffectID = GetEffectMgr()->RegisterEffect( pEffect );
				if( nEffectID == -1 )
				{
					pEffect->Release();
					pEffect = NULL;
				}
			}
			else
			{
				pEffect->Release();
				pEffect = NULL;
			}
		}
		else if( IsMissileEffect( pEffectName ) )
		{
			CMissileEffect* pEffect = MeNew CMissileEffect;

			char szFilePath[MAX_PATH] = {0};
			_snprintf( szFilePath, MAX_PATH-1, "data\\effect\\%s", pEffectName );

			if( pEffect->LoadSetting( GetFullFileName(szFilePath) ) )
			{
				int nEffectID = GetEffectMgr()->RegisterEffect( pEffect );
				if( nEffectID == -1 )
				{
					pEffect->Release();
					pEffect = NULL;
				}
			}
			else
			{
				pEffect->Release();
				pEffect = NULL;
			}
		}
		else if( IsChainLightingEffect( pEffectName ) )
		{
			CChainLightingEffect* pEffect = MeNew CChainLightingEffect;
			char szFilePath[MAX_PATH] = {0};
			_snprintf( szFilePath, MAX_PATH-1, "data\\effect\\%s", pEffectName );

			if( !pEffect->LoadSetting( GetFullFileName(szFilePath) ) )
			{
				pEffect->Release();
				return -1;
			}
			int nEffectId = GetEffectMgr()->RegisterEffect( pEffect );
			if( nEffectId == -1 )
			{
				pEffect->Release();
				return -1;
			}
			return nEffectId;
		}
		else
		{
			CWSModelEffect* pEffect = MeNew CWSModelEffect;

			char szFilePath[MAX_PATH] = {0};
			_snprintf( szFilePath, MAX_PATH-1, "data\\effect\\%s", pEffectName );


			if( pEffect->LoadSetting( GetFullFileName(szFilePath) ) )
			{
				int nEffectID = GetEffectMgr()->RegisterEffect( pEffect );
				if( nEffectID == -1 )
				{
					pEffect->Release();
					pEffect = NULL;
				}
			}
			else
			{
				pEffect->Release();
				pEffect = NULL;
			}
		}
	}
	return -1;
	unguard;
}

int PlayEffect( const char* pEffectName, CPlayer* pSrcPlayer = NULL, float fScale = 0 , DWORD dwFlyTime = 0, CPlayer* pDestPlayer = NULL, int nSlot = 0 ,bool bCalDist = true)
{
	guardfunc;
	if( !pEffectName || !pSrcPlayer )
		return -1;

	if( pSrcPlayer == theHeroGame.GetPlayerMgr()->GetMe() || /*������ʾ*/!pSrcPlayer->m_cFightStatus.IsHide()||!pSrcPlayer->IsHide()) 

	{
		// �ж�pSrcPlayer������ˮƽ���룬����25���򲻲���Ч
		if( pSrcPlayer->IsPlayer() && theHeroGame.GetPlayerMgr()->GetMe() && pSrcPlayer != theHeroGame.GetPlayerMgr()->GetMe() && bCalDist )
		{
			CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
			float fXOffset = pSrcPlayer->GetPos().x - pMe->GetPos().x;
			float fYOffset = pSrcPlayer->GetPos().y - pMe->GetPos().y;
			float fDist = fXOffset*fXOffset + fYOffset*fYOffset;
			if( fDist > 25*25 )
				return -1;
		}


		if( IsHitFlashEffect( pEffectName ) )
		{
			CHitFlashEffect* pEffect = MeNew CHitFlashEffect;

			char szFilePath[MAX_PATH] = {0};
			_snprintf( szFilePath, MAX_PATH-1, "data\\effect\\%s", pEffectName );

			if( pEffect->LoadSetting( GetFullFileName(szFilePath) ) )
			{
				int nEffectID = GetEffectMgr()->RegisterEffect( pEffect );
				if( nEffectID == -1 )
				{
					pEffect->Release();
					pEffect = NULL;
				}
				else
				{
					{
						GSound.PlaySound( GetFullFileName(pEffect->m_szSound), false, &pSrcPlayer->GetPos() );
					}
					pSrcPlayer->CastHitFlashEffect( pEffect );
					// �����ͷ���ID
					pEffect->SetPlayerID(pSrcPlayer->GetID());
					return nEffectID;
				}
			}
			else
			{
				pEffect->Release();
				pEffect = NULL;
			}
		}
		else if( IsMissileEffect( pEffectName ) )
		{
			CMissileEffect* pEffect = MeNew CMissileEffect;

			char szFilePath[MAX_PATH] = {0};
			_snprintf( szFilePath, MAX_PATH-1, "data\\effect\\%s", pEffectName );

			if( pEffect->LoadSetting( GetFullFileName(szFilePath) ) )
			{
				int nEffectID = GetEffectMgr()->RegisterEffect( pEffect );
				if( nEffectID == -1 )
				{
					pEffect->Release();
					pEffect = NULL;
				}
				else
				{
					pSrcPlayer->CastMissileEffect( pEffect, pDestPlayer );
					// �����ͷ���ID
					pEffect->SetPlayerID(pSrcPlayer->GetID());
					return nEffectID;
				}
			}
			else
			{
				pEffect->Release();
				pEffect = NULL;
			}
		}
		else if( IsChainLightingEffect( pEffectName ) )
		{
			CChainLightingEffect* pEffect = MeNew CChainLightingEffect;
			char szFilePath[MAX_PATH] = {0};
			_snprintf( szFilePath, MAX_PATH-1, "data\\effect\\%s", pEffectName );

			if( !pEffect->LoadSetting( GetFullFileName(szFilePath) ) )
			{
				pEffect->Release();
				return -1;
			}
			int nEffectId = GetEffectMgr()->RegisterEffect( pEffect );
			if( nEffectId == -1 )
			{
				pEffect->Release();
				return -1;
			}
			pSrcPlayer->CastChainLightingEffect( pEffect, pDestPlayer );
			// �����ͷ���ID
			pEffect->SetPlayerID(pSrcPlayer->GetID());
			return nEffectId;
		}
		else if(IsChainEffect( pEffectName ) )
		{
			CChainEffect* pEffect = MeNew CChainEffect;
			char szFilePath[MAX_PATH] = {0};
			MeSprintf_s(szFilePath,MAX_PATH - 1,"data\\effect\\%s",pEffectName);

			if( !pEffect->LoadSetting( GetFullFileName(szFilePath)))
			{
				pEffect->Release();
				return - 1;
			}

			int nEffectId = GetEffectMgr()->RegisterEffect(pEffect);
			if(nEffectId == -1)
			{
				pEffect->Release();
				return - 1;
			}

			pSrcPlayer->CastChainEffect(pEffect, pDestPlayer);
			if(pDestPlayer)
			{
				int nID = pDestPlayer->GetID();
				pEffect->SetPlayerID(nID);
			}
			return nEffectId;
		}
		else
		{
			CWSModelEffect* pEffect = MeNew CWSModelEffect;

			char szFilePath[MAX_PATH] = {0};
			_snprintf( szFilePath, MAX_PATH-1, "data\\effect\\%s", pEffectName );

			pEffect->m_dwFlyTime = dwFlyTime;
			pEffect->m_fScale = fScale;

			if( pEffect->LoadSetting( GetFullFileName(szFilePath), TRUE ) )
			{
				int nEffectID = GetEffectMgr()->RegisterEffect( pEffect );
				if( nEffectID == -1 )
				{
					pEffect->Release();
					pEffect = NULL;
				}
				else
				{
					const char* pSoundPath = pEffect->GetSound(Sex_Male==pSrcPlayer->GetSex());
					{
						GSound.PlaySound( GetFullFileName(pSoundPath), false, &pSrcPlayer->GetPos(),3,15 );
					}
					pSrcPlayer->CastModelEffect( pEffect, pDestPlayer, nSlot );
					// �����ͷ���ID
					pEffect->SetPlayerID(pSrcPlayer->GetID());
					return nEffectID;
				}
			}
			else
			{
				pEffect->Release();
				pEffect = NULL;
			}
		}
	}
	return -1;
	unguard;
}

bool CheckMapCanAssistant(CPlayer* pSrcPlayer,CPlayer* pTargetPlayer)
{
	//ֻ�������
	if (!pSrcPlayer) return false;
	if(!pTargetPlayer) return false;

	//�д������Զ�����Լ�
	if(thePlayerRole.GetDuelTarget() == pTargetPlayer->GetID()) //���Ŀ�����ҵ��д�Ŀ��ֱ�ӿ��Դ�
		return false;

	//���Ը��Լ���Ѫ
	if( pSrcPlayer == pTargetPlayer)
		return true; 

	//������Զ���Լ�Ѫ
	if (pTargetPlayer->MyTeamMember)
		return true;





	//�ж�ս���У�ս����ֻ�ܸ� ͬ����Ŀ����м�Ѫ

	CWorldTile* pTile = CURRENTTILE; 
	if (!pTile) return false;

	int pkMode = pTile->GetCanPk();
     int HeroPkMode = pSrcPlayer->GetPKType();

	switch (pkMode)
	{
	case MapConfig::MapData::EPKM_UnAllow_PK: 
		{ 
			//��ȫ���� ���Ը��κ��˼�Ѫ
			 return true;
		}
		break;
	case MapConfig::MapData::EPKM_Guild_PK:
		{
           //ս��ֻ�ܸ�ͬ�������ҽ��м�Ѫ
			return pTargetPlayer->GetGuildId() == pSrcPlayer->GetGuildId();
		}
		break;

	default: //���� ֻ�ܸ������˼�Ѫ
		{
			switch(HeroPkMode)
			{
			case PKMode_Normal: //����ģʽ �����Ը��κα�����Ҽ�Ѫ
				{
				if(pTargetPlayer->GetRealCountry() == thePlayerRole.GetCountry())
					return true;
				}
				break;
			case PKMode_Fight:   //pkģʽ��ֻ�ܸ��Լ���
			case PKMode_Critical:
				{
				  return false;
				}
				break;
			case PKMode_Guild: //����pkģʽ��ֻ�ܸ�ͬ���ŵ��˼�Ѫ
				{
					if(!pTargetPlayer->HasGuild() || !pSrcPlayer->HasGuild()) //��ͬ���Ų��ܼ�Ѫ
						return false;

					return pTargetPlayer->GetGuildId() == pSrcPlayer->GetGuildId();
				}
				break;
			default:
				return false;
			}


		}
	}

	return false;
}

bool CheckMapCanPk(CPlayer* pSrcPlayer,CPlayer* pTargetPlayer)
{
	CWorldTile* pTile = CURRENTTILE;  //lyh++  ��ͼ�Ƿ���pk ���ж� ֻ�����Ŀ��ļ���
	if (!pTile) return false;
	if (!pSrcPlayer) return false;
	if(!pTargetPlayer) return false;

	if(thePlayerRole.GetDuelTarget() == pTargetPlayer->GetID()) //���Ŀ�����ҵ��д�Ŀ��ֱ�ӿ��Դ�
		return true;


	if( thePlayerRole.GetLevel() < gCfg.m_ucPKLevelLimit || pTargetPlayer->GetLevel() < gCfg.m_ucPKLevelLimit)
		return false;  //����pk�ȼ�


	int pkMode = pTile->GetCanPk();

	CMapAreaManager* pAreaManager = theHeroGame.GetPlayerMgr()->m_StageDataLoader.GetMapAreaManager();  //������������ ͨ��λ��������Ŀ���Ƿ��ڰ�ȫ����
	if(pAreaManager)
	{
		int nMaxArea = pAreaManager->GetMaxArea();
		for (int n = 0;n < nMaxArea;++n)
		{
			SArea* pArea = pAreaManager->GetAreaByID(n);
			if(!pArea)
				continue;

			////û��˵�����򣬲�������
			//if(pArea->vctActionData.empty())
			//	continue;

			float fx = 0.0f,fy = 0.0f,fz = 0.0f;
			pTargetPlayer->GetPos( &fx, &fy, &fz );
			POINT pt;
			pt.x = fx;
			pt.y = fy;

			RECT rc;
			rc.left = TileToFloat(pArea->m_rcArea.left);
			rc.top  = TileToFloat(pArea->m_rcArea.top);
			rc.right = TileToFloat(pArea->m_rcArea.right);
			rc.bottom = TileToFloat(pArea->m_rcArea.bottom);

			if(!PtInRect(&rc,pt))
				continue;

			//��������߼�ƥ������,zone��updateͨ�����ýű�������,�ͻ������û��Ҳ��check zone������
			if((pArea->m_strEnterScript.empty()&&pArea->m_strLeaveScript.empty())
				||(strcmp(pArea->m_strEnterScript.c_str(),"NA") == 0&&strcmp(pArea->m_strLeaveScript.c_str(),"NA") == 0))
				continue;

			if(MapConfig::MapData::EPKM_None_PK != pArea->m_nPKMode)
			{
				pkMode = pArea->m_nPKMode;
			}
			break;
		}
	}

	switch (pkMode)
	{
	case MapConfig::MapData::EPKM_UnAllow_PK: //��ȫ����
		{ return false; }
		break;
	case MapConfig::MapData::EPKM_Critical_PK:
		{

			if ( pSrcPlayer->IsInOneTeam() && pTargetPlayer->IsInOneTeam() )
			{
				if ( pSrcPlayer->GetTeamId() == pTargetPlayer->GetTeamId() ) //ͬһ���鲻�ܽ���pk
				{ return false; }
			}

			if ( pSrcPlayer->GetPKType() == PKMode_Critical ) //ֻ���ǿ�ģʽpk
			{ return true; }
		}
		break;
	case MapConfig::MapData::EPKM_Allow_PK:
		{
			if ( pSrcPlayer->IsInOneTeam() && pTargetPlayer->IsInOneTeam() )
			{
				if ( pSrcPlayer->GetTeamId() == pTargetPlayer->GetTeamId() ) //ͬһ���鲻�ܽ���pk
				{ return false; }
			}

			// �ж��Լ���ģʽ
			switch ( pSrcPlayer->GetPKType() )   
			{
			case PKMode_Normal:     // ��ͨģʽ���������ģʽ��ҿ��Խ��й���
				{
					if (pTargetPlayer->GetPKType() == PKMode_Critical)
					{ return true; }
				}
				break;
			case PKMode_Guild:
				{
					if(!pTargetPlayer->HasGuild() || !pSrcPlayer->HasGuild()) //û�й�������pk
						return true;

					return pTargetPlayer->GetGuildId() != pSrcPlayer->GetGuildId();  //��ͬ������Խ���pk


				}
				break;
			case PKMode_Fight:      // ���ڿ���PKģʽ����ҺͿ�״̬����Ҷ����Խ��й���
				{
					/*if (pTarget->GetPKMode() == PKMode_Normal)
					{ return false; }*/
					return true;
				}
				break;
			case PKMode_AttackFight:
				{
					return true;
				}
				break;
			case PKMode_AttackGuild:
				{

					if(!pTargetPlayer->HasGuild() || !pSrcPlayer->HasGuild()) //û�й�������pk
						return true;

					return pTargetPlayer->GetGuildId() != pSrcPlayer->GetGuildId();  //��ͬ������Խ���pk

				}
				break;
			case PKMode_Critical:   // ��ģʽ
				{ return true; }
				break;
			}
		}
		break;
	case MapConfig::MapData::EPKM_Normal_PK:
		{
			if ( pSrcPlayer->IsInOneTeam() && pTargetPlayer->IsInOneTeam() )
			{
				if ( pSrcPlayer->GetTeamId() == pTargetPlayer->GetTeamId() ) //ͬһ���鲻�ܽ���pk
				{ return false; }
			}

			if (  pSrcPlayer->GetRealCountry() != pTargetPlayer->GetRealCountry() )  
			{ return true; }    // ����ͬһ���ҵĿ��Թ���

			// �ж��Լ���ģʽ
			switch ( pSrcPlayer->GetPKType() )   
			{
			case PKMode_Normal:     // ��ͨģʽ���������ģʽ��ҿ��Խ��й���
				{
					if (pTargetPlayer->GetPKType() == PKMode_Critical)
					{ return true; }
				}
				break;
			case PKMode_Guild:
				{
					if(!pTargetPlayer->HasGuild() || !pSrcPlayer->HasGuild()) //û�й�������pk
						return true;

					return pTargetPlayer->GetGuildId() != pSrcPlayer->GetGuildId();  //��ͬ������Խ���pk
				}
				break;
			case PKMode_Fight:      // ���ڿ���PKģʽ����ҺͿ�״̬����Ҷ����Խ��й���
				{
					/* if (pTarget->GetPKMode() == PKMode_Normal)
					{ return false; }*/
					return true;
				}
				break;
			case PKMode_AttackFight:
				{
					return true;
				}
				break;
			case PKMode_AttackGuild:
				{
					if(!pTargetPlayer->HasGuild() || !pSrcPlayer->HasGuild()) //û�й�������pk
						return true;

					return pTargetPlayer->GetGuildId() != pSrcPlayer->GetGuildId();  //��ͬ������Խ���pk
				}
				break;
			case PKMode_Critical:   // ��ģʽ
				{ return true; }
				break;
			}
		}
		break;
	case MapConfig::MapData::EPKM_Group_PK:         // ��Ӫս��
		{ /*return pSrcPlayer->GetFightCamp() != pTargetPlayer->GetFightCamp() ;*/ 
			return true;
		}
		break;
	case MapConfig::MapData::EPKM_Guild_PK:         // ����ս��
		{	
			if(!pTargetPlayer->HasGuild() || !pSrcPlayer->HasGuild()) //û�й�������pk
				return false;

			return pTargetPlayer->GetGuildId() != pSrcPlayer->GetGuildId();  //��ͬ������Խ���pk

		}
		break;
	case MapConfig::MapData::EPKM_WorldBattle_PK:
		{
			//�ж�2���Ƿ����Pk 
			if(thePlayerRole.GetWorldBattleCountryID() == CountryDefine::Country_Init)//�͹���� ������Pk��ͼ ��BOSS
				return false;
			else
			{
				if(pSrcPlayer->GetRealCountry() == thePlayerRole.GetWorldBattleCountryID())
				{
					//������
					return pTargetPlayer->GetRealCountry() != pSrcPlayer->GetRealCountry();
				}
				else
				{
					if(pTargetPlayer->GetRealCountry() == thePlayerRole.GetWorldBattleCountryID())
						return true;
					else
						return false;
				}
			}
		}
	case MapConfig::MapData::EPKM_Free_PK:
		{ return true; }
		break;
	case MapConfig::MapData::EPKM_Team_PK:          // ����ս��
		{ 


			if ( pSrcPlayer->GetTeamId() != pTargetPlayer->GetTeamId() ) //ͬһ���鲻�ܽ���pk
			{ return true; }



		}
		break;
	case MapConfig::MapData::EPKM_Challenge_PK:     // ������̨
		{ return true; }
		break;
	case MapConfig::MapData::EPKM_Contend_PK:
		{

			if ( pSrcPlayer->IsInOneTeam() && pTargetPlayer->IsInOneTeam() )
			{
				if ( pSrcPlayer->GetTeamId() == pTargetPlayer->GetTeamId() ) //ͬһ���鲻�ܽ���pk
				{ return false; }
			}

		}
		break;
	}



	return false;
}

//----------------����ƶ�·����¼-----------------------------------------------------------
void LogMovePath(const char* szFormat, ...)
{
	guardfunc;
	char szDate[256] = {0};
	char szBuf[1024] = {0};
	char szLog[1024] = {0};

	//ת������
	va_list vl;
	va_start(vl, szFormat);
	int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
	va_end(vl);

	_snprintf(szLog, sizeof(szLog)-1, "%s\n", szBuf);

	char szFile[MAX_PATH] = {0};
	char szRange[256] = {0};
	DWORD dwLogID = g_dwMovePathLogID;
	_mkdir("�ƶ�·����¼");
	_snprintf(szFile, sizeof(szFile)-1, "�ƶ�·����¼\\%s", szDate);
	_mkdir(szFile);
	_snprintf(szFile, sizeof(szFile)-1, "%s\\%d", szFile, dwLogID);
	_mkdir(szFile);
	_snprintf(szFile, sizeof(szFile)-1, "%s\\%s.pat", szFile, "RoleMovePath" );
	FILE* fLog = NULL;
	fLog = fopen(szFile, "at");
	if(fLog != NULL)
	{
		fwrite(szLog, strlen(szLog), 1, fLog);
		fclose(fLog);
	}
	unguard;
}
//---------------------------------------------------------------------------------------

//���Ƕ�ת����һ����ά������
void	GetAngleTo2D( float fangle, float* fdirx, float* fdiry )
{
	guardfunc;
	float fx = *fdirx;
	float fy = *fdiry;
	float fPosXOff;
	float fPosYOff;
	float fxtoy = tan(fangle);

	fangle = fmodf( fangle, D3DX_PI*2 );
	if( fxtoy == 0 )
	{
		fPosXOff = 1;
		fPosYOff = 0;
	}
	else
	{
		fPosXOff = sqrtf(1/(1+fxtoy*fxtoy));
		fPosYOff = fabs(fxtoy*fPosXOff);
	}

	if( ( fangle >= 0 && fangle <= D3DX_PI/2 ) || ( fangle >= -D3DX_PI*2 && fangle <= -D3DX_PI*3/2 ) )
	{
		fx = fPosXOff;
		fy = fPosYOff;
	}

	if( ( fangle >= D3DX_PI/2 && fangle <= D3DX_PI ) || ( fangle >= -D3DX_PI*3/2 && fangle <= -D3DX_PI ) )
	{
		fx = -fPosXOff;
		fy = fPosYOff;
	}
	if( ( fangle >= D3DX_PI && fangle <= D3DX_PI*3/2 ) || ( fangle >= -D3DX_PI && fangle <= -D3DX_PI/2 ) )
	{
		fx = -fPosXOff;
		fy = -fPosYOff;
	}
	if( ( fangle >= D3DX_PI*3/2 && fangle <= D3DX_PI*2 ) || ( fangle >= -D3DX_PI/2 && fangle <= 0 ) )
	{
		fx = fPosXOff;
		fy = -fPosYOff;
	}

	*fdirx = fx;
	*fdiry = fy;
	unguard;
}

void SOperation::Clear()
{
	guardfunc;
	dwType = eOpNothing;
	dwFlag = 0;
	//
	bAttackToDeadFlag = false;
	//
	dwOperBeginTime = 0;
	//
	target.stDst = -1;
	unguard;
}
//-------------------------------------------------------------------------------
//
void SkillRuntimeDesc::Reset()
{
	dwStartTime = 0;
	dwIntonateTime = 0;
	dwHoldTime = 0;
	dwCancelTime = 0;
	bCancelHasSent = FALSE;
	bMovePermit = TRUE;
	Start( SkillRuntimeDesc::eNone );

	vectorEffect.clear();
}

BOOL SkillRuntimeDesc::Cancel( DWORD dwTime )
{
	guardfunc;
	dwCancelTime = dwTime;
	bCancelHasSent = TRUE;
	bMovePermit = FALSE;

	return TRUE;
	unguard;
}
//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------
CPlayer::CPlayer()
:m_footPrint(NULL)
,m_bFoundPathCSInitialize(false)
,m_stTeamId(0)
, m_cTeamPosition(ETP_None)
{
	guardfunc;
	m_nTypeStatus = MonsterDefine::StatusNormal;
	m_bMorphInThread = false;
	m_pInstantSkill = 0;
	m_dwWithNPCActionTime = 0;
	m_nWithNPCActionID = 0;
	m_pNpcCoordInfo = 0;
	m_bNeedUpdateFiveElement = false;
	m_nTitleId = 0;
	m_dwReputation = 0;
	m_dwGlory = 0;
	m_dwCountryScore = 0;
	m_bPrivateShopOpen = false;
	m_nCollectionEffectID = -1;
	m_bCanPick = false;
	m_ucSitStatus = 0;	//���ڵ��ϵı�־
	m_ucSitInterrupt = 0;	// ���±���ϵı�־
	m_ucFightStatus = 1;	//ս��ģʽ
	m_ucSex = 0;			//�Ա�
	m_ucProfession = 0;	//ְҵ
	m_EffectID = -1;
	m_HeroKillTargetNum = 0;
	m_HeroKillHasChanged = false;

	char *_temp = "NULL";
	memset(m_EffectName,0,sizeof(m_EffectName));
	memcpy(m_EffectName,_temp,strlen(_temp));
	//
	m_ucToFightStatus = 1;//��Ҫ�л�����ս��״̬
	m_bCanInterruptIntonating = true;
	m_pChatPaoPao = NULL;
	m_pPrivateShopInfo = NULL;
	m_dwChatDialogBoxBornTime = 0;
	m_dwChatDialogLifeTime = CHAT_DIALOG_BOX_LIFE_LONG;
	//
	m_bOpenPrivateShop = false;
	m_listStatusEffects.clear();

	for( int i = 0; i < BodyStatusType_Max; i++ )
	{
		stBodyStatus[i].dwPreDamage = 0;
		stBodyStatus[i].dwStartTime = 0;
		stBodyStatus[i].iLevel = -1;
		stBodyStatus[i].nEffectID = -1;
		stBodyStatus[i].StatusID = -1;
		stBodyStatus[i].masterId = -1;
	}
	m_cFightStatus.CreateFromData(stBodyStatus, BodyStatusType_Max);

	m_bDead = false;
	m_bWillDie = false;
	m_bIsActivePlayer = true;
	//
	m_pAnim = NULL;
	m_pMountAnim = NULL;
	m_pMorphAnim = NULL;
	m_pAnimTaliman = NULL;
	m_bShowTaliman = false;
	m_nTalismanId = 0;

	//
	m_status.LinkPlayer(this);	
	Reset(); 
	m_sound.dwLastUpdate = HQ_TimeGetTime() + rand()%30000;
	m_sound.hSound = theCreatureSound.GetNull();
	SetShotEffectID( -1 );

	m_stMonsterType = -1;
	m_dwShowFlag = 0;
	m_dwFightFlag = 0;
	m_bPendingClearFightFlag = FALSE;
	m_dwFightChangeFlag = FALSE;
	m_dwFightChangeTime = 0;

	m_pWeaponSound = NULL;
	m_pArmourSound = "cloth";

	m_bMoving = FALSE;
	m_bLastFrameMoving = FALSE;
	sX = 0.0f;
	sY = 0.0f;

	m_bTwoHalfBody = FALSE;
	m_bFourFoot = FALSE;
	m_fSpeed = 0.0f;	

	m_nSpineBoneID = THEBONENOTEXISTINMEX2;
	m_nRightHandBoneID = THEBONENOTEXISTINMEX2;
	m_nLeftHandBoneID = THEBONENOTEXISTINMEX2;
	m_nBackBoneID = THEBONENOTEXISTINMEX2;

	m_bHangMoving = FALSE;
	m_dwStartHangMovingTime = 0;
	m_dwHangMovingTimeLength = 0;

	m_fBodySize = 1.0f;
	m_fBodyLengthSize = CHAR_DEFAULTBODYSIZE;
	m_fWeaponAttackRange = 0;

	m_vUncontrolMoveTargetPos = D3DXVECTOR3( 0, 0, 0 );
	m_bUncontrolMoving = FALSE;
	m_bUncontrolFlying = FALSE;

	m_ustWeaponAttackRange = 0;
	m_iCountry = 0;
	m_iRealCountry = 0;			//added by zhuomeng.hu		[9/9/2010]
	m_iCountryTitle = 0;		//added by zhuomeng.hu		[9/9/2010]
	m_iPortraitId = 0;          //added by ZhuoMeng.Hu		[9/19/2010]
	m_fUpperBodyDirCorrect = 0;

	m_iFamilyID = 0;
	m_iFamilyPos = 0;

	m_bNameMulted = false;
	m_tx = 0;
	m_ty = 0;
	m_tz = 0;

	m_distanceDelta = 0;
	m_distanceDeltaForDynamicLoad = 0;
	m_vCurDir = D3DXVECTOR3( 0,0,0 );

	m_vCurStatusColor = D3DXVECTOR3( 0,0,0 );
	m_vFinStatusColor = D3DXVECTOR3( 0,0,0 );

	m_fTerrainZ = 0;

	m_fUpperBodyRotLimit = D3DX_PI/6;

	m_stFaceIcoId = -1;

	m_dwDisplayAfterTime = 2000;

	m_pAttackInfo = NULL;

	m_fTargetUpperBodyDir = D3DX_PI;

	m_bRotateLowerBody = FALSE;
	m_bRotateLowerBodyStart = FALSE;
	m_dwRotateLowerBodyStartTime = 0;

	m_dwFightChCurrTime = 0;

	m_pCharEffectContainer = NULL;

	m_bMounting = FALSE;
	m_fDromeScaleCorrect = 1;
	m_fRiderScaleCorrect = 1;
	m_nMountBoneID = THEBONENOTEXISTINMEX2;
	m_nMountModelID = -1;
	m_nMountLevel = 0;

	m_bJumping = FALSE;
	m_shJumpingType = 0;
	m_fJumpingHeight = 0.0f;
	m_dwStartJumpingTime = 0;
	m_fStartJumpingTerrainZ = 0;
	m_fStartJumpingSpeed = g_fPlayerDefaultJumpingSpeed;
	m_fMaxStartJumpingSpeed = g_fPlayerDefaultJumpingSpeed;
	m_fJumpSpeed = 4.6f;
	m_bNeedDropBuf = FALSE;
	m_bPlayedDropAnim = FALSE;

	m_dwHitPointPlayTime = 0;
	m_dwPushHitPointTime = 0;
	m_bHitPointPlayOver = TRUE;
	m_bRunning = FALSE;
	m_bCountermarch = FALSE;
	m_bPlayedCoutermarchAnim = FALSE;
	ClearActionTarget();

	m_nNpcTipsType = CPlayerMgr::eNpcTips_None;
	m_nImageType = -1;

	m_dwStartStopMovingTime = 0;

	m_fCurRenderAlpha = 0.0f;
	m_fFinalRenderAlpha = 1.0f;

	m_bInFloor = FALSE;

	m_bCreateUpDataZ = FALSE;

	m_fDistanceToRole = 0;

	m_bInWater = FALSE;
	m_bIntonating = FALSE;
	m_pIntonateTarget = 0;
	m_dwIntonatingStartTime = 0;
	SetNeedRender();

	m_vCurNormal.x = 0;
	m_vCurNormal.y = 0;
	m_vCurNormal.z = 1;
	m_vTargetNormal.x = 0;
	m_vTargetNormal.y = 0;
	m_vTargetNormal.z = 1;

	m_dwSpecialIdleInterval = (rand() / (float) RAND_MAX) * 10000 + 2000;

	m_shCurMovingType = MsgPlayerMoving::eNotMoving;

	m_bAssaultMoving = FALSE;
	m_shAssaultTargetID = -1;

	m_bNeedToRemove = FALSE;
	m_dwStartRemoveTime = 0;
	m_vSaveXYGetZ = 0.0f;

	m_x = 0;
	m_y = 0;
	m_z = 0;

	m_fServerZ = WORLD_HEIGHT;

	m_bHavePet = FALSE;
	m_PetID = FALSE;
	m_bHaveMaster = FALSE;
	m_bMasterIsMe = FALSE;
	m_MasterID = -1;
	m_fDefaultFinalRenderAlpha = 1;
	m_bMaskPlayer = false;
	m_dwCharacterID = -1;
	m_dwDeadTime = 0;

	m_fCurRotationX = 0;
	m_fTargetRotationX = 0;

	MyTeamMember = FALSE;
	m_MapEffectId = -1;
	m_bDueler = FALSE;

	m_nDuelEffectId = -1;

	m_AdscriptionPlayerId = -1;
	m_AdscriptionGroupId = -1;
	m_bItemPlayedDropAnim = false;
	m_bAdscription_teamHeader = false;

	m_nCanPickEffectID = -1;

	m_bMorphing = false;
	m_nMorphMonsterID = -1;

	m_isFirstAttack = false;
	m_shPKKillValue = 0;
	m_shPKRightValue = 0;
	m_shPKType = PKMode_Normal;

	m_nIntonatingEffectID = -1;

	m_dwLastUpdateAnimTime = 0;
	m_bLoggingMovePath = false;

	m_bInstantMoving = false;

	ManipleID = 0;

	m_ShadowColor = 0xFFFFFFFF;

	m_fShowNameAphla = 1;

	m_nRippleEffectID = -1;
	m_nRippleEffectContainerID = -1;
	m_nBoatRippleEffectID = -1;
	m_nBoatRippleEffectContainerID = -1;
	m_dwRippleEffectOverTime = 0;
	m_fRippleEffectPlaySpeed = 1.0f;

	m_nWaterSideRippleEffectID = -1;				//ˮ����������ЧID
	m_nWaterSideRippleEffectContainerID = -1;		//ˮ�����������ID
	m_fWaterSideRippleEffectPlaySpeed = 1.0f;		//ˮ�������Ĳ����ٶ�
	m_dwWaterSideRippleEffectOverTime = 0;		//ˮ�������Ľ���ʱ��

	m_shBattleFlag = 0;
	m_bGuildIsCityMaster = false;

	m_nHairColorIndex = 1;

	m_dir = 0;
	m_fUpperBodyDir = 0;
	m_fLowerBodyDir = 0;
	m_tdir = 0;
	m_fTargetUpperBodyDir = 0;
	m_fTargetLowerBodyDir = 0;

	m_bHasRelive = false;

	m_shInfluence = -1;

	m_isShowHelmet = true;
	m_isShowSignature = true;

	m_isShowAecpratove = false;
	m_isShowHero     = false;

	m_startfeartime = HQ_TimeGetTime();

	m_vTargetPos = GetPos();

	m_currPathPointIndex = 0;
	m_bInSingleFloor = false;

	fontName_= 0;
	fontSpeName_ = 0;
	fontGuild_ = 0;
	fontPrivateShopName_ = 0;

	m_pHpPB3D = 0;
	m_pMpPB3D = 0;
	m_pFpPB3D = 0;

	m_dwStopMoveTime = HQ_TimeGetTime();
	m_dwStopJumpTime = HQ_TimeGetTime();

	m_dwDropEndTime = 0;
	m_bAutoRuning = false;
	m_bFightPose = FALSE;

	m_dwLastScabbardBeginTime = HQ_TimeGetTime();

	m_pkShadowDecal = NULL;
	m_LastRenderShadowDecal = FALSE;

	// point aoe
	m_bSelectAoePoint = false;
	m_bIsCurRandRun = FALSE;
	m_bIsCurStun = FALSE;
	m_bIsCurFreeze = FALSE;

	// fight point
	m_bUpdateExPowerEff = false;
	m_nExPower = 0;
	m_nFPTotalBall = 4;
	m_nFPTotal = 100;
	m_nFPCurrentBallCount = 0;
	m_nFightPowerEffectID = -1;
	m_nFightPowerEffectContainerID = -1;

	m_nBaseStarCount = 7;//7��
	m_nMinimalStar = 0xff;
	m_bUpdateFullStarEffect = false;
	m_nFullStarEffectID = -1;
	m_nFullStarEffectContainerID = -1;
	m_nFullStarEffectID2 = -1;
	m_nFullStarEffectContainerID2 = -1;
	m_ucLiftFlagStatus = 0;
	m_fDistanceToPickRay = 0;
	m_dwInstantMovingStartTime = 0;

	m_nOldChatDialogBoxX = 0;
	m_nOldChatDialogBoxY = 0;
	m_fOldPrivateShopX = 0;
	m_fOldPrivateShopY = 0;

	m_isPet = FALSE;

	m_vctAdvanceSkill.clear();
	m_vctAdvanceSkill.reserve(2);
	m_bMoveRateChange = FALSE;
	m_bForceTurnRole = FALSE;

	m_dwNextActionTime = 0;
	m_shNextActionId = 0;
	m_bNeedInitNpcAction = FALSE;

	memset( m_equipitemSeekEquip, 0, sizeof( SCharItem ) * EEquipPartType_MaxEquitPart);
	m_fPlayerScale = 1.f;
#ifdef NEW_PLAYER_LOAD
	m_bModelLoaded = FALSE;
	m_bPrivateShop = FALSE;
#endif

	SetGuildOffer(0);

	m_fPetAdjustPosCD = 0;
	m_szTitleTargetName.clear();
	m_nInfluence = enumBattleInfluence_Max; //Ĭ������Ӫ

	m_nActionFluence = enumBattleInfluence_Max;        
	m_bUpdateFluence = false;

	m_bHasUpdateAnim = false;
	m_bNpcGetBodySize = false;

	m_dwLastRenderTime = 0;
	m_bHide = false;

	m_dwElapseMonsterActionTime = 0;
	m_shCurrMonsterActionId = 0;
	m_nZoneIndex = 0;
	m_bMonsterActioning = false;

	m_bFirstOnline = false;

	m_RefreshPathDirction = false;
	m_bCarrier = false;
	m_nCarrierID = -1;
	m_nCarrierDriver = -1;
	m_bIsOthersPet = false;
	m_bAutoDismount = true;

	m_dwNpcActionTime = 0;
	m_act.anim.strType.clear();
	m_act.talk.nStringId = 0;
	m_IsSearch = true;
	m_dwSearchCD = 0;

	m_bShowPetEffect = false;
	m_strPetEffect.clear();

	m_eState = eAction_None;
	m_HitBackDir = D3DXVECTOR3(0,0,0);   //���˷���

	m_fTargetZValue  = 0;
	m_bStartZMoving = false;
	m_bHigh = false;
	m_bInElevator = false;

	m_nDefAvaterIndex = 0;
	m_nNpcId = 0;

	m_dwNpcBeginTime = 0;
	m_bBeginNpcShow = false;   //�Ƿ�ʼNPC��ʾ����

	m_nMountOperaType = 0;
	m_bPlayDropAnim = true;
	mHeroID = INVALID_HERO_ID;
	source_faceid = -1;
	source_hairid = -1;

	mIsCanRide = false;
	mIsYabiaoState = false;
	mBiaoCheScale = 0.0;
	m_isOfflineStall = false;

	m_bIsDuel = false;
	m_EffectCharSkillID = -1;
	//m_dwMapID = INVALID_MAP_ID;
	//m_PrevPosition = D3DXVECTOR3(0,0,0);
	//m_bIsInTPHJ = false;

	m_isShowRankTitle = true;
	m_shRankTitleId = -1;

	unguard;
}

CPlayer::~CPlayer()
{
	guardfunc;
	MonsterStatusMgr::Instance()->ReleasePlayer(m_stID);
	IEffect *pEffect = GetEffectMgr()->GetEffect( m_MapEffectId );
	if( pEffect )
	{
		pEffect->SetDead();
		GetEffectMgr()->ReleaseEffect(m_MapEffectId);
		m_MapEffectId = -1;
	}

	pEffect = GetEffectMgr()->GetEffect( m_nDuelEffectId );
	if( pEffect )
	{
		pEffect->SetDead();
		GetEffectMgr()->ReleaseEffect(m_nDuelEffectId);
		m_nDuelEffectId = -1;
	}

	if( m_nRippleEffectID >= 0 )
	{
		pEffect = GetEffectMgr()->GetEffect( m_nRippleEffectID );
		if( pEffect )
		{
			pEffect->SetDead();
			GetEffectMgr()->ReleaseEffect(m_nRippleEffectID);
		}
		m_nRippleEffectID = -1;
	}
	if( m_nBoatRippleEffectID >= 0 )
	{
		pEffect = GetEffectMgr()->GetEffect( m_nBoatRippleEffectID );
		if( pEffect )
		{
			pEffect->SetDead();
			GetEffectMgr()->ReleaseEffect(m_nBoatRippleEffectID);
		}
		m_nBoatRippleEffectID = -1;
	}

	if( m_nWaterSideRippleEffectID >= 0 )
	{
		pEffect = GetEffectMgr()->GetEffect( m_nWaterSideRippleEffectID );
		if( pEffect )
		{
			pEffect->SetDead();
			GetEffectMgr()->ReleaseEffect(m_nWaterSideRippleEffectID);
		}
		m_nWaterSideRippleEffectID = -1;
	}

	if( m_nCollectionEffectID >= 0 )
	{
		pEffect = GetEffectMgr()->GetEffect( m_nCollectionEffectID );
		if( pEffect )
		{
			pEffect->SetDead();
			GetEffectMgr()->ReleaseEffect(m_nCollectionEffectID);
		}
		m_nCollectionEffectID = -1;
	}


	SAFE_DELETE( m_pChatPaoPao );
	SAFE_DELETE( m_pPrivateShopInfo );
	SAFE_DELETE( m_pkShadowDecal);
	SAFE_DELETE( m_footPrint);
	if (m_bFoundPathCSInitialize)
	{
		DeleteCriticalSection(&m_FoundPathCS);
	}
	unguard;
}

void CPlayer::SetPos( float x, float y, float z )
{
	guardfunc;
	m_x = x;
	m_y = y;
	if (IsUncontrolFlying())
	{
		m_z = z;
		return;
	}
	//m_z = z;
	if( abs(z) >= 0.0001f )
		m_z = z;
	else
	{
		m_z = 4000.0f;
	}
	INT nCmp = m_z;
	if( nCmp > WORLD_HEIGHT || nCmp < -WORLD_HEIGHT )
	{
		m_z = WORLD_HEIGHT;
	}

	m_ptLoc.x = (m_x-MAPTILESIZE/2)/MAPTILESIZE+1;
	m_ptLoc.y = (m_y-MAPTILESIZE/2)/MAPTILESIZE+1;
	unguard;
}

void CPlayer::ReSetPos( float fx, float fy, float fz )
{
	guardfunc;
	m_x = fx;
	m_y = fy;
	if (IsUncontrolFlying())
	{
		m_z = fz;
		return;
	}

	if( abs(fz) >= 0.0001f )
		m_z = fz;
	else
	{
		m_z = 4000.0f;
	}
	INT nCmp = m_z;
	if( nCmp > WORLD_HEIGHT || nCmp < -WORLD_HEIGHT )
	{
		m_z = WORLD_HEIGHT;
	}

	DWORD dwLoadFlags = 0;

	// �����ӵ����������m_z��������Zֵ��ͬ
	bool bSetZ = false;
	if( IsEmbraceAnim() && m_nInteractionMasterPlayerID != -1 )
	{
		CPlayer* pMasterPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nInteractionMasterPlayerID);
		if( pMasterPlayer )
		{
			m_z = pMasterPlayer->GetPos().z;
			bSetZ = true;
		}
	}
	if( !bSetZ )
	{
		if( this == theHeroGame.GetPlayerMgr()->GetMe() ) 
		{
			m_z = GetZByXY( m_z + 80.0f*Config::m_fMdlSpaceScale, m_x, m_y, 0, &m_bInFloor, &dwLoadFlags, TRUE );
		}
		else
		{
			m_z = GetZByXY( m_z+ 80.0f*Config::m_fMdlSpaceScale,  m_x, m_y, 0, &m_bInFloor, &dwLoadFlags, FALSE );
		}
	}
	unguard;
}

void CPlayer::TurnCameraToPlayer( DWORD time )
{
	static DWORD dwLastTime;

	DWORD elapse = time - dwLastTime;

	dwLastTime = time;

	if ( elapse > 500 )
	{
		elapse = 500;
	}

	wsCamera* pCamera = getwsCamera();
	if ( pCamera )
	{
		float tmpDir = 0.0f;
		this->GetDir(&tmpDir);
		static float playerDir = 0.0f;
		if ( fabs( tmpDir - playerDir ) > 0.1f )
		{
			playerDir = tmpDir;
		}

		playerDir -= D3DX_PI / 2.0f;

		while( playerDir <= 0/*-1 * D3DX_PI * 2*/ )
		{
			playerDir += D3DX_PI * 2;
		}
		while( playerDir >= D3DX_PI * 2 )
		{
			playerDir -= D3DX_PI * 2;
		}

		float cameraDir = pCamera->GetCameraRotateX();
		while ( cameraDir <= 0 )
		{
			cameraDir += D3DX_PI * 2;
		}
		while( cameraDir >= D3DX_PI * 2 )
		{
			cameraDir -= D3DX_PI * 2;
		}

		if ( fabs( cameraDir - playerDir ) > 0.01f )
		{
			float diff = cameraDir - playerDir;
			if ( diff > 0 && diff < D3DX_PI  )
			{
				cameraDir -= elapse * 0.005f;
			}
			else if ( diff > D3DX_PI )
			{
				cameraDir += elapse * 0.005f;
			}
			else if ( diff < 0 && diff > -D3DX_PI )
			{
				cameraDir += elapse * 0.005f;
			}
			else if ( diff < -D3DX_PI )
			{
				cameraDir -= elapse * 0.005f;
			}

			if ( fabs(diff) < fabs(elapse * 0.005f) )
			{
				cameraDir = playerDir;
			}

			pCamera->SetCameraRotateX( cameraDir );

			//char tmpStr[256] = {0};
			//MeSprintf( tmpStr, sizeof(tmpStr), "playerDir:%f camerDir:%f \n", playerDir, cameraDir );
			//OutputDebugStr(tmpStr);
		}

		//if ( fabs( playerDir - pCamera->GetCameraRotateX() ) > 0.00001f )
		//{
		//pCamera->SetCameraRotateXCorrect( playerDir - pCamera->GetCameraRotateX() );
		//pCamera->SetCameraRotateX( playerDir );
		//pCamera->SetReturnTheCamera( TRUE );
		//}
	}
}

BOOL CPlayer::NeedVerifyPos( D3DXVECTOR3 vPos, float fVerifyRange /* = 6.18f  */)
{
	guardfunc;
	vPos.x -= m_x;
	vPos.y -= m_y;
	vPos.z = 0;
	float fLength = D3DXVec3Length( &vPos );

	if( fLength > fVerifyRange )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	unguard;
}

void CPlayer::SetDir( float dir )
{
	guardfunc;
	float fDir = dir;
	fDir = fmodf( fDir, D3DX_PI*2 );
	if( fDir < 0 )
	{
		fDir += D3DX_PI*2;
	}

	m_tdir = fDir;
	unguard;
}

void CPlayer::SetCurDir( float dir )
{
	guardfunc;
	float fDir = dir;
	fDir = fmodf( fDir, D3DX_PI*2 );
	if( fDir < 0 )
	{
		fDir += D3DX_PI*2;
	}
	m_dir = fDir;
	unguard;
}

void CPlayer::SetUpperDir( float dir )
{
	guardfunc;
	float fDir = dir;
	fDir = fmodf( fDir, D3DX_PI*2 );
	if( fDir < 0 )
	{
		fDir += D3DX_PI*2;
	}
	m_fTargetUpperBodyDir = fDir;
	unguard;
}

void CPlayer::SetCurUpperDir( float dir )
{
	guardfunc;
	float fDir = dir;
	fDir = fmodf( fDir, D3DX_PI*2 );
	if( fDir < 0 )
	{
		fDir += D3DX_PI*2;
	}
	m_fUpperBodyDir = fDir;
	unguard;
}

void CPlayer::SetLowerDir( float dir )
{
	guardfunc;
	float fDir = dir;
	fDir = fmodf( fDir, D3DX_PI*2 );
	if( fDir < 0 )
	{
		fDir += D3DX_PI*2;
	}
	m_fTargetLowerBodyDir = fDir;
	unguard;
}

void CPlayer::SetCurLowerDir( float dir )
{
	guardfunc;
	float fDir = dir;
	fDir = fmodf( fDir, D3DX_PI*2 );
	if( fDir < 0 )
	{
		fDir += D3DX_PI*2;
	}
	m_fLowerBodyDir = fDir;
	unguard;
}

void CPlayer::SetDirInt( int nDir )
{
	guardfunc;
	m_iDir = nDir;
	int nDegree = 0;
	switch( nDir )
	{
	case DIR_0:
		nDegree = 0;
		break;
	case DIR_45:
		nDegree = 45;
		break;
	case DIR_90:
		nDegree = 90;
		break;
	case DIR_135:
		nDegree = 135;
		break;
	case DIR_180:
		nDegree = 180;
		break;
	case DIR_225:
		nDegree = 225;
		break;
	case DIR_270:
		nDegree = 270;
		break;
	case DIR_315:
		nDegree = 315;
		break;
	}
	nDegree = 360-nDegree;
	m_tdir = nDegree*3.1415926f/180;
	m_dir = m_tdir;
	unguard;
}

void CPlayer::GetPos( float* x, float* y, float* z )
{
	guardfunc;
	if (x)
	{
		*x = m_x;
	}
	if (y)
	{
		*y = m_y;
	}
	if (z)
	{
		*z = m_z;
	}
	unguard;
}

void CPlayer::GetDir( float* dir )
{
	guardfunc;
	*dir = D3DX_PI * 2 - m_dir;
	unguard;
}

void CPlayer::SetGuildName( const char* pszName )
{
	guardfunc;
	if ( !pszName )
	{
		return;
	}
	memset( m_szGuildName, 0, sizeof(m_szGuildName) );
	strncpy( m_szGuildName, pszName, sizeof(m_szGuildName)-1 );
	unguard;
}

const char* CPlayer::GetOfficialTitle()
{
	guardfunc;
	if( m_iCountry <= country_none ||
		m_iCountry >= country_max )
		return "";
	if( m_byOfficialLevel > dr_MaxOfficialLevel )
	{
		assert( false && "player get official title error, level out of range" );
		return "";
	}
	COfficialMgr::Record* pRecord = g_officialMgr.GetRecord( m_byOfficialLevel );
	if( !pRecord )
	{
		assert( false && "player get official title error, record is null" );
		return "";
	}
	return pRecord->szOfficialTitle[m_iCountry];
	unguard;
}
void CPlayer::SetCharInfo( MsgAckCharInfo* pMsg )
{
	guardfunc;

	memcpy( &m_charSimpleInfo, pMsg, sizeof( MsgAckCharInfo ) ); 
	SetName( pMsg->szDisplayName );
	//SetGuildName( pMsg->szGuildName );
	//setGuildTitle( pMsg->shGuildTitle );
	//setGuildInfluence( pMsg->shGuildInfluence );
	//m_bGuildIsCityMaster = pMsg->bCityMaster;
	//SetHPInfo(m_charSimpleInfo.nHp, m_charSimpleInfo.nHpMax);
	//SetLevel(m_charSimpleInfo.stLevel);
	//SetFightStatus(m_charSimpleInfo.m_ucFightStatus);//ս��ģʽ
	//SetToFightStatus(m_charSimpleInfo.m_ucFightStatus);//ս��ģʽ
	//SetSex(m_charSimpleInfo.m_ucSex);//�Ա�
	//SetProfession(m_charSimpleInfo.m_ucProfession);//ְҵ

	if( IsPlayer() )
	{
		//SetGuildIconCRC(pMsg->stChar,pMsg->szGuildName,pMsg->ulCRCCode);
		if( m_pAnim )
			m_pAnim->UpdateHardItem( HasFightFlag( eFighting ), &m_equips );
	}
	else if ( IsNpc() && GetName() )
	{
		const NpcCoordInfo* info = NpcCoord::getInstance()->getNpcCoordInCurrTile(GetNpcID());
		if (info)
		{
			SetTitle(info->_title);
			SetBodySize(info->_scale);
			m_bNpcGetBodySize = true;
		}
	}
	unguard;
}


int CPlayer::AutoCS( const char* pszSkin /* = NULL  */, BOOL bForceLoad /*= FALSE*/ )
{
	guardfunc;
	if( m_pAnim || m_pMountAnim || m_pMorphAnim || m_pAnimTaliman)
		DestroyCS();

#ifdef NEW_PLAYER_LOAD
	//[���ģ�ͼ��ػ���]
	// ������Լ����򲻴�����������
	if( IsPlayer() && !IsRole() && !bForceLoad )	
	{
		m_pAnim = NULL;
		return 0;
	}
	m_bModelLoaded = TRUE;
#endif

	BOOL ok = FALSE;
	{	
		if( !m_pAnim )
		{
			m_pAnim = MeNew CPlayerAnim;
		}
		m_pAnim->SetPlayer( this );
	}

	bool validateMD5 = Md5Manager::Instance().IsMD5Validate();
	Md5Manager::Instance().EnableMD5Validate( false );


	//���ݲ�ͬ��npc���ͣ�ʹ�ò�ͬ�Ķ�ȡ����
	char szCharType[256];
	switch( m_stCharType )
	{
	case Object_Player:
		ok = TRUE;
		m_pAnim->NeedInitUpperBodyAndLowerBody();
		m_pAnim->SetChangeAllEquipComplete( FALSE );
		ChangeSkeletonAndEquipAllItem( HasFightFlag(eFighting) );
		m_pAnim->UpdateHardItem(HasFightFlag(eFighting), &m_equips );
		strcpy( szCharType, "player" );

		if( m_pAnim->GetMex() )
		{
			m_nSpineBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine1" );
			m_nRightHandBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 R Finger11" );
			m_nLeftHandBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 L Finger11" );
			m_nBackBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine2" );
		}
		else
		{
			m_nSpineBoneID = MEX2NOTLOADINGCOMPLETE;
			m_nRightHandBoneID = MEX2NOTLOADINGCOMPLETE;
			m_nLeftHandBoneID = MEX2NOTLOADINGCOMPLETE;
			m_nBackBoneID = MEX2NOTLOADINGCOMPLETE;
		}

		if( !m_pMountAnim )
		{
			m_pMountAnim = MeNew CPlayerAnim;
		}
		m_pMountAnim->SetPlayer( this );

		if( !m_pMorphAnim )
		{
			m_pMorphAnim = MeNew CPlayerAnim;
		}
		m_pMorphAnim->SetPlayer( this );

		if( m_bMorphing )
		{
#ifdef NEW_PLAYER_LOAD
			if( bForceLoad )
				MorphMonster( m_nMorphMonsterID, m_bPrivateShop );
			else
#endif
				MorphMonster( m_nMorphMonsterID );
		}

		if( m_bMounting )
		{
			MountMonster( m_nMountModelID, m_nMountLevel );
		}

		//װ������
		if(m_nTalismanId != 0)
			EquipTalismanById(m_nTalismanId);
		break;
	case Object_Item:  
		if( m_nModelId !=-1 )
			ok = m_pAnim->MyChangeModel( m_nModelId, TRUE ,NULL);

		strcpy( szCharType, "item" );
		break;
	case Object_Npc:
		{
			m_pAnim->NeedInitUpperBodyAndLowerBody();
			if( !m_pMountAnim )
			{
				m_pMountAnim = MeNew CPlayerAnim;
			}
			m_pMountAnim->SetPlayer( this );

			ok = m_pAnim->MyChangeModel( m_nModelId, TRUE, pszSkin );
			strcpy( szCharType, "npc" );
		}
		break;
	case Object_Effect:
		if( m_nModelId == -1 )
		{
			// 			int nNullModelID = GetMexResMgr()->AddExternalFile( "data\\null.mex2" );
			// 			ok = m_pAnim->ChangeModel( nNullModelID );
			ok = m_pAnim->MyChangeModel( -1 ,TRUE,NULL);
		}
		else 
			ok = m_pAnim->MyChangeModel( m_nModelId ,TRUE,NULL);

		strcpy( szCharType, "effect" );
		break;
	case Object_Monster:
		{
			if( m_nModelId !=-1 )
			{
				if( m_bTwoHalfBody )
				{
					m_pAnim->NeedInitUpperBodyAndLowerBody();
				}
				ok = m_pAnim->MyChangeModel( m_nModelId, TRUE, pszSkin );
			}

			if( m_pAnim->GetMex() )
			{
				m_nSpineBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine1" );
				m_nRightHandBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 R Hand" );
				m_nLeftHandBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 L Hand");
			}
			else
			{
				m_nSpineBoneID = MEX2NOTLOADINGCOMPLETE;
				m_nRightHandBoneID = MEX2NOTLOADINGCOMPLETE;
				m_nLeftHandBoneID = MEX2NOTLOADINGCOMPLETE;
			}

			if( !m_pMorphAnim )
			{
				m_pMorphAnim = MeNew CPlayerAnim;
			}
			m_pMorphAnim->SetPlayer( this );

			strcpy( szCharType, "monster" );
		}
		break;
		// 	case Object_Building:
		// 		if( m_nModelId !=-1 )
		// 			ok = m_pAnim->MyChangeModel( m_nModelId ,TRUE,NULL);
		// 
		// 		strcpy( szCharType, "building" );
		// 		break;
	default:
		assert( false && "autocs chartype unknown" );
		ok = m_pAnim->MyChangeModel( m_nModelId ,TRUE,NULL);

		strcpy( szCharType, "unknown" );
		break;
	};
	SwitchActionStatus(CPlayerStatus::esk_Idle, CStatusTimer::NoLimitDelay );

	m_stFaceIcoId = (short)(Random()*16.0);
	Md5Manager::Instance().EnableMD5Validate( validateMD5 );

	return 0;
	unguard;
}

void CPlayer::UpdateEquip()
{
	guardfunc;
	ChangeSkeletonAndEquipAllItem( HasFightFlag(eFighting) );
	if( m_pAnim )
		m_pAnim->UpdateHardItem(HasFightFlag(eFighting), &m_equips );
	unguard;
}

void CPlayer::UpdateBones()
{
	switch( m_stCharType )
	{
	case Object_Player:
		{
			if( m_pAnim->GetMex() )
			{
				m_nSpineBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine1" );
				m_nRightHandBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 R Finger11" );
				m_nLeftHandBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 L Finger11" );
				m_nBackBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine2" );
			}
			else
			{
				m_nSpineBoneID = MEX2NOTLOADINGCOMPLETE;
				m_nRightHandBoneID = MEX2NOTLOADINGCOMPLETE;
				m_nLeftHandBoneID = MEX2NOTLOADINGCOMPLETE;
				m_nBackBoneID = MEX2NOTLOADINGCOMPLETE;
			}
		}
		break;
	case Object_Monster:
		{
			if( m_pAnim->GetMex() )
			{
				m_nSpineBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine1" );
				m_nRightHandBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 R Hand");
				m_nLeftHandBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 L Hand");
			}
			else
			{
				m_nSpineBoneID = MEX2NOTLOADINGCOMPLETE;
				m_nRightHandBoneID = MEX2NOTLOADINGCOMPLETE;
				m_nLeftHandBoneID = MEX2NOTLOADINGCOMPLETE;
			}
		}
		break;
	};
}

void CPlayer::DestroyCS()
{
	guardfunc;
	if( m_pAnim )
	{
		m_pAnim->Destroy();
		delete m_pAnim;
		m_pAnim = NULL;
	}

	if( m_pMountAnim )
	{
		m_pMountAnim->Destroy();
		delete m_pMountAnim;
		m_pMountAnim = NULL;
	}

	if( m_pMorphAnim )
	{
		m_pMorphAnim->Destroy();
		delete m_pMorphAnim;
		m_pMorphAnim = NULL;
	}

	if(m_pAnimTaliman)
	{
		m_pAnimTaliman->Destroy();
		delete m_pAnimTaliman;
		m_pAnimTaliman = NULL;
		m_nTalismanId = 0;
	}
#ifdef NEW_PLAYER_LOAD
	m_bModelLoaded = FALSE;
#endif
	unguard;
}

void CPlayer::ExcuteClearActionQueue( void )
{
	guardfunc;	
	//ֻ��������Ϣ	
	while( m_actionQueue.PopNextAction(m_NowAction))
	{		
		switch( m_NowAction.stType )
		{		
		case CActionQueue::A_ATTACKEX:
			{
				SAttackInfo *info = *((SAttackInfo**)m_NowAction.sData);
				//�����
				OnHitPoint( TRUE,GlobalControl::eNormal,info );
			}
			break;
		case CActionQueue::A_INTONATE:
			{
				IntonateInfo *info = (IntonateInfo*)m_NowAction.sData;
				if( info->pDst )
					info->pDst->Release();
			}
			break;
		case CActionQueue::A_DEATH:
			{
				assert( false );
			}
			break;
		}
	}
	unguard;
}

#define DestroyEffectContainer(id)	\
	if (id != -1)	\
{	\
	CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( id );	\
	if( pEffectContainer )	\
	pEffectContainer->FlagDestroy();	\
}

void CPlayer::Destroy()
{
	guardfunc;	

	if( IsItem() )
	{
		if( m_nCanPickEffectID >= 0 )
		{
			IEffect* pEffect = GetEffectMgr()->GetEffect( m_nCanPickEffectID );
			if( pEffect )
			{
				pEffect->SetDead();
			}
			pEffect = NULL;
		}
	}

	DestroyCS();

	ClearAllBodyStatusEff();

	if( m_pCharEffectContainer )
	{
		m_pCharEffectContainer->FlagDestroy();
	}
	m_pCharEffectContainer = NULL;

	// �����Ч
	for( int i = ItemElements_Metal; i < ItemElements_End; ++ i )

	{
		DestroyEffectContainer( m_FiveElementEffectIds[i].m_nEffectContainerId );
	}
	DestroyEffectContainer( m_nFullStarEffectContainerID );
	DestroyEffectContainer( m_nFullStarEffectContainerID2 );
	DestroyEffectContainer(m_nFightPowerEffectContainerID);
	DestroyEffectContainer(m_nWaterSideRippleEffectContainerID);
	DestroyEffectContainer(m_nRippleEffectContainerID);
	DestroyEffectContainer(m_nBoatRippleEffectContainerID);

	SAFE_DELETE( m_pChatPaoPao );
	SAFE_DELETE( m_pPrivateShopInfo );

	if (Font3DManager::Instance())
	{
		Font3DManager::Instance()->DestroyFont3D(fontName_);
		Font3DManager::Instance()->DestroyFont3D(fontSpeName_);
		Font3DManager::Instance()->DestroyFont3D(fontGuild_);
		Font3DManager::Instance()->DestroyFont3D(fontPrivateShopName_);		
	}
	m_bNameMulted = false;

	SAFE_DELETE( m_pHpPB3D );
	SAFE_DELETE( m_pMpPB3D );
	SAFE_DELETE( m_pFpPB3D );



	unguard;
}

void CPlayer::PlayCreatureSound( CCreatureSound::enumCreatureSound sound )
{
	guardfunc;
	char szWavFile[ MAX_PATH ];
	if( !theCreatureSound.GetSoundFile(m_sound.hSound,sound,szWavFile) )
		return;
	GSound.PlaySound( (szWavFile),false, &GetPos() );
	unguard;
}

void CPlayer::SetCreatureSound( char *szCreature )
{
	guardfunc;
	m_sound.hSound = theCreatureSound.GetCreatureSoundByName( szCreature );
	unguard;
}

void CPlayer::UpdateSound( void )
{
	guardfunc;
	if( g_dwLastFrameBeginTime > m_sound.dwLastUpdate )
	{
		if( g_dwLastFrameBeginTime - m_sound.dwLastUpdate < 60000 )
			return;
	}
	else
	{
		return;
	}

	if( Object_Monster != GetCharType() )
		return;

	m_sound.dwLastUpdate = g_dwLastFrameBeginTime + rand()%30000;
	//����һ������Ч
	PlayCreatureSound( CCreatureSound::CreatureSound_Idle );
	unguard;
}
void CPlayer::CastChainLightingEffect( CChainLightingEffect* pEffect, CPlayer* pTargetPlayer )
{
	guardfunc;
	if( !pTargetPlayer )
		return;
	if( m_pCharEffectContainer )
	{
		switch( pEffect->m_nBind )
		{
		case CChainLightingEffect::eBindLeftHand:
			pEffect->m_pMaster = m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_LeftHand );
			break;
		case CChainLightingEffect::eBindRightHand:
			pEffect->m_pMaster = m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_RightHand );
			break;
		case CChainLightingEffect::eBindBody:
			pEffect->m_pMaster = m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_Body );
			break;
		}
	}
	if( pTargetPlayer->m_pCharEffectContainer )
	{
		switch( pEffect->m_nTargetBind )
		{
		case CChainLightingEffect::eBindLeftHand:
			pEffect->m_pTarget = pTargetPlayer->m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_LeftHand );
			break;
		case CChainLightingEffect::eBindRightHand:
			pEffect->m_pTarget = pTargetPlayer->m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_RightHand );
			break;
		case CChainLightingEffect::eBindBody:
			pEffect->m_pTarget = pTargetPlayer->m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_Body );
			break;
		}
	}
	pEffect->Start();
	unguard;
}

void CPlayer::CastChainEffect( CChainEffect* pEffect,CPlayer* pTargetPlayer /*= NULL*/)
{
	if(!pEffect || !pTargetPlayer)
		return;

	//Ŀ�������İ���Update
	if( m_pCharEffectContainer )
	{
		switch( pEffect->m_nBind )
		{
		case CChainLightingEffect::eBindLeftHand:
			pEffect->m_pMaster = m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_LeftHand );
			break;
		case CChainLightingEffect::eBindRightHand:
			pEffect->m_pMaster = m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_RightHand );
			break;
		case CChainLightingEffect::eBindBody:
			pEffect->m_pMaster = m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_Body );
			break;
		}
	}

	pEffect->Start();
}

void CPlayer::CastMissileEffect( CMissileEffect* pEffect, CPlayer* pTargetPlayer )
{
	float h = 0;
	Box* pBBox = NULL;
	if( m_pAnim )
	{
		pBBox = m_pAnim->GetWorldBBox();
		if( abs(pBBox->v[4].z - pBBox->v[0].z) < 0.01 )
		{
			MeMatrix matTransform;
			m_pAnim->CalcTransformMatrix( &matTransform );
			m_pAnim->UpdateWorldBBox( &matTransform );
			pBBox = m_pAnim->GetWorldBBox();
		}
		h = ( pBBox->v[4].z - pBBox->v[0].z )*1.3f;
	}
#ifdef NEW_PLAYER_LOAD
	else
	{
		pBBox = &m_fakeWorldBBox;
		if( abs(pBBox->v[4].z - pBBox->v[0].z) < 0.01 )
		{
			UpdateFakeWorldBBox( m_x, m_y, m_z );
			pBBox = &m_fakeWorldBBox;
		}
		h = ( pBBox->v[4].z - pBBox->v[0].z )*1.3f;
	}
#endif

	D3DXVECTOR3 vMyPos = GetPos();
	vMyPos.z += h;

	D3DXVECTOR3 vTargetPos = vMyPos;
	if( pTargetPlayer )
	{
		vTargetPos = pTargetPlayer->GetPos();
		if( pTargetPlayer->m_pAnim )
		{
			pBBox = pTargetPlayer->m_pAnim->GetWorldBBox();
			if( abs(pBBox->v[4].z - pBBox->v[0].z) < 0.01 )
			{
				MeMatrix matTransform;
				pTargetPlayer->m_pAnim->CalcTransformMatrix( &matTransform );
				pTargetPlayer->m_pAnim->UpdateWorldBBox( &matTransform );
				pBBox = pTargetPlayer->m_pAnim->GetWorldBBox();
			}
			float h = ( pBBox->v[4].z - pBBox->v[0].z )*1.3f;
			vTargetPos.z += h;
		}
#ifdef NEW_PLAYER_LOAD
		else if( !pTargetPlayer->IsModelLoaded() )
		{
			pBBox = pTargetPlayer->GetWorldBBox();
			if( abs(pBBox->v[4].z - pBBox->v[0].z) < 0.01 )
			{
				pTargetPlayer->UpdateFakeWorldBBox( vTargetPos.x, vTargetPos.y, vTargetPos.z );
				pBBox = pTargetPlayer->GetWorldBBox();
			}
			float h = ( pBBox->v[4].z - pBBox->v[0].z )*1.3f;
			vTargetPos.z += h;
		}
#endif
	}

	pEffect->m_ShootStartSpace.vCenter = vMyPos;

	GameObjectId gcPlayerServerID = theHeroGame.GetPlayerMgr()->GetMouseTargetPlayerSeverID();
	pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByID( gcPlayerServerID );

	if( pTargetPlayer )
		pEffect->m_ShootTargetSpace.vCenter = vTargetPos;
	else 
		pEffect->m_ShootTargetSpace.vCenter = vMyPos;

	if( pTargetPlayer )
		pEffect->m_DropTargetSpace.vCenter = vTargetPos;
	else
		pEffect->m_DropTargetSpace.vCenter = vMyPos;

	pEffect->Start();
}

void CPlayer::CastHitFlashEffect( CHitFlashEffect* pEffect )
{
	guardfunc;
	pEffect->m_vPos = D3DXVECTOR3( m_x, m_y, m_z );
	if( pEffect->m_nAction == CHitFlashEffect::eActionFollow )
	{
		if( m_pCharEffectContainer )
		{
			IEffectHelper* pEffectHelper = m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_Body );
			if( pEffectHelper )
				pEffect->m_pMaster = pEffectHelper;
		}
	}
	pEffect->Start();

	unguard;
}
void CPlayer::CastModelEffect( CWSModelEffect* pEffect, CPlayer* pTargetPlayer /* = NULL */, int nSlot /* = 0  */)
{
	guardfunc;
	CastModelEffect(pEffect, m_pCharEffectContainer, pTargetPlayer, nSlot);
	unguard;
}

void CPlayer::CastModelEffect( CWSModelEffect* pEffect, CCharEffectContainer* pCharEffectContainer,
							  CPlayer* pTargetPlayer /* = NULL */, int nSlot /* = 0  */)
{
	guardfunc;
	if( !pEffect )
	{
		assert( false );
		return;
	}

	pEffect->m_dwBornTime = HQ_TimeGetTime();
	float fRadius = pEffect->m_fRadius;
	int nNum = pEffect->m_nNumInstance;

	for( int nInst = 0; nInst < nNum; nInst++ )
	{
		CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
		if( !pInstance )
		{
			assert( FALSE );
			return;
		}

		pInstance->dwBornTime = HQ_TimeGetTime() + pInstance->fDelay;

		// ������Σ�quoter�϶�����Ч������
		if( pCharEffectContainer )
		{
			pEffect->SetEffectQuoter( pCharEffectContainer );
		}

		switch( pInstance->nAction )
		{
		case CWSModelEffect::eActionFollow:
		case CWSModelEffect::eActionFollowPos:
			pInstance->vBornPos = 
				D3DXVECTOR3( m_x, m_y, m_z )+
				D3DXVECTOR3( fRadius*(-0.5f+Random()), fRadius*(-0.5f+Random()), 0 );

			pInstance->vPos = pInstance->vBornPos;
			pInstance->nTrackType = CWSModelEffect::eTrackTypeLine;
			pInstance->vTargetPos = GetPos();
			pInstance->fRot = m_dir + D3DX_PI/2;
			break;
			//add by yanli 2010-6-30
			//-------------------------------------------------------------------------------
		case CWSModelEffect::eActionFollowCamera: 
			//-------------------------------------------------------------------------------
		case CWSModelEffect::eActionStand:
			break;
		case CWSModelEffect::eActionTrace:
			{
				pInstance->vBornPos = 
					D3DXVECTOR3( m_x, m_y, m_z )+
					D3DXVECTOR3( fRadius*(-0.5f+Random()), fRadius*(-0.5f+Random()), 0 );

				pInstance->vPos = pInstance->vBornPos;
				pInstance->nTrackType = CWSModelEffect::eTrackTypeLine;
			}
			break;
		case CWSModelEffect::eActionPointToNpc:
			{
				pInstance->vBornPos = 
					D3DXVECTOR3( m_x, m_y, m_z ) +
					D3DXVECTOR3( fRadius*(-0.5f+Random()), fRadius*(-0.5f+Random()), 0 );

				pInstance->vPos = pInstance->vBornPos;
				pInstance->nTrackType = CWSModelEffect::eTrackTypeLine;
				pInstance->vTargetPos = GetPos();
				pInstance->fRot = m_dir + D3DX_PI/2;
			}
			break;
		case CWSModelEffect::eActionFollowPoint:
			{
				pInstance->vBornPos = 
					D3DXVECTOR3( m_x, m_y, m_z ) +
					D3DXVECTOR3( fRadius*(-0.5f+Random()), fRadius*(-0.5f+Random()), 0 );

				pInstance->vPos = pInstance->vBornPos;
				pInstance->nTrackType = CWSModelEffect::eTrackTypeLine;
				SAttackInfo* info = GetAttackInfo();
				CPlayer* pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByID( info->nTargetId );
				if( pTargetPlayer )
					pInstance->vTargetPos = pTargetPlayer->GetPos();
				pInstance->fRot = m_dir + D3DX_PI/2;
			}
			break;
		case CWSModelEffect::eActionFall:
			{
				pInstance->vTargetPos = GetPos();
				pInstance->vTargetPos += D3DXVECTOR3( 
					fRadius*(-0.5f+Random()), 
					fRadius*(-0.5f+Random()), 0 );
				pInstance->vBornPos = pInstance->vTargetPos+D3DXVECTOR3( 0, 0, pInstance->fFallHeight );
				pInstance->vPos = pInstance->vBornPos;
				pInstance->fGroundZ = m_z;
			}
			break;
		case CWSModelEffect::eActionSpray:
			{
				pInstance->vTargetPos.x = m_x;
				pInstance->vTargetPos.y = m_y;
				pInstance->vTargetPos.z = m_fTerrainZ;
				pInstance->vTargetPos += D3DXVECTOR3( fRadius*(-0.5f+Random()), fRadius*(-0.5f+Random()), 0 );
				pInstance->vBornPos = pInstance->vTargetPos+D3DXVECTOR3( 0, 0, pInstance->fFallHeight );
				pInstance->vPos = pInstance->vBornPos;
				pInstance->fGroundZ = m_z;
				pInstance->fRot = m_dir + D3DX_PI/2;
			}
			break;
		case CWSModelEffect::eActionFollowSpray:
			{
				pInstance->vTargetPos.x = m_x;
				pInstance->vTargetPos.y = m_y;
				pInstance->vTargetPos = GetPos();
				pInstance->vTargetPos.z = m_fTerrainZ;
				pInstance->vTargetPos += D3DXVECTOR3( fRadius*(-0.5f+Random()), fRadius*(-0.5f+Random()), 0 );
				pInstance->vBornPos = pInstance->vTargetPos+D3DXVECTOR3( 0, 0, pInstance->fFallHeight );
				pInstance->vPos = pInstance->vBornPos;
				pInstance->fGroundZ = m_z;
			}
			break;
		case CWSModelEffect::eActionSkillBarCollect:
			{
				pInstance->vBornPos = D3DXVECTOR3( m_x, m_y, m_z ) + D3DXVECTOR3( 2*(-0.5f+Random()), 2*(-0.5f+Random()), 0 );

				pInstance->vPos = pInstance->vBornPos;
				pInstance->fXOffset = 12*(-0.5f+Random());
				pInstance->fYOffset = 12*(-0.5f+Random());
				pInstance->fZOffset = 3*Random();

				pInstance->fFallHeight = 0.6f + 3.4f*Random();
				pInstance->fBornScale = pInstance->fScale;
			}
			break;
		case CWSModelEffect::eActionPointAoe:
			{
				SAttackInfo* pAttackInfo = GetAttackInfo();
				D3DXVECTOR3 vAoePos;
				if( pAttackInfo )
				{
					vAoePos.x = pAttackInfo->pos.x;
					vAoePos.y = pAttackInfo->pos.y;
					vAoePos.z = pAttackInfo->pos.z;
				}
				else
				{
					vAoePos = m_vPointAoePos;
				}

				pInstance->vTargetPos.x = vAoePos.x;
				pInstance->vTargetPos.y = vAoePos.y;
				pInstance->vTargetPos.z = vAoePos.z/*m_fTerrainZ*/;								
				pInstance->vPos = D3DXVECTOR3( vAoePos.x, vAoePos.y, vAoePos.z/*m_fTerrainZ*/ );
				pInstance->fGroundZ = m_z;
				pInstance->fRot = m_dir + D3DX_PI/2;
			}
			break;
		default:
			assert( false );
		}
		// ����Ч��
		if( pCharEffectContainer )
		{
			switch( pInstance->nBindWhere )
			{
			case eEffectBindPart_Body:
				pInstance->pMaster =
					pCharEffectContainer->GetEffectHelper( eEffectBindPart_Body );
				break;
			case eEffectBindPart_Head:
				{
					Box* pBBox = NULL;
					if( m_pAnim )
					{
						pBBox = m_pAnim->GetWorldBBox();
						if( abs(pBBox->v[4].z - pBBox->v[0].z) < 0.01 )
						{
							// ��ʱ����Ч���������ŵף������ȸ����°�Χ��
							MeMatrix matTransform;
							m_pAnim->CalcTransformMatrix( &matTransform );
							m_pAnim->UpdateWorldBBox( &matTransform );
							pBBox = m_pAnim->GetWorldBBox();
						}
					}
#ifdef NEW_PLAYER_LOAD
					else
					{
						pBBox = &m_fakeWorldBBox;
						if( abs(pBBox->v[4].z - pBBox->v[0].z) < 0.01 )
						{
							UpdateFakeWorldBBox( m_x, m_y, m_z );
							pBBox = &m_fakeWorldBBox;
						}
					}
#endif
					if( pBBox )
					{
						pInstance->pMaster = pCharEffectContainer->GetEffectHelper( eEffectBindPart_Head );
						if( m_bMounting )
						{
							pInstance->pMaster->SetPos( m_x, m_y, m_z + (pBBox->v[4].z - pBBox->v[0].z)*1.3f + 1.0f );
						}
						else
						{
							pInstance->pMaster->SetPos( m_x, m_y, m_z + (pBBox->v[4].z - pBBox->v[0].z)*1.3f);
						}
					}
				}
				break;
			case eEffectBindPart_RightHand:
				pInstance->pMaster =
					pCharEffectContainer->GetEffectHelper( eEffectBindPart_RightHand );
				break;
			case eEffectBindPart_LeftHand:
				pInstance->pMaster =
					pCharEffectContainer->GetEffectHelper( eEffectBindPart_LeftHand );
				break;
			case eEffectBindPart_Foot:
				pInstance->pMaster =
					pCharEffectContainer->GetEffectHelper( eEffectBindPart_Foot );
				break;
			case eEffectBindPart_Spray:
				pInstance->pMaster = 
					pCharEffectContainer->GetEffectHelper( eEffectBindPart_Spray );
				break;
			case eEffectBindPart_Back:
				pInstance->pMaster = 
					pCharEffectContainer->GetEffectHelper( eEffectBindPart_Back );
				break;
			}
		}

		if( pTargetPlayer )
		{
			if( pTargetPlayer->GetCharEffectContainer() )
			{
				pInstance->pTarget =
					pTargetPlayer->m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_Body );
			}
		}
		else
		{
			SAttackInfo* info = GetAttackInfo();
			if( info )
			{
				CPlayer* pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByID( info->nTargetId );
				if( pTargetPlayer && pTargetPlayer->GetCharEffectContainer() )
				{
					pInstance->pTarget =
						pTargetPlayer->m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_Body );
				}

			}
		}
	}

	if( pCharEffectContainer )
	{
		pCharEffectContainer->ApplyEffect( nSlot, pEffect->GetID() );
	}
	unguard;
}

//����нǴ�����
float CalcRotateAngleWithDir( float fdir, float ftdir )
{
	float fd = fdir;
	float ftd = ftdir;

	fd = fmodf( fd, D3DX_PI*2 );
	if( fd < 0 )
	{
		fd += D3DX_PI*2;
	}

	ftd = fmodf( ftd, D3DX_PI*2 );
	if( ftd < 0 )
	{
		ftd += D3DX_PI*2;
	}

	if( fd > ftd )
	{
		float foffset = fd - ftd;
		if( foffset > D3DX_PI )
		{
			return D3DX_PI*2 - foffset;
		}
		else
		{
			return -foffset;
		}
	}
	else
	{
		float foffset = ftd - fd;
		if( foffset > D3DX_PI )
		{
			return foffset - D3DX_PI*2;
		}
		else
		{
			return foffset;
		}
	}
	return 0;
}

//����н�
float CalcRotateAngle( float fdir, float ftdir )
{
	float fd = fdir;
	float ftd = ftdir;

	fd = fmodf( fd, D3DX_PI*2 );
	if( fd < 0 )
	{
		fd += D3DX_PI*2;
	}

	ftd = fmodf( ftd, D3DX_PI*2 );
	if( ftd < 0 )
	{
		ftd += D3DX_PI*2;
	}

	if( fd > ftd )
	{
		float foffset = fd - ftd;
		if( foffset > D3DX_PI )
		{
			return D3DX_PI*2 - foffset;
		}
		else
		{
			return foffset;
		}
	}
	else
	{
		float foffset = ftd - fd;
		if( foffset > D3DX_PI )
		{
			return D3DX_PI*2 - foffset;
		}
		else
		{
			return foffset;
		}
	}
	return 0;
}


//��ת����( ��ָ���Ƕ�����һ����������ת��Ŀ�귽��,�������ָ���ĽǶ��ڻᱻ����ָ���ĽǶ� )
//( ��fanglevelocity�Ľ����ʴ�fdir����ת��ftdir����, fdir��ftdir֮��ļнǳ���fmaxangle, fdir���������õ���ftdir��fmaxangle�Ƕȵ�λ�� )
void RotateBody( float* fdir, float* ftdir, float fanglevelocity, float fmaxangle )
{
	guardfunc;
	float fd = *fdir;
	float ftd = *ftdir;

	fd = fmodf( fd, D3DX_PI*2 );
	if( fd < 0 )
	{
		fd += D3DX_PI*2;
	}

	ftd = fmodf( ftd, D3DX_PI*2 );
	if( ftd < 0 )
	{
		ftd += D3DX_PI*2;
	}

	if( fd > ftd )
	{
		if( fd - ftd > D3DX_PI )
		{
			if( D3DX_PI*2 - ( fd - ftd ) < fmaxangle + ROTATECORRECT )
			{
				if( D3DX_PI*2 - ( fd - ftd ) < fanglevelocity )
				{
					fd = ftd;
				}
				else
				{
					fd += fanglevelocity;
				}
			}
			else
			{
				fd = ftd - fmaxangle;
			}
		}
		else
		{
			if( fd - ftd < fmaxangle + ROTATECORRECT )
			{
				if( fd - ftd < fanglevelocity )
				{
					fd = ftd;
				}
				else
				{
					fd -= fanglevelocity;
				}
			}
			else
			{
				fd = ftd + fmaxangle;
			}
		}
	}
	else
	{
		if( ftd - fd > D3DX_PI )
		{
			if( D3DX_PI*2 - ( ftd - fd ) < fmaxangle + ROTATECORRECT )
			{
				if( D3DX_PI*2 - ( ftd - fd ) < fanglevelocity )
				{
					fd = ftd;
				}
				else
				{
					fd -= fanglevelocity;
				}
			}
			else
			{
				fd = ftd + fmaxangle;
			}
		}
		else
		{
			if( ftd - fd < fmaxangle + ROTATECORRECT )
			{
				if( ftd - fd < fanglevelocity )
				{
					fd = ftd;
				}
				else
				{
					fd += fanglevelocity;
				}
			}
			else
			{
				fd = ftd - fmaxangle;
			}
		}
	}

	*fdir = fd;
	*ftdir = ftd;
	unguard;
}

void CPlayer::UpdateEffectHelper()
{
	guardfunc;
	UpdateEffectHelper(m_pCharEffectContainer);
	unguard;
}


void CPlayer::UpdateEffectHelper(CCharEffectContainer* pCharEffectContainer)
{
	guardfunc;

	if( pCharEffectContainer )
	{
		IEffectHelper* pEffectHelper = NULL;
		Box* pBBox = GetWorldBBox();

		/////////////////////eEffectBindPart_Body
		if( m_nSpineBoneID == MEX2NOTLOADINGCOMPLETE && m_pAnim && m_pAnim->GetMex() )
		{
			m_nSpineBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine1" );
		}

		if( m_nSpineBoneID < 0 )
		{
			pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_Body );
			if( pEffectHelper )
			{
				pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
				pEffectHelper->SetRot( m_fLowerBodyDir + D3DX_PI/2 );
				if( pBBox )
					pEffectHelper->SetPos( m_x, m_y, pBBox->v[0].z + (pBBox->v[4].z - pBBox->v[0].z)*0.6f );
				else
					pEffectHelper->SetPos( m_x, m_y, m_z + 1.f );	// �����������1.7����1.7*0.6=1.0
				pEffectHelper->SetTerrainZ( m_fTerrainZ );
			}
		}
		else
		{
			pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_Body );
			if( pEffectHelper && m_pAnim )
			{
				Vector vSpinePos = m_pAnim->GetBoneWorldPos( m_nSpineBoneID );
				pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
				pEffectHelper->SetRot( m_dir + D3DX_PI/2 );
				pEffectHelper->SetPos( vSpinePos.x, vSpinePos.y, vSpinePos.z );
				pEffectHelper->SetTerrainZ( m_fTerrainZ );
			}
		}

		/////////////////////eEffectBindPart_Head
		pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_Head );
		if( pEffectHelper )
		{
			pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
			pEffectHelper->SetRot( m_dir + D3DX_PI/2 );
			float fMountHeight = 0.f;
			if( m_bMounting )
			{
				fMountHeight = 1.f;
			}
			if( pBBox )
				pEffectHelper->SetPos( m_x, m_y, m_z + (pBBox->v[4].z - pBBox->v[0].z)*1.3f + fMountHeight );
			else
				pEffectHelper->SetPos( m_x, m_y, m_z + 2.2f + fMountHeight );	// ���������1.7����1.7*1.3=2.2
		}

		///////////////////eEffectBindPart_Foot
		pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_Foot );
		if( pEffectHelper )
		{
			pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
			pEffectHelper->SetRot( m_dir + D3DX_PI/2 );
			float fMountHeight = 0.f;
			if( m_bMounting )
			{
				fMountHeight = 1.f;
			}
			pEffectHelper->SetPos( m_x, m_y, m_z + fMountHeight );
		}

		//////////////////////////eEffectBindPart_Spray
		pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_Spray );
		if( pEffectHelper )
		{
			pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
			pEffectHelper->SetRot( m_dir + D3DX_PI/2 );
			pEffectHelper->SetPos( m_x, m_y, m_fTerrainZ );
			pEffectHelper->SetTerrainZ( m_fTerrainZ );
		}

		{
			guard(HandPos);
			////////////////////eEffectBindPart_RightHand
			if( m_nRightHandBoneID == MEX2NOTLOADINGCOMPLETE && m_pAnim && m_pAnim->GetMex() )
			{
				m_nRightHandBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 R Finger11" );
			}

			if( m_nRightHandBoneID < 0 )
			{
				pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_RightHand );
				if( pEffectHelper )
				{
					pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
					pEffectHelper->SetRot( m_fLowerBodyDir + D3DX_PI/2 );
					if( pBBox )
						pEffectHelper->SetPos( m_x, m_y, pBBox->v[0].z + (pBBox->v[4].z - pBBox->v[0].z)*0.6f );
					else
						pEffectHelper->SetPos( m_x, m_y, m_z + 1.f );
				}
			}
			else
			{
				pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_RightHand );
				if( pEffectHelper && m_pAnim )
				{
					pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
					Vector vRightHandPos = m_pAnim->GetBoneWorldPos( m_nRightHandBoneID );
					pEffectHelper->SetRot( m_dir + D3DX_PI/2 );
					pEffectHelper->SetPos( vRightHandPos.x, vRightHandPos.y, vRightHandPos.z );
				}
			}

			////////////////////eEffectBindPart_LeftHand
			if( m_nLeftHandBoneID == MEX2NOTLOADINGCOMPLETE && m_pAnim && m_pAnim->GetMex() )
			{
				m_nLeftHandBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 L Finger11" );
			}

			if( m_nLeftHandBoneID < 0 )
			{
				pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_LeftHand );
				if( pEffectHelper )
				{
					pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
					pEffectHelper->SetRot( m_fLowerBodyDir + D3DX_PI/2 );
					if( pBBox )
						pEffectHelper->SetPos( m_x, m_y, pBBox->v[0].z + (pBBox->v[4].z - pBBox->v[0].z)*0.6f );
					else
						pEffectHelper->SetPos( m_x, m_y, m_z + 1.f );
				}
			}
			else
			{
				pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_LeftHand );
				if( pEffectHelper && m_pAnim )
				{
					pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
					Vector vLeftHandPos = m_pAnim->GetBoneWorldPos( m_nLeftHandBoneID );
					pEffectHelper->SetRot( m_dir + D3DX_PI/2 );
					pEffectHelper->SetPos( vLeftHandPos.x, vLeftHandPos.y, vLeftHandPos.z );
				}
			}
			unguard;

			guard(FlyBonePos);
			/////////////////////eEffectBindPart_Back
			if( m_nBackBoneID == MEX2NOTLOADINGCOMPLETE && m_pAnim && m_pAnim->GetMex() )
			{
				m_nBackBoneID = m_pAnim->GetMex()->GetSkeleton()->FindBone( "Bip01 Spine2" );
			}

			if( m_nBackBoneID < 0 )
			{
				pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_Back );
				if( pEffectHelper )
				{
					pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
					pEffectHelper->SetRot( m_fLowerBodyDir + D3DX_PI/2 );
					if( pBBox )
						pEffectHelper->SetPos( m_x, m_y, pBBox->v[0].z + (pBBox->v[4].z - pBBox->v[0].z)*0.6f );
					else
						pEffectHelper->SetPos( m_x, m_y, m_z + 1.f );
				}
			}
			else
			{
				pEffectHelper = pCharEffectContainer->GetEffectHelper( eEffectBindPart_Back );
				if( pEffectHelper && m_pAnim )
				{
					pEffectHelper->SetFinalRenderAlpha( m_fFinalRenderAlpha );
					Vector vFlyBonePos = m_pAnim->GetBoneWorldPos( m_nBackBoneID );
					pEffectHelper->SetRot( m_fUpperBodyDir + D3DX_PI/2 );
					pEffectHelper->SetPos( vFlyBonePos.x, vFlyBonePos.y, vFlyBonePos.z );
				}
			}
			unguard;
		}
		pEffectHelper = NULL;
		pBBox = NULL;
	}	
	unguard;
}

void CPlayer::SmoothFrameProcess()
{
	guardfunc;
	if( m_bRole )
	{
		int nOffFrame = g_dwLastFrameCostTime - g_dwSmoothFrame;

		if( nOffFrame > 0 )
		{
			if( nOffFrame > 6 )
			{
				g_dwSmoothFrame += nOffFrame/2;
			}
			else
			{
				g_dwSmoothFrame++;
			}
		}

		if( nOffFrame < 0 )
		{
			if( nOffFrame < -6 )
			{
				g_dwSmoothFrame += nOffFrame/2;
			}
			else
			{
				g_dwSmoothFrame--;
			}
		}
	}
	unguard;
}

static float HideSkillAlpha = 0.51f;

void CPlayer::HideSkillProcess()
{
	guardfunc;
	if( m_cFightStatus.IsHide() )
	{
		if( m_bRole )
		{
			SetFinalRenderAlpha( HideSkillAlpha );
		}
		else
		{
			if( theHeroGame.GetPlayerMgr() && GetID() == theHeroGame.GetPlayerMgr()->GetLockPlayerID() )
			{
				//s_CUI_ID_FRAME_NpcChatDialogBox.SetNpc(-1);
				s_CUI_NpcTaskDialogBox.SetNpc(-1);
				theHeroGame.GetPlayerMgr()->SetLockNpc(-1);
			}
			SetFinalRenderAlpha( 0 );
		}
		if (IsPlayer()) //NPC ���ع���bug++ ��һ���ж�
		{   
			if (!IsHide())
			{
				if(!m_bRole)
				{
					SetHide(true);
				}else
				{
					HideOrShowPlayerEffect(false); //������Ч  ��ֹloadmap��ʱ�� ��
					//���յ�ת����ͼ����˶��̵߳����ݼ������� 
					//������ݼ��ز��ɹ�����������������ڷ��ͽ�����Ұ����Ϣ���Ż�ȥ����
				}

			}
		}
	}
	else
	{
		SetFinalRenderAlpha( m_fDefaultFinalRenderAlpha );
		if (IsPlayer())  //NPC ���ع���bug++ ��һ���ж�
		{
			if (IsHide())
			{			
				if(!m_bRole)
				{
					SetHide(false);
				}else
				{
					HideOrShowPlayerEffect(true); //��ʾ��Ч
				}
			}
		}
	}
	unguard;
}


void CPlayer::MoveProcess()
{
	guardfunc;
	if( m_bRole || IsMonster() )
	{
		if ( m_bAssaultMoving || m_cFightStatus.IsCanMove() )
		{
			if( m_bIsCurStun && m_cFightStatus.GetCurStatusAnim() != BuffStatusManager::eStatusAnim_Stun )
			{
				if( !m_bMoving && !m_bJumping && !m_bCountermarch )
					SwitchIdleAnim();
				m_bIsCurStun = FALSE;
			}
			else if( m_bIsCurFreeze && m_cFightStatus.GetCurStatusAnim() != BuffStatusManager::eStatusAnim_Freeze )
			{
				if( !m_bMoving && !m_bJumping && !m_bCountermarch )
					SwitchIdleAnim();
				m_bIsCurFreeze = FALSE;
			}

			ActionStatusMove();
		}
		else
		{
			switch( m_cFightStatus.GetCurStatusAnim() )
			{
			case BuffStatusManager::eStatusAnim_Stun:
				if( !m_bIsCurStun && !m_bHitPointPlayOver )
				{
					// ������ʾ�������˺�����Ч
					OnHitPoint( TRUE, GlobalControl::eNormal, GetAttackInfo() );
				}
				SwitchStunAnim();
				m_bIsCurStun = TRUE;
				break;
			case BuffStatusManager::eStatusAnim_FallOver:
				SwitchIdleAnim();
				break;
			case BuffStatusManager::eStatusAnim_Freeze:
				if( !m_bIsCurFreeze && !m_bHitPointPlayOver )
				{
					// ������ʾ�������˺�����Ч
					OnHitPoint( TRUE, GlobalControl::eNormal, GetAttackInfo() );
				}
				m_bIsCurFreeze = TRUE;
				break;
			default:
				if(!m_cFightStatus.IsBuoy())  //����״̬������Idle����
					SwitchIdleAnim();
				break;
			}
		}
	}
	else
	{
		if( !m_cFightStatus.IsCanMove() && !m_bMoving && m_movepath.IsMoveOver() )
		{
			switch( m_cFightStatus.GetCurStatusAnim() )
			{
			case BuffStatusManager::eStatusAnim_Stun:
				if( !m_bIsCurStun && !m_bHitPointPlayOver )
				{
					// ������ʾ�������˺�����Ч
					OnHitPoint( TRUE, GlobalControl::eNormal, GetAttackInfo() );
				}
				SwitchStunAnim();
				m_bIsCurStun = TRUE;
				break;
			case BuffStatusManager::eStatusAnim_FallOver:
				SwitchIdleAnim();
				break;
			case BuffStatusManager::eStatusAnim_Freeze:
				if( !m_bIsCurFreeze && !m_bHitPointPlayOver )
				{
					// ������ʾ�������˺�����Ч
					OnHitPoint( TRUE, GlobalControl::eNormal, GetAttackInfo() );
				}
				m_bIsCurFreeze = TRUE;
				break;
			default:
				SwitchIdleAnim();
				break;
			}
		}
		else
		{
			if( m_cFightStatus.GetCurStatusAnim() != BuffStatusManager::eStatusAnim_Stun && m_bIsCurStun)
			{
				if( !m_bMoving && !m_bJumping && !m_bCountermarch )
					SwitchIdleAnim();
				m_bIsCurStun = FALSE;
			}
			else if( m_bIsCurFreeze && m_cFightStatus.GetCurStatusAnim() != BuffStatusManager::eStatusAnim_Freeze )
			{
				if( !m_bMoving && !m_bJumping && !m_bCountermarch )
					SwitchIdleAnim();
				m_bIsCurFreeze = FALSE;
			}

			ActionStatusMove();
		}
	}
	unguard;
}

//////////////////////////////////////////
void CPlayer::ProcessCurStatus()
{
	guardfunc;
	m_status.ProcessStatus();

	switch (m_status.CurStatus())
	{
	case CPlayerStatus::esk_Null:           // ��
		break;
	case CPlayerStatus::esk_Idle:           // ����״̬�����κβ������ȴ�ָ�
		ActionStatusIdle();
		break;
	case CPlayerStatus::esk_PickItem:       // ��ȡ����
		ActionStatusPickItem();
		break;
	case CPlayerStatus::esk_DropItem:
		ActionStatusDropItem();
		break;
	case CPlayerStatus::esk_Talk:           // �Ի�
		ActionStatusTalk();
		break;
	case CPlayerStatus::esk_Trade:          //����
		ActionStatusTrade();
		break;
	case CPlayerStatus::esk_ChangeDir:		//ת��
		ActionStatusChangeDir();
		break;
	case CPlayerStatus::esk_PreAttack:      // Ԥ������״̬
		ActionStatusPreAttack();
		break;
	case CPlayerStatus::esk_Attack:         // ����״̬
		ActionStatusAttack();
		break;
	case CPlayerStatus::esk_PreIntonate:
		ActionStatusPreIntonate();
		break;
	case CPlayerStatus::esk_Intonate:			//
		ActionStatusIntonate();
		break;
	case CPlayerStatus::esk_HoldSkill:
		ActionStatusHoldSkill();
		break;
	case CPlayerStatus::esk_Sleep:          // �赹״̬
		ActionStatusSleep();
		break;
	case CPlayerStatus::esk_Die:            // ����״̬
		ActionStatusDie();
		break;
	case CPlayerStatus::esk_ActionTime:		//��һ��ʱ������Ī������
		ActionStatusActionTime();
		break;
	}

	//ս��״̬�л�, ��Ҫ����ս��״̬ 
	if( IsPlayer() && m_dwFightChangeFlag )
	{
		{
			if( m_pAnim )
				m_pAnim->UpdateHardItem( HasFightFlag(eFighting), &m_equips );
			m_dwFightChangeFlag = eNoChangeFight;//���Ľ���
		}
	}
	unguard;
}

void CPlayer::ClearMoveQueue()
{
	m_MoveQueue.Clear();
}

void CPlayer::UpdateBaseData( DWORD time )
{
	guardfunc;

	// ������Ԥ������
	if( m_vctAdvanceSkill.size() )
	{
		std::vector<SAdvanceSkillData>::iterator iter;
		for(int i=0; i<m_vctAdvanceSkill.size(); i++)
		{
			if( m_vctAdvanceSkill[i].pSkill )
			{
				ItemDefine::SItemSkill* pSkill = m_vctAdvanceSkill[i].pSkill;
				if( !(pSkill->bEmissionSkill || pSkill->ustPrepTime > 0 ) )
				{
					if( m_vctAdvanceSkill[i].dwHitPointPlayTime < g_dwLastFrameBeginTime 
						&& m_vctAdvanceSkill[i].nNeedPlayHurtAnim == CPlayer::ASH_NeedPlay && m_vctAdvanceSkill[i].nTargetPlayerID > -1 )
					{
						// Ԥ���ܻ�����
						PlayAdvanceSkillHurtAnim(m_vctAdvanceSkill[i].nTargetPlayerID, pSkill);
						m_vctAdvanceSkill[i].nNeedPlayHurtAnim = CPlayer::ASH_Played;
					}
				}
			}
		}
	}

	if( !m_bHitPointPlayOver && CanPlayHitPoint() && GetAttackInfo() )
	{
		OnHitPoint( TRUE, GlobalControl::eNormal, GetAttackInfo() );
	}

	// ���������Ҳ��ǻ��player,���˲���Ҫ�ڸ���������
	if( IsDeadOver() && !IsActivePlayer() )
	{
		ClearMoveQueue();
		return;
	}

	// 2.5D�ӽǲ�����������º��������ƶ�
	if( m_bRole && getwsCamera()->GetLock45DegreeCameraMode() )
	{
		if( (g_b25DMouseLButtonDownOnTerrain || g_b25DRoleMoveFollowMouse) 
			&& (g_dw25DLButtonDownStartTime != 0) 
			&& (HQ_TimeGetTime() - g_dw25DLButtonDownStartTime > 200 )
			&& s_CUI_ID_FRAME_Team.GetTeamFollowID() == -1 )		//���ֻ�в�������Ӹ�������²������������
		{
			POINT ptMouse;
			GetCursorPos( &ptMouse );
			ScreenToClient( GetActiveWindow(), &ptMouse );
			float fx = ptMouse.x;
			float fy = ptMouse.y;
			
			//������������϶� icon�� ���򲻽����ƶ�
			if( ptMouse.x > 0 && ptMouse.x < SCREEN_WIDTH && ptMouse.y > 0 && ptMouse.y < SCREEN_HEIGHT && !theIconDragManager.IsIconMoved())
				
			{
				if( theHeroGame.PickFromTerrain( fx, fy ) )
				{
					float fOffsetX = fx - GetPos().x;	// �Ѿ��ж�m_bRole������this�����Լ�������GetMe()
					float fOffsetY = fy - GetPos().y;
					float fMoveDist = sqrtf(fOffsetX*fOffsetX + fOffsetY*fOffsetY);
					if( fMoveDist > 0.5f )
					{
						static DWORD s_LastTargetPointShowTime = 0;
						ClearActionTarget();
						theHeroGame.GetPlayerMgr()->m_SkillBufTargetID = -1;
						theHeroGame.GetPlayerMgr()->SetCurUseSkill( 0, 0 );

						bool bShowTargetPoint = false;
						if( HQ_TimeGetTime() - s_LastTargetPointShowTime > 500 )
						{
							bShowTargetPoint = true;
							s_LastTargetPointShowTime = HQ_TimeGetTime();
						}
						theHeroGame.GetPlayerMgr()->MoveRoleTo( fx, fy, bShowTargetPoint, false, false ,true);

						// �ж��Ƿ��ϸ���
						if( s_CUI_ID_FRAME_Target.GetFollowPlayerId() >= 0 )
						{
							s_CUI_ID_FRAME_Target.SetFollowPlayerId(-1);
						}

						if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
							s_CUI_ID_FRAME_AutoAttackSet.ID_BUTTON_StopOnButtonClick(NULL);
						CrossMapPF::Instance()->Reset();
						CPathDirection::Instance()->Reset();
						s_CUI_ID_FRAME_MiniMap.SetAutoRuning(false);
					}
				}
				if( HQ_TimeGetTime() - g_dw25DLButtonDownStartTime > 1000 && !g_b25DRoleMoveFollowMouse )
				{
					// �����ƶ�������ʾ�ƶ����
					g_b25DRoleMoveFollowMouse = TRUE;
				}
			}
			else
			{
				// ������Ļ��Χ
				g_b25DMouseLButtonDownOnTerrain = FALSE;
				g_b25DRoleMoveFollowMouse = FALSE;
			}
		}
	}

	UpdateSound();

	SmoothFrameProcess();

	HandleMoveQueue();

	HideSkillProcess();

	MoveProcess();

	HandleActionQueue(true);

	ProcessCurStatus();

	// ������ٻ��ޣ�������������ƶ��У������Zֵ�����һ��
	if( GetMasterID() > -1 )
	{
		if( m_fPetAdjustPosCD > 0 )
		{
			m_fPetAdjustPosCD -= theHeroGame.GetFrameElapsedTime();
			if( m_fPetAdjustPosCD < 0 )
				m_fPetAdjustPosCD = 0.f;
		}
		AdjustPosToMaster();
	}

	UpdateCurZPos();
	JumpingProcess();

	if( m_bNeedDropBuf && m_dwDropEndTime > 0 && m_dwDropEndTime < HQ_TimeGetTime() )
	{
		m_bNeedDropBuf = FALSE;
		m_dwDropEndTime = 0;
	}
	UpdateRenderAlpha();

	UpdateLiftFlagStatus();


	MeMatrix matTransform;
	if( m_pAnim )
	{
		m_pAnim->SetPosition( m_x, m_y, m_z );
		m_pAnim->CalcTransformMatrix( &matTransform );
		m_pAnim->UpdateWorldBBox( &matTransform );
	}
#ifdef NEW_PLAYER_LOAD
	else
	{
		UpdateFakeWorldBBox( m_x, m_y, m_z );
	}
#endif

	float fFarToRole = theHeroGame.GetPlayerMgr()->GetFarRole();
	if( fFarToRole < 1 )
		fFarToRole = 1;

	float fFactor = GetDistanceToRole()/fFarToRole;

	if( fFactor > 1 )
		fFactor = 1;

	if( m_fShowNameAphla < fFactor )
	{
		m_fShowNameAphla += g_dwSmoothFrame*0.001f;
		if( m_fShowNameAphla > fFactor )
		{
			m_fShowNameAphla = fFactor;
		}
	}
	else
	{
		m_fShowNameAphla -= g_dwSmoothFrame*0.001f;
		if( m_fShowNameAphla < fFactor )
		{
			m_fShowNameAphla = fFactor;
		}
	}

	if(m_bRole&&IsCarrierint())
		thePlayerRole.UpdateUI()

		unguard;
}

void CPlayer::ShowChatPaoPao()
{
	guardfunc;
	if ( m_pChatPaoPao )
	{
		if( IsNpc() )
		{
			// �ж�NPC������ʾ��������
			D3DXVECTOR3 namePos;
			namePos = GetPos();
			namePos.z = GetAnim() ? GetAnim()->GetWorldMax().z : m_z + 1.7f;

			D3DXVECTOR3 d = getwsCamera()->GetMeCamera()->GetEyePt() - namePos;
			float toPosDist = D3DXVec3Length(&d);

			if (toPosDist > gCfg.m_fNameShowDistance && theApp->GetPlayerMgr()->GetMouseTargetPlayerSeverID() != m_stID)
			{
				m_pChatPaoPao->SetScreenPos(-2000, -2000);
				return;
			}
		}
		int nFontSize = m_pChatPaoPao->GetFontSize() * ControlObject::GetSCALE(NULL);
		int nWidth = 0, nHeight = 0;
		// 		int nLen = strlen(m_pChatPaoPao->GetText());
		// 		if ( nLen <= CHAT_INFO_WIDTH_MAX )
		// 		{
		// 			nWidth = nFontSize*( nLen +2)/2;
		// 			nHeight = nFontSize;
		// 		}
		// 		else
		// 		{
		// 			nWidth = nFontSize*(CHAT_INFO_WIDTH_MAX+2)/2;
		// 			nHeight = nFontSize*( nLen / CHAT_INFO_WIDTH_MAX + 1);
		// 		}
		RECT rcPaoPao;
		m_pChatPaoPao->GetRealRect(&rcPaoPao);
		nWidth =rcPaoPao.right  - rcPaoPao.left;
		nHeight = rcPaoPao.bottom - rcPaoPao.top;

		static int MIN_WIDTH = 20;
		if (nWidth < MIN_WIDTH * ControlObject::GetSCALE(NULL))
			nWidth = MIN_WIDTH * ControlObject::GetSCALE(NULL);

		float fHeight = 0;
		float fX = m_x;
		float fY = m_y;
		bool bSkipScreenToC = false;
		if (fontName_ && fontName_->IsVisible() && IsShow(CPlayer::eHeadInfo_Name))
		{
			D3DXVECTOR3 vPos2D = fontName_->GetPosition();
			fX = vPos2D.x + RTTFont::RTT_TEX_WIDTH / 2;
			fY = vPos2D.y;
			bSkipScreenToC = true;
		}
		else
		{
			Box* pBBox = GetWorldBBox();
			fHeight = (pBBox ? pBBox->v[7].z : (m_z + 1.7)) + 30*Config::m_fMdlSpaceScale;

			if (IsMounting())
			{
				int headBone = -1;
				if (GetAnim() && 
					GetAnim()->GetMex() &&
					GetAnim()->GetMex()->GetSkeleton() &&
					(headBone = GetAnim()->GetMex()->
					GetSkeleton()->FindBone("Bip01 Head")) != -1)
				{
					D3DXVECTOR3 v = *(D3DXVECTOR3*)&GetAnim()->GetBoneWorldPos(headBone);
					fHeight = v.z + 0.25f;
				}
			}
		}

		float ix = 0, iy = 0;
		bool bGoOn = false;
		if( bSkipScreenToC )
		{
			ix = fX;
			iy = fY;
			bGoOn = true;
		}
		else
		{
			Vector vCenter( fX, fY, fHeight );
			bGoOn = getwsCamera()->GetMeCamera()->WorldToScreen( vCenter, &ix, &iy, SCREEN_WIDTH, SCREEN_HEIGHT );
		}
		if( bGoOn )
		{
			float x =  ix - (float)(nWidth/2.f);
			float y =  iy - (float)nHeight - 5;
			m_nOldChatDialogBoxX = x;
			m_nOldChatDialogBoxY = y;
			// 			if (abs(m_nOldChatDialogBoxX - x) > 5)
			// 				m_nOldChatDialogBoxX = x;
			// 			if (abs(m_nOldChatDialogBoxY - y) > 5)
			// 				m_nOldChatDialogBoxY = y;

			if( IsNpc() )
			{
				// ���ͷ����NPCͼ�꣬��������������̧
				if (m_nImageType != -1)
				{
					CAdvancedMiniMap::Image* pImage = GetAdvancedMiniMap()->GetImage(m_nImageType);
					if (pImage && pImage->strEffectPath.length()!= 0)
						m_nOldChatDialogBoxY -= 12 + pImage->nHeight;
				}
			}
			m_pChatPaoPao->SetScreenPos(m_nOldChatDialogBoxX, m_nOldChatDialogBoxY);
		}

		if ( HQ_TimeGetTime() - m_dwChatDialogBoxBornTime >= m_dwChatDialogLifeTime )
		{
			ClearChatPaoPao();
		}
	}
	unguard;
}

void CPlayer::SetShopName( const char* pszShopName, DWORD dwColor )
{
	if( !m_pPrivateShopInfo )
		return;

	if( !m_pPrivateShopInfo->GetData() )
		return;

	m_pPrivateShopInfo->Clear();
	m_pPrivateShopInfo->SetText( pszShopName, dwColor );
}

void CPlayer::ShowPrivateShopInfo()
{
	guardfunc;
	if ( m_pPrivateShopInfo )
	{		
		int nFontSize = m_pPrivateShopInfo->GetFontSize();
		int nWidth = 0, nHeight = 0;


		// 		int nLen = strlen(m_pPrivateShopInfo->GetText());
		// 		if ( nLen <= CHAT_INFO_WIDTH_MAX )
		// 		{
		// 			nWidth = nFontSize * ControlText::GetREAL_SCALE(NULL) *( nLen ) * PRIVATESHOP_LENGTH_FACTOR;
		// 			nHeight = ( nFontSize * ControlText::GetREAL_SCALE(NULL)  ) * 2;
		// 		}
		// 		else
		// 		{
		// 			nWidth = nFontSize * ControlText::GetREAL_SCALE(NULL) * ( CHAT_INFO_WIDTH_MAX + 4 );
		// 			nHeight = ( nFontSize * ControlText::GetREAL_SCALE(NULL) + 2 ) * ( nLen / CHAT_INFO_WIDTH_MAX + 1);
		// 		}
		// 		RECT rc = {0,0,0,0};
		// 		rc.right = nWidth;
		// 		rc.bottom = nHeight;
		//		m_pPrivateShopInfo->SetRealRect( &rc );

		// 		RECT rc = {0,0,0,0};
		// 		rc.right = nWidth;
		// 		rc.bottom = nHeight; 
		nWidth = gCfg.m_RealRect.right;
		nHeight = gCfg.m_RealRect.bottom;
		// 
		// 		m_pPrivateShopInfo->SetRealRect(&gCfg.m_RealRect);
		//		m_pPrivateShopInfo->SetRealRect(&rc);

		Box* pBBox = GetWorldBBox();
		float fHeight = pBBox ? pBBox->v[7].z+30*Config::m_fMdlSpaceScale : m_z + 1.7 + 30*Config::m_fMdlSpaceScale;
		if( m_bMounting )
			fHeight -= 50*Config::m_fMdlSpaceScale;
		Vector vCenter( m_x, m_y, fHeight );
		float fx = 0, fy = 0;
		if( getwsCamera()->GetMeCamera()->WorldToScreen( vCenter, &fx, &fy, SCREEN_WIDTH, SCREEN_HEIGHT ) )
		{
			float x =  fx - (float)nWidth / 2.f * ControlObject::GetSCALE(NULL);
			float y =  fy - (float)nHeight- 20.f * ControlObject::GetSCALE(NULL);
			m_fOldPrivateShopX = x;
			m_fOldPrivateShopY = y;

			m_pPrivateShopInfo->SetScreenPos( m_fOldPrivateShopX, m_fOldPrivateShopY );
		}
		// �������Լ���λ�ü����͸����
		CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if( pMe )
		{
			float fSrcX, fSrcY, fSrcZ;
			float fDstX, fDstY, fDstZ;
			pMe->GetPos( &fSrcX, &fSrcY, &fSrcZ );
			this->GetPos( &fDstX, &fDstY, &fDstZ );
			float x = fDstX - fSrcX;
			float y = fDstY - fSrcY;
			float dist = sqrtf( x*x + y*y );
			float nAlpha = 1. - (dist/60.0f);
			if ( nAlpha < 0 )
			{
				nAlpha = 0;
			}
			m_pPrivateShopInfo->SetVisable( true);
			m_pPrivateShopInfo->SetAlpha(nAlpha);
		}
		else
			m_pPrivateShopInfo->SetVisable( true);
	}
	unguard;
}

void CPlayer::AnimCorrectProcess()
{
	guardfunc;

	if( !m_pAnim )
		return;

	SwitchCampAnim();

	ProcessActionState();

	if( m_pAnim->IsUpperBodyAndLowerBodyMode() && this->GetCharType() != Object_Monster) //lyhǿ�ƴ��� ����Ϊ�������ǵĶ�����ȫ������������һ���
	{
		int nLowerAnimType;
		if( m_bMounting )
		{
			if( m_pMountAnim )
			{
				if( m_pMountAnim->IsUpperBodyAndLowerBodyMode())
					nLowerAnimType = m_pMountAnim->GetCurLowerAnimType();
				else
					nLowerAnimType = m_pMountAnim->GetCurUpperAnimType();
			}
			else
				return;
		}
		else if( m_bMorphing )
		{
			if( m_pMorphAnim )
				nLowerAnimType = m_pMorphAnim->GetCurUpperAnimType();
			else
				return;
		}
		else
		{
			nLowerAnimType = m_pAnim->GetCurLowerAnimType();	
		}

		if( m_bDead )
		{
			if( g_dwLastFrameBeginTime > m_dwDeadTime )
			{
				if( g_dwLastFrameBeginTime - m_dwDeadTime > 3000 )
				{
					if( !( nLowerAnimType == MoreActionClient::Dead
						|| nLowerAnimType == MoreActionClient::single_dead
						|| nLowerAnimType == MoreActionClient::double_dead ) )
					{
						SwitchDieOverAnim();
					}
				}
				if( m_dwDeadTime != 0 && g_dwLastFrameBeginTime - m_dwDeadTime > 10000 )
				{
					if( !m_bDeadOver )
					{
						if( IsMonster() && !IsCollection(false) )
						{
							SetDeadOver( true );
							SetDeadOverTime( HQ_TimeGetTime() );
						}
					}
				}
			}
			return;
		}
		else
		{
			if( nLowerAnimType == MoreActionClient::Dead
				|| nLowerAnimType == MoreActionClient::single_dead
				|| nLowerAnimType == MoreActionClient::double_dead )
			{
				if( /*m_bRole && */theHeroGame.GetPlayerMgr()->IsRelivedByPlayer() )
				{
					SwitchIdleAnim();
					theHeroGame.GetPlayerMgr()->SetReLivedByPlayer(false);
				}
			}
		}

		if( m_bMorphing )
		{
			if( nLowerAnimType == MoreActionClient::temp2006 )
			{
				SwitchIdleAnim();
			}
		}

		if( m_bMoving )
		{
			if( nLowerAnimType > -1 )
			{
				if( nLowerAnimType == MoreActionClient::Idle
					|| nLowerAnimType == MoreActionClient::single_idle
					|| nLowerAnimType == MoreActionClient::SpecialIdle
					|| nLowerAnimType == MoreActionClient::single_specialidle
					|| nLowerAnimType == MoreActionClient::Attack_idle
					|| nLowerAnimType == MoreActionClient::single_attack_idle
					|| nLowerAnimType == MoreActionClient::double_attack_idle
					|| nLowerAnimType == MoreActionClient::single_recital
					|| nLowerAnimType == MoreActionClient::single_recital1 || nLowerAnimType == MoreActionClient::single_recital2
					|| nLowerAnimType == MoreActionClient::single_recital3 || nLowerAnimType == MoreActionClient::single_recital4
					|| nLowerAnimType == MoreActionClient::single_recital5 || nLowerAnimType == MoreActionClient::single_recital6
					|| nLowerAnimType == MoreActionClient::double_recital
					|| nLowerAnimType == MoreActionClient::double_recital1 || nLowerAnimType == MoreActionClient::double_recital2
					|| nLowerAnimType == MoreActionClient::double_recital3 || nLowerAnimType == MoreActionClient::double_recital4
					|| nLowerAnimType == MoreActionClient::double_recital5 || nLowerAnimType == MoreActionClient::double_recital6 )
				{
					if( IsInWater() )
					{
						if( m_bCountermarch )
						{
							SwitchSwimIdleAnim();
						}
						else
						{
							SwitchSwimAnim();
						}
					}
					else
					{
						if( m_bCountermarch )
						{
							SwitchWalkBackWardsAnim();
						}
						else
							SwitchRunAnim();
					}
				}

				if( m_bInWater )
				{
					if( nLowerAnimType == MoreActionClient::Run 
						|| nLowerAnimType == MoreActionClient::single_run 
						|| nLowerAnimType == MoreActionClient::single_attack_run 
						|| nLowerAnimType == MoreActionClient::double_run
						|| nLowerAnimType == MoreActionClient::Walk
						|| nLowerAnimType == MoreActionClient::single_walk
						|| nLowerAnimType == MoreActionClient::WalkBackWards
						|| nLowerAnimType == MoreActionClient::single_attack_walkbackwards
						|| nLowerAnimType == MoreActionClient::single_walkbackwards )
					{
						if( m_bCountermarch )
						{
							SwitchSwimIdleAnim();
						}
						else
						{
							SwitchSwimAnim();
						}
					}

					if( nLowerAnimType == MoreActionClient::Swim )
					{
						if( m_bCountermarch )
						{
							SwitchSwimIdleAnim();
						}
					}

					if( nLowerAnimType == MoreActionClient::SwimIdle )
					{
						if( !m_bCountermarch )
						{
							SwitchSwimAnim();
						}
					}
				}
				else
				{
					if( nLowerAnimType == MoreActionClient::Swim || nLowerAnimType == MoreActionClient::SwimIdle )
					{
						if( m_bCountermarch )
						{
							SwitchWalkBackWardsAnim();
						}
						else
						{
							SwitchRunAnim();
						}
					}

					if( nLowerAnimType == MoreActionClient::Run
						|| nLowerAnimType == MoreActionClient::Walk
						|| nLowerAnimType == MoreActionClient::single_walk
						|| nLowerAnimType == MoreActionClient::double_run
						|| nLowerAnimType == MoreActionClient::single_attack_run
						|| nLowerAnimType == MoreActionClient::single_run )
					{
						if( m_bCountermarch )
						{
							SwitchWalkBackWardsAnim();
						}
					}

					if( nLowerAnimType == MoreActionClient::WalkBackWards
						|| nLowerAnimType == MoreActionClient::single_attack_walkbackwards
						|| nLowerAnimType == MoreActionClient::single_walkbackwards )
					{
						if( !m_bCountermarch )
						{
							SwitchRunAnim();
						}
					}

					if( nLowerAnimType == MoreActionClient::falltothegroundrun
						|| nLowerAnimType == MoreActionClient::falltothegroundrun1 
						|| nLowerAnimType == MoreActionClient::single_attack_falltothegroundrun
						|| nLowerAnimType == MoreActionClient::single_falltothegroundrun )
					{
						if( m_bCountermarch )
						{
							SwitchWalkBackWardsAnim();
						}
					}
					if( m_cFightStatus.IsCanMove() && nLowerAnimType == MoreActionClient::Stun )
					{
						if( m_bInWater )
						{
							if( m_bCountermarch )
							{
								SwitchSwimIdleAnim();
							}
							else
							{
								SwitchSwimAnim();
							}
						}
						else
						{
							SwitchRunAnim();
						}
					}

					if( nLowerAnimType == MoreActionClient::drop 
						|| nLowerAnimType == MoreActionClient::single_drop
						|| nLowerAnimType == MoreActionClient::single_attack_drop
						|| nLowerAnimType == MoreActionClient::drop1 )
					{
						if( !m_bJumping && !m_bCountermarch )
						{
							SwitchRunAnim();
						}
					}
				}
			}
		}
		else
		{
			if( m_cFightStatus.IsCanMove() && nLowerAnimType == MoreActionClient::Stun )
			{
				SwitchIdleAnim();
			}

			if( IsInWater() && nLowerAnimType == MoreActionClient::Swim )
			{
				SwitchSwimIdleAnim();
			}
			else if( nLowerAnimType == MoreActionClient::Run
				|| nLowerAnimType == MoreActionClient::single_run
				|| nLowerAnimType == MoreActionClient::single_attack_run
				|| nLowerAnimType == MoreActionClient::double_run
				|| nLowerAnimType == MoreActionClient::WalkBackWards 
				|| nLowerAnimType == MoreActionClient::single_walkbackwards
				|| nLowerAnimType == MoreActionClient::single_attack_walkbackwards
				|| nLowerAnimType == MoreActionClient::Walk
				|| nLowerAnimType == MoreActionClient::single_walk
				|| nLowerAnimType == MoreActionClient::falltothegroundrun  // ������Ծ���¶���Ҳ��Ҫ���
				|| nLowerAnimType == MoreActionClient::single_falltothegroundrun
				|| nLowerAnimType == MoreActionClient::single_attack_falltothegroundrun )
			{
				SwitchIdleAnim();
			}
		}
	}
	else
	{
		int nUpperAnimType = m_pAnim->GetCurUpperAnimType();

		if( m_stCharType == Object_Monster )
		{
			if( nUpperAnimType == MoreActionClient::temp2006 )
			{
				SwitchIdleAnim();
			}
		}


		if( m_bDead && g_dwLastFrameBeginTime > m_dwDeadTime && m_dwDeadTime != 0 )
		{


			if( g_dwLastFrameBeginTime - m_dwDeadTime > 4000 )
			{
				if( nUpperAnimType != MoreActionClient::Dead/*1 */) //lyh++ 
				{
					SwitchDieOverAnim();

					//////lyh����++ 
					//if( !m_bDeadOver )
					//{
					//	if( IsMonster() && !IsCollection(false) )
					//	{
					//		AddRef(); 
					//		SetDeadOver( true );
					//		SetDeadOverTime( HQ_TimeGetTime() );
					//	}
					//}
				}
			}

			if( g_dwLastFrameBeginTime - m_dwDeadTime > 10000 ) //lyh���� ɾ��
			{
				if( !m_bDeadOver )
				{
					if( IsMonster() && !IsCollection(false) )
					{

						SetDeadOver( true );
						SetDeadOverTime( HQ_TimeGetTime() );
					}
				}
			}
			return;
		}

		if( m_bMoving )
		{
			if( nUpperAnimType == MoreActionClient::Idle 
				|| nUpperAnimType == MoreActionClient::single_idle
				|| nUpperAnimType == MoreActionClient::single_attack_idle
				|| nUpperAnimType == MoreActionClient::SpecialIdle 
				|| nUpperAnimType == MoreActionClient::single_specialidle )
			{
				SwitchRunAnim();
			}
		}
		else
		{
			if( nUpperAnimType == MoreActionClient::Run 
				|| nUpperAnimType == MoreActionClient::Walk
				|| nUpperAnimType == MoreActionClient::single_walk
				|| nUpperAnimType == MoreActionClient::single_run
				|| nUpperAnimType == MoreActionClient::single_attack_run
				|| nUpperAnimType == MoreActionClient::double_run )
			{
				SwitchIdleAnim();
			}
		}
	}
	unguard;
}

void CPlayer::RoleOperationProcess()
{
	guardfunc;
	if( m_bRole && thePlayerRole.CanSendActionMessage() )
	{
		switch (m_operation.dwType)
		{
		case SOperation::eOpNothing:
			OperNothing();
			break;
		case SOperation::eOpIdle:        //����
			OperIdle();
			break;
		case SOperation::eOpUseSkill:    //ʹ�ü���
			OperUseSkill();
			break;
		case SOperation::eOpTalk:        //�Ի�
			OperTalk();
			break;
		case SOperation::eOpGetItem:     //ȡ�õ���
			OperGetItem();
			break;
		case SOperation::eOpDropItem:	//��������
			OperDropItem();
			break;
		case SOperation::eOpTrade:       //����
			OperTrade();
			break;
		case SOperation::eOpChangeDir:	//ת��
			OperChangeDir();
			break;
		case SOperation::eOpMoveSkill:   //�ƶ���ȥʹ�ü���
			OperMoveSkill();
			break;
			break;
		case SOperation::eOpMoveDropItem://�ƶ���ȥ��������
			OperMoveDroptem();
			break;
		case SOperation::eOpDoAction:	//��Ī����Ϊ��Action
			OperDoAction();
			break;
		default:
			break;
		}
	}
	unguard;
}

extern BOOL g_bRoleRotatebyDir;
void CPlayer::TurnAroundProcess()
{
	guardfunc;

	if( m_bDead )
		return;

	if( m_bRole && !m_cFightStatus.IsCanMove() )
	{
		return;
	}


	float fCurRotateDistance = (float)g_dwSmoothFrame * g_fPlayerRotateSpeed*0.001f;
	m_dir = fmodf( m_dir, D3DX_PI*2 );	

	if( m_dir < 0 )
	{
		m_dir += D3DX_PI*2;
	}

	float fdiroffset = m_tdir - m_dir;
	fdiroffset = fmodf( fdiroffset, D3DX_PI*2 );

	if( fdiroffset > fCurRotateDistance || fdiroffset < -fCurRotateDistance )
	{
		if( m_tdir > m_dir )
		{
			if( m_tdir - m_dir > D3DX_PI )
				m_dir -= fCurRotateDistance;
			else
				m_dir += fCurRotateDistance;
		}
		else
		{
			if( m_dir - m_tdir > D3DX_PI )
				m_dir += fCurRotateDistance;
			else
				m_dir -= fCurRotateDistance;
		}
	}
	else
	{
		m_dir = m_tdir;

		if (m_readySkillInfo.bTryUse )
		{
			TryUseSkill(m_readySkillInfo.pTagPlayer, m_readySkillInfo.pSkill, false, m_readySkillInfo.bNoTip);
			m_readySkillInfo.pTagPlayer = 0;
			m_readySkillInfo.pSkill = 0;
			m_readySkillInfo.bTryUse = false;
		}
	}

	fCurRotateDistance = fCurRotateDistance*0.25f;

	SetUpperDir( m_tdir );

	///////////////////////1
	if( m_bRole )
	{
		if( m_bMoving )
		{
			m_bRotateLowerBody = FALSE;
			m_bRotateLowerBodyStart = FALSE;

			if( getwsCamera()->GetLock45DegreeCameraMode() )
				m_bForceTurnRole = FALSE;

			{
				RotateBody( &m_fLowerBodyDir, &m_fTargetLowerBodyDir, fCurRotateDistance*4.0f, D3DX_PI );

				////////////////old
				RotateBody( &m_fUpperBodyDir, &m_dir, fCurRotateDistance*1.0f, D3DX_PI*0.3f );
				RotateBody( &m_fUpperBodyDir, &m_fLowerBodyDir, 0, D3DX_PI*0.2f );

			}

			thePlayerRole.SetLastStopMovingTime( HQ_TimeGetTime() );

			g_fLastTheRoleRotateZCorrect = g_fTheRoleRotateZCorrect;
		}
		else
		{
			if( HQ_TimeGetTime() - thePlayerRole.GetLastStopMovingTime() > 618 )
			{
				if( g_bMouseRButtonIsDown || g_bTheRoleJumping )
				{
					// ����ת���ҷ�����״̬
					if( g_bMouseRoleTurn && !(GetSitStatus() && !(GetSitInterrupt())) && !IsPlayStandAnim() && (theApp->GetPlayerMgr()->IsTurnRoleToCamera() ) )
					{
						float fUpperLowerBodyAngle = 0;

						if( !m_bRotateLowerBody && HQ_TimeGetTime() - g_dwTheRoleJumpingEndTime > 800 )
						{
							fUpperLowerBodyAngle = CalcRotateAngle( m_fLowerBodyDir, m_fTargetLowerBodyDir );
							if( fUpperLowerBodyAngle > 0.01f )
							{
								m_bRotateLowerBody = TRUE;
								if( m_pAnim )
								{
									bool bPlayBuffStatusAnim = false;
									if( m_iBuffStatusAnimType != -1 && m_iBuffStatusAnimType == m_pAnim->GetCurLowerAnimType() )
										bPlayBuffStatusAnim = true;
									if( !IsInWater() && !m_bIntonating && !bPlayBuffStatusAnim )
									{
										if( CalcRotateAngleWithDir( m_fLowerBodyDir, m_fTargetLowerBodyDir ) > 0 )
											SwitchShuffleLeftAnim();
										else
											SwitchShuffleRightAnim();
									}
								}
							}
						}

						//////////////////////////////
						if( m_bRotateLowerBody )
						{
							RotateBody( &m_fLowerBodyDir, &m_fTargetLowerBodyDir, fCurRotateDistance*1.6f, D3DX_PI*0.2f );
							fUpperLowerBodyAngle = CalcRotateAngle( m_fLowerBodyDir, m_fTargetLowerBodyDir);
							m_fUpperBodyDir = m_fLowerBodyDir;

							if( fUpperLowerBodyAngle < 0.01f  )
							{
								m_bRotateLowerBody = FALSE;

								if( !m_bIntonating && m_pAnim )
								{
									m_pAnim->ForceCurrAnimLoopTime(-1);
									if( m_bMounting && m_pMountAnim )
										m_pMountAnim->ForceCurrAnimLoopTime(-1);
								}
							}
						}
					}
				}
				else if( 
					(!getwsCamera()->GetLock45DegreeCameraMode() || (getwsCamera()->GetLock45DegreeCameraMode() && m_bForceTurnRole)) 
					&&
					( !m_pAnim || m_pAnim->GetCurAnimType() != MoreActionClient::yongbao )
					&& !thePlayerRole.IsReliveAndWaitingToHell() )
				{
					RotateBody( &m_fUpperBodyDir, &m_dir, fCurRotateDistance*1.6f, D3DX_PI*0.3f );
					RotateBody( &m_fUpperBodyDir, &m_fLowerBodyDir, 0, D3DX_PI*0.2f );

					float fUpperLowerBodyAngle = 0;

					if( !m_bRotateLowerBody && HQ_TimeGetTime() - g_dwTheRoleJumpingEndTime > 800 )
					{
						fUpperLowerBodyAngle = CalcRotateAngle( m_fLowerBodyDir, m_dir);

						if( fUpperLowerBodyAngle > 0.01f )
						{
							m_bRotateLowerBody = TRUE;
							if( m_pAnim )
							{
								bool bPlayBuffStatusAnim = false;
								if( m_iBuffStatusAnimType != -1 && m_iBuffStatusAnimType == m_pAnim->GetCurLowerAnimType() )
									bPlayBuffStatusAnim = true;
								if( !IsInWater() && !m_bIntonating && (! (HasFightFlag( eFighting ) || IsFightPose())|| IsGoudaOperaMode()) && !bPlayBuffStatusAnim )
								{
									if( CalcRotateAngleWithDir( m_fLowerBodyDir, m_fUpperBodyDir ) > 0 )
										SwitchShuffleLeftAnim();
									else
										SwitchShuffleRightAnim();
								}
							}
						}
					}

					//////////////////////////////////
					if( m_bRotateLowerBody )
					{
						RotateBody( &m_fLowerBodyDir, &m_fUpperBodyDir, fCurRotateDistance*1.6f, D3DX_PI*0.2f );
						fUpperLowerBodyAngle = CalcRotateAngle( m_fLowerBodyDir, m_dir);

						if( fUpperLowerBodyAngle < 0.01f )
						{
							m_bRotateLowerBody = FALSE;
							m_bRotateLowerBodyStart = FALSE;
							if( getwsCamera()->GetLock45DegreeCameraMode() )
								m_bForceTurnRole = FALSE;

							if( !m_bIntonating && m_pAnim )
							{
								m_pAnim->ForceCurrAnimLoopTime(-1);
								if( m_bMounting && m_pMountAnim )
									m_pMountAnim->ForceCurrAnimLoopTime(-1);
							}
						}
					}
				}

			}
		}
	}
	else
	{
		RotateBody( &m_fLowerBodyDir, &m_fTargetLowerBodyDir, fCurRotateDistance*2.5f, D3DX_PI );
		RotateBody( &m_fUpperBodyDir, &m_tdir, fCurRotateDistance*2.5f, D3DX_PI );
		m_fUpperBodyDir = m_fLowerBodyDir;
	}

	if( m_bRole )
	{
		if( m_bMounting )
		{
			if( m_bJumping && !g_bTheRoleSlipJumping )
			{
				m_fTargetRotationX = 0;
			}
			else
			{
				float fRoleHeight = 80.0f*Config::m_fMdlSpaceScale;
				float fFrontWorldZ = 0.0f;
				float fBehindWorldZ = 0.0f;
				DWORD dwLoadFlags = 0;
				float fLowerDirX;
				float fLowerDirY;

				GetAngleTo2D( m_fLowerBodyDir, &fLowerDirX, &fLowerDirY );
				const float front2Back = 1.1f;//��ǰ�㵽����ľ���
				fLowerDirX *= front2Back/2;
				fLowerDirY *= front2Back/2;
				BOOL bInFloor;
				fFrontWorldZ = GetZByXY( m_z+fRoleHeight,  m_x + fLowerDirX, m_y + fLowerDirY, 0, &bInFloor, &dwLoadFlags, false );
				fBehindWorldZ = GetZByXY( m_z+fRoleHeight,  m_x - fLowerDirX, m_y - fLowerDirY, 0, &bInFloor, &dwLoadFlags, false );
				float fZOffSet = fBehindWorldZ - fFrontWorldZ;

				if( abs(fZOffSet) < 40.0f*GetMe3dConfig()->m_fMdlSpaceScale )
				{
					m_fTargetRotationX = atan2f(fBehindWorldZ-fFrontWorldZ,2);
				}
			}

			float fCurRotateDistance = (float)g_dwSmoothFrame * g_fPlayerRotateSpeed*0.001f;
			RotateBody( &m_fCurRotationX, &m_fTargetRotationX, fCurRotateDistance*0.04f, D3DX_PI*0.5f );
		}
	}
	unguard;
}

void CPlayer::SetServerZ( float fz )
{ 
	m_fServerZ = fz; 
	INT nCmp = m_fServerZ;
	if( nCmp > WORLD_HEIGHT || nCmp < -WORLD_HEIGHT )
	{
		m_fServerZ = 0;
	}
}

void CPlayer::UpdateCurZPos()
{
	guardfunc;
	if (IsUncontrolFlying() || IsCarrierint())
	{
		return;
	}
	// �����Ĺֵ�һ�λ�ȡZʱ����վ��ģ��floor���棬����ÿ֡������Zֵ��ȷ����ȷ
	BOOL bNeedUpdate = TRUE;
	if (m_x == m_fLastGetZ_x && m_y == m_fLastGetZ_y && m_z == m_fLastGetZ_z)
	{
		m_usSamePosFrameCount++;
		if( m_usSamePosFrameCount > m_usUpdateZFrameCount)
		{
			m_usSamePosFrameCount = 0;
		}
		else
		{
			if (m_bInElevator)
				bNeedUpdate = TRUE;
			else
				bNeedUpdate = FALSE;
		}
	}
	else
	{
		m_usSamePosFrameCount = 0;
	}

	if ( bNeedUpdate )
	{
		float fWorldZ = 0.0f;

		DWORD dwLoadFlags = 0;
		FLOAT fRoleHeight = 80.0f*Config::m_fMdlSpaceScale;
		if ( getwsCamera()->GetFreeCameraMode() )
		{
			fRoleHeight = 100.f;
		}

		//������.ӦΪ�ڵ�ͼû�м��ص�ʱ��Player����Ϣ�ͷ�������.(�ȸ���Ϣ����)
		if ( m_bRole ) 
		{
			if ( m_bAssaultMoving )
			{
				fWorldZ = GetZByXY(
					m_z + 62, 
					m_x,
					m_y,
					0, 
					&m_bInFloor, 
					&dwLoadFlags,
					TRUE, 
					&m_vTargetNormal
					);
			}
			else
			{					
				if (m_bMounting)
				{
					fWorldZ = GetZByXY(
						WORLD_HEIGHT,
						m_x,
						m_y,
						0, 
						&m_bInFloor, 
						&dwLoadFlags,
						TRUE, 
						&m_vTargetNormal
						);
				}
				else
				{
					// �����ӵ����������m_z��������Zֵ��ͬ
					bool bSetZ = false;
					if ( IsEmbraceAnim() && m_nInteractionMasterPlayerID != -1 )
					{
						CPlayer* pMasterPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nInteractionMasterPlayerID);
						if( pMasterPlayer )
						{
							fWorldZ = pMasterPlayer->GetPos().z;
							bSetZ = true;
						}
					}
					if ( !bSetZ )
					{
						fWorldZ = GetZByXY(
							WORLD_HEIGHT, 
							m_x,
							m_y,
							0, 
							&m_bInFloor, 
							&dwLoadFlags,
							TRUE, 
							&m_vTargetNormal
							);

						// ӵ�����������󣬼���zֵ
						if ( !IsEmbraceAnim() && m_bNeedResetPosAfterInteraction )
						{
							if ( abs(fWorldZ - m_z) > 0.5 && m_nInteractionMasterPlayerID != -1 )
							{
								CPlayer* pMasterPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nInteractionMasterPlayerID);
								if ( pMasterPlayer )
								{
									m_x = pMasterPlayer->GetPos().x;
									m_y = pMasterPlayer->GetPos().y;
									fWorldZ = pMasterPlayer->GetPos().z;
								}
							}
							m_bNeedResetPosAfterInteraction = FALSE;
						}
					}
				}
			}
		}
		else
		{
			if ( IsPlayer() )
			{						
				// �����ӵ����������m_z��������Zֵ��ͬ
				bool bSetZ = false;
				if ( IsEmbraceAnim() )
				{
					if ( m_nInteractionMasterPlayerID != -1 )
					{
						CPlayer* pMasterPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nInteractionMasterPlayerID);
						if ( pMasterPlayer )
						{
							fWorldZ = pMasterPlayer->GetPos().z;
							bSetZ = true;
						}
					}
				}
				if ( !bSetZ )
				{
					fWorldZ = GetZByXY(
						m_fServerZ + fRoleHeight, 
						m_x,
						m_y,
						0, 
						&m_bInFloor, 
						&dwLoadFlags,
						FALSE, 
						&m_vTargetNormal
						);

					// ӵ�����������󣬼���zֵ
					if ( !IsEmbraceAnim() && m_bNeedResetPosAfterInteraction )
					{
						if ( abs(fWorldZ - m_z) > 0.5 && m_nInteractionMasterPlayerID != -1 )
						{
							CPlayer* pMasterPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nInteractionMasterPlayerID);
							if ( pMasterPlayer )
							{
								m_x = pMasterPlayer->GetPos().x;
								m_y = pMasterPlayer->GetPos().y;
								fWorldZ = pMasterPlayer->GetPos().z;
							}
						}
						m_bNeedResetPosAfterInteraction = FALSE;
					}
				}
				// �������������m_fServerZ����ͻ��˸��ݱ��ؼ������
				if ( m_fServerZ == WORLD_HEIGHT )
					m_fServerZ = fWorldZ;
			}
			else
			{
				fWorldZ = GetZByXY(
					m_z + fRoleHeight*2.f, 
					m_x,
					m_y,
					0, 
					&m_bInFloor, 
					&dwLoadFlags,
					FALSE, 
					&m_vTargetNormal
					);
			}
		}

		if (!m_bJumping && !m_bAssaultMoving && !m_bInElevator && IsRole() && !IsUnControlState())
		{			
			//if (!m_bStartZMoving)
			{
				float fz = fWorldZ - m_fTerrainZ;
				static float fHeight = 0.3f; 
				if(fz > fHeight)
				{
					//m_fTargetZValue = m_z;					
					//m_bStartZMoving = false;
					//m_bHigh = true;
					m_z = fWorldZ;
				}

				//if(fz < -fHeight)
				//{
				//    m_fTargetZValue = m_z;
				//    m_bStartZMoving = true;
				//    m_bHigh = false;
				//}
			}			
		}

		m_vSaveXYGetZ = fWorldZ;
		m_fTerrainZ = fWorldZ;
		m_bCreateUpDataZ = TRUE;

		m_fLastGetZ_x = m_x;
		m_fLastGetZ_y = m_y;
		m_fLastGetZ_z = m_z;
	}

	unguard;
}

void CPlayer::JumpingProcess()
{
	guardfunc;
	if (IsUncontrolFlying() || IsCarrierint())
	{
		return;
	}
	if( m_stCharType != Object_Player )
	{
		m_z = m_fTerrainZ;

		{
			CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
			CWorldChunk* pChunk = pTile->GetChunkFromPos(m_x, m_y);

			if( pChunk )
			{
				float fStature = 1.2f;
				Box* pBBox = GetWorldBBox();
				if( pBBox )
					fStature = (pBBox->v[4].z - pBBox->v[0].z) * 0.8f;

				if( m_pAnim )
					m_pAnim->UpdateWorldBBox( (MeMatrix*)&m_matTransform );
#ifdef NEW_PLAYER_LOAD
				else
				{
					UpdateFakeWorldBBox(m_x, m_y, m_z);
				}
#endif

				if( !m_bInSingleFloor && 
					pChunk->GetLiquidHeight() - m_z > fStature )
				{
					m_z =  pChunk->GetLiquidHeight() - fStature;

					if( m_bRole )
					{
						g_bTheRoleJumping = FALSE;
						g_dwTheRoleJumpingEndTime = HQ_TimeGetTime();
						g_bTheRoleSlipJumping = FALSE;
						g_bTheRoleFallJumping = FALSE;
						m_bNeedDropBuf = FALSE;
						m_bJumping = FALSE;
						thePlayerRole.EndJump();
						m_bPlayedDropAnim = FALSE;
					}
					else
					{
						m_bJumping = FALSE;
						m_bNeedDropBuf = FALSE;
						m_bPlayedDropAnim = FALSE;
					}

					if( !IsInWater() )
					{
						SetInWater(TRUE);
						if( HasFightFlag(eFighting) )
						{
							if( m_bRole && GetName() )
							{
								char str[MAX_PATH] = {0};
								MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%s ����ˮ�У��˳�ս��\n",GetName());
								LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, string(str));
							}

							if( ClearFightFlag( eFighting, 0 ) )
							{
								if( m_bRole && theHeroGame.GetPlayerMgr() )
								{
									theHeroGame.GetPlayerMgr()->SendDrawInWeapon();
								}
							}
						}

						if( m_bMoving )
						{
							if( m_bCountermarch || ( m_bRole && g_bTheRoleCountermarch ) )
							{
								SwitchSwimIdleAnim();
							}
							else
							{
								SwitchSwimAnim();
							}
						}
						else
						{
							SwitchSwimIdleAnim();
						}
					}

					SetInWater(TRUE);
					if( HasFightFlag(eFighting) )
					{
						if( m_bRole && GetName() )
						{
							char str[MAX_PATH] = {0};
							MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%s ����ˮ�У��˳�ս��\n",GetName());
							LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, string(str));
						}

						if( ClearFightFlag( eFighting, 0 ) )
						{
							if( m_bRole && theHeroGame.GetPlayerMgr() )
							{
								theHeroGame.GetPlayerMgr()->SendDrawInWeapon();
							}
						}
					}
				}
				else
				{
					if( IsInWater() )
					{
						SetInWater(FALSE);
						if( m_bMoving )
						{
							SwitchRunAnim();
						}
						else
						{
							SwitchIdleAnim();
						}

						if( IsHaveWeapon() )
						{
							// ��ʾ����
							SetShowWeapon(TRUE);
						}
					}
					SetInWater(FALSE);
				}
			}
		}
		return;
	}

	if( m_bRole )
	{
		//������ߵ��õ�ʱ��
		DWORD dwToHighestTime = m_fStartJumpingSpeed/g_fGravitation;
		//��Ծʱ���ڿ��з��е�ʱ��
		DWORD dwJumpingInTheSkyTime = 0;
		//��Ծ��߸߶�
		float fMaxJumpingHeight = m_fStartJumpingSpeed*dwToHighestTime - g_fGravitation*dwToHighestTime*dwToHighestTime*0.5f;

		if( g_bTheRoleJumping && g_dwLastFrameBeginTime > g_dwTheRoleJumpTime )
		{
			// У����Ծ�߶�
			/////////////////////////////////////////////////////////////////////////
			if( fMaxJumpingHeight > 1.7 )
			{
				m_fStartJumpingSpeed = m_fMaxStartJumpingSpeed;
				dwToHighestTime = m_fStartJumpingSpeed/g_fGravitation;
				fMaxJumpingHeight = m_fStartJumpingSpeed*dwToHighestTime - g_fGravitation*dwToHighestTime*dwToHighestTime*0.5f;
			}
			if( thePlayerRole.IsRoleJump() )
			{
				if( m_z > thePlayerRole.GetStartJumpZ() + fMaxJumpingHeight + 1.f )
				{
					// �߶��쳣�����Լ�ק��������
					m_x = thePlayerRole.GetStartJumpX();
					m_y = thePlayerRole.GetStartJumpY();
					m_z = thePlayerRole.GetStartJumpZ();

					g_bTheRoleJumping = FALSE;
					if( m_bJumping )
						g_dwTheRoleJumpingEndTime = HQ_TimeGetTime();
					g_bTheRoleSlipJumping = FALSE;
					g_bTheRoleFallJumping = FALSE;
					m_bNeedDropBuf = FALSE;
					m_bJumping = FALSE;
					thePlayerRole.EndJump();
					m_bPlayedDropAnim = FALSE;

					if( m_bMoving )
					{
						SwitchRunAnim();
					}
					else
					{
						SwitchIdleAnim();
					}

					if( IsHaveWeapon() )
					{
						// ��ʾ����
						SetShowWeapon(TRUE);
					}
					return;
				}
			}
		}

		if( g_bTheRoleJumping && g_dwLastFrameBeginTime > g_dwTheRoleJumpTime )
		{
			/////////////////////////////////////////////////////////////////////////

			dwJumpingInTheSkyTime = g_dwLastFrameBeginTime - g_dwTheRoleJumpTime;

			if( dwJumpingInTheSkyTime < dwToHighestTime )
			{
				float t = (float)dwJumpingInTheSkyTime/dwToHighestTime;
				float fMaxJumpingHeight = m_fStartJumpingSpeed*dwToHighestTime - g_fGravitation*dwToHighestTime*dwToHighestTime*0.5f;

				float fValue = 0.618f;
				if( m_bMounting || m_bMorphing )
				{
					fValue = 0.618f;
					if( m_bMounting )
					{
						ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
						if( pDrome )
						{
							fValue = pDrome->fJumpSpeed;
						}
					}
				}
				else
				{
					if( m_ucSex == Sex_Male )
					{
						fValue = gCfg.m_fJumpUpValueMale;
					}
					else
					{
						fValue = gCfg.m_fJumpUpValueFemale;
					}
				}

				m_fJumpingHeight = fMaxJumpingHeight*pow( t, fValue );
			}
			else
			{
				float fDropValue = 1;

				if( m_bMounting || m_bMorphing )
				{
					fDropValue = 4;
					if( m_bMounting )
					{
						ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
						if( pDrome )
						{
							fDropValue = pDrome->fDropSpeed;
						}
					}
				}
				else
				{
					if( m_ucSex == Sex_Male )
					{
						fDropValue = gCfg.m_fDropValueMale;
					}
					else
					{
						fDropValue = gCfg.m_fDropValueFemale;
					}
				}

				DWORD dwPassedTime = dwJumpingInTheSkyTime - dwToHighestTime;
				m_fJumpingHeight = fMaxJumpingHeight - g_fGravitation*dwPassedTime*dwPassedTime*0.5f*fDropValue;
			}

			m_z = m_fStartJumpingTerrainZ + m_fJumpingHeight;

			if( dwJumpingInTheSkyTime > dwToHighestTime || m_z - m_fTerrainZ < THEROLEANDTERRAINOFFZLIMIT  )
			{
				if( m_z < m_fTerrainZ && dwJumpingInTheSkyTime < dwToHighestTime )
				{
					m_z = m_fTerrainZ + 0.0618f;
				}

				if( m_z < m_fTerrainZ )
				{
					int iDropTime = 0;
					if( g_bTheRoleFallJumping || !g_bTheRoleSlipJumping )
						iDropTime = SwitchDropAnim();

					m_fJumpingHeight = 0;
					m_z = m_fTerrainZ;
					g_bTheRoleJumping = FALSE;
					g_dwTheRoleJumpingEndTime = HQ_TimeGetTime();
					g_bTheRoleSlipJumping = FALSE;
					g_bTheRoleFallJumping = FALSE;
					m_bJumping = FALSE;
					thePlayerRole.EndJump();
					if( IsRole() && !m_bMounting )
					{
						if( GetSex() == Sex_Male )
						{
							PlaySoundConfig( SoundConfig::EST_DropM );
						}
						else
						{
							PlaySoundConfig( SoundConfig::EST_DropF );
						}
					}
					if( iDropTime <= 0 )
					{
						m_bNeedDropBuf = FALSE;
					}
					else
					{
						m_dwDropEndTime = iDropTime + HQ_TimeGetTime();
						m_bNeedDropBuf = TRUE;
					}
				}
			}

			if( g_bTheRoleFallJumping )
			{
				if( dwJumpingInTheSkyTime > 600 )
				{
					if( m_pAnim && m_pAnim->IsUpperBodyAndLowerBodyMode() )
					{
						int nLowerAnimType;

						if( m_bMounting )
							nLowerAnimType = m_pMountAnim->GetCurUpperAnimType();
						else
							nLowerAnimType = m_pAnim->GetCurLowerAnimType();

						if( nLowerAnimType != MoreActionClient::glide && !m_bPlayedDropAnim )
						{
							SwitchGlide();
						}
					}
				}
			}
			else
			{
				if( g_bTheRoleSlipJumping )
				{
					m_z = m_fTerrainZ;
					m_fJumpingHeight = 0;
					m_fStartJumpingTerrainZ = m_fTerrainZ;
				}
			}
		}
		else
		{
			//�����Ҫƽ������
			if(m_bStartZMoving)
			{
				if(m_bHigh)
				{
					m_fTargetZValue += m_fMoveRate * g_ZMoveRate * g_dwLastFrameCostTime;
					m_z = m_fTargetZValue;

					if(m_z > m_fTerrainZ)
					{
						m_z = m_fTerrainZ;
						m_fTargetZValue = 0;
						m_bStartZMoving = false;
					}
				}
				else
				{
					m_fTargetZValue -= m_fMoveRate * g_ZMoveRate * g_dwLastFrameCostTime;
					m_z = m_fTargetZValue;

					if(m_z < m_fTerrainZ)
					{
						m_z = m_fTerrainZ;
						m_fTargetZValue = 0;
						m_bStartZMoving = false;
					}
				}
			}
			else
			{
				m_z = m_fTerrainZ;
				m_fJumpingHeight = 0;
				m_fStartJumpingTerrainZ = m_fTerrainZ;
			}
		}
	}
	else
	{
		if( m_bJumping && g_dwLastFrameBeginTime > m_dwStartJumpingTime )
		{
			DWORD dwToHighestTime = m_fStartJumpingSpeed/g_fGravitation;//������ߵ��õ�ʱ��
			DWORD dwJumpingInTheSkyTime = 0;//��Ծʱ���ڿ��з��е�ʱ��

			dwJumpingInTheSkyTime = g_dwLastFrameBeginTime - m_dwStartJumpingTime;

			if( dwJumpingInTheSkyTime < dwToHighestTime )
			{
				float t = (float)dwJumpingInTheSkyTime/dwToHighestTime;
				float fMaxJumpingHeight = m_fStartJumpingSpeed*dwToHighestTime - g_fGravitation*dwToHighestTime*dwToHighestTime*0.5f;

				float fValue = 0.618f;
				if( m_bMounting || m_bMorphing )
				{
					fValue = 0.618f;
					if( m_bMounting )
					{
						ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
						if( pDrome )
						{
							fValue = pDrome->fJumpSpeed;
						}
					}
				}
				else
				{
					if( m_ucSex == Sex_Male )
					{
						fValue = gCfg.m_fJumpUpValueMale;
					}
					else
					{
						fValue = gCfg.m_fJumpUpValueFemale;
					}
				}

				m_fJumpingHeight = fMaxJumpingHeight*pow( t, fValue );
			}
			else
			{
				float fDropValue = 1;
				if( m_bMounting || m_bMorphing )
				{
					fDropValue = 4;
					if( m_bMounting )
					{
						ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
						if( pDrome )
						{
							fDropValue = pDrome->fDropSpeed;
						}
					}
				}
				else
				{
					if( m_ucSex == Sex_Male )
					{
						fDropValue = gCfg.m_fDropValueMale;
					}
					else
					{
						fDropValue = gCfg.m_fDropValueFemale;
					}
				}

				float fMaxJumpingHeight = m_fStartJumpingSpeed*dwToHighestTime - g_fGravitation*dwToHighestTime*dwToHighestTime*0.5f;
				DWORD dwPassedTime = dwJumpingInTheSkyTime - dwToHighestTime;
				m_fJumpingHeight = fMaxJumpingHeight - g_fGravitation*dwPassedTime*dwPassedTime*0.5f*fDropValue;
			}

			m_z = m_fStartJumpingTerrainZ + m_fJumpingHeight;

			if( dwJumpingInTheSkyTime > dwToHighestTime || m_z - m_fTerrainZ < THEROLEANDTERRAINOFFZLIMIT  )
			{
				if( m_z < m_fTerrainZ && dwJumpingInTheSkyTime < dwToHighestTime )
				{
					m_z = m_fTerrainZ + 0.0618f;
				}

				if( m_z < m_fTerrainZ )
				{
					m_fJumpingHeight = 0;
					m_z = m_fTerrainZ;
					m_bJumping = FALSE;
					m_bNeedDropBuf = FALSE;
					SwitchDropAnim();
				}
			}
		}
		else
		{
			m_z = m_fTerrainZ;
			m_fJumpingHeight = 0;
			m_fStartJumpingTerrainZ = m_fTerrainZ;
		}
	}

	{
		CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
		CWorldChunk* pChunk = pTile->GetChunkFromPos(m_x, m_y);

		if( pChunk )
		{
			float fStature = 1.2f;
			Box* pBBox = GetWorldBBox();
			if( pBBox )
				fStature = (pBBox->v[4].z - pBBox->v[0].z) * 0.8f;

			if( m_pAnim )
				m_pAnim->UpdateWorldBBox( (MeMatrix*)&m_matTransform );
#ifdef NEW_PLAYER_LOAD
			else
			{
				UpdateFakeWorldBBox(m_x, m_y, m_z);
			}
#endif

			if( !m_bInSingleFloor && 
				pChunk->GetLiquidHeight() - m_z > fStature )
			{
				float fOffset = 0.102;
				m_z =  pChunk->GetLiquidHeight() - fStature - fOffset;

				if( m_bRole )
				{
					g_bTheRoleJumping = FALSE;
					if( m_bJumping )
						g_dwTheRoleJumpingEndTime = HQ_TimeGetTime();
					g_bTheRoleSlipJumping = FALSE;
					g_bTheRoleFallJumping = FALSE;
					m_bNeedDropBuf = FALSE;
					m_bJumping = FALSE;
					thePlayerRole.EndJump();

					m_bPlayedDropAnim = FALSE;
				}
				else
				{
					m_bJumping = FALSE;
					m_bNeedDropBuf = FALSE;
					m_bPlayedDropAnim = FALSE;
				}

				if( !IsInWater() )
				{
					SetInWater(TRUE);
					if( HasFightFlag(eFighting) )
					{
						if( m_bRole && GetName() )
						{
							char str[MAX_PATH] = {0};
							MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%s ����ˮ�У��˳�ս��\n",GetName());
							LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, string(str));
						}
						if( ClearFightFlag( eFighting, 0 ) )
						{
							if( m_bRole && theHeroGame.GetPlayerMgr() )
							{
								theHeroGame.GetPlayerMgr()->SendDrawInWeapon();
							}
						}
					}

					if( m_bMoving )
					{
						if( m_bCountermarch || ( m_bRole && g_bTheRoleCountermarch ) )
						{
							SwitchSwimIdleAnim();
						}
						else
						{
							SwitchSwimAnim();
						}
					}
					else
					{
						SwitchSwimIdleAnim();
					}
				}

				SetInWater(TRUE);
				if( HasFightFlag(eFighting) )
				{
					if( m_bRole && GetName() )
					{
						char str[MAX_PATH] = {0};
						MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%s ����ˮ�У��˳�ս��\n",GetName());
						LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, string(str));
					}

					if( ClearFightFlag( eFighting, 0 ) )
					{
						if( m_bRole && theHeroGame.GetPlayerMgr() )
						{
							theHeroGame.GetPlayerMgr()->SendDrawInWeapon();
						}
					}
				}
			}
			else
			{
				if( IsInWater() )
				{
					SetInWater(FALSE);
					if( m_bMoving )
					{
						SwitchRunAnim();
					}
					else
					{
						SwitchIdleAnim();
					}

					if( IsHaveWeapon() )
					{
						// ��ʾ����
						if( g_bTheRoleCountermarch )
							SetShowWeapon(TRUE);
						else
							SetShowWeapon(TRUE, TRUE);
					}
				}
				SetInWater(FALSE);
			}
		}
	}

	unguard;
}

void CPlayer::SoundProcess()
{
	guardfunc;
	if( m_bRole )
	{
		if( m_pAnim )
		{
			static BOOL bPlayedLeftSound = FALSE;
			static BOOL bPlayedRightSound = FALSE;
			static BOOL bPlaySwimSound = FALSE;

			bool bOverWater = false;

			int nLowerAnimType;
			int nUpperAnimType;

			if( m_bMounting && m_pMountAnim )
			{
				nLowerAnimType = m_pMountAnim->GetCurUpperAnimType();
				nUpperAnimType = m_pMountAnim->GetCurUpperAnimType();
			}
			else
			{
				nLowerAnimType = m_pAnim->GetCurLowerAnimType();
				nUpperAnimType = m_pAnim->GetCurUpperAnimType();
			}

			{

				float fWaterHeight = GetZByXY( WORLD_HEIGHT, m_x, m_y, 0 );
				CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
				CWorldChunk* pChunk = pTile->GetChunkFromPos(m_x, m_y);

				if( pChunk )
				{
					if( pChunk->GetLiquidHeight() > fWaterHeight )
					{
						bOverWater = TRUE;
					}
				}
			}

			if( m_bInWater )
			{
				float iSwimFactor = 0.7;
				{

					float fFactor = 0;
					fFactor = m_pAnim->GetUpperBodyFactor();

					if(fFactor > 0 && fFactor < iSwimFactor)
						bPlaySwimSound = false;
					if(fFactor > iSwimFactor && !bPlaySwimSound)
					{
						bPlaySwimSound = true;
						//GSound.PlaySound( GetFullFileName("data\\audio\\role\\swimmig_zi.wav"),false,NULL );
						if( GetSex() == Sex_Male )
						{
							PlaySoundConfigPos( SoundConfig::EST_SwimM, &GetPos() );
						}
						else
						{
							PlaySoundConfigPos( SoundConfig::EST_SwimF, &GetPos() );
						}

					}
				}
			}



			if( nLowerAnimType > -1 )
			{
				if( nLowerAnimType == MoreActionClient::falltothegroundrun 
					|| nLowerAnimType == MoreActionClient::single_falltothegroundrun
					|| nLowerAnimType == MoreActionClient::single_attack_falltothegroundrun )
				{
					float fFactor = 0;
					if( m_bMounting )
					{
						if( m_pMountAnim )
						{
							fFactor = m_pMountAnim->GetUpperBodyFactor();
							if( m_pMountAnim->IsUpperBodyBlending() )
							{
								bPlayedLeftSound = TRUE;
								bPlayedRightSound = TRUE;
								fFactor = 1;
							}
						}
					}
					else
					{
						{
							fFactor = m_pAnim->GetLowerBodyFactor();
							if( m_pAnim->IsLowerBodyBlending() )
							{
								bPlayedLeftSound = TRUE;
								bPlayedRightSound = TRUE;
								fFactor = 1;
							}
						}
					}

					if( fFactor > 0.75 && !bPlayedLeftSound )
					{
						if( m_bMounting )
						{
							ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
							if( pDrome )
							{
								GSound.PlaySound( GetFullFileName(pDrome->GetRunSoundOfLeftFootPath()), false,  &GetPos() );
							}
						}
						else if(bOverWater)
						{
							if( GetSex() == Sex_Male )
							{
								PlaySoundConfig( SoundConfig::EST_RunInWaterM );
							}
							else
							{
								PlaySoundConfig( SoundConfig::EST_RunInWaterF );
							}
							//GSound.PlaySound( GetFullFileName("data\\audio\\role\\runinwater.wav"),false, NULL );
						}
						else
						{
							if( GetSex() == Sex_Male )
							{
								PlaySoundConfig( SoundConfig::EST_RunLM );
							}
							else
							{
								PlaySoundConfig( SoundConfig::EST_RunLF );
							}
							//GSound.PlaySound( GetFullFileName("data\\audio\\role\\left_sand.wav"),false,NULL );
						}

						bPlayedLeftSound = TRUE;
					}

					if( fFactor < 0.75 )
					{
						bPlayedLeftSound = FALSE;
					}

					if( fFactor > 0.8667 && !bPlayedRightSound )
					{
						if( m_bMounting )
						{
							ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
							if( pDrome )
							{
								GSound.PlaySound( GetFullFileName((char*)pDrome->GetRunSoundOfRightFootPath()), false, &GetPos() );
							}
						}
						else if(bOverWater)
						{
							if( GetSex() == Sex_Male )
							{
								PlaySoundConfig( SoundConfig::EST_RunInWaterM );
							}
							else
							{
								PlaySoundConfig( SoundConfig::EST_RunInWaterF );
							}
							//GSound.PlaySound( GetFullFileName("data\\audio\\role\\runinwater.wav"),false, NULL );
						}
						else
						{
							if( GetSex() == Sex_Male )
							{
								PlaySoundConfig( SoundConfig::EST_RunRM );
							}
							else
							{
								PlaySoundConfig( SoundConfig::EST_RunRF );
							}
							//GSound.PlaySound( GetFullFileName("data\\audio\\role\\right_sand.wav"),false,NULL );
						}

						bPlayedRightSound = TRUE;
					}

					if( fFactor < 0.8667 )
					{
						bPlayedRightSound = FALSE;
					}
				}

				if( (nLowerAnimType == MoreActionClient::Run 
					|| nLowerAnimType == MoreActionClient::Walk 
					|| nLowerAnimType == MoreActionClient::single_walk 
					|| nLowerAnimType == MoreActionClient::WalkBackWards || nLowerAnimType == MoreActionClient::single_walkbackwards
					|| nLowerAnimType == MoreActionClient::double_run || nLowerAnimType == MoreActionClient::single_run 
					|| nLowerAnimType == MoreActionClient::single_attack_run 
					|| nLowerAnimType == MoreActionClient::single_run_attackr1 
					|| nLowerAnimType == MoreActionClient::single_walk_attackl1 
					|| nLowerAnimType == MoreActionClient::single_run_attackr1 
					|| nLowerAnimType == MoreActionClient::single_run_attackl1 
					|| nLowerAnimType == MoreActionClient::run_fire 
					|| nLowerAnimType == MoreActionClient::walk_fire )
					&& this->IsMoving()
					)
				{
					float fFactor = 0;

					if( m_bMounting )
					{
						if( m_pMountAnim )
						{
							fFactor = m_pMountAnim->GetUpperBodyFactor();
							if( m_pMountAnim->IsUpperBodyBlending() )
							{
								bPlayedLeftSound = TRUE;
								bPlayedRightSound = TRUE;
								fFactor = 1;
							}
						}
					}
					else
					{
						{
							fFactor = m_pAnim->GetLowerBodyFactor();
							//lyh++ �����еĶ������Ž���
							if( m_bMorphing && m_pMorphAnim )
							{
								fFactor = m_pMorphAnim->GetUpperBodyFactor();
							}

							if( m_pAnim->IsLowerBodyBlending() )
							{
								bPlayedLeftSound = TRUE;
								bPlayedRightSound = TRUE;
								fFactor = 1;
							}
						}
					}

					if( fFactor > 0.25 && !bPlayedLeftSound )
					{
						if( m_bMounting )
						{
							ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
							if( pDrome )
							{
								GSound.PlaySound( GetFullFileName((char*)pDrome->GetRunSoundOfLeftFootPath()), false,  &GetPos() );
							}
						}
						else if(bOverWater)
						{
							if( GetSex() == Sex_Male )
							{
								PlaySoundConfig( SoundConfig::EST_RunInWaterM );
							}
							else
							{
								PlaySoundConfig( SoundConfig::EST_RunInWaterF );
							}
							//GSound.PlaySound( GetFullFileName("data\\audio\\role\\runinwater.wav"),false, NULL );
						}
						else
						{
							if( GetSex() == Sex_Male )
							{
								PlaySoundConfig( SoundConfig::EST_RunLM );
							}
							else
							{
								PlaySoundConfig( SoundConfig::EST_RunLF );
							}
							//GSound.PlaySound( GetFullFileName("data\\audio\\role\\left_sand.wav"),false,NULL );
						}

						bPlayedLeftSound = TRUE;
					}

					if( fFactor < 0.25 )
					{
						bPlayedLeftSound = FALSE;
					}

					if( fFactor > 0.75 && !bPlayedRightSound )
					{
						if( m_bMounting )
						{
							ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
							if( pDrome )
							{
								GSound.PlaySound( GetFullFileName((char*)pDrome->GetRunSoundOfRightFootPath()), false, &GetPos() );
							}
						}
						else if(bOverWater)
						{
							if( GetSex() == Sex_Male )
							{
								PlaySoundConfig( SoundConfig::EST_RunInWaterM );
							}
							else
							{
								PlaySoundConfig( SoundConfig::EST_RunInWaterF );
							}
							//GSound.PlaySound( GetFullFileName("data\\audio\\role\\runinwater.wav"),false, NULL );
						}
						else
						{
							if( GetSex() == Sex_Male )
							{
								PlaySoundConfig( SoundConfig::EST_RunRM );
							}
							else
							{
								PlaySoundConfig( SoundConfig::EST_RunRF );
							}
							//GSound.PlaySound( GetFullFileName("data\\audio\\role\\right_sand.wav"),false,NULL );
						}

						bPlayedRightSound = TRUE;
					}

					if( fFactor < 0.75 )
					{
						bPlayedRightSound = FALSE;
					}
				}
			}
		}
	}
	unguard;
}

void CPlayer::RoleSlipProcess()
{
	guardfunc;
	// 	return;
	if( m_bRole && !g_bTheRoleJumping && !IsInWater() && !IsEmbraceAnim() )
	{
		D3DXVECTOR3 vAxis( 0, 0, 1 );
		D3DXVECTOR3 vUp( 0, 0, 1 );

		if( !getwsCamera()->GetFreeCameraMode() )
		{
			if( !IsInWater() && !m_bJumping )
			{
				vAxis = m_vTargetNormal;
			}

			D3DXVec3Normalize( &vAxis, &vAxis );

			float fDot = D3DXVec3Dot( &vUp, &vAxis );
			float fTheta = acosf( fDot );
			if( fTheta > g_fTheRoleSlipJumpingAngle && ( vAxis.x != 0 || vAxis.y != 0 ) )
			{
				if( m_bInFloor )
				{
					if( g_dwLastFrameBeginTime > g_dwTheRoleSlipStartTime + 100 )
					{
						g_dwTheRoleSlipStartTime = g_dwLastFrameBeginTime;
						g_bTheRoleSlipJumping = TRUE;
						g_vTheRoleSlipJumpingDir = vAxis;
						g_bTheRoleJumping = TRUE;
						g_bTheRoleJumpingCountermarch = g_bTheRoleCountermarch;
						g_vTheRoleJumpingDir = vAxis;
						g_fTheRoleJumpingRotate = g_fTheRoleRotateZCorrect + g_fTheRoleDirCorrect;
						g_dwTheRoleJumpTime = g_dwLastFrameBeginTime + 61;
						m_fJumpingHeight = 0;
						m_fStartJumpingTerrainZ = m_fTerrainZ;
						m_bJumping = TRUE;
						m_dwStartJumpingTime = g_dwLastFrameBeginTime + 61;
					}
				}
				else
				{
					if( g_dwLastFrameBeginTime > g_dwTheRoleSlipStartTime + 100 )
					{
						g_dwTheRoleSlipStartTime = g_dwLastFrameBeginTime;
						g_bTheRoleSlipJumping = TRUE;
						g_vTheRoleSlipJumpingDir = vAxis;
						g_bTheRoleJumping = TRUE;
						g_bTheRoleJumpingCountermarch = g_bTheRoleCountermarch;
						g_vTheRoleJumpingDir = vAxis;
						g_fTheRoleJumpingRotate = g_fTheRoleRotateZCorrect + g_fTheRoleDirCorrect;
						g_dwTheRoleJumpTime = g_dwLastFrameBeginTime + 61;
						m_fJumpingHeight = 0;
						m_fStartJumpingTerrainZ = m_fTerrainZ;
						m_bJumping = TRUE;
						m_dwStartJumpingTime = g_dwLastFrameBeginTime + 61;
					}
					else
					{
						g_dwTheRoleSlipStartTime -= (int)(fTheta*62);
					}
				}
			}
			else
			{
				if( m_bInFloor )
				{
					g_dwTheRoleSlipStartTime = g_dwLastFrameBeginTime;
				}
			}
		}
	}
	unguard;
}

void CPlayer::UpdateAnimSetting()
{
	guardfunc;
	if( m_bIsCurFreeze )
		return;

	if( !m_pAnim )
	{
#ifdef NEW_PLAYER_LOAD
		UpdateFakeWorldBBox(m_x, m_y, m_z);
#endif
		return;
	}
	if( !IsNpc() )
		m_bHasUpdateAnim = true;
	else if( m_bNpcGetBodySize )
		m_bHasUpdateAnim = true;

	//���ö�����С
	//float s = 1.0f;
	//if( m_pAnim->GetMexCfg() )
	//	s = m_pAnim->GetMexCfg()->m_mdlScale.m_npScale.GetNumber()/100.0f;

	// �������
	//s *= Config::m_fMdlSpaceScale*m_fPlayerScale;
	//s *= ( (GetBodySize() + m_fGrowSize*0.1f) );
	float playerScale = 1;
	if (mIsYabiaoState)
		playerScale = mBiaoCheScale;
	else
		playerScale = PlayerInfoMgr::Instance()->GetScaleForPlayer(this, false);

	if( m_bMounting )
	{
		m_pAnim->SetRotationZ( m_fLowerBodyDir + D3DX_PI/2 );
		m_pAnim->SetUpperRot( m_fUpperBodyDir + D3DX_PI/2 );
		m_pAnim->SetLowerRot( m_fLowerBodyDir + D3DX_PI/2 );

		if( m_pMountAnim )
		{
			if( m_bMoving )
			{
				m_pMountAnim->SetRotationZ( m_fLowerBodyDir + D3DX_PI/2 );
				m_pMountAnim->SetUpperRot( m_fLowerBodyDir + D3DX_PI/2 );
				m_pMountAnim->SetLowerRot( m_fLowerBodyDir + D3DX_PI/2 );
			}
			else
			{
				m_pMountAnim->SetRotationZ( m_fLowerBodyDir + D3DX_PI/2 );
				m_pMountAnim->SetUpperRot( m_fLowerBodyDir + D3DX_PI/2 );
				m_pMountAnim->SetLowerRot( m_fLowerBodyDir + D3DX_PI/2 );
			}
		}

		//���ö�����С
		//float fMountScale = 1.0f;
		//if( m_pAnim->GetMexCfg() )
		//	fMountScale = m_pAnim->GetMexCfg()->m_mdlScale.m_npScale.GetNumber()/100.0f;
		float fMountScale = PlayerInfoMgr::Instance()->GetScaleForMounting(this);

		if( m_pMountAnim )
		{
			m_pMountAnim->SetRotationX( m_fCurRotationX );
			m_pMountAnim->SetScale( fMountScale );
			m_pMountAnim->SetPosition( m_x, m_y, m_z );
			m_pMountAnim->CalcTransformMatrix( (MeMatrix*)&m_matTransform );
			m_pMountAnim->Update( HQ_TimeGetTime(), (MeMatrix*)&m_matTransform );
			m_pMountAnim->UpdateComponents( HQ_TimeGetTime(), (MeMatrix*)&m_matTransform );
		}

		UpdateTaliman(HQ_TimeGetTime());

		m_pAnim->SetScale( playerScale * m_fRiderScaleCorrect );

		BOOL bChangeLowerAnim = m_pAnim->UpdateSpineBonePosOffset( HQ_TimeGetTime(), (MeMatrix*)&m_matTransform );
		if( bChangeLowerAnim )
		{
			m_pAnim->SetPlayTargetAnim();
		}

		Vector vMountPos = Vector(m_x, m_y, m_z);
		guard(MountAnimGetBoneWorldPos);
		if( m_nMountBoneID == MEX2NOTLOADINGCOMPLETE && m_pMountAnim->GetMex() )
		{
			m_nMountBoneID = m_pMountAnim->GetMex()->GetSkeleton()->FindBone( "Mount" );
		}
		unguard;

		BOOL bGetMountData = FALSE;
		if( m_nMountBoneID != MEX2NOTLOADINGCOMPLETE )
		{
			vMountPos = m_pMountAnim->GetBoneWorldPos( m_nMountBoneID, &bGetMountData );

			if( bGetMountData )
			{
				D3DXMATRIX pmatTransform = m_pMountAnim->GetBoneMatrices( m_nMountBoneID, &bGetMountData );
				if( bGetMountData )
				{
					m_matTransform = pmatTransform;

					//lyh++ ע�����漸�� ��Ӱ���Զ��һ�ʱ ����������������bug
					float fXOff = m_pAnim->GetSpineBonePosOffset().x;
					float fYOff = m_pAnim->GetSpineBonePosOffset().y;
					float fZOff = m_pAnim->GetSpineBonePosOffset().z;
					m_matTransform._41 = m_matTransform._41 - fXOff;
					m_matTransform._42 = m_matTransform._42 - fYOff;
					m_matTransform._43 = m_matTransform._43 - fZOff;

					m_pAnim->SetPosition( m_matTransform._41, m_matTransform._42, m_matTransform._43 );
					m_pAnim->CalcTransformMatrix( (MeMatrix*)&m_matTransform );
					m_pAnim->UpdateWorldBBox( (MeMatrix*)&m_matTransform );
				}
			}
		}
		if( !bGetMountData )
		{
			vMountPos = Vector(m_x, m_y, m_z);
			m_pAnim->SetPosition( vMountPos.x, vMountPos.y, vMountPos.z );
			m_pAnim->CalcTransformMatrix( (MeMatrix*)&m_matTransform );
			m_pAnim->UpdateWorldBBox( (MeMatrix*)&m_matTransform );
		}
	}
	else
	{
		if( GetMonsterType() != eMT_Building )
		{
			{
				m_pAnim->SetRotationZ( m_fLowerBodyDir + D3DX_PI/2 );
				m_pAnim->SetUpperRot( m_fUpperBodyDir + D3DX_PI/2 );
				m_pAnim->SetLowerRot( m_fLowerBodyDir + D3DX_PI/2 );
			}
		}

		if( m_bMorphing && m_pMorphAnim )
		{
			//             if(m_nMorphMonsterID != -1&&m_pMorphAnim->GetMex() == NULL)
			//             {
			//                 ItemDefine::SMonster *pMonster = GettheItemDetail().GetMonsterById(m_nMorphMonsterID);
			//                 if(pMonster)
			// 				{
			//                    m_pMorphAnim->MyChangeModel(pMonster->iModelID,true,NULL);
			// 				   m_bMorphInThread = true;
			// 				}
			//             }

			m_pMorphAnim->SetRotationZ( m_fLowerBodyDir + D3DX_PI/2 );
			m_pMorphAnim->SetUpperRot( m_fLowerBodyDir + D3DX_PI/2 );
			m_pMorphAnim->SetLowerRot( m_fLowerBodyDir + D3DX_PI/2 );
			m_pMorphAnim->SetRotationX( m_fCurRotationX );
			m_pMorphAnim->SetScale( playerScale );
			if (!m_bOpenPrivateShop)
				m_pMorphAnim->SetPosition( m_x, m_y, m_z );
			m_pMorphAnim->CalcTransformMatrix( (MeMatrix*)&m_matTransform );
			m_pMorphAnim->Update( g_dwLastFrameBeginTime, (MeMatrix*)&m_matTransform );
			m_pMorphAnim->UpdateComponents( HQ_TimeGetTime(), (MeMatrix*)&m_matTransform );
		}
		UpdateTaliman(HQ_TimeGetTime());

		//�Ƿ��ڴ�������
		if(IsCarrierint())
		{
			CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nCarrierDriver);
			if(pPlayer)
			{
				CPlayerAnim *pAnim = NULL;
				if ( IsOthersPet() == false )
				{
					pAnim = pPlayer->GetAnim();
				}
				else
				{
					pAnim = pPlayer->GetMountAnim();
				}

				if(pAnim)
				{
					char szWord[256] = {0};
					MeSprintf_s(szWord,sizeof(szWord),"mount00%d",m_nCarrierID);
					if(pAnim->GetMex())
					{
						BOOL bGetMountData = FALSE;
						Vector vPos = Vector(m_x, m_y, m_z);
						int nBoneID = pAnim->GetMex()->GetSkeleton()->FindBone(szWord);
						if(nBoneID != -1)
						{
							//����λ��
							vPos = pAnim->GetBoneWorldPos(nBoneID,&bGetMountData);
							SetPos(vPos.x,vPos.y,vPos.z);

							//���õ�ǰ����
							float fLowDir = pPlayer->GetCurLowerDir();
							float fUpperDir = pPlayer->GetCurUpperDir();

							m_pAnim->SetRotationZ(fLowDir + D3DX_PI/2 );
							m_pAnim->SetUpperRot(fUpperDir + D3DX_PI/2 );
							m_pAnim->SetLowerRot(fLowDir + D3DX_PI/2 );


							//if (GetMountAnim())
							//{
							//	GetMountAnim()->SetRotationZ(fLowDir + D3DX_PI/2 );
							//	GetMountAnim()->SetUpperRot(fLowDir + D3DX_PI/2 );
							//	GetMountAnim()->SetLowerRot(fLowDir + D3DX_PI/2 );
							//	GetMountAnim()->CalcTransformMatrix( (MeMatrix*)&m_matTransform );
							//	GetMountAnim()->Update( HQ_TimeGetTime(), (MeMatrix*)&m_matTransform );
							//	GetMountAnim()->UpdateComponents( HQ_TimeGetTime(), (MeMatrix*)&m_matTransform );
							//} 

							float f;
							pPlayer->GetDir(&f);
							SetDir(f);
							SetCurDir(f);
							SetUpperDir(f);
							SetLowerDir(f);
							SetCurUpperDir(f);
							SetCurLowerDir(f);

							if(pPlayer->IsMoving()&&g_dwLastFrameBeginTime - thePlayerRole.GetStartCollectPosTime() >= 100)
							{

								//�ҵ�˾�����ƶ�������Ҳ�����ƶ�
								if(GetCarrierPlayerID() == pPlayer->GetID() && 
									this != pPlayer &&
									theHeroGame.GetPlayerMgr() &&
									theHeroGame.GetPlayerMgr()->GetMe() &&
									theHeroGame.GetPlayerMgr()->GetMe()->GetCarrierPlayerID() == pPlayer->GetID())
								{
									MsgPlayerPosAndDirToServer msg;
									msg.header.stID = GetID();
									msg.header.uMsgLevel = level_high;
									msg.vPos.x = pPlayer->GetPos().x;
									msg.vPos.y = pPlayer->GetPos().y;
									msg.vPos.z = pPlayer->GetPos().z;
									msg.chDirX = (char)(m_vCurDir.x*127);
									msg.chDirY = (char)(m_vCurDir.y*127);
									msg.chDirZ = 0;
									msg.dwSendTime = HQ_TimeGetTime();
									GettheNetworkInput().SendMsg( &msg );
								}

								thePlayerRole.SetStartCollectPosTime(g_dwLastFrameBeginTime);
							}
						}
					}
				}
			}
		}

		m_pAnim->SetScale( playerScale );
		m_pAnim->SetPosition( m_x, m_y, m_z );

		D3DXMATRIX matRot;

		if( !IsMonster() )
		{
			if( IsDead() )
			{
				D3DXVECTOR3 vUp( 0, 0, 1 );
				{
					m_vCurNormal = m_vCurNormal + ( m_vTargetNormal - m_vCurNormal )*0.002f*g_dwLastFrameCostTime;
				}

				D3DXVec3Normalize( &m_vCurNormal, &m_vCurNormal );
				BuildMatrixFromVectorToVector( (float*)&m_vCurNormal, (float*)&vUp, (float*)&matRot );
				m_pAnim->CalcTransformMatrix( (MeMatrix*)&m_matTransform );

				m_matTransform._41 = 0;
				m_matTransform._42 = 0;
				m_matTransform._43 = 0;

				D3DXMatrixMultiply( &m_matTransform, &m_matTransform, &matRot );

				m_matTransform._41 = m_x;
				m_matTransform._42 = m_y;
				m_matTransform._43 = m_z;
			}
			else
			{
				m_pAnim->CalcTransformMatrix( (MeMatrix*)&m_matTransform );
			}
		}
		else
		{
			if( m_bFourFoot )
			{
				D3DXVECTOR3 vAxis( 0, 0, 1 );
				if( !IsInWater() && !m_bInFloor && !m_bJumping )
				{
					GetZByXY( m_z +	38.2f*Config::m_fMdlSpaceScale, m_x, m_y, 0,NULL, NULL,false,&vAxis );
				}
				D3DXVECTOR3 vUp( 0, 0, 1 );
				D3DXVec3Normalize( &vAxis, &vAxis );

				BuildMatrixFromVectorToVector( (float*)&vAxis, (float*)&vUp, (float*)&matRot );
				m_pAnim->CalcTransformMatrix( (MeMatrix*)&m_matTransform );

				m_matTransform._41 = 0;
				m_matTransform._42 = 0;
				m_matTransform._43 = 0;

				D3DXMatrixMultiply( &m_matTransform, &m_matTransform, &matRot );

				m_matTransform._41 = m_x;
				m_matTransform._42 = m_y;
				m_matTransform._43 = m_z;
			}
			else if( IsDead() )
			{
				D3DXVECTOR3 vUp( 0, 0, 1 );

				{
					m_vCurNormal = m_vCurNormal + ( m_vTargetNormal - m_vCurNormal )*0.002f*g_dwLastFrameCostTime;
				}

				D3DXVec3Normalize( &m_vCurNormal, &m_vCurNormal );
				BuildMatrixFromVectorToVector( (float*)&m_vCurNormal, (float*)&vUp, (float*)&matRot );
				m_pAnim->CalcTransformMatrix( (MeMatrix*)&m_matTransform );

				m_matTransform._41 = 0;
				m_matTransform._42 = 0;
				m_matTransform._43 = 0;

				D3DXMatrixMultiply( &m_matTransform, &m_matTransform, &matRot );

				m_matTransform._41 = m_x;
				m_matTransform._42 = m_y;
				m_matTransform._43 = m_z;
			}
			else
			{
				m_pAnim->CalcTransformMatrix( (MeMatrix*)&m_matTransform );
			}
		}
		m_pAnim->UpdateWorldBBox( (MeMatrix*)&m_matTransform );
	}

	DWORD dwTime = HQ_TimeGetTime();
	BOOL bUpperAnimPlayOver;
	m_pAnim->Update( dwTime, (MeMatrix*)&m_matTransform, &bUpperAnimPlayOver );
	m_pAnim->UpdateComponents( dwTime, (MeMatrix*)&m_matTransform );

	if( (bUpperAnimPlayOver || m_pAnim->IsUpperAnimPlayOver()) && m_bPendingClearFightFlag && 0 == m_actionQueue.GetAttackActionNum())
	{
		// ��ս����ض���
		ClearFightFlag( eFighting );
		if ( this == theHeroGame.GetPlayerMgr()->GetMe() )
		{
			thePlayerRole.SetFighting( false );
			s_CUI_ID_FRAME_MAIN.RefeashHotKey();
			s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Status_Fight, theXmlString.GetString( eText_ExitFight ) );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_ExitFight ) );
			//s_CUI_ID_FRAME_Group_Me.PICTURE_Zhandou_SetVisable( false );
		}
		m_bPendingClearFightFlag = FALSE;
	}

	unguard;
}

void CPlayer::UpdateNpcTips()
{
	guardfunc;
	if( IsNpc() && m_bNeedRender )
	{
		char acCost[256] = {0};
		DWORD dwTimeCost = HQ_TimeGetTime();

		int nImageType = -1;

		if( !m_pNpcCoordInfo )
		{
			//ͨ��NPCID����
			const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(GetNpcID());
			m_pNpcCoordInfo = const_cast<NpcCoordInfo*>( pInfo );
		}
		//const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(GetName());
		if( m_pNpcCoordInfo )
		{
			nImageType = GetAdvancedMiniMap()->GetImageMap(m_pNpcCoordInfo->_nType);
		}

		int nNpcTipsType = theApp->GetPlayerMgr()->UpdateNpcTipsType( m_pNpcCoordInfo );
		{
			if(m_pNpcCoordInfo&&m_pNpcCoordInfo->_nType == eNT_SpecialNpc  ) 
			{
				if(!IsHide() && !IsNpcShowProcessing())
				{
					SetHide(true);
				}


				if(GetNpcTipsType() != nNpcTipsType)//npc tipsType �б仯���¼�仯ʱ��
				{	
					m_dwNpcBeginTime = HQ_TimeGetTime(); //��¼�仯ʱ��
				}
			}

			SetNpcTipsType( nNpcTipsType );

			if(m_pNpcCoordInfo&&m_pNpcCoordInfo->_nType == eNT_SpecialNpc)
			{
				ProcessNpcHideOrShow(nNpcTipsType);
			}

			// ������Ч
			// û��tips 
			if( m_nNpcTipsType != CPlayerMgr::eNpcTips_None )
			{
				{
					switch( m_nNpcTipsType )
					{
					case CPlayerMgr::eNpcTips_HaveQuest:
						nImageType = CAdvancedMiniMap::eImage_YellowGanTanHao;
						break;
					case CPlayerMgr::eNpcTips_HaveQuestNotNow:
						nImageType = CAdvancedMiniMap::eImage_WhiteGanTanHao;
						break;
					case CPlayerMgr::eNpcTips_QuestDone:
						nImageType = CAdvancedMiniMap::eImage_YellowWenHao;
						break;
					case CPlayerMgr::eNpcTips_QuestNotDone:
						nImageType = CAdvancedMiniMap::eImage_WhiteWenHao;
						break;
					default:
						return;
					}
				}
			}
		}
		dwTimeCost = HQ_TimeGetTime() - dwTimeCost;
		sprintf_s( acCost, 256, "\n Upate NPC Tips 11111 %d", dwTimeCost );
		if( dwTimeCost > 10 )
			OutputDebugStringA( acCost );
		dwTimeCost = HQ_TimeGetTime();

		if (m_nImageType != nImageType || (m_nImageType != -1 && GetEffectMgr()->GetEffectByPlayerID(GetID()) == -1))
		{
			m_nImageType = nImageType;
			//���ԭ����
			if( m_pCharEffectContainer )
			{
				m_pCharEffectContainer->ClearEffect( CCharEffectContainer::eNpcTip );
			}
			if (m_nImageType != -1)
			{
				CAdvancedMiniMap::Image* pImage = GetAdvancedMiniMap()->GetImage(m_nImageType);
				if (pImage->strEffectPath.length()!= 0)
				{
					CWSModelEffect* pEffect = MeNew CWSModelEffect;
					if( GetEffectMgr()->RegisterEffect( pEffect ) == -1 )
					{
						pEffect->Release();
						pEffect = NULL;
					}
					else
					{
						pEffect->SetPlayerID(this->GetID());
						pEffect->LoadSetting( GetFullFileName(pImage->strEffectPath.c_str()) );
						{
							GSound.PlaySound( GetFullFileName(pEffect->GetSound(Sex_Male == GetSex())),false, &GetPos(),3,15 );
						}
						CastModelEffect( pEffect, NULL, CCharEffectContainer::eNpcTip );
					}
				}
			}
			dwTimeCost = HQ_TimeGetTime() - dwTimeCost;
			sprintf_s( acCost, 256, "\n Update NPC Tips 22222 %d", dwTimeCost );
			if( dwTimeCost > 10 )
				OutputDebugStringA( acCost );
			dwTimeCost = HQ_TimeGetTime();
		}
	}
	unguard;
}

void CPlayer::UpdateRenderAlpha()
{
	guardfunc;
	if( m_pAnim )
	{
		if( !m_pAnim->ChangeAllEquipComplete() )
			return;
	}

	if( m_fCurRenderAlpha == m_fFinalRenderAlpha )
	{
		return;
	}

	//���������ʱ���͸����
	if( m_fCurRenderAlpha < m_fFinalRenderAlpha )
	{
		m_fCurRenderAlpha += 0.000618f*g_dwLastFrameCostTime;
		if( m_fCurRenderAlpha > m_fFinalRenderAlpha )
		{
			m_fCurRenderAlpha = m_fFinalRenderAlpha;
		}
	}

	if( m_fCurRenderAlpha > m_fFinalRenderAlpha )
	{
		m_fCurRenderAlpha -= 0.000618f*g_dwLastFrameCostTime;
		if( m_fCurRenderAlpha < m_fFinalRenderAlpha )
		{
			m_fCurRenderAlpha = m_fFinalRenderAlpha;
		}
		if( GetMonsterType() == eMT_IllusionMonster )
		{
			if( m_fCurRenderAlpha == m_fFinalRenderAlpha )
			{
				Remove(HQ_TimeGetTime());
			}
		}
	}
	unguard;
}

void CPlayer::UpdateStatusColor()
{
	guardfunc;
	if( m_vCurStatusColor == m_vFinStatusColor )
	{
		if( m_vCurStatusColor.x == 0 &&
			m_vCurStatusColor.y == 0 &&
			m_vCurStatusColor.z == 0 )
		{
			if( m_pCharEffectContainer && !m_pCharEffectContainer->IsStateLightClosed() )
				m_pCharEffectContainer->ClearStateLight();
		}
		return;
	}
	else
	{
		/////////////////////COLORX
		if( m_vCurStatusColor.x < m_vFinStatusColor.x )
		{
			m_vCurStatusColor.x += 0.000618f*g_dwLastFrameCostTime;
			if( m_vCurStatusColor.x > m_vFinStatusColor.x )
			{
				m_vCurStatusColor.x = m_vFinStatusColor.x;
			}
		}

		if( m_vCurStatusColor.x > m_vFinStatusColor.x )
		{
			m_vCurStatusColor.x -= 0.000618f*g_dwLastFrameCostTime;
			if( m_vCurStatusColor.x < m_vFinStatusColor.x )
			{
				m_vCurStatusColor.x = m_vFinStatusColor.x;
			}
		}

		/////////////////////COLORY
		if( m_vCurStatusColor.y < m_vFinStatusColor.y )
		{
			m_vCurStatusColor.y += 0.000618f*g_dwLastFrameCostTime;
			if( m_vCurStatusColor.y > m_vFinStatusColor.y )
			{
				m_vCurStatusColor.y = m_vFinStatusColor.y;
			}
		}

		if( m_vCurStatusColor.y > m_vFinStatusColor.y )
		{
			m_vCurStatusColor.y -= 0.000618f*g_dwLastFrameCostTime;
			if( m_vCurStatusColor.y < m_vFinStatusColor.y )
			{
				m_vCurStatusColor.y = m_vFinStatusColor.y;
			}
		}

		/////////////////////COLORZ
		if( m_vCurStatusColor.z < m_vFinStatusColor.z )
		{
			m_vCurStatusColor.z += 0.000618f*g_dwLastFrameCostTime;
			if( m_vCurStatusColor.z > m_vFinStatusColor.z )
			{
				m_vCurStatusColor.z = m_vFinStatusColor.z;
			}
		}

		if( m_vCurStatusColor.z > m_vFinStatusColor.z )
		{
			m_vCurStatusColor.z -= 0.000618f*g_dwLastFrameCostTime;
			if( m_vCurStatusColor.z < m_vFinStatusColor.z )
			{
				m_vCurStatusColor.z = m_vFinStatusColor.z;
			}
		}

		if( m_pCharEffectContainer )
		{
			m_pCharEffectContainer->OpenStateLight( 0x00ffffff, m_vCurStatusColor.x, m_vCurStatusColor.y, m_vCurStatusColor.z );
		}
	}
	unguard;
}

void CPlayer::Update( DWORD time)
{
	ProfilePlayerFun
		guardfunc;

	//���˲���Ҫ�ڸ���������
	if( m_bDeadOver && !m_bIsActivePlayer )
	{
		return;
	}

	// ������һ��ʱ���ڵ���UpdateAnimSetting�������ͼ�����档
	if ( !m_bNeedRender )
	{
		updateAnimNotRender();
		return;
	}

	// ����ƶ��ٶȱ仯�����������˶�״̬�����Ķ���Ƶ��
	if( m_bMoveRateChange )
	{
		if( IsMoving() && !m_bMounting && m_pAnim )
		{
			if( IsInWater() )
			{
				if( !m_bCountermarch )
				{
					m_pAnim->ClearLowerBodyAnims();
					m_pAnim->SetCurAnimType(-1);
					SwitchSwimAnim();
				}
			}
			else
			{
				if( m_bCountermarch )
				{
					m_pAnim->ClearLowerBodyAnims();
					m_pAnim->SetCurAnimType(-1);
					SwitchWalkBackWardsAnim();
				}
				else
				{
					if( CanSwitchRunAnim() )
					{
						m_pAnim->ClearLowerBodyAnims();
						m_pAnim->SetCurAnimType(-1);
						SwitchRunAnim();
					}
				}
			}

		}
		m_bMoveRateChange = FALSE;
	}
	//  [12/3/2010 zhangjiayi]
	PlayAnimWithActionID();

	ShowChatPaoPao();

	//////������Ҫ��״̬����ͼЧ��
	AnimCorrectProcess();
	RoleOperationProcess();
	TurnAroundProcess();		//��û�Ż�
	SoundProcess();
	RoleSlipProcess();		//��û�Ż�


	if( m_bRole )
	{
		if (s_CUI_ID_FRAME_Target.GetFollowPlayerId() != -1)
		{
			CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(s_CUI_ID_FRAME_Target.GetFollowPlayerId());
			if (pPlayer && pPlayer->GetDistanceToRole() > pPlayer->GetBodyLengthSize() + GetBodyLengthSize() + 2.f)
			{
				g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
				theHeroGame.GetPlayerMgr()->MoveRoleToPlayer( pPlayer, TRUE, 0.f, TRUE );
			}
		}

		if ( s_CUI_ID_FRAME_Team.GetTeamFollowID() != -1 )
		{
			CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(s_CUI_ID_FRAME_Team.GetTeamFollowID());
			if ( pPlayer && pPlayer->GetDistanceToRole() > pPlayer->GetBodyLengthSize() + GetBodyLengthSize() + 2.f )
			{
				g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
				m_vTeamFollowLastPos = pPlayer->GetPos();
				theHeroGame.GetPlayerMgr()->MoveRoleToPlayer( pPlayer, TRUE, -1.0f, TRUE );
			}
			else if ( pPlayer == NULL )	//����Ҳ���ͬ������Χ�ڵ�ʱ�򣬿��ͼ�Ǻ��������������
			{
				theHeroGame.GetPlayerMgr()->MoveRoleTo( m_vTeamFollowLastPos.x, m_vTeamFollowLastPos.y, false, false, false, true );
			}

			TurnCameraToPlayer( time );
		}

		UpdateAnimSetting();

		if( m_bLoggingMovePath )
			LoggingMovePath();

		if( m_vctAdvanceSkill.size() )
		{
			std::vector<SAdvanceSkillData>::iterator iter;
			for(iter = m_vctAdvanceSkill.begin(); iter != m_vctAdvanceSkill.end(); )
			{
				SAdvanceSkillData kAdvSkillData = *iter;
				if( HQ_TimeGetTime() - kAdvSkillData.dwBeginFrameTime > 3000/*5000*/ )
				{//5���ӳ�̫��,���׸о���,�ĳ�3�뿴�� by vvx 2013.11.22
					iter = m_vctAdvanceSkill.erase(iter);
				}
				else
					++iter;
			}
		}
	}
	else if ( m_pAnim )
	{
#if USE_ANIMATION_OPTIMIZATION
		DWORD dwTime = HQ_TimeGetTime();
		int nUpdateStep = m_fDistanceToRole - 40;

		if( nUpdateStep < 0 )
			nUpdateStep = 0;

		if( !m_bNeedRender || nUpdateStep > 20 )
			nUpdateStep = 20;

		if( m_pAnim->GetMex() && dwTime - m_dwLastUpdateAnimTime >= nUpdateStep*10 )
		{
			UpdateAnimSetting();		//��û�Ż�
			m_dwLastUpdateAnimTime = dwTime;
		}
#elif USE_ANIMATION_OPTIMIZATION_FORCE
		DWORD dwTime = HQ_TimeGetTime();
		int nUpdateStep = theHeroGame.GetPlayerMgr()->GetUpdateAnimTimeStep();

		if( nUpdateStep < 0 )
			nUpdateStep = 0;

		if( !m_bNeedRender )
			nUpdateStep = 200;

		if( m_pAnim->GetMex() && dwTime - m_dwLastUpdateAnimTime >= nUpdateStep )
		{
			UpdateAnimSetting();		//��û�Ż�
			m_dwLastUpdateAnimTime = dwTime;
		}
		m_pAnim->UpdateWorldBBox( (MeMatrix*)&m_matTransform );//lyh++ ʵʱ���°�Χ�� ��Ϊ�˽�� ����� ��Ȼ�� �������ȵ� ���˵����ֻ���
#else
		UpdateAnimSetting();		//��û�Ż�
		m_dwLastUpdateAnimTime = dwTime;
#endif
	}
	UpdateNpcTips();
	SpecialIdleTimeProcess();
	UpdateStatusColor();
	UpdateEffectHelper();

	if( m_bRole )
	{
		GSound.UpdatePos( GetPos(), m_vCurDir );
		UpdateWaterEffect();
	}
	UpdateFullStarEffect();
	UpdateFiveElementEffect();

	//UpdateFightPowerEffect();
	UpdateIntonateDirection();

	// ������������       added by ZhuoMeng.Hu		[1/9/2011]
	UpdateMeDirInFighting();

	ProcessSceneSegment();

	SwitchDropItemAnim();
	// 	if (IsItem())
	// 	{
	// 		m_pAnim->PlayAnimByActionName( "box_drop",
	// 			MexAnimCtrl::eNormalPlay,
	// 			0,
	// 			1,
	// 			MexAnimCtrl::eMaxTimeout,
	// 			MexAnimCtrl::eDefaultBlendingTime,
	// 			"box_stand",
	// 			MexAnimCtrl::eNormalPlay );
	// 	}
	if(this == theHeroGame.GetPlayerMgr()->GetMe())
	{
		if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
		{
			s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().Process();
		}
		else
		{
			/*
			*	Author 2012-9-15 zhuxincong
			*	DESC: ��������Ϸ���ж��ǲ����ڱ���״̬������HP��MP ���˶��پ��Լ�������Ѫ
			*/
			if (s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsProtection())
			{
				s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().ProcessRecover();
			}
			/*
			*	Author 2012-9-24 zhuxincong
			*	DESC: ��������Ϸ���ж��Ƿ��Զ�ʰȡ
			*/

			if (s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsPick())
			{
				s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().ProcessAutoPick();
			}
		}
	}
	unguard;
}

void CPlayer::SetExPower( int nExPower )
{
	m_nFPCurrentBallCount = nExPower / ( m_nFPTotal / m_nFPTotalBall );

	if( ( m_nExPower / ( m_nFPTotal / m_nFPTotalBall ) ) != m_nFPCurrentBallCount ) //�����������仯
		m_bUpdateExPowerEff = true;

	m_nExPower = nExPower; 
}

void CPlayer::CalcMinimalStar()
{
	m_nMinimalStar = 0xff;
	for( int iLoop = 0 ; iLoop < EEquipPartType_MaxEquitPart ; ++ iLoop)
	{	
		if (iLoop == EEquipPartType_Badge || 
			//iLoop == /*EEquipPartType_Manteau*/EEquipPartType_Shoulder || //�»������ļ��ҪӰ��������Ч��
			iLoop == EEquipPartType_LeaderCard || 
			iLoop == EEquipPartType_Amulet || 
			iLoop == EEquipPartType_AecorativeGoods || 
			iLoop == EEquipPartType_AecorativeClothing)
		{
			continue;
		}

		int nPart = CEquipPartMap::Instance()->GetLogicPart(iLoop);
		int nLevel = m_equips[nPart].item.equipdata.ucLevel;
		if( nLevel < 0 || nLevel > SCharItem::EL_Max )
			continue;

		if( m_equips[nPart].item.itembaseinfo.ustItemID == InvalidLogicNumber )//û��װ��
			nLevel = 0;
		m_nMinimalStar = min( m_nMinimalStar, nLevel );
	}
	if( m_nMinimalStar >= m_nBaseStarCount )//���ϳ���Ч������Ǽ�
		m_bUpdateFullStarEffect = true;
	else
		m_bUpdateFullStarEffect = false;

	// ��������
	UpdateMainElement();
}

bool CPlayer::LoadFullStarEffect(const char* name, int& iRetEffectID, int& iRetEffectContainerID )
{
	bool bRet = false;
	if( !name || name[0] == '\0' )
		return bRet;

	CWSModelEffect* pEffect = MeNew CWSModelEffect;
	char szName[256] = {0};
	MeSprintf_s(szName, sizeof(szName)/sizeof(char) -1, "data\\effect\\common\\%s", name);
	if( pEffect->LoadSetting( GetFullFileName(szName) ) )
	{
		iRetEffectID = GetEffectMgr()->RegisterEffect( pEffect );
		if( iRetEffectID == -1 )
		{
			pEffect->Release();
			bRet = false;
		}
		else
		{
			iRetEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
			pEffect->m_dwBornTime = HQ_TimeGetTime();
			float fRadius = pEffect->m_fRadius;
			int nNum = pEffect->m_nNumInstance;

			CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( iRetEffectContainerID );

			for( int nInst = 0; nInst < nNum; nInst++ )
			{
				CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
				if( !pInstance )
				{
					continue;
				}

				pInstance->dwBornTime = HQ_TimeGetTime() + /*pEffect->m_dwDelay*nInst*/pInstance->fDelay;

				if( pEffectContainer )
				{
					pEffect->SetEffectQuoter( pEffectContainer );
				}

				pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
				pInstance->vPos = pInstance->vBornPos;
				pInstance->bVisible = FALSE;

				// ����Ч��
				if( pEffectContainer )
				{
					pInstance->pMaster = pEffectContainer->GetEffectHelper( pInstance->nBindWhere );
				}
			}

			if( pEffectContainer )
			{
				pEffectContainer->ApplyEffect( 0, pEffect->GetID() );
			}
			bRet = true;
		}
	}
	else
	{
		pEffect->Release();
		bRet = false;
	}
	pEffect = NULL;
	return bRet;
}

void CPlayer::HideFullStarEffect(int iEffectID)
{
	CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( iEffectID );
	if( pModelEffect )
	{
		int nNum = pModelEffect->m_nNumInstance;
		for( int nInst = 0; nInst < nNum; nInst++ )
		{
			CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

			if( !pInstance )
				continue;

			pInstance->bVisible = false;
		}						
	}
}

void CPlayer::ShowFullStarEffect(float x, float y, bool setScale, float scale, int iEffectID, int iEffectContainerID, int iInstance)
{
	CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( iEffectID );
	if( pModelEffect )
	{
		if( iInstance >= 0 && iInstance < 4 )
		{
			CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( iInstance );			

			if( !pInstance )
				return;

			pInstance->bVisible = true;
			pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
			if (setScale)
				pInstance->fScale = scale;
		}
	}

	CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( iEffectContainerID );
	if( pEffectContainer && m_pCharEffectContainer )
	{
		IEffectHelper* pEffectHelper = NULL;
		float afBody[3] = {0.f};
		m_pCharEffectContainer->GetEffectHelper( eEffectBindPart_Body )->GetPos( afBody );

		pEffectHelper = pEffectContainer->GetEffectHelper( eEffectBindPart_Body );
		pEffectHelper->SetPos( x, y, afBody[2] );			
	}
}

void CPlayer::UpdateFullStarEffect()
{
	return;
	if( !m_bUpdateFullStarEffect || m_cFightStatus.IsHide() || !theHeroGame.GetPlayerMgr()->IsPlayerCanRender( this ))// ����״̬Ҳ����ʾ
	{
		HideFullStarEffect(m_nFullStarEffectID);
		HideFullStarEffect(m_nFullStarEffectID2);
		return;
	}

	_UpdateFullStarEffect(m_x, m_y);
}

void CPlayer::_UpdateFullStarEffect(float x, float y, bool setScale, float scale)
{
	if (GetEffectID() == -1) return;
	if(strcmp(m_EffectName,"NULL") == 0) return;


	CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( GetEffectID() );
	if (pModelEffect)
	{
		int	InstanceNum = pModelEffect->m_nNumInstance;
		for(int i = 0 ; i < InstanceNum ; i++)
		{
			CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( i);			

			if( !pInstance )
				return;

			pInstance->bVisible = true;
			pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
			if (setScale)
				pInstance->fScale = scale;

		}		
	}


	//ShowFullStarEffect( x, y, setScale, scale, m_nFullStarEffectID, m_nFullStarEffectContainerID, m_nMinimalStar-m_nBaseStarCount );


	//if (!m_bUpdateFullStarEffect)
	//	return;

	//if( m_nFullStarEffectID == -1 )
	//{
	//	LoadFullStarEffect("FullStarEffect.ini", m_nFullStarEffectID, m_nFullStarEffectContainerID);
	//}
	//if( m_nFullStarEffectID2 == -1 )
	//{
	//	LoadFullStarEffect("FullStarEffect2.ini", m_nFullStarEffectID2, m_nFullStarEffectContainerID2);
	//}

	//HideFullStarEffect(m_nFullStarEffectID);
	//HideFullStarEffect(m_nFullStarEffectID2);

	//// update effect
	//if( m_nMinimalStar <= 10 )
	//	ShowFullStarEffect( x, y, setScale, scale, m_nFullStarEffectID, m_nFullStarEffectContainerID, m_nMinimalStar-m_nBaseStarCount );
	//else
	//{
	//	if( m_nMinimalStar < 13 )
	//		ShowFullStarEffect( x, y, setScale, scale, m_nFullStarEffectID2, m_nFullStarEffectContainerID2, m_nMinimalStar-m_nBaseStarCount -4 );
	//	else
	//		ShowFullStarEffect( x, y, setScale, scale, m_nFullStarEffectID2, m_nFullStarEffectContainerID2, 2 );
	//}
}

void CPlayer::UpdateFightPowerEffect()
{
	if( !m_bUpdateExPowerEff )
		return;

	if( m_nFightPowerEffectID == -1 && GetProfession() == EArmType_Mage /*����*/ )
	{
		CWSModelEffect* pEffect = MeNew CWSModelEffect;
		if( pEffect->LoadSetting( GetFullFileName("data\\effect\\common\\FightPowerEffect.ini") ) )
		{
			m_nFightPowerEffectID = GetEffectMgr()->RegisterEffect( pEffect );
			if( m_nFightPowerEffectID == -1 )
			{
				pEffect->Release();
			}
			else
			{
				m_nFightPowerEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
				pEffect->m_dwBornTime = HQ_TimeGetTime();
				float fRadius = pEffect->m_fRadius;
				int nNum = pEffect->m_nNumInstance;

				CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( m_nFightPowerEffectContainerID );

				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
					if( !pInstance )
					{
						continue;
					}

					pInstance->dwBornTime = HQ_TimeGetTime() + pInstance->fDelay;

					if( pEffectContainer )
					{
						pEffect->SetEffectQuoter( pEffectContainer );
					}

					pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
					pInstance->vPos = pInstance->vBornPos;
					pInstance->bVisible = FALSE;

					// ����Ч��
					if( pEffectContainer )
					{
						pInstance->pMaster = pEffectContainer->GetEffectHelper( pInstance->nBindWhere );
					}
				}

				if( pEffectContainer )
				{
					pEffectContainer->ApplyEffect( 0, pEffect->GetID() );
				}
			}
		}
		else
		{
			pEffect->Release();
		}
		pEffect = NULL;
	}

	// update effect
	if( GetProfession() == EArmType_Mage )
	{
		CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( m_nFightPowerEffectID );
		if( pModelEffect )
		{
			int nNum = pModelEffect->m_nNumInstance;
			for( int nInst = 0; nInst < nNum; nInst++ )
			{
				CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

				if( !pInstance )
					continue;

				pInstance->bVisible = false;
			}

			if( m_nFPCurrentBallCount == 0 ) // û�ж�����
				return;

			assert( m_nFPCurrentBallCount <= 4 && "������������" );
			CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( m_nFPCurrentBallCount - 1 );
			assert( pInstance && "��������Ч���ô���" );

			if( !pInstance )
				return;

			pInstance->bVisible = true;
			pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;

		}

		CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( m_nFightPowerEffectContainerID );
		if( pEffectContainer )
		{
			float fEffectHelperZ = m_z;
			IEffectHelper* pEffectHelper = NULL;

			pEffectHelper = pEffectContainer->GetEffectHelper( eEffectBindPart_Body );
			pEffectHelper->SetPos( m_x, m_y, fEffectHelperZ );
		}
	}
}

bool CPlayer::IsIntonatingTargetExist()
{
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( GetIntonatingTargetID() );
	if( pPlayer && GetIntonatingTarget() && GetIntonatingTarget() == pPlayer )
		return true;

	return false;
}

void CPlayer::UpdateIntonateDirection()
{
	if( !m_bIntonating || !IsIntonatingTargetExist() )
		return;

	if( m_bRole )
		theHeroGame.GetPlayerMgr()->TurnRoleTo( GetIntonatingTarget() );
}

void CPlayer::UpdateMeDirInFighting()
{
	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return;

	// ���Լ�
	CPlayer* pMe = pPlayerMgr->GetMe();
	if( !pMe || GetID() != pMe->GetID() )
		return;

	// ��2.5D
	wsCamera* pCamera = getwsCamera();
	if( !pCamera || !getwsCamera()->GetLock45DegreeCameraMode() )
		return;

	// ��ս����
	if( !HasFightFlag( eFighting ) )
		return;

	// ��ԭ��״̬
	if( IsMoving() )
		return;

	int nTargetId = s_CUI_ID_FRAME_Target.GetPlayerID();
	if( nTargetId < 0 )
		return;

	CPlayer* pTarget = pPlayerMgr->FindByID( nTargetId );
	if( !pTarget )
		return;

	// ����ת���Լ�
	if( pTarget->GetID() == GetID() )
		return;

	pPlayerMgr->TurnRoleTo( pTarget );
}

void CPlayer::UpdateWaterEffect()
{
	guardfunc;
	if (IsUncontrolFlying()||IsCarrierint())
	{
		return;
	}
	if( m_bRole )
	{
		//ˮ�ߵ�����
		BOOL bOverWater = FALSE;
		float fWaterHeight = 0;
		float fRippleEffectScale = 0.8f;

		CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
		CWorldChunk* pChunk = pTile->GetChunkFromPos(m_x, m_y);

		if( pChunk && pChunk->GetLiquidId() != RES_INVALID_ID)
		{
			BOOL bFloor = FALSE;
			fWaterHeight = GetZByXY( WORLD_HEIGHT, m_x, m_y, 0 ,&bFloor);
			if( pChunk->GetLiquidHeight() > fWaterHeight )
			{
				fRippleEffectScale = 0.8f + (pChunk->GetLiquidHeight() - fWaterHeight);
				fWaterHeight = pChunk->GetLiquidHeight();
				bOverWater = TRUE;
			}
		}




		if( !m_bInWater && bOverWater && !m_bJumping )
		{
			LoadRippleEffect();
			CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( m_nWaterSideRippleEffectID );
			if( pModelEffect )
			{
				int nNum = pModelEffect->m_nNumInstance;
				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

					if( !pInstance )
						continue;

					if( !pInstance->bVisible )
					{
						pInstance->bVisible = TRUE;
						pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
					}

					if( pInstance->pEffectCtrl )
					{
						pInstance->fScale = fRippleEffectScale*GetMe3dConfig()->m_fMdlSpaceScale;
						if( !m_bMoving )
						{
							if( m_fWaterSideRippleEffectPlaySpeed > 0.15f )
							{
								m_fWaterSideRippleEffectPlaySpeed -= g_dwSmoothFrame*0.001f;
							}

							if( m_fWaterSideRippleEffectPlaySpeed < 0.15f )
								m_fWaterSideRippleEffectPlaySpeed = 0.15f;

							pInstance->pEffectCtrl->SetParticleEmitterPlaySpeed( m_fWaterSideRippleEffectPlaySpeed );
						}
						else
						{
							if( m_fWaterSideRippleEffectPlaySpeed < 1.0f )
							{
								m_fWaterSideRippleEffectPlaySpeed += g_dwSmoothFrame*0.001f;
							}

							if( m_fWaterSideRippleEffectPlaySpeed > 1.0f )
								m_fWaterSideRippleEffectPlaySpeed = 1.0f;

							pInstance->pEffectCtrl->SetParticleEmitterPlaySpeed( m_fWaterSideRippleEffectPlaySpeed );
						}
					}
				}
			}

			CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( m_nWaterSideRippleEffectContainerID );
			if( pEffectContainer )
			{
				float fEffectHelperZ = fWaterHeight;
				IEffectHelper* pEffectHelper = NULL;

				pEffectHelper = pEffectContainer->GetEffectHelper( eEffectBindPart_Body );
				pEffectHelper->SetPos( m_x, m_y, fEffectHelperZ );
				pEffectHelper->SetRot( m_dir + D3DX_PI/2 );
				pEffectHelper->SetFinalRenderAlpha( 0.3 );
			}
			m_dwWaterSideRippleEffectOverTime = HQ_TimeGetTime();
		}
		else if (m_dwWaterSideRippleEffectOverTime != 0)
		{
			if( HQ_TimeGetTime() - m_dwWaterSideRippleEffectOverTime > 1000 )
			{
				CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( m_nWaterSideRippleEffectID );
				if( pModelEffect )
				{
					int nNum = pModelEffect->m_nNumInstance;
					for( int nInst = 0; nInst < nNum; nInst++ )
					{
						CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

						if( !pInstance )
							continue;

						if( pInstance->bVisible )
						{
							pInstance->bVisible = FALSE;
							pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
						}
					}
				}
				m_dwWaterSideRippleEffectOverTime = 0;
			}
			else
			{
				CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( m_nWaterSideRippleEffectID );
				if( pModelEffect )
				{
					int nNum = pModelEffect->m_nNumInstance;
					for( int nInst = 0; nInst < nNum; nInst++ )
					{
						CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

						if( !pInstance )
							continue;

						if( m_fWaterSideRippleEffectPlaySpeed > 0.15f )
						{
							m_fWaterSideRippleEffectPlaySpeed -= g_dwSmoothFrame*0.001f;
						}

						if( m_fWaterSideRippleEffectPlaySpeed < 0.15f )
							m_fWaterSideRippleEffectPlaySpeed = 0.15f;

						if( pInstance->pEffectCtrl )
							pInstance->pEffectCtrl->SetParticleEmitterPlaySpeed( m_fWaterSideRippleEffectPlaySpeed );
					}
				}
			}
		}

		//ˮ�е�����

		if( m_bInWater )
		{
			int nRippleEffectID = m_nRippleEffectID;
			if (IsUncontrolMoving()&&IsMounting())
			{
				nRippleEffectID		= m_nBoatRippleEffectID;
			}
			CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( nRippleEffectID );
			if( pModelEffect )
			{
				int nNum = pModelEffect->m_nNumInstance;
				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

					if( !pInstance )
						continue;

					if( !pInstance->bVisible )
					{
						pInstance->bVisible = TRUE;
						pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
					}

					if( pInstance->pEffectCtrl )
					{
						if( !m_bMoving )
						{
							if( m_fRippleEffectPlaySpeed > 0.15f )
							{
								m_fRippleEffectPlaySpeed -= g_dwSmoothFrame*0.001f;
							}

							if( m_fRippleEffectPlaySpeed < 0.15f )
								m_fRippleEffectPlaySpeed = 0.15f;

							pInstance->pEffectCtrl->SetParticleEmitterPlaySpeed( m_fRippleEffectPlaySpeed );
						}
						else
						{
							if( m_fRippleEffectPlaySpeed < 1.0f )
							{
								m_fRippleEffectPlaySpeed += g_dwSmoothFrame*0.001f;
							}

							if( m_fRippleEffectPlaySpeed > 1.0f )
								m_fRippleEffectPlaySpeed = 1.0f;

							pInstance->pEffectCtrl->SetParticleEmitterPlaySpeed( m_fRippleEffectPlaySpeed );
						}
					}
				}
			}
			int nRippleEffectContainerID = m_nRippleEffectContainerID;
			if (IsUncontrolMoving()&&IsMounting())
			{
				nRippleEffectContainerID		= m_nBoatRippleEffectContainerID;
				StopRippleEffect(m_nRippleEffectID);
			}
			else
			{
				StopRippleEffect(m_nBoatRippleEffectID);
			}

			CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( nRippleEffectContainerID );
			if( pEffectContainer )
			{
				float fEffectHelperZ = fWaterHeight;
				IEffectHelper* pEffectHelper = NULL;

				pEffectHelper = pEffectContainer->GetEffectHelper( eEffectBindPart_Body );
				pEffectHelper->SetPos( m_x, m_y, fEffectHelperZ );
				pEffectHelper->SetRot( m_dir + D3DX_PI/2 );
				pEffectHelper->SetFinalRenderAlpha( 0.3 );
			}
			m_dwRippleEffectOverTime = HQ_TimeGetTime();
		}
		else
		{
			if( HQ_TimeGetTime() - m_dwRippleEffectOverTime > 1000 )
			{
				StopRippleEffect(m_nRippleEffectID);
				StopRippleEffect(m_nBoatRippleEffectID);
			}
			else
			{
				int nRippleEffectID = m_nRippleEffectID;
				if (IsUncontrolMoving()&&IsMounting())
				{
					nRippleEffectID		= m_nBoatRippleEffectID;
				}
				CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( nRippleEffectID );
				if( pModelEffect )
				{
					int nNum = pModelEffect->m_nNumInstance;
					for( int nInst = 0; nInst < nNum; nInst++ )
					{
						CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

						if( !pInstance )
							continue;

						if( m_fRippleEffectPlaySpeed > 0.15f )
						{
							m_fRippleEffectPlaySpeed -= g_dwSmoothFrame*0.001f;
						}

						if( m_fRippleEffectPlaySpeed < 0.15f )
							m_fRippleEffectPlaySpeed = 0.15f;

						if( pInstance->pEffectCtrl )
							pInstance->pEffectCtrl->SetParticleEmitterPlaySpeed( m_fRippleEffectPlaySpeed );
					}
				}
			}
		}
	}
	unguard;
}

BOOL CPlayer::AddOperationUseSkill( int tag_npc, int x, int y, int skillid, int skilllevel )
{
	guardfunc;
	m_operation.Clear();
	m_operation.dwType = SOperation::eOpUseSkill;
	m_operation.target.x = x;
	m_operation.target.y = y;
	m_operation.target.stDst = tag_npc;
	m_operation.skill.iSkillID = skillid;
	m_operation.skill.iSkillLevel = skilllevel;

	return TRUE;
	unguard;
}


BOOL CPlayer::AddOperationGotoAttackTarget( int tag_npc, int x, int y, int iSkillID, int iSkillLevel)
{
	guardfunc;

	m_operation.Clear();
	m_operation.dwType = SOperation::eOpMoveSkill;
	m_operation.target.x = x;
	m_operation.target.y = y;
	m_operation.target.stDst = tag_npc;
	//
	m_operation.skill.iSkillID = iSkillID;
	m_operation.skill.iSkillLevel = iSkillLevel;
	//
	return TRUE;
	unguard;
}

BOOL CPlayer::AddOperationIdle( void)
{
	guardfunc;
	m_operation.Clear();
	m_operation.dwType = SOperation::eOpIdle;
	m_operation.target.stDst = NULL;
	//
	m_operation.dwOperBeginTime = HQ_TimeGetTime();
	//
	return FALSE;
	unguard;
}

BOOL CPlayer::AddOperationChangeDir( short x, short y  )
{
	guardfunc;
	m_operation.Clear();
	m_operation.dwType = SOperation::eOpChangeDir;
	m_operation.target.stDst = 0;
	m_operation.target.x = x;
	m_operation.target.y = y;
	//
	return FALSE;
	unguard;
}
BOOL    CPlayer::AddOperationGotoDropItem( short x, short y  )
{ 
	guardfunc;
	m_operation.Clear();
	m_operation.dwType = SOperation::eOpMoveDropItem;
	m_operation.target.stDst = 0;
	m_operation.target.x = x;
	m_operation.target.y = y;
	//
	return FALSE;
	unguard;
}

BOOL	CPlayer::AddOperationDoAction(int ActionID)
{
	guardfunc;
	m_operation.dwType = SOperation::eOpDoAction;
	m_operation.action.iActionID = ActionID;
	//
	return FALSE;
	unguard;
}

BOOL	CPlayer::IsCanPutItem(int x, int y)
{
	guardfunc;
	if (theHeroGame.GetPlayerMgr()->IsHaveItemHere(x, y))
		return FALSE;
	//
	return TRUE;
	unguard;
}

BOOL CPlayer::TryDropItem( unsigned int nPackIndex )
{
	guardfunc;
	if ( nPackIndex >= thePlayerRole.m_bag.GetNowBagSize() )
		return false;
	const float fDistance = 3.0f;
	MsgDropItem2 drop;
	drop.ustPackIndex = nPackIndex;
	drop.fX = m_x - fDistance/2.0f + fDistance*rand()/RAND_MAX;
	drop.fY = m_y - fDistance/2.0f + fDistance*rand()/RAND_MAX;
	GettheNetworkInput().SendMsg( &drop );
	//
	return TRUE;
	unguard;
}

void CPlayer::TryPickItem( CPlayer* pItem )
{
	guardfunc;
	// �Ƿ���ʰȡ
	if( !pItem->m_bCanPick || !pItem->IsItemDropDelayOver() )
		return;

	if( CPreventWallow::Instance().IsFCMNotHealthy() )
		return;
	//pickup�󲥷�open����
	if (pItem != NULL)
	{
		pItem->GetAnim()->PlayAnimByActionName( "box_open",
			MexAnimCtrl::eNormalPlay,
			0,
			MexAnimCtrl::eHoldOnFirstFrame,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			"box_KeepOpen",
			MexAnimCtrl::eNormalPlay );
	}

	// ����鿴����
	//lyh����ҹһ�
	MsgPackageViewReq kPkgViewReq;
	kPkgViewReq.nItemPackageID = pItem->GetID();
	GettheNetworkInput().SendMsg( &kPkgViewReq );

	if(s_CUI_ID_FRAME_AutoAttackSet.GetRrame() && s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
	{
		GameObjectId itemServerID = pItem->GetID();
		s_CUI_ID_FRAME_AutoAttackSet.AddRecordByItemID(itemServerID);
	}

	unguard;
}

BOOL CPlayer::TryPickItem()
{
	guardfunc;
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_operation.target.stDst );
	if( !pPlayer ||
		!pPlayer->IsItem() )
	{
		return FALSE;
	}
	//  �������Ʊ�ĵط����ˣ�����Ͳ���Ҫ������
	MsgPickItem pick;
	POINT pt = pPlayer->GetMapPos();
	//Ŀ������Ʒ
	pick.stItemCharID = pPlayer->GetID();
	pick.header.stID = GetID();
	pick.x = (short)pt.x;
	pick.y = (short)pt.y;
	//
	//
	GettheNetworkInput().SendMsg( &pick );

	return TRUE;
	unguard;
}

void CPlayer::TryTalkWithNpc( CPlayer* pNpc )
{

	guardfunc;
	if( !pNpc || !g_bRenderUI )
	{
		return;
	}

	if( IsRole() && CPreventWallow::Instance().IsFCMNotHealthy() )
		return;

	//s_CUI_ID_FRAME_NpcChatDialogBox.SetNpc( pNpc->GetID() );
	if((pNpc->GetRealCountry() == CountryDefine::Country_Init) || (GetRealCountry() == pNpc->GetRealCountry()))
		s_CUI_NpcTaskDialogBox.SetNpc(pNpc->GetID());

	s_CUI_ID_FRAME_Storage.GetNpcSysID(pNpc->GetID());
	s_CUI_ID_FRAME_Compound.SetNpcId(pNpc->GetID());
	unguard;
}

BOOL CPlayer::TryTalkWithNpc()
{
	guardfunc;
	int px, py;
	int mx, my;
	//
	CPlayer* pNpc = theHeroGame.GetPlayerMgr()->FindByID( m_operation.target.stDst );
	if( !pNpc )
		m_operation.Clear();
	if( !pNpc->IsNpc() )
		m_operation.Clear();
	//��Ŀ��npcת������
	//s_CUI_ID_FRAME_NpcChatDialogBox.SetNpc( pNpc->GetID() );
	if((pNpc->GetRealCountry() == CountryDefine::Country_Init) || (GetRealCountry() == pNpc->GetRealCountry()))
		s_CUI_NpcTaskDialogBox.SetNpc(pNpc->GetID());

	//
	pNpc->GetMapPos( px, py );
	GetMapPos( mx, my );
	//
	if ( !(pNpc->GetShowFlag()&eNotChangeDir) )
	{
		pNpc->SetDir(atan2f((float)(my-py), (float)(mx-px) ) );
		pNpc->SetLowerDir(atan2f((float)(my-py), (float)(mx-px) ) );
	}
	if ( !(GetShowFlag()&eNotChangeDir) )
	{
		SetDir( atan2f((float)(py-my), (float)(px-mx )));
	}

	pNpc->SwitchActionStatus( CPlayerStatus::esk_Idle, CStatusTimer::NoLimitDelay );
	m_operation.Clear();
	return TRUE;
	unguard;
}

void CPlayer::TryTalkWithPlayer()
{
	guardfunc;
	if ( !IsNpc() )	//���ֻ�����npc�Ĳ���
	{
		return;
	}

	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if(!pMe)
		return;

	int px = 0, py = 0;
	int nx = 0, ny = 0;

	pMe->GetMapPos( px, py );
	GetMapPos( nx, ny );
	SetDir( atan2f( (float)(py-ny), (float)(px-nx) ) );
	SetLowerDir( atan2f( (float)(py-ny), (float)(px-nx) ) );
	unguard;
}

//һЩ���ܵ��ж�����
//---
//	�ж�������Ŀ���Ƿ���ȷ
//---
BOOL	CPlayer::IsTargetIsRight(int skill, int skill_level, int id)
{
	guardfunc;
	CPlayer* pDst = theHeroGame.GetPlayerMgr()->FindByID( id );

	if (NULL == pDst)
		return false;

	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(skill, skill_level);

	if (NULL == pSkill)
		return false;
	if (skill == 1063)
	{
		int i = 0;
		i++;
	}
	switch( pSkill->ustCastTarget )
	{
	case ItemDefine::casttarget_me:
		if( pDst != this||pDst->IsDead())
			return false;
		break;
	case ItemDefine::casttarget_friendlive:
		if( pDst->GetProfession() == EArmType_Monster && this->GetPetID() != pDst->GetID())
			return false;
		if(pDst->IsDead())
			return false;
		break;
	case ItemDefine::casttarget_enemylive:
		if( pDst == this|| pDst->IsDead())
			return false;
		break;
	case ItemDefine::casttarget_live:
		{
			if(!pDst || !pDst->IsPlayer() || pDst->IsDead())
				return false;
		}
		break;
	case ItemDefine::casttarget_friendcorpse:
		break;
	case ItemDefine::casttarget_enemycorpse:
		break;
	case ItemDefine::casttarget_corpse:
		break;
	case ItemDefine::casttarget_pet:
		{
			if (this->GetPetID() != pDst->GetID())
			{
				return false;
			}
		}
		break;
	case ItemDefine::casttarget_team:
		{
			if(pDst->IsDead())
				return false;
			if( pDst->GetProfession() == EArmType_Monster && this->GetPetID() != pDst->GetID())
				return false;
		}
		break;
	}
	return true;

	unguard;
}
//---
//	�жϿɷ�ʹ�õ���
//---
BOOL	CPlayer::IsCanUseItem(void)
{
	guardfunc;
	//�жϵ�ǰ�Ķ����ɷ񱻴��
	if (!IsPlayerCanChangeStatus())
		return FALSE;
	//
	switch (m_status.CurStatus())
	{
	case CPlayerStatus::esk_PickItem:       // ��ȡ����
	case CPlayerStatus::esk_Talk:           // �Ի�
	case CPlayerStatus::esk_Trade:          //����
	case CPlayerStatus::esk_Attack:         // ����״̬
	case CPlayerStatus::esk_BeAttack:       // �ܻ�״̬
	case CPlayerStatus::esk_BeatBack:       // ���˴���
	case CPlayerStatus::esk_Miss:           // ����״̬
	case CPlayerStatus::esk_Sleep:          // �赹״̬
	case CPlayerStatus::esk_Die:            // ����״̬
	case CPlayerStatus::esk_PreAttack:      // Ԥ������״̬
		return FALSE;
		break;
	}
	return TRUE;
	unguard;
}
//---
//	�жϿɷ������鶯��
//---
BOOL	CPlayer::IsCanDoExpression(void)
{
	guardfunc;
	//ս��״̬�����������鶯��
	if (GetFightStatus())
		return FALSE;
	//
	//�жϵ�ǰ�Ķ����ɷ񱻴��
	if (!IsPlayerCanChangeStatus())
		return FALSE;
	//
	switch (m_status.CurStatus())
	{
	case CPlayerStatus::esk_PickItem:       // ��ȡ����
	case CPlayerStatus::esk_Talk:           // �Ի�
	case CPlayerStatus::esk_Trade:          //����
	case CPlayerStatus::esk_Attack:         // ����״̬
	case CPlayerStatus::esk_BeAttack:       // �ܻ�״̬
	case CPlayerStatus::esk_BeatBack:       // ���˴���
	case CPlayerStatus::esk_Miss:           // ����״̬
	case CPlayerStatus::esk_Sleep:          // �赹״̬
	case CPlayerStatus::esk_Die:            // ����״̬
	case CPlayerStatus::esk_PreAttack:      // Ԥ������״̬
		return FALSE;
		break;
	}
	return true;
	unguard;
}
//---
//	�ж��ܷ�Ի�
//---
BOOL    CPlayer::IsCanTalk(int iDestID)
{
	guardfunc;
	BOOL ret = FALSE;
	//
	if (IsDead())
		return ret;
	//
	CPlayer* pPlayerTag = theHeroGame.GetPlayerMgr()->FindByID( m_operation.target.stDst );
	if ( pPlayerTag )
	{
		if (pPlayerTag->IsNpc())
		{
			ret = TRUE;
		}
	}
	return ret;
	unguard;
}

BOOL CPlayer::IsSkillCanUseStatus( int skill_id, int skill_level )
{
	guardfunc;
	//���µ�״̬������ʹ�ü���
	if (GetSitStatus())
		return FALSE;
	//�жϵ�ǰ�Ķ����ɷ񱻴��
	if (!IsPlayerCanChangeStatus())
		return FALSE;
	//
	switch (m_status.CurStatus())
	{
	case CPlayerStatus::esk_PickItem:       // ��ȡ����
	case CPlayerStatus::esk_Talk:           // �Ի�
	case CPlayerStatus::esk_Trade:          //����
	case CPlayerStatus::esk_Attack:         // ����״̬
	case CPlayerStatus::esk_BeAttack:       // �ܻ�״̬
	case CPlayerStatus::esk_BeatBack:       // ���˴���
	case CPlayerStatus::esk_Miss:           // ����״̬
	case CPlayerStatus::esk_Sleep:          // �赹״̬
	case CPlayerStatus::esk_Die:            // ����״̬
	case CPlayerStatus::esk_PreAttack:      // Ԥ������״̬
		return FALSE;
		break;
	}
	return TRUE;
	unguard;
}
//---
//�ж�Ī�����ܿɷ�ʹ��
//---
//BOOL    CPlayer::IsSkillCanUse(int skill_id, int skill_level)
//{
//	guardfunc;
//	return IsSkillCanUseExceptActionAndTime(skill_id, skill_level);
//	//
//	unguard;
//}

//BOOL	CPlayer::IsSkillCanUseExceptActionAndTime( ItemDefine::SItemSkill* pSkill, bool bCheckOnly )
//{
//	guardfunc;
//	//�жϿɷ�ʹ�ü���
//	if (!m_cFightStatus.IsCanUseSkill( pSkill ) )
//		return false;
//
//	//HP����
//	if ( pSkill->ustCostHP > (thePlayerRole.GetMyHP()+1) )
//	{
//		if ( bCheckOnly == false )
//		{
//			GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_SkillFailed_NotEnoughHP ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
//		}
//		return FALSE;
//	}
//	//MP����
//	if ( pSkill->ustCostMP > thePlayerRole.GetMyMP() )
//	{
//		if ( bCheckOnly == false )
//		{
//			GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_SkillFailed_NotEnoughMP ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
//		}
//		return FALSE;
//	}
//	//��������
//	if (pSkill->bNeedWeapon && !IsHaveWeapon())
//	{
//		if (pSkill->bNeedWeapon == TRUE)
//		{
//			if (pSkill->stWeaponNeed > -1)
//			{
//				bool bUse = false;
//				ItemDefine::SItemCanEquip* pCanEquipLeft = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(
//                    thePlayerRole.m_charinfo.visual.GetAttriSuitArray()[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandItemPartMask )].itembaseinfo.ustItemID );
//                ItemDefine::SItemCanEquip* pCanEquipRight = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(
//                    thePlayerRole.m_charinfo.visual.GetAttriSuitArray()[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask )].itembaseinfo.ustItemID );
//
//                if (pCanEquipLeft)
//				{
//					if (pSkill->stWeaponNeed == pCanEquipLeft->ustEquipType)
//					{
//						bUse = true;
//					}
//				}
//				if (pCanEquipRight&&bUse == false)
//				{
//					if (pSkill->stWeaponNeed == pCanEquipRight->ustEquipType)
//					{
//						bUse = true;
//					}
//				}
//				if (bUse == false)
//				{
//					if ( bCheckOnly == false )
//					{
//						assert("name.h error"&& 0 );
//					}
//					return FALSE;
//				}
//			}								
//		}
//	}
//	if (!pSkill->bNeedWeapon && !IsHaveShield())
//	{
//		if (pSkill->bIsLeftHand)
//		{
//            ItemDefine::SItemCanEquip* pCanEquipLeft1 = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(
//                thePlayerRole.m_charinfo.visual.GetAttriSuitArray()[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandItemPartMask )].itembaseinfo.ustItemID );
//            if (pCanEquipLeft1)
//			{
//				if (pSkill->stWeaponNeed != pCanEquipLeft1->ustEquipType)
//				{
//					return false;
//				}
//			}
//			return false;
//		}
//	}
//
//	//�������ܲ����Ա�ʹ��
//	if (ItemDefine::generaltype_passive == pSkill->stGeneralType)
//	{
//		if ( bCheckOnly == false )
//		{
//			s_CUI_ChatInfoBox.AddInfo( theXmlString.GetString(eTextPlayer_PassiveNotUse), Color_Config.getColor( CC_SystemPromp ) );
//		}
//		return FALSE;
//	}
//
//	return TRUE;
//	unguard;
//}

//BOOL    CPlayer::IsSkillCanUseExceptActionAndTime(int skill_id, int skill_level)
//{
//	guardfunc;
//	//�жϿɷ�ʹ�ü���
//	if (!m_cFightStatus.IsCanUseSkill(skill_id, skill_level))
//		return false;
//	if (m_bRole) //ֻ������Լ�����Ҫ�ж�
//	{
//		//�ж���Ӧ�ļ��������Ƿ�
//		ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(skill_id, skill_level);
//		if (NULL == pSkill)
//			return FALSE;
//		//HP����
//		if (pSkill->ustCostHP > (thePlayerRole.GetMyHP()+1))
//		{
//			GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_SkillFailed_NotEnoughHP/*eText_HPNoEnough*/ ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
//			return FALSE;
//		}
//		//MP����
//		if (pSkill->ustCostMP > thePlayerRole.GetMyMP())
//		{
//			GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_SkillFailed_NotEnoughMP/*eText_MPNoEnough*/ ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
//			return FALSE;
//		}
//		//��������
//		if (pSkill->bNeedWeapon && !IsHaveWeapon())
//		{
//			if (pSkill->bNeedWeapon == TRUE)
//			{
//				if (pSkill->stWeaponNeed > -1)
//				{
//                    bool bUse = false;
//                    ItemDefine::SItemCanEquip* pCanEquipLeft = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(
//                        thePlayerRole.m_charinfo.visual.GetAttriSuitArray()[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandItemPartMask )].itembaseinfo.ustItemID );
//                    ItemDefine::SItemCanEquip* pCanEquipRight = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(
//                        thePlayerRole.m_charinfo.visual.GetAttriSuitArray()[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask )].itembaseinfo.ustItemID );
//                    if (pCanEquipLeft)
//					{
//						if (pSkill->stWeaponNeed == pCanEquipLeft->ustEquipType)
//						{
//							bUse = true;
//						}
//					}
//					if (pCanEquipRight&&bUse == false)
//					{
//						if (pSkill->stWeaponNeed == pCanEquipRight->ustEquipType)
//						{
//							bUse = true;
//						}
//					}
//					if (bUse == false)
//					{
//						assert("name.h error" && 0);
//						return FALSE;
//					}
//				}								
//			}
//		}
//		//�������ܲ����Ա�ʹ��
//		if (ItemDefine::generaltype_passive == pSkill->stGeneralType)
//		{
//			s_CUI_ChatInfoBox.AddInfo( theXmlString.GetString(eTextPlayer_PassiveNotUse), Color_Config.getColor( CC_SystemPromp ) );
//			return FALSE;
//		}
//
//		//
//		if( !thePlayerRole.IsSkillCanUse( skill_id,skill_level ) )
//			return FALSE;
//	}
//	return TRUE;
//	unguard;
//}

BOOL IsInAttackRange( int x, int y, CPlayer *pAttacker, POINT ptag, float fTargetBodySize, int iAttackRange )
{
	guardfunc;
	// 	static float fAttackRange = 0;
	// 	fAttackRange = 0;
	// 
	// 	fAttackRange += pAttacker->GetBodyLengthSize();
	// 	fAttackRange += pAttacker->GetWeaponAttackRange();
	// 	fAttackRange += fTargetBodySize;

	return AttackFunction::InAttackRange( NULL, x, y, ptag.x, ptag.y, pAttacker->GetBodyLengthSize(), fTargetBodySize, pAttacker->GetWeaponAttackRange(), 0 );

	unguard;
}

//�Ƿ��ڹ���������,ֻ�ж��������
bool CPlayer::IsInAttackRangeOnlyTwoPoint( float fTargetX, float fTargetY, float fTargetBodySize, ItemDefine::SItemSkill *pSkill, bool bCalibrate /* = false */, BOOL* bTooClose/* =NULL */ )
{
	return IsInAttackRange( fTargetX, fTargetY, fTargetBodySize, pSkill, bTooClose );
	// 	float fRange = 0; //�ɹ�������
	// 	float fMinRange = 0;//��С�ɹ�������
	// 	float xoff = 0;
	// 	float yoff = 0;
	// 	float fDis = 0; //����
	// 
	// 	if( pSkill )
	// 	{
	// 		fRange += pSkill->fRangeCanCast;
	// 		fMinRange += pSkill->fRangeCanCastMin;
	// 	}
	// 
	// 	if( bCalibrate ) // ��С�жϷ�Χ���������������ͬ��
	// 	{
	// 		fRange -= 1.f;
	// 		if( fMinRange != 0.f )
	// 			fMinRange += 1.f;
	// 	}
	// 
	// 	xoff = fTargetX - m_x;
	// 	yoff = fTargetY - m_y;
	// 	fDis = sqrtf( xoff*xoff + yoff*yoff );
	// 
	// 	if( fDis < fRange + 0.001f && fMinRange <= fDis )
	// 	{
	// 		return TRUE;
	// 	}
	// 	if( bTooClose && fMinRange > fDis )
	// 		*bTooClose = TRUE;
	// 
	// 	return FALSE;
}
//�Ƿ��ڹ���������
bool CPlayer::IsInAttackRange( float fTargetX, float fTargetY, float fTargetBodySize, ItemDefine::SItemSkill *pSkill, BOOL* bTooClose/*=NULL*/ )
{
	guardfunc;
	float fMinRange = 0;//��С�ɹ�������
	float xoff = 0;
	float yoff = 0;
	float fDis = 0; //����

	if( pSkill )
	{
		fMinRange += pSkill->fRangeCanCastMin;
	}

	xoff = fTargetX - m_x;
	yoff = fTargetY - m_y;
	fDis = sqrtf( xoff*xoff + yoff*yoff );

	if( AttackFunction::InAttackRange( pSkill, m_x, m_y, fTargetX, fTargetY, m_fBodyLengthSize, fTargetBodySize, m_fWeaponAttackRange, 0 ) )
		return true;

	if( bTooClose && fMinRange > fDis )
		*bTooClose = TRUE;

	return false;
	unguard;
}

BOOL CPlayer::IsTargetInFront( float fTargetX, float fTargetY, float fTargetZ, float fAngleMax /* = D3DX_PI/2  */)
{
	guardfunc;
	float fAngle = 0;//fDir1��fDir2�ļн�
	float x = 0;
	float y1 = 0;
	float y2 = 0;
	float c = 0;
	D3DXVECTOR3 vSelfDir;
	D3DXVECTOR3 vTargetDir;

	if( m_bRole )
	{
		vSelfDir.x = m_vCurDir.x;
		vSelfDir.y = m_vCurDir.y;
		vSelfDir.z = 0;
	}
	else
	{
		GetAngleTo2D( m_dir, &vSelfDir.x, &vSelfDir.y );
	}
	vTargetDir.x = fTargetX - m_x;
	vTargetDir.y = fTargetY - m_y;
	vTargetDir.z = 0;
	x = vSelfDir.x*vTargetDir.x + vSelfDir.y*vTargetDir.y + vSelfDir.z*vTargetDir.z;
	y1 = sqrtf(vSelfDir.x*vSelfDir.x + vSelfDir.y*vSelfDir.y + vSelfDir.z*vSelfDir.z);
	y2 = sqrtf(vTargetDir.x*vTargetDir.x + vTargetDir.y*vTargetDir.y + vTargetDir.z*vTargetDir.z);

	if( y1*y2 <= 0 )
	{
		if( x > 0 )
		{
			c = 1.0f;
		}

		if( x < 0 )
		{
			c = -1.0f;
		}

		if( x == 0 )
		{
			c = 0;
		}
	}
	else
	{
		c = x/(y1*y2);
	}

	if( c > 1.0f )
	{
		c = 1.0f;
	}

	if( c < -1.0f )
	{
		c = -1.0f;
	}

	fAngle = acos( c );

	if( fAngle < fAngleMax*0.5f )
	{
		return TRUE;
	}
	return FALSE;

	unguard;
}

// ��õ�Ŀ���ľ���
float	CPlayer::GetDistToTarget( float fTargetX, float fTargetY )
{
	guardfunc;
	float xoff = fTargetX - m_x;
	float yoff = fTargetY - m_y;
	float fDist = sqrtf( xoff*xoff + yoff*yoff );
	return fDist;
	unguard;
}

//  �ж�һ����ҿɷ��ƶ�
BOOL    CPlayer::IsCanMove(void)
{
	guardfunc;
	if (HQ_TimeGetTime() <= m_dwStopMoveTime)
		return FALSE;

	//�ж��Ƿ���һЩ�������ƶ���ս��״̬..������
	if (!m_cFightStatus.IsCanMove())
		return FALSE;

	//�ж��Ƿ񸴻�ȴ�������ȥ����
	if( m_bRole && thePlayerRole.IsReliveAndWaitingToHell() )
		return FALSE;

	return TRUE;
	unguard;
}

// �ж�����ܷ���Ծ
BOOL CPlayer::IsCanJump(void)
{
	guardfunc;
	if( HQ_TimeGetTime() <= m_dwStopJumpTime )
		return FALSE;

	return TRUE;
	unguard;
}

//---
//  �ж�һ������Ƿ���Ըı�״̬(����)
//---
BOOL    CPlayer::IsPlayerCanChangeStatus(void)
{
	guardfunc;
	//�жϵ�ǰ�Ƿ��ڿ����жϵĶ���״̬
	if (!m_status.IsStateCanBreak())
	{
		//
		return FALSE;
	}
	if( Player_Status_HoldSkill ==  GetPlayerStatus() )
		return FALSE;
	//���µ�ʱ���ܸı䶯��
	if (0 != GetSitStatus())
		return FALSE;

	return TRUE;
	unguard;
}
//---
//	�ж�player�ܷ�ı䵽Ŀ��״̬
//---
BOOL    CPlayer::IsPlayerCanChangeToStatus(int next_status)
{
	guardfunc;
	switch (next_status)
	{
	case CPlayerStatus::esk_PreAttack:// Ԥ������״̬
	case CPlayerStatus::esk_Attack:// ����״̬
	case CPlayerStatus::esk_Intonate:// �ʳ�״̬
	case CPlayerStatus::esk_Die:// ����״̬
	case CPlayerStatus::esk_ActionTime://��һ��ʱ������Ī������
		return TRUE;
		break;
	}
	return IsPlayerCanChangeStatus();
	unguard;
}
//---
//�ж�Ŀ��ɷ񹥻�
//---
BOOL    CPlayer::IsTagCanBeAttack(void)
{
	guardfunc;
	CPlayer* pPlayerTag = theHeroGame.GetPlayerMgr()->FindByID( m_operation.target.stDst );
	//
	if( pPlayerTag->IsMonster() || 
		pPlayerTag->IsPlayer() 
		/*|| Object_Building == pPlayerTag->GetCharType()*/ )
		return TRUE;
	//
	return FALSE;
	unguard;
}
//---
//��npc������С�����Ķ���
//---
BOOL    CPlayer::OperNothing(void)
{
	guardfunc;
	AddOperationIdle();
	return FALSE;
	unguard;
}
//����
BOOL    CPlayer::OperIdle(void)     
{
	guardfunc;
	return TRUE;
	unguard;
}

void CPlayer::AutoDisMount(ItemDefine::SItemSkill* pSkill)
{
	if (pSkill)
	{
		if (m_bMounting && IsCanDisMount() && GetAutoDismount() && theHeroGame.GetPlayerMgr() && !IsGoudaOperaMode())
		{
			if (!(pSkill->iSkillActionFlags & ItemDefine::ONLY_MOUNT_CAST)&&!(pSkill->iSkillActionFlags & ItemDefine::CAN_MOUNT_CAST))
			{
				DisMount();
				theHeroGame.GetPlayerMgr()->DisDrome();
			}
		}
	}
	else
	{
		if (m_bMounting && IsCanDisMount() && GetAutoDismount() && theHeroGame.GetPlayerMgr() && !IsGoudaOperaMode())
		{
			DisMount();
			theHeroGame.GetPlayerMgr()->DisDrome();
		}
	}

}

//ʹ�ü���
BOOL	CPlayer::TryUseSkill( CPlayer* pTagPlayer, ItemDefine::SItemSkill* pSkill, bool bCheckOnly /* = false */, bool bNoTip /* = false  */)
{
	// ѹ��״̬�½�ֹʹ�ü���
	if (mIsYabiaoState && !s_CUI_ID_FRAME_Target.IsTargetUIUpDateIng)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_YabiaoState_UseSkill ));
		return FALSE;
	}

	//lyh++ �����;ö�Ϊ0 ����ʹ�ü��� ����ͨ���� 
	SCharItem* pAttriEquips = thePlayerRole.m_charinfo.visual.GetVisualArray();
	if (pAttriEquips)
	{
		if(	pAttriEquips[EEquipPartType::EEquipPartType_Weapon].itembaseinfo.ustItemID 
			!= InvalidLogicNumber &&
			pAttriEquips[EEquipPartType::EEquipPartType_Weapon].equipdata.usHP == 0 && pSkill && pSkill->bNeedWeapon) //�������� �����Ҽ����ͷ��������� �����ͷż���
		{
			if (!s_CUI_ID_FRAME_Target.IsTargetUIUpDateIng) //���Ǵ� Ŀ��ɹ����������� ����ʾ��ʾ
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_WeopenHpWhithZero ));
				return FALSE;
			}
		}
	}

	// �������ͨ����, �ƶ�ʱ�����ͷ�
	if (IsNormalAttack(pSkill->ustItemID) && IsMoving())
		return FALSE;

	guardfunc;
	if (!pSkill)
	{
		if( !bCheckOnly && !bNoTip )
			theApp->GetPlayerMgr()->ClearSkillBuf();
		return FALSE;
	}

	if( IsDead() )
	{
		if( !bCheckOnly && !bNoTip )
			theApp->GetPlayerMgr()->ClearSkillBuf();
		return FALSE;
	}

	if( IsRole() && CPreventWallow::Instance().IsFCMNotHealthy(!bCheckOnly && !bNoTip) )
		return FALSE;

	//ս��״̬��������
	/*if (ItemDefine::eSSI_MountMonster == pSkill->ustItemID && thePlayerRole.IsFighting() )
	{	
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_CannotUseInFighting ) );
	return FALSE;
	}*/

	if (ItemDefine::eSSI_MountMonster == pSkill->ustItemID && !m_cFightStatus.IsCanRide())
	{	
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eClient_AddInfo_2slk_NoRide ) );
		return FALSE;
	}

	bool bSentServer = true;

	// 1.�������̵��ж�
	if (this->IsOpenPrivateShop())
	{
		if( !bCheckOnly && !bNoTip )
		{
			if( IsLootMountSkill(pSkill->ustItemID) )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotLootMount_CurrStatus ));
			else
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_InPrivateShop ) );
		}
		return FALSE;
	}

	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (pMe && pMe->IsInWater() && !IsGoBackSkill(pSkill->ustItemID))
	{
		//ˮ�ﲻ��ʹ�÷ǻسǼ���
		if( !bCheckOnly && !bNoTip )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
		return FALSE;
	}


	// 2.���������ж�
	// 2.1�������ܲ����Ա�ʹ��
	if (ItemDefine::generaltype_passive == pSkill->stGeneralType)
	{
		//�������ܲ����Ա�ʹ��
		if( !bCheckOnly && !bNoTip )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_PassiveSkill_NotUse ) );
		return FALSE;
	}

	// ְҵ����     
	int nProfession = thePlayerRole.GetProfession();
	if( !pSkill->arrayProfessionReq[nProfession] )
	{
		if( !bCheckOnly && !bNoTip )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillUse_ProfessionLimit ) );
		return false;
	}

	// 2.3С�Ӽ���
	const CPlayerRole::PlayerTeamSkillVector* pVecTeamSkill = thePlayerRole.GetTeamSkillVector();
	int iTeamSkillLevel = -1;
	if( pSkill->specialSkillType >= ItemDefine::ESST_Team && pSkill->specialSkillType < ItemDefine::ESST_TeamMax )
	{
		if( !pVecTeamSkill )
		{
			if( !bCheckOnly && !bNoTip )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_TeamSkillFailed_NotAvailable ) );
			return FALSE;
		}
		// �Ƿ����
		bool bCanUse = false;
		for(int n=0; n<pVecTeamSkill->size(); ++n)
		{
			if( pSkill->ustItemID == (*pVecTeamSkill)[n].nSkillID )
			{
				iTeamSkillLevel = min((*pVecTeamSkill)[n].uchLevel, pSkill->ustLevel);
				bCanUse = true;
				break;
			}
		}
		if( !bCanUse )
		{
			if( !bCheckOnly && !bNoTip )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_TeamSkillFailed_NotAvailable ) );
			return FALSE;
		}
	}

	// 2.3���ѷ��ͷŵļ���
	short  shCastType = pSkill->shCastType;
	unsigned short  shCastTarget = pSkill->ustCastTarget;	
	if(shCastTarget == ItemDefine::casttarget_friendlive||shCastTarget == ItemDefine::casttarget_team)
	{
		if(thePlayerRole.GetDuelTarget() != -1)
		{
			if(pTagPlayer&&pTagPlayer->GetMasterID() != GetID())
			{
				pTagPlayer = this;
			}
		}
		//         else
		//         {
		//             if( pTagPlayer && pTagPlayer->IsPlayer())
		//             {
		//                 bool bAttack = true;
		//                 CGangMgr* theGuild = thePlayerRole.GetGangMgr();
		// 
		//                 //ͬһ��PK�ж�
		//                 bAttack = canAttack(pTagPlayer);
		//             }
		//         }    
	}


	// 3.Ŀ�������ж�
	if( pTagPlayer )
	{
		// 3.1�ɼ������ײ��
		if( pTagPlayer->IsMonster() )
		{
			int	nMonsterId =  pTagPlayer->GetMonsterID();
			ItemDefine::SMonster *pMonster;
			pMonster = GettheItemDetail().GetMonsterById( nMonsterId );
			if (pMonster)
			{
				if (pMonster->bIsCityMonster)
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
					return FALSE;
				}
			}


			// �ж��Ƿ�ɼ���Ʒ�ͼ���
			if( pTagPlayer->IsMonsterType(eMT_Mine)  )
			{
				if( !bCheckOnly && !bNoTip )
				{
					// ���ϰ��Ƿ�����
					if( thePlayerRole.m_bagMaterial.GetNullItemCount() <= 0 )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eWarning_BagFull ));
				}

				if( !CanLootMine(pTagPlayer, pSkill, !bCheckOnly && !bNoTip) )
					return FALSE;

				// ��龫��
				if( pSkill->usConsumeVigor > thePlayerRole.GetData(CPlayerRole::TYPE_VIGOR) )
				{
					if( !bCheckOnly && !bNoTip )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_NotEnoughVigorToMine ) );
					return FALSE;
				}
			}
			if( pTagPlayer->IsMonsterType(eMT_Herb)  )
			{
				if( !bCheckOnly && !bNoTip )
				{
					// ���ϰ��Ƿ�����
					if( thePlayerRole.m_bagMaterial.GetNullItemCount() <= 0 )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_MaterialPackFull ) );
				}

				if( !CanLootHerb(pTagPlayer, pSkill, !bCheckOnly && !bNoTip) )
					return FALSE;

				// ��龫��
				if( pSkill->usConsumeVigor > thePlayerRole.GetData(CPlayerRole::TYPE_VIGOR) )
				{
					if( !bCheckOnly && !bNoTip )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_NotEnoughVigorToHerb ) );
					return FALSE;
				}
			}
			// ���Ӳ���     added by zhuomeng.hu		[11/9/2010]
			if( pTagPlayer->IsMonsterType( eMT_Insect ) )
			{
				if( !bCheckOnly && !bNoTip )
				{
					// ���ϰ��Ƿ�����
					if( thePlayerRole.m_bagMaterial.GetNullItemCount() <= 0 )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_MaterialPackFull ));
				}
				if( !CanLootInsect( pTagPlayer, pSkill, !bCheckOnly && !bNoTip ) )
					return FALSE;

				// ��龫��
				if( pSkill->usConsumeVigor > thePlayerRole.GetData( CPlayerRole::TYPE_VIGOR ) )
				{
					if( !bCheckOnly && !bNoTip )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed,
						theXmlString.GetString( eText_NotEnoughVigorToInsect ) );
					return FALSE;
				}
			}
			if( pTagPlayer->IsMonsterType(eMT_Treasure)  )
			{
				ItemDefine::SItemSkill *pLootSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_Treasure, 1 );
				if( pLootSkill != pSkill )
				{
					if( !bCheckOnly && !bNoTip )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed,
						theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
					return FALSE;
				}
			}
			// ����
			if( pTagPlayer->IsMonsterType(eMT_Mount)  )
			{
				ItemDefine::SItemSkill *pLootSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_BuZhuo, 1 );
				if( pLootSkill != pSkill )
				{
					if( !bCheckOnly && !bNoTip )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
					return FALSE;
				}
			}

			//lyh++ ���ܹ���ͬ��Ӫ�Ĺ���
			if( !pTagPlayer->HaveMaster())
			{//���ǳ���Ĺ����������жϹ��� vvx 2013.6.10
				if(pTagPlayer->GetRealCountry() != CountryDefine::Country_Init&&
					thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry != CountryDefine::Country_Init&&
					thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry ==pTagPlayer->GetRealCountry() )
				{
					return false;
				}
			}
			/*
			* Author: 2013-1-7 14:23:50 wangshuai
			* Desc:   ������Ҳ���Դ�
			*/

			/*
			if( pTagPlayer->GetMonsterType() == eMT_Collision )
			{
			if( !bCheckOnly && !bNoTip )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
			return FALSE;
			}*/
		}
		// 3.2NPC��Item
		if( ( ( pTagPlayer->IsNpc() && !isNPCCanAttack( pTagPlayer ) ) || pTagPlayer->IsItem()) && shCastType != ItemDefine::casttype_AOEcircleself )
		{
			if( !bCheckOnly && !bNoTip )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
			return FALSE;
		}
		// 3.3������ʹ��
		if ( pSkill->stTargetType == ItemDefine::target_dead)
		{
			if ( !pTagPlayer->IsDead() )
			{
				if( !bCheckOnly && !bNoTip )
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
				return FALSE;
			}
		}

		// ��ͬ���ܵ�Ŀ���ж�
		if( shCastType == ItemDefine::casttype_singletarget ||
			shCastType == ItemDefine::casttype_singletargetcircleAOE ||
			shCastType == ItemDefine::casttype_AOETargetcirclearea )
		{
			// �з�Ŀ���ж�
			if( shCastTarget == ItemDefine::casttarget_enemylive || shCastTarget == ItemDefine::casttarget_enemycorpse )
			{
				if( GetRealCountry() == pTagPlayer->GetRealCountry() )
				{
					// �����ٻ���
					if(!pTagPlayer->HaveMaster() )
					{
						if( pTagPlayer == this )
						{
							if( !bCheckOnly && !bNoTip )
								CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
							return FALSE;
						}

						bool bAttack = false;
						CGangMgr* theGuild = thePlayerRole.GetGangMgr();

						//PK�ж�
						if ((pTagPlayer->IsPlayer() || pTagPlayer->IsNpc())&& !canAttack(pTagPlayer))
						{
							if( !bCheckOnly && !bNoTip )
								CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString(eClient_AddInfo_2slk_1) );
							return FALSE;
						}
					}
					else
					{
						// �Լ����ٻ���
						if(pTagPlayer->GetMasterID() == GetID() )
						{
							if( !bCheckOnly && !bNoTip )
								CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString(eClient_AddInfo_2slk_1) );
							return FALSE;
						}
						// �������ٻ��ޣ��ж������Ƿ��ܹ���
						else
						{
							BOOL bCanAttack = FALSE;
							CPlayer* pTargetMaster = theHeroGame.GetPlayerMgr()->FindByID(pTagPlayer->GetMasterID());
							if( pTargetMaster )
							{
								if( canAttack(pTargetMaster) )
									bCanAttack = TRUE;
							}
							if( !bCanAttack )
							{
								// �Ҳ���Master�����ݳ���Ĭ���޷���������
								if( !bCheckOnly && !bNoTip )
									CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
								return FALSE;
							}
						}
					}
				}
			}

			if ( pTagPlayer->GetMonsterType() == eMT_Building)
			{
				if( !bCheckOnly && !bNoTip )
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
				return FALSE;
			}

			if ( !IsTargetIsRight( pSkill->ustItemID, pSkill->ustLevel, pTagPlayer->GetID() ) )
			{
				if( !bCheckOnly && !bNoTip )
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString(eText_SkillFailed_NotCorrectTarget) );
				return FALSE;
			}
		}
		else if (shCastType == ItemDefine::casttype_AOEquartercirlcefrontage)
		{
			if( pTagPlayer != this )
			{
				if ( pSkill->stTargetType != ItemDefine::casttarget_me && pSkill->bNeedTestAngle )
				{
					// ���û������Ŀ����ż��ܣ����Զ�ת���ٷż���
					if (!IsTargetInFront( pTagPlayer->GetPos().x, pTagPlayer->GetPos().y, pTagPlayer->GetPos().z, pSkill->fAngle ) &&
						m_readySkillInfo.pTagPlayer != pTagPlayer &&
						m_readySkillInfo.pSkill != pSkill &&
						!bCheckOnly)
					{
						m_readySkillInfo.bTryUse = true;
						m_readySkillInfo.pTagPlayer = pTagPlayer;
						m_readySkillInfo.pSkill = pSkill;
						m_readySkillInfo.bNoTip = bNoTip;

						theHeroGame.GetPlayerMgr()->TurnRoleTo(pTagPlayer);
						return FALSE;
					}
				}
			}
		}
	}
	// ��Ŀ��
	else if( pSkill->shCastType != ItemDefine::casttype_AOEquartercirlcefrontage
		&& pSkill->shCastType != ItemDefine::casttype_AOEcircleself)
	{
		// �ǵ�AOE���ܣ��Ҳ���������Ŀ��ѡ��ĵ��弼��
		if( shCastType != ItemDefine::casttype_AOEPointCircleArea
			&& !( pSkill->shCastType == ItemDefine::casttype_singletarget && pSkill->usSpecialTargetType != ItemDefine::STT_NONE ))
		{
			// ����Ҫ��Ŀ��
			if( !bCheckOnly && !bNoTip )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NoTarget ) );
			return FALSE;
		}
	}


	// 4.ս��״̬�ж�
	if( pSkill->cFightStateCastType != ItemDefine::SCC_Null )
	{
		// ��Ҫս��״̬
		if( !HasFightFlag(eFighting) && pSkill->cFightStateCastType == ItemDefine::SCC_MustInFightState )
		{
			if( !bCheckOnly && !bNoTip )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_UseOnlyInFighting ) );
			return FALSE;
		}
		// ��Ҫ��ս��״̬
		else if( HasFightFlag(eFighting) && pSkill->cFightStateCastType == ItemDefine::SCC_MustOutFightState )
		{
			if( !bCheckOnly && !bNoTip )
			{
				if( IsLootMountSkill(pSkill->ustItemID) )
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotLootMount_InFight ) );
				else
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_CannotUseInFighting ) );
			}
			return FALSE;
		}
	}


	// 5.װ�������ж�
	if( pSkill->bNeedWeapon )
	{
		if( !IsHaveWeapon(pSkill->stWeaponNeed) )
		{
			if( !bCheckOnly && !bNoTip )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NeedWeapon ) );
			return FALSE;
		}
	}

	// �ж���װ
	//if (pSkill->specialSkillType > ItemDefine::ESST_Normal && pSkill->specialSkillType < ItemDefine::ESST_SuitMax 
	//	&& !thePlayerRole.suitManager.IsSuitHaveSkill(pSkill->ustItemID, pSkill->ustLevel))
	//{
	//	if( !bCheckOnly && !bNoTip )
	//		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_NotSatisfySuitSkillCondition ) );
	//	return FALSE;
	//}

	// 6.��ȴ״̬
	if (pSkill->sSkillCategory == ItemDefine::SCT_MountMasterInitiativeControl)
	{
		if ( thePlayerRole.m_MountSkillBag.IsSkillCoolDownById( pSkill->ustItemID ) )
		{
			if( !bCheckOnly && !bNoTip )
			{
				if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())//lyh++ �Զ��һ���ʱ����ʾ��������ȴ
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_WhenCoolDown ) );
				PlaySoundConfig( SoundConfig::EST_InCoolDown );
			}
			return FALSE;
		}
	}
	else if(pSkill->sSkillCategory == ItemDefine::SCT_PetMasterManualControl)
	{
		if ( thePlayerRole.m_PetSkillBag.IsSkillCoolDownById( pSkill->ustItemID ) )
		{
			if( !bCheckOnly && !bNoTip )
			{
				if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())//lyh++ �Զ��һ���ʱ����ʾ��������ȴ
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_WhenCoolDown ) );
				PlaySoundConfig( SoundConfig::EST_InCoolDown );
			}
			return FALSE;
		}
	}
	else
	{
		//�������������
		if (pSkill->sSkillCategory == ItemDefine::SCT_HeroAttack)
		{
			if(thePlayerRole.m_HeroSkillBag.IsSkillCoolDownById( pSkill->ustItemID ))
			{
				if( !bCheckOnly && !bNoTip )
				{
					if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())//lyh++ �Զ��һ���ʱ����ʾ��������ȴ
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_WhenCoolDown ) );
					PlaySoundConfig( SoundConfig::EST_InCoolDown );
				}
				return FALSE;
			}
		}
		else if ( thePlayerRole.m_SkillBag.IsSkillCoolDownById( pSkill->ustItemID ))
		{
			if( !bCheckOnly && !bNoTip )
			{
				if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())//lyh++ �Զ��һ���ʱ����ʾ��������ȴ
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_WhenCoolDown ) );
				PlaySoundConfig( SoundConfig::EST_InCoolDown );
			}
			return FALSE;
		}
	}


	// 7.BufferStatus�Ƿ���������ħ������
	if (!m_cFightStatus.IsCanUseSkill( pSkill ) )
	{
		if( !bCheckOnly && !bNoTip )
		{
			switch ( pSkill->ustDamageBalanceType )
			{
			case ItemDefine::balancetype_damagephysicaldefend:
				{
					if (pSkill->ustItemID == ItemDefine::eSSI_PetActive)
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotDoIt ) );
					else
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_CannotUsePhysicsSkill ) );
				}
				break;
			case ItemDefine::balancetype_damagemagicdefend:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_CannotUseMagicSkill ) );
				break;
			default:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotDoIt ) );
				break;
			}
		}
		return FALSE;
	}


	// 8.�ж�����ͷż���
	if (!(pSkill->iSkillActionFlags & ItemDefine::CAN_MOUNT_CAST) && IsMounting() && !GetAutoDismount())
	{
		if( !bCheckOnly && !bNoTip )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_WhenMounting ) );
		return FALSE;
	}

	// ֻ������ͷ�
	if (pSkill->iSkillActionFlags & ItemDefine::ONLY_MOUNT_CAST ) 
	{
		if( !IsMounting() )
		{
			if( !bCheckOnly && !bNoTip )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_OnlyMounting ) );
			return FALSE;
		}
		// �ж��Ƿ���ְҵ����
		if( pSkill->iMountSkillProfessionType != ItemDefine::MSPT_ALL )
		{
			// ǹ
			if( pSkill->iMountSkillProfessionType & ItemDefine::MSPT_SPEAR && GetProfession() != EArmType_Warrior )
			{
				if( !bCheckOnly && !bNoTip )
				{
					char msg[MAX_PATH] = {0};
					MeSprintf_s(msg,sizeof(msg)/sizeof(char) - 1,theXmlString.GetString(eText_SkillFailed_NotCorrectProfession), 
						theXmlString.GetString(eProfession_Warrior));
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, msg );
				}
				return FALSE;
			}
			// ��
			if( pSkill->iMountSkillProfessionType & ItemDefine::MSPT_STAFF && GetProfession() != EArmType_Mage )
			{
				if( !bCheckOnly && !bNoTip )
				{
					char msg[MAX_PATH] = {0};
					MeSprintf_s(msg,sizeof(msg)/sizeof(char) - 1,theXmlString.GetString(eText_SkillFailed_NotCorrectProfession), 
						theXmlString.GetString(eProfession_Mage));
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, msg );
				}
				return FALSE;
			}
			// ��
			if( pSkill->iMountSkillProfessionType & ItemDefine::MSPT_FAN && GetProfession() != EArmType_Taoist )
			{
				if( !bCheckOnly && !bNoTip )
				{
					char msg[MAX_PATH] = {0};
					MeSprintf_s(msg, sizeof(msg)/sizeof(char) - 1,theXmlString.GetString(eText_SkillFailed_NotCorrectProfession), 
						theXmlString.GetString(eProfession_Taoist));
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, msg );
				}
				return FALSE;
			}
			// ��
			if( pSkill->iMountSkillProfessionType & ItemDefine::MSPT_SWORD && GetProfession() != EArmType_Assassin )
			{
				if( !bCheckOnly && !bNoTip )
				{
					char msg[MAX_PATH] = {0};
					MeSprintf_s(msg,sizeof(msg)/sizeof(char) - 1, theXmlString.GetString(eText_SkillFailed_NotCorrectProfession), 
						theXmlString.GetString(eProfession_Assassin));
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, msg );
				}
				return FALSE;
			}
			// ��
			if( pSkill->iMountSkillProfessionType & ItemDefine::MSPT_BOW && GetProfession() != EArmType_Hunter )
			{
				if( !bCheckOnly && !bNoTip )
				{
					char msg[MAX_PATH] = {0};
					MeSprintf_s(msg,sizeof(msg)/sizeof(char) - 1, theXmlString.GetString(eText_SkillFailed_NotCorrectProfession), 
						theXmlString.GetString(eProfession_Hunter));
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, msg );
				}
				return FALSE;
			}
		}
	}


	// 9.��Ծʱ�����ж�
	if (IsJumping() && (pSkill->iSkillActionFlags & ItemDefine::CANNOT_JUMP_CAST))
	{
		if( !bCheckOnly && !bNoTip )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_CannotJump ) );
		return FALSE;
	}


	// 10.��鹥������
	// 10.1ѡ����������������Ŀ��ĵ��弼�ܣ����AOE
	BOOL bTargetTooFar = FALSE;
	if( (pSkill->shCastType == ItemDefine::casttype_singletarget && pSkill->usSpecialTargetType != ItemDefine::STT_NONE )
		|| shCastType == ItemDefine::casttype_AOEPointCircleArea )
	{
		BOOL bClose = false;
		if( !IsInAttackRangeOnlyTwoPoint( m_vPointAoePos.x, m_vPointAoePos.y, 0, pSkill, true, &bClose ) && !bCheckOnly && !IsSelectingPoint() )
		{
			if( !bCheckOnly && !bNoTip )
			{
				if( bClose )//����̫��
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_TooClose ) );
				}
				else        //������������
				{
					if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_TooFar ) );
				}
			}			
			return FALSE;
		}
	}
	// 10.2��Ŀ��ļ��ܹ���
	else if( shCastType == ItemDefine::casttype_singletarget ||
		shCastType == ItemDefine::casttype_singletargetcircleAOE ||
		shCastType == ItemDefine::casttype_AOETargetcirclearea )
	{
		BOOL bClose = false;
		if( !IsInAttackRangeOnlyTwoPoint( pTagPlayer->GetPos().x, pTagPlayer->GetPos().y, pTagPlayer->GetBodyLengthSize(), pSkill, true, &bClose ) )
		{
			if( !bCheckOnly && !bNoTip )
			{
				if( bClose )//����̫��
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_TooClose ) );
					return FALSE;
				}
				else        //������������
				{
					if( theHeroGame.GetPlayerMgr()->IsUseSkillBuf() )
						bTargetTooFar = TRUE;
					else
					{
						if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_TooFar ) );
						return FALSE;
					}
				}
			}
			else
				return FALSE;
		}
	}


	// 11.1���Ѫ������
	if( pSkill->cHpLimitType != ItemDefine::SHT_None )
	{

		switch ( pSkill->cHpLimitType )
		{
		case ItemDefine::SHT_Above:
			{                
				float nCurrentRate = thePlayerRole.GetData(CPlayerRole::TYPE_HP) * 1.f/ thePlayerRole.GetData(CPlayerRole::TYPE_HPMAX);
				if ( nCurrentRate < pSkill->fHpPerLimit )
				{
					if( !bCheckOnly && !bNoTip )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_HpLimit ) );
					return FALSE;
				}
			}
			break;
		case ItemDefine::SHT_Under:
			{
				float nCurrentRate = thePlayerRole.GetData(CPlayerRole::TYPE_HP) * 1.f/ thePlayerRole.GetData(CPlayerRole::TYPE_HPMAX);
				if ( nCurrentRate > pSkill->fHpPerLimit )
				{
					if( !bCheckOnly && !bNoTip )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_HpLimit ) );
					return FALSE;
				}
			}
			break;
		case ItemDefine::SHT_TargetAbove:
			{                
				float nCurrentRate = pTagPlayer->GetHp()* 1.f/pTagPlayer->GetHpMax();
				if ( nCurrentRate < pSkill->fHpPerLimit )
				{
					if( !bCheckOnly && !bNoTip )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_HpLimit ) );
					return FALSE;
				}
			}
			break;
		case ItemDefine::SHT_TargetUnder:
			{
				float nCurrentRate = pTagPlayer->GetHp()* 1.f/pTagPlayer->GetHpMax();
				if ( nCurrentRate > pSkill->fHpPerLimit )
				{
					if( !bCheckOnly && !bNoTip )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_HpLimit ) );
					return FALSE;
				}
			}
			break;
		}
	}

	//// �ٻ����Ѿ�����
	//if ( pSkill->bSummonSkill && theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->HavePet())
	//{
	//	if( !bCheckOnly && !bNoTip )
	//		GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_CannotConjurePetExit ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
	//	return FALSE;
	//}

	// 11.2HP����
	if ( pSkill->ustCostHP > (thePlayerRole.GetMyHP()+1) )
	{
		if( !bCheckOnly && !bNoTip )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotEnoughHP ) );
		return FALSE;
	}
	// 11.3����ֵ�ж�
	if (pSkill->ustCostMP > thePlayerRole.GetMyMP())
	{
		if( !bCheckOnly && !bNoTip )
		{
			std::string strTemp = GetMPTypeString( thePlayerRole.GetProfession() );
			strTemp = strTemp + theXmlString.GetString( eText_SkillFailed_NotEnoughMP );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, strTemp.c_str() );
		}
		return FALSE;
	}
	// 11.4�����ж�
	if( pSkill->usConsumeFightPower > thePlayerRole.GetExPower() )
	{
		if( !bCheckOnly && !bNoTip )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotEnoughExPower ) );
		return FALSE;
	}


	// 12.���󹥻��ж�
	if( pTagPlayer && pSkill->bMustInBackUse )
	{
		// �����Ŀ��ǰ��
		if( pTagPlayer->IsTargetInFront( GetPos().x, GetPos().y, GetPos().z, pSkill->fAngle ) )
		{
			if( !bCheckOnly && !bNoTip )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_MustAtBack ) );
			return FALSE;
		}
	}


	// 13.��鳯��
	if( !bTargetTooFar )
		if( shCastType == ItemDefine::casttype_singletarget ||
			shCastType == ItemDefine::casttype_singletargetcircleAOE ||
			shCastType == ItemDefine::casttype_AOETargetcirclearea )
		{
			if( pTagPlayer && pTagPlayer != this )
			{
				if ( pSkill->stTargetType != ItemDefine::casttarget_me && pSkill->bNeedTestAngle )
				{
					// ���û������Ŀ����ż��ܣ����Զ�ת���ٷż���
					if (!IsTargetInFront( pTagPlayer->GetPos().x, pTagPlayer->GetPos().y, pTagPlayer->GetPos().z, pSkill->fAngle ) &&
						m_readySkillInfo.pTagPlayer != pTagPlayer &&
						m_readySkillInfo.pSkill != pSkill &&
						!bCheckOnly )
					{
						/*
						* Author: 2013-1-4 17:09:30 wangshuai
						* Desc:   ���û�����Ŀ��, �Զ�ת������ʾ
					 */
						if( !g_bTheRoleMovingByDir /* && !g_bMouseRButtonIsDown */)
						{
							m_readySkillInfo.bTryUse = true;
							m_readySkillInfo.pTagPlayer = pTagPlayer;
							m_readySkillInfo.pSkill = pSkill;
							m_readySkillInfo.bNoTip = bNoTip;

							theHeroGame.GetPlayerMgr()->TurnRoleTo(pTagPlayer);
						}
						// else if( !bNoTip )
						//     CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotFaceToTarget ) );
						return FALSE;
					}
				}
			}
		}


		// 14.��������ͨ��״̬�£��޷��ͷż���
		if( IsIntonating() )
		{
			if( !bCheckOnly && !bNoTip )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_Busy ) );
				return FALSE;
			}
		}


		// 15.��������
		if( !bTargetTooFar )
			if( pSkill->ustPrepTime > 0 && !bCheckOnly )
			{
				AutoDisMount(pSkill);

				if ( IsGoBackSkill(pSkill->ustItemID) )
				{
					if (/*m_bMounting ||*/ m_bMoving || g_bTheRoleJumping)
					{
						//�˶��в�������
						if( !bCheckOnly && !bNoTip )
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_Motion_CantSing ) );
						return FALSE;
					}
				}
				else if( /*!m_bMounting &&*/ m_bMoving && !g_bTheRoleJumping ) //lyhע��m_bMounting ��������ƶ��оͲ����ͷ��������ܡ�
				{
					if( !IsMountMonsterSkill( pSkill->ustItemID ) )
					{
						//�˶��в�������
						if( !bCheckOnly && !bNoTip )
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_Motion_CantSing ) );
						return FALSE;
					}
				}
				/*
				else if( (m_bMounting&&!IsGoudaOperaMode()) || m_bMoving || g_bTheRoleJumping || HQ_TimeGetTime() - g_dwTheRoleJumpingEndTime < 400 )
				{
				//�˶��в�������
				if( !bCheckOnly && !bNoTip )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_Motion_CantSing ) );
				return FALSE;
				}
				*/
			}


			// 16.�ٻ����ж�
			if( pSkill->needpet && !HavePet() )
			{
				if( !bCheckOnly && !bNoTip )
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NeedPet ) );
				return FALSE;
			}


			// ����Ŀ��ѡ��ĵ��弼�ܣ�ѡ��ʱ����TRUE
			if( pSkill->shCastType == ItemDefine::casttype_singletarget 
				&& pSkill->usSpecialTargetType != ItemDefine::STT_NONE )
			{
				if( IsSelectingPoint() )		
					return TRUE;
				if( bCheckOnly )
					return TRUE;
			}


			// �ж��Ƿ���Ҫ�ܹ�ȥ�ż���
			if( bTargetTooFar )
			{
				if( !g_bTheRoleMovingByDir )
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_Skill_ChaseTarget ) );
					theHeroGame.GetPlayerMgr()->SetSkillBufPlayer(pTagPlayer);
					theHeroGame.GetPlayerMgr()->MoveRoleToPlayer(pTagPlayer, TRUE, 0.5f, TRUE, FALSE, TRUE);  // bCalibrate������IsInAttackRangeOnlyTwoPoint������bCalibrate����һ�£������ܹ�ȥ�᲻�ż���
				}
				else
				{
					if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_TooFar ) );
				}

				return FALSE;
			}

			if( shCastType == ItemDefine::casttype_singletarget ||
				shCastType == ItemDefine::casttype_singletargetcircleAOE ||
				shCastType == ItemDefine::casttype_AOETargetcirclearea )
			{
				// �ж��Ƿ����赲
				if( !bCheckOnly )
				{
					// ˲�Ƶ�����
					if (pSkill->ustInstantMovingType == IMT_TargetBack)
					{
						D3DXVECTOR3 vStart;
						D3DXVECTOR3 vDir = D3DXVECTOR3(0,0,0);
						float fRoleToCollision = 0;
						float fDistToTarget = GetDistToTarget( pTagPlayer->GetPos().x, pTagPlayer->GetPos().y );

						vDir.x = pTagPlayer->GetPos().x - m_x;
						vDir.y = pTagPlayer->GetPos().y - m_y;
						vDir.z = pTagPlayer->GetPos().z - m_z;

						D3DXVec3Normalize( &vDir, &vDir );

						vStart.x = GetPos().x;
						vStart.y = GetPos().y;
						vStart.z = GetPos().z + (g_fPlayerCollisionHeight)*GetMe3dConfig()->m_fMdlSpaceScale;  

						// �ж�ϥ�Ǹ߶�
						if(	theHeroGame.GetPlayerMgr()->CheckViewPlayerBBox(*(Vector*)&vDir,fDistToTarget - 0.5f) ||
							(thePlayerRole.GetDistToCollision( vStart, vDir, &fRoleToCollision, 0, 0, 0, FALSE ) && fRoleToCollision > 0 && fDistToTarget > fRoleToCollision + 0.5f) )
						{
							if( !bNoTip )
								CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_TargetNotInTheView ) );
							return FALSE;
						}
						else
						{
							// �ж�ͷ�������߶�
							vStart.z = GetPos().z + 1.6f;  
							if( thePlayerRole.GetDistToCollision( vStart, vDir, &fRoleToCollision, 0, 0, 0, FALSE ) && fRoleToCollision > 0 && fDistToTarget > fRoleToCollision + 0.5f )
							{
								if( !bNoTip )
									CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_TargetNotInTheView ) );
								return FALSE;
							}
						}
					}
					else
					{
						D3DXVECTOR3 vStart;
						D3DXVECTOR3 vDir = D3DXVECTOR3(0,0,0);

						vDir.x = pTagPlayer->GetPos().x - m_x;
						vDir.y = pTagPlayer->GetPos().y - m_y;
						vDir.z = pTagPlayer->GetPos().z - m_z;

						float fDistToTarget = sqrtf( vDir.x*vDir.x + vDir.y*vDir.y + vDir.z*vDir.z );

						D3DXVec3Normalize( &vDir, &vDir );

						vStart.x = GetPos().x;
						vStart.y = GetPos().y;
						vStart.z = GetPos().z + (g_fPlayerCollisionHeight)*GetMe3dConfig()->m_fMdlSpaceScale;

						float fRoleToCollision = 0;

						//lyh++ Ŀ�����赲�� �򲻽����赲��ײ���������֤���赲��ֻ���� ���� floor rcoli coli ����ģ�ͣ������ǹ��
						if(pTagPlayer && !pTagPlayer->IsMonsterType(eMT_Collision) )
							if(	theHeroGame.GetPlayerMgr()->CheckViewPlayerBBox(*(Vector*)&vDir,fDistToTarget - 0.5f) ||
								(thePlayerRole.GetDistToCollision( vStart, vDir, &fRoleToCollision, 0, 0, 0, FALSE, FALSE ) && fRoleToCollision > 0 && fDistToTarget > fRoleToCollision) /*+ 0.5f*/ )
							{
								if( !bNoTip )
									CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_TargetNotInTheView ) );
								return FALSE;
							}
					}
				}
			}
			else if( shCastType == ItemDefine::casttype_AOEPointCircleArea )
			{
				if( IsSelectingPoint() )	
					bSentServer = false;
			}


			//�ж����ڿɷ�ʹ�ü���
			if( bCheckOnly == false && bSentServer )
			{
				if( pTagPlayer)
				{
					if (!pTagPlayer->m_cFightStatus.IsCanBeMagAttack()) //Ŀ�괦�ڲ���ħ������
					{
						if ( pSkill->ustDamageBalanceType == ItemDefine::balancetype_damagemagicdefend)
						{
							return false; 
						}
					}
					if (!pTagPlayer->m_cFightStatus.IsCanBePhyAttack()) //Ŀ�괦�ڲ�������  
					{
						if ( pSkill->ustDamageBalanceType == ItemDefine::balancetype_damagephysicaldefend)
						{
							return false; 
						}
					}
				}
				thePlayerRole.SendMoveMessage( GetID(), m_x, m_y, m_z, m_vCurDir.x, m_vCurDir.y, g_dwLastFrameBeginTime, m_bMoving, 0, m_bLastFrameMoving );
				// ���������ܣ���ͨ�����ܣ��Ǵ�λ�Ƶ�˲�����ܣ����Ȳ�����
				if( pSkill->ustPrepTime <= 0 && pSkill->iDurationTime <=0 && !pSkill->bAssaultSkill && pSkill->ustInstantMovingType == IMT_None )
				{
					DWORD dwHitPointPlayTime;
					DWORD dwEndFrameTime;
					// �ж��Ƿ��Ѳ��ü��ܶ���
					if( m_vctAdvanceSkill.size() )
					{
						std::vector<SAdvanceSkillData>::iterator iter;
						for(iter = m_vctAdvanceSkill.begin(); iter != m_vctAdvanceSkill.end(); ++iter )
						{
							SAdvanceSkillData kAdvSkillData = *iter;
							// m_vctAdvanceSkill��������ͬ���ܣ��򲻷�����
							if( kAdvSkillData.pSkill && kAdvSkillData.pSkill == pSkill )
							{//1.�Ȱ���ͬ�����,�ں���ӻ�ȥ�ķ�ʽ�滻 by vvx 2013.11.22.
								m_vctAdvanceSkill.erase(iter);
								break;
								//return FALSE;
							}
						}
					}

					//if( thePlayerRole.GetProfession() != EArmType_Hunter )
					{
						if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
						{
							//�һ���ÿ���2�������������ս����Ϣ������̫Ƶ����
							if (GetTickCount() - s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().GetWaitBeginTime() < 2000 || theHeroGame.GetPlayerMgr()->GetMe()->IsIntonating() )
							{
								return FALSE;
							}

							goto Contioue; //�һ��� ������Ԥ���� ���÷�����ȥ�����Ų���
						}

						//lyh++duorenzuoji //���������� �Ǽ�ʻԱ�����ͷż���
						if(theHeroGame.GetPlayerMgr()&&
							theHeroGame.GetPlayerMgr()->GetMe()->IsMultiMounting() && 
							theHeroGame.GetPlayerMgr()->GetMe()->GetCarrierPlayerID() != theHeroGame.GetPlayerMgr()->GetMe()->GetID())
						{
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotDoIt ) );
							return false;
						}

						//�����ܲ����ͷż���
						if(theHeroGame.GetPlayerMgr()->GetMe()->IsIntonating())
						{
							return FALSE;
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_Busy ) );
						}

						if (pTagPlayer&&pTagPlayer->IsPlayer() && pTagPlayer != theHeroGame.GetPlayerMgr()->GetMe()) //����������ͷż���
						{
							//CWorldTile* pTile = CURRENTTILE;  //lyh++  ��ͼ�Ƿ���pk ���ж�
							if ( pSkill->sSkillCategory != ItemDefine::SCT_Assistant ) //��ǰ��ͼ��pk ���� Ŀ�����ҵ��д���� �����Խ���pk
							{
								if ( CheckMapCanPk(theHeroGame.GetPlayerMgr()->GetMe(),pTagPlayer))
								{
									//if( m_vctAdvanceSkill.size() == 0  )
									//{
									//	// ����Ԥ�����ܣ���Ϊ���ܿ϶���CD�������ڷ��������ص�һ�������˺�ǰ���ڶ��������ǷŲ��˵�
									//	if( m_cFightStatus.IsCanUseSkill( pSkill )) //lyh++ �����ǰ״̬����ʹ�ü��ܣ������ƶ�����Ԥ����
									//	{
									//		if( SwitchAttackAnim(pSkill->ustItemID, pSkill->ustLevel, &dwHitPointPlayTime, &dwEndFrameTime) )
									//		{
									//			SAdvanceSkillData kAdvanceSkill;
									//			kAdvanceSkill.pSkill = pSkill;
									//			kAdvanceSkill.dwBeginFrameTime = HQ_TimeGetTime();
									//			kAdvanceSkill.dwHitPointPlayTime = dwHitPointPlayTime;
									//			kAdvanceSkill.dwEndFrameTime = dwEndFrameTime;
									//			// �˺��ͼ��ܣ����ҵ�����Ŀ�꼼��
									//			if( pTagPlayer && pSkill->easyusedata.bSkillWithDamage && pSkill->shCastType == ItemDefine::casttype_singletarget 
									//				&& pSkill->ustCastTarget == ItemDefine::casttarget_enemylive )
									//			{
									//				kAdvanceSkill.nNeedPlayHurtAnim = CPlayer::ASH_NeedPlay;
									//				kAdvanceSkill.nTargetPlayerID = pTagPlayer->GetID();
									//			}
									//			else
									//			{
									//				kAdvanceSkill.nNeedPlayHurtAnim = CPlayer::ASH_NoNeedPlay;
									//				kAdvanceSkill.nTargetPlayerID = -1;
									//			}
									//			m_vctAdvanceSkill.push_back(kAdvanceSkill);
									//		}
									//	}										
									//}
									//else
									//	return FALSE;
								}else
								{
									CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
									return FALSE;
								}
								
							}
							else if ((pSkill->sSkillCategory == ItemDefine::SCT_Assistant && 
								shCastType == ItemDefine::casttype_singletarget  && 
								!CheckMapCanAssistant(theHeroGame.GetPlayerMgr()->GetMe(),pTagPlayer)))
							{
								pTagPlayer = this;
							}
							
						}
						else //����ֱ�ӷż���
						{
							//if( m_vctAdvanceSkill.size() == 0  )
							//{
							//	// ����Ԥ�����ܣ���Ϊ���ܿ϶���CD�������ڷ��������ص�һ�������˺�ǰ���ڶ��������ǷŲ��˵�
							//	if( m_cFightStatus.IsCanUseSkill( pSkill )) //lyh++ �����ǰ״̬����ʹ�ü��ܣ������ƶ�����Ԥ����
							//	{
							//		if( SwitchAttackAnim(pSkill->ustItemID, pSkill->ustLevel, &dwHitPointPlayTime, &dwEndFrameTime) )
							//		{
							//			SAdvanceSkillData kAdvanceSkill;
							//			kAdvanceSkill.pSkill = pSkill;
							//			kAdvanceSkill.dwBeginFrameTime = HQ_TimeGetTime();
							//			kAdvanceSkill.dwHitPointPlayTime = dwHitPointPlayTime;
							//			kAdvanceSkill.dwEndFrameTime = dwEndFrameTime;
							//			// �˺��ͼ��ܣ����ҵ�����Ŀ�꼼��
							//			if( pTagPlayer && pSkill->easyusedata.bSkillWithDamage && pSkill->shCastType == ItemDefine::casttype_singletarget 
							//				&& pSkill->ustCastTarget == ItemDefine::casttarget_enemylive )
							//			{
							//				kAdvanceSkill.nNeedPlayHurtAnim = CPlayer::ASH_NeedPlay;
							//				kAdvanceSkill.nTargetPlayerID = pTagPlayer->GetID();
							//			}
							//			else
							//			{
							//				kAdvanceSkill.nNeedPlayHurtAnim = CPlayer::ASH_NoNeedPlay;
							//				kAdvanceSkill.nTargetPlayerID = -1;
							//			}
							//			m_vctAdvanceSkill.push_back(kAdvanceSkill);
							//		}
							//	}
							//}
							//else
							//	return FALSE;			  
						}
					}
				} 
				else if(pSkill->ustPrepTime > 0 &&   //�������ĵ��帨������������
					pSkill->sSkillCategory == ItemDefine::SCT_Assistant && 
					shCastType == ItemDefine::casttype_singletarget&&
					!CheckMapCanAssistant(theHeroGame.GetPlayerMgr()->GetMe(),pTagPlayer))
				{
					pTagPlayer = this;
				}
Contioue:
				//if( pSkill->ustItemID == 1040 )
				//{
				//    char str[MAX_PATH] = {0};
				//    MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%s","Use Skill 1040, next skill not intonate");
				//    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, string(str));
				//}
				// ��漼�ܣ�Ԥ��ر�����Ƿ�����
				if( pSkill->bAssaultSkill )
				{
					D3DXVECTOR3 vDir = D3DXVECTOR3(0,0,0);
					float fDistToTarget = GetDistToTarget( pTagPlayer->GetPos().x, pTagPlayer->GetPos().y );
					float		fRoleHeight = 80.0f*Config::m_fMdlSpaceScale;

					vDir.x = pTagPlayer->GetPos().x - m_x;
					vDir.y = pTagPlayer->GetPos().y - m_y;
					D3DXVec3Normalize( &vDir, &vDir );

					BOOL bCanMove = TRUE;
					D3DXVECTOR3 vTestPos = D3DXVECTOR3(m_x,m_y,m_z);
					if( IsJumping() )   // ��Ծ�У�ȡ�ر�߶�
					{
						BOOL bInFloor = FALSE;
						DWORD dwLoadFlags = 0;
						vTestPos.z = GetZByXY( vTestPos.z+fRoleHeight, 
							vTestPos.x, vTestPos.y, 0, &bInFloor, &dwLoadFlags, true);
					}

					while( fDistToTarget > 0 )
					{
						if( fDistToTarget > 0.5f )
						{
							vTestPos.x += vDir.x * 0.5f;
							vTestPos.y += vDir.y * 0.5f;
							fDistToTarget -= 0.5;
						}
						else
						{
							vTestPos.x += vDir.x * fDistToTarget;
							vTestPos.y += vDir.y * fDistToTarget;
							fDistToTarget = 0;
						}

						DWORD		dwLoadFlags = 0;
						BOOL		bInFloor = FALSE;
						D3DXVECTOR3 vTargetNormal = D3DXVECTOR3(0,0,0);
						float       fHeadHeight = 1.7;
						Box*		pBBox = GetWorldBBox();
						if( pBBox )
							fHeadHeight = pBBox->v[4].z - pBBox->v[0].z;
						float       fZ = GetZByXY( vTestPos.z+fRoleHeight, 
							vTestPos.x, vTestPos.y, 0, &bInFloor, &dwLoadFlags, true, &vTargetNormal );
						// ����0.5�׵ĿӲ��ƶ�
						if( vTestPos.z - fZ > 0.5f )
						{
							bCanMove = FALSE;
							break;
						}
						else
							vTestPos.z = fZ;


						// �ж���б��
						D3DXVECTOR3 vAxis(0,0,1);
						D3DXVECTOR3 vUp( 0, 0, 1 );

						vAxis = vTargetNormal;
						D3DXVec3Normalize( &vAxis, &vAxis );
						float fDot = D3DXVec3Dot( &vUp, &vAxis );
						float fTheta = acosf( fDot );

						if( fTheta > g_fTheRoleSlipJumpingAngle && ( vAxis.x != 0 || vAxis.y != 0 ) )
						{
							bCanMove = FALSE;
							break;
						}
					}

					if( !bCanMove )
					{
						if( !bNoTip )
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_TargetNotInTheView ) );
						return FALSE;
					}
				}


				MsgReqSkillAttack msg;

				//����Ϣ֪ͨ����������ʼ������
				if( (pTagPlayer && shCastType == ItemDefine::casttype_singletarget ) ||
					shCastType == ItemDefine::casttype_AOETargetcirclearea )
				{
					msg.bCharTarget = true;
					msg.stWho = pTagPlayer->GetID();
				}
				else if( shCastType == ItemDefine::casttype_AOEPointCircleArea )
				{
					msg.bCharTarget = false;
					msg.vPos = m_vPointAoePos;
					msg.stWho = -1;
				}
				else
				{
					msg.bCharTarget = false;
					msg.stWho = -1;
				}

				msg.chSkillCount = 1;
				msg.stSkill = pSkill->ustItemID;

				// ���⴦��С�Ӽ���
				if( pSkill->specialSkillType >= ItemDefine::ESST_Team && pSkill->specialSkillType < ItemDefine::ESST_TeamMax )
				{
					if( iTeamSkillLevel > 0 )
						msg.stSkillLevel = iTeamSkillLevel;
					else
						return FALSE;
				}
				else
					msg.stSkillLevel = pSkill->ustLevel;


				AutoDisMount(pSkill);

				if( -1 == GettheNetworkInput().SendMsg( &msg ) )
				{
				}

				//����
				if( pSkill->ustPrepTime > 0 )
				{
					{
						SetIntonating( TRUE );
						SetIntonatingStartTime( g_dwLastFrameBeginTime );
						SwitchIntonateAnim( 0, pSkill );
						short stSingTime = pSkill->ustPrepTime;
						// 				if (m_cFightStatus.GetAddIntonateRate() != 0.0f)
						// 				{
						// 					float fTemp = (1.0f - m_cFightStatus.GetAddIntonateRate())*stSingTime;
						// 					stSingTime = fTemp;
						// 				}
						if (stSingTime <= 0)
						{
							stSingTime = 1;
						}

					}
				}

				//�ж��Ƿ��Զ���������Ŀ��
				if ( pSkill->bAutoAttackTarget && pTagPlayer )
				{
					bool canAttack = IsInAttackRange(pTagPlayer->GetPos().x, pTagPlayer->GetPos().y,
						pTagPlayer->GetBodyLengthSize(), 0);

					if( canAttack )
					{
						//����Ϣ֪ͨ������������������Ŀ��
						MsgAttackLockTarget	msg;
						g_bTheRoleAttackLockTarget = TRUE;

						if( GettheNetworkInput().SendMsg(&msg) == -1 )
						{
						}

						g_nRoleCommonAttackStatus = CAS_ATTACK_AGAIN_WHEN_FAILED;
					}
				}

				// �ж��Ƿ��ϸ���
				if( s_CUI_ID_FRAME_Target.GetFollowPlayerId() >= 0 )
				{
					s_CUI_ID_FRAME_Target.SetFollowPlayerId(-1);
				}
			}

			return TRUE;
			unguard;
}

//ʹ�ü���
BOOL    CPlayer::OperUseSkill(void)
{
	guardfunc;
	return TRUE;
	unguard;
}
//�Ի�
BOOL    CPlayer::OperTalk(void)
{
	guardfunc;
	if (IsCanTalk(m_operation.target.stDst))
	{
		//�ͻ��˽������ߵ�״̬(����)
		SwitchActionStatus( CPlayerStatus::esk_Talk, CStatusTimer::NoLimitDelay );
	}
	//
	return TRUE;
	unguard;
}
//ȡ�õ���
BOOL    CPlayer::OperGetItem(void)
{
	guardfunc;
	if (!IsDead())
	{
		//�ͻ��˽������ߵ�״̬(����)
		SwitchActionStatus( CPlayerStatus::esk_PickItem, CStatusTimer::NoLimitDelay );
	}
	//
	return TRUE;
	unguard;
}
//��������
BOOL    CPlayer::OperDropItem(void)
{
	guardfunc;
	if (!IsDead())
	{
		//�ͻ��˽������ߵ�״̬(����)
		SwitchActionStatus( CPlayerStatus::esk_DropItem, CStatusTimer::NoLimitDelay );
	}
	//
	return TRUE;
	unguard;
}

POINT	CPlayer::GetTargetMovePos( POINT ptNowPos, POINT ptTargetPos, int iAttackRange )
{
	guardfunc;
	POINT ptMovePos = ptTargetPos;
	if ( abs( ptNowPos.x - ptTargetPos.x ) <= iAttackRange )
	{
		ptMovePos.x = ptNowPos.x;
	}
	else
	{
		if ( ptNowPos.x > ptTargetPos.x )
		{
			ptMovePos.x = ptTargetPos.x + iAttackRange;
		}
		else
		{
			ptMovePos.x = ptTargetPos.x - iAttackRange;
		}
	}

	if ( abs( ptNowPos.y - ptTargetPos.y ) <= iAttackRange )
	{
		ptMovePos.y = ptNowPos.y;
	}
	else
	{
		if ( ptNowPos.y > ptTargetPos.y )
		{
			ptMovePos.y = ptTargetPos.y + iAttackRange;
		}
		else
		{
			ptMovePos.y = ptTargetPos.y - iAttackRange;
		}
	}
	return ptMovePos;
	unguard;
}

//����
BOOL    CPlayer::OperTrade(void)
{
	guardfunc;
	//
	SwitchActionStatus( CPlayerStatus::esk_Trade, CStatusTimer::NoLimitDelay );
	//
	return TRUE;
	unguard;
}

//ת��
BOOL    CPlayer::OperChangeDir(void)
{
	guardfunc;
	SwitchActionStatus( CPlayerStatus::esk_ChangeDir, CStatusTimer::NoLimitDelay );
	//
	return TRUE;
	unguard;
}

int GetNormalAttackByProfession( int iProfession )
{
	guardfunc;
	int iFirstAttackSkill;
	switch ( iProfession)
	{
		//սʿ
	case EArmType_Warrior:
		iFirstAttackSkill = ConstSkillId_NormalAttack_Warrior;
		break;
	case EArmType_Taoist:
		iFirstAttackSkill = ConstSkillId_NormalAttack_Taoist;
		break;
	case EArmType_Assassin:
		iFirstAttackSkill = ConstSkillId_NormalAttack_Assassin;
		break;
		//ħ��ʦ
	case EArmType_Mage:
		iFirstAttackSkill = ConstSkillId_NormalAttack_Mage;
		break;
	case EArmType_Hunter:
		iFirstAttackSkill = ConstSkillId_NormalAttack_Hunter;
		break;
	default:
		iFirstAttackSkill = ConstSkillId_NormalAttack_Combat;
		break;
	}


	if( theHeroGame.GetPlayerMgr()->GetMe() && !theHeroGame.GetPlayerMgr()->GetMe()->IsHaveWeapon() ) //lyh���鿴����ط��� ֻ�������õ�
	{
		iFirstAttackSkill = ConstSkillId_NormalAttack_Combat;
	}



	return iFirstAttackSkill;
	unguard;
}

//�ƶ���ȥʹ�ü���
BOOL    CPlayer::OperMoveSkill(void)
{
	guardfunc;

	int                 iFirstAttackSkill = -1;
	int					iFirstAttackSkillLevel = 0;
	int                 iAttackRange = 0,iTargetBodySize= 0;	
	ItemDefine::SItemSkill *pSkill = NULL;
	POINT               ptag;
	POINT               pnow;
	iFirstAttackSkill = m_operation.skill.iSkillID;
	iFirstAttackSkillLevel = m_operation.skill.iSkillLevel;
	OperUseSkill();

	//
	if ( 0 != GetActionQueue()->size())
	{
		return TRUE;
	}

	//�ȶ�Ӧ�ļ��ܵ�ǰ״̬�¿ɷ�ʹ��
	if (!IsSkillCanUseStatus(iFirstAttackSkill, iFirstAttackSkillLevel))
	{
		return FALSE;
	}

	if (0 <=  m_operation.target.stDst)
	{
		//�ж�����ʹ�õ�Ŀ���Ƿ����
		if (!IsTargetIsRight(iFirstAttackSkill, iFirstAttackSkillLevel, m_operation.target.stDst))
		{
			AddOperationIdle();
			return FALSE;
		}
	}

	//
	pSkill = GettheItemDetail().GetSkillByID(iFirstAttackSkill, iFirstAttackSkillLevel);
	if (NULL == pSkill)
	{
		AddOperationIdle();
		return FALSE;
	}

	//�ͷž���
	iAttackRange = pSkill->fRangeCanCast;
	if ( ConstSkillId_NormalAttack_Combat == m_operation.skill.iSkillID )
	{
		if( 1 < iAttackRange ) iAttackRange-=2;
	}
	//
	pnow = GetMapPos();

	//����һ��Ŀ��
	if (0 <=  m_operation.target.stDst)
	{
		CPlayer* pPlayerTag = theHeroGame.GetPlayerMgr()->FindByID( m_operation.target.stDst );
		if( NULL == pPlayerTag )
		{
			AddOperationIdle();
			return TRUE;
		}
		//�й�����Ŀ��

		//ȡ��Ŀ��ص�
		ptag = pPlayerTag->GetMapPos();
		iTargetBodySize = pPlayerTag->GetBodyLengthSize();
	}
	else
	{
		ptag.x = m_operation.target.x;
		ptag.y = m_operation.target.y;
		iTargetBodySize = 0;
	}

	//�ڹ�����Χ����Ҫ��ʼʹ�ü���
	if (!OperUseSkill())
	{
		AddOperationIdle();
		return  FALSE;
	}
	else
	{
		//����ʹ���˸ü���
		if (!m_operation.bAttackToDeadFlag) //�������Ҫ�������������л���idle״̬
		{
			AddOperationIdle();
		}
		else
		{
			if( !IsNormalAttack( iFirstAttackSkill ) )
			{
				//ִ����󣬽����ܱ����ͨ����
				m_operation.skill.iSkillID = GetNormalAttackByProfession( GetProfession() );
				m_operation.skill.iSkillLevel = 0;
			}
		}
		return TRUE;
	}	

	return TRUE;
	unguard;
}

//�ƶ���ȥ����
BOOL    CPlayer::OperMoveDroptem(void)
{
	guardfunc;
	//���˿��Լ���ߵľ����ˣ�ȥ�����
	return OperDropItem();
	unguard;
}

//��Ī������
BOOL    CPlayer::OperDoAction(void)
{
	guardfunc;
	return TRUE;
	unguard;
}

void CPlayer::JumpToMapPos( float x, float y, float z ,float xDir,float yDir)
{
	guardfunc;
	JumpToMapPos(x,y,z);
	float angle = atan2f( yDir,xDir) - D3DX_PI*0.5; 
	SetCurDir(angle);
	SetDir(angle);
	SetUpperDir(angle);
	SetCurUpperDir(angle);
	SetLowerDir(angle);
	SetCurLowerDir(angle);
	SwitchIdleAnim();
	getwsCamera()->SetCameraRotateX( fmodf((-angle - D3DX_PI*0.5), D3DX_PI*2 ) );
	if (getwsCamera()->GetCameraRotateX() < 0)
	{
		float zeta = getwsCamera()->GetCameraRotateX() + D3DX_PI*2;
		getwsCamera()->SetCameraRotateX( zeta );
	}
	getwsCamera()->SetCameraRotateXCorrect( 0 );
	getwsCamera()->SetCameraRotateXBuf( 0 );
	getwsCamera()->SetCameraRotateXBuf( 0 );
	getwsCamera()->SetCameraRotateZ( (float)( 16 - 90 )/180*D3DX_PI );

	getwsCamera()->SetCameraRotateX( fmodf( getwsCamera()->GetCameraRotateX(), D3DX_PI*2 ) );
	g_fTheRoleRotateZCorrect = getwsCamera()->GetCameraRotateX();
	g_fTheRoleDirCorrect = 0;
	unguard;
}

void CPlayer::JumpToMapPos( float x, float y, float z )
{
	guardfunc;

	m_x = x;
	m_y = y;
	FLOAT fUnKonwHeight = WORLD_HEIGHT*0.8; // ���ܰ�WORLD_HEIGHTֱ�Ӵ���ȥ���������0��ģ�͸߶Ȼ�ȡ����
	DWORD dwLoadFlags = 0;

	{
		if( IsPlayer() || IsNpc())
		{
			m_z = GetZByXY( 
				/*fUnKonwHeight*/z+80*Config::m_fMdlSpaceScale, // ���η���������Zֵ�������fUnKonwHeight��ʼ��ȡ�߶Ȼ�վ��������
				m_x,
				m_y,
				0,
				&m_bInFloor, 
				&dwLoadFlags,
				m_bRole );
		}
		else
		{
			m_z = GetZByXY(
				fUnKonwHeight,
				m_x,
				m_y,
				0,
				&m_bInFloor, 
				&dwLoadFlags, 
				FALSE );
		}
		m_vSaveXYGetZ = m_z;
		m_fTerrainZ	  = m_z;

		m_fLastGetZ_x = m_x;
		m_fLastGetZ_y = m_y;
		m_fLastGetZ_z = m_z;

	}

	ResetMove( 0xffffffff );

	if( IsRole() )
	{
		theHeroGame.GetPlayerMgr()->SetReLivedByPlayer(false);
	}
	unguard;
}

//---
//  �ж��Ƿ���һ�������״̬
//---
BOOL    CPlayer::IsMoveStepOver(void)
{
	guardfunc;
	if (0 == m_move.dwStartTime)
		return TRUE;
	//
	return FALSE;
	unguard;
}

bool CPlayer::IsTeamMember(const char* name)
{
	guardfunc;
	std::vector<TeamInfo> vecPlayer = thePlayerRole.GetTeamInfo();
	for(int i=0;i<vecPlayer.size();i++)
	{
		if(strcmp(vecPlayer[i].szName.c_str(), name ) == 0 )
		{
			return true;
		}
	}
	return false;
	unguard;
}

BOOL CPlayer::ReqCancelSkill()
{
	guardfunc;
	SkillRuntimeDesc* desc = &m_skillRuntimeDesc;
	if( desc->IsCancelHasSent() )
		return FALSE;
	Msg_ReqCancelSkill msgReqCancelSkill;
	if( -1 == GettheNetworkInput().SendMsg( &msgReqCancelSkill ) )
	{
	}
	desc->Cancel( HQ_TimeGetTime() );
	return TRUE;

	unguard;
}

BOOL CPlayer::CancelSkill()
{
	guardfunc;
	return TRUE;
	unguard;
}


void CPlayer::CaluHPPercent(void)
{
	guardfunc;
	if( !m_hpinfo.bIsValid )
		return;
	//��ʼ��
	float f;
	f = m_hpinfo.nHp;
	f /= m_hpinfo.nHpMax;
	if( f > 1 )
		f = 1;
	if( f < 0 )
		f = 0;

	if( m_hpinfo.fShowPercent < 0 )
	{
		m_hpinfo.fPrevPercent = f;
		m_hpinfo.fShowPercent = f;
	}
	else
	{
		m_hpinfo.fPrevPercent = m_hpinfo.fShowPercent;
	}

	m_hpinfo.fTargetPercent = f;
	m_hpinfo.fPercent = 0;
	m_hpinfo.dwLastShow = HQ_TimeGetTime();
	unguard;
}

void CPlayer::SetHPInfo( int nHp, int nHpMax )
{
	guardfunc;
	m_hpinfo.bIsValid = true;
	if( 0 == nHpMax )
		nHpMax = 1;
	m_hpinfo.nHp = nHp;
	m_hpinfo.nHpMax = nHpMax;
	CaluHPPercent();
	unguard;
}

void CPlayer::SetHPInfo_HP( int nHp )
{
	guardfunc;
	if (nHp > m_hpinfo.nHpMax )
	{
		nHp = m_hpinfo.nHpMax;
	}
	m_hpinfo.nHp = nHp;
	CaluHPPercent();
	unguard;
}

void CPlayer::SetMPInfo_MPChange( int nMp )
{
	guardfunc;
	m_charSimpleInfo.nMp += nMp;
	if( m_charSimpleInfo.nMp < 0 )
		m_charSimpleInfo.nMp = 0;
	else if (m_charSimpleInfo.nMp > m_charSimpleInfo.nMpMax )
	{
		m_charSimpleInfo.nMp = m_charSimpleInfo.nMpMax;
	}
	unguard;
}

void CPlayer::SetHPInfo_HPChange( int nHp )
{
	guardfunc;
	//#ifdef _DEBUG
	//	if (nHp < 0)
	//	{
	//		char szBuf[256];
	//		MeSprintf_s( szBuf, 256, "HP�ı� = %d.��ǰHP=%d", hptem1 ,m_hpinfo.nHp);
	//		s_CUI_ChatInfoBox.AddInfo( szBuf, 0xffff0000);		
	//	}
	//#endif //_DEBUG
	m_hpinfo.nHp += nHp;
	if( m_hpinfo.nHp < 0 )
		m_hpinfo.nHp = 0;
	else if (m_hpinfo.nHp > m_hpinfo.nHpMax )
	{
		m_hpinfo.nHp = m_hpinfo.nHpMax;
	}
	CaluHPPercent();
	unguard;
}
void CPlayer::SetHPInfo_HPMax( int nHpMax )
{
	guardfunc;
	if( 0 >= nHpMax )
		nHpMax = 1;
	m_hpinfo.nHpMax = nHpMax;
	CaluHPPercent();
	unguard;
}

void CPlayer::ResetHPInfo( void )
{
	guardfunc;
	m_hpinfo.bIsValid = false;
	m_hpinfo.fShowPercent = -1;
	unguard;
}

void CPlayer::DecHP( int iHPDec )
{
	guardfunc;
	if( m_hpinfo.nHp > iHPDec )
		m_hpinfo.nHp -= iHPDec;
	else
		m_hpinfo.nHp = 0;
	CaluHPPercent();
	unguard;
}
void CPlayer::IncHP( int iHPDec )
{
	guardfunc;
	m_hpinfo.nHp += iHPDec;
	if (m_hpinfo.nHp > m_hpinfo.nHpMax)
		m_hpinfo.nHp = m_hpinfo.nHpMax;
	if (m_hpinfo.nHp < 0)
		m_hpinfo.nHp = 0;
	CaluHPPercent();
	unguard;
}

void CPlayer::CheckBodyStatusEff(void)
{
	guardfunc;
	SCharBuff* pStatus;
	int		old_status_id;
	bool	status_flag = false;
	for (int i=0; i<m_cFightStatus.GetBufferStatusCount(); i++)
	{
		status_flag = false;
		//
		pStatus = m_cFightStatus.GetBuff(i);
		if (NULL != pStatus)
		{
			ItemDefine::SItemStatus*  pItemStatus = NULL;
			pItemStatus = GettheItemDetail().GetStatus(pStatus->StatusID, pStatus->iLevel);
			old_status_id = pStatus->StatusID;
			if (!IsDead()) //ֻ�л��˲���Ҫ״̬����ͼЧ����
			{
				if (NULL != pItemStatus)
				{
					status_flag = true;
				}
			}
			else
			{
				old_status_id = 0; //��������Ҫ������ϵ�״̬��
			}
		}
	}
	unguard;
}

//��������������е�״̬
void CPlayer::ClearAllBodyStatusEff(void)
{
	guardfunc
		m_cFightStatus.ClearAllBuff();
	unguard
}

void CPlayer::SetEquip( CPlayer_SEquipment* equips )
{
	guardfunc;
	memcpy( m_equips, equips, sizeof(m_equips) );
	unguard;
}

//�趨 ĳ����λ��װ��
void CPlayer::SetEquip( short stWhere,SCharItem *pItem )
{
	guardfunc;
	int iProfession = 0, iSex =0;

	if( stWhere < 0 || stWhere >= eKeyAll_Max )
		return;
	CPlayer_SEquipment *pEquip = &m_equips[ stWhere ];

	ItemDefine::SItemCommon *pItemCommon = NULL;

	iProfession = GetProfession();
	iSex = GetSex();
	if (iProfession <0 || iProfession>= EArmType_MaxSize)
		iProfession = 0;
	if (iSex <0 || iSex>= Sex_Max)
		iSex = 0;

	CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(mHeroID);

	int temp = -1;

	//ͷ��ֱ����ģ��ID
	if (eKeyAll_Hair == stWhere)
	{
		PlayerInfoMgr::Instance()->SetPlayerFaceAndHair(this, -1, source_hairid, temp, pEquip->iModelID);
		pEquip->iModelID2  = InvalidLogicNumber;
		pEquip->iModelID3  = InvalidLogicNumber;
	}
	else if (eKeyAll_Face == stWhere)
	{
		PlayerInfoMgr::Instance()->SetPlayerFaceAndHair(this, source_faceid, -1, pEquip->iModelID, temp);
		pEquip->iModelID2  = InvalidLogicNumber;
		pEquip->iModelID3  = InvalidLogicNumber;
	}
	else
	{
		if( pItem )
		{	
			pEquip->item = *pItem;
			pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
		}
		else
		{
			pItemCommon = 0;
		}
		if( !pItemCommon )
		{		
			pEquip->iModelID = InvalidLogicNumber;		
			pEquip->iModelID2 = InvalidLogicNumber;		
			pEquip->iModelID3 = InvalidLogicNumber;	
		}
		else
		{
			switch( pItemCommon->ucItemType ) 
			{
			case ItemDefine::ITEMTYPE_WEAPON:
				{
					ItemDefine::SItemWeapon *pItemCanEquip = NULL;
					pItemCanEquip = ( ItemDefine::SItemWeapon *) pItemCommon;
					pEquip->iModelID  = pItemCanEquip->ustModelID[ 0 ];
					pEquip->iModelID2  = pItemCanEquip->ustModelID[ 1 ];
					pEquip->iModelID3 = pItemCanEquip->ustIdleModelID;
					SetWeaponSound( pItemCanEquip->GetSound());
				}
				break;
			case ItemDefine::ITEMTYPE_ARMOUR:
				{
					ItemDefine::SItemArmour *pItemCanEquip = NULL;
					pItemCanEquip = ( ItemDefine::SItemArmour *) pItemCommon;

					int nProfessionIndex=0;
					for ( nProfessionIndex=0; nProfessionIndex<EArmType_MaxSize; nProfessionIndex++ )
					{
						if ( pItemCanEquip->ustModelID[nProfessionIndex][iSex][0] != InvalidLogicNumber
							|| pItemCanEquip->ustModelID[nProfessionIndex][iSex][1] != InvalidLogicNumber)
						{
							break;
						}
					}
					pEquip->iModelID  = pItemCanEquip->ustModelID[nProfessionIndex][iSex][0];
					pEquip->iModelID2  = pItemCanEquip->ustModelID[nProfessionIndex][iSex][1];
#pragma message("����ְҵ��װ����  ����")
					pEquip->iModelID3 = InvalidLogicNumber;

					int nArmourValue = 1;
					nArmourValue <<= 1;
					if( pItemCanEquip->ustEquipType == 2 )
					{
						SetArmourSound( pItemCanEquip->GetSound() );
					}
				}
				break;
			default:
				pEquip->iModelID = InvalidLogicNumber;
				pEquip->iModelID2  = InvalidLogicNumber;
				pEquip->iModelID3  = InvalidLogicNumber;
				break;
			}
		}
	}

	unguard;
}

bool CPlayer::IsHPInfoValid(void)
{
	guardfunc;
	return m_hpinfo.bIsValid;
	unguard;
}

void SetAllEquip(int iProfession, int iSex,  CPlayer_SEquipment* pEquip, SCharVisual* pVisual, CPlayer* pPlayer,bool isShowHero,int& source_hair,int& source_face )
{
	guardfunc;
	ItemDefine::SItemCommon *pItemCommon = NULL;

	source_hair = pVisual->hairId;
	source_face = pVisual->faceId;
	//PlayerInfoMgr::Instance()->SetPlayerFaceAndHair(pPlayer, pVisual->faceId, pVisual->hairId, pEquip[eKeyAll_Face].iModelID, pEquip[eKeyAll_Hair].iModelID);
	CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(pPlayer != NULL ? pPlayer->GetHeroID() : INVALID_HERO_ID);
	if (itemHero != NULL&&isShowHero)
	{		
		pEquip[eKeyAll_Hair].iModelID = itemHero->hero_faxing;
		pEquip[eKeyAll_Face].iModelID = itemHero->hero_lianxing;
	}
	else
	{
		if(source_hair != -1)
		{
			pEquip[eKeyAll_Hair].iModelID = source_hair;
		}
		else
			pEquip[eKeyAll_Hair].iModelID = pVisual->hairId;

		if(source_face != -1)
		{
			pEquip[eKeyAll_Face].iModelID = source_face;
		}
		else
		{
			pEquip[eKeyAll_Face].iModelID = pVisual->faceId;
		}
		/*pEquip[eKeyAll_Hair].iModelID = pVisual->hairId;
		pEquip[eKeyAll_Face].iModelID = pVisual->faceId;*/
	}

	SCharItem *pItem = pVisual->GetVisualArray();
	for(int i = 0 ; i < EEquipPartType_MaxEquitPart; ++i)
	{
		int j = CEquipPartMap::Instance()->GetLogicPart(i);
		pEquip[j].item = pItem[i];
		pItemCommon = GettheItemDetail().GetItemByID( pItem[i].itembaseinfo.ustItemID );
		if( !pItemCommon )
		{			
			pEquip[j].iModelID = InvalidLogicNumber;
			pEquip[j].iModelID2 = InvalidLogicNumber;
			pEquip[j].iModelID3 = InvalidLogicNumber;
			continue;
		}
		pEquip[j].item.itembaseinfo.ustItemID = pItem[i].itembaseinfo.ustItemID;

		switch( pItemCommon->ucItemType ) 
		{
		case ItemDefine::ITEMTYPE_WEAPON:
			{
				ItemDefine::SItemWeapon *pItemCanEquip = NULL;
				pItemCanEquip = ( ItemDefine::SItemWeapon *) pItemCommon;
				pEquip[j].iModelID  = pItemCanEquip->ustModelID[0];
				pEquip[j].iModelID2  = pItemCanEquip->ustModelID[1];
				pEquip[j].iModelID3 = pItemCanEquip->ustIdleModelID;
				if( pPlayer )
				{
					pPlayer->SetWeaponSound( pItemCanEquip->GetSound() );
				}
			}
			break;
		case ItemDefine::ITEMTYPE_ARMOUR:
			{
				ItemDefine::SItemArmour *pItemCanEquip = NULL;
				pItemCanEquip = ( ItemDefine::SItemArmour *) pItemCommon;

				int nProfessionIndex=0;
				for ( nProfessionIndex=0; nProfessionIndex<EArmType_MaxSize; nProfessionIndex++ )
				{
					if ( pItemCanEquip->ustModelID[nProfessionIndex][iSex][0] != 
						InvalidLogicNumber 
						|| pItemCanEquip->ustModelID[nProfessionIndex][iSex][1] != 
						InvalidLogicNumber 
						)
					{
						break;
					}
				}
				pEquip[j].iModelID  = pItemCanEquip->ustModelID[nProfessionIndex][iSex][0];
				pEquip[j].iModelID2  = pItemCanEquip->ustModelID[nProfessionIndex][iSex][1];
#pragma message("����ְҵ��װ����  ����")
				pEquip[j].iModelID3 = InvalidLogicNumber;

				int nArmourEquipType = 1;
				nArmourEquipType <<=1;
				if( pPlayer && pItemCanEquip->ustEquipType == nArmourEquipType )
				{
					pPlayer->SetArmourSound( pItemCanEquip->GetSound() );
				}
			}
			break;
		default:
			pEquip[j].iModelID = InvalidLogicNumber;
			pEquip[j].iModelID2  = InvalidLogicNumber;
			pEquip[j].iModelID3  = InvalidLogicNumber;
			break;
		}
	}
	unguard;
}


void CPlayer::SetAllEquip(/* SCharItem *pItem */SCharVisual* pVisual, bool isautocs)
{
	guardfunc;
	int iProfession, iSex ;
	iProfession = GetProfession();
	iSex = GetSex();
	if (iProfession <0 || iProfession>= EArmType_MaxSize)
		iProfession = 0;
	if (iSex < 0 || iSex >= Sex_Max)
		iSex = 0;

	::SetAllEquip( iProfession, iSex, m_equips, pVisual, this,IsSHowHero(),source_hairid,source_faceid);
	if (isautocs)
	{
		AutoCS();
	}	
	unguard;
}

void CPlayer::EquipByItemID(uint16 stItemID[], uint8 equipIntensifyTime[], uint8 equipIntensifyStar[], uint8 equipElements[] )
{
	guardfunc;
	SetEquipByItemID(stItemID, equipIntensifyTime, equipIntensifyStar, equipElements, m_equips);
	CalcMinimalStar();
	unguard;
}

void CPlayer::SetEquipPart(int nWhere,short stItemId)
{
	if(nWhere < 0 || nWhere >= eKeyAll_Max)
		return;

	m_equips[nWhere].iModelID = stItemId;
	if(eKeyAll_Hair == nWhere)
	{
		source_hairid = stItemId;
	}
	else if(eKeyAll_Face == nWhere)
	{
		source_faceid = stItemId;
	}
}

void CPlayer::SetEquipByItemID(uint16 stItemID[EEquipPartType_MaxEquitPart], uint8 equipIntensifyTime[EEquipPartType_MaxEquitPart], uint8 equipIntensifyStar[EEquipPartType_MaxEquitPart], uint8 equipElements[EEquipPartType_MaxEquitPart], CPlayer_SEquipment* pEquip)
{
	guardfunc;
	int iProfession, iSex ;
	iProfession = GetProfession();
	iSex = GetSex();
	if (iProfession <0 || iProfession>= EArmType_MaxSize)
		iProfession = 0;
	if (iSex <0 || iSex>= Sex_Max)
		iSex = 0;

	ItemDefine::SItemCommon *pItemCommon;
	for( int i = 0 ; i < EEquipPartType_MaxEquitPart; ++i)
	{
		int nPart = CEquipPartMap::Instance()->GetLogicPart(i);
		pEquip[nPart].item.itembaseinfo.ustItemID = stItemID[i];
		pEquip[nPart].item.equipdata.gemHoleCount = equipIntensifyTime[i];
		pEquip[nPart].item.equipdata.ucLevel = equipIntensifyStar[i];
		pEquip[nPart].item.itembaseinfo.value1 = ( pEquip[nPart].item.itembaseinfo.value1 & 0xffffff00 | equipElements[i] );

		pItemCommon = GettheItemDetail().GetItemByID( stItemID[i] );
		if( !pItemCommon )
		{
			pEquip[nPart].iModelID = InvalidLogicNumber;
			pEquip[nPart].iModelID2 = InvalidLogicNumber;
			pEquip[nPart].iModelID3 = InvalidLogicNumber;
			continue;
		}
		switch( pItemCommon->ucItemType ) 
		{
		case ItemDefine::ITEMTYPE_WEAPON:
			{
				ItemDefine::SItemWeapon *pItemCanEquip = NULL;
				pItemCanEquip = ( ItemDefine::SItemWeapon *) pItemCommon;
				pEquip[nPart].iModelID  = pItemCanEquip->ustModelID[0];
				pEquip[nPart].iModelID2  = pItemCanEquip->ustModelID[1];
				pEquip[nPart].iModelID3 = pItemCanEquip->ustIdleModelID;

				if( this )
				{
					this->SetWeaponSound( pItemCanEquip->GetSound() );
				}
			}
			break;
		case ItemDefine::ITEMTYPE_ARMOUR:
			{
				ItemDefine::SItemArmour *pItemCanEquip = NULL;
				pItemCanEquip = ( ItemDefine::SItemArmour *) pItemCommon;

				int nProfessionIndex=0;
				for ( nProfessionIndex=0; nProfessionIndex<EArmType_MaxSize; nProfessionIndex++ )
				{
					if ( pItemCanEquip->ustModelID[nProfessionIndex][iSex][0] != 
						InvalidLogicNumber 
						|| pItemCanEquip->ustModelID[nProfessionIndex][iSex][1] != 
						InvalidLogicNumber 
						)
					{
						break;
					}
				}
				pEquip[nPart].iModelID  = pItemCanEquip->ustModelID[nProfessionIndex][iSex][0];
				pEquip[nPart].iModelID2  = pItemCanEquip->ustModelID[nProfessionIndex][iSex][1];
#pragma message("����ְҵ��װ����  ����")
				pEquip[nPart].iModelID3 = InvalidLogicNumber;
				int nArmourEquipType = 1;
				nArmourEquipType <<=1;
				if( this && pItemCanEquip->ustEquipType == nArmourEquipType )
				{
					this->SetArmourSound( pItemCanEquip->GetSound() );
				}
			}
			break;
		default:
			pEquip[nPart].iModelID = InvalidLogicNumber;
			pEquip[nPart].iModelID2  = InvalidLogicNumber;
			pEquip[nPart].iModelID3  = InvalidLogicNumber;
			break;
		}
	}



	unguard;
}

void CPlayer::ChangeSkeletonAndEquipAllItem( bool bFightFlag)
{
	guardfunc;
	if( !m_pAnim )
		return;

	//bool showHelmet = IsShowHelmet() || IsShowAecpratove();

	m_pAnim->ChangeSkeletonAndEquipAll(
		&m_equips,
		GetSex(),
		GetProfession(), 
		m_nHairColorIndex,
		IsShowHelmet(), IsShowAecpratove(),GetDefAvaterIndex(), GetHeroID(),IsSHowHero());
	unguard;
}

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
//���������꣬�������Ļ����
void	World2Screen( D3DXVECTOR3 vPos,int &x,int &y )
{
	guardfunc;
	MeCamera *pCamera =  getwsCamera()->GetMeCamera();
	D3DXMATRIX mat = pCamera->GetViewXProj();
	D3DXVec3TransformCoord( &vPos,&vPos,&mat );
	//
	vPos.x -= -1.0f;
	vPos.x *= SCREEN_WIDTH;
	x = vPos.x;
	x/= 2;

	vPos.y -= -1.0f;
	vPos.y *= SCREEN_HEIGHT;
	y = vPos.y;
	y/= 2;

	y = SCREEN_HEIGHT - y;
	unguard;
}

void World3Screen( int x, int y, float fDistance, D3DXVECTOR3& vPos )
{
	guardfunc;
	MeCamera *pCamera =  getwsCamera()->GetMeCamera();

	D3DXVECTOR3 vStart;
	D3DXVECTOR3 vDir;

	pCamera->BuildPickRay( x, y, vStart,vDir, SCREEN_WIDTH, SCREEN_HEIGHT );

	vPos = vStart + vDir*16;

	unguard;
}

BOOL CPlayer::OnShowFlyText( int nBalanceType, int nNum, int nAddNum /* = 0 */, int nWordType /*= 0*/,bool bIsPlayer/* = false  */)
{
	guardfunc;
	D3DXVECTOR3 pos = GetPos();
	pos.z += g_fTheRoleBBoxHeight;

	int xEffect = 0,yEffect = 0;
	World2Screen( pos,xEffect,yEffect );
	if (nNum < 0)
	{
		return TRUE;
	}

	// 	g_pFlyTextEffect->Create( nBalanceType, xEffect, yEffect, nNum, -1, FALSE, pos, 0, nWordType );
	// 	return TRUE;
	//switch(nBalanceType)
	{
		// 	case CItemDetail::balance_status_type_life_stolen:
		// 		{
		// 			if(bIsPlayer)
		// 			{
		// 				g_pFlyTextEffect->Create( CFlyTextEffect::eNumberAttackWhite, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
		// 			}
		// 			else
		// 			{
		// 				g_pFlyTextEffect->Create( CFlyTextEffect::eNumberYellow, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
		// 			}
		// 		}
		// 		break;
		// 	case CItemDetail::balance_status_type_life_trans:
		// 		{
		// 			if(bIsPlayer)
		// 			{
		// 				g_pFlyTextEffect->Create( CFlyTextEffect::eNumberAttackWhite, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
		// 			}
		// 			else
		// 			{
		// 				g_pFlyTextEffect->Create( CFlyTextEffect::eNumberYellow, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
		// 			}
		// 		}
		// 		break;
		// 	case CItemDetail::balance_status_type_manaburn:
		// 		break;
		//default:
		if( nWordType == GlobalTexture::eAddExp )
			g_pFlyTextEffect->Create( CFlyTextEffect::eNumberAddEXP, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
		else if( nWordType == GlobalTexture::eAddMingWang )
			g_pFlyTextEffect->Create( CFlyTextEffect::eNumberMingWang, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
		else if( nWordType == GlobalTexture::eAddGongXun )
			g_pFlyTextEffect->Create( CFlyTextEffect::eNumberGongXun, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
		else if( nWordType == GlobalTexture::eAddBangGong )
			g_pFlyTextEffect->Create( CFlyTextEffect::eNumberBangGong, xEffect, yEffect, nNum,GetID(), FALSE, pos, nAddNum, nWordType );
		else if( nWordType == GlobalTexture::eAddAreaReputation )
			g_pFlyTextEffect->Create( CFlyTextEffect::eNumberAreaReputation, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
		else if( nWordType == GlobalTexture::eAddRongYu )
			g_pFlyTextEffect->Create( CFlyTextEffect::eNumberRongYu, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
		else if(nWordType == GlobalTexture::eAddSkillExp) //���Ӽ��ܾ���
			g_pFlyTextEffect->Create(CFlyTextEffect::eNumberAddSkillEXP,xEffect,yEffect,nNum,GetID(),FALSE,pos,nAddNum,nWordType);
		else
		{
			if(bIsPlayer)
				g_pFlyTextEffect->Create( CFlyTextEffect::eNumberAttackWhite, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
			else
				g_pFlyTextEffect->Create( CFlyTextEffect::eNumberYellow, xEffect, yEffect, nNum, GetID(), FALSE, pos, nAddNum, nWordType );
		}
	}

	return TRUE;
	unguard;
}

bool CPlayer::OnShowFlyText( CPlayer *pTagPlayer, CPlayer *pSrcPlayer, int iBalanceType, int iTagNum, int iScNum,
							int nAddNum /* = 0 */, bool bExplosive /* = false  */)
{
	guardfunc;
	int nWordType = 0;
	if( bExplosive )
		nWordType = GlobalTexture::eCruelHit;

	if (pTagPlayer == NULL || pSrcPlayer == NULL)
	{
		return false;
	}

	if( pTagPlayer->IsCollection(false)
		|| pTagPlayer->GetMonsterType() == eMT_Building )
	{
		return false;
	}

	int xEffect = -1,yEffect = -1;
	D3DXVECTOR3 pos = D3DXVECTOR3( 0, 0, 0 );
	if (pSrcPlayer->IsRole() && pTagPlayer->IsRole())
	{
		pos = pSrcPlayer->GetPos();
		World2Screen( pos,xEffect,yEffect );
	}
	switch (iBalanceType)
	{
	case ItemDefine::balancetype_restorehpmp://��HP����
		{
			D3DXVECTOR3 pos = pTagPlayer->GetPos();
			pos.z += g_fTheRoleBBoxHeight;
			World2Screen( pos,xEffect,yEffect );
			if(nAddNum == -1)
			{//����
				g_pFlyTextEffect->Create(CFlyTextEffect::eNumberBlue, xEffect, yEffect, -1 * iTagNum, pTagPlayer->GetID(), FALSE, pos);
			}
			else
			{
				g_pFlyTextEffect->Create(CFlyTextEffect::eNumberGreen, xEffect, yEffect, -1 * iTagNum, pTagPlayer->GetID(), FALSE, pos);
			}
		}
		break;
	case ItemDefine::balancetype_none://û���κν���
		break;
	case ItemDefine::balancetype_damagemagicdefend://ħ���˺�����
		{
			if (!pSrcPlayer)
				break;

			if (iTagNum != 0)
			{
				D3DXVECTOR3 pos = pTagPlayer->GetPos();
				pos.z += g_fTheRoleBBoxHeight;

				int xEffect = 0,yEffect = 0;
				if(	iTagNum > 0)
				{
					World2Screen( pos,xEffect,yEffect );
					if( pTagPlayer->IsRole() || pTagPlayer->MasterIsMe() )	//�ִ���
					{
						if(pSrcPlayer->IsPlayer())
							g_pFlyTextEffect->Create( CFlyTextEffect::eNumberBeAttackYellow, xEffect, yEffect, iTagNum, pTagPlayer->GetID() , FALSE, pos, nAddNum, nWordType );
						else
							g_pFlyTextEffect->Create( CFlyTextEffect::eNumberRed, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), FALSE, pos, nAddNum, nWordType );
					}
					else if( pSrcPlayer->IsRole() || pSrcPlayer->MasterIsMe() ) // �Ҵ��
					{
						if(pTagPlayer->IsPlayer())
						{
							if( bExplosive )
								g_pFlyTextEffect->Create( CFlyTextEffect::eNumberAttackWhite, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), TRUE, pos, nAddNum, GlobalTexture::eCruelHit );
							else
								g_pFlyTextEffect->Create( CFlyTextEffect::eNumberAttackWhite, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), TRUE, pos, nAddNum, 0 );
						}
						else
						{
							if( bExplosive )
								g_pFlyTextEffect->Create( CFlyTextEffect::eNumberYellow, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), TRUE, pos, nAddNum, GlobalTexture::eCruelHit );
							else
								g_pFlyTextEffect->Create( CFlyTextEffect::eNumberYellow, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), TRUE, pos, nAddNum, 0 );
						}
					}
				}

			}
			//
			if (iScNum != 0)
			{
				D3DXVECTOR3 pos = pSrcPlayer->GetPos();
				pos.z += g_fTheRoleBBoxHeight;

				int xEffect,yEffect;
				World2Screen( pos,xEffect,yEffect );
				if (iScNum > 0)
					g_pFlyTextEffect->Create(CFlyTextEffect::eNumberRed, xEffect, yEffect, iScNum, pSrcPlayer->GetID(), FALSE, pos, 0, 0 );
				else
					g_pFlyTextEffect->Create(CFlyTextEffect::eNumberGreen, xEffect, yEffect, -1 * iScNum, pSrcPlayer->GetID(), FALSE, pos, 0, 0 );
			}
		}
		break;
	case ItemDefine::balancetype_damagephysicaldefend://�˺�����
	case ItemDefine::balancetype_relive://�������
		//	case ItemDefine::balancetype_addextrahp://˲����Ѫ
	default:
		if (!pSrcPlayer)
			break;

		if (iTagNum != 0)
		{
			D3DXVECTOR3 pos = pTagPlayer->GetPos();
			pos.z += g_fTheRoleBBoxHeight;

			int xEffect = 0,yEffect = 0;
			if(	iTagNum > 0)
			{
				World2Screen( pos,xEffect,yEffect );
				if( pTagPlayer->IsRole() || pTagPlayer->MasterIsMe() )	//�ִ���
				{
					if(pSrcPlayer->IsPlayer())
						g_pFlyTextEffect->Create( CFlyTextEffect::eNumberBeAttackYellow, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), FALSE, pos, nAddNum, nWordType );
					else
						g_pFlyTextEffect->Create( CFlyTextEffect::eNumberRed, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), FALSE, pos, nAddNum, nWordType );
				}
				else if( pSrcPlayer->IsRole() || pSrcPlayer->MasterIsMe() ) // �Ҵ��
				{
					if(pTagPlayer->IsPlayer())
					{
						if( bExplosive )
							g_pFlyTextEffect->Create( CFlyTextEffect::eNumberAttackWhite, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), TRUE, pos, nAddNum, GlobalTexture::eCruelHit );
						else
							g_pFlyTextEffect->Create( CFlyTextEffect::eNumberAttackWhite, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), TRUE, pos, nAddNum, 0 );
					}
					else
					{
						if( bExplosive )
							g_pFlyTextEffect->Create( CFlyTextEffect::eNumberYellow, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), TRUE, pos, nAddNum, GlobalTexture::eCruelHit );
						else
							g_pFlyTextEffect->Create( CFlyTextEffect::eNumberWhite, xEffect, yEffect, iTagNum, pTagPlayer->GetID(), TRUE, pos, nAddNum, 0 );
					}
				}
			}

		}
		//
		if (iScNum != 0)
		{
			D3DXVECTOR3 pos = pSrcPlayer->GetPos();
			pos.z += g_fTheRoleBBoxHeight;

			int xEffect,yEffect;
			World2Screen( pos,xEffect,yEffect );
			if (iScNum > 0)
				g_pFlyTextEffect->Create(CFlyTextEffect::eNumberRed, xEffect, yEffect, iScNum, pSrcPlayer->GetID(), FALSE, pos, 0, 0 );
			else
				g_pFlyTextEffect->Create(CFlyTextEffect::eNumberGreen, xEffect, yEffect, -1 * iScNum, pSrcPlayer->GetID(), FALSE, pos, 0, 0 );
		}
		break;
	}
	return false;
	unguard;
}

bool	CPlayer::OnShowFlyPic( int nType )
{
	guardfunc;
	D3DXVECTOR3 pos = GetPos();
	pos.z += g_fTheRoleBBoxHeight;
	int xEffect = 0,yEffect = 0;
	World2Screen( pos,xEffect,yEffect );

	switch( nType )
	{
	case CFlyTextEffect::eMiss:
		g_pFlyTextEffect->Create( CFlyTextEffect::eMiss, xEffect, yEffect, 0, GetID(), TRUE, pos, 0, false );
		break;
	case CFlyTextEffect::eMonsterWard:
		g_pFlyTextEffect->Create( CFlyTextEffect::eMonsterWard, xEffect, yEffect, 0, GetID(), TRUE, pos, 0, false );
		break;
	case CFlyTextEffect::eMonsterResist:
		g_pFlyTextEffect->Create( CFlyTextEffect::eMonsterResist, xEffect, yEffect, 0, GetID(), TRUE, pos, 0, false );
		break;
	case CFlyTextEffect::eDodge:
		g_pFlyTextEffect->Create( CFlyTextEffect::eDodge, xEffect, yEffect, 0, GetID(), FALSE, pos, 0, false );
		break;
	case CFlyTextEffect::eResist:
		g_pFlyTextEffect->Create( CFlyTextEffect::eResist, xEffect, yEffect, 0, GetID(), FALSE, pos, 0, false );
		break;
	case CFlyTextEffect::eBackAttck:
		g_pFlyTextEffect->Create( CFlyTextEffect::eBackAttck, xEffect, yEffect, 0, GetID(), TRUE, pos, 0, false );
		break;
	case CFlyTextEffect::eDefence:
		g_pFlyTextEffect->Create( CFlyTextEffect::eDefence, xEffect, yEffect, 0, GetID(), TRUE, pos, 0, false );
		break;
	case CFlyTextEffect::eWard:
		g_pFlyTextEffect->Create( CFlyTextEffect::eWard, xEffect, yEffect, 0, GetID(), TRUE, pos, 0, false );
		break;
	case CFlyTextEffect::eCruelHit:
		g_pFlyTextEffect->Create( CFlyTextEffect::eCruelHit, xEffect, yEffect, 0, GetID(), TRUE, pos, 0, false );
		break;
	case CFlyTextEffect::eDeathHit:
		g_pFlyTextEffect->Create( CFlyTextEffect::eDeathHit, xEffect, yEffect, 0, GetID(), TRUE, pos, 0, false );
		break;
	default:
		break;
	}
	return TRUE;
	unguard;
}

//���˹���֡��Ҫ��������
bool CPlayer::OnHitPoint(BOOL bLastHitPoint, int nHitPointType,SAttackInfo *pAttackInfo )
{
	guardfunc;
	CPlayer* pSrcPlayer = NULL;
	ItemDefine::SItemSkill *pSkill = NULL;

	guard(test);
	bool ret = false;

	if( !pAttackInfo )
	{
		assert( false );
		m_bHitPointPlayOver = TRUE;
		m_pAttackInfo = NULL;
		return false;
	}

	pSrcPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->nSrcId );

	pSkill = GettheItemDetail().GetSkillByID(pAttackInfo->iSkill, pAttackInfo->iSkillLevel);
	unguard;

	guard(test1);
	if ( !pSrcPlayer )
	{
		m_bHitPointPlayOver = TRUE;
		m_pAttackInfo = NULL;
		return false;
	}

	if( !pSkill )
	{
		m_bHitPointPlayOver = TRUE;
		m_pAttackInfo = NULL;
		return false;
	}
	unguard;
	BOOL bCenterMeEffectCreated = FALSE;

	//��Ҫ������Ч������Ȼ������Ч�ٻص�
	//Ӧ���Ǹ��ݼ��ܵĲ�ͬ
	guard(test2);

	if(theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe() == this)
	{
		if(m_HeroKillHasChanged)
			g_pPrintTextEffect->Create(theHeroGame.GetPlayerMgr()->GetMe()->GetHeroKillTargetNum(),CPrintTextEffect::KILLTARGET);
		m_HeroKillHasChanged = false;
	}	

	SAttackInfo attackinfo = *pAttackInfo;

	for( int i = 0; i < pAttackInfo->nRecordCount; i++ )
	{
		SAttackInfoRecord* pRecord = &pAttackInfo->records[i];
		CPlayer* pDestPlayer = theHeroGame.GetPlayerMgr()->FindByID( pRecord->nTargetID );

		guard(test2.0);
		if (NULL == pDestPlayer)
		{
			pDestPlayer = theHeroGame.GetPlayerMgr()->FindByServerIDInDeath( pRecord->nTargetID );
			if( pDestPlayer == NULL )
			{
				continue;
			}
		}
		unguard;

		ShowFightInfo(pSrcPlayer,pDestPlayer,pRecord,pSkill);  //��ʾս����Ϣ

		guard(test2.2);
		if ( _HAS_FLAG( pRecord->dwState, eFIGHT_MISS ) && ( pSkill->ustCastTarget == ItemDefine::casttarget_enemylive ) )
		{
			if( pDestPlayer->IsHitPointPlayOver() && pDestPlayer->m_cFightStatus.IsCanMove() )
			{
				pDestPlayer->SwitchDodgeAnim(0);
			}

			if( pSrcPlayer->IsRole() || pSrcPlayer->MasterIsMe() )
			{
				pDestPlayer->OnShowFlyPic( CFlyTextEffect::eMiss );
			}

			if( pDestPlayer->IsRole() || pDestPlayer->MasterIsMe() )
			{
				pDestPlayer->OnShowFlyPic( CFlyTextEffect::eDodge );
			}

			if( GetWeaponSound() && pDestPlayer->GetArmourSound() )
			{
				char szBuf[MAX_PATH] = {0};
				_snprintf( szBuf, MAX_PATH-1, "data\\audio\\%s_%s_miss.wav", GetWeaponSound(), pDestPlayer->GetArmourSound() );
				GSound.PlaySound( GetFullFileName(szBuf), false, &pDestPlayer->GetPos() );
			}
			continue;
		}
		unguard;

		// 		guard(test2.3);
		// 		if( _HAS_FLAG( pRecord->dwState, eFIGHT_WARD ) && ( pSkill->ustCastTarget == ItemDefine::casttarget_enemylive ) )
		// 		{
		// 			if( pDestPlayer->IsRole() )
		// 			{
		// 				if( pDestPlayer->IsHitPointPlayOver() && pDestPlayer->m_cFightStatus.IsCanMove() )
		// 				{
		// 					pDestPlayer->SwitchDefendAnim(0);
		// 				}
		// 			}
		// 
		// 			if( pSrcPlayer->IsRole() || pSrcPlayer->MasterIsMe() )
		// 			{
		// 				pDestPlayer->OnShowFlyPic( CFlyTextEffect::eMonsterWard );
		// 			}
		// 
		// 			if( pDestPlayer->IsRole() || pDestPlayer->MasterIsMe() )
		// 			{
		// 				pDestPlayer->OnShowFlyPic( CFlyTextEffect::eWard );
		// 			}
		// 		}
		// 		unguard;

		// 		guard(test2.4);
		// 		if ( _HAS_FLAG( pRecord->dwState, eFIGHT_RESIST ) && ( pSkill->ustCastTarget == ItemDefine::casttarget_enemylive ) )
		// 		{
		// 			if( pSrcPlayer->IsRole() || pSrcPlayer->MasterIsMe() )
		// 			{
		// 				pDestPlayer->OnShowFlyPic( CFlyTextEffect::eMonsterResist );
		// 			}
		// 
		// 			if( pDestPlayer->IsRole() || pDestPlayer->MasterIsMe() )
		// 			{
		// 				pDestPlayer->OnShowFlyPic( CFlyTextEffect::eResist );
		// 			}
		// 		}
		// 		unguard;

		// ��Ѫ
		if ( _HAS_FLAG( pRecord->dwState, eFIGHT_SUCKHP ) /*&& ( pSkill->ustCastTarget == ItemDefine::casttarget_enemylive )*/ )
		{
			// ��Ѫ��Ч
			if( CanRenderPlayerEffect(pSrcPlayer->GetID()) )
			{
				PlayEffect( "ArmourSkill\\XiXue\\XiXue.effect", pSrcPlayer, PlayerInfoMgr::Instance()->GetScaleForPlayer(pSrcPlayer) );
			}
		}

		// ����
		if ( _HAS_FLAG( pRecord->dwState, eFIGHT_DAMREFLECT ) )
		{
			// ������Ч
			if( CanRenderPlayerEffect(pSrcPlayer->GetID()) )
			{
				PlayEffect( "ArmourSkill\\FanTan\\FanTan.effect", pSrcPlayer, PlayerInfoMgr::Instance()->GetScaleForPlayer(pSrcPlayer) );
			}
		}

		//�����ֿ�
		if(_HAS_FLAG(pRecord->dwState,eFIGHT_DAOXINGRESIST))
		{
			if (GameSetting::Instance()->GetLevel( GameSetting::eGSC_FightFlyText ))
			{
				OnShowFlyPic(CFlyTextEffect::eResist);
			}
		}

		//����ѹ��
		if(_HAS_FLAG(pRecord->dwState,eFIGHT_DAOXINGSTIFLE))
		{
			if (GameSetting::Instance()->GetLevel( GameSetting::eGSC_FightFlyText ))
			{
				OnShowFlyPic(CFlyTextEffect::eWard);
			}
		}

		guard(test2.0.1);

		if( pAttackInfo->bPlayHurtAnim && CanRenderPlayerEffect(pDestPlayer->GetID()) )
		{
			const char *pEffectPath = NULL;
			if( m_ucSex == Sex_Female )
				pEffectPath = pSkill->GetTargetEffectName2();
			else
				pEffectPath = pSkill->GetTargetEffectName();

			//����Ŀ����Ч
			if( stricmp( pEffectPath, "NULL" ) != 0 )
			{
				PlayEffect( (char*)pEffectPath, pDestPlayer, PlayerInfoMgr::Instance()->GetScaleForPlayer(pDestPlayer) );
			}
		}
		unguard;

		guard(test2.3);
		//if(theHeroGame.GetPlayerMgr()->GetMe()&&pDestPlayer != theHeroGame.GetPlayerMgr()->GetMe()) //lyh++ ���ǵ�Ѫ����Ϣ������Ϣ��������ʱ���Ѿ������ˣ�����Ͳ���Ҫ2�μ���
		//pDestPlayer->SetHPInfo_HPChange( -(pRecord->iTagNum+pRecord->stTagBackAttackNum) );
		pDestPlayer->SetHPInfo_HP(pRecord->iTagHp);//by vvx 2013.8.3
		// ���ӷ��˺���Ѫ���ܣ�����Ҫ�蹥����Ѫ��
		if( pRecord->iSrcHpNum != 0 )
		{
			pSrcPlayer->SetHPInfo_HPChange( -pRecord->iSrcHpNum );
		}
		if( pRecord->iSrcMpNum != 0 )
		{
			pSrcPlayer->SetMPInfo_MPChange( -pRecord->iSrcMpNum );
		}

		if(pRecord->nShieldHp > 0)
		{
			if (GameSetting::Instance()->GetLevel( GameSetting::eGSC_FightFlyText ))
			{
				OnShowFlyPic(CFlyTextEffect::eWard);
			}
		}

		if( _HAS_FLAG( pRecord->dwState, eFIGHT_BEKILLED ) )
		{
			//������Զ�����ܽ�����??
			if(pDestPlayer->GetID() == s_CUI_ID_FRAME_Target.GetPlayerID())
			{
				theHeroGame.GetPlayerMgr()->SetLockNpc(-1);
				s_CUI_ID_FRAME_Target.SetPlayer(-1);

				// ���ǹ���Ŀ���������������CAS_NOT_ATTACK״̬
				if( m_bRole )
					g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
			}

			{
				pDestPlayer->OnClearAllBodyStatusByDead();
				//pDestPlayer->OnClearAllBodyStatus();
				if( !pDestPlayer->IsDead() ) //�������Լ����߼�
					pDestPlayer->AddRef();
				pDestPlayer->SetCharDead( TRUE );
				if( theHeroGame.GetPlayerMgr()->GetMe() == pDestPlayer )
				{
					//s_CUI_ID_FRAME_NpcChatDialogBox.SetNpc(-1);
					s_CUI_NpcTaskDialogBox.SetNpc(-1);
					theHeroGame.GetPlayerMgr()->SetLockNpc( -1 );
					s_CUI_ID_FRAME_MessageBox.closeAll( false );
					s_CUI_ID_FRAME_PrivateShop.SetVisable(false);
					s_CUI_InputBox.ID_BUTTON_CANCELOnButtonClick(NULL);
					s_CUI_ID_FRAME_Bargaining.SetVisable(false);
				}
				else
				{
					if( this != pDestPlayer )
					{
						pDestPlayer->UpdateBaseData(HQ_TimeGetTime());
					}
				}
				pDestPlayer->SetHPInfo_HP(0);
				pDestPlayer->SwitchDieAnim();
				if(pDestPlayer->IsMonster()) //�Ƿ����
				{
					int nMaxHp = pDestPlayer->GetHpInfo_HPMax();
					if(pRecord->iTagNum >= nMaxHp)
					{
						float fx = 0,fy = 0,fz = 0;
						pDestPlayer->GetPos(&fx,&fy,&fz);
						D3DXVECTOR3 vDir = D3DXVECTOR3(fx - m_x ,fy - m_y, fz - m_z);
						D3DXVec3Normalize(&vDir,&vDir);
						pDestPlayer->SetActionState(eAction_HitBack,vDir);
					}
				}
				//���������ȴ���������ͷ�
				//pDestPlayer->AddRef();
			}

			// �ж��Ƿ���ҹ�����ң�������ʾ��ɱ��Ϣ������������Լ���ɱ��
			if( pDestPlayer->IsPlayer() && theHeroGame.GetPlayerMgr()->GetMe() && pDestPlayer->GetID() != theHeroGame.GetPlayerMgr()->GetMyID() )
			{
				if( IsPlayer() || (IsMonster() && GetMasterID() > -1) )
				{
					char *szDestName = pDestPlayer->GetName();
					char *szMe = NULL;
					CPlayer* pMaster = NULL;
					if( IsPlayer() )
						szMe = GetName();
					else
					{
						pMaster = theHeroGame.GetPlayerMgr()->FindByID(GetMasterID());
						if( pMaster )
							szMe = pMaster->GetName();
					}

					if( szDestName && szDestName[0] != '\0'&& szMe && szMe[0] != '\0')
					{
						char szResult[MAX_PATH] = {0};;
						if( IsRole() || (pMaster && pMaster == theHeroGame.GetPlayerMgr()->GetMe()) )
						{
							MeSprintf_s(szResult,sizeof(szResult)/sizeof(char) - 1 ,theXmlString.GetString( eText_PKResult_YouKillPlayer ), szDestName);
						}
						else
						{
							MeSprintf_s(szResult,sizeof(szResult)/sizeof(char) - 1, theXmlString.GetString( eText_PKResult ), szMe, szDestName);
						}
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Dual, szResult );
					}
				}
			}
		}
		// �����߱�����ɱ��
		if( _HAS_FLAG( pRecord->dwState, eFIGHT_SELFBEKILLED ) )
		{
			if(pSrcPlayer->GetID() == s_CUI_ID_FRAME_Target.GetPlayerID())
			{
				theHeroGame.GetPlayerMgr()->SetLockNpc(-1);
				s_CUI_ID_FRAME_Target.SetPlayer(-1);
				// ���ǹ���Ŀ���������������CAS_NOT_ATTACK״̬
				if( m_bRole )
					g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
			}
			pSrcPlayer->OnClearAllBodyStatusByDead();
			//pSrcPlayer->OnClearAllBodyStatus();
			//lyhȥ������
			if( !pSrcPlayer->IsDead() )
				pSrcPlayer->AddRef();
			pSrcPlayer->SetCharDead( TRUE );
			if( theHeroGame.GetPlayerMgr()->GetMe() == pSrcPlayer )
			{
				//s_CUI_ID_FRAME_NpcChatDialogBox.SetNpc(-1);
				s_CUI_NpcTaskDialogBox.SetNpc(-1);
				theHeroGame.GetPlayerMgr()->SetLockNpc( -1 );
				s_CUI_ID_FRAME_MessageBox.closeAll( false );
				s_CUI_ID_FRAME_PrivateShop.SetVisable(false);
				s_CUI_InputBox.ID_BUTTON_CANCELOnButtonClick(NULL);
				s_CUI_ID_FRAME_Bargaining.SetVisable(false);
			}
			else
			{
				if( this != pSrcPlayer )
				{
					pSrcPlayer->UpdateBaseData(HQ_TimeGetTime());
				}
			}
			pSrcPlayer->SetHPInfo_HP(0);
			pSrcPlayer->SwitchDieAnim();
			//���������ȴ���������ͷ�
			//pSrcPlayer->AddRef();

			// �ж��Ƿ���ҹ�����ң�������ʾ��ɱ��Ϣ������������Լ���ɱ��
			if( pSrcPlayer->IsPlayer() && theHeroGame.GetPlayerMgr()->GetMe() && pSrcPlayer->GetID() != theHeroGame.GetPlayerMgr()->GetMyID() )
			{
				if( pDestPlayer->IsPlayer() || (pDestPlayer->IsMonster() && pDestPlayer->GetMasterID() > -1) )
				{
					char *szDeadName = pSrcPlayer->GetName();
					char *szAttackName = NULL;
					CPlayer* pMaster = NULL;
					if( pDestPlayer->IsPlayer() )
						szAttackName = pDestPlayer->GetName();
					else
					{
						pMaster = theHeroGame.GetPlayerMgr()->FindByID(pDestPlayer->GetMasterID());
						if( pMaster )
							szAttackName = pMaster->GetName();
					}

					if( szDeadName && szDeadName[0] != '\0'&& szAttackName && szAttackName[0] != '\0')
					{
						char szResult[MAX_PATH] = {0};;
						if( pDestPlayer->IsRole() || (pMaster && pMaster == theHeroGame.GetPlayerMgr()->GetMe()) )
						{
							MeSprintf_s(szResult,sizeof(szResult)/sizeof(char) - 1, theXmlString.GetString( eText_PKResult_YouKillPlayer ), szDeadName);
						}
						else
						{
							MeSprintf_s(szResult,sizeof(szResult)/sizeof(char) - 1 ,theXmlString.GetString( eText_PKResult ), szAttackName, szDeadName);
						}
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Dual, szResult );
					}
				}
			}
		}

		if( pSrcPlayer->IsRole() || pDestPlayer->IsRole() || pSrcPlayer->MasterIsMe() || pDestPlayer->MasterIsMe() ||
			pRecord->iBalanceType == ItemDefine::balancetype_restorehpmp )
		{
			int nAddNum = 0;
			if( _HAS_FLAG( pRecord->dwState, eFIGHT_BACKSTRIKE ) )
			{
				nAddNum = pRecord->stTagBackAttackNum;
			}

			if( _HAS_FLAG( pRecord->dwState, eFIGHT_CRITICALHIT ) )
			{
				if( pSrcPlayer->IsRole() )
				{
					g_CameraStuntManager.StartRandShake( gCfg.m_fCriticalAttackMaxShakeRange, gCfg.m_fCriticalAttackMinShakeRange, gCfg.m_dwCriticalAttackShakeKeepTime, gCfg.m_nCriticalAttackCameraShakeType );
				}

				if (!IsNormalAttack(pAttackInfo->iSkill) && pRecord->iBalanceType != ItemDefine::balancetype_restorehpmp)
					pRecord->iBalanceType = ItemDefine::balancetype_damagemagicdefend;
				if (GameSetting::Instance()->GetLevel( GameSetting::eGSC_FightFlyText ))
				{
					CPlayer::OnShowFlyText( pDestPlayer, pSrcPlayer, pRecord->iBalanceType, pRecord->iTagNum, pAttackInfo->iSrcNum, nAddNum, true );
				}
			}
			else
			{
				if (!IsNormalAttack(pAttackInfo->iSkill) && pRecord->iBalanceType != ItemDefine::balancetype_restorehpmp)
					pRecord->iBalanceType = ItemDefine::balancetype_damagemagicdefend;

				if(pRecord->iBalanceType != ItemDefine::balancetype_restorehpmp)
				{
					if (GameSetting::Instance()->GetLevel( GameSetting::eGSC_FightFlyText ))
					{
						CPlayer::OnShowFlyText(pDestPlayer, pSrcPlayer, pRecord->iBalanceType, pRecord->iTagNum, pAttackInfo->iSrcNum, nAddNum, false);
					}
				}
				else
				{
					if(pRecord->iTagNum != 0)
					{
						if (GameSetting::Instance()->GetLevel( GameSetting::eGSC_FightFlyText ))
						{
							CPlayer::OnShowFlyText( pDestPlayer, pSrcPlayer, pRecord->iBalanceType, pRecord->iTagNum, pAttackInfo->iSrcNum, 0, false );
						}
					}
					else
					{
						if (GameSetting::Instance()->GetLevel( GameSetting::eGSC_FightFlyText ))
						{
							CPlayer::OnShowFlyText( pDestPlayer, pSrcPlayer, pRecord->iBalanceType, pRecord->iTagMpNum, pAttackInfo->iSrcMpNum, -1, false );
						}
					}
				}
			}

		}

		if( !pSkill->bEmissionSkill )
		{
			PlayCreatureSound( CCreatureSound::CreatureSound_Attack );

			char szBuf[MAX_PATH] = {0};
			if( GetWeaponSound() && pDestPlayer->GetArmourSound() )
			{
				if( pRecord->iTagNum > 0 )
				{
					_snprintf( szBuf, MAX_PATH-1, "data\\audio\\%s_%s_hit.wav", GetWeaponSound(), pDestPlayer->GetArmourSound() );
					GSound.PlaySound( GetFullFileName(szBuf),false,&GetPos() );
				}
			}
		}
		unguard;

		guard(test2.4);
		if( pDestPlayer->IsHitPointPlayOver() && pRecord->iTagNum > 0 ) // ���˺�ֵ
		{
			if( !_HAS_FLAG( pRecord->dwState, eFIGHT_BEKILLED ) && ( pSkill->ustCastTarget == ItemDefine::casttarget_enemylive ) 
				/*&&!_HAS_FLAG( pRecord->dwState, eFIGHT_WARD )*/)
			{
				//ShowDamageNumber(pDestPlayer, pRecord);  //lyh�޸��˺�����Ʈ���ε�bug

				if( _HAS_FLAG( pRecord->dwState, eFIGHT_CRITICALHIT ) && pDestPlayer->m_cFightStatus.IsCanMove() )
				{
					// ��Ҫ���ܻ�����
					if( pAttackInfo->bPlayHurtAnim&&!IsCanOverIntonation() )
					{
						pDestPlayer->PlayCreatureSound( CCreatureSound::CreatureSound_BeHit );
						pDestPlayer->SwitchHurtAnim();
					}
				}
				else
				{
					if( pDestPlayer->GetAnim() && pDestPlayer->GetAnim()->GetMexCfg() )
					{
						int nRadius = pDestPlayer->GetAnim()->GetMexCfg()->m_BodyRadius.m_npRadius.GetNumber();
						nRadius = nRadius*pDestPlayer->GetBodySize();
						if( nRadius > 0 && rand()%nRadius < 30 && pDestPlayer->m_cFightStatus.IsCanMove() )
						{
							// ��Ҫ���ܻ�����
							if( pAttackInfo->bPlayHurtAnim&&!IsCanOverIntonation() )
							{
								pDestPlayer->PlayCreatureSound( CCreatureSound::CreatureSound_BeHit );
								pDestPlayer->SwitchHurtAnim();
							}
						}
					}
				}
			}
		}
		unguard;
	}
	unguard;

	guard(test3);
	theAttackInfoMan.DeleteAttackInfo( pAttackInfo );
	unguard;

	m_bHitPointPlayOver = TRUE;
	m_pAttackInfo = NULL;

	return true;
	unguard;
}

void CPlayer::ShowDamageNumber(CPlayer *destPlayer, const SAttackInfoRecord *record)
{
	// �����Ƿ񱩻�
	bool isSkillCritical = false;
	if (_HAS_FLAG(record->dwState, eFIGHT_CRITICALHIT))
		isSkillCritical = true;

	D3DXVECTOR3 pos = GetPos();
	pos.z += g_fTheRoleBBoxHeight;

	int x = 0, y = 0;
	World2Screen(pos, x, y);
	if (destPlayer->IsPlayer())
	{
		if (isSkillCritical)
			g_pFlyTextEffect->Create(CFlyTextEffect::eNumberAttackWhite, x, y, record->iTagNum, destPlayer->GetID(), TRUE, pos, 0,  GlobalTexture::eCruelHit);
		else
			g_pFlyTextEffect->Create(CFlyTextEffect::eNumberAttackWhite, x, y, record->iTagNum, destPlayer->GetID(), TRUE, pos, 0, GlobalTexture::eNumber3);
	}
	else
	{
		if (isSkillCritical)
			g_pFlyTextEffect->Create(CFlyTextEffect::eNumberAttackWhite, x, y, record->iTagNum, destPlayer->GetID(), TRUE, pos, 0, GlobalTexture::eCruelHit);
		else
			g_pFlyTextEffect->Create(CFlyTextEffect::eNumberAttackWhite, x, y, record->iTagNum, destPlayer->GetID(), TRUE, pos, 0, GlobalTexture::eNumber3);
	}
}

// �ж��Ƿ�������
bool CPlayer::IsHaveWeapon(int iWeaponType/* = -1*/)
{
	guardfunc;
	{
		if ((m_equips[eKeyAll_LHandItem].iModelID != InvalidLogicNumber) || 
			(m_equips[eKeyAll_RHandItem].iModelID != InvalidLogicNumber))
		{
			if( iWeaponType == -1 )  // �������κζ���
				return true;

			// �����ж�����     added by zhuomeng.hu		[10/11/2010]
			CPlayer_SEquipment* pRightHandEquip = NULL;

			pRightHandEquip = &m_equips[eKeyAll_RHandItem];

			if( pRightHandEquip && pRightHandEquip->item.itembaseinfo.ustItemID != InvalidLogicNumber )
			{
				ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pRightHandEquip->item.itembaseinfo.ustItemID );
				if( pItem == NULL || pItem->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
					return false;

				ItemDefine::SItemWeapon *pWeapon = (ItemDefine::SItemWeapon *)pItem;
				if( pWeapon->stWeaponType == iWeaponType )
					return true;
			}
		}

		return false;
	}
	unguard;
}
//----
//������ҵ�����ȡ�ö�Ӧ�����ı��
//----
int		CPlayer::GetPlayerActionID(int ActionID, int iFightType)
{
	guardfunc;
	int id = 0;
	int fight_type = 0;
	int sex_type = 0;
	int profession_type = 0;
	int weapon_type = 0;
	int action_id = 0;

	int iProfession = 0;	

	switch (ActionID)
	{
	case MoreAction::Action_idle://(����)   
		return MoreActionClient::Idle;
		break;
	case MoreAction::Action_specialidle:
		return MoreActionClient::SpecialIdle;
		break;
	case MoreAction::Action_run://(����)     
		return MoreActionClient::Run;
		break;
	case MoreAction::Action_walk://(����)
		return MoreActionClient::Walk;
		break;
	case MoreAction::Action_dead://(ԭ�ص���)
	case MoreAction::Action_dead1://(���w�˄�)  
		return MoreActionClient::Dead;
		break;
	case MoreAction::Action_Attack1://(��������1��1)    
		{
			return MoreActionClient::Attack1;				
		}
		break;
	case MoreAction::Action_Attack2://(��������1��2)
		{
			return MoreActionClient::Attack2;
		}			
		break;

		//����
	case MoreAction::Action_single_attackr1://������ͨ����
		return MoreActionClient::single_attackr1;
		break;
	case MoreAction::Action_single_attackl1://������ͨ����
		return MoreActionClient::single_attackl1;
		break;
	case MoreAction::Action_single_attackr2://������ͨ����
		return MoreActionClient::single_attackr2;
		break;
	case MoreAction::Action_single_attackl2://������ͨ����
		return MoreActionClient::single_attackl2;
		break;
	case MoreAction::Action_single_attack_idle:
		return MoreActionClient::single_attack_idle;
		break;
		//����
	case MoreAction::Action_single_double_draw:		//˫�ְγ�����
		return MoreActionClient::single_double_draw;
		break;
	case MoreAction::Action_single_double_scabbard:			//˫����������
		return MoreActionClient::single_double_scabbard;
		break;
	case MoreAction::Action_single_draw:				//������������
		return MoreActionClient::single_draw;
		break;
	case MoreAction::Action_single_scabbard:			//���ְγ�����
		return MoreActionClient::single_scabbard;
		break;
	case MoreAction::Action_double_attack1:		//����
		return MoreActionClient::double_attack1;
		break;
	case MoreAction::Action_double_attack2:		//����2
		return MoreActionClient::double_attack2;
		break;
	case MoreAction::Action_double_draw:		//˫�ְ�����
		return MoreActionClient::double_draw;
		break;
	case MoreAction::Action_double_scabbard:		//˫��������
		return MoreActionClient::double_scabbard;
		break;
	case MoreAction::Action_double_attack_idle:
		return MoreActionClient::double_attack_idle;
		break;
	case MoreAction::Action_attack_idle:
		return MoreActionClient::Attack_idle;
		break;
	case MoreAction::Action_single_run_attackr1:
		return MoreActionClient::single_run_attackr1;
		break;
	case MoreAction::Action_single_run_attackl1:
		return MoreActionClient::single_run_attackl1;
		break;
	case MoreActionClient::single_walk_attackr1:
		return MoreActionClient::single_walk_attackr1;
		break;
	case MoreActionClient::single_walk_attackl1:
		return MoreActionClient::single_walk_attackl1;
		break;
	case MoreAction::Action_jump:
		return MoreActionClient::jump;
		break;
	case MoreAction::Action_single_run_scabbard:
		return MoreActionClient::single_run_scabbard;
		break;
	case MoreAction::Action_single_run_draw:
		return MoreActionClient::single_run_draw;
		break;
	case MoreAction::Action_single_flag_run:
		return MoreActionClient::single_flag_run;
		break;
	case MoreAction::Action_single_flag_idle:
		return MoreActionClient::single_flag_idle;
		break;
	default:
		return MoreActionClient::Idle;
		break;
	}
	//
	return id;
	unguard;
}

void	CPlayer::ClearEffStatus()
{
	guardfunc;
	unguard;
}

void CPlayer::OnBuffsUpdate( MsgBuffsUpdate* pBodyStatus )
{ // ���ý�ɫ���ϵ�״̬
	guardfunc

		// �������buff
		m_cFightStatus.ClearAllBuff();

	// log��¼�����Buff
	m_cFightStatus.LogAndClearBufferClearIdArray();

	for( int i=0; i < pBodyStatus->count; ++i )
	{
		SUpdateBuffInfo* pUpdateBuffInfo = &pBodyStatus->data[i];

		// �ͻ��˲���Ҫ֪��.״̬���ͷ��ߣ���������0�Ϳ�����
		m_cFightStatus.AddBuff( pUpdateBuffInfo->index, pUpdateBuffInfo->bStop,  pUpdateBuffInfo->stStatusID,pUpdateBuffInfo->cStatusLevel, 0, HQ_TimeGetTime(), pUpdateBuffInfo->bIsLast, pUpdateBuffInfo->dwDurationTime,0,0,0 );
	}

	// ����һ��״̬
	m_cFightStatus.UpdateEffect();

	// ͼ�α��ֵĸ���
	OnBuffsUpdateOrChangedRender();
	unguard;
}

void CPlayer::OnBuffsChanged( MsgBuffsChanged* pMsgBuffsChanged)
{ // ���npc���ϵ�ս��״̬
	guardfunc

		if ( pMsgBuffsChanged->count > BodyStatusType_Max)
		{ pMsgBuffsChanged->count = BodyStatusType_Max; }

		bool isHide = true;

		for( int i=0; i<pMsgBuffsChanged->count; ++i )
		{
			SUpdateBuffInfo* pUpdateBuffInfo = &pMsgBuffsChanged->data[i];

			if ( pUpdateBuffInfo->stStatusID == InvalidLogicNumber )
			{ // ��ʾ���index�Ѿ�û��buff�� ԭ�����ھ�ɾ�� û�˾Ͳ��ò���
				SCharBuff* pCharBuff = m_cFightStatus.GetBuff( pUpdateBuffInfo->index );
				if ( pCharBuff )
				{ 

					if(m_cFightStatus.IsHide())  //������ -�� ������� isShowEffect ���
					{
						isHide = false;	  
					}

					/*ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel );
					if ( pItemStatus )
					{ 
					if(pItemStatus->nChangeMonsterID > 0)
					{
					int i = 0;
					}

					}*/

					m_cFightStatus.ClearBuff( pUpdateBuffInfo->index ); 
				}
			}
			else
			{
				ClearStatusEffect(pUpdateBuffInfo->stStatusID,pUpdateBuffInfo->cStatusLevel);

				// ��ʾ���index��Ҫ���� ����ԭ����û�и��Ǿ���
				m_cFightStatus.AddBuff( pUpdateBuffInfo->index, pUpdateBuffInfo->bStop,  pUpdateBuffInfo->stStatusID,pUpdateBuffInfo->cStatusLevel, 0, HQ_TimeGetTime(), pUpdateBuffInfo->bIsLast, pUpdateBuffInfo->dwDurationTime,0,0,0 );
			}
		}

		// ����һ��״̬
		m_cFightStatus.UpdateEffect();

		// ͼ�α��ֵĸ���
		OnBuffsUpdateOrChangedRender();
		unguard
}

void CPlayer::OnBuffsUpdateOrChangedRender()
{
	// ������Ч һ��Ҫ������״̬֮ǰ
	ResetStatusEffectsKeepFlag();

	SCharBuff* pStatus = NULL;

	D3DXVECTOR3 vStatusColor = D3DXVECTOR3( 0, 0, 0 );
	int nStatusColorCount = 0; // ״̬��ɫ��
	int nMorphMonsterID = -1;  // ���ε�ģ��Id
	bool bPlayStatusAnim = false;   // �Ƿ��в�״̬����
	for( int i=0; i<m_cFightStatus.GetBufferStatusCount(); ++i )
	{
		pStatus = m_cFightStatus.GetBuff(i);
		if ( NULL == pStatus )
		{ continue; }

		ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatus( pStatus->StatusID, pStatus->iLevel );
		if ( NULL == pItemStatus )
		{ continue; }

				// ״̬ģ�� ToModify ��ʵ��Ҫ�ж����µ�buff,��ɫӦ�ø����µ�buffģ�� 
		if( pItemStatus->nChangeMonsterID >=0 )
		{ nMorphMonsterID = pItemStatus->nChangeMonsterID; }

		if ( IsDead() )
		{ continue; } 

		// buff��ɫ ToModify ��ʵ��Ҫ�ж����µ�buff,��ɫӦ�ø����µ�buff��ɫ 
		if( pItemStatus->bUseStateColour )
		{
			vStatusColor.x = pItemStatus->fStateColourR;
			vStatusColor.y = pItemStatus->fStateColourG;
			vStatusColor.z = pItemStatus->fStateColourB;
			++nStatusColorCount;
		}



		// ״̬��Ч
		if( stricmp( pItemStatus->GetStatusEffectName() , "NULL" ) != 0 )
		{
			// �Ƿ���Ҫ��Ⱦ��Ч
			if( CanRenderPlayerEffect(GetID()) )
			{
				// �Ƿ���Ч�Ѿ���Keepִ��
				if ( FindStatusEffect( pStatus->StatusID, pStatus->iLevel ) )
				{ continue; }

				// ����Buff��Ч
				pStatus->nEffectID = PlayEffect( (char*)pItemStatus->GetStatusEffectName(), this,
					PlayerInfoMgr::Instance()->GetScaleForPlayer(this, true), 0x00ffffff );
				AddStatusEffect( pStatus->StatusID, pStatus->iLevel, pStatus->nEffectID );
			}
		}

		// ״̬��������Ϊnone���򲥶���
		if( pItemStatus->GetAnimationName() && stricmp(pItemStatus->GetAnimationName(),"none") )
		{
			if( m_pAnim /*&& m_pAnim->IsUpperBodyAndLowerBodyMode()*/ )
			{
				int nAnimType = MoreAction::FindIdByName( pItemStatus->GetAnimationName() );
				if(m_pAnim->IsUpperBodyAndLowerBodyMode())
				{
					int nLowerAnimType = m_pAnim->GetCurLowerAnimType();

					if( nLowerAnimType != nAnimType )
					{
						// �Ȳ�HitPointer
						if( !m_bHitPointPlayOver )
						{
							// ������ʾ�������˺�����Ч
							OnHitPoint( TRUE, GlobalControl::eNormal, GetAttackInfo() );
						}

						m_pAnim->PlayLowerAnim(	nAnimType,
							MexAnimCtrl::eNormalPlay,
							0,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime*2,
							nAnimType,
							MexAnimCtrl::eNormalPlay );
					}
				}
				else
				{
					int nCurAnimType = m_pAnim->GetCurAnimType();
					if(nCurAnimType != nAnimType)
					{
						m_pAnim->PlayAnim2( nAnimType,
							MexAnimCtrl::eNormalPlay,
							0,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							nAnimType,
							MexAnimCtrl::eDefaultBlendingTime );
					}
				}
				m_iBuffStatusAnimType = nAnimType;
				bPlayStatusAnim = true;
			}
		}
	}

	// �ж��Ƿ��µ�״̬�ж���
	if( !bPlayStatusAnim && m_iBuffStatusAnimType != -1 )
	{ // ���û��״̬���� ����ǰ�ڲ�״̬���� ��idle����
		//         if( m_pAnim && m_iBuffStatusAnimType == m_pAnim->GetCurLowerAnimType() )
		//         { SwitchIdleAnim(); }

		if( m_pAnim)
		{
			if(m_pAnim->IsUpperBodyAndLowerBodyMode())
			{
				if(m_iBuffStatusAnimType == m_pAnim->GetCurLowerAnimType())
					SwitchIdleAnim();
			}
			else
			{
				if(m_iBuffStatusAnimType == m_pAnim->GetCurAnimType())
					SwitchIdleAnim();
			}

		}
		m_iBuffStatusAnimType = -1;
	}

	// �Ƿ��б���ģ��buff
	if( nMorphMonsterID < 0 )
	{ // ��
		if( m_bMorphing && !IsOpenPrivateShop() && !IsYabiaoState() )//lyh++ ��buff��Ҫ���µ�ʱ������Լ���Ѻ�ڵ�ģ�ͣ���buff���˻����ڳ�
		{ DisMorph(); }                                              //�����ڱ���buff���˵������ ������⡣�д�����
	}
	else
	{
		// �б���ģ��
		if( !m_bHitPointPlayOver )
		{ OnHitPoint( TRUE, GlobalControl::eNormal, GetAttackInfo() ); } // ������ʾ�������˺�����Ч

		if( m_bMorphing )
		{ // �Ѿ������� 
			if( m_nMorphMonsterID != nMorphMonsterID )
			{
				MorphMonster( nMorphMonsterID );
			}
		}
		else
		{
			MorphMonster( nMorphMonsterID );
		}
	}

	// ���������Buff��Ч
	ClearUnkeepStatusEffects();

	// �õ�������ɫ��ֵ
	if( m_pCharEffectContainer )
	{ m_vFinStatusColor = vStatusColor; }
}

void	CPlayer::SetFinStatusColor( D3DXVECTOR3 vColor )
{
	guardfunc;
	m_vFinStatusColor = vColor;
	unguard;
}

void CPlayer::OnClearAllBodyStatusByDead()
{
	guardfunc;
	for (int i=0; i<BodyStatusType_Max; i++)
	{
		SCharBuff* pStatus;
		pStatus = m_cFightStatus.GetBuff(i);
		if ( pStatus )
		{
			if( pStatus->nEffectID < 0 )
				continue;

			ItemDefine::SItemStatus* pNewStatusConfig = (ItemDefine::SItemStatus *)GettheItemDetail().GetStatus( pStatus->StatusID, pStatus->iLevel );
			if(!pNewStatusConfig)
				continue;
			if(!pNewStatusConfig->bIsClearByDead)
				continue;

			IEffect* pEffect = GetEffectMgr()->GetEffect( pStatus->nEffectID );
			if( pEffect )
			{
				pEffect->SetDead();
				m_cFightStatus.ClearBuff(i);
			}
			pEffect = NULL;
			pStatus->nEffectID = -1;
		}
	}
	unguard;
}
//  ���npc���ϵ�����ս��״̬
void CPlayer::OnClearAllBodyStatus()
{
	guardfunc;
	for (int i=0; i<BodyStatusType_Max; i++)
	{
		SCharBuff* pStatus;
		pStatus = m_cFightStatus.GetBuff(i);
		if ( pStatus )
		{
			if( pStatus->nEffectID < 0 )
				continue;

			IEffect* pEffect = GetEffectMgr()->GetEffect( pStatus->nEffectID );
			if( pEffect )
			{
				pEffect->SetDead();
				m_cFightStatus.ClearBuff(i);
			}
			pEffect = NULL;
			pStatus->nEffectID = -1;
		}
	}
	unguard;
}

void CPlayer::SetVisual( SCharVisual &visual,bool bNeedLoadModel )
{
	guardfunc;
	unguard;
}

bool CPlayer::IsInOneTeam()
{
	guardfunc;
	return  m_cTeamPosition != ETP_None ;
	unguard;
}

bool CPlayer::IsTeamHeader()
{
	guardfunc;
	return m_cTeamPosition == ETP_Leader;
	unguard;
}

bool CPlayer::IsDeadOver()
{
	guardfunc;
	return m_bDeadOver;
	unguard;
}
bool CPlayer::IsDead()
{
	guardfunc;
	return m_bDead;
	unguard;
}
void CPlayer::ClearDeath()
{ 
	guardfunc;
	m_bDeadOver = false; 
	m_bDead = false; 
	m_bWillDie = false;
	unguard;
}
bool CPlayer::Relive(short shToHell)
{
	guardfunc;
	if( this == theHeroGame.GetPlayerMgr()->GetMe() )// ���������������ã�����������ʧ����������������״̬�����Ǹ����ò����1�����ﲻ����ʧ [11/16/2010 zhangjiayi]
		ClearDeath();
	//�л���idle״̬
	if( m_bRole && GetName() )
	{
		char str[MAX_PATH] = {0};
		MeSprintf_s(str,sizeof(str)/sizeof(char) - 1,"%s ����˳�ս��\n",GetName());
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, string(str));
	}

	if( m_bRole )
	{
		//comment by yd NEXT-121
		//         if( shToHell )
		//         {
		//             SwitchActionStatus(CPlayerStatus::esk_Idle, 3000, CPlayerStatus::esk_Idle, FALSE);
		//             ClearFightFlag(eFighting, FALSE);
		//             // ��������õȴ�������ȥ�������޷��ж�
		//             thePlayerRole.SetIsReliveAndWaitingToHell(TRUE);
		//         }
		//         else
		{
			// ����Ҹ����վ����
			SwitchActionStatus(CPlayerStatus::esk_Revive, 3000, CPlayerStatus::esk_Idle, TRUE);
			ClearFightFlag(eFighting,FALSE);
			if( IsPlayer() )
				SetFightPose(FALSE);
			theHeroGame.GetPlayerMgr()->SetReLivedByPlayer(true);
		}
	}
	else
	{
		if( shToHell )
		{
			SwitchActionStatus(CPlayerStatus::esk_Revive, 3000, CPlayerStatus::esk_Idle, FALSE);
			ClearFightFlag(eFighting, FALSE);
			ClearDeath(); //lyh��Ҹ���
		}
		else
		{
			// ����Ҹ����վ����
			ClearDeath();
			SwitchActionStatus(CPlayerStatus::esk_Revive, 3000, CPlayerStatus::esk_Idle, TRUE);
			ClearFightFlag(eFighting,FALSE);
			if(IsPlayer())
				SetFightPose(FALSE);			
			theHeroGame.GetPlayerMgr()->SetReLivedByPlayer(true);
		}
	}
	SetIntonating(FALSE);

	//
	if( !m_pCharEffectContainer )
	{
		int nIndex = GetEffectMgr()->RegisterCharEffectContainer();
		if( nIndex >= 0 )
		{
			SetCharEffectContainer( GetEffectMgr()->GetCharEffectContainer( nIndex ) );
		}
	} 

	if(!gCfg.m_strReliveEffect.empty())
	{
		PlayEffect((char*) gCfg.m_strReliveEffect.c_str(), this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this) );
	}

	if( this == theHeroGame.GetPlayerMgr()->GetMe() && !theHeroGame.GetPlayerMgr()->GetMe()->IsDead())
		s_CUI_ID_FRAME_ESCDLG.SetVisable(false);

	if( m_bRole )
		g_ActionManager.Clear();

	return true;
	unguard;
}
//----
//	���������͹����Ĺ���ʧ�ܵ���Ϣ����
//----
bool CPlayer::ServerAttackFailProc(void)
{
	guardfunc;
	if (CPlayerStatus::esk_PreAttack == m_status.CurStatus())
	{
		SwitchActionStatus(CPlayerStatus::esk_Idle, CStatusTimer::NoLimitDelay );
	}
	return false;
	unguard;
}

void CPlayer::AddDeathTask()
{
	guardfunc;

	m_actionQueue.Push_Death();
	unguard;
}
//*/���⶯��

void CPlayer::Expression(ExpressionInfo* pInfo)
{
	guardfunc;
	DWORD dwTime = 1000;
	ItemDefine::SItemAction* pItem = (ItemDefine::SItemAction *)GettheItemDetail().GetItemByID(pInfo->iActionID);
	//
	if (NULL != pItem)
	{
		dwTime = pItem->stLastingPlayTime;
	}
	//
	SwitchActionStatus( CPlayerStatus::esk_ActionTime, dwTime);
	//
	unguard;
}

void CPlayer::HoldSkillEnd()
{
	guardfunc;
	m_iPlayerStatus = Player_Status_Normal;
	SwitchActionStatus( CPlayerStatus::esk_Idle, CStatusTimer::NoLimitDelay );
	m_bCanInterruptIntonating = true;
	m_skillRuntimeDesc.Reset();
	unguard;
}

void CPlayer::HoldSkillCancel()
{
	guardfunc;

	SwitchActionStatus( CPlayerStatus::esk_Idle, CStatusTimer::NoLimitDelay );
	m_skillRuntimeDesc.Reset();

	m_iPlayerStatus = Player_Status_Normal;
	unguard;
}

void CPlayer::BeAttacked(void)
{
	guardfunc;
	SwitchActionStatus( CPlayerStatus::esk_BeAttack, 500 );
	unguard;
}

void CPlayer::HoldSkillOneHit()
{
	guardfunc;

	unguard;
}

void CPlayer::Intonate(IntonateInfo* pIntonageInfo)
{
	guardfunc;
	m_iPlayerStatus = Player_Status_Intonate;

	if( !pIntonageInfo )
		return;
	//lyhȥ������
	if( pIntonageInfo->pSrc )
		pIntonageInfo->pSrc->DecRef();
	if( pIntonageInfo->pDst )
		pIntonageInfo->pDst->DecRef();

	//��ʹ�úü��ܺ󡣸������Ҫ���	
	//�л�״̬�����ʳ�
	ItemDefine::SItemSkill *pSkill = 
		GettheItemDetail().GetSkillByID(pIntonageInfo->iSkillNo, pIntonageInfo->iSkillLevel);

	if ( NULL == pSkill )
		return;

	if (NULL != pSkill)
	{

		// �Ƿ���Ҫ��Ⱦ��Ч
		if( CanRenderPlayerEffect(GetID()) )
		{
			const char *pEffectPath = NULL;
			if( m_ucSex == Sex_Female )
				pEffectPath = pSkill->GetIntonateEffectName2();
			else
				pEffectPath = pSkill->GetIntonateEffectName();

			if( stricmp( pEffectPath, "NULL" ) != 0 )
			{
				guard(testscale);				
				m_nIntonatingEffectID = PlayEffect( (char*)pEffectPath, this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this) );
				unguard;
			}
		}

		SwitchActionStatus( CPlayerStatus::esk_Intonate, MAX_STATUS_TIME );
	}
	unguard;
}

//////////////////////////////
void CPlayer::Dead()
{
	guardfunc;

	// ������һ�����˵�ʱ��
	m_bDead = TRUE;
	m_dwDeadTime = 0;
	// ����������Լ������ActionManager
	if( m_bRole )
	{
		g_ActionManager.Clear();
	}

	unguard;
}

bool CPlayer::Attack( SAttackInfo* pAttackInfo, bool bMustToDo /* = false  */)
{
	guardfunc;
	if( !m_pAnim )
	{
		if( GetAttackInfo() )
		{
			// ������ʾ�������˺�����Чmove
			OnHitPoint( TRUE, GlobalControl::eNormal, GetAttackInfo() );
		}

		m_pAttackInfo = pAttackInfo;
		SwitchActionStatus( CPlayerStatus::esk_Attack, pAttackInfo->dwActionTime );
		return true;
	}

	// ��ǰ�������ܻ��������򲥷��¹�������
	int nUpperAnimType = m_pAnim->GetCurUpperAnimType();
	if( nUpperAnimType == MoreActionClient::Hurt )
	{
		bMustToDo = true;
	}
	BOOL bHitPointPlayOver = m_pAnim->IsUpperAnimHitPointPlayOver();
	BOOL bUpperAnimPlayOver = m_pAnim->IsUpperAnimPlayOver();

	// ��ϵ�ǰ����
	{   //lyhtexiaoguai
		m_pAttackInfo = pAttackInfo;

		if( (!m_bHitPointPlayOver || Object_Effect == GetCharType()) && GetAttackInfo() )
		{
			// ������ʾ�������˺�����Ч
			if (Object_Effect == GetCharType()) //��Ч�ֲ����ͷż�����Ч
			{
				ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(m_pAttackInfo->iSkill,
					m_pAttackInfo->iSkillLevel );

				const char *pEffectPath = NULL;
				pEffectPath = pSkill->GetAttackerEffectName();
				if( stricmp( pEffectPath, "NULL" ) != 0 )
					PlayEffect( (char*)pEffectPath, this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this) );
			}

			OnHitPoint( TRUE, GlobalControl::eNormal, GetAttackInfo() );
		}

		if (Object_Effect == GetCharType())
			return true;

		if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
			m_pAnim->ResetUpperAnimPlayOver();
		SwitchActionStatus( CPlayerStatus::esk_Attack, pAttackInfo->dwActionTime );
		return true;
	}


	return true;

	unguard;
}

void CPlayer::EndAttack( SAttackInfo* pAttackInfo )
{
	guardfunc;
	CPlayer* pSrcPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->nSrcId );
	if ( !pSrcPlayer )
	{
		return;
	}
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pAttackInfo->iSkill, pAttackInfo->iSkillLevel);
	if( !pSkill )
	{
		return;
	}
	for( int i = 0; i < pAttackInfo->nRecordCount; i++ )
	{
		CPlayer* pDestPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->nTargetId );

		if (NULL == pDestPlayer)
		{
			continue;
		}
		SAttackInfoRecord* pRecord = &pAttackInfo->records[i];
	}
	unguard;
}

void CPlayer::EndIntonate(IntonateEndInfo* pInfo)
{
	guardfunc;

	// ��������,��Ҫ��������Ч����
	guard( test );
	m_bIntonating = FALSE;
	m_bCanInterruptIntonating = true;

	if( m_bRole )
		s_CUI_Progress.SetProgressComplete();

	// �򲹶�������ǲɼ����ܣ���ɼ���Ϊ�������ܽ�����ֱ���е�idle��QL, 2009/06/19
	if( !IsCollectSkill(pInfo->ustSkillId) && !IsMountMonsterSkill(pInfo->ustSkillId) )
	{
		IntonateEndInfo::EmissionTarget *pTarget = &pInfo->targetList[0];
		SwitchSpellAnim( pTarget->dwEmissionFlyTime, pTarget->target.ustTargetID, pInfo->ustSkillId, pInfo->ustSkillLevel );
		for (int i = 1;i < (int)MAXEMISSIONNUM;++i)
		{
			pTarget = &pInfo->targetList[i];
			if(pTarget&&pTarget->target.ustTargetID > 0)
				PlaySpellEffect( pTarget->dwEmissionFlyTime, pTarget->target.ustTargetID, pInfo->ustSkillId, pInfo->ustSkillLevel );
		}
	}
	else	// �ɼ���������idle����
	{
		SetShowWeapon(TRUE, TRUE);

		if( g_bNextNotIntonate )
		{
			SetIntonating(FALSE);
			g_bNextNotIntonate = FALSE;
		}

		RemoveAdvanceSkillByID( pInfo->ustSkillId );

		SwitchIdleAnim();

		return;
	}

	SetIntonatingTarget(0);

	// ����ǳ�漼�ܵĻ���������״̬
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( pInfo->ustSkillId, pInfo->ustSkillLevel );
	guard(test1)
		if( pSkill )
		{
			if( pSkill->bAssaultSkill )
			{
				CPlayer* pTargetPlayer = theApp->GetPlayerMgr()->FindByID( pInfo->targetList[0].target.ustTargetID );

				if( pTargetPlayer )
				{
					m_bAssaultMoving = TRUE;
					m_shAssaultTargetID = pTargetPlayer->GetID();
				}
				SetInstantMoving( false, pSkill );
			}

			if( pSkill->ustInstantMovingType == IMT_Forward )
			{
				if( m_bRole )
				{
					D3DXVECTOR3 vTargetPos = GetPos();
					vTargetPos = vTargetPos + GetCurDir()*pSkill->fRangeCanCast ;

					float fDir;
					GetDir(&fDir);

					SetInstantTargetPos( vTargetPos, fDir, (EInstantMovingType)pSkill->ustInstantMovingType, pSkill );
					SetCurRenderAlpha( 0.4f );
				}
				else
				{
					if( theHeroGame.GetPlayerMgr() && GetID() == theHeroGame.GetPlayerMgr()->GetLockPlayerID() )
					{
						//s_CUI_ID_FRAME_NpcChatDialogBox.SetNpc(-1);
						s_CUI_NpcTaskDialogBox.SetNpc(-1);
						if (!thePlayerRole.IsTeamMember(GetName()))
						{
							theHeroGame.GetPlayerMgr()->SetLockNpc(-1);
						}
					}
					SetCurRenderAlpha( 0.4f );
					SetInstantMoving( true, pSkill );
					m_dwInstantMovingStartTime = HQ_TimeGetTime();
				}
			}
			else if (pSkill->ustInstantMovingType == IMT_Backwards)
			{
				if( m_bRole )
				{
					D3DXVECTOR3 vTargetPos = GetPos();
					vTargetPos = vTargetPos - GetCurDir()*pSkill->fRangeCanCast ;

					float fDir;
					GetDir(&fDir);

					SetInstantTargetPos( vTargetPos, fDir, (EInstantMovingType)pSkill->ustInstantMovingType, pSkill );
					SetCurRenderAlpha( 0.4f );
				}
				else
				{
					if( theHeroGame.GetPlayerMgr() && GetID() == theHeroGame.GetPlayerMgr()->GetLockPlayerID() )
					{
						//s_CUI_ID_FRAME_NpcChatDialogBox.SetNpc(-1);
						s_CUI_NpcTaskDialogBox.SetNpc(-1);						
						if (!thePlayerRole.IsTeamMember(GetName()))
						{
							theHeroGame.GetPlayerMgr()->SetLockNpc(-1);
						}
					}
					SetCurRenderAlpha( 0.4f );
					SetInstantMoving( true, pSkill );
					m_dwInstantMovingStartTime = HQ_TimeGetTime();
				}
			}
			else if (pSkill->ustInstantMovingType == IMT_TargetBack)
			{
				if( m_bRole )
				{
					CPlayer* pTargetPlayer = theApp->GetPlayerMgr()->FindByID( pInfo->targetList[0].target.ustTargetID );
					if(pTargetPlayer)
					{
						D3DXVECTOR3 vTargetPos = pTargetPlayer->GetPos();
						D3DXVECTOR3 vDir = pTargetPlayer->m_vDir;

						D3DXVec3Normalize(&vDir, &vDir);

						float fDir = atan2f(vDir.y, vDir.x);

						vTargetPos = vTargetPos - vDir * pTargetPlayer->GetBodyLengthSize();

						SetInstantTargetPos(vTargetPos, fDir, (EInstantMovingType)pSkill->ustInstantMovingType, pSkill);

						SetCurRenderAlpha( 0.4f );
					}
				}
				else
				{
					if( theHeroGame.GetPlayerMgr() && GetID() == theHeroGame.GetPlayerMgr()->GetLockPlayerID() )
					{
						//s_CUI_ID_FRAME_NpcChatDialogBox.SetNpc(-1);
						s_CUI_NpcTaskDialogBox.SetNpc(-1);
						if (!thePlayerRole.IsTeamMember(GetName()))
						{
							theHeroGame.GetPlayerMgr()->SetLockNpc(-1);
						}
					}
					SetCurRenderAlpha( 0.4f );
					SetInstantMoving( true, pSkill );
					m_dwInstantMovingStartTime = HQ_TimeGetTime();
				}
			}

			guard(test2);
			if( m_bRole )
			{
				//�ж��Ƿ��Զ���������Ŀ��
				if ( pSkill->bAutoAttackTarget )
				{
					CPlayer* pTagPlayer = theHeroGame.GetPlayerMgr()->FindByID( pInfo->targetList[0].target.ustTargetID );
					if( pTagPlayer )
					{
						bool canAttack = IsInAttackRange(pTagPlayer->GetPos().x, pTagPlayer->GetPos().y,
							pTagPlayer->GetBodyLengthSize(), 0);

						if( canAttack )
						{
							//����Ϣ֪ͨ������������������Ŀ��
							MsgAttackLockTarget	msg;
							g_bTheRoleAttackLockTarget = TRUE;

							if( GettheNetworkInput().SendMsg(&msg) == -1 )
							{
							}
							g_nRoleCommonAttackStatus = CAS_ATTACK_AGAIN_WHEN_FAILED;
						}
					}
				}

				// �ж��Ƿ񱣳���ͨ����
				if( !pSkill->bContinueAtt )
				{
					g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
				}
			}
			unguard;
		}
		unguard;

		guard(test3);
		m_skillRuntimeDesc.Reset();	
		unguard;
		unguard;
		unguard;
}
void CPlayer::EndMoveAStep( BYTE byDir )
{
	guardfunc;
	unguard;
}

// �������ǵ��ƶ����У�ÿ֡������
void CPlayer::HandleMoveQueue( BOOL bHang )
{
	guardfunc;
	while( m_MoveQueue.PopNextMove( m_NowMove ) )
	{
		switch( m_NowMove.stType )
		{
		case CMoveQueue::M_KEEPMOVINGTOPOS:
			{
				// ���ǰ���Ǻϲ��ƶ����������з������������������������ظ÷����ƶ�
				D3DXVECTOR3 vTargetDir;
				if( m_movepath.HasTargetDir(vTargetDir) )
				{
					float fCurDir = atan2f( vTargetDir.y, vTargetDir.x );
					m_vDir = vTargetDir;
					m_movepath.ClearTargetDir();
					SetDir(fCurDir);
					SetLowerDir(fCurDir);
				}

				if( m_movepath.SetStartPosAndTargetPos( m_x, m_y, m_NowMove.vTargetPos.x, m_NowMove.vTargetPos.y, TRUE ) )
				{
					m_bMoving = TRUE;
				}

				{
					float fDir = atan2f(m_NowMove.vDir.y , m_NowMove.vDir.x );
					SetDir( fDir );
					SetLowerDir( fDir );
					SetUpperDir( fDir );
				}
			}
			break;
		case CMoveQueue::M_MOVINGTOPOS:
			{
				// ���ǰ���Ǻϲ��ƶ����������з����������������������ٸ�λ��
				D3DXVECTOR3 vTargetDir;
				if( m_movepath.HasTargetDir(vTargetDir) )
				{
					float fCurDir = atan2f( vTargetDir.y, vTargetDir.x );
					m_vDir = vTargetDir;
					m_movepath.ClearTargetDir();
					SetDir(fCurDir);
					SetLowerDir(fCurDir);
				}

				if( m_movepath.SetStartPosAndTargetPos( m_x, m_y, m_NowMove.vTargetPos.x, m_NowMove.vTargetPos.y, FALSE, FALSE ) )
				{
					// 					if (IsMounting())
					// 					{
					// 						//add by yd to test uncontrolmove
					// 						SetUncontrolMoving(TRUE);
					// 						SetUncontrolMoveTargetPos(D3DXVECTOR3( m_NowMove.vTargetPos.x, m_NowMove.vTargetPos.y,50));
					// 					}
					m_bMoving = TRUE;
				}
				else
				{
					StopMoving();
				}

				m_vDir = m_NowMove.vDir;
			}
			break;
		case CMoveQueue::M_MOVINGTOLOCKTARGET:
			{
				if( m_movepath.SetLockTarget( m_NowMove.nTargetID, m_NowMove.fKeepDistance ) )
				{
					m_bMoving = TRUE;
				}
			}
			break;
		case CMoveQueue::M_PLAYERMOVINGDIRANDTYPE:
			{
				float fDir = atan2f(m_NowMove.vDir.y, m_NowMove.vDir.x);
				SetDir( fDir );
				SetLowerDir( fDir );

				if( m_shCurMovingType == MsgPlayerMoving::eMovingLeft )
				{
					SetLowerDir( fDir - D3DX_PI/2 );
				}

				if( m_shCurMovingType == MsgPlayerMoving::eMovingRight )
				{
					SetLowerDir( fDir + D3DX_PI/2 );
				}

				if( m_shCurMovingType == MsgPlayerMoving::eMovingForwardLeft )
				{
					SetLowerDir( fDir - D3DX_PI/4 );
				}

				if( m_shCurMovingType == MsgPlayerMoving::eMovingForwardRight )
				{
					SetLowerDir( fDir + D3DX_PI/4 );
				}

				if( m_shCurMovingType == MsgPlayerMoving::eMovingCountermarchLeft )
				{
					SetLowerDir( fDir + D3DX_PI/4 );
				}

				if( m_shCurMovingType == MsgPlayerMoving::eMovingCountermarchRight )
				{
					SetLowerDir( fDir - D3DX_PI/4 );
				}

				m_vDir = m_NowMove.vDir;
				m_shCurMovingType = m_NowMove.shMovingType;
				m_bMoving = TRUE;
			}
			break;
		case CMoveQueue::M_PLAYERPOS:
			{
				// ���ǰ���Ǻϲ��ƶ����������з����������������������ٸ�λ��
				D3DXVECTOR3 vTargetDir;
				if( m_movepath.HasTargetDir(vTargetDir) )
				{
					float fCurDir = atan2f( vTargetDir.y, vTargetDir.x );
					m_vDir = vTargetDir;
					m_movepath.ClearTargetDir();
				}

				/* float fCurDir = atan2f( m_vDir.y, m_vDir.x );
				SetDir(fCurDir);
				SetLowerDir(fCurDir);
				SetUpperDir(fCurDir);*/

				if( IsOpenPrivateShop() )
				{
					if( abs(m_x - m_NowMove.vTargetPos.x) > 0.618f && abs(m_y - m_NowMove.vTargetPos.y) > 0.618f )
					{
						if( m_movepath.SetStartPosAndTargetPos( m_x, m_y, m_NowMove.vTargetPos.x, m_NowMove.vTargetPos.y, FALSE, FALSE ) )
						{
							m_shCurMovingType = MsgPlayerMoving::eNotMoving;
							m_bMoving = TRUE;
						}
					}
				}
				else
				{
					if( m_x !=  m_NowMove.vTargetPos.x || m_y != m_NowMove.vTargetPos.y )
					{
						if( m_movepath.SetStartPosAndTargetPos( m_x, m_y, m_NowMove.vTargetPos.x, m_NowMove.vTargetPos.y, FALSE, FALSE ) )
						{
							m_shCurMovingType = MsgPlayerMoving::eNotMoving;
							m_bMoving = TRUE;
						}
					}
				}
			}
			break;
		case CMoveQueue::M_PLAYERDIR:
			{
				float fDir = atan2f(m_NowMove.vDir.y, m_NowMove.vDir.x);
				SetDir( fDir );
				SetLowerDir( fDir );
				m_shCurMovingType = MsgPlayerMoving::eNotMoving;
				m_vDir = m_NowMove.vDir;
			}
			break;
		case CMoveQueue::M_PLAYERPOSANDDIR:
			{
				if( m_movepath.SetStartPosAndTargetPos( m_x, m_y, m_NowMove.vTargetPos.x, m_NowMove.vTargetPos.y, FALSE, FALSE ) )
				{
					//////////////////
					m_bMoving = TRUE;
				}
				float fDir = atan2f(m_NowMove.vDir.y, m_NowMove.vDir.x);
				SetDir( fDir );
				SetLowerDir( fDir );

				/////////////////////
				m_shCurMovingType = MsgPlayerMoving::eNotMoving;
				m_vDir = m_NowMove.vDir;
			}
			break;
		case CMoveQueue::M_PLAYERKEEPMOVINGPOS:
			{
				// ���ǰ���Ǻϲ��ƶ����������з����������������������ٸ�λ��
				D3DXVECTOR3 vTargetDir;
				if( m_movepath.HasTargetDir(vTargetDir) )
				{
					float fCurDir = atan2f( vTargetDir.y, vTargetDir.x );
					m_vDir = vTargetDir;
					m_movepath.ClearTargetDir();
				}

				float fMovingDirX = m_NowMove.vTargetPos.x - m_x;
				float fMovingDirY = m_NowMove.vTargetPos.y - m_y;
				float fMovingDir = atan2f( fMovingDirY, fMovingDirX );

				float fCurDir = atan2f( m_vDir.y, m_vDir.x );
				// 				SetDir(fCurDir);
				// 				SetLowerDir(fCurDir);
				// 				SetUpperDir(fCurDir);
				// ȡ�ƶ����� [11/17/2010 zhangjiayi]
				SetDir(fMovingDir);
				SetLowerDir(fMovingDir);
				SetUpperDir(fMovingDir);

				m_shCurMovingType = GetMovingType( m_tdir, fMovingDir );

				if( m_movepath.SetStartPosAndTargetPos( m_x, m_y, m_NowMove.vTargetPos.x, m_NowMove.vTargetPos.y, FALSE, FALSE ) )
				{
					m_bMoving = TRUE;
				}
			}
			break;
		case CMoveQueue::M_PLAYERKEEPMOVINGPOSANDDIR:
			{
				D3DXVECTOR3 vTargetDir;
				if( !m_movepath.HasTargetDir(vTargetDir) )
				{
					float fDir = atan2f(m_NowMove.vDir.y, m_NowMove.vDir.x);
					SetDir( fDir );
					SetLowerDir( fDir );

					float fMovingDirX = m_NowMove.vTargetPos.x - m_x;
					float fMovingDirY = m_NowMove.vTargetPos.y - m_y;
					float fMovingDir = atan2f( fMovingDirY, fMovingDirX );

					m_shCurMovingType = GetMovingType( m_tdir, fMovingDir );

					if( m_movepath.SetStartPosAndTargetPos( m_x, m_y, m_NowMove.vTargetPos.x, m_NowMove.vTargetPos.y, FALSE, FALSE ) )
					{
						m_vDir = m_NowMove.vDir;
						m_bMoving = TRUE;
					}
					break;
				}
				// �����m_bHasTargetDir������M_PLAYERKEEPMOVINGPOSANDDIR_FINDPATH���������˴���Ҫbreak
			}
		case CMoveQueue::M_PLAYERKEEPMOVINGPOSANDDIR_FINDPATH:
			{
				float fMovingDirX = m_NowMove.vTargetPos.x - m_x;
				float fMovingDirY = m_NowMove.vTargetPos.y - m_y;
				float fDir = atan2f(fMovingDirY, fMovingDirX);//atan2f(m_NowMove.vDir.y, m_NowMove.vDir.x);
				SetDir( fDir );
				SetLowerDir( fDir );

				float fMovingDir = atan2f( fMovingDirY, fMovingDirX );

				m_shCurMovingType = GetMovingType( m_tdir, fMovingDir );

				if( m_movepath.SetStartPosAndTargetPos( m_x, m_y, m_NowMove.vTargetPos.x, m_NowMove.vTargetPos.y, FALSE, FALSE ) )
				{
					m_vDir.x = fMovingDirX;
					m_vDir.y = fMovingDirY;
					m_vDir.z = 0;
					m_bMoving = TRUE;
					m_movepath.SetTargetDir(m_NowMove.vDir);
				}
			}
			break;
		default:
			assert(false);
			break;
		}
	}
	unguard;
}

// ���ڴ˺��������Ƿ��ƶ�������ÿ֡������
void CPlayer::HandleActionQueue( bool bSkipStatus )
{
	guardfunc;
	if( bSkipStatus)
		goto process;

	switch (m_status.CurStatus())
	{
		//��������״̬ʱ����Ҫ��ʱ����Action
	case CPlayerStatus::esk_Attack:
	case CPlayerStatus::esk_Intonate:
	case CPlayerStatus::esk_Idle:
	case CPlayerStatus::esk_PreAttack:
	case CPlayerStatus::esk_ActionTime:
	case CPlayerStatus::esk_PreIntonate:
	case CPlayerStatus::esk_HoldSkill:
		{
process:
			if( m_actionQueue.PopNextAction(m_NowAction))
			{		
				switch( m_NowAction.stType )
				{
				case CActionQueue::A_WALK:
					{
						if (m_NowAction.bSkip)
							return;
						CActionQueue::SWalk *pWalk = (CActionQueue::SWalk *)m_NowAction.sData;
					}
					//
					break;
				case CActionQueue::A_ATTACKEX:
					{
						SAttackInfo *info = *((SAttackInfo**)m_NowAction.sData);

						if( !Attack( info ) )
						{
							if( m_NowAction.nProcessedCount < 600 )
							{
								m_NowAction.nProcessedCount++;

								if( m_bRole )
								{
									{
										m_actionQueue.PushFront_Action( m_NowAction );
									}
								}
								else
								{
									m_actionQueue.PushFront_Action( m_NowAction );
								}
							}
							else
							{
								Attack( info, true );
							}
						}
						return;
					}
					break;
				case CActionQueue::A_INTONATE:
					{
						IntonateInfo *info = (IntonateInfo*)m_NowAction.sData;
						Intonate(info);
						return;
					}
					break;
				case CActionQueue::A_STARTHOLDSKILL:
					{
						//����������״̬
						IntonateEndInfo *pInfo = (IntonateEndInfo*)m_NowAction.sData;
						EndIntonate(pInfo);

						return;
					}
					break;
				case CActionQueue::A_ENDHOLDSKILL:
					{
						//������HoldSkill״̬
						HoldSkillEnd();
						return;
					}
					break;
				case CActionQueue::A_CANCELSKILL:
					{
						//����������״̬����ά�ּ���״̬
						HoldSkillCancel();
						return;
					}
					break;
				case CActionQueue::A_EXPRESSION:
					{
						ExpressionInfo *info = (ExpressionInfo*)m_NowAction.sData;
						Expression(info);
						return;
					}
					break;
				case CActionQueue::A_DEATH:
					{
						CActionQueue::SDeath* pDeath = (CActionQueue::SDeath*)m_NowAction.sData;						
						Dead();
						return;
					}
					break;

				case CActionQueue::A_BEATTACKED:
					{
						if( HQ_TimeGetTime() - m_NowAction.dwPushTime > 2000 )
						{
							//skip this beattacked;
							//ȡ��һ��action
							goto process;
						}
						SwitchActionStatus( CPlayerStatus::esk_BeAttack, 500 );
					}
					break;
				case CActionQueue::A_SEEHOLDSKILL:	// �����A_SEEHOLDSKILLû�д���Ϊ�˱�����Լ���case
					break;
				default:
					assert( false );
					break;
				}
			}

			break;
		}
	}
	unguard;
}

void CPlayer::ResetMove( DWORD dwSerialNo )
{
	guardfunc;
	m_move.dwStartTime = 0;
	m_move.fVelocity = MOVEVELOCITY;
	m_move.dwTimeLeft = 0;
	SwitchActionStatus(CPlayerStatus::esk_Idle, CStatusTimer::NoLimitDelay);
	unguard;
}

void CPlayer::Reset()
{
	guardfunc;
	if (m_footPrint )
	{
		m_footPrint->Reset();
	}
	m_stColorId = 0;
	m_bDeadOver = false;
	m_dwDeadOverTime = 0;
	m_szName[0] = 0;
	m_pTempMapName[0] = 0;
	m_x =0;
	m_y =0;
	m_z = 0;

	m_iIDInModelMan = -1;

	m_dwLastUpdateTime=0;

	m_bRole=FALSE;
	m_stCharType = Object_Player;
	m_nModelId = -1;

	m_actionQueue.Clear();
	m_MoveQueue.Clear();

	ResetMove( 0xffffffff );

	m_bHadGotValidGuildInfo = false;

	memset( &m_charSimpleInfo, 0x00, sizeof( m_charSimpleInfo ) );

	m_bServerPermitMove = TRUE;

	SetDirInt( 0 );

	m_szDisplayName[0] = 0;

	m_pAnim = NULL;
	m_pMountAnim = NULL;
	m_bMounting = FALSE;
	m_nMountModelID = -1;
	m_nMountLevel = 0;
	m_nMountBoneID = THEBONENOTEXISTINMEX2;
	m_fMoveRate = g_fTheRoleMovingRate/*4.6f*/;
	m_fCurMoveRate = g_fTheRoleMovingRate/*3.0f*/;
	m_fMovingStep = g_fTheRoleMovingStep/*1.382f*/;
	m_fRunStep = g_fTheRoleRunningStep/*2.56f*/;
	m_fSwimStep = 5.12f;
	m_fNormalAttackRate = 1.0f;

	m_hpinfo.bIsValid = false;
	m_hpinfo.fShowPercent = -1;

	m_bDead = false;
	m_bWillDie = false;
	m_bIsActivePlayer = true;


	m_bHadGotValidGuildInfo = false;
	m_dwGuildId = GuildDefine::InitID;
	m_szGuildName[0] = 0;

	m_byOfficialLevel = 0;

	m_dwExploit = 0;

	m_bHavePet = FALSE;
	m_PetID = FALSE;
	m_bHaveMaster = FALSE;
	m_bMasterIsMe = FALSE;
	m_MasterID = -1;

	DestroyCS();
	m_iRef = 0;
	m_bNeedToDelete = false;
	m_iPlayerStatus = Player_Status_Normal;

	m_nNpcTipsType = CPlayerMgr::eNpcTips_None;
	m_fShowNameAphla = 1;
	m_bFightPose = FALSE;

	m_dwLastScabbardBeginTime = HQ_TimeGetTime();
	m_ucLiftFlagStatus = 0;
	m_fDistanceToPickRay = 0;

	m_vctAdvanceSkill.clear();
	m_bMoveRateChange = FALSE;
	m_bForceTurnRole = FALSE;

	m_dwNextActionTime = 0;
	m_shNextActionId = 0;
	m_bNeedInitNpcAction = FALSE;
	m_nInteractionMasterPlayerID = -1;
	m_bNeedResetPosAfterInteraction = FALSE;
	m_bNeedRender = FALSE;
	m_iBuffStatusAnimType = -1;
	m_bIsVisibleToOtherPlayer = TRUE;

	memset( &m_equips, 0, sizeof(CPlayer_SEquipment)*eKeyAll_Max );
	m_fPlayerScale = 1.f;

	m_fLastGetZ_x = m_fLastGetZ_y = m_fLastGetZ_z = -1;
	int random = rand();
	m_usUpdateZFrameCount = random % 50 + 50;	// m_usUpdateZFrameCountȡֵ����[50,100]
	m_usSamePosFrameCount = 0;
#ifdef NEW_PLAYER_LOAD
	m_bModelLoaded = FALSE;
#endif
	m_fPetAdjustPosCD = 0;
	m_nMountOperaType = 0;
	m_bItemPlayedDropAnim = false;
	m_nSceneID = -1;
	m_nCurrSegmentIndex = 0;
	m_dwCurrSegBeginTime = 0;
	unguard;
}

float CPlayer::GetNormalStep()
{
	guardfunc;

	//�����ܲ�Step
	return GetRunStep();
	unguard;
}

//һЩ״̬���ƺ���
//---
// �ı�״̬
// ����˵��:
//      ��Ҫ�л���Ŀ��״̬
//      ��״̬��Ҫ������ʱ��
//      ��״̬��ʲôʱ�����
//---
void    CPlayer::SwitchActionStatus( CPlayerStatus::STATUS_KEY CurKey, DWORD Delay, CPlayerStatus::STATUS_KEY NextKey, BOOL bPlayAnim/* = TRUE*/ )
{
	guardfunc;
	DWORD dwAnimPlayTime = Delay;
	DWORD dwStatusTime = Delay;
	CPlayerStatus::STATUS_KEY  lastStatus = m_status.CurStatus();
	m_status.SwitchStatus(CurKey, dwStatusTime, NextKey);
	//�л�����Ҫ״̬�Ķ���
	if( bPlayAnim )
		SwitchAnim(lastStatus, dwAnimPlayTime);

	// ����ֵ�ģ����
	if( CurKey == CPlayerStatus::esk_Attack )
		AdjustAttackPos();

	unguard;
}
//ת��
void    CPlayer::ActionStatusChangeDir(void)
{
	guardfunc;
	float	dir;
	//
	dir = atan2f((float)(m_operation.target.y- m_ptLoc.y), (float)(m_operation.target.x-m_ptLoc.x));
	//
	SetDir(dir);
	//����Ϣ֪ͨ��������ת����
	MsgChangeDir ChangeDirMsg;
	//
	ChangeDirMsg.fChangeDir = dir;
	//
	GettheNetworkInput().SendMsg(&ChangeDirMsg);
	//
	//������߸ı�״̬��Idle
	SwitchActionStatus( CPlayerStatus::esk_Idle, CStatusTimer::NoLimitDelay );
	//
	AddOperationIdle();
	unguard;
}
// Ԥ������״̬
void    CPlayer::ActionStatusPreAttack(void)
{
	guardfunc;
	unguard;
}
// ����״̬
void    CPlayer::ActionStatusAttack(void)
{

	guardfunc;
	unguard;
}
void    CPlayer::ActionStatusPreIntonate(void)
{
	guardfunc;
	unguard;
}

void    CPlayer::ActionStatusIntonate(void)
{
	guardfunc;
	unguard;
}

void    CPlayer::ActionStatusHoldSkill(void)
{
	guardfunc;
	unguard;
}

// �ܻ�״̬
void    CPlayer::ActionStatusBeAttack(void)
{
	guardfunc;
	unguard;
}

// ����״̬
void    CPlayer::ActionStatusMiss(void)
{
	guardfunc;
	unguard;
}

// �赹״̬
void    CPlayer::ActionStatusSleep(void)
{
	guardfunc;
	unguard;
}
// ����״̬
void    CPlayer::ActionStatusDie(void)
{
	guardfunc;
	static	int s_player_dead_id = 0;
	static	int s_npc_dead_id = 0;
	int  dead_id = 0;
	//
	//
	if (IsPlayer())
	{
		if (0 == s_player_dead_id)
			s_player_dead_id = GetPlayerActionID(MoreAction::Action_dead);
		dead_id = s_player_dead_id;
	}
	else 
	{
		if (0 == s_npc_dead_id)
			s_npc_dead_id = GetPlayerActionID(MoreAction::Action_dead);
		dead_id = s_npc_dead_id;
	}
	unguard;
}
//��һ��ʱ������Ī������
void    CPlayer::ActionStatusActionTime(void)
{
	guardfunc;
	//��ʱ�������ʱ��Ѷ����ı�Ϊ����
	unguard;
}
//---
//   ��ȡ����״̬
//---
void    CPlayer::ActionStatusPickItem(void)
{
	guardfunc;
	TryPickItem();
	//
	//������߸ı�״̬��Idle
	SwitchActionStatus( CPlayerStatus::esk_Idle, CStatusTimer::NoLimitDelay );
	//�ı�AI��idle...(�Ҳ���������������û�а취������:S)..�鷳������
	if (SOperation::eOpMoveGetRangeItem != m_operation.dwType)//��pick�ܶ���ߵ�ʱ���ܡ�pickһ����ͣ����..
		AddOperationIdle();
	unguard;
}
//---
//	��������
//---
void    CPlayer::ActionStatusDropItem(void)
{
	guardfunc;
	unguard;
}
//---
//  �Ի�
//---
void CPlayer::ActionStatusTalk(void)
{
	guardfunc;
	//
	TryTalkWithNpc();
	//
	SwitchActionStatus( CPlayerStatus::esk_Idle, CStatusTimer::NoLimitDelay );
	//�ı�AI��idle...(�Ҳ���������������û�а취������:S)
	AddOperationIdle();
	unguard;
}
//---
//  ����
//---
void    CPlayer::ActionStatusTrade(void)
{
	guardfunc;
	//������߸ı�״̬��Idle
	SwitchActionStatus(CPlayerStatus::esk_Idle, CStatusTimer::NoLimitDelay);
	//�ı�AI��idle...(�Ҳ���������������û�а취������:S)
	AddOperationIdle();
	unguard;
}

//////////////////////////////////////////////////////////////////////////
//	�Ƿ�����ˮ��
BOOL    CPlayer::IsInWater(void)
{
	return m_bInWater && !m_bInSingleFloor;
}

void    CPlayer::SetInWater(BOOL bIn)
{
	if (IsRole() && bIn != m_bInWater)
	{
		// ˢ��HotKey
		s_CUI_ID_FRAME_MAIN.RefeashHotKey();
		s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
	}
	m_bInWater = bIn;

	if ( this == theHeroGame.GetPlayerMgr()->GetMe() && bIn == FALSE && s_CUI_ID_FRAME_Target.IsVisable() )
	{
		//add by zmy, ����ˮ���ʱ�����������ѡ�����״̬��Ҫ�û�ս��״̬
		CPlayer* targetPlayer = theHeroGame.GetPlayerMgr()->FindByID(s_CUI_ID_FRAME_Target.GetPlayerID()) ;
		if( g_bTheRoleAttackLockTarget && targetPlayer && ( targetPlayer->IsMonster() || thePlayerRole.GetDuelTarget() == targetPlayer->GetID() ) && targetPlayer->IsPet() == FALSE )
		{

			//if( !this->HasFightFlag(eFighting) )
			//	this->AddFightFlag( eFighting );
			if ( !this->IsFightPose() && this->HasFightFlag(eFighting) ) //����ˮ��ʱ��������Ǵ���ս��״̬���Ҳ���ս����̬��Ҫ�л���
			{
				this->ChangeToFightPose();
			}
		}
	}
}

//---
//  ����״̬
//---
void    CPlayer::ActionStatusIdle(void)
{
	guardfunc;
	const DWORD   c_ChangeToIdleTime = 500;
	const	DWORD c_dwSwitchFightStatusTime = 10000;
	const	DWORD c_dwSwitchIdleTime = 10000;

	unguard;
}
void CPlayer::ActionStatusBeatBack()
{
	guardfunc;

	unguard;
}

void CPlayer::RoleMovingCollision()
{
	guardfunc;

	unguard;
}

BOOL CPlayer::RoleMoveToShore( D3DXVECTOR3& vNextPos, D3DXVECTOR3& vNextDir, BOOL& bCollision, float fRoleHeight, float fCurMoveDist )
{
	guardfunc;
	if( IsInWater() && !getwsCamera()->GetFreeCameraMode() && !g_bTheRoleJumping )
	{
		DWORD dwLoadFlags = 0;
		BOOL  bInFloor = FALSE;
		D3DXVECTOR3 vAxis( 0, 0, 1 );
		float fFarWorldZ = GetZByXY( m_z + fRoleHeight, vNextPos.x, vNextPos.y, 0, &bInFloor, &dwLoadFlags, FALSE ,&vAxis);
		CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
		CWorldChunk* pChunk = pTile->GetChunkFromPos(vNextPos.x, vNextPos.y);

		if( pChunk )
		{
			float fStature = 1.2f;
			Box* pBBox = GetWorldBBox();
			if( pBBox )
				fStature = (pBBox->v[4].z - pBBox->v[0].z) * 0.8f;
			if( pChunk->GetLiquidHeight() - fFarWorldZ > fStature )
			{
				return TRUE;
			}
			else
			{
				D3DXVECTOR3 vUp( 0, 0, 1 );

				D3DXVec3Normalize( &vAxis, &vAxis );

				float fDot = D3DXVec3Dot( &vUp, &vAxis );
				float fTheta = acosf( fDot );

				if( fTheta > g_fTheRoleSlipJumpingAngle && ( vAxis.x != 0 || vAxis.y != 0 ) )
				{
					bCollision = TRUE;
				}
			}
		}
		else
		{
			bCollision = TRUE;
		}
	}
	return TRUE;
	unguard;
}

volatile swVec2f g_destPos;
bool g_PFOK = false;
BOOL g_FindPathThreadWillExit = false;
BOOL g_FindPathThreadExit = false;
extern BOOL g_FindPathThreadPause ;
extern BOOL g_FindPathThreadWillPause ;
HANDLE g_hNewPathRequest = 0;
void FindPathThreadProc( void* lpParam )
{
	g_FindPathThreadPause = FALSE;
	g_FindPathThreadWillPause = FALSE;

	while(!g_FindPathThreadWillExit)
	{
		WaitForSingleObject(g_hNewPathRequest,INFINITE);
		if (g_FindPathThreadWillPause)
		{
			g_FindPathThreadPause = TRUE;
			g_FindPathThreadWillPause = FALSE;
		}
		if (!g_FindPathThreadPause)
		{
			//if (g_FindPathThreadPause)
			//{
			//    Sleep(10);
			//}

			CPlayer* pMe = theApp->GetPlayerMgr()->GetMe();
			std::vector<swVec2f> tempFoundPath;

			swVec2f sourcePos;
			pMe->GetPos(&sourcePos.x, &sourcePos.y, NULL);

			SwMap &swmap = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile()->ReachableMap();
			if (swmap.CanMove(sourcePos, *((swVec2f*)(&g_destPos))))
			{
				g_vTheRoleTargetPos.x = g_destPos.x;
				g_vTheRoleTargetPos.y = g_destPos.y;

				std::vector<swVec2f> &vecFoundPath = pMe->GetFoundPathAndLocked();
				vecFoundPath.clear();
				vecFoundPath.push_back(swVec2f(sourcePos.x,sourcePos.y));
				vecFoundPath.push_back(swVec2f(g_destPos.x,g_destPos.y));

				pMe->SetRefreshPathDirction(true);
				pMe->UnlockedFoundPath();
			}
			else
			{
				std::vector<swVec2f> tempFoundPath0;
				if (swmap.FindPath(sourcePos, *((swVec2f*)(&g_destPos)), tempFoundPath0))
				{
					//if (g_hNewPathRequest)
					//{
					//    continue;
					//}
					if (tempFoundPath0.size() > 4)
					{
						//��ǰλ�õ���2����Ѱ·
						std::vector<swVec2f> tempFoundPath1;

						pMe->GetPos(&sourcePos.x,&sourcePos.y,NULL);
						swmap.FindPath(sourcePos, tempFoundPath0[2], tempFoundPath1);
						for (int i = 0; i < tempFoundPath1.size();++i)
						{
							tempFoundPath.push_back(tempFoundPath1[i]);
						}
						for (int i = 3; i < tempFoundPath0.size();++i)
						{
							tempFoundPath.push_back(tempFoundPath0[i]);
						}
					}
					else
					{
						for (int i = 1; i < tempFoundPath0.size();++i)
						{
							tempFoundPath.push_back(tempFoundPath0[i]);
						}

					}

					if (tempFoundPath.size() > 1)
					{
						tempFoundPath[tempFoundPath.size() - 1].x = g_destPos.x;
						tempFoundPath[tempFoundPath.size() - 1].y = g_destPos.y;
					}
					else
					{
						tempFoundPath.push_back(swVec2f(g_destPos.x,g_destPos.y));
					}
					pMe->SetCurrPathPointIndex(0);
					if(tempFoundPath.size() > 0)
					{
						g_vTheRoleTargetPos.x = tempFoundPath[0].x;
						g_vTheRoleTargetPos.y = tempFoundPath[0].y;
					}

					std::vector<swVec2f> &vecFoundPath = pMe->GetFoundPathAndLocked();
					vecFoundPath.assign(tempFoundPath.begin(), tempFoundPath.end());

					pMe->SetRefreshPathDirction(true);
					pMe->UnlockedFoundPath();
				}
				else
				{//Ϊ�˱�����̳߳�ͻ
					g_showPFErrorText = true;
				}
			}
			g_PFOK = true;
		} 

	}
	g_FindPathThreadExit = true;
	return;
}
bool CPlayer::CalcRoleMovePath(const D3DXVECTOR3& targetPos,bool bSync)
{
	guardfunc;
	CWorldTile* pCurrTile = CURRENTTILE;

	if (!pCurrTile || (targetPos.x < 0.f )|| (targetPos.x > pCurrTile->GetWidth() - 1) || (targetPos.y < 0.f) || (targetPos.y > pCurrTile->GetDepth() - 1))
	{
		return false;
	}
	if (!bSync&& theHeroGame.GetPlayerMgr()->ProcessShift(targetPos.x,targetPos.y))
	{
		return false;
	}

	swVec2f sourcePos(m_x, m_y);
	swVec2f destPos(targetPos.x, targetPos.y);

	SwMap& swmap = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile()->ReachableMap();
	if (!swmap.CanReach(sourcePos)  )
	{
		return false;
	}
	if (!swmap.CanReach(destPos))
	{
		swVec2f reachablePos;
		if (swmap.GetReachablePosToDest(sourcePos,destPos,&reachablePos))
		{
			destPos = reachablePos;
		}
		else
		{
			return false;
		}
	}

	// 	if (!swmap.CanMove(sourcePos, destPos))
	{
		g_destPos.x = destPos.x;
		g_destPos.y = destPos.y;
		if (bSync)
		{
			g_PFOK = false;
		}
		SetEvent(g_hNewPathRequest);
		if (bSync)
		{
			while(!g_PFOK)
			{
				Sleep(10);
			}
		}
	}
	// 	else
	// 	{
	// 		g_vTheRoleTargetPos.x = destPos.x;
	// 		g_vTheRoleTargetPos.y = destPos.y;
	// 		std::vector<swVec2f> vecFoundPath;
	// 		vecFoundPath.push_back(swVec2f(sourcePos.x,sourcePos.y));
	// 		vecFoundPath.push_back(swVec2f(destPos.x,destPos.y));
	// 		CPathDirection::Instance()->CreateEffectArr(vecFoundPath);
	// 	}
	return true;
	unguard;
}

void CPlayer::RoleMovePathProcess()
{
	guardfunc;
	std::vector<swVec2f>& foundPath = GetFoundPathAndLocked();
	if (m_RefreshPathDirction)
	{
		CPathDirection::Instance()->CreateEffectArr(foundPath);
		m_RefreshPathDirction = false;
	}
	if (!m_bMoving || g_bTheRoleMovingByDir)
	{
		foundPath.clear();
		m_currPathPointIndex = 0;
	}

	if (m_currPathPointIndex < foundPath.size())
	{
		swVec2f curFindPathPoint = foundPath[m_currPathPointIndex];
		if (g_vTheRoleTargetPos.x != curFindPathPoint.x || g_vTheRoleTargetPos.y != curFindPathPoint.y)
		{
			g_vTheRoleTargetPos.x = curFindPathPoint.x;
			g_vTheRoleTargetPos.y = curFindPathPoint.y;
		}
	}
	UnlockedFoundPath();
	unguard;
}

//////////////////////////
void CPlayer::RoleMoveProcess()
{
	guardfunc;

	if ( s_CUI_ID_FRAME_Team.GetTeamFollowID() >= 0 )
	{
		//����Ӹ����ʱ�򣬲����ü��̻��������Ծ���ƶ�
		m_bJumping = false;
		g_bTheRoleMovingByDir = FALSE;
	}

	RoleMovePathProcess();

	//std::vector<swVec2f> &foundPath = GetFoundPathAndLocked();
	const std::vector<swVec2f> &foundPath = GetFoundPathUnLocked();
	int nPathLength = foundPath.size();
	//UnlockedFoundPath();

	float fPosXOff = 0;
	float fPosYOff = 0;
	float fCurMoveDist = 0;
	float fDir = 0;
	float fxtoy = 0;
	static float fRotateX = g_fTheRoleRotateZCorrect;
	D3DXVECTOR3 vNextFramePos;

	fRotateX = g_fTheRoleRotateZCorrect + g_fTheRoleDirCorrect;
	fRotateX = fmodf( fRotateX, D3DX_PI*2 );

	if( fRotateX < 0 )
	{
		fRotateX += D3DX_PI*2;
	}

	// �ж��Ƿ��ϸ���
	if( s_CUI_ID_FRAME_Target.GetFollowPlayerId() >= 0 )
	{
		// ����������Ҽ�ת��
		if((theApp->GetPlayerMgr()->IsTurnRoleToCamera() && g_bMouseRButtonIsDown ) 
			|| g_bRoleRotatebyDir
			|| g_bTheRoleCountermarch 
			|| g_bTheRoleMovingByDir // ���ˣ���������ƶ�����ͬʱ��������Ҽ��ƶ�
			|| (g_bMouseLButtonIsDown && g_bMouseRButtonIsDown))
		{
			if( s_CUI_ID_FRAME_Target.GetFollowPlayerId() >= 0 )
				s_CUI_ID_FRAME_Target.SetFollowPlayerId(-1);
			CrossMapPF::Instance()->Reset();
			CPathDirection::Instance()->Reset();
			s_CUI_ID_FRAME_MiniMap.SetAutoRuning(false);
		}
	}

	if((theApp->GetPlayerMgr()->IsTurnRoleToCamera() && g_bMouseRButtonIsDown ) 
		|| g_bRoleRotatebyDir
		|| g_bTheRoleCountermarch 
		|| g_bTheRoleMovingByDir // ���ˣ���������ƶ�����ͬʱ��������Ҽ��ƶ�
		|| (g_bMouseLButtonIsDown && g_bMouseRButtonIsDown))
		if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
			s_CUI_ID_FRAME_AutoAttackSet.ID_BUTTON_StopOnButtonClick(NULL);

	if( !m_bMoving 
		&& g_bMouseRoleTurn 
		&& !(GetSitStatus() && !GetSitInterrupt())
		&& !IsPlayStandAnim() 
		&& ((theApp->GetPlayerMgr()->IsTurnRoleToCamera() && g_bMouseRButtonIsDown ) || g_bRoleRotatebyDir) )
	{

		fDir = -fRotateX;

		fDir -= D3DX_PI/2;

		if( fDir > D3DX_PI*2 )
		{
			fDir -= D3DX_PI*2;
		}

		if( fDir > D3DX_PI*2 )
		{
			fDir -= D3DX_PI*2;
		}

		if( fDir < 0 )
		{
			fDir += D3DX_PI*2;
		}

		if( fDir > D3DX_PI )
		{
			fDir = -D3DX_PI*2 + fDir;
		}

		SetDir( fDir );
		SetLowerDir( fDir );
	}

	if( m_bMoving )
	{
		if( !g_bTheRoleJumping )
		{
			if( m_bMounting )
				m_fJumpSpeed = GetMoveRate();
			else
				m_fJumpSpeed = GetMoveRate();
		}
	}
	else
	{
		if( !g_bTheRoleJumping )
		{
			m_fJumpSpeed = 0.0f;
		}

		if( g_bTheRoleSlipJumping )
		{
			m_fJumpSpeed = GetMoveRate();
		}
	}

	fDir = m_dir;
	GetAngleTo2D( m_dir, &m_vCurDir.x, &m_vCurDir.y );

	if( fDir > D3DX_PI*2 )
	{
		fDir -= D3DX_PI*2;
	}

	if( fDir < 0 )
	{
		fDir += D3DX_PI*2;
	}

	if( m_bMoving || g_bTheRoleJumping )
	{
		vNextFramePos.x = m_x;
		vNextFramePos.y = m_y;
		vNextFramePos.z = 0;

		if( g_bTheRoleJumping )
		{
			if( g_bTheRoleSlipJumping )
			{
				m_fStartJumpingSpeed = 0.0001f;
			}
			else
			{
				m_fStartJumpingSpeed = m_fMaxStartJumpingSpeed;
			}
		}

		if( getwsCamera()->GetCameraRotateZ() < -getwsCamera()->GetLookUpAngle() )
		{
			float fZRotateDistance = getwsCamera()->GetCameraRotateXSpeed()*g_dwLastFrameCostTime*0.01f;
			getwsCamera()->SetCameraRotateZ( getwsCamera()->GetCameraRotateZ() + fZRotateDistance );
		}

		if( g_bAutoRunForward || g_bTheRoleSlipJumping || ( g_bTheRoleMovingByDir || ( g_bTheRoleJumping && !g_bTheRoleMoveToTargetPos ) ) )
		{
			if( g_bTheRoleJumping )
			{
				fDir = atan2f(g_vTheRoleJumpingDir.y, g_vTheRoleJumpingDir.x) - g_fTheRoleJumpingRotate;
			}
			else
			{
				fDir = atan2f(g_vTheRoleTargetDir.y,g_vTheRoleTargetDir.x) - fRotateX;
			}

			if( g_bTheRoleJumping )
			{
				if( g_bTheRoleSlipJumping )
				{
					fCurMoveDist = m_fJumpSpeed*g_dwSmoothFrame/1250;
				}
				else
				{
					if( g_vTheRoleJumpingDir.x == 0 && g_vTheRoleJumpingDir.y == 0 )
					{
						m_fJumpSpeed = 0;
					}

					if( m_fJumpSpeed < 2 && g_vTheRoleTargetDir.x == 0 && g_vTheRoleTargetDir.y == 0 )
					{
						g_vTheRoleJumpingDir.x = 0;
						g_vTheRoleJumpingDir.y = 0;
						m_fJumpSpeed = 0;
					}
					else
					{
						if( m_fJumpSpeed == 0 && g_vTheRoleJumpingDir.x == 0 && g_vTheRoleJumpingDir.y == 0 )
						{
							g_vTheRoleJumpingDir = g_vTheRoleTargetDir;
							g_bTheRoleJumpingCountermarch = g_bTheRoleCountermarch;
							m_fJumpSpeed = 1.6f;
						}
					}
					fCurMoveDist = m_fJumpSpeed*g_dwSmoothFrame/1000;

					if( g_bTheRoleJumpingCountermarch )
					{
						g_bTheRoleCountermarch = TRUE;
						m_bCountermarch = TRUE;
					}
					else
					{
						g_bTheRoleCountermarch = FALSE;
						m_bCountermarch = FALSE;
					}
				}
			}
			else
			{
				if( g_bTheRoleCountermarch )
				{
					fCurMoveDist = GetMoveRate()*g_dwSmoothFrame/2000;
				}
				else
				{
					fCurMoveDist = GetMoveRate()*g_dwSmoothFrame/1000;
				}
			}

			{
				fxtoy = tan(fDir);

				{
					{
						fPosXOff = sqrtf(fCurMoveDist*fCurMoveDist/(1+fxtoy*fxtoy));
						fPosYOff = fabs(fxtoy*fPosXOff);
					}

					if( fDir > D3DX_PI*2 )
					{
						fDir -= D3DX_PI*2;
					}

					if( fDir < 0 )
					{
						fDir += D3DX_PI*2;
					}

					if( g_bTheRoleSlipJumping )
					{
						vNextFramePos.x += g_vTheRoleSlipJumpingDir.x*fCurMoveDist;
						vNextFramePos.y += g_vTheRoleSlipJumpingDir.y*fCurMoveDist;
					}
					else
					{
						bool bUnGetFramePos = true;
						if( ( fDir >= 0 && fDir <= D3DX_PI/2 ) || ( fDir >= -D3DX_PI*2 && fDir <= -D3DX_PI*3/2 ) )
						{
							vNextFramePos.x += fPosXOff;
							vNextFramePos.y += fPosYOff;
							bUnGetFramePos = false;
						}

						if( bUnGetFramePos && (( fDir >= D3DX_PI/2 && fDir <= D3DX_PI ) || ( fDir >= -D3DX_PI*3/2 && fDir <= -D3DX_PI )) )
						{
							vNextFramePos.x -= fPosXOff;
							vNextFramePos.y += fPosYOff;
							bUnGetFramePos = false;
						}

						if( bUnGetFramePos && (( fDir >= D3DX_PI && fDir <= D3DX_PI*3/2 ) || ( fDir >= -D3DX_PI && fDir <= -D3DX_PI/2 )) )
						{
							vNextFramePos.x -= fPosXOff;
							vNextFramePos.y -= fPosYOff;
							bUnGetFramePos = false;
						}

						if( bUnGetFramePos && (( fDir >= D3DX_PI*3/2 && fDir <= D3DX_PI*2 ) || ( fDir >= -D3DX_PI/2 && fDir <= 0 )) )
						{
							vNextFramePos.x += fPosXOff;
							vNextFramePos.y -= fPosYOff;
							bUnGetFramePos = false;
						}
					}
				}

				BOOL bRole = TRUE;
				float fRoleHeight = 80.0f*Config::m_fMdlSpaceScale;
				float fFarWorldZ = 0.0f;
				DWORD dwLoadFlags = 0;
				BOOL  bInFloor = FALSE;

				//fFarWorldZ = GetZByXY(m_z + fRoleHeight,  vNextFramePos.x, vNextFramePos.y, 0, &bInFloor, &dwLoadFlags, bRole);
				fFarWorldZ = GetZByXY(WORLD_HEIGHT,  vNextFramePos.x, vNextFramePos.y, 0, &bInFloor, &dwLoadFlags, bRole);
				float fZOffset = fFarWorldZ - m_z;

				if( fZOffset > 0.001f )
				{
					//��ɫ�������ռ��е��ƶ��ľ���
					float fSpaceDistance = sqrtf( fCurMoveDist*fCurMoveDist + fZOffset*fZOffset );

					if( !getwsCamera()->GetFreeCameraMode() && fSpaceDistance > 0 && fSpaceDistance > fCurMoveDist)
					{
						float t = fCurMoveDist/fSpaceDistance;
						fCurMoveDist = fCurMoveDist*t*t;
					}

					vNextFramePos.x = m_x;
					vNextFramePos.y = m_y;
					vNextFramePos.z = 0;

					fxtoy = tan(fDir);

					{
						{
							fPosXOff = sqrtf(fCurMoveDist*fCurMoveDist/(1+fxtoy*fxtoy));
							fPosYOff = fabs(fxtoy*fPosXOff);
						}

						if( fDir > D3DX_PI*2 )
						{
							fDir -= D3DX_PI*2;
						}

						if( fDir < 0 )
						{
							fDir += D3DX_PI*2;
						}

						if( g_bTheRoleSlipJumping )
						{
							vNextFramePos.x += g_vTheRoleSlipJumpingDir.x*fCurMoveDist;
							vNextFramePos.y += g_vTheRoleSlipJumpingDir.y*fCurMoveDist;
						}
						else
						{
							bool bUnGetFramePos = true;
							if( ( fDir >= 0 && fDir <= D3DX_PI/2 ) || ( fDir >= -D3DX_PI*2 && fDir <= -D3DX_PI*3/2 ) )
							{
								vNextFramePos.x += fPosXOff;
								vNextFramePos.y += fPosYOff;
								bUnGetFramePos = false;
							}

							if( bUnGetFramePos && (( fDir >= D3DX_PI/2 && fDir <= D3DX_PI ) || ( fDir >= -D3DX_PI*3/2 && fDir <= -D3DX_PI )) )
							{
								vNextFramePos.x -= fPosXOff;
								vNextFramePos.y += fPosYOff;
								bUnGetFramePos = false;
							}

							if( bUnGetFramePos && (( fDir >= D3DX_PI && fDir <= D3DX_PI*3/2 ) || ( fDir >= -D3DX_PI && fDir <= -D3DX_PI/2 )) )
							{
								vNextFramePos.x -= fPosXOff;
								vNextFramePos.y -= fPosYOff;
								bUnGetFramePos = false;
							}

							if( bUnGetFramePos && (( fDir >= D3DX_PI*3/2 && fDir <= D3DX_PI*2 ) || ( fDir >= -D3DX_PI/2 && fDir <= 0 )) )
							{
								vNextFramePos.x += fPosXOff;
								vNextFramePos.y -= fPosYOff;
								bUnGetFramePos = false;
							}
						}
					}
				}
			}

			if( g_bTheRoleJumping )
			{
				fDir = atan2f( g_vTheRoleJumpingDir.y - 3, g_vTheRoleJumpingDir.x ) - fRotateX;
			}
			else
			{
				fDir = atan2f( g_vTheRoleTargetDir.y /*- 3*/, g_vTheRoleTargetDir.x ) - fRotateX;
			}

			if( fDir > D3DX_PI )
			{
				fDir = -D3DX_PI*2 + fDir;
			}

			if( fDir < 0 )
			{
				fDir += D3DX_PI*2;
			}

			if( !g_bTheRoleCountermarch )
			{
				SetDir( -fRotateX - D3DX_PI*0.5f );
				SetLowerDir( fDir );				
				//if( ( getwsCamera()->GetLock45DegreeCameraMode() && !g_bTheRoleJumping ) ||
				//	!getwsCamera()->GetLock45DegreeCameraMode() )
				{
					/*if (bSendMoveMessage)
					{
					LOG_MESSAGE(INFO_LOG, LOG_PRIORITY_INFO,"RoleMoveProcess:12208::m_tdir=%f, DirX=%f, DirY=%f, m_bMoving=%d \n", m_tdir, m_vCurDir.x, m_vCurDir.y, m_bMoving);
					}*/
					if(getwsCamera()->GetLock45DegreeCameraMode())
					{

						SetDir(fDir); //lyh++ �����ƶ�ʱ ������aoe������Ч�������
						SetCurDir(fDir); 
						SetUpperDir(fDir);
						SetLowerDir(fDir);
						SetCurUpperDir(fDir);
						SetCurLowerDir(fDir);
					}
				}
			}
			else
			{
				if( fDir < 0 )
				{
					SetLowerDir( fDir + D3DX_PI );
				}
				else
				{
					SetLowerDir( fDir - D3DX_PI );
				}

				SetDir( -fRotateX - D3DX_PI*0.5f );
			}

			if( m_bMounting )
			{
				m_dir = m_tdir;
			}
		}
		else
		{
			if( g_bTheRoleMoveToTargetPos )
			{
				m_bCountermarch = FALSE;
				g_bTheRoleJumpingCountermarch = FALSE;

				// �ж��Ƿ��������Χ
				if( IsRole() && m_nActionTargetID != -1 )
				{
					//////////////////////////////////////////////////////////////////////////
					// �Զ�����
					if( g_nRoleCommonAttackStatus == CAS_NEED_AUTO_ATTACK )
					{
						float fAttackRange = 0;
						bool bChase = false;	// �Ƿ�����׷��
						CPlayer* pTargetPlayer = theApp->GetPlayerMgr()->FindByID( m_nActionTargetID );

						float fXOff, fYOff, fTargetMoveDist = 0;
						bool canAttack = true;
						if( pTargetPlayer )
						{
							// ���㹥��Ŀ���ƶ�����
							fXOff = pTargetPlayer->GetPos().x - g_vTheRoleAttackTargetPos.x;
							fYOff = pTargetPlayer->GetPos().y - g_vTheRoleAttackTargetPos.y;
							fTargetMoveDist = sqrtf( fXOff*fXOff + fYOff*fYOff );

							canAttack = IsInAttackRange(pTargetPlayer->GetPos().x, pTargetPlayer->GetPos().y,
								pTargetPlayer->GetBodyLengthSize(), 0);
						}
						else
						{
							canAttack = IsInAttackRange(g_vTheRoleAttackTargetPos.x, g_vTheRoleAttackTargetPos.y,
								0.5f, 0);
						}


						// ������Χ��
						if( canAttack
							&& ( nPathLength == 0 
							|| (nPathLength > 0 && m_currPathPointIndex == nPathLength -1 ) ))
						{

							//����Ϣ֪ͨ������������������Ŀ��
							MsgAttackLockTarget	msg;

							if( GettheNetworkInput().SendMsg(&msg) == -1 )
							{
							}
							g_nRoleCommonAttackStatus = CAS_ATTACK_AGAIN_WHEN_FAILED;

							//AutoDisMount();
						}
						else if( fTargetMoveDist > 1.f )
						{
							// ���¼���Ŀ��λ��
							theApp->GetPlayerMgr()->MoveRoleToPlayer( pTargetPlayer, FALSE, 0.f, TRUE ,TRUE);
						}
					}
					//////////////////////////////////////////////////////////////////////////
					// ����BUFF
					else if( theApp->GetPlayerMgr()->IsUseSkillBuf() && theApp->GetPlayerMgr()->GetSkillBufPlayerID() >= 0 )
					{
						// ����Buffer
						float fAttackRange = 0;
						bool bChase = false;	// �Ƿ�����׷��
						CPlayer* pTargetPlayer = theApp->GetPlayerMgr()->FindByID( m_nActionTargetID );
						int nCurUseSkillID = theApp->GetPlayerMgr()->GetCurUseSkill();
						int nCurUseSkillLevel = theApp->GetPlayerMgr()->GetCurUseSkillLevel();
						ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( nCurUseSkillID, nCurUseSkillLevel );
						if( !pSkill )
							return;

						float fXOff, fYOff, fTargetMoveDist = 0;
						bool canAttack = true;
						BOOL bClose = false;
						if( pTargetPlayer )
						{
							// ���㹥��Ŀ���ƶ�����
							fXOff = pTargetPlayer->GetPos().x - g_vTheRoleAttackTargetPos.x;
							fYOff = pTargetPlayer->GetPos().y - g_vTheRoleAttackTargetPos.y;
							fTargetMoveDist = sqrtf( fXOff*fXOff + fYOff*fYOff );

							canAttack = IsInAttackRangeOnlyTwoPoint( pTargetPlayer->GetPos().x, pTargetPlayer->GetPos().y, pTargetPlayer->GetBodyLengthSize(), pSkill, true, &bClose );
						}
						else
						{
							canAttack = IsInAttackRangeOnlyTwoPoint( g_vTheRoleAttackTargetPos.x, g_vTheRoleAttackTargetPos.y, 0, pSkill, true, &bClose );
						}


						// ������Χ��
						if( canAttack
							&& ( nPathLength == 0 
							|| (nPathLength > 0 && m_currPathPointIndex == nPathLength -1 ) ))
						{
							// �ǳ���˲�Ƽ��ܣ���ֹͣ�ƶ����ٷż���
							if( !pSkill->bAssaultSkill && pSkill->ustInstantMovingType == IMT_None )
								StopMoving(true);

							if( theApp->GetPlayerMgr()->OnSkill( TRUE, TRUE ) )
							{
								theApp->GetPlayerMgr()->ClearSkillBuf();
							}
						}
						else if( fTargetMoveDist > 1.f )
						{
							// ���¼���Ŀ��λ��
							theApp->GetPlayerMgr()->MoveRoleToPlayer( pTargetPlayer, FALSE, 0.f, TRUE ,TRUE);
						}
					}
					//////////////////////////////////////////////////////////////////////////
					// �������
					else
					{
						CPlayer* pPlayer = NULL;
						if( m_nActionTargetID != -1 )
						{
							pPlayer = theApp->GetPlayerMgr()->FindByID( m_nActionTargetID);
						}
						if (!pPlayer && m_szActionTargetName[0] != '\0')
						{
							pPlayer = theApp->GetPlayerMgr()->FindByName( m_szActionTargetName);
						}
						if( pPlayer == NULL )
						{
							if( g_bAutoPlayInteractionWithTarget )
								g_bAutoPlayInteractionWithTarget = FALSE;

							g_bAutoOpenPrivateShop = FALSE;
						}
						else
						{
							float xSrc = 0;
							float ySrc = 0;
							float xDst = 0;
							float yDst = 0;
							float x = 0;
							float y = 0;
							float Dist = 0;
							float BodyDist = 0;
							float TargetDir = 0;

							xSrc = GetPos().x;
							ySrc = GetPos().y;
							xDst = pPlayer->GetPos().x;
							yDst = pPlayer->GetPos().y;
							//		BodyDist = m_pMe->GetBodySize() + pPlayer->GetBodySize();
							BodyDist = PackagePickDistance;	//ʰȡ����

							x = xDst - xSrc;
							y = yDst - ySrc;
							Dist = sqrtf( x*x + y*y );
							TargetDir = atan2f( y, x );

							//////////////////////////////////////////////////////////////////////////
							// ����
							if (pPlayer->IsItem())
							{
								if( Dist <= BodyDist )
								{
									ClearActionTarget();
									TryPickItem( pPlayer );
								}
							}
							//////////////////////////////////////////////////////////////////////////
							// �ɼ���Ʒ
							else if( pPlayer->IsCollection())
								//|| pPlayer->GetMonsterType() == eMT_Building )
							{
								// �����Զ�Ѱ·�ɼ�
								if (m_szActionTargetName[0] != '\0')
								{
									std::map< GameObjectId, CPlayer* >& playArr = theHeroGame.GetPlayerMgr()->m_mapPlayers;
									std::map<GameObjectId, CPlayer*>::iterator it;
									for( it = playArr.begin(); it != playArr.end(); it++ )
									{
										pPlayer = it->second;
										if( 0 == strcmp( m_szActionTargetName,pPlayer->GetName() ) )
										{
											xDst = pPlayer->GetPos().x;
											yDst = pPlayer->GetPos().y;
											x = xDst - xSrc;
											y = yDst - ySrc;
											Dist = sqrtf( x*x + y*y );
											if( Dist < 2.f )
											{
												SetMoving( FALSE );
												if( HasFightFlag(eFighting) )
												{
													CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotLoot_InFight ) );
												}
												else
												{
													AutoDisMount();

													//--------------------------------------------------------
													// �ɼ�
													if( pPlayer->IsMonsterType(eMT_Mine))
													{
														SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(ItemDefine::eCSI_CaiKuang);
														if( pCharSkill && pCharSkill->bAvailable )
														{
															// ʹ�úͲɼ�����ͬ�ȼ��ļ��ܲɼ�
															int iSkillLevel = pCharSkill->stSkillLevel;
															if( pCharSkill->stSkillLevel > pPlayer->GetLevel() )
																iSkillLevel = pPlayer->GetLevel();
															ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_CaiKuang, iSkillLevel );
															TryUseSkill( pPlayer, pSkill );
														}
													}
													else if( pPlayer->IsMonsterType(eMT_Herb) )
													{
														SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(ItemDefine::eCSI_CaiYao);
														if( pCharSkill && pCharSkill->bAvailable )
														{
															// ʹ�úͲɼ�����ͬ�ȼ��ļ��ܲɼ�
															int iSkillLevel = pCharSkill->stSkillLevel;
															if( pCharSkill->stSkillLevel > pPlayer->GetLevel() )
																iSkillLevel = pPlayer->GetLevel();
															ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_CaiYao, iSkillLevel );
															TryUseSkill( pPlayer, pSkill );
														}
													}
													// ���Ӳ���     added by zhuomeng.hu		[11/9/2010]
													else if( pPlayer->IsMonsterType( eMT_Insect ) )
													{
														SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_BuChong );
														if( pCharSkill && pCharSkill->bAvailable )
														{
															// ʹ�úͲɼ�����ͬ�ȼ��ļ��ܲɼ�
															int iSkillLevel = pCharSkill->stSkillLevel;
															if( pCharSkill->stSkillLevel > pPlayer->GetLevel() )
																iSkillLevel = pPlayer->GetLevel();
															ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_BuChong,
																iSkillLevel );
															TryUseSkill( pPlayer, pSkill );
														}
													}
													else if( pPlayer->IsMonsterType(eMT_Treasure))
													{
														if( thePlayerRole.IsSkillCanUse( ItemDefine::eCSI_Treasure, 1 ) )
														{
															ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_Treasure, 1 );
															TryUseSkill( pPlayer, pSkill );
														}
													}
													// ����
													else if( pPlayer->IsMonsterType(eMT_Mount) )
													{
														if( thePlayerRole.IsSkillCanUse( ItemDefine::eCSI_BuZhuo, 1 ) )
														{
															if( thePlayerRole.HasMountSpace() )
															{
																ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_BuZhuo, 1 );
																TryUseSkill( pPlayer, pSkill );
															}
															else
																CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_MountBag_NotSpace ) );
														}
													}
												}
											}
										}
									}
								}
								else
								{
									if( Dist < 2.f )
									{
										SetMoving( FALSE );
										if( HasFightFlag(eFighting) )
										{
											CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotLoot_InFight ) );
										}
										/* else if( IsMounting() )
										{
										CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotLoot_WhenMounting ) );
										}*/
										else
										{
											// �ɼ�
											theHeroGame.GetPlayerMgr()->DisDrome();
											if( pPlayer->IsMonsterType(eMT_Mine))
											{
												SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(ItemDefine::eCSI_CaiKuang);
												if( pCharSkill && pCharSkill->bAvailable )
												{
													// ʹ�úͲɼ�����ͬ�ȼ��ļ��ܲɼ�
													int iSkillLevel = pCharSkill->stSkillLevel;
													if( pCharSkill->stSkillLevel > pPlayer->GetLevel() )
														iSkillLevel = pPlayer->GetLevel();
													ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_CaiKuang, iSkillLevel );
													TryUseSkill( pPlayer, pSkill );
												}
											}
											else if( pPlayer->IsMonsterType(eMT_Herb) )
											{
												SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(ItemDefine::eCSI_CaiYao);
												if( pCharSkill && pCharSkill->bAvailable )
												{
													// ʹ�úͲɼ�����ͬ�ȼ��ļ��ܲɼ�
													int iSkillLevel = pCharSkill->stSkillLevel;
													if( pCharSkill->stSkillLevel > pPlayer->GetLevel() )
														iSkillLevel = pPlayer->GetLevel();
													ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_CaiYao, iSkillLevel );
													TryUseSkill( pPlayer, pSkill );
												}
											}
											// ���Ӳ���     added by zhuomeng.hu		[11/9/2010]
											else if( pPlayer->IsMonsterType( eMT_Insect ) )
											{
												SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( ItemDefine::eCSI_BuChong );
												if( pCharSkill && pCharSkill->bAvailable )
												{
													// ʹ�úͲɼ�����ͬ�ȼ��ļ��ܲɼ�
													int iSkillLevel = pCharSkill->stSkillLevel;
													if( pCharSkill->stSkillLevel > pPlayer->GetLevel() )
														iSkillLevel = pPlayer->GetLevel();
													ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_BuChong, iSkillLevel );
													TryUseSkill( pPlayer, pSkill );
												}
											}
											else if( pPlayer->IsMonsterType(eMT_Treasure))
											{
												if( thePlayerRole.IsSkillCanUse( ItemDefine::eCSI_Treasure, 1 ) )
												{
													ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_Treasure, 1 );
													TryUseSkill( pPlayer, pSkill );
												}
											}
											// ����
											else if( pPlayer->IsMonsterType(eMT_Mount) )
											{
												if( thePlayerRole.IsSkillCanUse( ItemDefine::eCSI_BuZhuo, 1 ) )
												{
													if( thePlayerRole.HasMountSpace() )
													{
														ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ItemDefine::eCSI_BuZhuo, 1 );
														TryUseSkill( pPlayer, pSkill );
													}
													else
														CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_MountBag_NotSpace ) );
												}
											}
										}
									}
								}
							}
							//////////////////////////////////////////////////////////////////////////
							// �ű�npc
							else if( pPlayer->IsNpc() )
							{
								if( Dist < 4.0f )
								{
									//if(g_bAutoRunForward)
									//	g_bAutoRunForward = FALSE;

									theApp->GetPlayerMgr()->BeginDialog(xDst,yDst);
									const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pPlayer->GetNpcID());
									if( pInfo && pInfo->_nType == eNT_Item )    // NPC��Item���ͣ�����ʾѡ��ͷ��
									{
										// ����Ŀ��ͷ�񣬷���SetLockPlayerIDǰ����
										s_CUI_ID_FRAME_Target.SetPlayer( -1 );
										theApp->GetPlayerMgr()->SetLockPlayerID(pPlayer->GetID());
									}
									else
									{
										theApp->GetPlayerMgr()->SetLockNpc(pPlayer->GetID());
										if( theApp->GetPlayerMgr()->GetMe() )
											theApp->GetPlayerMgr()->GetMe()->StopMoving();
									}
									TryTalkWithNpc( pPlayer );
									ClearActionTarget();
									CPathDirection::Instance()->Reset();
								}
							}
							//////////////////////////////////////////////////////////////////////////

							else if( pPlayer->IsPlayer() )
							{
								// ӵ�����
								if( g_bAutoPlayInteractionWithTarget )
								{
									BOOL bReqHug = FALSE;
									BOOL bTooFar = FALSE;
									BOOL bZTooFar = FALSE;
									if( Dist < 1.5f )
									{
										StopMoving(true);
										thePlayerRole.SendMoveMessage( GetID(), m_x, m_y, m_z, m_vCurDir.x, m_vCurDir.y, g_dwLastFrameBeginTime, 
											false, m_shCurMovingType, m_bLastFrameMoving );
										if( theHeroGame.GetPlayerMgr()->GetMe() &&
											theHeroGame.GetPlayerMgr()->GetMe()->IsCanPlayInteraction(pPlayer, bTooFar, bZTooFar) )
										{
											// ����ӵ����Ϣ
											MsgReqChangeSubAction Req;
											Req.action = CS_SubAction_Embrace;
											Req.targetid = pPlayer->GetID();
											GettheNetworkInput().SendMsg( &Req );

											bReqHug = TRUE;
											g_bAutoPlayInteractionWithTarget = FALSE;
										}
										else if( bZTooFar )
										{
											// ��ʾ����ͬһ�߶�
											g_bAutoPlayInteractionWithTarget = FALSE;
											// 											CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OneAnother,
											//                                                 theXmlString.GetString( eText_CannotEmbrace_ZTooFar ) );
										}
									}
									if( !bReqHug && !bZTooFar )
									{
										float fXOff, fYOff, fTargetMoveDist = 0;
										fXOff = pPlayer->GetPos().x - g_vTheRoleAttackTargetPos.x;
										fYOff = pPlayer->GetPos().y - g_vTheRoleAttackTargetPos.y;
										fTargetMoveDist = sqrtf( fXOff*fXOff + fYOff*fYOff );
										if( fTargetMoveDist > 1.f )
										{
											// ���¼���Ŀ��λ��
											theApp->GetPlayerMgr()->MoveRoleToPlayer( pPlayer, TRUE, 0.f, TRUE ,TRUE);
										}
									}
								}
								// �����ѵ���Ѱ·�Զ��鿴̯λ��     modified by ZhuoMeng.Hu		[12/22/2010]
								else if( g_bAutoOpenPrivateShop )
								{
									if( Dist < 10.f )
									{
										StopMoving(true);
										thePlayerRole.SendMoveMessage( GetID(), m_x, m_y, m_z, m_vCurDir.x, m_vCurDir.y, g_dwLastFrameBeginTime, false, m_shCurMovingType, m_bLastFrameMoving );
										CSystemStallage::Instance()->QuerryPlayerStallageRequest( pPlayer->GetID() );
										g_bAutoOpenPrivateShop = FALSE;
									}
								}                            

							}
						}
					}
				}
			}

			//OutputDebugString( "GotoPos" );
			fCurMoveDist = GetMoveRate()*g_dwSmoothFrame/1000;
			fPosXOff = g_vTheRoleTargetPos.x - vNextFramePos.x;
			fPosYOff = g_vTheRoleTargetPos.y - vNextFramePos.y;
			float fOverallDist = sqrtf( fPosXOff*fPosXOff + fPosYOff*fPosYOff );

			if( fCurMoveDist < fOverallDist )
			{
				fDir = atan2f((g_vTheRoleTargetPos.y - vNextFramePos.y),(g_vTheRoleTargetPos.x - vNextFramePos.x));
				vNextFramePos.x = vNextFramePos.x + fCurMoveDist/fOverallDist*( g_vTheRoleTargetPos.x - vNextFramePos.x );
				vNextFramePos.y = vNextFramePos.y + fCurMoveDist/fOverallDist*( g_vTheRoleTargetPos.y - vNextFramePos.y );


				BOOL bRole = TRUE;
				float fRoleHeight = 80.0f*Config::m_fMdlSpaceScale;
				float fFarWorldZ = 0.0f;
				DWORD dwLoadFlags = 0;
				BOOL  bInFloor = FALSE;
				//commented out by jiayi [09.03.12]
				//fFarWorldZ = GetZByXY( m_z + fRoleHeight, 38.2f*Config::m_fMdlSpaceScale, vNextFramePos.x, vNextFramePos.y, 0, &bInFloor, &dwLoadFlags, bRole );
				fFarWorldZ = GetZByXY( m_z + fRoleHeight,  vNextFramePos.x, vNextFramePos.y, 0, &bInFloor, &dwLoadFlags, bRole );
				float fZOffset = fFarWorldZ - m_z;

				if( fZOffset > 0 )
				{
					//��ɫ�������ռ��е��ƶ��ľ���
					float fSpaceDistance = sqrtf( fCurMoveDist*fCurMoveDist + fZOffset*fZOffset );
					if( fSpaceDistance > 0 && fSpaceDistance > fCurMoveDist)
					{
						float t = fCurMoveDist/fSpaceDistance;
						fCurMoveDist = fCurMoveDist*t*t;
					}

					vNextFramePos.x = m_x;
					vNextFramePos.y = m_y;
					vNextFramePos.z = 0;

					vNextFramePos.x = vNextFramePos.x + fCurMoveDist/fOverallDist*( g_vTheRoleTargetPos.x - vNextFramePos.x );
					vNextFramePos.y = vNextFramePos.y + fCurMoveDist/fOverallDist*( g_vTheRoleTargetPos.y - vNextFramePos.y );
				}

				SetDir(fDir);
				SetLowerDir( fDir );
			}
			else
			{
				vNextFramePos.x = g_vTheRoleTargetPos.x;
				vNextFramePos.y = g_vTheRoleTargetPos.y;
				if (m_currPathPointIndex >= nPathLength)
				{
					if( g_nRoleCommonAttackStatus == CAS_NEED_AUTO_ATTACK && IsRole() )
					{
						//����Ϣ֪ͨ������������������Ŀ��
						MsgAttackLockTarget	msg;

						if( GettheNetworkInput().SendMsg(&msg) == -1 )
						{

						}
					}
					StopMoving(true);
					// �˵������������
					//if( !g_bReturnTheCamera )
					{
						float rotateX = getwsCamera()->GetCameraRotateX()+ getwsCamera()->GetCameraRotateXCorrect();
						getwsCamera()->SetCameraRotateX( fmodf( rotateX, D3DX_PI*2 ) );
						g_fTheRoleRotateZCorrect = getwsCamera()->GetCameraRotateX();
						getwsCamera()->SetCameraRotateXCorrect( 0 );
						g_fTheRoleDirCorrect = 0;
					}
				}
				g_bTheRoleMoveToTargetPos = m_currPathPointIndex < nPathLength;//FALSE;
				m_currPathPointIndex++;
			}
		}

		short shMapPosX = 0;
		short shMapPosY = 0;

		shMapPosX = (vNextFramePos.x-MAPTILESIZE/2)/MAPTILESIZE+1;
		shMapPosY = (vNextFramePos.y-MAPTILESIZE/2)/MAPTILESIZE+1;

		FLOAT fRoleHeight = 80.0f*Config::m_fMdlSpaceScale;
		BOOL bRole = FALSE;

		if( this == theHeroGame.GetPlayerMgr()->GetMe() )
		{
			bRole = TRUE;
		}

		BOOL		bCollision = FALSE;
		DWORD		dwLoadFlags = 0;
		BOOL		bInFloor = FALSE;

		float fWorldZ = 0.f;		
		fWorldZ = GetZByXY( m_z+fRoleHeight, vNextFramePos.x, vNextFramePos.y, 0, 
			&bInFloor, &dwLoadFlags, bRole);


		if( dwLoadFlags == emPT_Unknown)//dwLoadFlags == Me3d_CScene::eUnIntersect_Terrain ) commented out by jiayi [09.03.11]
		{
			OutputDebugString("ǰ��û�е�ͼ,�ȴ�");
			bCollision = TRUE;
		}

		float	fHeadHeight = 1.7f;
		Box* pBBox = GetWorldBBox();
		if( pBBox )
			fHeadHeight = pBBox->v[4].z - pBBox->v[0].z;

		float	fDistToCollision = 0.0f;

		D3DXVECTOR3 vStart;
		D3DXVECTOR3 vDir = D3DXVECTOR3(0,0,0);

		vDir.x = vNextFramePos.x - m_x;
		vDir.y = vNextFramePos.y - m_y;

		D3DXVec3Normalize( &vDir, &vDir );

		vStart.x = GetPos().x;
		vStart.y = GetPos().y;

		if( m_bJumping )
		{
			if( m_bMounting )
			{
				vStart.z = GetPos().z + 40.0f*GetMe3dConfig()->m_fMdlSpaceScale;
			}
			else
			{
				vStart.z = GetPos().z + 10.0f*GetMe3dConfig()->m_fMdlSpaceScale;
			}
		}
		else
		{
			vStart.z = GetPos().z + g_fPlayerCollisionHeight*GetMe3dConfig()->m_fMdlSpaceScale;
		}

		D3DXVECTOR3 vNextStart = D3DXVECTOR3( vNextFramePos.x, vNextFramePos.y, fWorldZ + fHeadHeight );
		if( theHeroGame.GetPlayerMgr()->GetMe() == this )
		{
			BOOL bCheck = theHeroGame.GetPlayerMgr()->CheckViewPlayerBBox(*(Vector*)&vDir,0.35);
			if( bCheck )
			{
				//OutputDebugString( "��ɫ��ײ" );
				bCollision = TRUE;
			}
		}

		if (0)
		{//���ٿ��Ƿ���Ծ��ʱ�����Դ������
			D3DXVECTOR3 vHead = D3DXVECTOR3( 0, 0, 0.1f );
			if( !bCollision )
			{
				if( thePlayerRole.GetDistToCollision( vNextStart, vHead, &fDistToCollision ) )
				{
					if( fDistToCollision > 0 )
					{
						{
							if( fDistToCollision < GetPlayerHeight() )
							{
								bCollision = TRUE;
								if( g_bMouseMoveMode )
								{
									StopMoving();
								}
								OutputDebugString( "����ͷ��???" );
							}
						}
					}
				}
			}
		}

		D3DXVECTOR3 vCollisionDir = D3DXVECTOR3( 0, 0, 0 );
		D3DXVECTOR3 vCollisionNormal = D3DXVECTOR3( 0, 0, 1 );
		float fAngleToCollision = 0;

		if( !getwsCamera()->GetFreeCameraMode() && !bCollision 
			&& (!((abs(vDir.x) < 0.001f) && (abs(vDir.y) < 0.001f)))
			&&thePlayerRole.GetDistToCollision( vStart, vDir, &fDistToCollision, &vCollisionDir, &vCollisionNormal, &fAngleToCollision ) )
		{
			if( fDistToCollision >= 0 )
			{
				if( m_bMounting )
				{
					if( fDistToCollision < 40.0f*GetMe3dConfig()->m_fMdlSpaceScale )
					{
						float f = D3DX_PI*0.5f - fAngleToCollision;
						if( f > 0 )
						{
							fCurMoveDist = fCurMoveDist*f;
						}

						if(  fDistToCollision < 20.0f*GetMe3dConfig()->m_fMdlSpaceScale )
						{
							vCollisionDir = vCollisionNormal;
							D3DXVec3Normalize( &vCollisionDir, &vCollisionDir );
						}

						vNextFramePos.x = m_x + fCurMoveDist*vCollisionDir.x;
						vNextFramePos.y = m_y + fCurMoveDist*vCollisionDir.y;

						vDir.x = vNextFramePos.x - m_x;
						vDir.y = vNextFramePos.y - m_y;

						if((!((abs(vDir.x) < 0.001f) && (abs(vDir.y) < 0.001f)))
							&& thePlayerRole.GetDistToCollision( vStart, vDir, &fDistToCollision, &vCollisionDir, &vCollisionNormal, &fAngleToCollision ) )
						{
							if( fDistToCollision >= 0 )
							{
								if( fDistToCollision < 40.0f*GetMe3dConfig()->m_fMdlSpaceScale )
								{
									bCollision = TRUE;
									if( g_bMouseMoveMode )
									{
										StopMoving();
									}
									OutputDebugString( "�赲����ײ\n" );
								}
								else
								{
									if( fCurMoveDist >= fDistToCollision )
									{
										bCollision = TRUE;
										if( g_bMouseMoveMode )
										{
											StopMoving();
										}
										OutputDebugString( "�赲����ײ\n" );
									}
								}
							}
						}
					}
					else
					{
						if( fCurMoveDist >= fDistToCollision )
						{
							bCollision = TRUE;
							if( g_bMouseMoveMode )
							{
								StopMoving();
							}
						}
					}
				}
				else
				{
					if( fDistToCollision < 20.0f*GetMe3dConfig()->m_fMdlSpaceScale )
					{
						float f = /*D3DX_PI*0.5f -*/ fAngleToCollision;
						if( f > 0 )
						{
							fCurMoveDist = fCurMoveDist*cos(f);
						}

						if(  fDistToCollision < 10.0f*GetMe3dConfig()->m_fMdlSpaceScale )
						{
							vCollisionDir = vCollisionNormal;
							D3DXVec3Normalize( &vCollisionDir, &vCollisionDir );
						}

						vNextFramePos.x = m_x + fCurMoveDist*vCollisionDir.x;
						vNextFramePos.y = m_y + fCurMoveDist*vCollisionDir.y;

						vDir.x = vNextFramePos.x - m_x;
						vDir.y = vNextFramePos.y - m_y;


						if((!((abs(vDir.x) < 0.001f) && (abs(vDir.y) < 0.001f)))
							&&thePlayerRole.GetDistToCollision( vStart, vDir, &fDistToCollision, &vCollisionDir, &vCollisionNormal, &fAngleToCollision ) )
						{
							if( fDistToCollision >= 0.f )
							{
								if( fDistToCollision < 20.0f*GetMe3dConfig()->m_fMdlSpaceScale )
								{
									bCollision = TRUE;

									if( g_bMouseMoveMode )
									{
										StopMoving();
									}
									OutputDebugString( "�赲����ײ\n" );
								}
								else
								{
									if( fCurMoveDist >= fDistToCollision )
									{
										bCollision = TRUE;
										if( g_bMouseMoveMode )
										{
											StopMoving();
										}
										OutputDebugString( "�赲����ײ\n" );
									}
								}
							}
						}
					}
					else
					{
						if( fCurMoveDist >= fDistToCollision )
						{
							bCollision = TRUE;
							if( g_bMouseMoveMode )
							{
								StopMoving();
							}
						}
					}
				}
			}
		}

		if( !bCollision || getwsCamera()->GetFreeCameraMode() )
		{
			float fFarWorldZ = 0.0f;
			DWORD dwLoadFlags = 0;
			BOOL  bInFloor = FALSE;

			float fOffZ = fWorldZ - m_fTerrainZ;

			if( !m_bJumping && !IsInWater() && fOffZ < -38.2f*Config::m_fMdlSpaceScale && !m_bStartZMoving)
			{
				//if( g_dwLastFrameBeginTime > g_dwTheRoleSlipStartTime + 600 )
				{
					g_dwTheRoleSlipStartTime = g_dwLastFrameBeginTime;
					g_bTheRoleSlipJumping = TRUE;
					g_bTheRoleFallJumping = TRUE;
					g_vTheRoleSlipJumpingDir = vDir;
					g_bTheRoleJumping = TRUE;
					g_bTheRoleJumpingCountermarch = g_bTheRoleCountermarch;
					m_bJumping = TRUE;
					g_vTheRoleJumpingDir = vDir;
					g_fTheRoleJumpingRotate = g_fTheRoleRotateZCorrect + g_fTheRoleDirCorrect;
					g_dwTheRoleJumpTime = g_dwLastFrameBeginTime - 1;
					m_fJumpingHeight = 0;
					m_fStartJumpingTerrainZ = m_fTerrainZ;
					m_dwStartJumpingTime = g_dwLastFrameBeginTime + 61;
					bCollision = TRUE;
					m_bNeedDropBuf = FALSE;
					char temp[2048];
					MeSprintf_s(temp,2048,"\n����MyX:%f,MyY:%f,NextX:%f,NextY:%f,		MyZ:%f, NextZ:%f, TerrainZ:%f,bFloor:%d\n",m_x,m_y,vNextFramePos.x, vNextFramePos.y,m_z,fWorldZ,m_fTerrainZ,bInFloor);
					OutputDebugString( temp );
				}
			}
			m_vSaveXYGetZ = fWorldZ;
		}

		if( !bCollision /*|| getwsCamera()->GetFreeCameraMode()*/ )
		{
			if (IsInWater())
			{
				RoleMoveToShore( vNextFramePos, vDir, bCollision, fRoleHeight, fCurMoveDist );
			}
			// 			else
			// 			{//���б�ʴ���һ���Ƕȣ����ж�Ϊ�赲
			// 				D3DXVECTOR3 vAxis ;
			// 				float fFarWorldZ = GetZByXY( m_z + fRoleHeight, vNextFramePos.x, vNextFramePos.y, 0,NULL, NULL, FALSE ,&vAxis);
			// 				D3DXVECTOR3 vUp( 0, 0, 1 );
			// 				D3DXVec3Normalize( &vAxis, &vAxis );
			// 				float fDot = D3DXVec3Dot( &vUp, &vAxis );
			// 				float fTheta = acosf( fDot );
			// 
			// 				if( fTheta > g_fTheRoleSlipJumpingAngle && ( vAxis.x != 0 || vAxis.y != 0 ) )
			// 				{
			// 					bCollision = TRUE;
			// 				}
			// 			}
		}

		static float fLastx = 0;
		static float fLasty = 0;
		float fdx = 0;
		float fdy = 0;
		float fdxtody = 0;//���Ƕ�ת�ɵ�λ����

		if( !bCollision || getwsCamera()->GetFreeCameraMode() )
		{
			if( fLastx != m_x )
			{
				if( g_bTheRoleCountermarch )
				{
					fdx = fLastx - m_x;
				}
				else
				{
					fdx = m_x - fLastx;
				}
				fLastx = m_x;
			}

			if( fLasty != m_y )
			{
				if( g_bTheRoleCountermarch )
				{
					fdy = fLasty - m_y;
				}
				else
				{
					fdy = m_y - fLasty;
				}
				fLasty = m_y;
			}

			fdxtody = sqrtf( fdx*fdx + fdy*fdy );

			fdx = fdx/fdxtody;
			fdy = fdy/fdxtody;

			fdxtody = sqrtf( fdx*fdx + fdy*fdy );

			m_ptLoc.x = shMapPosX;
			m_ptLoc.y = shMapPosY;

			if( g_bTheRoleCountermarch )
			{
				g_vTheRoleCurDir.x = -fdx;
				g_vTheRoleCurDir.y = -fdy;
				g_vTheRoleCurDir.z = 0;
			}
			else
			{
				g_vTheRoleCurDir.x = fdx;
				g_vTheRoleCurDir.y = fdy;
				g_vTheRoleCurDir.z = 0;
			}

			m_x = vNextFramePos.x;
			m_y = vNextFramePos.y;
		}
		else
		{
			if( vNextFramePos.x != m_x )
			{
				if( g_bTheRoleCountermarch )
				{
					fdx = vNextFramePos.x - m_x;
				}
				else
				{
					fdx = vNextFramePos.x - m_x;
				}
			}

			if( vNextFramePos.y != m_y )
			{
				if( g_bTheRoleCountermarch )
				{
					fdy = vNextFramePos.y - m_y;
				}
				else
				{
					fdy = vNextFramePos.y - m_y;
				}
			}

			fdxtody = sqrtf( fdx*fdx + fdy*fdy );

			fdx = fdx/fdxtody;
			fdy = fdy/fdxtody;

			fdxtody = sqrtf( fdx*fdx + fdy*fdy );

			g_vTheRoleCurDir.x = fdx;
			g_vTheRoleCurDir.y = fdy;
			g_vTheRoleCurDir.z = 0;
		}
	}

	if( !m_bMoving )
	{
		m_shCurMovingType = MsgPlayerMoving::eNotMoving;
	}

	if( g_bTheRoleMovingByDir )
	{
		g_vTheRoleTargetPos = GetPos();
		g_vTheRoleTargetPos.z = 0;
		g_bTheRoleMoveToTargetPos = FALSE;
	}

	thePlayerRole.StartMoving( GetID(), g_dwLastFrameBeginTime, m_x, m_y, m_z, m_vCurDir.x, m_vCurDir.y, m_shCurMovingType );
	if( thePlayerRole.CanSendMoveMessage( g_dwLastFrameBeginTime ) )
	{
		if( m_bMoving )
		{
			thePlayerRole.SendMoveMessage( GetID(), m_x, m_y, m_z, m_vCurDir.x, m_vCurDir.y, g_dwLastFrameBeginTime, true, m_shCurMovingType, m_bLastFrameMoving );
		}
		else
		{
			thePlayerRole.SendMoveMessage( GetID(), m_x, m_y, m_z, m_vCurDir.x, m_vCurDir.y, g_dwLastFrameBeginTime, false, m_shCurMovingType, m_bLastFrameMoving );
		}
	}
	unguard;
}

void CPlayer::UnRoleMoveProcess()
{
	guardfunc;
	if( m_bMoving )
	{
		if( IsPlayer() && GetMonsterType() != eMT_IllusionMonster )
		{
			m_bCountermarch = FALSE;

			if( m_shCurMovingType == MsgPlayerMoving::eNotMoving )
			{
				float fDir;
				m_movepath.GetCurPosAndDir( &m_x, &m_y, &fDir, &m_fSpeed, GetMoveRate(), g_dwSmoothFrame );

				float fMovingDirX = m_movepath.GetTargetPos().x - m_x;
				float fMovingDirY = m_movepath.GetTargetPos().y - m_y;
				float fMovingDir = atan2f( fMovingDirY, fMovingDirX );
				float fCurDir = atan2f( m_vDir.y, m_vDir.x );

				// 				SetDir(fCurDir);
				// 				SetLowerDir(fCurDir);
				// 				SetUpperDir(fCurDir);

				int nMovingType = GetMovingType( m_tdir, fMovingDir );

				if( nMovingType == MsgPlayerMoving::eMovingCountermarch ||
					nMovingType == MsgPlayerMoving::eMovingCountermarchLeft ||
					nMovingType == MsgPlayerMoving::eMovingCountermarchRight )
				{
					m_bCountermarch = TRUE;
				}
			}

			if( m_shCurMovingType == MsgPlayerMoving::eMovingForward )
			{
				m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate, g_dwSmoothFrame );
			}

			if( m_shCurMovingType == MsgPlayerMoving::eMovingCountermarch )
			{
				m_bCountermarch = TRUE;
				if( m_bJumping )
					m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate, g_dwSmoothFrame );
				else
					m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate*0.5f, g_dwSmoothFrame );
			}

			if( m_shCurMovingType == MsgPlayerMoving::eMovingLeft )
			{
				m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate, g_dwSmoothFrame );

				SetLowerDir( m_dir - D3DX_PI/2 );
			}

			if( m_shCurMovingType == MsgPlayerMoving::eMovingRight )
			{
				m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate, g_dwSmoothFrame );

				SetLowerDir( m_dir + D3DX_PI/2 );
			}

			if( m_shCurMovingType == MsgPlayerMoving::eMovingForwardLeft )
			{
				m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate, g_dwSmoothFrame );

				SetLowerDir( m_dir - D3DX_PI/4 );
			}

			if( m_shCurMovingType == MsgPlayerMoving::eMovingForwardRight )
			{
				m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate, g_dwSmoothFrame );
				SetLowerDir( m_dir + D3DX_PI/4 );
			}

			if( m_shCurMovingType == MsgPlayerMoving::eMovingCountermarchLeft )
			{
				m_bCountermarch = TRUE;
				if( m_bJumping )
					m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate, g_dwSmoothFrame );
				else
					m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate*0.5f, g_dwSmoothFrame );

				SetLowerDir( m_dir + D3DX_PI/4 );
			}

			if( m_shCurMovingType == MsgPlayerMoving::eMovingCountermarchRight )
			{
				m_bCountermarch = TRUE;
				if( m_bJumping )
					m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate, g_dwSmoothFrame );
				else
					m_movepath.GetPlayerCurPos( &m_x, &m_y, m_fMoveRate*0.5f, g_dwSmoothFrame );

				SetLowerDir( m_dir - D3DX_PI/4 );
			}

			if(m_movepath.IsMoveOver())
			{
				/*float fCurDir = atan2f( m_vDir.y, m_vDir.x );
				D3DXVECTOR3 vTargetDir;
				if( m_movepath.HasTargetDir(vTargetDir) )
				{
				fCurDir = atan2f( vTargetDir.y, vTargetDir.x );
				m_vDir = vTargetDir;
				m_movepath.ClearTargetDir();
				}

				SetDir(fCurDir);
				SetLowerDir(fCurDir);*/
				StopMoving(true);
			}
		}
		else
		{
			if( m_movepath.NeedClosingToLockTarget() )
			{
				CPlayer* pLockTarget = theHeroGame.GetPlayerMgr()->FindByID( m_movepath.GetLockTargetID() );
				if( pLockTarget )
				{
					m_movepath.UpdateLockTargetPos( pLockTarget->GetPos() );
				}
				else
				{
					m_movepath.SetMoveOver();
				}
			}

			float fDir = 0;
			m_movepath.GetCurPosAndDir( &m_x, &m_y, &fDir, &m_fSpeed, GetMoveRate(), g_dwSmoothFrame );

			if( m_movepath.IsNeedChangeDir() )
			{
				SetDir(fDir);
				SetLowerDir(fDir);
			}

			if( m_movepath.IsMoveOver() )
			{
				float fCurDir = atan2f( m_vDir.y, m_vDir.x );
				SetDir(fCurDir);
				SetLowerDir(fCurDir);
				SetUpperDir(fCurDir);
				StopMoving(true);
				SwitchIdleAnim();
				

			}
		}
	}
	else
	{
		if(m_movepath.IsMoveOver())
		{
			float fCurDir = atan2f( m_vDir.y, m_vDir.x );
			D3DXVECTOR3 vTargetDir;
			if( m_movepath.HasTargetDir(vTargetDir) )
			{
				fCurDir = atan2f( vTargetDir.y, vTargetDir.x );
				m_vDir = vTargetDir;
				m_movepath.ClearTargetDir();
				SetDir(fCurDir);
				SetLowerDir(fCurDir);
				//StopMoving(true);
			}

		}
	}
	m_ptLoc.x = (m_x-MAPTILESIZE/2)/MAPTILESIZE+1;
	m_ptLoc.y = (m_y-MAPTILESIZE/2)/MAPTILESIZE+1;

	if( IsMonster() && !m_bMoving )
	{
		if( m_movepath.HaveLockTarget() )
		{
			CPlayer* pLockTarget = theHeroGame.GetPlayerMgr()->FindByID( m_movepath.GetLockTargetID() );
			if( pLockTarget )
			{
				float fDir = atan2f(pLockTarget->GetPos().y - m_y, pLockTarget->GetPos().x - m_x);
				if( GetMonsterType() != eMT_Building )
				{
					SetDir(fDir);
				}
			}
			else
			{
				m_movepath.LostLockTarget();
			}
		}
	}

	if( !IsRole() && m_bMoving )
	{
		if( !m_bRunning )
		{
			if( !m_bJumping )
			{
				if( IsInWater() )
				{
					SwitchSwimAnim();
				}
				else
				{
					if( IsMonster() )
					{
						SwitchRunAnim();
					}
					else
					{
						if( GetAnim() && GetAnim()->GetCurAnimType() != MoreActionClient::yongbao )
							SwitchRunAnim();
						m_bPlayedCoutermarchAnim = FALSE;
					}
				}
			}
			m_bRunning = TRUE;
		}

		if( IsPlayer() && m_bCountermarch )
		{
			if( !m_bPlayedCoutermarchAnim )
			{
				if( GetAnim() && GetAnim()->GetCurAnimType() != MoreActionClient::yongbao )
					SwitchWalkBackWardsAnim();
				m_bPlayedCoutermarchAnim = TRUE;
			}
		}
		else
		{
			if( m_bPlayedCoutermarchAnim )
			{
				if( GetAnim() 
					&& !GetAnim()->IsCurrAnimHideWeapon()
					)
					SwitchRunAnim();
				m_bPlayedCoutermarchAnim = FALSE;
			}
		}
	}
	unguard;
}

void	CPlayer::SpecialIdleTimeProcess()
{
	guardfunc;
	if ( !m_bInWater )
	{
		if ( !IsMoving() && !IsCanOverIntonation() )
		{
			if ( m_bLastFrameMoving != m_bMoving )
				m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

			if ( m_dwStartStopMovingTime <= 0 )
				m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

			DWORD dwStopMovingTimeDiff = g_dwLastFrameBeginTime - m_dwStartStopMovingTime;
			if (!IsMounting() && dwStopMovingTimeDiff > m_dwSpecialIdleInterval)
			{
				if ( IsMonster() )	// ����Monster�ᾭ���߶�, ���д�����Ϊ6~20�벥һ��
				{
					m_dwSpecialIdleInterval = (rand() / (float) RAND_MAX) * 14000 + 6000;
				}
				else if ( IsNpc() )	// NPC���д�����Ϊ5~25�벥һ��
				{
					m_dwSpecialIdleInterval = (rand() / (float) RAND_MAX) * 20000 + 5000;
				}
				else  // ��ɫ 30~60�벥һ��
				{
					m_dwSpecialIdleInterval = (rand() / (float) RAND_MAX) * 30000 + 30000;
				}

				if ( !IsRole() )
					SwitchSpecialIdleAnim(0);
				else
				{
					SwitchSpecialIdleAnim(0);
				}
				m_dwStartStopMovingTime = g_dwLastFrameBeginTime;
			}
		}
	}
	unguard;
}

void	CPlayer::MoveStatusChangedProcess()
{
	guardfunc;
	if( m_bLastFrameMoving != m_bMoving )
	{
		if( m_bMoving )
		{
			if( IsRole() )
			{
				if( g_bTheRoleCountermarch )
				{
					if( IsInWater() )
					{
						SwitchSwimIdleAnim(0);
					}
					else
					{
						SwitchWalkBackWardsAnim(0);
					}
					m_bRunning = TRUE;
				}
				else
				{
					if( IsInWater() )
					{
						SwitchSwimAnim();
					}
					else
					{
						SwitchRunAnim();
					}
					m_bRunning = FALSE;
				}
			}
			else
			{
				if( !m_bJumping )
				{
					if( IsInWater() )
					{
						SwitchSwimAnim();
					}
					else
					{
						if( IsMonster() )
						{
							SwitchRunAnim();
						}
						// ���������ӵ�����ɼ��������¶������򲻲��ܲ�
						else if( GetAnim()
							&& !GetAnim()->IsCurrAnimHideWeapon()
							&& GetAnim()->GetCurAnimType() != MoreActionClient::Sit
							&& GetAnim()->GetCurAnimType() != MoreActionClient::SitLoop 
							&& GetAnim()->GetCurAnimType() != MoreActionClient::loot)
						{
							SwitchRunAnim();
							m_bPlayedCoutermarchAnim = FALSE;
						}
					}
				}
			}
		}
		else
		{
			if( m_status.CurStatus() == CPlayerStatus::esk_ReadyToUseSpecialSkill ||
				m_status.CurStatus() == CPlayerStatus::esk_UseSpecialSkill )
			{

			}
			else
			{
				if( !m_bJumping )
				{
					if( IsInWater() )
					{
						SwitchSwimIdleAnim(0);
					}
					else
					{
						if( m_bRole )
							SwitchIdleAnim(0);
						// ���������ӵ�����ɼ��������¶������򲻲�idle
						else if( IsPlayer() )
						{
							if( GetAnim()
								&& !GetAnim()->IsCurrAnimHideWeapon()
								&& GetAnim()->GetCurAnimType() != MoreActionClient::Sit
								&& GetAnim()->GetCurAnimType() != MoreActionClient::SitLoop
								&& GetAnim()->GetCurAnimType() != MoreActionClient::loot)
								SwitchIdleAnim(0);
						}
						else
							SwitchIdleAnim(0);
					}
				}
			}
		}
	}
	m_bLastFrameMoving = m_bMoving;
	if( m_bRole )
	{
		if( m_bLastFrameMoving )
			g_bLastFrameMovebyDir = g_bTheRoleMovingByDir;
		else
			g_bLastFrameMovebyDir = FALSE;
	}
	unguard;
}

void CPlayer::SetUncontrolMoving( bool bUncontrolMoving ,bool isFly )
{
	guardfunc;
	m_bUncontrolMoving = bUncontrolMoving;
	m_bUncontrolFlying = isFly;
	unguard;
}

void CPlayer::SetUncontrolMoveTargetPos( D3DXVECTOR3 vTargetPos )
{
	guardfunc;
	//m_bUncontrolMoving = true;
	m_vUncontrolMoveTargetPos = vTargetPos;
	unguard;
}

D3DXVECTOR3 CPlayer::GetUncontrolMoveTargetPos()
{
	guardfunc;
	return m_vUncontrolMoveTargetPos;
	unguard;
}

bool CPlayer::IsUncontrolMoving()
{
	guardfunc;
	return m_bUncontrolMoving;
	unguard;
}

bool CPlayer::IsUnControlState()
{
	if (m_bUncontrolMoving || m_bUncontrolFlying)
	{
		return true;
	}

	return false;
}

bool CPlayer::IsCanDisMount()
{
	if (m_bUncontrolMoving || m_bUncontrolFlying)
	{
		return false;
	}

	return true;
}

//  �ƶ�״̬
void    CPlayer::ActionStatusMove(void)
{
	guardfunc;

	if( m_bRole && IsDead() )
	{
		return;
	}

	DWORD dwEffect = 0;
	dwEffect |= eTemporalBlur;
	if( m_bAssaultMoving )
	{
		AssaultMoving( m_shAssaultTargetID );

		if( theHeroGame.GetPlayerMgr()->GetMe() != this )
			return;

		if( m_bAssaultMoving ) // ��û�е���Ŀ��
			return;

		// �����Զ����� [12/8/2010 zhangjiayi]
		if( TryInstantSkill( m_pInstantSkill ) )
			m_pInstantSkill = 0;

		return;
	}

	if( m_bInstantMoving )
	{
		if( m_bRole )
		{
			ItemDefine::SItemSkill* pInstantSkill = m_pInstantSkill;
			InstantMoving( m_vInstantTargetPos, m_eInstantMovingType != IMT_TargetBack );

			if (m_eInstantMovingType == IMT_Backwards)
			{
				float fDir;
				GetDir(&fDir);
				SetDir(fDir + D3DX_PI);
			}
			else if (m_eInstantMovingType == IMT_TargetBack)
			{
				SetDir(m_fInstantMovingDir);
				SetLowerDir(m_fInstantMovingDir);
				SetCurDir(m_fInstantMovingDir);
				SetCurLowerDir(m_fInstantMovingDir);

				getwsCamera()->SetCameraRotateX( -m_fInstantMovingDir - D3DX_PI*0.5f );
			}
			if( theHeroGame.GetPlayerMgr()->GetMe() != this )
				return;

			// �����Զ����� [12/8/2010 zhangjiayi]
			TryInstantSkill( pInstantSkill );


			return;
		}
		else
		{
			D3DXVECTOR2 v(m_x, m_y);
			v = v - D3DXVECTOR2(m_movepath.GetTargetPos().x, m_movepath.GetTargetPos().y);
			float l = D3DXVec2Length(&v);

			if (l > 2.0f)
			{
				m_movepath.GetPlayerCurPos(&m_x, &m_y, GetMoveRate() + 1000.f, g_dwSmoothFrame);
				SetInstantMoving( false, NULL );

				return;
			}

			if (HQ_TimeGetTime() - m_dwInstantMovingStartTime > 2000)
				SetInstantMoving( false, NULL );
		}

	}

	if(IsCarrierint())
	{
		SetMoving(FALSE);
		SetInWater(FALSE);
		//SwitchIdleAnim();
		//SwitchSitLoopAnim(0xFFFFFFFF);
	}
	else if( m_bRole )
	{
		if( m_pAnim && m_pAnim->IsUpperBodyPlayingComAnim() )
		{
			return;
		}

		if( IsUncontrolMoving() )
		{
			UncontrolMoving( GetUncontrolMoveTargetPos(), FALSE );
		}
		else
		{
			if( false/*m_bIsCurRandRun != (BOOL)m_cFightStatus.IsUnControlRandRun()*/ )
			{
				if( m_bIsCurRandRun )   // ���RandRun״̬���º���FALSE������֮ǰ��RandRun��TRUE����ֹͣ
				{
					StopMoving();
				}
				m_bIsCurRandRun = false;//m_cFightStatus.IsUnControlRandRun();
			}

			if (false/*m_cFightStatus.IsUnControlRandRun()*/)
			{
				DWORD dwcurtime = HQ_TimeGetTime();
				if (dwcurtime - m_startfeartime >= 3000)
				{
					m_vTargetPos = GetPos();
					int randnum = rand();
					int randnum1 = rand();
					if (randnum%2 == 0)
					{
						m_vTargetPos.x += randnum%50;
						m_vTargetPos.y += randnum1%50;
					}
					else
					{
						m_vTargetPos.x -= randnum%50;
						m_vTargetPos.y -= randnum1%50;
					}
					m_startfeartime = dwcurtime;
					if (m_vTargetPos.x < 0)
					{
						m_vTargetPos.x = 0;
					}
					if (m_vTargetPos.y < 0)
					{
						m_vTargetPos.y  = 0;
					}
				}
				if( m_vTargetPos != D3DXVECTOR3(m_x, m_y, m_z) )
				{
					BOOL bCanMove = UncontrolMoving(m_vTargetPos, TRUE);
					if( !bCanMove )
					{
						m_vTargetPos = D3DXVECTOR3(m_x, m_y, m_z);
					}
				}
			}
			else
			{
				RoleMoveProcess();
			}
		}

		thePlayerRole.CheckFight();
	}
	else
	{
		if( IsUncontrolMoving() )
		{
			UncontrolMoving( GetUncontrolMoveTargetPos(), FALSE );
		}
		else
		{
			UnRoleMoveProcess();
		}
	}

	MoveStatusChangedProcess();
	unguard;
}

//  �л�����Ҫ״̬�Ķ���
void    CPlayer::SwitchAnim(CPlayerStatus::STATUS_KEY PreStatus, DWORD dwTimeOut)
{
	guardfunc;
	if( Object_Effect == GetCharType() )
	{
		if( !m_pAnim )
			return;
		////��ʱ����ʾ����Ч��
		//m_pAnim->PlayAnim2( 
		//	MoreActionClient::MagicRun, 
		//	MexAnimCtrl::eNormalPlay, 
		//	0,
		//	1000, 
		//	dwTimeOut, 
		//	MoreActionClient::MagicRun, 
		//	MexAnimCtrl::eNormalPlay );
		return;
	}

	BOOL bRoleSit = FALSE;
	BOOL bChangeStatus = FALSE;
	if (GetSitStatus() && IsRole())
	{
		bRoleSit = TRUE;
	}

	switch (m_status.CurStatus())
	{
	case CPlayerStatus::esk_Attack:         // ����״̬
		SwitchAttackAnim(dwTimeOut);
		if( m_bRole )
		{
			SAttackInfo* pAttackInfo = GetAttackInfo();
			if( pAttackInfo )
			{
				ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(pAttackInfo->iSkill, pAttackInfo->iSkillLevel);
				if( pSkill && !pSkill->bContinueAtt )
				{
					g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
				}
			}
			if( g_nRoleCommonAttackStatus != CAS_NOT_ATTACK )
			{
				if( theHeroGame.GetPlayerMgr()->GetLockPlayerID() != -1 && g_nRoleCommonAttackStatus != CAS_ATTACKING)
				{
					CPlayer* pTagPlayer = theHeroGame.GetPlayerMgr()->FindByID(theHeroGame.GetPlayerMgr()->GetLockPlayerID());
					if( pTagPlayer )
					{
						bool canAttack = IsInAttackRange(pTagPlayer->GetPos().x, pTagPlayer->GetPos().y,
							pTagPlayer->GetBodyLengthSize(), 0);

						if( canAttack )
						{
							//����Ϣ֪ͨ������������������Ŀ��
							MsgAttackLockTarget	msg;

							if( GettheNetworkInput().SendMsg(&msg) == -1 )
							{

							}
							g_nRoleCommonAttackStatus = CAS_ATTACK_AGAIN_WHEN_FAILED;
						}
					}
				}
			}
		}
		bChangeStatus = TRUE;
		break;
	case CPlayerStatus::esk_HoldSkill:
		SwitchHoldSkillAnim( dwTimeOut );
		bChangeStatus = TRUE;
		break;
	case CPlayerStatus::esk_Scabbard:
		SwitchScabbardAnim();
		bChangeStatus = TRUE;
		break;
	case CPlayerStatus::esk_ActionTime://��һ��ʱ������Ī������
		SwitchActionAnim(dwTimeOut);
		bChangeStatus = TRUE;
		//
		break;
	case CPlayerStatus::esk_Idle:           // ����״̬�����κβ������ȴ�ָ�
		if( (!bRoleSit && !m_bMoving && !m_bJumping) || (m_bMoving&&!m_bCanInterruptIntonating) )
		{
			if(!m_bCanInterruptIntonating)
			{
				if(m_pAnim&&m_pAnim->IsUpperBodyAndLowerBodyMode() )
					m_pAnim->ForceUpperAnimPlayOver();
			}
			if( IsInWater() )
				SwitchSwimIdleAnim();
			else
				SwitchIdleAnim();
		}
		break;
	case CPlayerStatus::esk_Revive:
		{
			SwitchReliveAnim();
		}
		break;
	}
	if( bRoleSit && bChangeStatus )
	{
		// ����״̬�����
		SetSitInterrupt(1);
		// ����վ��״̬��������
		theApp->GetPlayerMgr()->ProcessCommand("DoSitDown");
	}
	unguard;
}

//bool CPlayer::IsHaveLHardWeapon( )
//{
//	guardfunc;
//    return thePlayerRole.m_charinfo.visual.GetAttriSuitArray()[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandItemPartMask )].itembaseinfo.ustItemID != 0xFFFF;
//	unguard;
//}

//add by yanli 2010-9-27
//BOOL CPlayer::IsHaveShield()
//{
//	guardfunc;
//    return thePlayerRole.m_charinfo.visual.GetAttriSuitArray()[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandShieldPartMask )].itembaseinfo.ustItemID != 0xFFFF;
//	unguard;
//}

//add by yanli  2010-9-27
BOOL CPlayer::IsDoubleHandWeapon()
{
	return FALSE;
}

//BOOL CPlayer::IsDoubleHandWeapon()
//{
//	guardfunc;
//    UINT nId = thePlayerRole.m_charinfo.visual.GetAttriSuitArray()[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask )].itembaseinfo.ustItemID;
//	if( nId == InvalidLogicNumber )
//		return FALSE;
//
//	return FALSE;
//	unguard;
//}

//�л����ε����յ�����
void CPlayer::SwitchScabbardAnim( DWORD dwTimeOut, BOOL bPlayScabbard/*= TRUE*/ )
{
	guardfunc;
	if( !m_pAnim || IsDead() || IsJumping() || (GetSitStatus() && !GetSitInterrupt()) || IsCanOverIntonation())
	{
		return;
	}

	int iScabbardId = 0;
	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	if( !IsHaveWeapon() )
	{
		if( !m_bMoving )
		{
			SwitchIdleAnim();
		}
		else
		{
			SwitchRunAnim();
		}
		return;
	}

	{
		// �������ս����̬�ж���
		if( !IsFightPose() )
		{
			// ȥ��ս����̬���յ�
			if( !m_bMoving )
				iScabbardId = GetPlayerActionID(MoreAction::Action_single_draw );
			else
				iScabbardId = MoreActionClient::single_run_draw;
		}
		else
		{
			// ����ս����̬�󣬰ε�
			if( !m_bMoving )
				iScabbardId = GetPlayerActionID(MoreAction::Action_single_scabbard );
			else
				iScabbardId = MoreActionClient::single_run_scabbard;
		}

		if (NULL != m_pAnim && bPlayScabbard)
		{
			m_pAnim->PlayUpperAnim( iScabbardId,
				MexAnimCtrl::eNormalPlay, 
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime );
			m_dwLastScabbardBeginTime = HQ_TimeGetTime();
		}
	}

	if( !m_bMoving )
	{
		if (!m_bIntonating && m_bRole)
		{
			SwitchIdleAnim();
		}
		
	}
	else if( m_bCountermarch )
	{
		SwitchWalkBackWardsAnim();
	}
	else if( m_bJumping )
	{
		SwitchJumpAnim();
	}
	else
	{
		SwitchRunAnim();
	}
	unguard;
}

//�л���sit�Ķ���
void CPlayer::SwitchSitLoopAnim( DWORD dwTimeOut )
{
	if( m_bMounting || m_bJumping || m_bInWater )
		return;
	if( !m_pAnim )
	{
#ifdef NEW_PLAYER_LOAD
		if( IsPlayer() )
			SetSitStatus(1);
#endif
		return;
	}


	SetSitStatus(1);	// ��������
	/*if( IsHaveWeapon() )
	{
	SetShowWeapon(FALSE);
	}
	*/

	int sitloop_id = MoreActionClient::SitLoop;

	if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
	{
		m_pAnim->PlayLowerAnim(	sitloop_id,
			MexAnimCtrl::eNormalPlay,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			sitloop_id,
			MexAnimCtrl::eDefaultBlendingTime,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			0 );
	}
	else
	{
		m_pAnim->PlayAnim2( sitloop_id,
			MexAnimCtrl::eNormalPlay,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			sitloop_id,
			MexAnimCtrl::eDefaultBlendingTime );
	}
}

//�л���sit�Ķ���
void CPlayer::SwitchSitAnim( DWORD dwTimeOut )
{
	if( m_bMounting || m_bJumping || m_bInWater )
	{
		return;
	}
	if( !m_pAnim )
	{
#ifdef NEW_PLAYER_LOAD
		if( IsPlayer() )
			SetSitStatus(1);	// ��������״̬
#endif
		return;
	}

	int sit_id = MoreActionClient::Sit;
	int sitloop_id = MoreActionClient::SitLoop;

	if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
	{
		m_pAnim->PlayLowerAnim(	sit_id,
			MexAnimCtrl::eNormalPlay,
			0,
			1,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			sitloop_id,
			MexAnimCtrl::eNormalPlay,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			0 
			);
		// ���ݲ߻�Ҫ����Ϣʱ����������
		/*if( IsHaveWeapon() )
		{
		SetShowWeapon(FALSE);
		}*/
	}
	else
	{
		m_pAnim->PlayAnim2( sit_id,
			MexAnimCtrl::eNormalPlay,
			0,
			1,
			MexAnimCtrl::eMaxTimeout,
			sitloop_id,
			MexAnimCtrl::eNormalPlay
			);
	}
}

//�л��������Ķ���
void CPlayer::SwitchDieAnim( DWORD dwTimeOut )
{
	guardfunc;
	if( GetHp() > 0 )
	{
		OutputDebugString("���ܸ�HP����0��Player������������");
		return;
	}
	// �߼������ᵽǰ��
	if( m_bRole )
	{
		if( m_bMounting )
		{
			theApp->GetPlayerMgr()->DisDrome();
			DisMount( FALSE );
		}

		if( IsUncontrolMoving() )
		{
			theApp->GetPlayerMgr()->DisHitch();
		}

		StopMoving();
	}

	if( !m_pAnim )
	{
		return;
	}


	int dead_id;
	dead_id = MoreActionClient::Dead;

	if( !IsMonster() )
	{
		if( IsHaveWeapon() )		//if����������.
		{
			dead_id = MoreActionClient::single_dead;
		}
		if( IsDoubleHandWeapon() )
		{
			dead_id = MoreActionClient::double_dead;
		}
	}

	if( m_pAnim->IsUpperBodyAndLowerBodyMode() ) 
	{
		PlayCreatureSound( CCreatureSound::CreatureSound_Dead );

		m_pAnim->PlayLowerAnim(	dead_id,
			MexAnimCtrl::eNormalPlay,
			0,
			1,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			dead_id,
			MexAnimCtrl::eHoldOnLastFrame,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			0 );
	}
	else
	{
		PlayCreatureSound( CCreatureSound::CreatureSound_Dead );

		m_pAnim->PlayAnim2( dead_id,
			MexAnimCtrl::eNormalPlay,
			0,
			1,
			MexAnimCtrl::eMaxTimeout,
			dead_id,
			MexAnimCtrl::eHoldOnLastFrame );
	}

	//
	if(IsMorph()&&m_pMorphAnim)
	{
		if(m_pMorphAnim->IsUpperBodyAndLowerBodyMode())
		{
			m_pMorphAnim->PlayLowerAnim(MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				dead_id,
				MexAnimCtrl::eHoldOnLastFrame,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				0);
		}
		else
		{
			m_pMorphAnim->PlayAnim2( dead_id,
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				dead_id,
				MexAnimCtrl::eHoldOnLastFrame );
		}
	}

	unguard;
}

//�л����������������
void CPlayer::SwitchDieOverAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	if( !m_pAnim )
	{
		return;
	}

	int dead_id = MoreActionClient::Dead;

	if( !IsMonster() )
	{
		if( IsHaveWeapon() )		//if����������.
		{
			dead_id = MoreActionClient::single_dead;
		}

		if( IsDoubleHandWeapon() )
		{
			dead_id = MoreActionClient::double_dead;
		}
	}

	if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
	{
		m_pAnim->PlayLowerAnim(	dead_id,
			MexAnimCtrl::eHoldOnLastFrame,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			0,
			dead_id,
			MexAnimCtrl::eHoldOnLastFrame,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			0 );
	}
	else
	{
		m_pAnim->PlayAnim2( dead_id,
			MexAnimCtrl::eHoldOnLastFrame,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			dead_id,
			MexAnimCtrl::eHoldOnLastFrame );
	}

	if(IsMorph()&&m_pMorphAnim)
	{
		if(m_pMorphAnim->IsUpperBodyAndLowerBodyMode())
		{
			m_pMorphAnim->PlayLowerAnim(	dead_id,
				MexAnimCtrl::eHoldOnLastFrame,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				0,
				dead_id,
				MexAnimCtrl::eHoldOnLastFrame,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				0 );
		}
		else
		{
			m_pMorphAnim->PlayAnim2( dead_id,
				MexAnimCtrl::eHoldOnLastFrame,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				dead_id,
				MexAnimCtrl::eHoldOnLastFrame );
		}
	}
	unguard;
}

//�л�����Ī���罻����
void CPlayer::SwitchActionAnim(DWORD dwTimeOut)
{
	guardfunc;
	if( !m_pAnim )
		return;

	int action_id, facet_action_id, idle_id;
	DWORD dwLastTime,dwOneTime;
	DWORD dwPlayTimes;
	int last_frame_type;
	//�����罻�����ı�񣬲��Ŷ�Ӧ�Ķ���
	ExpressionInfo *pExpressionInfo = (ExpressionInfo*)m_NowAction.sData;
	//
	ItemDefine::SItemAction* pItem = (ItemDefine::SItemAction *)GettheItemDetail().GetItemByID(pExpressionInfo->iActionID);
	//
	if (NULL != pItem)
	{
		action_id = pItem->ustActionID;
		facet_action_id = GetPlayerActionID(action_id);
		idle_id = GetPlayerActionID(MoreAction::Action_idle);
		dwLastTime = pItem->stLastingPlayTime;
		dwOneTime = pItem->stSinglePlayTime;
		if (dwOneTime <= 0)
			dwOneTime = 1;
		if (pItem->bLastFrameRemain)
		{
			dwPlayTimes = 1;
			last_frame_type = MexAnimCtrl::eHoldOnLastFrame;
			//
			idle_id = facet_action_id;
		}
		else
		{
			dwPlayTimes = 1 + dwLastTime / dwOneTime;
			last_frame_type = MexAnimCtrl::eNormalPlay;
		}
		//
		//
		m_pAnim->PlayAnim2( 
			facet_action_id, 
			MexAnimCtrl::eNormalPlay,
			0,
			dwPlayTimes, 
			dwLastTime, 
			idle_id, 
			last_frame_type);
	}
	//
	unguard;
}

//�л������߶���
void CPlayer::SwitchWalkAnim(DWORD dwTimeOut)
{
	guardfunc;

	if( m_bRole )
	{
		if( g_bTheRoleJumping || m_bDead )
		{
			return;
		}
	}
	else
	{
		if( m_bDead )
		{
			return;
		}
	}
	// �����ƶ��ٶ�
	m_fCurMoveRate = GetMoveRate();

	if( !m_pAnim )
		return;

	DWORD dwOneLoopTime = 0;
	dwOneLoopTime = (m_fMovingStep/m_fCurMoveRate)*1000;
	int nRunActionId = MoreActionClient::Walk;

	if ( !IsRole() )
	{
		if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
		{
			m_pAnim->PlayLowerAnim(	"walk",
				MexAnimCtrl::eNormalPlay,
				dwOneLoopTime,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				"idle",
				MexAnimCtrl::eNormalPlay );
		}
		else
		{
			m_pAnim->PlayAnim2(	MoreActionClient::Walk,
				MexAnimCtrl::eNormalPlay,
				dwOneLoopTime,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MoreActionClient::Walk,
				MexAnimCtrl::eNormalPlay );
		}
	}
	else
	{
		if( m_bMounting )
		{
			char pszWalkName[MAX_PATH] = {0};
			ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
			if( pDrome )
				strcpy(pszWalkName, pDrome->GetMountAction( ItemDefine::MountWalk ));
			else
				strcpy(pszWalkName, "mountwalk");

			if( IsHaveWeapon() )
			{
				char szTemp[MAX_PATH] = {0};
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1 ,"single_%s", pszWalkName);
				strcpy(pszWalkName, szTemp);
			}

			m_pAnim->PlayLowerAnim(	pszWalkName,
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				pszWalkName,
				MexAnimCtrl::eNormalPlay );

			if( m_pMountAnim )
			{
				if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
				{
					m_pMountAnim->PlayLowerAnim( "walk",
						MexAnimCtrl::eNormalPlay,
						dwOneLoopTime,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
				else
				{
					m_pMountAnim->PlayAnimByActionName( "walk",
						MexAnimCtrl::eNormalPlay,
						dwOneLoopTime,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
			}
		}
		else
		{
			if( IsHaveWeapon() )
			{
				m_pAnim->PlayLowerAnim(	"single_walk",
					MexAnimCtrl::eNormalPlay,
					dwOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					"single_idle",
					MexAnimCtrl::eNormalPlay );
			}
			else
			{
				m_pAnim->PlayLowerAnim(	"walk",
					MexAnimCtrl::eNormalPlay,
					dwOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					"idle",
					MexAnimCtrl::eNormalPlay );
			}
		}
	}
	unguard;
}

void CPlayer::SwitchShuffleLeftAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	if( m_bJumping || IsDead() )
		return;

	if( GetSitStatus() && !GetSitInterrupt() )
		return;

	if( !m_pAnim )
		return;

	if( m_pAnim->GetCurAnimType() == MoreActionClient::stand )	
		return;

	if( IsEmbraceAnim() )
		return;

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	if( !m_bMounting && (HasFightFlag(eFighting) || IsFightPose()) )
		return;

	if( m_bMounting )
	{
		char szShuffle[MAX_PATH] = {0};
		char szIdle[MAX_PATH] = {0};
		ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
		if( pDrome )
		{
			strcpy(szShuffle, pDrome->GetMountAction( ItemDefine::MountShuffleLeft ));
			strcpy(szIdle, pDrome->GetMountAction( ItemDefine::MountDrive ));
		}
		else
		{
			strcpy(szShuffle, "mountShuffleleft");
			strcpy(szIdle, "mountdrive");
		}

		if( IsHaveWeapon() )
		{
			char szTemp[MAX_PATH] = {0};
			MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1 ,"single_%s", szShuffle);
			strcpy(szShuffle, szTemp);
			MeSprintf_s(szTemp, sizeof(szTemp)/sizeof(char) - 1,"single_%s", szIdle);
			strcpy(szIdle, szTemp);
		}

		if( stricmp( m_pAnim->GetCurrLowerBodyPlayTask()->szActionname, szShuffle ) )
		{
			if( !HasFightFlag(eFighting) && !IsFightPose() )
				m_pAnim->PlayLowerAnim(	szShuffle,
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime*0.3f,
				szIdle,
				MexAnimCtrl::eNormalPlay );
		}
		else
		{
			if( !HasFightFlag(eFighting) && !IsFightPose() )
				m_pAnim->ForceCurrAnimLoopTime(MexAnimCtrl::eMaxLoopTimes);
		}

		if( stricmp(m_pMountAnim->GetCurrLowerBodyPlayTask()->szActionname,szShuffle ) )
		{
			if( m_pMountAnim )
			{
				if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
				{
					m_pMountAnim->PlayLowerAnim("shuffleleft",
						MexAnimCtrl::eNormalPlay,
						0,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay);
				}
				else
				{
					m_pMountAnim->PlayAnimByActionName( "shuffleleft",
						MexAnimCtrl::eNormalPlay,
						618,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime*0.3f,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
			}
		}
		else
		{
			if( m_pMountAnim )
				m_pMountAnim->ForceCurrAnimLoopTime(MexAnimCtrl::eMaxLoopTimes);
		}
	}
	else
	{
		char szShuffle[MAX_PATH] = {0};
		char szIdle[MAX_PATH] = {0};
		if( HasFightFlag(eFighting) || IsFightPose() )
		{
			if( IsHaveWeapon() )
			{
				strcpy(szShuffle, "single_shuffle");
				strcpy(szIdle, "single_attack_idle");
			}
			else
			{
				strcpy(szShuffle, "attack_shuffle");
				strcpy(szIdle, "attack_idle");
			}
		}
		else
		{
			if( IsHaveWeapon() )
			{
				strcpy(szShuffle, "single_shuffleleft");
				strcpy(szIdle, "single_idle");
			}
			else
			{
				strcpy(szShuffle, "shuffle");
				strcpy(szIdle, "idle");
			}
		}

		if( stricmp( m_pAnim->GetCurrLowerBodyPlayTask()->szActionname, szShuffle ) )
		{
			m_pAnim->PlayLowerAnim(	szShuffle,
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				0,
				szIdle,
				MexAnimCtrl::eNormalPlay );
		}
		else
			m_pAnim->ForceCurrAnimLoopTime(MexAnimCtrl::eMaxLoopTimes);
	}
	unguard;
}

void CPlayer::SwitchShuffleRightAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	//return;
	if( m_bJumping || IsDead() )
	{
		return;
	}
	if( GetSitStatus() && !GetSitInterrupt() )
	{
		return;
	}

	if( !m_pAnim )
		return;

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;
	if( !m_bMounting && (HasFightFlag(eFighting) || IsFightPose()) )
		return;

	if( m_bMounting )
	{
		char szShuffle[MAX_PATH] = {0};
		char szIdle[MAX_PATH] = {0};
		ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
		if( pDrome )
		{
			strcpy(szShuffle, pDrome->GetMountAction( ItemDefine::MountShuffleRight ));
			strcpy(szIdle, pDrome->GetMountAction( ItemDefine::MountDrive ));
		}
		else
		{
			strcpy(szShuffle, "mountShuffleright");
			strcpy(szIdle, "mountdrive");
		}

		if( IsHaveWeapon() )
		{
			char szTemp[MAX_PATH] = {0};
			MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szShuffle);
			strcpy(szShuffle, szTemp);
			MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szIdle);
			strcpy(szIdle, szTemp);
		}

		if( stricmp( m_pAnim->GetCurrLowerBodyPlayTask()->szActionname, szShuffle ) )
		{
			if( !HasFightFlag(eFighting) && !IsFightPose() )
				m_pAnim->PlayLowerAnim(	szShuffle,
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime*0.3f,
				szIdle,
				MexAnimCtrl::eNormalPlay );
		}
		else
		{
			if( !HasFightFlag(eFighting) && !IsFightPose() )
				m_pAnim->ForceCurrAnimLoopTime(MexAnimCtrl::eMaxLoopTimes);
		}

		if( stricmp(m_pMountAnim->GetCurrLowerBodyPlayTask()->szActionname, szShuffle ) )
		{
			if( m_pMountAnim )
			{
				if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
				{
					m_pMountAnim->PlayLowerAnim( "shuffleright",
						MexAnimCtrl::eNormalPlay,
						618,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime*0.3f,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
				else
				{
					m_pMountAnim->PlayAnimByActionName( "shuffleright",
						MexAnimCtrl::eNormalPlay,
						618,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime*0.3f,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
			}
		}
		else
		{
			if( m_pMountAnim )
				m_pMountAnim->ForceCurrAnimLoopTime(MexAnimCtrl::eMaxLoopTimes);
		}
	}
	else
	{
		char szShuffle[MAX_PATH] = {0};
		char szIdle[MAX_PATH] = {0};
		if( HasFightFlag(eFighting) || IsFightPose() )
		{
			if( IsHaveWeapon() )
			{
				strcpy(szShuffle, "single_shuffle");
				strcpy(szIdle, "single_attack_idle");
			}
			else
			{
				strcpy(szShuffle, "attack_shuffle");
				strcpy(szIdle, "attack_idle");
			}
		}
		else
		{
			if( IsHaveWeapon() )
			{
				strcpy(szShuffle, "single_shuffleright");
				strcpy(szIdle, "single_idle");
			}
			else
			{
				strcpy(szShuffle, "shuffle");
				strcpy(szIdle, "idle");
			}
		}

		if( stricmp( m_pAnim->GetCurrLowerBodyPlayTask()->szActionname, szShuffle ) )
		{
			m_pAnim->PlayLowerAnim(	szShuffle,
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				0,
				szIdle,
				MexAnimCtrl::eNormalPlay );
		}
		else
			m_pAnim->ForceCurrAnimLoopTime(MexAnimCtrl::eMaxLoopTimes);	}
	unguard;
}

void CPlayer::SwitchWalkBackWardsAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */, DWORD dwBlendingTime /* = 0 */)
{
	guardfunc;
	if( g_bTheRoleJumping || IsDead() )	
		return;

	if( m_bRole && (IsUncontrolMoving()|| IsCarrierint()) )
		return;


	if( m_bRole )
		SitInterrupt();

	// �����ƶ��ٶ�
	m_fCurMoveRate = GetMoveRate()/2.66f/*2*/;

	if( !m_pAnim )
		return;

	DWORD dwOneLoopTime = 0;
	dwOneLoopTime = (m_fMovingStep/m_fCurMoveRate)*1000;

	if( IsMonster() )
	{
		m_pAnim->PlayLowerAnim(	"walk",
			MexAnimCtrl::eNormalPlay,
			dwOneLoopTime,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			"idle",
			MexAnimCtrl::eNormalPlay );
	}
	else
	{
		if( m_bMounting )
		{
			char szWalkBackwards[MAX_PATH] = {0};
			char szIdle[MAX_PATH] = {0};
			ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
			if( pDrome )
			{
				strcpy(szWalkBackwards, pDrome->GetMountAction( ItemDefine::MountWalkBackWards ));
				strcpy(szIdle, pDrome->GetMountAction( ItemDefine::MountDrive ));
			}
			else
			{
				strcpy(szWalkBackwards, "mountwalkbackwards" );
				strcpy(szIdle, "mountdrive" );
			}

			if( IsHaveWeapon() )
			{
				char szTemp[MAX_PATH] = {0};
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szWalkBackwards);
				strcpy(szWalkBackwards, szTemp);
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szIdle);
				strcpy(szIdle, szTemp);
			}

			m_pAnim->PlayLowerAnim(	szWalkBackwards,
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				szIdle,
				MexAnimCtrl::eNormalPlay );
			if( m_pMountAnim )
			{
				if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
				{
					m_pMountAnim->PlayLowerAnim("walkbackwards",
						MexAnimCtrl::eNormalPlay,
						dwOneLoopTime,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay);
				}
				else
				{
					m_pMountAnim->PlayAnimByActionName( "walkbackwards",
						MexAnimCtrl::eNormalPlay,
						dwOneLoopTime,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
			}
		}
		else
		{
			if( m_bMorphing && m_pMorphAnim )
			{
				m_pMorphAnim->PlayAnimByActionName( "walk"/*"walkbackwards"*/,
					MexAnimCtrl::eNormalPlay,
					0,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					"idle",
					MexAnimCtrl::eNormalPlay );
			}
			else if( IsHaveWeapon() )
			{
				if( HasFightFlag(eFighting) || IsFightPose() )
					m_pAnim->PlayLowerAnim(	"single_attack_walkbackwards",
					MexAnimCtrl::eNormalPlay,
					dwOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					dwBlendingTime,
					"single_attack_idle",
					MexAnimCtrl::eNormalPlay );
				else
					m_pAnim->PlayLowerAnim(	"single_walkbackwards",
					MexAnimCtrl::eNormalPlay,
					dwOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					dwBlendingTime,
					"single_idle",
					MexAnimCtrl::eNormalPlay );
			}
			else
			{
				m_pAnim->PlayLowerAnim(	"walkbackwards",
					MexAnimCtrl::eNormalPlay,
					dwOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					dwBlendingTime,
					"idle",
					MexAnimCtrl::eNormalPlay );
			}
		}

		if( GetLiftFlagStatus() > 0 )
		{
			int nUpperAnimType = m_pAnim->GetCurUpperAnimType();

			if( nUpperAnimType != MoreActionClient::single_flag_idle)
			{
				m_pAnim->PlayUpperAnim( MoreActionClient::single_flag_idle,
					MexAnimCtrl::eNormalPlay, 
					0,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime );
			}
		}
	}
	unguard;
}

//�л�����������
void CPlayer::SwitchJumpAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	if( IsDead() )
		return;

	if( m_bRole )
		SitInterrupt();

	UpdateCurZPos();
	m_fJumpingHeight = 0;
	m_fStartJumpingTerrainZ = m_fTerrainZ;
	if(m_bStartZMoving)
		m_fStartJumpingTerrainZ = m_z;

	if( !m_pAnim )
		return;

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	if( g_bTheRoleSlipJumping )
	{
		char szAnimName[MAX_PATH] = {0};
		if( IsHaveWeapon() )
		{
			if( HasFightFlag(eFighting) || IsFightPose() )
				strcpy(szAnimName, "single_attack_glide");
			else
				strcpy(szAnimName, "single_glide");
		}
		else
		{
			strcpy(szAnimName, "glide");
		}

		if (m_bMorphing)
		{
			if (m_pMorphAnim != NULL)
			{
				m_pMorphAnim->PlayAnimByActionName( szAnimName,
					MexAnimCtrl::eNormalPlay,
					0,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					szAnimName,
					MexAnimCtrl::eNormalPlay );
			}
		}
		else
		{
			m_pAnim->PlayLowerAnim(	szAnimName,
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				szAnimName,
				MexAnimCtrl::eNormalPlay );
		}

		return;
	}

	if( m_bMounting )
	{
		if( m_bMoving )
		{
			if( m_bCountermarch )
			{

			}
			else
			{
				char szJump[MAX_PATH] = {0};
				char szGlide[MAX_PATH] = {0};
				ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
				if( pDrome )
				{
					strcpy(szJump, pDrome->GetMountAction( ItemDefine::MountJump ));
					strcpy(szGlide, pDrome->GetMountAction( ItemDefine::MountGlide ));
				}
				else
				{
					strcpy(szJump, "mountjump");
					strcpy(szGlide, "mountGlide");
				}

				if( IsHaveWeapon() )
				{
					char szTemp[MAX_PATH] = {0};
					MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szJump);
					strcpy(szJump, szTemp);
					MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1,"single_%s", szGlide);
					strcpy(szGlide, szTemp);
				}

				m_pAnim->PlayLowerAnim(	szJump,
					MexAnimCtrl::eNormalPlay,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					0,
					szGlide,
					MexAnimCtrl::eNormalPlay );
				if( m_pMountAnim )
				{
					if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
					{
						m_pMountAnim->PlayLowerAnim( "jump",
							MexAnimCtrl::eNormalPlay,
							0,
							1,
							MexAnimCtrl::eMaxTimeout,
							0,
							"glide",
							MexAnimCtrl::eNormalPlay,
							0,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							0);
					}
					else
					{
						m_pMountAnim->PlayAnimByActionName( "jump",
							MexAnimCtrl::eNormalPlay,
							0,
							1,
							MexAnimCtrl::eMaxTimeout,
							0,
							"glide",
							MexAnimCtrl::eNormalPlay,
							0,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							0);
					}
				}
			}
		}
		else
		{
			char szNeigh[MAX_PATH] = {0};
			char szIdle[MAX_PATH] = {0};
			ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
			if( pDrome )
			{
				strcpy(szNeigh, pDrome->GetMountAction( ItemDefine::MountNeigh ));
				strcpy(szIdle, pDrome->GetMountAction( ItemDefine::MountDrive ));
				GSound.PlaySound( GetFullFileName((char*)pDrome->GetNeightSoundPath()), false, &GetPos());
			}
			else
			{
				strcpy(szNeigh, "mountneigh");
				strcpy(szIdle, "mountdrive");
			}

			if( IsHaveWeapon() )
			{
				char szTemp[MAX_PATH] = {0};
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szNeigh);
				strcpy(szNeigh, szTemp);
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szIdle);
				strcpy(szIdle, szTemp);
			}

			m_pAnim->PlayLowerAnim(	szNeigh,
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				szIdle,
				MexAnimCtrl::eNormalPlay );
			if( m_pMountAnim )
			{
				if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
				{
					m_pMountAnim->PlayLowerAnim("neigh",
						MexAnimCtrl::eNormalPlay,
						0,
						1,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
				else
				{
					m_pMountAnim->PlayAnimByActionName( "neigh",
						MexAnimCtrl::eNormalPlay,
						0,
						1,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
			}
		}
	}
	else
	{
		// ֻ��һ����Ծ����
		m_shJumpingType = 0;
		if( m_bRole && m_shJumpingType > 0 )
		{
			D3DXVECTOR3 vNextFramePos;
			vNextFramePos.x = m_x;
			vNextFramePos.y = m_y;
			vNextFramePos.z = 0;
			DWORD dwToHighestTime = m_fStartJumpingSpeed/g_fGravitation;//������ߵ��õ�ʱ��
			float fDir = atan2f(g_vTheRoleJumpingDir.y, g_vTheRoleJumpingDir.x) - g_fTheRoleJumpingRotate;
			float fJumpingMaxDistance = m_fJumpSpeed*dwToHighestTime*2*0.001f;
			float fPosXOff = 0;
			float fPosYOff = 0;
			float fxtoy = tan(fDir);

			if( fxtoy == 0 )
			{
				fPosXOff = fJumpingMaxDistance;
			}
			else
			{
				fPosXOff = sqrtf(fJumpingMaxDistance*fJumpingMaxDistance/(1+fxtoy*fxtoy));
				fPosYOff = fabs(fxtoy*fPosXOff);

				if( fDir > D3DX_PI*2 )
				{
					fDir -= D3DX_PI*2;
				}

				if( fDir < 0 )
				{
					fDir += D3DX_PI*2;
				}

				if( g_bTheRoleSlipJumping )
				{
					vNextFramePos.x += g_vTheRoleSlipJumpingDir.x*fJumpingMaxDistance;
					vNextFramePos.y += g_vTheRoleSlipJumpingDir.y*fJumpingMaxDistance;
				}
				else
				{
					bool bUnGetFramePos = true;
					if( ( fDir >= 0 && fDir <= D3DX_PI/2 ) || ( fDir >= -D3DX_PI*2 && fDir <= -D3DX_PI*3/2 ) )
					{
						vNextFramePos.x += fPosXOff;
						vNextFramePos.y += fPosYOff;
						bUnGetFramePos = false;
					}

					if( bUnGetFramePos && (( fDir >= D3DX_PI/2 && fDir <= D3DX_PI ) || ( fDir >= -D3DX_PI*3/2 && fDir <= -D3DX_PI )) )
					{
						vNextFramePos.x -= fPosXOff;
						vNextFramePos.y += fPosYOff;
						bUnGetFramePos = false;
					}

					if( bUnGetFramePos && (( fDir >= D3DX_PI && fDir <= D3DX_PI*3/2 ) || ( fDir >= -D3DX_PI && fDir <= -D3DX_PI/2 )) )
					{
						vNextFramePos.x -= fPosXOff;
						vNextFramePos.y -= fPosYOff;
						bUnGetFramePos = false;
					}

					if( bUnGetFramePos && (( fDir >= D3DX_PI*3/2 && fDir <= D3DX_PI*2 ) || ( fDir >= -D3DX_PI/2 && fDir <= 0 )) )
					{
						vNextFramePos.x += fPosXOff;
						vNextFramePos.y -= fPosYOff;
						bUnGetFramePos = false;
					}
				}
			}

			BOOL bRole = TRUE;
			float fRoleHeight = 80.0f*Config::m_fMdlSpaceScale;
			float fFarWorldZ = 0.0f;
			DWORD dwLoadFlags = 0;
			BOOL  bInFloor = FALSE;
			fFarWorldZ = GetZByXY( m_z + fRoleHeight,  vNextFramePos.x, vNextFramePos.y, 0, &bInFloor, &dwLoadFlags, bRole );
			float fZOffset = fFarWorldZ - m_z;
			if( fFarWorldZ > m_z )
			{
				m_shJumpingType = 0;
			}
		}

		DWORD dwJumpingPlayTime = 0;
		DWORD dwJumpBlendingTime = 0;
		if( m_ucSex == Sex_Male )
		{
			dwJumpingPlayTime = gCfg.m_dwJumpPlayTimeMale;
			dwJumpBlendingTime = gCfg.m_dwJumpBlendingTimeMale;
		}
		else
		{
			dwJumpingPlayTime = gCfg.m_dwJumpPlayTimeFemale;
			dwJumpBlendingTime = gCfg.m_dwJumpBlendingTimeFemale;
		}

		// 		int nJumpId = MoreActionClient::Idle;
		// 		int nJumpTargetId = MoreActionClient::Idle;
		std::string strJump;
		std::string strJumpTarget;
		if( IsHaveWeapon() )
		{
			if( HasFightFlag(eFighting) || IsFightPose() )
			{
				// 				nJumpId = MoreActionClient::single_attack_jump;
				// 				nJumpTargetId = MoreActionClient::single_attack_glide;
				strJump = "single_attack_jump";
				strJumpTarget = "single_attack_glide";
			}
			else
			{
				// 				nJumpId = MoreActionClient::single_jump;
				// 				nJumpTargetId = MoreActionClient::single_glide;

				strJump = "single_jump";
				strJumpTarget = "single_glide";
			}
		}
		else
		{
			if( m_shJumpingType > 0 )
			{
				// 				nJumpId = MoreActionClient::jump1;
				// 				nJumpTargetId = MoreActionClient::glide1;

				strJump = "jump1";
				strJumpTarget = "glide1";
			}
			else
			{
				// 				nJumpId = MoreActionClient::jump;
				// 				nJumpTargetId = MoreActionClient::glide;

				strJump = "jump";
				strJumpTarget = "glide";
			}

		}
		m_pAnim->PlayLowerAnim(	strJump.c_str(),
			MexAnimCtrl::eNormalPlay,
			dwJumpingPlayTime,
			1,
			MexAnimCtrl::eMaxTimeout,
			dwJumpBlendingTime,/*MexAnimCtrl::eDefaultBlendingTime,*/
			strJumpTarget.c_str(),
			MexAnimCtrl::eNormalPlay,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			618 );
		if (IsIntonating())
		{
			if (IsHaveWeapon())
			{
				SetShowWeapon(true);
			}
			GetAnim()->PlayUpperAnim(	strJump.c_str(),
				MexAnimCtrl::eNormalPlay,
				dwJumpingPlayTime,
				1,
				MexAnimCtrl::eMaxTimeout,
				dwJumpBlendingTime
				);
		}
		if( m_bMorphing && m_pMorphAnim )
		{
			m_pMorphAnim->PlayAnimByActionName( "jump",
				MexAnimCtrl::eNormalPlay,
				33*24,
				1,
				MexAnimCtrl::eMaxTimeout,
				0,
				"glide",
				MexAnimCtrl::eNormalPlay );

			int nUpperAnimType = m_pMorphAnim->GetCurUpperAnimType();

			if( nUpperAnimType < 0 )
			{
				m_fCurMoveRate = GetMoveRate();
				DWORD dwOneLoopTime = 0;
				dwOneLoopTime = (GetNormalStep()/m_fCurMoveRate)*1000;

				m_pMorphAnim->PlayAnimByActionName( "run",
					MexAnimCtrl::eNormalPlay,
					dwOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					"idle",
					MexAnimCtrl::eNormalPlay );
			}
		}
	}
	unguard;
}

void CPlayer::SwitchGlide(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	if( IsDead() )
		return;

	if( !m_pAnim )
		return;

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
	{
		if( m_bMounting )
		{
			char szGlide[MAX_PATH] = {0};
			ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
			if( pDrome )
			{
				strcpy(szGlide, pDrome->GetMountAction( ItemDefine::MountGlide ));
			}
			else
			{
				strcpy(szGlide, "mountGlide");
			}
			if( IsHaveWeapon() )
			{
				char szTemp[MAX_PATH] = {0};
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szGlide);
				strcpy(szGlide, szTemp);
			}

			m_pAnim->PlayLowerAnim(	szGlide,
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				szGlide,
				MexAnimCtrl::eNormalPlay );
			if( m_pMountAnim )
			{
				if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
				{
					m_pMountAnim->PlayLowerAnim( "glide",
						MexAnimCtrl::eNormalPlay,
						0,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"glide",
						MexAnimCtrl::eNormalPlay );
				}
				else
				{
					m_pMountAnim->PlayAnimByActionName( "glide",
						MexAnimCtrl::eNormalPlay,
						0,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"glide",
						MexAnimCtrl::eNormalPlay );
				}
			}
		}
		else
		{
			if( IsHaveWeapon() )
			{
				if( HasFightFlag(eFighting) || IsFightPose() )
				{
					m_pAnim->PlayLowerAnim(	"single_attack_glide",
						MexAnimCtrl::eNormalPlay,
						0,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"single_attack_glide",
						MexAnimCtrl::eNormalPlay );

				}
				else
				{
					m_pAnim->PlayLowerAnim(	"single_glide",
						MexAnimCtrl::eNormalPlay,
						0,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"single_glide",
						MexAnimCtrl::eNormalPlay );
				}
			}
			else
			{
				m_pAnim->PlayLowerAnim(	"glide",
					MexAnimCtrl::eNormalPlay,
					0,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					"glide",
					MexAnimCtrl::eNormalPlay );
			}
		}
	}
	unguard;
}

//�л������䶯��
int CPlayer::SwitchDropAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	if( IsDead() )
		return 0;

	if( !m_pAnim )
		return 0;

	int iDropAnimTime = 0;

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	if( m_bMounting )
	{
		if( m_bMoving )
		{
			DWORD dwRunOneLoopTime = (GetNormalStep()/m_fCurMoveRate)*1000;
			DWORD dwDropOneLoopTime = (float)dwRunOneLoopTime*29/20;

			if( g_bTheRoleCountermarch || m_bCountermarch )
			{
				char szDrop[MAX_PATH] = {0};
				char szWalk[MAX_PATH] = {0};
				ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
				if( pDrome )
				{
					strcpy(szDrop, pDrome->GetMountAction( ItemDefine::MountDrop ));
					strcpy(szWalk, pDrome->GetMountAction( ItemDefine::MountWalk ));
				}
				else
				{
					strcpy(szDrop, "mountdrop");
					strcpy(szWalk, "mountwalk");
				}

				if( IsHaveWeapon() )
				{
					char szTemp[MAX_PATH] = {0};
					MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1 ,"single_%s", szDrop);
					strcpy(szDrop, szTemp);
					MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1,"single_%s", szWalk);
					strcpy(szWalk, szTemp);
				}

				m_pAnim->PlayLowerAnim(	szDrop,
					MexAnimCtrl::eNormalPlay,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					0,
					szWalk,
					MexAnimCtrl::eNormalPlay );

				if( m_pMountAnim )
				{
					if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
					{
						m_pMountAnim->PlayLowerAnim( "drop",
							MexAnimCtrl::eNormalPlay,
							0,
							1,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime,
							"walk",
							MexAnimCtrl::eNormalPlay );

						iDropAnimTime = m_pMountAnim->GetAnimTimeLength( "drop" );
					}
					else
					{
						iDropAnimTime = m_pMountAnim->PlayAnimByActionName( "drop",
							MexAnimCtrl::eNormalPlay,
							0,
							1,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime,
							"walk",
							MexAnimCtrl::eNormalPlay );
					}
				}
			}
			else
			{
				char szFallToTheGroundRun[MAX_PATH] = {0};
				char szRun[MAX_PATH] = {0};
				ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
				if( pDrome )
				{
					strcpy(szFallToTheGroundRun, pDrome->GetMountAction( ItemDefine::MountFallToTheGroundRun ));
					strcpy(szRun, pDrome->GetMountAction( ItemDefine::MountRun ));
				}
				else
				{
					strcpy(szFallToTheGroundRun, "mountFalltothegroundrun");
					strcpy(szRun, "mountrun");
				}

				if( IsHaveWeapon() )
				{
					char szTemp[MAX_PATH] = {0};
					MeSprintf_s(szTemp, sizeof(szTemp)/sizeof(char) - 1,"single_%s", szFallToTheGroundRun);
					strcpy(szFallToTheGroundRun, szTemp);
					MeSprintf_s(szTemp, sizeof(szTemp)/sizeof(char) - 1,"single_%s", szRun);
					strcpy(szRun, szTemp);
				}
				m_pAnim->PlayLowerAnim(	szFallToTheGroundRun,
					MexAnimCtrl::eNormalPlay,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					0,
					szRun,
					MexAnimCtrl::eNormalPlay,
					0,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					0 );

				if( m_pMountAnim )
				{
					if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
					{
						m_pMountAnim->PlayLowerAnim( "falltothegroundrun",
							MexAnimCtrl::eNormalPlay,
							0,
							1,
							MexAnimCtrl::eMaxTimeout,
							0,
							"run",
							MexAnimCtrl::eNormalPlay,
							0,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							0 );

						iDropAnimTime = m_pMountAnim->GetAnimTimeLength( "falltothegroundrun" );
					}
					else
					{
						iDropAnimTime = m_pMountAnim->PlayAnimByActionName( "falltothegroundrun",
							MexAnimCtrl::eNormalPlay,
							0,
							1,
							MexAnimCtrl::eMaxTimeout,
							0,
							"run",
							MexAnimCtrl::eNormalPlay,
							0,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							0 );
					}
				}
			}
		}
		else
		{
			char szDrop[MAX_PATH] = {0};
			char szIdle[MAX_PATH] = {0};
			ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
			if( pDrome )
			{
				strcpy(szDrop, pDrome->GetMountAction( ItemDefine::MountDrop ));
				strcpy(szIdle, pDrome->GetMountAction( ItemDefine::MountDrive ));
			}
			else
			{
				strcpy(szDrop, "mountdrop");
				strcpy(szIdle, "mountdrive");
			}

			if( IsHaveWeapon() )
			{
				char szTemp[MAX_PATH] = {0};
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szDrop);
				strcpy(szDrop, szTemp);
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szIdle);
				strcpy(szIdle, szTemp);
			}
			m_pAnim->PlayLowerAnim(	szDrop,
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				0,
				szIdle,
				MexAnimCtrl::eNormalPlay );
			if( m_pMountAnim )
			{
				if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
				{
					m_pMountAnim->PlayLowerAnim( "drop",
						MexAnimCtrl::eNormalPlay,
						0,
						1,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );

					iDropAnimTime = m_pMountAnim->GetAnimTimeLength( "drop" );

				}
				else
				{
					iDropAnimTime = m_pMountAnim->PlayAnimByActionName( "drop",
						MexAnimCtrl::eNormalPlay,
						0,
						1,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
			}
		}
	}
	else
	{
		char szRun[36] = "run";
		char szWalkBack[36] = "walkbackwards";
		char szIdle[36] = "idle";

		if( IsPlayer() )
		{
			if( HasFightFlag(eFighting) || IsFightPose() )
			{
				if( IsHaveWeapon() )
				{
					strcpy(szRun,"single_attack_run");
					strcpy(szIdle,"single_attack_idle");
					strcpy(szWalkBack,"single_attack_walkbackwards");
				}
				else
				{
					strcpy(szIdle,"attack_idle");
				}
			}
			else
			{
				if( IsHaveWeapon() )
				{
					strcpy(szRun,"single_run");
					strcpy(szIdle,"single_idle");
					strcpy(szWalkBack,"single_walkbackwards");
				}
			}
		}

		if( IsInWater() )
		{
			strcpy(szRun,"swim");
			strcpy(szWalkBack,"swimidle");
			strcpy(szIdle,"swimidle");
			if( IsHaveWeapon() )
			{
				// ��������
				SetShowWeapon(FALSE);
			}
		}

		if( m_bMoving )
		{
			DWORD dwRunOneLoopTime = (m_fMovingStep/m_fCurMoveRate)*1000;
			DWORD dwDropOneLoopTime = (float)dwRunOneLoopTime*29/20;

			if( g_bTheRoleCountermarch || m_bCountermarch )	// ����
			{
				m_fCurMoveRate = GetMoveRate()/2;
				dwRunOneLoopTime = (m_fMovingStep/m_fCurMoveRate)*1000;
				iDropAnimTime = 300;

				char szDrop[36];
				if( IsHaveWeapon() )
				{
					if( HasFightFlag(eFighting) || IsFightPose() )
						strcpy( szDrop, "single_attack_drop" );
					else
						strcpy( szDrop, "single_falltothegroundwalkbackwards"/*"single_drop"*/ );
				}
				else if( m_shJumpingType > 0 )
					strcpy( szDrop, "drop1" );
				else
					strcpy( szDrop, "drop" );

				m_pAnim->PlayLowerAnim(	szDrop,
					MexAnimCtrl::eNormalPlay,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					0,
					szWalkBack,
					MexAnimCtrl::eNormalPlay,
					dwRunOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					100 );

				if( m_bMorphing && m_pMorphAnim )
				{
					m_pMorphAnim->PlayAnimByActionName( "drop",
						MexAnimCtrl::eNormalPlay,
						0,
						1,
						MexAnimCtrl::eMaxTimeout,
						50,
						"walkbackwards",
						MexAnimCtrl::eNormalPlay );

					int nUpperAnimType = m_pMorphAnim->GetCurUpperAnimType();

					if( nUpperAnimType < 0 )
					{
						m_fCurMoveRate = GetMoveRate();
						DWORD dwOneLoopTime = 0;
						dwOneLoopTime = (GetNormalStep()/m_fCurMoveRate)*1000;

						m_pMorphAnim->PlayAnimByActionName( "run",
							MexAnimCtrl::eNormalPlay,
							dwOneLoopTime,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime,
							"idle",
							MexAnimCtrl::eNormalPlay );
					}
				}
			}
			else
			{
				m_fCurMoveRate = GetMoveRate();
				dwRunOneLoopTime = (m_bRole && !m_bMorphing) ? gCfg.m_nRoleRunLoopTime : (GetNormalStep()/m_fCurMoveRate)*1000;

				if( m_fCurMoveRate <= 2.0 )
				{
					dwRunOneLoopTime = (m_fMovingStep/m_fCurMoveRate)*1000;
					strcpy(szRun,"walk");
				}

				DWORD dwFallToTheGroundRunPlayTime = 0;
				if( m_ucSex == Sex_Male )
				{
					dwFallToTheGroundRunPlayTime = gCfg.m_dwFallToTheGroundRunPlayTimeMale;
				}
				else
				{
					dwFallToTheGroundRunPlayTime = gCfg.m_dwFallToTheGroundRunPlayTimeFemale;
				}
				iDropAnimTime = 300;

				char szFalltothegroundrun[36];
				if( IsHaveWeapon() )
				{
					if( HasFightFlag(eFighting) || IsFightPose() )
						strcpy( szFalltothegroundrun, "single_attack_falltothegroundrun" );
					else
						strcpy( szFalltothegroundrun, "single_falltothegroundrun");
				}
				else if( m_shJumpingType > 0 )
					strcpy( szFalltothegroundrun, "falltothegroundrun1");
				else
					strcpy( szFalltothegroundrun, "falltothegroundrun");

				m_pAnim->PlayLowerAnim(	szFalltothegroundrun,
					MexAnimCtrl::eNormalPlay,
					dwFallToTheGroundRunPlayTime,
					1,
					MexAnimCtrl::eMaxTimeout,
					0,
					szRun,
					MexAnimCtrl::eNormalPlay,
					dwRunOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					0 );

				if( m_bMorphing && m_pMorphAnim )
				{
					m_fCurMoveRate = GetMoveRate();
					DWORD dwOneLoopTime = 0;
					dwOneLoopTime = (GetNormalStep()/m_fCurMoveRate)*1000;

					m_pMorphAnim->PlayAnimByActionName( "falltothegroundrun",
						MexAnimCtrl::eNormalPlay,
						0,
						1,
						MexAnimCtrl::eMaxTimeout,
						50,
						"run",
						MexAnimCtrl::eNormalPlay,
						dwOneLoopTime,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						0 );

					int nUpperAnimType = m_pMorphAnim->GetCurUpperAnimType();

					if( nUpperAnimType < 0 )
					{
						m_pMorphAnim->PlayAnimByActionName( "run",
							MexAnimCtrl::eNormalPlay,
							dwOneLoopTime,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime,
							"idle",
							MexAnimCtrl::eNormalPlay );
					}
				}
			}
		}
		else
		{
			DWORD dwDropPlayTime = 0;
			if( m_ucSex == Sex_Male )
			{
				dwDropPlayTime = gCfg.m_dwDropPlayTimeMale;
			}
			else
			{
				dwDropPlayTime = gCfg.m_dwDropPlayTimeFemale;
			}
			iDropAnimTime = (int)dwDropPlayTime;

			char szDrop[36];
			if( IsHaveWeapon() )
			{
				if( HasFightFlag(eFighting) || IsFightPose() )
					strcpy( szDrop, "single_attack_drop" );
				else
					strcpy( szDrop, "single_drop" );
			}
			else if( m_shJumpingType > 0 )
				strcpy( szDrop, "drop1" );
			else
				strcpy( szDrop, "drop" );

			m_pAnim->PlayLowerAnim(	szDrop,
				MexAnimCtrl::eNormalPlay,
				dwDropPlayTime,
				1,
				MexAnimCtrl::eMaxTimeout,
				0,
				szIdle,
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				200 );

			if( m_bMorphing && m_pMorphAnim )
			{
				m_pMorphAnim->PlayAnimByActionName( "drop",
					MexAnimCtrl::eNormalPlay,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					50,
					"idle",
					MexAnimCtrl::eNormalPlay );

				int nUpperAnimType = m_pMorphAnim->GetCurUpperAnimType();
				if( nUpperAnimType < 0 )
				{
					m_fCurMoveRate = GetMoveRate();
					DWORD dwOneLoopTime = 0;
					dwOneLoopTime = (GetNormalStep()/m_fCurMoveRate)*1000;

					m_pMorphAnim->PlayAnimByActionName( "run",
						MexAnimCtrl::eNormalPlay,
						dwOneLoopTime,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
			}
		}
	}
	return iDropAnimTime;
	unguard;
}

//////////////////////////////////
void CPlayer::PlayAnim( const char* szName, int nTimes, const char* szEndName )
{
	assert( m_pAnim );
	if (m_pAnim == NULL)
		return;

	//m_dwSpecialIdleInterval = 0xffffffff;
	if (m_bMorphing && m_pMorphAnim != NULL)
	{
		if (m_pMorphAnim->IsUpperBodyAndLowerBodyMode())
		{
			m_pMorphAnim->PlayLowerAnim(szName,
				MexAnimCtrl::eNormalPlay,
				0,
				nTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				szEndName,
				MexAnimCtrl::eNormalPlay);
		}
		else
		{
			m_pMorphAnim->PlayAnimByActionName( szName,
				MexAnimCtrl::eNormalPlay,
				0,
				nTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				szEndName,
				MexAnimCtrl::eNormalPlay );
		}
	}
	else
	{
		if (m_pAnim->IsUpperBodyAndLowerBodyMode())
		{
			m_pAnim->PlayLowerAnim(	szName,
				MexAnimCtrl::eNormalPlay,
				0,
				nTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				szEndName,
				MexAnimCtrl::eNormalPlay );
		}
		else
		{
			m_pAnim->PlayAnimByActionName( szName,
				MexAnimCtrl::eNormalPlay,
				0,
				nTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				szEndName,
				MexAnimCtrl::eNormalPlay );
		}
	}
}

void CPlayer::ReadyToLaunchSpecialSkill( short shStartPermillage )
{
	guardfunc;
	unguard;
}

void CPlayer::CancelReadyToLaunchSpecialSkill()
{
	guardfunc;
	unguard;
}

void CPlayer::StartCountDownSpecialSkill()
{
	guardfunc;
	thePlayerRole.SetCanUseSpecialSkill( true );
	unguard;
}

void CPlayer::StopMoving(bool bAction)
{
	guardfunc;
	m_bMoving = FALSE;
	if( IsRole() )
	{
		g_vTheRoleTargetPos.x = m_x;
		g_vTheRoleTargetPos.y = m_y;
		g_vTheRoleTargetPos.z = 0;
		g_bTheRoleMoveToTargetPos = FALSE;
		g_bTheRoleMovingByDir = FALSE;
		m_bLastFrameMoving = m_bMoving; // �Σ����в���ɾ�������Ӱ��ɼ�����
		g_bTheRoleCountermarch = false;
		CPlayerMgr* pMgr =theApp->GetPlayerMgr();
		pMgr->HideTargetPointEffect();

		if (pMgr->GetIsNeedNpcDailogShow())
		{			
			theApp->GetPlayerMgr()->SetNeedBeginDilog(false);
			if( pMgr->GetLockPlayerID() > -1 )
				Face2FaceWithNpc(pMgr->FindByID(pMgr->GetLockPlayerID()));
		}
		s_CUI_ID_FRAME_MiniMap.SetAutoRuning(false);
	}
	unguard;
}


void CPlayer::SwitchSpecialAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	if( !m_pAnim )
		return;
	m_pAnim->PlayAnim2(	MoreActionClient::Defend,
		MexAnimCtrl::eHoldOnLastFrame,
		0,
		1,
		MexAnimCtrl::eMaxTimeout,
		MoreActionClient::Idle,
		MexAnimCtrl::eNormalPlay );
	unguard;
}

void CPlayer::SwitchReadyToSpecialAnim( DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	if( !m_pAnim )
		return;
	m_pAnim->PlayAnim2(	MoreActionClient::Intonate,
		MexAnimCtrl::eNormalPlay,
		0,
		1,
		MexAnimCtrl::eMaxTimeout,
		MoreActionClient::Idle,
		MexAnimCtrl::eNormalPlay );
	unguard;
}

//�л���ˮ�д����Ķ���
void CPlayer::SwitchSwimIdleAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	if( !m_pAnim || g_bTheRoleJumping || IsDead() || m_bMounting )	
		return;

	if( IsPlayer() )
	{
		m_pAnim->PlayLowerAnim(	"swimidle",
			MexAnimCtrl::eNormalPlay,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			400,
			"swimidle",
			MexAnimCtrl::eNormalPlay );
	}
	if( IsHaveWeapon() )
	{
		// ��������
		SetShowWeapon(FALSE);
	}
	unguard;
}

//�л�����Ӿ�Ķ���
void CPlayer::SwitchSwimAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	// �����ƶ��ٶ�
	m_fCurMoveRate = GetMoveRate();

	if( !m_pAnim )
		return;

	if( g_bTheRoleJumping || IsDead() || m_bMounting )
		return;

	DWORD dwOneLoopTime = 0;
	dwOneLoopTime = (m_fSwimStep/m_fCurMoveRate)*1000;

	if ( IsPlayer() )
	{
		m_pAnim->PlayLowerAnim(	"swim",
			MexAnimCtrl::eNormalPlay,
			dwOneLoopTime,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			400,
			"swimidle",/*"idle",*/
			MexAnimCtrl::eNormalPlay );

		if( m_bMorphing && m_pMorphAnim )
		{
			int nUpperAnimType = m_pMorphAnim->GetCurUpperAnimType();

			m_pMorphAnim->PlayAnimByActionName( "run",
				MexAnimCtrl::eNormalPlay,
				dwOneLoopTime,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				"idle",
				MexAnimCtrl::eNormalPlay );
		}
	}
	if( IsHaveWeapon() )
	{
		// ��������
		SetShowWeapon(FALSE);
	}

	unguard;
}

//�л����ܲ��Ķ���
void CPlayer::SwitchRunAnim(DWORD dwTimeOut)
{
	guardfunc;

	if( !CanSwitchRunAnim() )
		return;

	if( m_bRole )
		SitInterrupt();

	m_fCurMoveRate = GetMoveRate();

	if( !m_pAnim )
		return;

	if(!m_bRole && m_bIntonating && IsPlayer()) 
	{
		return;
	}


	//m_pAnim->ForceCurrAnimLoopTime(-1,TRUE);

	DWORD dwOneLoopTime = 0;
	if( m_bRole && !m_bMounting && !m_bMorphing )
		dwOneLoopTime = gCfg.m_nRoleRunLoopTime;
	else
		dwOneLoopTime = (GetNormalStep()/m_fCurMoveRate)*1000;
	int nRunActionId = MoreActionClient::Run;

	if( m_fCurMoveRate <= 2.0 )
	{
		dwOneLoopTime = (m_fMovingStep/m_fCurMoveRate)*1000;
		nRunActionId = MoreActionClient::Walk;
		if( IsPlayer() )
		{
			if( IsHaveWeapon() )
			{
				nRunActionId = MoreActionClient::single_walk;
			}
		}
	}
	else if( IsPlayer() )
	{
		if( IsHaveWeapon() )
		{
			if( HasFightFlag(eFighting) || IsFightPose() )
				nRunActionId = MoreActionClient::single_attack_run;
			else
				nRunActionId = MoreActionClient::single_run;
		}
	}


	if( !IsPlayer() )
	{
		if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
		{
			if( m_bMounting )
			{
				ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
				if( pDrome )
				{
					m_pAnim->PlayLowerAnim(	pDrome->GetMountAction( ItemDefine::MountWalk ),
						MexAnimCtrl::eNormalPlay,
						dwOneLoopTime,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						pDrome->GetMountAction( ItemDefine::MountWalk ),
						MexAnimCtrl::eNormalPlay );
				}
				else
				{
					m_pAnim->PlayLowerAnim(	"mountwalk",
						MexAnimCtrl::eNormalPlay,
						dwOneLoopTime,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"mountwalk",
						MexAnimCtrl::eNormalPlay );
				}
				if( m_pMountAnim )
				{
					if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
					{
						m_pMountAnim->PlayLowerAnim( "walk",
							MexAnimCtrl::eNormalPlay,
							dwOneLoopTime,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime,
							"walk",
							MexAnimCtrl::eNormalPlay );
					}
					else
					{
						m_pMountAnim->PlayAnimByActionName( "walk",
							MexAnimCtrl::eNormalPlay,
							dwOneLoopTime,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime,
							"walk",
							MexAnimCtrl::eNormalPlay );
					}
				}
			}
			else
			{
				m_pAnim->PlayLowerAnim(	nRunActionId,
					MexAnimCtrl::eNormalPlay,
					dwOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					MoreActionClient::Idle,
					MexAnimCtrl::eNormalPlay );
			}
		}
		else
		{

			int nUpperAnimType = m_pAnim->GetCurUpperAnimType();

			if( nUpperAnimType == MoreActionClient::Attack1 ||
				nUpperAnimType == MoreActionClient::Attack2 ||
				nUpperAnimType == MoreActionClient::Attack3 )
			{
				return;
			}

			m_pAnim->PlayAnim2(	nRunActionId,
				MexAnimCtrl::eNormalPlay,
				dwOneLoopTime,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MoreActionClient::Idle,
				MexAnimCtrl::eNormalPlay );

			if( m_bMorphing && m_pMorphAnim )
			{
				m_pMorphAnim->PlayAnimByActionName( "run",
					MexAnimCtrl::eNormalPlay,
					dwOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					"idle",
					MexAnimCtrl::eNormalPlay );
			}
		}
	}
	else
	{
		if( m_bMounting )
		{
			char szRun[MAX_PATH] = {0};
			char szMountRun[MAX_PATH] = {0};
			BOOL bWalk = FALSE;
			if( m_fCurMoveRate <= 3.f )
			{
				bWalk = TRUE;
				strcpy( szMountRun, "walk");
			}
			else
			{
				strcpy( szMountRun, "run");
			}

			ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
			if( pDrome )
			{
				if( !bWalk )
					strcpy(szRun, pDrome->GetMountAction( ItemDefine::MountRun ));
				else
					strcpy(szRun, pDrome->GetMountAction( ItemDefine::MountWalk ));
			}
			else
			{
				if( !bWalk )
					strcpy(szRun, "mountrun");
				else
					strcpy(szRun, "mountwalk");
			}

			//if( IsHaveWeapon() )
			//         {
			//             char szTemp[MAX_PATH] = {0};
			//             MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1, "single_%s", szRun);
			//             strcpy(szRun, szTemp);
			//         }
			m_pAnim->PlayLowerAnim(	szRun,
				MexAnimCtrl::eNormalPlay,
				0,//dwOneLoopTime,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				szRun,
				MexAnimCtrl::eNormalPlay,
				0);
			if( m_pMountAnim )
			{
				if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
				{
					m_pMountAnim->PlayLowerAnim(szMountRun,
						MexAnimCtrl::eNormalPlay,
						0,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						szMountRun,
						MexAnimCtrl::eNormalPlay,
						0);
				}
				else
				{
					m_pMountAnim->PlayAnimByActionName( szMountRun,
						MexAnimCtrl::eNormalPlay,
						0,//dwOneLoopTime,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						szMountRun,
						MexAnimCtrl::eNormalPlay,
						0);
				}
			}
		}
		else
		{
			int iBlendTime = MexAnimCtrl::eDefaultBlendingTime;
			if( m_bRole && s_CUI_ID_FRAME_Target.GetFollowPlayerId() >= 0 )
				iBlendTime = 10;

			{
				m_pAnim->PlayLowerAnim(	nRunActionId,
					MexAnimCtrl::eNormalPlay,
					dwOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					iBlendTime,
					MoreActionClient::Idle,
					MexAnimCtrl::eNormalPlay );
			}

			if( m_bMorphing && m_pMorphAnim )
			{

				int nUpperAnimType = m_pMorphAnim->GetCurUpperAnimType();

				if( nUpperAnimType == MoreActionClient::Attack1 ||
					nUpperAnimType == MoreActionClient::Attack2 ||
					nUpperAnimType == MoreActionClient::Attack3 )
				{
					return;
				}

				m_pMorphAnim->PlayAnimByActionName( "run",
					MexAnimCtrl::eNormalPlay,
					dwOneLoopTime,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					"idle",
					MexAnimCtrl::eNormalPlay );
			}
		}

		if( GetLiftFlagStatus() > 0 )
		{
			int nUpperAnimType = m_pAnim->GetCurUpperAnimType();

			if( nUpperAnimType != MoreActionClient::single_flag_run)
			{
				m_pAnim->PlayUpperAnim( MoreActionClient::single_flag_run,
					MexAnimCtrl::eNormalPlay, 
					0,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime );
			}

		}
	}
	unguard;
}

//---
void	CPlayer::SwitchStunAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;
	if( !m_pAnim || m_bDead )
	{
		return;
	}

	int nLowerAnimType = m_pAnim->GetCurLowerAnimType();

	if( nLowerAnimType == MoreActionClient::Stun 
		|| nLowerAnimType == MoreActionClient::single_stun )
	{
		return;
	}

	if( IsHaveWeapon() )
	{
		m_pAnim->PlayLowerAnim(	MoreActionClient::single_stun,
			MexAnimCtrl::eNormalPlay,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime*2,
			MoreActionClient::single_stun,
			MexAnimCtrl::eNormalPlay );
	}
	else
	{
		m_pAnim->PlayLowerAnim(	MoreActionClient::Stun,
			MexAnimCtrl::eNormalPlay,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime*2,
			MoreActionClient::Stun,
			MexAnimCtrl::eNormalPlay );
	}

	unguard;
}

//---
void    CPlayer::SwitchIdleAnim( DWORD dwTimeOut, DWORD dwBlendingTime/* = MexAnimCtrl::eDefaultBlendingTime*/ )
{
	guardfunc;

	//duorenzuoji ������Ұ���� �������Ƕ��̼߳��� �ᵼ�� ����ģ���ӳټ��أ����Է������������¶���
	if ( !m_bRole && m_bCarrier)
	{
		SetShowWeapon(FALSE);
		SwitchSitLoopAnim(0xFFFFFFFF);
		return;
	}

	if( m_bRole )
	{
		if( !m_pAnim || g_bTheRoleJumping || m_bDead || IsCanOverIntonation())
		{
			return;
		}
		if( m_bNeedDropBuf )
			m_bNeedDropBuf = FALSE;
	}
	else
	{
		if( !m_pAnim || m_bDead || IsCanOverIntonation())
		{
			return;
		}
	}

	if(!m_bRole && m_bIntonating && IsPlayer()) 
	{
		return;
	}

	if(m_cFightStatus.IsBuoy())  //����״̬���ܲ���Idle����
		return;

	int nIdleActionId;
	nIdleActionId = GetPlayerActionID(MoreAction::Action_idle);
	int iBlendingTime = (int)dwBlendingTime;

	if( IsPlayer() )
	{
		if( HasFightFlag(eFighting) || IsFightPose() )
		{
			if( IsHaveWeapon() )		//if����������.
			{
				nIdleActionId = GetPlayerActionID( MoreAction::Action_single_attack_idle );
			}
			else
			{
				nIdleActionId = MoreActionClient::Attack_idle;
			}

			if( IsDoubleHandWeapon() )
			{
				nIdleActionId = GetPlayerActionID( MoreAction::Action_double_attack_idle );
			}
		}
		else if( IsHaveWeapon() )
		{
			nIdleActionId = MoreActionClient::single_idle;
		}
	}
	else if( IsMonster() )
	{
		if( HasFightFlag(eFighting) )
		{
			nIdleActionId = MoreActionClient::Attack_idle;
		}
	}else if(IsNpc())
	{
		if( HasFightFlag(eFighting) )
		{
			nIdleActionId = MoreActionClient::Attack_idle;
		}
	}

	if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
	{
		if( m_bMounting )
		{
			char szIdle[MAX_PATH] = {0};
			ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
			if( pDrome )
			{
				strcpy(szIdle, pDrome->GetMountAction( ItemDefine::MountDrive ));
			}
			else
			{
				strcpy(szIdle, "mountdrive");
			}

			if( IsHaveWeapon() )
			{
				char szTemp[MAX_PATH] = {0};
				MeSprintf_s(szTemp,sizeof(szTemp)/sizeof(char) - 1,"single_%s", szIdle);
				strcpy(szIdle, szTemp);
			}
			m_pAnim->PlayLowerAnim(	szIdle,
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				szIdle,
				MexAnimCtrl::eNormalPlay );
			if( m_pMountAnim )
			{
				if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
				{
					m_pMountAnim->PlayLowerAnim( "idle",
						MexAnimCtrl::eNormalPlay,
						0,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
				else
				{
					m_pMountAnim->PlayAnimByActionName( "idle",
						MexAnimCtrl::eNormalPlay,
						0,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
			}
		}
		else
		{
			{
				m_pAnim->PlayLowerAnim(	nIdleActionId,
					MexAnimCtrl::eNormalPlay,
					0,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					iBlendingTime,
					nIdleActionId,
					MexAnimCtrl::eNormalPlay );
			}

			if( m_bMorphing && m_pMorphAnim )
			{
				int nUpperAnimType = m_pMorphAnim->GetCurUpperAnimType();

				if( nUpperAnimType == MoreActionClient::Attack1 ||
					nUpperAnimType == MoreActionClient::Attack2 ||
					nUpperAnimType == MoreActionClient::Attack3 )
				{
					return;
				}

				m_pMorphAnim->PlayAnimByActionName( "idle",
					MexAnimCtrl::eNormalPlay,
					0,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					"idle",
					MexAnimCtrl::eNormalPlay );
			}
		}
	}
	else
	{

		int nUpperAnimType = m_pAnim->GetCurUpperAnimType();

		if( nUpperAnimType == MoreActionClient::Attack1 ||
			nUpperAnimType == MoreActionClient::Attack2 ||
			nUpperAnimType == MoreActionClient::Attack3 )
		{
			return;
		}

		m_pAnim->PlayAnim2( nIdleActionId,
			MexAnimCtrl::eNormalPlay, 
			0,
			MexAnimCtrl::eMaxLoopTimes, 
			MexAnimCtrl::eMaxTimeout, 
			nIdleActionId,
			MexAnimCtrl::eNormalPlay );

		if(m_bMorphing && m_pMorphAnim)
		{
			m_pMorphAnim->PlayAnimByActionName( "idle",
				MexAnimCtrl::eNormalPlay,
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				"idle",
				MexAnimCtrl::eNormalPlay );
		}
	}
	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	if( IsPlayer() && GetLiftFlagStatus() > 0 )
	{
		int nUpperAnimType = m_pAnim->GetCurUpperAnimType();

		if( nUpperAnimType != MoreActionClient::single_flag_idle)
		{
			m_pAnim->PlayUpperAnim( MoreActionClient::single_flag_idle,
				MexAnimCtrl::eNormalPlay, 
				0,
				MexAnimCtrl::eMaxLoopTimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime );
		}

	}

	unguard;
}

void	CPlayer::SwitchSpecialIdleAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;


	if( IsItem()/* || IsNpc()*/ )// npcҲ��������� [1/6/2011 zhangjiayi]
		return;

	if (IsNpc() && GetNpcType() == eNT_Elevator)
	{
		return; //����npc�����������
	}

	if( !m_pAnim )
		return;

	if( g_bTheRoleJumping || IsDead() || m_bMounting || m_ucSitStatus || HasFightFlag(eFighting) || IsFightPose() || m_pAnim->GetCurAnimType() == MoreActionClient::yongbao)
	{
		return;
	}

	if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
	{
		if( IsPlayer() && IsHaveWeapon() )
		{
			m_pAnim->PlayLowerAnim(	"single_specialidle",
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				"single_idle",
				MexAnimCtrl::eNormalPlay );
		}
		else
		{
			m_pAnim->PlayLowerAnim(	"specialidle",
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				"idle",
				MexAnimCtrl::eNormalPlay );
		}
	}
	else
	{
		int nUpperAnimType = m_pAnim->GetCurUpperAnimType();

		if( nUpperAnimType == MoreActionClient::Attack1 ||
			nUpperAnimType == MoreActionClient::Attack2 ||
			nUpperAnimType == MoreActionClient::Attack3 )
		{
			return;
		}

		m_pAnim->PlayAnimByActionName( "specialidle",
			MexAnimCtrl::eNormalPlay,
			0,
			1,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			"idle",
			MexAnimCtrl::eNormalPlay );
	}
	if( IsRole() )
	{
		if( GetSex() == Sex_Male )
		{
			PlaySoundConfig( SoundConfig::EST_IdleM );
		}
		else
		{
			PlaySoundConfig( SoundConfig::EST_IdleF );
		}
	}

	unguard;
}

bool CPlayer::GetSkillAnimLoopCnt(int &Times ,ItemDefine::SItemSkill * _skill)
{
	if (_skill) 
	{
		Times = 1;

		if(IsIntonating() && _skill->iDurationTime && _skill->iDamageBalanceDelay && _skill->bHoldSkill)
		{

			if ( HQ_TimeGetTime() - GetIntonatingStartTime() >  _skill->iDamageBalanceDelay) //�����ܵĵ�һ�鶯��Ԥ��һ�β��ż��ʱ��
			{
				return FALSE;
			}

			Times = MexAnimCtrl::eMaxLoopTimes;

		}

		return true;

	}
}

void CPlayer::PlaySpellEffect(DWORD dwEmissionFlyTime,GameObjectId ustTargetId,unsigned short ustSkillId,unsigned short ustSkillLevel,DWORD dwTimeOut /*= MexAnimCtrl::eMaxTimeout*/)
{
	//ȡ�ö�Ӧ���ܵĶ���
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ustSkillId, ustSkillLevel);
	ItemDefine::SItemStatus *pStatus = NULL;

	if (NULL == pSkill)
	{
		assert( false );
		return;
	}

	CPlayer* pDestPlayer = theHeroGame.GetPlayerMgr()->FindByID( ustTargetId );
	if(!pDestPlayer )
		return;

	float fDistance = D3DXVec3Length( &(pDestPlayer->GetPos() - GetPos()) );
	if( fDistance > 0.5 )
	{
		if( pSkill->bAssaultSkill )
		{
			dwEmissionFlyTime = 0;
		}

		// �Ƿ���Ҫ��Ⱦ��Ч
		if( CanRenderPlayerEffect(GetID()) )
		{
			const char *pEffectPath = NULL;
			if( m_ucSex == Sex_Female )
				pEffectPath = pSkill->GetSkillEffectName2();
			else
				pEffectPath = pSkill->GetSkillEffectName();

			if( stricmp( pEffectPath, "NULL" ) != 0 )
			{
				guard(testscale);				
				PlayEffect( (char*)pEffectPath, this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this), dwEmissionFlyTime, pDestPlayer );
				unguard;
			}
		}
	}
}

//---
//�л���ʩ������
//---
void	CPlayer::SwitchSpellAnim( DWORD dwEmissionFlyTime, GameObjectId ustTargetId, unsigned short ustSkillId, unsigned short ustSkillLevel, DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;

	//ȡ�ö�Ӧ���ܵĶ���
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ustSkillId, ustSkillLevel);
	ItemDefine::SItemStatus *pStatus = NULL;

	if (NULL == pSkill)
	{
		//	assert( false );
		return;
	}




	if( pSkill->ustPrepTime > 0 && g_bNextNotIntonate )
	{
		SetIntonating(FALSE);
		g_bNextNotIntonate = FALSE;
	}

	int looptimes = 1;
	if(!GetSkillAnimLoopCnt(looptimes,pSkill))
	{
		//PushHitPoint( 0, 1, 0, dwTimeOut );
		return ;
	}


	// �Ƿ��Ѿ�Ԥ�����ܶ���
	BOOL bPlayAnim = TRUE;
	if( m_vctAdvanceSkill.size() )
	{
		std::vector<SAdvanceSkillData>::iterator iter;
		for(iter = m_vctAdvanceSkill.begin(); iter != m_vctAdvanceSkill.end(); ++iter )
		{
			SAdvanceSkillData kAdvSkillData = *iter;
			if( kAdvSkillData.pSkill && kAdvSkillData.pSkill == pSkill )
			{
				bPlayAnim = FALSE;				
				break;				
				//m_vctAdvanceSkill.erase(iter);
				//break;				
			}
		}
	}

	if( IsDead() )
	{
		return;
	}
	if( !m_pAnim )
		return;

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	// �Ƿ���Ҫ��Ⱦ��Ч
	if( CanRenderPlayerEffect(GetID()) )
	{
		const char *pEffectPath = NULL;
		if( m_ucSex == Sex_Female )
			pEffectPath = pSkill->GetAttackerEffectName2();
		else
			pEffectPath = pSkill->GetAttackerEffectName();

		// ���似��Ҫ����Ч���Ƿ��似����SwitchAttackAnim�ﲥ��Ч
		// ���ŷ�����Ч
		if( pSkill->bEmissionSkill && stricmp( pEffectPath, "NULL" ) != 0 )
		{
			guard(testscale);
			PlayEffect( (char*)pEffectPath, this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this, true) );
			unguard;
		}
	}

	CPlayer* pDestPlayer = theHeroGame.GetPlayerMgr()->FindByID( ustTargetId );

	if( pDestPlayer )
	{
		float fDistance = D3DXVec3Length( &(pDestPlayer->GetPos() - GetPos()) );
		if( fDistance > 0.5 )
		{
			if( pSkill->bAssaultSkill )
			{
				dwEmissionFlyTime = 0;
			}

			// �Ƿ���Ҫ��Ⱦ��Ч
			if( CanRenderPlayerEffect(GetID()) )
			{
				const char *pEffectPath = NULL;
				if( m_ucSex == Sex_Female )
					pEffectPath = pSkill->GetSkillEffectName2();
				else
					pEffectPath = pSkill->GetSkillEffectName();

				// ����׷����Ч
				if( stricmp( pEffectPath, "NULL" ) != 0 )
				{
					guard(testscale);
					PlayEffect( (char*)pEffectPath, this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this, true), dwEmissionFlyTime, pDestPlayer );
					unguard;
				}
			}
		}
	}


	if( pDestPlayer )
	{
		float xSrc = 0;
		float ySrc = 0;
		float xDst = 0;
		float yDst = 0;
		xSrc = m_x;
		ySrc = m_y;
		xDst = pDestPlayer->GetPos().x;
		yDst = pDestPlayer->GetPos().y;

		//ת��Ŀ��
		if( !IsPlayer() && GetMonsterType() != eMT_Building && pSkill->bNeedTestAngle )
		{
			float fDir = atan2f( yDst-ySrc, xDst-xSrc );
			SetDir( fDir );
			SetLowerDir( fDir );
			SetUpperDir( fDir );
		}
	}

	int nActionIndex = 0;
	if( !m_bMoving )
	{
		nActionIndex = rand()%10;
	}


	// �Ӷ������ݶ����ܲ���ʱ��
	char szAnim[MAX_PATH] = {0};
	if (IsMounting())
		strncpy(szAnim, pSkill->GetSkillRideAction( ),sizeof(szAnim)-1);
	else
		strncpy(szAnim, pSkill->GetSkillAction( nActionIndex ),sizeof(szAnim)-1);

	if( m_pAnim )
	{
		dwTimeOut = m_pAnim->GetAnimTimeLength(szAnim/*pSkill->GetSkillAction( nActionIndex )*/);
	}

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	// ������Ϊnull�򲻲�����������ԭ������
	if( bPlayAnim && stricmp(szAnim, "null") )
	{
		if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
		{
			int iWholeBodyAnim = pSkill->iSkillActionFlags & ItemDefine::IS_WHOLE_ACTION;
			m_pAnim->PlayUpperAnim(	szAnim,
				MexAnimCtrl::eNormalPlay, 
				dwTimeOut,
				/*1*/looptimes,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				iWholeBodyAnim != 0 );

			if( !m_bMoving )
			{
				if( IsInWater() )
				{
					SwitchSwimIdleAnim();
				}
				else if(!(m_pAnim->GetCurUpperAnimType()==MoreActionClient::PetCall))
				{
					SwitchIdleAnim();
				}
			}
			else
			{
				if( IsInWater() )
				{
					SwitchSwimAnim();
				}
				else
				{
					SwitchRunAnim();
				}
			}

			if( m_bMorphing && m_pMorphAnim )
			{
				if( rand()%2 == 0 )
				{
					m_pMorphAnim->PlayInsertAnim( "attack1",
						MexAnimCtrl::eNormalPlay, 
						dwTimeOut,
						1, 
						MexAnimCtrl::eMaxTimeout );
				}
				else
				{
					m_pMorphAnim->PlayInsertAnim( "attack2",
						MexAnimCtrl::eNormalPlay, 
						dwTimeOut,
						1, 
						MexAnimCtrl::eMaxTimeout );
				}
			}
		}
		else
		{
			m_pAnim->PlayInsertAnim( szAnim/*pSkill->GetSkillAction( nActionIndex )*/,
				MexAnimCtrl::eNormalPlay, 
				dwTimeOut,
				1, 
				MexAnimCtrl::eMaxTimeout );

			if(m_bMorphing && m_pMorphAnim)
			{
				m_pMorphAnim->PlayInsertAnim(szAnim /*pSkill->GetSkillAction( nActionIndex )*/,
					MexAnimCtrl::eNormalPlay, 
					dwTimeOut,
					1, 
					MexAnimCtrl::eMaxTimeout );
			}
		}
	}

	unguard;
}

BOOL	CPlayer::SwitchAttackAnim( unsigned short ustSkillId, unsigned short ustSkillLevel, DWORD* pGetHitPointTime/* = NULL*/, DWORD* pGetEndFrameTime/* = NULL*/ )
{
	guardfunc;

	//��Ч�ֲ����ж�������
	if( Object_Effect == GetCharType() )
		return false;

	//ȡ�ö�Ӧ���ܵĶ���
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ustSkillId, ustSkillLevel);
	ItemDefine::SItemStatus *pStatus = NULL;
	int nActionIndex = 0;

	guard(test1);
	if (NULL == pSkill)
	{
		assert( false );
		return FALSE;
	}



	if( pSkill->ustPrepTime > 0 && g_bNextNotIntonate )
	{
		SetIntonating(FALSE);
		g_bNextNotIntonate = FALSE;
	}

	//����������У��������ڵ���������˺����ܣ��򲻽��ж�ζ������á�
	int looptimes = 1;
	if(!GetSkillAnimLoopCnt(looptimes,pSkill))
	{
		if( pGetHitPointTime )
		{
			// ���趯��֡��30��HitPoint��20֡����
			*pGetHitPointTime = CalHitPointPlayTime( 0, 30, 20 );
		}
		if( pGetEndFrameTime )
		{
			*pGetEndFrameTime = g_dwLastFrameBeginTime + 30*ONEFRAMEINTERVAL;
		}

		return false;
	}




	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	// �Ƿ���Ҫ��Ⱦ��Ч
	if( CanRenderPlayerEffect(GetID()) )
	{
		const char *pEffectPath = NULL;
		if( m_ucSex == Sex_Female )
			pEffectPath = pSkill->GetAttackerEffectName2();
		else
			pEffectPath = pSkill->GetAttackerEffectName();

		if( stricmp( pEffectPath, "NULL" ) != 0 )
		{
			guard(testscale);
			PlayEffect( (char*)pEffectPath, this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this) );
			unguard;
		}
	}

	if( !m_pAnim )
	{
		if( pGetHitPointTime )
		{
			// ���趯��֡��30��HitPoint��20֡����
			*pGetHitPointTime = CalHitPointPlayTime( 0, 30, 20 );
		}
		if( pGetEndFrameTime )
		{
			*pGetEndFrameTime = g_dwLastFrameBeginTime + 30*ONEFRAMEINTERVAL;
		}
		return TRUE;
	}

	if( m_ucSex == Sex_Female )
	{
		nActionIndex = rand()%10+10;
	}
	else
	{
		nActionIndex = rand()%10;
	}
	unguard;


	guard(test2);

	if( nActionIndex < 0 || nActionIndex > 19 )
		nActionIndex = 0;

	DWORD dwTimeOut;

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	if( nActionIndex > 9 )
		nActionIndex -= 10;

	char szAnim[MAX_PATH] = {0};
	if (IsMounting())
		strncpy(szAnim, pSkill->GetSkillRideAction( ),sizeof(szAnim)-1);
	else
		strncpy(szAnim, pSkill->GetSkillAction( nActionIndex ),sizeof(szAnim)-1);

	if( m_pAnim )
		dwTimeOut = m_pAnim->GetAnimTimeLength(szAnim/*pSkill->GetSkillAction( nActionIndex )*/);

	if (pSkill->iSkillActionFlags & ItemDefine::IS_AUTO_STOP )
		m_dwStopMoveTime = dwTimeOut + HQ_TimeGetTime();


	if( pSkill->iSkillActionFlags & ItemDefine::CANNOT_JUMP_CAST )
		m_dwStopJumpTime = dwTimeOut + HQ_TimeGetTime();

	// ������Ϊnull�򲻲�����������ԭ������
	if( stricmp(szAnim, "null") )
	{
		if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
		{
			if(IsGoudaOperaMode())
			{
				if(m_pMountAnim)
				{
					if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
					{
						int iWholeBodyAnim = pSkill->iSkillActionFlags & ItemDefine::IS_WHOLE_ACTION;
						m_pMountAnim->PlayUpperAnim(szAnim/*pSkill->GetSkillAction( nActionIndex )*/,
							MexAnimCtrl::eNormalPlay, 
							dwTimeOut,
							/*1*/looptimes,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime*0.5f,
							iWholeBodyAnim != 0,
							IsNormalAttack(ustSkillId));

						m_pMountAnim->PlayLowerAnim("idle",MexAnimCtrl::eNormalPlay,0,MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,MexAnimCtrl::eDefaultBlendingTime,"idle",MexAnimCtrl::eNormalPlay);
					}
					else
					{
						m_pMountAnim->PlayAnimByActionName( szAnim/*pSkill->GetSkillAction(nActionIndex)*/,
							MexAnimCtrl::eNormalPlay,
							dwTimeOut,
							/*1*/looptimes,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime,
							"idle",
							MexAnimCtrl::eNormalPlay );
					}
				}
			}
			else
			{
				if(!pSkill->bMoveInterrupt)
				{
					m_pAnim->PlayLowerAnim("single_skill5",
						MexAnimCtrl::eNormalPlay,
						dwTimeOut,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"single_skill5",
						MexAnimCtrl::eNormalPlay);
				}
				else
				{
					int iWholeBodyAnim = pSkill->iSkillActionFlags & ItemDefine::IS_WHOLE_ACTION;
					m_pAnim->PlayUpperAnim(	szAnim,
						MexAnimCtrl::eNormalPlay, 
						dwTimeOut,
						/*1*/looptimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime*0.5f,
						iWholeBodyAnim != 0,
						IsNormalAttack(ustSkillId),
						this == theHeroGame.GetPlayerMgr()->GetMe() );
				}

				if( !m_bMoving )
				{
					if( IsInWater() )
					{
						SwitchSwimIdleAnim();
					}
					else
					{
						SwitchIdleAnim();
					}
				}
				else
				{
					if( IsInWater() )
					{
						SwitchSwimAnim();
					}
					else
					{
						SwitchRunAnim();
					}
				}
			}

			if( m_bMorphing && m_pMorphAnim )
			{
				if( rand()%2 == 0 )
				{
					m_pMorphAnim->PlayInsertAnim( "attack1",
						MexAnimCtrl::eNormalPlay, 
						dwTimeOut,
						1, 
						MexAnimCtrl::eMaxTimeout );
				}
				else
				{
					m_pMorphAnim->PlayInsertAnim( "attack2",
						MexAnimCtrl::eNormalPlay, 
						dwTimeOut,
						1, 
						MexAnimCtrl::eMaxTimeout );
				}
			}
		}
		else
		{
			m_pAnim->PlayInsertAnim( szAnim,
				MexAnimCtrl::eNormalPlay, 
				dwTimeOut,
				1, 
				MexAnimCtrl::eMaxTimeout );
		}
	}
	else
	{
		if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
			m_pAnim->ForceUpperAnimPlayOver();
	}

	// ��սʱ, ����ҲҪ���Ź�������
	if (m_pMountAnim != NULL && IsMounting() && !IsMoving() && !IsGoudaOperaMode())
	{
		m_pMountAnim->PlayAnimByActionName( "ride_attack",
			MexAnimCtrl::eNormalPlay,
			dwTimeOut,
			1,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			"idle",
			MexAnimCtrl::eNormalPlay );
	}

	if( pGetHitPointTime )
	{
		*pGetHitPointTime = CalHitPointPlayTime( m_pAnim->GetStartFrameID(), m_pAnim->GetEndFrameId(), m_pAnim->GetHitPointFrameID() );
	}
	if( pGetEndFrameTime )
	{
		*pGetEndFrameTime = g_dwLastFrameBeginTime + ( m_pAnim->GetEndFrameId() - m_pAnim->GetStartFrameID() )*ONEFRAMEINTERVAL;
	}

	unguard;
	unguard;
	return TRUE;
}

//�л���ս������
void    CPlayer::SwitchAttackAnim(DWORD dwTimeOut)
{
	guardfunc;

	if(!m_pAttackInfo)
	{
		//������Ϣ����,����ǰ�������ļ����б����,Ҫ���Ῠ������ vvx 2013.11.22
		ClearAdvanceSkillList();
		return;
	}
	//ȡ�õ�ǰ��Ϊ������
	SAttackInfo *pAttackInfo = m_pAttackInfo;
	//ȡ�ö�Ӧ���ܵĶ���
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pAttackInfo->iSkill,
		pAttackInfo->iSkillLevel );

	if (NULL == pSkill)
	{
		assert( false );
		return;
	}

	if( pSkill->ustPrepTime > 0 && g_bNextNotIntonate )
	{
		SetIntonating(FALSE);
		g_bNextNotIntonate = FALSE;
	}


	//����������У��������ڵ���������˺����ܣ��򲻽��ж�ζ������á�
	int looptimes = 1;
	if(!GetSkillAnimLoopCnt(looptimes,pSkill))
	{
		PushHitPoint( 0, 1, 0, 0 );
		return ;

	}

	char szAnim[MAX_PATH] = {0};
	if (IsMounting())
		strncpy(szAnim, pSkill->GetSkillRideAction( ),sizeof(szAnim)-1);
	else
		strncpy(szAnim, pSkill->GetSkillAction( 0 ),sizeof(szAnim)-1);

	// ������Ԥ������
	if( m_vctAdvanceSkill.size() )
	{
		std::vector<SAdvanceSkillData>::iterator iter;
		for(iter = m_vctAdvanceSkill.begin(); iter != m_vctAdvanceSkill.end(); ++iter )
		{
			SAdvanceSkillData kAdvSkillData = *iter;
			if( kAdvSkillData.pSkill && kAdvSkillData.pSkill == pSkill )
			{
				if( pSkill->bEmissionSkill || pSkill->ustPrepTime > 0 )
				{
					PushHitPoint( 0, 1, 0, dwTimeOut );
				}
				else
				{
					m_dwPushHitPointTime = g_dwLastFrameBeginTime;
					m_dwHitPointPlayTime = kAdvSkillData.dwHitPointPlayTime;
					m_bHitPointPlayOver = FALSE;
					// Ԥ��������ҪԤ���ܻ���������hitpointʱ���ѹ���Ӧ���Ѳ����ܻ����������ظ���
					if( m_dwHitPointPlayTime < m_dwPushHitPointTime 
						&& kAdvSkillData.nNeedPlayHurtAnim == CPlayer::ASH_Played )
					{
						pAttackInfo->bPlayHurtAnim = false;
					}
				}
				m_vctAdvanceSkill.erase(iter);

				/*strcpy(szAnim, pSkill->GetSkillAction( 0 ));*/
				//if( !pSkill->bEmissionSkill && pSkill->ustPrepTime == 0 )
				if( m_pAnim )
				{
					// ������Ϊnull�򲻲�����������ԭ������
					if( !stricmp(szAnim, "null") && m_pAnim->IsUpperBodyAndLowerBodyMode() )
						m_pAnim->ForceUpperAnimPlayOver();
				}
				return;
			}
		}
	}

	// �Ƿ���Ҫ��Ⱦ��Ч
	if( CanRenderPlayerEffect(GetID()) )
	{
		const char *pEffectPath = NULL;
		if( m_ucSex == Sex_Female )
			pEffectPath = pSkill->GetAttackerEffectName2();
		else
			pEffectPath = pSkill->GetAttackerEffectName();

		if( !pSkill->bEmissionSkill )   // �Ƿ��似�ܾͲ���Ч
		{
			if( stricmp( pEffectPath, "NULL" ) != 0 )
			{
				guard(testscale);
				PlayEffect( (char*)pEffectPath, this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this) );
				unguard;
			}
		}
	}

	if( !m_pAnim )
	{
		PushHitPoint( 0, 1, 0, 0/*dwTimeOut*/ );
		return;
	}

	int nActionIndex = 0;
	if( m_ucSex == Sex_Female )
	{
		nActionIndex = rand()%10+10;
	}
	else
	{
		nActionIndex = rand()%10;
	}

	float fActionMod = m_cFightStatus.GetActionTimeMod();
	float fTemp = 0.0f;

	{
		if( nActionIndex < 0 || nActionIndex > 19 )
			nActionIndex = 0;

		if( nActionIndex > 9 )
			nActionIndex -= 10;

		if( m_pAnim )
		{
			if (IsMounting())
				strncpy(szAnim, pSkill->GetSkillRideAction( ),sizeof(szAnim)-1);
			else
				strncpy(szAnim, pSkill->GetSkillAction( nActionIndex ),sizeof(szAnim)-1);
			dwTimeOut = m_pAnim->GetAnimTimeLength(szAnim/*pSkill->GetSkillAction( nActionIndex )*/);
		}

		pAttackInfo->dwActionTime = dwTimeOut;

	}

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	if (pSkill->iSkillActionFlags & ItemDefine::IS_AUTO_STOP)
	{
		m_dwStopMoveTime = dwTimeOut + HQ_TimeGetTime();
	}

	if( pSkill->iSkillActionFlags & ItemDefine::CANNOT_JUMP_CAST )
	{
		m_dwStopJumpTime = dwTimeOut + HQ_TimeGetTime();
	}

	if( !pSkill->bEmissionSkill && pSkill->ustPrepTime == 0 )
	{
		// ������Ϊnull�򲻲�����������ԭ������
		if( stricmp(szAnim, "null") )
		{
			if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
			{
				if(IsGoudaOperaMode())
				{
					if(m_pMountAnim)
					{
						if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
						{
							m_pMountAnim->PlayLowerAnim( szAnim/*pSkill->GetSkillAction(nActionIndex)*/,
								MexAnimCtrl::eNormalPlay,
								dwTimeOut,
								1,
								MexAnimCtrl::eMaxTimeout,
								MexAnimCtrl::eDefaultBlendingTime,
								"idle",
								MexAnimCtrl::eNormalPlay );
						}
						else
						{
							m_pMountAnim->PlayAnimByActionName( szAnim/*pSkill->GetSkillAction(nActionIndex)*/,
								MexAnimCtrl::eNormalPlay,
								dwTimeOut,
								1,
								MexAnimCtrl::eMaxTimeout,
								MexAnimCtrl::eDefaultBlendingTime,
								"idle",
								MexAnimCtrl::eNormalPlay );
						}
					}
				}
				else
				{

					if(!pSkill->bMoveInterrupt)
					{
						m_pAnim->PlayUpperAnim(szAnim/*pSkill->GetSkillAction(nActionIndex)*/,
							MexAnimCtrl::eNormalPlay,
							dwTimeOut,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime,TRUE);
					}
					else
					{
						int iWholeBodyAnim = pSkill->iSkillActionFlags & ItemDefine::IS_WHOLE_ACTION;
						m_pAnim->PlayUpperAnim(	szAnim,
							MexAnimCtrl::eNormalPlay, 
							dwTimeOut,
							/*1*/looptimes,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime*0.5f,
							iWholeBodyAnim != 0,
							IsNormalAttack(pAttackInfo->iSkill),
							this == theHeroGame.GetPlayerMgr()->GetMe() );
					}
				}
			}
			else
			{
				m_pAnim->PlayInsertAnim( szAnim/*pSkill->GetSkillAction( nActionIndex )*/,
					MexAnimCtrl::eNormalPlay, 
					dwTimeOut,
					1, 
					MexAnimCtrl::eMaxTimeout );
			}

			if( m_bMorphing && m_pMorphAnim )
			{
				if( rand()%2 == 0 )
				{
					m_pMorphAnim->PlayInsertAnim( "attack1",
						MexAnimCtrl::eNormalPlay, 
						dwTimeOut,
						1, 
						MexAnimCtrl::eMaxTimeout );
				}
				else
				{
					m_pMorphAnim->PlayInsertAnim( "attack2",
						MexAnimCtrl::eNormalPlay, 
						dwTimeOut,
						1, 
						MexAnimCtrl::eMaxTimeout );
				}
			}
		}
		else
		{
			if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
				m_pAnim->ForceUpperAnimPlayOver();
		}
		m_pAnim->SetAttackInfo( GetAttackInfo() );
	}

	// "��ս"״̬ʱ, ����������ƶ���, ����һ������
	if (m_pMountAnim != NULL && IsMounting() && !IsMoving())
	{
		m_pMountAnim->PlayAnimByActionName( "ride_attack",
			MexAnimCtrl::eNormalPlay,
			dwTimeOut,
			1,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			"idle",
			MexAnimCtrl::eNormalPlay );
	}

	if( pSkill->bEmissionSkill || pSkill->ustPrepTime > 0 )
	{
		PushHitPoint( 0, 1, 0, dwTimeOut );
	}
	else
	{
		PushHitPoint( m_pAnim->GetStartFrameID(), m_pAnim->GetEndFrameId(), m_pAnim->GetHitPointFrameID(), dwTimeOut );
	}
	unguard;
}

void CPlayer::SwitchHoldSkillAnim(DWORD dwTimeOut )
{
	guardfunc;

	unguard;
}

//�л�����������
void CPlayer::SwitchIntonateAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */, ItemDefine::SItemSkill* pSkill )
{
	guardfunc;
	if( !pSkill )
		return;

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	if( m_bRole && GetSitStatus() && !GetSitInterrupt() )
	{
		// �������״̬
		SetSitInterrupt(1);
		// ����վ��״̬��������
		theApp->GetPlayerMgr()->ProcessCommand("DoSitDown");
	}

	//������������ܳ���32��,by vvx 2012.11.26		
	char IntonateAction[32];		
	if (IsMounting())
		strncpy(IntonateAction, pSkill->GetRideIntonateAction(),sizeof(IntonateAction)-1);
	else
		strncpy(IntonateAction, pSkill->GetIntonateAction(),sizeof(IntonateAction)-1);

	if( m_pAnim )
	{
		char idle[32];
		strcpy(idle, "idle");
		if( IsFightPose() )
		{
			if( IsHaveWeapon() )
				strcpy(idle, "single_attack_idle");
			else
				strcpy(idle, "attack_idle");
		}
		else
		{
			if( IsHaveWeapon() )
			{
				strcpy(idle, "single_idle");
			}
		}

		int looptimes;
		if( IsCollectionAnim(IntonateAction/*pSkill->GetIntonateAction()*/) && !IsMountMonsterSkill(pSkill->ustItemID) )
		{
			looptimes = 1;
		}
		else
			looptimes = MexAnimCtrl::eMaxLoopTimes;
		//����ǲ�׽���ܵĻ�����ѭ������
		if (IsCollectionAnim(IntonateAction/*pSkill->GetIntonateAction()*/) && pSkill->bIsCatchNurturePet == true)
		{
			looptimes = MexAnimCtrl::eMaxLoopTimes;
		}
		char szAnim[MAX_PATH] = {0};
		//if (IsMounting())
		//	strcpy(szAnim, pSkill->GetSkillRideAction());
		//else
		//	strcpy(szAnim, IntonateAction/*pSkill->GetIntonateAction()*/);
		strcpy(szAnim, IntonateAction/*pSkill->GetIntonateAction()*/);
		// ������Ϊnull�򲻲�����������ԭ������
		if ( stricmp(szAnim, "null") )
		{
			if ( IsMountMonsterSkill( pSkill->ustItemID ) )
			{
				m_pAnim->PlayUpperAnim(IntonateAction /*pSkill->GetIntonateAction()*/,
					MexAnimCtrl::eNormalPlay,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime
					);
			}
			else
			{
				if (m_bMorphing)
				{
					if (m_pMorphAnim != NULL)
					{
						m_pMorphAnim->PlayAnimByActionName( szAnim,
							MexAnimCtrl::eNormalPlay,
							0,
							MexAnimCtrl::eMaxLoopTimes,
							MexAnimCtrl::eMaxTimeout,
							MexAnimCtrl::eDefaultBlendingTime,
							idle,
							MexAnimCtrl::eNormalPlay );
					}
				}
				else
				{
					m_pAnim->PlayLowerAnim( szAnim,
						MexAnimCtrl::eNormalPlay,
						0,
						looptimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						idle,
						MexAnimCtrl::eNormalPlay );
				}
			}			
		}
	}

	if(!strcmp(IntonateAction/*pSkill->GetIntonateAction()*/,"loot")
		||!strcmp(IntonateAction/*pSkill->GetIntonateAction()*/,"rideloot"))
	{
		if( IsRole() )
		{
			if( GetSex() == Sex_Male )
			{
				PlaySoundConfig( SoundConfig::EST_IdleM );
			}
			else
			{
				PlaySoundConfig( SoundConfig::EST_IdleF );
			}
		}
		GetBillBoard()->SetTipCounts(FRIST_COLLECT);
	}
	unguard;
}

//�л����ʳ�����
void CPlayer::SwitchIntonateAnim(DWORD dwTimeOut)
{
	guardfunc;
	IntonateInfo *pIntonateInfo = (IntonateInfo *)m_NowAction.sData;
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pIntonateInfo->iSkillNo, pIntonateInfo->iSkillLevel);

	if (NULL == pSkill)
		return;

	if( m_bRole && GetSitStatus() && !GetSitInterrupt() )
	{
		// �������״̬
		SetSitInterrupt(1);
		// ����վ��״̬��������
		theApp->GetPlayerMgr()->ProcessCommand("DoSitDown");
	}

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	if( m_pAnim )
	{
		char idle[32];
		strcpy(idle, "idle");
		if( IsFightPose() )
		{
			if( IsHaveWeapon() )
				strcpy(idle, "single_attack_idle");
			else
				strcpy(idle, "attack_idle");
		}
		else
		{
			if( IsHaveWeapon() )
				strcpy(idle, "single_idle");
		}

		int looptimes;
		if( IsCollectSkill(pIntonateInfo->iSkillNo) && !IsMountMonsterSkill(pSkill->ustItemID) )
			looptimes = 1;
		else
			looptimes = MexAnimCtrl::eMaxLoopTimes;

		char szAnim[MAX_PATH] = {0};
		if (IsMounting())
			strncpy(szAnim, pSkill->GetRideIntonateAction(),sizeof(szAnim)-1);
		else
			strncpy(szAnim, pSkill->GetIntonateAction(),sizeof(szAnim)-1);

		/*char szAnim[MAX_PATH] = {0};
		strcpy(szAnim, pSkill->GetIntonateAction());*/
		// ������Ϊnull�򲻲�����������ԭ������
		if( stricmp(szAnim, "null") )
			m_pAnim->PlayLowerAnim( szAnim/*pSkill->GetIntonateAction()*/,
			MexAnimCtrl::eNormalPlay,
			0,
			looptimes,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			idle,
			MexAnimCtrl::eNormalPlay );
	}
	unguard;
}


//�л���pcik����
void CPlayer::SwitchPickAnim(DWORD dwTimeOut)
{
	guardfunc;
	return;
	unguard;
}


//�л�����������
void CPlayer::SwitchHurtAnim(DWORD dwTimeOut)
{
	guardfunc;
	if( !m_pAnim || IsDead() )
		return;

	if( m_pAnim->GetCurLowerAnimType() == MoreActionClient::Stun 
		|| m_pAnim->GetCurLowerAnimType() == MoreActionClient::single_stun
		|| m_pAnim->GetCurLowerAnimType() == MoreActionClient::Intonate )
		return;

	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	char szBuf[256] = {0};
	if( IsPlayer() )
	{
		if( HasFightFlag(eFighting) || IsFightPose() )
		{
			// ��������ж��������Ҳ�����ͨ�������������ܴ��
			if( !(m_pAnim->IsUpperAnimPlayOver() || IsCurrNormalAttackAnim() ))
				return;

			if( IsHaveWeapon() )		//if����������.
			{
				_snprintf( szBuf, 255, "single_hurt" );
			}
			else
			{
				_snprintf( szBuf, 255, "hurt" );
			}
		}
		else
		{
			if( IsHaveWeapon() )		//if����������.
				_snprintf( szBuf, 255, "single_hurt" );
			else
				_snprintf( szBuf, 255, "hurt" );
		}
	}
	else
	{
		_snprintf( szBuf, 255, "hurt" );
	}

	if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
	{
		m_pAnim->PlayUpperAnim(	szBuf,
			MexAnimCtrl::eNormalPlay, 
			0,
			1,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime );
	}
	else
	{
		if( !IsMoving() )// �ƶ�ʱ�򲻲岥���� [1/6/2011 zhangjiayi]
		{
			m_pAnim->PlayInsertAnim( szBuf,
				MexAnimCtrl::eNormalPlay, 
				0,
				1, 
				MexAnimCtrl::eMaxTimeout );
		}		
	}
	unguard;
}

//�л��񵲶���
void CPlayer::SwitchDefendAnim( DWORD dwTimeOut )
{
	guardfunc;

	unguard;
}


//�л�����ܶ���
void	CPlayer::SwitchDodgeAnim(DWORD dwTimeOut /* = MexAnimCtrl::eMaxTimeout */)
{
	guardfunc;

	unguard;
}

extern bool g_bCloseApp;
bool Disconnectted( const bool bPressYesButton, void *pData )
{
	guardfunc;
	PostMessage( g_hWnd, WM_USER_CLOSE/*WM_CLOSE*/, 0, 0 );
	g_bCloseApp = true;
	return true;
	unguard;
}

void CPlayer::ClearActionQueue()
{
	guardfunc;
	m_actionQueue.Clear();
	//m_walkQueue.Clear();
	unguard;
}

void RenderPlayerInMiniMap( int iCharType,bool bRole,bool bTeammate,int x,int y )
{
	guardfunc;
	DWORD dwColor;
	//��С��ͼ�ϵ�npc
	bool draw_flag = false;
	//��ɫ
	const DWORD dwColorRole = D3DCOLOR_ARGB( 255,255, 255,0);
	const DWORD dwColorPlayer = D3DCOLOR_ARGB( 255, 0, 0, 255);
	const DWORD dwColorTeammate = D3DCOLOR_ARGB( 255, 200, 200, 255);
	const DWORD dwColorAI = D3DCOLOR_ARGB(255, 0, 0, 255);
	const DWORD dwColorNPC = D3DCOLOR_ARGB(255, 0, 255, 0);
	const DWORD dwColorItem = D3DCOLOR_ARGB( 255,0,255,255 );
	const DWORD dwColorMonster = D3DCOLOR_ARGB( 255, 255, 0, 0);

	switch( iCharType )
	{
	case Object_Player:		//��ʾ�Ǹ����
		if( bTeammate )
			dwColor = dwColorTeammate;
		else
			dwColor = dwColorPlayer;

		if( bRole )
			dwColor = dwColorRole;
		draw_flag = true;
		break;
	case Object_Npc:			//��ʾ�Ǹ��ű�npc
		dwColor = dwColorNPC;
		draw_flag = true;
		break;
	case Object_Item:			//��ʾ�Ǹ�����
		dwColor = dwColorItem;
		draw_flag = true;
		break;
	case Object_Monster:		//��ʾ�Ǹ�����
		dwColor = dwColorMonster;
		draw_flag = true;
		break;
	case Object_Effect:		//��ʾ�Ǹ���������
		break;
	}
	unguard;
}

BOOL CPlayer::IsBuildPlayer()
{
	return TRUE;
}

FLOAT CPlayer::GetPlayerHeight()
{
	FLOAT fHeight = 1.7;
	if( m_pAnim )
	{
		Box *pBBox = m_pAnim->GetWorldBBox();
		if( pBBox )
		{
			FLOAT fBoxHeight = ( pBBox->v[4].z - pBBox->v[0].z );
			fHeight += fBoxHeight;		
		}
	}
	if( m_pMountAnim && m_bMounting )
	{
		fHeight += 0.6f;
	}

	return fHeight;
}

Box* CPlayer::GetBox()
{
	GetWorldBBox();
	return NULL;
}

void CPlayer::RenderShadow( LPDIRECT3DDEVICE9 pDevice, DWORD dwColor /* = 0xffffffff */, 
						   float fTransparent /* = 1.0f */, float fPlayerTransparent /* = 1.0f */ )
{
	if( !m_pAnim )
		return;

	// NPC��������ʾ
	if( IsNpc() && IsHide() )
	{
		return;
	}

	if( m_fCurRenderAlpha > 0 )
	{
		if( m_bMounting )
		{
			if( m_pMountAnim )
			{
				m_pMountAnim->RenderShadow();
			}
			m_pAnim->RenderShadow();
		}
		else
		{
			if( m_bMorphing && m_pMorphAnim )
			{
				m_pMorphAnim->RenderShadow();
			}
			else
			{
				m_pAnim->RenderShadow();
			}
		}
	}
}

void CPlayer::RenderChar( LPDIRECT3DDEVICE9 pDevice,
						 BOOL bRenderShadow/*= FALSE*/,
						 int* pRetVertexCount/*=NULL*/,
						 int* pRetFaceCount/*=NULL*/)
{
	ProfilePlayerFun
		guardfunc;
	// NPC��������ʾ
	if( IsNpc() && IsHide() )
	{
		if( pRetVertexCount )
			*pRetVertexCount = 0;
		if( pRetFaceCount )
			*pRetFaceCount = 0;

		return;
	}

	// 	D3DLIGHT9 light = *GetGameSun();
	D3DLIGHT9 light = SwGlobal::GetRender()->GetD9Light(); 
	D3DXCOLOR oldLightAmbient = ((RendererDx*)GetEngine()->GetRenderer())->GetLightAmbient(LIGHT_INDEX_TERRAIN);
	D3DXCOLOR oldLightDiffuse = ((RendererDx*)GetEngine()->GetRenderer())->GetLightDiffuse(LIGHT_INDEX_TERRAIN);
	D3DXCOLOR lightAmbient = oldLightAmbient;
	D3DXCOLOR lightDiffuse = oldLightDiffuse;
	// 	BOOL bCanCombine = TRUE;
	BOOL bDark = FALSE;

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, (D3DXVECTOR3*)&light.Direction );

	if(!bRenderShadow && m_pCharEffectContainer && m_pCharEffectContainer->HasEffectLight() )
	{
		m_pCharEffectContainer->UpdateLight( g_dwLastFrameBeginTime , &light );
		lightAmbient += light.Ambient;
		// 		bCanCombine = FALSE;
	}

	if( !bRenderShadow && theApp->GetPlayerMgr()->GetMouseTargetPlayerSeverID() == m_stID /*&& IsRole()*/ )
	{
		lightAmbient.a = 1.0f;
		lightAmbient.r = lightAmbient.r * 1.5f;
		lightAmbient.g = lightAmbient.g * 1.5f;
		lightAmbient.b = lightAmbient.b * 1.5f;
		// 		bCanCombine = FALSE;
	}

	//��������������Ӱ��Ϣ
	if(!bRenderShadow && SwGlobal::GetWorldPicker()->IsShadow( m_x, m_y ))
	{
		lightDiffuse.r = lightDiffuse.r / 4.f;
		lightDiffuse.g = lightDiffuse.g / 4.f;
		lightDiffuse.b = lightDiffuse.b / 4.f;
		bDark = TRUE;
	}
	GetEngine()->GetRenderer()->SetLight( LIGHT_INDEX_PLAYER, &light );
	((RendererDx*)GetEngine()->GetRenderer())->SetLightAmbient(LIGHT_INDEX_TERRAIN, lightAmbient);
	((RendererDx*)GetEngine()->GetRenderer())->SetLightDiffuse(LIGHT_INDEX_TERRAIN, lightDiffuse);
	GetEngine()->GetRenderer()->LightEnable(LIGHT_INDEX_PLAYER,TRUE);

	int nPlayerVertices=0;
	int nPlayerFaces=0;
	int nOtherVertices=0;
	int nOtherFaces=0;

	if( m_fCurRenderAlpha > 0/* && m_bHasUpdateAnim */)
	{
		// 		std::map<int, std::vector<CombineModelData>>* pCombineData;
		// 		if( !bCanCombine )
		// 			pCombineData = NULL;
		// 		else if( bDark )
		// 			pCombineData = pCombineDataMapDark;
		// 		else
		// 			pCombineData = pCombineDataMap;

		if( m_bMounting )
		{
			if( m_pAnim && m_pAnim->GetMex() )
			{
				BOOL bRender = m_pAnim->Render( m_fCurRenderAlpha, NULL, &nPlayerVertices, &nPlayerFaces,  bRenderShadow,IsRenderParticleEmitters() );
				if( bRender && m_pMountAnim )
					m_pMountAnim->Render( m_fCurRenderAlpha, NULL, &nOtherVertices, &nOtherFaces, false ,IsRenderParticleEmitters());
			}
		}
		else
		{
			if( m_bMorphing )
			{
				if( m_pMorphAnim )
				{
					// added, jiayi, [2009/12/14]
					// ���ڰ�̯��ģ�������⴦������Ⱦavatar
					CAvatar* pAvatar = m_pMorphAnim->GetAvatar();
					if( m_bPrivateShopOpen )
						m_pMorphAnim->SetAvatar( 0 );
					m_pMorphAnim->Render( m_fCurRenderAlpha, NULL, &nOtherVertices, &nOtherFaces,  bRenderShadow,IsRenderParticleEmitters() );
					m_pMorphAnim->SetAvatar( pAvatar );
				}
			}
			else
			{
				if( m_pAnim /* && m_pAnim->GetMex() */ )
					m_pAnim->Render( m_fCurRenderAlpha, NULL, &nPlayerVertices, &nPlayerFaces,  bRenderShadow,IsRenderParticleEmitters() );
			}
		}

		RenderTaliMan();
		if( pRetVertexCount )
		{
			*pRetVertexCount = nPlayerVertices + nOtherVertices;
		}
		if( pRetFaceCount )
		{
			*pRetFaceCount = nPlayerFaces + nOtherFaces;
		}
	}

	GetEngine()->GetRenderer()->LightEnable(LIGHT_INDEX_PLAYER,FALSE);
	//���û�ȥ
	((RendererDx*)GetEngine()->GetRenderer())->SetLightAmbient(LIGHT_INDEX_TERRAIN, oldLightAmbient);
	((RendererDx*)GetEngine()->GetRenderer())->SetLightDiffuse(LIGHT_INDEX_TERRAIN, oldLightDiffuse);
	//	GetHREngine()->GetRenderer()->SetLight( 0, &g_World.m_lgtRoleSun );
	unguard;
}

bool CPlayer::IsShow( eHeadInfo eType )
{
	if( eType == eHeadInfo_Name )
	{
		if( IsItem() )			//��Ʒ
			return (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_ItemName );
		else if( IsMonster() )	//monster
		{
			// ���ɼ����ٻ���
			if( !IsVisibleToOtherPlayer() )
			{
				if( theHeroGame.GetPlayerMgr()->GetMe() )
				{
					// �����Լ����ٻ���
					if( theHeroGame.GetPlayerMgr()->GetMe()->GetID() != GetMasterID() )
						return false;
				}
				else
					return false;
			}


			if( !IsPet() )
				return (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_MonsterName );
			else
			{
				bool bShow = false;
				if( thePlayerRole.IsTeamMember( GetMasterName().c_str() ) )	//����
					bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerPetName );
				else
					bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerPetName );
				//����ж��Լ�
				if( theHeroGame.GetPlayerMgr()->GetMe() && GetMasterID() == theHeroGame.GetPlayerMgr()->GetMe()->GetID() )
				{
					bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfPetName );
				}
				return bShow;
			}
		}
		else if( IsNpc() )		// npc
		{
			const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(GetNpcID());
			if( pInfo && pInfo->_nType == eNT_Item )    // NPC��Item���ͣ�����Ҫ��ʾ����
				return true;
			else
				return (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_NpcName );
		}
		else if( IsPlayer() )
		{
			bool bShow = false;
			if( theHeroGame.GetPlayerMgr()->GetMe() && GetID() == theHeroGame.GetPlayerMgr()->GetMe()->GetID() )
			{
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfName );
			}
			else
			{
				if( thePlayerRole.IsTeamMember( GetName() ) )	//����
					bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerName );
				else
					bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerName );
			}
			return bShow;
		}
	}
	else if( eType == eHeadInfo_Hp )
	{
		if( IsItem() )			//��Ʒ
			return false;
		else if( IsMonster() )	//monster
		{
			// ���ɼ����ٻ���
			if( !IsVisibleToOtherPlayer() )
			{
				if( theHeroGame.GetPlayerMgr()->GetMe() )
				{
					// �����Լ����ٻ���
					if( theHeroGame.GetPlayerMgr()->GetMe()->GetID() != GetMasterID() )
						return false;
				}
				else
					return false;
			}

			if( !IsPet() )
				return (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_MonsterHp );
			else
			{
				bool bShow = false;
				if( thePlayerRole.IsTeamMember( GetMasterName().c_str() ) )	//����
					bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerPetHp );
				else
					bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerPetHp );
				//����ж��Լ�
				if( theHeroGame.GetPlayerMgr()->GetMe() && GetMasterID() == theHeroGame.GetPlayerMgr()->GetMe()->GetID() )
				{
					bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfPetHp );
				}
				return bShow;
			}
		}
		else if( IsNpc() )		// npc
			return (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_NpcHp );
		else if( IsPlayer() )
		{
			bool bShow = false;
			if( thePlayerRole.IsTeamMember( GetName() ) )	//����
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerHp );
			else
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerHp );
			//����ж��Լ�
			if( theHeroGame.GetPlayerMgr()->GetMe() && GetID() == theHeroGame.GetPlayerMgr()->GetMe()->GetID() )
			{
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfHp );
			}
			return bShow;
		}	
	}
	else if( eType == eHeadInfo_Mp )
	{
		if( theHeroGame.GetPlayerMgr()->GetMe() && GetID() ==
			theHeroGame.GetPlayerMgr()->GetMe()->GetID() )
		{
			return (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfMp );
		}		
		return false;
	}
	else if( eType == eHeadInfo_Title )
	{
		if( IsItem() || IsMonster() || IsPet() )			
			return false;

		else if( IsNpc() )		// npc
			return (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_NpcTitle );
		else if( IsPlayer() )
		{
			bool bShow = false;
			if( thePlayerRole.IsTeamMember( GetName() ) )	//����
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerTitle );
			else
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerTitle );
			//����ж��Լ�
			if( theHeroGame.GetPlayerMgr()->GetMe() && GetID() == theHeroGame.GetPlayerMgr()->GetMe()->GetID() )
			{
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfTitle );
			}
			return bShow;
		}
	}
	else if( eType == eHeadInfo_Guild )
	{
		if( IsItem() || IsMonster() || IsNpc() || IsPet() )
			return false;		
		else if( IsPlayer() )
		{
			bool bShow = false;
			if( thePlayerRole.IsTeamMember( GetName() ) )	//����
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerGuild );
			else
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerGuild );
			//����ж��Լ�
			if( theHeroGame.GetPlayerMgr()->GetMe() && GetID() == theHeroGame.GetPlayerMgr()->GetMe()->GetID() )
			{
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfGuild );
			}
			return bShow;
		}
		else if( IsPet() )
		{
			return true;
		}

	}
	else if( eType == eHeadInfo_Tong )
	{
		if( IsItem() || IsMonster() || IsNpc() || IsPet() )
			return false;	
		else if( IsPlayer() )
		{
			bool bShow = false;
			if( thePlayerRole.IsTeamMember( GetName() ) )	//����
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerTong );
			else
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerTong );
			//����ж��Լ�
			if( theHeroGame.GetPlayerMgr()->GetMe() && GetID() == theHeroGame.GetPlayerMgr()->GetMe()->GetID() )
			{
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfTong );
			}
			return bShow;
		}
	}
	else if( eType == eHeadInfo_Chat )
	{
		if( IsPlayer() )
		{
			bool bShow = false;
			if( thePlayerRole.IsTeamMember( GetName() ) )	//����
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_ChatTeam );
			else
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_ChatOther );
			//����ж��Լ�
			if( theHeroGame.GetPlayerMgr()->GetMe() && GetID() == theHeroGame.GetPlayerMgr()->GetMe()->GetID() )
			{
				bShow = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_ChatSelf );
			}
			return bShow;
		}
		else if( IsNpc() )
		{
			return (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_ChatNpc );
		}
		else if( IsMonster() )
		{
			return (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_ChatMonster );
		}
		else if ( IsItem() )
		{
			//���������ָ����ʾ�õģ���Ȼ�����������һ��ר��ָ����
			return true;
		}
	}
	return false;
}
HANDLE g_hDynamicLoadMap = 0;

void CPlayer::Render( LPDIRECT3DDEVICE9 pDevice, DWORD dwColor /* = 0xffffffff */, float fTransparent /* = 1.0f */, float fPlayerTransparent /* = 1.0f  */ )
{
	// NPC��������ʾ
	if( IsNpc() && IsHide() )
	{
		if( fontName_ )
			fontName_->SetVisible(false);

		return;
	}

	if(IsPet())
		ShowPetEffect();

	RenderText(pDevice);
	ProcessNpcAction();


	//return;
	// ��player������Ҳ��ǻ��
	BOOL bRender = TRUE;
	// ����Ƿ��������е�player,���������һ�����,����������Ⱦ,
	if( !IsActivePlayer() )
	{
		// �����Ҫ��,���ǻ�û�в��������������
		if( IsWillDie() && 
			!IsDeadOver() )
		{
			bRender = TRUE;;
		}
		else
		{
			bRender = FALSE;
		}
	}
	if( !bRender )
		return;

	//��ʧ�ĵ����ǲ���Ҫ��ͼ��
	if( IsItem() )
	{
		if( HQ_TimeGetTime() < m_dwDisplayAfterTime )
		{
			return;
		}
		// 
		// 		if( !m_bItemPlayedDropAnim && m_pAnim )
		// 		{
		// 			m_bItemPlayedDropAnim = true;
		// 			m_pAnim->PlayAnimByActionName( "itemborn",
		// 				MexAnimCtrl::eNormalPlay,
		// 				3000,
		// 				1,
		// 				MexAnimCtrl::eMaxTimeout,
		// 				0,
		// 				"itemidle",
		// 				MexAnimCtrl::eNormalPlay );
		// 		}
	}
	//
	Box* pBBox = GetWorldBBox();

	int x = 0, y = 0;
	Vector vPos( m_x, m_y, m_z );
	bool bShow = getwsCamera()->GetMeCamera()->WorldToScreen( vPos, &x, &y, SCREEN_WIDTH, SCREEN_HEIGHT );
	if( !bShow )
		return;

	y += 8;

	// ��ʾ�����������С�����Բ    added by ZhuoMeng.Hu		[1/10/2011]
	if( CPlayer::IsServerTerrainRectShow() )
	{
		CPlayer::DrawServerTerrainRect( this );
	}
	if( CPlayer::IsHeightMapRectShow() && CPlayer::IsHeightMapDataLoad() )
	{
		CPlayer::DrawHeightMapRect( this );
	}
	if( CPlayer::IsMyCircleShow() )
	{
		CPlayer::DrawMyCircle( this );
	}
	if( CPlayer::IsMouseCircleShow() )
	{
		CPlayer::DrawMouseCircle( this );
	}


	if( g_bShowRoleAttackRange && IsRole() )
	{
		GetDrawer()->DrawCircleFlat3D( m_x, m_y, m_z+1, m_fBodySize + g_fAddRoleAttackRange, 32, 0xffffffff );
	}

	if( MyTeamMember && !m_bDueler )
	{
		INT nIdx = 0;
		switch( ManipleID ) {
		case 0:
		case 1:
		case 2:
		case 3:
			nIdx = ManipleID;
			break;
		default:
			nIdx = 0;
			break;
		}
		GTeamFlag[nIdx].SetPosition( m_x, m_y, m_z + GetPlayerHeight() + 0.6f );
		GTeamFlag[nIdx].UpdateByParam( HQ_TimeGetTime() );
		GTeamFlag[nIdx].Render( 1.0f );
	}

	if (IsNeedShowShadowDecal())
	{
		float deltaX = m_tx - m_x;
		float deltaY = m_ty - m_y;
		if (m_bMoving || !m_LastRenderShadowDecal || abs(deltaX) > 0.01 || abs(deltaY) > 0.01 )
		{
			UpdateDecalShadow();
		}
	}
	else
		m_LastRenderShadowDecal = FALSE;

	float deltaX = m_tx - m_x;
	float deltaY = m_ty - m_y;
	float fDeltaLength = sqrt(deltaX*deltaX + deltaY*deltaY);

	m_distanceDelta += fDeltaLength;
	UpdateFootPrint();

	m_distanceDeltaForDynamicLoad += fDeltaLength;
	if (m_distanceDeltaForDynamicLoad > 0.05f)
	{
		SetEvent(g_hDynamicLoadMap);
		m_distanceDeltaForDynamicLoad = 0;
	}


	m_tx = m_x;
	m_ty = m_y;	
	// #ifdef _DEBUG
	// 	if( m_bRole )
	// 	{
	// 		char szBuf[256];
	// 		MeSprintf_s( szBuf,sizeof(szBuf)/sizeof(char) -1 ,"%s:(%ld,%ld)",m_pTempMapName,m_ptLoc.x,m_ptLoc.y );
	// 		FontSystem::DrawText(szBuf, 0, 30, 0, 0xff7f7f7f, 0, false);
	// 	}
	// #endif
	//	unguard;
}

void CPlayer::RenderPrivateShopInfo()
{
	if ( m_pPrivateShopInfo )
	{
		ShowPrivateShopInfo();
		// ���zֵ		
		RendererDx* pRenderDx = ( RendererDx*)GetEngine()->GetRenderer();		
		D3DXMATRIXA16 matWVP = pRenderDx->GetWorldViewProjection();				
		D3DXVECTOR3 vTransformedPos;
		D3DXVec3TransformCoord( &vTransformedPos, &GetPos(), &matWVP );
		m_pPrivateShopInfo->SetBackPicZValue( vTransformedPos.z );
		m_pPrivateShopInfo->SetRenderTextWithZ( true );
		FontSystem::SetGlobalZ( vTransformedPos.z, m_pPrivateShopInfo->GetFontIndex() );
		m_pPrivateShopInfo->Render();
		FontSystem::SetGlobalZ( 0, m_pPrivateShopInfo->GetFontIndex() );		
	}
}

void CPlayer::RenderTeamBattleFlag()
{
	static float xo = 1;
	static float yo = 110;
	static float fontSize = 12;
	static float picWidth = 24;
	static float fontScale = 28/12;
	static float lineHeight = 22;

	if(!thePlayerRole.IsTeamBattleInMap())
		return;
	if (fontName_ && fontName_->IsVisible() && IsShow(CPlayer::eHeadInfo_Name))
	{
		D3DXVECTOR3 vPos2D = fontName_->GetPosition();
		float x =  vPos2D.x + RTTFont::RTT_TEX_WIDTH / 2;
		float y =  vPos2D.y;

		TeamInfo* teamInfo = thePlayerRole.GetTeamInfo(thePlayerRole.GetTeamMemberId(GetName()));

		CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if(!pMe)
			return;

		char szFilePath[255] = {0};

		bool bFlag = false;
		for(int i=0;i<s_CUI_ID_FRAME_TeamBattleResult.m_vecRecordInfoNoSort.size();++i)
		{
			if(GetTeamId()==s_CUI_ID_FRAME_TeamBattleResult.m_vecRecordInfoNoSort[i].dwID)
			{
				char str[256];
				MeSprintf_s( str,255,"ui\\common\\BattleTeam%d.tga",i+1);
				MeSprintf_s( szFilePath,sizeof(szFilePath)/sizeof(char) - 1, "%s\\%s", GetRootPath(), str );
				bFlag = true;
				break;
			}


			if (thePlayerRole.IsTeamMember(GetName()))
			{
				if(thePlayerRole.GetGroupId()==s_CUI_ID_FRAME_TeamBattleResult.m_vecRecordInfoNoSort[i].dwID)
				{
					char str[256];
					MeSprintf_s( str,255,"ui\\common\\BattleTeam%d.tga",i+1);
					MeSprintf_s( szFilePath,sizeof(szFilePath)/sizeof(char) - 1, "%s\\%s", GetRootPath(), str );
					bFlag = true;
					break;
				}
			}
		}
		if(bFlag)
		{
			std::wstring wideStr = Common::_tstring::toWideString(fontName_->GetText().c_str());
			int startCP = 0;
			int endCP = wideStr.length();
			int width = (float)FontSystem::GetTextWidth(fontName_->GetFontIndex(),wideStr,startCP,endCP,false) * ControlObject::GetSCALE(NULL) / 2.f;
			float w = picWidth * ControlObject::GetSCALE(NULL);
			RECT rc;
			rc.left = x + width ;
			rc.right = rc.left + w;
			rc.top = y - lineHeight * ControlObject::GetSCALE(NULL);
			rc.bottom = rc.top + w;

			int picId = -1;
			theControlPictureManager.BitBlt( &picId,
				szFilePath,
				&rc, NULL, 0xffffffff, 0);
		}
	}

	//     if (fontName_ && fontName_->IsVisible() && IsShow(CPlayer::eHeadInfo_Name))
	//     {
	//         Vector vCenter( fontName_->GetPosition().x, fontName_->GetPosition().y, fontName_->GetPosition().z );
	//         int x = 0, y = 0;
	//         if( getwsCamera()->GetMeCamera()->WorldToScreen( vCenter, &x, &y, SCREEN_WIDTH, SCREEN_HEIGHT ) )
	//         {
	//             if (IsRole() && !IsMounting())
	//                 x = SCREEN_WIDTH / 2;
	// 
	//             CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	//             if(!pMe)
	//                 return;
	// 
	//             char szFilePath[255] = {0};
	// 
	// 			bool bFlag = false;
	// 			for(int i=0;i<s_CUI_ID_FRAME_TeamBattleResult.m_vecRecordInfoNoSort.size();++i)
	// 			{
	// 				if(GetTeamId()==s_CUI_ID_FRAME_TeamBattleResult.m_vecRecordInfoNoSort[i].dwID)
	// 				{
	// 					char str[256];
	// 					MeSprintf_s( str,255,"ui\\common\\BattleTeam%d.tga",i+1);
	// 					MeSprintf_s( szFilePath,sizeof(szFilePath)/sizeof(char) - 1, "%s\\%s", GetRootPath(), str );
	// 					bFlag = true;
	// 					break;
	// 				}
	// 
	// 
	// 				if (thePlayerRole.IsTeamMember(GetName()))
	// 				{
	// 					if(thePlayerRole.GetGroupId()==s_CUI_ID_FRAME_TeamBattleResult.m_vecRecordInfoNoSort[i].dwID)
	// 					{
	// 						char str[256];
	// 						MeSprintf_s( str,255,"ui\\common\\BattleTeam%d.tga",i+1);
	// 						MeSprintf_s( szFilePath,sizeof(szFilePath)/sizeof(char) - 1, "%s\\%s", GetRootPath(), str );
	// 						bFlag = true;
	// 						break;
	// 					}
	// 				}
	// 			}
	// 
	// 			if(bFlag)
	// 			{
	// 				// ���zֵ
	// 				RendererDx* pRenderDx = ( RendererDx*)GetEngine()->GetRenderer();
	//                 D3DXMATRIX matWorld;
	//                 D3DXMatrixIdentity( &matWorld );
	//                 pRenderDx->SetTransform( D3DTS_WORLD, (FLOAT*)&matWorld );
	// 				D3DXMATRIXA16 matWVP = pRenderDx->GetWorldViewProjection();				
	// 				D3DXVECTOR3 vTransformedPos;
	// 				D3DXVec3TransformCoord( &vTransformedPos, &GetPos(), &matWVP );
	// 
	// 				int nLen = strlen( GetName() ) + 1;
	// 				int width = (float)nLen * fontSize * ControlObject::GetSCALE(NULL) / 2.f;
	// 
	// 				float w = picWidth * ControlObject::GetSCALE(NULL);
	// 
	// 				std::string::size_type s = 0;
	// 				std::string::size_type p = 0;
	// 				int lineNumber = 0;
	// 				while ((p = fontName_->GetText().find('\n', s)) != std::string::npos)
	// 				{
	// 					s = p + 1;
	// 					++lineNumber;
	// 				}
	// 
	// 				RECT rc;
	// 				rc.left = x + xo * width /*- w*/;
	// 				rc.right = rc.left + w;
	// 				rc.top = y - yo * ControlObject::GetSCALE(NULL) + lineNumber * lineHeight * ControlObject::GetSCALE(NULL);
	// 				rc.bottom = rc.top + w;
	// 
	// 				int picId = -1;
	// 				theControlPictureManager.BitBlt( &picId,
	// 					szFilePath,
	// 					&rc, NULL, 0xffffffff, vTransformedPos.z );
	// 			}
	//         }
	//     }
}
void CPlayer::RenderTeamFlag()
{
	// 	static float xo = 1;
	// 	static float yo = 110;
	// 	static float fontSize = 12;
	static float picWidth = 24;
	// 	static float fontScale = 28/12;
	static float lineHeight = 12;
	int nRow_Text = 1;
	if (!thePlayerRole.IsTeamMember(GetName()))
		return;

	if (fontName_ && fontName_->IsVisible() && IsShow(CPlayer::eHeadInfo_Name))
	{
		D3DXVECTOR3 vPos2D = fontName_->GetPosition();
		float x =  vPos2D.x + /*RTTFont::RTT_TEX_WIDTH / 2*/fontName_->GetWidth() / 2;
		float y =  vPos2D.y;
		/*if (HasGuild())
		{
		++nRow_Text;
		}
		if (m_iFamilyID > 0 )
		{
		++nRow_Text;
		}
		if (IsShow( CPlayer::eHeadInfo_Title ))
		{
		++nRow_Text;
		}*/
		nRow_Text = fontName_->GetColorsCount();
		if (IsShow(CPlayer::eHeadInfo_Hp))
		{//���Ѫ����ʾ�����ͼ���ʱ����һ��
			--nRow_Text;
		}

		TeamInfo* teamInfo = thePlayerRole.GetTeamInfo(thePlayerRole.GetTeamMemberId(GetName()));
		char filename[256];
		if (teamInfo && teamInfo->bHeader)
			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\Data\\Ui\\Common\\TeamLeader.tga", GetRootPath() );
		else
			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\Data\\Ui\\Common\\TeamPlayer.tga", GetRootPath() );

		//std::wstring wideStr = Common::_tstring::toWideString( m_szFinalName.c_str() );//Common::_tstring::toWideString(fontName_->GetText().c_str());
		std::wstring wideStr = Common::_tstring::toWideString( m_szDisplayName );  //ֻ������

		//lyh�޸Ķ�������λ��

		std::string _text ="";
		std::string strCountryString = CountryFunction::GetCountryNameById( GetRealCountry() );
		CPlayer* pPlayerMe = theHeroGame.GetPlayerMgr()->GetMe();


		//if (mHeroID != INVALID_HERO_ID)
		//{
		//	CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(mHeroID);
		//	if (itemHero == NULL)
		//		return;

		//	_text += itemHero->hero_name + "[" + m_szDisplayName + "]"; //�������� + ��ɫ����

		//	if( pPlayerMe && ( strCountryString.size() > 0 ) )
		//	{
		//		if( pPlayerMe != this )
		//		{
		//			if( pPlayerMe->GetRealCountry() != GetRealCountry() )
		//			{
		//				_text +=  " ("  + strCountryString + ")";//�������� + ��ɫ���� + ��������
		//			}
		//		}

		//	}

		//	wideStr = Common::_tstring::toWideString( _text.c_str() ); 			
		//}else
		{
			if( pPlayerMe && ( strCountryString.size() > 0 ) )
			{
				if( pPlayerMe != this )
				{
					if( pPlayerMe->GetRealCountry() != GetRealCountry() )
					{
						_text += m_szDisplayName;
						_text +=  " ("  + strCountryString + ")"; // ��ɫ���� + ��������
						wideStr = Common::_tstring::toWideString( _text.c_str() ); 	
					}
				}

			}


		}

		/*float picCountryWidth = 0.0f;
		float picCountryHeight = 0.0f;

		CountryTitleConfig::CountryTitleVector* vecTitle = theCountryTitleConfig.GetCountryTitleVec( GetRealCountry() );
		
		if( vecTitle && GetRealCountry() && GetCountryTitle() && CountryFunction::CheckIsCountryTitle(GetCountryTitle()) )
		{
			uint16 unCTitle = GetCountryTitle() - 1;
			if ( unCTitle >= 0 && unCTitle < (*vecTitle).size() )
			{
				picCountryWidth = (float)((*vecTitle)[unCTitle].nPicWidth) * ControlObject::GetSCALE(NULL);
				picCountryHeight = (float)((*vecTitle)[unCTitle].nPicHeight) * ControlObject::GetSCALE(NULL);
			}
		}*/


		int startCP = 0;
		int endCP = wideStr.length();
		int width = (float)FontSystem::GetTextWidth(fontName_->GetFontIndex(),wideStr,startCP,endCP,false) * ControlObject::GetSCALE(NULL) /*/ 2.f*/;
		int nHight= FontSystem::GetFontHeight( fontName_->GetFontIndex() ) + fontName_->GetLineSpace();
		float w = picWidth * ControlObject::GetSCALE(NULL);
		RECT rc;
		rc.left = x + width/2 /*- w*/ + 5 /*- picCountryWidth*/;
		rc.right = rc.left + w;
		rc.top = y + (nRow_Text-1)*(nHight) * ControlObject::GetSCALE(NULL);
		rc.bottom = rc.top + w;

		int picId = -1;
		theControlPictureManager.BitBlt( &picId,
			filename,
			&rc, NULL, 0xffffffff, 0 );
	}

	// 	float ix = 0, iy = 0;
	// 	if (fontName_ && fontName_->IsVisible() && IsShow(CPlayer::eHeadInfo_Name))
	// 	{
	// 		Vector vCenter( fontName_->GetPosition().x, fontName_->GetPosition().y, fontName_->GetPosition().z );
	// 		int x = 0, y = 0;
	// 		if( getwsCamera()->GetMeCamera()->WorldToScreen( vCenter, &x, &y, SCREEN_WIDTH, SCREEN_HEIGHT ) )
	// 		{
	// 			if (IsRole() && !IsMounting())
	// 				x = SCREEN_WIDTH / 2;
	// 
	// 			TeamInfo* teamInfo = thePlayerRole.GetTeamInfo(thePlayerRole.GetTeamMemberId(GetName()));
	// 
	// 			char filename[256];
	// 			if (teamInfo && teamInfo->bHeader)
	// 				MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\Data\\Ui\\Common\\TeamLeader.tga", GetRootPath() );
	// 			else
	// 				MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\Data\\Ui\\Common\\TeamPlayer.tga", GetRootPath() );
	// 
	// 			// ���zֵ
	// 			RendererDx* pRenderDx = ( RendererDx*)GetEngine()->GetRenderer();
	//             D3DXMATRIX matWorld;
	//             D3DXMatrixIdentity( &matWorld );
	//             pRenderDx->SetTransform( D3DTS_WORLD, (FLOAT*)&matWorld );
	// 			D3DXMATRIXA16 matWVP = pRenderDx->GetWorldViewProjection();				
	// 			D3DXVECTOR3 vTransformedPos;
	// 			D3DXVec3TransformCoord( &vTransformedPos, &GetPos(), &matWVP );
	// 
	// 			int nLen = strlen( GetName() ) + 1;
	// 			int width = (float)nLen * fontSize * ControlObject::GetSCALE(NULL) / 2.f;
	// 
	// 			float w = picWidth * ControlObject::GetSCALE(NULL);
	// 
	// 			std::string::size_type s = 0;
	// 			std::string::size_type p = 0;
	// 			int lineNumber = 0;
	// 			while ((p = fontName_->GetText().find('\n', s)) != std::string::npos)
	// 			{
	// 				s = p + 1;
	// 				++lineNumber;
	// 			}
	// 
	// 			RECT rc;
	// 			rc.left = x - xo * width - w;
	// 			rc.right = rc.left + w;
	// 			rc.top = y - yo * ControlObject::GetSCALE(NULL) + lineNumber * lineHeight * ControlObject::GetSCALE(NULL);
	// 			rc.bottom = rc.top + w;
	// 
	// 			int picId = -1;
	// 			theControlPictureManager.BitBlt( &picId,
	// 				filename,
	// 				&rc, NULL, 0xffffffff, vTransformedPos.z );
	// 
	// 		}
	// 	}
}

void CPlayer::RenderRankTitle()
{
	if ( !IsShowRankTitle() )
		return;

	if ( fontName_ && fontName_->IsVisible() && IsShow(CPlayer::eHeadInfo_Name) )
	{
		D3DXVECTOR3 vPos2D = fontName_->GetPosition();
		float x =  vPos2D.x;
		float y =  vPos2D.y;

		char filename[256];

		RankTitleConfig::RankTitleVector& vecTitle = theRankTitleConfig.GetRankTitleVec();
		short curId = GetRankTitleId();
		if ( curId >= 0 && curId < vecTitle.size() )
			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\%s", GetRootPath(), vecTitle[curId].strPic.c_str() );
		else
			return;

		float picWidth = (float)vecTitle[curId].nPicWidth;
		float lineHeight = (float)vecTitle[curId].nPicHeight;

		int width = fontName_->GetWidth();
		int nHight= FontSystem::GetFontHeight( fontName_->GetFontIndex() ) + fontName_->GetLineSpace();
		RECT rc;
		rc.left = x + width/2 - picWidth/2;
		rc.right = rc.left + picWidth;
		rc.top = y - lineHeight;
		rc.bottom = rc.top + lineHeight;

		int picId = -1;
		theControlPictureManager.BitBlt( &picId,
			filename,
			&rc, NULL, 0xffffffff, 0 );

	}
}

void CPlayer::RenderCountryTitle()
{
	if( !GetRealCountry() || !GetCountryTitle() || !CountryFunction::CheckIsCountryTitle(GetCountryTitle()) )
		return;

	if (fontName_ && fontName_->IsVisible() && IsShow(CPlayer::eHeadInfo_Name))
	{
		D3DXVECTOR3 vPos2D = fontName_->GetPosition();
		float x =  vPos2D.x + fontName_->GetWidth() / 2;
		float y =  vPos2D.y;

		int nRow_Text = 1;
		nRow_Text = fontName_->GetColorsCount();
		if (IsShow(CPlayer::eHeadInfo_Hp))
		{//���Ѫ����ʾ�����ͼ���ʱ����һ��
			--nRow_Text;
		}

		char filename[256];

		CountryTitleConfig::CountryTitleVector* vecTitle = theCountryTitleConfig.GetCountryTitleVec( GetRealCountry() );
		if ( !vecTitle )
			return;

		uint16 unCTitle = GetCountryTitle() - 1;
		/*if ( GetCountryTitle() == CountryDefine::Title_QueenMale )
			unCTitle = CountryTitle_QueenMale;*/
		if ( unCTitle < 0 || unCTitle >= (*vecTitle).size() )
			return;

		MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\%s", GetRootPath(), (*vecTitle)[unCTitle].strPic.c_str() );

		float picWidth = (float)((*vecTitle)[unCTitle].nPicWidth);
		float picHeight = (float)((*vecTitle)[unCTitle].nPicHeight);

		std::wstring wideStr = Common::_tstring::toWideString( m_szDisplayName );  //ֻ������

		std::string _text ="";
		std::string strCountryString = CountryFunction::GetCountryNameById( GetRealCountry() );
		CPlayer* pPlayerMe = theHeroGame.GetPlayerMgr()->GetMe();

		if( pPlayerMe && ( strCountryString.size() > 0 ) )
		{
			if( pPlayerMe != this )
			{
				if( pPlayerMe->GetRealCountry() != GetRealCountry() )
				{
					_text += m_szDisplayName;
					_text +=  " ("  + strCountryString + ")"; // ��ɫ���� + ��������
					wideStr = Common::_tstring::toWideString( _text.c_str() ); 	
				}
			}

		}

		int startCP = 0;
		int endCP = wideStr.length();
		int width = (float)FontSystem::GetTextWidth(fontName_->GetFontIndex(),wideStr,startCP,endCP,false);
		int nHight= FontSystem::GetFontHeight( fontName_->GetFontIndex() ) + fontName_->GetLineSpace();
		RECT rc;
		rc.left = x - width/2 - picWidth;
		rc.right = rc.left + picWidth;
		rc.top = y + (nRow_Text-1)*nHight;
		rc.bottom = rc.top + picHeight;

		int picId = -1;
		theControlPictureManager.BitBlt( &picId,
			filename,
			&rc, NULL, 0xffffffff, 0 );
	}
}

void CPlayer::RenderText2D( LPDIRECT3DDEVICE9 pDevice )
{

}

void CPlayer::SetPetNameColor(CPlayer* pMaster, DWORD& color)
{
	if (thePlayerRole.GetInfluence() == CampDefine::NoneCamp || !pMaster)
	{
		return;
	}

	pMaster->SetNameColorByInfluence(color);
}

void CPlayer::SetNameColorByInfluence(DWORD& color)
{
	if (thePlayerRole.GetInfluence() == CampDefine::NoneCamp)
	{
		return;
	}

	if (thePlayerRole.GetInfluence() == GetInfluence())
	{
		color = Color_Config.getColor(CC_PlayerNormal);
	}
	else
	{
		color = Color_Config.getColor(CC_PlayerEnemy);
	}
}

const char* GetGuildPositionByID(int nPosition)
{
	switch (nPosition)
	{
	case GuildDefine::Position_Member:
		return theXmlString.GetString(eText_Guild_Bangzhong);
	case GuildDefine::Position_FamilyMaster:
		return theXmlString.GetString(eText_Guild_Tangzhu);
	case GuildDefine::Position_ViceMaster:
		return theXmlString.GetString(eText_Guild_ViceMaster);
	case GuildDefine::Position_Master:
		return theXmlString.GetString(eText_Guild_Master);
	default:
		return "";
	}
}

void CPlayer::RenderText(LPDIRECT3DDEVICE9 pDevice)
{
	if(!pDevice)
		return;

	if( IsNpc() && IsHide() )
	{
		if( fontName_ )
			fontName_->SetVisible(false);

		return;
	}

	// ����ǵ������͵�NPC, ����ʾ���ֵ���Ϣ, ���Ұ�ģ�͵�BOX����Ϊ�㹻С, ��1
	if (IsNpc() && GetNpcType() == ENpcType::eNT_Elevator)
	{
		if( fontName_ )
			fontName_->SetVisible(false);
		return;
	}

	if (!fontName_ )
	{		
		// 		if( m_bNameMulted )
		// 			return;
		// 
		// 		Mex2LoadReq* pReq = MeLoopThreadMan::Instance()->CreateLoadReq( Mex2LoadReq::ePlayerName );
		// 		if( !pReq )
		// 			return;
		// 		PlayerNameReq* pNameReq = dynamic_cast<PlayerNameReq*>( pReq );
		// 		if( !pNameReq )
		// 			return;
		// 
		// 		pNameReq->m_pPlayer = this;
		// 		AddRef();
		// 		PostMexLoadingReq( pNameReq );
		// 		m_bNameMulted = true;
		RTTFont* pFontName = Font3DManager::Instance()->CreateFont3D(RTTFont::RTT_TEX_WIDTH,
			gCfg.m_szNameFontName, gCfg.m_nNameFontSize, false, gCfg.m_isNameFontBold);
		pFontName->SetCamera(getwsCamera()->GetMeCamera());
		pFontName->SetVisible( true );	
		SetFontObject( pFontName );
	}
	fontName_->SetVisible( true );
	if (m_pHpPB3D)
		m_pHpPB3D->SetVisible(false);
	if (m_pMpPB3D)
		m_pMpPB3D->SetVisible(false);
	if (m_pFpPB3D)
		m_pFpPB3D->SetVisible(false);

	static float ps1 = 0.4f;
	static float ps2 = 0.02f;

	static float ps3 = 0.394f;
	static float ps4 = 0.014f;
	if (!m_pHpPB3D && ((IsMonster() && (GetMonsterType() < 5 || GetMonsterType() == eMT_Pet) ) || IsPlayer()))
	{
		D3DXVECTOR2 backUV[4];
		backUV[0] = D3DXVECTOR2(0.0f, 0.0f);
		backUV[1] = D3DXVECTOR2((180.f - 0.5f) / 256.f, 0.0f);
		backUV[2] = D3DXVECTOR2((180.f - 0.5f) / 256.f, (12.f - 0.5f) / 256.f);
		backUV[3] = D3DXVECTOR2(0.0f, (12.f - 0.5f) / 256.f);

		D3DXVECTOR2 progressUV[4];
		progressUV[0] = D3DXVECTOR2((2.f - 0.5f) / 256.f, (14.f - 0.5f) / 256.f);
		progressUV[1] = D3DXVECTOR2((178.f - 0.5f) / 256.f, (14.f - 0.5f) / 256.f);;
		progressUV[2] = D3DXVECTOR2((178.f - 0.5f) / 256.f, (24.f - 0.5f) / 256.f);
		progressUV[3] = D3DXVECTOR2((2.f - 0.5f) / 256.f, (24.f - 0.5f) / 256.f);

		m_pHpPB3D = MeNew ProgressBar3D();
		if(!m_pHpPB3D)
			return;

		HRESULT hr = m_pHpPB3D->Create(pDevice, "Data\\UI\\Common\\Progress.dds", backUV, progressUV, ps1, ps2, ps3, ps4, D3DCOLOR_ARGB(255, 175, 19, 19), D3DCOLOR_ARGB(255, 42, 40, 40));
		if(SUCCEEDED(hr))
			m_pHpPB3D->SetCamera(getwsCamera()->GetMeCamera());
		else
		{
			SAFE_DELETE(m_pHpPB3D);
			return;
		}

		if (IsRole())
		{
			m_pMpPB3D = MeNew ProgressBar3D();
			if(!m_pMpPB3D)
				return;

			hr = m_pMpPB3D->Create(pDevice, "Data\\UI\\Common\\Progress.dds", backUV, progressUV, ps1, ps2, ps3, ps4, D3DCOLOR_ARGB(255, 32, 144, 176), D3DCOLOR_ARGB(255, 42, 40, 40));
			if(SUCCEEDED(hr))
				m_pMpPB3D->SetCamera(getwsCamera()->GetMeCamera());
			else
			{
				SAFE_DELETE(m_pMpPB3D);
				return;
			}

			m_pFpPB3D = MeNew ProgressBar3D();
			if(!m_pFpPB3D)
				return;

			hr = m_pFpPB3D->Create(pDevice, "Data\\UI\\Common\\Progress.dds", backUV, progressUV, ps1, ps2, ps3, ps4, D3DCOLOR_ARGB(255, 216, 196, 76), D3DCOLOR_ARGB(255, 42, 40, 40));
			if(SUCCEEDED(hr))
				m_pFpPB3D->SetCamera(getwsCamera()->GetMeCamera());
			else
			{
				SAFE_DELETE(m_pFpPB3D);
				return;
			}
		}
	}

	if ( ( (!m_cFightStatus.IsHide() || m_bRole) &&  !IsDisableCollection() )
		|| theApp->GetPlayerMgr()->GetMouseTargetPlayerSeverID() == m_stID  )
	{		
		if (m_pHpPB3D && IsShow( CPlayer::eHeadInfo_Hp ) )
			m_pHpPB3D->SetVisible(true);
		else if( m_pHpPB3D )
			m_pHpPB3D->SetVisible(false);
		if (m_pMpPB3D && IsShow( CPlayer::eHeadInfo_Mp ) )
			m_pMpPB3D->SetVisible(true);
		else if( m_pMpPB3D )
			m_pMpPB3D->SetVisible(false);
	}
	else
	{
		fontName_->SetVisible(false);
		if (m_pHpPB3D)
			m_pHpPB3D->SetVisible(false);
		if (m_pMpPB3D)
			m_pMpPB3D->SetVisible(false);
		if (m_pFpPB3D)
			m_pFpPB3D->SetVisible(false);
		return;
	}

	D3DXVECTOR3 fontPos;
	fontPos = GetPos();
	static float s_fOffset = 0.0f/*-0.2f*/; //modified by zmy
	fontPos.z = ( GetWorldBBox() ? GetWorldBBox()->v[7].z : m_z ) + s_fOffset;

	D3DXVECTOR3 d = getwsCamera()->GetMeCamera()->GetEyePt() - fontPos;
	float toPosDist = D3DXVec3Length(&d);



	if ( (IsMonster()||IsPlayer()) )
	{
		if (m_pHpPB3D && !IsShow( CPlayer::eHeadInfo_Hp ))
			m_pHpPB3D->SetVisible(false);
		if (m_pMpPB3D && !IsShow( CPlayer::eHeadInfo_Mp ))
			m_pMpPB3D->SetVisible(false);
	}

	if (toPosDist > gCfg.m_fNameShowDistance && theApp->GetPlayerMgr()->GetMouseTargetPlayerSeverID() != m_stID)
	{
		fontName_->SetVisible(false);
		if (m_pHpPB3D)
			m_pHpPB3D->SetVisible(false);
		if (m_pMpPB3D)
			m_pMpPB3D->SetVisible(false);
		if (m_pFpPB3D)
			m_pFpPB3D->SetVisible(false);
		return;
	}

	float fontScale = 1.0f;

	DWORD color = 0xffffffff;
	DWORD color1 = 0xffffffff;
	DWORD color2 = 0xffffffff;
	DWORD color3 = 0xffffffff;
	DWORD color4 = 0xffffffff;

	if (fontName_)
		fontName_->ClearColor();

	std::string text;

	// ���ݳƺź;����Z��ƫ�Ƶ����ű���
	float offsetZScale = 0.02f;

	switch (m_stCharType)
	{
	case Object_Player:
		// ��̯״̬������ͷ�ϵ�������Ϣ������ʾ     modified by ZhuoMeng.Hu		[12/24/2010]
		if( !CSystemStallage::Instance()->IsPlayerInStalling( GetID() ) )
		{
			float baroffy = 0.34f;
			static float fTemp = 0.2f;
			static float fTemp1 = 0.3f;
			static float fTemp2 = 0.12f;
			static float fTemp3 = 0.11f;
			std::vector<DWORD> colors;

			/*
			* Author: 2012-11-20 15:23:47 wangshuai
			* Desc:   ֻ��Ŀ�����ʾ�������ּ�ְ��
			*/
			if (HasGuild() /*&& GetID() == theHeroGame.GetPlayerMgr()->GetLockPlayerID()*/)
			{
				const char* szGuildName = GetGuildName();
				if (szGuildName && strlen(szGuildName) > 0 && IsShow( CPlayer::eHeadInfo_Guild ))
				{
					text += szGuildName;
					//text += /*CountryFunction::GetGuildTitleNameById(GetCountryTitle())*/GetGuildPositionByID( GetGangPosition() );
					text += "\n";
					// 				if((pTile->GetCanPk()  == MapConfig::MapData::EPKM_Allow_PK)/*&& thePlayerRole.GetGangMgr()->guildRelation(this) == GR_ADVERSE)*/)
					// 				{
					// 					colors.push_back(Color_Config.getColor(CC_PlayerEnemy));
					// 				}
					// 				else
					{
						colors.push_back(Color_Config.getColor(CC_Guild));
					}
					if (IsRole() || m_pPrivateShopInfo)
						offsetZScale += fTemp3;
					else
						offsetZScale += fTemp1;
					baroffy -= 0.1f;
				}
			}

			//��ʾ��������
			if ( m_iFamilyID > 0 )
			{
				FamilyDefine::FamilySimpleInfo* simpleInfo = CSystemFamily::Instance()->GetFamilySimpleInfo( m_iFamilyID );
				text += simpleInfo->GetFamilyName();
				if( m_iFamilyPos == FamilyDefine::Position_Leader )
				{
					text += theXmlString.GetString(eText_FamilyLeader);
				}
				text +="\n";
				colors.push_back(0xFF00FF00);
			}

			const char* szTitle = NULL;
			//ĿǰҪô��ʾ���飬Ҫô��ʾ�ƺ�
			//			if(IsShowSignature())
			//			{
			//                szTitle = GetSignature();
			//			}
			//			else
			//			{
			//				szTitle = GetTitle().c_str();
			//			}
			bool Signature = false;
			if(/*!IsShowRankTitle() &&*/ !IsShowSignature() && strlen(GetTitle().c_str()) == 0)
			{
				szTitle = "";
			}
			else if(strlen(GetTitle().c_str()) > 0 && !IsShowSignature() /*&& !IsShowRankTitle()*/)
			{	
				szTitle = GetTitle().c_str();
			}
			else if( IsShowSignature() /*&& !IsShowRankTitle()*/ )
			{
				szTitle = GetSignature();
				Signature = true;
			}
			/*else if ( IsShowRankTitle() )
			{
				RankTitleConfig::RankTitleVector& vecTitle = theRankTitleConfig.GetRankTitleVec();
				short curId = GetRankTitleId();
				if ( curId >= 0 && curId < vecTitle.size() )
					szTitle = vecTitle[curId].strName.c_str();
				else
					szTitle = "";
				Signature = true;
			}*/

			//-------- ���ҳƺ�			added by zhuomeng.hu		[9/10/2010]   ------
			std::string strCountryString = CountryFunction::GetCountryNameById( GetRealCountry() );
			///*if (HasGuild())
			//{	*/			
			//if( GetCountryTitle() && CountryFunction::CheckIsCountryTitle(GetCountryTitle()) && strCountryString.size() > 0 )
			//{
			//	std::string strCountryTitle = strCountryString;
			//	strCountryTitle += CountryFunction::GetCountryTitleNameById( GetCountryTitle() );

			//	if( strCountryTitle.size() > 0 )
			//	{
			//		text += strCountryTitle + "\n";
			//		// ���������ɫ [11/11/2010 zhangjiayi]
			//		colors.push_back( Color_Config.getColor( CC_ContryTitle ) );

			//		if ( IsRole() || m_pPrivateShopInfo )
			//			offsetZScale += fTemp3;
			//		else
			//			offsetZScale += fTemp1;
			//		baroffy -= 0.1f;
			//	}
			//}
			/*} */         
			//---------------------------------------------------------------------------

			if (szTitle && strlen(szTitle) > 0 && IsShow( CPlayer::eHeadInfo_Title ))
			{
				int iTitleLine = 1;
				int iTitleLength = strlen(szTitle);
				//if( iTitleLength > 17 )
				//{
				//	// �ƺŻ��� //lyh�ƺ�ΪʲôҪ���У�
				//	++iTitleLine;
				//}
				text += szTitle;
				for(int j=0; j<iTitleLine; ++j)
				{
					text += "\n"; 
					if( m_dwTitleColor == 0 || Signature) //������һ����ɫ
						colors.push_back(Color_Config.getColor(CC_PlayerTile));
					else
						colors.push_back( m_dwTitleColor );

				}

				if (IsRole() || m_pPrivateShopInfo)
					offsetZScale += fTemp2;
				else
					offsetZScale += fTemp;

				baroffy -= 0.1f;
			}

			CWorldTile* pTile = CURRENTTILE;			
			DWORD tempColor = 0xffffffff;
			bool isZhuJiangState = false;

			// ����� �� ������(�Ǳ��������ʾ)			added by zhuomeng.hu		[9/10/2010]
			if ( IsShow( CPlayer::eHeadInfo_Name ))
			{
				// ��ȡ��������  �������ֲ���ʾ lrt
				//if (mHeroID != INVALID_HERO_ID)
				//{
				//	CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(mHeroID);
				//	if (itemHero == NULL)
				//		return;

				//	/*
				//	* Author: 2012-9-22 11:24:56 wangshuai
				//	* Desc:   �����ĵ�����������ȫ�ǵģ�Ӧ�߻�Ҫ�󣬸�Ϊ���
				//	*/
				//	text += itemHero->hero_name + "[" + m_szDisplayName + "]";
				//	isZhuJiangState = true;					
				//}
				//else
				{
					text += m_szDisplayName;
				}

				CPlayer* pPlayerMe = theHeroGame.GetPlayerMgr()->GetMe();
				if( pPlayerMe && ( strCountryString.size() > 0 ) )
				{
					if( pPlayerMe != this )
					{
						if( pPlayerMe->GetRealCountry() != GetRealCountry() )
							text += " (" + strCountryString + ")";
					}
				}
			}

			//Ϊ��ҵĻ�
			if (pTile && pTile->GetCanPk() == MapConfig::MapData::EPKM_Group_PK)
			{                
				SetNameColorByInfluence(tempColor);
			}
			else if (pTile&&pTile->GetCanPk() == MapConfig::MapData::EPKM_Team_PK)
			{
				if (thePlayerRole.IsTeamMember(GetName()) )
					tempColor = Color_Config.getColor(CC_CampBattleSame);
				else
					tempColor = Color_Config.getColor(CC_CampBattleNoSame);
			}
			else if (GetRealCountry() != thePlayerRole.GetCountry() )
				tempColor = Color_Config.getColor( CC_Player_OtherCountry ) ;
			/*else if (isZhuJiangState)
			tempColor = Color_Config.getColor(CC_ZhuJiang_Name);*/
			else
				tempColor = GetPkNameColor();

			//��������ж������Ҫ����ҵ�ͷ����ɫ�õж���ɫ
			/*if( theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->canAttack( this ) )
			tempColor = Color_Config.getColor(CC_PlayerEnemy);*/
			if(theHeroGame.GetPlayerMgr()->GetMe()->GetRealCountry() != this->GetRealCountry())
			{
				//��ͬ���� ���ҵж�
				if( theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->canAttack( this ) )
					tempColor = Color_Config.getColor(CC_PlayerEnemy);
			}

			//�������ս�� �����ǲ�ͬ��˫�� ������ɫΪ��ɫ
			if (pTile && pTile->GetCanPk() == MapConfig::MapData::EPKM_Guild_PK)
			{                
				if(theHeroGame.GetPlayerMgr()->GetMe()->canAttack( this ))
					tempColor = Color_Config.getColor(CC_PlayerEnemy);
				else
					tempColor = Color_Config.getColor(CC_WhiteName);
			}

			//��Ӷ���������ɫ�����ȼ����
			if ( thePlayerRole.IsTeamMember(GetName()) )
				tempColor = Color_Config.getColor( CC_TeamPlayer );

			colors.push_back(tempColor);
			//---------------------------------------
			if (fontName_)
			{
				for (size_t i = 0; i < colors.size(); ++i)
					fontName_->SetColor(colors[i], i);
			}

			float pbo = 0.0f;
			float noff = 0.0f;
			static float inc = 0.045f;
			static float inc2 = 0.03f;
			if (m_pHpPB3D && m_pHpPB3D->GetVisible())
			{
				//m_pHpPB3D->SetOffsetY(baroffy - pbo);
				pbo += inc2;
				noff += inc;
				fontName_->SetColor(0xFFFFFFFF, colors.size());
			}
			if (m_pMpPB3D && m_pMpPB3D->GetVisible())
			{
				m_pMpPB3D->SetOffsetY(baroffy - pbo);
				pbo += inc2;
				noff += inc;
				fontName_->SetColor(0xFFFFFFFF, colors.size()+1);
			}
			if (m_pFpPB3D && m_pFpPB3D->GetVisible())
			{
				m_pFpPB3D->SetOffsetY(baroffy - pbo);
				pbo += inc2;
				noff += inc;
			}

			offsetZScale += noff;
		}
		break;
	case Object_Monster:
		{
			if (HaveMaster())
			{
				// ���ɼ����ٻ���
				bool bIsVisibleToOtherPlayer = true;
				if( !IsVisibleToOtherPlayer() )
				{
					if( theHeroGame.GetPlayerMgr()->GetMe() )
					{
						// �����Լ����ٻ���
						if( theHeroGame.GetPlayerMgr()->GetMe()->GetID() != GetMasterID() )
							bIsVisibleToOtherPlayer = false;
					}
					else
						bIsVisibleToOtherPlayer = false;
				}

				if( bIsVisibleToOtherPlayer )
				{
					color1 = Color_Config.getColor(CC_NAME_Pet);
					color2 = Color_Config.getColor(CC_PetTitle); //lyh�ڳ��ƺ���ɫ
					std::string title = GetTitle();
					if (!title.empty())
					{
						int nQuality=0;
						color2 = thePetSettingConfig.GetTitleColorByTitleName(title,nQuality);
						if (color2 == 0)
						{
							color2 = S_IconInfoHero::GetQualityColor(nQuality);
						}
						color1 = color2;
					}
					CPlayer* pMaster = theHeroGame.GetPlayerMgr()->FindByID( GetMasterID() );
					if( pMaster )
					{
						if( pMaster->GetRealCountry() != thePlayerRole.GetCountry() )
						{
							color1 = Color_Config.getColor( CC_Pet_OtherCountry );
							//color2 = Color_Config.getColor( CC_PetTitle_OtherCountry );
						}
						if (title.empty())
						{
							char temp[64] = {0};
							MeSprintf_s(temp,sizeof(temp),theXmlString.GetString( eClient_VassalName ),pMaster->GetName());
							title += temp;
						}
					}
					bool bShowPetTitle = false;
					if( !stricmp(thePlayerRole.GetName(), GetMasterName().c_str()) )
					{
						bShowPetTitle = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfPetTitle );
					}
					else if( thePlayerRole.IsTeamMember(GetMasterName().c_str()) )
					{
						bShowPetTitle = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPetTitle );
					}
					else
					{
						bShowPetTitle = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPetTitle );
					}
					if (!title.empty() && bShowPetTitle && GetID() == theHeroGame.GetPlayerMgr()->GetLockPlayerID())
					{
						text +=title.c_str();
						//text += "\n"; 

						//					    char buf[64];
						//					    MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1, GetMasterName().c_str());

						// 					    std::wstring wname = Common::_tstring::toWideString(GetMasterName().c_str());
						// 					    static int TITLE_MAX_LEN = 5;
						// 					    if (wname.length() > TITLE_MAX_LEN)
						// 					    {
						// 						    std::wstring wstr = Common::_tstring::toWideString(buf);
						// 						    wstr = wstr.substr(0, TITLE_MAX_LEN + 3);
						// 						    wstr += L"...>";
						// 
						// 						    text += Common::_tstring::toNarrowString(wstr.c_str());
						// 					    }
						// 					    else
						//						    text += buf;

						if (m_pHpPB3D)
							m_pHpPB3D->SetOffsetY(0.21f);
					}
					else
					{
						if (m_pHpPB3D)
							m_pHpPB3D->SetOffsetY(0.21f);
					}

					if( IsShow( CPlayer::eHeadInfo_Name ))
					{
						text += "\n";
						text += m_szDisplayName;
						offsetZScale += 0.12;
					}

					SetPetNameColor(pMaster, color1);
					SetPetNameColor(pMaster, color2);
				}
			}
			else
			{
				/*����������ʾ��ɫ��
				color2 :����
				color1 :�ƺ�
				*/
				if( IsShow( CPlayer::eHeadInfo_Name ))
					text += m_szDisplayName;
				text += "\n";
				ItemDefine::SMonster* pMonster = GettheItemDetail().GetMonsterByName(GetName());
				if (pMonster && pMonster->nIsInitiative)
				{
					if( theHeroGame.GetPlayerMgr()->GetMe() )
					{
						int l = GetLevel() - theHeroGame.GetPlayerMgr()->GetMe()->GetLevel();
						if (l >= -5 && l <= 5)
							color2 = Color_Config.getColor(CC_MonsterLevelRange5);
						else if (l < -5)
							color2 = Color_Config.getColor(CC_MonsterLevelLow5);
						else
							color2 = Color_Config.getColor(CC_MonsterLevelUp5);
					}
					else
						color2 = Color_Config.getColor(CC_MonsterLevelUp5);
				}
				else
				{
					/*
					* Author:	2012-8-31 wangshuai
					* Desc: 	������������ɫ����ColorConfig�е�������ʾ
					*/
					color2 = Color_Config.getColor(CC_ENTITY_MONSTER_PASSIVITY);
				}				

				if (!GetTitle().empty())
				{
					text += GetTitle();

					offsetZScale += 0.36f;

					if (m_pHpPB3D)
						m_pHpPB3D->SetOffsetY(0.30f);

					color1 = m_dwTitleColor;
				}
				else
				{
					if (m_pHpPB3D)
						m_pHpPB3D->SetOffsetY(0.30f);
				}

				//SetNameColorByInfluence(color1);
				SetNameColorByInfluence(color2);
			}


			if (fontName_)
			{
				fontName_->SetColor(color2, 0);
				fontName_->SetColor(color1, 1);
			}
			break;
		}
	case Object_Item:
		{
			//�߻�Ҫ����Ʒģ����ʱ��ʾ�����������ҲҪ����,Ҫ�ǲ���ʰȡ����������Ҳ����ʾ
			if( HQ_TimeGetTime() < m_dwDisplayAfterTime || m_bCanPick == false )
			{
				return;
			}
			if( IsShow( CPlayer::eHeadInfo_Name ))
				text += m_szDisplayName;
			color1 = S_IconInfoHero::GetQualityColor( GetLevel() );
			fontScale = 0.85f;
			offsetZScale += 0.2f;

			if (fontName_)
			{
				fontName_->SetColor(color1, 0);
			}
			break;
		}
	case Object_Npc:
		{

			if (!GetTitle().empty() && IsShow( CPlayer::eHeadInfo_Title ))
			{
				text += GetTitle();

				offsetZScale = 0.05f;
			}

			if( IsShow( CPlayer::eHeadInfo_Name )&&(m_pNpcCoordInfo&&m_pNpcCoordInfo->_nType != eNT_Elevator))
			{
				text += "\n";
				text += m_szDisplayName;
			}
			color2 = Color_Config.getColor(CC_NPCTile);


			if( GetRealCountry() == CountryDefine::Country_Init )
			{
				// ����NPC
				color1 = Color_Config.getColor( CC_NPC_NoCountry );
			}
			else if( GetRealCountry() == thePlayerRole.GetCountry() )
			{
				color1 = Color_Config.getColor( CC_NPC );
			}
			else
			{
				color1 = Color_Config.getColor( CC_NPC_OtherCountry );
			}

			if (fontName_)
			{
				fontName_->SetColor(color1, 1);
				fontName_->SetColor(color2, 0);
			}

			break;
		}
	}

	static float maxh = 1.2f;
	static float minh = 0.2f;
	if (toPosDist > maxh)
	{
		toPosDist = maxh;
	}
	else if (toPosDist < minh)
	{
		toPosDist = minh;
	}
	D3DXVECTOR3 barPos = fontPos;
	//fontPos.z += toPosDist * offsetZScale;
	//barPos.z += toPosDist * offsetZScale;

	d = getwsCamera()->GetMeCamera()->GetEyePt() - fontPos;
	toPosDist = D3DXVec3Length(&d);

	float fovScale = ( g_fCamerFOV - D3DXToRadian(45) ) / ( D3DXToRadian(70) - D3DXToRadian(45) );
	fontScale = fontScale * toPosDist * (gCfg.m_fNameFontScale + 2.6 * fovScale ) / gCfg.m_nNameFontSize;

	static float zoffscale = 0.01f;
	static float moff = 0.065f;
	static float zoff2 = -0.6f;
	if (IsMounting())
	{
		fontPos.z -= zoffscale * toPosDist;
		fontPos.z += zoff2;
	}
	else
	{
		barPos.z -= moff * toPosDist;
		//fontPos.z -= moff * toPosDist;
	}

	barPos.z += (gCfg.m_fNameFontOffset - 0.02 * fovScale) * toPosDist;
	//fontPos.z += (gCfg.m_fNameFontOffset - 0.02 * fovScale) * toPosDist;

	static float sitoffset = 0.03f;
	int headBone = -1;
	if (GetAnim() && 
		GetAnim()->GetMex() &&
		GetAnim()->GetMex()->GetSkeleton() &&
		(headBone = GetAnim()->GetMex()->
		GetSkeleton()->FindBone("Bip01 Head")) != -1)
	{
		D3DXVECTOR3 v = *(D3DXVECTOR3*)&GetAnim()->GetBoneWorldPos(headBone);
		if ( IsJumping() || IsInWater() )
			fontPos.z = v.z + 0.15f;
		if (IsMounting())
		{
			fontPos.x = v.x;
			fontPos.y = v.y;
		}
		else if (IsSittingAnim())
		{
			fontPos.z = v.z + sitoffset;
		}
	}


	if (fontName_)
	{
		fontName_->SetScale(D3DXVECTOR3(fontScale, fontScale, fontScale));
		D3DXVECTOR3 fontPos2D;
		if (fontName_->GetType() == RTTFont::ERTT_2D )
		{
			float fx = 0, fy = 0;
			if ( getwsCamera()->GetMeCamera()->WorldToScreen( *(Vector*)(&fontPos), &fx, &fy, SCREEN_WIDTH, SCREEN_HEIGHT ) )
			{
				fontPos2D.x = fx;
				fontPos2D.y = fy;
			}
			///���������ָ߶�///
			int nTotalLine = fontName_->GetColorsCount() ;//* 2 - 1;  //modified by zmy,��Щ����ֵ��֪��ʲô����
			// ���ָ߶�
			float fFontHeight = FontSystem::GetFontHeight( fontName_->GetFontIndex() ) + fontName_->GetLineSpace();
			// �ܸ߶� = ���� * ����
			float fTotalFontHeight = fFontHeight * nTotalLine;

			int nOffset = IsMoving() ? 20 : 12;				
			fontPos2D.y -= (fTotalFontHeight + nOffset);

			/*
			///������������Ļ����ϵ�еĸ߶�///			
			float fDeltaY = 0;
			Box *pBBox = GetWorldBBox();
			if( !pBBox )
			{
			return;
			}

			if( getwsCamera()->GetMeCamera()->WorldToScreen( *(Vector*)(&pBBox->v[0]), &fx, &fy, SCREEN_WIDTH, SCREEN_HEIGHT ) )
			{
			// ���糤��Ϊ1����Ļ����ΪfDeltaY
			fDeltaY = fy;
			if( getwsCamera()->GetMeCamera()->WorldToScreen( *(Vector*)(&pBBox->v[4]), &fx, &fy, SCREEN_WIDTH, SCREEN_HEIGHT ) )
			{
			fDeltaY -= fy;
			}
			}
			// ���������������������Ļ����
			float fPlayerHeightInScreen = fDeltaY;
			float fHalfHeight = fPlayerHeightInScreen * 0.5f;

			///�ټ�����Ļ��ռ����
			float fRatio = pBBox->v[4].z;//( pBBox->v[4].z - pBBox->v[0].z ) / fDeltaY;
			barPos.z = fRatio;
			static float fSign = -2;
			barPos.z -= ( moff * toPosDist + fSign / toPosDist );
			// ����ռ��иı�߶�
			float fDeltaYin3D = fRatio * ( (float)( RTTFont::RTT_TEX_WIDTH / 2.f ) - fHalfHeight - fTotalFontHeight );
			//barPos.z -= fDeltaYin3D;
			*/

			// ����depth
			RendererDx* pRenderDx = (RendererDx*)GetEngine()->GetRenderer();
			D3DXMATRIXA16 matWVP = pRenderDx->GetWorldViewProjection();				
			D3DXVECTOR3 vTransformedPos;
			D3DXVec3TransformCoord( &vTransformedPos, &GetPos(), &matWVP );
			fontPos2D.z = vTransformedPos.z;
			fontName_->SetPosition(fontPos2D);
		}
		else if( fontName_->GetType() == RTTFont::ERTT_3D )
		{
			fontName_->SetPosition( fontPos );
		}
		m_szFinalName = text;
		fontName_->SetText(text);
		if( text.empty() )//��
			fontName_->SetVisible( false );
	}
	static float s_barOffset = 0.f;
	//barPos.z += s_barOffset;

	if (m_pHpPB3D)
	{
		if (IsRole())
		{ // HPˢ�������⣬����ʹ��thePlayerRole.GetData
			m_pHpPB3D->SetMaxValue(thePlayerRole.GetData(CPlayerRole::TYPE_HPMAX));
			m_pHpPB3D->SetValue(thePlayerRole.GetData(CPlayerRole::TYPE_HP));
		}
		else
		{
			m_pHpPB3D->SetMaxValue(GetHpMax());
			m_pHpPB3D->SetValue(GetHp());
		}

		m_pHpPB3D->SetScale(D3DXVECTOR3(fontScale, fontScale, fontScale));
		//if ( m_pMpPB3D && m_pMpPB3D->GetVisible() == false )
		//{

		D3DXVECTOR3 vHPPos(fontPos);
		if (IsMounting())
			vHPPos.z += IsMoving() ? 0.22 : 0.0;
		else
			vHPPos.z += IsMoving() ? 0.15 : 0.0;

		m_pHpPB3D->SetPosition(/*barPos*/vHPPos);
		//}
		//else
		//{
		//	float fx = 0, fy = 0;
		//	getwsCamera()->GetMeCamera()->WorldToScreen( *(Vector*)(&fontPos), &fx, &fy, SCREEN_WIDTH, SCREEN_HEIGHT );
		//	float fontHeight = FontSystem::GetFontHeight( fontName_->GetFontIndex() );
		//	fy -= fontHeight;
		//	m_pHpPB3D->SetPosition(/*barPos*/D3DXVECTOR3( fontPos.x, fontPos.y, fontPos.z ) );
		//}

	}

	if (m_pMpPB3D)
	{
		m_pMpPB3D->SetMaxValue(thePlayerRole.GetData(CPlayerRole::TYPE_MPMAX));
		m_pMpPB3D->SetValue(thePlayerRole.GetData(CPlayerRole::TYPE_MP));

		m_pMpPB3D->SetScale(D3DXVECTOR3(fontScale, fontScale, fontScale));
		m_pMpPB3D->SetPosition(/*barPos*/fontPos);
	}

	if (m_pFpPB3D)
	{
		m_pFpPB3D->SetMaxValue(100);
		m_pFpPB3D->SetValue(thePlayerRole.GetData(CPlayerRole::TYPE_ExPower));

		m_pFpPB3D->SetScale(D3DXVECTOR3(fontScale, fontScale, fontScale));
		m_pFpPB3D->SetPosition(barPos);
	}

}


void CPlayer::RenderChatInfo()
{
	if ( m_pChatPaoPao && IsShow( eHeadInfo_Chat ) )
	{
		if( IsNpc() && IsHide() )
			return;
		// commented out, [9/28/2010 zhangjiayi]
		// �߻����󣬲���Ҫz
		RendererDx* pRenderDx = ( RendererDx*)GetEngine()->GetRenderer();
		D3DXMATRIX matWorld;
		D3DXMatrixIdentity( &matWorld );
		pRenderDx->SetTransform( D3DTS_WORLD, (FLOAT*)&matWorld );
		D3DXMATRIXA16 matWVP = pRenderDx->GetWorldViewProjection();				
		D3DXVECTOR3 vTransformedPos;
		D3DXVec3TransformCoord( &vTransformedPos, &GetPos(), &matWVP );
		m_pChatPaoPao->SetBackPicZValue( vTransformedPos.z );
		m_pChatPaoPao->SetRenderTextWithZ( true );
		FontSystem::SetGlobalZ( vTransformedPos.z, m_pChatPaoPao->GetFontIndex() );
		m_pChatPaoPao->Render();
		FontSystem::SetGlobalZ( 0, m_pChatPaoPao->GetFontIndex() );		
	}
}

POINT CPlayer::GetPlayerPos()
{
	guardfunc;
	int x, y;
	World2Screen( D3DXVECTOR3( m_x, m_y, m_z ), x, y );
	POINT pt = { x, y };

	return pt;
	unguard;
}
//----
//  ��npc��һЩ��ʾ��Ϣ
//----
void CPlayer::RenderInfo(LPDIRECT3DDEVICE9 pDevice, int x, int y)
{
	guardfunc;

	// NPC��������ʾ
	if( IsNpc() && IsHide() )
	{
		return;
	}

	float npc_x, npc_y, npc_z;
	char string[256];
	CPlayer* pPlayer = this;
	//����
	//���
	//����
	pPlayer->GetPos(&npc_x, &npc_y, &npc_z);
	MeSprintf_s(string,sizeof(string)/sizeof(char) - 1, theXmlString.GetString(eText_StringName)/*"����:%s  ���:%d  ����(x=%d, y=%d)"*/, pPlayer->GetName(), pPlayer->GetID(), (int)npc_x, (int)npc_y);
	FontSystem::DrawText( string, x, y, DT_NOCLIP, 0xffffffff );
	y+=24;
	//��ǰ��operation
	//��ǰ��Status
	//��ǰ��ִ�е���Ϊ

	MeSprintf_s(string,sizeof(string)/sizeof(char) - 1, "Operation:%d  Status:%d  NowAction:%d skill:%d fight:%d, Tfigth:%d", 
		pPlayer->GetOperation()->dwType, pPlayer->m_status.CurStatus(), 
		m_NowAction.stType, pPlayer->GetOperation()->skill.iSkillID, 
		pPlayer->GetFightStatus(), pPlayer->GetToFightStatus());
	FontSystem::DrawText( string, x, y, DT_NOCLIP, 0xffffffff );
	y+=24;
	//
	MeSprintf_s(string,sizeof(string)/sizeof(char) - 1, "Move StartTime:%d  StepTime:%d", m_move.dwStartTime, m_move.dwStepTime);
	FontSystem::DrawText( string, x, y+24, DT_NOCLIP, 0xffffffff );
	y+=24;
	unguard;
}

//ս��ģʽ
unsigned char	CPlayer::GetFightStatus(void)
{
	guardfunc;
	return true;
	unguard;
}
//�Ա�
unsigned char	CPlayer::GetSex(void)
{

	guardfunc;
	return m_ucSex;
	unguard;
}
//ְҵ
unsigned char	CPlayer::GetProfession(void)
{
	guardfunc;
	return m_ucProfession;
	unguard;
}
//
void CPlayer::SetSitStatus(unsigned char status)
{
	guardfunc;
	m_ucSitStatus = status;
	if( m_ucSitStatus != 1 && !IsInWater() )
	{
		// ���������ɼ�����ӵ����������ʾ����
		if( m_pAnim && !m_pAnim->IsCurrAnimHideWeapon() )
			SetShowWeapon(TRUE);
	}
	unguard;
}
//ս��ģʽ
void CPlayer::SetFightStatus(unsigned char status)
{
	guardfunc;
	m_ucFightStatus = status;
	unguard;
}
//�Ա�
void CPlayer::SetSex(unsigned char sex)
{
	guardfunc;
	m_ucSex = sex;
	unguard;
}
//ְҵ
void CPlayer::SetProfession(unsigned char profession)
{
	guardfunc;
	m_ucProfession = profession;
	unguard;
}
//..��Ҫ�л�����ս��ģʽ
void CPlayer::SetToFightStatus(unsigned char status)
{
	guardfunc;
	m_ucToFightStatus = status;
	unguard;
}

void CPlayer::SetCountryMask( int iCountry )
{
	guardfunc;

	//deleted

	int i = 0;
	i /= 100;
	i %= 100;

	//Ŀǰֻ�г�����Ҫ
	// 	if( buildingtype_chengmen != i )
	// 		return;	

	int xStart,yStart;

	xStart = m_ptLoc.x;
	yStart = m_ptLoc.y;
	int iRow,iCol;

	int iDir = GetDirInt();
	switch( iDir )
	{
	case 0:
	case 4:
		//6X2
		xStart -= 3;
		yStart -= 1;
		iRow = 2;
		iCol = 6;
		//
		break;
	case 2:
	case 6:
		//2X6
		xStart -= 1;
		yStart -= 3;
		iRow = 6;
		iCol = 2;
		break;
	default:
		assert( false );
		return;
	}

	int x,y;	
	y = yStart;
	for( int iRowLoop = 0 ; iRowLoop < iRow ; iRowLoop ++,y ++ )
	{
		x = xStart;
	}
	unguard;
}
//
void CPlayer::ApplyCountryMask( void )
{
	guardfunc;
	SetCountryMask( GetCountry() );
	unguard;
}

void CPlayer::ClearCountryMask( void )
{
	guardfunc;
	SetCountryMask( country_none );
	unguard;
}

void CPlayer::AddRef( void )
{
	guardfunc;
	// #ifdef LOG_PLAYER_REF
	// 	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "%s ADD ref at func:%s, line:%d", GetName(), __FUNCTION__, __LINE__ );
	// #endif // LOG_PLAYER_REF
	m_iRef ++;

	unguard;
}
void CPlayer::DecRef()
{
	// #ifdef LOG_PLAYER_REF
	// 	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "%s DEC ref at func:%s, line:%d", GetName(), __FUNCTION__, __LINE__ );
	// #endif // LOG_PLAYER_REF
	--m_iRef;
}

bool CPlayer::Release( void )
{
	guardfunc;
	--m_iRef ;
	assert( m_iRef >= 0 );

	if( m_iRef <= 0)
	{
		m_bNeedToDelete = true;
		return true;
	}
	m_bNeedToDelete = true;	
	return false;
	unguard;
}

#include "MeUi/ExpressionManager.h"
void CPlayer::SetChatInfo( std::string& strInfo ,DWORD dwLifeTime)
{
	guardfunc;
	if ( strInfo.size() > 0 )
	{
		RECT rc = {0,0,0,0};
		if ( !m_pChatPaoPao )
		{
			m_pChatPaoPao = MeNew ControlText;
			m_pChatPaoPao->Create( &rc, 0xffffffff );
			m_pChatPaoPao->SetColUrl(0xffffffff);
		}

		m_pChatPaoPao->SetFont(s_CUI_ChatInfoBox.GetEditInput());
		int nFontSize = m_pChatPaoPao->GetFontSize() * ControlObject::GetREAL_SCALE(NULL);
		ExpressionManager::GetInstance().AddExpressionAni(strInfo,3);
		int nMaxFontHeight = FontSystem::GetFontHeight( m_pChatPaoPao->GetFontIndex() );

		// modified by zhuomeng.hu		[11/10/2010]
		int nFontMaxWidth( 0 );
		if ( strInfo.size() <= CHAT_PAOPAO_WORDS_MAX )
		{
			nFontMaxWidth = nFontSize * strInfo.size() /** 0.4*/;
			rc.right = nFontMaxWidth + 23;
			// 			rc.bottom = nFontSize + 20;
		}
		else
		{
			nFontMaxWidth = nFontSize * CHAT_PAOPAO_WORDS_MAX /** 0.4*/;
			rc.right = nFontMaxWidth + 23;
			// 			rc.bottom = ( nMaxFontHeight)* ( ( strInfo.size() - 1 ) / ( CHAT_PAOPAO_WORDS_MAX / 2 ) + 1 );
		}
		//         if( strInfo.find( "#" ) != std::string::npos )
		//             rc.bottom += 30;
		//rc.bottom += 20;
		//if (rc.right - rc.left < rc.bottom - rc.top)
		//	rc.right = rc.left + rc.bottom - rc.top;


		strInfo += '\n';
		m_pChatPaoPao->SetRealRect( &rc );//�ȸ�һ���㹻���rc����Ԥ����,���������㻻�е�
		m_pChatPaoPao->SetMaxFontWidth( nFontMaxWidth+8 ); //��д��W�ر��
		m_pChatPaoPao->SetText( strInfo );
		//���ú��ʵ�rc���м���
		rc.right = m_pChatPaoPao->GetTextWidth() + nFontSize;
		rc.bottom = m_pChatPaoPao->GetTextHeight() + nMaxFontHeight;

		rc.right += 10;
		if ( rc.right < 30 )	//��ֹ��С���Ի����ݸ����޷���Ⱦ
		{
			rc.right = 30;
		}

		// 		static int MIN_WIDTH = 20;
		// 		if (rc.right - rc.left < MIN_WIDTH * ControlObject::GetSCALE(NULL))
		// 			rc.right = rc.left + MIN_WIDTH * ControlObject::GetSCALE(NULL);
		// 		if (rc.right - rc.left < rc.bottom - rc.top)
		// 			rc.right = rc.left + rc.bottom - rc.top;
		m_pChatPaoPao->SetRealRect( &rc );
		m_pChatPaoPao->SetText( strInfo );



		// 		// ���¼���λ��
		// 		if (m_pChatPaoPao->GetTextHeight() > 30)
		// 		{
		// 			rc.bottom = m_pChatPaoPao->GetTextHeight() + nFontSize * 3;
		// 			m_pChatPaoPao->SetRealRect( &rc );
		// 			m_pChatPaoPao->SetText( strInfo );
		// 		}


		S_BaseData::S_Pic pPic;
		// 		RECT rcFrame = {98, 287, 125, 313};
		// 		RECT rcClient = {102, 291, 107, 304};
		pPic.SetPicStruct(gCfg.m_strChatPaoPaoTexture.c_str(), &gCfg.m_ChatPaoPaoRect, &gCfg.m_ChatPaoPaoInnerRect);
		m_pChatPaoPao->SetPic(&pPic, true);
		//  		m_pChatPaoPao->SetOffsetY(3);

		S_BaseData* pData = m_pChatPaoPao->GetData();
		for(int i=0; i<S_BaseData::Mode_Max; ++i)
		{
			pData->m_nDrawMode[i] = DrawModeStrectch;
		}
		m_dwChatDialogBoxBornTime = HQ_TimeGetTime();
		m_dwChatDialogLifeTime = dwLifeTime;

		ShowChatPaoPao();
	}
	else
	{
		ClearChatPaoPao();
	}
	unguard;
}

void CPlayer::SetPrivateInfo( const bool bOpen, const char* szInfo )
{
	guardfunc;
	m_bOpenPrivateShop = bOpen;
	std::string strInfo = szInfo;
	m_strShopName = strInfo;
	if( bOpen == false )
	{
		m_bPrivateShopOpen = false;
		SAFE_DELETE( m_pPrivateShopInfo );
	}
	else
	{
		m_bPrivateShopOpen = true;
		RECT rc = { 0, 0, 0, 0 };
		if ( !m_pPrivateShopInfo )
		{
			m_pPrivateShopInfo = MeNew ControlText;
			m_pPrivateShopInfo->Create( &rc, 0xFFC2FF6C );
			m_pPrivateShopInfo->SetFont(s_CUI_ChatInfoBox.GetEditInput());
		}
		// 		int nFontSize = m_pPrivateShopInfo->GetFontSize();
		// 		int nStrLen = strlen( szInfo );
		// 		if ( nStrLen <= CHAT_INFO_WIDTH_MAX )
		// 		{
		// 			rc.right = nFontSize * ( nStrLen ) * ControlText::GetREAL_SCALE(NULL) * PRIVATESHOP_LENGTH_FACTOR;
		// 			rc.bottom = nFontSize * ControlText::GetREAL_SCALE(NULL) * 2 ;
		// 		}
		// 		else
		// 		{
		// 			rc.right = nFontSize * ( CHAT_INFO_WIDTH_MAX + 4 ) / 2 * ControlText::GetREAL_SCALE(NULL);
		// 			rc.bottom = (nFontSize * ControlText::GetREAL_SCALE(NULL) + 2 ) * nStrLen / CHAT_INFO_WIDTH_MAX + 5;
		// 			if ( nStrLen%CHAT_INFO_WIDTH_MAX != 0 )
		// 			{
		// 				rc.bottom += nFontSize * ControlText::GetREAL_SCALE(NULL);
		// 			}
		// 		}
		//m_pPrivateShopInfo->SetOffsetY( -6 );
		//m_pPrivateShopInfo->SetRealRect( &rc );

		/*
		//��þŹ���
		int nWidthOffset = gCfg.m_PrivateInnerRect.left;
		int nHeightOffset = gCfg.m_PrivateInnerRect.top;
		int nWidth = 0,nHeight = 0;

		std::wstring wStrInfo = Common::_tstring::toWideString(szInfo);
		int nLen = wStrInfo.length();
		if(nLen <= CHAT_INFO_WIDTH_MAX )
		{
		nWidth = FontSystem::GetTextWidth(m_pPrivateShopInfo->GetFontIndex(),wStrInfo,0,nLen,false) + nWidthOffset * 2;
		nHeight = FontSystem::GetFontHeight(m_pPrivateShopInfo->GetFontIndex()) + nHeightOffset * 2 + m_pPrivateShopInfo->GetOffsetHeight() * 2;
		}
		else
		{
		nWidth = FontSystem::GetTextWidth(m_pPrivateShopInfo->GetFontIndex(),wStrInfo,0,CHAT_INFO_WIDTH_MAX,false) + nWidthOffset * 2;
		nHeight = FontSystem::GetFontHeight(m_pPrivateShopInfo->GetFontIndex()) + nHeightOffset * 2 + m_pPrivateShopInfo->GetOffsetHeight() * 3;
		}
		rc.right = nWidth;
		rc.bottom = nHeight;
		*/
		rc.right = gCfg.m_RealRect.right;
		rc.bottom = gCfg.m_RealRect.bottom;
		m_pPrivateShopInfo->SetRealRect( &rc);
		m_pPrivateShopInfo->SetText( strInfo.c_str(), 0xffffffff );

		//zizi add test
		S_BaseData::S_Pic pPic;

		//RECT rcFrame = {0, 0, 128, 27};
		//RECT rcClient = {8, 11, 120, 16};
		//pPic.SetPicStruct("COMMON\\BaiTanTitle.tga", &rcFrame, &rcClient);//zjj fixed it
		pPic.SetPicStruct(gCfg.m_strPrivateTexture.c_str(),&gCfg.m_PrivateRect,&gCfg.m_PrivateInnerRect);
		m_pPrivateShopInfo->SetPic(&pPic, true);

		S_BaseData* pData = m_pPrivateShopInfo->GetData();
		for(int i=0; i<S_BaseData::Mode_Max; ++i)
		{
			pData->m_nDrawMode[i] = DrawModeStrectch;
		}
	}
	unguard;
} 

BOOL CPlayer::AddFightFlag( EActionFlag flag, BOOL bIsPlayAmin, BOOL IsReEquip )
{
	guardfunc;
	_SET_FLAG(m_dwFightFlag, flag);
	DWORD dwTime = 300;

	if( flag == eFighting )
	{
		m_bPendingClearFightFlag = FALSE;

		m_dwFightChangeFlag = eChangeFightAll;

		if( m_bRole )
		{
			theApp->GetPlayerMgr()->SetTurnRoleToCamera(FALSE);

			// ˢ��HotKey
			s_CUI_ID_FRAME_MAIN.RefeashHotKey();
			s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
		}

		if( bIsPlayAmin )
		{
			if( IsPlayer() && !IsFightPose() )
			{
				SetFightPose(TRUE);
				// ������״̬�����аε�����
				if( !(GetSitStatus() && !GetSitInterrupt() ) && !m_bMounting )
					SwitchScabbardAnim(MexAnimCtrl::eMaxTimeout, FALSE);
			}
			else
			{
				// �л���ս����̬��������
				if( !m_bMoving )
				{
					SwitchIdleAnim();
				}
				else
				{
					SwitchRunAnim();
				}
			}

			guard(test);
			if( m_pAnim != NULL )
			{
				if( m_pAnim->GetHitPointFrameID() == -1 )
				{
					dwTime = 500;
				}
				else
				{
					int nFrame = ( m_pAnim->GetHitPointFrameID() - m_pAnim->GetStartFrameID() );
					if( nFrame < 0 )
						dwTime = 500;
					else 
						dwTime = nFrame *33;
				}
			}
			unguard;
			m_dwFightChangeTime = dwTime;
			m_dwFightChCurrTime = g_dwLastFrameBeginTime;
		}
		else
		{
			return FALSE;
		}
	}
	else
		return FALSE;

	return TRUE;
	unguard;
}

void CPlayer::ChangeToFightPose()
{
	if( IsPlayer() && !IsFightPose() )
	{
		SetFightPose(TRUE);
		// ������״̬�����аε�����
		if( !(GetSitStatus() && !GetSitInterrupt() ) && !m_bMounting )
			SwitchScabbardAnim(MexAnimCtrl::eMaxTimeout, FALSE);
	}
	else
	{
		// �л���ս����̬��������
		if( !m_bMoving )
		{
			SwitchIdleAnim();
		}
		else
		{
			SwitchRunAnim();
		}
	}
}

extern int g_nRoleCommonAttackStatus;
BOOL CPlayer::ClearFightFlag( EActionFlag flag, BOOL bIsPlayAmin, BOOL IsReEquip )
{
	guardfunc;
	bool bWasFightStatus = HasFightFlag(eFighting);
	_CLS_FLAG(m_dwFightFlag, flag);
	DWORD dwTime = 500;

	switch( flag )
	{
	case eFighting:
		{
			g_nRoleCommonAttackStatus = CAS_NOT_ATTACK;
			m_dwFightChangeFlag = eChangeFightAll;

			if (IsRole())
			{
				// ˢ��HotKey
				s_CUI_ID_FRAME_MAIN.RefeashHotKey();
				s_CUI_ID_FRAME_Exmain.RefeashHotNumber();

				m_vctAdvanceSkill.clear();
			}

			if( bIsPlayAmin )
			{
				if( IsPlayer() )
				{
					SetFightPose(FALSE);
					if( bWasFightStatus )
						SwitchScabbardAnim();
				}

				guard(test);
				if( m_pAnim != NULL )
				{
					if( m_pAnim->GetHitPointFrameID() == -1 )
					{
						dwTime = 500;
					}
					else
					{
						int nFrame = ( m_pAnim->GetHitPointFrameID() - m_pAnim->GetStartFrameID() );
						if( nFrame < 0 )
							dwTime = 500;
						else 
							dwTime = nFrame *33;
					}
				}
				unguard;
				m_dwFightChangeTime = dwTime;
				m_dwFightChCurrTime = g_dwLastFrameBeginTime;
			}
			break;
	default:
		return FALSE;
		break;
		}
	}
	return TRUE;
	unguard;
}

void CPlayer::SetWeaponSound( const char* pWeaponSound )
{
	guardfunc;
	m_pWeaponSound = pWeaponSound;
	unguard;
}

const char* CPlayer::GetWeaponSound()
{
	guardfunc;
	return m_pWeaponSound;
	unguard;
}

void CPlayer::SetArmourSound( const char* pArmourSound )
{
	guardfunc;
	m_pArmourSound = pArmourSound;
	unguard;
}

const char* CPlayer::GetArmourSound()
{
	guardfunc;
	return m_pArmourSound;
	unguard;
}

void CPlayer::HangMoving( DWORD dwCurTime, DWORD dwTimeLenght )
{
	guardfunc;
	if( m_bHangMoving )
	{
		return;
	}
	m_bHangMoving = TRUE;
	m_dwStartHangMovingTime = dwCurTime;
	m_dwHangMovingTimeLength = dwTimeLenght;
	unguard;
}

BOOL CPlayer::IsHangMoving( DWORD dwCurTime )
{
	guardfunc;
	if( m_bHangMoving )
	{
		if( dwCurTime - m_dwStartHangMovingTime < m_dwHangMovingTimeLength )
		{
			return TRUE;
		}
		else
		{
			m_bHangMoving = FALSE;
		}
	}
	return FALSE;
	unguard;
}
// void ReadVisual( CPlayer* pPlayer, int nPart, CCfgFileLoader* l, std::vector<std::string>* pvectorFile )
// {
// 	guardfunc;
// 	for( int i = 0; i < l->GetCurrentSessionLineCount(); i++ )
// 	{
// 		const char* pszKey = l->GetLineKeyName( i );
// 		if( stricmp( pszKey, "model" ) == 0 )
// 			pvectorFile->push_back( l->GetLineStringValue( i ) );
// 	}
// 
// 	if( pvectorFile->size() == 0 )
// 		return;
// 
// 	
// 	int nID = rand()%pvectorFile->size();
// 	int nIndex = 0;
// 	while (nIndex < pvectorFile->size() && nPart != CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask ))
// 	{
// 		if (pPlayer->GetSex() == 0 && (*pvectorFile)[nID].find("Male") != std::string::npos)
// 		{
// 			break;
// 		}
// 		else if (pPlayer->GetSex() == 1 && (*pvectorFile)[nID].find("Female") != std::string::npos)
// 		{
// 			break;
// 		}
// 		nID = ++nIndex;
// 	}
// 	nID %= pvectorFile->size();
// 
// 	BOOL bBack = FALSE;
// 	if( l->HasKey( "Back" ) )
// 		bBack = l->GetIntValue( "Back" );
// 
// 	int nModelID = GetMexResMgr()->AddExternalFile( (*pvectorFile)[nID].c_str() );
// 	if( !pPlayer->GetAnim() )
// 		return;
// 	DWORD dwFlag = pPlayer->GetAnim()->GetAvatar()->GetItemFlag();
// 
// 	CPlayerAnimParam param;
// 	param.nPart = nPart;
// 	param.nModelId = nModelID;
// 	param.szSkin = "default";
// 	param.nSex = pPlayer->GetSex();
// 	pPlayer->GetAnim()->TryChangePartModel(param);
// 
// 	{
// 		INT nbFight = rand()%2;
// 
// 		if( nPart == CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandItemPartMask ) )
// 		{
// 			if( bBack )
// 				dwFlag |= CAvatar::eItem_LBack;
// 			else
// 				dwFlag |= CAvatar::eItem_LeftHand;
// 		}
// 		else if( nPart == CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask ) )
// 		{
// 			if( bBack )
// 				dwFlag |= CAvatar::eItem_RBack;
// 			else 
// 				dwFlag |= CAvatar::eItem_RightHand;
// 		}
// 		else if( nPart == CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandShieldPartMask ) )
// 		{
// 			if( bBack )
// 				dwFlag |= CAvatar::eItem_BackShield;
// 			else
// 				dwFlag |= CAvatar::eItem_Shield;
// 		}
// 	}
// 
// 	pPlayer->GetAnim()->GetAvatar()->SetItemFlag( dwFlag );
// 
// 	CPlayerAnim* pMountAnim = MeNew CPlayerAnim;
// 	pMountAnim->SetPlayer(pPlayer);
// 	pPlayer->SetMountAnim(pMountAnim);
// 	unguard;
// }


// BOOL CPlayer::ChangeAvatar( const char* pszFilename )
// {
// 	guardfunc;
// 	CCfgFileLoader l;
// 	if( !l.LoadFromFile( pszFilename ) )
// 		return FALSE;
// 
// 	std::vector<std::string> faces;
// 	std::vector<std::string> hairs;
// 	std::vector<std::string> helmets;
// 	std::vector<std::string> armours;
// 	std::vector<std::string> shoulders;
// 	std::vector<std::string> gloves;
// 	std::vector<std::string> trousers;
// 	std::vector<std::string> shoes;
// 	std::vector<std::string> items;
// 	std::vector<std::string> shield;
// 
// 	if( !l.HasKey( "action" ) )
// 		return FALSE;
// 	int nModelID = GetMexResMgr()->AddExternalFile( l.GetStringValue( "action" ) );
// 	if( GetAnim() )
// 		GetAnim()->ChangeModel( nModelID, TRUE );
// 	m_nModelId = nModelID;
// 
// 	if( l.OpenSession( "face" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eFacePartMask ),  &l, &faces );
// 	if( l.OpenSession( "hair" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eHairPartMask ), &l, &hairs );
// 
// 	if( l.OpenSession( "helmet" ) )
// 	{
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eHelmetPartMask ), &l, &hairs );
// 	}
// 
// 	if( l.OpenSession( "armour" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eArmourPartMask ), &l, &armours );
// 	if( l.OpenSession( "shoulder" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eShoulderPartMask ), &l, &shoulders );
// 	if( l.OpenSession( "glove" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eGlovePartMask ), &l, &gloves );
// 	if( l.OpenSession( "trousers" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eTrousersPartMask ), &l, &trousers );
// 	if( l.OpenSession( "shoe" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eShoePartMask ), &l, &shoes );
// 
// 	if( l.OpenSession( "shield" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandShieldPartMask ), &l, &shield );
// 
// 	if( l.OpenSession( "weapon" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask ), &l, &items );
// 
// 	if( l.OpenSession( "Mount" ) )
// 	{
// 		MountMonster( (char*)l.GetStringValue( "Model" ), (char*)l.GetStringValue( "Skin" ) );
// 	}
// 	return TRUE;
// 
// 	unguard;
// }
// BOOL CPlayer::RandomVisual()
// {
// 	guardfunc;
// 	CCfgFileLoader l;
// 	if( !l.LoadFromFile( "..\\Data\\Config\\RandomVisual.ini" ) )
// 		return FALSE;
// 
// 	if( !m_pAnim )
// 		return FALSE;
// 
// 	GetAnim()->ChangeModel( m_pAnim->GetActionModelId( GetProfession(), GetSex(), 0 ) );
// 	GetAnim()->ChangeWeaponAnim( m_pAnim->GetWeaponActionModelId( GetProfession(), GetSex() ));
// 
// 	std::vector<std::string> faces;
// 	std::vector<std::string> hairs;
// 	std::vector<std::string> armours;
// 	std::vector<std::string> shoulders;
// 	std::vector<std::string> gloves;
// 	std::vector<std::string> trousers;
// 	std::vector<std::string> shoes;
// 	std::vector<std::string> items;
// 	if( l.OpenSession( "face" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eFacePartMask ),  &l, &faces );
// 	if( l.OpenSession( "hair" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eHairPartMask ), &l, &hairs );
// 	if( l.OpenSession( "armour" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eArmourPartMask ), &l, &armours );
// 	if( l.OpenSession( "shoulder" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eShoulderPartMask ), &l, &shoulders );
// 	if( l.OpenSession( "glove" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eGlovePartMask ), &l, &gloves );
// 	if( l.OpenSession( "trousers" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eTrousersPartMask ), &l, &trousers );
// 	if( l.OpenSession( "shoe" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eShoePartMask ), &l, &shoes );
// 	if( l.OpenSession( "weapon" ) )
// 		ReadVisual( this, CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask ), &l, &items );
// 
// 	return TRUE;
// 	unguard;
// }
// 
void CPlayer::PushHitPoint( int nStartFrameID, int nEndFrameID, int nHitPointFrameID, DWORD dwOneLoopTime )
{
	guardfunc;

	if( nStartFrameID > nHitPointFrameID || nHitPointFrameID > nEndFrameID || nHitPointFrameID == -1)
	{
		nStartFrameID = 0;
		nEndFrameID = 1;
		nHitPointFrameID = 0;
	}
	m_dwPushHitPointTime = g_dwLastFrameBeginTime;

	if( !m_bHitPointPlayOver )
	{
		OutputDebugString( "Hitpoint�Ľ�����������ش�������������m_pAttackInfoָ�����" );
		return;
	}

	float f = 0;

	if( dwOneLoopTime == 0 )
	{
		dwOneLoopTime = ( nEndFrameID - nStartFrameID )*ONEFRAMEINTERVAL;
	}

	f = (float)( nHitPointFrameID - nStartFrameID )/( nEndFrameID - nStartFrameID );
	m_dwHitPointPlayTime = m_dwPushHitPointTime + f*dwOneLoopTime + 122;
	m_bHitPointPlayOver = FALSE;
	unguard;
}

DWORD CPlayer::CalHitPointPlayTime( int nStartFrameID, int nEndFrameID, int nHitPointFrameID )
{
	if( nStartFrameID > nHitPointFrameID || nHitPointFrameID > nEndFrameID || nHitPointFrameID == -1)
	{
		nStartFrameID = 0;
		nEndFrameID = 1;
		nHitPointFrameID = 0;
	}
	DWORD dwHitPointPlayTime = g_dwLastFrameBeginTime + ( nHitPointFrameID - nStartFrameID )*ONEFRAMEINTERVAL + 122;
	return dwHitPointPlayTime;
}

BOOL CPlayer::CanPlayHitPoint()
{
	guardfunc;
	if( g_dwLastFrameBeginTime > m_dwHitPointPlayTime )
	{
		return TRUE;
	}
	return FALSE;
	unguard;
}

BOOL CPlayer::IsHitPointPlayOver()
{
	guardfunc;
	return m_bHitPointPlayOver;
	unguard;
}

void CPlayer::SetActionTarget( int nID ,const char* pName )
{
	guardfunc;
	m_nActionTargetID = nID;
	if (pName)
	{
		int length = min(strlen(pName)+1, sizeof(char)*(dr_MaxPlayerName+1));
		memcpy(m_szActionTargetName,pName,length);
	}
	else
	{
		ZeroMemory(m_szActionTargetName,sizeof(char) * (dr_MaxPlayerName + 1));

	}
	unguard;
}

void CPlayer::ClearActionTarget()
{
	m_nActionTargetID = -1;
	memset(m_szActionTargetName,0,dr_MaxPlayerName);
}
void CPlayer::PostMountMonster( int nResMexID, bool bPlayEffect, int nModelId )
{
	ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( nModelId );
	if(!pDrome)
		return;

	if( m_bRole )
		getwsCamera()->SetMountLookUpHeight( pDrome->GetMountCameraHeight() );

	if(NULL == m_pMountAnim)
	{
		assert(0&&"���ǿյ�");
		return;
	}

	if ( m_bRole && pDrome->stCarry > 1 ) //������������1��˵�������غö���
	{

		s_CUI_ID_FRAME_CrowdCarryMainMore.SetVisable(true);
		s_CUI_ID_FRAME_CrowdCarryMainMore.SetTotalSetNum( pDrome->stCarry );
		s_CUI_ID_FRAME_CrowdCarryMainMore.RefreshPassengerList( m_passengers );
		s_CUI_ID_FRAME_CrowdCarryMainMore.m_pID_TEXT_PetName->SetText( pDrome->GetName() );

	}

	m_pMountAnim->MyChangeModel( nResMexID, FALSE, pDrome->GetSkinName() );
	m_pMountAnim->SetCurAnimType(-1);

	m_nMountBoneID = MEX2NOTLOADINGCOMPLETE;
	if( m_pMountAnim->GetMex() != NULL && m_pMountAnim->GetMex()->GetSkeleton() != NULL )
	{
		m_nMountBoneID = m_pMountAnim->GetMex()->GetSkeleton()->FindBone( "Mount" );
	}

	{
		const char* pszMountSkin = NULL;
		float fRunningStep = pDrome->fRunningStep;
		float fWalkingStep = pDrome->fWalkingStep;
		pszMountSkin = pDrome->GetSkinName();
		m_fMaxStartJumpingSpeed = pDrome->fJumpingHeight*0.001f;
		m_fDromeScaleCorrect = pDrome->fDromeScaleCorrect;
		m_fRiderScaleCorrect = pDrome->fRiderScaleCorrect;

		if( pszMountSkin )
		{
			m_pMountAnim->ChangeAvatarSetting( pszMountSkin );
		}

		if( bPlayEffect && stricmp( pDrome->GetMountEffectPath(), "NULL" ) != 0 )
		{
			guard(testscale);
			PlayEffect( (char*)pDrome->GetMountEffectPath(), this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this) );
			unguard;
		}

		SetMovingStep( fWalkingStep );
		SetRunStep( fRunningStep );
		m_bMounting = TRUE;
		m_nMountModelID = nModelId;
		UpdateFootPrintDetail();

		SetFightPose(FALSE);

		///////////////////////////////////////
		if( m_bRole )
		{
			D3DXVECTOR3 vHead = D3DXVECTOR3( 0, 0, 1 );
			float fDistToCollision = 0;
			float fHeadHeight = 1.7f;
			Box* pBBox = GetWorldBBox();
			if( pBBox )
			{
				fHeadHeight = pBBox->v[4].z - pBBox->v[0].z;
			}

			D3DXVECTOR3 vNextStart = D3DXVECTOR3( GetPos().x, GetPos().y, GetPos().z + fHeadHeight );

			if( thePlayerRole.GetDistToCollision( vNextStart, vHead, &fDistToCollision ) )
			{
				if( fDistToCollision > 0 )
				{
					if( m_bMounting )
					{
						if( fDistToCollision < 80.0f*GetMe3dConfig()->m_fMdlSpaceScale )
						{
							theApp->GetPlayerMgr()->DisDrome();
							DisMount( FALSE );
						}
					}
				}
			}
		}
	}

	if(m_nMountBoneID != MEX2NOTLOADINGCOMPLETE && m_pAnim )
	{
		char szIdle[MAX_PATH] = {0};
		ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
		if( pDrome )
		{
			strcpy(szIdle, pDrome->GetMountAction( ItemDefine::MountDrive ));
		}
		else
		{
			strcpy(szIdle, "mountdrive");
		}

		if( IsHaveWeapon() )
		{
			// ����ʱҲҪ��ʾ����
			SetShowWeapon(TRUE);
		}
		m_pAnim->PlayLowerAnim(	szIdle,
			MexAnimCtrl::eNormalPlay,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			szIdle,
			MexAnimCtrl::eNormalPlay );

		UpdateAnimSetting();
	}
}
void CPlayer::MountMonster( int nModelId, int nMountLevel /*= 0*/, BOOL bPlayEffect /* = TRUE  */, bool bMultThread /*= true */)
{
	guardfunc;

	// ����Ǳ����ڳ�״̬, ֱ�ӷ���
	if (mIsYabiaoState)
		return;

	if( m_bRole )
		SitInterrupt();

	if( nModelId <= 0 )
	{
		DisMount();
		return;
	}

	if ( nMountLevel > SMountItem::MICD_MountMaxLevel || nMountLevel < 0)
	{
		DisMount();
		return;
	}

	//     ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( nModelId );
	//     if(!pDrome)
	//         return;
	//     
	//     int	nResMexID = -1;
	//     nResMexID = GetMexResMgr()->AddExternalFile( pDrome->GetModelPath() );
	//     if( nResMexID == -1 )
	//     {
	//         assert( false );
	//         return;
	//     }

	if( !m_pAnim )
	{
#ifdef NEW_PLAYER_LOAD
		// [���ģ�ͼ��ػ���]
		if( IsPlayer() )	// ���ģ��δ���أ���������ID���˳�
		{
			m_bMounting = TRUE;
			m_nMountModelID = nModelId;
			m_nMountLevel = nMountLevel;
			m_nMountBoneID = MEX2NOTLOADINGCOMPLETE;
		}
#endif
		return;
	}

	if( !m_pMountAnim )
		return;   

	ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( nModelId );
	if(!pDrome)
		return;

	//������Լ����� �����duorenzuoji ������˾��Ϊ�Լ�
	if(IsRole())
	{
		if( pDrome->stCarry > 1 )
		{
			SetCarrierDriver(GetID());
			//SetCarrierState(true);
		}
	}

	SetMountOperaType(pDrome->stOperaType); //�����������ģʽ
	// �������ģʽ, 1Ϊ����(�ؾ�), 0Ϊ��ͨ
	if(IsRole()&&IsGoudaOperaMode()) //�Ƿ����ģʽ
	{
		s_CUI_ID_FRAME_MAIN.SetVisable(false);
		s_CUI_ID_FRAME_Exmain.SetVisable(false);

		s_CUI_ID_FRAME_CarryMain.SetVisable(true);
		s_CUI_ID_FRAME_CarryMain.SetModelId(nModelId);
		s_CUI_ID_FRAME_CarryMain.UpdateCD();

		for (int n = 0;n < ItemDefine::SDrome::DCD_MASTERUSESKILLCOUNT;++n)
		{
			unsigned short usSkillID = pDrome->masterUseSKillId[n];
			if( usSkillID != 0)
				thePlayerRole.m_MountSkillBag.AddSkill(usSkillID);
		}
	}

	//����ģʽ
	if(IsGoudaOperaMode())
		m_pMountAnim->NeedInitUpperBodyAndLowerBody();
	else
		m_pMountAnim->CancelUpperBodyAndLowerBodyMode();

	int	nResMexID = -1;	
	if( !bMultThread )
	{
		//nResMexID = GetMexResMgr()->AddExternalFile( pDrome->GetModelPath() );
		nResMexID = pDrome->modelID[nMountLevel];
		if( nResMexID == -1 )
		{
			assert( false );
			return;
		}

		PostMountMonster( nResMexID, bPlayEffect, nModelId );
		return;
	}	
	SetMountInThread( true );
	m_nMountModelID = nModelId;
	m_nMountLevel = nMountLevel;
	MeLoopThreadReq* pReq = MeNew MountReq;
	if( !pReq )
		return;

	MountReq* pMountReq = dynamic_cast< MountReq* >( pReq );
	if( !pMountReq )
		return;

	pMountReq->m_bPlayEffect = bPlayEffect;
	pMountReq->m_nDromeId = nModelId;
	pMountReq->m_pPlayer = this;
	//AddRef();
	pMountReq->m_nObjectType = LoopLoadType::eMount;
	//strcpy_s( pMountReq->m_szFileName, MAX_PATH, pDrome->GetModelPath() );
	ModelConfig::ModelData* pmodeldata = theModelConfig.GetModelDataById(pDrome->modelID[nMountLevel]);
	if (!pmodeldata)
	{
		return;
	}
	strcpy_s( pMountReq->m_szFileName, MAX_PATH, pmodeldata->FilePath.c_str() );
	MeLoopThreadMan::Instance()->PostMexLoadingReq( pReq );

	unguard;
}

void CPlayer::MountMonster( char* pMonsterPath, char* pSkin )
{
	guardfunc;

	if( m_bRole )
		SitInterrupt();

	if( !pMonsterPath )
	{
		DisMount();
		return;
	}

	int	nResMexID = -1;
	nResMexID = GetMexResMgr()->AddExternalFile( pMonsterPath );
	if( nResMexID == -1 )
	{
		assert( false );
		return;
	}
	if( !m_pAnim )
	{
		return;
	}

	if( !m_pMountAnim )
		return;

	m_pMountAnim->MyChangeModel( nResMexID, FALSE, pSkin );

	m_nMountBoneID = MEX2NOTLOADINGCOMPLETE;
	if( m_pMountAnim->GetMex() != NULL )
	{
		m_nMountBoneID = m_pMountAnim->GetMex()->GetSkeleton()->FindBone( "Mount" );
	}

	if( pSkin )
	{
		m_pMountAnim->ChangeAvatarSetting( pSkin );
	}

	m_bMounting = TRUE;
	m_nMountModelID = -1;
	m_nMountLevel = 0;
	UpdateFootPrintDetail();

	char mountname[MAX_PATH] = {0};
	if( IsHaveWeapon() )
		strcpy(mountname, "single_mountdrive");
	else
		strcpy(mountname, "mountdrive");

	m_pAnim->PlayUpperAnim(	mountname,
		MexAnimCtrl::eNormalPlay,
		0,
		1,
		MexAnimCtrl::eMaxTimeout,
		MexAnimCtrl::eDefaultBlendingTime );

	m_pAnim->PlayLowerAnim(	mountname,
		MexAnimCtrl::eNormalPlay,
		0,
		MexAnimCtrl::eMaxLoopTimes,
		MexAnimCtrl::eMaxTimeout,
		MexAnimCtrl::eDefaultBlendingTime,
		mountname,
		MexAnimCtrl::eNormalPlay );

	UpdateAnimSetting();

	unguard;
}

void CPlayer::DisMount( BOOL bPlayIdleAnim /* = TRUE  */)
{
	if( !m_bMounting )
		return;
	if( m_bMounting && m_nMountModelID >= 0 )
	{
		ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
		if( pDrome )
		{
			if ( m_bRole && pDrome->stCarry > 1 ) //������������1��˵�������غö���,�����ﴦ��ֻ�������
			{
				//s_CUI_ID_FRAME_CrowdCarryMain.SetVisable(false);
				//s_CUI_ID_FRAME_CrowdCarryMain.SetTotalSet( 0 );
				s_CUI_ID_FRAME_CrowdCarryMainMore.SetVisable(false);
			}
			if( stricmp( pDrome->GetDisMountEffectPath(), "NULL" ) != 0 )
			{
				PlayEffect( (char*)pDrome->GetDisMountEffectPath(), this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this) );
			}
		}
	}

	//�Լ�������������ĳ˿�
	if ( m_passengers.size() > 0 )	//˵�����������滹���г˿�
	{
		int count = (int)m_passengers.size();
		for ( int i = 0; i < count; i ++ )
		{
			CPlayer* passenger = theHeroGame.GetPlayerMgr()->FindByID( m_passengers[i] );
			if ( passenger )
			{
				passenger->SetCarrierState(false);
				passenger->SetOthersPet(false);
			}

		}
		m_passengers.clear();
	}

	UpdateLiftFlagStatus();

	SetMovingStep( g_fTheRoleMovingStep/*1.382f*/ );
	SetRunStep( g_fTheRoleRunningStep/*3.0f*/ );
	SetUncontrolMoving(FALSE);
	m_nMountBoneID = MEX2NOTLOADINGCOMPLETE;
	m_fMaxStartJumpingSpeed = g_fPlayerDefaultJumpingSpeed;

	if( m_bMounting && m_nMountModelID >= 0 && !IsDead() && m_pAnim )
	{
		if( bPlayIdleAnim )
		{
			if( !IsMoving() )
			{
				if( IsHaveWeapon() )
				{
					SetShowWeapon(TRUE);
					m_pAnim->PlayLowerAnim(	"single_idle",
						MexAnimCtrl::eNormalPlay,
						0,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime*0.2f,
						"single_idle",
						MexAnimCtrl::eNormalPlay );

				}
				else
					m_pAnim->PlayLowerAnim(	"idle",
					MexAnimCtrl::eNormalPlay,
					0,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime*0.2f,
					"idle",
					MexAnimCtrl::eNormalPlay );
			}
			else
			{
				if( IsHaveWeapon() )
				{
					SetShowWeapon(TRUE);
					m_pAnim->PlayLowerAnim(	"single_run",
						MexAnimCtrl::eNormalPlay,
						0,
						MexAnimCtrl::eMaxLoopTimes,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime*0.2f,
						"single_run",
						MexAnimCtrl::eNormalPlay );

				}
				else
					m_pAnim->PlayLowerAnim(	"run",
					MexAnimCtrl::eNormalPlay,
					0,
					MexAnimCtrl::eMaxLoopTimes,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime*0.2f,
					"run",
					MexAnimCtrl::eNormalPlay );
				// �������Ծ������̣������ñ�־
				if( m_bNeedDropBuf && m_dwDropEndTime > 0 )
				{
					m_bNeedDropBuf = FALSE;
					m_dwDropEndTime = 0;
				}

			}
		}
	}

	m_bMounting = FALSE;
	m_nMountModelID = -1;
	m_nMountLevel = 0;
	UpdateFootPrintDetail();

	if(IsRole()&&IsGoudaOperaMode()) //�Ƿ����ģʽ
	{
		SetMountOperaType(0);
		s_CUI_ID_FRAME_MAIN.SetVisable(true);
		s_CUI_ID_FRAME_Exmain.SetVisable(true);
		s_CUI_ID_FRAME_CarryMain.SetVisable(false);
		thePlayerRole.m_MountSkillBag.ClearAllSkills();
		if(m_pAnim->IsUpperBodyAndLowerBodyMode())
			m_pAnim->ForceUpperAnimPlayOver();
	}
}

BOOL CPlayer::IsMounting()
{
	guardfunc;
	if (m_bMounting)
		return m_bMounting;
	else
		return IsMultiMounting();
	unguard;
}

bool CPlayer::IsMultiMounting()
{

	//�����˾��duorenzuoji
	if (m_nMountModelID == -1)
	{
		CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nCarrierDriver);
		if ( pPlayer)
		{
			return true;
		}
	}



	if ( m_bMounting == FALSE )
	{
		return false;
	}

	ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
	if(!pDrome)
		return false;

	if( pDrome->stCarry > 1 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CPlayer::SetCharEffectContainer( CCharEffectContainer* pCharEffectContainer )
{
	guardfunc;
	m_pCharEffectContainer = pCharEffectContainer;
	unguard;
}

BOOL CPlayer::SetTwoHalfBody( BOOL bValue )
{
	guardfunc;
	m_bTwoHalfBody = bValue;
	return TRUE;
	unguard;
}

BOOL CPlayer::SetFourFoot( BOOL bValue )
{
	guardfunc;
	m_bFourFoot = bValue;
	return TRUE;
	unguard;
}

BOOL CPlayer::IsMoving()
{
	guardfunc;
	return m_bMoving;
	unguard;
}

void CPlayer::SetMoving( BOOL bMoving )
{
	guardfunc;
	// ������Ÿ����̵�
	if ( IsOpenPrivateShop() )
	{
		if ( bMoving == TRUE )
		{
			g_bAutoRunForward = FALSE;
		}
		StopMoving();
		return;
	}
	else
	{
		if(bMoving)
		{
			GetBillBoard()->SetTipCounts(FRIST_FIGHT_OPERATE);
			m_bMoving = TRUE;
			// ������Ű�������رհ���
			if( s_CUI_ID_FRAME_PickUp.IsVisable() )
			{
				if (s_CUI_ID_FRAME_AutoAttackSet.GetRrame() && s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
				{
					//�Զ��һ��У��������ҳ���Ѿ��򿪣���ֱִ��һ��ȫ��ʰȡ��
				   s_CUI_ID_FRAME_PickUp.ID_BUTTON_PickAllOnButtonClick(NULL);
				}
				s_CUI_ID_FRAME_PickUp.ID_BUTTON_CloseOnButtonClick(NULL);
			}
		}
		else
		{
			StopMoving();
		}

	}
	unguard;
}

void CPlayer::UpdateDistanceToRole( DWORD time, float fRoleX, float fRoleY )
{
	guardfunc;
	if( !m_bRole )
	{
		float x = m_x - fRoleX;
		float y = m_y - fRoleY;
		m_fDistanceToRole = sqrtf( x*x + y*y );
	}
	unguard;
}

void CPlayer::UpdateDistanceToPickRay( float fCameraX, float fCameraY )
{
	guardfunc;
	float x = m_x - fCameraX;
	float y = m_y - fCameraY;
	m_fDistanceToPickRay = x*x + y*y;
	unguard;
}

void CPlayer::SetIntonating( BOOL bIntonating )
{
	guardfunc;

	if(m_pAnim && !bIntonating && m_bIntonating != bIntonating) //lyh (ֻ�д�����״̬����������ʱ�򣬴����ѭ����������)
		m_pAnim->ForceCurrAnimLoopTime(1,TRUE);

	m_bIntonating = bIntonating;

	unguard;
}

BOOL CPlayer::IsIntonating()
{
	guardfunc;
	return m_bIntonating;
	unguard;
}

void CPlayer::SetEffectID(int i,const char* EffectName) 
{
	m_EffectID = i;
	memset(m_EffectName,0,sizeof(m_EffectName));
	memcpy(m_EffectName , EffectName,strlen(EffectName) );
}

void CPlayer::SetName( char* pszName )
{
	guardfunc;
	HelperFunc::SafeNCpy( m_szName, pszName, MAX_NAME_STRING );
	HelperFunc::SafeNCpy( m_szDisplayName, pszName, MAX_NAME_STRING );
	unguard;
}

void CPlayer::SetReputeName(char* szRepute,DWORD curID,GameObjectId playerid,SRankManager rkmgr)
{
	guardfunc;
	CPlayer* pTargetPlayer = theApp->GetPlayerMgr()->FindByID( playerid );
	if (pTargetPlayer && pTargetPlayer->IsPlayer())
	{
		if( pTargetPlayer->GetSex() == 0 )
		{//��
			pTargetPlayer->m_szReputeName = GetSocial()->SetRepute(szRepute,curID,playerid,rkmgr, true );
		}
		else
		{//Ů
			pTargetPlayer->m_szReputeName = GetSocial()->SetRepute(szRepute,curID,playerid,rkmgr, false );
		}
	}
	unguard;
}

void CPlayer::DelReputeName(DWORD curID,GameObjectId playerid,DWORD delIndex)
{
	CPlayer* pTargetPlayer = theApp->GetPlayerMgr()->FindByID( playerid );
	if (pTargetPlayer && pTargetPlayer->IsPlayer())
	{
		pTargetPlayer->m_szReputeName = GetSocial()->DelRepute(curID,playerid,true,delIndex);	
	}
}

void CPlayer::SetGuildIconCRC( WORD stID, const char *GuildName, ULONG ulCRC)//sbw_add_guild
{
	guardfunc;
	m_strGuildIcon.GetGuildCRC( stID,GuildName,ulCRC);
	unguard;
}

void CPlayer::RegisterGuildIcon(ULONG ulCrcCode, LPBYTE pbyte,DWORD dwSize)
{
	guardfunc;
	m_strGuildIcon.RegisterIconFromServer(ulCrcCode,pbyte,dwSize);
	unguard;
}

void CPlayer::Jump()
{
	guardfunc;

	m_bJumping = TRUE;
	m_dwStartJumpingTime = g_dwLastFrameBeginTime;

	if( m_bMounting )
	{
		if( m_bMoving )
		{
			if( m_bCountermarch )
			{
				m_bJumping = FALSE;
				m_dwStartJumpingTime = 0;
			}
		}
		else
		{
			m_bJumping = FALSE;
			m_dwStartJumpingTime = 0;
		}
	}

	SwitchJumpAnim();
	if(m_bStartZMoving)
	{
		//m_z = m_fTerrainZ;
		m_fTargetZValue = 0;
		m_bStartZMoving = false;
	}
	if( IsRole() && m_bJumping )
	{
		if( !m_bMounting )
		{
			if( GetSex() == Sex_Male )
			{
				PlaySoundConfig( SoundConfig::EST_JumpM );
			}
			else
			{
				PlaySoundConfig( SoundConfig::EST_JumpF );
			}
		}
		// ��������λ��
		thePlayerRole.SetStartJumpPos(m_x, m_y, m_z);
	}
	unguard;
}

void CPlayer::AssaultMoving( GameObjectId shTargetID )
{
	guardfunc;
	float fNextX = m_x;
	float fNextY = m_y;

	CPlayer* pTargetPlayer = theApp->GetPlayerMgr()->FindByID( shTargetID );
	if( pTargetPlayer )
	{
		float fTargetX = pTargetPlayer->GetPos().x;
		float fTargetY = pTargetPlayer->GetPos().y;
		float fCurMoveDist = g_fTheRoleMovingRate*0.006f*g_dwLastFrameCostTime;
		float fPosXOff = fTargetX - m_x;
		float fPosYOff = fTargetY - m_y;
		float fOverallDist = sqrtf( fPosXOff*fPosXOff + fPosYOff*fPosYOff );
		float fDir = atan2f(fPosYOff,fPosXOff);
		float fRange = 0;
		fRange += pTargetPlayer->GetBodySize() + GetBodySize();

		SetDir(fDir);
		SetLowerDir( fDir );

		if( fCurMoveDist < fOverallDist - fRange )
		{
			float f1 = fCurMoveDist/fOverallDist;
			fNextX = fNextX + f1*fPosXOff;
			fNextY = fNextY + f1*fPosYOff;
			m_bMoving = TRUE;

			D3DXVECTOR3 vStart;
			D3DXVECTOR3 vDir = D3DXVECTOR3(0,0,0);

			vDir.x = fNextX - m_x;
			vDir.y = fNextY - m_y;

			D3DXVec3Normalize( &vDir, &vDir );

			vStart.x = m_x;
			vStart.y = m_y;

			if( m_bJumping )
			{
				vStart.z = m_z + 10.0f*GetMe3dConfig()->m_fMdlSpaceScale;				
			}
			else
			{
				vStart.z = m_z + g_fPlayerCollisionHeight*GetMe3dConfig()->m_fMdlSpaceScale;
			}

			D3DXVECTOR3 vCollisionDir = D3DXVECTOR3( 0, 0, 0 );
			D3DXVECTOR3 vCollisionNormal = D3DXVECTOR3( 0, 0, 1 );
			float fAngleToCollision = 0;
			float fDistToCollision = 0;

			if( thePlayerRole.GetDistToCollision( vStart, vDir, &fDistToCollision, &vCollisionDir, &vCollisionNormal, &fAngleToCollision ) )
			{
				if( fDistToCollision >= 0 )
				{
					if( fDistToCollision < 40.0f*GetMe3dConfig()->m_fMdlSpaceScale )
					{
						float f = D3DX_PI*0.5f - fAngleToCollision;
						if( f > 0 )
						{
							fCurMoveDist = fCurMoveDist*f;
						}

						fNextX = m_x + fCurMoveDist*vCollisionDir.x;
						fNextY = m_y + fCurMoveDist*vCollisionDir.y;

						vDir.x = fNextX - m_x;
						vDir.y = fNextY - m_y;

						if( thePlayerRole.GetDistToCollision( vStart, vDir, &fDistToCollision, &vCollisionDir, &vCollisionNormal, &fAngleToCollision ) )
						{
							if( fDistToCollision >= 0 )
							{
								//OutputDebugString( "GetDistToCollision" );
								if( fDistToCollision < 40.0f*GetMe3dConfig()->m_fMdlSpaceScale )
								{
									StopMoving();
									m_bAssaultMoving = FALSE;
									m_shAssaultTargetID = -1;
								}
								else
								{
									if( fCurMoveDist >= fDistToCollision )
									{
										StopMoving();
										m_bAssaultMoving = FALSE;
										m_shAssaultTargetID = -1;
									}
								}
							}
						}
					}
					else
					{
						if( fCurMoveDist >= fDistToCollision )
						{
							StopMoving();
							m_bAssaultMoving = FALSE;
							m_shAssaultTargetID = -1;
						}
					}					
				}
			}
		}
		else
		{
			StopMoving();
			m_bAssaultMoving = FALSE;
			m_shAssaultTargetID = -1;
		}
	}
	else
	{
		StopMoving();
		m_bAssaultMoving = FALSE;
		m_shAssaultTargetID = -1;
	}

	if( m_bAssaultMoving )
	{
		m_x = fNextX;
		m_y = fNextY;
		m_ptLoc.x = (m_x-MAPTILESIZE/2)/MAPTILESIZE+1;
		m_ptLoc.y = (m_y-MAPTILESIZE/2)/MAPTILESIZE+1;
	}
	else
	{
		SwitchIdleAnim(MexAnimCtrl::eMaxTimeout, 0);
	}
	unguard;
}

void CPlayer::InstantMoving( D3DXVECTOR3 vTargetPos, bool bCheckPos )
{
	guardfunc;
	float fNextX = m_x;
	float fNextY = m_y;

	while( m_bInstantMoving )
	{
		float moveRate = GetMoveRate();
		moveRate = moveRate <= 0.1f ? 1.5f : moveRate;
		float fCurMoveDist = moveRate * 0.001f * 30;
		float fTargetX = vTargetPos.x;
		float fTargetY = vTargetPos.y;
		float fPosXOff = fTargetX - m_x;
		float fPosYOff = fTargetY - m_y;
		float fOverallDist = sqrtf( fPosXOff*fPosXOff + fPosYOff*fPosYOff );
		float fDir = atan2f(fPosYOff,fPosXOff);

		SetDir(fDir);
		SetLowerDir( fDir );

		if( fCurMoveDist < fOverallDist )
		{
			float f1 = fCurMoveDist/fOverallDist;
			fNextX = fNextX + f1*fPosXOff;
			fNextY = fNextY + f1*fPosYOff;
			m_bMoving = TRUE;

			D3DXVECTOR3 vStart;
			D3DXVECTOR3 vDir = D3DXVECTOR3(0,0,0);

			vDir.x = fNextX - m_x;
			vDir.y = fNextY - m_y;

			D3DXVec3Normalize( &vDir, &vDir );

			vStart.x = m_x;
			vStart.y = m_y;

			if( m_bJumping )
			{
				vStart.z = m_z + 60.0f*GetMe3dConfig()->m_fMdlSpaceScale;
			}
			else
			{
				vStart.z = m_z + g_fPlayerCollisionHeight*GetMe3dConfig()->m_fMdlSpaceScale;
			}

			BOOL bRole = FALSE;

			if( m_bRole )
			{
				bRole = TRUE;
			}

			DWORD		dwLoadFlags = 0;
			BOOL		bInFloor = FALSE;
			float		fRoleHeight = 80.0f*Config::m_fMdlSpaceScale;
			D3DXVECTOR3 vCollisionDir = D3DXVECTOR3( 0, 0, 0 );
			D3DXVECTOR3 vCollisionNormal = D3DXVECTOR3( 0, 0, 1 );
			float fAngleToCollision = 0;
			float fDistToCollision = 0;
			float fHeadHeight = 1.7;
			Box* pBBox = GetWorldBBox();
			if( pBBox )
				fHeadHeight = pBBox->v[4].z - pBBox->v[0].z;
			float fZ = GetZByXY( m_z+fRoleHeight, 
				fNextX,fNextY, 0, &bInFloor, &dwLoadFlags, bRole, &m_vTargetNormal );

			float fHigh = 0.5f;

			if(m_bJumping)
				fHigh = 2.5f;

			// ����0.5�׵ĿӲ��ƶ�
			if( m_z - fZ > fHigh )
				SetInstantMoving( false, NULL );
			else
				m_z = fZ;

			D3DXVECTOR3 vHead = D3DXVECTOR3( 0, 0, 1 );

			D3DXVECTOR3 vNextStart = D3DXVECTOR3( fNextX, fNextY, m_z + fHeadHeight	);
			if( bCheckPos && theHeroGame.GetPlayerMgr()->GetMe() == this )
			{
				BOOL bCheck = theHeroGame.GetPlayerMgr()->CheckViewPlayerBBox(*(Vector*)&vDir,0.35);
				if( bCheck )
				{
					SetInstantMoving( false, NULL );
				}
			}

			if( m_bInstantMoving )
			{
				if( bCheckPos && thePlayerRole.GetDistToCollision( vNextStart, vHead, &fDistToCollision ) )
				{
					if( fDistToCollision > 0 )
					{
						if( fDistToCollision < GetPlayerHeight() )
						{
							SetInstantMoving( false, NULL );
						}
					}
				}
			}


			if( bCheckPos && thePlayerRole.GetDistToCollision( vStart, vDir, &fDistToCollision, &vCollisionDir, &vCollisionNormal, &fAngleToCollision ) )
			{
				if( fDistToCollision >= 0 )
				{
					if( fDistToCollision < 100.0f*GetMe3dConfig()->m_fMdlSpaceScale )
					{
						OutputDebugString("3");
						SetInstantMoving( false, NULL );
					}
					else
					{
						if( fCurMoveDist >= fDistToCollision )
						{
							OutputDebugString("3");
							SetInstantMoving( false, NULL );
						}
					}
				}
			}
			else
			{
				OutputDebugString( "fDistToCollision" );
			}

			if( m_bInstantMoving )
			{
				D3DXVECTOR3 vAxis(0,0,1);
				D3DXVECTOR3 vUp( 0, 0, 1 );
				vAxis = m_vTargetNormal;

				D3DXVec3Normalize( &vAxis, &vAxis );
				float fDot = D3DXVec3Dot( &vUp, &vAxis );
				float fTheta = acosf( fDot );

				if( fTheta > g_fTheRoleSlipJumpingAngle && ( vAxis.x != 0 || vAxis.y != 0 ) )
				{
					//OutputDebugString("5");
					SetInstantMoving( false, NULL );
				}
			}


			//��ˮ�е���б�İ���Ҫ��������
			if( bCheckPos && IsInWater() && m_bInstantMoving && !g_bTheRoleJumping )
			{
				float fFarWorldZ = 0.0f;
				DWORD dwLoadFlags = 0;
				BOOL  bInFloor = FALSE;
				D3DXVECTOR3 vAxis( 0, 0, 1 );
				fFarWorldZ = GetZByXY( m_z+fRoleHeight,	fNextX, fNextY, 0, &bInFloor, &dwLoadFlags, bRole,&vAxis );

				CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
				CWorldChunk* pChunk = pTile->GetChunkFromPos(fNextX, fNextY);

				if( pChunk )
				{
					float fStature = 1.2f;
					if( pBBox )
						fStature = (pBBox->v[4].z - pBBox->v[0].z) * 0.8f;

					if(  pChunk->GetLiquidHeight() - fFarWorldZ > fStature )
					{

					}
					else
					{
						D3DXVECTOR3 vUp( 0, 0, 1 );

						D3DXVec3Normalize( &vAxis, &vAxis );

						float fDot = D3DXVec3Dot( &vUp, &vAxis );
						float fTheta = acosf( fDot );

						if( fTheta > g_fTheRoleSlipJumpingAngle && ( vAxis.x != 0 || vAxis.y != 0 ) )
						{
							//OutputDebugString("6");
							SetInstantMoving( false, NULL );
						}
					}
				}
			}
			if( m_bInstantMoving )
			{
				m_x = fNextX;
				m_y = fNextY;
				g_vTheRoleTargetPos.x = m_x;
				g_vTheRoleTargetPos.y = m_y;
				g_vTheRoleTargetPos.z = m_z;
				g_bTheRoleMoveToTargetPos = FALSE;
				m_ptLoc.x = (m_x-MAPTILESIZE/2)/MAPTILESIZE+1;
				m_ptLoc.y = (m_y-MAPTILESIZE/2)/MAPTILESIZE+1;
			}
		}
		else
		{
			//OutputDebugString("7");
			SetInstantMoving( false, NULL );
		}

	}
	unguard;
}

void CPlayer::Remove( DWORD dwStartRemoveTime )
{
	guardfunc;
	if( !m_bNeedToRemove )
	{
		m_bNeedToRemove = TRUE;
		m_dwStartRemoveTime = dwStartRemoveTime;
	}
	unguard;
}

BOOL CPlayer::NeedRemove()
{
	guardfunc;
	return m_bNeedToRemove;
	unguard;
}

DWORD CPlayer::GetStartRemoveTime()
{
	guardfunc;
	return m_dwStartRemoveTime;
	unguard;
}

void CPlayer::CancelRemove()
{
	guardfunc;
	m_bNeedToRemove = FALSE;
	unguard;
}

void CPlayer::ResetRenderAlpha()
{
	guardfunc;
	m_fCurRenderAlpha = 0;
	unguard;
}

void CPlayer::SetCurRenderAlpha( float fAlpha )
{
	guardfunc;
	m_fCurRenderAlpha = fAlpha;
	unguard;
}

void CPlayer::SetFinalRenderAlpha( float fAlpha )
{
	guardfunc;
	if( m_fFinalRenderAlpha != fAlpha)
		m_fFinalRenderAlpha = fAlpha;
	unguard;
}

void CPlayer::SetDefaultFinalRenderAlpha( float fAlpha )
{
	guardfunc;
	m_fDefaultFinalRenderAlpha = fAlpha;
	unguard;
}

float CPlayer::GetDefaultFinalRenderAlpha()
{
	guardfunc;
	return m_fDefaultFinalRenderAlpha;
	unguard;
}

float CPlayer::GetFinalRenderAlpha()
{
	guardfunc;
	return m_fFinalRenderAlpha;
	unguard;
}

float CPlayer::GetCurRenderAlpha()
{
	guardfunc;
	return m_fCurRenderAlpha;
	unguard;
}

BOOL CPlayer::IsCountermarch()
{
	guardfunc;
	return m_bCountermarch;
	unguard;
}

void CPlayer::SetCountermarch( BOOL bCountermarch )
{
	guardfunc;
	m_bCountermarch = bCountermarch;
	unguard;
}

void CPlayer::SetSubPetID(GameObjectId subPetID)
{
	guardfunc;
	m_bHaveSubPet = true;
	m_SubPetID = subPetID;
	unguard;
}
GameObjectId CPlayer::GetSubPetID()
{
	guardfunc;
	return m_SubPetID;
	unguard;
}
bool CPlayer::HaveSubPet()
{
	guardfunc;
	return m_bHaveSubPet;
	unguard;
}
void CPlayer::ReleaseSubPet()
{
	guardfunc;
	m_bHaveSubPet = FALSE;
	m_SubPetID = -1;
	unguard;
}
void CPlayer::SetPetID( GameObjectId PetID )
{
	guardfunc;
	m_bHavePet = TRUE;
	m_PetID = PetID;
	unguard;
}

GameObjectId CPlayer::GetPetID()
{
	guardfunc;
	return m_PetID;
	unguard;
}

BOOL CPlayer::HavePet()
{
	guardfunc;
	return m_bHavePet;
	unguard;
}

void CPlayer::ReleasePet()
{
	guardfunc;
	m_bHavePet = FALSE;
	m_PetID = -1;
	unguard;
}

void CPlayer::SetMasterID( GameObjectId MasterID, BOOL bMasterIsMe )
{
	guardfunc;
	m_bHaveMaster = TRUE;
	m_MasterID = MasterID;
	m_bMasterIsMe = bMasterIsMe;
	unguard;
}

GameObjectId CPlayer::GetMasterID()
{
	guardfunc;
	return m_MasterID;
	unguard;
}

BOOL CPlayer::HaveMaster()
{
	guardfunc;
	return m_bHaveMaster && m_MasterID > -1;
	unguard;
}

BOOL CPlayer::MasterIsMe()
{
	guardfunc;
	if( m_bHaveMaster )
	{
		return m_bMasterIsMe;
	}
	return FALSE;
	unguard;
}

void CPlayer::ReleaseMaster()
{
	guardfunc;
	m_bHaveMaster = FALSE;
	m_MasterID = -1;
	m_bMasterIsMe = FALSE;
	unguard;
}

void CPlayer::SetCharacterID( DWORD dwCharacterID )
{
	guardfunc;
	m_dwCharacterID = dwCharacterID;
	unguard;
}

DWORD CPlayer::GetCharacterID()
{
	guardfunc;
	return 	m_dwCharacterID;
	unguard;
}

short CPlayer::GetMovingType( float fCurDir, float fMovingDir )
{
	guardfunc;
	// �ƶ��ķ����������֮��ļн�
	float fAngle = CalcRotateAngleWithDir( fCurDir, fMovingDir );
	short shMovingType = MsgPlayerMoving::eMovingForward;

	if( fAngle > 0 )
	{
		if( fAngle <= D3DX_PI/8 )
		{
			shMovingType = MsgPlayerMoving::eMovingForward;
		}
		else if( fAngle >= D3DX_PI/8 && fAngle <= D3DX_PI*3/8 )
		{
			shMovingType = MsgPlayerMoving::eMovingForwardRight;
		}
		else if( fAngle >= D3DX_PI*3/8 && fAngle <= D3DX_PI*5/8 )
		{
			shMovingType = MsgPlayerMoving::eMovingRight;
		}
		else if( fAngle >= D3DX_PI*5/8 && fAngle <= D3DX_PI*7/8 )
		{
			shMovingType = MsgPlayerMoving::eMovingRight;//eMovingCountermarchRight;
		}
		else if( fAngle >= D3DX_PI*7/8 )
		{
			shMovingType = MsgPlayerMoving::eMovingForward;//eMovingCountermarch;
		}
	}
	else
	{
		if( fAngle >= -D3DX_PI/8 )
		{
			shMovingType = MsgPlayerMoving::eMovingForward;
		}
		else if( fAngle >= -D3DX_PI*3/8 && fAngle <= -D3DX_PI/8 )
		{
			shMovingType = MsgPlayerMoving::eMovingForwardLeft;
		}
		else if( fAngle >= -D3DX_PI*5/8 && fAngle <= -D3DX_PI*3/8 )
		{
			shMovingType = MsgPlayerMoving::eMovingLeft;
		}
		else if( fAngle >= -D3DX_PI*7/8 && fAngle <= -D3DX_PI*5/8 )
		{
			shMovingType = MsgPlayerMoving::eMovingLeft;//eMovingCountermarchLeft;
		}
		else if( fAngle <= -D3DX_PI*7/8 )
		{
			shMovingType = MsgPlayerMoving::eMovingForward;//eMovingCountermarch;
		}
	}
	return shMovingType;
	unguard;
}

void CPlayer::SetCharDead( bool bDead )
{
	guardfunc;
	m_bDead = bDead;

	if( bDead )
	{		
		m_dwDeadTime = g_dwLastFrameBeginTime;

		// ����������Լ������ActionManager
		if( m_bRole )
		{
			if( s_CUI_ID_FRAME_Group_Me.GetPROGRESS_Hp() )
				s_CUI_ID_FRAME_Group_Me.GetPROGRESS_Hp()->SetFlicker( false );
			if( s_CUI_ID_FRAME_Group_Me.GetPROGRESS_Mp() )
				s_CUI_ID_FRAME_Group_Me.GetPROGRESS_Mp()->SetFlicker( false );

			g_ActionManager.Clear();
			if( GetSex() == Sex_Male )
			{
				PlaySoundConfigPos( SoundConfig::EST_DeadM, &GetPos() );
			}
			else 
			{
				PlaySoundConfigPos( SoundConfig::EST_DeadF, &GetPos() );
			}
		}		
	}
	unguard;
}
bool CPlayer::IsCanPick( int pick_playerid, int pick_player_Groupid )
{
	guardfunc;

	if( GetAdscriptionPlayerId() == -1 && GetAdscriptionGroupId() == -1 )
	{
		if( GetHold_GroupId() == true )
			return false;

		return true;
	}

	if( GetAdscriptionPlayerId() == pick_playerid )
		return true;

	if( GetAdscriptionGroupId() == pick_player_Groupid )
	{
		if( GetAdscription_teamHeader() == false )
		{
			if( GetAdscriptionPlayerId() == -1 )
				return true;
		}
		else 
		{
			//to zizi Ҫ��playerRole������ɺ���
			return thePlayerRole.IsTeamHeader();
		}
	}

	return false;

	unguard;
}


void CPlayer::MorphMonster( int nMonsterId, bool bPrivateShop /* = false */ )
{
	guardfunc;
	if( nMonsterId < 0 )
	{
		DisMorph();
		return;
	}

	ItemDefine::SMonster *pMonster;
	pMonster = GettheItemDetail().GetMonsterById( nMonsterId );

#ifdef NEW_PLAYER_LOAD
	m_bPrivateShop = FALSE;
#endif

	BOOL bMulti = TRUE;
	if( pMonster )
	{
		const char* pszMountSkin = NULL;
		float fRunningStep = pMonster->fRunStep;
		float fWalkingStep = pMonster->fMovingStep;
		pszMountSkin = pMonster->GetSkin();
		SetMorph(true);
		if( bMulti )
		{
			m_bMorphInThread = true;
		}

		if( m_pMorphAnim )
			m_pMorphAnim->MyChangeModel( pMonster->iModelID, bMulti, pszMountSkin );

		if( m_bMounting&&(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->GetID() == GetID()))
		{
			theApp->GetPlayerMgr()->DisDrome();
			DisMount( FALSE );
		}

		m_nMorphMonsterID = nMonsterId;
		SetMovingStep( fWalkingStep );
		SetRunStep( fRunningStep );
	}
	else if( bPrivateShop )
	{
		SetMorph(true);
		m_nMorphMonsterID = nMonsterId;
		if( bMulti )
		{
			m_bMorphInThread = true;
		}
		if( m_pMorphAnim )
			m_pMorphAnim->MyChangeModel( nMonsterId, bMulti,NULL );			

		if( m_bMounting&&(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->GetID() == GetID()))
		{
			theApp->GetPlayerMgr()->DisDrome();
			DisMount( FALSE );
		}
#ifdef NEW_PLAYER_LOAD
		m_bPrivateShop = TRUE;
#endif
	}
	else
	{
		return;
	}

	if( m_pMorphAnim )
	{
		m_pMorphAnim->PlayAnimByActionName( "idle",
			MexAnimCtrl::eNormalPlay,
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime,
			"idle",
			MexAnimCtrl::eNormalPlay );
		m_pMorphAnim->SetPosition(m_x, m_y, m_z);
	}
	unguard;
}



void CPlayer::DisMorph()
{
	guardfunc;
	if( m_bMounting && m_nMorphMonsterID >= 0 )
	{
		ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMorphMonsterID );
		if( pDrome )
		{
			if( stricmp( pDrome->GetDisMountEffectPath(), "NULL" ) != 0 )
			{
				guard(testscale);
				PlayEffect( (char*)pDrome->GetDisMountEffectPath(), this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this) );
				unguard;
			}
		}
	}

	guard(test2);
	SetMovingStep( g_fTheRoleMovingStep );
	SetRunStep( g_fTheRoleRunningStep );
	SetMorph(false);
	m_nMorphMonsterID = -1;
	m_fMaxStartJumpingSpeed = g_fPlayerDefaultJumpingSpeed;
#ifdef NEW_PLAYER_LOAD
	m_bPrivateShop = FALSE;
#endif
	if( m_bMoving )
	{
		if( IsInWater() )
		{
			if( m_bCountermarch )
			{
				SwitchSwimIdleAnim();
			}
			else
			{
				SwitchSwimAnim();
			}
		}
		else
		{
			SwitchRunAnim();
		}
	}

	unguard;
	unguard;
}

void	CPlayer::SetHide(bool bHide) 
{
	if(bHide == m_bHide) return; ////һ������������ֹ���ע����Ч
	m_bHide = bHide; 
	//todo:��������״̬������һЩ����,���ϱ�����ж�
	if( !IsPlayer() && !IsNpc()) return; //������Щǿ����Ч���� ֻ�����ҡ�

	if(m_bMorphing||m_bHide)
	{

		IEffect *pEffect = GetEffectMgr()->GetEffect( GetEffectID() );
		if (pEffect)
		{
			pEffect->SetDead();
		}
		ReSetEffectID();
	}
	else
	{
		if ( strcmp(m_EffectName,"NULL") != 0) //������ǿ����Ч ����ӡ�
		{
			int _CurIntensifyEffectId = PlayEffect( m_EffectName,  this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this) ,0,0,0, false);
			//SetEffectID(_CurIntensifyEffectId,m_EffectName);
			m_EffectID = _CurIntensifyEffectId;
		}
	}

}

void CPlayer::SetMorph(bool b)  //���ñ���
{
	if(b == m_bMorphing) return; //һ������������ֹ���ע����Ч
	m_bMorphing = b;
	//todo:���ݱ���״̬������һЩ����,����������ж�
	if( !IsPlayer()) return; //������Щǿ����Ч���� ֻ������

	if(m_bMorphing||m_bHide)
	{

		IEffect *pEffect = GetEffectMgr()->GetEffect( GetEffectID() );
		if (pEffect)
		{
			pEffect->SetDead();
		}
		ReSetEffectID();
	}
	else
	{
		if ( strcmp(m_EffectName,"NULL") != 0) //������ǿ����Ч ����ӡ�
		{
			int _CurIntensifyEffectId = PlayEffect( m_EffectName,  this, PlayerInfoMgr::Instance()->GetScaleForPlayer(this) ,0,0,0, false);
			m_EffectID = _CurIntensifyEffectId;
			//SetEffectID(_CurIntensifyEffectId,m_EffectName);
		}
	}
}

bool CPlayer::IsMorph()
{
	guardfunc;
	return m_bMorphing;
	unguard;
}

float CPlayer::GetTerrainZ()
{
	guardfunc;
	return m_fTerrainZ;
	unguard;
}

int CPlayer::GetIntonatingEffectID()
{
	guardfunc;
	return m_nIntonatingEffectID;
	unguard;
}

void CPlayer::StartLoggingMovePath()
{
	guardfunc;
	g_dwMovePathLogID = HQ_TimeGetTime();
	g_nMovePathCount = 0;
	m_bLoggingMovePath = true;
	unguard;
}

void CPlayer::StopLoggingMovePath()
{
	guardfunc;
	m_bLoggingMovePath = false;
	unguard;
}

void CPlayer::LoggingMovePath()
{
	guardfunc;
	static D3DXVECTOR3 vLoggingPos = D3DXVECTOR3( 0, 0, 0 ); //��¼��
	float fXOffSet = vLoggingPos.x - m_x;
	float fYOffSet = vLoggingPos.y - m_y;
	float fOverallDist = sqrtf( fXOffSet*fXOffSet + fYOffSet*fYOffSet );

	if( fOverallDist > 2 )
	{
		int nPath = g_nMovePathCount%16;
		if( nPath == 0 )
		{
			LogMovePath( "[Path%d]", g_nMovePathCount/16 );
		}

		g_nMovePathCount++;
		nPath++;
		int nCount = nPath;
		LogMovePath( "x%d=%f", nCount, m_x );
		LogMovePath( "y%d=%f", nCount, m_y );
		vLoggingPos = GetPos();
	}
	unguard;
}

BOOL CPlayer::UncontrolMoving( D3DXVECTOR3 vTargetPos, BOOL bTestCollision )
{
	guardfunc;
	float fCurMoveDist = GetMoveRate()*0.001f*g_dwSmoothFrame;
	float fPosXOff = vTargetPos.x - m_x;
	float fPosYOff = vTargetPos.y - m_y;
	float fPosZOff = vTargetPos.z - m_z;
	float fOverallDist = sqrtf( fPosXOff*fPosXOff + fPosYOff*fPosYOff + fPosZOff* fPosZOff);
	D3DXVECTOR3 vNext;
	bool bStateTurn = true;

	if( fCurMoveDist < fOverallDist )
	{
		float f1 = fCurMoveDist/fOverallDist;
		vNext.x = m_x + f1*fPosXOff;
		vNext.y = m_y + f1*fPosYOff;
		vNext.z = m_z + f1*fPosZOff;
	}
	else
	{
		vNext.x = vTargetPos.x;
		vNext.y = vTargetPos.y;
		vNext.z = vTargetPos.z;
		fCurMoveDist = fOverallDist;
		bStateTurn = false;
	}



	BOOL bCanMove = TRUE;
	if( bTestCollision )
	{
		// �ж��Ƿ�����ײ
		D3DXVECTOR3 vStart;
		vStart.x = m_x;
		vStart.y = m_y;
		vStart.z = m_z + g_fPlayerCollisionHeight*GetMe3dConfig()->m_fMdlSpaceScale;

		D3DXVECTOR3 vDir = D3DXVECTOR3(0,0,0);
		vDir.x = vNext.x - m_x;
		vDir.y = vNext.y - m_y;
		D3DXVec3Normalize( &vDir, &vDir );
		FLOAT fDistToCollision;
		if( thePlayerRole.GetDistToCollision( vStart, vDir, &fDistToCollision ) )
		{
			if( fDistToCollision < fCurMoveDist )
				bCanMove = FALSE;
		}
		// ȡvNext���ڵر�߶ȣ��ж��Ƿ����䣬�����ƶ�
		BOOL bInFloor = FALSE;
		float fZ = GetZByXY( m_z+1.5f,  vNext.x, vNext.y, 0, &bInFloor, NULL, TRUE );
		if( m_z - fZ > 0.5f )
			bCanMove = FALSE;
	}
	if( bCanMove )
	{
		if(bStateTurn)
		{
			float fDir = atan2f(fPosYOff,fPosXOff);
			SetDir(fDir);
			SetLowerDir( fDir );
			GetAngleTo2D( m_dir, &m_vCurDir.x, &m_vCurDir.y );
		}
		m_x = vNext.x;
		m_y = vNext.y;
		m_z = vNext.z;
		if( fCurMoveDist == fOverallDist )
			StopMoving();
		else
			m_bMoving = TRUE;
	}
	else
		StopMoving();

	m_ptLoc.x = (m_x-MAPTILESIZE/2)/MAPTILESIZE+1;
	m_ptLoc.y = (m_y-MAPTILESIZE/2)/MAPTILESIZE+1;
	if (IsRole())
	{
		g_vTheRoleTargetPos.x = m_x;
		g_vTheRoleTargetPos.y = m_y;
		g_vTheRoleTargetPos.z = m_z;
		g_bTheRoleMoveToTargetPos = FALSE;

		thePlayerRole.StartMoving( GetID(), g_dwLastFrameBeginTime, m_x, m_y, m_z, m_vCurDir.x, m_vCurDir.y, m_shCurMovingType );
		if( thePlayerRole.CanSendMoveMessage( g_dwLastFrameBeginTime ) )
		{
			if( m_bMoving || g_bTheRoleJumping )
			{
				thePlayerRole.SendMoveMessage( GetID(), m_x, m_y, m_z, m_vCurDir.x, m_vCurDir.y, g_dwLastFrameBeginTime, true, m_shCurMovingType, m_bLastFrameMoving );
			}
			else
			{
				thePlayerRole.SendMoveMessage( GetID(), m_x, m_y, m_z, m_vCurDir.x, m_vCurDir.y, g_dwLastFrameBeginTime, false, m_shCurMovingType, m_bLastFrameMoving );
			}
		}
	}
	return m_bMoving;
	unguard;
}

void CPlayer::SetInstantTargetPos( const D3DXVECTOR3& vTargetPos, float fDir, EInstantMovingType type, ItemDefine::SItemSkill* pSkill )
{
	guardfunc;
	SetInstantMoving( true, pSkill );
	m_eInstantMovingType = type;
	m_vInstantTargetPos = vTargetPos;
	m_fInstantMovingDir = fDir;
	unguard;
}

BOOL CPlayer::IsInFloor()
{
	guardfunc;
	return m_bInFloor;
	unguard;
}

bool CPlayer::ClearStatusEffect( int nStatusID, int nLevel )
{
	for( ItrStatusEffectContainer it = m_listStatusEffects.begin(); it != m_listStatusEffects.end(); ++it )
	{
		SStatusEffect& statuseffect = *it;

		if( statuseffect.nStatusID == nStatusID && statuseffect.nLevel == nLevel )
		{
			if( statuseffect.nEffectID >= 0 )
			{
				IEffect* pEffect = GetEffectMgr()->GetEffect( statuseffect.nEffectID );

				if( pEffect && pEffect == statuseffect.pEffect )
					pEffect->SetDead();

				statuseffect.nEffectID = -1;
				pEffect = NULL;
				m_listStatusEffects.erase( it );
				return false;
			}
			break;
		}
	}
	return true;
}


BOOL CPlayer::FindStatusEffect( int nStatusID, int nLevel )
{
	guardfunc

		for( ItrStatusEffectContainer it = m_listStatusEffects.begin(); it != m_listStatusEffects.end(); ++it )
		{
			SStatusEffect& statuseffect = *it;

			if( statuseffect.nStatusID == nStatusID && statuseffect.nLevel == nLevel )
			{
				statuseffect.bEffectKeep = TRUE;
				return TRUE;
			}
		}
		return FALSE;

		unguard
}

void CPlayer::AddStatusEffect( int nStatusID, int nLevel, int nEffectID )
{
	guardfunc

		SStatusEffect statuseffect;
	statuseffect.nStatusID = nStatusID;
	statuseffect.nLevel = nLevel;
	statuseffect.nEffectID = nEffectID;
	statuseffect.bEffectKeep = TRUE;
	statuseffect.pEffect = GetEffectMgr()->GetEffect(nEffectID);
	m_listStatusEffects.push_front( statuseffect );
	unguard
}

void CPlayer::ClearUnkeepStatusEffects()
{
	guardfunc;
	list<SStatusEffect>::iterator itNext;

	////////////////////////////////////
	for( list<SStatusEffect>::iterator it = m_listStatusEffects.begin(); it != m_listStatusEffects.end(); )
	{
		itNext = it;
		itNext++;
		SStatusEffect& statuseffect = *it;

		if( !statuseffect.bEffectKeep )
		{
			if( statuseffect.nEffectID >= 0 )
			{
				IEffect* pEffect = GetEffectMgr()->GetEffect( statuseffect.nEffectID );

				if( pEffect )
				{
					pEffect->SetDead();
				}

				statuseffect.nEffectID = -1;
				pEffect = NULL;
			}

			m_listStatusEffects.erase( it );
			it = itNext;
			continue;
		}

		it = itNext;
	}
	unguard;
}

void CPlayer::ResetStatusEffectsKeepFlag()
{
	guardfunc
		for( ItrStatusEffectContainer it = m_listStatusEffects.begin(); it != m_listStatusEffects.end(); ++it )
		{
			SStatusEffect& statuseffect = *it;
			statuseffect.bEffectKeep = FALSE;
		}
		unguard
}
void CPlayer::updateAnimNotRender()
{
	guardfunc
		if( !m_pAnim )
			return;

#if USE_ANIMATION_OPTIMIZATION
	DWORD dwTime = HQ_TimeGetTime();
	int nUpdateStep = m_fDistanceToRole - 40;

	if( nUpdateStep < 0 )
		nUpdateStep = 0;

	if( !m_bNeedRender || nUpdateStep > 20 )
		nUpdateStep = 20;

	nUpdateStep *= 10;

	if( m_pAnim->GetMex() && ( dwTime - m_dwLastUpdateAnimTime >= nUpdateStep ) )
	{
		UpdateAnimSetting();		//��û�Ż�
		m_dwLastUpdateAnimTime = dwTime;
	}
#elif USE_ANIMATION_OPTIMIZATION_FORCE
	DWORD dwTime = HQ_TimeGetTime();
	int nUpdateStep = theHeroGame.GetPlayerMgr()->GetUpdateAnimTimeStep();

	if( nUpdateStep < 0 )
		nUpdateStep = 0;

	if( !m_bNeedRender )
		nUpdateStep = 200;

	if( m_pAnim->GetMex() && dwTime - m_dwLastUpdateAnimTime >= nUpdateStep )
	{
		UpdateAnimSetting();		//��û�Ż�
		m_dwLastUpdateAnimTime = dwTime;
	}
#else
	UpdateAnimSetting();		//��û�Ż�
	m_dwLastUpdateAnimTime = dwTime;
#endif;
	unguard
}

bool CPlayer::isNPCCanAttack( CPlayer* target )
{
	if( !target )
		return false; 

	const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(target->GetNpcID());
	if(pInfo && pInfo->_nType == eNT_Patrol && thePlayerRole.GetCountry() != target->GetRealCountry())
	{
		return true;
	}
	return false;
}

bool CPlayer::canAttack(CPlayer* target )
{
	if ( !target || this == target )
		return false;

	// �ж�Ŀ���Ƿ�������
	if( target->IsDead() || target->GetHp() <= 0)
		return false;

	switch ( target->GetCharType() )
	{
	case Object_Player:
		return _canAttackPlayer( target );
		break;
	case Object_Monster:
	case Object_Effect: //��Ч��
		if (target->HaveMaster())
		{
			CPlayer* pMaster = theHeroGame.GetPlayerMgr()->FindByID(target->GetMasterID());
			return canAttack(pMaster);
		}

		if (thePlayerRole.GetInfluence() != CampDefine::NoneCamp)
		{
			if (thePlayerRole.GetInfluence() != target->GetInfluence())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		if(target->GetRealCountry() != CountryDefine::Country_Init&&
			thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry != CountryDefine::Country_Init&&
			thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry ==target->GetRealCountry() )
			return false;  //lyh++ ͬһ���ҵĹ��� ���ܹ���

		return true;

		//return (target->GetMonsterType() != eMT_Collision);
		break;
	case Object_Npc:
		{
			if (target->IsNpc())
			{
				const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(target->GetNpcID());
				if(pInfo && pInfo->_nType == eNT_Patrol && thePlayerRole.GetCountry() != target->GetRealCountry())
				{
					return true;
				}
			}
		}
		break;
	}
	return false;
}

void CPlayer::SetInfluence(int nValue)
{
	m_nInfluence = CampDefine::GetBaseFightCamp(nValue);
	m_nCampType = CampDefine::GetBattleTypeByCamp(nValue);
}

bool CPlayer::IsSameInfluence(const CPlayer* pPlayer)
{
	if (pPlayer)
	{
		if (GetInfluence() == pPlayer->GetInfluence())
		{
			return true;
		}
	}
	return false;
}

bool CPlayer::_canAttackPlayer(CPlayer* target)
{

	if( !target )
		return false;


	// �ж��Ƿ��д����
	if( IsDueling() && thePlayerRole.GetDuelTime() == 0 && thePlayerRole.GetDuelTarget() == target->GetID() )
		return true;

	// �ػ��� PK
	CWorldTile* pTile = CURRENTTILE;
	if( NULL == pTile )
		return false;
	const CountryConfig::SpecialMapSetting* pSetting = theCountryConfig.GetReliveMapSetting( thePlayerRole.GetCountry() );
	if( !pSetting )
		return false;
	/*if( pSetting->GetMapID() == pTile->GetMapId() )
	return false;*/
	// �������� PK
	pSetting = theCountryConfig.GetPrisonMapSetting( thePlayerRole.GetCountry() );
	if( !pSetting )
		return false;
	//if( pSetting->GetMapID() == pTile->GetMapId() )
	//return false;

	// ����ȼ�����(���ֱ���)
	/*int target_level = target->GetLevel();
	int sel_level = thePlayerRole.GetLevel();
	if ( target_level < PKProtectLevel || sel_level < PKProtectLevel )
	return false;*/

	// ͬ�Ӳ���ɱ
	if ( IsTeamMember( target->GetName() ) )
		return false;

	// �ж��Ƿ����޵�Buff
	if( target->m_cFightStatus.IsInvincible() )
		return false;

	//----------- modified by ZhuoMeng.Hu	[9/28/2010]  -----------
	// �����Ҷ��ܿ�
	//if( thePlayerRole.GetCountry() != target->GetRealCountry() )
	//	return true;


	//lyh++
	return CheckMapCanPk(theHeroGame.GetPlayerMgr()->GetMe(),target);

	// ��ͼ����
	switch(pTile->GetCanPk())
	{
	case MapConfig::MapData::EPKM_UnAllow_PK:
		return false;
	case MapConfig::MapData::EPKM_Challenge_PK:
		return true;
	case MapConfig::MapData::EPKM_Group_PK:
		{ 
			/*if(m_nInfluence == enumBattleInfluence_Max)
			{
			assert(0&&"m_nInfluence == enumBattleInfluence_Max");
			return false;
			}*/

			//��Ӫս���ж�,�Ƿ�����ͬһ��Ӫ
			/*if(m_nInfluence != target->GetInfluence())
			return true;
			else
			return false;*/
			return !IsSameInfluence(target);
		}
		break;
	case MapConfig::MapData::EPKM_Guild_PK:
		{
			//Ϊͬһ���� ������PK
			if(target->GetGuildId() == thePlayerRole.GetGangMgr()->GetGuildID() && thePlayerRole.GetGangMgr()->GetGuildID() != GuildDefine::InitID)
				return false;
			else 
				return true;
		}
		break;
	case MapConfig::MapData::EPKM_Team_PK:
		{
			if( thePlayerRole.IsTeamMember(target->GetName()) )
				return false;
			else
				return true;
		}
		break;
	}

	int pkMode = GetPKType();
	// ��ģʽ�ܱ������ֿ�
	if( target->GetPKType() == PKMode_Critical )
		return true;

	// ��ģʽ�ܹ������з�����������
	if( pkMode == PKMode_Critical )
		return true;

	//��ͬ��Ӫ����PK
	if (thePlayerRole.GetInfluence() != target->GetInfluence())
	{
		return true;
	}

	// ��ͨģʽ���ܿ�ͬ���ǿ�ģʽ���
	if( pkMode == PKMode_Normal )
		return false;

	if( pkMode == PKMode_Fight || pkMode == PKMode_AttackFight )
		return true;

	if( pkMode == PKMode_Guild || pkMode == PKMode_AttackGuild)
	{
		//�жϺ�Ŀ���Ƿ�ͬһ���� �ǵĻ�������PK ���ǿ���PK
		if ( GetGuildId() == GuildDefine::InitID || target->GetGuildId() == GuildDefine::InitID || GetGuildId() != target->GetGuildId())
			return true;
		else
			return false;//ͬһ����
	}
	// PKģʽ���ܿ���ͨģʽ���
	/*if( pkMode == PKMode_Fight )
	{
	if( target->GetPKType() == PKMode_Fight )
	return true;
	else
	return false;
	}*/

	return true;
}

void CPlayer::ShowHelmet(bool v)
{
	m_isShowHelmet = v;

	if (theHeroGame.GetPlayerMgr()->GetMe() == this)
	{
		thePlayerRole.m_charinfo.visual.ShowHelmet(v);
	}
}

void CPlayer::ShowHelmetAndSendMsg(bool v)
{
	ShowHelmet(v);

	MsgShowHelmet msg;
	msg.showHelmet = v;
	GettheNetworkInput().SendMsg(&msg);
}

bool CPlayer::IsShowHelmet() const
{
	return m_isShowHelmet;
}

void CPlayer::SetSignature(const char *pSignature_)
{
	//SetTitle(pSignature_);
	if(NULL == pSignature_)
		m_signature.clear();

	m_signature = pSignature_;
}

void CPlayer::ShowSignature(bool v)
{
	m_isShowSignature = v;

	if (theHeroGame.GetPlayerMgr()->GetMe() == this)
	{
		thePlayerRole.m_charinfo.visual.ShowSignature(v);
	}
}

void CPlayer::ShowSignatureAndSendMsg(bool v)
{
	ShowSignature(v);

	MsgShowSignature msg;
	msg.showSignature = v;
	GettheNetworkInput().SendMsg(&msg);
}

bool CPlayer::IsShowSignature(void) const
{
	return m_isShowSignature;
}

void CPlayer::ShowRankTitle( bool v )
{
	m_isShowRankTitle = v;

	if (theHeroGame.GetPlayerMgr()->GetMe() == this)
	{
		thePlayerRole.m_charinfo.visual.ShowRankTitle(v);
	}
}

bool CPlayer::IsShowRankTitle() const
{
	return m_isShowRankTitle;
}

void CPlayer::SetRankTitleId( short titleId )
{
	m_shRankTitleId = titleId;
}

short CPlayer::GetRankTitleId()
{
	return m_shRankTitleId;
}

//add by yanli  2010-9-27
//----------------------------------------------------
void CPlayer::ShowAecpratove(bool v)
{
	m_isShowAecpratove = v;

	if (theHeroGame.GetPlayerMgr()->GetMe() == this)
	{
		thePlayerRole.m_charinfo.visual.ShowAecorative(v);
	}
}

void CPlayer::ShowAecpratoveAndSendMsg(bool v)
{
	ShowAecpratove(v);

	MsgSwitchSuit msg;
	msg.nSuitIndex =  v;
	GettheNetworkInput().SendMsg(&msg);
}

bool CPlayer::IsShowAecpratove() const
{
	return m_isShowAecpratove;
}

void	CPlayer::clear()
{
	PlayerOwnList.clear();
}

short   CPlayer::GetReputeID(int vecIndex)
{
	if (vecIndex < PlayerOwnList.size())
	{
		return PlayerOwnList[vecIndex].usReputeID;
	}else{
		return 0;
	}
}

void CPlayer::CallForRepute(DWORD flag)
{
	GetSocial()->dwFlag = flag;
	BinaryList	bl;
	::CopyMemory(&bl,&GetSocial()->dwFlag,sizeof(DWORD));
	for (int i = 1; i <= GettheItemDetail().GetReputeListSize(); i++)
	{
		if (bl.b & (1 << i))
		{
			PlayerOwnList.push_back(*(GettheItemDetail().GetReputeById(i)));
		}
	}
}

void CPlayer::SetShowWeapon( BOOL bShow, BOOL bShowAfterBlend/* = FALSE*/ )
{
	/*
	* Author: 2013-1-19 14:11:23 wangshuai
	* Desc:   ��ʱ����������
	*/
	bShow = TRUE;

	if( m_pAnim && m_pAnim->GetAvatar() )
	{
		if( m_pAnim->GetAvatar()->GetComponent(eKeyAll_RHandItem) )
		{
			if( !bShow )// ��������
				m_pAnim->GetAvatar()->GetComponent(eKeyAll_RHandItem)->SetCanSee(bShow);
			else
			{
				// ��ʾ����
				if( !bShowAfterBlend )
					m_pAnim->GetAvatar()->GetComponent(eKeyAll_RHandItem)->SetCanSee(TRUE);
				else
					m_pAnim->GetAvatar()->GetComponent(eKeyAll_RHandItem)->SetCanSeeAfterBlend(TRUE);
			}
		}
		if(m_pAnim->GetAvatar()->GetComponent(eKeyAll_LHandItem))
		{
			if( !bShow )// ��������
				m_pAnim->GetAvatar()->GetComponent(eKeyAll_LHandItem)->SetCanSee(bShow);
			else
			{	// ��ʾ����
				if( !bShowAfterBlend )
					m_pAnim->GetAvatar()->GetComponent(eKeyAll_LHandItem)->SetCanSee(TRUE);
				else
					m_pAnim->GetAvatar()->GetComponent(eKeyAll_LHandItem)->SetCanSeeAfterBlend(TRUE);
			}
		}
	}
}

void  CPlayer::HideOrShowPlayerEffect(bool bShow )
{

	if(!IsPlayer()) return;
	if(GetEffectID() == -1) return;
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if(!pMe) //����Լ��������� �����װ��ǿ����Ч
		return;

	IEffect *pEffect = GetEffectMgr()->GetEffect( GetEffectID() );
	if (!pEffect) return;

	CModelEffect * _ModeEffect = (CModelEffect*)pEffect;

	int InstanceCnt = _ModeEffect->m_nNumInstance;
	for (int i = 0 ;i < InstanceCnt ; i++)
	{
		CWSModelEffect::Instance * ins = _ModeEffect->GetInstance( i);
		if( !ins) continue;
		ins->bVisible = bShow;
	}
}

VOID CPlayer::SetNeedRender()	
{

	m_bNeedRender = TRUE; m_dwLastRenderTime = HQ_TimeGetTime(); 
	HideOrShowPlayerEffect();

}

void CPlayer::ResetNeedRender()
{
	m_bNeedRender = FALSE;

	if (fontName_)
	{
		fontName_->SetVisible(false);
	}
	if (m_pHpPB3D)
		m_pHpPB3D->SetVisible(false);

	HideOrShowPlayerEffect(false);

}

void CPlayer::SwitchStandAnim()
{
	guardfunc;
	if( m_bRole )
	{
		if( !m_pAnim || g_bTheRoleJumping || m_bDead )
		{
			return;
		}
	}
	else
	{
		if( !m_pAnim || m_bDead )
		{
			return;
		}
	}

	if( IsPlayer() )
	{
		int nStandctionId = MoreActionClient::stand;
		int nIdleActionId = MoreActionClient::Idle;
		if( !HasFightFlag(eFighting) && !IsFightPose() )
		{
			if( IsHaveWeapon() )
			{
				nIdleActionId = MoreActionClient::single_idle;
			}
		}
		else
		{
			if( IsHaveWeapon() )
			{
				nIdleActionId = MoreActionClient::single_attack_idle;
			}
			else
			{
				nIdleActionId = MoreActionClient::Attack_idle;
			}
		}

		if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
		{
			m_pAnim->PlayLowerAnim(	nStandctionId,
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				nIdleActionId,
				MexAnimCtrl::eNormalPlay );
		}
		else
		{
			m_pAnim->PlayAnim2( nStandctionId,
				MexAnimCtrl::eNormalPlay, 
				0,
				1, 
				MexAnimCtrl::eMaxTimeout, 
				nIdleActionId,
				MexAnimCtrl::eNormalPlay );
		}
	}
	m_dwStartStopMovingTime = g_dwLastFrameBeginTime;

	unguard;
}

BOOL CPlayer::IsCurrNormalAttackAnim()
{
	if( !m_pAnim )
		return FALSE;

	int nUpperAnimType = m_pAnim->GetCurUpperAnimType();
	if( nUpperAnimType == MoreActionClient::Attack1 
		|| nUpperAnimType == MoreActionClient::Attack2
		|| nUpperAnimType == MoreActionClient::Attack3
		|| nUpperAnimType == MoreActionClient::single_attackl1
		|| nUpperAnimType == MoreActionClient::single_attackl2
		|| nUpperAnimType == MoreActionClient::single_attackr1
		|| nUpperAnimType == MoreActionClient::single_attackr2
		)
		return TRUE;

	return FALSE;
}

void CPlayer::Face2FaceWithNpc( CPlayer* pNpc )
{
	float ftx = 0;
	float fty = 0;
	float fsx = 0;
	float fsy = 0;

	// added, jiayi, [2009/8/27], ��ֹcrash
	if( !pNpc )
	{
		assert( 0 && "Face2FaceWithNpc, pNpc = NULL" );
		return;
	}

	ftx = pNpc->GetPos().x;
	fty = pNpc->GetPos().y;
	fsx = GetPos().x;
	fsy = GetPos().y;

	/////////////
	if ( !(pNpc->GetShowFlag()&eNotChangeDir) )
	{
		pNpc->SetDir(atan2f((float)(fsy - fty), (float)(fsx - ftx)));
		pNpc->SetLowerDir(atan2f((float)(fsy - fty), (float)(fsx - ftx)));
	}

	if ( !(GetShowFlag()&eNotChangeDir) )
	{
		SetDir( atan2f((float)(fty - fsy), (float)(ftx - fsx)));
	}
}

void CPlayer::SitInterrupt()
{
	if( m_bRole && GetSitStatus() && !GetSitInterrupt() )
	{
		SetSitInterrupt(1);
		// ֪ͨ�������ı�sit״̬
		theApp->GetPlayerMgr()->ProcessCommand("DoSitDown");
	}
}

void CPlayer::InitShadowDecal()
{
	if( m_pkShadowDecal )
		return;

	m_pkShadowDecal = MeNew CNdlDecalRes;
	char filename[MAX_PATH] = {0};
	MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s\\Data\\TEXTURE\\Effect\\shadow.tga", GetRootPath());

	if( !m_pkShadowDecal->Create( filename, 0.85f) )
	{
		SAFE_DELETE( m_pkShadowDecal);
	}
}

CNdlDecalRes* CPlayer::GetShadowDecal() 
{
	if (  m_pkShadowDecal == NULL )
	{
		InitShadowDecal();
	}
	return m_pkShadowDecal;
}

void CPlayer::UpdateDecalShadow()
{
	if (IsNeedShowShadowDecal())
	{
		CNdlDecalRes* pShadowDecal = GetShadowDecal();
		if( !pShadowDecal )
			return;
		float pos[3] = {m_x,m_y,m_z};
		pShadowDecal->SetPos(pos);
		if (IsMonster())
		{
			if (!pShadowDecal->IsExistDecalShape())
			{
				pShadowDecal->SetFloorDecalEnable(false);
			}
		}
		m_LastRenderShadowDecal = TRUE;
	}
}

bool CPlayer::IsNeedShowShadowDecal()
{
	if (IsPlayer() || IsNpc() || IsMonster())
	{
		return ( GetShaderMgr()->GetShadowType() == eShadow_Fake || !SystemSetting::Instance()->IsAdvance() || !theHeroGame.GetPlayerMgr()->IsPlayerCanRender( this ) ) && (!m_cFightStatus.IsHide() || m_bRole);
	}
	return false;
}

CFootPrint* CPlayer::GetFootPrint() 
{
	if (m_footPrint == NULL)
	{
		m_footPrint = MeNew CFootPrint(IsMonster());
		if (IsMonster())
		{
			ItemDefine::SMonster* pMonster = GettheItemDetail().GetMonsterById(GetMonsterID());
			if (pMonster == NULL)
			{
				m_footPrint->SetMonster(false);
			}
			else
			{
				int frontTexture = -1;
				int backTexture = -1;
				frontTexture = GetEngine()->GetTextureManager()->RegisterTexture( GetFullFileName((char*)pMonster->GetFrontFootPrintPath()), TRUE ,TRUE);
				backTexture = GetEngine()->GetTextureManager()->RegisterTexture( GetFullFileName((char*)pMonster->GetBackFootPrintPath()), TRUE ,TRUE);
				m_footPrint->SetFootTex(backTexture,frontTexture);
				m_footPrint->SetDeltaForBody(pMonster->fBodyLengthSize*0.11);
				m_footPrint->SetStepLength(pMonster->fMovingStep/2);
				if (pMonster->nIsHaveFourFoot)
				{
					m_footPrint->SetFootPrintType(CFootPrint::eFourFoot);
					GetFootPrint()->SetScale(0.42);
				}
				else
				{
					GetFootPrint()->SetScale(0.22);
				}
			}			
		}
		else
		{
			UpdateFootPrintDetail();
		}
	}
	return m_footPrint;
}

BOOL CPlayer::IsNeedShowFootPrint()
{
	CWorldTile* pTile = CURRENTTILE;
	if(NULL == pTile)
	{
		return FALSE;
	}
	return pTile->GetShowFootPrint() && (IsPlayer() || IsMonster())  ;
}

void CPlayer::UpdateFootPrint()
{
	if (!IsNeedShowFootPrint())
		return;

	GetFootPrint()->Update();
	if (!g_bRenderFootPrint )
		return;

	if (IsJumping() || (m_cFightStatus.IsHide() & (!m_bRole)) || IsUncontrolMoving() || IsCarrierint() || (abs(m_tx) < 0.001 && abs(m_ty) < 0.001) || (IsInWater()))
	{
	}
	else
	{
		if (m_distanceDelta > GetFootPrint()->GetStepLength())
		{
			D3DVECTOR pos = {m_x,m_y,m_z};
			GetFootPrint()->AddFootPrint(pos,m_fTargetLowerBodyDir);
			m_distanceDelta = 0;
		}
	}	
}

void CPlayer::UpdateFootPrintDetail()
{
	if (!IsNeedShowFootPrint())
	{
		return;
	}
	if(m_bMounting)
	{
		ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
		if( pDrome )
		{
			GetFootPrint()->SetDeltaForBody(0.42);
			if (pDrome->shMoveType == 0)
			{
				GetFootPrint()->SetFootPrintType(CFootPrint::eTwoFoot);
			}
			else
			{
				GetFootPrint()->SetFootPrintType(CFootPrint::eFourFoot);
			}
			int frontTexture = -1;
			int backTexture = -1;
			frontTexture = GetEngine()->GetTextureManager()->RegisterTexture( GetFullFileName((char*)pDrome->GetFrontFootPrintPath()), TRUE ,TRUE);
			backTexture = GetEngine()->GetTextureManager()->RegisterTexture( GetFullFileName((char*)pDrome->GetBackFootPrintPath()), TRUE ,TRUE);
			GetFootPrint()->SetFootTex(backTexture,frontTexture);
			GetFootPrint()->SetStepLength(2.2);
			GetFootPrint()->SetScale(0.42);
		}
	}
	else
	{
		GetFootPrint()->SetDeltaForBody(0.11);
		GetFootPrint()->SetFootPrintType(CFootPrint::eTwoFoot);
		GetFootPrint()->SetStepLength(0.9);
		GetFootPrint()->SetScale(0.22);

	}
}

void CPlayer::RenderShadowDecal( BOOL bCombineRenderShadowDecal/* = FALSE*/ )
{
	// NPC��������ʾ
	if( IsNpc() && IsHide() )
		return;

	if (!IsNeedShowShadowDecal() || !GetShadowDecal() )
		return;

	CNdlDecalRes* pShadowDecal = GetShadowDecal();
	if( bCombineRenderShadowDecal )
		pShadowDecal->CombineRenderData();
	else
		pShadowDecal->Render();

}

bool CPlayer::IsCollection(bool bEnsure)
{

	bool bRet = GetMonsterType() == eMT_Herb || GetMonsterType() == eMT_Mine || GetMonsterType() == eMT_Mount || GetMonsterType() == eMT_Insect || GetMonsterType() == eMT_Treasure;
	if (bEnsure)
	{
		return  EnsureCollection(bRet);
	}
	return bRet;
}

bool CPlayer::IsMonsterType( short stMonsterType )
{
	// ���Ӳ���     added by zhuomeng.hu		[11/9/2010]
	if (stMonsterType == eMT_Herb || stMonsterType == eMT_Mine || stMonsterType == eMT_Mount || stMonsterType == eMT_Insect
		|| stMonsterType == eMT_Treasure)
	{
		bool bRet = ( m_stMonsterType == stMonsterType );
		return  EnsureCollection( bRet );
	}
	else
	{
		return m_stMonsterType == stMonsterType;
	}
}

bool CPlayer::EnsureCollection( bool bRet )
{
	if (!bRet)
		return false;

	ItemDefine::SMonster* pMonster =  GettheItemDetail().GetMonsterByName(GetName());
	if (pMonster && pMonster->nRelativeQuest != 0)
	{
		bRet = false;
		SQuest* pQuest = theQuestManager.GetQuest(pMonster->nRelativeQuest);
		CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById(pMonster->nRelativeQuest);

		if (pInfo && theQuestManager.IsQuestActive(pInfo->chState) && pQuest)
		{
			std::vector<SQuestRequirement>& stCommitRequirement = pQuest->stCommitRequirement;
			for(std::vector<SQuestRequirement>::iterator workitr = stCommitRequirement.begin() ; workitr != stCommitRequirement.end() ; ++workitr)
			{
				if (workitr->byType == SQuest::eRequirement_Item)
				{
					SQuestRequirement *pRequirement = &(*workitr);
					ItemDefine::SItemCommon* pItemDetail = NULL;
					pItemDetail = GettheItemDetail().GetItemByID( pRequirement->Value );
					if( pItemDetail )
					{
						int nItemCount = thePlayerRole.m_bag.GetItemCount( pItemDetail->ustItemID );
						if (nItemCount < 1)
						{
							nItemCount = thePlayerRole.m_bagMaterial.GetItemCount( pItemDetail->ustItemID );
							if (nItemCount < 1)
								nItemCount = thePlayerRole.m_bagTask.GetItemCount( pItemDetail->ustItemID );
						}

						if( nItemCount < pRequirement->MaxNum )
						{
							bRet = true;
							break;
						}

					}
				}
			}
		}
	}
	if( m_nCollectionEffectID == -1 && bRet )
	{
		m_nCollectionEffectID = PlayEffect("common\\QuestItem.ini",this);
		if( IsItem() )
			m_bCanPick = true;
	}
	else if(m_nCollectionEffectID != -1 && !bRet )
	{
		IEffect* pEffect = GetEffectMgr()->GetEffect( m_nCollectionEffectID );
		if( pEffect )
		{
			pEffect->SetDead();
		}
		m_nCollectionEffectID = -1;
		if( IsItem() )
			m_bCanPick = false;
	}


	return bRet;
}

bool CPlayer::IsDisableCollection()
{
	bool bRet = GetMonsterType() == eMT_Herb || GetMonsterType() == eMT_Mine || GetMonsterType() == eMT_Mount || GetMonsterType() == eMT_Insect || GetMonsterType() == eMT_Treasure;
	if (bRet && !EnsureCollection(bRet))
		return true;
	return false;
}

void CPlayer::LoadRippleEffect()
{
	if( m_nWaterSideRippleEffectID == -1 )
		LoadWaterSideEffect();

	if( m_nRippleEffectID == -1 )
		LoadRippleIDEffect();

	if( m_nBoatRippleEffectID == -1 )
		LoadBoatRippleEffect();
}

void  CPlayer::LoadWaterSideEffect()
{
	CWSModelEffect* pEffect = MeNew CWSModelEffect;
	if(!pEffect)
		return;

	if( !pEffect->LoadSetting( GetFullFileName("data\\effect\\common\\RippleEffect.ini") ) )
	{
		pEffect->Release();
		pEffect = NULL;
		return;
	}

	m_nWaterSideRippleEffectID = GetEffectMgr()->RegisterEffect( pEffect );
	if( m_nWaterSideRippleEffectID == -1 )
	{
		pEffect->Release();
		pEffect = NULL;
		return;
	}

	m_nWaterSideRippleEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
	pEffect->m_dwBornTime = HQ_TimeGetTime();
	float fRadius = pEffect->m_fRadius;
	int nNum = pEffect->m_nNumInstance;

	CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( m_nWaterSideRippleEffectContainerID );

	for( int nInst = 0; nInst < nNum; nInst++ )
	{
		CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
		if( !pInstance )
		{
			continue;
		}

		pInstance->dwBornTime = HQ_TimeGetTime() + pInstance->fDelay;

		if( pEffectContainer )
		{
			pEffect->SetEffectQuoter( pEffectContainer );
		}

		pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
		pInstance->vPos = pInstance->vBornPos;
		pInstance->bVisible = FALSE;

		// ����Ч��
		if( pEffectContainer )
		{
			pInstance->pMaster = pEffectContainer->GetEffectHelper( eEffectBindPart_Body );
		}
	}

	if( pEffectContainer )
	{
		pEffectContainer->ApplyEffect( 0, pEffect->GetID() );
	}
}

void CPlayer::LoadBoatRippleEffect()
{
	CWSModelEffect* pEffect = MeNew CWSModelEffect;
	if(!pEffect)
		return;

	if( !pEffect->LoadSetting( GetFullFileName("data\\effect\\common\\BoatRippleEffect.ini") ) )
	{
		pEffect->Release();
		pEffect = NULL;
		return;
	}

	m_nBoatRippleEffectID = GetEffectMgr()->RegisterEffect( pEffect );
	if( m_nBoatRippleEffectID == -1 )
	{
		pEffect->Release();
		pEffect = NULL;
		return;
	}

	m_nBoatRippleEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
	pEffect->m_dwBornTime = HQ_TimeGetTime();
	float fRadius = pEffect->m_fRadius;
	int nNum = pEffect->m_nNumInstance;

	CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( m_nBoatRippleEffectContainerID );

	for( int nInst = 0; nInst < nNum; nInst++ )
	{
		CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
		if( !pInstance )
		{
			continue;
		}

		pInstance->dwBornTime = HQ_TimeGetTime() + /*pEffect->m_dwDelay*nInst*/pInstance->fDelay;

		if( pEffectContainer )
		{
			pEffect->SetEffectQuoter( pEffectContainer );
		}

		pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
		pInstance->vPos = pInstance->vBornPos;
		pInstance->bVisible = FALSE;

		// ����Ч��
		if( pEffectContainer )
		{
			pInstance->pMaster = pEffectContainer->GetEffectHelper( eEffectBindPart_Body );
		}
	}

	if( pEffectContainer )
	{
		pEffectContainer->ApplyEffect( 0, pEffect->GetID() );
	}
}

void CPlayer::LoadRippleIDEffect()
{
	CWSModelEffect* pEffect = MeNew CWSModelEffect;
	if(!pEffect)
		return;

	if(! pEffect->LoadSetting( GetFullFileName("data\\effect\\common\\RippleEffect.ini") ) )
	{
		pEffect->Release();
		pEffect = NULL;
		return;
	}

	m_nRippleEffectID = GetEffectMgr()->RegisterEffect( pEffect );
	if( m_nRippleEffectID == -1 )
	{
		pEffect->Release();
		pEffect = NULL;
		return;
	}

	m_nRippleEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
	pEffect->m_dwBornTime = HQ_TimeGetTime();
	float fRadius = pEffect->m_fRadius;
	int nNum = pEffect->m_nNumInstance;

	CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( m_nRippleEffectContainerID );

	for( int nInst = 0; nInst < nNum; nInst++ )
	{
		CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
		if( !pInstance )
		{
			continue;
		}

		pInstance->dwBornTime = HQ_TimeGetTime() + pInstance->fDelay;

		if( pEffectContainer )
		{
			pEffect->SetEffectQuoter( pEffectContainer );
		}

		pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
		pInstance->vPos = pInstance->vBornPos;
		pInstance->bVisible = FALSE;

		// ����Ч��
		if( pEffectContainer )
		{
			pInstance->pMaster = pEffectContainer->GetEffectHelper( eEffectBindPart_Body );
		}
	}

	if( pEffectContainer )
	{
		pEffectContainer->ApplyEffect( 0, pEffect->GetID() );
	}
}


void CPlayer::StopRippleEffect( int nRippleEffectID )
{
	CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( nRippleEffectID );
	if( pModelEffect )
	{
		int nNum = pModelEffect->m_nNumInstance;
		for( int nInst = 0; nInst < nNum; nInst++ )
		{
			CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

			if( !pInstance )
				continue;

			if( pInstance->bVisible )
			{
				pInstance->bVisible = FALSE;
				pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
			}
		}
	}
}

BOOL CPlayer::IsRenderParticleEmitters()
{
	switch(g_nRenderParticleEmittersLevel)
	{
	case 0:
		{
			return false;
		}
		break;
	case 1:
		{
			return (IsRole());
		}
		break;
	case 2:
		{
			return true;
		}
		break;
	}
	return true;
}

void CPlayer::SwitchLiftFlagAnim()
{
	guardfunc;
	if( !IsMounting() || GetProfession() != EArmType_Taoist || !IsHaveWeapon() )
		return;

	if (NULL != m_pAnim)
	{
		int nActionId = MoreActionClient::single_flag_idle;
		if( IsMoving() )
		{
			nActionId = MoreActionClient::single_flag_run;
		}
		m_pAnim->PlayUpperAnim( nActionId,
			MexAnimCtrl::eNormalPlay, 
			0,
			MexAnimCtrl::eMaxLoopTimes,
			MexAnimCtrl::eMaxTimeout,
			MexAnimCtrl::eDefaultBlendingTime );
	}

	unguard;
}

void CPlayer::UpdateLiftFlagStatus( void )
{
	// �����ȡ�����Ӻ��޷�����
	if( GetLiftFlagStatus() <= 0 )
		return;

	if( !m_bMounting || !IsHaveWeapon() || !IsFlagModel(GetWeaponModelID()) )
	{
		SetLiftFlagStatus(0);
		GetAnim()->ForceCurrAnimLoopTime(-1,TRUE);
		// �㲥���������
		theApp->GetPlayerMgr()->SendDrawInWeapon();
	}    
}

//int CPlayer::GetWeaponModelID(BOOL bLeft/* = FALSE*/)
//{
//    guardfunc;
//    if( IsRole() )
//    {
//        SCharItem* suits = thePlayerRole.m_charinfo.visual.GetAttriSuitArray();
//        if( bLeft )
//            return suits[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandItemPartMask )].itembaseinfo.ustItemID;
//        else
//            return suits[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask )].itembaseinfo.ustItemID;
//    }
//    else
//    {
//        if( bLeft )
//            return m_equips[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandItemPartMask )].item.itembaseinfo.ustItemID;
//        else
//            return m_equips[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask )].item.itembaseinfo.ustItemID;
//    }
//    unguard;
//}

//add by yanli  2010-9-27
int CPlayer::GetWeaponModelID(BOOL bLeft/* = FALSE*/)
{
	guardfunc;
	if( IsRole() )
	{
		SCharItem* suits = thePlayerRole.m_charinfo.visual.GetVisualArray();
		if( bLeft )
			return suits[eKeyAll_LHandItem].itembaseinfo.ustItemID;
		else
			return suits[eKeyAll_RHandItem].itembaseinfo.ustItemID;
	}
	else
	{
		if( bLeft )
			return m_equips[eKeyAll_LHandItem].item.itembaseinfo.ustItemID;
		else
			return m_equips[eKeyAll_RHandItem].item.itembaseinfo.ustItemID;
	}
	unguard;
}

const std::vector<swVec2f> & CPlayer::GetFoundPathUnLocked()
{
	return m_FoundPath;
}

std::vector<swVec2f> & CPlayer::GetFoundPathAndLocked()
{
	if (!m_bFoundPathCSInitialize)
	{
		InitializeCriticalSection(&m_FoundPathCS);
		m_bFoundPathCSInitialize = true;
	}
	EnterCriticalSection(&m_FoundPathCS);
	return m_FoundPath;
}

void CPlayer::UnlockedFoundPath()
{
	LeaveCriticalSection(&m_FoundPathCS);;
}

BOOL CPlayer::IsCollectionAnim( const char* szAnim )
{
	if( !stricmp(szAnim,"loot") || !stricmp(szAnim,"intonate")||!stricmp(szAnim,"rideintonate")||!stricmp(szAnim,"rideloot") )
		return TRUE;

	return FALSE;
}

void CPlayer::SetIntonatingTarget( CPlayer* pTarget )
{
	m_pIntonateTarget = pTarget;
	if( GetIntonatingTarget() )
		SetIntonatingTargetID( m_pIntonateTarget->GetID() );
	else
		SetIntonatingTargetID( -1 );
}

BOOL CPlayer::CheckAdvanceSkill( unsigned short nSkillID, unsigned short nSkillLevel )
{
	if( m_vctAdvanceSkill.size() <= 0)
		return FALSE;

	std::vector<SAdvanceSkillData>::iterator iter;
	for(iter = m_vctAdvanceSkill.begin(); iter != m_vctAdvanceSkill.end(); ++iter )
	{
		SAdvanceSkillData kAdvSkillData = *iter;
		if( kAdvSkillData.pSkill->ustLevel == nSkillLevel && kAdvSkillData.pSkill->ustItemID == nSkillID )
		{
			m_vctAdvanceSkill.erase(iter);
			return TRUE;
		}
	}    
	return FALSE;
}

BOOL CPlayer::RemoveAdvanceSkillByID( int nSkillID )
{
	if( m_vctAdvanceSkill.size() <= 0 )
		return FALSE;

	std::vector<SAdvanceSkillData>::iterator iter;
	for(iter = m_vctAdvanceSkill.begin(); iter != m_vctAdvanceSkill.end(); ++iter )
	{
		SAdvanceSkillData kAdvSkillData = *iter;
		if( kAdvSkillData.pSkill && kAdvSkillData.pSkill->ustItemID == nSkillID )
		{
			m_vctAdvanceSkill.erase(iter);
			return TRUE;
		}
	}

	return FALSE;
}

void CPlayer::SwitchEmbraceAnim()
{
	guardfunc;
	if (!m_pAnim)
		return;

	int idleAnim = MoreActionClient::Idle;
	if( IsHaveWeapon() )
	{
		idleAnim = MoreActionClient::single_idle;
		SetShowWeapon(FALSE);
	}
	m_pAnim->PlayLowerAnim(	MoreActionClient::yongbao,
		MexAnimCtrl::eNormalPlay,
		0,
		1,
		MexAnimCtrl::eMaxTimeout,
		10,
		idleAnim,
		MexAnimCtrl::eNormalPlay );
	if( m_nInteractionMasterPlayerID != -1 )
		m_bNeedResetPosAfterInteraction = TRUE;

	unguard;
}

void CPlayer::SwitchReliveAnim()
{
	if(!m_pAnim)
		return;

	int idleAnim = MoreActionClient::Idle;
	m_pAnim->PlayUpperAnim(MoreActionClient::single_revive,
		MexAnimCtrl::eNormalPlay,
		0,
		1,
		MexAnimCtrl::eMaxTimeout,
		MexAnimCtrl::eDefaultBlendingTime,
		TRUE);
}

void CPlayer::SwitchDropItemAnim()
{
	if(!IsItem())
		return;

	if(!m_bPlayDropAnim)
		return;

	if(!m_pAnim || !m_pAnim->GetMex() || !m_pAnim->GetMexCfg())
		return;

	if(!IsItemDropDelayOver())
		return;

	MexCfgSequence* pSeq = m_pAnim->GetMexCfg()->GetSequence("box_drop");
	if(!pSeq)
		return;

	if(m_pAnim->GetCurAnimType() == MoreActionClient::box_stand)
		return;

	if(IsWillPlayDropAnim())
		PlayAnim("box_drop",1,"box_stand");
	else
		PlayAnim("box_stand",1,"box_stand");

	m_bPlayDropAnim = false;
}

BOOL CPlayer::IsCanPlayInteraction( CPlayer* pTargetPlayer, BOOL& bTooFar, BOOL& bZTooFar )
{
	if( !pTargetPlayer )
		return FALSE;

	// �ж�����״̬
	if( IsMounting() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OneAnother, theXmlString.GetString( eText_InteractionFailed_InMounting ) );
		return FALSE;
	}
	if( IsInWater() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OneAnother, theXmlString.GetString( eText_InteractionFailed_InWater ) );
		return FALSE;
	}
	if( HasFightFlag(eFighting) )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OneAnother, theXmlString.GetString( eText_InteractionFaided_InFighting ) );
		return FALSE;
	}
	if( IsLootOrIntonateAnim() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OneAnother, theXmlString.GetString( eText_InteractionFailed_InLooting ) );
		return FALSE;
	}
	if( IsDead() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OneAnother, theXmlString.GetString( eText_InteractionFailed_IsDead ) );
		return FALSE;
	}

	// �ж϶Է�״̬
	if( pTargetPlayer->IsMounting() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OneAnother, theXmlString.GetString( eText_InteractionFailed_TargetInMounting ) );
		return FALSE;
	}
	if( pTargetPlayer->IsInWater() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OneAnother, theXmlString.GetString( eText_InteractionFailed_TargetInWater ) );
		return FALSE;
	}
	//if( pTargetPlayer->HasFightFlag(eFighting) )
	//{
	//    GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_InteractionFailed_TargetInFighting ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
	//    return FALSE;
	//}
	if( pTargetPlayer->IsLootOrIntonateAnim() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OneAnother, theXmlString.GetString( eText_InteractionFailed_TargetInLooting ) );
		return FALSE;
	}
	if( pTargetPlayer->IsDead() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OneAnother, theXmlString.GetString( eText_InteractionFailed_TargetDead ) );
		return FALSE;
	}

	// �жϾ���
	float fOffsetX, fOffsetY, fOffsetZ, fDist;
	fOffsetX = GetPos().x - pTargetPlayer->GetPos().x;
	fOffsetY = GetPos().y - pTargetPlayer->GetPos().y;
	fOffsetZ = GetPos().z - pTargetPlayer->GetPos().z;
	fDist = sqrtf(fOffsetX*fOffsetX + fOffsetY*fOffsetY + fOffsetZ*fOffsetZ);
	if( fDist > 1.5 )
	{
		bTooFar = TRUE;
		return FALSE;
	}
	// �����ж�
	if( fabs(fOffsetZ) > (g_fPlayerCollisionHeight)*GetMe3dConfig()->m_fMdlSpaceScale )
	{
		// ����һ���߶�
		bZTooFar = TRUE;
		return FALSE;
	}

	return TRUE;
}
void CPlayer::SetTitleInfoById( int nId ,const char* pszName /*= NULL*/)
{
	SetTitleId( nId );

	// 	if(0 == nId)
	// 	{
	// 		//���������title�����������Ϣ�������ڷ�����ʾ����֮���͵�����title����Ϣ��
	// 		//��ʱ�Ͳ���settitle�ˣ���Ϊ�����ڱ���������顣
	// 		if(IsShowSignature())
	// 			return;
	// 	}
	// 	if(IsShowSignature())
	// 	{
	// 		if(this == theHeroGame.GetPlayerMgr()->GetMe())
	// 		{
	// 			SetTitle(thePlayerRole.GetSignature());
	// 		}
	// 
	// 		return;
	// 	}

	TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID( nId );
	if( !pTitle )
	{
		SetTitle( "" );
		SetTitleColor( 0 );
		return;
	}

	if(pTitle->GetType() == TitleConfig::Title_Marriage)
	{
		const char* pszMarryName = NULL;
		if(IsRole())
			pszMarryName = thePlayerRole.GetMarryerName();
		else
		{
			if(pszName != 0)  //��ͬ��Ļ�иĳƺ�
				pszMarryName = pszName;
			else if(m_szTitleTargetName.empty()) //������Ұʱ��ĳƺ�
				pszMarryName = NULL;
			else
				pszMarryName = m_szTitleTargetName.c_str();
		}

		if(pszMarryName != NULL)
		{
			char szText[256] = {0};
			if(GetSex() == 0)
				MeSprintf_s(szText,sizeof(szText)/sizeof(char) - 1,pTitle->GetName(),pszMarryName,theXmlString.GetString(eText_MarryHusband));
			else
				MeSprintf_s(szText,sizeof(szText)/sizeof(char) - 1,pTitle->GetName(),pszMarryName,theXmlString.GetString(eText_MarryWife));

			SetTitle(szText);
		}
		else
		{
			SetTitle("");
		}
	}
	else if( pTitle->GetType() == TitleConfig::Title_Student)
	{
		const char* pcTeacherName = pszName;
		if( pcTeacherName )
		{
			char szText[256] = {0};
			MeSprintf_s( szText, sizeof( szText ) / sizeof( char ) - 1, pTitle->GetName(), pcTeacherName );
			SetTitle(szText);
		}
		else
		{
			SetTitle("");
		}
	}
	else
		SetTitle( pTitle->GetName() );
	// ������ɫ
	SetTitleColor( pTitle->dwColor);		
}
void CPlayer::GetPFPos(  float &fX, float &fY )
{
	CWorldTile* pCurrTile = CURRENTTILE;
	const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(GetNpcID(),pCurrTile->GetMapId());
	if (pInfo && pInfo->_bPFPossible)
	{
		fX = pInfo->_pfMapX;
		fY = pInfo->_pfMapY;
	}
	else
	{
		GetPos(&fX,&fY,NULL);
	}
}

void CPlayer::ClearChatPaoPao()
{
	SAFE_DELETE( m_pChatPaoPao );
}

void CPlayer::TryPlayNpcAction()
{
	DWORD dwElapse = HQ_TimeGetTime() - m_dwNpcActionTime;
	if(!m_act.anim.strType.empty() && dwElapse >= m_act.anim.nDelayTime)
	{
		if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
		{
			m_pAnim->PlayLowerAnim(	m_act.anim.strType.c_str(),
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				"idle",
				MexAnimCtrl::eNormalPlay );
		}
		else
		{
			m_pAnim->PlayAnimByActionName( m_act.anim.strType.c_str(),
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				"idle",
				MexAnimCtrl::eNormalPlay );
		}
		m_act.anim.strType.clear();
	}

	if(m_act.talk.nStringId != 0 && dwElapse >= m_act.talk.nDelayTime)
	{
		SetChatInfo(std::string(theXmlString.GetString(m_act.talk.nStringId)));
		m_act.talk.nStringId = 0;
	}
	if( m_act.autoFace.bIsAutoFace == true && dwElapse >= m_act.autoFace.nDelayTime )
	{
		TryTalkWithPlayer();
		m_act.autoFace.bIsAutoFace = false;
	}
}

bool CPlayer::IsHaveAppeaseRequire(Require *pReq)
{
	if(!pReq)
		return false;

	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if(!pMe)
		return false;


	switch(pReq->eType)
	{
	case Req_Dislen: //����
		{
			D3DXVECTOR3 vPos = pMe->GetPos();
			if(!pReq->IsInZoneArea(m_x,m_y,vPos.x,vPos.y))
				return false;
		}
		break;
	case Req_Sex:    //�Ա�
		{
			if(!pReq->IsSameSex(pMe->GetSex()))
				return false;
		}
		break;
	case Req_Task:
		{
			CPlayerRole::QuestInfo* info = thePlayerRole.FindQuestInfoById( pReq->FinishedTaskID() );
			if ( info == NULL || info->bDone == false || info->chState != -1 ) //ֻ���Ѿ�������������Ч
			{
				return false;
			}
		}
		break;
	case Req_Level:  //�ȼ�
		{
			if(!pReq->IsInLevelArea(pMe->GetLevel()))
				return false;
		}
		break;
	case Req_None:
	default:
		{
			assert(0&&"NpcAction����");
		}
	}
	return true;
}

void CPlayer::ProcessNpcAction()
{
	CWorldTile *pTile = CURRENTTILE;
	if(!pTile)
		return;

	if(!IsNpc())
		return;

	if(m_dwNpcActionTime != 0)
	{
		TryPlayNpcAction();
		return;
	}

	//���û����Ϊ�б�Ͳ���
	if(!m_IsSearch)
		return;

	//1.5�����һ��
	if(HQ_TimeGetTime() - m_dwSearchCD < 1000)
		return;

	m_dwSearchCD = HQ_TimeGetTime();

	NpcInfo::Npc *pNpc = theNpcInfo.GetNpc(m_nNpcId,pTile->GetMapId());
	if(!pNpc)
		return;

	//ɸѡ����������������Action
	std::vector<Action*> set;
	set.clear();
	int nSize = pNpc->npcAct.GetSize();
	if(nSize == 0)
	{
		m_IsSearch = false;
		return;
	}

	for (int i = 0;i < nSize;++i)
	{
		Action* pAction =  pNpc->npcAct.GetOneActionByIndex(i);
		if(!pAction)
			continue;

		bool bMust = true,bProbility = false;
		//�жϱ�Ҫ����,������������������
		int nCount = pAction->vecMustTerm.size();
		for (int n = 0;n < nCount;++n)
		{
			if(!IsHaveAppeaseRequire(&pAction->vecMustTerm[n]))
			{
				bMust = false;
				break;
			}
		}

		if(!bMust)
			continue;

		//�жϸ�������,ֻҪ����һ�����������Ϳ�����
		nCount = pAction->vecProbilityTerm.size();
		for (int n = 0;n < nCount;++n)
		{
			if(IsHaveAppeaseRequire(&pAction->vecProbilityTerm[n]))
			{
				bProbility = true;
				break;
			}
		}

		if(nCount ==0 ||(nCount != 0&&bProbility))
			set.push_back(pAction);
	}

	nSize = set.size();
	if(nSize <= 0)
		return;

	int nIndex = rand()%nSize;
	if(nIndex < 0 || nIndex >= nSize)
		return;

	m_dwNpcActionTime = HQ_TimeGetTime();

	Action *pAction = set[nIndex];
	if(!pAction->anim.strType.empty())
	{
		m_act.anim.strType = pAction->anim.strType;
		m_act.anim.nProbability = pAction->anim.nProbability;
		m_act.anim.nDelayTime = pAction->anim.nDelayTime;
	}

	if(pAction->talk.nStringId != 0)
	{
		m_act.talk.nStringId = pAction->talk.nStringId;
		m_act.talk.nProbability = pAction->talk.nProbability;
		m_act.talk.nDelayTime = pAction->talk.nDelayTime;
	}

	if ( pAction->autoFace.bIsAutoFace == true )
	{
		m_act.autoFace.bIsAutoFace = pAction->autoFace.bIsAutoFace;
	}
}

void CPlayer::InitNpcAction(DWORD dwTime)
{
	CWorldTile *pTile = CURRENTTILE;
	if(!pTile)
		return;

	if( strlen(GetName()) == 0 )
	{
		m_bNeedInitNpcAction = TRUE;
		return;
	}

	m_bNeedInitNpcAction = FALSE;
	NpcInfo::Npc* pNpc = theNpcInfo.GetNpc(m_nNpcId,pTile->GetMapId());
	if( !pNpc )
		return;

	if( pNpc->vctActionData.size() )
	{
		m_shNextActionId = pNpc->vctActionData[0].shId;
		m_dwNextActionTime = dwTime + pNpc->vctActionData[0].shElapseTime * 1000;
	}
}

void CPlayer::ExitNpcAction()
{
	m_dwNextActionTime = 0;
	m_shNextActionId = 0;
}

void CPlayer::UpdateNpcAction( DWORD dwTime )
{
	CWorldTile* pTile = CURRENTTILE;
	if(!pTile)
		return;

	if( m_bNeedInitNpcAction )
	{
		InitNpcAction(dwTime);
		return;
	}

	if( m_dwNextActionTime == 0 )
		return;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpc(m_nNpcId,pTile->GetMapId());
	if( !pNpc )
		return;

	if( pNpc->vctActionData.size() <= m_shNextActionId )
	{
		// Id���ԣ���ͷ����
		InitNpcAction(dwTime);
		return;
	}

	if( dwTime <= m_dwNextActionTime )
		return;

	NpcInfo::NpcActionData* pActionData = &pNpc->vctActionData[m_shNextActionId];
	// ������
	if( pActionData->vctActions.size() && m_pAnim )
	{
		int probability = rand();
		probability %= 100;
		int nActionProbability = 0; // ��ǰaction�ĸ���
		for(int i=0; i<pActionData->vctActions.size(); i++)
		{
			nActionProbability += pActionData->vctActions[i].shProbability;
			if( probability < nActionProbability )
			{
				// ������
				if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
				{
					m_pAnim->PlayLowerAnim(	pActionData->vctActions[i].strAnimName.c_str(),
						MexAnimCtrl::eNormalPlay,
						0,
						1,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
				else
				{
					m_pAnim->PlayAnimByActionName( pActionData->vctActions[i].strAnimName.c_str(),
						MexAnimCtrl::eNormalPlay,
						0,
						1,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
				break;
			}
		}
	}
	// ˵��
	if( pActionData->vctTalks.size() )
	{
		int probability = rand();
		probability %= 100;
		int nTalkProbability = 0;   // ��ǰtalk�ĸ���
		for(int i=0; i<pActionData->vctTalks.size(); i++)
		{
			nTalkProbability += pActionData->vctTalks[i].shProbability;
			if( probability < nTalkProbability )
			{
				// ��������
				SetChatInfo(std::string(theXmlString.GetString(pActionData->vctTalks[i].shStringId)));
				break;
			}
		}
	}
	// �¸�����
	m_shNextActionId = pActionData->shNextId;
	if( m_shNextActionId >= pNpc->vctActionData.size() )
		m_shNextActionId = 0;

	m_dwNextActionTime = dwTime + pNpc->vctActionData[m_shNextActionId].shElapseTime * 1000;

}

DWORD CPlayer::GetPkNameColor()
{
	return Color_Config.GetPkNameColor( GetPKType() );
}

void CPlayer::PlayAdvanceSkillHurtAnim(int nPlayerID, ItemDefine::SItemSkill* pSkill)
{
	if( nPlayerID <= -1 )
		return;

	CPlayer* pDestPlayer = theHeroGame.GetPlayerMgr()->FindByID(nPlayerID);
	if( !pDestPlayer )
		return;

	// �Ƿ���Ҫ��Ⱦ��Ч
	if( CanRenderPlayerEffect(GetID()) )
	{
		// Ԥ���ܻ���Ч
		const char *pEffectPath = NULL;
		if( m_ucSex == Sex_Female )
			pEffectPath = pSkill->GetTargetEffectName2();
		else
			pEffectPath = pSkill->GetTargetEffectName();

		//����Ŀ����Ч
		if( stricmp( pEffectPath, "NULL" ) != 0 )
		{
			float fScale = 0.5f;
			if( pDestPlayer->GetAnim() && pDestPlayer->GetAnim()->GetMexCfg() )
			{
				guard(test2.0.1.1);
				fScale = (float)(pDestPlayer->GetAnim()->GetMexCfg()->m_BodyRadius.m_npRadius.GetNumber());
				fScale = fScale*Config::m_fMdlSpaceScale*m_fBodySize;
				unguard;
			}
			PlayEffect( (char*)pEffectPath, pDestPlayer, PlayerInfoMgr::Instance()->GetScaleForPlayer(pDestPlayer) );
		}
	}

	if( pDestPlayer->m_cFightStatus.IsCanMove() )
	{
		// ��Ҫ���ܻ�����
		pDestPlayer->PlayCreatureSound( CCreatureSound::CreatureSound_BeHit );
		pDestPlayer->SwitchHurtAnim();
	}  
}

BOOL CPlayer::CanSwitchRunAnim()
{
	if( m_bRole )
	{
		if( g_bTheRoleJumping || m_bDead )
		{
			return FALSE;
		}
		else if( m_bNeedDropBuf && m_dwDropEndTime > 0 )
		{
			return FALSE;
		}
	}
	else
	{
		if( m_bDead )
		{
			return FALSE;
		}
	}

	if(IsCanOverIntonation())
		return FALSE;

	if( !m_cFightStatus.IsCanMove() )
		return FALSE;

	return TRUE;
}

void CPlayer::StopJump()
{
	g_bTheRoleJumping = FALSE;
	g_dwTheRoleJumpingEndTime = 0;
	g_bTheRoleSlipJumping = FALSE;
	g_bTheRoleFallJumping = FALSE;
	m_bJumping = FALSE;
	m_bNeedDropBuf = FALSE;
	if( IsRole() )
		thePlayerRole.EndJump();
}
const char* const c_pcFiveElementString[] = 
{
	"null",
	"Jin",
	"Mu",
	"Shui",
	"Huo",
	"Tu"
};
void CPlayer::UpdateMainElement()
{
	// hide all
	for( int i = ItemElements_Metal ; i < ItemElements_End; ++ i )
	{
		CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( m_FiveElementEffectIds[i].m_nEffectId );
		if( pModelEffect )
		{
			int nNum = pModelEffect->m_nNumInstance;
			for( int nInst = 0; nInst < nNum; nInst++ )
			{
				CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

				if( !pInstance )
					continue;

				pInstance->bVisible = false;
			}						
		}
	}	

	CheckSuitForFiveElement();
	if( m_nMainElement == -1 )
	{
		m_bNeedUpdateFiveElement = false;			
	}
	else //����������Ч
	{
		m_bNeedUpdateFiveElement = true;
	}

}
void CPlayer::UpdateFiveElementEffect()
{
	if( !m_bNeedUpdateFiveElement )
		return;

	if( m_cFightStatus.IsHide() || !theHeroGame.GetPlayerMgr()->IsPlayerCanRender( this ) )
	{
		// hide all
		for( int i = ItemElements_Metal ; i < ItemElements_End; ++ i )
		{
			CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( m_FiveElementEffectIds[i].m_nEffectId );
			if( pModelEffect )
			{
				int nNum = pModelEffect->m_nNumInstance;
				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

					if( !pInstance )
						continue;

					pInstance->bVisible = false;
				}						
			}
		}	
		return;
	}

	_UpdateFiveElementEffect();
}
void CPlayer::_UpdateFiveElementEffect(bool setScale, float scale)
{
	if( !m_bNeedUpdateFiveElement )
		return;

	if( m_nMainElement < ItemElements_Metal || m_nMainElement >= ItemElements_End )
		return;

	InitFiveElementEffect();

	CWSModelEffect::Instance* pInstance = 0;
	CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( m_FiveElementEffectIds[m_nMainElement].m_nEffectId );
	if( pModelEffect )
	{
		int nNum = pModelEffect->m_nNumInstance;
		for( int nInst = 0; nInst < nNum; nInst++ )
		{
			CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );

			if( !pInstance )
				continue;

			pInstance->bVisible = false;
		}						

		pInstance = pModelEffect->GetInstance( m_nMaxElementCount - 2 );//�����������2��ʼ�����Լ�ȥ2

		if( !pInstance )
			return;

		pInstance->bVisible = true;
		pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;

		if (setScale)
			pInstance->fScale = scale;
	}

	CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( m_FiveElementEffectIds[m_nMainElement].m_nEffectContainerId );
	if( pEffectContainer && m_pCharEffectContainer && pInstance )
	{
		IEffectHelper* pEffectHelper = NULL;
		float afBody[3] = {0.f};
		m_pCharEffectContainer->GetEffectHelper( pInstance->nBindWhere )->GetPos( afBody );

		pEffectHelper = pEffectContainer->GetEffectHelper( pInstance->nBindWhere );
		pEffectHelper->SetPos( afBody[0], afBody[1], afBody[2] );			
	}
}
void CPlayer::InitFiveElementEffect()
{
	for( int i = ItemElements_Metal ; i < ItemElements_End; ++ i )
	{
		if( m_FiveElementEffectIds[i].m_nEffectId != -1 )
			continue;

		CWSModelEffect* pEffect = MeNew CWSModelEffect;
		char acEffectFilename[256] = {0};
		MeSprintf_s( acEffectFilename, 256, "data\\effect\\common\\%sElement.ini", c_pcFiveElementString[i] );
		if( pEffect->LoadSetting( GetFullFileName( acEffectFilename ) ) )
		{
			m_FiveElementEffectIds[i].m_nEffectId = GetEffectMgr()->RegisterEffect( pEffect );
			if( m_FiveElementEffectIds[i].m_nEffectId == -1 )
			{
				pEffect->Release();
			}
			else
			{
				m_FiveElementEffectIds[i].m_nEffectContainerId = GetEffectMgr()->RegisterCharEffectContainer();
				pEffect->m_dwBornTime = HQ_TimeGetTime();
				float fRadius = pEffect->m_fRadius;
				int nNum = pEffect->m_nNumInstance;

				CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( m_FiveElementEffectIds[i].m_nEffectContainerId );

				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
					if( !pInstance )
					{
						continue;
					}

					pInstance->dwBornTime = HQ_TimeGetTime() + /*pEffect->m_dwDelay*nInst*/pInstance->fDelay;

					if( pEffectContainer )
					{
						pEffect->SetEffectQuoter( pEffectContainer );
					}

					pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
					pInstance->vPos = pInstance->vBornPos;
					pInstance->bVisible = FALSE;

					// ����Ч��
					if( pEffectContainer )
					{
						pInstance->pMaster = pEffectContainer->GetEffectHelper( pInstance->nBindWhere );
					}
				}

				if( pEffectContainer )
				{
					pEffectContainer->ApplyEffect( 0, pEffect->GetID() );
				}
			}
		}
		else
		{
			pEffect->Release();
		}
		pEffect = NULL;
	}	
}
//void CPlayer::CheckSuitForFiveElement()
//{	
//	
//	std::vector< ItemDefine::SItemArmour* > vSuitEquip;
//	std::vector< SCharItem* > vSuitCharItem;	
//	
//	// ��ȷ����װid��ȡarmour�����λ
//	short stSuitId = -1;
//	SCharItem* pPlayerEquip = &m_equips[EPT_Armour].item;
//	if( pPlayerEquip )
//	{
//		ItemDefine::SItemCommon* pPlayerItem = GettheItemDetail().GetItemByID( pPlayerEquip->itembaseinfo.ustItemID );
//		if( pPlayerItem && 
//			pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
//		{
//			ItemDefine::SItemArmour* pPlayerArmour = (ItemDefine::SItemArmour*)pPlayerItem;
//			if( pPlayerArmour->sSuitID == -1 || pPlayerArmour->sSuitID == 0 )
//			{
//				m_nMainElement = -1;
//				return;
//			}
//			stSuitId = pPlayerArmour->sSuitID;
//		}
//	}
//	else
//	{
//		m_nMainElement = -1;
//		return;
//	}
//	
//	for( int i = 0 ; i < EPT_MaxEquitPart ; ++ i )
//	{
//		SCharItem* pPlayerEquip = &m_equips[i].item;
//		if( pPlayerEquip )
//		{
//			ItemDefine::SItemCommon* pPlayerItem = GettheItemDetail().GetItemByID( pPlayerEquip->itembaseinfo.ustItemID );
//			if( pPlayerItem && 
//				pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
//			{
//				ItemDefine::SItemArmour* pPlayerArmour = (ItemDefine::SItemArmour*)pPlayerItem;							
//				if( pPlayerArmour->sSuitID == stSuitId )//����װ����
//				{
//					vSuitEquip.push_back( pPlayerArmour );
//					vSuitCharItem.push_back( pPlayerEquip );
//				}
//			}
//		}	
//	}
//		
//	// �Ƿ��ж�����,�����Ƿ�����
//	bool bEnableFiveElement = false;
//	const int ncEnableFiveElementCount = 6;//6����װ�ŻῪ��
//	// ����
//	if( ncEnableFiveElementCount != vSuitEquip.size() )
//	{
//		m_nMainElement = -1;
//		return;
//	}
//
//	// �����ж�
//	
//	struct FiveElementHelper
//	{
//		FiveElementHelper(){
//			ucElement = 0;
//			nMaxCount = 0;
//		}
//		unsigned char ucElement;
//		int nMaxCount;
//	};
//	bool bDisable = false;
//	std::vector< FiveElementHelper > vFeh;
//	for( int i = 0 ; i < vSuitCharItem.size() ; ++ i )
//	{
//		SCharItem* pArmourItem = vSuitCharItem[i];		
//		unsigned char ucElement = ( pArmourItem->itembaseinfo.value1 & 0xff );
//		if( ucElement == 0 )
//		{
//			bDisable = true;
//			break;
//		}
//
//		bool bFound = false;
//		for( int j = 0 ; j < vFeh.size(); ++ j )
//		{
//			if( ucElement == vFeh[j].ucElement )
//			{
//				++vFeh[j].nMaxCount;
//				bFound = true;
//				break;
//			}						
//		}
//		if( bFound )
//			continue;
//		FiveElementHelper h;
//		h.ucElement = ( pArmourItem->itembaseinfo.value1 & 0xff );
//		++h.nMaxCount;
//		vFeh.push_back( h );
//	}
//	m_nMaxElementCount = 0;
//	m_nMainElement = 0;
//	if( !bDisable )
//	{		
//		for( int i = 0 ; i < vFeh.size() ; ++ i )
//		{
//			if( m_nMaxElementCount < vFeh[i].nMaxCount )//bigger
//			{
//				m_nMainElement = vFeh[i].ucElement;
//				m_nMaxElementCount = vFeh[i].nMaxCount;
//				bDisable = false;
//				continue;
//			}
//			if( m_nMaxElementCount == vFeh[i].nMaxCount )
//				bDisable = true;
//		}
//	}
//	if( bDisable )
//		m_nMainElement = -1;
//
//}

//add by yanli  2010-9-27
void CPlayer::CheckSuitForFiveElement()
{	

	std::vector< ItemDefine::SItemArmour* > vSuitEquip;
	std::vector< SCharItem* > vSuitCharItem;	

	// ��ȷ����װid��ȡarmour�����λ
	short stSuitId = -1;
	SCharItem* pPlayerEquip = &m_equips[CEquipPartMap::Instance()->GetLogicPart(EEquipPartType_Armour)].item;
	if( pPlayerEquip )
	{
		ItemDefine::SItemCommon* pPlayerItem = GettheItemDetail().GetItemByID( pPlayerEquip->itembaseinfo.ustItemID );
		if( pPlayerItem && 
			pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
		{
			ItemDefine::SItemArmour* pPlayerArmour = (ItemDefine::SItemArmour*)pPlayerItem;
			if( pPlayerArmour->sSuitID == -1 || pPlayerArmour->sSuitID == 0 )
			{
				m_nMainElement = -1;
				return;
			}
			stSuitId = pPlayerArmour->sSuitID;
		}
	}
	else
	{
		m_nMainElement = -1;
		return;
	}

	for( int i = 0 ; i < EEquipPartType_MaxEquitPart ; ++ i )
	{
		SCharItem* pPlayerEquip = &m_equips[CEquipPartMap::Instance()->GetLogicPart(i)].item;
		if( pPlayerEquip )
		{
			ItemDefine::SItemCommon* pPlayerItem = GettheItemDetail().GetItemByID( pPlayerEquip->itembaseinfo.ustItemID );
			if( pPlayerItem && 
				pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
			{
				ItemDefine::SItemArmour* pPlayerArmour = (ItemDefine::SItemArmour*)pPlayerItem;							
				if( pPlayerArmour->sSuitID == stSuitId )//����װ����
				{
					vSuitEquip.push_back( pPlayerArmour );
					vSuitCharItem.push_back( pPlayerEquip );
				}
			}
		}	
	}

	// �Ƿ��ж�����,�����Ƿ�����
	bool bEnableFiveElement = false;
	const int ncEnableFiveElementCount = 6;//6����װ�ŻῪ��
	// ����
	if( ncEnableFiveElementCount != vSuitEquip.size() )
	{
		m_nMainElement = -1;
		return;
	}

	// �����ж�

	struct FiveElementHelper
	{
		FiveElementHelper(){
			ucElement = 0;
			nMaxCount = 0;
		}
		unsigned char ucElement;
		int nMaxCount;
	};
	bool bDisable = false;
	std::vector< FiveElementHelper > vFeh;
	for( int i = 0 ; i < vSuitCharItem.size() ; ++ i )
	{
		SCharItem* pArmourItem = vSuitCharItem[i];		
		unsigned char ucElement = ( pArmourItem->itembaseinfo.value1 & 0xff );
		if( ucElement == 0 )
		{
			bDisable = true;
			break;
		}

		bool bFound = false;
		for( int j = 0 ; j < vFeh.size(); ++ j )
		{
			if( ucElement == vFeh[j].ucElement )
			{
				++vFeh[j].nMaxCount;
				bFound = true;
				break;
			}						
		}
		if( bFound )
			continue;
		FiveElementHelper h;
		h.ucElement = ( pArmourItem->itembaseinfo.value1 & 0xff );
		++h.nMaxCount;
		vFeh.push_back( h );
	}
	m_nMaxElementCount = 0;
	m_nMainElement = 0;
	if( !bDisable )
	{		
		for( int i = 0 ; i < vFeh.size() ; ++ i )
		{
			if( m_nMaxElementCount < vFeh[i].nMaxCount )//bigger
			{
				m_nMainElement = vFeh[i].ucElement;
				m_nMaxElementCount = vFeh[i].nMaxCount;
				bDisable = false;
				continue;
			}
			if( m_nMaxElementCount == vFeh[i].nMaxCount )
				bDisable = true;
		}
	}
	if( bDisable )
		m_nMainElement = -1;
}

void CPlayer::_RenderFiveElement()
{
	if( !m_bNeedUpdateFiveElement )
		return;

	if( m_nMainElement < ItemElements_Metal || m_nMainElement >= ItemElements_End )
		return;

	IEffect* pEffect = GetEffectMgr()->GetEffect( m_FiveElementEffectIds[m_nMainElement].m_nEffectId );
	if( pEffect )
	{
		pEffect->Render();		
	}
}

void CPlayer::_RenderFullStarEffect()
{
	/*if( !m_bUpdateFullStarEffect )
	return;

	IEffect* pEffect = GetEffectMgr()->GetEffect( m_nFullStarEffectID );
	if( pEffect )
	{
	pEffect->Render();		
	}
	pEffect = GetEffectMgr()->GetEffect( m_nFullStarEffectID2 );
	if( pEffect )
	{
	pEffect->Render();		
	}*/

	if (GetEffectID() == -1) return;
	if (strcmp(m_EffectName,"NULL") == 0) return;

	IEffect* pEffect = GetEffectMgr()->GetEffect( GetEffectID() );
	if( pEffect )
	{
		pEffect->Render();		
	}

}


void CPlayer::ShowFightInfo(CPlayer* pSrcPlayer,CPlayer* pDestPlayer,SAttackInfoRecord* pRecord,ItemDefine::SItemSkill *pSkill)
{
	if(!pSrcPlayer || !pDestPlayer || !pRecord || !pSkill)
		return;

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if(!pMe)
		return;

	if(pSrcPlayer->GetID() != pMe->GetID() && pDestPlayer->GetID() != pMe->GetID() &&
		pSrcPlayer->GetMasterID() != pMe->GetID() && pDestPlayer->GetMasterID() != pMe->GetID())
		return;

	char szFightInfo[256];
	char szTemp[128];
	char szAttackType[128];
	std::string  strFightInfo = "";
	std::string  strFightInfoOther = "";
	strFightInfoOther.clear();
	DWORD dwColor = 0xffffffff;

	memset(szTemp,0,sizeof(szTemp));
	memset(szAttackType,0,sizeof(szAttackType));
	memset(szFightInfo,0,sizeof(szFightInfo));

	if(IsNormalAttack( pSkill->ustItemID))
		MeSprintf_s(szAttackType,sizeof(szAttackType),"%s",theXmlString.GetString(eText_NormalAttack));  //��ͨ����
	else
		if(pSrcPlayer->IsMonster())
			MeSprintf_s(szAttackType,sizeof(szAttackType),"%s",pSkill->GetSkillName());  // ħ������
		else
			MeSprintf_s(szAttackType,sizeof(szAttackType),theXmlString.GetString(eText_MagicAttack),pSkill->ustLevel,pSkill->GetSkillName());  // ħ������

	switch(pSkill->ustDamageBalanceType)
	{
	case ItemDefine::balancetype_damagemagicdefend:
	case ItemDefine::balancetype_damagephysicaldefend:
		{
			//������״̬��������
			//��Ӹ�����Ϣ
			if(/*_HAS_FLAG(pRecord->dwState,eFIGHT_RELIVE)||*/_HAS_FLAG(pRecord->dwState,eFIGHT_MISS))
			{
				//                 if(_HAS_FLAG(pRecord->dwState,eFIGHT_RELIVE))  //����
				//                 {
				//                     char szWord[128];
				//                     if(pDestPlayer == pMe)
				//                     {
				//                         MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Relive),pSrcPlayer->GetName(),theXmlString.GetString(eText_Your));
				//                         strFightInfo = szWord;
				//                     }
				//                     else
				//                     {
				//                         MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Relive),theXmlString.GetString(eText_Your),pSrcPlayer->GetName());
				//                         strFightInfo = szWord;
				//                     }
				//                 }
				if(_HAS_FLAG(pRecord->dwState,eFIGHT_MISS))//����δ����
				{
					char szWord[128];
					memset(szWord,0,sizeof(szWord));
					if(pDestPlayer->GetID() == pMe->GetID())
					{
						MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Miss),theXmlString.GetString(eText_Your),pSrcPlayer->GetName());//%s������%s�Ĺ���
					}else if (pSrcPlayer->GetID() == pMe->GetID())
					{
						MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_NoHit),theXmlString.GetString(eText_Your),pDestPlayer->GetName());//%s�Ĺ���δ����%s"
					}
					else if(pSrcPlayer->GetMasterID() == pMe->GetID())
					{
						MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_NoHit),pSrcPlayer->GetName(),pDestPlayer->GetName());//%s�Ĺ���δ����%s"
					}
					else if(pDestPlayer->GetMasterID() == pMe->GetID())
					{
						MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Miss),pDestPlayer->GetName(),pSrcPlayer->GetName());//%s������%s�Ĺ���
					}
					strFightInfo = szWord;
				}
			}
			else
			{
				if(pSkill->ustDamageBalanceType == ItemDefine::balancetype_damagemagicdefend )
				{ MeSprintf_s(szTemp,sizeof(szTemp),"%s",theXmlString.GetString(eText_NearDistance));  }//���� 
				else
					MeSprintf_s(szTemp,sizeof(szTemp),"%s",theXmlString.GetString(eText_FarDistance));  //Զ��

				//�������˺�
				int nTotalHurt = pRecord->iTagNum + (int)pRecord->stTagBackAttackNum;
				if( nTotalHurt > 0 )
				{
					//lyhtexiaoguai++
					if(pSrcPlayer == pMe || (pSrcPlayer->IsEffect() && pSrcPlayer->MasterIsMe()))
					{
						dwColor = Color_Config.getColor(CC_CHAT_TEAM);
						MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_FightInfoHurt),theXmlString.GetString(eText_Your),pDestPlayer->GetName(),szAttackType,nTotalHurt,szTemp);
					}
					else if(pDestPlayer == pMe)
					{
						dwColor = Color_Config.getColor(CC_PlayerEnemy);
						MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_FightInfoHurt),pSrcPlayer->GetName(),theXmlString.GetString(eText_Your),szAttackType,nTotalHurt,szTemp);
					}
					else if(pSrcPlayer->GetMasterID() == pMe->GetID()) //"%s��%sʹ��%s,���%d%s�˺�"
					{
						dwColor = Color_Config.getColor(CC_CHAT_TEAM);
						MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_FightInfoHurt),pSrcPlayer->GetName(),pDestPlayer->GetName(),szAttackType,nTotalHurt,szTemp);
					}
					else if(pDestPlayer->GetMasterID() == pMe->GetID()) //"%s��%sʹ��%s,���%d%s�˺�"
					{
						dwColor = Color_Config.getColor(CC_PlayerEnemy);
						MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_FightInfoHurt),pSrcPlayer->GetName(),pDestPlayer->GetName(),szAttackType,nTotalHurt,szTemp);
					}

					strFightInfo = szFightInfo;
				}

				//��Ӹ�����Ϣ
				if(_HAS_FLAG(pRecord->dwState,eFIGHT_CRITICALHIT)
					||_HAS_FLAG(pRecord->dwState,eFIGHT_BACKSTRIKE))
				{
					char szAdd[128];
					char szBack[128];
					memset(szAdd,0,sizeof(szAdd));
					memset(szBack,0,sizeof(szBack));

					if(_HAS_FLAG(pRecord->dwState,eFIGHT_CRITICALHIT))// ����
						MeSprintf_s(szAdd,sizeof(szAdd),"%s",theXmlString.GetString(eText_Critical));

					if((pRecord->stTagBackAttackNum > 0)&&_HAS_FLAG(pRecord->dwState,eFIGHT_BACKSTRIKE))  // ����
						MeSprintf_s(szBack,sizeof(szBack),theXmlString.GetString(eText_BackHit),pRecord->stTagBackAttackNum);

					if(strlen(szAdd) > 0 || strlen(szBack) > 0)
					{
						MeSprintf_s(szFightInfo,sizeof(szFightInfo),"(%s %s)",szAdd,szBack);
						strFightInfo += szFightInfo;
					}
				} 

				//�����ֿ�
				if(_HAS_FLAG(pRecord->dwState,eFIGHT_DAOXINGRESIST))
				{
					char szWord[128] = {0};
					MeSprintf_s(szWord,sizeof(szWord),"%s", theXmlString.GetString(eText_DaoHangResist));//�����ֿ�
					strFightInfo += szWord;
				}

				//����ѹ��
				if(_HAS_FLAG(pRecord->dwState,eFIGHT_DAOXINGSTIFLE))
				{
					char szWord[128] = {0};
					MeSprintf_s(szWord,sizeof(szWord),"%s",theXmlString.GetString(eText_DaoHangStifle));//"����ѹ��"
					strFightInfo += szWord;
				}

				//��ͬʱ����ʱ��ֻ��ʾһ��״̬
				if(_HAS_FLAG(pRecord->dwState,eFIGHT_SUCKHP)&&_HAS_FLAG(pRecord->dwState,eFIGHT_DAMREFLECT))
				{
					if(pRecord->iSrcHpNum > 0)
					{
						if(pDestPlayer == pMe)
						{
							char szWord[256] = {0};
							MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_AddHpBySkill),pSrcPlayer->GetName(),-pRecord->iSrcHpNum);
							strFightInfoOther = szWord;
						}
						else if(pSrcPlayer == pMe)
						{
							char szWord[256] = {0};
							MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_AddHpBySkill),theXmlString.GetString(eText_Your),-pRecord->iSrcHpNum);
							strFightInfoOther = szWord;
						}
					}
					else if(pRecord->iSrcHpNum < 0)
					{
						if(pDestPlayer == pMe)
						{  
							char szWord[256] = {0};
							MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_ReduceHpBySkill),pSrcPlayer->GetName(),pRecord->iSrcHpNum);
							strFightInfoOther = szWord;
						}
						else if(pSrcPlayer == pMe)
						{
							char szWord[256] = {0};
							MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_ReduceHpBySkill),theXmlString.GetString(eText_Your),pRecord->iSrcHpNum);
							strFightInfoOther = szWord;
						}
					}
				}
				else  if(_HAS_FLAG(pRecord->dwState,eFIGHT_SUCKHP))// ��Ѫ
				{
					if(pDestPlayer == pMe)
					{
						char szWord[256] = {0};
						MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_AddHpBySkill),pSrcPlayer->GetName(),-pRecord->iSrcHpNum);
						strFightInfoOther = szWord;
					}
					else if(pSrcPlayer == pMe)
					{
						char szWord[256] = {0};
						MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_AddHpBySkill),theXmlString.GetString(eText_Your),-pRecord->iSrcHpNum);
						strFightInfoOther = szWord;
					}
				}
				else if(_HAS_FLAG(pRecord->dwState,eFIGHT_DAMREFLECT))// ����
				{
					if(pDestPlayer == pMe)
					{  
						char szWord[256] = {0};
						MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_ReduceHpBySkill),pSrcPlayer->GetName(),pRecord->iSrcHpNum);
						strFightInfoOther = szWord;
					}
					else if(pSrcPlayer == pMe)
					{
						char szWord[256] = {0};
						MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_ReduceHpBySkill),theXmlString.GetString(eText_Your),pRecord->iSrcHpNum);
						strFightInfoOther = szWord;
					}
				}
			}
		}
		break;
	case ItemDefine::balancetype_none:  // û���κν���
		{
			ItemDefine::SItemStatus* pStatus = NULL;

			if(pSrcPlayer == pMe&&pDestPlayer == pMe)
			{
				pStatus = (ItemDefine::SItemStatus *)GettheItemDetail().GetStatus(pSkill->ustMeAddStatusID[0], pSkill->ustMeAddStatusLevel[0]);
				if(!pStatus)
				{
					pStatus = (ItemDefine::SItemStatus *)GettheItemDetail().GetStatus(pSkill->ustDstAddStatusID[0], pSkill->ustDstAddStatusLevel[0]);
				}
				if(pStatus)
				{
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_SkillBuf),szAttackType,pStatus->GetItemName());
				}
				else
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_MySelfSkill),szAttackType);
			}
			else if(pSrcPlayer == pMe)
			{
				pStatus = (ItemDefine::SItemStatus *)GettheItemDetail().GetStatus(pSkill->ustDstAddStatusID[0], pSkill->ustDstAddStatusLevel[0]);
				if(pStatus)
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_UseSkillBuf),theXmlString.GetString(eText_Your),pDestPlayer->GetName(),szAttackType,pDestPlayer->GetName(),pStatus->GetItemName());
				else
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_UseSkill),theXmlString.GetString(eText_Your),pDestPlayer->GetName(),szAttackType);
			}
			else if(pDestPlayer == pMe)
			{
				pStatus = (ItemDefine::SItemStatus *)GettheItemDetail().GetStatus(pSkill->ustDstAddStatusID[0], pSkill->ustDstAddStatusLevel[0]);
				if(pStatus)
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_UseSkillBuf),pSrcPlayer->GetName(),theXmlString.GetString(eText_Your),szAttackType,theXmlString.GetString(eText_Your),pStatus->GetItemName());
				else
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_UseSkill),pDestPlayer->GetName(),theXmlString.GetString(eText_Your),szAttackType);
			}
			else if(pSrcPlayer->GetMasterID() == pMe->GetID())
			{
				pStatus = (ItemDefine::SItemStatus *)GettheItemDetail().GetStatus(pSkill->ustDstAddStatusID[0], pSkill->ustDstAddStatusLevel[0]);
				if(pStatus)
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_UseSkillBuf),pSrcPlayer->GetName(),pDestPlayer->GetName(),szAttackType,pDestPlayer->GetName(),pStatus->GetItemName());
				else
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_UseSkill),pSrcPlayer->GetName(),pDestPlayer->GetName(),szAttackType);
			}
			else if(pDestPlayer->GetMasterID() == pMe->GetID())
			{
				pStatus = (ItemDefine::SItemStatus *)GettheItemDetail().GetStatus(pSkill->ustDstAddStatusID[0], pSkill->ustDstAddStatusLevel[0]);
				if(pStatus)
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_UseSkillBuf),pSrcPlayer->GetName(),pDestPlayer->GetName(),szAttackType,pDestPlayer->GetName()/*theXmlString.GetString(eText_Your)*/,pStatus->GetItemName());
				else
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_UseSkill),pSrcPlayer->GetName(),pDestPlayer->GetName(),szAttackType);
			}

			strFightInfo = szFightInfo;
		}
		break;
	case ItemDefine::balancetype_restorehpmp: // ��HP����
		{
			::OutputDebugString("��HP����");
			if(pSrcPlayer == pMe&&pDestPlayer == pMe)
				if(pRecord->iTagNum != 0)
				{
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_RestoreHpBySelf),szAttackType,-pRecord->iTagNum);
				}
				if(pRecord->iTagMpNum != 0)
				{
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_RestoreMpBySelf),szAttackType,-pRecord->iTagMpNum);
				}
				else if(pSrcPlayer == pMe)
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_RestoreHp),theXmlString.GetString(eText_Your),pDestPlayer->GetName(),szAttackType,pDestPlayer->GetName(),-pRecord->iTagNum);
				else if(pDestPlayer == pMe)
					MeSprintf_s(szFightInfo,sizeof(szFightInfo),theXmlString.GetString(eText_RestoreHp),pSrcPlayer->GetName(),theXmlString.GetString(eText_Your),szAttackType,theXmlString.GetString(eText_Your),-pRecord->iTagNum);

				strFightInfo = szFightInfo;
		}
		break;
	case ItemDefine::balancetype_relive: // �������
		{
			::OutputDebugString("�������");
		}
		break;
		//��ʱ������
		//     case ItemDefine::balancetype_addextrahp: // �����˺�˲����Ѫ
		//         break;
		//     case  ItemDefine::balancetype_damagemp: // �˺�MP
		//         break;
		//     case ItemDefine::balancetype_suckfetch: // �������
		//         break;
	}

	//             if(_HAS_FLAG(pRecord->dwState,eFIGHT_BEKILLED))  //Ŀ�걻ɱ
	//             {
	// 
	//             }

	//             if(_HAS_FLAG(pRecord->dwState,eFIGHT_DEADLYHIT))  //����һ��
	//                 fightInfo += "����һ��";

	//             if(_HAS_FLAG(pRecord->dwState,eFIGHT_WARD))// �м�
	//                 fightInfo += "�м�";
	// 
	//             if(_HAS_FLAG(pRecord->dwState,eFIGHT_RESIST))// �ֿ�
	//                 fightInfo += "�ֿ�";

	//             if(_HAS_FLAG(pRecord->dwState,eFIGHT_SELFBEKILLED))// ��������ɱ
	//             {
	// 
	//             }
	s_CUI_ChatInfoBox.AddInfo(strFightInfo,dwColor,MsgChat::CHAT_TYPE_FIGHTINFO);
	if(!strFightInfoOther.empty())
		s_CUI_ChatInfoBox.AddInfo(strFightInfoOther,dwColor,MsgChat::CHAT_TYPE_FIGHTINFO);
}


Box* CPlayer::GetWorldBBox()
{
	if( m_bMorphing )
	{
		if( m_pMorphAnim )
		{
			return m_pMorphAnim->GetWorldBBox();
		}
	}

	if( GetAnim() )
		return GetAnim()->GetWorldBBox();
#ifdef NEW_PLAYER_LOAD
	else
		return &m_fakeWorldBBox;
#endif

	return NULL;
}

#ifdef NEW_PLAYER_LOAD
void CPlayer::UpdateFakeWorldBBox( float x, float y, float z )
{
	D3DXMATRIX matRot;
	D3DXMATRIX matRotZ;
	D3DXMatrixRotationAxis( &matRotZ, &D3DXVECTOR3( 0, 0, 1 ), m_fLowerBodyDir + D3DX_PI/2 );
	D3DXMATRIX matRotY;
	D3DXMatrixRotationAxis( &matRotY, &D3DXVECTOR3( 0, 1, 0 ), 0.f );
	D3DXMATRIX matRotX;
	D3DXMatrixRotationAxis( &matRotX, &D3DXVECTOR3( 1, 0, 0 ), m_fCurRotationX );
	D3DXMatrixMultiply( &matRot, &matRotY, &matRotZ );
	D3DXMatrixMultiply( &matRot, &matRotX, &matRot );

	D3DXMATRIX matScale;
	D3DXMatrixScaling( &matScale, 1.f, 1.f, 1.f/*m_fScaleX, m_fScaleY, m_fScaleZ*/ );

	MeMatrix matTransform;
	D3DXMatrixMultiply( (D3DXMATRIX*)&matTransform, &matRot, &matScale );

	matTransform.m[3][0] = x;
	matTransform.m[3][1] = y;
	matTransform.m[3][2] = z;


	Box box;
	Vector vMin = Vector(-0.4f, -0.3f, 0.f);
	Vector vMax = Vector(0.4f, 0.3f, 2.f);
	if( m_bMounting )
		vMax.z = 3.f;
	box.BuildAABB( vMax, vMin );
	box.Transform( matTransform, m_fakeWorldBBox );
}

void CPlayer::LoadModel()
{
	//DWORD time = HQ_TimeGetTime();
	AutoCS("Default", TRUE );
	m_bModelLoaded = TRUE;
	if ( GetSitStatus() )
		SwitchSitLoopAnim( 0xFFFFFFFF );
	else
		AnimCorrectProcess();

	// ��ʱ��װ
	ShapeShift();
}

#endif

DWORD CPlayer::GetPlayerType()
{
	if (IsRole()) // �Լ�
	{
		return PT_Me;
	}
	else if (IsMonster() && !HaveMaster()) // ����
	{
		return PT_Monster;
	}
	else if (HaveMaster()) // �ٻ��޻�ū��
	{
		DWORD dwType = 0;
		if (theHeroGame.GetPlayerMgr()->GetMe() && GetMasterID() == theHeroGame.GetPlayerMgr()->GetMe()->GetID()) // �Լ�
		{
			dwType = PT_MyPet;
		}
		else if (thePlayerRole.IsTeamMember(GetMasterID())) // ����
		{
			dwType = PT_TeamPlayerPet;
		}

		CPlayer* pMaster = theHeroGame.GetPlayerMgr()->FindByID(GetMasterID());
		if (pMaster)
		{
			// ���
			if (pMaster->HasGuild() && theHeroGame.GetPlayerMgr()->GetMe() &&
				pMaster->GetGuildId() == theHeroGame.GetPlayerMgr()->GetMe()->GetGuildId())
				dwType |= PT_MyGuildPlayerPet;
			/*else if (thePlayerRole.GetGangMgr()->guildRelation(pMaster) == GR_ADVERSE)
			dwType |= PT_EnemyGuildPlayerPet;*/
			/*else if (thePlayerRole.GetGangMgr()->guildRelation(pMaster) == GR_LEAGUE)
			dwType |= PT_LeaguePlayerPet;*/

			// �������ж�
			if (pMaster->GetPKKillValue() < 0 || thePlayerRole.isChouRen(pMaster->GetName()))
				dwType |= PT_RedNamePlayerPet;

			// PK
			if (thePlayerRole.GetDuelTarget() == GetMasterID())
				dwType |= PT_PKPlayer;
		}

		// ��ͨ
		if (dwType == 0)
			dwType = PT_NormalPlayerPet;
		return dwType;
	}
	else if (IsPlayer()) // ���
	{
		DWORD dwType = 0;

		// ����
		if (thePlayerRole.IsTeamMember(GetID()))
		{
			dwType = PT_TeamPlayer;
		}

		// ���
		if (HasGuild() && theHeroGame.GetPlayerMgr()->GetMe() && 
			GetGuildId() == theHeroGame.GetPlayerMgr()->GetMe()->GetGuildId())
			dwType |= PT_MyGuildPlayer;
		/*else if (thePlayerRole.GetGangMgr()->guildRelation(this) == GR_ADVERSE)
		dwType |= PT_EnemyGuildPlayer;
		else if (thePlayerRole.GetGangMgr()->guildRelation(this) == GR_LEAGUE)
		dwType |= PT_LeaguePlayer;*/

		// �������ж�
		if (GetPKKillValue() < 0 || thePlayerRole.isChouRen(GetName()))
			dwType |= PT_RedNamePlayer;

		// PK
		if (thePlayerRole.GetDuelTarget() == GetID())
			dwType |= PT_PKPlayer;

		// ��ͨ
		if (dwType == 0)
			dwType = PT_NormalPlayer;
		return dwType;
	}
	return PT_Other;
}

void CPlayer::AdjustAttackPos()
{
	if( !m_pAttackInfo )
		return;

	if( !theHeroGame.GetPlayerMgr() )
		return;

	if( m_pAttackInfo->nSrcId >= 0 && m_pAttackInfo->nTargetId >= 0 )
	{
		CPlayer* pAttacker = theHeroGame.GetPlayerMgr()->FindByID(m_pAttackInfo->nSrcId);
		CPlayer* pTarget = theHeroGame.GetPlayerMgr()->FindByID(m_pAttackInfo->nTargetId);
		if( pAttacker && pTarget )
		{
			// ��һ������ң�һ���ǹ֣���ѹ��������ͬһ�߶�
			bool bGet = false;
			CPlayer* pMaster = NULL;	// �������ָ��
			CPlayer* pFollow = NULL;	// �������ָ��
			if( pAttacker->IsPlayer() && pTarget->IsMonster() )
			{
				pMaster = pAttacker;
				pFollow = pTarget;
				bGet = true;
			}
			else if( pAttacker->IsMonster() && pTarget->IsPlayer() )
			{
				pMaster = pTarget;
				pFollow = pAttacker;
				bGet = true;
			}

			if( !bGet )
				return;

			D3DXVECTOR3 pMasterPos = pMaster->GetPos();
			D3DXVECTOR3 pFollowPos = pFollow->GetPos();
			if( fabs(pFollowPos.z - pMasterPos.z) > 1.f )
			{
				pFollow->ReSetPos(pFollowPos.x, pFollowPos.y, pMasterPos.z+1.f);
			}
		}
	}
}

void CPlayer::AdjustPosToMaster()
{
	if( !theHeroGame.GetPlayerMgr() )
		return;

	if( GetMasterID() <= -1 )
		return;

	if( m_fPetAdjustPosCD > 0 )
		return;

	m_fPetAdjustPosCD = 2.f;	// 2����һ��

	CPlayer* pMaster = theHeroGame.GetPlayerMgr()->FindByID(GetMasterID());
	if( !pMaster )
		return;

	D3DXVECTOR3 pMasterPos = pMaster->GetPos();
	float fDist = sqrt((pMasterPos.x - m_x)*(pMasterPos.x - m_x) + (pMasterPos.y - m_y)*(pMasterPos.y - m_y));
	if( fDist <= 5.f && fabs(pMasterPos.z - m_z) > 1.f )
		m_z = pMasterPos.z+1.f;
}

void CPlayer::SetTitleTargetName( const char* name )
{
	m_szTitleTargetName = name;
}

void CPlayer::SwitchCampAnim()
{
	CWorldTile* pCurrTile = CURRENTTILE;
	if(!pCurrTile)
		return;

	//ֻ����Ӫ��ͼ��Ч�� 
	if(pCurrTile->GetCanPk() !=  MapConfig::MapData::EPKM_Group_PK)
		return;

	if(!IsNpc())  //ֻ��NPC��Ч��
		return;

	//�Ƿ���Ҫ�л�����
	if(!m_bUpdateFluence)
		return;

	//����Ĭ�϶���
	if(m_nActionFluence == enumBattleInfluence_Max)
		return;

	if(!m_pAnim)
		return;

	int nCurAnimType = m_pAnim->GetCurAnimType();
	if(m_nActionFluence == enumBattleInfluence_Red)  //�ƾ�
	{
		PlayAnim("idle3",	1,"idle3" );  
	}
	else if(m_nActionFluence == enumBattleInfluence_Blue)  //���
	{
		PlayAnim("idle2",	1, "idle2");
	}

}

void CPlayer::InitMonsterAction(int nIndex,SArea *pArea)
{
	if(!pArea)
		return;

	if(pArea->vctActionData.empty())
		return;

	m_bMonsterActioning = true;
	m_shCurrMonsterActionId = pArea->vctActionData[0].shId;
	m_dwElapseMonsterActionTime = HQ_TimeGetTime() + pArea->vctActionData[0].shElapseTime * 1000;	
	m_nZoneIndex  = nIndex;

	PlayMonsterAction();
}

void CPlayer::UpdateMonsterAction(DWORD dwTime)
{
	if(!m_bMonsterActioning)
		return;

	SArea *pArea = theHeroGame.GetPlayerMgr()->GetAreaByIndex(m_nZoneIndex);
	if(!pArea)
	{
		EndMonsterAction();
		return;
	}

	if(m_shCurrMonsterActionId >=  pArea->vctActionData.size() || m_shCurrMonsterActionId < 0)
	{
		EndMonsterAction();
		return;
	}

	//��ǰƬ��ʱ������,������һ��
	if(dwTime > m_dwElapseMonsterActionTime)
	{
		m_shCurrMonsterActionId = pArea->vctActionData[m_shCurrMonsterActionId].shNextId;
		if(m_shCurrMonsterActionId >=  pArea->vctActionData.size() || m_shCurrMonsterActionId < 0)
		{
			EndMonsterAction();
			return;
		}
		m_dwElapseMonsterActionTime = dwTime + pArea->vctActionData[m_shCurrMonsterActionId].shElapseTime * 1000;

		if(m_shCurrMonsterActionId == 0)
		{
			m_bMonsterActioning = false;
			m_shCurrMonsterActionId = 0;
			m_dwElapseMonsterActionTime = 0;
		}
		else
			PlayMonsterAction();
	}
}

void CPlayer::PlayMonsterAction()
{
	if(!m_bMonsterActioning)
		return;

	SArea *pArea = theHeroGame.GetPlayerMgr()->GetAreaByIndex(m_nZoneIndex);
	if(!pArea)
	{
		EndMonsterAction();
		return;
	}

	if(m_shCurrMonsterActionId >=  pArea->vctActionData.size() || m_shCurrMonsterActionId < 0)
	{
		EndMonsterAction();
		return;
	}

	SArea::AreaActionData* pActionData = &pArea->vctActionData[m_shCurrMonsterActionId];

	// ������
	if( pActionData->vctActions.size() && m_pAnim )
	{
		int probability = rand();
		probability %= 100;
		int nActionProbability = 0; // ��ǰaction�ĸ���
		for(int i=0; i<pActionData->vctActions.size(); i++)
		{
			nActionProbability += pActionData->vctActions[i].shProbability;
			if( probability < nActionProbability )
			{
				// ������
				if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
				{
					m_pAnim->PlayLowerAnim(	pActionData->vctActions[i].strAnimName.c_str(),
						MexAnimCtrl::eNormalPlay,
						0,
						1,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
				else
				{
					m_pAnim->PlayAnimByActionName( pActionData->vctActions[i].strAnimName.c_str(),
						MexAnimCtrl::eNormalPlay,
						0,
						1,
						MexAnimCtrl::eMaxTimeout,
						MexAnimCtrl::eDefaultBlendingTime,
						"idle",
						MexAnimCtrl::eNormalPlay );
				}
				break;
			}
		}
	}

	// ˵��
	if( pActionData->vctTalks.size() )
	{
		int probability = rand();
		probability %= 100;
		int nTalkProbability = 0;   // ��ǰtalk�ĸ���
		for(int i=0; i<pActionData->vctTalks.size(); i++)
		{
			nTalkProbability += pActionData->vctTalks[i].shProbability;
			if( probability < nTalkProbability )
			{
				// ��������
				SetChatInfo(std::string(theXmlString.GetString(pActionData->vctTalks[i].shStringId)));
				break;
			}
		}
	}
}

void CPlayer::EndMonsterAction()
{
	m_dwElapseMonsterActionTime = 0;  //�����ʱ��
	m_shCurrMonsterActionId     = 0;
	m_bMonsterActioning         = false;
}

void GetAttrChangeInfo(float value_, eName tipId_, CPlayerRole::enUpdataType attrId_, char *_str, DWORD &_color)
{
	if(NULL == _str)
		return;

	std::string strInfo;
	float fFactor = 0.0f;
	int nNewValue = (int)(value_ + fFactor);
	int nOldValue = (int)(thePlayerRole.GetData(attrId_) + fFactor);
	if(nOldValue < nNewValue)
	{
		_color = 0xff00ff00;
		strInfo += "+";
	}
	else
		strInfo += "-";

	int nValue = (int)(nNewValue - nOldValue);
	if(nValue == 0)
		return;
	nValue = abs(nValue);
	MeSprintf_s(_str,sizeof(_str)*64,"%s%s%d",theXmlString.GetString(tipId_),strInfo.c_str(),nValue);
};

void CPlayer::ShowAttrChangeInfo(SValueChanged &valueChange)
{
	DWORD dwValue = 0;
	float fValue;
	short stValue;
	int	  nValue;
	__int64 n64Value = 0;

	dwValue = valueChange.data.dwValue;
	fValue = valueChange.data.fValue;
	stValue = valueChange.data.stValue;
	nValue = valueChange.data.nValue;
	n64Value = valueChange.data.n64Value;

	DWORD dwColor = 0xffff0000;

	char szWord[256] = {0};

	std::stringstream str;

	std::string strInfo;
	strInfo.clear();

	eName tipId;
	CPlayerRole::enUpdataType attrId;
	switch(valueChange.ustWhichAttr)
	{
	case CharAttr_Strength:  // ����
		{
			float fFactor = 0.0f;
			int nNewValue = (int)(fValue + fFactor);
			int nOldValue = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Strength) + fFactor);
			if(nOldValue < nNewValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)(nNewValue - nOldValue);
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddStrength),strInfo.c_str(),nValue);
		}
		break;
	case  CharAttr_Agility:      // ����
		{
			float fFactor = 0.0f;
			int   nNewValue = (int)(fValue + fFactor);
			int   nOldValue = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Agility) + fFactor);
			if(nOldValue < nNewValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)(nNewValue - nOldValue);
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddAgility),strInfo.c_str(),nValue);
		}
		break;
	case  CharAttr_Stamina: // ����
		{
			float fFactor = 0.0f;
			int   nNewValue = (int)(fValue + fFactor);
			int   nOldValue = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Stamina) + fFactor);

			if(nOldValue < nNewValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)(nNewValue - nOldValue);
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddConstitution),strInfo.c_str(),nValue);
		}
		break;
	case CharAttr_Intelligence:  // ����(����)
		{
			float fFactor = 0.0f;
			int   nNewValue = (int)(fValue + fFactor);
			int   nOldValue = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Intelligence) + fFactor);

			if(nOldValue < nNewValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)(nNewValue - nOldValue);
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddIntelligence),strInfo.c_str(),nValue);
		}
		break;
		//��������
	case  CharAttr_HPMax:  // ��������
		{
			int nOldValue = (int)thePlayerRole.GetData(CPlayerRole::TYPE_HPMAX);//thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.hpMax.final;
			int nNewValue = (int)dwValue;
			if(nOldValue < nNewValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)(nNewValue - nOldValue);
			if(nValue == 0)
				return;
			nValue = abs(nValue); 
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddHPMax),strInfo.c_str(),nValue);
		}
		break;
	case CharAttr_MPMax:              // ��Դ����
		{
			int nOldValue = (int)thePlayerRole.GetData(CPlayerRole::TYPE_MPMAX);//thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.hpMax.final;
			int nNewValue = (int)dwValue;
			if(nOldValue < nNewValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)(nNewValue - nOldValue);
			if(nValue == 0)
				return;
			nValue = abs(nValue); 
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddMPMax),strInfo.c_str(),nValue);
		}
		break;
	case CharAttr_AttackPhysics:             // ������
		{
			int nOldValue = (int)thePlayerRole.GetData(CPlayerRole::TYPE_ATTACKPHYSICS); //thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.attackPhysics.base;
			int nNewValue = (int)fValue;
			if(nOldValue < nNewValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)(nNewValue - nOldValue);
			if(nValue == 0)
				return;
			nValue = abs(nValue); 

			// 			if(GetProfession() == EArmType_Warrior || GetProfession() == EArmType_Assassin)
			// 			    MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddShortAttack),strInfo.c_str(),nValue);//����
			// 			else if(GetProfession() == EArmType_Hunter)
			// 			    MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddLongAttack),strInfo.c_str(),nValue);//Զ��
			// 			else
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d","������",strInfo.c_str(),nValue);
		}
		break;
	case  CharAttr_AttackMagic:        // ħ������������������
		{
			int nOldValue = (int)thePlayerRole.GetData(CPlayerRole::TYPE_AttackMagic);//thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.attackMagic.base;
			int nNewValue = (int)fValue;

			if(nOldValue < nNewValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)(nNewValue - nOldValue);
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",/*"��������"*/theXmlString.GetString(eTip_sAddMagicAttack),strInfo.c_str(),nValue);
		}
		break;
	case CharAttr_DefendPhysics:        // �������
		{
			int nOldValue = (int)thePlayerRole.GetData(CPlayerRole::TYPE_DefendPhysics);
			int nNewValue = (int)fValue;

			if(nOldValue < nNewValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)(nNewValue - nOldValue);
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d","�������",strInfo.c_str(),nValue);
		}
		break;
	case CharAttr_DefendMagic:       // ħ������������������
		{
			int nOldValue = (int)thePlayerRole.GetData(CPlayerRole::TYPE_DefendMagic);//thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.defendMagic.base;
			int nNewValue = (int)fValue;
			if(nOldValue < nNewValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)(nNewValue - nOldValue);
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddMagicDefend),strInfo.c_str(),nValue);
		}
		break;
	case CharAttr_MoveSpeed:          // �ƶ��ٶ�
		{
			// 			float nOldValue = (int)thePlayerRole.GetData(CPlayerRole::TYPE_MOVESPEED);//thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.moveSpeed.base;
			//  			float nNewValue = (float)fValue;
			//  			if(nOldValue - nNewValue < 0.001)
			//  			{
			//  				dwColor = 0xff00ff00;
			//  				strInfo += "+";
			//  			}
			//  			else
			//  				strInfo += "-";
			//  
			//  			float nValue = (nNewValue - nOldValue);
			//  			if(abs(nValue) <= 0.0001)
			//  				return;
			//  			nValue = abs(nValue);
			//  			MeSprintf_s(szWord,sizeof(szWord),"%s%s%.f",theXmlString.GetString(eTip_sAddMoveSpeed),strInfo.c_str(),nValue);
		}
		break;
	case CharAttr_HPRestore:          // HP�ָ�����
	case CharAttr_MPRestore:         // MP�ָ�����
		break;
	case CharAttr_Dodge:              // ������
		{
			int nOldShanBi = (int)thePlayerRole.GetData(CPlayerRole::TYPE_DODGE);//thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.dodge.final;
			// 			if( nOldShanBi % 100 == 0 )
			// 				nOldShanBi = nOldShanBi / 100;
			// 			else
			// 				nOldShanBi = nOldShanBi / 100 + 1;

			int nNewShanBi = stValue;
			// 			if( nNewShanBi % 100 == 0 )
			// 				nNewShanBi = nNewShanBi / 100;
			// 			else
			// 				nNewShanBi = nNewShanBi / 100 + 1;

			if(nOldShanBi < nNewShanBi)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			//strInfo += abs(nNewShanBi - nOldShanBi);

			int nValue = nNewShanBi - nOldShanBi;
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddDodge),strInfo.c_str(),nValue);

		}
		break;		
	case CharAttr_Exact:              // ������
		{
			int nOldMingZhong = (int)thePlayerRole.GetData(CPlayerRole::TYPE_EXACT);//thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.exact.final;
			// 			if( nOldMingZhong % 100 == 0 )
			// 				nOldMingZhong = nOldMingZhong / 100;
			// 			else
			// 				nOldMingZhong = nOldMingZhong / 100 + 1;

			int nNewMingZhong = stValue;
			// 			if( nNewMingZhong % 100 == 0 )
			// 				nNewMingZhong = nNewMingZhong / 100;
			// 			else
			// 				nNewMingZhong = nNewMingZhong / 100 + 1;

			if(nOldMingZhong < nNewMingZhong)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = nNewMingZhong - nOldMingZhong;
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddExact),strInfo.c_str(),nValue);
		}
		break;		
	case CharAttr_Critical:           // ������
		{
			int stOldValue = (int)thePlayerRole.GetData(CPlayerRole::TYPE_CRITICLE);
			if(stOldValue < (int)fValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";
			int nValue = (int)fValue - stOldValue;
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddCritical),strInfo.c_str(),nValue);

		}
		break;		
	case CharAttr_CriticalIntensity:  // �����˺�
		{
			int stOldValue = (int)thePlayerRole.GetData(CPlayerRole::TYPE_CRITICLEINTENSITY);
			if(stOldValue < stValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";

			int nValue = (int)stValue - stOldValue;
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddCriticalIntensity),strInfo.c_str(),nValue);

		}
		break;		
	case CharAttr_Tenacity:           // ����
		{
			int stOldValue = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_TENACITY);
			if(stOldValue < (int)fValue)
			{
				dwColor = 0xff00ff00;
				strInfo += "+";
			}
			else
				strInfo += "-";
			int nValue = (int)fValue - stOldValue;
			if(nValue == 0)
				return;
			nValue = abs(nValue);
			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_sAddTenacity),strInfo.c_str(),nValue);
		}
		break;
	case CharAttr_HP:                     // Ѫ��
		{
		}
		break;
		// 	case CharAttr_ResistDread:        // �־忹��
		// 		{
		// 			short stOldValue = (int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistDread.final;//thePlayerRole.GetData(CPlayerRole::TYPE_RESISTDREAD);
		// 			if(stOldValue < stValue)
		// 			{
		// 				dwColor = 0xff00ff00;
		// 				strInfo += "+";
		// 			}
		// 			else
		// 				strInfo += "-";
		// 
		// 			int nValue = stValue - stOldValue;
		// 			if(nValue == 0)
		// 				return;
		// 			nValue = abs(nValue);
		// 			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_Resist_Dread),strInfo.c_str(),nValue);
		// 
		// 		}
		// 		break;		
		// 	case CharAttr_ResistComa:         // ���Կ���
		// 		{
		// 			short stOldValue = (int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistComa.final;//thePlayerRole.GetData(CPlayerRole::TYPE_RESISTCOMA);
		// 			if(stOldValue < stValue)
		// 			{
		// 				dwColor = 0xff00ff00;
		// 				strInfo += "+";
		// 			}
		// 			else
		// 				strInfo += "-";
		// 
		// 			int nValue = stValue - stOldValue;
		// 			if(nValue == 0)
		// 				return;
		// 			nValue = abs(nValue);
		// 			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_Resist_Coma),strInfo.c_str(),nValue);
		// 		}
		// 		break;		
		// 	case CharAttr_ResistSilence:      // ��Ĭ����
		// 		{
		// 			short stOldValue = (int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistSilence.final;//thePlayerRole.GetData(CPlayerRole::TYPE_RESISTSILENCE);
		// 			if(stOldValue < stValue)
		// 			{
		// 				dwColor = 0xff00ff00;
		// 				strInfo += "+";
		// 			}
		// 			else
		// 				strInfo += "-";
		// 			int nValue = stValue - stOldValue;
		// 			if(nValue == 0)
		// 				return;
		// 			nValue = abs(nValue);
		// 			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_Resist_Silence),strInfo.c_str(),nValue);
		// 		}
		// 		break;		
		// 	case CharAttr_ResistSlow:         // ���ٿ���
		// 		{
		// 			short stOldValue = (int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistSlow.final;//thePlayerRole.GetData(CPlayerRole::TYPE_RESISTSLOW);
		// 			if(stOldValue < stValue)
		// 			{
		// 				dwColor = 0xff00ff00;
		// 				strInfo += "+";
		// 			}
		// 			else
		// 				strInfo += "-";
		// 
		// 			int nValue = stValue - stOldValue;
		// 			if(nValue == 0)
		// 				return;
		// 			nValue = abs(nValue);
		// 
		// 			MeSprintf_s(szWord,sizeof(szWord),"%s%s%d",theXmlString.GetString(eTip_Resist_Slow),strInfo.c_str(),nValue);
		// 		}
		// 		break;
	case CharAttr_AttackSpeed:        // �����ٶ�		
		//case CharAttr_IntonateSpeed:      // �����ٶ�
		//��������
	case CharAttr_Level:  // �ȼ�                                    	
	case CharAttr_Reputation:             // ��ǰ����		
	case CharAttr_CurGetReputation:       // ��ǰ�������                
	case CharAttr_Exploit:                // ��ǰ��ѫ		
	case CharAttr_CurGetExploit:           // ��ǰ��ù�ѫ                                                		
		//case CharAttr_HP:                     // Ѫ��
	case CharAttr_MP:                     // ħ�� 	
	case CharAttr_Exp:                    // ��ǰ����		
	case CharAttr_ExpNotUsed:             // δʹ�õľ���		
	case CharAttr_SkillExp:               // ���ܾ���		
	case CharAttr_SkillExpNotUsed:        // δʹ�õļ��ܾ���		
	case CharAttr_Energy:                 // ����ֵ (��������)		
	case CharAttr_EnergyMax:              // ����ֵ���ֵ        45+����ȼ�(ILevel)*5	
	case CharAttr_Vigor:                  // ���� (�ɼ�����)		
	case CharAttr_VigorMax:               // �������ֵ 45+����ȼ�(ILevel)*5
		break;
	case CharAttr_BreakStrike:   // �Ƽ��˺�
		{
			tipId = eTip_sAddBreakStrike;
			attrId = CPlayerRole::TYPE_BreakStrike;
			GetAttrChangeInfo(stValue, tipId, attrId, szWord, dwColor);
		}
		break;
	case CharAttr_StabStrike:   // �ᴩ�˺�
		{
			tipId = eTip_sAddStabStrike;
			attrId = CPlayerRole::TYPE_StabStrike;
			GetAttrChangeInfo(stValue, tipId, attrId, szWord, dwColor);
		}
		break;
	case CharAttr_ElementStrike:   // Ԫ���˺�
		{
			tipId = eTip_sAddElementStrike;
			attrId = CPlayerRole::TYPE_ElementStrike;
			GetAttrChangeInfo(stValue, tipId, attrId, szWord, dwColor);
		}
		break;
	case CharAttr_ToxinStrike:   // �����˺�
		{
			tipId = eTip_sAddToxinStrike;
			attrId = CPlayerRole::TYPE_ToxinStrike;
			GetAttrChangeInfo(stValue, tipId, attrId, szWord, dwColor);
		}
		break;
	case CharAttr_SpiritStrike:   // �����˺�
		{
			tipId = eTip_sAddSpiritStrike;
			attrId = CPlayerRole::TYPE_SpiritStrike;
			GetAttrChangeInfo(stValue, tipId, attrId, szWord, dwColor);
		}
		break;
	case CharAttr_BreakResist:   // �Ƽ׿���
		{
			tipId = eTip_sAddBreakResist;
			attrId = CPlayerRole::TYPE_BreakResist;
			GetAttrChangeInfo(stValue, tipId, attrId, szWord, dwColor);
		}
		break;
	case CharAttr_StabResist:   // �ᴩ����
		{
			tipId = eTip_sAddStabResist;
			attrId = CPlayerRole::TYPE_StabResist;
			GetAttrChangeInfo(stValue, tipId, attrId, szWord, dwColor);
		}
		break;
	case CharAttr_ElementResist:   // Ԫ�ؿ���
		{
			tipId = eTip_sAddElementResist;
			attrId = CPlayerRole::TYPE_ElementResist;
			GetAttrChangeInfo(stValue, tipId, attrId, szWord, dwColor);
		}
		break;
	case CharAttr_ToxinResist:   // ���ؿ���
		{
			tipId = eTip_sAddToxinResist;
			attrId = CPlayerRole::TYPE_ToxinResist;
			GetAttrChangeInfo(stValue, tipId, attrId, szWord, dwColor);
		}
		break;
	case CharAttr_SpiritResist:   // ������
		{
			tipId = eTip_sAddSpiritResist;
			attrId = CPlayerRole::TYPE_SpiritResist;
			GetAttrChangeInfo(stValue, tipId, attrId, szWord, dwColor);
		}
		break;
	default:
		//assert(0&&"���Դ���");
		break;
	}
	//�߻�Ҫ��ע�� 2011-6-20  21:40
	// 	if(strlen(szWord) > 0)
	//     {
	//         if( dwColor == 0xffff0000 )
	//             CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_AttrDown, szWord );
	//         else if( dwColor == 0xff00ff00 )
	//             CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_AttrUp, szWord );
	//     }
}

void CPlayer::SetFontObject( RTTFont* pFontObj )
{
	fontName_ = pFontObj;
	fontName_->SetLineSpace(8);
}

RTTFont* CPlayer::GetFontObject() const
{
	return fontName_;
}

void CPlayer::PlayAnimWithActionID()
{
	// <= 0 �������ж�
	if( m_nWithNPCActionID <= 0 || !m_pAnim )
		return;

	if( gCfg.m_PlayerNpcActions.find( m_nWithNPCActionID ) == gCfg.m_PlayerNpcActions.end() )
		return;

	const char* pcEndAnim = 0;
	if( IsHaveWeapon() )
		pcEndAnim = "single_idle";
	else
		pcEndAnim = "idle";

	//PlayAnim( gCfg.m_PlayerNpcActions[m_nWithNPCActionID].m_acSingName, m_dwWithNPCActionTime, pcEndAnim );

	m_pAnim->PlayLowerAnim( gCfg.m_PlayerNpcActions[m_nWithNPCActionID].m_acSingName,
		MexAnimCtrl::eNormalPlay,
		0,
		m_dwWithNPCActionTime,
		m_dwWithNPCActionTime,
		MexAnimCtrl::eDefaultBlendingTime,
		pcEndAnim,
		MexAnimCtrl::eNormalPlay );

	m_nWithNPCActionID = 0;
	m_dwWithNPCActionTime = 0;


}
void CPlayer::SetWithNPCAnimInfo( int nActionID, DWORD dwDuringTime )
{
	m_nWithNPCActionID = nActionID;
	m_dwWithNPCActionTime = dwDuringTime;
}

void CPlayer::SetInstantMoving( bool bMoving, ItemDefine::SItemSkill* pSkill )
{
	m_bInstantMoving = bMoving;
	m_pInstantSkill = pSkill;
}
bool CPlayer::TryInstantSkill( ItemDefine::SItemSkill* pSkill )
{
	if( theHeroGame.GetPlayerMgr()->GetMe() != this )
		return false;

	// �����Զ����� [12/8/2010 zhangjiayi]
	if( !m_pInstantSkill || !m_pInstantSkill->bAutoAttackTarget )// �ü���ȷʵ��Ҫ�Զ�����
		return false;

	if( !g_bTheRoleAttackLockTarget )// ֮ǰҲȷʵ�Զ�������
		return false;

	CPlayer* pTagPlayer = theHeroGame.GetPlayerMgr()->FindByID( theHeroGame.GetPlayerMgr()->GetLockPlayerID() );
	if( pTagPlayer )
	{
		bool canAttack = IsInAttackRange(pTagPlayer->GetPos().x, pTagPlayer->GetPos().y,
			pTagPlayer->GetBodyLengthSize(), 0);

		if( canAttack )
		{
			//����Ϣ֪ͨ������������������Ŀ��
			MsgAttackLockTarget	msg;
			if( GettheNetworkInput().SendMsg(&msg) == -1 )
			{
			}
			g_nRoleCommonAttackStatus = CAS_ATTACK_AGAIN_WHEN_FAILED;
		}
	}
	return true;
}
void CPlayer::SetCarrierState(bool bValue)
{
	m_bCarrier = bValue;
	if ( m_bRole )
	{
		if ( bValue )
		{
			s_CUI_ID_FRAME_CrowdCarryMain.SetVisable(true);
			s_CUI_ID_FRAME_CrowdCarryMain.SetPassagerViewer();
		}
		else
		{
			s_CUI_ID_FRAME_CrowdCarryMain.SetVisable(false);
		}
	}
	if ( bValue )
	{
		SetShowWeapon(FALSE);
		SwitchSitLoopAnim(0xFFFFFFFF);
	}
	else
	{
		SetShowWeapon(TRUE);
		SwitchIdleAnim();
	}
}

void CPlayer::AddPassenger(GameObjectId id)
{
	m_passengers.push_back(id);
	if ( m_bRole )
	{
		//s_CUI_ID_FRAME_CrowdCarryMain.UpdateLeftSets( (int)m_passengers.size() );
		s_CUI_ID_FRAME_CrowdCarryMainMore.RefreshPassengerList( m_passengers );
	}

}

void CPlayer::RemovePassenge(GameObjectId id)
{
	for ( std::vector<GameObjectId>::iterator it = m_passengers.begin(); it != m_passengers.end(); it ++ )
	{
		if ( *it == id )
		{
			m_passengers.erase(it);
			break;
		}
	}
	if ( m_bRole )
	{
		//s_CUI_ID_FRAME_CrowdCarryMain.UpdateLeftSets( (int)m_passengers.size() );
		s_CUI_ID_FRAME_CrowdCarryMainMore.RefreshPassengerList( m_passengers );
	}

}

bool CPlayer::IsSameCountry(int nCountry)
{
	if(!SwGlobal::GetWorld() || !SwGlobal::GetWorld()->GetWorldBuffer() || !SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile())
		return false;

	CWorldTile* pCurrTile = CURRENTTILE;
	if(!pCurrTile)
		return false;

	if(pCurrTile->GetCountry() != nCountry)
		return false;

	return true;
}

//------------  ��ʾ�����������С����  ---------------
void CPlayer::SetServerTerrainRectShow( bool bShow )
{
	m_bShowServerRect = bShow;
}

void CPlayer::SetHeightMapRectShow( bool bShow )
{
	if( bShow )
	{
		ReleaseHeightMapData();
		if( LoadHeightMapData() )
		{
			m_bShowHeightMapRect = true;
		}
	}
	else
	{
		ReleaseHeightMapData();
		m_bShowHeightMapRect = false;
	}
}

void CPlayer::ReleaseHeightMapData()
{
	if( m_pHeightMapData )
	{
		delete m_pHeightMapData;
		m_pHeightMapData = NULL;
	}
	m_bHeightMapLoad = false;
}

bool CPlayer::LoadHeightMapData()
{
	if( m_bHeightMapLoad )
		return false;

	if( m_pHeightMapData )
	{
		delete m_pHeightMapData;
		m_pHeightMapData = NULL;
	}

	CWorldTile* pTile = CURRENTTILE;
	if( !pTile )
		return false;

	m_pHeightMapData = new CHeightMapData;

	std::string strFilePath = std::string( GetRootPath() ) + "\\Data\\HeightMap\\" + pTile->GetTileName() + ".height";
	if( !m_pHeightMapData->ReadDataFromFile( strFilePath.c_str() ) )
		return false;

	m_bHeightMapLoad = true;
	return true;
}

void CPlayer::SetMyCircleShow( bool bShow, float fR )
{
	m_bShowMyCircle = bShow;
	m_fMyCircleR = fR;
}

void CPlayer::SetMouseCircleShow( bool bShow, float fR )
{
	m_bShowMouseCircle = bShow;
	m_fMouseCircleR = fR;
}

bool CPlayer::IsHeightMapDataLoad()
{
	return m_bHeightMapLoad;
}

bool CPlayer::IsServerTerrainRectShow()
{
	return m_bShowServerRect;
}

bool CPlayer::IsHeightMapRectShow()
{
	return m_bShowHeightMapRect;
}

bool CPlayer::IsMyCircleShow()
{
	return m_bShowMyCircle;
}

bool CPlayer::IsMouseCircleShow()
{
	return m_bShowMouseCircle;
}

void CPlayer::DrawServerTerrainRect( CPlayer* pPlayer )
{
	if( !pPlayer )
		return;

	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return;

	CPlayer* pMe = pPlayerMgr->GetMe();
	if( !pMe )
		return;

	if( pPlayer->GetID() != pMe->GetID() )
		return;

	CWorldTile* pTile = CURRENTTILE;
	if( !pTile )
		return;

	float fMapWidth = pTile->GetWidth();
	float fMapLength = pTile->GetDepth();

	D3DXVECTOR3 vPos = pMe->GetPos();
	if( vPos.x < 0 || vPos.x > fMapWidth || vPos.y < 0 || vPos.y > fMapLength )
		return;

	// ����С����
	float fSmallRectSize = MAPTILESIZE;
	float fBigRectSize = fSmallRectSize * dr_stageAreaSize;

	int nSmallRectRCount = fMapWidth / fSmallRectSize;
	int nSmallRectVCount = fMapLength / fSmallRectSize;

	int nMeBigRIndex = vPos.x / fBigRectSize;
	int nMeBigVIndex = vPos.y / fBigRectSize;
	int nMeSmallRIndex = nMeBigRIndex * dr_stageAreaSize;
	int nMeSmallVIndex = nMeBigVIndex * dr_stageAreaSize;

	int nSmallRIndexBegin = nMeSmallRIndex;
	int nSmallRIndexEnd = min( nMeSmallRIndex + dr_stageAreaSize - 1, nSmallRectRCount - 1 );
	int nSmallVIndexBegin = nMeSmallVIndex;
	int nSmallVIndexEnd = min( nMeSmallVIndex + dr_stageAreaSize - 1, nSmallRectVCount - 1 );

	// ��С����     2.56 * 9 * 9
	for( int i = nSmallRIndexBegin; i <= nSmallRIndexEnd; ++i )
	{
		for( int j = nSmallVIndexBegin; j <= nSmallVIndexEnd; ++j )
		{
			float fR = i * fSmallRectSize;
			float fV = j * fSmallRectSize;

			// ֱ�߷�5������
			const int nLinePart( 5 );
			for( float fx = fR; fx < fR + fSmallRectSize; fx += fSmallRectSize / nLinePart )
			{
				float fz1( 0.0f ), fz2( 0.0f );
				if( !SwGlobal::GetWorldPicker()->GetHeight( pTile, fx, fV, fz1 ) )
					continue;

				if( !SwGlobal::GetWorldPicker()->GetHeight( pTile, fx + fSmallRectSize / nLinePart, fV, fz2 ) )
					continue;

				float fLinePartEndX = min( fx + fSmallRectSize / nLinePart, fR + fSmallRectSize );
				GetDrawer()->DrawLine3D( D3DXVECTOR3( fx, fV, fz1 + 0.1f ), D3DXVECTOR3( fLinePartEndX, fV, fz2 + 0.1f ), 0xffffff00 );
				if( j == nSmallVIndexEnd )
				{
					float fz3( 0.0f ), fz4( 0.0f );
					if( !SwGlobal::GetWorldPicker()->GetHeight( pTile, fx, fV + fSmallRectSize, fz3 ) )
						continue;

					if( !SwGlobal::GetWorldPicker()->GetHeight( pTile, fx + fSmallRectSize / nLinePart, fV + fSmallRectSize, fz4 ) )
						continue;

					GetDrawer()->DrawLine3D( D3DXVECTOR3( fx, fV + fSmallRectSize, fz3 + 0.1f ),
						D3DXVECTOR3( fLinePartEndX, fV + fSmallRectSize, fz4 + 0.1f ), 0xffffff00 );
				}
			}

			for( float fy = fV; fy < fV + fSmallRectSize; fy += fSmallRectSize / nLinePart )
			{
				float fz1( 0.0f ), fz2( 0.0f );
				if( !SwGlobal::GetWorldPicker()->GetHeight( pTile, fR, fy, fz1 ) )
					continue;

				if( !SwGlobal::GetWorldPicker()->GetHeight( pTile, fR, fy + fSmallRectSize / nLinePart, fz2 ) )
					continue;

				float fLinePartEndY = min( fy + fSmallRectSize / nLinePart, fV + fSmallRectSize );
				GetDrawer()->DrawLine3D( D3DXVECTOR3( fR, fy, fz1 + 0.1f ), D3DXVECTOR3( fR, fLinePartEndY, fz2 + 0.1f ), 0xffffff00 );
				if( i == nSmallRIndexEnd )
				{
					float fz3( 0.0f ), fz4( 0.0f );
					if( !SwGlobal::GetWorldPicker()->GetHeight( pTile, fR + fSmallRectSize, fy, fz3 ) )
						continue;

					if( !SwGlobal::GetWorldPicker()->GetHeight( pTile, fR + fSmallRectSize, fy + fSmallRectSize / nLinePart, fz4 ) )
						continue;

					GetDrawer()->DrawLine3D( D3DXVECTOR3( fR + fSmallRectSize, fy, fz3 + 0.1f ),
						D3DXVECTOR3( fR + fSmallRectSize, fLinePartEndY, fz4 + 0.1f ), 0xffffff00 );
				}
			}
		}
	}
}

void CPlayer::DrawHeightMapRect( CPlayer* pPlayer )
{
	if( !pPlayer || !m_pHeightMapData )
		return;

	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return;

	CPlayer* pMe = pPlayerMgr->GetMe();
	if( !pMe )
		return;

	if( pPlayer->GetID() != pMe->GetID() )
		return;

	if( !m_pHeightMapData->m_ptMapHeader || !m_pHeightMapData->m_ptCharData )
		return;

	CWorldTile* pTile = CURRENTTILE;
	if( !pTile )
		return;

	// ��ȡ�Լ��ڵڼ���
	D3DXVECTOR3 vPos = pMe->GetPos();
	float fRate = ( double )m_pHeightMapData->m_ptMapHeader->rate_M / ( double )m_pHeightMapData->m_ptMapHeader->rate_R;
	float fRectUnit = HEIGHTMAP_UNIT / fRate;

	int nXCount = pTile->GetWidth() / fRectUnit;
	int nYCount = pTile->GetDepth() / fRectUnit;
	int nMeXIndex = vPos.x / fRectUnit;
	int nMeYIndex = vPos.y / fRectUnit;

	int nXIndexBegin = max( 0, nMeXIndex - HEIGHTMAP_SHOW_RECT_CNT / 2 );
	int nXIndexEnd = min( nXCount, nMeXIndex + HEIGHTMAP_SHOW_RECT_CNT / 2 );
	int nYIndexBegin = max( 0, nMeYIndex - HEIGHTMAP_SHOW_RECT_CNT / 2 );
	int nYIndexEnd = min( nYCount, nMeYIndex + HEIGHTMAP_SHOW_RECT_CNT / 2 );

	// ���¶�������
	int nXIndex( 0 ), nYIndex( 0 );
	for( int i = 0; i < HEIGHTMAP_SHOW_RECT_CNT; ++i )
	{
		nXIndex = i + nMeXIndex - HEIGHTMAP_SHOW_RECT_CNT / 2;
		for( int j = 0; j < HEIGHTMAP_SHOW_RECT_CNT; ++j )
		{
			nYIndex = j + nMeYIndex - HEIGHTMAP_SHOW_RECT_CNT / 2;
			int nVtIndex = ( i * HEIGHTMAP_SHOW_RECT_CNT + j ) * 6;
			if( nXIndex < 0 || nXIndex > nXIndexEnd || nYIndexBegin < 0 || nYIndexBegin > nYIndexEnd )
			{
				m_vtHeightMapRect[nVtIndex].p.x = 0;
				m_vtHeightMapRect[nVtIndex].p.y = 0;
				m_vtHeightMapRect[nVtIndex].p.z = 0;
				m_vtHeightMapRect[nVtIndex].color = 0x00000000;
				for( int k = 1; k < 6; ++k )
				{
					m_vtHeightMapRect[nVtIndex + k] = m_vtHeightMapRect[nVtIndex];
				}
			}
			else
			{
				// ��������0.5
				m_vtHeightMapRect[nVtIndex].p.x = nXIndex * fRectUnit;
				m_vtHeightMapRect[nVtIndex].p.y = nYIndex * fRectUnit;
				m_vtHeightMapRect[nVtIndex].p.z = m_pHeightMapData->GetZbyXY( static_cast< size_t >( ( m_vtHeightMapRect[nVtIndex].p.x + fRectUnit ) * fRate ),
					static_cast< size_t >( ( pTile->GetDepth() - m_vtHeightMapRect[nVtIndex].p.y - fRectUnit ) * fRate ) ) + 0.5f;

				// ������ɫ
				float fH( 0.0f ), fS( 1.0f ), fV( 0.5f );
				int nTmp = 240 - m_vtHeightMapRect[nVtIndex].p.z;
				nTmp = max( 0, nTmp );
				nTmp = min( 240, nTmp );        // �趨ɫ�����240����Windowsͳһ�������

				// ���߶ȵ���ɫ��ʾ��Ϊ20�ȷ�
				nTmp = nTmp % 12 * 20;
				fH = float( nTmp ) / 240.0f;
				m_vtHeightMapRect[nVtIndex].color = GetColorByAHSL( 1.0f, fH, fS, fV );

				for( int k = 1; k < 4; ++k )
				{
					m_vtHeightMapRect[nVtIndex + k] = m_vtHeightMapRect[nVtIndex];
				}
				m_vtHeightMapRect[nVtIndex + 1].p.x += fRectUnit;
				m_vtHeightMapRect[nVtIndex + 2].p.y += fRectUnit;
				m_vtHeightMapRect[nVtIndex + 3].p.x += fRectUnit;
				m_vtHeightMapRect[nVtIndex + 3].p.y += fRectUnit;

				// ��С����0.05
				m_vtHeightMapRect[nVtIndex + 0].p.x += 0.05f;
				m_vtHeightMapRect[nVtIndex + 0].p.y += 0.05f;
				m_vtHeightMapRect[nVtIndex + 1].p.x -= 0.05f;
				m_vtHeightMapRect[nVtIndex + 1].p.y += 0.05f;
				m_vtHeightMapRect[nVtIndex + 2].p.x += 0.05f;
				m_vtHeightMapRect[nVtIndex + 2].p.y -= 0.05f;
				m_vtHeightMapRect[nVtIndex + 3].p.x -= 0.05f;
				m_vtHeightMapRect[nVtIndex + 3].p.y -= 0.05f;

				m_vtHeightMapRect[nVtIndex + 4] = m_vtHeightMapRect[nVtIndex + 2];
				m_vtHeightMapRect[nVtIndex + 5] = m_vtHeightMapRect[nVtIndex + 1];
			}
		}
	}

	// ��ȾС����
	IRenderer* r = GetEngine()->GetRenderer();
	r->SetTexture( 0, NULL );
	r->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );
	r->SetRenderState( D3DRS_LIGHTING,  FALSE );
	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	r->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
	r->SetTextureStageState( 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
	r->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
	r->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );
	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );
	r->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	r->Commit();

	r->DrawPrimitiveUP( D3DPT_TRIANGLELIST, HEIGHTMAP_SHOW_RECT_CNT * HEIGHTMAP_SHOW_RECT_CNT * 2, m_vtHeightMapRect, sizeof( CBaseGraphics::Vertex3D ) );
}

void CPlayer::DrawMyCircle( CPlayer* pPlayer )
{
	if( !pPlayer )
		return;

	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return;

	CPlayer* pMe = pPlayerMgr->GetMe();
	if( !pMe )
		return;

	if( pPlayer->GetID() != pMe->GetID() )
		return;

	D3DXVECTOR3 vPos = pMe->GetPos();
	DrawTerrainCircle( vPos.x, vPos.y, m_fMyCircleR, 0xffff0000 );
	DrawTerrainCircle( vPos.x, vPos.y, 0.2f, 0xffff0000 );
}

void CPlayer::DrawMouseCircle( CPlayer* pPlayer )
{
	if( !pPlayer )
		return;

	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return;

	CPlayer* pMe = pPlayerMgr->GetMe();
	if( !pMe )
		return;

	if( pPlayer->GetID() != pMe->GetID() )
		return;

	// ��ȡ���ʰȡ�ĵر�����
	POINT ptMouse;
	GetCursorPos( &ptMouse );
	ScreenToClient( GetActiveWindow(), &ptMouse );
	float fx = ptMouse.x;
	float fy = ptMouse.y;

	if( ptMouse.x <= 0 || ptMouse.x >= SCREEN_WIDTH || ptMouse.y <= 0 || ptMouse.y >= SCREEN_HEIGHT )
		return;

	if( !theHeroGame.PickFromTerrain( fx, fy ) )
		return;

	// ��Բ
	DrawTerrainCircle( fx, fy, m_fMouseCircleR, 0xff0000ff );
	DrawTerrainCircle( fx, fy, 0.2f, 0xff0000ff );
}

void CPlayer::DrawTerrainCircle( float fCenterX, float fCenterY, float fR, DWORD dwColor )
{
	CWorldTile* pTile = CURRENTTILE;
	if( !pTile )
		return;

	// ÿ3�㻭����
	const float fDegree( PI / 60.0f );
	for( float fD = 0.0f; fD <= PI * 2; fD += fDegree )
	{
		float fX1 = fCenterX + fR * sinf( fD );
		float fY1 = fCenterY + fR * cosf( fD );
		float fX2 = fCenterX + fR * sinf( fD + fDegree );
		float fY2 = fCenterY + fR * cosf( fD + fDegree );
		float fZ1( 0.0f ), fZ2( 0.0f );

		if( !SwGlobal::GetWorldPicker()->GetHeight( pTile, fX1, fY1, fZ1 ) )
			continue;

		if( !SwGlobal::GetWorldPicker()->GetHeight( pTile, fX2, fY2, fZ2 ) )
			continue;

		// �����ˮ�棬����Ҫ���⴦��
		CWorldChunk* pChunk = pTile->GetChunkFromPos( fX1, fY1 );
		if( pChunk )
		{
			if( pChunk->GetLiquidHeight() > fZ1 )
			{
				fZ1 =  pChunk->GetLiquidHeight();
			}
		}
		pChunk = pTile->GetChunkFromPos( fX2, fY2 );
		if( pChunk )
		{
			if( pChunk->GetLiquidHeight() > fZ2 )
			{
				fZ2 =  pChunk->GetLiquidHeight();
			}
		}
		GetDrawer()->DrawLine3D( D3DXVECTOR3( fX1, fY1, fZ1 + 0.1f ), D3DXVECTOR3( fX2, fY2, fZ2 + 0.1f ), dwColor );
	}
}

DWORD CPlayer::GetColorByAHSL( float fAlpha, float fHue, float fSaturation, float fLighteness )
{
	// ɫ�ȣ����Ͷȣ����� ת RGB
	fAlpha = max( 0.0f, fAlpha );
	fAlpha = min( 1.0f, fAlpha );
	fHue = max( 0.0f, fHue );
	fHue = min( 1.0f, fHue );
	fSaturation = max( 0.0f, fSaturation );
	fSaturation = min( 1.0f, fSaturation );
	fLighteness = max( 0.0f, fLighteness );
	fLighteness = min( 1.0f, fLighteness );

	DWORD dwA( 0 ), dwR( 0 ), dwG( 0 ), dwB( 0 );
	float fTmp1( 0.0f ), fTmp2( 0.0f );
	if( fSaturation < 0.01f )
	{
		dwR = fLighteness * 255.0f;
		dwG = fLighteness * 255.0f;
		dwB = fLighteness * 255.0f;
	}
	else
	{
		if( fLighteness < 0.5f )
		{
			fTmp2 = fLighteness * ( 1.0f + fSaturation );
		}
		else
		{
			fTmp2 = ( fLighteness + fSaturation ) - ( fSaturation * fLighteness );
		}

		fTmp1 = 2.0f * fLighteness - fTmp2;

		dwR = 255.0f * Hue2RGB( fTmp1, fTmp2, fHue + ( 1.0f / 3.0f ) );
		dwG = 255.0f * Hue2RGB( fTmp1, fTmp2, fHue );
		dwB = 255.0f * Hue2RGB( fTmp1, fTmp2, fHue - ( 1.0f / 3.0f ) );
	}

	dwA = ( fAlpha ) * 255.0f;
	DWORD dwColor = ( dwA << 24 ) + ( dwR << 16 ) + ( dwG << 8 ) + dwB;
	return dwColor;
}

float CPlayer::Hue2RGB( float v1, float v2, float vH )
{
	if( vH < 0.0f )
	{
		vH += 1.0f;
	}
	if( vH > 1.0f )
	{
		vH -= 1.0f;
	}
	if( 6.0f * vH < 1.0f )
	{
		return v1 + ( v2 - v1 ) * 6.0f * vH;
	}
	if( 2.0f * vH < 1.0f )
	{
		return v2;
	}
	if( 3.0f * vH < 2.0f )
	{
		return v1 + ( v2 - v1 ) * ( ( 2.0f / 3.0f ) - vH ) * 6.0f;
	}
	return v1;
}
//-----------------------------------------------------

void CPlayer::ShowPetEffect()
{
	if(!m_bShowPetEffect)
		return;

	if(!m_pAnim)
		return;

	PlayEffect((char*)m_strPetEffect.c_str(),this);
	m_bShowPetEffect = false;
}

void CPlayer::SetPetEffect(const char* pszEffectName)
{
	m_bShowPetEffect = true;
	m_strPetEffect   = pszEffectName;
}

void CPlayer::TestPlayAnimByType(const char* pszAnim,bool bUpper)
{
	if(bUpper)		
		m_pAnim->PlayUpperAnim( pszAnim,MexAnimCtrl::eNormalPlay,0,1,MexAnimCtrl::eMaxTimeout,MexAnimCtrl::eDefaultBlendingTime);
	else
		m_pAnim->PlayLowerAnim(pszAnim,MexAnimCtrl::eNormalPlay,0,MexAnimCtrl::eMaxLoopTimes,MexAnimCtrl::eMaxTimeout,MexAnimCtrl::eDefaultBlendingTime,"Idle",MexAnimCtrl::eNormalPlay);
}


void CPlayer::SetActionState(eActionState eValue,D3DXVECTOR3 vDir)
{
	m_eState = eValue;
	if(m_eState == eAction_HitBack)
		m_HitBackDir = vDir;

	static int nElapse = 300;
	m_eStateTimer.Start(nElapse);
}

void CPlayer::ProcessActionState()
{
	switch(m_eState)
	{
	case eAction_Buoy:
		ProcessBuoy();
		break;
	case eAction_HitBack:
		ProcessHitBack();
		break;
	default:
		break;
	}
}

void CPlayer::ProcessHitBack()
{
	if(m_eState != eAction_HitBack)
		return;

	if(m_eStateTimer.IsTimerDone())
	{
		m_eState = eAction_None;
		return;
	}

	m_eStateTimer.Run();

	static float fMoveLen = 0.4f;
	D3DXVECTOR3 vLen = m_HitBackDir * fMoveLen + D3DXVECTOR3(m_x,m_y,m_z);

	D3DXVECTOR3 vDir = D3DXVECTOR3(0,0,0);
	float fDistToTarget = GetDistToTarget( vLen.x, vLen.y );
	float fRoleHeight = 80.0f*Config::m_fMdlSpaceScale;

	vDir.x = vLen.x - m_x;
	vDir.y = vLen.y - m_y;
	D3DXVec3Normalize( &vDir, &vDir );

	BOOL bCanMove = TRUE;
	D3DXVECTOR3 vTestPos = D3DXVECTOR3(m_x,m_y,m_z);

	//б�µ��ж�
	//ͨ��ѭ���ҳ������ƶ���λ��
	while( fDistToTarget > 0 )
	{
		if( fDistToTarget > 0.5f )
		{
			vTestPos.x += vDir.x * 0.5f;
			vTestPos.y += vDir.y * 0.5f;
			fDistToTarget -= 0.5;
		}
		else
		{
			vTestPos.x += vDir.x * fDistToTarget;
			vTestPos.y += vDir.y * fDistToTarget;
			fDistToTarget = 0;
		}

		DWORD		dwLoadFlags = 0;
		BOOL		bInFloor = FALSE;
		D3DXVECTOR3 vTargetNormal = D3DXVECTOR3(0,0,0);
		float       fHeadHeight = 1.7;
		Box*		pBBox = GetWorldBBox();
		if( pBBox )
			fHeadHeight = pBBox->v[4].z - pBBox->v[0].z;

		float fZ = 0;
		if(m_bRole)
			fZ = GetZByXY( vTestPos.z + fRoleHeight,vTestPos.x, vTestPos.y, 0, &bInFloor, &dwLoadFlags, true, &vTargetNormal );
		else
			fZ = GetZByXY( vTestPos.z + fRoleHeight,vTestPos.x, vTestPos.y, 0, &bInFloor, &dwLoadFlags, false, &vTargetNormal );

		// ����0.5�׵ĿӲ��ƶ�
		if( vTestPos.z - fZ > 0.5f )
		{
			bCanMove = FALSE;
			break;
		}
		else
			vTestPos.z = fZ;

		// �ж���б��
		D3DXVECTOR3 vAxis(0,0,1);
		D3DXVECTOR3 vUp(0,0,1);

		vAxis = vTargetNormal;
		D3DXVec3Normalize( &vAxis, &vAxis );
		float fDot = D3DXVec3Dot( &vUp, &vAxis );
		float fTheta = acosf( fDot );

		if( fTheta > g_fTheRoleSlipJumpingAngle && ( vAxis.x != 0 || vAxis.y != 0 ) )
		{
			bCanMove = FALSE;
			break;
		}
	}

	//�����ƶ�
	if(!bCanMove)
	{
		m_eStateTimer.Reset(); //ֹͣ�ƶ�
		m_eState = eAction_None;
		return;
	}

	//�����赲����ж�
	D3DXVECTOR3 vCollisionDir = D3DXVECTOR3( 0, 0, 0 );
	D3DXVECTOR3 vCollisionNormal = D3DXVECTOR3( 0, 0, 1 );
	float fAngleToCollision = 0;
	float fDistToCollision = 0;

	D3DXVECTOR3 vStart = D3DXVECTOR3(m_x,m_y,m_z);

	if((!((abs(vDir.x) < 0.001f) && (abs(vDir.y) < 0.001f)))
		&&thePlayerRole.GetDistToCollision( vStart, vDir, &fDistToCollision, &vCollisionDir, &vCollisionNormal, &fAngleToCollision ) )
	{
		float fDis = GetDistToTarget(vTestPos.x,vTestPos.y);
		if(fDis > fDistToCollision)  //��һ���ƶ����赲ֱ��ֹͣ�ƶ�
		{
			m_eStateTimer.Reset();
			m_eState = eAction_None;
			return;
		}
	}

	m_x = vTestPos.x;
	m_y = vTestPos.y;
	m_z = vTestPos.z;

	m_vSaveXYGetZ = m_z;
	m_fTerrainZ	  = m_z;

	m_fLastGetZ_x = m_x;
	m_fLastGetZ_y = m_y;
	m_fLastGetZ_z = m_z;
}

void CPlayer::ProcessBuoy()
{
	if(m_eState != eAction_Buoy)
		return;
}


void CPlayer::EquipTalismanById(unsigned short usItemID)
{
	if(usItemID <= 0)
		return;

	m_bShowTaliman = true;
	m_nTalismanId = usItemID;

	CreateTaliman(usItemID);
}

void CPlayer::CreateTaliman(unsigned short ustItemID)
{
	if(!m_bShowTaliman)
		return;

	ItemDefine::SItemCommon* pCommon = GetItemDetailConfig().GetItemByID(ustItemID);
	if(!pCommon || pCommon->ucItemType != ItemDefine::ITEMTYPE_TALISMAN)
	{
		m_bShowTaliman = false;
		return;
	}

	ItemDefine::SItemTalisman* pTalisman = (ItemDefine::SItemTalisman*)pCommon;

	if(!m_pAnimTaliman)
		m_pAnimTaliman = MeNew CPlayerAnim;

	if(!m_pAnimTaliman)
	{
		m_nTalismanId = 0;
		m_bShowTaliman = false;
		return;
	}

	m_pAnimTaliman->SetPlayer(this);
	m_pAnimTaliman->MyChangeModel( pTalisman->iModelID, FALSE, NULL );
	m_bShowTaliman = true;
}

void CPlayer::UnEquipTalisman()
{
	m_bShowTaliman = false;
}

void CPlayer::DestroyTaliman()
{
	if(!m_bShowTaliman)
		return;

	if(!m_pAnimTaliman)
		return;

	if(m_pAnimTaliman)
	{
		m_pAnimTaliman->Destroy();
		delete m_pAnimTaliman;
		m_pAnimTaliman = NULL;
		m_nTalismanId = 0;
	}
}

void CPlayer::UpdateTaliman(DWORD dwTime)
{
	if(!m_bShowTaliman)
		return;

	if(!m_pAnimTaliman)
		return;

	float x = m_x,y = m_y,z = m_z;
	if(m_pAnim&&m_pAnim->GetMex())
	{
		BOOL bRetOk = FALSE;
		int headBone = m_pAnim->GetMex()->GetSkeleton()->FindBone("Bip01 Head");
		Vector vPos = m_pAnim->GetBoneWorldPos(headBone,&bRetOk);
		if(bRetOk)
		{
			x = vPos.x;
			y = vPos.y;
			z = vPos.z;
		}
	}

	//m_pAnimTaliman->SetRotationX( m_fCurRotationX );
	m_pAnimTaliman->SetScale( 0.02f );
	m_pAnimTaliman->SetPosition( x, y, z );
	m_pAnimTaliman->CalcTransformMatrix( (MeMatrix*)&m_matTransform );
	m_pAnimTaliman->Update( HQ_TimeGetTime(), (MeMatrix*)&m_matTransform );
	m_pAnimTaliman->UpdateComponents( HQ_TimeGetTime(), (MeMatrix*)&m_matTransform);
}

void CPlayer::RenderTaliMan()
{
	if(!m_bShowTaliman)
		return;

	if(!m_pAnimTaliman)
		return;

	m_pAnimTaliman->Render(m_fCurRenderAlpha);
}

float CPlayer::GetZByXY(float fCurrentZ,float x,float y,DWORD dwFlag,BOOL* bInFloor /*= NULL*/,DWORD* pdwRet /*= NULL*/,
						BOOL bIsRole /*= false*/, D3DXVECTOR3 *pNormal /*= NULL*/ )
{
	float fResult = 0.0f;
	fResult = SwGlobal::GetWorldPicker()->GetZByXY( fCurrentZ,  x, y, dwFlag, bInFloor, pdwRet, bIsRole,pNormal);

	if (IsPlayer() || m_MasterID != -1)
	{
		CPlayerMgr *pMgr = theHeroGame.GetPlayerMgr();
		if(pMgr)
		{
			if(pMgr->GetZByXY(40000.0f,x,y,fResult))
			{
				m_bInElevator = true;
				return fResult;
			}
		}
		m_bInElevator = false;
	}

	return fResult;
}

int CPlayer::GetNpcType()
{
	if (!m_pNpcCoordInfo)
		return 0;

	//return m_pNpcCoordInfo->_nType;
	NpcInfo::Npc * npc = theNpcInfo.GetNpcByStaticId(m_pNpcCoordInfo->_nID);
	if (npc != NULL)
		return npc->type;
	else
		return -1;
}


void CPlayer::SwitchMedicalAnim()
{
	if(!m_pAnim)
		return;

	// 	float fScale = 0.5f;
	// 	if(m_pAnim && m_pAnim->GetMexCfg())
	// 	{
	// 		fScale = (float)(m_pAnim->GetMexCfg()->m_BodyRadius.m_npRadius.GetNumber());
	// 		fScale = fScale * Config::m_fMdlSpaceScale * m_fBodySize;
	// 	}
	// 
	// 	if(!gCfg.m_strSitEffect.empty())
	// 	    PlayEffect((char*)gCfg.m_strSitEffect.c_str(),this,fScale);
	// 
	// 	m_pAnim->PlayLowerAnim(	gCfg.m_strSitBeginAnim.c_str(),
	// 		MexAnimCtrl::eNormalPlay,
	// 		0,
	// 		1,
	// 		MexAnimCtrl::eMaxTimeout,
	// 		MexAnimCtrl::eDefaultBlendingTime,
	// 		gCfg.m_strSitEndAnim.c_str(),
	// 		MexAnimCtrl::eNormalPlay,
	// 		0,
	// 		MexAnimCtrl::eMaxLoopTimes,
	// 		MexAnimCtrl::eMaxTimeout,
	// 		0 
	// 		);
}

void CPlayer::PlayNpcHideOrShow(bool isHide)
{
	float fScale = PlayerInfoMgr::Instance()->GetScaleForPlayer(this);
	if (isHide)
	{
		PlayEffect((char*)gCfg.m_strNpcShowEffect.c_str(),this,fScale);
		PlayAnim( gCfg.m_strNpcShowAnim.c_str(),1,"idle");
	}
	else
	{
		PlayEffect((char*)gCfg.m_strNpcHideEffect.c_str(),this,fScale);
		PlayAnim( gCfg.m_strNpcHideAnim.c_str(),1,"idle" );
	}
}

void CPlayer::HideSpeicalNpc()
{
	if(!IsNpc())
		return;

	//ͨ��NPCID����
	if( !m_pNpcCoordInfo )
	{
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(GetNpcID());
		m_pNpcCoordInfo = const_cast<NpcCoordInfo*>( pInfo );
	}

	if(!m_pNpcCoordInfo)
		return;

	if( m_pNpcCoordInfo->_nType != eNT_SpecialNpc)
		return;

	int nNpcTipsType = theApp->GetPlayerMgr()->UpdateNpcTipsType( m_pNpcCoordInfo );
	SetHide(nNpcTipsType == 0);
}

bool bPlayHideNpcEffect = true;
void CPlayer::ProcessNpcHideOrShow(int nNpcType)
{

	//lyh ����npcû������ ������ʾ
	if( m_nNpcTipsType != CPlayerMgr::eNpcTips_HaveQuest &&
		m_nNpcTipsType != CPlayerMgr::eNpcTips_HaveQuestNotNow &&
		m_nNpcTipsType != CPlayerMgr::eNpcTips_QuestDone)
	{   
		if(m_bBeginNpcShow && !IsHide()) //npc�Ѿ���ʾ�˲���û������ ��������
		{
			if(HQ_TimeGetTime() - m_dwNpcBeginTime >1000 && bPlayHideNpcEffect )
			{
				PlayNpcHideOrShow(false); //��ʾ ������Ч����ʧ����
				bPlayHideNpcEffect = false;
			}

			if(HQ_TimeGetTime() - m_dwNpcBeginTime > 3000)
			{
				SetHide(true); //������֮�����ظ�npc
				if(nNpcType == 0)
					if(theApp->GetPlayerMgr()->GetLockPlayerID() == GetID())
						theApp->GetPlayerMgr()->SetLockNpc(-1);

				m_bBeginNpcShow = false;
				bPlayHideNpcEffect = true;

			}
		}
		return;
	}

	//lyh ����npc������ ������ʾ��
	if (!m_bBeginNpcShow) //��ʾncp��
	{	
		SetHide(false); //
		PlayNpcHideOrShow(true); //��ʾ

		if(nNpcType == 0)
			if(theApp->GetPlayerMgr()->GetLockPlayerID() == GetID())
				theApp->GetPlayerMgr()->SetLockNpc(-1);

		m_bBeginNpcShow = true;
		bPlayHideNpcEffect = true;

		return;
	}



	//�Ƿ�ʼ������
	//if(m_bBeginNpcShow)
	//{
	//	if(HQ_TimeGetTime() - m_dwNpcBeginTime > 3000)
	//	{
	//		if(nNpcType != 0)
	//		{
	//			PlayNpcHideOrShow(false); //������
	//		}
	//		SetHide(nNpcType == 0);
	//		if(nNpcType == 0)
	//			if(theApp->GetPlayerMgr()->GetLockPlayerID() == GetID())
	//				theApp->GetPlayerMgr()->SetLockNpc(-1);

	//		m_bBeginNpcShow = false;
	//		return;
	//	}
	//}

	//bool isHide = (nNpcType == 0);

	//if(!m_bBeginNpcShow &&((m_bHide&&!isHide) || (!m_bHide&&isHide)))
	//{
	//	if(isHide)
	//	{
	//		m_bBeginNpcShow = true;
	//		m_dwNpcBeginTime = HQ_TimeGetTime();

	//		PlayNpcHideOrShow(isHide);
	//	}
	//	else
	//	{
	//		m_bBeginNpcShow = true;
	//		m_dwNpcBeginTime = HQ_TimeGetTime() + 3000;
	//	}
	//}
}


void CPlayer::BeginPlaying(int nSceneID)
{
	m_nSceneID = nSceneID;

	m_nCurrSegmentIndex = 0;
	m_dwCurrSegBeginTime = HQ_TimeGetTime();
}

void CPlayer::EndPlaying()
{
	m_nSceneID = -1;

	m_nCurrSegmentIndex = -1;
	m_dwCurrSegBeginTime = 0;
}

void CPlayer::ProcessSceneSegment()
{
	if(m_nSceneID == -1)
		return;

	SceneAction *pAction = theScenePlay.GetActionInfoById(m_nSceneID);
	if(!pAction)
		return;

	if(m_nCurrSegmentIndex < 0 || m_nCurrSegmentIndex >= pAction->vecSet.size())
		return;

	ElapseTime *pElapse = &pAction->vecSet[m_nCurrSegmentIndex];
	if(!pElapse)
		return;

	//ʱ��û�е�����
	if(HQ_TimeGetTime() - m_dwCurrSegBeginTime < pElapse->nTime)
		return;

	if( pElapse->set.size() <= 0 )  //������д����
	{
		EndPlaying();
		return;
	}

	Segment *pSeg = &pElapse->set[0];
	if(!pSeg)
		return;

	//��ͷ�й�
	theHeroGame.GetPlayerMgr()->InitCamera(pAction->nModelID);
	if(!pSeg->strTrack.empty())
	{
		theHeroGame.GetPlayerMgr()->PlayTaskAnim(pSeg->strTrack.c_str(),pAction->fx,pAction->fy,pAction->fz,pAction->fRot);
		theHeroGame.GetPlayerMgr()->BeginTrack();
	}

	//˵��
	if(pSeg->nTalkId != 0)
		SetChatInfo(std::string(theXmlString.GetString(pSeg->nTalkId)));

	//����
	if(!pSeg->strAnimBegin.empty())
	{
		char szEndAnim[64] = {0};
		//Ĭ�ϲ���Idle����
		if(pSeg->strAnimEnd.empty())
		{
			if(IsHaveWeapon())
				MeSprintf_s(szEndAnim,sizeof(szEndAnim),"%s","single_idle");
			else
				MeSprintf_s(szEndAnim,sizeof(szEndAnim),"%s","idle");
		}
		else
		{
			MeSprintf_s(szEndAnim,sizeof(szEndAnim),"%s",pSeg->strAnimEnd.c_str());
		}

		if (m_pAnim)
		{
			if( m_pAnim->IsUpperBodyAndLowerBodyMode() )
			{
				m_pAnim->PlayLowerAnim(	pSeg->strAnimBegin.c_str(),
					MexAnimCtrl::eNormalPlay,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					szEndAnim,
					MexAnimCtrl::eNormalPlay );
			}
			else
			{

				m_pAnim->PlayAnimByActionName( pSeg->strAnimBegin.c_str(),
					MexAnimCtrl::eNormalPlay,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					szEndAnim,
					MexAnimCtrl::eNormalPlay );
			}
		}		
	}

	//���ﶯ��
	if(!pSeg->strMountAnimBegin.empty())
	{
		if(m_pMountAnim&&m_bMounting)
		{
			if(m_pMountAnim->IsUpperBodyAndLowerBodyMode())
			{
				m_pMountAnim->PlayLowerAnim( pSeg->strMountAnimBegin.c_str(),
					MexAnimCtrl::eNormalPlay,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					pSeg->strMountAnimEnd.c_str(),
					MexAnimCtrl::eNormalPlay);

			}
			else
			{
				m_pMountAnim->PlayAnimByActionName( pSeg->strMountAnimBegin.c_str(),
					MexAnimCtrl::eNormalPlay,
					0,
					1,
					MexAnimCtrl::eMaxTimeout,
					MexAnimCtrl::eDefaultBlendingTime,
					pSeg->strMountAnimEnd.c_str(),
					MexAnimCtrl::eNormalPlay);
			}
		}
	}

	m_nCurrSegmentIndex = pElapse->nNextId;
	if(m_nCurrSegmentIndex <= 0)
	{ 
	   if(theHeroGame.GetPlayerMgr())
		theHeroGame.GetPlayerMgr()->EndTrack();

		EndPlaying();
		return;
	}

	m_dwCurrSegBeginTime = HQ_TimeGetTime();
}

void CPlayer::SetTypeStatus( uint8 val )
{
	m_nTypeStatus = val;
	MonsterStatusMgr::Instance()->ChangeMonsterStatus(GetID(), GetMonsterID(),val);
}

bool CPlayer::IsCanOperateByKey(AN_Configure_ShortcutKey::ShortCutKey_Configure type)
{
	if(!m_bMounting)
		return true;

	ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountModelID );
	if( !pDrome )
		return true;

	switch( pDrome ->shMoveType )
	{
	case ItemDefine::movetype_twofooted:          // ˫���ƶ�
	case ItemDefine::movetype_fourfooted:         // �����ƶ�
	case ItemDefine::movetype_fly:                // �����ƶ�
	case ItemDefine::movetype_reptile:            // �����ƶ�
	case ItemDefine::movetype_drive:              // ��ʻ�ƶ�
	case ItemDefine::movetype_fourwheel:          // �����ƶ�
		break;
	case ItemDefine::movetype_twowheel:           // �����ƶ�
		{
			if(type == AN_Configure_ShortcutKey::AN_SCKC_leftwalk || type == AN_Configure_ShortcutKey::AN_SCKC_rightwalk)
				return false;
		}
		break;
	default:
		break;
	}

	return true;
}

void CPlayer::ShapeShift()
{
	if (mIsYabiaoState)
	{
		//CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, "ѹ��״̬�²��ܱ�������"));
		return;
	}

	CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(mHeroID);
	if (itemHero == NULL)
		return;

	// ����ͷ�������͡���ɫ
	SetEquip(eKeyAll_Hair, &m_equips[eKeyAll_Hair].item);
	SetEquip(eKeyAll_Face, &m_equips[eKeyAll_Face].item);
	ChangeSkeletonAndEquipAllItem(this->HasFightFlag(eFighting));

	// �ı����ʹ�С
	if (m_pAnim != NULL)
		m_pAnim->SetScale(PlayerInfoMgr::Instance()->GetScaleForPlayer(this));

	// ˢ��ͷ��
	if(this == theHeroGame.GetPlayerMgr()->GetMe())
	{
		s_CUI_ID_FRAME_Group_Me.RefreshHeadPic(true);
	}
	else
	{
		if(theHeroGame.GetPlayerMgr()->GetLockPlayerID() != -1&&theHeroGame.GetPlayerMgr()->GetLockPlayerID() == GetID())
		{
			s_CUI_ID_FRAME_Target.SetPlayer(-1);
			s_CUI_ID_FRAME_Target.SetPlayer(GetID());
		}
	}
}
void CPlayer::SetBeLongID(uint32 ID)
{
	if(ID == m_BeLongID) return;
	m_BeLongID = ID;
	//�����ҵ�ǰѡ��Ĺ��������ID ���ù���ͷ���ú�
	//�жϵ�ǰĿ���Ƿ�Ϊָ������
	if(s_CUI_ID_FRAME_Target.GetSelId() == GetID())
		s_CUI_ID_FRAME_Target.UpdateBeLongID(m_BeLongID);
}


int CPlayer::GetEffectCharSkillID()
{
	return m_EffectCharSkillID;
}
void CPlayer::SetEffectCharSkillID(int skillID)
{
	m_EffectCharSkillID = skillID;
}