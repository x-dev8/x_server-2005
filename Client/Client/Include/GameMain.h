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

// ������Buffer
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

// ��Ϸ״̬
enum GAME_STATE
{
	G_GETSERVERIP,	//ȡ������IP
	G_LOGIN,		// ����
	G_PRODUCER,		// ����������
	G_SELECT,		// ѡ������
    //G_SELECTWEAPON, 			deleted by zhuomeng.hu		[8/20/2010]
	G_CREATE,		// ��������
	G_MAIN,			// ����Ϸ
	G_LOADSPLASH    // ��ʼ��ȫ�����ݺ���ʾ��˾logo������G_LOGIN֮ǰ
};

#endif // __GAMESTATE_DEF__
	
extern void	ChangeGameState( const GAME_STATE gsCur, const GAME_STATE gsDes, bool bLoadUI = true );	// bLoadUI: SwitchGateʱ���ܲ���Ҫ����UI
extern bool CheckMapCanPk(CPlayer* pSrcPlayer,CPlayer* pTargetPlayer);
class CNdlWorldPickerBase;

class CHeroGame:	public CMyD3DApplication
{
	friend class CPlayerMgr;

public: // static function
    static void SendCrashEmail( const char* pszDumpFileName,const char* pszDumpResult = NULL);  //pszDumResult Dump��ʾ������

	CHeroGame();
	virtual ~CHeroGame();

	// �������ڡ��豸��ʼ���ͻָ�������
	///////////////////////////////////
public:
	void					PreCreate();					// ����·��
	virtual HRESULT			Create( HINSTANCE hInstance );	// �������ڣ��豸
	HWND					GetHWnd(){ return m_hWnd; }
	LPDIRECT3DDEVICE9		GetD3DDevice(){ return m_pd3dDevice; }
	void					OnSizeWindow( WPARAM wParam ,LPARAM lParam );
	bool					IsWindowActive() { return isActive; }	// ���ڼ���״̬
protected:
	virtual HRESULT			DeleteDeviceObjects();
	virtual HRESULT			OneTimeSceneInit();
	virtual HRESULT			InitDeviceObjects();
	virtual HRESULT			InvalidateDeviceObjects();
	virtual HRESULT 		RestoreDeviceObjects();
	virtual LRESULT			MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	//HRESULT				FinalCleanup();
	bool					isActive;

	// Ӳ�����
public:
	void					GetMacAddr(std::string* address);	// ��¼mac��ַ
	void					SetSlowCPU(unsigned short slow) { m_ustSlowCPU = slow; }
	void					CloseLauncher();					// ��ʾSplash��֪ͨLauncher�ر�
	SIZE_T					GetAvailPhyMemory();
protected:
	void					SlowCPU();							// ����CPUռ����
	void					UpdateGetPhyMemoryCD();				// ÿ֡����CD��CDΪ0ʱ��ȡ�����´ε�GetAvailPhyMemory��ȡ
	unsigned short			m_ustSlowCPU;
	bool					m_bGetMacAddr;
	std::string				m_strMacAddr;
	SIZE_T					m_dwAvailPhyMemory;					// ���������ڴ棬Byte
	int						m_iGetPhyMemoryCD;


	// ��Ϸ״̬����
	///////////////////////////////////
protected:
	virtual HRESULT			ProcessCommond();				


	// ʹ�ö������������
	///////////////////////////////////
protected:
	HRESULT					InitDirectInput( HWND hWnd );
	void					FreeDirectInput();
	BOOL					ProcessInput( DWORD dwTime );
	void					ProcessMouseInput();
	void					ProcessKeyInput();
public:
	// �������룬��DirectInput��ȡ
	struct KeyChangeData
	{
		short				nKeyIndex;	// ��ֵ
		BOOL				bPressed;	// ����/�ͷ�
	};
	void					UpdateKeyState();
	BOOL					GetKeyState(int nKey) { return m_CurrKeyStates[nKey]; }
	void					SetDefaultMouseSpeed(int speed) { m_iDefaultMouseSpeed = speed; }
protected:
	int						m_iDefaultMouseSpeed;							// ���Ĭ���ٶ�
	bool					OnProcessMouseEvent( HWND hWnd, UINT uMsg , bool MouseLButtonPress );
	BOOL					m_LastKeyStates[256];							// ��һ֡������״̬, TRUE: ����״̬; FALSE:�ͷ�״̬
	BOOL					m_CurrKeyStates[256];							// ��ǰ֡������״̬, TRUE: ����״̬; FALSE:�ͷ�״̬
	KeyChangeData			m_CurrKeyChangeList[SAMPLEKEY_BUFFER_SIZE];		// ��ǰ֡������/�ͷ�ʱ��
	short					m_nCurrKeyChangeNum;

	typedef MeQueriesInterlock<2> NextQueriesInterlock;
	NextQueriesInterlock*		m_pQueriesInterlock;


	// ľ���ɱ
	///////////////////////////////////
protected:
	bool					AntiProcess(DWORD dwTime);
	DWORD					m_checkTime;


	// ����������Ϣ
	///////////////////////////////////
public:
	void					EnterWorld(MsgAckEnterWorld*);					// ��ѡ�˽��������Ϸ
protected:
	virtual void			UpdateNet();
	void					UpdateMsg(void);

	
	void					CaculateNetSreamLog();							// ������Ϣ��������������
	void					UpdateNetStreamLog( int& nLine );
	bool					m_bStartCaculateNetStream;
public:
	void					SetStartCaculateNetStream(bool bFlag) { m_bStartCaculateNetStream = bFlag; }
	bool					GetStartCaculateNetStream() { return m_bStartCaculateNetStream; }
	void					ProcessSwitchGateMsg(Msg* pMsg);
	void					JumpToWorldFromTransport(int nMapId, int nTargetId);// �ߴ������е�ͼ
	void					DisConnect();

	void					EnterWorldLocalVersion();						// �����汾enterworld

	void					LoadGlobalData();								// ����global��Ч����EnterWorld�������̵߳���

	// ���߳�
	///////////////////////////////////
public:
	BOOL					LoadLand( int iLandID, int nMeX, int nMeY );	// ���̼߳��ص�ͼ


	// Splash���̳߳�ʼ����Ϸ����
	///////////////////////////////////
public:
	HRESULT					InitGameInThread();								// ���̳߳�ʼ����Ϸ
	void					LoadUIIcons();									// ����ICON����û�ж��̱߳������������̼߳���
	virtual BOOL			LoadFxShader();

public:
	static void				LoadRoleSklProc();									// ���ﶯ�������̻߳ص�
    static void             LoadConfigProc();                                   // �����̻߳ص�
    static void             LoadTaskDataProc();                                 // �����̻߳ص�
    static void             LoadEffectProc();                                   // ��Ч�̻߳ص�

	//added by zilong. 2011-02-21. ------------------------------
	//����Ӧ�ü������Ǳ�������Ҫ��ʼ����һЩ���ݣ���Щ�����п����ڶ�ȡ����ʱ��Ϊ���ǲ����ڶ�û�б����á���
	bool InitializeRoleProperty(void);
	//added by zilong. end. -------------------------------------

	// ��Ϸ���
	///////////////////////////////////
protected:
	virtual HRESULT			FrameMove();									// ÿ֡�߼����½ӿ�
	virtual HRESULT			Render();										// ÿ֡��Ⱦ�ӿ�
	BOOL					RunGameMain( DWORD dwTime );					// G_MAIN״̬��ѭ������
	void					RenderGameMain( DWORD dwTime );					// G_MAIN״̬��Ⱦ���
	BOOL					DisplayGameMain( DWORD dwTime );				// ������Ϸ��������Ⱦ���
	void					RenderBeforeGameMainUI( DWORD dwTime );			// ��G_MAIN״̬��Ⱦ���
	void					RenderCornerOverlay();							// ��Ⱦ���ܰ���

public:
	void					SetUserName(const char* name) { if( name ) strncpy(m_szUserName, name, sizeof(m_szUserName)-1); }
	char*                   GetUserName(){return m_szUserName;}
protected:
	char					m_szUserName[256];								// �����û�

	// �߼����
	///////////////////////////////////
public:
	CPlayerMgr*				GetPlayerMgr(){ return m_pPlayerMgr; }			//���Զ���������ΪSINGLETON ������Ϊ��Ա����
	CDuelTips*				GetDuelTips() { return m_pDuelTips;}
	CBattleFlag*			GetBattleFlag() { return m_pBattleFlag;}
protected:
	CPlayerMgr*				m_pPlayerMgr;
	CDuelTips*				m_pDuelTips;
	CBattleFlag*			m_pBattleFlag;
	
	navigation*				_pNavigation;									// ����ģ��

	bool					focusInUIEdit();								// �������
	void					SetDlgVisable();								// ����Ҫֱ����ʾ��dlg��ʾ����

public:
	void					SwitchGate(/*bool _connect = true*/);									// �з��߼�

	// 2.5D����
	////////////////////////////////////
public:
	enum E25DMoveDirection			// 2.5D�˸��ƶ�����
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
	BOOL					Update25Direction();							// 2.5D�ӽǣ�WASD������Ϣ
	unsigned short			m_shCur25Direction;								// ��ǰ2.5D�ƶ����� //��Ҫ�ƶ���wsCamera��


	// ��Ⱦ���
	////////////////////////////////////
public:
	SwRender*				GetSwRender(){ return m_swRender; }				// ��Ⱦ��ӿ�
	void					ChangeGraphicsLevel(int level);					// ������Ⱦ����
	void					SetLightHeight(float height) { m_fLightHeight = height; }
	void					SetProjHeight(float height) { m_fProjHeight = height; }
protected:
	SwRender*				m_swRender;
	float					m_fLightHeight;
	float					m_fProjHeight;

	// 2Dȫ����Ч
	// ����ҹ�����Ļ��Ч
public:
	void					SetPlayerHitMeEffectPlayerSpeedScale( float scale ) { if(scale > 0) m_fPlayerHitMeEffectPlayerSpeedScale = scale; }
	void					SetPlayerHitMeEffectTotalTime( DWORD time ) { m_dwPlayerHitMeEffectTotalTime = time; }

public:
	void					SetStateCursor( MouseManager::E_CursorType type ){ m_eStateMouseType = type; }
protected:
	void					RenderPlayerHitMeEffect();
	float					m_fPlayerHitMeEffectPlayerSpeedScale;			// ��˸Ƶ��
	DWORD					m_dwPlayerHitMeEffectTotalTime;					// ��Ч��ʾʱ�䣬����
	void					UpdateMouseCursor();							// �������icon��ʾ

	MouseManager::E_CursorType	m_eStateMouseType;							// ��괦����ʾĳ��״̬������˵������������������״̬�ͻ��������cursor��ֵ

	// ��ͼ���
	////////////////////////////////////
public:
	CWorld*					GetWorld(){ return m_world; }
	int						GetLandID(){ return m_iLandID; }
	BOOL					PickFromTerrain( float &x, float &y );			// ��ͼȡ�߶�
	BOOL					GetMousePickXY( float &x, float &y, int &nMouseXOffset, int &nMouseYOffset );
protected:
	CWorld*					m_world;										// ��ͼ������
	int						m_iLandID;										// ��ǰ��ͼID
	int						m_nLastLandId;									// ��ʼֵ-1�������ж��Ƿ��һ�ν����ͼ
	CNdlWorldPickerBase*	m_worldPick;									// ��ͼȡ�߶�

	
	// ���ﶯ��
public:
	enum
	{
		eMaxSaveRoleID = 40
	};
	void					UnLoadRoleSkl();								// �ͷ�
	static INT  			m_nSaveRoleID[eMaxSaveRoleID];


	// �������
	////////////////////////////////////
public:
	void					OnChangeControlType(const bool bMouz_Camera);	// ���
protected:
	bool					m_bZRotateStarted;
	DWORD					m_bZRotateStartTime;
	bool					m_bXRotateStarted;
	DWORD					m_bXRotateStartTime;
	float					GetZRotatePerStamp( int nData, DWORD dwStampTime );	// �����ת
	float					GetXRotatePerStamp( int nData, DWORD dwStampTime );


	// ����
	////////////////////////////////////
public:
	void					SetMusicVolume(float volume) { m_fMusicVolume = volume; }
	void					SetSoundVolume(float volume) { m_fSoundVolume = volume; }
protected:
	float					m_fMusicVolume;
	float					m_fSoundVolume;

	
	// ��Ϸ��ͣ������ʱ
	////////////////////////////////////
public:
	void					ResetServerShutDownPara();
	__time64_t				GetServerAndLocalOffsetTime() {return m_serverAndLocalOffsetTime;}
	void					SetServerAndLocalOffsetTime(__time64_t time){ m_serverAndLocalOffsetTime = time; }
	void					OnMsgServerShutdown(Msg *pMsg);
protected:
	void					UpdateServerShutdownCountDown();
	bool					m_bServerShutDown;								// ͣ�����
	float					m_fServerShutDownCoundDown;						// ͣ������ʱ����
	__time64_t				m_serverAndLocalOffsetTime;

public: //������Ϣ
	//��¼��ߺ�ʱ
	DWORD                   m_PlayerMaxCost; //��ɫ��ߺ�ʱ
	DWORD                   m_SceneUpdateMaxCost; //����������ߺ�ʱ
	DWORD                   m_SceneRenderMaxCost; 
	DWORD                   m_TerrainRenderMaxCost;
	DWORD                   m_DoodadRenderMaxCost; //ֲ����ߺ�ʱ
	DWORD                   m_LiquidRenderMaxCost; //������ߺ�ʱ
	DWORD                   m_EffectRenderMaxCost; //��Ч��ߺ�ʱ
	DWORD                   m_UIRenderMaxCost;     //ui��ߺ�ʱ
	DWORD                   m_PostProcessMaxCost; 

	// ������Ϣ
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
	DWORD                   m_PostProcessCost; //����ʱ��




	// ����
	///////////////////////////////////
#if 0
protected:
	//ȡ������IP
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
	static	DWORD WINAPI	ConnectToGateFunc(LPVOID lpParam);//���ӵ�Gate���߳�
	HANDLE					m_hConnectToGateThread; //thread handle
	static void				OnCancelConnect(const bool bPressYes, void *pData);
	LPDIRECT3DSURFACE9		m_pBackBuffer;
	LPDIRECT3DTEXTURE9		m_pBackTexture;
	LPDIRECT3DSURFACE9		m_pBackFace;

	// ��ȡװ�������������ֵ������ֵΪEItemLevelö������
	unsigned short GetEquipRandomEvaluate(unsigned short usItemID, unsigned short usEvalType, const std::vector<unsigned short>& vectorRandID);
#endif

	//
public:
	BOOL	StartConnectToGate( const char *szDstIP, int iPort );
	char	m_szDstIP[256]; //����Ŀ���������ip
	int		m_iPort;		 //����Ŀ�����Ķ˿�

	//bool	isShowDisconnetMsg;
#ifdef USE_OLD_LOGIN
public:
	//BOOL	StartConnectToGate( const char *szDstIP, int iPort );
	bool	login2LoginServer( const char *szUserName, const char *szPassword, int isSoftKeyboardChar,bool isForced);
	char*	m_loginCheckKey;
	//char	m_szDstIP[256]; //����Ŀ���������ip
	//int		m_iPort;		 //����Ŀ�����Ķ˿�
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