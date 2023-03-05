#include <stdio.h> 
#include "MeTerrain/stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <commdlg.h>
#include <tchar.h>
#include "Dxsdk/d3dx9.h"
#include "Dxsdk/dinput.h"
#include <string.h>
#include <vector>
#include <map>
#include <mmsystem.h>
#include "Dxsdk/dxerr9.h"
#include "Cfg.h"
#include "DXUtil.h"
#include "DuelTips.h"
#include "BattleFlag.h"
#include "Helper.h"
#include "NpcInfo.h"
#include "NpcCoord.h"
#include "FilePath.h"
#include "MathLib.h"
#include "Sociality.h"
#include "../Resource/Resource.h"
#include "Me3d\Include.h"
#include "Me3d\Config.h"
#include "FuncPerformanceLog.h"
#include "Effect.h"
#include "PlayerRole.h"
#include "MonsterStatusConfig.h"
#include "tga.h"
#include "Me3d/BaseGraphics.h"
#include "MeFont/MeFontSystem.h"
#include "D3DUtil.h"
#include "Mex2LoadReq.h"
#include <MeFoundation/MeLoopThreadMan.h>
#include <MeFoundation/MeLoopThreadProcedure.h>
#include "ModelLoadingThreadProc.h"
#include "navigation.h"
#include "MeFoundation/MeMemoryTracker.h"
//#include "MsgCutAndRebuild.h"
#include "GlobalDef.h"
#include "Me3d/MoreAction.h"
#include "ItemDetail.h"
#include "LotteryStatus.h"
#include "MiniMap.h"
#include "XmlStringLanguage.h"
#include "globalvars.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "Me3d/Engine/Engine.h"
#include "MeUi/UiPicture.h"
#include "MeUi/UiManager.h"
#include "MeUi/ControlIconDragManager.h"
#include "Billboard2D.h"
#include "wordparser.h"
#include <Iptypes.h>
#include <Iphlpapi.h>
#include "RollSystemBase.h"
#include "DumpInfo.h"
#include "ProcessCharInfo.h"
#include "ErrorLog.h"
#include "SortLuaScript.h"
#include "LGStatus.h"
//#include "MeConnector.h"
//#include "MeNetwork.h"
#include "TimeClock.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Engine/RendererDx.h"
#include "Logger.h"
#include "Me3d/Model/MtlAnim.h"
#include "MeAudio/MeAudio.h"
#include "Me3d/Platform.h"
#include "ShowScreenText.h"
#include "AckEnterWorldPackage.h"
#include "gamemain.h"
#include "ActionManager.h"
#include "CameraStuntManager.h"
#include "MotionBillBoard.h"
#include "Me3d/ShaderMgr.h"
#include "MeFont/MeFont.h"
#include "MultiThreadMexLoading.h"
#include "Me3d/skybox.h"
#include "Me3d/Md5Manager.h"
#include "application_config.h"
#include "chatcheck.h"
#include "MessageProcess.h"
#include "WealthProtect.h"
#include "PreventWallow.h"
#include "GivePresentLogic.h"
#include "Me3d\PostProcess\PostProcess.h"
#include "Me3d\PostProcess\PostProcessManager.h"
#include "Me3d\Shader.h"
#include "Me3d\ShaderManager.h"
#include "script_manager.h"
//#include "cipher/cipher_factory.h"
#include <sys/stat.h>
#include "jwsmtp/jwsmtp.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "wsRender.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "MeTerrain/STSkyBox.h"
#include "Font3DManager.h"
#include "ConsoleWindow.h"
#include "CrossMapPF.h"
#include "PathDirection.h"
#include "Dxsdk/ddraw.h"
#include "MiniDumper.h"
#include "meui/ExpressionManager.h"
#include "MeTerrain/FootPrint.h"
#include "ProgressBar3DManager.h"
#include "ChatMessageMgr.h"
#include "UserData.h"
#include "PetDefineConfig.h"
#include "packet_interface.h"
// /#include "Launcher/DataLauncher.h"
//#include "Launcher/IloadData.h"
#include "RegionMap.h"
#include "IntroductionManager.h"
#include "WSModelEffect.h"
#include "TimeEx.h"
#include "wsCamera.h"
#include "ModelConfig.h"
#include "TreasureBoxConfig.h"
#include "StarLevelUpConfig.h"
#include "ExpStage.h"
#include "LuckRewardConfig.h"
#include "AvatarSystemSetting.h"
#include "SystemConfig.h"
#include "RecipeConfig.h"
#include "ArmourElementsConfig.h"
// #include "event_timeable.h"
#include "color_config.h"
#include "tip_configure.h"
#include "shortcutkey_configure.h"
#include "softKeyboard_configure.h"
// #include "event_timeable_configure.h"
#include "ResourcePath.h"
#include "QuestData.h"
#include "TitleConfig.h"
#include "TradeCenterConfig.h"
#include "TradeCenterInfo.h"
#include "RandPropertyEvaluate.h"
#include "SplitItemConfig.h"
#include "SuitOperateConfig.h"
#include "OnLineRewardConfig.h"
#include "KillMonsterCountConfig.h"
#include "ItemComposeConfig.h"
#include "ExpActionConfig.h"
#include "FamilyConfig.h"
#include "ui/LotteryGameUI.h"
#include "ui/chat_particular.h"
#include "ui/chat_list.h"
#include "ui/SystemSetting.h"
#include "ui/SystemSettingUI.h"
// #include "ui/Event_more.h"
#include "ui/chat_list.h"				
#include "ui/pack.h"
#include "ui/UIStorage.h"
#include "ui/Select.h"
#include "ui/Login.h"
#include "ui/Create.h"
#include "ui/MessageBox.h"
#include "ui/InputBox.h"
#include "ui/SelectBox.h"
#include "ui/Progress.h"
#include "ui/ChatInfoBox.h"
#include "ui/FaceDlg1.h"
#include "ui/Shop.h"
#include "ui/Main.h"
#include "ui/Skill.h"
#include "ui/Property.h"
#include "ui/LoadMap.h"
#include "ui/Target.h"
#include "ui/ExitGame.h"
#include "GameUI/ExitTip.h"
//#include "ui/Guild.h"
#include "ui/Group.h"
#include "ui/NpcChatDialogBox.h"
#include "ui/MiniMapUI.h"
#include "ui/PrivateShop.h"
#include "ui/PlayerPrivateShop.h"
#include "ui/LuckGameUI.h"
#include "ui/Compound.h"
#include "ui/Bargaining.h"
#include "ui/Task.h"
#include "ui/EscDlg.h"
#include "ui/ActionUI.h"
#include "ui/tips.h"
#include "ui/target.h"
#include "ui/baseProperty.h"
#include "ui/rbtnMenu.h"
#include "ui/Group_Me.h"
#include "ui/GameSettingUI.h"
#include "ui/FriendDlg.h"
#include "ui/Rename.h"
#include "ui/topinfo.h"
// #include "ui/ChatSystem.h"
// #include "ui/FriRBMeun.h"
#include "ui/Group_StateUI.h"
#include "ui/Guild_Create.h"
#include "ui/AddMember.h"
#include "ui/exmain.h"
#include "ui/CodeCheck.h"
#include "ui/LoginCheck.h"
#include "ui/SelectAssignMode.h"
#include "ui/Pack_Ex.h"
#include "ui/AllNpcList.h"
#include "UI/customShortcutKey.h"
#include "ui/SoftKeyboard.h"
#include "ui/GroupPanel_NearPlayer.h"
#include "ui/ChatSet.h"
#include "ui/Task_Track.h"
#include "ui/Group_DeBuffUI.h"
#include "UI/SeekEquip.h"
#include "ui/BillBoard.h"
#include "Billboard.h"
#include "ui/AllNpcList.h"
#include "ui/Shopping_InputBox.h"
#include "ui/GameSetting.h"
#include "ChatHistory.h"
#include "Announce.h"
#include "ui/EditPrice.h"
#include "Create.h"
#include "ui/Pet.h"
#include "ui/BatchShop.h"
#include "ui/MainMenu.h"
#include "ui/SeekPet.h"
#include "ui/UiTitle.h"
//#include "ui/Alignment.h"
#include "ui/DemandItem.h"
#include "ui/ActivityList.h"
#include "ui/SkillProduce.h"
#include "ui/GameSettingMouse.h"
#include "ui/Speaker.h"
#include "ui/LoadSplash.h"
#include "ui/Decompound.h"
//#include "ui/WebAward.h"
#include "ui/TargetProgrss.h"
#include "ui/Team.h"
#include "ui/TutorialBox.h"
#include "GameUI/ChangeEquip.h"
#include "GameUI/PlayerRename.h"
#include "SuperPassword.h"
#include "SuperPasswordReset.h"
#include "SuperPasswordRegister.h"
#include "ui/PasswordProtect.h"
#include "GameUI/MailMain.h"
#include "ui/BullSystem.h"
#include "GameUI/AutoAttackSet.h"
#include "MoveStarUpgrade.h"
#include "StarMaterialUpgrade.h"
#include "Master.h"
#include "Action.h"
#include "IntensifyStar.h"
#include "DeleteCase.h"
#include "CountryInput.h"					//added by zhuomeng.hu		[8/27/2010]
#include "CountryBroadcast.h"				//added by ZhuoMeng.Hu		[8/30/2010]
#include "Me3d/Engine/MeRenderManager.h"
#include "Me3d/Engine/MeBitSorter.h"
#include "Me3d/Engine/MeShimmerCollector.h"
#include "Me3d/Engine/MeAlphaCollector.h"
#include "Common.h"
#include "CountryConfig.h"
#include "ItemDetailConfig.h"
#include "XinFaConfig.h"	//added by zilong. 2011-02-18
#include "UINoobTipManager.h"				//added by ZhuoMeng.Hu		[9/17/2010]
#include "RapidXml/MeRapidXml.h"
#include "Ui/InfoList.h"
#include "PetMore.h"
#include "ProduceLearn.h"
#include "AchieveConfig.h"
#include "ScreenInfoManager.h"
#include "Epic.h"
#include "GuildConfig.h"
#include "Search.h"
#include "GamePlay/FindBestEquip.h"
#include "GameUI/IconMgrBestEquip.h"
#include "ui/AddFriend.h"
#include "CountryFunction.h"
#include "Ui/FriendView.h"
#include "SoundConfig.h"
#include "PetStorage.h"
#include "ReclaimPriceInput.h"
#include "CampGuildBattleConfig.h"
#include "CampCountryBattleConfig.h"
#include "EquipEvolveConfig.h"
#include "ui/Sprite.h"
#include "ui/Editor.h"
#include "PetSettingConfig.h"
#include "SuAnimal.h"
#include "FirstCREATE.h"
#include "SuAnimalMore.h"
#include "ui/TaskDialog.h"
#include "ui/FamilyCreate.h"
#include "ui/FamilyTenet.h"
#include "ui/FamilyMoney.h"
#include "ui/FamilyMessageBox.h"
#include "ui/FamilyApply.h"
#include "TalismanConfig.h"
#include "ui/BasePropertyBGFrame.h"
#include "ui/TradeMoney.h"
#include "WeatherEventManager.h"

#include "SystemFamily.h"
#include "Talisman.h"

#include "OtherInfo.h"
#include "SelfInfo.h"
#include "SuAnimalCardList.h"
#include "GuildApply.h"
#include "SuAnimalCard.h"

#include "IntroductionManager.h"
#include "MovieManager.h"               //added by zhuomeng.hu		[2/24/2011]
#include "monsterStatusMgr.h"
#include "Lens.h"
#include "ScenePlay.h"
#include "Gut.h"
#include "SeeBasePropertyBGFrame.h"
#include "network.h"
#include "ItemHero.h"
#include "TPHJManger.h"
#include "NetWorkParameterDefine.h"
//#include "Kwamemap.h"
#include "PocketShop.h"
#include "GameUI/Kwamemap.h"
#include "ChangeCountryTip.h"
#include "MountStrengthenConfig.h"
#include "Ui/AskPresent.h"
#include "ChangeCountryConfig.h"
#include "TimeStringConfig.h"
#include "EquipScoreRatioConfig.h"
#include "CardIconConfig.h"
#include "CardAchieveConfig.h"
#include "SevenDays.h"
#include "GameUI/SelectChannel.h"
#include "SuitConfig.h"
#include "MonsterDefine.h"
#include "EffectCharConfig.h"
#include "RankTitleConfig.h"
#include "IntensifyEquipEffect.h"
#include "ui/QuestEntrust.h"
#include "CountryTitleConfig.h"
#include "HuntingQuestConfig.h"
#include "StallConfig.h"
#include "SoulConfig.h"

#include "ui/AddGuildGeneralBattle.h"
#include "ui/CountryBaseInfo.h"

#include "ThreeDayConfig.h"
#include "YuanBaoTotleConfig.h"
#include "MountMoveStarConfig.h"
#include "PetSpeakConfig.h"
#include "TextHyberOtherConfig.h"
//#include "HeroSoullConfig.h"
#include "CSAuthMessage.h"
//lyh NP
#ifdef NPGUARD
#include <NP/NPGameLib.h>
//#define  NO_GAMEGUARD
extern CNPGameLib *npgl = NULL;//GameName为.ini文件的名称
bool bAppExit = false;
char g_szHackMsg [256] = { 0 };
char  lpszMsg[256] = { 0 };
DWORD NpInit_dwResult = NPGAMEMON_SUCCESS;
#endif

//#ifdef _DEBUG
//#include "ConsoleWindow.h"
//#endif
static MeCollectorPtr   ms_spShimmerCollector = 0;
static MeCollectorPtr   ms_spAlphaCollector = 0;
static MeSorterPtr      ms_spBitSorter = 0;

INT CHeroGame::m_nSaveRoleID[eMaxSaveRoleID];


//#define PACKET_AUDIO_DATA   "..\\data\\Audio.data"
//#define PACKET_CONFIG_DATA   "..\\data\\Config.data"
//#define PACKET_AVATAR_DATA   "..\\data\\Avatar.data"
//#define PACKET_CHARACTER_DATA   "..\\data\\Character.data"
//#define PACKET_EFFECT_DATA   "..\\data\\Effect.data"
//#define PACKET_MAGIC_DATA   "..\\data\\Magic.data"
//#define PACKET_QUEST_DATA   "..\\data\\Quest.data"
//#define PACKET_SCENE_DATA   "..\\data\\sceneobject.data"
////#define PACKET_SHADER_DATA   "..\\data\\Shader.data"
//#define PACKET_TERRAIN_DATA   "..\\data\\Terrain.data"
//#define PACKET_TEXTURE_DATA   "..\\data\\Texture.data"`
//#define PACKET_UI_DATA   "..\\data\\Ui.data"
//#define PACKET_WORLD_DATA   "..\\data\\World.data"
//#define PACKET_CONFIG_CLIENT_DATA   "..\\data\\clientconfig.data"


#define PACKET_AUDIO_DATA   "Data0.tz"
#define PACKET_CONFIG_DATA   "Data1.tz"
#define PACKET_AVATAR_DATA   "Data2.tz"
#define PACKET_CHARACTER_DATA   "Data3.tz"
#define PACKET_EFFECT_DATA   "Data4.tz"
#define PACKET_MAGIC_DATA   "Data5.tz"
#define PACKET_QUEST_DATA   "Data6.tz"
#define PACKET_SCENE_DATA   "Data7.tz"
#define PACKET_TERRAIN_DATA   "Data8.tz"
#define PACKET_TEXTURE_DATA   "Data9.tz"
#define PACKET_UI_DATA   "Data10.tz"
#define PACKET_WORLD_DATA   "Data11.tz"
#define PACKET_CONFIG_CLIENT_DATA   "Data12.tz"


//extern bool g_DirectReadInPackage;
extern void SetTipColors( DWORD dwColor0, 
						 DWORD dwColor1,	
						 DWORD dwWhite, 
						 DWORD dwGrayed,
						 DWORD dwBlue,
						 DWORD dwGreen,
						 DWORD dwGold,
						 DWORD dwYellow,
						 DWORD dwRed);

extern FLOAT g_fCamerFOV;
extern BOOL	g_bTheRoleJumping; //主角是否起跳
extern BOOL g_bTheRoleJumpingCountermarch; //主角是否在向后跳
extern BOOL g_bTheRoleSlipJumping; //主角在下划跳跃

const char* g_pszVersion = "HEROOnline";

extern BOOL g_DynamicMapLoadThreadWillExit;
BOOL DynamicMapLoadThreadExit();

extern D3DXVECTOR3	g_vTheRoleTargetDir;
extern BOOL	g_bTheRoleMovingByDir;
extern BOOL g_bRenderRole;
extern BOOL g_bTheRoleCountermarch;

extern BOOL g_bAutoRunForward;
extern bool g_RenderTips = true;
//extern DWORD g_dwAutoRunWithMouseStartCheckTime; //开始判定一直跟着鼠标跑的时间

extern float g_fTheRoleDirCorrect;
extern int g_nRenderParticleEmittersLevel;
extern BOOL g_bLastFrameMovebyDir;

int g_nTargetPointEffectID = -1;
int g_nTargetPointEffectContainerID = -1;

int g_nPKFlagEffectID = -1;
int g_nPKFlagEffectContainerID = -1;

float g_fTheRoleRotateZCorrect = 0.0f; //主角的转向修整

BOOL g_bMultiThreadLoadingMex = TRUE; //多线程加载MEX

float g_fTheRoleSlipJumpingAngle = D3DX_PI/180*45.0f; //主角下滑的角度
float g_fTheRoleBBoxHeight = 0; //主角的BBox的高

BOOL g_bShowRoleAttackRange = FALSE; //显示主角攻击距离
float g_fAddRoleAttackRange = 0;

BOOL g_bMainToSelectUI = FALSE;
BOOL g_bMouseMoveMode = FALSE;	            //鼠标移动模式，智能鼠标

bool	g_bConnectSuccFlag = false;	//用户是否连接上LoginServer　标志
BOOL	g_bRoleMoveByLRButtonDown = FALSE;	// 人物按下鼠标右键后，是否同时按下鼠标左键来移动

// 玩家的职业
int g_nTheRoleProfession = -1;
float	g_PickedZFromMouse = WORLD_HEIGHT;
extern int g_nCharacterDBID;
extern int g_ChunkTextureDefaultOverlap ;

bool isShowDisconnetMsg = false;

// 关闭TrueTime 1
#define OFF_TRUETIME

CActionManager				g_ActionManager;			//游戏动作管理器
CCameraStuntManager			g_CameraStuntManager;		//摄象机特技管理器

int g_nKeyupGameAction[DIK_MEDIASELECT+1];
int g_nKeydownGameAction[DIK_MEDIASELECT+1];

BOOL g_bRoleRotatebyDir = FALSE;
BOOL g_bMouseLeave = FALSE;     // 鼠标是否离开窗口，移到输入法上需要记录鼠标状态
BOOL g_bGlobalDataLoaded = FALSE;    // 只加载一次的全局数据是否加载标记，挪到LoadMap里实现，包含任务，特效
BOOL g_bIsShowSceneAndPlayer = FALSE;       // 是否开始显示场景和人物
BOOL g_bCanUpdateQuest = TRUE;      // 接收到任务状态更新消息(MsgTellCharVar)时，是否需要更新任务状态
bool g_maploaded		= false;	//多线程载入地图完成,需要发给server

std::vector<int> g_vecPendingShowInfo;		// 等待进入游戏时，如果有系统消息，则先保存起来
extern int g_iShowJoinFightCountDown;

BOOL g_DynamicMapLoadThreadWillPause = TRUE;
void GetMACAddressString( std::string* pStrMacString );

float g_fZRotate = 0.6f;

extern unsigned int g_dwServerNumber = 0;

// 服务器用网络流量log
struct NetStreamLog
{
	NetStreamLog()
	{
		m_dwTotalSentByte = 0;
		m_dwMinSentByte = ULONG_MAX;
		m_dwMaxSentByte = 0;

		m_dwTotalReceivedByte = 0;
		m_dwMinReceivedByte = ULONG_MAX;
		m_dwMaxReceivedByte = 0;
	}
	void Reset()
	{
		m_dwStartTime = 0;
		m_dwEndTime = 0;
		m_dwMaxReceivedByte = 0;
		m_dwMaxSentByte = 0;
		m_dwMinReceivedByte = ULONG_MAX - 1;
		m_dwMinSentByte = ULONG_MAX - 1;
		m_dwTotalReceivedByte = 0;
		m_dwTotalSentByte = 0;
		m_dwSentBytePerSecond = 0;
		m_dwReceivedBytePerSecond = 0;
	}
	void Start()
	{
		m_dwStartTime = HQ_TimeGetTime();
	}
	void End()
	{
		m_dwEndTime = HQ_TimeGetTime();
	}
	void Caculate()
	{
		m_dwSentBytePerSecond = m_dwTotalSentByte / ( m_dwEndTime - m_dwStartTime );
		m_dwReceivedBytePerSecond = m_dwTotalReceivedByte / ( m_dwEndTime - m_dwStartTime );
	}
	DWORD m_dwStartTime;
	DWORD m_dwEndTime;
	// sent
	DWORD m_dwTotalSentByte;
	DWORD m_dwSentBytePerSecond;
	DWORD m_dwMinSentByte;
	DWORD m_dwMaxSentByte;

	// received
	DWORD m_dwTotalReceivedByte;
	DWORD m_dwReceivedBytePerSecond;
	DWORD m_dwMinReceivedByte;
	DWORD m_dwMaxReceivedByte;
};

static NetStreamLog g_NetStreamLog;

//////////////////////////////////////////////////////////////////////////
// MEX多线程加载
// void MexLoadingThread(void* p);
// void StartMexLoadingThread();
// void ProcessMexLoadingThread();
// void CloseMexLoadingThread();
extern HWND g_HelpHwnd;
extern HWND g_RegisterHwnd;
bool g_bFocusWindow = true;
BOOL IsActiveWindow()
{
	HWND hActiveWnd = GetActiveWindow();
	return (hActiveWnd != NULL &&(hActiveWnd == g_hWnd || hActiveWnd == g_HelpHwnd || hActiveWnd == g_RegisterHwnd ) && g_bFocusWindow);
}
struct STestMap
{
	bool bTestMap;
	char szTerrainFile[ 256 ];
	int  x,y;
}theTestMap = { false,"" };


void FlushRenderPic();
void RenderPic( int nTextureId, RECT& rc, DWORD dwColor );
BOOL DebugCommand( const char* pszCommand );
extern DWORD HQ_HQ_TimeGetTime();

int g_nWindowMode = 0;

extern CMyD3DApplication* g_pApp; 
extern HINSTANCE          g_hInst;
extern void SaveSurfaceAsBmp(	LPDIRECT3DDEVICE9 pd3dDevice, 
							 LPDIRECT3DSURFACE9 pBackBuffer,
							 char* pszFilename,
							 BYTE *pBuffer );

HWND	g_hIMPanel = NULL;
BOOL	g_bShowIMPanel = FALSE;
HWND	g_hhWnd = NULL;
extern void FlushBloodBarToScreen();
extern int PlayEffect( const char* pEffectName, CPlayer* pSrcPlayer = NULL, float fScale = 0 , DWORD dwFlyTime = 0, CPlayer* pDestPlayer = NULL, int nSlot = 0 ,bool bCalDist = true);
//extern bool CheckMapCanPk(CPlayer* pSrcPlayer,CPlayer* pTargetPlayer);

CHeroGame				theHeroGame;
CHeroGame* theApp =		&theHeroGame;

bool	g_bCloseApp =		false;
BOOL	g_bConnectDis = TRUE;

GAME_STATE		g_GameState;
//
BOOL			g_bRenderSkyBox = TRUE;

int					g_nLockPassivityTargetEffectID = -1;
int					g_nLockPassivityTargetEffectContainerID = -1;
int					g_nLockInitiativeTargetEffectID = -1;
int					g_nLockInitiativeTargetEffectContainerID = -1;
// aoe effect
bool				g_bShowAoeSelectEffect = false;
int					g_nAoePointEffectID = -1;
int					g_nAoePointEffectContainerID = -1;

int					g_nLockTargetEffectID = -1;
int					g_nLockTargetEffectContainerID = -1;

extern BOOL	g_bTheRoleAttackLockTarget;


BOOL	g_bMouseLButtonIsDown = FALSE;
BOOL	g_bMouseRButtonIsDown = FALSE;
BOOL    g_bMouseLButtonRotate = FALSE;          // 用左键按下旋转相机
BOOL    g_bMouseRButtonRotate = FALSE;          // 用右键按下旋转相机

LPDIRECT3DTEXTURE9 g_pGlowRenderToTexture = NULL;

// 可旋转
BOOL	g_bRotateEnable = FALSE;

extern float g_fMaleLookatPtHeight;
extern float g_fFemaleLookatPtHeight;

/////////////////////////
extern D3DXVECTOR3		g_vCurSelectNpcPos;			//当前选中的Npc位置
extern BOOL				g_bHaveSelectNpc;			//是否有选中的Npc

void GetNowTime(struct tm& nowtime);	// 获取当前时间

//鼠标的DirectInput
//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
LPDIRECTINPUT8       g_pDI    = NULL;         
LPDIRECTINPUTDEVICE8 g_pMouse = NULL;
LPDIRECTINPUTDEVICE8 g_pKeyboard = NULL;

BOOL	g_bRenderUI = TRUE;

// 帧数时间
DWORD g_dwLastFrameBeginTime = 0; // 上一帧开始的时间
DWORD g_dwLastFrameCostTime = 0; // 上一帧花费的时间
DWORD g_dwLastFrameRealCostTime = 0;    // 因为g_dwLastFrameCostTime会设置上帧花费时间最大为1000，所以需要g_dwLastFrameRealCostTime保存真实的上帧花费时间，用于ping值计算

float	g_fTheRoleRunningStep = 2.46f;// 按照18帧来播跑步动画，计算公式:动画帧数 / 30 * g_fTheRoleMovingRate
float	g_fTheRoleMovingRate = 4.1f;

#define WM_MOUSEWHEELUP 7864320
#define WM_MOUSEWHEELDOWN 4287102976

extern void	World2Screen( D3DXVECTOR3 vPos,int &x,int &y );

// debug
BOOL	g_bShowFps = FALSE;
BOOL	g_bDebugPos = FALSE;

BOOL	g_bFirstSightCamera = FALSE;
BOOL	g_bShowModelBBox = FALSE;
BOOL	g_bShowMouseTile = FALSE;
BOOL	g_bShowPlayer = TRUE;
int		g_nMiniMapSight = 128;
int		g_nMiniMapWindowSize = 128;

// 浏览的UI文件名
static std::string g_strViewerUIFilename;

NetStatistics g_Statistics;
BOOL g_bRenderFootPrint = TRUE;

extern BOOL g_b25DRoleMoveFollowMouse;
extern BOOL g_b25DMouseLButtonDownOnTerrain;
extern BOOL g_b25DRoleMoveFollowMouseFocusOnUI;
extern DWORD g_dw25DLButtonDownStartTime;
BOOL g_bBackToLogin = FALSE;    // 断开链接时，设置返回Login的全局变量
BOOL g_bIsShowDisconnect = FALSE;
BOOL g_bIsEnteringWorld = FALSE;    // 选人界面是否正在等待EnterWorld

extern bool FocusToNameEdit( char bIsTell,void *pData );

extern void	World2Screen( D3DXVECTOR3 vPos,int &x,int &y );
extern char* GetFullFileName(const char* filename);
void ErrorInfoLog( const char *string )
{
#ifdef _DEBUG //lyh屏蔽日志

	LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, string);

#endif // _DEBUG
}
short GetKeyboardInput( int iKey );
short GetKeyboardInputWin32( int iKey );
WPARAM GetWindowKeyFromDirectXKey(int iKey);

static bool NeedTradeViewer(ControlFrame* pFrame)
{
	return theTradeCenter.GetShortcutsItems(pFrame->GetData()->m_szID, 0);
}

//
// Splash screen, implemented with old-style Windows code so that it
// can be opened super-fast before initialization.
//
BOOL CALLBACK SplashDialogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( uMsg==WM_DESTROY )
		PostQuitMessage(0);
	if( uMsg == WM_QUIT )
	{
		PostQuitMessage(0);
	}
	if( uMsg == WM_PAINT )
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		RECT rc = { 0, 0, 100 ,100 };
		SetBkMode( hdc, TRANSPARENT );
		SetTextColor( hdc, RGB(255,0,255) );
		EndPaint(hWnd, &ps);
	}

	if( uMsg == WM_TIMER )
	{
		RECT rt;
		SetRect(&rt, 0, 0, 100, 100 );
		InvalidateRect( hWnd, &rt, TRUE);
	}


	return 0;
}
HWND    hWndSplash = NULL;
HBITMAP hBitmap    = NULL;
INT     BitmapX    = 0;
INT     BitmapY    = 0;
DWORD   ThreadId   = 0;
HANDLE  hThread    = 0;
// A bitmap.
class FWindowsBitmap
{
public:
	INT SizeX, SizeY, Keep;
	FWindowsBitmap( BOOL InKeep=0 )
		: hBitmap( NULL )
		, SizeX( 0 )
		, SizeY( 0 )
		, Keep( InKeep )
	{}
	~FWindowsBitmap()
	{
		if( hBitmap && !Keep )
			DeleteObject( hBitmap );
	}
	BOOL LoadFile( const char* Filename );
	HBITMAP GetBitmapHandle();
private:
	HBITMAP hBitmap;
	void operator=( FWindowsBitmap& ) {}
};

/*-----------------------------------------------------------------------------
FWindowsBitmap.
-----------------------------------------------------------------------------*/

HBITMAP LoadFileToBitmap( const char* Filename, INT& SizeX, INT& SizeY )
{
	guard(LoadFileToBitmap);
	BYTE *Bitmap = NULL;
	FILE* fp = fopen( Filename, "rb" );

	if( fp )
	{
		fseek( fp,0,SEEK_END );
		INT nSize = ftell( fp );
		fseek( fp, 0, SEEK_SET );
		Bitmap = MeDefaultNew BYTE [nSize];
		fread( Bitmap, nSize, 1, fp );
		fclose(fp);

		{
			HDC              hDC = GetDC(NULL);
			BITMAPFILEHEADER* FH = (BITMAPFILEHEADER*)&Bitmap[0];
			BITMAPINFO*       BM = (BITMAPINFO      *)(FH+1);
			BITMAPINFOHEADER* IH = (BITMAPINFOHEADER*)(FH+1);
			RGBQUAD*          RQ = (RGBQUAD         *)(IH+1);

			BYTE*             BY = (BYTE            *)((LPDWORD)(BM->bmiColors + BM->bmiHeader.biClrUsed) + 
				((BM->bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));

			//BYTE*             BY = (BYTE            *)(RQ+(1<<IH->biBitCount));
			SizeX                = IH->biWidth;
			SizeY                = IH->biHeight;
			HBITMAP      hBitmap = CreateDIBitmap( hDC, IH, CBM_INIT, BY, BM, DIB_RGB_COLORS );
			ReleaseDC( NULL, hDC );
			delete []Bitmap;

			return hBitmap;
		}
	}
	//if( appLoadFileToArray(Bitmap,Filename) )

	return NULL;
	unguard;
}

BOOL FWindowsBitmap::LoadFile( const char* Filename )
{
	if( hBitmap )
		DeleteObject( hBitmap );
	hBitmap = LoadFileToBitmap( Filename, SizeX, SizeY );
	return hBitmap!=NULL;
}

HBITMAP FWindowsBitmap::GetBitmapHandle()
{
	return hBitmap;
}

DWORD WINAPI ThreadProc( VOID* Parm )
{
	hWndSplash = CreateDialog( g_hInst, MAKEINTRESOURCEA(IDDIALOG_Splash), NULL, SplashDialogProc);
	if( hWndSplash )
	{
		HWND hWndLogo = GetDlgItem(hWndSplash,IDC_Logo);
		if( hWndLogo )
		{
			SetWindowPos(hWndSplash,HWND_TOPMOST,(GetSystemMetrics(SM_CXSCREEN)-BitmapX)/2,(GetSystemMetrics(SM_CYSCREEN)-BitmapY)/2,BitmapX,BitmapY,SWP_SHOWWINDOW);
			SetWindowPos(hWndSplash,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

			SendMessage( hWndLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap );
			SetWindowPos(hWndLogo,HWND_TOPMOST,
				(GetSystemMetrics(SM_CXSCREEN)-BitmapX)/2,
				(GetSystemMetrics(SM_CYSCREEN)-BitmapY)/2,BitmapX,BitmapY,
				SWP_SHOWWINDOW);

			ShowWindow( hWndSplash, SW_SHOW );
			UpdateWindow( hWndSplash );
			MSG Msg;
			while( GetMessage(&Msg,NULL,0,0) )
			{
				DispatchMessage(&Msg);
			}
		}
	}
	return 0;
}
void InitSplash( const TCHAR* Filename )
{

	STARTUPINFO si = {sizeof(si)};

	FWindowsBitmap Bitmap(1);
	if( Filename )
	{
		Bitmap.LoadFile(Filename);
		hBitmap = Bitmap.GetBitmapHandle();
		BitmapX = Bitmap.SizeX;
		BitmapY = Bitmap.SizeY;
	}
	hThread=CreateThread(NULL,0,&ThreadProc,NULL,0,&ThreadId);	
}

void ExitSplash()
{
	ShowWindow( hWndSplash,  SW_HIDE );
	if( ThreadId )
	{
		PostThreadMessage(ThreadId,WM_QUIT,0,0);
	}
}

//////////////////////////////////////////////////////////////////////////
struct FileDesc
{
	char	szPath[MAX_PATH];
	BOOL	bDir;
};
extern HANDLE g_hDynamicLoadMap;
extern HANDLE g_hNewPathRequest;

BOOL g_FindPathThreadPause = FALSE;
BOOL g_FindPathThreadWillPause = FALSE;

BOOL g_DynamicMapLoadThreadExit = TRUE;
BOOL g_DynamicMapLoadThreadPause = TRUE;
void PauseThread()
{
	if (!g_DynamicMapLoadThreadPause && !DynamicMapLoadThreadExit())
	{
		g_DynamicMapLoadThreadWillPause = TRUE;
		SetEvent(g_hDynamicLoadMap);
		while(!g_DynamicMapLoadThreadPause)
		{
			Sleep(1);
		}
	}
	if (!g_FindPathThreadPause && !g_FindPathThreadExit)
	{
		g_FindPathThreadWillPause = TRUE;
		SetEvent(g_hNewPathRequest);
		while(!g_FindPathThreadPause)
		{
			Sleep(1);
		}
	}
}
void UnpauseThread()
{
	g_DynamicMapLoadThreadPause = FALSE;
	g_FindPathThreadPause = FALSE;
}

BOOL GetFileListFromDirectory( const char* pszDirectory, std::vector<FileDesc>& files, const char** pszFilters, int nNumFilter )
{
	guardfunc;
	BOOL	bRC = TRUE;
	HANDLE					hFind = NULL;
	WIN32_FIND_DATA			FindFileData;

	std::vector<FileDesc> dirs;
	std::string strPathName = pszDirectory;
	std::string strPattern = strPathName+"*.*";
	hFind = ::FindFirstFile(strPattern.c_str(), &FindFileData);	// strat search	
	if(hFind == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	// filter off the system files and directories

	if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
	{

	}  
	// loop through to add all of them to our vector	
	while(bRC)
	{
		bRC = ::FindNextFile(hFind, &FindFileData);
		if(bRC)
		{
			if( FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				std::string strPath = strPathName+FindFileData.cFileName;
				if( FindFileData.cFileName[0] != '.' )
				{
					FileDesc desc;
					desc.bDir = TRUE;
					strcpy( desc.szPath, (strPath+"\\").c_str() );
					dirs.push_back( desc );
				}
			}
			// filter off the system files and directories
			if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
			{
				std::string strPath = strPathName+FindFileData.cFileName;
				//files.push_back( strPath );
				FileDesc desc;
				desc.bDir = FALSE;
				if( pszFilters )
				{
					//int nLen = strPath.length();
					strcpy( desc.szPath, strPath.c_str() );
					int nLen = strlen( desc.szPath );
					BOOL bMatch = FALSE;
					for( int nFilter = 0; nFilter < nNumFilter; nFilter++ )
					{
						if( stricmp( &desc.szPath[nLen - strlen( pszFilters[nFilter] )], pszFilters[nFilter] ) == 0 )
						{
							bMatch = TRUE;
							break;
						}
					}
					if( bMatch )
						files.push_back( desc );
				}
			}
		}   
		else
		{
			DWORD err = ::GetLastError();
			if(err !=  ERROR_NO_MORE_FILES)
			{
				return FALSE;
			}
		}
	} // end of while loop

	// close the search handle
	::FindClose(hFind);
	for( int nDir = 0; nDir < dirs.size(); nDir++ )
	{
		GetFileListFromDirectory( dirs[nDir].szPath, files, pszFilters, nNumFilter );
	}
	return TRUE;
	unguard;
}
INT_PTR CALLBACK IMPanelMsgProc( HWND hDlg,UINT uMsg,	WPARAM wParam, LPARAM lParam )
{
	guardfunc;
	HWND hEffectList = GetDlgItem( hDlg, IDC_LIST_EFFECT );
	char strDir[MAX_PATH] = {0};
	MeSprintf_s(strDir,sizeof(strDir)/sizeof(char) - 1, "%s\\data\\effect\\", SwGlobal::GetWorld()->GetAppDataCharDir());
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{

			char* pszFilters[] =
			{
				".effect"
			};
			std::vector<FileDesc> files;
			GetFileListFromDirectory( strDir, files, (const char**)pszFilters, 1 );
			for( int nFile = 0; nFile < files.size(); nFile++ )
			{
				ListBox_AddString( hEffectList, &files[nFile].szPath[strlen(strDir)] );
			}
		}
		break;
	case WM_CLOSE:
		EndDialog( hDlg, 0 );
		break;
	case WM_COMMAND:
		{
			switch( LOWORD( wParam ) )
			{
			case IDC_LIST_EFFECTLIST:
				{
					switch ( HIWORD( wParam ) )
					{
					case BN_HILITE:
						{
							int selected = ListBox_GetCurSel( hEffectList );
							if( selected != -1 )
							{
								char buffer[1024] = {};
								ListBox_GetText( hEffectList, selected, buffer );
								char szCommand[1024] = {};
								sprintf( szCommand, "casteffect %s", buffer );
								DebugCommand( szCommand );
							}
						}
						break;

					default:
						break;
					}
				}
				break;

			default:
				break;
			}
		}
		break;
	}

	return FALSE;

	unguard;
}
BOOL CreateBlpTexture( char* name, LPDIRECT3DDEVICE9 pd3dDevice, LPDIRECT3DTEXTURE9* ppTexture )
{
	guardfunc;
	return FALSE;
	unguard;
}
extern DWORD g_RoleMultRegTexgture;
void ClearGMain()
{
	guardfunc;
	g_RoleMultRegTexgture = FALSE;
// 	CUILayout::GetInstance()->Restore();
	thePlayerRole.OnExitTeam();
	thePlayerRole.m_nCompoundRateAdd = 0;
	if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
		theHeroGame.GetPlayerMgr()->GetMe()->clear();
	if( GetAdvancedMiniMap() )
		GetAdvancedMiniMap()->CancelNPCPF();
	if( s_CUI_ID_FRAME_ExitGame.IsVisable() )
	{
		s_CUI_ID_FRAME_ExitGame.UnLoadUI();
	}


	if( GetUIScriptMgr() )
	{
		GetUIScriptMgr()->clearUIs();
	}
	chatMessageManage.Clear();

    CountryFunction::Instance()->ClearCountryName();

	if( theHeroGame.GetPlayerMgr() )
		theHeroGame.GetPlayerMgr()->Destroy();

	unguard;
}


//----------------------------- 设置游戏状态 -----------------------------   
void ChangeGameState( const GAME_STATE gsCur, const GAME_STATE gsDes, bool bLoadUI/* = true*/ )
{
	guardfunc;
	switch(gsDes)
	{
	case G_PRODUCER:
		{
			switch(gsCur) 
			{
			case G_LOGIN:
				{
					guard(Login->Producer)
						unguard
				}
				break;
			}
		}
		break;
	case G_LOGIN:
		{
			theControlPictureManager.EnableLoadImage(false);
			switch(gsCur)
			{
			case G_SELECT:
				{
					guard(G_SELECT);
					s_CUI_ID_FRAME_Select.UnLoadUI();
					theHeroGame.GetPlayerMgr()->Destroy();
					s_CUI_ID_FRAME_LOGIN.LoadUI();
                    s_CUI_ID_FRAME_LOGIN.SetVisable( true );
					unguard;
				}
				break;
			case G_PRODUCER:
				{
// 					GMusic.StopMusic();
// 					GMusic.PlayMusic( gCfg.m_szLoginPageMusic, TRUE, TRUE );
// 					GSound.StopSound(  );
				}
				break;
			case G_MAIN:
				{
					PauseThread();
					ClearGMain();
					if( bLoadUI )	// 如果是SwitchGate，则无需加载Login UI
                    {
						s_CUI_ID_FRAME_LOGIN.LoadUI();
                        s_CUI_ID_FRAME_LOGIN.SetVisable( true );
                    }
					// 清除没用的模型
					if( GetMexResMgr() )
						GetMexResMgr()->RemoveUnusedModelWhenChangeMap();
					theHeroGame.ResetServerShutDownPara();
					s_CUI_Progress.UnLoadUI();
					s_CUI_ID_FRAME_TargetProgrss.UnLoadUI();
				}
				break;
            case G_LOADSPLASH:
                {
                    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      LoadSplash 结束", GetCurrentThreadId() );
                    s_CUI_ID_FRAME_LoadSplash.DestroyMultiThread();
                    s_CUI_ID_FRAME_LoadSplash.UnLoadUI();
                    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      Login 界面加载开始", GetCurrentThreadId() );
                    s_CUI_ID_FRAME_LOGIN.LoadUI();
                    s_CUI_ID_FRAME_LOGIN.SetVisable( true );
//                    s_CUI_ID_FRAME_LOGIN.SetLoginGroupVisable(false);//.m_GroupBroadcast.SetVisible(false);
//                     s_CUI_ID_FRAME_Antivir.LoadUI();
                    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      Login 界面加载结束", GetCurrentThreadId() );

					if( gCfg.m_bLocalVersion )
					{
						s_CUI_ID_FRAME_Select.LoadUI();
                        s_CUI_ID_FRAME_Select.SetVisable( true );
						theHeroGame.EnterWorldLocalVersion();					
						return;
					}
				}
				break;
			default:
				break;
			}
		}
		break;
		// 选择人物
	case G_SELECT:
		{
			switch(gsCur)
			{
			case G_LOGIN: // Login->Select
				{
					guard(Login->Select);
					s_CUI_ID_FRAME_LoadMap.LoadUI();
                    s_CUI_ID_FRAME_LoadMap.SetVisable( true );

					if( s_CUI_ID_FRAME_LoadMap.GetFrame())
						s_CUI_ID_FRAME_LoadMap.GetFrame()->SetVisable( false );
					s_CUI_ID_FRAME_Select.EnableMoveCamera(s_CUI_ID_FRAME_LOGIN.IsVisable());
                    s_CUI_ID_FRAME_LOGIN.SetVisable( false );
					s_CUI_ID_FRAME_LOGIN.UnLoadUI();
					s_CUI_ID_FRAME_Select.SetVisable(true);
					theUiManager.Compositor();
					//#endif
					//---
					unguard;
				}
				break;
			case G_CREATE: // Create->Select
				{
                    s_CUI_ID_FRAME_CREATE.SetVisable( false );
					s_CUI_ID_FRAME_CREATE.UnLoadUI();
					s_CUI_ID_FRAME_FirstCreate.SetVisable(false);
					s_CUI_ID_FRAME_FirstCreate.UnLoadUI();
					s_CUI_ID_FRAME_Select.LoadUI();	
					s_CUI_ID_FRAME_Select.SetVisable( true );
					s_CUI_ID_FRAME_Select.BackToSelect();
				}
				break;
			case G_MAIN:
				{
					PauseThread();

					s_CUI_ID_FRAME_Select.Release();
					ClearGMain();
					s_CUI_ID_FRAME_Select.LoadUI();	
					s_CUI_ID_FRAME_Select.SetVisable( true );	
					s_CUI_ID_FRAME_CodeCheck.SetVisable( false );
					s_CUI_ID_FRAME_LoginCheck.SetVisable( false );
					// 清除没用的模型
					if( GetMexResMgr() )
						GetMexResMgr()->RemoveUnusedModelWhenChangeMap();
					theHeroGame.ResetServerShutDownPara();
					s_CUI_Progress.UnLoadUI();
					s_CUI_ID_FRAME_TargetProgrss.UnLoadUI();
				}
				break;
			}
			break;
		}
		// 创建人物
	case G_CREATE:
		{
			switch( gsCur )
			{
			case G_SELECT: // Select->Create
				{
                    s_CUI_ID_FRAME_Select.SetVisable( false );
					s_CUI_ID_FRAME_Select.SetClearCharacter(false);
					s_CUI_ID_FRAME_Select.UnLoadUI();
                    s_CUI_ID_FRAME_DeleteCase.SetVisable( false );
                    s_CUI_ID_FRAME_DeleteCase.UnLoadUI();
                    //s_CUI_ID_FRAME_CREATE.LoadUI();
                    //s_CUI_ID_FRAME_CREATE.SetVisable( true );
					s_CUI_ID_FRAME_FirstCreate.LoadUI();
					s_CUI_ID_FRAME_FirstCreate.SetVisable(true);
				
				}
				break;
			case G_LOGIN: // Login->Select
				{
					guard(Login->Create);
					s_CUI_ID_FRAME_LoadMap.LoadUI();
					s_CUI_ID_FRAME_LoadMap.SetVisable( true );

					if( s_CUI_ID_FRAME_LoadMap.GetFrame())
						s_CUI_ID_FRAME_LoadMap.GetFrame()->SetVisable( false );
					s_CUI_ID_FRAME_LOGIN.SetVisable( false );
					s_CUI_ID_FRAME_LOGIN.UnLoadUI();
					s_CUI_ID_FRAME_FirstCreate.LoadUI();
					s_CUI_ID_FRAME_FirstCreate.SetVisable(true);
					theUiManager.Compositor();
				}
				break;
			}
			break;
		}
		// 主游戏
	case G_MAIN:
		g_RoleMultRegTexgture = TRUE;

		// 锁2.5D视角
		if( getwsCamera()->GetLock45DegreeCameraMode() )
			getwsCamera()->SetNeedUpdate45DegreeCamera( TRUE );

		theHeroGame.ResetServerShutDownPara();

		switch(gsCur)
		{
		case G_SELECT: // Select->Main		
			// 清除没用的模型
            LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      清除没用的模型", GetCurrentThreadId() );
			if( GetMexResMgr() )
				GetMexResMgr()->RemoveUnusedModelWhenChangeMap();
            s_CUI_ID_FRAME_Select.SetVisable( false );
            s_CUI_ID_FRAME_Select.UnLoadUI();
			break;
		}
		break;
	}
	theIconInfoMouseTip.Clear();

	g_GameState = gsDes;

	unguard;
}

void CHeroGame::ChangeGraphicsLevel(int level)
{

	if (level > 0)
	{
		graphics::ShaderManager::instance()->useShader(true);
		PostProcessManager::instance().enablePostProcess(true);
		GetEngine()->GetRenderer()->SetShaderLevel( 1 );

	}
	else
	{
		if(g_GameState != G_MAIN)  //lyh修改黑屏，在不是gamemain 的情况下关闭 ，回导致黑屏，所以此处不让关闭而是打开，ui做
		{
			graphics::ShaderManager::instance()->useShader(true);
			PostProcessManager::instance().enablePostProcess(true);
			GetEngine()->GetRenderer()->SetShaderLevel( 1 );
		}else
		{
			graphics::ShaderManager::instance()->useShader(false);
			PostProcessManager::instance().enablePostProcess(false);
			GetEngine()->GetRenderer()->SetShaderLevel( 0 );
		}

	}
}

//===================================================//

CHeroGame::CHeroGame()
{
	guardfunc;

	OutputDebugStr("CHeroGame");

	m_pQueriesInterlock = 0;
	m_bWindowed = TRUE;
	g_GameState = G_LOADSPLASH;//G_LOGIN;

	m_iLandID = -1;
	m_dwCreationWidth           = SCREEN_WIDTH;
	m_dwCreationHeight          = SCREEN_HEIGHT;

    m_pPlayerMgr = new CPlayerMgr;
	m_pDuelTips = new CDuelTips;
	m_pBattleFlag = new CBattleFlag;
	m_bZRotateStarted = false;
	m_bZRotateStartTime = 0;
	m_bXRotateStarted = false;
	m_bXRotateStartTime = 0;

	for( int i=0; i< eMaxSaveRoleID; i++ )
	{
        CHeroGame::m_nSaveRoleID[i] = -1;
	}

	m_ustSlowCPU = 1;
	m_checkTime = HQ_TimeGetTime();


	m_world = NULL;
	m_worldPick = NULL;
	m_swRender = new CWSRender;
	SwGlobal::SetRender(m_swRender);

	m_NetCostMax = 0;

	m_TotalFrame = 0;
	m_UIRenderTotal = 0;
	m_PlayerRenderTotal = 0;
	m_GrassRenderTotal = 0;
	m_ChunkRenderTotal = 0;
	m_LiquidRenderTotal = 0;
	m_ModelRenderTotal = 0;
	m_AllRenderTotal = 0;

	memset(m_LastKeyStates, 0, sizeof(BOOL)*256);
	memset(m_CurrKeyStates, 0, sizeof(BOOL)*256);
	memset(m_CurrKeyChangeList, 0, sizeof(KeyChangeData)*SAMPLEKEY_BUFFER_SIZE);
	m_nCurrKeyChangeNum = 0;

	m_nLastLandId = -1;
	isActive = false;
	m_fMusicVolume = 0.f;
	m_fSoundVolume = 0.f;

	m_bServerShutDown = false;
	m_fServerShutDownCoundDown = 0.f;
	m_serverAndLocalOffsetTime = 0;

	m_bGetMacAddr = false;
	m_strMacAddr = "";
	m_szUserName[0] = '\0';
	m_iDefaultMouseSpeed = 10;

	m_fPlayerHitMeEffectPlayerSpeedScale = 0.002f;
	m_dwPlayerHitMeEffectTotalTime = 4700;

	m_fLightHeight = 100.f;
	m_fProjHeight = 150.f;

	m_bStartCaculateNetStream = false;

	m_iGetPhyMemoryCD = 0;
	m_dwAvailPhyMemory = 0;

	m_eStateMouseType = MouseManager::Type_Max;
	                  
	m_PlayerMaxCost = 0; //角色最高耗时
	m_SceneUpdateMaxCost= 0; //场景更新最高耗时
	m_SceneRenderMaxCost= 0; 
	m_TerrainRenderMaxCost= 0;
	m_DoodadRenderMaxCost= 0; //植被最高耗时
	m_LiquidRenderMaxCost= 0; //流体最高耗时
	m_EffectRenderMaxCost= 0; //特效最高耗时
	m_UIRenderMaxCost= 0;     //ui最高耗时
	m_PostProcessMaxCost= 0; 
	//isShowDisconnetMsg = false;
	unguard;
}

void CHeroGame::LoadRoleSklProc()
{
	guardfunc;

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化角色骨骼开始", GetCurrentThreadId() );
    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Skeleton, 0.0f );
	MexResMgr::Record* pRecord = NULL;

	const int FEMALE_ANIMATION_NUMBER = 6;
	const char *FEMALE_ANIMATION_PATH[FEMALE_ANIMATION_NUMBER] =
	{
		"DATA\\CHARACTER\\Female\\Female.mex",
		"DATA\\CHARACTER\\Female\\FemaleJi.mex",
		"DATA\\CHARACTER\\Female\\FemaleDao.mex",
		"DATA\\CHARACTER\\Female\\FemaleQiang.mex",
		"DATA\\CHARACTER\\Female\\FemaleJian.mex",
		"DATA\\CHARACTER\\Female\\FemaleWu.mex",
		//"DATA\\CHARACTER\\Female\\FemaleFlag.mex"
	};	// 增加动画文件时同时修正FEMALE_ANIMATION_NUMBER
	const int MALE_ANIMATION_NUMBER = 6;
	const char *MALE_ANIMATION_PATH[MALE_ANIMATION_NUMBER] =
	{
		"DATA\\CHARACTER\\Male\\Male.mex",
		"DATA\\CHARACTER\\Male\\MaleJi.mex",
		"DATA\\CHARACTER\\Male\\MaleDao.mex",
		"DATA\\CHARACTER\\Male\\MaleQiang.mex",
		"DATA\\CHARACTER\\Male\\MaleJian.mex",
		"DATA\\CHARACTER\\Male\\MaleWu.mex",
		//"DATA\\CHARACTER\\Male\\MaleFlag.mex"
	};	// 增加动画文件时同时修正MALBow.mE_ANIMATION_NUMBER

	//加载人物通用动画
	int record_count = 0;

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d         女性角色骨骼读取开始", GetCurrentThreadId() );
	// 女性
	int nAnimTotalFrameCount = 0;
	int record_begin = record_count;	// 记录女性起始动画文件对应m_nSaveRoleID下标
	for( int i = 0; i < FEMALE_ANIMATION_NUMBER; i++ )
	{
		pRecord = GetMexResMgr()->CreateModel( FEMALE_ANIMATION_PATH[i], false );
		if( pRecord )
		{
			m_nSaveRoleID[record_count++] = pRecord->nId;
			nAnimTotalFrameCount += pRecord->GetCfgFrameCount();
		}
	}
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d         女性角色骨骼读取结束", GetCurrentThreadId() );

    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Skeleton, 0.25f );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d         女性角色骨骼合并开始", GetCurrentThreadId() );
	if( record_count - record_begin > 1 && nAnimTotalFrameCount > 0 )
	{
		// 有武器动画，合并动画数据
		if( GetMexResMgr()->ReallocMexAnimData( m_nSaveRoleID[record_begin], nAnimTotalFrameCount ) )
		{
			for( int i = record_begin + 1 ; i < record_count; i++ )
				GetMexResMgr()->CombineMexAnimData( m_nSaveRoleID[record_begin], m_nSaveRoleID[i] );
			GetMexResMgr()->BuildKeyFrameTimeList(m_nSaveRoleID[record_begin]);
		}
	}
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d         女性角色骨骼合并结束", GetCurrentThreadId() );

    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Skeleton, 0.5f );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d         男性角色骨骼读取开始", GetCurrentThreadId() );
	// 男性
	nAnimTotalFrameCount = 0;
	record_begin = record_count;	// 记录男性起始动画文件对应m_nSaveRoleID下标
	for( int i = 0; i < MALE_ANIMATION_NUMBER; i++ )
	{
		pRecord = GetMexResMgr()->CreateModel( MALE_ANIMATION_PATH[i], false );
		if( pRecord )
		{
			m_nSaveRoleID[record_count++] = pRecord->nId;
			nAnimTotalFrameCount += pRecord->GetCfgFrameCount();
		}
	}
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d         男性角色骨骼读取结束", GetCurrentThreadId() );

    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Skeleton, 0.75f );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d         男性角色骨骼合并开始", GetCurrentThreadId() );
	if( record_count - record_begin > 1 && nAnimTotalFrameCount > 0 )
	{
		// 有武器动画，合并动画数据
		if( GetMexResMgr()->ReallocMexAnimData( m_nSaveRoleID[record_begin], nAnimTotalFrameCount ) )
		{
			for( int i = record_begin + 1 ; i< record_count; i++ )
			{
				bool bSucc = GetMexResMgr()->CombineMexAnimData( m_nSaveRoleID[record_begin], m_nSaveRoleID[i] );
				LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "合并mex动画信息: %s", bSucc ? "成功" : "失败");
			}
			GetMexResMgr()->BuildKeyFrameTimeList(m_nSaveRoleID[record_begin]);
		}
	}
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d         男性角色骨骼合并结束", GetCurrentThreadId() );

// #if LOAD_COST_TIME_DEBUG
//     nThisTimeRecord = HQ_TimeGetTime();
//     MeSprintf_s( cOutputString, 2048, "\nInitRoleSkl:%d\n", nThisTimeRecord - nLastTimeRecord );
//     nLastTimeRecord = nThisTimeRecord;
//     OutputDebugStr(cOutputString);
// #endif

    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Skeleton, 1.0f );
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化角色骨骼结束", GetCurrentThreadId() );

	unguard;
}

void CHeroGame::UnLoadRoleSkl()
{
	guardfunc;

	for( int i=0; i< eMaxSaveRoleID; i++ )
	{
        if( CHeroGame::m_nSaveRoleID[i] != -1 )
		{
            GetMexResMgr()->DestroyModel( CHeroGame::m_nSaveRoleID[i] );
		}
	}

	unguard;
}

CHeroGame::~CHeroGame()
{
	guardfunc;
	unguard;
}
VOID DestorySpecualrTex();
HRESULT CHeroGame::DeleteDeviceObjects()
{
	guardfunc;

	// UI Viewer不清空资源！
	if (gCfg.m_bUiViewer)
	{
		return S_OK;
	}

	delete m_pQueriesInterlock;
	m_pQueriesInterlock = 0;

	Font3DManager::Instance()->Destroy();
	Font3DManager::Shutdown();

	BillboardManager<Billboard2D>::Instance()->Destroy();

	// added, jiayi, [2010/1/5]
	RollSystemStatusMan<RST_LuckyGame>::Destroy();
	RollSystemStatusMan<RST_Lottery>::Destroy();

	// add [5/20/2008 whu]
	try
	{
		graphics::ShaderManager::instance()->shutdown();
		delete graphics::ShaderManager::instance();

		PostProcessManager::instance().shutdown();
		delete PostProcessManager::instancePtr();
	}
	catch ( const std::exception& e )
	{
		OutputDebugString( e.what() );
	}

	if ( _pNavigation )
	{
		delete _pNavigation;
		_pNavigation = NULL;
	}

	UnLoadRoleSkl();

	if( g_pGlowRenderToTexture )
	{
		g_pGlowRenderToTexture->Release();
		g_pGlowRenderToTexture = NULL;
	}
	thePlayerRole.m_doll.Destroy();
	ClearGMain();
    s_CUI_ID_FRAME_LOGIN.SetVisable( false );
	s_CUI_ID_FRAME_LOGIN.UnLoadUI();
	//s_CUI_ID_FRAME_GameSetup.UnLoadUI();
	s_CUI_ID_FRAME_MessageBox.UnLoadUI();
	s_CUI_ID_FRAME_CodeCheck.UnLoadUI();
	s_CUI_ID_FRAME_LoginCheck.UnLoadUI();
	s_CUI_ID_FRAME_Tips.UnLoadUI();
	//s_CUI_ID_FRAME_BaseProperty.DestroyAnimCtrl();
	s_CUI_ID_FRAME_BaseProperty.UnLoadUI();
	s_CUI_ID_FRAME_BasePropertyBGFrame.UnLoadUI();
	s_CUI_ID_FRAME_Team.DestroyAnimCtrl();
	//s_CUI_ID_FRAME_SeekEqup.Destory();
	s_CUI_ID_FRAME_Group_Me.Destory();
	s_CUI_ID_FRAME_Group_Me.UnLoadUI();

	chatMessageManage.Reset();
	CUIMgr::Instance()->Destory();
	theUiManager.Destroy();


	ProgressBar3DManager::Shutdown();
	DestoryAudio();

	// added, jiayi, [2010/6/18]
	MeRenderManager::Instance()->SetSorter( NULL );	
	ms_spShimmerCollector = 0;
	ms_spAlphaCollector = 0;
	ms_spBitSorter = 0;

	if( g_pFlyTextEffect )
	{
		delete g_pFlyTextEffect;
		g_pFlyTextEffect = NULL;
	}

	if(g_pPrintTextEffect)//lyh++feixingwenzi
	{
		delete g_pPrintTextEffect;
		g_pPrintTextEffect = NULL;
	}

	FreeDirectInput();

	if( m_pPlayerMgr )
	{
		m_pPlayerMgr->ClearMustData();

		delete m_pPlayerMgr;
		m_pPlayerMgr = NULL;
	}

	if( m_pDuelTips )
	{
		delete m_pDuelTips;
		m_pDuelTips = NULL;
	}
	if( m_pBattleFlag )
	{
		delete m_pBattleFlag;
		m_pBattleFlag = NULL;
	}

	MeRenderManager::Release();
	GlobalTexture::UnLoad();
	GetEffectMgr()->Destroy();
	for( int i = 0; i < eCommonEffectTextureMax; i++ )
	{
		int nTextureID = GetMe3dConfig()->m_nCommonEffectTextureIDs[i];
		if( nTextureID  != -1 )
		{
			GetEngine()->GetTextureManager()->UnRegisterTexture( nTextureID );
			GetMe3dConfig()->m_nCommonEffectTextureIDs[i] = -1;
		}
	}
	m_world->Destroy();

	MexInstanceMan::GlobalDestroy();
	//析构天空盒
	GetSTSkyBox()->Release();
	SAFE_DELETE( m_worldPick );
	SAFE_DELETE( m_world );
	SAFE_DELETE( m_swRender );
	SAFE_DELETE(g_pFlyTextEffect);
	GetAdvancedMiniMap()->Destroy();
	for( int i = 0; i < GlobalTexture::eMaxTexture; i++ )
	{
		if( GlobalTexture::GetTexture( (GlobalTexture::enumTexture)i ) != -1 )
			GetEngine()->GetTextureManager()->UnRegisterTexture( GlobalTexture::GetTexture( (GlobalTexture::enumTexture)i ) );
	}

	DestorySpecualrTex();

// 	GetUIScriptMgr()->clearUIDatas();
	theControlPictureManager.Release();
	theUiManager.Destroy();

	//  [1/5/2011 zhangjiayi]
	CFootPrintMgr::Instance()->clear();

	GetMexResMgr()->Destroy();
	GetEngine()->GetTextureManager()->CloseTextureLoadingThread();

	//CloseMexLoadingThread();
	MeLoopThreadMan::Instance()->CloseThreads();

	// 删除字体
	FontSystem::DestroyFontManager();

	if( GetEngine() )
	{
		GetEngine()->Release();
		SetEngine(NULL);
	}

	s_CUI_ID_FRAME_MAIN.setHelpWithHtmlExit();


	CHRRenderSurface::GlobalDestroy();

	//free ddraw
	if( m_pDDobject )
		m_pDDobject->Release();
	m_pDDobject = NULL;
	if( m_ddrawLib )
		FreeLibrary( m_ddrawLib );
	m_ddrawLib = NULL;

	GameSetting::Instance()->Destroy();
	SystemSetting::Instance()->Destroy();
	CUserData::Instance()->Destroy();
	WeatherEventManager::Instance()->DestoryWeather();
// 	if (Cipher::g_Encoder)
// 	{
// 		delete Cipher::g_Encoder;
// 	}
// 	if (Cipher::g_Decoder)
// 	{
// 		delete Cipher::g_Decoder;
// 	}

	// 由于每个单件中又对别的类有依赖（比如engine），所以这个
	// 机制还很不完善，需要对所有单件类型进行顺序或者是依赖的管理，
	// 并统一使用这个来管理。目前移动到这里，为了解决单件中引用下面用到的
	// 对象。
	CSingletonBase::ReleaseAll();

	return S_OK;
	unguard;
}

//exter
HRESULT	CHeroGame::OneTimeSceneInit()
{
	guardfunc;
	char szPath[MAX_PATH] = {0};

	BOOL bOK = FALSE;

	GetMe3dConfig()->m_bUseSkinMesh = gCfg.m_bUseSkinMeshShader;
	InitCommonControls();
	//
	getwsCamera()->SetMeCamera( Config::GetCamera() );
	// 改成右手系
	getwsCamera()->GetMeCamera()->SetLeftHand(false);
	//
	m_bWindowed = TRUE;

	return S_OK;
	unguard;

}

void InitCharInfo(MsgAckEnterWorld &enterworld)
{
	guardfunc;
	int DefBoyDress[2] = {
		11100,	// 缺省
		11100,	// 缺省
	};
	int DefGirlDress[2] = {
		24000,	// 缺省
		24000,	// 缺省
	};
	int DefBoyFace[3] = {
		2950,		// 缺省男生脸部编号
		2950,		// 缺省男生脸部编号
		2950,		// 缺省男生脸部编号
	};
	int DefGirlFace[3] = {
		2980,		// 缺省女生脸部编号
		2981,		// 缺省女生脸部编号
		2982,		// 缺省女生脸部编号
	};
	int DefBoyHair[9] = {
		2800,
		2800,
		2800,
		2800,
		2800,
		2800,
		2800,
		2800,
		2800,
	};
	int DefGirlHair[9] = {
		2900,
		2901,
		2902,
		2903,
		2904,
		2905,
		2906,
		2907,
		2908,
	};
	const BYTE defSettingHairColorRGB[12][3] =
	{
		220,15,20, //        	红色:
		10,50,170, //		  	蓝色:
		40,180,190,//		  	青色:
		170,40,210,//		  	紫色:
		250,220,40,//		  	黄色:
		255,120,0, //		  	橙色:
		40,150,10, //		  	绿色:
		255,110,140,//		    粉红色:
		130,150,155,//		  	灰色:
		0,100,255,	//	    亮蓝色:
		0,90,60,	//		    暗绿色:
		120,45,0,	//	  	棕色:
	};

	MsgCreateHeroChar createchar;
	strcpy( createchar.create.szCharacterName, theXmlString.GetString(eText_StringSingleName) );
	createchar.create.ucHairColorIndex = 0;
	createchar.create.ucHairModelIndex = 0;
    createchar.create.ucFaceIndex = 0;
	createchar.create.ucHeadPic = 0;
	createchar.create.ucModelIndex = 0;
	createchar.create.usProfession = 1;
	createchar.fModelPercent = 1.f;
	//createchar.create.byYear = 1990;
	createchar.create.byMonth = 1;
	createchar.create.byDay = 1;

	MsgCreateHeroChar *pmsgCreateChar = & createchar;

	//参数检查	
    MsgCreateHeroChar::SCreateData* pCreate = &pmsgCreateChar->create;

	//性别
	switch( pCreate->ucSex )
	{
	case Sex_Male:
	case Sex_Female:
		break;
	default:
		pCreate->ucSex = Sex_Male;
	}

	pCreate->ucSex = gCfg.m_nLocalRoleSex;
	pCreate->ucHairModelIndex = 1;

	pCreate->usProfession = gCfg.m_nLocalRoleProfession;

	//TODO 以后将由客户端填写基本数值
	SCharBaseInfo  blobBaseInfo;	
	SCharOtherData blobOtherData;
	SCharVisual    visual;

	memset( &blobBaseInfo,0,sizeof(blobBaseInfo) );
	memset( &blobOtherData,0,sizeof(blobOtherData) );
	memset( &visual,0,sizeof(SCharVisual) );

	blobBaseInfo.liveinfo.nHp			= 200;
	blobBaseInfo.liveinfo.nMp			= 100;
	blobBaseInfo.aptotic.ucCountry			= 2;
	blobBaseInfo.aptotic.usProfession		= 2;

	int iLoop;
	for( iLoop = 0 ; iLoop < EBaseAttr_MaxSize ; iLoop ++ )
	{
		blobBaseInfo.baseProperty.baseAttr.baseAttrValue[iLoop].base = 5;
	}
	blobBaseInfo.liveinfo.dwExp = 0;

	for( iLoop = 0 ; iLoop < EEquipPartType_MaxEquitPart ; iLoop ++ )
	{
		visual.GetVisualArray()[ iLoop ].itembaseinfo.ustItemID = InvalidLogicNumber;
	}
	//设置出生点
	blobOtherData.sBornPos.dwMapID = 0;
	//
	blobOtherData.pos.dwMapID = 0;

	if( theTestMap.bTestMap )
	{
		blobOtherData.pos.stX = theTestMap.x;
		blobOtherData.pos.stY = theTestMap.y;

	}

	//技能清空
	for( iLoop = 0 ; iLoop < More_iMaxSkillKnown ; iLoop ++ )
	{
		blobOtherData.skills.skill[iLoop].ustSkillID = InvalidLogicNumber;
	}

	//热键背包清空
	for( iLoop = 0 ; iLoop < More_iHotkey ; iLoop ++ )
	{		
		blobOtherData.hotkeys.itemHotKey[iLoop].ShortCut.BagIndex = ErrorUnsignedShortID;
		blobOtherData.hotkeys.itemHotKey[iLoop].ShortCut.BagType = BagTypeMax;
	}

	if (pCreate->ucModelIndex < 0)
		pCreate->ucModelIndex =0;
	if (pCreate->ucModelIndex >= 2)
		pCreate->ucModelIndex = 1;
	if (pCreate->ucHairModelIndex < 0)
		pCreate->ucHairModelIndex = 0;
	if (pCreate->ucHairModelIndex >= 9)
		pCreate->ucHairModelIndex = 8;
	if (pCreate->ucHairColorIndex < 0)
		pCreate->ucHairColorIndex = 0;
	if (pCreate->ucHairColorIndex >= 12)
		pCreate->ucHairColorIndex = 11;
	if (pCreate->ucFaceIndex < 0)
		pCreate->ucFaceIndex = 0;
	if (pCreate->ucFaceIndex >= 3)
		pCreate->ucFaceIndex = 1;

	if(pCreate->byMonth > 12 || pCreate->byMonth <= 0)
		pCreate->byMonth = 1;
	if(pCreate->byDay > 31 || pCreate->byDay <= 0)
		pCreate->byDay = 1;

	//
	blobBaseInfo.aptotic.ucSex			= pCreate->ucSex;
	blobBaseInfo.aptotic.ucHeadPic		= pCreate->ucHeadPic;
	blobBaseInfo.aptotic.usProfession	= pCreate->usProfession;
	//blobBaseInfo.aptotic.byYear = pCreate->byYear;
	blobBaseInfo.aptotic.byMonth = pCreate->byMonth;
	blobBaseInfo.aptotic.byDay = pCreate->byDay;
	blobBaseInfo.baseProperty.fightAttr.moveSpeed.final = 1.0f;
	blobBaseInfo.baseProperty.fightAttr.moveSpeed.base = 1.0f;
	enterworld.charinfo.baseinfo.aptotic.usProfession = 1;
	enterworld.charinfo.baseinfo = blobBaseInfo;
	enterworld.charinfo.otherdataclient = blobOtherData;
	enterworld.charinfo.baseinfo.liveinfo.ustLevel = 1;
	enterworld.charinfo.baseinfo.liveinfo.dwMoney = 100;
	enterworld.charinfo.baseinfo.baseProperty.fightAttr.moveSpeed.final = g_fTheRoleMovingRate;
	/*enterworld.charinfo.visual.nHairColorIndex = 1;*/
	unguard;
}

static short UI_RegisterTexture(const char *name, 
								BOOL bWarning, bool bUseBlp ) 
{
	guardfunc;

	short shID = GetEngine()->GetTextureManager()->RegisterTexture( name, false ,TRUE, TRUE );
	return shID;
	unguard;
}

// static short UI_RegisterTextureFromFileMem(const char *name, void* pSrcData, unsigned int nLength,
// 										   BOOL bWarning, bool bUseBlp ) 
// {
// 	guardfunc;
// 
// 	short shID = GetEngine()->GetTextureManager()->RegisterTextureFromFileMem( name, pSrcData, nLength, false, false, false );
// 	return shID;
// 	unguard;
// }

static void UI_UnRegisterTexture( short ID )
{
	guardfunc;
	GetEngine()->GetTextureManager()->UnRegisterTexture( ID );
	unguard;
}

void InitSpecularTex();

void HookClient()
{
	guardfunc;
	unguard;
}

//////////////////////////////////////////////////////////////////////////

bool FPlaySound( const char* szName, D3DXVECTOR3* vPos,bool bLoop )
{
	GSound.PlaySound( szName,bLoop, vPos );
	return true;
}

extern int RetrieveFileFromInternet(CHAR* pHttpAddress,CHAR* pFileFullPath);

HWND _CreateHelpWindow()
{
	return theHeroGame.CreateHelpWindow();
}

BOOL DynamicMapLoadThreadExit()
{
	return g_DynamicMapLoadThreadExit;
}
bool g_DynamicMapLoadOpenEvent = false;
void DynamicLoadMapResourceThreadProc( void* lpParam )
{
	g_DynamicMapLoadThreadExit = FALSE;
	g_DynamicMapLoadThreadPause = FALSE;
	g_DynamicMapLoadThreadWillPause = FALSE;
	
	while( !g_DynamicMapLoadThreadWillExit )
	{
		WaitForSingleObject(g_hDynamicLoadMap,INFINITE);
		if (g_DynamicMapLoadThreadWillPause)
		{
			g_DynamicMapLoadThreadPause = TRUE;
			g_DynamicMapLoadThreadWillPause = FALSE;
		}
		if(!g_DynamicMapLoadThreadPause)
		{
			CWorldTile* pTile = CURRENTTILE;
			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
			if( pMe )
			{
				// 			if(g_DynamicMapLoadOpenEvent || pMe->IsMoving() )
				{
					float fx,fy;
					pMe->GetPos(&fx,&fy,NULL);
					pTile->SetRolePosition(fx,fy);
					pTile->RefreshChunkLoadLevel(SwGlobal::GetRender()->GetFogProperty()->fFogFar,false);

				}
			}
		}
// 		if(g_GameState != G_MAIN)
// 		{
// 			Sleep( 10 );
// 			continue;
// 		}
// 		if(g_DynamicMapLoadThreadPause)
// 		{
// 			Sleep( 10 );
// 			continue;
// 		}

		
	}
	// 这个线程结束了
	g_DynamicMapLoadThreadExit = TRUE;
	return ;

}

extern void FindPathThreadProc( void* lpParam );

#ifdef _DEBUG
//#define LOAD_COST_TIME_DEBUG 1
#else
#define LOAD_COST_TIME_DEBUG 0
#endif //_DEBUG

extern int g_MainThreadId;
HRESULT	CHeroGame::InitDeviceObjects()
{
	guardfunc;
	theControlPictureManager.EnableLoadImage(false);

	g_MainThreadId = GetCurrentThreadId();

	float fScale = (float)SCREEN_HEIGHT/768.0f;
	if ( fScale > 1.0f )
		fScale = 1.0f;
	ControlObject::SetUIScale(1);
	ControlObject::SetFontScale( /*1*/ fScale );
	ControlObject::SetAdjustSCALE( fScale );


	HookClient();

	GetPlatform()->Init();	
	InitAudioSystem( g_hWnd );

	g_ChunkTextureDefaultOverlap = 4;
    SetEngine( new CEngineInstance );
    GetEngine()->GetRenderer()->SetDevice( m_pd3dDevice );
    GetEngine()->GetTextureManager()->StartTextureLoadingThread();
    GetEngine()->UseAbstractPath(FALSE);	
	GetEngine()->UseTextureMultiThreadLoading( FALSE );
	GetEngine()->SetEffectMirror(FALSE);	// 特效不要镜像
	graphics::ShaderManager::instance()->initialize( m_pd3dDevice );	

	// skeleton shader
	bool bSkeleton = (bool)SystemSetting::Instance()->GetLevel( 
		SystemSetting::eSSC_SKELETON );//是否骨骼shader
	// added, [8/17/2010 zhangjiayi]	
	if( SystemSetting::Instance()->IsLowLevelCard() || !bSkeleton )
		graphics::ShaderManager::instance()->enableSkeletonShader( false );

	// added, [9/21/2010 zhangjiayi]
	SwGlobal::Initialize();
// 
// 	// temp code - jiayi
// 	graphics::ShaderManager::instance()->enableSkeletonShader( false );
	graphics::ShaderManager::instance()->enableSkeletonShader( false );


	CHRRenderSurface::GlobalInitialize();

	// added, jiayi, [2010/7/29]        

// 	HANDLE pHand = NULL;

	//创建地图动态加载线程
// 	pHand = CreateThread( NULL, 0,
// 		DynamicLoadMapResourceThreadProc, NULL,
// 		0, NULL );
	g_hDynamicLoadMap = CreateEvent(NULL,false,false,NULL);
	_beginthread( DynamicLoadMapResourceThreadProc, NULL, NULL );
// #ifdef _DEBUG
// 	if(pHand)
// 	{
// 		//CloseHandle(pHand);
// 		pHand = NULL;
// 	}
// #endif

	g_hNewPathRequest = CreateEvent(NULL,false,false,NULL);
	//创建自动寻路线程
// 	pHand = CreateThread( NULL, 0,
// 		FindPathThreadProc, NULL,
// 		0, NULL );
	_beginthread( FindPathThreadProc, NULL, NULL );
// #ifdef _DEBUG
// 	if(pHand)
// 	{
// 		//CloseHandle(pHand);
// 		pHand = NULL;
// 	}
// 
// #endif


	// UpdateFarFog会更新渲染状态，要放在GetEngine()->GetRenderer()->SetDevice之后执行
	if( GetPlatform()->GetMemoryLvl() == eMemory_Low )
	{
		SwGlobal::GetRender()->UpdateFarFog( 80 );
	}
 
	//
	// post process.
	//
	// commented out, jiayi, [2010/6/1]
	// 去掉try-catch,尽早暴露问题
	//  try
	{
		char strName[MAX_PATH] = {0};
		MeSprintf_s(strName,sizeof(strName)/sizeof(char) - 1 ,"%s\\DATA\\SHADER\\PostProcess\\Quad.fxo", SwGlobal::GetWorld()->GetAppDataCharDir());
		PostProcessManager::instance().initialize( m_pd3dDevice, strName );

		MeSprintf_s(strName,sizeof(strName)/sizeof(char) - 1, "%s\\DATA\\SHADER\\PostProcess", SwGlobal::GetWorld()->GetAppDataCharDir());

		if( !SystemSetting::Instance()->IsLowLevelCard() )
		{
			PostProcessManager::instance().enablePostProcess(true); 
 
 
           //hdr effect
			HdrPostProcessEffect *hdrPost = MeNew HdrPostProcessEffect("Hdr");
			hdrPost->create(m_pd3dDevice, strName);
			hdrPost->enable(false);
			PostProcessManager::instance().addPostProcessEffect(hdrPost); 


			BloomPostProcessEffect* bloomPost = MeNew BloomPostProcessEffect( "Bloom" );		
			bloomPost->create( m_pd3dDevice, strName );
			bloomPost->enable( true );
			PostProcessManager::instance().addPostProcessEffect( bloomPost );
			

			/*
			// 2.5D用不到
			GlowPostProcessEffect* glowPost = MeNew GlowPostProcessEffect( "Glow" );		
			glowPost->create( m_pd3dDevice, strName );
			glowPost->enable( true );
			PostProcessManager::instance().addPostProcessEffect( glowPost );

			LightShaftProcessEffect* lightShaftPost = MeNew LightShaftProcessEffect( "LightShaft" );
			lightShaftPost->create( m_pd3dDevice, strName );
			lightShaftPost->enable( true );
			PostProcessManager::instance().addPostProcessEffect( lightShaftPost );

			ShadowBlurPostProcessEffect* shadowBlurPost = MeNew ShadowBlurPostProcessEffect( "ShadowBlur" );		
			shadowBlurPost->create( m_pd3dDevice, strName );
			shadowBlurPost->enable( true );
			PostProcessManager::instance().addPostProcessEffect( shadowBlurPost );
			*/
		}
	}
	//     catch ( const std::exception& e )
	//     {
	//         OutputDebugString( e.what() );
	//     }

	static bool s_bNewFont = true;
	FontSystem::InitFontManager( s_bNewFont );
	static float s_ftscale = 1.2f;
	FontSystem::InitAllFontScale( gCfg.m_fUIFontScale );
	Font3DManager::Initialize(m_pd3dDevice);

	// added, [10/18/2010 zhangjiayi]
	BillboardManager<Billboard2D>::Instance()->Initialize( m_pd3dDevice );

	// 初始化字体
	FontSystem::CreateDevice( m_pd3dDevice );
	FontSystem::CreateFont( gCfg.m_szDefaultFont, gCfg.m_nDefaultFontSize );

	SetTipColors(	GetSystemConfig()->m_dwTipColor0, 
		GetSystemConfig()->m_dwTipColor1,
		GetSystemConfig()->m_dwWhite,
		GetSystemConfig()->m_dwGrayed,
		GetSystemConfig()->m_dwBlue,
		GetSystemConfig()->m_dwGreen,
		GetSystemConfig()->m_dwGold,
		GetSystemConfig()->m_dwYellow,
		GetSystemConfig()->m_dwRed	);

	theUiManager.InitDeviceObjects(	UI_RegisterTexture,
// 		UI_RegisterTextureFromFileMem,
		UI_UnRegisterTexture,
		CBaseGraphics::BltTexture,
		CBaseGraphics::DrawRect2D,
		CBaseGraphics::FillRect2D,
		CBaseGraphics::DrawProgressRect );


	theUiManager.SetPlaySoundFun( FPlaySound );
	UiManager::m_strButtonClickSound	= CWorld::GetAppDataCharDir();
	UiManager::m_strMoveOnSound		= CWorld::GetAppDataCharDir();
	UiManager::m_strCheckBoxSound		= CWorld::GetAppDataCharDir();
	UiManager::m_strIconDragSound		= CWorld::GetAppDataCharDir();
	UiManager::m_strListSound			= CWorld::GetAppDataCharDir();
	UiManager::m_strScrollBarSound		= CWorld::GetAppDataCharDir();
	UiManager::m_strCloseSound			= CWorld::GetAppDataCharDir();

	UiManager::m_strButtonClickSound	+= "\\data\\audio\\ui\\ButtonClick.wav";
	UiManager::m_strMoveOnSound		+= "\\data\\audio\\ui\\moveon.wav";
	UiManager::m_strCheckBoxSound		+= "\\data\\audio\\ui\\CheckBox.wav";
	UiManager::m_strIconDragSound		+= "\\data\\audio\\ui\\IconDrag.wav";
	UiManager::m_strListSound			+= "\\data\\audio\\ui\\List.wav";
	UiManager::m_strScrollBarSound		+= "\\data\\audio\\ui\\ScrollBar.wav";
	UiManager::m_strCloseSound			+= "\\data\\audio\\ui\\closeui.wav";
	theUiManager.m_pLogInfoFun = ErrorInfoLog;
	theUiManager.m_pCreateHelpWindowFun = _CreateHelpWindow;

	ControlFrame::NeedTradeViewerFunc = NeedTradeViewer;

// #if LOAD_COST_TIME_DEBUG
// 	DWORD nLastTimeRecord = HQ_TimeGetTime();
// 	char cOutputString[2048];
// #endif
	theHeroGame.LoadUIIcons();
// #if LOAD_COST_TIME_DEBUG
// 	DWORD nThisTimeRecord = HQ_TimeGetTime();
// 	MeSprintf_s( cOutputString, 2048, "\nLoadUIIcons:%d\n", nThisTimeRecord - nLastTimeRecord );
// 	nLastTimeRecord = nThisTimeRecord;
// 	OutputDebugStr(cOutputString);
// #endif

	// 下面三个UI要在其他UI之前加载，否则渲染字会出错，很恶心！
	s_CUI_ID_FRAME_MessageBox.LoadUI();
	s_CUI_ID_FRAME_MessageBox.SetVisable( false );
	s_CUI_ID_FRAME_CodeCheck.LoadUI();
	s_CUI_ID_FRAME_LoginCheck.LoadUI();
	s_CUI_ID_FRAME_BasePropertyBGFrame.LoadUI();
	//s_CUI_ID_FRAME_GameSetup.LoadUI();		//Setup界面

	Color_Config.load();
	Tip_Configure.load();
	g_shortcutKey_configure.loadDefault();

	//StartMexLoadingThread();
	MeLoopThread* pkPartModelLoadingThread = MeLoopThread::CreateThread(
		MeNew ModelLoadingThreadProc(), LoopLoadType::ePlayerEquip );	
	MeLoopThread* pkMounstNPCLoadingThread = MeLoopThread::CreateThread(
		MeNew ModelLoadingThreadProc(), LoopLoadType::eMonsterModel );
 	//pkMounstNPCLoadingThread->SetMainProcessSpeed( 5 );
	MeLoopThread* pkEffectLoadingThread = MeLoopThread::CreateThread(
		MeNew ModelLoadingThreadProc(), LoopLoadType::eModelEffect );
	// MeLoopThreadMan负责管理线程释放
	MeLoopThreadMan::Instance()->StartThreads( pkPartModelLoadingThread );
	MeLoopThreadMan::Instance()->StartThreads( pkMounstNPCLoadingThread );
	MeLoopThreadMan::Instance()->StartThreads( pkEffectLoadingThread );

	_pNavigation = MeNew navigation();
	char navi_name[MAX_PATH] = {0};
	MeSprintf_s(navi_name,sizeof(navi_name)/sizeof(char) - 1 ,"%s\\DATA\\Magic\\Common\\navigation\\navigation.MEX", CWorld::GetAppDataCharDir());//added, jiayi, [09.04.07]
	bool ret = _pNavigation->create( navi_name );
	assert( ret && "加载DATA\\Magic\\Common\\navigation\\navigation.MEX失败！" );//added, jiayi, [09.04.07]

	InitDirectInput( g_hWnd );

	s_CUI_ID_FRAME_LoadSplash.LoadUI();
	s_CUI_ID_FRAME_LoadSplash.SetVisable(true);	

	ms_spShimmerCollector = MeNew MeShimmerCollector;
	ms_spAlphaCollector = MeNew MeAlphaCollector;
	ms_spBitSorter = MeNew MeBitSorter;	
	// 默认开
	ms_spShimmerCollector->SetEnable( true );
	MeRenderManager::Instance()->SetSorter( ms_spBitSorter );
	MeRenderManager::Instance()->AddCollector( ms_spAlphaCollector );
	MeRenderManager::Instance()->AddCollector( ms_spShimmerCollector );	

	return S_OK;
	unguard;
}

HRESULT CHeroGame::InitGameInThread()
{
	guardfunc;
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      InitGameInThread开始", GetCurrentThreadId() );
    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Main, 0.0f );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载服务器列表", GetCurrentThreadId() );
	s_CUI_ID_FRAME_LOGIN.LoadServerList();

// #if LOAD_COST_TIME_DEBUG
// 	DWORD nLastTimeRecord = HQ_TimeGetTime();
// 	char cOutputString[2048];
// #endif

	// commented out, jiayi, [2010/6/1]
	// 去掉try-catch
	//try
	{
        LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化 Shader", GetCurrentThreadId() );
		if ( graphics::ShaderManager::instance()->supportPixelShader(1, 0) )
		{
			char  filename[MAX_PATH] = {0};
			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\Particle.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pParticleVP = MeNew graphics::ShaderVertexPixel( "MexShaderParticle",
				m_pd3dDevice, filename, "Particle_vp", filename, "Particle_fp", "vs_1_1", "ps_1_0" );
			graphics::ShaderManager::instance()->addShader( pParticleVP );
		}

		if ( graphics::ShaderManager::instance()->supportPixelShader( 2, 0 ) )
		{
			/*
			// specular.
			graphics::ShaderVertexPixel* pSpecularShader = MeNew graphics::ShaderVertexPixel( "Specular",
				m_pd3dDevice, "DATA\\SHADER\\RenderObject.fxo", "Specular_vs",
				"DATA\\SHADER\\RenderObject.fxo", "Specular_ps", "vs_2_0", "ps_2_0" );
			pSpecularShader->setTextureStageIndex( "brightTex", 1 );
			pSpecularShader->setTextureStageIndex( "animTex", 2 );
			graphics::ShaderManager::instance()->addShader( pSpecularShader );
			*/		

			if( !LoadFxShader() )
				return S_FALSE;

			// diffuse shader.
			char  filename[MAX_PATH] = {0};
			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\RenderObject.fxo", GetRootPath() );
			graphics::ShaderEffect* pDiffuseShader = MeNew graphics::ShaderEffect( "MexShader",
				m_pd3dDevice, filename );
			pDiffuseShader->setTechnique( "Diffuse" );
			graphics::ShaderManager::instance()->addShader( pDiffuseShader );

			/*
			// specular and animation.
			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\RenderObject.fxo", GetRootPath() );
			graphics::ShaderVertexPixel* pSpecularAndAnimShader = MeNew graphics::ShaderVertexPixel( "SpecularAndAnim",
				m_pd3dDevice, filename, "Specular_vs", filename, "SpecularAndAnim_ps", "vs_2_0", "ps_2_0" );
			pSpecularAndAnimShader->setTextureStageIndex( "brightTex", 1 );
			pSpecularAndAnimShader->setTextureStageIndex( "animTex", 2 );
			graphics::ShaderManager::instance()->addShader( pSpecularAndAnimShader );
			*/

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\Diffuse.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pDiffuseVP = MeNew graphics::ShaderVertexPixel( "MexShaderDiffuse",
				m_pd3dDevice, filename, "Diffuse_vp", filename, "Diffuse_fp" );
			graphics::ShaderManager::instance()->addShader( pDiffuseVP );

			// with lightmap
			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\Diffuse.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pDiffuseLMVP = MeNew graphics::ShaderVertexPixel( "MexShaderDiffuseLM",
				m_pd3dDevice, filename, "DiffuseLM_vp", filename, "DiffuseLM_fp" );
			graphics::ShaderManager::instance()->addShader( pDiffuseLMVP );

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\Shimmer.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pShimmerVP = MeNew graphics::ShaderVertexPixel( "MexShaderShimmer",
				m_pd3dDevice, filename, "Shimmer_vp", filename, "Shimmer_fp" );
			graphics::ShaderManager::instance()->addShader( pShimmerVP );

			/*
			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\Glow.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pGlowVP = MeNew graphics::ShaderVertexPixel( "MexShaderGlow",
				m_pd3dDevice, filename, "Glow_vp", filename, "Glow_fp" );
			graphics::ShaderManager::instance()->addShader( pGlowVP );
			*/

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\Specular.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pSpecularVP = MeNew graphics::ShaderVertexPixel( "MexShaderSpecular",
				m_pd3dDevice, filename, "Specular_vp", filename, "Specular_fp" );
			graphics::ShaderManager::instance()->addShader( pSpecularVP );

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\NoLighting.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pNotLightingVP = MeNew graphics::ShaderVertexPixel( "MexShaderNoLighting",
				m_pd3dDevice, filename, "NoLighting_vp", filename, "NoLighting_fp" );
			graphics::ShaderManager::instance()->addShader( pNotLightingVP );

			// with light map
			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\NoLighting.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pNotLightingLMVP = MeNew graphics::ShaderVertexPixel( "MexShaderNoLightingLM",
				m_pd3dDevice, filename, "NoLightingLM_vp", filename, "NoLightingLM_fp" );
			graphics::ShaderManager::instance()->addShader( pNotLightingLMVP );

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\AlphaTest.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pAlphaTestVP = MeNew graphics::ShaderVertexPixel( "MexShaderAlphaTest",
				m_pd3dDevice, filename, "AlphaTest_vp", filename, "AlphaTest_fp" );
			graphics::ShaderManager::instance()->addShader( pAlphaTestVP );

			// with lightmap
			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\AlphaTest.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pAlphaTestLMVP = MeNew graphics::ShaderVertexPixel( "MexShaderAlphaTestLM",
				m_pd3dDevice, filename, "AlphaTestLM_vp", filename, "AlphaTestLM_fp" );
			graphics::ShaderManager::instance()->addShader( pAlphaTestLMVP );


			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\SkyBox.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pSkyBoxVP = MeNew graphics::ShaderVertexPixel( "MexShaderSkyBox",
				m_pd3dDevice, filename, "SkyBox_vp", filename, "SkyBox_fp" );
			graphics::ShaderManager::instance()->addShader( pSkyBoxVP );

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\Collision.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pCollisionVP = MeNew graphics::ShaderVertexPixel( "MexShaderCollision",
				m_pd3dDevice, filename, "Collision_vp", filename, "Collision_fp" );
			graphics::ShaderManager::instance()->addShader( pCollisionVP );

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\Shadow.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pShadowVP = MeNew graphics::ShaderVertexPixel( "MexShaderShadow",
				m_pd3dDevice, filename, "Shadow_vp", filename, "Shadow_fp" );
			graphics::ShaderManager::instance()->addShader( pShadowVP );

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\SkeletonDiffuse.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pSkeletonDiffuseVP = MeNew graphics::ShaderVertexPixel( "MexShaderDiffuseSkeleton",
				m_pd3dDevice, filename, "SkeletonDiffuse_vp", filename, "SkeletonDiffuse_fp" );
			graphics::ShaderManager::instance()->addShader( pSkeletonDiffuseVP );

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\SkeletonShimmer.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pSkeletonShimmerVP = MeNew graphics::ShaderVertexPixel( "MexShaderShimmerSkeleton",
				m_pd3dDevice, filename, "SkeletonShimmer_vp", filename, "SkeletonShimmer_fp" );
			graphics::ShaderManager::instance()->addShader( pSkeletonShimmerVP );

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\SkeletonSpecular.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pSkeletonSpecularVP = MeNew graphics::ShaderVertexPixel( "MexShaderSpecularSkeleton",
				m_pd3dDevice, filename, "SkeletonSpecular_vp", filename, "SkeletonSpecular_fp" );
			graphics::ShaderManager::instance()->addShader( pSkeletonSpecularVP );

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1 ,"%s\\DATA\\SHADER\\SkeletonEffect.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pSkeletonEffectVP = MeNew graphics::ShaderVertexPixel( "MexShaderEffectSkeleton",
				m_pd3dDevice, filename, "SkeletonEffect_vp", filename, "SkeletonEffect_fp" );
			graphics::ShaderManager::instance()->addShader( pSkeletonEffectVP );

			MeSprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s\\DATA\\SHADER\\SkeletonShadow.hlsl", GetRootPath() );
			graphics::ShaderVertexPixel* pSkeletonShadowVP = MeNew graphics::ShaderVertexPixel( "MexShaderShadowSkeleton",
				m_pd3dDevice, filename, "SkeletonShadow_vp", filename, "SkeletonShadow_fp" );
			graphics::ShaderManager::instance()->addShader( pSkeletonShadowVP );
		}
		else
		{
			graphics::ShaderManager::instance()->useShader( false );
			MessageBox(hWndSplash,theXmlString.GetString( eError_VideoCardToSlow ), "Error", MB_OK);
			::TerminateProcess( ::GetCurrentProcess(), 0 );
		}

#if 0
		else if ( graphics::ShaderManager::instance()->supportPixelShader( 1, 1 ) )
		{
#if 0
			// specular.
			graphics::ShaderVertexPixel* pSpecularShader = MeNew graphics::ShaderVertexPixel( "Specular",
				m_pd3dDevice, "DATA\\SHADER\\RenderObject.fxo", "Specular_vs_1_1",
				"DATA\\SHADER\\RenderObject.fxo", "Specular_ps_1_1", "vs_1_1", "ps_1_1" );
			pSpecularShader->setTextureStageIndex( "brightTex", 1 );
			pSpecularShader->setTextureStageIndex( "animTex", 2 );

			graphics::ShaderManager::instance()->addShader( pSpecularShader );

			// specular and animation.
			graphics::ShaderVertexPixel* pSpecularAndAnimShader = MeNew graphics::ShaderVertexPixel( "SpecularAndAnim",
				m_pd3dDevice, "DATA\\SHADER\\RenderObject.fxo", "Specular_vs_1_1",
				"DATA\\SHADER\\RenderObject.fxo", "SpecularAndAnim_ps_1_1", "vs_1_1", "ps_1_1" );
			pSpecularAndAnimShader->setTextureStageIndex( "brightTex", 1 );
			pSpecularAndAnimShader->setTextureStageIndex( "animTex", 2 );

			graphics::ShaderManager::instance()->addShader( pSpecularAndAnimShader );
#else
			// specular.
			graphics::ShaderEffect* pSpecularShader = MeNew graphics::ShaderEffect( "Specular",
				m_pd3dDevice, "DATA\\SHADER\\RenderObject.fxo" );
			pSpecularShader->setTechnique( "Specular_1_1" );

			graphics::ShaderManager::instance()->addShader( pSpecularShader );

			// specular and animation.
			graphics::ShaderEffect* pSpecularAndAnimShader = MeNew graphics::ShaderEffect( "SpecularAndAnim",
				m_pd3dDevice, "DATA\\SHADER\\RenderObject.fxo" );
			pSpecularAndAnimShader->setTechnique( "SpecularAndAnim_1_1" );

			graphics::ShaderManager::instance()->addShader( pSpecularAndAnimShader );
#endif
		}
#endif

	}
// #if LOAD_COST_TIME_DEBUG
// 	DWORD nThisTimeRecord = HQ_TimeGetTime();
// 	MeSprintf_s( cOutputString, 2048, "\nShaderLoad:%d\n", nThisTimeRecord - nLastTimeRecord );
// 	nLastTimeRecord = nThisTimeRecord;
// 	OutputDebugStr(cOutputString);
// #endif

	s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Main, 0.25f );

	if( SystemSetting::Instance()->IsLowLevelCard() )//low level
	{
        LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      低端显卡更换图像等级", GetCurrentThreadId() );
		ChangeGraphicsLevel( 0 );		
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化相机", GetCurrentThreadId() );
	getwsCamera()->Init3DCamera();

	GetEngine()->UseTextureMultiThreadLoading( TRUE );
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化玩家管理器", GetCurrentThreadId() );
	GetPlayerMgr()->Init( );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化宝箱系统", GetCurrentThreadId() );
	// added, jiayi, [2010/1/5]
	RollSystemStatusMan<RST_LuckyGame>::Init();
	RollSystemStatusMan<RST_Lottery>::Init();

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载过滤表", GetCurrentThreadId() );
	// 加载过滤表
	CChatCheck::getInstance()->LoadUndueString("..\\Data\\ClientConfig\\FilterString.config");
	CChatCheck::getInstance()->LoadSpecialCharFilterString("..\\Data\\ClientConfig\\SpecialCharFilter.config");	// ANSI格式特殊字符

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化网络", GetCurrentThreadId() );
	//建立连接服务器
	GettheNetworkInput().InitConnect( gCfg.m_szDstIP,gCfg.m_iLoginDstPort );
// #if LOAD_COST_TIME_DEBUG
// 	nThisTimeRecord = HQ_TimeGetTime();
// 	MeSprintf_s( cOutputString, 2048, "\nInitial1:%d\n", nThisTimeRecord - nLastTimeRecord );
// 	nLastTimeRecord = nThisTimeRecord;
// 	OutputDebugStr(cOutputString);
// #endif

	if (gCfg.m_bUiViewer)
	{
		guard(AddFrame);

		TCHAR Buffer[256] = {0};
		GetCurrentDirectory(256, Buffer);

		OPENFILENAME ofn;       // common dialog box structure
		char szFile[260];       // buffer for file name

		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		//
		// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
		// use the contents of szFile to initialize itself.
		//
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "MEUI files\0*.meui\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		// Display the Open dialog box. 

		if (GetOpenFileName(&ofn))
		{
			SetCurrentDirectory(Buffer);
			g_strViewerUIFilename = szFile;

			DWORD dwResult = theUiManager.AddFrame( g_strViewerUIFilename.c_str() );
			if ( dwResult == 0 )
			{
				MessageBoxA(0, "读取文件失败！", "UI Viewer", MB_OK|MB_ICONERROR);
			}
		}

		unguard;
		return S_OK;
	}

	s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Main, 0.5f );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载地形管理", GetCurrentThreadId() );
	if (NULL == m_world)
	{
		char pathName[MAX_PATH] = {0};
		strcpy(pathName, "../data/world");

		Assert( NULL == m_world );
		m_world = new CWorld();
		SwGlobal::SetWorld(m_world);
		if (m_world->Create(new CWorldBuffer(m_world)) && m_world->Load( pathName ))
		{
// 			m_world->GetWorldBuffer()->SetMultiThread(false);//使用游戏原有的多线程机制
			m_world->GetWorldBuffer()->GetGlobalResMgr()->Create();
			m_worldPick = new CNdlWorldPickerBase(m_world);
			SwGlobal::SetWorldPicker(m_worldPick);
		}
		gCfg.FillTileIdCountryMap();
	}
// #if LOAD_COST_TIME_DEBUG
// 	nThisTimeRecord = HQ_TimeGetTime();
// 	MeSprintf_s( cOutputString, 2048, "\nWorldCreate:%d\n", nThisTimeRecord - nLastTimeRecord );
// 	nLastTimeRecord = nThisTimeRecord;
// 	OutputDebugStr(cOutputString);
// #endif

	s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Main, 0.8f );

	if( !g_pFlyTextEffect )	
		g_pFlyTextEffect = MeNew CFlyTextEffect;

	if(!g_pPrintTextEffect)//lyh++feixingwenzi
		g_pPrintTextEffect = MeNew CPrintTextEffect;


	thePlayerRole.m_doll.Create();

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      创建天空盒", GetCurrentThreadId() );
	GetSTSkyBox()->Create(8,						// resolution
		45,										// sweep in degrees
		500,									// size at horizon
		1.0f,									// height scale factor
		D3DXVECTOR3 (0, 0, 0));					// offset


	GetMe3dConfig()->m_nScreenWidth = SCREEN_WIDTH;
	GetMe3dConfig()->m_nScreenHeight = SCREEN_HEIGHT;

    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Main, 1.0f );
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      InitGameInThread结束", GetCurrentThreadId() );

	return S_OK;
	unguard;
}

void CHeroGame::LoadUIIcons()
{
	theControlPictureManager.EnableLoadImage(true);
	IconManager::Get().Load("..\\Data\\Config\\ItemIcon.config");
	{
		char filename[256];

		int nPicId = -1;

		nPicId = -1;
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/%s", GetRootPath(), "Data/Ui/Icon/SkillIcon/Armour/ArmourSkill01.dds");
		theControlPictureManager.RegisterTexture(&nPicId, filename);

		nPicId = -1;
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/%s", GetRootPath(), "Data/Ui/Icon/SkillIcon/Common/MountSkill.dds");
		theControlPictureManager.RegisterTexture(&nPicId, filename);

		nPicId = -1;
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/%s", GetRootPath(), "Data/Ui/Icon/SkillIcon/Common/ProduceSkill.dds");
		theControlPictureManager.RegisterTexture(&nPicId, filename);

		nPicId = -1;
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/%s", GetRootPath(), "Data/Ui/Icon/SkillIcon/Skill/SkillIcon2.dds");
		theControlPictureManager.RegisterTexture(&nPicId, filename);

		nPicId = -1;
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/%s", GetRootPath(), "Data/Ui/Icon/SkillIcon/Skill/SkillIcon3.dds");
		theControlPictureManager.RegisterTexture(&nPicId, filename);

	}
	theControlPictureManager.EnableLoadImage(false);
}

void CHeroGame::OnSizeWindow( WPARAM wParam ,LPARAM lParam )
{
	int nWidth = LOWORD( lParam );
	int nHeight = HIWORD( lParam );
	if( nWidth != SCREEN_WIDTH || nHeight != SCREEN_HEIGHT )		
	{
		int nValue = ((nWidth << 16)&0xFFFF0000) | nHeight;
		SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_RESOLUTION, nValue );
		SystemSetting::Instance()->CommitChanges();
		char szSetting[MAX_PATH] = {0};
		MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1 ,"%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
		SystemSetting::Instance()->SaveSetting( szSetting );
		if( g_GameState == G_MAIN )
			SystemSetting::Instance()->CommitChanges();
// 			s_CUI_ID_FRAME_Systemset.Refresh();
	}
}

HRESULT CHeroGame::RestoreDeviceObjects()
{
	guardfunc;

	if (gCfg.m_bUiViewer)
		return S_OK;

	// added, jiayi, [2009/9/23]
	m_pd3dDevice->EvictManagedResources();

	// 重置字体
	FontSystem::ResetDevice( ControlObject::GetREAL_SCALE(NULL) );

	GetEngine()->GetRenderer()->SetDevice( m_pd3dDevice );

	// init queries interlock.s
	assert( m_pQueriesInterlock == 0 );
	m_pQueriesInterlock = new NextQueriesInterlock( m_pd3dDevice );

	//
	// add [5/30/2008 whu]
	//
	IRenderer* RI = GetEngine()->GetRenderer();
	RI->RestoreDeviceObjects( m_pd3dDevice );


	GetShaderMgr()->Enable( TRUE );

	GetShaderMgr()->InitShader();// 不管支不支持 都要初始化 不支持就用固定管道渲染
	
	GetMexResMgr()->OnDeviceReset();

	HRESULT hr = S_OK;

	// UI
	theUiManager.RestoreDeviceObjects();
	GetShowScreenText()->ReCalYPos();
	// Set the world matrix
	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity( &matIdentity );
	RI->SetTransform( D3DTS_WORLD,  (FLOAT*)&matIdentity );

	// 去掉try-catch
	//try
	{
		MexInstanceMan::OnResetDevice();

		if( !SystemSetting::Instance()->IsLowLevelCard() )
		{
			PostProcessManager::instance().restoreDeviceObjects( m_pd3dDevice, 
				SCREEN_WIDTH, SCREEN_HEIGHT );
			MeShimmerCollector::CreateFrameTexture( SCREEN_WIDTH, SCREEN_HEIGHT, PostProcessManager::instance().GetSceneRT() );
		}        
	}
	// 	catch ( const std::exception& e )
	// 	{
	// 		OutputDebugString( e.what() );
	// 	}

	//灯光设备恢复暂时用InitZone替代
	if(SwGlobal::GetWorld() && SwGlobal::GetWorld()->GetWorldBuffer() )
	{
		SwGlobal::GetWorld()->InitZone();
		SwGlobal::GetWorld()->OnDeviceReset(false);
	}

	RI->SetRenderState( D3DRS_LIGHTING, TRUE );	

	// added by zhuomeng.hu		[2/24/2011]
	CMovieManager::Instance()->ResetDevice();

	CUIMgr::Instance()->ResetDevice();

	Font3DManager::Instance()->OnResetDevice(m_pd3dDevice);


	theHeroGame.GetPlayerMgr()->ResetRevice();

	m_ddrawLib = LoadLibraryW( L"ddraw.dll" );
	if( m_ddrawLib )
	{
		HRESULT (WINAPI* _DirectDrawCreateEx)( GUID* lpGUID, void** lplpDD, REFIID iid, IUnknown* pUnkOuter ) = 
			(HRESULT (WINAPI*)( GUID* lpGUID, void** lplpDD, REFIID iid, IUnknown* pUnkOuter ))GetProcAddress( m_ddrawLib, "DirectDrawCreateEx" ); 
		if( _DirectDrawCreateEx )
		{
			HRESULT result = _DirectDrawCreateEx( 0,  (void**)&m_pDDobject, IID_IDirectDraw7, NULL );			
		}



		//lyh++ 显存小于300 则不让进游戏
		/*DDSCAPS2 ddscaps2;
		DWORD VideoMemory=-1;
		DWORD Temp=0;
		memset( &ddscaps2, 0, sizeof(ddscaps2) );
		ddscaps2.dwCaps = DDSCAPS_VIDEOMEMORY;
		DWORD dwTotal=0;
		DWORD dwFree=0;
          HRESULT hr = m_pDDobject->GetAvailableVidMem(&ddscaps2, &dwTotal, &dwFree);
		if (SUCCEEDED(hr)) 
		{
			if(dwTotal / 1000000 < 300)
			{
				MessageBox(hWndSplash,"显卡配置过低,无法运行游戏!","错误" ,MB_OK);
				PostQuitMessage(0);
			}
		}*/
	}

	if( g_GameState == G_MAIN )
	{
		s_CUI_ID_FRAME_Task.Refresh();
		s_CUI_ChatInfoBox.Refresh(s_CUI_ID_FRAME_chatInfoList.GetChannelStartIndex(s_CUI_ChatInfoBox.GetChatChannelIndex()));
// 		s_CUI_ID_FRAME_ChatSystem.Refresh();
		chatMessageManage.Refresh();
		s_CUI_ID_FRAME_AllNpcList.CalDrawParameter();
		s_CUI_ID_FRAME_Speaker.Refresh(0);
		s_CUI_ID_FRAME_InfoList.Refresh(0);
		UnpauseThread();
	}

	MeLoopThreadMan::Instance()->ResumeThreads();

	WeatherEventManager::Instance()->OnDeviceReset();

	return S_OK;
	unguard;
}

HRESULT CHeroGame::InvalidateDeviceObjects()
{
	guardfunc;

	if (gCfg.m_bUiViewer)
		return S_OK;

	if( g_GameState == GAME_STATE::G_MAIN )
	{
		PauseThread();
	}
	MeLoopThreadMan::Instance()->PauseThreads();
	// TODO: Cleanup any objects created in RestoreDeviceObjects()
	//	theUiManager.InvalidateDeviceObjects();
	//
	FontSystem::LostDevice();

	// add [5/20/2008 whu]
	GetEngine()->GetRenderer()->InvalidateDeviceObjects();

	delete m_pQueriesInterlock;
	m_pQueriesInterlock = 0;

	if(SwGlobal::GetWorld())
	{
		SwGlobal::GetWorld()->OnDeviceLost();
	}

	GetShaderMgr()->DestroyDeviceOjbects();
	// added, [8/12/2010 zhangjiayi]
	MeRenderManager::Instance()->OnDeviceLost();

	// added by zhuomeng.hu		[2/24/2011]
	CMovieManager::Instance()->OnDeviceLost();

	//try
	{
		MexInstanceMan::OnLostDevice();
		if( !SystemSetting::Instance()->IsLowLevelCard() )
		{
			PostProcessManager::instance().invalidateDeviceObjects();
		}

	}
	// 	catch ( const std::exception& e )
	// 	{
	// 		OutputDebugString( e.what() );
	// 	}

	Font3DManager::Instance()->OnLostDevice();

	//free ddraw
	if( m_pDDobject )
		m_pDDobject->Release();
	m_pDDobject = NULL;
	if( m_ddrawLib )
		FreeLibrary( m_ddrawLib );
	m_ddrawLib = NULL;

	// 刷新抗锯齿ui
	SystemSetting::Instance()->GetFSAATypeList().clear();	
	D3DDEVTYPE devType = D3DDEVTYPE_HAL;
	UINT adapterNumber = 0;

	// Look for 'NVIDIA NVPerfHUD' adapter (<= v4)
	// or 'NVIDIA PerfHUD' (v5)
	// If it is present, override default settings
	for (UINT adapter=0; adapter < m_pD3D->GetAdapterCount(); ++adapter)
	{
		D3DADAPTER_IDENTIFIER9 identifier;
		HRESULT res;
		res = m_pD3D->GetAdapterIdentifier(adapter,0,&identifier);
		if (strstr(identifier.Description,"PerfHUD") != 0)
		{
			adapterNumber = adapter;
			devType = D3DDEVTYPE_REF;
			break;
		}
	}

	/*
	for( UINT iMode=0; iMode < m_pD3D->GetAdapterModeCount( adapterNumber, D3DFMT_X8R8G8B8 ); iMode++ )
	{
		D3DDISPLAYMODE displayMode;
		m_pD3D->EnumAdapterModes( adapterNumber, D3DFMT_X8R8G8B8, iMode, &displayMode );

		// Filter out low-resolutions
		if( displayMode.Width != SCREEN_WIDTH || displayMode.Height != SCREEN_HEIGHT )// modified, jiayi, [2009.4.17]
			continue;

		// get non maskable FSAA for this VMODE
		DWORD numLevels = 0;
		HRESULT hr;
		SystemSetting::Instance()->AddFSAAType( 0 );		
		for( int iSampleCount = 2 ; iSampleCount <= 8 ; iSampleCount++ )
		{
			hr = m_pD3D->CheckDeviceMultiSampleType( 
				adapterNumber, 
				D3DDEVTYPE_HAL, 
				displayMode.Format, 
				!m_bWindowed, 
				(D3DMULTISAMPLE_TYPE)iSampleCount, 
				&numLevels);

			numLevels -= 1;

			bool bOK = SUCCEEDED(hr);
			if (bOK && numLevels >= 0)
			{
				SystemSetting::Instance()->AddFSAAType( iSampleCount );							
			}
		}
	}
	*/
	GetBestAvailableMultiSampleType(m_pD3D);

	GetMexResMgr()->OnDeviceLost();

	WeatherEventManager::Instance()->OnDeviceLost();

	return CMyD3DApplication::InvalidateDeviceObjects();
	unguard;
}

HRESULT CHeroGame::ProcessCommond()
{
	guardfunc;

	if ( g_bCloseApp ) 
	{
		if (gCfg.m_bOpenExitPage)
		{
			ShellExecute( NULL, "open", gCfg.m_strExitPage.c_str(), NULL, NULL, 0 );
		}
		::PostMessage( g_hWnd, WM_USER_CLOSE, 0, 0 );
		return S_OK;
	}

	if( g_bBackToLogin )
	{
		ChangeGameState(g_GameState,G_LOGIN);
		g_bBackToLogin = FALSE;
		if( theHeroGame.GetPlayerMgr() )
			theHeroGame.GetPlayerMgr()->DeletePlayersExceptMe();
	}

	if( g_bMainToSelectUI )
	{
		ChangeGameState(G_MAIN,G_LOGIN);
		g_bMainToSelectUI = FALSE;
		if( theHeroGame.GetPlayerMgr() )
			theHeroGame.GetPlayerMgr()->DeletePlayersExceptMe();
	}
	if( s_CUI_ID_FRAME_LoadSplash.IsFinished() )
	{
		static bool bChanged = false;
		if( !bChanged )
			ChangeGameState(G_LOADSPLASH, G_LOGIN);
		bChanged = true;
	}

	if(s_CUI_ID_FRAME_Select.GetStateToLogin())
	{
		ChangeGameState( G_SELECT, G_LOGIN );
		s_CUI_ID_FRAME_Select.SetStateToLogin();
	}
	//	删除 SelectWeapon 界面		modified by zhuomeng.hu		[8/20/2010]
	if(s_CUI_ID_FRAME_Select.GetStateToCreate())             // Select -> Create
	{
		ChangeGameState( G_SELECT, G_CREATE );
        s_CUI_ID_FRAME_Select.SetStateToCreate();
	}
	if(s_CUI_ID_FRAME_CREATE.GetStateToSelect())          // Create -> Select
	{
		s_CUI_ID_FRAME_CREATE.UnLoadUI();
		s_CUI_ID_FRAME_CREATE.SetVisable(false);

		s_CUI_ID_FRAME_FirstCreate.LoadUI();
		s_CUI_ID_FRAME_FirstCreate.SetVisable(true);
		
		s_CUI_ID_FRAME_CREATE.SetStateToSelect();
	}

	if(s_CUI_ID_FRAME_FirstCreate.GetStateToCreate())
	{
		s_CUI_ID_FRAME_FirstCreate.UnLoadUI();
		s_CUI_ID_FRAME_FirstCreate.SetVisable(false);

		s_CUI_ID_FRAME_CREATE.LoadUI();
		s_CUI_ID_FRAME_CREATE.SetVisable(true);
		s_CUI_ID_FRAME_CREATE.RefreshPlayerAnim(s_CUI_ID_FRAME_FirstCreate.GetSex(),s_CUI_ID_FRAME_FirstCreate.GetCountry());

		s_CUI_ID_FRAME_FirstCreate.SetStateToCreate(false);
	}

	if(s_CUI_ID_FRAME_FirstCreate.GetStateToSelect())
	{
		ChangeGameState(G_CREATE,G_SELECT);
		s_CUI_ID_FRAME_FirstCreate.SetStateToSelect(false);
	}

	return S_OK;
	unguard;
}


bool isDetectInvalidPlus = false;
bool OnceNP = false;
bool RecorveInvalidPlusDetect(char bIsTell,void *pData )
{
#ifdef NPGUARD
	TerminateProcess(::GetCurrentProcess(), 0); //发现错误后 点击ok结束游戏进程
#endif
	//isDetectInvalidPlus = false;
	return true;

}

//优化,这里有%25的时间不知道在那儿耗费的. 给sleep了
BOOL GLoadCoreDataError;
BOOL GLoadCoreDataExited = FALSE;
HRESULT	CHeroGame::FrameMove()
{
	guardfunc;
	DWORD time_cost = HQ_TimeGetTime();
#ifndef _DEBUG
	if (!isDetectInvalidPlus)
	{
		//变速齿轮
		char Temp[256];
		sprintf(Temp,"%x",*(unsigned long*)timeGetTime);
		char Temp1[256];
		sprintf(Temp1,"%x",*(unsigned long*)GetTickCount);
		if ((Temp[6]  == 'e' && Temp[7]  == '9')
			|| (Temp1[6]  == 'e' && Temp1[7]  == '9'))
		{
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eError_DetectInvalidPlus),"",CUI_ID_FRAME_MessageBox::eTypeConfirm,true,RecorveInvalidPlusDetect);
			isDetectInvalidPlus = true;
			return -1;
		}
	}
#endif

	#ifdef NPGUARD
  //LYH NP

	//初始化已经退出 这里我提示发现外怪,直接推出游戏,日志已经写完毕了
	 if(bAppExit)
	 {
		if( lpszMsg[0])
		{
		char msg[256] = {0};
		wsprintf(msg, "GameGuard执行错误:%lu", NpInit_dwResult);
		MessageBox(NULL,lpszMsg, msg, MB_OK);
		TerminateProcess(::GetCurrentProcess(), 0); //发现错误后 点击ok结束游戏进程
		}
	 }


	static DWORD ClientRunTimeBegin = timeGetTime();
	DWORD ClientRunTimeEnd = timeGetTime();
	DWORD clientPassTime = (ClientRunTimeEnd - ClientRunTimeBegin)*0.001f;

	if (clientPassTime > 15 )
	{

		ClientRunTimeBegin = ClientRunTimeEnd;

		if ( !OnceNP  && npgl && npgl->Check() != NPGAMEMON_SUCCESS)
		{  
			    OnceNP = true;
				if(npgl)
				{
				delete npgl;
				npgl = NULL;
				}
				s_CUI_ID_FRAME_MessageBox.Show("GameGuard异常结束!","",CUI_ID_FRAME_MessageBox::eTypeConfirm,true,RecorveInvalidPlusDetect);
			  	s_CUI_ID_FRAME_MessageBox.SetAutoClose(4);
				
		}
	 }

		if (g_szHackMsg[0] && !OnceNP)
		{
			OnceNP = true;
				if(npgl)
				{
				delete npgl;
				npgl = NULL;
				}

			    s_CUI_ID_FRAME_MessageBox.Show("发现第三方工具，游戏关闭","",CUI_ID_FRAME_MessageBox::eTypeConfirm,true,RecorveInvalidPlusDetect);
			  	s_CUI_ID_FRAME_MessageBox.SetAutoClose(6);
		}

  #endif
	

	DWORD fBeforeFrameMove = HQ_TimeGetTime() ;
	IRenderer* RI = GetEngine()->GetRenderer();
	// add [5/29/2008 whu]
	IRenderer::ShaderParameter shaderParam;
	shaderParam["time"] = m_fTime;
	RI->SetShaderParameter( shaderParam );

	GetEngine()->GetTextureManager()->ProcessTextureLoadingThread();
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n ProcessTextureLoadingThread:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif
	//ProcessMexLoadingThread();
	MeLoopThreadMan::Instance()->MainThreadProcess();

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n MeLoopThreadMan::Instance()->MainThreadProcess();:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	//////////////////////////////////////////////////////////////////////////
	// Check 加载时候如果出错就退出
	if( !GLoadCoreDataExited )
	{
		if( GLoadCoreDataError )
		{
			assert( 0 && "load core data error" );
			SendMessage( g_hWnd, WM_USER_CLOSE/*WM_CLOSE*/, 0, 0 );
			return S_FALSE;
		}

	}

	// 更新获取物理内存CD
	UpdateGetPhyMemoryCD();

	g_dwLastFrameCostTime = HQ_TimeGetTime() - g_dwLastFrameBeginTime;
	g_dwLastFrameRealCostTime = g_dwLastFrameCostTime;
	if ( g_dwLastFrameCostTime > 1000 )
	{
		g_dwLastFrameCostTime = 1000;
	}
	g_dwLastFrameBeginTime = HQ_TimeGetTime();


	DWORD dwTime = HQ_TimeGetTime();	
	if( g_GameState != G_LOADSPLASH )
	{
		ExpressionManager::GetInstance().SetCurrentFrameTime( dwTime );
		ExpressionManager::GetInstance().ToNextFrame();
	}
	{
		ProcessInput( dwTime );
	}

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n ProcessInput:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	// HRUI
	if( g_bRenderUI )
	{
		m_UIUpdateCost = HQ_TimeGetTime();
		theUiManager.FrameMove();
		m_UIUpdateCost = HQ_TimeGetTime() - m_UIUpdateCost;
	}

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n theUiManager.FrameMove();:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	MexAnimCtrl::SetGameTime( dwTime );
	// added by zhuomeng.hu		[2/25/2011]
	CMovieManager::Instance()->Update();

	{
		switch( g_GameState )
		{
		case G_LOGIN:
			{

			}
			break;
		case G_CREATE:
			break;
		case G_SELECT:
			break;
		case G_MAIN:
			// 加载地图或者switch gate状态，不刷新游戏逻辑
			if( !CUI_ID_FRAME_LOGIN::g_bSwitchGate && !CUI_ID_FRAME_LOGIN::g_bEndGetCharacter )
			{
				if ( s_CUI_ID_FRAME_LoadMap.IsMapLoaded()/* == true*/ )
				{
					s_CUI_ID_FRAME_Task.RefreshTaskTrack();
					s_CUI_ID_FRAME_ActivityList.Update();

#if LOAD_COST_TIME_DEBUG
					time_cost = HQ_TimeGetTime() - time_cost;
					if(time_cost > 20)
					{
						char cOutputString[2048];
						MeSprintf_s( cOutputString, 2048, "\n s_CUI_ID_FRAME_ActivityList.Update(): %d\n", time_cost );
						OutputDebugStr(cOutputString);
					}
					time_cost = HQ_TimeGetTime();
#endif

					RunGameMain( dwTime );
				}
				else
					Sleep(10);
			}
			else
				Sleep(1);
			break;
		};
	}

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n RunGameMain: %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&getwsCamera()->GetMeCamera()->GetViewMatrix() );

	{
		guard(UpdateAudio);
		UpdateAudio( dwTime );
		if (IsActiveWindow())
		{
			if (!isActive)
			{
				GMusic.SetVolume(m_fMusicVolume);
				GSound.SetVolume(m_fSoundVolume);
				isActive = true;
			}
		}
		else
		{
			if (isActive)
			{
				m_fMusicVolume = GMusic.m_fSoundVal;
				m_fSoundVolume = GSound.m_fSoundVal;
				GMusic.SetVolume(0.f);
				GSound.SetVolume(0.f);
				isActive = false;
			}
		}
		unguard;
	}

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n UpdateAudio: %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	ProcessCommond();

	GetEngine()->GetTextureManager()->FrameClear();

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n GetEngine()->GetTextureManager()->FrameClear();: %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	g_bHaveSelectNpc = GetAdvancedMiniMap()->GetCurSelectNpc( g_vCurSelectNpcPos );

	m_FrameMoveCost =  HQ_TimeGetTime() - fBeforeFrameMove;

    if( s_CUI_ID_FRAME_LoadSplash.ShouldUILoad() )
    {
        // UI加载移到此       added by ZhuoMeng.Hu		[10/26/2010]
        LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化UI管理器", GetCurrentThreadId() );
        GetUIScriptMgr()->Init();
        if( GetUIScriptMgr() )
        {
            GetEngine()->UseTextureMultiThreadLoading( FALSE );
            theControlPictureManager.EnableLoadImage(true);
            LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      UI加载开始", GetCurrentThreadId() );
            GetUIScriptMgr()->loadUIs();
            LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      UI加载结束", GetCurrentThreadId() );
            theControlPictureManager.EnableLoadImage(false);
        }
    }

	//ME_MEMORY_CHECK
	//ME_END_MEMORY_CHECK;
#ifdef _DEBUG
	if (0)
	{
		CMeMemoryDetailDump::Instance()->DumpDetailInfo();
	}
#endif
	return S_OK;
	unguard;
}

void CHeroGame::RenderGameMain( DWORD dwTime )
{
	guardfunc;
#if LOAD_COST_TIME_DEBUG
	DWORD time_cost = HQ_TimeGetTime();
#endif
	IRenderer* RI = GetEngine()->GetRenderer();

	if ( FAILED( RI->BeginScene() ) )
	{
		return;
	}

	// 没有加载完地图
	if ( !s_CUI_ID_FRAME_LoadMap.IsMapLoaded() )
	{
		theUiManager.Render();
		RI->EndScene();
		return;
	}

	if( FontSystem::IsUseNewFont() )
	{
		FontSystem::ClearRender( FontRender::EFR_SECOND );// second is for will be cleared each frame
		FontRender::getFontRender()->SetDefaultRendererIdx( FontRender::EFR_SECOND );
	}

	DisplayGameMain( dwTime );
	UpdateMouseCursor();

	if( theApp->GetPlayerMgr() && GetPlayerMgr()->GetMe() )
	{
		GetEffectMgr()->SetTheLookerPos( getwsCamera()->GetMeCamera()->GetEyePt() );
		GetEffectMgr()->SetTheLookerViewDistance( theApp->GetPlayerMgr()->GetFarRole() );
	}



	RI->SetRenderState( D3DRS_FOGENABLE, TRUE );

	GetEngine()->GetRenderer()->Flush( eSortByFarZ );

	RI->SetRenderState( D3DRS_FOGENABLE, TRUE );	


#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nRender_DisplayGameMain:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	GetEffectMgr()->Update( dwTime );
	GetEffectMgr()->Render();
	SwGlobal::GetRender()->RenderDoodad();
	MeRenderManager::Instance()->DoRender(false);

	RI->SetRenderState( D3DRS_FOGENABLE, TRUE );	
	MeRenderManager::Instance()->DoRender(true);
	// 	MeRenderManager::Instance()->DoRenderCollector();
	RI->SetRenderState( D3DRS_FOGENABLE, FALSE );

	// Render weather
	WeatherEventManager::Instance()->RenderWeather();

	RI->EndScene();

	// add [5/20/2008 whu]
	RI->SetRenderState( D3DRS_FOGENABLE, FALSE );
	try
	{
		// added, jiayi, [2009.5.10]
		LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
#ifdef RENDER_MRT
		if(PostProcessManager::instance().enableMultiRenderTarget())//支持multi-rt
		{
			pDev->SetRenderTarget( 1, 0 );
		}
#endif // RENDER_MRT


		//if( !SystemSetting::Instance()->IsLowLevelCard() && SystemSetting::Instance()->IsAdvance()  )
		{
			/*RendererDx* meRender = (RendererDx*)RI;
			PostProcessManager::instance().setParameter( "View",  meRender->GetViewMatrix() );
			PostProcessManager::instance().setParameter( "WorldViewProjection",  meRender->GetWorldViewProjection() );
			PostProcessManager::instance().setParameter( "LightPosition", GetSTSkyBox()->GetSunPosition() );
			PostProcessManager::instance().setParameter( "LightDirection", meRender->GetLightDir( LIGHT_INDEX_TERRAIN ) );
			PostProcessManager::instance().setParameter( "CameraPos", meRender->GetEyePt() );*/
			m_PostProcessCost = timeGetTime();
			PostProcessManager::instance().render();
			m_PostProcessCost = timeGetTime() - m_PostProcessCost;
		}

	}
	catch ( const std::exception& e )
	{
		OutputDebugString( e.what() );
	}
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nRender_PostProcessManager:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	RI->BeginScene();
	
	RI->SetRenderState( D3DRS_FOGENABLE, TRUE );	

	Font3DManager::Instance()->Render();
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nRender_Font3DManager:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	GetPlayerMgr()->RenderPlayerTeamFlag();

	ProgressBar3DManager::Get().Render();

	guard(RenderTextEffect);
	if( g_pFlyTextEffect )
	{
		g_pFlyTextEffect->Render();
	}
	if (g_pPrintTextEffect)
	{
		g_pPrintTextEffect->Render(); //lyh++feixingwenzi
	}
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nRender_Display1:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	unguard;

	GetBillBoard()->BillBoardProcess();

	// 渲染玩家聊天泡泡
	GetPlayerMgr()->RenderPlayerChatInfo();

	if( FontSystem::IsUseNewFont() )
		FontSystem::DoRender( FontRender::EFR_SECOND );
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nRender_Display2:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif


	// added, jiayi, [2010/6/21]
	// 保存rt,为shimmer效果所用
	if( !SystemSetting::Instance()->IsLowLevelCard() && SystemSetting::Instance()->IsAdvance()  )
	{
		PostProcessManager::instance().ScretchRectToTexture();

		RI->SetRenderState( D3DRS_FOGENABLE, FALSE );	
		MeRenderManager::Instance()->DoRender(true);
		// 	MeRenderManager::Instance()->DoRenderCollector();
		RI->SetRenderState( D3DRS_FOGENABLE, TRUE );

#if LOAD_COST_TIME_DEBUG
		time_cost = HQ_TimeGetTime() - time_cost;
		if(time_cost > 20)
		{
			char cOutputString[2048];
			MeSprintf_s( cOutputString, 2048, "\nRender_ScretchRectToTexture:%d\n", time_cost );
			OutputDebugStr(cOutputString);
		}
		time_cost = HQ_TimeGetTime();
#endif
	}
	SwGlobal::GetRender()->UnlockModelRes();

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nRender_Display3:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	// 渲染四角
	RenderCornerOverlay();

	// HRUI
	{
		guard(HRUI);
		m_UIRenderCost = 0;
		if( g_bRenderUI )
		{
			TRUETIMEBLOCK( "Render::theUiManager Render" );

			m_UIRenderCost = HQ_TimeGetTime();
			RI->SetRenderState( D3DRS_FOGENABLE, FALSE );	

			{
				CEquipmentDoll::PartType partMain, partMinor;
				switch (thePlayerRole.GetProfession())
                {
                case EArmType_Warrior:
                    {
                        partMain = CEquipmentDoll::ePart_WarriorMain;
                        //partMinor = CEquipmentDoll::ePart_WarriorMinor;
                    }
                    break;
				case EArmType_Assassin:
                    {
                        partMain = CEquipmentDoll::ePart_AssassinMain;
                       // partMinor = CEquipmentDoll::ePart_AssassinMinor;
                    }
                    break;
				case EArmType_Taoist:
                    {
                        partMain = CEquipmentDoll::ePart_TaoistMain;
                      //  partMinor = CEquipmentDoll::ePart_TaoistMinor;
                    }
                    break;
				case EArmType_Mage:
                    {
                        partMain = CEquipmentDoll::ePart_MageMain;
                        //partMinor = CEquipmentDoll::ePart_MageMinor;
                    }
                    break;
				case EArmType_Hunter:
                    {
                        partMain = CEquipmentDoll::ePart_HunterMain;
                       // partMinor = CEquipmentDoll::ePart_HunterMinor;
                    }
                    break;
				}
				thePlayerRole.m_doll.Render( partMain, partMinor );
			}

            CScreenInfoManager::Instance()->Render();   //added by zhuomeng.hu		[11/27/2010]
			theUiManager.Render();
			CUINoobTipManager::Instance()->Render();	//added by ZhuoMeng.Hu		[9/17/2010]
#if LOAD_COST_TIME_DEBUG
			time_cost = HQ_TimeGetTime() - time_cost;
			if(time_cost > 20)
			{
				char cOutputString[2048];
				MeSprintf_s( cOutputString, 2048, "\nRender_UiManager.Render:%d\n", time_cost );
				OutputDebugStr(cOutputString);
			}
			time_cost = HQ_TimeGetTime();
#endif

			// 播放被玩家击打屏幕效果
			if (thePlayerRole.m_isPlayerHitMe)
			{
				RenderPlayerHitMeEffect();
			}

			// 播放好友赠送礼物特效
			if( CGivePresentLogic::Instance().IsPlayGivePresentEffect() )
			{
				CGivePresentLogic::Instance().RenderPlayerGivePresentEffect();
			}

			m_UIRenderCost = HQ_TimeGetTime() - m_UIRenderCost;
		}
		unguard;
	}

	if( FontSystem::IsUseNewFont() )
	{
		FontSystem::ClearRender( FontRender::EFR_SECOND );// second is for will be cleared each frame
		FontRender::getFontRender()->SetDefaultRendererIdx( FontRender::EFR_SECOND );
	}

	guard(RenderTextEffectTopLevel);
	GetShowScreenText()->Render();
	GetShowScreenText()->Render(true);
	unguard;

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nGetShowScreenText()->Render:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	if( FontSystem::IsUseNewFont() )
		FontSystem::DoRender( FontRender::EFR_SECOND );

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nFontSystem::DoRender( FontRender::EFR_SECOND ):%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	MeRenderManager::Instance()->DoRender(true);
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nRender_Display4:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

// 	guard(RenderTextEffectTopLevel);
// 	GetShowScreenText()->Render();
// 	GetShowScreenText()->Render(true);
// 	unguard;
	{
		guard(RenderTips);
		RI->SetRenderState( D3DRS_FOGENABLE, FALSE );
		if (g_RenderTips)
        theUiManager.RenderTips();
		
		s_CUI_ID_FRAME_chatInfoList.RenderTip();

		IconMgrBestEquip::Instance()->Render();

		RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
		unguard;
	}

	theHeroGame.GetDuelTips()->Render();
	theCountryTipInstance.Render();
	// 3D视角操作时非旋转时，或2.5D视角操作并点地行走时，渲染鼠标
	if( !g_bRotateEnable || g_b25DRoleMoveFollowMouse || g_b25DMouseLButtonDownOnTerrain || g_b25DRoleMoveFollowMouseFocusOnUI )
	{
		theMouseManager.Render();
	}
	else
	{
		::SetCursor( NULL );
	}
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nRender_Display5:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	RI->EndScene();
	unguard;
}

void CHeroGame::RenderBeforeGameMainUI( DWORD dwTime )
{
	guardfunc;
	IRenderer* RI = GetEngine()->GetRenderer();
	if ( SUCCEEDED( RI->BeginScene() ) )
	{

		{
			theUiManager.Render();
			//if( g_GameState == G_LOGIN )
			theUiManager.RenderTips();
		}


		if( g_pFlyTextEffect )
		{
			g_pFlyTextEffect->Render();
		}
		GetEngine()->GetRenderer()->Flush( eSortByFarZ );

		if( !g_bRotateEnable )
		{
			theMouseManager.Render();
		}

		RI->EndScene();

		PostProcessManager::instance().render();


		
	}
	SwGlobal::GetRender()->UnlockModelRes();
	unguard;
}

HRESULT	CHeroGame::Render()
{
	guardfunc;
	DWORD	fBeforeOneFrame = HQ_TimeGetTime();
#if LOAD_COST_TIME_DEBUG
	DWORD time_cost = fBeforeOneFrame;
#endif
	if ( !m_pd3dDevice )
	{
		return S_FALSE;
	}

	if( !GetEngine() )
		return S_FALSE;

	MeFreeProfileStart("Interlock");
	if( m_pQueriesInterlock )
		m_pQueriesInterlock->UpdateQueries();
	MeFreeProfileEnd("Interlock");

	IRenderer* RI = GetEngine()->GetRenderer();

	if( !RI )
		return S_FALSE;

	// added, jiayi, [2009.5.5]	
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();


	// 场景过亮 [6/26/2008 whu]
	ZeroMemory( &CPlayerAnim::GlobalMaterial, sizeof(D3DMATERIAL9) );
	CPlayerAnim::GlobalMaterial.Ambient = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	CPlayerAnim::GlobalMaterial.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

	if ( getwsCamera() && getwsCamera()->GetViewPortMain()->Width == 0)
	{
		getwsCamera()->GetViewPortMain()->X = 0;
		getwsCamera()->GetViewPortMain()->Y = 0;
		getwsCamera()->GetViewPortMain()->Width = SCREEN_WIDTH;
		getwsCamera()->GetViewPortMain()->Height = SCREEN_HEIGHT;
		getwsCamera()->GetViewPortMain()->MinZ = 0;
		getwsCamera()->GetViewPortMain()->MaxZ = 1;
	}
	RI->SetViewport( getwsCamera()->GetViewPortMain() );

	if( G_MAIN == g_GameState )
	{
		GetSTSkyBox()->m_bCanRender = TRUE;
	}
	else
	{
		GetSTSkyBox()->m_bCanRender = FALSE;
	}

	if( G_MAIN == g_GameState )
	{
		if( s_CUI_ID_FRAME_LoadMap.IsMapLoaded() )
		{

			CShaderMgr* ShaderMgr=GetShaderMgr();
			if( GetPlayerMgr()->GetMe())
			{		
				D3DXVECTOR3 p = GetPlayerMgr()->GetMe()->GetPos();
				MexInstanceMan::SetPlayerPos(&p);//dynamic grasss
				if(ShaderMgr&&ShaderMgr->GetWaterType() == 2)
				{					
					p.z = /*g_World.GetSkyBoxHeight()* to remove g_World*/GetMe3dConfig()->m_fMdlSpaceScale;						
					m_swRender->RenderLiquidReflect(getwsCamera()->GetMeCamera(), g_fCamerFOV, p, m_world,0,0);
				}				
			}
#if LOAD_COST_TIME_DEBUG
			time_cost = HQ_TimeGetTime() - time_cost;
			if(time_cost > 20)
			{
				char cOutputString[2048];
				MeSprintf_s( cOutputString, 2048, "\nRender_LiquidReflect:%d\n", time_cost );
				OutputDebugStr(cOutputString);
			}
			time_cost = HQ_TimeGetTime();
#endif

			if( GetPlayerMgr()->GetMe() && ShaderMgr&&ShaderMgr->IsCanUseShader() && SystemSetting::Instance()->IsAdvance() )
			{
				if( ShaderMgr->GetShadowType()  == eShadow_RealTime /*&& !SystemSetting::Instance()->IsLowLevelCard()*/  )
				{					

					LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();	

					D3DXVECTOR3 vEyeAt = getwsCamera()->GetMeCamera()->GetEyePt();
					D3DXVECTOR3 vLookat = getwsCamera()->GetMeCamera()->GetLookatPt();
					D3DXVECTOR3 vViewDir = getwsCamera()->GetMeCamera()->GetViewDir();
					RendererDx* pMeRenderer = (RendererDx*)GetEngine()->GetRenderer();
					D3DXVECTOR3 vLightDir = pMeRenderer->GetLightDir( LIGHT_INDEX_TERRAIN );

					graphics::ShaderManager::instance()->beginRenderShadow(vEyeAt, vLookat, vViewDir, vLightDir);
					if(SUCCEEDED(pDev->BeginScene()))
					{
						GetPlayerMgr()->RenderShadow( m_pd3dDevice );	
						pDev->EndScene();

					}
					graphics::ShaderManager::instance()->endRenderShadow();			
				}
			}
			GetPlayerMgr()->ClearPlayerQueue();
#if LOAD_COST_TIME_DEBUG
			time_cost = HQ_TimeGetTime() - time_cost;
			if(time_cost > 20)
			{
				char cOutputString[2048];
				MeSprintf_s( cOutputString, 2048, "\nRender_Shadow:%d\n", time_cost );
				OutputDebugStr(cOutputString);
			}
			time_cost = HQ_TimeGetTime();
#endif
		}

		RI->Clear( 0L, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0, 1.0f, 0L );
		if(g_bRenderSkyBox && s_CUI_ID_FRAME_LoadMap.IsMapLoaded() && SUCCEEDED( RI->BeginScene() ) && GetPlayerMgr() && GetPlayerMgr()->GetMe() )
		{

#ifdef RENDER_MRT
			PostProcessManager::instance().updateMultiRenderTarget();
#endif // RENDER_MRT

			{
				
				FLOAT fAspect = ((FLOAT)SCREEN_WIDTH) / SCREEN_HEIGHT;
				getwsCamera()->GetMeCamera()->SetProjParams( g_fCamerFOV/*D3DX_PI*(30/45.0f)/4*/, fAspect, 1.0f, 100000.0f );
				RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&getwsCamera()->GetMeCamera()->GetProjMatrix() );
				D3DXVECTOR3 p = GetPlayerMgr()->GetMe()->GetPos();

				SwGlobal::GetRender()->RenderSkyBox( m_world, p );	

				getwsCamera()->GetMeCamera()->SetProjParams( g_fCamerFOV, fAspect, m_swRender->GetNearPlane(), m_swRender->GetFarPlane() );
				RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&getwsCamera()->GetMeCamera()->GetProjMatrix() );
				RI->EndScene();
			}



		}	
		else
		{
			FogProperty* pFogProp = m_swRender->GetFogProperty();
			RI->Clear( 0L, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER ,
				D3DCOLOR_ARGB(255,(int)(pFogProp->kFogColor.r * 255.f),
				(int)(pFogProp->kFogColor.g * 255.f),
				(int)(pFogProp->kFogColor.b * 255.f)), 1.0f, 0L );

		}
#if LOAD_COST_TIME_DEBUG
		time_cost = HQ_TimeGetTime() - time_cost;
		if(time_cost > 20)
		{
			char cOutputString[2048];
			MeSprintf_s( cOutputString, 2048, "\nRender_SkyBox:%d\n", time_cost );
			OutputDebugStr(cOutputString);
		}
		time_cost = HQ_TimeGetTime();
#endif

		BOOL bUpDateNight = FALSE;
		if( GetMe3dConfig()->IsShowFog() )
		{
			RI->SetRenderState( D3DRS_FOGENABLE, FALSE );
		}
		else
		{
			RI->SetRenderState( D3DRS_FOGENABLE, FALSE );
		}
	}
	else
	{
		RI->Clear( 0L, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0, 1.0f, 0L );
	}

	Config::FrameUpdated( true );	

	// added, jiayi, [2009.4.27]
	GetEngine()->GetRenderer()->SetEyePt( (float*)Config::GetCamera()->GetEyePt() );

    //CMovieManager::Instance()->Render( false );

	switch( g_GameState )
	{
	case G_MAIN:
		{
			RenderGameMain( HQ_TimeGetTime() );

#if LOAD_COST_TIME_DEBUG
			time_cost = HQ_TimeGetTime() - time_cost;
			if(time_cost > 20)
			{
				char cOutputString[2048];
				MeSprintf_s( cOutputString, 2048, "\nRender_RenderGameMain:%d\n", time_cost );
				OutputDebugStr(cOutputString);
			}
			time_cost = HQ_TimeGetTime();
#endif
			// 统计
			m_TotalFrame++;
			m_UIRenderTotal += m_UIRenderCost;
			m_PlayerRenderTotal += m_PlayerRenderCost;
			m_GrassRenderTotal += m_swRender->GetDoodadRenderTime();
			m_ChunkRenderTotal += m_swRender->GetChunkRenderTime();
			m_LiquidRenderTotal += m_LiquidRenderCost;
			m_ModelRenderTotal += m_swRender->GetModelRenderTime();
			m_AllRenderTotal += m_OneFrameDisplayCost;
		}
		break;
	default:
		{
			RenderBeforeGameMainUI( HQ_TimeGetTime() );
		}
		break;
	}

	// added by zhuomeng.hu		[2/25/2011]
    CMovieManager::Instance()->Render( true );

	if((g_bShowFps || g_bDebugPos) && SUCCEEDED( RI->BeginScene() ) )
	{
		int nLine = 150;
		int fontsize = 3;
		if( g_bShowFps )
		{
			FontRender::EFontRenders eOldIdx = FontRender::EFR_FIRST;
			if( FontSystem::IsUseNewFont() )
			{
				eOldIdx = FontRender::getFontRender()->GetDefaultRendererIdx();
				FontRender::getFontRender()->SetDefaultRendererIdx( FontRender::EFR_THIRD );
				FontSystem::ClearRender( FontRender::EFR_THIRD );
			}
			TCHAR strPerformanceText[256] = {0};
			// 显卡类型，当前帧数，显存
			DDSCAPS2 ddscaps2;
			DWORD VideoMemory=-1;
			DWORD Temp=0;
			memset( &ddscaps2, 0, sizeof(ddscaps2) );
			ddscaps2.dwCaps = DDSCAPS_VIDEOMEMORY;
			DWORD dwTotal=0;
			DWORD dwFree=0;

			// lp_DD points to the IDirectDraw object
			HRESULT hr;
			// Test the cooperative level to see if it's okay to render
			hr = m_pd3dDevice->TestCooperativeLevel();
			if( m_pDDobject && hr == D3D_OK )
			{
				HRESULT hr = m_pDDobject->GetAvailableVidMem(&ddscaps2, &dwTotal, &dwFree);
				_stprintf(strPerformanceText, "Info\n%s\nVideo Memory: %d MB, Used: %d MB", m_strDeviceStats,
					dwTotal / 1000000, ( dwTotal - dwFree ) / 1000000);
			}
			else
				_stprintf(strPerformanceText, "Info\n%s\n%s\n", m_strDeviceStats, m_strFrameStats);
			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xffffffff, fontsize, false );
			nLine += 25;
			_stprintf( strPerformanceText, "Fps: %s, 显卡配置:%s", m_strFrameStats,
				SystemSetting::Instance()->IsLowLevelCard() ? "低" : "高");
			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xffffffff, fontsize, false );
			nLine += 25;

			//_stprintf(strPerformanceText, "Character Count: %d, Vertex: %d, Face:%d", 
			//	GetPlayerMgr()->GetRenderPlayerCount(),
			//	GetPlayerMgr()->GetRenderPlayerVertexCount(),
			//	GetPlayerMgr()->GetRenderPlayerFaceCount() );
			//FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
			//nLine += 25;
			//_stprintf(strPerformanceText, "Model(Sub) Count: %d( %d), Vertex: %d, Face: %d", 
			//	m_swRender->GetModelCount(),
			//	m_swRender->GetSubmodelCount(),
			//	m_swRender->GetModelVertexCount(),
			//	m_swRender->GetModelFaceCount() );
			//FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
			//nLine += 25;
			//_stprintf(strPerformanceText, "Terrain Count: %d, Vertex: %d, Face: %d", 
			//	m_swRender->GetChunkCount(),
			//	m_swRender->GetChunkVertexCount(),
			//	m_swRender->GetChunkFaceCount()	);
			//FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
			//nLine += 35;


			if(m_PlayerRenderCost > m_PlayerMaxCost)
				m_PlayerMaxCost = m_PlayerRenderCost;
			
 			_stprintf(strPerformanceText, "角色更新时间: %dms, 角色渲染时间: %dms ,角色数量%d个,最高耗时：%d\n, ", m_PlayerUpdateCost,m_PlayerRenderCost,GetPlayerMgr()->GetRenderPlayerCount(),m_PlayerMaxCost);	
 			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
 			nLine += 25;

			if(m_swRender->GetModelRenderTime() > m_SceneUpdateMaxCost)
                m_SceneUpdateMaxCost = m_swRender->GetModelRenderTime();

			//场景模型的更新时间 m_TotalFrame m_ModelRenderTotal
 			_stprintf(strPerformanceText, "场景更新时间: %dms, 最高耗时：%d\n", m_swRender->GetModelRenderTime(),m_SceneUpdateMaxCost);
 			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
 			nLine += 25;


			if (m_swRender->GetSceneModeRealRenderTime() > m_SceneRenderMaxCost)
			{
				m_SceneRenderMaxCost=m_swRender->GetSceneModeRealRenderTime();
			}
			
			//场景模型的渲染时间
			_stprintf(strPerformanceText, "场景渲染时间: %dms ,场景数量 %d个 ,子集数量 %d个，最高耗时：%d\n", m_swRender->GetSceneModeRealRenderTime(),m_swRender->GetModelCount(),m_swRender->GetSubmodelCount(),m_SceneRenderMaxCost);
			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
			nLine += 25;


			
			if (m_swRender->GetChunkRenderTime() > m_TerrainRenderMaxCost)
			{
				m_TerrainRenderMaxCost = m_swRender->GetChunkRenderTime();
			}

			//地形的渲染时间
 			_stprintf(strPerformanceText, "地形渲染时间: %dms ,最高耗时%d\n", m_swRender->GetChunkRenderTime(),m_TerrainRenderMaxCost);	
 			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
 			nLine += 25;


			if(m_swRender->GetDoodadRenderTime() > m_DoodadRenderMaxCost)
			{
              m_DoodadRenderMaxCost = m_swRender->GetDoodadRenderTime();
			}

 			_stprintf(strPerformanceText, "草渲染时间: %dms 最高耗时%d\n,", m_swRender->GetDoodadRenderTime(),m_DoodadRenderMaxCost);
 			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
 			nLine += 25;

			if (m_LiquidRenderCost > m_LiquidRenderMaxCost)
			{
				m_LiquidRenderMaxCost = m_LiquidRenderCost;
			}


 			_stprintf(strPerformanceText, "水面渲染时间: %dms ,最高耗时%d\n,", m_LiquidRenderCost,m_LiquidRenderMaxCost);
 			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
 			nLine += 25;

			if ( m_swRender->GetEffectRenderTime() > m_EffectRenderMaxCost)
			{
				m_EffectRenderMaxCost = m_swRender->GetEffectRenderTime();
			}
 			_stprintf( strPerformanceText, _T("特效数量: %d, 特效渲染时间: %dms ,最高耗时%d\n"),m_swRender->GetEffectCount(), m_swRender->GetEffectRenderTime(),m_EffectRenderMaxCost ); 
 			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
 			nLine += 25;


		
			if (m_UIRenderCost > m_UIRenderMaxCost)
			{
				m_UIRenderMaxCost = m_UIRenderCost;
			}
		
 			_stprintf(strPerformanceText, "UI更新时间: %dms, UI渲染时间: %dms ,最高耗时%d\n", m_UIUpdateCost,m_UIRenderCost,m_UIRenderMaxCost);
 			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
 			nLine += 25;

			if (m_PostProcessCost > m_PostProcessMaxCost)
			{
				m_PostProcessMaxCost = m_PostProcessCost;
			}
			_stprintf(strPerformanceText, "后置处理时间: %dms ,最高耗时：%d\n", m_PostProcessCost,m_PostProcessMaxCost);
			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
			nLine += 25;

			// 网络
			//_stprintf( strPerformanceText, _T("Ping: %d"), GetPlayerMgr()->GetGamePing());
			//FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
			//nLine += 25;

			/*_stprintf( strPerformanceText, _T("NetIn AVG: %dB, Max: %dB"), g_Statistics.iInAvgPerSecond, g_Statistics.iInMaxPerSecond);
			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
			nLine += 25;
			_stprintf( strPerformanceText, _T("NetOut AVG: %dB, Max: %dB"), g_Statistics.iOutAvgPerSecond, g_Statistics.iOutMaxPerSecond);
			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
			nLine += 25;

			_stprintf( strPerformanceText, _T("Net Update time: %dms, Net Update Max: %dms")
				,m_NetCost, m_NetCostMax);
			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
			nLine += 45;*/

			// 声音
// 			float fDsp;
// 			float fStream;
// 			float fUpdate;
// 			float fTotal;
// 			GSound.GetSoundCPUUsage( &fDsp, &fStream, &fUpdate, &fTotal );
// 			_stprintf( strPerformanceText, _T("SoundCPUUsage: Dsp %.02f%% Stream %.02f%% Update %.02f%% Total %.02f%%"),
// 				fDsp, fStream, fUpdate, fTotal );
// 			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
// 			nLine += 25;
// 			TCHAR m_strInMemorySoundFileCount[256];
// 			m_strInMemorySoundFileCount[0]  = _T('\0');
// 			int nFinderSize;
// 			int nListSize;
// 			GSound.GetInMemorySoundFileCount( &nFinderSize, &nListSize );
// 			_stprintf( m_strInMemorySoundFileCount, _T("SoundFileInMemorySize: Finder %d List %d"),
// 				nFinderSize, nListSize );
// 			FontSystem::DrawText( m_strInMemorySoundFileCount, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
// 			nLine += 40;
// 
 			_stprintf( strPerformanceText, _T("总顶点数: %d, 总面数: %d"), 
 				m_swRender->GetChunkVertexCount() + m_swRender->GetModelVertexCount() + GetPlayerMgr()->GetRenderPlayerVertexCount(),
 				m_swRender->GetChunkFaceCount() + m_swRender->GetModelFaceCount() + GetPlayerMgr()->GetRenderPlayerFaceCount() );
 			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xffff0000, fontsize, false );
 			nLine += 25;

			m_OneFrameDisplayCost = HQ_TimeGetTime() - fBeforeOneFrame;
			_stprintf(strPerformanceText, "当前帧时间: %dms\n", m_OneFrameDisplayCost);
			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xff00ff00, fontsize, false );
			nLine += 25;
 
// 			_stprintf(strPerformanceText, "Total Update: %02dms, Render: %dms, Render AVG: %.1fms\n", 
// 				m_FrameMoveCost+m_NetCost,
// 				m_OneFrameDisplayCost,
// 				m_AllRenderTotal*1.f/m_TotalFrame );
// 			FontSystem::DrawText( strPerformanceText, 0, nLine, DT_NOCLIP, 0xffff0000, fontsize, false );
// 
// 			UpdateNetStreamLog( nLine );

			if( FontSystem::IsUseNewFont() )
			{
				FontRender::getFontRender()->SetDefaultRendererIdx( eOldIdx );
				FontSystem::DoRender( FontRender::EFR_THIRD );
			}	
		}

		if( g_bDebugPos )
		{
			TCHAR m_strFrameStats [128] = {0};
			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
			if( pMe && m_world && m_world->GetWorldBuffer()&& m_world->GetWorldBuffer()->GetActiveTile() )
			{
				sprintf( m_strFrameStats, "World MapID: %d, Pos: %0.3f %0.3f %0.3f",
					m_world->GetWorldBuffer()->GetActiveTile()->GetMapId(),
					(float)pMe->GetPos().x,
					(float)pMe->GetPos().y,
					(float)pMe->GetPos().z);
				nLine += 25;
				FontSystem::DrawText( m_strFrameStats, 0, nLine, DT_NOCLIP, 0xffffffff, fontsize, false );
			}
		}
		RI->EndScene();
	}

	////////////////////////////
	
	{
		BOOL bNeedDelay = TRUE;
		if( !s_CUI_ID_FRAME_LoadMap.IsMapLoaded() )
			bNeedDelay = FALSE;
		GetMexResMgr()->ClearDestroyingRes(bNeedDelay);
	}

	return S_OK;
	unguard;
}

extern CUI_ChatInfoBox s_CUI_ChatInfoBox;
void PrintDebugInfo( DWORD dwType,  const char* string, ... )
{
	guardfunc;
	if( !string )
		return;
	int nLength = strlen( string );
	if ( nLength <=0 )
		return;

	va_list	va;
	static char data[1024];
	va_start( va, string );
	wvsprintf( (char*)data, string, va );
	va_end( va );

	s_CUI_ChatInfoBox.AddInfo(std::string("调试信息:") + data, 0xffffffff);
	unguard;
}

BOOL CHeroGame::GetMousePickXY( float &x, float &y, int &nMouseXOffset, int &nMouseYOffset )
{
	guardfunc;
	POINT ptMouse;

	GetCursorPos( &ptMouse );
	ScreenToClient( g_hhWnd, &ptMouse );

	nMouseXOffset = ptMouse.x - SCREEN_WIDTH*0.5;
	nMouseYOffset = ptMouse.y - SCREEN_HEIGHT*0.5;
	x = ptMouse.x;
	y = ptMouse.y;

	return PickFromTerrain( x, y );
	unguard;
}

BOOL CHeroGame::PickFromTerrain( float &x, float &y )
{
	guardfunc;

	D3DXVECTOR3 vStart;
	D3DXVECTOR3 vDir;

	getwsCamera()->GetMeCamera()->BuildPickRay( x, y, vStart,vDir, SCREEN_WIDTH, SCREEN_HEIGHT );
	bool bPicked = false;
	{
		TPickResult pickResult;
		g_PickedZFromMouse = WORLD_HEIGHT;
		if( SwGlobal::GetWorldPicker() && SwGlobal::GetWorldPicker()->Pick(Vector(vStart.x, vStart.y
			,vStart.z), Vector(vDir.x, vDir.y, vDir.z), pickResult,emPT_Terrain|emPT_FloorObj,true,m_swRender->GetFogProperty()->fFogFar))
		{
			x = pickResult.pickResultInfo[0].point.x;
			y = pickResult.pickResultInfo[0].point.y;
			g_PickedZFromMouse = pickResult.pickResultInfo[0].point.z;
			bPicked = true;
		}
		CWorldTile* pCurrTile = CURRENTTILE;
		if(pCurrTile&& pCurrTile->ReachableMap().CanReach(swVec2f(x,y)))
			return TRUE;
		// 如果与场景模型有交点
		if (SwGlobal::GetWorldPicker()->Pick(Vector(vStart.x, vStart.y
			,vStart.z), Vector(vDir.x, vDir.y, vDir.z), pickResult,emPT_CollisionObj,true,m_swRender->GetFogProperty()->fFogFar))
		{
			bool IsUseCollision = true;
			D3DXVECTOR3 vCollisionPos = D3DXVECTOR3(pickResult.pickResultInfo[0].point.x,
				pickResult.pickResultInfo[0].point.y,
				pickResult.pickResultInfo[0].point.z);
			if (bPicked)
			{
				D3DXVECTOR3 vTerrainPickPos = D3DXVECTOR3(x,y,g_PickedZFromMouse);
				float fDistToTerrain = D3DXVec3Length( &( vTerrainPickPos - vStart ) );
				float fDistToCollision = D3DXVec3Length( &( vCollisionPos - vStart ) );
				if (fDistToCollision > fDistToTerrain)
				{
					IsUseCollision = false;
				}
			}
			if (IsUseCollision && GetPlayerMgr()->GetMe())
			{
				D3DXVECTOR3 MyPos = GetPlayerMgr()->GetMe()->GetPos();
				D3DXVECTOR3 MeToCollision = vCollisionPos - MyPos;

				float pProjectionDist = sqrtf(MeToCollision.x*MeToCollision.x + MeToCollision.y*MeToCollision.y);
				if(pProjectionDist > 0.500001)
				{
					D3DXVECTOR2 vecNormal(pickResult.pickResultInfo[0].normal.x,pickResult.pickResultInfo[0].normal.y);
					float vecLength = sqrtf(vecNormal.x*vecNormal.x + vecNormal.y*vecNormal.y);
					if (abs(vecLength) < 0.00001)
					{
					}
					else
					{
						vecNormal.x = vecNormal.x/vecLength;
						vecNormal.y = vecNormal.y/vecLength;
						x = vCollisionPos.x + vecNormal.x/2;
						y = vCollisionPos.y + vecNormal.y/2;
					}
				}
				else
				{
					x = MyPos.x ;
					y = MyPos.y ;
				}
				g_PickedZFromMouse = pickResult.pickResultInfo[0].point.z;
			}
			bPicked = true;
		}
	}
	return bPicked;
	unguard;
}

LRESULT	CHeroGame::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	guardfunc;
	g_hhWnd = hWnd;

	if( m_world && m_world->GetWorldBuffer() && !s_CUI_ID_FRAME_LoadMap.IsMapLoaded()/*m_world->IsLoading()*/ &&
		( uMsg == WM_KEYDOWN || uMsg == WM_KEYUP || uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP || uMsg == WM_CLOSE/* || uMsg == WM_USER_CLOSE/*) )
		return S_OK;

	if( thePlayerRole.IsShowingWaitforTransport() && (uMsg == WM_CLOSE/* || uMsg == WM_USER_CLOSE*/ ) )
		return S_OK;

	if ( ( s_CUI_ID_FRAME_LOGIN.IsLogining() || s_CUI_ID_FRAME_Select.GetEnterWorldState()/*UI_ID_FRAME_SELECT::m_isEnterWorld*/ ) && (uMsg == WM_CLOSE/* || uMsg == WM_USER_CLOSE*/) )
		return S_OK;

	if (GetBillBoard()->MsgProc(hWnd,uMsg,wParam,lParam))
	{
		return S_OK;
	}

	if( uMsg == WM_MOUSEMOVE )
	{
		if ( s_CUI_ChatInfoBox.FreeTipMoveProc( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) ) )
		{
			return S_OK;
		}

		// 特殊要求导致的特殊写法
		IconMgrBestEquip::Instance()->SetVisable( false );
		s_CUI_ID_FRAME_FriendView.SetVisable(false);
		s_CUI_ID_FRAME_Sprite.SetVisable(false);
		if ( g_bMouseLeave )
		{
			return S_OK;
		}
	}

	if( uMsg == WM_LBUTTONDOWN )
	{

		if ( s_CUI_ChatInfoBox.FreeTipMoveBeginProc( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) ) )
		{
			return S_OK;
		}

		if ( s_CUI_ChatInfoBox.PtInAllFreeTipBtn( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) ) > -1 )
		{
			return S_OK;
		}

	}
	else if (uMsg == WM_LBUTTONUP)
	{
		// added, jiayi, [2009/9/29]
		g_bMouseLeave = false;
		s_CUI_ID_FRAME_chatInfoList.SetChangeSize(false);
		g_dw25DLButtonDownStartTime = 0;
		g_b25DRoleMoveFollowMouse = FALSE;
		//g_b25DMouseLButtonDownOnTerrain = FALSE;
		/*if (s_CUI_ChatInfoBox.m_FreeTip.PtInCloseBtn(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)))
		{
			s_CUI_ChatInfoBox.m_FreeTip.ShowItemTip( false );
			return true;
		}*/

		int idx = s_CUI_ChatInfoBox.PtInAllFreeTipBtn( GET_X_LPARAM( lParam ),GET_Y_LPARAM( lParam ) );
		if ( idx > -1 )
		{
			s_CUI_ChatInfoBox.m_AllFreeTip[idx].ShowItemTip( false );
			// 清理下记录的ID号(中，左，右用的)
			s_CUI_ChatInfoBox.ClearNoteId( idx );
			// 清理下记录的显示排序ID
			s_CUI_ChatInfoBox.FreeTipEraseStack( idx );

			return S_OK;
		}

		if ( s_CUI_ChatInfoBox.FreeTipMoveEndProc( GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) ) )
		{
			return S_OK;
		}

	/*	if (chatMessageManage.IsPtInCloseBtn(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)))
		{
			return S_OK;
		}*/
	}

	// 只把WM_CHAR，WM_LBUTTONDBLCLK，WM_RBUTTONDBLCLK传入theUiManager，其他都在ProcessInput传入
	if( uMsg == WM_CHAR || ((uMsg == WM_KEYDOWN || uMsg == WM_KEYUP) 
		&& (wParam == VK_RETURN || wParam == VK_LEFT || wParam == VK_RIGHT || wParam == VK_DELETE) ) ||
		uMsg == WM_LBUTTONDBLCLK || uMsg == WM_RBUTTONDBLCLK || uMsg == WM_MOUSEMOVE )	
	{
		guard(UI_Msg);
		if ( theUiManager.MsgProc( hWnd, uMsg, wParam, lParam ) == true )
		{
			if( getwsCamera()->GetLock45DegreeCameraMode() && uMsg == WM_MOUSEMOVE )
			{
				g_dw25DLButtonDownStartTime = 0;
				// 2.5D操作，人物跟随鼠标移动时，鼠标移动到UI上
				if(g_bMouseLButtonIsDown && (g_b25DMouseLButtonDownOnTerrain || g_b25DRoleMoveFollowMouse ))
				{
					g_b25DRoleMoveFollowMouseFocusOnUI = TRUE;
					g_b25DMouseLButtonDownOnTerrain = FALSE;
					g_b25DRoleMoveFollowMouse = FALSE;
				}
			}
			return S_OK;
		}
		else if( getwsCamera()->GetLock45DegreeCameraMode() && uMsg == WM_MOUSEMOVE  && g_bMouseLButtonIsDown )
		{
			// 2.5D操作，人物跟随鼠标移动时，鼠标从UI上返回地面
			if( g_b25DRoleMoveFollowMouseFocusOnUI )
			{
				g_b25DRoleMoveFollowMouseFocusOnUI = FALSE;
				g_b25DMouseLButtonDownOnTerrain = TRUE;
				g_dw25DLButtonDownStartTime = HQ_TimeGetTime();
			}
		}
		unguard;
	}
	//}

	//--
	switch( uMsg )
	{
	case WM_KEYDOWN:
		{
			if (wParam == VK_F5 && !g_strViewerUIFilename.empty())
			{
				DWORD dwResult = theUiManager.AddFrame( g_strViewerUIFilename.c_str() );
				if ( dwResult == 0 )
				{
					MessageBoxA(0, "读取文件失败！", "UI Viewer", MB_OK|MB_ICONERROR);
				}
			}

			if (gCfg.m_bUiViewer)
			{
				if (wParam == VK_F6)
				{
					TCHAR Buffer[256] = {0};
					GetCurrentDirectory(256, Buffer);

					OPENFILENAME ofn;       // common dialog box structure
					char szFile[260];       // buffer for file name

					// Initialize OPENFILENAME
					ZeroMemory(&ofn, sizeof(ofn));
					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = NULL;
					ofn.lpstrFile = szFile;
					//
					// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
					// use the contents of szFile to initialize itself.
					//
					ofn.lpstrFile[0] = '\0';
					ofn.nMaxFile = sizeof(szFile);
					ofn.lpstrFilter = "MEUI files\0*.meui\0";
					ofn.nFilterIndex = 1;
					ofn.lpstrFileTitle = NULL;
					ofn.nMaxFileTitle = 0;
					ofn.lpstrInitialDir = NULL;
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

					// Display the Open dialog box. 

					if (GetOpenFileName(&ofn))
					{
						SetCurrentDirectory(Buffer);
						g_strViewerUIFilename = szFile;

						DWORD dwResult = theUiManager.AddFrame( g_strViewerUIFilename.c_str() );
						if ( dwResult == 0 )
						{
							MessageBoxA(0, "读取文件失败！", "UI Viewer", MB_OK|MB_ICONERROR);
						}
					}
				}
			}
			else
			{


				guard(Key);
				if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_HideUI))
				{
					g_bRenderUI = !g_bRenderUI;
				}
				unguard;

			}

		}
		break;
	case WM_KEYUP:
		{
			guard(WM_KEYUP);
			SetCapture( hWnd );
			switch( wParam )
			{
			case VK_TAB:
				ReleaseCapture();
				break;
			}

			if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_PrintScreen) && m_pd3dDevice)
			{
				LPDIRECT3DSURFACE9 pBackBuffer;
				m_pd3dDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );
				char buf[128] = {0};
				char s[512] = {0};
				char file[128] = {0};

				CreateDirectory("Screenshots",NULL);
				MeSprintf_s(file, 127, "%d-%02d-%02d %02d-%02d-%02d.bmp", TimeEx::GetCurrentTime().GetYear(), TimeEx::GetCurrentTime().GetMonth(),
					TimeEx::GetCurrentTime().GetDay(), TimeEx::GetCurrentTime().GetHour(), TimeEx::GetCurrentTime().GetMinute(), TimeEx::GetCurrentTime().GetSecond());
				MeSprintf_s( buf, 127, "Screenshots\\%s", file);
				D3DXSaveSurfaceToFile( buf, D3DXIFF_BMP, pBackBuffer, NULL, NULL );
				if( g_GameState == G_MAIN )
				{
					MeSprintf_s( s, 511, theXmlString.GetString(eText_ScreenshotSaved), file );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, s );
				}
				if (pBackBuffer)
				{
					pBackBuffer->Release();
					pBackBuffer=NULL;
				}
			}
			unguard;
		}
		break;
	case WM_KILLFOCUS:
		{
			guardfunc(WM_KILLFOCUS);
			g_bFocusWindow = false;
			if (isActive)
			{
				m_fMusicVolume = GMusic.m_fSoundVal;
				m_fSoundVolume = GSound.m_fSoundVal;
				GMusic.SetVolume(0.f);
				GSound.SetVolume(0.f);
				isActive = false;
			}
			if(!g_bMouseRButtonIsDown)
			g_bMouseRButtonIsDown = FALSE;


			g_bMouseLButtonIsDown = FALSE;
			m_nCurrKeyChangeNum = 0;
			memset(m_CurrKeyStates, 0, sizeof(BOOL)*256);
			if( g_GameState == G_MAIN )
			{
				
				g_bRotateEnable = FALSE;
				getwsCamera()->SetCameraRotateZBuf(0);
				getwsCamera()->SetCameraRotateXBuf(0);
				if(!g_bMouseRButtonIsDown)//lyh++鼠标右键锁区域
				{
					ClipCursor( NULL );
					ReleaseCapture();
					//OutputDebugString("鼠标位置清空2\n");
				}
				
				m_shCur25Direction = EMD_NONE;
				if( g_b25DRoleMoveFollowMouse )
				{
					g_b25DRoleMoveFollowMouse = FALSE;
					theMouseManager.SetCursor(MouseManager::Type_Arrow);
				}
				g_b25DMouseLButtonDownOnTerrain = FALSE;
				g_b25DRoleMoveFollowMouse = FALSE;
				g_b25DRoleMoveFollowMouseFocusOnUI = FALSE;
			}
			unguard;
		}

		break;
	case WM_SETFOCUS:
		{
			guardfunc(WM_SETFOCUS);
			g_bFocusWindow = true;
			if (!isActive)
			{
				GMusic.SetVolume(m_fMusicVolume);
				GSound.SetVolume(m_fSoundVolume);
				isActive = true;
			}
			g_bMouseLButtonIsDown = FALSE;
			if(!g_bMouseRButtonIsDown)
			g_bMouseRButtonIsDown = FALSE;
			m_nCurrKeyChangeNum = 0;
			memset(m_CurrKeyStates, 0, sizeof(BOOL)*256);
			if( g_GameState == G_MAIN )
			{
				
				g_bRotateEnable = FALSE;
				getwsCamera()->SetCameraRotateZBuf(0);
				getwsCamera()->SetCameraRotateXBuf(0);
				if(!g_bMouseRButtonIsDown)//lyh++鼠标右键锁区域
				{
					ReleaseCapture();
					ClipCursor( NULL );
					//OutputDebugString("鼠标位置清空12\n");
				}
				
				m_shCur25Direction = EMD_NONE;
				if( g_b25DRoleMoveFollowMouse )
				{
					g_b25DRoleMoveFollowMouse = FALSE;
					theMouseManager.SetCursor(MouseManager::Type_Arrow);
				}
				g_b25DMouseLButtonDownOnTerrain = FALSE;
				g_b25DRoleMoveFollowMouse = FALSE;
				g_b25DRoleMoveFollowMouseFocusOnUI = FALSE;
			}
			unguard;
		}

		break;
	case WM_ERASEBKGND:
		return TRUE;
		break;
	case WM_COMMAND:
		break;
	case WM_CLOSE:
		break;
	case WM_USER_CLOSE:
		{
			if (!g_bCloseApp)
			{
				if (isDetectInvalidPlus)
				{
					CUI_ID_FRAME_ExitGame::TellExitGame(true,NULL);
				}
				else
				{
					if( g_GameState == G_MAIN )
						s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eIsExitGame), theXmlString.GetString(eClient_AddInfo_2slk_16),
						CUI_ID_FRAME_MessageBox::eTypeYesNo, true,CUI_ID_FRAME_ExitGame::ExitGameCountDown);
					else
						s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eIsExitGame), theXmlString.GetString(eClient_AddInfo_2slk_16),
						CUI_ID_FRAME_MessageBox::eTypeYesNo, true,CUI_ID_FRAME_ExitGame::TellExitGame);
				}
				UiDrawer::StartFillFullScreen( 500, true );
				return 0;
			}
			else
			{
				MsgExit msg;
				GettheNetworkInput().SendMsg(&msg);
				//GettheNetworkInput().CheckSendReq();

				SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)(INT_PTR)(m_iDefaultMouseSpeed), 0);
			}

			break;
		}
	case WM_SYSKEYUP:
		{
			switch(wParam)
			{
			case VK_MENU:
				{
					if (s_CUI_ID_FRAME_GameSetup.GetShowItemName())
					{
						s_CUI_ID_FRAME_GameSetup.SetShowItemName(false);
					}
					else
					{
						s_CUI_ID_FRAME_GameSetup.SetShowItemName(true);
					}

					if (s_CUI_ID_FRAME_GameSetup.IsVisable())
					{
						s_CUI_ID_FRAME_GameSetup.RefreshUI();
					}
				}
				break;
			default:
				break;
			}
		}
	case WM_ACTIVATEAPP:
		{
			if (wParam == FALSE)
				SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)(INT_PTR)(m_iDefaultMouseSpeed), 0);
			else
				SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)(INT_PTR)(s_CUI_ID_FRAME_GameSettingMouse.GetMouseSpeed()), 0);

			if (!g_strViewerUIFilename.empty())
			{
				DWORD dwResult = theUiManager.AddFrame( g_strViewerUIFilename.c_str() );
				if ( dwResult == 0 )
				{
					MessageBoxA(0, "读取文件失败！", "UI Viewer", MB_OK|MB_ICONERROR);
				}
			}
			break;
		}
	case WM_MOUSELEAVE:
		g_bMouseLeave = TRUE;
		g_bMouseLButtonIsDown = FALSE;
		break;
	case WM_NCHITTEST:
		g_bMouseLeave = FALSE;
		break;

	case WM_MOVE:
		s_CUI_ID_FRAME_FirstCreate.OnGameWindowMove(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_SYSCOMMAND:
		// Prevent moving/sizing and power loss in fullscreen mode
		switch( wParam )
		{
		case SC_CLOSE:
			{
#ifndef _DEBUG
				if (g_GameState == G_MAIN)
				{
					// 如果已经进入游戏了, 弹出确认退出界面
					s_CUI_ID_FRAME_ExitTip.SetVisable( true );
					s_CUI_ID_FRAME_ExitTip.RefreshInfo();
				}
				else
#endif
				{
					ShowWindow( hWnd, SW_HIDE );
					Cleanup3DEnvironment();
					DestroyMenu( GetMenu(hWnd) );
					DestroyWindow( hWnd );
				}
				return 0;
			}
			break;
		}
		break;

	default:
		break;
	}
	return CMyD3DApplication::MsgProc( hWnd, uMsg, wParam, lParam );
	unguard;
}

BOOL CHeroGame::LoadLand( int iLandID, int nMeX, int nMeY )
{
	guardfunc;	

	// 设置为2.5D视角
	if (getwsCamera())
	{
		CUserData::Instance()->SetViewSet(0);
		getwsCamera()->Set45DegreeCameraMode(true);
	}

	if( !GetPlayerMgr() )
	{
		return FALSE;
	}

	CWorldTile* pTile = CURRENTTILE;
	if ( pTile && pTile->GetPointSoundPlay())
	{
		pTile->SetPointSoundPlay(false);
		CResMgr* pResMgr = pTile->GetCResMgr();
		for (int i = 0; i < pResMgr->GetSoundPointCount(); ++i)
		{
			CSoundPointRes* pSoundRes = pResMgr->SoundPoint(i);
			string strFullPath(CWorld::GetAppDataCharDir());
			strFullPath += '\\';
			strFullPath += pSoundRes->GetMuiscPath();
			GSound.ReleaseSound((char*)strFullPath.c_str());
		}
	}
	getwsCamera()->ClearCollideTree();

	theUiManager.SetFocus(NULL);

	guard(test0);
	if( GetPlayerMgr()->GetMe() )
	{
		GetPlayerMgr()->GetMe()->SetMoving( FALSE );
		GetPlayerMgr()->GetMe()->StopJump();
	}
	GetPlayerMgr()->AutoControlClear();
	unguard;

	DWORD dwTick= HQ_TimeGetTime();

	CWorldTile* pWorldTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(iLandID);
	guard(test3);
	if( !pWorldTile )
	{
		assert( pWorldTile != NULL && "cannot open map file" );
		::SendMessage( g_hWnd, WM_USER_CLOSE/*WM_CLOSE*/, 0, 0 );
		return FALSE;
	}
	unguard;

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      天空盒", GetCurrentThreadId() );
	// change skybox
	char szLandID[256];
	itoa( iLandID, szLandID, 10 );
	//if( GetSTSkyBox() && GetSTSkyBox()->GetSkybox() )
	//	GetSTSkyBox()->GetSkybox()->ChangeAvatarSetting( szLandID );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      天气效果", GetCurrentThreadId() );
	guard(test4);
	if( GetPlayerMgr() ) 
	{
		GetPlayerMgr()->m_szPlayMapEffect = pWorldTile->GetEffectPath();
		GetPlayerMgr()->m_bPlayMapEffect = (GetPlayerMgr()->m_szPlayMapEffect.size() != 0);
		CPlayer* pPlayer = GetPlayerMgr()->GetMe();
		if( pPlayer )
		{
			// 删除旧的天气效果
			if( pPlayer->GetMapEffectId() != -1 )
			{
				IEffect *pEffect = GetEffectMgr()->GetEffect( pPlayer->GetMapEffectId());
				if( pEffect )
				{
					pEffect->SetDead();
				}
				pPlayer->SetMapEffectId(-1);
			}
		}
		if( pPlayer && GetPlayerMgr()->m_bPlayMapEffect && GetMe3dConfig()->IsPlayMapEffect() )
		{
			int nEffect = PlayEffect( (char*)GetPlayerMgr()->m_szPlayMapEffect.c_str(), pPlayer );
			pPlayer->SetMapEffectId(nEffect);
		}

		
		GetPlayerMgr()->LoadMonsterConfig(pWorldTile);
	}
	unguard;

	guard(test5);

	unguard;

	//
	{
		guard(CHeroGame::LoadLand::load_begin);
		{
			CWorldBuffer* pbuffer = SwGlobal::GetWorld()->GetWorldBuffer();
			CWorldTile* pActiveTile = pbuffer->GetTileFromMapId(iLandID);
			if (!pActiveTile)
			{
				assert( pWorldTile != NULL && "load map failed" );
				::SendMessage( g_hWnd, WM_USER_CLOSE/*WM_CLOSE*/, 0, 0 );
				return FALSE;
			}
            LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      设备调用 EvictManagedResources() 开始", GetCurrentThreadId() );
			m_pd3dDevice->EvictManagedResources();
            LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      设备调用 EvictManagedResources() 结束", GetCurrentThreadId() );

			CFootPrintMgr::Instance()->clear();
//  			pbuffer->SetMaxTileCacheNum(1);

            LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载地块开始", GetCurrentThreadId() );
			BOOL bRet  = pbuffer->SetActiveTile(pActiveTile,nMeX,nMeY) ;
            LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载地块结束", GetCurrentThreadId() );
            LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      可寻路地图标记NPC", GetCurrentThreadId() );
			g_fTheRoleSlipJumpingAngle = D3DX_PI/180*pActiveTile->GetReachableAngle();
			NpcCoord::getInstance()->MarkNpcOnReachableMap(pActiveTile);
			CPathDirection::Instance()->Reset();


			{
				LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载小地图", GetCurrentThreadId() );
				char szTga[MAX_PATH] = {0};
				BOOL bMiniMapLoadSucc = FALSE;
				{
					bMiniMapLoadSucc = GetAdvancedMiniMap()->Create( 
						m_world->GetWorldBuffer()->GetActiveTile()->GetWidth(), 
						m_world->GetWorldBuffer()->GetActiveTile()->GetDepth(), 
						szTga );
				}
			}

			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      设置大地图NPC信息", GetCurrentThreadId() );
			s_CUI_ID_FRAME_MiniMap.ResetZoneInfo();
 			s_CUI_ID_FRAME_AllNpcList.RefreshMapList();
			s_CUI_ID_FRAME_AllNpcList.InitByTile(pActiveTile);
// 			s_CUI_ID_FRAME_TRACK.RefreshNpc();
			//CIntroductionManager::Instance()->ClearStack();
		}
		unguard;
	}

	m_iLandID = iLandID;

	dwTick = HQ_TimeGetTime()-dwTick;
	//load_succ:
	if( GLoadCoreDataError )
	{
		GLoadCoreDataExited = TRUE;
		assert( 0 && "load core data error" );
		SendMessage( g_hWnd, WM_USER_CLOSE/*WM_CLOSE*/, 0, 0 );
		return FALSE;
	}

	//载入地图
	//载入完成
	guard(load_succerror);
	g_maploaded = true;
	//MsgMapLoaded msg;
	//std::string address = "";
	//GetMacAddr(&address);
	//strncpy(msg.szMacAddress, address.c_str(), sizeof(msg.szMacAddress)-1);
	//GettheNetworkInput().SendMsg( &msg,msg.GetLength() );

	// 地图加载完毕，设置可以接收玩家进入/离开视野，和移动消息
	if( GetPlayerMgr() )
		GetPlayerMgr()->SetCanReceivePlayerMsg(TRUE);

	g_vecPendingShowInfo.clear();

	g_bCanUpdateQuest = FALSE;

	if(thePlayerRole.GetCanChangeMap())
	{
		CrossMapPF::Instance()->Reset();
	}
	// 可以切换地图
	thePlayerRole.SetCanChangeMap(true);

	// 是否显示小地图
	s_CUI_ID_FRAME_MiniMap.SetVisable(true );
// 	SetDlgVisable();	//设置需要显示的界面

	thePlayerRole.UpdateUI();
	CWealthProtect::Instance().SetFirstEnterMap(m_nLastLandId == -1);
	s_CUI_ID_FRAME_MiniMap.ResetEctypeMapTimeRemain();

	/*
	 *	Author 2012-11-7 zhuxincong
	 *	DESC: 跨地图寻路，到达一个地图之后就隐藏一个text
	 */
	//s_CUI_ID_FRAME_FindRoad.CloseText();
	
	m_nLastLandId = iLandID;

	if( g_iShowJoinFightCountDown > 0 )
		--g_iShowJoinFightCountDown;

	unguard;
	return TRUE;
	unguard;
}
// void CHeroGame::SetDlgVisable()
// {
// 	s_CUI_ID_FRAME_MAIN.SetVisable(true);
// }

void CHeroGame::ProcessKeyInput()	// 处理玩家移动可以放到CPlayer里
{
	guardfunc;
	BOOL bOderToMoving = FALSE;

	if (GetPlayerMgr()->GetMe() && GetPlayerMgr()->GetMe()->IsDead())
		return;

	if( theApp->GetPlayerMgr() && GetPlayerMgr()->GetMe() )
	{
		g_vTheRoleTargetDir.x = 0;
		g_vTheRoleTargetDir.y = 0;

		if( !g_bMouseLButtonIsDown )
		{
			g_fTheRoleDirCorrect = 0;
		}

		g_bRoleRotatebyDir = FALSE;
		if (GetPlayerMgr()->GetMe()->IsCanMove() && s_CUI_ID_FRAME_Team.GetTeamFollowID() == -1 ) //可以移动，且没有处于跟随状态
		{
			if( !getwsCamera()->GetLock45DegreeCameraMode() )
			{
				// 按下左转，并且没按右转，向左走，向右走
				if( GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_leftRotate)) && 
					!(GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_rightRotate)) ) &&
					!(GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_leftwalk)) ) && 
					!(GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_rightwalk)) ) ) 
				{
					if( g_bMouseRButtonIsDown )
					{
						s_CUI_ID_FRAME_TutorialBox.OnMovePlayerLeft();
						if (GetPlayerMgr()->GetMe()->m_cFightStatus.IsRandRun())
						{
							g_vTheRoleTargetDir.x /*+*/-= 100;		// 相机改成右手系，旋转方向相应调整[QL]
							g_bTheRoleMovingByDir = TRUE;
							g_bTheRoleCountermarch = FALSE;
							GetPlayerMgr()->GetMe()->SetMoving( TRUE );
							GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
							bOderToMoving = TRUE;
						}
						else
						{
							g_vTheRoleTargetDir.x /*-*/+= 100;	// 相机改成右手系，旋转方向相应调整[QL]
							g_bTheRoleMovingByDir = TRUE;
							g_bTheRoleCountermarch = FALSE;
							GetPlayerMgr()->GetMe()->SetMoving( TRUE );
							GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
							bOderToMoving = TRUE;
						}
					}
					else
					{
						if( g_bMouseLButtonIsDown )
						{
							g_fTheRoleDirCorrect /*+*/-= (float)g_dwLastFrameCostTime*g_fZRotate*getwsCamera()->GetCameraRotateZSpeed();	// 相机改成右手系，旋转方向相应调整，QL
						}
						else
						{
							getwsCamera()->SetCameraRotateZBuf( getwsCamera()->GetCameraRotateZBuf() + g_dwLastFrameCostTime );
							// 人跟着相机一起转
							g_fTheRoleRotateZCorrect -= (float)g_dwLastFrameCostTime*getwsCamera()->GetCameraRotateZSpeed();
						}
						g_bRoleRotatebyDir = TRUE;
					}
				}

				// 按下右转，并且没按左转，向左走和向右走
				if( GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_rightRotate)) && 
					!(GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_leftRotate)) ) &&
					!(GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_leftwalk)) ) && 
					!(GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_rightwalk)) ) ) 
				{
					if( g_bMouseRButtonIsDown )
					{
						s_CUI_ID_FRAME_TutorialBox.OnMovePlayerRight();
						if (GetPlayerMgr()->GetMe()->m_cFightStatus.IsRandRun())
						{
							g_vTheRoleTargetDir.x /*-*/+= 100;	// 相机改成右手系，旋转方向相应调整[QL]
							g_bTheRoleMovingByDir = TRUE;
							g_bTheRoleCountermarch = FALSE;
							GetPlayerMgr()->GetMe()->SetMoving( TRUE );
							GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
							bOderToMoving = TRUE;
						}
						else
						{
							g_vTheRoleTargetDir.x /*+*/-= 100;	// 相机改成右手系，旋转方向相应调整[QL]
							g_bTheRoleMovingByDir = TRUE;
							g_bTheRoleCountermarch = FALSE;
							GetPlayerMgr()->GetMe()->SetMoving( TRUE );
							GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
							bOderToMoving = TRUE;
						}
					}
					else
					{
						if( g_bMouseLButtonIsDown )
						{
							g_fTheRoleDirCorrect /*-*/+= (float)g_dwLastFrameCostTime*g_fZRotate*getwsCamera()->GetCameraRotateZSpeed();	// 相机改成右手系，旋转方向相应调整，QL
						}
						else
						{
							getwsCamera()->SetRotateXBuf( getwsCamera()->GetRotateXBuf()-(float)g_dwLastFrameCostTime );						    
							// 人跟着相机一起转
							g_fTheRoleRotateZCorrect += (float)g_dwLastFrameCostTime*getwsCamera()->GetCameraRotateZSpeed();
						}
						g_bRoleRotatebyDir = TRUE;
					}
				}

				// 按下向前走
				if( GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_forward)) || 
					g_bAutoRunForward || (!getwsCamera()->GetLock45DegreeCameraMode() && g_bMouseLButtonIsDown && g_bMouseRButtonIsDown ) ) 
				{
					s_CUI_ID_FRAME_TutorialBox.OnMovePlayerUp();
					if (GetPlayerMgr()->GetMe()->IsCountermarch())
					{
						GetPlayerMgr()->GetMe()->m_bLastFrameMoving = FALSE;
					}

					CrossMapPF::Instance()->Reset();
					CPathDirection::Instance()->Reset();
					s_CUI_ID_FRAME_MiniMap.SetAutoRuning(false);
					if (GetPlayerMgr()->GetMe()->m_cFightStatus.IsRandRun())
					{
						g_bAutoRunForward = FALSE;
						if( g_vTheRoleTargetDir.y == 0 )
						{
							g_vTheRoleTargetDir.y += 100;
							g_bTheRoleCountermarch = TRUE;
							g_bTheRoleMovingByDir = TRUE;
							GetPlayerMgr()->GetMe()->SetMoving( TRUE );
							GetPlayerMgr()->GetMe()->SetCountermarch( TRUE );
							bOderToMoving = TRUE;
						}
					}
					else
					{
						if( g_bAutoRunForward && 
							GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_forward)) )
						{
							g_bAutoRunForward = FALSE;
						}

						if( !getwsCamera()->GetLock45DegreeCameraMode() && g_bMouseLButtonIsDown && g_bMouseRButtonIsDown ) 
						{
							g_bAutoRunForward = FALSE;
						}

						g_vTheRoleTargetDir.y -= 100;
						g_bTheRoleMovingByDir = TRUE;
						g_bTheRoleCountermarch = FALSE;
						GetPlayerMgr()->GetMe()->SetMoving( TRUE );
						GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
						bOderToMoving = TRUE;
					}

					if( !getwsCamera()->GetLock45DegreeCameraMode() && g_bMouseLButtonIsDown && g_bMouseRButtonIsDown ) 
					{
						g_bRoleMoveByLRButtonDown = TRUE;
					}
				}

				// 按下向左走，且没按向右走
				if( GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_leftwalk))&&GetPlayerMgr()->GetMe()->IsCanOperateByKey(AN_Configure_ShortcutKey::AN_SCKC_leftwalk)&& 
					!(GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_rightwalk)) ) ) 
				{
					if (GetPlayerMgr()->GetMe()->m_cFightStatus.IsRandRun())
					{
						g_vTheRoleTargetDir.x += 100;
						g_bTheRoleMovingByDir = TRUE;
						g_bTheRoleCountermarch = FALSE;
						GetPlayerMgr()->GetMe()->SetMoving( TRUE );
						GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
						bOderToMoving = TRUE;
					}
					else
					{
						g_vTheRoleTargetDir.x /*-*/+= 100;	// 相机改成右手系，旋转方向相应调整[QL]
						g_bTheRoleMovingByDir = TRUE;
						g_bTheRoleCountermarch = FALSE;
						GetPlayerMgr()->GetMe()->SetMoving( TRUE );
						GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
						bOderToMoving = TRUE;
					}
				}

				// 按下向右走，且没按向左走
				if( GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_rightwalk))&&GetPlayerMgr()->GetMe()->IsCanOperateByKey(AN_Configure_ShortcutKey::AN_SCKC_rightwalk) && 
					!(GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_leftwalk)) ) )
				{
					if (GetPlayerMgr()->GetMe()->m_cFightStatus.IsRandRun())
					{
						g_vTheRoleTargetDir.x -= 100;
						g_bTheRoleMovingByDir = TRUE;
						g_bTheRoleCountermarch = FALSE;
						GetPlayerMgr()->GetMe()->SetMoving( TRUE );
						GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
						bOderToMoving = TRUE;
					}
					else
					{
						g_vTheRoleTargetDir.x /*+*/-= 100;	// 相机改成右手系，旋转方向相应调整[QL]
						g_bTheRoleMovingByDir = TRUE;
						g_bTheRoleCountermarch = FALSE;
						GetPlayerMgr()->GetMe()->SetMoving( TRUE );
						GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
						bOderToMoving = TRUE;
					}
				}

				// 按下向后走，且没按向前走
				if( GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_backward)) && 
					!(GetKeyboardInput(g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_forward)) ) )
				{
					s_CUI_ID_FRAME_TutorialBox.OnMovePlayerDown();
					CrossMapPF::Instance()->Reset();
					CPathDirection::Instance()->Reset();
					s_CUI_ID_FRAME_MiniMap.SetAutoRuning(false);
					if (GetPlayerMgr()->GetMe()->m_cFightStatus.IsRandRun())
					{
						g_vTheRoleTargetDir.y -= 100;
						g_bTheRoleMovingByDir = TRUE;
						g_bTheRoleCountermarch = FALSE;
						GetPlayerMgr()->GetMe()->SetMoving( TRUE );
						GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
						bOderToMoving = TRUE;
					}
					else
					{
						g_bAutoRunForward = FALSE;
						if( g_vTheRoleTargetDir.y == 0 )
						{
							g_vTheRoleTargetDir.y += 100;
							g_bTheRoleCountermarch = TRUE;
							g_bTheRoleMovingByDir = TRUE;
							GetPlayerMgr()->GetMe()->SetMoving( TRUE );
							GetPlayerMgr()->GetMe()->SetCountermarch( TRUE );
							bOderToMoving = TRUE;
						}
					}
				}
			}
			else
			{
				// 锁45°角，用默认2.5D操作方法
				bOderToMoving = Update25Direction();
			}
		}


		if( !bOderToMoving && g_bTheRoleMovingByDir )
		{
			g_vTheRoleTargetDir.x = 0;
			g_vTheRoleTargetDir.y = 0;
			g_bLastFrameMovebyDir = g_bTheRoleMovingByDir;
			g_bTheRoleMovingByDir = FALSE;
			g_bTheRoleCountermarch = FALSE;
			GetPlayerMgr()->GetMe()->SetMoving( FALSE );
			GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
		}

		if( bOderToMoving )
		{
			GetPlayerMgr()->HideTargetPointEffect();
			// added, jiayi, [2009/7/25], 选点的时候不要清除技能信息
			if( GetPlayerMgr()->GetMe() && !GetPlayerMgr()->GetMe()->IsSelectingPoint() )
				GetPlayerMgr()->SetCurUseSkill( 0, 0 );
		}
	}

	CActionManager::SGameActionOperation GameActionOperation;
	if( g_ActionManager.PopNextAction( GameActionOperation ) )
	{
		g_shortcutKey_configure.dealwithHotkey(GameActionOperation);
	}

	unguard;
}

void CHeroGame::ProcessMouseInput()
{
	guardfunc;
	getwsCamera()->SetDIMOFS_X_Changed(false);
	getwsCamera()->SetDIMOFS_Y_Changed(false);
	static BOOL bMouseLButtonDownUIProc = FALSE;	// 最近一个鼠标左键按下消息由UI获取相应
	static BOOL bShowCursor = TRUE;
	static BOOL bOutOfClientWindow = FALSE;
	g_bShowAoeSelectEffect = true;
	bool isInRequest = s_CUI_ID_FRAME_Team.GetInRequestState(); //这个决定在UI响应后是否取消，因为在启动那一次点击UI是不取消的
	if( g_pMouse )
	{
		DIDEVICEOBJECTDATA didod[ SAMPLE_BUFFER_SIZE ];  // Receives buffered data 
		DWORD              dwElements;
		DWORD              i;
		HRESULT            hr;
		POINT			   ptMouse;

		dwElements = SAMPLE_BUFFER_SIZE;
		hr = g_pMouse->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), didod, &dwElements, 0 );

		if( hr != DI_OK ) 
		{
			hr = g_pMouse->Acquire();

			while( hr == DIERR_INPUTLOST )
			{
				hr = g_pMouse->Acquire();
			}
		}
		if( g_bMouseLeave )
			return;
		if( !HasFocus() || !IsActiveWindow() )
			return;

		GetCursorPos( &ptMouse );
		ScreenToClient( g_hWnd , &ptMouse );
		if( ptMouse.x > 0 && ptMouse.x < SCREEN_WIDTH && ptMouse.y > 0 && ptMouse.y < SCREEN_HEIGHT )
		{
			if( bOutOfClientWindow )
				theMouseManager.ForceSetCursor();
			bOutOfClientWindow = FALSE;
		}
		else
			bOutOfClientWindow = TRUE;

		if( theIconDragManager.IsIconMoved() )
		{
			// 隐藏系统鼠标
			if( ptMouse.x > 0 && ptMouse.x < SCREEN_WIDTH && ptMouse.y > 0 && ptMouse.y < SCREEN_HEIGHT )
			{
				if( bShowCursor )
				{
					ShowCursor(FALSE);
					bShowCursor = FALSE;
				}
			}
			else if( !bShowCursor )
			{
				bShowCursor = TRUE;
				ShowCursor(TRUE);
			}
		}
		else if( !bShowCursor )
		{
			bShowCursor = TRUE;
			ShowCursor(TRUE);
		}

		if( !FAILED(hr) ) 
		{
			bool bUIProcessMouseMove = false;
			for( i = 0; i < dwElements; i++ ) 
			{
				switch( didod[ i ].dwOfs )
				{
				case DIMOFS_BUTTON0:
					GetCursorPos( &ptMouse );
					ScreenToClient( g_hWnd , &ptMouse );

					if( didod[ i ].dwData == 0x80 )	// 左键按下
					{
						BOOL bLastMouseLButtonIsDown = g_bMouseLButtonIsDown;
						g_bMouseLButtonIsDown = TRUE;
						g_bMouseLButtonRotate = FALSE;

						// 先处理UI
						LPARAM lParam = MAKELONG((int)ptMouse.x, (int)ptMouse.y);
						if ( theUiManager.MsgProc( g_hWnd, WM_LBUTTONDOWN, VK_LBUTTON, lParam ) == true )
						{
							bMouseLButtonDownUIProc = TRUE;
							if ( isInRequest == true )
							{
								s_CUI_ID_FRAME_Team.CheckOnPlayerClick(NULL); //如果UI处理过了就取消申请状态
							}
							break;
						}
						else
							bMouseLButtonDownUIProc = FALSE;

						if( g_bMouseLButtonIsDown == bLastMouseLButtonIsDown )
							break;

						// 清空g_bRoleMoveByLRButtonDown标志，记录在按下右键到释放右键的途中有没有通过按下左键来移动
						g_bRoleMoveByLRButtonDown = FALSE;

						if( g_GameState == G_MAIN )
						{
							if(GetPlayerMgr()->GetMe() && GetPlayerMgr()->GetMe()->m_cFightStatus.IsRandRun())
							{
								break;
							}
							if( theUiManager.IsMouseInUI() )
							{
								ClipCursor( NULL );
								//OutputDebugString("鼠标位置清空11\n");
								break;
							}
						}

						if( g_GameState == G_MAIN )
						{
							g_bRotateEnable = TRUE;


							if( ptMouse.x > 0 && ptMouse.x < SCREEN_WIDTH && ptMouse.y > 0 && ptMouse.y < SCREEN_HEIGHT )
							{
								OnProcessMouseEvent( g_hWnd, WM_LBUTTONDOWN, g_bMouseLButtonIsDown );
								GetCursorPos( &ptMouse );

								if( !g_b25DMouseLButtonDownOnTerrain && !g_b25DRoleMoveFollowMouse )
								{
									RECT rc;
									rc.left = ptMouse.x-1;
									rc.top = ptMouse.y-1;
									rc.right = ptMouse.x+1;
									rc.bottom = ptMouse.y+1;
									ClipCursor( &rc );
									//OutputDebugString("鼠标位置清空1111\n");
								}

								ClientToScreen( g_hWnd, &ptMouse );
							}
						}
					}
					else if( didod[ i ].dwData == 0 )	// 左键释放
					{
						BOOL bLastMouseLButtonIsDown = g_bMouseLButtonIsDown;
						g_bMouseLButtonIsDown = FALSE;

						LPARAM lParam = MAKELONG((int)ptMouse.x, (int)ptMouse.y);
						if ( theUiManager.MsgProc( g_hWnd, WM_LBUTTONUP, VK_LBUTTON, lParam ) )
						{
							if ( isInRequest == true )
							{
								s_CUI_ID_FRAME_Team.CheckOnPlayerClick(NULL); //如果UI处理过了就取消申请状态
							}
							if( !g_bMouseRButtonIsDown )
							{
								ClipCursor( NULL );
								//OutputDebugString("鼠标位置清空4\n");
								theMouseManager.ForceSetCursor();
							}
							break;
						}

						if( bMouseLButtonDownUIProc )
							break;

						if( g_bMouseLButtonIsDown == bLastMouseLButtonIsDown )
							break;

						if( g_GameState == G_MAIN )
						{
							if(GetPlayerMgr()->GetMe() && GetPlayerMgr()->GetMe()->m_cFightStatus.IsRandRun())
							{
								break;
							}
							if( theUiManager.IsMouseInUI() )
							{
								ClipCursor( NULL );
								//OutputDebugString("鼠标位置清空9\n");
								break;
							}

							if( !g_bMouseRButtonIsDown )
							{
								ClipCursor( NULL );
								//OutputDebugString("鼠标位置清空8\n");
							}

							theMouseManager.ForceSetCursor();

							if( bLastMouseLButtonIsDown )
							{
								GetCursorPos( &ptMouse );
								ScreenToClient( g_hWnd , &ptMouse );

								if( ptMouse.x > 0 && ptMouse.x < SCREEN_WIDTH && ptMouse.y > 0 && ptMouse.y < SCREEN_HEIGHT )
								{
									s_CUI_ID_FRAME_TutorialBox.OnLMouseButton();
									if( getwsCamera()->GetLock45DegreeCameraMode() || (!getwsCamera()->GetLock45DegreeCameraMode() && !g_bMouseRButtonIsDown ) )
										OnProcessMouseEvent( g_hWnd, WM_LBUTTONUP, g_bMouseLButtonIsDown );
								}
							}
						}
					}
					break;
				case DIMOFS_BUTTON1:
					GetCursorPos( &ptMouse );
					ScreenToClient( g_hWnd, &ptMouse );

					if ( isInRequest == true )
					{
						s_CUI_ID_FRAME_Team.CheckOnPlayerClick(NULL); //如果UI处理过了就取消申请状态
					}

					if( didod[ i ].dwData == 0x80 )		// 右键按下
					{
						bool bLastMouseRButtonIsDown = g_bMouseRButtonIsDown;
						g_bMouseRButtonIsDown = TRUE;
						g_bMouseRButtonRotate = FALSE;

						// 先处理UI
						LPARAM lParam = MAKELONG((int)ptMouse.x, (int)ptMouse.y);
						if ( theUiManager.MsgProc( g_hWnd, WM_RBUTTONDOWN, VK_RBUTTON, lParam ) == true && GetPlayerMgr()->GetMe() && !GetPlayerMgr()->GetMe()->IsDead())
						{
							break;
						}

						if( g_bMouseRButtonIsDown == (BOOL)bLastMouseRButtonIsDown )
							break;

						s_CUI_ID_FRAME_TutorialBox.OnRMouseButton();
						// 记录右键按下时，相机朝向
						getwsCamera()->SetCameraRotateXWhenRButtonIsDown( getwsCamera()->GetCameraRotateX() );

						// 清空g_bRoleMoveByLRButtonDown标志，记录在按下右键到释放右键的途中有没有通过按下左键来移动
						g_bRoleMoveByLRButtonDown = FALSE;

						if( theUiManager.IsMouseInUI() )
						{
							ClipCursor( NULL );
							//OutputDebugString("鼠标位置清空7\n");
							break;
						}

						if( g_GameState == G_MAIN )
						{
							g_bRotateEnable = TRUE;

							if(  ptMouse.x > 0 && ptMouse.x < SCREEN_WIDTH && ptMouse.y > 0 && ptMouse.y < SCREEN_HEIGHT )
							{
								OnProcessMouseEvent( g_hWnd , WM_RBUTTONDOWN , g_bMouseLButtonIsDown );
								GetCursorPos( &ptMouse );
								RECT rc;
								rc.left = ptMouse.x-1;
								rc.top = ptMouse.y-1;
								rc.right = ptMouse.x+1;
								rc.bottom = ptMouse.y+1;
								ClipCursor( &rc );
                              // OutputDebugString("鼠标位置清空22222\n");
								ClientToScreen( g_hWnd, &ptMouse );
							}
						}
					}
					else if( didod[ i ].dwData == 0 )		// 右键释放
					{
						bool bLastMouseRButtonIsDown = g_bMouseRButtonIsDown;
						g_bMouseRButtonIsDown = FALSE;


						// 先处理UI
						LPARAM lParam = MAKELONG((int)ptMouse.x, (int)ptMouse.y);
						if ( theUiManager.MsgProc( g_hWnd, WM_RBUTTONUP, VK_RBUTTON, lParam ) == true )
						{
							if( !g_bMouseLButtonIsDown )
							{
								ClipCursor( NULL );
								//OutputDebugString("鼠标位置清空6\n");
								theMouseManager.ForceSetCursor();
							}
							break;
						}

						if( g_bMouseRButtonIsDown == (BOOL)bLastMouseRButtonIsDown )
							break;
						if( theUiManager.IsMouseInUI() )
						{
							ClipCursor( NULL );
							//OutputDebugString("鼠标位置清空5\n");
							break;
						}

						if( getwsCamera()->GetLock45DegreeCameraMode() || !g_bMouseLButtonIsDown )
						{
							ClipCursor( NULL );
							//OutputDebugString("鼠标位置清空4\n");
						}
						if( g_GameState == G_MAIN )
							OnProcessMouseEvent( g_hWnd, WM_RBUTTONUP, g_bMouseLButtonIsDown );
					}
					break;
				case DIMOFS_X:
					{
						GetCursorPos( &ptMouse );
						ScreenToClient( g_hWnd, &ptMouse );
						if ( g_GameState == G_MAIN && g_bRotateEnable && !theUiManager.IsMouseInUI() && !theIconDragManager.IsIconMoved() )
						{
							int lData = didod[ i ].dwData;

							// modified, [9/21/2010 zhangjiayi]
							if( g_bMouseRButtonIsDown || ( !getwsCamera()->GetLock45DegreeCameraMode() && g_bMouseLButtonIsDown ) )
								getwsCamera()->SetRotateXBuf(getwsCamera()->GetRotateXBuf() - GetZRotatePerStamp( lData, didod[i].dwTimeStamp ));
							getwsCamera()->SetDIMOFS_X_Changed( true );
						}
					}
					break;
				case DIMOFS_Y:
					{
						GetCursorPos( &ptMouse );
						ScreenToClient( g_hWnd, &ptMouse );
						if ( g_GameState == G_MAIN && g_bRotateEnable && !theUiManager.IsMouseInUI() && !theIconDragManager.IsIconMoved() )
						{
							int lData = didod[ i ].dwData;

							if( !getwsCamera()->GetLockCameraMode() )
							{
								getwsCamera()->SetRotateYBuf(getwsCamera()->GetRotateYBuf() + GetXRotatePerStamp( lData, didod[i].dwTimeStamp ));
								getwsCamera()->SetDIMOFS_Y_Changed( true );
							}
						}
					}
					break;
				case DIMOFS_Z:
					long lData = didod[ i ].dwData;
					// 先处理UI
					LPARAM lParam = MAKELONG((int)ptMouse.x, (int)ptMouse.y);
					if ( theUiManager.MsgProc( g_hWnd, WM_MOUSEWHEEL, lData, lParam ) == true )
					{
						break;
					}

					if (g_GameState == G_MAIN && !theUiManager.IsMouseInUI() && !theIconDragManager.IsIconMoved())
					{
						if (lData < 65535 && lData > -65535)
						{
							const float zoom = getwsCamera()->GetCameraZoomBuf();
							getwsCamera()->SetCameraZoomBuf(zoom - lData * 0.004f);
						}
					}
					break;
				}
			}
		}
	}

	if( !getwsCamera()->GetDIMOFS_X_Changed() )
	{
		m_bZRotateStarted = false;
	}

	if( !getwsCamera()->GetDIMOFS_Y_Changed() )
	{
		m_bXRotateStarted = false;
	}


	if( !g_bMouseLButtonIsDown && !g_bMouseRButtonIsDown )
	{
		ReleaseCapture();
		ClipCursor( NULL );
	   // OutputDebugString("鼠标位置清空1\n");
		g_bRotateEnable = FALSE;
	}

	if( !( GetKeyboardInputWin32( VK_LBUTTON ) & 0x800000 ) ) 
	{
		g_bMouseLButtonIsDown = FALSE;
	}

	if( !( GetKeyboardInputWin32( VK_RBUTTON ) & 0x800000 ) ) 
	{
		g_bMouseRButtonIsDown = FALSE;
		//OutputDebugString("鼠标位置清空0\n");
	}

	if( g_bMouseMoveMode )
	{
		if( theUiManager.IsMouseInUI() )
			g_bShowAoeSelectEffect = false;
	}
	unguard;
}

BOOL CHeroGame::ProcessInput( DWORD dwTime )
{
	guardfunc;
	// 读取键盘数据
	UpdateKeyState();

	// 播视频时屏蔽除ESC以外的键        added by zhuomeng.hu		[3/1/2011]
	for( int i = 0; i < m_nCurrKeyChangeNum; ++i )
	{
		if( m_CurrKeyChangeList[i].bPressed )
		{
			WPARAM wParam = GetWindowKeyFromDirectXKey( m_CurrKeyChangeList[i].nKeyIndex );
			if( wParam > 0 && wParam == VK_ESCAPE )
			{
                CMovieManager::Instance()->ProcessESC();
			}
		}
	}
    if( CMovieManager::Instance()->DisableInput() )
	{
		return FALSE;
	}

	if ( (g_GameState == G_LOADSPLASH || !m_world || !s_CUI_ID_FRAME_LoadMap.IsMapLoaded()/*m_world->IsLoading()*/ ) && !s_CUI_ID_FRAME_MessageBox.IsVisable() )
	{
		return FALSE;
	}

	if( g_bFirstSightCamera )
	{
		D3DXVECTOR3 vPosMe;
		if( GetPlayerMgr()->GetMe() )
		{
			vPosMe = GetPlayerMgr()->GetMe()->GetPos();
		}
		else
		{
			return FALSE;
		}

		//第一人称模式
		//以下代码是以前写的，用的话在改
		static float fDistToEye = 10;
		static float fDistToTarget = 5;
		static float fRotateY = 45;

		if( GetKeyboardInput( DIK_HOME ) )
		{
			fDistToEye += 0.5;
			fDistToTarget += 0.25;
		}
		if( GetKeyboardInput( DIK_END ) )
		{
			fDistToEye -= 0.5;
			fDistToTarget -= 0.25;
		}

		D3DXVECTOR3 vEyePt( cosf(fRotateY*D3DX_PI/180)*fDistToEye, 0, sinf(fRotateY*D3DX_PI/180)*fDistToEye);
		D3DXVECTOR3 vLookatPt( 0,0,0 );
		D3DXVECTOR3 vDist = vEyePt-vLookatPt;
		vDist = -vDist;
		D3DXVec3Normalize( &vDist, &vDist );

		D3DXVECTOR3 vTartet = fDistToTarget*vDist;
		vTartet.z = 0;
		D3DXVECTOR3 vZAxis( 0, 0, -1 );
		D3DXMATRIX matRotZ;
		D3DXMatrixRotationAxis(	&matRotZ, &vZAxis, getwsCamera()->GetCameraRotateX() );
		D3DXVec3TransformCoord( &vEyePt, &vEyePt, &matRotZ );
		D3DXVec3TransformCoord( &vTartet, &vTartet, &matRotZ );

		D3DXVECTOR3 vPos = vPosMe;
		vEyePt += vPos;
		vTartet += vPos;
		getwsCamera()->GetMeCamera()->SetViewParams( vEyePt, vTartet, D3DXVECTOR3( 0, 0, 1 ) );
	}
	else
	{
		if( GetPlayerMgr()->GetMe() && GetPlayerMgr()->GetMe()->IsDead() && !g_bMouseRButtonIsDown)
		{
			ClipCursor( NULL );
			//OutputDebugString("鼠标位置清空3\n");
		}

		///////////////////////////////////1
		ProcessMouseInput();

		// 处理KeyUp和KeyDown消息
		if( m_nCurrKeyChangeNum > 0 )
		{
			for(int i=0; i<m_nCurrKeyChangeNum; i++)
			{
				if( m_CurrKeyChangeList[i].bPressed )
				{
					// 处理KeyDown消息
					LPARAM lParam = 0;
					WPARAM wParam = GetWindowKeyFromDirectXKey(m_CurrKeyChangeList[i].nKeyIndex);
					if ( wParam > 0 && wParam != VK_RETURN && wParam != VK_LEFT && wParam != VK_RIGHT &&
						wParam != VK_DELETE && (g_GameState != G_MAIN || wParam != VK_TAB) &&
						theUiManager.MsgProc( g_hWnd, WM_KEYDOWN, wParam, lParam ) == true )
					{
						break;
					}

					if( !focusInUIEdit() && g_GameState == G_MAIN )
					{
						GetPlayerMgr()->KeyboardControlFunction( m_CurrKeyChangeList[i].nKeyIndex, TRUE );

						g_ActionManager.Push_NormalAction( g_nKeydownGameAction[m_CurrKeyChangeList[i].nKeyIndex], g_dwLastFrameBeginTime );
						g_shortcutKey_configure.setHotkeyState( g_nKeydownGameAction[m_CurrKeyChangeList[i].nKeyIndex], 
							AN_Configure_ShortcutKey::ON_KEY_DOWN );



						if( m_CurrKeyChangeList[i].nKeyIndex == g_shortcutKey_configure.getValueCharInput(AN_Configure_ShortcutKey::AN_SCKC_changeTarget) )
						{
							GetPlayerMgr()->TabSelectPlayer();
						}



						s_CUI_Group.ProcessHotKey(wParam);

					}
				}
				else
				{
					// 处理KeyUp消息
					LPARAM lParam = 0;
					WPARAM wParam = GetWindowKeyFromDirectXKey(m_CurrKeyChangeList[i].nKeyIndex);

					// added, jiayi, [2009/7/23]
					if( GetPlayerMgr()->BreakInputMessage( wParam ) )
						break;

#ifdef _DEBUG
					if( g_GameState == G_CREATE )
					{
						if( wParam > 0 && GetKeyboardInput(DIK_LALT))
						{
							if( wParam == VK_UP )
							{
								s_CUI_ID_FRAME_CREATE.SetPlayerScaleDelta(0.02f);
							}
							else if( wParam == VK_DOWN )
							{
								s_CUI_ID_FRAME_CREATE.SetPlayerScaleDelta(-0.02f);
							}
						}
					}
#endif
					if ( wParam > 0 && wParam != VK_RETURN && theUiManager.MsgProc( g_hWnd, WM_KEYUP, wParam, lParam ) == true )
					{
						break;
					}

					if( g_GameState == G_MAIN )
					{
						if( !s_CUI_ChatInfoBox.EditInputIsVisable() 
							&& !chatMessageManage.EditInputIsVisable()
							&& !s_CUI_ID_FRAME_ChatSet.EditInputIsVisable()
							)
						{
							GetPlayerMgr()->KeyboardKeyUpControlFunction( m_CurrKeyChangeList[i].nKeyIndex, TRUE );
						}

						if( !focusInUIEdit() )
						{
							g_ActionManager.Push_NormalAction( g_nKeyupGameAction[m_CurrKeyChangeList[i].nKeyIndex], g_dwLastFrameBeginTime );
							g_shortcutKey_configure.setHotkeyState( g_nKeydownGameAction[m_CurrKeyChangeList[i].nKeyIndex], 
								AN_Configure_ShortcutKey::ON_KEY_NONE );
						}

						if( m_CurrKeyChangeList[i].nKeyIndex == DIK_ESCAPE )
							theHeroGame.GetPlayerMgr()->cancelBehavior();
					}
				}
			}
		}

		bool bHasModaleMessageBox = s_CUI_ID_FRAME_MessageBox.HasModaleMessageBox();
		if ( !bHasModaleMessageBox )
			bHasModaleMessageBox = s_CUI_ID_FRAME_SelectChannel.IsVisable();
		if( g_GameState == G_MAIN && !focusInUIEdit() && !bHasModaleMessageBox /*&& !s_CUI_ID_FRAME_ExitGame.IsVisable()*/ //取消各种限制 jiayi
			&& !s_CUI_ID_FRAME_LuckGame.IsVisable() && !s_CUI_ID_FRAME_TaskDialog.IsVisable() )// added, jiayi, [2010/1/7]
		{
			ProcessKeyInput();
		}
		else
		{
			if( g_bTheRoleMovingByDir )
			{
				g_vTheRoleTargetDir.x = 0;
				g_vTheRoleTargetDir.y = 0;
				g_bLastFrameMovebyDir = g_bTheRoleMovingByDir;
				g_bTheRoleMovingByDir = FALSE;
				g_bTheRoleCountermarch = FALSE;
				if( GetPlayerMgr()->GetMe() )
				{
					GetPlayerMgr()->GetMe()->SetMoving( FALSE );
					GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
				}
			}

			if( getwsCamera()->GetLock45DegreeCameraMode() )
			{
				m_shCur25Direction = EMD_NONE;
			}

			if( bHasModaleMessageBox && GetPlayerMgr()->GetMe() )
			{
				GetPlayerMgr()->GetMe()->StopMoving();
			}
		}
	}

	return true;
	unguard;
}
bool CHeroGame::focusInUIEdit()
{
	if( s_CUI_ChatInfoBox.EditInputIsVisable() ||
		chatMessageManage.EditInputIsVisable() ||
		s_CUI_ID_FRAME_ChatHistory.EditInputIsVisable() ||
		s_CUI_ID_FRAME_Rename.EditInputIsVisable() ||
		s_CUI_ID_FRAME_ADD_MEMBER.EditInputIsVisable() ||
		s_CUI_ID_FRAME_Announce.EditInputIsVisable() ||
		s_CUI_ID_FRAME_GUILD_CREATE.EditInputIsVisable() ||
		//s_CUI_ID_FRAME_PrivateShop.EditInputIsVisable() ||
		s_CUI_ID_FRAME_custom.IsVisable() ||
		s_CUI_ID_FRAME_EditPrice.EditInputIsVisable() ||
		s_CUI_ID_FRAME_BatchShop.EditInputIsVisable() ||
		s_CUI_ID_FRAME_ChatSet.EditInputIsVisable() ||
		//s_CUI_ID_FRAME_WebAward.EditInputIsVisable() ||
		s_CUI_ID_FRAME_SuperPassword.EditInputIsVisable()||
		s_CUI_ID_FRAME_SuperPasswordReset.EditInputIsVisable()||
		s_CUI_ID_FRAME_SuperPasswordRegister.EditInputIsVisable()||
		(CommonChatFrame::GetActiveChatFrame() && CommonChatFrame::GetActiveChatFrame()->EditInputIsVisable())||
        s_CUI_ID_FRAME_PlayerRename.EditInputIsVisable()||
        s_CUI_ID_FRAME_MailMain.EditInputIsVisable()||
		s_CUI_ID_FRAME_AllNpcList.EditInputIsVisable()||
		s_CUI_ID_FRAME_Search.EditInputIsVisable()||		
		s_CUI_ID_FRAME_AddFriend.EditInputIsVisable()||		
		s_CUI_ID_FRAME_CountryInput.EditInputIsVisable()||				//added by zhuomeng.hu		[8/27/2010]
		s_CUI_ID_FRAME_CountryBroadcast.EditInputIsVisable()||			//added by ZhuoMeng.Hu		[8/30/2010]
        s_CUI_ID_FRAME_Reclaim.EditInputIsVisable() ||
		s_CUI_ID_FRAME_Editor.EditInputIsVisable() ||
		s_CUI_ID_FRAME_Family_Create.EditInputIsVisable() ||
		s_CUI_ID_FRAME_GUILD_FamilyTenet.EditInputIsVisable() ||
		s_CUI_ID_FRAME_GUILD_FamilyMoney.EditInputIsVisable() ||
		s_CUI_ID_FRAME_GUILD_FamilyMessageBox.EditInputIsVisable() ||
		s_CUI_ID_FRAME_FamilyApply.EditInputIsVisable() ||
		s_CUI_ID_FRAME_SelfInfo.EditInputIsVisable() ||
		s_CUI_ID_FRAME_SuAnimalCardList.EditInputIsVisable() ||
		s_CUI_ID_FRAME_GuildApply.EditInputIsVisable() ||
		s_CUI_ID_FRAME_TradeMoney.EditInputIsVisable() ||
		s_CUI_ID_FRAME_Title.EditInputIsVisable()||
		s_CUI_ID_FRAME_AskPresent.EditInputIsVisable() ||
		s_CUI_ID_FRAME_AddGuildGeneralBattle.EditInputIsVisable()	
		)		
		return true;
	return false;
}

#ifdef _DEBUG
extern D3DXVECTOR3 g_TempVt[];
extern D3DXVECTOR3 g_TempLine[];
#endif

BOOL CHeroGame::DisplayGameMain( DWORD dwTime )
{
	guardfunc;
#ifndef OFF_TRUETIME
	//TRUETIMEFUNC();	
#endif
#if LOAD_COST_TIME_DEBUG
	DWORD time_cost = HQ_TimeGetTime();
#endif

	IRenderer* RI = GetEngine()->GetRenderer();
	RendererDx* pRendererDx = ( RendererDx* )RI;

	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();

	guard(test1);

	unguard;

	D3DXMATRIXA16 mView, mProj, mWorld;
	mView = getwsCamera()->GetMeCamera()->GetViewMatrix();
	mProj = getwsCamera()->GetMeCamera()->GetProjMatrix();
	mWorld = pRendererDx->GetWorldMatrix();
	FontSystem::SetWorldMatrix( mWorld );
	FontSystem::SetViewMatrix( mView );

	CShaderMgr* ShaderMgr=GetShaderMgr();	


    
       
	guard(test2);

	{
		guard(test2.1);
		{
			{
				 
				// 渲染世界
				m_world->Update((float)dwTime/1000.f,dwTime);

				RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
				bool bRenderFlare = true;

				// 是否显示光晕
				CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
				if( pTile && !pTile->IsSunLightRender() )
				{
					bRenderFlare = false;
				}
				if( bRenderFlare )
					GetSTSkyBox()->RenderFlare();

				FrustumEx frustum;	
				frustum.BuildFrustum( mProj, mView );
				if( GetMe3dConfig()->IsRenderWorld() )
				{
					MeFreeProfileStart( "RenderWorld " );
					bool bRenderShadow = (ShaderMgr->GetShadowType() == eShadow_RealTime 
						&& ShaderMgr->IsCanUseShader() && SystemSetting::Instance()->IsAdvance() );

					graphics::ShaderManager::instance()->enableShadow(bRenderShadow);

					if ( GetPlayerMgr()->GetMe())
					{
						m_swRender->RenderWorld( m_world, frustum,  GetPlayerMgr()->GetMe()->GetPos(), dwTime, dwTime );
					}
					else
					{
						m_swRender->RenderWorld( m_world, frustum,  getwsCamera()->GetMeCamera()->GetEyePt(), dwTime, dwTime );
					}

					graphics::ShaderManager::instance()->enableShadow(false);					
					MeFreeProfileEnd( "RenderWorld " );
				}
				RI->SetRenderState( D3DRS_FOGENABLE, FALSE );

				
				

			}
		}
		unguard;	
#if LOAD_COST_TIME_DEBUG
		time_cost = HQ_TimeGetTime() - time_cost;
		if(time_cost > 20)
		{
			char cOutputString[2048];
			MeSprintf_s( cOutputString, 2048, "\nRender_RenderWorld:%d\n", time_cost );
			OutputDebugStr(cOutputString);
		}
		time_cost = HQ_TimeGetTime();
#endif

		guard(test2.2);
		{
			//渲染主角
			m_PlayerRenderCost = HQ_TimeGetTime();
			RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
			//if( GetMe3dConfig()->IsRenderObjs() )
			{
				GetPlayerMgr()->Render(m_pd3dDevice);
			    RI->SetSamplerState(0,D3DSAMP_MIPMAPLODBIAS,GetMe3dConfig()->GetMipLodBais());
			}
			m_PlayerRenderCost = HQ_TimeGetTime() - m_PlayerRenderCost;
		}
		unguard;
#if LOAD_COST_TIME_DEBUG
		time_cost = HQ_TimeGetTime() - time_cost;
		if(time_cost > 20)
		{
			char cOutputString[2048];
			MeSprintf_s( cOutputString, 2048, "\nRender_PlayerMgr:%d\n", time_cost );
			OutputDebugStr(cOutputString);
		}
		time_cost = HQ_TimeGetTime();
#endif

		guard(test2.3);
		{
			RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
			m_LiquidRenderCost = HQ_TimeGetTime();
			if(ShaderMgr->GetWaterType() == 2)
				m_swRender->RenderLiquid_High();
			else
				m_swRender->RenderLiquid();
			m_LiquidRenderCost = HQ_TimeGetTime() - m_LiquidRenderCost;
			m_swRender->RenderEffect();
			MeRenderManager::Instance()->DoRender(false);

			RI->SetRenderState( D3DRS_FOGENABLE, FALSE );			
		}
#if LOAD_COST_TIME_DEBUG
		time_cost = HQ_TimeGetTime() - time_cost;
		if(time_cost > 20)
		{
			char cOutputString[2048];
			MeSprintf_s( cOutputString, 2048, "\nRender_Liquid:%d\n", time_cost );
			OutputDebugStr(cOutputString);
		}
		time_cost = HQ_TimeGetTime();
#endif

		unguard;
		//WORD dwTimeCost_ = HQ_TimeGetTime();
		GetPlayerMgr()->RenderAlpha(m_pd3dDevice);

		RI->SetRenderState( D3DRS_FOGENABLE, FALSE );	
		guard(test2.4);
		{
			//渲染主角
			GetPlayerMgr()->RenderPlayerInfo( m_pd3dDevice );		
			RI->SetRenderState( D3DRS_FOGENABLE, TRUE );	
		}
		//m_PlayerRenderCost += HQ_TimeGetTime() - dwTimeCost_;
		unguard;
		
#if LOAD_COST_TIME_DEBUG
		time_cost = HQ_TimeGetTime() - time_cost;
		if(time_cost > 20)
		{
			char cOutputString[2048];
			MeSprintf_s( cOutputString, 2048, "\nRender_渲染主角:%d\n", time_cost );
			OutputDebugStr(cOutputString);
		}
		time_cost = HQ_TimeGetTime();
#endif

		// added, jiayi, [2009.5.8],渲染好物件和天空盒
//  		if( PostProcessManager::instance().enablePostProcess() )
//  		{
//  			if(g_bRenderSkyBox && s_CUI_ID_FRAME_LoadMap.IsMapLoaded() && GetPlayerMgr() && GetPlayerMgr()->GetMe() )
//  			{			
//  				D3DXVECTOR3 p = GetPlayerMgr()->GetMe()->GetPos();
//  				PostProcessManager::instance().saveTempRenderTarget();
//  				RI->Clear( 0L, D3DCLEAR_TARGET , 0, 1.0f, 0L );
//  
//  				FLOAT fAspect = ((FLOAT)SCREEN_WIDTH) / SCREEN_HEIGHT;
//  				getwsCamera()->GetMeCamera()->SetProjParams( g_fCamerFOV, fAspect, 0.1f, 100000.0f );
//  				RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&getwsCamera()->GetMeCamera()->GetProjMatrix() );	
//  
//  				GetSTSkyBox()->RenderSunAndMoon( p );				
//  				getwsCamera()->GetMeCamera()->SetProjParams( g_fCamerFOV, fAspect, m_swRender->GetNearPlane(), m_swRender->GetFarPlane() );
//  				RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&getwsCamera()->GetMeCamera()->GetProjMatrix() );
//  				RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
//  
//  				PostProcessManager::instance().updateRenderTargetToEffect();
//  				PostProcessManager::instance().restoreTempRenderTarget();				
//  			}
//  		}


		guard(test2.5);
		{
			//渲染导航模型
			CPlayer* pLock = GetPlayerMgr()->FindByID(GetPlayerMgr()->GetLockPlayerID()) ;
			if ( pLock && GetPlayerMgr()->GetMe() && pLock != GetPlayerMgr()->GetMe())
			{
				_pNavigation->setNavigationPoint( 
					GetPlayerMgr()->GetMe()->GetPos(), 
					pLock->GetPos() );
				_pNavigation->getMexAnimCtrl()->Render( 1.0f );		
			}	
		}
		unguard;
	}

	guard(test2.7);

	GetPlayerMgr()->DrawNetStreamFlux(m_pd3dDevice, 470, 60, FALSE, &g_Statistics);

	unguard;
	unguard;

#ifdef _DEBUG
	//...
	GetDrawer()->FillTri( g_TempVt[0], g_TempVt[1], g_TempVt[2], 0xFFFF0000 );

	//GetDrawer()->DrawLine3D( g_TempLine[0], g_TempLine[1], 0xFF00FF00 );
	//
#endif

	// add [6/26/2008 whu]
	CPlayerAnim::GlobalMaterial.Ambient = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	CPlayerAnim::GlobalMaterial.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\nRender_DisplayGameMainEnd:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	return TRUE;
	unguard;
}
//
//POINT ptS;
BOOL CHeroGame::RunGameMain( DWORD dwTime )
{
	DWORD time_cost = HQ_TimeGetTime();
	guardfunc;
	{
		BOOL bNeedUpdate = FALSE;
		WORD	dwTimeCost = HQ_TimeGetTime();
		guard(UpdateUI);
		{
			bNeedUpdate = thePlayerRole.IsNeedUpdateUI();
			if ( bNeedUpdate && g_GameState == G_MAIN)
			{
				s_CUI_Group.Refeash();				

				if( s_CUI_ID_FRAME_Compound.IsVisable() )
					s_CUI_ID_FRAME_Compound.Refeash();
			}

			if( s_CUI_ID_FRAME_Group_Me.NeedUpdata() )
			{
				//状态的持续时间数值减少需要
				s_CUI_ID_FRAME_Group_Me.Updata();
			}
			if( DemandItemFrameManage.IsVisable() )
			{
				DemandItemFrameManage.Update();
			}
		}	
		unguard;


#if LOAD_COST_TIME_DEBUG
		time_cost = HQ_TimeGetTime() - time_cost;
		if(time_cost > 20)
		{
			char cOutputString[2048];
			MeSprintf_s( cOutputString, 2048, "\n DemandItemFrameManage %d\n", time_cost );
			OutputDebugStr(cOutputString);
		}
		time_cost = HQ_TimeGetTime();
#endif

		if( GetPlayerMgr()->GetMe() )
		{
			if( GetPlayerMgr()->GetMe()->IsMoving() || bNeedUpdate )
			{
				if( s_CUI_ID_FRAME_MiniMap.GetFrame() )
					s_CUI_ID_FRAME_MiniMap.Refeash();
			}
		}

#if LOAD_COST_TIME_DEBUG
		time_cost = HQ_TimeGetTime() - time_cost;
		if(time_cost > 20)
		{
			char cOutputString[2048];
			MeSprintf_s( cOutputString, 2048, "\n s_CUI_ID_FRAME_MiniMap %d\n", time_cost );
			OutputDebugStr(cOutputString);
		}
		time_cost = HQ_TimeGetTime();
#endif

	}

	WeatherEventManager::Instance()->UpdateWeather();

	if (g_DynamicMapLoadOpenEvent)
	{
		SetEvent(g_hDynamicLoadMap);
	}
	CIntroductionManager::Instance()->Update();

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n CIntroductionManager %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	guard(test2.1.9);
	{
		//渲染路标
		m_testCost = HQ_TimeGetTime();
		CPathDirection::Instance()->UpdatePathDirection();
		m_testCost = HQ_TimeGetTime() - m_testCost;
	}
	unguard;

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n UpdatePathDirection %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	if(m_pPlayerMgr&&!m_pPlayerMgr->IsTracking() && s_CUI_ID_FRAME_Team.GetTeamFollowID() == -1 )
	     getwsCamera()->UpdateCamera();


#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n UpdateCamera %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif
	//渲染2D场景
	//
	FrustumEx frustum;	
	frustum.BuildFrustum( getwsCamera()->GetMeCamera()->GetProjMatrix(),getwsCamera()->GetMeCamera()->GetViewMatrix() );
	//
	D3DXVECTOR3 vCameraOrg;
	vCameraOrg = getwsCamera()->GetMeCamera()->GetLookatPt();
	vCameraOrg -= getwsCamera()->GetMeCamera()->GetEyePt();
	D3DXVec3Normalize( &vCameraOrg,&vCameraOrg );



	// 更新players
	m_PlayerUpdateCost = HQ_TimeGetTime();
	GetPlayerMgr()->Update( dwTime, *(Frustum*)&frustum );
	m_PlayerUpdateCost = HQ_TimeGetTime() - m_PlayerUpdateCost;

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n GetPlayerMgr()->Update %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif


	if(m_pPlayerMgr&&!m_pPlayerMgr->IsTracking())
	    getwsCamera()->ProcessCamera();

	UpdateServerShutdownCountDown();

	guard(test0.2);
	{
		//TRUETIMEBLOCK( "RunGameMain::OtherUpdate" );
		//取得鼠标选择的目标
		GameObjectId gcPlayerServerID = GetPlayerMgr()->GetMouseTargetPlayerSeverID();
		CPlayer* pSelPlayer = GetPlayerMgr()->FindByID( gcPlayerServerID );
		CPlayer* pMe = GetPlayerMgr()->GetMe();
		float fMouseOnTerrainPosX, fMouseOnTerrainPosY;

		////////////////////////////////////////////
		// set the pos of effect of point aoe
		// added, jiayi, [2009/7/20]
		bool bSelectingAoePoint = false;
		if( pMe )
		{
			bSelectingAoePoint = GetPlayerMgr()->GetMe()->IsSelectingPoint();
			if( bSelectingAoePoint && g_bShowAoeSelectEffect )
			{
				CCharEffectContainer* pAoePointEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nAoePointEffectContainerID );
				if( pAoePointEffectContainer )
				{
					IEffectHelper* pEffectHelper = NULL;
					pEffectHelper = pAoePointEffectContainer->GetEffectHelper( eEffectBindPart_Body );
					if( pEffectHelper)
					{
						// 设置鼠标位置
						POINT ptMouse;
						GetCursorPos( &ptMouse );
						ScreenToClient( g_hWnd, &ptMouse );
						fMouseOnTerrainPosX = ptMouse.x;
						fMouseOnTerrainPosY = ptMouse.y;
						if( PickFromTerrain( fMouseOnTerrainPosX, fMouseOnTerrainPosY ) )
						{
							D3DXVECTOR3 vPos( fMouseOnTerrainPosX, fMouseOnTerrainPosY, g_PickedZFromMouse/*pMe->GetPos().z*/ );
							pMe->SetPointAoePos( vPos );
							pEffectHelper->SetPos( fMouseOnTerrainPosX, fMouseOnTerrainPosY, pMe->GetPos().z );
						}						
					}
				}
			}
		}

		//设定锁定的npc的效果
		guard(test0.3);

		bool bLockPassivityTargetEffectVisible = false;
		bool bLockInitiativeTargetEffectVisible = false;
		float fLockPassivityTargetEffectScale = 0;
		float fLockInitiativeTargetEffectScale = 0;
		float fLockTargetEffectScale = 0;

		CPlayer* pLockPlayer = GetPlayerMgr()->FindByID(GetPlayerMgr()->GetLockPlayerID());
		if (pLockPlayer)
		{
			D3DXVECTOR3 vPos = pLockPlayer->GetPos();
			float fBodySize = pLockPlayer->GetBodySize();
			float fRadius = 0.5f;

			guard(Error);
			if( pLockPlayer->GetAnim() && pLockPlayer->GetAnim()->GetMexCfg() )
			{
				fRadius = pLockPlayer->GetAnim()->GetMexCfg()->m_BodyRadius.m_npRadius.GetNumber();
				fRadius = fRadius*Config::m_fMdlSpaceScale;
			}
			unguard;

			if( g_bTheRoleAttackLockTarget )
			{
				bLockInitiativeTargetEffectVisible = true;
				fLockInitiativeTargetEffectScale = fRadius*fBodySize*Config::m_fMdlSpaceScale;

				CCharEffectContainer* pLockInitiativeTargetEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nLockInitiativeTargetEffectContainerID );
				if( pLockInitiativeTargetEffectContainer )
				{
					IEffectHelper* pEffectHelper = NULL;
					pEffectHelper = pLockInitiativeTargetEffectContainer->GetEffectHelper( eEffectBindPart_Foot );
					if( pEffectHelper)
						pEffectHelper->SetPos( pLockPlayer->GetPos().x, pLockPlayer->GetPos().y, pLockPlayer->GetPos().z );
				}
			}
			else
			{
				bLockPassivityTargetEffectVisible = true;
				fLockPassivityTargetEffectScale = fRadius*fBodySize*Config::m_fMdlSpaceScale;

				CCharEffectContainer* pLockPassivityTargetEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nLockPassivityTargetEffectContainerID );
				if( pLockPassivityTargetEffectContainer )
				{
					IEffectHelper* pEffectHelper = NULL;
					pEffectHelper = pLockPassivityTargetEffectContainer->GetEffectHelper( eEffectBindPart_Foot );
					if( pEffectHelper )
						pEffectHelper->SetPos( pLockPlayer->GetPos().x, pLockPlayer->GetPos().y, pLockPlayer->GetPos().z );
				}
			}
		}

		//////////////
		g_pFlyTextEffect->Update();

		if(g_pPrintTextEffect)
		g_pPrintTextEffect->Update();//lyh++feixingwenzi
		///////////////////

		CWSModelEffect* pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( g_nLockPassivityTargetEffectID );
		if( pModelEffect )
		{
			int nNum = pModelEffect->m_nNumInstance;
			for( int nInst = 0; nInst < nNum; nInst++ )
			{
				CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );
				if( !pInstance )
					continue;

				if( pInstance->bVisible != (BOOL)bLockPassivityTargetEffectVisible )
				{
					pInstance->bVisible = bLockPassivityTargetEffectVisible;

					if( bLockInitiativeTargetEffectVisible )
						pInstance->dwVisibleChangeTime = 0;
					else
						pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
				}

				if( fLockPassivityTargetEffectScale > 0 )
					pInstance->fScale = fLockPassivityTargetEffectScale;
			}
		}
		pModelEffect = NULL;

		pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( g_nLockInitiativeTargetEffectID );
		if( pModelEffect )
		{
			int nNum = pModelEffect->m_nNumInstance;
			for( int nInst = 0; nInst < nNum; nInst++ )
			{
				CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );
				if( !pInstance )
					continue;

				if( pInstance->bVisible != (BOOL)bLockInitiativeTargetEffectVisible )
				{
					pInstance->bVisible = bLockInitiativeTargetEffectVisible;
					pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
				}

				if( fLockInitiativeTargetEffectScale > 0 )
					pInstance->fScale = fLockInitiativeTargetEffectScale;
			}
		}
		pModelEffect = NULL;

		//////////////////////////////////////////////////////////////////////////
		// point aoe
		// added, jiayi, [2009/7/20]
		if( g_nAoePointEffectID != -1 )
		{
			pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( g_nAoePointEffectID );
			if( pModelEffect )
			{
				if( pModelEffect->m_nNumInstance == 2 )
				{
					for( int i = 0 ; i < pModelEffect->m_nNumInstance ; ++ i )
						pModelEffect->GetInstance( i )->bVisible = false;

					if( bSelectingAoePoint && g_bShowAoeSelectEffect && pModelEffect && pMe )
					{
						int nSkillID = GetPlayerMgr()->GetCurUseSkill();
						int nSkillLevel = GetPlayerMgr()->GetCurUseSkillLevel();
						ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( nSkillID, nSkillLevel );			
						if( pSkill )
						{
							int nUseInstance = -1;

							// 判断鼠标与玩家距离是否超过技能设置,改变不同特效
							// 这里约定第一个instance是正常,第二个instance是越界				

							if( pMe->IsInAttackRangeOnlyTwoPoint( fMouseOnTerrainPosX, fMouseOnTerrainPosY, 0, pSkill, true ) )//正常
								nUseInstance = 1; 
							else // 超界
								nUseInstance = 0;

							// 设置特效状态
							CWSModelEffect::Instance* pUseInstance = pModelEffect->GetInstance( nUseInstance );
							CWSModelEffect::Instance* pUnUseInstance = pModelEffect->GetInstance( 1 - nUseInstance );
							pUseInstance->bVisible = true;
							pUnUseInstance->bVisible = false;
							pUseInstance->fScale = pSkill->fAOEradius * Config::m_fMdlSpaceScale;			
						}			
					}
					pModelEffect = NULL;
				}			
			}
		}

		// 人物头顶特效
		pModelEffect = (CWSModelEffect*)GetEffectMgr()->GetEffect( g_nLockTargetEffectID );
		CCharEffectContainer* pLockTargetEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nLockTargetEffectContainerID );
		if( pModelEffect && pLockTargetEffectContainer)
		{
			int nNum = pModelEffect->m_nNumInstance;
			BOOL bVisible = FALSE;
			for( int nInst = 0; nInst < nNum; nInst++ )
			{
				CWSModelEffect::Instance* pInstance = pModelEffect->GetInstance( nInst );
				if( !pInstance )
					continue;

				if( GetPlayerMgr()->GetMe() )
					bVisible = GetPlayerMgr()->GetLockPlayerID() != -1 &&
					GetPlayerMgr()->GetLockPlayerID() != GetPlayerMgr()->GetMe()->GetID();
				if( pInstance->bVisible != bVisible )
				{
					pInstance->bVisible = bVisible;
					pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
				}
				static int lastLockTargetId = -1;
				if (bVisible && lastLockTargetId != GetPlayerMgr()->GetLockPlayerID() && pLockPlayer)
				{
					lastLockTargetId = GetPlayerMgr()->GetLockPlayerID();

					pLockPlayer->CastModelEffect( pModelEffect, pLockTargetEffectContainer, 0 );
					pModelEffect->SetPlayerID(pLockPlayer->GetID());
				}
			}

			if (bVisible && pLockPlayer)
				pLockPlayer->UpdateEffectHelper(pLockTargetEffectContainer);
		}
		pModelEffect = NULL;

		unguard;
	}

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n 33333333333333333 %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	static DWORD dwRoleDeadTime = 0;
	static BOOL bShowRoleDeadMenu = FALSE;

	guard(test05);
	if ( thePlayerRole.GetMyHP() <= 0||(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsDead()) )
	{
		if( !bShowRoleDeadMenu && HQ_TimeGetTime() - dwRoleDeadTime > 2000 )
		{
			theMouseManager.SetCursor( MouseManager::Type_Arrow );
			s_CUI_ID_FRAME_ESCDLG.SetPassWaitForFalse();
			s_CUI_ID_FRAME_ESCDLG.Process();
			bShowRoleDeadMenu = TRUE;
			g_bRotateEnable = FALSE;
		}
	}
	else
	{
		bShowRoleDeadMenu = FALSE;
		dwRoleDeadTime = HQ_TimeGetTime();
	}
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n 5444444444444444444444 %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif
	unguard;
	unguard;


	guard(test06);
	// 播放天气效果
	if( GetPlayerMgr() && GetPlayerMgr()->m_bPlayMapEffect )
	{
		CPlayer* pPlayer = GetPlayerMgr()->GetMe();
		if( pPlayer )
		{
			if( GetMe3dConfig()->IsPlayMapEffect() && pPlayer->GetMapEffectId()/*m_MapEffectId*/ == -1 )
			{
				// 播放
				int nEffect = PlayEffect( (char*)GetPlayerMgr()->m_szPlayMapEffect.c_str(), pPlayer );
				pPlayer->SetMapEffectId(nEffect); //m_MapEffectId = 
			}
			else if( !GetMe3dConfig()->IsPlayMapEffect() && pPlayer->GetMapEffectId()/*m_MapEffectId*/ != -1 )
			{
				// 停止
				IEffect *pEffect = GetEffectMgr()->GetEffect( pPlayer->GetMapEffectId()/*m_MapEffectId*/ );
				if( pEffect )
				{
					pEffect->SetDead();
				}
				pPlayer->SetMapEffectId(-1);//m_MapEffectId = -1;
			}
		}
	}

#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n 555555555555555555 %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif
	unguard;
	CUIMgr::Instance()->ClearHideUI();
	MonsterStatusMgr::Instance()->Update();
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		MeSprintf_s( cOutputString, 2048, "\n ClearHideUI %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	return TRUE;
	unguard;
}

void CHeroGame::EnterWorld(MsgAckEnterWorld *pAckEnterWorld )
{
	guardfunc;

	PlaySoundConfig( SoundConfig::EST_EnterWorld );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      进游戏加载开始", GetCurrentThreadId() );

	m_nLastLandId = -1;
	g_nTheRoleProfession = pAckEnterWorld->charinfo.baseinfo.aptotic.usProfession;

	//	pAckEnterWorld->charinfo.baseinfo
	thePlayerRole.initialize( pAckEnterWorld->charinfo, pAckEnterWorld->dwPlayerDBID );
	thePlayerRole.SetYuanBaoStates(pAckEnterWorld->dwAccountYuanBaoStates);//设置状态值
	thePlayerRole.SetYuanBaoTotle(pAckEnterWorld->dwAccountYuanBaoTotle);

	ChangeGameState( G_SELECT, G_MAIN );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      清除NPC信息", GetCurrentThreadId() );
	// added, jiayi, [2009/9/20], fix bug.
	GetPlayerMgr()->CleaNpcInfos();


	GetMe3dConfig()->m_dwServerStartTime  = pAckEnterWorld->dwStartTime;
	GetMe3dConfig()->m_dwClientStartTime = HQ_TimeGetTime();

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化技能树", GetCurrentThreadId() );
	//Init Skill Tree
	s_CUI_ID_FRAME_SKILL.InitSkillTree();
	s_CUI_ID_FRAME_SKILL.NeedRefresh();

    // UI的初始化逻辑
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化UI逻辑开始", GetCurrentThreadId() );
	CUserData::Instance()->SetRoleString(pAckEnterWorld->charinfo.baseinfo.aptotic.szCharacterName);
    GetUIScriptMgr()->InitAtEnterWorld();
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化UI逻辑结束", GetCurrentThreadId() );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      用户信息创建", GetCurrentThreadId() );
	// 创建UserData
	//lyh++ 创建玩家的用户目录根据玩家名字
	CUserData::Instance()->SetRoleString(pAckEnterWorld->charinfo.baseinfo.aptotic.szCharacterName);
	CUserData::Instance()->CreateUserData();
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      读取角色装备脚本", GetCurrentThreadId() );
	CUserData::Instance()->ReadSuit();

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      创建主角", GetCurrentThreadId() );
	CPlayer *pMe = GetPlayerMgr()->GetMe();	
	if( !pMe )
	{
		GetPlayerMgr()->CreateMe( pAckEnterWorld->header.stID );
		pMe = GetPlayerMgr()->GetMe();
		pMe->SetCharacterID( pAckEnterWorld->dwPlayerCharacterID );
		pMe->SetDefAvaterIndex( pAckEnterWorld->charinfo.visual.defaultModelIndex);
		/*
		 * Author:	2012-7-26 wangshuai
		 * Desc: 	设置CPlayer的HeroID
		 */
		pMe->SetHeroID(pAckEnterWorld->charinfo.baseinfo.liveinfo.hero_id);
	}

	pMe->SetFirstOnline(true);

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      设置主角的信息 (模型信息和游戏信息)", GetCurrentThreadId() );
	// 人物身高
	pMe->SetPlayerScale(pAckEnterWorld->charinfo.visual.fModelPercent);
	pMe->SetMp(thePlayerRole.GetData(CPlayerRole::TYPE_MP));
	pMe->SetMpMax(thePlayerRole.GetData(CPlayerRole::TYPE_MPMAX));

	//国家
	SCharBaseInfo charbaseinfo = pAckEnterWorld->charinfo.baseinfo;
	SCharBaseInfo* pInfo = &charbaseinfo;
	pMe->SetCountry( pInfo->aptotic.ucCountry );
	s_CUI_ID_FRAME_BaseInfo.m_nMoney = 0;
	//国家称号			added by zhuomeng.hu		[9/9/2010]
	pMe->SetRealCountry( pInfo->aptotic.ucCountry );
	pMe->SetCountryTitle( pInfo->liveinfo.nCountryTitle );
    pMe->SetPortraitId( pInfo->aptotic.ucHeadPic );

	pMe->SetMoveRate( pInfo->baseProperty.fightAttr.moveSpeed.final );

	pMe->SetNormalAttackRate( pInfo->baseProperty.fightAttr.attackSpeed.final );
	pMe->SetExact( pInfo->baseProperty.fightAttr.exact.final );
	//pMe->SetShortAtt( pInfo->baseProperty.fightAttr.attack.final );
	//pMe->SetFarAtt( pInfo->baseProperty.fightAttr.attack.final );
	pMe->SetLevel(pInfo->liveinfo.ustLevel );
	pMe->SetRunStep( g_fTheRoleRunningStep );
	pMe->SetReputation(pInfo->liveinfo.reputation);
	pMe->SetExploit(pInfo->liveinfo.exploit);
	//
	// 载入人物资料
	thePlayerRole.SetCharInfo( pAckEnterWorld->charinfo );
	thePlayerRole.SetDuelTarget(-1);

	//装备穿什么和职业，性别有关系。所以要在setcharinfo之后
	pMe->SetProfession( pInfo->aptotic.usProfession );
	pMe->SetSex( pInfo->aptotic.ucSex);

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      根据角色性别设置相机属性", GetCurrentThreadId() );
	if( pInfo->aptotic.ucSex == Sex_Male )
	{
		getwsCamera()->SetLookatPtHeight( g_fMaleLookatPtHeight );
	}

	if( pInfo->aptotic.ucSex == Sex_Female )
	{
		getwsCamera()->SetLookatPtHeight( g_fFemaleLookatPtHeight );
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      设置声音", GetCurrentThreadId() );
	switch( pAckEnterWorld->charinfo.baseinfo.aptotic.ucSex )
	{
	case Sex_Male:
		pMe->SetCreatureSound( "male" );
		break;
	case Sex_Female:
		pMe->SetCreatureSound( "female" );
		break;
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      主角换装", GetCurrentThreadId() );
	SCharVisual* pVisual = &pAckEnterWorld->charinfo.visual;
	pMe->SetHairColorIndex( 0 );                ///*pVisual->nHairColorIndex*/ add by yanli  2010-9-27
    pMe->ShowHelmet( pVisual->IsShowHelmet() );
	pMe->ShowSignature(pVisual->IsShowSignature());
	pMe->ShowAecpratove( pVisual->IsShowAecorative() );
	pMe->SetShowHero(pVisual->IsShowHero());
	pMe->ShowRankTitle(pVisual->IsShowRankTitle());

	pMe->SetRankTitleId( pAckEnterWorld->charinfo.otherdataclient.rankTitle.shCurRankTitleId );

	//pMe->SetCurrSuitIndex(/*pVisual->GetViewSuitIndex()*/0); //add by yanli  2010-9-27
	//if( pAckEnterWorld->charinfo.visual.btCurrentShowSuitIndex )//时装并且换的是属性装
	//{		
	//	const SCharItem* pCharItem = &thePlayerRole.m_pVisual->GetAttriSuitArray()[EPT_RHandItem];
	//	pVisual->GetVisualArray()[EPT_RHandItem] = *pCharItem;

	//	pCharItem = &thePlayerRole.m_pVisual->GetAttriSuitArray()[EPT_LHandItem];	
	//	pVisual->GetViewSuitArray()[EPT_LHandItem] = *pCharItem;
	//}
	//设置法宝ID
	if(pVisual->talisman.itembaseinfo.ustItemID != InvalidLogicNumber)
		pMe->SetTalismanById(pVisual->talisman.itembaseinfo.ustItemID);

	pMe->SetAllEquip(pVisual);
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      施法条UI的加载", GetCurrentThreadId() );
	s_CUI_Progress.LoadUI();
	s_CUI_ID_FRAME_TargetProgrss.LoadUI();
	s_CUI_ID_FRAME_Group_Me.SetVisable( true );

	thePlayerRole.UpdateUI();

	pMe->SetHPInfo( pInfo->liveinfo.nHp, pInfo->baseProperty.fightAttr.hpMax.final );
	// added, jiayi, [2010/2/26],计算装备中最小星级
	pMe->CalcMinimalStar();
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      设置人物称号", GetCurrentThreadId() );
	thePlayerRole.SetTitleListInfo( &pAckEnterWorld->charinfo.baseinfo.liveinfo );
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载软键盘", GetCurrentThreadId() );
	g_shortcutKey_configure.load();
// 	g_timeable_configure.load();

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      刷新包裹物品的CD", GetCurrentThreadId() );
	// 刷新包裹物品CD
	s_CUI_ID_FRAME_PACK.RefreshCooldown();

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      刷新背包物品", GetCurrentThreadId() );
	s_CUI_ID_FRAME_PACK.RefreshNormalPack();
	s_CUI_ID_FRAME_PACK.RefreshMaterialPack();
	s_CUI_ID_FRAME_PACK.RefreshTaskPack();
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      人物装备界面刷新", GetCurrentThreadId() );
	s_CUI_ID_FRAME_BaseProperty.Refresh();
	s_CUI_ID_FRAME_BaseProperty.RefreshEquip();	

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      刷新宠物界面", GetCurrentThreadId() );
	s_CUI_ID_FRAME_Pet.Refresh();
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      刷新称号界面", GetCurrentThreadId() );
	s_CUI_ID_FRAME_Title.NeedRefresh();

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      刷新快捷键", GetCurrentThreadId() );
	s_CUI_ID_FRAME_MainMenu.refreshHotKey();

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      快速换装界面初始化", GetCurrentThreadId() );
	s_CUI_ID_FRAME_ChangeEquip.Init();

	GetBillBoard()->getFirstInfoFromServer( pInfo->liveinfo.dwHelpFlag );

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      设置进度条信息", GetCurrentThreadId() );
	s_CUI_ID_FRAME_LoadMap.SetFloatX(pAckEnterWorld->charinfo.otherdataclient.pos.vPos.x);
	s_CUI_ID_FRAME_LoadMap.SetFloatY(pAckEnterWorld->charinfo.otherdataclient.pos.vPos.y);
	s_CUI_ID_FRAME_LoadMap.SetFloatZ(pAckEnterWorld->charinfo.otherdataclient.pos.vPos.z);
	s_CUI_ID_FRAME_LoadMap.LoadMap( pAckEnterWorld->charinfo.otherdataclient.pos.dwMapID,
		pAckEnterWorld->charinfo.otherdataclient.pos.stX,
		pAckEnterWorld->charinfo.otherdataclient.pos.stY,

		pAckEnterWorld->charinfo.otherdataclient.fDirX,
		pAckEnterWorld->charinfo.otherdataclient.fDirY,  pAckEnterWorld->nGameMapId);
	s_CUI_ID_FRAME_LoadMap.SetVisable(true);
	{
		//added by zilong. 2011-02-21. ------------------------------
		//这里应该加入主角被创建后要初始化的一些内容（这些内容有可能在读取配置时因为主角不存在而没有被设置。）
		InitializeRoleProperty();
		//added by zilong. end. -------------------------------------
	}
	CSystemFamily::Instance()->ClearFamilyInfo();
//lyh++ 玩家进入游戏世界的时候 ，重置跟随目标位 -1； s_CUI_ID_FRAME_Target 和 s_CUI_ID_FRAME_Team这个ui是一直在内存的 ，在login.meui的时候已经加载
	s_CUI_ID_FRAME_Target.SetFollowPlayerId(-1);
	s_CUI_ID_FRAME_Team.SetTeamFollowID(-1);

	s_CUI_ID_FRAME_MiniMap.m_nPlayerRenderFlag = CPlayerMgr::EPlayerRenderFlag::EPRF_ALL;
     GetPlayerMgr()->SetPlayerRenderFlag(CPlayerMgr::EPlayerRenderFlag::EPRF_ALL);
    
	 if(!s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().ReadData(0))
		 s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().LoadDefaultData();

	 PostProcessManager::instance().enableProcess( "Bloom", false );
	unguard;
}

void CHeroGame::ProcessSwitchGateMsg(Msg* pMsg)
{
	MsgSwitchGate* gateinfo = (MsgSwitchGate*)pMsg;

	switch (gateinfo->nResult)
	{
	case ER_Success:
		{
			if( strlen(gateinfo->szGateIP) != 0 && 
				gateinfo->uGatePort != 0)
			{
				if (gateinfo->nServerType == ST_CharacterServer && g_GameState == G_MAIN)
				{
					ChangeGameState(g_GameState, G_LOGIN, false);
					s_CUI_ID_FRAME_LOGIN.SetVisable(false);
					CUI_ID_FRAME_Select::m_time = 1; // 读取时间
				}

				//不知什么意思，为什么还要返回过去一个转换通知？ vy vvx 2012.4.10
				MsgAckSwitchGate msg;
				GettheNetworkInput().SendMsg(&msg);

				CUI_ID_FRAME_LOGIN::g_bSwitchGate = true;
				CUI_ID_FRAME_LOGIN::g_dwSwitchGateTime = HQ_TimeGetTime() + CUI_ID_FRAME_LOGIN::g_dwSwitchGatePeriod;

				CUI_ID_FRAME_LOGIN::g_gateIp = gateinfo->szGateIP;
				CUI_ID_FRAME_LOGIN::g_gatePort = gateinfo->uGatePort;

				s_CUI_ID_FRAME_MiniMap.SetServerName(gateinfo->szChannelName);

				LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Receive MsgSwitchGate \t[%s:%d]", gateinfo->szGateIP, gateinfo->uGatePort);
			}
		}
		break;
	case ER_ThisAccountHaveInPlayer:
		{
			s_CUI_ID_FRAME_MessageBox.closeAll(false);
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_UseOnline), "", 
				CUI_ID_FRAME_MessageBox::eTypeYesNo, true, CUI_ID_FRAME_LOGIN::connectFailed_UserOnline );

			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_ERROR, "Receive MsgSwitchGate \tError[%d]", gateinfo->nResult);

			isShowDisconnetMsg = true;
		}
		break;
	default:
		{
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_ERROR, "Receive MsgSwitchGate \tError[%d]", gateinfo->nResult);

			s_CUI_ID_FRAME_MessageBox.closeAll(false);
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_TimeLongConnectFailed), "", 
				CUI_ID_FRAME_MessageBox::eTypeConfirm, true, CUI_ID_FRAME_LOGIN::connectFailed );

			isShowDisconnetMsg = true;
		}
		break;
	}
}

void CHeroGame::SwitchGate(/*bool _connect*/)
{
	//static int loginFlag = 0;
	DWORD dwTime = HQ_TimeGetTime();

	if (dwTime + CUI_ID_FRAME_LOGIN::g_dwSwitchGatePeriod - CUI_ID_FRAME_LOGIN::g_dwSwitchGateTime > 16 * 10000/* 16s */)
	{
		// 超时
		CUI_ID_FRAME_LOGIN::g_bSwitchGate = false;
		CUI_ID_FRAME_LOGIN::g_bEndGetCharacter = false;
		/*CUI_ID_FRAME_LOGIN::m_bNeedAckAgain =false;*/
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Start connect gate \t[%s:%d] ...", CUI_ID_FRAME_LOGIN::g_gateIp.c_str(), CUI_ID_FRAME_LOGIN::g_gatePort);

	GettheNetworkInput().InitConnect(CUI_ID_FRAME_LOGIN::g_gateIp.c_str(), CUI_ID_FRAME_LOGIN::g_gatePort);

	if (GettheNetworkInput().ConnectToServer(false)&& CUI_ID_FRAME_LOGIN::g_bSwitchGate)
	{
		/*CUI_ID_FRAME_LOGIN::g_bSwitchGate = false;
		return;*/
		/*if ( loginFlag == 0 )
		{
			std::string sessionStr = theHeroGame.GetPlayerMgr()->m_strSessionKey;
			MsgLoginInfo msg;
			msg.nAccountID             = 123;
			strncpy_s( msg.szIP,       sizeof(msg.szIP ),      "127.0.0.1",        sizeof(msg.szIP)-1)       ;
			strncpy_s( msg.SessionKey, sizeof(msg.SessionKey), sessionStr.c_str(),	   sizeof(msg.SessionKey )-1 );
			strncpy_s( msg.szAccount,  sizeof(msg.szAccount),  "123",				   sizeof(msg.szAccount)-1   );
			strncpy_s( msg.Password,   sizeof(msg.Password),   "123",				   sizeof(msg.Password)-1    );
			strncpy_s( msg.Seed ,      sizeof(msg.Seed),       "" ,					   sizeof(msg.Seed)-1        );
			msg.isWallow               = false;
			GettheNetworkInput().SendMsg(&msg);
			loginFlag++;
			return;
		}*/
		
		/*if((_connect&&GettheNetworkInput().ConnectToServer(16)))
		{
			CUI_ID_FRAME_LOGIN::g_bSwitchGate = false;
			CUI_ID_FRAME_LOGIN::g_bEndGetCharacter = TRUE;
			CUI_ID_FRAME_LOGIN::m_bNeedAckAgain = false;

			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Connect gate succeed!");

			MsgAllocGWID allgwid;
			allgwid.nAccountID = GetPlayerMgr()->m_dwAccountID;
			allgwid.nIsSwitchGame = g_GameState == G_MAIN;
			strncpy(allgwid.SessionKey, GetPlayerMgr()->m_strSessionKey.c_str(),sizeof(allgwid.SessionKey)-1);
			strncpy(allgwid.szAccount, theHeroGame.m_szUserName, sizeof(allgwid.szAccount)-1);
			GettheNetworkInput().SendMsg(&allgwid);

			MsgGetCharacter getChar;
			strncpy(getChar.szAccount, theHeroGame.m_szUserName, sizeof(getChar.szAccount)-1);
			getChar.nAccountID = GetPlayerMgr()->m_dwAccountID;
			strncpy(getChar.SessionKey, GetPlayerMgr()->m_strSessionKey.c_str(), sizeof(allgwid.SessionKey)-1);
			getChar.dwCharacterId = g_nCharacterDBID;
			getChar.stWitchSlot = GetPlayerMgr()->sPlayerSlot;
			GettheNetworkInput().SendMsg(&getChar);
		}
		else if (!_connect)*/
		{
			CUI_ID_FRAME_LOGIN::g_bSwitchGate = false;
			CUI_ID_FRAME_LOGIN::g_bEndGetCharacter = TRUE;
			/*CUI_ID_FRAME_LOGIN::m_bNeedAckAgain = false;*/

			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Connect gate succeed!");

			MsgAllocGWID allgwid;
			allgwid.nAccountID = GetPlayerMgr()->m_dwAccountID;
			allgwid.nIsSwitchGame = g_GameState == G_MAIN;
			/*strncpy(allgwid.SessionKey, GetPlayerMgr()->m_strSessionKey.c_str(),sizeof(allgwid.SessionKey)-1);*/
			allgwid.SessionKey = GetPlayerMgr()->m_SessionKey;
			strncpy(allgwid.szAccount, theHeroGame.m_szUserName, sizeof(allgwid.szAccount)-1);
			GettheNetworkInput().SendMsg(&allgwid);

			MsgGetCharacter getChar;
			strncpy(getChar.szAccount, theHeroGame.GetUserName(), sizeof(getChar.szAccount)-1);
			getChar.nAccountID = GetPlayerMgr()->m_dwAccountID;
			/*strncpy(getChar.SessionKey, GetPlayerMgr()->m_strSessionKey.c_str(), sizeof(allgwid.SessionKey)-1);*/
			getChar.SessionKey = GetPlayerMgr()->m_SessionKey;
			getChar.dwCharacterId = g_nCharacterDBID;
			getChar.stWitchSlot = theHeroGame.GetPlayerMgr()->sPlayerSlot;
			GettheNetworkInput().SendMsg(&getChar);
			
		}
//		MsgAllocGWID allgwid;
//#ifdef __NEW_LOGIN__
//		allgwid.nAccountID = GetPlayerMgr()->m_dwAccountID;
//		allgwid.nIsSwitchGame = g_GameState == G_MAIN;
//		strcpy(allgwid.SessionKey, GetPlayerMgr()->m_strSessionKey.c_str());
//		strncpy(allgwid.szAccount, theHeroGame.m_szUserName, sizeof(allgwid.szAccount)-1);
//#endif
//		GettheNetworkInput().SendMsg(&allgwid);

		/*MsgGetCharacter getChar;
		strncpy(getChar.szAccount, theHeroGame.m_szUserName, sizeof(getChar.szAccount)-1);
		getChar.nAccountID = GetPlayerMgr()->m_dwAccountID;
#ifdef __NEW_LOGIN__
		strcpy(getChar.SessionKey, GetPlayerMgr()->m_strSessionKey.c_str());
#else
		getChar.SessionKey = GetPlayerMgr()->m_dwSessionKey;
#endif
		getChar.dwCharacterId = g_nCharacterDBID;
		getChar.stWitchSlot = GetPlayerMgr()->sPlayerSlot;
		GettheNetworkInput().SendMsg(&getChar);*/

		if (g_GameState == G_LOGIN)
		{
// 			s_CUI_ID_FRAME_Select.LoadUI();
//             s_CUI_ID_FRAME_Select.SetVisable( true );

// 			s_CUI_ID_FRAME_LOGIN.m_dwLoginStartTime = HQ_TimeGetTime();
		}

		//LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Send    MsgGetCharacter");
	}
	else if (CUI_ID_FRAME_LOGIN::g_bSwitchGate == false)
	{
		if( g_GameState == G_LOGIN )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_TimeLongConnectFailed), "", 
				CUI_ID_FRAME_MessageBox::eTypeConfirm, true, CUI_ID_FRAME_LOGIN::connectFailed );
		}
		else
		{
			s_CUI_ID_FRAME_MessageBox.closeAll(false);
			// added, [2/4/2010 jiayi],添加错误码
			char acErrorString[256] = {0};
			struct tm nowtime;
			GetNowTime(nowtime);
			MeSprintf_s( acErrorString, 256, "%02d:%02d:%02d%s[-]", nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec, theXmlString.GetString(eText_Disconnect)/*, GettheNetworkInput().GetCriticalError()*/ ); 
			s_CUI_ID_FRAME_MessageBox.Show(
				acErrorString,
				acErrorString,
				CUI_ID_FRAME_MessageBox::eTypeConfirm,
				true,
				CUI_ID_FRAME_ExitGame::BackToLogin );

			s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);//.m_pID_BUTTON_COMFIRM->SetEnable(true);
			s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);//.m_pID_BUTTON_COMFIRM->SetVisable(true);

		}

		isShowDisconnetMsg = true;

		Sleep(100);
	}
}


void CHeroGame::UpdateMsg(void)
{	
	guardfunc;   
	g_MessageProcess.UpdateMsg();
	unguard;
}

void CHeroGame::JumpToWorldFromTransport( int nMapId, int nTargetId )
{

	MexAnimCtrl::SetGameTime( HQ_TimeGetTime() );
	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapId);
	CResMgr* pResMgr = pTile->GetCResMgr();
	double posx, posy;
	Assert( pResMgr );
	{
		for(UINT i=0; i<pResMgr->GetTransportCount(); i++)
		{
			CTransportResBase* pTransport = pResMgr->Transport(i);
			if( !pTransport->IsTransport() && pTransport->GetNtargetID() == nTargetId)	
			{
				CTargetRes* pTarget = (CTargetRes*)pTransport;
				posx = pTarget->GetPosX();
				posy = pTarget->GetPosY();
				break;
			}
		}
	}

	s_CUI_ID_FRAME_LoadMap.SetFloatX(posx);
	s_CUI_ID_FRAME_LoadMap.SetFloatY(posy);
	s_CUI_ID_FRAME_LoadMap.SetFloatZ( WORLD_HEIGHT );
	DebugLogout( "%s", "Begin UI_ID_FRAME_LoadMap::LoadMap" );
	s_CUI_ID_FRAME_LoadMap.LoadMap( nMapId,
		0,
		0,
		1,0);
	s_CUI_ID_FRAME_LoadMap.SetVisable(true);
}

void CHeroGame::UpdateKeyState()
{
	m_nCurrKeyChangeNum = 0;
	DIDEVICEOBJECTDATA didod[ SAMPLEKEY_BUFFER_SIZE ];  // Receives buffered data 
	DWORD              dwElements;
	DWORD              i;
	HRESULT            hr;


	dwElements = SAMPLEKEY_BUFFER_SIZE;
	if( g_pKeyboard )
	{
		hr = g_pKeyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), didod, &dwElements, 0 );
		if( FAILED(hr) ) 
		{
			hr = g_pKeyboard->Acquire();

			while( hr == DIERR_INPUTLOST )
			{
				hr = g_pKeyboard->Acquire();
			}
		}
	}

	if( g_pKeyboard && HasFocus() && IsActiveWindow() && SUCCEEDED(hr) )
	{
		memcpy(m_LastKeyStates, m_CurrKeyStates, sizeof(BOOL)*256);
		if( !FAILED(hr) ) 
		{
			for( i = 0; i < dwElements; i++ ) 
			{
				int nIndex = didod[i].dwOfs;

				if( nIndex < 0x01 || nIndex > DIK_MEDIASELECT )
					continue;

				if( didod[i].dwData == 0x80 && !m_CurrKeyStates[nIndex] )
				{
					m_CurrKeyChangeList[m_nCurrKeyChangeNum].nKeyIndex = nIndex;
					m_CurrKeyChangeList[m_nCurrKeyChangeNum].bPressed = TRUE;
					m_CurrKeyStates[nIndex] = TRUE;
					m_nCurrKeyChangeNum++;
				}
				else if( didod[i].dwData == 0 && m_CurrKeyStates[nIndex] )
				{
					m_CurrKeyChangeList[m_nCurrKeyChangeNum].nKeyIndex = nIndex;
					m_CurrKeyChangeList[m_nCurrKeyChangeNum].bPressed = FALSE; 
					m_CurrKeyStates[nIndex] = FALSE;
					m_nCurrKeyChangeNum++;
				}
			}
		}
	}
	else
		memset(m_CurrKeyStates, 0, sizeof(BOOL)*256);
}

//显示玩家
void RenderPlayer( int iPlayerID )
{
	guardfunc;
	theHeroGame.GetPlayerMgr()->RenderPlayer( NULL ,iPlayerID );
	unguard;
}

// added, jiayi, [2009/10/10]
// 更改dump文件名
bool ModifyDumpFilename( const char* pszCurrentDumpFilename, // 修改前dump文件名
						const char* pszVideoCardName,		 // 显卡名称
						const char* pszMacString,			 // mac地址
						bool bRunning,						 // 游戏是否已经运行起来
						std::string* pNewName				 // 新文件名
						)
{
	_finddata_t filedata;
	intptr_t ret = _findfirst( pszCurrentDumpFilename, &filedata );
	if( ret == -1 )
		return false;
	if( !pszCurrentDumpFilename )
		return false;

	std::string strOldName( pszCurrentDumpFilename );
	std::string strPostfix = strOldName.substr( strOldName.length() - 4 );
	std::string strPrefix = strOldName.substr( 0, strOldName.length() - 4 );
	// 添加显卡信息
	strPrefix += "- " + std::string( pszVideoCardName );
	// 添加mac地址和运行信息
	strPrefix += "- " + std::string( pszMacString );
	if( bRunning )
		strPrefix += "- InGame";
	else
		strPrefix += "- OutGame";

	*pNewName = strPrefix + strPostfix;

	//改文件名
	rename( pszCurrentDumpFilename, pNewName->c_str() );

	return true;

}

// added, jiayi, [2009/10/10]
// 获得mac地址，只取一个，不一定是当前使用的地址
void GetMACAddressString( std::string* pStrMacString )
{
	PIP_ADAPTER_ADDRESSES pAddresses;
	pAddresses = (IP_ADAPTER_ADDRESSES*) malloc(sizeof(IP_ADAPTER_ADDRESSES));
	ULONG outBufLen = 0;
	DWORD dwRetVal = 0;

	// Make an initial call to GetAdaptersAddresses to get the 
	// size needed into the outBufLen variable
	if (GetAdaptersAddresses(AF_INET, 
		0, 
		NULL, 
		pAddresses, 
		&outBufLen) == ERROR_BUFFER_OVERFLOW) {
			free(pAddresses);
			pAddresses = (IP_ADAPTER_ADDRESSES*) malloc(outBufLen);
	}

	// Make a second call to GetAdapters Addresses to get the
	// actual data we want
	if ((dwRetVal = GetAdaptersAddresses(AF_INET, 
		0, 
		NULL, 
		pAddresses, 
		&outBufLen)) == NO_ERROR) {
			// If successful, output some information from the data we received
			PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses;
			if (pCurrAddresses) {
				//只返回一个mac地址就行了		
				char szByte[255];
				for( DWORD dwIndex = 0 ; dwIndex < pCurrAddresses->PhysicalAddressLength ; ++ dwIndex )
				{
					BYTE bi = pCurrAddresses->PhysicalAddress[dwIndex];
					itoa( bi, szByte, 16 );
					*pStrMacString += std::string( szByte ) + std::string("-");
				}
				if( pStrMacString->length() > 0 )
					*pStrMacString = pStrMacString->substr( 0, pStrMacString->length() - 1 );
			}
	}
	else { 
		printf("Call to GetAdaptersAddresses failed.\n");
		LPVOID lpMsgBuf;
		if (FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwRetVal,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL )) {
				printf("\tError: %s", lpMsgBuf);
		}
		LocalFree( lpMsgBuf );
	}
	free(pAddresses);
}

void CHeroGame::SendCrashEmail( const char* pszDumpFileName,const char* pszDumpResult /*= NULL*/ )
{
	//
	return;
	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)(INT_PTR)(theHeroGame.m_iDefaultMouseSpeed), 0);

	DumpInfo dumpinfo;
	std::string to("jiayi.zhang@tolez.com"); 
	std::string from("jiayi.zhang@tolez.com"); 
	std::string smtpserver("mail.tolez.com"); 
	std::string macAddr = "";
	if( theHeroGame.m_bGetMacAddr )
		macAddr = theHeroGame.m_strMacAddr;
	else
		GetMACAddressString( &macAddr );
	std::string content;
	content += theHeroGame.GetDeviceStates(); 
	content += "\nVersion:";
	content += ApplicationConfig::Instance().GetFullVersion();	
	// memory
	char acTemp[255] = {0};
	MEMORYSTATUS M;
	GlobalMemoryStatus(&M);
	MeSprintf_s( acTemp,sizeof(acTemp)/sizeof(char) - 1 ,"\n总物理内存: %d, 可用物理内存: %d.\n总虚拟内存: %d, 可用虚拟内存: %d", 
		M.dwTotalPhys / 1024 / 1024, M.dwAvailPhys / 1024 / 1024,
		M.dwTotalVirtual / 1024 / 1024, M.dwAvailVirtual / 1024 / 1024);
	content += acTemp;

	content += "\n当前目录:";
	//返回当前目录
	char szText[256] = {0};
	GetCurrentDirectory(sizeof(szText)/sizeof(char) - 1,szText);

	content += szText;
	content += "\n";

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if ( pMe )
	{
		// server name
		content += "\nServerName:";
		content +=s_CUI_ID_FRAME_LOGIN.GetServer(); 

		// character name
		content += "\nCharacterName:";	 	
		content += pMe->GetName();

		if(pszDumpResult && strlen(pszDumpResult) > 0)
			content += pszDumpResult;

		// map name	
		memset( acTemp, 0, sizeof( acTemp ) );
		MeSprintf_s( acTemp,sizeof(acTemp)/sizeof(char) - 1, "\n地图id: %d", EctypeId2MapId(theHeroGame.GetLandID()) );
		content += acTemp;		

		// customsystemsetting.xml
		char szSetting[MAX_PATH] = {0};
		MeSprintf_s( szSetting, MAX_PATH, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );		
		dumpinfo.m_strCustomSystemSettingFile = szSetting;

		// customgamesetting.xml
		MeSprintf_s( szSetting, MAX_PATH, "%s%s", CUserData::Instance()->GetAccountDataPath(), SystemSetting::Instance()->GetCustomSettingFile() );
		dumpinfo.m_strCustomGameSettingFile = szSetting;

	}
	// change dump filename
	std::string strNewDumpFilename;
	ModifyDumpFilename( pszDumpFileName, theHeroGame.GetDeviceStates(), macAddr.c_str(), !( pMe == 0 ), &strNewDumpFilename );
	dumpinfo.m_strContent = content;
	dumpinfo.m_strDumpFileName = strNewDumpFilename;

	dumpinfo.SaveDumpInfo();

	// start dumpreport
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	if( !::CreateProcess( TEXT("BugReporter.exe"),
		NULL, // Command line. 
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi )             // Pointer to PROCESS_INFORMATION structure.
		)
	{
		dumpinfo.DeleteTempFile();
	}
	/*mail.operator()(); */

}

#define guardsmtp try{
#define unguardsmtp     }catch(char*Err){throw Err;}catch(...){/*appUnwindf("%s",__FUNC_NAME__);*/ SendCrashEmail();	}

#include "StringLanguageTranslator.h"

//#define LOG4CPP_CONFIG "config/log.config"

extern "C" 
{
#include "Luaplus/lua/lua.h"
#include "Luaplus/lua/lauxlib.h"
#include "Luaplus/lua/lualib.h"
}
#include "NewWithDebug.h"

class SwMemleakCleaner
{
public:
	SwMemleakCleaner()
	{
		GetAllocInfo();
		GetPointerInfo();
		GetAutoIntLock();
	}
	~SwMemleakCleaner()
	{
		delete &GetAutoIntLock();
		delete &GetPointerInfo();
		delete &GetAllocInfo();
	}

};
SwMemleakCleaner cleaner;
#include "LuaScript.h"
void RetrieveRegionServerIpPort(const char* lwrCmd);

void CheckMemoryStatus()
{
	return;
	MEMORYSTATUS M;
	GlobalMemoryStatus(&M);
	// 之前已经用了近200M，所以只检测400M
	if( M.dwAvailPhys > 1024 * 1024 * 400 )// 可用内存小于600MB,关闭客户端，给出提示
		return;

	char acError[256] = {0};
	strcpy_s( acError, 256, theXmlString.GetString( eError_ClientMemoryLack ));
	int nRet = MessageBoxA( NULL, acError, acError, MB_ICONERROR|MB_YESNO );
	if(  nRet != IDYES )
	{
		::TerminateProcess( ::GetCurrentProcess(), 0 );	
		return;
	}

}

//#define PLAYER_NAME_KEY        TEXT("Software\\Tolez\\Sanguo")
//void WriteSettings()
//{
//	HKEY hkey;
//	if( ERROR_SUCCESS == RegCreateKeyEx( HKEY_CURRENT_USER, PLAYER_NAME_KEY, 
//		0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, NULL ) )
//	{
//		DXUtil_WriteStringRegKey( hkey, TEXT("CPID"), ::GetCurrentProcessId() );
//		RegCloseKey( hkey );
//	}
//}

#ifdef NPGUARD
//LYH NP
bool NP_Init()
{
    npgl = new CNPGameLib("SGCN");
	assert(npgl);
	DWORD dwResult = npgl->Init();

	if (dwResult != NPGAMEMON_SUCCESS)
	{

		NpInit_dwResult = dwResult;

		switch (dwResult)
		{

		case NPGAMEMON_ERROR_EXIST:

			wsprintf(lpszMsg, "GameGuard正在运行，请重新启动计算机后再执行游戏");
			bAppExit = true;
			break;

		case NPGAMEMON_ERROR_GAME_EXIST:

			
			wsprintf(lpszMsg, "客户端不允许多开或GameGuard重复运行,结束游戏后请重试");
            bAppExit = true;
			break;

		case NPGAMEMON_ERROR_INIT:

           wsprintf(lpszMsg, "GameGuard初始化错误！①如果更新了系统漏洞补丁请重启计算机后执行游戏②如果杀毒软件将其阻挡请关闭杀毒软件。若还不能正常游戏请将GameGuard文件夹压缩后发送到邮箱gghelp@gameguard.cn");
			bAppExit = true;
			break;

		case NPGAMEMON_ERROR_AUTH_GAMEGUARD:

		case NPGAMEMON_ERROR_NFOUND_GG:

		case NPGAMEMON_ERROR_AUTH_INI:

		case NPGAMEMON_ERROR_NFOUND_INI:	
           wsprintf(lpszMsg, "sgcn.ini或GameGuard.des配置文件不存在或已损坏,请重新安装游戏或者拷贝正常的文件并复制到游戏主程序同级目录下");
            bAppExit = true;
			break;

		case NPGAMEMON_ERROR_CRYPTOAPI:

			
			wsprintf(lpszMsg, "Windows系统文件rsabase.dll有可能被损坏,请修复该DLL与系统");
            bAppExit = true;
			break;

		case NPGAMEMON_ERROR_EXECUTE:

			wsprintf(lpszMsg, "GameGuard执行失败。请删除GameGuard文件夹运行游戏或重新安装游戏");
            bAppExit = true;
			break;

		case NPGAMEMON_ERROR_ILLEGAL_PRG:

			wsprintf(lpszMsg, "检测到非法程序，请关闭与游戏无关的程序后执行游戏");
            bAppExit = true;
			break;

		case NPGMUP_ERROR_ABORT:

			wsprintf(lpszMsg, "GameGuard更新被中断，请检查网络状况或个人防火墙设置");
            bAppExit = true;
			break;

		case NPGMUP_ERROR_CONNECT:
			wsprintf(lpszMsg, "请检查本机所在的网络通讯状况是否存在不稳定状态，以及是否防火墙拦截了GameGuard与升级服务器的会话，以确保GameGuard的正常更新（建议重新启动路由器）");
            bAppExit = true;
			break;

		case NPGAMEMON_ERROR_GAMEGUARD:
			wsprintf(lpszMsg, "GameGuard初始化错误或者使用了一个旧版本的GameGuard.请删除GameGuard文件夹或重新安装客户端");
            bAppExit = true;
			break;

		case NPGMUP_ERROR_PARAM:
			wsprintf(lpszMsg, ".ini 文件不存在或被更改。请重新安装客户端");
			bAppExit = true;
			break;

		case NPGMUP_ERROR_INIT:
			wsprintf(lpszMsg, "npgmup.des初始化错误。请删除GameGuard文件夹后重新执行游戏");
            bAppExit = true;
			break;

		case NPGMUP_ERROR_DOWNCFG:

			wsprintf(lpszMsg, "连接GameGuard更新服务器失败!请检查网络设置或重新连接");
            bAppExit = true;
			break;

		case NPGMUP_ERROR_AUTH:
           wsprintf(lpszMsg, "请确定防火墙的设置未拦截GameGuard更新，并检查本机所在的网络通讯状况是否存在不稳定状态。如果上述一切正常请删除游戏目录下的GameGuard文件夹，重新运行游戏或者在正常游戏的玩家电脑中拷贝GameGuard文件夹替换游戏目录中的GameGuard文件夹.");
			bAppExit = true;
			 break;

		case NPGAMEMON_ERROR_NPSCAN:

			wsprintf(lpszMsg, "因内存空间不足或已感染病毒，病毒和间谍程序扫描模块加载失败");
            bAppExit = true;
			break;

		case NPGG_ERROR_COLLISION:
			wsprintf(lpszMsg, "您电脑中运行着其他游戏反外挂程序和GameGuard存在冲突，请关闭其他游戏后再执行游戏.");
            bAppExit = true;
			break;

		default: //相关信息显示

			wsprintf(lpszMsg, "GameGuard运行发生错误，请发送客户端文件夹下的GameGuard文件夹至gghelp@gameguard.cn或客服人员.");
            bAppExit = true;
				break;

		}


		if (bAppExit)
		{
			
			
			return !bAppExit;
		}


		//根据自身情况请提示相应信息

		

	}

	return true;
}
BOOL CALLBACK NPGameMonCallback(DWORD dwMsg, DWORD dwArg)
{   if(!npgl)
       return false;
	char szHackInfo[MAX_PATH] = {0,};
	strcpy_s(szHackInfo, npgl->GetInfo());
	switch (dwMsg)	
	{	
	case NPGAMEMON_COMM_ERROR:
		return false;

	case NPGAMEMON_COMM_CLOSE:
		{
			bAppExit = true;  //结束代码
			return false;
		}

	case NPGAMEMON_INIT_ERROR:
		{
			wsprintf(g_szHackMsg, "GameGuard 初始化错误: %lu", dwArg);
			bAppExit = true;  //结束代码
			return false;
		}

	case NPGAMEMON_SPEEDHACK:
		{
			wsprintf(g_szHackMsg, _T("检测到加速外挂"));
			bAppExit = true;  //结束代码
			break;
		}

	case NPGAMEMON_GAMEHACK_KILLED:
		{

			wsprintf(g_szHackMsg, "检测到外挂.\r\n%s", npgl->GetInfo());
			bAppExit = true;  //结束代码
			return false; 
		}

	case NPGAMEMON_GAMEHACK_DETECT:
		{
			wsprintf(g_szHackMsg, "检测到外挂.\r\n%s", npgl->GetInfo());
			bAppExit = true;  //结束代码
			return false;
		}

	case NPGAMEMON_GAMEHACK_DOUBT:
		{
			wsprintf(g_szHackMsg, "游戏或GameGuard已被篡改");
			bAppExit = true;  //结束代码
			return false;
		}

	case NPGAMEMON_GAMEHACK_REPORT:
		{

			DWORD dwHackInfoSize = 0;
			LPBYTE pHackInfo = NULL;
			pHackInfo = npgl->GetHackInfo(&dwHackInfoSize); 
			if (pHackInfo && dwHackInfoSize > 0)	
			{
				// 该部分函数GameGuard不提供 

			}
			return false;
		}
	case NPGAMEMON_CHECK_CSAUTH3:
		{
			PCSAuth3Data pCSAuth3 = (PCSAuth3Data)dwArg;
			// 当仅仅CS认证响应值是当前的服务器时，发送服务器 (如果不是即抛弃)
			if( pCSAuth3->dwServerNumber == g_dwServerNumber)
			{
				//SendToServer( pCSAuth3->bPacket, pCSAuth3->dwPacketSize );
				MsgCheckCSAuthAck msg;
				msg.PlayerID = thePlayerRole.GetDBID();
				msg.size = pCSAuth3->dwPacketSize;
				memcpy(msg.packet,pCSAuth3->bPacket,msg.size);
				GettheNetworkInput().SendMsg(&msg);
				break;
			}
		}
		return true;
	}
	return true;  //继续	
}

#endif


#include "Common.h"
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, INT iShow )
{
#ifdef _DEBUG
	MessageBox(NULL,"debug","debug",MB_OK);
#endif
	guardfunc;
	{
		/*int ClientCnt = 0;
		PROCESSENTRY32 pe;
		HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
		pe.dwSize=sizeof(PROCESSENTRY32);
		if(!Process32First(hSnapshot,&pe))
			return false;
		while(1)
		{
			pe.dwSize=sizeof(PROCESSENTRY32);
			if(Process32Next(hSnapshot,&pe)==FALSE)
				break;
			if(stricmp(pe.szExeFile,"Client.exe")==0)
			{
				++ClientCnt;
			}
		}*/

		/*if ( ClientCnt > 2)
		{
			CloseHandle(hSnapshot);
			MessageBox(NULL,"你的客户端开启数量已达上限，无法开启！","错误",MB_OK);
			return 0;
		}*/
	}

	#ifdef NPGUARD
	//LYH NP
	if(!NP_Init())
	{
		delete npgl;
		npgl = NULL;
	}
#endif

	//切换当前路径为EXE文件所在路径
	TCHAR FilePath[_MAX_PATH ] = {0};
	TCHAR Drive[_MAX_DRIVE];
	TCHAR Dir[_MAX_DIR];
	TCHAR FileTitle[_MAX_FNAME];
	TCHAR FileExt[_MAX_EXT];
	GetModuleFileName(NULL,FilePath,MAX_PATH);
	_splitpath_s(FilePath,Drive,Dir,FileTitle,FileExt);
	sprintf( FilePath, "%s%s", Drive,Dir );
	SetCurrentDirectory(FilePath);

	
	// 获取鼠标默认速度
	int iDefaultMouseSpeed = 0;
	SystemParametersInfo(SPI_GETMOUSESPEED, 0, &iDefaultMouseSpeed, 0);
	theHeroGame.SetDefaultMouseSpeed(iDefaultMouseSpeed);

	CreateDirectory("Log",NULL);
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	MiniDumper dumper( "YQDQ", ApplicationConfig::Instance().GetFullVersion(), "application error"/*theXmlString.GetString( eDumper_MessageBox_ClientError )*/ );
//     try
//     {
// //        LOG_CONFIGURE(LOG4CPP_CONFIG);
//     }
//     catch(ConfigureException &)
//     {
//     }
//#ifndef _DEBUG
//	dumper.pCrashFunc_WithPath = CHeroGame::SendCrashEmail;	
//#endif // _DEBUG

	gCfg.m_bUiViewer = false;

	//theHeroGame.m_RunType = -1;
	const char* DELIM = " ";
	char* szCmdLine = lpCmd;
	char lwrCmd[MAX_PATH] = {0};
	MeSprintf_s(lwrCmd, sizeof(lwrCmd)-1, "%s", szCmdLine);
	strlwr(lwrCmd);

	// 客户端登陆类型
	s_CUI_ID_FRAME_LOGIN.SetClientLoginType("geren");
	std::string command = lwrCmd;
	size_t findpos = command.find("-t:");
	if (findpos != std::string::npos)
	{
		std::string type = command.substr(findpos);
		size_t endpos = type.find(" ");
		if (endpos != std::string::npos)
			type = type.substr(0, endpos);
		s_CUI_ID_FRAME_LOGIN.SetClientLoginType(type.substr(3));
		// 如果类型字符串长度超过10，则用默认替代
		if( s_CUI_ID_FRAME_LOGIN.GetClientLoginLen() > 10 )
			s_CUI_ID_FRAME_LOGIN.SetClientLoginType("geren");
	} 

	/*
	 * 2012.7.11 wangshuai
	 * 根据策划要求, 默认是nolauncher
	 lyh修改， 当是发布版的时候 如果直接执行client.exe 则打开 launch程序启动
	 */
	/*if (szCmdLine != 0 && strstr(lwrCmd,"-launch"))*/


	//lyh++ 加一个配置文件标志是否读取打包内容 ，主要针对策划用的。策划可以，等到正式发布，把这个文件删除即可
  
	
#ifdef NDEBUG  //只有Release进来


	char* _command = GetCommandLine();
	if ( (szCmdLine == 0 || strlen(szCmdLine) == 0) &&  strstr(_command,"-NP") == NULL)
	{
		char cszWorkingDir[MAX_PATH] = {0};
		_getcwd( cszWorkingDir, MAX_PATH );
		char gameDataDir[MAX_PATH] = {0};	
		MeSprintf_s(gameDataDir,sizeof(gameDataDir)/sizeof(char) - 1, "%s\\..\\Launcher\\Launcher.exe", cszWorkingDir);
		// Start the child process. 
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		if( !CreateProcess( TEXT(gameDataDir),   // No module name (use command line). 
			NULL, // Command line. 
			NULL,             // Process handle not inheritable. 
			NULL,             // Thread handle not inheritable. 
			FALSE,            // Set handle inheritance to FALSE. 
			0,                // No creation flags. 
			NULL,             // Use parent's environment block. 
			NULL,             // starting directory. 
			&si,              // Pointer to STARTUPINFO structure.
			&pi )             // Pointer to PROCESS_INFORMATION structure.
			) 
		{
			if( pi.hThread )
			{
				CloseHandle(pi.hThread);
				pi.hThread = NULL;
			}

			ZeroMemory( &si, sizeof(si) );
			si.cb = sizeof(si);
			ZeroMemory( &pi, sizeof(pi) ); 

			MeSprintf_s(gameDataDir,sizeof(gameDataDir)/sizeof(char) - 1, "%s\\..\\Launcher.exe", cszWorkingDir);
			if( !CreateProcess( TEXT(gameDataDir),   // No module name (use command line). 
				NULL, // Command line. 
				NULL,             // Process handle not inheritable. 
				NULL,             // Thread handle not inheritable. 
				FALSE,            // Set handle inheritance to FALSE. 
				0,                // No creation flags. 
				NULL,             // Use parent's environment block. 
				NULL,             // starting directory. 
				&si,              // Pointer to STARTUPINFO structure.
				&pi )             // Pointer to PROCESS_INFORMATION structure.
				) 
			{
				MessageBox( NULL, "需要从Launcher启动 ", "启动出错", MB_OK | MB_ICONERROR );
				if( pi.hThread )
				{
					CloseHandle(pi.hThread);
					pi.hThread = NULL;
				}
			}
		}
		return 0;
	}
#endif
	// 是否读大包
// 	g_DirectReadInPackage = false;
// 	if (strstr(lwrCmd,"-package"))
// 	{
// 		g_DirectReadInPackage = true;
// 	}

	// 是否读大包
	if (strstr(lwrCmd,"-package"))
	{
		packet_namespace::s_PacketRootPath=GetRootPath();
		packet_namespace::SetReadPacket(true);
		packet_namespace::openpacket(PACKET_AUDIO_DATA);
		packet_namespace::openpacket(PACKET_CONFIG_DATA);
		packet_namespace::openpacket(PACKET_AVATAR_DATA);
		packet_namespace::openpacket(PACKET_CHARACTER_DATA);
		packet_namespace::openpacket(PACKET_EFFECT_DATA);
		packet_namespace::openpacket(PACKET_MAGIC_DATA);
		packet_namespace::openpacket(PACKET_QUEST_DATA);
		packet_namespace::openpacket(PACKET_SCENE_DATA );
		

		packet_namespace::openpacket(PACKET_TERRAIN_DATA);
		packet_namespace::openpacket(PACKET_TEXTURE_DATA);
		packet_namespace::openpacket(PACKET_UI_DATA);
		packet_namespace::openpacket(PACKET_WORLD_DATA);

		packet_namespace::openpacket(PACKET_CONFIG_CLIENT_DATA);

	}
	
	theHeroGame.SetTrue3D( false );
	if (strstr(lwrCmd,"-full"))
	{
		theHeroGame.SetTrue3D( true );
	}

	// 从命令行获取大区、服务器、IP和端口数据
	RetrieveRegionServerIpPort(lwrCmd);
	if ( szCmdLine != 0)
	{
		if ( strstr(lwrCmd,"-ui") )
		{
			gCfg.m_bUiViewer = true;
		}
		else if (strstr(lwrCmd,"-c") )
		{
			CustomConsole::RedirectIoToConsole();
		}
	}

	//获取exe所在路径
	char szModuleName[MAX_PATH] = {0};
	GetModuleFileName(NULL, szModuleName, MAX_PATH);
	int nLength = strlen(szModuleName);
	for (int i=nLength-1; i>0; i--)
	{
		if (szModuleName[i] == '\\')
		{
			szModuleName[i] = '\0';
			break;
		}
	}

	//为方便调试指定程序所在目录,DEBUG版下不强制设置当前目录
#ifndef _DEBUG
	//设置exe所在路径为当前目录
	int nRet = ::_chdir(szModuleName);
#endif
	theHeroGame.PreCreate();

	//初始化cfg
	gCfg.InitializeConfig();
	MiniDumper::set_upload_info(gCfg.DumpFtpUser,gCfg.DumpFtpPwd,gCfg.DumpFtpUrl,gCfg.bUploadDump);
	
	s_CUI_ID_FRAME_LOGIN.LoadServerList();
	//load setting
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
	SystemSetting::Instance()->LoadLastSetting( szSetting );	
	SystemSetting::Instance()->LoadSetting( szSetting );
	g_nWindowMode = SystemSetting::Instance()->GetLevel( 
		SystemSetting::eSSC_WINDOWMODE );//是否窗口模式

	int nResolution = SystemSetting::Instance()->GetLevel( 
		SystemSetting::eSSC_RESOLUTION );//是否窗口模式
	if (nResolution > 1000)
	{
		SCREEN_WIDTH = ((nResolution) >> 16) & 0x0000FFFF;
		SCREEN_HEIGHT = nResolution & 0x0000FFFF;

		if (SCREEN_WIDTH < 1024)
		{
			SCREEN_WIDTH = 1024;
		}

		if (SCREEN_HEIGHT < 768)
		{
			SCREEN_HEIGHT= 768;
		}
	}
	SystemSetting::Instance()->SetResolutionValueOnly( SCREEN_WIDTH, SCREEN_HEIGHT );

	if( theHeroGame.Create( hInst ) != S_OK )
	{
		theHeroGame.CloseLauncher();   
		return 0;
	}
	theHeroGame.CloseLauncher();   

	// added, jiayi, [2010/5/31]
	CheckMemoryStatus();

	int nBigArea = 0;

	if (gCfg.m_bIsOpenResourceCkeck)
	{
		char filename[MAX_PATH] = {0};
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/DATA/files_info.data", GetRootPath());
		Md5Manager::Instance().Initialize( filename );
		Md5Manager::Instance().EnableMD5Validate(true);
	}
	else
	{
		Md5Manager::Instance().EnableMD5Validate(false);
	}

	srand( HQ_TimeGetTime() );
	g_hInst = hInst;

	Logger::initialize();
	//Init Config
	GetSystemConfig();
	LOGINFO("WinMain");

	if( lpCmd && strlen( lpCmd ) > 0 )
	{
		if( 3 == sscanf( lpCmd,"%s%d%d",theTestMap.szTerrainFile,&theTestMap.x,&theTestMap.y ) )
		{
			theTestMap.bTestMap = true;			
			gCfg.m_bLocalVersion = true;
		}
		if( 1 == sscanf( lpCmd, "%d", &nBigArea) )
		{

		}

	}
	nBigArea = nBigArea < ( s_CUI_ID_FRAME_LOGIN.GetBigAreaCount() -1) ? nBigArea :( s_CUI_ID_FRAME_LOGIN.GetBigAreaCount() - 1 );

	g_pApp  = &theHeroGame;

	s_CUI_ID_FRAME_MAIN.SetFullSceenValue(gCfg.m_bFullScreen);

	gCfg.m_bFullScreen = FALSE;
	theHeroGame.m_bFullScreen = gCfg.m_bFullScreen;

	//GetMeNetwork().SocketStartUp();
	if (!network::net_init(eN_Client_BigBufferSize,
					       eN_Client_BigBufferNum,
						   eN_Client_SmallBufferSize,
						   eN_Client_SmallBufferNum,
						   eN_Client_ListenNum,
						   eN_Client_SocketNum,
						   eN_Client_ThreadNum))
	{
		return 0;
	}

	ShowWindow( theHeroGame.GetHWnd(), SW_SHOW );
	SetForegroundWindow( theHeroGame.GetHWnd() );
	SetFocus( theHeroGame.GetHWnd() );

	//ExitSplash();	

// 	try
// 	{
// 		ScriptManager::instance().compile();
// 	}
// 	catch ( const LuaException& e )
// 	{
// 		OutputDebugString( e.GetErrorMessage() );
// 	}

	LOGSAVE;
	int iRet = theHeroGame.Run();
	//GetMeNetwork().SocketCleanUp();
	packet_namespace::release();
	GettheNetworkInput().Destroy();
	network::net_release();
	return iRet;

	unguard;
}
#ifdef _DEBUG

class detectLeakImpl
{
public:
	~detectLeakImpl(){
		MeMemoryTracker::Instance()->OutputMemInfo();
		MeMemoryTracker::Shutdown();
	}
};
detectLeakImpl kDetectLeak;

#endif //MEDEBUG

HRESULT CHeroGame::InitDirectInput( HWND hWnd )
{
	guardfunc;
	HRESULT hr;
	BOOL    bExclusive = FALSE;
	BOOL    bForeground = FALSE;
	DWORD   dwCoopFlags = 0;

	FreeDirectInput();

	if( bExclusive )
		dwCoopFlags = DISCL_EXCLUSIVE;
	else
		dwCoopFlags = DISCL_NONEXCLUSIVE;

	if( bForeground )
		dwCoopFlags |= DISCL_FOREGROUND;
	else
		dwCoopFlags |= DISCL_BACKGROUND;

	// Create a DInput object
	if( FAILED( hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (VOID**)&g_pDI, NULL ) ) )
		return hr;

	// Obtain an interface to the system mouse device.
	if( FAILED( hr = g_pDI->CreateDevice( GUID_SysMouse, &g_pMouse, NULL ) ) )
		return hr;

	if( FAILED( hr = g_pMouse->SetDataFormat( &c_dfDIMouse2 ) ) )
		return hr;

	hr = g_pMouse->SetCooperativeLevel( hWnd, dwCoopFlags );

	if( hr == DIERR_UNSUPPORTED && !bForeground && bExclusive )
	{
		FreeDirectInput();
		MessageBox( hWnd, _T("SetCooperativeLevel() returned DIERR_UNSUPPORTED.\n")
			_T("For security reasons, background exclusive mouse\n")
			_T("access is not allowed."), 
			_T("Mouse"), MB_OK );
		return S_OK;
	}

	if( FAILED(hr) )
		return hr;

	{
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj        = 0;
		dipdw.diph.dwHow        = DIPH_DEVICE;
		dipdw.dwData            = SAMPLE_BUFFER_SIZE; // Arbitary buffer size

		if( FAILED( hr = g_pMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
			return hr;
	}
	g_pMouse->Acquire();

	bExclusive = FALSE;
	bForeground = TRUE;
	dwCoopFlags = 0;

	if( bExclusive )
		dwCoopFlags = DISCL_EXCLUSIVE;
	else
		dwCoopFlags = DISCL_NONEXCLUSIVE;

	if( bForeground )
		dwCoopFlags |= DISCL_FOREGROUND;
	else
		dwCoopFlags |= DISCL_BACKGROUND;

	// added, [9/25/2010 zhangjiayi]
	SAFE_RELEASE( g_pDI );

	if( FAILED( hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (VOID**)&g_pDI, NULL ) ) )
		return hr;

	// Obtain an interface to the system keyboard device.
	if( FAILED( hr = g_pDI->CreateDevice( GUID_SysKeyboard, &g_pKeyboard, NULL ) ) )
		return hr;

	if( FAILED( hr = g_pKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
		return hr;

	hr = g_pKeyboard->SetCooperativeLevel( hWnd, dwCoopFlags );
	if( hr == DIERR_UNSUPPORTED && !bForeground && bExclusive )
	{
		FreeDirectInput();
		MessageBox( hWnd, _T("SetCooperativeLevel() returned DIERR_UNSUPPORTED.\n")
			_T("For security reasons, background exclusive keyboard\n")
			_T("access is not allowed."), _T("Keyboard"), MB_OK );
		return S_OK;
	}

	if( FAILED(hr) )
		return hr;

	{
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj        = 0;
		dipdw.diph.dwHow        = DIPH_DEVICE;
		dipdw.dwData            = SAMPLEKEY_BUFFER_SIZE; // Arbitary buffer size

		if( FAILED( hr = g_pKeyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
			return hr;
	}

	g_pKeyboard->Acquire();

	/////////////////////
	for( int i = 0; i < DIK_MEDIASELECT + 1; i++ )
	{
		g_nKeydownGameAction[i] = -1;
		g_nKeyupGameAction[i] = -1;
	}

	return S_OK;
	unguard;
}

void CHeroGame::FreeDirectInput()
{
	if( g_pMouse ) 
		g_pMouse->Unacquire();

	if( g_pKeyboard )
		g_pKeyboard->Unacquire();

	SAFE_RELEASE( g_pMouse );
	SAFE_RELEASE( g_pKeyboard );
	SAFE_RELEASE( g_pDI );
}

BOOL GameExit()
{
	return g_DynamicMapLoadThreadWillExit;
}
//第2等级数据从点击进入游戏开始加入
void CHeroGame::LoadConfigProc()
{
	guardfunc;
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载游戏数据(读表)开始", GetCurrentThreadId() );
    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Config, 0.0f );

	char strName[MAX_PATH] = {0};
	char strHeroString[MAX_PATH] = {0};
	char strErrorFmt[MAX_PATH] = "数据异常，请检查客户端版本，或下载最新客户端！";
	char strErrorMsg[MAX_PATH] = {0};

// #if LOAD_COST_TIME_DEBUG
// 	DWORD nLastTimeRecord = HQ_TimeGetTime();
// 	char cOutputString[2048];
// #endif
// 	MeSprintf_s(strName, sizeof(strName)/sizeof(char)-1, "%s\\Data\\Config\\Item\\", SwGlobal::GetWorld()->GetAppDataCharDir());
// 	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载ItemDetail", GetCurrentThreadId() );
// 	if(!GetItemDetailConfig().LoadItemDetailConfig( strName ))
	MeSprintf_s(strName, sizeof(strName)/sizeof(char)-1, "%s\\Data\\Config\\Data.config", SwGlobal::GetWorld()->GetAppDataCharDir());
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载BinItemDetail", GetCurrentThreadId() );
	if(!GettheItemDetail().LoadBinFile( strName ))
	{
		MeSprintf_s(strName, sizeof(strName)/sizeof(char)-1, "%s\\Data\\Config\\Item\\", SwGlobal::GetWorld()->GetAppDataCharDir());
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载ItemDetail", GetCurrentThreadId() );
		if(!GetItemDetailConfig().LoadItemDetailConfig( strName ))
		{
			MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "Data %s", strErrorFmt);
			MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
			::TerminateProcess( ::GetCurrentProcess(), 0 );
		}


		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载怪物数据", GetCurrentThreadId() );
		// 加载怪物数据
		MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\Monster.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
		if (!theItemDetailConfig.LoadXmlMonster(strName))
		{
			MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "Monster %s", strErrorFmt);
			MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
			::TerminateProcess( ::GetCurrentProcess(), 0 );
		}

		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载怪物声音", GetCurrentThreadId() );
		// 加载怪物声音
		MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\CreatureSound.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
		if (!theItemDetailConfig.LoadXmlCreatureSound( strName ))
		{
			MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "CreatureSound %s", strErrorFmt);
			MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
			::TerminateProcess( ::GetCurrentProcess(), 0 );
		}

		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载坐骑属性", GetCurrentThreadId() );
		// 加载坐骑属性
		MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\Mount.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
		if (!theItemDetailConfig.LoadXmlMount( strName ))
		{
			MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "CreatureSound %s", strErrorFmt);
			MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
			::TerminateProcess( ::GetCurrentProcess(), 0 );
		}

		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载装备随机属性", GetCurrentThreadId() );
		// 加载装备随机属性
		MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\EquipmentRandom.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
		if (!theItemDetailConfig.LoadXmlRand( strName ))
		{
			MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "EquipmentRandom %s", strErrorFmt);
			MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
			::TerminateProcess( ::GetCurrentProcess(), 0 );
		}
		
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载副将属性", GetCurrentThreadId() );
		// 加载副将属性
		MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\Pet.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
		if (!theItemDetailConfig.LoadXmlPetMonster( strName ))
		{
			MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "Pet %s", strErrorFmt);
			MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
			::TerminateProcess( ::GetCurrentProcess(), 0 );
		}
	}

	//加载武将数据表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\SanGuoLord.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	MeSprintf_s(strHeroString,sizeof(strHeroString)/sizeof(char)-1,"%s\\Data\\Config\\SanGuoLord.string",SwGlobal::GetWorld()->GetAppDataCharDir());
	if (!theItemHero.LoadHeroConfig( strName,strHeroString))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "SanGuoLord %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	//加载太平幻境数据
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\tphj.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if (!theTPHJManager.LoadConifg( strName))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "TaiPingHuanJing %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	//zhuxincong 10.9加载夸地图寻路数据
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1,"%s\\Data\\Config\\Kwamemap.config",SwGlobal::GetWorld()->GetAppDataCharDir());
	if (!theKwamemap.LoadConfigFile(strName))
	{
		MeSprintf_s(strErrorMsg,sizeof(strErrorMsg)-1,"Kwamema %s",strErrorFmt);
		MessageBox(hWndSplash,strErrorMsg,"Error",MB_OK);
		::TerminateProcess(::GetCurrentProcess(),0);
	}

	//加载随身商店数据
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1,"%s\\Data\\Config\\PocketShop.config",SwGlobal::GetWorld()->GetAppDataCharDir());
	if (!thePocketShopManager.LoadConifg(strName))
	{
		MeSprintf_s(strErrorMsg,sizeof(strErrorMsg)-1,"PocketShop %s",strErrorFmt);
		MessageBox(hWndSplash,strErrorMsg,"Error",MB_OK);
		::TerminateProcess(::GetCurrentProcess(),0);
	}

// #if LOAD_COST_TIME_DEBUG
// 	DWORD nThisTimeRecord = HQ_TimeGetTime();
// 	MeSprintf_s( cOutputString, 2048, "\nItemDetail:%d\n", nThisTimeRecord - nLastTimeRecord );
// 	nLastTimeRecord = nThisTimeRecord;
// 	OutputDebugStr(cOutputString);
// #endif
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载怪物状态配置", GetCurrentThreadId() );
	// 加载怪物状态配置
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\MonsterStatus.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if (!theMonsterStatusConfig.LoadConfig( strName ))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "MonsterStatus %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	//added by zilong. 2011-02-18. ------------------------------------
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载心法配置表", GetCurrentThreadId() );
	if(!theXinFaConfig.LoadXinFaConfig( XINFACONFIG_FILEPATH ))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "心法配置表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}
	//added by zilong. end. -------------------------------------------

	//将魂配置
	//if(!theHeroSoullConfig.LoadHeroSoullConfig( HEROSOULLCONGIGPATH ))
	//{
	//	MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "HeroSoull %s", strErrorFmt);
	//	MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
	//	::TerminateProcess( ::GetCurrentProcess(), 0 );
	//}

	//added by zilong. 2011-03-07. ------------------------------------
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载装备打孔成功率配置表", GetCurrentThreadId() );
	if(!theEquipEvolveConfig.LoadStilettoConfig( EQUIPSTILETTO_FILEPATH ))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "装备打孔成功率 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}
	//added by zilong. end. -------------------------------------------

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载特效怪配置表", GetCurrentThreadId() );
	if(!theEffectCharConfig.LoadEffectCharConfig( EFFECTCHAR_FILEPATH ))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "特效怪配置表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	if(!theIntensifyEffect.LoadIntensifyEffectConfig( "..\\data\\config\\EquipIntensifyEffect.config" ))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "装备强化配置表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}



    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Config, 0.75f );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载称号", GetCurrentThreadId() );
	// 称号表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\title.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theTitleConfig.LoadTitleConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "称号表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载升星表", GetCurrentThreadId() );
	// 升星表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\StarLevelUp.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theStarLevelUpConfig.LoadResourceConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "升星表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载坐骑强化表", GetCurrentThreadId() );
	// 坐骑强化表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\MountStrengthen.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theMountStrengthenConfig.LoadResourceConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "坐骑强化表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载装备属性系数表", GetCurrentThreadId() );
	// 装备属性系数表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\EquipScoreRatio.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theEquipScoreRatioConfig.LoadEquipScoreRatioConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "装备属性系数表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载卡牌表", GetCurrentThreadId() );
	// 卡牌表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\CardIcon.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theCardIconConfig.LoadCardIconConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "卡牌表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载卡牌成就表", GetCurrentThreadId() );
	// 卡牌成就表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\CardAchieve.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theCardAchieveConfig.LoadCardAchieveConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "卡牌成就表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载七天乐表", GetCurrentThreadId() );
	// 七天乐表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\SevenDays.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theSevenDaysConfig.LoadSevenDaysConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "七天乐表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载军阶表", GetCurrentThreadId() );
	// 军阶表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\RankTitle.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theRankTitleConfig.LoadRankTitleConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "军阶表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      国家称号", GetCurrentThreadId() );
	// 国家称号
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\CountryTitle.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theCountryTitleConfig.LoadCountryTitleConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "国家称号 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      狩猎表", GetCurrentThreadId() );
	// 狩猎表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\HuntingQuest.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theHuntingQuestConfig.LoadHuntingQuestConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "狩猎表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      铸魂表", GetCurrentThreadId() );
	// 铸魂表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\Soul.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theSoulConfig.LoadSoulConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "铸魂表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载TimeString表", GetCurrentThreadId() );
	// TimeString
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\TimeString.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theTimeStringConfig.LoadTimeStringConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "TimeString表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载配方表", GetCurrentThreadId() );
	// 配方表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\Recipe.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !theRecipeConfig.LoadData( strName ) )
	{
		assert( 0 && "配方表读取失败" );
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "配方表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}	

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载摆摊费率表", GetCurrentThreadId() );
	// 摆摊费率表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\Stall.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if( !GetStallConfig().LoadStallConfig( strName ) )
	{
		assert( 0 && "摆摊费率表" );
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "摆摊费率表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}	

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载评估表", GetCurrentThreadId() );
	// 读随机属性评估表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\PropertyEvaluate.config", GetRootPath());
	if( !theRandPropEvaluate.LoadConfig(strName) )
	{
		Assert(0 && "PropertyEvaluate.config加载失败！");
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "属性评估表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载奖品表", GetCurrentThreadId() );
	// 幸运15关奖品配置
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\Luck.config", GetRootPath() );
	if( !theLuckRewardConfig.LoadLuckRewardConfig( strName ) )
	{
		Assert( 0 && "LuckReward.config加载失败" );
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "奖品表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载帮派设置列表", GetCurrentThreadId() );
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\GuildSetting.config", GetRootPath() );
	if( !theGuildConfig.LoadConfig( strName ) )
	{
		Assert( 0 && "GuildSetting.config加载失败" );
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "帮派设置 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载帮派战设置列表", GetCurrentThreadId() );
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\GuildBattle.config", GetRootPath() );
	if( !theCampGuildBattleConfig.LoadConfig( strName ) )
	{
		Assert( 0 && "GuildBattle.config加载失败" );
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "帮派战设置 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}
	/*LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载国王争夺战设置列表", GetCurrentThreadId() );
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\KingBattle.config", GetRootPath() );
	if( !theKingCampBattleConfig.LoadConfig( strName ) )
	{
		Assert( 0 && "KingBattle.config加载失败" );
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "帮派战设置 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}*/

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载国家表", GetCurrentThreadId() );
	// 国家配置
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\Country.config", GetRootPath() );
	if( !theCountryConfig.LoadCountryConfig( strName ) )
	{
		Assert( 0 && "Country.config加载失败" );
		MeSprintf_s( strErrorMsg, sizeof( strErrorMsg )-1, "国家配置表 %s", strErrorFmt );
		MessageBox( hWndSplash, strErrorMsg, "Error", MB_OK );
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      信息显示分类表", GetCurrentThreadId() );
    // 加载信息显示分类表       added by ZhuoMeng.Hu		[11/18/2010]
    if( !CScreenInfoManager::Instance()->LoadScreenInfoConfig( "..\\Data\\Config\\ScreenInfo.config" ) )
    {
        Assert( 0 && "ScreenInfo.config加载失败" );
        MeSprintf_s( strErrorMsg, sizeof( strErrorMsg )-1, "信息显示分类表 %s", strErrorFmt );
        MessageBox( hWndSplash, strErrorMsg, "Error", MB_OK );
        ::TerminateProcess( ::GetCurrentProcess(), 0 );
    }

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载宝箱表", GetCurrentThreadId() );
	// 宝箱配置
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\data\\config\\TreasureBox.config", GetRootPath() );
	if( !theTreasureBoxConfig.LoadConfig( strName ) )
	{
		Assert( 0 && "TreasureBox.config failed " );
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "宝箱表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}	

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载五行表", GetCurrentThreadId() );
	// 五行表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s/data/config/ArmourElements.config", GetRootPath() );
	if( !theArmourElementsConfig.LoadArmourElementsConfig( strName ) )
	{
		Assert( 0 && "五行表错误" );
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "五行表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载倒计时送礼表", GetCurrentThreadId() );
	// 倒计时送礼表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s/data/config/OnLineTimeReward.config", GetRootPath() );
	if( !theOnLineRewardConfig.LoadOnLineRewardConfig(strName) )
	{
		Assert( 0 && "倒计时送礼表错误" );
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "送礼表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

// #if LOAD_COST_TIME_DEBUG
// 	nThisTimeRecord = HQ_TimeGetTime();
// 	MeSprintf_s( cOutputString, 2048, "\nOtherConfig1:%d\n", nThisTimeRecord - nLastTimeRecord );
// 	nLastTimeRecord = nThisTimeRecord;
// 	OutputDebugStr(cOutputString);	
// #endif
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载模型表", GetCurrentThreadId() );
	// Model表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s/data/config/Model.config", GetRootPath() );
	if( !theModelConfig.LoadModelConfig(strName) )
	{
		assert(false && "Model.config读取文件出错");
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "模型表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载好友表", GetCurrentThreadId() );
	// 好友表
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\Relation.config", GetRootPath() );
	if( !theRelationConfig.LoadRelationConfig(strName) )
	{
		assert(false && "Friendly.config读取文件出错");
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "好友表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\ItemCompose2.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if ( !theItemComposeConfig.LoadItemComposeConfig2( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "ItemCompose2 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\Achieve.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if ( !theAchieveConfig.LoadAchieveConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "Achievements %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\Sound.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if ( !theSoundConfig.LoadSoundConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "Sound %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
	}

	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\FamilySetting.config", GetRootPath() );
	if ( !theFamilyConfig.LoadConfig( strName ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "Family %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
	}

	ModelConfig::modeliter iter;
	if( theModelConfig.m_mapModelData.size() > 0 )
	{
		for(iter = theModelConfig.m_mapModelData.begin(); iter != theModelConfig.m_mapModelData.end(); ++iter)
		{
			GetMexResMgr()->AddFile( iter->second.FilePath.c_str(), iter->first, iter->second.HeadPicture.c_str(), false );
		}
	}
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载Other表", GetCurrentThreadId() );

	//任务委托
	if(!s_CUI_ID_FRAME_QuestEntrust.GetConfig().LoadQuestEntrustConfig(QUESTENTRUSTCONFIG_FILEPATH))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "QuestEntrust %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
	}

	theChangeCountryConfig.LoadConfigFile();

	if(!ThreeDayConfig::Instance().LoadThreeDayConfig(THREEDAYCONFIGPATH))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "ThreeDay %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
	}

	if(!YuanBaoTotleConfig::Instance().LoadYuanBaoTotleConfig(YUANBAOCONFIGPATH))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "YuanBaoTotleStates %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
	}

	if (!MountMoveStarConfig::Instance().LoadMountMoveStarConfig(MOUNTMOVESTAR_FILEPATH_CONFIG))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "MountMoveStarConfig %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
	}


	if (!PetSpeakConfig::Instance().LoadPetSpeakConfig(PETSPEAKPATH))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "PetSpeakConfig %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
	}


	if (!TextHyberOtherConfig::Instance().LoadTextHyberOtherConfig(TEXTHYBEROTHERPATH))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "TextHyberOtherConfig %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
	}

	

	
	thePetDefineConfig.LoadFileConfigPath(PETDEFINECONFIG_FILEPATH);

// #if LOAD_COST_TIME_DEBUG
// 	nThisTimeRecord = HQ_TimeGetTime();
// 	MeSprintf_s( cOutputString, 2048, "\nOtherConfig2:%d\n", nThisTimeRecord - nLastTimeRecord );
// 	nLastTimeRecord = nThisTimeRecord;
// 	OutputDebugStr(cOutputString);	
// #endif

	// 加载最佳装备说明
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载最佳装备说明", GetCurrentThreadId() );

	if ( !FindBestEquip::Instance()->LoadXml() )
	{
		//MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "BestEquipInfo %s", strErrorFmt);
		//MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		//::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	if( GameExit() )
	{
		return;
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      初始化 Lua", GetCurrentThreadId() );
	g_IniScriptEngine( "../Data/Ui/Lua" );
	if( GameExit() )
	{
		return;
	}

	if( GameExit() )
	{
		return;
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载经验表", GetCurrentThreadId() );
	// 经验表
	char pszFullPath[MAX_PATH] = {0};
	MeSprintf_s( pszFullPath, sizeof(pszFullPath)/sizeof(char) -1, "%s\\Data\\Config\\LevelExperience.config", GetRootPath() );
	if( !theExpStage.LoadFromConfig( pszFullPath ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "经验表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}
	if( GameExit() )
	{
		return;
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载套装表", GetCurrentThreadId() );
	// 套装表
	if( !theSuitOperateConfig.LoadSuitLevelUpConfig( "..\\Data\\Config\\SuitOperate.config" ) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "套装表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}
// #if LOAD_COST_TIME_DEBUG
// 	nThisTimeRecord = HQ_TimeGetTime();
// 	MeSprintf_s( cOutputString, 2048, "\nOtherConfig3:%d\n", nThisTimeRecord - nLastTimeRecord );
// 	nLastTimeRecord = nThisTimeRecord;
// 	OutputDebugStr(cOutputString);	
// #endif

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载人物动作表", GetCurrentThreadId() );
	// 人物动作表
	MoreActionClient::Initialize();

	// 加载天气系统配置文件
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载天气系统", GetCurrentThreadId() );	
	MeSprintf_s( pszFullPath, sizeof(pszFullPath)/sizeof(char) -1, "%s\\Data\\Config\\WeatherEvent.config", GetRootPath() );
	WeatherEventManager::Instance()->InitializeWeather( pszFullPath );

	if( GameExit() )
	{
		return;
	}	
	bool bOK = CStdCharSkeleton::Instance()->LoadCfg();
	if( GameExit() )
	{
		return;
	}
// #if LOAD_COST_TIME_DEBUG
// 	nThisTimeRecord = HQ_TimeGetTime();
// 	MeSprintf_s( cOutputString, 2048, "\n人物动作表:%d\n", nThisTimeRecord - nLastTimeRecord );
// 	nLastTimeRecord = nThisTimeRecord;
// 	OutputDebugStr(cOutputString);	
// #endif

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载NPC表", GetCurrentThreadId() );
	// 读NPC String
    char filename[MAX_PATH] = {0};
	MeSprintf_s( filename, sizeof(filename)/sizeof(char) -1, "%s\\Data\\Config\\Npc.string", GetRootPath());
	theXmlString.LoadStringFile(filename,false,false);

	thePlayerRole.FillRequirementQuestArr();

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载杀怪统计表", GetCurrentThreadId() );
	// 杀怪计数表
	MeSprintf_s( filename, sizeof(filename)/sizeof(char) -1, "%s\\Data\\Config\\KillMonsterCount.config",GetRootPath());
	if(!theKillMonsterCountConfig.LoadKillMonsterCountConfig(filename))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "杀怪计数表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载道具合成表", GetCurrentThreadId() );
	// 读道具合成表
	MeSprintf_s( filename, sizeof(filename)/sizeof(char) -1, "%s\\Data\\Config\\ItemCompose.config",GetRootPath());
	if(!theItemComposeConfig.LoadItemComposeConfig(filename))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "道具合成表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载表情动作表", GetCurrentThreadId() );
	// 表情动作表
	MeSprintf_s( filename, sizeof(filename)-1, "%s\\Data\\Config\\ExpAction.config", GetRootPath() );
	if( !theExpActionConfig.LoadExpActionConfig(filename) )
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "表情动作表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}
// #if LOAD_COST_TIME_DEBUG
// 	nThisTimeRecord = HQ_TimeGetTime();
// 	MeSprintf_s( cOutputString, 2048, "\nOtherConfig4:%d\n", nThisTimeRecord - nLastTimeRecord );
// 	nLastTimeRecord = nThisTimeRecord;
// 	OutputDebugStr(cOutputString);	
// #endif

	LOG_MESSAGE(INFO_LOG,LOG_PRIORITY_INFO,"ThreadId: %d  未知装备鉴定表",GetCurrentThreadId());
	//未知装备鉴定
	MeSprintf_s(filename,sizeof(filename) - 1,"%s\\Data\\Config\\EquipUnknowIdentify.config",GetRootPath());
	if(!theEquipEvolveConfig.LoadUnknowIdentifyConfig(filename))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "未知装备鉴定表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE(INFO_LOG,LOG_PRIORITY_INFO,"ThreadId: %d  宠物配置表",GetCurrentThreadId());
	//宠物配置表
	MeSprintf_s(filename,sizeof(filename) - 1,"%s\\Data\\Config\\PetSetting.config",GetRootPath());
	if(!thePetSettingConfig.LoadPetSettingConfig(filename))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "宠物配置表 %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载装备品质属性", GetCurrentThreadId() );
	// 加载装备品质属性
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\EquipQualityIntensity.config", SwGlobal::GetWorld()->GetAppDataCharDir() );
	if (!theItemDetailConfig.LoadXmlEquipQualityIntensity( strName ))
	{
		MeSprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "EquipQualityIntensity %s", strErrorFmt);
		MessageBox(hWndSplash, strErrorMsg, "Error", MB_OK);
		::TerminateProcess( ::GetCurrentProcess(), 0 );
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      法宝属性", GetCurrentThreadId() );
	MeSprintf_s(strName,sizeof(strName),"%s\\Data\\Config\\TalismanSetting.Config",GetRootPath());
	if(!theTalismanConfig.LoadTalismanConfig(strName))
	{
		MeSprintf_s(strErrorMsg,sizeof(strErrorMsg),"法宝配置表 %s",strErrorFmt);
		MessageBox(hWndSplash,strErrorMsg,"Error",MB_OK);
		::TerminateProcess(::GetCurrentProcess(),0);
	}

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      场景表", GetCurrentThreadId() );
	MeSprintf_s(strName,sizeof(strName),"%s\\Data\\Config\\SceneAction.config",GetRootPath());
	if(!theScenePlay.LoadSceneConfig(strName))
	{
		MeSprintf_s(strErrorMsg,sizeof(strErrorMsg),"场景行为表 %s",strErrorFmt);
		MessageBox(hWndSplash,strErrorMsg,"Error",MB_OK);
		::TerminateProcess(::GetCurrentProcess(),0);
	}

    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Config, 1.0f );
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载游戏数据(读表)结束", GetCurrentThreadId() );

	//套装的配置文件
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      套装属性", GetCurrentThreadId() );
	MeSprintf_s(strName,sizeof(strName),"%s\\Data\\Config\\SuitDefine.Config",GetRootPath());
	if(!theSuitConfig.LoadFilePath(strName))
	{
		MeSprintf_s(strErrorMsg,sizeof(strErrorMsg),"套装配置表 %s",strErrorFmt);
		MessageBox(hWndSplash,strErrorMsg,"Error",MB_OK);
		::TerminateProcess(::GetCurrentProcess(),0);
	}

	unguard;
}

void    CHeroGame::DisConnect()
{
	GettheNetworkInput().Close();
}

//#ifdef USE_OLD_LOGIN
BOOL	CHeroGame::StartConnectToGate( const char *szDstIP, int iPort )
{
	guardfunc;
	DWORD dwThreadId = 0;
	DWORD dwThrdParam = 1;
	//
	strcpy(m_szDstIP, szDstIP);
	m_iPort = iPort;

	g_bConnectSuccFlag = false;

	//建立和服务的连接
	GettheNetworkInput().InitConnect(m_szDstIP, m_iPort);
	if (GettheNetworkInput().ConnectToServer(false))
	{
		g_bConnectSuccFlag = true;
	}
	//DWORD  dwTime = HQ_TimeGetTime();
	//while (1)
	//{
	//	if (GettheNetworkInput().ConnectToServer())
	//	{
	//		g_bConnectSuccFlag = true;
	//		break;
	//	}
	//	//if (HQ_TimeGetTime() - dwTime > 1000 * 10) //try 10 秒
	//	//	break;
	//	//
	//	Sleep(100);
	//	//
	//}

	return g_bConnectSuccFlag;
	unguard;
}

#ifdef USE_OLD_LOGIN
bool CHeroGame::login2LoginServer( const char *szUserName, const char *szPassword, int isSoftKeyboardChar,bool isForced)
{
	guardfunc;
	if( !g_bConnectSuccFlag )
		return false;

	//if (theHeroGame.m_LoginName != 0 && theHeroGame.m_LoginPWD != 0)
	//{
	//	if (strstr(szUserName,theHeroGame.m_LoginName) == NULL)
	//	{
	//		strcpy(m_szUserName, theHeroGame.m_LoginName);
	//		strcpy(m_szPassword, theHeroGame.m_LoginPWD);
	//		UI_MessageBox::Show(theXmlString.GetString(eTell_NameAndPWD_Lock),theHeroGame.m_szUserName);
	//		return false;
	//	}
	//}	
	//else
	{
		strcpy(m_szUserName, szUserName);
		strcpy(m_szPassword, szPassword);
	}

	s_CUI_ID_FRAME_LOGIN.SetLoginInfo(theXmlString.GetString(eText_NowTryConnecting));

	//s_CUI_ID_FRAME_LOGIN.SetLoginInfo(theXmlString.GetString(eText_Connected) );
	DWORD  dwTime = HQ_TimeGetTime();
	//static char szBuf[30000];
	static Msg*	pMsg = NULL;

	//s_CUI_ID_FRAME_LOGIN.SetLoginInfo(theXmlString.GetString(eText_SendRightCheck) );
	//发送和server的握手消息
	//发送《天》验证消息
	//MsgRightCheck RightCheck;
	//RightCheck.dwClientVersion = _GAMEVERSION_;
	//   int nRet = GettheNetworkInput().SendMsg( (char*)&RightCheck, RightCheck.GetLength() );

	/*static unsigned long ulgameversion = 10097;*/
	//发送验证码的同时发送检测
	MsgRightCheck2 RightCheck2;
	strcpy(RightCheck2.szGameVersion,ApplicationConfig::Instance().GetFullVersion());
	RightCheck2.checkplayer.nNum = rand()%(MsgCheckPlayerEnterWorld::e_iMaxNum);
	if (RightCheck2.checkplayer.nNum < 2)
	{
		RightCheck2.checkplayer.nNum  = 2;
		RightCheck2.checkplayer.nInstead = 2;
	}

	RightCheck2.checkplayer.nInstead = rand()%RightCheck2.checkplayer.nNum;

	if (RightCheck2.checkplayer.nInstead < 2)
	{
		RightCheck2.checkplayer.nInstead = 2;
	}

	RightCheck2.dwGameVerSion[0]=ApplicationConfig::Instance().GetMajorVersion();
	RightCheck2.dwGameVerSion[1]=ApplicationConfig::Instance().GetMinorVersion();
	RightCheck2.dwGameVerSion[2]=ApplicationConfig::Instance().GetBuildVersion();
	RightCheck2.dwGameVerSion[3]=ApplicationConfig::Instance().GetRevisionVersion();

	RightCheck2.checkplayer.AddResult(RightCheck2.checkplayer.nNum,RightCheck2.checkplayer.nInstead);
	strcpy( RightCheck2.szUserName, m_szUserName);
	//RightCheck2.CheckPlayerEnterWorldLength = RightCheck2.checkplayer.CaluLength();	
	//RightCheck2.CaluLength();

	int nRet = GettheNetworkInput().SendMsg( (char*)&RightCheck2, RightCheck2.GetLength() );

	if (nRet == -1)
	{
		s_CUI_ID_FRAME_LOGIN.SetLoginInfo(theXmlString.GetString(eText_Disconnect) );
		g_bConnectSuccFlag = false;
		return g_bConnectSuccFlag;
	}
	//
	Sleep(100);
	//发送登陆消息
	//MsgLogin msg;
	MsgLogin2 msg;
	strcpy( msg.szUserName, m_szUserName);
	strcpy( msg.szPassword, m_szPassword);

	msg.isSoftKeboardChar = isSoftKeyboardChar;
	msg.IsForceLogin = isForced;

	strcpy(msg.szGameVersion,ApplicationConfig::Instance().GetFullVersion());
	msg.dwGameVerSion[0] = ApplicationConfig::Instance().GetMajorVersion();
	msg.dwGameVerSion[1] = ApplicationConfig::Instance().GetMinorVersion();
	msg.dwGameVerSion[2] = ApplicationConfig::Instance().GetBuildVersion();
	msg.dwGameVerSion[3] = ApplicationConfig::Instance().GetRevisionVersion();

	if (theHeroGame.m_loginCheckKey)
	{
		strncpy(msg.checkkey,theHeroGame.m_loginCheckKey,sizeof(msg.checkkey)-1);
	}

	msg.checkplayer.nNum = rand()%(MsgCheckPlayerEnterWorld::e_iMaxNum);
	if (msg.checkplayer.nNum < 2)
	{
		msg.checkplayer.nNum  = 2;
		msg.checkplayer.nInstead = 2;
	}

	msg.checkplayer.nInstead = rand()%msg.checkplayer.nNum;

	if (msg.checkplayer.nInstead < 2)
	{
		msg.checkplayer.nInstead = 2;
	}

	msg.checkplayer.AddResult(msg.checkplayer.nNum,msg.checkplayer.nInstead);

	nRet = GettheNetworkInput().SendMsg( (char*)&msg,msg.GetLength() );

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Send    MsgLogin2");

	if (nRet == -1)
	{
		s_CUI_ID_FRAME_LOGIN.SetLoginInfo(theXmlString.GetString(eText_Disconnect) );
		g_bConnectSuccFlag = false;
		return g_bConnectSuccFlag;
	}

	s_CUI_ID_FRAME_LOGIN.ProcessLog();

	//s_CUI_ID_FRAME_LOGIN.SetLoginInfo(theXmlString.GetString(eText_WaitingRequest) );

	return TRUE;
	unguard;
}
#endif

#ifndef _RELEASE_CLIENT
bool bOpenDebugInfo = true;
#else
bool bOpenDebugInfo = false;
#endif //_DEBUG
extern int g_iLoadModelPerFrame;
#include "ui\ShowScriptGif.h"
extern int g_iShowScriptGifCountDown;

#ifdef _DEBUG
#include "StoryTip.h"
#endif


//lyh++ 全局命令开关钥匙指令 
//默认情况不能手动掉程序命令
bool G_OpenCommand = false;
BOOL DebugCommand( const char* pszCommand )
{
	guardfunc;

	if( pszCommand == NULL )
		return FALSE;

	if( pszCommand[0] == 0 )
		return FALSE;

	WordParser words;
	if( words.Parse( pszCommand ) == 0 )
		return FALSE;

	if( theApp->GetPlayerMgr() && theApp->GetPlayerMgr()->ProcessCommand(pszCommand) )
	{
		return TRUE;
	}
	CPlayer* pMe = theApp->GetPlayerMgr()->GetMe();
	if( !pMe )
		return FALSE;

#ifdef _RELEASE_CLIENT
	//if( words.Compare( 0, "debug" ))
	//{
	//bOpenDebugInfo = (bool)atoi( words.GetWord( 1 ) );
	//if(words.GetWordCount() == 1)
	//	bOpenDebugInfo = true;
	/*	}
	else*/ if( words.Compare( 0, "freecamera" ) )
	{
		//return FALSE;
		if( words.GetWordCount() != 1 && atoi( words.GetWord( 1 ) ) == 0 )
		{
			getwsCamera()->SetFreeCameraMode( FALSE );
			g_bRenderRole = TRUE;
			getwsCamera()->SetLookatPtHeight( 90.0f );
		}
		else
		{
			getwsCamera()->SetFreeCameraMode( TRUE );
			getwsCamera()->SetFreeCameraStartPos( theApp->GetPlayerMgr()->GetMe()->GetPos() );
			g_bRenderRole = FALSE;
		}
	}
#endif // _RELEASE_CLIENT

	//lyh++调试信息开关
	if( words.Compare( 0, "whatishappening" ))
	{
	
		  G_OpenCommand = true;
		  return TRUE;
		
	}

	if( words.Compare( 0, "setkeepfps" ) && G_OpenCommand)
	{
		if(words.GetWordCount() > 1)
		{
			int nFPS = atoi( words.GetWord( 1 ) );
			GetMe3dConfig()->SetKeepFPS(nFPS);
		}
	}


	//if( !bOpenDebugInfo )
	//	return false;

	if( words.Compare(0, "showscriptgif") && G_OpenCommand)
	{
		if(words.GetWordCount() > 1 )
		{
			int nCD = atoi( words.GetWord( 1 ) );
			if( nCD > 0 )
				g_iShowScriptGifCountDown = nCD;
		}
		s_CUI_ID_FRAME_ShowScriptGif.SetVisable(true);
	}
	else
		if( words.Compare(0, "crash"))
		{
			int *i=0;
			*i=1;
			return TRUE;
		}
		else if( words.Compare(0,"mail" ) && G_OpenCommand && false)
		{
			theHeroGame.SendCrashEmail( "test" );
		}
		else if( words.Compare( 0, "ltstate" ))
		{
			if( !s_CUI_ID_FRAME_LotteryGame.IsVisable() )
				s_CUI_ID_FRAME_LotteryGame.SetVisable( true );
			int nState = atoi( words.GetWord( 1 ) );
			nState = min( nState, LOTTERYSTATUS_COUNT - 1 );
			nState = max( LOTTERYSTATUS_DEFAULT, nState );
			RollSystemStatusMan<RST_Lottery>::Instance()->ChangeState( nState );
		}
		else if( words.Compare( 0, "lttarget" ) )
		{
			int nTargetAnim = atoi( words.GetWord( 1 ) );

			RollSystemStatusMan<RST_Lottery>::Instance()->GetCurrentState()->SetTargetDiceAnimState( nTargetAnim );
		}
		else if( words.Compare( 0, "lgstate" ) )
		{
			int nState = atoi( words.GetWord( 1 ) );
			nState = min( nState, LGS_COUNT - 1 );
			nState = max( LGS_DEFAULT, nState );
			RollSystemStatusMan<RST_LuckyGame>::Instance()->ChangeState( nState );
		}
		else if( words.Compare( 0, "lgtarget" ) )
		{
			int nTargetAnim = atoi( words.GetWord( 1 ) );

			RollSystemStatusMan<RST_LuckyGame>::Instance()->GetCurrentState()->SetTargetDiceAnimState( nTargetAnim );
		}
		else if( words.Compare( 0, "sleep" ) && G_OpenCommand)
		{
			short nSpeed = atoi( words.GetWord( 1 ) );
			theHeroGame.SetSlowCPU(nSpeed);
		}
		else if( words.Compare( 0, "memory" ) && G_OpenCommand)
		{
			LOG_MESSAGE( MEMORY_LOG, LOG_PRIORITY_INFO, "[堆分配内存占用输出起始]");
			unsigned int nAllMemory = 0;
			for (map<const char*, ALLOCMEMORYINFO>::iterator itr = GetAllocInfo().begin(); itr != GetAllocInfo().end(); itr++)
			{
				nAllMemory += itr->second.nAllUseMemory;
				LOG_MESSAGE( MEMORY_LOG, LOG_PRIORITY_INFO, "%-60s 占用内存 [%-15d] 字节, 目前未释放共分配 [%-10d] 次, 历史申请[%-10d]次", itr->first!=NULL?itr->first:"未定义用途", itr->second.nAllUseMemory, itr->second.nExistCount, itr->second.nAllocCount );
			}


			LOG_MESSAGE( MEMORY_LOG, LOG_PRIORITY_INFO, "全部分配内存[%d]Byte [%d]MByte", nAllMemory, nAllMemory/(1024*1024) );

			LOG_MESSAGE( MEMORY_LOG, LOG_PRIORITY_INFO, "[堆分配内存占用输出终止]\n" );
		}
		else if( words.Compare( 0, "mousespeed") && G_OpenCommand)
		{
			short nSpeed = atoi( words.GetWord( 1 ) );
			SystemParametersInfo( SPI_SETMOUSESPEED, 0, (PVOID)nSpeed, SPIF_SENDCHANGE );
		}

		if( words.Compare( 0, "locktime" ))
		{
			SwGlobal::GetRender()->SetLockMaxTime( atoi( words.GetWord(1)));
		}
		if( words.Compare( 0, "reloadterrainshader" ) && G_OpenCommand)
		{
			IRenderer* r = GetEngine()->GetRenderer();
			char path[MAX_PATH] = {0};
			MeSprintf_s( path, MAX_PATH, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\TerrainBlender.fxo" );
			graphics::ShaderEffect* pLOD2_TerrainShader = MeNew graphics::ShaderEffect( "TerrainBlender",
				(LPDIRECT3DDEVICE9)r->GetRealDevice(), path );
			graphics::ShaderManager::instance()->addShader( pLOD2_TerrainShader );
			r->EnableUseShader(true);
			static graphics::Material terrainMeterial;
			terrainMeterial.setShader("TerrainBlender");
			r->SetTerrainMaterial(&terrainMeterial);
		}
		if( words.Compare( 0, "amblight") && G_OpenCommand)
		{
			float color_r = atof( words.GetWord(1) ) / 255.f;
			float color_g = atof( words.GetWord(2) ) / 255.f;
			float color_b = atof( words.GetWord(3) ) / 255.f;
			NiColor Color = NiColor( color_r, color_g, color_b );
			Color.Clamp();
			SwRender* pRender = SwGlobal::GetRender();
			pRender->SetLightAmbientColor( Color );
			return TRUE;
		}
		if( words.Compare( 0, "difflight") && G_OpenCommand)
		{
			float color_r = atof( words.GetWord(1) ) / 255.f;
			float color_g = atof( words.GetWord(2) ) / 255.f;
			float color_b = atof( words.GetWord(3) ) / 255.f;
			NiColor Color = NiColor( color_r, color_g, color_b );
			Color.Clamp();
			SwRender* pRender = SwGlobal::GetRender();
			pRender->SetLightDiffuseColor( Color );
			return TRUE;
		}
		if( words.Compare( 0, "fog") && G_OpenCommand)
		{
			float fognear = atof( words.GetWord(1) );
			float fogfar  = atof( words.GetWord(2) );
			SwRender* pRender = SwGlobal::GetRender();
			pRender->SetFogDepthByCommand( fognear, fogfar );
			return TRUE;
		}
		if( words.Compare( 0, "fogcolor" )&& G_OpenCommand)
		{
			float color_r = atof( words.GetWord(1) ) / 255.f;
			float color_g = atof( words.GetWord(2) ) / 255.f;
			float color_b = atof( words.GetWord(3) ) / 255.f;
			NiColor Color = NiColor( color_r, color_g, color_b );
			Color.Clamp();
			SwRender* pRender = SwGlobal::GetRender();
			pRender->SetFogColor( Color );

			return TRUE;
		}
//		else if( words.Compare( 0, "lockcamera" ) )
//		{
//// 			int nLock = atoi( words.GetWord( 1 ) );
//// 			if(words.GetWordCount() == 1)
//// 				nLock = 1;
//// 			g_bUpdateCamera = ( nLock == 1 ) ? false : true;
//		}
		else if( words.Compare( 0 , "culldis" ) )
		{
			int nDistance = atoi( words.GetWord( 1 ) );
			GetMe3dConfig()->SetCullDistance( nDistance );
		}
		else if( words.Compare( 0,"showgrass" ) )
		{
			int iCheck = atoi( words.GetWord( 1 ) );
			GetMe3dConfig()->SetRenderGrass( iCheck );
			if(words.GetWordCount() == 1)
				iCheck = 1;
			if( iCheck == 1 )
				SwGlobal::GetRender()->SetRenderDoodad(true);
			else
				SwGlobal::GetRender()->SetRenderDoodad(false);
		}
		else  if( words.Compare( 0,"fov" ) )
		{
			//0 - 30
			INT iCheck = atoi( words.GetWord( 1 ) );
			if( iCheck == 0 )
				iCheck = 1;
			g_fCamerFOV = D3DX_PI/180*( 45 + iCheck );
		}
		else  if( words.Compare( 0,"camerashake" ) && G_OpenCommand)
		{
			D3DXVECTOR3 vRolePos = theHeroGame.GetPlayerMgr()->GetMe()->GetPos();
			g_CameraStuntManager.StartRandShake(atof(words.GetWord(1)), atof(words.GetWord(2)), atoi(words.GetWord(3)),atoi(words.GetWord(4)),getwsCamera()->GetCurCameraZoom() );
		}
		else if( words.Compare( 0, "findpath") && G_OpenCommand && false)
		{
			float x = atof( words.GetWord(1) ) ;
			float y = atof( words.GetWord(2) );
			if( theApp->GetPlayerMgr()->GetMe() )
				theApp->GetPlayerMgr()->MoveRoleTo(x,y,true,false);
		}
		else if( words.Compare( 0, "renderparticlelevel") && G_OpenCommand)
		{
			g_nRenderParticleEmittersLevel = atoi( words.GetWord(1) ) ;
		}
		else if( words.Compare( 0, "finstatuscolor" ) )
		{
			D3DXVECTOR3 vColor;
			vColor.x = atof( words.GetWord( 1 ) );
			vColor.y = atof( words.GetWord( 2 ) );
			vColor.z = atof( words.GetWord( 3 ) );

			if( theApp->GetPlayerMgr()->GetMe() )
				theApp->GetPlayerMgr()->GetMe()->SetFinStatusColor( vColor );
		}
        else if( words.Compare( 0, "showuitip" ) )
        {
            int nTipId = atoi( words.GetWord( 1 ) );
            CIntroductionManager::Instance()->ShowTip( nTipId );
        }
		else if( words.Compare( 0, "freecamera" ) && G_OpenCommand)
		{
			//return FALSE;
			if( words.GetWordCount() != 1 && atoi( words.GetWord( 1 ) ) == 0 )
			{
				getwsCamera()->SetFreeCameraMode( FALSE );
				g_bRenderRole = TRUE;
				getwsCamera()->SetLookatPtHeight( 90.0f );
			}
			else
			{
				getwsCamera()->SetFreeCameraMode( TRUE );
				getwsCamera()->SetFreeCameraStartPos( theApp->GetPlayerMgr()->GetMe()->GetPos() );
				g_bRenderRole = FALSE;
			}
		}
        // 测试服务器需要的一些命令(不可以删)
        else if( words.Compare( 0, "ShowTR" ) && G_OpenCommand )
        {
            int nShow = atoi( words.GetWord( 1 ) );
            CPlayer::SetServerTerrainRectShow( nShow != 0 );
        }
        else if( words.Compare( 0, "ShowTH" ) && G_OpenCommand)
        {
            int nShow = atoi( words.GetWord( 1 ) );
            CPlayer::SetHeightMapRectShow( nShow != 0 );
        }
        else if( words.Compare( 0, "ShowMyCircle" ) && G_OpenCommand)
        {
            int nShow = atoi( words.GetWord( 1 ) );
            if( nShow == 0 )
            {
                CPlayer::SetMyCircleShow( false, 0.0f );
            }
            else
            {
                float fR = atof( words.GetWord( 2 ) );
                CPlayer::SetMyCircleShow( true, fR );
            }
        }
        else if( words.Compare( 0, "ShowMouseCircle" ) && G_OpenCommand)
        {
            int nShow = atoi( words.GetWord( 1 ) );
            if( nShow == 0 )
            {
                CPlayer::SetMouseCircleShow( false, 0.0f );
            }
            else
            {
                float fR = atof( words.GetWord( 2 ) );
                CPlayer::SetMouseCircleShow( true, fR );
            }
        }
        else if( words.Compare( 0, "TestServerConnect" ) && G_OpenCommand)
        {
            if( !GettheNetworkInput().IsConnectted() )
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldList_Info, "已与服务器断开连接！" );
            }
            else
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldList_Info, "与服务器连接正常！" );
            }
        }

        // 测试换模型
        else if( words.Compare( 0, "ChangeMex" ) && G_OpenCommand)
        {
            int iModelId = atoi( words.GetWord( 1 ) );
            CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
            if( pPlayerMgr )
            {
                CPlayer* pPlayer = pPlayerMgr->GetMe();
                if( pPlayer )
                {
                    CPlayerAnim* pPlayerAnim = pPlayer->GetAnim();
                    if( pPlayerAnim )
                        pPlayerAnim->TryChangeModel( iModelId, "default" );
                }
            }
        }
        // 测试屏幕文字
        else if( words.Compare( 0, "ScreenShow" ) && G_OpenCommand)
        {
            int nType = atoi( words.GetWord( 1 ) );
            const char* pChar = words.GetWord( 2 );
            CScreenInfoManager::Instance()->ShowInfoByType( nType, std::string( pChar ) );
        }
        else if( words.Compare( 0,"localflymap" ) && G_OpenCommand)
        {
            //return TRUE;
            int	noldMapSize  = 128;
            int iMapID = -1;
            if( words.IsNumber( 1 ) )
            {
                iMapID = atoi( words.GetWord( 1 ) );
            }
            else
            {
                CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromTileName(words.GetWord(1));
                if( pTile )
                {
                    iMapID = pTile->GetMapId();
                }
                else 
                    return FALSE;
            }

			int nMapX = atoi(words.GetWord(2));
			int nMapY = atoi(words.GetWord(3));

			s_CUI_ID_FRAME_LoadMap.SetFloatX(nMapX);
			s_CUI_ID_FRAME_LoadMap.SetFloatY(nMapY);
			s_CUI_ID_FRAME_LoadMap.SetFloatZ(WORLD_HEIGHT);
			s_CUI_ID_FRAME_LoadMap.LoadMap(iMapID,nMapX,nMapY,1,0);
			s_CUI_ID_FRAME_LoadMap.SetVisable(true);


//             if( words.GetWordCount() == 4 )
//             {
//                 int x = atoi( words.GetWord( 2 ) )*noldMapSize;
//                 int y = atoi( words.GetWord( 3 ) )*noldMapSize;
//                 float fx = x*noldMapSize*GetMe3dConfig()->m_fMdlSpaceScale;
//                 float fy = y*noldMapSize*GetMe3dConfig()->m_fMdlSpaceScale;
// 
//                 //	theHeroGame.LoadLand( iMapID, x, y );
// 
//                 s_CUI_ID_FRAME_LoadMap.SetFloatX(fx);
//                 s_CUI_ID_FRAME_LoadMap.SetFloatY(fy);
//                 s_CUI_ID_FRAME_LoadMap.LoadMap( iMapID,
//                     x, y,
//                     1,0);
// 
//                 theHeroGame.GetPlayerMgr()->GetMe()->JumpToMapPos( fx, fy, 0.0f);
// 
// 
//             }
//             else if( words.GetWordCount() == 6 )
//             {
//                 int x = atoi( words.GetWord( 2 ) )*noldMapSize+atoi( words.GetWord( 4 ) );
//                 int y = atoi( words.GetWord( 3 ) )*noldMapSize+atoi( words.GetWord( 5 ) );
//                 float fx = x*noldMapSize*GetMe3dConfig()->m_fMdlSpaceScale;
//                 float fy = y*noldMapSize*GetMe3dConfig()->m_fMdlSpaceScale;
// 
// 
//                 s_CUI_ID_FRAME_LoadMap.SetFloatX(fx);
//                 s_CUI_ID_FRAME_LoadMap.SetFloatY(fy);
//                 s_CUI_ID_FRAME_LoadMap.LoadMap( iMapID,
//                     x, y,
//                     1,0);		
// 
//                 theHeroGame.GetPlayerMgr()->GetMe()->JumpToMapPos( fx, fy, 0.0f);
//             }
        }
		else if( words.Compare( 0, "localmount" ) && G_OpenCommand)
		{
			if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
			{
				if(words.GetWordCount() > 1)
				{
					int nMountId = atoi( words.GetWord(1) );
					if( nMountId >= 0 )
					{
						theHeroGame.GetPlayerMgr()->GetMe()->MountMonster(nMountId);
						if( theHeroGame.GetPlayerMgr()->GetMe()->IsMounting() ||
							theHeroGame.GetPlayerMgr()->GetMe()->IsMountInThread() )
							theHeroGame.GetPlayerMgr()->GetMe()->SetMoveRate(6.f);
					}
					else
					{
						theHeroGame.GetPlayerMgr()->GetMe()->DisMount();
						theHeroGame.GetPlayerMgr()->GetMe()->SetMoveRate(4.f);
					}
				}
			}
		}
        else if( words.Compare( 0,"playloweranim" ) && G_OpenCommand)
        {
            if( words.GetWordCount() == 6 )
            {
                if( theApp->GetPlayerMgr()->GetMe() && theApp->GetPlayerMgr()->GetMe()->GetAnim() )
                    theApp->GetPlayerMgr()->GetMe()->GetAnim()->PlayLowerAnim( words.GetWord(1),
                    MexAnimCtrl::eNormalPlay,
                    atoi( words.GetWord( 2 ) ),
                    1,
                    MexAnimCtrl::eMaxTimeout,
                    atoi( words.GetWord( 3 ) ),
                    words.GetWord(4),
                    MexAnimCtrl::eNormalPlay,
                    atoi( words.GetWord( 5 ) ) );
            }
        }
        else if( words.Compare( 0,"playupperanim" ) && G_OpenCommand)
        {
            if( words.GetWordCount() == 4 )
            {
                if( theApp->GetPlayerMgr()->GetMe() && theApp->GetPlayerMgr()->GetMe()->GetAnim() )
                    theApp->GetPlayerMgr()->GetMe()->GetAnim()->PlayUpperAnim( words.GetWord(1),
                    MexAnimCtrl::eNormalPlay,
                    atoi( words.GetWord( 2 ) ),
                    1,
                    MexAnimCtrl::eMaxTimeout,
                    atoi( words.GetWord( 3 ) ));
            }
        }
        else if( words.Compare( 0, "changemodel" ) && G_OpenCommand)
        {
            if( words.GetWordCount() == 3 )
            {
                if( atoi( words.GetWord( 1 ) ) == 0 )
                {
                    theApp->GetPlayerMgr()->GetMe()->DisMorph();
                }
                else
                {
					theApp->GetPlayerMgr()->GetMe()->MorphMonster( atoi( words.GetWord( 2 ) ) );
				}
			}
		}	

		else if(  words.Compare( 0, "jumpspeed" ) && G_OpenCommand && false)
		{
			theApp->GetPlayerMgr()->GetMe()->SetStartJumpingSpeed( atof( words.GetWord( 1 ) ) );
		}
		else if( words.Compare( 0, "showcollision" ) && G_OpenCommand)
		{
			if( words.GetWordCount() == 2 )
			{
				if( atoi( words.GetWord( 1 ) ) == 0 )
				{
					getwsCamera()->SetShowCollision( FALSE );
				}
				else
				{
					getwsCamera()->SetShowCollision( TRUE );
				}
			}
		}
		else if( words.Compare( 0, "showattackrange" ) && G_OpenCommand)
		{
			if( words.GetWordCount() == 3 )
			{
				if( atoi( words.GetWord( 1 ) ) == 0 )
				{
					g_bShowRoleAttackRange = FALSE;
					g_fAddRoleAttackRange = atof( words.GetWord( 2 ) );
				}
				else
				{
					g_bShowRoleAttackRange = TRUE;
					g_fAddRoleAttackRange = atof( words.GetWord( 2 ) );
				}
			}
		}
		else if( words.Compare( 0, "cameracollision" ) && G_OpenCommand)
		{
			if( words.GetWordCount() == 2 )
			{
				if( atoi( words.GetWord( 1 ) ) == 0 )
				{
					getwsCamera()->SetCameraCollision( FALSE );
				}
				else
				{
					getwsCamera()->SetCameraCollision( TRUE );
				}
			}
		}
		else if( words.Compare( 0, "netlog" ) && G_OpenCommand && false)
		{
			if( words.GetWordCount() == 2 )
			{
				theHeroGame.SetStartCaculateNetStream((bool)atoi( words.GetWord( 1 ) ));
				if( theHeroGame.GetStartCaculateNetStream() ) // start
				{
					g_NetStreamLog.Reset();
					g_NetStreamLog.Start();
				}
				else // end
				{
					g_NetStreamLog.End();
					g_NetStreamLog.Caculate();
				}
			}
		}
		else if( words.Compare( 0, "TestEffect" ) && G_OpenCommand)
		{
			if( !g_bShowIMPanel )
			{
				if( !g_hIMPanel )
				{
					g_hIMPanel = CreateDialog( 
						0, 
						MAKEINTRESOURCE( IDD_DIALOG_TESTEFFECT ), g_hWnd, 
						IMPanelMsgProc );
				}
				ShowWindow( g_hIMPanel, SW_SHOW );
				g_bShowIMPanel = TRUE;
			}
		}
		else if( words.Compare( 0, "setskybox" ) && G_OpenCommand)
		{
			g_bRenderSkyBox = atoi( words.GetWord( 1 ) );
		}
		else if( words.Compare( 0, "invitejoinguild" ) && G_OpenCommand)
		{
			//if( pMe->HasGuild() )
			//{
			//	if( words.GetWord( 1 ) )
			//	{
			//		CPlayer* pPlayer = theApp->GetPlayerMgr()->FindByName( words.GetWord( 1 ) );
			//		if( pPlayer )
			//		{
			//			//MsgGuildMasterInvite invite;
			//			invite.dwGuildId = pMe->GetGuildId();
			//			invite.stCharId = pPlayer->GetID();
			//			GettheNetworkInput().SendMsg( &invite );

			//			return TRUE;
			//		}
			//	}
			//}
		}
		else if( words.Compare( 0, "targetdis" ) && G_OpenCommand)
		{
			int nTargetID = s_CUI_ID_FRAME_Target.GetPlayerID();
			CPlayer* pMe = theApp->GetPlayerMgr()->GetMe();
			CPlayer* pTarget = theApp->GetPlayerMgr()->FindByID( nTargetID );
			if( pMe && pTarget )
			{
				float fDistance = pMe->GetDistToTarget( pTarget->GetPos().x, pTarget->GetPos().y );
				char szDis[MAX_PATH] = {0};
				MeSprintf_s( szDis, MAX_PATH, "%f", fDistance );
				PrintDebugInfo( 0, szDis );
			}
			else
			{
				PrintDebugInfo( 0, "没有目标" );
			}
		}
		else if( words.Compare( 0, "localspeed" ) && G_OpenCommand && false)
		{
			int nSpeed = atoi( words.GetWord( 1 ) );		
			theHeroGame.GetPlayerMgr()->GetMe()->SetMoveRate( (float)nSpeed );
		}
		else if( words.Compare( 0, "changecomeffect" ) && G_OpenCommand)
		{
			CPlayer* pMe = theApp->GetPlayerMgr()->GetMe();
			// com id
			int nComId = atoi( words.GetWord( 1 ) );
			// bone id
			int nBone = atoi( words.GetWord( 2 ) ) ;
			// load effect mex
			IMex* pEffectMex = GetEngine()->CreateMex();
			pEffectMex->LoadFromFile( "f:\\hero\\program\\trunk\\bin\\client\\data\\sceneobject\\common\\huo\\huopen001.mex", 0 );
			pMe->GetAnim()->AttachEffectToComponent( nComId, nBone, pEffectMex );
		}
		else if( words.Compare( 0, "useske" ) && G_OpenCommand)
		{
			int nEnable = atoi( words.GetWord( 1 ) );
			graphics::ShaderManager::instance()->enableSkeletonShader( (bool)nEnable );
			SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_SKELETON, nEnable );			
		}
		else if( words.Compare( 0, "info" ) && G_OpenCommand)
		{
			int nShow = atoi( words.GetWord( 1 ) );
			if(words.GetWordCount() == 1)
				nShow = 1;
			g_bShowFps = nShow;
			g_bDebugPos = nShow;
			if(g_bShowFps)
				PrintDebugInfo( 0, "显示游戏信息开启" );
			else
				PrintDebugInfo( 0, "显示游戏信息关闭" ); 
		}else if ( words.Compare(0, "hdr") && G_OpenCommand) 
		{
			int nShow = atoi( words.GetWord( 1 ) );
			PostProcessManager::instance().enableProcess("Hdr",nShow);
		}
		else if( words.Compare( 0, "weathereffect") && G_OpenCommand)
		{
			int nShow = atoi( words.GetWord( 1 ) );
			if(words.GetWordCount() == 1)
				nShow = 1;
			GetMe3dConfig()->SetPlayMapEffect((BOOL)nShow);
		}
		//else if( words.Compare( 0, "lockfps") && G_OpenCommand)	// 锁帧
		//{
		//	int nLock = atoi( words.GetWord( 1 ) );
		//	if(words.GetWordCount() == 1)
		//		nLock = 1;
		//	GetMe3dConfig()->SetLockFPS((BOOL)nLock);
		//}
		else if( words.Compare( 0, "Clear") && G_OpenCommand)	// 锁帧
		{

			theHeroGame.m_PlayerMaxCost = 0; //角色最高耗时
			theHeroGame.m_SceneUpdateMaxCost= 0; //场景更新最高耗时
			theHeroGame.m_SceneRenderMaxCost= 0; 
			theHeroGame.m_TerrainRenderMaxCost= 0;
			theHeroGame.m_DoodadRenderMaxCost= 0; //植被最高耗时
			theHeroGame.m_LiquidRenderMaxCost= 0; //流体最高耗时
			theHeroGame.m_EffectRenderMaxCost= 0; //特效最高耗时
			theHeroGame.m_UIRenderMaxCost= 0;     //ui最高耗时
			theHeroGame.m_PostProcessMaxCost= 0; 

		}
		else if( words.Compare( 0, "showobj" ) && G_OpenCommand)
		{
//#ifndef _DEBUG
//			return TRUE;
//#endif
			char szTemp[MAX_PATH] = {0};
			int nParam = atoi( words.GetWord( 1 ) );

			GetMe3dConfig()->SetRenderObjs( nParam );

			bool bRender = 	GetMe3dConfig()->IsRenderObjs();
			sprintf ( szTemp, " 显示Scence %s", bRender?"是":"否" );
			PrintDebugInfo( 0, szTemp );
		}
		else if( words.Compare( 0, "terrainlayer" ) && G_OpenCommand)
		{
			char szTemp[MAX_PATH] = {0};
			int nParam = atoi( words.GetWord( 1 ) );
			GetMe3dConfig()->SetTerrainRenderLayer( (short)nParam );
		}
		else if( words.Compare( 0, "showworld" ) && G_OpenCommand)
		{
			char szTemp[MAX_PATH] = {0};
			int nParam = atoi( words.GetWord( 1 ) );
			GetMe3dConfig()->SetRenderWorld( nParam );
		}
		else if( words.Compare( 0, "firstcam" ) && G_OpenCommand)
		{
			g_bFirstSightCamera = TRUE;
		}
		else if( words.Compare( 0, "topcam" ) )
		{
			g_bFirstSightCamera = FALSE;
		}
		else if( words.Compare( 0, "showwalk" ) && G_OpenCommand)
		{
			int nParam = atoi( words.GetWord( 1 ) );
			GetMe3dConfig()->SetShowWalk( nParam );
			PrintDebugInfo( 0, "showwalk" );
		}
		else if(	words.Compare( 0, "guild" ) &&
			words.Compare( 1, "declare" ) && G_OpenCommand)
		{
			////MsgGuildMasterDeclare msgDeclare;
			//strcpy( msgDeclare.szDeclare, words.GetWord( 2 ) );
			//GettheNetworkInput().SendMsg( &msgDeclare );

		}	
// 		else if( words.Compare( 0, "RandomVS" ) )
// 		{
// 			pMe->RandomVisual();
// 		}
		else if( words.Compare( 0, "addplayers" ) && G_OpenCommand)
		{
					//theHeroGame.GetPlayerMgr()->ResumeLastRenderFlag();
			static int base = 10000;
			int nNumAdd = atoi( words.GetWord( 1 ) );
			for( int nAdd = 0; nAdd < nNumAdd; nAdd++ )
			{
				CPlayer* pPlayer= theApp->GetPlayerMgr()->AddPlayer( base++, Object_Player );
				pPlayer->AutoCS(0,1);
				float x, y, z;
				pMe->GetPos( &x, &y, &z  );
				float fSize = atoi( words.GetWord(2) )*MAPTILESIZE;

				pPlayer->SetPos( 
					x-fSize/2+Random( fSize ), 
					y-fSize/2+Random( fSize ), z );

			CPlayerAnim* pAnim = MeNew CPlayerAnim;
			pPlayer->SetAnim( pAnim );
			//pPlayer->GetAnim()->SetChangeAllEquipComplete( FALSE );
				//CPlayerAnim* pAnim = MeNew CPlayerAnim;
				//pPlayer->SetAnim( pAnim );
				//pPlayer->GetAnim()->SetChangeAllEquipComplete( FALSE );

				if( rand()%2 == 0 )
					pPlayer->SetSex( 0 );
				else 
					pPlayer->SetSex( 1 );

			//}
			pPlayer->SetProfession( EArmType_Assassin );
			//pPlayer->SetSex( 1 );
			if( rand()%2 == 0 )
				pPlayer->SetSex( 0 );
			else 
				pPlayer->SetSex( 1 );
				//}
				pPlayer->SetProfession( EArmType_Assassin );
				//pPlayer->SetSex( 1 );
				if( rand()%2 == 0 )
					pPlayer->SetSex( 0 );
				else 
					pPlayer->SetSex( 1 );

			//pPlayer->SetSex( 1 );
			//pPlayer->SetProfession( EArmType_Warrior );
			pPlayer->SetBodySize( 1.0f );
			
			pAnim->SetPlayer( pPlayer );
			if( g_bMultiThreadLoadingMex )
			{
				//if( !MeLoopThreadMan::Instance()->FindPointer( pAnim ) )
				//pPlayer->SetSex( 1 );
				//pPlayer->SetProfession( EArmType_Warrior );
				pPlayer->SetBodySize( 1.0f );

				//pAnim->SetPlayer( pPlayer );
				if( g_bMultiThreadLoadingMex )


				{
					MeLoopThreadMan::Instance()->RegisterPointer( pAnim );				
					//if( !MeLoopThreadMan::Instance()->FindPointer( pAnim ) )
					{
						//MeLoopThreadMan::Instance()->RegisterPointer( pAnim );				
					}
				}
			}

// 				pPlayer->RandomVisual();
				// 				pPlayer->RandomVisual();
				pPlayer->SetDir( Random( D3DX_PI*2 ) );

				pPlayer->MountMonster(12);

				pPlayer->MountMonster(853);


				if( pPlayer->GetAnim() )
				{
					pPlayer->GetAnim()->InitUpperBodyAndLowerBody();
					pPlayer->SwitchIdleAnim();
				}
			}
		}
		else if(words.Compare(0,"KillMonsterTime")&& G_OpenCommand)
		{
			int nNumAdd = atoi( words.GetWord( 1 ) );
		}
		else if( words.Compare( 0, "bbox" ) && G_OpenCommand)
		{
			int nShow = atoi( words.GetWord( 1 ) );
			if(words.GetWordCount() == 1)
				nShow = 1;
			g_bShowModelBBox = nShow;
			GetMe3dConfig()->SetRenderBBox( g_bShowModelBBox );
		}			
		else if( words.Compare( 0, "setminimapsize" ) && G_OpenCommand)
		{
			g_nMiniMapSight = atoi( words.GetWord( 1 ) );
			int nWinSize  = atoi( words.GetWord( 2 ) );;
			if( nWinSize > 0 )
				g_nMiniMapWindowSize = nWinSize;
			PrintDebugInfo( 0, "设置小地图视野(%ld),渲染窗口大小(%ld,%ld)", 
				g_nMiniMapSight,
				g_nMiniMapWindowSize,
				g_nMiniMapWindowSize );
		}
		else if( words.Compare( 0, "minimapmark" ) && G_OpenCommand)
		{
			CRegionMap::Mark mark;

			CWorldTile* ptile = CURRENTTILE;

			mark.x = ptile->GetWidth()*Random();
			mark.y = ptile->GetDepth()*Random();
			mark.dwBornTime = HQ_TimeGetTime();
			mark.dwLife = 2000;

			if( words.GetWordCount() > 1 )
				mark.x = atoi( words.GetWord(1) );
			if( words.GetWordCount() > 2 )
				mark.y = atoi( words.GetWord(2) );
			if( words.GetWordCount() > 3 )
				mark.dwLife = atoi( words.GetWord(3 ) );

			mark.bFlicker = TRUE;

			GetRegionMap()->AddMark( &mark );
		}
		else if( words.Compare( 0, "minimapfind" ) && G_OpenCommand)
		{
			int nNpcID = atoi(words.GetWord( 1 ));
			GetRegionMap()->MarkNpcPosByID( nNpcID );
		}
		else if( words.Compare( 0, "npclist"))
		{
			s_CUI_ID_FRAME_AllNpcList.SetVisable( true );
		}
		else if( words.Compare( 0, "playerskinlist" ) && G_OpenCommand)
		{
			GameObjectId gcPlayerServerID = theApp->GetPlayerMgr()->GetMouseTargetPlayerSeverID();
			CPlayer* pPlayer = theApp->GetPlayerMgr()->FindByID( gcPlayerServerID );
			char szBuf[256];
			if( pPlayer && pPlayer->GetAnim() )
			{
				MexCfgAvatarSettings* pSettings = &pPlayer->GetAnim()->GetMexCfg()->m_AvatarSettings;
				for( int i = 0; i < pSettings->m_vectorSetting.size(); i++ )
				{
					MexCfgAvatarSetting* s = pSettings->m_vectorSetting[i];

					MeSprintf_s( szBuf, 256, "skin:%s", s->m_spName.GetString() );
					s_CUI_ChatInfoBox.AddInfo( szBuf, 0xffff0000);				
				}
			}
		}
		else if( words.Compare( 0, "changeplayerskin" ) && G_OpenCommand)
		{
			GameObjectId gcPlayerServerID = theApp->GetPlayerMgr()->GetMouseTargetPlayerSeverID();
			CPlayer* pPlayer = theApp->GetPlayerMgr()->FindByID( gcPlayerServerID );
			if(  pPlayer && pPlayer->GetAnim() )
			{
				pPlayer->GetAnim()->ChangeAvatarSetting( words.GetWord(1));
			}
		}
		else if( words.Compare( 0, "changeskybox" ) && G_OpenCommand)
		{
			GetSTSkyBox()->GetSkybox()->ChangeAvatarSetting( words.GetWord(1) );
		}
		else if( words.Compare( 0, "wireframe" ) && G_OpenCommand)
		{
			if( 			words.Compare( 1, "on" ))
			{
				SwGlobal::GetRender()->SetWireFrame(true);
			}
			else if( words.Compare( 1, "off" ) )
			{
				SwGlobal::GetRender()->SetWireFrame(false);
				GetMe3dConfig()->m_bAlwayseWireFrameRendering = FALSE;
			}
			else if( words.Compare( 1, "other" ) )
			{
				GetMe3dConfig()->m_bAlwayseWireFrameRendering = TRUE;
			}
		}
		else if( words.Compare( 0, "showflytext" ) && G_OpenCommand)
		{
			theApp->GetPlayerMgr()->GetMe()->OnShowFlyText( atoi(words.GetWord(1)), atoi(words.GetWord(2)), atoi(words.GetWord(3)), atoi(words.GetWord(4)),false );
		}
		else if(words.Compare(0, "ReloadText")&& G_OpenCommand)
		{
			if(g_pFlyTextEffect)
				g_pFlyTextEffect->InitConfig();
		}
		else if( words.Compare( 0, "showflypic" ) && G_OpenCommand)
		{
			theApp->GetPlayerMgr()->GetMe()->OnShowFlyPic( atoi(words.GetWord(1)) );
		}
		else if( words.Compare( 0, "camerasmoothparam" ) && G_OpenCommand)
		{
			getwsCamera()->SetCameraSmoothParameter( atof(words.GetWord(1)) );
		}
		else if( words.Compare( 0, "setautocamera" ) && G_OpenCommand)
		{
			getwsCamera()->SetAutoCamera(atoi(words.GetWord(1)));
		}
		else if( words.Compare( 0, "stoplogmovepath" ) && G_OpenCommand)
		{
			CPlayer* pMe = theApp->GetPlayerMgr()->GetMe();
			if( pMe )
				pMe->StopLoggingMovePath();
		}
		else if( words.Compare( 0, "startlogmovepath" ) && G_OpenCommand)
		{
			CPlayer* pMe = theApp->GetPlayerMgr()->GetMe();
			if( pMe )
				pMe->StartLoggingMovePath();
		}
		else if( words.Compare( 0, "casteffect" ) && G_OpenCommand)
		{
			GetEffectMgr()->DestroyCache();
			CPlayer* pMe = theApp->GetPlayerMgr()->GetMe();

			int nPlayerID = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
			CPlayer* pTarget = theHeroGame.GetPlayerMgr()->FindByID(nPlayerID);
			if( pTarget )
			{
				//PlayEffect( (char*)words.GetWord(1), pTarget );
				PlayEffect( (char*)words.GetWord(1), pMe, 0.8f, 4000, pTarget );
			}
			else
			{
				PlayEffect( (char*)words.GetWord(1), pMe );
			}

			pMe = NULL;
			pTarget = NULL;
		}
		else if( words.Compare( 0, "lighteffect" ) && G_OpenCommand)
		{
			CPlayer* pMe = theApp->GetPlayerMgr()->GetMe();
			pMe->GetCharEffectContainer()->OpenStateLight( 10000, 0,0,1 );
		}
		else if( words.Compare( 0, "showfog" ) && G_OpenCommand)
		{
			GetMe3dConfig()->SetShowFog( !GetMe3dConfig()->IsShowFog() );
			IRenderer* Render = GetEngine()->GetRenderer();//->GetDevice();
			Render->SetRenderState( D3DRS_FOGENABLE, !GetMe3dConfig()->IsShowFog() );
		}
		else if( words.Compare( 0, "showplayer" ) && G_OpenCommand)
		{
			g_bShowPlayer = atoi( words.GetWord( 1 ) );
		}
		else if ( words.Compare( 0, "queryvar" )  && G_OpenCommand )
		{
			MsgQueryScriptVar msg;
			strncpy( msg.szVar, words.GetWord(1), MsgQueryScriptVar::STRING_LEGTH );
			GettheNetworkInput().SendMsg( &msg );
		}
		else if( words.Compare( 0, "setfarplane" ) && G_OpenCommand)
		{
			float fogFar = atof( words.GetWord(1) );
			SwGlobal::GetRender()->SetFarChunk( fogFar );
		}
		/*else if ( words.Compare( 0, "watertype" ) && G_OpenCommand)
		{
			GetShaderMgr()->SetWaterType( atoi( words.GetWord(1) ) );
		}*/
		else if ( words.Compare( 0, "testPrintText" ) && G_OpenCommand)
		{
			if(g_pPrintTextEffect) 
			{
				int CNum = atoi( words.GetWord(1));
				int CreateCnt = atoi( words.GetWord(2));

				   if( CreateCnt > 0)
				   {
					for (int i = 0; i < CreateCnt ; i++)
					{
						g_pPrintTextEffect->Create(CNum,CPrintTextEffect::KILLTARGET );
					}
				   }else
				   {
                      g_pPrintTextEffect->Create(CNum,CPrintTextEffect::KILLTARGET );
				   }
				
			}
		}
		else if ( words.Compare( 0, "shadowtype" ) && G_OpenCommand)
		{
			GetShaderMgr()->SetShadowType( atoi( words.GetWord(1) ) );
		}
		else if ( words.Compare( 0, "reseteffect" ) && G_OpenCommand)// updataeffect
		{
			GetShaderMgr()->ResetEffect();
		}		

		//add by yanli  2010-9-9
		else if( words.Compare( 0, "3d" ) && G_OpenCommand)
		{
			CUserData::Instance()->SetViewSet( 1 );
			getwsCamera()->Set45DegreeCameraMode(false);
		}

		else if( words.Compare( 0, "2.5d" ) && G_OpenCommand)
		{
			CUserData::Instance()->SetViewSet( 0 );
			getwsCamera()->Set45DegreeCameraMode(true);
		}
		else if( words.Compare( 0, "2.8d" ) && G_OpenCommand)
		{
			CUserData::Instance()->SetViewSet( 0 );
			getwsCamera()->Set28Mode(true);
		}


		else if( words.Compare( 0, "multiloadmex" ) && G_OpenCommand)
		{
			g_bMultiThreadLoadingMex = atoi( words.GetWord(1) );
		}
		else if( words.Compare( 0, "savefont" ) && G_OpenCommand)
		{
			FontSystem::SaveAllFontTexture();
		}
		else if( words.Compare( 0, "maxpartnum" ) && G_OpenCommand)
		{
			int num = atoi( words.GetWord( 1 ) );
			GetEngine()->SetMaxPartNum( num );
		}
		else if( words.Compare( 0, "animstep" ) && G_OpenCommand)
		{
			int step = atoi( words.GetWord( 1 ) );
			theHeroGame.GetPlayerMgr()->SetUpdateAnimTimeStep( step );
		}
		else if( words.Compare( 0, "msaa" ) && G_OpenCommand)
		{
			int nB = atoi( words.GetWord(1));
			if( nB > 0 )
			{
				unsigned int uiValue = min( 1, nB );
				theApp->GetD3DPP()->MultiSampleType = (D3DMULTISAMPLE_TYPE)( uiValue * 2 );
				theApp->ChangeDevice();
			}			
		}
		else if( words.Compare( 0, "brightcontrast" ) && G_OpenCommand)
		{
			float br = atof( words.GetWord( 1 ) );
			D3DXVECTOR3 vC( atof( words.GetWord( 2 ) ), atof( words.GetWord( 3 ) ), atof( words.GetWord( 4 ) ) );
			PostProcessManager::instance().SetBrightNContrast( br, vC );
		}
		else if ( words.Compare( 0, "bloompost" ) )
		{
			bool enable = words.Compare( 1, "1" ) || words.Compare( 1, "on" );
			//PostProcessManager::instance().enablePostProcess( enable );
			PostProcessManager::instance().enableProcess("Bloom",enable);

			float value = atof( words.GetWord(2) );
			PostProcessManager::instance().setParameter( "BloomScale", D3DXVECTOR4( value, 0, 0, 0 ) );

			value = atof( words.GetWord(3) );
			PostProcessManager::instance().setParameter( "Luminance", D3DXVECTOR4( value, 0, 0, 0 ) );
		}
		/*else if( words.Compare( 0, "dof" ))
		{
			bool enable = words.Compare( 1, "1" ) || words.Compare( 1, "on" );
			PostProcessManager::instance().enableProcess( "DOF", enable );
		}*/

		else if( words.Compare( 0, "lightshaft" ) && G_OpenCommand)
		{
			bool enable = words.Compare( 1, "1" ) || words.Compare( 1, "on" );
			PostProcessManager::instance().enableProcess( "LightShaft", enable );
		}
		else if( words.Compare( 0, "ls_para" ) && G_OpenCommand)
		{
			float value1 = atof( words.GetWord(1) );
			float value2 = atof( words.GetWord(2) );
			float value3 = atof( words.GetWord(3) );
			float value4 = atof( words.GetWord(4) );
			PostProcessManager::instance().setParameter( "vDWDE", D3DXVECTOR4( value1, value2, value3, value4 ));
		}
		else if( words.Compare( 0, "shadowheight" ) && G_OpenCommand)
		{
			theHeroGame.SetLightHeight(atof( words.GetWord(1) ));
			theHeroGame.SetProjHeight(atof( words.GetWord(2) ));

		}
		else if( words.Compare( 0, "bloom" ) && G_OpenCommand)
		{
			bool enable = words.Compare( 1, "1" ) || words.Compare( 1, "on" );
			PostProcessManager::instance().enableProcess( "Bloom", enable );
		}
		else if( words.Compare( 0, "dofplane" ) && G_OpenCommand)
		{
			float value1 = atof( words.GetWord(1) );
			float value2 = atof( words.GetWord(2) );
			float value3 = atof( words.GetWord(3) );
			float value4 = atof( words.GetWord(4) );
			PostProcessManager::instance().setParameter( "FocalPlane", D3DXVECTOR4( value1, value2, value3, value4 ));
		}
		else if ( words.Compare( 0, "darkscale" ) && G_OpenCommand )
		{
			float f1 = atof( words.GetWord(1) );
			float f2 = atof( words.GetWord(2) );
			float f3 = atof( words.GetWord(3) );
			PostProcessManager::instance().setParameter( "DarkScale", D3DXVECTOR4( f1, f2, f3, 0 ) );

		}
		else if( words.Compare( 0 , "dynamicgrass") && G_OpenCommand)
		{
			bool enable = words.Compare(1, "1");
			MexInstanceMan::SetDynamicGrass(enable);
		}
		else if ( words.Compare( 0, "fsaa" ) && G_OpenCommand)
		{
			bool enable = words.Compare( 1, "1" ) || words.Compare( 1, "on" );
			GetMe3dConfig()->SetFullSceneAntialiasing( enable );
		}
		else if ( words.Compare( 0, "showhelmet" ) && G_OpenCommand && false)
		{
			bool show = words.Compare( 1, "1" ) || words.Compare( 1, "on" );
			theHeroGame.GetPlayerMgr()->GetMe()->ShowHelmetAndSendMsg(show);
			theHeroGame.GetPlayerMgr()->GetMe()->ChangeSkeletonAndEquipAllItem(
				theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting));

			s_CUI_ID_FRAME_BaseProperty.RefreshEquip();
			//更新界面
			thePlayerRole.UpdateUI();
		}
		else if ( words.Compare( 0, "window" ) && G_OpenCommand)
		{
			SCREEN_WIDTH = atoi( words.GetWord(1) );
			SCREEN_HEIGHT = atoi( words.GetWord(2) );

			float fScale = (float)SCREEN_HEIGHT/768.0f;
			if ( fScale > 1.0f )
				fScale = 1.0f;
			ControlObject::SetUIScale(1/*(float)SCREEN_HEIGHT/960.0f*/);
			ControlObject::SetFontScale( /*1*/ fScale );
			ControlObject::SetAdjustSCALE( fScale );

			GetMe3dConfig()->m_nScreenWidth = SCREEN_WIDTH;
			GetMe3dConfig()->m_nScreenHeight = SCREEN_HEIGHT;
			getwsCamera()->GetViewPortMain()->Width = SCREEN_WIDTH;
			getwsCamera()->GetViewPortMain()->Height = SCREEN_HEIGHT;
			theApp->GetD3DPP()->MultiSampleType = D3DMULTISAMPLE_NONE;
			theApp->GetD3DPP()->MultiSampleQuality = 0;
			theApp->ResizeWindow(atoi( words.GetWord(3) ));
			getwsCamera()->ResetViewport();
		}
		else if( words.Compare( 0, "setpsoffset")&& G_OpenCommand)
		{
			float fOffset = (float)atoi( words.GetWord(1));
		}
		else if ( words.Compare( 0, "sample" ) && G_OpenCommand)
		{
			theApp->GetD3DPP()->MultiSampleType = (D3DMULTISAMPLE_TYPE)atoi( words.GetWord(1) );
			theApp->ChangeDevice();
		}
		else if ( words.Compare( 0, "shader" ) && G_OpenCommand)
		{
			graphics::ShaderManager::instance()->useShader(atoi( words.GetWord(1) ));
		}
		else if ( words.Compare( 0, "graphics" ) && G_OpenCommand)
		{
			theApp->ChangeGraphicsLevel(atoi( words.GetWord(1) ));
		}
		else if ( words.Compare( 0, "gate" ) && G_OpenCommand && false)
		{
			CUI_ID_FRAME_LOGIN::g_dwSwitchGatePeriod = atoi( words.GetWord(1) );
		}
		else if( words.Compare( 0, "lock45camera") && G_OpenCommand)
		{
			int nShow = atoi( words.GetWord( 1 ) );
			if(words.GetWordCount() == 1)
				nShow = 1;
			getwsCamera()->Set45DegreeCameraMode(nShow == 1);
		}
		else if( words.Compare( 0, "set45camera") && G_OpenCommand)
		{
			float fDegree = atof( words.GetWord( 1 ) );
			getwsCamera()->Set45DegreeCameraRotateZ( fDegree - 90 );
			if( getwsCamera()->Get45DegreeCameraRotateZ() >= 0 )
				getwsCamera()->Set45DegreeCameraRotateZ( -5 );
			if( getwsCamera()->GetLock45DegreeCameraMode() )
				getwsCamera()->Set45DegreeCameraMode(TRUE);
		}
		else if( words.Compare( 0, "lockfollowcamera") && G_OpenCommand)
		{
			int nShow = atoi( words.GetWord( 1 ) );
			if(words.GetWordCount() == 1)
				nShow = 1;
			getwsCamera()->SetFollowCameraMode(nShow == 1);
		}
		else if( words.Compare( 0, "footprint") && G_OpenCommand)
		{
			int nShow = atoi( words.GetWord( 1 ) );
			if(words.GetWordCount() == 1)
				nShow = 1;
			g_bRenderFootPrint = (nShow != 0);
		}
		else if( words.Compare( 0, "loadui") && G_OpenCommand )
		{
			TCHAR Buffer[256] = {0};
			GetCurrentDirectory(256, Buffer);

			OPENFILENAME ofn;       // common dialog box structure
			char szFile[260];       // buffer for file name

			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szFile;
			//
			// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
			// use the contents of szFile to initialize itself.
			//
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "MEUI files\0*.meui\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			// Display the Open dialog box. 

			if (GetOpenFileName(&ofn))
			{
				SetCurrentDirectory(Buffer);
				g_strViewerUIFilename = szFile;

				DWORD dwResult = theUiManager.AddFrame( g_strViewerUIFilename.c_str(), false, UI_Render_LayerThree );
				if ( dwResult == 0 )
				{
					MessageBoxA(0, "读取文件失败！", "UI Viewer", MB_OK|MB_ICONERROR);
				}
			}
		}
		else if( words.Compare( 0, "setroledist") && G_OpenCommand)
		{
			int iDist = atoi( words.GetWord( 1 ) );
			if( iDist > 0 )
				theApp->GetPlayerMgr()->SetFarRole((float)iDist);
		}
		else if( words.Compare( 0, "setplayerrender") && G_OpenCommand) // 设置人物渲染优先级
		{
			int iFlag = atoi( words.GetWord( 1 ) );
			if( iFlag >= 0 )
			{
				theHeroGame.GetPlayerMgr()->SetPlayerRenderPriority(iFlag);
			}
		}
		else if( words.Compare( 0, "autoskill") && G_OpenCommand && false)
		{
			int iAutorun = atoi( words.GetWord( 1 ) );
			if(words.GetWordCount() == 1)
				iAutorun = 1;
			theHeroGame.GetPlayerMgr()->SetUseSkillBuf((BOOL)iAutorun);
		}
		else if( words.Compare( 0, "serverinfo") && G_OpenCommand && false)
		{
			std::string str = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile()->GetTileName();
			str += ' ';
			str += s_CUI_ID_FRAME_MiniMap.GetServerName();

			s_CUI_ChatInfoBox.AddInfo( str.c_str() );
		}
		else if( words.Compare( 0, "clearprotecttime") && G_OpenCommand)
		{
			CWealthProtect::Instance().ClearProtectEndintTime();
		}
		else if( words.Compare( 0, "setping") && G_OpenCommand && false)
		{
			DWORD ping = atoi( words.GetWord( 1 ) );
			if(words.GetWordCount() > 1 && theHeroGame.GetPlayerMgr() )
			{
				theHeroGame.GetPlayerMgr()->m_dwGamePing = ping;
				if( g_GameState == G_MAIN )
				{
					s_CUI_ID_FRAME_MiniMap.SetPing(ping);
				}
			}
		}
		else if( words.Compare( 0, "return" ) && G_OpenCommand && false)
		{
			MsgExit msg;
			GettheNetworkInput().SendMsg( &msg );
			//GettheNetworkInput().CheckSendReq();

			g_bMainToSelectUI = TRUE;
		}
		else if( words.Compare( 0, "decompound" ) && G_OpenCommand)
		{
			int iOpenUI = atoi( words.GetWord( 1 ) );
			if(words.GetWordCount() == 1)
				iOpenUI = 1;
			if( iOpenUI != 0 )
				iOpenUI = 1;
			s_CUI_ID_FRAME_Decompound.SetVisable((bool)iOpenUI);
			if( theHeroGame.GetPlayerMgr() )
			{
				D3DXVECTOR3 kPos = theHeroGame.GetPlayerMgr()->GetMe()->GetPos();
				Vector kVecPos = Vector(kPos.x, kPos.y, kPos.z);
				s_CUI_ID_FRAME_Decompound.SetVisiblePosition(kVecPos);
			}
		}
		else if( words.Compare( 0, "hiteffecttime" ) && G_OpenCommand)
		{
			if (words.GetWordCount() > 1)
			{
				theHeroGame.SetPlayerHitMeEffectTotalTime(atoi( words.GetWord( 1 ) ));
				theHeroGame.SetPlayerHitMeEffectPlayerSpeedScale(atof( words.GetWord( 2 ) ));
			}
		}
		else if( words.Compare( 0, "loadmodelperframe")&& G_OpenCommand)
		{
			if( words.GetWordCount() != 1 )
			{
				g_iLoadModelPerFrame = atoi( words.GetWord( 1 ) );
				if( g_iLoadModelPerFrame <= 0 )
					g_iLoadModelPerFrame = 1;
			}
		}
		else if(words.Compare(0,"ChangeSuit")&&words.GetWordCount() == 2 && G_OpenCommand)
		{
			const char* pszWord = words.GetWord(1);

			int nCoolDown = 0;
			if(sscanf_s(pszWord,"%d",&nCoolDown) == 1)
				s_CUI_ID_FRAME_ChangeEquip.SetElapseTime(nCoolDown);
		}
		else if( words.Compare( 0, "onlinetime") && G_OpenCommand)
		{
			if (words.GetWordCount() > 1)
			{
				int time = atoi( words.GetWord( 1 ) );
				//CPreventWallow::Instance().SetFCMOnlineTime(time);
			}
		}
		else if( words.Compare( 0, "shutdownserver") && G_OpenCommand && false)
		{
			if (words.GetWordCount() > 1)
			{
				int time = atoi( words.GetWord( 1 ) );
				if( time > 0 )
				{
					MsgShutdownServer kShutdownMsg;
					kShutdownMsg.delayTime = time;

					__time64_t curTime;
					_time64(&curTime);
					kShutdownMsg.nowTime = curTime + theHeroGame.GetServerAndLocalOffsetTime();
					theHeroGame.OnMsgServerShutdown(&kShutdownMsg);
				}
			}
		}
		else if( words.Compare( 0, "movestarup") && G_OpenCommand)
		{
			s_CUI_ID_FRAME_MoveStarUpgrade.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
		}
		else if( words.Compare( 0, "starmatup") && G_OpenCommand)
		{
			s_CUI_ID_FRAME_StarMaterialUpgrade.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SetVisable( true );
			s_CUI_ID_FRAME_PACK.SwitchToBag(BT_MaterialBag);
		}
		else if( words.Compare( 0, "givepresent" ) && G_OpenCommand)
		{
			CGivePresentLogic::Instance().SetPlayGivePresentEffect(true);
			if (words.GetWordCount() > 3)
			{
				int time = atoi( words.GetWord( 1 ) );
				if( time > 0 )
					CGivePresentLogic::Instance().SetGivePresentDuration(time);
				float rate = atof( words.GetWord(2) );
				if( rate > 0 )
					CGivePresentLogic::Instance().SetGivePresentFlashRate(rate);
				float scale = atof( words.GetWord(3) );
				if( scale > 0 )
					CGivePresentLogic::Instance().SetGivePresentScale(scale);
			}
		}
		else if( words.Compare( 0, "expaction") && G_OpenCommand)
		{
			s_CUI_ID_FRAME_Action.SetVisable(true);
		}
		else if( words.Compare( 0, "intensifystar") && G_OpenCommand && false)
		{
			s_CUI_ID_FRAME_IntensifyStar.SetVisable( true );
			if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
			{
				s_CUI_ID_FRAME_IntensifyStar.SetVisiblePosition( *(Vector*)&theHeroGame.GetPlayerMgr()->GetMe()->GetPos() );
			}			
		}
//		else if(words.Compare(0,"ShowAnim"))
//		{
// 			s_CUI_ID_FRAME_StoryTip.SetVisable(true);
// 			int nTime = atoi(words.GetWord(1));
// 			int nStringId = atoi(words.GetWord(2));
// 			s_CUI_ID_FRAME_StoryTip.ShowAnim(nTime,nStringId);
//		}
// 		else if(words.Compare(0,"OutputMeme"))
// 		{
//            CMeMemoryDetailDump::Instance()->DumpDetailInfo();
// 		}
		if(words.Compare(0,"Epic")&& G_OpenCommand)
		{
			s_CUI_ID_FRAME_Epic.SetVisable(true);
			int nIndex = atoi(words.GetWord(1));
			if(nIndex == 1)
			    s_CUI_ID_FRAME_Epic.InitAnim();

		}

		if(words.Compare(0,"OpenUI")&& G_OpenCommand && false)
		{
			int nNum = atoi(words.GetWord(1));

			MsgOpenUI msg;
			msg.UIFlag = nNum;

			theHeroGame.GetPlayerMgr()->OnOpenUI(&msg);
		}

		if(words.Compare(0,"ShowMonsterArea")&& G_OpenCommand && false)
		{
			int nValue = atoi(words.GetWord(1));
			theHeroGame.GetPlayerMgr()->SetShowMonsterArea(nValue);
		}

		//added by zilong. 2011-02-12. ------------------------------------
		if(words.Compare(0, "reloadskill")&& G_OpenCommand && false)
		{
			if(1 == words.GetWordCount())
			{//reload skill.config
				char fileName[MAX_PATH] = {0};
				MeSprintf_s(fileName, sizeof(fileName)/sizeof(char)-1, "%s\\Data\\Config\\Item\\Skill.config", SwGlobal::GetWorld()->GetAppDataCharDir());

				if(!GetItemDetailConfig().LoadSkillItem(fileName/*, CItemDetailConfig::ConfigLoadMode_Reload*/))
				{
					return FALSE;
				}
			}
			else if(2 == words.GetWordCount())
			{//reload effect files
				if(words.Compare(1, "all"))
				{
					GetEffectMgr()->DestroyCache();
				}
			}
			else if(3 == words.GetWordCount())
			{//reload the effect files for the specfic skill
				
				int id = atoi(words.GetWord(1));
				int level = atoi(words.GetWord(2));

				GetEffectMgr()->DestroyCache();
			}

			//thePlayerRole.m_SkillBag.ReInit();
		}
		//added by zilong. end. -------------------------------------------

		if(words.Compare(0,"ShowEffect")&& G_OpenCommand)
		{
			int nPlayerID = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
			CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(nPlayerID);
			if(pPlayer)
			     PlayEffect( (char*)words.GetWord( 1 ),theHeroGame.GetPlayerMgr()->GetMe(),1.0f,0,pPlayer,0);
		}

		if(words.Compare(0,"PlayAnim")&& G_OpenCommand)
		{
			const char* pszAnim = words.GetWord(1);
			bool bUpper = atoi(words.GetWord(2));
			theHeroGame.GetPlayerMgr()->GetMe()->TestPlayAnimByType(pszAnim,bUpper);
		}

		if(words.Compare(0,"ChangeRunTime")&& G_OpenCommand)
		{
			int nTime = atoi(words.GetWord(1));
			if( nTime >= 0 )
				gCfg.m_nRoleRunLoopTime = nTime;
		}

		if(words.Compare(0,"MipLod")&& G_OpenCommand)
		{
			float fLod = atof(words.GetWord(1));
			theHeroGame.GetPlayerMgr()->SetPlayerLod(fLod);
			//GetMe3dConfig()->SetMipLodBais( fLod );
		}

		if(words.Compare(0,"UnEquipTali")&& G_OpenCommand && false)
		{
			int nPos = atoi(words.GetWord(1));
			MsgUnEquipTalisman msg;
			msg.stPackIndex = nPos;
			GettheNetworkInput().SendMsg(&msg);
		}

		if(words.Compare(0,"Taliman")&& G_OpenCommand && false)
		{
			s_CUI_ID_FRAME_Talisman.SetVisable(true);
			s_CUI_ID_FRAME_Talisman.UpdateTalisman(&thePlayerRole.m_pVisual->talisman);
		}

		if(words.Compare(0,"Talismanskill")&& G_OpenCommand && false)
		{
			MsgReqSkillAttack msg;
			msg.bCharTarget = true;
			msg.stWho = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
			msg.chSkillCount = 1;

			ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(thePlayerRole.m_pVisual->talisman.itembaseinfo.ustItemID);
			if(!pItem)
				return FALSE;

			ItemDefine::SItemTalisman *p = (ItemDefine::SItemTalisman*)pItem;

			msg.stSkill = p->skillId;
			msg.stSkillLevel = p->ustLevel;
		    GettheNetworkInput().SendMsg( &msg );
		}
		if (words.Compare(0,"otherinfo")&& G_OpenCommand)
		{
			s_CUI_ID_FRAME_OtherInfo.SetVisable(true);
		}
		if (words.Compare(0,"selfinfo")&& G_OpenCommand)
		{
			s_CUI_ID_FRAME_SelfInfo.SetVisable(true);
		}
		if(words.Compare(0,"SeeBaseInfo")&& G_OpenCommand)
		{
			s_CUI_ID_FRAME_SeeBasePropertyBGFrame.SetVisable(true);
		}
		if (words.Compare(0,"Card")&& G_OpenCommand)
		{
			s_CUI_ID_FRAME_SuAnimalCard.SetVisable(true);
		}
		if (words.Compare(0,"shortcutkey")&& G_OpenCommand)
		{
			s_CUI_ID_FRAME_custom.SetVisable(true);
		}


		// 测试 Movie    added by zhuomeng.hu		[3/1/2011]
		if( words.Compare( 0, "PlayWmv" )&& G_OpenCommand )
		{
			bool bPlay = atoi( words.GetWord( 1 ) );
			int nId = atoi( words.GetWord( 2 ) );

			if( bPlay )
			{
				CMovieManager::Instance()->OpenByType( nId );
			}
			else
			{
				CMovieManager::Instance()->Close();
			}
		}

		if(words.Compare(0,"CameraTrack")&& G_OpenCommand)
		{
			int bPlay  = atoi(words.GetWord(1));
			int nModelID = atoi(words.GetWord(2));
			int nRot     = atoi(words.GetWord(3));
			const char* pszAnim = words.GetWord(4);
			if(!bPlay)
			{
				theHeroGame.GetPlayerMgr()->EndTrack();
				return FALSE;
			}

			int nPlayerID = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
			CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(nPlayerID);
			if(!pPlayer)
				return FALSE;

			float fx,fy,fz;
			pPlayer->GetPos(&fx,&fy,&fz);

			theHeroGame.GetPlayerMgr()->InitCamera(nModelID);
			theHeroGame.GetPlayerMgr()->PlayTaskAnim(pszAnim,fx,fy,fz,nRot);
			theHeroGame.GetPlayerMgr()->BeginTrack();
		}

		if(words.Compare(0,"ShowHelper")&& G_OpenCommand)
		{
			int nIndex = atoi(words.GetWord(1));
			GetMe3dConfig()->SetRenderHelper((Config::ERenderHelper)nIndex);
		}

		if(words.Compare(0,"ShowMovice")&& G_OpenCommand)
		{
			int nShow = atoi(words.GetWord(1));

			s_CUI_ID_FRAME_Lens.SetVisable(true);
			if(nShow)
			    s_CUI_ID_FRAME_Lens.BeginAnim();
			else
				s_CUI_ID_FRAME_Lens.EndAnim();
		}

		if(words.Compare(0,"SceneType")&& G_OpenCommand)
		{
			int nID = atoi(words.GetWord(1));

			int nPlayerID = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
			CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(nPlayerID);
			if(pPlayer)
				pPlayer->BeginPlaying(nID);
		}

		if(words.Compare(0,"NpcHeight")&& G_OpenCommand)
		{
			float fHeight = s_CUI_ID_FRAME_Gut.GetNpcHeight();
			char szInfo[256] = {0};
			MeSprintf_s(szInfo,sizeof(szInfo),"升高:%f",fHeight);

			s_CUI_ID_FRAME_Gut.SetNpcGutText(szInfo);
		}

		if(words.Compare(0,"SetNpcHeight")&& G_OpenCommand)
		{
			float fHeight = atof(words.GetWord(1));
			float fScele  = atof(words.GetWord(2));
			float fViewHeight = atof(words.GetWord(3));

			s_CUI_ID_FRAME_Gut.SetNpcHeightModel(fHeight,fScele,fViewHeight);
		}

		if (words.Compare(0, "openui")&& G_OpenCommand && false)
		{
			int open_index = atoi(words.GetWord(1));
			MsgOpenUI msg;
			msg.UIFlag = open_index;
			theHeroGame.GetPlayerMgr()->OnOpenUI(&msg);
			return TRUE;
		}

		if (words.Compare(0, "hero")&& G_OpenCommand && false)
		{
			int hero_id = atoi(words.GetWord(1));
			MsgG2CReqBianShen BianShen;
			BianShen.result = MsgG2CReqBianShen::eResult_succ;
			BianShen.hero_id = hero_id;
			BianShen.header.stID = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
			theHeroGame.GetPlayerMgr()->OnMsgG2CReqBianShen(&BianShen);
			return TRUE;
		}

		if ( words.Compare( 0, "biaoche") && G_OpenCommand && false)
		{
			int on_or_off = atoi( words.GetWord( 1 ) );
			if (on_or_off == 0)
			{
				MsgRestoreFromBiaocheReq msg;
				GettheNetworkInput().SendMsg(&msg);
			}
		}
		if (words.Compare(0,"showcountry")&& G_OpenCommand)
		{
			int nCountry = atoi( words.GetWord( 1 ) );
			theCountryTipInstance.AddTips(nCountry);
		}
		if (words.Compare(0,"askpresent")&& G_OpenCommand && false)
		{
			string strSN = words.GetWord(1) ;
			MsgAskForPresent msg;
			strncpy_s(msg.sn,sizeof(msg.sn),strSN.c_str(),sizeof(msg.sn) -1);
			GettheNetworkInput().SendMsg(&msg);
		}

		return FALSE;
		unguard;
}

bool CHeroGame::OnProcessMouseEvent( HWND hWnd, UINT uMsg , bool MouseLButtonPress )
{
	guardfunc;
	POINT ptMouse;

	GetCursorPos( &ptMouse );
	ScreenToClient( hWnd, &ptMouse );

	if( g_GameState != G_MAIN )
		return false;

	float fx = ptMouse.x;
	float fy = ptMouse.y;

	if( PickFromTerrain( fx, fy ) )
	{
		GetPlayerMgr()->MouseControlFunction( fx, fy, uMsg, ptMouse.x, ptMouse.y, true );
	}
	else
	{
		GetPlayerMgr()->MouseControlFunction( 0, 0, uMsg, ptMouse.x, ptMouse.y, false );
	}

	// 右键取消施法
	if ( uMsg == WM_RBUTTONDOWN )
	{
		theHeroGame.GetPlayerMgr()->BreakInputMessage( VK_ESCAPE );
	}

	return true;
	unguard;
}


void CHeroGame::OnChangeControlType(const bool bMouz_Camera)
{
	if (focusInUIEdit())
	{
		return;
	}
	if (bMouz_Camera)
	{
		if (g_bMouseMoveMode)
		{
			g_bMouseMoveMode = false;

			GetPlayerMgr()->HideTargetPointEffect();

		}
		else
		{
			g_bMouseMoveMode = true;
		}
		bool IsTrue = (bool)g_bMouseMoveMode;
		s_CUI_ID_FRAME_MAIN.setKeyboardChecked();
	}
	else
	{
		if (getwsCamera()->GetLockCameraMode())
		{
			getwsCamera()->SetLockCameraMode( false );
		}
		else
		{
			getwsCamera()->SetLockCameraMode( true );
		}

		bool IsTrue = (bool)getwsCamera()->GetLockCameraMode();
		s_CUI_ID_FRAME_MAIN.setAngleChecked();
	}
}

float CHeroGame::GetZRotatePerStamp( int nData, DWORD dwStampTime )
{
	guardfunc;
	float fData = nData;

	if( m_bZRotateStarted )
	{
		if( dwStampTime >= m_bZRotateStartTime )
		{
			DWORD dwCostTime = dwStampTime - m_bZRotateStartTime;
			float fZRotateInertia =  fabs(fData)/dwCostTime*getwsCamera()->GetCameraInertia();

			if( fZRotateInertia > 0.618f )
				fZRotateInertia = 0.618f;

			float fZRotateBuffer = fData;

			for( int i = 0; i < 100; i++ )
			{
				if( fabs(fData) > 0.0001f )
				{
					fData = fData*fZRotateInertia;
					fZRotateBuffer += fData;
				}
				else
				{
					break;
				}
			}

			m_bZRotateStartTime = dwStampTime;
			return fZRotateBuffer;
		}
		else
		{
			OutputDebugString( "GetZRotatePerStampGetZRotatePerStampGetZRotatePerStamp" );
		}
	}
	else
	{
		m_bZRotateStarted = true;
		m_bZRotateStartTime = dwStampTime;
		return fData;
	}
	return 0;
	unguard;
}

float CHeroGame::GetXRotatePerStamp( int nData, DWORD dwStampTime )
{
	guardfunc;
	float fData = nData;

	if( m_bXRotateStarted )
	{
		if( dwStampTime >= m_bXRotateStartTime )
		{
			DWORD dwCostTime = dwStampTime - m_bXRotateStartTime;
			float fXRotateInertia =  fabs(fData)/dwCostTime*getwsCamera()->GetCameraInertia();

			if( fXRotateInertia > 0.618f )
				fXRotateInertia = 0.618f;

			float fXRotateBuffer = fData;

			for( int i = 0; i < 100; i++ )
			{
				if( fabs(fData) > 0.0001f )
				{
					fData = fData*fXRotateInertia;
					fXRotateBuffer += fData;
				}
				else
				{
					break;
				}
			}

			m_bXRotateStartTime = dwStampTime;
			return fXRotateBuffer;
		}
		else
		{
			OutputDebugString( "GetXRotatePerStampGetXRotatePerStampGetXRotatePerStamp" );
		}
	}
	else
	{
		m_bXRotateStarted = true;
		m_bXRotateStartTime = dwStampTime;
		return fData;
	}
	return 0;
	unguard;
}

short GetKeyboardInput( int iKey )
{
	guardfunc;
	bool bActive = ( GetActiveWindow() == g_hWnd );	
	if( !bActive )
		return 0;

	if( iKey < 0 || iKey > DIK_MEDIASELECT )
		return 0;
	return theApp->GetKeyState(iKey);
	unguard;
}

short GetKeyboardInputWin32( int iKey )
{
	guardfunc;
	bool bActive = ( GetActiveWindow() == g_hWnd );	
	if( !bActive )
		return 0;

	return GetAsyncKeyState( iKey );
	unguard;
}



bool CHeroGame::AntiProcess(DWORD dwTime)
{
	guardfunc;
	if (gCfg.m_dwAntiTime > 0)
	{
		if (dwTime - m_checkTime >= gCfg.m_dwAntiTime)
		{
			m_checkTime = dwTime;
			for (int n =0;n< gCfg.m_nAntiProcessNum;n++)
			{
				HWND hwnd = ::FindWindow(0,gCfg.m_strProcessName[n].c_str()); /*::FindWindowEx(NULL,NULL,MAKEINTATOM(0x800),gCfg.m_strProcessName[n].c_str());*/
				if (hwnd)
				{
					return FALSE;
				}
			}
		}	
	}		
	return true;
	unguard;
}


void MeSleep( int Ms )
{
	Sleep(Ms);
// 	HANDLE hTimer = NULL;
// 	LARGE_INTEGER liDueTime;
// 
// 	liDueTime.QuadPart = -Ms * 1000;
// 
// 	// Create a waitable timer.
// 	hTimer = CreateWaitableTimer(NULL, TRUE, "WaitableTimer");
// 	if (!hTimer)
// 	{
// 		MeLog::Instance()->Print("CreateWaitableTimer failed (%d)\n", GetLastError());
// 		return ;
// 	}
// 
// 	// Set a timer to wait for 10 seconds.
// 	if (!SetWaitableTimer(hTimer, &liDueTime, 1, NULL, NULL, 0))
// 	{
// 		MeLog::Instance()->Print("SetWaitableTimer failed (%d)\n", GetLastError());
// 		return ;
// 	}
// 
// 	// Wait for the timer.
// 
// 	if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0)
// 		MeLog::Instance()->Print("WaitForSingleObject failed (%d)\n", GetLastError());
}


void CHeroGame::SlowCPU()
{
	if( m_ustSlowCPU != 0 )
	{
		MeSleep( m_ustSlowCPU );
	}
}

void CHeroGame::UpdateNet()
{
	//处理系统消息
	if( g_GameState == G_LOADSPLASH )
		return;

	m_NetCost = HQ_TimeGetTime();
	UpdateMsg();
	m_NetCost = HQ_TimeGetTime() - m_NetCost;
	if( g_bShowFps && m_NetCost > m_NetCostMax )
		m_NetCostMax = m_NetCost;

	//GettheNetworkInput().CheckSendReq();
}

void CullBaseDir( TCHAR* pszBuffer ) {
	size_t j	= _tcslen( pszBuffer );
	TCHAR* pBuffer = NULL;
	pBuffer = _tcsrchr( pszBuffer, _T('\\') );
	if ( pBuffer ) {
		*(pBuffer+1) = _T('\0');
	}
	j		= _tcslen( pszBuffer );
	if( j > 0 ) {
		if ( ( pszBuffer[j-1] == _T('\\') ) || ( pszBuffer[j-1] == _T('/') ) ) {
			pszBuffer[j-1] = 0;
		}
	}
}

#include <winsock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

LPSTR GetHostIpAddress()
{
	hostent * pHost;
	in_addr in;
	char szHostName[128];
	char * ptr;

	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested=MAKEWORD(2,0);
	if(WSAStartup(wVersionRequested,&wsaData)!=0)
		return NULL;
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=0)
	{
		WSACleanup();
		return NULL;
	}
	if(gethostname(szHostName,sizeof(szHostName))==SOCKET_ERROR)
		return NULL;
	if(! (pHost=gethostbyname(szHostName)))
		return NULL;
	memset((void *)&in,0,sizeof(in));
	in.s_addr=*((unsigned long *)pHost->h_addr_list[0]);
	if(! (ptr=inet_ntoa(in)))
		return NULL;
	WSACleanup();
	return ptr;
}

LPSTR GetRealHostIpAddress()
{
	//by vvx 2012.4.6
	/*WSAData wsaDat;
	short int Port = 80;
	WSAStartup(MAKEWORD(1,1),&wsaDat);
	SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sockAddr;
	memset((void*)&sockAddr,0,sizeof(sockAddr));
	sockAddr.sin_family=AF_INET;
	sockAddr.sin_port=htons(Port);
	sockAddr.sin_addr.s_addr=inet_addr("221.5.47.132");
	connect(sd,
		(LPSOCKADDR)&sockAddr,
		sizeof(sockAddr));*/
	//char sendstr[]="GET /ip2city.asp HTTP/1.1\r\nAccept: */*\r\nReferer: ******\r\nUser-Agent: Mozilla/4.0\r\nHost: www.ip138.com\r\nConnection: close\r\n\r\n\0";
	/*char* p;
	int iLen = strlen(sendstr);
	p = sendstr;
	while (iLen){
		int iRet = send(sd,p,iLen,0);
		if (iRet > 0) {
			p += iRet;
			iLen -= iRet;
			continue;
		}
		return NULL;
	}
	static char recvstr[1024];
	memset(recvstr,0,1024);
	p = recvstr;
	char* iIndex_Head ;
	iLen = 1024;
	int need_len = -1;
	while (iLen){
		int iRet = recv(sd,p,iLen,0);
		if (iRet <= 0) {
			return NULL;
		}
		p += iRet;
		iLen -= iRet;
		if ((iIndex_Head = strstr(recvstr,"\r\n\r\n"))&&(need_len==-1)) {
			char* iIndex = strstr(recvstr,"Content-Length:");
			if (!iIndex) {
				continue;
			}
			char *p1 =  iIndex + strlen("Content-Length:");
			need_len = iIndex_Head - recvstr + 2 + atol(p1);

		}
		if (1024 - iLen >=need_len) { break;

		}
	}
	closesocket(sd);
	WSACleanup(); 
	char *p1 = strstr(iIndex_Head,"[");
	if (p1)
	{
		char *p0 = strstr(p1,"]");
		*p0 = '\0';
		return p1+1;
	}*/
	return NULL;
}

static DWORD GetPackageSize(const char* filename)
{
	if( !filename || filename[0] == '\0' )
		return 0;

	HANDLE hFile;         // the file handle
	hFile = CreateFile(filename, 
		GENERIC_READ,
		0, 
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	DWORD dwFileSize = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{
		dwFileSize = GetFileSize(hFile,  NULL);
		CloseHandle(hFile);
	}
	return dwFileSize;
}

void CHeroGame::PreCreate()
{
	char cszWorkingDir[MAX_PATH] = {0};
	//// Get the current working directory: 
	_getcwd( cszWorkingDir, MAX_PATH );
	char gameDataDir[MAX_PATH] = {0};
	MeSprintf_s(gameDataDir,sizeof(gameDataDir)/sizeof(char) - 1, "%s\\..\\data", cszWorkingDir);
	char gameBinDir[MAX_PATH] = {0};
	MeSprintf_s(gameBinDir,sizeof(gameBinDir)/sizeof(char) - 1, "%s\\..", cszWorkingDir);
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(gameDataDir,&data);
	bool bFind = (hFind != INVALID_HANDLE_VALUE);
	if (bFind)
	{
		strlwr(cszWorkingDir);
		char dataStr[MAX_PATH] = {0};
		strcpy(dataStr, cszWorkingDir);
		char *p = strrchr(dataStr, '\\');
		if( p )
			*p = 0;

		CWorld::SetAppCharDir( cszWorkingDir );
		CWorld::SetAppDataCharDir(dataStr);
		std::wstring appStr = _tUNICODECHAR(dataStr);
		wchar_t* pszStr = const_cast<wchar_t*>(appStr.c_str());
		CWorld::SetAppDataDir(pszStr);
		SetRootPath(dataStr);

		packet_namespace::s_PacketRootPath=GetRootPath();
		
		
		if (false)//g_DirectReadInPackage)
		{
			int nErrorFile = -1;
			int nRet=0;//= Launcher::GetLoadDataInstance()->SetMainDir(gameBinDir,cszWorkingDir, nErrorFile);
			if (nRet != 0)
			{
				//by vvx 2012.4.6
				//char * pAddress = GetHostIpAddress();
				//char * pRealAddress = GetRealHostIpAddress();

				//std::string to("dumplaunch@tolez.com"); 
				//std::string from("dumplaunch@tolez.com"); 
				//std::string smtpserver("mail.tolez.com"); 
				//char acTemp[256] = {0};
				//// subject
				//std::string subject;
				//std::string macAddr;
				//GetMACAddressString( &macAddr );
				//MeSprintf_s( acTemp , 256, "Version: %s , Mac: %s, ErrorCode: %d, ErrorFile: %d", ApplicationConfig::Instance().GetFullVersion(), macAddr.c_str(), nRet, nErrorFile );
				//subject += acTemp;

				//memset( acTemp , 0, sizeof( acTemp ) );
				//std::string content;// = std::string( pAddress ) + std::string( pRealAddress );			
				//MeSprintf_s( acTemp , 256, "\nVersion: %s \nErrorCode: %d", ApplicationConfig::Instance().GetFullVersion(), nRet );
				//content += acTemp;

				//jwsmtp::mailer mail( to.c_str(), from.c_str(), subject.c_str(), content.c_str(), 
				//	smtpserver.c_str(), jwsmtp::mailer::SMTP_PORT, false ); 
				//mail.username( "dumplaunch@tolez.com" );
				//mail.password( "Win2008" );

				HKEY hkey;
				char szCompress[256] = {0};
				if( ERROR_SUCCESS == RegOpenKey( HKEY_LOCAL_MACHINE, TEXT("Software\\WinRAR"), &hkey ) )
				{
					DXUtil_ReadStringRegKey( hkey, TEXT("exe32"), szCompress, 256, "" );
					RegCloseKey( hkey );
				}

				switch( nErrorFile )
				{
				case 0:		// client_config
					{
						bool bMailRAR = false;
						//by vvx 2012.4.6
						/*if( szCompress[0] != '\0')
						{
							char CmdLine[MAX_PATH] = {0};
							::DeleteFile( "config.rar" );
							sprintf(CmdLine,"%s A -ep1 config.rar Config.package", szCompress);
							WinExec(CmdLine, SW_HIDE);
							if(_access("config.rar",0) == 0)   
							{
								bMailRAR = true;
								mail.attach( "config.rar" );
							}
						}
						if( !bMailRAR )
						{
							DWORD dwFileSize = GetPackageSize("Config.package");
							if( dwFileSize > 0 && dwFileSize < 1024*1024)
								mail.attach( "Config.package" );
						}*/
					}
					break;
				case 5:		// Data\Effect.package
					{
						bool bMailRAR = false;
						//by vvx 2012.4.6
						/*if( szCompress[0] != '\0')
						{
							char CmdLine[MAX_PATH] = {0};
							::DeleteFile( "effect.rar" );
							sprintf(CmdLine,"%s A -ep1 effect.rar ..\\Data\\Effect.package", szCompress);
							WinExec(CmdLine, SW_HIDE);
							if(_access("effect.rar",0) == 0)   
							{
								bMailRAR = true;
								mail.attach( "effect.rar" );
							}
						}
						if( !bMailRAR )
						{
							DWORD dwFileSize = GetPackageSize("..\\Data\\Effect.package");
							if( dwFileSize > 0 && dwFileSize < 1024*1024)
								mail.attach( "..\\Data\\Effect.package" );
						}*/
					}
					break;
				case 9:		// Data\Shader.package
					{
						bool bMailRAR = false;
						//by vvx 2012.4.6
						/*if( szCompress[0] != '\0')
						{
							char CmdLine[MAX_PATH] = {0};
							::DeleteFile( "shader.rar" );
							sprintf(CmdLine,"%s A -ep1 shader.rar ..\\Data\\Shader.package", szCompress);
							WinExec(CmdLine, SW_HIDE);
							if(_access("shader.rar",0) == 0)   
							{
								bMailRAR = true;
								mail.attach( "shader.rar" );
							}
						}
						if( !bMailRAR )
						{
							DWORD dwFileSize = GetPackageSize("..\\Data\\Shader.package");
							if( dwFileSize > 0 && dwFileSize < 1024*1024)
								mail.attach( "..\\Data\\Shader.package" );
						}*/
					}
					break;
				default:
					break;
				}

				//by vvx 2012.4.6
				//mail.operator()();

				::ExitProcess(0 );
			}
		}

		sprintf(dataStr, "%s\\Data\\Config\\String.config", GetRootPath());
		theXmlString.LoadStringFile(dataStr);
	}
}

void CHeroGame::UpdateNetStreamLog( int& nLine )
{
	CaculateNetSreamLog();
	if( m_bStartCaculateNetStream )
	{
		nLine += 20;
		FontSystem::DrawText( "Caculating...", 0, nLine, 0, 0xffffffff, 2, false );	
	}
	else if( g_NetStreamLog.m_dwTotalSentByte > 0 ) // done
	{
		nLine += 20;
		char szTemp[256];

		// total sent
		MeSprintf_s( szTemp, 256, "Total Sent: %d Byte", g_NetStreamLog.m_dwTotalSentByte );
		FontSystem::DrawText( szTemp, 0, nLine, DT_NOCLIP, 0xfffefefe, 2, false );	
		nLine += 20;

		MeSprintf_s( szTemp, 256, "Sent Per-Second: %d Byte", g_NetStreamLog.m_dwSentBytePerSecond );
		FontSystem::DrawText( szTemp, 0, nLine, DT_NOCLIP, 0xffffffff, 2, false );	
		nLine += 20;

		MeSprintf_s( szTemp, 256, "Min Sent: %d Byte", g_NetStreamLog.m_dwMinSentByte );
		FontSystem::DrawText( szTemp, 0, nLine, DT_NOCLIP, 0xffffffff, 2, false );	
		nLine += 20;

		MeSprintf_s( szTemp, 256, "Max Sent: %d Byte", g_NetStreamLog.m_dwMaxSentByte );
		FontSystem::DrawText( szTemp, 0, nLine, DT_NOCLIP, 0xffffffff, 2, false );	
		nLine += 20;	

		MeSprintf_s( szTemp, 256, "Total Received: %d Byte", g_NetStreamLog.m_dwTotalReceivedByte );
		FontSystem::DrawText( szTemp, 0, nLine, DT_NOCLIP, 0xfffefefe, 2, false );		
		nLine += 20;

		MeSprintf_s( szTemp, 256, "Received Per-Second: %d Byte", g_NetStreamLog.m_dwReceivedBytePerSecond );
		FontSystem::DrawText( szTemp, 0, nLine, DT_NOCLIP, 0xffffffff, 2, false );		
		nLine += 20;

		MeSprintf_s( szTemp, 256, "Min Received: %d Byte", g_NetStreamLog.m_dwMinReceivedByte );
		FontSystem::DrawText( szTemp, 0, nLine, DT_NOCLIP, 0xffffffff, 2, false );		
		nLine += 20;

		MeSprintf_s( szTemp, 256, "Max Received: %d Byte", g_NetStreamLog.m_dwMaxReceivedByte );
		FontSystem::DrawText( szTemp, 0, nLine, DT_NOCLIP, 0xffffffff, 2, false );		
		nLine += 20;

	}
}

void CHeroGame::CaculateNetSreamLog()
{
	if( !m_bStartCaculateNetStream )
		return;

	// sent
	g_NetStreamLog.m_dwTotalSentByte += 0;/*GettheNetworkInput().GetSocketCtrl()->GetBytesSent();*/
	g_NetStreamLog.m_dwMaxSentByte = max( g_NetStreamLog.m_dwMaxSentByte, 0/*GettheNetworkInput().GetSocketCtrl()->GetBytesSent() */);
	g_NetStreamLog.m_dwMinSentByte = min( g_NetStreamLog.m_dwMinSentByte, 0/*GettheNetworkInput().GetSocketCtrl()->GetBytesSent() */);

	// received
	g_NetStreamLog.m_dwTotalReceivedByte += 0;/*GettheNetworkInput().GetSocketCtrl()->GetBytesRecved();*/
	g_NetStreamLog.m_dwMaxReceivedByte = max( g_NetStreamLog.m_dwMaxReceivedByte, 0/*GettheNetworkInput().GetSocketCtrl()->GetBytesRecved() */);
	g_NetStreamLog.m_dwMinReceivedByte = min( g_NetStreamLog.m_dwMinReceivedByte, 0/*GettheNetworkInput().GetSocketCtrl()->GetBytesRecved() */);
}

HRESULT CHeroGame::Create( HINSTANCE hInstance )
{
	// 加载鼠标图标
	theMouseManager.LoadCursor();
	HRESULT result = CMyD3DApplication::Create(hInstance);
	if (result != S_OK)
	{
		return result;
	}
	return S_OK;
}

#include "Me3d\Shader.h"
#include "Me3d\ShaderManager.h"

BOOL CHeroGame::LoadFxShader()
{
	// 	graphics::ShaderManager::instance()->initialize( m_pd3dDevice );
	// 	if ( graphics::ShaderManager::instance()->supportPixelShader( 2, 0 ) )
	{
		//try
		{
			char shaderfile[MAX_PATH] = {0};
			MeSprintf_s( shaderfile, MAX_PATH, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Instancing.fxo" );
			MexInstanceMan::GlobalInitialize( shaderfile );
			char path[MAX_PATH] = {0};
#if _MSC_VER >= 1400
			MeSprintf_s( path, MAX_PATH, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\TerrainBlender.fxo" );
#else
			sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\TerrainBlender.fx");
#endif
			graphics::ShaderEffect* pLOD2_TerrainShader = MeNew graphics::ShaderEffect( "TerrainBlender",
				m_pd3dDevice, path );
			graphics::ShaderManager::instance()->addShader( pLOD2_TerrainShader );
			IRenderer* r = GetEngine()->GetRenderer();
			r->EnableUseShader(true);
			static graphics::Material terrainMeterial;
			terrainMeterial.setShader("TerrainBlender");
			r->SetTerrainMaterial(&terrainMeterial);

		}
		// 		catch ( const std::exception& e )
		// 		{
		// 			OutputDebugString( e.what() );
		// 			return false;
		// 		}

	}

	return true;
}

WPARAM GetWindowKeyFromDirectXKey(int iKey)
{
	WPARAM wParam = 0;
	switch(iKey)
	{
	case DIK_0:				wParam = 0x30;			break;
	case DIK_1:				wParam = 0x31;			break;
	case DIK_2:				wParam = 0x32;			break;
	case DIK_3:				wParam = 0x33;			break;
	case DIK_4:				wParam = 0x34;			break;
	case DIK_5:				wParam = 0x35;			break;
	case DIK_6:				wParam = 0x36;			break;
	case DIK_7:				wParam = 0x37;			break;
	case DIK_8:				wParam = 0x38;			break;
	case DIK_9:				wParam = 0x39;			break;
	case DIK_APOSTROPHE:	wParam = VK_OEM_7;		break;
	case DIK_A:				wParam = 0x41;			break;
	case DIK_ADD:			wParam = VK_ADD;		break;	// 小键盘+
	case DIK_B:				wParam = 0x42;			break;
	case DIK_BACK:			wParam = VK_BACK;		break;
	case DIK_BACKSLASH:		wParam = VK_OEM_5;		break; //'|'
	case DIK_C:				wParam = 0x43;			break;
	case DIK_CAPITAL:		wParam = VK_CAPITAL;	break;
	case DIK_COLON:			wParam = VK_OEM_1;		break; //':'
	case DIK_COMMA:			wParam = VK_OEM_COMMA;	break;
	case DIK_D:				wParam = 0x44;			break;
	case DIK_DECIMAL:		wParam = VK_DECIMAL;	break;
	case DIK_DELETE:		wParam = VK_DELETE;		break;
	case DIK_DIVIDE:		wParam = VK_DIVIDE;		break;
	case DIK_DOWN:			wParam = VK_DOWN;		break;
	case DIK_E:				wParam = 0x45;			break;
	case DIK_END:			wParam = VK_END;		break;
	case DIK_EQUALS:		wParam = VK_OEM_PLUS;	break;
	case DIK_ESCAPE:		wParam = VK_ESCAPE;		break;
	case DIK_F:				wParam = 0x46;			break;
	case DIK_F1:			wParam = VK_F1;			break;
	case DIK_F2:			wParam = VK_F2;			break;
	case DIK_F3:			wParam = VK_F3;			break;
	case DIK_F4:			wParam = VK_F4;			break;
	case DIK_F5:			wParam = VK_F5;			break;
	case DIK_F6:			wParam = VK_F6;			break;
	case DIK_F7:			wParam = VK_F7;			break;
	case DIK_F8:			wParam = VK_F8;			break;
	case DIK_F9:			wParam = VK_F9;			break;
	case DIK_F10:			wParam = VK_F10;		break;
	case DIK_F11:			wParam = VK_F11;		break;
	case DIK_F12:			wParam = VK_F12;		break;
	case DIK_F13:			wParam = VK_F13;		break;
	case DIK_F14:			wParam = VK_F14;		break;
	case DIK_F15:			wParam = VK_F15;		break;
	case DIK_G:				wParam = 0x47;			break;
	case DIK_GRAVE:			wParam = VK_OEM_3;		break;	//'~'
	case DIK_H:				wParam = 0x48;			break;
	case DIK_HOME:			wParam = VK_HOME;		break;
	case DIK_I:				wParam = 0x49;			break;
	case DIK_INSERT:		wParam = VK_INSERT;		break;
	case DIK_J:				wParam = 0x4A;			break;
	case DIK_K:				wParam = 0x4B;			break;
	case DIK_L:				wParam = 0x4C;			break;
	case DIK_LBRACKET:		wParam = VK_OEM_4;		break;	//'['
	case DIK_LCONTROL:		wParam = VK_LCONTROL;	break;
	case DIK_LEFT:			wParam = VK_LEFT;		break;
	case DIK_LMENU:			wParam = VK_LMENU;		break;
	case DIK_LSHIFT:		wParam = VK_LSHIFT;		break;
	case DIK_M:				wParam = 0x4D;			break;
	case DIK_MINUS:			wParam = VK_OEM_MINUS;	break; //'-'
	case DIK_MULTIPLY:		wParam = VK_MULTIPLY;	break; //'*'
	case DIK_N:				wParam = 0x4E;			break;
	case DIK_NEXT:			wParam = VK_NEXT;		break;
	case DIK_NUMLOCK:		wParam = VK_NUMLOCK;	break;
	case DIK_NUMPAD0:		wParam = VK_NUMPAD0;	break;
	case DIK_NUMPAD1:		wParam = VK_NUMPAD1;	break;
	case DIK_NUMPAD2:		wParam = VK_NUMPAD2;	break;
	case DIK_NUMPAD3:		wParam = VK_NUMPAD3;	break;
	case DIK_NUMPAD4:		wParam = VK_NUMPAD4;	break;
	case DIK_NUMPAD5:		wParam = VK_NUMPAD5;	break;
	case DIK_NUMPAD6:		wParam = VK_NUMPAD6;	break;
	case DIK_NUMPAD7:		wParam = VK_NUMPAD7;	break;
	case DIK_NUMPAD8:		wParam = VK_NUMPAD8;	break;
	case DIK_NUMPAD9:		wParam = VK_NUMPAD9;	break;
	case DIK_NUMPADCOMMA:	wParam = VK_DECIMAL;	break;
	case DIK_NUMPADENTER:	wParam = VK_RETURN;		break;
	case DIK_O:				wParam = 0x4F;			break;
	case DIK_P:				wParam = 0x50;			break;
	case DIK_PAUSE:			wParam = VK_PAUSE;		break;
	case DIK_PERIOD:		wParam = VK_OEM_PERIOD;	break;
	case DIK_PLAYPAUSE:		wParam = VK_PAUSE;		break;
	case DIK_PRIOR:			wParam = VK_PRIOR;		break;
	case DIK_Q:				wParam = 0x51;			break;
	case DIK_R:				wParam = 0x52;			break;
	case DIK_RBRACKET:		wParam = VK_OEM_6;		break; //']'
	case DIK_RCONTROL:		wParam = VK_RCONTROL;	break;
	case DIK_RETURN:		wParam = VK_RETURN;		break;
	case DIK_RIGHT:			wParam = VK_RIGHT;		break;
	case DIK_RMENU:			wParam = VK_RMENU;		break;
	case DIK_RSHIFT:		wParam = VK_RSHIFT;		break;
	case DIK_S:				wParam = 0x53;			break;
	case DIK_SCROLL:		wParam = VK_SCROLL;		break;
	case DIK_SEMICOLON:		wParam = VK_OEM_1;		break; //';'
	case DIK_SLASH:			wParam = VK_OEM_2;		break; //'/'
	case DIK_SPACE:			wParam = VK_SPACE;		break;
	case DIK_SUBTRACT:		wParam = VK_SUBTRACT;	break; //小键盘-
	case DIK_T:				wParam = 0x54;			break;
	case DIK_TAB:			wParam = VK_TAB;		break;
	case DIK_U:				wParam = 0x55;			break;
	case DIK_UP:			wParam = VK_UP;			break;
	case DIK_V:				wParam = 0x56;			break;
	case DIK_W:				wParam = 0x57;			break;
	case DIK_X:				wParam = 0x58;			break;
	case DIK_Y:				wParam = 0x59;			break;
	case DIK_Z:				wParam = 0x5A;			break;
	default:
		break;
	}
	return wParam;
}


BOOL CHeroGame::Update25Direction()
{
	if( m_nCurrKeyChangeNum <= 0 && m_shCur25Direction == EMD_NONE )
	{
		if( GetKeyboardInput(DIK_W) )
			m_shCur25Direction = EMD_UP;
		else if( GetKeyboardInput(DIK_S) )
			m_shCur25Direction = EMD_DOWN;
		else if( GetKeyboardInput(DIK_A) )
			m_shCur25Direction = EMD_LEFT;
		else if( GetKeyboardInput(DIK_D) )
			m_shCur25Direction = EMD_RIGHT;

		return FALSE;
	}

// 	if( g_b25DRoleMoveFollowMouse || g_b25DMouseLButtonDownOnTerrain )
// 	{
// 		m_shCur25Direction = EMD_NONE;
// 		return FALSE;
// 	}

	// 更新移动方向
	for(int i=0; i<m_nCurrKeyChangeNum; i++)
	{
		if( m_CurrKeyChangeList[i].bPressed )   // 按下
		{
			switch( m_CurrKeyChangeList[i].nKeyIndex )
			{
			case DIK_W:     // Up
				if( m_shCur25Direction <= EMD_AXEDIR )
				{
					if( m_shCur25Direction == EMD_NONE || m_shCur25Direction == EMD_DOWN || m_shCur25Direction == EMD_UP )
					{
						m_shCur25Direction = EMD_UP;
					}
					else 
					{
						if( m_shCur25Direction == EMD_LEFT )
							m_shCur25Direction = EMD_LEFT_UP;
						else if( m_shCur25Direction == EMD_RIGHT )
							m_shCur25Direction = EMD_RIGHT_UP;
					}
				}
				break;
			case DIK_S:     // Down
				if( m_shCur25Direction <= EMD_AXEDIR )
				{
					if( m_shCur25Direction == EMD_NONE || m_shCur25Direction == EMD_DOWN || m_shCur25Direction == EMD_UP )
					{
						m_shCur25Direction = EMD_DOWN;
					}
					else 
					{
						if( m_shCur25Direction == EMD_LEFT )
							m_shCur25Direction = EMD_LEFT_DOWN;
						else if( m_shCur25Direction == EMD_RIGHT )
							m_shCur25Direction = EMD_RIGHT_DOWN;
					}
				}
				break;
			case DIK_A:     // Left
				if( m_shCur25Direction <= EMD_AXEDIR )
				{
					if( m_shCur25Direction == EMD_NONE || m_shCur25Direction == EMD_LEFT || m_shCur25Direction == EMD_RIGHT )
					{
						m_shCur25Direction = EMD_LEFT;
					}
					else 
					{
						if( m_shCur25Direction == EMD_UP )
							m_shCur25Direction = EMD_LEFT_UP;
						else if( m_shCur25Direction == EMD_DOWN )
							m_shCur25Direction = EMD_LEFT_DOWN;
					}
				}
				break;
			case DIK_D:     // Right
				if( m_shCur25Direction <= EMD_AXEDIR )
				{
					if( m_shCur25Direction == EMD_NONE || m_shCur25Direction == EMD_LEFT || m_shCur25Direction == EMD_RIGHT )
					{
						m_shCur25Direction = EMD_RIGHT;
					}
					else 
					{
						if( m_shCur25Direction == EMD_UP )
							m_shCur25Direction = EMD_RIGHT_UP;
						else if( m_shCur25Direction == EMD_DOWN )
							m_shCur25Direction = EMD_RIGHT_DOWN;
					}
				}
				break;
			default:
				break;
			}
		}
		else    // 释放
		{
			switch( m_CurrKeyChangeList[i].nKeyIndex )
			{
			case DIK_W:     // Up
				switch( m_shCur25Direction )
				{
				case EMD_UP:
					m_shCur25Direction = EMD_NONE;
					break;
				case EMD_LEFT_UP:
					m_shCur25Direction = EMD_LEFT;
					break;
				case EMD_RIGHT_UP:
					m_shCur25Direction = EMD_RIGHT;
					break;
				default:
					break;
				}
				break;
			case DIK_S:     // Down
				switch( m_shCur25Direction )
				{
				case EMD_DOWN:
					m_shCur25Direction = EMD_NONE;
					break;
				case EMD_LEFT_DOWN:
					m_shCur25Direction = EMD_LEFT;
					break;
				case EMD_RIGHT_DOWN:
					m_shCur25Direction = EMD_RIGHT;
					break;
				default:
					break;
				}
				break;
			case DIK_A:     // Left
				switch( m_shCur25Direction )
				{
				case EMD_LEFT:
					m_shCur25Direction = EMD_NONE;
					break;
				case EMD_LEFT_UP:
					m_shCur25Direction = EMD_UP;
					break;
				case EMD_LEFT_DOWN:
					m_shCur25Direction = EMD_DOWN;
					break;
				default:
					break;
				}
				break;
			case DIK_D:     // Right
				switch( m_shCur25Direction )
				{
				case EMD_RIGHT:
					m_shCur25Direction = EMD_NONE;
					break;
				case EMD_RIGHT_UP:
					m_shCur25Direction = EMD_UP;
					break;
				case EMD_RIGHT_DOWN:
					m_shCur25Direction = EMD_DOWN;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}

	bool bW = false, bS = false, bA = false, bD = false;
	if( !GetKeyboardInput(DIK_W) )
	{
		if( m_shCur25Direction == EMD_UP )
			m_shCur25Direction = EMD_NONE;
		else if( m_shCur25Direction == EMD_LEFT_UP )
			m_shCur25Direction = EMD_LEFT;
		else if( m_shCur25Direction == EMD_RIGHT_UP )
			m_shCur25Direction = EMD_RIGHT;
	}
	else
		bW = true;
	if( !GetKeyboardInput(DIK_S) )
	{
		if( m_shCur25Direction == EMD_DOWN )
			m_shCur25Direction = EMD_NONE;
		else if( m_shCur25Direction == EMD_LEFT_DOWN )
			m_shCur25Direction = EMD_LEFT;
		else if( m_shCur25Direction == EMD_RIGHT_DOWN )
			m_shCur25Direction = EMD_RIGHT;
	}
	else
		bS = true;
	if( !GetKeyboardInput(DIK_A) )
	{
		if( m_shCur25Direction == EMD_LEFT )
			m_shCur25Direction = EMD_NONE;
		else if( m_shCur25Direction == EMD_LEFT_UP )
			m_shCur25Direction = EMD_UP;
		else if( m_shCur25Direction == EMD_LEFT_DOWN )
			m_shCur25Direction = EMD_DOWN;
	}
	else 
		bA = true;
	if( !GetKeyboardInput(DIK_D) )
	{
		if( m_shCur25Direction == EMD_RIGHT )
			m_shCur25Direction = EMD_NONE;
		else if( m_shCur25Direction == EMD_RIGHT_UP )
			m_shCur25Direction = EMD_UP;
		else if( m_shCur25Direction == EMD_RIGHT_DOWN )
			m_shCur25Direction = EMD_DOWN;
	}
	else
		bD = true;
	if( m_nCurrKeyChangeNum <= 0 )
	{
		switch( m_shCur25Direction )
		{
		case EMD_UP:
			{
				if( bA )
					m_shCur25Direction = EMD_LEFT_UP;
				else if( bD )
					m_shCur25Direction = EMD_RIGHT_UP;
			}
			break;
		case EMD_DOWN:
			{
				if( bA )
					m_shCur25Direction = EMD_LEFT_DOWN;
				else if( bD )
					m_shCur25Direction = EMD_RIGHT_DOWN;
			}
			break;
		case EMD_LEFT:
			{
				if( bW )
					m_shCur25Direction = EMD_LEFT_UP;
				else if( bS )
					m_shCur25Direction = EMD_LEFT_DOWN;
			}
			break;
		case EMD_RIGHT:
			{
				if( bW )
					m_shCur25Direction = EMD_RIGHT_UP;
				else if( bS )
					m_shCur25Direction = EMD_RIGHT_DOWN;
			}
			break;
		}
	}

	switch( m_shCur25Direction )
	{
	case EMD_UP:
		g_vTheRoleTargetDir.y -= 100;
		g_bTheRoleMovingByDir = TRUE;
		g_bTheRoleCountermarch = FALSE;
		if( GetPlayerMgr()->GetMe() )
		{
			GetPlayerMgr()->GetMe()->SetMoving( TRUE );
			GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
		}
		return TRUE;
		break;
	case EMD_DOWN:
		if( g_vTheRoleTargetDir.y == 0 )
		{
			g_vTheRoleTargetDir.y += 100;
			g_bTheRoleCountermarch = FALSE;
			g_bTheRoleMovingByDir = TRUE;
			if( GetPlayerMgr()->GetMe() )
			{
				GetPlayerMgr()->GetMe()->SetMoving( TRUE );
				GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
			}
		}
		return TRUE;
		break;
	case EMD_LEFT:
		g_vTheRoleTargetDir.x += 100;
		g_bTheRoleMovingByDir = TRUE;
		g_bTheRoleCountermarch = FALSE;
		if( GetPlayerMgr()->GetMe() )
		{
			GetPlayerMgr()->GetMe()->SetMoving( TRUE );
			GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
		}
		return TRUE;
		break;
	case EMD_RIGHT:
		g_vTheRoleTargetDir.x -= 100;
		g_bTheRoleMovingByDir = TRUE;
		g_bTheRoleCountermarch = FALSE;
		if( GetPlayerMgr()->GetMe() )
		{
			GetPlayerMgr()->GetMe()->SetMoving( TRUE );
			GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
		}
		return TRUE;
		break;
	case EMD_LEFT_UP:
		g_vTheRoleTargetDir.y -= 100;
		g_vTheRoleTargetDir.x += 100;
		g_bTheRoleMovingByDir = TRUE;
		g_bTheRoleCountermarch = FALSE;
		if( GetPlayerMgr()->GetMe() )
		{
			GetPlayerMgr()->GetMe()->SetMoving( TRUE );
			GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
		}
		return TRUE;
		break;
	case EMD_LEFT_DOWN:
		if( g_vTheRoleTargetDir.y == 0 )
		{
			g_vTheRoleTargetDir.y += 100;
			g_vTheRoleTargetDir.x += 100;
			g_bTheRoleCountermarch = FALSE;
			g_bTheRoleMovingByDir = TRUE;
			if( GetPlayerMgr()->GetMe() )
			{
				GetPlayerMgr()->GetMe()->SetMoving( TRUE );
				GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
			}
		}
		return TRUE;
		break;
	case EMD_RIGHT_UP:
		g_vTheRoleTargetDir.y -= 100;
		g_vTheRoleTargetDir.x -= 100;
		g_bTheRoleMovingByDir = TRUE;
		g_bTheRoleCountermarch = FALSE;
		if( GetPlayerMgr()->GetMe() )
		{
			GetPlayerMgr()->GetMe()->SetMoving( TRUE );
			GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
		}
		return TRUE;
		break;
	case EMD_RIGHT_DOWN:
		if( g_vTheRoleTargetDir.y == 0 )
		{
			g_vTheRoleTargetDir.y += 100;
			g_vTheRoleTargetDir.x -= 100;
			g_bTheRoleCountermarch = FALSE;
			g_bTheRoleMovingByDir = TRUE;
			if( GetPlayerMgr()->GetMe() )
			{
				GetPlayerMgr()->GetMe()->SetMoving( TRUE );
				GetPlayerMgr()->GetMe()->SetCountermarch( FALSE );
			}
		}
		return TRUE;
		break;
	}
	return FALSE;
}

void CHeroGame::CloseLauncher()
{
	HWND hWnd = ::FindWindow(NULL,_T("Launcher"));
	if( hWnd )
		::SendMessageA(hWnd,10401,0,0);
}

void CHeroGame::LoadGlobalData()
{
	{
		CWSModelEffect* pEffect = MeNew CWSModelEffect;
		char filename[MAX_PATH] = {0};
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1,"%s\\%s", GetRootPath(), gCfg.m_szLockPassivityTargetEffectPath);
		if( pEffect->LoadSetting( filename ) )
		{
			g_nLockPassivityTargetEffectID = GetEffectMgr()->RegisterEffect( pEffect );
			if( g_nLockPassivityTargetEffectID == -1 )
			{
				pEffect->Release();
			}
			else
			{
				g_nLockPassivityTargetEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
				pEffect->m_dwBornTime = HQ_TimeGetTime();
				float fRadius = pEffect->m_fRadius;
				int nNum = pEffect->m_nNumInstance;

				CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nLockPassivityTargetEffectContainerID );

				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
					if( !pInstance )
					{
						continue;
					}

					pInstance->dwBornTime = HQ_TimeGetTime() + /*pEffect->m_dwDelay**/pInstance->fDelay;

					if( pEffectContainer )
					{
						pEffect->SetEffectQuoter( pEffectContainer );
					}

					pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
					pInstance->vPos = pInstance->vBornPos;
					pInstance->bVisible = false;

					// 把特效绑定
					if( pEffectContainer )
					{
						pInstance->pMaster = pEffectContainer->GetEffectHelper( eEffectBindPart_Foot );
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


	////////////////////////////////////////////
	{
		CWSModelEffect* pEffect = MeNew CWSModelEffect;
		char filename[MAX_PATH] = {0};
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s\\%s", GetRootPath(), gCfg.m_szLockInitiativeTargetEffectPath);
		if( pEffect->LoadSetting( filename ) )
		{
			g_nLockInitiativeTargetEffectID = GetEffectMgr()->RegisterEffect( pEffect );
			if( g_nLockInitiativeTargetEffectID == -1 )
			{
				pEffect->Release();
			}
			else
			{
				g_nLockInitiativeTargetEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
				pEffect->m_dwBornTime = HQ_TimeGetTime();
				float fRadius = pEffect->m_fRadius;
				int nNum = pEffect->m_nNumInstance;

				CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nLockInitiativeTargetEffectContainerID );

				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
					if( !pInstance )
					{
						continue;
					}

					pInstance->dwBornTime = HQ_TimeGetTime() + /*pEffect->m_dwDelay**/pInstance->fDelay;

					if( pEffectContainer )
					{
						pEffect->SetEffectQuoter( pEffectContainer );
					}

					pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
					pInstance->vPos = pInstance->vBornPos;
					pInstance->bVisible = false;

					// 把特效绑定
					if( pEffectContainer )
					{
						pInstance->pMaster = pEffectContainer->GetEffectHelper( eEffectBindPart_Foot );
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

	{
		CWSModelEffect* pEffect = MeNew CWSModelEffect;
		char filename[MAX_PATH] = {0};
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s\\data\\effect\\common\\TargetPoint.ini", GetRootPath());
		if( pEffect->LoadSetting( filename ) )
		{
			g_nTargetPointEffectID = GetEffectMgr()->RegisterEffect( pEffect );
			if( g_nTargetPointEffectID == -1 )
			{
				pEffect->Release();
			}
			else
			{
				g_nTargetPointEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
				pEffect->m_dwBornTime = HQ_TimeGetTime();
				float fRadius = pEffect->m_fRadius;
				int nNum = pEffect->m_nNumInstance;

				CCharEffectContainer* pTargetPointEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nTargetPointEffectContainerID );

				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
					if( !pInstance )
					{
						continue;
					}

					pInstance->dwBornTime = HQ_TimeGetTime() + /*pEffect->m_dwDelay**/pInstance->fDelay;

					if( pTargetPointEffectContainer )
					{
						pEffect->SetEffectQuoter( pTargetPointEffectContainer );
					}

					pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
					pInstance->vPos = pInstance->vBornPos;
					pInstance->bVisible = false;

					// 把特效绑定
					if( pTargetPointEffectContainer )
					{
						pInstance->pMaster = pTargetPointEffectContainer->GetEffectHelper( eEffectBindPart_Body );
					}
				}

				if( pTargetPointEffectContainer )
				{
					pTargetPointEffectContainer->ApplyEffect( 0, pEffect->GetID() );
				}
			}
		}
		else
		{
			pEffect->Release();
		}
		pEffect = NULL;
	}
	///////////////////////////////
	{

		CWSModelEffect* pEffect = MeNew CWSModelEffect;
		char filename[MAX_PATH] = {0};
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s\\data\\effect\\common\\PKFlag.ini", GetRootPath());
		if( pEffect->LoadSetting( filename ) )
		{
			g_nPKFlagEffectID = GetEffectMgr()->RegisterEffect( pEffect );
			if( g_nPKFlagEffectID == -1 )
			{
				pEffect->Release();
			}
			else
			{
				g_nPKFlagEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
				pEffect->m_dwBornTime = HQ_TimeGetTime();
				float fRadius = pEffect->m_fRadius;
				int nNum = pEffect->m_nNumInstance;

				CCharEffectContainer* pPKFlagEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nPKFlagEffectContainerID );

				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
					if( !pInstance )
					{
						continue;
					}

					pInstance->dwBornTime = HQ_TimeGetTime() + /*pEffect->m_dwDelay**/pInstance->fDelay;

					if( pPKFlagEffectContainer )
					{
						pEffect->SetEffectQuoter( pPKFlagEffectContainer );
					}

					pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
					pInstance->vPos = pInstance->vBornPos;
					pInstance->bVisible = false;

					// 把特效绑定
					if( pPKFlagEffectContainer )
					{
						pInstance->pMaster = pPKFlagEffectContainer->GetEffectHelper( eEffectBindPart_Body );
					}
				}

				if( pPKFlagEffectContainer )
				{
					pPKFlagEffectContainer->ApplyEffect( 0, pEffect->GetID() );
				}
			}
		}
		else
		{
			pEffect->Release();
		}
		pEffect = NULL;
	}
	//////////////////////////////////////////////////////////////////////////
	// point aoe
	//////////////////////////////////////////////////////////////////////////
	{

		CWSModelEffect* pEffect = MeNew CWSModelEffect;
		char filename[MAX_PATH] = {0};
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s\\data\\effect\\common\\AOEPoint.ini", GetRootPath());
		if( pEffect->LoadSetting( filename ) )
		{
			g_nAoePointEffectID = GetEffectMgr()->RegisterEffect( pEffect );
			if( g_nAoePointEffectID == -1 )
			{
				pEffect->Release();
			}
			else
			{
				g_nAoePointEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
				pEffect->m_dwBornTime = HQ_TimeGetTime();
				float fRadius = pEffect->m_fRadius;
				int nNum = pEffect->m_nNumInstance;

				CCharEffectContainer* pAoePointEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nAoePointEffectContainerID );

				for( int nInst = 0; nInst < nNum; nInst++ )
				{
					CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
					if( !pInstance )
					{
						continue;
					}

					pInstance->dwBornTime = HQ_TimeGetTime() + /*pEffect->m_dwDelay**/pInstance->fDelay;

					if( pAoePointEffectContainer )
					{
						pEffect->SetEffectQuoter( pAoePointEffectContainer );
					}

					pInstance->vBornPos = D3DXVECTOR3( 0, 0, 0 );
					pInstance->vPos = pInstance->vBornPos;
					pInstance->bVisible = false;

					// 把特效绑定
					if( pAoePointEffectContainer )
					{
						pInstance->pMaster = pAoePointEffectContainer->GetEffectHelper( eEffectBindPart_Body );
					}
				}

				if( pAoePointEffectContainer )
				{
					pAoePointEffectContainer->ApplyEffect( 0, pEffect->GetID() );
				}
			}
		}
		else
		{
			pEffect->Release();
		}
		pEffect = NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	// 人物选择头顶特效
	//////////////////////////////////////////////////////////////////////////
	{

		CWSModelEffect* pEffect = MeNew CWSModelEffect;
		char filename[MAX_PATH] = {0};
		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s\\data\\effect\\common\\TargetTop.ini", GetRootPath());
		if( pEffect->LoadSetting( filename ) )
		{
			g_nLockTargetEffectID = GetEffectMgr()->RegisterEffect( pEffect );
			if( g_nLockTargetEffectID == -1 )
			{
				pEffect->Release();
			}
			else
			{
				g_nLockTargetEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();

				pEffect->m_dwBornTime = HQ_TimeGetTime();

				float fRadius = pEffect->m_fRadius;
				int nNum = pEffect->m_nNumInstance;

				CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( g_nLockTargetEffectContainerID );

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
					pInstance->bVisible = false;

					// 把特效绑定
					if( pEffectContainer )
					{
						pInstance->pMaster = pEffectContainer->GetEffectHelper( eEffectBindPart_Head );
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

	if( !GlobalTexture::m_bLoaded )
		GlobalTexture::LoadFromSlk( NULL );

	InitSpecularTex();

	GetDuelTips()->InitTips();
	theCountryTipInstance.InitTips();
	GetBattleFlag()->RegisterTexture();

	// 读取分解系统配置
	char szSplitFile[MAX_PATH] = {0};
	MeSprintf_s(szSplitFile,sizeof(szSplitFile)/sizeof(char) - 1, "%s\\data\\config\\SplitItem.config", GetRootPath());
	theItemSplitConfig.Load(szSplitFile);
}

void CHeroGame::EnterWorldLocalVersion()
{
	ChangeGameState( G_LOGIN,G_SELECT );
	GetPlayerMgr()->CreateMe( 0 );
	//added by zilong. 2011-02-21. ------------------------------
	//这里应该加入主角被创建后要初始化的一些内容（这些内容有可能在读取配置时因为主角不存在而没有被设置。）
	bool InitializeRoleProperty();
	//added by zilong. end. -------------------------------------

	MsgAckEnterWorld enter;
	InitCharInfo( enter );

	MexAnimCtrl::SetGameTime( HQ_TimeGetTime() );
    s_CUI_ID_FRAME_Select.SetVisable( false );
	s_CUI_ID_FRAME_Select.UnLoadUI();
	double mapid = 0;
	double posx, posy;

	MeXmlDocument LocalXMLSetting;
	bool bRet = LocalXMLSetting.LoadFile( 
		XML_GLOBALCONFIG_FILENAME );

	mapid = 0;
	posx = posy = 128.f;
	enter.charinfo.otherdataclient.pos.dwMapID = ZnFloat2Int(mapid);
	enter.charinfo.otherdataclient.pos.vPos.x = posx;
	enter.charinfo.otherdataclient.pos.vPos.y = posy;
	strcpy(enter.charinfo.baseinfo.aptotic.szCharacterName, "单机");
	enter.charinfo.baseinfo.aptotic.ucSex = 0;

	if( bRet )
	{
		//load root
		MeXmlElement* pRoot = LocalXMLSetting.FirstChildElement( 
			XML_GLOBALCONFIG_ROOT_NAME );
		if( !pRoot )
			return ;			

		//load settings	
		MeXmlElement* pLocalVersionRoot = pRoot->FirstChildElement( "LocalVersionSetting" ); 
		if( pLocalVersionRoot )
		{
			pLocalVersionRoot->QueryDoubleAttribute( "SceneID", &mapid );
			pLocalVersionRoot->QueryDoubleAttribute( "PosX", &posx );
			pLocalVersionRoot->QueryDoubleAttribute( "PosY", &posy );
		}
	}

	enter.charinfo.otherdataclient.pos.dwMapID = ZnFloat2Int(mapid);

	enter.charinfo.otherdataclient.pos.vPos.x = posx;
	enter.charinfo.otherdataclient.pos.vPos.y = posy;
	strcpy(enter.charinfo.baseinfo.aptotic.szCharacterName, "单机");

	// 男性角色
	enter.charinfo.baseinfo.aptotic.ucSex = 0;
	Color_Config.load();

	EnterWorld( &enter );
	s_CUI_ID_FRAME_MessageBox.SetVisable(false);
}

void CHeroGame::ResetServerShutDownPara()
{
	m_bServerShutDown = false;
	m_fServerShutDownCoundDown = 0.f;
	m_serverAndLocalOffsetTime = 0;
}

void CHeroGame::OnMsgServerShutdown(Msg *pMsg)
{
	CHECK_MSGLEN( pMsg, MsgShutdownServer);
	if( !pMsg )
		return;

	MsgShutdownServer *pShutdownMsg = (MsgShutdownServer*)pMsg;

	m_bServerShutDown = true;
	m_fServerShutDownCoundDown = (float)pShutdownMsg->delayTime;

	// 先按原始时间给提示
	char szBuf[256]={0};
	char szTime[64]={0};
	int minute = m_fServerShutDownCoundDown / 60;
	int second = m_fServerShutDownCoundDown - minute * 60;
	if( minute > 0 && second > 0 )
		MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%d%s%d%s", minute, theXmlString.GetString(eText_Title_Minute),
		second, theXmlString.GetString(eTimeUnit_Second));
	else if( minute > 0 )
		MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%d%s", minute, theXmlString.GetString(eText_Title_Minute));
	else if( second > 0 )
		MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%d%s", second, theXmlString.GetString(eTimeUnit_Second));

	MeSprintf_s(szBuf, sizeof(szBuf)/sizeof(char)-1, theXmlString.GetString(eText_ServerShutdown1), szTime);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, szBuf );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Bull_Broadcast, szBuf, 2, true );

	// 计算准确时间，用于倒计时
	__time64_t serverTime = pShutdownMsg->nowTime;
	__time64_t curTime;
	_time64(&curTime);
	__time64_t deltaTime = serverTime - curTime - m_serverAndLocalOffsetTime;
	struct tm tmDeltaTime;
	_localtime64_s(&tmDeltaTime, &deltaTime);
	m_fServerShutDownCoundDown -= tmDeltaTime.tm_min * 60 + tmDeltaTime.tm_sec;
	m_fServerShutDownCoundDown -= 2;	// 提前2秒
}

void CHeroGame::UpdateServerShutdownCountDown()
{
	if( !m_bServerShutDown )
		return;

	if( g_GameState != G_MAIN || isShowDisconnetMsg )
	{
		ResetServerShutDownPara();
		return;
	}

	float fLastCountDown = m_fServerShutDownCoundDown;
	m_fServerShutDownCoundDown -= GetFrameElapsedTime();
	if( m_fServerShutDownCoundDown <= 0.f )
	{
		ResetServerShutDownPara();
		// 主动断开链接
		if (thePlayerRole.GetTeamMemberNum() > 0)
		{
			s_CUI_ID_FRAME_Team.CheckChangeFollowState();
			MsgExitTeam ExitTeammsg;
			GettheNetworkInput().SendMsg( &ExitTeammsg );
		}

		MsgExit msg;
		GettheNetworkInput().SendMsg( &msg );
		GettheNetworkInput().CheckSendReq();

		// 弹对话框
		s_CUI_ID_FRAME_MessageBox.closeAll(false);
		char acErrorString[256] = {0};
		struct tm nowtime;
		GetNowTime(nowtime);
		MeSprintf_s( acErrorString, sizeof(acErrorString)/sizeof(char) -1, "%02d:%02d:%02d%s", nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec, theXmlString.GetString(eText_Disconnect) ); 
		s_CUI_ID_FRAME_MessageBox.Show(
			acErrorString,
			"",
			CUI_ID_FRAME_MessageBox::eTypeConfirm,
			true,
			CUI_ID_FRAME_ExitGame::BackToLogin );

		s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
		s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);

		isShowDisconnetMsg = true;

		//s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().WriteData();

		return;
	}

	char szBuf[256]={0};
	char szTime[64]={0};
	bool bShow = false;
	bool bBullShow = false;
	// 30分钟内（包括30分钟），每5分钟给聊天框提示和走马灯提示
	if( (int)(fLastCountDown/300) - (int)(m_fServerShutDownCoundDown/300) == 1 )
	{
		int minute = (int)(fLastCountDown/60);
		MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%d%s", minute, theXmlString.GetString(eText_Title_Minute));
		bShow = true;
		bBullShow = true;
	}
	else if( m_fServerShutDownCoundDown < 600 )	// <10分钟，每分钟提示，去除5分钟
	{
		if( (int)(fLastCountDown/60) - (int)(m_fServerShutDownCoundDown/60) == 1 )
		{
			int minute = (int)(fLastCountDown/60);
			if( minute != 5 )
			{
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%d%s", minute, theXmlString.GetString(eText_Title_Minute));
				bShow = true;
			}
		}
		else if( m_fServerShutDownCoundDown < 60 && m_fServerShutDownCoundDown > 0 )	//  <1分钟，每秒提示
		{
			if( (int)fLastCountDown - (int)m_fServerShutDownCoundDown >= 1 )
			{
				int second = (int)m_fServerShutDownCoundDown + 1;
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%d%s", second, theXmlString.GetString(eTimeUnit_Second));
				bShow = true;
			}
		}
	}

	if( bShow || bBullShow )
	{
		MeSprintf_s(szBuf, sizeof(szBuf)/sizeof(char)-1, theXmlString.GetString(eText_ServerShutdown1), szTime);
		if( bShow )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, szBuf );
		if( bBullShow )
		{
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Bull_Broadcast, szBuf, 2, true );
		}
	}
}

void GetNowTime(struct tm& nowtime)
{
	__time64_t ltime;
	_time64(&ltime);
	_localtime64_s(&nowtime, &ltime);
};

bool GetSubStringParam(const char* source, const char* substring, std::string& strRet)
{
	if( !source || !substring || source[0] == '\0' || substring[0] == '\0' )
		return false;

	std::string strCommand = source;
	std::string strTemp;

	size_t findpos = strCommand.find(substring);
	if (findpos != std::string::npos)
	{
		std::string type = strCommand.substr(findpos);
		size_t endpos = type.find(" ");
		if (endpos != std::string::npos)
			type = type.substr(0, endpos);
		strTemp = type.substr(strlen(substring));
#ifdef _DEBUG
		OutputDebugString(substring);
		OutputDebugString(strTemp.c_str());
		OutputDebugString("\n");
#endif
		strRet = strTemp;
		return true;
	}
	return false;
}

void RetrieveRegionServerIpPort(const char* lwrCmd)
{
	bool bGetRegion = false;
	bool bGetServer = false;
	bool bGetIP = false;
	bool bGetPort = false;
	std::string strRegion = "";
	std::string strServer = "";
	std::string strIP = "";
	std::string strPort = "";
	std::string strCommand = lwrCmd;
	std::string strTemp = "";
	std::wstring str;

	// 区
	bGetRegion = GetSubStringParam(lwrCmd, "-region:", strRegion);

	// 服
	bGetServer = GetSubStringParam(lwrCmd, "-server:", strServer);

	// IP
	bGetIP = GetSubStringParam(lwrCmd, "-ip:", strIP);

	// Port
	bGetPort = GetSubStringParam(lwrCmd, "-port:", strPort);

	if( bGetRegion && bGetServer && bGetIP && bGetPort )
	{
		s_CUI_ID_FRAME_LOGIN.SetRegionServerIPPort(strRegion.c_str(),strServer.c_str(),strIP.c_str(),strPort.c_str());
	}

	// 是否显示密保卡登录勾选，临时使用
	std::string strPP = "";
	bool bShowPwdProtect = GetSubStringParam(lwrCmd, "-pp:", strPP);
	if( strPP.length() > 0 && !strcmp( strPP.c_str(), "1" ) )
		s_CUI_ID_FRAME_LOGIN.SetPwdProtect(true);
	else
		s_CUI_ID_FRAME_LOGIN.SetPwdProtect(false);

	// 2.5D视角
	std::string strVS = "";
	bool bViewSet25D = true;//GetSubStringParam(lwrCmd, "-vs25", strVS);
	CUserData::Instance()->SetViewSet(!bViewSet25D);
}

void CHeroGame::GetMacAddr(std::string* address)
{
	if( !address )
		return;
	if( !m_bGetMacAddr )
	{
		GetMACAddressString( &m_strMacAddr );
		m_bGetMacAddr = true;
	}
	*address = m_strMacAddr;
}

void CHeroGame::RenderPlayerHitMeEffect()
{
	static int picId = -1;
	char filename[256] = {0};
	MeSprintf_s( filename, sizeof(filename)-1, "%s\\Data\\Ui\\Common\\Alarum.dds", GetRootPath() );

	RECT rcFrame;
	rcFrame.left = 0;
	rcFrame.right = SCREEN_WIDTH;
	rcFrame.top = 0;
	rcFrame.bottom = SCREEN_HEIGHT;

	RECT rcSrc;
	rcSrc.left = 2;
	rcSrc.right = rcSrc.left + 269;
	rcSrc.top = 308;
	rcSrc.bottom = rcSrc.top + 202;

	DWORD dwElapseTime = HQ_TimeGetTime() - thePlayerRole.m_dwPlayerHitMeAlphaStartTime;
	float fAlpha = fabs(sin(dwElapseTime * m_fPlayerHitMeEffectPlayerSpeedScale));
	DWORD dwColor = D3DCOLOR_ARGB((int)(fAlpha * 255), 255, 255, 255);

	if (dwElapseTime < m_dwPlayerHitMeEffectTotalTime)
	{
		theControlPictureManager.BitBlt( &picId,
			filename,
			&rcFrame, &rcSrc, dwColor );
	}
	else if (!thePlayerRole.IsFighting())
	{
		thePlayerRole.m_isPlayerHitMe = false;
	}
}

void CHeroGame::UpdateMouseCursor()
{
	theMouseManager.SetCanSetCursor(true);
	if( !g_b25DRoleMoveFollowMouse )
		if ( m_eStateMouseType > 0 && m_eStateMouseType < MouseManager::Type_Max )
		{
			theMouseManager.SetCursor( m_eStateMouseType );
		}
		else
		{
			theMouseManager.SetCursor( MouseManager::Type_Arrow );
		}
	else
		theMouseManager.SetCursor(MouseManager::Type_MoveFollowMouse);

	//根据角色类型 改变鼠标的cursor
	GameObjectId gcPlayerServerID = GetPlayerMgr()->GetMouseTargetPlayerSeverID();
	CPlayer* pSelPlayer = GetPlayerMgr()->FindByID( gcPlayerServerID );
	if( pSelPlayer && !g_bRotateEnable )
	{
		switch( pSelPlayer->GetCharType() )
		{
		case Object_Effect: //lyh鼠标移动到特效怪身上的改变逻辑
			{
				//1:不可攻击
				EFFECTCHARCONFIG _Config;
				if(theEffectCharConfig.FindEffectCharConfigBySkillID(_Config,pSelPlayer->GetEffectCharSkillID()))
				{
					theMouseManager.SetCursor( MouseManager::Type_Arrow );
					if (_Config.bCanBeAttack && !pSelPlayer->MasterIsMe())
					{
						theMouseManager.SetCursor( MouseManager::Type_Attack );
					}

				}else
				{
                   theMouseManager.SetCursor( MouseManager::Type_Arrow );
				}
				
			}
			break;
		case Object_Npc:
			{
				const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pSelPlayer->GetNpcID());
				if( pInfo && pInfo->_nType == eNT_Item )    // NPC是Item类型，则不显示选中头像
					theMouseManager.SetCursor( MouseManager::Type_NpcItem );
				else
				{
					if( GetPlayerMgr()->GetMe() && GetPlayerMgr()->GetMe()->canAttack( pSelPlayer ) )
						theMouseManager.SetCursor( MouseManager::Type_Attack );
					else if (pSelPlayer->IsDead() || (pSelPlayer->GetRealCountry() != 0 && GetPlayerMgr()->GetMe()->GetRealCountry() != pSelPlayer->GetRealCountry()))
					{
						theMouseManager.SetCursor( MouseManager::Type_Arrow );
					}
					else
						theMouseManager.SetCursor( MouseManager::Type_Dialog );
				}
			}
			break;
		case Object_Item:
			{
				if( pSelPlayer->m_bCanPick && pSelPlayer->IsItemDropDelayOver() )
					theMouseManager.SetCursor( MouseManager::Type_PickItem );
				else
					theMouseManager.SetCursor( MouseManager::Type_Arrow );
			}
			break;
		case Object_Player:
			if( pSelPlayer->GetID() == GetPlayerMgr()->GetLockPlayerID() )
			{
				if( GetPlayerMgr()->GetMe() && GetPlayerMgr()->GetMe()->canAttack( pSelPlayer ) )
					theMouseManager.SetCursor( MouseManager::Type_Attack );
				else
				{
					
					//lyh++ 组队的时候鼠标移到角色伸长还是组队光标 
					if (theMouseManager.GetCursor() == MouseManager::Type_Group)
					{
						theMouseManager.SetCursor( MouseManager::Type_Group );
					}else
					{
                      theMouseManager.SetCursor( MouseManager::Type_Arrow );
					}

					
				}
			}
			else
			{
				//lyh++ 组队的时候鼠标移到角色伸长还是组队光标 
				if (theMouseManager.GetCursor() == MouseManager::Type_Group)
				{
					theMouseManager.SetCursor( MouseManager::Type_Group );
				}else
				{
					theMouseManager.SetCursor( MouseManager::Type_LockTarget );
				}
				
				
			}
			break;
		case Object_Monster:
			if (thePlayerRole.GetInfluence() != CampDefine::NoneCamp)
			{
				if (thePlayerRole.GetInfluence() != pSelPlayer->GetInfluence())
				{
					CPlayer* pMaster = theHeroGame.GetPlayerMgr()->FindByID(pSelPlayer->GetMasterID());
					if (pMaster)
					{
						if (thePlayerRole.GetInfluence() != pMaster->GetInfluence())
						{
							theMouseManager.SetCursor( MouseManager::Type_Attack );
							break;
						}
						else
						{
							theMouseManager.SetCursor( MouseManager::Type_Arrow );
							break;
						}
					}
					else
					{
                        //lyh ++  如果怪物和自己是同一个阵营，则不能攻击
						if(pSelPlayer->GetRealCountry() != CountryDefine::Country_Init&&
							thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry != CountryDefine::Country_Init&&
							thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry ==pSelPlayer->GetRealCountry() )
						{
							theMouseManager.SetCursor( MouseManager::Type_Arrow );
						}
						else if ((pSelPlayer->GetTypeStatus() == MonsterDefine::StatusUnMoveNpc 
							    || pSelPlayer->GetTypeStatus() == MonsterDefine::StatusMoveNpc ))
						{
							theMouseManager.SetCursor( MouseManager::Type_Dialog );
						}else
						{
							theMouseManager.SetCursor( MouseManager::Type_Attack );
						}
						break;
					}
				}
				else
				{
					theMouseManager.SetCursor( MouseManager::Type_Arrow );
					break;
				}
			}
			
			if( pSelPlayer->IsMonsterType(eMT_Herb)  )
			{
				theMouseManager.SetCursor( MouseManager::Type_CollectHerb );
			}
			else if ( pSelPlayer->IsMonsterType(eMT_Mine) )
			{
				theMouseManager.SetCursor( MouseManager::Type_CollectMine );
			}
            // 增加捕虫         added by zhuomeng.hu		[11/9/2010]
            else if( pSelPlayer->IsMonsterType( eMT_Insect )  )
            {
                theMouseManager.SetCursor( MouseManager::Type_PickItem );
            }
			else if( pSelPlayer->IsMonsterType(eMT_Treasure)  )
			{
				theMouseManager.SetCursor( MouseManager::Type_Pick );
			}
			else if ( pSelPlayer->IsMonsterType(eMT_Mount) )
			{
				theMouseManager.SetCursor( MouseManager::Type_CollectMount );
			}
			else if( pSelPlayer->IsDisableCollection()  )
			{
			}
			else if( pSelPlayer->IsMonsterType(eMT_Building)   )
			{
				theMouseManager.SetCursor( MouseManager::Type_Arrow );
			}
			else if( pSelPlayer->IsMonsterType(eMT_Mount)   )
			{
				theMouseManager.SetCursor( MouseManager::Type_CollectMount );
			}
			else
			{
				if( pSelPlayer->IsMonster() || pSelPlayer->GetID() == GetPlayerMgr()->GetLockPlayerID() ) //要求monster鼠标移动上去就是显示可攻击鼠标
				{
					if( pSelPlayer->HaveMaster() && pSelPlayer->GetMasterID() > -1 )
					{
						if( pSelPlayer->MasterIsMe() )
							theMouseManager.SetCursor( MouseManager::Type_Arrow );
						else
						{
							CPlayer* pTargetMaster = theHeroGame.GetPlayerMgr()->FindByID(pSelPlayer->GetMasterID());
							if( pTargetMaster && theHeroGame.GetPlayerMgr()->GetMe() &&
								theHeroGame.GetPlayerMgr()->GetMe()->canAttack(pTargetMaster) )
							{
								theMouseManager.SetCursor( MouseManager::Type_Attack );
							}
							else
								theMouseManager.SetCursor( MouseManager::Type_Arrow );
						}
					}
					else
					{
						//lyh ++  如果怪物和自己是同一个阵营，则不能攻击
						if(pSelPlayer->GetRealCountry() != CountryDefine::Country_Init&&
							thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry != CountryDefine::Country_Init&&
							thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry ==pSelPlayer->GetRealCountry())
							theMouseManager.SetCursor( MouseManager::Type_Arrow );
						else if ((pSelPlayer->GetTypeStatus() == MonsterDefine::StatusUnMoveNpc 
							|| pSelPlayer->GetTypeStatus() == MonsterDefine::StatusMoveNpc ))
						{
							theMouseManager.SetCursor( MouseManager::Type_Dialog );
						}else
						{
                         theMouseManager.SetCursor( MouseManager::Type_Attack );
						}
					
							
					}
				}
				else
				{
					theMouseManager.SetCursor( MouseManager::Type_LockTarget );
				}
			}
			break;
		}
	}
}

void CHeroGame::UpdateGetPhyMemoryCD()
{
	if( m_iGetPhyMemoryCD > 0 )
		m_iGetPhyMemoryCD -= (int)(GetFrameElapsedTime() * 1000);

	if( m_iGetPhyMemoryCD <= 0 )
	{
		m_iGetPhyMemoryCD = 0;
	}
}

SIZE_T CHeroGame::GetAvailPhyMemory()
{
	if( m_iGetPhyMemoryCD <= 0 )
	{
		m_iGetPhyMemoryCD = 3000;	// 3秒获取一次可用物理内存
		MEMORYSTATUS M;
		GlobalMemoryStatus(&M);
		m_dwAvailPhyMemory = M.dwAvailPhys;
	}

	return m_dwAvailPhyMemory;
}

void CHeroGame::LoadTaskDataProc()
{
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载任务数据开始", GetCurrentThreadId() );
    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Task, 0.0f );
    // 任务数据只加载一次
    char filename[MAX_PATH] = {0};
    MeSprintf_s( filename, sizeof(filename)/sizeof(char) -1, "%s\\Data\\Quest\\Client", GetRootPath());
 //  theXmlString.LoadStringPath(filename,false,false,true);//g_DirectReadInPackage,true);放到QuestInfo::Instance().LoadQuest
    MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s\\Data\\Quest", GetRootPath());
    QuestInfo::Instance().LoadQuest(filename,false);//g_DirectReadInPackage);

    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Task, 1.0f );
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载任务数据结束", GetCurrentThreadId() );
}

void CHeroGame::LoadEffectProc()
{
    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Effect, 0.0f );
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      特效配置加载开始", GetCurrentThreadId() );
    CWSModelEffectReader::PreLoadWSModelEffectSetting( false );//g_DirectReadInPackage );
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      特效配置加载结束", GetCurrentThreadId() );

    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Effect, 0.5f );

    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载 GlobalData 开始", GetCurrentThreadId() );
    if( !g_bGlobalDataLoaded )
    {
        theHeroGame.LoadGlobalData();
        g_bGlobalDataLoaded = TRUE;
    }
    s_CUI_ID_FRAME_LoadSplash.SetThreadLoadRate( CUI_ID_FRAME_LoadSplash::Thread_Effect, 1.0f );
    LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      加载 GlobalData 结束", GetCurrentThreadId() );
}

bool CHeroGame::InitializeRoleProperty(void)
{
	//初始化是否显示头盔的标志。
	//由于在游戏初始化读取配置时，在设置是否显示头盔的接口中，如果主角没有被创建，则在客户端不设置该标志，
	//所以此处重新设置该标志。
/*	{
		//该类只是为了导出父类的SetShowHelmet(unsigned int uiValue)接口。
		class GameSetting_Helper: public GameSetting
		{
		public:
			void SetShowHelmet(void)
			{
				GameSetting::SetShowHelmet(GetLevel(GameSetting::eGSC_SHOWHELMET));
			}
		};

		GameSetting_Helper *gameSettingHelper = (GameSetting_Helper *)GameSetting::Instance();
		gameSettingHelper->SetShowHelmet();
	}
*/

	//added by zilong. 2011-03-11. ---------------------------------
	CPlayer* me = theHeroGame.GetPlayerMgr()->GetMe();
	if( me )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_SHOWHELMET, me->IsShowHelmet());
		GameSetting::Instance()->CommitChanges(GameSetting::eGSC_SHOWHELMET);
	}
	else
	{
		assert(false);
	}
	//added by zilong. end. ----------------------------------------

	return true;
}

void CHeroGame::RenderCornerOverlay()
{
	static bool s_bLoaded = false;
	static short s_stId = -1;
	static int s_nScreenWidth = 0;
	static int s_nScreenHeight = 0;
	/// 拼出四个角，颠倒uv, 12个顶点
	static CBaseGraphics::UVVertex2D s_akVertex[24];

	if( s_nScreenWidth != SCREEN_WIDTH ||
		s_nScreenHeight != SCREEN_HEIGHT )
	{
		s_nScreenWidth = SCREEN_WIDTH;
		s_nScreenHeight = SCREEN_HEIGHT;

		// 左上
		s_akVertex[0].p = D3DXVECTOR4( 0, 0, 0, 1 );
		s_akVertex[0].u = 0;
		s_akVertex[0].v = 0;
		s_akVertex[0].color = 0xffffffff;

		s_akVertex[1].p = D3DXVECTOR4( 0, SCREEN_HEIGHT / 2 , 0, 1 );
		s_akVertex[1].u = 0;
		s_akVertex[1].v = 1;
		s_akVertex[1].color = 0xffffffff;

		s_akVertex[2].p = D3DXVECTOR4( SCREEN_WIDTH / 2, 0, 0, 1 );
		s_akVertex[2].u = 1;
		s_akVertex[2].v = 0;
		s_akVertex[2].color = 0xffffffff;

		s_akVertex[3].p = D3DXVECTOR4( SCREEN_WIDTH / 2, 0, 0, 1 );
		s_akVertex[3].u = 1;
		s_akVertex[3].v = 0;
		s_akVertex[3].color = 0xffffffff;

		s_akVertex[4].p = D3DXVECTOR4( 0, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[4].u = 0;
		s_akVertex[4].v = 1;
		s_akVertex[4].color = 0xffffffff;

		s_akVertex[5].p = D3DXVECTOR4( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[5].u = 1;
		s_akVertex[5].v = 1;
		s_akVertex[5].color = 0xffffffff;

		// 右上
		s_akVertex[6].p = D3DXVECTOR4( SCREEN_WIDTH / 2, 0, 0, 1 );
		s_akVertex[6].u = 1;
		s_akVertex[6].v = 0;
		s_akVertex[6].color = 0xffffffff;

		s_akVertex[7].p = D3DXVECTOR4( SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[7].u = 0;
		s_akVertex[7].v = 1;
		s_akVertex[7].color = 0xffffffff;

		s_akVertex[8].p = D3DXVECTOR4( SCREEN_WIDTH, 0, 0, 1 );
		s_akVertex[8].u = 0;
		s_akVertex[8].v = 0;
		s_akVertex[8].color = 0xffffffff;

		s_akVertex[9].p = D3DXVECTOR4( SCREEN_WIDTH / 2, 0, 0, 1 );
		s_akVertex[9].u = 1;
		s_akVertex[9].v = 0;
		s_akVertex[9].color = 0xffffffff;

		s_akVertex[10].p = D3DXVECTOR4( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[10].u = 1;
		s_akVertex[10].v = 1;
		s_akVertex[10].color = 0xffffffff;

		s_akVertex[11].p = D3DXVECTOR4( SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[11].u = 0;
		s_akVertex[11].v = 1;
		s_akVertex[11].color = 0xffffffff;

		// 左下
		s_akVertex[12].p = D3DXVECTOR4( 0, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[12].u = 1;
		s_akVertex[12].v = 0;
		s_akVertex[12].color = 0xffffffff;

		s_akVertex[13].p = D3DXVECTOR4( 0, SCREEN_HEIGHT, 0, 1 );
		s_akVertex[13].u = 0;
		s_akVertex[13].v = 0;
		s_akVertex[13].color = 0xffffffff;

		s_akVertex[14].p = D3DXVECTOR4( SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0, 1 );
		s_akVertex[14].u = 0;
		s_akVertex[14].v = 1;
		s_akVertex[14].color = 0xffffffff;

		s_akVertex[15].p = D3DXVECTOR4( 0, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[15].u = 1;
		s_akVertex[15].v = 0;
		s_akVertex[15].color = 0xffffffff;

		s_akVertex[16].p = D3DXVECTOR4( SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0, 1 );
		s_akVertex[16].u = 0;
		s_akVertex[16].v = 1;
		s_akVertex[16].color = 0xffffffff;

		s_akVertex[17].p = D3DXVECTOR4( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[17].u = 1;
		s_akVertex[17].v = 1;
		s_akVertex[17].color = 0xffffffff;

		// 右下
		s_akVertex[18].p = D3DXVECTOR4( SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[18].u = 1;
		s_akVertex[18].v = 0;
		s_akVertex[18].color = 0xffffffff;

		s_akVertex[19].p = D3DXVECTOR4( SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0, 1 );
		s_akVertex[19].u = 0;
		s_akVertex[19].v = 1;
		s_akVertex[19].color = 0xffffffff;

		s_akVertex[20].p = D3DXVECTOR4( SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1 );
		s_akVertex[20].u = 0;
		s_akVertex[20].v = 0;
		s_akVertex[20].color = 0xffffffff;

		s_akVertex[21].p = D3DXVECTOR4( SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[21].u = 1;
		s_akVertex[21].v = 0;
		s_akVertex[21].color = 0xffffffff;

		s_akVertex[22].p = D3DXVECTOR4( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 1 );
		s_akVertex[22].u = 1;
		s_akVertex[22].v = 1;
		s_akVertex[22].color = 0xffffffff;

		s_akVertex[23].p = D3DXVECTOR4( SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0, 1 );
		s_akVertex[23].u = 0;
		s_akVertex[23].v = 1;
		s_akVertex[23].color = 0xffffffff;
	}	
	
	if( !s_bLoaded )
	{
		s_bLoaded = true;

		// load
		s_stId = GetEngine()->GetTextureManager()->RegisterTexture( "./data/texture/BlackCorner.dds", false, true );

	}
	if( s_stId == -1 )
		return;

	IRenderer* r = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
	ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( s_stId );
	if( pTexture != NULL )
	{
		LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pTexture->GetData();
		if( !pd3dTexture )
			return;
		
		r->SetTexture(0, pd3dTexture);		
	}	

	r->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	r->SetRenderState(D3DRS_LIGHTING, FALSE);
	r->SetRenderState(D3DRS_FOGENABLE, FALSE);
	r->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	r->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	r->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	r->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	r->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE );
	r->SetRenderState(D3DRS_ZENABLE, FALSE);
	r->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

	r->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	r->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	r->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	r->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
	r->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	r->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	r->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	r->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	r->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0);

	r->Commit();

	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, 24, &s_akVertex, sizeof(CBaseGraphics::UVVertex2D) );

}
