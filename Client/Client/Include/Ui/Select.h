/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Select.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include "MessageDefine.h"
#include "Me3d/camera.h"
#include "Me3d/Model/MexAnimCtrl.h"

#ifndef ID_FRAME_SELECT
#define ID_FRAME_SELECT		"ID_FRAME_SELECT"
#endif  ID_FRAME_SELECT
#ifndef ID_BUTTON_CREATE
#define ID_BUTTON_CREATE		"ID_BUTTON_CREATE"
#endif  ID_BUTTON_CREATE
#ifndef ID_BUTTON_ENTER
#define ID_BUTTON_ENTER		"ID_BUTTON_ENTER"
#endif  ID_BUTTON_ENTER
#ifndef ID_BUTTON_DELETE
#define ID_BUTTON_DELETE		"ID_BUTTON_DELETE"
#endif  ID_BUTTON_DELETE
#ifndef ID_BUTTON_LEAVE
#define ID_BUTTON_LEAVE		"ID_BUTTON_LEAVE"
#endif  ID_BUTTON_LEAVE
#ifndef ID_TEXT_NAME
#define ID_TEXT_NAME		"ID_TEXT_NAME"
#endif  ID_TEXT_NAME
#ifndef ID_TEXT_LEVEL
#define ID_TEXT_LEVEL		"ID_TEXT_LEVEL"
#endif  ID_TEXT_LEVEL
#ifndef ID_TEXT_BIRTHDAY
#define ID_TEXT_BIRTHDAY		"ID_TEXT_BIRTHDAY"
#endif  ID_TEXT_BIRTHDAY
#ifndef ID_LIST_PLAYER
#define ID_LIST_PLAYER		"ID_LIST_PLAYER"
#endif  ID_LIST_PLAYER
#ifndef ID_TEXT_JOB
#define ID_TEXT_JOB		"ID_TEXT_JOB"
#endif ID_TEXT_JOB
#ifndef ID_CHECKBOX_KEYBD
#define ID_CHECKBOX_KEYBD		"ID_CHECKBOX_KEYBD"
#endif ID_CHECKBOX_KEYBD
#ifndef ID_CHECKBOX_MOUSE
#define ID_CHECKBOX_MOUSE		"ID_CHECKBOX_MOUSE"	
#endif ID_CHECKBOX_MOUSE
#ifndef ID_BUTTON_RESTORE
#define ID_BUTTON_RESTORE		"ID_BUTTON_RESTORE"
#endif  ID_BUTTON_RESTORE
#ifndef ID_BUTTON_Left
#define ID_BUTTON_Left		"ID_BUTTON_Left"
#endif  ID_BUTTON_Left
#ifndef ID_BUTTON_Right
#define ID_BUTTON_Right		"ID_BUTTON_Right"
#endif  ID_BUTTON_Right
#ifndef ID_TEXT_LastIP
#define ID_TEXT_LastIP		"ID_TEXT_LastIP"
#endif  ID_TEXT_LastIP
#ifndef ID_TEXT_LastTime
#define ID_TEXT_LastTime		"ID_TEXT_LastTime"
#endif  ID_TEXT_LastTime
#ifndef ID_TEXT_LastPlace
#define ID_TEXT_LastPlace		"ID_TEXT_LastPlace"
#endif  ID_TEXT_LastPlace

//added by zhuomeng.hu		[8/20/2010]
#ifndef ID_TEXT_COUNTRY
#define ID_TEXT_COUNTRY		"ID_TEXT_COUNTRY"
#endif  ID_TEXT_COUNTRY
#ifndef ID_TEXT_currectsever
#define ID_TEXT_currectsever		"ID_TEXT_currectsever"
#endif  ID_TEXT_currectsever
#ifndef ID_PICTURE_CreateBg1
#define ID_PICTURE_CreateBg1		"ID_PICTURE_CreateBg1"
#endif  ID_PICTURE_CreateBg1
#ifndef ID_PICTURE_CreateBg2
#define ID_PICTURE_CreateBg2		"ID_PICTURE_CreateBg2"
#endif  ID_PICTURE_CreateBg2
#ifndef ID_PICTURE_CreateBg3
#define ID_PICTURE_CreateBg3		"ID_PICTURE_CreateBg3"
#endif  ID_PICTURE_CreateBg3
#ifndef ID_PICTURE_CreateBg4
#define ID_PICTURE_CreateBg4		"ID_PICTURE_CreateBg4"
#endif  ID_PICTURE_CreateBg4
#ifndef ID_PICTURE_CreateBg5
#define ID_PICTURE_CreateBg5		"ID_PICTURE_CreateBg5"
#endif  ID_PICTURE_CreateBg5

#ifndef ID_BUTTON_PLAYER0
#define ID_BUTTON_PLAYER0		"ID_BUTTON_PLAYER0"
#endif  ID_BUTTON_PLAYER0
#ifndef ID_BUTTON_PLAYER1
#define ID_BUTTON_PLAYER1		"ID_BUTTON_PLAYER1"
#endif  ID_BUTTON_PLAYER1
#ifndef ID_BUTTON_PLAYER2
#define ID_BUTTON_PLAYER2		"ID_BUTTON_PLAYER2"
#endif  ID_BUTTON_PLAYER2
#ifndef ID_BUTTON_PLAYER3
#define ID_BUTTON_PLAYER3		"ID_BUTTON_PLAYER3"
#endif  ID_BUTTON_PLAYER3
#ifndef ID_BUTTON_PLAYER4
#define ID_BUTTON_PLAYER4		"ID_BUTTON_PLAYER4"
#endif  ID_BUTTON_PLAYER4
#ifndef ID_TEXT_JOB0
#define ID_TEXT_JOB0		"ID_TEXT_JOB0"
#endif  ID_TEXT_JOB0
#ifndef ID_TEXT_LEVEL0
#define ID_TEXT_LEVEL0		"ID_TEXT_LEVEL0"
#endif  ID_TEXT_LEVEL0
#ifndef ID_TEXT_Name0
#define ID_TEXT_Name0		"ID_TEXT_Name0"
#endif  ID_TEXT_Name0
#ifndef ID_TEXT_JOB1
#define ID_TEXT_JOB1		"ID_TEXT_JOB1"
#endif  ID_TEXT_JOB1
#ifndef ID_TEXT_LEVEL1
#define ID_TEXT_LEVEL1		"ID_TEXT_LEVEL1"
#endif  ID_TEXT_LEVEL1
#ifndef ID_TEXT_Name1
#define ID_TEXT_Name1		"ID_TEXT_Name1"
#endif  ID_TEXT_Name1
#ifndef ID_TEXT_LEVEL2
#define ID_TEXT_LEVEL2		"ID_TEXT_LEVEL2"
#endif  ID_TEXT_LEVEL2
#ifndef ID_TEXT_JOB2
#define ID_TEXT_JOB2		"ID_TEXT_JOB2"
#endif  ID_TEXT_JOB2
#ifndef ID_TEXT_Name2
#define ID_TEXT_Name2		"ID_TEXT_Name2"
#endif  ID_TEXT_Name2
#ifndef ID_TEXT_LEVEL3
#define ID_TEXT_LEVEL3		"ID_TEXT_LEVEL3"
#endif  ID_TEXT_LEVEL3
#ifndef ID_TEXT_JOB3
#define ID_TEXT_JOB3		"ID_TEXT_JOB3"
#endif  ID_TEXT_JOB3
#ifndef ID_TEXT_Name3
#define ID_TEXT_Name3		"ID_TEXT_Name3"
#endif  ID_TEXT_Name3
#ifndef ID_TEXT_LEVEL4
#define ID_TEXT_LEVEL4		"ID_TEXT_LEVEL4"
#endif  ID_TEXT_LEVEL4
#ifndef ID_TEXT_JOB4
#define ID_TEXT_JOB4		"ID_TEXT_JOB4"
#endif  ID_TEXT_JOB4
#ifndef ID_TEXT_Name4
#define ID_TEXT_Name4		"ID_TEXT_Name4"
#endif  ID_TEXT_Name4
#ifndef ID_PICTURE_Fan0
#define ID_PICTURE_Fan0		"ID_PICTURE_Fan0"
#endif  ID_PICTURE_Fan0
#ifndef ID_PICTURE_Bow0
#define ID_PICTURE_Bow0		"ID_PICTURE_Bow0"
#endif  ID_PICTURE_Bow0
#ifndef ID_PICTURE_Staff0
#define ID_PICTURE_Staff0		"ID_PICTURE_Staff0"
#endif  ID_PICTURE_Staff0
#ifndef ID_PICTURE_Sword0
#define ID_PICTURE_Sword0		"ID_PICTURE_Sword0"
#endif  ID_PICTURE_Sword0
#ifndef ID_PICTURE_Spear0
#define ID_PICTURE_Spear0		"ID_PICTURE_Spear0"
#endif  ID_PICTURE_Spear0
#ifndef ID_PICTURE_Fan1
#define ID_PICTURE_Fan1		"ID_PICTURE_Fan1"
#endif  ID_PICTURE_Fan1
#ifndef ID_PICTURE_Bow1
#define ID_PICTURE_Bow1		"ID_PICTURE_Bow1"
#endif  ID_PICTURE_Bow1
#ifndef ID_PICTURE_Staff1
#define ID_PICTURE_Staff1		"ID_PICTURE_Staff1"
#endif  ID_PICTURE_Staff1
#ifndef ID_PICTURE_Fan2
#define ID_PICTURE_Fan2		"ID_PICTURE_Fan2"
#endif  ID_PICTURE_Fan2
#ifndef ID_PICTURE_Sword1
#define ID_PICTURE_Sword1		"ID_PICTURE_Sword1"
#endif  ID_PICTURE_Sword1
#ifndef ID_PICTURE_Spear1
#define ID_PICTURE_Spear1		"ID_PICTURE_Spear1"
#endif  ID_PICTURE_Spear1
#ifndef ID_PICTURE_Spear2
#define ID_PICTURE_Spear2		"ID_PICTURE_Spear2"
#endif  ID_PICTURE_Spear2
#ifndef ID_PICTURE_Sword2
#define ID_PICTURE_Sword2		"ID_PICTURE_Sword2"
#endif  ID_PICTURE_Sword2
#ifndef ID_PICTURE_Staff2
#define ID_PICTURE_Staff2		"ID_PICTURE_Staff2"
#endif  ID_PICTURE_Staff2
#ifndef ID_PICTURE_Bow2
#define ID_PICTURE_Bow2		"ID_PICTURE_Bow2"
#endif  ID_PICTURE_Bow2
#ifndef ID_PICTURE_Fan3
#define ID_PICTURE_Fan3		"ID_PICTURE_Fan3"
#endif  ID_PICTURE_Fan3
#ifndef ID_PICTURE_Bow3
#define ID_PICTURE_Bow3		"ID_PICTURE_Bow3"
#endif  ID_PICTURE_Bow3
#ifndef ID_PICTURE_Staff3
#define ID_PICTURE_Staff3		"ID_PICTURE_Staff3"
#endif  ID_PICTURE_Staff3
#ifndef ID_PICTURE_Sword3
#define ID_PICTURE_Sword3		"ID_PICTURE_Sword3"
#endif  ID_PICTURE_Sword3
#ifndef ID_PICTURE_Spear3
#define ID_PICTURE_Spear3		"ID_PICTURE_Spear3"
#endif  ID_PICTURE_Spear3
#ifndef ID_PICTURE_Spear4
#define ID_PICTURE_Spear4		"ID_PICTURE_Spear4"
#endif  ID_PICTURE_Spear4
#ifndef ID_PICTURE_Sword4
#define ID_PICTURE_Sword4		"ID_PICTURE_Sword4"
#endif  ID_PICTURE_Sword4
#ifndef ID_PICTURE_Staff4
#define ID_PICTURE_Staff4		"ID_PICTURE_Staff4"
#endif  ID_PICTURE_Staff4
#ifndef ID_PICTURE_Bow4
#define ID_PICTURE_Bow4		"ID_PICTURE_Bow4"
#endif  ID_PICTURE_Bow4
#ifndef ID_PICTURE_Fan4
#define ID_PICTURE_Fan4		"ID_PICTURE_Fan4"
#endif  ID_PICTURE_Fan4
#ifndef ID_TEXT_DeleteInfo0
#define ID_TEXT_DeleteInfo0		"ID_TEXT_DeleteInfo0"
#endif  ID_TEXT_DeleteInfo0
#ifndef ID_TEXT_DeleteInfo1
#define ID_TEXT_DeleteInfo1		"ID_TEXT_DeleteInfo1"
#endif  ID_TEXT_DeleteInfo1
#ifndef ID_TEXT_DeleteInfo2
#define ID_TEXT_DeleteInfo2		"ID_TEXT_DeleteInfo2"
#endif  ID_TEXT_DeleteInfo2

#ifndef ID_CHECKBOX_PLAYER0
#define ID_CHECKBOX_PLAYER0		"ID_CHECKBOX_PLAYER0"
#endif  ID_CHECKBOX_PLAYER0
#ifndef ID_CHECKBOX_PLAYER1
#define ID_CHECKBOX_PLAYER1		"ID_CHECKBOX_PLAYER1"
#endif  ID_CHECKBOX_PLAYER1
#ifndef ID_CHECKBOX_PLAYER2
#define ID_CHECKBOX_PLAYER2		"ID_CHECKBOX_PLAYER2"
#endif  ID_CHECKBOX_PLAYER2

#ifndef ID_TEXT_PageInfo
#define ID_TEXT_PageInfo		"ID_TEXT_PageInfo"
#endif  ID_TEXT_PageInfo

#ifndef ID_BUTTON_Up
#define ID_BUTTON_Up		"ID_BUTTON_Up"
#endif  ID_BUTTON_Up

#ifndef ID_BUTTON_Down
#define ID_BUTTON_Down		"ID_BUTTON_Down"
#endif  ID_BUTTON_Down


#define MAX_PLAYER_COUNT 3
#define Now_CharCount 2

#include "GlobalDef.h"
class TObjectInfo;
class CPlayerAnim;
#include "UiBase.h"

struct SelectPlayerInfo
{
	//选人界面一个玩家的基本结构
	SelectPlayerInfo(SCharBaseInfo* pPlayerInfo,SCharVisual* pVisual,const int nIndex, DWORD dwCharacterID, bool IsDel, DWORD dwDelTime,float fModelPercent)
	{
		m_stPlayerInfo = *pPlayerInfo;
		m_bSlotIsUsed = true;
		m_bSlotCharacterID = dwCharacterID;
		m_pVisual = *pVisual;
		m_bIsDel = IsDel;
		m_fPlayerScale = fModelPercent;
		m_dwDelTime = dwDelTime;
		m_SlotID = nIndex;
	}

	SCharBaseInfo   m_stPlayerInfo;
	SCharVisual     m_pVisual;
	bool			m_bSlotIsUsed;
	DWORD           m_bSlotCharacterID;
	bool            m_bIsDel;
    float           m_fPlayerScale;
	DWORD           m_dwDelTime;
	int				m_SlotID;
};

struct PlayerListManager
{
	PlayerListManager():m_NowPage(0)
	{
		m_PlayerList.clear();
		m_bClear = true;
	}
	int GetIndexByNowPage(int Index)
	{
		int begin = m_NowPage*MAX_PLAYER_COUNT;
		int end = begin + MAX_PLAYER_COUNT -1;
		int VecIndex  =GetInfoBySlot(Index);
		if(VecIndex >= begin && VecIndex<= end)
			return VecIndex - begin;
		else
			return -1;
	}
	int GetSlotByPageIndex(int Index)
	{
		return m_PlayerList[m_NowPage*MAX_PLAYER_COUNT+Index].m_SlotID;
	}
	size_t GetInfoBySlot(int SLot)
	{
		std::vector<SelectPlayerInfo>::iterator Iter = m_PlayerList.begin();
		size_t i = 0;
		for(;Iter != m_PlayerList.end();++Iter)
		{
			if(Iter->m_SlotID == SLot)
			{
				return i;
			}
			++i;
		}
		return 0xFFFFFFFF;
	}
	void AddPlayerInfo(SelectPlayerInfo info)
	{
		std::vector<SelectPlayerInfo>::iterator Iter = m_PlayerList.begin();
		for(;Iter != m_PlayerList.end();++Iter)
		{
			if(Iter->m_bSlotCharacterID == info.m_bSlotCharacterID)
			{
				//同一个角色 替换掉
				Iter = m_PlayerList.insert(Iter,info);
				++Iter;
				m_PlayerList.erase(Iter);
				return;
			}
		}
		m_PlayerList.push_back(info);
	}
	std::vector<SelectPlayerInfo>	m_PlayerList;
	unsigned int					m_NowPage;
	bool							m_bClear;//是否清空,主要用来unload
};

class CUI_ID_FRAME_Select :public CUIBase
{
public:
    CUI_ID_FRAME_Select();

	int	 GetControlMode();
	// Frame
	
	bool OnFrameRun();
	bool OnFrameRender();
	// Button
	bool ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_ENTEROnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_DELETEOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_LEAVEOnButtonClick( ControlObject* pSender );
    // Button
    bool ID_BUTTON_RESTOREOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_UpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DownOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_PLAYER0OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PLAYER1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PLAYER2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PLAYER3OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PLAYER4OnButtonClick( ControlObject* pSender );

	void ID_CHECKBOX_PLAYER0OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PLAYER1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PLAYER2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	// List
	void ID_LIST_PLAYEROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	//鼠标选择控制方式
	void ID_CHECKBOX_KEYBDOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MOUSEOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	bool  initEquipIntensifyEffect();

public:
    static void ID_LIST_PLAYEROnListRBClick( ControlObject* pSender, ControlList::S_List* pItem);
    static void ID_LIST_PLAYEROnListLDBClick( ControlObject* pSender, ControlList::S_List* pItem );
    static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
    static bool FrameOnDBClick( ControlObject* pSender );
	
	const char * GetUserListBySel()
	{
    return  m_pID_TEXT_Names[m_nCurrSel]->GetText();
	}

	void ChangeName();
	int  GetCurSelectPlayerID();
public:
	void Refeash(int index=-1);
	void AddPlayer( MsgAckChar* pAckChar, SCharBaseInfo* pPlayerInfo,SCharVisual* pVisual,const int nIndex, DWORD dwCharacterID, bool IsDel,DWORD dwDelTime ,bool bRefeash = true );

	bool GetStateToLogin();	// true: 说明上次已经点击的 放回登陆 返回选人这样的btn了
	void SetStateToLogin(bool bState = false);

	bool GetStateToCreate();
	void SetStateToCreate(bool bState = false);
	void SetControlMode( int nMode);

	void Release();

    void EnableMoveCamera(BOOL bMove);
    void BackToSelect();

	void ClearPlayerData();
    void LoadScene();

    void SetRotateValue(bool bValue){m_bRotate = bValue;}
    void SetDel(int nIndex,bool bValue,DWORD dwLeftTime);
    bool GetDel(int nIndex);

    bool GetSlotIsUsed(int nIndex);
    void SetSlotIsUsed(int nIndex,bool bValue);


    ControlFrame* GetFrame();
    ControlButton* GetButOnEnter();
    ControlButton* GetButOnCreate();
    ControlList*   GetListOnSelect();

    CPlayerAnim*   GetPlayerAnim(int nIndex);

    void    SetButEnableOnEnter(bool bValue);
    bool    GetButEnableOnEnter();
    
    bool    GetButEnableOnCreate();

    void    SetEnterWorldState(bool bValue){m_isEnterWorld = bValue;}
    bool    GetEnterWorldState(){return m_isEnterWorld;}

    void     SetLastIp(const char* pszValue){m_strLastIp = pszValue;}
    void     SetLastTime(const char* pszValue){m_strLastTime = pszValue;}
    void     SetLastAddress(const char* pszValue){m_strLastAddress = pszValue;}

    int      GetSlotEmpty(){return m_nSlotEmpty;}
	void     SetSlotEmpty(int value) {m_nSlotEmpty = value;}

    static time_t		    m_time;

	int		GetTotalRole();

	SCharBaseInfo GetCurSelPlayerInfo();
	void          InitPlayerAnim();
	bool          IsHavePlayer();
public:
	int   GetPlayAnimBySel();
	void  PlayControlAnim();
	void  PlayAnimByIndex(int nIndex);
	static bool SelectModelLButtonDown(OUT ControlObject* pSender);
	int  GetCurSelIndex(){return m_nCurrSel;}
	void SetMouseMoveIndex(int nIndex){m_nMouseIndex = nIndex;}
	void SetCurrSelectPlayer();
	void SetCheckBoxByIndex(int nIndex);

	int	 GetSlotByIndex(int Index){return m_PlayerInfoList.GetSlotByPageIndex(Index);}

	void SetClearCharacter(bool b){m_PlayerInfoList.m_bClear = b;}

	std::string     m_strWindowText;            // 记录客户端窗口名称
protected:
    bool CheckFocusOnModel();               // 双击人物模型进入游戏      added by zhuomeng.hu		[11/26/2010]
	void SetAnimPos(int nIndex,TObjectInfo* pInfo);
	void SetPlayerInfo(int nIndex);
	void EnterGame(int nIndex);
private:
	std::string m_strLastSel;  //记录上次选择的模型	void  PlayControlAnim();
	int         m_nCurrSel;    //当前选中模型
private:
    // SGuildMember
    ControlCheckBox* m_pID_CHECKBOX_KEYBD;	//键盘控制
    ControlCheckBox* m_pID_CHECKBOX_MOUSE;	//鼠标控制

    ControlFrame*	m_pID_FRAME_SELECT;
    ControlButton*	m_pID_BUTTON_CREATE;
    ControlButton*	m_pID_BUTTON_ENTER;
    ControlButton*	m_pID_BUTTON_DELETE;
    ControlButton*	m_pID_BUTTON_LEAVE;
    ControlButton*  m_pID_BUTTON_RESTORE;
    ControlText*	m_pID_TEXT_NAME;
    ControlText*	m_pID_TEXT_LEVEL;
    ControlText*	m_pID_TEXT_Job;
    ControlText*	m_pID_TEXT_BIRTHDAY;
    ControlText*	m_pID_TEXT_LastIP;
    ControlText*	m_pID_TEXT_LastTime;
    ControlText*	m_pID_TEXT_LastPlace;
    ControlList*	m_pID_LIST_PLAYER;

	ControlButton*	m_pID_BUTTON_PLAYER0;
	ControlButton*	m_pID_BUTTON_PLAYER1;
	ControlButton*	m_pID_BUTTON_PLAYER2;
	ControlButton*	m_pID_BUTTON_PLAYER3;
	ControlButton*	m_pID_BUTTON_PLAYER4;

	ControlCheckBox*	m_pID_CHECKBOX_PLAYER0;
	ControlCheckBox*	m_pID_CHECKBOX_PLAYER1;
	ControlCheckBox*	m_pID_CHECKBOX_PLAYER2;

    ControlButton*	m_pID_BUTTON_Left;
    ControlButton*	m_pID_BUTTON_Right;
	ControlText*	m_pID_TEXT_COUNTRY;			//added by zhuomeng.hu		[8/20/2010]
	ControlText*	m_pID_TEXT_currectsever;	//added by zhuomeng.hu		[8/20/2010]
    ControlPicture* m_pID_PICTURE_CreateBg[MAX_PLAYER_COUNT];

	ControlPicture* m_pID_PICTURE_Jobs[MAX_PLAYER_COUNT][EArmType_MaxSize];
	ControlText*    m_pID_TEXT_Jobs[MAX_PLAYER_COUNT];
	ControlText*    m_pID_TEXT_Names[MAX_PLAYER_COUNT];
	ControlText*    m_pID_TEXT_Levs[MAX_PLAYER_COUNT];

	ControlText*	m_pID_TEXT_DeleteInfo0;
	ControlText*	m_pID_TEXT_DeleteInfo1;
	ControlText*	m_pID_TEXT_DeleteInfo2;

	ControlText*	m_pID_TEXT_PageInfo;
	ControlButton*	m_pID_BUTTON_Up;
    ControlButton*	m_pID_BUTTON_Down;


    bool			m_bToLogin;  //该状态表示　选人->登陆 或者　选人->主游戏　的btn点击 这样的状态改变(记录下，下次主循环在 UnLoadUI)
    bool			m_bToCreate;    //创建新角色
    int				m_nControlMode;

    SCharBaseInfo	m_stPlayerInfo[MAX_PLAYER_COUNT];
    SCharVisual     m_pVisual[MAX_PLAYER_COUNT];
    CPlayerAnim*	m_pPlayerAnim[MAX_PLAYER_COUNT];
	CPlayer*	m_pPlayer[MAX_PLAYER_COUNT];
	int         m_EffectID[MAX_PLAYER_COUNT];
	bool			m_bSlotIsUsed[MAX_PLAYER_COUNT];
    bool            m_bIsDel[MAX_PLAYER_COUNT];
	DWORD           m_dwDelTime[MAX_PLAYER_COUNT];
    DWORD           m_bSlotCharacterID[MAX_PLAYER_COUNT];
    float           m_fPlayerScale[MAX_PLAYER_COUNT];
	float           m_fPlayerRotate[MAX_PLAYER_COUNT];
	D3DXVECTOR3		m_vPlayerPos[MAX_PLAYER_COUNT];


    CPlayerAnim*	m_pRenderPlayer;
   
    int				m_nSlotEmpty;
    BOOL			m_bUpdateOnce;
    
	float			m_fPlayerBaseScale;
    MexAnimCtrl*    m_pCameraModel;
    MexAnimCtrl*    m_pDoorModel;
	MexAnimCtrl*    m_pBGModel;
    BOOL            m_bMoveCamera;
    BOOL            m_bMoveBackCamera;
    BOOL            m_bForceUpdateCamera;
    Vector          m_vCameraStartPos;
    DWORD           m_dwCameraStartMoveTime;
    BOOL            m_bPlayCameraAnim;

    MeCamera*       m_pCamera;
    INT				m_OldSelPlayerList;

    D3DXVECTOR3     m_vEye;
    D3DXVECTOR3     m_vLookat;
    float           m_RotateZ;
    bool            m_bIsTileLoaded;
    bool            m_bRotate;
    bool            m_bNeedSetLastLogin;
    bool            m_bNeedReadUserData;
    char            m_pszLastLoginRole[MAX_PATH];
    int			    m_nEnterWorldCount;
    bool		    m_isEnterWorld;
    std::string     m_strLastIp;
    std::string     m_strLastAddress;
    std::string     m_strLastTime;
    

	int				m_totalRole;

    ControlGroup    m_Group;
	int             m_nMouseIndex;

	PlayerListManager  m_PlayerInfoList;
//以下接口都是为创建人物之后默认选择上一步创建的人时所用
public:
	static  int     m_CurrentSelectIndex;
private:
	static  bool	m_IsSetCameraForCreate;
private:
	void	ChangePageShowPlayerInfo(int Page);
	void	UpdatePageInfo();
	void    LoadPlayer();
};
extern CUI_ID_FRAME_Select s_CUI_ID_FRAME_Select;
extern bool EnterWorldFailed(const char bPressYesButton, void *pData);