#pragma once
#include "NetworkInput.h"
#include "Me3d\Include.h"
#include "d3dapp.h"
#include "client.h"
#include "UI/UIMgr.h"
#include "MeFoundation/MeQueriesInterlock.h"
#include "logmgr.h"
//#include "log4cpp/log4cpp_logger.h"
#include "MessageDefine.h"

#define ERROR_INFO_LOG	"ErrorInfo.log"
#define INFO_LOG		"Info.log"
#define MEMORY_LOG		"Memory.log"

#ifndef __GAMESTATE_DEF__
#define __GAMESTATE_DEF__

// 鼠标键盘Buffer
#define SAMPLE_BUFFER_SIZE  64      // arbitrary number of buffer elements
#define SAMPLEKEY_BUFFER_SIZE  16      // arbitrary number of buffer elements

class CPlayer;
class CPlayerMgr;
class CDuelTips;
class CBattleFlag;
class navigation;
class CWorld;
class swLuaScript;
class SwRender;
class CNdlDecalRes;

// 游戏状态
enum GAME_STATE
{
	G_GETSERVERIP,	//取服务器IP
	G_LOGIN,		// 登入
	G_PRODUCER,		// 制作都名单
	G_SELECT,		// 选择人物
    //G_SELECTWEAPON, 			deleted by zhuomeng.hu		[8/20/2010]
	G_CREATE,		// 创建人物
	G_MAIN,			// 主游戏
	G_LOADSPLASH    // 初始化全局数据和显示公司logo，放在G_LOGIN之前
};

#endif // __GAMESTATE_DEF__
	
extern void	ChangeGameState( const GAME_STATE gsCur, const GAME_STATE gsDes, bool bLoadUI = true );	// bLoadUI: SwitchGate时可能不需要加载UI
extern bool CheckMapCanPk(CPlayer* pSrcPlayer,CPlayer* pTargetPlayer);
class CNdlWorldPickerBase;

class CHeroGame:	public CMyD3DApplication
{
	friend class CPlayerMgr;

public: // static function
    static void SendCrashEmail( const char* pszDumpFileName,const char* pszDumpResult = NULL);  //pszDumResult Dump表示错误结果

	CHeroGame();
	virtual ~CHeroGame();

	// 创建窗口、设备初始化和恢复，销毁
	///////////////////////////////////
public:
	void					PreCreate();					// 设置路径
	virtual HRESULT			Create( HINSTANCE hInstance );	// 创建窗口，设备
	HWND					GetHWnd(){ return m_hWnd; }
	LPDIRECT3DDEVICE9		GetD3DDevice(){ return m_pd3dDevice; }
	void					OnSizeWindow( WPARAM wParam ,LPARAM lParam );
	bool					IsWindowActive() { return isActive; }	// 窗口激活状态
protected:
	virtual HRESULT			DeleteDeviceObjects();
	virtual HRESULT			OneTimeSceneInit();
	virtual HRESULT			InitDeviceObjects();
	virtual HRESULT			InvalidateDeviceObjects();
	virtual HRESULT 		RestoreDeviceObjects();
	virtual LRESULT			MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	//HRESULT				FinalCleanup();
	bool					isActive;

	// 硬件相关
public:
	void					GetMacAddr(std::string* address);	// 记录mac地址
	void					SetSlowCPU(unsigned short slow) { m_ustSlowCPU = slow; }
	void					CloseLauncher();					// 显示Splash后通知Launcher关闭
	SIZE_T					GetAvailPhyMemory();
protected:
	void					SlowCPU();							// 降低CPU占用率
	void					UpdateGetPhyMemoryCD();				// 每帧更新CD，CD为0时不取，等下次调GetAvailPhyMemory才取
	unsigned short			m_ustSlowCPU;
	bool					m_bGetMacAddr;
	std::string				m_strMacAddr;
	SIZE_T					m_dwAvailPhyMemory;					// 可用物理内存，Byte
	int						m_iGetPhyMemoryCD;


	// 游戏状态管理
	///////////////////////////////////
protected:
	virtual HRESULT			ProcessCommond();				


	// 使用独立的输入管理
	///////////////////////////////////
protected:
	HRESULT					InitDirectInput( HWND hWnd );
	void					FreeDirectInput();
	BOOL					ProcessInput( DWORD dwTime );
	void					ProcessMouseInput();
	void					ProcessKeyInput();
public:
	// 键盘输入，从DirectInput读取
	struct KeyChangeData
	{
		short				nKeyIndex;	// 键值
		BOOL				bPressed;	// 按下/释放
	};
	void					UpdateKeyState();
	BOOL					GetKeyState(int nKey) { return m_CurrKeyStates[nKey]; }
	void					SetDefaultMouseSpeed(int speed) { m_iDefaultMouseSpeed = speed; }
protected:
	int						m_iDefaultMouseSpeed;							// 鼠标默认速度
	bool					OnProcessMouseEvent( HWND hWnd, UINT uMsg , bool MouseLButtonPress );
	BOOL					m_LastKeyStates[256];							// 上一帧键按下状态, TRUE: 按下状态; FALSE:释放状态
	BOOL					m_CurrKeyStates[256];							// 当前帧键按下状态, TRUE: 按下状态; FALSE:释放状态
	KeyChangeData			m_CurrKeyChangeList[SAMPLEKEY_BUFFER_SIZE];		// 当前帧键按下/释放时间
	short					m_nCurrKeyChangeNum;

	typedef MeQueriesInterlock<2> NextQueriesInterlock;
	NextQueriesInterlock*		m_pQueriesInterlock;


	// 木马查杀
	///////////////////////////////////
protected:
	bool					AntiProcess(DWORD dwTime);
	DWORD					m_checkTime;


	// 处理网络消息
	///////////////////////////////////
public:
	void					EnterWorld(MsgAckEnterWorld*);					// 从选人界面进入游戏
protected:
	virtual void			UpdateNet();
	void					UpdateMsg(void);

	
	void					CaculateNetSreamLog();							// 调试信息，计算网络流量
	void					UpdateNetStreamLog( int& nLine );
	bool					m_bStartCaculateNetStream;
public:
	void					SetStartCaculateNetStream(bool bFlag) { m_bStartCaculateNetStream = bFlag; }
	bool					GetStartCaculateNetStream() { return m_bStartCaculateNetStream; }
	void					ProcessSwitchGateMsg(Msg* pMsg);
	void					JumpToWorldFromTransport(int nMapId, int nTargetId);// 走传送门切地图
	void					DisConnect();

	void					EnterWorldLocalVersion();						// 单机版本enterworld

	void					LoadGlobalData();								// 加载global特效，在EnterWorld函数主线程调用

	// 多线程
	///////////////////////////////////
public:
	BOOL					LoadLand( int iLandID, int nMeX, int nMeY );	// 多线程加载地图


	// Splash多线程初始化游戏数据
	///////////////////////////////////
public:
	HRESULT					InitGameInThread();								// 多线程初始化游戏
	void					LoadUIIcons();									// 加载ICON代码没有多线程保护，放在主线程加载
	virtual BOOL			LoadFxShader();

public:
	static void				LoadRoleSklProc();									// 人物动作加载线程回调
    static void             LoadConfigProc();                                   // 读表线程回调
    static void             LoadTaskDataProc();                                 // 任务线程回调
    static void             LoadEffectProc();                                   // 特效线程回调

	//added by zilong. 2011-02-21. ------------------------------
	//这里应该加入主角被创建后要初始化的一些内容（这些内容有可能在读取配置时因为主角不存在而没有被设置。）
	bool InitializeRoleProperty(void);
	//added by zilong. end. -------------------------------------

	// 游戏相关
	///////////////////////////////////
protected:
	virtual HRESULT			FrameMove();									// 每帧逻辑更新接口
	virtual HRESULT			Render();										// 每帧渲染接口
	BOOL					RunGameMain( DWORD dwTime );					// G_MAIN状态主循环更新
	void					RenderGameMain( DWORD dwTime );					// G_MAIN状态渲染入口
	BOOL					DisplayGameMain( DWORD dwTime );				// 进入游戏场景后渲染入口
	void					RenderBeforeGameMainUI( DWORD dwTime );			// 非G_MAIN状态渲染入口
	void					RenderCornerOverlay();							// 渲染四周暗角

public:
	void					SetUserName(const char* name) { if( name ) strncpy(m_szUserName, name, sizeof(m_szUserName)-1); }
	char*                   GetUserName(){return m_szUserName;}
protected:
	char					m_szUserName[256];								// 保留用户

	// 逻辑相关
	///////////////////////////////////
public:
	CPlayerMgr*				GetPlayerMgr(){ return m_pPlayerMgr; }			//可以独立出来作为SINGLETON 不必作为成员变量
	CDuelTips*				GetDuelTips() { return m_pDuelTips;}
	CBattleFlag*			GetBattleFlag() { return m_pBattleFlag;}
protected:
	CPlayerMgr*				m_pPlayerMgr;
	CDuelTips*				m_pDuelTips;
	CBattleFlag*			m_pBattleFlag;
	
	navigation*				_pNavigation;									// 导航模型

	bool					focusInUIEdit();								// 界面相关
	void					SetDlgVisable();								// 把需要直接显示的dlg显示出来

public:
	void					SwitchGate(/*bool _connect = true*/);									// 切服逻辑

	// 2.5D操作
	////////////////////////////////////
public:
	enum E25DMoveDirection			// 2.5D八个移动方向
	{
		EMD_NONE = 0,
		EMD_UP,
		EMD_DOWN,
		EMD_LEFT,
		EMD_RIGHT,
		EMD_AXEDIR = EMD_RIGHT,
		EMD_LEFT_UP,
		EMD_RIGHT_UP,
		EMD_LEFT_DOWN,
		EMD_RIGHT_DOWN
	};

	unsigned short			getshCur25Direction(){ return m_shCur25Direction; };
	void					setshCur25Direction( unsigned short dir ){ m_shCur25Direction = dir; }
protected:
	BOOL					Update25Direction();							// 2.5D视角，WASD按键信息
	unsigned short			m_shCur25Direction;								// 当前2.5D移动方向 //需要移动到wsCamera中


	// 渲染相关
	////////////////////////////////////
public:
	SwRender*				GetSwRender(){ return m_swRender; }				// 渲染类接口
	void					ChangeGraphicsLevel(int level);					// 设置渲染级别
	void					SetLightHeight(float height) { m_fLightHeight = height; }
	void					SetProjHeight(float height) { m_fProjHeight = height; }
protected:
	SwRender*				m_swRender;
	float					m_fLightHeight;
	float					m_fProjHeight;

	// 2D全屏特效
	// 被玩家攻击屏幕特效
public:
	void					SetPlayerHitMeEffectPlayerSpeedScale( float scale ) { if(scale > 0) m_fPlayerHitMeEffectPlayerSpeedScale = scale; }
	void					SetPlayerHitMeEffectTotalTime( DWORD time ) { m_dwPlayerHitMeEffectTotalTime = time; }

public:
	void					SetStateCursor( MouseManager::E_CursorType type ){ m_eStateMouseType = type; }
protected:
	void					RenderPlayerHitMeEffect();
	float					m_fPlayerHitMeEffectPlayerSpeedScale;			// 闪烁频率
	DWORD					m_dwPlayerHitMeEffectTotalTime;					// 特效显示时间，毫秒
	void					UpdateMouseCursor();							// 更新鼠标icon显示

	MouseManager::E_CursorType	m_eStateMouseType;							// 鼠标处于提示某种状态，比如说处于邀请或者请求组队状态就会设置这个cursor的值

	// 地图相关
	////////////////////////////////////
public:
	CWorld*					GetWorld(){ return m_world; }
	int						GetLandID(){ return m_iLandID; }
	BOOL					PickFromTerrain( float &x, float &y );			// 地图取高度
	BOOL					GetMousePickXY( float &x, float &y, int &nMouseXOffset, int &nMouseYOffset );
protected:
	CWorld*					m_world;										// 地图数据类
	int						m_iLandID;										// 当前地图ID
	int						m_nLastLandId;									// 初始值-1，用于判断是否第一次进入地图
	CNdlWorldPickerBase*	m_worldPick;									// 地图取高度

	
	// 人物动作
public:
	enum
	{
		eMaxSaveRoleID = 40
	};
	void					UnLoadRoleSkl();								// 释放
	static INT  			m_nSaveRoleID[eMaxSaveRoleID];


	// 相机控制
	////////////////////////////////////
public:
	void					OnChangeControlType(const bool bMouz_Camera);	// 相机
protected:
	bool					m_bZRotateStarted;
	DWORD					m_bZRotateStartTime;
	bool					m_bXRotateStarted;
	DWORD					m_bXRotateStartTime;
	float					GetZRotatePerStamp( int nData, DWORD dwStampTime );	// 相机旋转
	float					GetXRotatePerStamp( int nData, DWORD dwStampTime );


	// 声音
	////////////////////////////////////
public:
	void					SetMusicVolume(float volume) { m_fMusicVolume = volume; }
	void					SetSoundVolume(float volume) { m_fSoundVolume = volume; }
protected:
	float					m_fMusicVolume;
	float					m_fSoundVolume;

	
	// 游戏内停服倒计时
	////////////////////////////////////
public:
	void					ResetServerShutDownPara();
	__time64_t				GetServerAndLocalOffsetTime() {return m_serverAndLocalOffsetTime;}
	void					SetServerAndLocalOffsetTime(__time64_t time){ m_serverAndLocalOffsetTime = time; }
	void					OnMsgServerShutdown(Msg *pMsg);
protected:
	void					UpdateServerShutdownCountDown();
	bool					m_bServerShutDown;								// 停服标记
	float					m_fServerShutDownCoundDown;						// 停服倒计时，秒
	__time64_t				m_serverAndLocalOffsetTime;

public: //调试信息
	//记录最高耗时
	DWORD                   m_PlayerMaxCost; //角色最高耗时
	DWORD                   m_SceneUpdateMaxCost; //场景更新最高耗时
	DWORD                   m_SceneRenderMaxCost; 
	DWORD                   m_TerrainRenderMaxCost;
	DWORD                   m_DoodadRenderMaxCost; //植被最高耗时
	DWORD                   m_LiquidRenderMaxCost; //流体最高耗时
	DWORD                   m_EffectRenderMaxCost; //特效最高耗时
	DWORD                   m_UIRenderMaxCost;     //ui最高耗时
	DWORD                   m_PostProcessMaxCost; 

	// 调试信息
	////////////////////////////////////
protected:
	DWORD					m_UIUpdateCost;
	DWORD					m_UIRenderCost;
	DWORD					m_PlayerUpdateCost;
	DWORD					m_PlayerRenderCost;
	DWORD					m_LiquidRenderCost;
	DWORD					m_OneFrameDisplayCost;
	DWORD					m_FrameMoveCost;
	DWORD					m_testCost;
	DWORD					m_NetCostMax;
	DWORD					m_TotalFrame;
	DWORD					m_UIRenderTotal;
	DWORD					m_PlayerRenderTotal;
	DWORD					m_GrassRenderTotal;
	DWORD					m_ChunkRenderTotal;
	DWORD					m_LiquidRenderTotal;
	DWORD					m_ModelRenderTotal;
	DWORD					m_AllRenderTotal;
	DWORD                   m_PostProcessCost; //后处理时间




	// 无用
	///////////////////////////////////
#if 0
protected:
	//取服务器IP
	BOOL					RunGetServerIP(void);
	void					ProcessCmd( const char*szCmd );
	void					SetLoginWait(bool bLoginWait = false)		{ m_bLoginWait = bLoginWait; }
	bool					m_bLoginWait;

	void					leftRotate();
	void					rightRotate();
	void					forward();
	void					leftwalk();
	void					rightwalk();
	void					backward();
	swLuaScript*			m_Lua;
	char*					m_LoginName;
	char*					m_LoginPWD;
	enum
	{
		CategoricalLogin = 0,
		SelectServer = 1,
		e_max
	};
	int						m_RunType;
	bool           			m_bIsSendCheck;
	bool					m_bMapChangedJustNow;
	BOOL					DeCodeVfsFile();
	bool					SaveVfsTemp(unsigned char vfs[],unsigned long vfslength);
	unsigned char*			GetVfs();
	HANDLE					m_hLoadWnd;
	static	DWORD WINAPI	ConnectToGateFunc(LPVOID lpParam);//连接到Gate的线程
	HANDLE					m_hConnectToGateThread; //thread handle
	static void				OnCancelConnect(const bool bPressYes, void *pData);
	LPDIRECT3DSURFACE9		m_pBackBuffer;
	LPDIRECT3DTEXTURE9		m_pBackTexture;
	LPDIRECT3DSURFACE9		m_pBackFace;

	// 获取装备随机属性评估值，返回值为EItemLevel枚举类型
	unsigned short GetEquipRandomEvaluate(unsigned short usItemID, unsigned short usEvalType, const std::vector<unsigned short>& vectorRandID);
#endif

	//
public:
	BOOL	StartConnectToGate( const char *szDstIP, int iPort );
	char	m_szDstIP[256]; //保留目标服务器的ip
	int		m_iPort;		 //保留目标服务的端口

	//bool	isShowDisconnetMsg;
#ifdef USE_OLD_LOGIN
public:
	//BOOL	StartConnectToGate( const char *szDstIP, int iPort );
	bool	login2LoginServer( const char *szUserName, const char *szPassword, int isSoftKeyboardChar,bool isForced);
	char*	m_loginCheckKey;
	//char	m_szDstIP[256]; //保留目标服务器的ip
	//int		m_iPort;		 //保留目标服务的端口
	char	m_szPassword[256];//
#endif

};

class FGameState
{
public:
	BOOL	bRenderMiniMap;
	BOOL	RenderGroup;
	BOOL	UseDefPart;
	
	FGameState();

	void	Init();
	BOOL	DebugCommand( const char* pszCommand );
};

extern FGameState	GameState;
extern CHeroGame theHeroGame;
extern void PauseThread();
extern void UnpauseThread();